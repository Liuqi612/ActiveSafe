#ifndef TAP_SDK_ALGORITHM_DOW_DOW_FUNCTION_H_
#define TAP_SDK_ALGORITHM_DOW_DOW_FUNCTION_H_
#include "common/enum_type.h"
#include "common/global_config.h"
#include "dow_cals.h"
#include "dow_obs.h"
#include "interface/active_safety_types.h"
#include "interface/active_safety_vse.h"
#include "math/statemachine/modemanager.hpp"
#include "math/signalprocess/feature_freezing_block/feature_freezing_block.h"
#include "math/signalprocess/signal_release_block/signal_release_block.h"
#include "math/signalprocess/signal_hold_block/signal_hold_block.h"
#include "math/utils/util_math.h"

#include <array>

namespace active_safety {
namespace dow {

enum class DowSwitch : uint8_t { RESERVE_0 = 0, ON = 1, OFF = 2, RESERVE_3 = 3 };

using math::ModeCondition;
using math::ModeConditionContext;
using math::ModeManager;
using math::ModeStateCondition;
using math::FeatureFreezingBlock;
using math::SignalHoldBlock;
using math::SignalReleaseBlock;

struct DowOutput {
    AsTargetInfo_T left_tgt;
    AsTargetInfo_T right_tgt;
    uint32_t       switch_req; // 0:Default 1:灯光+声音 2: 关闭 3: 灯光
    uint32_t       warn_left;  // 0:Inactive, 1:Level_1, 2:Level_2
    uint32_t       warn_right; // 0:Inactive, 1:Level_1, 2:Level_2
    DowState       state;
};

// 单个障碍物在 DOW 处理链路各阶段的判据快照。
// 由 IsObjectValid/IsObjectRelevant/UpdateCriticalObs 在运行时填充，
// 供 dow_debug_logger 在回灌时打印，保证打印值与实际决策 100% 一致，不重复计算。
struct DowObjDebug {
    bool used = false;    // 本帧该槽位是否有有效目标(fus_trkID>0)
    int32_t fus_trkID = 0;

    // 有效性判据 (IsObjectValid)
    bool valid = false;          // 整体有效
    bool status_ok = false;      // 跟踪状态为 UPDATED/COASTED
    bool not_stationary = false; // 非静止
    bool width_ok = false;       // 宽度大于最小阈值

    // 相关性判据 (IsObjectRelevant)
    bool relevant = false;         // 整体相关(有效性+区域+航向)
    bool long_rel_vel_ok = false;  // 纵向相对接近速度达标
    bool long_vel_ok = false;      // 目标纵向速度达标
    bool lat_vel_ok = false;       // 横向速度未超限
    bool heading_ok = false;       // 航向角在允许区间

    // 原始量(便于定位为何被过滤)
    float obj_speed = 0.0F;
    float long_rel_vel = 0.0F;
    float long_vel = 0.0F;
    float lat_vel = 0.0F;
    float heading = 0.0F;
    float width = 0.0F;

    // 区域/几何 (CheckPointInZone / FindReferencePoint)
    int overlap = 0;       // OverlapType
    int location_side = 0; // DowObjectSide
    float ref_x = 0.0F;
    float ref_y = 0.0F;

    // 运动学与确认 (UpdateCriticalObs)
    int direction = 0;      // TravelEgoDirection(相对自车运动方向)
    float ttc = 0.0F;
    float distance = 0.0F;
    float intersec_lat = 0.0F;
    bool ttc_valid = false;        // 后向 TTC 校验
    bool dist_valid = false;       // 后向距离校验
    bool dir_valid = false;        // 后向方向校验
    bool front_ttc_valid = false;  // 前向(FTM) TTC 校验
    bool front_dist_valid = false; // 前向(FTM) 距离校验
    bool front_dir_valid = false;  // 前向(FTM) 方向校验
    bool late_check = false;       // 迟报警校验
    int cycle_of_alert = 0;        // 报警确认累计周期
    bool alert = false;            // 目标本帧是否报警
};

// DOW 状态机每帧计算出的关键中间条件快照。
struct DowSmDebug {
    // 四个基础状态位(直接决定 OFF/FAULT/INHIBIT/STANDBY/ACTIVE 走向)
    bool state_off = false;      // 软开关关闭
    bool state_fault = false;    // 诊断故障
    bool state_inhibit = false;  // 被抑制(车速不在允许区间)
    bool state_active = false;   // 满足激活(经保持/释放处理)

    // 参与激活判定的中间量
    bool host_speed_enable = false; // 自车车速在允许区间
    bool is_active_raw = false;     // 原始威胁(warn_left>0 || warn_right>0)
    bool active_hold = false;       // 最小报警保持窗口输出
    bool signal_release = false;    // 达到最长报警时间被强制释放
    bool final_active = false;      // 最终激活信号

    // 状态机跳转条件
    bool off2inhibit = false;
    bool inhibit2standby = false;
    bool inhibit2active = false;
    bool standby2active = false;
    bool active2standby = false;
    int sub_state = 0;              // ModeState 结果

    // 门状态(影响告警等级升级 LEVEL_1/LEVEL_2)
    uint8_t fl_door = 0;
    uint8_t fr_door = 0;
    uint8_t rl_door = 0;
    uint8_t rr_door = 0;

    // 全局门控
    bool use_shadowmode = false;
    bool dow_enable = false;
    float ego_speed = 0.0F;
    uint8_t dow_switch = 0;
};

struct DowDebugSnapshot {
    DowSmDebug sm;
    std::array<DowObjDebug, kMaxNormalObject> obj;
};

class DowFunction {
  public:
    explicit DowFunction(const VehicleConfig &vehcfg = VehicleConfig());
    ~DowFunction();

    void Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list);
    void InitZone(const VehicleConfig &vehcfg);
    void FindReferencePoint(DowObsData &obs_data);

    void CheckMotion(DowObsData &obs_data);
    bool IsObjectValid(DowObsData &obs_data);
    bool IsObjectRelevant(const AsVseOut &vse_out, DowObsData &obs_data);

    void UpdateCriticalObs(const AsVseOut &vse_out, DowObsData &obs_data);
    void FillTargetInfo(const DowObsData &obs_data, AsTargetInfo_T &tgt_info);
    void ResetObjectPersistent(DowObsData &obs_data);
    void CheckPointInZone(const math::Point2D &pt, DowObsData &obs_data);
    void FindThreatWarn();
    void StateMachine(const GlobalConfig &config, const AsVseOut &vse_out);

    // 回灌调试：把本帧影响 DOW 输出的所有关键条件打印到 stdout(可重定向到文件)。
    // 受 config 中的 dow_enable 与 shadowmode 影响，故一并传入。
    void DumpDebugFrame(const AsVseOut &vse_out, const GlobalConfig &config);

    DowOutput m_dow_out;

    // 回灌调试用：每帧记录影响 DOW 输出的关键中间条件，由 DumpDebugFrame 打印
    DowDebugSnapshot m_debug;

    math::Point2D CalcObjectCorner(float center_x, float center_y, float heading, float local_x, float local_y);

    DowCal m_dow_cal;

    math::Polygon m_rear_left_zone;
    math::Polygon m_rear_right_zone;
    math::Polygon m_front_left_zone;
    math::Polygon m_front_right_zone;

    std::array<DowObsData, kMaxNormalObject> m_obs_data;

    ModeManager          m_dow_mode;
    ModeConditionContext m_dow_mode_context;
    ModeStateCondition   m_dow_mode_cond;
    SignalHoldBlock      m_dow_hold;
    SignalReleaseBlock   m_dow_release;

};

} // namespace dow
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_DOW_DOW_FUNCTION_H_
