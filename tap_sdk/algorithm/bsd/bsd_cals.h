#ifndef TAP_SDK_ALGORITHM_BSD_BSD_CALS_H_
#define TAP_SDK_ALGORITHM_BSD_BSD_CALS_H_
#include <vector>

namespace active_safety {
namespace bsd {
struct BsdCal {
    bool k_bsd_debug_log_enable = false;                // 是否启用BSD回灌调试(调试信息记录+DumpDebugFrame打印)，数值：false
    float k_bsd_min_track_age = 0.1F;                   // 目标最小跟踪时长阈值，数值：0.1 s
    float k_bsw_alert_track_age = 0.5F;                 // BSW报警目标跟踪时长阈值，数值：0.5 s
    float k_bsd_max_range = -80.0F;                     // 目标最大纵向检测距离，数值：-80.0 m
    float k_bsd_exp_avg_filter_constant = 0.8F;         // 指数平均滤波常数，数值：0.8
    float k_bsd_bsw_zone_hys_x = 1.0F;                  // BSW区域纵向迟滞，数值：1.0 m
    float k_bsd_bsw_zone_hys_y = 0.2F;                  // BSW区域横向迟滞，数值：0.2 m
    float k_bsd_cvw_zone_hys_x = 1.0F;                  // CVW区域纵向迟滞，数值：1.0 m
    float k_bsd_cvw_zone_hys_y = 0.2F;                  // CVW区域横向迟滞，数值：0.2 m
    float k_bsd_cvw_max_zone_thres = 70.0F;             // CVW区域最大纵向范围，数值：70.0 m
    float k_bsw_stag_vel = -4.1667F;                    // BSW静止目标相对速度阈值，数值：-4.1667 m/s
    float k_bsw_stag_vel_hys = 0.5F;                    // BSW静止目标速度迟滞-恢复，数值：0.5 m/s
    float k_bsw_stag_vel_hys_breaking = 0.5F;           // BSW静止目标速度迟滞-制动，数值：0.5 m/s
    float k_bsw_effective_lane_width_factor = 0.8F;     // BSW有效车道宽度系数，数值：0.8
    float k_bsd_default_lane_width = 3.5F;              // 默认车道宽度，数值：3.5 m
    float k_cvw_ttc_long_calculation_offset = 0.0F;     // CVW TTC纵向计算偏移量，数值：0.0 m
    float k_cvw_candidate_ttc = 11.0F;                  // CVW候选目标TTC阈值，数值：11.0 s
    float k_cvw_active_ttc = 3.5F;                      // CVW激活TTC阈值，数值：3.5 s
    float k_cvw_deactive_ttc = 3.7F;                    // CVW去激活TTC阈值，数值：3.7 s
    float k_cvw_distance_count_twice = 40.0F;           // CVW远距离目标双倍计数距离阈值，数值：40.0 m
    float k_cvw_closest_x_hys = 0.5F;                   // CVW最近目标纵向迟滞，数值：0.5 m
    float k_cvw_effective_lane_width_factor = 0.6F;     // CVW有效车道宽度系数，数值：0.6
    float k_bsw_max_heading_abs = 0.785F;               // BSW目标最大航向角绝对值，数值：0.785 rad
    float k_cvw_max_heading = 0.262F;                   // CVW目标最大航向角，数值：0.262 rad
    float k_cvw_min_obj_long_vel = 0.84F;               // CVW目标最小纵向速度，数值：0.84F m/s
    float k_bsw_min_obj_long_vel = 0.84F;               // BSW目标最小纵向速度，数值：0.84F m/s
    float k_bsw_min_longvel_active = -4.16F;            // BSW激活最小纵向相对速度，数值：-4.16F m/s
    float k_bsw_min_longvel_deactive = -3.61F;          // BSW去激活最小纵向相对速度，数值：-3.61F m/s
    float k_bsd_min_enable_host_speed = 2.78F;          // 功能使能最小自车速度，数值：2.78 m/s
    float k_bsd_max_enable_host_speed = 41.67F;         // 功能使能最大自车速度，数值：41.67 m/s
    float k_bsd_min_enable_host_speed_hys = 2.5F;       // 功能使能最小自车速度迟滞，数值：2.5 m/s
    float k_bsd_max_enable_host_speed_hys = 43.06F;     // 功能使能最大自车速度迟滞，数值：43.06 m/s
    float k_bsd_FLine_y = 0.5F;                         // 区域横向F线偏移量，数值：0.5 m

    int k_bsw_min_cycles = 1;                           // BSW区域内最小持续周期数，数值：1
    int k_cvw_min_cycles = 20;                          // CVW区域内最小持续周期数，数值：20
    float k_bsd_step_time = 0.02F;                      // 单步时间，数值：0.02 s
    float k_bsw_min_warn_time = 1.0F;                   // BSD最小报警持续时间，数值：1.0 s

    bool k_bsw_uses_cvw_alert_state_enabled = false;    // BSW是否使用CVW报警状态，数值：false
    bool k_bsd_enable_obj_in_ego_lane_check = true;     // 是否启用自车道内目标检查，数值：true

    float k_bsd_front_axle_to_front_bumper = 1.0F;      // 前轴到前保险杠距离，数值：1.0 m

    float k_bsd_stationary_speed_thres = 0.9F;          // 静止目标速度判定阈值，数值：0.9 m/s
    float k_bsd_filter_init_tolerance = 1.0F;           // 曲线滤波器未初始化判定容差(相对 m_inf)，数值：1.0 m/s
    float k_bsd_default_ttc = 25.0F;                    // CVW默认TTC值，数值：25.0 s


    std::vector<float> k_bsd_origin_bsw_zone_x = {0.0F, -7.0F, -7.0F, 0.0F};           // BSW区域纵向坐标，数值：{0.0, -7.0, -7.0, 0.0} m
    std::vector<float> k_bsd_origin_bsw_zone_y = {0.0F, 0.0F, 3.0F, 3.0F};             // BSW区域横向坐标，数值：{0.0, 0.0, 3.0, 3.0} m
    std::vector<float> k_bsw_dynamic_zone_host_speed = {2.78F, 16.67F, 25.0F, 41.67F}; // BSW动态区域自车速度插值点，数值：{2.78, 16.67, 25.0, 41.67} m/s
    std::vector<float> k_bsw_dynamic_zone_x = {0.0F, 2.0F, 4.0F, 7.0F};                // BSW动态区域纵向扩展量，数值：{0.0, 2.0, 4.0, 7.0} m
    std::vector<float> k_bsw_curvature_radius_val = {125.0F, 250.0F, 500.0F};          // BSW曲率半径阈值，数值：{125.0, 250.0, 500.0} m
    std::vector<float> k_bsw_curvature_radius_rel_speed = {10.0F, 15.0F};              // BSW曲率半径对应相对速度阈值，数值：{10.0, 15.0} m/s
    std::vector<float> k_cvw_curvature_radius_val = {125.0F, 250.0F, 500.0F};          // CVW曲率半径阈值，数值：{125.0, 250.0, 500.0} m
    std::vector<float> k_cvw_curvature_radius_rel_speed = {10.0F, 15.0F};              // CVW曲率半径对应相对速度阈值，数值：{10.0, 15.0} m/s
    std::vector<float> k_cvw_curvature_radius_ttc = {2.5F, 3.0F, 3.5F};                // CVW曲率半径对应TTC阈值，数值：{2.5, 3.0, 3.5} s
};
} // namespace bsd
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_BSD_BSD_CALS_H_
