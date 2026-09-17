
#pragma once

#include "async/thread_pool.h"
#include "initializer/initializer_input.h"
#include "initializer/initializer_output.h"
#include "initializer/interactive_search/common/common.h"
#include <absl/status/statusor.h>

namespace pnc_x {
namespace planning {

using LeadingTrajs = std::vector<std::string>;

absl::StatusOr<MotionSearchOutput> SearchForRawTrajectory(
    const MotionSearchInput &input, ThreadPool *thread_pool, int plan_id);

absl::StatusOr<MotionSearchOutput> DPSearch(
    const MotionSearchInput &input,
    ThreadPool *thread_pool,
    int plan_id,
    std::vector<LeadingTrajs> leading_traj_configs);

absl::StatusOr<MotionSearchOutput> InteractiveAStarSearch(
    const MotionSearchInput &input,
    ThreadPool *thread_pool,
    int plan_id,
    const std::vector<LeadingTrajs> &leading_traj_configs);

void RunInteractiveSearch(
    const MotionSearchInput &input,
    ThreadPool *thread_pool,
    int plan_id,
    const pnc_x::FrenetCoordinate &ego_sl,
    const std::vector<ObstacleDecisionGroup> &decision_groups,
    const ObsDecisionGap *pre_obs_gap,
    std::vector<std::vector<ApolloTrajectoryPointProto>> &coarse_trajectories,
    std::vector<int> &first_safe_to_gap_indexes,
    std::vector<bool> &start_node_safety,
    std::vector<int> &all_node_safety,
    std::vector<uint64_t> &goal_indices,
    int &pri_decision_group_index,
    std::vector<std::string> &infos,
    const std::vector<double> &thw,
    double tail_ttc);

absl::StatusOr<MotionSearchOutput> SearchFailOut(
    const DrivePassage &drive_passage,
    const FrenetCoordinate &ego_sl,
    const int plan_id,
    const MotionSearchInput &input,
    MotionSearchOutput &output);

}  // namespace planning
}  // namespace pnc_x
