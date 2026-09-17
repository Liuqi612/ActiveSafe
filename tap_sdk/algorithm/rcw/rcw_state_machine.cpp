#include "rcw_function.h"

#include <cmath>
#include <string.h>

namespace active_safety {
namespace rcw {

void RcwFunction::StateMachine(const GlobalConfig &config, const AsVseOut &vse_out) {

    // 报警时间限制和冷却时间逻辑
    bool is_active_raw = (m_rcw_active[0] || m_rcw_active[1]);
    bool delay_active = m_rcw_ondelay.onDelay(is_active_raw, m_rcw_cal.k_rcw_ondelay_time, m_rcw_cal.k_rcw_step_time);
    bool hold_active = m_rcw_hold.signalHold(delay_active, m_rcw_cal.k_rcw_alert_time_min, m_rcw_cal.k_rcw_step_time);
    bool final_active = hold_active;
    m_rcw_release.signalRelease(final_active, m_rcw_cal.k_rcw_alert_time_max, m_rcw_cal.k_rcw_step_time);
    m_rcw_freezing.featureFreezing(final_active, m_rcw_cal.k_rcw_freezing_time, m_rcw_cal.k_rcw_step_time);

    // 如果超过最长报警时间或在冷却期或未超过激活延时，抑制报警
    bool is_suppressed = m_rcw_release.getSignalRelease() || m_rcw_freezing.getfeatureFreezing() || 
    (m_rcw_tar.ttc < m_rcw_cal.k_rcw_ttc_inhibit_thd && m_rcw_out.state != RcwState::ACTIVE);

    m_rcw_mode_cond.state_off = (vse_out.rcw_switch == static_cast<uint8_t>(RcwSwitch::OFF));
    m_rcw_mode_cond.state_fault = math::GetDiagBitValue(vse_out.function_did_config, static_cast<uint32_t>(FunctionDid::RCW));
    m_rcw_mode_cond.state_inhibit = (vse_out.display_speed / 3.6F > m_rcw_cal.k_rcw_enable_speed_max || vse_out.actual_gear != static_cast<uint8_t>(GearPosition::DRIVE));
    m_rcw_mode_cond.state_active = final_active && !is_suppressed;

    m_rcw_mode_cond.off2inhibit = !m_rcw_mode_cond.state_off && !m_rcw_mode_cond.state_fault && vse_out.display_speed / 3.6F < m_rcw_cal.k_rcw_inhibit_speed_max;
    m_rcw_mode_cond.fault2inhibit = !m_rcw_mode_cond.state_off && !m_rcw_mode_cond.state_fault;
    m_rcw_mode_cond.inhibit2standby = !m_rcw_mode_cond.state_inhibit;
    m_rcw_mode_cond.inhibit2active = !m_rcw_mode_cond.state_inhibit && m_rcw_mode_cond.state_active;
    m_rcw_mode_cond.standby2active = !m_rcw_mode_cond.state_inhibit && m_rcw_mode_cond.state_active;
    m_rcw_mode_cond.active2standby = !m_rcw_mode_cond.state_inhibit && !m_rcw_mode_cond.state_active;

    m_rcw_mode_context.setCondition(m_rcw_mode_cond);
    m_rcw_mode.update(m_rcw_mode_context);

    // 记录状态机条件集合(与实际决策一致)
    if (m_rcw_cal.k_rcw_debug_log_enable) {
        RcwStateDebug &sd = m_debug.state;
        sd.is_active_raw = is_active_raw;
        sd.delay_active = delay_active;
        sd.hold_active = hold_active;
        sd.final_active = final_active;
        sd.is_suppressed = is_suppressed;
        sd.signal_release = m_rcw_release.getSignalRelease();
        sd.freezing = m_rcw_freezing.getfeatureFreezing();
        sd.ttc_inhibit = (m_rcw_tar.ttc < m_rcw_cal.k_rcw_ttc_inhibit_thd && m_rcw_out.state != RcwState::ACTIVE);
        sd.state_off = m_rcw_mode_cond.state_off;
        sd.state_fault = m_rcw_mode_cond.state_fault;
        sd.state_inhibit = m_rcw_mode_cond.state_inhibit;
        sd.state_active = m_rcw_mode_cond.state_active;
        sd.short_ttc_flag = m_short_ttc_flag;
        sd.short_ttc_offdly = m_short_ttc_offdly.getStateOut();
    }

    m_min_dist_idx >= 0 ? FillTargetInfo(m_rcw_tar, m_rcw_out.tgt_rcw) : ResetTargetInfo(m_rcw_out.tgt_rcw);
    switch (m_rcw_mode.getCurrentSubState()) {
        case math::ModeState::OFF:
            m_rcw_out.rcw_collision_warn = OnOffStatus::NotActive;
            m_rcw_out.state = RcwState::OFF;
            break;
        case math::ModeState::FAULT:
            m_rcw_out.rcw_collision_warn = OnOffStatus::NotActive;
            m_rcw_out.state = RcwState::FAULT;
            break;
        case math::ModeState::INHIBIT:
            m_rcw_out.rcw_collision_warn = OnOffStatus::NotActive;
            m_rcw_out.state = RcwState::INHIBIT;
            break;
        case math::ModeState::STANDBY:
            m_rcw_out.rcw_collision_warn = OnOffStatus::NotActive;
            m_rcw_out.state = RcwState::STANDBY;
            break;
        case math::ModeState::ACTIVE:
            m_rcw_out.rcw_collision_warn = OnOffStatus::Active;
            m_rcw_out.state = RcwState::ACTIVE;
            break;
        default:
            m_rcw_out.rcw_collision_warn = OnOffStatus::NotActive;
            m_rcw_out.state = RcwState::INHIBIT;
            break;
    }
    switch (vse_out.rcw_switch) {
        case static_cast<uint8_t>(RcwSwitch::ON):
            m_rcw_out.switch_req = static_cast<uint32_t>(RcwSwitchReqOut::ON);
            break;
        case static_cast<uint8_t>(RcwSwitch::OFF):
            m_rcw_out.switch_req = static_cast<uint32_t>(RcwSwitchReqOut::OFF);
            break;
        case static_cast<uint8_t>(RcwSwitch::RESERVE_3):
            if(m_rcw_out.state == RcwState::OFF)
                m_rcw_out.switch_req = static_cast<uint32_t>(RcwSwitchReqOut::OFF);
            else{
                m_rcw_out.switch_req = static_cast<uint32_t>(RcwSwitchReqOut::ON);
            }
            break;
        default:
            if(m_rcw_out.state == RcwState::OFF)
                m_rcw_out.switch_req = static_cast<uint32_t>(RcwSwitchReqOut::OFF);
            else{
                m_rcw_out.switch_req = static_cast<uint32_t>(RcwSwitchReqOut::ON);
            }
            break;
    }
    if (config.k_use_shadowmode || !config.k_rcw_enable) {
        m_rcw_out.rcw_collision_warn = OnOffStatus::NotActive;
    }
}

void RcwFunction::FillTargetInfo(const RcwObsData &obs_data, AsTargetInfo_T &tgt_info) {
    tgt_info.id = obs_data.obs->fus_trkID;
    tgt_info.type = static_cast<uint32_t>(obs_data.obs->object_class);
    tgt_info.source = static_cast<uint32_t>(obs_data.obs->fusion_source);
    tgt_info.posx = obs_data.obs->long_posn;
    tgt_info.posy = obs_data.obs->lat_posn;
    tgt_info.spdx = obs_data.obs->long_vel;
    tgt_info.spdy = obs_data.obs->lat_vel;
    tgt_info.accelx = obs_data.obs->long_accel;
    tgt_info.accely = obs_data.obs->lat_accel;
    tgt_info.heading = obs_data.obs->heading;
    tgt_info.ttc = obs_data.ttc;
}

} // namespace rcw
} // namespace active_safety
