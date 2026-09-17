// Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
//
// The core adapter is the only layer allowed to translate normalized TAP
// planning data into the upstream Planning value types.  RSCL/Cap'n Proto
// readers stay in the Node message adapter and the algorithms stay in the
// Planning core.

#pragma once

#include <absl/status/statusor.h>

#include "common/path_sl_boundary.h"
#include "pncx_trajectory_point.pb.h"
#include "router/drive_passage.h"
#include "tap_adapter/core/planning_normalized_types.h"

namespace tap {
namespace planning_adapter {
namespace core {

struct PlanningGeometry {
    pnc_x::ApolloTrajectoryPointProto start_point;
    pnc_x::planning::DrivePassage drive_passage;
    pnc_x::planning::PathSlBoundary path_boundary;
};

// Convert a validated normalized ego state to the proto consumed by both the
// Initializer and DDP.  No frame transform or extrapolation is performed.
absl::StatusOr<pnc_x::ApolloTrajectoryPointProto> ToApolloTrajectoryPoint(
    const NormalizedEgoState &ego);

// Build the upstream DrivePassage representation.  Validation is strict:
// invalid geometry, non-monotonic s, non-positive lane IDs, lane-sequence
// re-entry (A->B->A), and non-positive widths are rejected rather than being
// silently repaired.
absl::StatusOr<pnc_x::planning::DrivePassage> BuildDrivePassage(
    const NormalizedRoadCorridor &corridor);

// Build the standard PathSlBoundary used by the Normal Initializer.  This
// invokes the upstream boundary builder after DrivePassage construction; it
// does not implement a second boundary algorithm in TAP.
absl::StatusOr<pnc_x::planning::PathSlBoundary> BuildPathSlBoundary(
    const NormalizedRoadCorridor &corridor);

// Atomically creates the three geometry inputs used by the Normal chain and
// verifies that the ego centre projects inside the supplied corridor.  This
// is the preferred production entry point after message normalization.
absl::StatusOr<PlanningGeometry> BuildPlanningGeometry(
    const NormalizedEgoState &ego, const NormalizedRoadCorridor &corridor);

}  // namespace core
}  // namespace planning_adapter
}  // namespace tap
