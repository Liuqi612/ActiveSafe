
#pragma once

#include <limits>
#include <map>
#include <memory>

#include <string>
#include <utility>
#include <vector>

#include "pncx_constraint.pb.h"
#include "pncx_initializer.pb.h"
#include "initializer/cost_provider.h"
#include "initializer/motion_search_types.h"
#include "initializer/interactive_search/decision_extractor/object_decision.h"
#include "initializer/motion_graph.h"
#include "initializer/motion_state.h"
#include "initializer/select_nudge_object.h"
#include "util/hmi_content_util.h"
#include <absl/container/flat_hash_set.h>
namespace pnc_x {
namespace planning {

struct MotionSearchOutput {
    absl::Status result_status = absl::OkStatus();

    NudgeInfos nudge_info;
    ObjectDecisions object_decisions;
    ObsDecisionGap obs_gap;

    absl::flat_hash_set<std::string> follower_set;
    absl::flat_hash_set<std::string> leader_set;
    double follower_max_decel = 0.0;
    absl::flat_hash_set<std::string> unsafe_object_ids;

    bool is_lc_pause = false;
    std::vector<ApolloTrajectoryPointProto> traj_points;
    MotionEdgeIndex best_last_edge_index;

    struct SearchCost {
        std::vector<double> feature_cost;
        double cost_to_come = 0.0;
        double TotalCost() const { return cost_to_come; }
    };

    MotionEdgeVector<SearchCost> search_costs;
    boost::optional<int> first_safe_to_gap_index = boost::none;
    double min_cost;
    std::map<std::string, ConstraintProto::LeadingObjectProto> leading_trajs;

    std::unique_ptr<MotionGraph> motion_graph;

    std::unique_ptr<RefSpeedTable> ref_speed_table;

    std::unique_ptr<CostProvider> cost_provider;

    std::vector<MotionEdgeIndex> terminated_edge_idxes;
    std::vector<std::vector<ApolloTrajectoryPointProto>> top_k_trajs;
    std::vector<double> top_k_total_costs;
    std::vector<MotionEdgeIndex> top_k_edges;

    struct MultiTrajCandidate {
        std::vector<ApolloTrajectoryPointProto> trajectory;
        std::vector<std::string> leading_traj_ids;
        double total_cost;
        MotionEdgeIndex last_edge_index;
        std::vector<double> feature_costs;
        double final_cost;
        IgnoreTrajMap ignored_trajs;
    };
    std::vector<MultiTrajCandidate> multi_traj_candidates;

    struct IsFilteredReasons {
        bool is_out_of_bound = false;
        bool is_violating_stop_constraint = false;
        bool is_dynamic_collision = false;
        bool is_violating_leading_objects = false;
    };
    struct TrajectoryEvaluationDumping {
        double weighted_total_cost;
        std::vector<double> dumped_weights;
        std::vector<double> feature_costs;
        std::vector<ApolloTrajectoryPointProto> traj;
        IsFilteredReasons is_filtered_reasons;
    };
    TrajectoryEvaluationDumping expert_evaluation;
    std::vector<TrajectoryEvaluationDumping> candidates_evaluation;
    SpeedResponseStyle speed_response_style;
    PlannerStatusProto::PlannerStatusCode lc_status_code =
        PlannerStatusProto::OK;
    std::vector<double> thw;
};

struct InitializerOutput {
    absl::flat_hash_set<std::string> follower_set;
    absl::flat_hash_set<std::string> leader_set;
    double follower_max_decel = 0.0;
    bool is_lc_pause = false;
    std::vector<ApolloTrajectoryPointProto> traj_points;
    InitializerStateProto initializer_state;
    std::map<std::string, ConstraintProto::LeadingObjectProto> leading_trajs;
    NudgeInfos nudge_info;
    ObjectDecisions object_decisions;
    ObsDecisionGap obs_gap;

    SpeedResponseStyle speed_response_style;
    PlannerStatusProto::PlannerStatusCode lc_status_code =
        PlannerStatusProto::OK;
    bool is_init_follow_scene = false;
    std::string lc_lead_obj_id = "none";
    bool is_aeb_result = false;
    boost::optional<bool> is_modify_speed = boost::none;
};

struct ReferenceLineSearcherOutput {
    struct NodeInfo {
        double min_cost = std::numeric_limits<double>::infinity();
        GeometryEdgeIndex outgoing_edge_idx =
            static_cast<GeometryEdgeIndex>(-1);
        GeometryNodeIndex prev_node_idx = static_cast<GeometryNodeIndex>(-1);
    };

    struct EdgeInfo {
        std::vector<double> feature_costs;
        double sum_cost = 0.0;
    };

    std::vector<GeometryNodeIndex> nodes_list;
    std::vector<GeometryEdgeIndex> edges_list;
    std::vector<Vec2d> ref_line_points;
    double total_cost = 0.0;
    std::vector<double> feature_costs;

    std::unique_ptr<RefLineCostProvider> ptr_cost_provider;
    GeometryEdgeVector<EdgeInfo> cost_edges;
};

}  // namespace planning
}  // namespace pnc_x
