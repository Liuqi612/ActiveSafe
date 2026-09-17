
#pragma once

#include <map>
#include <string>
#include <vector>

#include "common/path_sl_boundary.h"
#include "pncx_constraint.pb.h"
#include "decision/leading_groups_builder.h"
#include "pncx_initializer.pb.h"
#include "initializer/interactive_search/common/common.h"
#include "math/frenet_common.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "pncx_planner_params.pb.h"
#include "router/drive_passage.h"
#include "pncx_vehicle.pb.h"
#include <absl/container/flat_hash_set.h>

namespace pnc_x {
namespace planning {

std::vector<SpeedPoint> GenerateConstAccelSpeedPoints(double init_v,
                                                      double init_s,
                                                      double init_t,
                                                      double accel,
                                                      double step_time,
                                                      double acc_time,
                                                      double duration);

std::vector<ObstaclePointInfo> TransferTrajectoryFromXY2SL(
    const DrivePassage &drive_passage, const SpacetimeObjectTrajectory &traj);

std::pair<bool, int> IsPreMergeSafe(
    const std::vector<LeadingGroup> &leading_groups,
    const std::vector<std::vector<std::string>> &insertion_orders,
    const ObsDecisionGap *pre_obs_gap);

std::vector<ObstacleDecisionGroup> ComputeDecisionGroup(
    const DrivePassage &drive_passage,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const std::vector<LeadingGroup> &leading_groups,
    const std::vector<std::vector<std::string>> &insertion_orders,
    const ApolloTrajectoryPointProto &start_point,
    const LaneChangeStateProto &lc_state,
    const std::string *current_path_leader_id,
    const FrenetBox *av_frenet_box,
    const ObsDecisionGap *pre_obs_gap,
    const InitializerConfig *initializer_params,
    const boost::optional<std::string> &nullable_nearest_vru_object_id,
    int plan_id,
    bool is_lane_change,
    bool is_pre_lane_change);

}  // namespace planning
}  // namespace pnc_x
