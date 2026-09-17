/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#include "active_safety_wrapper.h"

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace active_safety {

ActiveSafetyWrapper::ActiveSafetyWrapper() {
    for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
        obs_list_[i] = std::make_shared<AsObstacle>();
    }
    fault_type_ = 0;
}

ActiveSafetyWrapper::~ActiveSafetyWrapper() = default;

bool ActiveSafetyWrapper::Init(const std::string &cali_path, uint8_t tsel_longsafe_cnt, uint8_t tsel_sf_cnt, uint8_t ctrl_lgsf_cnt) {
    json11::Json config;
    std::string err;
    std::ifstream file(cali_path); // 替换为你的文件名
    std::stringstream buffer;
    std::string json_content{""};
    if (file) {
        buffer << file.rdbuf();
        json_content = buffer.str();
        file.close();
    } else {
        return false;
    }
    config = json11::Json::parse(json_content, err);
    if (!err.empty()) {
        return false;
    }
    if (!LoadJsonParam(config)) {
        return false;
    }

    vse_.Init();
    return true;
}

void ActiveSafetyWrapper::RunVse(const VseInput &vse_input, uint64_t curtime) {
    std::lock_guard<std::mutex> lock(vse_mtx_);
    vse_.Run(vse_input, curtime, global_config_);
}

void ActiveSafetyWrapper::DiagArbitrate() {
    // 统一故障掩码
    const uint32_t kFaultMask = 
        static_cast<uint32_t>(FaultType::Fusion) |
        static_cast<uint32_t>(FaultType::Vehicle) |
        static_cast<uint32_t>(FaultType::Gop) |
        static_cast<uint32_t>(FaultType::Config) |
        static_cast<uint32_t>(FaultType::Lane);

    // 配置表：{功能掩码, 使能标志, 结果引用}
    struct DiagItem {
        FunctionInhibitMask func;
        uint8_t enable;
        uint8_t& result;
    };

    // 绑定到结构体变量（类型完全匹配，无警告）
    const DiagItem items[] = {
        {FunctionInhibitMask::AEB,    diag_param_.k_enable_aeb_diag,    diag_inhibit_result_.aeb_inhibit},
        {FunctionInhibitMask::LKA,    diag_param_.k_enable_lka_diag,    diag_inhibit_result_.lka_inhibit},
        {FunctionInhibitMask::ESA,    diag_param_.k_enable_esa_diag,    diag_inhibit_result_.esa_inhibit},
        {FunctionInhibitMask::AES,    diag_param_.k_enable_aes_diag,    diag_inhibit_result_.aes_inhibit},
        {FunctionInhibitMask::ELK,    diag_param_.k_enable_elk_diag,    diag_inhibit_result_.elk_inhibit},
        {FunctionInhibitMask::LOCP,   diag_param_.k_enable_locp_diag,   diag_inhibit_result_.locp_inhibit},
        {FunctionInhibitMask::FCTA_B, diag_param_.k_enable_fcta_diag,   diag_inhibit_result_.fcta_b_inhibit},
        {FunctionInhibitMask::RCTA_B, diag_param_.k_enable_rcta_diag,   diag_inhibit_result_.rcta_b_inhibit},
        {FunctionInhibitMask::DOW,    diag_param_.k_enable_dow_diag,    diag_inhibit_result_.dow_inhibit},
        {FunctionInhibitMask::BSD,    diag_param_.k_enable_bsd_diag,    diag_inhibit_result_.bsd_inhibit},
        {FunctionInhibitMask::RCW,    diag_param_.k_enable_rcw_diag,    diag_inhibit_result_.rcw_inhibit},
        {FunctionInhibitMask::LDW,    diag_param_.k_enable_ldw_diag,    diag_inhibit_result_.ldw_inhibit}
    };

    for (const auto& item : items) {
        const bool inhibit_condition = ((fault_type_ & kFaultMask) || 
                                       (function_inhibit_mask_ & static_cast<uint32_t>(item.func))) && 
                                      (item.enable != 0);
        item.result = inhibit_condition ? 1 : 0;
    }
}

bool ActiveSafetyWrapper:: CheckHighSpeedFrontVehicleCutOut(const senseAD::tap::AsLongSafeObject& current_target, bool aeb_unavoid_collision_flag, bool aes_exist_steer_space) {
    const auto& long_scene = lgsf_2024_.GetLgSf();
    bool should_inhibit = false;
    
    // 检测目标跳变 目前LgSf_AbaReq赋值AEB不可避撞标志位
    if (target_jump_state_.last_target_id > 0 && 
        current_target.fus_trkId > 0 &&
        target_jump_state_.last_target_id != current_target.fus_trkId &&
        aes_exist_steer_space && aeb_unavoid_collision_flag && global_config_.k_Lgsf_EnCutOutSceneCheck) {
        // 目标发生跳变，检查条件
        const float delta_long_posn = current_target.long_posn - target_jump_state_.last_long_posn;
        const float delta_speed = current_target.speed - target_jump_state_.last_speed;
        
        const bool target_type_ok = (target_jump_state_.last_object_class == 1 && current_target.object_class == 1); // CAR类型
        const bool ego_speed_ok = (vse_out_.speed * 3.6F > 70.0F);
        
        if (delta_long_posn >= 10.0F && 
            delta_speed <= -12.0F && 
            current_target.speed < 1.0F &&
            target_type_ok &&
            ego_speed_ok) {
            // 满足所有条件，钳制1.0s
            target_jump_state_.inhibit_end_time = vse_out_.veh_time_stamp + 1000000000;
            should_inhibit = true;
        }
    }
    
    // 更新历史目标信息
    target_jump_state_.last_target_id = current_target.fus_trkId;
    target_jump_state_.last_object_class = current_target.object_class;
    target_jump_state_.last_long_posn = current_target.long_posn;
    target_jump_state_.last_speed = current_target.speed;
    
    // 检查是否还在钳制时间内 
    if ((vse_out_.veh_time_stamp < target_jump_state_.inhibit_end_time)  &&  aes_exist_steer_space) {

        should_inhibit = true;
    }else{

        target_jump_state_.inhibit_end_time = vse_out_.veh_time_stamp;//一旦检测到AES无避撞空间立马退出抑制 延时清零
    }
    
    return should_inhibit;
}

void ActiveSafetyWrapper::ActuatorArbitrate(){

    if(global_config_.k_Lgsf_EnSocAesAebArb){

        const auto& aes_esa_out = aes_esa_.GetOutput();
        const auto& longsafe_cmd = lgsf_2024_.GetCmd();
        const auto& ltap_out = lgsf_2024_.GetLtapOut();
        const auto& current_target = lgsf_2024_.GetSelectOut().longsafe_aeb;
        const auto& long_scene = lgsf_2024_.GetLgSf();

        // aeb 借位LgSf_AbaReq 输出不可避撞标志位
        bool aeb_unavoid_collision_flag = long_scene.LgSf_LongScene.LgSf_AbaReq;
        // 存在避撞空间
        const auto& aes_exist_steer_space = aes_esa_out.AES_ESA_EvasionDirection != 0;
        // 内部esa激活
        const auto& esa_active = aes_esa_out.AES_ESA_Mode == 5;
        // 夹心场景标志位
        const auto& carsanwich_flag = aes_esa_out.padding_6;
        // fcw内部风险标志位
        //const auto& fcw_threat_flag = ltap_out.AEBFunc.FCW.ActtnDataFromCllsnFwdWarnCtrl.WarnReq;
        // aeb内部风险标志位
        const auto& aeb_threat_flag = (ltap_out.AEBFunc.CMBB.CMbBStatus == 1 || ltap_out.AEBFunc.CMBB.CMbBStatus == 2 || ltap_out.AEBFunc.CMBB.CMbBStatus == 14);
        // aeb激活
        const auto& aeb_active = longsafe_cmd.aeb_req == senseAD::tap::OnOffStatus::Active;
        // 输出不可避撞标志位 借用cmd_output_.resv1 传送给Aes模块
        lgsf_2024_.SetAebUnavoidCollision(aeb_unavoid_collision_flag);

        // 输出fcw_threat_flag标志位 借用cmd_output_.resv2 传送给Aes模块
        //lgsf_2024_.SetFcwThreatFlag(fcw_threat_flag);
        // 输出fcw_threat_flag标志位 借用cmd_output_.resv3 传送给Aes模块
        lgsf_2024_.SetAebThreatFlag(aeb_threat_flag);
        
        bool final_aes = false;
        
        // 调用高速前车切出场景检测
        bool cut_out_with_stationary_vehicle_scene = CheckHighSpeedFrontVehicleCutOut(current_target, aeb_unavoid_collision_flag, aes_exist_steer_space);

        if (longsafe_cmd.aeb_status ==  senseAD::tap::AebStatus::AEB_Init || 
            longsafe_cmd.aeb_status ==   senseAD::tap::AebStatus::AEB_OFF ||
            (cut_out_with_stationary_vehicle_scene) || carsanwich_flag)  {
            aeb_unavoid_collision_flag = 1;             
        } 
        if (last_aes_activated_) {
                // 【上一周期已经激活】 透传AES内部激活指令 仲裁不会打断AES的激活进程
                final_aes = aes_esa_out.AES_ESA_ActiveFlag;
        } else {
                // 针对FCW激活后 + 驾驶员干预且ESA激活满足 final_aes 无需考虑AEB相关指令
                if(!last_aeb_activated_ && aes_exist_steer_space && esa_active && aes_esa_out.AES_ESA_ActiveFlag)
                {
                    final_aes = aes_esa_out.AES_ESA_ActiveFlag;
                }else{
                   // 正常逻辑：必须满足 AEB风险激活 + AES存在避障空间 + AEB制动不可避撞置起
                    final_aes = (aeb_active || aeb_threat_flag || global_config_.k_AES_aebactive_enable) && aes_exist_steer_space && aeb_unavoid_collision_flag &&(aes_esa_out.AES_ESA_ActiveFlag || global_config_.k_Lgsf_EnWaitAesActive);
                }
        }
        //终止AEB激活
        if(final_aes){
        lgsf_2024_.AbortAebCmd();
        }else{
        aes_esa_.AbortAesEsaCmd();
        }
        // 获取仲裁后的AES指令
        const auto& aes_esa_cmd = aes_esa_.GetAesEsaCmd();
        last_aes_activated_ = aes_esa_cmd.active_flag;

        // 获取仲裁后的AEB指令
        last_aeb_activated_ = longsafe_cmd.aeb_req == senseAD::tap::OnOffStatus::Active;

    }
}

void ActiveSafetyWrapper::RunTselCtrl(const FusionInfo &fusioninfo, const LanesInfo &road_info, const PlanningInfo &long_ctrl_info,
                                      const MebMsgInfo &meb_info, uint64_t control_time_ns) {

    // Selection output is read by the Planning timer on another thread.  Hold
    // the same mutex across the control update so ID/TTC/status are observed
    // as one decision rather than from different control ticks.
    std::lock_guard<std::mutex> threat_lock(threat_assor_mtx);

    // diag
    DiagArbitrate();

    // SetInput
    Eigen::Vector3f ego_delta_last_cycle;
    {
        std::lock_guard<std::mutex> lock(vse_mtx_);
        vse_out_ = vse_.vse_ipc_;
        /*
        AEB: bit0
        AES: bit1
        ESA: bit2
        ELK: bit3
        FCTA/B: bit4
        RCTA/B: bit5
        RCW: bit6
        BSD: bit7
        DOW: bit8
        LKA: bit9
        LDW: bit10
        */ 
        SetDiagBitToValue(vse_out_.function_did_config, 0, diag_inhibit_result_.aeb_inhibit);
        SetDiagBitToValue(vse_out_.function_did_config, 1, diag_inhibit_result_.aes_inhibit);
        SetDiagBitToValue(vse_out_.function_did_config, 2, diag_inhibit_result_.esa_inhibit);
        SetDiagBitToValue(vse_out_.function_did_config, 3, diag_inhibit_result_.elk_inhibit);
        SetDiagBitToValue(vse_out_.function_did_config, 4, diag_inhibit_result_.fcta_b_inhibit);
        SetDiagBitToValue(vse_out_.function_did_config, 5, diag_inhibit_result_.rcta_b_inhibit);
        SetDiagBitToValue(vse_out_.function_did_config, 6, diag_inhibit_result_.rcw_inhibit);
        SetDiagBitToValue(vse_out_.function_did_config, 7, diag_inhibit_result_.bsd_inhibit);
        SetDiagBitToValue(vse_out_.function_did_config, 8, diag_inhibit_result_.dow_inhibit);
        SetDiagBitToValue(vse_out_.function_did_config, 9, diag_inhibit_result_.lka_inhibit);
        SetDiagBitToValue(vse_out_.function_did_config, 10, diag_inhibit_result_.ldw_inhibit);

        
        vse_out_.state_machine_sts = long_ctrl_info.state_machine.state_machine_sts;

        float time = math::Clamp(static_cast<float>(vse_out_.veh_time_stamp - time_info_.cur_time) / 1000000.F, 0.0F, 500.F);
        ego_delta_last_cycle = vse_.TransformPosForDelay(time);

        // 做好时间记录
        if (obs_time_comp.fus_comp.input_time != fusioninfo.time) {
            obs_time_comp.fus_comp.f_input_update = true;

            obs_time_comp.fus_comp.input_time = fusioninfo.time;
            obs_time_comp.fus_comp.delta_time = math::Clamp(static_cast<float>(vse_out_.veh_time_stamp - fusioninfo.time) / 1000000.F, 0.0F, 500.F);
            obs_time_comp.fus_comp.delta_ego = vse_.TransformPosForDelay(obs_time_comp.fus_comp.delta_time);
        } else {
            obs_time_comp.fus_comp.f_input_update = false;
        }

        if (obs_time_comp.gop_comp.input_time != fusioninfo.gop_time) {
            obs_time_comp.gop_comp.f_input_update = true;

            obs_time_comp.gop_comp.input_time = fusioninfo.gop_time;
            obs_time_comp.gop_comp.delta_time =
                math::Clamp(static_cast<float>(vse_out_.veh_time_stamp - fusioninfo.gop_time) / 1000000.F, 0.0F, 500.F);
            obs_time_comp.gop_comp.delta_ego = vse_.TransformPosForDelay(obs_time_comp.gop_comp.delta_time);
        } else {
            obs_time_comp.gop_comp.f_input_update = false;
        }
    }

    MappingMebCmd(meb_info, vse_out_.speed);

    uint64_t brake_point_time = 1786174148099227039;
    if (vse_out_.veh_time_stamp == brake_point_time) {
        vse_out_.veh_time_stamp = brake_point_time;
    }
    //    if (vse_out_.long_accel < -1.0F) {
    //        vse_out_.long_accel   = 0.0F;
    //        float cv              = 5.4F;
    //        vse_out_.vcs_long_vel = cv;
    //        vse_out_.speed        = cv;
    //    }

    //     printf("***************************************************\n");
    //     printf("VehTime:%ld\n", vse_out_.veh_time_stamp);

    //     printf("Spd:%f,Accel:%f,StrAng:%f,StrAngRate:%f,Yaw:%f\n", vse_out_.speed, vse_out_.long_accel, vse_out_.steerwheelangle,
    //            vse_out_.steerwheelangle_rate, vse_out_.yawrate);

    for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
        obs_list_[i]->UpdateObstacle(fusioninfo.trk[i], vse_out_, obs_time_comp, ego_delta_last_cycle);
    }

    lgsf_threat_tgt_.SelectLongThreatTgt(vse_out_, obs_list_, global_config_);
    lgsf_func_.Update(vse_out_, lgsf_threat_tgt_.aeb_target, global_config_, lgsf_threat_tgt_.ego_path_);

    //是否切换新版目标筛选控制结果进行输出
    use_new_tar_select_out = global_config_.k_Lgsf_EnNewTarSelectOut;

    if(use_new_tar_select_out){

        lgsf_2024_.UpdateNewTsel(vse_out_,lgsf_threat_tgt_.aeb_target,lgsf_2024_param_,diag_inhibit_result_.aeb_inhibit,global_config_);
    }else{

        lgsf_2024_.Update(vse_out_, obs_list_, road_info, lgsf_2024_param_, diag_inhibit_result_.aeb_inhibit,global_config_);
    }
    senseAD::tap::AsParamConfig_T pm_new;
    (void)memcpy(&pm_new, &lgsf_2024_param_, sizeof(lgsf_2024_param_));
    lgsf_2024_new_.UpdateNewTsel(vse_out_, lgsf_threat_tgt_.aeb_target, pm_new);

    bsd_func_.Update(vse_out_, global_config_, obs_list_);
    dow_func_.Update(vse_out_, global_config_, obs_list_);
    rcw_func_.Update(vse_out_, global_config_, obs_list_);
    cts_func_.Update(vse_out_, global_config_, obs_list_);
    elk_func_.Update(vse_out_, road_info, global_config_, obs_list_);
    lka_func_.Update(vse_out_, elk_func_.getElkEnvironmentProcessObj(), global_config_,
                     static_cast<uint8_t>(elk_func_.getElkStateMachineObj().getCurrentState()),
                     long_ctrl_info.state_machine.mcu_lfp_actv_cdt, control_time_ns);
    ldw_func_.Update(vse_out_, elk_func_.getElkEnvironmentProcessObj(), global_config_);

    // AES/ESA 逐帧推进
    // 对向/超车目标来自 elk_func_，主目标来自 lgsf_2024_，目标长宽来自 AEB 选择输出。
    // global_config_ 透传到 aes_esa_.Update，用于后续统一接入 shadow/enable 门控。
    const auto &aeb_sel = lgsf_2024_.GetSelectOut();
    ::Reserved_Input reserved_input{};
    reserved_input.last_aes_active = last_aes_activated_;
    reserved_input.aes_float_reserv1 = global_config_.k_AES_esafeedback_factor;
    reserved_input.aes_uint32_reserv1 = global_config_.k_AES_feedbackopen;

    const auto& ltap_out = lgsf_2024_.GetLtapOut();
    // fcw内部风险标志位
    const auto& fcw_threat_flag = ltap_out.AEBFunc.FCW.ActtnDataFromCllsnFwdWarnCtrl.WarnReq;
    // 输出fcw_threat_flag标志位 借用cmd_output_.resv2 传送给Aes模块
    lgsf_2024_.SetFcwThreatFlag(fcw_threat_flag);   

    aes_esa_.Update(fusioninfo, road_info, vse_out_, elk_func_.getElkTargetSelectionObj().GetOncomingOutput(), elk_func_.getElkTargetSelectionObj().GetOvertakingOutput(), lgsf_2024_.GetCmd(),
                    global_config_, reserved_input,aeb_sel.longsafe_aeb.length, aeb_sel.longsafe_aeb.width);
    // AEB/AES仲裁
    ActuatorArbitrate();
    last_aes_activated_ = aes_esa_.GetAesEsaCmd().active_flag;

    // printf("LgtPos:%f,ReqAccel:%f\n", lgsf_func_.lgsf_out_.tgt.posx, lgsf_func_.lgsf_out_.aeb_tar_dec);
    // printf("AebState:%d\n", (int)lgsf_func_.aeb_state_);
    // printf("DowState:%d\n", (int)dow_func_.dow_out_.state);
    // printf("FctaState:%d LeftLevel:%d RightLevel:%d BrakeState:%d\n", (int)cts_func_.front.state, (int)cts_func_.fcta_warn_info_[0].cur_level,
    //        (int)cts_func_.fcta_warn_info_[1].cur_level, (int)cts_func_.front.brake_state);
    // if (cts_func_.fcta_warn_info_[1].obs_index >= 0) {
    //     printf("FrontRightCrashX:%f\n", cts_func_.obs_data_[cts_func_.fcta_warn_info_[1].obs_index].attr[0].intersect_pt.x);
    // }
    // printf("RctsState:%d LeftLevel:%d RightLevel:%d BrakeState:%d\n", (int)cts_func_.rear.state, (int)cts_func_.rcta_warn_info_[0].cur_level,
    //        (int)cts_func_.rcta_warn_info_[1].cur_level, (int)cts_func_.rear.brake_state);

    // 输出功能状态
    CalcShadowMode();

    // 输出总时间
    time_info_.cur_time = vse_out_.veh_time_stamp;
    time_info_.fus_time = fusioninfo.time;
    time_info_.roadgeometry_time = road_info.time;
    time_info_.vehicle_time = vse_out_.veh_time_stamp;
    time_info_.gop_time = fusioninfo.gop_time;
    time_info_.vehicle_cmd_time = meb_info.meb_cmd.time;
    time_info_.occ_time = 0;
    time_info_.resv1_time = meb_info.uic_cmd.time;
    time_info_.resv2_time = long_ctrl_info.long_ctrl.time;
    time_info_.resv3_time = 0;
    time_info_.tap_mode = 0;
    time_info_.tsel_lgsf_cnt = global_config_.k_use_new_swc;
    time_info_.tsel_sf_cnt = 0;
    time_info_.ctrl_lgsf_cnt = 0;
    time_info_.ctrl_sf_cnt = 0;
}

void ActiveSafetyWrapper::RunFaultMonitor(uint32_t fault_type, uint32_t function_inhibit_mask) {
    {
        std::lock_guard<std::mutex> lock(fault_mtx_);
        fault_type_ = static_cast<uint32_t>(fault_type);
        function_inhibit_mask_ = static_cast<uint32_t>(function_inhibit_mask);
    }
}

uint32_t ActiveSafetyWrapper::GetFaultType() const {
    uint32_t res;
    {
        std::lock_guard<std::mutex> lock(fault_mtx_);
        res = fault_type_;
    }
    return res;
}

LongSafeAebTargetSnapshot ActiveSafetyWrapper::GetLongSafeAebTargetSnapshot()
    const {
    std::lock_guard<std::mutex> lock(threat_assor_mtx);
    const auto &target = lgsf_2024_.GetSelectOut().longsafe_aeb;
    return {target.fus_trkId, target.ttc, target.status};
}

void ActiveSafetyWrapper::RunPathPlanning(uint64_t time) {
    (void)time;
    AsVseOut vse_out;
    {
        std::lock_guard<std::mutex> lock(vse_mtx_);
        vse_out = vse_out_;
    }

    {
        // 获取目标选择输出互斥
    }

    // 执行PP
    {
        // 打包PP的时间
    }
}

void ActiveSafetyWrapper::CalcShadowMode() {
    shadow_mode = 0;
    if (trust_meb_complete) {
        shadow_mode |= meb_cmd_.shadow_mode;
    } else {
        if (global_config_.k_aeb_enable) {
            shadow_mode |= lgsf_2024_.GetCmd().shadow_mode;

        } else if (global_config_.k_use_shadowmode) {

            shadow_mode |= global_config_.k_use_shadowmode;
        }
    }
    if ((lgsf_func_.aeb_state_ == AebStatus::AEB_Active || lgsf_func_.aeb_state_ == AebStatus::EBA_Active ||
        lgsf_func_.fcw_state_ == FcwStatus::FCW_Active)&&(global_config_.k_aeb_enable)) {
        shadow_mode |= AsShadowMode::SCENE1;
        }
    if (lgsf_2024_new_.GetCmd().shadow_mode & 62) {
        shadow_mode |= AsShadowMode::SCENE2;
    }

    // SideFeature 功能的状态设置（始终检查，不受影子模式影响）
    if ((bsd_func_.m_bsd_out.state == BsdState::ACTIVE)  &&  global_config_.k_bsd_enable) {
        shadow_mode |= AsShadowMode::BSD;
    }
    if ((rcw_func_.m_rcw_out.state == RcwState::ACTIVE)  &&  global_config_.k_rcw_enable) {
        shadow_mode |= AsShadowMode::RCW;
    }
    if ((dow_func_.m_dow_out.state == DowState::ACTIVE)  &&  global_config_.k_dow_enable) {
        shadow_mode |= AsShadowMode::DOW;
    }
    if ((cts_func_.m_front.warn_state == CtsState::ACTIVE)  &&  global_config_.k_cta_enable) {
        shadow_mode |= AsShadowMode::FCTA;
    }
    if ((cts_func_.m_front.brake_state == CtsState::ACTIVE)  &&  global_config_.k_ctb_enable) {
        shadow_mode |= AsShadowMode::FCTB;
    }
    if ((cts_func_.m_rear.warn_state == CtsState::ACTIVE)  &&  global_config_.k_cta_enable) {
        shadow_mode |= AsShadowMode::RCTA;
    }
    if ((cts_func_.m_rear.brake_state == CtsState::ACTIVE)  &&  global_config_.k_ctb_enable) {
        shadow_mode |= AsShadowMode::RCTB;
    }
    // mode == 4 表示 AES 激活；mode == 5 表示 ESA 激活
    if (global_config_.k_aes_enable) {
        const auto& aes_mode = aes_esa_.GetAesEsaCmd().mode;
        if (aes_mode == 4U) {
            shadow_mode |= AsShadowMode::AES;
        } else if (aes_mode == 5U) {
            shadow_mode |= AsShadowMode::ESA;
        }
    }
    // LSS 功能的状态设置
    if (ldw_func_.getLdwStateMachineObj().getCurrentState() == ldw::LdwStateMachine::State::LeftWarning ||
        ldw_func_.getLdwStateMachineObj().getCurrentState() == ldw::LdwStateMachine::State::RightWarning) {
        shadow_mode |= AsShadowMode::LDW;
    }
    if (lka_func_.getLkaStateMachineObj().getCurrentState() == lka::LkaStateMachine::State::LeftIntervention ||
        lka_func_.getLkaStateMachineObj().getCurrentState() == lka::LkaStateMachine::State::RightIntervention) {
        shadow_mode |= AsShadowMode::LKA;
    }
    if (elk_func_.getElkStateMachineObj().getCurrentState() == elk::ElkStateMachine::State::Left_Intervention ||
        elk_func_.getElkStateMachineObj().getCurrentState() == elk::ElkStateMachine::State::Right_Intervention) {
        shadow_mode |= AsShadowMode::ELK;
    }
}

void ActiveSafetyWrapper::MappingMebCmd(const MebMsgInfo &meb_info, float host_spd) {
    (void)memset(&meb_cmd_, 0, sizeof(meb_cmd_));
    trust_meb_complete = meb_info.uic_cmd.trust_meb_complete;
    if (meb_info.meb_cmd.brake.brakeMode == BrakeMode::emergency) {
        meb_cmd_.aeb_req = senseAD::tap::OnOffStatus::Active;
        meb_cmd_.aeb_status = senseAD::tap::AebStatus::AEB_ACTIVE;
        meb_cmd_.aeb_req_valid = 1;
        meb_cmd_.aeb_tar_dec = -8.0;
        meb_cmd_.shadow_mode = 2;
        if (host_spd < 0.001F) {
            meb_cmd_.hold_type = 2;
        } else {
            meb_cmd_.hold_type = 1;
        }
    }
}

bool ActiveSafetyWrapper::LoadJsonParam(const json11::Json &config) {
    if (!JsonParse<decltype(global_config_.k_use_shadowmode)>(config, "longsafe_config", "k_use_shadowmode", &global_config_.k_use_shadowmode))
        return false;
    if (!JsonParse<decltype(global_config_.k_aeb_enable)>(config, "longsafe_config", "k_aeb_enable", &global_config_.k_aeb_enable))
        return false;
    if (!JsonParse<decltype(global_config_.k_aes_enable)>(config, "longsafe_config", "k_aes_enable", &global_config_.k_aes_enable))
        return false;
    if (!JsonParse<decltype(global_config_.k_ctb_enable)>(config, "longsafe_config", "k_ctb_enable", &global_config_.k_ctb_enable))
        return false;
    if (!JsonParse<decltype(global_config_.k_cta_enable)>(config, "longsafe_config", "k_cta_enable", &global_config_.k_cta_enable))
        return false;
    if (!JsonParse<decltype(global_config_.k_dow_enable)>(config, "longsafe_config", "k_dow_enable", &global_config_.k_dow_enable))
        return false;
    if (!JsonParse<decltype(global_config_.k_bsd_enable)>(config, "longsafe_config", "k_bsd_enable", &global_config_.k_bsd_enable))
        return false;
    if (!JsonParse<decltype(global_config_.k_rcw_enable)>(config, "longsafe_config", "k_rcw_enable", &global_config_.k_rcw_enable))
        return false;
    if (!JsonParse<decltype(global_config_.k_use_new_swc)>(config, "longsafe_config", "k_use_new_swc", &global_config_.k_use_new_swc))
        return false;
    if (!JsonParse<decltype(global_config_.k_Lgsf_EnCutOutSceneCheck)>(config, "longsafe_config", "k_Lgsf_EnCutOutSceneCheck", &global_config_.k_Lgsf_EnCutOutSceneCheck))
        return false;
    if (!JsonParse<decltype(global_config_.k_Lgsf_EnWaitAesActive)>(config, "longsafe_config", "k_Lgsf_EnWaitAesActive", &global_config_.k_Lgsf_EnWaitAesActive))
        return false;
    if (!JsonParse<decltype(global_config_.k_Lgsf_EnSocAesAebArb)>(config, "longsafe_config", "k_Lgsf_EnSocAesAebArb", &global_config_.k_Lgsf_EnSocAesAebArb))
        return false;
    if (!JsonParse<decltype(global_config_.k_Lgsf_EnNewTarSelectOut)>(config, "longsafe_config", "k_Lgsf_EnNewTarSelectOut", &global_config_.k_Lgsf_EnNewTarSelectOut))
        return false;
    if (!JsonParse<decltype(global_config_.k_Lgsf_EnReverseTrajPred)>(config, "longsafe_config", "k_Lgsf_EnReverseTrajPred", &global_config_.k_Lgsf_EnReverseTrajPred))
        return false;
    if (!JsonParse<decltype(global_config_.k_Lgsf_ForOldRsclBag)>(config, "longsafe_config", "k_Lgsf_ForOldRsclBag", &global_config_.k_Lgsf_ForOldRsclBag))
        return false;
    // parse 2024 param.
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_UseShadowMode)>(config, "longsafe_config", "k_use_shadowmode",
                                                                    &lgsf_2024_param_.k_LgSf_UseShadowMode))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_AEB_Enable)>(config, "longsafe_config", "k_aeb_enable", &lgsf_2024_param_.k_LgSf_AEB_Enable))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnCone)>(config, "longsafe_param", "k_LgSf_EnCone", &lgsf_2024_param_.k_LgSf_EnCone))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnBarrier)>(config, "longsafe_param", "k_LgSf_EnBarrier", &lgsf_2024_param_.k_LgSf_EnBarrier))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_PosnLgtOffset)>(config, "longsafe_param", "k_LgSf_PosnLgtOffset",
                                                                    &lgsf_2024_param_.k_LgSf_PosnLgtOffset))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnConfInhibit)>(config, "longsafe_param", "k_LgSf_EnConfInhibit",
                                                                    &lgsf_2024_param_.k_LgSf_EnConfInhibit))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnEgoConfInhibit)>(config, "longsafe_param", "k_LgSf_EnEgoConfInhibit",
                                                                       &lgsf_2024_param_.k_LgSf_EnEgoConfInhibit))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnObsConfInhibit)>(config, "longsafe_param", "k_LgSf_EnObsConfInhibit",
                                                                       &lgsf_2024_param_.k_LgSf_EnObsConfInhibit))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnSceniaroCheck)>(config, "longsafe_param", "k_LgSf_EnSceniaroCheck",
                                                                      &lgsf_2024_param_.k_LgSf_EnSceniaroCheck))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnAWB)>(config, "longsafe_param", "k_LgSf_EnAWB", &lgsf_2024_param_.k_LgSf_EnAWB))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_MinAebDecelValue)>(config, "longsafe_param", "k_LgSf_MinAebDecelValue",
                                                                       &lgsf_2024_param_.k_LgSf_MinAebDecelValue))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnHighMiles)>(config, "longsafe_param", "k_LgSf_EnHighMiles",
                                                                  &lgsf_2024_param_.k_LgSf_EnHighMiles))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnSimulationMode)>(config, "longsafe_param", "k_LgSf_EnSimulationMode",
                                                                       &lgsf_2024_param_.k_LgSf_EnSimulationMode))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_ActiveSafeMode)>(config, "longsafe_param", "k_LgSf_ActiveSafeMode",
                                                                     &lgsf_2024_param_.k_LgSf_ActiveSafeMode))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_ignore_roadedge_check)>(config, "longsafe_param", "k_ignore_roadedge_check",
                                                                       &lgsf_2024_param_.k_ignore_roadedge_check))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnTestScene)>(config, "longsafe_param", "k_LgSf_EnTestScene",
                                                                  &lgsf_2024_param_.k_LgSf_EnTestScene))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnOcc)>(config, "longsafe_param", "k_LgSf_EnOcc",
                                                                  &lgsf_2024_param_.k_LgSf_EnOcc))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_EnAebDecelNoFilter)>(config, "longsafe_param", "k_LgSf_EnAebDecelNoFilter",
                                                                  &lgsf_2024_param_.k_LgSf_EnAebDecelNoFilter))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_LgSf_AebVehSpdRednLim)>(config, "longsafe_param", "k_LgSf_AebVehSpdRednLim",
                                                                      &lgsf_2024_param_.k_LgSf_AebVehSpdRednLim))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_AEB_FullBrkSpdThres)>(config, "longsafe_param", "k_AEB_FullBrkSpdThres",
                                                                      &lgsf_2024_param_.k_AEB_FullBrkSpdThres))
        return false;
    if (!JsonParse<decltype(lgsf_2024_param_.k_AEB_HighReqDecel)>(config, "longsafe_param", "k_AEB_HighReqDecel",
                                                                  &lgsf_2024_param_.k_AEB_HighReqDecel))
        return false;
    if (!JsonParse<decltype(diag_param_.k_enable_aeb_diag)>(config, "diag_param", "k_enable_aeb_diag", &diag_param_.k_enable_aeb_diag))

        return false;
    if (!JsonParse<decltype(diag_param_.k_enable_bsd_diag)>(config, "diag_param", "k_enable_bsd_diag", &diag_param_.k_enable_bsd_diag))

        return false;
    if (!JsonParse<decltype(diag_param_.k_enable_dow_diag)>(config, "diag_param", "k_enable_dow_diag", &diag_param_.k_enable_dow_diag))

        return false;
    if (!JsonParse<decltype(diag_param_.k_enable_elk_diag)>(config, "diag_param", "k_enable_elk_diag", &diag_param_.k_enable_elk_diag))

        return false;
    if (!JsonParse<decltype(diag_param_.k_enable_esa_diag)>(config, "diag_param", "k_enable_esa_diag", &diag_param_.k_enable_esa_diag))

        return false;
    if (!JsonParse<decltype(diag_param_.k_enable_fcta_diag)>(config, "diag_param", "k_enable_fcta_diag", &diag_param_.k_enable_fcta_diag))

        return false;
    if (!JsonParse<decltype(diag_param_.k_enable_ldw_diag)>(config, "diag_param", "k_enable_ldw_diag", &diag_param_.k_enable_ldw_diag))

        return false;
    if (!JsonParse<decltype(diag_param_.k_enable_lka_diag)>(config, "diag_param", "k_enable_lka_diag", &diag_param_.k_enable_lka_diag))

        return false;
    if (!JsonParse<decltype(diag_param_.k_enable_locp_diag)>(config, "diag_param", "k_enable_locp_diag", &diag_param_.k_enable_locp_diag))

        return false;
    if (!JsonParse<decltype(diag_param_.k_enable_rcta_diag)>(config, "diag_param", "k_enable_rcta_diag", &diag_param_.k_enable_rcta_diag))

        return false;
    if (!JsonParse<decltype(diag_param_.k_enable_rcw_diag)>(config, "diag_param", "k_enable_rcw_diag", &diag_param_.k_enable_rcw_diag))
        return false;
    // LSS config
    if (!JsonParse<decltype(global_config_.k_LDW_func_enable)>(config, "latsafe_config", "k_LDW_func_enable",
                                                                       &global_config_.k_LDW_func_enable))
        return false;
    if (!JsonParse<decltype(global_config_.k_LKA_func_enable)>(config, "latsafe_config", "k_LKA_func_enable",
                                                                       &global_config_.k_LKA_func_enable))
        return false;
    if (!JsonParse<decltype(global_config_.k_ELK_func_enable)>(config, "latsafe_config", "k_ELK_func_enable",
                                                                       &global_config_.k_ELK_func_enable))
        return false;
    if (!JsonParse<decltype(global_config_.k_LKA_HandoffWarningEnable)>(config, "latsafe_config", "k_LKA_HandoffWarningEnable",
                                                                        &global_config_.k_LKA_HandoffWarningEnable))
        return false;
    if (!JsonParse<decltype(global_config_.k_LDW_EnLine)>(config, "latsafe_config", "k_LDW_EnLine",
                                                                       &global_config_.k_LDW_EnLine))
        return false;
    if (!JsonParse<decltype(global_config_.k_LDW_EnEdge)>(config, "latsafe_config", "k_LDW_EnEdge",
                                                                       &global_config_.k_LDW_EnEdge))
        return false;
    if (!JsonParse<decltype(global_config_.k_ELK_EnLct)>(config, "latsafe_config", "k_ELK_EnLct",
                                                                       &global_config_.k_ELK_EnLct))
        return false;
    if (!JsonParse<decltype(global_config_.k_ELK_EnEdge)>(config, "latsafe_config", "k_ELK_EnEdge",
                                                                       &global_config_.k_ELK_EnEdge))
        return false;
    if (!JsonParse<decltype(global_config_.k_ELK_EnSld)>(config, "latsafe_config", "k_ELK_EnSld",
                                                                       &global_config_.k_ELK_EnSld))
        return false;
    if (!JsonParse<decltype(global_config_.k_ELK_bUsLowRtNearTrg)>(config, "latsafe_config", "k_ELK_bUsLowRtNearTrg",
                                                                       &global_config_.k_ELK_bUsLowRtNearTrg))
        return false;
    if (config["latsafe_config"]["k_LSS_IgnoreFaultInhibit"].is_number()) {
        global_config_.k_LSS_IgnoreFaultInhibit =
            static_cast<bool>(config["latsafe_config"]["k_LSS_IgnoreFaultInhibit"].number_value());
    }
    if (config["latsafe_config"]["k_ELK_DebugLogEnable"].is_number()) {
        global_config_.k_ELK_DebugLogEnable =
            static_cast<bool>(config["latsafe_config"]["k_ELK_DebugLogEnable"].number_value());
    }
    if (!JsonParse<decltype(global_config_.k_ELK_OC_ObjTTCScale)>(config, "latsafe_config", "k_ELK_OC_ObjTTCScale",
                                                                  &global_config_.k_ELK_OC_ObjTTCScale))
        return false;
    if (!JsonParse<decltype(global_config_.k_ELK_OT_ObjTTCScale)>(config, "latsafe_config", "k_ELK_OT_ObjTTCScale",
                                                                  &global_config_.k_ELK_OT_ObjTTCScale))
        return false;
    if (!JsonParse<decltype(global_config_.k_ELK_LCT_TTLCScale)>(config, "latsafe_config", "k_ELK_LCT_TTLCScale",
                                                                 &global_config_.k_ELK_LCT_TTLCScale))
        return false;
    if (!JsonParse<decltype(global_config_.k_ELK_SLD_TTLCScale)>(config, "latsafe_config", "k_ELK_SLD_TTLCScale",
                                                                 &global_config_.k_ELK_SLD_TTLCScale))
        return false;
    if (!JsonParse<decltype(global_config_.k_ELK_ROR_TTLCScale)>(config, "latsafe_config", "k_ELK_ROR_TTLCScale",
                                                                 &global_config_.k_ELK_ROR_TTLCScale))
        return false;
    if (!JsonParse<decltype(global_config_.k_LKA_TTLCScale)>(config, "latsafe_config", "k_LKA_TTLCScale",
                                                             &global_config_.k_LKA_TTLCScale))
        return false;
    if (!JsonParse<decltype(global_config_.k_LDW_TTLCScale)>(config, "latsafe_config", "k_LDW_TTLCScale",
                                                             &global_config_.k_LDW_TTLCScale))
        return false;
    if (!JsonParse<decltype(global_config_.k_LKA_LDW_EnDriftingTrigger)>(config, "latsafe_config", "k_LKA_LDW_EnDriftingTrigger",
                                                                        &global_config_.k_LKA_LDW_EnDriftingTrigger))
        return false;
    if (!JsonParse<decltype(global_config_.k_ELK_Aligned_OnDelayTime)>(config, "latsafe_config", "k_ELK_Aligned_OnDelayTime",
                                                                       &global_config_.k_ELK_Aligned_OnDelayTime))
        return false;
    if (!JsonParse<decltype(global_config_.k_LKA_Centered_OnDelayTime)>(config, "latsafe_config", "k_LKA_Centered_OnDelayTime",
                                                                       &global_config_.k_LKA_Centered_OnDelayTime))
        return false;
    if (!JsonParse<decltype(global_config_.k_AES_aebactive_enable)>(config, "latsafe_config", "k_AES_aebactive_enable",
                                                                       &global_config_.k_AES_aebactive_enable))
        return false;
    if (!JsonParse<decltype(global_config_.k_AES_esafeedback_factor)>(config, "latsafe_config", "k_AES_esafeedback_factor",
                                                                       &global_config_.k_AES_esafeedback_factor))
        return false;
    if (!JsonParse<decltype(global_config_.k_AES_feedbackopen)>(config, "latsafe_config", "k_AES_feedbackopen",
                                                                       &global_config_.k_AES_feedbackopen))
        return false;
    return true;
}

template <typename T> bool ActiveSafetyWrapper::JsonParse(const json11::Json &config, std::string param, std::string key, T *value) {
    if (config[param][key].is_number()) {
        // TODO: check T type
        *value = static_cast<T>(config[param][key].number_value());
    } else {
        return false;
    }
    return true;
}

template <typename T, std::size_t N>
bool ActiveSafetyWrapper::JsonParse(const json11::Json &config, std::string param, std::string key, std::array<T, N> *value) {
    if (config[param][key].is_array()) {
        auto n = config[param][key].array_items().size();
        auto m = value->size();
        if (n != m) {
            return false;
        }
        for (auto i = 0; i < n && i < m; ++i) {
            (*value)[i] = static_cast<T>(config[param][key].array_items().at(i).number_value());
        }
    } else {
        return false;
    }
    return true;
}

template <typename T, std::size_t M, std::size_t N>
bool ActiveSafetyWrapper::JsonParse(const json11::Json &config, std::string param, std::string key, std::array<std::array<T, M>, N> *value) {
    if (config[param][key].is_array()) {
        auto n = config[param][key].array_items().size();
        auto m = value->size();
        if (n != m) {
            return false;
        }
        for (auto i = 0; i < n && i < m; ++i) {
            if (config[param][key].array_items().at(0).is_array()) {
                auto nn = config[param][key].array_items().at(i).array_items().size();
                auto mm = (*value)[0].size();
                if (nn != mm) {
                    return false;
                }
                for (auto j = 0; j < nn && j < mm; ++j) {
                    (*value)[i][j] = static_cast<T>(config[param][key].array_items().at(i).array_items().at(j).number_value());
                }
            } else {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

} // namespace active_safety
