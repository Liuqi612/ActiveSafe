
#pragma once

#include <memory>
#include <optional>
#include <string_view>
#include <vector>

#include "common/path_sl_boundary.h"
#include "decision/constraint_manager.h"
#include "initializer/select_nudge_object.h"
#include "optimization/ddp/path_time_corridor.h"
#include "optimization/ddp/trajectory_optimizer_defs.h"
#include "optimization/problem/center_line_query_helper.h"
#include "optimization/problem/cost.h"
#include "math/rtree/boost_geometry_common.hpp"
#include "plan/trajectory_point.h"
#include "router/drive_passage.h"
#include "util/hmi_content_util.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {
namespace optimizer {

void AddStaticBoundaryCosts(
    int trajectory_steps,
    std::string base_name,
    int frame_id,
    long long stamp_us,
    bool enable_three_point_turn,
    const TrajectoryPoint &plan_start_point,
    const DrivePassage &drive_passage,
    const NudgeInfos &nudge_info,
    const PathSlBoundary &path_sl_boundary,
    const std::vector<senseAD::planning_pilot::BgPolygon> *occ_polygon,
    const std::vector<double> &inner_path_boundary_gains,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    const std::unique_ptr<CenterLineQueryHelper<Mfob>> &stations_query_helper,
    const PathTimeCorridor *path_time_corridor,
    const boost::optional<double> &lane_width_curb_buffer_opt,
    const double lane_width,
    boost::optional<double> *extra_curb_buffer_opt,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs,
    const LaneChangeStage lc_stage,
    bool borrow_lane);

void AddSolidWhiteLineCost(
    int trajectory_steps,
    std::string base_name,
    const std::vector<TrajectoryPoint> &solver_init_traj,
    const ConstraintManager &constraint_manager,
    const TrajectoryPoint &plan_start_point,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    const std::unique_ptr<CenterLineQueryHelper<Mfob>> &stations_query_helper,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs);

}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
