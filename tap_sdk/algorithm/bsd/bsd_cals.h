#pragma once
#include <vector>

namespace active_safety {
namespace bsd {
struct BsdCal {
    float k_lcda_min_track_age              = 0.1f;
    float k_bsw_alert_track_age             = 0.5f;
    float k_lcda_max_range                  = -80.0f;
    float k_lcda_exp_avg_filter_constant    = 0.8f;
    float k_lcda_bsw_zone_hys_x             = 0.5f;
    float k_lcda_bsw_zone_hys_y             = 0.2f;
    float k_lcda_cvw_zone_hys_x             = 1.0f;
    float k_lcda_cvw_zone_hys_y             = 0.2f;
    float k_lcda_cvw_max_zone_thres         = 70.0f;
    float k_bsw_stag_vel                    = -4.1667f;
    float k_bsw_stag_vel_hys                = 0.5f;
    float k_bsw_stag_vel_hys_breaking       = 0.5f;
    float k_bsw_effective_lane_width_factor = 0.8f;
    float k_lcda_default_lane_width         = 3.5f;
    float k_cvw_ttc_long_calculation_offset = 0.0f;
    float k_cvw_candidate_ttc               = 11.0f;
    float k_cvw_distance_count_twice        = 40.0f;
    float k_cvw_closest_x_hys               = 0.5f;
    float k_cvw_effective_lane_width_factor = 0.6f;
    float k_bsw_max_heading_abs             = 0.785f;
    float k_cvw_max_heading                 = 0.262f;
    float k_cvw_min_obj_long_vel            = 1.4f;
    float k_bsw_min_obj_long_vel            = 1.4f;
    float k_lcda_min_longvel                = 2.0f;
    float k_lcda_min_enable_host_speed      = 4.17;
    float k_lcda_max_enable_host_speed      = 41.7;
    float k_lcda_min_enable_host_speed_hys  = 3.6;
    float k_lcda_max_enable_host_speed_hys  = 43.1;

    int k_bsw_min_cycles         = 1;
    int k_cvw_min_cycles         = 20;
    int k_lcda_hold_cycles       = 20;
    int k_lcda_step_time         = 20;  // ms
    int k_lcda_bsd_min_warn_time = 500; // ms

    bool k_bsw_uses_cvw_alert_state_enabled  = false;
    bool k_lcda_enable_obj_in_ego_lane_check = true;

    float k_lcda_front_axle_to_front_bumper = 1.0f;

    std::vector<float> k_lcda_origin_bsw_zone_x = {0.0f, -7.0f, -7.0f, 0.0f};
    std::vector<float> k_lcda_origin_bsw_zone_y = {0.0f, 0.0f, 3.0f, 3.0f};
};
} // namespace bsd
} // namespace active_safety