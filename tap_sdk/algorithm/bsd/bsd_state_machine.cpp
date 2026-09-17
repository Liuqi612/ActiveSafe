#include "bsd_function.h"
namespace active_safety {
namespace bsd {

void BsdFunction::StateMachine(const GlobalConfig &config, const AsVseOut &vse_out) {
    bool bsw_left_warn = m_bsw_alert_active[0];
    bool bsw_right_warn = m_bsw_alert_active[1];

    bool lcw_left_warn_1 = m_cvw_alert_active[0];
    bool lcw_right_warn_1 = m_cvw_alert_active[1];
    bool lcw_left_warn_2 = (lcw_left_warn_1 && vse_out.turn_light_switch_pos == static_cast<uint8_t>(TurnLightSwitchPos::LEFT) &&
                            vse_out.hazard_lamp_st != static_cast<uint8_t>(HazardLampStatus::PRESSED));
    bool lcw_right_warn_2 = (lcw_right_warn_1 && vse_out.turn_light_switch_pos == static_cast<uint8_t>(TurnLightSwitchPos::RIGHT) &&
                             vse_out.hazard_lamp_st != static_cast<uint8_t>(HazardLampStatus::PRESSED));
    bool lcw_warn_level_1 = (lcw_left_warn_1 || lcw_right_warn_1);
    bool lcw_warn_level_2 = (lcw_left_warn_2 || lcw_right_warn_2);

    bool bsw_warn_raw = (bsw_left_warn || bsw_right_warn);
    bool hold_active = m_bsw_hold.signalHold(bsw_warn_raw, m_bsd_cal.k_bsw_min_warn_time, m_bsd_cal.k_bsd_step_time);
    bool final_bsw_active = hold_active;

    m_bsd_mode_cond.state_off = !(vse_out.bsd_switch == static_cast<uint8_t>(BsdSwitch::LIGHT_AND_SOUND) ||
                                  vse_out.bsd_switch == static_cast<uint8_t>(BsdSwitch::LIGHT));
    m_bsd_mode_cond.state_fault = math::GetDiagBitValue(vse_out.function_did_config, static_cast<uint32_t>(FunctionDid::BSD));

    if (m_host_speed_enable) {
        m_host_speed_enable =
            !(vse_out.display_speed / 3.6F < m_bsd_cal.k_bsd_min_enable_host_speed_hys || vse_out.display_speed / 3.6F > m_bsd_cal.k_bsd_max_enable_host_speed_hys);
    } else {
        m_host_speed_enable = (m_bsd_cal.k_bsd_min_enable_host_speed < vse_out.display_speed / 3.6F && vse_out.display_speed / 3.6F < m_bsd_cal.k_bsd_max_enable_host_speed);
    }

    m_bsd_mode_cond.state_inhibit = (!m_host_speed_enable || vse_out.actual_gear != static_cast<uint8_t>(GearPosition::DRIVE));
    m_bsd_mode_cond.state_active = (final_bsw_active || lcw_warn_level_1 || lcw_warn_level_2);
    m_bsd_mode_cond.off2inhibit = (m_bsd_mode_cond.state_off == false && m_bsd_mode_cond.state_fault == false);
    m_bsd_mode_cond.fault2inhibit = (m_bsd_mode_cond.state_off == false && m_bsd_mode_cond.state_fault == false);
    m_bsd_mode_cond.inhibit2standby = (m_bsd_mode_cond.state_inhibit == false);
    m_bsd_mode_cond.inhibit2active = (m_bsd_mode_cond.state_inhibit == false && m_bsd_mode_cond.state_active == true);
    m_bsd_mode_cond.standby2active = (m_bsd_mode_cond.state_inhibit == false && m_bsd_mode_cond.state_active == true);
    m_bsd_mode_cond.active2standby = (m_bsd_mode_cond.state_inhibit == false && m_bsd_mode_cond.state_active == false);
    m_bsd_mode_context.setCondition(m_bsd_mode_cond);
    m_bsd_mode.update(m_bsd_mode_context);

    // 回灌调试：记录状态机门控条件与侧级报警（读取已算好的量，不重复计算）
    if (m_bsd_cal.k_bsd_debug_log_enable) {
        m_debug.sm.state_off = m_bsd_mode_cond.state_off;
        m_debug.sm.state_fault = m_bsd_mode_cond.state_fault;
        m_debug.sm.state_inhibit = m_bsd_mode_cond.state_inhibit;
        m_debug.sm.state_active = m_bsd_mode_cond.state_active;
        m_debug.sm.host_speed_enable = m_host_speed_enable;
        m_debug.sm.bsw_warn_raw = bsw_warn_raw;
        m_debug.sm.hold_active = hold_active;
        m_debug.sm.final_bsw_active = final_bsw_active;
        m_debug.sm.lcw_warn_level_1 = lcw_warn_level_1;
        m_debug.sm.lcw_warn_level_2 = lcw_warn_level_2;
        m_debug.sm.bsw_left_warn = bsw_left_warn;
        m_debug.sm.bsw_right_warn = bsw_right_warn;
        m_debug.sm.lcw_left_warn_1 = lcw_left_warn_1;
        m_debug.sm.lcw_right_warn_1 = lcw_right_warn_1;
        m_debug.sm.lcw_left_warn_2 = lcw_left_warn_2;
        m_debug.sm.lcw_right_warn_2 = lcw_right_warn_2;
        m_debug.sm.speed = vse_out.display_speed / 3.6F;
        m_debug.sm.gear = vse_out.actual_gear;
        m_debug.sm.sw = vse_out.bsd_switch;
        m_debug.sm.cur_substate = static_cast<int>(m_bsd_mode.getCurrentSubState());
        for (int side = 0; side < 2; ++side) {
            m_debug.bsw_alert_active[side] = m_bsw_alert_active[side];
            m_debug.bsw_alert_fusId[side] = m_bsw_alert_fusId[side];
            m_debug.cvw_alert_active[side] = m_cvw_alert_active[side];
            m_debug.cvw_alert_fusId[side] = m_cvw_alert_fusId[side];
            m_debug.closest_cvw_obs_dist[side] = m_closest_cvw_obs_dist[side];
        }
    }

    if (m_bsd_mode.getCurrentSubState() == math::ModeState::ACTIVE) {
        m_bsw_active = final_bsw_active ? true : false;
        m_lcw_active = (lcw_warn_level_1 || lcw_warn_level_2);
    } else {
        m_bsw_active = false;
        m_lcw_active = false;
    }

    memset(&m_bsd_out, 0, sizeof(m_bsd_out));

    switch (m_bsd_mode.getCurrentSubState()) {
        case math::ModeState::OFF:
            m_bsd_out.state = BsdState::OFF;
            break;
        case math::ModeState::FAULT:
            m_bsd_out.state = BsdState::FAULT;
            break;
        case math::ModeState::ON:
        case math::ModeState::INHIBIT:
            m_bsd_out.state = BsdState::INHIBIT;
            break;
        case math::ModeState::STANDBY:
            m_bsd_out.state = BsdState::STANDBY;
            break;
        case math::ModeState::ACTIVE:
            m_bsd_out.state = BsdState::ACTIVE;
            break;
        default:
            m_bsd_out.state = BsdState::INHIBIT;
            break;
    }

    m_bsd_out.bsd_warn_left = (m_bsw_active && bsw_left_warn);
    if (m_bsd_out.bsd_warn_left == static_cast<uint32_t>(WarnLevel::LEVEL_1) &&
        vse_out.turn_light_switch_pos == static_cast<uint8_t>(TurnLightSwitchPos::LEFT) &&
        vse_out.hazard_lamp_st != static_cast<uint8_t>(HazardLampStatus::PRESSED)) {
        m_bsd_out.bsd_warn_left = static_cast<uint32_t>(WarnLevel::LEVEL_2);
    }
    m_bsd_out.bsd_warn_right = (m_bsw_active && bsw_right_warn);
    if (m_bsd_out.bsd_warn_right == static_cast<uint32_t>(WarnLevel::LEVEL_1) &&
        vse_out.turn_light_switch_pos == static_cast<uint8_t>(TurnLightSwitchPos::RIGHT) &&
        vse_out.hazard_lamp_st != static_cast<uint8_t>(HazardLampStatus::PRESSED)) {
        m_bsd_out.bsd_warn_right = static_cast<uint32_t>(WarnLevel::LEVEL_2);
    }
    if (m_lcw_active) {
        if (lcw_left_warn_1) {
            m_bsd_out.lca_warn_left = static_cast<uint32_t>(WarnLevel::LEVEL_1);
        }
        if (lcw_left_warn_2) {
            m_bsd_out.lca_warn_left = static_cast<uint32_t>(WarnLevel::LEVEL_2);
        }
        if (lcw_right_warn_1) {
            m_bsd_out.lca_warn_right = static_cast<uint32_t>(WarnLevel::LEVEL_1);
        }
        if (lcw_right_warn_2) {
            m_bsd_out.lca_warn_right = static_cast<uint32_t>(WarnLevel::LEVEL_2);
        }
    } else {
        m_bsd_out.lca_warn_left = static_cast<uint32_t>(WarnLevel::NO_REQUEST);
        m_bsd_out.lca_warn_right = static_cast<uint32_t>(WarnLevel::NO_REQUEST);
    }

    switch (vse_out.bsd_switch) {
        case static_cast<uint8_t>(BsdSwitch::LIGHT_AND_SOUND):
            m_bsd_out.switch_req = static_cast<uint32_t>(SwitchReqOut::LIGHT_AND_SOUND);
            break;
        case static_cast<uint8_t>(BsdSwitch::LIGHT):
            m_bsd_out.switch_req = static_cast<uint32_t>(SwitchReqOut::LIGHT);
            break;
        case static_cast<uint8_t>(BsdSwitch::OFF):
            m_bsd_out.switch_req = static_cast<uint32_t>(SwitchReqOut::OFF);
            break;
        default:
            if(m_bsd_out.state == BsdState::OFF){
                m_bsd_out.switch_req = static_cast<uint32_t>(SwitchReqOut::OFF);
            }else{
                m_bsd_out.switch_req = static_cast<uint32_t>(SwitchReqOut::LIGHT);
            }
            break;
    }

    if (m_bsd_out.bsd_warn_left == static_cast<uint32_t>(WarnLevel::LEVEL_1) ||
        m_bsd_out.lca_warn_left == static_cast<uint32_t>(WarnLevel::LEVEL_1)) {
        m_bsd_out.bsd_warn_left = static_cast<uint32_t>(WarnLevel::LEVEL_1);
        m_bsd_out.lca_warn_left = static_cast<uint32_t>(WarnLevel::LEVEL_1);
    }
    if (m_bsd_out.bsd_warn_left == static_cast<uint32_t>(WarnLevel::LEVEL_2) ||
        m_bsd_out.lca_warn_left == static_cast<uint32_t>(WarnLevel::LEVEL_2)) {
        m_bsd_out.bsd_warn_left = static_cast<uint32_t>(WarnLevel::LEVEL_2);
        m_bsd_out.lca_warn_left = static_cast<uint32_t>(WarnLevel::LEVEL_2);
        m_bsd_out.bsc_sound = OnOffStatus::Active;
    }
    if (m_bsd_out.bsd_warn_right == static_cast<uint32_t>(WarnLevel::LEVEL_1) ||
        m_bsd_out.lca_warn_right == static_cast<uint32_t>(WarnLevel::LEVEL_1)) {
        m_bsd_out.bsd_warn_right = static_cast<uint32_t>(WarnLevel::LEVEL_1);
        m_bsd_out.lca_warn_right = static_cast<uint32_t>(WarnLevel::LEVEL_1);
    }
    if (m_bsd_out.bsd_warn_right == static_cast<uint32_t>(WarnLevel::LEVEL_2) ||
        m_bsd_out.lca_warn_right == static_cast<uint32_t>(WarnLevel::LEVEL_2)) {
        m_bsd_out.bsd_warn_right = static_cast<uint32_t>(WarnLevel::LEVEL_2);
        m_bsd_out.lca_warn_right = static_cast<uint32_t>(WarnLevel::LEVEL_2);
        m_bsd_out.bsc_sound = OnOffStatus::Active;
    }

    for (const BsdObsData &obs_data : m_obs_data) {
        if (obs_data.m_obs->fus_trkID <= 0) {
            continue;
        }
        if (m_bsw_alert_fusId[0] > 0 && m_bsw_alert_fusId[0] == obs_data.m_obs->fus_trkID) {
            FillTargetInfo(obs_data, m_bsd_out.left_tgt_bsd);
        }
        if (m_bsw_alert_fusId[1] > 0 && m_bsw_alert_fusId[1] == obs_data.m_obs->fus_trkID) {
            FillTargetInfo(obs_data, m_bsd_out.right_tgt_bsd);
        }
        if (m_cvw_alert_fusId[0] > 0 && m_cvw_alert_fusId[0] == obs_data.m_obs->fus_trkID) {
            FillTargetInfo(obs_data, m_bsd_out.left_tgt_lca);
        }
        if (m_cvw_alert_fusId[1] > 0 && m_cvw_alert_fusId[1] == obs_data.m_obs->fus_trkID) {
            FillTargetInfo(obs_data, m_bsd_out.right_tgt_lca);
        }
    }
    if (config.k_use_shadowmode || !config.k_bsd_enable) {
        m_bsd_out.bsc_sound = OnOffStatus::NotActive;
        m_bsd_out.lca_warn_left = static_cast<uint32_t>(WarnLevel::NO_REQUEST);
        m_bsd_out.lca_warn_right = static_cast<uint32_t>(WarnLevel::NO_REQUEST);
        m_bsd_out.bsd_warn_left = static_cast<uint32_t>(WarnLevel::NO_REQUEST);
        m_bsd_out.bsd_warn_right = static_cast<uint32_t>(WarnLevel::NO_REQUEST);
    }
}

void BsdFunction::FillTargetInfo(const BsdObsData &obs_data, AsTargetInfo_T &tgt_info) {
    tgt_info.id = obs_data.m_obs->fus_trkID;
    tgt_info.type = static_cast<uint32_t>(obs_data.m_obs->object_class);
    tgt_info.source = static_cast<uint32_t>(obs_data.m_obs->fusion_source);
    tgt_info.posx = obs_data.m_obs->long_posn;
    tgt_info.posy = obs_data.m_obs->lat_posn;
    tgt_info.spdx = obs_data.m_obs->long_vel;
    tgt_info.spdy = obs_data.m_obs->lat_vel;
    tgt_info.accelx = obs_data.m_obs->long_accel;
    tgt_info.accely = obs_data.m_obs->lat_accel;
    tgt_info.heading = obs_data.m_obs->heading;
    tgt_info.ttc = obs_data.m_ttc;
}

} // namespace bsd
} // namespace active_safety