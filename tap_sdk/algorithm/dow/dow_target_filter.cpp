#include "dow_function.h"

#include <cmath>

namespace active_safety {
namespace dow {

void DowFunction::ResetObjectPersistent(DowObsData &obs_data) {
    obs_data.m_in_zone                   = false;
    obs_data.m_alert                     = false;
    obs_data.m_ttc                       = m_dow_cal.k_dow_ttc_dist_invalid_init;
    obs_data.m_distance                  = m_dow_cal.k_dow_ttc_dist_invalid_init;
    obs_data.m_intersec_point_lat        = 0.0f;
    obs_data.m_overlap                   = OverlapType::NO_OVERLAP;
    obs_data.m_location_side             = DowObjectSide::UNDEF_SIDE;
    obs_data.m_direction_relative_to_ego = TravelEgoDirection::UNDEF_DIRECTION;
}

void DowFunction::CheckMotion(DowObsData &obs_data) {
    if (obs_data.m_obs->speed < m_dow_cal.k_dow_stationary_speed_thres) {
        obs_data.m_stationary = true;
    } else {
        obs_data.m_stationary = false;
    }
}

bool DowFunction::IsObjectValid(DowObsData &obs_data) {
    CheckMotion(obs_data);

    // 回灌调试：记录有效性判据(索引由 obs_data 在数组中的位置推得)
    const bool dbg_on   = m_dow_cal.k_dow_debug_log_enable;
    std::size_t dbg_idx = static_cast<std::size_t>(&obs_data - m_obs_data.data());
    DowObjDebug &dbg     = m_debug.obj[dbg_idx];
    if (dbg_on) {
        dbg.status_ok      = (obs_data.m_obs->status == TrackStatus::UPDATED || obs_data.m_obs->status == TrackStatus::COASTED);
        dbg.not_stationary = !obs_data.m_stationary;
        dbg.width_ok       = (obs_data.m_obs->width > m_dow_cal.k_dow_min_target_width);
        dbg.obj_speed      = obs_data.m_obs->speed;
        dbg.width          = obs_data.m_obs->width;
    }

    if (obs_data.m_obs->fus_trkID > 0 && (obs_data.m_obs->status == TrackStatus::UPDATED || obs_data.m_obs->status == TrackStatus::COASTED) &&
        !obs_data.m_stationary && obs_data.m_obs->width > m_dow_cal.k_dow_min_target_width) {
        if (dbg_on) dbg.valid = true;
        return true;
    }
    if (dbg_on) dbg.valid = false;
    return false;
}

bool DowFunction::IsObjectRelevant(const AsVseOut &vse_out, DowObsData &obs_data) {
    const bool dbg_on   = m_dow_cal.k_dow_debug_log_enable;
    std::size_t dbg_idx = static_cast<std::size_t>(&obs_data - m_obs_data.data());
    DowObjDebug &dbg     = m_debug.obj[dbg_idx];

    float objLongRelVel = obs_data.m_obs->long_vel - vse_out.vcs_long_vel;

    bool LongRelVelCheck = (objLongRelVel >= m_dow_cal.k_dow_approaching_velocity_min);
    bool LongVelCheck    = (obs_data.m_obs->long_vel >= m_dow_cal.k_dow_target_long_velocity_min);
    bool LatVelCheck     = (std::abs(obs_data.m_obs->lat_vel) <= m_dow_cal.k_dow_target_lat_velocity_max);
    bool HeadingCheck    = (std::abs(obs_data.m_obs->heading) <= (m_dow_cal.k_dow_angle_velocity_vector_max * m_pi / 180.0f));

    // 回灌调试：记录相关性判据与原始量
    if (dbg_on) {
        dbg.long_rel_vel_ok = LongRelVelCheck;
        dbg.long_vel_ok     = LongVelCheck;
        dbg.lat_vel_ok      = LatVelCheck;
        dbg.heading_ok      = HeadingCheck;
        dbg.long_rel_vel    = objLongRelVel;
        dbg.long_vel        = obs_data.m_obs->long_vel;
        dbg.lat_vel         = obs_data.m_obs->lat_vel;
        dbg.heading         = obs_data.m_obs->heading;
    }

    if (!LongRelVelCheck || !LongVelCheck || !LatVelCheck || !HeadingCheck) {
        if (dbg_on) dbg.relevant = false;
        return false;
    }

    FindReferencePoint(obs_data);
    if (dbg_on) {
        dbg.ref_x         = obs_data.m_reference_point.x;
        dbg.ref_y         = obs_data.m_reference_point.y;
        dbg.location_side = static_cast<int>(obs_data.m_location_side);
    }

    switch (m_dow_cal.k_dow_zone_test_mode) {
        case 0:
            CheckPointInZone(obs_data.m_reference_point, obs_data);
            break;
        case 1:
            CheckPointInZone(math::Point2D(obs_data.m_obs->long_posn, obs_data.m_obs->lat_posn), obs_data);
            break;
        case 2:
            if ((-vse_out.config.k_host_width / 2.0f) > obs_data.m_obs->lat_posn) {
                obs_data.m_location_side = DowObjectSide::EGO_RIGHT_SIDE;
            } else if ((vse_out.config.k_host_width / 2.0f) < obs_data.m_obs->lat_posn) {
                obs_data.m_location_side = DowObjectSide::EGO_LEFT_SIDE;
            } else if (std::abs(obs_data.m_obs->lat_posn) < (vse_out.config.k_host_width / 2.0f)) {
                obs_data.m_location_side = DowObjectSide::EGO_LANE;
            } else {
                obs_data.m_location_side = DowObjectSide::UNDEF_SIDE;
            }

            if ((DowObjectSide::UNDEF_SIDE == obs_data.m_location_side) || (DowObjectSide::EGO_LANE == obs_data.m_location_side)) {
                obs_data.m_overlap = OverlapType::NO_OVERLAP;
            }
            break;
        default:
            obs_data.m_overlap = OverlapType::NO_OVERLAP;
            break;
    }

    // 回灌调试：记录区域归属结果(CheckPointInZone 已写入 m_overlap)
    if (dbg_on) dbg.overlap = static_cast<int>(obs_data.m_overlap);

    if (((obs_data.m_overlap == OverlapType::OVERLAP_REAR_LEFT) || (obs_data.m_overlap == OverlapType::OVERLAP_REAR_RIGHT)) &&
        (std::abs(obs_data.m_obs->heading) <= ((m_dow_cal.k_dow_angle_velocity_vector_max * m_pi / 180.0f)))) {
        if (dbg_on) dbg.relevant = true;
        return true;
    }

    if ((true == m_dow_cal.k_dow_ftm_enable_flag) &&
        ((obs_data.m_overlap == OverlapType::OVERLAP_FRONT_LEFT) || (obs_data.m_overlap == OverlapType::OVERLAP_FRONT_RIGHT)) &&
        (std::abs(obs_data.m_obs->heading) >= ((m_pi - m_dow_cal.k_dow_ftm_angle_velocity_vector_max)))) {
        if (dbg_on) dbg.relevant = true;
        return true;
    }

    if (dbg_on) dbg.relevant = false;
    return false;
}

void DowFunction::FindReferencePoint(DowObsData& obs_data) {
  float obj_center_x = obs_data.m_obs->curvi_long_posn;
  float obj_center_y = obs_data.m_obs->curvi_lat_posn;
  float heading = obs_data.m_obs->curvi_heading;
  float half_l = obs_data.m_obs->length * 0.5f;
  float half_w = obs_data.m_obs->width * 0.5f;

  math::Point2D corner_fr =
      CalcObjectCorner(obj_center_x, obj_center_y, heading, half_l, half_w);
  math::Point2D corner_fl =
      CalcObjectCorner(obj_center_x, obj_center_y, heading, half_l, -half_w);

  float fr_y_abs = fabsf(corner_fr.y);
  float fl_y_abs = fabsf(corner_fl.y);

  if (fr_y_abs < fl_y_abs) {
    obs_data.m_reference_point = corner_fr;
  } else {
    obs_data.m_reference_point = corner_fl;
  }

  if (corner_fr.y < -m_dow_cal.k_dow_side_judge_tolerance) {
    obs_data.m_location_side = DowObjectSide::EGO_RIGHT_SIDE;
  } else if (corner_fl.y > m_dow_cal.k_dow_side_judge_tolerance) {
    obs_data.m_location_side = DowObjectSide::EGO_LEFT_SIDE;
  } else {
    obs_data.m_location_side = DowObjectSide::EGO_LANE;
  }
}

void DowFunction::CheckPointInZone(const math::Point2D &pt, DowObsData &obs_data) {
    obs_data.m_overlap = OverlapType::NO_OVERLAP;

    if (math::Geometry::IsPointInPoly(m_rear_left_zone, pt)) {
        obs_data.m_overlap = OverlapType::OVERLAP_REAR_LEFT;
        obs_data.m_in_zone = true;
        return;
    }

    if (math::Geometry::IsPointInPoly(m_rear_right_zone, pt)) {
        obs_data.m_overlap = OverlapType::OVERLAP_REAR_RIGHT;
        obs_data.m_in_zone = true;
        return;
    }
    if (m_dow_cal.k_dow_ftm_enable_flag) {
        if (math::Geometry::IsPointInPoly(m_front_left_zone, pt)) {
            obs_data.m_overlap = OverlapType::OVERLAP_FRONT_LEFT;
            obs_data.m_in_zone = true;
            return;
        }
        if (math::Geometry::IsPointInPoly(m_front_right_zone, pt)) {
            obs_data.m_overlap = OverlapType::OVERLAP_FRONT_RIGHT;
            obs_data.m_in_zone = true;
            return;
        }
    }
}

math::Point2D DowFunction::CalcObjectCorner(float center_x, float center_y, float heading, float local_x, float local_y) {
    float cos_h = cosf(heading);
    float sin_h = sinf(heading);
    float rx = local_x * cos_h - local_y * sin_h;
    float ry = local_x * sin_h + local_y * cos_h;
    return math::Point2D(rx + center_x, ry + center_y);
}

} // namespace dow
} // namespace active_safety
