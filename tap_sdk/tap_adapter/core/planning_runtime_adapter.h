// Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
//
// Small runtime-facing facade. Planning implementation types are deliberately
// hidden in the .cc file so Node callbacks remain independent of Boost and
// generated Planning protobuf headers.

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <absl/status/status.h>
#include <absl/status/statusor.h>

#include "tap_adapter/core/planning_normalized_types.h"
#include "tap_adapter/core/planning_runtime_types.h"

namespace tap {
namespace planning_adapter {
namespace core {

// Materializes and validates the normalized native inputs used by the
// emergency core. This gate is useful for Node diagnostics; production
// planning then enters EmergencyPlanningRuntime::Plan below.
absl::Status ValidatePlanningCoreInputs(
    const NormalizedEgoState &ego,
    const NormalizedRoadCorridor &corridor,
    const std::vector<NormalizedPredictedObject> &objects);

// Stateful emergency planner owned by tap_adapter.  The implementation retains
// only algorithm state required across frames; Node supplies coherent,
// normalized snapshots and receives a lightweight validated trajectory.
class EmergencyPlanningRuntime {
 public:
    explicit EmergencyPlanningRuntime(EmergencyPlanningRuntimeConfig config);
    ~EmergencyPlanningRuntime();

    EmergencyPlanningRuntime(const EmergencyPlanningRuntime &) = delete;
    EmergencyPlanningRuntime &operator=(const EmergencyPlanningRuntime &) = delete;
    EmergencyPlanningRuntime(EmergencyPlanningRuntime &&) noexcept;
    EmergencyPlanningRuntime &operator=(EmergencyPlanningRuntime &&) noexcept;

    absl::Status Initialize();

    // Runs the product emergency chain: Interactive A* -> DDP -> validator.
    // Every failure is returned to Node; no synthetic map/object/trajectory
    // fallback is created at this boundary.
    absl::StatusOr<EmergencyPlanningResult> Plan(
        const NormalizedEgoState &ego,
        const NormalizedRoadCorridor &corridor,
        const std::vector<NormalizedPredictedObject> &objects,
        const EmergencyPlanningRequest &emergency_request =
            EmergencyPlanningRequest{});

    // Compatibility entry point for callers that only provide a target ID.
    absl::StatusOr<EmergencyPlanningResult> Plan(
        const NormalizedEgoState &ego,
        const NormalizedRoadCorridor &corridor,
        const std::vector<NormalizedPredictedObject> &objects,
        const std::string &emergency_target_id);

 private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

}  // namespace core
}  // namespace planning_adapter
}  // namespace tap
