
#pragma once

#include <memory>
#include <vector>

#include "decision/constraint_manager.h"
#include "pncx_lane_change.pb.h"
#include "math/vec.h"
#include "optimization/ddp/trajectory_optimizer_defs.h"
#include "optimization/problem/center_line_query_helper.h"
#include "optimization/problem/cost.h"
#include "optimization/problem/segmented_speed_limit_cost_v2.h"
#include "pncx_optimizer.pb.h"
#include "plan/trajectory_point.h"
#include "router/drive_passage.h"
#include "pncx_vehicle.pb.h"
namespace pnc_x {
namespace planning {
namespace optimizer {

using SpeedlimitInfoPoint =
    SegmentedSpeedLimitCostV2<Mfob>::SpeedlimitInfoPoint;

struct SpeedZoneInfo {
    double s_start{0};
    double s_end{0};
    Vec2d x_start;
    Vec2d x_end;
    double target_speed{0};
};

namespace speedlimit {

void MergeSpeedLimitWithFirstStopLine(
    double first_stop_line_s,
    const Vec2d &first_stop_point,
    const std::vector<double> &station_points_s,
    const std::vector<Vec2d> &speed_limit_x,
    std::vector<double> *station_speed_limits,
    std::vector<std::vector<SpeedlimitInfoPoint>> *additional_speed_limits);

void MergeSpeedLimitWithSpeedZones(
    const std::vector<SpeedZoneInfo> &speed_zones,
    const std::vector<Vec2d> &station_points,
    std::vector<double> *station_speed_limits,
    std::vector<std::vector<SpeedlimitInfoPoint>> *additional_speed_limits);

std::vector<double> CreateSpatialRef(
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
    const TrajectoryPoint &plan_start_point,
    const std::vector<Vec2d> &station_points,
    const std::vector<double> &station_speed_limits,
    const std::vector<std::vector<SpeedlimitInfoPoint>>
        &additional_speed_limits,
    const std::vector<LeadingInfo> &leading_min_s,
    int step_count,
    double max_a,
    double min_a,
    double leading_s_offset);
}  // namespace speedlimit

void AddSpeedLimitCost(
    const LaneChangeStage lc_stage,
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
    const TrajectoryPoint &plan_start_point,
    const DrivePassage &drive_passage,
    const ConstraintManager &constraint_manager,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const MotionConstraintParamsProto &motion_constraint_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const std::unique_ptr<CenterLineQueryHelper<Mfob>> &stations_query_helper,
    const std::vector<LeadingInfo> &leading_min_s,
    double *ref_end_state_s,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs,
    TrajectoryOptimizerDebugProto *traj_opt_debug_proto,
    const bool borrow_lane);

}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
