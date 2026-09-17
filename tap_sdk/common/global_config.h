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
    bool k_aeb_enable = true;     // AEB功能是否打开
    bool k_aes_enable = false;     // AES/ESA功能是否打开
    bool k_ctb_enable = false;     // CTB功能是否打开
    bool k_cta_enable = false;     // CTA功能是否打开
    bool k_rcw_enable = false;     // RCW功能是否打开
    bool k_bsd_enable = false;     // BSD功能是否打开
    bool k_dow_enable = false;     // DOW功能是否打开
    bool k_use_new_swc = 0;        //是否使用NewSwc
    bool k_LDW_func_enable = false; // LDW功能是否打开
    bool k_LKA_func_enable = false; // LKA功能是否打开
    bool k_ELK_func_enable = false; // ELK功能是否打开
    bool k_LKA_HandoffWarningEnable = false; // LKA/ELK脱手报警功能开关
    bool k_LSS_IgnoreFaultInhibit = false; // LSS是否忽略上游功能故障抑制位
    bool k_LDW_EnLine = false; // LDW是否对车道线报警
    bool k_LDW_EnEdge = false; // LDW是否对路沿报警
    bool k_ELK_EnLct = false; // ELK是否对oncoming/overtaking目标触发
    bool k_ELK_EnEdge = false; // ELK是否对路沿触发
    bool k_ELK_EnSld = false; // ELK是否对实线触发
    bool k_ELK_bUsLowRtNearTrg = false; // ELK是否近距离贴线触发
    bool k_ELK_DebugLogEnable = false; // ELK debug日志开关，默认关闭
    float k_ELK_OC_ObjTTCScale = 1.0F; // ELK对向来车目标纵向/横向TTC门限倍率
    float k_ELK_OT_ObjTTCScale = 1.0F; // ELK后向超车目标纵向/横向TTC门限倍率
    float k_ELK_LCT_TTLCScale = 1.0F; // ELK对向来车/后向超车场景共用的跨线TTLC门限倍率
    float k_ELK_SLD_TTLCScale = 1.0F; // ELK实线场景TTLC门限倍率
    float k_ELK_ROR_TTLCScale = 1.0F; // ELK路沿场景TTLC门限倍率
    float k_LKA_TTLCScale = 1.0F; // LKA左右车道线TTLC门限倍率
    float k_LDW_TTLCScale = 1.0F; // LDW左右边界TTLC门限倍率
    bool k_LKA_LDW_EnDriftingTrigger = false; // LKA/LDW是否启用横向速度或航向角漂移旁路
    float k_ELK_Aligned_OnDelayTime = 0.35F; // ELK纠偏完成回正判定延时，单位：s
    float k_LKA_Centered_OnDelayTime = 2.0F; // LKA纠偏完成回正判定延时，单位：s
    bool k_Lgsf_EnCutOutSceneCheck = false;//是否使能高速前车切出遇静止车辆检测
    bool k_Lgsf_EnWaitAesActive = false; //AES存在避撞空间的时候 是否使能抑制AEB激活 等待AES激活
    bool k_Lgsf_EnSocAesAebArb = false; //是否使能soc AEB AES仲裁机制
    bool k_Lgsf_EnNewTarSelectOut = false;//是否使能新版目标筛选控制输出结果
    bool k_Lgsf_EnReverseTrajPred = false;//是否使能自车倒车(速度为负)的轨迹预测
    bool k_Lgsf_ForOldRsclBag = false;//是否适配旧版RSCL Bag
    bool k_AES_aebactive_enable = false; // aes仲裁是否参考aeb_active
    float k_AES_esafeedback_factor = 0.0F; // 反馈控制系数
    bool k_AES_feedbackopen = 1; // 是否打开反馈
    uint32_t major_version = 0;
    uint32_t midle_version = 0;
    uint32_t minor_version = 151;
};
} // namespace active_safety
