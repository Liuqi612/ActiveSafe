#include "lka_state_machine.h"

#include "common/enum_type.h"
#include "math/lookuptable/lookuptable.h"

#include <algorithm>
#include <cmath>

namespace active_safety {
namespace lka {

namespace {
constexpr uint32_t kLatSafeFaultMask = 1U << static_cast<uint8_t>(FunctionDid::LKA); // function_did_config bit9: LKA fault inhibit
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

// 计算本周期抑制位、可用性和状态迁移结果。
void LkaStateMachine::Update(const AsVseOut &vse_out,
                             const elk::LaneBoundaryParameters &lane_boundary,
                             const elk::LaneCenterParameters &lane_center,
                             const GlobalConfig &config) {
    const State prev_state = state_;

    checkDriverSuppression(vse_out);
    UpdateStateMachine(BuildCondition(vse_out, lane_boundary, lane_center, config));
    UpdateInterventionTimers(prev_state);

    available_ = (state_ == State::Enable) || (state_ == State::LeftIntervention) || (state_ == State::RightIntervention) ||
                 (state_ == State::InterventionAbort) || (state_ == State::InterventionCompleted) ||
                 (state_ == State::LeftSuppressed) || (state_ == State::RightSuppressed);
}

void LkaStateMachine::updateSteerTorqueSuppressHistory(bool suppress_condition) {
    steer_torque_suppress_history_[steer_torque_suppress_history_index_] = suppress_condition;
    steer_torque_suppress_history_index_ =
        (steer_torque_suppress_history_index_ + 1U) % steer_torque_suppress_history_.size();
}

bool LkaStateMachine::isSteerTorqueHistorySuppressed() const {
    const std::size_t history_window =
        std::min<std::size_t>(lka_cal_.k_LKA_DriHandsOvr_HistoryWindow, steer_torque_suppress_history_.size());
    const std::size_t suppress_count =
        std::min<std::size_t>(lka_cal_.k_LKA_DriHandsOvr_HistorySuppressCount, history_window);
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

bool LkaStateMachine::updateDriverIntentScoreHistory(float driver_intent_score) {
    driver_intent_score_history_[driver_intent_score_history_index_] = driver_intent_score;
    driver_intent_score_valid_history_[driver_intent_score_history_index_] = true;
    driver_intent_score_history_index_ =
        (driver_intent_score_history_index_ + 1U) % driver_intent_score_history_.size();
    driver_intent_score_valid_count_ =
        std::min<uint8_t>(static_cast<uint8_t>(driver_intent_score_valid_count_ + 1U),
                          static_cast<uint8_t>(driver_intent_score_history_.size()));

    const std::size_t required_frame_count =
        std::min<std::size_t>(lka_cal_.k_driver_intent_history_frame_count, driver_intent_score_history_.size());
    if ((required_frame_count == 0U) || (driver_intent_score_valid_count_ < required_frame_count)) {
        return false;
    }

    for (std::size_t i = 0U; i < required_frame_count; ++i) {
        const std::size_t history_index =
            (driver_intent_score_history_index_ + driver_intent_score_history_.size() - 1U - i) %
            driver_intent_score_history_.size();
        if (!driver_intent_score_valid_history_[history_index] ||
            driver_intent_score_history_[history_index] < lka_cal_.k_driver_intent_score_threshold) {
            return false;
        }
    }

    return true;
}

void LkaStateMachine::resetTtcHistory(TtcHistory &history) {
    history.ttlc.fill(0.0F);
    history.valid_frame_count = 0U;
    history.invalid_ttlc_count = 0U;
}

bool LkaStateMachine::checkStableTtcDeparture(TtcHistory &history,
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
        if (history.invalid_ttlc_count > lka_cal_.k_ttlc_invalid_tolerance_frames) {
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

bool LkaStateMachine::checkTtcDeparture(TtcHistory &history,
                                        float ttlc,
                                        float threshold,
                                        bool history_enabled,
                                        TtcCheckMode mode) {
    if (!history_enabled) {
        resetTtcHistory(history);
        return false;
    }

    if (mode == TtcCheckMode::SuppressedExit) {
        return std::isfinite(ttlc) && (ttlc > 0.0F) &&
               std::isfinite(threshold) && (threshold > 0.0F) &&
               (ttlc <= threshold);
    }

    return checkStableTtcDeparture(history, ttlc, threshold, history_enabled);
}

float LkaStateMachine::calcSpeedBasedTtcThreshold(float speed_kph) const {
    if (speed_kph <= lka_cal_.k_ttlc_low_speed_start_kph) {
        return lka_cal_.k_low_speed_intervention_ttlc_s;
    }
    if (speed_kph <= lka_cal_.k_ttlc_low_speed_end_kph) {
        return lka_cal_.k_low_speed_intervention_ttlc_s;
    }
    if (speed_kph >= lka_cal_.k_ttlc_high_speed_recover_kph) {
        return lka_cal_.k_intervention_ttlc_s;
    }

    return math::LookUpTable::LinearInterpolation(speed_kph,
                                                   lka_cal_.k_ttlc_low_speed_end_kph,
                                                   lka_cal_.k_low_speed_intervention_ttlc_s,
                                                   lka_cal_.k_ttlc_high_speed_recover_kph,
                                                   lka_cal_.k_intervention_ttlc_s);
}

void LkaStateMachine::checkDriverSuppression(const AsVseOut &vse_out) {
    // 每一位代表一种抑制来源，便于外部定位本周期 LKA 被压制的原因。
    suppress_mask_ = 0;

    // bit0: 横摆角速度
    if (yawrate_inhibit_checker_.process(std::fabs(vse_out.yawrate),
                                         lka_cal_.k_yawrate_inhibit_on_rps,
                                         lka_cal_.k_yawrate_inhibit_off_rps,
                                         lka_cal_.k_yawrate_inhibit_on_delay_s,
                                         lka_cal_.k_yawrate_inhibit_off_delay_s,
                                         kCycleTimeS,
                                         true,
                                         false)) {
        suppress_mask_ |= 0x1U;
    }

    // bit1: 制动踏板/制动压力
    if (brake_inhibit_checker_.offDelay(vse_out.brake_pedal_apld || (vse_out.brake_pressure > lka_cal_.k_brake_pressure_inhibit_pa),
                                        lka_cal_.k_brake_inhibit_off_delay_s,
                                        kCycleTimeS)) {
        suppress_mask_ |= 0x2U;
    }

    // bit2: 加速踏板速率，或低速区间持续踩下加速踏板。
    const bool low_speed_accel_pedal_suppressed = low_speed_accel_pedal_inhibit_checker_.onDelay(
        (vse_out.display_speed >= lka_cal_.k_low_speed_accel_pedal_min_speed_kph) &&
            (vse_out.display_speed <= lka_cal_.k_low_speed_accel_pedal_max_speed_kph) &&
            (vse_out.gas_pedal_pos > lka_cal_.k_low_speed_accel_pedal_threshold_pct),
        lka_cal_.k_low_speed_accel_pedal_on_delay_s,
        kCycleTimeS);
    if (accel_inhibit_checker_.offDelay(vse_out.gas_pedal_pos_rate > lka_cal_.k_accel_pedal_rate_inhibit_pct,
                                        lka_cal_.k_accel_inhibit_off_delay_s,
                                        kCycleTimeS) ||
        low_speed_accel_pedal_suppressed) {
        suppress_mask_ |= 0x4U;
    }

    // bit3: 方向盘角度

    if (steer_angle_inhibit_checker_.offDelay(std::fabs(vse_out.steerwheelangle) > lka_cal_.k_steer_angle_inhibit_deg,
                                              lka_cal_.k_steer_angle_inhibit_off_delay_s,
                                              kCycleTimeS)) {
        suppress_mask_ |= 0x8U;
    }

    // bit4: 方向盘角速度
    if (steer_angle_rate_inhibit_checker_.offDelay(std::fabs(vse_out.steerwheelangle_rate) > lka_cal_.k_steer_angle_rate_inhibit_degps,
                                                   lka_cal_.k_steer_angle_rate_inhibit_off_delay_s,
                                                   kCycleTimeS)) {
        suppress_mask_ |= 0x10U;
    }

    // bit5: 双闪
    if (hazard_inhibit_checker_.offDelay(vse_out.hazard_lamp_st == 1U, lka_cal_.k_hazard_inhibit_off_delay_s, kCycleTimeS)) {
        suppress_mask_ |= 0x20U;
    }

    //bit6: 纵向加速度
    if (long_accel_inhibit_checker_.offDelay(std::fabs(vse_out.long_accel) > lka_cal_.k_long_accel_inhibit_mpss, lka_cal_.k_long_accel_inhibit_off_delay_s, kCycleTimeS)) {
        suppress_mask_ |= 0x40U;
    } 

    // bit7:挡位
    if (gear_inhibit_checker_.offDelay(vse_out.actual_gear != 3U, lka_cal_.k_gear_inhibit_off_delay_s, kCycleTimeS)) {
        suppress_mask_ |= 0x80U;
    }

    // bit8: 脱手
    if (hands_off_inhibit_checker_.process(std::fabs(vse_out.torsion_bar_trq),
                                           lka_cal_.k_hands_off_inhibit_on_nm,
                                           lka_cal_.k_hands_off_inhibit_off_nm,
                                           lka_cal_.k_hands_off_inhibit_on_delay_s,
                                           lka_cal_.k_hands_off_inhibit_off_delay_s,
                                           kCycleTimeS,
                                           false,
                                           true)) {
        suppress_mask_ |= 0x100U;
    }

    // bit9: EPS 不可用或故障
    const bool eps_unavailable_or_fault =
        (vse_out.lka_trq_ovl_dlvd_stat == 2U) || (vse_out.lka_trq_ovl_dlvd_stat == 3U);
    if (eps_available_inhibit_checker_.offDelay(eps_unavailable_or_fault,
                                                lka_cal_.k_eps_available_inhibit_off_delay_s,
                                                kCycleTimeS)) {
        suppress_mask_ |= 0x200U;
    }

    // bit10: 驾驶员手力矩接管，判定和延时逻辑与 ELK 普通场景保持一致。
    const float override_torque_threshold = math::LookUpTable::LookupTable1D<7>(
        lka_cal_.k_LKA_ovrd_tq_thd_per_spd_x,
        lka_cal_.k_LKA_ovrd_tq_thd_per_spd_z,
        vse_out.display_speed);
    updateSteerTorqueSuppressHistory(std::fabs(vse_out.torsion_bar_trq) >= override_torque_threshold);
    const bool steer_torque_history_suppressed = isSteerTorqueHistorySuppressed();
    if (steer_torque_inhibit_checker_.process(steer_torque_history_suppressed ? 1.0F : 0.0F,
                                              1.0F,
                                              0.0F,
                                              lka_cal_.k_LKA_DriHandsOvr_OnDlyTime,
                                              lka_cal_.k_LKA_DriHandsOvr_OffDlyTime,
                                              kCycleTimeS,
                                              true,
                                              false)) {
        suppress_mask_ |= kDriverTorqueOverrideSuppressBit;
    }

    // bit11: 方向盘手力矩和踏板输入共同表征的驾驶员主动接管意图。
    constexpr float kKpaToBar = 0.01F;
    const float steer_score = calcScore(std::fabs(vse_out.torsion_bar_trq), override_torque_threshold);
    const float accel_score =
        calcScore(vse_out.gas_pedal_pos, lka_cal_.k_driver_intent_accel_pedal_threshold_pct);
    const float brake_pressure_score = calcScore(kKpaToBar * vse_out.brake_pressure,
                                                 lka_cal_.k_driver_intent_brake_pressure_threshold_bar);
    const float brake_pedal_score =
        calcScore(vse_out.brake_pedal_pos, lka_cal_.k_driver_intent_brake_pedal_threshold_pct);
    const float pedal_score = std::max(accel_score, std::max(brake_pressure_score, brake_pedal_score));
    const float driver_intent_score = lka_cal_.k_driver_intent_steer_weight * steer_score +
                                      lka_cal_.k_driver_intent_pedal_weight * pedal_score;
    if (driver_intent_inhibit_checker_.offDelay(updateDriverIntentScoreHistory(driver_intent_score),
                                                lka_cal_.k_driver_intent_off_delay_s,
                                                kCycleTimeS)) {
        suppress_mask_ |= kDriverIntentSuppressBit;
    }
}

LkaStateMachine::Condition LkaStateMachine::BuildCondition(const AsVseOut &vse_out,
                                                           const elk::LaneBoundaryParameters &lane_boundary,
                                                           const elk::LaneCenterParameters &lane_center,
                                                           const GlobalConfig &config) {
    Condition condition;
    const bool enabled = config.k_LKA_func_enable || (vse_out.lka_switch == 1U);
    const bool upstream_fault_inhibit = (vse_out.function_did_config & kLatSafeFaultMask) != 0U;
    const bool fault_inhibit = !config.k_LSS_IgnoreFaultInhibit && upstream_fault_inhibit;

    const float speed_kph = vse_out.display_speed + lka_cal_.k_speed_compensation_kph;
    const bool standby_enable = checkStandby2Enable(speed_kph, lane_boundary, lane_center);
    bool left_trigger = false;
    bool right_trigger = false;
    if (state_ == State::LeftSuppressed) {
        left_trigger = determineLeftIntervention(
            lane_boundary, lane_center, config, speed_kph, TtcCheckMode::SuppressedExit);
        resetTtcHistory(right_ttc_history_);
    } else if (state_ == State::RightSuppressed) {
        right_trigger = determineRightIntervention(
            lane_boundary, lane_center, config, speed_kph, TtcCheckMode::SuppressedExit);
        resetTtcHistory(left_ttc_history_);
    } else {
        left_trigger =
            determineLeftIntervention(lane_boundary, lane_center, config, speed_kph, TtcCheckMode::Activation);
        right_trigger =
            determineRightIntervention(lane_boundary, lane_center, config, speed_kph, TtcCheckMode::Activation);
    }
    const bool left_suppressed_now = leftSuppressed(vse_out);
    const bool right_suppressed_now = rightSuppressed(vse_out);
    const bool aligned = checkAligned(lane_center, config);
    const uint16_t retrigger_window_cycle = static_cast<uint16_t>(lka_cal_.k_retrigger_suppressed_window_s / kCycleTimeS);
    const uint16_t intervention_abort_timeout_cycle = static_cast<uint16_t>(lka_cal_.k_intervention_abort_timeout_s / kCycleTimeS);

    left_trigger_ = left_trigger;
    right_trigger_ = right_trigger;

    condition.fault_to_off = !fault_inhibit;
    condition.off_to_fault = fault_inhibit;
    condition.off_to_standby = enabled;
    condition.standby_to_off = !enabled;

    condition.standby_to_enable = standby_enable && ((suppress_mask_ & lka_cal_.k_standby_enable_mask) == 0);
    condition.enable_to_standby = checkEnable2Standby(speed_kph);
    condition.enable_to_off = !enabled;
    condition.enable_to_left_intervention = left_trigger && (!right_trigger) && (!left_suppressed_now);
    condition.enable_to_right_intervention = right_trigger && (!left_trigger) && (!right_suppressed_now);

    condition.left_to_right_intervention = condition.enable_to_right_intervention;
    condition.right_to_left_intervention = condition.enable_to_left_intervention;
    
    // 进入干预后才开始计时，超过6s终止
    condition.intervention_timeout = intervention_duration_frame_count_ >= intervention_abort_timeout_cycle;

    condition.left_to_abort = left_suppressed_now || condition.intervention_timeout;
    condition.right_to_abort = right_suppressed_now || condition.intervention_timeout;

    condition.left_to_completed = aligned;
    condition.right_to_completed = condition.left_to_completed;

    // 进入 abort 或 completed 状态后开始计数，达到阈值后回到 enable。
    if (state_ == State::InterventionAbort) {
        abort_state_frame_count_ = std::min<uint8_t>(static_cast<uint8_t>(abort_state_frame_count_ + 1U), static_cast<uint8_t>(255U));
    } else {
        abort_state_frame_count_ = 0U;
    }

    if (state_ == State::InterventionCompleted) {
        completed_state_frame_count_ =
            std::min<uint8_t>(static_cast<uint8_t>(completed_state_frame_count_ + 1U), static_cast<uint8_t>(255U));
    } else {
        completed_state_frame_count_ = 0U;
    }

    condition.abort_to_enable = abort_state_frame_count_ >= lka_cal_.k_abort_to_enable_cycle;
    condition.completed_to_enable = completed_state_frame_count_ >= lka_cal_.k_completed_to_enable_cycle;

    //纠偏结束后，进入5s冷却时间，所以每次触发后没有常规抑制条件就会进suppressed维持5s
    condition.within_retrigger_suppressed_window = recent_intervention_end_frame_count_ <= retrigger_window_cycle;// 纠偏相关：干预触发后，如果在5s内持续有抑制输入，则进入抑制状态；如果没有抑制输入且车辆回到车道中心，则恢复使能状态。

    condition.enable_to_left_suppressed =
        left_trigger && (left_suppressed_now || condition.within_retrigger_suppressed_window);
    condition.enable_to_right_suppressed =
        right_trigger && (right_suppressed_now || condition.within_retrigger_suppressed_window);
    condition.left_suppressed_to_enable = !condition.enable_to_left_suppressed;
    condition.right_suppressed_to_enable = !condition.enable_to_right_suppressed;

    return condition;
}

void LkaStateMachine::UpdateInterventionTimers(State prev_state) {
    if (IsInterventionState(state_)) {
        intervention_duration_frame_count_ = IsInterventionState(prev_state) ? SaturatingInc(intervention_duration_frame_count_) : 0U;
    } else {
        intervention_duration_frame_count_ = 0U;
    }

    if (!IsInterventionState(state_) && IsInterventionState(prev_state)) {
        recent_intervention_end_frame_count_ = 0U;
    } else {
        recent_intervention_end_frame_count_ = SaturatingInc(recent_intervention_end_frame_count_);
    }
}

bool LkaStateMachine::checkStandby2Enable(float speed_kph,
                                          const elk::LaneBoundaryParameters &lane_boundary,
                                          const elk::LaneCenterParameters &lane_center) {
    // 使能位定义：
    // bit0 车速，bit1 中心线有效，bit2 左车道线有效，
    // bit3 右车道线有效，bit4 曲率有效，bit5 车道宽度有效。
    enable_mask_ = 0;

    const bool speed_valid = (speed_kph >= lka_cal_.k_enable_min_speed_kph) && (speed_kph <= lka_cal_.k_enable_max_speed_kph);
    if (speed_valid) {
        enable_mask_ |= 0x1U;
    }

    const bool center_valid = lane_center.vld;
    if (center_valid) {
        enable_mask_ |= 0x2U;
    }

    const bool left_marker_valid =
        left_marker_valid_checker_.onDelay(lane_boundary.lftBdryVld, lka_cal_.k_marker_valid_on_delay_s, kCycleTimeS);
    if (left_marker_valid) {
        enable_mask_ |= 0x4U;
    }

    const bool right_marker_valid =
        right_marker_valid_checker_.onDelay(lane_boundary.rgtBdryVld, lka_cal_.k_marker_valid_on_delay_s, kCycleTimeS);
    if (right_marker_valid) {
        enable_mask_ |= 0x8U;
    }

    const bool curvature_valid = lane_curv_valid_checker_.process(std::fabs(lane_boundary.frtAxlCurv),
                                                                  lka_cal_.k_lane_curvature_valid_on,
                                                                  lka_cal_.k_lane_curvature_valid_off,
                                                                  false,
                                                                  true);
    if (curvature_valid) {
        enable_mask_ |= 0x10U;
    }

    const bool min_width_valid = min_lane_width_checker_.process(lane_boundary.laneWidth,
                                                                 lka_cal_.k_lane_width_min_on_m,
                                                                 lka_cal_.k_lane_width_min_off_m,
                                                                 true,
                                                                 false);
    const bool max_width_valid = max_lane_width_checker_.process(lane_boundary.laneWidth,
                                                                 lka_cal_.k_lane_width_max_on_m,
                                                                 lka_cal_.k_lane_width_max_off_m,
                                                                 false,
                                                                 true);
    if (min_width_valid && max_width_valid) {
        enable_mask_ |= 0x20U;
    }

    return speed_valid && center_valid && left_marker_valid && right_marker_valid && curvature_valid && min_width_valid && max_width_valid;
}

bool LkaStateMachine::checkEnable2Standby(float speed_kph) const {
    constexpr uint16_t kNonSpeedEnableMask = 0x3EU;
    const bool speed_valid = speed_kph >= lka_cal_.k_exit_min_speed_kph && speed_kph <= lka_cal_.k_exit_max_speed_kph;
    const bool non_speed_enable_valid = (enable_mask_ & kNonSpeedEnableMask) == kNonSpeedEnableMask;
    const bool suppression_cleared = (suppress_mask_ & lka_cal_.k_standby_enable_mask) == 0U;
    return !(speed_valid && non_speed_enable_valid && suppression_cleared);
}

bool LkaStateMachine::checkAligned(const elk::LaneCenterParameters &lane_center, const GlobalConfig &config) {
    const bool aligned = lane_center.vld && std::fabs(lane_center.c0) < lka_cal_.k_centered_c0_abs_m &&
                          std::fabs(lane_center.c1) < lka_cal_.k_centered_c1_abs;
    return aligned_checker_.onDelay(aligned, config.k_LKA_Centered_OnDelayTime, kCycleTimeS);
}

bool LkaStateMachine::determineLeftIntervention(const elk::LaneBoundaryParameters &lane_boundary,
                                                const elk::LaneCenterParameters &lane_center,
                                                const GlobalConfig &config,
                                                float speed_kph,
                                                TtcCheckMode ttc_mode) {
    (void)lane_center;
    const bool near_left_boundary = lane_boundary.lftBdryVld && lane_boundary.curLftDisToBdry < lka_cal_.k_intervention_boundary_maxdist_m && 
                                    lane_boundary.curLftDisToBdry > lka_cal_.k_intervention_boundary_mindist_m;
    const bool left_boundary_quality_valid = !lane_boundary.lftBdryJump && !lane_boundary.lftBdryRangeShort;
    //主要考虑ttlc触发困难的小横向速度场景                                
    const bool drifting_to_left = (lane_boundary.lftBdryLatRt < lka_cal_.k_left_boundary_lat_rate_mps && lane_boundary.lftBdryLatRt > 0.0F)||
                                  lane_boundary.lftBdryHdgDeg > lka_cal_.k_left_boundary_heading_deg;
    const float ttlc_threshold = calcSpeedBasedTtcThreshold(speed_kph) * config.k_LKA_TTLCScale;
    const bool left_ttlc_urgent = checkTtcDeparture(left_ttc_history_,
                                                    lane_boundary.lftBdryTtlc,
                                                    ttlc_threshold,
                                                    near_left_boundary && left_boundary_quality_valid,
                                                    ttc_mode);
    //const bool lane_offset_left = lane_center.vld && lane_center.c0 < lka_cal_.k_left_lane_offset_m;
    return near_left_boundary && left_boundary_quality_valid &&
           (left_ttlc_urgent || (config.k_LKA_LDW_EnDriftingTrigger && drifting_to_left));
}

bool LkaStateMachine::determineRightIntervention(const elk::LaneBoundaryParameters &lane_boundary,
                                                 const elk::LaneCenterParameters &lane_center,
                                                 const GlobalConfig &config,
                                                 float speed_kph,
                                                 TtcCheckMode ttc_mode) {
    (void)lane_center;
    const bool near_right_boundary = lane_boundary.rgtBdryVld && lane_boundary.curRgtDisToBdry < lka_cal_.k_intervention_boundary_maxdist_m && 
                                     lane_boundary.curRgtDisToBdry > lka_cal_.k_intervention_boundary_mindist_m;
    const bool right_boundary_quality_valid = !lane_boundary.rgtBdryJump && !lane_boundary.rgtBdryRangeShort;
    //主要考虑ttlc触发困难的小横向速度场景                                
    const bool drifting_to_right = (lane_boundary.rgtBdryLatRt > lka_cal_.k_right_boundary_lat_rate_mps && lane_boundary.rgtBdryLatRt < 0.0F)||
                                   lane_boundary.rgtBdryHdgDeg < lka_cal_.k_right_boundary_heading_deg;
    const float ttlc_threshold = calcSpeedBasedTtcThreshold(speed_kph) * config.k_LKA_TTLCScale;
    const bool right_ttlc_urgent = checkTtcDeparture(right_ttc_history_,
                                                     lane_boundary.rgtBdryTtlc,
                                                     ttlc_threshold,
                                                     near_right_boundary && right_boundary_quality_valid,
                                                     ttc_mode);
    //const bool lane_offset_right = lane_center.vld && lane_center.c0 > lka_cal_.k_right_lane_offset_m;
    return near_right_boundary && right_boundary_quality_valid &&
           (right_ttlc_urgent || (config.k_LKA_LDW_EnDriftingTrigger && drifting_to_right));
}

bool LkaStateMachine::commonSuppressed() const {
    return (suppress_mask_ & lka_cal_.k_enable_suppressed_mask) != 0U;
}

bool LkaStateMachine::leftSuppressed(const AsVseOut &vse_out) const {
    return commonSuppressed() || (vse_out.turn_light_switch_pos == 1U);
}

bool LkaStateMachine::rightSuppressed(const AsVseOut &vse_out) const {
    return commonSuppressed() || (vse_out.turn_light_switch_pos == 3U);
}

void LkaStateMachine::UpdateStateMachine(const Condition &condition) {
    if ((state_ != State::Fault)  &&  condition.off_to_fault) {
        state_ = State::Fault;
        return;
    }

    if ((state_ != State::Off) && (state_ != State::Fault) && condition.enable_to_off) {
        state_ = State::Off;
        return;
    }

    if ((state_ != State::Off)  &&  (state_ != State::Fault)  &&  (state_ != State::Standby)  &&  condition.enable_to_standby) {
        state_ = condition.standby_to_off ? State::Off : State::Standby;
        return;
    }

    switch (state_) {
        case State::Fault:
            if (condition.fault_to_off) {
                state_ = State::Off;
            }
            break;
        case State::Off:
            if (condition.off_to_fault) {
                state_ = State::Fault;
            } else if (condition.off_to_standby) {
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
            } else if (condition.enable_to_left_intervention) {
                state_ = State::LeftIntervention;
            } else if (condition.enable_to_right_intervention) {
                state_ = State::RightIntervention;
            } else if (condition.enable_to_left_suppressed) {
                state_ = State::LeftSuppressed;
            } else if (condition.enable_to_right_suppressed) {
                state_ = State::RightSuppressed;
            }
            break;
        case State::LeftIntervention:
            if (condition.left_to_right_intervention) {
                state_ = State::RightIntervention;
            } else if (condition.left_to_abort) {
                state_ = State::InterventionAbort;
            } else if (condition.left_to_completed) {
                state_ = State::InterventionCompleted;
            }
            break;
        case State::RightIntervention:
            if (condition.right_to_left_intervention) {
                state_ = State::LeftIntervention;
            } else if (condition.right_to_abort) {
                state_ = State::InterventionAbort;
            } else if (condition.right_to_completed) {
                state_ = State::InterventionCompleted;
            }
            break;
        case State::InterventionAbort:
            if (condition.abort_to_enable) {
                state_ = State::Enable;
            }
            break;
        case State::InterventionCompleted:
            if (condition.completed_to_enable) {
                state_ = State::Enable;
            }
            break;
        case State::LeftSuppressed:
            if (condition.left_suppressed_to_enable) {
                state_ = State::Enable;
            }
            break;
        case State::RightSuppressed:
            if (condition.right_suppressed_to_enable) {
                state_ = State::Enable;
            }
            break;
        default:
            state_ = State::Off;
            break;
    }
}

} // namespace lka
} // namespace active_safety
