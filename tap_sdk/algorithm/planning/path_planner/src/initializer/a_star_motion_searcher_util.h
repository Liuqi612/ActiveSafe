#pragma once

#include <string>
#include <utility>
#include <vector>

#include <boost/heap/pairing_heap.hpp>

#include "initializer/a_star_motion_searcher_defs.h"
#include "initializer/cost_provider.h"
#include "initializer/motion_search_types.h"
#include "initializer/geometry/geometry_graph.h"
#include "initializer/initializer_input.h"
#include "initializer/initializer_output.h"
#include "initializer/interactive_search/common/common.h"
#include "initializer/motion_graph.h"
#include "initializer/motion_state.h"
#include "pncx_planner_params.pb.h"
#include "pncx_trajectory_point.pb.h"

namespace pnc_x {
namespace planning {

struct CompareNodes {
    bool operator()(const std::pair<uint64_t, double> &lhs,
                    const std::pair<uint64_t, double> &rhs) const {
        return lhs.second > rhs.second;
    }
};

typedef boost::heap::pairing_heap<std::pair<uint64_t, double>,
                                  boost::heap::compare<CompareNodes>>
    priorityQueue;

void ConstructTrajFromLastIndex(
    const absl::flat_hash_map<uint64_t, AStarSearchNode> &nodes_map,
    uint64_t goal_index,
    std::vector<ApolloTrajectoryPointProto> &traj_points);

bool ReachGoal(const GeometryGraph &geom_graph,
               AStarSearchNode &current_node,
               double goal_s,
               bool is_lane_change,
               const InitializerConfig &initializer_params,
               const InitializerSceneType init_scene_type);

void ComputeHCost(AStarSearchNode *ptr_search_node,
                  const GeometryGraph &geom_graph,
                  double heurstic_s,
                  double h2g_ratio,
                  bool is_lane_change,
                  const InitializerConfig &initializer_params,
                  const InitializerSceneType init_scene_type);

void ComputeGCost(const CostProvider &cost_provider,
                  AStarSearchNode *ptr_search_node);

void ComputeDpLeadingObjCost(const CostProvider &cost_provider,
                             AStarSearchNode *ptr_action_info);

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
    uint64_t *node_index);

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
    std::vector<AStarSearchNode> &succ_search_nodes,
    uint64_t *node_index);

void CheckAndInsertOpenQueue(
    const AStarSearchNode &node_pred,
    std::vector<AStarSearchNode> &succ_search_nodes,
    absl::flat_hash_map<uint64_t, AStarSearchNode> &nodes_map,
    priorityQueue &open_queue,
    std::vector<SptDebugNode> *spt_search_tree);

void AddSearchTreeDebugMsg(const AStarSearchNode &candidate_node,
                           std::vector<SptDebugNode> *spt_search_tree);

}  // namespace planning
}  // namespace pnc_x
