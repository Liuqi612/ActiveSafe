#include "lgsf_function.h"

namespace active_safety {
namespace longsafe {
LgSfFunction::LgSfFunction() {
    aeb_state_   = AebStatus::AEB_Inhibit;
    fcw_state_   = FcwStatus::FCW_Inhibit;
    inhibit_mask = 0;
}

LgSfFunction::~LgSfFunction() = default;

void LgSfFunction::Update(const AsVseOut &vse_out, const LongSafeObject &obs, const GlobalConfig &config, const AsCurvaturePath &ego_path) {
    cmbb_threat_n_1_ = cmbb_threat_;
    drvr_est_.Run(vse_out, obs);
    threat_assessor_.Update(vse_out, drvr_est_, obs, ego_path);
    common_inhibit_.Update(vse_out, obs, threat_assessor_);
    EvalAebDeactive(vse_out, obs);
    CheckEbaBrkActive(vse_out);
    UpdateCmbbThreat();
    CalcCloseLoopDecel(vse_out, obs);
    InhibitEvaluator(vse_out);
    FaultEvaluator(vse_out);
    AebStateMachine(vse_out.longsafe_switch == 3 || vse_out.longsafe_switch == 2, vse_out.speed);
    FcwStateMachine(vse_out.longsafe_switch == 3 || vse_out.longsafe_switch == 1);
    BrakeDecelArb();
    prev_obs = obs;
    OutPutMapping(config);
}

void LgSfFunction::AebStateMachine(bool aeb_switch_on, float host_speed) {

    switch (aeb_state_) {
        case AebStatus::AEB_OFF:
            if (aeb_fault) {
                aeb_state_ = AebStatus::AEB_Fault;
            } else if (aeb_switch_on) {
                aeb_state_ = AebStatus::AEB_Inhibit;
            }
            break;

        case AebStatus::AEB_Fault:
            if ((aeb_fault == false)  &&  (aeb_switch_on == false)) {
                aeb_state_ = AebStatus::AEB_OFF;
            } else if (aeb_fault == false && aeb_switch_on == true) {
                aeb_state_ = AebStatus::AEB_Inhibit;
            }
            break;

        case AebStatus::AEB_Inhibit:
            if (aeb_fault) {
                aeb_state_ = AebStatus::AEB_Fault;
            } else if (aeb_switch_on == false) {
                aeb_state_ = AebStatus::AEB_OFF;
            } else if (aeb_inhibit == false) {
                aeb_state_ = AebStatus::AEB_Standby;
            }
            break;

        case AebStatus::AEB_Standby:
            if (aeb_fault) {
                aeb_state_ = AebStatus::AEB_Fault;
            } else if (aeb_switch_on == false) {
                aeb_state_ = AebStatus::AEB_OFF;
            } else if (aeb_inhibit) {
                aeb_state_ = AebStatus::AEB_Inhibit;
            } else if (eba_atv && !aeb_atv_freez_.getfeatureFreezing()) {
                aeb_state_ = AebStatus::EBA_Active;
            } else if (aeb_atv && !aeb_atv_freez_.getfeatureFreezing()) {
                aeb_state_ = AebStatus::AEB_Active;
            }
            break;

        case AebStatus::EBA_Active:
            if (aeb_fault) {
                aeb_state_ = AebStatus::AEB_Fault;
            } else if (aeb_switch_on == false) {
                aeb_state_ = AebStatus::AEB_OFF;
            } else if (aeb_inhibit) {
                aeb_state_ = AebStatus::AEB_Inhibit;
            } else if (eba_atv == false && aeb_atv) {
                aeb_state_ = AebStatus::AEB_Active;
            } else if (eba_atv == false && aeb_atv == false) {
                aeb_state_ = AebStatus::AEB_Standby;
            }
            break;

        case AebStatus::AEB_Active:
            if (aeb_fault) {
                aeb_state_ = AebStatus::AEB_Fault;
            } else if (aeb_switch_on == false) {
                aeb_state_ = AebStatus::AEB_OFF;
            } else if (aeb_inhibit) {
                aeb_state_ = AebStatus::AEB_Inhibit;
            } else if (eba_atv) {
                aeb_state_ = AebStatus::EBA_Active;
            } else if (cmbb_threat_ == 0) {
                aeb_state_ = AebStatus::AEB_Standby;
            }
            break;

        default:
            break;
    }
    bool aeb_active = (aeb_state_ == AebStatus::EBA_Active || aeb_state_ == AebStatus::AEB_Active);
    (void)aeb_atv_freez_.featureFreezing(aeb_active, cmbb_cal_.k_aeb_brake_freezing_time, LGSF_FUNC_TIME_STEP);
    // Update hold req.
    if ((aeb_state_ == AebStatus::AEB_Active || aeb_state_ == AebStatus::EBA_Active)  &&  (host_speed < cmbb_cal_.k_host_standstill_spd_mps)) {
        hold_req = true;
    } else {
        hold_req = false;
    }
}

void LgSfFunction::CheckEbaBrkActive(const AsVseOut &vse_out) {
    bool drv_brk_pdl_chk =
        fabs(vse_out.brake_pedal_pos) > cmbb_cal_.k_drv_brk_pdl_pos_thres && fabs(vse_out.brake_pressure) > cmbb_cal_.k_drv_brk_prs_thres;

    float brk_pdl_rate_thres = cmbb_cal_.k_brk_pdl_rate_thres_aeb_notatv;
    if (aeb_state_ == AebStatus::AEB_Active) {
        brk_pdl_rate_thres = cmbb_cal_.k_brk_pdl_rate_thres_aeb_atv;
    }

    bool brkpdlrate = fabs(vse_out.brake_pedal_pos_rate) >= brk_pdl_rate_thres;
    (void)brkpdlrate_offdly_.offDelay(brkpdlrate, 0.15F, LGSF_FUNC_TIME_STEP);

    bool brk_pos_chk = (fabs(vse_out.brake_pedal_pos) >= cmbb_cal_.k_brk_pdl_pos_thres && brkpdlrate_offdly_.getStateOut());
    bool brk_prs_chk =
        (fabs(vse_out.brake_pressure) >= cmbb_cal_.k_brk_prs_thres && fabs(vse_out.brake_pressure_rate) >= cmbb_cal_.k_brk_prs_rate_thres - 0.00001F);

    drv_brk_atv_ = drv_brk_pdl_chk && (brk_pos_chk || brk_prs_chk);

    eba_atv = ((drv_brk_atv_ && threat_assessor_.threat_iba_ && vse_out.long_accel < -2.30F) || (aeb_state_ == AebStatus::EBA_Active)) &&
              !brake_deactive && !common_inhibit_.inhibit_res_ && !aeb_atv_freez_.getfeatureFreezing();
}

void LgSfFunction::FcwStateMachine(bool fcw_switch_on) {
    //[TODO]
}

void LgSfFunction::UpdateCmbbThreat() {
    bool active = ((threat_assessor_.threat_autobraking_ || threat_assessor_.threat_iba_) && !common_inhibit_.inhibit_res_ &&
                   !aeb_atv_freez_.getfeatureFreezing());

    switch (cmbb_threat_) {
        case CmbbThreat::No_Threat:
            brake_threat_cnt_ = 0.0F;
            if (active) {
                cmbb_threat_ = CmbbThreat::Brake_Preliminary;
                brake_threat_cnt_ += 0.02F;
                aeb_atv = true;
            }
            break;

        case CmbbThreat::Brake_Preliminary:
            brake_threat_cnt_ += 0.02F;
            if (!active || brake_deactive) {
                cmbb_threat_ = CmbbThreat::No_Threat;
                aeb_atv      = false;
            } else if (brake_threat_cnt_ > cmbb_cal_.k_preliminary_to_confirmed_count) {
                cmbb_threat_ = CmbbThreat::Brake_Confirmed;
                aeb_atv      = true;
            }
            break;
        case CmbbThreat::Brake_Confirmed:
            brake_threat_cnt_ += 0.02F;
            if (brake_deactive) {
                cmbb_threat_ = CmbbThreat::No_Threat;
                aeb_atv      = false;
            }
            break;
        default:
            break;
    }
}

void LgSfFunction::CalcCloseLoopDecel(const AsVseOut &vse_out, const LongSafeObject &obs) {
    float obs_range = obs.long_posn - 0.5F * obs.length * cosf(obs.heading) - vse_out.config.k_dist_to_rear_axle;

    // calc predict time.
    float obs_spd      = obs.long_vel;
    float obs_accel    = obs.long_accel;
    float range_rate   = obs_spd - vse_out.vcs_long_vel;
    float predict_time = math::LookUpTable::LookupTable2D<5, 11>(cmbb_cal_.k_predict_time_range_accel_x, cmbb_cal_.k_predict_time_range_x,
                                                                 cmbb_cal_.k_max_predict_time, obs_accel, range_rate);

    bool closerange_leadecel = (predict_time >= 0.6F && obs_range <= 10.0F);

    float ttc = obs.ttr;
    if (obs_accel < -0.3F) {
        ttc = fmin(ttc, math::SafeDivide(obs_spd, fabs(obs_accel)));
    }
    predict_time    = math::Clamp(fmin(ttc, predict_time), 0.0F, 3.0F);
    float host_dist = predict_time * vse_out.speed;

    float obs_dist = 0.0F;
    MotionLinearPredict::LinearPredictWithStop(obs_dist, obs_spd, obs_accel, predict_time, true);

    float host_allow_travel_dist = obs_dist + obs_range - obs.offs_lgt_short_pred - host_dist;

    host_allow_travel_dist     = math::Clamp(host_allow_travel_dist, 0.0F, 100.0F) * 2.0F;
    float delta_spd            = obs_spd - vse_out.vcs_long_vel;
    float sqrd_delta_spd_accel = math::SafeDivide(pow(delta_spd, 2) * math::SignF(delta_spd), host_allow_travel_dist);
    float need_decel           = fmax(sqrd_delta_spd_accel, -12.0F);

    if (closerange_leadecel) {
        float host_spd_sqrd             = vse_out.vcs_long_vel * vse_out.vcs_long_vel;
        float delta_spd_sqrd_accel      = math::SafeDivide(obs_spd * obs_spd - host_spd_sqrd, host_allow_travel_dist);
        float satu_delta_spd_sqrd_accel = fmax(delta_spd_sqrd_accel, -12.0F);
        need_decel                      = satu_delta_spd_sqrd_accel;
    }
    bool use_stronger_filter = (obs_range <= 2.0F && need_decel <= -1.0F && range_rate > -4.5F && range_rate < 1.0F);

    // printf("host_allow_travel_dist:%f obs_range:%f delta_spd:%f
    // sqrd_delta_spd_accel:%f\n",host_allow_travel_dist,obs_range,delta_spd,sqrd_delta_spd_accel);

    if (need_decel < vse_out.long_accel * 1.0F) {
        float dec_gap = fmin(need_decel, 0.0F) - vse_out.long_accel;
        dec_gap = math::LookUpTable::LookupTable1D(threat_assessor_.threat_ass_cal_.k_decel_diff_x, cmbb_cal_.k_clamp_ramp_down_factor, dec_gap);
        float min_dec = fmin(vse_out.long_accel, fmin(close_loop_dec, aeb_req_dec));
        min_dec       = min_dec - dec_gap;
        need_decel    = fmax(need_decel, min_dec);
        need_decel    = math::Clamp(need_decel, -12.0F, 0.0F);
    }

    close_loop_dec_filt = math::LowPassFilter(need_decel, close_loop_dec_filt, 1.0F);

    if (use_stronger_filter) {
        close_loop_dec = close_loop_dec_filt;
    } else {
        close_loop_dec = need_decel;
    }

    close_loop_dec = math::Clamp(close_loop_dec, -12.0F, 0.0F);
}

void LgSfFunction::BrakeDecelArb() {
    if (hold_req) {
        aeb_req_dec = fmin(close_loop_dec, cmbb_cal_.k_max_req_decel_after_brake);
    } else if (aeb_state_ == AebStatus::AEB_Active || aeb_state_ == AebStatus::EBA_Active) {
        aeb_req_dec = close_loop_dec;
    } else {
        aeb_req_dec = 0.0F;
    }
}

void LgSfFunction::EvalAebDeactive(const AsVseOut &vse_out, const LongSafeObject &obs) {
    // 1. Steer OverRide.[TODO]

    // 2. GasPdl OverRide.
    aeb_system_ovrd = false;
    // 3. Brake release

    // check no brake req.
    bool no_req = (threat_assessor_.rqrd_neg_lgt_accel_ > -0.001F);
    (void)no_brk_req.onDelay(no_req, cmbb_cal_.k_aeb_deactive_no_brk_req_time_thres, LGSF_FUNC_TIME_STEP);

    // check high ttc time
    float ttc          = 100.0F;
    bool  ttc_solution = false;
    bool  dist         = obs.long_posn - vse_out.config.k_dist_to_rear_axle - 0.5F * obs.length * cosf(obs.heading);

    if (fabs(obs.long_accel) > 0.01F) {
        float rel_lgt_vel = obs.long_vel - vse_out.vcs_long_vel;
        float safe_delta  = math::SafeDivide(rel_lgt_vel * rel_lgt_vel, 2.0F * obs.long_accel);
        if ((dist < safe_delta && obs.long_accel < 0.0F) || (dist > safe_delta && obs.long_accel > 0.0F)) {
            ttc_solution = true;
        }
    }

    if ((ttc_solution == false)  &&  (dist > 0.0F)) {
        ttc_solution = (obs.ttr < 0.0F);
    }
    if (ttc_solution == false) {
        ttc = obs.ttr;
    }
    bool check_high_ttc = (ttc > cmbb_cal_.k_aeb_deactive_high_ttc_thres && obs.fus_trkID > 0);
    (void)high_ttc.onDelay(check_high_ttc, cmbb_cal_.k_aeb_deactive_high_ttc_time_thres, LGSF_FUNC_TIME_STEP);

    bool collision_avoid_by_brk = (obs.long_vel > 1.5F && (no_brk_req.getStateOut() || high_ttc.getStateOut()));
    // bool collision_avoid_by_brk = (obs.long_vel > 1.5F && (high_ttc.getStateOut()));
    // check obj info large change.
    bool obj_data_change_detect =
        (prev_obs.fus_trkID > 0 && prev_obs.fus_trkID != obs.fus_trkID) &&
        (fabs(prev_obs.long_posn - obs.long_posn) > 2.0F || fabs(prev_obs.lat_posn - obs.lat_posn) > 2.0F || fabs(obs.ttr - prev_obs.ttr) > 1.0F);
    // checl no object.
    bool no_obj = (obs.fus_trkID <= 0);

    bool obj_deactive = (no_obj || collision_avoid_by_brk || obj_data_change_detect);
    // check delay deactive.
    bool low_spd = vse_out.speed < cmbb_cal_.k_aeb_delay_deactive_min_spd;
    (void)dly_low_spd.onDelay(low_spd, cmbb_cal_.k_aeb_delay_deactive_min_spd_time, LGSF_FUNC_TIME_STEP);
    bool delay_deavtive = low_spd ^ dly_low_spd.getStateOut();

    // vehicle standstill.
    bool veh_standstill       = vse_out.speed < cmbb_cal_.k_host_standstill_spd_mps;
    bool veh_station_deactive = station_veh.onDelay(veh_standstill, cmbb_cal_.k_aeb_deactive_static_veh_time, LGSF_FUNC_TIME_STEP);

    brake_deactive = (veh_station_deactive || (obj_deactive && !delay_deavtive) || aeb_system_ovrd);
}

void LgSfFunction::InhibitEvaluator(const AsVseOut &vse_out) {
    const CmbbFuncInhibitStateCal &inhibit_cal = cmbb_cal_.inhibit_info_;

    bool signal_res = (vse_out.gas_pedal_pos > inhibit_cal.k_acc_pdl_pos_enter_thres);
    (void)inhibit_acc_pdl_on.onDelay(signal_res, inhibit_cal.k_acc_pdl_pos_enter_time, LGSF_FUNC_TIME_STEP);
    signal_res = (vse_out.gas_pedal_pos > inhibit_cal.k_acc_pdl_pos_exit_thres);
    (void)inhibit_acc_pdl_off.offDelay(signal_res, inhibit_cal.k_acc_pdl_pos_exit_time, LGSF_FUNC_TIME_STEP);
    if (inhibit_acc_pdl_on.getStateOut()) {
        inhibit_mask |= (1 << 0);
    } else {
        if (inhibit_acc_pdl_off.getStateOut() == false) {
            inhibit_mask &= ~(1 << 0);
        } else {
            // do nothing.
        }
    }

    signal_res = (fabs(vse_out.steerwheelangle) > inhibit_cal.k_steer_whl_angle_enter_thres);
    (void)inhibit_steer_wheel_angle_on.onDelay(signal_res, inhibit_cal.k_steer_whl_angle_enter_time, LGSF_FUNC_TIME_STEP);
    signal_res = (fabs(vse_out.steerwheelangle) >= inhibit_cal.k_steer_whl_angle_exit_thres);
    (void)inhibit_steer_wheel_angle_off.offDelay(signal_res, inhibit_cal.k_steer_whl_angle_exit_time, LGSF_FUNC_TIME_STEP);
    if (inhibit_steer_wheel_angle_on.getStateOut()) {
        inhibit_mask |= (1 << 1);
    } else {
        if (inhibit_steer_wheel_angle_off.getStateOut() == false) {
            inhibit_mask &= ~(1 << 1);
        } else {
            // do nothing.
        }
    }

    signal_res          = ((vse_out.speed < inhibit_cal.k_host_speed_enter_low_thres)  ||  (vse_out.speed > inhibit_cal.k_host_speed_enter_up_thres));
    bool aeb_not_active = !(aeb_state_ == AebStatus::AEB_Active || aeb_state_ == AebStatus::EBA_Active);

    (void)inhibit_host_speed_on.onDelay(signal_res && aeb_not_active, inhibit_cal.k_host_speed_enter_time, LGSF_FUNC_TIME_STEP);
    signal_res = ((vse_out.speed < inhibit_cal.k_host_speed_exit_low_thres)  ||  (vse_out.speed > inhibit_cal.k_host_speed_exit_up_thres));
    (void)inhibit_host_speed_off.offDelay(signal_res && aeb_not_active, inhibit_cal.k_host_speed_exit_time, LGSF_FUNC_TIME_STEP);
    if (inhibit_host_speed_on.getStateOut()) {
        inhibit_mask |= (1 << 2);
    } else {
        if (inhibit_host_speed_off.getStateOut() == false) {
            inhibit_mask &= ~(1 << 2);
        } else {
            // do nothing.
        }
    }

    signal_res = (fabs(vse_out.yawrate) > inhibit_cal.k_yaw_rate_enter_thres);
    (void)inhibit_yaw_rate_on.onDelay(signal_res, inhibit_cal.k_yaw_rate_enter_time, LGSF_FUNC_TIME_STEP);
    signal_res = (fabs(vse_out.yawrate) > inhibit_cal.k_yaw_rate_exit_thres);
    (void)inhibit_yaw_rate_off.offDelay(signal_res, inhibit_cal.k_yaw_rate_exit_time, LGSF_FUNC_TIME_STEP);
    if (inhibit_yaw_rate_on.getStateOut()) {
        inhibit_mask |= (1 << 3);
    } else {
        if (inhibit_yaw_rate_off.getStateOut() == false) {
            inhibit_mask &= ~(1 << 3);
        } else {
            // do nothing.
        }
    }

    signal_res = (vse_out.fl_door_st == 1 || vse_out.fr_door_st == 1 || vse_out.rl_door_st == 1 || vse_out.rr_door_st == 1 ||
                  vse_out.eng_hood_unlock_warn == 1 || vse_out.trunk_st == 1);
    (void)inhibit_door_open_on.onDelay(signal_res, inhibit_cal.k_door_open_enter_time, LGSF_FUNC_TIME_STEP);
    (void)inhibit_door_open_off.offDelay(signal_res, inhibit_cal.k_door_open_exit_time, LGSF_FUNC_TIME_STEP);
    if (inhibit_door_open_on.getStateOut()) {
        inhibit_mask |= (1 << 4);
    } else {
        if (inhibit_door_open_off.getStateOut() == false) {
            inhibit_mask &= ~(1 << 4);
        } else {
            // do nothing.
        }
    }

    signal_res = (vse_out.driver_belt_switch_st == 0);
    (void)inhibit_drv_belt_fasten_on.onDelay(signal_res, inhibit_cal.k_driver_belt_fasten_enter_time, LGSF_FUNC_TIME_STEP);
    (void)inhibit_drv_belt_fasten_off.offDelay(signal_res, inhibit_cal.k_driver_belt_fasten_exit_time, LGSF_FUNC_TIME_STEP);
    if (inhibit_drv_belt_fasten_on.getStateOut()) {
        inhibit_mask |= (1 << 5);
    } else {
        if (inhibit_drv_belt_fasten_off.getStateOut() == false) {
            inhibit_mask &= ~(1 << 5);
        } else {
            // do nothing.
        }
    }

    signal_res = (vse_out.vdc_active_st == 1);
    (void)inhibit_vdc_atv_on.onDelay(signal_res, inhibit_cal.k_vdc_atv_enter_time, LGSF_FUNC_TIME_STEP);
    (void)inhibit_vdc_atv_off.offDelay(signal_res, inhibit_cal.k_vdc_atv_exit_time, LGSF_FUNC_TIME_STEP);
    if (inhibit_vdc_atv_on.getStateOut()) {
        inhibit_mask |= (1 << 6);
    } else {
        if (inhibit_vdc_atv_off.getStateOut() == false) {
            inhibit_mask &= ~(1 << 6);
        } else {
            // do nothing.
        }
    }

    signal_res = (vse_out.tcs_active_st == 1);
    (void)inhibit_tcs_atv_on.onDelay(signal_res, inhibit_cal.k_tcs_atv_enter_time, LGSF_FUNC_TIME_STEP);
    (void)inhibit_tcs_atv_off.offDelay(signal_res, inhibit_cal.k_tcs_atv_exit_time, LGSF_FUNC_TIME_STEP);
    if (inhibit_tcs_atv_on.getStateOut()) {
        inhibit_mask |= (1 << 7);
    } else {
        if (inhibit_tcs_atv_off.getStateOut() == false) {
            inhibit_mask &= ~(1 << 7);
        } else {
            // do nothing.
        }
    }

    signal_res = (vse_out.hdc_active_st == 1);
    (void)inhibit_hdc_atv_on.onDelay(signal_res, inhibit_cal.k_hdc_atv_enter_time, LGSF_FUNC_TIME_STEP);
    (void)inhibit_hdc_atv_off.offDelay(signal_res, inhibit_cal.k_hdc_atv_exit_time, LGSF_FUNC_TIME_STEP);
    if (inhibit_hdc_atv_on.getStateOut()) {
        inhibit_mask |= (1 << 8);
    } else {
        if (inhibit_hdc_atv_off.getStateOut() == false) {
            inhibit_mask &= ~(1 << 8);
        } else {
            // do nothing.
        }
    }

    signal_res = (vse_out.hdc_active_st == 1);
    (void)inhibit_tcs_off_on.onDelay(signal_res, inhibit_cal.k_tcs_off_enter_time, LGSF_FUNC_TIME_STEP);
    (void)inhibit_tcs_off_off.offDelay(signal_res, inhibit_cal.k_tcs_off_exit_time, LGSF_FUNC_TIME_STEP);
    if (inhibit_tcs_off_on.getStateOut()) {
        inhibit_mask |= (1 << 9);
    } else {
        if (inhibit_tcs_off_off.getStateOut() == false) {
            inhibit_mask &= ~(1 << 9);
        } else {
            // do nothing.
        }
    }

    signal_res = (vse_out.actual_gear != 3);
    (void)inhibit_gear_on.onDelay(signal_res, inhibit_cal.k_tcs_off_enter_time, LGSF_FUNC_TIME_STEP);
    (void)inhibit_gear_off.offDelay(signal_res, inhibit_cal.k_tcs_off_exit_time, LGSF_FUNC_TIME_STEP);
    if (inhibit_gear_on.getStateOut()) {
        inhibit_mask |= (1 << 10);
    } else {
        if (inhibit_gear_off.getStateOut() == false) {
            inhibit_mask &= ~(1 << 10);
        } else {
            // do nothing.
        }
    }
    aeb_inhibit = (inhibit_mask > 0);
    fcw_inhibit = (inhibit_mask > 0);
}

void LgSfFunction::FaultEvaluator(const AsVseOut &vse_out) {
    //[TODO]
    aeb_fault = false;
    fcw_fault = false;
}

void LgSfFunction::OutPutMapping(const GlobalConfig &config) {
    lgsf_out_.tgt.id      = prev_obs.fus_trkID;
    lgsf_out_.tgt.type    = 0;
    lgsf_out_.tgt.source  = 0;
    lgsf_out_.tgt.posx    = prev_obs.long_posn;
    lgsf_out_.tgt.posy    = prev_obs.lat_posn;
    lgsf_out_.tgt.spdx    = prev_obs.long_vel;
    lgsf_out_.tgt.spdy    = prev_obs.lat_vel;
    lgsf_out_.tgt.accelx  = prev_obs.long_accel;
    lgsf_out_.tgt.accely  = prev_obs.lat_accel;
    lgsf_out_.tgt.heading = prev_obs.heading;
    lgsf_out_.tgt.ttc     = prev_obs.ttr;
    if (config.k_aeb_enable && !config.k_use_shadowmode) {
        lgsf_out_.aeb_tar_dec = aeb_req_dec;
        lgsf_out_.hold_type   = hold_req ? 2 : 0;
        lgsf_out_.aeb_req     = static_cast<OnOffStatus>(aeb_state_ == AebStatus::AEB_Active || aeb_state_ == AebStatus::EBA_Active);
        // temp logic
        if (lgsf_out_.aeb_req == OnOffStatus::Active) {
            // if(hold_req){

            // }
            //        lgsf_out_.aeb_tar_dec = math::Clamp(aeb_req_dec, -10.0F, 0.0F);
            lgsf_out_.aeb_tar_dec = -9.8F;
        } else {
            lgsf_out_.aeb_tar_dec = 0.0F;
        }
        lgsf_out_.awb_req       = static_cast<OnOffStatus>(0);
        lgsf_out_.prefill_req   = static_cast<OnOffStatus>(0);
        lgsf_out_.aba_req       = static_cast<OnOffStatus>(0);
        lgsf_out_.belt_req      = static_cast<OnOffStatus>(0);
        lgsf_out_.aeb_status    = aeb_state_;
        lgsf_out_.fcw_status    = fcw_state_;
        lgsf_out_.warn_level    = static_cast<WarnLevel>(0);
        lgsf_out_.aba_level     = 0;
        lgsf_out_.awb_level     = 0;
        lgsf_out_.aeb_req_valid = 1;
    } else if (!config.k_aeb_enable || config.k_use_shadowmode) {
        lgsf_out_.aeb_tar_dec   = 0;
        lgsf_out_.hold_type     = 0;
        lgsf_out_.aeb_req       = OnOffStatus::NotActive;
        lgsf_out_.aeb_tar_dec   = 0.0F;
        lgsf_out_.awb_req       = static_cast<OnOffStatus>(0);
        lgsf_out_.prefill_req   = static_cast<OnOffStatus>(0);
        lgsf_out_.aba_req       = static_cast<OnOffStatus>(0);
        lgsf_out_.belt_req      = static_cast<OnOffStatus>(0);
        lgsf_out_.aeb_status    = AebStatus::AEB_Inhibit;
        lgsf_out_.fcw_status    = FcwStatus::FCW_Inhibit;
        lgsf_out_.warn_level    = static_cast<WarnLevel>(0);
        lgsf_out_.aba_level     = 0;
        lgsf_out_.awb_level     = 0;
        lgsf_out_.aeb_req_valid = 0;
    }
    lgsf_out_.shadow_mode += uint8(aeb_state_ == AebStatus::AEB_Active ? AsShadowMode::AEB : AsShadowMode::UNKNOWN);
    if (aeb_state_ == AebStatus::AEB_Active) {
        lgsf_out_.shadow_mode = 2;
    } else if (aeb_state_ == AebStatus::EBA_Active) {
        lgsf_out_.shadow_mode = 4;
    } else {
        lgsf_out_.shadow_mode = 0;
    }
}

} // namespace longsafe
} // namespace active_safety
