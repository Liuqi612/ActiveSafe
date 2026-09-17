

#include "initializer/multi_traj_selector.h"

#include <algorithm>
#include <ostream>
#include <utility>

#include <float.h>

#include "async/parallel_for.h"
#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <absl/strings/str_format.h>
#include "common/log.h"

#include "common/lane_change_safety.h"
#include "maps/lane_path.h"
#include "maps/lane_point.h"
#include "math/frenet_frame.h"
#include "math/vec.h"
#include "util/status_macros.h"

namespace pnc_x {
namespace planning {
uint64_t gDangerLeftCounter = 0;
uint64_t gSafeLeftCounter = 0;
uint64_t gDangerRightCounter = 0;
uint64_t gSafeRightCounter = 0;

namespace {

absl::Status EvaluateSingleTrajectory(const SingleTrajInfo &traj_info,
                                      TrajEvalInfo *eval_info) {
    eval_info->eval_cost = traj_info.total_cost;
    return absl::OkStatus();
}

absl::Status EvaluateSingleTrajectoryAndCheckSafety(
    const ApolloTrajectoryPointProto &start_point,
    const SingleTrajInfo &traj_info,
    const FrenetFrame &target_frenet_frame,
    double speed_limit,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const VehicleGeometryParamsProto &vehicle_geom,
    LaneChangeStyle lc_style,
    const pnc_x::LaneChangeStage &lc_state,
    const pnc_x::LaneChangeStage &prev_lc_stage,
    absl::Duration path_look_ahead_duration,
    TrajEvalInfo *eval_info) {
    auto lc_safety_status = CheckLaneChangeSafety(
        start_point, traj_info.traj_points, target_frenet_frame, speed_limit,
        st_traj_mgr, vehicle_geom, lc_style, lc_state, prev_lc_stage,
        path_look_ahead_duration, eval_info, false);
    eval_info->eval_cost =
        lc_safety_status.ok() ? traj_info.total_cost : DBL_MAX;

    return lc_safety_status;
}

}  // namespace

SpeedResponseStyle MappingLongResponseLevel(LaneChangeStage prev_lc_stage,
                                            double follower_max_decel,
                                            double leader_max_decel,
                                            const std::string &prefix) {
    SpeedResponseStyle leader_level = SPEED_RESPONSE_NORMAL;
    static SpeedResponseStyle output_level = SPEED_RESPONSE_NORMAL;

    if (leader_max_decel == 0.0) {
        leader_level = SPEED_RESPONSE_NORMAL;
    } else if (leader_max_decel < 0.8) {
        leader_level = SPEED_RESPONSE_NORMAL;
    } else if (leader_max_decel < 2.0) {
        leader_level = SPEED_RESPONSE_FAST;
    } else {
        leader_level = SPEED_RESPONSE_RADICAL;
    }

    auto follower_level = SPEED_RESPONSE_NORMAL;
    if (follower_max_decel == 0.0) {
        follower_level = SPEED_RESPONSE_NORMAL;
    } else if (follower_max_decel < 0.3) {
        follower_level = SPEED_RESPONSE_NORMAL;
    } else if (follower_max_decel < 0.8) {
        follower_level = SPEED_RESPONSE_FAST;
    } else {
        follower_level = SPEED_RESPONSE_RADICAL;
    }

    auto res_level = std::max(leader_level, follower_level);

    if (prev_lc_stage == LaneChangeStage::LCS_EXECUTING) {
        output_level = std::max(res_level, output_level);
    } else {
        output_level = SPEED_RESPONSE_NORMAL;
    }

    return output_level;
}

absl::StatusOr<int> EvaluateMultiTrajs(
    const DrivePassage &drive_passage,
    const ApolloTrajectoryPointProto &start_point,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const std::vector<SingleTrajInfo> &multi_trajs,
    const VehicleGeometryParamsProto &vehicle_geom,
    bool eval_safety,
    LaneChangeStyle lc_style,
    const pnc_x::LaneChangeStage &lc_state,
    const pnc_x::LaneChangeStage &prev_lc_stage,
    absl::Duration path_look_ahead_duration,
    absl::flat_hash_set<std::string> *follower_set,
    absl::flat_hash_set<std::string> *leader_set,
    double *follower_max_decel,
    double *leader_max_decel,
    absl::flat_hash_set<std::string> *unsafe_object_ids,
    PlannerStatusProto::PlannerStatusCode *status_code,
    ThreadPool *thread_pool,
    int plan_id,
    bool is_borrow) {
    return 0;
}

}  // namespace planning
}  // namespace pnc_x
