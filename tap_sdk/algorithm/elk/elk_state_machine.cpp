#include "elk_state_machine.h"

#include "ad_log/ad_log.hpp"
#include "common/enum_type.h"

#include <algorithm>

namespace active_safety {
namespace elk {

namespace {
constexpr uint32_t kLatSafeFaultMask = 1U << static_cast<uint8_t>(FunctionDid::ELK); // function_did_config bit3: ELK fault inhibit

float clamp01(float value)
{
    return std::min(std::max(value, 0.0F), 1.0F);
}

float calcScore(float value, float threshold)
{
    if (threshold <= 0.001F) {
        return 0.0F;
    }
    return clamp01(value / threshold);
}
}

void ElkStateMachine::Update(const AsVseOut &vse_out,
                             const LanesInfo &road_info,
                             const LaneBoundaryParameters &lane_boundary,
                             const LaneCenterParameters &lane_center,
                             const ElkTaSl &ta_info,
                             const GlobalConfig &config)
{
    Update(vse_out, road_info, lane_boundary, lane_center, ta_info, config, vse_out.torsion_bar_trq);
}

void ElkStateMachine::Update(const AsVseOut &vse_out,
                             const LanesInfo &road_info,
                             const LaneBoundaryParameters &lane_boundary,
                             const LaneCenterParameters &lane_center,
                             const ElkTaSl &ta_info,
                             const GlobalConfig &config,
                             float elk_torsion_bar_trq)
{
    AD_LINFO(ElkStateMachine::Update) << "New state condition judge...";
    UpdateStateMachine(BuildCondition(vse_out, road_info, lane_boundary, lane_center, ta_info, config, elk_torsion_bar_trq));

    if (state_ != State::Left_Intervention) {
        elk_scenario_decider_.resetLeftActiveSource();
    }

    if (state_ != State::Right_Intervention) {
        elk_scenario_decider_.resetRightActiveSource();
    }
}

void ElkStateMachine::checkVehicleInhabit(const AsVseOut &vse_out, float elk_torsion_bar_trq)
{
    // vehicle inhabit in Diag
    diag_inhabit_mask_ = 0x0;

    // bit0: 档位不在D档
    if (vse_out.actual_gear != 3) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x1;
    }
    
    // bit1: AEB激活
    if (vse_out.aeb_active) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x2;
    }

    // bit2: EPS反馈not avaliable或故障
    if ((vse_out.lka_trq_ovl_dlvd_stat == 2) || (vse_out.lka_trq_ovl_dlvd_stat == 3)) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x4;
    }

    // bit3: 胎压报警
    if (vse_out.tire_presr_fault == 1) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x8;
    }

    // bit4: 车门打开
    if ((vse_out.fl_door_st == 1) || (vse_out.fr_door_st == 1) || (vse_out.rl_door_st == 1) || (vse_out.rr_door_st == 1)) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x10;
    }

    // bit5: 引擎盖或后备箱盖打开
    if (vse_out.trunk_st == 1) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x20;
    }

    // bit6: 安全带解开
    if (vse_out.driver_belt_switch_st == 0) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x40;
    }

    // bit7: ESC激活
    if (vse_out.vdc_active_st == 1) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x80;
    }

    // bit8: ABS激活
    if (vse_out.abs_active) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x100;
    }

    // bit9: TCS激活
    if (vse_out.tcs_active_st == 1) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x200;
    }

    // bit10: 车辆发生碰撞
    if (vse_out.veh_crash) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x400;
    }

    // bit11: 雨刮器处于快速档
    if (vse_out.front_wiper_work_st == 1) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x800;
    }

    // bit12: EPB拉起
    if (vse_out.epb_applied == 1) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x1000;
    }

    // bit13: 脱手
    if (hand_off_detector_.process(std::fabs(elk_torsion_bar_trq),
            elk_cals_.k_EVP_hands_on_wheel_torque_hi, elk_cals_.k_EVP_hands_on_wheel_torque_lo,
            elk_cals_.k_EVP_handson_delay_time, elk_cals_.k_EVP_handsoff_delay_time,
            elk_cals_.k_ELK_StepTime)
    ) {
        diag_inhabit_mask_ = diag_inhabit_mask_ + 0x2000;
    }
}

void ElkStateMachine::updateSteerTorqueSuppressHistory(bool suppress_condition,
                                                       std::array<bool, 10> &suppress_history,
                                                       std::size_t &suppress_history_index)
{
    // 写入当前帧结果后移动索引，下一次统计时从最新帧向前回看。
    suppress_history[suppress_history_index] = suppress_condition;
    suppress_history_index = (suppress_history_index + 1U) % suppress_history.size();
}

bool ElkStateMachine::isSteerTorqueHistorySuppressed(const std::array<bool, 10> &suppress_history,
                                                     std::size_t suppress_history_index) const
{
    // 以当前写入索引为环形缓存尾部，统计最近 N 帧内超过力矩阈值的帧数。
    const std::size_t history_window =
        std::min<std::size_t>(elk_cals_.k_ELK_DriHandsOvr_HistoryWindow, suppress_history.size());
    const std::size_t suppress_count =
        std::min<std::size_t>(elk_cals_.k_ELK_DriHandsOvr_HistorySuppressCount, history_window);
    if ((history_window == 0U) || (suppress_count == 0U)) {
        return false;
    }

    std::size_t satisfied_count = 0U;
    for (std::size_t i = 0U; i < history_window; ++i) {
        const std::size_t history_index =
            (suppress_history_index + suppress_history.size() - 1U - i) % suppress_history.size();
        if (suppress_history[history_index]) {
            ++satisfied_count;
        }
    }

    return satisfied_count >= suppress_count;
}

bool ElkStateMachine::updateDriverIntentScoreHistory(float driver_intent_score)
{
    driver_intent_score_history_[driver_intent_score_history_index_] = driver_intent_score;
    driver_intent_score_valid_history_[driver_intent_score_history_index_] = true;
    driver_intent_score_history_index_ =
        (driver_intent_score_history_index_ + 1U) % driver_intent_score_history_.size();
    driver_intent_score_valid_count_ =
        std::min<uint8_t>(static_cast<uint8_t>(driver_intent_score_valid_count_ + 1U),
                          static_cast<uint8_t>(driver_intent_score_history_.size()));

    const std::size_t required_frame_count =
        std::min<std::size_t>(elk_cals_.k_EVP_DriverIntent_HistoryFrameCount, driver_intent_score_history_.size());
    if (required_frame_count == 0U) {
        return false;
    }
    if (driver_intent_score_valid_count_ < required_frame_count) {
        return false;
    }

    for (std::size_t i = 0U; i < required_frame_count; ++i) {
        const std::size_t history_index =
            (driver_intent_score_history_index_ + driver_intent_score_history_.size() - 1U - i) %
            driver_intent_score_history_.size();
        if (!driver_intent_score_valid_history_[history_index] ||
            driver_intent_score_history_[history_index] < elk_cals_.k_EVP_DriverIntent_ScoreThr) {
            return false;
        }
    }

    return true;
}

void ElkStateMachine::checkDriverSuppression(
    const AsVseOut &vse_out, const LaneBoundaryParameters &lane_boundary, float elk_torsion_bar_trq)
{
    // common inhabit
    evp_disable_mask_ = 0x0;
    driver_false_trigger_debug_mask_ = 0U;
    const float veh_speed_kph = vse_out.display_speed;

    // bit0: 横摆角速度
    if (yawrate_inhabit_checker_.process(std::fabs(vse_out.yawrate),
            elk_cals_.k_EVP_yawrate_hi_thold, elk_cals_.k_EVP_yawrate_lo_thold,
            elk_cals_.k_EVP_yawrate_disable_time, elk_cals_.k_EVP_yawrate_enable_time,
            elk_cals_.k_ELK_StepTime, true, false)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x1;
    }
        
    // bit1: 制动踏板
    bool f_brake_prs_inhabit, b_brake_pedal_sprsn;
    constexpr float kpa2bar = 0.01F;
    const float brake_pressure_bar = kpa2bar * vse_out.brake_pressure;
    f_brake_prs_inhabit = brake_pressure_disable_checker_.process(brake_pressure_bar, 
        elk_cals_.k_EVP_brkPdPs_threshold_elk, elk_cals_.k_EVP_brkPdPs_threshold_elk - elk_cals_.k_EVP_brake_ped_pos_thold_HYS,
        elk_cals_.k_EVP_brake_pedal_hold, elk_cals_.k_ELK_StepTime);
    b_brake_pedal_sprsn = brake_pedal_inhabit_checker_.offDelay(f_brake_prs_inhabit && vse_out.brake_pedal_apld,
        elk_cals_.k_EVP_brake_suprress_hold, elk_cals_.k_ELK_StepTime);
    if (b_brake_pedal_sprsn) {
        evp_disable_mask_ = evp_disable_mask_ + 0x2;
    }

    // bit2: 加速踏板
    const bool low_speed_accel_pedal_suppress = low_speed_accel_pedal_inhabit_checker_.onDelay(
        (veh_speed_kph >= elk_cals_.k_EVP_LowSpd_AccelPedal_MinSpeedKph) &&
            (veh_speed_kph <= elk_cals_.k_EVP_LowSpd_AccelPedal_MaxSpeedKph) &&
            (vse_out.gas_pedal_pos > elk_cals_.k_EVP_LowSpd_AccelPedal_Thr),
        elk_cals_.k_EVP_LowSpd_AccelPedal_OnDelayTime, elk_cals_.k_ELK_StepTime);
    if (low_speed_accel_pedal_suppress) {
        driver_false_trigger_debug_mask_ |= (1U << 29U);
    }
    if (accel_pedal_inhabit_checker_.offDelay(vse_out.gas_pedal_pos > elk_cals_.k_EVP_accPdPs_inhibit_thr_elk,
        elk_cals_.k_EVP_accel_ped_suppress_hold, elk_cals_.k_ELK_StepTime)
        || low_speed_accel_pedal_suppress
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x4;
    }

    // bit3: 横向加速度
    if (lat_accel_inhabit_checker_.process(std::fabs(vse_out.lat_accel),
        elk_cals_.k_EVP_LatAccel_thold_up, elk_cals_.k_EVP_LatAccel_thold_lo,
        elk_cals_.k_EVP_HighAccel_suppress_hold, elk_cals_.k_ELK_StepTime,
        true, false)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x8;
    }

    // bit4: 纵向加速度
    if (lon_accel_inhabit_checker_.process(vse_out.long_accel,
        elk_cals_.k_EVP_LonAccel_thold_up, elk_cals_.k_EVP_LonAccel_thold_lo,
        elk_cals_.k_EVP_HighAccel_suppress_hold, elk_cals_.k_ELK_StepTime,
        true, false)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x10;
    }

    // bit5: 纵向减速度
    if (lon_decel_inhabit_checker_.process(-vse_out.long_accel,
        elk_cals_.k_EVP_LonDecel_thold_up, elk_cals_.k_EVP_LonDecel_thold_lo,
        elk_cals_.k_EVP_HighAccel_suppress_hold, elk_cals_.k_ELK_StepTime,
        true, false)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x20;
    }

    // bit6: 普通方向盘手力矩/override，用于 SLD/ROR 等非 LCT 目标源抑制。
    const float ovrdTrqThr = math::LookUpTable::LookupTable1D<7>(
        elk_cals_.k_ELK_ovrd_tq_thd_per_spd_x, elk_cals_.k_ELK_ovrd_tq_thd_per_spd_z, veh_speed_kph);
    const float lctOvrdTrqThr = math::LookUpTable::LookupTable1D<7>(
        elk_cals_.k_ELK_LCT_ovrd_tq_thd_per_spd_x, elk_cals_.k_ELK_LCT_ovrd_tq_thd_per_spd_z, veh_speed_kph);
    // ELK使用专用手力矩输入，避免VSE为其他功能清零该信号后影响ELK驾驶员接管抑制。
    updateSteerTorqueSuppressHistory(std::abs(elk_torsion_bar_trq) >= ovrdTrqThr,
        steer_torque_suppress_history_, steer_torque_suppress_history_index_);
    const bool steer_torque_history_suppressed =
        isSteerTorqueHistorySuppressed(steer_torque_suppress_history_, steer_torque_suppress_history_index_);
    if (steer_torque_history_suppressed) {
        driver_false_trigger_debug_mask_ |= (1U << 28U);
    }
    if (steer_torque_inhabit_checker_.process(steer_torque_history_suppressed ? 1.0F : 0.0F,
        1.0F, 0.0F,
        elk_cals_.k_ELK_DriHandsOvr_OnDlyTime, elk_cals_.k_ELK_DriHandsOvr_OffDlyTime,
        elk_cals_.k_ELK_StepTime, true, false)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x40;
    }

    // bit30: LCT OC/OT 目标源专用方向盘手力矩/override，使用更高起步阈值和独立 off-delay。
    updateSteerTorqueSuppressHistory(std::abs(elk_torsion_bar_trq) >= lctOvrdTrqThr,
        lct_steer_torque_suppress_history_, lct_steer_torque_suppress_history_index_);
    const bool lct_steer_torque_history_suppressed =
        isSteerTorqueHistorySuppressed(lct_steer_torque_suppress_history_, lct_steer_torque_suppress_history_index_);
    if (lct_steer_torque_inhabit_checker_.process(lct_steer_torque_history_suppressed ? 1.0F : 0.0F,
        1.0F, 0.0F,
        elk_cals_.k_ELK_DriHandsOvr_OnDlyTime, elk_cals_.k_ELK_LCT_DriHandsOvr_OffDlyTime,
        elk_cals_.k_ELK_StepTime, true, false)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + elk_cals_.k_EVP_LCT_DriHandsOvr_Suprsn_Bit;
    }

    // bit29: 综合驾驶员主观接管意图
    const float steer_score = calcScore(std::abs(elk_torsion_bar_trq), ovrdTrqThr);
    const float accel_score = calcScore(vse_out.gas_pedal_pos, elk_cals_.k_EVP_accPdPs_inhibit_thr_elk);
    const float brake_pressure_score = calcScore(brake_pressure_bar, elk_cals_.k_EVP_brkPdPs_threshold_elk);
    const float brake_pedal_score = calcScore(vse_out.brake_pedal_pos, elk_cals_.k_EVP_DriverIntent_BrakePedalThr);
    const float brake_score = std::max(brake_pressure_score, brake_pedal_score);
    const float pedal_score = std::max(accel_score, brake_score);
    const float driver_intent_score =
        elk_cals_.k_EVP_DriverIntent_SteerWeight * steer_score +
        elk_cals_.k_EVP_DriverIntent_PedalWeight * pedal_score;
    const bool driver_intent_suppress =
        driver_intent_inhabit_checker_.offDelay(updateDriverIntentScoreHistory(driver_intent_score),
            elk_cals_.k_EVP_DriverIntent_OffDelayTime, elk_cals_.k_ELK_StepTime);
    if (driver_intent_suppress) {
        driver_false_trigger_debug_mask_ |= (1U << 30U);
        evp_disable_mask_ = evp_disable_mask_ + elk_cals_.k_EVP_DriverIntent_Suprsn_Bit;
    }

    // bit7: 方向盘角度
    if (steer_angle_inhabit_checker_.process(std::fabs(vse_out.steerwheelangle),
        elk_cals_.k_EVP_SteerAngle_thold_up, elk_cals_.k_EVP_SteerAngle_thold_lo,
        elk_cals_.k_EVP_StrAng_CR_suppress_hold, elk_cals_.k_ELK_StepTime,
        true, false)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x80;
    }

    // bit8: 方向盘角速度
    float strAgSpd_thr;
    strAgSpd_thr = math::LookUpTable::LookupTable1D<5>(
        elk_cals_.k_EVP_StrAng_CR_thrd_x, elk_cals_.k_EVP_StrAng_CR_thrd_z, vse_out.display_speed);
    if (steer_angle_speed_inhabit_checker_.process(std::fabs(vse_out.steerwheelangle_rate),
        strAgSpd_thr, strAgSpd_thr - elk_cals_.k_EVP_StrAng_CR_threshold_HYS,
        elk_cals_.k_EVP_StrAng_CR_hold, elk_cals_.k_EVP_StrAng_CR_suppress_hold, elk_cals_.k_ELK_StepTime,
        true, false)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x100;
    }
    
    // bit9: 双闪
    if (hazard_lamp_checker_.offDelay(vse_out.hazard_lamp_st == 1, 
        elk_cals_.k_EVP_drvrSprsn_hold_time, elk_cals_.k_ELK_StepTime)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x200;
    }

    // left
    // bit10: 向左偏离车道线速度
    if (lane_boundary.lftBdryLatRt > elk_cals_.k_ELK_lat_rate_thold_max) {
        evp_disable_mask_ = evp_disable_mask_ + 0x400;
    }

    // bit11: 向左偏离路沿速度
    if (lane_boundary.lftEdgeLatRt > elk_cals_.k_ELK_ROR_lat_rate_thold_max) {
        evp_disable_mask_ = evp_disable_mask_ + 0x800;
    }

    // bit12: 左转向灯
    if (left_turn_lamp_inhabit_checker_.offDelay(vse_out.turn_light_switch_pos == 1, 
        elk_cals_.k_EVP_drvrSprsn_hold_time, elk_cals_.k_ELK_StepTime)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x1000;
    }

    // right
    // bit13: 向右偏离车道线速度
    if (lane_boundary.rgtBdryLatRt < -elk_cals_.k_ELK_lat_rate_thold_min) {
        evp_disable_mask_ = evp_disable_mask_ + 0x2000;
    }

    // bit14: 向右偏离路沿速度
    if (lane_boundary.rgtEdgeLatRt < -elk_cals_.k_ELK_ROR_lat_rate_thold_min) {
        evp_disable_mask_ = evp_disable_mask_ + 0x4000;
    }

    // bit15: 右转向灯
    if (right_turn_lamp_inhabit_checker_.offDelay(vse_out.turn_light_switch_pos == 3, 
        elk_cals_.k_EVP_drvrSprsn_hold_time, elk_cals_.k_ELK_StepTime)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x8000;
    }
}

void ElkStateMachine::checkEnvironmentSuppression(const LaneBoundaryParameters &lane_boundary)
{
    // bit16: 左侧车道线无效
    if (!lane_boundary.lftBdryVld) {
        evp_disable_mask_ = evp_disable_mask_ + 0x10000;
    }

    // bit17: 向左跃出车道线
    if (lane_boundary.lftLaneChange) {
        evp_disable_mask_ = evp_disable_mask_ + 0x20000;
    }

    // bit18: 左侧路沿无效
    if (!lane_boundary.lftEdgeVld) {
        evp_disable_mask_ = evp_disable_mask_ + 0x40000;
    }

     // bit19: 向左跃出车道
    if (lane_boundary.runOffRoadLft) {
        evp_disable_mask_ = evp_disable_mask_ + 0x80000;
    }

    // bit20: 左侧路沿长度无效
    if (!elk_scenario_decider_.isLeftEdgeRangeValid()) {
        evp_disable_mask_ = evp_disable_mask_ + 0x100000;
    }

    // bit21: 右侧车道线无效
    if (!lane_boundary.rgtBdryVld) {
        evp_disable_mask_ = evp_disable_mask_ + 0x200000;
    }

    // bit22: 向右跃出车道线
    if (lane_boundary.rgtLaneChange) {
        evp_disable_mask_ = evp_disable_mask_ + 0x400000;
    }

    // bit23: 右侧路沿无效
    if (!lane_boundary.rgtEdgeVld) {
        evp_disable_mask_ = evp_disable_mask_ + 0x800000;
    }

     // bit24: 向右跃出车道
    if (lane_boundary.runOffRoadRgt) {
        evp_disable_mask_ = evp_disable_mask_ + 0x1000000;
    }

    // bit25: 右侧路沿长度无效
    if (!elk_scenario_decider_.isRightEdgeRangeValid()) {
        evp_disable_mask_ = evp_disable_mask_ + 0x2000000;
    }

    // bit26: 2次激活间隔时间小于6s
    if (finish_checker_.offDelay((state_ == State::Completed) || (state_ == State::Abort),
        elk_cals_.k_ELK_ConIntervent_Time, elk_cals_.k_ELK_StepTime)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x4000000;
    }

    // bit27: 左侧激活时间超过7.5s
    if (left_interveention_checker_.onDelay(state_ == State::Left_Intervention,
        elk_cals_.k_ELK_Intervention_MaxTime, elk_cals_.k_ELK_StepTime)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x8000000;
    }

    // bit28: 右侧激活时间超过7.5s
    if (right_interveention_checker_.onDelay(state_ == State::Right_Intervention,
        elk_cals_.k_ELK_Intervention_MaxTime, elk_cals_.k_ELK_StepTime)
    ) {
        evp_disable_mask_ = evp_disable_mask_ + 0x10000000;
    }
}

ElkStateMachine::Condition ElkStateMachine::BuildCondition(const AsVseOut &vse_out,
                                                           const LanesInfo &road_info,
                                                           const LaneBoundaryParameters &lane_boundary,
                                                           const LaneCenterParameters &lane_center,
                                                           const ElkTaSl &ta_info,
                                                           const GlobalConfig &config,
                                                           float elk_torsion_bar_trq)
{
    bool b_left_triged, b_right_triged, b_left_suppression, b_right_suppression;
    Condition condition;
    const bool enabled = config.k_ELK_func_enable || (vse_out.elk_switch == 1U);
    const bool upstream_fault_inhibit = (vse_out.function_did_config & kLatSafeFaultMask) != 0U;
    const bool fault_inhibit = !config.k_LSS_IgnoreFaultInhibit && upstream_fault_inhibit;

    condition.fault_to_off = !fault_inhibit;
    condition.off_to_fault = fault_inhibit;

    condition.off_to_standby = enabled; // 软开关
    condition.standby_to_off = !enabled;

    // enable条件应该使用仪表车速，但是WI中CAN仪表车速接口没有赋值，用的是内部计算的
    checkVehicleInhabit(vse_out, elk_torsion_bar_trq);
    condition.standby_to_enable = checkStandby2Enable(vse_out.display_speed, lane_boundary);
    condition.enable_to_standby = checkEnable2Standby(vse_out.display_speed);
    condition.enable_to_off = !enabled;
    
    // intervention条件
    elk_scenario_decider_.resetTtcFalseTriggerDebugMask();
    const float veh_speed_mps = vse_out.display_speed / 3.6F;
    if (state_ == State::Left_Suppressed) {
        b_left_triged = elk_scenario_decider_.determineLeftInterventionForSuppressedExit(
            road_info, lane_boundary, ta_info, config,
            veh_speed_mps, left_marker_valid_checker_.getStateOut(), left_edge_valid_checker_.getStateOut());
        b_right_triged = false;
    } else if (state_ == State::Right_Suppressed) {
        b_left_triged = false;
        b_right_triged = elk_scenario_decider_.determineRightInterventionForSuppressedExit(
            road_info, lane_boundary, ta_info, config,
            veh_speed_mps, right_marker_valid_checker_.getStateOut(), right_edge_valid_checker_.getStateOut());
    } else {
        b_left_triged = elk_scenario_decider_.determineLeftIntervention(road_info, lane_boundary, ta_info, config,
            veh_speed_mps, left_marker_valid_checker_.getStateOut(), left_edge_valid_checker_.getStateOut());
        b_right_triged = elk_scenario_decider_.determineRightIntervention(road_info, lane_boundary, ta_info, config,
            veh_speed_mps, right_marker_valid_checker_.getStateOut(), right_edge_valid_checker_.getStateOut());
    }
    AD_LINFO(ElkStateMachine::BuildCondition) << "b_left_triged is: " << b_left_triged
        << ", b_right_triged is: " << b_right_triged;

    // abort条件
    checkDriverSuppression(vse_out, lane_boundary, elk_torsion_bar_trq);
    checkEnvironmentSuppression(lane_boundary);
    AD_LINFO(ElkStateMachine::BuildCondition) << "evp_disable_mask_ is: " << evp_disable_mask_;

    b_left_suppression = elk_scenario_decider_.determineLeftSuppression(evp_disable_mask_);
    b_right_suppression = elk_scenario_decider_.determineRightSuppression(evp_disable_mask_);

    AD_LINFO(ElkStateMachine::BuildCondition) << "b_left_suppression is: " << b_left_suppression
        << ", b_right_suppression is: " << b_right_suppression;

    condition.enable_to_left_intervention = b_left_triged && (!b_right_triged) && (!b_left_suppression);
    condition.enable_to_right_intervention = b_right_triged && (!b_left_triged) && (!b_right_suppression);

    condition.left_to_right_intervention = condition.enable_to_right_intervention;
    condition.right_to_left_intervention = condition.enable_to_left_intervention;

    condition.left_to_abort = b_left_suppression;
    condition.right_to_abort = b_right_suppression;

    // completed条件
    condition.left_to_completed = elk_scenario_decider_.checkLeftAligned(road_info, lane_boundary, lane_center, config);
    condition.right_to_completed = elk_scenario_decider_.checkRightAligned(road_info, lane_boundary, lane_center, config);

    if (state_ == State::Abort) {
        abort_state_frame_count_ = std::min<uint8_t>(static_cast<uint8_t>(abort_state_frame_count_ + 1U), static_cast<uint8_t>(255));
    } else {
        abort_state_frame_count_ = 0;
    }

    if (state_ == State::Completed) {
        completed_state_frame_count_ = std::min<uint8_t>(static_cast<uint8_t>(completed_state_frame_count_ + 1U), static_cast<uint8_t>(255));
    } else {
        completed_state_frame_count_ = 0;
    }

    condition.abort_to_enable = (abort_state_frame_count_ >= 5U);
    condition.completed_to_enable = (completed_state_frame_count_ >= 5U);

    // suppress条件
    // suppress状态是未进入intervention之前进的，abort是在进入intervention之后进的
    condition.enable_to_left_suppressed = b_left_triged && b_left_suppression;
    condition.enable_to_right_suppressed = b_right_triged && b_right_suppression;

    condition.left_suppressed_to_enable = !condition.enable_to_left_suppressed;
    condition.right_suppressed_to_enable = !condition.enable_to_right_suppressed;

    debug_left_active_source_mask_ = elk_scenario_decider_.getLeftActiveSourceMask();
    debug_right_active_source_mask_ = elk_scenario_decider_.getRightActiveSourceMask();

    return condition;
}

void ElkStateMachine::UpdateStateMachine(const Condition &condition)
{

    if ((state_ != State::Fault)  &&  condition.off_to_fault) {
        state_ = State::Fault;
        return;
    }

    if ((state_ != State::Off)  &&  (state_ != State::Fault)  &&  (state_ != State::Standby)  &&  condition.enable_to_standby) {
        if (condition.standby_to_off) {
            state_ = State::Off;
        } else {
            state_ = State::Standby;
        }
        return;
    }

    switch (state_) {

        case State::Fault: {
            if (condition.fault_to_off) {
                state_ = State::Off;
            }
            break;
        }

        case State::Off: {
            if (condition.off_to_fault) {
                state_ = State::Fault;
            } else if (condition.off_to_standby) {
                state_ = State::Standby;
            }
            break;
        }

        case State::Standby: {
            if (condition.standby_to_off) {
                state_ = State::Off;
            } else if (condition.standby_to_enable) {
                state_ = State::Enable;
            }
            break;
        }

        case State::Enable: {
            if (condition.enable_to_off) {
                state_ = State::Off;
            } else if (condition.enable_to_left_intervention) {
                state_ = State::Left_Intervention;
            } else if (condition.enable_to_right_intervention) {
                state_ = State::Right_Intervention;
            } else if (condition.enable_to_left_suppressed) {
                state_ = State::Left_Suppressed;
            } else if (condition.enable_to_right_suppressed) {
                state_ = State::Right_Suppressed;
            }
            break;
        }

        case State::Left_Intervention: {
            if (condition.left_to_right_intervention) {
                state_ = State::Right_Intervention;
            } else if (condition.left_to_abort) {
                state_ = State::Abort;
            } else if (condition.left_to_completed) {
                state_ = State::Completed;
            }
            break;
        }

        case State::Right_Intervention: {
            if (condition.right_to_left_intervention) {
                state_ = State::Left_Intervention;
            } else if (condition.right_to_abort) {
                state_ = State::Abort;
            } else if (condition.right_to_completed) {
                state_ = State::Completed;
            }
            break;
        }

        case State::Abort: {
            if (condition.abort_to_enable) {
                state_ = State::Enable;
            }
            break;
        }

        case State::Completed: {
            if (condition.completed_to_enable) {
                state_ = State::Enable;
            }
            break;
        }

        case State::Left_Suppressed: {
            if (condition.left_suppressed_to_enable) {
                state_ = State::Enable;
            }
            break;
        }

        case State::Right_Suppressed: {
            if (condition.right_suppressed_to_enable) {
                state_ = State::Enable;
            }
            break;
        }

        default: {
            state_ = State::Off;
            break;
        }

    }

    AD_LINFO(ElkStateMachine::UpdateStateMachine) << "current elk state is: " << (int)state_;
}

bool ElkStateMachine::checkStandby2Enable(float speed_kph, const LaneBoundaryParameters &lane_boundary)
{
    bool b_valid_speed, b_valid_curv, b_valid_width_min, b_valid_width_max;
    bool b_valid_left_marker, b_valid_right_marker, b_left_edge_valid, b_right_edge_valid;
    bool b_valid_boundary;

    stanby_enable_mask_ = 0x0;

    b_valid_speed = (speed_kph >= elk_cals_.k_ELK_MIN_SPEED_HI) && (speed_kph <= elk_cals_.k_ELK_MAX_SPEED_LO);
    if (b_valid_speed) {
        stanby_enable_mask_ = stanby_enable_mask_ + 0x1;
    }

    b_valid_curv = lane_curv_valid_checker_.process(
        std::fabs(lane_boundary.frtAxlCurv), elk_cals_.k_ELK_MAX_CURVATURE, elk_cals_.k_ELK_MAX_CURVATURE_OFF, false, true);
    if (b_valid_curv) {
        stanby_enable_mask_ = stanby_enable_mask_ + 0x2;
    }

    b_valid_width_min = min_lane_width_checker_.process(
        lane_boundary.laneWidth, elk_cals_.k_ELK_min_lane_width_enable_hi, elk_cals_.k_ELK_min_lane_width_enable_lo, true, false);
    if (b_valid_width_min) {
        stanby_enable_mask_ = stanby_enable_mask_ + 0x4;
    }

    b_valid_width_max = max_lane_width_checker_.process(
        lane_boundary.laneWidth, elk_cals_.k_ELK_max_lane_width_enable_hi, elk_cals_.k_ELK_max_lane_width_enable_lo);
    if (b_valid_width_max) {
        stanby_enable_mask_ = stanby_enable_mask_ + 0x8;
    }

    b_valid_left_marker = left_marker_valid_checker_.onDelay(
        lane_boundary.lftBdryVld, elk_cals_.k_ELK_mkr_mature_time, elk_cals_.k_ELK_StepTime);
    if (b_valid_left_marker) {
        stanby_enable_mask_ = stanby_enable_mask_ + 0x10;
    }

    b_valid_right_marker = right_marker_valid_checker_.onDelay(
        lane_boundary.rgtBdryVld, elk_cals_.k_ELK_mkr_mature_time, elk_cals_.k_ELK_StepTime);
    if (b_valid_right_marker) {
        stanby_enable_mask_ = stanby_enable_mask_ + 0x20;
    }

    b_left_edge_valid = left_edge_valid_checker_.onDelay(
        lane_boundary.lftEdgeVld, elk_cals_.k_ELK_mkr_mature_time, elk_cals_.k_ELK_StepTime);
    if (b_left_edge_valid) {
        stanby_enable_mask_ = stanby_enable_mask_ + 0x40;
    }

    b_right_edge_valid = right_edge_valid_checker_.onDelay(
        lane_boundary.rgtEdgeVld, elk_cals_.k_ELK_mkr_mature_time, elk_cals_.k_ELK_StepTime);
    if (b_right_edge_valid) {
        stanby_enable_mask_ = stanby_enable_mask_ + 0x80;
    }

    if (!yawrate_inhabit_checker_.getOutput()) {
        stanby_enable_mask_ = stanby_enable_mask_ + 0x100;
    }

    if (diag_inhabit_mask_ == 0) {
        stanby_enable_mask_ = stanby_enable_mask_ + 0x200;
    }

    b_valid_boundary = b_valid_left_marker || b_valid_right_marker || b_left_edge_valid || b_right_edge_valid;

    return b_valid_speed && b_valid_curv && b_valid_width_min && b_valid_width_max && b_valid_boundary &&
         (!yawrate_inhabit_checker_.getOutput()) && (diag_inhabit_mask_ == 0);
}

bool ElkStateMachine::checkEnable2Standby(float speed_kph)
{
    bool b_invalid_speed, b_invalid_curv, b_invalid_width, b_invalid_boundary;

    b_invalid_speed = (speed_kph > elk_cals_.k_ELK_MAX_SPEED_HI) || (speed_kph < elk_cals_.k_ELK_MIN_SPEED_LO);

    b_invalid_curv = !lane_curv_valid_checker_.getOutput();

    b_invalid_width = (!min_lane_width_checker_.getOutput()) || (!max_lane_width_checker_.getOutput());

    b_invalid_boundary = (!left_marker_valid_checker_.getStateOut()) && (!right_marker_valid_checker_.getStateOut()) &&
        (!left_edge_valid_checker_.getStateOut()) && (!right_edge_valid_checker_.getStateOut());

    return b_invalid_speed || b_invalid_curv || b_invalid_width || b_invalid_boundary || 
        (yawrate_inhabit_checker_.getOutput()) || (diag_inhabit_mask_ > 0);
}


} // namespace elk
} // namespace active_safety
