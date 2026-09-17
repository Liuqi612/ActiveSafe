#include "cts_function.h"

namespace active_safety {
namespace cts {

void CtsFunction::CheckCommonInhibit(const AsVseOut &vse_out) {
    bool f_steer_inhibit = (fabs(vse_out.steerwheelangle) > m_cts_cal.k_cts_strangle_inhibit_thrd) ||
        (fabs(vse_out.steerwheelangle_rate) > m_cts_cal.k_cts_strangrt_inhibit_thrd) ||
        (fabs(vse_out.rear_curvature) > m_cts_cal.k_cts_curvature_inhibit_thrd);

    bool f_pedal_inhibit = (vse_out.brake_pedal_pos > m_cts_cal.k_cts_brkpdl_inhibit_thrd) ||
        (vse_out.gas_pedal_pos > m_cts_cal.k_cts_accpdl_inhibit_thrd) || (vse_out.gas_pedal_pos_rate > m_cts_cal.k_cts_gas_pedal_rate_inhibit_thrd);

    m_common_inhibit_offdly.offDelay(f_steer_inhibit || f_pedal_inhibit, m_cts_cal.k_cts_common_inhibit_time, CTS_STEP_TIME);
}

void CtsFunction::CheckDrvBehavior(const AsVseOut &vse_out) {
    bool res = fabs(vse_out.steerwheelangle) > m_cts_cal.k_drv_continues_steer_ang_thres;
    m_drv_continues_steer_ondly.onDelay(res, m_cts_cal.k_drv_continues_steer_ondly_time, CTS_STEP_TIME);
    m_drv_continues_steer_offdly.offDelay(m_drv_continues_steer_ondly.getStateOut(), m_cts_cal.k_drv_continues_steer_offdly_time, CTS_STEP_TIME);
    // 判断驾驶员是否持续向一个方向转向，如果是则对于对侧方向的阈值可认为驾驶员非盲区，缩短其区域阈值——用于合流
    if (m_drv_continues_steer_offdly.getStateOut()) {
        if (vse_out.steerwheelangle > m_cts_cal.k_drv_continues_steer_ang_thres) {
            m_drv_continues_str_dir = DriverSteerDir::Left;
        } else if (vse_out.steerwheelangle < -m_cts_cal.k_drv_continues_steer_ang_thres) {
            m_drv_continues_str_dir = DriverSteerDir::Right;
        }
        m_drv_max_continues_str_ang = fmax(m_drv_max_continues_str_ang, fabs(vse_out.steerwheelangle));
    } else {
        m_drv_continues_str_dir = DriverSteerDir::None;
        m_drv_max_continues_str_ang = 0.0f;
    }
    // 判断驾驶员是否持续向一个方向增大转向，如果是则认为驾驶员有对其对侧方向的目标有避让趋势——用于路口
    float str_increase_anglerate = m_cts_cal.k_drv_increase_steerangrate_thres;
    if (m_drv_increase_str_left_ondly.getCurCount() > static_cast<uint32_t>(m_cts_cal.k_cts_steer_increase_cnt_thres)) {
        str_increase_anglerate *= m_cts_cal.k_cts_steer_rate_shrink_factor;
    }

    res = vse_out.steerwheelangle_rate > str_increase_anglerate;
    m_drv_increase_str_left_ondly.onDelay(res, m_cts_cal.k_drv_increase_steer_ondly_time, CTS_STEP_TIME);
    m_drv_increase_str_left_offdly.offDelay(m_drv_increase_str_left_ondly.getStateOut(), m_cts_cal.k_drv_increase_steer_offdly_time, CTS_STEP_TIME);

    str_increase_anglerate = m_cts_cal.k_drv_increase_steerangrate_thres;
    if (m_drv_increase_str_right_ondly.getCurCount() > static_cast<uint32_t>(m_cts_cal.k_cts_steer_increase_cnt_thres)) {
        str_increase_anglerate *= m_cts_cal.k_cts_steer_rate_shrink_factor;
    }

    res = vse_out.steerwheelangle_rate < -str_increase_anglerate;
    m_drv_increase_str_right_ondly.onDelay(res, m_cts_cal.k_drv_increase_steer_ondly_time, CTS_STEP_TIME);
    m_drv_increase_str_right_offdly.offDelay(m_drv_increase_str_right_ondly.getStateOut(), m_cts_cal.k_drv_increase_steer_offdly_time, CTS_STEP_TIME);

    if (m_drv_increase_str_right_offdly.getStateOut() && vse_out.steerwheelangle < -10.0f) {
        m_drv_increase_str_dir = DriverSteerDir::Right;
    } else if (m_drv_increase_str_left_offdly.getStateOut() && vse_out.steerwheelangle > 10.0f) {
        m_drv_increase_str_dir = DriverSteerDir::Left;
    } else {
        m_drv_increase_str_dir = DriverSteerDir::None;
    }

    // 判断车辆是否在持续减速
    res = vse_out.long_accel < m_cts_cal.k_veh_decel_thres && fabs(vse_out.speed) < m_cts_cal.k_cts_default_spd &&
        m_front.brake_req != OnOffStatus::Active && m_rear.brake_req != OnOffStatus::Active;
    m_veh_decel_ondly.onDelay(res, m_cts_cal.k_veh_decel_ondly_time, CTS_STEP_TIME);
    m_veh_decel_offdly.offDelay(m_veh_decel_ondly.getStateOut(), m_cts_cal.k_veh_decel_offdly_time, CTS_STEP_TIME);

    // 判断驾驶员在低速情况是否在刹车——判断其有识别风险趋势，用于交流区较多目标
    float drv_pdl_pos_thres = m_cts_cal.k_drv_want_brake_brkpdlpos_thres;
    if (m_drv_wantbrake_ondly.getCurCount() > static_cast<uint32_t>(m_cts_cal.k_cts_drv_brake_cnt_thres)) {
        drv_pdl_pos_thres = m_cts_cal.k_drv_want_brake_brkpdlpos_hys_thres;
    }
    res = vse_out.brake_pedal_pos > drv_pdl_pos_thres;
    m_drv_wantbrake_ondly.onDelay(res, m_cts_cal.k_drv_want_brake_brkpdlpos_ondly_time, CTS_STEP_TIME);
    m_drv_wantbrake_offdly.offDelay(m_drv_wantbrake_ondly.getStateOut(), m_cts_cal.k_drv_want_brake_brkpdlpos_offdly_time, CTS_STEP_TIME);
}

void CtsFunction::CtsDecision(const AsVseOut &vse_out, const GlobalConfig &config) {
    FCTAStateMachine(vse_out, config);
    FCTBStateMachine(vse_out, config);
    RCTAStateMachine(vse_out, config);
    RCTBStateMachine(vse_out, config);

    // 记录跨功能共享的驾驶员行为/抑制条件，供回灌调试打印
    if (m_cts_cal.k_cts_debug_log_enable) {
        m_debug.common_inhibit = m_common_inhibit_offdly.getStateOut();
        m_debug.drv_continues_steer = m_drv_continues_steer_offdly.getStateOut();
        m_debug.drv_continues_str_dir = static_cast<int>(m_drv_continues_str_dir);
        m_debug.drv_increase_steer =
            (m_drv_increase_str_left_offdly.getStateOut() || m_drv_increase_str_right_offdly.getStateOut());
        m_debug.drv_increase_str_dir = static_cast<int>(m_drv_increase_str_dir);
        m_debug.veh_decel = m_veh_decel_offdly.getStateOut();
        m_debug.drv_want_brake = m_drv_wantbrake_offdly.getStateOut();
    }

    auto map_state = [](math::ModeState ms) {
        switch (ms) {
            case math::ModeState::OFF:
                return CtsState::OFF;
            case math::ModeState::FAULT:
                return CtsState::FAULT;
            case math::ModeState::INHIBIT:
                return CtsState::INHIBIT;
            case math::ModeState::STANDBY:
                return CtsState::STANDBY;
            case math::ModeState::ACTIVE:
                return CtsState::ACTIVE;
            default:
                return CtsState::INHIBIT;
        }
    };

    memset(&m_front, 0, sizeof(m_front));
    memset(&m_rear, 0, sizeof(m_rear));

    m_front.warn_state = map_state(m_fcta_mode.getCurrentSubState());
    m_front.brake_state = map_state(m_fctb_mode.getCurrentSubState());
    m_rear.warn_state = map_state(m_rcta_mode.getCurrentSubState());
    m_rear.brake_state = map_state(m_rctb_mode.getCurrentSubState());
}

void CtsFunction::FCTAStateMachine(const AsVseOut &vse_out, const GlobalConfig &config) {
    bool fcta_was_active = (m_fcta_mode.getCurrentSubState() == math::ModeState::ACTIVE);
    bool fcta_was_standby = (m_fcta_mode.getCurrentSubState() == math::ModeState::STANDBY);

    m_fcta_release.signalRelease(m_front.warn_state == CtsState::ACTIVE, m_cts_cal.k_cts_alert_time_thrd_max, CTS_STEP_TIME);
    m_fcta_freezing.featureFreezing(m_front.warn_state == CtsState::ACTIVE, m_cts_cal.k_cta_freezing_time, CTS_STEP_TIME);

    m_fcta_mode_cond.state_off = (vse_out.fctb_switch == static_cast<uint8_t>(CtaWorkingStatus::OFF));
    m_fcta_mode_cond.state_fault = math::GetDiagBitValue(vse_out.function_did_config, static_cast<uint32_t>(FunctionDid::FCTA_FCTB));

    bool fcta_aeb_available = true;
    // bool fcta_aeb_available = ((vse_out.fctb_switch == static_cast<uint8_t>(CtaWorkingStatus::ONLY_WARING)) ||
    //                            (vse_out.fctb_switch == static_cast<uint8_t>(CtaWorkingStatus::WARING_BRAKE)));

    bool fcta_standby_entry = ((vse_out.display_speed / 3.6F >= m_cts_cal.k_fcta_min_enable_host_speed) && vse_out.display_speed / 3.6F <= m_cts_cal.k_fcta_max_enable_host_speed) &&
        (vse_out.actual_gear == static_cast<uint8_t>(GearPosition::DRIVE)) && fcta_aeb_available;
    bool fcta_inhibit_cond = (vse_out.display_speed / 3.6F > m_cts_cal.k_fcta_max_enable_host_speed_inhibit ||
                              (vse_out.display_speed / 3.6F <= m_cts_cal.k_fcta_min_enable_host_speed_inhibit && m_front.brake_state == CtsState::INHIBIT)) ||
        (vse_out.actual_gear != static_cast<uint8_t>(GearPosition::DRIVE)) || !fcta_aeb_available;

    m_fcta_mode_cond.state_inhibit = (fcta_inhibit_cond || m_common_inhibit_offdly.getStateOut() || m_fcta_freezing.getfeatureFreezing()) 
    && !m_fcta_warn_min_hold_active;

    bool fcta_max_time_reached = m_fcta_release.getSignalRelease();
    bool fcta_active_raw = (m_fcts_info[0].cur_level >= m_cts_cal.k_cta_min_active_level || m_fcts_info[1].cur_level >= m_cts_cal.k_cta_min_active_level);

    bool fcta_entering_active = (!fcta_was_active && fcta_was_standby && fcta_active_raw && !m_fcta_mode_cond.state_inhibit && !fcta_max_time_reached);
    if (fcta_entering_active) {
        m_fcta_warn_min_hold_active = true;
        m_fcta_warn_min_hold_elapsed_s = CTS_STEP_TIME;
    } else if (m_fcta_warn_min_hold_active) {
        m_fcta_warn_min_hold_elapsed_s += CTS_STEP_TIME;
    }

    bool fcta_min_hold_done = m_fcta_warn_min_hold_elapsed_s > m_cts_cal.k_cts_warn_min_hold_time - CTS_STEP_TIME;
    m_fcta_warn_min_hold_active &= !fcta_min_hold_done;

    if (fcta_entering_active) {
        for (int i = 0; i < CTS_MAX_SIDE; ++i) {
            m_fcta_warn_hold_side_active[i] = (m_fcts_info[i].cur_level > 0);
        }
    }

    if (m_fcta_mode_cond.state_off || m_fcta_mode_cond.state_fault || m_fcta_mode_cond.state_inhibit || fcta_max_time_reached ||
        fcta_min_hold_done) {
        m_fcta_warn_min_hold_active = false;
        m_fcta_warn_min_hold_elapsed_s = 0.0f;
        m_fcta_warn_hold_side_active[0] = false;
        m_fcta_warn_hold_side_active[1] = false;
    }

    m_fcta_mode_cond.state_active = (fcta_active_raw || m_fcta_warn_min_hold_active) && !fcta_max_time_reached;

    m_fcta_mode_cond.off2inhibit = (!m_fcta_mode_cond.state_off && !m_fcta_mode_cond.state_fault);
    m_fcta_mode_cond.fault2inhibit = !m_fcta_mode_cond.state_fault;
    m_fcta_mode_cond.inhibit2standby = fcta_standby_entry && !m_fcta_mode_cond.state_inhibit;
    m_fcta_mode_cond.standby2active = m_fcta_mode_cond.state_active;
    m_fcta_mode_cond.active2standby = !m_fcta_mode_cond.state_active && !fcta_inhibit_cond && !m_fcta_warn_min_hold_active;
    m_fcta_mode_cond.active2standby |= fcta_max_time_reached;

    m_fcta_mode_context.setCondition(m_fcta_mode_cond);
    m_fcta_mode.update(m_fcta_mode_context);

    if (m_cts_cal.k_cts_debug_log_enable) {
        m_debug.fcta.state_off = m_fcta_mode_cond.state_off;
        m_debug.fcta.state_fault = m_fcta_mode_cond.state_fault;
        m_debug.fcta.state_inhibit = m_fcta_mode_cond.state_inhibit;
        m_debug.fcta.state_active = m_fcta_mode_cond.state_active;
        m_debug.fcta.standby_entry = fcta_standby_entry;
        m_debug.fcta.inhibit_cond = fcta_inhibit_cond;
        m_debug.fcta.raw_trigger = fcta_active_raw;
        m_debug.fcta.max_time_reached = fcta_max_time_reached;
        m_debug.fcta.freezing = m_fcta_freezing.getfeatureFreezing();
        m_debug.fcta.min_hold_active = m_fcta_warn_min_hold_active;
        m_debug.fcta.speed = vse_out.display_speed / 3.6F;
        m_debug.fcta.gear = vse_out.actual_gear;
        m_debug.fcta.sw = vse_out.fctb_switch;
        m_debug.fcta.level_side0 = m_fcts_info[0].cur_level;
        m_debug.fcta.level_side1 = m_fcts_info[1].cur_level;
    }
}

void CtsFunction::FCTBStateMachine(const AsVseOut &vse_out, const GlobalConfig &config) {
    m_fctb_release.signalRelease(m_front.brake_state == CtsState::ACTIVE, m_cts_cal.k_cts_alert_time_thrd_max, CTS_STEP_TIME);
    m_fctb_freezing.featureFreezing(m_front.brake_state == CtsState::ACTIVE, m_cts_cal.k_cta_freezing_time, CTS_STEP_TIME);

    m_fctb_mode_cond.state_off = (vse_out.fctb_switch == static_cast<uint8_t>(CtaWorkingStatus::OFF) || 
    vse_out.fctb_switch == static_cast<uint8_t>(CtaWorkingStatus::ONLY_WARING));
    m_fctb_mode_cond.state_fault = math::GetDiagBitValue(vse_out.function_did_config, static_cast<uint32_t>(FunctionDid::FCTA_FCTB));

    bool fctb_aeb_available = true;
    // bool fctb_aeb_available = (vse_out.fctb_switch == static_cast<uint8_t>(CtaWorkingStatus::WARING_BRAKE));

    bool fctb_standby_entry = ((vse_out.display_speed / 3.6F >= m_cts_cal.k_fctb_min_enable_host_speed) && vse_out.display_speed / 3.6F <= m_cts_cal.k_fctb_max_enable_host_speed) &&
        (vse_out.actual_gear == static_cast<uint8_t>(GearPosition::DRIVE)) && fctb_aeb_available;
    bool fctb_inhibit_cond = (vse_out.display_speed / 3.6F > m_cts_cal.k_fctb_max_enable_host_speed_inhibit ||
                              (vse_out.display_speed / 3.6F <= m_cts_cal.k_fctb_min_enable_host_speed_inhibit && m_front.brake_state == CtsState::INHIBIT)) ||
        (vse_out.actual_gear != static_cast<uint8_t>(GearPosition::DRIVE)) || !fctb_aeb_available;

    m_fctb_mode_cond.state_inhibit = fctb_inhibit_cond || m_common_inhibit_offdly.getStateOut() || m_fctb_freezing.getfeatureFreezing();
    bool fctb_max_time_reached = m_fctb_release.getSignalRelease();
    bool fctb_active = (m_fcts_info[0].cur_level >= m_cts_cal.k_ctb_min_active_level || m_fcts_info[1].cur_level >= m_cts_cal.k_ctb_min_active_level);

    const bool fctb_low_speed_hold_enabled = !config.k_use_shadowmode && config.k_ctb_enable;
    const bool fctb_low_speed_hold_reset =
        !fctb_low_speed_hold_enabled || m_fctb_mode_cond.state_off || m_fctb_mode_cond.state_fault || fctb_max_time_reached;
    const float host_speed_abs = fabs(vse_out.speed);
    bool fctb_low_speed_hold_timeout = false;
    if (fctb_low_speed_hold_reset) {
        m_fctb_low_speed_hold_active = false;
        m_fctb_low_speed_hold_elapsed_s = 0.0F;
    } else if (m_fctb_mode_cond.state_inhibit) {
        m_fctb_low_speed_hold_active = false;
        m_fctb_low_speed_hold_elapsed_s = 0.0F;
    } else if (m_fctb_low_speed_hold_active) {
        m_fctb_low_speed_hold_elapsed_s += CTS_STEP_TIME;
        if (m_fctb_low_speed_hold_elapsed_s >= m_cts_cal.k_cts_low_speed_hold_time) {
            m_fctb_low_speed_hold_active = false;
            m_fctb_low_speed_hold_elapsed_s = 0.0F;
            fctb_low_speed_hold_timeout = true;
        }
    } else {
        const bool is_currently_active = (m_fctb_mode.getCurrentSubState() == math::ModeState::ACTIVE);
        if (is_currently_active && host_speed_abs < m_cts_cal.k_cts_low_speed_hold_entry_thres) {
            m_fctb_low_speed_hold_active = true;
            m_fctb_low_speed_hold_elapsed_s = 0.0F;
        }
    }
    const bool fctb_keep_active_for_low_speed = m_fctb_low_speed_hold_active;

    m_fctb_mode_cond.state_active =
        ((fctb_active && !fctb_low_speed_hold_timeout) || fctb_keep_active_for_low_speed) && !fctb_max_time_reached;

    m_fctb_mode_cond.off2inhibit = (!m_fctb_mode_cond.state_off && !m_fctb_mode_cond.state_fault);
    m_fctb_mode_cond.fault2inhibit = !m_fctb_mode_cond.state_fault;
    m_fctb_mode_cond.inhibit2standby = fctb_standby_entry && !m_fctb_mode_cond.state_inhibit;
    m_fctb_mode_cond.standby2active = m_fctb_mode_cond.state_active;
    m_fctb_mode_cond.active2standby = !m_fctb_mode_cond.state_active && !fctb_inhibit_cond;
    m_fctb_mode_cond.active2standby |= fctb_max_time_reached;

    m_fctb_mode_context.setCondition(m_fctb_mode_cond);
    m_fctb_mode.update(m_fctb_mode_context);

    if (m_cts_cal.k_cts_debug_log_enable) {
        m_debug.fctb.state_off = m_fctb_mode_cond.state_off;
        m_debug.fctb.state_fault = m_fctb_mode_cond.state_fault;
        m_debug.fctb.state_inhibit = m_fctb_mode_cond.state_inhibit;
        m_debug.fctb.state_active = m_fctb_mode_cond.state_active;
        m_debug.fctb.standby_entry = fctb_standby_entry;
        m_debug.fctb.inhibit_cond = fctb_inhibit_cond;
        m_debug.fctb.raw_trigger = fctb_active;
        m_debug.fctb.max_time_reached = fctb_max_time_reached;
        m_debug.fctb.freezing = m_fctb_freezing.getfeatureFreezing();
        m_debug.fctb.keep_active_low_speed = fctb_keep_active_for_low_speed;
        m_debug.fctb.speed = vse_out.display_speed / 3.6F;
        m_debug.fctb.gear = vse_out.actual_gear;
        m_debug.fctb.sw = vse_out.fctb_switch;
        m_debug.fctb.level_side0 = m_fcts_info[0].cur_level;
        m_debug.fctb.level_side1 = m_fcts_info[1].cur_level;
    }
}

void CtsFunction::RCTAStateMachine(const AsVseOut &vse_out, const GlobalConfig &config) {
    bool rcta_was_active = (m_rcta_mode.getCurrentSubState() == math::ModeState::ACTIVE);
    bool rcta_was_standby = (m_rcta_mode.getCurrentSubState() == math::ModeState::STANDBY);

    m_rcta_release.signalRelease(m_rear.warn_state == CtsState::ACTIVE, m_cts_cal.k_cts_alert_time_thrd_max, CTS_STEP_TIME);
    m_rcta_freezing.featureFreezing(m_rear.warn_state == CtsState::ACTIVE, m_cts_cal.k_cta_freezing_time, CTS_STEP_TIME);

    m_rcta_mode_cond.state_off = (vse_out.rctb_switch == static_cast<uint8_t>(CtaWorkingStatus::OFF));
    m_rcta_mode_cond.state_fault = math::GetDiagBitValue(vse_out.function_did_config, static_cast<uint32_t>(FunctionDid::RCTA_RCTB));
    bool rcta_aeb_available = (vse_out.esp_brake_available_st == static_cast<uint32_t>(BrakeSysAvailMask::AEB));
    rcta_aeb_available = true;

    bool rcta_standby_entry = (vse_out.display_speed / 3.6F <= m_cts_cal.k_rcta_max_enable_host_speed && vse_out.display_speed / 3.6F >= m_cts_cal.k_rcta_min_enable_host_speed) &&
        (vse_out.actual_gear == static_cast<uint8_t>(GearPosition::REVERSE)) && rcta_aeb_available;
    bool rcta_inhibit_cond = (vse_out.display_speed / 3.6F < m_cts_cal.k_rcta_min_enable_host_speed_inhibit ||
                              (vse_out.display_speed / 3.6F >= m_cts_cal.k_rcta_max_enable_host_speed_inhibit && m_rear.brake_state == CtsState::INHIBIT)) ||
        (vse_out.actual_gear != static_cast<uint8_t>(GearPosition::REVERSE)) || !rcta_aeb_available;

    m_rcta_mode_cond.state_inhibit = (rcta_inhibit_cond || m_common_inhibit_offdly.getStateOut() || m_rcta_freezing.getfeatureFreezing())
        && !m_rcta_warn_min_hold_active;
    bool rcta_warn_raw = (m_rcts_info[0].cur_level > 0 || m_rcts_info[1].cur_level > 0);
    bool rcta_max_time_reached = m_rcta_release.getSignalRelease();

    bool rcta_entering_active = (!rcta_was_active && rcta_was_standby && rcta_warn_raw && !m_rcta_mode_cond.state_inhibit && !rcta_max_time_reached);
    if (rcta_entering_active) {
        m_rcta_warn_min_hold_active = true;
        m_rcta_warn_min_hold_elapsed_s = CTS_STEP_TIME;
    } else if (m_rcta_warn_min_hold_active) {
        m_rcta_warn_min_hold_elapsed_s += CTS_STEP_TIME;
    }

    bool rcta_min_hold_done = m_rcta_warn_min_hold_elapsed_s > m_cts_cal.k_cts_warn_min_hold_time - CTS_STEP_TIME;
    m_rcta_warn_min_hold_active &= !rcta_min_hold_done;

    if (rcta_entering_active) {
        for (int i = 0; i < CTS_MAX_SIDE; ++i) {
            m_rcta_warn_hold_side_active[i] = (m_rcts_info[i].cur_level > 0);
        }
    }

    if (m_rcta_mode_cond.state_off || m_rcta_mode_cond.state_fault || m_rcta_mode_cond.state_inhibit || rcta_max_time_reached ||
        rcta_min_hold_done) {
        m_rcta_warn_min_hold_active = false;
        m_rcta_warn_min_hold_elapsed_s = 0.0f;
        m_rcta_warn_hold_side_active[0] = false;
        m_rcta_warn_hold_side_active[1] = false;
    }

    m_rcta_mode_cond.state_active = (rcta_warn_raw || m_rcta_warn_min_hold_active) && !rcta_max_time_reached;

    m_rcta_mode_cond.off2inhibit = (!m_rcta_mode_cond.state_off && !m_rcta_mode_cond.state_fault);
    m_rcta_mode_cond.fault2inhibit = !m_rcta_mode_cond.state_fault;
    m_rcta_mode_cond.inhibit2standby = rcta_standby_entry && !m_rcta_mode_cond.state_inhibit;
    m_rcta_mode_cond.standby2active = m_rcta_mode_cond.state_active;
    m_rcta_mode_cond.active2standby = !m_rcta_mode_cond.state_active && !rcta_inhibit_cond && !m_rcta_warn_min_hold_active;
    m_rcta_mode_cond.active2standby |= rcta_max_time_reached;

    m_rcta_mode_context.setCondition(m_rcta_mode_cond);
    m_rcta_mode.update(m_rcta_mode_context);

    if (m_cts_cal.k_cts_debug_log_enable) {
        m_debug.rcta.state_off = m_rcta_mode_cond.state_off;
        m_debug.rcta.state_fault = m_rcta_mode_cond.state_fault;
        m_debug.rcta.state_inhibit = m_rcta_mode_cond.state_inhibit;
        m_debug.rcta.state_active = m_rcta_mode_cond.state_active;
        m_debug.rcta.standby_entry = rcta_standby_entry;
        m_debug.rcta.inhibit_cond = rcta_inhibit_cond;
        m_debug.rcta.raw_trigger = rcta_warn_raw;
        m_debug.rcta.max_time_reached = rcta_max_time_reached;
        m_debug.rcta.freezing = m_rcta_freezing.getfeatureFreezing();
        m_debug.rcta.min_hold_active = m_rcta_warn_min_hold_active;
        m_debug.rcta.speed = vse_out.display_speed / 3.6F;
        m_debug.rcta.gear = vse_out.actual_gear;
        m_debug.rcta.sw = vse_out.rctb_switch;
        m_debug.rcta.level_side0 = m_rcts_info[0].cur_level;
        m_debug.rcta.level_side1 = m_rcts_info[1].cur_level;
    }
}

void CtsFunction::RCTBStateMachine(const AsVseOut &vse_out, const GlobalConfig &config) {
    m_rctb_release.signalRelease(m_rear.brake_state == CtsState::ACTIVE, m_cts_cal.k_cts_alert_time_thrd_max, CTS_STEP_TIME);
    m_rctb_freezing.featureFreezing(m_rear.brake_state == CtsState::ACTIVE, m_cts_cal.k_cta_freezing_time, CTS_STEP_TIME);

    m_rctb_mode_cond.state_off = (vse_out.rctb_switch == static_cast<uint8_t>(CtaWorkingStatus::OFF) || 
    vse_out.rctb_switch == static_cast<uint8_t>(CtaWorkingStatus::ONLY_WARING));
    m_rctb_mode_cond.state_fault = math::GetDiagBitValue(vse_out.function_did_config, static_cast<uint32_t>(FunctionDid::RCTA_RCTB));

    bool rctb_aeb_available = (vse_out.esp_brake_available_st == static_cast<uint32_t>(BrakeSysAvailMask::AEB));
    rctb_aeb_available = true;
    // bool rctb_aeb_available = (vse_out.rctb_switch == static_cast<uint8_t>(CtaWorkingStatus::WARING_BRAKE));
    bool rctb_standby_entry = (vse_out.display_speed / 3.6F <= m_cts_cal.k_rctb_max_enable_host_speed && vse_out.display_speed / 3.6F >= m_cts_cal.k_rctb_min_enable_host_speed) &&
        (vse_out.actual_gear == static_cast<uint8_t>(GearPosition::REVERSE)) && rctb_aeb_available;
    bool rctb_inhibit_cond = (vse_out.display_speed / 3.6F < m_cts_cal.k_rctb_min_enable_host_speed_inhibit ||
                              (vse_out.display_speed / 3.6F >= m_cts_cal.k_rctb_max_enable_host_speed_inhibit && m_rear.brake_state == CtsState::INHIBIT)) ||
        (vse_out.actual_gear != static_cast<uint8_t>(GearPosition::REVERSE)) || !rctb_aeb_available;

    m_rctb_mode_cond.state_inhibit = rctb_inhibit_cond || m_common_inhibit_offdly.getStateOut() || m_rctb_freezing.getfeatureFreezing();
    bool rctb_any_warn = (m_rcts_info[0].cur_level >= m_cts_cal.k_ctb_min_active_level || m_rcts_info[1].cur_level >= m_cts_cal.k_ctb_min_active_level);
    bool rctb_max_time_reached = m_rctb_release.getSignalRelease();

    const bool rctb_low_speed_hold_enabled = !config.k_use_shadowmode && config.k_ctb_enable;
    const bool rctb_low_speed_hold_reset =
        !rctb_low_speed_hold_enabled || m_rctb_mode_cond.state_off || m_rctb_mode_cond.state_fault || rctb_max_time_reached;
    const float host_speed_abs = fabs(vse_out.speed);
    bool rctb_low_speed_hold_timeout = false;
    if (rctb_low_speed_hold_reset) {
        m_rctb_low_speed_hold_active = false;
        m_rctb_low_speed_hold_elapsed_s = 0.0F;
    } else if (m_rctb_mode_cond.state_inhibit) {
        m_rctb_low_speed_hold_active = false;
        m_rctb_low_speed_hold_elapsed_s = 0.0F;
    } else if (m_rctb_low_speed_hold_active) {
        m_rctb_low_speed_hold_elapsed_s += CTS_STEP_TIME;
        if (m_rctb_low_speed_hold_elapsed_s >= m_cts_cal.k_cts_low_speed_hold_time) {
            m_rctb_low_speed_hold_active = false;
            m_rctb_low_speed_hold_elapsed_s = 0.0F;
            rctb_low_speed_hold_timeout = true;
        }
    } else {
        const bool is_currently_active = (m_rctb_mode.getCurrentSubState() == math::ModeState::ACTIVE);
        if (is_currently_active && host_speed_abs < m_cts_cal.k_cts_low_speed_hold_entry_thres) {
            m_rctb_low_speed_hold_active = true;
            m_rctb_low_speed_hold_elapsed_s = 0.0F;
        }
    }
    const bool rctb_keep_active_for_low_speed = m_rctb_low_speed_hold_active;

    m_rctb_mode_cond.state_active =
        ((rctb_any_warn && !rctb_low_speed_hold_timeout) || rctb_keep_active_for_low_speed) && !rctb_max_time_reached;

    m_rctb_mode_cond.off2inhibit = (!m_rctb_mode_cond.state_off && !m_rctb_mode_cond.state_fault);
    m_rctb_mode_cond.fault2inhibit = !m_rctb_mode_cond.state_fault;
    m_rctb_mode_cond.inhibit2standby = rctb_standby_entry && !m_rctb_mode_cond.state_inhibit;
    m_rctb_mode_cond.standby2active = m_rctb_mode_cond.state_active;
    m_rctb_mode_cond.active2standby = !m_rctb_mode_cond.state_active && !rctb_inhibit_cond;
    m_rctb_mode_cond.active2standby |= rctb_max_time_reached;

    m_rctb_mode_context.setCondition(m_rctb_mode_cond);
    m_rctb_mode.update(m_rctb_mode_context);

    if (m_cts_cal.k_cts_debug_log_enable) {
        m_debug.rctb.state_off = m_rctb_mode_cond.state_off;
        m_debug.rctb.state_fault = m_rctb_mode_cond.state_fault;
        m_debug.rctb.state_inhibit = m_rctb_mode_cond.state_inhibit;
        m_debug.rctb.state_active = m_rctb_mode_cond.state_active;
        m_debug.rctb.standby_entry = rctb_standby_entry;
        m_debug.rctb.inhibit_cond = rctb_inhibit_cond;
        m_debug.rctb.raw_trigger = rctb_any_warn;
        m_debug.rctb.max_time_reached = rctb_max_time_reached;
        m_debug.rctb.freezing = m_rctb_freezing.getfeatureFreezing();
        m_debug.rctb.keep_active_low_speed = rctb_keep_active_for_low_speed;
        m_debug.rctb.speed = vse_out.display_speed / 3.6F;
        m_debug.rctb.gear = vse_out.actual_gear;
        m_debug.rctb.sw = vse_out.rctb_switch;
        m_debug.rctb.level_side0 = m_rcts_info[0].cur_level;
        m_debug.rctb.level_side1 = m_rcts_info[1].cur_level;
    }
}

void CtsFunction::FillOutput(const AsVseOut &vse_out, const GlobalConfig &config, const std::array<WarnInfo, CTS_MAX_SIDE> &warn_infos, CtsOut &out,
                             CtsDirection dir) {
    uint8_t sw = (dir == CtsDirection::FRONT) ? vse_out.fctb_switch : vse_out.rctb_switch;
    switch (sw) {
        case static_cast<uint8_t>(CtsSwitch::ONLY_WARING):
            out.working_status = CtaWorkingStatus::ONLY_WARING;
            out.switch_req = static_cast<uint32_t>(SwitchReqOut::LIGHT);
            break;
        case static_cast<uint8_t>(CtsSwitch::WARING_BRAKE):
            out.working_status = CtaWorkingStatus::WARING_BRAKE;
            out.switch_req = static_cast<uint32_t>(SwitchReqOut::LIGHT_AND_SOUND);
            break;
        case static_cast<uint8_t>(CtsSwitch::OFF):
            out.working_status = CtaWorkingStatus::OFF;
            out.switch_req = static_cast<uint32_t>(SwitchReqOut::OFF);
            break;
        default:
            if(out.warn_state == CtsState::OFF){
                out.switch_req = static_cast<uint32_t>(SwitchReqOut::OFF);
                out.working_status = CtaWorkingStatus::OFF;
            }else if(out.warn_state != CtsState::OFF && out.brake_state == CtsState::OFF){
                out.switch_req = static_cast<uint32_t>(SwitchReqOut::LIGHT);
                out.working_status = CtaWorkingStatus::ONLY_WARING;
            }else{
                out.switch_req = static_cast<uint32_t>(SwitchReqOut::LIGHT_AND_SOUND);
                out.working_status = CtaWorkingStatus::WARING_BRAKE;
            }
            break;
    }

    bool warn_can_output = (out.warn_state == CtsState::ACTIVE);
    bool brake_can_output = (out.brake_state == CtsState::ACTIVE);
    const bool low_speed_brake_hold = (dir == CtsDirection::FRONT) ? m_fctb_low_speed_hold_active : m_rctb_low_speed_hold_active;
    const float brake_dec_req = low_speed_brake_hold ? m_cts_cal.k_cts_low_speed_brake_dec_req : m_cts_cal.k_cts_brake_dec_req;
    for (int side = 0; side < CTS_MAX_SIDE; ++side) {
        const WarnInfo &warn_info = warn_infos[side];
        AsTargetInfo_T &tgt_out = (side == 0) ? out.left_tgt : out.right_tgt;

        if (warn_info.obs_index >= 0 && m_obs_data[warn_info.obs_index].m_obs->fus_trkID == warn_info.obs_fusId) {
            FillTargetInfo(m_obs_data[warn_info.obs_index], side, tgt_out);
        }

        // hold_cycles(0.6s)到期后cur_level会归零，但min_hold(1.0s)仍在保持ACTIVE状态。
        // 用min_hold触发时记录的侧向活跃标志填补这段gap，确保告警输出完整覆盖1.0s。
        bool hold_side_active = false;
        if (dir == CtsDirection::FRONT) {
            hold_side_active = m_fcta_warn_min_hold_active && m_fcta_warn_hold_side_active[side];
        } else {
            hold_side_active = m_rcta_warn_min_hold_active && m_rcta_warn_hold_side_active[side];
        }
        bool side_has_threat = (warn_info.cur_level > 0) || hold_side_active;

        if (warn_can_output && side_has_threat) {
            if (side == 0) {
                out.left_warn = OnOffStatus::Active;
                out.sound = OnOffStatus::Active;
            } else {
                out.right_warn = OnOffStatus::Active;
                out.sound = OnOffStatus::Active;
            }
        }
        if ((warn_can_output || (brake_can_output && !m_rctb_low_speed_hold_active && !m_fctb_low_speed_hold_active)) && side_has_threat) {
            if (side == 0) {
                out.collision_dir = CtbCollisionDir::LEFT;
            } else {
                out.collision_dir = CtbCollisionDir::RIGHT;
            }
        }
        if (brake_can_output) {
            out.brake_req_valid = OnOffStatus::Active;
            out.brake_req = OnOffStatus::Active;
            out.brake_dec_req = brake_dec_req;
        }
    }

    if (config.k_use_shadowmode) {
        out.left_warn = OnOffStatus::NotActive;
        out.right_warn = OnOffStatus::NotActive;
        out.sound = OnOffStatus::NotActive;
        out.brake_req = OnOffStatus::NotActive;
        out.brake_req_valid = OnOffStatus::NotActive;
        out.brake_dec_req = 0.0f;
    }
    if (!config.k_cta_enable) {
        out.left_warn = OnOffStatus::NotActive;
        out.right_warn = OnOffStatus::NotActive;
        out.sound = OnOffStatus::NotActive;
    }
    if (!config.k_ctb_enable) {
        out.brake_req = OnOffStatus::NotActive;
        out.brake_req_valid = OnOffStatus::NotActive;
        out.brake_dec_req = 0.0f;
    } else {
        out.brake_req_valid = OnOffStatus::Active;
    }
}

void CtsFunction::FillTargetInfo(const CtsObsData &obs_data, int side, AsTargetInfo_T &tgt_info) {
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
    tgt_info.ttc = obs_data.m_attr[side].lat_ttc;
}

} // namespace cts
} // namespace active_safety
