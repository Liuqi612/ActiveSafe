/****************************************************************************
 * Calibration file for FCW production code.
 * DD uses version 5 of the bas file.
 * File Name: D:\SenseTime_Model\ZDriver\02_DataDictionary\FCW\FCW_cal.c
 * Created: 2025/6/2        15:30:52 
 * From Excel file: DataDictionary_FCW_zDriver.xls
 * Calibration Values for project         
 * Calibrations for full application.
 * Set Description:         Initial Value
 *****************************************************************************/

#include "rtwtypes.h"
#include "FCW_cal.h"


/*
 *  COMPONENT:  \FCW
*/

/*
 *  COMPONENT:  \FDI
*/

/*
 *  COMPONENT:  \Version Control
*/
/* Global Variables */
/* Define the global structure of RAM image for EE Calibrations. Please note  
* that this RAM image is updated during every power ON from corresponding 
* Data Flash memory area. */
 


/* File Scope Variables */ 
/* Define a local structure for EE Calibrations placed in data flash.Please note  
* that these variable will not be used by application directly. This definition is 
* only to facilitate placing EE cals on fixed Data Flash area through #pragma  
* directive. 
*/ 


#define FCW_START_SEC_CAL_UNSPECIFIED

FCW_cal_T FCW_Cal_DF_V __attribute__((section(".data#"))) = {

 /* k_FCW_Enable_str */   (boolean)   1 ,

 /* k_FCW_FusHistConfLevel_str */   (uint8)   5 ,

 /* k_FCW_FusHiConfLevel_str */   (uint8)   4 ,

 /* k_FCW_FusMedConfLevel_str */   (uint8)   3 ,

 /* k_FCW_FusHiMinInPAgeTrhd_str */   (uint8)   2 ,

 /* k_FCW_FusHiMinInPAgeTrhdLg_str */   (uint8)   6 ,

 /* k_FCW_FusMedMinInPAgeTrhd_str */   (uint8)   3 ,

 /* k_FCW_FusMedMinInPAgeTrhdLg_str */   (uint8)   10 ,

 /* k_FCW_VisMedMinInPAgeTrhd_str */   (uint8)   3 ,

 /* k_FCW_VisMedMinInPAgeTrhdLg_str */   (uint8)   10 ,

 /* k_FCW_MinInPAgeTrhd_str */   (uint8)   6 ,

 /* k_FCW_MinInPAgeTrhdLg_str */   (uint8)   40 ,

 /* k_FCW_VehSHiEstMinInPAgeTrhd_str */   (uint8)   4 ,

 /* k_FCW_VehSHiMinInPAgeTrhd_str */   (uint8)   6 ,

 /* k_FCW_VehSMedMinInPAgeTrhd_str */   (uint8)   10 ,

 /* k_FCW_VehSMinInPAgeTrhd_str */   (uint8)   20 ,

 /* k_FCW_VehMHiEstMinInPAgeTrhd_str */   (uint8)   4 ,

 /* k_FCW_VehMHiMinInPAgeTrhd_str */   (uint8)   6 ,

 /* k_FCW_VehMMedMinInPAgeTrhd_str */   (uint8)   10 ,

 /* k_FCW_VehMMinInPAgeTrhd_str */   (uint8)   20 ,

 /* k_FCW_LatWarnHostAccThres_str */   (float32)  0.4F,

 /* k_FCW_MinSpd_str */   (float32)  2.0F,

 /* k_FCW_MaxRactnTmSpd_str */   (float32)  13.0F,

 /* k_FCW_MinSpdACC_str */   (float32)  8.375F,

 /* k_FCW_MaxSpdStat_str */   (float32)  36.111F,

 /* k_FCW_ObjPredPermitHeadAbs_str */   (float32)  10.0F,

 /* k_FCW_ObjCrossPermitHeadMin_str */   (float32)  80.0F,

 /* k_FCW_ObjCrossPermitHeadMax_str */   (float32)  100.0F,

 /* k_FCW_TmHdwyBuffer_z_str[ 7 ][ 2 ]*/   {
                            { (float32)0.296875F, (float32)0.296875F},
                            { (float32)0.296875F, (float32)0.296875F},
                            { (float32)0.296875F, (float32)0.296875F},
                            { (float32)0.296875F, (float32)0.296875F},
                            { (float32)0.296875F, (float32)0.296875F},
                            { (float32)0.296875F, (float32)0.296875F},
                            { (float32)0.296875F, (float32)0.296875F}},

 /* k_FCW_MovMaxTTC_z_str[ 7 ][ 2 ]*/   {
                            { (float32)2.8984375F, (float32)2.8984375F},
                            { (float32)2.8984375F, (float32)2.8984375F},
                            { (float32)3.203125F, (float32)3.203125F},
                            { (float32)3.203125F, (float32)3.203125F},
                            { (float32)3.203125F, (float32)3.203125F},
                            { (float32)3.5F, (float32)3.5F},
                            { (float32)3.5F, (float32)3.5F}},

 /* k_FCW_RangeBuffer_z_str[ 7 ][ 2 ]*/   {
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F}},

 /* k_FCW_LeadAccelAdj_z_str[ 7 ][ 2 ]*/   {
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F}},

 /* k_FCW_DeaccForReleAccPedl_str */   (float32)  -1.0F,

 /* k_FCW_ReactionTime_z_str[ 7 ][ 2 ]*/   {
                            { (float32)1.0F, (float32)0.5F},
                            { (float32)1.0F, (float32)0.5F},
                            { (float32)1.3046875F, (float32)0.703125F},
                            { (float32)1.3046875F, (float32)0.703125F},
                            { (float32)1.3046875F, (float32)0.703125F},
                            { (float32)1.6015625F, (float32)0.8984375F},
                            { (float32)1.6015625F, (float32)0.8984375F}},

 /* k_FCW_MaxRngStat_z_str[ 7 ][ 2 ]*/   {
                            { (float32)80.0F, (float32)80.0F},
                            { (float32)80.0F, (float32)80.0F},
                            { (float32)80.0F, (float32)80.0F},
                            { (float32)80.0F, (float32)80.0F},
                            { (float32)80.0F, (float32)80.0F},
                            { (float32)80.0F, (float32)80.0F},
                            { (float32)80.0F, (float32)80.0F}},

 /* k_FCW_VRUMaxRng_z_str[ 7 ][ 2 ]*/   {
                            { (float32)60.0F, (float32)60.0F},
                            { (float32)60.0F, (float32)60.0F},
                            { (float32)60.0F, (float32)60.0F},
                            { (float32)60.0F, (float32)60.0F},
                            { (float32)60.0F, (float32)60.0F},
                            { (float32)60.0F, (float32)60.0F},
                            { (float32)60.0F, (float32)60.0F}},

 /* k_FCW_StatRatnTmAdj_z_str[ 7 ][ 2 ]*/   {
                            { (float32)-0.1016F, (float32)-0.3048F},
                            { (float32)-0.1016F, (float32)-0.3048F},
                            { (float32)-0.1016F, (float32)-0.3048F},
                            { (float32)-0.1016F, (float32)-0.3048F},
                            { (float32)-0.1016F, (float32)-0.3048F},
                            { (float32)-0.1016F, (float32)-0.3048F},
                            { (float32)-0.1016F, (float32)-0.3048F}},

 /* k_FCW_ResponseAccel_z_str[ 7 ][ 2 ]*/   {
                            { (float32)-7.0F, (float32)-5.0F},
                            { (float32)-7.0F, (float32)-5.0F},
                            { (float32)-7.0F, (float32)-5.0F},
                            { (float32)-7.0F, (float32)-5.0F},
                            { (float32)-7.0F, (float32)-5.0F},
                            { (float32)-7.0F, (float32)-5.0F},
                            { (float32)-7.0F, (float32)-5.0F}},

 /* k_FCW_CautnAllowTailgate_z_str[ 7 ]*/   { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_FCW_MinTmBtAlerts_ms_str */   (uint16)   20000 ,

 /* k_FCW_reserve1_str */   (uint16)   0 ,

 /* k_FCW_StatMaxTTC_z_str[ 7 ][ 2 ]*/   {
                            { (float32)3.0234375F, (float32)3.0234375F},
                            { (float32)3.0234375F, (float32)3.0234375F},
                            { (float32)3.328125F, (float32)3.328125F},
                            { (float32)3.328125F, (float32)3.328125F},
                            { (float32)3.328125F, (float32)3.328125F},
                            { (float32)3.625F, (float32)3.625F},
                            { (float32)3.625F, (float32)3.625F}},

 /* k_FCW_VRUMaxTTC_z_str[ 7 ][ 2 ]*/   {
                            { (float32)2.75F, (float32)2.75F},
                            { (float32)2.75F, (float32)2.75F},
                            { (float32)2.95F, (float32)2.95F},
                            { (float32)2.95F, (float32)2.95F},
                            { (float32)2.95F, (float32)2.95F},
                            { (float32)3.25F, (float32)3.25F},
                            { (float32)3.25F, (float32)3.25F}},

 /* k_FCW_MaxStatYaw_str */   (float32)  5.0F,

 /* k_FCW_MaxSpdCautnOn_str */   (float32)  15.2778F,

 /* k_FCW_MaxSpdCautnOff_str */   (float32)  13.625F,

 /* k_FCW_CautnCoast_ms_str */   (uint16)   250 ,

 /* k_FCW_AWBAtvWarnThresTm_str */   (uint16)   300 ,

 /* k_FCW_MinAlertReqAccel_str */   (float32)  -2.0F,

 /* k_FCW_MinAlertReqRngRt_str */   (float32)  -1.0F,

 /* k_FCW_RTWhileSuppressed_str */   (float32)  0.5F,

 /* k_FCW_MaxRTWhileBraking_str */   (float32)  0.5F,

 /* k_FCW_RTRecoverTC_ms_str */   (uint16)   500 ,

 /* k_FCW_reserve3_str */   (uint16)   0 ,

 /* k_FCW_MaxDecelRate_str */   (float32)  -5.0F,

 /* k_FCW_MaxStrRate_str */   (float32)  50.0F,

 /* k_FCW_MinAccelPdl_str */   (float32)  -100.0F,

 /* k_FCW_MaxAccelPdl_str */   (float32)  80.0F,

 /* k_FCW_MinBrkPdl_str */   (float32)  -30.0F,

 /* k_FCW_MaxBrkPdl_str */   (float32)  1000.0F,

 /* k_FCW_HdTmSteer_ms_str */   (uint16)   400 ,

 /* k_FCW_HdTmAccelUp_ms_str */   (uint16)   1000 ,

 /* k_FCW_HdTmAccelDown_ms_str */   (uint16)   500 ,

 /* k_FCW_HdTmBrkUp_ms_str */   (uint16)   1000 ,

 /* k_FCW_HdTmBrkDown_ms_str */   (uint16)   1000 ,

 /* k_FCW_AlertHdTm_ms_str */   (uint16)   550 ,

 /* k_FCW_BrakePropnBuffer_str */   (float32)  0.5F,

 /* k_FCW_HostSpdFilterTm_ms_str */   (uint16)   150 ,

 /* k_FCW_RawCautnFilterTm_ms_str */   (uint16)   200 ,

 /* k_FCW_HdTmAccel_ms_str */   (uint16)   1000 ,

 /* k_FCW_reserve4_str */   (uint16)   0 ,

 /* k_FCW_GapSetgIn_x_str[ 7 ]*/   { (float32)0.0F, (float32)1.0F, (float32)2.0F, (float32)3.0F, (float32)4.0F, (float32)5.0F, (float32)6.0F},

 /* k_FCW_ACCOKIn_y_str[ 2 ]*/   { (float32)0.0F, (float32)1.0F},

 /* k_FCW_CautnAllowClosing_z_str[ 7 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_FCW_CautnTHW_z_str[ 7 ]*/   { (float32)0.4F, (float32)0.4F, (float32)0.7F, (float32)0.7F, (float32)0.7F, (float32)0.9F, (float32)0.9F},

 /* k_FCW_CautnTTC_z_str[ 7 ]*/   { (float32)2.0F, (float32)2.0F, (float32)2.5F, (float32)2.5F, (float32)2.5F, (float32)3.0F, (float32)3.0F},

 /* k_FCW_MaxHostAccel_str */   (float32)  1.5F,

 /* k_FCW_CautnTTCHys_str */   (float32)  4.0F,

 /* k_FCW_AllowBrkAlerts_str */   (boolean)   0 ,

 /* k_FCW_AccelPdlSuppr_str */   (boolean)   1 ,

 /* k_FCW_HostAccelSuppr_str */   (boolean)   1 ,

 /* k_FCW_ChmSuppressUse_str */   (uint8)   1 ,

 /* k_FCW_AllowTmngAdjACCBrk_str */   (uint8)   1 ,

 /* k_FCW_CautnforACCEngvsBrk_str */   (uint8)   0 ,

 /* k_FCW_AllowedDuringCrusCtrl_str */   (uint8)   15 ,

 /* k_FCW_AllowedTypes_str */   (uint8)   15 ,

 /* k_FCW_CautnPersist_ms_str */   (uint16)   100 ,

 /* k_FCW_HdTmDecel_ms_str */   (uint16)   1000 ,

 /* k_FCW_HostDecelSuppr_str */   (boolean)   1 ,

 /* k_FCW_reserve5_str */   (uint8)   0 ,

 /* k_FCW_reserve6_str */   (uint16)   0 ,

 /* k_FCW_MinHostAccel_str */   (float32)  -1.5F,

 /* k_FCW_CautnLatHys_str */   (float32)  10.0F,

 /* k_FCW_CautnLat_str */   (float32)  10.0F,

 /* k_FCW_MaxLat_str */   (float32)  1.5F,

 /* k_FCW_VRUMaxLat_str */   (float32)  1.0F,

 /* k_FCW_VehSReqConf_str */   (uint8)   3 ,

 /* k_FCW_reserve7_str */   (uint8)   0 ,

 /* k_FCW_reserve8_str */   (uint16)   0 ,

 /* k_FCW_VRUSensitize_str */   (float32)  1.0F,

 /* k_FCW_HostSpeed_x_str[ 8 ]*/   { (float32)1.0F, (float32)5.0F, (float32)7.0F, (float32)9.0F, (float32)11.0F, (float32)16.0F, (float32)20.0F, (float32)27.0F},

 /* k_FCW_MinTaperProp_z_str[ 8 ]*/   { (float32)0.95F, (float32)0.45F, (float32)0.2F, (float32)0.0F, (float32)0.75F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_FCW_VehMReqConf_str */   (uint8)   3 ,

 /* k_FCW_VehMUseLatRt_str */   (boolean)   1 ,

 /* k_FCW_reserve9_str */   (uint16)   0 ,

 /* k_FCW_FullXolc_str */   (float32)  0.5F,

 /* k_FCW_NegXolc_str */   (float32)  0.25F,

 /* k_FCW_StrTurnTrhd_str */   (float32)  10.0F,

 /* k_FCW_StrTrhd_str */   (float32)  10.0F,

 /* k_FCW_XolcTrhd_str */   (float32)  0.7F,

 /* k_FCW_UseXolc_str */   (boolean)   1 ,

 /* k_FCW_AccelPdlPosSuppr_str */   (boolean)   1 ,

 /* k_FCW_BrkPdlSuppr_str */   (boolean)   1 ,

 /* k_FCW_reserve10_str */   (uint8)   0 ,

 /* k_FCW_MaxAccelPdlPos_str */   (float32)  60.0F,

 /* k_FCW_MaxAccelPdlPosVec_str[ 9 ]*/   { (float32)7.0F, (float32)8.5F, (float32)15.1F, (float32)16.6F, (float32)18.2F, (float32)20.3F, (float32)23.2F, (float32)24.4F, (float32)45.0F},

 /* k_FCW_MinAccelPdlPosVec_str[ 9 ]*/   { (float32)0.5F, (float32)0.5F, (float32)4.1F, (float32)5.6F, (float32)7.2F, (float32)10.3F, (float32)10.3F, (float32)12.4F, (float32)12.4F},

 /* k_FCW_HdTmAccelPos_ms_str */   (uint16)   3000 ,

 /* k_FCW_BrkPdlMoniTm_ms_str */   (uint16)   200 ,

 /* k_FCW_HdTmBrkPdl_ms_str */   (uint16)   3000 ,

 /* k_FCW_reserve11_str */   (uint16)   0 ,

 /* k_FCW_HostSpdRTAdj_z_str[ 8 ]*/   { (float32)0.0F, (float32)0.0F, (float32)-0.15F, (float32)-0.5F, (float32)0.25F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_FCW_HostSpdRTAdj_x_str[ 8 ]*/   { (float32)1.0F, (float32)5.0F, (float32)7.0F, (float32)9.0F, (float32)11.0F, (float32)16.0F, (float32)20.0F, (float32)27.0F},

 /* k_FCW_ACCHostSpdRTAdj_z_str[ 8 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_FCW_ACCHostSpdRTAdj_x_str[ 8 ]*/   { (float32)1.0F, (float32)5.0F, (float32)7.0F, (float32)9.0F, (float32)11.0F, (float32)16.0F, (float32)20.0F, (float32)27.0F},

 /* k_FCW_ROCTrhdVehS_str */   (uint16)   1000 ,

 /* k_FCW_ROCTrhdVehM_str */   (uint16)   0 ,

 /* k_FCW_VisnFCWCnfgEnbl_str */   (boolean)   0 ,

 /* k_FCW_UseOnlyVisnFCW_str */   (boolean)   0 ,

 /* k_FCW_Visn_IgnChmSupress_str */   (boolean)   0 ,

 /* k_FCW_reserve12_str */   (uint8)   0 ,

 /* k_FCW_VisnTTCTrhdSpd_x_str[ 8 ]*/   { (float32)0.0F, (float32)8.889F, (float32)11.11F, (float32)14.44F, (float32)17.778F, (float32)21.11F, (float32)24.44F, (float32)26.667F},

 /* k_FCW_VisnTTCTrhd_z_str[ 7 ][ 8 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)1.3F, (float32)1.3F, (float32)2.25F, (float32)2.325F, (float32)2.4F, (float32)2.475F, (float32)2.55F, (float32)2.6F},
                            { (float32)1.4F, (float32)1.4F, (float32)2.55F, (float32)2.625F, (float32)2.7F, (float32)2.775F, (float32)2.85F, (float32)2.9F},
                            { (float32)1.4F, (float32)1.4F, (float32)2.55F, (float32)2.625F, (float32)2.7F, (float32)2.775F, (float32)2.85F, (float32)2.9F},
                            { (float32)1.4F, (float32)1.4F, (float32)2.55F, (float32)2.625F, (float32)2.7F, (float32)2.775F, (float32)2.85F, (float32)2.9F},
                            { (float32)1.5F, (float32)1.5F, (float32)2.85F, (float32)2.925F, (float32)3.0F, (float32)3.075F, (float32)3.15F, (float32)3.2F},
                            { (float32)1.5F, (float32)1.5F, (float32)2.85F, (float32)2.925F, (float32)3.0F, (float32)3.075F, (float32)3.15F, (float32)3.2F}},

 /* k_FCW_VisnVRUTTCTrhd_z_str[ 7 ][ 8 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)1.3F, (float32)1.3F, (float32)2.25F, (float32)2.325F, (float32)2.4F, (float32)2.475F, (float32)2.55F, (float32)2.6F},
                            { (float32)1.4F, (float32)1.4F, (float32)2.55F, (float32)2.625F, (float32)2.7F, (float32)2.775F, (float32)2.85F, (float32)2.9F},
                            { (float32)1.4F, (float32)1.4F, (float32)2.55F, (float32)2.625F, (float32)2.7F, (float32)2.775F, (float32)2.85F, (float32)2.9F},
                            { (float32)1.4F, (float32)1.4F, (float32)2.55F, (float32)2.625F, (float32)2.7F, (float32)2.775F, (float32)2.85F, (float32)2.9F},
                            { (float32)1.5F, (float32)1.5F, (float32)2.85F, (float32)2.925F, (float32)3.0F, (float32)3.075F, (float32)3.15F, (float32)3.2F},
                            { (float32)1.5F, (float32)1.5F, (float32)2.85F, (float32)2.925F, (float32)3.0F, (float32)3.075F, (float32)3.15F, (float32)3.2F}},

 /* k_FCW_HostAccelMoniTm_ms_str */   (uint16)   0 ,

 /* k_FCW_reserve13_str */   (uint16)   0 ,

 /* k_FCW_Visn_SensorLatency_mps_str[ 8 ]*/   { (float32)0.0F, (float32)8.889F, (float32)11.11F, (float32)14.44F, (float32)17.778F, (float32)21.11F, (float32)24.44F, (float32)26.667F},

 /* k_FCW_Visn_SensorLatency_sec_str[ 8 ]*/   { (float32)0.3F, (float32)0.25F, (float32)0.3F, (float32)0.22F, (float32)0.22F, (float32)0.226F, (float32)0.225F, (float32)0.22F},

 /* k_FCW_Visn_HostSpd_x_str[ 8 ]*/   { (float32)5.0F, (float32)8.889F, (float32)11.11F, (float32)14.44F, (float32)17.778F, (float32)21.11F, (float32)24.44F, (float32)26.667F},

 /* k_FCW_Visn_RelSpd_x_str[ 8 ]*/   { (float32)-26.667F, (float32)-24.44F, (float32)-21.11F, (float32)-17.778F, (float32)-14.44F, (float32)-11.11F, (float32)-8.889F, (float32)-5.0F},

 /* k_FCW_Visn_Rel_TTCTrhd_z_str[ 8 ][ 8 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F}},

 /* k_FCW_CautnMinRngRt_str */   (float32)  2.0F,

 /* k_FCW_BrkPdlRateSuppr_str */   (boolean)   0 ,

 /* k_FCW_VisnVRU_WarnEnbl_str */   (boolean)   1 ,

 /* k_FCW_VisnVeh_NoHostCntrl_str */   (boolean)   1 ,

 /* k_FCW_VisnTTCPlausEnbl_str */   (boolean)   1 ,

 /* k_FCW_VisnTTCPlausMinSpeed_str */   (uint8)   0 ,

 /* k_FCW_VisnMinPlausTTC_str */   (uint8)   4 ,

 /* k_FCW_reserve14_str */   (uint16)   0 ,

 /* k_FCW_VisnPlausTTC_z_str[ 8 ][ 9 ]*/   {
                            { (float32)25.0F, (float32)25.0F, (float32)25.0F, (float32)25.0F, (float32)20.0F, (float32)20.0F, (float32)20.0F, (float32)20.0F, (float32)20.0F},
                            { (float32)25.0F, (float32)25.0F, (float32)5.0F, (float32)2.25F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.8F, (float32)2.0F},
                            { (float32)25.0F, (float32)10.0F, (float32)2.75F, (float32)1.8F, (float32)1.5F, (float32)1.25F, (float32)1.25F, (float32)1.5F, (float32)2.0F},
                            { (float32)25.0F, (float32)5.0F, (float32)1.5F, (float32)0.9F, (float32)0.7F, (float32)0.5F, (float32)0.5F, (float32)0.9F, (float32)1.0F},
                            { (float32)20.0F, (float32)3.5F, (float32)1.4F, (float32)0.8F, (float32)0.6F, (float32)0.5F, (float32)0.5F, (float32)0.9F, (float32)1.0F},
                            { (float32)10.0F, (float32)3.0F, (float32)1.25F, (float32)0.7F, (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.9F, (float32)1.0F},
                            { (float32)10.0F, (float32)2.5F, (float32)1.1F, (float32)0.6F, (float32)0.4F, (float32)0.3F, (float32)0.3F, (float32)0.5F, (float32)0.75F},
                            { (float32)10.0F, (float32)2.0F, (float32)0.9F, (float32)0.5F, (float32)0.3F, (float32)0.2F, (float32)0.2F, (float32)0.5F, (float32)0.75F}},

 /* k_FCW_VisnMinPlausAccel_x_str[ 9 ]*/   { (float32)-3.92F, (float32)-2.93F, (float32)-2.1F, (float32)-1.5F, (float32)-0.75F, (float32)-0.5F, (float32)0.0F, (float32)0.4F, (float32)0.75F},

 /* k_FCW_VisnMesTTCEnbl_str */   (boolean)   1 ,

 /* k_FCW_VRUReqConf_str */   (uint8)   3 ,

 /* k_FCW_reserve15_str */   (uint16)   0 ,

 /* k_FCW_VRULockIn_y_str[ 2 ]*/   { (float32)0.0F, (float32)1.0F},

 /* k_FCW_AcuteWarnMaxTm_ms_str */   (uint16)   20000 ,

 /* k_FCW_reserve16_str */   (uint16)   0 ,

 /* k_FCW_VisnAcuTTCTrhd_z_str[ 7 ][ 8 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.8F, (float32)0.8F, (float32)1.5F, (float32)1.6F, (float32)1.65F, (float32)1.7F, (float32)1.75F, (float32)1.8F},
                            { (float32)0.9F, (float32)0.9F, (float32)1.6F, (float32)1.7F, (float32)1.75F, (float32)1.8F, (float32)1.85F, (float32)1.9F},
                            { (float32)0.9F, (float32)0.9F, (float32)1.6F, (float32)1.7F, (float32)1.75F, (float32)1.8F, (float32)1.85F, (float32)1.9F},
                            { (float32)0.9F, (float32)0.9F, (float32)1.6F, (float32)1.7F, (float32)1.75F, (float32)1.8F, (float32)1.85F, (float32)1.9F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.65F, (float32)1.77F, (float32)1.8F, (float32)1.85F, (float32)1.9F, (float32)1.95F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.65F, (float32)1.77F, (float32)1.8F, (float32)1.85F, (float32)1.9F, (float32)1.95F}},

 /* k_FCW_VisnVRUAcuTTCTrhd_z_str[ 7 ][ 8 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.8F, (float32)0.8F, (float32)1.5F, (float32)1.6F, (float32)1.65F, (float32)1.7F, (float32)1.75F, (float32)1.8F},
                            { (float32)0.9F, (float32)0.9F, (float32)1.6F, (float32)1.7F, (float32)1.75F, (float32)1.8F, (float32)1.85F, (float32)1.9F},
                            { (float32)0.9F, (float32)0.9F, (float32)1.6F, (float32)1.7F, (float32)1.75F, (float32)1.8F, (float32)1.85F, (float32)1.9F},
                            { (float32)0.9F, (float32)0.9F, (float32)1.6F, (float32)1.7F, (float32)1.75F, (float32)1.8F, (float32)1.85F, (float32)1.9F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.65F, (float32)1.77F, (float32)1.8F, (float32)1.85F, (float32)1.9F, (float32)1.95F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.65F, (float32)1.77F, (float32)1.8F, (float32)1.85F, (float32)1.9F, (float32)1.95F}},

 /* k_FCW_VisnAcuTTCTrhdSpd_x_str[ 8 ]*/   { (float32)0.0F, (float32)8.889F, (float32)11.11F, (float32)14.44F, (float32)17.778F, (float32)21.11F, (float32)24.44F, (float32)26.667F},

 /* k_FCW_AcuteAlertHdTm_ms_str */   (uint16)   300 ,

 /* k_FCW_AcuteHdTm_ms_str */   (uint16)   550 ,

 /* k_FCW_AcutWnBrakeConfig_str */   (boolean)   1 ,

 /* k_FCW_reserve17_str */   (uint8)   0 ,

 /* k_FCW_reserve18_str */   (uint16)   0 ,

 /* k_FCW_AllowActuWnDuringACC_str */   (uint16)   1 ,

 /* k_FCW_AllowActuWnTypes_str */   (uint16)   11 ,

 /* k_FCW_BrkSuppressUse_str */   (boolean)   1 ,

 /* k_FCW_AcutWarnPFSuppr_str */   (boolean)   0 ,

 /* k_FCW_reserve19_str */   (uint16)   0 ,

 /* k_FCW_MaxSpdAcutWarnOff_str */   (float32)  6.9F,

 /* k_FCW_MaxSpdAcutWarnOn_str */   (float32)  8.33F,

 /* k_FCW_AcutForACCEngvsBrk_str */   (uint8)   1 ,

 /* k_FCW_reserve20_str */   (uint8)   0 ,

 /* k_FCW_reserve21_str */   (uint16)   0 ,

 /* k_FCW_HostSpdAcutRTGain_z_str[ 8 ]*/   { (float32)0.2F, (float32)0.25F, (float32)0.3F, (float32)0.3F, (float32)0.35F, (float32)0.4F, (float32)0.45F, (float32)0.55F},

 /* k_FCW_HostSpdAcutRTGain_x_str[ 8 ]*/   { (float32)1.0F, (float32)5.0F, (float32)7.0F, (float32)9.0F, (float32)11.0F, (float32)16.0F, (float32)20.0F, (float32)27.0F},

 /* k_FCW_VRUMaxAcutTTC_z_str[ 7 ][ 2 ]*/   {
                            { (float32)2.0F, (float32)2.0F},
                            { (float32)2.0F, (float32)2.0F},
                            { (float32)2.2F, (float32)2.2F},
                            { (float32)2.2F, (float32)2.2F},
                            { (float32)2.2F, (float32)2.2F},
                            { (float32)2.5F, (float32)2.5F},
                            { (float32)2.5F, (float32)2.5F}},

 /* k_FCW_StatMaxAcutTTC_z_str[ 7 ][ 2 ]*/   {
                            { (float32)2.0F, (float32)2.0F},
                            { (float32)2.0F, (float32)2.0F},
                            { (float32)2.25F, (float32)2.25F},
                            { (float32)2.25F, (float32)2.25F},
                            { (float32)2.25F, (float32)2.25F},
                            { (float32)2.5F, (float32)2.5F},
                            { (float32)2.5F, (float32)2.5F}},

 /* k_FCW_VRUMaxAcutRng_z_str[ 7 ][ 2 ]*/   {
                            { (float32)30.0F, (float32)30.0F},
                            { (float32)30.0F, (float32)30.0F},
                            { (float32)30.0F, (float32)30.0F},
                            { (float32)30.0F, (float32)30.0F},
                            { (float32)30.0F, (float32)30.0F},
                            { (float32)30.0F, (float32)30.0F},
                            { (float32)30.0F, (float32)30.0F}},

 /* k_FCW_MaxAcutRngStat_z_str[ 7 ][ 2 ]*/   {
                            { (float32)45.0F, (float32)45.0F},
                            { (float32)45.0F, (float32)45.0F},
                            { (float32)45.0F, (float32)45.0F},
                            { (float32)45.0F, (float32)45.0F},
                            { (float32)45.0F, (float32)45.0F},
                            { (float32)45.0F, (float32)45.0F},
                            { (float32)45.0F, (float32)45.0F}},

 /* k_FCW_MovMaxAcutTTC_z_str[ 7 ][ 2 ]*/   {
                            { (float32)2.2F, (float32)2.2F},
                            { (float32)2.2F, (float32)2.2F},
                            { (float32)2.4F, (float32)2.4F},
                            { (float32)2.4F, (float32)2.4F},
                            { (float32)2.4F, (float32)2.4F},
                            { (float32)2.6F, (float32)2.6F},
                            { (float32)2.6F, (float32)2.6F}},

 /* k_FCW_EnblWithCruiseOnOff_str */   (boolean)   0 ,

 /* k_FCW_UseUncompSpd_str */   (boolean)   1 ,

 /* k_FCW_UseTTCFromFCWCalc_str */   (boolean)   0 ,

 /* k_FCW_AllowExtWarnBrkOny_str */   (boolean)   0 ,

 /* k_FCW_EnblSdRdrDgrdChk_str */   (boolean)   1 ,

 /* k_FCW_SdRdrDgrdMinConf_str */   (uint8)   3 ,

 /* k_FCW_AcutWarnEnbl_str */   (boolean)   1 ,

 /* k_FCW_UseLatRt_VehM_str */   (boolean)   0 ,

 /* k_FCW_reserve22_str */   (uint8)   0 ,

 /* k_FCW_MaxSpd_LongBike_str */   (float32)  41.667F,

 /* k_FCW_MaxSpd_VRU_str */   (float32)  23.611F,

 /* k_FCW_MaxSpd_CrossBike_str */   (float32)  23.611F,

 /* k_FCW_UseVRUHold_str */   (boolean)   0 ,

 /* k_FCW_MaxTTCRngAccelSrc_str */   (boolean)   1 ,

 /* k_FCW_IgnoreOvrdForCautn_str */   (boolean)   0 ,

 /* k_FCW_OvrdCycleforInhibCautn_str */   (uint8)   100 ,

 /* k_FCW_GeneralSpd_x_str[ 9 ]*/   { (float32)2.7F, (float32)5.6F, (float32)8.3F, (float32)11.1F, (float32)13.9F, (float32)16.7F, (float32)22.2F, (float32)27.8F, (float32)33.3F},

 /* k_FCW_HardTurnStrAngTrhd_str[ 9 ]*/   { (float32)120.0F, (float32)80.0F, (float32)75.0F, (float32)65.0F, (float32)60.0F, (float32)55.0F, (float32)50.0F, (float32)45.0F, (float32)45.0F},

 /* k_FCW_StrAngRateTrhd_str[ 9 ]*/   { (float32)80.0F, (float32)80.0F, (float32)80.0F, (float32)80.0F, (float32)80.0F, (float32)80.0F, (float32)80.0F, (float32)80.0F, (float32)80.0F},

 /* k_FCW_StrInhibitCauEnblTm_str */   (uint16)   500 ,

 /* k_FCW_StrInhibitHoldTm_str */   (uint16)   2000 ,

 /* k_FCW_CautnAllowRngRt_str */   (float32)  2.0F,

 /* k_FCW_CautnEnablTm_str[ 7 ]*/   { (float32)8000.0F, (float32)8000.0F, (float32)7000.0F, (float32)7000.0F, (float32)7000.0F, (float32)5000.0F, (float32)5000.0F},

 /* k_FCW_CautnQuitEnablTm_str */   (uint16)   500 ,

 /* k_FCW_reserve23_str */   (uint16)   0 ,

 /* k_FCW_HWTmGainCautnOn_str */   (float32)  1.0F,

 /* k_FCW_HWTmGainCautnOff_str */   (float32)  1.3F,

 /* k_FCW_VisnVehJAWarnSustain_ms_str */   (uint16)   0 ,

 /* k_FCW_reserve24_str */   (uint16)   0 ,

 /* k_FCW_NoJAMinSpd_str */   (float32)  1.5F,

 /* k_FCW_IgnoreVRUGOE_str */   (boolean)   0 ,

 /* k_FCW_IgnoreVehGOE_str */   (boolean)   0 ,

 /* k_FCW_VRUFusHiConfLvl_str */   (uint8)   5 ,

 /* k_FCW_VRUFusMedConfLvl_str */   (uint8)   4 ,

 /* k_FCW_VRUVisMedConfLvl_str */   (uint8)   3 ,

 /* k_FCW_RiderFusHiMinInPAgeTrhd_str */   (uint8)   8 ,

 /* k_FCW_PedFusHiMinInPAgeTrhd_str */   (uint8)   2 ,

 /* k_FCW_RiderFusMedMinInPAgeTrhd_str */   (uint8)   8 ,

 /* k_FCW_PedFusMedMinInPAgeTrhd_str */   (uint8)   8 ,

 /* k_FCW_RiderVisMedMinInPAgeTrhd_str */   (uint8)   8 ,

 /* k_FCW_PedVisMedMinInPAgeTrhd_str */   (uint8)   8 ,

 /* k_FCW_RiderMinInPAgeTrhd_str */   (uint8)   8 ,

 /* k_FCW_PedMinInPAgeTrhd_str */   (uint8)   8 ,

 /* k_FCW_TimeGapSet_z_str[ 7 ]*/   { (uint8)  1 , (uint8)  1 , (uint8)  2 , (uint8)  2 , (uint8)  2 , (uint8)  3 , (uint8)  3 },

 /* k_FCW_UseTTC_SpdPoints_str[ 9 ]*/   { (float32)1.375F, (float32)2.75F, (float32)5.5625F, (float32)8.3125F, (float32)11.125F, (float32)13.875F, (float32)16.6875F, (float32)19.4375F, (float32)22.25F},

 /* k_FCW_BiLongWarnTTCTrhd_sec_str[ 9 ][ 3 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.92F, (float32)1.12F, (float32)1.32F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.23F, (float32)1.53F, (float32)1.83F},
                            { (float32)1.8F, (float32)2.1F, (float32)2.4F},
                            { (float32)2.0F, (float32)2.3F, (float32)2.6F},
                            { (float32)2.1F, (float32)2.4F, (float32)2.7F},
                            { (float32)2.2F, (float32)2.5F, (float32)2.8F}},

 /* k_FCW_BiStatWarnTTCTrhd_sec_str[ 9 ][ 3 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.92F, (float32)1.12F, (float32)1.32F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.23F, (float32)1.53F, (float32)1.83F},
                            { (float32)1.8F, (float32)2.1F, (float32)2.4F},
                            { (float32)2.0F, (float32)2.3F, (float32)2.6F},
                            { (float32)2.1F, (float32)2.4F, (float32)2.7F},
                            { (float32)2.2F, (float32)2.5F, (float32)2.8F}},

 /* k_FCW_BiCrossWarnTTCTrhd_sec_str[ 9 ][ 3 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.92F, (float32)1.12F, (float32)1.32F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.23F, (float32)1.53F, (float32)1.83F},
                            { (float32)1.8F, (float32)2.1F, (float32)2.4F},
                            { (float32)2.0F, (float32)2.3F, (float32)2.6F},
                            { (float32)2.1F, (float32)2.4F, (float32)2.7F},
                            { (float32)2.2F, (float32)2.5F, (float32)2.8F}},

 /* k_FCW_PedLongWarnTTCTrhd_sec_str[ 9 ][ 3 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.92F, (float32)1.12F, (float32)1.32F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.23F, (float32)1.53F, (float32)1.83F},
                            { (float32)1.8F, (float32)2.1F, (float32)2.4F},
                            { (float32)2.0F, (float32)2.3F, (float32)2.6F},
                            { (float32)2.1F, (float32)2.4F, (float32)2.7F},
                            { (float32)2.2F, (float32)2.5F, (float32)2.8F}},

 /* k_FCW_PedStatWarnTTCTrhd_sec_str[ 9 ][ 3 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.92F, (float32)1.12F, (float32)1.32F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.23F, (float32)1.53F, (float32)1.83F},
                            { (float32)1.8F, (float32)2.1F, (float32)2.4F},
                            { (float32)2.0F, (float32)2.3F, (float32)2.6F},
                            { (float32)2.1F, (float32)2.4F, (float32)2.7F},
                            { (float32)2.2F, (float32)2.5F, (float32)2.8F}},

 /* k_FCW_PedCrossWarnTTCTrhd_sec_str[ 9 ][ 3 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.92F, (float32)1.12F, (float32)1.32F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.23F, (float32)1.53F, (float32)1.83F},
                            { (float32)1.8F, (float32)2.1F, (float32)2.4F},
                            { (float32)2.0F, (float32)2.3F, (float32)2.6F},
                            { (float32)2.1F, (float32)2.4F, (float32)2.7F},
                            { (float32)2.2F, (float32)2.5F, (float32)2.8F}},

 /* k_FCW_MovWarnTTCTrhd_sec_str[ 9 ][ 3 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.92F, (float32)1.12F, (float32)1.32F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.23F, (float32)1.53F, (float32)1.83F},
                            { (float32)2.22F, (float32)2.52F, (float32)2.82F},
                            { (float32)2.4F, (float32)2.7F, (float32)3.0F},
                            { (float32)2.68F, (float32)2.98F, (float32)3.28F},
                            { (float32)2.85F, (float32)3.15F, (float32)3.45F}},

 /* k_FCW_StatWarnTTCTrhd_sec_str[ 9 ][ 3 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.92F, (float32)1.12F, (float32)1.32F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.12F, (float32)1.32F, (float32)1.52F},
                            { (float32)1.23F, (float32)1.53F, (float32)1.83F},
                            { (float32)2.22F, (float32)2.52F, (float32)2.82F},
                            { (float32)2.4F, (float32)2.7F, (float32)3.0F},
                            { (float32)2.68F, (float32)2.98F, (float32)3.28F},
                            { (float32)2.85F, (float32)3.15F, (float32)3.45F}},

 /* k_FCW_ScpTurnLong_Delay_str */   (float32)  1.6F,

 /* k_FCW_ChimeSuppr_Delay_str */   (float32)  0.5F,

 /* k_FCW_BrkPdlPrsd_Delay_str */   (float32)  0.3F,

 /* k_FCW_AcuteAvail_Delay_str[ 8 ]*/   { (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.5F},

 /* k_FCW_MovUseRangeTriger_str */   (boolean)   0 ,

 /* k_FCW_StatUseRangeTriger_str */   (boolean)   0 ,

 /* k_FCW_reserve26_str */   (uint16)   0 ,

 /* k_FCW_TTCTriggerSvntySet_str[ 3 ]*/   { (float32)1.0F, (float32)2.0F, (float32)3.0F},

 /* k_FCW_TWDecelerateDetectAccel_str */   (float32)  2.8F,

 /* k_FCW_PedDecelerateDetectAccel_str */   (float32)  1.4F,

 /* k_FCW_VRUDecelerateDetectHdTm_str */   (uint16)   500 ,

 /* k_FCW_Mature_RE_thres_str */   (uint8)   2 ,

 /* k_FCW_reserve27_str */   (uint8)   0 ,

 /* k_FCW_left_A0_RE_enter_thres_str */   (float32)  0.6F,

 /* k_FCW_left_A0_RE_exit_thres_str */   (float32)  0.3F,

 /* k_FCW_right_A0_RE_enter_thres_str */   (float32)  -0.6F,

 /* k_FCW_right_A0_RE_exit_thres_str */   (float32)  -0.3F,

 /* k_FCW_RE_EndRangeOffset_str */   (float32)  4.0F,

 /* k_FCW_RE_StartRangeOffset_str */   (float32)  -2.0F,

 /* k_FCW_IgnoreVRU_RECheck_str */   (boolean)   0 ,

 /* k_FCW_IgnoreVRU_XolcCheck_str */   (boolean)   0 ,

 /* k_FCW_VRUReqConf_Fusion_str */   (uint8)   5 ,

 /* k_FCW_IgnoreAEBTriggerSpd_str */   (boolean)   0 ,

 /* k_FCW_Default_Time_Offset_str */   (float32)  0.1F,

 /* k_FCW_HighSpdCrsLatVel_str */   (float32)  3.0F,

 /* k_FCW_MaxSpdStatAcuWarnThresh_str */   (float32)  23.611F,

 /* k_FCW_MaxSpdAcutWarnThresh_str */   (float32)  41.667F,

 /* k_FCW_MaxSpdMov_str */   (float32)  41.667F,

 /* k_FCW_MaxSpdCautnThresh_str */   (float32)  41.667F,

 /* k_FCW_VehFusHiMinInPAgeTrhd_str */   (uint8)   2 ,

 /* k_FCW_VehFusMedMinInPAgeTrhd_str */   (uint8)   4 ,

 /* k_FCW_VehVisMedMinInPAgeTrhd_str */   (uint8)   8 ,

 /* k_FCW_VehMinInPAgeTrhd_str */   (uint8)   12 ,

 /* k_FCW_MinTTCReq_str */   (float32)  0.2F,

 /* k_FCW_MinRangeReq_str */   (float32)  3.3F,

 /* k_FCW_AccActive_RedFac_str */   (float32)  0.8F,

 /* k_FCWSnvty_map_z_str[ 7 ]*/   { (float32)3.0F, (float32)3.0F, (float32)1.0F, (float32)6.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_FCWSnvty_map_x_str[ 7 ]*/   { (float32)0.0F, (float32)1.0F, (float32)2.0F, (float32)3.0F, (float32)4.0F, (float32)5.0F, (float32)6.0F},

 /* k_FCW_TTC_ACC_RedFac_str[ 9 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_FCW_DisHldTime_Latent_str */   (uint16)   0 ,

 /* k_FCW_DisHldTime_PreWarn_str */   (uint16)   0 ,

 /* k_FCW_Bypass_Spdlimit_str */   (boolean)   0 ,

 /* k_FCW_reserve28_str */   (uint8)   0 ,

 /* k_FCW_reserve29_str */   (uint16)   0 ,

 /* k_FCW_VehSpdBrkPoinys_str[ 8 ]*/   { (float32)9.72F, (float32)13.5F, (float32)13.89F, (float32)19.44F, (float32)25.0F, (float32)30.56F, (float32)33.33F, (float32)38.89F},

 /* k_FCW_CmftForLv1DWWarnDist_str[ 8 ]*/   { (float32)0.0F, (float32)0.0F, (float32)9.72F, (float32)13.6F, (float32)17.5F, (float32)21.3F, (float32)23.3F, (float32)27.2F},

 /* k_FCW_CmftForLv2DWWarnDist_str[ 8 ]*/   { (float32)0.0F, (float32)0.0F, (float32)9.72F, (float32)13.6F, (float32)17.5F, (float32)21.3F, (float32)23.3F, (float32)27.2F},

 /* k_FCW_CmftForLv3DWWarnDist_str[ 8 ]*/   { (float32)0.0F, (float32)0.0F, (float32)9.72F, (float32)13.6F, (float32)17.5F, (float32)21.3F, (float32)23.3F, (float32)27.2F},

 /* k_FCW_DW_MainLoopTime_str */   (float32)  0.05F,

 /* k_FCW_DW_Enable_str */   (boolean)   1 ,

 /* k_FCW_DW_UseDistLmt_str */   (boolean)   0 ,

 /* k_FCW_reserve30_str */   (uint16)   0 ,

 /* k_FCW_DW_DisResThresh_str */   (float32)  100.0F,

 /* k_FCW_DW_DisResLow_str */   (float32)  10.0F,

 /* k_FCW_DW_DisResHigh_str */   (float32)  5.0F,

 /* k_FCW_DW_DisHysResLow_str */   (float32)  1.5F,

 /* k_FCW_DW_DisHysResHigh_str */   (float32)  1.0F,

 /* k_FCW_DW_TimeResThresh_str */   (float32)  5.0F,

 /* k_FCW_DW_TimeResLow_str */   (float32)  0.5F,

 /* k_FCW_DW_TimeResHigh_str */   (float32)  0.1F,

 /* k_FCW_DW_TimeHysResLow_str */   (float32)  0.1F,

 /* k_FCW_DW_TimeHysResHigh_str */   (float32)  0.1F,

 /* k_FCW_DW_MinActivationSpeed_str */   (float32)  5.6F,

 /* k_FCW_DW_LowerCutoffSpeed_str */   (float32)  4.1F,

 /* k_FCW_DW_MaxActivationSpeed_str */   (float32)  70.0F,

 /* k_FCW_DW_UpperCutoffSpeed_str */   (float32)  72.0F,

 /* k_FCW_DW_IgnoreVehAhdInd_str */   (boolean)   1 ,

 /* k_FCW_IgnoreFCWTmChkAWB_str */   (boolean)   0 ,

 /* k_FCW_reserve32_str */   (uint16)   0 ,

 /* k_FCW_DW_MinLVSpeed_str */   (float32)  0.0F,

 /* k_FCW_DW_LVCutoffSpeed_str */   (float32)  0.0F,

 /* k_FCW_DW_MaxRange_str */   (float32)  120.0F,

 /* k_FCW_DW_MaxTime_str */   (float32)  20.0F,

 /* k_FCW_DW_TimeTooLow_str */   (float32)  0.5F,

 /* k_FCW_DW_TimeTooHigh_str */   (float32)  3.0F,

 /* k_FCW_DW_DisTooLow_str */   (float32)  5.0F,

 /* k_FCW_DW_DisTooHigh_str */   (float32)  100.0F,

 /* k_FCW_DW_FLWTimeMax_str */   (float32)  3.0F,

 /* k_FCW_DW_FLWTimeMin_str */   (float32)  0.5F,

 /* k_FCW_DW_FLWDistMax_str */   (float32)  100.0F,

 /* k_FCW_DW_FLWDistMin_str */   (float32)  5.0F,

 /* k_FCW_DW_DisplayHoldTime_str */   (uint16)   100 ,

 /* k_FCW_DW_CPIVChangeTime_str */   (uint16)   400 ,

 /* k_FCW_DW_ALGO_LOOP_INT_str */   (uint16)   50 ,

 /* k_FCW_PreWarningMask_str */   (uint16)   65535 ,

 /* k_FCW_reserve34_str */   (uint8)   0 ,

 /* k_FCW_Customer_str */   (uint8)   0 ,

 /* k_FCW_Platform_str */   (uint8)   0 ,

 /* k_FCW_VehVariant_str */   (uint8)   0 ,

 /* k_FCW_ProductionModelYear_str */   (uint8)   0 ,

 /* k_FCW_SensorConfig_str */   (uint8)   0 ,

 /* k_Cal_FCW_major_version_str */   (uint8)   5 ,

 /* k_Cal_FCW_minor_version_str */   (uint8)   0 ,

};
#define FCW_STOP_SEC_CAL_UNSPECIFIED
/*
*| fcw_cal.FCW_Cal_DF_V {
*|  :is_calconst;
*|  .k_FCW_Enable_str {
*|  :description = "Vehicle Configuration data - FCW is enabled when this is TRUE.";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_FusHistConfLevel_str {
*|  :description = "Fusion highest confidence level";
*|  :units = "enum";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_FCW_FusHiConfLevel_str {
*|  :description = "Fusion high confidence level";
*|  :units = "enum";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_FCW_FusMedConfLevel_str {
*|  :description = "Fusion medium confidence level";
*|  :units = "enum";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_FCW_FusHiMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion high confidence le\
*|  vel crossing target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_FusHiMinInPAgeTrhdLg_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion high confidence le\
*|  vel longitudinal target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_FusMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion medium confidence \
*|  level crossing target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_FusMedMinInPAgeTrhdLg_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion medium confidence \
*|  level longitudinal target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_VisMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for vision on medium confiden\
*|  ce level crossing target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_VisMedMinInPAgeTrhdLg_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for vision medium confidence \
*|  level longitudinal target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_MinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for low confidence level cros\
*|  sing target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_MinInPAgeTrhdLg_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for lowh confidence level lon\
*|  gitudinal target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_VehSHiEstMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion highest confidence\
*|   level CIPS target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_VehSHiMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion high confidence le\
*|  vel CIPS target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_VehSMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion medium confidence \
*|  level CIPS target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_VehSMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion low confidence lev\
*|  el CIPS target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_VehMHiEstMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion highest confidence\
*|   level CIPV target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_VehMHiMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion high confidence le\
*|  vel CIPV target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_VehMMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion medium confidence \
*|  level CIPV target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_VehMMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion low confidence lev\
*|  el CIPV target";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_LatWarnHostAccThres_str {
*|  :description = "Host accel thres for lat warn.";
*|  :units = "m/s";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_FCW_MinSpd_str {
*|  :description = "Minimum speed for FCW alert to be triggered";
*|  :units = "m/s";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_MaxRactnTmSpd_str {
*|  :description = "Host speed at which reaction time saturates to maximum values";
*|  :units = "m/s";
*|  :type = caltype.single_0p0078125_100_CT;
*|  }
*|  .k_FCW_MinSpdACC_str {
*|  :description = "Minimum speed of FCW alert to be triggered when ACC engage";
*|  :units = "m/s";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_MaxSpdStat_str {
*|  :description = "Maximum host speed allowed for stationary alert to be triggered";
*|  :units = "m/s";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_FCW_ObjPredPermitHeadAbs_str {
*|  :description = "";
*|  :units = "deg";
*|  :type = caltype.single_0_180_CT;
*|  }
*|  .k_FCW_ObjCrossPermitHeadMin_str {
*|  :description = "";
*|  :units = "deg";
*|  :type = caltype.single_0_180_CT;
*|  }
*|  .k_FCW_ObjCrossPermitHeadMax_str {
*|  :description = "";
*|  :units = "deg";
*|  :type = caltype.single_0_180_CT;
*|  }
*|  .k_FCW_TmHdwyBuffer_z_str {
*|  :description = "2D table indicates Time headway range buffer (speed dependent) added to FCW warning-:::FCWHdwyStg_V:::";
*|  :units = "s";
*|  :type = caltype.array_7X2_k_FCW_TmHdwyBuffer_z_single_0_5_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_MovMaxTTC_z_str {
*|  :description = "2D table indicates Maximum TTC for moveable alert-:::FCWHdwyStg_V:::";
*|  :units = "s";
*|  :type = caltype.array_7X2_k_FCW_MovMaxTTC_z_single_0_10_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_RangeBuffer_z_str {
*|  :description = "2D table indicates buffer (not speed dependent) added to imminent warning range-:::FCWHdwyStg_V:::";
*|  :units = "m";
*|  :type = caltype.array_7X2_k_FCW_RangeBuffer_z_single_0_100_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_LeadAccelAdj_z_str {
*|  :description = "2D table indicates Adjustment to the detected lead vehicle deceleration when deceleration is detecte\
*|  d-:::FCWHdwyStg_V:::";
*|  :units = "m/s^2";
*|  :type = caltype.array_7X2_k_FCW_LeadAccelAdj_z_single_m20_20_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_DeaccForReleAccPedl_str {
*|  :description = "";
*|  :units = "m/s^2";
*|  :type = caltype.single_m20_20_CT;
*|  }
*|  .k_FCW_ReactionTime_z_str {
*|  :description = "2D table indicates Assumed driver reaction time (rises linearly from zero to this at low speed while\
*|   ACC braking )-:::FCWHdwyStg_V:::";
*|  :units = "s";
*|  :type = caltype.array_7X2_k_FCW_ReactionTime_z_single_0_5_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_MaxRngStat_z_str {
*|  :description = "2D table indicates Maximum warning distance for stationary targets-:::FCWHdwyStg_V:::";
*|  :units = "m";
*|  :type = caltype.array_7X2_k_FCW_MaxRngStat_z_single_0_200_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_VRUMaxRng_z_str {
*|  :description = "2D table indicates Maximum warning distance for pedestrians-:::FCWHdwyStg_V:::";
*|  :units = "m";
*|  :type = caltype.array_7X2_k_FCW_VRUMaxRng_z_single_0_200_CT;
*|  :annotation = caltype.anns_k_FCW_PedLockIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_StatRatnTmAdj_z_str {
*|  :description = "1D table indicates adjustment to assumed driver reaction time for stationary targets-:::FCWHdwyStg_V:::";
*|  :units = "s";
*|  :type = caltype.array_7X2_k_FCW_StatRatnTmAdj_z_single_m2_2_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_ResponseAccel_z_str {
*|  :description = "2D table indicates Assumed host vehicle deceleration once the driver responds (after Response Time)-:::FCWHdwyStg_V:::";
*|  :units = "m/s^2";
*|  :type = caltype.array_2_k_FCW_ResponseAccel_z_single_m20_m0p0078125_CT;
*|  :annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_CautnAllowTailgate_z_str {
*|  :description = "Bit to allow tailgate part of cautionary alert";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_FCW_MinTmBtAlerts_ms_str {
*|  :description = "Minimal time gap required between two consecutive FCW";
*|  :units = "msec";
*|  :type = caltype.uint16_0_30000_CT;
*|  }
*|  .k_FCW_reserve1_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_StatMaxTTC_z_str {
*|  :description = "2D table indicates Maximum TTC for stationary alert-:::FCWHdwyStg_V:::";
*|  :units = "s";
*|  :type = caltype.array_7X2_k_FCW_StatMaxTTC_z_single_0_20_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_VRUMaxTTC_z_str {
*|  :description = "2D table indicates Maximum TTC for pedestrain alert";
*|  :units = "s";
*|  :type = caltype.single_0_20_CT;
*|  }
*|  .k_FCW_MaxStatYaw_str {
*|  :description = "Maximum Yaw Rate allowed for imminent alert availability";
*|  :units = "deg/s";
*|  :type = caltype.single_0_20_CT;
*|  }
*|  .k_FCW_MaxSpdCautnOn_str {
*|  :description = "Minimal host speed for cautionary alert to be firstly actived";
*|  :units = "m/s";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_MaxSpdCautnOff_str {
*|  :description = "Speed that cautionary alert is activated after cautionary alert is available (hysteresis)";
*|  :units = "m/s";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_CautnCoast_ms_str {
*|  :description = "Coasting time (Temporal hysteresis or alert hold) to bridge cautionary alerts after conditions expir\
*|  e";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_AWBAtvWarnThresTm_str {
*|  :description = "The time  awb active for fcw.";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_MinAlertReqAccel_str {
*|  :description = "Minimum Lead vehicle acceleration required to trigger alert if range rate is not closing";
*|  :units = "m/s/s";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_FCW_MinAlertReqRngRt_str {
*|  :description = "Minimum Range Rate required to trigger alert if Lead vehicle is not decelerating";
*|  :units = "m/s";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_FCW_RTWhileSuppressed_str {
*|  :description = "Reaction Time value used while alerts are suppressed by driver activity for purposes of exponential \
*|  return";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_MaxRTWhileBraking_str {
*|  :description = "Maximum reaction time value while host vehicle is braking";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_RTRecoverTC_ms_str {
*|  :description = "Exponential filter time constant for gradual return to nominal reaction time after suppression";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_reserve3_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_MaxDecelRate_str {
*|  :description = "Maximum deceleration rate for still allowing FCW alerts";
*|  :units = "m/s/s";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_FCW_MaxStrRate_str {
*|  :description = "Maximum (absolute) steering angle rate allowed before driver activity suppresses alerts";
*|  :units = "deg/s";
*|  :type = caltype.single_0_500_CT;
*|  }
*|  .k_FCW_MinAccelPdl_str {
*|  :description = "Minimum Accelerator pedal position rate of change allowed before driver activity suppresses alerts";
*|  :units = "none";
*|  :type = caltype.single_m500_0_CT;
*|  }
*|  .k_FCW_MaxAccelPdl_str {
*|  :description = "Maximum Accelerator pedal position rate of change allowed before driver activity suppresses alerts";
*|  :units = "none";
*|  :type = caltype.single_0_500_CT;
*|  }
*|  .k_FCW_MinBrkPdl_str {
*|  :description = "Minimum Brake pedal position rate of change allowed before driver activity suppresses alerts";
*|  :units = "none";
*|  :type = caltype.single_m500_0_CT;
*|  }
*|  .k_FCW_MaxBrkPdl_str {
*|  :description = "Maximum Brake pedal position rate of change allowed before driver activity suppresses alerts";
*|  :units = "none";
*|  :type = caltype.single_0_5000_CT;
*|  }
*|  .k_FCW_HdTmSteer_ms_str {
*|  :description = "Suppression hold time for which steering rate causes alert suppression";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_HdTmAccelUp_ms_str {
*|  :description = "Suppression hold time for which downward accelerator pedal rate causes alert suppression";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_HdTmAccelDown_ms_str {
*|  :description = "Suppression hold time for which upward accelerator pedal rate causes alert suppression";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_HdTmBrkUp_ms_str {
*|  :description = "Suppression hold time for which downward brake pedal rate causes alert suppression";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_HdTmBrkDown_ms_str {
*|  :description = "Suppression hold time for which upward brake pedal rate causes alert suppression";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_AlertHdTm_ms_str {
*|  :description = "Time which FCW impending alert holds true once activated";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_BrakePropnBuffer_str {
*|  :description = "Proportion multiplier for range buffer when driver is already braking";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_FCW_HostSpdFilterTm_ms_str {
*|  :description = "Time constant in msec applied to Vehicle Speed Compensated before calculation of HostAccel";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_RawCautnFilterTm_ms_str {
*|  :description = "Time constant in msec applied inside Caution_Timer_Function";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_HdTmAccel_ms_str {
*|  :description = "Suppression hold time for which absolute host acceleration causes alert suppression";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_reserve4_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_GapSetgIn_x_str {
*|  :description = "Input =  k_FCAGapSetting";
*|  :units = "enum";
*|  :type = caltype.single_0_8_CT;
*|  }
*|  .k_FCW_ACCOKIn_y_str {
*|  :description = "Input =  ACCOK-:::FCWHdwyStg_V:::";
*|  :units = "enum";
*|  :type = caltype.array_2_k_FCW_ACCOKIn_y_single_0_1_CT;
*|  :annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_CautnAllowClosing_z_str {
*|  :description = "Bit to allow closing part of cautionary alert-:::FCWHdwyStg_V:::";
*|  :units = "none";
*|  :type = caltype.array_7_k_FCW_CautnAllowClosing_z_single_0_1_CT;
*|  :annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_CautnTHW_z_str {
*|  :description = "Time headway for cautionary alert across gap settings-:::FCWHdwyStg_V:::";
*|  :units = "s";
*|  :type = caltype.array_7_k_FCW_CautnTHW_z_single_0_10_CT;
*|  :annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_CautnTTC_z_str {
*|  :description = "Time before FCW alert that Cautionary alert will be issued across gap settings";
*|  :units = "s";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_MaxHostAccel_str {
*|  :description = "Maximum Host Acceleration allowed before driver activity suppresses alerts";
*|  :units = "m/s/s";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_CautnTTCHys_str {
*|  :description = "Time before Impending alert that Cautionary alert will be issued added on when cationary alert is is\
*|  sued (hysteresis)";
*|  :units = "s";
*|  :type = caltype.single_0_20_CT;
*|  }
*|  .k_FCW_AllowBrkAlerts_str {
*|  :description = "Bit to allow alerts while brake pedal depressed";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_AccelPdlSuppr_str {
*|  :description = "Bit to allow alert suppression based on accelerator pedal";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_HostAccelSuppr_str {
*|  :description = "Bit to allow alert suppression based on host acceleration";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_ChmSuppressUse_str {
*|  :description = "Cal used to determine how Chime Suppress is used (0-no chime suppress, 1-chime suppresses complete a\
*|  lert, 2-chime suppress allowed)";
*|  :units = "none";
*|  :type = caltype.uint8_0_2_CT;
*|  }
*|  .k_FCW_AllowTmngAdjACCBrk_str {
*|  :description = "Cal used to determine whether FCW behavior changes (0-not, 1-when ACC engaged, 2-only when ACC braki\
*|  ng)";
*|  :units = "none";
*|  :type = caltype.uint8_0_2_CT;
*|  }
*|  .k_FCW_CautnforACCEngvsBrk_str {
*|  :description = "Cal used to determine whether Caution is allowed during ACC (0-not allowed during ACC engaged, 1-no \
*|  allowed during ACC braking, 2-not changed by ACC)";
*|  :units = "none";
*|  :type = caltype.uint8_0_2_CT;
*|  }
*|  .k_FCW_AllowedDuringCrusCtrl_str {
*|  :description = "Cal used in bitwise and to allow different alerts while ACC engaged (bit0(1)Moving,bit1(2)Stationary\
*|  ,bit2(4)AEB/External-- 7 allows all)";
*|  :units = "none";
*|  :type = caltype.uint8_0_64_CT;
*|  }
*|  .k_FCW_AllowedTypes_str {
*|  :description = "Cal used in bitwise and to allow different alerts while ACC not engaged (bit0(1)Moving,bit1(2)Statio\
*|  nary,bit2(4)AEB/External-- 7 allows all)";
*|  :units = "none";
*|  :type = caltype.uint8_0_64_CT;
*|  }
*|  .k_FCW_CautnPersist_ms_str {
*|  :description = "Delay before headway alert is issued after the conditions are met";
*|  :units = "none";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_HdTmDecel_ms_str {
*|  :description = "Suppression hold time for which absolute host deceleration causes alert suppression";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_HostDecelSuppr_str {
*|  :description = "Bit to allow alert suppression based on host deceleration";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_reserve5_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_1_CT;
*|  }
*|  .k_FCW_reserve6_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_MinHostAccel_str {
*|  :description = "Maximum Host Deceleration allowed before driver activity suppresses alerts";
*|  :units = "m/s^2";
*|  :type = caltype.single_m20_0_CT;
*|  }
*|  .k_FCW_CautnLatHys_str {
*|  :description = "Latreal position hysteris limit for Cautionary Alerts";
*|  :units = "m";
*|  :type = caltype.single_0_25_CT;
*|  }
*|  .k_FCW_CautnLat_str {
*|  :description = "Lateral offset limit for Cautionary Alerts";
*|  :units = "m";
*|  :type = caltype.single_0_25_CT;
*|  }
*|  .k_FCW_MaxLat_str {
*|  :description = "Maximum target lateral position limit, out of which FCW is not allowed";
*|  :units = "m";
*|  :type = caltype.single_0_25_CT;
*|  }
*|  .k_FCW_VRUMaxLat_str {
*|  :description = "Maximum target lateral Limit for pedestrain Targets,out of which FCW is not allowed";
*|  :units = "m";
*|  :type = caltype.single_0_25_CT;
*|  }
*|  .k_FCW_VehSReqConf_str {
*|  :description = "Match Confidence level for FCW pedestrian Reaction";
*|  :units = "";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_FCW_reserve7_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_1_CT;
*|  }
*|  .k_FCW_reserve8_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_VRUSensitize_str {
*|  :description = "Pedestrain Warn range Gain";
*|  :units = "";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_HostSpeed_x_str {
*|  :description = "Speed Taper Breakpoints-:::Vehicle_Speed_Compensated_V:::";
*|  :units = "m/s";
*|  :type = caltype.array_8_k_FCW_HostSpeed_x_single_0_100_CT;
*|  :annotation = caltype.anns_k_FCW_HostSpeed_x;
*|  }
*|  .k_FCW_MinTaperProp_z_str {
*|  :description = "Speed Taper Table";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_VehMReqConf_str {
*|  :description = "Match Cinfidence level for FCW pedestrian Reaction";
*|  :units = "";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_FCW_VehMUseLatRt_str {
*|  :description = "Use Target Lat Rate";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_reserve9_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_FullXolc_str {
*|  :description = "XOLC Deadband";
*|  :units = "m";
*|  :type = caltype.single_0_25_CT;
*|  }
*|  .k_FCW_NegXolc_str {
*|  :description = "XOLC Deadband";
*|  :units = "m";
*|  :type = caltype.single_0_25_CT;
*|  }
*|  .k_FCW_StrTurnTrhd_str {
*|  :description = "Turn Detection Threshold";
*|  :units = "deg/s";
*|  :type = caltype.single_0_500_CT;
*|  }
*|  .k_FCW_StrTrhd_str {
*|  :description = "Steer Rate Threshold";
*|  :units = "deg/s";
*|  :type = caltype.single_0_500_CT;
*|  }
*|  .k_FCW_XolcTrhd_str {
*|  :description = "Xolc Threshold";
*|  :units = "m";
*|  :type = caltype.single_0_25_CT;
*|  }
*|  .k_FCW_UseXolc_str {
*|  :description = "Use XOLC or XOHP";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_AccelPdlPosSuppr_str {
*|  :description = "Use Accel pedal position suppresion";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_BrkPdlSuppr_str {
*|  :description = "Use Brake pedal  suppresion";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_reserve10_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_1_CT;
*|  }
*|  .k_FCW_MaxAccelPdlPos_str {
*|  :description = "Accel pedal FCW suppresion threshold";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_MaxAccelPdlPosVec_str {
*|  :description = "Accel pedal FCW suppresion threshold Max";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_MinAccelPdlPosVec_str {
*|  :description = "Accel pedal FCW suppresion threshold Min";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_HdTmAccelPos_ms_str {
*|  :description = "Accel Pedal postion Halotime";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_BrkPdlMoniTm_ms_str {
*|  :description = "Brake Pedal monitor time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_HdTmBrkPdl_ms_str {
*|  :description = "Brake Pedal Halotime";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_reserve11_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_HostSpdRTAdj_z_str {
*|  :description = "Host speed based reaction Time Adjust Table";
*|  :units = "sec";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_FCW_HostSpdRTAdj_x_str {
*|  :description = "Host speed based reaction Time Adjust Break Points";
*|  :units = "m/s";
*|  :type = caltype.array_8_k_FCW_HostSpdRTAdj_x_single_0_100_CT;
*|  :annotation = caltype.anns_k_FCW_ACCHostSpeedRTAdj_x;
*|  }
*|  .k_FCW_ACCHostSpdRTAdj_z_str {
*|  :description = "Host speed based reaction Time Adjust Table";
*|  :units = "sec";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_FCW_ACCHostSpdRTAdj_x_str {
*|  :description = "Host speed based reaction Time Adjust Break Points";
*|  :units = "m/s";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_ROCTrhdVehS_str {
*|  :description = "Minimum ROC Threshold for  Stationary Targets";
*|  :units = "m";
*|  :type = caltype.uint16_0_8191_CT;
*|  }
*|  .k_FCW_ROCTrhdVehM_str {
*|  :description = "Minimum ROC Threshold for  Moveable Targets";
*|  :units = "m";
*|  :type = caltype.uint16_0_8191_CT;
*|  }
*|  .k_FCW_VisnFCWCnfgEnbl_str {
*|  :description = "Enable FCW Imminent alert trigger from ME";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_UseOnlyVisnFCW_str {
*|  :description = "Master Config to use only ME solution for the the trigger of FCW Imminent Alert";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_Visn_IgnChmSupress_str {
*|  :description = "Ignore Supresstion of FCW imminent alert for internally calculated supresstion conditions when ME Wa\
*|  rning tigger is used";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_reserve12_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_1_CT;
*|  }
*|  .k_FCW_VisnTTCTrhdSpd_x_str {
*|  :description = "FCW timing host vehicle speed break points-:::FCWHdwyStg_V,Vehicle_Speed_Compensated_V:::";
*|  :units = "m/s";
*|  :type = caltype.array_1X8_k_FCW_VisnTTCTrhdSpd_x_single_0_100_CT;
*|  :annotation = caltype.anns_k_FCW_METTCThres_speed_bp;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_VisnTTCTrhd_z_str {
*|  :description = "FCW Mobileye TTC based timing threshold-:::FCWHdwyStg_V,Vehicle_Speed_Compensated_V:::";
*|  :units = "s";
*|  :type = caltype.array_7X8_k_FCW_VisnTTCTrhd_z_single_0_10_CT;
*|  :annotation = caltype.anns_k_FCW_METTCThres_speed_bp;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_VisnVRUTTCTrhd_z_str {
*|  :description = "FCW Mobileye TTC based timing threshold for VRU";
*|  :units = "s";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_HostAccelMoniTm_ms_str {
*|  :description = "minimum accelerator pedal position press duration allowed before driver activity suppresses alerts";
*|  :units = "ms";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_reserve13_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_Visn_SensorLatency_mps_str {
*|  :description = "FCW sensor latency host speed break point-:::Vehicle_Speed_Compensated_V:::";
*|  :units = "m/s";
*|  :type = caltype.array_8_k_FCW_Visn_SensorLatency_mps_single_0_100_CT;
*|  :annotation = caltype.anns_k_MEFCW_Sensor_Latency_Mps;
*|  }
*|  .k_FCW_Visn_SensorLatency_sec_str {
*|  :description = "TTC threshold offset based on sensor latency";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_Visn_HostSpd_x_str {
*|  :description = "FCW TTC offset host speed break point";
*|  :units = "m/s";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_Visn_RelSpd_x_str {
*|  :description = "FCW TTC offset relative speed break point-:::Vehicle_Speed_Compensated_V:::";
*|  :units = "m/s";
*|  :type = caltype.array_1X8_k_FCW_Visn_RelSpd_x_single_m100_100_CT;
*|  :annotation = caltype.anns_k_FCW_MEHost_speed_bp;
*|  :elements:annotation = caltype.anns_k_FCW_MERel_speed_bp;
*|  }
*|  .k_FCW_Visn_Rel_TTCTrhd_z_str {
*|  :description = "FCW TTC offset relative speed versus hosts speed table";
*|  :units = "s";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_CautnMinRngRt_str {
*|  :description = "minimum range Rate for issuing cautionary alert";
*|  :units = "m/s";
*|  :type = caltype.single_m100_100_CT;
*|  }
*|  .k_FCW_BrkPdlRateSuppr_str {
*|  :description = "enable FCW chime suppression  based on brake pedal rate";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_VisnVRU_WarnEnbl_str {
*|  :description = "Enable fusion FCW to pedestrians and cyclist";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_VisnVeh_NoHostCntrl_str {
*|  :description = "Disable Host side claibration of vehcile Imminent alert";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_VisnTTCPlausEnbl_str {
*|  :description = "Enable ME early alarm filtered algorithm";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_VisnTTCPlausMinSpeed_str {
*|  :description = "Minimal speed above which filtered algorithm will apply";
*|  :units = "m/s";
*|  :type = caltype.uint8_0_100_CT;
*|  }
*|  .k_FCW_VisnMinPlausTTC_str {
*|  :description = "Minimal TTC above which filtered algorithm will not apply";
*|  :units = "s";
*|  :type = caltype.uint8_0_7_CT;
*|  }
*|  .k_FCW_reserve14_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_VisnPlausTTC_z_str {
*|  :description = "TTC deviation need to be smaller than threshold value before FCW is allowed";
*|  :units = "s";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_VisnMinPlausAccel_x_str {
*|  :description = "TTC deviation range acceleration break points";
*|  :units = "m/s/s";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_FCW_VisnMesTTCEnbl_str {
*|  :description = "Enable TTC calculation using ME reported inputs";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_VRUReqConf_str {
*|  :description = "Enable the confidence check for VRU FCW";
*|  :units = "none";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_FCW_reserve15_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_VRULockIn_y_str {
*|  :description = "Enable reaction time adjustment for VRU";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_FCW_AcuteWarnMaxTm_ms_str {
*|  :description = "";
*|  :units = "msec";
*|  :type = caltype.uint16_0_50000_CT;
*|  }
*|  .k_FCW_reserve16_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_VisnAcuTTCTrhd_z_str {
*|  :description = "2D TTC threshold values table against different host speed and different headway setting for vision \
*|  AWB feature of vehicle or motorcycle";
*|  :units = "s";
*|  :type = caltype.array_7X8_k_FCW_VisnAcuTTCTrhd_z_single_0_5_CT;
*|  :annotation = caltype.anns_k_FCW_MEAcuTTCThres_speed_bp;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_VisnVRUAcuTTCTrhd_z_str {
*|  :description = "2D TTC threshold values table against different host speed and different headway setting for vision \
*|  AWB feature of vulnerable road user";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_VisnAcuTTCTrhdSpd_x_str {
*|  :description = "Host speed break points for vision AWB feature";
*|  :units = "mps";
*|  :type = caltype.single_0_75_CT;
*|  }
*|  .k_FCW_AcuteAlertHdTm_ms_str {
*|  :description = "";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_AcuteHdTm_ms_str {
*|  :description = "";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_AcutWnBrakeConfig_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_reserve17_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_1_CT;
*|  }
*|  .k_FCW_reserve18_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_AllowActuWnDuringACC_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_1024_CT;
*|  }
*|  .k_FCW_AllowActuWnTypes_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_1024_CT;
*|  }
*|  .k_FCW_BrkSuppressUse_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_AcutWarnPFSuppr_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_reserve19_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_MaxSpdAcutWarnOff_str {
*|  :description = "";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_MaxSpdAcutWarnOn_str {
*|  :description = "";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_AcutForACCEngvsBrk_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint8_0_5_CT;
*|  }
*|  .k_FCW_reserve20_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_1_CT;
*|  }
*|  .k_FCW_reserve21_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_HostSpdAcutRTGain_z_str {
*|  :description = "FCW_cal.k_FCW_HostSpdAcutRTGain_z";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_FCW_HostSpdAcutRTGain_x_str {
*|  :description = "FCW_cal.k_FCW_HostSpdAcutRTGain_x";
*|  :units = "none";
*|  :type = caltype.array_1X8_k_FCW_HostSpdAcutRTGain_x_single_0_100_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_VRUMaxAcutTTC_z_str {
*|  :description = "Maximum allowed TTC threshold value table of fusion AWB to vulnerable road user";
*|  :units = "s";
*|  :type = caltype.array_7X2_k_FCW_VRUMaxAcutTTC_z_single_0_5_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_StatMaxAcutTTC_z_str {
*|  :description = "Maximum allowed TTC threshold value table of fusion AWB to stationary target";
*|  :units = "s";
*|  :type = caltype.array_7X2_k_FCW_StatMaxAcutTTC_z_single_0_5_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_VRUMaxAcutRng_z_str {
*|  :description = "FCW_cal.k_FCW_VRUMaxAcutRng_z";
*|  :units = "m";
*|  :type = caltype.array_7X2_k_FCW_VRUMaxAcutRng_z_single_0_200_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_MaxAcutRngStat_z_str {
*|  :description = "FCW_cal.k_FCW_MaxAcutRngStat_z";
*|  :units = "m";
*|  :type = caltype.array_7X2_k_FCW_MaxAcutRngStat_z_single_0_200_CT;
*|  :annotation = caltype.anns_k_FCW_ACCOKIn_y;
*|  :elements:annotation = caltype.anns_k_FCW_GapSetgIn_x;
*|  }
*|  .k_FCW_MovMaxAcutTTC_z_str {
*|  :description = "Maximum allowed TTC threshold value table of fusion AWB to moveable target";
*|  :units = "s";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_EnblWithCruiseOnOff_str {
*|  :description = "When set to TRUE, FCA feature is enabled with Cruise ON/OFF switch in ON state (without cruise engag\
*|  ed.)";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_UseUncompSpd_str {
*|  :description = "Use wheel speed based host speed as FCW input speed source";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_UseTTCFromFCWCalc_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_AllowExtWarnBrkOny_str {
*|  :description = "Allow extenal trigger FCW warning when this value set to true";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_EnblSdRdrDgrdChk_str {
*|  :description = "Will do SRR Mis Aligment check for moving target when this is true.";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_SdRdrDgrdMinConf_str {
*|  :description = "require at least fusion source";
*|  :units = "";
*|  :type = caltype.uint8_0_7_CT;
*|  }
*|  .k_FCW_AcutWarnEnbl_str {
*|  :description = "Enable AWB feature";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_UseLatRt_VehM_str {
*|  :description = "When it is set to true, Lateral rate will used to calculate the predicted lateral displacement";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_reserve22_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_1_CT;
*|  }
*|  .k_FCW_MaxSpd_LongBike_str {
*|  :description = "Maximum host speed allowed for LongBike alert to be triggered";
*|  :units = "m/s";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_FCW_MaxSpd_VRU_str {
*|  :description = "Maximum host speed allowed for VRU alert to be triggered";
*|  :units = "m/s";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_FCW_MaxSpd_CrossBike_str {
*|  :description = "Maximum host speed allowed for CrossBike alert to be triggered";
*|  :units = "m/s";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_FCW_UseVRUHold_str {
*|  :description = "When this is set to true, FCW will react to was previously high conf pedestrain target";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_MaxTTCRngAccelSrc_str {
*|  :description = "Select using LeadAccel or RangeAccel to calculate MaxTTCRange. When set 1, RangeAccel is selected.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_IgnoreOvrdForCautn_str {
*|  :description = "Ignore ACC override status when  cautionary alert";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_OvrdCycleforInhibCautn_str {
*|  :description = "Acc override counter for inhibit cautionary alert";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_GeneralSpd_x_str {
*|  :description = "Speed point to determine steering angle inhibit";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_HardTurnStrAngTrhd_str {
*|  :description = "Table value for steering angle inhibit";
*|  :units = "degrees";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_FCW_StrAngRateTrhd_str {
*|  :description = "Steering angle rate threshold to inhibit cautionary alert";
*|  :units = "degrees/s";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_FCW_StrInhibitCauEnblTm_str {
*|  :description = "Min enable time for big steer angle to inhibit cuationary alert";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_StrInhibitHoldTm_str {
*|  :description = "driver steer inhibti hold time for cautionar";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_CautnAllowRngRt_str {
*|  :description = "range rate allowed for cautionary alert";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_CautnEnablTm_str {
*|  :description = "Min enable time for cautionary when meet the warning condition";
*|  :units = "msec";
*|  :type = caltype.single_0_50000_CT;
*|  }
*|  .k_FCW_CautnQuitEnablTm_str {
*|  :description = "Min enable time for cautionary when doesn't meet the warning condition";
*|  :units = "msec";
*|  :type = caltype.uint16_0_50000_CT;
*|  }
*|  .k_FCW_reserve23_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_HWTmGainCautnOn_str {
*|  :description = "head time gain (not speed related) for cautionary alert (before alert is activated)";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_HWTmGainCautnOff_str {
*|  :description = "head time gain (not speed related) for cautionary alert for hysteresis (during alert activations)";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_VisnVehJAWarnSustain_ms_str {
*|  :description = "ME Veh JA Warning sustian time";
*|  :units = "m/s";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_FCW_reserve24_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_NoJAMinSpd_str {
*|  :description = "Minimum speed for NO JA FCW alert to be triggered";
*|  :units = "m/s";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_IgnoreVRUGOE_str {
*|  :description = "Set to one if ignore GOE check for VRU FCW";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_IgnoreVehGOE_str {
*|  :description = "Set to one if ignore GOE check for vehicle FCW";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_VRUFusHiConfLvl_str {
*|  :description = "Fusion high confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_VRUFusMedConfLvl_str {
*|  :description = "Fusion medium confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_VRUVisMedConfLvl_str {
*|  :description = "vision medium confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_RiderFusHiMinInPAgeTrhd_str {
*|  :description = "Minimal in path(future) age for rider object that has to wait before steady selection confirmed for \
*|  Fusion high confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_PedFusHiMinInPAgeTrhd_str {
*|  :description = "Minimal in path(future) age for pedestrain object that has to wait before steady selection confirmed\
*|   for Fusion high confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_RiderFusMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path(future) age for rider object that has to wait before steady selection confirmed for \
*|  Fusion medium confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_PedFusMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path(future) age for pedestrain object that has to wait before steady selection confirmed\
*|   for Fusion medium confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_RiderVisMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path(future) age for rider object that has to wait before steady selection confirmed for \
*|  Vision medium confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_PedVisMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path(future) age for pedestrain object that has to wait before steady selection confirmed\
*|   for Vision medium confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_RiderMinInPAgeTrhd_str {
*|  :description = "Minimal in path age for rider object that has to wait before steady selection confirmed for lowh con\
*|  fidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_PedMinInPAgeTrhd_str {
*|  :description = "Minimal in path age for pedestrain object that has to wait before steady selection confirmed for low\
*|  h confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_TimeGapSet_z_str {
*|  :description = "Time gap set output";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_UseTTC_SpdPoints_str {
*|  :description = "Speed point to determine FCW TTC threshold";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_BiLongWarnTTCTrhd_sec_str {
*|  :description = "FCW TTC threshold for stationary objects";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_BiStatWarnTTCTrhd_sec_str {
*|  :description = "FCW TTC threshold for stationary objects";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_BiCrossWarnTTCTrhd_sec_str {
*|  :description = "FCW TTC threshold for stationary objects";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_PedLongWarnTTCTrhd_sec_str {
*|  :description = "FCW TTC threshold for stationary objects";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_PedStatWarnTTCTrhd_sec_str {
*|  :description = "FCW TTC threshold for stationary objects";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_PedCrossWarnTTCTrhd_sec_str {
*|  :description = "FCW TTC threshold for stationary objects";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_MovWarnTTCTrhd_sec_str {
*|  :description = "FCW TTC threshold for stationary objects";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_StatWarnTTCTrhd_sec_str {
*|  :description = "FCW TTC threshold for moving objects";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_ScpTurnLong_Delay_str {
*|  :description = "When ScpTurnLong is active, FCW will delay.";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_ChimeSuppr_Delay_str {
*|  :description = "When chime suppress is active, FCW will delay.";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_BrkPdlPrsd_Delay_str {
*|  :description = "When brake pedal is pressed, FCW will delay.";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_AcuteAvail_Delay_str {
*|  :description = "When acute warn is available, FCW will delay.";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_MovUseRangeTriger_str {
*|  :description = "When set to TRUE, FCA will be trigger based on range for moving objects";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_StatUseRangeTriger_str {
*|  :description = "When set to TRUE, FCA will be trigger based on range for stationary objects";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_reserve26_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_TTCTriggerSvntySet_str {
*|  :description = "Lookup table for FCW TTC threshold.";
*|  :units = "none";
*|  :type = caltype.single_0_6_CT;
*|  }
*|  .k_FCW_TWDecelerateDetectAccel_str {
*|  :description = "TW deceleration detection acceleration threshold";
*|  :units = "m/s^2";
*|  :type = caltype.single_m20_20_CT;
*|  }
*|  .k_FCW_PedDecelerateDetectAccel_str {
*|  :description = "Ped deceleration detection acceleration threshold";
*|  :units = "m/s^2";
*|  :type = caltype.single_m20_20_CT;
*|  }
*|  .k_FCW_VRUDecelerateDetectHdTm_str {
*|  :description = "VRU deceleration detection hold time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_Mature_RE_thres_str {
*|  :description = "mature RE confidence threshold";
*|  :units = "";
*|  :type = caltype.uint8_0_7_CT;
*|  }
*|  .k_FCW_reserve27_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_1_CT;
*|  }
*|  .k_FCW_left_A0_RE_enter_thres_str {
*|  :description = "in road edge check left A0 enter thres";
*|  :units = "m";
*|  :type = caltype.single_m1_1_CT;
*|  }
*|  .k_FCW_left_A0_RE_exit_thres_str {
*|  :description = "in road edge check left A0 exit thres";
*|  :units = "m";
*|  :type = caltype.single_m1_1_CT;
*|  }
*|  .k_FCW_right_A0_RE_enter_thres_str {
*|  :description = "in road edge check right A0 enter thres";
*|  :units = "m";
*|  :type = caltype.single_m1_1_CT;
*|  }
*|  .k_FCW_right_A0_RE_exit_thres_str {
*|  :description = "in road edge check right A0 exit thres";
*|  :units = "m";
*|  :type = caltype.single_m1_1_CT;
*|  }
*|  .k_FCW_RE_EndRangeOffset_str {
*|  :description = "The offset for end distance of road edge.";
*|  :units = "m";
*|  :type = caltype.single_m5_5_CT;
*|  }
*|  .k_FCW_RE_StartRangeOffset_str {
*|  :description = "The offset for start distance of road edge.";
*|  :units = "m";
*|  :type = caltype.single_m5_5_CT;
*|  }
*|  .k_FCW_IgnoreVRU_RECheck_str {
*|  :description = "When it is set to true,Road edge will be not check.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_IgnoreVRU_XolcCheck_str {
*|  :description = "When it is set to true,Xolc will be not check.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_VRUReqConf_Fusion_str {
*|  :description = "Enable the confidence check for VRU FCW";
*|  :units = "none";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_FCW_IgnoreAEBTriggerSpd_str {
*|  :description = "When it is set to true,vehspd will be not check for AEB trigger FCW";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_Default_Time_Offset_str {
*|  :description = "";
*|  :units = "s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_FCW_HighSpdCrsLatVel_str {
*|  :description = "When VRU lat vel is beyond this threshold, it will use TWDecelerateDetectAccel.";
*|  :units = "mps";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_MaxSpdStatAcuWarnThresh_str {
*|  :description = "MaxSpd for stationary object AcuteWarning";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_MaxSpdAcutWarnThresh_str {
*|  :description = "MaxSpd for AcuteWarning";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_MaxSpdMov_str {
*|  :description = "Maximum host speed allowed for Mov vehicle alert to be triggered";
*|  :units = "m/s";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_FCW_MaxSpdCautnThresh_str {
*|  :description = "MaxSpd for latern warning";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_VehFusHiMinInPAgeTrhd_str {
*|  :description = "Minimal in path(future) age for vehicle object that has to wait before steady selection confirmed fo\
*|  r Fusion high confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_VehFusMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path(future) age for vehicle object that has to wait before steady selection confirmed fo\
*|  r Fusion medium confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_FCW_VehVisMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path(future) age for vehicle object that has to wait before steady selection confirmed fo\
*|  r Vision medium confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_255_CT;
*|  }
*|  .k_FCW_VehMinInPAgeTrhd_str {
*|  :description = "Minimal in path(future) age for vehicle object that has to wait before steady selection confirmed fo\
*|  r lowh confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_255_CT;
*|  }
*|  .k_FCW_MinTTCReq_str {
*|  :description = "Minimum TTC for FCW alert to be triggered";
*|  :units = "s";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_MinRangeReq_str {
*|  :description = "Minimum range for FCW alert to be triggered";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_AccActive_RedFac_str {
*|  :description = "When ACC is active, FCW TTC threshold to vehicle will reduce to the factor.";
*|  :units = "s";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_FCWSnvty_map_z_str {
*|  :description = "indicates the headway index selected for each FCW gap";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCWSnvty_map_x_str {
*|  :description = "Input = GapSwitchType for FCW";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_TTC_ACC_RedFac_str {
*|  :description = "When ACC is active, FCW TTC threshold to vehicle will reduce to the factor based on RangeRate.";
*|  :units = "s";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_FCW_DisHldTime_Latent_str {
*|  :description = "Display hold time for Signal FCWLatentWarn";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_DisHldTime_PreWarn_str {
*|  :description = "Display hold time for Signal FCWPreWarn";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_Bypass_Spdlimit_str {
*|  :description = "FCW output will be inhibited in Translate out if speed is smaller than a certain speed (GAC Req). Th\
*|  is calibrations is used to bypass this logic";
*|  :units = "dimensionless";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_reserve28_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_1_CT;
*|  }
*|  .k_FCW_reserve29_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_VehSpdBrkPoinys_str {
*|  :description = "FDI loop counter in milliseconds";
*|  :units = "none";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_CmftForLv1DWWarnDist_str {
*|  :description = "FDI loop counter in milliseconds";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_CmftForLv2DWWarnDist_str {
*|  :description = "FDI loop counter in milliseconds";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_CmftForLv3DWWarnDist_str {
*|  :description = "FDI loop counter in milliseconds";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_DW_MainLoopTime_str {
*|  :description = "FDI baseloop time is seconds";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_DW_Enable_str {
*|  :description = "EnableFDI algorithm";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_DW_UseDistLmt_str {
*|  :description = "Enable the Usage of Minimum Follow Distance";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_reserve30_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_DW_DisResThresh_str {
*|  :description = "Threshold Values for Distance Resolution change";
*|  :units = "m";
*|  :type = caltype.single_0_250_CT;
*|  }
*|  .k_FCW_DW_DisResLow_str {
*|  :description = "Resolution of Distance (for large values of distance)";
*|  :units = "m";
*|  :type = caltype.single_0p1_50_CT;
*|  }
*|  .k_FCW_DW_DisResHigh_str {
*|  :description = "Resolution of Distance (for small values of distance)";
*|  :units = "m";
*|  :type = caltype.single_0p1_50_CT;
*|  }
*|  .k_FCW_DW_DisHysResLow_str {
*|  :description = "Hysteresis for switching to the next quant for large values of distance";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_DW_DisHysResHigh_str {
*|  :description = "Hysteresis for switching to the next quant for small values of distance";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_DW_TimeResThresh_str {
*|  :description = "Threshold Values for Time Resolution change";
*|  :units = "sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_DW_TimeResLow_str {
*|  :description = "Low Resolution of Time";
*|  :units = "sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_DW_TimeResHigh_str {
*|  :description = "High Resolution of Time";
*|  :units = "sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_DW_TimeHysResLow_str {
*|  :description = "Hysteresis for switching to the next quant  (for high values of time)";
*|  :units = "sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_DW_TimeHysResHigh_str {
*|  :description = "Hysteresis for switching to the next quant for small values of distance";
*|  :units = "sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_DW_MinActivationSpeed_str {
*|  :description = "Minimum Host Speed (FDI not RTA above)";
*|  :units = "mps";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_DW_LowerCutoffSpeed_str {
*|  :description = "Minimum Host Speed (FDI not RTA above) when FDI is already active";
*|  :units = "mps";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_DW_MaxActivationSpeed_str {
*|  :description = "Maximum Host Speed (FDI not RTA above)";
*|  :units = "mps";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_DW_UpperCutoffSpeed_str {
*|  :description = "Maximum Host Speed (FDI not RTA above) when FDI is already active";
*|  :units = "mps";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_DW_IgnoreVehAhdInd_str {
*|  :description = "FDI will display values even when VAI is not true";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_IgnoreFCWTmChkAWB_str {
*|  :description = "If use fcw active time check for awb.";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_FCW_reserve32_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_1_CT;
*|  }
*|  .k_FCW_DW_MinLVSpeed_str {
*|  :description = "CIPVs will not be shown below this CIPV-speed";
*|  :units = "mps";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_DW_LVCutoffSpeed_str {
*|  :description = "CIPVs will not be shown below this CIPV-speed if FDI was already active";
*|  :units = "mps";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_FCW_DW_MaxRange_str {
*|  :description = "Upto this Range all the targets will be slected for FDI";
*|  :units = "m";
*|  :type = caltype.single_0_250_CT;
*|  }
*|  .k_FCW_DW_MaxTime_str {
*|  :description = "The Maximum headway time beyond which Targets will not be selected for FDI";
*|  :units = "sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_FCW_DW_TimeTooLow_str {
*|  :description = "Lower point of Time To Follow working range of FDI.";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_DW_TimeTooHigh_str {
*|  :description = "Upper point of Time To Follow working range of FDI.";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_DW_DisTooLow_str {
*|  :description = "Lower point of distance working range of FDI.";
*|  :units = "m";
*|  :type = caltype.single_0_250_CT;
*|  }
*|  .k_FCW_DW_DisTooHigh_str {
*|  :description = "Upper point of distance working range of FDI.";
*|  :units = "m";
*|  :type = caltype.single_0_250_CT;
*|  }
*|  .k_FCW_DW_FLWTimeMax_str {
*|  :description = "Upper limit of Follow Time";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_DW_FLWTimeMin_str {
*|  :description = "Lower limit of Follow Time";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_FCW_DW_FLWDistMax_str {
*|  :description = "Upper limit of Follow Distance";
*|  :units = "m";
*|  :type = caltype.single_0_250_CT;
*|  }
*|  .k_FCW_DW_FLWDistMin_str {
*|  :description = "Lower limit of Follow Distance";
*|  :units = "m";
*|  :type = caltype.single_0_250_CT;
*|  }
*|  .k_FCW_DW_DisplayHoldTime_str {
*|  :description = "FDI output display freeze time in milliseconds";
*|  :units = "sec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_DW_CPIVChangeTime_str {
*|  :description = "FDI output display freeze time in milliseconds during the change in CIPV";
*|  :units = "sec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_DW_ALGO_LOOP_INT_str {
*|  :description = "FDI loop counter in milliseconds";
*|  :units = "ms";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_FCW_PreWarningMask_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_FCW_reserve34_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_1_CT;
*|  }
*|  .k_FCW_Customer_str {
*|  :description = "customer definition.  Refer to Data Record sheet for detail";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_Platform_str {
*|  :description = "platform definition.";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_VehVariant_str {
*|  :description = "vehicle variant definition.";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_ProductionModelYear_str {
*|  :description = "model year definition. Refer to Data Record sheet for detail";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_FCW_SensorConfig_str {
*|  :description = "[enum] ";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_Cal_FCW_major_version_str {
*|  :description = "The major software version number of the feature function customer specific software or Data diction\
*|  ary version.";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_Cal_FCW_minor_version_str {
*|  :description = "The minor version number of the  feature function customer specific software or Data dictionary vers\
*|  ion..";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*| }
*/
