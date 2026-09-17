
#include "initializer/interactive_search/decision_extractor/gap_decision.h"
#include "initializer/motion_search_util.h"
#include "math/geometry/util.h"
#include "util/status_macros.h"

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
    bool is_ego_cener_across_bound,
    std::vector<ApolloTrajectoryPointProto> *traj_result,
    boost::optional<int> &first_safe_to_gap_index_out) {
    std::string best_gap_info = " ";
    absl::StrAppend(&best_gap_info,
                    absl::StrCat("pri group:  ", pri_index, "\n"));
    auto gap_result =
        StabilizeGapResult(pri_index, decision_groups, pre_obs_gap,
                           goal_indices, all_node_safety, is_lane_change);
    absl::StrAppend(
        &best_gap_info,
        absl::StrCat(
            "select group:  ", gap_result.selected_index,
            ", lead: ", gap_result.lead_obj_id.value_or("null"),
            ", tail: ", gap_result.tail_obj_id.value_or("null"),
            ", ori lead: ", gap_result.ori_lead_obj_id.value_or("null"), "\n"));

    const size_t selected_idx = static_cast<size_t>(gap_result.selected_index);
    const auto &traj = coarse_trajectories[selected_idx];
    std::vector<double> xs, ys;
    xs.reserve(traj.size());
    ys.reserve(traj.size());
    for (const auto &point : traj) {
        xs.push_back(point.path_point().x());
        ys.push_back(point.path_point().y());
    }

    ASSIGN_OR_RETURN(
        *traj_result,
        ConstructTrajResult(coarse_trajectories[selected_idx],
                            kTrajectoryTimeStep, kMinCoarseTrajectorySize));
    FindMergeIndex(drive_passage, is_lane_change, *traj_result,
                   first_safe_to_gap_indexes, &gap_result,
                   first_safe_to_gap_index_out);

    bool cur_merge_safe = (all_node_safety[selected_idx] == 1);
    StabilizeMergeSafe(pre_obs_gap, cur_merge_safe, is_pre_lane_change,
                       is_ego_cener_across_bound, &gap_result);

    if (is_lane_change) {
        absl::StrAppend(
            &best_gap_info,
            absl::StrCat("\n", safety_check_info[selected_idx],
                         "merge idx : ", first_safe_to_gap_index_out.value(),
                         ", merge safe: ", gap_result.is_merge_safe.first));
    }
    return gap_result;
}

void FindMergeIndex(
    const DrivePassage &drive_passage,
    bool is_lane_change,
    const std::vector<ApolloTrajectoryPointProto> &selected_traj,
    const std::vector<int> &first_safe_to_gap_indexes,
    ObsDecisionGap *best_gap,
    boost::optional<int> &first_safe_to_gap_index_out) {
    first_safe_to_gap_index_out =
        5 * first_safe_to_gap_indexes[static_cast<size_t>(best_gap->selected_index)];
    if (is_lane_change) {
        for (int i = 0; i < selected_traj.size(); i++) {
            ASSIGN_OR_CONTINUE(
                const auto cur_sl,
                drive_passage.QueryFrenetCoordinateAt(
                    Vec2dFromApolloTrajectoryPointProto(selected_traj[i])));
            const auto boundaries =
                drive_passage.QueryEnclosingLaneBoundariesAtS(cur_sl.s);
            if ((cur_sl.l < boundaries.left->lat_offset) &&
                (cur_sl.l > boundaries.right->lat_offset)) {
                first_safe_to_gap_index_out = i;
                break;
            }
        }
    }
}

void StabilizeMergeSafe(const ObsDecisionGap *pre_obs_gap,
                        bool cur_merge_safe,
                        bool is_pre_lane_change,
                        bool is_ego_center_across_bound,
                        ObsDecisionGap *best_gap) {
    std::pair<bool, int> res = {false, 0};
    std::pair<bool, int> not_safe_res = {false, 0};
    constexpr int kMaxCounter = 10;
    if (is_pre_lane_change && is_ego_center_across_bound) {
        res.first = true;
        res.second = kMaxCounter;
        best_gap->is_merge_safe = res;
        best_gap->is_merge_not_safe = not_safe_res;
        return;
    }
    if (pre_obs_gap == nullptr) {
        best_gap->is_merge_safe = res;
        best_gap->is_merge_not_safe = not_safe_res;
        return;
    }
    const bool gap_match =
        (pre_obs_gap->lead_obj_id.has_value() &&
         best_gap->lead_obj_id == pre_obs_gap->lead_obj_id) ||
        (pre_obs_gap->tail_obj_id.has_value() &&
         best_gap->tail_obj_id == pre_obs_gap->tail_obj_id) ||
        (!pre_obs_gap->lead_obj_id.has_value() &&
         !best_gap->lead_obj_id.has_value()) ||
        (!pre_obs_gap->tail_obj_id.has_value() &&
         !best_gap->tail_obj_id.has_value());
    if (!gap_match) {
        best_gap->is_merge_safe = res;
        best_gap->is_merge_not_safe = not_safe_res;
        return;
    }
    constexpr int kStabilizeCounter = 3;
    if (cur_merge_safe) {
        res.second =
            std::min(pre_obs_gap->is_merge_safe.second + 1, kMaxCounter);
    }
    if (res.second >= kStabilizeCounter) {
        res.first = true;
    }
    if (!cur_merge_safe && is_pre_lane_change &&
        pre_obs_gap->is_merge_safe.first &&
        (pre_obs_gap->is_merge_safe.second > kStabilizeCounter)) {
        not_safe_res.second =
            std::min(pre_obs_gap->is_merge_not_safe.second + 1, kMaxCounter);
        if (not_safe_res.second <= kStabilizeCounter) {
            res.first = true;
            res.second =
                std::min(pre_obs_gap->is_merge_safe.second + 1, kMaxCounter);
        }
    }
    best_gap->is_merge_safe = res;
    best_gap->is_merge_not_safe = not_safe_res;
}

void AddLeadingTrajs(
    const ObsDecisionGap &best_gap_result,
    bool is_lane_change,
    const std::vector<LeadingGroup> &leading_groups,
    const std::vector<std::vector<std::string>> &insertion_orders,
    int plan_id,
    std::map<std::string, ConstraintProto::LeadingObjectProto> *leading_trajs) {
    if (best_gap_result.lead_obj_id.has_value() &&
        (!is_lane_change || best_gap_result.is_merge_safe.first)) {
        for (size_t i = 0; i < leading_groups.size(); ++i) {
            if (insertion_orders[i].empty() || leading_groups[i].empty() ||
                (insertion_orders[i].size() != leading_groups[i].size())) {
                continue;
            }
            const std::string &trajectory_id = insertion_orders[i].front();
            if (!leading_groups[i].count(trajectory_id)) {
                continue;
            }
            if (best_gap_result.lead_obj_id.value() !=
                SpacetimeObjectTrajectory::GetObjectIdFromTrajectoryId(
                    trajectory_id)) {
                continue;
            }

            for (size_t idx = i; idx < insertion_orders.size(); ++idx) {
                for (const auto &traj_id : insertion_orders[idx]) {
                    if (!leading_groups[idx].count(traj_id)) {
                        continue;
                    }
                    const auto &leading_object_proto =
                        leading_groups[idx].at(traj_id);
                    if (!leading_object_proto.traj_id().empty()) {
                        leading_trajs->emplace(leading_object_proto.traj_id(),
                                               leading_object_proto);
                    }
                }
            }
        }
    }
}

}  // namespace planning
}  // namespace pnc_x
