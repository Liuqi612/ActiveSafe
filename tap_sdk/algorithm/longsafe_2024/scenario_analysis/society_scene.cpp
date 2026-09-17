#include "society_scene.h"

#include "math/lookuptable/lookuptable.h"
#include "society_scene_cal.h"

#include <array>
#include <cmath>
namespace senseAD {

namespace tap {

AsSocietyScene::AsSocietyScene() {
}

AsSocietyScene::~AsSocietyScene() = default;

AsSocietySceneParam society_param = AsSocietySceneParam{};

void AsSocietyScene::CheckSimulationMode() {
    if (!simulation_check) {
        simulation_check_cnt += 1;
        if (simulation_check_cnt < society_param.k_simulation_max_steps) {
            simulation_check = true;
        }
    }
}
void AsSocietyScene::ProcessSocietyScene(const active_safety::AsObstacleList &obj_list, const AsVseOut &vse_out, const AsParamConfig_T &longparam) {

    // 1. 更新核心成员变量（封装为函数，提高可读性和可维护性）
    UpdateEgoVehicleState(vse_out);

    // 2. 判断自动驾驶状态（语义化命名，避免魔法数字）
    is_auto_driving_ = IsEgoInAutoDrivingState(vse_out);

    test_scene_enabled = longparam.k_LgSf_EnTestScene;

    CheckSimulationMode();

    CheckTestSceneBaseEgoInfo(obj_list);
}
void AsSocietyScene::UpdateEgoVehicleState(const AsVseOut &vse_out) {
    ego_ = vse_out;
    // 速度转换：m/s -> km/h（
    display_spd_kph_ = ego_.speed * 3.6;
}

/**
 * @brief 判断自车是否处于自动驾驶状态
 * @param vse_out 车辆状态输出
 * @return true-自动驾驶中，false-非自动驾驶
 * @note 状态机值10代表自动驾驶（需确认该魔法数字的语义，建议用枚举替代）
 */
bool AsSocietyScene::IsEgoInAutoDrivingState(const AsVseOut &vse_out) {
    // 定义魔法数字为常量，提高可读性和可维护性
    constexpr int AUTO_DRIVING_STATE_MACHINE_VALUE = 10;
    return (vse_out.state_machine_sts == AUTO_DRIVING_STATE_MACHINE_VALUE);
}
void AsSocietyScene::CheckAroundCar(const active_safety::AsObstacle &obj) {
    // 1. 后方移动车辆（速度>5kph，纵向-20~0m，横向<2m）
    if ((obj.speed > 5) && (-20.0 < obj.long_posn) && (obj.long_posn < 0) && (abs(obj.lat_posn) < 2)) {
        backforward_moving_car += 1;
    }
    // 2. 直道路径内车辆（曲率<0.001，纵向-15~10m，横向<1.5m，非仿真模式）
    if ((abs(ego_.rear_curvature) < 0.001) && (-15.0 < obj.long_posn) && (!simulation_check) && (obj.long_posn < 10) && (abs(obj.lat_posn) < 1.5)) {

        ego_stright_inpath_car += 1;
    }
    // 3. 弯道前方移动车辆（曲率>0.001，纵向5~15m，速度>3kph，横向<3m）
    if ((abs(ego_.rear_curvature) > 0.001) && (5.0 < obj.long_posn) && (obj.long_posn < 15) && (obj.long_vel > 3) && (abs(obj.lat_posn) < 3)) {
        tap_moving_forward_car += 1;
    }
}
void AsSocietyScene::CheckAroundTruck(const active_safety::AsObstacle &obj) {
    // 1. 后方移动卡车（速度>4kph，纵向-30~30m，横向<7m）
    if ((obj.speed > 4) && (-30.0 < obj.long_posn) && (obj.long_posn < 30) && (abs(obj.lat_posn) < 7)) {
        backforward_moving_truck += 1;
    }
    // 2. 后方近距离卡车（纵向-10~10m，横向<5m）
    if ((-10.0 < obj.long_posn) && (obj.long_posn < 10) && (abs(obj.lat_posn) < 5)) {
        backforward_moving_truck += 1;
    }
}

void AsSocietyScene::CheckEgoFromStationaryToStart() {

    // 1. 判断当前自车是否静止（速度≤0kph时判定为静止）
    bool ego_stationary_current = (display_spd_kph_ <= 4.0 * 3.6);
    bool is_ego_stationary_to_start = !ego_stationary_current && pre_ego_stationary_;

    // 2. 检测自车从静止→启动的状态切换
    if (is_ego_stationary_to_start) {
        // 批量重置速度确认计数（避免重复赋值）
        ResetEgoSpeedConfirmCounters();
        // 批量重置速度未达标延迟计数
        ResetEgoSpeedDelayCounters();
        // 标记自车从静止启动
        is_ego_stationary_to_start = true;
    }

    // 3. 更新启动后有效时间窗口计数
    UpdateEgoStartValidTimeCounter(is_ego_stationary_to_start);

    // 4. 更新自车静止状态的历史值（供下一次检测使用）
    pre_ego_stationary_ = ego_stationary_current;
}

// 辅助函数：重置速度确认计数（封装重复逻辑，提升可读性）
void AsSocietyScene::ResetEgoSpeedConfirmCounters() {
    ego_10kph_confirm_cnt = 0;
    ego_20kph_confirm_cnt = 0;
    ego_30kph_confirm_cnt = 0;
    ego_40kph_confirm_cnt = 0;
    ego_50kph_confirm_cnt = 0;
    ego_60kph_confirm_cnt = 0;
}

// 辅助函数：重置速度未达标延迟计数
void AsSocietyScene::ResetEgoSpeedDelayCounters() {
    ego_not_10kph_delay_cnt = 0;
    ego_not_20kph_delay_cnt = 0;
    ego_not_30kph_delay_cnt = 0;
    ego_not_40kph_delay_cnt = 0;
    ego_not_50kph_delay_cnt = 0;
    ego_not_60kph_delay_cnt = 0;
}
// 辅助函数：更新启动后有效时间窗口计数
void AsSocietyScene::UpdateEgoStartValidTimeCounter(const bool is_ego_started) {
    if (is_ego_started) {
        // 启动时重置有效时间为配置值
        validtime_after_ego_start_cnt = society_param.k_stationary2start_max_valid_time;
    } else {
        // 非启动状态时递减计数，且不允许小于0（避免负数计数）
        validtime_after_ego_start_cnt = std::max(0, validtime_after_ego_start_cnt - 1);

        // 强制禁用启动状态时，直接清零计数
        if (ego_just_start_state_disabled) {
            validtime_after_ego_start_cnt = 0;
        }
    }

    // 更新启动后有效时间窗口的状态标记
    within_validtime_after_ego_start_ = (validtime_after_ego_start_cnt > 0);
}

// 核心功能：检测自车各恒定车速状态并更新相关计数
void AsSocietyScene::CheckEgoConstantSpeedDuration() {
    // 1. 预计算通用判断条件：曲率是否符合要求
    const bool is_curvature_valid = (abs(ego_.rear_curvature) < society_param.k_constant_spd_allow_max_curv);

    // 2. 构造各车速检测参数列表
    std::vector<SpeedCheckParam> speed_check_params = {
        {10, society_param.k_constand_spd_max_err, ego_10kph_confirm_cnt, ego_10kph_confirmeok, ego_not_10kph_delay_cnt, society_param.k_DecStep,
         society_param.k_ego_constant_spd_cnt_thrd},
        {20, society_param.k_constand_spd_max_err, ego_20kph_confirm_cnt, ego_20kph_confirmeok, ego_not_20kph_delay_cnt, society_param.k_DecStep,
         society_param.k_ego_constant_spd_cnt_thrd},
        {30, society_param.k_constand_spd_max_err, ego_30kph_confirm_cnt, ego_30kph_confirmeok, ego_not_30kph_delay_cnt, society_param.k_DecStep,
         society_param.k_ego_constant_spd_cnt_thrd},
        {40, society_param.k_constand_spd_max_err, ego_40kph_confirm_cnt, ego_40kph_confirmeok, ego_not_40kph_delay_cnt, society_param.k_DecStep,
         society_param.k_ego_constant_spd_cnt_thrd},
        {50, society_param.k_constand_spd_max_err, ego_50kph_confirm_cnt, ego_50kph_confirmeok, ego_not_50kph_delay_cnt, society_param.k_DecStep,
         society_param.k_ego_constant_spd_cnt_thrd},
        {60, society_param.k_constand_highspd_max_err, ego_60kph_confirm_cnt, ego_60kph_confirmeok, ego_not_60kph_delay_cnt, society_param.k_DecStep,
         society_param.k_ego_constant_highspd_cnt_thrd},
        {70, society_param.k_constand_spd_max_err, ego_70kph_confirm_cnt, ego_70kph_confirmeok, ego_not_70kph_delay_cnt, society_param.k_DecStep,
         society_param.k_ego_constant_spd_cnt_thrd},
        {80, society_param.k_constand_highspd_max_err, ego_80kph_confirm_cnt, ego_80kph_confirmeok, ego_not_80kph_delay_cnt, society_param.k_DecStep,
         society_param.k_ego_constant_highspd_cnt_thrd}};

    // 3. 遍历检测各车速状态
    for (auto &param : speed_check_params) {
        UpdateSpeedConfirmState(param, is_curvature_valid);
    }

    // 4. 更新各场景下的恒定车速标记
    UpdateEgoConstantSpeedFlags();
}

// 辅助函数：更新单个车速的确认状态和计数
void AsSocietyScene::UpdateSpeedConfirmState(SpeedCheckParam &param, bool is_curvature_valid) {
    // 判定当前车速是否在目标车速的误差范围内
    const bool is_speed_in_range =
        (display_spd_kph_ > (param.target_speed - param.speed_err)) && (display_spd_kph_ < (param.target_speed + param.speed_err));

    if (is_speed_in_range && is_curvature_valid) {
        // 车速符合要求：累加计数，且不超过上限
        param.confirm_cnt = std::min(param.confirm_cnt + 1, society_param.k_MaxConfirmCount);
    } else {
        // 车速不符合要求：分状态处理计数
        if (!param.confirm_ok) {
            // 未确认恒定车速：递减计数，且不低于0
            param.confirm_cnt = std::max(param.confirm_cnt - param.dec_step, 0);
        } else {
            // 已确认恒定车速：累加延迟计数，超过阈值则清零确认计数
            param.not_speed_delay_cnt += 1;
            if (param.not_speed_delay_cnt > society_param.k_ego_not_constant_spd_cnt_thrd) {
                param.confirm_cnt = 0;
            }
        }
    }

    // 简化布尔赋值：计数超过阈值则确认恒定车速，否则未确认
    param.confirm_ok = (param.confirm_cnt > param.confirm_thrd);
}
void AsSocietyScene::UpdateEgoConstantSpeedFlags() {
    // 转弯场景恒定车速（低车速）
    ego_during_turn_constant_spd_ = ego_10kph_confirmeok || ego_20kph_confirmeok || ego_30kph_confirmeok;
    // 直道场景恒定车速（全车速）
    ego_during_stright_constant_spd_ =
        ego_10kph_confirmeok || ego_20kph_confirmeok || ego_30kph_confirmeok || ego_40kph_confirmeok || ego_50kph_confirmeok || ego_60kph_confirmeok;
    // 交叉场景恒定车速（偶数车速）
    ego_cross_constant_spd_ = ego_20kph_confirmeok || ego_40kph_confirmeok || ego_60kph_confirmeok;
  
}
void AsSocietyScene::InvalidateEgoJustStartState() {
    if ((backforward_moving_car > 0) || (backforward_moving_truck > 0) || (ego_stright_inpath_car > 0) || (tap_moving_forward_car > 0) ||
        (ego_.gas_pedal_pos > society_param.k_disable_testscene_accel_pose_thd) || is_auto_driving_ ||
        (ego_.brake_pedal_pos > society_param.k_disable_testscene_brake_pose_thd) || simulation_check) {
        ego_just_start_state_disabled = true;
    } else {
        ego_just_start_state_disabled = false;
    }
}
void AsSocietyScene::CheckTestSceneBaseEgoInfo(const active_safety::AsObstacleList &obj_list) {

    CheckSurroundingEnvironment(obj_list);
    InvalidateEgoJustStartState();
    CheckEgoFromStationaryToStart();
    CheckEgoConstantSpeedDuration();

    UpdateEgoTestSceneState();
    UpdateEgoTurnSceneState();

    // if(ego_at_test_scene_){
    // std::cout<<"within_validtime_after_ego_start_" << static_cast<uint16_t>(within_validtime_after_ego_start_)
    //          << "validtime_after_ego_start_cnt" << validtime_after_ego_start_cnt
    //          <<"ego_40kph_confirm_cnt" << ego_40kph_confirm_cnt
    //          << "ego_40kph_confirmeok" << ego_40kph_confirmeok
    //          << "ego_at_test_scene_" <<  static_cast<uint16_t>(ego_at_test_scene_)
    //           << "ego_.speed" <<  ego_.speed
    //          <<std::endl;}
}
void AsSocietyScene::UpdateEgoTestSceneState() {

    ego_at_test_scene_ = (within_validtime_after_ego_start_ && ego_during_stright_constant_spd_) || test_scene_enabled;
}
void AsSocietyScene::UpdateEgoTurnSceneState() {

    ego_at_turn_scene_ = (within_validtime_after_ego_start_ && ego_during_turn_constant_spd_) || test_scene_enabled;
}
void AsSocietyScene::CheckSurroundingEnvironment(const active_safety::AsObstacleList &obj_list) {
    for (const auto &obj_ptr : obj_list) { // 明确命名为obj_ptr，语义更清晰
        if (obj_ptr->object_class == active_safety::ObjectClass::CAR) {
            // 解引用shared_ptr，传递裸对象
            CheckAroundCar(*obj_ptr);
        } else if (obj_ptr->object_class == active_safety::ObjectClass::TRUCK) {
            CheckAroundTruck(*obj_ptr);
        }
    }
}
} // namespace tap
} // namespace senseAD
