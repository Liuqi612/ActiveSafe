/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#ifndef TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_ACTIVE_SAFETY_VSE_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_ACTIVE_SAFETY_VSE_H_
#include <cstddef>
#include <cstdint>

namespace senseAD {
namespace tap {
struct AsVseHeader {
  uint8_t vse_version_major;
  uint8_t vse_version_minor;
  uint16_t u16_vse_reserve01;
  uint32_t Start_timestamp_ms;
  uint32_t Start_timestamp_us_high;
  uint32_t Start_timestamp_us_low;
  uint32_t End_timestamp_ms;
  uint32_t End_timestamp_us_high;
  uint32_t End_timestamp_us_low;
};
struct AsVseSeries {
  uint64_t timestamp_ms[20];
  float yawrate_rps[20];
  float speed_mps[20];
  float slip_rad[20];
  float rear_position_long_m[20];
  float rear_position_lat_m[20];
  float heading_rad[20];
  float pitch_rad[20];
  float roll_rad[20];
};
struct AsVseOut {
  AsVseHeader vse_header;
  AsVseSeries state_series;
  float host_length;            // 车辆长度
  float host_width;             // 车辆宽度，不带后视镜
  float host_dist_to_front;     // 车辆后轴中心到前保距离
  float speed;                  // 车辆速度，m/s
  float display_speed;          // 车辆表显车速
  float yawrate;                // 横摆角速度, rad/s
  float yawrate_unfiltered_rps; // 未滤波的横摆角速度, rad/s
  float long_accel;             // 纵向加速度,m/s2
  float lat_accel;              // 横向加速度,m/s2
  float host_pitch_rad;         // 车辆pitch角
  float host_roll_rad;          // 车辆roll角
  float vcs_sideslip;           // 车辆vcs侧偏角
  float vcs_long_vel;           // 车辆vcs纵向速度,mps
  float vcs_lat_vel;            // 车辆vcs横向速度,mps
  float sensor_sideslip;
  float sensor_long_vel;
  float sensor_lat_vel;
  float rear_curvature;
  float rear_curvaturerate;
  float rear_curvature_radius;
  float rear_sideslip;
  float steerwheelangle;      // 方向盘转角，左正右负
  float steerwheelangle_rate; // 方向盘转角变化率，左正右负
  float slope_long_rad;
  float slope_lat_rad;
  float gas_pedal_pos;           // 加速踏板位置,[0-100]
  float brake_pedal_pos;         // 制动踏板位置,[0-100]
  float brake_pressure;          // 主缸压力
  float gas_pedal_pos_rate;      // 加速踏板位置变化率
  float brake_pedal_pos_rate;    // 制动踏板位置变化率
  float brake_pressure_rate;     // 主缸压力变化率
  float acc_brake_cmd;           // ACC请求减速度
  uint8_t hazard_lamp_st;        // 危险报警灯状态信号
  uint8_t front_fog_lamp_st;     // 前雾灯状态
  uint8_t back_fog_lamp_st;      // 后雾灯状态
  uint8_t left_light_fault_st;   // 左转向灯故障状态
  uint8_t right_light_fault_st;  // 右转向灯故障状态
  uint8_t epb_applied;           // EPB是否拉起
  uint8_t high_beam_st;          // 远光灯状态
  uint8_t vdc_active_st;         // VDC激活状态
  uint8_t tcs_active_st;         // TCS激活状态
  uint8_t hdc_active_st;         // HDC激活状态
  uint8_t esc_off_st;            // ESC关闭状态
  uint8_t fl_door_st;            // 左前车门状态信号
  uint8_t fr_door_st;            // 右前车门状态信号
  uint8_t rl_door_st;            // 左后车门状态信号
  uint8_t rr_door_st;            // 右后车门状态信号
  uint8_t turn_light_switch_pos; // 转向开关状态
  uint8_t left_light_st;         // 左转向状态信号
  uint8_t right_light_st;        // 右转向状态信号
  uint8_t eng_hood_unlock_warn;  // 发动机罩未锁紧报警信号
  uint8_t trunk_st;              // 行李箱门状态信号
  uint8_t front_wiper_work_st;   // 前雨刮工作模式
  uint8_t f_reverse_status;      // 车辆是否倒车
  uint8_t driver_belt_switch_st; // 安全带信号
  uint8_t actual_gear;           // 实际档位信息:
  uint8_t brake_pedal_type;      // 踏板类型
  uint8_t fcw_warn_dist;         // FCW灵敏度设置
  uint8_t longsafe_switch;       // AEBS开关状态:
  uint8_t bsd_switch;            // BSD开关状态:
  uint8_t dow_switch;            // DOW开关状态:
  uint8_t fctb_switch;           // FCTA/FCTB开关状态:
  uint8_t rctb_switch;           // RCTA/RCTB开关状态:
  uint8_t rcw_switch;            // RCW开关状态:
  uint8_t aeb_switch;            // AEB开关状态: 0:关闭, 1:开启
  uint8_t fcw_switch;            // FCW开关状态: 0:关闭, 1:开启
  uint8_t fcw_sensitivity_set;   // FCW灵敏度设置
  bool brake_pedal_apld;         // 制动踏板是否踩下
  bool abs_active;               // 底盘反馈ABS是否激活
  bool aeb_active;               // 底盘反馈AEB是否激活
  uint8_t power_mode;            // 车辆是否上电:
  bool long_ctrl_brake_active;   // 底盘反馈纵向控制激活:
  bool straight_driving;         // 自车直行-根据曲率判断
  bool high_dynamic;             // 自车大制动（加速）
  uint16_t
      host_state; // 车辆状态:Bit0:自车匀速,Bit1:自车大转角快速转向,Bit2:自车匀直行;
  uint32_t esp_brake_available_st; // ESP可响应制动功能状态
  uint32_t function_did_config;    // 功能DID配置
  uint8_t state_machine_sts;      // 智驾状态
};

} // namespace tap
} // namespace senseAD
#endif // TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_ACTIVE_SAFETY_VSE_H_
