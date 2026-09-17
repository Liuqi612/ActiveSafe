#pragma once

#include <memory>
#include <string>
#include <vector>

#include "pncx_behavior.pb.h"
#include "common/planning_macros.h"
#include "common/type_def.h"
#include "plan/planner_flags.h"
#include "pncx_planner_params.pb.h"

namespace ads_x {
namespace planning {

struct HmiAccCloseCutInInfo {
    std::string acc_close_cut_in_obj_id = "";
    int acc_close_cut_in_obj_type = 0;
    int acc_close_cut_in_warning_info = 0;
};

struct AccCipvLossState {
    bool cipv_loss = false;
    int debounce_count = 0;
};

struct EmergencyBrakingState {
    bool need_emergency_braking = false;
    int em_debounce_count = 0;
    int consume_time = 0;
};

struct NearestStopTLInfo {
    std::string id = "";
    double min_s = 1000.0;
};

enum VehicleDriveStyle {
    kDriveStyleDefault = 0,
    KDriveStyleConservative = 1,
    KDriveStyleStandard = 2,
    KDriveStyleAggressive = 3
};

class VehicleBehaviorHelper {
 public:
    ~VehicleBehaviorHelper() = default;

    VehicleBehaviorHelper(VehicleBehaviorHelper &) = delete;
    void operator=(VehicleBehaviorHelper) = delete;
    void Init(const double speed,
              const double accel,
              const int thw_level,
              const int drive_style,
              const double pos_x,
              const double pos_y,
              const double pos_yaw,
              const pnc_x::Behavior_FunctionId func_id);
    void ResetOutput();

    double GetVehicleSpeed();
    double GetVehicleAccel();
    int GetThwLevel();
    int GetDriveStyle();
    double GetVehiclePosX();
    double GetVehiclePosY();
    double GetVehiclePosYaw();
    void SetLonType(int lon_type);
    int GetLonType();
    void SetLonInfo(int lon_info);
    int GetLonInfo();
    void SetWarningInfo(int warning_info);
    int GetWarningInfo();
    void SetLaneMergeDeceleration(bool lane_merge_deceleration);
    bool GetLaneMergeDeceleration();
    void SetTrafficJamState(bool traffic_jam_state);
    bool GetTrafficJamState();
    bool GetTrafficJamKeepingState();
    bool GetVehicleSharpTurn();
    void SetVehicleSharpTurn(bool vehicle_is_in_sharpturn);
    int GetPlanId();
    void SetPlanId(int plan_id);
    std::unordered_map<int, double> GetSharpTurnSpeedLimitMap();
    void SetSharpTurnSpeedLimitMap(int plan_id, double speed_limit);
    std::unordered_map<int, bool> GetEmergencyBrakingMap();
    void SetEmergencyBrakingMap(int plan_id, bool need_emergency_braking);
    std::unordered_map<int, NearestStopTLInfo> GetNearestStopTLMap();
    void SetNearestStopTLMap(int plan_id, NearestStopTLInfo stop_tl_info);
    void SetIsLargevehicleOverLane(bool is_large_vehicle_over_lane);
    bool GetIsLargevehicleOverLane();
    void SetIsEvade(bool is_evade);
    bool GetIsEvade();
    void SetTaskNums(int task_nums);
    int GetTaskNums();
    void SetFlashHonkingStatus(int fh_status);
    int GetFlashHonkingStatus();
    void SetFlashCutin(bool is_flash_cutin);
    bool GetFlashCutin();
    void SetMRCState(bool MRC_state);
    bool GetMRCState();
    void SetStNums(int st_nums);
    int GetStNums();
    void SetCruiseSpeed(int cruise_speed);
    int GetCruiseSpeed();
    void SetFlashAlert(int flash_alert);
    int GetFlashAlert();
    void SetHonkAlert(int honk_alert);
    int GetHonkAlert();
    void SetNudgeMaxL(double nudge_max_l);
    double GetNudgeMaxL();
    void SetStopDistance(double stop_distance);
    double GetStopDistance();
    AccCipvLossState GetLastAccCipvLossState() const {
        return acc_cipv_loss_state_;
    }
    EmergencyBrakingState GetEmergencyBrakingState() const {
        return emergency_braking_state_;
    }
    void ClearNearestStopTLMap() { nearest_stop_tl_map_.clear(); }
    void ResetPlanId() { plan_id_ = -1; }

    void SetLastAccCipvLossState(const AccCipvLossState &state) {
        acc_cipv_loss_state_.cipv_loss = state.cipv_loss;
        acc_cipv_loss_state_.debounce_count = state.debounce_count;
    }

    AccCipvLossState ConsumeAccCipvLossState() {
        if (acc_cipv_loss_state_.debounce_count > 0) {
            --acc_cipv_loss_state_.debounce_count;
        }

        if (acc_cipv_loss_state_.debounce_count == 0) {
            acc_cipv_loss_state_.cipv_loss = false;
        }

        return acc_cipv_loss_state_;
    }

    void SetEmergencyBrakingState(const EmergencyBrakingState &state) {
        emergency_braking_state_.need_emergency_braking =
            state.need_emergency_braking;
        emergency_braking_state_.em_debounce_count = state.em_debounce_count;
    }

    EmergencyBrakingState ConsumeEmergencyBrakingState() {
        constexpr int kEnableEmergencyBrakingCount = 9;

        auto &state = emergency_braking_state_;
        auto &count = state.em_debounce_count;

        if (count > 0) {
            --count;
            if (count == 0) {
                state.need_emergency_braking = false;
            }
        }

        if (count == kEnableEmergencyBrakingCount &&
            state.need_emergency_braking) {
            state.consume_time++;
        } else {
            state.consume_time = 0;
        }

        return state;
    }

    void SetHmiAccCloseCutInInfos(
        HmiAccCloseCutInInfo hmi_acc_close_cut_in_info) {
        hmi_acc_close_cut_in_infos_.emplace_back(hmi_acc_close_cut_in_info);
    }

    std::vector<HmiAccCloseCutInInfo> GetHmiAccCloseCutInInfos() {
        return hmi_acc_close_cut_in_infos_;
    }

    DECLARE_CLASS_SINGLETON(VehicleBehaviorHelper);

 private:
    double vehicle_speed_ = 0.0;
    double vehicle_accel_ = 0.0;
    int thw_level_ = 1;
    int drive_style_ = 2;
    double pos_x_ = 0.0;
    double pos_y_ = 0.0;
    double pos_yaw_ = 0.0;
    pnc_x::Behavior_FunctionId func_id_ = pnc_x::Behavior_FunctionId_NONE;

    int lon_type_ = 0;
    int lon_info_ = 0;
    int warning_info_ = 0;
    std::vector<HmiAccCloseCutInInfo> hmi_acc_close_cut_in_infos_;

    bool traffic_jam_state_ = false;
    bool vehicle_is_in_sharpturn_ = false;
    bool lane_merge_deceleration_ = false;
    int plan_id_ = -1;
    std::unordered_map<int, double> sharp_turn_speed_limit_map_;
    std::unordered_map<int, NearestStopTLInfo> nearest_stop_tl_map_;

    AccCipvLossState acc_cipv_loss_state_ = {false, 0};
    EmergencyBrakingState emergency_braking_state_ = {false, 0};
    bool is_large_vehicle_over_lane_ = false;
    bool is_evade_ = false;
    int task_nums_ = 0;
    int fh_status_ = 0;
    bool is_flash_cutin_ = false;
    int st_nums_ = 0;
    int cruise_speed_ = 0;
    int flash_alert_ = 0;
    int honk_alert_ = 0;
    bool mrc_state_ = false;
    double nudge_max_l_ = 0.0;
    double stop_distance_ = -1.0;

    std::unordered_map<int, bool> emergency_braking_map_;
};

}  // namespace planning
}  // namespace ads_x
