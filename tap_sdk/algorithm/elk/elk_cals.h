#ifndef TAP_SDK_ALGORITHM_ELK_ELK_CALS_H_
#define TAP_SDK_ALGORITHM_ELK_ELK_CALS_H_
#include <array>
#include <cstdint>

namespace active_safety {
namespace elk {

struct ElkCal {
    float k_ELK_StepTime = 0.02F; // s
    // target selection
    float   k_lineconf_vld_thr          = 0.5F;
    float   k_default_lane_width        = 3.75F;
    float   k_oncom_long_thres          = 250.0F;
    float   k_oc_trk_heading            = 2.09F; // 120deg
    float   k_ot_trk_heading            = 1.0472F; // 60deg
    float   k_curvature_speed           = 8.0F;
    float   k_max_start_range_re        = 15.0F;
    float   k_range_lm                  = 15.0F;
    float   k_offset_small              = 0.4F;
    float   k_offset_big                = 4.0F;
    float   k_lm_pad_two                = 0.15F;
    float   k_lm_pad_one                = 0.425F;
    float   k_oc_ttc_thrd               = 1.5F;
    float   k_neighbor_factor           = 0.9F;
    float   k_neighbor_factor_truck     = 1.05F;
    float   k_oc_min_x                  = -5.0F;
    float   k_oc_min_speed              = -1.0F;
    float   k_ELK_OC_MinOncomingSpeed   = 1.0F;
    float   k_ot_min_speed              = 0.5F;
    float   k_ot_ttc_thrd               = 3.0F;
    float   k_ot_front_max_x            = 80.0F;
    float   k_ot_front_min_x            = -2.0F;
    float   k_ot_rear_max_x             = 0.0F;
    float   k_ot_rear_min_x             = -80.0F;
    float   k_ot_rear_hysteretic_x      = 5.0F;
    bool    k_enable_oncom_selection    = true;
    bool    k_enable_overtake_selection = true;
    uint8_t k_Max_Oncom_Pool_Trks       = 3;
    uint8_t k_Max_Overtake_Pool_Trks    = 5;
    uint8_t k_Max_Coast_Cycle           = 10;
    uint8_t k_Max_Candidate             = 3;
    // threat assessment
    float k_ELK_DiscreteInterval = 1.5F;
    float k_ELK_S_TTCThr_OC = 3.0F;
    float k_ELK_L_LatEdgThr_OC = 2.3F;
    float k_ELK_L_TTCThr_OC = 2.5F;
    float k_ELK_RightOC_S_TTCThr = 3.0F;
    float k_ELK_RightOC_L_LatEdgThr = 2.3F;
    float k_ELK_RightOC_L_TTCThr = 2.5F;
    float k_ELK_RightOC_S_FrontEdgeThrScale = 1.0F;
    float k_ELK_RightOC_MinOncomingSpeed = 1.0F; // Deprecated alias, use k_ELK_OC_MinOncomingSpeed for both sides.
    std::array<float, 9> k_ELK_S_FrontEdgeThr_OC_x{40, 60, 80, 100, 120, 140, 160, 180, 200};
    std::array<float, 9> k_ELK_S_FrontEdgeThr_OC_z{80, 80, 90, 110, 120, 130, 150, 150, 150};
    std::array<float, 12> k_ELK_S_LonEdgThr_OT_x{0, 35, 40, 50, 60, 70, 80, 90, 100, 110, 120, 140};
    std::array<float, 12> k_ELK_S_LonEdgThr_OT_z{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    float k_ELK_S_TTCThr_OT = 3;
    float k_ELK_L_LatEdgThr_OT = 2;
    float k_ELK_L_TTCThr_OT = 4.5;
    float k_ELK_LargeRearTargetLength = 10.0F;
    float k_ELK_TA_Collision_LongMargin = 0.5F;
    float k_ELK_TA_Collision_LatMargin = 0.2F;
    float k_ELK_TA_MaxPredictionTime = 5.0F;
    // state machine
    float k_EVP_yawrate_hi_thold = 0.25F;
    float k_EVP_yawrate_lo_thold = 0.2F;
    float k_EVP_yawrate_disable_time = 5.0F;
    float k_EVP_yawrate_enable_time = 1.0F;
    float k_EVP_brkPdPs_threshold_elk = 12.0F; // bar
    float k_EVP_brake_ped_pos_thold_HYS = 2.0F; // bar
    float k_EVP_brake_pedal_hold = 0.08F;
    float k_EVP_brake_suprress_hold = 1.0F;
    float k_EVP_accPdPs_inhibit_thr_elk = 30.0F;
    float k_EVP_accel_ped_suppress_hold = 1.0F; // sec
    float k_EVP_LatAccel_thold_up = 3.5F; // mpss
    float k_EVP_LatAccel_thold_lo = 3.5F; // mpss
    float k_EVP_HighAccel_suppress_hold = 3.0F; // sec
    float k_EVP_LonAccel_thold_up = 4.0F; // mpss
    float k_EVP_LonAccel_thold_lo = 3.5F; // mpss
    float k_EVP_LonDecel_thold_up = 5.0F; // mpss
    float k_EVP_LonDecel_thold_lo = 4.5F; // mpss
    float k_EVP_DrvTorq_thold_up = 3.5F; // Nm
    float k_EVP_DrvTorq_thold_lo = 3.0F; // Nm
    float k_EVP_hardsteer_suppress_hold = 3.0F;
    std::array<float, 7> k_ELK_ovrd_tq_thd_per_spd_x{40, 60, 84, 108, 132, 156, 180};
    std::array<float, 7> k_ELK_ovrd_tq_thd_per_spd_z{1.0, 1.5, 1.56, 1.66, 1.72, 1.76, 1.80};
    std::array<float, 7> k_ELK_LCT_ovrd_tq_thd_per_spd_x{40, 60, 84, 108, 132, 156, 180};
    std::array<float, 7> k_ELK_LCT_ovrd_tq_thd_per_spd_z{1.5, 1.5, 1.56, 1.66, 1.72, 1.76, 1.80};
    float k_ELK_DriHandsOvr_OnDlyTime = 0.02F;
    float k_ELK_DriHandsOvr_OffDlyTime = 1.0F;
    float k_ELK_LCT_DriHandsOvr_OffDlyTime = 0.5F;
    uint8_t k_ELK_DriHandsOvr_HistoryWindow = 10U;
    uint8_t k_ELK_DriHandsOvr_HistorySuppressCount = 6U;
    float k_EVP_LowSpd_AccelPedal_MinSpeedKph = 40.0F;
    float k_EVP_LowSpd_AccelPedal_MaxSpeedKph = 60.0F;
    float k_EVP_LowSpd_AccelPedal_Thr = 15.0F;
    float k_EVP_LowSpd_AccelPedal_OnDelayTime = 2.0F;
    uint8_t k_EVP_DriverIntent_HistoryFrameCount = 3U;
    float k_EVP_DriverIntent_ScoreThr = 0.9F;
    float k_EVP_DriverIntent_SteerWeight = 0.55F;
    float k_EVP_DriverIntent_PedalWeight = 0.45F;
    float k_EVP_DriverIntent_BrakePedalThr = 20.0F;
    float k_EVP_DriverIntent_OffDelayTime = 1.0F;
    uint32_t k_EVP_DriverIntent_Suprsn_Bit = 1U << 29U;
    uint32_t k_EVP_LCT_DriHandsOvr_Suprsn_Bit = 1U << 30U;
    float k_EVP_SteerAngle_thold_up = 90.0F; // deg
    float k_EVP_SteerAngle_thold_lo = 70.0F; // deg
    float k_EVP_StrAng_CR_suppress_hold = 3.0F; // s
    float k_EVP_StrAng_CR_threshold_HYS = 20.0F; // deg/s
    float k_EVP_StrAng_CR_hold = 8.0F; // s
    std::array<float, 5> k_EVP_StrAng_CR_thrd_x{60.0F, 80.0F, 120.0F, 150.0F, 180.0F};
    std::array<float, 5> k_EVP_StrAng_CR_thrd_z{60.0F, 60.0F, 60.0F, 60.0F, 60.0F};
    float k_EVP_drvrSprsn_hold_time = 1.0F; // s
    float k_ELK_lat_rate_thold_max = 1.2F; // m/s
    float k_ELK_ROR_lat_rate_thold_max = 1.2F; // m/s
    float k_ELK_lat_rate_thold_min = 1.2F; // m/s
    float k_ELK_ROR_lat_rate_thold_min = 1.2F; // m/s
    float k_ELK_ConIntervent_Time = 3.0F;
    float k_ELK_Intervention_MaxTime = 7.5F;
    float k_ELK_MIN_SPEED_HI = 50.0F;
    float k_ELK_MAX_SPEED_LO = 130.0F;
    float k_ELK_mkr_mature_time = 0.8F;
    float k_ELK_MAX_CURVATURE = 0.01F;
    float k_ELK_MAX_CURVATURE_OFF = 1.0F / 150.0F;
    float k_ELK_min_lane_width_enable_hi = 2.6F;
    float k_ELK_min_lane_width_enable_lo = 2.5F;
    float k_ELK_max_lane_width_enable_hi = 5.5F;
    float k_ELK_max_lane_width_enable_lo = 5.4F;
    float k_ELK_MIN_SPEED_LO = 45.0F;
    float k_ELK_MAX_SPEED_HI = 135.0F;
    std::array<float, 10> k_ELK_LfCurvDistOffst_mrgn_x{
        -0.01F, -0.0029F, -0.0017F, -0.0012F, -0.0006F, 0.0006F, 0.0012F, 0.0017F, 0.0029F, 0.01F}; //查表曲率左弯为负，右弯为正
    std::array<float, 10> k_ELK_LfCurvDistOffst_mrgn_z{
        0.03F, 0.03F, 0.03F, 0.03F, 0.03F, -0.1F, -0.12F, -0.15F, -0.15F, -0.15F}; //左偏需要对右弯减去offset放大阈值，提前触发
    std::array<float, 10> k_ELK_RtCurvDistOffst_mrgn_x{
        -0.01F, -0.0029F, -0.0017F, -0.0012F, -0.0006F, 0.0006F, 0.0012F, 0.0017F, 0.0029F, 0.01F}; //查表曲率左弯为负，右弯为正
    std::array<float, 10> k_ELK_RtCurvDistOffst_mrgn_z{
        -0.15F, -0.15F, -0.15F, -0.12F, -0.1F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F}; //右偏需要对左弯减去offset放大阈值，提前触发
    uint32_t k_EVP_Left_Suprsn_Mask_LCT = (201525247U & ~(1U << 6U)) | (1U << 29U) | (1U << 30U);
    uint32_t k_EVP_Right_Suprsn_Mask_LCT = (341844991U & ~(1U << 6U)) | (1U << 29U) | (1U << 30U);
    uint32_t k_EVP_Left_Suprsn_Mask_RE = 203168767U | (1U << 29U);
    uint32_t k_EVP_Right_Suprsn_Mask_RE = 394314751U | (1U << 29U);
    uint32_t k_EVP_Left_Suprsn_Mask_SLD = 201529343U | (1U << 29U);
    uint32_t k_EVP_Right_Suprsn_Mask_SLD = 341877759U | (1U << 29U);
    float k_EVP_hands_on_wheel_torque_hi = -0.5F;
    float k_EVP_hands_on_wheel_torque_lo = -1.0F; // 当前关闭脱手
    float k_EVP_handson_delay_time = 0.4F; // sec
    float k_EVP_handsoff_delay_time = 1.0F; // sec
    // intervention scerio
    float k_ELK_LCT_intvn_TTLC = 0.8F;
    float k_ELK_LCT_low_spd_intvn_TTLC = 0.65F;
    float k_ELK_ROR_low_spd_intvn_TTLC = 0.65F;
    float k_ELK_SLD_low_spd_intvn_TTLC = 0.65F;
    uint8_t k_ELK_TTC_InvalidToleranceFrames = 2U;
    float k_ELK_TTC_LowSpdStartKph = 40.0F;
    float k_ELK_TTC_LowSpdEndKph = 60.0F;
    float k_ELK_TTC_HighSpdRecoverKph = 80.0F;
    float k_ELK_LCT_LLR_LftMaxIntvnDTM = 0.15F;
    float k_ELK_LCT_MinIntvnDTM = -0.15F;
    float k_ELK_LCT_LftMaxIntvnDTM = 0.4F;
    float k_ELK_LCT_LftMinIntvnDTM = -0.2F;
    float k_ELK_LCT_LLR_RgtMaxIntvnDTM = 0.15F;
    float k_ELK_RgtMaxIntvnDTM = 0.4F;
    float k_ELK_RgtMinIntvnDTM = -0.2F;
    float k_ELK_ROR_intvn_TTLC_left = 1.05F;
    float k_ELK_ROR_LLR_LftMaxIntvnDTE = 0.5F;
    float k_ELK_ROR_MinIntvnDTE = -0.15F;
    float k_ELK_ROR_LftMaxIntvnDTE = 1.0F;
    float k_ELK_ROR_intvn_TTLC_right = 1.05F;
    float k_ELK_ROR_LLR_RgtMaxIntvnDTE = 0.5F;
    float k_ELK_ROR_RgtMaxIntvnDTE = 1.0F;
    float k_ELK_RE_min_StartRange_m = 10.0F;
    float k_ELK_RE_minRange_m = 10.0F;
    float k_ELK_RE_maxRange_m = 70.0F;
    float k_ELK_RE_RangeChk_deltaT_sec = 0.5F;
    float k_ELK_SLD_intvn_TTLC_left = 1.05F;
    float k_ELK_SLD_LLR_LftMaxIntvnDTM = 0.2F;
    float k_ELK_SLD_MinIntvnDTM = -0.15F;
    float k_ELK_SLD_LftMaxIntvnDTM = 1.0F;
    float k_ELK_SLD_intvn_TTLC_right = 1.05F;
    float k_ELK_SLD_LLR_RgtMaxIntvnDTM = 0.2F;
    float k_ELK_SLD_RgtMaxIntvnDTM = 1.0F;
    float k_ELK_Aligned_LMOffset = 0.7F;
    float k_ELK_Aligned_REOffset = 1.0F;
    float k_ELK_Aligned_C0_Thr = 0.12F;
    float k_ELK_Aligned_C1_Thr = 0.018F;
    float k_ELK_Aligned_OnDelayTime = 0.35F;
    float k_ELK_BoundaryJump_C0Thr = 0.5F;
    float k_ELK_BoundaryJump_C1Thr = 0.03F;
    float k_ELK_BoundaryJump_HoldTime = 0.3F;
    float k_ELK_Boundary_MinViewRangeEnd = 10.0F;
    float k_ELK_EdgeLaneMismatch_C1DiffThr = 0.05F;
    float k_ELK_EdgeLaneMismatch_EndGapThr = 0.5F;
    float k_ELK_EdgeLaneMismatch_MinEvalRange = 10.0F;
};

} // namespace elk
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_ELK_ELK_CALS_H_
