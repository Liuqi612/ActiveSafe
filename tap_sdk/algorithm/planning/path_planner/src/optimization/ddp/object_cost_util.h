
#pragma once

#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "async/thread_pool.h"
#include "common/path_sl_boundary.h"
#include "pncx_constraint.pb.h"
#include "initializer/interactive_search/decision_extractor/object_decision.h"
#include "initializer/select_nudge_object.h"
#include "pncx_lane_change.pb.h"
#include "math/geometry/polygon2d.h"
#include "math/geometry/segment2d.h"
#include "math/vec.h"
#include "object/object_history.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "optimization/ddp/buffer_calc_util.h"
#include "optimization/ddp/path_time_corridor.h"
#include "optimization/ddp/trajectory_optimizer_defs.h"
#include "optimization/problem/av_model_helper.h"
#include "optimization/problem/cost.h"
#include "plan/trajectory_point.h"
#include "router/drive_passage.h"
#include "util/hmi_content_util.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

namespace optimizer {

enum class TurnType {
    kUnknown = 0,
    kStraight = 1,
    kLeftTurn = 2,
    kRightTurn = 3,
    kUTurn = 4,
};

void AddObjectCosts(
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
    const std::unique_ptr<CenterLineQueryHelper<Mfob>> &stations_query_helper,
    std::vector<std::string> *static_object_ids);

void CalcPartitionHalfContourInfo(const Vec2d &x,
                                  const Vec2d &obj_x,
                                  const Polygon2d &contour,
                                  double buffer,
                                  std::vector<Segment2d> *lines,
                                  Vec2d *ref_x,
                                  Vec2d *ref_tangent,
                                  double *offset);

int CalcObjectTrajectoryStepsByMaxTime(
    double max_time,
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step);

std::vector<SpacetimeObjectState> SampleObjectStates(
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
    int use_object_steps,
    bool ignore_after_frozen,
    absl::Span<const SpacetimeObjectState> states);

}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
