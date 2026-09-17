

#include "initializer/dp_motion_searcher_util.h"

#include <algorithm>
#include <array>
#include <limits>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <absl/algorithm/container.h>
#include <absl/container/flat_hash_set.h>
#include <absl/hash/hash.h>
#include <absl/status/statusor.h>
#include <absl/types/span.h>

#include "initializer/cost_provider.h"
#include "initializer/dp_motion_searcher_defs.h"
#include "initializer/geometry/geometry_form.h"
#include "initializer/geometry/geometry_graph.h"
#include "initializer/geometry/geometry_state.h"
#include "initializer/motion_form.h"
#include "initializer/motion_graph.h"
#include "initializer/motion_graph_cache.h"
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
#include "router/drive_passage.h"
#include "pncx_trajectory_point.pb.h"
#include "util/loop_guard.h"

namespace pnc_x {
namespace planning {

void ComputeCost(const CostProvider &cost_provider,
                 DpMotionInfo *ptr_motion_info) {
    auto &dp_motion_info = *ptr_motion_info;
    dp_motion_info.costs.resize(cost_provider.weights().size());
    dp_motion_info.ignored_trajs = cost_provider.ComputeInteractiveCost(
        dp_motion_info.start_t, dp_motion_info.motion_form,
        dp_motion_info.ignored_trajs, absl::MakeSpan(dp_motion_info.costs));
}

void ComputeDpLeadingObjCost(const CostProvider &cost_provider,
                             DpMotionInfo *ptr_motion_info) {
    auto &dp_motion_info = *ptr_motion_info;
    cost_provider.ComputeDpLeadingObjCost(dp_motion_info.start_t,
                                          dp_motion_info.motion_form,
                                          absl::MakeSpan(dp_motion_info.costs));
}

void SampleDynamicMotions(
    MotionNodeIndex motion_node_idx,
    MotionEdgeIndex prev_motion_edge_idx,
    const MotionGraph &motion_graph,
    const GeometryEdge &geom_edge,
    const IgnoreTrajMap &ignored_trajs,
    const MotionConstraintParamsProto &motion_constraint_params,
    const CostProvider &cost_provider,
    const MotionGraphCache &cost_cache,
    bool sample_const_v,
    std::vector<DpMotionInfo> *ptr_motions,
    std::vector<NewCacheInfo> *new_motion_forms_cache,
    ThreadPool *thread_pool) {
    const auto motion_state = motion_graph.GetMotionNode(motion_node_idx).state;
    const double v0 = motion_state.v;
    const double t0 = motion_state.t;
    auto &motions = *ptr_motions;

    absl::flat_hash_set<DpMotionEdgeKey> unrepeated_keys;
    const auto expand_motion_by_a = [&unrepeated_keys, &geom_edge, t0](
                                        double v0, double a0) {
        unrepeated_keys.emplace(DpMotionEdgeKey(a0, v0, t0, geom_edge.index));
    };

    if (!XCHECK_GE(v0, 0.0)) {
        return;
    }
    const double a_max = motion_constraint_params.max_acceleration();
    const double a_min = motion_constraint_params.max_deceleration();
    if (!XCHECK_LT(a_min, 0.0) || !XCHECK_GT(a_max, 0.0)) {
        return;
    }
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
            const double a0 = motion_state.a;
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
        expand_motion_by_a(v0, acc);
    }

    std::vector<DpMotionEdgeKey> keys;
    keys.reserve(unrepeated_keys.size());
    for (auto &key : unrepeated_keys) {
        keys.push_back(key);
    }
    motions.reserve(keys.size());
    for (int i = 0; i < keys.size(); ++i) {
        DpMotionInfo motion_info;
        motion_info.key = keys[static_cast<size_t>(i)];
        motion_info.sum_cost = 0.0;
        motion_info.start_t = t0;
        motion_info.prev_motion_edge_index = prev_motion_edge_idx;
        motion_info.end_geometry_node_index = geom_edge.end;
        motion_info.motion_form = nullptr;
        motion_info.geometry_edge_index = geom_edge.index;
        motion_info.ignored_trajs = ignored_trajs;
        motions.emplace_back(std::move(motion_info));
    }
    std::vector<int> failed_idx;
    failed_idx.reserve(keys.size());

    cost_cache.BatchGetOrFail(keys, &motions, &failed_idx);

    std::vector<std::unique_ptr<MotionForm>> new_motion_forms;
    new_motion_forms.reserve(failed_idx.size());
    for (int i = 0; i < failed_idx.size(); ++i) {
        const int cur_failed_idx = failed_idx[static_cast<size_t>(i)];
        const auto &key = keys[static_cast<size_t>(cur_failed_idx)];
        new_motion_forms.emplace_back(std::make_unique<ConstAccelMotion>(
            key.v0(), key.a0(), geom_edge.geometry));
        motions[static_cast<size_t>(cur_failed_idx)].motion_form = new_motion_forms[static_cast<size_t>(i)].get();
    }

    for (int i = 0; i < failed_idx.size(); ++i) {
        const int cur_failed_idx = failed_idx[static_cast<size_t>(i)];
        ComputeCost(cost_provider, &motions[static_cast<size_t>(cur_failed_idx)]);
        MotionEdgeCache new_cache(
            {.ptr_motion_form = std::move(new_motion_forms[static_cast<size_t>(i)]),
             .costs = motions[static_cast<size_t>(cur_failed_idx)].costs,
             .ignored_trajs = motions[static_cast<size_t>(cur_failed_idx)].ignored_trajs});
        new_motion_forms_cache->push_back(NewCacheInfo{
            .key = keys[static_cast<size_t>(cur_failed_idx)], .cache = std::move(new_cache)});
    }

    for (int i = 0; i < keys.size(); ++i) {
        if (std::find(failed_idx.begin(), failed_idx.end(), i) ==
            failed_idx.end()) {
            ComputeDpLeadingObjCost(cost_provider, &motions[static_cast<size_t>(i)]);
        }
        motions[static_cast<size_t>(i)].sum_cost = absl::c_accumulate(motions[static_cast<size_t>(i)].costs, 0.0);
    }
}

std::vector<DpMotionInfo> ExpandStartMotionEdges(
    GeometryNodeIndex geom_node_idx,
    MotionNodeIndex motion_node_idx,
    const GeometryGraph &geometry,
    const MotionGraph &motion_graph,
    const MotionConstraintParamsProto &motion_constraint_params,
    const CostProvider &cost_provider,
    const MotionGraphCache &cost_cache,
    std::vector<NewCacheInfo> *new_motion_forms,
    ThreadPool *thread_pool) {
    const auto &outgoing_edge_idxs = geometry.GetOutgoingEdges(geom_node_idx);
    std::vector<DpMotionInfo> motions;
    motions.reserve((kAccelerationSamplePoints.size() + 3) *
                    outgoing_edge_idxs.size());
    for (const auto &outgoing_edge_idx : outgoing_edge_idxs) {
        const auto &geom_edge = geometry.GetEdge(outgoing_edge_idx);
        if (!geometry.IsActive(outgoing_edge_idx)) {
            continue;
        }

        std::vector<DpMotionInfo> motions_per_edge;
        SampleDynamicMotions(
            motion_node_idx, static_cast<MotionEdgeIndex>(-1), motion_graph,
            geom_edge, {}, motion_constraint_params, cost_provider, cost_cache,
            false, &motions_per_edge, new_motion_forms, thread_pool);
        for (int i = 0; i < motions_per_edge.size(); i++) {
            motions.emplace_back(std::move(motions_per_edge[static_cast<size_t>(i)]));
        }
    }
    return motions;
}

std::vector<DpMotionInfo> ExpandMotionEdges(
    GeometryNodeIndex geom_node_idx,
    const std::vector<MotionEdgeIndex> &motion_edge_idxes,
    const MotionEdgeVector<IgnoreTrajMap> &ignored_trajs_vector,
    const GeometryGraph &geometry,
    const MotionGraph &motion_graph,
    const MotionConstraintParamsProto &motion_constraint_params,
    const CostProvider &cost_provider,
    bool sample_const_v,
    const MotionGraphCache &cost_cache,
    std::vector<NewCacheInfo> *new_motion_forms,
    ThreadPool *thread_pool) {
    const auto &outgoing_edge_idxs = geometry.GetOutgoingEdges(geom_node_idx);
    std::vector<DpMotionInfo> motions;
    motions.reserve((kAccelerationSamplePoints.size() + 2) *
                    outgoing_edge_idxs.size() * motion_edge_idxes.size());
    for (const auto &outgoing_edge_idx : outgoing_edge_idxs) {
        const auto &geom_edge = geometry.GetEdge(outgoing_edge_idx);
        if (!geometry.IsActive(outgoing_edge_idx)) {
            continue;
        }
        for (const auto &motion_edge_idx : motion_edge_idxes) {
            std::vector<DpMotionInfo> motions_per_edge;
            const auto motion_node_idx =
                motion_graph.GetMotionEdge(motion_edge_idx).end;
            const auto &ignored_trajs = ignored_trajs_vector[motion_edge_idx];
            SampleDynamicMotions(motion_node_idx, motion_edge_idx, motion_graph,
                                 geom_edge, ignored_trajs,
                                 motion_constraint_params, cost_provider,
                                 cost_cache, sample_const_v, &motions_per_edge,
                                 new_motion_forms, thread_pool);
            for (int i = 0; i < motions_per_edge.size(); i++) {
                motions.emplace_back(std::move(motions_per_edge[static_cast<size_t>(i)]));
            }
        }
    }
    return motions;
}

double GetLeadingObjectsEndMinS(const SpacetimeTrajectoryManager &st_mgr,
                                const DrivePassage &drive_passage,
                                const std::vector<std::string> &leading_objs,
                                double ego_front_to_ra) {
    double min_s = std::numeric_limits<double>::max();
    for (const auto &lead_obj : leading_objs) {
        const auto obj_traj = st_mgr.FindTrajectoryById(lead_obj);
        if (obj_traj == nullptr) {
            continue;
        }
        const auto states = obj_traj->states();
        const auto fbox =
            obj_traj->is_stationary()
                ? drive_passage.QueryFrenetBoxAt(states.front().box)
                : drive_passage.QueryFrenetBoxAt(states.back().box);
        if (!fbox.ok()) {
            continue;
        }
        min_s = std::min(min_s, fbox->s_min);
    }
    return min_s - ego_front_to_ra;
}

std::vector<TrajInfo> TopKTrajectories(
    const MotionGraph &motion_graph,
    absl::Span<const MotionEdgeIndex> terminated_edge_idxes,
    const MotionEdgeVector<MotionSearchOutput::SearchCost> &search_costs,
    int k_top_trajectories) {
    std::vector<TrajInfo> top_k_trajs;
    top_k_trajs.reserve(terminated_edge_idxes.size());
    for (const auto &term_idx : terminated_edge_idxes) {
        top_k_trajs.push_back(
            TrajInfo({.idx = term_idx,
                      .total_cost = search_costs[term_idx].cost_to_come}));
    }
    std::stable_sort(top_k_trajs.begin(), top_k_trajs.end(),
                     [](const TrajInfo &traj1, const TrajInfo &traj2) {
                         return traj1.total_cost < traj2.total_cost;
                     });

    if (top_k_trajs.size() > 1) {
        double max_traj_len = 0.1;
        const double ref_cost_th = 0.6;
        std::vector<TrajInfo>::iterator straightest_iter = top_k_trajs.begin();
        for (auto iter = top_k_trajs.begin(); top_k_trajs.end() != iter;
             ++iter) {
            const auto &motion_edge = motion_graph.GetMotionEdge(iter->idx);
            const auto &motion_node =
                motion_graph.GetMotionNode(motion_edge.end);
            if ((search_costs[iter->idx].feature_cost[1] < ref_cost_th) &&
                (motion_node.state.accumulated_s > max_traj_len)) {
                max_traj_len = motion_node.state.accumulated_s;
                straightest_iter = iter;
            }
        }
        auto end_idx = k_top_trajectories < top_k_trajs.size()
                           ? k_top_trajectories
                           : top_k_trajs.size();
        if (top_k_trajs.begin() != straightest_iter) {
            std::swap(*straightest_iter, *(top_k_trajs.begin() + end_idx - 1));
        }
    }
    if (k_top_trajectories < top_k_trajs.size()) {
        top_k_trajs.resize(static_cast<size_t>(k_top_trajectories));
    }
    return top_k_trajs;
}

BestEdgeInfo FindBestEdge(
    const CostProvider &cost_provider,
    const MotionState &sdc_motion,
    MotionNodeIndex sdc_node_index,
    const GeometryNodeIndex &sdc_geom_node,
    MotionGraph *mutable_motion_graph,
    MotionGraphCache *cost_cache,
    MotionEdgeVector<MotionSearchOutput::SearchCost> *ptr_mutable_search_costs,
    MotionEdgeVector<IgnoreTrajMap> *ptr_mutable_ignore_traj_map,
    std::vector<MotionEdgeIndex> *ptr_mutable_terminated_idxes) {
    auto &mutable_search_costs = *ptr_mutable_search_costs;
    auto &mutable_terminated_idxes = *ptr_mutable_terminated_idxes;
    MotionEdgeIndex best_final_edge = static_cast<MotionEdgeIndex>(-1);
    double min_cost = std::numeric_limits<double>::max();
    for (int i = 0, n = mutable_terminated_idxes.size(); i < n; ++i) {
        const auto terminated_idx = mutable_terminated_idxes[static_cast<size_t>(i)];
        const auto total_cost =
            mutable_search_costs[terminated_idx].cost_to_come;
        if (total_cost < min_cost) {
            best_final_edge = terminated_idx;
            min_cost = total_cost;
        }
    }

    bool is_created_stationary_motion = false;
    if (best_final_edge == static_cast<MotionEdgeIndex>(-1) &&
        (sdc_motion.v < kSearchFailedCanSetToZeroSpeed)) {
        is_created_stationary_motion = true;
        auto set2zero_sdc_motion = sdc_motion;
        set2zero_sdc_motion.v = 0.0;
        DpMotionEdgeKey stationary_motion_key = DpMotionEdgeKey(
            set2zero_sdc_motion.v, set2zero_sdc_motion.a, set2zero_sdc_motion.t,
            static_cast<GeometryEdgeIndex>(-1));

        const auto end_node_index = mutable_motion_graph->AddMotionNode(
            set2zero_sdc_motion, sdc_geom_node);
        const auto ptr_motion_form_or =
            cost_cache->GetMotionForm(stationary_motion_key);
        MotionForm *ptr_motion_form = nullptr;
        std::unique_ptr<MotionForm> stationary_motion = nullptr;
        if (!ptr_motion_form_or.ok()) {
            stationary_motion = std::make_unique<StationaryMotion>(
                kInitializerTrajectoryTimeHorizon,
                GeometryState{.xy = sdc_motion.xy,
                              .h = sdc_motion.h,
                              .k = sdc_motion.k,
                              .accumulated_s = sdc_motion.accumulated_s,
                              .l = sdc_motion.l});
            ptr_motion_form = stationary_motion.get();
            DpMotionInfo temp_motion_info{
                .sum_cost = 0.0,
                .start_t = 0.0,
                .motion_form = stationary_motion.get()};
            ComputeCost(cost_provider, &temp_motion_info);
            cost_cache->Insert(stationary_motion_key, temp_motion_info.costs,
                               {}, std::move(stationary_motion));
            MotionSearchOutput::SearchCost new_search_cost{
                .feature_cost = temp_motion_info.costs,
                .cost_to_come =
                    absl::c_accumulate(temp_motion_info.costs, 0.0)};
            mutable_search_costs.push_back(new_search_cost);
            min_cost = new_search_cost.cost_to_come;
        } else {
            ptr_motion_form = *ptr_motion_form_or;

            absl::StatusOr<std::vector<double>> feature_costs =
                cost_cache->GetCosts(stationary_motion_key);
            if (feature_costs.ok()) {
                MotionSearchOutput::SearchCost new_search_cost{
                    .feature_cost = feature_costs.value(),
                    .cost_to_come =
                        absl::c_accumulate(feature_costs.value(), 0.0),
                };
                mutable_search_costs.push_back(new_search_cost);
                min_cost = new_search_cost.cost_to_come;
            }
        }
        const auto motion_edge_index = mutable_motion_graph->AddMotionEdge(
            sdc_node_index, end_node_index, ptr_motion_form, sdc_geom_node,
            static_cast<MotionEdgeIndex>(-1));

        ptr_mutable_ignore_traj_map->push_back({});
        mutable_terminated_idxes.push_back(motion_edge_index);
        best_final_edge = motion_edge_index;
    }
    return {.idx = best_final_edge,
            .total_cost = min_cost,
            .is_created_stationary_motion = is_created_stationary_motion};
}

std::vector<ApolloTrajectoryPointProto> ConstructTrajFromLastEdge(
    const MotionGraph &motion_graph, MotionEdgeIndex last_edge_index) {
    std::vector<const MotionForm *> motions;
    XCHECK_GE(last_edge_index.value(), 0);
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (last_edge_index != static_cast<MotionEdgeIndex>(-1) && loop_guard) {
        const auto &motion_edge = motion_graph.GetMotionEdge(last_edge_index);
        motions.emplace_back(motion_edge.motion);
        last_edge_index = motion_edge.prev_edge;
    }
    std::reverse(motions.begin(), motions.end());
    std::vector<ApolloTrajectoryPointProto> traj_points;
    ResampleTrajectoryPoints(motions, traj_points);
    return traj_points;
}

}  // namespace planning
}  // namespace pnc_x
