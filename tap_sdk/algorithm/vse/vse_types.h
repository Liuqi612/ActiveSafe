/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#ifndef TAP_SDK_ALGORITHM_VSE_VSE_TYPES_H_
#define TAP_SDK_ALGORITHM_VSE_VSE_TYPES_H_
#include <array>
#include <cstddef>
#include <cstdint>
namespace active_safety {

#define His_State_Num 250
#define His_State_Num_Output 20

struct AsVseCal {
    uint8_t vse_major_version = 0;
    uint8_t vse_minor_version = 0;
    uint8_t vse_field_version = 0;

    float k_vse_step_time = 0.01F;
    float k_yawrate_filter_gain = 0.05F;
    float k_min_yawrate_delta = 0.005F;
    float k_speed_filter_gain = 1;
    float k_steer_angle_rate_gain = 0.6065;
    float k_gas_pedal_rate_gain = 1;
    float k_brake_pedal_rate_gain = 1;
    float k_brake_press_rate_gain = 1;
    float k_min_speed_delta = 0;
    float k_max_speed_change_rate = 10.0F;         // 最大速度变化率 m/s^2
    float k_speed_accel_consistency_thresh = 0.5F; // 速度-加速度一致性阈值
    float k_speed_kalman_process_noise = 0.1F;     // 速度卡尔曼滤波过程噪声
    float k_speed_kalman_measure_noise = 1.0F;     // 速度卡尔曼滤波观测噪声
    float k_speed_fusion_weight_pred = 0.7F;       // 预测速度融合权重（当更新速度不一致时）
    float k_cal_curv_use_steering_speed_mps = 1.389F;
    float k_cal_curv_use_yawrte_speed_mps = 2.778F;
    float k_picth_compliance = 0.01F;
    float k_roll_compliance = 0.01F;
    float k_dist_based_curv_speed_thresh = 0.05F;
    float k_dist_based_curv_discrete_distance_interval = 0.1F;
    float k_curv_kalman_gain_1 = 0.5F;
    float k_curv_kalman_gain_2 = 0.001F;
};

} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_VSE_VSE_TYPES_H_
