#pragma once

#include <unordered_map>
#include <vector>

#include "decision/leading_groups_builder.h"
#include "initializer/interactive_search/decision_extractor/object_decision.h"

namespace pnc_x {
namespace planning {

absl::StatusOr<ObsDecisionGap> ComputeGapResult(
    int pri_index,
    const std::vector<ObstacleDecisionGroup> &decision_groups,
    const ObsDecisionGap *pre_obs_gap,
    const std::vector<uint64_t> &goal_indices,
    const std::vector<std::string> &safety_check_info,
    const std::vector<std::vector<ApolloTrajectoryPointProto>>
        &coarse_trajectories,
    const DrivePassage &drive_passage,
    bool is_lane_change,
    bool is_pre_lane_change,
    const std::vector<int> &first_safe_to_gap_indexes,
    const std::vector<bool> &start_node_safety,
    const std::vector<int> &all_node_safety,
    const int plan_id,
    bool is_ego_center_across_bound,
    std::vector<ApolloTrajectoryPointProto> *traj_result,
    boost::optional<int> &first_safe_to_gap_index_out);

void FindMergeIndex(
    const DrivePassage &drive_passage,
    bool is_lane_change,
    const std::vector<ApolloTrajectoryPointProto> &selected_traj,
    const std::vector<int> &first_safe_to_gap_indexes,
    ObsDecisionGap *best_gap,
    boost::optional<int> &first_safe_to_gap_index_out);

void StabilizeMergeSafe(const ObsDecisionGap *pre_obs_gap,
                        bool cur_merge_safe,
                        bool is_pre_lane_change,
                        bool is_ego_center_across_bound,
                        ObsDecisionGap *best_gap);

ObsDecisionGap GapSelectConsiderLaneChange(
    int pri_index,
    const std::vector<ObstacleDecisionGroup> &decision_groups,
    const ObsDecisionGap *pre_obs_gap,
    const std::vector<uint64_t> &goal_indices,
    const std::vector<int> &all_node_safety,
    const bool is_lane_change);

ObsDecisionGap StabilizeGapResult(
    int pri_index,
    const std::vector<ObstacleDecisionGroup> &decision_groups,
    const ObsDecisionGap *pre_obs_gap,
    const std::vector<uint64_t> &goal_indices,
    const std::vector<int> &all_node_safety,
    const bool is_lane_change);

void AddLeadingTrajs(
    const ObsDecisionGap &best_gap_result,
    bool is_lane_change,
    const std::vector<LeadingGroup> &leading_groups,
    const std::vector<std::vector<std::string>> &insertion_orders,
    int plan_id,
    std::map<std::string, ConstraintProto::LeadingObjectProto> *leading_trajs);

}  // namespace planning
}  // namespace pnc_x
