
#pragma once

#include <vector>

#include "pncx_alc.pb.h"
#include <absl/status/status.h>
#include <absl/status/statusor.h>

#include "pncx_autonomy_state.pb.h"
#include "common/path_sl_boundary.h"

#include "router/drive_passage.h"

#include "pncx_trajectory_point.pb.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

absl::StatusOr<bool> CrossedBoundary(const DrivePassage &dp,
                                     const Vec2d &ego_pos);

absl::StatusOr<bool> HasTrajectoryCrossedSolidBoundary(
    const DrivePassage &drive_passage,
    const PathSlBoundary &sl_boundary,
    const std::vector<ApolloTrajectoryPointProto> &traj_pts,
    const VehicleGeometryParamsProto &vehicle_geom,
    bool lc_pause);

absl::StatusOr<bool> HasForePartTrajectoryCrossedSolidBoundary(
    const DrivePassage &drive_passage,
    const PathSlBoundary &sl_boundary,
    const std::vector<ApolloTrajectoryPointProto> &traj_pts,
    const VehicleGeometryParamsProto &vehicle_geom,
    double ego_v_kph,
    bool lc_left);

absl::StatusOr<ALCState> UpdateAlcState(ALCState state,
                                        const Vec2d &preview_pos,
                                        const Vec2d &ego_pos,
                                        double ego_heading,
                                        const DrivePassage &drive_passage);

void ReportPlcEventSignal(ALCState old_state,
                          ALCState new_state,
                          DriverAction::LaneChangeCommand lc_cmd);

}  // namespace planning
}  // namespace pnc_x
