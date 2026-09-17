#include <algorithm>
#include <cmath>

#include "common/gflags.h"
#include "common/log.h"
#include "common/vehicle_speed_config_helper.h"
#include "math/math_utils.h"
#include "math/piecewise_linear_function.h"
#include "math/util.h"
#include "math/vec.h"

namespace ads_x {
namespace planning {

double ComputeAlpha(double f_sample, double t_rise) {
    double f_cutoff = (0.35 / t_rise) * f_sample;
    double tau = 1.0 / (2.0 * M_PI * f_cutoff);
    double T = 1.0 / f_sample;
    return T / (T + tau);
}

double LowPassFilter(const double x, const double &y_prev, const double alpha) {
    double y_prev_res = ((1.0 - alpha) * y_prev) + (alpha * x);
    return y_prev_res;
}

bool VehicleSpeedConfigHelper::is_init_ = false;
double VehicleSpeedConfigHelper::alpha_ = 0.01;
double VehicleSpeedConfigHelper::max_acceleration_ = 5.0;
double VehicleSpeedConfigHelper::max_deceleration_ = -5.0;
double VehicleSpeedConfigHelper::max_accel_jerk_ = 5.0;
double VehicleSpeedConfigHelper::max_decel_jerk_ = -5.0;
double VehicleSpeedConfigHelper::vehicle_speed_ = 0.0;
double VehicleSpeedConfigHelper::vehicle_accel_ = 0.0;

const std::vector<double> VehicleSpeedConfigHelper::speed_indcb_map_ = {
    0.0, 8.33,  11.11, 13.89, 16.67, 19.44, 22.22,
    25,  27.78, 30.56, 33.33, 36.11, 38.89};

std::vector<double> VehicleSpeedConfigHelper::speed_local_map_ = {
    0.0, 8.33,  11.11, 13.89, 16.67, 19.44, 22.22,
    25,  27.78, 30.56, 33.33, 36.11, 38.89};

VehicleSpeedConfigHelper::VehicleSpeedConfigHelper() {}

void VehicleSpeedConfigHelper::Init() {
    if (!is_init_) {
        is_init_ = true;
    }
    VehicleSpeedConfigHelper::speed_local_map_ = {
        FLAGS_pnc_x_local_speed_0,   FLAGS_pnc_x_local_speed_30,
        FLAGS_pnc_x_local_speed_40,  FLAGS_pnc_x_local_speed_50,
        FLAGS_pnc_x_local_speed_60,  FLAGS_pnc_x_local_speed_70,
        FLAGS_pnc_x_local_speed_80,  FLAGS_pnc_x_local_speed_90,
        FLAGS_pnc_x_local_speed_100, FLAGS_pnc_x_local_speed_110,
        FLAGS_pnc_x_local_speed_120, FLAGS_pnc_x_local_speed_130,
        FLAGS_pnc_x_local_speed_140};

    double f_sample = 2000.0;
    double t_rise = 20.0;
    alpha_ = ComputeAlpha(f_sample, t_rise);
}

double VehicleSpeedConfigHelper::TransferVehicleSpd2SpdIndcd(
    const double &veh_speed_kph) {
    return 1.05 * veh_speed_kph;
}

double VehicleSpeedConfigHelper::TransferVehicleSpdIndcd2Spd(
    const double &veh_speed_indcd_mps) {
    return 1.05 * veh_speed_indcd_mps;
}

double VehicleSpeedConfigHelper::TransferVehicleSpdIndcd2Spd(
    const double &set_indcd_mps,
    const double &speed_dashboard_mps,
    const double &current_veh_speed_mps,
    double &last_filtered_error_mps) {
    double error = speed_dashboard_mps - current_veh_speed_mps;
    std::string last_filtered_error_mps_str =
        std::to_string(last_filtered_error_mps);
    last_filtered_error_mps =
        LowPassFilter(error, last_filtered_error_mps, alpha_);

    return set_indcd_mps - last_filtered_error_mps;
}

void VehicleSpeedConfigHelper::UpdateVehicleDynamicLimits(
    const pnc_x::MotionConstraintParamsProto &motion_constraint_params,
    const double speed,
    const int drive_style) {
    const pnc_x::PiecewiseLinearFunction<double> accel_max_plf(
        {0, 10.0 / 3.6, 40.0 / 3.6, 80.0 / 3.6, 120.0 / 3.6, 160.0 / 3.6},
        {1.7, 1.6, 1.15, 0.6, 0.4, 0.25});
    const pnc_x::PiecewiseLinearFunction<double> accel_jerk_max_plf(
        {0, 5.0, 20.0, 100.0}, {5.0, 5.0, 5.0, 5.0});
    max_acceleration_ = accel_max_plf(speed);
    max_accel_jerk_ = accel_jerk_max_plf(speed);

    if (speed < 0.05) {
        max_accel_jerk_ = std::fmin(max_accel_jerk_, 2.0);
    }
    if (true) {
        const pnc_x::PiecewiseLinearFunction<double> decel_max_plf(
            {0, 5.0, 20.0, 100.0}, {-5.0, -5.0, -3.5, -3.5});
        const pnc_x::PiecewiseLinearFunction<double> decel_jerk_max_plf(
            {0, 5.0, 20.0, 100.0}, {-5.0, -5.0, -2.5, -2.5});
        max_deceleration_ = decel_max_plf(speed);
        max_decel_jerk_ = decel_jerk_max_plf(speed);
    } else {
        max_deceleration_ = motion_constraint_params.max_deceleration();
        max_decel_jerk_ = motion_constraint_params.max_decel_jerk();
    }

    if (drive_style == 1) {
        max_acceleration_ *= FLAGS_planner_k_accel_comfort_drive_style;
    } else if (drive_style == 3) {
        max_acceleration_ *= FLAGS_planner_k_accel_effic_drive_style;
    } else {
        max_acceleration_ *= FLAGS_planner_k_accel_normal_drive_style;
    }

    std::string vehicle_limits_debug = absl::StrCat(
        "drive_style: ", drive_style, " max_acceleration_: ", max_acceleration_,
        " max_deceleration_: ", max_deceleration_,
        " max_accel_jerk_: ", max_accel_jerk_,
        " max_decel_jerk_: ", max_decel_jerk_);
    return;
}

void VehicleSpeedConfigHelper::UpdateVehicleDynamicLimitsWithStartPointInfo(
    const pnc_x::MotionConstraintParamsProto &motion_constraint_params,
    const double speed,
    const int drive_style,
    const pnc_x::planning::PlanStartPointInfo &plan_start_point_info,
    EmergencyBrakingState last_emergency_brake_state) {
    const double start_v = plan_start_point_info.start_point.v();
    const double start_a = plan_start_point_info.start_point.a();

    constexpr int kEnableEmergencyBrakingCount = 4;
    const bool emergency_active =
        last_emergency_brake_state.need_emergency_braking &&
        (last_emergency_brake_state.consume_time >= kEnableEmergencyBrakingCount);

    const pnc_x::PiecewiseLinearFunction<double> accel_max_plf(
        {0, 10.0 / 3.6, 40.0 / 3.6, 80.0 / 3.6, 120.0 / 3.6, 160.0 / 3.6},
        {1.7, 1.6, 1.15, 0.6, 0.4, 0.25});
    const pnc_x::PiecewiseLinearFunction<double> accel_jerk_max_plf(
        {0, 5.0, 20.0, 100.0}, {5.0, 5.0, 5.0, 5.0});

    max_acceleration_ = accel_max_plf(start_v);
    max_accel_jerk_ = accel_jerk_max_plf(start_v);

    if (speed < 0.05) {
        max_accel_jerk_ = std::fmin(max_accel_jerk_, 2.0);
    }

    if (true) {
        const pnc_x::PiecewiseLinearFunction<double> decel_max_plf(
            {0, 5.0, 20.0, 100.0}, {-5.0, -5.0, -3.5, -3.5});
        const pnc_x::PiecewiseLinearFunction<double> decel_max_plf2(
            {0, 5.0, 20.0, 100.0}, {-6.5, -6.5, -5.0, -5.0});

        const pnc_x::PiecewiseLinearFunction<double> decel_jerk_max_plf(
            {0, 5.0, 20.0, 100.0}, {-5.0, -5.0, -2.5, -2.5});
        const pnc_x::PiecewiseLinearFunction<double> decel_jerk_max_plf2(
            {0, 5.0, 20.0, 100.0}, {-5.0, -5.0, -3.5, -3.5});

        if (emergency_active) {
            max_deceleration_ = decel_max_plf2(start_v);
            max_decel_jerk_ = decel_jerk_max_plf2(start_v);
        } else {
            max_deceleration_ =
                std::fmin(decel_max_plf(start_v), start_a - 0.1);
            max_decel_jerk_ = decel_jerk_max_plf(start_v);
        }
    } else {
        max_deceleration_ = motion_constraint_params.max_deceleration();
        max_decel_jerk_ = motion_constraint_params.max_decel_jerk();
    }

    if (drive_style == 1) {
        max_acceleration_ *= FLAGS_planner_k_accel_comfort_drive_style;
    } else if (drive_style == 3) {
        max_acceleration_ *= FLAGS_planner_k_accel_effic_drive_style;
    } else {
        max_acceleration_ *= FLAGS_planner_k_accel_normal_drive_style;
    }

    return;
}

double VehicleSpeedConfigHelper::GetMaxAcceleration() {
    return max_acceleration_;
}

double VehicleSpeedConfigHelper::GetMaxDeceleration() {
    return max_deceleration_;
}

double VehicleSpeedConfigHelper::GetMaxAccelJerk() { return max_accel_jerk_; }

double VehicleSpeedConfigHelper::GetMaxDecelJerk() { return max_decel_jerk_; }

void VehicleSpeedConfigHelper::UpdateVehicleInfo(const double speed,
                                                 const double accel) {
    vehicle_speed_ = speed;
    vehicle_accel_ = accel;
    return;
}

double VehicleSpeedConfigHelper::GetVehicleSpeed() { return vehicle_speed_; }

double VehicleSpeedConfigHelper::GetVehicleAccel() { return vehicle_accel_; }

}  // namespace planning
}  // namespace ads_x
