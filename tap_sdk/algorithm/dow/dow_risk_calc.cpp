#include "dow_function.h"

#include <cmath>
#include <string.h>

namespace active_safety {
namespace dow {

void DowFunction::UpdateCriticalObs(const AsVseOut &vse_out, DowObsData &obs_data) {
    float dirX         = cosf(obs_data.m_obs->heading);
    float dirY         = sinf(obs_data.m_obs->heading);
    float crashLineLon = (obs_data.m_overlap == OverlapType::OVERLAP_REAR_LEFT || obs_data.m_overlap == OverlapType::OVERLAP_REAR_RIGHT)
                             ? m_dow_cal.k_dow_crash_line_long
                             : m_dow_cal.k_dow_ftm_crash_line_long;

    float distToCrash           = math::SafeDivide(crashLineLon - (obs_data.m_reference_point.x - vse_out.config.k_dist_to_rear_axle), dirX);
    obs_data.m_intersec_point_lat = obs_data.m_reference_point.y + (dirY * distToCrash);
    obs_data.m_ttc                = math::SafeDivide(distToCrash, obs_data.m_obs->speed);
    obs_data.m_ttc                = (obs_data.m_ttc > 0.0f) ? obs_data.m_ttc : 0.0f;
    obs_data.m_distance           = distToCrash;

    bool is_obs_alerted = false;
    if (DowObjectSide::EGO_LEFT_SIDE == obs_data.m_location_side) {
    } else if (DowObjectSide::EGO_RIGHT_SIDE == obs_data.m_location_side) {
    } else {
        is_obs_alerted = false;
    }

    float intersection_min[2];
    float intersection_max[2];
    float ttc_max;
    float ftm_intersection_min[2] = {0.0f, 0.0f};
    float ftm_intersection_max[2] = {0.0f, 0.0f};
    float ftm_ttc_max             = 0.0f;

    intersection_min[0] = m_dow_cal.k_dow_intersection_point_lat_critical_level_min;
    intersection_min[1] = m_dow_cal.k_dow_intersection_point_lat_critical_level_min;
    intersection_max[0] = m_dow_cal.k_dow_intersection_point_lat_critical_level_max;
    intersection_max[1] = m_dow_cal.k_dow_intersection_point_lat_critical_level_max;
    ttc_max             = m_dow_cal.k_dow_first_warn_level_ttc_thres;

    if (true == m_dow_cal.k_dow_ftm_enable_flag) {
        ftm_intersection_min[0] = m_dow_cal.k_dow_ftm_intersection_point_lat_critical_level_min;
        ftm_intersection_min[1] = m_dow_cal.k_dow_ftm_intersection_point_lat_critical_level_min;
        ftm_intersection_max[0] = m_dow_cal.k_dow_ftm_intersection_point_lat_critical_level_max;
        ftm_intersection_max[1] = m_dow_cal.k_dow_ftm_intersection_point_lat_critical_level_max;
        ftm_ttc_max             = m_dow_cal.k_dow_ftm_ttc_critical_level_max;
    }

    if (is_obs_alerted) {
        if (TravelEgoDirection::REAR_LEFT_DIRECTION == obs_data.m_direction_relative_to_ego) {
            intersection_min[0] -= m_dow_cal.k_dow_intersection_hysteresis;
            intersection_max[0] += m_dow_cal.k_dow_intersection_hysteresis;
            ttc_max = m_dow_cal.k_dow_first_warn_level_ttc_thres_hys;
        } else if (TravelEgoDirection::REAR_RIGHT_DIRECTION == obs_data.m_direction_relative_to_ego) {
            intersection_min[1] -= m_dow_cal.k_dow_intersection_hysteresis;
            intersection_max[1] += m_dow_cal.k_dow_intersection_hysteresis;
            ttc_max = m_dow_cal.k_dow_first_warn_level_ttc_thres_hys;
        } else if ((true == m_dow_cal.k_dow_ftm_enable_flag) && (TravelEgoDirection::FRONT_LEFT_DIRECTION == obs_data.m_direction_relative_to_ego)) {
            ftm_intersection_min[0] -= m_dow_cal.k_dow_ftm_intersection_hysteresis;
            ftm_intersection_max[0] += m_dow_cal.k_dow_ftm_intersection_hysteresis;
            ftm_ttc_max += m_dow_cal.k_dow_ftm_ttc_hysteresis;
        } else if ((true == m_dow_cal.k_dow_ftm_enable_flag) && (TravelEgoDirection::FRONT_RIGHT_DIRECTION == obs_data.m_direction_relative_to_ego)) {
            ftm_intersection_min[1] -= m_dow_cal.k_dow_ftm_intersection_hysteresis;
            ftm_intersection_max[1] += m_dow_cal.k_dow_ftm_intersection_hysteresis;
            ftm_ttc_max += m_dow_cal.k_dow_ftm_ttc_hysteresis;
        }
    }

    if ((OverlapType::OVERLAP_REAR_LEFT == obs_data.m_overlap) && (obs_data.m_reference_point.y > vse_out.config.k_host_width * 0.5f) &&
        (obs_data.m_intersec_point_lat >= intersection_min[1]) && (obs_data.m_intersec_point_lat <= intersection_max[1])) {
        obs_data.m_direction_relative_to_ego = TravelEgoDirection::REAR_LEFT_DIRECTION;
    } else if ((OverlapType::OVERLAP_REAR_RIGHT == obs_data.m_overlap) && (obs_data.m_reference_point.y < -vse_out.config.k_host_width * 0.5f) &&
               (obs_data.m_intersec_point_lat <= -intersection_min[0]) && (obs_data.m_intersec_point_lat >= -intersection_max[0])) {
        obs_data.m_direction_relative_to_ego = TravelEgoDirection::REAR_RIGHT_DIRECTION;
    } else if ((m_dow_cal.k_dow_ftm_enable_flag) && (OverlapType::OVERLAP_REAR_RIGHT == obs_data.m_overlap) &&
               (obs_data.m_reference_point.y < -vse_out.config.k_host_width * 0.5f) && (obs_data.m_intersec_point_lat <= -ftm_intersection_min[0]) &&
               (obs_data.m_intersec_point_lat >= -ftm_intersection_max[0])) {
        obs_data.m_direction_relative_to_ego = TravelEgoDirection::FRONT_RIGHT_DIRECTION;
    } else if ((m_dow_cal.k_dow_ftm_enable_flag) && (OverlapType::OVERLAP_FRONT_LEFT == obs_data.m_overlap) &&
               (obs_data.m_reference_point.y > vse_out.config.k_host_width * 0.5f) && (obs_data.m_intersec_point_lat >= ftm_intersection_min[1]) &&
               (obs_data.m_intersec_point_lat <= ftm_intersection_max[1])) {
        obs_data.m_direction_relative_to_ego = TravelEgoDirection::FRONT_LEFT_DIRECTION;
    } else {
        obs_data.m_direction_relative_to_ego = TravelEgoDirection::UNDEF_DIRECTION;
    }

    bool ttc_valid  = (obs_data.m_ttc > 0.0f && obs_data.m_ttc <= ttc_max);
    bool dist_valid = (obs_data.m_distance <= m_dow_cal.k_dow_distance_critical_level_max);
    bool dir_valid  = ((TravelEgoDirection::REAR_LEFT_DIRECTION == obs_data.m_direction_relative_to_ego) ||
                      (TravelEgoDirection::REAR_RIGHT_DIRECTION == obs_data.m_direction_relative_to_ego));

    bool front_ttc_valid  = (obs_data.m_ttc > 0.0f && obs_data.m_ttc <= ftm_ttc_max);
    bool front_dist_valid = (obs_data.m_distance <= m_dow_cal.k_dow_ftm_distance_critical_level_max);
    bool front_dir_valid  = ((TravelEgoDirection::FRONT_LEFT_DIRECTION == obs_data.m_direction_relative_to_ego) ||
                            (TravelEgoDirection::FRONT_RIGHT_DIRECTION == obs_data.m_direction_relative_to_ego));

    bool late_check = !((obs_data.m_ttc < m_dow_cal.k_dow_late_check_ttc_min) && (false == obs_data.m_alert));

    // 回灌调试：记录运动学/方向/确认判据(索引由 obs_data 在数组中的位置推得)
    const bool dbg_on   = m_dow_cal.k_dow_debug_log_enable;
    std::size_t dbg_idx = static_cast<std::size_t>(&obs_data - m_obs_data.data());
    DowObjDebug &dbg     = m_debug.obj[dbg_idx];
    if (dbg_on) {
        dbg.direction        = static_cast<int>(obs_data.m_direction_relative_to_ego);
        dbg.ttc              = obs_data.m_ttc;
        dbg.distance         = obs_data.m_distance;
        dbg.intersec_lat     = obs_data.m_intersec_point_lat;
        dbg.ttc_valid        = ttc_valid;
        dbg.dist_valid       = dist_valid;
        dbg.dir_valid        = dir_valid;
        dbg.front_ttc_valid  = front_ttc_valid;
        dbg.front_dist_valid = front_dist_valid;
        dbg.front_dir_valid  = front_dir_valid;
        dbg.late_check       = late_check;
    }

    if (ttc_valid && dist_valid && dir_valid && late_check) {
        if (obs_data.m_cycle_of_alert < m_dow_cal.k_dow_cycle_cnt_max) {
            obs_data.m_cycle_of_alert++;
        }

        if (obs_data.m_cycle_of_alert > m_dow_cal.k_dow_number_cycle_qualify_critical_level) {
            obs_data.m_alert = true;
        }
    } else if (m_dow_cal.k_dow_ftm_enable_flag && front_ttc_valid && front_dist_valid && front_dir_valid && late_check) {
        if (obs_data.m_cycle_of_alert < m_dow_cal.k_dow_cycle_cnt_max) {
            obs_data.m_cycle_of_alert++;
        }

        if (obs_data.m_cycle_of_alert > m_dow_cal.k_dow_number_cycle_qualify_critical_level) {
            obs_data.m_alert = true;
        }
    } else {
        obs_data.m_alert = false;
    }

    // 回灌调试：记录确认周期与最终报警结果
    if (dbg_on) {
        dbg.cycle_of_alert = obs_data.m_cycle_of_alert;
        dbg.alert          = obs_data.m_alert;
    }
}

void DowFunction::FindThreatWarn() {
    float right_lowest_TTC  = m_dow_cal.k_dow_ttc_dist_invalid_init;
    float left_lowest_TTC   = m_dow_cal.k_dow_ttc_dist_invalid_init;
    float right_lowest_dist = m_dow_cal.k_dow_ttc_dist_invalid_init;
    float left_lowest_dist  = m_dow_cal.k_dow_ttc_dist_invalid_init;
    memset(&m_dow_out.left_tgt, 0, sizeof(m_dow_out.left_tgt));
    memset(&m_dow_out.right_tgt, 0, sizeof(m_dow_out.right_tgt));
    for (const auto &obs_data : m_obs_data) {
        if (!obs_data.m_alert) {
            continue;
        }
        if ((obs_data.m_direction_relative_to_ego == TravelEgoDirection::FRONT_LEFT_DIRECTION ||
             obs_data.m_direction_relative_to_ego == TravelEgoDirection::REAR_LEFT_DIRECTION) &&
            obs_data.m_location_side == DowObjectSide::EGO_LEFT_SIDE) {

            if (obs_data.m_ttc < left_lowest_TTC ||
                (fabs(obs_data.m_ttc - left_lowest_TTC) < EQUALS_TOLERANCE && obs_data.m_distance < left_lowest_dist)) {
                FillTargetInfo(obs_data, m_dow_out.left_tgt);
                m_dow_out.warn_left = static_cast<uint32_t>(WarnLevel::LEVEL_1);
            }

        } else if ((obs_data.m_direction_relative_to_ego == TravelEgoDirection::REAR_RIGHT_DIRECTION ||
                    obs_data.m_direction_relative_to_ego == TravelEgoDirection::FRONT_RIGHT_DIRECTION) &&
                   obs_data.m_location_side == DowObjectSide::EGO_RIGHT_SIDE) {

            if (obs_data.m_ttc < right_lowest_TTC ||
                (fabs(obs_data.m_ttc - right_lowest_TTC) < EQUALS_TOLERANCE && obs_data.m_distance < right_lowest_dist)) {
                FillTargetInfo(obs_data, m_dow_out.right_tgt);
                m_dow_out.warn_right = static_cast<uint32_t>(WarnLevel::LEVEL_1);
            }
        }
    }
}

void DowFunction::FillTargetInfo(const DowObsData &obs_data, AsTargetInfo_T &tgt_info) {
    tgt_info.id      = obs_data.m_obs->fus_trkID;
    tgt_info.type    = static_cast<uint32_t>(obs_data.m_obs->object_class);
    tgt_info.source  = static_cast<uint32_t>(obs_data.m_obs->fusion_source);
    tgt_info.posx    = obs_data.m_obs->long_posn;
    tgt_info.posy    = obs_data.m_obs->lat_posn;
    tgt_info.spdx    = obs_data.m_obs->long_vel;
    tgt_info.spdy    = obs_data.m_obs->lat_vel;
    tgt_info.accelx  = obs_data.m_obs->long_accel;
    tgt_info.accely  = obs_data.m_obs->lat_accel;
    tgt_info.heading = obs_data.m_obs->heading;
    tgt_info.ttc     = obs_data.m_ttc;
}

} // namespace dow
} // namespace active_safety
