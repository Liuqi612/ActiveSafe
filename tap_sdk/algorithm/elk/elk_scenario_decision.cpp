#include "elk_scenario_decision.h"

#include "ad_log/ad_log.hpp"

#include <algorithm>

namespace active_safety {
namespace elk {

bool ElkScenarioDecision::determineLeftIntervention(const LanesInfo &road_info, 
                                                    const LaneBoundaryParameters &lane_boundary, 
                                                    const ElkTaSl &ta_info, 
                                                    const GlobalConfig &config, 
                                                    float vehSpd, 
                                                    bool lftMkrVld, 
                                                    bool lftEdgVld)
{
    return determineLeftInterventionWithTtcMode(
        road_info, lane_boundary, ta_info, config, vehSpd, lftMkrVld, lftEdgVld, TtcCheckMode::Activation);
}

bool ElkScenarioDecision::determineLeftInterventionForSuppressedExit(const LanesInfo &road_info,
                                                                     const LaneBoundaryParameters &lane_boundary,
                                                                     const ElkTaSl &ta_info,
                                                                     const GlobalConfig &config,
                                                                     float vehSpd,
                                                                     bool lftMkrVld,
                                                                     bool lftEdgVld)
{
    return determineLeftInterventionWithTtcMode(
        road_info, lane_boundary, ta_info, config, vehSpd, lftMkrVld, lftEdgVld, TtcCheckMode::SuppressedExit);
}

bool ElkScenarioDecision::determineLeftInterventionWithTtcMode(const LanesInfo &road_info,
                                                              const LaneBoundaryParameters &lane_boundary,
                                                              const ElkTaSl &ta_info,
                                                              const GlobalConfig &config,
                                                              float vehSpd,
                                                              bool lftMkrVld,
                                                              bool lftEdgVld,
                                                              TtcCheckMode ttcMode)
{
    k_left_curv_dist_offset_marker_ = math::LookUpTable::LookupTable1D<10>(
        elk_cals_.k_ELK_LfCurvDistOffst_mrgn_x, elk_cals_.k_ELK_LfCurvDistOffst_mrgn_z, -lane_boundary.frtAxlCurv);
    
    k_left_curv_dist_offset_edge_ = math::LookUpTable::LookupTable1D<10>(
        elk_cals_.k_ELK_LfCurvDistOffst_mrgn_x, elk_cals_.k_ELK_LfCurvDistOffst_mrgn_z, -lane_boundary.lftEdgeCurv);
    // environment_process模块的曲率左弯为正，右弯为负，与查表输入相反

    if (determineLeftSolidIntervention(lane_boundary, road_info.HostLeftLaneMarker, config, vehSpd, lftMkrVld, ttcMode)) {
        left_active_source_mask_ |= 0x1; // 将bit0设为1，表征实线触发
    }

    if (determineLeftEdgeIntervention(lane_boundary, road_info.LeftRoadEdge, config, vehSpd, lftEdgVld, ttcMode)) {
        left_active_source_mask_ |= 0x2; // 将bit1设为1，表征路沿触发
    }

    if (determineLeftObstacleIntervention(lane_boundary, ta_info, config, lftMkrVld, vehSpd, ttcMode)) {
        if (ta_info.oncoming_front_left.threat) {
            left_active_source_mask_ |= 0x4; // 将bit2设为1，表征oncoming触发
        } else if (ta_info.overtaking_rear_left.threat) {
            left_active_source_mask_ |= 0x8; // 将bit3设为1，表征overtaking触发
        }
    }

    //AD_LINFO(ElkScenarioDecision::determineLeftIntervention) << "left_active_source_mask_ is: " << (int)left_active_source_mask_;

    return left_active_source_mask_ > 0;
}

bool ElkScenarioDecision::determineRightIntervention(const LanesInfo &road_info, 
                                                     const LaneBoundaryParameters &lane_boundary, 
                                                     const ElkTaSl &ta_info, 
                                                     const GlobalConfig &config,
                                                     float vehSpd, 
                                                     bool rgtMkrVld, 
                                                     bool rgtEdgVld)
{
    return determineRightInterventionWithTtcMode(
        road_info, lane_boundary, ta_info, config, vehSpd, rgtMkrVld, rgtEdgVld, TtcCheckMode::Activation);
}

bool ElkScenarioDecision::determineRightInterventionForSuppressedExit(const LanesInfo &road_info,
                                                                      const LaneBoundaryParameters &lane_boundary,
                                                                      const ElkTaSl &ta_info,
                                                                      const GlobalConfig &config,
                                                                      float vehSpd,
                                                                      bool rgtMkrVld,
                                                                      bool rgtEdgVld)
{
    return determineRightInterventionWithTtcMode(
        road_info, lane_boundary, ta_info, config, vehSpd, rgtMkrVld, rgtEdgVld, TtcCheckMode::SuppressedExit);
}

bool ElkScenarioDecision::determineRightInterventionWithTtcMode(const LanesInfo &road_info,
                                                               const LaneBoundaryParameters &lane_boundary,
                                                               const ElkTaSl &ta_info,
                                                               const GlobalConfig &config,
                                                               float vehSpd,
                                                               bool rgtMkrVld,
                                                               bool rgtEdgVld,
                                                               TtcCheckMode ttcMode)
{
    k_right_curv_dist_offset_marker_ = math::LookUpTable::LookupTable1D<10>(
        elk_cals_.k_ELK_RtCurvDistOffst_mrgn_x, elk_cals_.k_ELK_RtCurvDistOffst_mrgn_z, -lane_boundary.frtAxlCurv);
    
    k_right_curv_dist_offset_edge_ = math::LookUpTable::LookupTable1D<10>(
        elk_cals_.k_ELK_RtCurvDistOffst_mrgn_x, elk_cals_.k_ELK_RtCurvDistOffst_mrgn_z, -lane_boundary.rgtEdgeCurv);
    // environment_process模块的曲率左弯为正，右弯为负，与查表输入相反

    if (determineRightSolidIntervention(lane_boundary, road_info.HostRightLaneMarker, config, vehSpd, rgtMkrVld, ttcMode)) {
        right_active_source_mask_ |= 0x1;
    }

    if (determineRightEdgeIntervention(lane_boundary, road_info.RightRoadEdge, config, vehSpd, rgtEdgVld, ttcMode)) {
        right_active_source_mask_ |= 0x2;
    }

    if (determineRightObstacleIntervention(lane_boundary, ta_info, config, rgtMkrVld, vehSpd, ttcMode)) {
        if (ta_info.oncoming_front_right.threat) {
            right_active_source_mask_ |= 0x4;
        } else if (ta_info.overtaking_rear_right.threat) {
            right_active_source_mask_ |= 0x8;
        }
    }

    //AD_LINFO(ElkScenarioDecision::determineRightIntervention) << "right_active_source_mask_ is: " << (int)right_active_source_mask_;

    return right_active_source_mask_ > 0;
}

bool ElkScenarioDecision::determineLeftSuppression(uint32_t suppression_mask)
{
    left_suppression_mask_ = 0U;
    if ((left_active_source_mask_ & 0xC) != 0) { // 激活的是障碍物
        left_suppression_mask_ = suppression_mask & elk_cals_.k_EVP_Left_Suprsn_Mask_LCT;
        //AD_LINFO(ElkScenarioDecision::determineLeftSuppression) << "left LCT Suppression mask is: " << left_suppression_mask_;
        return left_suppression_mask_ != 0;
    } else if ((left_active_source_mask_ & 0x2) != 0) { // 激活的是路沿
        left_suppression_mask_ = suppression_mask & elk_cals_.k_EVP_Left_Suprsn_Mask_RE;
        //AD_LINFO(ElkScenarioDecision::determineLeftSuppression) << "left RE Suppression mask is: " << left_suppression_mask_;
        return left_suppression_mask_ != 0;
    } else if ((left_active_source_mask_ & 0x1) != 0) { // 激活的是实线
        left_suppression_mask_ = suppression_mask & elk_cals_.k_EVP_Left_Suprsn_Mask_SLD;
        //AD_LINFO(ElkScenarioDecision::determineLeftSuppression) << "left SLD Suppression mask is: " << left_suppression_mask_;
        return left_suppression_mask_ != 0;
    } else {
        return false;
    }
}

bool ElkScenarioDecision::determineRightSuppression(uint32_t suppression_mask)
{
    right_suppression_mask_ = 0U;
    if ((right_active_source_mask_ & 0xC) != 0) { // 激活的是障碍物
        right_suppression_mask_ = suppression_mask & elk_cals_.k_EVP_Right_Suprsn_Mask_LCT;
        //AD_LINFO(ElkScenarioDecision::determineRightSuppression) << "right LCT Suppression mask is: " << right_suppression_mask_;
        return right_suppression_mask_ != 0;
    } else if ((right_active_source_mask_ & 0x2) != 0) { // 激活的是路沿
        right_suppression_mask_ = suppression_mask & elk_cals_.k_EVP_Right_Suprsn_Mask_RE;
        //AD_LINFO(ElkScenarioDecision::determineRightSuppression) << "right RE Suppression mask is: " << right_suppression_mask_;
        return right_suppression_mask_ != 0;
    } else if ((right_active_source_mask_ & 0x1) != 0) { // 激活的是实线
        right_suppression_mask_ = suppression_mask & elk_cals_.k_EVP_Right_Suprsn_Mask_SLD;
        //AD_LINFO(ElkScenarioDecision::determineRightSuppression) << "right SLD Suppression mask is: " << right_suppression_mask_;
        return right_suppression_mask_ != 0;
    } else {
        return false;
    }
}

bool ElkScenarioDecision::checkLeftAligned(const LanesInfo &road_info, const LaneBoundaryParameters &lane_boundary, const LaneCenterParameters &lane_center, const GlobalConfig &config)
{
    bool c0_aligned, c1_aligned;
    float c0, c1;

    if ((left_active_source_mask_ & 0x2) != 0) { // 左侧路沿激活
        if (lane_boundary.lftBdryVld && lane_boundary.rgtBdryVld) {
            c0 = 0.5F * (road_info.HostLeftLaneMarker.LinePolyC0 + road_info.HostRightLaneMarker.LinePolyC0);
            c1 = 0.5 * (road_info.HostLeftLaneMarker.LinePolyC1 + road_info.HostRightLaneMarker.LinePolyC1);
            //AD_LINFO(ElkScenarioDecision::checkLeftAligned) << "use center line for ELK left edge control target.";
        } else if (lane_boundary.lftBdryVld) {
            if ((road_info.HostLeftLaneMarker.LinePolyC0 < road_info.LeftRoadEdge.LinePolyC0) &&
                 lane_boundary.lftEdgeVld) { // 左侧车道线在左路沿内侧
                c0 = -road_info.HostLeftLaneMarker.LinePolyC0 + elk_cals_.k_ELK_Aligned_LMOffset;
                //AD_LINFO(ElkScenarioDecision::checkLeftAligned) << "left line inside edge, use left line offset for ELK left edge control target c0.";
            } else {
                c0 = -road_info.LeftRoadEdge.LinePolyC0 + elk_cals_.k_ELK_Aligned_REOffset;
                //AD_LINFO(ElkScenarioDecision::checkLeftAligned) << "left line outside edge, use left edge offset for ELK left edge control target c0.";
            }
            c1 = road_info.HostLeftLaneMarker.LinePolyC1;
            //AD_LINFO(ElkScenarioDecision::checkLeftAligned) << "use left line for ELK left edge control target c1.";
        } else if (lane_boundary.rgtBdryVld) {
            if ((road_info.LeftRoadEdge.LinePolyC0 - road_info.HostRightLaneMarker.LinePolyC0 > 4.0F) &&
                lane_boundary.rgtEdgeVld) { // 右车道线与左侧路沿较远
                c0 = -road_info.LeftRoadEdge.LinePolyC0 + elk_cals_.k_ELK_Aligned_REOffset;
                //AD_LINFO(ElkScenarioDecision::checkLeftAligned) << "right line far from edge, use left edge offset for ELK left edge control target c0.";
            } else {
                c0 = -road_info.HostRightLaneMarker.LinePolyC0 - elk_cals_.k_ELK_Aligned_LMOffset;
                //AD_LINFO(ElkScenarioDecision::checkLeftAligned) << "right line not far from edge, use right line offset for ELK left edge control target c0.";
            }
            c1 = 0.5 * (road_info.LeftRoadEdge.LinePolyC1 + road_info.HostRightLaneMarker.LinePolyC1);
            //AD_LINFO(ElkScenarioDecision::checkLeftAligned) << "use right line and left edge for ELK left edge control target c1.";
        } else { // 车道线均无效
            c0 = -road_info.LeftRoadEdge.LinePolyC0 + elk_cals_.k_ELK_Aligned_REOffset;
            c1 = road_info.LeftRoadEdge.LinePolyC1;
            //AD_LINFO(ElkScenarioDecision::checkLeftAligned) << "use left edge for ELK left edge control target.";
        }
    } else {
        c0 = lane_center.c0;
        c1 = lane_center.c1;
    }

    c0_aligned = std::fabs(c0) < elk_cals_.k_ELK_Aligned_C0_Thr;
    c1_aligned = std::fabs(c1) < elk_cals_.k_ELK_Aligned_C1_Thr;

    return left_aligned_checker_.onDelay(c0_aligned && c1_aligned,
        config.k_ELK_Aligned_OnDelayTime, elk_cals_.k_ELK_StepTime);
}

bool ElkScenarioDecision::checkRightAligned(const LanesInfo &road_info, const LaneBoundaryParameters &lane_boundary, const LaneCenterParameters &lane_center, const GlobalConfig &config)
{
    bool c0_aligned, c1_aligned;
    float c0, c1;

    if ((right_active_source_mask_ & 0x2) != 0) { // 右侧路沿激活
        if (lane_boundary.lftBdryVld && lane_boundary.rgtBdryVld) {
            c0 = 0.5 * (road_info.HostLeftLaneMarker.LinePolyC0 + road_info.HostRightLaneMarker.LinePolyC0);
            c1 = 0.5 * (road_info.HostLeftLaneMarker.LinePolyC1 + road_info.HostRightLaneMarker.LinePolyC1);
            //AD_LINFO(ElkScenarioDecision::checkRightAligned) << "use center line for ELK right edge control target.";
        } else if (lane_boundary.rgtBdryVld) {
            if ((road_info.HostRightLaneMarker.LinePolyC0 > road_info.RightRoadEdge.LinePolyC0) &&
                 lane_boundary.rgtEdgeVld) { // 右侧车道线在右路沿内侧
                c0 = -road_info.HostRightLaneMarker.LinePolyC0 - elk_cals_.k_ELK_Aligned_LMOffset;
                //AD_LINFO(ElkScenarioDecision::checkRightAligned) << "right line inside edge, use right line offset for ELK right edge control target c0.";
            } else {
                c0 = -road_info.RightRoadEdge.LinePolyC0 - elk_cals_.k_ELK_Aligned_REOffset;
                //AD_LINFO(ElkScenarioDecision::checkRightAligned) << "right line outside edge, use right edge offset for ELK right edge control target c0.";
            }
            c1 = road_info.HostRightLaneMarker.LinePolyC1;
            //AD_LINFO(ElkScenarioDecision::checkRightAligned) << "use right line for ELK right edge control target c1.";
        } else if (lane_boundary.lftBdryVld) {
            if ((road_info.HostLeftLaneMarker.LinePolyC0 - road_info.RightRoadEdge.LinePolyC0 > 4.0F) &&
                lane_boundary.rgtEdgeVld) { // 左车道线与右侧路沿较远
                c0 = -road_info.RightRoadEdge.LinePolyC0 - elk_cals_.k_ELK_Aligned_REOffset;
                //AD_LINFO(ElkScenarioDecision::checkRightAligned) << "left line far from edge, use right edge offset for ELK right edge control target c0.";
            } else {
                c0 = -road_info.HostLeftLaneMarker.LinePolyC0 + elk_cals_.k_ELK_Aligned_LMOffset;
                //AD_LINFO(ElkScenarioDecision::checkRightAligned) << "left line not far from edge, use left line offset for ELK right edge control target c0.";
            }
            c1 = 0.5 * (road_info.RightRoadEdge.LinePolyC1 + road_info.HostLeftLaneMarker.LinePolyC1);
            //AD_LINFO(ElkScenarioDecision::checkRightAligned) << "use right edge and left line for ELK right edge control target c1.";
        } else { // 车道线均无效
            c0 = -road_info.RightRoadEdge.LinePolyC0 - elk_cals_.k_ELK_Aligned_REOffset;
            c1 = road_info.RightRoadEdge.LinePolyC1;
            //AD_LINFO(ElkScenarioDecision::checkRightAligned) << "use right edge for ELK right edge control target.";
        }
    } else {
        c0 = lane_center.c0;
        c1 = lane_center.c1;
    }

    c0_aligned = std::fabs(c0) < elk_cals_.k_ELK_Aligned_C0_Thr;
    c1_aligned = std::fabs(c1) < elk_cals_.k_ELK_Aligned_C1_Thr;

    return right_aligned_checker_.onDelay(c0_aligned && c1_aligned,
        config.k_ELK_Aligned_OnDelayTime, elk_cals_.k_ELK_StepTime);
}

float ElkScenarioDecision::calcSpeedBasedTtcThreshold(float vehSpd, float lowSpdTtc, float nominalTtc) const
{
    const float veh_spd_kph = 3.6F * vehSpd;

    if (veh_spd_kph <= elk_cals_.k_ELK_TTC_LowSpdStartKph) {
        return lowSpdTtc;
    }
    if (veh_spd_kph <= elk_cals_.k_ELK_TTC_LowSpdEndKph) {
        return lowSpdTtc;
    }
    if (veh_spd_kph >= elk_cals_.k_ELK_TTC_HighSpdRecoverKph) {
        return nominalTtc;
    }

    return math::LookUpTable::LinearInterpolation(
        veh_spd_kph,
        elk_cals_.k_ELK_TTC_LowSpdEndKph,
        lowSpdTtc,
        elk_cals_.k_ELK_TTC_HighSpdRecoverKph,
        nominalTtc);
}

void ElkScenarioDecision::resetTtcHistory(TtcHistory &history)
{
    history.ttc.fill(0.0F);
    history.valid_frame_count = 0U;
    history.invalid_ttc_count = 0U;
}

bool ElkScenarioDecision::checkStableTtcDeparture(
    TtcHistory &history, float ttlc, float threshold, bool historyEnabled)
{
    if (!historyEnabled) {
        resetTtcHistory(history);
        return false;
    }

    if (ttlc <= 0.0F) {
        history.invalid_ttc_count =
            std::min<uint8_t>(static_cast<uint8_t>(history.invalid_ttc_count + 1U), static_cast<uint8_t>(255U));
        if (history.invalid_ttc_count > elk_cals_.k_ELK_TTC_InvalidToleranceFrames) {
            resetTtcHistory(history);
        }
        return false;
    }

    history.invalid_ttc_count = 0U;
    history.ttc[0] = history.ttc[1];
    history.ttc[1] = history.ttc[2];
    history.ttc[2] = ttlc;
    if (history.valid_frame_count < 3U) {
        ++history.valid_frame_count;
    }

    if (history.valid_frame_count < 3U) {
        return false;
    }

    const bool b_all_ttc_under_threshold =
        (history.ttc[0] < threshold) && (history.ttc[1] < threshold) && (history.ttc[2] < threshold);
    const bool b_ttc_non_increasing = (history.ttc[2] <= history.ttc[1]) && (history.ttc[1] <= history.ttc[0]);

    return b_all_ttc_under_threshold && b_ttc_non_increasing;
}

bool ElkScenarioDecision::checkTtcDeparture(
    TtcHistory &history, float ttlc, float threshold, bool historyEnabled, TtcCheckMode mode)
{
    if (!historyEnabled) {
        resetTtcHistory(history);
        return false;
    }

    if (mode == TtcCheckMode::SuppressedExit) {
        // Suppressed退出只判断当前TTC是否仍在阈值内，不再要求3帧历史稳定。
        // ttlc<=0视为当前TTC触发条件无效，允许按 !(trigger && suppression) 退出。
        return (ttlc > 0.0F) && (ttlc <= threshold);
    }

    return checkStableTtcDeparture(history, ttlc, threshold, historyEnabled);
}

void ElkScenarioDecision::updateTtcFalseTriggerDebugMask(const TtcHistory &history,
                                                         float ttlc,
                                                         float threshold,
                                                         float nominalThreshold,
                                                         bool historyEnabled,
                                                         bool lowLatRtNear,
                                                         bool stableTtcDeparture,
                                                         uint8_t historyBit,
                                                         uint8_t lowSpeedBit,
                                                         uint8_t invalidBit)
{
    if (!historyEnabled || lowLatRtNear) {
        return;
    }

    if (ttlc <= 0.0F) {
        if ((history.invalid_ttc_count > 0U) &&
            (history.invalid_ttc_count <= elk_cals_.k_ELK_TTC_InvalidToleranceFrames)) {
            ttc_false_trigger_debug_mask_ |= (1ULL << invalidBit);
        }
        return;
    }

    if ((threshold < nominalThreshold) && (ttlc < nominalThreshold) && (ttlc >= threshold)) {
        ttc_false_trigger_debug_mask_ |= (1ULL << lowSpeedBit);
    }

    if ((ttlc < threshold) && !stableTtcDeparture) {
        ttc_false_trigger_debug_mask_ |= (1ULL << historyBit);
    }
}

void ElkScenarioDecision::updateTtcDebugSignal(TtcDebugSignal &signal,
                                               float ttlc,
                                               float distance,
                                               float threshold,
                                               float nominalThreshold,
                                               bool historyEnabled,
                                               bool lowLatRtNear,
                                               bool stableTtcDeparture)
{
    signal.ttlc = ttlc;
    signal.distance = distance;
    signal.threshold = threshold;
    signal.nominal_threshold = nominalThreshold;
    signal.history_enabled = historyEnabled;
    signal.low_lat_rate_near = lowLatRtNear;
    signal.stable_departure = stableTtcDeparture;
}

bool ElkScenarioDecision::checkLeftTtlcValid(
    const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode)
{
    const bool f_lowLatRt_near_left_mkr =
        (dist < elk_cals_.k_ELK_LCT_LLR_LftMaxIntvnDTM - k_left_curv_dist_offset_marker_) &&
        (dist > elk_cals_.k_ELK_LCT_MinIntvnDTM - k_left_curv_dist_offset_marker_) &&
        config.k_ELK_bUsLowRtNearTrg;
    const float nominal_threshold = elk_cals_.k_ELK_LCT_intvn_TTLC * config.k_ELK_LCT_TTLCScale;
    const float ttc_threshold = calcSpeedBasedTtcThreshold(
        vehSpd, elk_cals_.k_ELK_LCT_low_spd_intvn_TTLC, elk_cals_.k_ELK_LCT_intvn_TTLC) *
        config.k_ELK_LCT_TTLCScale;
    const bool f_ttlc_departure_left_mkr =
        checkTtcDeparture(left_lct_ttc_history_, ttlc, ttc_threshold, historyEnabled, ttcMode);
    updateTtcDebugSignal(ttc_debug_snapshot_.left_lct,
                         ttlc,
                         dist,
                         ttc_threshold,
                         nominal_threshold,
                         historyEnabled,
                         f_lowLatRt_near_left_mkr,
                         f_ttlc_departure_left_mkr);
    if (ttcMode == TtcCheckMode::Activation) {
        updateTtcFalseTriggerDebugMask(
            left_lct_ttc_history_,
            ttlc,
            ttc_threshold,
            nominal_threshold,
            historyEnabled,
            f_lowLatRt_near_left_mkr,
            f_ttlc_departure_left_mkr,
            10U,
            16U,
            22U);
    }

    return f_lowLatRt_near_left_mkr || f_ttlc_departure_left_mkr;
}

bool ElkScenarioDecision::checkLeftDistStable(float dist) const
{
    return (dist > elk_cals_.k_ELK_LCT_LftMinIntvnDTM) &&
        (dist < elk_cals_.k_ELK_LCT_LftMaxIntvnDTM - k_left_curv_dist_offset_marker_);
}

bool ElkScenarioDecision::determineLeftObstacleIntervention(const LaneBoundaryParameters &lane_boundary, 
                                                            const ElkTaSl &ta_info, 
                                                            const GlobalConfig &config,
                                                            bool lftMkrVld,
                                                            float vehSpd,
                                                            TtcCheckMode ttcMode)
{
    left_intervention_mask_ = 0x0;

    const bool b_no_lane_change = !lane_boundary.lftLaneChange && !lane_boundary.rgtLaneChange;
    const bool b_left_dist_valid = checkLeftDistStable(lane_boundary.curLftDisToBdry);
    const bool b_left_boundary_quality_valid = !lane_boundary.lftBdryJump && !lane_boundary.lftBdryRangeShort;
    const bool b_left_ttc_history_enabled =
        config.k_ELK_EnLct && b_left_dist_valid && b_no_lane_change && lftMkrVld && b_left_boundary_quality_valid;
    const bool b_left_ttlc_valid = checkLeftTtlcValid(
        config, lane_boundary.curLftDisToBdry, lane_boundary.lftBdryTtlc, vehSpd, b_left_ttc_history_enabled, ttcMode);
    const bool b_left_target_threat = ta_info.oncoming_front_left.threat || ta_info.overtaking_rear_left.threat;

    if (b_no_lane_change) {
        left_intervention_mask_ = left_intervention_mask_ + 0x1;
    }

    if (b_left_ttlc_valid) {
        left_intervention_mask_ = left_intervention_mask_ + 0x2;
    }

    if (b_left_dist_valid) {
        left_intervention_mask_ = left_intervention_mask_ + 0x4;
    }

    if (lftMkrVld) {
        left_intervention_mask_ = left_intervention_mask_ + 0x8;
    }

    if (b_left_target_threat) {
        left_intervention_mask_ = left_intervention_mask_ + 0x10;
    }

    return config.k_ELK_EnLct && b_left_ttlc_valid && b_left_dist_valid && b_no_lane_change && lftMkrVld &&
        b_left_boundary_quality_valid &&
        b_left_target_threat;
}

bool ElkScenarioDecision::checkRightTtlcValid(
    const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode)
{
    const bool f_lowLatRt_near_right_mkr =
        (dist < elk_cals_.k_ELK_LCT_LLR_RgtMaxIntvnDTM - k_right_curv_dist_offset_marker_) &&
        (dist > elk_cals_.k_ELK_LCT_MinIntvnDTM - k_right_curv_dist_offset_marker_) &&
        config.k_ELK_bUsLowRtNearTrg;
    const float nominal_threshold = elk_cals_.k_ELK_LCT_intvn_TTLC * config.k_ELK_LCT_TTLCScale;
    const float ttc_threshold = calcSpeedBasedTtcThreshold(
        vehSpd, elk_cals_.k_ELK_LCT_low_spd_intvn_TTLC, elk_cals_.k_ELK_LCT_intvn_TTLC) *
        config.k_ELK_LCT_TTLCScale;
    const bool f_ttlc_departure_right_mkr =
        checkTtcDeparture(right_lct_ttc_history_, ttlc, ttc_threshold, historyEnabled, ttcMode);
    updateTtcDebugSignal(ttc_debug_snapshot_.right_lct,
                         ttlc,
                         dist,
                         ttc_threshold,
                         nominal_threshold,
                         historyEnabled,
                         f_lowLatRt_near_right_mkr,
                         f_ttlc_departure_right_mkr);
    if (ttcMode == TtcCheckMode::Activation) {
        updateTtcFalseTriggerDebugMask(
            right_lct_ttc_history_,
            ttlc,
            ttc_threshold,
            nominal_threshold,
            historyEnabled,
            f_lowLatRt_near_right_mkr,
            f_ttlc_departure_right_mkr,
            11U,
            17U,
            23U);
    }

    return f_lowLatRt_near_right_mkr || f_ttlc_departure_right_mkr;
}

bool ElkScenarioDecision::checkRightDistStable(float dist) const
{
    return (dist > elk_cals_.k_ELK_RgtMinIntvnDTM) &&
        (dist < elk_cals_.k_ELK_RgtMaxIntvnDTM - k_right_curv_dist_offset_marker_);
}

bool ElkScenarioDecision::determineRightObstacleIntervention(const LaneBoundaryParameters &lane_boundary, 
                                                             const ElkTaSl &ta_info, 
                                                             const GlobalConfig &config,
                                                             bool rgtMkrVld,
                                                             float vehSpd,
                                                             TtcCheckMode ttcMode)
{
    right_intervention_mask_ = 0x0;
    
    const bool b_no_lane_change = !lane_boundary.lftLaneChange && !lane_boundary.rgtLaneChange;
    const bool b_right_dist_valid = checkRightDistStable(lane_boundary.curRgtDisToBdry);
    const bool b_right_boundary_quality_valid = !lane_boundary.rgtBdryJump && !lane_boundary.rgtBdryRangeShort;
    const bool b_right_ttc_history_enabled =
        config.k_ELK_EnLct && b_right_dist_valid && b_no_lane_change && rgtMkrVld && b_right_boundary_quality_valid;
    const bool b_right_ttlc_valid = checkRightTtlcValid(
        config, lane_boundary.curRgtDisToBdry, lane_boundary.rgtBdryTtlc, vehSpd, b_right_ttc_history_enabled, ttcMode);
    const bool b_right_target_threat = ta_info.oncoming_front_right.threat || ta_info.overtaking_rear_right.threat;

    if (b_no_lane_change) {
        right_intervention_mask_ = right_intervention_mask_ + 0x1;
    }

    if (b_right_ttlc_valid) {
        right_intervention_mask_ = right_intervention_mask_ + 0x2;
    }

    if (b_right_dist_valid) {
        right_intervention_mask_ = right_intervention_mask_ + 0x4;
    }

    if (rgtMkrVld) {
        right_intervention_mask_ = right_intervention_mask_ + 0x8;
    }

    if (b_right_target_threat) {
        right_intervention_mask_ = right_intervention_mask_ + 0x10;
    }

    return config.k_ELK_EnLct && b_right_ttlc_valid && b_right_dist_valid && b_no_lane_change && rgtMkrVld &&
        b_right_boundary_quality_valid &&
        b_right_target_threat;
}

bool ElkScenarioDecision::checkLeftEdgeTtlcValid(
    const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode)
{
    const bool f_lowLatRt_near_left_edge =
        (dist < elk_cals_.k_ELK_ROR_LLR_LftMaxIntvnDTE - k_left_curv_dist_offset_edge_) &&
        (dist > elk_cals_.k_ELK_ROR_MinIntvnDTE - k_left_curv_dist_offset_edge_) &&
        config.k_ELK_bUsLowRtNearTrg;
    const float nominal_threshold = elk_cals_.k_ELK_ROR_intvn_TTLC_left * config.k_ELK_ROR_TTLCScale;
    const float ttc_threshold = calcSpeedBasedTtcThreshold(
        vehSpd, elk_cals_.k_ELK_ROR_low_spd_intvn_TTLC, elk_cals_.k_ELK_ROR_intvn_TTLC_left) *
        config.k_ELK_ROR_TTLCScale;
    const bool f_ttlc_departure_left_edge =
        checkTtcDeparture(left_edge_ttc_history_, ttlc, ttc_threshold, historyEnabled, ttcMode);
    updateTtcDebugSignal(ttc_debug_snapshot_.left_ror,
                         ttlc,
                         dist,
                         ttc_threshold,
                         nominal_threshold,
                         historyEnabled,
                         f_lowLatRt_near_left_edge,
                         f_ttlc_departure_left_edge);
    if (ttcMode == TtcCheckMode::Activation) {
        updateTtcFalseTriggerDebugMask(
            left_edge_ttc_history_,
            ttlc,
            ttc_threshold,
            nominal_threshold,
            historyEnabled,
            f_lowLatRt_near_left_edge,
            f_ttlc_departure_left_edge,
            12U,
            18U,
            24U);
    }

    return f_lowLatRt_near_left_edge || f_ttlc_departure_left_edge;
}

bool ElkScenarioDecision::checkLeftEdgeDistStable(float dist) const
{
    return (dist > elk_cals_.k_ELK_ROR_MinIntvnDTE) &&
        (dist < elk_cals_.k_ELK_ROR_LftMaxIntvnDTE - k_left_curv_dist_offset_edge_);
}

bool ElkScenarioDecision::determineLeftEdgeIntervention(const LaneBoundaryParameters &lane_boundary, 
                                                        const RoadEdge_t &left_edge, 
                                                        const GlobalConfig &config,
                                                        float vehSpd, 
                                                        bool lftEdgVld,
                                                        TtcCheckMode ttcMode)
{
    left_edge_intervention_mask_ = 0x0;

    const bool b_no_off_road = !lane_boundary.runOffRoadLft && !lane_boundary.runOffRoadRgt;
    const bool b_left_dist_valid = checkLeftEdgeDistStable(lane_boundary.curLftDisToEdge);
    const bool b_left_range_valid = checkEdgeRangeValid(left_edge.LineViewRangeStart, left_edge.LineViewRangeEnd, vehSpd);
    const bool b_left_edge_quality_valid =
        !lane_boundary.lftEdgeJump && !lane_boundary.lftEdgeRangeShort && !lane_boundary.lftEdgeLaneMismatch;
    const bool b_left_ttc_history_enabled =
        config.k_ELK_EnEdge && b_left_dist_valid && lftEdgVld && b_no_off_road && b_left_range_valid &&
        b_left_edge_quality_valid;
    const bool b_left_ttlc_valid = checkLeftEdgeTtlcValid(
        config, lane_boundary.curLftDisToEdge, lane_boundary.lftEdgeTtlc, vehSpd, b_left_ttc_history_enabled, ttcMode);

    if (b_no_off_road) {
        left_edge_intervention_mask_ = left_edge_intervention_mask_ + 0x1;
    }

    if (b_left_ttlc_valid) {
        left_edge_intervention_mask_ = left_edge_intervention_mask_ + 0x2;
    }

    if (b_left_dist_valid) {
        left_edge_intervention_mask_ = left_edge_intervention_mask_ + 0x4;
    }

    if (lftEdgVld) {
        left_edge_intervention_mask_ = left_edge_intervention_mask_ + 0x8;
    }

    if (b_left_range_valid) {
        left_edge_intervention_mask_ = left_edge_intervention_mask_ + 0x10;
    }

    return config.k_ELK_EnEdge && b_left_ttlc_valid && b_left_dist_valid && lftEdgVld && 
        b_no_off_road && b_left_range_valid && b_left_edge_quality_valid;
}

bool ElkScenarioDecision::checkRightEdgeTtlcValid(
    const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode)
{
    const bool f_lowLatRt_near_right_edge =
        (dist < elk_cals_.k_ELK_ROR_LLR_RgtMaxIntvnDTE - k_right_curv_dist_offset_edge_) &&
        (dist > elk_cals_.k_ELK_ROR_MinIntvnDTE - k_right_curv_dist_offset_edge_) &&
        config.k_ELK_bUsLowRtNearTrg;
    const float nominal_threshold = elk_cals_.k_ELK_ROR_intvn_TTLC_right * config.k_ELK_ROR_TTLCScale;
    const float ttc_threshold = calcSpeedBasedTtcThreshold(
        vehSpd, elk_cals_.k_ELK_ROR_low_spd_intvn_TTLC, elk_cals_.k_ELK_ROR_intvn_TTLC_right) *
        config.k_ELK_ROR_TTLCScale;
    const bool f_ttlc_departure_right_edge =
        checkTtcDeparture(right_edge_ttc_history_, ttlc, ttc_threshold, historyEnabled, ttcMode);
    updateTtcDebugSignal(ttc_debug_snapshot_.right_ror,
                         ttlc,
                         dist,
                         ttc_threshold,
                         nominal_threshold,
                         historyEnabled,
                         f_lowLatRt_near_right_edge,
                         f_ttlc_departure_right_edge);
    if (ttcMode == TtcCheckMode::Activation) {
        updateTtcFalseTriggerDebugMask(
            right_edge_ttc_history_,
            ttlc,
            ttc_threshold,
            nominal_threshold,
            historyEnabled,
            f_lowLatRt_near_right_edge,
            f_ttlc_departure_right_edge,
            13U,
            19U,
            25U);
    }

    return f_lowLatRt_near_right_edge || f_ttlc_departure_right_edge;
}

bool ElkScenarioDecision::checkRightEdgeDistStable(float dist) const
{
    return (dist > elk_cals_.k_ELK_ROR_MinIntvnDTE) &&
        (dist < elk_cals_.k_ELK_ROR_RgtMaxIntvnDTE - k_right_curv_dist_offset_edge_);
}

bool ElkScenarioDecision::determineRightEdgeIntervention(const LaneBoundaryParameters &lane_boundary, 
                                                         const RoadEdge_t &right_edge, 
                                                         const GlobalConfig &config,
                                                         float vehSpd, 
                                                         bool rgtEdgVld,
                                                         TtcCheckMode ttcMode)
{
    right_edge_intervention_mask_ = 0x0;

    const bool b_no_off_road = !lane_boundary.runOffRoadLft && !lane_boundary.runOffRoadRgt;
    const bool b_right_dist_valid = checkRightEdgeDistStable(lane_boundary.curRgtDisToEdge);
    const bool b_right_range_valid = checkEdgeRangeValid(right_edge.LineViewRangeStart, right_edge.LineViewRangeEnd, vehSpd);
    const bool b_right_edge_quality_valid =
        !lane_boundary.rgtEdgeJump && !lane_boundary.rgtEdgeRangeShort && !lane_boundary.rgtEdgeLaneMismatch;
    const bool b_right_ttc_history_enabled =
        config.k_ELK_EnEdge && b_right_dist_valid && rgtEdgVld && b_no_off_road && b_right_range_valid &&
        b_right_edge_quality_valid;
    const bool b_right_ttlc_valid = checkRightEdgeTtlcValid(
        config, lane_boundary.curRgtDisToEdge, lane_boundary.rgtEdgeTtlc, vehSpd, b_right_ttc_history_enabled, ttcMode);

    if (b_no_off_road) {
        right_edge_intervention_mask_ = right_edge_intervention_mask_ + 0x1;
    }

    if (b_right_ttlc_valid) {
        right_edge_intervention_mask_ = right_edge_intervention_mask_ + 0x2;
    }

    if (b_right_dist_valid) {
        right_edge_intervention_mask_ = right_edge_intervention_mask_ + 0x4;
    }

    if (rgtEdgVld) {
        right_edge_intervention_mask_ = right_edge_intervention_mask_ + 0x8;
    }

    if (b_right_range_valid) {
        right_edge_intervention_mask_ = right_edge_intervention_mask_ + 0x10;
    }

    return config.k_ELK_EnEdge && b_right_ttlc_valid && b_right_dist_valid && rgtEdgVld && 
        b_no_off_road && b_right_range_valid && b_right_edge_quality_valid;
}

bool ElkScenarioDecision::checkEdgeRangeValid(float startRange, float endRange, float vehSpd) const
{
    const float endrange_thr = math::Clamp(
        vehSpd * elk_cals_.k_ELK_RE_RangeChk_deltaT_sec, elk_cals_.k_ELK_RE_minRange_m, elk_cals_.k_ELK_RE_maxRange_m);

    return (startRange < elk_cals_.k_ELK_RE_min_StartRange_m) && (endRange > endrange_thr);
}

bool ElkScenarioDecision::checkLeftSolidTtlcValid(
    const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode)
{
    const bool f_lowLatRt_near_left_marker =
        (dist < elk_cals_.k_ELK_SLD_LLR_LftMaxIntvnDTM - k_left_curv_dist_offset_marker_) &&
        (dist > elk_cals_.k_ELK_SLD_MinIntvnDTM - k_left_curv_dist_offset_marker_) &&
        config.k_ELK_bUsLowRtNearTrg;
    const float nominal_threshold = elk_cals_.k_ELK_SLD_intvn_TTLC_left * config.k_ELK_SLD_TTLCScale;
    const float ttc_threshold = calcSpeedBasedTtcThreshold(
        vehSpd, elk_cals_.k_ELK_SLD_low_spd_intvn_TTLC, elk_cals_.k_ELK_SLD_intvn_TTLC_left) *
        config.k_ELK_SLD_TTLCScale;
    const bool f_ttlc_departure_left_marker =
        checkTtcDeparture(left_solid_ttc_history_, ttlc, ttc_threshold, historyEnabled, ttcMode);
    updateTtcDebugSignal(ttc_debug_snapshot_.left_sld,
                         ttlc,
                         dist,
                         ttc_threshold,
                         nominal_threshold,
                         historyEnabled,
                         f_lowLatRt_near_left_marker,
                         f_ttlc_departure_left_marker);
    if (ttcMode == TtcCheckMode::Activation) {
        updateTtcFalseTriggerDebugMask(
            left_solid_ttc_history_,
            ttlc,
            ttc_threshold,
            nominal_threshold,
            historyEnabled,
            f_lowLatRt_near_left_marker,
            f_ttlc_departure_left_marker,
            14U,
            20U,
            26U);
    }

    return f_lowLatRt_near_left_marker || f_ttlc_departure_left_marker;
}

bool ElkScenarioDecision::checkLeftSolidDistStable(float dist) const
{
    return (dist > elk_cals_.k_ELK_SLD_MinIntvnDTM) &&
        (dist < elk_cals_.k_ELK_SLD_LftMaxIntvnDTM - k_left_curv_dist_offset_marker_);
}

bool ElkScenarioDecision::determineLeftSolidIntervention(const LaneBoundaryParameters &lane_boundary, 
                                                         const LaneMarker_t &left_marker, 
                                                         const GlobalConfig &config,
                                                         float vehSpd, 
                                                         bool lftMkrVld,
                                                         TtcCheckMode ttcMode)
{
    left_solid_intervention_mask_ = 0x0;

    const bool b_no_lane_change = !lane_boundary.lftLaneChange;
    const bool b_left_dist_valid = checkLeftSolidDistStable(lane_boundary.curLftDisToBdry);
    const bool b_left_range_valid = checkEdgeRangeValid(left_marker.LineViewRangeStart, left_marker.LineViewRangeEnd, vehSpd);
    const bool b_left_type_valid = (left_marker.LineType == 2) || (left_marker.LineType == 4) ||
        (left_marker.LineType == 5) || (left_marker.LineType == 7) || (left_marker.LineType == 9);
    const bool b_left_boundary_quality_valid = !lane_boundary.lftBdryJump && !lane_boundary.lftBdryRangeShort;
    const bool b_left_ttc_history_enabled =
        config.k_ELK_EnSld && b_left_dist_valid && b_no_lane_change && lftMkrVld &&
        b_left_range_valid && b_left_type_valid && b_left_boundary_quality_valid;
    const bool b_left_ttlc_valid = checkLeftSolidTtlcValid(
        config, lane_boundary.curLftDisToBdry, lane_boundary.lftBdryTtlc, vehSpd, b_left_ttc_history_enabled, ttcMode);

    if (b_no_lane_change) {
        left_solid_intervention_mask_ = left_solid_intervention_mask_ + 0x1;
    }

    if (b_left_ttlc_valid) {
        left_solid_intervention_mask_ = left_solid_intervention_mask_ + 0x2;
    }

    if (b_left_dist_valid) {
        left_solid_intervention_mask_ = left_solid_intervention_mask_ + 0x4;
    }

    if (lftMkrVld) {
        left_solid_intervention_mask_ = left_solid_intervention_mask_ + 0x8;
    }

    if (b_left_range_valid) { // 复用路沿函数及参数
        left_solid_intervention_mask_ = left_solid_intervention_mask_ + 0x10;
    }

    if (b_left_type_valid) {
        left_solid_intervention_mask_ = left_solid_intervention_mask_ + 0x20;
    }

    return config.k_ELK_EnSld && b_left_ttlc_valid && b_left_dist_valid && b_no_lane_change && lftMkrVld &&
        b_left_range_valid && b_left_type_valid && b_left_boundary_quality_valid;
}

bool ElkScenarioDecision::checkRightSolidTtlcValid(
    const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode)
{
    const bool f_lowLatRt_near_right_marker =
        (dist < elk_cals_.k_ELK_SLD_LLR_RgtMaxIntvnDTM - k_right_curv_dist_offset_marker_) &&
        (dist > elk_cals_.k_ELK_SLD_MinIntvnDTM - k_right_curv_dist_offset_marker_) &&
        config.k_ELK_bUsLowRtNearTrg;
    const float nominal_threshold = elk_cals_.k_ELK_SLD_intvn_TTLC_right * config.k_ELK_SLD_TTLCScale;
    const float ttc_threshold = calcSpeedBasedTtcThreshold(
        vehSpd, elk_cals_.k_ELK_SLD_low_spd_intvn_TTLC, elk_cals_.k_ELK_SLD_intvn_TTLC_right) *
        config.k_ELK_SLD_TTLCScale;
    const bool f_ttlc_departure_right_marker =
        checkTtcDeparture(right_solid_ttc_history_, ttlc, ttc_threshold, historyEnabled, ttcMode);
    updateTtcDebugSignal(ttc_debug_snapshot_.right_sld,
                         ttlc,
                         dist,
                         ttc_threshold,
                         nominal_threshold,
                         historyEnabled,
                         f_lowLatRt_near_right_marker,
                         f_ttlc_departure_right_marker);
    if (ttcMode == TtcCheckMode::Activation) {
        updateTtcFalseTriggerDebugMask(
            right_solid_ttc_history_,
            ttlc,
            ttc_threshold,
            nominal_threshold,
            historyEnabled,
            f_lowLatRt_near_right_marker,
            f_ttlc_departure_right_marker,
            15U,
            21U,
            27U);
    }

    return f_lowLatRt_near_right_marker || f_ttlc_departure_right_marker;
}

bool ElkScenarioDecision::checkRightSolidDistStable(float dist) const
{
    return (dist > elk_cals_.k_ELK_SLD_MinIntvnDTM) &&
        (dist < elk_cals_.k_ELK_SLD_RgtMaxIntvnDTM - k_right_curv_dist_offset_marker_);
}

bool ElkScenarioDecision::determineRightSolidIntervention(const LaneBoundaryParameters &lane_boundary, 
                                                         const LaneMarker_t &right_marker, 
                                                         const GlobalConfig &config,
                                                         float vehSpd, 
                                                         bool rgtMkrVld,
                                                         TtcCheckMode ttcMode)
{
    right_solid_intervention_mask_ = 0x0;
    
    const bool b_no_lane_change = !lane_boundary.rgtLaneChange;
    const bool b_right_dist_valid = checkRightSolidDistStable(lane_boundary.curRgtDisToBdry);
    const bool b_right_range_valid = checkEdgeRangeValid(right_marker.LineViewRangeStart, right_marker.LineViewRangeEnd, vehSpd);
    const bool b_right_type_valid = (right_marker.LineType == 2) || (right_marker.LineType == 4) ||
        (right_marker.LineType == 5) || (right_marker.LineType == 7) || (right_marker.LineType == 9);
    const bool b_right_boundary_quality_valid = !lane_boundary.rgtBdryJump && !lane_boundary.rgtBdryRangeShort;
    const bool b_right_ttc_history_enabled =
        config.k_ELK_EnSld && b_right_dist_valid && b_no_lane_change && rgtMkrVld &&
        b_right_range_valid && b_right_type_valid && b_right_boundary_quality_valid;
    const bool b_right_ttlc_valid = checkRightSolidTtlcValid(
        config, lane_boundary.curRgtDisToBdry, lane_boundary.rgtBdryTtlc, vehSpd, b_right_ttc_history_enabled, ttcMode);

    if (b_no_lane_change) {
        right_solid_intervention_mask_ = right_solid_intervention_mask_ + 0x1;
    }

    if (b_right_ttlc_valid) {
        right_solid_intervention_mask_ = right_solid_intervention_mask_ + 0x2;
    }

    if (b_right_dist_valid) {
        right_solid_intervention_mask_ = right_solid_intervention_mask_ + 0x4;
    }

    if (rgtMkrVld) {
        right_solid_intervention_mask_ = right_solid_intervention_mask_ + 0x8;
    }

    if (b_right_range_valid) {
        right_solid_intervention_mask_ = right_solid_intervention_mask_ + 0x10;
    }

    if (b_right_type_valid) {
        right_solid_intervention_mask_ = right_solid_intervention_mask_ + 0x20;
    }

    return config.k_ELK_EnSld && b_right_ttlc_valid && b_right_dist_valid && b_no_lane_change && rgtMkrVld &&
        b_right_range_valid && b_right_type_valid && b_right_boundary_quality_valid;
}

} // namespace elk
} // namespace active_safety
