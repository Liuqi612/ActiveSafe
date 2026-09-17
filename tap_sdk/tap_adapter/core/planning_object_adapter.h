// Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
//
// Normalized prediction objects are independent of RSCL/Cap'n Proto.  The
// Node message adapter decodes platform messages into this contract; this
// file only translates validated values into upstream Planning types.

#pragma once

#include <absl/status/statusor.h>

#include "object/spacetime_trajectory_manager.h"
#include "tap_adapter/core/planning_normalized_types.h"

namespace tap {
namespace planning_adapter {
namespace core {

// Validates the complete normalized object vector without constructing the
// upstream manager.  Node adapters use this only to apply upstream's
// per-object malformed-record filtering before the production call.
absl::Status ValidatePredictedObjects(
    const std::vector<NormalizedPredictedObject> &objects);

// A valid explicit empty object vector produces an empty manager.  Every
// non-empty object must include a valid base contour and at least one valid
// trajectory; this strict path does not synthesize object-only predictions.
absl::StatusOr<pnc_x::planning::SpacetimeTrajectoryManager>
BuildSpacetimeTrajectoryManager(
    const std::vector<NormalizedPredictedObject> &objects);

}  // namespace core
}  // namespace planning_adapter
}  // namespace tap
