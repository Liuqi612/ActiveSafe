#ifndef TAP_SDK_ALGORITHM_LONGSAFE_DECISION_LGSF_FUNCTION_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_DECISION_LGSF_FUNCTION_H_
#include "algorithm/longsafe/decision/common_inhibit.h"
#include "algorithm/longsafe/decision/threat_assessor.h"
#include "algorithm/longsafe/ego/curvature_path.h"
#include "algorithm/longsafe/ego/driver_evaluator.h"
#include "algorithm/longsafe/longsafe_cals.h"
#include "algorithm/vse/vehicle_state_estimed.h"
#include "interface/active_safety_types.h"
#include "math/signalprocess/feature_freezing_block/feature_freezing_block.h"
#include "math/signalprocess/on_delay_block/on_delay_block.h"

namespace active_safety {
namespace longsafe {

using math::OffDelayBlock;
using math::OnDelayBlock;

class LgSfFunction {
  public:
    LgSfFunction();
    ~LgSfFunction();

    void Update(const AsVseOut &vse_out, const LongSafeObject &obs, const GlobalConfig &config, const AsCurvaturePath &ego_path);
    void UpdateCmbbThreat();
    void EvalAebDeactive(const AsVseOut &vse_out, const LongSafeObject &obs);
    void CalcCloseLoopDecel(const AsVseOut &vse_out, const LongSafeObject &obs);
    void BrakeDecelArb();
    void InhibitEvaluator(const AsVseOut &vse_out);
    void FaultEvaluator(const AsVseOut &vse_out);
    void AebStateMachine(bool aeb_switch_on, float host_speed);
    void FcwStateMachine(bool fcw_switch_on);
    void OutPutMapping(const GlobalConfig &config);
    void CheckEbaBrkActive(const AsVseOut &vse_out);

    struct LongSafeOutput {
        AsTargetInfo_T   tgt;
        float            aeb_tar_dec;
        uint32_t         hold_type;
        OnOffStatus      aeb_req;
        OnOffStatus      awb_req;
        OnOffStatus      prefill_req;
        OnOffStatus      aba_req;
        OnOffStatus      belt_req;
        AebStatus        aeb_status;
        FcwStatus        fcw_status;
        WarnLevel        warn_level;
        TargetObjColor   tgt_color;
        FcwWarnDist      warn_dist;
        FcwAebTextInfo   text_info;
        DrivingSoundWarn sound_warn;
        // 0:No Level,1:Level_1,2:Level_2,3:Level_3
        uint8_t aba_level;
        // 0: NoRequest, 1:Level_1; 2:Level_2; 3:Level_3
        uint8_t awb_level;
        uint8_t aeb_req_valid;
        // Bit0: 是否为影子模式
        // Bit1: AEB
        // Bit2: EBA
        // Bit3: FCW
        // Bit4: DW
        // Bit5: AWB
        uint8_t shadow_mode;
    };

    LongSafeOutput lgsf_out_;

    LongSafeObject  prev_obs;
    ThreatAssessor  threat_assessor_;
    CommonInhibit   common_inhibit_;
    DriverEvaluator drvr_est_;
    // deactive info.
    bool brake_deactive  = false;
    bool aeb_system_ovrd = false;

    OnDelayBlock station_veh;
    OnDelayBlock no_brk_req;
    OnDelayBlock high_ttc;
    OnDelayBlock dly_low_spd;

    float delay_deactive_state_cnt;

    // Inhibit
    // aeb inhibit info.
    uint32_t inhibit_mask;

    bool aeb_inhibit = false;
    bool fcw_inhibit = false;

    OnDelayBlock  inhibit_acc_pdl_on;
    OffDelayBlock inhibit_acc_pdl_off;

    OnDelayBlock  inhibit_steer_wheel_angle_on;
    OffDelayBlock inhibit_steer_wheel_angle_off;

    OnDelayBlock  inhibit_host_speed_on;
    OffDelayBlock inhibit_host_speed_off;

    OnDelayBlock  inhibit_yaw_rate_on;
    OffDelayBlock inhibit_yaw_rate_off;

    OnDelayBlock  inhibit_door_open_on;
    OffDelayBlock inhibit_door_open_off;

    OnDelayBlock  inhibit_drv_belt_fasten_on;
    OffDelayBlock inhibit_drv_belt_fasten_off;

    OnDelayBlock  inhibit_vdc_atv_on;
    OffDelayBlock inhibit_vdc_atv_off;

    OnDelayBlock  inhibit_tcs_atv_on;
    OffDelayBlock inhibit_tcs_atv_off;

    OnDelayBlock  inhibit_hdc_atv_on;
    OffDelayBlock inhibit_hdc_atv_off;

    OnDelayBlock  inhibit_tcs_off_on;
    OffDelayBlock inhibit_tcs_off_off;

    OnDelayBlock  inhibit_gear_on;
    OffDelayBlock inhibit_gear_off;
    // fault info.
    bool aeb_fault = false;
    bool fcw_fault = false;

    // active info.
    bool prefill_atv  = false;
    bool eba_atv      = false;
    bool aeb_atv      = false;
    bool drv_brk_atv_ = false;

    math::OffDelayBlock brkpdlrate_offdly_;
    //保压请求
    bool hold_req = false;
    //安全带请求
    bool belt_req = false;

    float aeb_req_dec         = 0.0F;
    float close_loop_dec      = 0.0F;
    float close_loop_dec_filt = 0.0F;

    enum CmbbThreat { No_Threat = 0, Brake_Preliminary = 1, Brake_Confirmed = 2 };

    float brake_threat_cnt_ = 0.0F;

    math::FeatureFreezingBlock aeb_atv_freez_;

    AebStatus       aeb_state_;
    FcwStatus       fcw_state_;
    CmbbThreat      cmbb_threat_;
    CmbbThreat      cmbb_threat_n_1_;
    CmbbFunctionCal cmbb_cal_;
};

} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_DECISION_LGSF_FUNCTION_H_
