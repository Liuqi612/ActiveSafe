
#pragma once

#include <boost/optional.hpp>
#include <string>
#include <vector>

#include "plan/trajectory_point.h"
#include "pncx_planner_params.pb.h"
#include "router/drive_passage.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

std::vector<TrajectoryPoint> SmoothTrajectoryByMixedFourthOrderDdp(
    int plan_id,
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
    const std::vector<TrajectoryPoint> &ref_traj,
    const DrivePassage &drive_passage,
    const std::string &owner,
    const TrajectorySmootherCostWeightParamsProto &smoother_params,
    const MotionConstraintParamsProto &motion_constraint_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const VehicleDriveParamsProto &veh_drive_params,
    boost::optional<double> *smooth_init_cost,
    const std::vector<double>& ref_ls);

}
}  // namespace pnc_x
