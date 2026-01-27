#pragma once
#include "common/enum_type.h"
#include "common/global_config.h"
#include "dow_cals.h"
#include "dow_obs.h"
#include "interface/active_safety_types.h"
#include "interface/active_safety_vse.h"
#include "math/statemachine/modemanager.hpp"
#include "math/signalprocess/feature_freezing_block/feature_freezing_block.h"

#include <array>

namespace active_safety {
namespace dow {

using math::ModeCondition;
using math::ModeConditionContext;
using math::ModeManager;
using math::ModeStateCondition;
using math::FeatureFreezingBlock;

struct DowOutput {
    AsTargetInfo_T left_tgt;
    AsTargetInfo_T right_tgt;
    uint32_t       switch_req; // 0:Default 1:灯光+声音 2: 关闭 3: 灯光
    uint32_t       warn_left;  // 0:Inactive, 1:Level_1, 2:Level_2
    uint32_t       warn_right; // 0:Inactive, 1:Level_1, 2:Level_2
    DowState       state;
};

class DowFunction {
  public:
    DowFunction();
    ~DowFunction();

    void Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list);
    void InitZone();
    void FindReferencePoint(DowObsData &obs_data, float host_dist_to_front);

    void CheckMotion(DowObsData &obs_data);
    bool IsObjectValid(DowObsData &obs_data);
    bool IsObjectRelevant(const AsVseOut &vse_out, DowObsData &obs_data);

    void UpdateCriticalObs(const AsVseOut &vse_out, DowObsData &obs_data);
    void FillTargetInfo(const DowObsData &obs_data, AsTargetInfo_T &tgt_info);
    void ResetObjectPersistent(DowObsData &obs_data);
    void CheckPointInZone(const math::Point2D &pt, DowObsData &obs_data);
    void FindThreatWarn();
    void StateMachine(const GlobalConfig &config, const AsVseOut &vse_out);

    DowOutput dow_out_;

    math::Point2D CalcObjectCorner(float center_x, float center_y, float heading, float local_x, float local_y);

    DowCal dow_cal_;

    // set zone.
    math::Polygon rear_left_zone;
    math::Polygon rear_right_zone;
    math::Polygon front_left_zone;
    math::Polygon front_right_zone;

    std::array<DowObsData, kMaxNormalObject> obs_data_;

    ModeManager          dow_mode_;
    ModeConditionContext dow_mode_context_;
    ModeStateCondition   dow_mode_cond_;
    
};

} // namespace dow
} // namespace active_safety
