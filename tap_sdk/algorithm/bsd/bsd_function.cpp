#include "bsd_function.h"
namespace active_safety {
namespace bsd {
BsdFunction::BsdFunction() {
}
BsdFunction::~BsdFunction() {
}
void BsdFunction::Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list) {
    f_bsw_alert_active_ = {false, false};
    bsw_alert_fusId_ = {-1, -1};
    closest_cvw_obs_dist_ = {-1000.0f, -1000.0f};
    f_cvw_alert_active_ = {false, false};
    cvw_alert_fusId_ = {-1, -1};

    for (std::size_t idx = 0; idx < kMaxNormalObject; ++idx) {
        obs_data_[idx].obs = obs_list[idx];
        GetObjClass(obs_data_[idx]);
        FilterCurviDataAndCheckSide(obs_data_[idx]);
        // cal cvw prev active object.
        int side = static_cast<int>(obs_data_[idx].side);
        bool alertActive = false;
        if ((prev_data_[side].f_prev_cvw_active) && (obs_data_[idx].obs->fus_trkID == prev_data_[side].prev_cvw_alert_obs_id)) {
            alertActive = true;
        }
        obs_data_[idx].f_is_prev_cvw_active_obj = alertActive;
        // cal bsw prev active object.
        alertActive = false;
        if ((prev_data_[side].f_prev_bsw_active) && (obs_data_[idx].obs->fus_trkID == prev_data_[side].prev_bsw_alert_obs_id)) {
            alertActive = true;
        }
        obs_data_[idx].f_is_prev_bsw_active_obj = alertActive;
        CalcObsPolygon(obs_data_[idx]);
        CalcValidZone(vse_out.config, obs_data_[idx]);
        CalcTTc(vse_out.config, obs_data_[idx]);
        // Check valid critical bsw obs.
        UpdateCriticalObsInBswZone(vse_out, obs_data_[idx]);
        // Check valid critical cvw obs.
        UpdateCriticalObsInCvwZone(vse_out, obs_data_[idx]);
    }
    WarnJudgement();
    StateMachine(config, vse_out);
}

void BsdFunction::UpdateCriticalObsInBswZone(const AsVseOut &vse_out, BsdObsData &obs_data) {
    if (obs_data.obs_vld_type != ObsValidType::OBS_BSW && obs_data.obs_vld_type != ObsValidType::OBS_BSW_AND_CVW) {
        obs_data.f_bsw_in_zone = false;
        obs_data.bsw_in_zone_cnt = 0;
        return;
    }

    obs_data.f_bsw_in_zone = math::Geometry::IsPolyOverlapSAT(obs_data.bsw_polygon, obs_data.polygon);
    if (obs_data.f_bsw_in_zone == false) {
        obs_data.bsw_in_zone_cnt = 0;
        return;
    }

    UpdateFallbackState(obs_data);
    if (obs_data.obs->status == TrackStatus::UPDATED) {
        obs_data.bsw_in_zone_cnt++;
    }
    bool countCheckPassed = false;
    bool fbackCheckPassed = false;
    int side = static_cast<int>(obs_data.side);

    countCheckPassed = (obs_data.bsw_in_zone_cnt >= bsd_cal_.k_bsw_min_cycles) || (obs_data.obs->age >= bsd_cal_.k_bsw_alert_track_age) ||
        prev_data_[side].f_prev_bsw_active || (bsd_cal_.k_bsw_uses_cvw_alert_state_enabled && obs_data.f_is_prev_cvw_active_obj);

    fbackCheckPassed = (FallbackState::FALLBACK_NONE == obs_data.fallback_state) || (FallbackState::FALLBACK_PREVIOUS == obs_data.fallback_state);

    if (bsd_cal_.k_lcda_enable_obj_in_ego_lane_check) // 1U
    {
        float effective_lane_width = bsd_cal_.k_lcda_default_lane_width * bsd_cal_.k_bsw_effective_lane_width_factor;
        if (fabs(obs_data.curvi_lat_posn_filt) < (0.5f * effective_lane_width)) {
            obs_data.f_bsw_in_ego_lane = true;
        } else {
            obs_data.f_bsw_in_ego_lane = false;
        }
    } else {
        obs_data.f_bsw_in_ego_lane = false;
    }
    if ((countCheckPassed && fbackCheckPassed && (false == obs_data.f_bsw_in_ego_lane))) {
        if (bsw_alert_fusId_[side] <= 0 || obs_data.f_is_prev_bsw_active_obj) {
            f_bsw_alert_active_[side] = true;
            bsw_alert_fusId_[side] = obs_data.obs->fus_trkID;
        }
    }
}

void BsdFunction::UpdateCriticalObsInCvwZone(const AsVseOut &vse_out, BsdObsData &obs_data) {
    if (obs_data.obs_vld_type != ObsValidType::OBS_CVW && obs_data.obs_vld_type != ObsValidType::OBS_BSW_AND_CVW) {
        obs_data.f_cvw_in_zone = false;
        obs_data.cvw_in_zone_cnt = 0;
        return;
    }

    if (obs_data.ttc <= 0.0f || obs_data.ttc >= bsd_cal_.k_cvw_candidate_ttc) {
        obs_data.cvw_in_zone_cnt = 0;
        return;
    }

    obs_data.f_cvw_in_zone = math::Geometry::IsPolyOverlapSAT(obs_data.cvw_polygon, obs_data.polygon);
    if (obs_data.f_cvw_in_zone) {
        if (obs_data.obs->status == TrackStatus::UPDATED) {
            obs_data.cvw_in_zone_cnt++;
            if (fabs(obs_data.obs->curvi_long_posn) > bsd_cal_.k_cvw_distance_count_twice) {
                obs_data.cvw_in_zone_cnt++;
            }
        }
    } else {
        obs_data.cvw_in_zone_cnt = 0;
    }
    int side = static_cast<int>(obs_data.side);

    bool checkMatureInZone = false;
    if (obs_data.cvw_in_zone_cnt > bsd_cal_.k_cvw_min_cycles || obs_data.f_is_prev_cvw_active_obj) {
        checkMatureInZone = true;
    }

    float effectiveCenter = obs_data.obs->curvi_long_posn;
    if (obs_data.f_is_prev_cvw_active_obj) {
        effectiveCenter = effectiveCenter + bsd_cal_.k_cvw_closest_x_hys; // 0.5
    }
    bool checkObjEffectiveCenter = effectiveCenter > closest_cvw_obs_dist_[side];

    if (bsd_cal_.k_lcda_enable_obj_in_ego_lane_check) // 1U
    {
        float effective_lane_width = bsd_cal_.k_lcda_default_lane_width * bsd_cal_.k_cvw_effective_lane_width_factor;
        if (fabs(obs_data.curvi_lat_posn_filt) < (0.5f * effective_lane_width)) {
            obs_data.f_cvw_in_ego_lane = true;
        } else {
            obs_data.f_cvw_in_ego_lane = false;
        }
    } else {
        obs_data.f_cvw_in_ego_lane = false;
    }

    if (checkMatureInZone && checkObjEffectiveCenter && obs_data.ttc < 3.5f && obs_data.f_cvw_in_ego_lane == false) {
        f_cvw_alert_active_[side] = true;
        cvw_alert_fusId_[side] = obs_data.obs->fus_trkID;
        closest_cvw_obs_dist_[side] = effectiveCenter;
    }
}

void BsdFunction::WarnJudgement() {
    bool bswAlertflag = false;
    int bswAlertObjIndex[2] = {-1, -1};

    for (int side = 0; side < 2; side++) {
        bswAlertflag = f_bsw_alert_active_[side];

        if (f_bsw_alert_active_[side]) {
            /* Increment the BSW Alert hold counter */
            prev_data_[side].bsw_hold_counter++;
            bswAlertObjIndex[side] = bsw_alert_fusId_[side];
        } else if (prev_data_[side].f_prev_bsw_active && (prev_data_[side].bsw_hold_counter <= bsd_cal_.k_lcda_hold_cycles)) {
            /* If there is no alert for this cycle, then check if the alert from the
               previous cycle needs to be held */
            prev_data_[side].bsw_hold_counter++;
            bswAlertflag = true;
            bswAlertObjIndex[side] = prev_data_[side].prev_bsw_alert_obs_id;
        }

        if (bswAlertflag) {
            bsw_level_[side] = WarnLevel::LEVEL_1;
            bsw_obs_id_[side] = bswAlertObjIndex[side];
        } else {
            prev_data_[side].bsw_hold_counter = 0;
            bsw_level_[side] = WarnLevel::NO_REQUEST;
            bsw_obs_id_[side] = -1;
        }

        prev_data_[side].prev_bsw_alert_obs_id = bsw_obs_id_[side];
        prev_data_[side].f_prev_bsw_active = (WarnLevel::LEVEL_1 == bsw_level_[side] || WarnLevel::LEVEL_2 == bsw_level_[side]);
    }

    // bool cvwAlertflag = false;
    // int cvwAlertObjIndex[2] = {-1, -1};

    for (int side = 0; side < 2; side++) {
        // cvwAlertflag = f_cvw_alert_active_[side];

        if (f_cvw_alert_active_[side]) {
            cvw_level_[side] = WarnLevel::LEVEL_1;
            cvw_obs_id_[side] = cvw_alert_fusId_[side];
            prev_data_[side].cvw_hold_counter++;
        } else if (prev_data_[side].f_prev_cvw_active && (prev_data_[side].cvw_hold_counter <= bsd_cal_.k_lcda_hold_cycles)) {
            prev_data_[side].cvw_hold_counter++;
            // cvwAlertflag = true;
            // cvwAlertObjIndex[side] = prev_data_[side].prev_cvw_alert_obj_index;
        } else {
            prev_data_[side].cvw_hold_counter = 0;
            cvw_level_[side] = WarnLevel::NO_REQUEST;
            cvw_obs_id_[side] = -1;
        }
        prev_data_[side].prev_cvw_alert_obs_id = cvw_obs_id_[side];
        prev_data_[side].f_prev_cvw_active = (WarnLevel::LEVEL_1 == cvw_level_[side] || WarnLevel::LEVEL_2 == cvw_level_[side]);
    }
}

void BsdFunction::UpdateFallbackState(BsdObsData &obs_data) {

    float relVelThreshold = -fabs(bsd_cal_.k_bsw_stag_vel); //-4.1667

    switch (obs_data.fallback_state) {
        case FallbackState::FALLBACK_ACTIVE: {
            /* If the obj accelerates enough, it will be classified as an object that
             * was previously falling back */
            relVelThreshold = relVelThreshold + fabs(bsd_cal_.k_bsw_stag_vel_hys); // 0.5

            if (obs_data.curvi_long_vel_rel_filt > relVelThreshold) {
                obs_data.fallback_state = FallbackState::FALLBACK_PREVIOUS;
            } else {
                /* No change  - state remains as FALLBACK_ACTIVE */
            }
            break;
        }

        case FallbackState::FALLBACK_PREVIOUS: {
            /* If target brakes and slows downs enough, it goes into the fallback active
             * state again */
            relVelThreshold = relVelThreshold - fabs(bsd_cal_.k_bsw_stag_vel_hys_breaking); // 0.5
            if (obs_data.curvi_long_vel_rel_filt < relVelThreshold) {
                obs_data.fallback_state = FallbackState::FALLBACK_ACTIVE;
            } else {
                obs_data.fallback_state = FallbackState::FALLBACK_NONE;
            }
            break;
        }

        case FallbackState::FALLBACK_NONE:

        default:
            if (obs_data.curvi_long_vel_rel_filt < relVelThreshold) {
                /* Object is going much slower than the vse_out vehicle i.e. vse_out is overtaking
                 * and obj is falling back */
                obs_data.fallback_state = FallbackState::FALLBACK_ACTIVE;
            } else {
                obs_data.fallback_state = FallbackState::FALLBACK_NONE;
            }

            break;
    }
}

void BsdFunction::FilterCurviDataAndCheckSide(BsdObsData &obs_data) {
    if (ObsValidType::OBS_NONE == obs_data.obs_vld_type) {
        obs_data.curvi_long_vel_rel_filt = m_inf;
        obs_data.curvi_lat_posn_filt = m_inf;
    } else {
        if (obs_data.curvi_long_vel_rel_filt < m_inf - 1.0f) {
            obs_data.curvi_long_vel_rel_filt =
                math::LowPassFilter(obs_data.curvi_long_vel_rel_filt, obs_data.obs->curvi_long_vel_rel, bsd_cal_.k_lcda_exp_avg_filter_constant);
            obs_data.curvi_lat_posn_filt =
                math::LowPassFilter(obs_data.curvi_lat_posn_filt, obs_data.obs->curvi_lat_posn, bsd_cal_.k_lcda_exp_avg_filter_constant);
        } else {
            obs_data.curvi_long_vel_rel_filt = obs_data.obs->curvi_long_vel_rel;
            obs_data.curvi_lat_posn_filt = obs_data.obs->curvi_lat_posn;
        }
    }
    if (obs_data.curvi_lat_posn_filt < 0) {
        obs_data.side = ObsSide::Right;
    } else {
        obs_data.side = ObsSide::Left;
    }
}

void BsdFunction::CalcTTc(const VehicleConfig &veh_config, BsdObsData &obs_data) {
    obs_data.ttc = 25.0;
    float objDist = 0.0f;

    if (obs_data.curvi_long_vel_rel_filt < 1e-10) {
        obs_data.ttc = 25.0;
    } else {
        /* Calcuate the object distance of the front bumper of object from the rear
         * bumper of the vse_out vehicle */
        objDist = -(obs_data.obs->long_posn + (0.5f * obs_data.obs->length) + veh_config.k_host_length - veh_config.k_dist_to_rear_axle) +
            bsd_cal_.k_cvw_ttc_long_calculation_offset;

        /* Calculate the ttc */
        obs_data.ttc = math::SafeDivide(objDist, obs_data.curvi_long_vel_rel_filt);
    }
}

void BsdFunction::CalcObsPolygon(BsdObsData &obs_data) {
    float objHalfWidthSinAng = 0.5f * obs_data.obs->width * sinf(obs_data.obs->curvi_heading);
    float objHalfWidthCosAng = 0.5f * obs_data.obs->width * cosf(obs_data.obs->curvi_heading);
    float objHalfLengthCosAng = 0.5f * obs_data.obs->length * cosf(obs_data.obs->curvi_heading);
    float objHalfLengthSinAng = 0.5f * obs_data.obs->length * sinf(obs_data.obs->curvi_heading);
    obs_data.polygon.clear();
    obs_data.polygon.point_list.emplace_back(obs_data.obs->curvi_long_posn + objHalfLengthCosAng - objHalfWidthSinAng,
                                             obs_data.obs->curvi_lat_posn + objHalfLengthSinAng + objHalfWidthCosAng);

    obs_data.polygon.point_list.emplace_back(obs_data.obs->curvi_long_posn + objHalfLengthCosAng + objHalfWidthSinAng,
                                             obs_data.obs->curvi_lat_posn + objHalfLengthSinAng - objHalfWidthCosAng);

    obs_data.polygon.point_list.emplace_back(obs_data.obs->curvi_long_posn - objHalfLengthCosAng + objHalfWidthSinAng,
                                             obs_data.obs->curvi_lat_posn - objHalfLengthSinAng - objHalfWidthCosAng);

    obs_data.polygon.point_list.emplace_back(obs_data.obs->curvi_long_posn - objHalfLengthCosAng - objHalfWidthSinAng,
                                             obs_data.obs->curvi_lat_posn - objHalfLengthSinAng + objHalfWidthCosAng);
}

void BsdFunction::CalcValidZone(const VehicleConfig &config, BsdObsData &obs_data) {
    obs_data.bsw_polygon.point_list.clear();
    obs_data.cvw_polygon.point_list.clear();

    float bsw_longhys = 0.0f;
    float bsw_lathys = 0.0f;
    if (obs_data.f_bsw_in_zone) {
        bsw_longhys = bsd_cal_.k_lcda_bsw_zone_hys_x;
        bsw_lathys = bsd_cal_.k_lcda_bsw_zone_hys_y;
    }

    float half_width = 0.5f * config.k_host_width;

    float dist_to_front_axle = config.k_dist_to_rear_axle - bsd_cal_.k_lcda_front_axle_to_front_bumper;
    // --- BSW Polygon ---
    // 1. left_top

    obs_data.bsw_polygon.point_list.emplace_back(bsd_cal_.k_lcda_origin_bsw_zone_x[0] + dist_to_front_axle + bsw_longhys,
                                                 half_width + bsd_cal_.k_lcda_origin_bsw_zone_y[0] + bsw_lathys);
    // 2. left_bottom
    obs_data.bsw_polygon.point_list.emplace_back(bsd_cal_.k_lcda_origin_bsw_zone_x[1] + dist_to_front_axle - bsw_longhys,
                                                 half_width + bsd_cal_.k_lcda_origin_bsw_zone_y[1] + bsw_lathys);
    // 3. right_bottom
    obs_data.bsw_polygon.point_list.emplace_back(bsd_cal_.k_lcda_origin_bsw_zone_x[2] + dist_to_front_axle - bsw_longhys,
                                                 half_width + bsd_cal_.k_lcda_origin_bsw_zone_y[2] - bsw_lathys);
    // 4. right_top
    obs_data.bsw_polygon.point_list.emplace_back(bsd_cal_.k_lcda_origin_bsw_zone_x[3] + dist_to_front_axle + bsw_longhys,
                                                 half_width + bsd_cal_.k_lcda_origin_bsw_zone_y[3] - bsw_lathys);

    // --- CVW Polygon ---
    float cvw_longhys = 0.0f;
    float cvw_lathys = 0.0f;
    if (obs_data.f_cvw_in_zone) {
        cvw_longhys = bsd_cal_.k_lcda_cvw_zone_hys_x;
        cvw_lathys = bsd_cal_.k_lcda_cvw_zone_hys_y;
    }

    float dist_to_rear_bumper = config.k_host_length - config.k_dist_to_rear_axle;
    float cvw_far_x_thres = bsd_cal_.k_lcda_cvw_max_zone_thres + dist_to_rear_bumper;
    cvw_far_x_thres *= -1.0f;
    // 1. left_top
    obs_data.cvw_polygon.point_list.emplace_back(bsd_cal_.k_lcda_origin_bsw_zone_x[1] + dist_to_front_axle + cvw_longhys,
                                                 half_width + bsd_cal_.k_lcda_origin_bsw_zone_y[1] + cvw_lathys);
    // 2. left_bottom
    obs_data.cvw_polygon.point_list.emplace_back(cvw_far_x_thres - cvw_longhys, half_width + bsd_cal_.k_lcda_origin_bsw_zone_y[1] + cvw_lathys);
    // 3. right_bottom
    obs_data.cvw_polygon.point_list.emplace_back(cvw_far_x_thres - cvw_longhys, half_width + bsd_cal_.k_lcda_origin_bsw_zone_y[2] - cvw_lathys);
    // 4. right_top
    obs_data.cvw_polygon.point_list.emplace_back(bsd_cal_.k_lcda_origin_bsw_zone_x[2] + dist_to_front_axle - cvw_longhys,
                                                 half_width + bsd_cal_.k_lcda_origin_bsw_zone_y[2] - cvw_lathys);

    // Side handling (negate Y for Right side)
    if (obs_data.side == ObsSide::Right) {
        for (auto &pt : obs_data.bsw_polygon.point_list) {
            pt.y *= -1.0f;
        }
        for (auto &pt : obs_data.cvw_polygon.point_list) {
            pt.y *= -1.0f;
        }
    }
}

void BsdFunction::GetObjClass(BsdObsData &obs_data) {
    CheckMotion(obs_data);

    bool objIsRelevant = IsObjectRelevant(obs_data);
    bool objIsBsw = IsValidBSWObj(obs_data);
    bool objIsCvw = IsValidCVWObj(obs_data);
    if (objIsRelevant && objIsBsw && objIsCvw) {
        obs_data.obs_vld_type = ObsValidType::OBS_BSW_AND_CVW;
    } else if (objIsRelevant && objIsBsw) {
        obs_data.obs_vld_type = ObsValidType::OBS_BSW;
    } else if (objIsRelevant && objIsCvw) {
        obs_data.obs_vld_type = ObsValidType::OBS_CVW;
    } else {
        obs_data.obs_vld_type = ObsValidType::OBS_NONE;
    }
}

void BsdFunction::CheckMotion(BsdObsData &obs_data) {
    if (obs_data.obs->speed < 0.9f) {
        obs_data.f_stationary = true;
    } else {
        obs_data.f_stationary = false;
    }
}

bool BsdFunction::IsObjectRelevant(const BsdObsData &obs_data) {
    if ((obs_data.obs->age >= bsd_cal_.k_lcda_min_track_age) && (obs_data.f_stationary == false) &&
        (fabs(obs_data.obs->long_posn) < fabs(bsd_cal_.k_lcda_max_range)) && (obs_data.obs->long_vel >= bsd_cal_.k_lcda_min_longvel)) {
        return true;
    }
    return false;
}

bool BsdFunction::IsValidBSWObj(const BsdObsData &obs_data) {
    bool objIsBSW = false;

    if (((obs_data.obs->status == TrackStatus::UPDATED || obs_data.obs->status == TrackStatus::COASTED)) &&
        (fabs(obs_data.obs->heading) < (bsd_cal_.k_bsw_max_heading_abs)) && (obs_data.obs->long_vel > bsd_cal_.k_bsw_min_obj_long_vel)) {
        objIsBSW = true;
    } else {
        objIsBSW = false;
    }

    return objIsBSW;
}

bool BsdFunction::IsValidCVWObj(const BsdObsData &obs_data) {
    bool objIsCVW = false;

    if (((obs_data.obs->status == TrackStatus::UPDATED || obs_data.obs->status == TrackStatus::COASTED)) &&
        (fabs(obs_data.obs->curvi_heading) < bsd_cal_.k_cvw_max_heading) && (obs_data.obs->long_vel > bsd_cal_.k_cvw_min_obj_long_vel)) {
        objIsCVW = true;
    } else {
        objIsCVW = false;
    }

    return objIsCVW;
}

void BsdFunction::StateMachine(const GlobalConfig &config, const AsVseOut &vse_out) {
    // Check bsd left
    bool bsd_left_warn = (bsw_level_[0] > WarnLevel::NO_REQUEST);
    bool bsd_right_warn = (bsw_level_[1] > WarnLevel::NO_REQUEST);
    bool bsd_warn = (bsd_left_warn || bsd_right_warn);
    if (bsd_active_ && !bsd_warn) {
        // 如果上一帧激活，这一帧不满足激活条件，则滞回bsd_hold_active_time_时间
        if (bsd_hold_active_time_ > bsd_cal_.k_lcda_step_time) {
            bsd_hold_active_time_ -= bsd_cal_.k_lcda_step_time;
            bsd_warn = true;
        } else {
            bsd_hold_active_time_ = 0;
        }
    }
    bool lcw_left_warn_1 = (cvw_level_[0] > WarnLevel::NO_REQUEST);
    bool lcw_right_warn_1 = (cvw_level_[1] > WarnLevel::NO_REQUEST);
    // 打转向进入二级报警
    bool lcw_left_warn_2 = (lcw_left_warn_1 && vse_out.turn_light_switch_pos == 1);
    bool lcw_right_warn_2 = (lcw_right_warn_1 && vse_out.turn_light_switch_pos == 3);
    // LCW报警等级确认
    bool lcw_warn_level_1 = (lcw_left_warn_1 || lcw_right_warn_1);
    bool lcw_warn_level_2 = (lcw_left_warn_2 || lcw_right_warn_2);
    // 功能是否关闭:开关判断
    lcda_mode_cond_.state_off = !(vse_out.bsd_switch == 1 || vse_out.bsd_switch == 2);
    // 功能是否故障：待故障输入
    lcda_mode_cond_.state_fault = false;
    // 车速合理性滞回
    if (host_speed_enable) {
        host_speed_enable = !(vse_out.speed < bsd_cal_.k_lcda_min_enable_host_speed_hys || vse_out.speed > bsd_cal_.k_lcda_max_enable_host_speed_hys);
    } else {
        host_speed_enable = (bsd_cal_.k_lcda_min_enable_host_speed < vse_out.speed && vse_out.speed < bsd_cal_.k_lcda_max_enable_host_speed);
    }
    // 功能是否被抑制:车速过高/低、档位非D档
    lcda_mode_cond_.state_inhibit = (!host_speed_enable || vse_out.actual_gear != 3);
    // 功能是否激活:
    lcda_mode_cond_.state_active = (bsd_warn || lcw_warn_level_1 || lcw_warn_level_2);
    lcda_mode_cond_.off2inhibit = (lcda_mode_cond_.state_off == false && lcda_mode_cond_.state_fault == false);
    lcda_mode_cond_.fault2inhibit = (lcda_mode_cond_.state_off == false && lcda_mode_cond_.state_fault == false);
    lcda_mode_cond_.inhibit2standby = (lcda_mode_cond_.state_inhibit == false);
    lcda_mode_cond_.inhibit2active = (lcda_mode_cond_.state_inhibit == false && lcda_mode_cond_.state_active == true);
    lcda_mode_cond_.standby2active = (lcda_mode_cond_.state_inhibit == false && lcda_mode_cond_.state_active == true);
    lcda_mode_cond_.active2standby = (lcda_mode_cond_.state_inhibit == false && lcda_mode_cond_.state_active == false);
    // 设置状态机条件:BSD和LCW用同一个
    lcda_mode_context_.setCondition(lcda_mode_cond_);
    // 更新状态机
    lcda_mode_.update(lcda_mode_context_);
    // 根据状态机输出记录激活信号
    if (lcda_mode_.getCurrentSubState() == math::ModeState::ACTIVE) {
        bsd_active_ = bsd_warn ? true : false;
        if (bsd_left_warn || bsd_right_warn) {
            bsd_hold_active_time_ = bsd_cal_.k_lcda_bsd_min_warn_time;
        }
        lcw_active_ = (lcw_warn_level_1 || lcw_warn_level_2);
    } else {
        bsd_active_ = false;
        bsd_hold_active_time_ = 0;
        lcw_active_ = false;
    }
    //输出激活信号
    memset(&bsd_out_, 0, sizeof(bsd_out_));
    //输出状态机.
    switch (lcda_mode_.getCurrentSubState()) {
        case math::ModeState::OFF: {
            bsd_out_.state = BsdState::OFF;
            break;
        }
        case math::ModeState::FAULT: {
            bsd_out_.state = BsdState::FAULT;
            break;
        }
        case math::ModeState::ON:
        case math::ModeState::INHIBIT: {
            bsd_out_.state = BsdState::INHIBIT;
            break;
        }
        case math::ModeState::STANDBY: {
            bsd_out_.state = BsdState::STANDBY;
            break;
        }
        case math::ModeState::ACTIVE: {
            bsd_out_.state = BsdState::ACTIVE;
            break;
        }
        default: {
            bsd_out_.state = BsdState::INHIBIT;
            break;
        }
    }
    //报警标志位
    // bsd_out_.bsc_sound = static_cast<OnOffStatus>(bsd_out_.bsd_warn_left || bsd_out_.bsd_warn_right);
    //报警等级
    bsd_out_.bsd_warn_left = (bsd_active_ && bsd_left_warn);
    if (bsd_out_.bsd_warn_left == 1 && vse_out.turn_light_switch_pos == 1) {
        bsd_out_.bsd_warn_left = 2;
    }
    bsd_out_.bsd_warn_right = (bsd_active_ && bsd_right_warn);
    if (bsd_out_.bsd_warn_right == 1 && vse_out.turn_light_switch_pos == 3) {
        bsd_out_.bsd_warn_right = 2;
    }
    if (lcw_active_) {
        if (lcw_left_warn_1) {
            bsd_out_.lca_warn_left = 1; // Level_1
        }
        if (lcw_left_warn_2) {
            bsd_out_.lca_warn_left = 2; // Level_2
        }
        if (lcw_right_warn_1) {
            bsd_out_.lca_warn_right = 1; // Level_1
        }
        if (lcw_right_warn_2) {
            bsd_out_.lca_warn_right = 2; // Level_2
        }
    } else {
        bsd_out_.lca_warn_left = 0;
        bsd_out_.lca_warn_right = 0;
    }
    //开关信息
    switch (vse_out.bsd_switch) {
        case 1:
            bsd_out_.switch_req = 2;
            break;
        case 2:
            bsd_out_.switch_req = 3;
            break;
        default:
            bsd_out_.switch_req = 1;
            break;
    }
    //适配DF接口
    if (bsd_out_.bsd_warn_left == 1 || bsd_out_.lca_warn_left == 1) {
        bsd_out_.bsd_warn_left = 1;
        bsd_out_.lca_warn_left = 1;
    }
    if (bsd_out_.bsd_warn_left == 2 || bsd_out_.lca_warn_left == 2) {
        bsd_out_.bsd_warn_left = 2;
        bsd_out_.lca_warn_left = 2;
        bsd_out_.bsc_sound = OnOffStatus::Active;
    }
    if (bsd_out_.bsd_warn_right == 1 || bsd_out_.lca_warn_right == 1) {
        bsd_out_.bsd_warn_right = 1;
        bsd_out_.lca_warn_right = 1;
    }
    if (bsd_out_.bsd_warn_right == 2 || bsd_out_.lca_warn_right == 2) {
        bsd_out_.bsd_warn_right = 2;
        bsd_out_.lca_warn_right = 2;
        bsd_out_.bsc_sound = OnOffStatus::Active;
    }
    //填写目标信息
    for (const BsdObsData &obs_data : obs_data_) {
        if (obs_data.obs->fus_trkID <= 0) {
            continue;
        }
        if (bsw_alert_fusId_[0] > 0 && bsw_alert_fusId_[0] == obs_data.obs->fus_trkID) {
            FillTargetInfo(obs_data, bsd_out_.left_tgt_bsd);
        }
        if (bsw_alert_fusId_[1] > 0 && bsw_alert_fusId_[1] == obs_data.obs->fus_trkID) {
            FillTargetInfo(obs_data, bsd_out_.right_tgt_bsd);
        }
        if (cvw_alert_fusId_[0] > 0 && cvw_alert_fusId_[0] == obs_data.obs->fus_trkID) {
            FillTargetInfo(obs_data, bsd_out_.left_tgt_lca);
        }
        if (cvw_alert_fusId_[1] > 0 && cvw_alert_fusId_[1] == obs_data.obs->fus_trkID) {
            FillTargetInfo(obs_data, bsd_out_.right_tgt_lca);
        }
    }
    if (config.k_use_shadowmode || !config.k_bsd_enable) {
        bsd_out_.bsc_sound = OnOffStatus::NotActive;
        bsd_out_.lca_warn_left = 0;
        bsd_out_.lca_warn_right = 0;
        bsd_out_.bsd_warn_left = 0;
        bsd_out_.bsd_warn_right = 0;
    }
}

void BsdFunction::FillTargetInfo(const BsdObsData &obs_data, AsTargetInfo_T &tgt_info) {
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

} // namespace bsd
} // namespace active_safety
