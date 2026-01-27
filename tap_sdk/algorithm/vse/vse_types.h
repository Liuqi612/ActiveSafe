/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
namespace active_safety {

#define His_State_Num        250
#define His_State_Num_Output 20

struct AsVseCal {
    uint8_t vse_major_version = 0;
    uint8_t vse_minor_version = 0;
    uint8_t vse_field_version = 0;

    float k_vse_step_time                              = 0.01;
    float k_yawrate_filter_gain                        = 0.05f;
    float k_min_yawrate_delta                          = 0.005f;
    float k_speed_filter_gain                          = 1;
    float k_steer_angle_rate_gain                      = 0.6065;
    float k_gas_pedal_rate_gain                        = 1;
    float k_brake_pedal_rate_gain                      = 1;
    float k_brake_press_rate_gain                      = 1;
    float k_min_speed_delta                            = 0;
    float k_max_speed_change_rate                      = 10.0f;  // 最大速度变化率 m/s^2
    float k_speed_accel_consistency_thresh             = 0.5f;    // 速度-加速度一致性阈值
    float k_speed_kalman_process_noise                 = 0.1f;    // 速度卡尔曼滤波过程噪声
    float k_speed_kalman_measure_noise                 = 1.0f;    // 速度卡尔曼滤波观测噪声
    float k_speed_fusion_weight_pred                   = 0.7f;    // 预测速度融合权重（当更新速度不一致时）
    float k_cal_curv_use_steering_speed_mps            = 1.389f;
    float k_cal_curv_use_yawrte_speed_mps              = 2.778f;
    float k_picth_compliance                           = 0.01f;
    float k_roll_compliance                            = 0.01f;
    float k_dist_based_curv_speed_thresh               = 0.05f;
    float k_dist_based_curv_discrete_distance_interval = 0.1f;
    float k_curv_kalman_gain_1                         = 0.5f;
    float k_curv_kalman_gain_2                         = 0.001f;
};

} // namespace active_safety
