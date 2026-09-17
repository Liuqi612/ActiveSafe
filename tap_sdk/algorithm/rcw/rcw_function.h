#ifndef TAP_SDK_ALGORITHM_RCW_RCW_FUNCTION_H_
#define TAP_SDK_ALGORITHM_RCW_RCW_FUNCTION_H_
#include "common/enum_type.h"
#include "common/global_config.h"
#include "interface/active_safety_types.h"
#include "interface/active_safety_vse.h"
#include "math/signalprocess/feature_freezing_block/feature_freezing_block.h"
#include "math/signalprocess/on_delay_block/on_delay_block.h"
#include "math/signalprocess/signal_hold_block/signal_hold_block.h"
#include "math/signalprocess/signal_release_block/signal_release_block.h"
#include "math/statemachine/modemanager.hpp"
#include "math/signalprocess/off_delay_block/off_delay_block.h"
#include "math/utils/util_math.h"
#include "rcw_cals.h"
#include "rcw_obs.h"

#include <array>

namespace active_safety {
namespace rcw {

enum class RcwSwitch : uint8_t { RESERVE_0 = 0, ON = 1, OFF = 2, RESERVE_3 = 3 };

// RCW switch_req 输出码: 0:reserve,1:On,2:Off,3:reserve
enum class RcwSwitchReqOut : uint8_t { RESERVE_0 = 0, ON = 1, OFF = 2, RESERVE_3 = 3 };

using math::FeatureFreezingBlock;
using math::ModeCondition;
using math::ModeConditionContext;
using math::ModeManager;
using math::ModeStateCondition;
using math::OnDelayBlock;
using math::OffDelayBlock;
using math::SignalHoldBlock;
using math::SignalReleaseBlock;

struct RcwOutput {
    AsTargetInfo_T tgt_rcw;
    // 0:reserve,1:On,2:Off,3:reserve
    uint32_t switch_req;
    OnOffStatus rcw_collision_warn;
    RcwState state;
};

enum RcwWarnState { WARNING_OFF, WARNING_ON, WARNING_SUPPRESS, WARNING_HOLD };

// ---- 回灌调试快照(见 rcw_debug_logger.cpp) ----
// 说明：以下各结构仅由算法在运行时把“已算好的中间量”读入，供 DumpDebugFrame 在回灌时打印，
//       保证打印值与实际决策 100% 一致，不重复计算、不改变行为。

// 单个报警等级(i=0..1)的逐级判据快照，对应 Calculate_WarnLevel 内每级 TTC/概率判断。
struct RcwLevelDebug {
    float relative_speed = 0.0F;             // 合成相对速度(带符号)
    float ttc = 0.0F;                        // 关键目标 TTC
    float warn_ttc_thres = 0.0F;             // 本级激活 TTC 阈值(含短TTC下调)
    float min_ttc_thres = 0.0F;              // 本级最小 TTC 阈值
    float crash_prob = 0.0F;                 // 关键目标综合碰撞概率
    float min_crash_prob = 0.0F;             // 本级最小碰撞概率阈值
    float warn_ttc_thres_deactive = 0.0F;    // 本级退出 TTC 阈值
    bool active = false;                     // 本级是否判定激活
};

// 关键目标(最近 inpath 目标)从筛选到风险评估的逐项判据快照。
struct RcwTargetDebug {
    bool valid = false;                      // 本帧是否存在关键目标
    int32_t fus_trkID = 0;
    uint8_t track_id = 0;
    float heading = 0.0F;
    float filtered_heading = 0.0F;

    // 目标有效性/路径(读自 IsRcwValidObj / ObjInPathEvaluator 的存量结果)
    bool is_valid = false;                   // IsRcwValidObj 结果
    bool is_current_inpath = false;
    bool is_pred_inpath = false;
    bool is_inpath = false;

    // CheckObjectInfo 各筛选位(直接决定 is_valid_obj_last_cycle)
    bool f_moving_obj = false;               // 目标速度达阈值
    bool f_obj_counter = false;              // 目标年龄达阈值
    bool f_valid_length = false;             // 目标长度达阈值
    bool f_valid_heading = false;            // 航向角在接近角区间内
    bool f_valid_min_rel_speed = false;      // 相对速度 > 最小阈值
    bool f_valid_max_rel_speed = false;      // 相对速度 < 最大阈值
    bool f_valid_longpos = false;            // 纵向位置在自车后方
    bool f_valid_latpos = false;             // 横向位置在半车宽内
    bool f_inline = false;                   // 在车道内(或关闭车道滤波)
    bool f_valid_obj_width = false;          // 目标宽度达阈值
    bool f_valid_x_rel_speed = false;        // 纵向相对速度差达阈值
    bool f_not_turning = false;              // 目标未在转弯(!f_turning)
    bool f_valid_bike_lat_pos = false;       // 自行车横向位置约束
    bool is_in_lane = false;                 // 连续在车道内计数达阈值
    bool is_valid_obj_last_cycle = false;    // CheckObjectInfo 总结果

    // 参与判断的原始量/阈值
    float age = 0.0F;
    float rel_vel_long = 0.0F;
    float min_rel_speed = 0.0F;
    float max_approach_angle = 0.0F;
    bool ego_stationary = false;

    // 风险(CrashProbSteerBrake)
    float crash_prob_braking = 0.0F;
    float crash_prob_steering = 0.0F;
    float crash_prob_combined = 0.0F;
    float ttc = 0.0F;

    RcwLevelDebug levels[2];
};

// 状态机(StateMachine)的条件集合快照。
struct RcwStateDebug {
    // 报警时序链
    bool is_active_raw = false;              // level 触发原始激活
    bool delay_active = false;               // 经开启延时
    bool hold_active = false;                // 经最短报警保持
    bool final_active = false;               // 送入状态机的最终激活

    // 抑制来源
    bool is_suppressed = false;              // 综合抑制
    bool signal_release = false;             // 超过最长报警时间释放
    bool freezing = false;                   // 处于冷却期
    bool ttc_inhibit = false;                // 触发前 TTC 过小抑制

    // 状态机四个基础条件位
    bool state_off = false;                  // 软开关关闭
    bool state_fault = false;                // 诊断故障
    bool state_inhibit = false;              // 车速/档位抑制
    bool state_active = false;               // 满足激活

    // 短 TTC 目标行为
    bool short_ttc_flag = false;
    bool short_ttc_offdly = false;
};

struct RcwDebugSnapshot {
    // 目标选择概览
    int min_dist_idx = -1;                   // 关键目标在 m_obs_data 中的下标
    float min_dist = 0.0F;                   // 关键目标纵向位置(排序值)
    int inpath_count = 0;                    // 本帧 inpath 目标数

    RcwTargetDebug target;
    RcwStateDebug state;
};

class RcwFunction {
  public:
    RcwFunction();
    ~RcwFunction();

    void Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list);

    bool CheckObjectInfo(const AsVseOut &vse_out, RcwObsData &obs_data);
    void ObjInPathEvaluator(const AsVseOut &vse_out, RcwObsData &obs_data);
    void CalPredInpath(const AsVseOut &vse_out, RcwObsData &obs_data);
    void IsRcwValidObj(const AsVseOut &vse_out, RcwObsData &obs_data);
    void RcwThreatEvaluator(const AsVseOut &vse_out, const GlobalConfig &config);
    void Calculate_TTC(const AsVseOut &vse_out, RcwObsData &obs_data);
    void Filter_Object_Heading(const AsVseOut &vse_out, RcwObsData &obs_data);
    void CrashProbSteerBrake(const AsVseOut &vse_out, RcwObsData &obs_data);
    void ResetTargetInfo(AsTargetInfo_T &tgt_info);
    void EvaluateTarBehavior();

    float GetBrakeAccToAvoidRearEndColl(const float vcs_long_acc, float lon_rel_vel_obj, float lon_pos_bumper_obj);
    float GetSteerAccToAvoidRearEndColl(const AsVseOut &vse_out, RcwObsData &obs_data, float lon_rel_vel_obj, const float lat_rel_vel_obj,
                                        float lon_pos_bumper_obj);

    void Calculate_WarnLevel(const AsVseOut &vse_out);
    void StateMachine(const GlobalConfig &config, const AsVseOut &vse_out);
    void FillTargetInfo(const RcwObsData &obs_data, AsTargetInfo_T &tgt_info);
    void ResetPersistant(RcwObsData &obs_data);

    // 回灌调试：把本帧影响 RCW 输出的所有关键条件打印到 stdout(可重定向到文件)。
    // 受 config 中的 k_rcw_enable / k_use_shadowmode 门控影响，故一并传入。
    void DumpDebugFrame(const AsVseOut &vse_out, const GlobalConfig &config);

    RcwCal m_rcw_cal;
    RcwObsData m_rcw_tar;

    // 回灌调试用：每帧记录影响 RCW 输出的关键中间条件，由 DumpDebugFrame 打印
    RcwDebugSnapshot m_debug;

    std::array<RcwObsData, kMaxNormalObject> m_obs_data;

    RcwOutput m_rcw_out;
    ModeManager m_rcw_mode;
    ModeConditionContext m_rcw_mode_context;
    ModeStateCondition m_rcw_mode_cond;
    OnDelayBlock m_rcw_ondelay;
    SignalHoldBlock m_rcw_hold;

    // 报警时间限制和冷却时间模块
    SignalReleaseBlock m_rcw_release;
    FeatureFreezingBlock m_rcw_freezing;
    OffDelayBlock m_short_ttc_offdly;

    int32_t m_last_tar_obj_id = 0;
    std::array<bool, 2> m_rcw_active = {false,false};
    // inpath的目标
    std::vector<int> m_inpath_index;
    int m_min_dist_idx = -1;
    static constexpr float k_rcw_min_dist_init = -100.0F; // 最近目标距离排序哨兵初值(m)
    float m_min_dist = k_rcw_min_dist_init;
    int m_ego_stationary_counter = 0;
    bool m_ego_stationary = false;
    bool m_short_ttc_flag = false;
};

} // namespace rcw
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_RCW_RCW_FUNCTION_H_
