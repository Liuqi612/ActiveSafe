
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "async/thread_pool.h"
#include "pncx_driving_style.pb.h"
#include "initializer/cost_provider.h"
#include "initializer/initializer_output.h"
#include "initializer/interactive_search/decision_extractor/object_decision.h"
#include "initializer/motion_graph.h"
#include "initializer/ref_speed_table.h"
#include "initializer/select_nudge_object.h"
#include "router/drive_passage.h"
#include "pncx_trajectory_point.pb.h"
#include "pncx_vehicle.pb.h"
#include <absl/container/flat_hash_set.h>
#include <absl/status/statusor.h>
#include <absl/strings/str_join.h>

namespace pnc_x {
namespace planning {

struct SingleTrajDebugInfo {
    std::vector<MotionEdgeIndex> terminated_edge_idxes;
    std::vector<std::vector<ApolloTrajectoryPointProto>> top_k_trajs;
    std::vector<double> top_k_total_costs;
    std::vector<MotionEdgeIndex> top_k_edges;
};

struct SingleTrajInfo {
    std::vector<std::string> leading_trajs;
    std::vector<ApolloTrajectoryPointProto> traj_points;
    NudgeInfos nudge_info;
    ObjectDecisions object_decisions;
    ObsDecisionGap obs_gap;
    MotionEdgeIndex last_edge_index;
    MotionEdgeVector<MotionSearchOutput::SearchCost> search_costs;
    std::vector<double> feature_costs;
    double total_cost;
    std::unique_ptr<MotionGraph> motion_graph;
    std::unique_ptr<RefSpeedTable> ref_speed_table;
    std::unique_ptr<CostProvider> cost_provider;
    IgnoreTrajMap ignored_trajs;
    SingleTrajDebugInfo debug_info;
    std::string GetLeadingObjTrajId() const {
        if (leading_trajs.empty()) {
            return "No leading trajectories.";
        } else {
            return absl::StrJoin(leading_trajs, ", ");
        }
    }
};

SpeedResponseStyle MappingLongResponseLevel(LaneChangeStage prev_lc_stage,
                                            double follower_max_decel,
                                            double leader_max_decel,
                                            const std::string &prefix);
absl::StatusOr<int> EvaluateMultiTrajs(
    const DrivePassage &passage,
    const ApolloTrajectoryPointProto &start_point,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const std::vector<SingleTrajInfo> &multi_trajs,
    const VehicleGeometryParamsProto &vehicle_geom,
    bool eval_safety,
    LaneChangeStyle lc_style,
    const pnc_x::LaneChangeStage &lc_state,
    const pnc_x::LaneChangeStage &prev_lc_stage,
    absl::Duration path_look_ahead_duration,
    absl::flat_hash_set<std::string> *follower_set,
    absl::flat_hash_set<std::string> *leader_set,
    double *follower_max_decel,
    double *leader_max_decel,
    absl::flat_hash_set<std::string> *unsafe_object_ids,
    PlannerStatusProto::PlannerStatusCode *status_code,
    ThreadPool *thread_pool,
    int plan_id,
    bool is_borrow);

}  // namespace planning
}  // namespace pnc_x
