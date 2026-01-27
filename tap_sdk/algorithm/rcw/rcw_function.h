#pragma once
#include "common/enum_type.h"
#include "common/global_config.h"
#include "interface/active_safety_types.h"
#include "interface/active_safety_vse.h"
#include "math/signalprocess/feature_freezing_block/feature_freezing_block.h"
#include "math/signalprocess/signal_release_block/signal_release_block.h"
#include "math/statemachine/modemanager.hpp"
#include "rcw_cals.h"
#include "rcw_obs.h"

#include <array>

namespace active_safety {
namespace rcw {

using math::FeatureFreezingBlock;
using math::ModeCondition;
using math::ModeConditionContext;
using math::ModeManager;
using math::ModeStateCondition;
using math::SignalReleaseBlock;

struct RcwOutput {
    AsTargetInfo_T tgt_rcw;
    // 0:reserve,1:On,2:Off,3:reserve
    uint32_t    switch_req;
    OnOffStatus rcw_collision_warn;
    RcwState    state;
};

enum RcwWarnState { WARNING_OFF, WARNING_ON, WARNING_SUPPRESS, WARNING_HOLD };

class RcwFunction {
  public:
    RcwFunction();
    ~RcwFunction();

    void Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list);

    void Init();
    bool IsValidObject(const AsVseOut &vse_out, RcwObsData &obs_data);
    void Is_Object_Permanent_Within_Ego_Lane(const AsVseOut &vse_out, RcwObsData &obs_data);
    void Calculate_TTC(const AsVseOut &vse_out, RcwObsData &obs_data);
    void Filter_Object_Heading(const AsVseOut &vse_out, RcwObsData &obs_data);
    bool UpdateHighestCritObject(RcwObsData &obs_data);
    void CrashProbSteerBrake(const AsVseOut &vse_out, RcwObsData &obs_data);

    float GetBrakeAccToAvoidRearEndColl(const float vcs_long_acc, float lon_rel_vel_obj, float lon_pos_bumper_obj);
    float GetSteerAccToAvoidRearEndColl(const AsVseOut &vse_out, RcwObsData &obs_data, float lon_rel_vel_obj, const float lat_rel_vel_obj,
                                        float lon_pos_bumper_obj);

    void Calculate_WarnLevel();
    void StateMachine(const GlobalConfig &config, const AsVseOut &vse_out);
    void FillTargetInfo(const RcwObsData &obs_data, AsTargetInfo_T &tgt_info);
    bool Handle_Warnlevel_Debounce_Counter(const bool should_warning_be_active, const RcwWarnLevel &warn_level,
                                           RcwWarnDebounceCounter &debounce_counter);

    bool Handle_Warn_State_Off(RcwWarnDebounceCounter &debounce_counter);

    bool Is_Max_Warn_Duration_Exceeded(const RcwWarnLevel &warn_level, RcwWarnDebounceCounter &debounce_counter);

    bool Handle_Warn_State_On(const RcwWarnLevel &warn_level, RcwWarnDebounceCounter &debounce_counter);

    bool Handle_Warn_State_Hold(const RcwWarnLevel &warn_level, RcwWarnDebounceCounter &debounce_counter);

    bool Handle_Warn_State_Suppress(const RcwWarnLevel &warn_level, RcwWarnDebounceCounter &debounce_counter);

    RcwWarnState Identify_Current_Warning_State(const bool should_warning_be_active, const bool was_active_last_cycle);

    RcwCal rcw_cal_;

    std::array<RcwObsData, kMaxNormalObject> obs_data_;

    RcwOutput            rcw_out_;
    ModeManager          rcw_mode_;
    ModeConditionContext rcw_mode_context_;
    ModeStateCondition   rcw_mode_cond_;

    // 报警时间限制和冷却时间模块
    SignalReleaseBlock   rcw_release_;
    FeatureFreezingBlock rcw_freezing_;

    int32_t                last_cycle_obj_id;
    int                    highest_critical_index = -1;
    bool                   is_warnlevel_active_[2];
    RcwWarnDebounceCounter debounce_counter_[2];

    void ResetPersistant(RcwObsData &obs_data);
};

} // namespace rcw
} // namespace active_safety
