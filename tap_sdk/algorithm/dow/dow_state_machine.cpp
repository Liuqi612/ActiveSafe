#include "dow_function.h"

namespace active_safety {
namespace dow {

void DowFunction::StateMachine(const GlobalConfig &config, const AsVseOut &vse_out) {
    m_dow_mode_cond.state_off   = (vse_out.dow_switch != static_cast<uint8_t>(DowSwitch::ON));
    m_dow_mode_cond.state_fault = math::GetDiagBitValue(vse_out.function_did_config, static_cast<uint32_t>(FunctionDid::DOW));

    bool host_speed_enable = (vse_out.display_speed / 3.6F > -0.1f && vse_out.display_speed / 3.6F <= m_dow_cal.k_dow_active_vehspd_max);
    if (m_dow_out.state == DowState::ACTIVE) {
        host_speed_enable = (vse_out.display_speed / 3.6F > -0.1f && vse_out.display_speed / 3.6F < m_dow_cal.k_dow_deactive_vehspd_max);
    }

    bool is_active = m_dow_out.warn_left > 0 || m_dow_out.warn_right > 0;
    bool active_hold = m_dow_hold.signalHold(is_active, m_dow_cal.k_dow_min_warn_time, m_dow_cal.k_dow_step_time);
    bool final_active = active_hold;
    m_dow_release.signalRelease(final_active, m_dow_cal.k_dow_max_warn_time, m_dow_cal.k_dow_step_time);

    m_dow_mode_cond.state_inhibit   = (!host_speed_enable);
    m_dow_mode_cond.state_active    = final_active && !m_dow_release.getSignalRelease();

    m_dow_mode_cond.off2inhibit     = (m_dow_mode_cond.state_off == false && m_dow_mode_cond.state_fault == false);
    m_dow_mode_cond.fault2inhibit   = (m_dow_mode_cond.state_off == false && m_dow_mode_cond.state_fault == false);
    m_dow_mode_cond.inhibit2standby = (m_dow_mode_cond.state_inhibit == false);
    m_dow_mode_cond.inhibit2active  = (m_dow_mode_cond.state_inhibit == false && m_dow_mode_cond.state_active == true);
    m_dow_mode_cond.standby2active  = (m_dow_mode_cond.state_inhibit == false && m_dow_mode_cond.state_active == true);
    m_dow_mode_cond.active2standby  = (m_dow_mode_cond.state_inhibit == false && m_dow_mode_cond.state_active == false);
    m_dow_mode_context.setCondition(m_dow_mode_cond);
    m_dow_mode.update(m_dow_mode_context);

    // 回灌调试：记录状态机条件与中间量(读取已算好的值，不重复计算)
    if (m_dow_cal.k_dow_debug_log_enable) {
        m_debug.sm.state_off         = m_dow_mode_cond.state_off;
        m_debug.sm.state_fault       = m_dow_mode_cond.state_fault;
        m_debug.sm.state_inhibit     = m_dow_mode_cond.state_inhibit;
        m_debug.sm.state_active      = m_dow_mode_cond.state_active;
        m_debug.sm.host_speed_enable = host_speed_enable;
        m_debug.sm.is_active_raw     = is_active;
        m_debug.sm.active_hold       = active_hold;
        m_debug.sm.signal_release    = m_dow_release.getSignalRelease();
        m_debug.sm.final_active      = final_active;
        m_debug.sm.off2inhibit       = m_dow_mode_cond.off2inhibit;
        m_debug.sm.inhibit2standby   = m_dow_mode_cond.inhibit2standby;
        m_debug.sm.inhibit2active    = m_dow_mode_cond.inhibit2active;
        m_debug.sm.standby2active    = m_dow_mode_cond.standby2active;
        m_debug.sm.active2standby    = m_dow_mode_cond.active2standby;
        m_debug.sm.sub_state         = static_cast<int>(m_dow_mode.getCurrentSubState());
        m_debug.sm.fl_door           = vse_out.fl_door_st;
        m_debug.sm.fr_door           = vse_out.fr_door_st;
        m_debug.sm.rl_door           = vse_out.rl_door_st;
        m_debug.sm.rr_door           = vse_out.rr_door_st;
        m_debug.sm.use_shadowmode    = config.k_use_shadowmode;
        m_debug.sm.dow_enable        = config.k_dow_enable;
        m_debug.sm.ego_speed         = vse_out.display_speed / 3.6F;
        m_debug.sm.dow_switch        = vse_out.dow_switch;
    }

    bool f_display_target = false;
    if (m_dow_mode.getCurrentSubState() == math::ModeState::ACTIVE) {
        if (m_dow_out.warn_left > 0 && (vse_out.fl_door_st == static_cast<uint8_t>(DoorStatus::OPEN) ||
                                        vse_out.rl_door_st == static_cast<uint8_t>(DoorStatus::OPEN))) {
            m_dow_out.warn_left = static_cast<uint32_t>(WarnLevel::LEVEL_2);
        } else if(m_dow_out.warn_left > 0){
            m_dow_out.warn_left = static_cast<uint32_t>(WarnLevel::LEVEL_1);
        }
        if (m_dow_out.warn_right > 0 && (vse_out.fr_door_st == static_cast<uint8_t>(DoorStatus::OPEN) ||
                                         vse_out.rr_door_st == static_cast<uint8_t>(DoorStatus::OPEN))) {
            m_dow_out.warn_right = static_cast<uint32_t>(WarnLevel::LEVEL_2);
        } else if(m_dow_out.warn_right > 0){
            m_dow_out.warn_right = static_cast<uint32_t>(WarnLevel::LEVEL_1);
        }
        f_display_target = true;
    } else {
        m_dow_out.warn_left  = static_cast<uint32_t>(WarnLevel::NO_REQUEST);
        m_dow_out.warn_right = static_cast<uint32_t>(WarnLevel::NO_REQUEST);
    }

    switch (m_dow_mode.getCurrentSubState()) {
        case math::ModeState::OFF: {
            m_dow_out.state = DowState::OFF;
            break;
        }
        case math::ModeState::FAULT: {
            m_dow_out.state = DowState::FAULT;
            break;
        }
        case math::ModeState::ON:
        case math::ModeState::INHIBIT: {
            m_dow_out.state = DowState::INHIBIT;
            break;
        }
        case math::ModeState::STANDBY: {
            {
                m_dow_out.state = DowState::STANDBY;
                break;
            }
        }
        case math::ModeState::ACTIVE: {
            m_dow_out.state = DowState::ACTIVE;
            break;
        }
        default: {
            m_dow_out.state = DowState::INHIBIT;
            break;
        }
    }

    switch (vse_out.dow_switch) {
        case static_cast<uint8_t>(DowSwitch::ON):
            m_dow_out.switch_req = static_cast<uint32_t>(SwitchReqOut::LIGHT);
            break;
        default:
            if(m_dow_out.state == DowState::OFF)
                m_dow_out.switch_req = static_cast<uint32_t>(SwitchReqOut::OFF);
            else{
                m_dow_out.switch_req = static_cast<uint32_t>(SwitchReqOut::LIGHT);
            }
            break;
    }

    if (config.k_use_shadowmode || !config.k_dow_enable) {
        m_dow_out.warn_left  = static_cast<uint32_t>(WarnLevel::NO_REQUEST);
        m_dow_out.warn_right = static_cast<uint32_t>(WarnLevel::NO_REQUEST);
    }
}

} // namespace dow
} // namespace active_safety
