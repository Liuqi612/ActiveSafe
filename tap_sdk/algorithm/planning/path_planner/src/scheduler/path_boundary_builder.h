
#pragma once

#include "common/path_sl_boundary.h"
#include "pncx_lane_change.pb.h"
#include "object/spacetime_trajectory_manager.h"
#include "router/drive_passage.h"
#include "scheduler/lane_evasion_status.h"
#include "scheduler/smooth_reference_line_result.h"
#include "pncx_trajectory_point.pb.h"
#include "pncx_vehicle.pb.h"
#include <absl/status/statusor.h>

namespace pnc_x {
namespace planning {

absl::StatusOr<PathSlBoundary> BuildPathBoundaryFromDrivePassage(
    const DrivePassage &drive_passage);

absl::StatusOr<PathSlBoundary> BuildPathBoundaryFromPose(
    const DrivePassage &drive_passage,
    const ApolloTrajectoryPointProto &plan_start_point,
    const LaneEvadeInfo &lane_evade_info,
    const VehicleGeometryParamsProto &vehicle_geom,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const LaneChangeStateProto &lc_state,
    const SmoothedReferenceLineResultMap &smooth_result_map,
    bool borrow_lane_boundary,
    bool should_smooth_next_left_turn,
    double *last_used_target_lane_offset,
    const boost::optional<double> ref_centered_compensation_offset,
    int is_force_lc,
    double force_lc_offset_ratio,
    bool is_ego_corner_across_lane_bound = false,
    const DrivePassage *lk_drive_passage = nullptr,
    bool is_limited_pause = false,
    bool adjust_astar_search_boundary_for_lc = false,
    bool is_uturn = false);

}  // namespace planning
}  // namespace pnc_x
