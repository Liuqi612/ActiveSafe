#include "bsd_function.h"
namespace active_safety {
namespace bsd {

void BsdFunction::CalcObsPolygon(BsdObsData &obs_data) {
    float objHalfWidthSinAng = 0.5f * obs_data.m_obs->width * sinf(obs_data.m_obs->curvi_heading);
    float objHalfWidthCosAng = 0.5f * obs_data.m_obs->width * cosf(obs_data.m_obs->curvi_heading);
    float objHalfLengthCosAng = 0.5f * obs_data.m_obs->length * cosf(obs_data.m_obs->curvi_heading);
    float objHalfLengthSinAng = 0.5f * obs_data.m_obs->length * sinf(obs_data.m_obs->curvi_heading);
    obs_data.m_polygon.clear();
    obs_data.m_polygon.point_list.emplace_back(obs_data.m_obs->curvi_long_posn + objHalfLengthCosAng - objHalfWidthSinAng,
                                             obs_data.m_obs->curvi_lat_posn + objHalfLengthSinAng + objHalfWidthCosAng);
    obs_data.m_polygon.point_list.emplace_back(obs_data.m_obs->curvi_long_posn + objHalfLengthCosAng + objHalfWidthSinAng,
                                             obs_data.m_obs->curvi_lat_posn + objHalfLengthSinAng - objHalfWidthCosAng);
    obs_data.m_polygon.point_list.emplace_back(obs_data.m_obs->curvi_long_posn - objHalfLengthCosAng + objHalfWidthSinAng,
                                             obs_data.m_obs->curvi_lat_posn - objHalfLengthSinAng - objHalfWidthCosAng);
    obs_data.m_polygon.point_list.emplace_back(obs_data.m_obs->curvi_long_posn - objHalfLengthCosAng - objHalfWidthSinAng,
                                             obs_data.m_obs->curvi_lat_posn - objHalfLengthSinAng + objHalfWidthCosAng);
}

void BsdFunction::CalcValidZone(const VehicleConfig &config, BsdObsData &obs_data, const AsVseOut &vse_out) {
    obs_data.m_bsw_polygon.point_list.clear();
    obs_data.m_cvw_polygon.point_list.clear();

    float bsw_longhys = 0.0f;
    float bsw_lathys = 0.0f;
    if (obs_data.m_bsw_in_zone) {
        bsw_longhys = m_bsd_cal.k_bsd_bsw_zone_hys_x;
        bsw_lathys = m_bsd_cal.k_bsd_bsw_zone_hys_y;
    }
    float half_width = 0.5f * config.k_host_width;
    float bsw_dynamic_bottom = 0.0f;
    if (vse_out.speed >= m_bsd_cal.k_bsw_dynamic_zone_host_speed[0] && vse_out.speed < m_bsd_cal.k_bsw_dynamic_zone_host_speed[1]) {
        bsw_dynamic_bottom =
            math::LookUpTable::LinearInterpolation(vse_out.speed, m_bsd_cal.k_bsw_dynamic_zone_host_speed[0], m_bsd_cal.k_bsw_dynamic_zone_x[0],
                                                   m_bsd_cal.k_bsw_dynamic_zone_host_speed[1], m_bsd_cal.k_bsw_dynamic_zone_x[1]);
    } else if (vse_out.speed >= m_bsd_cal.k_bsw_dynamic_zone_host_speed[1] && vse_out.speed < m_bsd_cal.k_bsw_dynamic_zone_host_speed[2]) {
        bsw_dynamic_bottom =
            math::LookUpTable::LinearInterpolation(vse_out.speed, m_bsd_cal.k_bsw_dynamic_zone_host_speed[1], m_bsd_cal.k_bsw_dynamic_zone_x[1],
                                                   m_bsd_cal.k_bsw_dynamic_zone_host_speed[2], m_bsd_cal.k_bsw_dynamic_zone_x[2]);
    } else if (vse_out.speed >= m_bsd_cal.k_bsw_dynamic_zone_host_speed[2] && vse_out.speed < m_bsd_cal.k_bsw_dynamic_zone_host_speed[3]) {
        bsw_dynamic_bottom =
            math::LookUpTable::LinearInterpolation(vse_out.speed, m_bsd_cal.k_bsw_dynamic_zone_host_speed[2], m_bsd_cal.k_bsw_dynamic_zone_x[2],
                                                   m_bsd_cal.k_bsw_dynamic_zone_host_speed[3], m_bsd_cal.k_bsw_dynamic_zone_x[3]);
    } else {
        bsw_dynamic_bottom = 0.0f;
    }

    float dist_to_front_axle = config.k_dist_to_rear_axle - m_bsd_cal.k_bsd_front_axle_to_front_bumper;
    obs_data.m_bsw_polygon.point_list.emplace_back(m_bsd_cal.k_bsd_origin_bsw_zone_x[0] + dist_to_front_axle + bsw_longhys,
                                                 half_width + m_bsd_cal.k_bsd_origin_bsw_zone_y[0] + bsw_lathys);
    obs_data.m_bsw_polygon.point_list.emplace_back(m_bsd_cal.k_bsd_origin_bsw_zone_x[1] + dist_to_front_axle - bsw_longhys - bsw_dynamic_bottom,
                                                 half_width + m_bsd_cal.k_bsd_origin_bsw_zone_y[1] + bsw_lathys);
    obs_data.m_bsw_polygon.point_list.emplace_back(m_bsd_cal.k_bsd_origin_bsw_zone_x[2] + dist_to_front_axle - bsw_longhys - bsw_dynamic_bottom,
                                                 half_width + m_bsd_cal.k_bsd_origin_bsw_zone_y[2] - bsw_lathys + m_bsd_cal.k_bsd_FLine_y);
    obs_data.m_bsw_polygon.point_list.emplace_back(m_bsd_cal.k_bsd_origin_bsw_zone_x[3] + dist_to_front_axle + bsw_longhys,
                                                 half_width + m_bsd_cal.k_bsd_origin_bsw_zone_y[3] - bsw_lathys + m_bsd_cal.k_bsd_FLine_y);

    float cvw_longhys = 0.0f;
    float cvw_lathys = 0.0f;
    if (obs_data.m_cvw_in_zone) {
        cvw_longhys = m_bsd_cal.k_bsd_cvw_zone_hys_x;
        cvw_lathys = m_bsd_cal.k_bsd_cvw_zone_hys_y;
    }

    float dist_to_rear_bumper = config.k_host_length - config.k_dist_to_rear_axle;
    float cvw_far_x_thres = m_bsd_cal.k_bsd_cvw_max_zone_thres + dist_to_rear_bumper;
    cvw_far_x_thres *= -1.0f;
    obs_data.m_cvw_polygon.point_list.emplace_back(m_bsd_cal.k_bsd_origin_bsw_zone_x[1] + dist_to_front_axle + cvw_longhys,
                                                 half_width + m_bsd_cal.k_bsd_origin_bsw_zone_y[1] + cvw_lathys);
    obs_data.m_cvw_polygon.point_list.emplace_back(cvw_far_x_thres - cvw_longhys, half_width + m_bsd_cal.k_bsd_origin_bsw_zone_y[1] + cvw_lathys);
    obs_data.m_cvw_polygon.point_list.emplace_back(cvw_far_x_thres - cvw_longhys,
                                                 half_width + m_bsd_cal.k_bsd_origin_bsw_zone_y[2] - cvw_lathys + m_bsd_cal.k_bsd_FLine_y);
    obs_data.m_cvw_polygon.point_list.emplace_back(m_bsd_cal.k_bsd_origin_bsw_zone_x[2] + dist_to_front_axle - cvw_longhys,
                                                 half_width + m_bsd_cal.k_bsd_origin_bsw_zone_y[2] - cvw_lathys + m_bsd_cal.k_bsd_FLine_y);

    if (obs_data.m_side == ObsSide::Right) {
        for (auto &pt : obs_data.m_bsw_polygon.point_list) {
            pt.y *= -1.0f;
        }
        for (auto &pt : obs_data.m_cvw_polygon.point_list) {
            pt.y *= -1.0f;
        }
    }

}

} // namespace bsd
} // namespace active_safety
