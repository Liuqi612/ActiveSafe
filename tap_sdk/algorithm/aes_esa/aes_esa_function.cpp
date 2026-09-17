#include "algorithm/aes_esa/aes_esa_function.h"

#include <algorithm>
#include <cstring>
#include <iostream>

namespace active_safety {
namespace aes_esa {

AesEsaFunction::AesEsaFunction() {
    // B/DW 结构体尺寸很大，静态分配放入 BSS 段，避免栈溢出（与 LgSafe2024Function 保持一致）
    static B_AES_ESA_SWC_T b{};
    static DW_AES_ESA_SWC_T dw{};
    static RT_MODEL_AES_ESA_SWC_T m{};

    rtm_ = &m;
    rtm_->blockIO = &b;
    rtm_->dwork = &dw;

    // 初始化所有输入/输出缓冲区
    std::memset(&u_lanes_info_, 0, sizeof(u_lanes_info_));
    std::memset(&u_vse_out_, 0, sizeof(u_vse_out_));
    std::memset(&u_elk_info_, 0, sizeof(u_elk_info_));
    std::memset(&u_as_target_, 0, sizeof(u_as_target_));
    std::memset(&u_fus_info_, 0, sizeof(u_fus_info_));
    std::memset(&u_reseverved_input_, 0, sizeof(u_reseverved_input_));
    std::memset(&aes_esa_out_, 0, sizeof(aes_esa_out_));
    std::memset(&aes_esa_cmd_, 0, sizeof(aes_esa_cmd_));

    Init();
}

AesEsaFunction::~AesEsaFunction() {
    if (rtm_ != nullptr) {
        AES_ESA_SWC_terminate(rtm_);
    }
}

void AesEsaFunction::Init() {
    // 调用 Simulink 生成的初始化函数，绑定所有输入/输出缓冲区指针
    AES_ESA_SWC_initialize(rtm_, &u_lanes_info_, &u_vse_out_, &u_elk_info_, &u_as_target_, &u_fus_info_, &u_reseverved_input_,&aes_esa_out_);
}

void AesEsaFunction::Update(const FusionInfo &fusioninfo, const LanesInfo &road_info, const AsVseOut &vse_out, const AsOnComingOut &oncom_out,
                            const AsOverTakingOut &overtake_out, const senseAD::tap::AsCmdLgSafe_T &cmd_output, const GlobalConfig &global_config,
                            const Reserved_Input &reseverved_input,float aeb_length, float aeb_width) {
    // 将业务层入参映射到模型原生缓冲区
    MapToSimulinkInput(fusioninfo, road_info, vse_out, oncom_out, overtake_out, reseverved_input,cmd_output, aeb_length, aeb_width);
    //    for(auto &i : fusioninfo.trk)
    //    {if (i.fus_trkID ==646)
    //     {std::cout<<"fus_trkID = "<<i.fus_trkID<<" ; age = "<<i.age<<" ;"<<std::endl;}
    // }
    // std::cout<<"left_c0 = "<<road_info.HostLeftLaneMarker.LinePolyC0<<std::endl;
    // std::cout<<"自车kph = "<<vse_out.speed*3.6<<std::endl;

    // 调用 Simulink step 函数，结果写入 aes_esa_out_
    AES_ESA_SWC_step(rtm_, &u_lanes_info_, &u_vse_out_, &u_elk_info_, &u_as_target_, &u_fus_info_,&u_reseverved_input_, &aes_esa_out_);
    // // 回灌判分支：rtb_Switch4_i 写入 blockIO->AESTarget_Oncoming_Flg（与 Simulink <S8>/Logical Operator11 一致）
    // // Oncoming=1：<S9>/Switch3 不执行 fmin
    // // Oncoming=0：Final = fmin(ttc_phy, k_AES_MaxBrakeDecelProtect)
    // if (rtm_->blockIO != nullptr) {
    //     const bool oncoming = (rtm_->blockIO->AESTarget_Oncoming_Flg != 0U);
    //     const float ttc_phy = rtm_->blockIO->AES_LastPntToBrk_TTC;
    //     const float ttc_final = aes_esa_out_.AES_LastPntToBrk_TTC_Final;
    //     constexpr float kBranchEps = 1.0e-4F;
    //     const char* branch = "NON_ONCOMING_PHY_DIRECT";
    //     if (oncoming) {
    //         branch = "ONCOMING_BYPASS_MIN";
    //     } else if (ttc_final + kBranchEps < ttc_phy) {
    //         branch = "NON_ONCOMING_MIN_CLAMP";
    //     }
    //     std::cout << "[AES_LastPntToBrk_Branch] branch=" << branch
    //               << " oncoming=" << static_cast<int>(rtm_->blockIO->AESTarget_Oncoming_Flg)
    //               << " ttc_phy=" << ttc_phy
    //               << " ttc_final=" << ttc_final
    //               << " ttc_esa=" << rtm_->blockIO->AES_LastPntToBrk_TTC_ESA
    //               << " ttc_esa_final=" << rtm_->blockIO->AES_LastPntToBrk_TTC_ESA_Final
    //               << std::endl;
    // }
    // 从完整输出中抽取对外指令量 cmd（用于 73a验证）
    // 影子模式或功能关闭时，仅保留 mode 用于观测，执行相关输出清零。
    if (global_config.k_use_shadowmode || !global_config.k_aes_enable) {
        aes_esa_cmd_.evasion_direction = 0U;
        aes_esa_cmd_.active_flag = 0U;
        aes_esa_cmd_.str_whl_ang_req = 0.0F;
    } else {
        aes_esa_cmd_.evasion_direction = static_cast<uint8_t>(aes_esa_out_.AES_ESA_EvasionDirection);
        aes_esa_cmd_.active_flag = static_cast<uint8_t>(aes_esa_out_.AES_ESA_ActiveFlag);
        aes_esa_cmd_.str_whl_ang_req = aes_esa_out_.AES_ESA_StrWhlAngReq;
    }
    aes_esa_cmd_.mode = static_cast<uint8_t>(aes_esa_out_.AES_ESA_Mode);
}
void AesEsaFunction::AbortAesEsaCmd() {

    aes_esa_cmd_.evasion_direction = 0U;
    aes_esa_cmd_.active_flag = 0U;
    aes_esa_cmd_.str_whl_ang_req = 0.0F;
}

void AesEsaFunction::MapToSimulinkInput(const FusionInfo &fusioninfo, const LanesInfo &road_info, const AsVseOut &vse_out,
                                        const AsOnComingOut &oncom_out, const AsOverTakingOut &overtake_out, const Reserved_Input &reseverved_input,
                                        const senseAD::tap::AsCmdLgSafe_T &cmd_output, float aeb_length, float aeb_width) {
    // ── LanesInfo：业务层与模型层内存布局完全一致，直接拷贝 ──────────────────
    static_assert(sizeof(active_safety::LanesInfo) == sizeof(::LanesInfo), "LanesInfo size mismatch between business and model");
    std::memcpy(&u_lanes_info_, &road_info, sizeof(::LanesInfo));

    // AsVseOut: business struct and model struct are not layout-compatible after 00.55.
    // Map by field to avoid offset corruption when either side inserts fields.
    u_vse_out_ = ::AsVseOut{};
    u_vse_out_.config.k_dist_to_rear_axle = vse_out.config.k_dist_to_rear_axle;
    u_vse_out_.config.k_host_width = vse_out.config.k_host_width;
    u_vse_out_.config.k_host_length = vse_out.config.k_host_length;
    u_vse_out_.config.k_steer_gradient = vse_out.config.k_steer_gradient;
    u_vse_out_.config.k_rear_cornering_compliance = vse_out.config.k_rear_cornering_compliance;
    u_vse_out_.config.k_steer_ratio = vse_out.config.k_steer_ratio;
    u_vse_out_.config.k_wheel_base = vse_out.config.k_wheel_base;
    u_vse_out_.config.k_vcs_camera_long_posn = vse_out.config.k_vcs_camera_long_posn;
    u_vse_out_.config.k_vcs_camera_lat_posn = vse_out.config.k_vcs_camera_lat_posn;
    u_vse_out_.speed = vse_out.speed;
    u_vse_out_.display_speed = vse_out.display_speed;
    u_vse_out_.yawrate = vse_out.yawrate;
    u_vse_out_.yawrate_unfiltered_rps = vse_out.yawrate_unfiltered_rps;
    u_vse_out_.long_accel = vse_out.long_accel;
    u_vse_out_.lat_accel = vse_out.lat_accel;
    u_vse_out_.host_pitch_rad = vse_out.host_pitch_rad;
    u_vse_out_.host_roll_rad = vse_out.host_roll_rad;
    u_vse_out_.vcs_sideslip = vse_out.vcs_sideslip;
    u_vse_out_.vcs_long_vel = vse_out.vcs_long_vel;
    u_vse_out_.vcs_lat_vel = vse_out.vcs_lat_vel;
    u_vse_out_.sensor_sideslip = vse_out.sensor_sideslip;
    u_vse_out_.sensor_long_vel = vse_out.sensor_long_vel;
    u_vse_out_.sensor_lat_vel = vse_out.sensor_lat_vel;
    u_vse_out_.rear_curvature = vse_out.rear_curvature;
    u_vse_out_.rear_curvaturerate = vse_out.rear_curvaturerate;
    u_vse_out_.rear_curvature_radius = vse_out.rear_curvature_radius;
    u_vse_out_.rear_sideslip = vse_out.rear_sideslip;
    u_vse_out_.steerwheelangle = vse_out.steerwheelangle;
    u_vse_out_.steerwheelangle_rate = vse_out.steerwheelangle_rate;
    u_vse_out_.slope_long_rad = vse_out.slope_long_rad;
    u_vse_out_.slope_lat_rad = vse_out.slope_lat_rad;
    u_vse_out_.gas_pedal_pos = vse_out.gas_pedal_pos;
    u_vse_out_.brake_pedal_pos = vse_out.brake_pedal_pos;
    u_vse_out_.brake_pressure = vse_out.brake_pressure;
    u_vse_out_.torsion_bar_trq = vse_out.torsion_bar_trq;
    u_vse_out_.gas_pedal_pos_rate = vse_out.gas_pedal_pos_rate;
    u_vse_out_.brake_pedal_pos_rate = vse_out.brake_pedal_pos_rate;
    u_vse_out_.brake_pressure_rate = vse_out.brake_pressure_rate;
    u_vse_out_.hazard_lamp_st = vse_out.hazard_lamp_st;
    u_vse_out_.front_fog_lamp_st = vse_out.front_fog_lamp_st;
    u_vse_out_.back_fog_lamp_st = vse_out.back_fog_lamp_st;
    u_vse_out_.left_light_fault_st = vse_out.left_light_fault_st;
    u_vse_out_.right_light_fault_st = vse_out.right_light_fault_st;
    u_vse_out_.epb_applied = vse_out.epb_applied;
    u_vse_out_.high_beam_st = vse_out.high_beam_st;
    u_vse_out_.vdc_active_st = vse_out.vdc_active_st;
    u_vse_out_.veh_dyn_cntl_stat = vse_out.veh_dyn_cntl_stat;
    u_vse_out_.tcs_active_st = vse_out.tcs_active_st;
    u_vse_out_.hdc_active_st = vse_out.hdc_active_st;
    u_vse_out_.esc_off_st = vse_out.esc_off_st;
    u_vse_out_.airbag_virt_dev_avl = vse_out.airbag_virt_dev_avl;
    u_vse_out_.tire_presr_fault = vse_out.tire_presr_fault;
    u_vse_out_.lka_trq_ovl_dlvd_stat = vse_out.lka_trq_ovl_dlvd_stat;
    u_vse_out_.fl_door_st = vse_out.fl_door_st;
    u_vse_out_.fr_door_st = vse_out.fr_door_st;
    u_vse_out_.rl_door_st = vse_out.rl_door_st;
    u_vse_out_.rr_door_st = vse_out.rr_door_st;
    u_vse_out_.turn_light_switch_pos = vse_out.turn_light_switch_pos;
    u_vse_out_.left_light_st = vse_out.left_light_st;
    u_vse_out_.right_light_st = vse_out.right_light_st;
    u_vse_out_.eng_hood_unlock_warn = vse_out.eng_hood_unlock_warn;
    u_vse_out_.trunk_st = vse_out.trunk_st;
    u_vse_out_.front_wiper_work_st = vse_out.front_wiper_work_st;
    u_vse_out_.f_reverse_status = vse_out.f_reverse_status;
    u_vse_out_.driver_belt_switch_st = vse_out.driver_belt_switch_st;
    u_vse_out_.actual_gear = vse_out.actual_gear;
    u_vse_out_.brake_pedal_type = vse_out.brake_pedal_type;
    u_vse_out_.fcw_warn_dist = vse_out.fcw_warn_dist;
    u_vse_out_.longsafe_switch = vse_out.longsafe_switch;
    u_vse_out_.esa_switch = vse_out.esa_switch;
    u_vse_out_.aes_switch = vse_out.aes_switch;
    u_vse_out_.bsd_switch = vse_out.bsd_switch;
    u_vse_out_.dow_switch = vse_out.dow_switch;
    u_vse_out_.fctb_switch = vse_out.fctb_switch;
    u_vse_out_.rctb_switch = vse_out.rctb_switch;
    u_vse_out_.rcw_switch = vse_out.rcw_switch;
    u_vse_out_.brake_pedal_apld = vse_out.brake_pedal_apld;
    u_vse_out_.abs_active = vse_out.abs_active;
    u_vse_out_.aeb_active = vse_out.aeb_active;
    u_vse_out_.power_mode = vse_out.power_mode;
    u_vse_out_.long_ctrl_brake_active = vse_out.long_ctrl_brake_active;
    u_vse_out_.straight_driving = vse_out.straight_driving;
    u_vse_out_.esp_brake_available_st = vse_out.esp_brake_available_st;
    u_vse_out_.function_did_config = vse_out.function_did_config;
    u_vse_out_.veh_time_stamp = vse_out.veh_time_stamp;

    // ── ElkInfo：来自 ELK 模块的超车/对向目标输出 ───────────────────────────
    {
        // AsOnComingObject 字段顺序与类型完全相同，二进制兼容，直接拷贝
        static_assert(sizeof(active_safety::AsOnComingObject) == sizeof(::AsOnComingObject), "AsOnComingObject size mismatch");
        std::memcpy(&u_elk_info_.oncom_target1, &oncom_out.oncom_target_1, sizeof(::AsOnComingObject));
        std::memcpy(&u_elk_info_.oncom_target2, &oncom_out.oncom_target_2, sizeof(::AsOnComingObject));
        std::memcpy(&u_elk_info_.oncom_target3, &oncom_out.oncom_target_3, sizeof(::AsOnComingObject));

        // AsOverTakingObject：模型结构体末尾有额外 pad 字段，不能直接 memcpy，逐字段赋值
        // 用 visTrkID 代替 fusTrkID（fusTrkID 暂无可靠来源）
        auto mapOvertake = [](const active_safety::AsOverTakingObject &src, ::AsOverTakingObject &dst) {
            dst.vcs_long_posn = src.vcs_long_posn;
            dst.vcs_long_vel = src.vcs_long_vel;
            dst.vcs_long_accel = src.vcs_long_accel;
            dst.vcs_lat_posn = src.vcs_lat_posn;
            dst.vcs_lat_vel = src.vcs_lat_vel;
            dst.vcs_lat_accel = src.vcs_lat_accel;
            dst.width = src.width;
            dst.length = src.length;
            dst.vcs_heading = src.vcs_heading;
            dst.confidence = src.confidence;
            dst.object_class = src.object_class;
            dst.fusion_source = src.fusion_source;
            dst.track_status = src.track_status;
            dst.fusTrkID = src.visTrkID; // 阶段1 用 visTrkID 代替
            dst.track_id = src.track_id;
            dst.pad0 = 0;
            dst.pad1 = 0;
            dst.pad2 = 0;
        };
        mapOvertake(overtake_out.overtake_target_rear_left, u_elk_info_.overtake_target_rear_left);
        mapOvertake(overtake_out.overtake_target_rear_right, u_elk_info_.overtake_target_rear_right);
        mapOvertake(overtake_out.overtake_target_front_left, u_elk_info_.overtake_target_front_left);
        mapOvertake(overtake_out.overtake_target_front_right, u_elk_info_.overtake_target_front_right);
    }

    // ── AsTarget：主目标信息来自 cmd_output.lgsf_target；长宽来自 AEB 选择输出 ─
    {
        const auto &tgt = cmd_output.lgsf_target;
        u_as_target_.id = tgt.id; // 优先取 cmd_output 中的目标 ID
        u_as_target_.type = static_cast<uint8_T>(tgt.type);
        u_as_target_.source = static_cast<uint8_T>(tgt.source);
        u_as_target_.color = 0;
        u_as_target_.padding = 0;
        u_as_target_.posX = tgt.posx;
        u_as_target_.posY = tgt.posy;
        u_as_target_.spdX = tgt.spdx;
        u_as_target_.spdY = tgt.spdy;
        u_as_target_.accelX = tgt.accelx;
        u_as_target_.accelY = tgt.accely;
        u_as_target_.heading = tgt.heading;
        u_as_target_.length = aeb_length; // 来自 lgsf_2024_.GetSelectOut().longsafe_aeb
        u_as_target_.width = aeb_width;
        u_as_target_.ttc = tgt.ttc;
        u_as_target_.fcw_active = cmd_output.fcw_mode == senseAD::tap::FcwMode::FCW_ACTIVE || cmd_output.resv2 ;
    }

    // ── AS_FusionInfo：逐字段赋值（age 字段类型不同：业务层 float → 模型 uint16_T）
    {
        u_fus_info_.look_index = static_cast<uint32_T>(fusioninfo.seq_num);
        u_fus_info_.time = static_cast<uint64_T>(fusioninfo.time);
        u_fus_info_.gop_cnt = static_cast<uint32_T>(fusioninfo.gop_seq_num);
        u_fus_info_.gop_time = static_cast<uint64_T>(fusioninfo.gop_time);

        for (std::size_t i = 0; i < 96U; ++i) {
            const auto &src = fusioninfo.trk[i];
            auto &dst = u_fus_info_.trk[i];
            dst.track_id = src.track_id;
            dst.vis_trk_id = src.vis_trk_id;
            // age：业务层为 float，模型层为 uint16_T，clamp 到 [0, 65535] 后截断
            dst.age = static_cast<uint16_T>(std::min(65535.0f, std::max(0.0f, src.age)));
            dst.fus_trkID = src.fus_trkID;
            dst.vis_trkID = src.vis_trkID;
            dst.speed = src.speed;
            dst.lat_posn = src.lat_posn;
            dst.long_posn = src.long_posn;
            dst.lat_vel = src.lat_vel;
            dst.long_vel = src.long_vel;
            dst.lat_accel = src.lat_accel;
            dst.long_accel = src.long_accel;
            dst.heading = src.heading;
            // ObsConfidence 为 enum class : uint8_t，模型侧为 real32_T，需显式转换
            dst.confidence = static_cast<real32_T>(static_cast<uint8_t>(src.confidence));
            dst.status = static_cast<uint8_T>(src.status);
            dst.object_class = static_cast<uint8_T>(src.object_class);
            dst.fusion_source = static_cast<uint8_T>(src.fusion_source);
            dst.resv1 = src.resv1;
            dst.length = src.length;
            dst.width = src.width;
            dst.height = src.height;
        }
    }
    {
       u_reseverved_input_.last_aes_active = reseverved_input.last_aes_active;
       u_reseverved_input_.aes_float_reserv1 = reseverved_input.aes_float_reserv1;
       u_reseverved_input_.aes_float_reserv2 = reseverved_input.aes_float_reserv2;
       u_reseverved_input_.aes_float_reserv3 = reseverved_input.aes_float_reserv3;
       u_reseverved_input_.aes_uint32_digmsk = reseverved_input.aes_uint32_digmsk;
       u_reseverved_input_.aes_uint32_reserv1 = reseverved_input.aes_uint32_reserv1;
       u_reseverved_input_.aes_uint32_reserv2 = reseverved_input.aes_uint32_reserv2;
       u_reseverved_input_.aes_uint32_reserv3 = reseverved_input.aes_uint32_reserv3;

    }
}


} // namespace aes_esa
} // namespace active_safety
