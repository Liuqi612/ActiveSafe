#include "elk_debug_logger.h"

#include "ad_log/ad_log.hpp"

#include <cstddef>
#include <iomanip>
#include <sstream>
#include <string>

namespace active_safety {
namespace elk {
namespace {

struct BitDesc {
    uint8_t bit;
    const char *desc;
};

const char *StateName(ElkStateMachine::State state)
{
    switch (state) {
        case ElkStateMachine::State::Fault: return "Fault";
        case ElkStateMachine::State::Off: return "Off";
        case ElkStateMachine::State::Standby: return "Standby";
        case ElkStateMachine::State::Enable: return "Enable";
        case ElkStateMachine::State::Left_Intervention: return "Left_Intervention";
        case ElkStateMachine::State::Right_Intervention: return "Right_Intervention";
        case ElkStateMachine::State::Completed: return "Completed";
        case ElkStateMachine::State::Abort: return "Abort";
        case ElkStateMachine::State::Left_Suppressed: return "Left_Suppressed";
        case ElkStateMachine::State::Right_Suppressed: return "Right_Suppressed";
        default: return "Unknown";
    }
}

std::string DescribeBits(uint64_t mask, const BitDesc *descs, std::size_t count)
{
    std::ostringstream oss;
    bool first = true;
    for (std::size_t i = 0U; i < count; ++i) {
        if ((mask & (1ULL << descs[i].bit)) == 0ULL) {
            continue;
        }
        if (!first) {
            oss << "|";
        }
        oss << "bit" << static_cast<int>(descs[i].bit) << ":" << descs[i].desc;
        first = false;
    }
    if (first) {
        return "无";
    }
    return oss.str();
}

std::string DescribeActiveSource(uint8_t mask)
{
    static const BitDesc kActiveSourceDesc[] = {
        {0U, "实线(SLD)"},
        {1U, "路沿(ROR)"},
        {2U, "对向目标(OC)"},
        {3U, "超越目标(OT)"},
    };
    return DescribeBits(mask, kActiveSourceDesc, sizeof(kActiveSourceDesc) / sizeof(kActiveSourceDesc[0]));
}

std::string DescribeStandbyMask(uint16_t mask)
{
    static const BitDesc kStandbyDesc[] = {
        {0U, "车速有效"},
        {1U, "曲率有效"},
        {2U, "最小车道宽有效"},
        {3U, "最大车道宽有效"},
        {4U, "左车道线成熟"},
        {5U, "右车道线成熟"},
        {6U, "左路沿成熟"},
        {7U, "右路沿成熟"},
        {8U, "横摆角速度未抑制"},
        {9U, "诊断未抑制"},
    };
    return DescribeBits(mask, kStandbyDesc, sizeof(kStandbyDesc) / sizeof(kStandbyDesc[0]));
}

std::string DescribeDiagMask(uint32_t mask)
{
    static const BitDesc kDiagDesc[] = {
        {0U, "档位不在D档"},
        {1U, "AEB激活"},
        {2U, "EPS不可用或故障"},
        {3U, "胎压报警"},
        {4U, "车门打开"},
        {5U, "引擎盖或后备箱打开"},
        {6U, "安全带解开"},
        {7U, "ESC激活"},
        {8U, "ABS激活"},
        {9U, "TCS激活"},
        {10U, "车辆碰撞"},
        {11U, "雨刮快速档"},
        {12U, "EPB拉起"},
        {13U, "脱手"},
    };
    return DescribeBits(mask, kDiagDesc, sizeof(kDiagDesc) / sizeof(kDiagDesc[0]));
}

std::string DescribeEvpMask(uint32_t mask)
{
    static const BitDesc kEvpDesc[] = {
        {0U, "横摆角速度抑制"},
        {1U, "制动踏板抑制"},
        {2U, "加速踏板抑制"},
        {3U, "横向加速度抑制"},
        {4U, "纵向加速度抑制"},
        {5U, "纵向减速度抑制"},
        {6U, "方向盘手力矩抑制"},
        {7U, "方向盘角度抑制"},
        {8U, "方向盘角速度抑制"},
        {9U, "双闪抑制"},
        {10U, "左偏离车道线速度抑制"},
        {11U, "左偏离路沿速度抑制"},
        {12U, "左转向灯抑制"},
        {13U, "右偏离车道线速度抑制"},
        {14U, "右偏离路沿速度抑制"},
        {15U, "右转向灯抑制"},
        {16U, "左车道线无效"},
        {17U, "左跃出车道线"},
        {18U, "左路沿无效"},
        {19U, "左跃出车道"},
        {20U, "左路沿长度无效"},
        {21U, "右车道线无效"},
        {22U, "右跃出车道线"},
        {23U, "右路沿无效"},
        {24U, "右跃出车道"},
        {25U, "右路沿长度无效"},
        {26U, "两次激活间隔小于6s"},
        {27U, "左侧激活超时"},
        {28U, "右侧激活超时"},
    };
    return DescribeBits(mask, kEvpDesc, sizeof(kEvpDesc) / sizeof(kEvpDesc[0]));
}

std::string DescribeObjectInterventionMask(uint8_t mask)
{
    static const BitDesc kDesc[] = {
        {0U, "无变道"},
        {1U, "TTLC满足"},
        {2U, "距离稳定"},
        {3U, "车道线有效"},
        {4U, "目标威胁"},
    };
    return DescribeBits(mask, kDesc, sizeof(kDesc) / sizeof(kDesc[0]));
}

std::string DescribeEdgeInterventionMask(uint8_t mask)
{
    static const BitDesc kDesc[] = {
        {0U, "未runOffRoad"},
        {1U, "TTLC满足"},
        {2U, "距离稳定"},
        {3U, "路沿有效"},
        {4U, "可视距离有效"},
    };
    return DescribeBits(mask, kDesc, sizeof(kDesc) / sizeof(kDesc[0]));
}

std::string DescribeSolidInterventionMask(uint8_t mask)
{
    static const BitDesc kDesc[] = {
        {0U, "无本侧变道"},
        {1U, "TTLC满足"},
        {2U, "距离稳定"},
        {3U, "车道线有效"},
        {4U, "可视距离有效"},
        {5U, "实线类型有效"},
    };
    return DescribeBits(mask, kDesc, sizeof(kDesc) / sizeof(kDesc[0]));
}

std::string DescribeFalseTriggerBus(uint64_t mask)
{
    static const BitDesc kFalseTriggerDesc[] = {
        {0U, "左车道线跳变"},
        {1U, "右车道线跳变"},
        {2U, "左路沿跳变"},
        {3U, "右路沿跳变"},
        {4U, "左车道线可视距离过短"},
        {5U, "右车道线可视距离过短"},
        {6U, "左路沿可视距离过短"},
        {7U, "右路沿可视距离过短"},
        {8U, "左路沿与车道线不匹配"},
        {9U, "右路沿与车道线不匹配"},
        {10U, "LCT左TTC历史不稳定"},
        {11U, "LCT右TTC历史不稳定"},
        {12U, "ROR左TTC历史不稳定"},
        {13U, "ROR右TTC历史不稳定"},
        {14U, "SLD左TTC历史不稳定"},
        {15U, "SLD右TTC历史不稳定"},
        {16U, "LCT左低速阈值收紧导致未触发"},
        {17U, "LCT右低速阈值收紧导致未触发"},
        {18U, "ROR左低速阈值收紧导致未触发"},
        {19U, "ROR右低速阈值收紧导致未触发"},
        {20U, "SLD左低速阈值收紧导致未触发"},
        {21U, "SLD右低速阈值收紧导致未触发"},
        {22U, "LCT左TTC短时无效"},
        {23U, "LCT右TTC短时无效"},
        {24U, "ROR左TTC短时无效"},
        {25U, "ROR右TTC短时无效"},
        {26U, "SLD左TTC短时无效"},
        {27U, "SLD右TTC短时无效"},
        {28U, "方向盘手力矩/override历史抑制"},
        {29U, "低速油门踏板抑制"},
        {30U, "综合驾驶员主观接管意图"},
    };
    return DescribeBits(mask, kFalseTriggerDesc, sizeof(kFalseTriggerDesc) / sizeof(kFalseTriggerDesc[0]));
}

void AppendBool(std::ostringstream &oss, const char *key, bool value)
{
    oss << key << "=" << (value ? 1 : 0) << ";";
}

void AppendTtcSignal(std::ostringstream &oss,
                     const char *prefix,
                     const ElkScenarioDecision::TtcDebugSignal &signal)
{
    oss << prefix << "_ttlc=" << signal.ttlc << ";"
        << prefix << "_dist=" << signal.distance << ";"
        << prefix << "_thr=" << signal.threshold << ";"
        << prefix << "_nominal_thr=" << signal.nominal_threshold << ";";
    AppendBool(oss, (std::string(prefix) + "_history_enabled").c_str(), signal.history_enabled);
    AppendBool(oss, (std::string(prefix) + "_low_lat_rate_near").c_str(), signal.low_lat_rate_near);
    AppendBool(oss, (std::string(prefix) + "_stable_departure").c_str(), signal.stable_departure);
}

void AppendObjSl(std::ostringstream &oss, const char *prefix, const ElkObjSl &sl)
{
    oss << prefix << "_sl_x=" << sl.x << ";"
        << prefix << "_sl_y=" << sl.y << ";"
        << prefix << "_s=" << sl.s << ";"
        << prefix << "_l=" << sl.l << ";"
        << prefix << "_vs=" << sl.vs << ";"
        << prefix << "_vl=" << sl.vl << ";"
        << prefix << "_as=" << sl.as << ";"
        << prefix << "_al=" << sl.al << ";"
        << prefix << "_ttc_s=" << sl.ttc_s << ";"
        << prefix << "_ttc_l=" << sl.ttc_l << ";";
    AppendBool(oss, (std::string(prefix) + "_threat").c_str(), sl.threat);
}

void AppendOcMotionGuard(std::ostringstream &oss, const char *prefix, const ElkOcMotionGuardDebug &debug)
{
    oss << prefix << "_guard_long_vel=" << debug.long_vel << ";"
        << prefix << "_guard_min_oncoming_speed=" << debug.min_oncoming_speed << ";"
        << prefix << "_guard_heading_abs=" << debug.heading_abs << ";"
        << prefix << "_guard_heading_thr=" << debug.heading_threshold << ";"
        << prefix << "_guard_f_oncoming=" << static_cast<int>(debug.f_oncoming) << ";"
        << prefix << "_guard_movement=" << static_cast<int>(debug.movement) << ";";
    AppendBool(oss, (std::string(prefix) + "_guard_speed_valid").c_str(), debug.speed_valid);
    AppendBool(oss, (std::string(prefix) + "_guard_f_oncoming_valid").c_str(), debug.f_oncoming_valid);
    AppendBool(oss, (std::string(prefix) + "_guard_movement_valid").c_str(), debug.movement_valid);
    AppendBool(oss, (std::string(prefix) + "_guard_heading_valid").c_str(), debug.heading_valid);
    AppendBool(oss, (std::string(prefix) + "_guard_motion_valid").c_str(), debug.motion_valid);
    AppendBool(oss, (std::string(prefix) + "_collision_consistent").c_str(), debug.collision_consistent);
}

void AppendOncomingTarget(std::ostringstream &oss,
                          const char *prefix,
                          const AsOnComingObject &obj,
                          const ElkObjSl &sl,
                          const ElkOcMotionGuardDebug &debug)
{
    oss << prefix << "_track_id=" << static_cast<int>(obj.track_id) << ";"
        << prefix << "_object_class=" << static_cast<int>(obj.object_class) << ";"
        << prefix << "_vcs_long_posn=" << obj.vcs_long_posn << ";"
        << prefix << "_vcs_lat_posn=" << obj.vcs_lat_posn << ";"
        << prefix << "_vcs_long_vel=" << obj.vcs_long_vel << ";"
        << prefix << "_vcs_lat_vel=" << obj.vcs_lat_vel << ";"
        << prefix << "_vcs_long_accel=" << obj.vcs_long_accel << ";"
        << prefix << "_vcs_lat_accel=" << obj.vcs_lat_accel << ";"
        << prefix << "_width=" << obj.width << ";"
        << prefix << "_length=" << obj.length << ";";
    AppendObjSl(oss, prefix, sl);
    AppendOcMotionGuard(oss, prefix, debug);
}

void AppendOvertakingTarget(std::ostringstream &oss,
                            const char *prefix,
                            const AsOverTakingObject &obj,
                            const ElkObjSl &sl,
                            bool collisionConsistent,
                            bool constVelModel)
{
    oss << prefix << "_track_id=" << static_cast<int>(obj.track_id) << ";"
        << prefix << "_object_class=" << static_cast<int>(obj.object_class) << ";"
        << prefix << "_vcs_long_posn=" << obj.vcs_long_posn << ";"
        << prefix << "_vcs_lat_posn=" << obj.vcs_lat_posn << ";"
        << prefix << "_vcs_long_vel=" << obj.vcs_long_vel << ";"
        << prefix << "_vcs_lat_vel=" << obj.vcs_lat_vel << ";"
        << prefix << "_vcs_long_accel=" << obj.vcs_long_accel << ";"
        << prefix << "_vcs_lat_accel=" << obj.vcs_lat_accel << ";"
        << prefix << "_width=" << obj.width << ";"
        << prefix << "_length=" << obj.length << ";";
    AppendObjSl(oss, prefix, sl);
    AppendBool(oss, (std::string(prefix) + "_collision_consistent").c_str(), collisionConsistent);
    AppendBool(oss, (std::string(prefix) + "_large_rear_const_vel_model").c_str(), constVelModel);
}

} // namespace

uint64_t BuildBoundaryFalseTriggerDebugBus(const LaneBoundaryParameters &lane_boundary)
{
    uint64_t debug_bus = 0ULL;
    if (lane_boundary.lftBdryJump) debug_bus |= (1ULL << 0U);
    if (lane_boundary.rgtBdryJump) debug_bus |= (1ULL << 1U);
    if (lane_boundary.lftEdgeJump) debug_bus |= (1ULL << 2U);
    if (lane_boundary.rgtEdgeJump) debug_bus |= (1ULL << 3U);
    if (lane_boundary.lftBdryRangeShort) debug_bus |= (1ULL << 4U);
    if (lane_boundary.rgtBdryRangeShort) debug_bus |= (1ULL << 5U);
    if (lane_boundary.lftEdgeRangeShort) debug_bus |= (1ULL << 6U);
    if (lane_boundary.rgtEdgeRangeShort) debug_bus |= (1ULL << 7U);
    if (lane_boundary.lftEdgeLaneMismatch) debug_bus |= (1ULL << 8U);
    if (lane_boundary.rgtEdgeLaneMismatch) debug_bus |= (1ULL << 9U);
    return debug_bus;
}

void LogElkFrame(const AsVseOut &vse_out,
                 const LanesInfo &road_info,
                 const GlobalConfig &config,
                 const LaneBoundaryParameters &lane_boundary,
                 const LaneCenterParameters &lane_center,
                 const ElkTaSl &ta_info,
                 const ElkThreatDebugSnapshot &threat_debug,
                 const AsOnComingOut &oncoming_out,
                 const AsOverTakingOut &overtaking_out,
                 const ElkStateMachine &state_machine,
                 uint8_t rolling_counter)
{
    if (!config.k_ELK_DebugLogEnable) {
        return;
    }

    const uint64_t false_trigger_debug_bus =
        BuildBoundaryFalseTriggerDebugBus(lane_boundary) | state_machine.getFalseTriggerDebugMask();
    const auto state = state_machine.getCurrentState();
    const auto &ttc_debug = state_machine.getTtcDebugSnapshot();

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "ELK_DEBUG;"
        << "rolling_counter=" << static_cast<int>(rolling_counter) << ";"
        << "state=" << static_cast<int>(state) << ";"
        << "state_name=" << StateName(state) << ";"
        << "standby_enable_mask=" << state_machine.getStandbyEnableMask() << ";"
        << "standby_enable_desc=" << DescribeStandbyMask(state_machine.getStandbyEnableMask()) << ";"
        << "diag_inhibit_mask=" << state_machine.getDiagInhabitMask() << ";"
        << "diag_inhibit_desc=" << DescribeDiagMask(state_machine.getDiagInhabitMask()) << ";"
        << "evp_disable_mask=" << state_machine.getEvpDisableMask() << ";"
        << "evp_disable_desc=" << DescribeEvpMask(state_machine.getEvpDisableMask()) << ";"
        << "left_active_source=" << static_cast<int>(state_machine.getLeftDebugActiveSourceMask()) << ";"
        << "left_active_source_desc=" << DescribeActiveSource(state_machine.getLeftDebugActiveSourceMask()) << ";"
        << "right_active_source=" << static_cast<int>(state_machine.getRightDebugActiveSourceMask()) << ";"
        << "right_active_source_desc=" << DescribeActiveSource(state_machine.getRightDebugActiveSourceMask()) << ";"
        << "left_lct_intervention_mask=" << static_cast<int>(state_machine.getLeftInterventionMask()) << ";"
        << "left_lct_intervention_desc=" << DescribeObjectInterventionMask(state_machine.getLeftInterventionMask()) << ";"
        << "right_lct_intervention_mask=" << static_cast<int>(state_machine.getRightInterventionMask()) << ";"
        << "right_lct_intervention_desc=" << DescribeObjectInterventionMask(state_machine.getRightInterventionMask()) << ";"
        << "left_ror_intervention_mask=" << static_cast<int>(state_machine.getLeftEdgeInterventionMask()) << ";"
        << "left_ror_intervention_desc=" << DescribeEdgeInterventionMask(state_machine.getLeftEdgeInterventionMask()) << ";"
        << "right_ror_intervention_mask=" << static_cast<int>(state_machine.getRightEdgeInterventionMask()) << ";"
        << "right_ror_intervention_desc=" << DescribeEdgeInterventionMask(state_machine.getRightEdgeInterventionMask()) << ";"
        << "left_sld_intervention_mask=" << static_cast<int>(state_machine.getLeftSolidInterventionMask()) << ";"
        << "left_sld_intervention_desc=" << DescribeSolidInterventionMask(state_machine.getLeftSolidInterventionMask()) << ";"
        << "right_sld_intervention_mask=" << static_cast<int>(state_machine.getRightSolidInterventionMask()) << ";"
        << "right_sld_intervention_desc=" << DescribeSolidInterventionMask(state_machine.getRightSolidInterventionMask()) << ";"
        << "left_suppression_mask=" << state_machine.getLeftSuppressionMask() << ";"
        << "left_suppression_desc=" << DescribeEvpMask(state_machine.getLeftSuppressionMask()) << ";"
        << "right_suppression_mask=" << state_machine.getRightSuppressionMask() << ";"
        << "right_suppression_desc=" << DescribeEvpMask(state_machine.getRightSuppressionMask()) << ";"
        << "false_trigger_debug_bus=" << false_trigger_debug_bus << ";"
        << "false_trigger_desc=" << DescribeFalseTriggerBus(false_trigger_debug_bus) << ";";

    AppendTtcSignal(oss, "lct_left", ttc_debug.left_lct);
    AppendTtcSignal(oss, "lct_right", ttc_debug.right_lct);
    AppendTtcSignal(oss, "ror_left", ttc_debug.left_ror);
    AppendTtcSignal(oss, "ror_right", ttc_debug.right_ror);
    AppendTtcSignal(oss, "sld_left", ttc_debug.left_sld);
    AppendTtcSignal(oss, "sld_right", ttc_debug.right_sld);

    oss << "left_marker_valid=" << lane_boundary.lftBdryVld << ";"
        << "right_marker_valid=" << lane_boundary.rgtBdryVld << ";"
        << "left_edge_valid=" << lane_boundary.lftEdgeVld << ";"
        << "right_edge_valid=" << lane_boundary.rgtEdgeVld << ";"
        << "left_marker_jump=" << lane_boundary.lftBdryJump << ";"
        << "right_marker_jump=" << lane_boundary.rgtBdryJump << ";"
        << "left_edge_jump=" << lane_boundary.lftEdgeJump << ";"
        << "right_edge_jump=" << lane_boundary.rgtEdgeJump << ";"
        << "left_marker_range_short=" << lane_boundary.lftBdryRangeShort << ";"
        << "right_marker_range_short=" << lane_boundary.rgtBdryRangeShort << ";"
        << "left_edge_range_short=" << lane_boundary.lftEdgeRangeShort << ";"
        << "right_edge_range_short=" << lane_boundary.rgtEdgeRangeShort << ";"
        << "left_edge_lane_mismatch=" << lane_boundary.lftEdgeLaneMismatch << ";"
        << "right_edge_lane_mismatch=" << lane_boundary.rgtEdgeLaneMismatch << ";"
        << "left_lane_change=" << lane_boundary.lftLaneChange << ";"
        << "right_lane_change=" << lane_boundary.rgtLaneChange << ";"
        << "left_run_off_road=" << lane_boundary.runOffRoadLft << ";"
        << "right_run_off_road=" << lane_boundary.runOffRoadRgt << ";"
        << "left_marker_lat_rate=" << lane_boundary.lftBdryLatRt << ";"
        << "right_marker_lat_rate=" << lane_boundary.rgtBdryLatRt << ";"
        << "left_edge_lat_rate=" << lane_boundary.lftEdgeLatRt << ";"
        << "right_edge_lat_rate=" << lane_boundary.rgtEdgeLatRt << ";"
        << "left_marker_curv=" << lane_boundary.lftBdryCurv << ";"
        << "right_marker_curv=" << lane_boundary.rgtBdryCurv << ";"
        << "left_edge_curv=" << lane_boundary.lftEdgeCurv << ";"
        << "right_edge_curv=" << lane_boundary.rgtEdgeCurv << ";"
        << "left_curv_offset_marker=" << state_machine.getLeftCurvOffsetMarker() << ";"
        << "right_curv_offset_marker=" << state_machine.getRightCurvOffsetMarker() << ";"
        << "left_curv_offset_edge=" << state_machine.getLeftCurvOffsetEdge() << ";"
        << "right_curv_offset_edge=" << state_machine.getRightCurvOffsetEdge() << ";"
        << "lane_center_valid=" << lane_center.vld << ";"
        << "lane_center_c0=" << lane_center.c0 << ";"
        << "lane_center_c1=" << lane_center.c1 << ";"
        << "left_marker_type=" << static_cast<int>(road_info.HostLeftLaneMarker.LineType) << ";"
        << "right_marker_type=" << static_cast<int>(road_info.HostRightLaneMarker.LineType) << ";";

    AppendOncomingTarget(oss, "oc_left", oncoming_out.oncom_target_1, ta_info.oncoming_front_left,
                         threat_debug.left_oc_motion_guard);
    AppendOncomingTarget(oss, "oc_right", oncoming_out.oncom_target_2, ta_info.oncoming_front_right,
                         threat_debug.right_oc_motion_guard);
    AppendOvertakingTarget(oss, "ot_rear_left", overtaking_out.overtake_target_rear_left,
                           ta_info.overtaking_rear_left,
                           threat_debug.left_ot_collision_consistent,
                           threat_debug.left_ot_const_vel_model);
    AppendOvertakingTarget(oss, "ot_rear_right", overtaking_out.overtake_target_rear_right,
                           ta_info.overtaking_rear_right,
                           threat_debug.right_ot_collision_consistent,
                           threat_debug.right_ot_const_vel_model);

    oss << "ego_s=" << ta_info.ego.s << ";"
        << "ego_l=" << ta_info.ego.l << ";"
        << "ego_vs=" << ta_info.ego.vs << ";"
        << "ego_vl=" << ta_info.ego.vl << ";"
        << "ego_as=" << ta_info.ego.as << ";"
        << "ego_al=" << ta_info.ego.al << ";"
        << "torsion_bar_trq=" << vse_out.torsion_bar_trq << ";"
        << "gas_pedal_pos=" << vse_out.gas_pedal_pos << ";"
        << "brake_pedal_pos=" << vse_out.brake_pedal_pos << ";"
        << "brake_pedal_apld=" << vse_out.brake_pedal_apld << ";"
        << "turn_light_switch_pos=" << static_cast<int>(vse_out.turn_light_switch_pos) << ";"
        << "hazard_lamp_st=" << static_cast<int>(vse_out.hazard_lamp_st) << ";";

    AD_LERROR(ElkDebug) << oss.str();
}

} // namespace elk
} // namespace active_safety
