
#pragma once

#include <string>
#include <vector>

#include "async/thread_pool.h"
#include "initializer/cost_provider.h"
#include "initializer/dp_motion_searcher_defs.h"
#include "initializer/geometry/geometry_graph.h"
#include "initializer/initializer_output.h"
#include "initializer/motion_graph.h"
#include "initializer/motion_graph_cache.h"
#include "initializer/motion_state.h"
#include "object/spacetime_trajectory_manager.h"
#include "pncx_planner_params.pb.h"
#include "router/drive_passage.h"
#include "pncx_trajectory_point.pb.h"
#include <absl/types/span.h>

namespace pnc_x {
namespace planning {

std::vector<double> AddCost(absl::Span<const double> vec1,
                            absl::Span<const double> vec2);

void ComputeCost(const CostProvider &cost_provider,
                 DpMotionInfo *ptr_motion_info);

void ComputeDpLeadingObjCost(const CostProvider &cost_provider,
                             DpMotionInfo *ptr_motion_info);

void SampleDynamicMotions(MotionNodeIndex motion_node_idx,
                          MotionEdgeIndex prev_motion_edge_idx,
                          const MotionGraph &motion_graph,
                          const GeometryEdge &geom_edge,
                          const IgnoreTrajMap &ignored_trajs,
                          const PlannerParamsProto &planner_params,
                          const CostProvider &cost_provider,
                          const MotionGraphCache &cost_cache,
                          bool sample_const_v,
                          std::vector<DpMotionInfo> *ptr_motions,
                          std::vector<NewCacheInfo> *new_motion_forms_cache,
                          ThreadPool *thread_pool);

std::vector<DpMotionInfo> ExpandStartMotionEdges(
    GeometryNodeIndex geom_node_idx,
    MotionNodeIndex motion_node_idx,
    const GeometryGraph &geometry,
    const MotionGraph &motion_graph,
    const MotionConstraintParamsProto &motion_constraint_params,
    const CostProvider &cost_provider,
    const MotionGraphCache &cost_cache,
    std::vector<NewCacheInfo> *new_motion_forms,
    ThreadPool *thread_pool);

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
    ThreadPool *thread_pool);

double GetLeadingObjectsEndMinS(const SpacetimeTrajectoryManager &st_mgr,
                                const DrivePassage &drive_passage,
                                const std::vector<std::string> &leading_objs,
                                double sdc_length);

std::vector<TrajInfo> TopKTrajectories(
    const MotionGraph &motion_graph,
    absl::Span<const MotionEdgeIndex> terminated_edge_idxes,
    const MotionEdgeVector<MotionSearchOutput::SearchCost> &search_costs,
    int k_top_trajectories);

BestEdgeInfo FindBestEdge(
    const CostProvider &cost_provider,
    const MotionState &sdc_motion,
    MotionNodeIndex sdc_node_index,
    const GeometryNodeIndex &sdc_geom_node,
    MotionGraph *mutable_motion_graph,
    MotionGraphCache *cost_cache,
    MotionEdgeVector<MotionSearchOutput::SearchCost> *ptr_mutable_search_costs,
    MotionEdgeVector<IgnoreTrajMap> *ptr_mutable_ignore_traj_map,
    std::vector<MotionEdgeIndex> *ptr_mutable_terminated_idxes);

std::vector<ApolloTrajectoryPointProto> ConstructTrajFromLastEdge(
    const MotionGraph &motion_graph, MotionEdgeIndex last_edge_index);

}  // namespace planning
}  // namespace pnc_x
