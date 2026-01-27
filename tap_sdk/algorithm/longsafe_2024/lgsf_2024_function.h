#pragma once
extern "C" {
#include "algorithm/longsafe_2024/aeb/LongSafe_SWC_ert_rtw/LongSafe_SWC.h"
}

// Undefine Simulink-generated macros that conflict with SDK enums
#ifdef Aeb_Off
#undef Aeb_Off
#endif
#ifdef Aeb_Fault
#undef Aeb_Fault
#endif
#ifdef Aeb_Passive
#undef Aeb_Passive
#endif
#ifdef Aeb_Standby
#undef Aeb_Standby
#endif
#ifdef Prefill_Active
#undef Prefill_Active
#endif
#ifdef Aeb_Active
#undef Aeb_Active
#endif
#ifdef Eba_Active
#undef Eba_Active
#endif

#ifdef Fcw_Off
#undef Fcw_Off
#endif
#ifdef Fcw_Fault
#undef Fcw_Fault
#endif
#ifdef Fcw_Passive
#undef Fcw_Passive
#endif
#ifdef Fcw_Standby
#undef Fcw_Standby
#endif
#ifdef Fcw_FirstLevel
#undef Fcw_FirstLevel
#endif
#ifdef Fcw_SecondLevel
#undef Fcw_SecondLevel
#endif
#ifdef Fcw_ThirdLevel
#undef Fcw_ThirdLevel
#endif

#ifdef Awb_Off
#undef Awb_Off
#endif
#ifdef Awb_Fault
#undef Awb_Fault
#endif
#ifdef Awb_Passive
#undef Awb_Passive
#endif
#ifdef Awb_Standby
#undef Awb_Standby
#endif
#ifdef Awb_Active
#undef Awb_Active
#endif

#include "algorithm/longsafe_2024/algo_interface/active_safety_command.h"
#include "algorithm/longsafe_2024/algo_interface/active_safety_control.h"
#include "algorithm/longsafe_2024/algo_interface/active_safety_coreout.h"
#include "algorithm/longsafe_2024/algo_interface/active_safety_display.h"
#include "algorithm/longsafe_2024/algo_interface/active_safety_vse.h"
#include "algorithm/longsafe_2024/param/as_param.h"
#include "algorithm/longsafe_2024/select/threat_assessment/long_safe.h"
#include "common/global_config.h"

namespace active_safety {
namespace longsafe_2024 {

class LgSafe2024Function {
  public:
    LgSafe2024Function();
    ~LgSafe2024Function();

    void Init();
    void Update(const active_safety::AsVseOut &vse_out, const active_safety::AsObstacleList &obs_list, const active_safety::LanesInfo &road_info,
                const senseAD::tap::AsParamConfig_T &long_safe_param);

    // Outputs
    const senseAD::tap::AsCmdLgSafe_T &    GetCmd() const { return cmd_output_; }
    const senseAD::tap::AsDisplayLgSafe_T &GetDisplay() const { return display_output_; }
    const senseAD::tap::AsLongSafeOut &    GetSelectOut() const { return select_output_; }
    const senseAD::tap::LgSf_Ltap_T &      GetLtapOut() const { return ltap_output_; }
    const senseAD::tap::LgSafe_T &      GetLgSf() const { return simulink_y_lg_safe_; }

  private:
    void MapToSimulinkInput(const senseAD::tap::AsVseOut &vse_out, const senseAD::tap::AsLongSafeOut &select_out,
                            const senseAD::tap::AsParamConfig_T &long_safe_param);

    void MapFromSimulinkOutput(const senseAD::tap::LgSafe_T &lg_safe_internal, const senseAD::tap::AsCmdLgSafe_T &cmd_internal,
                               const senseAD::tap::AsDisplayLgSafe_T &display_internal);

    void MapVseInput(const active_safety::AsVseOut &vse_in, senseAD::tap::AsVseOut &vse_out);
    void MapRoadInfo(const active_safety::LanesInfo &road_info_in, senseAD::tap::AS_LaneMarkerInfo_T &lane_info_out);

  private:
    void MapLaneMarker(const active_safety::LaneMarker_t &in, senseAD::tap::LaneMarker_t &out);
    void MapRoadEdge(const active_safety::RoadEdge_t &in, senseAD::tap::RoadEdge_t &out);

    senseAD::tap::AsLongSafe select_module_;

    // Simulink Internal States and Structures
    RT_MODEL_LongSafe_SWC_T *       rtm_;
    senseAD::tap::AsVseOut          simulink_u_vse_;
    senseAD::tap::AsCoreOut_T       simulink_u_core_out_;
    senseAD::tap::AsParamConfig_T   simulink_u_param_config_;
    senseAD::tap::LgSafe_T          simulink_y_lg_safe_;
    senseAD::tap::AsCmdLgSafe_T     simulink_y_cmd_lg_safe_;
    senseAD::tap::AsDisplayLgSafe_T simulink_y_display_lg_safe_;

    senseAD::tap::AsSocietyScene society_scene_;
    // Final SDK Outputs
    senseAD::tap::AsLongSafeOut     select_output_;
    senseAD::tap::AsCmdLgSafe_T     cmd_output_;
    senseAD::tap::AsDisplayLgSafe_T display_output_;
    senseAD::tap::LgSf_Ltap_T       ltap_output_;
};

} // namespace longsafe_2024
} // namespace active_safety
