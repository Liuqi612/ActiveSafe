#pragma once
#include "common/enum_type.h"
#include "cts_cals.h"
#include "cts_obs.h"
#include "interface/active_safety_types.h"
#include "math/signalprocess/feature_freezing_block/feature_freezing_block.h"
#include "math/signalprocess/off_delay_block/off_delay_block.h"
#include "math/signalprocess/signal_release_block/signal_release_block.h"
#include "math/statemachine/modemanager.hpp"

#include <array>

namespace active_safety {
namespace cts {
using math::FeatureFreezingBlock;
using math::ModeCondition;
using math::ModeConditionContext;
using math::ModeManager;
using math::ModeStateCondition;
using math::OffDelayBlock;
using math::SignalReleaseBlock;

struct WarnInfo {
    int cur_level = 0;
    int warn_level = 0;
    int max_level = 0;
    int highest_critical_obs_idx = -1;
    int hold_cnt = 0;
    int last_level = 0;
    int32_t obs_fusId = 0;
    int32_t obs_index = 0;
};
struct CtsOut {
    AsTargetInfo_T left_tgt;
    AsTargetInfo_T right_tgt;
    OnOffStatus sound;
    OnOffStatus left_warn;
    OnOffStatus right_warn;
    OnOffStatus brake_req;
    OnOffStatus brake_req_valid;
    float brake_dec_req;
    CtbCollisionDir collision_dir;
    CtaWorkingStatus working_status;
    CtsState brake_state;
    CtsState warn_state;
    // 0:Default 1:灯光+声音 2: 关闭 3: 灯光
    uint32_t switch_req;
};

class CtsFunction {
  public:
    CtsFunction();
    ~CtsFunction();
    void Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list);

    CtsOut front;
    CtsOut rear;

    CtsCal cts_cal_;

    std::array<ThresData, CTS_MAX_LEVEL> rcts_thres_;
    std::array<ThresData, CTS_MAX_LEVEL> fcts_thres_;

    bool f_fcta_ttc_execution_state = false;

    std::array<WarnInfo, CTS_MAX_SIDE> fcts_info_;
    std::array<WarnInfo, CTS_MAX_SIDE> rcts_info_;

    math::Polygon cta_zone;

    // Control/Cooldown state
    struct SideControl {
        SignalReleaseBlock release;
        FeatureFreezingBlock freezing;
    };

    void CheckMotion(CtsObsData &obs_data);
    void CheckTurning(CtsObsData &obs_data);
    void CheckApproachSide(CtsObsData &obs_data);
    void CheckCommonInhibit(const AsVseOut &vse_out);
    bool ValidObs(const CtsObsData &obs_data, const std::array<WarnInfo, CTS_MAX_SIDE> &warn_info, ObsAttribute &obs_attr);
    void CheckCTA(const AsVseOut &vse_out, const CtsObsData &obs_data, const std::array<ThresData, CTS_MAX_LEVEL> &thres, ObsAttribute &obs_attr,
                  std::array<WarnInfo, CTS_MAX_SIDE> &warn_info);
    void CalculateTargetCornersPoint(CtsObsData &obs_data);
    void CalculateTargetReferencePoint(const CtsObsData &obs_data, ObsAttribute &obs_attr);
    void CalculateRelativeVelocity(const AsVseOut &vse_out, CtsObsData &obs_data);
    void CalculateTimeToConflict(const VehicleConfig &veh_config, const CtsObsData &obs_data, ObsAttribute &obs_attr);
    void CalculateIntersecPoint(const math::Point2D &relative_velocity, ObsAttribute &obs_attr);
    void CalculateRadialDistance(const VehicleConfig &veh_config, ObsAttribute &obs_attr);
    void CheckObsInZone(const AsVseOut &vse_out, const CtsObsData &obs_data, ObsAttribute &obs_attr);
    bool IsObjectBehindTrailingEdge(const AsVseOut &vse_out, const CtsObsData &obs_data, const ObsAttribute &obs_attr);
    void CheckAllLevel(const AsVseOut &vse_out, const CtsObsData &obs_data, const std::array<ThresData, CTS_MAX_LEVEL> &thres, ObsAttribute &obs_attr,
                       std::array<WarnInfo, CTS_MAX_SIDE> &warn_info);
    void SetThresData(const AsVseOut &vse_out);

    void ResetObsData(ObsAttribute &obs_attr);

    void ProcessThreatLevel(std::array<WarnInfo, CTS_MAX_SIDE> &warn_infos, CtsDirection dir);
    void CtsDecision(const AsVseOut &vse_out, const GlobalConfig &config);
    void FCTAStateMachine(const AsVseOut &vse_out, const GlobalConfig &config);
    void FCTBStateMachine(const AsVseOut &vse_out, const GlobalConfig &config);
    void RCTAStateMachine(const AsVseOut &vse_out, const GlobalConfig &config);
    void RCTBStateMachine(const AsVseOut &vse_out, const GlobalConfig &config);
    void FillOutput(const AsVseOut &vse_out, const GlobalConfig &config, const std::array<WarnInfo, CTS_MAX_SIDE> &warn_infos, CtsOut &out,
                    CtsDirection dir);
    void FillTargetInfo(const CtsObsData &obs_data, int side, AsTargetInfo_T &tgt_info);

    bool f_common_inhibit = false;
    math::OffDelayBlock common_inhibit_offdly_;

    math::ModeManager fcta_mode_;
    math::ModeConditionContext fcta_mode_context_;
    math::ModeStateCondition fcta_mode_cond_;
    SignalReleaseBlock fcta_release;
    FeatureFreezingBlock fcta_freezing;

    math::ModeManager fctb_mode_;
    math::ModeConditionContext fctb_mode_context_;
    math::ModeStateCondition fctb_mode_cond_;
    SignalReleaseBlock fctb_release;
    FeatureFreezingBlock fctb_freezing;
    OffDelayBlock fctb_low_speed_delay; // 用于延迟退出激活状态（车速 < 0.01 后 2 秒）

    math::ModeManager rcta_mode_;
    math::ModeConditionContext rcta_mode_context_;
    math::ModeStateCondition rcta_mode_cond_;
    SignalReleaseBlock rcta_release;
    FeatureFreezingBlock rcta_freezing;

    math::ModeManager rctb_mode_;
    math::ModeConditionContext rctb_mode_context_;
    math::ModeStateCondition rctb_mode_cond_;
    SignalReleaseBlock rctb_release;
    FeatureFreezingBlock rctb_freezing;
    OffDelayBlock rctb_low_speed_delay; // 用于延迟退出激活状态（车速 < 0.01 后 2 秒）

    std::array<CtsObsData, kMaxNormalObject> obs_data_;
};

} // namespace cts
} // namespace active_safety
