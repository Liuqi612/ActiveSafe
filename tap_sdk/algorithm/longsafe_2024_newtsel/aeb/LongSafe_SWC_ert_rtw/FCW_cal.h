#ifndef FCW_CAL_H
#define FCW_CAL_H
/****************************************************************************
 * Calibration file for FCW production code.
 * DD uses version 5 of the bas file.
 * File Name: D:\SenseTime_Model\ZDriver\02_DataDictionary\FCW\FCW_cal.h
 * Created: 2025/6/2        15:30:52 
 * From Excel file: DataDictionary_FCW_zDriver.xls
 * Calibration Values for project         
 * Calibrations for full application.
 * Set Description:         Initial Value
 ****************************************************************************/

#include "rtwtypes.h"

/*
 *  COMPONENT:  \FCW
*/

/*
 *  COMPONENT:  \FDI
*/

/*
 *  COMPONENT:  \Version Control
*/


#define FCW_CAL_SIZE  4968 

typedef struct {
   boolean k_FCW_Enable_str;
   uint8 k_FCW_FusHistConfLevel_str;
   uint8 k_FCW_FusHiConfLevel_str;
   uint8 k_FCW_FusMedConfLevel_str;
   uint8 k_FCW_FusHiMinInPAgeTrhd_str;
   uint8 k_FCW_FusHiMinInPAgeTrhdLg_str;
   uint8 k_FCW_FusMedMinInPAgeTrhd_str;
   uint8 k_FCW_FusMedMinInPAgeTrhdLg_str;
   uint8 k_FCW_VisMedMinInPAgeTrhd_str;
   uint8 k_FCW_VisMedMinInPAgeTrhdLg_str;
   uint8 k_FCW_MinInPAgeTrhd_str;
   uint8 k_FCW_MinInPAgeTrhdLg_str;
   uint8 k_FCW_VehSHiEstMinInPAgeTrhd_str;
   uint8 k_FCW_VehSHiMinInPAgeTrhd_str;
   uint8 k_FCW_VehSMedMinInPAgeTrhd_str;
   uint8 k_FCW_VehSMinInPAgeTrhd_str;
   uint8 k_FCW_VehMHiEstMinInPAgeTrhd_str;
   uint8 k_FCW_VehMHiMinInPAgeTrhd_str;
   uint8 k_FCW_VehMMedMinInPAgeTrhd_str;
   uint8 k_FCW_VehMMinInPAgeTrhd_str;
   float32 k_FCW_LatWarnHostAccThres_str;
   float32 k_FCW_MinSpd_str;
   float32 k_FCW_MaxRactnTmSpd_str;
   float32 k_FCW_MinSpdACC_str;
   float32 k_FCW_MaxSpdStat_str;
   float32 k_FCW_ObjPredPermitHeadAbs_str;
   float32 k_FCW_ObjCrossPermitHeadMin_str;
   float32 k_FCW_ObjCrossPermitHeadMax_str;
   float32 k_FCW_TmHdwyBuffer_z_str[ 7 ][ 2 ];
   float32 k_FCW_MovMaxTTC_z_str[ 7 ][ 2 ];
   float32 k_FCW_RangeBuffer_z_str[ 7 ][ 2 ];
   float32 k_FCW_LeadAccelAdj_z_str[ 7 ][ 2 ];
   float32 k_FCW_DeaccForReleAccPedl_str;
   float32 k_FCW_ReactionTime_z_str[ 7 ][ 2 ];
   float32 k_FCW_MaxRngStat_z_str[ 7 ][ 2 ];
   float32 k_FCW_VRUMaxRng_z_str[ 7 ][ 2 ];
   float32 k_FCW_StatRatnTmAdj_z_str[ 7 ][ 2 ];
   float32 k_FCW_ResponseAccel_z_str[ 7 ][ 2 ];
   float32 k_FCW_CautnAllowTailgate_z_str[ 7 ];
   uint16 k_FCW_MinTmBtAlerts_ms_str;
   uint16 k_FCW_reserve1_str;
   float32 k_FCW_StatMaxTTC_z_str[ 7 ][ 2 ];
   float32 k_FCW_VRUMaxTTC_z_str[ 7 ][ 2 ];
   float32 k_FCW_MaxStatYaw_str;
   float32 k_FCW_MaxSpdCautnOn_str;
   float32 k_FCW_MaxSpdCautnOff_str;
   uint16 k_FCW_CautnCoast_ms_str;
   uint16 k_FCW_AWBAtvWarnThresTm_str;
   float32 k_FCW_MinAlertReqAccel_str;
   float32 k_FCW_MinAlertReqRngRt_str;
   float32 k_FCW_RTWhileSuppressed_str;
   float32 k_FCW_MaxRTWhileBraking_str;
   uint16 k_FCW_RTRecoverTC_ms_str;
   uint16 k_FCW_reserve3_str;
   float32 k_FCW_MaxDecelRate_str;
   float32 k_FCW_MaxStrRate_str;
   float32 k_FCW_MinAccelPdl_str;
   float32 k_FCW_MaxAccelPdl_str;
   float32 k_FCW_MinBrkPdl_str;
   float32 k_FCW_MaxBrkPdl_str;
   uint16 k_FCW_HdTmSteer_ms_str;
   uint16 k_FCW_HdTmAccelUp_ms_str;
   uint16 k_FCW_HdTmAccelDown_ms_str;
   uint16 k_FCW_HdTmBrkUp_ms_str;
   uint16 k_FCW_HdTmBrkDown_ms_str;
   uint16 k_FCW_AlertHdTm_ms_str;
   float32 k_FCW_BrakePropnBuffer_str;
   uint16 k_FCW_HostSpdFilterTm_ms_str;
   uint16 k_FCW_RawCautnFilterTm_ms_str;
   uint16 k_FCW_HdTmAccel_ms_str;
   uint16 k_FCW_reserve4_str;
   float32 k_FCW_GapSetgIn_x_str[ 7 ];
   float32 k_FCW_ACCOKIn_y_str[ 2 ];
   float32 k_FCW_CautnAllowClosing_z_str[ 7 ];
   float32 k_FCW_CautnTHW_z_str[ 7 ];
   float32 k_FCW_CautnTTC_z_str[ 7 ];
   float32 k_FCW_MaxHostAccel_str;
   float32 k_FCW_CautnTTCHys_str;
   boolean k_FCW_AllowBrkAlerts_str;
   boolean k_FCW_AccelPdlSuppr_str;
   boolean k_FCW_HostAccelSuppr_str;
   uint8 k_FCW_ChmSuppressUse_str;
   uint8 k_FCW_AllowTmngAdjACCBrk_str;
   uint8 k_FCW_CautnforACCEngvsBrk_str;
   uint8 k_FCW_AllowedDuringCrusCtrl_str;
   uint8 k_FCW_AllowedTypes_str;
   uint16 k_FCW_CautnPersist_ms_str;
   uint16 k_FCW_HdTmDecel_ms_str;
   boolean k_FCW_HostDecelSuppr_str;
   uint8 k_FCW_reserve5_str;
   uint16 k_FCW_reserve6_str;
   float32 k_FCW_MinHostAccel_str;
   float32 k_FCW_CautnLatHys_str;
   float32 k_FCW_CautnLat_str;
   float32 k_FCW_MaxLat_str;
   float32 k_FCW_VRUMaxLat_str;
   uint8 k_FCW_VehSReqConf_str;
   uint8 k_FCW_reserve7_str;
   uint16 k_FCW_reserve8_str;
   float32 k_FCW_VRUSensitize_str;
   float32 k_FCW_HostSpeed_x_str[ 8 ];
   float32 k_FCW_MinTaperProp_z_str[ 8 ];
   uint8 k_FCW_VehMReqConf_str;
   boolean k_FCW_VehMUseLatRt_str;
   uint16 k_FCW_reserve9_str;
   float32 k_FCW_FullXolc_str;
   float32 k_FCW_NegXolc_str;
   float32 k_FCW_StrTurnTrhd_str;
   float32 k_FCW_StrTrhd_str;
   float32 k_FCW_XolcTrhd_str;
   boolean k_FCW_UseXolc_str;
   boolean k_FCW_AccelPdlPosSuppr_str;
   boolean k_FCW_BrkPdlSuppr_str;
   uint8 k_FCW_reserve10_str;
   float32 k_FCW_MaxAccelPdlPos_str;
   float32 k_FCW_MaxAccelPdlPosVec_str[ 9 ];
   float32 k_FCW_MinAccelPdlPosVec_str[ 9 ];
   uint16 k_FCW_HdTmAccelPos_ms_str;
   uint16 k_FCW_BrkPdlMoniTm_ms_str;
   uint16 k_FCW_HdTmBrkPdl_ms_str;
   uint16 k_FCW_reserve11_str;
   float32 k_FCW_HostSpdRTAdj_z_str[ 8 ];
   float32 k_FCW_HostSpdRTAdj_x_str[ 8 ];
   float32 k_FCW_ACCHostSpdRTAdj_z_str[ 8 ];
   float32 k_FCW_ACCHostSpdRTAdj_x_str[ 8 ];
   uint16 k_FCW_ROCTrhdVehS_str;
   uint16 k_FCW_ROCTrhdVehM_str;
   boolean k_FCW_VisnFCWCnfgEnbl_str;
   boolean k_FCW_UseOnlyVisnFCW_str;
   boolean k_FCW_Visn_IgnChmSupress_str;
   uint8 k_FCW_reserve12_str;
   float32 k_FCW_VisnTTCTrhdSpd_x_str[ 8 ];
   float32 k_FCW_VisnTTCTrhd_z_str[ 7 ][ 8 ];
   float32 k_FCW_VisnVRUTTCTrhd_z_str[ 7 ][ 8 ];
   uint16 k_FCW_HostAccelMoniTm_ms_str;
   uint16 k_FCW_reserve13_str;
   float32 k_FCW_Visn_SensorLatency_mps_str[ 8 ];
   float32 k_FCW_Visn_SensorLatency_sec_str[ 8 ];
   float32 k_FCW_Visn_HostSpd_x_str[ 8 ];
   float32 k_FCW_Visn_RelSpd_x_str[ 8 ];
   float32 k_FCW_Visn_Rel_TTCTrhd_z_str[ 8 ][ 8 ];
   float32 k_FCW_CautnMinRngRt_str;
   boolean k_FCW_BrkPdlRateSuppr_str;
   boolean k_FCW_VisnVRU_WarnEnbl_str;
   boolean k_FCW_VisnVeh_NoHostCntrl_str;
   boolean k_FCW_VisnTTCPlausEnbl_str;
   uint8 k_FCW_VisnTTCPlausMinSpeed_str;
   uint8 k_FCW_VisnMinPlausTTC_str;
   uint16 k_FCW_reserve14_str;
   float32 k_FCW_VisnPlausTTC_z_str[ 8 ][ 9 ];
   float32 k_FCW_VisnMinPlausAccel_x_str[ 9 ];
   boolean k_FCW_VisnMesTTCEnbl_str;
   uint8 k_FCW_VRUReqConf_str;
   uint16 k_FCW_reserve15_str;
   float32 k_FCW_VRULockIn_y_str[ 2 ];
   uint16 k_FCW_AcuteWarnMaxTm_ms_str;
   uint16 k_FCW_reserve16_str;
   float32 k_FCW_VisnAcuTTCTrhd_z_str[ 7 ][ 8 ];
   float32 k_FCW_VisnVRUAcuTTCTrhd_z_str[ 7 ][ 8 ];
   float32 k_FCW_VisnAcuTTCTrhdSpd_x_str[ 8 ];
   uint16 k_FCW_AcuteAlertHdTm_ms_str;
   uint16 k_FCW_AcuteHdTm_ms_str;
   boolean k_FCW_AcutWnBrakeConfig_str;
   uint8 k_FCW_reserve17_str;
   uint16 k_FCW_reserve18_str;
   uint16 k_FCW_AllowActuWnDuringACC_str;
   uint16 k_FCW_AllowActuWnTypes_str;
   boolean k_FCW_BrkSuppressUse_str;
   boolean k_FCW_AcutWarnPFSuppr_str;
   uint16 k_FCW_reserve19_str;
   float32 k_FCW_MaxSpdAcutWarnOff_str;
   float32 k_FCW_MaxSpdAcutWarnOn_str;
   uint8 k_FCW_AcutForACCEngvsBrk_str;
   uint8 k_FCW_reserve20_str;
   uint16 k_FCW_reserve21_str;
   float32 k_FCW_HostSpdAcutRTGain_z_str[ 8 ];
   float32 k_FCW_HostSpdAcutRTGain_x_str[ 8 ];
   float32 k_FCW_VRUMaxAcutTTC_z_str[ 7 ][ 2 ];
   float32 k_FCW_StatMaxAcutTTC_z_str[ 7 ][ 2 ];
   float32 k_FCW_VRUMaxAcutRng_z_str[ 7 ][ 2 ];
   float32 k_FCW_MaxAcutRngStat_z_str[ 7 ][ 2 ];
   float32 k_FCW_MovMaxAcutTTC_z_str[ 7 ][ 2 ];
   boolean k_FCW_EnblWithCruiseOnOff_str;
   boolean k_FCW_UseUncompSpd_str;
   boolean k_FCW_UseTTCFromFCWCalc_str;
   boolean k_FCW_AllowExtWarnBrkOny_str;
   boolean k_FCW_EnblSdRdrDgrdChk_str;
   uint8 k_FCW_SdRdrDgrdMinConf_str;
   boolean k_FCW_AcutWarnEnbl_str;
   boolean k_FCW_UseLatRt_VehM_str;
   uint8 k_FCW_reserve22_str;
   float32 k_FCW_MaxSpd_LongBike_str;
   float32 k_FCW_MaxSpd_VRU_str;
   float32 k_FCW_MaxSpd_CrossBike_str;
   boolean k_FCW_UseVRUHold_str;
   boolean k_FCW_MaxTTCRngAccelSrc_str;
   boolean k_FCW_IgnoreOvrdForCautn_str;
   uint8 k_FCW_OvrdCycleforInhibCautn_str;
   float32 k_FCW_GeneralSpd_x_str[ 9 ];
   float32 k_FCW_HardTurnStrAngTrhd_str[ 9 ];
   float32 k_FCW_StrAngRateTrhd_str[ 9 ];
   uint16 k_FCW_StrInhibitCauEnblTm_str;
   uint16 k_FCW_StrInhibitHoldTm_str;
   float32 k_FCW_CautnAllowRngRt_str;
   float32 k_FCW_CautnEnablTm_str[ 7 ];
   uint16 k_FCW_CautnQuitEnablTm_str;
   uint16 k_FCW_reserve23_str;
   float32 k_FCW_HWTmGainCautnOn_str;
   float32 k_FCW_HWTmGainCautnOff_str;
   uint16 k_FCW_VisnVehJAWarnSustain_ms_str;
   uint16 k_FCW_reserve24_str;
   float32 k_FCW_NoJAMinSpd_str;
   boolean k_FCW_IgnoreVRUGOE_str;
   boolean k_FCW_IgnoreVehGOE_str;
   uint8 k_FCW_VRUFusHiConfLvl_str;
   uint8 k_FCW_VRUFusMedConfLvl_str;
   uint8 k_FCW_VRUVisMedConfLvl_str;
   uint8 k_FCW_RiderFusHiMinInPAgeTrhd_str;
   uint8 k_FCW_PedFusHiMinInPAgeTrhd_str;
   uint8 k_FCW_RiderFusMedMinInPAgeTrhd_str;
   uint8 k_FCW_PedFusMedMinInPAgeTrhd_str;
   uint8 k_FCW_RiderVisMedMinInPAgeTrhd_str;
   uint8 k_FCW_PedVisMedMinInPAgeTrhd_str;
   uint8 k_FCW_RiderMinInPAgeTrhd_str;
   uint8 k_FCW_PedMinInPAgeTrhd_str;
   uint8 k_FCW_TimeGapSet_z_str[ 7 ];
   float32 k_FCW_UseTTC_SpdPoints_str[ 9 ];
   float32 k_FCW_BiLongWarnTTCTrhd_sec_str[ 9 ][ 3 ];
   float32 k_FCW_BiStatWarnTTCTrhd_sec_str[ 9 ][ 3 ];
   float32 k_FCW_BiCrossWarnTTCTrhd_sec_str[ 9 ][ 3 ];
   float32 k_FCW_PedLongWarnTTCTrhd_sec_str[ 9 ][ 3 ];
   float32 k_FCW_PedStatWarnTTCTrhd_sec_str[ 9 ][ 3 ];
   float32 k_FCW_PedCrossWarnTTCTrhd_sec_str[ 9 ][ 3 ];
   float32 k_FCW_MovWarnTTCTrhd_sec_str[ 9 ][ 3 ];
   float32 k_FCW_StatWarnTTCTrhd_sec_str[ 9 ][ 3 ];
   float32 k_FCW_ScpTurnLong_Delay_str;
   float32 k_FCW_ChimeSuppr_Delay_str;
   float32 k_FCW_BrkPdlPrsd_Delay_str;
   float32 k_FCW_AcuteAvail_Delay_str[ 8 ];
   boolean k_FCW_MovUseRangeTriger_str;
   boolean k_FCW_StatUseRangeTriger_str;
   uint16 k_FCW_reserve26_str;
   float32 k_FCW_TTCTriggerSvntySet_str[ 3 ];
   float32 k_FCW_TWDecelerateDetectAccel_str;
   float32 k_FCW_PedDecelerateDetectAccel_str;
   uint16 k_FCW_VRUDecelerateDetectHdTm_str;
   uint8 k_FCW_Mature_RE_thres_str;
   uint8 k_FCW_reserve27_str;
   float32 k_FCW_left_A0_RE_enter_thres_str;
   float32 k_FCW_left_A0_RE_exit_thres_str;
   float32 k_FCW_right_A0_RE_enter_thres_str;
   float32 k_FCW_right_A0_RE_exit_thres_str;
   float32 k_FCW_RE_EndRangeOffset_str;
   float32 k_FCW_RE_StartRangeOffset_str;
   boolean k_FCW_IgnoreVRU_RECheck_str;
   boolean k_FCW_IgnoreVRU_XolcCheck_str;
   uint8 k_FCW_VRUReqConf_Fusion_str;
   boolean k_FCW_IgnoreAEBTriggerSpd_str;
   float32 k_FCW_Default_Time_Offset_str;
   float32 k_FCW_HighSpdCrsLatVel_str;
   float32 k_FCW_MaxSpdStatAcuWarnThresh_str;
   float32 k_FCW_MaxSpdAcutWarnThresh_str;
   float32 k_FCW_MaxSpdMov_str;
   float32 k_FCW_MaxSpdCautnThresh_str;
   uint8 k_FCW_VehFusHiMinInPAgeTrhd_str;
   uint8 k_FCW_VehFusMedMinInPAgeTrhd_str;
   uint8 k_FCW_VehVisMedMinInPAgeTrhd_str;
   uint8 k_FCW_VehMinInPAgeTrhd_str;
   float32 k_FCW_MinTTCReq_str;
   float32 k_FCW_MinRangeReq_str;
   float32 k_FCW_AccActive_RedFac_str;
   float32 k_FCWSnvty_map_z_str[ 7 ];
   float32 k_FCWSnvty_map_x_str[ 7 ];
   float32 k_FCW_TTC_ACC_RedFac_str[ 9 ];
   uint16 k_FCW_DisHldTime_Latent_str;
   uint16 k_FCW_DisHldTime_PreWarn_str;
   boolean k_FCW_Bypass_Spdlimit_str;
   uint8 k_FCW_reserve28_str;
   uint16 k_FCW_reserve29_str;
   float32 k_FCW_VehSpdBrkPoinys_str[ 8 ];
   float32 k_FCW_CmftForLv1DWWarnDist_str[ 8 ];
   float32 k_FCW_CmftForLv2DWWarnDist_str[ 8 ];
   float32 k_FCW_CmftForLv3DWWarnDist_str[ 8 ];
   float32 k_FCW_DW_MainLoopTime_str;
   boolean k_FCW_DW_Enable_str;
   boolean k_FCW_DW_UseDistLmt_str;
   uint16 k_FCW_reserve30_str;
   float32 k_FCW_DW_DisResThresh_str;
   float32 k_FCW_DW_DisResLow_str;
   float32 k_FCW_DW_DisResHigh_str;
   float32 k_FCW_DW_DisHysResLow_str;
   float32 k_FCW_DW_DisHysResHigh_str;
   float32 k_FCW_DW_TimeResThresh_str;
   float32 k_FCW_DW_TimeResLow_str;
   float32 k_FCW_DW_TimeResHigh_str;
   float32 k_FCW_DW_TimeHysResLow_str;
   float32 k_FCW_DW_TimeHysResHigh_str;
   float32 k_FCW_DW_MinActivationSpeed_str;
   float32 k_FCW_DW_LowerCutoffSpeed_str;
   float32 k_FCW_DW_MaxActivationSpeed_str;
   float32 k_FCW_DW_UpperCutoffSpeed_str;
   boolean k_FCW_DW_IgnoreVehAhdInd_str;
   boolean k_FCW_IgnoreFCWTmChkAWB_str;
   uint16 k_FCW_reserve32_str;
   float32 k_FCW_DW_MinLVSpeed_str;
   float32 k_FCW_DW_LVCutoffSpeed_str;
   float32 k_FCW_DW_MaxRange_str;
   float32 k_FCW_DW_MaxTime_str;
   float32 k_FCW_DW_TimeTooLow_str;
   float32 k_FCW_DW_TimeTooHigh_str;
   float32 k_FCW_DW_DisTooLow_str;
   float32 k_FCW_DW_DisTooHigh_str;
   float32 k_FCW_DW_FLWTimeMax_str;
   float32 k_FCW_DW_FLWTimeMin_str;
   float32 k_FCW_DW_FLWDistMax_str;
   float32 k_FCW_DW_FLWDistMin_str;
   uint16 k_FCW_DW_DisplayHoldTime_str;
   uint16 k_FCW_DW_CPIVChangeTime_str;
   uint16 k_FCW_DW_ALGO_LOOP_INT_str;
   uint16 k_FCW_PreWarningMask_str;
   uint8 k_FCW_reserve34_str;
   uint8 k_FCW_Customer_str;
   uint8 k_FCW_Platform_str;
   uint8 k_FCW_VehVariant_str;
   uint8 k_FCW_ProductionModelYear_str;
   uint8 k_FCW_SensorConfig_str;
   uint8 k_Cal_FCW_major_version_str;
   uint8 k_Cal_FCW_minor_version_str;
} FCW_cal_T;

#define FCW_START_SEC_CAL_UNSPECIFIED
extern FCW_cal_T FCW_Cal_DF_V;
#define FCW_STOP_SEC_CAL_UNSPECIFIED
/* Access Macros for the structure elements. Please note that application
* does not use data flash memory directly and uses the RAM copy of data flash.Though
* following macros start with K_ they actually point to RAM image of calibrations.
*/

#define k_FCW_Enable    (FCW_Cal_DF_V.k_FCW_Enable_str)
#define k_FCW_FusHistConfLevel    (FCW_Cal_DF_V.k_FCW_FusHistConfLevel_str)
#define k_FCW_FusHiConfLevel    (FCW_Cal_DF_V.k_FCW_FusHiConfLevel_str)
#define k_FCW_FusMedConfLevel    (FCW_Cal_DF_V.k_FCW_FusMedConfLevel_str)
#define k_FCW_FusHiMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_FusHiMinInPAgeTrhd_str)
#define k_FCW_FusHiMinInPAgeTrhdLg    (FCW_Cal_DF_V.k_FCW_FusHiMinInPAgeTrhdLg_str)
#define k_FCW_FusMedMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_FusMedMinInPAgeTrhd_str)
#define k_FCW_FusMedMinInPAgeTrhdLg    (FCW_Cal_DF_V.k_FCW_FusMedMinInPAgeTrhdLg_str)
#define k_FCW_VisMedMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VisMedMinInPAgeTrhd_str)
#define k_FCW_VisMedMinInPAgeTrhdLg    (FCW_Cal_DF_V.k_FCW_VisMedMinInPAgeTrhdLg_str)
#define k_FCW_MinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_MinInPAgeTrhd_str)
#define k_FCW_MinInPAgeTrhdLg    (FCW_Cal_DF_V.k_FCW_MinInPAgeTrhdLg_str)
#define k_FCW_VehSHiEstMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehSHiEstMinInPAgeTrhd_str)
#define k_FCW_VehSHiMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehSHiMinInPAgeTrhd_str)
#define k_FCW_VehSMedMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehSMedMinInPAgeTrhd_str)
#define k_FCW_VehSMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehSMinInPAgeTrhd_str)
#define k_FCW_VehMHiEstMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehMHiEstMinInPAgeTrhd_str)
#define k_FCW_VehMHiMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehMHiMinInPAgeTrhd_str)
#define k_FCW_VehMMedMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehMMedMinInPAgeTrhd_str)
#define k_FCW_VehMMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehMMinInPAgeTrhd_str)
#define k_FCW_LatWarnHostAccThres    (FCW_Cal_DF_V.k_FCW_LatWarnHostAccThres_str)
#define k_FCW_MinSpd    (FCW_Cal_DF_V.k_FCW_MinSpd_str)
#define k_FCW_MaxRactnTmSpd    (FCW_Cal_DF_V.k_FCW_MaxRactnTmSpd_str)
#define k_FCW_MinSpdACC    (FCW_Cal_DF_V.k_FCW_MinSpdACC_str)
#define k_FCW_MaxSpdStat    (FCW_Cal_DF_V.k_FCW_MaxSpdStat_str)
#define k_FCW_ObjPredPermitHeadAbs    (FCW_Cal_DF_V.k_FCW_ObjPredPermitHeadAbs_str)
#define k_FCW_ObjCrossPermitHeadMin    (FCW_Cal_DF_V.k_FCW_ObjCrossPermitHeadMin_str)
#define k_FCW_ObjCrossPermitHeadMax    (FCW_Cal_DF_V.k_FCW_ObjCrossPermitHeadMax_str)
#define k_FCW_TmHdwyBuffer_z    (FCW_Cal_DF_V.k_FCW_TmHdwyBuffer_z_str[0])
#define k_FCW_MovMaxTTC_z    (FCW_Cal_DF_V.k_FCW_MovMaxTTC_z_str[0])
#define k_FCW_RangeBuffer_z    (FCW_Cal_DF_V.k_FCW_RangeBuffer_z_str[0])
#define k_FCW_LeadAccelAdj_z    (FCW_Cal_DF_V.k_FCW_LeadAccelAdj_z_str[0])
#define k_FCW_DeaccForReleAccPedl    (FCW_Cal_DF_V.k_FCW_DeaccForReleAccPedl_str)
#define k_FCW_ReactionTime_z    (FCW_Cal_DF_V.k_FCW_ReactionTime_z_str[0])
#define k_FCW_MaxRngStat_z    (FCW_Cal_DF_V.k_FCW_MaxRngStat_z_str[0])
#define k_FCW_VRUMaxRng_z    (FCW_Cal_DF_V.k_FCW_VRUMaxRng_z_str[0])
#define k_FCW_StatRatnTmAdj_z    (FCW_Cal_DF_V.k_FCW_StatRatnTmAdj_z_str[0])
#define k_FCW_ResponseAccel_z    (FCW_Cal_DF_V.k_FCW_ResponseAccel_z_str[0])
#define k_FCW_CautnAllowTailgate_z    (FCW_Cal_DF_V.k_FCW_CautnAllowTailgate_z_str)
#define k_FCW_MinTmBtAlerts_ms    (FCW_Cal_DF_V.k_FCW_MinTmBtAlerts_ms_str)
#define k_FCW_reserve1    (FCW_Cal_DF_V.k_FCW_reserve1_str)
#define k_FCW_StatMaxTTC_z    (FCW_Cal_DF_V.k_FCW_StatMaxTTC_z_str[0])
#define k_FCW_VRUMaxTTC_z    (FCW_Cal_DF_V.k_FCW_VRUMaxTTC_z_str[0])
#define k_FCW_MaxStatYaw    (FCW_Cal_DF_V.k_FCW_MaxStatYaw_str)
#define k_FCW_MaxSpdCautnOn    (FCW_Cal_DF_V.k_FCW_MaxSpdCautnOn_str)
#define k_FCW_MaxSpdCautnOff    (FCW_Cal_DF_V.k_FCW_MaxSpdCautnOff_str)
#define k_FCW_CautnCoast_ms    (FCW_Cal_DF_V.k_FCW_CautnCoast_ms_str)
#define k_FCW_AWBAtvWarnThresTm    (FCW_Cal_DF_V.k_FCW_AWBAtvWarnThresTm_str)
#define k_FCW_MinAlertReqAccel    (FCW_Cal_DF_V.k_FCW_MinAlertReqAccel_str)
#define k_FCW_MinAlertReqRngRt    (FCW_Cal_DF_V.k_FCW_MinAlertReqRngRt_str)
#define k_FCW_RTWhileSuppressed    (FCW_Cal_DF_V.k_FCW_RTWhileSuppressed_str)
#define k_FCW_MaxRTWhileBraking    (FCW_Cal_DF_V.k_FCW_MaxRTWhileBraking_str)
#define k_FCW_RTRecoverTC_ms    (FCW_Cal_DF_V.k_FCW_RTRecoverTC_ms_str)
#define k_FCW_reserve3    (FCW_Cal_DF_V.k_FCW_reserve3_str)
#define k_FCW_MaxDecelRate    (FCW_Cal_DF_V.k_FCW_MaxDecelRate_str)
#define k_FCW_MaxStrRate    (FCW_Cal_DF_V.k_FCW_MaxStrRate_str)
#define k_FCW_MinAccelPdl    (FCW_Cal_DF_V.k_FCW_MinAccelPdl_str)
#define k_FCW_MaxAccelPdl    (FCW_Cal_DF_V.k_FCW_MaxAccelPdl_str)
#define k_FCW_MinBrkPdl    (FCW_Cal_DF_V.k_FCW_MinBrkPdl_str)
#define k_FCW_MaxBrkPdl    (FCW_Cal_DF_V.k_FCW_MaxBrkPdl_str)
#define k_FCW_HdTmSteer_ms    (FCW_Cal_DF_V.k_FCW_HdTmSteer_ms_str)
#define k_FCW_HdTmAccelUp_ms    (FCW_Cal_DF_V.k_FCW_HdTmAccelUp_ms_str)
#define k_FCW_HdTmAccelDown_ms    (FCW_Cal_DF_V.k_FCW_HdTmAccelDown_ms_str)
#define k_FCW_HdTmBrkUp_ms    (FCW_Cal_DF_V.k_FCW_HdTmBrkUp_ms_str)
#define k_FCW_HdTmBrkDown_ms    (FCW_Cal_DF_V.k_FCW_HdTmBrkDown_ms_str)
#define k_FCW_AlertHdTm_ms    (FCW_Cal_DF_V.k_FCW_AlertHdTm_ms_str)
#define k_FCW_BrakePropnBuffer    (FCW_Cal_DF_V.k_FCW_BrakePropnBuffer_str)
#define k_FCW_HostSpdFilterTm_ms    (FCW_Cal_DF_V.k_FCW_HostSpdFilterTm_ms_str)
#define k_FCW_RawCautnFilterTm_ms    (FCW_Cal_DF_V.k_FCW_RawCautnFilterTm_ms_str)
#define k_FCW_HdTmAccel_ms    (FCW_Cal_DF_V.k_FCW_HdTmAccel_ms_str)
#define k_FCW_reserve4    (FCW_Cal_DF_V.k_FCW_reserve4_str)
#define k_FCW_GapSetgIn_x    (FCW_Cal_DF_V.k_FCW_GapSetgIn_x_str)
#define k_FCW_ACCOKIn_y    (FCW_Cal_DF_V.k_FCW_ACCOKIn_y_str)
#define k_FCW_CautnAllowClosing_z    (FCW_Cal_DF_V.k_FCW_CautnAllowClosing_z_str)
#define k_FCW_CautnTHW_z    (FCW_Cal_DF_V.k_FCW_CautnTHW_z_str)
#define k_FCW_CautnTTC_z    (FCW_Cal_DF_V.k_FCW_CautnTTC_z_str)
#define k_FCW_MaxHostAccel    (FCW_Cal_DF_V.k_FCW_MaxHostAccel_str)
#define k_FCW_CautnTTCHys    (FCW_Cal_DF_V.k_FCW_CautnTTCHys_str)
#define k_FCW_AllowBrkAlerts    (FCW_Cal_DF_V.k_FCW_AllowBrkAlerts_str)
#define k_FCW_AccelPdlSuppr    (FCW_Cal_DF_V.k_FCW_AccelPdlSuppr_str)
#define k_FCW_HostAccelSuppr    (FCW_Cal_DF_V.k_FCW_HostAccelSuppr_str)
#define k_FCW_ChmSuppressUse    (FCW_Cal_DF_V.k_FCW_ChmSuppressUse_str)
#define k_FCW_AllowTmngAdjACCBrk    (FCW_Cal_DF_V.k_FCW_AllowTmngAdjACCBrk_str)
#define k_FCW_CautnforACCEngvsBrk    (FCW_Cal_DF_V.k_FCW_CautnforACCEngvsBrk_str)
#define k_FCW_AllowedDuringCrusCtrl    (FCW_Cal_DF_V.k_FCW_AllowedDuringCrusCtrl_str)
#define k_FCW_AllowedTypes    (FCW_Cal_DF_V.k_FCW_AllowedTypes_str)
#define k_FCW_CautnPersist_ms    (FCW_Cal_DF_V.k_FCW_CautnPersist_ms_str)
#define k_FCW_HdTmDecel_ms    (FCW_Cal_DF_V.k_FCW_HdTmDecel_ms_str)
#define k_FCW_HostDecelSuppr    (FCW_Cal_DF_V.k_FCW_HostDecelSuppr_str)
#define k_FCW_reserve5    (FCW_Cal_DF_V.k_FCW_reserve5_str)
#define k_FCW_reserve6    (FCW_Cal_DF_V.k_FCW_reserve6_str)
#define k_FCW_MinHostAccel    (FCW_Cal_DF_V.k_FCW_MinHostAccel_str)
#define k_FCW_CautnLatHys    (FCW_Cal_DF_V.k_FCW_CautnLatHys_str)
#define k_FCW_CautnLat    (FCW_Cal_DF_V.k_FCW_CautnLat_str)
#define k_FCW_MaxLat    (FCW_Cal_DF_V.k_FCW_MaxLat_str)
#define k_FCW_VRUMaxLat    (FCW_Cal_DF_V.k_FCW_VRUMaxLat_str)
#define k_FCW_VehSReqConf    (FCW_Cal_DF_V.k_FCW_VehSReqConf_str)
#define k_FCW_reserve7    (FCW_Cal_DF_V.k_FCW_reserve7_str)
#define k_FCW_reserve8    (FCW_Cal_DF_V.k_FCW_reserve8_str)
#define k_FCW_VRUSensitize    (FCW_Cal_DF_V.k_FCW_VRUSensitize_str)
#define k_FCW_HostSpeed_x    (FCW_Cal_DF_V.k_FCW_HostSpeed_x_str)
#define k_FCW_MinTaperProp_z    (FCW_Cal_DF_V.k_FCW_MinTaperProp_z_str)
#define k_FCW_VehMReqConf    (FCW_Cal_DF_V.k_FCW_VehMReqConf_str)
#define k_FCW_VehMUseLatRt    (FCW_Cal_DF_V.k_FCW_VehMUseLatRt_str)
#define k_FCW_reserve9    (FCW_Cal_DF_V.k_FCW_reserve9_str)
#define k_FCW_FullXolc    (FCW_Cal_DF_V.k_FCW_FullXolc_str)
#define k_FCW_NegXolc    (FCW_Cal_DF_V.k_FCW_NegXolc_str)
#define k_FCW_StrTurnTrhd    (FCW_Cal_DF_V.k_FCW_StrTurnTrhd_str)
#define k_FCW_StrTrhd    (FCW_Cal_DF_V.k_FCW_StrTrhd_str)
#define k_FCW_XolcTrhd    (FCW_Cal_DF_V.k_FCW_XolcTrhd_str)
#define k_FCW_UseXolc    (FCW_Cal_DF_V.k_FCW_UseXolc_str)
#define k_FCW_AccelPdlPosSuppr    (FCW_Cal_DF_V.k_FCW_AccelPdlPosSuppr_str)
#define k_FCW_BrkPdlSuppr    (FCW_Cal_DF_V.k_FCW_BrkPdlSuppr_str)
#define k_FCW_reserve10    (FCW_Cal_DF_V.k_FCW_reserve10_str)
#define k_FCW_MaxAccelPdlPos    (FCW_Cal_DF_V.k_FCW_MaxAccelPdlPos_str)
#define k_FCW_MaxAccelPdlPosVec    (FCW_Cal_DF_V.k_FCW_MaxAccelPdlPosVec_str)
#define k_FCW_MinAccelPdlPosVec    (FCW_Cal_DF_V.k_FCW_MinAccelPdlPosVec_str)
#define k_FCW_HdTmAccelPos_ms    (FCW_Cal_DF_V.k_FCW_HdTmAccelPos_ms_str)
#define k_FCW_BrkPdlMoniTm_ms    (FCW_Cal_DF_V.k_FCW_BrkPdlMoniTm_ms_str)
#define k_FCW_HdTmBrkPdl_ms    (FCW_Cal_DF_V.k_FCW_HdTmBrkPdl_ms_str)
#define k_FCW_reserve11    (FCW_Cal_DF_V.k_FCW_reserve11_str)
#define k_FCW_HostSpdRTAdj_z    (FCW_Cal_DF_V.k_FCW_HostSpdRTAdj_z_str)
#define k_FCW_HostSpdRTAdj_x    (FCW_Cal_DF_V.k_FCW_HostSpdRTAdj_x_str)
#define k_FCW_ACCHostSpdRTAdj_z    (FCW_Cal_DF_V.k_FCW_ACCHostSpdRTAdj_z_str)
#define k_FCW_ACCHostSpdRTAdj_x    (FCW_Cal_DF_V.k_FCW_ACCHostSpdRTAdj_x_str)
#define k_FCW_ROCTrhdVehS    (FCW_Cal_DF_V.k_FCW_ROCTrhdVehS_str)
#define k_FCW_ROCTrhdVehM    (FCW_Cal_DF_V.k_FCW_ROCTrhdVehM_str)
#define k_FCW_VisnFCWCnfgEnbl    (FCW_Cal_DF_V.k_FCW_VisnFCWCnfgEnbl_str)
#define k_FCW_UseOnlyVisnFCW    (FCW_Cal_DF_V.k_FCW_UseOnlyVisnFCW_str)
#define k_FCW_Visn_IgnChmSupress    (FCW_Cal_DF_V.k_FCW_Visn_IgnChmSupress_str)
#define k_FCW_reserve12    (FCW_Cal_DF_V.k_FCW_reserve12_str)
#define k_FCW_VisnTTCTrhdSpd_x    (FCW_Cal_DF_V.k_FCW_VisnTTCTrhdSpd_x_str)
#define k_FCW_VisnTTCTrhd_z    (FCW_Cal_DF_V.k_FCW_VisnTTCTrhd_z_str[0])
#define k_FCW_VisnVRUTTCTrhd_z    (FCW_Cal_DF_V.k_FCW_VisnVRUTTCTrhd_z_str[0])
#define k_FCW_HostAccelMoniTm_ms    (FCW_Cal_DF_V.k_FCW_HostAccelMoniTm_ms_str)
#define k_FCW_reserve13    (FCW_Cal_DF_V.k_FCW_reserve13_str)
#define k_FCW_Visn_SensorLatency_mps    (FCW_Cal_DF_V.k_FCW_Visn_SensorLatency_mps_str)
#define k_FCW_Visn_SensorLatency_sec    (FCW_Cal_DF_V.k_FCW_Visn_SensorLatency_sec_str)
#define k_FCW_Visn_HostSpd_x    (FCW_Cal_DF_V.k_FCW_Visn_HostSpd_x_str)
#define k_FCW_Visn_RelSpd_x    (FCW_Cal_DF_V.k_FCW_Visn_RelSpd_x_str)
#define k_FCW_Visn_Rel_TTCTrhd_z    (FCW_Cal_DF_V.k_FCW_Visn_Rel_TTCTrhd_z_str[0])
#define k_FCW_CautnMinRngRt    (FCW_Cal_DF_V.k_FCW_CautnMinRngRt_str)
#define k_FCW_BrkPdlRateSuppr    (FCW_Cal_DF_V.k_FCW_BrkPdlRateSuppr_str)
#define k_FCW_VisnVRU_WarnEnbl    (FCW_Cal_DF_V.k_FCW_VisnVRU_WarnEnbl_str)
#define k_FCW_VisnVeh_NoHostCntrl    (FCW_Cal_DF_V.k_FCW_VisnVeh_NoHostCntrl_str)
#define k_FCW_VisnTTCPlausEnbl    (FCW_Cal_DF_V.k_FCW_VisnTTCPlausEnbl_str)
#define k_FCW_VisnTTCPlausMinSpeed    (FCW_Cal_DF_V.k_FCW_VisnTTCPlausMinSpeed_str)
#define k_FCW_VisnMinPlausTTC    (FCW_Cal_DF_V.k_FCW_VisnMinPlausTTC_str)
#define k_FCW_reserve14    (FCW_Cal_DF_V.k_FCW_reserve14_str)
#define k_FCW_VisnPlausTTC_z    (FCW_Cal_DF_V.k_FCW_VisnPlausTTC_z_str[0])
#define k_FCW_VisnMinPlausAccel_x    (FCW_Cal_DF_V.k_FCW_VisnMinPlausAccel_x_str)
#define k_FCW_VisnMesTTCEnbl    (FCW_Cal_DF_V.k_FCW_VisnMesTTCEnbl_str)
#define k_FCW_VRUReqConf    (FCW_Cal_DF_V.k_FCW_VRUReqConf_str)
#define k_FCW_reserve15    (FCW_Cal_DF_V.k_FCW_reserve15_str)
#define k_FCW_VRULockIn_y    (FCW_Cal_DF_V.k_FCW_VRULockIn_y_str)
#define k_FCW_AcuteWarnMaxTm_ms    (FCW_Cal_DF_V.k_FCW_AcuteWarnMaxTm_ms_str)
#define k_FCW_reserve16    (FCW_Cal_DF_V.k_FCW_reserve16_str)
#define k_FCW_VisnAcuTTCTrhd_z    (FCW_Cal_DF_V.k_FCW_VisnAcuTTCTrhd_z_str[0])
#define k_FCW_VisnVRUAcuTTCTrhd_z    (FCW_Cal_DF_V.k_FCW_VisnVRUAcuTTCTrhd_z_str[0])
#define k_FCW_VisnAcuTTCTrhdSpd_x    (FCW_Cal_DF_V.k_FCW_VisnAcuTTCTrhdSpd_x_str)
#define k_FCW_AcuteAlertHdTm_ms    (FCW_Cal_DF_V.k_FCW_AcuteAlertHdTm_ms_str)
#define k_FCW_AcuteHdTm_ms    (FCW_Cal_DF_V.k_FCW_AcuteHdTm_ms_str)
#define k_FCW_AcutWnBrakeConfig    (FCW_Cal_DF_V.k_FCW_AcutWnBrakeConfig_str)
#define k_FCW_reserve17    (FCW_Cal_DF_V.k_FCW_reserve17_str)
#define k_FCW_reserve18    (FCW_Cal_DF_V.k_FCW_reserve18_str)
#define k_FCW_AllowActuWnDuringACC    (FCW_Cal_DF_V.k_FCW_AllowActuWnDuringACC_str)
#define k_FCW_AllowActuWnTypes    (FCW_Cal_DF_V.k_FCW_AllowActuWnTypes_str)
#define k_FCW_BrkSuppressUse    (FCW_Cal_DF_V.k_FCW_BrkSuppressUse_str)
#define k_FCW_AcutWarnPFSuppr    (FCW_Cal_DF_V.k_FCW_AcutWarnPFSuppr_str)
#define k_FCW_reserve19    (FCW_Cal_DF_V.k_FCW_reserve19_str)
#define k_FCW_MaxSpdAcutWarnOff    (FCW_Cal_DF_V.k_FCW_MaxSpdAcutWarnOff_str)
#define k_FCW_MaxSpdAcutWarnOn    (FCW_Cal_DF_V.k_FCW_MaxSpdAcutWarnOn_str)
#define k_FCW_AcutForACCEngvsBrk    (FCW_Cal_DF_V.k_FCW_AcutForACCEngvsBrk_str)
#define k_FCW_reserve20    (FCW_Cal_DF_V.k_FCW_reserve20_str)
#define k_FCW_reserve21    (FCW_Cal_DF_V.k_FCW_reserve21_str)
#define k_FCW_HostSpdAcutRTGain_z    (FCW_Cal_DF_V.k_FCW_HostSpdAcutRTGain_z_str)
#define k_FCW_HostSpdAcutRTGain_x    (FCW_Cal_DF_V.k_FCW_HostSpdAcutRTGain_x_str)
#define k_FCW_VRUMaxAcutTTC_z    (FCW_Cal_DF_V.k_FCW_VRUMaxAcutTTC_z_str[0])
#define k_FCW_StatMaxAcutTTC_z    (FCW_Cal_DF_V.k_FCW_StatMaxAcutTTC_z_str[0])
#define k_FCW_VRUMaxAcutRng_z    (FCW_Cal_DF_V.k_FCW_VRUMaxAcutRng_z_str[0])
#define k_FCW_MaxAcutRngStat_z    (FCW_Cal_DF_V.k_FCW_MaxAcutRngStat_z_str[0])
#define k_FCW_MovMaxAcutTTC_z    (FCW_Cal_DF_V.k_FCW_MovMaxAcutTTC_z_str[0])
#define k_FCW_EnblWithCruiseOnOff    (FCW_Cal_DF_V.k_FCW_EnblWithCruiseOnOff_str)
#define k_FCW_UseUncompSpd    (FCW_Cal_DF_V.k_FCW_UseUncompSpd_str)
#define k_FCW_UseTTCFromFCWCalc    (FCW_Cal_DF_V.k_FCW_UseTTCFromFCWCalc_str)
#define k_FCW_AllowExtWarnBrkOny    (FCW_Cal_DF_V.k_FCW_AllowExtWarnBrkOny_str)
#define k_FCW_EnblSdRdrDgrdChk    (FCW_Cal_DF_V.k_FCW_EnblSdRdrDgrdChk_str)
#define k_FCW_SdRdrDgrdMinConf    (FCW_Cal_DF_V.k_FCW_SdRdrDgrdMinConf_str)
#define k_FCW_AcutWarnEnbl    (FCW_Cal_DF_V.k_FCW_AcutWarnEnbl_str)
#define k_FCW_UseLatRt_VehM    (FCW_Cal_DF_V.k_FCW_UseLatRt_VehM_str)
#define k_FCW_reserve22    (FCW_Cal_DF_V.k_FCW_reserve22_str)
#define k_FCW_MaxSpd_LongBike    (FCW_Cal_DF_V.k_FCW_MaxSpd_LongBike_str)
#define k_FCW_MaxSpd_VRU    (FCW_Cal_DF_V.k_FCW_MaxSpd_VRU_str)
#define k_FCW_MaxSpd_CrossBike    (FCW_Cal_DF_V.k_FCW_MaxSpd_CrossBike_str)
#define k_FCW_UseVRUHold    (FCW_Cal_DF_V.k_FCW_UseVRUHold_str)
#define k_FCW_MaxTTCRngAccelSrc    (FCW_Cal_DF_V.k_FCW_MaxTTCRngAccelSrc_str)
#define k_FCW_IgnoreOvrdForCautn    (FCW_Cal_DF_V.k_FCW_IgnoreOvrdForCautn_str)
#define k_FCW_OvrdCycleforInhibCautn    (FCW_Cal_DF_V.k_FCW_OvrdCycleforInhibCautn_str)
#define k_FCW_GeneralSpd_x    (FCW_Cal_DF_V.k_FCW_GeneralSpd_x_str)
#define k_FCW_HardTurnStrAngTrhd    (FCW_Cal_DF_V.k_FCW_HardTurnStrAngTrhd_str)
#define k_FCW_StrAngRateTrhd    (FCW_Cal_DF_V.k_FCW_StrAngRateTrhd_str)
#define k_FCW_StrInhibitCauEnblTm    (FCW_Cal_DF_V.k_FCW_StrInhibitCauEnblTm_str)
#define k_FCW_StrInhibitHoldTm    (FCW_Cal_DF_V.k_FCW_StrInhibitHoldTm_str)
#define k_FCW_CautnAllowRngRt    (FCW_Cal_DF_V.k_FCW_CautnAllowRngRt_str)
#define k_FCW_CautnEnablTm    (FCW_Cal_DF_V.k_FCW_CautnEnablTm_str)
#define k_FCW_CautnQuitEnablTm    (FCW_Cal_DF_V.k_FCW_CautnQuitEnablTm_str)
#define k_FCW_reserve23    (FCW_Cal_DF_V.k_FCW_reserve23_str)
#define k_FCW_HWTmGainCautnOn    (FCW_Cal_DF_V.k_FCW_HWTmGainCautnOn_str)
#define k_FCW_HWTmGainCautnOff    (FCW_Cal_DF_V.k_FCW_HWTmGainCautnOff_str)
#define k_FCW_VisnVehJAWarnSustain_ms    (FCW_Cal_DF_V.k_FCW_VisnVehJAWarnSustain_ms_str)
#define k_FCW_reserve24    (FCW_Cal_DF_V.k_FCW_reserve24_str)
#define k_FCW_NoJAMinSpd    (FCW_Cal_DF_V.k_FCW_NoJAMinSpd_str)
#define k_FCW_IgnoreVRUGOE    (FCW_Cal_DF_V.k_FCW_IgnoreVRUGOE_str)
#define k_FCW_IgnoreVehGOE    (FCW_Cal_DF_V.k_FCW_IgnoreVehGOE_str)
#define k_FCW_VRUFusHiConfLvl    (FCW_Cal_DF_V.k_FCW_VRUFusHiConfLvl_str)
#define k_FCW_VRUFusMedConfLvl    (FCW_Cal_DF_V.k_FCW_VRUFusMedConfLvl_str)
#define k_FCW_VRUVisMedConfLvl    (FCW_Cal_DF_V.k_FCW_VRUVisMedConfLvl_str)
#define k_FCW_RiderFusHiMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_RiderFusHiMinInPAgeTrhd_str)
#define k_FCW_PedFusHiMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_PedFusHiMinInPAgeTrhd_str)
#define k_FCW_RiderFusMedMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_RiderFusMedMinInPAgeTrhd_str)
#define k_FCW_PedFusMedMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_PedFusMedMinInPAgeTrhd_str)
#define k_FCW_RiderVisMedMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_RiderVisMedMinInPAgeTrhd_str)
#define k_FCW_PedVisMedMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_PedVisMedMinInPAgeTrhd_str)
#define k_FCW_RiderMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_RiderMinInPAgeTrhd_str)
#define k_FCW_PedMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_PedMinInPAgeTrhd_str)
#define k_FCW_TimeGapSet_z    (FCW_Cal_DF_V.k_FCW_TimeGapSet_z_str)
#define k_FCW_UseTTC_SpdPoints    (FCW_Cal_DF_V.k_FCW_UseTTC_SpdPoints_str)
#define k_FCW_BiLongWarnTTCTrhd_sec    (FCW_Cal_DF_V.k_FCW_BiLongWarnTTCTrhd_sec_str[0])
#define k_FCW_BiStatWarnTTCTrhd_sec    (FCW_Cal_DF_V.k_FCW_BiStatWarnTTCTrhd_sec_str[0])
#define k_FCW_BiCrossWarnTTCTrhd_sec    (FCW_Cal_DF_V.k_FCW_BiCrossWarnTTCTrhd_sec_str[0])
#define k_FCW_PedLongWarnTTCTrhd_sec    (FCW_Cal_DF_V.k_FCW_PedLongWarnTTCTrhd_sec_str[0])
#define k_FCW_PedStatWarnTTCTrhd_sec    (FCW_Cal_DF_V.k_FCW_PedStatWarnTTCTrhd_sec_str[0])
#define k_FCW_PedCrossWarnTTCTrhd_sec    (FCW_Cal_DF_V.k_FCW_PedCrossWarnTTCTrhd_sec_str[0])
#define k_FCW_MovWarnTTCTrhd_sec    (FCW_Cal_DF_V.k_FCW_MovWarnTTCTrhd_sec_str[0])
#define k_FCW_StatWarnTTCTrhd_sec    (FCW_Cal_DF_V.k_FCW_StatWarnTTCTrhd_sec_str[0])
#define k_FCW_ScpTurnLong_Delay    (FCW_Cal_DF_V.k_FCW_ScpTurnLong_Delay_str)
#define k_FCW_ChimeSuppr_Delay    (FCW_Cal_DF_V.k_FCW_ChimeSuppr_Delay_str)
#define k_FCW_BrkPdlPrsd_Delay    (FCW_Cal_DF_V.k_FCW_BrkPdlPrsd_Delay_str)
#define k_FCW_AcuteAvail_Delay    (FCW_Cal_DF_V.k_FCW_AcuteAvail_Delay_str)
#define k_FCW_MovUseRangeTriger    (FCW_Cal_DF_V.k_FCW_MovUseRangeTriger_str)
#define k_FCW_StatUseRangeTriger    (FCW_Cal_DF_V.k_FCW_StatUseRangeTriger_str)
#define k_FCW_reserve26    (FCW_Cal_DF_V.k_FCW_reserve26_str)
#define k_FCW_TTCTriggerSvntySet    (FCW_Cal_DF_V.k_FCW_TTCTriggerSvntySet_str)
#define k_FCW_TWDecelerateDetectAccel    (FCW_Cal_DF_V.k_FCW_TWDecelerateDetectAccel_str)
#define k_FCW_PedDecelerateDetectAccel    (FCW_Cal_DF_V.k_FCW_PedDecelerateDetectAccel_str)
#define k_FCW_VRUDecelerateDetectHdTm    (FCW_Cal_DF_V.k_FCW_VRUDecelerateDetectHdTm_str)
#define k_FCW_Mature_RE_thres    (FCW_Cal_DF_V.k_FCW_Mature_RE_thres_str)
#define k_FCW_reserve27    (FCW_Cal_DF_V.k_FCW_reserve27_str)
#define k_FCW_left_A0_RE_enter_thres    (FCW_Cal_DF_V.k_FCW_left_A0_RE_enter_thres_str)
#define k_FCW_left_A0_RE_exit_thres    (FCW_Cal_DF_V.k_FCW_left_A0_RE_exit_thres_str)
#define k_FCW_right_A0_RE_enter_thres    (FCW_Cal_DF_V.k_FCW_right_A0_RE_enter_thres_str)
#define k_FCW_right_A0_RE_exit_thres    (FCW_Cal_DF_V.k_FCW_right_A0_RE_exit_thres_str)
#define k_FCW_RE_EndRangeOffset    (FCW_Cal_DF_V.k_FCW_RE_EndRangeOffset_str)
#define k_FCW_RE_StartRangeOffset    (FCW_Cal_DF_V.k_FCW_RE_StartRangeOffset_str)
#define k_FCW_IgnoreVRU_RECheck    (FCW_Cal_DF_V.k_FCW_IgnoreVRU_RECheck_str)
#define k_FCW_IgnoreVRU_XolcCheck    (FCW_Cal_DF_V.k_FCW_IgnoreVRU_XolcCheck_str)
#define k_FCW_VRUReqConf_Fusion    (FCW_Cal_DF_V.k_FCW_VRUReqConf_Fusion_str)
#define k_FCW_IgnoreAEBTriggerSpd    (FCW_Cal_DF_V.k_FCW_IgnoreAEBTriggerSpd_str)
#define k_FCW_Default_Time_Offset    (FCW_Cal_DF_V.k_FCW_Default_Time_Offset_str)
#define k_FCW_HighSpdCrsLatVel    (FCW_Cal_DF_V.k_FCW_HighSpdCrsLatVel_str)
#define k_FCW_MaxSpdStatAcuWarnThresh    (FCW_Cal_DF_V.k_FCW_MaxSpdStatAcuWarnThresh_str)
#define k_FCW_MaxSpdAcutWarnThresh    (FCW_Cal_DF_V.k_FCW_MaxSpdAcutWarnThresh_str)
#define k_FCW_MaxSpdMov    (FCW_Cal_DF_V.k_FCW_MaxSpdMov_str)
#define k_FCW_MaxSpdCautnThresh    (FCW_Cal_DF_V.k_FCW_MaxSpdCautnThresh_str)
#define k_FCW_VehFusHiMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehFusHiMinInPAgeTrhd_str)
#define k_FCW_VehFusMedMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehFusMedMinInPAgeTrhd_str)
#define k_FCW_VehVisMedMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehVisMedMinInPAgeTrhd_str)
#define k_FCW_VehMinInPAgeTrhd    (FCW_Cal_DF_V.k_FCW_VehMinInPAgeTrhd_str)
#define k_FCW_MinTTCReq    (FCW_Cal_DF_V.k_FCW_MinTTCReq_str)
#define k_FCW_MinRangeReq    (FCW_Cal_DF_V.k_FCW_MinRangeReq_str)
#define k_FCW_AccActive_RedFac    (FCW_Cal_DF_V.k_FCW_AccActive_RedFac_str)
#define k_FCWSnvty_map_z    (FCW_Cal_DF_V.k_FCWSnvty_map_z_str)
#define k_FCWSnvty_map_x    (FCW_Cal_DF_V.k_FCWSnvty_map_x_str)
#define k_FCW_TTC_ACC_RedFac    (FCW_Cal_DF_V.k_FCW_TTC_ACC_RedFac_str)
#define k_FCW_DisHldTime_Latent    (FCW_Cal_DF_V.k_FCW_DisHldTime_Latent_str)
#define k_FCW_DisHldTime_PreWarn    (FCW_Cal_DF_V.k_FCW_DisHldTime_PreWarn_str)
#define k_FCW_Bypass_Spdlimit    (FCW_Cal_DF_V.k_FCW_Bypass_Spdlimit_str)
#define k_FCW_reserve28    (FCW_Cal_DF_V.k_FCW_reserve28_str)
#define k_FCW_reserve29    (FCW_Cal_DF_V.k_FCW_reserve29_str)
#define k_FCW_VehSpdBrkPoinys    (FCW_Cal_DF_V.k_FCW_VehSpdBrkPoinys_str)
#define k_FCW_CmftForLv1DWWarnDist    (FCW_Cal_DF_V.k_FCW_CmftForLv1DWWarnDist_str)
#define k_FCW_CmftForLv2DWWarnDist    (FCW_Cal_DF_V.k_FCW_CmftForLv2DWWarnDist_str)
#define k_FCW_CmftForLv3DWWarnDist    (FCW_Cal_DF_V.k_FCW_CmftForLv3DWWarnDist_str)
#define k_FCW_DW_MainLoopTime    (FCW_Cal_DF_V.k_FCW_DW_MainLoopTime_str)
#define k_FCW_DW_Enable    (FCW_Cal_DF_V.k_FCW_DW_Enable_str)
#define k_FCW_DW_UseDistLmt    (FCW_Cal_DF_V.k_FCW_DW_UseDistLmt_str)
#define k_FCW_reserve30    (FCW_Cal_DF_V.k_FCW_reserve30_str)
#define k_FCW_DW_DisResThresh    (FCW_Cal_DF_V.k_FCW_DW_DisResThresh_str)
#define k_FCW_DW_DisResLow    (FCW_Cal_DF_V.k_FCW_DW_DisResLow_str)
#define k_FCW_DW_DisResHigh    (FCW_Cal_DF_V.k_FCW_DW_DisResHigh_str)
#define k_FCW_DW_DisHysResLow    (FCW_Cal_DF_V.k_FCW_DW_DisHysResLow_str)
#define k_FCW_DW_DisHysResHigh    (FCW_Cal_DF_V.k_FCW_DW_DisHysResHigh_str)
#define k_FCW_DW_TimeResThresh    (FCW_Cal_DF_V.k_FCW_DW_TimeResThresh_str)
#define k_FCW_DW_TimeResLow    (FCW_Cal_DF_V.k_FCW_DW_TimeResLow_str)
#define k_FCW_DW_TimeResHigh    (FCW_Cal_DF_V.k_FCW_DW_TimeResHigh_str)
#define k_FCW_DW_TimeHysResLow    (FCW_Cal_DF_V.k_FCW_DW_TimeHysResLow_str)
#define k_FCW_DW_TimeHysResHigh    (FCW_Cal_DF_V.k_FCW_DW_TimeHysResHigh_str)
#define k_FCW_DW_MinActivationSpeed    (FCW_Cal_DF_V.k_FCW_DW_MinActivationSpeed_str)
#define k_FCW_DW_LowerCutoffSpeed    (FCW_Cal_DF_V.k_FCW_DW_LowerCutoffSpeed_str)
#define k_FCW_DW_MaxActivationSpeed    (FCW_Cal_DF_V.k_FCW_DW_MaxActivationSpeed_str)
#define k_FCW_DW_UpperCutoffSpeed    (FCW_Cal_DF_V.k_FCW_DW_UpperCutoffSpeed_str)
#define k_FCW_DW_IgnoreVehAhdInd    (FCW_Cal_DF_V.k_FCW_DW_IgnoreVehAhdInd_str)
#define k_FCW_IgnoreFCWTmChkAWB    (FCW_Cal_DF_V.k_FCW_IgnoreFCWTmChkAWB_str)
#define k_FCW_reserve32    (FCW_Cal_DF_V.k_FCW_reserve32_str)
#define k_FCW_DW_MinLVSpeed    (FCW_Cal_DF_V.k_FCW_DW_MinLVSpeed_str)
#define k_FCW_DW_LVCutoffSpeed    (FCW_Cal_DF_V.k_FCW_DW_LVCutoffSpeed_str)
#define k_FCW_DW_MaxRange    (FCW_Cal_DF_V.k_FCW_DW_MaxRange_str)
#define k_FCW_DW_MaxTime    (FCW_Cal_DF_V.k_FCW_DW_MaxTime_str)
#define k_FCW_DW_TimeTooLow    (FCW_Cal_DF_V.k_FCW_DW_TimeTooLow_str)
#define k_FCW_DW_TimeTooHigh    (FCW_Cal_DF_V.k_FCW_DW_TimeTooHigh_str)
#define k_FCW_DW_DisTooLow    (FCW_Cal_DF_V.k_FCW_DW_DisTooLow_str)
#define k_FCW_DW_DisTooHigh    (FCW_Cal_DF_V.k_FCW_DW_DisTooHigh_str)
#define k_FCW_DW_FLWTimeMax    (FCW_Cal_DF_V.k_FCW_DW_FLWTimeMax_str)
#define k_FCW_DW_FLWTimeMin    (FCW_Cal_DF_V.k_FCW_DW_FLWTimeMin_str)
#define k_FCW_DW_FLWDistMax    (FCW_Cal_DF_V.k_FCW_DW_FLWDistMax_str)
#define k_FCW_DW_FLWDistMin    (FCW_Cal_DF_V.k_FCW_DW_FLWDistMin_str)
#define k_FCW_DW_DisplayHoldTime    (FCW_Cal_DF_V.k_FCW_DW_DisplayHoldTime_str)
#define k_FCW_DW_CPIVChangeTime    (FCW_Cal_DF_V.k_FCW_DW_CPIVChangeTime_str)
#define k_FCW_DW_ALGO_LOOP_INT    (FCW_Cal_DF_V.k_FCW_DW_ALGO_LOOP_INT_str)
#define k_FCW_PreWarningMask    (FCW_Cal_DF_V.k_FCW_PreWarningMask_str)
#define k_FCW_reserve34    (FCW_Cal_DF_V.k_FCW_reserve34_str)
#define k_FCW_Customer    (FCW_Cal_DF_V.k_FCW_Customer_str)
#define k_FCW_Platform    (FCW_Cal_DF_V.k_FCW_Platform_str)
#define k_FCW_VehVariant    (FCW_Cal_DF_V.k_FCW_VehVariant_str)
#define k_FCW_ProductionModelYear    (FCW_Cal_DF_V.k_FCW_ProductionModelYear_str)
#define k_FCW_SensorConfig    (FCW_Cal_DF_V.k_FCW_SensorConfig_str)
#define k_Cal_FCW_major_version    (FCW_Cal_DF_V.k_Cal_FCW_major_version_str)
#define k_Cal_FCW_minor_version    (FCW_Cal_DF_V.k_Cal_FCW_minor_version_str)

#endif  /* _CAL_H */
