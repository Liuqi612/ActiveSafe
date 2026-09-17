#include <algorithm>
#include <chrono>
#include <cmath>
#include <memory>
#include <string>
#include <tuple>

#include <absl/container/inlined_vector.h>
#include <boost/heap/pairing_heap.hpp>

#include "common/gflags.h"
#include "common/vehicle_speed_config_helper.h"
#include "initializer/interactive_search/common/interactive_a_star_constant.h"
#include "initializer/interactive_search/search/a_star_search.h"
#include "common/log.h"

namespace pnc_x {
namespace planning {

namespace {
constexpr double kKmh2Ms = 3.6;
constexpr int kMaxTraceBackNum = 100;
constexpr int kMaxLogIteration = 12;
constexpr int kLeftAndRight = 2;
}  // namespace


std::pair<std::vector<double>, std::vector<double>> AStarSearch::yaw_rate_map_ =
    {{5.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 80.0, 100.0, 120.0, 150.0},
     {520.0, 520.0, 520.0, 260.0, 118.0, 90.0, 74.0, 59.0, 52.0, 48.0, 45.0}};

bool AStarSearch::ReachGoal(Node &current_node,
                            const ObstacleDecisionGroup &decision_group,
                            bool is_lane_change,
                            const InitializerConfig &initializer_params,
                            const Node &start_node) {
    bool reach_goal_l =
        std::fabs(current_node.L()) <
        initializer_params.interactive_astar_search_config().goal_l();
    bool reach_goal_heading = current_node.DiffHeading() < 10.0;
    bool reach_goal_s = current_node.S() > goal_s_;

    if (drive_passage_ == nullptr) {
        return false;
    }
    auto extendPredTraj = [](int pred_pt_index,
                             const std::vector<ObstaclePointInfo> &pred_traj,
                             double *cur_x, double *cur_y) {
        if ((cur_x == nullptr) || (cur_y == nullptr)) {
            return false;
        }
        if (pred_traj.size() < 2) {
            return false;
        }
        double obs_cur_x_front =
            pred_traj[pred_traj.size() - 2].traj_point.pos().x();
        double obs_cur_y_front =
            pred_traj[pred_traj.size() - 2].traj_point.pos().y();
        double obs_cur_x_back = pred_traj.back().traj_point.pos().x();
        double obs_cur_y_back = pred_traj.back().traj_point.pos().y();
        *cur_x = obs_cur_x_back + (pred_pt_index - pred_traj.size() + 1) *
                                      (obs_cur_x_back - obs_cur_x_front);
        *cur_y = obs_cur_y_back + (pred_pt_index - pred_traj.size() + 1) *
                                      (obs_cur_y_back - obs_cur_y_front);
        return true;
    };

    bool has_lead = decision_group.obs_goal_gap.lead_obj_id.has_value();
    bool has_tail = decision_group.obs_goal_gap.tail_obj_id.has_value();

    if (!has_lead && !has_tail) {
        reach_goal_s = current_node.S() > goal_s_;
    } else {
        bool reach_lead = true;
        bool reach_tail = true;
        int pred_pt_index =
            current_node.AccumulatedTime() / decision_group.traj_time_step;
        if (has_lead && is_lane_change) {
            auto it = decision_group.obstacles_decision.find(
                std::string(decision_group.obs_goal_gap.lead_obj_id.value()));
            if (it == decision_group.obstacles_decision.end()) {
                return false;
            }
            const auto &lead_obs = it->second;
            double lead_obs_min_s;
            double lead_obs_cur_s;
            if (pred_pt_index >= lead_obs.modified_pred_traj.size()) {
                double obs_cur_x;
                double obs_cur_y;
                if (!extendPredTraj(pred_pt_index, lead_obs.modified_pred_traj,
                                    &obs_cur_x, &obs_cur_y)) {
                    return false;
                }
                double lead_obs_cur_l;

                if (!QueryXY2SLmap(*drive_passage_, obs_cur_x, obs_cur_y,
                                   &lead_obs_min_s, &lead_obs_cur_l)) {
                    return false;
                }
            } else {
                lead_obs_min_s = lead_obs.modified_pred_traj[pred_pt_index]
                                     .sl_boundary.s_min;
                lead_obs_cur_s =
                    lead_obs.modified_pred_traj.front().sl_boundary.s_min;
            }
            double ego_max_s =
                current_node.S() + vehicle_params_->vehicle_geometry_params()
                                       .front_edge_to_center();

            const auto &is_leaving_target_table =
                safety_checker_->GetIsObstacleLeavingTargetTable();
            bool is_lead_left = false;
            constexpr double kRearLeadThresh = 10.0;
            bool is_rear_lead =
                (start_node.S() - lead_obs_cur_s) > kRearLeadThresh;
            if (is_leaving_target_table.find(lead_obs.obj_id) !=
                is_leaving_target_table.end()) {
                const double time_resolution =
                    initializer_params_.interactive_astar_search_config()
                        .time_resolution();
                const auto &is_obstacle_leaving_target_vec =
                    is_leaving_target_table.at(lead_obs.obj_id);
                const int flag_idx =
                    static_cast<int>(round(current_node.AccumulatedTime() /
                                           std::max(time_resolution, 1e-6)));
                if (flag_idx < is_obstacle_leaving_target_vec.size()) {
                    is_lead_left = is_obstacle_leaving_target_vec[flag_idx] &&
                                   !is_rear_lead;
                }
            }
            reach_lead = is_lead_left || (ego_max_s < lead_obs_min_s);
        }

        reach_goal_s = reach_goal_s && reach_lead;
    }
    bool reach_goal = reach_goal_l && reach_goal_s;

    return reach_goal;
}
double AStarSearch::GetYawRateLimit(const double v) {
    int lower_bound = 0;
    int left = 0;
    int right = AStarSearch::yaw_rate_map_.first.size() - 1;
    while (left < right) {
        int mid = (left + right + 1) >> 1;
        if (AStarSearch::yaw_rate_map_.first[mid] <= (v * kKmh2Ms)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    lower_bound = left;

    if (lower_bound == (AStarSearch::yaw_rate_map_.first.size() - 1)) {
        return (v * std::tan((yaw_rate_map_.second[lower_bound] / kSteerRatio) *
                             kAngle2Rad)) /
               vehicle_params_->vehicle_geometry_params().wheel_base();
    }
    if (lower_bound == 0) {
        return (v * std::tan((yaw_rate_map_.second[lower_bound] / kSteerRatio) *
                             kAngle2Rad)) /
               vehicle_params_->vehicle_geometry_params().wheel_base();
    }
    double v1 = AStarSearch::yaw_rate_map_.first[lower_bound];
    double v2 = AStarSearch::yaw_rate_map_.first[lower_bound + 1];
    double steer1 = AStarSearch::yaw_rate_map_.second[lower_bound];
    double steer2 = AStarSearch::yaw_rate_map_.second[lower_bound + 1];
    return (v * std::tan((steer1 + ((((v * kKmh2Ms) - v1) / (v2 - v1)) *
                                    (steer2 - steer1))) /
                         kSteerRatio * kAngle2Rad)) /
           vehicle_params_->vehicle_geometry_params().wheel_base();
}

double AStarSearch::GetSteerLimit(const double v) {
    auto v_it = std::lower_bound(yaw_rate_map_.first.begin(),
                                 yaw_rate_map_.first.end(), v * kKmh2Ms);
    int lower_bound = v_it - yaw_rate_map_.first.begin();

    if (lower_bound == AStarSearch::yaw_rate_map_.first.size()) {
        return yaw_rate_map_.second.back();
    }
    if ((lower_bound == 0) && ((v * kKmh2Ms) < yaw_rate_map_.first[lower_bound])) {
        return yaw_rate_map_.second[lower_bound];
    }
    double v2 = AStarSearch::yaw_rate_map_.first[lower_bound];
    double v1 = AStarSearch::yaw_rate_map_.first[lower_bound - 1];
    double steer2 = AStarSearch::yaw_rate_map_.second[lower_bound];
    double steer1 = AStarSearch::yaw_rate_map_.second[lower_bound - 1];
    return (steer1 + (((v * kKmh2Ms) - v1) / (v2 - v1) * (steer2 - steer1))) /
           kSteerRatio * kAngle2Rad;
}

uint64_t AStarSearch::Search(Node &start,
                             double goal_s,

                             std::unordered_map<uint64_t, Node> &nodes_map,
                             const ObstacleDecisionGroup &decision_group,
                             const std::string group_prefix,
                             const std::vector<double> &xy_range,
                             bool is_lane_change,
                             bool is_manual_lane_change,
                             std::vector<double> speed_limits,
                             const SpacetimeTrajectoryManager &st_traj_mgr,
                             bool is_pre_safe) {
    const auto &interactive_astar_config =
        initializer_params_.interactive_astar_search_config();
    // The search limit is small and known up front.  Reserve the node table
    // once so repeated successor insertions do not trigger bucket rehashes.
    const auto max_search_iteration =
        interactive_astar_config.max_search_iteration();
    if (max_search_iteration > 0) {
        nodes_map.reserve(nodes_map.size() +
                          static_cast<size_t>(max_search_iteration) + 1U);
    }
    const double max_decel_by_jerk =
        ads_x::planning::VehicleSpeedConfigHelper::GetMaxDecelJerk() *
        interactive_astar_config.time_resolution();
    constexpr double kMaxDeceleration = -3.5;
    goal_s_ = goal_s;

    uint64_t index_pred = 0UL;
    uint64_t index_succ = 0UL;
    double new_g_cost = 0.0;

    searchPriorityQueue open_queue;

    start.UpdateHCost(goal_s_, is_lane_change, is_manual_lane_change,
                      initializer_params_);
    start.UpdateTotalCost(
        initializer_params_.interactive_astar_search_config().h2g_ratio());
    start.SetOpen();
    start.SetStart();
    start.ResetUnclose();

    index_pred = start.SetIndex(initializer_params_, xy_range);
    open_queue.push(std::pair<uint64_t, double>(index_pred, start.TotalCost()));
    nodes_map[index_pred] = start;

    while (!open_queue.empty()) {
        const auto &node = open_queue.top();
        auto node_pred_it = nodes_map.find(node.first);
        if (node_pred_it == nodes_map.end()) {
            open_queue.pop();
            continue;
        }
        auto &node_pred = node_pred_it->second;

        index_pred = node_pred.Index();
        if (node_pred.IsClose()) {
            open_queue.pop();
            continue;
        }

        iterations_++;

        if (iterations_ > initializer_params_.interactive_astar_search_config()
                              .max_search_iteration()) {
            if (FLAGS_planner_print_search_info) {
                if (decision_group.obs_goal_gap.lead_obj_id.has_value()) {
                    search_info_ +=
                        "lead: " +
                        decision_group.obs_goal_gap.lead_obj_id.value();
                }
                if (decision_group.obs_goal_gap.tail_obj_id.has_value()) {
                    search_info_ +=
                        ".  tail: " +
                        decision_group.obs_goal_gap.tail_obj_id.value();
                }
                absl::StrAppend(&search_info_,
                                absl::StrCat("\nSearch Fail: reached max iter, "
                                             "tracing back... iterations: ",
                                             iterations_, "\n"));

                TraceBack(index_pred, nodes_map, search_info_);
            }
            absl::StrAppend(
                &search_fail_reason_,
                absl::StrCat("reached max iter, tracing back... iterations: ",
                             iterations_, "\n"));
            return 0;
        }

        // node_pred already refers to the entry found above; avoid a second
        // hash lookup through unordered_map::operator[].
        if (node_pred.IsOpen()) {
            node_pred.SetClose();

            open_queue.pop();

            if (ReachGoal(node_pred, decision_group, is_lane_change,
                          initializer_params_, start)) {
                if (FLAGS_planner_print_search_info) {
                    if (decision_group.obs_goal_gap.lead_obj_id.has_value()) {
                        absl::StrAppend(
                            &search_info_,
                            absl::StrCat("lead: ", decision_group.obs_goal_gap
                                                       .lead_obj_id.value()));
                    }
                    if (decision_group.obs_goal_gap.tail_obj_id.has_value()) {
                        absl::StrAppend(
                            &search_info_,
                            absl::StrCat("tail: ", decision_group.obs_goal_gap
                                                       .tail_obj_id.value()));
                    }
                    absl::StrAppend(&search_info_,
                                    absl::StrCat("\nReached goal, iteration: ",
                                                 iterations_, "\n"));
                }
                TraceBack(index_pred, nodes_map, search_info_);
                return index_pred;
            }

            double yaw_rate_limit = GetYawRateLimit(node_pred.V());

            double sample_num =
                std::max(initializer_params_.interactive_astar_search_config()
                             .sample_num(),
                         1);
            double max_acceleration =
                ads_x::planning::VehicleSpeedConfigHelper::GetMaxAcceleration();
            double max_deceleration = std::max(
                ads_x::planning::VehicleSpeedConfigHelper::GetMaxDeceleration(),
                std::max(kMaxDeceleration,
                         node_pred.Acc() + max_decel_by_jerk));
            double acc_sample_interval =
                (max_acceleration - max_deceleration) / sample_num;
            double omega_sample_interval = (yaw_rate_limit * 2.0) / sample_num;
            absl::InlinedVector<double, 8> acc_smaple;
            acc_smaple.reserve(static_cast<int>(sample_num) + 1);
            acc_smaple.emplace_back(0.0);
            for (int i = 0; i < sample_num; ++i) {
                double acc = max_deceleration +
                             (static_cast<double>(i) * acc_sample_interval);
                acc_smaple.emplace_back(acc);
            }
            absl::InlinedVector<double, 8> omega_sample;
            omega_sample.reserve(static_cast<int>(sample_num));

            if (std::fabs(yaw_rate_limit) < kEpsilon) {
                omega_sample.emplace_back(yaw_rate_limit);

            } else {
                for (int j = 0; j < sample_num; ++j) {
                    double omega = yaw_rate_limit - (static_cast<double>(j) *
                                                     omega_sample_interval);
                    omega_sample.emplace_back(omega);
                }
            }

            for (auto acc : acc_smaple) {
                for (auto omega : omega_sample) {
                    if (drive_passage_ == nullptr) {
                        continue;
                    }
                    std::unique_ptr<Node> node_succ =
                        node_pred.CreateSuccessor(
                            nodes_map, omega, acc, speed_limits,
                            safety_checker_, vehicle_params_,
                            initializer_params_, *drive_passage_,
                            is_lane_change, sl_boundary_, group_prefix,
                            is_pre_safe);
                    if (node_succ == nullptr) {
                        continue;
                    }

                    if (FLAGS_planner_search_fail_level >= 1) {
                        if (is_lane_change) {
                            std::vector<double> xs, ys;
                            xs.push_back(node_succ->X());
                            ys.push_back(node_succ->Y());
                        } else {
                        }
                    }

                    index_succ =
                        node_succ->SetIndex(initializer_params_, xy_range);

                    auto successor_it = nodes_map.find(index_succ);
                    const bool successor_is_new =
                        successor_it == nodes_map.end();
                    if (successor_is_new || !successor_it->second.IsClose() ||
                        (index_pred == index_succ)) {
                        if (drive_passage_ == nullptr) {
                            continue;
                        }
                        node_succ->UpdateGCost(
                            *drive_passage_, yaw_rate_limit,
                            node_pred.GCost(),
                            is_lane_change, is_manual_lane_change,
                            initializer_params_, vehicle_params_,
                            decision_group, obs_behavior_map_);
                        new_g_cost = node_succ->GCost();

                        if (successor_is_new ||
                            (new_g_cost < successor_it->second.GCost()) ||
                            (index_pred == index_succ)) {
                            node_succ->UpdateHCost(goal_s_, is_lane_change,
                                                   is_manual_lane_change,
                                                   initializer_params_);
                            node_succ->UpdateTotalCost(
                                initializer_params_
                                    .interactive_astar_search_config()
                                    .h2g_ratio());

                            if ((index_pred == index_succ) &&
                                (node_succ->TotalCost() >
                                    (node_pred.TotalCost() + 1e-6))) {
                                continue;
                            } else if ((index_pred == index_succ) &&
                                       (node_succ->TotalCost() <=
                                           (node_pred.TotalCost() + 1e-6))) {
                                if (!node_pred.IsStart()) {
                                    node_succ->SetPredecessor(
                                        node_pred.Predecessor());
                                }
                            }
                            node_succ->SetOpen();
                            const double successor_total_cost =
                                node_succ->TotalCost();
                            if (successor_is_new) {
                                nodes_map.emplace(index_succ,
                                                   std::move(*node_succ));
                            } else {
                                successor_it->second = std::move(*node_succ);
                            }

                            open_queue.emplace(std::pair<uint64_t, double>(
                                index_succ, successor_total_cost));
                        }
                    }
                }
            }

        } else {
            search_info_ += "any cases other than not close & not open?";
        }
    }

    if (open_queue.empty()) {
        if (FLAGS_planner_print_search_info) {
            if (decision_group.obs_goal_gap.lead_obj_id.has_value()) {
                search_info_ +=
                    "lead: " + decision_group.obs_goal_gap.lead_obj_id.value();
            }
            if (decision_group.obs_goal_gap.tail_obj_id.has_value()) {
                search_info_ += ".  tail: " +
                                decision_group.obs_goal_gap.tail_obj_id.value();
            }
            search_info_ += "\nopen set empty, no solution \n";
            TraceBack(index_pred, nodes_map, search_info_);
        }
        search_fail_reason_ += "open set empty, no solution \n";
        return 0UL;
    }

    search_info_ += "unreasonable situation cause search failure";
    return 0UL;
}

void AStarSearch::TraceBack(uint64_t result_index,
                            std::unordered_map<uint64_t, Node> &nodes_map,
                            std::string &search_info_) {
    int i = 0;
    uint64_t node_index = result_index;
    while (!nodes_map[node_index].IsStart()) {
        i++;
        const auto &node = nodes_map[node_index];
        node_list_.emplace_back(node);
        node_index = node.Predecessor();
        if (i > kMaxTraceBackNum) {
            search_info_ += "traceback cannot find start node, force exit!\n";
            break;
        }
    }
    const auto &node = nodes_map[node_index];
    node_list_.emplace_back(node);

    if (FLAGS_planner_print_search_info) {
        for (const auto &node : node_list_) {
            search_info_ += node.ToString();
        }
    }
}

bool AStarSearch::GetCoarseTrajectory(
    std::vector<ApolloTrajectoryPointProto> &planning_trajectory,
    int *first_safe_to_gap_index,
    bool start_node_safety,
    bool is_pre_safe,
    int *all_node_safety,
    std::string *infos) {
    constexpr double kLooseSafetyCheck = 0.2;
    double safety_dist = is_pre_safe ? kLooseSafetyCheck : 1e-6;
    if (node_list_.empty()) {
        return false;
    } else {
        std::reverse(node_list_.begin(), node_list_.end());
    }
    planning_trajectory.clear();
    planning_trajectory.reserve(node_list_.size());
    bool has_find_safe_gap = false;
    *all_node_safety = 1;
    for (size_t i = 0; i < node_list_.size(); i++) {
        if (node_list_[i].SafetyCheckInfo() != " ") {
            *infos += node_list_[i].SafetyCheckInfo();
        }
        if (!has_find_safe_gap &&
            (node_list_[i].EgoToSafetyDis() < safety_dist)) {
            if (((0 == i) && start_node_safety) || (i != 0)) {
                *first_safe_to_gap_index = i;
                has_find_safe_gap = true;
            }
        }
        if ((*all_node_safety == 1) &&
            (node_list_[i].EgoToSafetyDis() >= safety_dist)) {
            *all_node_safety = 0;
        }

        ApolloTrajectoryPointProto tmp;
        tmp.set_relative_time(node_list_[i].AccumulatedTime());

        tmp.mutable_path_point()->set_x(node_list_[i].X());
        tmp.mutable_path_point()->set_y(node_list_[i].Y());
        tmp.mutable_path_point()->set_theta(node_list_[i].Theta());
        tmp.set_v(node_list_[i].V());
        tmp.set_a(node_list_[i].Acc());

        tmp.mutable_path_point()->set_s(node_list_[i].S());

        planning_trajectory.emplace_back(tmp);
    }
    return true;
}

}  // namespace planning
}  // namespace pnc_x
