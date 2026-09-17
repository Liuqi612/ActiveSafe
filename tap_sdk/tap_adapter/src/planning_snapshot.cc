#include "tap_adapter/include/planning_snapshot.h"

#include <limits>

namespace tap {
namespace planning_adapter {

namespace {

SnapshotValidationResult Failure(SnapshotFailureReason reason,
                                 PlanningInputKind kind,
                                 const std::string &message,
                                 const PlanningSnapshot &snapshot) {
    SnapshotValidationResult result;
    result.failure = reason;
    result.input_kind = kind;
    result.message = message;
    result.snapshot = snapshot;
    return result;
}

}  // namespace

const char *PlanningInputKindName(PlanningInputKind kind) {
    switch (kind) {
        case PlanningInputKind::kEgoState:
            return "ego_state";
        case PlanningInputKind::kRoadStructure:
            return "road_structure";
        case PlanningInputKind::kObjects:
            return "objects";
        case PlanningInputKind::kPrediction:
            return "prediction";
        case PlanningInputKind::kOccupancy:
            return "occupancy";
        case PlanningInputKind::kRouteGuidance:
            return "route_guidance";
        case PlanningInputKind::kTrafficRules:
            return "traffic_rules";
        case PlanningInputKind::kPreviousTrajectory:
            return "previous_trajectory";
        case PlanningInputKind::kCount:
            break;
    }
    return "unknown";
}

PlanningSnapshotAssembler::PlanningSnapshotAssembler(SnapshotPolicy policy)
    : policy_(policy) {}

bool PlanningSnapshotAssembler::IsKnownKind(PlanningInputKind kind) {
    return static_cast<size_t>(kind) <
           static_cast<size_t>(PlanningInputKind::kCount);
}

size_t PlanningSnapshotAssembler::Index(PlanningInputKind kind) {
    return static_cast<size_t>(kind);
}

bool PlanningSnapshotAssembler::Update(PlanningInputKind kind,
                                       TimestampNs source_timestamp_ns,
                                       bool valid,
                                       bool explicitly_empty) {
    if (!IsKnownKind(kind) || source_timestamp_ns == 0) {
        return false;
    }
    auto &history = histories_[Index(kind)];
    if (!history.empty() &&
        source_timestamp_ns < history.back().source_timestamp_ns) {
        return false;
    }
    InputSample sample;
    sample.source_timestamp_ns = source_timestamp_ns;
    sample.received = true;
    sample.valid = valid;
    sample.explicitly_empty = explicitly_empty;
    sample.usable = false;
    if (!history.empty() &&
        source_timestamp_ns == history.back().source_timestamp_ns) {
        history.back() = sample;
        return true;
    }
    history.push_back(sample);
    const size_t history_depth =
        policy_.history_depth == 0 ? 1 : policy_.history_depth;
    while (history.size() > history_depth) {
        history.pop_front();
    }
    return true;
}

void PlanningSnapshotAssembler::Clear(PlanningInputKind kind) {
    if (IsKnownKind(kind)) {
        histories_[Index(kind)].clear();
    }
}

const InputSample *PlanningSnapshotAssembler::SelectAtOrBefore(
    PlanningInputKind kind, TimestampNs frame_timestamp_ns) const {
    const auto &history = histories_[Index(kind)];
    for (auto it = history.rbegin(); it != history.rend(); ++it) {
        if (it->source_timestamp_ns <= frame_timestamp_ns) {
            return &*it;
        }
    }
    return nullptr;
}

SnapshotValidationResult PlanningSnapshotAssembler::ValidateRequired(
    const PlanningSnapshot &snapshot,
    PlanningInputKind kind,
    TimestampNs max_age_ns) const {
    const auto &sample = snapshot.Sample(kind);
    if (!sample.received) {
        return Failure(SnapshotFailureReason::kMissingSample, kind,
                       std::string("missing ") + PlanningInputKindName(kind),
                       snapshot);
    }
    if (!sample.valid) {
        return Failure(SnapshotFailureReason::kInvalidSample, kind,
                       std::string("invalid ") + PlanningInputKindName(kind),
                       snapshot);
    }
    if (sample.source_timestamp_ns > snapshot.frame_timestamp_ns) {
        return Failure(SnapshotFailureReason::kFutureSample, kind,
                       std::string("future ") + PlanningInputKindName(kind),
                       snapshot);
    }
    if (snapshot.frame_timestamp_ns - sample.source_timestamp_ns > max_age_ns) {
        return Failure(SnapshotFailureReason::kStaleSample, kind,
                       std::string("stale ") + PlanningInputKindName(kind),
                       snapshot);
    }
    return SnapshotValidationResult{};
}

void PlanningSnapshotAssembler::MarkOptionalUsability(
    PlanningSnapshot *snapshot,
    PlanningInputKind kind,
    TimestampNs max_age_ns) const {
    auto &sample = snapshot->samples[Index(kind)];
    sample.usable =
        sample.received && sample.valid &&
        sample.source_timestamp_ns <= snapshot->frame_timestamp_ns &&
        snapshot->frame_timestamp_ns - sample.source_timestamp_ns <= max_age_ns;
}

SnapshotValidationResult PlanningSnapshotAssembler::Build(
    TimestampNs frame_timestamp_ns) const {
    PlanningSnapshot snapshot;
    snapshot.frame_timestamp_ns = frame_timestamp_ns;
    if (frame_timestamp_ns == 0) {
        return Failure(SnapshotFailureReason::kInvalidFrameTimestamp,
                       PlanningInputKind::kEgoState,
                       "planning frame timestamp is zero", snapshot);
    }

    for (size_t i = 0; i < static_cast<size_t>(PlanningInputKind::kCount);
         ++i) {
        const auto kind = static_cast<PlanningInputKind>(i);
        const auto *selected = SelectAtOrBefore(kind, frame_timestamp_ns);
        if (selected != nullptr) {
            snapshot.samples[i] = *selected;
        } else if (!histories_[i].empty()) {
            // Preserve the earliest future sample so validation reports
            // "future" instead of incorrectly reporting a missing topic.
            snapshot.samples[i] = histories_[i].front();
        }
    }

    for (const auto kind :
         {PlanningInputKind::kEgoState, PlanningInputKind::kRoadStructure}) {
        const auto max_age_ns = kind == PlanningInputKind::kEgoState
                                    ? policy_.ego_max_age_ns
                                    : policy_.road_max_age_ns;
        auto result = ValidateRequired(snapshot, kind, max_age_ns);
        if (result.failure != SnapshotFailureReason::kNone) {
            return result;
        }
        snapshot.samples[Index(kind)].usable = true;
    }

    auto objects = ValidateRequired(snapshot, PlanningInputKind::kObjects,
                                    policy_.objects_max_age_ns);
    if (objects.failure != SnapshotFailureReason::kNone) {
        return objects;
    }
    snapshot.samples[Index(PlanningInputKind::kObjects)].usable = true;

    if (policy_.require_prediction) {
        auto prediction =
            ValidateRequired(snapshot, PlanningInputKind::kPrediction,
                             policy_.prediction_max_age_ns);
        if (prediction.failure != SnapshotFailureReason::kNone) {
            if (!policy_.allow_object_only_fallback ||
                prediction.failure == SnapshotFailureReason::kInvalidSample ||
                prediction.failure == SnapshotFailureReason::kFutureSample ||
                prediction.failure == SnapshotFailureReason::kStaleSample ||
                prediction.failure == SnapshotFailureReason::kMissingSample) {
                if (!policy_.allow_object_only_fallback) {
                    return prediction;
                }
                snapshot.object_only_fallback = true;
            }
        } else {
            snapshot.samples[Index(PlanningInputKind::kPrediction)].usable =
                true;
        }
    }

    MarkOptionalUsability(&snapshot, PlanningInputKind::kOccupancy,
                          policy_.occupancy_max_age_ns);
    MarkOptionalUsability(&snapshot, PlanningInputKind::kRouteGuidance,
                          policy_.route_max_age_ns);
    MarkOptionalUsability(&snapshot, PlanningInputKind::kTrafficRules,
                          policy_.traffic_max_age_ns);
    MarkOptionalUsability(&snapshot, PlanningInputKind::kPreviousTrajectory,
                          policy_.previous_trajectory_max_age_ns);

    SnapshotValidationResult result;
    result.ok = true;
    result.snapshot = snapshot;
    return result;
}

}  // namespace planning_adapter
}  // namespace tap
