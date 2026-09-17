// Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
//
// Planning adapter boundary: timestamp alignment only.  RSCL message
// readers and Planning algorithm types intentionally do not appear here.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>

namespace tap {
namespace planning_adapter {

using TimestampNs = uint64_t;

constexpr TimestampNs kNanosecondsPerMillisecond = 1000000ULL;
constexpr TimestampNs kNanosecondsPerSecond = 1000000000ULL;

enum class PlanningInputKind : uint8_t {
    kEgoState = 0,
    kRoadStructure,
    kObjects,
    kPrediction,
    kOccupancy,
    kRouteGuidance,
    kTrafficRules,
    kPreviousTrajectory,
    kCount,
};

const char *PlanningInputKindName(PlanningInputKind kind);

enum class SnapshotFailureReason : uint8_t {
    kNone = 0,
    kInvalidFrameTimestamp,
    kMissingSample,
    kInvalidSample,
    kFutureSample,
    kStaleSample,
};

// These limits are copied from the emergency Planning input contract.  The
// adapter stores only metadata; the message-specific payload remains owned by
// the Node and is converted after this snapshot has been accepted.
struct SnapshotPolicy {
    TimestampNs ego_max_age_ns = 100ULL * kNanosecondsPerMillisecond;
    TimestampNs road_max_age_ns = 500ULL * kNanosecondsPerMillisecond;
    TimestampNs objects_max_age_ns = 200ULL * kNanosecondsPerMillisecond;
    TimestampNs prediction_max_age_ns = 300ULL * kNanosecondsPerMillisecond;
    TimestampNs occupancy_max_age_ns = 300ULL * kNanosecondsPerMillisecond;
    TimestampNs route_max_age_ns = 1ULL * kNanosecondsPerSecond;
    TimestampNs traffic_max_age_ns = 1ULL * kNanosecondsPerSecond;
    TimestampNs previous_trajectory_max_age_ns =
        100ULL * kNanosecondsPerMillisecond;

    // Prediction is mandatory by default.  An adapter may explicitly opt in
    // to an object-only Normal fallback; omission must never happen silently.
    bool require_prediction = true;
    bool allow_object_only_fallback = false;

    // Keep enough monotonic history for a planning tick to select the newest
    // sample at or before T even when a newer callback has already arrived.
    size_t history_depth = 16;
};

struct InputSample {
    TimestampNs source_timestamp_ns = 0;
    bool received = false;
    bool valid = false;
    bool explicitly_empty = false;
    bool usable = false;
};

struct PlanningSnapshot {
    TimestampNs frame_timestamp_ns = 0;
    std::array<InputSample, static_cast<size_t>(PlanningInputKind::kCount)>
        samples{};
    bool object_only_fallback = false;

    const InputSample &Sample(PlanningInputKind kind) const {
        return samples[static_cast<size_t>(kind)];
    }
};

struct SnapshotValidationResult {
    bool ok = false;
    SnapshotFailureReason failure = SnapshotFailureReason::kNone;
    PlanningInputKind input_kind = PlanningInputKind::kEgoState;
    std::string message;
    PlanningSnapshot snapshot;
};

class PlanningSnapshotAssembler {
 public:
    explicit PlanningSnapshotAssembler(
        SnapshotPolicy policy = SnapshotPolicy{});

    // Updates are monotonic per input.  An out-of-order sample is rejected and
    // the previously accepted sample remains intact.
    bool Update(PlanningInputKind kind,
                TimestampNs source_timestamp_ns,
                bool valid = true,
                bool explicitly_empty = false);

    void Clear(PlanningInputKind kind);

    SnapshotValidationResult Build(TimestampNs frame_timestamp_ns) const;

    const InputSample &Latest(PlanningInputKind kind) const {
        const auto &history = histories_[static_cast<size_t>(kind)];
        return history.empty() ? empty_sample_ : history.back();
    }

 private:
    static bool IsKnownKind(PlanningInputKind kind);
    static size_t Index(PlanningInputKind kind);

    SnapshotValidationResult ValidateRequired(const PlanningSnapshot &snapshot,
                                              PlanningInputKind kind,
                                              TimestampNs max_age_ns) const;
    void MarkOptionalUsability(PlanningSnapshot *snapshot,
                               PlanningInputKind kind,
                               TimestampNs max_age_ns) const;

    SnapshotPolicy policy_;
    const InputSample *SelectAtOrBefore(PlanningInputKind kind,
                                        TimestampNs frame_timestamp_ns) const;

    std::array<std::deque<InputSample>,
               static_cast<size_t>(PlanningInputKind::kCount)>
        histories_{};
    InputSample empty_sample_{};
};

}  // namespace planning_adapter
}  // namespace tap
