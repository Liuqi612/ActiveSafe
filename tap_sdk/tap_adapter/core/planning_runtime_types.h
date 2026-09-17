// Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
//
// Runtime configuration and output DTOs.  Node may include this header
// without importing Planning protobuf, Boost, or algorithm implementation
// types.

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace tap {
namespace planning_adapter {
namespace core {

struct EmergencyPlanningRuntimeConfig {
    // Directory containing the reviewed emergency Planning text-proto bundle.
    std::string parameter_directory;
    // LongSafe TTC threshold for entering the emergency Planning path.
    double emergency_ttc_threshold_s = 3.0;
    // Extra clearance used by the explicit LongSafe target guard.  This does
    // not alter upstream A*/DDP costs; it prevents near-touching boxes from
    // being reported as a safe emergency maneuver.
    double emergency_safety_margin_m = 0.20;
    // Baseline clearance applied to every Prediction branch, including
    // non-LongSafe objects.
    double object_safety_margin_m = 0.0;
};

// This is the normalized contract crossing from Node/LongSafe into Planning.
// The target geometry and all future motion still come from Prediction; these
// fields only carry the risk decision and its provenance.
struct EmergencyPlanningRequest {
    bool enabled = false;
    std::string target_id;
    double ttc_s = 0.0;
    uint8_t target_status = 0U;
    std::string trigger_reason;
};

struct NormalizedTrajectoryPoint {
    double x = 0.0;
    double y = 0.0;
    double s = 0.0;
    double heading = 0.0;
    double curvature = 0.0;
    double relative_time = 0.0;
    double speed = 0.0;
    double acceleration = 0.0;
    double jerk = 0.0;
    double steer_angle = 0.0;
};

struct EmergencyPlanningResult {
    uint64_t source_timestamp_ns = 0;
    // Non-empty only when the LongSafe-selected fusion ID was present in the
    // normalized Prediction snapshot consumed by this successful plan.
    std::string emergency_target_id;
    double emergency_target_ttc_s = 0.0;
    // LongSafe selects an object ID; all Prediction branches for that ID are
    // consumed by the same A*/DDP obstacle set.  Keep the count observable
    // without changing the RSCL trajectory protocol.
    std::size_t emergency_prediction_branch_count = 0U;
    // Retained for SIL/debug verification. The published trajectory remains
    // the validated DDP result below.
    std::vector<NormalizedTrajectoryPoint> initializer_trajectory;
    std::vector<NormalizedTrajectoryPoint> trajectory;
};

}  // namespace core
}  // namespace planning_adapter
}  // namespace tap
