#pragma once
#include <array>
#include <vector>

namespace active_safety {
namespace dow {

struct DowCal {
    // Selection Calibrations (from AsDowCal)
    uint8_t k_dow_major_version                                 = 0;
    uint8_t k_dow_minor_version                                 = 0;
    uint8_t k_ced_number_cycle_hold_critical_level              = 10;
    uint8_t k_ced_number_cycle_qualify_critical_level           = 1;
    uint8_t k_ced_zone_test_mode                                = 1;
    uint8_t k_ced_dynamic_zone_enabled                          = 0;
    uint8_t k_ced_f_coasted_targets_exclude                     = 1;
    uint8_t k_ced_min_stage_age_mature                          = 2;
    uint8_t k_ced_moving_average_window_size                    = 3;
    uint8_t k_ced_f_enable_moving_average                       = 1;
    uint8_t k_ced_f_check_obstruction_probability_signal        = 0;
    bool    k_ced_ftm_enable_flag                               = 0;
    uint8_t k_ced_ftm_number_cycle_hold_critical_level          = 10;
    uint8_t k_ced_ftm_number_cycle_qualify_critical_level       = 3;
    uint8_t k_ced_ftm_zone_test_mode                            = 0;
    uint8_t k_ced_f_enable_second_level_warning                 = 0;
    uint8_t k_ced_f_check_target_position                       = 1;
    uint8_t k_ced_enable_path_tracking                          = 0;
    uint8_t k_ced_f_tracker_calculated_heading                  = 0;
    float   k_ced_scan_step_time                                = 0.05f;
    float   k_ced_existence_probability_min                     = 0.5f;
    float   k_ced_angle_velocity_vector_max                     = 60.0f;
    float   k_ced_distance_critical_level_max                   = 75.0f;
    float   k_ced_approaching_velocity_min                      = 1.0f;
    float   k_ced_target_long_velocity_min                      = 1.375f;
    float   k_ced_target_lat_velocity_max                       = 10.0f;
    float   k_ced_ttc_critical_level_max                        = 2.0f;
    float   k_ced_intersection_point_lat_critical_level_max     = 3.5f;
    float   k_ced_intersection_point_lat_critical_level_min     = -0.5f;
    float   k_ced_lateral_position_max                          = 4.0f;
    float   k_ced_crash_line_long                               = -1.0f;
    float   k_ced_ttc_hysteresis                                = 0.3f;
    float   k_ced_intersection_hysteresis                       = 0.5f;
    float   k_ced_auto_mode_lateral_distance_max                = 3.0f;
    float   k_ced_dynamic_zone_ttc                              = 4.0f;
    float   k_ced_max_vcs_long_posn_mature                      = 0.0f;
    float   k_ced_min_obstruction_probability                   = 0.8f;
    float   k_ced_ftm_existence_probability_min                 = 0.5f;
    float   k_ced_ftm_angle_velocity_vector_max                 = 1.05f;
    float   k_ced_ftm_distance_critical_level_max               = 25.0f;
    float   k_ced_ftm_approaching_velocity_min                  = 1.0f;
    float   k_ced_ftm_target_long_velocity_min                  = 1.0f;
    float   k_ced_ftm_target_lat_velocity_max                   = 10.0f;
    float   k_ced_ftm_ttc_critical_level_max                    = 3.0f;
    float   k_ced_ftm_intersection_point_lat_critical_level_max = 2.5f;
    float   k_ced_ftm_intersection_point_lat_critical_level_min = 0.5f;
    float   k_ced_ftm_crash_line_long                           = 1.0f;
    float   k_ced_ftm_ttc_hysteresis                            = 0.2f;
    float   k_ced_ftm_intersection_hysteresis                   = 0.5f;
    float   k_ced_first_warning_ttc_threshold                   = 0.0f;
    float   k_ced_second_warning_ttc_threshold                  = 0.0f;
    float   k_ced_ds_zone_lat_dis_max                           = 10.0f;
    float   k_ced_ds_zone_long_dis_max                          = 5.0f;
    float   k_ced_ds_zone_long_dis_min                          = -80.0f;
    float   k_ced_object_min_dist_to_crash_line_for_path_match  = 10.0f;

    std::array<float, 4> k_ced_warning_zone_long         = {-1.0f, -24.6f, -24.6f, -1.0f};
    std::array<float, 4> k_ced_warning_zone_lat          = {4.0f, 4.0f, 0.8f, 0.8f};
    std::array<float, 2> k_ced_dynamic_zone_object_speed = {1.0f, 2.78f};
    std::array<float, 4> k_ced_dynamic_zone_long         = {-1.0f, -7.7f, -7.7f, -1.0f};
    std::array<float, 4> k_ced_ftm_warning_zone_long     = {0.0f, 40.0f, 40.0f, 0.0f};
    std::array<float, 4> k_ced_ftm_warning_zone_lat      = {3.4f, 3.4f, 1.0f, 1.0f};

    // Control Calibrations (from AsDowCtrlCal)
    int32_t k_dow_min_warn_time                  = 500;
    int32_t k_dow_max_warn_time                  = 10000;
    float   k_dow_max_enable_host_spd            = 2.0f;
    float   k_dow_first_warn_level_ttc_thres     = 2.5f;
    float   k_dow_first_warn_level_ttc_thres_hys = 2.7f;

    // Common
    float k_dow_step_time = 0.05f;
};

} // namespace dow
} // namespace active_safety
