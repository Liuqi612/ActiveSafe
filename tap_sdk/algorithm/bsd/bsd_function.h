#ifndef TAP_SDK_ALGORITHM_BSD_BSD_FUNCTION_H_
#define TAP_SDK_ALGORITHM_BSD_BSD_FUNCTION_H_
#include "bsd_cals.h"
#include "bsd_obs.h"
#include "common/basic_types.h" 
#include "common/enum_type.h"
#include "interface/active_safety_types.h"
#include "math/statemachine/modemanager.hpp"
#include "math/utils/util_math.h"
#include "math/signalprocess/signal_hold_block/signal_hold_block.h"

#include <array>

namespace active_safety {
namespace bsd {

enum class BsdSwitch : uint8_t { DEFAULT = 0, LIGHT_AND_SOUND = 1, OFF = 2, LIGHT = 3 };

using math::ModeCondition;
using math::ModeConditionContext;
using math::ModeManager;
using math::ModeStateCondition;
using math::SignalHoldBlock;

struct BsdFuncData {
    bool prev_cvw_active = false;
    bool prev_bsw_active = false;
    int32_t prev_cvw_alert_obs_id = 0;
    int32_t prev_bsw_alert_obs_id = 0;
};

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

// BSD 状态机每帧计算出的关键门控条件快照。
// 由 StateMachine 在运行时填充，供 bsd_debug_logger 在回灌时打印，保证打印值与实际决策完全一致。
struct BsdStateDebug {
    // 四个基础状态位（直接决定 OFF/FAULT/INHIBIT/STANDBY/ACTIVE 走向）
    bool state_off = false;      // 软开关关闭
    bool state_fault = false;    // 诊断故障
    bool state_inhibit = false;  // 被抑制(车速不使能 或 非D档)
    bool state_active = false;   // 满足激活(BSW保持 或 LCW一/二级)

    // 参与 inhibit/active 的中间量
    bool host_speed_enable = false;  // 自车车速处于使能区间(含迟滞)
    bool bsw_warn_raw = false;       // 左右任一 BSW 原始报警
    bool hold_active = false;        // BSW 报警保持块输出
    bool final_bsw_active = false;   // 经保持后的 BSW 激活
    bool lcw_warn_level_1 = false;   // 左右任一 CVW 一级
    bool lcw_warn_level_2 = false;   // 左右任一 CVW 二级(叠加转向灯)

    // 左右两侧原始报警(未经状态机掩掉)
    bool bsw_left_warn = false;
    bool bsw_right_warn = false;
    bool lcw_left_warn_1 = false;
    bool lcw_right_warn_1 = false;
    bool lcw_left_warn_2 = false;
    bool lcw_right_warn_2 = false;

    // 原始输入
    float speed = 0.0F;
    uint8_t gear = 0;
    uint8_t sw = 0;
    int cur_substate = 0;  // ModeState 当前子状态
};

// 一侧 BSW 区域关键候选目标的逐条判据快照(对应 UpdateCriticalObsInBswZone)。
struct BsdBswTargetDebug {
    bool valid = false;              // 本帧该侧是否记录了 BSW 候选目标
    int32_t fus_trkID = 0;
    bool in_zone = false;            // 目标多边形与 BSW 区域重叠
    int in_zone_cnt = 0;             // 连续在区域内周期数
    int fallback_state = 0;          // FallbackState 0:NONE 1:ACTIVE 2:PREVIOUS
    bool count_check = false;        // 周期数/年龄/历史激活 满足
    bool fback_check = false;        // fallback 状态允许报警
    bool in_ego_lane = false;        // 落在自车道内(会抑制报警)
    bool curvature_radius_check = false; // 后轴曲率半径-相对速度校验通过
    float curvi_long_vel_rel = 0.0F; // 纵向相对速度(去激活判据)
    float curvi_lat_posn_filt = 0.0F;
};

// 一侧 CVW 区域关键候选目标的逐条判据快照(对应 UpdateCriticalObsInCvwZone)。
struct BsdCvwTargetDebug {
    bool valid = false;              // 本帧该侧是否记录了 CVW 候选目标
    int32_t fus_trkID = 0;
    bool in_zone = false;            // 目标多边形与 CVW 区域重叠
    int in_zone_cnt = 0;             // 连续在区域内周期数(远距离双倍计数)
    float ttc = 0.0F;                // 计算得到的 TTC
    bool mature_in_zone = false;     // 周期数达标 或 历史激活
    bool obj_effective_center_check = false; // 目标较此前最近目标更近
    bool active_ttc_check = false;   // ttc <= 激活阈值
    bool in_ego_lane = false;        // 落在自车道内(会抑制报警)
    bool curvature_radius_check = false; // 后轴曲率半径-相对速度-TTC 校验通过
    float curvi_lat_posn_filt = 0.0F;
};

// 回灌调试快照：聚合本帧影响 BSD 输出的所有关键中间条件。
struct BsdDebugSnapshot {
    BsdStateDebug sm;
    // 每侧关键候选目标逐条判据：下标 0:Left 1:Right
    BsdBswTargetDebug bsw[2];
    BsdCvwTargetDebug cvw[2];
    // 侧级最终报警(读 m_bsw_alert_active/m_cvw_alert_active)
    bool bsw_alert_active[2] = {false, false};
    int32_t bsw_alert_fusId[2] = {-1, -1};
    bool cvw_alert_active[2] = {false, false};
    int32_t cvw_alert_fusId[2] = {-1, -1};
    float closest_cvw_obs_dist[2] = {0.0F, 0.0F};
};

class BsdFunction {
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
    void CalcValidZone(const VehicleConfig &config, BsdObsData &obs_data, const AsVseOut &vse_out);
    void UpdateCriticalObsInBswZone(const AsVseOut &vse_out, BsdObsData &obs_data);
    void UpdateCriticalObsInCvwZone(const AsVseOut &vse_out, BsdObsData &obs_data);
    void UpdateFallbackState(BsdObsData &obs_data);
    void CalcTTc(const VehicleConfig &veh_config, BsdObsData &obs_data);
    void WarnJudgement();
    void StateMachine(const GlobalConfig &config, const AsVseOut &vse_out);
    void FillTargetInfo(const BsdObsData &obs_data, AsTargetInfo_T &tgt_info);

    // 回灌调试：把本帧影响 BSD 输出的所有关键条件打印到 stdout(可重定向到文件)。
    // 受 config 中的 k_bsd_enable 与 k_use_shadowmode 影响，故一并传入。
    void DumpDebugFrame(const AsVseOut &vse_out, const GlobalConfig &config);

    BsdOutput m_bsd_out;
    bool m_bsw_active;
    bool m_lcw_active;
    bool m_host_speed_enable;
    ModeManager m_bsd_mode;
    ModeConditionContext m_bsd_mode_context;
    ModeStateCondition m_bsd_mode_cond;
    // Decide function result.
    std::array<WarnLevel, 2> m_bsw_level;
    std::array<int32_t, 2> m_bsw_obs_id;
    std::array<WarnLevel, 2> m_cvw_level;
    std::array<int32_t, 2> m_cvw_obs_id;

    SignalHoldBlock m_bsw_hold;

    BsdCal m_bsd_cal;

    std::array<BsdObsData, kMaxNormalObject> m_obs_data;

    // Variable to indicate threat after obs iters.
    std::array<bool, 2> m_bsw_alert_active = {false, false};
    std::array<int32_t, 2> m_bsw_alert_fusId = {-1, -1};

    // CVW 最近目标距离无效初始值(m)
    static constexpr float k_cvw_closest_dist_init = -1000.0F;
    std::array<float, 2> m_closest_cvw_obs_dist = {k_cvw_closest_dist_init, k_cvw_closest_dist_init};
    std::array<bool, 2> m_cvw_alert_active = {false, false};
    std::array<int32_t, 2> m_cvw_alert_fusId = {-1, -1};

    // record data.
    BsdFuncData m_prev_data[2];

    // 回灌调试用：每帧记录影响 BSD 输出的关键中间条件，由 DumpDebugFrame 打印
    BsdDebugSnapshot m_debug;
};
} // namespace bsd
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_BSD_BSD_FUNCTION_H_
