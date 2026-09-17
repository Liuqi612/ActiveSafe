#include "cts_function.h"

namespace active_safety {
namespace cts {

void CtsFunction::CheckApproachSide(CtsObsData &obs_data) {
    obs_data.m_approach_side = CTA_APPROACH_UNDEFINED;
    if (obs_data.m_obs->heading < 0.0f) {
        if (obs_data.m_obs->lat_posn > 0.0f && obs_data.m_obs->lat_vel < 0.0f) {
            obs_data.m_approach_side = CTA_APPROACH_FROM_LEFT;
        }
    } else {
        if (obs_data.m_obs->lat_posn < 0.0f && obs_data.m_obs->lat_vel > 0.0f) {
            obs_data.m_approach_side = CTA_APPROACH_FROM_RIGHT;
        }
    }
}

bool CtsFunction::CalculateObsDuringObsToHost(const AsVseOut &vse_out, CtsObsData &obs_data) {
    // 前提为obs_data朝向自车
    obs_data.m_dur_obs_to_host_ids.clear();
    obs_data.m_during_obs_to_host_zone.clear();
    if (obs_data.m_obs->lat_posn * obs_data.m_obs->heading > 0.0f) {
        return true;
    }
    // 计算目标和自车中心包络的矩形
    math::Point2D fl_pt, fr_pt;
    float half_obs_width = obs_data.m_obs->width * 0.5f + m_cts_cal.k_cta_obs_envelope_buffer;
    float half_obs_length = obs_data.m_obs->length * 0.5f;
    float cos_obs_heading = cosf(obs_data.m_obs->heading);
    float sin_obs_heading = sinf(obs_data.m_obs->heading);

    float obs_half_width_sin = half_obs_width * sin_obs_heading;
    float obs_half_width_cos = half_obs_width * cos_obs_heading;
    float obs_half_length_cos = half_obs_length * cos_obs_heading;
    float obs_half_length_sin = half_obs_length * sin_obs_heading;

    fl_pt.x = obs_data.m_obs->long_posn + obs_half_length_cos - obs_half_width_sin;
    fl_pt.y = obs_data.m_obs->lat_posn + obs_half_length_sin + obs_half_width_cos;
    fr_pt.x = obs_data.m_obs->long_posn + obs_half_length_cos + obs_half_width_sin;
    fr_pt.y = obs_data.m_obs->lat_posn + obs_half_length_sin - obs_half_width_cos;

    // 沿目标航向线求与自车中心线(y=0)的交点：y + sinθ·t = 0 => t = -y/sinθ
    // x_inter = x + cosθ·t = x - y·cosθ/sinθ = x - y/tanθ
    float inter_delta_lgt_fl = math::SafeDivide(-fl_pt.y * cos_obs_heading, sin_obs_heading);
    float inter_delta_lgt_fr = math::SafeDivide(-fr_pt.y * cos_obs_heading, sin_obs_heading);

    math::Point2D fl_2_host_inter_pt{fl_pt.x + inter_delta_lgt_fl, 0.0f};
    math::Point2D fr_2_host_inter_pt{fr_pt.x + inter_delta_lgt_fr, 0.0f};

    obs_data.m_during_obs_to_host_zone.point_list.push_back(fl_pt);
    obs_data.m_during_obs_to_host_zone.point_list.push_back(fl_2_host_inter_pt);
    obs_data.m_during_obs_to_host_zone.point_list.push_back(fr_2_host_inter_pt);
    obs_data.m_during_obs_to_host_zone.point_list.push_back(fr_pt);

    for (size_t i = 0; i < m_obs_data.size(); ++i) {
        if (m_obs_data[i].m_obs->fus_trkID == obs_data.m_obs->fus_trkID ||
            (m_obs_data[i].m_obs->lat_posn * obs_data.m_obs->lat_posn < 0.0f &&
             fabs(m_obs_data[i].m_obs->lat_posn) > m_cts_cal.k_cta_opposite_side_lat_thres &&
             m_obs_data[i].m_obs->object_class != ObjectClass::TRUCK)) {
            continue;
        }
        
        // 其他目标中心点到 obs_data 朝向直线的垂直距离（叉积），超过目标外接圆半径则不可能与包络区域重叠
        float dx = m_obs_data[i].m_obs->long_posn - obs_data.m_obs->long_posn;
        float dy = m_obs_data[i].m_obs->lat_posn - obs_data.m_obs->lat_posn;
        float lateral_dist = fabsf(dx * sin_obs_heading - dy * cos_obs_heading);
        float other_half_width = 0.5f * m_obs_data[i].m_obs->width;
        float other_half_diag = 0.5f * sqrtf(m_obs_data[i].m_obs->length * m_obs_data[i].m_obs->length +
                                              m_obs_data[i].m_obs->width * m_obs_data[i].m_obs->width);
        if (lateral_dist > half_obs_width + other_half_diag) {
            continue;
        }

        const AsObstacle &other = *m_obs_data[i].m_obs;
        float other_cos = cosf(other.heading);
        float other_sin = sinf(other.heading);
        float other_hl_cos = 0.5f * other.length * other_cos;
        float other_hl_sin = 0.5f * other.length * other_sin;
        float other_hw_sin = other_half_width * other_sin;
        float other_hw_cos = other_half_width * other_cos;

        math::Polygon obs_poly;
        obs_poly.point_list.emplace_back(other.long_posn + other_hl_cos - other_hw_sin, other.lat_posn + other_hl_sin + other_hw_cos);
        obs_poly.point_list.emplace_back(other.long_posn + other_hl_cos + other_hw_sin, other.lat_posn + other_hl_sin - other_hw_cos);
        obs_poly.point_list.emplace_back(other.long_posn - other_hl_cos + other_hw_sin, other.lat_posn - other_hl_sin - other_hw_cos);
        obs_poly.point_list.emplace_back(other.long_posn - other_hl_cos - other_hw_sin, other.lat_posn - other_hl_sin + other_hw_cos);

        // 若该路径内目标为卡车，将走廊远端从自车中心线扩展到自车车身线外1.5m，以包住可能被卡车遮挡的区域
        if (other.object_class == ObjectClass::TRUCK) {
            float half_ego_width = 0.5f * vse_out.config.k_host_width;
            // 右来车(FROM_RIGHT, heading>0)：目标在自车右侧，向左扩展到左车身线外1.5m (y 正方向)
            // 左来车(FROM_LEFT, heading<0)：目标在自车左侧，向右扩展到右车身线外1.5m (y 负方向)
            float y_far = (obs_data.m_approach_side == CTA_APPROACH_FROM_RIGHT)
                              ? (half_ego_width + m_cts_cal.k_cta_path_truck_zone_extend)
                              : -(half_ego_width + m_cts_cal.k_cta_path_truck_zone_extend);
            // 沿目标航向线求与远端边界线(y=y_far)的交点：t = (y_far - pt.y) / sinθ
            float inter_fl = math::SafeDivide(y_far - fl_pt.y, sin_obs_heading);
            float inter_fr = math::SafeDivide(y_far - fr_pt.y, sin_obs_heading);
            math::Point2D fl_truck_inter_pt{fl_pt.x + cos_obs_heading * inter_fl, y_far};
            math::Point2D fr_truck_inter_pt{fr_pt.x + cos_obs_heading * inter_fr, y_far};
            math::Polygon truck_zone;
            truck_zone.point_list.push_back(fl_pt);
            truck_zone.point_list.push_back(fl_truck_inter_pt);
            truck_zone.point_list.push_back(fr_truck_inter_pt);
            truck_zone.point_list.push_back(fr_pt);
            if (math::Geometry::IsPolyOverlapSAT(obs_poly, truck_zone)) {
                obs_data.m_dur_obs_to_host_ids.push_back(i);
            }
        } else {
            if (math::Geometry::IsPolyOverlapSAT(obs_poly, obs_data.m_during_obs_to_host_zone)) {
                obs_data.m_dur_obs_to_host_ids.push_back(i);
            }
        }
    }

    for (auto idx : obs_data.m_dur_obs_to_host_ids) {
        
        if (m_obs_data[idx].m_stationary) {
            // 路径中有静止目标，目标不会穿过目标行驶，判断无效目标
            return false;
        }

        // 路径中存在低速卡车：朝向接近正北(heading~0)或正南(heading~±π)，且速度绝对值低于阈值(~10kph)，
        // 认为该目标路径不会穿过该低速卡车，判断无效目标
        if (m_obs_data[idx].m_obs->object_class == ObjectClass::TRUCK &&
            fabs(m_obs_data[idx].m_obs->speed) < m_cts_cal.k_cta_path_truck_low_speed_thres) {
            float truck_heading = fabs(m_obs_data[idx].m_obs->heading);
            bool heading_north = truck_heading < m_cts_cal.k_cta_path_truck_ns_heading_tol;
            bool heading_south = truck_heading > (m_pi - m_cts_cal.k_cta_path_truck_ns_heading_tol);
            if (heading_north || heading_south) {
                return false;
            }
        }

        float rel_lat_vel = obs_data.m_obs->lat_vel - m_obs_data[idx].m_obs->lat_vel;
        float rel_lat_pos = obs_data.m_obs->lat_posn - m_obs_data[idx].m_obs->lat_posn;
        float lat_ttc = math::SafeDivide(rel_lat_pos, rel_lat_vel);

        // 横向不会发生碰撞，lat_ttc <= 0 表示相互远离，目标有效
        if (lat_ttc <= 0.0f) {
            continue;
        }

        // 碰撞时刻纵向位置
        float obs_long_at_ttc = obs_data.m_obs->long_posn + obs_data.m_obs->long_vel * lat_ttc;
        float other_long_at_ttc = m_obs_data[idx].m_obs->long_posn + m_obs_data[idx].m_obs->long_vel * lat_ttc;
        float half_len_sum = 0.5f * obs_data.m_obs->length + 0.5f * m_obs_data[idx].m_obs->length;

        // 纵向不会发生碰撞，目标有效
        if (fabsf(obs_long_at_ttc - other_long_at_ttc) > half_len_sum) {
            continue;
        }

        // 碰撞时 obs_data 横向位置是否已穿过自车中心线（y=0）
        float obs_lat_posn_at_ttc = obs_data.m_obs->lat_posn + obs_data.m_obs->lat_vel * lat_ttc;
        if (obs_lat_posn_at_ttc * obs_data.m_obs->lat_posn <= 0.0f) {
            // 碰撞时横向已穿过或恰好到达中心线，目标有效
            continue;
        }
        // 在自车同侧，目标可能与其他目标先发生碰撞，则认为此目标无效
        return false;
    }
    return true;
}

void CtsFunction::CalculateTargetCornersPoint(CtsObsData &obs_data) {
    float cos_heading;
    float sin_heading;
    float half_length;
    float half_width;

    float cta_heading = obs_data.m_obs->heading;
    // Follow C logic for heading adjustment based on velocity
    if (obs_data.m_obs->lat_vel >= 0.0f) {
        cta_heading = fabs(obs_data.m_obs->heading);
    } else {
        cta_heading = -1.0f * fabs(obs_data.m_obs->heading);
    }

    cos_heading = std::cos(cta_heading);
    sin_heading = std::sin(cta_heading);

    half_length = obs_data.m_obs->length * 0.5f;
    half_width = obs_data.m_obs->width * 0.5f;

    // Relative corners in object CS
    math::Point2D rel_corners[4];
    rel_corners[0] = {half_length, -half_width};
    rel_corners[1] = {half_length, half_width};
    rel_corners[2] = {-half_length, half_width};
    rel_corners[3] = {-half_length, -half_width};

    // Transform to VCS
    for (int i = 0; i < 4; ++i) {
        obs_data.m_corner_pts[2 * i].x = obs_data.m_obs->long_posn + (cos_heading * rel_corners[i].x) - (sin_heading * rel_corners[i].y);
        obs_data.m_corner_pts[2 * i].y = obs_data.m_obs->lat_posn + (sin_heading * rel_corners[i].x) + (cos_heading * rel_corners[i].y);
    }

    // Midpoints
    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;
        obs_data.m_corner_pts[2 * i + 1].x = 0.5f * (obs_data.m_corner_pts[2 * i].x + obs_data.m_corner_pts[2 * next].x);
        obs_data.m_corner_pts[2 * i + 1].y = 0.5f * (obs_data.m_corner_pts[2 * i].y + obs_data.m_corner_pts[2 * next].y);
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
        if (fabs(obs_data.m_corner_pts[loop_index].y) > fabs(obs_data.m_obs->lat_posn)) {
            continue;
        }
        // x_rear_bumper calculation
        float x_rear_bumper = obs_data.m_corner_pts[loop_index].x - m_cts_cal.k_cta_distance_to_rear_bumper;
        float distance_to_cs_origin =
            std::sqrt((x_rear_bumper * x_rear_bumper) + (obs_data.m_corner_pts[loop_index].y * obs_data.m_corner_pts[loop_index].y));
        if (distance_to_cs_origin < min_distance_to_ego_rear_bumper) {
            min_distance_to_ego_rear_bumper = distance_to_cs_origin;
            index_min_distance = loop_index;
        }
    }

    // Default reference point logic
    if (fabs(obs_data.m_corner_pts[index_min_distance].y) >= m_cts_cal.k_cta_min_lat_posn_for_default_ref_point) {
        if (index_min_distance != 2 &&
            ((obs_attr.direction == CtsDirection::REAR && obs_data.m_approach_side == CTA_APPROACH_FROM_LEFT) ||
             (obs_attr.direction == CtsDirection::FRONT && obs_data.m_approach_side == CTA_APPROACH_FROM_RIGHT))) {
            index_min_distance = 2;
        } else if (index_min_distance != 0 &&
                   ((obs_attr.direction == CtsDirection::REAR && obs_data.m_approach_side == CTA_APPROACH_FROM_RIGHT) ||
                    (obs_attr.direction == CtsDirection::FRONT && obs_data.m_approach_side == CTA_APPROACH_FROM_LEFT))) {
            index_min_distance = 0;
        }
    }

    obs_attr.reference_pt = obs_data.m_corner_pts[index_min_distance];
    obs_attr.reference_index = index_min_distance + 1;
}

void CtsFunction::CalculateRelativeVelocity(const AsVseOut &vse_out, CtsObsData &obs_data) {
    if (m_cts_cal.k_cta_use_heading_for_relative_velocity_calculation) {
        obs_data.m_relative_velocity.x = (obs_data.m_obs->speed * cosf(obs_data.m_obs->heading)) - vse_out.vcs_long_vel;
        obs_data.m_relative_velocity.y = (obs_data.m_obs->speed * sinf(obs_data.m_obs->heading));
    } else {
        obs_data.m_relative_velocity.x = obs_data.m_obs->long_vel - vse_out.vcs_long_vel;
        obs_data.m_relative_velocity.y = obs_data.m_obs->lat_vel - vse_out.vcs_lat_vel;
    }
}

void CtsFunction::CalculateTimeToConflict(const VehicleConfig &veh_config, const CtsObsData &obs_data, ObsAttribute &obs_attr) {
    if (m_cts_cal.k_cta_calc_ttc_ego_side_enabled) {
        float sign = (obs_data.m_approach_side == CTA_APPROACH_FROM_LEFT) ? 1.0f : -1.0f;
        obs_attr.lat_ttc = (fabs(obs_data.m_relative_velocity.y) > EQUALS_TOLERANCE)
            ? (-(obs_attr.reference_pt.y - sign * 0.5f * veh_config.k_host_width) / obs_data.m_relative_velocity.y)
            : m_cts_cal.k_cta_default_lat_ttc;
    } else {
        obs_attr.lat_ttc = (fabs(obs_data.m_relative_velocity.y) > EQUALS_TOLERANCE)
            ? (-obs_attr.reference_pt.y / obs_data.m_relative_velocity.y)
            : m_cts_cal.k_cta_default_lat_ttc;
    }
    // 使用简单点代替碰撞TTC
    float delta_lgt_dist = obs_attr.reference_pt.x - veh_config.k_dist_to_rear_axle;
    obs_attr.lgt_ttc = math::SafeDivide(delta_lgt_dist, -obs_data.m_relative_velocity.x);
}

void CtsFunction::CalculateIntersecPoint(const math::Point2D &relative_velocity, ObsAttribute &obs_attr) {
    obs_attr.intersect_pt.x = obs_attr.reference_pt.x + (obs_attr.lat_ttc * relative_velocity.x);

    if (fabs(relative_velocity.x) < EQUALS_TOLERANCE) {
        obs_attr.intersect_pt.y = m_cts_cal.k_cta_intersect_inf; // INFINITY
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
    if (obs_data.m_obs->f_obs_straight_cross) {
        m_cta_zone.point_list = m_cts_cal.k_cta_area_for_cross;
        // 对于横穿目标，将范围限制在近距离矩形框，避免远处目标误触发。
        for (int i = 0; i < 4; ++i) {
            m_cta_zone.point_list[i].x -= vse_out.config.k_host_length;
        }
    } else {
        m_cta_zone.point_list = m_cts_cal.k_cta_area;
    }
    if (obs_attr.direction == CtsDirection::FRONT) {
        for (int i = 0; i < 4; ++i) {
            m_cta_zone.point_list[i].x = -m_cta_zone.point_list[i].x - vse_out.config.k_host_length;
        }
    }

    for (int i = 0; i < 4; ++i) {
        m_cta_zone.point_list[i].x = m_cta_zone.point_list[i].x + vse_out.config.k_dist_to_rear_axle;

        if (m_drv_wantbrake_offdly.getStateOut()) {
            if (obs_attr.direction == CtsDirection::FRONT) {
                m_cta_zone.point_list[i].x =
                    fmin(m_cts_cal.k_cts_default_long_area_pos + vse_out.config.k_dist_to_rear_axle, m_cta_zone.point_list[i].x);
            } else {
                m_cta_zone.point_list[i].x =
                    fmax(-m_cts_cal.k_cts_default_long_area_pos + vse_out.config.k_dist_to_rear_axle - vse_out.config.k_host_length,
                         m_cta_zone.point_list[i].x);
            }
        }
    }

    if (obs_data.m_approach_side == CTA_APPROACH_FROM_RIGHT) {
        for (int i = 0; i < 4; ++i) {
            m_cta_zone.point_list[i].y = -m_cta_zone.point_list[i].y;
        }
        if (m_drv_continues_str_dir == DriverSteerDir::Left) {
            for (int i = 0; i < 4; ++i) {
                m_cta_zone.point_list[i].y *= m_cts_cal.k_cta_steer_zone_shrink_factor;
            }
        }
        if (m_drv_increase_str_dir == DriverSteerDir::Left) {
            for (int i = 0; i < 4; ++i) {
                m_cta_zone.point_list[i].y *= m_cts_cal.k_cta_steer_zone_shrink_factor;
            }
        }
    }

    if (obs_data.m_approach_side == CTA_APPROACH_FROM_LEFT) {
        if (m_drv_continues_str_dir == DriverSteerDir::Right) {
            for (int i = 0; i < 4; ++i) {
                m_cta_zone.point_list[i].y *= m_cts_cal.k_cta_steer_zone_shrink_factor;
            }
        }
        if (m_drv_increase_str_dir == DriverSteerDir::Right) {
            for (int i = 0; i < 4; ++i) {
                m_cta_zone.point_list[i].y *= m_cts_cal.k_cta_steer_zone_shrink_factor;
            }
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

    bool in_poly = math::Geometry::IsPointInPoly(m_cta_zone, obs_attr.reference_pt) ||
        math::Geometry::IsPointInPoly(m_cta_zone, obs_data.m_corner_pts[n1_idx - 1]) ||
        math::Geometry::IsPointInPoly(m_cta_zone, obs_data.m_corner_pts[n2_idx - 1]);

    bool f_behind_trailing_edge = IsObjectBehindTrailingEdge(vse_out, obs_data, obs_attr);

    obs_attr.in_zone = in_poly && f_behind_trailing_edge;
}

bool CtsFunction::IsObjectBehindTrailingEdge(const AsVseOut &vse_out, const CtsObsData &obs_data, const ObsAttribute &obs_attr) {
    if (!m_cts_cal.k_cta_use_trailing_edge || obs_attr.direction == CtsDirection::REAR)
        return true;

    float half_ego_width = 0.5f * vse_out.config.k_host_width;

    if (obs_data.m_approach_side == CTA_APPROACH_FROM_RIGHT) {
        if (obs_data.m_obs->heading > m_pi / 2.0f) {
            return obs_data.m_corner_pts[6].y < -half_ego_width;
        } else {
            return obs_data.m_corner_pts[4].y < -half_ego_width;
        }
    } else {
        if (obs_data.m_obs->heading < -m_pi / 2.0f) {
            return obs_data.m_corner_pts[6].y > half_ego_width;
        } else {
            return obs_data.m_corner_pts[4].y > half_ego_width;
        }
    }
}

void CtsFunction::ResetObsData(ObsAttribute &obs_attr) {
    (void)obs_attr;
}

} // namespace cts
} // namespace active_safety
