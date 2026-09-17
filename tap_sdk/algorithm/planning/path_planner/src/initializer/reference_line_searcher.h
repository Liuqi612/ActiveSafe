
#pragma once

#include <vector>

#include "async/thread_pool.h"
#include "common/path_sl_boundary.h"
#include "pncx_initializer.pb.h"
#include "initializer/geometry/geometry_graph.h"
#include "initializer/initializer_input.h"
#include "initializer/initializer_output.h"
#include "pncx_trajectory_point.pb.h"
#include <absl/status/status.h>
#include <absl/status/statusor.h>

namespace pnc_x {
namespace planning {

absl::StatusOr<ReferenceLineSearcherOutput> SearchReferenceLine(
    const ReferenceLineSearcherInput &input,
    InitializerDebugProto *debug_proto,
    ThreadPool *thread_pool);

absl::Status DeactivateFarGeometries(
    const ReferenceLineSearcherOutput &searcher_result,
    const PathSlBoundary &path_sl,
    GeometryGraph *mutable_geom_graph);

absl::Status DeactivateFarGeometries(
    const std::vector<ApolloTrajectoryPointProto> &traj_points,
    const PathSlBoundary &path_sl,
    GeometryGraph *mutable_geometry_graph);

void ParseReferenceLineResultToProto(const ReferenceLineSearcherOutput &result,
                                     GeometryGraphProto *debug_proto);
}  // namespace planning
}  // namespace pnc_x
