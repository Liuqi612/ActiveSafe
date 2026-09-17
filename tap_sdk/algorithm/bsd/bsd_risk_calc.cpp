#include "bsd_function.h"
namespace active_safety {
namespace bsd {

void BsdFunction::CalcTTc(const VehicleConfig &veh_config, BsdObsData &obs_data) {
    obs_data.m_ttc = m_bsd_cal.k_bsd_default_ttc;
    float objDist = 0.0f;

    if (obs_data.m_curvi_long_vel_rel_filt < m_eps) {
        obs_data.m_ttc = m_bsd_cal.k_bsd_default_ttc;
    } else {
        objDist = -(obs_data.m_obs->long_posn + (0.5f * obs_data.m_obs->length) + veh_config.k_host_length - veh_config.k_dist_to_rear_axle) +
            m_bsd_cal.k_cvw_ttc_long_calculation_offset;
        obs_data.m_ttc = math::SafeDivide(objDist, obs_data.m_curvi_long_vel_rel_filt);
    }
}

void BsdFunction::UpdateFallbackState(BsdObsData &obs_data) {
    float relVelThreshold = -fabs(m_bsd_cal.k_bsw_stag_vel);

    switch (obs_data.m_fallback_state) {
        case FallbackState::FALLBACK_ACTIVE: {
            relVelThreshold = relVelThreshold + fabs(m_bsd_cal.k_bsw_stag_vel_hys);
            if (obs_data.m_curvi_long_vel_rel_filt > relVelThreshold) {
                obs_data.m_fallback_state = FallbackState::FALLBACK_PREVIOUS;
            }
            break;
        }

        case FallbackState::FALLBACK_PREVIOUS: {
            relVelThreshold = relVelThreshold - fabs(m_bsd_cal.k_bsw_stag_vel_hys_breaking);
            if (obs_data.m_curvi_long_vel_rel_filt < relVelThreshold) {
                obs_data.m_fallback_state = FallbackState::FALLBACK_ACTIVE;
            } else {
                obs_data.m_fallback_state = FallbackState::FALLBACK_NONE;
            }
            break;
        }

        case FallbackState::FALLBACK_NONE:
        default:
            if (obs_data.m_curvi_long_vel_rel_filt < relVelThreshold) {
                obs_data.m_fallback_state = FallbackState::FALLBACK_ACTIVE;
            } else {
                obs_data.m_fallback_state = FallbackState::FALLBACK_NONE;
            }
            break;
    }
}

void BsdFunction::UpdateCriticalObsInBswZone(const AsVseOut &vse_out, BsdObsData &obs_data) {

    if (obs_data.m_obs_vld_type != ObsValidType::OBS_BSW && obs_data.m_obs_vld_type != ObsValidType::OBS_BSW_AND_CVW) {
        obs_data.m_bsw_in_zone = false;
        obs_data.m_bsw_in_zone_cnt = 0;
        return;
    }

    obs_data.m_bsw_in_zone = math::Geometry::IsPolyOverlapSAT(obs_data.m_bsw_polygon, obs_data.m_polygon);
    if (obs_data.m_bsw_in_zone == false) {
        obs_data.m_bsw_in_zone_cnt = 0;
        return;
    }

    UpdateFallbackState(obs_data);
    if (obs_data.m_obs->status == TrackStatus::UPDATED) {
        obs_data.m_bsw_in_zone_cnt++;
    }
    bool countCheckPassed = false;
    bool fbackCheckPassed = false;
    int side = static_cast<int>(obs_data.m_side);

    countCheckPassed = (obs_data.m_bsw_in_zone_cnt >= m_bsd_cal.k_bsw_min_cycles) || (obs_data.m_obs->age >= m_bsd_cal.k_bsw_alert_track_age) ||
        m_prev_data[side].prev_bsw_active || (m_bsd_cal.k_bsw_uses_cvw_alert_state_enabled && obs_data.m_is_prev_cvw_active_obj);

    fbackCheckPassed = (FallbackState::FALLBACK_NONE == obs_data.m_fallback_state) || (FallbackState::FALLBACK_PREVIOUS == obs_data.m_fallback_state);

    if (m_bsd_cal.k_bsd_enable_obj_in_ego_lane_check) {
        float effective_lane_width = m_bsd_cal.k_bsd_default_lane_width * m_bsd_cal.k_bsw_effective_lane_width_factor;
        if (fabs(obs_data.m_curvi_lat_posn_filt) < (0.5f * effective_lane_width)) {
            obs_data.m_bsw_in_ego_lane = true;
        } else {
            obs_data.m_bsw_in_ego_lane = false;
        }
    } else {
        obs_data.m_bsw_in_ego_lane = false;
    }
    if ((countCheckPassed && fbackCheckPassed && (false == obs_data.m_bsw_in_ego_lane))) {
        if (m_bsw_alert_fusId[side] <= 0 || obs_data.m_is_prev_bsw_active_obj) {
            m_bsw_alert_active[side] = true;
            m_bsw_alert_fusId[side] = obs_data.m_obs->fus_trkID;
        }
    }

    bool rear_curvature_radius_bsw_check = false;

    if (obs_data.m_obs->curvi_long_vel_rel <= m_bsd_cal.k_bsw_curvature_radius_rel_speed[0] &&
        vse_out.rear_curvature_radius > m_bsd_cal.k_bsw_curvature_radius_val[0]) {
        rear_curvature_radius_bsw_check = true;
    } else if (obs_data.m_obs->curvi_long_vel_rel > m_bsd_cal.k_bsw_curvature_radius_rel_speed[0] &&
               obs_data.m_obs->curvi_long_vel_rel <= m_bsd_cal.k_bsw_curvature_radius_rel_speed[1] &&
               vse_out.rear_curvature_radius > m_bsd_cal.k_bsw_curvature_radius_val[1]) {
        rear_curvature_radius_bsw_check = true;
    } else if (obs_data.m_obs->curvi_long_vel_rel < m_bsd_cal.k_bsw_curvature_radius_rel_speed[1] &&
               vse_out.rear_curvature_radius > m_bsd_cal.k_bsw_curvature_radius_val[2]) {
        rear_curvature_radius_bsw_check = true;
    }

    if (obs_data.m_obs->curvi_long_vel_rel < m_bsd_cal.k_bsw_min_longvel_deactive || !rear_curvature_radius_bsw_check) {
        m_bsw_alert_active[side] = false;
    }

    // 回灌调试：记录本侧 BSW 候选目标逐条判据（优先记录成为报警的目标）
    if (m_bsd_cal.k_bsd_debug_log_enable && (!m_debug.bsw[side].valid || obs_data.m_obs->fus_trkID == m_bsw_alert_fusId[side])) {
        BsdBswTargetDebug &dbg = m_debug.bsw[side];
        dbg.valid = true;
        dbg.fus_trkID = obs_data.m_obs->fus_trkID;
        dbg.in_zone = obs_data.m_bsw_in_zone;
        dbg.in_zone_cnt = obs_data.m_bsw_in_zone_cnt;
        dbg.fallback_state = static_cast<int>(obs_data.m_fallback_state);
        dbg.count_check = countCheckPassed;
        dbg.fback_check = fbackCheckPassed;
        dbg.in_ego_lane = obs_data.m_bsw_in_ego_lane;
        dbg.curvature_radius_check = rear_curvature_radius_bsw_check;
        dbg.curvi_long_vel_rel = obs_data.m_obs->curvi_long_vel_rel;
        dbg.curvi_lat_posn_filt = obs_data.m_curvi_lat_posn_filt;
    }
}

void BsdFunction::UpdateCriticalObsInCvwZone(const AsVseOut &vse_out, BsdObsData &obs_data) {

    if (obs_data.m_obs_vld_type != ObsValidType::OBS_CVW && obs_data.m_obs_vld_type != ObsValidType::OBS_BSW_AND_CVW) {
        obs_data.m_cvw_in_zone = false;
        obs_data.m_cvw_in_zone_cnt = 0;
        return;
    }

    if (obs_data.m_ttc <= 0.0f || obs_data.m_ttc >= m_bsd_cal.k_cvw_candidate_ttc) {
        obs_data.m_cvw_in_zone_cnt = 0;
        return;
    }

    obs_data.m_cvw_in_zone = math::Geometry::IsPolyOverlapSAT(obs_data.m_cvw_polygon, obs_data.m_polygon);
    if (obs_data.m_cvw_in_zone) {
        if (obs_data.m_obs->status == TrackStatus::UPDATED) {
            obs_data.m_cvw_in_zone_cnt++;
            if (fabs(obs_data.m_obs->curvi_long_posn) > m_bsd_cal.k_cvw_distance_count_twice) {
                obs_data.m_cvw_in_zone_cnt++;
            }
        }
    } else {
        obs_data.m_cvw_in_zone_cnt = 0;
    }
    int side = static_cast<int>(obs_data.m_side);

    bool checkMatureInZone = false;
    if (obs_data.m_cvw_in_zone_cnt > m_bsd_cal.k_cvw_min_cycles || obs_data.m_is_prev_cvw_active_obj) {
        checkMatureInZone = true;
    }

    float effectiveCenter = obs_data.m_obs->curvi_long_posn;
    if (obs_data.m_is_prev_cvw_active_obj) {
        effectiveCenter = effectiveCenter + m_bsd_cal.k_cvw_closest_x_hys;
    }
    bool checkObjEffectiveCenter = effectiveCenter > m_closest_cvw_obs_dist[side];

    if (m_bsd_cal.k_bsd_enable_obj_in_ego_lane_check) {
        float effective_lane_width = m_bsd_cal.k_bsd_default_lane_width * m_bsd_cal.k_cvw_effective_lane_width_factor;
        if (fabs(obs_data.m_curvi_lat_posn_filt) < (0.5f * effective_lane_width)) {
            obs_data.m_cvw_in_ego_lane = true;
        } else {
            obs_data.m_cvw_in_ego_lane = false;
        }
    } else {
        obs_data.m_cvw_in_ego_lane = false;
    }

    if (checkMatureInZone && checkObjEffectiveCenter && obs_data.m_ttc <= m_bsd_cal.k_cvw_active_ttc && obs_data.m_cvw_in_ego_lane == false) {
        m_cvw_alert_active[side] = true;
        m_cvw_alert_fusId[side] = obs_data.m_obs->fus_trkID;
        m_closest_cvw_obs_dist[side] = effectiveCenter;
    }
    if (obs_data.m_ttc > m_bsd_cal.k_cvw_deactive_ttc && (m_bsd_out.bsd_warn_left == 1 || m_bsd_out.bsd_warn_left == 2) && side == 0) {
        m_cvw_alert_active[side] = false;
    }
    if (obs_data.m_ttc > m_bsd_cal.k_cvw_deactive_ttc && (m_bsd_out.bsd_warn_right == 1 || m_bsd_out.bsd_warn_right == 2) && side == 1) {
        m_cvw_alert_active[side] = false;
    }
    bool rear_curvature_radius_cvw_check = false;

    if (obs_data.m_obs->curvi_long_vel_rel <= m_bsd_cal.k_cvw_curvature_radius_rel_speed[0] &&
        vse_out.rear_curvature_radius > m_bsd_cal.k_cvw_curvature_radius_val[0] && obs_data.m_ttc <= m_bsd_cal.k_cvw_curvature_radius_ttc[0]) {
        rear_curvature_radius_cvw_check = true;
    } else if (obs_data.m_obs->curvi_long_vel_rel > m_bsd_cal.k_cvw_curvature_radius_rel_speed[0] &&
               obs_data.m_obs->curvi_long_vel_rel <= m_bsd_cal.k_cvw_curvature_radius_rel_speed[1] &&
               vse_out.rear_curvature_radius > m_bsd_cal.k_cvw_curvature_radius_val[1] && obs_data.m_ttc <= m_bsd_cal.k_cvw_curvature_radius_ttc[1]) {
        rear_curvature_radius_cvw_check = true;
    } else if (obs_data.m_obs->curvi_long_vel_rel < m_bsd_cal.k_cvw_curvature_radius_rel_speed[1] &&
               vse_out.rear_curvature_radius > m_bsd_cal.k_cvw_curvature_radius_val[2] && obs_data.m_ttc <= m_bsd_cal.k_cvw_curvature_radius_ttc[2]) {
        rear_curvature_radius_cvw_check = true;
    }

    if (!rear_curvature_radius_cvw_check) {
        m_cvw_alert_active[side] = false;
    }

    // 回灌调试：记录本侧 CVW 候选目标逐条判据（优先记录成为报警的目标）
    if (m_bsd_cal.k_bsd_debug_log_enable && (!m_debug.cvw[side].valid || obs_data.m_obs->fus_trkID == m_cvw_alert_fusId[side])) {
        BsdCvwTargetDebug &dbg = m_debug.cvw[side];
        dbg.valid = true;
        dbg.fus_trkID = obs_data.m_obs->fus_trkID;
        dbg.in_zone = obs_data.m_cvw_in_zone;
        dbg.in_zone_cnt = obs_data.m_cvw_in_zone_cnt;
        dbg.ttc = obs_data.m_ttc;
        dbg.mature_in_zone = checkMatureInZone;
        dbg.obj_effective_center_check = checkObjEffectiveCenter;
        dbg.active_ttc_check = (obs_data.m_ttc <= m_bsd_cal.k_cvw_active_ttc);
        dbg.in_ego_lane = obs_data.m_cvw_in_ego_lane;
        dbg.curvature_radius_check = rear_curvature_radius_cvw_check;
        dbg.curvi_lat_posn_filt = obs_data.m_curvi_lat_posn_filt;
    }
}

void BsdFunction::WarnJudgement() {
    bool bswAlertflag = false;
    int bswAlertObjIndex[2] = {-1, -1};
    for (int side = 0; side < 2; side++) {
        m_prev_data[side].prev_bsw_alert_obs_id = m_bsw_obs_id[side];
        m_prev_data[side].prev_bsw_active = m_bsw_alert_active[side];
        m_prev_data[side].prev_cvw_alert_obs_id = m_cvw_obs_id[side];
        m_prev_data[side].prev_cvw_active = m_cvw_alert_active[side];

    }

}

} // namespace bsd
} // namespace active_safety
