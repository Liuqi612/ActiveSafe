#include "tap_adapter/core/planning_runtime_adapter.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

namespace {

tap::planning_adapter::core::NormalizedRoadCorridor MakeCorridor() {
    tap::planning_adapter::core::NormalizedRoadCorridor corridor;
    corridor.source_timestamp_ns = 1000000000000ULL;
    for (int i = 0; i <= 100; ++i) {
        tap::planning_adapter::core::NormalizedCorridorPoint point;
        point.x = static_cast<double>(i);
        point.y = 0.0;
        point.heading = 0.0;
        point.s = static_cast<double>(i);
        point.lane_id = 1U;
        point.right_width = 3.5;
        point.left_width = 3.5;
        point.speed_limit = 15.0;
        point.right_boundary = tap::planning_adapter::core::
            NormalizedBoundaryType::kDashedLaneMarking;
        point.left_boundary = tap::planning_adapter::core::
            NormalizedBoundaryType::kDashedLaneMarking;
        corridor.points.push_back(point);
    }
    return corridor;
}

tap::planning_adapter::core::NormalizedPredictedObject MakeBlockingVehicle() {
    using namespace tap::planning_adapter::core;
    NormalizedPredictedObject object;
    object.source_timestamp_ns = 1000000000000ULL;
    object.id = "7";
    object.type = NormalizedObjectType::kVehicle;
    object.x = 18.0;
    object.y = 0.0;
    object.heading = 0.0;
    object.velocity_x = 1.0;
    object.length = 4.5;
    object.width = 2.0;
    object.contour = {{20.25, 1.0}, {15.75, 1.0}, {15.75, -1.0}, {20.25, -1.0}};

    NormalizedPredictedTrajectory prediction;
    prediction.index = 0;
    prediction.probability = 1.0;
    prediction.type = NormalizedPredictionType::kVehicle;
    for (int i = 0; i < 8; ++i) {
        NormalizedPredictedPoint point;
        point.x = 18.0 + 0.2 * static_cast<double>(i);
        point.y = 0.0;
        point.s = 0.2 * static_cast<double>(i);
        point.relative_time = 0.2 * static_cast<double>(i);
        point.speed = 1.0;
        prediction.points.push_back(point);
    }
    object.trajectories.push_back(std::move(prediction));
    return object;
}

tap::planning_adapter::core::NormalizedPredictedObject MakeDistantVehicle() {
    auto object = MakeBlockingVehicle();
    object.x = 35.0;
    object.y = 8.0;
    object.contour = {{37.25, 9.0}, {32.75, 9.0}, {32.75, 7.0},
                      {37.25, 7.0}};
    for (auto &point : object.trajectories.front().points) {
        point.x += 17.0;
        point.y += 8.0;
    }
    return object;
}

tap::planning_adapter::core::NormalizedPredictedObject MakeMultiBranchVehicle() {
    auto object = MakeDistantVehicle();
    auto second = object.trajectories.front();
    second.index = 1;
    second.probability = 0.35;
    for (auto &point : second.points) {
        point.y += 2.0;
    }
    object.trajectories.front().probability = 0.65;
    object.trajectories.push_back(std::move(second));
    return object;
}

}  // namespace

int main() {
    tap::planning_adapter::core::EmergencyPlanningRuntime runtime(
        {std::string(TAP_PLANNING_RUNTIME_CONFIG_DIR)});
    const auto init = runtime.Initialize();
    assert(init.ok());

    tap::planning_adapter::core::NormalizedEgoState ego;
    ego.source_timestamp_ns = 1000000000000ULL;
    ego.speed = 5.0;
    const auto result = runtime.Plan(ego, MakeCorridor(), {});
    assert(result.ok());
    assert(result->source_timestamp_ns == ego.source_timestamp_ns);
    assert(result->trajectory.size() >= 10U);
    for (std::size_t i = 1; i < result->trajectory.size(); ++i) {
        assert(std::isfinite(result->trajectory[i].x));
        assert(result->trajectory[i].relative_time >
               result->trajectory[i - 1].relative_time);
    }

    // The obstacle must enter both the spacetime manager and the Normal
    // planner-object view consumed by Interactive A*/DDP.  This is a smoke
    // test for the real object path, not a live replay or RSCL publication
    // test.
    const auto obstacle_result =
        runtime.Plan(ego, MakeCorridor(), {MakeBlockingVehicle()});
    if (!obstacle_result.ok()) {
        std::cerr << "ordinary obstacle failed: "
                  << obstacle_result.status().message() << std::endl;
    }
    assert(obstacle_result.ok());
    assert(obstacle_result->trajectory.size() >= 10U);
    assert(obstacle_result->emergency_target_id.empty());

    // The explicit LongSafe request activates the emergency path.  With a
    // sufficiently wide corridor the planner must generate a collision-free
    // avoidance trajectory for the selected target.
    tap::planning_adapter::core::EmergencyPlanningRequest request;
    request.enabled = true;
    request.target_id = "7";
    request.ttc_s = 2.5;
    const auto emergency_result =
        runtime.Plan(ego, MakeCorridor(), {MakeBlockingVehicle()}, request);
    if (!emergency_result.ok()) {
        std::cerr << "blocking emergency failed: "
                  << emergency_result.status().message() << std::endl;
    }
    assert(emergency_result.ok());
    assert(emergency_result->emergency_target_id == "7");

    const auto avoidable_result =
        runtime.Plan(ego, MakeCorridor(), {MakeDistantVehicle()}, request);
    if (!avoidable_result.ok()) {
        std::cerr << "avoidable emergency failed: "
                  << avoidable_result.status().message() << std::endl;
    }
    assert(avoidable_result.ok());
    assert(avoidable_result->emergency_target_id == "7");
    assert(std::abs(avoidable_result->emergency_target_ttc_s - 2.5) < 1e-9);
    assert(avoidable_result->emergency_prediction_branch_count == 1U);
    assert(!avoidable_result->initializer_trajectory.empty());

    // LongSafe selects an object ID, not one arbitrarily chosen Prediction
    // branch. Both branches for that ID must enter the same A*/DDP obstacle
    // set and be counted in the result metadata.
    const auto multi_branch_result =
        runtime.Plan(ego, MakeCorridor(), {MakeMultiBranchVehicle()}, request);
    assert(multi_branch_result.ok());
    assert(multi_branch_result->emergency_target_id == "7");
    assert(multi_branch_result->emergency_prediction_branch_count == 2U);

    request.ttc_s = 3.01;
    assert(!runtime.Plan(ego, MakeCorridor(), {MakeDistantVehicle()}, request)
                .ok());
    return 0;
}
