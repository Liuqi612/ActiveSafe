#ifndef TAP_SDK_WRAPPER_ACTIVE_SAFETY_WRAPPER_H_
#define TAP_SDK_WRAPPER_ACTIVE_SAFETY_WRAPPER_H_
#include "algorithm/aes_esa/aes_esa_function.h"
#include "algorithm/bsd/bsd_function.h"
#include "algorithm/cts/cts_function.h"
#include "algorithm/dow/dow_function.h"
#include "algorithm/elk/elk_function.h"
#include "algorithm/lka/lka_function.h"
#include "algorithm/ldw/ldw_function.h"
#include "algorithm/longsafe/decision/lgsf_function.h"
#include "algorithm/longsafe/threat_assessor/single_threat_target.h"
#include "algorithm/longsafe_2024/lgsf_2024_function.h"
#include "algorithm/longsafe_2024_newtsel/lgsf_2024_function.h"
#include "algorithm/obstacle/obstacle.h"
#include "algorithm/rcw/rcw_function.h"
#include "algorithm/vse/vehicle_state_estimed.h"
#include "common/global_config.h"
#include "interface/active_safety_coreout.h"
#include "interface/fusion_object.h"
#include "interface/other_out.h"
#include "json11.hpp"

#include <array>
#include <mutex>

namespace active_safety {

enum class SubScene {
    UNKNOWN = 0,
    STRAIGHT_2_STATIONARY ,
    STRAIGHT_2_LONG_MOVING,
    STRAIGHT_2_CROSS,
    STRAIGHT_2_ONCOMING,
    STRAIGHT_2_CUTIN,
    TURN_2_STATIONARY,
    TURN_2_MOVING,
};

// 位操作工具函数
template<typename T>
inline void SetDiagBitToValue(T& value, const uint32_t bit_idx, const bool set_bit) {
    const T mask = T(1U) << bit_idx;
    if (set_bit) {
        value |= mask;
    } else {
        value &= ~mask;
    }
}

class ActiveSafetyWrapper {
  public:
    ActiveSafetyWrapper();
    ~ActiveSafetyWrapper();

    bool Init(const std::string &cali_path, uint8_t tsel_longsafe_cnt = 0, uint8_t tsel_sf_cnt = 0, uint8_t ctrl_lgsf_cnt = 0);

    void RunVse(const VseInput &vse_input, uint64_t curtime);
    void RunTselCtrl(const FusionInfo &fusioninfo,
                     const LanesInfo &road_info,
                     const PlanningInfo &long_ctrl_info,
                     const MebMsgInfo &meb_info,
                     uint64_t control_time_ns = 0U);
    void RunPathPlanning(uint64_t time);
    void RunFaultMonitor(uint32_t fault_type, uint32_t function_inhibit_mask);
    void DiagArbitrate();
    void ActuatorArbitrate();
    bool CheckHighSpeedFrontVehicleCutOut(const senseAD::tap::AsLongSafeObject& current_target, bool aeb_unavoid_collision_flag, bool aes_exist_steer_space);

    uint32_t GetFaultType() const;
    SubScene sub_scene_ = SubScene::UNKNOWN;

  private:
    bool last_aes_activated_ = false;
    bool last_aeb_activated_ = false;
    bool LoadJsonParam(const json11::Json &config);
    void MappingMebCmd(const MebMsgInfo &meb_info, float host_spd);

    void CalcShadowMode();
    void CalcScene(const senseAD::tap::LgSf_Ltap_T &ltap_out,
                   const longsafe::LongSafeObject &aeb_target);
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
    senseAD::tap::AsDiagParam_T diag_param_;

    ReplayFrame replay_frame_;
    AsTimeInfo time_info_;
    ObsTimeComp obs_time_comp;
    //输入融合目标信息
    AsObstacleList obs_list_;
    //故障监控信息
    mutable std::mutex fault_mtx_;
    uint32_t fault_type_;
    uint32_t function_inhibit_mask_;
    //车辆估计
    std::mutex vse_mtx_; // 保护VSE的mutex
    VehicleStateEstimed vse_;
    AsVseOut vse_out_;
    // AEB/FCW
    std::mutex threat_assor_mtx; //锁用于PP和Control的AEB/FCW目标选择结果之间的互斥.
    longsafe::SingleThreatTarget lgsf_threat_tgt_;
    longsafe::LgSfFunction lgsf_func_;

    active_safety::longsafe_2024::LgSafe2024Function lgsf_2024_;
    active_safety::longsafe_2024_newtsel::LgSafe2024Function lgsf_2024_new_;
    active_safety::aes_esa::AesEsaFunction aes_esa_;
    // MEB控制输出
    senseAD::tap::AsCmdLgSafe_T meb_cmd_;

    bool trust_meb_complete = false;
    bool use_new_tar_select_out = false;
   
    // 主动安全诊断禁止结果结构体
    struct DiagInhibitResult {
        uint8_t aeb_inhibit     = 0;
        uint8_t lka_inhibit     = 0;
        uint8_t esa_inhibit     = 0;
        uint8_t aes_inhibit     = 0;
        uint8_t elk_inhibit     = 0;
        uint8_t locp_inhibit    = 0;
        uint8_t fcta_b_inhibit  = 0;
        uint8_t rcta_b_inhibit  = 0;
        uint8_t dow_inhibit     = 0;
        uint8_t bsd_inhibit     = 0;
        uint8_t rcw_inhibit     = 0;
        uint8_t ldw_inhibit     = 0;
    };
    
    // 目标跳变检测状态
    struct TargetJumpState {
        int32_t last_target_id = -1;
        int32_t last_object_class = 0;
        float last_long_posn = 0.0F;
        float last_speed = 0.0F;
        uint64_t inhibit_end_time = 0;
    };
    TargetJumpState target_jump_state_;
    
    // SideFeature.
    rcw::RcwFunction rcw_func_;
    dow::DowFunction dow_func_;
    bsd::BsdFunction bsd_func_;
    cts::CtsFunction cts_func_;
    elk::ElkFunction elk_func_;
    lka::LkaFunction lka_func_;
    ldw::LdwFunction ldw_func_;
    DiagInhibitResult diag_inhibit_result_;
};

} // namespace active_safety
#endif // TAP_SDK_WRAPPER_ACTIVE_SAFETY_WRAPPER_H_
