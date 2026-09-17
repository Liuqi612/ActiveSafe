#include "bsd_function.h"
namespace active_safety {
namespace bsd {

void BsdFunction::CheckMotion(BsdObsData &obs_data) {
    if (obs_data.m_obs->speed < m_bsd_cal.k_bsd_stationary_speed_thres) {
        obs_data.m_stationary = true;
    } else {
        obs_data.m_stationary = false;
    }
}

bool BsdFunction::IsObjectRelevant(const BsdObsData &obs_data) {
    if ((obs_data.m_obs->age >= m_bsd_cal.k_bsd_min_track_age) && (obs_data.m_stationary == false) &&
        (fabs(obs_data.m_obs->long_posn) < fabs(m_bsd_cal.k_bsd_max_range))) {
        return true;
    }
    return false;
}

bool BsdFunction::IsValidBSWObj(const BsdObsData &obs_data) {
    bool objIsBSW = false;

    if (((obs_data.m_obs->status == TrackStatus::UPDATED || obs_data.m_obs->status == TrackStatus::COASTED)) &&
        (fabs(obs_data.m_obs->heading) < (m_bsd_cal.k_bsw_max_heading_abs)) && (obs_data.m_obs->long_vel > m_bsd_cal.k_bsw_min_obj_long_vel) &&
        (obs_data.m_obs->long_vel >= m_bsd_cal.k_bsw_min_longvel_active)) {
        objIsBSW = true;
    }

    return objIsBSW;
}

bool BsdFunction::IsValidCVWObj(const BsdObsData &obs_data) {
    bool objIsCVW = false;

    if (((obs_data.m_obs->status == TrackStatus::UPDATED || obs_data.m_obs->status == TrackStatus::COASTED)) &&
        (fabs(obs_data.m_obs->curvi_heading) < m_bsd_cal.k_cvw_max_heading) && (obs_data.m_obs->long_vel > m_bsd_cal.k_cvw_min_obj_long_vel)) {
        objIsCVW = true;
    }

    return objIsCVW;
}

void BsdFunction::GetObjClass(BsdObsData &obs_data) {
    CheckMotion(obs_data);

    bool objIsRelevant = IsObjectRelevant(obs_data);
    bool objIsBsw = IsValidBSWObj(obs_data);
    bool objIsCvw = IsValidCVWObj(obs_data);
    if (objIsRelevant && objIsBsw && objIsCvw) {
        obs_data.m_obs_vld_type = ObsValidType::OBS_BSW_AND_CVW;
    } else if (objIsRelevant && objIsBsw) {
        obs_data.m_obs_vld_type = ObsValidType::OBS_BSW;
    } else if (objIsRelevant && objIsCvw) {
        obs_data.m_obs_vld_type = ObsValidType::OBS_CVW;
    } else {
        obs_data.m_obs_vld_type = ObsValidType::OBS_NONE;
    }
}

void BsdFunction::FilterCurviDataAndCheckSide(BsdObsData &obs_data) {
    if (ObsValidType::OBS_NONE == obs_data.m_obs_vld_type) {
        obs_data.m_curvi_long_vel_rel_filt = m_inf;
        obs_data.m_curvi_lat_posn_filt = m_inf;
    } else {
        if (obs_data.m_curvi_long_vel_rel_filt < m_inf - m_bsd_cal.k_bsd_filter_init_tolerance) {
            obs_data.m_curvi_long_vel_rel_filt =
                math::LowPassFilter(obs_data.m_curvi_long_vel_rel_filt, obs_data.m_obs->curvi_long_vel_rel, m_bsd_cal.k_bsd_exp_avg_filter_constant);
            obs_data.m_curvi_lat_posn_filt =
                math::LowPassFilter(obs_data.m_curvi_lat_posn_filt, obs_data.m_obs->curvi_lat_posn, m_bsd_cal.k_bsd_exp_avg_filter_constant);
        } else {
            obs_data.m_curvi_long_vel_rel_filt = obs_data.m_obs->curvi_long_vel_rel;
            obs_data.m_curvi_lat_posn_filt = obs_data.m_obs->curvi_lat_posn;
        }
    }
    if (obs_data.m_curvi_lat_posn_filt < 0) {
        obs_data.m_side = ObsSide::Right;
    } else {
        obs_data.m_side = ObsSide::Left;
    }
}

} // namespace bsd
} // namespace active_safety