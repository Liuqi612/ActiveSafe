/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#pragma once
#include "common/global_config.h"

#include <cstddef>
#include <cstdint>

namespace active_safety {

struct AsVseOut {
    // Calibration for vse vehicle state.
    VehicleConfig config;

    float    speed;                  // 车辆速度，m/s
    float    display_speed;          // 车辆表显车速
    float    yawrate;                // 横摆角速度, rad/s
    float    yawrate_unfiltered_rps; // 未滤波的横摆角速度, rad/s
    float    long_accel;             // 纵向加速度,m/s2
    float    lat_accel;              // 横向加速度,m/s2
    float    host_pitch_rad;         // 车辆pitch角
    float    host_roll_rad;          // 车辆roll角
    float    vcs_sideslip;           // 车辆vcs侧偏角
    float    vcs_long_vel;           // 车辆vcs纵向速度,mps
    float    vcs_lat_vel;            // 车辆vcs横向速度,mps
    float    sensor_sideslip;
    float    sensor_long_vel;
    float    sensor_lat_vel;
    float    rear_curvature;        // 后轴曲率,rad，左正右负
    float    rear_curvaturerate;    // 后轴曲率变化率,rad/s，左正右负
    float    rear_curvature_radius; // 后轴曲率半径,1/rad，左正右负
    float    rear_sideslip;
    float    steerwheelangle;      // 方向盘转角，左正右负
    float    steerwheelangle_rate; // 方向盘转角变化率，左正右负
    float    slope_long_rad;
    float    slope_lat_rad;
    float    gas_pedal_pos;          // 加速踏板位置,[0-100]
    float    brake_pedal_pos;        // 制动踏板位置,[0-100]
    float    brake_pressure;         // 主缸压力
    float    torsion_bar_trq;        // 扭杆扭矩
    float    gas_pedal_pos_rate;     // 加速踏板位置变化率
    float    brake_pedal_pos_rate;   // 制动踏板位置变化率
    float    brake_pressure_rate;    // 主缸压力变化率
    uint8_t  hod_hands_monitor;      // 电容方向盘HOD: 1=脱手, 2=触摸, 3=握住
    uint8_t  hazard_lamp_st;         // 危险报警灯状态信号
    uint8_t  front_fog_lamp_st;      // 前雾灯状态
    uint8_t  back_fog_lamp_st;       // 后雾灯状态
    uint8_t  left_light_fault_st;    // 左转向灯故障状态
    uint8_t  right_light_fault_st;   // 右转向灯故障状态
    uint8_t  epb_applied;            // EPB是否拉起
    uint8_t  high_beam_st;           // 远光灯状态
    uint8_t  vdc_active_st;          // VDC激活状态
    uint8_t  veh_dyn_cntl_stat;      // 车身动态控制状态
    uint8_t  tcs_active_st;          // TCS激活状态
    uint8_t  tcs_sta;                // TCS状态（多一个fault）
    uint8_t  hdc_active_st;          // HDC激活状态
    uint8_t  lgctrl_trq_req_sts;     // 纵向执行器状态
    bool     veh_crash;              // 车辆碰撞
    uint8_t  esc_off_st;             // ESC关闭状态
    uint8_t  airbag_virt_dev_avl;    // 安全气囊状态
    uint8_t  tire_presr_fault;       // 胎压异常状态
    uint8_t  lka_trq_ovl_dlvd_stat;  // EPS状态机
    uint8_t  fl_door_st;             // 左前车门状态信号
    uint8_t  fr_door_st;             // 右前车门状态信号
    uint8_t  rl_door_st;             // 左后车门状态信号
    uint8_t  rr_door_st;             // 右后车门状态信号
    uint8_t  turn_light_switch_pos;  // 转向开关状态
    uint8_t  left_light_st;          // 左转向状态信号
    uint8_t  right_light_st;         // 右转向状态信号
    uint8_t  eng_hood_unlock_warn;   // 发动机罩未锁紧报警信号
    uint8_t  trunk_st;               // 行李箱门状态信号
    uint8_t  front_wiper_work_st;    // 前雨刮工作模式
    uint8_t  f_reverse_status;       // 车辆是否倒车
    uint8_t  driver_belt_switch_st;  // 安全带信号
    uint8_t  actual_gear;            // 实际档位信息:
    uint8_t  brake_pedal_type;       // 踏板类型
    uint8_t  fcw_warn_dist;          // FCW灵敏度设置
    uint8_t  longsafe_switch;        // AEBS开关状态:
    uint8_t  lss_switch;             // LSS软开关: 0:关闭，1:预警，2:预警+纠偏
    uint8_t  lss_sensitivity;        // LSS纠偏灵敏度
    uint8_t  elk_switch;             // ELK软开关
    uint8_t  ldw_switch;             // LDW软开关
    uint8_t  lka_switch;             // LKA软开关
    uint8_t  esa_switch;             // ESA开关状态
    uint8_t  aes_switch;             // AES开关状态
    uint8_t  bsd_switch;             // BSD开关状态:
    uint8_t  dow_switch;             // DOW开关状态:
    uint8_t  fctb_switch;            // FCTA/FCTB开关状态:
    uint8_t  rctb_switch;            // RCTA/RCTB开关状态:
    uint8_t  rcw_switch;             // RCW开关状态:
    uint8_t  aeb_switch;             // AEB开关状态: 0:关闭, 1:开启
    uint8_t  fcw_switch;             // FCW开关状态: 0:关闭, 1:开启
    uint8_t  fcw_sensitivity_set;    // FCW灵敏度设置
    bool     brake_pedal_apld;       // 制动踏板是否踩下
    bool     abs_active;             // 底盘反馈ABS是否激活
    bool     aeb_active;             // 底盘反馈AEB是否激活
    uint8_t  power_mode;             // 车辆是否上电:
    bool     long_ctrl_brake_active; // 底盘反馈纵向控制激活:
    bool     straight_driving;       // 自车直行-根据曲率判断
    uint32_t esp_brake_available_st; // ESP可响应制动功能状态
    uint32_t function_did_config;    // 功能DID配置
    uint64_t veh_time_stamp;
    uint8_t  state_machine_sts;             // 车辆是否上电:
};

} // namespace active_safety
