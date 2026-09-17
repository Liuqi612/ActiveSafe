#include "rcw_function.h"

#include <cmath>

namespace active_safety {
namespace rcw {

void RcwFunction::ResetTargetInfo(AsTargetInfo_T &tgt_info) {
    tgt_info.id = 0;
    tgt_info.type = 0;
    tgt_info.source = 0;
    tgt_info.posx = 0;
    tgt_info.posy = 0;
    tgt_info.spdx = 0;
    tgt_info.spdy = 0;
    tgt_info.accelx = 0;
    tgt_info.accely = 0;
    tgt_info.heading = 0;
    tgt_info.ttc = 0;
}

void RcwFunction::CalPredInpath(const AsVseOut &vse_out, RcwObsData &obs_data) {

    float posnlat_pred = obs_data.obs->lat_posn + obs_data.ttc * obs_data.obs->lat_vel;
    float pred_inpath_lat_thres = 0.5 * m_rcw_cal.k_rcw_lane_filter_width;
    if (m_rcw_tar.obs->fus_trkID == obs_data.obs->fus_trkID) {

        pred_inpath_lat_thres = pred_inpath_lat_thres + m_rcw_cal.k_rcw_pred_inpath_Hysteresis;
    }
    if (fabs(posnlat_pred) < pred_inpath_lat_thres) {
        obs_data.is_pred_inpath = true;
    }
}

void RcwFunction::ObjInPathEvaluator(const AsVseOut &vse_out, RcwObsData &obs_data) {
    obs_data.is_current_inpath = false;
    obs_data.is_pred_inpath = false;

    float curvi_lon_pos = obs_data.obs->curvi_long_posn + (vse_out.config.k_host_length - vse_out.config.k_dist_to_rear_axle);

    float effective_lane_width =
        m_rcw_cal.k_rcw_lane_filter_width - fmin((m_rcw_cal.k_rcw_lane_width_slope * fabs(curvi_lon_pos)), m_rcw_cal.k_rcw_lane_width_offset_max);
    // current inpath
    if (fabs(obs_data.obs->lat_posn) < (0.5f * effective_lane_width)) {

        obs_data.is_current_inpath = true;
        Calculate_TTC(vse_out, obs_data);
        CalPredInpath(vse_out, obs_data);
    }
    obs_data.is_inpath = obs_data.is_current_inpath && obs_data.is_pred_inpath;
    // pred inpath
}

void RcwFunction::IsRcwValidObj(const AsVseOut &vse_out, RcwObsData &obs_data) {

    bool posn_check = false;
    bool obj_status_check = false;
    bool valid_id = false;
    obs_data.is_valid = false;

    if (obs_data.obs->fus_trkID > 0) {
        valid_id = true;
    }

    if (obs_data.obs->status == TrackStatus::UPDATED) {
        obj_status_check = true;
    }

    float curvi_lon_pos = obs_data.obs->curvi_long_posn + (vse_out.config.k_host_length - vse_out.config.k_dist_to_rear_axle);
    if (curvi_lon_pos < m_rcw_cal.k_rcw_posnlgt_max) {
        posn_check = true;
    }

    if (valid_id && obj_status_check && posn_check) {
        obs_data.is_valid = true;
    }
}

bool RcwFunction::CheckObjectInfo(const AsVseOut &vse_out, RcwObsData &obs_data) {

    obs_data.age = obs_data.obs->age;
    // 主目标inpath维持一定时间 is_in_lane确认
    if (m_last_tar_obj_id == obs_data.obs->fus_trkID && obs_data.obs->fus_trkID > 0 && obs_data.is_inpath) {

        obs_data.object_within_lane_counter++;
        if (obs_data.object_within_lane_counter > m_rcw_cal.k_rcw_lane_filter_num_consecutive_cycles) {
            obs_data.is_in_lane = true;
            if (obs_data.object_within_lane_counter > m_rcw_cal.k_rcw_counter_max) {
                obs_data.object_within_lane_counter = m_rcw_cal.k_rcw_counter_max;
            }
        }
    } else {
        obs_data.object_within_lane_counter = 0;
        obs_data.is_in_lane = false;
    }
    // 自车非静止提高相对速度阈值
    if (vse_out.speed < m_rcw_cal.k_rcw_ego_stationary_speed_thres) {
        m_ego_stationary_counter++;
        if (m_ego_stationary_counter > m_rcw_cal.k_rcw_ego_stationary_thd) {
            m_ego_stationary = true;
            m_ego_stationary_counter = fmin(m_ego_stationary_counter, m_rcw_cal.k_rcw_counter_max);
        }
    } else {
        m_ego_stationary_counter = 0;
        m_ego_stationary = false;
    }
    Filter_Object_Heading(vse_out, obs_data);

    float maxApproachAngle = m_rcw_cal.k_rcw_ApproachAngleMax;
    float minRelativeSpeed = m_rcw_cal.k_rcw_RelativeSpeedPreCrashMin;
    if (!m_ego_stationary) {
        minRelativeSpeed = m_rcw_cal.k_rcw_RelativeSpeedPreCrashForMovingMin;
    }
    if (obs_data.is_valid_obj_last_cycle && m_rcw_tar.obs->fus_trkID == obs_data.obs->fus_trkID) {
        maxApproachAngle += m_rcw_cal.k_rcw_ApproachAngleHysteresisMax;
        minRelativeSpeed -= m_rcw_cal.k_rcw_RelativeSpeedPreCrashHysteresisMin;
    }

    bool f_moving_obj = (obs_data.obs->speed >= m_rcw_cal.k_rcw_moving_obj_speed_thres);
    bool f_obj_counter = (obs_data.age > m_rcw_cal.k_rcw_ObjectAgeMin);
    bool f_valid_length = (obs_data.obs->length > m_rcw_cal.k_rcw_min_obj_length);

    bool f_valid_heading = false;
    if (m_rcw_cal.k_rcw_enable_heading_filter) {
        f_valid_heading = fabs(obs_data.filtered_heading) < maxApproachAngle;
    } else {
        f_valid_heading = fabs(obs_data.obs->heading) < maxApproachAngle;
    }

    float rel_vel_long = obs_data.obs->long_vel - vse_out.vcs_long_vel;
    bool f_valid_min_relative_speed = (rel_vel_long > minRelativeSpeed);
    bool f_valid_max_relative_speed = (rel_vel_long < m_rcw_cal.k_rcw_RelativeSpeedPreCrashMax);

    bool f_valid_longpos = (obs_data.obs->long_posn < 0);
    bool f_valid_latpos = (fabsf(obs_data.obs->lat_posn) < 0.5f * vse_out.config.k_host_width);

    bool f_inline = obs_data.is_in_lane;

    f_inline = (f_inline || (m_rcw_cal.k_rcw_apply_lane_filter));

    bool f_valid_obj_width = (obs_data.obs->width < m_rcw_cal.k_rcw_object_width_warn_on_max);

    bool f_valid_x_relative_speed = (fabs(rel_vel_long - obs_data.effective_rel_vel.x) < m_rcw_cal.k_rcw_allowed_rel_vel_long_diff_max);

    bool f_valid_bike_lat_pos = (!obs_data.obs->f_is_bicycle || fabs(obs_data.obs->curvi_lat_posn) < m_rcw_cal.k_rcw_bicycle_lat_pos_thres);

    obs_data.is_valid_obj_last_cycle = (f_moving_obj && f_obj_counter && f_valid_length && f_valid_heading && f_valid_min_relative_speed &&
                                          f_valid_max_relative_speed && f_valid_longpos && f_inline && f_valid_obj_width &&
                                          f_valid_x_relative_speed && f_valid_latpos && !obs_data.obs->f_turning && f_valid_bike_lat_pos);

    // 记录关键目标的各筛选位(等价原分散判断)，供回灌调试定位为何目标未通过筛选
    if (m_rcw_cal.k_rcw_debug_log_enable) {
        RcwTargetDebug &td = m_debug.target;
        td.valid = true;
        td.fus_trkID = obs_data.obs->fus_trkID;
        td.track_id = obs_data.obs->track_id;
        td.heading = obs_data.obs->heading;
        td.filtered_heading = obs_data.filtered_heading;
        td.age = obs_data.age;
        td.rel_vel_long = rel_vel_long;
        td.min_rel_speed = minRelativeSpeed;
        td.max_approach_angle = maxApproachAngle;
        td.ego_stationary = m_ego_stationary;
        td.f_moving_obj = f_moving_obj;
        td.f_obj_counter = f_obj_counter;
        td.f_valid_length = f_valid_length;
        td.f_valid_heading = f_valid_heading;
        td.f_valid_min_rel_speed = f_valid_min_relative_speed;
        td.f_valid_max_rel_speed = f_valid_max_relative_speed;
        td.f_valid_longpos = f_valid_longpos;
        td.f_valid_latpos = f_valid_latpos;
        td.f_inline = f_inline;
        td.f_valid_obj_width = f_valid_obj_width;
        td.f_valid_x_rel_speed = f_valid_x_relative_speed;
        td.f_not_turning = !obs_data.obs->f_turning;
        td.f_valid_bike_lat_pos = f_valid_bike_lat_pos;
        td.is_in_lane = obs_data.is_in_lane;
        td.is_valid_obj_last_cycle = obs_data.is_valid_obj_last_cycle;
    }

    if (m_last_tar_obj_id != obs_data.obs->fus_trkID) {
        m_short_ttc_offdly.Reset();
    }
    m_last_tar_obj_id = obs_data.obs->fus_trkID;

    return obs_data.is_valid_obj_last_cycle;
}

void RcwFunction::Filter_Object_Heading(const AsVseOut &vse_out, RcwObsData &obs_data) {
    float filter_coeff;
    float diff_pos_x, diff_pos_y;

    obs_data.filtered_heading = obs_data.obs->heading;

    if (obs_data.last_object_pos.x < m_rcw_cal.k_rcw_valid_last_pos_thres) {
        diff_pos_x = obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle - obs_data.last_object_pos.x;
        diff_pos_y = obs_data.obs->lat_posn - obs_data.last_object_pos.y;

        if (obs_data.filter_counter < m_rcw_cal.k_rcw_heading_filter_cnt_max) {
            obs_data.filter_counter++;
        }

        filter_coeff = math::SafeDivide(1.0f, (float)obs_data.filter_counter);

        // Lowpass
        obs_data.filtered_diff_pos.x = (1.0f - filter_coeff) * obs_data.last_object_pos_filtered.x + (filter_coeff * diff_pos_x);
        obs_data.filtered_diff_pos.y = (1.0f - filter_coeff) * obs_data.last_object_pos_filtered.y + (filter_coeff * diff_pos_y);

        if (obs_data.filter_counter == m_rcw_cal.k_rcw_heading_filter_cnt_max && m_rcw_cal.k_rcw_enable_pos_diff_rel_vel) {
            obs_data.effective_rel_vel.x = obs_data.filtered_diff_pos.x / m_rcw_cal.k_rcw_step_time;
            obs_data.effective_rel_vel.y = obs_data.filtered_diff_pos.y / m_rcw_cal.k_rcw_step_time;

            if (obs_data.filtered_diff_pos.x > m_rcw_cal.k_rcw_filter_pos_diff_min) {
                obs_data.filtered_heading = std::atan2(obs_data.filtered_diff_pos.y, obs_data.filtered_diff_pos.x);
            }
        } else {
            obs_data.effective_rel_vel.x = obs_data.obs->long_vel - vse_out.vcs_long_vel;
            obs_data.effective_rel_vel.y = obs_data.obs->lat_vel - vse_out.vcs_lat_vel;
        }
    }

    obs_data.last_object_pos.x = obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle;
    obs_data.last_object_pos.y = obs_data.obs->lat_posn;
    obs_data.last_object_pos_filtered.x = obs_data.filtered_diff_pos.x;
    obs_data.last_object_pos_filtered.y = obs_data.filtered_diff_pos.y;
}

void RcwFunction::ResetPersistant(RcwObsData &obs_data) {

    obs_data.age = 0;
    obs_data.is_valid_obj_last_cycle = false;
    if (m_min_dist_idx == -1) {
        obs_data.ttc = m_rcw_cal.k_rcw_default_ttc;
        obs_data.is_inpath = false;
    }
    obs_data.crash_prob_combined = 0.0f;
    obs_data.is_in_lane = false;

    obs_data.filtered_heading = 0.0f;
    obs_data.filtered_diff_pos.x = 0.0f;
    obs_data.filtered_diff_pos.y = 0.0f;
    obs_data.effective_rel_vel.x = 0.0f;
    obs_data.effective_rel_vel.y = 0.0f;
    obs_data.last_object_pos.x = 0.0f;
    obs_data.last_object_pos.y = 0.0f;
    obs_data.last_object_pos_filtered.x = 0.0f;
    obs_data.last_object_pos_filtered.y = 0.0f;
    obs_data.filter_counter = 0;
}
} // namespace rcw
} // namespace active_safety
