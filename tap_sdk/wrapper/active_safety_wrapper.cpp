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

ActiveSafetyWrapper::~ActiveSafetyWrapper() {
}

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
    vse_.Run(vse_input, curtime);
}

void ActiveSafetyWrapper::RunTselCtrl(const FusionInfo &fusioninfo, const LanesInfo &road_info, const LongCtrlInfo &long_ctrl_info,
                                      const MebMsgInfo &meb_info) {
    // SetInput
    ObsTimeComp obs_time_comp;
    Eigen::Vector3f ego_delta_last_cycle;
    {
        std::lock_guard<std::mutex> lock(vse_mtx_);
        vse_out_ = vse_.vse_ipc_;
        obs_time_comp.fus_comp.delta_time = math::Clamp(static_cast<float>(vse_out_.veh_time_stamp - fusioninfo.time) / 1000000.f, 0.0f, 500.f);
        obs_time_comp.fus_comp.delta_ego = vse_.TransformPosForDelay(obs_time_comp.fus_comp.delta_time);

        obs_time_comp.gop_comp.delta_time = math::Clamp(static_cast<float>(vse_out_.veh_time_stamp - fusioninfo.gop_time) / 1000000.f, 0.0f, 500.f);
        obs_time_comp.gop_comp.delta_ego = vse_.TransformPosForDelay(obs_time_comp.gop_comp.delta_time);

        float time = math::Clamp(static_cast<float>(vse_out_.veh_time_stamp - time_info_.cur_time) / 1000000.f, 0.0f, 500.f);
        ego_delta_last_cycle = vse_.TransformPosForDelay(time);
    }

    MappingMebCmd(meb_info, vse_out_.speed);

    uint64_t brake_point_time = 1768036769420288970;
    if (vse_out_.veh_time_stamp == brake_point_time) {
        vse_out_.veh_time_stamp = brake_point_time;
    }
    //    if (vse_out_.long_accel < -1.0f) {
    //        vse_out_.long_accel   = 0.0f;
    //        float cv              = 5.4f;
    //        vse_out_.vcs_long_vel = cv;
    //        vse_out_.speed        = cv;
    //    }

    // printf("***************************************************\n");
    // printf("VehTime:%ld\n", vse_out_.veh_time_stamp);

    // printf("Spd:%f,Accel:%f,StrAng:%f,StrAngRate:%f,Yaw:%f\n", vse_out_.speed, vse_out_.long_accel, vse_out_.steerwheelangle,
    //        vse_out_.steerwheelangle_rate, vse_out_.yawrate);

    for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
        obs_list_[i]->UpdateObstacle(fusioninfo.trk[i], vse_out_, obs_time_comp, ego_delta_last_cycle);
    }

#if USE_LONGSAFE_LEGACY
    lgsf_threat_tgt_.SelectLongThreatTgt(vse_out_, obs_list_);
    lgsf_func_.Update(vse_out_, lgsf_threat_tgt_.aeb_target, global_config_, lgsf_threat_tgt_.ego_path_);
#endif

    lgsf_2024_.Update(vse_out_, obs_list_, road_info, lgsf_2024_param_);

    bsd_func_.Update(vse_out_, global_config_, obs_list_);
    dow_func_.Update(vse_out_, global_config_, obs_list_);
    rcw_func_.Update(vse_out_, global_config_, obs_list_);
    cts_func_.Update(vse_out_, global_config_, obs_list_);
    elk_func_.Update(vse_out_, road_info, global_config_, obs_list_);
#if USE_LONGSAFE_LEGACY
    // printf("LgtPos:%f,ReqAccel:%f\n", lgsf_func_.lgsf_out_.tgt.posx, lgsf_func_.lgsf_out_.aeb_tar_dec);
    // printf("AebState:%d\n", (int)lgsf_func_.aeb_state_);
#endif
    // printf("DowState:%d\n", (int)dow_func_.dow_out_.state);
    // printf("FctaState:%d LeftLevel:%d RightLevel:%d BrakeState:%d\n", (int)cts_func_.front.state, (int)cts_func_.fcta_warn_info_[0].cur_level,
    //        (int)cts_func_.fcta_warn_info_[1].cur_level, (int)cts_func_.front.brake_state);
    // if (cts_func_.fcta_warn_info_[1].obs_index >= 0) {
    //     printf("FrontRightCrashX:%f\n", cts_func_.obs_data_[cts_func_.fcta_warn_info_[1].obs_index].attr[0].intersect_pt.x);
    // }
    // printf("RctsState:%d LeftLevel:%d RightLevel:%d BrakeState:%d\n", (int)cts_func_.rear.state, (int)cts_func_.rcta_warn_info_[0].cur_level,
    //        (int)cts_func_.rcta_warn_info_[1].cur_level, (int)cts_func_.rear.brake_state);
    {
        //获取PP信息
    }

    //输出功能状态
    CalcShadowMode();

    //输出总时间
    time_info_.cur_time = vse_out_.veh_time_stamp;
    time_info_.fus_time = fusioninfo.time;
    time_info_.roadgeometry_time = road_info.time;
    time_info_.vehicle_time = vse_out_.veh_time_stamp;
    time_info_.gop_time = fusioninfo.gop_time;
    time_info_.vehicle_cmd_time = meb_info.meb_cmd.time;
    time_info_.occ_time = 0;
    time_info_.resv1_time = meb_info.uic_cmd.time;
    time_info_.resv2_time = long_ctrl_info.time;
    time_info_.resv3_time = 0;
    time_info_.tap_mode = 0;
#if USE_LONGSAFE_LEGACY
    time_info_.tsel_lgsf_cnt = global_config_.k_use_new_swc;
#else
    time_info_.tsel_lgsf_cnt = 0;
#endif
    time_info_.tsel_sf_cnt = 0;
    time_info_.ctrl_lgsf_cnt = 0;
    time_info_.ctrl_sf_cnt = 0;
}

void ActiveSafetyWrapper::RunFaultMonitor(uint32_t fault_type) {
    {
        std::lock_guard<std::mutex> lock(fault_mtx_);
        fault_type_ = static_cast<uint32_t>(fault_type);
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

void ActiveSafetyWrapper::RunPathPlanning(uint64_t time) {
    (void)time;
    AsVseOut vse_out;
    {
        std::lock_guard<std::mutex> lock(vse_mtx_);
        vse_out = vse_out_;
    }

    {
        //获取目标选择输出互斥

    }

    //执行PP
    {
        //打包PP的时间
    }
}

void ActiveSafetyWrapper::CalcShadowMode() {
    shadow_mode = 0;
    if (trust_meb_complete) {
        shadow_mode |= meb_cmd_.shadow_mode;
    } else {
        if (global_config_.k_use_shadowmode) {
            shadow_mode |= AsShadowMode::SHADOWMODE;
#if USE_LONGSAFE_LEGACY
            if (global_config_.k_use_new_swc) {
                //输出Trigger：lgsf_2024触发AEB/EBA/FCW时，结果放到AEB位
                // 14 = 0b1110 = Bit1|Bit2|Bit3 (AEB|EBA|FCW)
                if ((lgsf_2024_.GetCmd().shadow_mode & 14) > 0) {
                    shadow_mode |= AsShadowMode::AEB;
                }
                if (lgsf_func_.aeb_state_ == AebStatus::AEB_Active || lgsf_func_.aeb_state_ == AebStatus::EBA_Active ||
                    lgsf_func_.fcw_state_ == FcwStatus::FCW_Active) {
                    shadow_mode |= AsShadowMode::FCW;
                }
            } else {
                shadow_mode |= lgsf_2024_.GetCmd().shadow_mode;
            }
#else
            shadow_mode |= lgsf_2024_.GetCmd().shadow_mode;
#endif

        } else if (global_config_.k_use_new_swc) {
#if USE_LONGSAFE_LEGACY
            if (lgsf_func_.aeb_state_ == AebStatus::AEB_Active) {
                shadow_mode |= AsShadowMode::AEB;
            }
            if (lgsf_func_.aeb_state_ == AebStatus::EBA_Active) {
                shadow_mode |= AsShadowMode::EBA;
            }
            if (lgsf_func_.fcw_state_ == FcwStatus::FCW_Active) {
                shadow_mode |= AsShadowMode::FCW;
            }
#else
            // longsafe legacy 不可用时，使用 lgsf_2024 的结果
            if ((lgsf_2024_.GetCmd().shadow_mode & 2) > 0) { // Bit1: AEB
                shadow_mode |= AsShadowMode::AEB;
            }
            if ((lgsf_2024_.GetCmd().shadow_mode & 4) > 0) { // Bit2: EBA
                shadow_mode |= AsShadowMode::EBA;
            }
            if ((lgsf_2024_.GetCmd().shadow_mode & 8) > 0) { // Bit3: FCW
                shadow_mode |= AsShadowMode::FCW;
            }
#endif
        } else {
            shadow_mode |= lgsf_2024_.GetCmd().shadow_mode;
        }
    }

    // SideFeature 功能的状态设置（始终检查，不受影子模式影响）
    if (bsd_func_.bsd_out_.state == BsdState::ACTIVE && global_config_.k_bsd_enable) {
        shadow_mode |= AsShadowMode::BSD;
    }
    if (rcw_func_.rcw_out_.state == RcwState::ACTIVE && global_config_.k_rcw_enable) {
        shadow_mode |= AsShadowMode::RCW;
    }
    if (dow_func_.dow_out_.state == DowState::ACTIVE && global_config_.k_dow_enable) {
        shadow_mode |= AsShadowMode::DOW;
    }
    if (cts_func_.front.warn_state == CtsState::ACTIVE && global_config_.k_cta_enable) {
        shadow_mode |= AsShadowMode::FCTA;
    }
    if (cts_func_.front.brake_state == CtsState::ACTIVE && global_config_.k_ctb_enable) {
        shadow_mode |= AsShadowMode::FCTB;
    }
    if (cts_func_.rear.warn_state == CtsState::ACTIVE && global_config_.k_cta_enable) {
        shadow_mode |= AsShadowMode::RCTA;
    }
    if (cts_func_.rear.brake_state == CtsState::ACTIVE && global_config_.k_ctb_enable) {
        shadow_mode |= AsShadowMode::RCTB;
    }
}

void ActiveSafetyWrapper::MappingMebCmd(const MebMsgInfo &meb_info, float host_spd) {
    memset(&meb_cmd_, 0, sizeof(meb_cmd_));
    trust_meb_complete = meb_info.uic_cmd.trust_meb_complete;
    if (meb_info.meb_cmd.brake.brakeMode == BrakeMode::emergency) {
        meb_cmd_.aeb_req = senseAD::tap::OnOffStatus::Active;
        meb_cmd_.aeb_status = senseAD::tap::AebStatus::AEB_ACTIVE;
        meb_cmd_.aeb_req_valid = 1;
        meb_cmd_.aeb_tar_dec = -8.0;
        meb_cmd_.shadow_mode = 2;
        if (host_spd < 0.001f) {
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
