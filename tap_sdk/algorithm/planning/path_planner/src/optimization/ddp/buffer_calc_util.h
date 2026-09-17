#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "async/thread_pool.h"
#include "common/path_sl_boundary.h"
#include "pncx_constraint.pb.h"
#include "initializer/interactive_search/decision_extractor/object_decision.h"
#include "initializer/select_nudge_object.h"
#include "pncx_lane_change.pb.h"
#include "math/geometry/polygon2d.h"
#include "math/geometry/segment2d.h"
#include "math/piecewise_linear_function.h"
#include "math/vec.h"
#include "object/object_history.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "optimization/ddp/path_time_corridor.h"
#include "optimization/ddp/trajectory_optimizer_defs.h"
#include "optimization/problem/av_model_helper.h"
#include "optimization/problem/cost.h"
#include "plan/trajectory_point.h"
#include "router/drive_passage.h"
#include "util/hmi_content_util.h"
#include "pncx_vehicle.pb.h"
#include "optimization/problem/center_line_query_helper.h"

namespace pnc_x {
namespace planning {
namespace optimizer {

enum class TurnType;
struct NudgeBufferWeightInfo {
    std::vector<double> buffer_value;
    std::vector<bool> has_curb;
    std::vector<double> weight_gains;
};

class NudgeBufferManager {
 public:
    void CalcNudgeBuffers(
        const PathTimeCorridor &path_time_corridor,
        const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
        const std::vector<TrajectoryPoint> &prev_traje,
        const std::vector<TrajectoryPoint> &init_traj,
        const DrivePassage &drive_passage);

    const NudgeBufferWeightInfo GenerateNudgeBufferDynamic(
        const int plan_id,
        const LaneChangeStage lc_stage,
        const bool borrow_lane,
        const std::vector<SpacetimeObjectState> &states,
        const std::vector<pnc_x::planning::TrajectoryPoint> &init_traj,
        bool is_camera_object,
        const Vec2d &object_velocity,
        const Polygon2d &object_contour,
        const TrajectoryPoint &plan_start_point,
        const DrivePassage &drive_passage,
        const double lane_width,
        const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
        const VehicleGeometryParamsProto &veh_geo_params,
        const SpacetimeObjectTrajectory &traj,
        const PathSlBoundary &path_boundary,
        const PathTimeCorridor &path_time_corridor,
        pnc_x::planning::optimizer::TurnType ego_turn_type,
        const std::vector<pnc_x::planning::TrajectoryPoint> &prev_traj);

    const std::vector<double> GenerateNudgeBufferStationary(
        const int plan_id,
        const LaneChangeStage lc_stage,
        const std::vector<SpacetimeObjectState> &states,
        bool is_camera_object,
        bool is_static,
        const Vec2d &object_velocity,
        const Polygon2d &object_contour,
        const std::vector<pnc_x::planning::TrajectoryPoint> &init_traj,
        const DrivePassage &drive_passage,
        const double lane_width,
        const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
        const VehicleGeometryParamsProto &veh_geo_params,
        const SpacetimeObjectTrajectory &traj,
        const PathSlBoundary &path_boundary,
        const PathTimeCorridor &path_time_corridor,
        TurnType ego_turn_type);

    bool GenerateNudgeBufferUU(
        const int plan_id,
        double trajectory_time_step,
        std::string base_name,
        const LaneChangeStage lc_stage,
        const TrajectoryPoint &plan_start_point,
        const PathTimeCorridor &path_time_corridor,
        absl::Span<const SpacetimeObjectTrajectory *const> spacetime_trajs,
        double min_mirror_height_avg,
        double max_mirror_height_avg,
        const double lane_width_l,
        const double lane_width_r,
        const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
        const VehicleCircleModelParamsProto
            &trajectory_optimizer_vehicle_model_params,
        const VehicleGeometryParamsProto &veh_geo_params);

    friend void AddObjectCosts(
        const int plan_id,
        const LaneChangeStage lc_stage,
        const bool borrow_lane,
        const NudgeInfos &nudge_info,
        const ObjectDecisions &object_decisions,
        int dense_trajectory_steps,
        int sparse_trajectory_steps,
        double dense_trajectory_time_step,
        double sparse_trajectory_time_step,
        double avoid_dynamic_obj_early_time,
        std::string base_name,
        const std::vector<TrajectoryPoint> &init_traj,
        const DrivePassage &drive_passage,
        const PathSlBoundary &path_boundary,
        const PathTimeCorridor &path_time_corridor,
        const std::map<std::string, ConstraintProto::LeadingObjectProto>
            &leading_trajs,
        const SpacetimeTrajectoryManager &st_traj_mgr,
        const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
        const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
        const VehicleGeometryParamsProto &veh_geo_params,
        const MotionConstraintParamsProto &motion_constraint_params,
        const VehicleCircleModelParamsProto
            &trajectory_optimizer_vehicle_model_params,
        const std::unique_ptr<AvModelHelper<Mfob>> &av_model_helpers,
        const bool is_narrow_scene,
        std::vector<LeadingInfo> *leading_min_s,
        std::vector<double> *inner_path_boundary_gains,
        std::vector<std::unique_ptr<Cost<Mfob>>> *costs,
        ThreadPool *thread_pool,
        TurnType ego_turn_type,
        const std::vector<TrajectoryPoint> &prev_traj,
        const FrenetBox *ego_frenet_box,
        const double follow_time,
        const ObjectHistoryManager *obs_history,
        const boost::optional<bool> &is_modify_speed,
        const LaneChangeStateProto &lane_change_state,
        const NudgeObjectInfo *prev_nudge_object_info,
        const ApolloTrajectoryPointProto &plan_start_point,
        const std::unique_ptr<CenterLineQueryHelper<Mfob>>
            &stations_query_helper,
        std::vector<std::string> *static_object_ids);

 private:
    std::vector<std::map<mapping::ElementId, double>> uu_buffers_;
    std::vector<std::map<mapping::ElementId, double>> static_object_buffers_;
    std::vector<std::map<mapping::ElementId, std::vector<double>>>
        dynamic_object_buffers_;
};

}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
