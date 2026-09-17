#ifndef TAP_SDK_ALGORITHM_LDW_LDW_STATE_MACHINE_H_
#define TAP_SDK_ALGORITHM_LDW_LDW_STATE_MACHINE_H_

#include "common/global_config.h"
#include "interface/active_safety_vse.h"
#include "ldw_cals.h"
#include "ldw_types.h"
#include "math/signalprocess/off_delay_block/off_delay_block.h"
#include "math/signalprocess/on_delay_block/on_delay_block.h"
#include "math/signalprocess/relay_block/relay_block.h"
#include "math/signalprocess/relay_block/relay_on_off_delay_block.h"

#include <array>
#include <cstddef>
#include <cstdint>

namespace active_safety {
namespace ldw {

class LdwStateMachine {
  public:
    enum class State : uint8_t {
        Fault = 0,
        Off,
        Standby,
        Enable,
        LeftWarning,
        RightWarning
    };

    struct Condition {
        bool fault_to_off = false;
        bool off_to_fault = false;
        bool off_to_standby = false;
        bool standby_to_off = false;
        bool standby_to_enable = false;
        bool enable_to_standby = false;
        bool enable_to_off = false;
        bool enable_to_left_warning = false;
        bool enable_to_right_warning = false;
        bool left_warning_to_enable = false;
        bool right_warning_to_enable = false;
        bool left_warning_to_off = false;
        bool right_warning_to_off = false;
        bool left_warning_to_standby = false;
        bool right_warning_to_standby = false;
    };

    LdwStateMachine() = default;
    ~LdwStateMachine() = default;

    // 根据车辆状态和车道特征推进 LDW 状态机。
    void Update(const AsVseOut &vse_out,
                const LaneBoundaryParameters &lane_boundary,
                const LaneCenterParameters &lane_center,
                const GlobalConfig &config);

    State getCurrentState() const { return state_; }
    uint32_t getSuppressMask() const { return suppress_mask_; }
    uint16_t getEnableMask() const { return enable_mask_; }
    bool isAvailable() const { return available_; }
    bool isLeftWarningActive() const { return state_ == State::LeftWarning; }
    bool isRightWarningActive() const { return state_ == State::RightWarning; }
    bool isLeftDepartureDetected() const { return left_trigger_; }
    bool isRightDepartureDetected() const { return right_trigger_; }

  private:
    struct TtcHistory {
        std::array<float, 3> ttlc{{0.0F, 0.0F, 0.0F}};
        uint8_t valid_frame_count = 0U;
        uint8_t invalid_ttlc_count = 0U;
    };

    static constexpr float kCycleTimeS = 0.02F;
    static bool IsWarningState(State state) { return state == State::LeftWarning || state == State::RightWarning; }

    // 计算驾驶员输入和车辆状态带来的公共抑制位。
    void checkDriverSuppression(const AsVseOut &vse_out);
    void updateSteerTorqueSuppressHistory(bool suppress_condition);
    bool isSteerTorqueHistorySuppressed() const;
    bool updateDriverIntentScoreHistory(float driver_intent_score);
    void resetTtcHistory(TtcHistory &history);
    bool checkStableTtcDeparture(TtcHistory &history, float ttlc, float threshold, bool history_enabled);
    float calcSpeedBasedTtcThreshold(float speed_kph) const;
    // 判断 Standby 是否满足进入 Enable 的基础条件。
    bool checkStandby2Enable(const AsVseOut &vse_out,
                             const LaneBoundaryParameters &lane_boundary,
                             const LaneCenterParameters &lane_center,
                             const GlobalConfig &config);
    // 判断 Enable 及告警态是否需要退回 Standby。
    bool checkEnable2Standby(float speed_kph, const GlobalConfig &config) const;
    // 判断左侧是否满足车道偏离告警触发条件。
    bool determineLeftWarning(const AsVseOut &vse_out,
                              const LaneBoundaryParameters &lane_boundary,
                              const LaneCenterParameters &lane_center,
                              const GlobalConfig &config);
    // 判断右侧是否满足车道偏离告警触发条件。
    bool determineRightWarning(const AsVseOut &vse_out,
                               const LaneBoundaryParameters &lane_boundary,
                               const LaneCenterParameters &lane_center,
                               const GlobalConfig &config);
    // 判断 LDW 功能软开关是否允许模块离开 Off 态。
    bool switchEnabled(const AsVseOut &vse_out) const;

    // 判断是否存在方向无关的基础抑制。
    //bool commonSuppressed() const;
    
    // 判断左侧告警是否应被公共抑制或左转向灯压制。
    bool leftSuppressed(const AsVseOut &vse_out) const;
    // 判断右侧告警是否应被公共抑制或右转向灯压制。
    bool rightSuppressed(const AsVseOut &vse_out) const;
    // 按灵敏度配置计算当前告警 TTLC 门限。
    float warningTtlcThreshold(const AsVseOut &vse_out, const GlobalConfig &config) const;
    // 汇总本周期输入并构造状态跳转条件表。
    Condition BuildCondition(const AsVseOut &vse_out,
                             const LaneBoundaryParameters &lane_boundary,
                             const LaneCenterParameters &lane_center,
                             const GlobalConfig &config);
    // 根据条件表推进状态机状态。
    void UpdateStateMachine(const Condition &condition);
    // 维护告警态驻留时长，供最短/最长告警时间约束使用。
    void UpdateWarningTimers(State prev_state);

    math::OnDelayBlock left_marker_valid_checker_;
    math::OnDelayBlock right_marker_valid_checker_;
    math::OnDelayBlock left_edge_valid_checker_;
    math::OnDelayBlock right_edge_valid_checker_;
    math::RelayBlock lane_curv_valid_checker_;
    math::RelayBlock left_edge_curv_valid_checker_;
    math::RelayBlock right_edge_curv_valid_checker_;
    math::RelayBlock min_lane_width_checker_;
    math::RelayBlock max_lane_width_checker_;
    math::RelayOnOffDelayBlock yawrate_inhibit_checker_;
    math::OffDelayBlock brake_inhibit_checker_;
    math::OffDelayBlock accel_inhibit_checker_;
    math::OnDelayBlock low_speed_accel_pedal_inhibit_checker_;
    math::OffDelayBlock steer_angle_inhibit_checker_;
    math::OffDelayBlock steer_angle_rate_inhibit_checker_;
    math::OffDelayBlock hazard_inhibit_checker_;
    math::OffDelayBlock long_accel_inhibit_checker_;
    math::OffDelayBlock gear_inhibit_checker_;
    math::RelayOnOffDelayBlock hands_off_inhibit_checker_;
    math::RelayOnOffDelayBlock steer_torque_inhibit_checker_;
    math::OffDelayBlock driver_intent_inhibit_checker_;

    State state_ = State::Off;
    uint16_t warning_active_frame_count_ = 0;
    uint32_t suppress_mask_ = 0;
    uint16_t enable_mask_ = 0;
    bool available_ = false;
    bool left_trigger_ = false;
    bool right_trigger_ = false;
    std::array<bool, 10> steer_torque_suppress_history_{};
    std::size_t steer_torque_suppress_history_index_ = 0U;
    std::array<float, 3> driver_intent_score_history_{};
    std::array<bool, 3> driver_intent_score_valid_history_{};
    std::size_t driver_intent_score_history_index_ = 0U;
    uint8_t driver_intent_score_valid_count_ = 0U;
    TtcHistory left_line_ttc_history_;
    TtcHistory right_line_ttc_history_;
    TtcHistory left_edge_ttc_history_;
    TtcHistory right_edge_ttc_history_;
    LdwCal ldw_cal_;
};

} // namespace ldw
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LDW_LDW_STATE_MACHINE_H_
