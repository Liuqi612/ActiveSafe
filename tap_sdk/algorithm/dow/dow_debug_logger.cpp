#include "dow_function.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// =============================================================================
// DOW 回灌调试打印
//
// 作用：在回灌数据时，把“影响 DOW 最终输出（左右告警等级/开关请求/状态）”的所有
//      关键条件按帧打印到 stdout。可通过重定向落地成文件，例如：
//          ./your_replay_bin ...  > dow_debug.log 2>&1
//      再用 grep "DOW_DBG" dow_debug.log 过滤。
//
// DOW 输出链路（自上而下）总结：
//   1. 目标级筛选 (dow_target_filter.cpp IsObjectValid / IsObjectRelevant)：
//        - 有效性：fus_trkID>0、跟踪状态 UPDATED/COASTED、非静止、宽度>最小阈值。
//        - 相关性：纵向接近相对速度、目标纵向速度、横向速度上限、航向角区间；
//          参考点落入后向/前向(FTM)检测多边形(CheckPointInZone)。
//   2. 运动学与确认 (dow_risk_calc.cpp UpdateCriticalObs)：
//        - 计算 TTC/距离/横向交叉点，判定相对自车运动方向(REAR/FRONT L/R)。
//        - 后向或前向(FTM)各自的 ttc/dist/dir 校验 + late_check，
//          连���满足 number_cycle_qualify 周期后置 m_alert=true。
//   3. 威胁选择 (FindThreatWarn)：在报警目标中按最小 TTC/距离选每侧关键目标，
//        产出 warn_left/warn_right 的原始触发(LEVEL_1)。
//   4. 状态机 (dow_state_machine.cpp StateMachine)：由
//        state_off(开关) / state_fault(诊断DID) / state_inhibit(车速区间) /
//        state_active(报警经最小保持 signalHold + 最长释放 signalRelease)
//        决定 OFF/FAULT/INHIBIT/STANDBY/ACTIVE；仅 ACTIVE 才输出告警，
//        并结合车门开启状态升级 LEVEL_1/LEVEL_2；最后受 shadowmode / dow_enable 掩掉。
//
// 本文件只“读取”上面各阶段已算好的中间量（存放在 m_debug 快照中），保证打印值与
// 实际决策 100% 一致，不重复计算、不改变行为。
// =============================================================================

namespace active_safety {
namespace dow {

namespace {

std::string StateName(DowState s) {
    const char *name = nullptr;
    switch (s) {
        case DowState::OFF: name = "OFF"; break;
        case DowState::FAULT: name = "FAULT"; break;
        case DowState::INHIBIT: name = "INHIBIT"; break;
        case DowState::STANDBY: name = "STANDBY"; break;
        case DowState::ACTIVE: name = "ACTIVE"; break;
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

std::string SwitchName(uint8_t s) {
    const char *name = nullptr;
    switch (s) {
        case static_cast<uint8_t>(DowSwitch::ON): name = "ON"; break;
        case static_cast<uint8_t>(DowSwitch::OFF): name = "OFF"; break;
        default: name = "RESERVE"; break;
    }
    return std::to_string(s) + ":" + name;
}

std::string OverlapName(int o) {
    const char *name = nullptr;
    switch (static_cast<OverlapType>(o)) {
        case OverlapType::NO_OVERLAP: name = "NONE"; break;
        case OverlapType::OVERLAP_REAR_RIGHT: name = "R-R"; break;
        case OverlapType::OVERLAP_REAR_LEFT: name = "R-L"; break;
        case OverlapType::OVERLAP_FRONT_RIGHT: name = "F-R"; break;
        case OverlapType::OVERLAP_FRONT_LEFT: name = "F-L"; break;
        default: name = "UNK"; break;
    }
    return std::to_string(o) + ":" + name;
}

std::string SideName(int s) {
    const char *name = nullptr;
    switch (static_cast<DowObjectSide>(s)) {
        case DowObjectSide::EGO_LANE: name = "LANE"; break;
        case DowObjectSide::EGO_LEFT_SIDE: name = "L"; break;
        case DowObjectSide::EGO_RIGHT_SIDE: name = "R"; break;
        default: name = "UNDEF"; break;
    }
    return std::to_string(s) + ":" + name;
}

std::string DirName(int d) {
    const char *name = nullptr;
    switch (static_cast<TravelEgoDirection>(d)) {
        case TravelEgoDirection::REAR_LEFT_DIRECTION: name = "REAR_L"; break;
        case TravelEgoDirection::REAR_RIGHT_DIRECTION: name = "REAR_R"; break;
        case TravelEgoDirection::FRONT_LEFT_DIRECTION: name = "FRONT_L"; break;
        case TravelEgoDirection::FRONT_RIGHT_DIRECTION: name = "FRONT_R"; break;
        default: name = "UNDEF"; break;
    }
    return std::to_string(d) + ":" + name;
}

std::string DoorName(uint8_t d) {
    const char *name = (d == static_cast<uint8_t>(DoorStatus::OPEN)) ? "OPEN" : "CLOSED";
    return std::to_string(d) + ":" + name;
}

// 打印单个障碍物的各阶段判据(仅打印本帧参与筛选的目标以减少输出)
void DumpObj(std::ostream &os, std::size_t idx, const DowObjDebug &o) {
    if (!o.used) {
        return;
    }
    os << "  [OBJ idx=" << idx << " fusId=" << o.fus_trkID << "]"
       << " valid=" << o.valid
       << "(st=" << o.status_ok << " mv=" << o.not_stationary << " w=" << o.width_ok << ")"
       << " relevant=" << o.relevant
       << "(rv=" << o.long_rel_vel_ok << " lv=" << o.long_vel_ok
       << " lat=" << o.lat_vel_ok << " hdg=" << o.heading_ok << ")"
       << "\n";
    os << "      spd=" << o.obj_speed << " rel_vel=" << o.long_rel_vel
       << " long_vel=" << o.long_vel << " lat_vel=" << o.lat_vel
       << " heading=" << o.heading << " width=" << o.width
       << "\n";
    os << "      overlap=" << OverlapName(o.overlap) << " side=" << SideName(o.location_side)
       << " ref=(" << o.ref_x << "," << o.ref_y << ")"
       << " dir=" << DirName(o.direction)
       << " ttc=" << o.ttc << " dist=" << o.distance << " isec_lat=" << o.intersec_lat
       << "\n";
    os << "      rear(ttc/dist/dir)=" << o.ttc_valid << "/" << o.dist_valid << "/" << o.dir_valid
       << " front(ttc/dist/dir)=" << o.front_ttc_valid << "/" << o.front_dist_valid << "/" << o.front_dir_valid
       << " late=" << o.late_check
       << " cycle=" << o.cycle_of_alert
       << " ALERT=" << o.alert
       << "\n";
}

} // namespace

void DowFunction::DumpDebugFrame(const AsVseOut &vse_out, const GlobalConfig &config) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(3);

    os << "==== DOW_DBG ts=" << vse_out.veh_time_stamp << " ====\n";

    // ---- 开关 / 使能 / 诊断（全局门控）----
    os << "  [SW] dow_switch=" << SwitchName(m_debug.sm.dow_switch)
       << " ego_spd=" << m_debug.sm.ego_speed
       << " | dow_enable=" << m_debug.sm.dow_enable
       << " shadowmode=" << m_debug.sm.use_shadowmode
       << "\n";

    // ---- 车门状态（决定 LEVEL_1/LEVEL_2 升级）----
    os << "  [DOOR] FL=" << DoorName(m_debug.sm.fl_door)
       << " FR=" << DoorName(m_debug.sm.fr_door)
       << " RL=" << DoorName(m_debug.sm.rl_door)
       << " RR=" << DoorName(m_debug.sm.rr_door)
       << "\n";

    // ---- 状态机条件 ----
    os << "  [SM]"
       << " off=" << m_debug.sm.state_off
       << " fault=" << m_debug.sm.state_fault
       << " inhibit=" << m_debug.sm.state_inhibit
       << " active=" << m_debug.sm.state_active
       << " | spd_enable=" << m_debug.sm.host_speed_enable
       << " raw=" << m_debug.sm.is_active_raw
       << " hold=" << m_debug.sm.active_hold
       << " release=" << m_debug.sm.signal_release
       << " final=" << m_debug.sm.final_active
       << " | sub_state=" << SubStateName(m_debug.sm.sub_state)
       << "\n";
    os << "      trans: off2inh=" << m_debug.sm.off2inhibit
       << " inh2sb=" << m_debug.sm.inhibit2standby
       << " inh2act=" << m_debug.sm.inhibit2active
       << " sb2act=" << m_debug.sm.standby2active
       << " act2sb=" << m_debug.sm.active2standby
       << "\n";

    // ---- 每个障碍物逐阶段判据(定位为何某目标未报警)----
    for (std::size_t i = 0; i < m_debug.obj.size(); ++i) {
        DumpObj(os, i, m_debug.obj[i]);
    }

    // ---- 最终输出（StateMachine 之后）----
    os << "  [OUT] state=" << StateName(m_dow_out.state)
       << " warn_left=" << m_dow_out.warn_left
       << " warn_right=" << m_dow_out.warn_right
       << " switch_req=" << m_dow_out.switch_req
       << " | left_tgt(id=" << m_dow_out.left_tgt.id << " ttc=" << m_dow_out.left_tgt.ttc << ")"
       << " right_tgt(id=" << m_dow_out.right_tgt.id << " ttc=" << m_dow_out.right_tgt.ttc << ")"
       << "\n";

    std::cout << os.str();
}

} // namespace dow
} // namespace active_safety
