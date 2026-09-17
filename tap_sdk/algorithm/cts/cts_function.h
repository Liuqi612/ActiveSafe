#ifndef TAP_SDK_ALGORITHM_CTS_CTS_FUNCTION_H_
#define TAP_SDK_ALGORITHM_CTS_CTS_FUNCTION_H_
#include "common/basic_types.h" 
#include "common/enum_type.h"
#include "cts_cals.h"
#include "cts_obs.h"
#include "interface/active_safety_types.h"
#include "math/signalprocess/feature_freezing_block/feature_freezing_block.h"
#include "math/signalprocess/off_delay_block/off_delay_block.h"
#include "math/signalprocess/on_delay_block/on_delay_block.h"
#include "math/signalprocess/signal_release_block/signal_release_block.h"
#include "math/statemachine/modemanager.hpp"
#include "math/utils/util_math.h"

#include <array>
#include <cstdint>

namespace active_safety {
namespace cts {
using math::FeatureFreezingBlock;
using math::ModeCondition;
using math::ModeConditionContext;
using math::ModeManager;
using math::ModeStateCondition;
using math::OffDelayBlock;
using math::OnDelayBlock;
using math::SignalReleaseBlock;

enum class CtsSwitch : uint8_t { DEFAULT = 0, OFF = 1, ONLY_WARING = 2, WARING_BRAKE = 3 };

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

// 单个子功能(FCTA/FCTB/RCTA/RCTB)状态机每帧计算出的关键中间条件快照。
// 由各状态机函数在运行时填充，供 cts_debug_logger 在回灌时打印，保证打印值与实际决策完全一致。
struct CtsFeatureDebug {
    // 四个基础状态位（直接决定 OFF/FAULT/INHIBIT/STANDBY/ACTIVE 走向）
    bool state_off = false;      // 软开关关闭
    bool state_fault = false;    // 诊断故障
    bool state_inhibit = false;  // 被抑制
    bool state_active = false;   // 满足激活

    // 进入/退出各状态的直接判据
    bool standby_entry = false;  // 车速+档位+AEB可用 满足进入 standby
    bool inhibit_cond = false;   // 车速/档位/AEB 触发抑制
    bool raw_trigger = false;    // 目标威胁等级达到激活门限(未经保持/释放处理)
    bool max_time_reached = false; // 达到最长报警时间被强制释放
    bool freezing = false;       // 处于冻结期
    bool min_hold_active = false;      // (CTA)最小保持窗口内
    bool keep_active_low_speed = false; // (CTB)低速制动保持

    // 参与判断的原始量(便于定位为何未进入 standby/active)
    float speed = 0.0F;
    uint8_t gear = 0;
    uint8_t sw = 0;
    int level_side0 = 0;
    int level_side1 = 0;
};

// 单个告警等级(k=0..CTS_MAX_LEVEL-1)的逐级判据快照，对应被删掉的 CheckAllLevel 内 cout。
struct CtsLevelDebug {
    bool in_zone = false;
    float lat_ttc = 0.0F;
    float ttc_thres = 0.0F;
    float lgt_ttc = 0.0F;
    bool ttc_check = false;
    float radial_distance = 0.0F;
    float rad_dist_thres = 0.0F;
    bool radial_dist_check = false;
    float intersect_x = 0.0F;
    float inter_min = 0.0F;   // 已叠加 k_dist_to_rear_axle
    float inter_max = 0.0F;   // 已叠加 k_dist_to_rear_axle + 各类收缩/修正
    bool inter_x_check = false;
    int counter_val = 0;
    int confirm_thres = 0;
    bool level_passed = false; // counter_val > confirm_thres
};

// 一个方向(FRONT/REAR)一侧(L/R)的关键目标(highest_critical_obs_idx)逐级明细。
// 对应被删掉的 CheckAllLevel / ProcessThreatLevel 内 per-target cout。
struct CtsTargetDebug {
    bool valid = false;             // 本帧该侧是否有被记录的关键目标
    int32_t fus_trkID = 0;
    int track_id = 0;
    float heading = 0.0F;
    // 目标在自车坐标系下的位置(m)和速度(m/s)
    float lat_posn = 0.0F;
    float long_posn = 0.0F;
    float lat_vel = 0.0F;
    float long_vel = 0.0F;
    CtsLevelDebug levels[CTS_MAX_LEVEL];
    // ProcessThreatLevel 保持/迟滞相关
    int max_level = 0;
    int last_level = 0;
    int cur_level = 0;
    int hold_cnt = 0;
    int highest_critical_obs_idx = -1;
};

// ValidObs rejection reasons. A target can fail more than one check in a frame;
// keeping a bit mask lets the debug output show all of them instead of only the
// first failed condition.
enum CtsInvalidTargetReason : uint32_t {
    CTS_INVALID_NO_TRACK_ID = 1U << 0,
    CTS_INVALID_LOW_CONFIDENCE = 1U << 1,
    CTS_INVALID_STATIONARY = 1U << 2,
    CTS_INVALID_AGE = 1U << 3,
    CTS_INVALID_SPEED = 1U << 4,
    CTS_INVALID_HEADING_RANGE = 1U << 5,
    CTS_INVALID_LATERAL_APPROACH_SPEED = 1U << 6,
    CTS_INVALID_APPROACH_SIDE = 1U << 7,
    CTS_INVALID_HEADING_FILTER = 1U << 8,
    CTS_INVALID_OVERLAP = 1U << 9,
    CTS_INVALID_TURNING = 1U << 10,
    CTS_INVALID_VISIBLE_DIAGONAL = 1U << 11,
    CTS_INVALID_HEADING_DEVIATION = 1U << 12,
    CTS_INVALID_PATH_CONFLICT = 1U << 13,
};

// One target/direction validity report. Reports are kept for every populated
// target so invalid targets are visible even when they never become critical.
struct CtsInvalidTargetDebug {
    bool evaluated = false;
    int32_t fus_trkID = 0;
    int track_id = 0;
    uint8_t approach_side = CTA_APPROACH_UNDEFINED;
    float age = 0.0F;
    float speed = 0.0F;
    float heading = 0.0F;
    float lat_approach_speed = 0.0F;
    float angle_diff = 0.0F;
    uint32_t reasons = 0U;
    // Target position and component velocity in the ego vehicle coordinate
    // system, retained for diagnosing rejected targets.
    float lat_posn = 0.0F;
    float long_posn = 0.0F;
    float lat_vel = 0.0F;
    float long_vel = 0.0F;
};

struct CtsDebugSnapshot {
    CtsFeatureDebug fcta;
    CtsFeatureDebug fctb;
    CtsFeatureDebug rcta;
    CtsFeatureDebug rctb;
    bool common_inhibit = false;         // 公共抑制(转向/踏板/曲率)
    bool drv_continues_steer = false;    // 驾驶员持续转向
    int  drv_continues_str_dir = 0;      // 0:None 1:Left 2:Right
    bool drv_increase_steer = false;     // 驾驶员增大转向
    int  drv_increase_str_dir = 0;       // 0:None 1:Left 2:Right
    bool veh_decel = false;              // 自车持续减速
    bool drv_want_brake = false;         // 驾驶员低速制动意图

    // 每侧关键目标逐级明细：[dir][side]，dir 0:FRONT 1:REAR，side 0:Left 1:Right
    CtsTargetDebug target[2][CTS_MAX_SIDE];

    // 每帧所有已评估目标的无效原因：[dir][target index]。
    std::array<std::array<CtsInvalidTargetDebug, kMaxNormalObject>, 2> invalid_target;
};

class CtsFunction {
  public:
    CtsFunction();

    ~CtsFunction();

    void Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list);

    void CheckMotion(CtsObsData &obs_data);
    void CheckCrossDecel(CtsObsData &obs_data);
    void CheckApproachSide(CtsObsData &obs_data);
    bool CalculateObsDuringObsToHost(const AsVseOut &vse_out, CtsObsData &obs_data);
    void CheckCommonInhibit(const AsVseOut &vse_out);
    void CheckDrvBehavior(const AsVseOut &vse_out);
    bool ValidObs(const AsVseOut &vse_out, const std::array<WarnInfo, CTS_MAX_SIDE> &warn_info, CtsObsData &obs_data, ObsAttribute &obs_attr);
    void CheckCTA(const AsVseOut &vse_out, const std::array<ThresData, CTS_MAX_LEVEL> &thres, CtsObsData &obs_data, ObsAttribute &obs_attr,
                  std::array<WarnInfo, CTS_MAX_SIDE> &warn_info, CtsDirection dir);

    void CalculateTargetCornersPoint(CtsObsData &obs_data);
    void CalculateTargetReferencePoint(const CtsObsData &obs_data, ObsAttribute &obs_attr);
    void CalculateRelativeVelocity(const AsVseOut &vse_out, CtsObsData &obs_data);
    void CalculateTimeToConflict(const VehicleConfig &veh_config, const CtsObsData &obs_data, ObsAttribute &obs_attr);
    void CalculateIntersecPoint(const math::Point2D &relative_velocity, ObsAttribute &obs_attr);
    void CalculateRadialDistance(const VehicleConfig &veh_config, ObsAttribute &obs_attr);
    void CheckObsInZone(const AsVseOut &vse_out, const CtsObsData &obs_data, ObsAttribute &obs_attr);
    bool IsObjectBehindTrailingEdge(const AsVseOut &vse_out, const CtsObsData &obs_data, const ObsAttribute &obs_attr);
    void CheckAllLevel(const AsVseOut &vse_out, const std::array<ThresData, CTS_MAX_LEVEL> &thres, const CtsObsData &obs_data, ObsAttribute &obs_attr,
                       std::array<WarnInfo, CTS_MAX_SIDE> &warn_info, CtsDirection dir);

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

    // 回灌调试：把本帧影响 CTS 输出的所有关键条件打印到 stdout(可重定向到文件)。
    // 仅在 vse_out.config 无关，受 config 中的 CTA/CTB 使能与 shadowmode 影响，故一并传入。
    void DumpDebugFrame(const AsVseOut &vse_out, const GlobalConfig &config);

    CtsOut m_front;
    CtsOut m_rear;

    CtsCal m_cts_cal;

    // 回灌调试用：每帧记录影响 CTS 输出的关键中间条件，由 DumpDebugFrame 打印
    CtsDebugSnapshot m_debug;

    std::array<ThresData, CTS_MAX_LEVEL> m_rcts_thres;
    std::array<ThresData, CTS_MAX_LEVEL> m_fcts_thres;

    bool m_fcta_ttc_execution_state = false;

    std::array<WarnInfo, CTS_MAX_SIDE> m_fcts_info;
    std::array<WarnInfo, CTS_MAX_SIDE> m_rcts_info;

    math::Polygon m_cta_zone;

    // Control/Cooldown state
    SignalReleaseBlock m_release;
    FeatureFreezingBlock m_freezing;

    // Drv behavior.
    OffDelayBlock m_common_inhibit_offdly;

    enum DriverSteerDir { None, Left, Right };
    OnDelayBlock m_drv_continues_steer_ondly;
    OffDelayBlock m_drv_continues_steer_offdly;
    DriverSteerDir m_drv_continues_str_dir;
    float m_drv_max_continues_str_ang;

    OnDelayBlock m_drv_increase_str_left_ondly;
    OffDelayBlock m_drv_increase_str_left_offdly;
    OnDelayBlock m_drv_increase_str_right_ondly;
    OffDelayBlock m_drv_increase_str_right_offdly;
    DriverSteerDir m_drv_increase_str_dir;

    OnDelayBlock m_veh_decel_ondly;
    OffDelayBlock m_veh_decel_offdly;

    OnDelayBlock m_drv_wantbrake_ondly;
    OffDelayBlock m_drv_wantbrake_offdly;

    math::ModeManager m_fcta_mode;
    math::ModeConditionContext m_fcta_mode_context;
    math::ModeStateCondition m_fcta_mode_cond;
    SignalReleaseBlock m_fcta_release;
    FeatureFreezingBlock m_fcta_freezing;
    bool m_fcta_warn_min_hold_active = false;
    float m_fcta_warn_min_hold_elapsed_s = 0.0F;
    bool m_fcta_warn_hold_side_active[CTS_MAX_SIDE] = {false, false};

    math::ModeManager m_fctb_mode;
    math::ModeConditionContext m_fctb_mode_context;
    math::ModeStateCondition m_fctb_mode_cond;
    SignalReleaseBlock m_fctb_release;
    FeatureFreezingBlock m_fctb_freezing;
    bool m_fctb_low_speed_hold_active = false; // 低速制动保持状态
    float m_fctb_low_speed_hold_elapsed_s = 0.0F;

    math::ModeManager m_rcta_mode;
    math::ModeConditionContext m_rcta_mode_context;
    math::ModeStateCondition m_rcta_mode_cond;
    SignalReleaseBlock m_rcta_release;
    FeatureFreezingBlock m_rcta_freezing;
    bool m_rcta_warn_min_hold_active = false;
    float m_rcta_warn_min_hold_elapsed_s = 0.0F;
    bool m_rcta_warn_hold_side_active[CTS_MAX_SIDE] = {false, false};

    math::ModeManager m_rctb_mode;
    math::ModeConditionContext m_rctb_mode_context;
    math::ModeStateCondition m_rctb_mode_cond;
    SignalReleaseBlock m_rctb_release;
    FeatureFreezingBlock m_rctb_freezing;
    bool m_rctb_low_speed_hold_active = false; // 低速制动保持状态
    float m_rctb_low_speed_hold_elapsed_s = 0.0F;

    std::array<CtsObsData, kMaxNormalObject> m_obs_data;
};

} // namespace cts
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_CTS_CTS_FUNCTION_H_
