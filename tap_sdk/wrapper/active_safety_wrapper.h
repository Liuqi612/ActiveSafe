#pragma once
#include "algorithm/bsd/bsd_function.h"
#include "algorithm/cts/cts_function.h"
#include "algorithm/dow/dow_function.h"
#include "algorithm/elk/elk_function.h"
#include "algorithm/longsafe_2024/lgsf_2024_function.h"
#include "algorithm/obstacle/obstacle.h"
#include "algorithm/rcw/rcw_function.h"
#include "algorithm/vse/vehicle_state_estimed.h"
#include "common/build_config.h"
#include "common/global_config.h"
#include "interface/active_safety_coreout.h"
#include "interface/fusion_object.h"
#include "interface/other_out.h"
#include "json11.hpp"

#include <array>
#include <mutex>

#if USE_LONGSAFE_LEGACY
#include "algorithm/longsafe/decision/lgsf_function.h"
#include "algorithm/longsafe/threat_assessor/single_threat_target.h"
#endif

namespace active_safety {

class ActiveSafetyWrapper {
  public:
    ActiveSafetyWrapper();
    ~ActiveSafetyWrapper();

    bool Init(const std::string &cali_path, uint8_t tsel_longsafe_cnt = 0, uint8_t tsel_sf_cnt = 0, uint8_t ctrl_lgsf_cnt = 0);

    void RunVse(const VseInput &vse_input, uint64_t curtime);
    void RunTselCtrl(const FusionInfo &fusioninfo, const LanesInfo &road_info, const LongCtrlInfo &long_ctrl_info, const MebMsgInfo &meb_info);
    void RunPathPlanning(uint64_t time);
    void RunFaultMonitor(uint32_t fault_type);

    uint32_t GetFaultType() const;

  private:
    bool LoadJsonParam(const json11::Json &config);
    void MappingMebCmd(const MebMsgInfo &meb_info, float host_spd);

    void CalcShadowMode();
    // Json解析单变量
    template <typename T> bool JsonParse(const json11::Json &config, std::string param, std::string key, T *value);
    // Json解析一维数组变量
    template <typename T, std::size_t N> bool JsonParse(const json11::Json &config, std::string param, std::string key, std::array<T, N> *value);
    // Json解析多维数组变量
    template <typename T, std::size_t M, std::size_t N>
    bool JsonParse(const json11::Json &config, std::string param, std::string key, std::array<std::array<T, M>, N> *value);

  public:
    // Bit0: LongSafe || SideFeature任一功能打开
    // Bit1: AEB
    // Bit2: EBA
    // Bit3: FCW
    // Bit4: DW
    // Bit5: AWB
    // Bit6: DOW
    // Bit7: RCW
    // Bit8: FCTA
    // Bit9: FCTB
    // Bit10: RCTA
    // Bit11: RCTB
    // Bit12: BSD
    // Bit13: LCA
    uint32_t shadow_mode;
    //外部可修改的配置
    GlobalConfig global_config_;
    senseAD::tap::AsParamConfig_T lgsf_2024_param_;

    AsTimeInfo time_info_;
    //输入融合目标信息
    AsObstacleList obs_list_;
    //故障监控信息
    mutable std::mutex fault_mtx_;
    uint32_t fault_type_;
    //车辆估计
    std::mutex vse_mtx_; // 保护VSE的mutex
    VehicleStateEstimed vse_;
    AsVseOut vse_out_;
    // AEB/FCW
    std::mutex threat_assor_mtx; //锁用于PP和Control的AEB/FCW目标选择结果之间的互斥.
#if USE_LONGSAFE_LEGACY
    longsafe::SingleThreatTarget lgsf_threat_tgt_;
    longsafe::LgSfFunction lgsf_func_;
#endif

    active_safety::longsafe_2024::LgSafe2024Function lgsf_2024_;
    // MEB控制输出
    senseAD::tap::AsCmdLgSafe_T meb_cmd_;

    bool trust_meb_complete = false;
    // SideFeature.
    rcw::RcwFunction rcw_func_;
    dow::DowFunction dow_func_;
    bsd::BsdFunction bsd_func_;
    cts::CtsFunction cts_func_;
    elk::ElkFunction elk_func_;
};

} // namespace active_safety
