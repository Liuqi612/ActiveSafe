#ifndef TAP_SDK_ALGORITHM_RCW_RCW_CALS_H_
#define TAP_SDK_ALGORITHM_RCW_RCW_CALS_H_
#include <array>
#include <cstdint>
#include <vector>

namespace active_safety {
namespace rcw {

struct RcwWarnLevel {
    float min_crash_prob;                // 最小碰撞概率阈值
    float min_ttc_threshold;             // 最小TTC阈值 (s)
    std::array<float, 5> ttc_lookuptable; // TTC查找表，对应不同相对速度下的TTC阈值
};

struct RcwCal {
    bool k_rcw_debug_log_enable = false;  // 是否启用RCW回灌调试(调试信息记录+DumpDebugFrame打印)，数值：false
    float k_rcw_ObjectAgeMin = 1.0F;       // 目标最小存在时间，数值：1.0 s
    int k_rcw_ego_stationary_thd = 5;     // 自车静止判断计数阈值，数值：5 cycles
    bool k_rcw_enable_ttc_dependent_std_factor = true;  // 是否启用TTC相关的标准差因子，数值：true
    bool k_rcw_enable_heading_filter = false;    // 是否启用航向角滤波，数值：false
    bool k_rcw_enable_pos_diff_rel_vel = false;  // 是否启用位置差分计算相对速度，数值：false
    float k_rcw_RelativeSpeedPreCrashMax = 40.0F;   // 碰撞前最大相对速度阈值，数值：40.0 m/s
    float k_rcw_RelativeSpeedPreCrashMin = 2.78F;   // 碰撞前最小相对速度阈值，数值：2.78 m/s
    float k_rcw_RelativeSpeedPreCrashForMovingMin = 5.6F;  // 运动目标碰撞前最小相对速度阈值，数值：5.6 m/s
    float k_rcw_RelativeSpeedPreCrashHysteresisMin = 0.5F; // 最小相对速度迟滞量，数值：0.5 m/s
    float k_rcw_ApproachAngleMax = 0.53F;           // 最大接近角阈值，数值：0.53 rad
    float k_rcw_ApproachAngleHysteresisMax = 0.27F; // 接近角迟滞量，数值：0.27F rad
    float k_rcw_lane_filter_width = 1.925F;   // 车道滤波宽度(半车道宽)，数值：1.925 m
    float k_rcw_lane_width_slope = 0.02F;     // 车道宽度随距离增长斜率，数值：0.02
    float k_rcw_valid_tar_ttc_thd_min = 2.0F; // 非vehicle目标参与排序的最小TTC阈值，数值：2.0 s
    float k_rcw_posnlgt_max = -0.5F;          // 目标最大纵向位置阈值(负值表示在自车后方)，数值：-0.5 m
    float k_rcw_lane_width_offset_max = 0.2F; // 车道宽度最大偏移量，数值：0.2 m
    int k_rcw_lane_filter_num_consecutive_cycles = 10; // 车道滤波连续周期数，数值：10S
    float k_rcw_AverageSensorLatency = 0.0F;  // 传感器平均延迟，数值：0.0 s
    bool k_rcw_apply_lane_filter = false;   // 是否应用车道滤波，数值：false
    float k_rcw_object_width_warn_on_max = 5.0F;  // 报警开启时目标最大宽度，数值：5.0 m
    float k_rcw_allowed_rel_vel_long_diff_max = 1.0F;  // 允许的最大纵向相对速度差，数值：1.0 m/s
    float k_rcw_FactorEgoWidth = 0.8F;        // 自车宽度缩放因子，数值：0.8
    float k_rcw_ttc_acute_alert = 0.3F;       // 紧急报警TTC阈值，数值：0.3 s
    float k_rcw_cross_vlat_min = 1.0F;        // 横穿目标最小横向速度，数值：1.0 m/s
    float k_rcw_decel_acccel_thres = -2.0F;   // 减速加速度阈值，数值：-2.0 m/s^2
    float k_rcw_thresh_velocity_long_for_ttc_max = 8.33F; // 用于最大TTC计算的纵向速度阈值，数值：8.33 m/s
    float k_rcw_pred_inpath_Hysteresis = 0.15F;   // 预测路径内判断迟滞量，数值：0.15 m
    float k_rcw_short_ttc_offdly_time = 2.0F;   // 短TTC关闭延迟时间，数值：2.0 s
    float k_rcw_vel_rel_min = 2.8F;           // 最小相对速度，数值：2.8 m/s
    float k_rcw_steerang_max = 60.0F;         // 最大方向盘转角阈值，数值：60.0 deg
    float k_rcw_steerang_host_speed_max = 4.17F; // 方向盘转角抑制对应的自车速度阈值，数值：4.17F m/s
    float k_rcw_enable_speed_max = 41.77F;  // RCW功能最大使能速度，数值：41.77 m/s
    float k_rcw_inhibit_speed_max = 43.06F;     // RCW功能抑制速度，数值：43.06 m/s
    float k_rcw_step_time = 0.02F;         // 算法步长时间，数值：0.02 s
    float k_rcw_alert_time_min = 0.5F;     // 最短报警时间，数值：0.5 s
    float k_rcw_alert_time_max = 3.0F;     // 最长报警时间，数值：3.0 s
    float k_rcw_freezing_time = 20.0F;     // 冷却时间，数值：20.0 s
    float k_rcw_ondelay_time = 0.2F;       // 报警开启延迟时间，数值：0.2 s
    float k_rcw_ttc_inhibit_thd = 0.3F;    // TTC抑制阈值(触发前TTC < 此值直接抑制)，数值：0.3 s

    // ---- 阈值标定（rcw_risk_calc.cpp / rcw_function.cpp / rcw_target_filter.cpp）----
    float k_rcw_crash_prob_min = 0.01F;          // 碰撞概率下限阈值，数值：0.01
    float k_rcw_default_ttc = 25.5F;             // 默认/上限TTC，数值：25.5 s
    float k_rcw_rel_vel_near_zero_thres = 0.1F;  // 相对速度近零判定阈值，数值：0.1 m/s
    float k_rcw_rel_acc_near_zero_thres = 0.1F;  // 相对加速度近零判定阈值，数值：0.1 m/s^2
    float k_rcw_brake_acc_at_zero_dist = -20.0F; // 近零距离制动加速度边界，数值：-20.0 m/s^2
    float k_rcw_steer_acc_at_zero_dist = 20.0F;  // 近零距离转向加速度边界，数值：20.0 m/s^2
    float k_rcw_short_ttc_thres_offset = 0.2F;   // 短TTC条件TTC阈值下调量，数值：0.2 s
    float k_rcw_ego_stationary_speed_thres = 0.5F; // 自车静止判定速度阈值，数值：0.5 m/s
    float k_rcw_moving_obj_speed_thres = 4.0F;   // 运动目标速度判定阈值，数值：4.0 m/s
    float k_rcw_min_obj_length = 1.0F;           // 目标最小有效长度，数值：1.0 m
    float k_rcw_bicycle_lat_pos_thres = 0.71F;   // 自行车横向位置阈值，数值：0.71 m
    float k_rcw_valid_last_pos_thres = 100.0F;   // 上周期位置有效性阈值，数值：100.0 m
    float k_rcw_filter_pos_diff_min = 0.01F;      // 航向滤波位置差最小有效阈值，数值：0.01 m
    int   k_rcw_heading_filter_cnt_max = 8;      // 航向滤波计数饱和上限，数值：8 cycle
    int   k_rcw_counter_max = 255;               // 计数器饱和上限，数值：255

    // 制动减速度查找表
    std::array<float, 6> k_rcw_breakDecel = {0.0F, 2.0F, 5.0F, 8.0F, 9.0F, 13.0F}; // 数值：{0.0, 2.0, 5.0, 8.0, 9.0, 13.0} m/s^2
    // 制动减速度对应的碰撞概率
    std::array<float, 6> k_rcw_PrBreakDecel = {0.0F, 0.2F, 0.5F, 0.95F, 0.99F, 1.0F}; // 数值：{0.0, 0.2, 0.5, 0.95, 0.99, 1.0}
    // 转向加速度查找表
    std::array<float, 6> k_rcw_steerAccel = {0.0F, 1.3F, 4.0F, 8.0F, 10.0F, 13.0F}; // 数值：{0.0, 1.3, 4.0, 8.0, 10.0, 13.0} m/s^2
    // 转向加速度对应的碰撞概率
    std::array<float, 6> k_rcw_PrSteerAccel = {0.0F, 0.2F, 0.5F, 0.95F, 0.99F, 1.0F}; // 数值：{0.0, 0.2, 0.5, 0.95, 0.99, 1.0}
    // 相对速度查找表，用于TTC阈值插值
    std::array<float, 5> k_rcw_RelVelocity = {0.0F, 2.8F, 5.6F, 8.3F, 10.0F}; // 数值：{0.0, 2.8, 5.6, 8.3, 10.0} m/s
    // 报警等级配置: [level1, level2]，数值：{{0.2, 0.0, {0.0,0.47,0.94,1.4,1.4}}, {0.4, 0.0, {0.0,0.27,0.64,1.1,1.2}}}
    std::array<RcwWarnLevel, 2> k_rcw_warn_level = {
        {{0.2F, 0.0F, {0.0F, 0.47F, 0.94F, 1.4F, 1.4F}}, {0.4F, 0.0F, {0.0F, 0.27F, 0.64F, 1.1F, 1.2F}}}};
    // std::array<RcwWarnLevel, 2> k_rcw_warn_level = {
    //     {{0.1F, 0.0F, 6, {0.0F, 2.0F, 2.0F, 2.5F, 2.5F}, 0, true, 60}, {0.1F, 0.0F, 6, {0.0F, 0.8F, 1.2F, 1.2F, 1.2F}, 0, true, 60}}};
    // 报警退出TTC查找表: [level1, level2]，对应不同相对速度下的退出TTC阈值，数值：{{0.0,0.67,1.14,1.6,1.6}, {0.0,0.47,0.84,1.3,1.4}} s
    std::array<std::array<float, 5>, 2> k_rcw_ttc_lookuptable_deactive = {{{0.0F, 0.67F, 1.14F, 1.6F, 1.6F}, {0.0F, 0.47F, 0.84F, 1.3F, 1.4F}}};
};

} // namespace rcw
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_RCW_RCW_CALS_H_
