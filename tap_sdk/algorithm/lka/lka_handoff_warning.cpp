#include "lka_handoff_warning.h"

#include <cmath>

namespace active_safety {
namespace lka {
namespace {

constexpr uint8_t kLeftInterventionMode = 4U;
constexpr uint8_t kRightInterventionMode = 5U;
constexpr uint8_t kHandsOffConfirmFrames = 30U;
constexpr uint8_t kHandsOnConfirmFrames = 30U;
constexpr float kHandsOffTorqueThreshold = 0.35F;
constexpr float kHandsOnTorqueThreshold = 0.45F;
constexpr float kControlCycleTimeSeconds = 0.02F;
constexpr float kTimeComparisonToleranceSeconds = 1.0e-6F;
constexpr uint8_t kHodHandsOff = 1U;
constexpr uint8_t kHodHandsTouch = 2U;
constexpr uint8_t kHodHandsShake = 3U;
constexpr uint64_t kNsPerSecond = 1000000000ULL;
constexpr uint64_t kInterventionResetNs = 180ULL * kNsPerSecond;
constexpr uint64_t kWarningStepNs = 10ULL * kNsPerSecond;
constexpr uint8_t kVisualAlarm = 1U;
constexpr uint8_t kSecondaryAlarm = 2U;

} // namespace

bool LkaElkHandoffWarning::IsActiveMode(uint8_t mode) {
    return mode == kLeftInterventionMode || mode == kRightInterventionMode;
}

uint8_t LkaElkHandoffWarning::SaturatingIncrement(uint8_t value) {
    return value == UINT8_MAX ? UINT8_MAX : static_cast<uint8_t>(value + 1U);
}

uint8_t LkaElkHandoffWarning::SaturatingFrameIncrement(uint8_t value, uint8_t maximum) {
    return value >= maximum ? maximum : static_cast<uint8_t>(value + 1U);
}

uint64_t LkaElkHandoffWarning::WarningDurationNs(uint8_t intervention_count) {
    if (intervention_count < 2U) {
        return 0U;
    }
    return static_cast<uint64_t>(intervention_count - 1U) * kWarningStepNs;
}

bool LkaElkHandoffWarning::IsElapsed(uint64_t now_ns, uint64_t start_ns, uint64_t duration_ns) {
    return now_ns >= start_ns && now_ns - start_ns >= duration_ns;
}

void LkaElkHandoffWarning::Reset() {
    lka_tracker_ = InterventionTracker{};
    elk_tracker_ = InterventionTracker{};
    hands_off_confirmed_ = false;
    low_torque_frame_count_ = 0U;
    high_torque_frame_count_ = 0U;
    hod_hands_off_frame_count_ = 0U;
    hod_hands_on_frame_count_ = 0U;
    has_last_timestamp_ = false;
    last_timestamp_ns_ = 0U;
}

void LkaElkHandoffWarning::UpdateTorqueHandsOff(float hands_torque) {
    const float abs_torque = std::fabs(hands_torque);
    if (abs_torque <= kHandsOffTorqueThreshold) {
        low_torque_frame_count_ = SaturatingFrameIncrement(low_torque_frame_count_, kHandsOffConfirmFrames);
        high_torque_frame_count_ = 0U;
        if (low_torque_frame_count_ >= kHandsOffConfirmFrames) {
            hands_off_confirmed_ = true;
        }
    } else if (abs_torque >= kHandsOnTorqueThreshold) {
        high_torque_frame_count_ = SaturatingFrameIncrement(high_torque_frame_count_, kHandsOnConfirmFrames);
        low_torque_frame_count_ = 0U;
        if (high_torque_frame_count_ >= kHandsOnConfirmFrames) {
            hands_off_confirmed_ = false;
        }
    } else {
        // 滞回区既不确认脱手也不取消脱手，但会中断两侧的连续帧计数。
        low_torque_frame_count_ = 0U;
        high_torque_frame_count_ = 0U;
    }
}

void LkaElkHandoffWarning::UpdateHandsOff(float hands_torque,
                                          uint8_t hod_hands_monitor,
                                          float hod_hands_off_confirm_time_s,
                                          float hod_hands_on_confirm_time_s) {
    const bool hod_hands_off = hod_hands_monitor == kHodHandsOff;
    const bool hod_hands_on = hod_hands_monitor == kHodHandsTouch || hod_hands_monitor == kHodHandsShake;
    if (!hod_hands_off && !hod_hands_on) {
        // HOD无效或不在线时立即回退扭矩；切源会清除HOD未完成计时。
        hod_hands_off_frame_count_ = 0U;
        hod_hands_on_frame_count_ = 0U;
        UpdateTorqueHandsOff(hands_torque);
        return;
    }

    // HOD有效时优先使用电容方向盘；切源会清除扭矩未完成计时。
    low_torque_frame_count_ = 0U;
    high_torque_frame_count_ = 0U;
    if (hod_hands_off) {
        hod_hands_off_frame_count_ = hod_hands_off_frame_count_ == UINT32_MAX
                                         ? UINT32_MAX
                                         : hod_hands_off_frame_count_ + 1U;
        hod_hands_on_frame_count_ = 0U;
        const float confirm_time_s = std::fmax(hod_hands_off_confirm_time_s, 0.0F);
        const float elapsed_time_s = static_cast<float>(hod_hands_off_frame_count_) * kControlCycleTimeSeconds;
        if (elapsed_time_s + kTimeComparisonToleranceSeconds >= confirm_time_s) {
            hands_off_confirmed_ = true;
        }
    } else {
        // Hands Touch与Hands Shake都表示Hands On，二者切换不中断连续计时。
        hod_hands_on_frame_count_ = hod_hands_on_frame_count_ == UINT32_MAX
                                        ? UINT32_MAX
                                        : hod_hands_on_frame_count_ + 1U;
        hod_hands_off_frame_count_ = 0U;
        const float confirm_time_s = std::fmax(hod_hands_on_confirm_time_s, 0.0F);
        const float elapsed_time_s = static_cast<float>(hod_hands_on_frame_count_) * kControlCycleTimeSeconds;
        if (elapsed_time_s + kTimeComparisonToleranceSeconds >= confirm_time_s) {
            hands_off_confirmed_ = false;
        }
    }
}

void LkaElkHandoffWarning::UpdateTracker(InterventionTracker &tracker, bool active, uint64_t now_ns) {
    if (tracker.has_last_event_time && IsElapsed(now_ns, tracker.last_event_time_ns, kInterventionResetNs)) {
        tracker.intervention_count = 0U;
        tracker.pending_increment = false;
        tracker.has_last_event_time = false;
        tracker.warning_window_active = false;
        tracker.warning_window_start_ns = 0U;
        tracker.warning_window_duration_ns = 0U;
    }

    // 第二次及以后介入在上升沿后的下一帧增加次数。
    if (tracker.pending_increment) {
        tracker.intervention_count = SaturatingIncrement(tracker.intervention_count);
        tracker.pending_increment = false;
    }

    const bool rising_edge = !tracker.previous_active && active;
    if (rising_edge) {
        if (tracker.intervention_count == 0U) {
            tracker.intervention_count = 1U;
            tracker.warning_window_active = false;
            tracker.warning_window_start_ns = 0U;
            tracker.warning_window_duration_ns = 0U;
        } else {
            const uint8_t event_count = SaturatingIncrement(tracker.intervention_count);
            if (tracker.intervention_count != UINT8_MAX) {
                tracker.pending_increment = true;
            }
            tracker.warning_window_active = true;
            tracker.warning_window_start_ns = now_ns;
            tracker.warning_window_duration_ns = WarningDurationNs(event_count);
        }
        tracker.has_last_event_time = true;
        tracker.last_event_time_ns = now_ns;
    }
    tracker.previous_active = active;
}

uint8_t LkaElkHandoffWarning::CalculateAlarmLevel(InterventionTracker &tracker,
                                                   bool active,
                                                   bool output_enabled,
                                                   uint64_t now_ns) {
    if (!output_enabled || !active) {
        return 0U;
    }
    if (tracker.intervention_count < 2U || !tracker.warning_window_active) {
        return kVisualAlarm;
    }
    if (!IsElapsed(now_ns, tracker.warning_window_start_ns, tracker.warning_window_duration_ns)) {
        return kSecondaryAlarm;
    }
    tracker.warning_window_active = false;
    return kVisualAlarm;
}

void LkaElkHandoffWarning::Update(uint8_t lka_mode,
                                  uint8_t elk_mode,
                                  float hands_torque,
                                  uint8_t hod_hands_monitor,
                                  float hod_hands_off_confirm_time_s,
                                  float hod_hands_on_confirm_time_s,
                                  bool mcu_lfp_actv_cdt,
                                  bool enable,
                                  bool shadow_mode,
                                  uint64_t now_ns) {
    const bool lka_active = IsActiveMode(lka_mode);
    const bool elk_active = IsActiveMode(elk_mode);
    output_ = HandoffWarningOutput{};
    output_.lka_active_flag = lka_active;
    output_.elk_active_flag = elk_active;

    if (!enable) {
        Reset();
        return;
    }
    if (has_last_timestamp_ && now_ns < last_timestamp_ns_) {
        Reset();
        return;
    }
    has_last_timestamp_ = true;
    last_timestamp_ns_ = now_ns;

    UpdateHandsOff(hands_torque,
                   hod_hands_monitor,
                   hod_hands_off_confirm_time_s,
                   hod_hands_on_confirm_time_s);
    UpdateTracker(lka_tracker_, lka_active, now_ns);
    UpdateTracker(elk_tracker_, elk_active, now_ns);

    const bool output_enabled = hands_off_confirmed_ && !mcu_lfp_actv_cdt && !shadow_mode;
    output_.lka_secondary_alarm_end_flag = CalculateAlarmLevel(lka_tracker_, lka_active, output_enabled, now_ns);
    output_.elk_secondary_alarm_end_flag = CalculateAlarmLevel(elk_tracker_, elk_active, output_enabled, now_ns);
}

} // namespace lka
} // namespace active_safety
