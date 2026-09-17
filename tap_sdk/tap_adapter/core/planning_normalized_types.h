// Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
//
// Lightweight data contract shared by the Node message adapter and the
// Planning runtime bridge. This header intentionally contains no protobuf,
// Cap'n Proto, Boost, or Planning implementation headers.

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace tap {
namespace planning_adapter {
namespace core {

// Positions use the Planning local Cartesian frame. Lengths are metres,
// angles are radians, and speed/acceleration use SI units.
struct NormalizedPoint2d {
    double x = 0.0;
    double y = 0.0;
};

struct NormalizedEgoState {
    uint64_t source_timestamp_ns = 0;
    double x = 0.0;
    double y = 0.0;
    double heading = 0.0;
    double speed = 0.0;
    double acceleration = 0.0;
    double curvature = 0.0;
};

enum class NormalizedBoundaryType : uint8_t {
    kUnknown = 0,
    kDashedLaneMarking,
    kSolidLaneMarking,
    kCurb,
    kVirtual,
};

struct NormalizedCorridorPoint {
    double x = 0.0;
    double y = 0.0;
    double heading = 0.0;
    double s = 0.0;
    uint64_t lane_id = 0;
    double right_width = 0.0;
    double left_width = 0.0;
    double speed_limit = 0.0;
    NormalizedBoundaryType right_boundary = NormalizedBoundaryType::kVirtual;
    NormalizedBoundaryType left_boundary = NormalizedBoundaryType::kVirtual;
};

struct NormalizedRoadCorridor {
    std::vector<NormalizedCorridorPoint> points;
    uint64_t source_timestamp_ns = 0;
};

enum class NormalizedObjectType : uint8_t {
    kUnknownStatic = 0,
    kUnknownMovable,
    kVehicle,
    kLargeVehicle,
    kPedestrian,
    kCyclist,
    kCone,
    kBarrier,
};

enum class NormalizedPredictionType : uint8_t {
    kStationary = 0,
    kVehicle,
    kPedestrian,
    kCyclist,
    kUnknown,
};

struct NormalizedPredictedPoint {
    double x = 0.0;
    double y = 0.0;
    double s = 0.0;
    double heading = 0.0;
    double curvature = 0.0;
    double relative_time = 0.0;
    double speed = 0.0;
    double acceleration = 0.0;
};

struct NormalizedPredictedTrajectory {
    int index = 0;
    double probability = 0.0;
    NormalizedPredictionType type = NormalizedPredictionType::kUnknown;
    std::vector<NormalizedPredictedPoint> points;
};

struct NormalizedPredictedObject {
    uint64_t source_timestamp_ns = 0;
    std::string id;
    NormalizedObjectType type = NormalizedObjectType::kUnknownStatic;
    double x = 0.0;
    double y = 0.0;
    double heading = 0.0;
    double yaw_rate = 0.0;
    double velocity_x = 0.0;
    double velocity_y = 0.0;
    double acceleration_x = 0.0;
    double acceleration_y = 0.0;
    double length = 0.0;
    double width = 0.0;
    std::vector<NormalizedPoint2d> contour;
    std::vector<NormalizedPredictedTrajectory> trajectories;
};

}  // namespace core
}  // namespace planning_adapter
}  // namespace tap
