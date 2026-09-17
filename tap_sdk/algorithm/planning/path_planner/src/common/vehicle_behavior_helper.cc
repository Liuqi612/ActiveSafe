#include "common/vehicle_behavior_helper.h"

#include <algorithm>
#include <cmath>

#include "common/gflags.h"
#include "common/log.h"
#include "math/math_utils.h"
#include "math/piecewise_linear_function.h"
#include "math/util.h"
#include "math/vec.h"

namespace ads_x {
namespace planning {
VehicleBehaviorHelper::VehicleBehaviorHelper() {}

void VehicleBehaviorHelper::Init(const double speed,
                                 const double accel,
                                 const int thw_level,
                                 const int drive_style,
                                 const double pos_x,
                                 const double pos_y,
                                 const double pos_yaw,
                                 const pnc_x::Behavior_FunctionId func_id) {
    vehicle_speed_ = speed;
    vehicle_accel_ = accel;
    thw_level_ = thw_level;
    drive_style_ = drive_style;
    pos_x_ = pos_x;
    pos_y_ = pos_y;
    pos_yaw_ = pos_yaw;
    func_id_ = func_id;
    ResetOutput();
    return;
}

void VehicleBehaviorHelper::ResetOutput() {
    lon_type_ = 0;
    lon_info_ = 0;
    warning_info_ = 0;
    traffic_jam_state_ = false;
    hmi_acc_close_cut_in_infos_.clear();
    sharp_turn_speed_limit_map_.clear();
    emergency_braking_map_.clear();
    vehicle_is_in_sharpturn_ = false;

    is_large_vehicle_over_lane_ = false;
    is_evade_ = false;
    task_nums_ = 0;
    is_flash_cutin_ = false;
    st_nums_ = 0;
    flash_alert_ = 0;
    honk_alert_ = 0;
    nudge_max_l_ = 0.0;
    lane_merge_deceleration_ = false;
    stop_distance_ = -1.0;

    return;
}

double VehicleBehaviorHelper::GetVehicleSpeed() { return vehicle_speed_; }

double VehicleBehaviorHelper::GetVehicleAccel() { return vehicle_accel_; }

int VehicleBehaviorHelper::GetThwLevel() { return thw_level_; }

int VehicleBehaviorHelper::GetDriveStyle() { return drive_style_; }

double VehicleBehaviorHelper::GetVehiclePosX() { return pos_x_; }

double VehicleBehaviorHelper::GetVehiclePosY() { return pos_y_; }

double VehicleBehaviorHelper::GetVehiclePosYaw() { return pos_yaw_; }

void VehicleBehaviorHelper::SetLonType(int lon_type) {
    lon_type_ = lon_type;
    return;
}

int VehicleBehaviorHelper::GetLonType() { return lon_type_; }

void VehicleBehaviorHelper::SetLonInfo(int lon_info) {
    lon_info_ = lon_info;
    return;
}

int VehicleBehaviorHelper::GetLonInfo() { return lon_info_; }

void VehicleBehaviorHelper::SetWarningInfo(int warning_info) {
    warning_info_ = warning_info;
    return;
}

int VehicleBehaviorHelper::GetWarningInfo() { return warning_info_; }

void VehicleBehaviorHelper::SetLaneMergeDeceleration(
    bool lane_merge_deceleration) {
    lane_merge_deceleration_ = lane_merge_deceleration;
    return;
}

bool VehicleBehaviorHelper::GetLaneMergeDeceleration() {
    return lane_merge_deceleration_;
}

void VehicleBehaviorHelper::SetTrafficJamState(bool traffic_jam_state) {
    traffic_jam_state_ = traffic_jam_state;
    return;
}

bool VehicleBehaviorHelper::GetTrafficJamState() { return traffic_jam_state_; }

bool VehicleBehaviorHelper::GetTrafficJamKeepingState() {
    return FLAGS_planner_enable_traffic_jam_state_keeping &&
           traffic_jam_state_ && (thw_level_ == 0);
}

void VehicleBehaviorHelper::SetVehicleSharpTurn(bool vehicle_is_in_sharpturn) {
    vehicle_is_in_sharpturn_ = vehicle_is_in_sharpturn;
    return;
}
bool VehicleBehaviorHelper::GetVehicleSharpTurn() {
    return vehicle_is_in_sharpturn_;
}
int VehicleBehaviorHelper::GetPlanId() { return plan_id_; }
void VehicleBehaviorHelper::SetPlanId(int plan_id) {
    plan_id_ = plan_id;
    return;
}
void VehicleBehaviorHelper::SetSharpTurnSpeedLimitMap(int plan_id,
                                                      double speed_limit) {
    (void)sharp_turn_speed_limit_map_.emplace(plan_id, speed_limit);
}
std::unordered_map<int, double>
VehicleBehaviorHelper::GetSharpTurnSpeedLimitMap() {
    return sharp_turn_speed_limit_map_;
}

void VehicleBehaviorHelper::SetEmergencyBrakingMap(
    int plan_id, bool need_emergency_braking) {
    (void)emergency_braking_map_.emplace(plan_id, need_emergency_braking);
}
std::unordered_map<int, bool> VehicleBehaviorHelper::GetEmergencyBrakingMap() {
    return emergency_braking_map_;
}

void VehicleBehaviorHelper::SetNearestStopTLMap(
    int plan_id, NearestStopTLInfo stop_tl_info) {
    (void)nearest_stop_tl_map_.emplace(plan_id, stop_tl_info);
}
std::unordered_map<int, NearestStopTLInfo>
VehicleBehaviorHelper::GetNearestStopTLMap() {
    return nearest_stop_tl_map_;
}
void VehicleBehaviorHelper::SetIsLargevehicleOverLane(
    bool is_large_vehicle_over_lane) {
    is_large_vehicle_over_lane_ = is_large_vehicle_over_lane;
    return;
}
bool VehicleBehaviorHelper::GetIsLargevehicleOverLane() {
    return is_large_vehicle_over_lane_;
}
void VehicleBehaviorHelper::SetIsEvade(bool is_evade) {
    is_evade_ = is_evade;
    return;
}
bool VehicleBehaviorHelper::GetIsEvade() { return is_evade_; }
int VehicleBehaviorHelper::GetTaskNums() { return task_nums_; }
void VehicleBehaviorHelper::SetTaskNums(int task_nums) {
    task_nums_ = task_nums;
    return;
}
int VehicleBehaviorHelper::GetFlashHonkingStatus() { return fh_status_; }
void VehicleBehaviorHelper::SetFlashHonkingStatus(int fh_status) {
    fh_status_ = fh_status;
    return;
}
void VehicleBehaviorHelper::SetFlashCutin(bool is_flash_cutin) {
    is_flash_cutin_ = is_flash_cutin;
    return;
}
bool VehicleBehaviorHelper::GetFlashCutin() { return is_flash_cutin_; }
int VehicleBehaviorHelper::GetStNums() { return st_nums_; }
void VehicleBehaviorHelper::SetStNums(int st_nums) {
    st_nums_ = st_nums;
    return;
}

int VehicleBehaviorHelper::GetCruiseSpeed() { return cruise_speed_; }
void VehicleBehaviorHelper::SetCruiseSpeed(int cruise_speed) {
    cruise_speed_ = cruise_speed;
    return;
}

bool VehicleBehaviorHelper::GetMRCState() { return mrc_state_; }
void VehicleBehaviorHelper::SetMRCState(bool mrc_state) {
    mrc_state_ = mrc_state;
    return;
}
void VehicleBehaviorHelper::SetFlashAlert(int flash_alert) {
    flash_alert_ = flash_alert;
    return;
};
int VehicleBehaviorHelper::GetFlashAlert() { return flash_alert_; };
void VehicleBehaviorHelper::SetHonkAlert(int honk_alert) {
    honk_alert_ = honk_alert;
    return;
};
int VehicleBehaviorHelper::GetHonkAlert() { return honk_alert_; };
void VehicleBehaviorHelper::SetNudgeMaxL(double nudge_max_l) {
    nudge_max_l_ = nudge_max_l;
    return;
};
double VehicleBehaviorHelper::GetNudgeMaxL() { return nudge_max_l_; };
void VehicleBehaviorHelper::SetStopDistance(double stop_distance) {
    stop_distance_ = stop_distance;
    return;
}
double VehicleBehaviorHelper::GetStopDistance() { return stop_distance_; }
}  // namespace planning
}  // namespace ads_x