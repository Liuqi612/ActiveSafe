#include "dow_function.h"

#include <algorithm>
#include <cmath>
#include <string.h>

namespace active_safety {
namespace dow {

DowFunction::DowFunction() {
    InitZone();
}

DowFunction::~DowFunction() {
}
void DowFunction::Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list) {

    for (std::size_t idx = 0; idx < kMaxNormalObject; ++idx) {
        obs_data_[idx].obs = obs_list[idx];
        if (obs_data_[idx].obs->fus_trkID <= 0) {
            ResetObjectPersistent(obs_data_[idx]);
            continue;
        }

        if (!IsObjectValid(obs_data_[idx])) {
            ResetObjectPersistent(obs_data_[idx]);
            continue;
        }

        if (!IsObjectRelevant(vse_out, obs_data_[idx])) {
            ResetObjectPersistent(obs_data_[idx]);
            continue;
        }

        UpdateCriticalObs(vse_out, obs_data_[idx]);
    }
    FindThreatWarn();
    StateMachine(config, vse_out);
}

void DowFunction::InitZone() {
    rear_left_zone.clear();
    rear_left_zone.point_list.emplace_back(dow_cal_.k_ced_warning_zone_long[0], dow_cal_.k_ced_warning_zone_lat[0]);
    rear_left_zone.point_list.emplace_back(dow_cal_.k_ced_warning_zone_long[1], dow_cal_.k_ced_warning_zone_lat[1]);
    rear_left_zone.point_list.emplace_back(dow_cal_.k_ced_warning_zone_long[2], dow_cal_.k_ced_warning_zone_lat[2]);
    rear_left_zone.point_list.emplace_back(dow_cal_.k_ced_warning_zone_long[3], dow_cal_.k_ced_warning_zone_lat[3]);
    rear_right_zone.clear();
    rear_right_zone.point_list.emplace_back(dow_cal_.k_ced_warning_zone_long[3], -dow_cal_.k_ced_warning_zone_lat[3]);
    rear_right_zone.point_list.emplace_back(dow_cal_.k_ced_warning_zone_long[2], -dow_cal_.k_ced_warning_zone_lat[2]);
    rear_right_zone.point_list.emplace_back(dow_cal_.k_ced_warning_zone_long[0], -dow_cal_.k_ced_warning_zone_lat[0]);
    rear_right_zone.point_list.emplace_back(dow_cal_.k_ced_warning_zone_long[1], -dow_cal_.k_ced_warning_zone_lat[1]);
    front_left_zone.clear();
    front_left_zone.point_list.emplace_back(dow_cal_.k_ced_ftm_warning_zone_long[1], dow_cal_.k_ced_ftm_warning_zone_lat[1]);
    front_left_zone.point_list.emplace_back(dow_cal_.k_ced_ftm_warning_zone_long[0], dow_cal_.k_ced_ftm_warning_zone_lat[0]);
    front_left_zone.point_list.emplace_back(dow_cal_.k_ced_ftm_warning_zone_long[2], dow_cal_.k_ced_ftm_warning_zone_lat[2]);
    front_left_zone.point_list.emplace_back(dow_cal_.k_ced_ftm_warning_zone_long[3], dow_cal_.k_ced_ftm_warning_zone_lat[3]);
    front_right_zone.clear();
    front_right_zone.point_list.emplace_back(dow_cal_.k_ced_ftm_warning_zone_long[2], -dow_cal_.k_ced_ftm_warning_zone_lat[2]);
    front_right_zone.point_list.emplace_back(dow_cal_.k_ced_ftm_warning_zone_long[3], -dow_cal_.k_ced_ftm_warning_zone_lat[3]);
    front_right_zone.point_list.emplace_back(dow_cal_.k_ced_ftm_warning_zone_long[1], -dow_cal_.k_ced_ftm_warning_zone_lat[1]);
    front_right_zone.point_list.emplace_back(dow_cal_.k_ced_ftm_warning_zone_long[0], -dow_cal_.k_ced_ftm_warning_zone_lat[0]);
}

void DowFunction::ResetObjectPersistent(DowObsData &obs_data) {
    obs_data.f_in_zone                 = false;
    obs_data.f_alert                   = false;
    obs_data.ttc                       = 1000.0f;
    obs_data.distance                  = 1000.0f;
    obs_data.intersec_point_lat        = 0.0f;
    obs_data.overlap                   = OverlapType::NO_OVERLAP;
    obs_data.location_side             = DowObjectSide::UNDEF_SIDE;
    obs_data.direction_relative_to_ego = TravelEgoDirection::UNDEF_DIRECTION;
}

void DowFunction::FindReferencePoint(DowObsData &obs_data, float host_dist_to_front) {
    float obj_center_x = obs_data.obs->curvi_long_posn - host_dist_to_front;
    float obj_center_y = obs_data.obs->curvi_lat_posn;
    float heading      = obs_data.obs->curvi_heading;
    float half_l       = obs_data.obs->length * 0.5f;
    float half_w       = obs_data.obs->width * 0.5f;

    // 仿照 dow_select.cpp 的逻辑定义 FR 和 FL
    math::Point2D corner_fr = CalcObjectCorner(obj_center_x, obj_center_y, heading, half_l, half_w);
    math::Point2D corner_fl = CalcObjectCorner(obj_center_x, obj_center_y, heading, half_l, -half_w);

    float fr_y_abs = fabsf(corner_fr.y);
    float fl_y_abs = fabsf(corner_fl.y);

    // 选取离中线最近的点作为参考点 (pRefPoint)
    if (fr_y_abs < fl_y_abs) {
        obs_data.reference_point = corner_fr;
    } else {
        obs_data.reference_point = corner_fl;
    }

    // 侧向判定 logic from FindReferencePoint
    if (corner_fr.y < -0.01f) {
        obs_data.location_side = DowObjectSide::EGO_RIGHT_SIDE;
    } else if (corner_fl.y > 0.01f) {
        obs_data.location_side = DowObjectSide::EGO_LEFT_SIDE;
    } else {
        obs_data.location_side = DowObjectSide::EGO_LANE;
    }
}

void DowFunction::CheckPointInZone(const math::Point2D &pt, DowObsData &obs_data) {
    obs_data.overlap = OverlapType::NO_OVERLAP;

    if (math::Geometry::IsPointInPoly(rear_left_zone, pt)) {
        obs_data.overlap = OverlapType::OVERLAP_REAR_LEFT;
        return;
    }

    if (math::Geometry::IsPointInPoly(rear_right_zone, pt)) {
        obs_data.overlap = OverlapType::OVERLAP_REAR_RIGHT;
        return;
    }
    if (dow_cal_.k_ced_ftm_enable_flag) {
        if (math::Geometry::IsPointInPoly(front_left_zone, pt)) {
            obs_data.overlap = OverlapType::OVERLAP_FRONT_LEFT;
            return;
        }
        if (math::Geometry::IsPointInPoly(front_right_zone, pt)) {
            obs_data.overlap = OverlapType::OVERLAP_FRONT_RIGHT;
            return;
        }
    }
}

math::Point2D DowFunction::CalcObjectCorner(float center_x, float center_y, float heading, float local_x, float local_y) {
    float cos_h = cosf(heading);
    float sin_h = sinf(heading);
    // 标准 2D 旋转公式
    float rx = local_x * cos_h - local_y * sin_h;
    float ry = local_x * sin_h + local_y * cos_h;
    return math::Point2D(rx + center_x, ry + center_y);
}

void DowFunction::CheckMotion(DowObsData &obs_data) {
    if (obs_data.obs->speed < 0.9f) {
        obs_data.f_stationary = true;
    } else {
        obs_data.f_stationary = false;
    }
}

bool DowFunction::IsObjectValid(DowObsData &obs_data) {
    CheckMotion(obs_data);
    if (obs_data.obs->fus_trkID > 0 && (obs_data.obs->status == TrackStatus::UPDATED || obs_data.obs->status == TrackStatus::COASTED) &&
        !obs_data.f_stationary && obs_data.obs->width > 0.1f) {
        return true;
    }
    return false;
}

bool DowFunction::IsObjectRelevant(const AsVseOut &vse_out, DowObsData &obs_data) {
    float objLongRelVel = obs_data.obs->long_vel - vse_out.vcs_long_vel;

    bool LongRelVelCheck = (objLongRelVel >= dow_cal_.k_ced_approaching_velocity_min);
    bool LongVelCheck    = (obs_data.obs->long_vel >= dow_cal_.k_ced_target_long_velocity_min);
    bool LatVelCheck     = (std::abs(obs_data.obs->lat_vel) <= dow_cal_.k_ced_target_lat_velocity_max);
    bool HeadingCheck    = (std::abs(obs_data.obs->heading) <= (dow_cal_.k_ced_angle_velocity_vector_max * M_PI / 180.0f));

    if (!LongRelVelCheck || !LongVelCheck || !LatVelCheck || !HeadingCheck) {
        return false;
    }

    FindReferencePoint(obs_data, vse_out.config.k_dist_to_rear_axle);

    switch (dow_cal_.k_ced_zone_test_mode) {
        case 0:
            CheckPointInZone(obs_data.reference_point, obs_data);
            break;
        case 1:
            CheckPointInZone(math::Point2D(obs_data.obs->long_posn, obs_data.obs->lat_posn), obs_data);
            break;
        case 2:
            if ((-vse_out.config.k_host_width / 2.0f) > obs_data.obs->lat_posn) {
                obs_data.location_side = DowObjectSide::EGO_RIGHT_SIDE;
            } else if ((vse_out.config.k_host_width / 2.0f) < obs_data.obs->lat_posn) {
                obs_data.location_side = DowObjectSide::EGO_LEFT_SIDE;
            } else if (std::abs(obs_data.obs->lat_posn) < (vse_out.config.k_host_width / 2.0f)) {
                obs_data.location_side = DowObjectSide::EGO_LANE;
            } else {
                obs_data.location_side = DowObjectSide::UNDEF_SIDE;
            }

            if ((DowObjectSide::UNDEF_SIDE == obs_data.location_side) || (DowObjectSide::EGO_LANE == obs_data.location_side)) {
                obs_data.overlap = OverlapType::NO_OVERLAP;
            }
            break;
        default:
            obs_data.overlap = OverlapType::NO_OVERLAP;
            break;
    }

    if (((obs_data.overlap == OverlapType::OVERLAP_REAR_LEFT) || (obs_data.overlap == OverlapType::OVERLAP_REAR_RIGHT)) &&
        (std::abs(obs_data.obs->heading) <= ((dow_cal_.k_ced_angle_velocity_vector_max * m_pi / 180.0f)))) {
        return true;
    }

    if ((true == dow_cal_.k_ced_ftm_enable_flag) &&
        ((obs_data.overlap == OverlapType::OVERLAP_FRONT_LEFT) || (obs_data.overlap == OverlapType::OVERLAP_FRONT_RIGHT)) &&
        (std::abs(obs_data.obs->heading) >= ((m_pi - dow_cal_.k_ced_ftm_angle_velocity_vector_max)))) {
        return true;
    }

    return false;
}

void DowFunction::UpdateCriticalObs(const AsVseOut &vse_out, DowObsData &obs_data) {
    // Ported FindVelIntersection
    float dirX         = cosf(obs_data.obs->heading);
    float dirY         = sinf(obs_data.obs->heading);
    float crashLineLon = (obs_data.overlap == OverlapType::OVERLAP_REAR_LEFT || obs_data.overlap == OverlapType::OVERLAP_REAR_RIGHT)
                             ? dow_cal_.k_ced_crash_line_long
                             : dow_cal_.k_ced_ftm_crash_line_long;

    // Use reference for distance to crash line
    float distToCrash           = math::SafeDivide(crashLineLon - (obs_data.reference_point.x - vse_out.config.k_dist_to_rear_axle), dirX);
    obs_data.intersec_point_lat = obs_data.reference_point.y + (dirY * distToCrash);
    obs_data.ttc                = math::SafeDivide(distToCrash, obs_data.obs->speed);
    obs_data.ttc                = (obs_data.ttc > 0.0f) ? obs_data.ttc : 0.0f;
    obs_data.distance           = distToCrash;

    // IsObjectAlerted
    bool is_obs_alerted = false;
    if (DowObjectSide::EGO_LEFT_SIDE == obs_data.location_side) {
        // is_obs_alerted = (previous_alert[0]);
    } else if (DowObjectSide::EGO_RIGHT_SIDE == obs_data.location_side) {
        // is_obs_alerted = (previous_alert[1]);
    } else {
        is_obs_alerted = false;
    }
    // Ported AddCriticalLevelInfo filtering
    float intersection_min[2];
    float intersection_max[2];
    float ttc_max;
    float ftm_intersection_min[2] = {0.0f, 0.0f};
    float ftm_intersection_max[2] = {0.0f, 0.0f};
    float ftm_ttc_max             = 0.0f;

    float rearViewMirrorToRearBumpTTC = 0.0f;

    intersection_min[0] = dow_cal_.k_ced_intersection_point_lat_critical_level_min;
    intersection_min[1] = dow_cal_.k_ced_intersection_point_lat_critical_level_min;
    intersection_max[0] = dow_cal_.k_ced_intersection_point_lat_critical_level_max;
    intersection_max[1] = dow_cal_.k_ced_intersection_point_lat_critical_level_max;
    ttc_max             = dow_cal_.k_ced_ttc_critical_level_max;
    if (obs_data.obs->long_vel > 2.0f) {
        rearViewMirrorToRearBumpTTC = vse_out.config.k_dist_to_rear_axle / obs_data.obs->long_vel;
    }
    ttc_max = ttc_max + rearViewMirrorToRearBumpTTC;

    if (true == dow_cal_.k_ced_ftm_enable_flag) {
        ftm_intersection_min[0] = dow_cal_.k_ced_ftm_intersection_point_lat_critical_level_min;
        ftm_intersection_min[1] = dow_cal_.k_ced_ftm_intersection_point_lat_critical_level_min;
        ftm_intersection_max[0] = dow_cal_.k_ced_ftm_intersection_point_lat_critical_level_max;
        ftm_intersection_max[1] = dow_cal_.k_ced_ftm_intersection_point_lat_critical_level_max;
        ftm_ttc_max             = dow_cal_.k_ced_ftm_ttc_critical_level_max;
    }

    if (is_obs_alerted) {
        if (TravelEgoDirection::REAR_LEFT_DIRECTION == obs_data.direction_relative_to_ego) {
            /* Adding another condition here to check if the direction of the
             * alerted target is forward */
            intersection_min[0] -= dow_cal_.k_ced_intersection_hysteresis;
            intersection_max[0] += dow_cal_.k_ced_intersection_hysteresis;
            ttc_max += dow_cal_.k_ced_ttc_hysteresis;
        } else if (TravelEgoDirection::REAR_RIGHT_DIRECTION == obs_data.direction_relative_to_ego) {
            intersection_min[1] -= dow_cal_.k_ced_intersection_hysteresis;
            intersection_max[1] += dow_cal_.k_ced_intersection_hysteresis;
            ttc_max += dow_cal_.k_ced_ttc_hysteresis;
        } else if ((true == dow_cal_.k_ced_ftm_enable_flag) && (TravelEgoDirection::FRONT_LEFT_DIRECTION == obs_data.direction_relative_to_ego)) {
            ftm_intersection_min[0] -= dow_cal_.k_ced_ftm_intersection_hysteresis;
            ftm_intersection_max[0] += dow_cal_.k_ced_ftm_intersection_hysteresis;
            ftm_ttc_max += dow_cal_.k_ced_ftm_ttc_hysteresis;
        } else if ((true == dow_cal_.k_ced_ftm_enable_flag) && (TravelEgoDirection::FRONT_RIGHT_DIRECTION == obs_data.direction_relative_to_ego)) {
            ftm_intersection_min[1] -= dow_cal_.k_ced_ftm_intersection_hysteresis;
            ftm_intersection_max[1] += dow_cal_.k_ced_ftm_intersection_hysteresis;
            ftm_ttc_max += dow_cal_.k_ced_ftm_ttc_hysteresis;
        }
    }

    if ((OverlapType::OVERLAP_REAR_LEFT == obs_data.overlap) && (obs_data.reference_point.y > vse_out.config.k_host_width * 0.5f) &&
        (obs_data.intersec_point_lat >= intersection_min[1]) && (obs_data.intersec_point_lat <= intersection_max[1])) {
        obs_data.direction_relative_to_ego = TravelEgoDirection::REAR_LEFT_DIRECTION;
    } else if ((OverlapType::OVERLAP_REAR_RIGHT == obs_data.overlap) && (obs_data.reference_point.y < -vse_out.config.k_host_width * 0.5f) &&
               (obs_data.intersec_point_lat <= -intersection_min[0]) && (obs_data.intersec_point_lat >= -intersection_max[0])) {
        obs_data.direction_relative_to_ego = TravelEgoDirection::REAR_RIGHT_DIRECTION;
    } else if ((dow_cal_.k_ced_ftm_enable_flag) && (OverlapType::OVERLAP_REAR_RIGHT == obs_data.overlap) &&
               (obs_data.reference_point.y < -vse_out.config.k_host_width * 0.5f) && (obs_data.intersec_point_lat <= -ftm_intersection_min[0]) &&
               (obs_data.intersec_point_lat >= -ftm_intersection_max[0])) {
        obs_data.direction_relative_to_ego = TravelEgoDirection::FRONT_RIGHT_DIRECTION;
    } else if ((dow_cal_.k_ced_ftm_enable_flag) && (OverlapType::OVERLAP_FRONT_LEFT == obs_data.overlap) &&
               (obs_data.reference_point.y > vse_out.config.k_host_width * 0.5f) && (obs_data.intersec_point_lat >= ftm_intersection_min[1]) &&
               (obs_data.intersec_point_lat <= ftm_intersection_max[1])) {
        obs_data.direction_relative_to_ego = TravelEgoDirection::FRONT_LEFT_DIRECTION;
    } else {
        obs_data.direction_relative_to_ego = TravelEgoDirection::UNDEF_DIRECTION;
    }

    bool ttc_valid  = (obs_data.ttc > 0.0f && obs_data.ttc <= ttc_max);
    bool dist_valid = (obs_data.distance <= dow_cal_.k_ced_distance_critical_level_max);
    bool dir_valid  = ((TravelEgoDirection::REAR_LEFT_DIRECTION == obs_data.direction_relative_to_ego) ||
                      (TravelEgoDirection::REAR_RIGHT_DIRECTION == obs_data.direction_relative_to_ego));

    bool front_ttc_valid  = (obs_data.ttc > 0.0f && obs_data.ttc <= ftm_ttc_max);
    bool front_dist_valid = (obs_data.distance <= dow_cal_.k_ced_ftm_distance_critical_level_max);
    bool front_dir_valid  = ((TravelEgoDirection::FRONT_LEFT_DIRECTION == obs_data.direction_relative_to_ego) ||
                            (TravelEgoDirection::FRONT_RIGHT_DIRECTION == obs_data.direction_relative_to_ego));

    bool late_check = !((obs_data.ttc < 0.2f) && (false == obs_data.f_alert));

    if (ttc_valid && dist_valid && dir_valid && late_check) {
        if (obs_data.cycle_of_alert < 255) {
            obs_data.cycle_of_alert++;
        }

        if (obs_data.cycle_of_alert > dow_cal_.k_ced_number_cycle_qualify_critical_level) {
            obs_data.f_alert = true;
        }
    } else if (dow_cal_.k_ced_ftm_enable_flag && front_ttc_valid && front_dist_valid && front_dir_valid && late_check) {
        if (obs_data.cycle_of_alert < 255) {
            obs_data.cycle_of_alert++;
        }

        if (obs_data.cycle_of_alert > dow_cal_.k_ced_number_cycle_qualify_critical_level) {
            obs_data.f_alert = true;
        }
    } else {
        obs_data.f_alert = false;
        // obs_data.cycle_of_alert = 0;
    }
}

void DowFunction::StateMachine(const GlobalConfig &config, const AsVseOut &vse_out) {
    dow_mode_cond_.state_off   = (vse_out.dow_switch != 1);
    dow_mode_cond_.state_fault = false;
    //车速条件
    bool host_speed_enable         = (vse_out.speed > -0.1f && vse_out.speed < dow_cal_.k_dow_max_enable_host_spd);
    dow_mode_cond_.state_inhibit   = (!host_speed_enable);
    dow_mode_cond_.state_active    = (dow_out_.warn_left > 0 || dow_out_.warn_right > 0);
    dow_mode_cond_.off2inhibit     = (dow_mode_cond_.state_off == false && dow_mode_cond_.state_fault == false);
    dow_mode_cond_.fault2inhibit   = (dow_mode_cond_.state_off == false && dow_mode_cond_.state_fault == false);
    dow_mode_cond_.inhibit2standby = (dow_mode_cond_.state_inhibit == false);
    dow_mode_cond_.inhibit2active  = (dow_mode_cond_.state_inhibit == false && dow_mode_cond_.state_active == true);
    dow_mode_cond_.standby2active  = (dow_mode_cond_.state_inhibit == false && dow_mode_cond_.state_active == true);
    dow_mode_cond_.active2standby  = (dow_mode_cond_.state_inhibit == false && dow_mode_cond_.state_active == false);
    // 设置状态机条件
    dow_mode_context_.setCondition(dow_mode_cond_);
    // 更新状态机
    dow_mode_.update(dow_mode_context_);
    bool f_display_target = false;
    if (dow_mode_.getCurrentSubState() == math::ModeState::ACTIVE) {
        // left
        if (dow_out_.warn_left > 0 && (vse_out.fl_door_st == 1 || vse_out.rl_door_st == 1)) {
            dow_out_.warn_left = 2; // for warn sound
        } else {
            dow_out_.warn_left = 0;
        }
        // right
        if (dow_out_.warn_right > 0 && (vse_out.fr_door_st == 1 || vse_out.rr_door_st == 1)) {
            dow_out_.warn_right = 2; // for warn sound
        } else {
            dow_out_.warn_right = 0;
        }
        f_display_target = true;
    } else {
        dow_out_.warn_left  = 0;
        dow_out_.warn_right = 0;
    }
    if ((dow_mode_.getCurrentStateId() == math::ModeState::ON) || vse_out.dow_switch == 1) {
        dow_out_.switch_req = 2;
    } else {
        dow_out_.switch_req = 1;
    }
    switch (dow_mode_.getCurrentSubState()) {
        case math::ModeState::OFF: {
            dow_out_.state = DowState::OFF;
            break;
        }
        case math::ModeState::FAULT: {
            dow_out_.state = DowState::FAULT;
            break;
        }
        case math::ModeState::ON:
        case math::ModeState::INHIBIT: {
            dow_out_.state = DowState::INHIBIT;
            break;
        }
        case math::ModeState::STANDBY: {
            {
                dow_out_.state = DowState::STANDBY;
                break;
            }
        }
        case math::ModeState::ACTIVE: {
            dow_out_.state = DowState::ACTIVE;
            break;
        }
        default: {
            dow_out_.state = DowState::INHIBIT;
            break;
        }
    }
    if (config.k_use_shadowmode || !config.k_dow_enable) {
        dow_out_.warn_left  = 0;
        dow_out_.warn_right = 0;
    }
}

void DowFunction::FindThreatWarn() {
    float right_lowest_TTC  = 1000.0;
    float left_lowest_TTC   = 1000.0;
    float right_lowest_dist = 1000.0;
    float left_lowest_dist  = 1000.0;
    memset(&dow_out_.left_tgt, 0, sizeof(dow_out_.left_tgt));
    memset(&dow_out_.right_tgt, 0, sizeof(dow_out_.right_tgt));
    for (const auto &obs_data : obs_data_) {
        if (!obs_data.f_alert) {
            continue;
        }
        if ((obs_data.direction_relative_to_ego == TravelEgoDirection::FRONT_LEFT_DIRECTION ||
             obs_data.direction_relative_to_ego == TravelEgoDirection::REAR_LEFT_DIRECTION) &&
            obs_data.location_side == DowObjectSide::EGO_LEFT_SIDE) {

            if (obs_data.ttc < left_lowest_TTC || (fabs(obs_data.ttc - left_lowest_TTC) < 0.0001f && obs_data.distance < left_lowest_dist)) {
                FillTargetInfo(obs_data, dow_out_.left_tgt);
                dow_out_.warn_left = 1;
            }

        } else if ((obs_data.direction_relative_to_ego == TravelEgoDirection::REAR_RIGHT_DIRECTION ||
                    obs_data.direction_relative_to_ego == TravelEgoDirection::FRONT_RIGHT_DIRECTION) &&
                   obs_data.location_side == DowObjectSide::EGO_RIGHT_SIDE) {

            if (obs_data.ttc < right_lowest_TTC || (fabs(obs_data.ttc - right_lowest_TTC) < 0.0001f && obs_data.distance < right_lowest_dist)) {
                FillTargetInfo(obs_data, dow_out_.right_tgt);
                dow_out_.warn_right = 1;
            }
        }
    }
}

void DowFunction::FillTargetInfo(const DowObsData &obs_data, AsTargetInfo_T &tgt_info) {
    tgt_info.id      = obs_data.obs->fus_trkID;
    tgt_info.type    = static_cast<uint32_t>(obs_data.obs->object_class);
    tgt_info.source  = static_cast<uint32_t>(obs_data.obs->fusion_source);
    tgt_info.posx    = obs_data.obs->long_posn;
    tgt_info.posy    = obs_data.obs->lat_posn;
    tgt_info.spdx    = obs_data.obs->long_vel;
    tgt_info.spdy    = obs_data.obs->lat_vel;
    tgt_info.accelx  = obs_data.obs->long_accel;
    tgt_info.accely  = obs_data.obs->lat_accel;
    tgt_info.heading = obs_data.obs->heading;
    tgt_info.ttc     = obs_data.ttc;
}

} // namespace dow
} // namespace active_safety
