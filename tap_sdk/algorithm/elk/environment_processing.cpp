#include "environment_processing.h"

#include <cmath>

namespace active_safety {
namespace elk {

EnvironmentProcessing::EnvironmentProcessing() {
    lane_marker_boundary_parms_.laneWidth = 3.6F;
    his_env_info_.lftC0 = 0.5F * lane_marker_boundary_parms_.laneWidth;
    his_env_info_.rgtC0 = -0.5F * lane_marker_boundary_parms_.laneWidth;
}

void EnvironmentProcessing::Update(const AsVseOut &vse_out, const LanesInfo &road_info)
{
    getLaneMarkerBoundaryParameters(vse_out, road_info, vse_out.config);
    getRoadEdgeBoundaryParameters(vse_out, road_info, vse_out.config);
    detectLaneChangeBoundary(road_info);
    updateBoundaryQualityStatus(road_info);
    getLaneCenterParameters(road_info);
    updateBoundaryHistory(road_info);
}

void EnvironmentProcessing::getLaneMarkerBoundaryParameters(const AsVseOut &vse_out, const LanesInfo &road_info, const VehicleConfig &veh_config)
{
    float a0, a1, a2, a3;
    float wheel_base, half_width;
    float wb2, wb3, hdg_rad;
    // bool left_valid_lst, right_valid_lst;

    wheel_base = veh_config.k_wheel_base;
    half_width = 0.5F * veh_config.k_host_width;
    wb2 = wheel_base * wheel_base;
    wb3 = wb2 * wheel_base;

    a0 = road_info.HostLeftLaneMarker.LinePolyC0
        + road_info.HostLeftLaneMarker.LinePolyC1 * wheel_base
        + road_info.HostLeftLaneMarker.LinePolyC2 * wb2
        + road_info.HostLeftLaneMarker.LinePolyC3 * wb3;
    
    a1 = road_info.HostLeftLaneMarker.LinePolyC1
        + 2 * road_info.HostLeftLaneMarker.LinePolyC2 * wheel_base
        + 3 * road_info.HostLeftLaneMarker.LinePolyC3 * wb2;
    
    a2 = road_info.HostLeftLaneMarker.LinePolyC2
        + 3 * road_info.HostLeftLaneMarker.LinePolyC3 * wheel_base;
    
    a3 = road_info.HostLeftLaneMarker.LinePolyC3;
    
    lane_marker_boundary_parms_.lftBdryVld = road_info.HostLeftLaneMarker.LineConf > 0;
    if (lane_marker_boundary_parms_.lftBdryVld) {
        lane_marker_boundary_parms_.curLftDisToBdry = a0 - half_width;
        hdg_rad = atan2f(-a1, 1);
        lane_marker_boundary_parms_.lftBdryHdgDeg = hdg_rad * 180/ M_PI; // 正值代表车头朝左
        lane_marker_boundary_parms_.lftBdryLatRt = vse_out.speed * sin(hdg_rad); // 正值代表向左压线偏离
        lane_marker_boundary_parms_.lftBdryCurv = 2 * a2;
        lane_marker_boundary_parms_.lftBdryCurvRt = a3;
        lane_marker_boundary_parms_.lftBdryTtlc = math::Clamp(math::SafeDivide(lane_marker_boundary_parms_.curLftDisToBdry, 
            std::max(lane_marker_boundary_parms_.lftBdryLatRt, 0.001F)), 
            0.0F, 10.0F);
    } else {
        lane_marker_boundary_parms_.curLftDisToBdry = 1.0F;
        lane_marker_boundary_parms_.lftBdryHdgDeg = 0.0F;
        lane_marker_boundary_parms_.lftBdryLatRt = 0.0;
        lane_marker_boundary_parms_.lftBdryCurv = 0.0;
        lane_marker_boundary_parms_.lftBdryCurvRt = 0.0;
        lane_marker_boundary_parms_.lftBdryTtlc = 10.0;
    }

    a0 = road_info.HostRightLaneMarker.LinePolyC0
        + road_info.HostRightLaneMarker.LinePolyC1 * wheel_base
        + road_info.HostRightLaneMarker.LinePolyC2 * wb2
        + road_info.HostRightLaneMarker.LinePolyC3 * wb3;
    
    a1 = road_info.HostRightLaneMarker.LinePolyC1
        + 2 * road_info.HostRightLaneMarker.LinePolyC2 * wheel_base
        + 3 * road_info.HostRightLaneMarker.LinePolyC3 * wb2;
    
    a2 = road_info.HostRightLaneMarker.LinePolyC2
        + 3 * road_info.HostRightLaneMarker.LinePolyC3 * wheel_base;
    
    a3 = road_info.HostRightLaneMarker.LinePolyC3;
    
    lane_marker_boundary_parms_.rgtBdryVld = road_info.HostRightLaneMarker.LineConf > 0;
    if (lane_marker_boundary_parms_.rgtBdryVld) {
        lane_marker_boundary_parms_.curRgtDisToBdry = -a0 - half_width;
        hdg_rad = atan2f(-a1, 1);
        lane_marker_boundary_parms_.rgtBdryHdgDeg = hdg_rad * 180/ M_PI; // 负值代表车头朝右
        lane_marker_boundary_parms_.rgtBdryLatRt = vse_out.speed * sin(hdg_rad); // 负值代表向右压线偏离
        lane_marker_boundary_parms_.rgtBdryCurv = 2 * a2;
        lane_marker_boundary_parms_.rgtBdryCurvRt = a3;
        lane_marker_boundary_parms_.rgtBdryTtlc = math::Clamp(math::SafeDivide(lane_marker_boundary_parms_.curRgtDisToBdry, 
            std::max(-lane_marker_boundary_parms_.rgtBdryLatRt, 0.001F)), 
            0.0F, 10.0F);
    } else {
        lane_marker_boundary_parms_.curRgtDisToBdry = 1.0F;
        lane_marker_boundary_parms_.rgtBdryHdgDeg = 0.0F;
        lane_marker_boundary_parms_.rgtBdryLatRt = 0.0;
        lane_marker_boundary_parms_.rgtBdryCurv = 0.0;
        lane_marker_boundary_parms_.rgtBdryCurvRt = 0.0;
        lane_marker_boundary_parms_.rgtBdryTtlc = 10.0;
    }

    if (lane_marker_boundary_parms_.lftBdryVld && lane_marker_boundary_parms_.rgtBdryVld) {
        lane_marker_boundary_parms_.laneWidth = road_info.HostLeftLaneMarker.LinePolyC0 - road_info.HostRightLaneMarker.LinePolyC0;
    }

}

void EnvironmentProcessing::getRoadEdgeBoundaryParameters(const AsVseOut &vse_out, const LanesInfo &road_info, const VehicleConfig &veh_config)
{
    float a0, a1, a2, a3;
    float wheel_base, half_width;
    float wb2, wb3, hdg_rad;
    const float k_EP_offset_for_LC = -1.5F;
    const float k_EP_LC_hold_duration = 0.3F;

    wheel_base = veh_config.k_wheel_base;
    half_width = 0.5F * veh_config.k_host_width;
    wb2 = wheel_base * wheel_base;
    wb3 = wb2 * wheel_base;

    a0 = road_info.LeftRoadEdge.LinePolyC0
        + road_info.LeftRoadEdge.LinePolyC1 * wheel_base
        + road_info.LeftRoadEdge.LinePolyC2 * wb2
        + road_info.LeftRoadEdge.LinePolyC3 * wb3;
    
    a1 = road_info.LeftRoadEdge.LinePolyC1
        + 2 * road_info.LeftRoadEdge.LinePolyC2 * wheel_base
        + 3 * road_info.LeftRoadEdge.LinePolyC3 * wb2;
    
    a2 = road_info.LeftRoadEdge.LinePolyC2
        + 3 * road_info.LeftRoadEdge.LinePolyC3 * wheel_base;
    
    a3 = road_info.LeftRoadEdge.LinePolyC3;
    
    lane_marker_boundary_parms_.lftEdgeVld = road_info.LeftRoadEdge.LineConf > 0;
    if (lane_marker_boundary_parms_.lftEdgeVld) {
        lane_marker_boundary_parms_.curLftDisToEdge = a0 - half_width;
        hdg_rad = atan2f(-a1, 1);
        lane_marker_boundary_parms_.lftEdgeHdgDeg = hdg_rad * 180/ M_PI; // 正值代表车头朝左
        lane_marker_boundary_parms_.lftEdgeLatRt = vse_out.speed * sin(hdg_rad); // 正值代表向左压线偏离
        lane_marker_boundary_parms_.lftEdgeCurv = 2 * a2;
        lane_marker_boundary_parms_.lftEdgeCurvRt = a3;
        lane_marker_boundary_parms_.lftEdgeTtlc = math::Clamp(math::SafeDivide(lane_marker_boundary_parms_.curLftDisToEdge, 
            std::max(lane_marker_boundary_parms_.lftEdgeLatRt, 0.001F)), 
            0.0F, 10.0F);
    } else {
        lane_marker_boundary_parms_.curLftDisToEdge = 1.0F;
        lane_marker_boundary_parms_.lftEdgeHdgDeg = 0.0F;
        lane_marker_boundary_parms_.lftEdgeLatRt = 0.0;
        lane_marker_boundary_parms_.lftEdgeCurv = 0.0;
        lane_marker_boundary_parms_.lftEdgeCurvRt = 0.0;
        lane_marker_boundary_parms_.lftEdgeTtlc = 10.0;
    }

    a0 = road_info.RightRoadEdge.LinePolyC0
        + road_info.RightRoadEdge.LinePolyC1 * wheel_base
        + road_info.RightRoadEdge.LinePolyC2 * wb2
        + road_info.RightRoadEdge.LinePolyC3 * wb3;
    
    a1 = road_info.RightRoadEdge.LinePolyC1
        + 2 * road_info.RightRoadEdge.LinePolyC2 * wheel_base
        + 3 * road_info.RightRoadEdge.LinePolyC3 * wb2;
    
    a2 = road_info.RightRoadEdge.LinePolyC2
        + 3 * road_info.RightRoadEdge.LinePolyC3 * wheel_base;
    
    a3 = road_info.RightRoadEdge.LinePolyC3;
    
    lane_marker_boundary_parms_.rgtEdgeVld = road_info.RightRoadEdge.LineConf > 0;
    if (lane_marker_boundary_parms_.rgtEdgeVld) {
        lane_marker_boundary_parms_.curRgtDisToEdge = -a0 - half_width;
        hdg_rad = atan2f(-a1, 1);
        lane_marker_boundary_parms_.rgtEdgeHdgDeg = hdg_rad * 180/ M_PI; // 负值代表车头朝右
        lane_marker_boundary_parms_.rgtEdgeLatRt = vse_out.speed * sin(hdg_rad); // 负值代表向右压线偏离
        lane_marker_boundary_parms_.rgtEdgeCurv = 2 * a2;
        lane_marker_boundary_parms_.rgtEdgeCurvRt = a3;
        lane_marker_boundary_parms_.rgtEdgeTtlc = math::Clamp(math::SafeDivide(lane_marker_boundary_parms_.curRgtDisToEdge, 
            std::max(-lane_marker_boundary_parms_.rgtEdgeLatRt, 0.001F)), 
            0.0F, 10.0F);
    } else {
        lane_marker_boundary_parms_.curRgtDisToEdge = 1.0F;
        lane_marker_boundary_parms_.rgtEdgeHdgDeg = 0.0F;
        lane_marker_boundary_parms_.rgtEdgeLatRt = 0.0;
        lane_marker_boundary_parms_.rgtEdgeCurv = 0.0;
        lane_marker_boundary_parms_.rgtEdgeCurvRt = 0.0;
        lane_marker_boundary_parms_.rgtEdgeTtlc = 10.0;
    }

    lane_marker_boundary_parms_.runOffRoadLft = left_run_off_road_.signalHold(
        lane_marker_boundary_parms_.curLftDisToEdge < k_EP_offset_for_LC && 
        lane_marker_boundary_parms_.lftEdgeVld && 
        !lane_marker_boundary_parms_.rgtEdgeVld,
        k_EP_LC_hold_duration, 0.02F);
    
    lane_marker_boundary_parms_.runOffRoadRgt = right_run_off_road_.signalHold(
        lane_marker_boundary_parms_.curRgtDisToEdge < k_EP_offset_for_LC && 
        !lane_marker_boundary_parms_.lftEdgeVld && 
        lane_marker_boundary_parms_.rgtEdgeVld,
        k_EP_LC_hold_duration, 0.02F);

}

void EnvironmentProcessing::getLaneCenterParameters(const LanesInfo &road_info)
{
    if (lane_marker_boundary_parms_.lftBdryVld && lane_marker_boundary_parms_.rgtBdryVld) {
        lane_center_parms_.c0 = -0.5F * (road_info.HostLeftLaneMarker.LinePolyC0 + road_info.HostRightLaneMarker.LinePolyC0);
        lane_center_parms_.c1 = -0.5F * (road_info.HostLeftLaneMarker.LinePolyC1 + road_info.HostRightLaneMarker.LinePolyC1);
        lane_center_parms_.c2 = -0.5F * (road_info.HostLeftLaneMarker.LinePolyC2 + road_info.HostRightLaneMarker.LinePolyC2);
        lane_center_parms_.c3 = -0.5F * (road_info.HostLeftLaneMarker.LinePolyC3 + road_info.HostRightLaneMarker.LinePolyC3);
        lane_center_parms_.startRange = std::max(road_info.HostLeftLaneMarker.LineViewRangeStart, road_info.HostRightLaneMarker.LineViewRangeStart);
        lane_center_parms_.endRange = std::min(road_info.HostLeftLaneMarker.LineViewRangeEnd, road_info.HostRightLaneMarker.LineViewRangeEnd);
        lane_center_parms_.vld = true;
        lane_marker_boundary_parms_.frtAxlCurv = 0.5F * (lane_marker_boundary_parms_.lftBdryCurv + lane_marker_boundary_parms_.rgtBdryCurv);
    } else if (lane_marker_boundary_parms_.lftBdryVld) {
        lane_center_parms_.c0 = -road_info.HostLeftLaneMarker.LinePolyC0 + 0.5 * lane_marker_boundary_parms_.laneWidth; // 左负右正，与模块输入相反
        lane_center_parms_.c1 = -road_info.HostLeftLaneMarker.LinePolyC1;
        lane_center_parms_.c2 = -road_info.HostLeftLaneMarker.LinePolyC2;
        lane_center_parms_.c3 = -road_info.HostLeftLaneMarker.LinePolyC3;
        lane_center_parms_.startRange = road_info.HostLeftLaneMarker.LineViewRangeStart;
        lane_center_parms_.endRange = road_info.HostLeftLaneMarker.LineViewRangeEnd;
        lane_center_parms_.vld = true;
        lane_marker_boundary_parms_.frtAxlCurv = lane_marker_boundary_parms_.lftBdryCurv;
    } else if (lane_marker_boundary_parms_.rgtBdryVld) {
        lane_center_parms_.c0 = -road_info.HostRightLaneMarker.LinePolyC0 - 0.5 * lane_marker_boundary_parms_.laneWidth;
        lane_center_parms_.c1 = -road_info.HostRightLaneMarker.LinePolyC1;
        lane_center_parms_.c2 = -road_info.HostRightLaneMarker.LinePolyC2;
        lane_center_parms_.c3 = -road_info.HostRightLaneMarker.LinePolyC3;
        lane_center_parms_.startRange = road_info.HostRightLaneMarker.LineViewRangeStart;
        lane_center_parms_.endRange = road_info.HostRightLaneMarker.LineViewRangeEnd;
        lane_center_parms_.vld = true;
        lane_marker_boundary_parms_.frtAxlCurv = lane_marker_boundary_parms_.rgtBdryCurv;
    } else {
        lane_center_parms_.c0 = 0.0F;
        lane_center_parms_.c1 = 0.0F;
        lane_center_parms_.c2 = 0.0F;
        lane_center_parms_.c3 = 0.0F;
        lane_center_parms_.startRange = 0.0F;
        lane_center_parms_.endRange = 0.0F;
        lane_center_parms_.vld = false;
        lane_marker_boundary_parms_.frtAxlCurv = 0.0F;
    }
    lane_center_parms_.heading = std::atan2(lane_center_parms_.c1, 1);
}

bool EnvironmentProcessing::isBoundaryJump(
    float c0, float c1, bool valid, float prev_c0, float prev_c1, bool prev_valid) const
{
    return valid && prev_valid &&
        ((std::fabs(c0 - prev_c0) > elk_cal_.k_ELK_BoundaryJump_C0Thr) ||
         (std::fabs(c1 - prev_c1) > elk_cal_.k_ELK_BoundaryJump_C1Thr));
}

float EnvironmentProcessing::calcBoundaryY(float c0, float c1, float c2, float c3, float x) const
{
    const float x2 = x * x;
    const float x3 = x2 * x;
    return c0 + c1 * x + c2 * x2 + c3 * x3;
}

bool EnvironmentProcessing::isLeftEdgeLaneMismatch(const LanesInfo &road_info) const
{
    if (!lane_marker_boundary_parms_.lftBdryVld || !lane_marker_boundary_parms_.lftEdgeVld ||
        road_info.LeftRoadEdge.LineViewRangeEnd < elk_cal_.k_ELK_EdgeLaneMismatch_MinEvalRange) {
        return false;
    }

    const float c1_diff =
        std::fabs(road_info.LeftRoadEdge.LinePolyC1 - road_info.HostLeftLaneMarker.LinePolyC1);
    const float x_eval = road_info.LeftRoadEdge.LineViewRangeEnd;
    const float edge_y = calcBoundaryY(
        road_info.LeftRoadEdge.LinePolyC0,
        road_info.LeftRoadEdge.LinePolyC1,
        road_info.LeftRoadEdge.LinePolyC2,
        road_info.LeftRoadEdge.LinePolyC3,
        x_eval);
    const float marker_y = calcBoundaryY(
        road_info.HostLeftLaneMarker.LinePolyC0,
        road_info.HostLeftLaneMarker.LinePolyC1,
        road_info.HostLeftLaneMarker.LinePolyC2,
        road_info.HostLeftLaneMarker.LinePolyC3,
        x_eval);
    const float left_gap = edge_y - marker_y;

    return (c1_diff > elk_cal_.k_ELK_EdgeLaneMismatch_C1DiffThr) &&
        (left_gap <= elk_cal_.k_ELK_EdgeLaneMismatch_EndGapThr);
}

bool EnvironmentProcessing::isRightEdgeLaneMismatch(const LanesInfo &road_info) const
{
    if (!lane_marker_boundary_parms_.rgtBdryVld || !lane_marker_boundary_parms_.rgtEdgeVld ||
        road_info.RightRoadEdge.LineViewRangeEnd < elk_cal_.k_ELK_EdgeLaneMismatch_MinEvalRange) {
        return false;
    }

    const float c1_diff =
        std::fabs(road_info.RightRoadEdge.LinePolyC1 - road_info.HostRightLaneMarker.LinePolyC1);
    const float x_eval = road_info.RightRoadEdge.LineViewRangeEnd;
    const float marker_y = calcBoundaryY(
        road_info.HostRightLaneMarker.LinePolyC0,
        road_info.HostRightLaneMarker.LinePolyC1,
        road_info.HostRightLaneMarker.LinePolyC2,
        road_info.HostRightLaneMarker.LinePolyC3,
        x_eval);
    const float edge_y = calcBoundaryY(
        road_info.RightRoadEdge.LinePolyC0,
        road_info.RightRoadEdge.LinePolyC1,
        road_info.RightRoadEdge.LinePolyC2,
        road_info.RightRoadEdge.LinePolyC3,
        x_eval);
    const float right_gap = marker_y - edge_y;

    return (c1_diff > elk_cal_.k_ELK_EdgeLaneMismatch_C1DiffThr) &&
        (right_gap <= elk_cal_.k_ELK_EdgeLaneMismatch_EndGapThr);
}

void EnvironmentProcessing::updateBoundaryQualityStatus(const LanesInfo &road_info)
{
    const bool left_boundary_jump_raw = isBoundaryJump(
        road_info.HostLeftLaneMarker.LinePolyC0,
        road_info.HostLeftLaneMarker.LinePolyC1,
        lane_marker_boundary_parms_.lftBdryVld,
        his_env_info_.lftC0,
        his_env_info_.lftC1,
        his_env_info_.lftVld);
    lane_marker_boundary_parms_.lftBdryJump = left_boundary_jump_.signalHold(
        left_boundary_jump_raw, elk_cal_.k_ELK_BoundaryJump_HoldTime, elk_cal_.k_ELK_StepTime);

    const bool right_boundary_jump_raw = isBoundaryJump(
        road_info.HostRightLaneMarker.LinePolyC0,
        road_info.HostRightLaneMarker.LinePolyC1,
        lane_marker_boundary_parms_.rgtBdryVld,
        his_env_info_.rgtC0,
        his_env_info_.rgtC1,
        his_env_info_.rgtVld);
    lane_marker_boundary_parms_.rgtBdryJump = right_boundary_jump_.signalHold(
        right_boundary_jump_raw, elk_cal_.k_ELK_BoundaryJump_HoldTime, elk_cal_.k_ELK_StepTime);

    const bool left_edge_jump_raw = isBoundaryJump(
        road_info.LeftRoadEdge.LinePolyC0,
        road_info.LeftRoadEdge.LinePolyC1,
        lane_marker_boundary_parms_.lftEdgeVld,
        his_env_info_.lftEdgeC0,
        his_env_info_.lftEdgeC1,
        his_env_info_.lftEdgeVld);
    lane_marker_boundary_parms_.lftEdgeJump = left_edge_jump_.signalHold(
        left_edge_jump_raw, elk_cal_.k_ELK_BoundaryJump_HoldTime, elk_cal_.k_ELK_StepTime);

    const bool right_edge_jump_raw = isBoundaryJump(
        road_info.RightRoadEdge.LinePolyC0,
        road_info.RightRoadEdge.LinePolyC1,
        lane_marker_boundary_parms_.rgtEdgeVld,
        his_env_info_.rgtEdgeC0,
        his_env_info_.rgtEdgeC1,
        his_env_info_.rgtEdgeVld);
    lane_marker_boundary_parms_.rgtEdgeJump = right_edge_jump_.signalHold(
        right_edge_jump_raw, elk_cal_.k_ELK_BoundaryJump_HoldTime, elk_cal_.k_ELK_StepTime);

    lane_marker_boundary_parms_.lftBdryRangeShort =
        lane_marker_boundary_parms_.lftBdryVld &&
        (road_info.HostLeftLaneMarker.LineViewRangeEnd < elk_cal_.k_ELK_Boundary_MinViewRangeEnd);
    lane_marker_boundary_parms_.rgtBdryRangeShort =
        lane_marker_boundary_parms_.rgtBdryVld &&
        (road_info.HostRightLaneMarker.LineViewRangeEnd < elk_cal_.k_ELK_Boundary_MinViewRangeEnd);
    lane_marker_boundary_parms_.lftEdgeRangeShort =
        lane_marker_boundary_parms_.lftEdgeVld &&
        (road_info.LeftRoadEdge.LineViewRangeEnd < elk_cal_.k_ELK_Boundary_MinViewRangeEnd);
    lane_marker_boundary_parms_.rgtEdgeRangeShort =
        lane_marker_boundary_parms_.rgtEdgeVld &&
        (road_info.RightRoadEdge.LineViewRangeEnd < elk_cal_.k_ELK_Boundary_MinViewRangeEnd);

    lane_marker_boundary_parms_.lftEdgeLaneMismatch = isLeftEdgeLaneMismatch(road_info);
    lane_marker_boundary_parms_.rgtEdgeLaneMismatch = isRightEdgeLaneMismatch(road_info);
}

void EnvironmentProcessing::updateBoundaryHistory(const LanesInfo &road_info)
{
    his_env_info_.lftC0 = road_info.HostLeftLaneMarker.LinePolyC0;
    his_env_info_.lftC1 = road_info.HostLeftLaneMarker.LinePolyC1;
    his_env_info_.lftVld = lane_marker_boundary_parms_.lftBdryVld;
    his_env_info_.rgtC0 = road_info.HostRightLaneMarker.LinePolyC0;
    his_env_info_.rgtC1 = road_info.HostRightLaneMarker.LinePolyC1;
    his_env_info_.rgtVld = lane_marker_boundary_parms_.rgtBdryVld;
    his_env_info_.lftEdgeC0 = road_info.LeftRoadEdge.LinePolyC0;
    his_env_info_.lftEdgeC1 = road_info.LeftRoadEdge.LinePolyC1;
    his_env_info_.lftEdgeVld = lane_marker_boundary_parms_.lftEdgeVld;
    his_env_info_.rgtEdgeC0 = road_info.RightRoadEdge.LinePolyC0;
    his_env_info_.rgtEdgeC1 = road_info.RightRoadEdge.LinePolyC1;
    his_env_info_.rgtEdgeVld = lane_marker_boundary_parms_.rgtEdgeVld;
}

void EnvironmentProcessing::detectLaneChangeBoundary(const LanesInfo &road_info)
{
    if ((road_info.HostLeftLaneMarker.LinePolyC0 - his_env_info_.lftC0 > 2.5F) && 
        (his_env_info_.lftC0 < 0.1F) && (his_env_info_.lftC0 > -0.1F) &&
        lane_marker_boundary_parms_.lftBdryVld && his_env_info_.lftVld) {
        
        lane_marker_boundary_parms_.lftLcTm = 0.0F;
        lane_marker_boundary_parms_.lftLaneChange = true;
    } else {
        lane_marker_boundary_parms_.lftLcTm = lane_marker_boundary_parms_.lftLcTm + 0.02F;
        if (lane_marker_boundary_parms_.lftLcTm > 0.3F) {
            lane_marker_boundary_parms_.lftLcTm = 0.0F;
            lane_marker_boundary_parms_.lftLaneChange = false;
        }
    }

    if ((road_info.HostRightLaneMarker.LinePolyC0 - his_env_info_.rgtC0 < -2.5F) && 
        (his_env_info_.rgtC0 < 0.1F) && (his_env_info_.rgtC0 > -0.1F) &&
        lane_marker_boundary_parms_.rgtBdryVld && his_env_info_.rgtVld) {
        
        lane_marker_boundary_parms_.rgtLcTm = 0.0F;
        lane_marker_boundary_parms_.rgtLaneChange = true;
    } else {
        lane_marker_boundary_parms_.rgtLcTm = lane_marker_boundary_parms_.rgtLcTm + 0.02F;
        if (lane_marker_boundary_parms_.rgtLcTm > 0.3F) {
            lane_marker_boundary_parms_.rgtLcTm = 0.0F;
            lane_marker_boundary_parms_.rgtLaneChange = false;
        }
    }
}

} // namespace elk
} // namespace active_safety
