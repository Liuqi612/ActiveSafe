/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>
namespace active_safety {

struct VehicleConfig {
    float k_dist_to_rear_axle = 3.68;
    float k_host_width = 1.925;
    float k_host_length = 4.791;
    float k_steer_gradient = 0.003;
    float k_rear_cornering_compliance = 0.005;
    float k_steer_ratio = 15.5;
    float k_wheel_base = 2.75;
    float k_vcs_camera_long_posn = 0.0f;
    float k_vcs_camera_lat_posn = 0.0f;
};

struct GlobalConfig {
    bool k_use_shadowmode = false; //判断是否发送制动指令
    bool k_aeb_enable = false;     // AEB功能是否打开
    bool k_ctb_enable = false;     // CTB功能是否打开
    bool k_cta_enable = false;     // CTA功能是否打开
    bool k_rcw_enable = false;     // RCW功能是否打开
    bool k_bsd_enable = false;     // BSD功能是否打开
    bool k_dow_enable = false;     // DOW功能是否打开
    bool k_use_new_swc = 0;        //是否使用NewSwc
    uint32_t major_version = 0;
    uint32_t midle_version = 0;
    uint32_t minor_version = 6;
};

} // namespace active_safety
