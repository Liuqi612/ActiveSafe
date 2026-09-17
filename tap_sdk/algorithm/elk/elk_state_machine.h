#ifndef TAP_SDK_ALGORITHM_ELK_ELK_STATE_MACHINE_H_
#define TAP_SDK_ALGORITHM_ELK_ELK_STATE_MACHINE_H_

#include "environment_processing.h"
#include "elk_threat_assessment.h"
#include "elk_scenario_decision.h"
#include "interface/active_safety_vse.h"
#include "math/lookuptable/lookuptable.h"
#include "math/signalprocess/on_delay_block/on_delay_block.h"
#include "math/signalprocess/off_delay_block/off_delay_block.h"
#include "math/signalprocess/relay_block/relay_block.h"
#include "math/signalprocess/relay_block/relay_off_delay_block.h"
#include "math/signalprocess/relay_block/relay_on_delay_block.h"
#include "math/signalprocess/relay_block/relay_on_off_delay_block.h"
#include "math/signalprocess/signal_hold_block/signal_hold_block.h"

#include <array>
#include <cstddef>
#include <cstdint>

namespace active_safety {
namespace elk {

class ElkStateMachine {
  public:
    enum class State : uint8_t {
        Fault = 0,
        Off,
        Standby,
        Enable,
        Left_Intervention,
        Right_Intervention,
        Completed,
        Abort,
        Left_Suppressed,
        Right_Suppressed
    };

    struct Condition {
        bool fault_to_off                = false;
        bool off_to_fault                = false;
        bool off_to_standby              = false;
        bool standby_to_off              = false;
        bool standby_to_enable           = false;
        bool enable_to_standby           = false;
        bool enable_to_off               = false;
        bool enable_to_left_intervention = false;
        bool enable_to_right_intervention = false;
        bool left_to_right_intervention  = false;
        bool right_to_left_intervention = false;
        bool left_to_abort              = false;
        bool right_to_abort             = false;
        bool left_to_completed          = false;
        bool right_to_completed         = false;
        bool abort_to_enable            = false;
        bool completed_to_enable        = false;
        bool enable_to_left_suppressed  = false;
        bool enable_to_right_suppressed = false;
        bool left_suppressed_to_enable  = false;
        bool right_suppressed_to_enable = false;
    };

    ElkStateMachine()
        : state_(State::Off),
          abort_state_frame_count_(0),
          completed_state_frame_count_(0),
          evp_disable_mask_(0),
          diag_inhabit_mask_(0),
          stanby_enable_mask_(0),
          debug_left_active_source_mask_(0),
          debug_right_active_source_mask_(0) {}
    ~ElkStateMachine() = default;

    void Update(const AsVseOut &vse_out, 
                const LanesInfo &road_info, 
                const LaneBoundaryParameters &lane_boundary, 
                const LaneCenterParameters &lane_center, 
                const ElkTaSl &ta_info, 
                const GlobalConfig &config);
    void Update(const AsVseOut &vse_out,
                const LanesInfo &road_info,
                const LaneBoundaryParameters &lane_boundary,
                const LaneCenterParameters &lane_center,
                const ElkTaSl &ta_info,
                const GlobalConfig &config,
                float elk_torsion_bar_trq);

    State getCurrentState() const { return state_; }
    uint32_t getEvpDisableMask() const { return evp_disable_mask_; }
    uint32_t getDiagInhabitMask() const { return diag_inhabit_mask_; }
    uint16_t getStandbyEnableMask() const { return stanby_enable_mask_; }
    uint8_t getLeftActiveSourceMask() const { return elk_scenario_decider_.getLeftActiveSourceMask(); }
    uint8_t getRightActiveSourceMask() const { return elk_scenario_decider_.getRightActiveSourceMask(); }
    uint8_t getLeftDebugActiveSourceMask() const { return debug_left_active_source_mask_; }
    uint8_t getRightDebugActiveSourceMask() const { return debug_right_active_source_mask_; }
    uint8_t getLeftInterventionMask() const { return elk_scenario_decider_.getLeftInterventionMask(); }
    uint8_t getRightInterventionMask() const { return elk_scenario_decider_.getRightInterventionMask(); }
    uint8_t getLeftEdgeInterventionMask() const { return elk_scenario_decider_.getLeftEdgeInterventionMask(); }
    uint8_t getRightEdgeInterventionMask() const { return elk_scenario_decider_.getRightEdgeInterventionMask(); }
    uint8_t getLeftSolidInterventionMask() const { return elk_scenario_decider_.getLeftSolidInterventionMask(); }
    uint8_t getRightSolidInterventionMask() const { return elk_scenario_decider_.getRightSolidInterventionMask(); }
    uint32_t getLeftSuppressionMask() const { return elk_scenario_decider_.getLeftSuppressionMask(); }
    uint32_t getRightSuppressionMask() const { return elk_scenario_decider_.getRightSuppressionMask(); }
    uint64_t getTtcFalseTriggerDebugMask() const { return elk_scenario_decider_.getTtcFalseTriggerDebugMask(); }
    const ElkScenarioDecision::TtcDebugSnapshot &getTtcDebugSnapshot() const { return elk_scenario_decider_.getTtcDebugSnapshot(); }
    uint64_t getFalseTriggerDebugMask() const
    {
        return driver_false_trigger_debug_mask_ | elk_scenario_decider_.getTtcFalseTriggerDebugMask();
    }

    float getLeftCurvOffsetMarker() const { return elk_scenario_decider_.getLeftCurvOffsetMarker(); }
    float getRightCurvOffsetMarker() const { return elk_scenario_decider_.getRightCurvOffsetMarker(); }
    float getLeftCurvOffsetEdge() const { return elk_scenario_decider_.getLeftCurvOffsetEdge(); }
    float getRightCurvOffsetEdge() const { return elk_scenario_decider_.getRightCurvOffsetEdge(); }

  private:
  
    ElkCal elk_cals_;

    void checkVehicleInhabit(const AsVseOut &vse_out, float elk_torsion_bar_trq);
    void checkDriverSuppression(const AsVseOut &vse_out, const LaneBoundaryParameters &lane_boundary, float elk_torsion_bar_trq);
    void checkEnvironmentSuppression(const LaneBoundaryParameters &lane_boundary);
    // 更新指定手力矩抑制历史环形缓存；普通 bit6 和 LCT 专用 bit30 复用该计数逻辑。
    void updateSteerTorqueSuppressHistory(bool suppress_condition,
                                          std::array<bool, 10> &suppress_history,
                                          std::size_t &suppress_history_index);
    // 最近 k_ELK_DriHandsOvr_HistoryWindow 帧中命中数达到标定数量时，认为驾驶员手力矩接管成立。
    bool isSteerTorqueHistorySuppressed(const std::array<bool, 10> &suppress_history,
                                        std::size_t suppress_history_index) const;
    bool updateDriverIntentScoreHistory(float driver_intent_score);
    
    bool checkStandby2Enable(float speed_kph, const LaneBoundaryParameters &lane_boundary);
    bool checkEnable2Standby(float speed_kph);
    Condition BuildCondition(const AsVseOut &vse_out, 
                             const LanesInfo &road_info, 
                             const LaneBoundaryParameters &lane_boundary, 
                             const LaneCenterParameters &lane_center, 
                             const ElkTaSl &ta_info, 
                             const GlobalConfig &config,
                             float elk_torsion_bar_trq);
    void UpdateStateMachine(const Condition &condition);

    math::OnDelayBlock left_marker_valid_checker_;
    math::OnDelayBlock right_marker_valid_checker_;
    math::OnDelayBlock left_edge_valid_checker_;
    math::OnDelayBlock right_edge_valid_checker_;
    math::OnDelayBlock left_interveention_checker_;
    math::OnDelayBlock right_interveention_checker_;
    math::OnDelayBlock low_speed_accel_pedal_inhabit_checker_;
    math::OffDelayBlock brake_pedal_inhabit_checker_;
    math::OffDelayBlock accel_pedal_inhabit_checker_;
    math::OffDelayBlock driver_intent_inhabit_checker_;
    math::OffDelayBlock hazard_lamp_checker_;
    math::OffDelayBlock left_turn_lamp_inhabit_checker_;
    math::OffDelayBlock right_turn_lamp_inhabit_checker_;
    math::OffDelayBlock finish_checker_;
    math::RelayBlock lane_curv_valid_checker_;
    math::RelayBlock min_lane_width_checker_;
    math::RelayBlock max_lane_width_checker_;
    math::RelayOnDelayBlock brake_pressure_disable_checker_;
    math::RelayOffDelayBlock lat_accel_inhabit_checker_;
    math::RelayOffDelayBlock lon_accel_inhabit_checker_;
    math::RelayOffDelayBlock lon_decel_inhabit_checker_;
    math::RelayOffDelayBlock steer_angle_inhabit_checker_;   
    math::RelayOnOffDelayBlock steer_torque_inhabit_checker_;
    math::RelayOnOffDelayBlock lct_steer_torque_inhabit_checker_;
    math::RelayOnOffDelayBlock steer_angle_speed_inhabit_checker_;
    math::RelayOnOffDelayBlock yawrate_inhabit_checker_;
    math::RelayOnOffDelayBlock hand_off_detector_;

    State state_;
    uint8_t abort_state_frame_count_;
    uint8_t completed_state_frame_count_;

    uint32_t evp_disable_mask_;
    uint32_t diag_inhabit_mask_;
    uint16_t stanby_enable_mask_;
    uint32_t driver_false_trigger_debug_mask_ = 0U;
    uint8_t debug_left_active_source_mask_ = 0U;
    uint8_t debug_right_active_source_mask_ = 0U;
    std::array<bool, 10> steer_torque_suppress_history_{};
    std::size_t steer_torque_suppress_history_index_ = 0U;
    std::array<bool, 10> lct_steer_torque_suppress_history_{};
    std::size_t lct_steer_torque_suppress_history_index_ = 0U;
    std::array<float, 3> driver_intent_score_history_{};
    std::array<bool, 3> driver_intent_score_valid_history_{};
    std::size_t driver_intent_score_history_index_ = 0U;
    uint8_t driver_intent_score_valid_count_ = 0U;

    ElkScenarioDecision elk_scenario_decider_;
};

} // namespace elk
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_ELK_ELK_STATE_MACHINE_H_
