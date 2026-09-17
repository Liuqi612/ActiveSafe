
#pragma once

#include <boost/optional.hpp>
#include <string>
#include <vector>

#include <absl/time/time.h>

#include "pncx_perception.pb.h"
#include "plan/trajectory_point.h"
#include "pncx_planner.pb.h"
#include "pncx_planner_params.pb.h"
#include "pncx_positioning.pb.h"
#include "pncx_selector_params.pb.h"
#include "pncx_trajectory.pb.h"
#include "pncx_trajectory_point.pb.h"
#include "pncx_vehicle.pb.h"

struct VehiclePose {
    double x;
    double y;
    double heading;
};

struct LineEquation {
    double A;
    double B;
    double C;
};

namespace pnc_x {
namespace planning {

double ComputeLongitudinalJerk(const TrajectoryPoint &traj_point);
double ComputeLateralAcceleration(const TrajectoryPoint &traj_point);
double ComputeLateralJerk(const TrajectoryPoint &traj_point);

bool IsVulnerableRoadUserType(ObjectType type);
bool IsStaticObjectType(ObjectType type);

std::vector<ApolloTrajectoryPointProto> CreatePastPointsList(
    absl::Time plan_time,
    const TrajectoryProto &prev_traj,
    bool reset,
    ResetReasonProto::Reason reset_reason,
    int max_past_point_num);

ApolloTrajectoryPointProto ComputePlanStartPointAfterReset(
    const boost::optional<ApolloTrajectoryPointProto> &prev_reset_planned_point,
    const PoseProto &pose,
    double front_wheel_angle,
    const MotionConstraintParamsProto &motion_constraint_params,
    const VehicleGeometryParamsProto &vehicle_geom_params,
    const VehicleDriveParamsProto &vehicle_drive_params,
    bool is_forward_task);

ApolloTrajectoryPointProto ComputePlanStartPointAfterLateralReset(
    const boost::optional<ApolloTrajectoryPointProto> &prev_reset_planned_point,
    const PoseProto &pose,
    double front_wheel_angle,
    const VehicleGeometryParamsProto &vehicle_geom_params,
    const VehicleDriveParamsProto &vehicle_drive_params);

ApolloTrajectoryPointProto
ComputePlanStartPointAfterLongitudinalResetFromPrevTrajectory(
    const TrajectoryProto &prev_traj,
    const PoseProto &pose,
    double front_wheel_angle,
    const VehicleGeometryParamsProto &vehicle_geom_params,
    const VehicleDriveParamsProto &vehicle_drive_params);

SelectorParamsProto LoadSelectorParamsFromFile(const std::string &file_address);
LineEquation GetLineEquation(const VehiclePose &pos);
boost::optional<std::pair<double, double>> CalculateIntersection(
    const VehiclePose &pos1, const VehiclePose &pos2);
std::vector<VehiclePose> PredictEgoTrajectory(double x,
                                              double y,
                                              double heading,
                                              double v,
                                              double yaw_rate,
                                              double delta_t,
                                              int steps);

}  // namespace planning
}  // namespace pnc_x
