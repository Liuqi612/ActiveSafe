#pragma once
#include <array>
#include <cstdint>
#include <vector>

namespace active_safety {
namespace rcw {

struct RcwWarnLevel {
    float                min_crash_prob;
    float                min_ttc_threshold;
    uint8_t              hold_cycles;
    std::array<float, 5> ttc_lookuptable;
    uint8_t              suppress_cycles;
    bool                 should_coasting_be_allowed;
    uint8_t              max_warn_cycles;
};

struct RcwCal {
    int   k_recw_MinObjectAge                       = 5;
    bool  enable_ttc_dependent_std_factor           = true;
    bool  enable_heading_filter                     = false;
    bool  enable_pos_diff_rel_vel                   = false;
    float k_recw_MaxRelativeSpeedPreCrash           = 40.0f;
    float k_recw_MinRelativeSpeedPreCrash           = 2.77f;
    float k_recw_MinRelativeSpeedPreCrashHysteresis = 0.83f;
    float k_recw_MaxApproachAngle                   = 0.53f;
    float k_recw_MaxApproachAngleHysteresis         = 0.27f;
    float k_recw_lane_filter_width                  = 2.0f;
    float k_recw_lane_width_slope                   = 0.03f;
    int   k_recw_lane_filter_num_consecutive_cycles = 10;
    float k_recw_AverageSensorLatency               = 0.0f;
    bool  k_recw_f_apply_lane_filter                = true;
    float k_recw_max_object_width_warn_on           = 5.0f;
    float k_max_allowed_rel_vel_long_diff           = 1.0f;
    float k_recw_FactorEgoWidth                     = 0.8f;
    float k_recw_ttc_acute_alert                    = 0.3f;
    float k_recw_thresh_velocity_long_for_max_ttc   = 8.33f;
    float k_recw_minCpDebouncingThres               = 0.0f;
    int   k_recw_minNumberOfCpDebouncingCycles      = 0;

    std::array<float, 5>                k_recw_BreakTrkAbsSpeed = {0.0f, 25.0f, 50.0f, 75.0f, 100.0f};
    std::array<float, 6>                k_recw_breakDecel       = {0.0f, 2.0f, 5.0f, 8.0f, 9.0f, 13.0f};
    std::array<std::array<float, 6>, 5> k_recw_PrBreakDecel     = {{{{0.0f, 0.2f, 0.5f, 0.95f, 0.99f, 1.0f}},
                                                                {{0.0f, 0.2f, 0.5f, 0.95f, 0.99f, 1.0f}},
                                                                {{0.0f, 0.2f, 0.5f, 0.95f, 0.99f, 1.0f}},
                                                                {{0.0f, 0.2f, 0.5f, 0.95f, 0.99f, 1.0f}},
                                                                {{0.0f, 0.2f, 0.5f, 0.95f, 0.99f, 1.0f}}}};

    std::array<float, 5>                k_recw_SteerTrkAbsSpeed = {0.0f, 25.0f, 50.0f, 75.0f, 100.0f};
    std::array<float, 6>                k_recw_steerAccel       = {0.0f, 1.3f, 4.0f, 8.0f, 10.0f, 13.0f};
    std::array<std::array<float, 6>, 5> k_recw_PrSteerAccel     = {{{{0.0f, 0.2f, 0.5f, 0.95f, 0.99f, 1.0f}},
                                                                {{0.0f, 0.2f, 0.5f, 0.95f, 0.99f, 1.0f}},
                                                                {{0.0f, 0.2f, 0.5f, 0.95f, 0.99f, 1.0f}},
                                                                {{0.0f, 0.2f, 0.5f, 0.95f, 0.99f, 1.0f}},
                                                                {{0.0f, 0.2f, 0.5f, 0.95f, 0.99f, 1.0f}}}};

    std::array<float, 5> k_recw_RelVelocity = {0.0f, 2.8f, 5.6f, 8.3f, 10.0f};

    std::array<RcwWarnLevel, 2> warn_level = {
        {{0.4f, 0.0f, 6, {0.0f, 0.47f, 0.94f, 2.5f, 2.5f}, 0, true, 60}, {0.8f, 0.0f, 6, {0.0f, 0.0f, 0.2f, 0.3f, 0.3f}, 0, true, 60}}};

    // std::array<RcwWarnLevel, 2> warn_level = {
    //     {{0.1f, 0.0f, 6, {0.0f, 2.0f, 2.0f, 2.5f, 2.5f}, 0, true, 60}, {0.1f, 0.0f, 6, {0.0f, 0.8f, 1.2f, 1.2f, 1.2f}, 0, true, 60}}};

    float k_rcw_max_enable_speed = 150.0f / 3.6f;
    float k_rcw_inhibit_speed    = 155.0f / 3.6f;
    float k_rcw_step_time        = 0.05f;

    // 报警时间限制和冷却时间
    float k_rcw_alert_time_max = 3.0f;   // 最长报警时间: 3秒
    float k_rcw_freezing_time  = 20.0f;  // 冷却时间: 20秒
};

} // namespace rcw
} // namespace active_safety
