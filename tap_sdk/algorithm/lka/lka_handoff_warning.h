#ifndef TAP_SDK_ALGORITHM_LKA_LKA_HANDOFF_WARNING_H_
#define TAP_SDK_ALGORITHM_LKA_LKA_HANDOFF_WARNING_H_

#include <cstdint>

namespace active_safety {
namespace lka {

// LKA/ELK 脱手报警的内部输出。报警等级：0=无，1=视觉，2=视觉+听觉+弹窗。
struct HandoffWarningOutput {
    uint8_t lka_secondary_alarm_end_flag = 0U;
    uint8_t elk_secondary_alarm_end_flag = 0U;
    bool lka_active_flag = false;
    bool elk_active_flag = false;
};

class LkaElkHandoffWarning {
  public:
    void Update(uint8_t lka_mode,
                uint8_t elk_mode,
                float hands_torque,
                bool mcu_lfp_actv_cdt,
                bool enable,
                bool shadow_mode,
                uint64_t now_ns);

    const HandoffWarningOutput &GetOutput() const { return output_; }

  private:
    struct InterventionTracker {
        bool previous_active = false;
        bool pending_increment = false;
        uint8_t intervention_count = 0U;
        bool has_last_event_time = false;
        uint64_t last_event_time_ns = 0U;
        bool warning_window_active = false;
        uint64_t warning_window_start_ns = 0U;
        uint64_t warning_window_duration_ns = 0U;
    };

    static bool IsActiveMode(uint8_t mode);
    static uint8_t SaturatingIncrement(uint8_t value);
    static uint8_t SaturatingFrameIncrement(uint8_t value, uint8_t maximum);
    static uint64_t WarningDurationNs(uint8_t intervention_count);
    static bool IsElapsed(uint64_t now_ns, uint64_t start_ns, uint64_t duration_ns);

    void Reset();
    void UpdateHandsOff(float hands_torque);
    void UpdateTracker(InterventionTracker &tracker, bool active, uint64_t now_ns);
    uint8_t CalculateAlarmLevel(InterventionTracker &tracker, bool active, bool output_enabled, uint64_t now_ns);

    HandoffWarningOutput output_;
    InterventionTracker lka_tracker_;
    InterventionTracker elk_tracker_;
    bool hands_off_confirmed_ = false;
    uint8_t low_torque_frame_count_ = 0U;
    uint8_t high_torque_frame_count_ = 0U;
    bool has_last_timestamp_ = false;
    uint64_t last_timestamp_ns_ = 0U;
};

} // namespace lka
} // namespace active_safety

#endif // TAP_SDK_ALGORITHM_LKA_LKA_HANDOFF_WARNING_H_
