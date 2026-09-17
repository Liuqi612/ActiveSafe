#pragma once

#include <memory>
#include <string>
#include <vector>

#include "common/plan_start_point_info.h"
#include "common/planning_macros.h"
#include "common/type_def.h"
#include "common/vehicle_behavior_helper.h"
#include "plan/planner_flags.h"
#include "pncx_planner_params.pb.h"

namespace ads_x {
namespace planning {

class VehicleSpeedConfigHelper {
 public:
    ~VehicleSpeedConfigHelper() = default;

    VehicleSpeedConfigHelper(VehicleSpeedConfigHelper &) = delete;
    void operator=(VehicleSpeedConfigHelper) = delete;

    static void Init();

    static double TransferVehicleSpd2SpdIndcd(const double &veh_speed_mps);

    static double TransferVehicleSpdIndcd2Spd(
        const double &veh_speed_indcd_mps);

    static double TransferVehicleSpdIndcd2Spd(
        const double &set_indcd_mps,
        const double &speed_dashboard_mps,
        const double &current_veh_speed_mps,
        double &last_filtered_error_mps);

    static void UpdateVehicleDynamicLimits(
        const pnc_x::MotionConstraintParamsProto &motion_constraint_params,
        const double speed,
        const int drive_style);

    static void UpdateVehicleDynamicLimitsWithStartPointInfo(
        const pnc_x::MotionConstraintParamsProto &motion_constraint_params,
        const double speed,
        const int drive_style,
        const pnc_x::planning::PlanStartPointInfo &plan_start_point_info,
        EmergencyBrakingState last_emergency_brake_state);

    static double GetMaxAcceleration();

    static double GetMaxDeceleration();

    static double GetMaxAccelJerk();

    static double GetMaxDecelJerk();

    static void UpdateVehicleInfo(const double speed, const double accel);

    static double GetVehicleSpeed();

    static double GetVehicleAccel();
    DECLARE_CLASS_SINGLETON(VehicleSpeedConfigHelper);

 private:
    static bool is_init_;
    const static std::vector<double> speed_indcb_map_;
    static std::vector<double> speed_local_map_;
    static double alpha_;
    static double max_acceleration_;
    static double max_deceleration_;
    static double max_accel_jerk_;
    static double max_decel_jerk_;
    static double vehicle_speed_;
    static double vehicle_accel_;
};

}  // namespace planning
}  // namespace ads_x
