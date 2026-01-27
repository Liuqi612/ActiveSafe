#pragma once
#include "bsd_cals.h"
#include "bsd_obs.h"
#include "common/enum_type.h"
#include "interface/active_safety_types.h"
#include "math/statemachine/modemanager.hpp"

#include <array>

namespace active_safety {
namespace bsd {

using math::ModeCondition;
using math::ModeConditionContext;
using math::ModeManager;
using math::ModeStateCondition;

struct BsdFuncData {
    bool f_prev_cvw_active = false;
    bool f_prev_bsw_active = false;
    int32_t prev_cvw_alert_obs_id = 0;
    int32_t prev_bsw_alert_obs_id = 0;
    int bsw_hold_counter = 0;
    int cvw_hold_counter = 0;
};
struct BsdFunction {
  public:
    BsdFunction();
    ~BsdFunction();
    void Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list);

    void CheckMotion(BsdObsData &obs_data);
    void GetObjClass(BsdObsData &obs_data);
    bool IsObjectRelevant(const BsdObsData &obs_data);
    bool IsValidBSWObj(const BsdObsData &obs_data);
    bool IsValidCVWObj(const BsdObsData &obs_data);

    void FilterCurviDataAndCheckSide(BsdObsData &obs_data);
    void CalcObsPolygon(BsdObsData &obs_data);
    void CalcValidZone(const VehicleConfig &config, BsdObsData &obs_data);
    void UpdateCriticalObsInBswZone(const AsVseOut &vse_out, BsdObsData &obs_data);
    void UpdateCriticalObsInCvwZone(const AsVseOut &vse_out, BsdObsData &obs_data);
    void UpdateFallbackState(BsdObsData &obs_data);
    void CalcTTc(const VehicleConfig &veh_config, BsdObsData &obs_data);
    void WarnJudgement();
    void StateMachine(const GlobalConfig &config, const AsVseOut &vse_out);
    void FillTargetInfo(const BsdObsData &obs_data, AsTargetInfo_T &tgt_info);
    // Output.
    struct BsdOutput {
        AsTargetInfo_T left_tgt_bsd;
        AsTargetInfo_T right_tgt_bsd;
        AsTargetInfo_T left_tgt_lca;
        AsTargetInfo_T right_tgt_lca;
        // 0:Default 1:灯光+声音 2: 关闭 3: 灯光
        uint32_t switch_req;
        // 0：Inactive,1：Warning_level_1,2：Warning_Level_2,3：Invalid
        uint32_t bsd_warn_left;
        // 0：Inactive,1：Warning_level_1,2：Warning_Level_2,3：Invalid
        uint32_t bsd_warn_right;
        OnOffStatus bsc_sound;
        // 0：Inactive,1：Warning_level_1,2：Warning_Level_2,3：Invalid
        uint32_t lca_warn_left;
        // 0：Inactive,1：Warning_level_1,2：Warning_Level_2,3：Invalid
        uint32_t lca_warn_right;
        BsdState state;
    };

    BsdOutput bsd_out_;
    int bsd_hold_active_time_;
    bool bsd_active_;
    bool lcw_active_;
    bool host_speed_enable;
    ModeManager lcda_mode_;
    ModeConditionContext lcda_mode_context_;
    ModeStateCondition lcda_mode_cond_;
    // Decide function result.
    std::array<WarnLevel, 2> bsw_level_;
    std::array<int32_t, 2> bsw_obs_id_;
    std::array<WarnLevel, 2> cvw_level_;
    std::array<int32_t, 2> cvw_obs_id_;

    BsdCal bsd_cal_;

    std::array<BsdObsData, kMaxNormalObject> obs_data_;

    // Variable to indicate threat after obs iters.
    std::array<bool, 2> f_bsw_alert_active_ = {false, false};
    std::array<int32_t, 2> bsw_alert_fusId_ = {-1, -1};

    std::array<float, 2> closest_cvw_obs_dist_ = {-1000.0f, -1000.0f};
    std::array<bool, 2> f_cvw_alert_active_ = {false, false};
    std::array<int32_t, 2> cvw_alert_fusId_ = {-1, -1};

    // record data.
    BsdFuncData prev_data_[2];
};
} // namespace bsd
} // namespace active_safety