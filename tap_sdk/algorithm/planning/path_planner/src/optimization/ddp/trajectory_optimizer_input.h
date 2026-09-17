
#pragma once

#include <map>
#include <string>
#include <vector>

#include "common/path_sl_boundary.h"
#include "common/type_def.h"
#include "decision/constraint_manager.h"
#include "initializer/interactive_search/decision_extractor/object_decision.h"
#include "object/object_history.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "optimization/ddp/trajectory_optimizer_state.h"
#include "plan/trajectory_point.h"
#include "math/rtree/boost_geometry_common.hpp"
#include "pncx_planner.pb.h"
#include "pncx_planner_params.pb.h"
#include "router/drive_passage.h"
#include "scheduler/lane_evasion_status.h"
#include "util/hmi_content_util.h"
#include "pncx_vehicle.pb.h"
#include <absl/types/span.h>

namespace pnc_x {
namespace planning {
/**
 * @brief 存储前密后稀的采样策略信息
 */
struct SamplingTrajectoryInfo {
    int dense_trajectory_steps = 20;          // 密集轨迹步数
    int sparse_trajectory_steps = 15;         // 稀疏轨迹步数
    double dense_trajectory_time_step = 0.2;   // 密集轨迹时间步长
    double sparse_trajectory_time_step = 0.4;  // 稀疏轨迹时间步长
    int trajectory_steps = 10;                // 总时间步长
};

struct TrajectoryOptimizerInput {
    // absl::Span<const ApolloTrajectoryPointProto> trajectory;
    std::vector<ApolloTrajectoryPointProto> trajectory;

    NudgeInfos nudge_info;
    bool is_motion_aeb_result = false;
    ObjectDecisions object_decisions;
    ObsDecisionGap obs_gap;
    // absl::Span<const ApolloTrajectoryPointProto> previous_trajectory;
    std::vector<ApolloTrajectoryPointProto> previous_trajectory;


    boost::optional<TrajectoryOptimizerState> trajectory_optimizer_state;

    const SpacetimeTrajectoryManager *st_traj_mgr = nullptr;
    const SpacetimePlannerObjectTrajectories *st_planner_object_traj = nullptr;
    const DrivePassage *drive_passage = nullptr;
    const PathSlBoundary *path_sl_boundary = nullptr;
    // 规划 local 坐标下的 OCC polygon，供 DDP 直接转 curb-like segments。
    const std::vector<senseAD::planning_pilot::BgPolygon> *occ_polygon =
        nullptr;
    const ConstraintManager *constraint_mgr = nullptr;
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        *leading_trajs = nullptr;
    const LaneEvadeInfo *lane_evade_info = nullptr;
    ApolloTrajectoryPointProto plan_start_point;
    absl::Time plan_start_time;
    int plan_id = 0;
    bool borrow_lane = false;
    const std::vector<TrajectoryPoint> *captain_trajectory = nullptr;
    LaneChangeStage lc_stage;
    LaneChangeStateProto lane_change_state;
    ads_x::planning::PushDirection push_dir =
        ads_x::planning::PushDirection::Push_None;

    const TrajectoryOptimizerParamsProto *trajectory_optimizer_params = nullptr;
    const MotionConstraintParamsProto *motion_constraint_params = nullptr;
    const PlannerFunctionsParamsProto *planner_functions_params = nullptr;
    const PlannerVehicleModelParamsProto *vehicle_models_params = nullptr;
    const VehicleGeometryParamsProto *veh_geo_params = nullptr;
    const VehicleDriveParamsProto *veh_drive_params = nullptr;
    const NudgeObjectInfo *nudge_object_info = nullptr;
    const ads_x::planning::EntryFuncSmoothInfo *entry_func_smooth_info =
        nullptr;
    const FrenetBox *ego_frenet_box = nullptr;
    double dynamic_time_headway{};
    boost::optional<double> prev_time_headway = boost::none;
    const ObjectHistoryManager *obs_history = nullptr;
    boost::optional<bool> is_modify_speed = boost::none;

    bool is_quick_lane_change = false; // 快速变道标志位

    TrajectoryOptimizerInput() = default;
    TrajectoryOptimizerInput(const TrajectoryOptimizerInput &) = default;
};

}  // namespace planning
}  // namespace pnc_x
