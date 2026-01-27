#include "cts_function.h"

namespace active_safety {
namespace cts {
CtsFunction::CtsFunction() {
}
CtsFunction::~CtsFunction() {
}

void CtsFunction::Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list) {
    SetThresData(vse_out);
    CheckCommonInhibit(vse_out);
    // Reset max levels for this cycle
    for (int i = 0; i < CTS_MAX_SIDE; ++i) {
        fcts_info_[i].max_level = 0;
        fcts_info_[i].highest_critical_obs_idx = -1;
        rcts_info_[i].max_level = 0;
        rcts_info_[i].highest_critical_obs_idx = -1;
    }

    for (std::size_t idx = 0; idx < kMaxNormalObject; ++idx) {
        obs_data_[idx].obs = obs_list[idx];
        CheckApproachSide(obs_data_[idx]);
        CalculateTargetCornersPoint(obs_data_[idx]);
        CalculateRelativeVelocity(vse_out, obs_data_[idx]);
        CheckMotion(obs_data_[idx]);
        CheckCTA(vse_out, obs_data_[idx], fcts_thres_, obs_data_[idx].attr[0], fcts_info_);
        //        CheckCTA(vse_out, obs_data_[idx], rcts_thres_, obs_data_[idx].attr[1], rcts_info_);
    }
    // for (std::size_t i = 0; i < fcts_thres_.size(); ++i) {
    //     printf("Front:TTC:%.3f RadDist:%.3f IntMin:%.3f IntMax:%.3f\n", fcts_thres_[i].ttc_thres, fcts_thres_[i].rad_dist_thres,
    //            fcts_thres_[i].inter_sec_min, fcts_thres_[i].inter_sec_max);
    //     // printf("Rear:TTC:%.3f RadDist:%.3f IntMin:%.3f IntMax:%.3f\n", rcts_thres_[i].ttc_thres, rcts_thres_[i].rad_dist_thres,
    //     //        rcts_thres_[i].inter_sec_min, rcts_thres_[i].inter_sec_max);
    // }
    // for (std::size_t i = 0; i < kMaxNormalObject; ++i) {
    //     if (obs_data_[i].obs->fus_trkID != 580) {
    //         continue;
    //     }
    //     printf("Pos:(%.3f,%.3f),Vel:(%.3f,%.3f) Heading:%.3f\n", obs_data_[i].obs->long_posn, obs_data_[i].obs->lat_posn,
    //     obs_data_[i].obs->long_vel,
    //            obs_data_[i].obs->lat_vel, obs_data_[i].obs->heading);
    //     printf("Front:\n");
    //     printf("ttc:%.3f radialDist:%.3f  IntSecX:%.3f  intSecY:%.3f  RefPos(%.3f,%.3f)\n", obs_data_[i].attr[0].ttc,
    //            obs_data_[i].attr[0].radial_distance, obs_data_[i].attr[0].intersect_pt.x, obs_data_[i].attr[0].intersect_pt.y,
    //            obs_data_[i].attr[0].reference_pt.x, obs_data_[i].attr[0].reference_pt.y);

    //     // printf("Rear:\n");
    //     // printf("ttc:%.3f radialDist:%.3f  IntSecX:%.3f  intSecY:%.3f  RefPos(%.3f,%.3f)\n", obs_data_[i].attr[1].ttc,
    //     //        obs_data_[i].attr[1].radial_distance, obs_data_[i].attr[1].intersect_pt.x, obs_data_[i].attr[1].intersect_pt.y,
    //     //        obs_data_[i].attr[1].reference_pt.x, obs_data_[i].attr[1].reference_pt.y);
    // }
    ProcessThreatLevel(fcts_info_, CtsDirection::FRONT);
    //    ProcessThreatLevel(rcts_info_, CtsDirection::REAR);

    CtsDecision(vse_out, config);

    FillOutput(vse_out, config, fcts_info_, front, CtsDirection::FRONT);
    FillOutput(vse_out, config, rcts_info_, rear, CtsDirection::REAR);
}

void CtsFunction::CheckApproachSide(CtsObsData &obs_data) {
    obs_data.approach_side = CTA_APPROACH_UNDEFINED;
    if (obs_data.obs->heading < 0.0f) {
        if (obs_data.obs->lat_posn > 0.0f && obs_data.obs->lat_vel < 0.0f) {
            obs_data.approach_side = CTA_APPROACH_FROM_LEFT;
        }
    } else {
        if (obs_data.obs->lat_posn < 0.0f && obs_data.obs->lat_vel > 0.0f) {
            obs_data.approach_side = CTA_APPROACH_FROM_RIGHT;
        }
    }
}

void CtsFunction::CheckCommonInhibit(const AsVseOut &vse_out) {
    bool f_steer_inhibit = (fabs(vse_out.steerwheelangle) > cts_cal_.k_cts_strangle_inhibit_thrd) ||
        (fabs(vse_out.steerwheelangle_rate) > cts_cal_.k_cts_strangrt_inhibit_thrd) ||
        (fabs(vse_out.rear_curvature) > cts_cal_.k_cts_curvature_inhibit_thrd);

    bool f_pedal_inhibit = (vse_out.brake_pedal_pos > cts_cal_.k_cts_brkpdl_inhibit_thrd) ||
        (vse_out.gas_pedal_pos > cts_cal_.k_cts_accpdl_inhibit_thrd) || (vse_out.gas_pedal_pos_rate > cts_cal_.k_cts_gas_pedal_rate_inhibit_thrd);

    f_common_inhibit = common_inhibit_offdly_.offDelay(f_steer_inhibit || f_pedal_inhibit, cts_cal_.k_cts_common_inhibit_time, CTS_STEP_TIME);
}

void CtsFunction::CtsDecision(const AsVseOut &vse_out, const GlobalConfig &config) {
    FCTAStateMachine(vse_out, config);
    FCTBStateMachine(vse_out, config);
    RCTAStateMachine(vse_out, config);
    RCTBStateMachine(vse_out, config);

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

    memset(&front, 0, sizeof(front));
    memset(&rear, 0, sizeof(rear));

    front.warn_state = map_state(fcta_mode_.getCurrentSubState());
    front.brake_state = map_state(fctb_mode_.getCurrentSubState());
    rear.warn_state = map_state(rcta_mode_.getCurrentSubState());
    rear.brake_state = map_state(rctb_mode_.getCurrentSubState());
}

void CtsFunction::FCTAStateMachine(const AsVseOut &vse_out, const GlobalConfig &config) {
    fcta_release.signalRelease(front.warn_state == CtsState::ACTIVE, cts_cal_.k_cts_alert_time_thrd_max, CTS_STEP_TIME);
    fcta_freezing.featureFreezing(front.warn_state == CtsState::ACTIVE, cts_cal_.k_cta_freezing_time, CTS_STEP_TIME);

    fcta_mode_cond_.state_off = (vse_out.fctb_switch == 0x1);
    fcta_mode_cond_.state_fault = false;

    bool fcta_aeb_available = true;
    bool fcta_standby_entry = ((vse_out.speed >= cts_cal_.k_fcta_min_enable_host_speed) && vse_out.speed <= cts_cal_.k_fcta_max_enable_host_speed) &&
        (vse_out.actual_gear == 3) && fcta_aeb_available;
    bool fcta_inhibit_cond = (vse_out.speed > cts_cal_.k_fcta_max_enable_host_speed_inhibit ||
                              (vse_out.speed <= cts_cal_.k_fcta_min_enable_host_speed_inhibit && front.brake_state == CtsState::INHIBIT)) ||
        (vse_out.actual_gear != 3) || !fcta_aeb_available;

    fcta_mode_cond_.state_inhibit = fcta_inhibit_cond || f_common_inhibit || fcta_freezing.getfeatureFreezing();
    bool fcta_max_time_reached = fcta_release.getSignalRelease();
    bool fcta_active = (fcts_info_[0].cur_level >= cts_cal_.k_cta_min_active_level || fcts_info_[1].cur_level >= cts_cal_.k_cta_min_active_level);
    fcta_mode_cond_.state_active = fcta_active && !fcta_max_time_reached;

    fcta_mode_cond_.off2inhibit = (!fcta_mode_cond_.state_off && !fcta_mode_cond_.state_fault);
    fcta_mode_cond_.fault2inhibit = !fcta_mode_cond_.state_fault;
    fcta_mode_cond_.inhibit2standby = fcta_standby_entry && !fcta_mode_cond_.state_inhibit;
    fcta_mode_cond_.standby2active = fcta_mode_cond_.state_active;
    fcta_mode_cond_.active2standby = !fcta_mode_cond_.state_active && !fcta_inhibit_cond;
    fcta_mode_cond_.active2standby |= fcta_max_time_reached;

    fcta_mode_context_.setCondition(fcta_mode_cond_);
    fcta_mode_.update(fcta_mode_context_);
}

void CtsFunction::FCTBStateMachine(const AsVseOut &vse_out, const GlobalConfig &config) {
    fctb_release.signalRelease(front.brake_state == CtsState::ACTIVE, cts_cal_.k_cts_alert_time_thrd_max, CTS_STEP_TIME);
    fctb_freezing.featureFreezing(front.brake_state == CtsState::ACTIVE, cts_cal_.k_cta_freezing_time, CTS_STEP_TIME);

    fctb_mode_cond_.state_off = (vse_out.fctb_switch == 0x1);
    fctb_mode_cond_.state_fault = false;

    bool fctb_aeb_available = true;
    bool fctb_standby_entry = ((vse_out.speed >= cts_cal_.k_fctb_min_enable_host_speed) && vse_out.speed <= cts_cal_.k_fctb_max_enable_host_speed) &&
        (vse_out.actual_gear == 3) && fctb_aeb_available;
    bool fctb_inhibit_cond = (vse_out.speed > cts_cal_.k_fctb_max_enable_host_speed_inhibit ||
                              (vse_out.speed <= cts_cal_.k_fctb_min_enable_host_speed_inhibit && front.brake_state == CtsState::INHIBIT)) ||
        (vse_out.actual_gear != 3) || !fctb_aeb_available;

    fctb_mode_cond_.state_inhibit = fctb_inhibit_cond || f_common_inhibit || fctb_freezing.getfeatureFreezing();
    bool fctb_max_time_reached = fctb_release.getSignalRelease();
    bool fctb_active = (fcts_info_[0].cur_level >= cts_cal_.k_ctb_min_active_level || fcts_info_[1].cur_level >= cts_cal_.k_ctb_min_active_level);

    // 当 shadow_mode=false 且 ctb_enable=true 时，激活后制动请求要持续发送到自车车速小于0.01之后2s
    bool fctb_keep_active_for_low_speed = false;
    if (!config.k_use_shadowmode && config.k_ctb_enable) {
        bool is_currently_active = (fctb_mode_.getCurrentSubState() == math::ModeState::ACTIVE);
        bool is_low_speed = (fabs(vse_out.speed) < 0.01f);
        bool low_speed_condition = is_currently_active && is_low_speed;
        fctb_low_speed_delay.offDelay(low_speed_condition, 2.0f, CTS_STEP_TIME);
        fctb_keep_active_for_low_speed = fctb_low_speed_delay.getStateOut();
    }

    fctb_mode_cond_.state_active = ((fctb_active || fctb_keep_active_for_low_speed) && !fctb_max_time_reached);

    fctb_mode_cond_.off2inhibit = (!fctb_mode_cond_.state_off && !fctb_mode_cond_.state_fault);
    fctb_mode_cond_.fault2inhibit = !fctb_mode_cond_.state_fault;
    fctb_mode_cond_.inhibit2standby = fctb_standby_entry && !fctb_mode_cond_.state_inhibit;
    fctb_mode_cond_.standby2active = fctb_mode_cond_.state_active;
    fctb_mode_cond_.active2standby = !fctb_mode_cond_.state_active && !fctb_inhibit_cond;
    fctb_mode_cond_.active2standby |= fctb_max_time_reached;

    fctb_mode_context_.setCondition(fctb_mode_cond_);
    fctb_mode_.update(fctb_mode_context_);
}

void CtsFunction::RCTAStateMachine(const AsVseOut &vse_out, const GlobalConfig &config) {
    rcta_release.signalRelease(rear.warn_state == CtsState::ACTIVE, cts_cal_.k_cts_alert_time_thrd_max, CTS_STEP_TIME);
    rcta_freezing.featureFreezing(rear.warn_state == CtsState::ACTIVE, cts_cal_.k_cta_freezing_time, CTS_STEP_TIME);

    rcta_mode_cond_.state_off = (vse_out.rctb_switch == 0x1);
    rcta_mode_cond_.state_fault = false;

    bool rcta_aeb_available = (vse_out.esp_brake_available_st == 0x1);
    bool rcta_standby_entry = (vse_out.speed <= cts_cal_.k_rcta_max_enable_host_speed && vse_out.speed >= cts_cal_.k_rcta_min_enable_host_speed) &&
        (vse_out.actual_gear == 1) && rcta_aeb_available;
    bool rcta_inhibit_cond = (vse_out.speed < cts_cal_.k_rcta_min_enable_host_speed_inhibit ||
                              (vse_out.speed >= cts_cal_.k_rcta_max_enable_host_speed_inhibit && rear.brake_state == CtsState::INHIBIT)) ||
        (vse_out.actual_gear != 1) || !rcta_aeb_available;

    rcta_mode_cond_.state_inhibit = rcta_inhibit_cond || f_common_inhibit || rcta_freezing.getfeatureFreezing();
    bool rcta_any_warn = (rcts_info_[0].cur_level > 0 || rcts_info_[1].cur_level > 0);
    bool rcta_max_time_reached = rcta_release.getSignalRelease();
    rcta_mode_cond_.state_active = rcta_any_warn && !rcta_max_time_reached;

    rcta_mode_cond_.off2inhibit = (!rcta_mode_cond_.state_off && !rcta_mode_cond_.state_fault);
    rcta_mode_cond_.fault2inhibit = !rcta_mode_cond_.state_fault;
    rcta_mode_cond_.inhibit2standby = rcta_standby_entry && !rcta_mode_cond_.state_inhibit;
    rcta_mode_cond_.standby2active = rcta_mode_cond_.state_active;
    rcta_mode_cond_.active2standby = !rcta_mode_cond_.state_active && !rcta_inhibit_cond;
    rcta_mode_cond_.active2standby |= rcta_max_time_reached;

    rcta_mode_context_.setCondition(rcta_mode_cond_);
    rcta_mode_.update(rcta_mode_context_);
}

void CtsFunction::RCTBStateMachine(const AsVseOut &vse_out, const GlobalConfig &config) {
    rctb_release.signalRelease(rear.brake_state == CtsState::ACTIVE, cts_cal_.k_cts_alert_time_thrd_max, CTS_STEP_TIME);
    rctb_freezing.featureFreezing(rear.brake_state == CtsState::ACTIVE, cts_cal_.k_cta_freezing_time, CTS_STEP_TIME);

    rctb_mode_cond_.state_off = (vse_out.rctb_switch == 0x1);
    rctb_mode_cond_.state_fault = false;

    bool rctb_aeb_available = (vse_out.esp_brake_available_st == 0x1);
    bool rctb_standby_entry = (vse_out.speed <= cts_cal_.k_rctb_max_enable_host_speed && vse_out.speed >= cts_cal_.k_rctb_min_enable_host_speed) &&
        (vse_out.actual_gear == 1) && rctb_aeb_available;
    bool rctb_inhibit_cond = (vse_out.speed < cts_cal_.k_rctb_min_enable_host_speed_inhibit ||
                              (vse_out.speed >= cts_cal_.k_rctb_max_enable_host_speed_inhibit && rear.brake_state == CtsState::INHIBIT)) ||
        (vse_out.actual_gear != 1) || !rctb_aeb_available;

    rctb_mode_cond_.state_inhibit = rctb_inhibit_cond || f_common_inhibit || rctb_freezing.getfeatureFreezing();
    bool rctb_any_warn = (rcts_info_[0].cur_level >= cts_cal_.k_ctb_min_active_level || rcts_info_[1].cur_level >= cts_cal_.k_ctb_min_active_level);
    bool rctb_max_time_reached = rctb_release.getSignalRelease();

    // 当 shadow_mode=false 且 ctb_enable=true 时，激活后制动请求要持续发送到自车车速小于0.01之后2s
    bool rctb_keep_active_for_low_speed = false;
    if (!config.k_use_shadowmode && config.k_ctb_enable) {
        bool is_currently_active = (rctb_mode_.getCurrentSubState() == math::ModeState::ACTIVE);
        bool is_low_speed = (fabs(vse_out.speed) < 0.01f);
        bool low_speed_condition = is_currently_active && is_low_speed;
        rctb_low_speed_delay.offDelay(low_speed_condition, 2.0f, CTS_STEP_TIME);
        rctb_keep_active_for_low_speed = rctb_low_speed_delay.getStateOut();
    }

    rctb_mode_cond_.state_active = ((rctb_any_warn || rctb_keep_active_for_low_speed) && !rctb_max_time_reached);

    rctb_mode_cond_.off2inhibit = (!rctb_mode_cond_.state_off && !rctb_mode_cond_.state_fault);
    rctb_mode_cond_.fault2inhibit = !rctb_mode_cond_.state_fault;
    rctb_mode_cond_.inhibit2standby = rctb_standby_entry && !rctb_mode_cond_.state_inhibit;
    rctb_mode_cond_.standby2active = rctb_mode_cond_.state_active;
    rctb_mode_cond_.active2standby = !rctb_mode_cond_.state_active && !rctb_inhibit_cond;
    rctb_mode_cond_.active2standby |= rctb_max_time_reached;

    rctb_mode_context_.setCondition(rctb_mode_cond_);
    rctb_mode_.update(rctb_mode_context_);
}

void CtsFunction::FillOutput(const AsVseOut &vse_out, const GlobalConfig &config, const std::array<WarnInfo, CTS_MAX_SIDE> &warn_infos, CtsOut &out,
                             CtsDirection dir) {
    uint8_t sw = (dir == CtsDirection::FRONT) ? vse_out.fctb_switch : vse_out.rctb_switch;
    switch (sw) {
        case 1:
            out.switch_req = 2;
            break;
        case 2:
            out.switch_req = 3;
            break;
        default:
            out.switch_req = 1;
            break;
    }

    bool warn_can_output = (out.warn_state == CtsState::ACTIVE);
    bool brake_can_output = (out.brake_state == CtsState::ACTIVE);

    for (int side = 0; side < CTS_MAX_SIDE; ++side) {
        const WarnInfo &warn_info = warn_infos[side];
        AsTargetInfo_T &tgt_out = (side == 0) ? out.left_tgt : out.right_tgt;

        if (warn_info.obs_index >= 0 && obs_data_[warn_info.obs_index].obs->fus_trkID == warn_info.obs_fusId) {
            FillTargetInfo(obs_data_[warn_info.obs_index], side, tgt_out);
        }

        if (warn_can_output && warn_info.cur_level > 0) {
            if (side == 0) {
                out.left_warn = OnOffStatus::Active;
                out.sound = OnOffStatus::Active;
            } else {
                out.right_warn = OnOffStatus::Active;
                out.sound = OnOffStatus::Active;
            }
        }
        if ((warn_can_output || brake_can_output) && warn_info.cur_level > 0) {
            if (side == 0) {
                out.collision_dir = CtbCollisionDir::LEFT;
            } else {
                out.collision_dir = CtbCollisionDir::RIGHT;
            }
        }
        if (brake_can_output) {
            out.brake_req_valid = OnOffStatus::Active;
            out.brake_req = OnOffStatus::Active;
            out.brake_dec_req = -8.0f;
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
    tgt_info.ttc = obs_data.attr[side].ttc;
}

void CtsFunction::CheckCTA(const AsVseOut &vse_out, const CtsObsData &obs_data, const std::array<ThresData, CTS_MAX_LEVEL> &thres,
                           ObsAttribute &obs_attr, std::array<WarnInfo, CTS_MAX_SIDE> &warn_info) {
    if (ValidObs(obs_data, warn_info, obs_attr)) {
        if ((warn_info[0].highest_critical_obs_idx == -1 && obs_data.approach_side == CTA_APPROACH_FROM_LEFT) ||
            (warn_info[1].highest_critical_obs_idx == -1 && obs_data.approach_side == CTA_APPROACH_FROM_RIGHT)) {
            warn_info[0].highest_critical_obs_idx = obs_data.obs->track_id - 1;
        }
        CalculateTargetReferencePoint(obs_data, obs_attr);
        CalculateTimeToConflict(vse_out.config, obs_data, obs_attr);
        CalculateIntersecPoint(obs_data.relative_velocity, obs_attr);
        CalculateRadialDistance(vse_out.config, obs_attr);
        CheckObsInZone(vse_out, obs_data, obs_attr);
        CheckAllLevel(vse_out, obs_data, thres, obs_attr, warn_info);
    } else {
        obs_attr.Reset();
    }
}

void CtsFunction::ProcessThreatLevel(std::array<WarnInfo, CTS_MAX_SIDE> &warn_infos, CtsDirection dir) {
    for (std::size_t i = 0; i < CTS_MAX_SIDE; ++i) {
        WarnInfo &warn_info = warn_infos[i];

        if (f_common_inhibit) {
            warn_info.hold_cnt = 0;
            warn_info.obs_fusId = 0;
            warn_info.obs_index = -1;
            warn_info.last_level = 0;
            continue;
        }

        if (warn_info.max_level > warn_info.last_level) {
            warn_info.hold_cnt = 0;
            if (warn_info.highest_critical_obs_idx >= 0) {
                warn_info.last_level = warn_info.max_level;
                warn_info.obs_fusId = obs_data_[warn_info.highest_critical_obs_idx].obs->fus_trkID;
                warn_info.obs_index = obs_data_[warn_info.highest_critical_obs_idx].obs->track_id - 1;
            }
        } else {
            warn_info.hold_cnt = std::min(++warn_info.hold_cnt, 255);
            if (warn_info.hold_cnt > cts_cal_.k_cts_hold_cycles) {
                warn_info.last_level = warn_info.max_level;
                if (warn_info.highest_critical_obs_idx >= 0) {
                    if (warn_info.max_level > 0) {
                        warn_info.hold_cnt = 0;
                        warn_info.obs_fusId = obs_data_[warn_info.highest_critical_obs_idx].obs->fus_trkID;
                        warn_info.obs_index = obs_data_[warn_info.highest_critical_obs_idx].obs->track_id - 1;
                    } else {
                        warn_info.obs_fusId = 0;
                        warn_info.obs_index = -1;
                    }
                }
            } else {
                if (warn_info.highest_critical_obs_idx >= 0 && warn_info.obs_fusId == obs_data_[warn_info.highest_critical_obs_idx].obs->fus_trkID) {
                    int last_level = warn_info.last_level - 1;
                    if (last_level >= 0) {
                        obs_data_[warn_info.highest_critical_obs_idx].attr[static_cast<int>(dir)].counter_val[last_level] = 255;
                    }
                }
            }
        }
        warn_info.cur_level = warn_info.last_level;
    }
}

void CtsFunction::CheckAllLevel(const AsVseOut &vse_out, const CtsObsData &obs_data, const std::array<ThresData, CTS_MAX_LEVEL> &thres,
                                ObsAttribute &obs_attr, std::array<WarnInfo, CTS_MAX_SIDE> &warn_info) {
    int side = 0;
    if (obs_data.approach_side == ObsApproachSide::CTA_APPROACH_FROM_RIGHT) {
        side = 1;
    }
    int &side_idx = warn_info[side].highest_critical_obs_idx;

    int cur_level = 0;

    std::array<ThresData, CTS_MAX_LEVEL> ts = thres;

    for (std::size_t k = 0; k < ts.size(); ++k) {
        if (obs_attr.last_level > ts[k].level) {
            // ApplyLevelThresHyst();
        }
        bool ttc_check = (0.0f < obs_attr.ttc && obs_attr.ttc < ts[k].ttc_thres);
        bool radial_dist_check = obs_attr.radial_distance < ts[k].rad_dist_thres;
        bool inter_x_check = (ts[k].inter_sec_min + vse_out.config.k_dist_to_rear_axle < obs_attr.intersect_pt.x &&
                              obs_attr.intersect_pt.x < ts[k].inter_sec_max + vse_out.config.k_dist_to_rear_axle);
        if (ttc_check && radial_dist_check && inter_x_check) {
            obs_attr.counter_val[k]++;
            if (obs_attr.counter_val[k] > ts[k].above_thres_cnt) {
                cur_level = k + 1;
                if (cur_level > warn_info[side].max_level) {
                    warn_info[side].max_level = cur_level;

                    side_idx = obs_data.obs->track_id - 1;
                } else if (side_idx >= 0 && cur_level == warn_info[side].max_level && obs_attr.ttc <= obs_data_[side_idx].attr[side].ttc) {
                    if (!(fabs(obs_attr.ttc - obs_data_[side_idx].attr[side].ttc) < 0.0001f &&
                          obs_attr.radial_distance >= obs_data_[side_idx].attr[side].radial_distance)) {
                        side_idx = obs_data.obs->track_id - 1;
                    }
                }
            }
        }
    }
    obs_attr.last_level = cur_level;
}

void CtsFunction::CheckMotion(CtsObsData &obs_data) {
    if (obs_data.obs->speed < 0.9f) {
        obs_data.f_stationary = true;
    } else {
        obs_data.f_stationary = false;
    }
    CheckTurning(obs_data);
}

void CtsFunction::CheckTurning(CtsObsData &obs_data) {
    obs_data.f_turning = false;

    const size_t min_history_size = 5;
    if (obs_data.obs->fus_heading.size() < min_history_size) {
        return;
    }

    if (obs_data.obs->speed < 0.5f) {
        return;
    }

    float min_heading = obs_data.obs->fus_heading.get_frame(0);
    float max_heading = min_heading;
    float sum_heading = min_heading;

    for (size_t i = 1; i < obs_data.obs->fus_heading.size(); ++i) {
        float h = obs_data.obs->fus_heading.get_frame(i);
        sum_heading += h;

        float diff_min = std::atan2(std::sin(h - min_heading), std::cos(h - min_heading));
        float diff_max = std::atan2(std::sin(h - max_heading), std::cos(h - max_heading));

        if (diff_min < 0.0f) {
            min_heading = h;
        }
        if (diff_max > 0.0f) {
            max_heading = h;
        }
    }
    float heading_range = std::atan2(std::sin(max_heading - min_heading), std::cos(max_heading - min_heading));
    heading_range = std::abs(heading_range);
    const float heading_range_threshold = 0.2f; // 约 11.5 度

    if (heading_range > heading_range_threshold) {
        obs_data.f_turning = true;
    }
}

bool CtsFunction::ValidObs(const CtsObsData &obs_data, const std::array<WarnInfo, CTS_MAX_SIDE> &warn_info, ObsAttribute &obs_attr) {
    if (obs_data.obs->fus_trkID <= 0) {
        return false;
    }
    bool f_return = true;

    // 1. 滞后处理 (Hysteresis)
    float k_cta_heading_angle_hys = cts_cal_.k_cta_cross_dist_max_lat_angle_diff * cts_cal_.k_cta_rel_warning_hysteresis;
    float min_speed_obj = cts_cal_.k_cta_min_speed;
    float min_lat_approach_spd = cts_cal_.k_cta_min_lateral_approach_speed;

    float min_hdg_obj, max_hdg_obj;
    if (obs_data.approach_side == ObsApproachSide::CTA_APPROACH_FROM_LEFT) {
        min_hdg_obj = cts_cal_.k_cta_cross_dist_max_lat_angle_diff - M_PI;
        max_hdg_obj = -cts_cal_.k_cta_cross_dist_max_lat_angle_diff;
    } else {
        min_hdg_obj = cts_cal_.k_cta_cross_dist_max_lat_angle_diff;
        max_hdg_obj = M_PI - cts_cal_.k_cta_cross_dist_max_lat_angle_diff;
    }

    if (obs_attr.last_level > 0) {
        min_speed_obj -= cts_cal_.k_cta_min_speed_hys;
        min_lat_approach_spd -= min_lat_approach_spd * cts_cal_.k_cta_rel_warning_hysteresis;
        min_hdg_obj -= k_cta_heading_angle_hys;
        max_hdg_obj += k_cta_heading_angle_hys;
    }

    // 静止目标校验
    if (cts_cal_.k_cta_f_check_stationary_signal) {
        f_return &= !obs_data.f_stationary;
    }

    // 生存周期校验
    f_return &= (obs_data.obs->age > cts_cal_.k_cta_min_object_age_in_cycles);

    // 速度校验
    f_return &= (obs_data.obs->speed >= min_speed_obj);

    // 航向角区间校验
    f_return &= (obs_data.obs->heading >= min_hdg_obj && obs_data.obs->heading <= max_hdg_obj);

    // 横向靠近速度校验
    f_return &= (fabs(obs_data.relative_velocity.y) >= min_lat_approach_spd);

    //方向校验
    f_return &= (obs_data.approach_side != CTA_APPROACH_UNDEFINED);

    // 航向角滤波器/角度偏差校验
    f_return &= ((obs_data.obs->speed > cts_cal_.k_cta_object_heading_filter_max_speed_thres) ||
                 (fabs(obs_data.angle_diff) < cts_cal_.k_cta_object_max_angle_diff));

    bool no_overlap_chk = true;
    int side = static_cast<int>(obs_data.approach_side);
    if (side < warn_info.size() && warn_info[side].obs_fusId != obs_data.obs->fus_trkID) {
        for (const Point2D &pt : obs_data.corner_pts) {
            if (fabs(pt.y) < 0.9f) {
                no_overlap_chk = false;
                break;
            }
        }
        if (no_overlap_chk) {
            bool has_left_corner = false;
            bool has_right_corner = false;

            for (int i = 0; i < 4; ++i) {
                int corner_idx = 2 * i;
                const Point2D &pt = obs_data.corner_pts[corner_idx];
                if (pt.y > 0.0f) {
                    has_left_corner = true;
                } else if (pt.y < 0.0f) {
                    has_right_corner = true;
                }
            }

            if (has_left_corner && has_right_corner) {
                no_overlap_chk = false;
            }
        }
    }

    f_return &= no_overlap_chk;

    bool f_turning_in_fov = true;
    if (obs_data.obs->f_is_motor_vehicle && obs_data.f_turning) {
        float azimuth = std::atan2(obs_data.obs->lat_posn, obs_data.obs->long_posn);
        float abs_azimuth = std::abs(azimuth);

        if (abs_azimuth < M_PI / 3.0f) {
            f_turning_in_fov = false;
        }
    }
    f_return &= f_turning_in_fov;

    return f_return;
}

void CtsFunction::SetThresData(const AsVseOut &vse_out) {
    rcts_thres_ = cts_cal_.k_cta_thres_data;
    for (ThresData &td : rcts_thres_) {
        td.inter_sec_min -= vse_out.config.k_host_length;
        td.inter_sec_max -= vse_out.config.k_host_length;
    }

    fcts_thres_ = cts_cal_.k_cta_thres_data;
    for (ThresData &td : fcts_thres_) {
        float tmp = td.inter_sec_min;
        td.inter_sec_min = -td.inter_sec_max;
        td.inter_sec_max = -tmp;
    }
    if (f_fcta_ttc_execution_state) {
        if (fabs(vse_out.speed) > cts_cal_.k_cta_speed_threshold_deactive_fcta_ttc) {
            fcts_thres_[0].ttc_thres -= cts_cal_.k_cta_ttc_threshold_offset_fcta_fast;
            f_fcta_ttc_execution_state = false;
        } else {
            fcts_thres_[0].ttc_thres -= cts_cal_.k_cta_ttc_threshold_offset_fcta_slow;
            f_fcta_ttc_execution_state = true;
        }
    } else {
        if (fabs(vse_out.speed) < cts_cal_.k_cta_speed_threshold_activate_fcta_ttc) {
            fcts_thres_[0].ttc_thres -= cts_cal_.k_cta_ttc_threshold_offset_fcta_slow;
            f_fcta_ttc_execution_state = true;
        } else {
            fcts_thres_[0].ttc_thres -= cts_cal_.k_cta_ttc_threshold_offset_fcta_fast;
            f_fcta_ttc_execution_state = false;
        }
    }
}

void CtsFunction::CalculateTargetCornersPoint(CtsObsData &obs_data) {
    float cos_heading;
    float sin_heading;
    float half_length;
    float half_width;

    float cta_heading = obs_data.obs->heading;
    // Follow C logic for heading adjustment based on velocity
    if (obs_data.obs->lat_vel >= 0.0f) {
        cta_heading = fabs(obs_data.obs->heading);
    } else {
        cta_heading = -1.0f * fabs(obs_data.obs->heading);
    }

    cos_heading = std::cos(cta_heading);
    sin_heading = std::sin(cta_heading);

    half_length = obs_data.obs->length * 0.5f;
    half_width = obs_data.obs->width * 0.5f;

    // Relative corners in object CS
    math::Point2D rel_corners[4];
    rel_corners[0] = {half_length, -half_width};
    rel_corners[1] = {half_length, half_width};
    rel_corners[2] = {-half_length, half_width};
    rel_corners[3] = {-half_length, -half_width};

    // Transform to VCS
    for (int i = 0; i < 4; ++i) {
        obs_data.corner_pts[2 * i].x = obs_data.obs->long_posn + (cos_heading * rel_corners[i].x) - (sin_heading * rel_corners[i].y);
        obs_data.corner_pts[2 * i].y = obs_data.obs->lat_posn + (sin_heading * rel_corners[i].x) + (cos_heading * rel_corners[i].y);
    }

    // Midpoints
    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;

        obs_data.corner_pts[2 * i + 1].x = 0.5f * (obs_data.corner_pts[2 * i].x + obs_data.corner_pts[2 * next].x);
        obs_data.corner_pts[2 * i + 1].y = 0.5f * (obs_data.corner_pts[2 * i].y + obs_data.corner_pts[2 * next].y);
    }
}

void CtsFunction::CalculateTargetReferencePoint(const CtsObsData &obs_data, ObsAttribute &obs_attr) {
    float min_distance_to_ego_rear_bumper = m_inf;
    uint8_t index_min_distance = 0;
    // 1. 顶点（偶数索引）
    // Index 0：右前角 (Front Right) —— 目标的 X 正方向，Y 负方向。
    // Index 2：左前角 (Front Left) —— 目标的 X 正方向，Y 正方向。
    // Index 4：左后角 (Rear Left) —— 目标的 X 负方向，Y 正方向。
    // Index 6：右后角 (Rear Right) —— 目标的 X 负方向，Y 负方向。
    // 2. 边中点（奇数索引）
    // Index 1：前边中点 (Front Mid) —— Index 0 和 2 的中点。
    // Index 3：左边中点 (Left Mid) —— Index 2 和 4 的中点。
    // Index 5：后边中点 (Rear Mid) —— Index 4 和 6 的中点。
    // Index 7：右边中点 (Right Mid) —— Index 6 和 0 的中点。
    for (uint8_t loop_index = 0; loop_index < 8; loop_index++) {
        // Filter points based on direction of movement to avoid tail points
        if ((obs_data.obs->lat_vel <= 0.0f) && (obs_data.corner_pts[index_min_distance].y > obs_data.obs->lat_posn)) {
            continue;
        }
        if ((obs_data.obs->lat_vel >= 0.0f) && (obs_data.corner_pts[index_min_distance].y < obs_data.obs->lat_posn)) {
            continue;
        }

        // x_rear_bumper calculation
        float x_rear_bumper = obs_data.corner_pts[loop_index].x - cts_cal_.k_cta_distance_to_rear_bumper;
        float distance_to_cs_origin =
            std::sqrt((x_rear_bumper * x_rear_bumper) + (obs_data.corner_pts[loop_index].y * obs_data.corner_pts[loop_index].y));

        if (distance_to_cs_origin < min_distance_to_ego_rear_bumper) {
            min_distance_to_ego_rear_bumper = distance_to_cs_origin;
            index_min_distance = loop_index;
        }
    }

    // Default reference point logic
    if (fabs(obs_data.corner_pts[index_min_distance].y) >= cts_cal_.k_cta_min_lat_posn_for_default_ref_point) {
        if (index_min_distance != 2 &&
            ((obs_attr.direction == CtsDirection::REAR && obs_data.approach_side == CTA_APPROACH_FROM_LEFT) ||
             (obs_attr.direction == CtsDirection::FRONT && obs_data.approach_side == CTA_APPROACH_FROM_RIGHT))) {
            index_min_distance = 2;
        } else if (index_min_distance != 0 &&
                   ((obs_attr.direction == CtsDirection::REAR && obs_data.approach_side == CTA_APPROACH_FROM_RIGHT) ||
                    (obs_attr.direction == CtsDirection::FRONT && obs_data.approach_side == CTA_APPROACH_FROM_LEFT))) {
            index_min_distance = 0;
        }
    }

    obs_attr.reference_pt = obs_data.corner_pts[index_min_distance];
    obs_attr.reference_index = index_min_distance + 1;
}

void CtsFunction::CalculateRelativeVelocity(const AsVseOut &vse_out, CtsObsData &obs_data) {
    if (cts_cal_.k_cta_f_use_heading_for_relative_velocity_calculation) {
        obs_data.relative_velocity.x = (obs_data.obs->speed * cosf(obs_data.obs->heading)) - vse_out.vcs_long_vel;
        obs_data.relative_velocity.y = (obs_data.obs->speed * sinf(obs_data.obs->heading));
    } else {
        obs_data.relative_velocity.x = obs_data.obs->long_vel - vse_out.vcs_long_vel;
        obs_data.relative_velocity.y = obs_data.obs->lat_vel - vse_out.vcs_lat_vel;
    }
}

void CtsFunction::CalculateTimeToConflict(const VehicleConfig &veh_config, const CtsObsData &obs_data, ObsAttribute &obs_attr) {

    if (cts_cal_.k_cta_f_calc_ttc_ego_side_enabled) {
        float sign = (obs_data.approach_side == CTA_APPROACH_FROM_LEFT) ? 1.0f : -1.0f;
        obs_attr.ttc = (fabs(obs_data.relative_velocity.y) > 0.001f)
            ? (-(obs_attr.reference_pt.y - sign * 0.5f * veh_config.k_host_width) / obs_data.relative_velocity.y)
            : 60.0f;
    } else {
        obs_attr.ttc = (fabs(obs_data.relative_velocity.y) > 0.001f) ? (-obs_attr.reference_pt.y / obs_data.relative_velocity.y) : 60.0f;
    }
}

void CtsFunction::CalculateIntersecPoint(const math::Point2D &relative_velocity, ObsAttribute &obs_attr) {
    obs_attr.intersect_pt.x = obs_attr.reference_pt.x + (obs_attr.ttc * relative_velocity.x);

    if (fabs(relative_velocity.x) < 0.001f) {
        obs_attr.intersect_pt.y = 1000.0f; // INFINITY
    } else {
        obs_attr.intersect_pt.y = obs_attr.reference_pt.y - ((obs_attr.reference_pt.x / relative_velocity.x) * relative_velocity.y);
    }
}

void CtsFunction::CalculateRadialDistance(const VehicleConfig &veh_config, ObsAttribute &obs_attr) {
    float transition_to_middle_of_bumper;
    if (obs_attr.direction == CtsDirection::FRONT) {
        transition_to_middle_of_bumper = veh_config.k_dist_to_rear_axle;
    } else {
        transition_to_middle_of_bumper = veh_config.k_dist_to_rear_axle - veh_config.k_host_length;
    }
    float dx = obs_attr.reference_pt.x - transition_to_middle_of_bumper;
    float dy = obs_attr.reference_pt.y;

    obs_attr.radial_distance = sqrtf(dx * dx + dy * dy);
}

void CtsFunction::CheckObsInZone(const AsVseOut &vse_out, const CtsObsData &obs_data, ObsAttribute &obs_attr) {

    cta_zone.point_list = cts_cal_.k_cta_area;

    if (obs_attr.direction == CtsDirection::FRONT) {
        for (int i = 0; i < 4; ++i) {
            cta_zone.point_list[i].x = -cta_zone.point_list[i].x - vse_out.config.k_host_length;
        }
    }
    for (int i = 0; i < 4; ++i) {
        cta_zone.point_list[i].x = cta_zone.point_list[i].x + vse_out.config.k_dist_to_rear_axle;
    }

    if (obs_data.approach_side == CTA_APPROACH_FROM_RIGHT) {
        for (int i = 0; i < 4; ++i) {
            cta_zone.point_list[i].y = -cta_zone.point_list[i].y;
        }
    }

    uint32_t n1_idx, n2_idx;
    uint32_t ref_idx = obs_attr.reference_index;
    if (ref_idx == 3 || ref_idx == 5) {
        n1_idx = ref_idx + 1;
        n2_idx = ref_idx + 2;
    } else if (ref_idx == 1 || ref_idx == 7) {
        n1_idx = ((ref_idx - 1 + 6) % 8) + 1;
        n2_idx = ((ref_idx - 1 + 6) % 8) + 2;
    } else {
        n1_idx = ((ref_idx - 1 + 1) % 8) + 1;
        n2_idx = ((ref_idx - 1 + 7) % 8) + 1;
    }

    bool in_poly = math::Geometry::IsPointInPoly(cta_zone, obs_attr.reference_pt) ||
        math::Geometry::IsPointInPoly(cta_zone, obs_data.corner_pts[n1_idx - 1]) ||
        math::Geometry::IsPointInPoly(cta_zone, obs_data.corner_pts[n2_idx - 1]);

    // 3. Trailing Edge Check
    bool f_behind_trailing_edge = IsObjectBehindTrailingEdge(vse_out, obs_data, obs_attr);

    obs_attr.f_in_zone = in_poly && f_behind_trailing_edge;
}

bool CtsFunction::IsObjectBehindTrailingEdge(const AsVseOut &vse_out, const CtsObsData &obs_data, const ObsAttribute &obs_attr) {
    if (!cts_cal_.k_cta_f_use_trailing_edge || obs_attr.direction == CtsDirection::REAR)
        return true;

    float half_ego_width = 0.5f * vse_out.config.k_host_width;

    if (obs_data.approach_side == CTA_APPROACH_FROM_RIGHT) {
        // Right side: Y < 0
        if (obs_data.obs->heading > M_PI_2) { // Moving away from center or steep angle
            return obs_data.corner_pts[6].y < -half_ego_width;
        } else {
            return obs_data.corner_pts[4].y < -half_ego_width;
        }
    } else {
        // Left side: Y > 0
        if (obs_data.obs->heading < -M_PI_2) {
            return obs_data.corner_pts[6].y > half_ego_width;
        } else {
            return obs_data.corner_pts[4].y > half_ego_width;
        }
    }
}

void CtsFunction::ResetObsData(ObsAttribute &obs_attr) {
}

} // namespace cts
} // namespace active_safety
