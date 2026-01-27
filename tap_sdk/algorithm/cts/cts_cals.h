#pragma once
#include "math/geometry/geometry.h"

#include <array>
#include <vector>
#define CTS_MAX_LEVEL 5
#define CTS_MAX_SIDE 2
#define CTS_STEP_TIME 0.02f
namespace active_safety {
namespace cts {

struct ThresData {
    int level;
    int above_thres_cnt;
    float ttc_thres;
    float rad_dist_thres;
    float inter_sec_min;
    float inter_sec_max;
};

struct CtsCal {
    bool k_cta_f_use_heading_for_relative_velocity_calculation = false;
    bool k_cta_f_calc_ttc_ego_side_enabled = true;
    float k_cta_stop_alert_ttc = -6.0f;
    float k_cta_min_lat_posn_for_default_ref_point = 5.0f;
    float k_cta_distance_to_rear_bumper = 1.0f;
    bool k_cta_f_use_trailing_edge = false;
    float k_cta_ttc_threshold_offset_fcta_fast = 0.5f;
    float k_cta_ttc_threshold_offset_fcta_slow = 1.0f;
    float k_cta_speed_threshold_activate_fcta_ttc = 1.38f;
    float k_cta_speed_threshold_deactive_fcta_ttc = 1.67f;

    bool k_cta_f_check_stationary_signal = true;
    float k_cta_min_object_age_in_cycles = 0.2f;
    float k_cta_min_speed = 1.0f;
    float k_cta_min_speed_hys = 0.14f;
    float k_cta_min_lateral_approach_speed = 1.0f;
    float k_cta_cross_dist_max_lat_angle_diff = 0.52f;
    float k_cta_rel_warning_hysteresis = 0.3f;
    float k_cta_object_heading_filter_max_speed_thres = 1.5f;
    float k_cta_object_max_angle_diff = 0.5f;

    int k_cta_min_active_level = 1;
    int k_ctb_min_active_level = 4;
    float k_fcta_min_enable_host_speed = 0.55f;
    float k_fcta_max_enable_host_speed = 4.16f;
    float k_fcta_min_enable_host_speed_inhibit = 0.35f;
    float k_fcta_max_enable_host_speed_inhibit = 4.72f;

    float k_fctb_min_enable_host_speed = 0.55f;
    float k_fctb_max_enable_host_speed = 4.16f;
    float k_fctb_min_enable_host_speed_inhibit = 0.35f;
    float k_fctb_max_enable_host_speed_inhibit = 4.72f;

    float k_rcta_min_enable_host_speed = -4.16f;
    float k_rcta_max_enable_host_speed = -0.55f;
    float k_rcta_min_enable_host_speed_inhibit = -4.72f;
    float k_rcta_max_enable_host_speed_inhibit = -0.35f;

    float k_rctb_min_enable_host_speed = -4.16f;
    float k_rctb_max_enable_host_speed = -0.55f;
    float k_rctb_min_enable_host_speed_inhibit = -4.72f;
    float k_rctb_max_enable_host_speed_inhibit = -0.35f;

    float k_cts_strangle_inhibit_thrd = 100.0f;
    float k_cts_strangrt_inhibit_thrd = 200.0f;
    float k_cts_curvature_inhibit_thrd = 0.03f;
    float k_cts_brkpdl_inhibit_thrd = 15.0f;
    float k_cts_accpdl_inhibit_thrd = 30.0f;
    float k_cts_gas_pedal_rate_inhibit_thrd = 750.0f;
    float k_cts_common_inhibit_time = 3.0f;

    float k_cta_freezing_time = 20.0f;
    float k_cts_alert_time_thrd_max = 3.0f;

    int k_cts_hold_cycles = 50;

    // default for rcta
    std::vector<math::Point2D> k_cta_area = {{0.0, 0.0}, {-14.0, 0.0}, {-83.0, 50.0}, {26.0, 50.0}};
    std::array<ThresData, CTS_MAX_LEVEL> k_cta_thres_data = {ThresData{1, 3, 2.5, 100, -3.5, 1.5}, ThresData{2, 3, 1.65, 100, -3.5, 1.5},
                                                             ThresData{3, 3, 1.35, 100, -2.5, 1.0}, ThresData{4, 3, 1.0, 25, -2.5, 1.0},
                                                             ThresData{5, 3, 0.5, 15, -2.5, 1.0}};
};

} // namespace cts
} // namespace active_safety
