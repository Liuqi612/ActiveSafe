#include "bsd_function.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// =============================================================================
// BSD 回灌调试打印
//
// 作用：在回灌数据时，把“影响 BSD 最终输出（左右 BSW/LCA 告警、声音、状态）”
//      的所有关键条件按帧打印到 stdout。可通过重定向落地成文件，例如：
//          ./your_replay_bin ...  > bsd_debug.log 2>&1
//      再用 grep "BSD_DBG" bsd_debug.log 过滤。
//
// BSD 输出链路（自上而下）总结：
//   1. 目标级筛选 (bsd_target_filter.cpp GetObjClass)：目标年龄/静止/纵向范围
//      + BSW(航向角/纵向速度) / CVW(曲线航向/纵向速度) 有效性 => ObsValidType。
//   2. BSW 区域判据 (bsd_risk_calc.cpp UpdateCriticalObsInBswZone)：
//      in_zone(多边形重叠) + in_zone_cnt/age/历史激活 + fallback 状态 +
//      非自车道内 + 后轴曲率半径-相对速度校验 => 侧级 m_bsw_alert_active。
//   3. CVW 区域判据 (UpdateCriticalObsInCvwZone)：
//      in_zone + in_zone_cnt + ttc<激活阈值 + 最近目标 + 非自车道内 +
//      曲率半径-相对速度-TTC 校验 => 侧级 m_cvw_alert_active。
//   4. 状态机 (bsd_state_machine.cpp StateMachine)：
//      state_off(软开关) / state_fault(诊断DID) / state_inhibit(车速使能/非D档) /
//      state_active(BSW保持 或 LCW一/二级) 决定 OFF/FAULT/INHIBIT/STANDBY/ACTIVE。
//   5. 输出装配：ACTIVE 时才输出 warn/sound；转向灯升 LEVEL_2；再受 GlobalConfig
//      的 k_use_shadowmode / k_bsd_enable 掩掉。
//
// 本文件只“读取”上面各阶段已算好的中间量（存放在 m_debug 快照与 m_bsd_out），
// 保证打印值与实际决策 100% 一致，不重复计算、不改变行为。
// =============================================================================

namespace active_safety {
namespace bsd {

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
    switch (static_cast<BsdSwitch>(s)) {
        case BsdSwitch::LIGHT_AND_SOUND: name = "LIGHT_AND_SOUND"; break;
        case BsdSwitch::OFF: name = "OFF"; break;
        case BsdSwitch::LIGHT: name = "LIGHT"; break;
        default: name = "DEFAULT"; break;
    }
    return std::to_string(s) + ":" + name;
}

std::string StateName(BsdState s) {
    const char *name = nullptr;
    switch (s) {
        case BsdState::OFF: name = "OFF"; break;
        case BsdState::FAULT: name = "FAULT"; break;
        case BsdState::INHIBIT: name = "INHIBIT"; break;
        case BsdState::STANDBY: name = "STANDBY"; break;
        case BsdState::ACTIVE: name = "ACTIVE"; break;
        default: name = "UNK"; break;
    }
    return std::to_string(static_cast<int>(s)) + ":" + name;
}

std::string SubStateName(int s) {
    const char *name = nullptr;
    switch (static_cast<math::ModeState>(s)) {
        case math::ModeState::OFF: name = "OFF"; break;
        case math::ModeState::FAULT: name = "FAULT"; break;
        case math::ModeState::ON: name = "ON"; break;
        case math::ModeState::INHIBIT: name = "INHIBIT"; break;
        case math::ModeState::STANDBY: name = "STANDBY"; break;
        case math::ModeState::ACTIVE: name = "ACTIVE"; break;
        default: name = "UNK"; break;
    }
    return std::to_string(s) + ":" + name;
}

std::string FallbackName(int s) {
    const char *name = nullptr;
    switch (static_cast<FallbackState>(s)) {
        case FallbackState::FALLBACK_ACTIVE: name = "ACTIVE"; break;
        case FallbackState::FALLBACK_PREVIOUS: name = "PREVIOUS"; break;
        default: name = "NONE"; break;
    }
    return std::to_string(s) + ":" + name;
}

std::string OnOff(OnOffStatus s) {
    const char *name = (s == OnOffStatus::Active) ? "Active" : "NotActive";
    return std::to_string(static_cast<int>(s)) + ":" + name;
}

// 打印一侧 BSW 候选目标的逐条判据(对应 UpdateCriticalObsInBswZone)
void DumpBsw(std::ostream &os, int side, const BsdBswTargetDebug &t, bool alert, int32_t alert_id) {
    const char *side_tag = (side == 0) ? "L" : "R";
    if (!t.valid && !alert) {
        return; // 该侧本帧无候选目标且无报警，略过以减少输出
    }
    os << "  [BSW-" << side_tag << "]"
       << " fusId=" << t.fus_trkID
       << " in_zone=" << t.in_zone
       << " cnt=" << t.in_zone_cnt
       << " fback=" << FallbackName(t.fallback_state)
       << " cnt_chk=" << t.count_check
       << " fback_chk=" << t.fback_check
       << " ego_lane=" << t.in_ego_lane
       << " curv_chk=" << t.curvature_radius_check
       << " long_vrel=" << t.curvi_long_vel_rel
       << " lat_posn=" << t.curvi_lat_posn_filt
       << " => alert=" << alert << "(id=" << alert_id << ")"
       << "\n";
}

// 打印一侧 CVW 候选目标的逐条判据(对应 UpdateCriticalObsInCvwZone)
void DumpCvw(std::ostream &os, int side, const BsdCvwTargetDebug &t, bool alert, int32_t alert_id, float closest) {
    const char *side_tag = (side == 0) ? "L" : "R";
    if (!t.valid && !alert) {
        return;
    }
    os << "  [CVW-" << side_tag << "]"
       << " fusId=" << t.fus_trkID
       << " in_zone=" << t.in_zone
       << " cnt=" << t.in_zone_cnt
       << " ttc=" << t.ttc
       << " mature=" << t.mature_in_zone
       << " center_chk=" << t.obj_effective_center_check
       << " ttc_chk=" << t.active_ttc_check
       << " ego_lane=" << t.in_ego_lane
       << " curv_chk=" << t.curvature_radius_check
       << " lat_posn=" << t.curvi_lat_posn_filt
       << " closest=" << closest
       << " => alert=" << alert << "(id=" << alert_id << ")"
       << "\n";
}

} // namespace

void BsdFunction::DumpDebugFrame(const AsVseOut &vse_out, const GlobalConfig &config) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(3);

    os << "==== BSD_DBG ts=" << vse_out.veh_time_stamp << " ====\n";

    // ---- 自车/环境输入（决定使能与区域阈值）----
    os << "  [EGO] spd=" << vse_out.speed
       << " gear=" << GearName(vse_out.actual_gear)
       << " rear_curv_radius=" << vse_out.rear_curvature_radius
       << " turn_light=" << static_cast<int>(vse_out.turn_light_switch_pos)
       << " hazard=" << static_cast<int>(vse_out.hazard_lamp_st)
       << "\n";

    // ---- 开关 / 使能 / 诊断（全局门控）----
    os << "  [SW] bsd_switch=" << SwitchName(vse_out.bsd_switch)
       << " did_config=0x" << std::hex << vse_out.function_did_config << std::dec
       << " | bsd_enable=" << config.k_bsd_enable
       << " shadowmode=" << config.k_use_shadowmode
       << "\n";

    // ---- 侧级候选目标逐条判据（目标筛选/区域层，定位为何某目标未报警）----
    DumpBsw(os, 0, m_debug.bsw[0], m_debug.bsw_alert_active[0], m_debug.bsw_alert_fusId[0]);
    DumpBsw(os, 1, m_debug.bsw[1], m_debug.bsw_alert_active[1], m_debug.bsw_alert_fusId[1]);
    DumpCvw(os, 0, m_debug.cvw[0], m_debug.cvw_alert_active[0], m_debug.cvw_alert_fusId[0], m_debug.closest_cvw_obs_dist[0]);
    DumpCvw(os, 1, m_debug.cvw[1], m_debug.cvw_alert_active[1], m_debug.cvw_alert_fusId[1], m_debug.closest_cvw_obs_dist[1]);

    // ---- 状态机门控条件 ----
    const BsdStateDebug &sm = m_debug.sm;
    os << "  [SM] off=" << sm.state_off
       << " fault=" << sm.state_fault
       << " inhibit=" << sm.state_inhibit
       << " active=" << sm.state_active
       << " | spd_enable=" << sm.host_speed_enable
       << " bsw_raw=" << sm.bsw_warn_raw
       << " hold=" << sm.hold_active
       << " final_bsw=" << sm.final_bsw_active
       << " lcw_lv1=" << sm.lcw_warn_level_1
       << " lcw_lv2=" << sm.lcw_warn_level_2
       << " substate=" << SubStateName(sm.cur_substate)
       << "\n";
    os << "  [SM-SIDE] bsw(L/R)=" << sm.bsw_left_warn << "/" << sm.bsw_right_warn
       << " lcw1(L/R)=" << sm.lcw_left_warn_1 << "/" << sm.lcw_right_warn_1
       << " lcw2(L/R)=" << sm.lcw_left_warn_2 << "/" << sm.lcw_right_warn_2
       << "\n";

    // ---- 最终输出（StateMachine 之后，含 shadowmode/enable 掩码）----
    os << "  [OUT] state=" << StateName(m_bsd_out.state)
       << " bsd_warn(L/R)=" << m_bsd_out.bsd_warn_left << "/" << m_bsd_out.bsd_warn_right
       << " lca_warn(L/R)=" << m_bsd_out.lca_warn_left << "/" << m_bsd_out.lca_warn_right
       << " sound=" << OnOff(m_bsd_out.bsc_sound)
       << " switch_req=" << m_bsd_out.switch_req
       << "\n";

    std::cout << os.str();
}

} // namespace bsd
} // namespace active_safety
