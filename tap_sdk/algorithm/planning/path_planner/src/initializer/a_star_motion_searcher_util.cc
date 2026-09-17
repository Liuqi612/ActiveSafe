#include <algorithm>
#include <array>
#include <limits>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/gflags.h"
#include "initializer/a_star_motion_searcher_defs.h"
#include "initializer/a_star_motion_searcher_util.h"
#include "initializer/cost_provider.h"
#include "initializer/motion_search_types.h"
#include "initializer/geometry/geometry_form.h"
#include "initializer/geometry/geometry_graph.h"
#include "initializer/geometry/geometry_state.h"
#include "initializer/motion_form.h"
#include "initializer/motion_graph.h"
#include "initializer/motion_search_types.h"
#include "initializer/motion_search_util.h"
#include "initializer/motion_state.h"
#include "math/frenet_common.h"
#include "math/util.h"
#include "object/spacetime_object_state.h"
#include "object/spacetime_object_trajectory.h"
#include "object/spacetime_trajectory_manager.h"
#include "plan/planner_defs.h"
#include "plan/planner_flags.h"
#include "pncx_planner_params.pb.h"
#include "pncx_trajectory_point.pb.h"
#include "util/loop_guard.h"
#include <absl/algorithm/container.h>
#include <absl/container/flat_hash_set.h>
#include <absl/hash/hash.h>
#include <absl/status/statusor.h>
#include <absl/types/span.h>

namespace pnc_x {
namespace planning {

void ConstructTrajFromLastIndex(
    const absl::flat_hash_map<uint64_t, AStarSearchNode> &nodes_map,
    uint64_t goal_index,
    std::vector<ApolloTrajectoryPointProto> &traj_points) {
    std::vector<const MotionForm *> motions;
    uint64_t node_index = goal_index;
    AD_LINFO(PP) << "--------- ConstructTrajFromLastIndex ---------";

    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while ((node_index != 1UL) && loop_guard) {
        AD_LINFO(PP) << "node_index: " << node_index;
        const auto &node = nodes_map.at(node_index);
        motions.emplace_back(node.motion_form);
        node_index = node.pred_index;
    }

    std::reverse(motions.begin(), motions.end());
    if (motions.empty()) {
        AD_LINFO(PP) << "empty motions";
        return;
    } else {
        AD_LINFO(PP) << "size of motions: " << motions.size();
    }

    ResampleTrajectoryPoints(motions, traj_points);
}

bool ReachGoal(const GeometryGraph &geom_graph,
               AStarSearchNode &current_node,
               double goal_s,
               bool is_lane_change,
               const InitializerConfig &initializer_params,
               const InitializerSceneType init_scene_type) {
    const auto &space_node = geom_graph.GetNode(current_node.geom_node_idx);
    const auto &cur_action_state =
        current_node.motion_form->GetEndMotionState();

    bool reach_lateral_goal = std::fabs(cur_action_state.l) <
                              initializer_params.astar_search_config().goal_l();
    bool reach_stational_goal =
        (space_node.accumulated_s > (goal_s - 1e-6)) ||
        (std::fabs(space_node.accumulated_s - goal_s) < (5.0 * 1e-6));

    bool reach_goal = (init_scene_type == InitializerSceneType::INIT_SCENE_BORROW)
                          ? reach_stational_goal
                          : (reach_stational_goal && reach_lateral_goal);

    return reach_goal;
}

void ComputeHCost(AStarSearchNode *ptr_search_node,
                  const GeometryGraph &geom_graph,
                  double heurstic_s,
                  double h2g_ratio,
                  bool is_lane_change,
                  const InitializerConfig &initializer_params,
                  const InitializerSceneType init_scene_type) {
    const auto &space_node = geom_graph.GetNode(ptr_search_node->geom_node_idx);
    double diff_l = std::fabs(space_node.lateral_offset);
    double diff_s = (space_node.accumulated_s > heurstic_s)
                        ? 0.0
                        : heurstic_s - space_node.accumulated_s;
    double goal_t =
        initializer_params.astar_search_config().goal_time_upper_bound();
    double cur_t =
        ptr_search_node->is_start ? 0.0 : ptr_search_node->accumulated_t;
    double diff_t = (cur_t < goal_t) ? (goal_t - cur_t) : 0.0;

    if (init_scene_type == InitializerSceneType::INIT_SCENE_BORROW) {
        ptr_search_node->h_cost = h2g_ratio * std::fabs(diff_s);
    } else if (init_scene_type == InitializerSceneType::INIT_SCENE_FOLLOW) {
        ptr_search_node->h_cost =
            h2g_ratio *
            std::sqrt(std::pow(diff_s, 2) + (100.0 * std::pow(diff_l, 2)));
    } else {
        ptr_search_node->h_cost =
            h2g_ratio * std::sqrt(std::pow(diff_s, 2) + std::pow(diff_t, 2));
    }
}

void ComputeGCost(const CostProvider &cost_provider,
                  AStarSearchNode *ptr_search_node) {
    ptr_search_node->feature_costs.resize(cost_provider.weights().size());
    ptr_search_node->ignored_trajs = cost_provider.ComputeInteractiveCost(
        ptr_search_node->motion_form->GetEndMotionState().t,
        ptr_search_node->motion_form, ptr_search_node->ignored_trajs,
        absl::MakeSpan(ptr_search_node->feature_costs));
    ComputeDpLeadingObjCost(cost_provider, ptr_search_node);
}

void ComputeDpLeadingObjCost(const CostProvider &cost_provider,
                             AStarSearchNode *ptr_search_node) {
    const auto &cur_action_state =
        ptr_search_node->motion_form->GetEndMotionState();
    cost_provider.ComputeDpLeadingObjCost(
        cur_action_state.t, ptr_search_node->motion_form,
        absl::MakeSpan(ptr_search_node->feature_costs));
}

void SampleDynamicActions(
    const MotionState &init_action_state,
    const AStarSearchNode &pred_search_node,
    const GeometryEdge &geom_edge,
    const GeometryGraph &geom_graph,
    const IgnoreTrajMap &ignored_trajs,
    const MotionConstraintParamsProto &motion_constraint_params,
    const InitializerConfig &initializer_params,
    const CostProvider &cost_provider,
    bool sample_const_v,
    double heurstic_s,
    const InitializerSceneType init_scene_type,
    double h2g_ratio,
    bool is_lane_change,
    std::vector<std::unique_ptr<MotionForm>> &motion_forms,
    std::vector<AStarSearchNode> &succ_search_nodes,
    uint64_t *node_index) {
    const auto &pred_action_state =
        pred_search_node.is_start
            ? init_action_state
            : pred_search_node.motion_form->GetEndMotionState();

    const double v0 = pred_action_state.v;
    const double t0 = pred_action_state.t;

    absl::flat_hash_set<MotionEdgeKey> unrepeated_keys;
    const auto expand_action_by_a = [&unrepeated_keys, &geom_edge, t0](
                                        double v0, double a0) {
        unrepeated_keys.emplace(MotionEdgeKey(a0, v0, t0, geom_edge.index));
    };

    XCHECK_GE(v0, 0.0);
    const double a_max = motion_constraint_params.max_acceleration();
    const double a_min = motion_constraint_params.max_deceleration();
    XCHECK_LT(a_min, 0.0);
    XCHECK_GT(a_max, 0.0);
    const double v_limit =
        Mph2Mps(motion_constraint_params.default_speed_limit());
    const double reciprocal_s = 1.0 / geom_edge.geometry->length();
    const double pos_a_limit = (Sqr(v_limit) - Sqr(v0)) * reciprocal_s * 0.5;
    const double stop_a = -Sqr(v0) * reciprocal_s * 0.5;

    double a_lower = std::max(a_min, stop_a);
    double a_upper = std::min(pos_a_limit, a_max);
    std::set<double> acc_samples;
    if (!sample_const_v) {
        if (FLAGS_planner_initializer_enable_clip) {
            const double a0 = pred_action_state.a;
            constexpr double kAccVariationRange = 1.0;
            a_lower = std::max(a_lower, a0 - kAccVariationRange);
            a_upper = std::min(a_upper, a0 + kAccVariationRange);
        }
        const auto a_begin =
            std::lower_bound(kAccelerationSamplePoints.begin(),
                             kAccelerationSamplePoints.end(), a_lower);
        const auto a_end =
            std::lower_bound(a_begin, kAccelerationSamplePoints.end(), a_upper);

        for (auto it = a_begin; it != a_end; ++it) {
            acc_samples.insert(*it);
        }
    }
    acc_samples.insert(a_lower);
    acc_samples.insert(a_upper);
    acc_samples.insert(a_min);
    acc_samples.insert(0.0);
    for (const double acc : acc_samples) {
        expand_action_by_a(v0, acc);
    }

    std::vector<MotionEdgeKey> keys;
    keys.reserve(unrepeated_keys.size());
    for (auto &key : unrepeated_keys) {
        keys.push_back(key);
    }
    succ_search_nodes.reserve(keys.size());
    for (int i = 0; i < keys.size(); ++i) {
        const auto &key = keys[i];
        motion_forms.emplace_back(std::make_unique<ConstAccelMotion>(
            key.v0(), key.a0(), geom_edge.geometry));

        double accumulated_t = pred_search_node.accumulated_t +
                               motion_forms.back()->GetEndMotionState().t;
        succ_search_nodes.emplace_back(
            AStarSearchNode({.accumulated_t = accumulated_t,

                             .pred_index = pred_search_node.index,
                             .geom_node_idx = geom_edge.end,
                             .motion_form = motion_forms.back().get(),
                             .geom_edge_idx = geom_edge.index,
                             .ignored_trajs = ignored_trajs}));
        auto index = succ_search_nodes.size() - 1;
        succ_search_nodes[index].SetIndex(geom_graph, initializer_params);
        ComputeGCost(cost_provider, &succ_search_nodes[index]);
        succ_search_nodes[index].g_cost = absl::c_accumulate(
            succ_search_nodes[index].feature_costs, pred_search_node.g_cost);
        succ_search_nodes[index].feature_costs =
            AddCost(succ_search_nodes[index].feature_costs,
                    pred_search_node.feature_costs),
        ComputeHCost(&succ_search_nodes[index], geom_graph, heurstic_s,
                     h2g_ratio, is_lane_change, initializer_params,
                     init_scene_type);
        succ_search_nodes[index].total_cost =
            succ_search_nodes[index].g_cost + succ_search_nodes[index].h_cost;
    }
}

void CreateSuccessorNodes(
    const MotionState &init_action_state,
    const AStarSearchNode &pred_search_node,
    const CostProvider &cost_provider,
    const GeometryGraph &geom_graph,
    const MotionConstraintParamsProto &motion_constraint_params,
    const InitializerConfig &initializer_params,
    double heurstic_s,
    const InitializerSceneType init_scene_type,
    double h2g_ratio,
    bool is_lane_change,
    std::vector<std::unique_ptr<MotionForm>> &motion_forms,
    std::vector<AStarSearchNode> &candidate_nodes,
    uint64_t *node_index) {
    const auto &outgoing_edge_idxs =
        geom_graph.GetOutgoingEdges(pred_search_node.geom_node_idx);
    candidate_nodes.reserve((kAccelerationSamplePoints.size() + 3) *
                            outgoing_edge_idxs.size());
    for (const auto &outgoing_edge_idx : outgoing_edge_idxs) {
        const auto &geom_edge = geom_graph.GetEdge(outgoing_edge_idx);
        if (!geom_graph.IsActive(outgoing_edge_idx)) {
            continue;
        }

        SampleDynamicActions(
            init_action_state, pred_search_node, geom_edge, geom_graph, {},
            motion_constraint_params, initializer_params, cost_provider, false,
            heurstic_s, init_scene_type, h2g_ratio, is_lane_change,
            motion_forms, candidate_nodes, node_index);
    }
}

void CheckAndInsertOpenQueue(
    const AStarSearchNode &node_pred,
    std::vector<AStarSearchNode> &candidate_nodes,
    absl::flat_hash_map<uint64_t, AStarSearchNode> &nodes_map,
    priorityQueue &open_queue,
    std::vector<SptDebugNode> *spt_search_tree) {
    for (auto &candidate_node : candidate_nodes) {
        const auto succ_index = candidate_node.index;

        if (nodes_map.find(succ_index) != nodes_map.end()) {
            if (candidate_node.g_cost > nodes_map[succ_index].g_cost) {
                continue;
            } else if (candidate_node.pred_index == candidate_node.index &&
                       candidate_node.g_cost <= node_pred.g_cost) {
                if (!node_pred.is_start) {
                    candidate_node.pred_index = node_pred.pred_index;
                }
            }
        }

        candidate_node.open = true;

        nodes_map[succ_index] = std::move(candidate_node);

        open_queue.emplace(std::pair<uint64_t, double>(
            succ_index, nodes_map[succ_index].total_cost));

        if (FLAGS_planner_dumping_astar_search_process) {
            AddSearchTreeDebugMsg(nodes_map[succ_index], spt_search_tree);
        }
    }
}

void AddSearchTreeDebugMsg(const AStarSearchNode &candidate_node,
                           std::vector<SptDebugNode> *spt_search_tree) {
    SptDebugNode debug_node;
    debug_node.index_ = static_cast<int>(candidate_node.index);
    debug_node.prev_index_ = static_cast<int>(candidate_node.pred_index);
    const auto &action_state = candidate_node.motion_form->GetEndMotionState();
    debug_node.x_ = action_state.xy.x();
    debug_node.y_ = action_state.xy.y();
    debug_node.heading_ = action_state.h;
    debug_node.v_ = action_state.v;
    debug_node.omega_ = action_state.v * action_state.k;
    debug_node.s_ = action_state.s;
    debug_node.l_ = action_state.l;
    debug_node.a_ = action_state.a;
    debug_node.t_ = action_state.t;
    debug_node.kappa_ = action_state.k;
    spt_search_tree->push_back(debug_node);
}

}  // namespace planning
}  // namespace pnc_x
