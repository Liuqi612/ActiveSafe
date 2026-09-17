#ifndef TAP_SDK_ALGORITHM_LKA_LKA_STATE_MACHINE_H_
#define TAP_SDK_ALGORITHM_LKA_LKA_STATE_MACHINE_H_

#include "algorithm/elk/environment_processing.h"
#include "common/global_config.h"
#include "interface/active_safety_vse.h"
#include "lka_cals.h"
#include "lka_types.h"
#include "math/signalprocess/off_delay_block/off_delay_block.h"
#include "math/signalprocess/on_delay_block/on_delay_block.h"
#include "math/signalprocess/relay_block/relay_block.h"
#include "math/signalprocess/relay_block/relay_on_off_delay_block.h"

#include <array>
#include <cstddef>
#include <cstdint>

namespace active_safety {
namespace lka {

// 轻量级 LKA 状态机。
// 组织方式对齐 ELK，但只保留车道保持干预所需的条件判断。
class LkaStateMachine {
  public:
    enum class State : uint8_t {
        Fault = 0,
        Off,
        Standby,
        Enable,
        LeftIntervention,
        RightIntervention,
        InterventionCompleted,
        InterventionAbort,
        LeftSuppressed,
        RightSuppressed
    };

    struct Condition {
        bool fault_to_off = false;
        bool off_to_fault = false;
        bool off_to_standby = false;
        bool standby_to_off = false;
        bool standby_to_enable = false;
        bool enable_to_standby = false;
        bool enable_to_off = false;
        bool enable_to_left_intervention = false;
        bool enable_to_right_intervention = false;
        bool left_to_right_intervention = false;
        bool right_to_left_intervention = false;
        bool left_to_abort = false;
        bool right_to_abort = false;
        bool intervention_timeout = false;
        bool within_retrigger_suppressed_window = false;
        bool left_to_completed = false;
        bool right_to_completed = false;
        bool abort_to_enable = false;
        bool completed_to_enable = false;
        bool enable_to_left_suppressed = false;
        bool enable_to_right_suppressed = false;
        bool left_suppressed_to_enable = false;
        bool right_suppressed_to_enable = false;
    };

    LkaStateMachine() = default;
    ~LkaStateMachine() = default;

    // 根据当前车辆状态和车道特征推进 LKA 状态机。
    void Update(const AsVseOut &vse_out,
                const elk::LaneBoundaryParameters &lane_boundary,
                const elk::LaneCenterParameters &lane_center,
                const GlobalConfig &config);

    State getCurrentState() const { return state_; }
    uint32_t getSuppressMask() const { return suppress_mask_; }
    uint16_t getEnableMask() const { return enable_mask_; }
    bool isAvailable() const { return available_; }
    bool isLeftTriggerActive() const { return left_trigger_; }
    bool isRightTriggerActive() const { return right_trigger_; }
    bool isLeftInterventionActive() const { return state_ == State::LeftIntervention; }
    bool isRightInterventionActive() const { return state_ == State::RightIntervention; }

  private:
    enum class TtcCheckMode : uint8_t {
        Activation = 0,
        SuppressedExit
    };

    struct TtcHistory {
        std::array<float, 3> ttlc{{0.0F, 0.0F, 0.0F}};
        uint8_t valid_frame_count = 0U;
        uint8_t invalid_ttlc_count = 0U;
    };

    static bool IsInterventionState(State state) {
        return state == State::LeftIntervention || state == State::RightIntervention;
    }
    static uint16_t SaturatingInc(uint16_t value) {
        return value < static_cast<uint16_t>(0xFFFFU) ? static_cast<uint16_t>(value + 1U) : value;
    }

    // 计算驾驶员输入和车辆状态带来的抑制位。
    void checkDriverSuppression(const AsVseOut &vse_out);
    // 更新驾驶员手力矩接管判定的环形历史缓存。
    void updateSteerTorqueSuppressHistory(bool suppress_condition);
    // 判断最近标定帧数中达到手力矩阈值的帧数是否足够。
    bool isSteerTorqueHistorySuppressed() const;
    // 综合方向盘和踏板输入，判断驾驶员接管意图是否连续成立。
    bool updateDriverIntentScoreHistory(float driver_intent_score);
    // 清空、更新并判断单侧 TTLC 三帧稳定性。
    void resetTtcHistory(TtcHistory &history);
    bool checkStableTtcDeparture(TtcHistory &history, float ttlc, float threshold, bool history_enabled);
    bool checkTtcDeparture(TtcHistory &history,
                           float ttlc,
                           float threshold,
                           bool history_enabled,
                           TtcCheckMode mode);
    float calcSpeedBasedTtcThreshold(float speed_kph) const;
    // 判断 Standby 是否满足进入 Enable 的基础条件。
    bool checkStandby2Enable(float speed_kph, const elk::LaneBoundaryParameters &lane_boundary, const elk::LaneCenterParameters &lane_center);
    // 判断 Enable 及其子状态是否需要退回 Standby。
    bool checkEnable2Standby(float speed_kph) const;
    // 判断车辆是否已经稳定回到车道中心附近。
    bool checkAligned(const elk::LaneCenterParameters &lane_center, const GlobalConfig &config);
    // 判断是否需要触发左侧车道保持干预。
    bool determineLeftIntervention(const elk::LaneBoundaryParameters &lane_boundary,
                                   const elk::LaneCenterParameters &lane_center,
                                   const GlobalConfig &config,
                                   float speed_kph,
                                   TtcCheckMode ttc_mode);
    // 判断是否需要触发右侧车道保持干预。
    bool determineRightIntervention(const elk::LaneBoundaryParameters &lane_boundary,
                                    const elk::LaneCenterParameters &lane_center,
                                    const GlobalConfig &config,
                                    float speed_kph,
                                    TtcCheckMode ttc_mode);
    // 判断是否存在与方向无关的公共抑制条件。
    bool commonSuppressed() const;
    // 判断左侧干预是否应被驾驶员/车辆状态压制。
    bool leftSuppressed(const AsVseOut &vse_out) const;
    // 判断右侧干预是否应被驾驶员/车辆状态压制。
    bool rightSuppressed(const AsVseOut &vse_out) const;
    // 根据当前输入集中构造状态跳转条件。
    Condition BuildCondition(const AsVseOut &vse_out,
                             const elk::LaneBoundaryParameters &lane_boundary,
                             const elk::LaneCenterParameters &lane_center,
                             const GlobalConfig &config);
    // 根据条件表推进状态机。
    void UpdateStateMachine(const Condition &condition);
    // 维护纠偏持续时长和“上次纠偏结束后”的时间窗。
    void UpdateInterventionTimers(State prev_state);

    // TAP side-feature 模块运行周期为 50 Hz。
    static constexpr float kCycleTimeS = 0.02F;

    // 去抖/滞回模块，用于稳定可用性和抑制判断。
    math::OnDelayBlock left_marker_valid_checker_;
    math::OnDelayBlock right_marker_valid_checker_;
    math::RelayBlock lane_curv_valid_checker_;
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
    math::OffDelayBlock eps_available_inhibit_checker_;
    math::OnDelayBlock aligned_checker_;

    State state_ = State::Off;
    uint8_t abort_state_frame_count_ = 0U;
    uint8_t completed_state_frame_count_ = 0U;
    uint16_t recent_intervention_end_frame_count_ = 0xFFFFU;
    uint16_t intervention_duration_frame_count_ = 0U;
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
    TtcHistory left_ttc_history_;
    TtcHistory right_ttc_history_;
    LkaCal lka_cal_;
};

} // namespace lka
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LKA_LKA_STATE_MACHINE_H_
