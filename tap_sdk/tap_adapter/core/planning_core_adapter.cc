#include "tap_adapter/core/planning_core_adapter.h"

#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <utility>

#include <absl/status/status.h>
#include <absl/strings/str_cat.h>

#include "maps/lane_path.h"
#include "maps/lane_path_data.h"
#include "scheduler/path_boundary_builder.h"

namespace tap {
namespace planning_adapter {
namespace core {
namespace {

constexpr double kGeometryEpsilon = 1e-6;
constexpr double kMinCorridorWidth = 0.1;
constexpr double kMaxCorridorWidth = 30.0;
constexpr double kMaxNormalizedSpeed = 100.0;
constexpr double kMaxLocalCoordinate = 1.0e7;
constexpr double kPi = 3.14159265358979323846;

bool IsFinite(double value) { return std::isfinite(value); }

absl::Status Invalid(const char *field, size_t index) {
    return absl::InvalidArgumentError(
        absl::StrCat("invalid corridor ", field, " at point ", index));
}

pnc_x::planning::StationBoundaryType ToStationBoundaryType(
    NormalizedBoundaryType type) {
    switch (type) {
        case NormalizedBoundaryType::kUnknown:
            return pnc_x::planning::StationBoundaryType::UNKNOWN_TYPE;
        case NormalizedBoundaryType::kDashedLaneMarking:
            return pnc_x::planning::StationBoundaryType::BROKEN_WHITE;
        case NormalizedBoundaryType::kSolidLaneMarking:
            return pnc_x::planning::StationBoundaryType::SOLID_WHITE;
        case NormalizedBoundaryType::kCurb:
            return pnc_x::planning::StationBoundaryType::CURB;
        case NormalizedBoundaryType::kVirtual:
            return pnc_x::planning::StationBoundaryType::VIRTUAL_CURB;
    }
    return pnc_x::planning::StationBoundaryType::UNKNOWN_TYPE;
}

absl::Status ValidateEgo(const NormalizedEgoState &ego) {
    if (ego.source_timestamp_ns == 0) {
        return absl::InvalidArgumentError("ego timestamp is zero");
    }
    if (!IsFinite(ego.x) || !IsFinite(ego.y) || !IsFinite(ego.heading) ||
        !IsFinite(ego.speed) || !IsFinite(ego.acceleration) ||
        !IsFinite(ego.curvature)) {
        return absl::InvalidArgumentError("ego state contains non-finite data");
    }
    if (ego.speed < 0.0) {
        return absl::InvalidArgumentError("ego speed must be non-negative");
    }
    if (std::abs(ego.x) > kMaxLocalCoordinate ||
        std::abs(ego.y) > kMaxLocalCoordinate ||
        std::abs(ego.heading) > kPi + kGeometryEpsilon ||
        ego.speed > kMaxNormalizedSpeed) {
        return absl::InvalidArgumentError(
            "ego state violates normalized coordinate or unit limits");
    }
    return absl::OkStatus();
}

absl::Status ValidateCorridor(const NormalizedRoadCorridor &corridor) {
    if (corridor.source_timestamp_ns == 0) {
        return absl::InvalidArgumentError("corridor timestamp is zero");
    }
    if (corridor.points.size() < 2) {
        return absl::InvalidArgumentError(
            "corridor requires at least two center points");
    }
    std::unordered_set<uint64_t> lane_ids;
    uint64_t previous_lane_id = 0;
    for (size_t i = 0; i < corridor.points.size(); ++i) {
        const auto &point = corridor.points[i];
        if (!IsFinite(point.x) || !IsFinite(point.y) ||
            !IsFinite(point.heading) || !IsFinite(point.s) ||
            !IsFinite(point.right_width) || !IsFinite(point.left_width) ||
            !IsFinite(point.speed_limit)) {
            return Invalid("geometry", i);
        }
        if (std::abs(point.x) > kMaxLocalCoordinate ||
            std::abs(point.y) > kMaxLocalCoordinate ||
            std::abs(point.heading) > kPi + kGeometryEpsilon) {
            return Invalid("coordinate or heading units", i);
        }
        if (point.lane_id == 0) {
            return Invalid("lane_id", i);
        }
        if (point.right_width < kMinCorridorWidth ||
            point.left_width < kMinCorridorWidth ||
            point.right_width > kMaxCorridorWidth ||
            point.left_width > kMaxCorridorWidth) {
            return Invalid("boundary width", i);
        }
        if (point.speed_limit < 0.0 ||
            point.speed_limit > kMaxNormalizedSpeed) {
            return Invalid("speed_limit", i);
        }
        if (i == 0) {
            if (std::abs(point.s) > kGeometryEpsilon) {
                return absl::InvalidArgumentError(
                    "corridor s must start at the local origin");
            }
        } else {
            const auto &previous = corridor.points[i - 1];
            if (point.s <= previous.s + kGeometryEpsilon) {
                return Invalid("non-monotonic s", i);
            }
            const double dx = point.x - previous.x;
            const double dy = point.y - previous.y;
            const double chord = std::hypot(dx, dy);
            if (chord <= kGeometryEpsilon) {
                return Invalid("duplicate center point", i);
            }
            const double delta_s = point.s - previous.s;
            const double max_arc_chord_error = std::max(0.5, 0.2 * delta_s);
            if (chord > delta_s + kGeometryEpsilon ||
                delta_s - chord > max_arc_chord_error) {
                return Invalid("s/geometry discontinuity", i);
            }
        }
        // Repeated samples of one lane are normal.  A lane appearing again
        // after a transition indicates an ambiguous/non-linear lane path.
        if (point.lane_id != previous_lane_id) {
            if (!lane_ids.insert(point.lane_id).second) {
                return Invalid("lane sequence re-entry", i);
            }
            previous_lane_id = point.lane_id;
        }
    }
    return absl::OkStatus();
}

}  // namespace

absl::StatusOr<pnc_x::ApolloTrajectoryPointProto> ToApolloTrajectoryPoint(
    const NormalizedEgoState &ego) {
    const auto status = ValidateEgo(ego);
    if (!status.ok()) {
        return status;
    }
    pnc_x::ApolloTrajectoryPointProto point;
    auto *path_point = point.mutable_path_point();
    path_point->set_x(ego.x);
    path_point->set_y(ego.y);
    path_point->set_theta(ego.heading);
    path_point->set_kappa(ego.curvature);
    path_point->set_s(0.0);
    point.set_v(ego.speed);
    point.set_a(ego.acceleration);
    point.set_j(0.0);
    point.set_relative_time(0.0);
    return point;
}

absl::StatusOr<pnc_x::planning::DrivePassage> BuildDrivePassage(
    const NormalizedRoadCorridor &corridor) {
    const auto status = ValidateCorridor(corridor);
    if (!status.ok()) {
        return status;
    }

    std::vector<pnc_x::mapping::ElementId> lane_ids;
    std::vector<double> lane_end_s{0.0};
    lane_ids.reserve(corridor.points.size());
    lane_end_s.reserve(corridor.points.size() + 1);
    uint64_t active_lane_id = corridor.points.front().lane_id;
    for (size_t i = 1; i < corridor.points.size(); ++i) {
        if (corridor.points[i].lane_id == active_lane_id) {
            continue;
        }
        lane_ids.push_back(active_lane_id);
        lane_end_s.push_back(corridor.points[i].s);
        active_lane_id = corridor.points[i].lane_id;
    }
    lane_ids.push_back(active_lane_id);
    lane_end_s.push_back(corridor.points.back().s);

    std::vector<double> lane_lengths;
    lane_lengths.reserve(lane_ids.size());
    for (size_t i = 1; i < lane_end_s.size(); ++i) {
        const double length = lane_end_s[i] - lane_end_s[i - 1];
        if (length <= kGeometryEpsilon) {
            return absl::InvalidArgumentError(
                "lane segment has no positive longitudinal length");
        }
        lane_lengths.push_back(length);
    }

    const auto station_lane_ids = lane_ids;
    const pnc_x::mapping::LanePathData lane_path_data(0.0, 1.0,
                                                      std::move(lane_ids));
    const pnc_x::mapping::LanePath lane_path(lane_path_data, lane_end_s,
                                             lane_lengths);

    pnc_x::planning::StationVector<pnc_x::planning::Station> stations;
    stations.reserve(corridor.points.size());
    size_t lane_index = 0;
    for (size_t i = 0; i < corridor.points.size(); ++i) {
        const auto &point = corridor.points[i];
        if (point.lane_id != station_lane_ids[lane_index]) {
            ++lane_index;
        }
        const double segment_start_s = lane_end_s[lane_index];
        const double segment_end_s = lane_end_s[lane_index + 1];
        const double fraction =
            (point.s - segment_start_s) / (segment_end_s - segment_start_s);
        pnc_x::planning::StationCenter center;
        center.lane_id = point.lane_id;
        center.fraction = std::max(0.0, std::min(1.0, fraction));
        center.xy = pnc_x::Vec2d(point.x, point.y);
        center.tangent =
            pnc_x::Vec2d(std::cos(point.heading), std::sin(point.heading));
        center.accum_s = point.s;
        center.speed_limit = point.speed_limit;
        center.is_virtual =
            point.right_boundary == NormalizedBoundaryType::kVirtual &&
            point.left_boundary == NormalizedBoundaryType::kVirtual;
        center.turn_type = ads_x::planning::NO_TURN;
        center.station_info.speed_limit = point.speed_limit;
        center.station_info.turn_type = ads_x::planning::NO_TURN;
        stations.emplace_back(center,
                              std::vector<pnc_x::planning::StationBoundary>{
                                  {ToStationBoundaryType(point.right_boundary),
                                   -point.right_width},
                                  {ToStationBoundaryType(point.left_boundary),
                                   point.left_width}});
    }
    return pnc_x::planning::DrivePassage(std::move(stations), lane_path,
                                         lane_path, 0.0, false,
                                         pnc_x::FrenetFrameType::kBvh, {});
}

absl::StatusOr<pnc_x::planning::PathSlBoundary> BuildPathSlBoundary(
    const NormalizedRoadCorridor &corridor) {
    auto drive_passage = BuildDrivePassage(corridor);
    if (!drive_passage.ok()) {
        return drive_passage.status();
    }
    return pnc_x::planning::BuildPathBoundaryFromDrivePassage(*drive_passage);
}

absl::StatusOr<PlanningGeometry> BuildPlanningGeometry(
    const NormalizedEgoState &ego, const NormalizedRoadCorridor &corridor) {
    auto start_point = ToApolloTrajectoryPoint(ego);
    if (!start_point.ok()) {
        return start_point.status();
    }
    auto drive_passage = BuildDrivePassage(corridor);
    if (!drive_passage.ok()) {
        return drive_passage.status();
    }
    const pnc_x::Vec2d ego_xy(start_point->path_point().x(),
                              start_point->path_point().y());
    const auto ego_sl = drive_passage->QueryFrenetCoordinateAt(ego_xy);
    if (!ego_sl.ok()) {
        return absl::OutOfRangeError(
            absl::StrCat("ego is outside normalized road corridor: ",
                         ego_sl.status().message()));
    }
    auto path_boundary =
        pnc_x::planning::BuildPathBoundaryFromDrivePassage(*drive_passage);
    if (!path_boundary.ok()) {
        return path_boundary.status();
    }
    PlanningGeometry result;
    result.start_point = std::move(*start_point);
    result.drive_passage = std::move(*drive_passage);
    result.path_boundary = std::move(*path_boundary);
    return result;
}

}  // namespace core
}  // namespace planning_adapter
}  // namespace tap
