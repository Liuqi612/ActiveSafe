#ifndef TAP_SDK_ALGORITHM_CTS_CTS_CALS_H_
#define TAP_SDK_ALGORITHM_CTS_CTS_CALS_H_
#include "math/geometry/geometry.h"

#include <array>
#include <vector>
#define CTS_MAX_LEVEL 5
#define CTS_MAX_SIDE 2
#define CTS_STEP_TIME 0.02F
namespace active_safety {
namespace cts {

struct ThresData {
    int level;            // 告警等级
    int above_thres_cnt;  // 超过阈值的连续帧计数
    float ttc_thres;      // TTC（碰撞时间）阈值，单位：s
    float rad_dist_thres; // 径向距离阈值，单位：m
    float inter_sec_min;  // 交叉区域重叠量最小值，单位：m
    float inter_sec_max;  // 交叉区域重叠量最大值，单位：m
};

struct CtsCal {
    bool k_cts_debug_log_enable = false;                              // 是否启用CTS回灌调试(调试信息记录+DumpDebugFrame打印)，数值：false
    bool k_cta_use_heading_for_relative_velocity_calculation = false; // 是否使用目标航向角计算相对速度，数值：false
    bool k_cta_calc_ttc_ego_side_enabled = true;                      // 是否启用从自车侧计算TTC，数值：true
    float k_cta_stop_alert_ttc = -6.0F;                                 // 未使用，数值：-6.0 s
    float k_cta_min_lat_posn_for_default_ref_point = 5.0F;              // 默认参考点的最小横向位置，数值：5.0 m
    float k_cta_distance_to_rear_bumper = 1.0F;                         // 自车后保险杠到参考点的距离，数值：1.0 m
    bool k_cta_use_trailing_edge = false;                             // 是否使用目标后沿作为参考点，数值：false
    float k_cta_ttc_threshold_offset_fcta_fast = 0.5F;                  // FCTA快速场景TTC阈值偏移量，数值：0.5 s
    float k_cta_ttc_threshold_offset_fcta_slow = 1.0F;                  // FCTA慢速场景TTC阈值偏移量，数值：1.0 s
    float k_cta_speed_threshold_activate_fcta_ttc = 1.38F;              // 激活FCTA TTC模式的目标速度阈值，数值：1.38 m/s
    float k_cta_speed_threshold_deactive_fcta_ttc = 1.67F;              // 退出FCTA TTC模式的目标速度阈值，数值：1.67 m/s

    bool k_cta_check_stationary_signal = true;                        // 是否检查目标静止信号，数值：true
    float k_cta_min_object_age_in_cycles = 0.2F;                        // 目标最小存在时长，数值：0.2 s
    float k_cta_min_object_age_for_diagonal_tgt = 1.0F;                 // 斜向目标的最小存在时长，数值：1.0 s
    float k_cta_min_speed = 1.0F;                                       // 目标触发告警的最小速度，数值：1.0 m/s
    float k_cta_min_speed_hys = 0.14F;                                  // 目标速度判断的迟滞量，数值：0.14 m/s
    float k_cta_min_lateral_approach_speed = 1.0F;                      // 目标最小横向接近速度，数值：1.0 m/s
    float k_cta_cross_dist_max_lat_angle_diff = 0.52F;                  // 交叉距离计算允许的最大横向角度差，数值：0.52 rad
    float k_cta_rel_warning_hysteresis = 0.3F;                          // 相对告警等级切换的迟滞量，数值：0.3 s
    float k_cta_object_heading_filter_max_speed_thres = 1.5F;           // 目标航向滤波生效的最大速度阈值，数值：1.5 m/s
    float k_cta_object_max_angle_diff = 0.5F;                           // 目标允许的最大角度差，数值：0.5 rad

    int k_cta_min_active_level = 1;                                     // CTA告警最小激活等级，数值：1
    int k_ctb_min_active_level = 4;                                     // CTB制动最小激活等级，数值：4
    float k_fcta_min_enable_host_speed = 0.27F;                         // FCTA使能的自车最小速度，数值：0.27 m/s
    float k_fcta_max_enable_host_speed = 2.78F;                         // FCTA使能的自车最大速度，数值：2.78 m/s
    float k_fcta_min_enable_host_speed_inhibit = 0.13F;                 // FCTA抑制使能的自车最小速度，数值：0.13 m/s
    float k_fcta_max_enable_host_speed_inhibit = 3.33F;                 // FCTA抑制使能的自车最大速度，数值：3.33 m/s

    float k_fctb_min_enable_host_speed = 1.11F;                         // FCTB使能的自车最小速度，数值：1.11 m/s
    float k_fctb_max_enable_host_speed = 2.78F;                         // FCTB使能的自车最大速度，数值：2.78 m/s
    float k_fctb_min_enable_host_speed_inhibit = 1.0F;                  // FCTB抑制使能的自车最小速度，数值：1.0 m/s
    float k_fctb_max_enable_host_speed_inhibit = 2.8F;                  // FCTB抑制使能的自车最大速度，数值：2.8 m/s

    float k_rcta_min_enable_host_speed = -4.17F;                        // RCTA使能的自车最小速度（负值表示倒车），数值：-4.17 m/s
    float k_rcta_max_enable_host_speed = 0.001F;                        // RCTA使能的自车最大速度，数值：0.001 m/s
    float k_rcta_min_enable_host_speed_inhibit = -4.73F;                // RCTA抑制使能的自车最小速度，数值：-4.73 m/s
    float k_rcta_max_enable_host_speed_inhibit = 0.001F;                // RCTA抑制使能的自车最大速度，数值：0.001 m/s

    float k_rctb_min_enable_host_speed = -4.17F;                        // RCTB使能的自车最小速度，数值：-4.17 m/s
    float k_rctb_max_enable_host_speed = -1.11F;                        // RCTB使能的自车最大速度，数值：-1.11 m/s
    float k_rctb_min_enable_host_speed_inhibit = -4.73F;                // RCTB抑制使能的自车最小速度，数值：-4.73 m/s
    float k_rctb_max_enable_host_speed_inhibit = -0.001F;               // RCTB抑制使能的自车最大速度，数值：-0.001F m/s

    float k_cts_strangle_inhibit_thrd = 100.0F;                         // 转向角抑制阈值，数值：100.0 deg
    float k_cts_strangrt_inhibit_thrd = 200.0F;                         // 转向角速率抑制阈值，数值：200.0 deg/s
    float k_cts_curvature_inhibit_thrd = 0.03F;                         // 道路曲率抑制阈值，数值：0.03 1/m
    float k_cts_brkpdl_inhibit_thrd = 15.0F;                            // 制动踏板开度抑制阈值，数值：15.0%
    float k_cts_accpdl_inhibit_thrd = 30.0F;                            // 油门踏板开度抑制阈值，数值：30.0%
    float k_cts_gas_pedal_rate_inhibit_thrd = 750.0F;                   // 油门踏板变化率抑制阈值，数值：750.0 %/s
    float k_cts_common_inhibit_time = 3.0F;                             // 公共抑制持续时间，数值：3.0 s
    float k_cts_default_spd = 4.1667F;                                  // 默认自车速度（无速度信号时使用），数值：4.1667 m/s

    float k_drv_continues_steer_ang_thres = 15.0F;                      // 驾驶员持续转向判断的转向角阈值，数值：15.0 deg
    float k_drv_continues_steer_ondly_time = 3.0F;                      // 驾驶员持续转向状态开启延迟时间，数值：3.0 s
    float k_drv_continues_steer_offdly_time = 2.0F;                     // 驾驶员持续转向状态关闭延迟时间，数值：2.0 s

    float k_drv_increase_steerangrate_thres = 9.0F;                     // 驾驶员增大转向判断的转向角速率阈值，数值：9.0 deg/s
    float k_drv_increase_steer_ondly_time = 0.6F;                       // 驾驶员增大转向状态开启延迟时间，数值：0.6 s
    float k_drv_increase_steer_offdly_time = 1.2F;                      // 驾驶员增大转向状态关闭延迟时间，数值：1.2 s

    float k_veh_decel_thres = 0.4F;                                     // 车辆减速度判断阈值，数值：0.4 g
    float k_veh_decel_ondly_time = 2.0F;                                // 车辆减速状态开启延迟时间，数值：2.0 s
    float k_veh_decel_offdly_time = 3.0F;                               // 车辆减速状态关闭延迟时间，数值：3.0 s

    float k_drv_want_brake_brkpdlpos_thres = 10.0F;                     // 驾驶员制动意图判断的制动踏板位置阈值，数值：10.0%
    float k_drv_want_brake_brkpdlpos_hys_thres = 8.0F;                  // 驾驶员制动意图判断的制动踏板位置迟滞阈值，数值：8.0%
    float k_drv_want_brake_brkpdlpos_ondly_time = 1.0F;                 // 驾驶员制动意图状态开启延迟时间，数值：1.0 s
    float k_drv_want_brake_brkpdlpos_offdly_time = 3.0F;                // 驾驶员制动意图状态关闭延迟时间，数值：3.0 s

    float k_cta_freezing_time = 20.0F;                                  // CTA告警冻结时间，数值：20.0 s
    float k_cts_alert_time_thrd_max = 3.0F;                             // 告警持续时间上限阈值，数值：3.0 s
    float k_cts_warn_min_hold_time = 1.0F;                              // 告警最小保持时间，数值：1.0 s
    int k_cts_hold_cycles = 30;                                         // 告警保持的最大周期数，数值：30

    // default for rcta
    float k_cts_default_long_area_pos = 6.0F;                           // RCTA默认纵向检测区域边界位置，数值：6.0 m

    std::vector<math::Point2D> k_cta_area = {{0.0, 0.0}, {-14.0, 0.0}, {-83.0, 50.0}, {26.0, 50.0}};                // CTA检测区域多边形顶点坐标，数值：{(0,0),(-14,0),(-83,50),(26,50)}
    std::vector<math::Point2D> k_cta_area_for_cross = {{0.0, 0.0}, {-6.0, 0.0}, {-6.0, 60.0}, {0.0, 60.0}};         // 交叉场景CTA检测区域多边形顶点坐标，数值：{(0,0),(-6,0),(-6,50),(0,50)}
    std::array<ThresData, CTS_MAX_LEVEL> k_cta_thres_data = {ThresData{1, 3, 2.5, 100, -3.5, 1.5}, ThresData{2, 3, 1.65, 100, -3.5, 1.5},
                                                             ThresData{3, 3, 1.35, 100, -2.5, 1.0}, ThresData{4, 3, 1.0, 25, -2.5, 1.0},
                                                             ThresData{5, 3, 0.5, 15, -2.5, 1.0}};                  // 各等级CTA告警阈值数据
    std::array<float, 5> k_fcta_inter_sec_max_correction_speed = {0.0F, 1.389F, 2.778F, 4.167F, 5.556F}; // 未使用，数值：{0.0, 1.389, 2.778, 4.167, 5.556} m/s
    std::array<float, 5> k_fcta_inter_sec_max_correction_x = {0.3F, 0.42F, 0.78F, 1.4F, 2.5F};           // 未使用，数值：{0.3, 0.42, 0.78, 1.4, 2.5}

    bool k_cta_inter_sec_max_correction_enabled = true;                 // 是否启用交叉区域重叠量最大值修正，数值：true

    // ---- 几何/风险计算阈值（cts_geometry.cpp / cts_risk_calc.cpp）----
    float k_cta_obs_envelope_buffer = 0.5F;        // 目标包络横向安全裕量，数值：0.5 m
    float k_cta_opposite_side_lat_thres = 0.7F;    // 对侧目标横向位置筛除阈值，数值：0.7 m
    float k_cta_default_lat_ttc = 60.0F;           // 横向TTC默认/上限值，数值：60.0 s
    float k_cta_intersect_inf = 1000.0F;           // 交叉点无穷大占位值，数值：1000.0 m
    float k_cta_steer_zone_shrink_factor = 0.25F;  // 转向时检测区域横向缩减系数，数值：0.25
    float k_cta_stationary_speed_thres = 0.9F;     // 静止目标速度判定阈值，数值：0.9 m/s
    float k_cta_path_truck_low_speed_thres = 2.778F; // 路径中卡车低速判定阈值(~10km/h)，数值：2.778 m/s
    float k_cta_path_truck_ns_heading_tol = 0.785F; // 路径中卡车朝向南北判定容差(±45°)，数值：0.785 rad
    float k_cta_path_truck_zone_extend = 1.5F;      // 路径中卡车走廊远端扩展距离(相对自车车身线)，数值：1.5 m
    float k_cta_cross_decel_offdly_time = 0.4F;    // 横向减速标志关闭延时，数值：0.4 s
    float k_cta_brake_zone_shrink_factor = 0.5F;   // 减速且驾驶员制动时区域缩减系数，数值：0.5
    float k_cta_continues_steer_shrink_factor = 0.8F; // 持续转向时区域缩减系数，数值：0.8
    float k_cta_long_steer_shrink_factor = 0.5F;   // 长时间持续转向额外缩减系数，数值：0.5
    float k_cta_cross_decel_shrink_factor = 0.3F;  // 横向减速目标区域缩减系数，数值：0.3
    float k_cta_overlap_check_lat_thres = 0.9F;    // 横向重叠校验位置阈值，数值：0.9 m
    float k_cta_yawrate_thres = 0.02F;             // 横摆角速度判定阈值，数值：0.02 rad/s
    float k_cta_visible_long_dist_thres = 5.0F;    // 可视范围纵向距离阈值，数值：5.0 m
    float k_cta_heading_dev_thres = 0.3F;          // 航向角与速度方向偏差阈值，数值：0.3 rad

    // 交叉区域重叠量最大值偏移量计算（cts_risk_calc.cpp CheckAllLevel）
    float k_cta_offset_reverse = 0.6F;             // 倒车时交叉区域偏移量，数值：0.6 m
    float k_cta_offset_speed_seg_thres = 4.167F;   // 偏移量计算分段速度阈值(~15km/h)，数值：4.167 m/s
    float k_cta_offset_high_speed_base = 1.09F;    // 高速段偏移量基值，数值：1.09 m
    float k_cta_offset_speed_coeff = 0.2F;         // 偏移量速度系数，数值：0.2
    float k_cta_offset_min = 0.3F;                 // 偏移量最小值，数值：0.3 m
    float k_cta_offset_margin = 0.3F;              // 偏移量附加裕量，数值：0.3 m
    float k_cta_offset_assumed_decel = 8.0F;       // 偏移量计算假设减速度，数值：8.0 m/s^2
    float k_cta_offset_kinematic_factor = 2.0F;    // 偏移量运动学因子(v^2/2a)，数值：2.0

    // 斜穿目标航向角区间（cts_risk_calc.cpp ValidObs）
    float k_cta_diag_front_heading_min = 2.1F;     // 前向斜穿目标航向角下限，数值：2.1 rad
    float k_cta_diag_front_heading_max = 2.9F;     // 前向斜穿目标航向角上限，数值：2.9 rad
    float k_cta_diag_rear_heading_min = 0.5F;      // 后向斜穿目标航向角下限，数值：0.5 rad
    float k_cta_diag_rear_heading_max = 1.04F;     // 后向斜穿目标航向角上限，数值：1.04 rad
    float k_cta_visible_diag_heading_min = 0.3F;   // 可视斜穿目标航向角下限，数值：0.3 rad
    float k_cta_visible_diag_heading_max = 1.0F;   // 可视斜穿目标航向角上限，数值：1.0 rad
    float k_cta_visible_azimuth_thres = m_pi / 6.0F; // 可视范围方位角阈值，数值：m_pi/6 rad (30°)

    // 驾驶员行为/状态机阈值（cts_state_machine.cpp）
    int   k_cts_steer_increase_cnt_thres = 5;      // 转向增大计数阈值，数值：5 cycle
    float k_cts_steer_rate_shrink_factor = 0.8F;   // 转向增大速率阈值缩减系数，数值：0.8
    int   k_cts_drv_brake_cnt_thres = 4;           // 驾驶员制动持续计数阈值，数值：4 cycle
    int   k_cts_continues_steer_cnt_thres = 100;   // 持续转向计数阈值，数值：100 cycle
    float k_cts_low_speed_hold_entry_thres = 0.5F; // 低速制动保持进入阈值，数值：0.5 m/s
    float k_cts_low_speed_hold_time = 2.0F;        // 低速制动保持时间，数值：2.0 s
    float k_cts_low_speed_brake_dec_req = -3.0F;   // 低速保持减速度请求值，数值：-3.0 m/s^2
    float k_cts_brake_dec_req = -8.0F;             // 常规制动减速度请求值，数值：-8.0 m/s^2

    // FCTA斜穿目标确认帧增加（自车直行 + 二轮车目标前提下）
    // |heading| <= 60°             ：额外 extra_max 帧（目标大致朝前，斜穿风险高）
    // |heading| ∈ (60°, 75°)      ：线性插值 extra_max → extra_min
    // |heading| ∈ [75°, 105°]     ：不增加（纯横向附近，正常确认帧足够）
    // |heading| ∈ (105°, 120°)    ：线性插值 extra_min → extra_max
    // |heading| >= 120°            ：额外 extra_max 帧（目标大致朝后，斜穿风险高）
    float k_fcta_diag_heading_low_thrd  = 1.047F; // 前向斜穿阈值，数值：1.047 rad (60 deg)
    float k_fcta_diag_heading_low_fade  = 1.309F; // 前向斜穿渐出阈值，数值：1.309 rad (75 deg)
    float k_fcta_diag_heading_high_fade = 1.833F; // 后向斜穿渐入阈值，数值：1.833 rad (105 deg)
    float k_fcta_diag_heading_high_thrd = 2.094F; // 后向斜穿阈值，数值：2.094 rad (120 deg)
    int   k_fcta_diag_extra_confirm_frames     = 25; // 两端满足时额外确认帧数，数值：25 frames
    int   k_fcta_diag_extra_confirm_frames_min = 10; // 渐变区边缘额外确认帧数，数值：10 frames
};

} // namespace cts
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_CTS_CTS_CALS_H_
