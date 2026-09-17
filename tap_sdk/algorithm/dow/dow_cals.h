#ifndef TAP_SDK_ALGORITHM_DOW_DOW_CALS_H_
#define TAP_SDK_ALGORITHM_DOW_DOW_CALS_H_
#include <array>
#include <vector>

namespace active_safety {
namespace dow {

struct DowCal {
    bool k_dow_debug_log_enable = false;  // 是否启用DOW回灌调试(调试信息记录+DumpDebugFrame打印)，数值：false
    // Selection Calibrations (from AsDowCal)
    uint8_t k_dow_number_cycle_hold_critical_level              = 10;   // 报警保持周期数，数值：10 //未使用
    uint8_t k_dow_number_cycle_qualify_critical_level           = 1;    // 报警确认周期数，数值：1
    uint8_t k_dow_zone_test_mode                                = 0;    // 区域测试模式开关，数值：0
    uint8_t k_dow_coasted_targets_exclude                       = 1;    // 是否排除推测目标，数值：1 //未使用
    uint8_t k_dow_min_stage_age_mature                          = 2;    // 目标成熟最小阶段年龄，数值：2 //未使用
    uint8_t k_dow_moving_average_window_size                    = 3;    // 移动平均窗口大小，数值：3 //未使用
    uint8_t k_dow_enable_moving_average                         = 1;    // 移动平均使能开关，数值：1 //未使用
    uint8_t k_dow_check_obstruction_probability_signal          = 0;    // 遮挡概率信号检查开关，数值：0 //未使用
    uint8_t k_dow_enable_second_level_warning                   = 0;    // 二级报警使能开关，数值：0 //未使用
    uint8_t k_dow_check_target_position                         = 1;    // 目标位置检查开关，数值：1 //未使用
    uint8_t k_dow_enable_path_tracking                          = 0;    // 路径跟踪使能开关，数值：0 //未使用
    uint8_t k_dow_tracker_calculated_heading                    = 0;    // 使用跟踪器计算航向开关，数值：0 //未使用
    float   k_dow_existence_probability_min                     = 0.5F; // 目标最小存在概率阈值，数值：0.5 //未使用
    float   k_dow_angle_velocity_vector_max                     = 60.0F;  // 速度矢量最大角度，数值：60.0 deg
    float   k_dow_distance_critical_level_max                   = 75.0F;  // 临界等级最大距离，数值：75.0 m
    float   k_dow_approaching_velocity_min                      = 1.375F;   // 最小接近速度，数值：1.375 m/s
    float   k_dow_target_long_velocity_min                      = 1.375F; // 目标最小纵向速度，数值：1.375 m/s
    float   k_dow_target_lat_velocity_max                       = 10.0F;  // 目标最大横向速度，数值：10.0 m/s
    float   k_dow_ttc_critical_level_max                        = 2.0F;   // 临界等级最大TTC，数值：2.0 s //未使用
    float   k_dow_intersection_point_lat_critical_level_max     = 2.5F;   // 交叉点横向最大距离，数值：2.5 m
    float   k_dow_intersection_point_lat_critical_level_min     = -0.5F;  // 交叉点横向最小距离，数值：-0.5 m
    float   k_dow_lateral_position_max                          = 4.0F;   // 最大横向位置，数值：4.0 m //未使用
    float   k_dow_crash_line_long                               = -1.0F;  // 碰撞线纵向位置，数值：-1.0 m
    float   k_dow_ttc_hysteresis                                = 0.3F;   // TTC迟滞值，数值：0.3 s //未使用
    float   k_dow_intersection_hysteresis                       = 0.5F;   // 交叉点迟滞值，数值：0.5 m
    float   k_dow_auto_mode_lateral_distance_max                = 3.0F;   // 自动模式最大横向距离，数值：3.0 m //未使用
    float   k_dow_max_vcs_long_posn_mature                      = 0.0F;   // 成熟目标最大纵向位置，数值：0.0 m //未使用
    float   k_dow_min_obstruction_probability                   = 0.8F;   // 最小遮挡概率阈值，数值：0.8 //未使用
    float   k_dow_first_warning_ttc_threshold                   = 0.0F;   // 一级报警TTC阈值，数值：0.0 s //未使用
    float   k_dow_second_warning_ttc_threshold                  = 0.0F;   // 二级报警TTC阈值，数值：0.0 s //未使用
    float   k_dow_ds_zone_lat_dis_max                           = 10.0F;  // 检测区域最大横向距离，数值：10.0 m //未使用
    float   k_dow_ds_zone_long_dis_max                          = 5.0F;   // 检测区域最大纵向距离，数值：5.0 m //未使用
    float   k_dow_ds_zone_long_dis_min                          = -80.0F; // 检测区域最小纵向距离，数值：-80.0 m //未使用
    float   k_dow_object_min_dist_to_crash_line_for_path_match  = 10.0F;  // 路径匹配时目标到碰撞线最小距离，数值：10.0 m //未使用
    std::array<float, 4> k_dow_warning_zone_long                = {2.68F, -24.6F, -24.6F, 2.68F}; // 报警区域纵向坐标，数值：{2.68, -24.6, -24.6, 2.68} m
    std::array<float, 4> k_dow_warning_zone_lat                 = {2.4625F, 2.4625F, 0.8F, 0.8F}; // 报警区域横向坐标，数值：{2.4625, 2.4625, 0.8, 0.8} m

    // Dynamic Zone Calibrations
    uint8_t k_dow_dynamic_zone_enabled                          = 0;    // 动态区域使能开关，数值：0 //未使用
    float   k_dow_dynamic_zone_ttc                              = 4.0F; // 动态区域TTC阈值，数值：4.0 s //未使用
    std::array<float, 2> k_dow_dynamic_zone_object_speed        = {1.0F, 2.78F};              // 动态区域目标速度范围，数值：{1.0, 2.78} m/s //未使用
    std::array<float, 4> k_dow_dynamic_zone_long                = {-1.0F, -7.7F, -7.7F, -1.0F}; // 动态区域纵向坐标，数值：{-1.0, -7.7, -7.7, -1.0} m //未使用

    // FTM Calibrations
    bool    k_dow_ftm_enable_flag                               = 0;      // FTM功能使能开关，数值：0
    uint8_t k_dow_ftm_number_cycle_hold_critical_level          = 10;     // FTM报警保持周期数，数值：10 //未使用
    uint8_t k_dow_ftm_number_cycle_qualify_critical_level       = 3;      // FTM报警确认周期数，数值：3 //未使用
    uint8_t k_dow_ftm_zone_test_mode                            = 0;      // FTM区域测试模式开关，数值：0 //未使用
    float   k_dow_ftm_existence_probability_min                 = 0.5F;   // FTM目标最小存在概率阈值，数值：0.5 //未使用
    float   k_dow_ftm_angle_velocity_vector_max                 = 1.05F;  // FTM速度矢量最大角度，数值：1.05 rad
    float   k_dow_ftm_distance_critical_level_max               = 25.0F;  // FTM临界等级最大距离，数值：25.0 m
    float   k_dow_ftm_approaching_velocity_min                  = 1.0F;   // FTM最小接近速度，数值：1.0 m/s //未使用
    float   k_dow_ftm_target_long_velocity_min                  = 1.0F;   // FTM目标最小纵向速度，数值：1.0 m/s //未使用
    float   k_dow_ftm_target_lat_velocity_max                   = 10.0F;  // FTM目标最大横向速度，数值：10.0 m/s //未使用
    float   k_dow_ftm_ttc_critical_level_max                    = 3.0F;   // FTM临界等级最大TTC，数值：3.0 s
    float   k_dow_ftm_intersection_point_lat_critical_level_max = 2.5F;   // FTM交叉点横向最大距离，数值：2.5 m
    float   k_dow_ftm_intersection_point_lat_critical_level_min = 0.5F;   // FTM交叉点横向最小距离，数值：0.5 m
    float   k_dow_ftm_crash_line_long                           = 1.0F;   // FTM碰撞线纵向位置，数值：1.0 m
    float   k_dow_ftm_ttc_hysteresis                            = 0.2F;   // FTM TTC迟滞值，数值：0.2 s
    float   k_dow_ftm_intersection_hysteresis                   = 0.5F;   // FTM交叉点迟滞值，数值：0.5 m
    std::array<float, 4> k_dow_ftm_warning_zone_long     = {0.0F, 40.0F, 40.0F, 0.0F}; // FTM报警区域纵向坐标，数值：{0.0, 40.0, 40.0, 0.0} m
    std::array<float, 4> k_dow_ftm_warning_zone_lat      = {3.4F, 3.4F, 1.0F, 1.0F};   // FTM报警区域横向坐标，数值：{3.4, 3.4, 1.0, 1.0} m

    // Control Calibrations (from AsDowCtrlCal)
    float   k_dow_min_warn_time                  = 0.5F;   // 最小报警持续时间，数值：0.5 s
    float   k_dow_max_warn_time                  = 10.0F;  // 最大报警持续时间，数值：10.0 s
    float   k_dow_min_run_time_powerdown         = 180.0F; // 下电前最小运行时间，数值：180.0 s //待开发验证
    float   k_dow_active_vehspd_max              = 1.39F;  // 功能激活最大车速，数值：1.39 m/s
    float   k_dow_deactive_vehspd_max            = 1.67F;  // 功能退出最大车速，数值：1.67 m/s
    float   k_dow_first_warn_level_ttc_thres     = 2.5F;   // 一级报警TTC阈值，数值：2.5 s
    float   k_dow_first_warn_level_ttc_thres_hys = 2.7F;   // 一级报警TTC迟滞阈值，数值：2.7 s

    // Common
    float k_dow_step_time = 0.02F; // 算法执行步长时间，数值：0.02 s

    float   k_dow_stationary_speed_thres = 0.9F;   // 静止目标速度判定阈值，数值：0.9 m/s
    float   k_dow_min_target_width       = 0.1F;   // 目标最小有效宽度，数值：0.1 m
    float   k_dow_late_check_ttc_min     = 0.2F;   // 迟报警判定TTC下限，数值：0.2 s
    uint8_t k_dow_cycle_cnt_max          = 255;    // 报警确认周期计数上限，数值：255
    float   k_dow_ttc_dist_invalid_init  = 1000.0F;// 寻找威胁时TTC/距离的无效初始值，数值：1000.0
    float   k_dow_side_judge_tolerance     = 0.01F;  // 左右侧判定的横向位置容差，数值：0.01 m
};

} // namespace dow
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_DOW_DOW_CALS_H_
