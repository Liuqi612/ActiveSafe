#include "cts_function.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// =============================================================================
// CTS 回灌调试打印
//
// 作用：在回灌数据时，把“影响 CTS 最终输出（左右告警/声音/制动请求/碰撞方向）”
//      的所有关键条件按帧打印到 stdout。可通过重定向落地成文件，例如：
//          ./your_replay_bin ...  > cts_debug.log 2>&1
//      再用 grep "CTS_DBG" cts_debug.log 过滤。
//
// CTS 输出链路（自上而下）总结：
//   1. 目标级筛选 (cts_risk_calc.cpp ValidObs / CheckAllLevel)：
//        - 目标有效性：fus_trkID>0、置信度、静止信号、目标年龄(age)、目标速度、
//          航向角区间、横向接近速度、来向(approach_side)、航向-速度方向偏差、
//          目标间遮挡/重叠、路径穿越校验(CalculateObsDuringObsToHost)。
//        - 区域/运动学：in_zone(检测多边形)、lat_ttc<ttc_thres、lgt_ttc>0(≥L4)、
//          radial_distance<rad_dist_thres、交叉点 intersect_x 落在 [min,max]。
//        - 确认帧：counter_val 连续超阈值 above_thres_cnt(自行车斜穿额外加帧)。
//        => 产出各 side 的 cur_level(经 ProcessThreatLevel 保持/迟滞)。
//   2. 驾驶员行为/公共抑制 (cts_state_machine.cpp CheckCommonInhibit/CheckDrvBehavior)：
//        - common_inhibit：方向盘转角/转角速率/曲率/制动踏板/油门/油门变化率超阈值。
//        - 持续转向、增大转向、自车持续减速、驾驶员低速制动意图（改变区域阈值）。
//   3. 状态机 (FCTA/FCTB/RCTA/RCTB)：由
//        state_off(软开关) / state_fault(诊断DID) / state_inhibit(车速/档位/AEB可用/
//        common_inhibit/freezing) / state_active(cur_level≥门限 或 保持窗口)
//        决定 OFF/FAULT/INHIBIT/STANDBY/ACTIVE。
//        进入 STANDBY 还要满足 standby_entry(车速区间 + 档位 D/R + AEB 可用)。
//   4. 输出装配 (FillOutput)：warn_state/brake_state==ACTIVE 且对应 side 有威胁时
//        才输出 warn/sound/brake_req；再受 GlobalConfig 的 shadowmode / cta_enable /
//        ctb_enable 掩掉。
//
// 本文件只“读取”上面各阶段已算好的中间量（存放在 m_debug 快照中），保证打印值与
// 实际决策 100% 一致，不重复计算、不改变行为。
// =============================================================================

namespace active_safety {
namespace cts {

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
    switch (s) {
        case static_cast<uint8_t>(CtsSwitch::OFF): name = "OFF"; break;
        case static_cast<uint8_t>(CtsSwitch::ONLY_WARING): name = "ONLY_WARN"; break;
        case static_cast<uint8_t>(CtsSwitch::WARING_BRAKE): name = "WARN_BRAKE"; break;
        default: name = "DEFAULT"; break;
    }
    return std::to_string(s) + ":" + name;
}

std::string StateName(CtsState s) {
    const char *name = nullptr;
    switch (s) {
        case CtsState::OFF: name = "OFF"; break;
        case CtsState::FAULT: name = "FAULT"; break;
        case CtsState::INHIBIT: name = "INHIBIT"; break;
        case CtsState::STANDBY: name = "STANDBY"; break;
        case CtsState::ACTIVE: name = "ACTIVE"; break;
        default: name = "UNK"; break;
    }
    return std::to_string(static_cast<int>(s)) + ":" + name;
}

std::string DirName(int d) {
    const char *name = nullptr;
    switch (d) {
        case 1: name = "Left"; break;
        case 2: name = "Right"; break;
        default: name = "None"; break;
    }
    return std::to_string(d) + ":" + name;
}

std::string OnOff(OnOffStatus s) {
    const char *name = (s == OnOffStatus::Active) ? "Active" : "NotActive";
    return std::to_string(static_cast<int>(s)) + ":" + name;
}

// 打印一个方向一侧关键目标的逐级判据(对应被删掉的 CheckAllLevel/ProcessThreatLevel cout)
void DumpTarget(std::ostream &os, const char *dir_tag, int side, const CtsTargetDebug &t) {
    if (!t.valid && t.cur_level == 0 && t.max_level == 0) {
        return; // 该侧本帧无关键目标且无保持，略过以减少输出
    }
    const char *side_tag = (side == 0) ? "L" : "R";
    os << "  [" << dir_tag << "-" << side_tag << "-TGT]"
       << " fusId=" << t.fus_trkID
       << " trk=" << t.track_id
       << " hdg=" << t.heading
       << " lat_posn=" << t.lat_posn
       << " long_posn=" << t.long_posn
       << " lat_vel=" << t.lat_vel
       << " long_vel=" << t.long_vel
       << " | max_level=" << t.max_level
       << " last_level=" << t.last_level
       << " cur_level=" << t.cur_level
       << " hold_cnt=" << t.hold_cnt
       << "\n";
    for (int k = 0; k < CTS_MAX_LEVEL; ++k) {
        const CtsLevelDebug &l = t.levels[k];
        os << "      k=" << k
           << " in_zone=" << l.in_zone
           << " | lat_ttc=" << l.lat_ttc << " ttc_thres=" << l.ttc_thres
           << " lgt_ttc=" << l.lgt_ttc << " ttc_chk=" << l.ttc_check
           << " | rad=" << l.radial_distance << " rad_thres=" << l.rad_dist_thres
           << " rad_chk=" << l.radial_dist_check
           << " | isec_x=" << l.intersect_x
           << " [" << l.inter_min << "," << l.inter_max << "]"
           << " x_chk=" << l.inter_x_check
           << " | cnt=" << l.counter_val << "/" << l.confirm_thres
           << " pass=" << l.level_passed
           << "\n";
    }
}

std::string ApproachSideName(uint8_t side) {
    const char *name = nullptr;
    switch (static_cast<ObsApproachSide>(side)) {
        case CTA_APPROACH_FROM_LEFT: name = "Left"; break;
        case CTA_APPROACH_FROM_RIGHT: name = "Right"; break;
        default: name = "Undefined"; break;
    }
    return std::to_string(side) + ":" + name;
}

void DumpInvalidReasons(std::ostream &os, uint32_t reasons) {
    struct ReasonName {
        uint32_t bit;
        const char *name;
    };
    const ReasonName reason_names[] = {
        {CTS_INVALID_NO_TRACK_ID, "NO_TRACK_ID"},
        {CTS_INVALID_LOW_CONFIDENCE, "LOW_CONFIDENCE"},
        {CTS_INVALID_STATIONARY, "STATIONARY"},
        {CTS_INVALID_AGE, "AGE"},
        {CTS_INVALID_SPEED, "SPEED"},
        {CTS_INVALID_HEADING_RANGE, "HEADING_RANGE"},
        {CTS_INVALID_LATERAL_APPROACH_SPEED, "LATERAL_APPROACH_SPEED"},
        {CTS_INVALID_APPROACH_SIDE, "APPROACH_SIDE"},
        {CTS_INVALID_HEADING_FILTER, "HEADING_FILTER"},
        {CTS_INVALID_OVERLAP, "OVERLAP"},
        {CTS_INVALID_TURNING, "TURNING"},
        {CTS_INVALID_VISIBLE_DIAGONAL, "VISIBLE_DIAGONAL"},
        {CTS_INVALID_HEADING_DEVIATION, "HEADING_DEVIATION"},
        {CTS_INVALID_PATH_CONFLICT, "PATH_CONFLICT"},
    };
    bool first = true;
    for (const ReasonName &reason : reason_names) {
        if ((reasons & reason.bit) == 0U) {
            continue;
        }
        if (!first) {
            os << '|';
        }
        os << reason.name;
        first = false;
    }
}

std::size_t DumpInvalidTargets(std::ostream &os, const char *dir_tag,
                               const std::array<CtsInvalidTargetDebug, kMaxNormalObject> &targets) {
    std::size_t invalid_count = 0;
    for (const CtsInvalidTargetDebug &target : targets) {
        // Empty obstacle slots have no target to diagnose; only print populated
        // targets that were rejected by one or more validity checks.
        if (!target.evaluated || target.reasons == 0U ||
            (target.fus_trkID <= 0 && target.track_id <= 0)) {
            continue;
        }
        ++invalid_count;
        os << "  [" << dir_tag << "-INVALID-TGT]"
           << " fusId=" << target.fus_trkID
           << " trk=" << target.track_id
           << " side=" << ApproachSideName(target.approach_side)
           << " age=" << target.age
           << " speed=" << target.speed
           << " hdg=" << target.heading
           << " lat_posn=" << target.lat_posn
           << " long_posn=" << target.long_posn
           << " lat_vel=" << target.lat_vel
           << " long_vel=" << target.long_vel
           << " lat_app_spd=" << target.lat_approach_speed
           << " angle_diff=" << target.angle_diff
           << " reasons=0x" << std::hex << target.reasons << std::dec << ':';
        DumpInvalidReasons(os, target.reasons);
        os << "\n";
    }
    return invalid_count;
}

// 打印单个子功能状态机的条件集合
void DumpFeature(std::ostream &os, const char *tag, const CtsFeatureDebug &f) {
    os << "  [" << tag << "]"
       << " sw=" << SwitchName(f.sw)
       << " spd=" << f.speed << " gear=" << GearName(f.gear)
       << " lvl(L/R)=" << f.level_side0 << "/" << f.level_side1
       << " | off=" << f.state_off
       << " fault=" << f.state_fault
       << " inhibit=" << f.state_inhibit
       << " active=" << f.state_active
       << " | standby_entry=" << f.standby_entry
       << " inhibit_cond=" << f.inhibit_cond
       << " raw_trig=" << f.raw_trigger
       << " max_time=" << f.max_time_reached
       << " freezing=" << f.freezing
       << " min_hold=" << f.min_hold_active
       << " keep_lowspd=" << f.keep_active_low_speed
       << "\n";
}

} // namespace

void CtsFunction::DumpDebugFrame(const AsVseOut &vse_out, const GlobalConfig &config) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(3);

    os << "==== CTS_DBG ts=" << vse_out.veh_time_stamp << " ====\n";

    // ---- 自车/驾驶员输入（决定抑制与区域阈值）----
    os << "  [EGO] spd=" << vse_out.speed
       << " gear=" << GearName(vse_out.actual_gear)
       << " str_ang=" << vse_out.steerwheelangle
       << " str_rate=" << vse_out.steerwheelangle_rate
       << " curvature=" << vse_out.rear_curvature
       << " long_acc=" << vse_out.long_accel
       << " brk_pdl=" << vse_out.brake_pedal_pos
       << " gas_pdl=" << vse_out.gas_pedal_pos
       << " gas_rate=" << vse_out.gas_pedal_pos_rate
       << " yawrate=" << vse_out.yawrate
       << " straight=" << vse_out.straight_driving
       << "\n";

    // ---- 开关 / 使能 / 诊断（全局门控）----
    os << "  [SW] fctb_switch=" << SwitchName(vse_out.fctb_switch)
       << " rctb_switch=" << SwitchName(vse_out.rctb_switch)
       << " did_config=0x" << std::hex << vse_out.function_did_config << std::dec
       << " | cta_enable=" << config.k_cta_enable
       << " ctb_enable=" << config.k_ctb_enable
       << " shadowmode=" << config.k_use_shadowmode
       << "\n";

    // ---- 驾驶员行为 / 公共抑制（跨功能共享）----
    os << "  [DRV] common_inhibit=" << m_debug.common_inhibit
       << " cont_steer=" << m_debug.drv_continues_steer
       << "(" << DirName(m_debug.drv_continues_str_dir) << ")"
       << " incr_steer=" << m_debug.drv_increase_steer
       << "(" << DirName(m_debug.drv_increase_str_dir) << ")"
       << " veh_decel=" << m_debug.veh_decel
       << " want_brake=" << m_debug.drv_want_brake
       << "\n";

    // ---- 四个子功能状态机的条件 ----
    DumpFeature(os, "FCTA", m_debug.fcta);
    DumpFeature(os, "FCTB", m_debug.fctb);
    DumpFeature(os, "RCTA", m_debug.rcta);
    DumpFeature(os, "RCTB", m_debug.rctb);

    // ---- 无效目标分析(目标筛选层，定位目标为何被 ValidObs 拒绝) ----
    const std::size_t front_invalid = DumpInvalidTargets(os, "FRONT", m_debug.invalid_target[0]);
    const std::size_t rear_invalid = DumpInvalidTargets(os, "REAR", m_debug.invalid_target[1]);
    os << "  [INVALID-TGT-SUMMARY] front=" << front_invalid
       << " rear=" << rear_invalid << "\n";

    // ---- 每侧关键目标逐级判据(目标筛选层，定位为何某目标未升级)----
    DumpTarget(os, "FRONT", 0, m_debug.target[0][0]);
    DumpTarget(os, "FRONT", 1, m_debug.target[0][1]);
    DumpTarget(os, "REAR", 0, m_debug.target[1][0]);
    DumpTarget(os, "REAR", 1, m_debug.target[1][1]);

    // ---- 最终输出（FillOutput 之后）----
    os << "  [OUT-FRONT] warn_state=" << StateName(m_front.warn_state)
       << " brake_state=" << StateName(m_front.brake_state)
       << " Lwarn=" << OnOff(m_front.left_warn)
       << " Rwarn=" << OnOff(m_front.right_warn)
       << " sound=" << OnOff(m_front.sound)
       << " brake_req=" << OnOff(m_front.brake_req)
       << " dec_req=" << m_front.brake_dec_req
       << " collision_dir=" << static_cast<int>(m_front.collision_dir)
       << "\n";
    os << "  [OUT-REAR ] warn_state=" << StateName(m_rear.warn_state)
       << " brake_state=" << StateName(m_rear.brake_state)
       << " Lwarn=" << OnOff(m_rear.left_warn)
       << " Rwarn=" << OnOff(m_rear.right_warn)
       << " sound=" << OnOff(m_rear.sound)
       << " brake_req=" << OnOff(m_rear.brake_req)
       << " dec_req=" << m_rear.brake_dec_req
       << " collision_dir=" << static_cast<int>(m_rear.collision_dir)
       << "\n";

    std::cout << os.str();
}

} // namespace cts
} // namespace active_safety
