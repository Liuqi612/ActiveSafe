#include "tap_adapter/core/planning_core_adapter.h"

#include <cassert>
#include <cmath>
#include <limits>

namespace {

using tap::planning_adapter::core::BuildDrivePassage;
using tap::planning_adapter::core::NormalizedBoundaryType;
using tap::planning_adapter::core::NormalizedCorridorPoint;
using tap::planning_adapter::core::NormalizedEgoState;
using tap::planning_adapter::core::NormalizedRoadCorridor;
using tap::planning_adapter::core::ToApolloTrajectoryPoint;

NormalizedRoadCorridor MakeStraightCorridor() {
    NormalizedRoadCorridor corridor;
    corridor.source_timestamp_ns = 1;
    for (int i = 0; i < 11; ++i) {
        NormalizedCorridorPoint point;
        point.x = static_cast<double>(i) * 5.0;
        point.y = 0.0;
        point.heading = 0.0;
        point.s = point.x;
        point.lane_id = 42;
        point.right_width = 2.0;
        point.left_width = 2.0;
        point.speed_limit = 15.0;
        point.right_boundary = NormalizedBoundaryType::kDashedLaneMarking;
        point.left_boundary = NormalizedBoundaryType::kCurb;
        corridor.points.push_back(point);
    }
    return corridor;
}

void TestEgoConversion() {
    NormalizedEgoState ego;
    ego.source_timestamp_ns = 1;
    ego.x = 2.0;
    ego.y = -1.0;
    ego.heading = 0.3;
    ego.speed = 4.0;
    ego.acceleration = 0.2;
    ego.curvature = 0.01;
    const auto result = ToApolloTrajectoryPoint(ego);
    assert(result.ok());
    assert(std::abs(result->path_point().x() - 2.0) < 1e-9);
    assert(std::abs(result->v() - 4.0) < 1e-9);
}

void TestStraightAndLaneTransition() {
    auto corridor = MakeStraightCorridor();
    corridor.points[6].lane_id = 43;
    corridor.points[7].lane_id = 43;
    corridor.points[8].lane_id = 43;
    corridor.points[9].lane_id = 43;
    corridor.points[10].lane_id = 43;
    const auto result = BuildDrivePassage(corridor);
    assert(result.ok());
    assert(result->size() == 11);
    assert(result->lane_path().lane_ids().size() == 2);
    assert(result->end_s() > 49.0);
    assert(std::abs(result->station(pnc_x::planning::StationIndex(6))
                        .GetLanePoint()
                        .fraction()) < 1e-9);
    assert(result->station(pnc_x::planning::StationIndex(0))
               .boundaries()[0]
               .lat_offset < 0.0);
}

void TestRejectsMalformedCorridor() {
    auto too_short = MakeStraightCorridor();
    too_short.points.resize(1);
    assert(!BuildDrivePassage(too_short).ok());

    auto bad_s = MakeStraightCorridor();
    bad_s.points[3].s = bad_s.points[2].s;
    assert(!BuildDrivePassage(bad_s).ok());

    auto bad_width = MakeStraightCorridor();
    bad_width.points[2].left_width = 0.0;
    assert(!BuildDrivePassage(bad_width).ok());

    auto reentry = MakeStraightCorridor();
    reentry.points[4].lane_id = 2;
    reentry.points[5].lane_id = 2;
    reentry.points[6].lane_id = 42;
    assert(!BuildDrivePassage(reentry).ok());

    auto nonfinite = MakeStraightCorridor();
    nonfinite.points[1].x = std::numeric_limits<double>::quiet_NaN();
    assert(!BuildDrivePassage(nonfinite).ok());

    auto zero_lane = MakeStraightCorridor();
    zero_lane.points[2].lane_id = 0;
    assert(!BuildDrivePassage(zero_lane).ok());

    auto discontinuous_s = MakeStraightCorridor();
    for (size_t i = 5; i < discontinuous_s.points.size(); ++i) {
        discontinuous_s.points[i].s += 20.0;
    }
    assert(!BuildDrivePassage(discontinuous_s).ok());
}

void TestCurvedCorridor() {
    NormalizedRoadCorridor corridor;
    corridor.source_timestamp_ns = 1;
    constexpr double kRadius = 50.0;
    for (int i = 0; i <= 10; ++i) {
        const double angle = 0.05 * static_cast<double>(i);
        NormalizedCorridorPoint point;
        point.x = kRadius * std::sin(angle);
        point.y = kRadius * (1.0 - std::cos(angle));
        point.heading = angle;
        point.s = kRadius * angle;
        point.lane_id = 7;
        point.right_width = 1.8;
        point.left_width = 2.2;
        point.speed_limit = 12.0;
        corridor.points.push_back(point);
    }
    const auto result = BuildDrivePassage(corridor);
    assert(result.ok());
    const auto tangent = result->QueryTangentAtS(12.5);
    assert(tangent.ok());
    assert(tangent->y() > 0.0);
}

void TestPathBoundaryAndEgoValidation() {
    const auto corridor = MakeStraightCorridor();
    const auto boundary =
        tap::planning_adapter::core::BuildPathSlBoundary(corridor);
    assert(boundary.ok());
    assert(boundary->size() == static_cast<int>(corridor.points.size()));
    assert(boundary->right_l_vector()[0] < boundary->left_l_vector()[0]);

    NormalizedEgoState bad_ego;
    bad_ego.source_timestamp_ns = 1;
    bad_ego.speed = -1.0;
    assert(!ToApolloTrajectoryPoint(bad_ego).ok());
    bad_ego.speed = 0.0;
    bad_ego.x = std::numeric_limits<double>::infinity();
    assert(!ToApolloTrajectoryPoint(bad_ego).ok());

    NormalizedEgoState ego;
    ego.source_timestamp_ns = 1;
    ego.speed = 1.0;
    auto geometry =
        tap::planning_adapter::core::BuildPlanningGeometry(ego, corridor);
    assert(geometry.ok());
    ego.y = 10.0;
    geometry =
        tap::planning_adapter::core::BuildPlanningGeometry(ego, corridor);
    assert(!geometry.ok());
}

}  // namespace

int main() {
    TestEgoConversion();
    TestStraightAndLaneTransition();
    TestRejectsMalformedCorridor();
    TestCurvedCorridor();
    TestPathBoundaryAndEgoValidation();
    return 0;
}
