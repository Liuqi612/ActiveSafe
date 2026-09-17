#include "initializer/motion_searcher.h"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "async/parallel_for.h"
#include "common/gflags.h"
#include "common/timer.h"
#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>
#include <absl/status/status.h>
#include <absl/strings/str_format.h>
#include <absl/strings/str_join.h>
#include <absl/types/span.h>
#include "common/log.h"

#include "common/path_sl_boundary.h"
#include "pncx_constraint.pb.h"
#include "decision/decision_util.h"
#include "decision/leading_groups_builder.h"
#include "initializer/a_star_motion_searcher_defs.h"
#include "initializer/a_star_motion_searcher_util.h"
#include "initializer/collision_checker.h"
#include "initializer/cost_provider.h"
#if !TAP_PLANNING_EMERGENCY_ONLY
#include "initializer/dp_motion_searcher_defs.h"
#include "initializer/dp_motion_searcher_util.h"
#else
#include "initializer/motion_search_types.h"
#endif
#include "initializer/geometry/geometry_form_builder.h"
#include "initializer/geometry/geometry_graph.h"
#include "initializer/interactive_search/decision_extractor/object_decision.h"
#include "initializer/interactive_search/decision_groups_generator/compute_decision_group.h"
#include "initializer/interactive_search/search/goal_condition.h"
#include "initializer/motion_form.h"
#include "initializer/motion_graph.h"
#if !TAP_PLANNING_EMERGENCY_ONLY
#include "initializer/motion_graph_cache.h"
#include "initializer/ref_speed_table.h"
#endif
#include "initializer/motion_search_util.h"
#include "initializer/motion_state.h"
#include "initializer/multi_traj_selector.h"
#include "math/frenet_common.h"
#include "math/geometry/box2d.h"
#include "math/geometry/util.h"
#include "math/util.h"
#include "object/spacetime_object_state.h"
#include "object/spacetime_object_trajectory.h"
#include "object/spacetime_trajectory_manager.h"
#include "plan/planner_defs.h"
#include "plan/planner_flags.h"
#include "prediction/predicted_trajectory.h"
#include "common/log.h"

#include "common/constants.h"
#include "common/lane_change_safety.h"
#include "common/planning_macros.h"
#include "common/timer.h"
#include "initializer/interactive_search/decision_extractor/gap_decision.h"
#include "initializer/interactive_search/search/a_star_search.h"
#include "initializer/select_nudge_object.h"
#include "math/linear_interpolation.h"
#include "object/spacetime_object_state.h"
#include "object/spacetime_object_trajectory.h"
#include "object/spacetime_trajectory_manager.h"
#include "plan/planner_defs.h"
#include "plan/planner_flags.h"
#include "pncx_planner_params.pb.h"
#include "prediction/predicted_trajectory.h"
#include "router/drive_passage.h"
#include "pncx_trajectory_point.pb.h"
#include "util/loop_guard.h"
#include "util/status_macros.h"
#include "util/vehicle_geometry_util.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

namespace {

#if TAP_PLANNING_EMERGENCY_ONLY
double GetLeadingObjectsEndMinS(const SpacetimeTrajectoryManager &st_mgr,
                                const DrivePassage &drive_passage,
                                const std::vector<std::string> &leading_objs,
                                double ego_front_to_ra) {
    double min_s = std::numeric_limits<double>::max();
    for (const auto &lead_obj : leading_objs) {
        const auto obj_traj = st_mgr.FindTrajectoryById(lead_obj);
        if (obj_traj == nullptr || obj_traj->states().empty()) continue;
        const auto states = obj_traj->states();
        const auto fbox = obj_traj->is_stationary()
                              ? drive_passage.QueryFrenetBoxAt(states.front().box)
                              : drive_passage.QueryFrenetBoxAt(states.back().box);
        if (fbox.ok()) min_s = std::min(min_s, fbox->s_min);
    }
    return min_s - ego_front_to_ra;
}
#endif

std::vector<LeadingTrajs> BuildLeadingConfigs(
    const std::vector<LeadingGroup> &leading_groups,
    const ConstraintProto::LeadingObjectProto *blocking_static_traj) {
    std::vector<LeadingTrajs> leading_configs;
    leading_configs.reserve(leading_groups.size());
    for (const auto &leading_group : leading_groups) {
        leading_configs.emplace_back();
        auto &leading_trajs = *leading_configs.rbegin();
        for (const auto &pair : leading_group) {
            const auto &traj_id = pair.first;
            const auto &lead_obj = pair.second;
            leading_trajs.push_back(traj_id);
            if (lead_obj.is_group_tail() && leading_trajs.size() > 1) {
                std::swap(leading_trajs.front(), leading_trajs.back());
            }
        }
    }

    if (blocking_static_traj != nullptr) {
        for (auto &leading_config : leading_configs) {
            leading_config.push_back(blocking_static_traj->traj_id());
        }
    }

    return leading_configs;
}

void CheckEgoPosWithLane(const DrivePassage &drive_passage,
                         const VehicleGeometryParamsProto &vehicle_geo_params,
                         const FrenetCoordinate &ego_sl,
                         bool *ego_corner_across_lane_bound,
                         bool *ego_center_across_lane_bound) {
    double ego_s = ego_sl.s;
    double ego_l = ego_sl.l;
    float ego_max_l = ego_l + 0.5 * vehicle_geo_params.width();
    float ego_min_l = ego_l - 0.5 * vehicle_geo_params.width();

    auto boundary = drive_passage.QueryEnclosingLaneBoundariesAtS(ego_s);
    auto right_boundary = boundary.right;
    auto left_boundary = boundary.left;
    const double boundary_right_l =
        right_boundary.has_value()
            ? std::max(right_boundary->lat_offset, -kMaxHalfLaneWidth)
            : -kMaxHalfLaneWidth;
    const double boundary_left_l =
        left_boundary.has_value()
            ? std::min(left_boundary->lat_offset, kMaxHalfLaneWidth)
            : kMaxHalfLaneWidth;

    *ego_corner_across_lane_bound =
        ego_min_l < boundary_left_l && ego_max_l > boundary_right_l;
    *ego_center_across_lane_bound =
        ego_l < boundary_left_l && ego_l > boundary_right_l;
}

double InterpolateSafetyParams(
    const DrivePassage &drive_passage,
    const VehicleGeometryParamsProto &vehicle_geo_params,
    const FrenetCoordinate &ego_sl,
    bool ego_corner_across_lane_bound,
    double thw_max,
    double thw_min,
    bool is_ttc = false) {
    double thw = thw_max;
    if (!ego_corner_across_lane_bound && !is_ttc) {
        return thw;
    }

    const double vehicle_half_width = 0.5 * vehicle_geo_params.width();
    double ego_s = ego_sl.s;
    double ego_l = ego_sl.l;
    float ego_max_l = ego_l + vehicle_half_width;
    float ego_min_l = ego_l - vehicle_half_width;

    auto boundary = drive_passage.QueryEnclosingLaneBoundariesAtS(ego_s);
    auto right_boundary = boundary.right;
    auto left_boundary = boundary.left;
    const double boundary_right_l =
        right_boundary.has_value()
            ? std::max(right_boundary->lat_offset, -kMaxHalfLaneWidth)
            : -kMaxHalfLaneWidth;
    const double boundary_left_l =
        left_boundary.has_value()
            ? std::min(left_boundary->lat_offset, kMaxHalfLaneWidth)
            : kMaxHalfLaneWidth;

    const double left_threshold = is_ttc ? -vehicle_half_width : 0.0;
    double cross_distance = 0.0;
    if (ego_l > 0.0) {
        cross_distance = is_ttc ? boundary_left_l - ego_min_l
                                : std::abs(boundary_left_l - ego_min_l);
    } else {
        cross_distance = is_ttc ? ego_max_l - boundary_right_l
                                : std::abs(boundary_right_l - ego_max_l);
    }
    thw = ads_x::planning::math::lerp(thw_max, left_threshold, thw_min,
                                      vehicle_half_width, cross_distance);
    thw = boost::algorithm::clamp(thw, thw_min, thw_max);
    return thw;
}

#if !TAP_PLANNING_EMERGENCY_ONLY
void InsertMotionNodes(
    const std::vector<GeometryNodeIndex> &nodes_layer,
    const MotionNodeIndex &sdc_node_idx,
    const GeometryNodeVector<absl::flat_hash_map<DpMotionSample, DpMotionInfo>>
        &opt_motion_samples,
    MotionGraph *motion_graph,
    std::vector<MotionEdgeIndex> *terminated_edge_idxes,
    GeometryNodeVector<std::vector<MotionEdgeIndex>> *motions_to_expand,
    MotionEdgeVector<MotionSearchOutput::SearchCost> *search_costs,
    MotionEdgeVector<IgnoreTrajMap> *ignored_trajs_vec) {
    for (int i = 0, n = nodes_layer.size(); i < n; ++i) {
        const auto geom_node_idx = nodes_layer[static_cast<size_t>(i)];

        const auto &best_motions = opt_motion_samples[geom_node_idx];
        for (const auto &it : best_motions) {
            auto &dp_motion_info = it.second;
            MotionState end_motion_state =
                dp_motion_info.motion_form->GetEndMotionState();
            MotionEdgeIndex motion_edge_index;
            const auto prev_motion_edge_index =
                dp_motion_info.prev_motion_edge_index;
            if (prev_motion_edge_index == static_cast<MotionEdgeIndex>(-1)) {
                const auto end_node_index = motion_graph->AddMotionNode(
                    end_motion_state, geom_node_idx);
                motion_edge_index = motion_graph->AddMotionEdge(
                    sdc_node_idx, end_node_index, dp_motion_info.motion_form,
                    geom_node_idx, static_cast<MotionEdgeIndex>(-1));

                search_costs->push_back(MotionSearchOutput::SearchCost{
                    .feature_cost = dp_motion_info.costs,
                    .cost_to_come = dp_motion_info.sum_cost});
                ignored_trajs_vec->push_back(dp_motion_info.ignored_trajs);
            } else {
                const auto &prev_motion_edge =
                    motion_graph->GetMotionEdge(prev_motion_edge_index);
                end_motion_state.t +=
                    motion_graph->GetMotionNode(prev_motion_edge.end).state.t;
                const auto end_node_index = motion_graph->AddMotionNode(
                    end_motion_state, geom_node_idx);
                motion_edge_index = motion_graph->AddMotionEdge(
                    prev_motion_edge.end, end_node_index,
                    dp_motion_info.motion_form, geom_node_idx,
                    prev_motion_edge_index);

                const auto &prev_cost = (*search_costs)[prev_motion_edge_index];
                search_costs->push_back(MotionSearchOutput::SearchCost{
                    .feature_cost =
                        AddCost(dp_motion_info.costs, prev_cost.feature_cost),
                    .cost_to_come =
                        dp_motion_info.sum_cost + prev_cost.cost_to_come});
                ignored_trajs_vec->push_back(dp_motion_info.ignored_trajs);
            }

            if ((end_motion_state.v < 0.1) &&
                (end_motion_state.t < kActiveInitializerTrajectoryTimeHorizon)) {
                continue;
            }

            if (end_motion_state.t >= kActiveInitializerTrajectoryTimeHorizon) {
                terminated_edge_idxes->push_back(motion_edge_index);
            } else {
                (*motions_to_expand)[geom_node_idx].push_back(
                    motion_edge_index);
            }
        }
    }
}

int UpdateOptimalMotions(
    const MotionEdgeVector<MotionSearchOutput::SearchCost> &search_costs,
    const MotionGraphCache &cost_cache,
    std::vector<std::vector<DpMotionInfo>> candidate_motions,
    GeometryNodeVector<absl::flat_hash_map<DpMotionSample, DpMotionInfo>>
        *opt_motion_samples) {
    int motion_count = 0;
    for (auto &candidate_motions_per_node : candidate_motions) {
        motion_count += static_cast<int>(candidate_motions_per_node.size());

        for (auto &candidate_motion : candidate_motions_per_node) {
            const auto end_geometry_node_index =
                candidate_motion.end_geometry_node_index;

            auto &best_motion_so_far =
                (*opt_motion_samples)[end_geometry_node_index];
            ASSIGN_OR_CONTINUE(candidate_motion.motion_form,
                               cost_cache.GetMotionForm(candidate_motion.key));
            const auto end_state =
                candidate_motion.motion_form->GetEndMotionState();
            const DpMotionSample dp_motion_sample(end_state.v, end_state.t);
            if (best_motion_so_far.find(dp_motion_sample) ==
                best_motion_so_far.end()) {
                best_motion_so_far[dp_motion_sample] =
                    std::move(candidate_motion);
            } else {
                const auto &prev_best = best_motion_so_far[dp_motion_sample];
                auto prev_cost = prev_best.sum_cost;
                if (prev_best.prev_motion_edge_index !=
                    static_cast<MotionEdgeIndex>(-1)) {
                    prev_cost += search_costs[prev_best.prev_motion_edge_index]
                                     .cost_to_come;
                }
                auto cur_cost = candidate_motion.sum_cost;
                if (candidate_motion.prev_motion_edge_index !=
                    static_cast<MotionEdgeIndex>(-1)) {
                    cur_cost +=
                        search_costs[candidate_motion.prev_motion_edge_index]
                            .cost_to_come;
                }
                if (cur_cost < prev_cost) {
                    best_motion_so_far[dp_motion_sample] =
                        std::move(candidate_motion);
                }
            }
        }
    }
    return motion_count;
}

void FillTrajDebugInfo(
    const MotionGraph &motion_graph,
    const MotionEdgeVector<MotionSearchOutput::SearchCost> &search_costs,
    std::vector<MotionEdgeIndex> terminated_edge_idxes,
    SingleTrajDebugInfo *debug_info) {
    constexpr int kMaxTopTrajectoryNum = 50;
    const int k_top_traj_num = std::min(
        static_cast<int>(terminated_edge_idxes.size()), kMaxTopTrajectoryNum);
    const auto top_k_traj_info = TopKTrajectories(
        motion_graph, terminated_edge_idxes, search_costs, k_top_traj_num);

    auto &top_k_trajs = debug_info->top_k_trajs;
    top_k_trajs.reserve(top_k_traj_info.size());
    auto &top_k_total_costs = debug_info->top_k_total_costs;
    top_k_total_costs.reserve(top_k_traj_info.size());
    auto &top_k_edges = debug_info->top_k_edges;
    top_k_edges.reserve(top_k_traj_info.size());
    for (const auto &traj_info : top_k_traj_info) {
        top_k_total_costs.push_back(traj_info.total_cost);
        top_k_edges.push_back(traj_info.idx);
        top_k_trajs.push_back(
            ConstructTrajFromLastEdge(motion_graph, traj_info.idx));
    }
    debug_info->terminated_edge_idxes = std::move(terminated_edge_idxes);
}
BestEdgeInfo DPMainLoop(
    const MotionState &sdc_motion,
    const MotionNodeIndex &sdc_node_idx,
    const InitializerSceneType init_scene_type,
    int start_node_idx_on_first_layer,
    const GeometryGraph &geom_graph,
    const MotionConstraintParamsProto motion_constraint_params,
    MotionEdgeVector<MotionSearchOutput::SearchCost> &search_costs,
    MotionEdgeVector<IgnoreTrajMap> &ignored_trajs_vector,
    MotionGraphCache *cost_cache,
    ThreadPool *thread_pool,
    SingleTrajInfo &traj_output,
    std::vector<MotionEdgeIndex> &terminated_edge_idxes) {
    GeometryNodeVector<absl::flat_hash_map<DpMotionSample, DpMotionInfo>>
        opt_motion_samples;
    opt_motion_samples.resize(geom_graph.nodes().size());

    GeometryNodeVector<std::vector<MotionEdgeIndex>> motions_to_expand;
    motions_to_expand.resize(geom_graph.nodes().size());

    int motion_count = 0;
    const auto &nodes_layers = geom_graph.nodes_layers();
    for (int cur_layer_idx = 0, num_layer = nodes_layers.size();
         cur_layer_idx < num_layer; ++cur_layer_idx) {
        const auto &nodes_layer = nodes_layers[static_cast<size_t>(cur_layer_idx)];

        if (cur_layer_idx == num_layer - 1) break;

        if (cur_layer_idx != 0) {
            InsertMotionNodes(nodes_layer, sdc_node_idx, opt_motion_samples,
                              traj_output.motion_graph.get(),
                              &terminated_edge_idxes, &motions_to_expand,
                              &search_costs, &ignored_trajs_vector);
        }

        std::vector<std::vector<DpMotionInfo>> candidate_motions;
        candidate_motions.resize(nodes_layer.size());
        std::vector<std::vector<NewCacheInfo>> new_motion_forms_container;
        new_motion_forms_container.resize(nodes_layer.size());

        if (cur_layer_idx == 0) {
            candidate_motions[static_cast<size_t>(start_node_idx_on_first_layer)] =
                ExpandStartMotionEdges(
                    nodes_layer[static_cast<size_t>(start_node_idx_on_first_layer)], sdc_node_idx,
                    geom_graph, *(traj_output.motion_graph),
                    motion_constraint_params, *traj_output.cost_provider,
                    *cost_cache,
                    &new_motion_forms_container[static_cast<size_t>(start_node_idx_on_first_layer)],
                    thread_pool);
        } else {
            bool sample_const_v = false;
            if ((InitializerSceneType::INIT_SCENE_BORROW != init_scene_type) &&
                cur_layer_idx >= kConstVelSampleLayerSizeThreshold - 1) {
                sample_const_v = true;
            }
            ParallelFor(0, nodes_layer.size(), thread_pool, [&](int i) {
                const auto geom_node_idx = nodes_layer[i];
                const auto &motion_edge_idxs = motions_to_expand[geom_node_idx];
                auto &new_motion_forms = new_motion_forms_container[i];
                candidate_motions[i] = ExpandMotionEdges(
                    geom_node_idx, motion_edge_idxs, ignored_trajs_vector,
                    geom_graph, *(traj_output.motion_graph),
                    motion_constraint_params, *traj_output.cost_provider,
                    sample_const_v, *cost_cache, &new_motion_forms,
                    thread_pool);
            });
        }
        for (auto it =
                 std::make_move_iterator(new_motion_forms_container.begin());
             it != std::make_move_iterator(new_motion_forms_container.end());
             ++it) {
            cost_cache->BatchInsert(*it);
        }

        motion_count += UpdateOptimalMotions(search_costs, *cost_cache,
                                             std::move(candidate_motions),
                                             &opt_motion_samples);
    }

    // VLOG(2) << "Total evaluated motions of DP: " << motion_count;
    // VLOG(2) << "Collected motion edge cache size: " << cost_cache->size();

    return FindBestEdge(*traj_output.cost_provider, sdc_motion, sdc_node_idx,
                        nodes_layers[0][static_cast<size_t>(start_node_idx_on_first_layer)],
                        traj_output.motion_graph.get(), cost_cache,
                        &search_costs, &ignored_trajs_vector,
                        &terminated_edge_idxes);
}
#endif  // !TAP_PLANNING_EMERGENCY_ONLY

uint64_t AStarMainLoop(
    AStarSearchNode &start_node,
    MotionState init_action_state,
    double goal_s,
    double heurstic_s,
    const GeometryGraph &geom_graph,
    const MotionConstraintParamsProto motion_constraint_params,
    const InitializerConfig &initializer_params,
    bool is_lane_change,
    const InitializerSceneType init_scene_type,
    const int plan_id,

    absl::flat_hash_map<uint64_t, AStarSearchNode> &nodes_map,
    std::vector<std::unique_ptr<MotionForm>> &motion_forms,
    SingleTrajInfo &traj_output,
    std::vector<SptDebugNode> *spt_search_tree) {
    const auto &astar_config = initializer_params.astar_search_config();

    uint64_t node_index = static_cast<uint64_t>(astar_config.node_index());

    priorityQueue open_queue;

    start_node.is_start = true;
    start_node.total_cost = start_node.h_cost;
    start_node.open = true;
    start_node.close = false;
    start_node.index = 1;
    double h2g_ratio = 0.0;
    if (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type) {
        h2g_ratio = astar_config.h2g_ratio();
    } else if (InitializerSceneType::INIT_SCENE_FOLLOW == init_scene_type) {
        h2g_ratio = 1.0;
    } else {
        h2g_ratio = 2.0;
    }
    ComputeHCost(&start_node, geom_graph, heurstic_s, astar_config.h2g_ratio(),
                 is_lane_change, initializer_params, init_scene_type);

    uint64_t index_pred = start_node.index;
    uint64_t index_succ;

    open_queue.push(
        std::pair<uint64_t, double>(index_pred, start_node.total_cost));
    nodes_map[index_pred] = start_node;

    if (FLAGS_planner_dumping_astar_search_process) {
        SptDebugNode debug_start_node;
        debug_start_node.index_ = static_cast<int>(start_node.index);
        debug_start_node.prev_index_ = -1;
        debug_start_node.x_ = init_action_state.xy.x();
        debug_start_node.y_ = init_action_state.xy.y();
        debug_start_node.heading_ = init_action_state.h;
        debug_start_node.v_ = init_action_state.v;
        debug_start_node.omega_ = init_action_state.v * init_action_state.k;
        debug_start_node.s_ = init_action_state.s;
        debug_start_node.l_ = init_action_state.l;
        debug_start_node.a_ = init_action_state.a;
        debug_start_node.t_ = init_action_state.t;
        debug_start_node.kappa_ = init_action_state.k;
        spt_search_tree->push_back(debug_start_node);
    }

    int iterations = 0;
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (!open_queue.empty() && loop_guard) {
        const auto &node = open_queue.top();
        index_pred = node.first;
        auto &node_pred = nodes_map[index_pred];
        iterations++;

        const auto &space_node = geom_graph.GetNode(node_pred.geom_node_idx);

        if (iterations > astar_config.max_search_iteration()) {
            return 0;
        }

        if (nodes_map[index_pred].close) {
            open_queue.pop();
            continue;
        }

        if ((iterations != 1) &&
            ReachGoal(geom_graph, node_pred, goal_s, is_lane_change,
                      initializer_params, init_scene_type)) {
            return index_pred;
        }

        if (nodes_map[index_pred].open) {
            nodes_map[index_pred].close = true;
            open_queue.pop();

            std::vector<AStarSearchNode> candidate_nodes;
            CreateSuccessorNodes(
                init_action_state, node_pred, *traj_output.cost_provider,
                geom_graph, motion_constraint_params, initializer_params,
                heurstic_s, init_scene_type, h2g_ratio, is_lane_change,
                motion_forms, candidate_nodes, &node_index);
            CheckAndInsertOpenQueue(node_pred, candidate_nodes, nodes_map,
                                    open_queue, spt_search_tree);
        } else {
        }
    }

    if (open_queue.empty()) {
        return 0;
    }

    return 0;
}

void ResetGoalSForStaticObs(const SpacetimeTrajectoryManager &st_traj_mgr,
                            const GeometryGraph &geom_graph,
                            const double &geom_graph_max_s,
                            const DrivePassage &drive_passage,
                            const VehicleGeometryParamsProto &vehicle_geom,
                            const std::vector<std::string> &leading_objs,
                            double &goal_s) {
    double min_s = std::numeric_limits<double>::max();
    for (const auto &lead_obj : leading_objs) {
        const auto obj_traj = st_traj_mgr.FindTrajectoryById(lead_obj);
        if (obj_traj == nullptr) {
            continue;
        }
        if (!obj_traj->is_stationary()) continue;
        const auto states = obj_traj->states();
        const auto fbox = drive_passage.QueryFrenetBoxAt(states.front().box);
        if (!fbox.ok()) {
            continue;
        }
        min_s = std::min(min_s, fbox->s_min);
    }

    if (min_s > geom_graph_max_s) return;
    goal_s = std::max(
        min_s - vehicle_geom.length() - vehicle_geom.front_edge_to_center(),
        0.0);

    const auto &nodes_layers = geom_graph.nodes_layers();
    std::vector<double> layers_s;
    for (const auto &layer : nodes_layers) {
        if (layer.empty()) continue;

        layers_s.emplace_back(geom_graph.GetNode(layer[0]).accumulated_s);
    }

    std::sort(layers_s.begin(), layers_s.end());

    static constexpr double kEpsilon = 1e-6;
    for (int i = 1; i < layers_s.size(); ++i) {
        const double &layer_s = layers_s[static_cast<size_t>(i)];

        if ((goal_s < layer_s) &&
            ((std::abs(layer_s - min_s) < vehicle_geom.length()) ||
             (layer_s > min_s))) {
            goal_s = std::max(layers_s[static_cast<size_t>(i - 1)] - kEpsilon, 0.0);
            break;
        }
    }
}

absl::StatusOr<SingleTrajInfo> SearchForSingleTrajectory(
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_sl,
    const ApolloTrajectoryPointProto &start_point,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const LeadingTrajs &leading_trajs,
    const InitializerConfig &initializer_params,
    const MotionConstraintParamsProto &motion_constraint_params,
    const VehicleGeometryParamsProto &vehicle_geom,
    const GeometryGraph &geom_graph,
    const GeometryFormBuilder &form_builder,
    const CollisionChecker &collision_checker,

    const std::vector<double> &stop_s_on_drive_passage,
    const double passage_speed_limit,
    const InitializerSceneType init_scene_type,
    bool is_lane_change,
    bool is_manual_lane_change,
#if !TAP_PLANNING_EMERGENCY_ONLY
    MotionGraphCache *cost_cache,
#endif
    ThreadPool *thread_pool,
    const int plan_id,
    std::vector<SptDebugNode> *spt_search_tree) {
    const double geom_graph_max_s = geom_graph.GetMaxAccumulatedS();
    const double speed_max_s =
        (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type)
            ? std::fmax(
                  kMinSpeedForFinalCost * kActiveInitializerTrajectoryTimeHorizon,
                  start_point.v() > passage_speed_limit
                      ? start_point.v() * kActiveInitializerTrajectoryTimeHorizon
                      : (passage_speed_limit - start_point.v() >
                                 kActiveInitializerTrajectoryTimeHorizon
                             ? start_point.v() *
                                       kActiveInitializerTrajectoryTimeHorizon +
                                   0.5 * kActiveInitializerTrajectoryTimeHorizon *
                                       kActiveInitializerTrajectoryTimeHorizon
                             : 0.5 * (passage_speed_limit *
                                          passage_speed_limit -
                                      start_point.v() * start_point.v()) +
                                   passage_speed_limit *
                                       (kActiveInitializerTrajectoryTimeHorizon -
                                        passage_speed_limit + start_point.v())))
            : std::fmax(start_point.v(), kMinSpeedForFinalCost) *
                  kActiveInitializerTrajectoryTimeHorizon;

    Timer start_time;
    SingleTrajInfo traj_output;
    traj_output.leading_trajs = leading_trajs;
    traj_output.ref_speed_table = std::make_unique<RefSpeedTable>(
        st_traj_mgr, leading_trajs, drive_passage, stop_s_on_drive_passage);
    traj_output.motion_graph = std::make_unique<XYTMotionGraph>(&geom_graph);

    const double leading_obj_min_s =
        GetLeadingObjectsEndMinS(st_traj_mgr, drive_passage, leading_trajs,
                                 vehicle_geom.front_edge_to_center());
    const double max_accumulated_s =
        Min(leading_obj_min_s, geom_graph_max_s, speed_max_s);

    traj_output.cost_provider = std::make_unique<CostProvider>(
        drive_passage, initializer_params, motion_constraint_params,
        stop_s_on_drive_passage, st_traj_mgr, leading_trajs, vehicle_geom,
        &collision_checker, &path_sl, traj_output.ref_speed_table.get(),
        init_scene_type, is_lane_change, max_accumulated_s);

    std::vector<MotionEdgeIndex> terminated_edge_idxes;

#if !TAP_PLANNING_EMERGENCY_ONLY
    MotionEdgeVector<MotionSearchOutput::SearchCost> search_costs;
    MotionEdgeVector<IgnoreTrajMap> ignored_trajs_vector;
#endif

    const auto &nodes_layers = geom_graph.nodes_layers();
    int start_node_idx_on_first_layer = 0;
    MotionState sdc_motion =
        PrepareStartMotionNode(geom_graph, nodes_layers[0], start_point,
                               &start_node_idx_on_first_layer);
#if !TAP_PLANNING_EMERGENCY_ONLY
    const auto sdc_node_idx = traj_output.motion_graph->AddMotionNode(
        sdc_motion, nodes_layers[0][static_cast<size_t>(start_node_idx_on_first_layer)]);
#endif
    std::vector<ApolloTrajectoryPointProto> traj_points;
    if (FLAGS_pnc_x_use_astar_search_algorithm) {
        absl::flat_hash_map<uint64_t, AStarSearchNode> nodes_map;
        std::vector<std::unique_ptr<MotionForm>> motion_forms;

        AStarSearchNode start_search_node;
        start_search_node.feature_costs.resize(
            traj_output.cost_provider->cost_names().size(), 0.0);
        start_search_node.geom_node_idx =
            nodes_layers[0][static_cast<size_t>(start_node_idx_on_first_layer)];
        double ego_s =
            geom_graph.GetNode(start_search_node.geom_node_idx).accumulated_s;
        const auto &astar_search_config =
            initializer_params.astar_search_config();
        double lk_goal_s =
            ego_s +
            std::max(astar_search_config.min_dis(),
                     double(start_point.v()) * astar_search_config.goal_time());
        ResetGoalSForStaticObs(st_traj_mgr, geom_graph, geom_graph_max_s,
                               drive_passage, vehicle_geom, leading_trajs,
                               lk_goal_s);

        double graph_max_s = geom_graph.GetMaxAccumulatedS();

        double goal_s =
            init_scene_type == InitializerSceneType::INIT_SCENE_BORROW
                ? graph_max_s
                : std::min(lk_goal_s, graph_max_s);
        double heurstic_s = goal_s;

        uint64_t goal_index = AStarMainLoop(
            start_search_node, sdc_motion, goal_s, heurstic_s, geom_graph,
            motion_constraint_params, initializer_params, is_lane_change,
            init_scene_type, plan_id, nodes_map, motion_forms, traj_output,
            spt_search_tree);

        if (goal_index == 0) {
            return absl::NotFoundError("No trajectories found.");
        }
        traj_output.feature_costs = nodes_map[goal_index].feature_costs;
        traj_output.total_cost = nodes_map[goal_index].total_cost;

        ConstructTrajFromLastIndex(nodes_map, goal_index, traj_points);
        if (traj_points.empty()) {
            return absl::NotFoundError("No trajectories found.");
        }
    }
#if !TAP_PLANNING_EMERGENCY_ONLY
    else {
        BestEdgeInfo best_edge_info = DPMainLoop(
            sdc_motion, sdc_node_idx, init_scene_type,
            start_node_idx_on_first_layer, geom_graph, motion_constraint_params,
            search_costs, ignored_trajs_vector, cost_cache, thread_pool,
            traj_output, terminated_edge_idxes);
        const auto best_final_edge = best_edge_info.idx;
        if (best_final_edge == static_cast<MotionEdgeIndex>(-1)) {
            return absl::NotFoundError("No trajectories found.");
        }
        traj_output.last_edge_index = best_final_edge;
        traj_output.search_costs = search_costs;
        traj_output.total_cost = best_edge_info.total_cost;
        // VLOG(2) << "best_final_edge: " << best_final_edge.value()
        //         << " Total cost: " << traj_output.total_cost;

        traj_output.ignored_trajs =
            ignored_trajs_vector[traj_output.last_edge_index];
        traj_points = ConstructTrajFromLastEdge(*traj_output.motion_graph,
                                                traj_output.last_edge_index);
    }
#endif  // !TAP_PLANNING_EMERGENCY_ONLY

    ConstructTrajResult(&traj_points, kTrajectoryTimeStep,
                        kMinCoarseTrajectorySize);

    const auto &front_pt = traj_points.front();
    const auto &back_pt = traj_points.back();
    if ((front_pt.v() < kCanSetToZeroSpeed) && (back_pt.v() < kCanSetToZeroSpeed) &&
        (back_pt.path_point().s() - front_pt.path_point().s() <
            kCanSetToZeroTrajLength)) {
        traj_output.traj_points = ConstructStationaryTraj(sdc_motion);
    } else {
        traj_output.traj_points = std::move(traj_points);
    }
    NudgeInfos nudge_info;
    ObjectLongDecision lon_decision_info;
    ObjectDecisions object_decisions;
    std::vector<TrajectoryPoint> init_traj_points;
    TrajectoryPoint traj_point;
    for (const auto &point : traj_output.traj_points) {
        traj_point.FromProto(point);
        init_traj_points.emplace_back(traj_point);
    }
    std::string nudge_debug = "";
    const auto nudge_object_infos = initializer::SelectNudgeObjectId(
        static_cast<int>(traj_output.traj_points.size()), kTrajectoryTimeStep, is_lane_change,
        drive_passage, path_sl, init_traj_points, st_planner_object_traj,
        vehicle_geom, plan_id, &nudge_debug);
    if (nudge_object_infos.ok()) {
        nudge_info = nudge_object_infos.value();
    }
    traj_output.nudge_info = nudge_info;

    const auto objects_long_decision_out_or = ParseObjectLongDecisions(
        is_lane_change, drive_passage, init_traj_points, st_planner_object_traj,
        vehicle_geom);
    if (objects_long_decision_out_or.ok()) {
        lon_decision_info = objects_long_decision_out_or.value();
    }

    boost::optional<std::string> lead_obj_id = boost::none;
    boost::optional<std::string> tail_obj_id = boost::none;
    const auto object_decison_out_or =
        ParseObjectDecisions(st_planner_object_traj, nudge_info,
                             lon_decision_info, lead_obj_id, tail_obj_id);

    if (object_decison_out_or.ok()) {
        object_decisions = object_decison_out_or.value();
    }

    std::string infos;
    for (const auto &decision : object_decisions) {
        const auto &tag = decision.second.decision_tag;
        absl::StrAppend(&infos, "id: ", decision.first,
                        ", lat tag: ", static_cast<int>(tag.lat_decision_tag),
                        ", lon tag: ", static_cast<int>(tag.lon_decision_tag),
                        "\n");
    }

    traj_output.object_decisions = object_decisions;

#if !TAP_PLANNING_EMERGENCY_ONLY
    if (FLAGS_planner_initializer_debug_level >= 1 ||
        FLAGS_planner_dumping_initializer_features) {
        FillTrajDebugInfo(*traj_output.motion_graph, traj_output.search_costs,
                          std::move(terminated_edge_idxes),
                          &traj_output.debug_info);
    }
#endif

    return traj_output;
}

absl::Status CheckForImmediateCollision(
    const DrivePassage &drive_passage,
    const ApolloTrajectoryPointProto &plan_start_point,
    const VehicleGeometryParamsProto &vehicle_geom,
    const SpacetimeTrajectoryManager &st_traj_mgr) {
    const auto ego_box =
        ComputeAvBox(Vec2dFromApolloTrajectoryPointProto(plan_start_point),
                     plan_start_point.path_point().theta(), vehicle_geom);

    constexpr double kImmediateTimeThreshold = 0.3;
    for (const auto *traj_ptr : st_traj_mgr.moving_object_trajs()) {
        for (const auto &state : traj_ptr->states()) {
            if (state.traj_point->t() > kImmediateTimeThreshold) break;

            if (ego_box.HasOverlap(state.box)) {
                ASSIGN_OR_CONTINUE(
                    const auto obj_sl,
                    drive_passage.QueryFrenetCoordinateAt(state.box.center()));

                if (HasEnteredTargetLane(obj_sl.l, state.box.half_width())) {
                    return absl::CancelledError(absl::StrFormat(
                        "Trajectory %s will reach the ego vehicle\'s current "
                        "position at %.2f s",
                        traj_ptr->traj_id(), state.traj_point->t()));
                }
            }
        }
    }
    return absl::OkStatus();
}

}  // namespace

bool IsPreGapSafe(const ObsDecisionGap &obs_goal_gap,
                  const ObsDecisionGap *pre_obs_gap) {
    if (pre_obs_gap == nullptr) {
        return false;
    }
    bool is_target_gap =
        (obs_goal_gap.tail_obj_id.has_value() &&
         pre_obs_gap->tail_obj_id.has_value() &&
         obs_goal_gap.tail_obj_id.value() == pre_obs_gap->tail_obj_id.value());
    if (is_target_gap && pre_obs_gap->is_merge_safe.first) {
        return true;
    }
    return false;
}

ObsDecisionGap GapSelectConsiderLaneChange(
    int pri_index,
    const std::vector<ObstacleDecisionGroup> &decision_groups,
    const ObsDecisionGap *pre_obs_gap,
    const std::vector<uint64_t> &goal_indices,
    const std::vector<int> &all_node_safety,
    const bool is_lane_change) {
    ObsDecisionGap res_gap;
    auto cur_gap = decision_groups[static_cast<size_t>(pri_index)].obs_goal_gap;
    res_gap = cur_gap;
    res_gap.selected_index = pri_index;
    res_gap.counter = 1;
    if (!is_lane_change) return res_gap;

    if ((all_node_safety[pri_index] == 1) &&
        ((pre_obs_gap->lead_obj_id.has_value() &&
          cur_gap.lead_obj_id == pre_obs_gap->lead_obj_id) ||
         (pre_obs_gap->tail_obj_id.has_value() &&
          cur_gap.tail_obj_id == pre_obs_gap->tail_obj_id))) {
        res_gap = cur_gap;
        res_gap.selected_index = pri_index;
        res_gap.counter = 1;
        return res_gap;
    }

    for (int idx = 0; idx < decision_groups.size(); idx++) {
        if (idx == pri_index) continue;
        if (goal_indices[idx] == 0) continue;
        if ((all_node_safety[idx] == 1) &&
            ((pre_obs_gap->lead_obj_id.has_value() &&
              decision_groups[idx].obs_goal_gap.lead_obj_id ==
                  pre_obs_gap->lead_obj_id) ||
             (pre_obs_gap->tail_obj_id.has_value() &&
              decision_groups[idx].obs_goal_gap.tail_obj_id ==
                  pre_obs_gap->tail_obj_id))) {
            res_gap = decision_groups[static_cast<size_t>(idx)].obs_goal_gap;
            res_gap.selected_index = idx;
            res_gap.counter = 1;
            return res_gap;
        }
    }
    return res_gap;
}

ObsDecisionGap StabilizeGapResult(
    int pri_index,
    const std::vector<ObstacleDecisionGroup> &decision_groups,
    const ObsDecisionGap *pre_obs_gap,
    const std::vector<uint64_t> &goal_indices,
    const std::vector<int> &all_node_safety,
    const bool is_lane_change) {
    ObsDecisionGap res_gap;
    auto cur_gap = decision_groups[static_cast<size_t>(pri_index)].obs_goal_gap;
    cur_gap.ori_lead_obj_id = decision_groups[static_cast<size_t>(pri_index)].ori_lead_obj_id;
    if (pre_obs_gap == nullptr) {
        res_gap = cur_gap;
        res_gap.selected_index = pri_index;
        res_gap.counter = 1;
        return res_gap;
    }
    auto it = std::find_if(decision_groups.begin(), decision_groups.end(),
                           [pre_obs_gap](const ObstacleDecisionGroup &group) {
                               return group.obs_goal_gap == *pre_obs_gap;
                           });

    if (it == decision_groups.end()) {
        return GapSelectConsiderLaneChange(pri_index, decision_groups,
                                           pre_obs_gap, goal_indices,
                                           all_node_safety, is_lane_change);
    }

    int selected_index = std::distance(decision_groups.begin(), it);
    if (goal_indices[selected_index] == 0) {
        res_gap = cur_gap;
        res_gap.selected_index = pri_index;
        res_gap.counter = 1;
        return res_gap;
    }

    constexpr int kMaxCounter = 10;
    constexpr int kStabilizeCounter = 4;
    if (cur_gap != *pre_obs_gap) {
        if (pre_obs_gap->counter <= kStabilizeCounter) {
            res_gap = *pre_obs_gap;
            res_gap.selected_index = selected_index;
            res_gap.counter = std::min(pre_obs_gap->counter + 1, kMaxCounter);
        } else {
            res_gap = cur_gap;
            res_gap.selected_index = pri_index;
            res_gap.counter = 1;
        }
    } else {
        res_gap = cur_gap;
        res_gap.selected_index = pri_index;
        res_gap.counter = 1;
    }
    return res_gap;
}

absl::StatusOr<MotionSearchOutput> SearchFailOut(
    const DrivePassage &drive_passage,
    const FrenetCoordinate &ego_sl,
    const int plan_id,
    const MotionSearchInput &input,
    MotionSearchOutput &output) {
    const auto boundaries =
        drive_passage.QueryEnclosingLaneBoundariesAtS(ego_sl.s);
    bool is_ego_crossed_line = ego_sl.l < boundaries.left->lat_offset &&
                               ego_sl.l > boundaries.right->lat_offset;
    if (input.is_lane_change) {
        if (!is_ego_crossed_line ||
            input.prev_lc_stage == LaneChangeStage::LCS_PAUSE) {
            output.is_lc_pause = true;
            output.lc_status_code = PlannerStatusProto::LC_SAFETY_XCHECK_FAILED;
            return absl::StatusOr<MotionSearchOutput>(std::move(output));
        } else {
            return absl::NotFoundError("lc search fail.");
        }
    } else {
        return absl::NotFoundError("lk search fail.");
    }
}

#if !TAP_PLANNING_EMERGENCY_ONLY
absl::StatusOr<MotionSearchOutput> DPSearch(
    const MotionSearchInput &input,
    ThreadPool *thread_pool,
    int plan_id,
    std::vector<LeadingTrajs> leading_traj_configs) {
    const DrivePassage &drive_passage = *input.drive_passage;
    const ApolloTrajectoryPointProto &start_point = *input.start_point;
    const VehicleGeometryParamsProto &vehicle_geom =
        input.vehicle_params->vehicle_geometry_params();
    const GeometryGraph &geom_graph = *input.geom_graph;
    const std::vector<LeadingGroup> &leading_groups = *input.leading_groups;
    const std::vector<std::vector<std::string>> &insertion_orders =
        *input.insertion_orders;
    const SpacetimeTrajectoryManager &st_traj_mgr = *input.st_traj_mgr;
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj =
        *input.st_planner_object_traj;
    const LaneChangeStateProto &lc_state = *input.lane_change_state;

    MotionSearchOutput output;

    MotionGraphCache cost_cache;
    std::vector<SingleTrajInfo> multi_trajs;
    std::vector<std::vector<SptDebugNode>> spt_search_trees_vec;

    multi_trajs.reserve(leading_traj_configs.size());
    spt_search_trees_vec.reserve(leading_traj_configs.size());

    for (const auto &leading_trajs : leading_traj_configs) {
        std::vector<SptDebugNode> spt_search_tree;
        auto single_traj_result = SearchForSingleTrajectory(
            drive_passage, *input.sl_boundary, start_point, st_traj_mgr,
            *input.st_planner_object_traj, leading_trajs,
            *input.initializer_params, *input.motion_constraint_params,
            vehicle_geom, geom_graph, *input.form_builder,
            *input.collision_checker, *input.stop_s_vec,
            input.passage_speed_limit, input.init_scene_type,
            input.is_lane_change, input.is_manual_lane_change, &cost_cache,
            thread_pool, plan_id, &spt_search_tree);
        if (single_traj_result.ok()) {
            multi_trajs.push_back(std::move(single_traj_result).value());
            spt_search_trees_vec.push_back(spt_search_tree);
        }
    }

    if (multi_trajs.empty()) {
        return absl::NotFoundError("No terminating motion edge found.");
    }

    // VLOG(3) << "---------- Leading Object Group ----------";
    // int i = 1;
    // for (const auto &traj_info : multi_trajs) {
    //     VLOG(3) << i++ << ": " << traj_info.GetLeadingObjTrajId()
    //             << " cost: " << traj_info.total_cost;
    // }
    // VLOG(3) << "------------------------------------------";

    absl::flat_hash_set<std::string> follower_set;
    absl::flat_hash_set<std::string> leader_set;
    double leader_max_decel = 0.0;
    double follower_max_decel = 0.0;
    absl::flat_hash_set<std::string> unsafe_object_ids;
    PlannerStatusProto::PlannerStatusCode lc_status_code =
        PlannerStatusProto::OK;

    const auto choice_or = EvaluateMultiTrajs(
        drive_passage, start_point, st_traj_mgr, multi_trajs, vehicle_geom,
        input.eval_safety, input.lc_style, input.lc_state, input.prev_lc_stage,
        input.path_look_ahead_duration, &follower_set, &leader_set,
        &follower_max_decel, &leader_max_decel, &unsafe_object_ids,
        &lc_status_code, thread_pool, plan_id, input.borrow_lane);

    if (!multi_trajs.empty()) {
        const int chosen_idx = choice_or.ok() ? *choice_or : 0;
        const auto &chosen_traj = multi_trajs[static_cast<size_t>(chosen_idx)];
    }

    output.multi_traj_candidates.reserve(multi_trajs.size());
    for (const auto &traj : multi_trajs) {
        MotionSearchOutput::MultiTrajCandidate traj_candidate;
        traj_candidate.leading_traj_ids = traj.leading_trajs;
        traj_candidate.trajectory = traj.traj_points;
        if (traj.last_edge_index.value() < traj.search_costs.size()) {
            traj_candidate.feature_costs =
                traj.search_costs[traj.last_edge_index].feature_cost;
        }
        traj_candidate.last_edge_index = traj.last_edge_index;
        traj_candidate.total_cost = traj.total_cost;
        traj_candidate.ignored_trajs = traj.ignored_trajs;
        output.multi_traj_candidates.push_back(std::move(traj_candidate));
    }

    std::string prefix;
    output.speed_response_style = MappingLongResponseLevel(
        input.prev_lc_stage, follower_max_decel, leader_max_decel, prefix);
    output.lc_status_code = lc_status_code;

    if (!choice_or.ok()) {
        AD_LWARN(PP) << "No safe trajectory found for initializer, pausing "
                        "lane change: "
                     << choice_or.status().message();
        output.unsafe_object_ids = std::move(unsafe_object_ids);

        const auto immediate_collision_status = CheckForImmediateCollision(
            drive_passage, start_point, vehicle_geom, st_traj_mgr);
        if (!immediate_collision_status.ok()) {
            output.result_status = immediate_collision_status;

            return output;
        }

        output.is_lc_pause = true;

        return output;
    }

    const int choice = *choice_or;
    if (choice != 0) {
        std::swap(output.multi_traj_candidates[0],
                  output.multi_traj_candidates[static_cast<size_t>(choice)]);
    }
    output.follower_set = std::move(follower_set);
    output.leader_set = std::move(leader_set);
    output.follower_max_decel = follower_max_decel;
    for (const auto &traj_id : multi_trajs[static_cast<size_t>(choice)].leading_trajs) {
        for (const auto &leading_group : *input.leading_groups) {
            const auto it = leading_group.find(traj_id);
            if (it != leading_group.end()) {
                output.leading_trajs.emplace(traj_id, it->second);
                break;
            }
        }
    }
    output.nudge_info = std::move(multi_trajs[static_cast<size_t>(choice)].nudge_info);
    output.object_decisions = std::move(multi_trajs[static_cast<size_t>(choice)].object_decisions);
    output.traj_points = std::move(multi_trajs[static_cast<size_t>(choice)].traj_points);

    output.best_last_edge_index = multi_trajs[static_cast<size_t>(choice)].last_edge_index;
    output.min_cost = multi_trajs[static_cast<size_t>(choice)].total_cost;
    output.motion_graph = std::move(multi_trajs[static_cast<size_t>(choice)].motion_graph);
    output.ref_speed_table = std::move(multi_trajs[static_cast<size_t>(choice)].ref_speed_table);
    output.cost_provider = std::move(multi_trajs[static_cast<size_t>(choice)].cost_provider);

    if (FLAGS_planner_initializer_debug_level >= 1 ||
        FLAGS_planner_dumping_initializer_features) {
        auto &debug_info = multi_trajs[static_cast<size_t>(choice)].debug_info;
        output.terminated_edge_idxes =
            std::move(debug_info.terminated_edge_idxes);
        output.top_k_trajs = std::move(debug_info.top_k_trajs);
        output.top_k_total_costs = std::move(debug_info.top_k_total_costs);
        output.top_k_edges = std::move(debug_info.top_k_edges);
    }

    return output;
}
#endif  // !TAP_PLANNING_EMERGENCY_ONLY

void ComputeSafetyParams(const DrivePassage &drive_passage,
                         const VehicleGeometryParamsProto &vehicle_geom,
                         const InitializerConfig *initializer_params,
                         const FrenetCoordinate &ego_sl,
                         const bool is_manual_lane_change,
                         const double start_v,
                         const bool is_pre_safe,
                         std::vector<double> *thw,
                         double *ttc) {
    bool ego_corner_across_lane_bound = false;
    bool ego_center_across_lane_bound = false;
    CheckEgoPosWithLane(drive_passage, vehicle_geom, ego_sl,
                        &ego_corner_across_lane_bound,
                        &ego_center_across_lane_bound);

    const auto &safety_param =
        initializer_params->interactive_astar_search_config()
            .gap_safety_check_param();
    double is_less_v_upper = start_v < safety_param.manual_lc_v_upper();
    double gap_lead_thw =
        is_manual_lane_change && is_less_v_upper && !is_pre_safe
            ? InterpolateSafetyParams(drive_passage, vehicle_geom, ego_sl,
                                      ego_corner_across_lane_bound,
                                      safety_param.manual_lc_gap_lead_thw_max(),
                                      safety_param.manual_lc_gap_lead_thw_min())
            : InterpolateSafetyParams(drive_passage, vehicle_geom, ego_sl,
                                      ego_corner_across_lane_bound,
                                      safety_param.gap_lead_thw_max(),
                                      safety_param.gap_lead_thw_min());
    double gap_tail_thw =
        is_manual_lane_change && is_less_v_upper
            ? (!is_pre_safe ? InterpolateSafetyParams(
                                  drive_passage, vehicle_geom, ego_sl,
                                  ego_corner_across_lane_bound,
                                  safety_param.manual_lc_gap_tail_thw_max(),
                                  safety_param.manual_lc_gap_tail_thw_min())
                            : InterpolateSafetyParams(
                                  drive_passage, vehicle_geom, ego_sl,
                                  ego_corner_across_lane_bound,
                                  safety_param.gap_tail_thw_max(),
                                  safety_param.gap_tail_thw_min()))
            : (!is_pre_safe ? InterpolateSafetyParams(
                                  drive_passage, vehicle_geom, ego_sl,
                                  ego_corner_across_lane_bound,
                                  safety_param.gap_tail_thw_max(),
                                  safety_param.gap_tail_thw_min())
                            : InterpolateSafetyParams(
                                  drive_passage, vehicle_geom, ego_sl,
                                  ego_corner_across_lane_bound,
                                  safety_param.radical_gap_tail_thw_max(),
                                  safety_param.radical_gap_tail_thw_min()));
    double ori_lead_thw =
        is_manual_lane_change && is_less_v_upper && !is_pre_safe
            ? InterpolateSafetyParams(drive_passage, vehicle_geom, ego_sl,
                                      ego_corner_across_lane_bound,
                                      safety_param.manual_lc_ori_lead_thw_max(),
                                      safety_param.manual_lc_ori_lead_thw_min())
            : InterpolateSafetyParams(drive_passage, vehicle_geom, ego_sl,
                                      ego_corner_across_lane_bound,
                                      safety_param.ori_lead_thw_max(),
                                      safety_param.ori_lead_thw_min());

    *thw = {gap_lead_thw, gap_tail_thw, ori_lead_thw};

    *ttc = !is_pre_safe
               ? InterpolateSafetyParams(drive_passage, vehicle_geom, ego_sl,
                                         ego_corner_across_lane_bound,
                                         safety_param.gap_tail_ttc_max(),
                                         safety_param.gap_tail_ttc_min(), true)
               : InterpolateSafetyParams(
                     drive_passage, vehicle_geom, ego_sl,
                     ego_corner_across_lane_bound,
                     safety_param.radical_gap_tail_ttc_max(),
                     safety_param.radical_gap_tail_ttc_min(), true);
}

absl::StatusOr<MotionSearchOutput> InteractiveAStarSearch(
    const MotionSearchInput &input,
    ThreadPool *thread_pool,
    int plan_id,
    const std::vector<LeadingTrajs> &leading_traj_configs) {
    SCOPED_TRACE("EstPlanner/InteractiveAStarSearch");

    const DrivePassage &drive_passage = *input.drive_passage;
    const ApolloTrajectoryPointProto &start_point = *input.start_point;
    const VehicleGeometryParamsProto &vehicle_geom =
        input.vehicle_params->vehicle_geometry_params();
    const GeometryGraph &geom_graph = *input.geom_graph;
    const std::vector<LeadingGroup> &leading_groups = *input.leading_groups;
    const std::vector<std::vector<std::string>> &insertion_orders =
        *input.insertion_orders;
    const SpacetimeTrajectoryManager &st_traj_mgr = *input.st_traj_mgr;
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj =
        *input.st_planner_object_traj;
    const LaneChangeStateProto &lc_state = *input.lane_change_state;
    const boost::optional<std::string> &nullable_nearest_vru_object_id =
        input.nullable_nearest_vru_object_id;
    const bool is_pre_lane_change =
        input.prev_lc_stage == LaneChangeStage::LCS_EXECUTING ||
        input.prev_lc_stage == LaneChangeStage::LCS_PAUSE;
    MotionSearchOutput output;

    std::vector<ObstacleDecisionGroup> decision_groups = ComputeDecisionGroup(
        drive_passage, st_planner_object_traj, leading_groups, insertion_orders,
        start_point, lc_state, input.current_path_leader_id,
        input.av_frenet_box, input.pre_obs_gap, input.initializer_params,
        nullable_nearest_vru_object_id, plan_id, input.is_lane_change,
        is_pre_lane_change);

    const int group_size = decision_groups.size();
    std::vector<std::vector<ApolloTrajectoryPointProto>> coarse_trajectories;
    coarse_trajectories.resize(static_cast<size_t>(group_size));
    std::vector<int> first_safe_to_gap_indexes(static_cast<size_t>(group_size), -1);
    std::vector<bool> start_node_safety(static_cast<size_t>(group_size), false);
    std::vector<int> all_node_safety(static_cast<size_t>(group_size), 1);
    std::vector<std::string> safety_check_info(static_cast<size_t>(group_size), "all safe.\n");
    std::vector<uint64_t> goal_indices(static_cast<size_t>(group_size), 0);
    int pri_decision_group_index = -1;

    const auto ego_pos = Vec2dFromApolloTrajectoryPointProto(start_point);
    ASSIGN_OR_RETURN(const auto ego_sl,
                     drive_passage.QueryFrenetCoordinateAt(ego_pos),
                     _ << "Failed to project ego position on drive passage.");

    std::vector<double> thw(3, 0.0);
    double tail_ttc = 0.0;
    bool is_pre_safe =
        input.pre_obs_gap == nullptr
            ? false
            : (input.pre_obs_gap->is_merge_safe.first && is_pre_lane_change);
    ComputeSafetyParams(drive_passage, vehicle_geom, input.initializer_params,
                        ego_sl, input.is_manual_lane_change, start_point.v(),
                        is_pre_safe, &thw, &tail_ttc);
    output.thw = thw;

    RunInteractiveSearch(
        input, thread_pool, plan_id, ego_sl, decision_groups, input.pre_obs_gap,
        coarse_trajectories, first_safe_to_gap_indexes, start_node_safety,
        all_node_safety, goal_indices, pri_decision_group_index,
        safety_check_info, thw, tail_ttc);

    if (pri_decision_group_index == -1) {
        return SearchFailOut(drive_passage, ego_sl, plan_id, input, output);
    }

    bool ego_corner_across_lane_bound = false;
    bool ego_center_across_lane_bound = false;
    CheckEgoPosWithLane(drive_passage, vehicle_geom, ego_sl,
                        &ego_corner_across_lane_bound,
                        &ego_center_across_lane_bound);
    std::vector<ApolloTrajectoryPointProto> traj_result;
    ASSIGN_OR_RETURN(
        auto best_gap_result,
        ComputeGapResult(pri_decision_group_index, decision_groups,
                         input.pre_obs_gap, goal_indices, safety_check_info,
                         coarse_trajectories, drive_passage,
                         input.is_lane_change, is_pre_lane_change,
                         first_safe_to_gap_indexes, start_node_safety,
                         all_node_safety, plan_id, ego_center_across_lane_bound,
                         &traj_result, output.first_safe_to_gap_index));

    AddLeadingTrajs(best_gap_result, input.is_lane_change, leading_groups,
                    insertion_orders, plan_id, &output.leading_trajs);
    std::string prefix;
    NudgeInfos nudge_info;
    auto object_decisions_out = ExtractObjectDecisions(
        traj_result, input.is_lane_change, drive_passage, *input.sl_boundary,
        st_planner_object_traj, vehicle_geom, prefix, plan_id, &nudge_info,
        best_gap_result, input.pre_object_decisions);

    output.traj_points = std::move(traj_result);
    output.obs_gap = std::move(best_gap_result);
    output.nudge_info = std::move(nudge_info);
    output.object_decisions = std::move(object_decisions_out);

    return output;
}

std::mutex spt_debug_info_mutex;
absl::StatusOr<MotionSearchOutput> SearchForRawTrajectory(
    const MotionSearchInput &input, ThreadPool *thread_pool, int plan_id) {
    const auto &leading_traj_configs =
        BuildLeadingConfigs(*input.leading_groups, input.blocking_static_traj);
    if (leading_traj_configs.empty()) {
        return absl::NotFoundError("No leading group generated.");
    }

    switch (input.initializer_params->search_algorithm()) {
#if !TAP_PLANNING_EMERGENCY_ONLY
        case InitializerConfig::DP: {
            return DPSearch(input, thread_pool, plan_id, leading_traj_configs);
        } break;
#endif
        case InitializerConfig::InteractiveAStar: {
            return InteractiveAStarSearch(input, thread_pool, plan_id,
                                          leading_traj_configs);
        } break;
    }
    return absl::UnknownError("UnknownError.");
}

std::vector<double> GenerateSpeedLimitByGap(
    const MotionSearchInput &input,
    const pnc_x::FrenetCoordinate &ego_sl,
    const ObstacleDecisionGroup &decision_group) {
    const auto &interactive_astar_config =
        input.initializer_params->interactive_astar_search_config();
    const ApolloTrajectoryPointProto &start_point = *input.start_point;
    const DrivePassage &drive_passage = *input.drive_passage;
    const auto ori_speed_limit = drive_passage.QuerySpeedLimitAtS(ego_sl.s);
    std::vector<double> speed_limits;
    constexpr double kSpeedLimitTimeRange = 20.0;
    const int size = static_cast<int>(
        kSpeedLimitTimeRange / interactive_astar_config.time_resolution());
    speed_limits.reserve(static_cast<size_t>(size));
    if (ori_speed_limit.ok()) {
        for (int i = 0; i < size; ++i) {
            speed_limits.push_back(
                std::max(ori_speed_limit.value(),
                         start_point.v() -
                             0.8 * double(i) *
                                 interactive_astar_config.time_resolution()));
        }
    } else {
        speed_limits.resize(static_cast<size_t>(size), 33.3);
    }
    if (input.is_lane_change &&
        decision_group.obs_goal_gap.tail_obj_id.has_value()) {
        constexpr double kExceedingRatio = 1.1;
        for (auto &speed : speed_limits) {
            speed *= kExceedingRatio;
            speed = std::min(ads_x::planning::Constants::MAX_LANE_CHANGE_SPEED,
                             speed);
        }
    }
    return speed_limits;
}

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
    double tail_ttc) {
    SCOPED_TRACE("EstPlanner/RunInteractiveSearch");

    const ApolloTrajectoryPointProto &start_point = *input.start_point;
    Node start_node(start_point.path_point().x(), start_point.path_point().y(),
                    start_point.path_point().theta(), start_point.v());
    start_node.SetS(ego_sl.s);
    start_node.SetL(ego_sl.l);
    const auto &interactive_astar_config =
        input.initializer_params->interactive_astar_search_config();
    double goal_s_original =
        ego_sl.s + std::max(interactive_astar_config.min_dis(),
                            double(start_point.v()) *
                                interactive_astar_config.goal_time());

    int group_size = decision_groups.size();
    Timer start_time;
    std::vector<ApolloTrajectoryPointProto> coarse_trajectory;
    std::vector<std::unordered_map<uint64_t, Node>> nodes_maps(static_cast<size_t>(group_size));
    std::vector<AStarSearch> a_star_searchers;
    for (int i = 0; i < group_size; ++i) {
        AStarSearch astar_searcher(
            &decision_groups[static_cast<size_t>(i)], input.obstacles_behavior_map,
            input.vehicle_params, *input.initializer_params,
            input.drive_passage, input.sl_boundary, thw, tail_ttc);
        // std::cout << "[DEBUG] Created AStarSearch " << i << ", adding to
        // vector"
        //           << std::endl;

        a_star_searchers.push_back(std::move(astar_searcher));
    }

    const LaneChangeStage prev_lc_stage = input.prev_lc_stage;
    bool is_pre_safe =
        pre_obs_gap == nullptr
            ? false
            : (pre_obs_gap->is_merge_safe.first &&
               (prev_lc_stage == LaneChangeStage::LCS_EXECUTING ||
                prev_lc_stage == LaneChangeStage::LCS_PAUSE));
    RefVelocityInGap start_ref_velocity_lon;
    ParallelFor(0, group_size, thread_pool, [&](int i) {
        double goal_s = goal_s_original;
        double start_ego_to_safety_dis = 0.0;
        const std::string group_prefix = absl::StrCat("-group", i);
        std::string start_safety_check_msg = " ";
        const std::vector<double> speed_limits =
            GenerateSpeedLimitByGap(input, ego_sl, decision_groups[i]);
        start_node_safety[i] =
            a_star_searchers[i].safety_checker()->IsCollisionFree(
                input.is_lane_change, start_node.X(), start_node.Y(),
                start_node.V(), start_node.Theta(), 0.0, start_node.S(),
                start_node.L(), true, &start_ego_to_safety_dis, start_node.X(),
                start_node.Y(), start_node.V(), start_node.Theta(), 0.0,
                group_prefix, &start_safety_check_msg, is_pre_safe, nullptr,
                nullptr, &start_ref_velocity_lon);
        start_node.SetEgoToSafetyDis(start_ego_to_safety_dis);
        start_node.SetSafetyCheckInfo(std::move(start_safety_check_msg));
        start_node.SetRefVelocityInGap(start_ref_velocity_lon);

        UpdateGoalSByLeadObs(decision_groups[i], *input.initializer_params,
                             input.vehicle_params, start_node, goal_s);
        std::string goal_s_str;
        std::string leading_obj;
        if (decision_groups[i].obs_goal_gap.lead_obj_id.has_value()) {
            leading_obj = decision_groups[i].obs_goal_gap.lead_obj_id.value();
        }
        goal_s_str = absl::StrCat(leading_obj, "  :  ", goal_s);

        goal_indices[i] = a_star_searchers[i].Search(
            start_node, goal_s, nodes_maps[i], decision_groups[i], group_prefix,
            *input.xy_range, input.is_lane_change, input.is_manual_lane_change,
            speed_limits, *input.st_traj_mgr, is_pre_safe);
        std::string all_node_safety_check_msg = " ";
        const bool is_pre_gap_safe =
            IsPreGapSafe(decision_groups[i].obs_goal_gap, pre_obs_gap);
        a_star_searchers[i].GetCoarseTrajectory(
            coarse_trajectories[i], &first_safe_to_gap_indexes[i],
            start_node_safety[i], is_pre_gap_safe, &all_node_safety[i],
            &all_node_safety_check_msg);
        if (all_node_safety_check_msg != " ") {
            infos[i] = all_node_safety_check_msg;
        }
    });

    double min_goal_cost = std::numeric_limits<double>::max();
    std::vector<SearchResult> search_results;
    search_results.reserve(static_cast<size_t>(group_size));
    std::string search_result_info = " ";
    std::string search_info = " ";
    for (int i = 0; i < group_size; ++i) {
        absl::StrAppend(&search_result_info, "group ", i, ": ");
        absl::StrAppend(&search_info, absl::StrCat("group ", i, ": "));
        if (goal_indices[static_cast<size_t>(i)] == 0) {
            absl::StrAppend(&search_result_info, "search failed. ",
                            a_star_searchers[static_cast<size_t>(i)].SearchFailReason());
            search_results.push_back(SearchResult::kSearchFailed);
            search_info += a_star_searchers[static_cast<size_t>(i)].SearchInfo() + "\n";
            continue;
        }
        absl::StrAppend(&search_result_info, "search succeed, iterations: ",
                        a_star_searchers[static_cast<size_t>(i)].GetIterations());
        search_results.push_back(SearchResult::kSearchSuccess);

        double cost = nodes_maps[static_cast<size_t>(i)][goal_indices[static_cast<size_t>(i)]].TotalCost();
        absl::StrAppend(&search_result_info, ", cost: ", cost, "\n");
        if (cost < min_goal_cost) {
            min_goal_cost = cost;
            pri_decision_group_index = i;
        }

        search_info += a_star_searchers[static_cast<size_t>(i)].SearchInfo() + "\n";
    }
}

}  // namespace planning
}  // namespace pnc_x
