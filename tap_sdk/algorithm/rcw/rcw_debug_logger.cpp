#include "rcw_function.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// =============================================================================
// RCW 回灌调试打印
//
// 作用：在回灌数据时，把“影响 RCW 最终输出（后向碰撞告警 rcw_collision_warn/状态）”
//      的所有关键条件按帧打印到 stdout。可通过重定向落地成文件，例如：
//          ./your_replay_bin ...  > rcw_debug.log 2>&1
//      再用 grep "RCW_DBG" rcw_debug.log 过滤。
//
// RCW 输出链路（自上而下）总结：
//   1. 目标筛选 (rcw_target_filter.cpp)：
//        - IsRcwValidObj：fus_trkID>0、track 状态 UPDATED、纵向位置在自车后方。
//        - ObjInPathEvaluator/CalPredInpath：横向位置在有效车道宽内(current inpath) 且
//          预测横向位置在阈值内(pred inpath) => is_inpath。
//        - Update：inpath 目标中按纵向位置取最近，非 vehicle 需 TTC<2.0 才参与排序，
//          产出关键目标 m_min_dist_idx / m_rcw_tar。
//        - CheckObjectInfo：目标速度/年龄/长度/航向角/相对速���(min,max)/纵横位置/
//          车道内确认/宽度/相对速度差/未转弯/自行车横向约束 => is_valid_obj_last_cycle。
//   2. 风险评估 (rcw_risk_calc.cpp CrashProbSteerBrake)：
//        - 由避撞所需制动/转向加速度查表得 crash_prob_braking/steering，取小得 combined。
//   3. 报警等级 (Calculate_WarnLevel)：两级各自判断 TTC<激活阈值 且 ≥最小TTC 且
//        combined≥最小概率 => m_rcw_active[i]；另有退出阈值/最小相对速度/大转角抑制。
//   4. 状态机 (rcw_state_machine.cpp StateMachine)：
//        onDelay/signalHold/signalRelease/featureFreezing 组成时序，得 final_active；
//        state_off(软开关)/state_fault(诊断DID)/state_inhibit(车速/档位)/state_active
//        决定 OFF/FAULT/INHIBIT/STANDBY/ACTIVE；再受 k_use_shadowmode / k_rcw_enable 掩掉。
//
// 本文件只“读取”上面各阶段已算好的中间量(存放在 m_debug 快照中)，保证打印值与实际
// 决策 100% 一致，不重复计算、不改变行为。
// =============================================================================

namespace active_safety {
namespace rcw {

namespace {

std::string GearName(uint8_t g) {
    const char *name = nullptr;
    switch (static_cast<GearPosition>(g)) {
        case GearPosition::PARK: name = "P"; break;
        case GearPosition::REVERSE: name = "R"; break;
        case GearPosition::NEUTRAL: name = "N"; break;
        case GearPosition::DRIVE: name = "D"; break;
        default: name = "UNK"; break;
    }
    return std::to_string(g) + ":" + name;
}

std::string SwitchName(uint8_t s) {
    const char *name = nullptr;
    switch (static_cast<RcwSwitch>(s)) {
        case RcwSwitch::ON: name = "ON"; break;
        case RcwSwitch::OFF: name = "OFF"; break;
        default: name = "RESERVE"; break;
    }
    return std::to_string(s) + ":" + name;
}

std::string StateName(RcwState s) {
    const char *name = nullptr;
    switch (s) {
        case RcwState::OFF: name = "OFF"; break;
        case RcwState::FAULT: name = "FAULT"; break;
        case RcwState::INHIBIT: name = "INHIBIT"; break;
        case RcwState::STANDBY: name = "STANDBY"; break;
        case RcwState::ACTIVE: name = "ACTIVE"; break;
        default: name = "UNK"; break;
    }
    return std::to_string(static_cast<int>(s)) + ":" + name;
}

std::string OnOff(OnOffStatus s) {
    const char *name = (s == OnOffStatus::Active) ? "Active" : "NotActive";
    return std::to_string(static_cast<int>(s)) + ":" + name;
}

// 打印关键目标的逐项筛选/风险/分级判据
void DumpTarget(std::ostream &os, const RcwTargetDebug &t) {
    if (!t.valid) {
        os << "  [TGT] <none>\n";
        return;
    }
    os << "  [TGT] fusId=" << t.fus_trkID
       << " trk=" << static_cast<int>(t.track_id)
       << " hdg=" << t.heading
       << " filt_hdg=" << t.filtered_heading
       << " age=" << t.age
       << " | inpath=" << t.is_inpath
       << "(cur=" << t.is_current_inpath << " pred=" << t.is_pred_inpath << ")"
       << " valid=" << t.is_valid
       << "\n";
    // CheckObjectInfo 各筛选位
    os << "    [FILT] valid_obj=" << t.is_valid_obj_last_cycle
       << " | moving=" << t.f_moving_obj
       << " age_ok=" << t.f_obj_counter
       << " len_ok=" << t.f_valid_length
       << " hdg_ok=" << t.f_valid_heading
       << " min_vrel=" << t.f_valid_min_rel_speed
       << " max_vrel=" << t.f_valid_max_rel_speed
       << " longpos=" << t.f_valid_longpos
       << " latpos=" << t.f_valid_latpos
       << " inline=" << t.f_inline
       << " width_ok=" << t.f_valid_obj_width
       << " vrel_diff=" << t.f_valid_x_rel_speed
       << " not_turn=" << t.f_not_turning
       << " bike_lat=" << t.f_valid_bike_lat_pos
       << " in_lane=" << t.is_in_lane
       << "\n";
    os << "    [FILT] rel_vel_long=" << t.rel_vel_long
       << " min_rel_spd=" << t.min_rel_speed
       << " max_appr_ang=" << t.max_approach_angle
       << " ego_stationary=" << t.ego_stationary
       << "\n";
    // 风险
    os << "    [RISK] p_brake=" << t.crash_prob_braking
       << " p_steer=" << t.crash_prob_steering
       << " p_comb=" << t.crash_prob_combined
       << " ttc=" << t.ttc
       << "\n";
    // 两级分级判据
    for (int i = 0; i < 2; ++i) {
        const RcwLevelDebug &l = t.levels[i];
        os << "    [LVL" << i << "]"
           << " vrel=" << l.relative_speed
           << " ttc=" << l.ttc
           << " warn_thr=" << l.warn_ttc_thres
           << " min_ttc=" << l.min_ttc_thres
           << " | p_comb=" << l.crash_prob
           << " min_p=" << l.min_crash_prob
           << " deact_thr=" << l.warn_ttc_thres_deactive
           << " active=" << l.active
           << "\n";
    }
}

// 打印状态机条件集合
void DumpState(std::ostream &os, const RcwStateDebug &s) {
    os << "  [SM] act_raw=" << s.is_active_raw
       << " delay=" << s.delay_active
       << " hold=" << s.hold_active
       << " final=" << s.final_active
       << " | off=" << s.state_off
       << " fault=" << s.state_fault
       << " inhibit=" << s.state_inhibit
       << " active=" << s.state_active
       << "\n";
    os << "  [SM] suppress=" << s.is_suppressed
       << "(release=" << s.signal_release
       << " freezing=" << s.freezing
       << " ttc_inh=" << s.ttc_inhibit << ")"
       << " short_ttc=" << s.short_ttc_flag
       << " short_ttc_dly=" << s.short_ttc_offdly
       << "\n";
}

} // namespace

void RcwFunction::DumpDebugFrame(const AsVseOut &vse_out, const GlobalConfig &config) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(3);

    os << "==== RCW_DBG ts=" << vse_out.veh_time_stamp << " ====\n";

    // ---- 自车/驾驶员输入 ----
    os << "  [EGO] spd=" << vse_out.speed
       << " gear=" << GearName(vse_out.actual_gear)
       << " str_ang=" << vse_out.steerwheelangle
       << " long_acc=" << vse_out.long_accel
       << " lat_acc=" << vse_out.lat_accel
       << " vcs_long_vel=" << vse_out.vcs_long_vel
       << " vcs_lat_vel=" << vse_out.vcs_lat_vel
       << " straight=" << vse_out.straight_driving
       << "\n";

    // ---- 开关 / 使能 / 诊断（全局门控）----
    os << "  [SW] rcw_switch=" << SwitchName(vse_out.rcw_switch)
       << " did_config=0x" << std::hex << vse_out.function_did_config << std::dec
       << " | rcw_enable=" << config.k_rcw_enable
       << " shadowmode=" << config.k_use_shadowmode
       << "\n";

    // ---- 目标选择概览 ----
    os << "  [SEL] inpath_cnt=" << m_debug.inpath_count
       << " min_dist_idx=" << m_debug.min_dist_idx
       << " min_dist=" << m_debug.min_dist
       << "\n";

    // ---- 关键目标逐项判据（定位为何未升级/未激活）----
    DumpTarget(os, m_debug.target);

    // ---- 状态机条件 ----
    DumpState(os, m_debug.state);

    // ---- 最终输出（StateMachine 之后）----
    os << "  [OUT] state=" << StateName(m_rcw_out.state)
       << " collision_warn=" << OnOff(m_rcw_out.rcw_collision_warn)
       << " switch_req=" << m_rcw_out.switch_req
       << " tgt_id=" << m_rcw_out.tgt_rcw.id
       << " tgt_ttc=" << m_rcw_out.tgt_rcw.ttc
       << "\n";

    std::cout << os.str();
}

} // namespace rcw
} // namespace active_safety
