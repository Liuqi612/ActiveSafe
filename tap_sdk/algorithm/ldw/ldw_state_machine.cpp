#include "ldw_state_machine.h"

#include "common/enum_type.h"
#include "math/lookuptable/lookuptable.h"

#include <algorithm>
#include <cmath>

namespace active_safety {
namespace ldw {

namespace {
constexpr uint32_t kLatSafeFaultMask = 1U << static_cast<uint8_t>(FunctionDid::LDW); // function_did_config bit10: LDW fault inhibit
constexpr uint32_t kLowSpeedAccelPedalSuppressBit = 1U << 9U;
constexpr uint32_t kDriverTorqueOverrideSuppressBit = 1U << 10U;
constexpr uint32_t kDriverIntentSuppressBit = 1U << 11U;

float clamp01(float value) {
    return std::min(std::max(value, 0.0F), 1.0F);
}

float calcScore(float value, float threshold) {
    if (threshold <= 0.001F) {
        return 0.0F;
    }
    return clamp01(value / threshold);
}
}

// 计算本周期状态转移结果，并更新模块可用状态。
void LdwStateMachine::Update(const AsVseOut &vse_out,
                             const LaneBoundaryParameters &lane_boundary,
                             const LaneCenterParameters &lane_center,
                             const GlobalConfig &config) {
    const State prev_state = state_;

    checkDriverSuppression(vse_out);
    UpdateStateMachine(BuildCondition(vse_out, lane_boundary, lane_center, config));
    UpdateWarningTimers(prev_state);

    available_ = state_ == State::Enable || state_ == State::LeftWarning || state_ == State::RightWarning;
}

void LdwStateMachine::updateSteerTorqueSuppressHistory(bool suppress_condition) {
    steer_torque_suppress_history_[steer_torque_suppress_history_index_] = suppress_condition;
    steer_torque_suppress_history_index_ =
        (steer_torque_suppress_history_index_ + 1U) % steer_torque_suppress_history_.size();
}

bool LdwStateMachine::isSteerTorqueHistorySuppressed() const {
    const std::size_t history_window =
        std::min<std::size_t>(ldw_cal_.k_LDW_DriHandsOvr_HistoryWindow, steer_torque_suppress_history_.size());
    const std::size_t suppress_count =
        std::min<std::size_t>(ldw_cal_.k_LDW_DriHandsOvr_HistorySuppressCount, history_window);
    if ((history_window == 0U) || (suppress_count == 0U)) {
        return false;
    }

    std::size_t satisfied_count = 0U;
    for (std::size_t i = 0U; i < history_window; ++i) {
        const std::size_t history_index =
            (steer_torque_suppress_history_index_ + steer_torque_suppress_history_.size() - 1U - i) %
            steer_torque_suppress_history_.size();
        if (steer_torque_suppress_history_[history_index]) {
            ++satisfied_count;
        }
    }

    return satisfied_count >= suppress_count;
}

bool LdwStateMachine::updateDriverIntentScoreHistory(float driver_intent_score) {
    driver_intent_score_history_[driver_intent_score_history_index_] = driver_intent_score;
    driver_intent_score_valid_history_[driver_intent_score_history_index_] = true;
    driver_intent_score_history_index_ =
        (driver_intent_score_history_index_ + 1U) % driver_intent_score_history_.size();
    driver_intent_score_valid_count_ =
        std::min<uint8_t>(static_cast<uint8_t>(driver_intent_score_valid_count_ + 1U),
                          static_cast<uint8_t>(driver_intent_score_history_.size()));

    const std::size_t required_frame_count =
        std::min<std::size_t>(ldw_cal_.k_driver_intent_history_frame_count, driver_intent_score_history_.size());
    if ((required_frame_count == 0U) || (driver_intent_score_valid_count_ < required_frame_count)) {
        return false;
    }

    for (std::size_t i = 0U; i < required_frame_count; ++i) {
        const std::size_t history_index =
            (driver_intent_score_history_index_ + driver_intent_score_history_.size() - 1U - i) %
            driver_intent_score_history_.size();
        if (!driver_intent_score_valid_history_[history_index] ||
            driver_intent_score_history_[history_index] < ldw_cal_.k_driver_intent_score_threshold) {
            return false;
        }
    }

    return true;
}

void LdwStateMachine::resetTtcHistory(TtcHistory &history) {
    history.ttlc.fill(0.0F);
    history.valid_frame_count = 0U;
    history.invalid_ttlc_count = 0U;
}

bool LdwStateMachine::checkStableTtcDeparture(TtcHistory &history,
                                              float ttlc,
                                              float threshold,
                                              bool history_enabled) {
    if (!history_enabled) {
        resetTtcHistory(history);
        return false;
    }

    if (!std::isfinite(ttlc) || (ttlc <= 0.0F) ||
        !std::isfinite(threshold) || (threshold <= 0.0F)) {
        history.invalid_ttlc_count =
            std::min<uint8_t>(static_cast<uint8_t>(history.invalid_ttlc_count + 1U), static_cast<uint8_t>(255U));
        if (history.invalid_ttlc_count > ldw_cal_.k_ttlc_invalid_tolerance_frames) {
            resetTtcHistory(history);
        }
        return false;
    }

    history.invalid_ttlc_count = 0U;
    history.ttlc[0] = history.ttlc[1];
    history.ttlc[1] = history.ttlc[2];
    history.ttlc[2] = ttlc;
    if (history.valid_frame_count < history.ttlc.size()) {
        ++history.valid_frame_count;
    }

    return (history.valid_frame_count >= history.ttlc.size()) &&
           (history.ttlc[0] < threshold) && (history.ttlc[1] < threshold) && (history.ttlc[2] < threshold) &&
           (history.ttlc[2] <= history.ttlc[1]) && (history.ttlc[1] <= history.ttlc[0]);
}

float LdwStateMachine::calcSpeedBasedTtcThreshold(float speed_kph) const {
    if (speed_kph <= ldw_cal_.k_ttlc_low_speed_start_kph) {
        return ldw_cal_.k_low_speed_warning_ttlc_s;
    }
    if (speed_kph <= ldw_cal_.k_ttlc_low_speed_end_kph) {
        return ldw_cal_.k_low_speed_warning_ttlc_s;
    }
    if (speed_kph >= ldw_cal_.k_ttlc_high_speed_recover_kph) {
        return ldw_cal_.k_warning_ttlc_s;
    }

    return math::LookUpTable::LinearInterpolation(speed_kph,
                                                   ldw_cal_.k_ttlc_low_speed_end_kph,
                                                   ldw_cal_.k_low_speed_warning_ttlc_s,
                                                   ldw_cal_.k_ttlc_high_speed_recover_kph,
                                                   ldw_cal_.k_warning_ttlc_s);
}

// 将驾驶员操作和车辆状态编码成统一的抑制位。
void LdwStateMachine::checkDriverSuppression(const AsVseOut &vse_out) {
    suppress_mask_ = 0;

    // bit0: 横摆角速度
    if (yawrate_inhibit_checker_.process(std::fabs(vse_out.yawrate),
                                         ldw_cal_.k_yawrate_inhibit_on_rps,
                                         ldw_cal_.k_yawrate_inhibit_off_rps,
                                         ldw_cal_.k_yawrate_inhibit_on_delay_s,
                                         ldw_cal_.k_yawrate_inhibit_off_delay_s,
                                         kCycleTimeS,
                                         true,
                                         false)) {
        suppress_mask_ |= 0x1U;
    }

    // bit1: 制动踏板/制动压力
    if (brake_inhibit_checker_.offDelay(vse_out.brake_pedal_apld || (vse_out.brake_pressure > ldw_cal_.k_brake_pressure_inhibit_pa),
                                        ldw_cal_.k_brake_inhibit_off_delay_s,
                                        kCycleTimeS)) {
        suppress_mask_ |= 0x2U;
    }

    // bit2: 加速踏板速率
    if (accel_inhibit_checker_.offDelay(vse_out.gas_pedal_pos_rate > ldw_cal_.k_accel_pedal_rate_inhibit_pct,
                                        ldw_cal_.k_accel_inhibit_off_delay_s,
                                        kCycleTimeS)) {
        suppress_mask_ |= 0x4U;
    }

    // bit3: 方向盘角度
    if (steer_angle_inhibit_checker_.offDelay(std::fabs(vse_out.steerwheelangle) > ldw_cal_.k_steer_angle_inhibit_deg,
                                              ldw_cal_.k_steer_angle_inhibit_off_delay_s,
                                              kCycleTimeS)) {
        suppress_mask_ |= 0x8U;
    }

    // bit4: 方向盘角速度
    if (steer_angle_rate_inhibit_checker_.offDelay(std::fabs(vse_out.steerwheelangle_rate) > ldw_cal_.k_steer_angle_rate_inhibit_degps,
                                                   ldw_cal_.k_steer_angle_rate_inhibit_off_delay_s,
                                                   kCycleTimeS)) {
        suppress_mask_ |= 0x10U;
    }

    // bit5: 双闪
    if (hazard_inhibit_checker_.offDelay(vse_out.hazard_lamp_st == 1U, ldw_cal_.k_hazard_inhibit_off_delay_s, kCycleTimeS)) {
        suppress_mask_ |= 0x20U;
    }

    // bit6: 纵向加速度
    if (long_accel_inhibit_checker_.offDelay(std::fabs(vse_out.long_accel) > ldw_cal_.k_long_accel_inhibit_mpss,
                                             ldw_cal_.k_long_accel_inhibit_off_delay_s,
                                             kCycleTimeS)) {
        suppress_mask_ |= 0x40U;
    }

    // bit7: 挡位
    if (gear_inhibit_checker_.offDelay(vse_out.actual_gear != 3U, ldw_cal_.k_gear_inhibit_off_delay_s, kCycleTimeS)) {
        suppress_mask_ |= 0x80U;
    }

    // bit8: Handsoff
    if (hands_off_inhibit_checker_.process(std::fabs(vse_out.torsion_bar_trq),
                                           ldw_cal_.k_hands_off_inhibit_on_nm,
                                           ldw_cal_.k_hands_off_inhibit_off_nm,
                                           ldw_cal_.k_hands_off_inhibit_on_delay_s,
                                           ldw_cal_.k_hands_off_inhibit_off_delay_s,
                                           kCycleTimeS,
                                           false,
                                           true)) {
        suppress_mask_ |= 0x100U;
    }

    // bit9: 40~60 km/h 区间持续踩下加速踏板，只用于阻止告警入态。
    if (low_speed_accel_pedal_inhibit_checker_.onDelay(
            (vse_out.display_speed >= ldw_cal_.k_low_speed_accel_pedal_min_speed_kph) &&
                (vse_out.display_speed <= ldw_cal_.k_low_speed_accel_pedal_max_speed_kph) &&
                (vse_out.gas_pedal_pos > ldw_cal_.k_low_speed_accel_pedal_threshold_pct),
            ldw_cal_.k_low_speed_accel_pedal_on_delay_s,
            kCycleTimeS)) {
        suppress_mask_ |= kLowSpeedAccelPedalSuppressBit;
    }

    // bit10: 驾驶员手力矩接管，使用与 ELK/LKA 相同的速度查表和历史命中策略。
    const float override_torque_threshold = math::LookUpTable::LookupTable1D<7>(
        ldw_cal_.k_LDW_ovrd_tq_thd_per_spd_x,
        ldw_cal_.k_LDW_ovrd_tq_thd_per_spd_z,
        vse_out.display_speed);
    updateSteerTorqueSuppressHistory(std::fabs(vse_out.torsion_bar_trq) >= override_torque_threshold);
    const bool steer_torque_history_suppressed = isSteerTorqueHistorySuppressed();
    if (steer_torque_inhibit_checker_.process(steer_torque_history_suppressed ? 1.0F : 0.0F,
                                              1.0F,
                                              0.0F,
                                              ldw_cal_.k_LDW_DriHandsOvr_OnDlyTime,
                                              ldw_cal_.k_LDW_DriHandsOvr_OffDlyTime,
                                              kCycleTimeS,
                                              true,
                                              false)) {
        suppress_mask_ |= kDriverTorqueOverrideSuppressBit;
    }

    // bit11: 方向盘手力矩和踏板输入共同表征的驾驶员主动接管意图。
    constexpr float kKpaToBar = 0.01F;
    const float steer_score = calcScore(std::fabs(vse_out.torsion_bar_trq), override_torque_threshold);
    const float accel_score =
        calcScore(vse_out.gas_pedal_pos, ldw_cal_.k_driver_intent_accel_pedal_threshold_pct);
    const float brake_pressure_score = calcScore(kKpaToBar * vse_out.brake_pressure,
                                                 ldw_cal_.k_driver_intent_brake_pressure_threshold_bar);
    const float brake_pedal_score =
        calcScore(vse_out.brake_pedal_pos, ldw_cal_.k_driver_intent_brake_pedal_threshold_pct);
    const float pedal_score = std::max(accel_score, std::max(brake_pressure_score, brake_pedal_score));
    const float driver_intent_score = ldw_cal_.k_driver_intent_steer_weight * steer_score +
                                      ldw_cal_.k_driver_intent_pedal_weight * pedal_score;
    if (driver_intent_inhibit_checker_.offDelay(updateDriverIntentScoreHistory(driver_intent_score),
                                                ldw_cal_.k_driver_intent_off_delay_s,
                                                kCycleTimeS)) {
        suppress_mask_ |= kDriverIntentSuppressBit;
    }
}

// 检查 LDW 从 Standby 进入 Enable 所需的环境和车辆条件。
bool LdwStateMachine::checkStandby2Enable(const AsVseOut &vse_out,
                                          const LaneBoundaryParameters &lane_boundary,
                                          const LaneCenterParameters &lane_center,
                                          const GlobalConfig &config) {
    // bit0 车速，bit1 中心线有效，bit2 左侧线有效，
    // bit3 右侧线有效，bit4 车道线曲率有效，bit5 车道宽度有效，
    // bit6 左侧路沿有效，bit7 右侧路沿有效，
    // bit8 左侧路沿曲率有效，bit9 右侧路沿曲率有效。
    enable_mask_ = 0;

    const float speed_kph = vse_out.display_speed + ldw_cal_.k_speed_compensation_kph;
    const bool speed_valid = speed_kph >= ldw_cal_.k_enable_min_speed_kph && speed_kph <= ldw_cal_.k_enable_max_speed_kph;
    if (speed_valid) {
        enable_mask_ |= 0x1U;
    }

    if (lane_center.vld) {
        enable_mask_ |= 0x2U;
    }

    const bool left_marker_valid =
        left_marker_valid_checker_.onDelay(lane_boundary.lftBdryVld, ldw_cal_.k_marker_valid_on_delay_s, kCycleTimeS);
    if (left_marker_valid) {
        enable_mask_ |= 0x4U;
    }

    const bool right_marker_valid =
        right_marker_valid_checker_.onDelay(lane_boundary.rgtBdryVld, ldw_cal_.k_marker_valid_on_delay_s, kCycleTimeS);
    if (right_marker_valid) {
        enable_mask_ |= 0x8U;
    }

    const bool line_curvature_valid = lane_curv_valid_checker_.process(std::fabs(lane_boundary.frtAxlCurv),
                                                                       ldw_cal_.k_lane_curvature_valid_on,
                                                                       ldw_cal_.k_lane_curvature_valid_off,
                                                                       false,
                                                                       true);
    if (line_curvature_valid) {
        enable_mask_ |= 0x10U;
    }

    const bool min_width_valid = min_lane_width_checker_.process(lane_boundary.laneWidth,
                                                                 ldw_cal_.k_lane_width_min_on_m,
                                                                 ldw_cal_.k_lane_width_min_off_m,
                                                                 true,
                                                                 false);
    const bool max_width_valid = max_lane_width_checker_.process(lane_boundary.laneWidth,
                                                                 ldw_cal_.k_lane_width_max_on_m,
                                                                 ldw_cal_.k_lane_width_max_off_m,
                                                                 false,
                                                                 true);
    if (min_width_valid && max_width_valid) {
        enable_mask_ |= 0x20U;
    }

    const bool left_edge_valid =
        left_edge_valid_checker_.onDelay(lane_boundary.lftEdgeVld, ldw_cal_.k_marker_valid_on_delay_s, kCycleTimeS);
    if (left_edge_valid) {
        enable_mask_ |= 0x40U;
    }

    const bool right_edge_valid =
        right_edge_valid_checker_.onDelay(lane_boundary.rgtEdgeVld, ldw_cal_.k_marker_valid_on_delay_s, kCycleTimeS);
    if (right_edge_valid) {
        enable_mask_ |= 0x80U;
    }

    const bool left_edge_curvature_valid = left_edge_curv_valid_checker_.process(std::fabs(lane_boundary.lftEdgeCurv),
                                                                                 ldw_cal_.k_lane_curvature_valid_on,
                                                                                 ldw_cal_.k_lane_curvature_valid_off,
                                                                                 false,
                                                                                 true);
    if (left_edge_curvature_valid) {
        enable_mask_ |= 0x100U;
    }

    const bool right_edge_curvature_valid = right_edge_curv_valid_checker_.process(std::fabs(lane_boundary.rgtEdgeCurv),
                                                                                   ldw_cal_.k_lane_curvature_valid_on,
                                                                                   ldw_cal_.k_lane_curvature_valid_off,
                                                                                   false,
                                                                                   true);
    if (right_edge_curvature_valid) {
        enable_mask_ |= 0x200U;
    }

    const bool line_scene_valid = config.k_LDW_EnLine && speed_valid && lane_center.vld && left_marker_valid &&
                                  right_marker_valid && line_curvature_valid && min_width_valid && max_width_valid;

    const bool left_edge_scene_valid = config.k_LDW_EnEdge && speed_valid && left_edge_valid && left_edge_curvature_valid;
    const bool right_edge_scene_valid = config.k_LDW_EnEdge && speed_valid && right_edge_valid && right_edge_curvature_valid;

    return line_scene_valid || left_edge_scene_valid || right_edge_scene_valid;
}

// 根据独立的退出速度窗口和当前场景条件判断是否需要退回 Standby。
bool LdwStateMachine::checkEnable2Standby(float speed_kph, const GlobalConfig &config) const {
    constexpr uint16_t kLineSceneMask = 0x3EU;
    constexpr uint16_t kLeftEdgeSceneMask = 0x140U;
    constexpr uint16_t kRightEdgeSceneMask = 0x280U;

    const bool speed_valid = speed_kph >= ldw_cal_.k_exit_min_speed_kph && speed_kph <= ldw_cal_.k_exit_max_speed_kph;
    const bool line_scene_valid = config.k_LDW_EnLine && (enable_mask_ & kLineSceneMask) == kLineSceneMask;
    const bool left_edge_scene_valid = config.k_LDW_EnEdge && (enable_mask_ & kLeftEdgeSceneMask) == kLeftEdgeSceneMask;
    const bool right_edge_scene_valid = config.k_LDW_EnEdge && (enable_mask_ & kRightEdgeSceneMask) == kRightEdgeSceneMask;
    const bool suppression_cleared = (suppress_mask_ & ldw_cal_.k_standby_enable_mask) == 0U;

    return !(speed_valid && (line_scene_valid || left_edge_scene_valid || right_edge_scene_valid) && suppression_cleared);
}

// 根据左侧边界距离、逼近趋势和 TTLC 判断是否需要左偏离告警。
bool LdwStateMachine::determineLeftWarning(const AsVseOut &vse_out,
                                           const LaneBoundaryParameters &lane_boundary,
                                           const LaneCenterParameters &lane_center,
                                           const GlobalConfig &config) {
    (void)lane_center;
    const bool near_left_line = lane_boundary.lftBdryVld &&
                                lane_boundary.curLftDisToBdry < ldw_cal_.k_warning_boundary_maxdist_m &&
                                lane_boundary.curLftDisToBdry > ldw_cal_.k_warning_boundary_mindist_m;
    const bool left_line_quality_valid = !lane_boundary.lftBdryJump && !lane_boundary.lftBdryRangeShort;
    //主要考虑ttlc触发困难的小横向速度场景                          
    const bool drifting_to_left_line = (lane_boundary.lftBdryLatRt < ldw_cal_.k_left_boundary_lat_rate_mps && lane_boundary.lftBdryLatRt > 0.0F) ||
                                       lane_boundary.lftBdryHdgDeg > ldw_cal_.k_left_boundary_heading_deg;
    const bool left_line_ttlc_urgent = checkStableTtcDeparture(left_line_ttc_history_,
                                                              lane_boundary.lftBdryTtlc,
                                                              warningTtlcThreshold(vse_out, config),
                                                              config.k_LDW_EnLine && near_left_line &&
                                                                  left_line_quality_valid);
    const bool line_warning = config.k_LDW_EnLine && near_left_line && left_line_quality_valid &&
                              (left_line_ttlc_urgent ||
                               (config.k_LKA_LDW_EnDriftingTrigger && drifting_to_left_line));

    const bool near_left_edge = lane_boundary.lftEdgeVld &&
                                lane_boundary.curLftDisToEdge < ldw_cal_.k_warning_boundary_maxdist_m &&
                                lane_boundary.curLftDisToEdge > ldw_cal_.k_warning_boundary_mindist_m;
    const bool left_edge_quality_valid = !lane_boundary.lftEdgeJump && !lane_boundary.lftEdgeRangeShort &&
                                         !lane_boundary.lftEdgeLaneMismatch;
    //主要考虑ttlc触发困难的小横向速度场景                           
    const bool drifting_to_left_edge = (lane_boundary.lftEdgeLatRt < ldw_cal_.k_left_boundary_lat_rate_mps && lane_boundary.lftEdgeLatRt > 0.0F) ||
                                       lane_boundary.lftEdgeHdgDeg > ldw_cal_.k_left_boundary_heading_deg;
    const bool left_edge_ttlc_urgent = checkStableTtcDeparture(left_edge_ttc_history_,
                                                              lane_boundary.lftEdgeTtlc,
                                                              warningTtlcThreshold(vse_out, config),
                                                              config.k_LDW_EnEdge && near_left_edge &&
                                                                  left_edge_quality_valid);
    const bool edge_warning = config.k_LDW_EnEdge && near_left_edge && left_edge_quality_valid &&
                              (left_edge_ttlc_urgent ||
                               (config.k_LKA_LDW_EnDriftingTrigger && drifting_to_left_edge));

    return line_warning || edge_warning;
}

// 根据右侧边界距离、逼近趋势和 TTLC 判断是否需要右偏离告警。
bool LdwStateMachine::determineRightWarning(const AsVseOut &vse_out,
                                            const LaneBoundaryParameters &lane_boundary,
                                            const LaneCenterParameters &lane_center,
                                            const GlobalConfig &config) {
    (void)lane_center;
    const bool near_right_line = lane_boundary.rgtBdryVld &&
                                 lane_boundary.curRgtDisToBdry < ldw_cal_.k_warning_boundary_maxdist_m &&
                                 lane_boundary.curRgtDisToBdry > ldw_cal_.k_warning_boundary_mindist_m;
    const bool right_line_quality_valid = !lane_boundary.rgtBdryJump && !lane_boundary.rgtBdryRangeShort;
    //主要考虑ttlc触发困难的小横向速度场景                             
    const bool drifting_to_right_line = (lane_boundary.rgtBdryLatRt > ldw_cal_.k_right_boundary_lat_rate_mps && lane_boundary.rgtBdryLatRt < 0.0F) ||
                                        lane_boundary.rgtBdryHdgDeg < ldw_cal_.k_right_boundary_heading_deg;
    const bool right_line_ttlc_urgent = checkStableTtcDeparture(right_line_ttc_history_,
                                                               lane_boundary.rgtBdryTtlc,
                                                               warningTtlcThreshold(vse_out, config),
                                                               config.k_LDW_EnLine && near_right_line &&
                                                                   right_line_quality_valid);
    const bool line_warning = config.k_LDW_EnLine && near_right_line && right_line_quality_valid &&
                              (right_line_ttlc_urgent ||
                               (config.k_LKA_LDW_EnDriftingTrigger && drifting_to_right_line));

    const bool near_right_edge = lane_boundary.rgtEdgeVld &&
                                 lane_boundary.curRgtDisToEdge < ldw_cal_.k_warning_boundary_maxdist_m &&
                                 lane_boundary.curRgtDisToEdge > ldw_cal_.k_warning_boundary_mindist_m;
    const bool right_edge_quality_valid = !lane_boundary.rgtEdgeJump && !lane_boundary.rgtEdgeRangeShort &&
                                          !lane_boundary.rgtEdgeLaneMismatch;
    //主要考虑ttlc触发困难的小横向速度场景                             
    const bool drifting_to_right_edge = (lane_boundary.rgtEdgeLatRt > ldw_cal_.k_right_boundary_lat_rate_mps && lane_boundary.rgtEdgeLatRt < 0.0F) ||
                                        lane_boundary.rgtEdgeHdgDeg < ldw_cal_.k_right_boundary_heading_deg;
    const bool right_edge_ttlc_urgent = checkStableTtcDeparture(right_edge_ttc_history_,
                                                               lane_boundary.rgtEdgeTtlc,
                                                               warningTtlcThreshold(vse_out, config),
                                                               config.k_LDW_EnEdge && near_right_edge &&
                                                                   right_edge_quality_valid);
    const bool edge_warning = config.k_LDW_EnEdge && near_right_edge && right_edge_quality_valid &&
                              (right_edge_ttlc_urgent ||
                               (config.k_LKA_LDW_EnDriftingTrigger && drifting_to_right_edge));

    return line_warning || edge_warning;
}

// 读取软开关，决定模块是否允许从 Off 进入待机。
bool LdwStateMachine::switchEnabled(const AsVseOut &vse_out) const {
    return vse_out.lss_switch >= 1U;
}

// 左侧告警受 warning 专用驾驶员抑制和左转向灯压制。
bool LdwStateMachine::leftSuppressed(const AsVseOut &vse_out) const {
    return ((suppress_mask_ & ldw_cal_.k_warning_suppressed_mask) != 0U) ||
           (vse_out.turn_light_switch_pos == 1U);
}

// 右侧告警受 warning 专用驾驶员抑制和右转向灯压制。
bool LdwStateMachine::rightSuppressed(const AsVseOut &vse_out) const {
    return ((suppress_mask_ & ldw_cal_.k_warning_suppressed_mask) != 0U) ||
           (vse_out.turn_light_switch_pos == 3U);
}

// 按用户灵敏度设置缩放告警 TTLC 门限。
float LdwStateMachine::warningTtlcThreshold(const AsVseOut &vse_out, const GlobalConfig &config) const {
    float scale = 1.0F;
    if (vse_out.lss_sensitivity == 1U) {
        scale = ldw_cal_.k_high_sensitivity_scale;
    } else if (vse_out.lss_sensitivity == 2U) {
        scale = ldw_cal_.k_low_sensitivity_scale;
    }
    return calcSpeedBasedTtcThreshold(vse_out.display_speed) * scale * config.k_LDW_TTLCScale;
}

// 汇总本周期触发、抑制和使能条件，生成状态跳转表。
LdwStateMachine::Condition LdwStateMachine::BuildCondition(const AsVseOut &vse_out,
                                                           const LaneBoundaryParameters &lane_boundary,
                                                           const LaneCenterParameters &lane_center,
                                                           const GlobalConfig &config) {
    Condition condition;
    const bool enabled = config.k_LDW_func_enable || (vse_out.ldw_switch == 1U);
    const bool upstream_fault_inhibit = (vse_out.function_did_config & kLatSafeFaultMask) != 0U;
    const bool fault_inhibit = !config.k_LSS_IgnoreFaultInhibit && upstream_fault_inhibit;
    //switchEnabled(vse_out);
    const bool scene_enable = checkStandby2Enable(vse_out, lane_boundary, lane_center, config);
    const bool suppression_cleared = (suppress_mask_ & ldw_cal_.k_standby_enable_mask) == 0U;
    const bool standby_enable = scene_enable && suppression_cleared;
    const float speed_kph = vse_out.display_speed + ldw_cal_.k_speed_compensation_kph;
    const bool enable_to_standby = checkEnable2Standby(speed_kph, config);
    const bool left_trigger = determineLeftWarning(vse_out, lane_boundary, lane_center, config);
    const bool right_trigger = determineRightWarning(vse_out, lane_boundary, lane_center, config);
    const bool left_suppressed_now = leftSuppressed(vse_out);
    const bool right_suppressed_now = rightSuppressed(vse_out);
    const bool can_warn_left = left_trigger && !left_suppressed_now;
    const bool can_warn_right = right_trigger && !right_suppressed_now;
    const uint16_t warning_min_hold_cycle = static_cast<uint16_t>(ldw_cal_.k_warning_min_hold_s / kCycleTimeS);
    const uint16_t warning_max_hold_cycle = static_cast<uint16_t>(ldw_cal_.k_warning_max_hold_s / kCycleTimeS);
    const bool warning_min_hold_elapsed = warning_active_frame_count_ >= warning_min_hold_cycle;
    const bool warning_max_hold_elapsed = warning_active_frame_count_ >= warning_max_hold_cycle;

    left_trigger_ = left_trigger;
    right_trigger_ = right_trigger;

    condition.fault_to_off = !fault_inhibit;
    condition.off_to_fault = fault_inhibit;
    condition.off_to_standby = enabled;
    condition.standby_to_off = !enabled;
    condition.standby_to_enable = standby_enable;
    condition.enable_to_standby = enabled && enable_to_standby;
    condition.enable_to_off = !enabled;

    condition.enable_to_left_warning = can_warn_left && !can_warn_right;
    condition.enable_to_right_warning = can_warn_right && !can_warn_left;
    // 从告警态退回 Enable 的条件是：未满足退出条件，且最短告警时间(2s)已到，且不存在新的告警触发或者最长告警时间(7s)已到。
    condition.left_warning_to_enable = enabled && !enable_to_standby && warning_min_hold_elapsed &&
                                       (!can_warn_left || warning_max_hold_elapsed);
    condition.right_warning_to_enable = enabled && !enable_to_standby && warning_min_hold_elapsed &&
                                        (!can_warn_right || warning_max_hold_elapsed);
    condition.left_warning_to_off = !enabled;
    condition.right_warning_to_off = !enabled;
    condition.left_warning_to_standby = enabled && enable_to_standby && warning_min_hold_elapsed;
    condition.right_warning_to_standby = enabled && enable_to_standby && warning_min_hold_elapsed;

    return condition;
}

// 按状态图定义推进 LDW 状态机。
void LdwStateMachine::UpdateStateMachine(const Condition &condition) {
    if (state_ == State::Fault) {
        if (condition.fault_to_off) {
            state_ = State::Off;
        }
        return;
    }

    if ((state_ != State::Fault)  &&  condition.off_to_fault) {
        state_ = State::Fault;
        return;
    }

    switch (state_) {
        case State::Fault:
            break;
        case State::Off:
            if (condition.off_to_standby) {
                state_ = State::Standby;
            }
            break;
        case State::Standby:
            if (condition.standby_to_off) {
                state_ = State::Off;
            } else if (condition.standby_to_enable) {
                state_ = State::Enable;
            }
            break;
        case State::Enable:
            if (condition.enable_to_off) {
                state_ = State::Off;
            } else if (condition.enable_to_standby) {
                state_ = State::Standby;
            } else if (condition.enable_to_left_warning) {
                state_ = State::LeftWarning;
            } else if (condition.enable_to_right_warning) {
                state_ = State::RightWarning;
            }
            break;
        case State::LeftWarning:
            if (condition.left_warning_to_off) {
                state_ = State::Off;
            } else if (condition.left_warning_to_standby) {
                state_ = State::Standby;
            } else if (condition.left_warning_to_enable) {
                state_ = State::Enable;
            }
            break;
        case State::RightWarning:
            if (condition.right_warning_to_off) {
                state_ = State::Off;
            } else if (condition.right_warning_to_standby) {
                state_ = State::Standby;
            } else if (condition.right_warning_to_enable) {
                state_ = State::Enable;
            }
            break;
    }
}

// 记录当前 Warning 态已持续的帧数，用于最短/最长告警时间控制。
void LdwStateMachine::UpdateWarningTimers(State prev_state) {
    if (!IsWarningState(state_)) {
        warning_active_frame_count_ = 0;
        return;
    }

    if (prev_state == state_) {
        if (warning_active_frame_count_ < static_cast<uint16_t>(0xFFFFU)) {
            ++warning_active_frame_count_;
        }
    } else {
        warning_active_frame_count_ = 1U;
    }
}

} // namespace ldw
} // namespace active_safety
