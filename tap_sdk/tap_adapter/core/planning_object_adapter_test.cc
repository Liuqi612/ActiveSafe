#include "tap_adapter/core/planning_object_adapter.h"

#include <cassert>
#include <limits>

namespace {

using tap::planning_adapter::core::BuildSpacetimeTrajectoryManager;
using tap::planning_adapter::core::NormalizedObjectType;
using tap::planning_adapter::core::NormalizedPoint2d;
using tap::planning_adapter::core::NormalizedPredictedObject;
using tap::planning_adapter::core::NormalizedPredictedPoint;
using tap::planning_adapter::core::NormalizedPredictedTrajectory;
using tap::planning_adapter::core::NormalizedPredictionType;
using tap::planning_adapter::core::ValidatePredictedObjects;

NormalizedPredictedObject MakeMovingObject() {
    NormalizedPredictedObject object;
    object.source_timestamp_ns = 1000000000ULL;
    object.id = "101";
    object.type = NormalizedObjectType::kVehicle;
    object.x = 10.0;
    object.y = 0.0;
    object.velocity_x = 5.0;
    object.length = 4.5;
    object.width = 2.0;
    object.contour = {{12.25, 1.0}, {7.75, 1.0}, {7.75, -1.0}, {12.25, -1.0}};
    NormalizedPredictedTrajectory trajectory;
    trajectory.index = 0;
    trajectory.probability = 1.0;
    trajectory.type = NormalizedPredictionType::kVehicle;
    for (int i = 0; i < 4; ++i) {
        NormalizedPredictedPoint point;
        point.x = 10.0 + static_cast<double>(i);
        point.y = 0.0;
        point.s = static_cast<double>(i);
        point.relative_time = 0.2 * static_cast<double>(i);
        point.speed = 5.0;
        trajectory.points.push_back(point);
    }
    object.trajectories.push_back(trajectory);
    return object;
}

NormalizedPredictedObject MakeStationaryObject() {
    auto object = MakeMovingObject();
    object.id = "202";
    object.type = NormalizedObjectType::kCone;
    object.velocity_x = 0.0;
    object.length = 0.5;
    object.width = 0.5;
    object.trajectories.clear();
    NormalizedPredictedTrajectory trajectory;
    trajectory.index = 0;
    trajectory.probability = 1.0;
    trajectory.type = NormalizedPredictionType::kStationary;
    NormalizedPredictedPoint point;
    point.x = object.x;
    point.y = object.y;
    trajectory.points.push_back(point);
    object.trajectories.push_back(trajectory);
    return object;
}

void TestMovingAndStationaryObjects() {
    assert(
        ValidatePredictedObjects({MakeMovingObject(), MakeStationaryObject()})
            .ok());
    const auto result = BuildSpacetimeTrajectoryManager(
        {MakeMovingObject(), MakeStationaryObject()});
    assert(result.ok());
    assert(result->trajectories().size() == 2);
    assert(result->moving_object_trajs().size() == 1);
    assert(result->stationary_object_trajs().size() == 1);
    assert(result->FindObjectByObjectId("101") != nullptr);
    assert(result->FindObjectByObjectId("202") != nullptr);
    assert(result->FindTrajectoriesByObjectId("202")[0]->states().size() > 1);
}

void TestExplicitEmptyObjects() {
    const auto result = BuildSpacetimeTrajectoryManager({});
    assert(result.ok());
    assert(result->trajectories().empty());
}

void TestRejectsInvalidObjects() {
    auto object = MakeMovingObject();
    object.contour.resize(2);
    assert(!BuildSpacetimeTrajectoryManager({object}).ok());

    object = MakeMovingObject();
    object.contour = {{12.0, 1.0}, {8.0, -1.0}, {8.0, 1.0}, {12.0, -1.0}};
    assert(!BuildSpacetimeTrajectoryManager({object}).ok());

    object = MakeMovingObject();
    object.trajectories.clear();
    assert(!BuildSpacetimeTrajectoryManager({object}).ok());

    object = MakeMovingObject();
    object.trajectories[0].points[1].relative_time = 0.0;
    assert(!BuildSpacetimeTrajectoryManager({object}).ok());

    object = MakeMovingObject();
    object.trajectories[0].probability = 1.1;
    assert(!BuildSpacetimeTrajectoryManager({object}).ok());

    object = MakeStationaryObject();
    object.trajectories[0].points[0].speed = 1.0;
    assert(!BuildSpacetimeTrajectoryManager({object}).ok());

    object = MakeMovingObject();
    object.x = std::numeric_limits<double>::quiet_NaN();
    assert(!BuildSpacetimeTrajectoryManager({object}).ok());

    const auto duplicate = MakeMovingObject();
    assert(!BuildSpacetimeTrajectoryManager({duplicate, duplicate}).ok());

    auto different_timestamp = MakeStationaryObject();
    different_timestamp.source_timestamp_ns += 1;
    assert(!BuildSpacetimeTrajectoryManager(
                {MakeMovingObject(), different_timestamp})
                .ok());
}

}  // namespace

int main() {
    TestMovingAndStationaryObjects();
    TestExplicitEmptyObjects();
    TestRejectsInvalidObjects();
    return 0;
}
