#ifndef TAP_SDK_ALGORITHM_LKA_LKA_CALS_H_
#define TAP_SDK_ALGORITHM_LKA_LKA_CALS_H_

#include <array>
#include <cstdint>

namespace active_safety {
namespace lka {

struct LkaCal {
    // 抑制条件阈值
    float k_yawrate_inhibit_on_rps = 0.25F;
    float k_yawrate_inhibit_off_rps = 0.20F;
    float k_yawrate_inhibit_on_delay_s = 0.2F;
    float k_yawrate_inhibit_off_delay_s = 0.6F;

    float k_brake_pressure_inhibit_pa = 1000.0F;
    float k_brake_inhibit_off_delay_s = 1.0F;

    float k_accel_pedal_rate_inhibit_pct = 300.0F;
    float k_accel_inhibit_off_delay_s = 1.0F;

    float k_low_speed_accel_pedal_min_speed_kph = 40.0F; // 低速持续油门抑制生效的最低仪表车速，单位：km/h
    float k_low_speed_accel_pedal_max_speed_kph = 60.0F; // 低速持续油门抑制生效的最高仪表车速，单位：km/h
    float k_low_speed_accel_pedal_threshold_pct = 15.0F; // 低速持续油门抑制的油门开度阈值，单位：%
    float k_low_speed_accel_pedal_on_delay_s = 2.0F; // 油门和车速条件连续成立后进入抑制的延时，单位：s

    float k_steer_angle_inhibit_deg = 90.0F;
    float k_steer_angle_inhibit_off_delay_s = 0.8F;

    float k_steer_angle_rate_inhibit_degps = 80.0F;
    float k_steer_angle_rate_inhibit_off_delay_s = 0.5F;

    float k_hazard_inhibit_off_delay_s = 0.8F;

    float k_long_accel_inhibit_mpss = 5.0F;
    float k_long_accel_inhibit_off_delay_s = 0.5F;

    float k_gear_inhibit_off_delay_s = 0.5F;

    float k_hands_off_inhibit_on_nm = 0.3F;
    float k_hands_off_inhibit_off_nm = 0.2F;
    float k_hands_off_inhibit_on_delay_s = 0.2F;
    float k_hands_off_inhibit_off_delay_s = 0.3F;

    std::array<float, 7> k_LKA_ovrd_tq_thd_per_spd_x{40.0F, 60.0F, 84.0F, 108.0F, 132.0F, 156.0F, 180.0F}; // 手力矩接管阈值查表的仪表车速轴，单位：km/h
    std::array<float, 7> k_LKA_ovrd_tq_thd_per_spd_z{1.0F, 1.5F, 1.56F, 1.66F, 1.72F, 1.76F, 1.80F}; // 各车速点对应的驾驶员手力矩接管阈值，单位：Nm
    float k_LKA_DriHandsOvr_OnDlyTime = 0.02F; // 手力矩历史条件成立后进入接管抑制的延时，单位：s
    float k_LKA_DriHandsOvr_OffDlyTime = 1.0F; // 手力矩历史条件解除后保持接管抑制的延时，单位：s
    uint8_t k_LKA_DriHandsOvr_HistoryWindow = 10U; // 手力矩接管判定的历史统计窗口，单位：帧
    uint8_t k_LKA_DriHandsOvr_HistorySuppressCount = 6U; // 历史窗口内达到手力矩阈值即可判定接管的最少帧数，单位：帧

    uint8_t k_driver_intent_history_frame_count = 3U; // 综合驾驶意图分数需要连续满足阈值的帧数，单位：帧
    float k_driver_intent_score_threshold = 0.9F; // 综合驾驶意图抑制的归一化分数阈值，范围：0~1
    float k_driver_intent_steer_weight = 0.55F; // 综合驾驶意图中方向盘手力矩分数的权重
    float k_driver_intent_pedal_weight = 0.45F; // 综合驾驶意图中油门/制动踏板分数的权重
    float k_driver_intent_accel_pedal_threshold_pct = 30.0F; // 油门踏板分数达到1.0时对应的开度，单位：%
    float k_driver_intent_brake_pressure_threshold_bar = 12.0F; // 制动压力分数达到1.0时对应的压力，单位：bar
    float k_driver_intent_brake_pedal_threshold_pct = 20.0F; // 制动踏板分数达到1.0时对应的开度，单位：%
    float k_driver_intent_off_delay_s = 1.0F; // 综合驾驶意图条件解除后保持抑制的延时，单位：s

    float k_eps_available_inhibit_off_delay_s = 0.5F;

    // 使能条件阈值
    float k_speed_compensation_kph = 0.0F;
    float k_enable_min_speed_kph = 60.0F;
    float k_enable_max_speed_kph = 150.0F;
    float k_exit_min_speed_kph = 55.0F;
    float k_exit_max_speed_kph = 155.0F;
    float k_marker_valid_on_delay_s = 0.3F;

    float k_lane_curvature_valid_on = 0.005F;
    float k_lane_curvature_valid_off = 0.004F;

    float k_lane_width_min_on_m = 2.7F;
    float k_lane_width_min_off_m = 2.6F;
    float k_lane_width_max_on_m = 5.2F;
    float k_lane_width_max_off_m = 5.0F;

    // 回正判定阈值
    float k_centered_c0_abs_m = 0.20F;
    float k_centered_c1_abs = 0.015F;
    float k_centered_on_delay_s = 0.35F;

    // 左右干预触发阈值
    float k_intervention_boundary_maxdist_m = 0.3F;
    float k_intervention_boundary_mindist_m = -0.15F;
    float k_left_boundary_lat_rate_mps = 0.15F;
    float k_right_boundary_lat_rate_mps = -0.15F;
    float k_left_boundary_heading_deg = 1.5F;
    float k_right_boundary_heading_deg = -1.5F;
    float k_intervention_ttlc_s = 1.0F;
    float k_low_speed_intervention_ttlc_s = 0.65F; // 低速区间的 LKA 干预 TTLC 基础门限，单位：s
    float k_ttlc_low_speed_start_kph = 40.0F; // TTLC 低速门限策略的起始车速，低于该值保持低速门限，单位：km/h
    float k_ttlc_low_speed_end_kph = 60.0F; // TTLC 低速固定门限区间的结束车速，单位：km/h
    float k_ttlc_high_speed_recover_kph = 80.0F; // TTLC 门限线性恢复到标称值的车速，单位：km/h
    uint8_t k_ttlc_invalid_tolerance_frames = 2U; // TTLC 短时无效时允许保留原历史的最大连续帧数，单位：帧
    float k_left_lane_offset_m = -0.1F;
    float k_right_lane_offset_m = 0.1F;


    uint16_t k_enable_suppressed_mask = 0xC7EU; // bit1-6: 常规抑制，bit10: 手力矩接管，bit11: 综合驾驶意图
    uint16_t k_standby_enable_mask = 0x281U; // bit0: valid speed, bit7: 挡位 bit8: Handsoff bit9: EPS不可用


    // 中间态恢复阈值
    uint8_t k_abort_to_enable_cycle = 5U;
    uint8_t k_completed_to_enable_cycle = 5U;

    // 纠偏相关时序阈值
    float k_retrigger_suppressed_window_s = 5.0F;
    float k_intervention_abort_timeout_s = 6.0F;
};

} // namespace lka
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LKA_LKA_CALS_H_
