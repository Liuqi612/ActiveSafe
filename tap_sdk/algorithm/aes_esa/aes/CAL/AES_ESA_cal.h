#ifndef AES_ESA_CAL_H
#define AES_ESA_CAL_H
/****************************************************************************
 * Calibration file for AES_ESA production code.
 * DD uses version 5 of the bas file.
 * File Name: E:\user\AES_ESA_Module_0413_bak\AES_ESA_Module_0907\02_DataDictionary\AES\AES_ESA_cal.h
 * Created: 2026/9/14       10:59:36 
 * From Excel file: DataDictionary_AES_A02.xlsx
 * Calibration Values for project         
 * Calibrations for full application.
 * Set Description:         Initial Value
 ****************************************************************************/

#include "rtwtypes.h"

/*
 *  COMPONENT:  \AES_ESA
*/


#define AES_ESA_CAL_SIZE  10816 

typedef struct {
   uint16 k_AES_LaneWdth_filt_tau_str;
   uint16 k_AES_minROC_acceptable_str;
   uint16 k_AES_minROC_Hyst_str;
   uint8 k_AES_NrOfNcssryFrames_str;
   uint8 k_AES_NrOfNcssryIndcns_str;
   boolean k_AES_ObjDrvOffEnaFlg_str;
   boolean k_AES_SteerAgMdlEnaFlg_str;
   boolean k_AES_SysInitdLatCtrlEnaFlg_str;
   boolean k_AES_TRUE_str;
   boolean k_AES_UseMainSwtEnaFlg_str;
   boolean k_AES_UseLCKPIDController_str;
   boolean k_AES_UseVirtualData_str;
   float32 k_AES_mTot_str;
   float32 k_AES_m_str;
   float32 k_AES_DefaultTTC_str;
   float32 k_AES_ObjVirtX_str;
   float32 k_AES_SecondPlan_EndX_str;
   float32 k_AES_MaxDecelByAEB_str;
   float32 k_AES_MaxDecelRearObj_str;
   float32 k_AES_SteerWhlTqChgRateThd_str;
   float32 k_AES_EgoVDerivRateLim_str;
   float32 k_AES_ML_TIME_MSEC_str;
   float32 k_AES_Bx_str;
   float32 k_AES_MaxCritLatAccThd_str;
   float32 k_AES_OvrallSteerRat_str;
   float32 k_AES_By_str;
   float32 k_AES_Reset_EnTime_str;
   float32 k_AES_LLM_minRng_str;
   float32 k_AES_SteerWhlAgDzThd_str;
   float32 k_AES_CheckObsDistMinFront_str[ 16 ];
   float32 k_AES_CheckObsDistMinRear_str[ 16 ];
   float32 k_AES_EgoAOverGndObsvrL2_str;
   float32 k_AES_MaxLatAForPlanning_str;
   float32 k_AES_maxLnWdth_str;
   float32 k_AES_maxLnWdthHyst_str;
   float32 k_AES_maxSPPLnWdth_str;
   float32 k_AES_maxSPPLnWdthHyst_str;
   float32 k_AES_SteerWhlAgDifAbortThd_str;
   float32 k_AES_KntRiPosnY_str;
   float32 k_AES_Jz_str;
   float32 k_AES_KntLePosnX_str;
   float32 k_AES_KntRiPosnX_str;
   float32 k_AES_TorqueRate_Limit_str;
   float32 k_AES_IntvStrtMaxVelThd_str;
   float32 k_AES_IntvAbrtLatAccThd_str;
   float32 k_AES_IntvStrtMinVelThd_str;
   float32 k_AES_KntLePosnY_str;
   float32 k_AES_Functional_Torque_Limit_str;
   float32 k_AES_MaxIntvDurnThd_str;
   float32 k_AES_ttcTresholdBeep_str;
   float32 k_AES_l_str;
   float32 k_AES_WhlBase_str;
   float32 k_AES_ttcPartialBrake_str;
   float32 k_AES_LLM_maxA0_str;
   float32 k_AES_minSPPLnWdth_str;
   float32 k_AES_minSPPLnWdthHyst_str;
   float32 k_AES_ttcTresholdLLCD_str;
   float32 k_AES_minLnWdth_str;
   float32 k_AES_IntvStrtLatAccThd_str;
   float32 k_AES_MaxLatADiffThd_str;
   float32 k_AES_MaxLongADiffThd_str;
   float32 k_AES_MinCritLatAccThd_str;
   float32 k_AES_ObjVirtWidth_str;
   float32 k_AES_SteerWhlTqThd_str;
   float32 k_AES_minLnWdthHyst_str;
   float32 k_AES_lh_str;
   float32 k_AES_Cx_str;
   float32 k_AES_EgoWidth_str;
   float32 k_AES_ObjVirtY_str;
   float32 k_AES_SteerWhlAgSpdThd_str;
   float32 k_AES_lv_str;
   float32 k_AES_l_r_str;
   float32 k_AES_l_f_str;
   float32 k_AES_EgoAYMeanDevThd_str;
   float32 k_AES_LaneChangeFrontMinTTC_str;
   float32 k_AES_LaneChangeRearMinTTC_str;
   float32 k_AES_YPosDevThd_str;
   float32 k_AES_Cy_str;
   float32 k_AES_phiTraj_str;
   float32 k_AES_NotFsblCritVal_str;
   float32 k_AES_EgoAOverGndObsvrL1_str;
   float32 k_AES_EgoVMinToActvt_str;
   float32 k_AES_EgoVMinToCncl_str;
   float32 k_AES_ObjVirtIdx_str;
   float32 k_AES_ObjVirtRlsEgoVThd_str;
   float32 k_AES_SftyDstLat_str;
   float32 k_AES_TiStbMin_str;
   float32 k_AES_TimeGapDistFrontWeight_str;
   float32 k_AES_TimeGapDistRearWeight_str;
   float32 k_AES_mue_str;
   float32 k_AES_y_str;
   float32 k_AES_iBreak_str;
   float32 k_AES_SteerWhlAgMeanDeThd_str;
   float32 k_AES_h_str;
   float32 k_AES_A1Diff_str;
   float32 k_AES_SysInitdSteerThd_str;
   float32 k_AES_LnCetr_SP_A1Init_hys_str;
   float32 k_AES_LatADiffLowDurnThd_str;
   float32 k_AES_LnCetr_SP_A0Init_str;
   float32 k_AES_LongADiffLowDurnThd_str;
   float32 k_AES_RearObsTimeGap_str;
   float32 k_AES_LatTolrSigm_str;
   float32 k_AES_EgoAXDiffRateLim_str;
   float32 k_AES_FrontObsTimeGap_str;
   float32 k_AES_UndrStrCoeff_str;
   float32 k_AES_LaneWdth_RateLmt_str;
   float32 k_AES_LnCetr_SP_A0Init_hys_str;
   float32 k_AES_P_alpha_str;
   float32 k_AES_lambdaMax_str;
   float32 k_AES_LnCetr_SP_A1Init_str;
   float32 k_AES_ML_TIME_SEC_str;
   float32 k_AES_A1Diff_CnclTime_str;
   float32 k_AES_A1Diff_EnTime_str;
   float32 k_AES_Conf_CanclTime_str;
   float32 k_AES_Conf_EnTime_str;
   float32 k_AES_LnCetr_DlyTmInit_str;
   float32 k_AES_LnWdth_EnTime_str;
   float32 k_AES_NxtLnWdth_filt_tau_str;
   float32 k_AES_ROC_CanclTime_str;
   float32 k_AES_ROC_EnTime_str;
   float32 k_AES_SPPLnWdth_CnclTime_str;
   float32 k_AES_SPPLnWdth_EnTime_str;
   float32 k_AES_P_y_str;
   float32 k_AES_SMALL_NUMBER_str;
   float32 k_AES_ObjVirtAX_str;
   float32 k_AES_ObjVirtVX_str;
   float32 k_AES_Obs_l_hys_str;
   float32 k_AES_RearSecLaneLatArea_str;
   float32 k_AES_ZERO_str;
   float32 k_AES_Steering_Rate_Deadband_str[ 5 ];
   float32 k_AES_Damping_Torque_Gain_str[ 5 ];
   float32 k_AES_Proportinal_Gain_str[ 5 ];
   float32 k_AES_AMatrixPredAES_str[ 2 ][ 2 ];
   float32 k_AES_Derivative_Gain_str[ 5 ];
   float32 k_AES_lambdaRange_str[ 61 ];
   float32 k_AES_Setpoint_BrkPs_str[ 11 ];
   float32 k_AES_BMatrixPredAES_str[ 2 ][ 1 ];
   float32 k_AES_v_map_str[ 5 ];
   float32 k_AES_Feedforward_Map_str[ 11 ][ 5 ];
   float32 k_AES_Steering_Angle_Deadband_str[ 5 ];
   float32 k_AES_accelerationFullBrake_str;
   float32 k_AES_cAlphaR_str;
   float32 k_AES_cAlphaF_str;
   float32 k_AES_accelerationPartialBrake_str;
   float32 k_AES_cLambdaF_str;
   float32 k_AES_cLambdaR_str;
   float32 k_AES_c_h_str;
   float32 k_AES_c_v_str;
   float32 k_AES_Ey_str;
   float32 k_AES_deltaT_phi_str;
   float32 k_AES_durationPartialBrake_str;
   float32 k_AES_Ex_str;
   float32 k_AES_alphaMax_str;
   float32 k_AES_curv_str;
   float32 k_AES_IntvStrtLatAccDurThd_str;
   float32 k_AES_evasionTimeOffs_str;
   float32 k_AES_IntvAbrtLatAccDurThd_str;
   float32 k_AES_LMType_CanclTime_str;
   float32 k_AES_LMType_EnTime_str;
   float32 k_AES_FrontSecLaneLatArea_str;
   float32 k_AES_KntLeCrvt_str;
   float32 k_AES_KntLeYawAg_str;
   float32 k_AES_KntRiCrvt_str;
   float32 k_AES_KntRiYawAg_str;
   float32 k_AES_cAlpha_str[ 13 ];
   float32 k_AES_cLambda_str[ 27 ];
   float32 k_AES_dfydalpha_str[ 13 ][ 1 ];
   float32 k_AES_Integral_Gain_str[ 5 ];
   sint16 k_AES_LMConLo_str;
   sint16 k_AES_LMConfAccumuLmtHi_str;
   sint16 k_AES_LMConHi_str;
   sint16 k_AES_LMConfAccumuLmtLo_str;
   sint8 k_AES_BRKG_EMGY_BRKG_ALLWD_str;
   sint8 k_AES_BRKG_PTL_BRKG_ALLWD_str;
   sint8 k_AES_STEER_LAT_CTRL_ALLWD_str;
   sint8 k_AES_BRKG_CNCL_INTV_str;
   sint8 k_AES_EVASN_DIR_RIGHT_str;
   sint8 k_AES_STEER_CNCL_INTV_str;
   sint8 k_AES_BRKG_WARN_ALLWD_str;
   sint8 k_AES_EVASN_DIR_LEFT_str;
   sint8 k_AES_STEER_WARN_ALLWD_str;
   sint8 k_AES_BRKG_NO_INTV_STRT_ALLWD_str;
   sint8 k_AES_EVASN_DIR_NONE_str;
   sint8 k_AES_STEER_NO_INTV_STRT_ALLWD_str;
   boolean k_AES_FALSE_str;
   boolean k_AES_LgtCtrlrEnaFlg_str;
   boolean k_AES_ObjVirtRls_str;
   boolean k_AES_TestModVirtObjEnaFlg_str;
   boolean k_AES_UseSigmdPathEnaFlg_str;
   float32 k_AES_AEBTarDistance_str;
   boolean k_AES_UseVirtualAEB_str;
   uint8 k_AES_UseCrticalTTC_str;
   float32 k_AES_FinishDureTimeThd_str;
   boolean k_AES_UseRawLatYLogic_str;
   boolean k_AES_UseRealObsLatY_str;
   float32 k_AES_PlnMaxAyWeight_str;
   float32 k_AES_ObsLatYWeight_str;
   float32 k_AES_VehLatYWeight_str;
   boolean k_AES_UseSecondPlanner_str;
   boolean k_AES_VirtualMainSwitch_str;
   float32 k_AES_FirstPlanEndXMinThrd_str;
   float32 k_AES_FirstCompltXThrd_str;
   boolean k_AES_UseNextNextLaneC0_str;
   float32 k_AES_DyErrorFilterCon_str;
   float32 k_AES_DyDotErrorFilterCon_str;
   float32 k_AES_HeadErrorFilterCon_str;
   float32 k_AES_HeadDotErrorFilterCon_str;
   float32 k_AES_PhiDotErrorFilterCon_str;
   float32 k_AES_FFCurveFilterCon_str;
   float32 k_AES_LatCtrl_PosPID_Kp_Near_str;
   float32 k_AES_LatCtrl_PosPID_Kp_Far_str;
   float32 k_AES_LatCtrl_PosPID_KI_str;
   float32 k_AES_LatCtrl_PosPID_Kd_Near_str;
   float32 k_AES_LatCtrl_PosPID_Kd_Far_str;
   float32 k_AES_LatCtrl_HeadPID_Kp_str;
   float32 k_AES_LatCtrl_HeadPID_Kd_str;
   float32 k_AES_RatLmtFac_TorqCmd_Vspd_str[ 16 ];
   float32 k_AES_VspdBks_str[ 16 ];
   float32 k_AES_VspdBks_OnCome_str[ 11 ];
   float32 k_AES_CtrlPredTime_str[ 16 ];
   boolean k_AES_UseRealTimeEndPointY_str;
   boolean k_AES_UseRealTimeEndPointDY_str;
   boolean k_AES_UseRealTimeEndPointDDY_str;
   float32 k_AES_PathPredC2Thrd_str;
   float32 k_AES_PathPred_Time_str;
   float32 k_AES_CtrlStartPredTime_str[ 16 ];
   float32 k_AES_AySatisfyOnDelayTime_str;
   float32 k_AES_TrajColl_DiscreteDist_str;
   float32 k_AES_ActiveMaxDyThr_str;
   float32 k_AES_EgoVehicle_HalfWidth_str;
   float32 k_AES_SafetyDistanceThr_str;
   float32 k_AES_FeedForward_CurveAxis_str[ 17 ];
   float32 k_AES_FeedForward_SpdAxis_str[ 11 ];
   float32 k_AES_FeedForward_Coef_First_L_str[ 17 ][ 11 ];
   float32 k_AES_FeedForward_Coef_First_R_str[ 17 ][ 11 ];
   float32 k_AES_FeedForward_Coef_Sec_L_str[ 17 ][ 11 ];
   float32 k_AES_FeedForward_Coef_Sec_R_str[ 17 ][ 11 ];
   float32 k_AES_RadBks_str[ 25 ];
   float32 k_AES_Lat_PFac_Rad_str[ 25 ];
   float32 k_AES_Lat_IFac_Rad_str[ 25 ];
   float32 k_AES_Lat_DFac_Rad_str[ 25 ];
   float32 k_AES_Hed_PFac_Rad_str[ 25 ];
   float32 k_AES_Hed_DFac_Rad_str[ 25 ];
   boolean k_AES_DisableLeftTurning_str;
   boolean k_AES_DisableRightTurning_str;
   float32 k_AES_Dis_EgoRAxleToFBumper_str;
   float32 k_AES_EgoVehicle_Width_str;
   float32 k_AES_AverageTurnAccelMax_str;
   float32 k_AES_LastPntToStr_SafeDis_str;
   float32 k_AES_Obj_PredictedTime_str;
   float32 k_AES_CheckDriverAvoid_SafeDis_str;
   float32 k_AES_EnterEgoSpeed_MaxThr_str;
   float32 k_AES_EnterEgoSpeed_MinThr_str;
   float32 k_AES_ExitEgoSpeed_MaxThr_str;
   float32 k_AES_ExitEgoSpeed_MinThr_str;
   float32 k_AES_EnterEgoYawRate_Thr_str;
   float32 k_AES_ExitEgoYawRate_Thr_str;
   float32 k_AES_t_EnterEgoYawRate_OnDly_str;
   float32 k_AES_EnterEgoAy_Thr_str;
   float32 k_AES_t_EnterEgoAy_OnDly_str;
   float32 k_AES_ExitEgoAy_Thr_str;
   float32 k_AES_EnterEgoAccelPer_Thr_str;
   float32 k_AES_EnterEgoBrakePer_Thr_str;
   float32 k_AES_t_EnterPedalPer_OnDly_str;
   float32 k_AES_ExitEgoAccelPer_Thr_str;
   float32 k_AES_ExitEgoBrakePer_Thr_str;
   float32 k_AES_EnterStrAng_Thr_str;
   float32 k_AES_t_EnterStrAng_OnDly_str;
   float32 k_AES_ExitStrAng_Thr_str;
   float32 k_AES_t_ExitStrAng_OnDly_str;
   float32 k_AES_EnterTrajMaxAy_Thr_str;
   boolean k_AES_StateUseTrajMaxAyThr_str;
   float32 k_AES_EnterAES_HandTorq_Thr_str;
   float32 k_AES_EnterESA_HandTorq_Thr_str;
   float32 k_AES_t_DriverStrJudge_OnDly_str;
   float32 k_AES_AESAbortHTorq_SameDirThr_str;
   float32 k_AES_AESAbortHTorq_DiffDirThr_str;
   float32 k_AES_ESAAbortHTorq_SameDirThr_str;
   float32 k_AES_ESAAbortHTorq_DiffDirThr_str;
   float32 k_AES_AbortEgoAccelPer_Thr_str;
   float32 k_AES_AbortEgoBrakePer_Thr_str;
   float32 k_AES_AbortEgoYawRate_Thr_str;
   float32 k_AES_AbortEgoAy_Thr_str;
   float32 k_AES_AbortStrAng_Thr_str;
   float32 k_AES_t_AbortEgoAccelPer_OnDly_str;
   float32 k_AES_t_AbortEgoBrakePer_OnDly_str;
   float32 k_AES_t_AbortEgoYawRate_OnDly_str;
   float32 k_AES_t_AbortEgoAy_OnDly_str;
   float32 k_AES_t_AbortStrAng_OnDly_str;
   float32 k_AES_t_AbortHandTorq_OnDly_str;
   float32 k_AES_t_AbortESCActive_OnDly_str;
   float32 k_AES_CompletedC0_Thr_str;
   float32 k_AES_CompletedC1_Thr_str;
   float32 k_AES_t_CompletedC0C1_OnDly_str;
   float32 k_AES_t_DriverAvoidObj_OnDly_str;
   float32 k_AES_AngLimitMax_Vspd_str[ 16 ];
   float32 k_AES_Lat_KpKdSlopeLmt_str;
   float32 k_AES_Hed_KpKdSlopeLmt_str;
   float32 k_AES_t_FCWObstacleValid_OnDly_str;
   boolean k_AES_CsderEgoLen2PlanEndX_str;
   boolean k_AES_DefaultPassLaneLineCheck_str;
   boolean k_AES_DefaultPassObstacleCheck_str;
   float32 k_AES_StrWhlAngFilterCon_str;
   boolean k_AES_useFeedbackFirstPln_str;
   float32 k_AES_EnterEgoSpeed_MaxThr_VRU_str;
   float32 k_AES_EnterEgoSpeed_MinThr_VRU_str;
   float32 k_AES_ExitEgoSpeed_MaxThr_VRU_str;
   float32 k_AES_ExitEgoSpeed_MinThr_VRU_str;
   float32 k_AES_FeedForward_Coef_Second_str[ 17 ][ 11 ];
   float32 k_AES_FeedForwardGain_SlopeLmt_str;
   sint8 k_AES_AEBObjUseISOcoordinate_str;
   float32 k_AES_t_DriverQuickStr_OffDly_str;
   float32 k_AES_HostLaneObsOffset_str;
   float32 k_AES_FeedForward_First_ESA_L_str[ 17 ][ 11 ];
   float32 k_AES_FeedForward_First_ESA_R_str[ 17 ][ 11 ];
   float32 k_AES_FeedForward_Sec_ESA_L_str[ 17 ][ 11 ];
   float32 k_AES_FeedForward_Sec_ESA_R_str[ 17 ][ 11 ];
   float32 k_AES_t_TTCValid_OnDly_str;
   boolean k_AES_EnableAllTypeForAES_str;
   float32 k_AES_PlanAddDist_Static_str[ 16 ];
   float32 k_AES_PlanAddDist_SlowSpd_str[ 16 ];
   float32 k_AES_PlanAddDist_OnCome_str[ 11 ];
   float32 k_AES_LastPntBrk_TTC_OC_str[ 16 ];
   float32 k_AES_LastPntBrk_TTC_OC_ESA_str[ 16 ];
   float32 k_AES_MaxBrakeDecelProtect_str[ 16 ];
   float32 k_AES_MaxBrakeDecelProtect_ESA_str[ 16 ];
   float32 k_AES_FCWObsSlowSpd_OnDly_str;
   float32 k_AES_MaxBrakeDecelThr_str[ 16 ];
   float32 k_AES_MaxBrakeDecelThr_ESA_str[ 16 ];
   float32 k_AES_MaxBrkDeThr_SlowSpd_str[ 16 ];
   float32 k_AES_LeftLongSafeDistance_str;
   float32 k_AES_RightLongSafeDistance_str;
   float32 k_AES_t_ActiveMaxTimeThr_str[ 16 ];
   float32 k_AES_ObjFilterLonMaxTTC_str;
   float32 k_AES_DriverStrJudge_AngSpdThr_str[ 16 ];
   float32 k_AES_DriverStrJudge_AngThr_str[ 16 ];
   float32 k_AES_ObjOverLapLatThrsd_str;
   boolean k_AES_DisableESAObj_str;
   float32 k_AES_FCWObstacleLatOverLap_str;
   float32 k_AES_FCWObstacleLatVel_str;
   float32 k_AES_RoadEdgeValid_MaxThd_str;
   float32 k_AES_RoadEdgeValid_MinThd_str;
   float32 k_AES_NoLaneLine_LatMoveThd_str;
   uint8 k_AES_NoLaneLine_Flag_str;
   float32 k_AES_CTL_heading_spd_str[ 10 ];
   float32 k_AES_CTL_heading_error_factor_str[ 10 ];
   float32 k_AES_FCWObstacleLatOverLap_AES_str;
} AES_ESA_cal_T;

#define AES_ESA_START_SEC_CAL_UNSPECIFIED
#include "MemMap.h"
extern const AES_ESA_cal_T AES_ESA_Cal_DF_V;
#define AES_ESA_STOP_SEC_CAL_UNSPECIFIED
#include "MemMap.h"
/* Access Macros for the structure elements. Please note that application
* does not use data flash memory directly and uses the RAM copy of data flash.Though
* following macros start with K_ they actually point to RAM image of calibrations.
*/

#define k_AES_LaneWdth_filt_tau    (AES_ESA_Cal_DF_V.k_AES_LaneWdth_filt_tau_str)
#define k_AES_minROC_acceptable    (AES_ESA_Cal_DF_V.k_AES_minROC_acceptable_str)
#define k_AES_minROC_Hyst    (AES_ESA_Cal_DF_V.k_AES_minROC_Hyst_str)
#define k_AES_NrOfNcssryFrames    (AES_ESA_Cal_DF_V.k_AES_NrOfNcssryFrames_str)
#define k_AES_NrOfNcssryIndcns    (AES_ESA_Cal_DF_V.k_AES_NrOfNcssryIndcns_str)
#define k_AES_ObjDrvOffEnaFlg    (AES_ESA_Cal_DF_V.k_AES_ObjDrvOffEnaFlg_str)
#define k_AES_SteerAgMdlEnaFlg    (AES_ESA_Cal_DF_V.k_AES_SteerAgMdlEnaFlg_str)
#define k_AES_SysInitdLatCtrlEnaFlg    (AES_ESA_Cal_DF_V.k_AES_SysInitdLatCtrlEnaFlg_str)
#define k_AES_TRUE    (AES_ESA_Cal_DF_V.k_AES_TRUE_str)
#define k_AES_UseMainSwtEnaFlg    (AES_ESA_Cal_DF_V.k_AES_UseMainSwtEnaFlg_str)
#define k_AES_UseLCKPIDController    (AES_ESA_Cal_DF_V.k_AES_UseLCKPIDController_str)
#define k_AES_UseVirtualData    (AES_ESA_Cal_DF_V.k_AES_UseVirtualData_str)
#define k_AES_mTot    (AES_ESA_Cal_DF_V.k_AES_mTot_str)
#define k_AES_m    (AES_ESA_Cal_DF_V.k_AES_m_str)
#define k_AES_DefaultTTC    (AES_ESA_Cal_DF_V.k_AES_DefaultTTC_str)
#define k_AES_ObjVirtX    (AES_ESA_Cal_DF_V.k_AES_ObjVirtX_str)
#define k_AES_SecondPlan_EndX    (AES_ESA_Cal_DF_V.k_AES_SecondPlan_EndX_str)
#define k_AES_MaxDecelByAEB    (AES_ESA_Cal_DF_V.k_AES_MaxDecelByAEB_str)
#define k_AES_MaxDecelRearObj    (AES_ESA_Cal_DF_V.k_AES_MaxDecelRearObj_str)
#define k_AES_SteerWhlTqChgRateThd    (AES_ESA_Cal_DF_V.k_AES_SteerWhlTqChgRateThd_str)
#define k_AES_EgoVDerivRateLim    (AES_ESA_Cal_DF_V.k_AES_EgoVDerivRateLim_str)
#define k_AES_ML_TIME_MSEC    (AES_ESA_Cal_DF_V.k_AES_ML_TIME_MSEC_str)
#define k_AES_Bx    (AES_ESA_Cal_DF_V.k_AES_Bx_str)
#define k_AES_MaxCritLatAccThd    (AES_ESA_Cal_DF_V.k_AES_MaxCritLatAccThd_str)
#define k_AES_OvrallSteerRat    (AES_ESA_Cal_DF_V.k_AES_OvrallSteerRat_str)
#define k_AES_By    (AES_ESA_Cal_DF_V.k_AES_By_str)
#define k_AES_Reset_EnTime    (AES_ESA_Cal_DF_V.k_AES_Reset_EnTime_str)
#define k_AES_LLM_minRng    (AES_ESA_Cal_DF_V.k_AES_LLM_minRng_str)
#define k_AES_SteerWhlAgDzThd    (AES_ESA_Cal_DF_V.k_AES_SteerWhlAgDzThd_str)
#define k_AES_CheckObsDistMinFront    (AES_ESA_Cal_DF_V.k_AES_CheckObsDistMinFront_str)
#define k_AES_CheckObsDistMinRear    (AES_ESA_Cal_DF_V.k_AES_CheckObsDistMinRear_str)
#define k_AES_EgoAOverGndObsvrL2    (AES_ESA_Cal_DF_V.k_AES_EgoAOverGndObsvrL2_str)
#define k_AES_MaxLatAForPlanning    (AES_ESA_Cal_DF_V.k_AES_MaxLatAForPlanning_str)
#define k_AES_maxLnWdth    (AES_ESA_Cal_DF_V.k_AES_maxLnWdth_str)
#define k_AES_maxLnWdthHyst    (AES_ESA_Cal_DF_V.k_AES_maxLnWdthHyst_str)
#define k_AES_maxSPPLnWdth    (AES_ESA_Cal_DF_V.k_AES_maxSPPLnWdth_str)
#define k_AES_maxSPPLnWdthHyst    (AES_ESA_Cal_DF_V.k_AES_maxSPPLnWdthHyst_str)
#define k_AES_SteerWhlAgDifAbortThd    (AES_ESA_Cal_DF_V.k_AES_SteerWhlAgDifAbortThd_str)
#define k_AES_KntRiPosnY    (AES_ESA_Cal_DF_V.k_AES_KntRiPosnY_str)
#define k_AES_Jz    (AES_ESA_Cal_DF_V.k_AES_Jz_str)
#define k_AES_KntLePosnX    (AES_ESA_Cal_DF_V.k_AES_KntLePosnX_str)
#define k_AES_KntRiPosnX    (AES_ESA_Cal_DF_V.k_AES_KntRiPosnX_str)
#define k_AES_TorqueRate_Limit    (AES_ESA_Cal_DF_V.k_AES_TorqueRate_Limit_str)
#define k_AES_IntvStrtMaxVelThd    (AES_ESA_Cal_DF_V.k_AES_IntvStrtMaxVelThd_str)
#define k_AES_IntvAbrtLatAccThd    (AES_ESA_Cal_DF_V.k_AES_IntvAbrtLatAccThd_str)
#define k_AES_IntvStrtMinVelThd    (AES_ESA_Cal_DF_V.k_AES_IntvStrtMinVelThd_str)
#define k_AES_KntLePosnY    (AES_ESA_Cal_DF_V.k_AES_KntLePosnY_str)
#define k_AES_Functional_Torque_Limit    (AES_ESA_Cal_DF_V.k_AES_Functional_Torque_Limit_str)
#define k_AES_MaxIntvDurnThd    (AES_ESA_Cal_DF_V.k_AES_MaxIntvDurnThd_str)
#define k_AES_ttcTresholdBeep    (AES_ESA_Cal_DF_V.k_AES_ttcTresholdBeep_str)
#define k_AES_l    (AES_ESA_Cal_DF_V.k_AES_l_str)
#define k_AES_WhlBase    (AES_ESA_Cal_DF_V.k_AES_WhlBase_str)
#define k_AES_ttcPartialBrake    (AES_ESA_Cal_DF_V.k_AES_ttcPartialBrake_str)
#define k_AES_LLM_maxA0    (AES_ESA_Cal_DF_V.k_AES_LLM_maxA0_str)
#define k_AES_minSPPLnWdth    (AES_ESA_Cal_DF_V.k_AES_minSPPLnWdth_str)
#define k_AES_minSPPLnWdthHyst    (AES_ESA_Cal_DF_V.k_AES_minSPPLnWdthHyst_str)
#define k_AES_ttcTresholdLLCD    (AES_ESA_Cal_DF_V.k_AES_ttcTresholdLLCD_str)
#define k_AES_minLnWdth    (AES_ESA_Cal_DF_V.k_AES_minLnWdth_str)
#define k_AES_IntvStrtLatAccThd    (AES_ESA_Cal_DF_V.k_AES_IntvStrtLatAccThd_str)
#define k_AES_MaxLatADiffThd    (AES_ESA_Cal_DF_V.k_AES_MaxLatADiffThd_str)
#define k_AES_MaxLongADiffThd    (AES_ESA_Cal_DF_V.k_AES_MaxLongADiffThd_str)
#define k_AES_MinCritLatAccThd    (AES_ESA_Cal_DF_V.k_AES_MinCritLatAccThd_str)
#define k_AES_ObjVirtWidth    (AES_ESA_Cal_DF_V.k_AES_ObjVirtWidth_str)
#define k_AES_SteerWhlTqThd    (AES_ESA_Cal_DF_V.k_AES_SteerWhlTqThd_str)
#define k_AES_minLnWdthHyst    (AES_ESA_Cal_DF_V.k_AES_minLnWdthHyst_str)
#define k_AES_lh    (AES_ESA_Cal_DF_V.k_AES_lh_str)
#define k_AES_Cx    (AES_ESA_Cal_DF_V.k_AES_Cx_str)
#define k_AES_EgoWidth    (AES_ESA_Cal_DF_V.k_AES_EgoWidth_str)
#define k_AES_ObjVirtY    (AES_ESA_Cal_DF_V.k_AES_ObjVirtY_str)
#define k_AES_SteerWhlAgSpdThd    (AES_ESA_Cal_DF_V.k_AES_SteerWhlAgSpdThd_str)
#define k_AES_lv    (AES_ESA_Cal_DF_V.k_AES_lv_str)
#define k_AES_l_r    (AES_ESA_Cal_DF_V.k_AES_l_r_str)
#define k_AES_l_f    (AES_ESA_Cal_DF_V.k_AES_l_f_str)
#define k_AES_EgoAYMeanDevThd    (AES_ESA_Cal_DF_V.k_AES_EgoAYMeanDevThd_str)
#define k_AES_LaneChangeFrontMinTTC    (AES_ESA_Cal_DF_V.k_AES_LaneChangeFrontMinTTC_str)
#define k_AES_LaneChangeRearMinTTC    (AES_ESA_Cal_DF_V.k_AES_LaneChangeRearMinTTC_str)
#define k_AES_YPosDevThd    (AES_ESA_Cal_DF_V.k_AES_YPosDevThd_str)
#define k_AES_Cy    (AES_ESA_Cal_DF_V.k_AES_Cy_str)
#define k_AES_phiTraj    (AES_ESA_Cal_DF_V.k_AES_phiTraj_str)
#define k_AES_NotFsblCritVal    (AES_ESA_Cal_DF_V.k_AES_NotFsblCritVal_str)
#define k_AES_EgoAOverGndObsvrL1    (AES_ESA_Cal_DF_V.k_AES_EgoAOverGndObsvrL1_str)
#define k_AES_EgoVMinToActvt    (AES_ESA_Cal_DF_V.k_AES_EgoVMinToActvt_str)
#define k_AES_EgoVMinToCncl    (AES_ESA_Cal_DF_V.k_AES_EgoVMinToCncl_str)
#define k_AES_ObjVirtIdx    (AES_ESA_Cal_DF_V.k_AES_ObjVirtIdx_str)
#define k_AES_ObjVirtRlsEgoVThd    (AES_ESA_Cal_DF_V.k_AES_ObjVirtRlsEgoVThd_str)
#define k_AES_SftyDstLat    (AES_ESA_Cal_DF_V.k_AES_SftyDstLat_str)
#define k_AES_TiStbMin    (AES_ESA_Cal_DF_V.k_AES_TiStbMin_str)
#define k_AES_TimeGapDistFrontWeight    (AES_ESA_Cal_DF_V.k_AES_TimeGapDistFrontWeight_str)
#define k_AES_TimeGapDistRearWeight    (AES_ESA_Cal_DF_V.k_AES_TimeGapDistRearWeight_str)
#define k_AES_mue    (AES_ESA_Cal_DF_V.k_AES_mue_str)
#define k_AES_y    (AES_ESA_Cal_DF_V.k_AES_y_str)
#define k_AES_iBreak    (AES_ESA_Cal_DF_V.k_AES_iBreak_str)
#define k_AES_SteerWhlAgMeanDeThd    (AES_ESA_Cal_DF_V.k_AES_SteerWhlAgMeanDeThd_str)
#define k_AES_h    (AES_ESA_Cal_DF_V.k_AES_h_str)
#define k_AES_A1Diff    (AES_ESA_Cal_DF_V.k_AES_A1Diff_str)
#define k_AES_SysInitdSteerThd    (AES_ESA_Cal_DF_V.k_AES_SysInitdSteerThd_str)
#define k_AES_LnCetr_SP_A1Init_hys    (AES_ESA_Cal_DF_V.k_AES_LnCetr_SP_A1Init_hys_str)
#define k_AES_LatADiffLowDurnThd    (AES_ESA_Cal_DF_V.k_AES_LatADiffLowDurnThd_str)
#define k_AES_LnCetr_SP_A0Init    (AES_ESA_Cal_DF_V.k_AES_LnCetr_SP_A0Init_str)
#define k_AES_LongADiffLowDurnThd    (AES_ESA_Cal_DF_V.k_AES_LongADiffLowDurnThd_str)
#define k_AES_RearObsTimeGap    (AES_ESA_Cal_DF_V.k_AES_RearObsTimeGap_str)
#define k_AES_LatTolrSigm    (AES_ESA_Cal_DF_V.k_AES_LatTolrSigm_str)
#define k_AES_EgoAXDiffRateLim    (AES_ESA_Cal_DF_V.k_AES_EgoAXDiffRateLim_str)
#define k_AES_FrontObsTimeGap    (AES_ESA_Cal_DF_V.k_AES_FrontObsTimeGap_str)
#define k_AES_UndrStrCoeff    (AES_ESA_Cal_DF_V.k_AES_UndrStrCoeff_str)
#define k_AES_LaneWdth_RateLmt    (AES_ESA_Cal_DF_V.k_AES_LaneWdth_RateLmt_str)
#define k_AES_LnCetr_SP_A0Init_hys    (AES_ESA_Cal_DF_V.k_AES_LnCetr_SP_A0Init_hys_str)
#define k_AES_P_alpha    (AES_ESA_Cal_DF_V.k_AES_P_alpha_str)
#define k_AES_lambdaMax    (AES_ESA_Cal_DF_V.k_AES_lambdaMax_str)
#define k_AES_LnCetr_SP_A1Init    (AES_ESA_Cal_DF_V.k_AES_LnCetr_SP_A1Init_str)
#define k_AES_ML_TIME_SEC    (AES_ESA_Cal_DF_V.k_AES_ML_TIME_SEC_str)
#define k_AES_A1Diff_CnclTime    (AES_ESA_Cal_DF_V.k_AES_A1Diff_CnclTime_str)
#define k_AES_A1Diff_EnTime    (AES_ESA_Cal_DF_V.k_AES_A1Diff_EnTime_str)
#define k_AES_Conf_CanclTime    (AES_ESA_Cal_DF_V.k_AES_Conf_CanclTime_str)
#define k_AES_Conf_EnTime    (AES_ESA_Cal_DF_V.k_AES_Conf_EnTime_str)
#define k_AES_LnCetr_DlyTmInit    (AES_ESA_Cal_DF_V.k_AES_LnCetr_DlyTmInit_str)
#define k_AES_LnWdth_EnTime    (AES_ESA_Cal_DF_V.k_AES_LnWdth_EnTime_str)
#define k_AES_NxtLnWdth_filt_tau    (AES_ESA_Cal_DF_V.k_AES_NxtLnWdth_filt_tau_str)
#define k_AES_ROC_CanclTime    (AES_ESA_Cal_DF_V.k_AES_ROC_CanclTime_str)
#define k_AES_ROC_EnTime    (AES_ESA_Cal_DF_V.k_AES_ROC_EnTime_str)
#define k_AES_SPPLnWdth_CnclTime    (AES_ESA_Cal_DF_V.k_AES_SPPLnWdth_CnclTime_str)
#define k_AES_SPPLnWdth_EnTime    (AES_ESA_Cal_DF_V.k_AES_SPPLnWdth_EnTime_str)
#define k_AES_P_y    (AES_ESA_Cal_DF_V.k_AES_P_y_str)
#define k_AES_SMALL_NUMBER    (AES_ESA_Cal_DF_V.k_AES_SMALL_NUMBER_str)
#define k_AES_ObjVirtAX    (AES_ESA_Cal_DF_V.k_AES_ObjVirtAX_str)
#define k_AES_ObjVirtVX    (AES_ESA_Cal_DF_V.k_AES_ObjVirtVX_str)
#define k_AES_Obs_l_hys    (AES_ESA_Cal_DF_V.k_AES_Obs_l_hys_str)
#define k_AES_RearSecLaneLatArea    (AES_ESA_Cal_DF_V.k_AES_RearSecLaneLatArea_str)
#define k_AES_ZERO    (AES_ESA_Cal_DF_V.k_AES_ZERO_str)
#define k_AES_Steering_Rate_Deadband    (AES_ESA_Cal_DF_V.k_AES_Steering_Rate_Deadband_str)
#define k_AES_Damping_Torque_Gain    (AES_ESA_Cal_DF_V.k_AES_Damping_Torque_Gain_str)
#define k_AES_Proportinal_Gain    (AES_ESA_Cal_DF_V.k_AES_Proportinal_Gain_str)
#define k_AES_AMatrixPredAES    (AES_ESA_Cal_DF_V.k_AES_AMatrixPredAES_str)
#define k_AES_Derivative_Gain    (AES_ESA_Cal_DF_V.k_AES_Derivative_Gain_str)
#define k_AES_lambdaRange    (AES_ESA_Cal_DF_V.k_AES_lambdaRange_str)
#define k_AES_Setpoint_BrkPs    (AES_ESA_Cal_DF_V.k_AES_Setpoint_BrkPs_str)
#define k_AES_BMatrixPredAES    (AES_ESA_Cal_DF_V.k_AES_BMatrixPredAES_str)
#define k_AES_v_map    (AES_ESA_Cal_DF_V.k_AES_v_map_str)
#define k_AES_Feedforward_Map    (AES_ESA_Cal_DF_V.k_AES_Feedforward_Map_str)
#define k_AES_Steering_Angle_Deadband    (AES_ESA_Cal_DF_V.k_AES_Steering_Angle_Deadband_str)
#define k_AES_accelerationFullBrake    (AES_ESA_Cal_DF_V.k_AES_accelerationFullBrake_str)
#define k_AES_cAlphaR    (AES_ESA_Cal_DF_V.k_AES_cAlphaR_str)
#define k_AES_cAlphaF    (AES_ESA_Cal_DF_V.k_AES_cAlphaF_str)
#define k_AES_accelerationPartialBrake    (AES_ESA_Cal_DF_V.k_AES_accelerationPartialBrake_str)
#define k_AES_cLambdaF    (AES_ESA_Cal_DF_V.k_AES_cLambdaF_str)
#define k_AES_cLambdaR    (AES_ESA_Cal_DF_V.k_AES_cLambdaR_str)
#define k_AES_c_h    (AES_ESA_Cal_DF_V.k_AES_c_h_str)
#define k_AES_c_v    (AES_ESA_Cal_DF_V.k_AES_c_v_str)
#define k_AES_Ey    (AES_ESA_Cal_DF_V.k_AES_Ey_str)
#define k_AES_deltaT_phi    (AES_ESA_Cal_DF_V.k_AES_deltaT_phi_str)
#define k_AES_durationPartialBrake    (AES_ESA_Cal_DF_V.k_AES_durationPartialBrake_str)
#define k_AES_Ex    (AES_ESA_Cal_DF_V.k_AES_Ex_str)
#define k_AES_alphaMax    (AES_ESA_Cal_DF_V.k_AES_alphaMax_str)
#define k_AES_curv    (AES_ESA_Cal_DF_V.k_AES_curv_str)
#define k_AES_IntvStrtLatAccDurThd    (AES_ESA_Cal_DF_V.k_AES_IntvStrtLatAccDurThd_str)
#define k_AES_evasionTimeOffs    (AES_ESA_Cal_DF_V.k_AES_evasionTimeOffs_str)
#define k_AES_IntvAbrtLatAccDurThd    (AES_ESA_Cal_DF_V.k_AES_IntvAbrtLatAccDurThd_str)
#define k_AES_LMType_CanclTime    (AES_ESA_Cal_DF_V.k_AES_LMType_CanclTime_str)
#define k_AES_LMType_EnTime    (AES_ESA_Cal_DF_V.k_AES_LMType_EnTime_str)
#define k_AES_FrontSecLaneLatArea    (AES_ESA_Cal_DF_V.k_AES_FrontSecLaneLatArea_str)
#define k_AES_KntLeCrvt    (AES_ESA_Cal_DF_V.k_AES_KntLeCrvt_str)
#define k_AES_KntLeYawAg    (AES_ESA_Cal_DF_V.k_AES_KntLeYawAg_str)
#define k_AES_KntRiCrvt    (AES_ESA_Cal_DF_V.k_AES_KntRiCrvt_str)
#define k_AES_KntRiYawAg    (AES_ESA_Cal_DF_V.k_AES_KntRiYawAg_str)
#define k_AES_cAlpha    (AES_ESA_Cal_DF_V.k_AES_cAlpha_str)
#define k_AES_cLambda    (AES_ESA_Cal_DF_V.k_AES_cLambda_str)
#define k_AES_dfydalpha    (AES_ESA_Cal_DF_V.k_AES_dfydalpha_str)
#define k_AES_Integral_Gain    (AES_ESA_Cal_DF_V.k_AES_Integral_Gain_str)
#define k_AES_LMConLo    (AES_ESA_Cal_DF_V.k_AES_LMConLo_str)
#define k_AES_LMConfAccumuLmtHi    (AES_ESA_Cal_DF_V.k_AES_LMConfAccumuLmtHi_str)
#define k_AES_LMConHi    (AES_ESA_Cal_DF_V.k_AES_LMConHi_str)
#define k_AES_LMConfAccumuLmtLo    (AES_ESA_Cal_DF_V.k_AES_LMConfAccumuLmtLo_str)
#define k_AES_BRKG_EMGY_BRKG_ALLWD    (AES_ESA_Cal_DF_V.k_AES_BRKG_EMGY_BRKG_ALLWD_str)
#define k_AES_BRKG_PTL_BRKG_ALLWD    (AES_ESA_Cal_DF_V.k_AES_BRKG_PTL_BRKG_ALLWD_str)
#define k_AES_STEER_LAT_CTRL_ALLWD    (AES_ESA_Cal_DF_V.k_AES_STEER_LAT_CTRL_ALLWD_str)
#define k_AES_BRKG_CNCL_INTV    (AES_ESA_Cal_DF_V.k_AES_BRKG_CNCL_INTV_str)
#define k_AES_EVASN_DIR_RIGHT    (AES_ESA_Cal_DF_V.k_AES_EVASN_DIR_RIGHT_str)
#define k_AES_STEER_CNCL_INTV    (AES_ESA_Cal_DF_V.k_AES_STEER_CNCL_INTV_str)
#define k_AES_BRKG_WARN_ALLWD    (AES_ESA_Cal_DF_V.k_AES_BRKG_WARN_ALLWD_str)
#define k_AES_EVASN_DIR_LEFT    (AES_ESA_Cal_DF_V.k_AES_EVASN_DIR_LEFT_str)
#define k_AES_STEER_WARN_ALLWD    (AES_ESA_Cal_DF_V.k_AES_STEER_WARN_ALLWD_str)
#define k_AES_BRKG_NO_INTV_STRT_ALLWD    (AES_ESA_Cal_DF_V.k_AES_BRKG_NO_INTV_STRT_ALLWD_str)
#define k_AES_EVASN_DIR_NONE    (AES_ESA_Cal_DF_V.k_AES_EVASN_DIR_NONE_str)
#define k_AES_STEER_NO_INTV_STRT_ALLWD    (AES_ESA_Cal_DF_V.k_AES_STEER_NO_INTV_STRT_ALLWD_str)
#define k_AES_FALSE    (AES_ESA_Cal_DF_V.k_AES_FALSE_str)
#define k_AES_LgtCtrlrEnaFlg    (AES_ESA_Cal_DF_V.k_AES_LgtCtrlrEnaFlg_str)
#define k_AES_ObjVirtRls    (AES_ESA_Cal_DF_V.k_AES_ObjVirtRls_str)
#define k_AES_TestModVirtObjEnaFlg    (AES_ESA_Cal_DF_V.k_AES_TestModVirtObjEnaFlg_str)
#define k_AES_UseSigmdPathEnaFlg    (AES_ESA_Cal_DF_V.k_AES_UseSigmdPathEnaFlg_str)
#define k_AES_AEBTarDistance    (AES_ESA_Cal_DF_V.k_AES_AEBTarDistance_str)
#define k_AES_UseVirtualAEB    (AES_ESA_Cal_DF_V.k_AES_UseVirtualAEB_str)
#define k_AES_UseCrticalTTC    (AES_ESA_Cal_DF_V.k_AES_UseCrticalTTC_str)
#define k_AES_FinishDureTimeThd    (AES_ESA_Cal_DF_V.k_AES_FinishDureTimeThd_str)
#define k_AES_UseRawLatYLogic    (AES_ESA_Cal_DF_V.k_AES_UseRawLatYLogic_str)
#define k_AES_UseRealObsLatY    (AES_ESA_Cal_DF_V.k_AES_UseRealObsLatY_str)
#define k_AES_PlnMaxAyWeight    (AES_ESA_Cal_DF_V.k_AES_PlnMaxAyWeight_str)
#define k_AES_ObsLatYWeight    (AES_ESA_Cal_DF_V.k_AES_ObsLatYWeight_str)
#define k_AES_VehLatYWeight    (AES_ESA_Cal_DF_V.k_AES_VehLatYWeight_str)
#define k_AES_UseSecondPlanner    (AES_ESA_Cal_DF_V.k_AES_UseSecondPlanner_str)
#define k_AES_VirtualMainSwitch    (AES_ESA_Cal_DF_V.k_AES_VirtualMainSwitch_str)
#define k_AES_FirstPlanEndXMinThrd    (AES_ESA_Cal_DF_V.k_AES_FirstPlanEndXMinThrd_str)
#define k_AES_FirstCompltXThrd    (AES_ESA_Cal_DF_V.k_AES_FirstCompltXThrd_str)
#define k_AES_UseNextNextLaneC0    (AES_ESA_Cal_DF_V.k_AES_UseNextNextLaneC0_str)
#define k_AES_DyErrorFilterCon    (AES_ESA_Cal_DF_V.k_AES_DyErrorFilterCon_str)
#define k_AES_DyDotErrorFilterCon    (AES_ESA_Cal_DF_V.k_AES_DyDotErrorFilterCon_str)
#define k_AES_HeadErrorFilterCon    (AES_ESA_Cal_DF_V.k_AES_HeadErrorFilterCon_str)
#define k_AES_HeadDotErrorFilterCon    (AES_ESA_Cal_DF_V.k_AES_HeadDotErrorFilterCon_str)
#define k_AES_PhiDotErrorFilterCon    (AES_ESA_Cal_DF_V.k_AES_PhiDotErrorFilterCon_str)
#define k_AES_FFCurveFilterCon    (AES_ESA_Cal_DF_V.k_AES_FFCurveFilterCon_str)
#define k_AES_LatCtrl_PosPID_Kp_Near    (AES_ESA_Cal_DF_V.k_AES_LatCtrl_PosPID_Kp_Near_str)
#define k_AES_LatCtrl_PosPID_Kp_Far    (AES_ESA_Cal_DF_V.k_AES_LatCtrl_PosPID_Kp_Far_str)
#define k_AES_LatCtrl_PosPID_KI    (AES_ESA_Cal_DF_V.k_AES_LatCtrl_PosPID_KI_str)
#define k_AES_LatCtrl_PosPID_Kd_Near    (AES_ESA_Cal_DF_V.k_AES_LatCtrl_PosPID_Kd_Near_str)
#define k_AES_LatCtrl_PosPID_Kd_Far    (AES_ESA_Cal_DF_V.k_AES_LatCtrl_PosPID_Kd_Far_str)
#define k_AES_LatCtrl_HeadPID_Kp    (AES_ESA_Cal_DF_V.k_AES_LatCtrl_HeadPID_Kp_str)
#define k_AES_LatCtrl_HeadPID_Kd    (AES_ESA_Cal_DF_V.k_AES_LatCtrl_HeadPID_Kd_str)
#define k_AES_RatLmtFac_TorqCmd_Vspd    (AES_ESA_Cal_DF_V.k_AES_RatLmtFac_TorqCmd_Vspd_str)
#define k_AES_VspdBks    (AES_ESA_Cal_DF_V.k_AES_VspdBks_str)
#define k_AES_VspdBks_OnCome    (AES_ESA_Cal_DF_V.k_AES_VspdBks_OnCome_str)
#define k_AES_CtrlPredTime    (AES_ESA_Cal_DF_V.k_AES_CtrlPredTime_str)
#define k_AES_UseRealTimeEndPointY    (AES_ESA_Cal_DF_V.k_AES_UseRealTimeEndPointY_str)
#define k_AES_UseRealTimeEndPointDY    (AES_ESA_Cal_DF_V.k_AES_UseRealTimeEndPointDY_str)
#define k_AES_UseRealTimeEndPointDDY    (AES_ESA_Cal_DF_V.k_AES_UseRealTimeEndPointDDY_str)
#define k_AES_PathPredC2Thrd    (AES_ESA_Cal_DF_V.k_AES_PathPredC2Thrd_str)
#define k_AES_PathPred_Time    (AES_ESA_Cal_DF_V.k_AES_PathPred_Time_str)
#define k_AES_CtrlStartPredTime    (AES_ESA_Cal_DF_V.k_AES_CtrlStartPredTime_str)
#define k_AES_AySatisfyOnDelayTime    (AES_ESA_Cal_DF_V.k_AES_AySatisfyOnDelayTime_str)
#define k_AES_TrajColl_DiscreteDist    (AES_ESA_Cal_DF_V.k_AES_TrajColl_DiscreteDist_str)
#define k_AES_ActiveMaxDyThr    (AES_ESA_Cal_DF_V.k_AES_ActiveMaxDyThr_str)
#define k_AES_EgoVehicle_HalfWidth    (AES_ESA_Cal_DF_V.k_AES_EgoVehicle_HalfWidth_str)
#define k_AES_SafetyDistanceThr    (AES_ESA_Cal_DF_V.k_AES_SafetyDistanceThr_str)
#define k_AES_FeedForward_CurveAxis    (AES_ESA_Cal_DF_V.k_AES_FeedForward_CurveAxis_str)
#define k_AES_FeedForward_SpdAxis    (AES_ESA_Cal_DF_V.k_AES_FeedForward_SpdAxis_str)
#define k_AES_FeedForward_Coef_First_L    (AES_ESA_Cal_DF_V.k_AES_FeedForward_Coef_First_L_str)
#define k_AES_FeedForward_Coef_First_R    (AES_ESA_Cal_DF_V.k_AES_FeedForward_Coef_First_R_str)
#define k_AES_FeedForward_Coef_Sec_L    (AES_ESA_Cal_DF_V.k_AES_FeedForward_Coef_Sec_L_str)
#define k_AES_FeedForward_Coef_Sec_R    (AES_ESA_Cal_DF_V.k_AES_FeedForward_Coef_Sec_R_str)
#define k_AES_RadBks    (AES_ESA_Cal_DF_V.k_AES_RadBks_str)
#define k_AES_Lat_PFac_Rad    (AES_ESA_Cal_DF_V.k_AES_Lat_PFac_Rad_str)
#define k_AES_Lat_IFac_Rad    (AES_ESA_Cal_DF_V.k_AES_Lat_IFac_Rad_str)
#define k_AES_Lat_DFac_Rad    (AES_ESA_Cal_DF_V.k_AES_Lat_DFac_Rad_str)
#define k_AES_Hed_PFac_Rad    (AES_ESA_Cal_DF_V.k_AES_Hed_PFac_Rad_str)
#define k_AES_Hed_DFac_Rad    (AES_ESA_Cal_DF_V.k_AES_Hed_DFac_Rad_str)
#define k_AES_DisableLeftTurning    (AES_ESA_Cal_DF_V.k_AES_DisableLeftTurning_str)
#define k_AES_DisableRightTurning    (AES_ESA_Cal_DF_V.k_AES_DisableRightTurning_str)
#define k_AES_Dis_EgoRAxleToFBumper    (AES_ESA_Cal_DF_V.k_AES_Dis_EgoRAxleToFBumper_str)
#define k_AES_EgoVehicle_Width    (AES_ESA_Cal_DF_V.k_AES_EgoVehicle_Width_str)
#define k_AES_AverageTurnAccelMax    (AES_ESA_Cal_DF_V.k_AES_AverageTurnAccelMax_str)
#define k_AES_LastPntToStr_SafeDis    (AES_ESA_Cal_DF_V.k_AES_LastPntToStr_SafeDis_str)
#define k_AES_Obj_PredictedTime    (AES_ESA_Cal_DF_V.k_AES_Obj_PredictedTime_str)
#define k_AES_CheckDriverAvoid_SafeDis    (AES_ESA_Cal_DF_V.k_AES_CheckDriverAvoid_SafeDis_str)
#define k_AES_EnterEgoSpeed_MaxThr    (AES_ESA_Cal_DF_V.k_AES_EnterEgoSpeed_MaxThr_str)
#define k_AES_EnterEgoSpeed_MinThr    (AES_ESA_Cal_DF_V.k_AES_EnterEgoSpeed_MinThr_str)
#define k_AES_ExitEgoSpeed_MaxThr    (AES_ESA_Cal_DF_V.k_AES_ExitEgoSpeed_MaxThr_str)
#define k_AES_ExitEgoSpeed_MinThr    (AES_ESA_Cal_DF_V.k_AES_ExitEgoSpeed_MinThr_str)
#define k_AES_EnterEgoYawRate_Thr    (AES_ESA_Cal_DF_V.k_AES_EnterEgoYawRate_Thr_str)
#define k_AES_ExitEgoYawRate_Thr    (AES_ESA_Cal_DF_V.k_AES_ExitEgoYawRate_Thr_str)
#define k_AES_t_EnterEgoYawRate_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_EnterEgoYawRate_OnDly_str)
#define k_AES_EnterEgoAy_Thr    (AES_ESA_Cal_DF_V.k_AES_EnterEgoAy_Thr_str)
#define k_AES_t_EnterEgoAy_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_EnterEgoAy_OnDly_str)
#define k_AES_ExitEgoAy_Thr    (AES_ESA_Cal_DF_V.k_AES_ExitEgoAy_Thr_str)
#define k_AES_EnterEgoAccelPer_Thr    (AES_ESA_Cal_DF_V.k_AES_EnterEgoAccelPer_Thr_str)
#define k_AES_EnterEgoBrakePer_Thr    (AES_ESA_Cal_DF_V.k_AES_EnterEgoBrakePer_Thr_str)
#define k_AES_t_EnterPedalPer_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_EnterPedalPer_OnDly_str)
#define k_AES_ExitEgoAccelPer_Thr    (AES_ESA_Cal_DF_V.k_AES_ExitEgoAccelPer_Thr_str)
#define k_AES_ExitEgoBrakePer_Thr    (AES_ESA_Cal_DF_V.k_AES_ExitEgoBrakePer_Thr_str)
#define k_AES_EnterStrAng_Thr    (AES_ESA_Cal_DF_V.k_AES_EnterStrAng_Thr_str)
#define k_AES_t_EnterStrAng_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_EnterStrAng_OnDly_str)
#define k_AES_ExitStrAng_Thr    (AES_ESA_Cal_DF_V.k_AES_ExitStrAng_Thr_str)
#define k_AES_t_ExitStrAng_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_ExitStrAng_OnDly_str)
#define k_AES_EnterTrajMaxAy_Thr    (AES_ESA_Cal_DF_V.k_AES_EnterTrajMaxAy_Thr_str)
#define k_AES_StateUseTrajMaxAyThr    (AES_ESA_Cal_DF_V.k_AES_StateUseTrajMaxAyThr_str)
#define k_AES_EnterAES_HandTorq_Thr    (AES_ESA_Cal_DF_V.k_AES_EnterAES_HandTorq_Thr_str)
#define k_AES_EnterESA_HandTorq_Thr    (AES_ESA_Cal_DF_V.k_AES_EnterESA_HandTorq_Thr_str)
#define k_AES_t_DriverStrJudge_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_DriverStrJudge_OnDly_str)
#define k_AES_AESAbortHTorq_SameDirThr    (AES_ESA_Cal_DF_V.k_AES_AESAbortHTorq_SameDirThr_str)
#define k_AES_AESAbortHTorq_DiffDirThr    (AES_ESA_Cal_DF_V.k_AES_AESAbortHTorq_DiffDirThr_str)
#define k_AES_ESAAbortHTorq_SameDirThr    (AES_ESA_Cal_DF_V.k_AES_ESAAbortHTorq_SameDirThr_str)
#define k_AES_ESAAbortHTorq_DiffDirThr    (AES_ESA_Cal_DF_V.k_AES_ESAAbortHTorq_DiffDirThr_str)
#define k_AES_AbortEgoAccelPer_Thr    (AES_ESA_Cal_DF_V.k_AES_AbortEgoAccelPer_Thr_str)
#define k_AES_AbortEgoBrakePer_Thr    (AES_ESA_Cal_DF_V.k_AES_AbortEgoBrakePer_Thr_str)
#define k_AES_AbortEgoYawRate_Thr    (AES_ESA_Cal_DF_V.k_AES_AbortEgoYawRate_Thr_str)
#define k_AES_AbortEgoAy_Thr    (AES_ESA_Cal_DF_V.k_AES_AbortEgoAy_Thr_str)
#define k_AES_AbortStrAng_Thr    (AES_ESA_Cal_DF_V.k_AES_AbortStrAng_Thr_str)
#define k_AES_t_AbortEgoAccelPer_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_AbortEgoAccelPer_OnDly_str)
#define k_AES_t_AbortEgoBrakePer_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_AbortEgoBrakePer_OnDly_str)
#define k_AES_t_AbortEgoYawRate_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_AbortEgoYawRate_OnDly_str)
#define k_AES_t_AbortEgoAy_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_AbortEgoAy_OnDly_str)
#define k_AES_t_AbortStrAng_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_AbortStrAng_OnDly_str)
#define k_AES_t_AbortHandTorq_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_AbortHandTorq_OnDly_str)
#define k_AES_t_AbortESCActive_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_AbortESCActive_OnDly_str)
#define k_AES_CompletedC0_Thr    (AES_ESA_Cal_DF_V.k_AES_CompletedC0_Thr_str)
#define k_AES_CompletedC1_Thr    (AES_ESA_Cal_DF_V.k_AES_CompletedC1_Thr_str)
#define k_AES_t_CompletedC0C1_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_CompletedC0C1_OnDly_str)
#define k_AES_t_DriverAvoidObj_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_DriverAvoidObj_OnDly_str)
#define k_AES_AngLimitMax_Vspd    (AES_ESA_Cal_DF_V.k_AES_AngLimitMax_Vspd_str)
#define k_AES_Lat_KpKdSlopeLmt    (AES_ESA_Cal_DF_V.k_AES_Lat_KpKdSlopeLmt_str)
#define k_AES_Hed_KpKdSlopeLmt    (AES_ESA_Cal_DF_V.k_AES_Hed_KpKdSlopeLmt_str)
#define k_AES_t_FCWObstacleValid_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_FCWObstacleValid_OnDly_str)
#define k_AES_CsderEgoLen2PlanEndX    (AES_ESA_Cal_DF_V.k_AES_CsderEgoLen2PlanEndX_str)
#define k_AES_DefaultPassLaneLineCheck    (AES_ESA_Cal_DF_V.k_AES_DefaultPassLaneLineCheck_str)
#define k_AES_DefaultPassObstacleCheck    (AES_ESA_Cal_DF_V.k_AES_DefaultPassObstacleCheck_str)
#define k_AES_StrWhlAngFilterCon    (AES_ESA_Cal_DF_V.k_AES_StrWhlAngFilterCon_str)
#define k_AES_useFeedbackFirstPln    (AES_ESA_Cal_DF_V.k_AES_useFeedbackFirstPln_str)
#define k_AES_EnterEgoSpeed_MaxThr_VRU    (AES_ESA_Cal_DF_V.k_AES_EnterEgoSpeed_MaxThr_VRU_str)
#define k_AES_EnterEgoSpeed_MinThr_VRU    (AES_ESA_Cal_DF_V.k_AES_EnterEgoSpeed_MinThr_VRU_str)
#define k_AES_ExitEgoSpeed_MaxThr_VRU    (AES_ESA_Cal_DF_V.k_AES_ExitEgoSpeed_MaxThr_VRU_str)
#define k_AES_ExitEgoSpeed_MinThr_VRU    (AES_ESA_Cal_DF_V.k_AES_ExitEgoSpeed_MinThr_VRU_str)
#define k_AES_FeedForward_Coef_Second    (AES_ESA_Cal_DF_V.k_AES_FeedForward_Coef_Second_str)
#define k_AES_FeedForwardGain_SlopeLmt    (AES_ESA_Cal_DF_V.k_AES_FeedForwardGain_SlopeLmt_str)
#define k_AES_AEBObjUseISOcoordinate    (AES_ESA_Cal_DF_V.k_AES_AEBObjUseISOcoordinate_str)
#define k_AES_t_DriverQuickStr_OffDly    (AES_ESA_Cal_DF_V.k_AES_t_DriverQuickStr_OffDly_str)
#define k_AES_HostLaneObsOffset    (AES_ESA_Cal_DF_V.k_AES_HostLaneObsOffset_str)
#define k_AES_FeedForward_First_ESA_L    (AES_ESA_Cal_DF_V.k_AES_FeedForward_First_ESA_L_str)
#define k_AES_FeedForward_First_ESA_R    (AES_ESA_Cal_DF_V.k_AES_FeedForward_First_ESA_R_str)
#define k_AES_FeedForward_Sec_ESA_L    (AES_ESA_Cal_DF_V.k_AES_FeedForward_Sec_ESA_L_str)
#define k_AES_FeedForward_Sec_ESA_R    (AES_ESA_Cal_DF_V.k_AES_FeedForward_Sec_ESA_R_str)
#define k_AES_t_TTCValid_OnDly    (AES_ESA_Cal_DF_V.k_AES_t_TTCValid_OnDly_str)
#define k_AES_EnableAllTypeForAES    (AES_ESA_Cal_DF_V.k_AES_EnableAllTypeForAES_str)
#define k_AES_PlanAddDist_Static    (AES_ESA_Cal_DF_V.k_AES_PlanAddDist_Static_str)
#define k_AES_PlanAddDist_SlowSpd    (AES_ESA_Cal_DF_V.k_AES_PlanAddDist_SlowSpd_str)
#define k_AES_PlanAddDist_OnCome    (AES_ESA_Cal_DF_V.k_AES_PlanAddDist_OnCome_str)
#define k_AES_LastPntBrk_TTC_OC    (AES_ESA_Cal_DF_V.k_AES_LastPntBrk_TTC_OC_str)
#define k_AES_LastPntBrk_TTC_OC_ESA    (AES_ESA_Cal_DF_V.k_AES_LastPntBrk_TTC_OC_ESA_str)
#define k_AES_MaxBrakeDecelProtect    (AES_ESA_Cal_DF_V.k_AES_MaxBrakeDecelProtect_str)
#define k_AES_MaxBrakeDecelProtect_ESA    (AES_ESA_Cal_DF_V.k_AES_MaxBrakeDecelProtect_ESA_str)
#define k_AES_FCWObsSlowSpd_OnDly    (AES_ESA_Cal_DF_V.k_AES_FCWObsSlowSpd_OnDly_str)
#define k_AES_MaxBrakeDecelThr    (AES_ESA_Cal_DF_V.k_AES_MaxBrakeDecelThr_str)
#define k_AES_MaxBrakeDecelThr_ESA    (AES_ESA_Cal_DF_V.k_AES_MaxBrakeDecelThr_ESA_str)
#define k_AES_MaxBrkDeThr_SlowSpd    (AES_ESA_Cal_DF_V.k_AES_MaxBrkDeThr_SlowSpd_str)
#define k_AES_LeftLongSafeDistance    (AES_ESA_Cal_DF_V.k_AES_LeftLongSafeDistance_str)
#define k_AES_RightLongSafeDistance    (AES_ESA_Cal_DF_V.k_AES_RightLongSafeDistance_str)
#define k_AES_t_ActiveMaxTimeThr    (AES_ESA_Cal_DF_V.k_AES_t_ActiveMaxTimeThr_str)
#define k_AES_ObjFilterLonMaxTTC    (AES_ESA_Cal_DF_V.k_AES_ObjFilterLonMaxTTC_str)
#define k_AES_DriverStrJudge_AngSpdThr    (AES_ESA_Cal_DF_V.k_AES_DriverStrJudge_AngSpdThr_str)
#define k_AES_DriverStrJudge_AngThr    (AES_ESA_Cal_DF_V.k_AES_DriverStrJudge_AngThr_str)
#define k_AES_ObjOverLapLatThrsd    (AES_ESA_Cal_DF_V.k_AES_ObjOverLapLatThrsd_str)
#define k_AES_DisableESAObj    (AES_ESA_Cal_DF_V.k_AES_DisableESAObj_str)
#define k_AES_FCWObstacleLatOverLap    (AES_ESA_Cal_DF_V.k_AES_FCWObstacleLatOverLap_str)
#define k_AES_FCWObstacleLatVel    (AES_ESA_Cal_DF_V.k_AES_FCWObstacleLatVel_str)
#define k_AES_RoadEdgeValid_MaxThd    (AES_ESA_Cal_DF_V.k_AES_RoadEdgeValid_MaxThd_str)
#define k_AES_RoadEdgeValid_MinThd    (AES_ESA_Cal_DF_V.k_AES_RoadEdgeValid_MinThd_str)
#define k_AES_NoLaneLine_LatMoveThd    (AES_ESA_Cal_DF_V.k_AES_NoLaneLine_LatMoveThd_str)
#define k_AES_NoLaneLine_Flag    (AES_ESA_Cal_DF_V.k_AES_NoLaneLine_Flag_str)
#define k_AES_CTL_heading_spd    (AES_ESA_Cal_DF_V.k_AES_CTL_heading_spd_str)
#define k_AES_CTL_heading_error_factor    (AES_ESA_Cal_DF_V.k_AES_CTL_heading_error_factor_str)
#define k_AES_FCWObstacleLatOverLap_AES    (AES_ESA_Cal_DF_V.k_AES_FCWObstacleLatOverLap_AES_str)

#endif  /* _CAL_H */
