/****************************************************************************
 * Calibration file for LongSafe production code.
 * DD uses version 5 of the bas file.
 * File Name: D:\00ST\00Git\00_LongSafeCtrl\02_DataDictionary\LongSafe\LongSafe_cal.c
 * Created: 2025/7/8        20:05:55 
 * From Excel file: DataDictionary_LongSafe_DF.xls
 * Calibration Values for project         
 * Calibrations for full application.
 * Set Description:         Initial Value
 *****************************************************************************/

#include "rtwtypes.h"
#include "LongSafe_cal.h"


/*
 *  COMPONENT:  \AEB
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


#define LongSafe_START_SEC_CAL_UNSPECIFIED

LongSafe_cal_T LongSafe_Cal_DF_V __attribute__((section(".data#"))) = {

 /* k_AEB_FLBA_Enabled_str */   (boolean)   1 ,

 /* k_AEB_DBS_Enabled_str */   (boolean)   1 ,

 /* k_AEB_UseTestSceneFlag_str */   (boolean)   1 ,

 /* k_AEB_UseSpecialSceneFullBrk_str */   (boolean)   1 ,

 /* k_AEB_MinStop_Enabled_str */   (boolean)   1 ,

 /* k_AEB_AccelMinGasPedPosInhbt_str */   (float32)  25.0F,

 /* k_AEB_AccelTrhdMov_str */   (float32)  12.0F,

 /* k_AEB_AccelTrhdStat_str */   (float32)  12.0F,

 /* k_AEB_SpecScenHostSpdMax_str */   (float32)  18.0F,

 /* k_AEB_SpecScenFBHostHiSpd_str */   (float32)  15.2F,

 /* k_AEB_SpecScenFBHostMidSpd_str */   (float32)  12.5F,

 /* k_AEB_SpecScenFBHostLowSpd_str */   (float32)  9.72F,

 /* k_AEB_SpecScenFBThresInHiSpd_str */   (float32)  22.5F,

 /* k_AEB_SpecScenFBThresInMidSpd_str */   (float32)  17.0F,

 /* k_AEB_SpecScenFBThresInLowSpd_str */   (float32)  12.0F,

 /* k_AEB_SpecScenFBThresInElseSpd_str */   (float32)  7.0F,

 /* k_AEB_SpecScenHostSpdMin_str */   (float32)  4.17F,

 /* k_AEB_AlgInternalLpTm_ms_str */   (uint16)   20 ,

 /* k_AEB_BrkHdTmAfterTrig_ms_str */   (float32)  750.0F,

 /* k_AEB_Enable_str */   (boolean)   1 ,

 /* k_AEB_UseHoldTrigAfterStand_str */   (boolean)   1 ,

 /* k_AEB_AlgLpTm_sec_str */   (float32)  0.02F,

 /* k_AEB_BrkingRampToHiStep_mps_str */   (float32)  -3.92F,

 /* k_AEB_BrkingRampToLoStep_mps_str */   (float32)  -3.92F,

 /* k_AEB_BrakingRampToZeroStep_str */   (float32)  0.5F,

 /* k_AEB_DecelTrhdMov_str */   (float32)  -12.0F,

 /* k_AEB_DecelTrhdStat_str */   (float32)  -12.0F,

 /* k_AEB_DrvAppRefTmForAdj_str */   (float32)  0.5F,

 /* k_AEB_DrvOvrdBasePressure_str */   (float32)  15000.0F,

 /* k_AEB_RdrTimeStep_sec_str */   (float32)  0.02F,

 /* k_AEB_GasPedalMargin_str */   (uint8)   50 ,

 /* k_AEB_GasPedalPositionMax_str */   (uint8)   80 ,

 /* k_AEB_GasPedalOvrdTm_ms_str */   (uint16)   2000 ,

 /* k_AEB_GateClosingRngRtTrhd_str */   (float32)  -1.0F,

 /* k_AEB_ZeroSpdTrhd1_str */   (float32)  3.0F,

 /* k_AEB_ZeroSpdTrhd2_str */   (float32)  0.1F,

 /* k_AEB_GateMaxObjAngle_str */   (float32)  60.0F,

 /* k_AEB_GateMaxObjOffset_str */   (float32)  8.0F,

 /* k_AEB_GateMaxOpeningRngRt_str */   (float32)  1.0F,

 /* k_AEB_GateMaxRangeMov_str */   (float32)  75.0F,

 /* k_AEB_GateMaxRangeStat_str */   (float32)  60.0F,

 /* k_AEB_GateMaxTOIAngle_str */   (float32)  30.0F,

 /* k_AEB_GateMinROC_str */   (uint16)   35 ,

 /* k_AEB_UseInFunnelChk_str */   (boolean)   0 ,

 /* k_AEB_HiBrkHdTm_str */   (float32)  0.0F,

 /* k_AEB_HiBrkLdTmStat_sec_str[ 15 ]*/   { (float32)-0.1F, (float32)-0.15F, (float32)-0.15F, (float32)-0.11F, (float32)0.01F, (float32)0.14F, (float32)0.25F, (float32)0.37F, (float32)0.54F, (float32)0.53F, (float32)0.51F, (float32)0.51F, (float32)0.51F, (float32)0.51F, (float32)0.51F},

 /* k_AEB_AEBEgoSpdKneePoints_str[ 15 ]*/   { (float32)1.5F, (float32)2.75F, (float32)4.125F, (float32)5.5F, (float32)6.9375F, (float32)8.1875F, (float32)9.5F, (float32)11.0F, (float32)12.5F, (float32)13.875F, (float32)15.0F, (float32)16.6875F, (float32)18.0625F, (float32)19.4375F, (float32)22.25F},

 /* k_AEB_MEAEBEgoSpdKneePoints_str[ 8 ]*/   { (float32)1.5F, (float32)2.75F, (float32)4.125F, (float32)5.5F, (float32)6.9375F, (float32)8.1875F, (float32)9.5F, (float32)11.0F},

 /* k_AEB_HiBrkLdTmMov_sec_str[ 15 ]*/   { (float32)0.25F, (float32)0.17F, (float32)0.12F, (float32)0.11F, (float32)0.21F, (float32)0.33F, (float32)0.43F, (float32)0.56F, (float32)0.72F, (float32)0.71F, (float32)0.7F, (float32)0.7F, (float32)0.7F, (float32)0.7F, (float32)0.7F},

 /* k_AEB_VehHiBrkLowPersistanceCnt_str */   (uint8)   0 ,

 /* k_AEB_VRUHiBrkLowPersistanceCnt_str */   (uint8)   1 ,

 /* k_AEB_HiBrkACCStrongBrkCnt_str */   (uint8)   2 ,

 /* k_AEB_HiBrkMaxSpdMov_str */   (float32)  41.67F,

 /* k_AEB_HiBrkMaxSpdStat_str */   (float32)  31.111F,

 /* k_AEB_HiBrkMinRlsTm_str */   (float32)  0.2F,

 /* k_AEB_HiBrakingLvlMov_mps_str */   (float32)  -8.0F,

 /* k_AEB_HiBrakingLvlStat_mps_str */   (float32)  -8.0F,

 /* k_AEB_LittleBrakeDecel_mps_str */   (float32)  -2.0F,

 /* k_AEB_HiBrkMinSpdChkEnbl_str */   (boolean)   1 ,

 /* k_AEB_HoldDrvActionWithBrk_str */   (boolean)   0 ,

 /* k_AEB_DBSAbsMaxDecel_str */   (float32)  -10.0F,

 /* k_AEB_DBSLdTmMov_sec_str[ 15 ]*/   { (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.33F, (float32)0.28F, (float32)0.25F, (float32)0.23F, (float32)0.28F, (float32)0.29F, (float32)0.3F, (float32)0.3F, (float32)0.3F, (float32)0.3F, (float32)0.3F},

 /* k_AEB_DBSLdTmStat_sec_str[ 15 ]*/   { (float32)1.0F, (float32)0.8F, (float32)0.75F, (float32)0.7F, (float32)0.73F, (float32)0.75F, (float32)0.8F, (float32)0.9F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_AEB_WrapperLpTm_ms_str */   (uint16)   20 ,

 /* k_AEB_LCHighFactor_str */   (float32)  1.0F,

 /* k_AEB_LCHdTm_str */   (float32)  0.0F,

 /* k_AEB_LCLongTermSteerGain_str */   (float32)  0.9753F,

 /* k_AEB_LCSpdIntercept_str */   (float32)  25.5F,

 /* k_AEB_LCSpdSlope_str */   (float32)  0.0F,

 /* k_AEB_LwBrkLateralLimit_str */   (float32)  1.5F,

 /* k_AEB_LwBrkLdTmMov_sec_str[ 15 ]*/   { (float32)0.4F, (float32)0.29F, (float32)0.2F, (float32)0.2F, (float32)0.13F, (float32)0.08F, (float32)-0.05F, (float32)-0.07F, (float32)-0.21F, (float32)-0.21F, (float32)-0.2F, (float32)-0.2F, (float32)-0.2F, (float32)-0.2F, (float32)-0.2F},

 /* k_AEB_LwBrkLdTmStat_sec_str[ 15 ]*/   { (float32)0.7F, (float32)0.35F, (float32)0.32F, (float32)0.08F, (float32)0.11F, (float32)0.29F, (float32)0.4F, (float32)0.53F, (float32)0.68F, (float32)0.69F, (float32)0.7F, (float32)0.7F, (float32)0.7F, (float32)0.7F, (float32)0.7F},

 /* k_AEB_LwBrkMaxSpdMov_str */   (float32)  41.67F,

 /* k_AEB_LwBrkMaxSpdStat_str */   (float32)  31.11F,

 /* k_AEB_LwBrkMinSpdChkEnbl_str */   (boolean)   1 ,

 /* k_AEB_LwBrkPersistanceCnt_str */   (uint8)   2 ,

 /* k_AEB_LwBrakingLvl_mps_str */   (float32)  -4.0F,

 /* k_AEB_LwBrakingThrshACCBrk_str */   (float32)  -2.5F,

 /* k_AEB_MinClosingSpd_str */   (float32)  -1.8F,

 /* k_AEB_MinVehicleSpd_str */   (float32)  1.11F,

 /* k_AEB_MovingAwayNoiseLvlNeg_str */   (float32)  -0.2F,

 /* k_AEB_MovingAwayNoiseLvlPos_str */   (float32)  0.2F,

 /* k_AEB_PathFarWidthEntryGate_str */   (float32)  0.75F,

 /* k_AEB_PathFarWidthExitGate_str */   (float32)  0.9F,

 /* k_AEB_PathHitDistanceEntryGate_str */   (float32)  1.3F,

 /* k_AEB_PathHitDistanceExitGate_str */   (float32)  4.0F,

 /* k_AEB_PathNearFarTransitRng_str */   (float32)  60.0F,

 /* k_AEB_PathNearWidthEntryGate_str */   (float32)  1.23F,

 /* k_AEB_PathNearWidthExitGate_str */   (float32)  1.3F,

 /* k_AEB_PathYawDistanceEntryGate_str */   (float32)  1.2F,

 /* k_AEB_PathYawDistanceExitGate_str */   (float32)  1.75F,

 /* k_AEB_DBSPathYawDistExitGate_str */   (float32)  10.0F,

 /* k_AEB_PrefillLateralLimit_str */   (float32)  1.5F,

 /* k_AEB_PrefillLdTmMov_sec_str[ 15 ]*/   { (float32)0.8F, (float32)0.69F, (float32)0.6F, (float32)0.6F, (float32)0.53F, (float32)0.48F, (float32)0.35F, (float32)0.33F, (float32)0.19F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F},

 /* k_AEB_PrefillLdTmStat_sec_str[ 15 ]*/   { (float32)1.1F, (float32)0.75F, (float32)0.72F, (float32)0.48F, (float32)0.51F, (float32)0.69F, (float32)0.8F, (float32)0.93F, (float32)1.08F, (float32)1.09F, (float32)1.1F, (float32)1.1F, (float32)1.1F, (float32)1.1F, (float32)1.1F},

 /* k_AEB_PrefillMinSpdChkEnbl_str */   (boolean)   1 ,

 /* k_AEB_ReferLowToTTEMinStat_str */   (boolean)   1 ,

 /* k_AEB_UseTwoLevelDecel_str */   (boolean)   1 ,

 /* k_AEB_ReleaseOvrdTime_ms_str */   (uint16)   2000 ,

 /* k_AEB_SteeringInhibitHaloTime_str */   (uint16)   2000 ,

 /* k_AEB_SteeringAngleRtTrhd_str[ 6 ]*/   { (float32)100.0F, (float32)100.0F, (float32)75.0F, (float32)50.0F, (float32)35.0F, (float32)35.0F},

 /* k_AEB_OvrdSteeringRateMax_str */   (float32)  200.0F,

 /* k_AEB_JAOvrdSteeringRateMax_str */   (uint16)   2047 ,

 /* k_AEB_JAOvrdYawRateMax_str */   (float32)  2560.0F,

 /* k_AEB_SteeringRtOvrdGain_str */   (float32)  0.6065F,

 /* k_AEB_TTBAccBrkDelay_str */   (float32)  0.0F,

 /* k_AEB_TTBAvgBrkDelay_str */   (float32)  0.3F,

 /* k_AEB_TTBMaxSpd_str */   (float32)  30.0F,

 /* k_AEB_TTCIntegAccelEntry_str */   (float32)  2.0F,

 /* k_AEB_TTCIntegAccelExit_str */   (float32)  1.0F,

 /* k_AEB_TTCIntegDecelEntry_str */   (float32)  -1.5F,

 /* k_AEB_TTCIntegDecelExit_str */   (float32)  -1.0F,

 /* k_AEB_TTCIntegMaxSteps_str */   (uint8)   160 ,

 /* k_AEB_TTCIntegMaxTime_str */   (float32)  4.0F,

 /* k_AEB_TTCIntegTimeStep_str */   (float32)  0.025F,

 /* k_AEB_TTCLowerClip_x_str[ 5 ]*/   { (float32)1.0F, (float32)2.9F, (float32)5.6F, (float32)7.8F, (float32)9.8F},

 /* k_AEB_TTCLowerClip_z_str[ 5 ]*/   { (float32)0.9F, (float32)0.9F, (float32)0.85F, (float32)0.85F, (float32)0.8F},

 /* k_AEB_TTCMax_str */   (float32)  7.0F,

 /* k_AEB_TTCMaxEvalTime_str */   (float32)  3.2F,

 /* k_AEB_TTCMinEvalTime_str */   (float32)  0.2F,

 /* k_AEB_TTTAverageTurnAccel_str */   (float32)  4.0F,

 /* k_AEB_TTCMinClipSpd_str */   (float32)  6.6875F,

 /* k_AEB_TTCMinClipRR_str */   (float32)  0.1F,

 /* k_AEB_TTCUpperClip_x_str[ 5 ]*/   { (float32)1.0F, (float32)2.9F, (float32)5.6F, (float32)7.8F, (float32)9.8F},

 /* k_AEB_TTCUpperClip_z_str[ 5 ]*/   { (float32)1.1F, (float32)1.1F, (float32)1.15F, (float32)1.15F, (float32)1.2F},

 /* k_AEB_TTTMinLatMovement_str */   (float32)  0.5F,

 /* k_AEB_WheelSpdFilterGain_str */   (float32)  0.0F,

 /* k_AEB_YawNeutral_str */   (float32)  0.125F,

 /* k_AEB_YawNoiseFloorForXolc_str */   (float32)  1.125F,

 /* k_AEB_HostAcceAeblRdcFac_str[ 9 ]*/   { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_AEB_HostAccelPoints_str[ 9 ]*/   { (float32)-4.0F, (float32)-3.0F, (float32)-2.0F, (float32)-1.0F, (float32)-0.5F, (float32)1.0F, (float32)2.0F, (float32)3.0F, (float32)4.0F},

 /* k_AEB_HMIBrakingEnbld_str */   (boolean)   1 ,

 /* k_AEB_LowBrakeAlertEnbl_str */   (boolean)   1 ,

 /* k_AEB_PrefillBrakeAlertEnbl_str */   (boolean)   0 ,

 /* k_AEB_OvrdYawRateMax_str */   (float32)  2560.0F,

 /* k_AEB_SteerOvrdOffHdTm_str */   (float32)  0.0F,

 /* k_AEB_SteerOvrdOffTTEMinMinusX_str */   (float32)  0.1F,

 /* k_AEB_VehSSettingValue_str */   (uint8)   3 ,

 /* k_AEB_FLBALatchTime_str */   (uint16)   300 ,

 /* k_AEB_PrefillLatchTime_str */   (uint16)   300 ,

 /* k_AEB_UsePrefillOverride_str */   (boolean)   0 ,

 /* k_AEB_UseUnclippedComTTC_str */   (boolean)   0 ,

 /* k_AEB_OnlyCommonTTC_str */   (boolean)   1 ,

 /* k_AEB_RCSFilterGain_str */   (float32)  0.779F,

 /* k_AEB_AllowHiBrkUnclipped_str */   (boolean)   1 ,

 /* k_AEB_HeavyHighSpdTrhd_str */   (float32)  22.222F,

 /* k_AEB_HeavyFullSpdTrhd_str */   (float32)  4.1875F,

 /* k_AEB_MinHeavyFullSpdTrhd_str */   (float32)  7.0F,

 /* k_AEB_MaxHeavyFullSpdTrhd_str */   (float32)  8.0F,

 /* k_AEB_FullBrakingLvlMov_mps_str */   (float32)  -10.0F,

 /* k_AEB_FullBrakingLvlStat_mps_str */   (float32)  -10.0F,

 /* k_AEB_MaxDecelRadarOnly_str */   (float32)  -3.92F,

 /* k_AEB_CnfmByCameraEnbl_str */   (boolean)   1 ,

 /* k_AEB_HiBrkSpdTrhd_str */   (float32)  6.0F,

 /* k_AEB_ZeroSpdTrhd_str */   (float32)  2.0F,

 /* k_AEB_CIBEventLatchTime_str */   (uint16)   3000 ,

 /* k_AEB_BrkHdTmAfterStop_str */   (uint16)   2000 ,

 /* k_AEB_TestSceneHdTm_ms_str */   (uint16)   300 ,

 /* k_AEB_FltGainLateralAccel_str */   (float32)  0.909F,

 /* k_AEB_VRUHiBrkMaxSpd_str */   (float32)  23.625F,

 /* k_AEB_OCBike_ABAMaxSpd_mps_str */   (float32)  23.6111F,

 /* k_AEB_LongBike_ABAMaxSpd_mps_str */   (float32)  23.6111F,

 /* k_AEB_CrsBike_ABAMaxSpd_mps_str */   (float32)  18.0556F,

 /* k_AEB_StatBike_ABAMaxSpd_mps_str */   (float32)  23.6111F,

 /* k_AEB_OCPed_ABAMaxSpd_mps_str */   (float32)  18.0556F,

 /* k_AEB_NonCrsPed_ABAMaxSpd_mps_str */   (float32)  23.6111F,

 /* k_AEB_CrsPed_ABAMaxSpd_mps_str */   (float32)  18.0556F,

 /* k_AEB_OCBike_IBAMaxSpd_mps_str */   (float32)  18.0556F,

 /* k_AEB_LongBike_IBAMaxSpd_mps_str */   (float32)  18.0556F,

 /* k_AEB_CrsBike_IBAMaxSpd_mps_str */   (float32)  18.0556F,

 /* k_AEB_StatBike_IBAMaxSpd_mps_str */   (float32)  18.0556F,

 /* k_AEB_OCPed_IBAMaxSpd_mps_str */   (float32)  17.7778F,

 /* k_AEB_NonCrsPed_IBAMaxSpd_mps_str */   (float32)  17.7778F,

 /* k_AEB_CrsPed_IBAMaxSpd_mps_str */   (float32)  17.7778F,

 /* k_AEB_NonCrsPed_IBAMinSpd_mps_str */   (float32)  2.2222F,

 /* k_AEB_VRUMinHostSpd_mps_str */   (float32)  0.5556F,

 /* k_AEB_VRUMaxHostSpd_mps_str */   (float32)  23.6111F,

 /* k_AEB_PFVRUMaxHostSpd_mps_str */   (float32)  17.7778F,

 /* k_AEB_VRULongRange_str[ 7 ]*/   { (float32)0.0F, (float32)2.0F, (float32)5.0F, (float32)10.0F, (float32)15.0F, (float32)20.0F, (float32)25.0F},

 /* k_AEB_VRULatOffsetTrhd_str[ 7 ]*/   { (float32)1.25F, (float32)1.25F, (float32)1.25F, (float32)1.25F, (float32)1.2F, (float32)1.1F, (float32)1.1F},

 /* k_AEB_VRUEnable_str */   (boolean)   1 ,

 /* k_AEB_EnableOncoming_str */   (boolean)   0 ,

 /* k_AEB_UseHostLatAccel_str */   (boolean)   0 ,

 /* k_AEB_VRUYPosHoldOnTrhd_str */   (float32)  1.0F,

 /* k_AEB_MinMatchConfMov_str */   (uint8)   4 ,

 /* k_AEB_MinMatchConfStat_str */   (uint8)   4 ,

 /* k_AEB_UseROCXolc_str */   (boolean)   0 ,

 /* k_AEB_HostLatAccelSign_str */   (sint8)  -1 ,

 /* k_AEB_RevGearHoldRlsEnbl_str */   (boolean)   1 ,

 /* k_AEB_TTCAnnoyOffset_str */   (float32)  0.699F,

 /* k_AEB_TTCAnnoyMinEnbl_str */   (boolean)   0 ,

 /* k_AEB_TTCAnnoyMax_str */   (float32)  2.1F,

 /* k_AEB_ReferLeadAccel_str */   (boolean)   0 ,

 /* k_AEB_GateMinOpeningRange_str */   (float32)  0.6F,

 /* k_AEB_UseMinTrkAccel_str */   (boolean)   1 ,

 /* k_AEB_HighBrkAnnoyTTCThrs_str */   (float32)  1.275F,

 /* k_AEB_HighBrkLeadDecelTrhd_str */   (float32)  -3.92F,

 /* k_AEB_HiBrkLdTmStop_sec_str[ 10 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.05F, (float32)0.1F, (float32)0.15F, (float32)0.15F, (float32)0.15F, (float32)0.15F},

 /* k_AEB_HiBrkLdTmStop_mps_str[ 10 ]*/   { (float32)1.5F, (float32)2.75F, (float32)4.125F, (float32)5.5F, (float32)6.9375F, (float32)8.1875F, (float32)9.5F, (float32)11.0F, (float32)12.5F, (float32)15.0F},

 /* k_AEB_AlertOnlyTTCTrhd_str */   (float32)  -1.0F,

 /* k_AEB_HostAccelInhbtTrhd_str */   (float32)  30.0F,

 /* k_AEB_UseLeadAccelFCW_str */   (boolean)   1 ,

 /* k_AEB_BrkPedPosFiltgain_str */   (float32)  1.0F,

 /* k_AEB_DBSDrvBrkPdlPosThres_str */   (float32)  5.0F,

 /* k_AEB_DBSDrvBrkPdlPrsThres_str */   (float32)  200.0F,

 /* k_AEB_DBSPedRateEnblTm_str */   (float32)  0.0F,

 /* k_AEB_DBSPedRateHdTm_str */   (uint16)   150 ,

 /* k_AEB_DBSActiveMinPedPos_str */   (float32)  20.0F,

 /* k_AEB_DBSPedPosEnblTm_str */   (float32)  0.0F,

 /* k_AEB_DBSMinBrkPedRateOff_str */   (sint32)   0 ,

 /* k_AEB_DBSPedRateDsblTm_str */   (float32)  0.0F,

 /* k_AEB_DBSReleaseMinPedPos_str */   (float32)  0.0F,

 /* k_AEB_DBSPedPosDisableTime_str */   (float32)  0.0F,

 /* k_AEB_DBSMinBrkPedRateOn_str */   (sint32)   60 ,

 /* k_AEB_DBSLBMinBrkPedRateOn_str */   (sint32)   80 ,

 /* k_AEB_DBSHBMinBrkPedRateOn_str */   (sint32)   80 ,

 /* k_AEB_DBSFBMinBrkPedRateOn_str */   (sint32)   80 ,

 /* k_AEB_DrvBrkPressFiltgain_str */   (float32)  1.0F,

 /* k_AEB_DBSMinDrvAppBrkPresOn_str */   (uint16)   2550 ,

 /* k_AEB_DBSPressEnblTm_str */   (float32)  0.0F,

 /* k_AEB_DBSDrvBrkPrsRateOn_str */   (sint32)   0 ,

 /* k_AEB_DBSPrsRateEnblTm_str */   (float32)  0.0F,

 /* k_AEB_DBSMinDrvAppBrkPresOff_str */   (uint16)   525 ,

 /* k_AEB_DBSPressDisableTime_str */   (float32)  0.0F,

 /* k_AEB_DBSDrvBrkPrsRateOff_str */   (sint32)   50000 ,

 /* k_AEB_DBSPrsRateDisableTime_str */   (float32)  0.0F,

 /* k_AEB_DBSAccelOffset_sec_str[ 8 ]*/   { (float32)0.225F, (float32)0.225F, (float32)0.25F, (float32)0.2F, (float32)0.225F, (float32)0.125F, (float32)0.1F, (float32)0.0F},

 /* k_AEB_DBSAccelOffset_mpss_str[ 8 ]*/   { (float32)-9.81F, (float32)-6.8F, (float32)-5.0F, (float32)-3.8F, (float32)-2.93F, (float32)-2.5F, (float32)-2.1F, (float32)-1.0F},

 /* k_AEB_DBSWhlSpdAcceEnbl_str */   (boolean)   0 ,

 /* k_AEB_DBSTTCBsdRampdownRate_str[ 5 ]*/   { (float32)2.0F, (float32)1.5F, (float32)0.7F, (float32)0.4F, (float32)0.3F},

 /* k_AEB_DBSTTCBsdRampdown_sec_str[ 5 ]*/   { (float32)0.0F, (float32)0.5F, (float32)1.0F, (float32)1.5F, (float32)2.0F},

 /* k_AEB_DBSTTCBsdRampupRate_str[ 5 ]*/   { (float32)0.05F, (float32)0.05F, (float32)0.1F, (float32)0.1F, (float32)0.1F},

 /* k_AEB_DBSTTCBsdRampup_sec_str[ 5 ]*/   { (float32)0.0F, (float32)0.5F, (float32)1.0F, (float32)1.5F, (float32)2.0F},

 /* k_AEB_DBSBrkPedPosOnlyEnbl_str */   (boolean)   0 ,

 /* k_AEB_DBSDrvBrkPrsOnlyEnbl_str */   (boolean)   1 ,

 /* k_AEB_DBSMinLeadAccel_str */   (float32)  -2.0F,

 /* k_AEB_DBSMinRangeAccel_str */   (float32)  -1.5F,

 /* k_AEB_DBSLeadAccelFact_str */   (float32)  1.1F,

 /* k_AEB_DBSHostDecelThrsFac_str */   (float32)  1.0F,

 /* k_AEB_DBSMinDecelRampOut_str */   (float32)  0.0F,

 /* k_AEB_HostAccelInhbtHaloTime_str */   (uint16)   0 ,

 /* k_AEB_DBSBrkDualCnfmEnbl_str */   (boolean)   0 ,

 /* k_AEB_DBSDualConfirmMaxTime_str */   (uint16)   200 ,

 /* k_AEB_DBSMaxActivationWindow_str */   (uint16)   10000 ,

 /* k_AEB_DBSBrakeCnfmEnbl_str */   (boolean)   0 ,

 /* k_AEB_DBSLeadAclOfst_sec_str[ 8 ]*/   { (float32)0.175F, (float32)0.163F, (float32)0.15F, (float32)0.125F, (float32)0.1F, (float32)0.065F, (float32)0.04F, (float32)0.0F},

 /* k_AEB_DBSLeadAclOfst_mpss_str[ 8 ]*/   { (float32)-9.81F, (float32)-5.0F, (float32)-3.8F, (float32)-3.0F, (float32)-2.8F, (float32)-2.5F, (float32)-2.1F, (float32)-1.0F},

 /* k_AEB_DBSMinStopDistance_str */   (float32)  0.6F,

 /* k_AEB_DBSMinStopDistanceLmt_str */   (float32)  0.5F,

 /* k_AEB_DBSRRAccelFiltGain_str */   (float32)  1.0F,

 /* k_AEB_DBSRngAccelFiltGain_str */   (float32)  0.5F,

 /* k_AEB_DBSRngBsdAccelEnbl_str */   (boolean)   0 ,

 /* k_AEB_DBSLdAclBsdAccelEnbl_str */   (boolean)   0 ,

 /* k_AEB_DrvOvrdBaseBrkPdPos_str */   (float32)  80.0F,

 /* k_AEB_PrefillMaxSpdMov_str */   (float32)  41.6667F,

 /* k_AEB_PrefillMaxSpdStat_str */   (float32)  23.6111F,

 /* k_AEB_FLBALdTmMov_sec_str[ 15 ]*/   { (float32)1.2F, (float32)1.24F, (float32)1.24F, (float32)1.23F, (float32)1.2F, (float32)1.17F, (float32)1.28F, (float32)1.0F, (float32)1.0F, (float32)1.05F, (float32)1.1F, (float32)1.1F, (float32)1.1F, (float32)1.1F, (float32)1.1F},

 /* k_AEB_FLBALdTmStat_sec_str[ 15 ]*/   { (float32)1.5F, (float32)1.15F, (float32)1.09F, (float32)1.02F, (float32)1.18F, (float32)1.35F, (float32)1.3F, (float32)1.58F, (float32)1.63F, (float32)1.71F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F},

 /* k_AEB_MSLdTmMov_sec_str[ 15 ]*/   { (float32)1.0F, (float32)0.9F, (float32)0.88F, (float32)0.85F, (float32)0.98F, (float32)1.1F, (float32)0.9F, (float32)0.9F, (float32)0.9F, (float32)0.9F, (float32)0.9F, (float32)0.9F, (float32)0.9F, (float32)0.9F, (float32)0.9F},

 /* k_AEB_MSLdTmStat_sec_str[ 15 ]*/   { (float32)1.2F, (float32)1.0F, (float32)0.98F, (float32)0.95F, (float32)1.0F, (float32)1.05F, (float32)1.25F, (float32)1.5F, (float32)1.5F, (float32)1.53F, (float32)1.55F, (float32)1.55F, (float32)1.55F, (float32)1.55F, (float32)1.55F},

 /* k_AEB_FLBAMinSpdChkEnbl_str */   (boolean)   1 ,

 /* k_AEB_FLBAMaxSpdMov_str */   (float32)  41.6667F,

 /* k_AEB_FLBAMaxSpdStat_str */   (float32)  23.6111F,

 /* k_AEB_MSMinSpdChkEnbl_str */   (boolean)   1 ,

 /* k_AEB_MSMaxSpdMov_str */   (float32)  50.0F,

 /* k_AEB_MSMaxSpdStat_str */   (float32)  50.0F,

 /* k_AEB_DBSMaxSpdMov_str */   (float32)  41.6667F,

 /* k_AEB_DBSMaxSpdStat_str */   (float32)  23.6111F,

 /* k_AEB_VRUMinMatchConf_str */   (uint8)   4 ,

 /* k_AEB_VRUDBSEnbl_str */   (boolean)   1 ,

 /* k_AEB_SteerOvrdOffTTEMin_str */   (float32)  0.7F,

 /* k_AEB_FLBADefaultEnbl_str */   (boolean)   0 ,

 /* k_AEB_FLBAIgnoreHMIStng_str */   (boolean)   0 ,

 /* k_AEB_FLBAHMICustStng_str */   (uint8)   2 ,

 /* k_AEB_MinStopDefaultEnbl_str */   (boolean)   0 ,

 /* k_AEB_MinStopIgnoreHMIStng_str */   (boolean)   0 ,

 /* k_AEB_MinStopHMICustStng_str */   (uint8)   2 ,

 /* k_AEB_DBSIgnoreHMIStng_str */   (boolean)   0 ,

 /* k_AEB_DBSHMICustStng_str */   (uint8)   2 ,

 /* k_AEB_IgnLowBrkHBTimerReset_str */   (boolean)   0 ,

 /* k_AEB_DBSMaxDecelExitTime_str */   (float32)  10.0F,

 /* k_AEB_PrefillExitTime_str */   (float32)  10.0F,

 /* k_AEB_FLBAExitTime_str */   (float32)  10.0F,

 /* k_AEB_MinStopExitTime_str */   (float32)  10.0F,

 /* k_AEB_MaxDecelExitTime_str */   (float32)  10.0F,

 /* k_AEB_HoldRelPressure_str */   (uint16)   300 ,

 /* k_AEB_UseOnlyBrkPrsHldRel_str */   (boolean)   1 ,

 /* k_AEB_NoEPBBrakeHdTm_str */   (uint32)   2000 ,

 /* k_AEB_VRUOncomingEnbl_str */   (boolean)   0 ,

 /* k_AEB_HiConfOCBikePFTTC_sec_str[ 15 ]*/   { (float32)0.7F, (float32)0.6F, (float32)0.65F, (float32)0.7F, (float32)0.8F, (float32)0.9F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},

 /* k_AEB_HiConfOCBikeLoBrkTTC_sec_str[ 15 ]*/   { (float32)0.5F, (float32)0.4F, (float32)0.45F, (float32)0.5F, (float32)0.6F, (float32)0.7F, (float32)0.9F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_AEB_HiConfOCBikeHiBrkTTC_sec_str[ 15 ]*/   { (float32)0.4F, (float32)0.3F, (float32)0.35F, (float32)0.4F, (float32)0.5F, (float32)0.6F, (float32)0.7F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_HiConfOCPedPrefillTTC_sec_str[ 15 ]*/   { (float32)1.0F, (float32)1.0F, (float32)0.95F, (float32)0.9F, (float32)1.1F, (float32)1.2F, (float32)1.3F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F},

 /* k_AEB_HiConfOCPedLoBrkTTC_sec_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.75F, (float32)0.7F, (float32)0.9F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},

 /* k_AEB_HiConfOCPedHiBrkTTC_sec_str[ 15 ]*/   { (float32)0.5F, (float32)0.5F, (float32)0.55F, (float32)0.6F, (float32)0.7F, (float32)0.8F, (float32)0.9F, (float32)1.0F, (float32)1.1F, (float32)1.1F, (float32)1.1F, (float32)1.1F, (float32)1.1F, (float32)1.1F, (float32)1.1F},

 /* k_AEB_AccelOffsetRangeBrkPoints_str[ 7 ]*/   { (float32)5.0F, (float32)10.0F, (float32)15.0F, (float32)20.0F, (float32)25.0F, (float32)30.0F, (float32)40.0F},

 /* k_AEB_SteerOvrdDisbleType_str */   (uint8)   2 ,

 /* k_AEB_HighBrkAnnoyTTCLose_str */   (float32)  0.0F,

 /* k_AEB_LowBrkAnnoyTTLose_str */   (float32)  0.0F,

 /* k_AEB_RangeDecelTrhd_str */   (float32)  -2.5F,

 /* k_AEB_LeadDecelTrhd_str */   (float32)  -2.5F,

 /* k_AEB_DBSMinSpdChkEnbl_str */   (boolean)   1 ,

 /* k_AEB_DBSUseDefaultDecel_str */   (boolean)   1 ,

 /* k_AEB_IgnoreObjClassChk_str */   (boolean)   1 ,

 /* k_AEB_MinEgoSpdRadarOnly_str */   (float32)  13.9F,

 /* k_AEB_MinMatchConfMovLowSpd_str */   (uint8)   4 ,

 /* k_AEB_HardTurnInhibitSpdPoints_str[ 6 ]*/   { (float32)2.0F, (float32)2.2F, (float32)5.5F, (float32)8.3F, (float32)11.1F, (float32)11.2F},

 /* k_AEB_HardTurnStrAngleTrhd_str[ 9 ]*/   { (float32)60.0F, (float32)50.0F, (float32)43.0F, (float32)35.0F, (float32)35.0F, (float32)35.0F, (float32)30.0F, (float32)25.0F, (float32)15.0F},

 /* k_AEB_StrAngInhibitEnblTm_str */   (float32)  0.2F,

 /* k_AEB_BrkEngagePresEnblTm_str */   (float32)  0.5F,

 /* k_AEB_BrkEngageHdTm_str */   (uint16)   2000 ,

 /* k_AEB_IgrLowBrkDrvEng_str */   (boolean)   0 ,

 /* k_AEB_DBSMinVehicleSpd_str */   (float32)  1.1111F,

 /* k_AEB_BcyMaxRangeRate_str */   (float32)  0.75F,

 /* k_AEB_IgrHiBrkDrvEng_str */   (boolean)   0 ,

 /* k_AEB_DrvEngInhibitSpd_str */   (float32)  50.0F,

 /* k_AEB_VRUHBMinConf_str */   (uint8)   4 ,

 /* k_AEB_HBHdTmLowAge_str */   (float32)  0.0F,

 /* k_AEB_OtherTrgtMinDeltaYpos_str */   (float32)  3.0F,

 /* k_AEB_VRULatDeSelTrhd_str[ 7 ]*/   { (float32)1.1F, (float32)1.1F, (float32)1.05F, (float32)0.95F, (float32)0.9F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_GasInhibitLowSpdTrhd_str */   (float32)  8.375F,

 /* k_AEB_GasInhibitHiSpdTrhd_str */   (float32)  9.75F,

 /* k_AEB_VehHBDrvEngTypeSltd_str */   (uint8)   3 ,

 /* k_AEB_VehLBDrvEngTypeSltd_str */   (uint8)   7 ,

 /* k_AEB_VehPFDrvEngTypeSltd_str */   (uint8)   7 ,

 /* k_AEB_IgrPrefillDrvEng_str */   (boolean)   0 ,

 /* k_AEB_VRUHBDrvEngTypeSltd_str */   (uint8)   3 ,

 /* k_AEB_VRULBDrvEngTypeSltd_str */   (uint8)   7 ,

 /* k_AEB_IgrVRUPFDrvEng_str */   (boolean)   0 ,

 /* k_AEB_VRUPFDrvEngTypeSltd_str */   (uint8)   7 ,

 /* k_AEB_HiBrkDropWaitTime_str */   (uint16)   4000 ,

 /* k_AEB_VRUHBHoldMaxRngAllow_str[ 9 ]*/   { (float32)3.0F, (float32)3.0F, (float32)3.5F, (float32)4.0F, (float32)4.5F, (float32)5.0F, (float32)5.5F, (float32)7.0F, (float32)8.0F},

 /* k_AEB_HBHoldMaxRngAllow_str[ 9 ]*/   { (float32)2.5F, (float32)2.5F, (float32)2.8F, (float32)3.3F, (float32)3.5F, (float32)4.0F, (float32)5.5F, (float32)7.0F, (float32)8.0F},

 /* k_AEB_DRTClassHoldEnbl_str */   (boolean)   0 ,

 /* k_AEB_GateMinRangeMov_str */   (float32)  2.0F,

 /* k_AEB_GateMinRangeStat_str */   (float32)  2.0F,

 /* k_AEB_ClsFstDectIPAOffset_str */   (uint8)   50 ,

 /* k_AEB_OvtkStrAngleTrhd_str[ 9 ]*/   { (float32)80.0F, (float32)35.0F, (float32)32.0F, (float32)30.0F, (float32)28.0F, (float32)25.0F, (float32)25.0F, (float32)20.0F, (float32)17.0F},

 /* k_AEB_OvtkGasPedalTrhd_str[ 9 ]*/   { (float32)30.0F, (float32)20.0F, (float32)15.0F, (float32)15.0F, (float32)15.0F, (float32)15.0F, (float32)18.0F, (float32)20.0F, (float32)25.0F},

 /* k_AEB_LongBikePFLdTm_mps_str[ 10 ]*/   { (float32)1.5F, (float32)2.75F, (float32)4.125F, (float32)5.5F, (float32)6.9375F, (float32)8.1875F, (float32)9.5F, (float32)11.0F, (float32)12.5F, (float32)15.0F},

 /* k_AEB_LongBikePFLdTm_sec_str[ 15 ]*/   { (float32)1.7F, (float32)1.5F, (float32)1.5F, (float32)1.43F, (float32)1.48F, (float32)1.57F, (float32)1.57F, (float32)1.65F, (float32)1.7F, (float32)1.7F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F},

 /* k_AEB_LongBikeLBLdTm_mps_str[ 10 ]*/   { (float32)1.5F, (float32)2.75F, (float32)4.125F, (float32)5.5F, (float32)6.9375F, (float32)8.1875F, (float32)9.5F, (float32)11.0F, (float32)12.5F, (float32)15.0F},

 /* k_AEB_LongBikeLBLdTm_sec_str[ 15 ]*/   { (float32)0.3F, (float32)0.3F, (float32)0.3F, (float32)0.3F, (float32)0.3F, (float32)0.25F, (float32)0.2F, (float32)0.1F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_AEB_LongBikeHBLdTm_sec_str[ 15 ]*/   { (float32)1.03F, (float32)0.93F, (float32)0.78F, (float32)0.87F, (float32)1.08F, (float32)1.08F, (float32)1.13F, (float32)1.2F, (float32)1.39F, (float32)1.32F, (float32)1.24F, (float32)1.24F, (float32)1.24F, (float32)1.24F, (float32)1.24F},

 /* k_AEB_LongBikeFLBALdTm_sec_str[ 15 ]*/   { (float32)1.7F, (float32)1.6F, (float32)1.6F, (float32)1.53F, (float32)1.58F, (float32)1.67F, (float32)1.67F, (float32)1.75F, (float32)1.9F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F},

 /* k_AEB_LongBikeMSLdTm_sec_str[ 15 ]*/   { (float32)1.9F, (float32)1.7F, (float32)1.7F, (float32)1.63F, (float32)1.68F, (float32)1.77F, (float32)1.77F, (float32)1.85F, (float32)2.0F, (float32)1.9F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F},

 /* k_AEB_LongBikeDBSLdTm_sec_str[ 15 ]*/   { (float32)0.25F, (float32)0.15F, (float32)0.13F, (float32)0.15F, (float32)0.33F, (float32)0.28F, (float32)0.25F, (float32)0.23F, (float32)0.28F, (float32)0.29F, (float32)0.3F, (float32)0.3F, (float32)0.3F, (float32)0.3F, (float32)0.3F},

 /* k_AEB_HiConfBikeStaPFTTC_mps_str[ 10 ]*/   { (float32)1.5F, (float32)2.75F, (float32)4.125F, (float32)5.5F, (float32)6.9375F, (float32)8.1875F, (float32)9.5F, (float32)11.0F, (float32)12.5F, (float32)15.0F},

 /* k_AEB_HiConfBikeStaPFTTC_sec_str[ 15 ]*/   { (float32)1.35F, (float32)1.35F, (float32)1.35F, (float32)1.33F, (float32)1.42F, (float32)1.52F, (float32)1.62F, (float32)1.65F, (float32)1.7F, (float32)1.65F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F},

 /* k_AEB_BikeStaLBTTC_sec_str[ 15 ]*/   { (float32)1.08F, (float32)1.08F, (float32)1.08F, (float32)1.06F, (float32)1.15F, (float32)1.25F, (float32)1.35F, (float32)1.38F, (float32)1.43F, (float32)1.38F, (float32)1.33F, (float32)1.33F, (float32)1.33F, (float32)1.33F, (float32)1.33F},

 /* k_AEB_HiConfBikeStaHBTTC_sec_str[ 15 ]*/   { (float32)0.53F, (float32)0.61F, (float32)0.67F, (float32)0.77F, (float32)0.92F, (float32)1.04F, (float32)1.18F, (float32)1.2F, (float32)1.29F, (float32)1.27F, (float32)1.24F, (float32)1.24F, (float32)1.24F, (float32)1.24F, (float32)1.24F},

 /* k_AEB_HiConfBikeStaFLBATTC_sec_str[ 15 ]*/   { (float32)1.65F, (float32)1.65F, (float32)1.65F, (float32)1.63F, (float32)1.72F, (float32)1.82F, (float32)1.92F, (float32)1.95F, (float32)2.0F, (float32)1.95F, (float32)1.9F, (float32)1.9F, (float32)1.9F, (float32)1.9F, (float32)1.9F},

 /* k_AEB_HiConfBikeStaMSTTC_sec_str[ 15 ]*/   { (float32)1.75F, (float32)1.75F, (float32)1.75F, (float32)1.73F, (float32)1.82F, (float32)1.92F, (float32)2.02F, (float32)2.05F, (float32)2.0F, (float32)2.05F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F},

 /* k_AEB_HiConfBikeStaDBSTTC_sec_str[ 15 ]*/   { (float32)0.9F, (float32)0.9F, (float32)0.83F, (float32)0.75F, (float32)1.05F, (float32)1.35F, (float32)1.45F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F},

 /* k_AEB_FullBrakeHiBrkCnt_str */   (uint8)   2 ,

 /* k_AEB_JAFullBrakeHiBrkCnt_str */   (uint8)   2 ,

 /* k_AEB_FullBrkDuringTimer_mps_str */   (float32)  -8.82F,

 /* k_AEB_IgnLowBrkFBTimerReset_str */   (boolean)   0 ,

 /* k_AEB_IgnHiBrkFBTimerReset_str */   (boolean)   0 ,

 /* k_AEB_VRUAEBXolcTrhd_str[ 7 ]*/   { (float32)0.97F, (float32)0.93F, (float32)0.9F, (float32)0.8F, (float32)0.75F, (float32)0.7F, (float32)0.65F},

 /* k_AEB_HiBrkLowPerstCntJA_str */   (uint8)   0 ,

 /* k_AEB_DBSHostAccelTrhd_str */   (float32)  0.0F,

 /* k_AEB_SuppressTime_str */   (uint16)   20000 ,

 /* k_AEB_CLHiBrkNeedDecelLimt_str */   (float32)  -8.0F,

 /* k_AEB_NoAEBSuppressEnbl_str */   (boolean)   0 ,

 /* k_AEB_HeadingAngOCTAPTrhd_str */   (uint16)   18 ,

 /* k_AEB_HeadingAngCPTATrhd_str */   (uint16)   40 ,

 /* k_AEB_SensorInputLpTm_str */   (float32)  0.025F,

 /* k_AEB_VcanInputLpTm_str */   (float32)  0.02F,

 /* k_AEB_StationaryVehFullChkEnbl_str */   (boolean)   0 ,

 /* k_AEB_LongMovBikeFullChkEnbl_str */   (boolean)   0 ,

 /* k_AEB_leadAccelEnFullBrk_str */   (float32)  -3.5F,

 /* k_AEB_FullBrkRangePoints_str[ 8 ]*/   { (float32)0.5F, (float32)1.0F, (float32)1.5F, (float32)2.0F, (float32)3.0F, (float32)4.0F, (float32)5.0F, (float32)10.0F},

 /* k_AEB_FullBrkRngRtPoints_str[ 7 ]*/   { (float32)-10.0F, (float32)-5.0F, (float32)-4.0F, (float32)-3.0F, (float32)-2.0F, (float32)-1.5F, (float32)-1.0F},

 /* k_AEB_FullBrakeChkEnbl_str[ 7 ][ 8 ]*/   {
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)0.0F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)1.0F, (float32)1.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)1.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F}},

 /* k_AEB_AxleTorqueFiltTime_ms_str */   (uint16)   50 ,

 /* k_AEB_AxleTorqueRateMax_str */   (uint16)   1000 ,

 /* k_AEB_AxleTorqueRateMin_str */   (sint16)  -8192 ,

 /* k_AEB_BrakeAccelFiltTime_ms_str */   (uint16)   0 ,

 /* k_AEB_BrakeAccelRateMax_str */   (uint16)   500 ,

 /* k_AEB_BrakeAccelRateMin_str */   (sint16)  -500 ,

 /* k_AEB_DrvIntndAxlTrqMinNegOffst_str */   (sint16)   0 ,

 /* k_AEB_BrakeAccelFinalLimit_str */   (float32)  -9.8125F,

 /* k_AEB_HoldDecelEnbl_str */   (boolean)   1 ,

 /* k_AEB_HoldBrkReqEnbl_str */   (boolean)   1 ,

 /* k_AEB_UseAxleTrqtoBrk_str */   (boolean)   0 ,

 /* k_AEB_IgnorePedTTCChk_str */   (boolean)   0 ,

 /* k_AEB_IgnorePedRngChk_str */   (boolean)   0 ,

 /* k_AEB_VRUMaxTTCAllowed_str */   (float32)  6.0F,

 /* k_AEB_VRUMinTTCAllowed_str */   (float32)  0.3F,

 /* k_AEB_VRUMaxRngAllowed_str */   (float32)  50.0F,

 /* k_AEB_VRUMinRngAllowed_str */   (float32)  1.0F,

 /* k_AEB_EPBStateAffectHold_str */   (boolean)   0 ,

 /* k_AEB_MinConfSRRDegrade_str */   (uint8)   3 ,

 /* k_AEB_MovSRRMisAlignChkEnbl_str */   (boolean)   1 ,

 /* k_AEB_DBSReleaseAEBDisbl_str */   (boolean)   1 ,

 /* k_AEB_LowConfInPathAgeTrhd_str */   (uint8)   75 ,

 /* k_AEB_MedConfInPathAgeTrhd_str */   (uint8)   15 ,

 /* k_AEB_HiConfInPathAgeTrhd_str */   (uint8)   15 ,

 /* k_AEB_HiBrkMinReleaseDist_str */   (float32)  0.5F,

 /* k_AEB_EnVRUClutterShutDown_str */   (boolean)   0 ,

 /* k_AEB_HiBrkVisConfirmDisable_str */   (boolean)   1 ,

 /* k_AEB_LowBrkVisConfirmDisable_str */   (boolean)   1 ,

 /* k_AEB_GasEngagePosEnTime_str */   (float32)  1.0F,

 /* k_AEB_GasEngagePosEntryTrhd_str */   (uint8)   65 ,

 /* k_AEB_GasEngagePosExitTrhd_str */   (uint8)   60 ,

 /* k_AEB_GasPosRateEntryTrhd_str */   (sint16)   500 ,

 /* k_AEB_GasPosRateExitTrhd_str */   (sint16)   499 ,

 /* k_AEB_GasPosRateEnTime_str */   (float32)  100.0F,

 /* k_AEB_GasEngageHdTm_str */   (uint16)   1500 ,

 /* k_AEB_BrkEngagePosEntryTrhd_str */   (uint8)   9 ,

 /* k_AEB_BrkEngagePosExitTrhd_str */   (uint8)   4 ,

 /* k_AEB_BrkEngagePosEnTime_str */   (float32)  0.5F,

 /* k_AEB_HBNoVisFlagMinConf_str */   (uint8)   6 ,

 /* k_AEB_LBNoVisFlagMinConf_str */   (uint8)   6 ,

 /* k_AEB_UseNewPrefillCounter_str */   (uint8)   1 ,

 /* k_AEB_AllowOutFunAEBPRelease_str */   (boolean)   1 ,

 /* k_AEB_VRUHBMinConfEnblTime_str */   (float32)  0.1F,

 /* k_AEB_HBHdTmAgeTrhd_str */   (uint8)   50 ,

 /* k_AEB_VRUHBHdTmAgeTrhd_str */   (uint8)   10 ,

 /* k_AEB_ExtendUsePedHdTm_str */   (uint16)   2000 ,

 /* k_AEB_LastValHaloTime_str */   (uint16)   2000 ,

 /* k_AEB_VRULBMinConf_str */   (uint8)   4 ,

 /* k_AEB_VRULBMinConfEnblTm_str */   (float32)  0.1F,

 /* k_AEB_IDChangeHaloTime_str */   (uint16)   0 ,

 /* k_AEB_HiSpdGasRateEntryTrhd_str */   (sint16)   6 ,

 /* k_AEB_HiSpdGasRateExitTrhd_str */   (sint16)   4 ,

 /* k_AEB_HiSpdGasRateEnTime_str */   (float32)  0.4F,

 /* k_AEB_HiSpdGasInhibtHdTm_str */   (uint16)   1500 ,

 /* k_AEB_UnIdeLowestConfInPathTrhd_str */   (uint8)   100 ,

 /* k_AEB_UnIdeLowConfInPathTrhd_str */   (uint8)   75 ,

 /* k_AEB_UnIdeMedConfInPathTrhd_str */   (uint8)   40 ,

 /* k_AEB_UnIdeHiConfInPathTrhd_str */   (uint8)   30 ,

 /* k_AEB_LowestConfInPathAgeTrhd_str */   (uint8)   100 ,

 /* k_AEB_TTCReduceLatOfstBrkPoint_str[ 9 ]*/   { (float32)0.05F, (float32)0.1F, (float32)0.15F, (float32)0.2F, (float32)0.25F, (float32)0.3F, (float32)0.4F, (float32)0.5F, (float32)1.0F},

 /* k_AEB_HiConfLBTTCReduceFactor_str[ 9 ]*/   { (float32)1.0F, (float32)0.8F, (float32)0.7F, (float32)0.6F, (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.5F},

 /* k_AEB_HiConfHBTTCReduceFactor_str[ 9 ]*/   { (float32)1.0F, (float32)0.8F, (float32)0.7F, (float32)0.6F, (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.5F},

 /* k_AEB_HiConfDBSTTCReduceFactor_str[ 9 ]*/   { (float32)1.0F, (float32)0.8F, (float32)0.7F, (float32)0.6F, (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.5F, (float32)0.5F},

 /* k_AEB_NoTTCReduceLatEstTrhd_str */   (float32)  0.65F,

 /* k_AEB_LastBrkYposHaloTime_str */   (uint16)   2000 ,

 /* k_AEB_VRUFusHiConfLvl_str */   (uint8)   5 ,

 /* k_AEB_VRUFusMedConfLvl_str */   (uint8)   4 ,

 /* k_AEB_VRUVisMedConfLvl_str */   (uint8)   3 ,

 /* k_AEB_FusHiMinInPAgeTrhd_str */   (uint8)   4 ,

 /* k_AEB_FusHiMinInPAgeTrhdLong_str */   (uint8)   5 ,

 /* k_AEB_FusMedMinInPAgeTrhd_str */   (uint8)   8 ,

 /* k_AEB_VisMedMinInPAgeTrhd_str */   (uint8)   10 ,

 /* k_AEB_VisMedMinInPAgeTrhdLong_str */   (uint8)   10 ,

 /* k_AEB_FusMedMinInPAgeTrhdLong_str */   (uint8)   10 ,

 /* k_AEB_MinInPAgeTrhd_str */   (uint8)   20 ,

 /* k_AEB_MinInPAgeTrhdLong_str */   (uint8)   40 ,

 /* k_AEB_DrvBrkVRURlsEnTime_str */   (float32)  0.1F,

 /* k_AEB_GeneralSpdPoints_str[ 9 ]*/   { (float32)2.7F, (float32)5.6F, (float32)8.3F, (float32)11.1F, (float32)13.9F, (float32)16.7F, (float32)22.2F, (float32)27.8F, (float32)33.3F},

 /* k_AEB_OvtkMaxTTCTrhd_str */   (float32)  2.5F,

 /* k_AEB_OTMinXolcPercent_str */   (float32)  0.4F,

 /* k_AEB_OneWayXolcChgCountTrhd_str */   (uint8)   3 ,

 /* k_AEB_OvtkGasPdlHaloTime_str */   (uint16)   500 ,

 /* k_AEB_OvtkReducHaloTime_str */   (uint16)   4000 ,

 /* k_AEB_TTCReduceXolcBrkPoint_str[ 10 ]*/   { (float32)0.0F, (float32)0.2F, (float32)0.4F, (float32)0.6F, (float32)0.8F, (float32)1.0F, (float32)1.2F, (float32)1.4F, (float32)1.6F, (float32)2.0F},

 /* k_AEB_PrefillTTCReduceFactor_str[ 9 ]*/   { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)0.5F, (float32)0.5F, (float32)0.5F},

 /* k_AEB_LowTTCReduceFactor_str[ 9 ]*/   { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)0.5F, (float32)0.5F, (float32)0.5F},

 /* k_AEB_HBTTCReduceFactor_str[ 10 ]*/   { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)0.3F, (float32)0.3F},

 /* k_AEB_DBSTTCReduceFactor_str[ 10 ]*/   { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)0.5F, (float32)0.5F},

 /* k_AEB_NeedDecelFilterGain_str */   (float32)  1.0F,

 /* k_AEB_UseTrackerLeadAeecl_str */   (boolean)   1 ,

 /* k_AEB_LeadVehDecelTrhd_str */   (float32)  -1.0F,

 /* k_AEB_DecelDiffBrkPoints_str[ 13 ]*/   { (float32)-10.0F, (float32)-8.0F, (float32)-6.0F, (float32)-4.0F, (float32)-2.0F, (float32)-1.0F, (float32)0.0F, (float32)1.0F, (float32)2.0F, (float32)4.0F, (float32)6.0F, (float32)8.0F, (float32)10.0F},

 /* k_AEB_ESPSettlingTime_str[ 13 ]*/   { (float32)0.25F, (float32)0.2F, (float32)0.15F, (float32)0.11F, (float32)0.07F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)-0.1F, (float32)-0.15F},

 /* k_AEB_DesireStopDistance_str[ 15 ]*/   { (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F},

 /* k_AEB_UseCloseLoopDecel_str */   (boolean)   0 ,

 /* k_AEB_CLRampDownFactor_str[ 13 ]*/   { (float32)5.0F, (float32)3.0F, (float32)2.0F, (float32)1.6F, (float32)1.2F, (float32)1.0F, (float32)1.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_AEB_CLDecelBrkRelseTrhd_str */   (float32)  -0.1F,

 /* k_AEB_CLDecelBrkRelseEnTime_str */   (float32)  0.3F,

 /* k_AEB_EgoTartAccelBrkPoints_str[ 7 ]*/   { (float32)0.0F, (float32)1.0F, (float32)2.0F, (float32)4.0F, (float32)6.0F, (float32)8.0F, (float32)10.0F},

 /* k_AEB_TartInforFilterGain_str[ 7 ]*/   { (float32)0.8F, (float32)0.71F, (float32)0.6F, (float32)0.55F, (float32)0.45F, (float32)0.4F, (float32)0.4F},

 /* k_AEB_TartLeadSpdOffset_str */   (float32)  0.5F,

 /* k_AEB_LBDrvEngReducFactor_str */   (float32)  0.6F,

 /* k_AEB_HBDrvEngReducFactor_str */   (float32)  0.5F,

 /* k_AEB_DBSDrvEngReducFactor_str */   (float32)  0.6F,

 /* k_AEB_PFDrvEngReducFactor_str */   (float32)  0.7F,

 /* k_AEB_VehDBSDrvEngTypeSltd_str */   (uint8)   5 ,

 /* k_AEB_IgrDBSDrvEng_str */   (boolean)   0 ,

 /* k_AEB_PredTimeRRBrkPoint_str[ 11 ]*/   { (float32)-20.0F, (float32)-15.0F, (float32)-12.0F, (float32)-10.0F, (float32)-8.0F, (float32)-6.0F, (float32)-4.0F, (float32)-2.0F, (float32)-1.0F, (float32)0.0F, (float32)1.0F},

 /* k_AEB_PredTimeRAccelBrkPoint_str[ 5 ]*/   { (float32)-8.0F, (float32)-4.0F, (float32)-2.0F, (float32)-1.0F, (float32)0.0F},

 /* k_AEB_MaxPredictTime_str[ 5 ][ 11 ]*/   {
                            { (float32)3.2F, (float32)2.4F, (float32)2.2F, (float32)2.0F, (float32)1.8F, (float32)1.6F, (float32)1.2F, (float32)0.8F, (float32)0.6F, (float32)0.5F, (float32)0.4F},
                            { (float32)2.8F, (float32)2.0F, (float32)1.8F, (float32)1.6F, (float32)1.4F, (float32)1.3F, (float32)0.9F, (float32)0.6F, (float32)0.4F, (float32)0.3F, (float32)0.2F},
                            { (float32)2.0F, (float32)1.5F, (float32)1.2F, (float32)1.0F, (float32)0.8F, (float32)0.6F, (float32)0.5F, (float32)0.4F, (float32)0.3F, (float32)0.15F, (float32)0.1F},
                            { (float32)0.7F, (float32)0.6F, (float32)0.5F, (float32)0.4F, (float32)0.3F, (float32)0.2F, (float32)0.1F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F},
                            { (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F}},

 /* k_AEB_DrvEngUseTTCReduc_str */   (boolean)   0 ,

 /* k_AEB_NoESPDisDecelTrhd_str */   (float32)  -6.0F,

 /* k_AEB_NoESPDisRangeTrhd_str */   (float32)  3.0F,

 /* k_AEB_EgoAllowDisScalFactor_str */   (float32)  2.0F,

 /* k_AEB_EgoHiDynamicAccelTrhd_str */   (float32)  3.5F,

 /* k_AEB_LongVelFullHiDymic_str */   (float32)  1.5F,

 /* k_AEB_LongVelFull_str */   (float32)  1.2F,

 /* k_AEB_LongVelNegliHiDymic_str */   (float32)  1.1F,

 /* k_AEB_LongVelNegli_str */   (float32)  0.8F,

 /* k_AEB_MovLeadVelNegliEnTime_str */   (float32)  0.5F,

 /* k_AEB_MovLeadVelNegliHaloTime_str */   (uint16)   500 ,

 /* k_AEB_NonProceedVRUFullChkEnbl_str */   (boolean)   1 ,

 /* k_AEB_ESPDelayDisFadingTime_str */   (float32)  0.3F,

 /* k_AEB_AccuAngEgoStopHaloTime_str */   (uint32)   10000 ,

 /* k_AEB_MaxAllowVehHeadAngTime_str */   (float32)  20.0F,

 /* k_AEB_TTTUseTrtWidth_str */   (boolean)   1 ,

 /* k_AEB_TTTPersistXolcTrhd_str */   (float32)  0.7F,

 /* k_AEB_BrkPressurePositionSel_str */   (uint16)   3 ,

 /* k_AEB_HiBrkUseRangeTrigger_str */   (boolean)   1 ,

 /* k_AEB_HiBrkTrigMovRangeOffset_str[ 15 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_AEB_HiBrkTrigStatRangeOffset_str[ 15 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_AEB_LoBrkTrigMovDuration_str[ 15 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_AEB_LoBrkTrigStatDuration_str[ 15 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_AEB_PrefillTrigMovDuration_str[ 15 ]*/   { (float32)0.15F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F},

 /* k_AEB_PrefillTrigStatDuration_str[ 15 ]*/   { (float32)0.15F, (float32)0.15F, (float32)0.15F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F},

 /* k_AEB_FLBATrigMovDuration_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_FLBATrigStatDuration_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_MinStopTrigMovDuration_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_MinStopTrigStatDuration_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_FusionFLBAMaskWrd_str */   (uint16)   65535 ,

 /* k_AEB_FusionPFMaskWrd_str */   (uint16)   65535 ,

 /* k_AEB_FusionLBMaskWrd_str */   (uint16)   65535 ,

 /* k_AEB_FusionHBMaskWrd_str */   (uint16)   65535 ,

 /* k_AEB_FusionFBMaskWrd_str */   (uint16)   65535 ,

 /* k_AEB_FusionVRUFLBAMaskWrd_str */   (uint16)   65535 ,

 /* k_AEB_FusionVRUPFMaskWrd_str */   (uint16)   65535 ,

 /* k_AEB_FusionVRULBMaskWrd_str */   (uint16)   65535 ,

 /* k_AEB_FusionVRUHBMaskWrd_str */   (uint16)   65535 ,

 /* k_AEB_FusionVRUFBMaskWrd_str */   (uint16)   65535 ,

 /* k_AEB_FusionVRUTOIMaskWrd_str */   (uint16)   65535 ,

 /* k_AEB_VehWithIboostNoESP_str */   (boolean)   0 ,

 /* k_AEB_PedEnable_str */   (boolean)   1 ,

 /* k_AEB_IgnoreDecelCheckInPCS_str */   (boolean)   1 ,

 /* k_AEB_DesiredVehHitSpd_str */   (float32)  0.0F,

 /* k_AEB_FullBrkLvl_mps_offset_str */   (float32)  0.0F,

 /* k_AEB_HiBrkLvl_mps_offset_str */   (float32)  0.8F,

 /* k_AEB_Adjust_XOLC_MovementLimit_str */   (float32)  1.33F,

 /* k_AEB_LongBikePFDuration_str */   (float32)  0.3F,

 /* k_AEB_DBSMaxDecel_mps_str */   (float32)  -2.25F,

 /* k_AEB_VRUMinTTC_sec_str */   (float32)  0.3F,

 /* k_AEB_PFNearTrgt_RedFac_str[ 5 ]*/   { (float32)1.0F, (float32)1.0F, (float32)0.75F, (float32)0.75F, (float32)0.75F},

 /* k_AEB_LBNearTrgt_RedFac_str[ 5 ]*/   { (float32)1.0F, (float32)1.0F, (float32)0.75F, (float32)0.75F, (float32)0.75F},

 /* k_AEB_HBNearTrgt_RedFac_str[ 5 ]*/   { (float32)1.0F, (float32)1.0F, (float32)0.85F, (float32)0.85F, (float32)0.85F},

 /* k_AEB_NearTrgt_KneePoints_str[ 5 ]*/   { (uint8)  1 , (uint8)  2 , (uint8)  3 , (uint8)  4 , (uint8)  5 },

 /* k_AEB_enb_veh_sta_check_str */   (boolean)   1 ,

 /* k_AEB_veh_coasted_enb_cont_str */   (uint8)   10 ,

 /* k_AEB_InpathNowReduceFactor_str[ 7 ]*/   { (float32)1.0F, (float32)1.0F, (float32)0.95F, (float32)0.9F, (float32)0.85F, (float32)0.85F, (float32)0.85F},

 /* k_AEB_InpathLaterReduceFactor_str[ 7 ]*/   { (float32)1.0F, (float32)1.0F, (float32)0.95F, (float32)0.9F, (float32)0.85F, (float32)0.85F, (float32)0.85F},

 /* k_AEB_StrAngRtLatEstReduceFac_str[ 7 ]*/   { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_AEB_StrAngRatePoints_str[ 7 ]*/   { (float32)20.0F, (float32)40.0F, (float32)60.0F, (float32)80.0F, (float32)100.0F, (float32)120.0F, (float32)140.0F},

 /* k_AEB_BrkInhibitLowSpdTrhd_str */   (float32)  5.0F,

 /* k_AEB_BrkInhibitHiSpdTrhd_str */   (float32)  5.55F,

 /* k_AEB_HiSpdBrkEngageHdTm_str */   (uint16)   1500 ,

 /* k_AEB_BrkEngagePresFactor_str */   (float32)  0.05F,

 /* k_AEB_HiSpdBrkEngagePresFactor_str */   (float32)  0.06F,

 /* k_AEB_HiSpdBrkEngPosEntryTrhd_str */   (uint8)   10 ,

 /* k_AEB_VRULatEstFunnelExitFac_str */   (float32)  1.15F,

 /* k_AEB_HiSpdBrkEngPosExitTrhd_str */   (uint8)   5 ,

 /* k_AEB_VRUPFVehBehType_str */   (uint8)   15 ,

 /* k_AEB_VRULBVehBehType_str */   (uint8)   15 ,

 /* k_AEB_VRUHBVehBehType_str */   (uint8)   15 ,

 /* k_AEB_VRUPFVBCTTCRedFac_str */   (float32)  0.7F,

 /* k_AEB_VRULBVBCTTCRedFac_str */   (float32)  0.7F,

 /* k_AEB_VRUHBVBCTTCRedFac_str */   (float32)  0.7F,

 /* k_AEB_IgrHiBrkVehBeh_str */   (boolean)   0 ,

 /* k_AEB_VRUHBInhVehBehType_str */   (uint32)   15 ,

 /* k_AEB_VehBehChkLowSpdTrhd_str */   (float32)  6.94F,

 /* k_AEB_VehBehChkHiSpdTrhd_str */   (float32)  8.33F,

 /* k_AEB_StrRateReductionHdTm_str */   (uint16)   2000 ,

 /* k_AEB_StrReductionHdTm_str */   (uint16)   2000 ,

 /* k_AEB_BrkReductionHdTm_str */   (uint16)   3000 ,

 /* k_AEB_GasPdlReductionHdTm_str */   (uint16)   500 ,

 /* k_AEB_GasPdlReductionEntryTrhd_str */   (float32)  80.0F,

 /* k_AEB_GasPdlReductionExitTrhd_str */   (float32)  75.0F,

 /* k_AEB_StrRateReductionEntryTrhd_str */   (float32)  45.0F,

 /* k_AEB_StrRateReductionExitTrhd_str */   (float32)  45.0F,

 /* k_AEB_StrReductionEntryTrhd_str */   (float32)  30.0F,

 /* k_AEB_StrReductionExitTrhd_str */   (float32)  25.0F,

 /* k_AEB_StrRateReductionFactor_str */   (float32)  1.0F,

 /* k_AEB_StrReductionFactor_str */   (float32)  0.7F,

 /* k_AEB_BrkReductionFactor_str */   (float32)  1.0F,

 /* k_AEB_GasPdlReductionFactor_str */   (float32)  1.0F,

 /* k_AEB_BrkReductionSource_str */   (boolean)   1 ,

 /* k_AEB_VRUFLBAVehBehType_str */   (uint8)   15 ,

 /* k_AEB_VRUFLBAVBCTTCRedFac_str */   (float32)  0.7F,

 /* k_AEB_GateMinRangeVRU_str */   (float32)  10.0F,

 /* k_AEB_ClsFstDectVRUIPAOffset_str */   (uint8)   75 ,

 /* k_AEB_RoadCondLowSpdTrhd_str */   (float32)  5.0F,

 /* k_AEB_RoadCondHiSpdTrhd_str */   (float32)  5.0F,

 /* k_AEB_VRUNumThres_str */   (uint8)   1 ,

 /* k_AEB_VRURadarLatErrThres_str */   (float32)  1.7F,

 /* k_AEB_VRUVisionLongErrThres_str[ 9 ]*/   { (float32)1.0F, (float32)1.2F, (float32)1.5F, (float32)2.0F, (float32)2.5F, (float32)3.0F, (float32)3.5F, (float32)4.0F, (float32)4.5F},

 /* k_AEB_VRUXolcChkLowSpdTrhd_str */   (float32)  4.72F,

 /* k_AEB_VRUXolcChkHiSpdTrhd_str */   (float32)  18.05F,

 /* k_AEB_MomErrorThresLong_str[ 7 ]*/   { (float32)0.6F, (float32)0.9F, (float32)1.5F, (float32)2.25F, (float32)2.85F, (float32)3.6F, (float32)6.75F},

 /* k_AEB_VehMomErrorThresLong_str[ 7 ]*/   { (float32)0.6F, (float32)0.9F, (float32)2.0F, (float32)2.7F, (float32)3.0F, (float32)3.6F, (float32)6.75F},

 /* k_AEB_TrtRangRateBrkPoints_str[ 7 ]*/   { (float32)1.5F, (float32)2.78F, (float32)5.55F, (float32)8.33F, (float32)11.11F, (float32)13.38F, (float32)25.0F},

 /* k_AEB_TrtLatRRBrkPoints_str[ 8 ]*/   { (float32)0.0F, (float32)0.3F, (float32)0.6F, (float32)1.0F, (float32)1.5F, (float32)2.2F, (float32)5.5F, (float32)8.33F},

 /* k_AEB_MomErrorThresLat_str[ 8 ]*/   { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_AEB_VRUXolcChkVelGapThres_str */   (float32)  0.25F,

 /* k_AEB_VRUXolcChkLongVelThres_str */   (float32)  1.5F,

 /* k_AEB_DesireStopDistanceLowSpd_str */   (float32)  0.5F,

 /* k_AEB_VRUHiSpdCrossThres_str */   (float32)  7.0F,

 /* k_AEB_VRUHiSpdCrossXolcLimit_str */   (float32)  4.0F,

 /* k_AEB_VRUMinReductionFac_str */   (float32)  0.5F,

 /* k_AEB_VehMinReductionFac_str */   (float32)  0.5F,

 /* k_AEB_VehBasicCheckFailHldTime_str */   (uint16)   1000 ,

 /* k_AEB_VRUBasicCheckFailHldTime_str */   (uint16)   1000 ,

 /* k_AEB_TrgtNumTrhdForVRUCmplx_str */   (uint8)   4 ,

 /* k_AEB_TrgtNumTrhdForVehCmplx_str */   (uint8)   4 ,

 /* k_AEB_VehCmplxReduceFac_str */   (float32)  0.8F,

 /* k_AEB_VRUCmplxReduceFac_str */   (float32)  0.8F,

 /* k_AEB_VRUHBMinReductionFac_str */   (float32)  1.0F,

 /* k_AEB_VehHBMinReductionFac_str */   (float32)  1.0F,

 /* k_AEB_NotChkSpdInFB_str */   (boolean)   1 ,

 /* k_AEB_RE_EndRangeOffset_str */   (float32)  4.0F,

 /* k_AEB_RE_StartRangeOffset_str */   (float32)  -2.0F,

 /* k_AEB_Reduce_GasPdlTrhd_str[ 9 ]*/   { (float32)100.0F, (float32)100.0F, (float32)50.0F, (float32)50.0F, (float32)55.0F, (float32)60.0F, (float32)70.0F, (float32)70.0F, (float32)70.0F},

 /* k_GasPdlReduceDelayTime_str */   (float32)  1.0F,

 /* k_AEB_Use_TTE_In_CCR_str */   (boolean)   1 ,

 /* k_AEB_MinLostRangeVRU_str */   (float32)  4.0F,

 /* k_AEB_MinLostLatPosVRU_str */   (float32)  0.9F,

 /* k_AEB_MinLostRangeVeh_str */   (float32)  4.0F,

 /* k_AEB_MinLostLatPosVeh_str */   (float32)  0.9F,

 /* k_AEB_CloseLostHold_Enabled_str */   (boolean)   0 ,

 /* k_AEB_MinLostLatEstVRU_str */   (float32)  1.0F,

 /* k_AEB_GdRail_RangeOffset_str */   (float32)  0.0F,

 /* k_AEB_NearTrgt_RedFac_str[ 5 ]*/   { (float32)1.0F, (float32)1.0F, (float32)0.85F, (float32)0.85F, (float32)0.85F},

 /* k_AEB_VRUVehBehType_str */   (uint8)   15 ,

 /* k_AEB_VRUVBCTTCRedFac_str */   (float32)  0.7F,

 /* k_AEB_TTBAvgBrkDelay_Full_str */   (float32)  0.02F,

 /* k_AEB_HiToFuBrakingLvlMov_mps_str */   (float32)  -7.84F,

 /* k_AEB_LwBrakingLvl_Factor_str */   (float32)  1.0F,

 /* k_AEB_UseCSMdlToLwBrkRngCal_str */   (boolean)   1 ,

 /* k_AEB_CloseLost_VRUEnableMask_str */   (uint16)   0 ,

 /* k_AEB_DBSStatTimeGap_str[ 15 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F},

 /* k_AEB_DBSMovTimeGap_str[ 15 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F},

 /* k_AEB_DBSUseRangeTrigger_str */   (boolean)   1 ,

 /* k_AEB_TTCAccelBasedCalMode_str */   (boolean)   1 ,

 /* k_AEB_DBSBrakingLvl_Factor_str */   (float32)  1.0F,

 /* k_AEB_LowBrkMaxRangeStat_str */   (float32)  40.0F,

 /* k_AEB_LowBrkMaxRangeMov_str */   (float32)  30.0F,

 /* k_AEB_MovTrgtFlyInMaxRange_str */   (float32)  5.0F,

 /* k_AEB_StatTrgtFlyInMaxRange_str */   (float32)  5.0F,

 /* k_AEB_TrgtFlyInMaxLatPos_str */   (float32)  0.7F,

 /* k_AEB_TrgtFlyInMaxAge_str */   (uint8)   255 ,

 /* k_AEB_FlyInDectIPAOffset_str */   (uint8)   250 ,

 /* k_AEB_DBSBrkMaxStatRange_str */   (float32)  45.0F,

 /* k_AEB_DBSBrkMaxMovRange_str */   (float32)  35.0F,

 /* k_AEB_ExtraInpathAgeCounter_z_str[ 12 ][ 12 ]*/   {
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)3.0F, (float32)4.0F, (float32)5.0F, (float32)5.0F, (float32)6.0F, (float32)6.0F, (float32)7.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)3.0F, (float32)4.0F, (float32)5.0F, (float32)6.0F, (float32)7.0F, (float32)8.0F, (float32)9.0F, (float32)10.0F, (float32)10.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)3.0F, (float32)5.0F, (float32)6.0F, (float32)7.0F, (float32)8.0F, (float32)9.0F, (float32)10.0F, (float32)12.0F, (float32)13.0F, (float32)14.0F},
                            { (float32)0.0F, (float32)3.0F, (float32)5.0F, (float32)6.0F, (float32)8.0F, (float32)9.0F, (float32)11.0F, (float32)12.0F, (float32)14.0F, (float32)15.0F, (float32)17.0F, (float32)19.0F},
                            { (float32)0.0F, (float32)4.0F, (float32)6.0F, (float32)8.0F, (float32)10.0F, (float32)12.0F, (float32)14.0F, (float32)16.0F, (float32)17.0F, (float32)19.0F, (float32)21.0F, (float32)23.0F},
                            { (float32)0.0F, (float32)5.0F, (float32)7.0F, (float32)10.0F, (float32)12.0F, (float32)15.0F, (float32)17.0F, (float32)19.0F, (float32)22.0F, (float32)24.0F, (float32)27.0F, (float32)29.0F},
                            { (float32)0.0F, (float32)6.0F, (float32)9.0F, (float32)12.0F, (float32)15.0F, (float32)17.0F, (float32)20.0F, (float32)23.0F, (float32)26.0F, (float32)29.0F, (float32)32.0F, (float32)35.0F},
                            { (float32)4.0F, (float32)8.0F, (float32)12.0F, (float32)16.0F, (float32)19.0F, (float32)23.0F, (float32)27.0F, (float32)31.0F, (float32)35.0F, (float32)39.0F, (float32)43.0F, (float32)47.0F},
                            { (float32)5.0F, (float32)10.0F, (float32)15.0F, (float32)19.0F, (float32)24.0F, (float32)29.0F, (float32)34.0F, (float32)39.0F, (float32)44.0F, (float32)48.0F, (float32)53.0F, (float32)58.0F},
                            { (float32)7.0F, (float32)14.0F, (float32)20.0F, (float32)27.0F, (float32)34.0F, (float32)41.0F, (float32)47.0F, (float32)54.0F, (float32)61.0F, (float32)68.0F, (float32)75.0F, (float32)81.0F},
                            { (float32)8.0F, (float32)16.0F, (float32)23.0F, (float32)31.0F, (float32)39.0F, (float32)47.0F, (float32)54.0F, (float32)62.0F, (float32)70.0F, (float32)77.0F, (float32)85.0F, (float32)93.0F}},

 /* k_AEB_ExtraInpathAgeCounter_x_str[ 12 ]*/   { (float32)2.75F, (float32)5.5625F, (float32)8.3125F, (float32)11.125F, (float32)13.875F, (float32)16.6875F, (float32)19.4375F, (float32)22.25F, (float32)25.0F, (float32)27.75F, (float32)30.5625F, (float32)33.3125F},

 /* k_AEB_ExtraInpathAgeCounter_y_str[ 12 ]*/   { (float32)0.3F, (float32)0.6F, (float32)0.9F, (float32)1.2F, (float32)1.6F, (float32)2.0F, (float32)2.5F, (float32)3.0F, (float32)4.0F, (float32)5.0F, (float32)7.0F, (float32)8.0F},

 /* k_AEB_LongBikeHB_TTCMax_str */   (float32)  1.8F,

 /* k_AEB_LongBikeLB_TTCMax_str */   (float32)  1.8F,

 /* k_AEB_LongBikePF_TTCMax_str */   (float32)  2.0F,

 /* k_AEB_VRUNoPredictLongVelThres_str */   (float32)  2.0F,

 /* k_AEB_ROCDecelLimit_tbl_y_str[ 5 ]*/   { (float32)-10.0F, (float32)-10.0F, (float32)-10.0F, (float32)-10.0F, (float32)-10.0F},

 /* k_AEB_ROCDecelLimit_tbl_x_str[ 5 ]*/   { (float32)100.0F, (float32)200.0F, (float32)300.0F, (float32)400.0F, (float32)500.0F},

 /* k_AEB_LoadDecelLimit_tbl_y_str[ 6 ]*/   { (float32)-10.0F, (float32)-10.0F, (float32)-10.0F, (float32)-10.0F, (float32)-10.0F, (float32)-10.0F},

 /* k_AEB_LoadDecelLimit_tbl_x_str[ 6 ]*/   { (float32)2000.0F, (float32)3000.0F, (float32)4000.0F, (float32)5000.0F, (float32)6000.0F, (float32)7000.0F},

 /* k_AEB_SpdDecelLimit_tbl_y_str[ 6 ]*/   { (float32)-10.0F, (float32)-10.0F, (float32)-10.0F, (float32)-10.0F, (float32)-10.0F, (float32)-10.0F},

 /* k_AEB_SpdDecelLimit_tbl_x_str[ 6 ]*/   { (float32)27.78F, (float32)30.56F, (float32)33.33F, (float32)36.11F, (float32)38.89F, (float32)41.67F},

 /* k_AEB_VRU_BrkRls_en_str */   (boolean)   1 ,

 /* k_AEB_VRU_SpdReduction_max_str */   (float32)  10.0F,

 /* k_AEB_BrkAct_LimitDecel_en_str */   (boolean)   0 ,

 /* k_AEB_DetBrkAct_AccelMax_str */   (float32)  -0.5F,

 /* k_AEB_PedDecelerateDetectAccel_str */   (float32)  1.8F,

 /* k_AEB_TWDecelerateDetectAccel_str */   (float32)  3.2F,

 /* k_AEB_VRUDecelerateDetectHdTm_str */   (uint16)   500 ,

 /* k_AEB_XolcLaterEntryGate_str */   (float32)  2.0F,

 /* k_AEB_XolcLaterExitGate_str */   (float32)  4.0F,

 /* k_AEB_IniMethodVRUIPAOffset_str */   (uint8)   40 ,

 /* k_AEB_HldRls_AccelPos_str */   (uint8)   15 ,

 /* k_AEB_CCRB_MinActiveAccel_str */   (float32)  -1.5F,

 /* k_AEB_CCRB_ActiveDelay_str[ 12 ]*/   { (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F},

 /* k_AEB_CCRB_ActiveDelaySpdPoints_str[ 12 ]*/   { (float32)2.8F, (float32)5.6F, (float32)8.3F, (float32)11.1F, (float32)13.9F, (float32)16.7F, (float32)19.4F, (float32)22.2F, (float32)25.0F, (float32)27.8F, (float32)30.6F, (float32)33.3F},

 /* k_AEB_CCRB_IgnoreClassCheck_str */   (boolean)   0 ,

 /* k_AEB_CCRB_ActiveHldTime_str */   (uint16)   0 ,

 /* k_AEB_HldAllowMaxVRUSpd_str */   (float32)  2.2F,

 /* k_AEB_HldAllowMaxVehSpd_str */   (float32)  2.0F,

 /* k_AEB_HldAllowMaxVRURange_str */   (float32)  2.1F,

 /* k_AEB_HldAllowMaxVehRange_str */   (float32)  2.0F,

 /* k_AEB_HldEntryIgnObjCheck_str */   (boolean)   0 ,

 /* k_AEB_HldRlsMinVRULatEst_str */   (float32)  1.0F,

 /* k_AEB_HldRlsMinVRULatPos_str */   (float32)  0.9F,

 /* k_AEB_HldRlsMinVehLatEst_str */   (float32)  1.8F,

 /* k_AEB_HldRlsMinVehLatPos_str */   (float32)  1.5F,

 /* k_AEB_HldRlsMinVehSpd_str */   (float32)  2.2F,

 /* k_AEB_HldRlsMinVehRange_str */   (float32)  2.1F,

 /* k_AEB_HldRlsMinVRURange_str */   (float32)  2.2F,

 /* k_AEB_HoldBrkPdlPosThres_str */   (float32)  15.0F,

 /* k_AEB_DrvActInHoldTm_str */   (float32)  500.0F,

 /* k_AEB_UseHoldTrigDly_str */   (boolean)   1 ,

 /* k_AEB_CheckIniMethodMaxAge_str */   (uint8)   20 ,

 /* k_AEB_IBA_DecelCalMod_str */   (boolean)   0 ,

 /* k_AEB_IBA_BypassBrkPosPrs_str */   (boolean)   1 ,

 /* k_AEB_IBA_BypassDecel_str */   (boolean)   1 ,

 /* k_AEB_IgnoreCBLATTBCal_str */   (boolean)   1 ,

 /* k_AEB_HighSpdCrsLatVel_str */   (float32)  3.0F,

 /* k_AEB_VehMaxAllowSpdStep_str */   (float32)  -1.0F,

 /* k_AEB_VehMaxAllowAgeStep_str */   (uint8)   4 ,

 /* k_AEB_IgnVRUInpathAgeChk_str */   (boolean)   0 ,

 /* k_AEB_VehRdrInfoChkFailHldTime_str */   (uint16)   1000 ,

 /* k_AEB_VRUIDChgChkHoldTime_str */   (uint16)   100 ,

 /* k_AEB_VRUHiBrkIgnLatAccEn_str */   (boolean)   0 ,

 /* k_AEB_host_straightly_yaw_thrh_str */   (float32)  5.0F,

 /* k_AEB_VRUHiBrkIgnLatEstEn_str */   (boolean)   1 ,

 /* k_AEB_VRUHiBrkUseRangeTrigger_str */   (boolean)   1 ,

 /* k_AEB_BikeHitSpdDes_mps_str[ 10 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)5.56F, (float32)6.94F, (float32)8.33F},

 /* k_AEB_BikeStatHitSpdDes_mps_str[ 10 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)5.56F, (float32)6.94F, (float32)8.33F},

 /* k_AEB_LongBikeHitSpdDes_mps_str[ 10 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)5.56F, (float32)6.94F, (float32)8.33F},

 /* k_AEB_OCBikeHitSpdDes_mps_str[ 10 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)4.17F, (float32)5.56F, (float32)6.94F, (float32)8.33F},

 /* k_AEB_PedHitSpdDes_mps_str[ 10 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)5.56F, (float32)6.94F, (float32)8.33F},

 /* k_AEB_OCPedHitSpdDes_mps_str[ 10 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)4.17F, (float32)5.56F, (float32)6.94F, (float32)8.33F},

 /* k_AEB_VRUTTBAvgBrkDelay_str */   (float32)  0.15F,

 /* k_AEB_VRUTTBAvgBrkDelay_Full_str */   (float32)  0.1F,

 /* k_AEB_DesHitSpdInputTbl_mps_str[ 10 ]*/   { (float32)5.56F, (float32)6.94F, (float32)8.33F, (float32)9.72F, (float32)11.11F, (float32)12.5F, (float32)13.89F, (float32)15.28F, (float32)16.67F, (float32)18.06F},

 /* k_AEB_VRULowBrkMaxRng_m_str */   (float32)  35.0F,

 /* k_AEB_VRULowBrkMaxTTC_sec_str */   (float32)  1.8F,

 /* k_AEB_VRUPFMaxRng_m_str */   (float32)  50.0F,

 /* k_AEB_VRUPFMaxTTC_sec_str */   (float32)  2.0F,

 /* k_AEB_VRUPFTrigDuration_str[ 15 ]*/   { (float32)0.15F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F},

 /* k_AEB_VRUFLBATrigDuration_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_VRUMinStopTrigDuration_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_BikeLBDuration_sec_str[ 15 ]*/   { (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F},

 /* k_AEB_BikeStatLBDuration_sec_str[ 15 ]*/   { (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F},

 /* k_AEB_LongBikeLBDuration_sec_str[ 15 ]*/   { (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F},

 /* k_AEB_OCBikeLBDuration_sec_str[ 15 ]*/   { (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F},

 /* k_AEB_PedLBDuration_sec_str[ 15 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_AEB_OCPedLBDuration_sec_str[ 15 ]*/   { (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F},

 /* k_AEB_IgnoreEstHitDistChk_str */   (boolean)   0 ,

 /* k_AEB_IgnoreEstYawDistChk_str */   (boolean)   1 ,

 /* k_AEB_IgnoreXolcLaterChk_str */   (boolean)   0 ,

 /* k_AEB_NonCrsPed_MinSpd_mps_str */   (float32)  2.22F,

 /* k_AEB_NonCrsPed_LBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_CrsPed_LBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_StatBike_LBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_CrsBike_LBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_LongBike_LBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_OCPed_LBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_OCBike_LBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_CrsPed_HBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_NonCrsPed_HBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_StatBike_HBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_CrsBike_HBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_LongBike_HBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_OCPed_HBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_OCBike_HBMaxSpd_mps_str */   (float32)  17.778F,

 /* k_AEB_BikeIBADuration_sec_str[ 15 ]*/   { (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F},

 /* k_AEB_BikeStatIBADuration_sec_str[ 15 ]*/   { (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F},

 /* k_AEB_LongBikeIBADuration_sec_str[ 15 ]*/   { (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F},

 /* k_AEB_OCBikeIBADuration_sec_str[ 15 ]*/   { (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F},

 /* k_AEB_PedIBADuration_sec_str[ 15 ]*/   { (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F},

 /* k_AEB_OCPedIBADuration_sec_str[ 15 ]*/   { (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F},

 /* k_AEB_DBSBrkVRUMaxRange_str */   (float32)  30.0F,

 /* k_AEB_DBSVRUMinSpdChkEnbl_str */   (boolean)   1 ,

 /* k_AEB_VRUDBSMaxDecel_mps_str */   (float32)  -1.5F,

 /* k_AEB_DBSVRUMinVehicleSpd_str */   (float32)  3.5F,

 /* k_AEB_IBAVRU_BypassDecel_str */   (boolean)   1 ,

 /* k_AEB_TWLatEstComp_str */   (float32)  0.5F,

 /* k_AEB_VRUHiBrkLvl_mps_offset_str */   (float32)  0.0F,

 /* k_AEB_HiBrkLongBikeRangeOffset_str */   (float32)  0.0F,

 /* k_AEB_HiBrkRefRange_str */   (float32)  1.5F,

 /* k_AEB_VRUHiBrkRefRange_str */   (float32)  1.3F,

 /* k_AEB_SpdReduction_max_str */   (float32)  18.0F,

 /* k_AEB_Veh_BrkRls_en_str */   (boolean)   1 ,

 /* k_AEB_BrkPdlEngageLgAccThres_str */   (float32)  -1.0F,

 /* k_AEB_BrkPosConfirmEn_str */   (boolean)   1 ,

 /* k_AEB_BrkPrsConfirmEn_str */   (boolean)   1 ,

 /* k_AEB_VRULoBrkIgnLatEstEn_str */   (boolean)   1 ,

 /* k_AEB_VRULoBrkHoldXolcThres_str */   (float32)  2.5F,

 /* k_AEB_VRUHiBrkRefRange_IBST_str[ 15 ]*/   { (float32)0.5F, (float32)0.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F},

 /* k_AEB_VRUHiBrkRefRange_ESP_str[ 15 ]*/   { (float32)0.5F, (float32)0.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F},

 /* k_AEB_LongPedLBDuration_sec_str[ 15 ]*/   { (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F, (float32)0.1F},

 /* k_AEB_HiBrkRefRange_IBST_str[ 15 ]*/   { (float32)1.2F, (float32)1.5F, (float32)1.5F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)2.5F, (float32)2.5F, (float32)2.5F, (float32)2.5F, (float32)3.0F, (float32)3.0F},

 /* k_AEB_HiBrkRefRange_ESP_str[ 15 ]*/   { (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.8F, (float32)2.5F, (float32)2.5F},

 /* k_AEB_VruHBCrossingRangeOffset_str[ 15 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_AEB_DesireStopDistance_IBST_str[ 15 ]*/   { (float32)0.7F, (float32)1.1F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F},

 /* k_AEB_DesireStopDistance_ESP_str[ 15 ]*/   { (float32)0.7F, (float32)1.1F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F},

 /* k_AEB_CLHiBrkNeedDecelLimt_IBA_str */   (float32)  -9.81F,

 /* k_AEB_VRUXolcUpLimit_str */   (float32)  6.0F,

 /* k_AEB_VRUXolcDownLimit_str */   (float32)  -7.5F,

 /* k_AEB_TapVehIgnStrOvrdMask_str */   (uint8)   2 ,

 /* k_AEB_TapVRUIgnStrOvrdMask_str */   (uint8)   6 ,

 /* k_AEB_IgnDrvBehRedToFunnel_str */   (boolean)   1 ,

 /* k_AEB_DrvOvrdBasePreFac_FLBA_str */   (float32)  0.1F,

 /* k_AEB_DrvOvrdBasePosFac_FLBA_str */   (float32)  0.1F,

 /* k_AEB_DrvOvrdBasePreFac_PF_str */   (float32)  0.1F,

 /* k_AEB_DrvOvrdBasePosFac_PF_str */   (float32)  0.1F,

 /* k_AEB_DrvOvrdBasePreFac_LB_str */   (float32)  0.8F,

 /* k_AEB_DrvOvrdBasePosFac_LB_str */   (float32)  0.4F,

 /* k_AEB_DrvOvrdBasePreFac_HB_str */   (float32)  0.8F,

 /* k_AEB_DrvOvrdBasePosFac_HB_str */   (float32)  0.8F,

 /* k_AEB_DrvOvrdBasePreFac_FB_str */   (float32)  0.9F,

 /* k_AEB_DrvOvrdBasePosFac_FB_str */   (float32)  0.9F,

 /* k_AEB_HiSpdBrkEngPresEnblTm_str */   (float32)  0.5F,

 /* k_AEB_HiSpdBrkEngPosEnTime_str */   (float32)  0.5F,

 /* k_AEB_GasRateEngHdTm_str */   (uint16)   3000 ,

 /* k_AEB_HiSpdGasRateEngHdTm_str */   (uint16)   3000 ,

 /* k_AEB_GasRateCntThres_str */   (uint8)   15 ,

 /* k_AEB_HiSpdGasRateCntThres_str */   (uint8)   15 ,

 /* k_AEB_DrvEngUseTTCReduc_IBA_str */   (boolean)   1 ,

 /* k_AEB_BrkPdlEngageMode_str */   (boolean)   1 ,

 /* k_AEB_BrkEngStatusEnTime_str */   (float32)  0.2F,

 /* k_AEB_BrkResetHaloTime_ms_str */   (uint16)   60 ,

 /* k_AEB_IgnoreBrkResetChk_str */   (boolean)   1 ,

 /* k_AEB_IBA_UseBrkPedal_str */   (boolean)   0 ,

 /* k_AEB_EnBrkResetChk_str */   (boolean)   0 ,

 /* k_AEB_LeadVel_OCDead_str */   (float32)  0.0F,

 /* k_AEB_IBA_PermitAccelGap_str */   (float32)  -1.0F,

 /* k_AEB_BrkPosIgnore_str */   (boolean)   0 ,

 /* k_AEB_BrkPrsIgnore_str */   (boolean)   0 ,

 /* k_AEB_BikeHiConfMaxHeadError_str */   (float32)  30.0F,

 /* k_AEB_HostSpdEstUsed_str */   (boolean)   1 ,

 /* k_AEB_MovHiBrkRefRange_IBST_str[ 15 ]*/   { (float32)1.7F, (float32)1.7F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)2.5F, (float32)2.5F, (float32)2.5F, (float32)2.5F, (float32)3.0F, (float32)3.0F, (float32)3.0F, (float32)3.0F, (float32)3.0F, (float32)3.0F},

 /* k_AEB_MovHiBrkRefRange_ESP_str[ 15 ]*/   { (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.8F, (float32)2.5F, (float32)2.5F},

 /* k_AEB_CrossHiBrkRefRange_ESP_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)1.0F, (float32)1.0F, (float32)1.2F, (float32)1.2F, (float32)1.3F, (float32)1.3F, (float32)1.3F, (float32)1.3F, (float32)1.5F, (float32)2.5F, (float32)2.5F},

 /* k_AEB_Brk_Reduc_ToFunnel_str */   (float32)  0.6F,

 /* k_AEB_Spd_Reduc_ToFunnel_str[ 9 ]*/   { (float32)0.7F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_AEB_NearTrgtReducHdTm_str */   (uint16)   500 ,

 /* k_AEB_GateMinLatPosVRU_str */   (float32)  1.0F,

 /* k_AEB_VehMinMatchConf_str */   (uint8)   5 ,

 /* k_AEB_BigXolc_RedFac_str[ 9 ]*/   { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_AEB_VRURangeBrkPoints_str[ 9 ]*/   { (float32)0.1F, (float32)5.0F, (float32)10.0F, (float32)15.0F, (float32)20.0F, (float32)30.0F, (float32)40.0F, (float32)50.0F, (float32)60.0F},

 /* k_AEB_IgnoreVRUFusChk_str */   (boolean)   1 ,

 /* k_AEB_HostStraightlyYawThrh_str */   (float32)  0.85F,

 /* k_AEB_VRUHB_UseDefaultOfst_str */   (boolean)   1 ,

 /* k_AEB_VRUHB_LongBikeOffset_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_VRUHB_CrossBikeOffset_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_VRUHB_StatBikeOffset_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_VRUHB_LongPedOffset_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_VRUHB_CrossPedOffset_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_VRUHB_StatPedOffset_str[ 15 ]*/   { (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F, (float32)0.8F},

 /* k_AEB_UseLgSfJAVehCusSet_str */   (boolean)   0 ,

 /* k_AEB_UseLgSfJAPedCusSet_str */   (boolean)   0 ,

 /* k_AEB_PedVisLatEstChkDisable_str */   (boolean)   0 ,

 /* k_AEB_PedOCPedExitThres_str */   (float32)  -1.0F,

 /* k_AEB_PedOCCrossingAllow_str */   (boolean)   0 ,

 /* k_AEB_PedIgnoreVisPlauCheck_str */   (boolean)   1 ,

 /* k_AEB_PedUseVisionTTC_str */   (boolean)   0 ,

 /* k_AEB_DisblAEBOCBicycle_str */   (boolean)   1 ,

 /* k_AEB_DisblAEBBicycle_str */   (boolean)   0 ,

 /* k_AEB_DisblAEBPed_str */   (boolean)   0 ,

 /* k_AEB_DisblAEBOCPed_str */   (boolean)   1 ,

 /* k_AEB_UseRRFunelInput_str */   (boolean)   1 ,

 /* k_AEB_EnableYawRateRedc_str */   (boolean)   0 ,

 /* k_AEB_IgnoreLongVelForCrsScene_str */   (boolean)   1 ,

 /* k_AEB_UseTapTTCForVRU_str */   (boolean)   1 ,

 /* k_AEB_IgnoreVRUXolcChk_str */   (boolean)   0 ,

 /* k_AEB_IgnoreVehFusionCheck_str */   (boolean)   1 ,

 /* k_AEB_IgnoreVehRadarCheck_str */   (boolean)   0 ,

 /* k_AEB_IgnoreVRUBasicCheck_str */   (boolean)   1 ,

 /* k_AEB_UseTapThresFunc_str */   (boolean)   1 ,

 /* k_AEB_mi_VisLowConf_str */   (uint8)   0 ,

 /* k_AEB_AllowFCWOCBicycle_str */   (boolean)   0 ,

 /* k_AEB_DisblFCWBicycle_str */   (boolean)   0 ,

 /* k_AEB_AllowFCWOCPed_str */   (boolean)   0 ,

 /* k_AEB_DisblFCWPed_str */   (boolean)   0 ,

 /* k_AEB_ABALevel_str */   (uint8)   2 ,

 /* k_AEB_AWBLevel_str */   (uint8)   2 ,

 /* k_AEB_NotUseBrakeTypeFlag_str */   (boolean)   1 ,

 /* k_AEB_UseShadowMode_str */   (boolean)   0 ,

 /* k_AEB_IgnoreFusVisCheck_str */   (boolean)   1 ,

 /* k_AEB_AWBAutoBrkTyp_Mask_str */   (uint8)   11 ,

 /* k_AEB_MaxTime_ms_AWBReq_str */   (uint16)   500 ,

 /* k_AEB_DRTVisLongErrThres_str[ 9 ]*/   { (float32)1.0F, (float32)2.0F, (float32)2.5F, (float32)3.0F, (float32)3.5F, (float32)4.0F, (float32)4.5F, (float32)5.0F, (float32)6.0F},

 /* k_AEB_DRTVisLongChkDelayTime_str */   (uint32)   200 ,

 /* k_AEB_FullLatVel_str */   (float32)  0.5F,

 /* k_AEB_NegligibleLatVel_str */   (float32)  0.25F,

 /* k_AEB_YawRateIgnoreLatVel_str */   (float32)  0.01745F,

 /* k_AEB_LatVelMinStepsize_str */   (float32)  0.15F,

 /* k_AEB_LongVelMinStepsize_str */   (float32)  0.06F,

 /* k_AEB_UseVelTrackAngle_str */   (boolean)   1 ,

 /* k_AEB_UseLatVelforRR_str */   (boolean)   1 ,

 /* k_AEB_UseHostSpdBsdRR_str */   (boolean)   1 ,

 /* k_AEB_LatVelVisionConfirmIgnr_str */   (boolean)   1 ,

 /* k_AEB_Default_Time_Offset_str */   (float32)  0.1F,

 /* k_AEB_VehRangeBrkPoints_str[ 9 ]*/   { (float32)0.0F, (float32)3.0F, (float32)5.0F, (float32)10.0F, (float32)15.0F, (float32)20.0F, (float32)25.0F, (float32)40.0F, (float32)50.0F},

 /* k_AEB_VehRangRateBrkPoints_str[ 7 ]*/   { (float32)1.5F, (float32)2.78F, (float32)5.55F, (float32)8.33F, (float32)11.11F, (float32)13.38F, (float32)20.0F},

 /* k_AEB_VehLongRangeErrorThres_str[ 7 ][ 9 ]*/   {
                            { (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F},
                            { (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F},
                            { (float32)8.0F, (float32)8.0F, (float32)6.0F, (float32)6.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F},
                            { (float32)8.0F, (float32)8.0F, (float32)8.0F, (float32)6.0F, (float32)6.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F},
                            { (float32)10.0F, (float32)10.0F, (float32)10.0F, (float32)8.0F, (float32)8.0F, (float32)8.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F},
                            { (float32)12.0F, (float32)12.0F, (float32)12.0F, (float32)12.0F, (float32)10.0F, (float32)10.0F, (float32)10.0F, (float32)100.0F, (float32)100.0F},
                            { (float32)16.0F, (float32)16.0F, (float32)16.0F, (float32)16.0F, (float32)12.0F, (float32)12.0F, (float32)12.0F, (float32)100.0F, (float32)100.0F}},

 /* k_AEB_VehLatRangeErrorThres_str[ 8 ]*/   { (float32)0.3F, (float32)0.45F, (float32)0.6F, (float32)0.6F, (float32)0.8F, (float32)0.9F, (float32)1.2F, (float32)1.6F},

 /* k_AEB_TgtMomErrorThresLong_str[ 7 ]*/   { (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F},

 /* k_AEB_TgtMomErrorThresLat_str[ 8 ]*/   { (float32)0.08F, (float32)0.12F, (float32)0.16F, (float32)0.16F, (float32)0.24F, (float32)0.36F, (float32)0.8F, (float32)1.0F},

 /* k_AEB_VehLatRRBrkPoints_str[ 8 ]*/   { (float32)0.0F, (float32)0.3F, (float32)0.6F, (float32)1.0F, (float32)1.5F, (float32)2.2F, (float32)5.5F, (float32)8.33F},

 /* k_AEB_VehAccuErrorChkOnLong_str */   (boolean)   1 ,

 /* k_AEB_VehAccuErrorChkOnLat_str */   (boolean)   1 ,

 /* k_AEB_VehMomeErrorChkOnLong_str */   (boolean)   1 ,

 /* k_AEB_VehMomeErrorChkOnLat_str */   (boolean)   1 ,

 /* k_AEB_VehBaseChkFailEnblTime_str */   (uint32)   50 ,

 /* k_AEB_VehBaseChkFailHoldTime_str */   (uint32)   10000 ,

 /* k_AEB_VehErrorAccuPerdLong_str */   (uint16)   32 ,

 /* k_AEB_VehErrorAccuPerdLat_str */   (uint16)   10 ,

 /* k_AEB_VehLongRangeChkEnbl_str */   (boolean)   1 ,

 /* k_AEB_VehLatRangeChkEnbl_str */   (boolean)   1 ,

 /* k_AEB_VehFusionMinAgeCount_str */   (uint8)   20 ,

 /* k_AEB_VehMulTrklMinAgeCount_str */   (uint8)   60 ,

 /* k_AEB_VehSingleTrkMinAgeCount_str */   (uint8)   80 ,

 /* k_AEB_VehVisionMinAgeCount_str */   (uint8)   250 ,

 /* k_AEB_VehMinAgeCount_str */   (uint8)   250 ,

 /* k_AEB_VehDetStatus_str */   (uint8)   3 ,

 /* k_AEB_VehIgnoreDetProfile_str */   (boolean)   1 ,

 /* k_AEB_VehIgnoreDetProfileLatPos_str */   (float32)  0.7F,

 /* k_AEB_VehProfileChk_HdTm_str */   (uint16)   500 ,

 /* k_AEB_VehRadarIDChk_HdTm_str */   (uint16)   400 ,

 /* k_AEB_VehRadarIDChkRangeThres_str[ 9 ]*/   { (float32)12.0F, (float32)12.0F, (float32)12.6F, (float32)16.5F, (float32)20.7F, (float32)24.9F, (float32)33.3F, (float32)41.4F, (float32)50.1F},

 /* k_AEB_VehRangeRate_BrkPoints_str[ 9 ]*/   { (float32)1.5F, (float32)2.8F, (float32)4.2F, (float32)5.5F, (float32)6.9F, (float32)8.3F, (float32)11.1F, (float32)13.8F, (float32)16.7F},

 /* k_AEB_VehRadarIDChk_str */   (boolean)   1 ,

 /* k_AEB_VehRAIDChk_MinLongAccel_str */   (float32)  -3.92F,

 /* k_AEB_IgnoreAEBPedConfCheck_str */   (boolean)   1 ,

 /* k_AEB_IgnoreConfCheck_str */   (boolean)   1 ,

 /* k_AEB_IgnoreInPathAgeCheck_str */   (boolean)   1 ,

 /* k_AEB_IgnoreAebInhibit_str */   (uint8)   1 ,

 /* k_AEB_IgnoreAebFault_str */   (uint16)   1 ,

 /* k_AEB_Vehicle_Mass_str */   (uint16)   2150 ,

 /* k_AEB_EPB_Present_str */   (boolean)   1 ,

 /* k_AEB_EspRespTime_str */   (float32)  0.13F,

 /* k_AEB_EspRespMaxJerk_str */   (float32)  -20.0F,

 /* k_AEB_ESPRespomseTime_str[ 8 ]*/   { (float32)0.12F, (float32)0.12F, (float32)0.12F, (float32)0.12F, (float32)0.12F, (float32)0.12F, (float32)0.12F, (float32)0.12F},

 /* k_AEB_ESPTmSpdBrkPoints_str[ 8 ]*/   { (float32)2.78F, (float32)5.55F, (float32)8.33F, (float32)11.11F, (float32)13.38F, (float32)16.67F, (float32)19.44F, (float32)22.22F},

 /* k_AEB_ESPDecelDiffBrkPoints_str[ 6 ]*/   { (float32)-10.0F, (float32)-8.0F, (float32)-6.0F, (float32)-4.0F, (float32)-2.0F, (float32)0.0F},

 /* k_AEB_ESPDelayTime_str[ 6 ]*/   { (float32)0.45F, (float32)0.35F, (float32)0.25F, (float32)0.15F, (float32)0.05F, (float32)0.0F},

 /* k_AEB_UseOriginRangeCal_str */   (boolean)   0 ,

 /* k_AEB_ESPRespTmHB2FB_str */   (float32)  0.1F,

 /* k_AEB_ESPDeftResponseTime_str */   (float32)  0.12F,

 /* k_AEB_VRURlsMinXolc_str */   (float32)  0.4F,

 /* k_AEB_VehIgnCstMask_str */   (uint16)   0 ,

 /* k_AEB_PedInterestChk_str */   (uint16)   0 ,

 /* k_AEB_VehHighestConf_str */   (uint8)   3 ,

 /* k_AEB_VehHiConf_str */   (uint8)   2 ,

 /* k_AEB_GateTOIAngle_Arr_str[ 3 ]*/   { (float32)70.0F, (float32)30.0F, (float32)30.0F},

 /* k_AEB_GateTOIPosi_x_str[ 3 ]*/   { (float32)0.5F, (float32)2.0F, (float32)10.0F},

 /* k_Cal_LgSafe_minor_version_str */   (uint8)   0 ,

 /* k_Cal_LgSafe_major_version_str */   (uint8)   0 ,

};
#define LongSafe_STOP_SEC_CAL_UNSPECIFIED
/*
*| longsafe_cal.LongSafe_Cal_DF_V {
*|  :is_calconst;
*|  .k_AEB_FLBA_Enabled_str {
*|  :description = "Vehicle Configuration data - FLBA feature is enabled when this is TRUE.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBS_Enabled_str {
*|  :description = "Vehicle Configuration data - IBA feature is enabled when this is TRUE.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseTestSceneFlag_str {
*|  :description = "if UseTestSceneFlag";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseSpecialSceneFullBrk_str {
*|  :description = "";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_MinStop_Enabled_str {
*|  :description = "Vehicle Configuration data - Min Stop feature is enabled when this is TRUE.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_AccelMinGasPedPosInhbt_str {
*|  :description = "Minimum gap pedal position below which the Acceleration Inhibit will not be allowed";
*|  :units = "percent";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_AccelTrhdMov_str {
*|  :description = "Acceleration Thereshold used to determine if the host is accelerating while approaching a Moveable O\
*|  bject";
*|  :units = "m/sec^2";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_AccelTrhdStat_str {
*|  :description = "Acceleration Thereshold used to determine if the host is accelerating while approaching a Stationary\
*|   Object";
*|  :units = "m/sec^2";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_SpecScenHostSpdMax_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_SpecScenFBHostHiSpd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_SpecScenFBHostMidSpd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_SpecScenFBHostLowSpd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_SpecScenFBThresInHiSpd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_SpecScenFBThresInMidSpd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_SpecScenFBThresInLowSpd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_SpecScenFBThresInElseSpd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_SpecScenHostSpdMin_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_AlgInternalLpTm_ms_str {
*|  :description = "Radar Data Cycle Time";
*|  :units = "counts";
*|  :type = caltype.uint16_1_32767_CT;
*|  }
*|  .k_AEB_BrkHdTmAfterTrig_ms_str {
*|  :description = "";
*|  :units = "counts";
*|  :type = caltype.single_1_32767_CT;
*|  }
*|  .k_AEB_Enable_str {
*|  :description = "AEB feature is enabled when this is TRUE.";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseHoldTrigAfterStand_str {
*|  :description = "Flag if use hold trig after stand till.";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_AlgLpTm_sec_str {
*|  :description = "Radar Data Cycle Time In Seconds";
*|  :units = "Sec";
*|  :type = caltype.single_0p001_25p5_CT;
*|  }
*|  .k_AEB_BrkingRampToHiStep_mps_str {
*|  :description = "Deceleration step size used to reach needed high braking level.";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_BrkingRampToLoStep_mps_str {
*|  :description = "Deceleration step size used to reach needed braking level.";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_BrakingRampToZeroStep_str {
*|  :description = "Deceleration step size used to return braking level to 0";
*|  :units = "m/sec^2";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_DecelTrhdMov_str {
*|  :description = "Deceleration Thereshold used to determine if brakes are applied When approaching a Moveable Object";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_DecelTrhdStat_str {
*|  :description = "DecelerationThereshold used to determine if brakes are applied when approaching a stationary object";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_DrvAppRefTmForAdj_str {
*|  :description = "Maximum adjustment time subtracted from TTE_Max";
*|  :units = "Sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_DrvOvrdBasePressure_str {
*|  :description = "Driver Applied Brk Pedal Pressure above which all CIB braking is released leaving the Driver in cont\
*|  rol";
*|  :units = "kPa";
*|  :type = caltype.single_0_50025_CT;
*|  }
*|  .k_AEB_RdrTimeStep_sec_str {
*|  :description = "ESR Cycle Time in seconds";
*|  :units = "Sec";
*|  :type = caltype.single_0p001_25p5_CT;
*|  }
*|  .k_AEB_GasPedalMargin_str {
*|  :description = "When driver further press this amount of accelerator pdeal postion compared to AEB onset gas pedal p\
*|  ostion. Accelerator pedal overide will be triggered";
*|  :units = "percent";
*|  :type = caltype.uint8_0_100_CT;
*|  }
*|  .k_AEB_GasPedalPositionMax_str {
*|  :description = "Gas pedal position above which AEB auto braking will be released";
*|  :units = "percent";
*|  :type = caltype.uint8_0_100_CT;
*|  }
*|  .k_AEB_GasPedalOvrdTm_ms_str {
*|  :description = "Minimal duration of accelerator overide";
*|  :units = "counts";
*|  :type = caltype.uint16_0_32767_CT;
*|  }
*|  .k_AEB_GateClosingRngRtTrhd_str {
*|  :description = "Range Rate Threshold to determine Closing RR condition";
*|  :units = "m/sec";
*|  :type = caltype.single_m82_82_CT;
*|  }
*|  .k_AEB_ZeroSpdTrhd1_str {
*|  :description = "";
*|  :units = "m/sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_ZeroSpdTrhd2_str {
*|  :description = "";
*|  :units = "m/sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_GateMaxObjAngle_str {
*|  :description = "Maximum angle allowed for Objects";
*|  :units = "deg";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_GateMaxObjOffset_str {
*|  :description = "Maximum lateral offset used for Offset calculations";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_GateMaxOpeningRngRt_str {
*|  :description = "Maximum range rate used to determine if the target is moving away. Above this level deployment is no\
*|  t allowed.";
*|  :units = "m/sec";
*|  :type = caltype.single_m81p92_81p91_CT;
*|  }
*|  .k_AEB_GateMaxRangeMov_str {
*|  :description = "Maximum range beyond which the is no discrimination for Moveable";
*|  :units = "m";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AEB_GateMaxRangeStat_str {
*|  :description = "Maximum range beyond which the is no discrimination for stationary";
*|  :units = "m";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AEB_GateMaxTOIAngle_str {
*|  :description = "Max target of interest angle";
*|  :units = "deg/sec";
*|  :type = caltype.single_0_60_CT;
*|  }
*|  .k_AEB_GateMinROC_str {
*|  :description = "Min Radius of Curvature below which no deployments";
*|  :units = "m";
*|  :type = caltype.uint16_0_8191_CT;
*|  }
*|  .k_AEB_UseInFunnelChk_str {
*|  :description = "";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HiBrkHdTm_str {
*|  :description = "Time perioe for which a vehicle stopped by a CIB activations will hold the brakes on after a stop is\
*|   reached as indicated by the '297_3' message";
*|  :units = "Sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_HiBrkLdTmStat_sec_str {
*|  :description = "Time Added to TTE_Min to allow High Brake deployment for Stationary";
*|  :units = "sec";
*|  :type = caltype.array_15_k_AEB_HiBrkLdTmStat_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_HiBrakeLeadTimeStatMps;
*|  }
*|  .k_AEB_AEBEgoSpdKneePoints_str {
*|  :description = "Input = Host Speed Mps";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_MEAEBEgoSpdKneePoints_str {
*|  :description = "Input = Host Speed Mps for vision only AEB system";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_HiBrkLdTmMov_sec_str {
*|  :description = "Time Added to TTE_Min to allow High Brake deployment for Moveable";
*|  :units = "sec";
*|  :type = caltype.array_15_k_AEB_HiBrkLdTmMov_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_HiBrakeLeadTimeMovMps;
*|  }
*|  .k_AEB_VehHiBrkLowPersistanceCnt_str {
*|  :description = "C-Code Minimum length of time low brakes are active prior to allowing high: 1 Cnt = 20 ms";
*|  :units = "Counts";
*|  :type = caltype.uint8_0_254_CT;
*|  }
*|  .k_AEB_VRUHiBrkLowPersistanceCnt_str {
*|  :description = "C-Code Minimum length of time low brakes are active prior to allowing high: 1 Cnt = 20 ms";
*|  :units = "Counts";
*|  :type = caltype.uint8_0_254_CT;
*|  }
*|  .k_AEB_HiBrkACCStrongBrkCnt_str {
*|  :description = "C-Code Minimum length of time ACC Strong brakes are active prior to allowing high: 1 Cnt = 50 ms";
*|  :units = "Counts";
*|  :type = caltype.uint8_0_254_CT;
*|  }
*|  .k_AEB_HiBrkMaxSpdMov_str {
*|  :description = "Max speed above which high brakes shall not be commanded";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_HiBrkMaxSpdStat_str {
*|  :description = "Max speed above which high brakes shall not be commanded";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_HiBrkMinRlsTm_str {
*|  :description = "Time below which high brakes willl not be released";
*|  :units = "sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_HiBrakingLvlMov_mps_str {
*|  :description = "High brake deceleration value applied to moveable brake objects";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_HiBrakingLvlStat_mps_str {
*|  :description = "High brake deceleration value applied to stationary brake objects";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_LittleBrakeDecel_mps_str {
*|  :description = "Little brake deceleration value applied to stationary brake objects";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_HiBrkMinSpdChkEnbl_str {
*|  :description = "Enable Minimum Host speed check for High Brake Activation";
*|  :units = "None";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HoldDrvActionWithBrk_str {
*|  :description = "Enable if consider for driver brake action when hold";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSAbsMaxDecel_str {
*|  :description = "Maximum Decel applied for IBA";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_DBSLdTmMov_sec_str {
*|  :description = "Time added to TTE_Max to create the IBA TTC threshold";
*|  :units = "Sec";
*|  :type = caltype.array_15_k_AEB_DBSLdTmMov_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_IBALeadTimeMoveMps;
*|  }
*|  .k_AEB_DBSLdTmStat_sec_str {
*|  :description = "Time added to TTE_Min to create the IBA TTC threshold";
*|  :units = "Sec";
*|  :type = caltype.array_15_k_AEB_DBSLdTmStat_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_IBALeadTimeStatMps;
*|  }
*|  .k_AEB_WrapperLpTm_ms_str {
*|  :description = "CIB to Vehicle interface loop time";
*|  :units = "counts";
*|  :type = caltype.uint16_0_32767_CT;
*|  }
*|  .k_AEB_LCHighFactor_str {
*|  :description = "Multiplcation factor used to set the High long term to short term difference threshold relative to t\
*|  he low threshold";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_LCHdTm_str {
*|  :description = "Time limit to hold lane chang flag active after it is first set to true";
*|  :units = "Sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_LCLongTermSteerGain_str {
*|  :description = "Gain value for LP Filter for the long term steering angle to Replace the Time constant Calibration";
*|  :units = "None";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_LCSpdIntercept_str {
*|  :description = "y intercept of line that determines the long term to short term difference threshold as a function o\
*|  f speed";
*|  :units = "Degrees";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_LCSpdSlope_str {
*|  :description = "Slope of line that determines the long term to short term difference threshold as a function of spee\
*|  d";
*|  :units = "Deg / speed";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_LwBrkLateralLimit_str {
*|  :description = "Minimum Lateral Movement derived from Track Lateral Rate and TTC";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_LwBrkLdTmMov_sec_str {
*|  :description = "Time Added to TTE_Min/Max to allow Low Brake deployment for Moveable-:::CIB_RangeRate_Filtered64_V:::";
*|  :units = "sec";
*|  :type = caltype.array_15_k_AEB_LwBrkLdTmMov_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_LowBrakeLeadTimeMoveMps;
*|  }
*|  .k_AEB_LwBrkLdTmStat_sec_str {
*|  :description = "Time Added to TTE_Min/Max to allow Low Brake deployment for stationary";
*|  :units = "sec";
*|  :type = caltype.array_15_k_AEB_LwBrkLdTmStat_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_LowBrakeLeadTimeStatMps;
*|  }
*|  .k_AEB_LwBrkMaxSpdMov_str {
*|  :description = "Max speed above which low brakes shall not be commanded";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_LwBrkMaxSpdStat_str {
*|  :description = "Max speed above which low brakes shall not be commanded";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_LwBrkMinSpdChkEnbl_str {
*|  :description = "Enable Minimum Host speed check for Low Brake Activation";
*|  :units = "None";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_LwBrkPersistanceCnt_str {
*|  :description = "Minimum low brake object persistance to allow deployment: 1 Cnt -= 50 ms";
*|  :units = "Counts";
*|  :type = caltype.uint8_0_254_CT;
*|  }
*|  .k_AEB_LwBrakingLvl_mps_str {
*|  :description = "AEB low braking deceleration value";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_LwBrakingThrshACCBrk_str {
*|  :description = "Threshold of ACC braking active that inhibits CIB low braking";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_MinClosingSpd_str {
*|  :description = "Minimum Closing Speed for PCS Discrimination";
*|  :units = "m/sec";
*|  :type = caltype.single_m82_82_CT;
*|  }
*|  .k_AEB_MinVehicleSpd_str {
*|  :description = "Minimum Speed for PCS Discrimination";
*|  :units = "m/sec";
*|  :type = caltype.single_0_127p5_CT;
*|  }
*|  .k_AEB_MovingAwayNoiseLvlNeg_str {
*|  :description = "Noise Level used to determine moving away, toward, or neutral";
*|  :units = "m";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_MovingAwayNoiseLvlPos_str {
*|  :description = "Noise Level used to determine moving away, toward, or neutral";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_PathFarWidthEntryGate_str {
*|  :description = "1/2 Path Width for in-path position for entry at far range";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_PathFarWidthExitGate_str {
*|  :description = "1/2 Path Width for in-path position for exit at far range";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_PathHitDistanceEntryGate_str {
*|  :description = "1/2 Path Width for est. Hit distance to enter in-path now and later gate";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_PathHitDistanceExitGate_str {
*|  :description = "1/2 Path Width for est. Hit distance to exit in-path now and later gate";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_PathNearFarTransitRng_str {
*|  :description = "Range boundary between near and far range";
*|  :units = "m";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AEB_PathNearWidthEntryGate_str {
*|  :description = "1/2 Path Width for in-path position for entry at close range";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_PathNearWidthExitGate_str {
*|  :description = "1/2 Path Width for in-path position for exit at close range";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_PathYawDistanceEntryGate_str {
*|  :description = "1/2 Path Width for est. Yaw distance to enter in-path now and later gate";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_PathYawDistanceExitGate_str {
*|  :description = "1/2 Path Width for est. Yaw distance to exit in-path now and later gate";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_DBSPathYawDistExitGate_str {
*|  :description = "IBA 1/2 Path Width for est. Yaw distance to exit in-path now and later gate";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_PrefillLateralLimit_str {
*|  :description = "Minimum Lateral Movement derived from Track Lateral Rate and TTC";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_PrefillLdTmMov_sec_str {
*|  :description = "Time Added to TTE_Max to allow Pre-fill For Moveable-:::CIB_RangeRate_Filtered64_V:::";
*|  :units = "Sec";
*|  :type = caltype.array_15_k_AEB_PrefillLdTmMov_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_PrefillLeadTimeMoveMps;
*|  }
*|  .k_AEB_PrefillLdTmStat_sec_str {
*|  :description = "Time Added to TTE_Max to allow Pre-fill For Stationary";
*|  :units = "Sec";
*|  :type = caltype.array_15_k_AEB_PrefillLdTmStat_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_PrefillLeadTimeStatMps;
*|  }
*|  .k_AEB_PrefillMinSpdChkEnbl_str {
*|  :description = "Enable Minimum Host speed check forPrefill Activation";
*|  :units = "None";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_ReferLowToTTEMinStat_str {
*|  :description = "Flag that allows low brakes to be referenced to TTEMin for stationary";
*|  :units = "enum";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseTwoLevelDecel_str {
*|  :description = "";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_ReleaseOvrdTime_ms_str {
*|  :description = "Hold Brake release command period";
*|  :units = "counts";
*|  :type = caltype.uint16_0_32767_CT;
*|  }
*|  .k_AEB_SteeringInhibitHaloTime_str {
*|  :description = "Minimum Brake pedal Rate Halo Time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_SteeringAngleRtTrhd_str {
*|  :description = "angle Rate threshold to determine active maneuvering";
*|  :units = "Deg/sec";
*|  :type = caltype.single_0_2047_CT;
*|  }
*|  .k_AEB_OvrdSteeringRateMax_str {
*|  :description = "Maximum Steering rate above which a steering override will be commanded";
*|  :units = "Deg/sec";
*|  :type = caltype.single_0_2047_CT;
*|  }
*|  .k_AEB_JAOvrdSteeringRateMax_str {
*|  :description = "Maximum Steering rate above which a steering override will be commanded";
*|  :units = "Deg/sec";
*|  :type = caltype.uint16_0_2047_CT;
*|  }
*|  .k_AEB_JAOvrdYawRateMax_str {
*|  :description = "Yaw rate of change threshold above which the steering override will become active";
*|  :units = "deg/sec^2";
*|  :type = caltype.single_0_2560_CT;
*|  }
*|  .k_AEB_SteeringRtOvrdGain_str {
*|  :description = "Gain value for LP Filter for the Steering Rate Override to Replace the Time constant Calibration";
*|  :units = "None";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_TTBAccBrkDelay_str {
*|  :description = "Average brake system delay when ACC is active and Decelaring the host";
*|  :units = "Sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_TTBAvgBrkDelay_str {
*|  :description = "Average brake system delay";
*|  :units = "Sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_TTBMaxSpd_str {
*|  :description = "Maximum Speed above which the speed used to calculate TTB will be clipped to this level";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_TTCIntegAccelEntry_str {
*|  :description = "Acceleration level above which the TTC integration calculation will be used";
*|  :units = "m/sec^2";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_TTCIntegAccelExit_str {
*|  :description = "Acceleration level below which the TTC integration calculation may be used";
*|  :units = "m/sec^2";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_TTCIntegDecelEntry_str {
*|  :description = "Deceleration level below which TTC integration will be used";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_TTCIntegDecelExit_str {
*|  :description = "deceleration level above which the TTC integration calculation if running will stop and the R/RR cal\
*|  culaiton used";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_TTCIntegMaxSteps_str {
*|  :description = "Maximum counts for which TTC integration will be allowed";
*|  :units = "sec";
*|  :type = caltype.uint8_1_254_CT;
*|  }
*|  .k_AEB_TTCIntegMaxTime_str {
*|  :description = "Maximum time above which TTC integration will not be used";
*|  :units = "sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_TTCIntegTimeStep_str {
*|  :description = "Time Step used for TTC integration";
*|  :units = "Sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_TTCLowerClip_x_str {
*|  :description = "Lookup table refrence points for Base TTC lower Gain Calculation";
*|  :units = "m/sec^2";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_TTCLowerClip_z_str {
*|  :description = "Lookup table Base TTC lower Gain-:::CIB_RangeAccel64_V:::";
*|  :units = "";
*|  :type = caltype.array_5_k_AEB_TTCLowerClip_z_single_0_5_CT;
*|  :annotation = caltype.anns_kcib_TTCLowerClip_x;
*|  }
*|  .k_AEB_TTCMax_str {
*|  :description = "Default TTC for non-closing  far away objects";
*|  :units = "sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_TTCMaxEvalTime_str {
*|  :description = "Maximum TTC beyond which the object is not discriminated";
*|  :units = "sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_TTCMinEvalTime_str {
*|  :description = "Minimum time below which Discrimination is not done";
*|  :units = "sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_TTTAverageTurnAccel_str {
*|  :description = "Average Lat Accel for Evasive maneuver used to compute TTT";
*|  :units = "m/sec^2";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_TTCMinClipSpd_str {
*|  :description = "Minimum speed below which clipping of Accel TTC is activated.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_127p9375_CT;
*|  }
*|  .k_AEB_TTCMinClipRR_str {
*|  :description = "Minimum speed below which clipping of Accel TTC is activated.";
*|  :units = "m/sec";
*|  :type = caltype.single_m82_82_CT;
*|  }
*|  .k_AEB_TTCUpperClip_x_str {
*|  :description = "Lookup table refrence points for Base TTC upper Gain Calculation";
*|  :units = "m/sec^2";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_TTCUpperClip_z_str {
*|  :description = "Lookup table Base TTC upper Gain-:::CIB_RangeAccel64_V:::";
*|  :units = "";
*|  :type = caltype.array_5_k_AEB_TTCUpperClip_z_single_0_5_CT;
*|  :annotation = caltype.anns_kcib_TTCUpperClip_x;
*|  }
*|  .k_AEB_TTTMinLatMovement_str {
*|  :description = "Minimum lateral movement used to compute TTT";
*|  :units = "m";
*|  :type = caltype.single_0_8_CT;
*|  }
*|  .k_AEB_WheelSpdFilterGain_str {
*|  :description = "Gain value for LP Filter for the Wheel Speed Fulter to Replace the Time constant Calibration";
*|  :units = "None";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_YawNeutral_str {
*|  :description = "yaw threshold used to est host to target movement";
*|  :units = "deg/sec";
*|  :type = caltype.single_m128_127p5_CT;
*|  }
*|  .k_AEB_YawNoiseFloorForXolc_str {
*|  :description = "Minimum Yaw below which path angle for XOLC is set to 0";
*|  :units = "deg/sec";
*|  :type = caltype.single_m128_127p5_CT;
*|  }
*|  .k_AEB_HostAcceAeblRdcFac_str {
*|  :description = "Host accel reduce table factor for aeb.";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_HostAccelPoints_str {
*|  :description = "Host accel reduce rows factor for aeb.";
*|  :units = "mps";
*|  :type = caltype.single_m50_50_CT;
*|  }
*|  .k_AEB_HMIBrakingEnbld_str {
*|  :description = "FALSE = HMI_NOT_ENABLED, this overrides the customization to the content of kcib_CPS_SettingValue TR\
*|  UE = HMI_ENABLED";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_LowBrakeAlertEnbl_str {
*|  :description = "Vehicle Configuration Data - When this calibration is TRUE, an FCW alert will be triggered for each \
*|  Low Brake CIB event.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_PrefillBrakeAlertEnbl_str {
*|  :description = "Vehicle Configuration Data - When this calibration is TRUE, an FCW alert will be triggered for each \
*|  brake prefill event.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_OvrdYawRateMax_str {
*|  :description = "Yaw rate of change threshold above which the steering override will become active";
*|  :units = "deg/sec^2";
*|  :type = caltype.single_0_2560_CT;
*|  }
*|  .k_AEB_SteerOvrdOffHdTm_str {
*|  :description = "Length of time after the Steering override starts that it will be maintained active";
*|  :units = "Sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_SteerOvrdOffTTEMinMinusX_str {
*|  :description = "Time To Subtract From TTEMin below which the steering/Yaw Override will not be allowed to cancel a C\
*|  IB Event";
*|  :units = "Sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_VehSSettingValue_str {
*|  :description = "this value determines the CPS setting in case of kcib_HMI_BrakingEnabled = FALSE";
*|  :units = "enum";
*|  :type = caltype.uint8_2_3_CT;
*|  }
*|  .k_AEB_FLBALatchTime_str {
*|  :description = "FLBA once active will be held during this time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_3000_CT;
*|  }
*|  .k_AEB_PrefillLatchTime_str {
*|  :description = "Brake Prefill once active will be held during this time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_3000_CT;
*|  }
*|  .k_AEB_UsePrefillOverride_str {
*|  :description = "Enable   Throttle overide monitoring  at prefill Prefill Activation";
*|  :units = "None";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseUnclippedComTTC_str {
*|  :description = "Enable the Clipping of Accel Based TTC to some percentage within the Base TTC for moveable targets";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_OnlyCommonTTC_str {
*|  :description = "Setting this calibration TRUE will use only common TTC calculation, FALSE will switch back to step-w\
*|  ise calculation This switch will disable the path with kcib_OnlyCommonTTC switch inside!";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_RCSFilterGain_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_AllowHiBrkUnclipped_str {
*|  :description = "Allows 1.0g deployment also when vehicle speed is going down from > kcib_HeavyFullSpeedThreshold If \
*|  this cal is equal to 0 the 1.0g braking is only applied if the initial vehicle speed at CIB deployme\
*|  nt is <= kcib_HeavyFullSpeedThreshold";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HeavyHighSpdTrhd_str {
*|  :description = "Max speed above which High brakes shall not be commanded";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_HeavyFullSpdTrhd_str {
*|  :description = "Max speed above which Full brakes shall not be commanded";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_MinHeavyFullSpdTrhd_str {
*|  :description = "Speed below which Full brakes enter";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_MaxHeavyFullSpdTrhd_str {
*|  :description = "Speed above which Full brakes exit";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_FullBrakingLvlMov_mps_str {
*|  :description = "full brake deceleration value applied to moveable objects";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_FullBrakingLvlStat_mps_str {
*|  :description = "full brake deceleration value applied to stationary objects";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_MaxDecelRadarOnly_str {
*|  :description = "Max Decel allowed in Radar only mode or in faulty sensors state";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_CnfmByCameraEnbl_str {
*|  :description = "Enable/disable whether or not a camera is being used";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HiBrkSpdTrhd_str {
*|  :description = "Below this speed threshold Highbrakes/Fullbrakes are deployed independant of camera enable or active\
*|   faults (camera)";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_ZeroSpdTrhd_str {
*|  :description = "Threshold for the host speed (filtered speed) to set HOLD trigger";
*|  :units = "m/s";
*|  :type = caltype.single_m16_16_CT;
*|  }
*|  .k_AEB_CIBEventLatchTime_str {
*|  :description = "CIBEventLatch once active will be held during this time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_BrkHdTmAfterStop_str {
*|  :description = "How long the vehicle will be hold after vehicle stop";
*|  :units = "msec";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_TestSceneHdTm_ms_str {
*|  :description = "";
*|  :units = "msec";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_FltGainLateralAccel_str {
*|  :description = "Lateral Accel filter Gain";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_VRUHiBrkMaxSpd_str {
*|  :description = "Max host speed allowed for AEB high brake to pedestrain and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_OCBike_ABAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_LongBike_ABAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_CrsBike_ABAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_StatBike_ABAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_OCPed_ABAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_NonCrsPed_ABAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_CrsPed_ABAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_OCBike_IBAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_LongBike_IBAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_CrsBike_IBAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_StatBike_IBAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_OCPed_IBAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_NonCrsPed_IBAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_CrsPed_IBAMaxSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_NonCrsPed_IBAMinSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_VRUMinHostSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_VRUMaxHostSpd_mps_str {
*|  :description = "Max host speed to trigger AEB for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_PFVRUMaxHostSpd_mps_str {
*|  :description = "Max host speed to trigger Prefill for pedestraian and cyclist";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_VRULongRange_str {
*|  :description = "Pedestrain Range Funne1";
*|  :units = "m";
*|  :type = caltype.single_0_120_CT;
*|  }
*|  .k_AEB_VRULatOffsetTrhd_str {
*|  :description = "Pedestrian Lateral offset limit";
*|  :units = "m";
*|  :type = caltype.array_7_k_AEB_VRULatOffsetTrhd_single_0_25_CT;
*|  :annotation = caltype.anns_kcib_PedLongRange;
*|  }
*|  .k_AEB_VRUEnable_str {
*|  :description = "Enable AEB braking to pedestraian and cyclist";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_EnableOncoming_str {
*|  :description = "Enble CIB rteaction to Oncoming Targets";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseHostLatAccel_str {
*|  :description = "Use Host lateral accelaration";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRUYPosHoldOnTrhd_str {
*|  :description = "Lateral limit fo holding on to Pedestrian Target";
*|  :units = "m";
*|  :type = caltype.single_0_35_CT;
*|  }
*|  .k_AEB_MinMatchConfMov_str {
*|  :description = "Minimum Match confidence for Moveable Target";
*|  :units = "";
*|  :type = caltype.uint8_0_5_CT;
*|  }
*|  .k_AEB_MinMatchConfStat_str {
*|  :description = "Minimum Match confidence for Stationary Target";
*|  :units = "";
*|  :type = caltype.uint8_0_5_CT;
*|  }
*|  .k_AEB_UseROCXolc_str {
*|  :description = "Use ROC  Based TTC";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HostLatAccelSign_str {
*|  :description = "Sign Conversion to make Host LatAccel Clockwise Positive";
*|  :units = "";
*|  :type = caltype.int8_m1_1_CT;
*|  }
*|  .k_AEB_RevGearHoldRlsEnbl_str {
*|  :description = "Enbable exit from HOLD when gear is in REVERSE";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_TTCAnnoyOffset_str {
*|  :description = "Offset TTC added to Track annoyance line";
*|  :units = "";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_TTCAnnoyMinEnbl_str {
*|  :description = "Enable Upper limit for Track Annoyance TTC";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_TTCAnnoyMax_str {
*|  :description = "Upper TTC limit to Track annoyance line";
*|  :units = "";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_ReferLeadAccel_str {
*|  :description = "Enbable Lead vehicle as Input for High Brake Lead Accel Based Leadtime Offset Calculation";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_GateMinOpeningRange_str {
*|  :description = "Minimum Opening Range for PCS discirmation for a Actively braking target";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_UseMinTrkAccel_str {
*|  :description = "Enable usage of Range Accel for Min Accel Determination";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HighBrkAnnoyTTCThrs_str {
*|  :description = "High Brake Annoyance TTC Threshold Above which High Brakes will not be deployed";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_HighBrkLeadDecelTrhd_str {
*|  :description = "Decel Threshold for determining a Strongly decelarated stopped Target";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_HiBrkLdTmStop_sec_str {
*|  :description = "High Brake Lead time for  a Stopped Target";
*|  :units = "sec";
*|  :type = caltype.array_10_k_AEB_HiBrkLdTmStop_sec_single_0_10_CT;
*|  :annotation = caltype.anns_kcib_HiBrakeLeadTimeStopMps;
*|  }
*|  .k_AEB_HiBrkLdTmStop_mps_str {
*|  :description = "High Brake Host Speed reference point for  a Stopped Target";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_AlertOnlyTTCTrhd_str {
*|  :description = "TTC Threshold for Brakes when customization is 'ALERT'";
*|  :units = "sec";
*|  :type = caltype.single_m2_2_CT;
*|  }
*|  .k_AEB_HostAccelInhbtTrhd_str {
*|  :description = "Host Accel threshold above which Trak Accel based lead time is negated";
*|  :units = "mpss";
*|  :type = caltype.single_m10_30_CT;
*|  }
*|  .k_AEB_UseLeadAccelFCW_str {
*|  :description = "Enable the usage Lead Accel Caluclated by FCW module";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_BrkPedPosFiltgain_str {
*|  :description = "Brake Pedal Position Filter gain";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSDrvBrkPdlPosThres_str {
*|  :description = "The Thres for driver brake pedal position.";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_DBSDrvBrkPdlPrsThres_str {
*|  :description = "The Thres for driver brake pedal pressure.";
*|  :units = "sec";
*|  :type = caltype.single_0_15000_CT;
*|  }
*|  .k_AEB_DBSPedRateEnblTm_str {
*|  :description = "Minimum Brake pedal Rate Duration Sustain Time for IBA Activation";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSPedRateHdTm_str {
*|  :description = "Minimum Brake pedal Rate Halo Time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_DBSActiveMinPedPos_str {
*|  :description = "Minimum Brake Pedal Position for IBA Activation";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_DBSPedPosEnblTm_str {
*|  :description = "Minimum Brake pedal Position Sustain Time  for IBA Activation";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSMinBrkPedRateOff_str {
*|  :description = "Minimum Brake Pedal Position Rate for IBA DeActivation";
*|  :units = "";
*|  :type = caltype.int32_m50000_50000_CT;
*|  }
*|  .k_AEB_DBSPedRateDsblTm_str {
*|  :description = "Minimum Brake pedal Rate Duration Sustain Time for IBA Deactivation";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSReleaseMinPedPos_str {
*|  :description = "Minimum Brake Pedal Position for IBA Deactivation";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_DBSPedPosDisableTime_str {
*|  :description = "Minimum Brake pedal Position Duration Sustain Time for IBA Deactivation";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSMinBrkPedRateOn_str {
*|  :description = "Minimum Brake Pedal Position Rate for IBA Activation during no Automatic Braking";
*|  :units = "";
*|  :type = caltype.int32_m50000_50000_CT;
*|  }
*|  .k_AEB_DBSLBMinBrkPedRateOn_str {
*|  :description = "Minimum Brake Pedal Position Rate for IBA Activation during CIB Low Brakes";
*|  :units = "";
*|  :type = caltype.int32_m50000_50000_CT;
*|  }
*|  .k_AEB_DBSHBMinBrkPedRateOn_str {
*|  :description = "Minimum Brake Pedal Position Rate for IBA Activation during CIB High Brakes";
*|  :units = "";
*|  :type = caltype.int32_m50000_50000_CT;
*|  }
*|  .k_AEB_DBSFBMinBrkPedRateOn_str {
*|  :description = "Minimum Brake Pedal Position Rate for IBA Activation during CIB Full Brakes";
*|  :units = "";
*|  :type = caltype.int32_m50000_50000_CT;
*|  }
*|  .k_AEB_DrvBrkPressFiltgain_str {
*|  :description = "Brake Pedal Pressure Filter gain";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSMinDrvAppBrkPresOn_str {
*|  :description = "Minimum Brake Pedal Pressure for IBA Activation";
*|  :units = "";
*|  :type = caltype.uint16_0_19125_CT;
*|  }
*|  .k_AEB_DBSPressEnblTm_str {
*|  :description = "Minimum Brake pedal Pressure Sustain Time  for IBA Activation";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSDrvBrkPrsRateOn_str {
*|  :description = "Minimum Brake Pedal Pressure Rate for IBA Activation";
*|  :units = "";
*|  :type = caltype.int32_m50000_50000_CT;
*|  }
*|  .k_AEB_DBSPrsRateEnblTm_str {
*|  :description = "Minimum Brake pedal Pressure Rate Sustain Time  for IBA Activation";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSMinDrvAppBrkPresOff_str {
*|  :description = "Minimum Brake Pedal Pressure for IBA Deactivation";
*|  :units = "";
*|  :type = caltype.uint16_0_19125_CT;
*|  }
*|  .k_AEB_DBSPressDisableTime_str {
*|  :description = "Minimum Brake pedal Pressure Sustain Time  for IBA Deactivation";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSDrvBrkPrsRateOff_str {
*|  :description = "Minimum Brake Pedal Pressure Rate for IBA Deactivation";
*|  :units = "";
*|  :type = caltype.int32_m50000_50000_CT;
*|  }
*|  .k_AEB_DBSPrsRateDisableTime_str {
*|  :description = "Minimum Brake Pedal Pressure Rate Duration Sustain Time for IBA Deactivation";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSAccelOffset_sec_str {
*|  :description = "Offset Added to the IBA Lead time for Moveable Targets based on Accelaration Reference";
*|  :units = "sec";
*|  :type = caltype.array_8_k_AEB_DBSAccelOffset_sec_single_0_10_CT;
*|  :annotation = caltype.anns_kcib_IBAAccelOffsetMpss;
*|  }
*|  .k_AEB_DBSAccelOffset_mpss_str {
*|  :description = "Accelaration Reference for  Low Brake Lead time offset";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_DBSWhlSpdAcceEnbl_str {
*|  :description = "Enable the Usage of Wheel Speed based Accelaration calculation for IBA";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSTTCBsdRampdownRate_str {
*|  :description = "Decel Rampdown Rate Based on TTC";
*|  :units = "";
*|  :type = caltype.array_5_k_AEB_DBSTTCBsdRampdownRate_single_0_10_CT;
*|  :annotation = caltype.anns_kcib_IBATTCBsdRampdown_Sec;
*|  }
*|  .k_AEB_DBSTTCBsdRampdown_sec_str {
*|  :description = "Rampdown Rate TTC Break points";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSTTCBsdRampupRate_str {
*|  :description = "Decel Rampup Rate Based on TTC";
*|  :units = "";
*|  :type = caltype.array_5_k_AEB_DBSTTCBsdRampupRate_single_0_10_CT;
*|  :annotation = caltype.anns_kcib_IBATTCBsdRampup_Sec;
*|  }
*|  .k_AEB_DBSTTCBsdRampup_sec_str {
*|  :description = "Rampup Rate TTC Break points";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSBrkPedPosOnlyEnbl_str {
*|  :description = "Activate IBA only based on Brake Pedal Position";
*|  :units = "Boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSDrvBrkPrsOnlyEnbl_str {
*|  :description = "Activate IBA only based on Brake Pedal Pressure";
*|  :units = "Boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSMinLeadAccel_str {
*|  :description = "Minimum Lead Accelaration for future Needed deceleartion prediction";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_DBSMinRangeAccel_str {
*|  :description = "Minimum Relative Accelaration for future Needed deceleartion prediction";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_DBSLeadAccelFact_str {
*|  :description = "Lead Accelaration factoe for future Needed deceleartion prediction";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSHostDecelThrsFac_str {
*|  :description = "Host Decelaration Threshold factor";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSMinDecelRampOut_str {
*|  :description = "Minimum IBA Decelartion request during Brake Ramp out";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_HostAccelInhbtHaloTime_str {
*|  :description = "Halo Time after host accelaratiion during which all the brake lead time offset based on relative Acc\
*|  el should be disabled";
*|  :units = "msec";
*|  :type = caltype.uint16_0_50000_CT;
*|  }
*|  .k_AEB_DBSBrkDualCnfmEnbl_str {
*|  :description = "Enable usage of Brake pedal and Brake Pressure for IBA Activation";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSDualConfirmMaxTime_str {
*|  :description = "Maximum Wait time allowed for Dual confirmation for IBA Activation";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_DBSMaxActivationWindow_str {
*|  :description = "Maximum Grace time allowed for IBA Activation after a valid Driver Brake pedal Press";
*|  :units = "msec";
*|  :type = caltype.uint16_0_20000_CT;
*|  }
*|  .k_AEB_DBSBrakeCnfmEnbl_str {
*|  :description = "Enable the Usage of CIB Brake Confirm for Exiiting IBA";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSLeadAclOfst_sec_str {
*|  :description = "Offset Added to the IBA Lead time for Moveable Targets based on Lead Accelaration";
*|  :units = "sec";
*|  :type = caltype.array_8_k_AEB_DBSLeadAclOfst_sec_single_0_10_CT;
*|  :annotation = caltype.anns_kcib_IBALeadAclOfstMpss;
*|  }
*|  .k_AEB_DBSLeadAclOfst_mpss_str {
*|  :description = "Lead Accelaration Reference for  IBA Lead time offset";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_DBSMinStopDistance_str {
*|  :description = "Miinimum Stop dsiatnce with lead vehicle  during IBA";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSMinStopDistanceLmt_str {
*|  :description = "Miinimum Range to be considered during IBA for Needed Accel Calulation";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DBSRRAccelFiltGain_str {
*|  :description = "Filter Gain for Range rate Based Need Decel";
*|  :units = "";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_DBSRngAccelFiltGain_str {
*|  :description = "Filter Gain for Range Based Need Decel";
*|  :units = "";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_DBSRngBsdAccelEnbl_str {
*|  :description = "Enable the usage of Range Based Needed Accel  caluclation for Braking Targets";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSLdAclBsdAccelEnbl_str {
*|  :description = "Enable the usage of Lead Accel Based Needed Accel  caluclation for Braking Targets";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DrvOvrdBaseBrkPdPos_str {
*|  :description = "Max Brake pedal Position  for  Low Brake Inhibit";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_PrefillMaxSpdMov_str {
*|  :description = "Maximum host speed allowed for prefill to be triggered for moveable targets";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_PrefillMaxSpdStat_str {
*|  :description = "Maximum host speed allowed for prefill  to be triggered stationary targets";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_FLBALdTmMov_sec_str {
*|  :description = "FLBA Lead time Moveable Targets";
*|  :units = "mps";
*|  :type = caltype.array_15_k_AEB_FLBALdTmMov_sec_single_0_10_CT;
*|  :annotation = caltype.anns_kcib_PrefillLeadTimeMoveMps;
*|  }
*|  .k_AEB_FLBALdTmStat_sec_str {
*|  :description = "FLBA Lead time Moveable Targets";
*|  :units = "mps";
*|  :type = caltype.array_15_k_AEB_FLBALdTmStat_sec_single_0_10_CT;
*|  :annotation = caltype.anns_kcib_PrefillLeadTimeStatMps;
*|  }
*|  .k_AEB_MSLdTmMov_sec_str {
*|  :description = "Mnstop Lead time Moveable Targets";
*|  :units = "mps";
*|  :type = caltype.array_15_k_AEB_MSLdTmMov_sec_single_0_10_CT;
*|  :annotation = caltype.anns_kcib_PrefillLeadTimeMoveMps;
*|  }
*|  .k_AEB_MSLdTmStat_sec_str {
*|  :description = "Minstop Lead time Moveable Targets";
*|  :units = "mps";
*|  :type = caltype.array_15_k_AEB_MSLdTmStat_sec_single_0_10_CT;
*|  :annotation = caltype.anns_kcib_PrefillLeadTimeStatMps;
*|  }
*|  .k_AEB_FLBAMinSpdChkEnbl_str {
*|  :description = "Enable Minimum speed check for FLBA";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_FLBAMaxSpdMov_str {
*|  :description = "Maximum speed  for FLBA  Actiavtion for  Moveable Targets";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_FLBAMaxSpdStat_str {
*|  :description = "Maximum speed  for FLBA Actiavtion for Stationary Targets";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_MSMinSpdChkEnbl_str {
*|  :description = "Enable Minimum speed check for MinStop";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_MSMaxSpdMov_str {
*|  :description = "Maximum speed  for MinStop Actiavtion for  Moveable Targets";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_MSMaxSpdStat_str {
*|  :description = "Maximum speed  for MinStop Actiavtion for Stationary Targets";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_DBSMaxSpdMov_str {
*|  :description = "Maximum host speed allowed for EBA to be triggered  for moveable targets";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_DBSMaxSpdStat_str {
*|  :description = "Maximum speed  for IBA Actiavtion for Stationary Targets";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_VRUMinMatchConf_str {
*|  :description = "Minimum Pedestrain Match Confidence";
*|  :units = "";
*|  :type = caltype.uint8_0_5_CT;
*|  }
*|  .k_AEB_VRUDBSEnbl_str {
*|  :description = "Enable IBA to Pedestrains";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_SteerOvrdOffTTEMin_str {
*|  :description = "Minimmum TTC Steering Override Inhibit";
*|  :units = "sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_FLBADefaultEnbl_str {
*|  :description = "Enable FLBA by default";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_FLBAIgnoreHMIStng_str {
*|  :description = "Ignore Driver Customization for FLBA";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_FLBAHMICustStng_str {
*|  :description = "Minimum Driver Customization for FLBA";
*|  :units = "";
*|  :type = caltype.uint8_0_3_CT;
*|  }
*|  .k_AEB_MinStopDefaultEnbl_str {
*|  :description = "Enable Minstop by default";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_MinStopIgnoreHMIStng_str {
*|  :description = "Ignore Driver Customization forMinstop";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_MinStopHMICustStng_str {
*|  :description = "Minimum Driver Customization for Minstop";
*|  :units = "";
*|  :type = caltype.uint8_0_3_CT;
*|  }
*|  .k_AEB_DBSIgnoreHMIStng_str {
*|  :description = "Ignore Driver Customization for IBA";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSHMICustStng_str {
*|  :description = "Minimum Driver Customization for IBA";
*|  :units = "";
*|  :type = caltype.uint8_0_3_CT;
*|  }
*|  .k_AEB_IgnLowBrkHBTimerReset_str {
*|  :description = "Ignore the reseting of HighBrake timer durng Low Brakes";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSMaxDecelExitTime_str {
*|  :description = "Maximum duration for which IBA Max decelartion request is allowed";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_PrefillExitTime_str {
*|  :description = "Maximum duration for which Prefill request is allowed";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_FLBAExitTime_str {
*|  :description = "Maximum duration for which FLBA request is allowed";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_MinStopExitTime_str {
*|  :description = "Maximum duration for which Minstop request is allowed";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_MaxDecelExitTime_str {
*|  :description = "Maximum duration for which CIB Maximum Decelaration request is allowed";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_HoldRelPressure_str {
*|  :description = "Minimum Driver Applied Brake pressure to release the CIB Hold Command";
*|  :units = "Kpa";
*|  :type = caltype.uint16_0_50025_CT;
*|  }
*|  .k_AEB_UseOnlyBrkPrsHldRel_str {
*|  :description = "Enable the Release of HOLD only using Driver Applied Brake Presure";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_NoEPBBrakeHdTm_str {
*|  :description = "Maximum Brake hold time when Vehicle is not equipped with EPB.";
*|  :units = "msec";
*|  :type = caltype.uint32_0_1000000_CT;
*|  }
*|  .k_AEB_VRUOncomingEnbl_str {
*|  :description = "when false, will disable all oncoimg VRU AEB";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HiConfOCBikePFTTC_sec_str {
*|  :description = "prifill threshold for high confidence oncoming bicycle";
*|  :units = "Sec";
*|  :type = caltype.array_15_k_AEB_HiConfOCBikePFTTC_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_HiConfBikePrefillTTCMps;
*|  }
*|  .k_AEB_HiConfOCBikeLoBrkTTC_sec_str {
*|  :description = "low brake threshold for high confidence oncoming bicycle";
*|  :units = "Sec";
*|  :type = caltype.array_15_k_AEB_HiConfOCBikeLoBrkTTC_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_HiConfBikeLowBrakeTTCMps;
*|  }
*|  .k_AEB_HiConfOCBikeHiBrkTTC_sec_str {
*|  :description = "high brake threshold for high confidence oncoming bicycle";
*|  :units = "Sec";
*|  :type = caltype.array_15_k_AEB_HiConfOCBikeHiBrkTTC_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_HiConfBikeHiBrakeTTCMps;
*|  }
*|  .k_AEB_HiConfOCPedPrefillTTC_sec_str {
*|  :description = "prifill threshold for high confidence oncoming pedestrian";
*|  :units = "Sec";
*|  :type = caltype.array_15_k_AEB_HiConfOCPedPrefillTTC_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_HiConfPedPrefillTTCMps;
*|  }
*|  .k_AEB_HiConfOCPedLoBrkTTC_sec_str {
*|  :description = "low brake threshold for high confidence oncoming pedestrian";
*|  :units = "Sec";
*|  :type = caltype.array_15_k_AEB_HiConfOCPedLoBrkTTC_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_HiConfPedLowBrakeTTCMps;
*|  }
*|  .k_AEB_HiConfOCPedHiBrkTTC_sec_str {
*|  :description = "high brake threshold for high confidence oncoming pedestrian";
*|  :units = "Sec";
*|  :type = caltype.array_15_k_AEB_HiConfOCPedHiBrkTTC_sec_single_m25p5_25p5_CT;
*|  :annotation = caltype.anns_kcib_HiConfPedHiBrakeTTCMps;
*|  }
*|  .k_AEB_AccelOffsetRangeBrkPoints_str {
*|  :description = "Range break points input of table that used for offset added to the prefill/Brake Lead time for Move\
*|  able targets";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_SteerOvrdDisbleType_str {
*|  :description = "When this value set to 0, driver can not steer overide AEB to vehicle target When this value set to \
*|  1, driver can not steer overide AEB to VRU target When this value set to 2, driver can steer overide\
*|   AEB to any target";
*|  :units = "";
*|  :type = caltype.uint8_0_3_CT;
*|  }
*|  .k_AEB_HighBrkAnnoyTTCLose_str {
*|  :description = "Offset added to high brake annoying TTC threshold when lead vehicle deceleration detected";
*|  :units = "sec";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_LowBrkAnnoyTTLose_str {
*|  :description = "Offset added to low brake annoying TTC threshold when lead vehicle deceleration detected.";
*|  :units = "sec";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_RangeDecelTrhd_str {
*|  :description = "range deceleration value threshold for determine lead vehicle decelearation";
*|  :units = "mps^2";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_AEB_LeadDecelTrhd_str {
*|  :description = "range deceleration value threshold for determine lead vehicle decelearation";
*|  :units = "mps^2";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_AEB_DBSMinSpdChkEnbl_str {
*|  :description = "When this set to true, minimal speed will be checked before IBA allowed";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSUseDefaultDecel_str {
*|  :description = "When set to true, Fusion IBA will use default deceleration instead of variable decel.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreObjClassChk_str {
*|  :description = "AEB will not check object class whether it is car, truck or motorcycle. If false, AEB will not trig \
*|  for motorcycle";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_MinEgoSpdRadarOnly_str {
*|  :description = "Minimal host speed above which radar only target allowed.";
*|  :units = "none";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_MinMatchConfMovLowSpd_str {
*|  :description = "Minimal confidence required to trigger AEB to moveable target when vehicle speed below threshold val\
*|  ue kcib_MinEgoSpdRadarOnly";
*|  :units = "none";
*|  :type = caltype.uint8_0_5_CT;
*|  }
*|  .k_AEB_HardTurnInhibitSpdPoints_str {
*|  :description = "Speed point to determine steering angle inhibit";
*|  :units = "mps";
*|  :type = caltype.single_0_20_CT;
*|  }
*|  .k_AEB_HardTurnStrAngleTrhd_str {
*|  :description = "Table value for steering angle inhibit";
*|  :units = "degrees";
*|  :type = caltype.single_0_1024_CT;
*|  }
*|  .k_AEB_StrAngInhibitEnblTm_str {
*|  :description = "Minimal times required for AEB steering angle inhibit";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_BrkEngagePresEnblTm_str {
*|  :description = "Minimal time required to trigger brake pedal pressure inhibit";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_BrkEngageHdTm_str {
*|  :description = "Brake pedal engage hold time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_IgrLowBrkDrvEng_str {
*|  :description = "When set to true, low brake will not consider brake engage";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSMinVehicleSpd_str {
*|  :description = "Minimal host speed for IBA to engage";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_BcyMaxRangeRate_str {
*|  :description = "Rangerate above which AEB VRU will be released";
*|  :units = "mps";
*|  :type = caltype.single_m7_7_CT;
*|  }
*|  .k_AEB_IgrHiBrkDrvEng_str {
*|  :description = "When set to true, high brake will not consider brake engage";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DrvEngInhibitSpd_str {
*|  :description = "Maximum speed allowed for brake pedal AEB inhibt";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_VRUHBMinConf_str {
*|  :description = "Minimal confidence level require to trigger high brake";
*|  :units = "none";
*|  :type = caltype.uint8_0_5_CT;
*|  }
*|  .k_AEB_HBHdTmLowAge_str {
*|  :description = "When target age is small. Set high brake hold time to this small value";
*|  :units = "msec";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AEB_OtherTrgtMinDeltaYpos_str {
*|  :description = "Minimal Ypos delta before it can be seen as another target";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_VRULatDeSelTrhd_str {
*|  :description = "Pedestrian Lateral offset limit";
*|  :units = "m";
*|  :type = caltype.single_0_25_CT;
*|  }
*|  .k_AEB_GasInhibitLowSpdTrhd_str {
*|  :description = "When speed below this thres, gas pedal AEB inhibit will switch to low speed mode";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_GasInhibitHiSpdTrhd_str {
*|  :description = "When speed above this thres, gas pedal AEB inhibit will switch to high speed mode";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_VehHBDrvEngTypeSltd_str {
*|  :description = "Vehicle high brake will be inhibit by driver engage manuver by following type: 1 driver steer;2drive\
*|  r brake; 4driver accel";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VehLBDrvEngTypeSltd_str {
*|  :description = "Vehicle low brake will be inhibit by driver engage manuver by following type: 1 driver steer;2driver\
*|   brake; 4driver accel";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VehPFDrvEngTypeSltd_str {
*|  :description = "Vehicle prefill will be inhibit by driver engage manuver by following type: 1 driver steer;2driver b\
*|  rake; 4driver accel";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_IgrPrefillDrvEng_str {
*|  :description = "AEB Prefill tp vehicle will be innored driver manuver by set this to true";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRUHBDrvEngTypeSltd_str {
*|  :description = "VRU high brake will be inhibit by driver engage manuver by following type: 1 driver steer;2driver br\
*|  ake; 4driver accel";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VRULBDrvEngTypeSltd_str {
*|  :description = "VRU low brake will be inhibit by driver engage manuver by following type: 1 driver steer;2driver bra\
*|  ke; 4driver accel";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_IgrVRUPFDrvEng_str {
*|  :description = "AEB Prefill tp VRU will be innored driver manuver by set this to true";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRUPFDrvEngTypeSltd_str {
*|  :description = "VRU prefill will be inhibit by driver engage manuver by following type: 1 driver steer;2driver brake\
*|  ; 4driver accel";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_HiBrkDropWaitTime_str {
*|  :description = "when high brake drop and object move out funnel, this output will be latched";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_VRUHBHoldMaxRngAllow_str {
*|  :description = "Maximum range allowed for VRU target drop before high brake hold logic can be enabled.";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_HBHoldMaxRngAllow_str {
*|  :description = "Maximum range allowed for vehicle target drop before high brake hold logic can be enabled.";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_DRTClassHoldEnbl_str {
*|  :description = "When true, enable class hold logic.";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_GateMinRangeMov_str {
*|  :description = "Minimal range below which the is no discrimination for Moveable";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_GateMinRangeStat_str {
*|  :description = "Minimal range below which the is no discrimination for Moveable";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_ClsFstDectIPAOffset_str {
*|  :description = "Number of cycles that will add to normal in-path age when their first detected range is less than th\
*|  is value.";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_OvtkStrAngleTrhd_str {
*|  :description = "Steering angle has to great than this value before driver overtaking can be initialied.";
*|  :units = "degrees";
*|  :type = caltype.single_0_1024_CT;
*|  }
*|  .k_AEB_OvtkGasPedalTrhd_str {
*|  :description = "Gas pedal has to great than this value before driver overtaking can be initialied.";
*|  :units = "none";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_LongBikePFLdTm_mps_str {
*|  :description = "Input range rate";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_LongBikePFLdTm_sec_str {
*|  :description = "Time Added to TTB to allow Prefill deployment for proceeding bicycle";
*|  :units = "sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_LongBikeLBLdTm_mps_str {
*|  :description = "Input range rate";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_LongBikeLBLdTm_sec_str {
*|  :description = "Time Added to TTB to allow LowBrake deployment for proceeding bicycle";
*|  :units = "sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_LongBikeHBLdTm_sec_str {
*|  :description = "Time Added to TTB to allow HighBrake deployment for proceeding bicycle";
*|  :units = "sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_LongBikeFLBALdTm_sec_str {
*|  :description = "Time Added to TTB to allow FLBA deployment for proceeding bicycle";
*|  :units = "sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_LongBikeMSLdTm_sec_str {
*|  :description = "Time Added to TTB to allow MS deployment for proceeding bicycle";
*|  :units = "sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_LongBikeDBSLdTm_sec_str {
*|  :description = "Time Added to TTB to allow IBA deployment for proceeding bicycle";
*|  :units = "sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_HiConfBikeStaPFTTC_mps_str {
*|  :description = "Input range rate";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_HiConfBikeStaPFTTC_sec_str {
*|  :description = "TTC threshold for stationary bike to allow Prefill";
*|  :units = "Sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_BikeStaLBTTC_sec_str {
*|  :description = "TTC threshold for stationary bike to allow Low Brake";
*|  :units = "Sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_HiConfBikeStaHBTTC_sec_str {
*|  :description = "TTC threshold for stationary bike to allow High Brake";
*|  :units = "Sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_HiConfBikeStaFLBATTC_sec_str {
*|  :description = "TTC threshold for stationary bike to allow FLBA";
*|  :units = "Sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_HiConfBikeStaMSTTC_sec_str {
*|  :description = "TTC threshold for stationary bike to allow MinStop";
*|  :units = "Sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_HiConfBikeStaDBSTTC_sec_str {
*|  :description = "TTC threshold for stationary bike to allow IBA";
*|  :units = "Sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_FullBrakeHiBrkCnt_str {
*|  :description = "C-Code Minimum length of time AEB high brakes are active prior to allowing high: 1 Cnt = 50 ms";
*|  :units = "Counts";
*|  :type = caltype.uint8_0_254_CT;
*|  }
*|  .k_AEB_JAFullBrakeHiBrkCnt_str {
*|  :description = "C-Code Minimum length of time AEB JA high brakes are active prior to allowing high: 1 Cnt = 50 ms";
*|  :units = "Counts";
*|  :type = caltype.uint8_0_254_CT;
*|  }
*|  .k_AEB_FullBrkDuringTimer_mps_str {
*|  :description = "full brake deceleration value applied during target drop and brake timer trigger";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_IgnLowBrkFBTimerReset_str {
*|  :description = "Ignore the reseting of FullBrake timer durng Low Brakes";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnHiBrkFBTimerReset_str {
*|  :description = "Ignore the reseting of FullBrake timer durng High Brakes";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRUAEBXolcTrhd_str {
*|  :description = "Pedestrian Lateral offset limit";
*|  :units = "m";
*|  :type = caltype.single_0_25_CT;
*|  }
*|  .k_AEB_HiBrkLowPerstCntJA_str {
*|  :description = "C-Code Minimum length of time low brakes are active prior to allowing Junction high: 1 Cnt = 50 ms";
*|  :units = "Counts";
*|  :type = caltype.uint8_0_254_CT;
*|  }
*|  .k_AEB_DBSHostAccelTrhd_str {
*|  :description = "Host vehicle accel threshold for IBA active";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_SuppressTime_str {
*|  :description = "Least suppress time between two AEB";
*|  :units = "msec";
*|  :type = caltype.uint16_0_50000_CT;
*|  }
*|  .k_AEB_CLHiBrkNeedDecelLimt_str {
*|  :description = "Close loop deceleration value limitation during high brake";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_NoAEBSuppressEnbl_str {
*|  :description = "When true, enable no suppress between two AEB";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HeadingAngOCTAPTrhd_str {
*|  :description = "Minimal absoultely value of heading angle that ego veihcle has turned before it can be seen as OCTAP\
*|   case";
*|  :units = "none";
*|  :type = caltype.uint16_0_360_CT;
*|  }
*|  .k_AEB_HeadingAngCPTATrhd_str {
*|  :description = "Minimal absoultely value of heading angle ego veihcle has turned before it can be seen as CPTA case";
*|  :units = "none";
*|  :type = caltype.uint16_0_360_CT;
*|  }
*|  .k_AEB_SensorInputLpTm_str {
*|  :description = "Sensor input Cycle Time In Seconds";
*|  :units = "Sec";
*|  :type = caltype.single_0p001_25p5_CT;
*|  }
*|  .k_AEB_VcanInputLpTm_str {
*|  :description = "VCAN input Cycle Time In Seconds";
*|  :units = "Sec";
*|  :type = caltype.single_0p001_25p5_CT;
*|  }
*|  .k_AEB_StationaryVehFullChkEnbl_str {
*|  :description = "Enable full brake condition check for movable car";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_LongMovBikeFullChkEnbl_str {
*|  :description = "Enable Full rangerate and range double check for long moving bicycle";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_leadAccelEnFullBrk_str {
*|  :description = "Enable Full brake directly when lead accel less than this threshold";
*|  :units = "none";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_FullBrkRangePoints_str {
*|  :description = "range points which used check full brake enable";
*|  :units = "none";
*|  :type = caltype.single_0_255_CT;
*|  }
*|  .k_AEB_FullBrkRngRtPoints_str {
*|  :description = "rangerate points which used check full brake enable";
*|  :units = "none";
*|  :type = caltype.single_m255_0_CT;
*|  }
*|  .k_AEB_FullBrakeChkEnbl_str {
*|  :description = "Flag indicates whether full brake should be trigger based on range and rangerate";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_AxleTorqueFiltTime_ms_str {
*|  :description = "Filter time constant in msec applied to axle torque output.";
*|  :units = "msec";
*|  :type = caltype.uint16_0_1000_CT;
*|  }
*|  .k_AEB_AxleTorqueRateMax_str {
*|  :description = "Rate limit applied to axle torque output.";
*|  :units = "Nm/sec";
*|  :type = caltype.uint16_128_8192_CT;
*|  }
*|  .k_AEB_AxleTorqueRateMin_str {
*|  :description = "Rate limit applied to axle torque output.";
*|  :units = "Nm/sec";
*|  :type = caltype.int16_m8192_m128_CT;
*|  }
*|  .k_AEB_BrakeAccelFiltTime_ms_str {
*|  :description = "Filter time constant in msec applied to brake control acceleration output.";
*|  :units = "msec";
*|  :type = caltype.uint16_0_2000_CT;
*|  }
*|  .k_AEB_BrakeAccelRateMax_str {
*|  :description = "Rate limit applied to brake control acceleration output.";
*|  :units = "mps^3";
*|  :type = caltype.uint16_1_500_CT;
*|  }
*|  .k_AEB_BrakeAccelRateMin_str {
*|  :description = "Rate limit applied to brake control acceleration output.";
*|  :units = "mps^3";
*|  :type = caltype.int16_m500_m1_CT;
*|  }
*|  .k_AEB_DrvIntndAxlTrqMinNegOffst_str {
*|  :description = "During a CIB event, the axle torque request to the engine equals the (Driver Intended Axle Torque Mi\
*|  nimum + kcibd_DrvIntndAxlTrqMinNegOffst).";
*|  :units = "Nm";
*|  :type = caltype.int16_m1000_1000_CT;
*|  }
*|  .k_AEB_BrakeAccelFinalLimit_str {
*|  :description = "Final limit applied to CIB braking requests.";
*|  :units = "mpss";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_AEB_HoldDecelEnbl_str {
*|  :description = "Enable the Holding of the Last Decel request during CIB Hold";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HoldBrkReqEnbl_str {
*|  :description = "Enable the Holding of the Last AutobRake Required signal during CIB Hold";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseAxleTrqtoBrk_str {
*|  :description = "Enable the useage of CIB computed Axle torque request";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnorePedTTCChk_str {
*|  :description = "When it is set to true,fusion system will ignore TTC check for pedestrain";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnorePedRngChk_str {
*|  :description = "When it is set to true,fusion system will ignore range check for pedestrain";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRUMaxTTCAllowed_str {
*|  :description = "Maximum TTC for fusion pedestrian target to be discriminated as interest target";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_VRUMinTTCAllowed_str {
*|  :description = "Minimal TTC for fusion pedestrian target to be discriminated as interest target";
*|  :units = "sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_VRUMaxRngAllowed_str {
*|  :description = "Maximum range for fusion pedestrian target to be discriminated as interest target";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_VRUMinRngAllowed_str {
*|  :description = "Minimal range for fusion pedestrian target to be discriminated as interest target";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_EPBStateAffectHold_str {
*|  :description = "when this calibration is set to 1, whether EPB is available will results in differetn AEB hold strat\
*|  egy. When this calibration is set to 0, Hold will exit for a calibrated time no matter whether EPB a\
*|  vailable or not.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_MinConfSRRDegrade_str {
*|  :description = "require at least fusion source";
*|  :units = "enum";
*|  :type = caltype.uint8_0_7_CT;
*|  }
*|  .k_AEB_MovSRRMisAlignChkEnbl_str {
*|  :description = "Will do SRR Mis Aligment check for moveable target when this is true.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSReleaseAEBDisbl_str {
*|  :description = "When this cal set to true, IBA can not cause AEB release and therefore FLBA/MinStop exit";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_LowConfInPathAgeTrhd_str {
*|  :description = "Minimal In-path age need to be waitted for AEB engage under low confidence";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_MedConfInPathAgeTrhd_str {
*|  :description = "Minimal In-path age need to be waitted for AEB engage under low confidence";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_HiConfInPathAgeTrhd_str {
*|  :description = "Minimal In-path age need to be waitted for AEB engage under low confidence";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_HiBrkMinReleaseDist_str {
*|  :description = "AEB VRU high brake release minimal target distance allowed";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_EnVRUClutterShutDown_str {
*|  :description = "when true, will enable AEB shutdown when clutter";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HiBrkVisConfirmDisable_str {
*|  :description = "when true, not use ME Flag for high brake. when false, use ME flag";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_LowBrkVisConfirmDisable_str {
*|  :description = "when true, not use ME Flag for low brake. when false, use ME flag";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_GasEngagePosEnTime_str {
*|  :description = "min time required to to active gas pedal inhibit";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_GasEngagePosEntryTrhd_str {
*|  :description = "gas pedal position threshold to inhibit AEB";
*|  :units = "none";
*|  :type = caltype.uint8_0_100_CT;
*|  }
*|  .k_AEB_GasEngagePosExitTrhd_str {
*|  :description = "gas pedal position relay threshold to inhibit AEB";
*|  :units = "none";
*|  :type = caltype.uint8_0_100_CT;
*|  }
*|  .k_AEB_GasPosRateEntryTrhd_str {
*|  :description = "gas pedal position rate threshold to inhibit AEB";
*|  :units = "none";
*|  :type = caltype.int16_m500_500_CT;
*|  }
*|  .k_AEB_GasPosRateExitTrhd_str {
*|  :description = "gas pedal position rate relay threshold to inhibit AEB";
*|  :units = "none";
*|  :type = caltype.int16_m500_500_CT;
*|  }
*|  .k_AEB_GasPosRateEnTime_str {
*|  :description = "min time required to to active gas pedal rate inhibit";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_GasEngageHdTm_str {
*|  :description = "latch time when gas pedal inhibit was actived";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_BrkEngagePosEntryTrhd_str {
*|  :description = "Brake pedal position threshold to inhibit AEB";
*|  :units = "none";
*|  :type = caltype.uint8_0_100_CT;
*|  }
*|  .k_AEB_BrkEngagePosExitTrhd_str {
*|  :description = "brake position threshold relay";
*|  :units = "none";
*|  :type = caltype.uint8_0_100_CT;
*|  }
*|  .k_AEB_BrkEngagePosEnTime_str {
*|  :description = "min time required to to active brake brake inhibit";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_HBNoVisFlagMinConf_str {
*|  :description = "when PCA confidence >= the threshold, will ignore ME flag";
*|  :units = "uint8";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_AEB_LBNoVisFlagMinConf_str {
*|  :description = "when PCA confidence >= the threshold, will ignore ME flag";
*|  :units = "uint8";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_AEB_UseNewPrefillCounter_str {
*|  :description = "when true, use new prifill logic";
*|  :units = "boolean";
*|  :type = caltype.uint8_0_5_CT;
*|  }
*|  .k_AEB_AllowOutFunAEBPRelease_str {
*|  :description = "AEBP will be release immediately when lateral corssing pedestrain walked outu of funnel";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRUHBMinConfEnblTime_str {
*|  :description = "Minimial time required for confidence satisfication to have High brake";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_HBHdTmAgeTrhd_str {
*|  :description = "Below this threshold, high brake timer shall be set to a small number";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VRUHBHdTmAgeTrhd_str {
*|  :description = "Below this threshold, high brake timer shall be set to a small number";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_ExtendUsePedHdTm_str {
*|  :description = "After Use ped was set to false, it will latech the use ped for this amount of time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_LastValHaloTime_str {
*|  :description = "Will latch the signals of last brake age and ID for this amount of time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_VRULBMinConf_str {
*|  :description = "Minimal confidence required for  low brake";
*|  :units = "boolean";
*|  :type = caltype.uint8_0_5_CT;
*|  }
*|  .k_AEB_VRULBMinConfEnblTm_str {
*|  :description = "Minimal amount of time require for low confidence check satisfication";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_IDChangeHaloTime_str {
*|  :description = "ID change hold time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_HiSpdGasRateEntryTrhd_str {
*|  :description = "gas pedal position rate threshold to inhibit AEB under high speed mode";
*|  :units = "none";
*|  :type = caltype.int16_m500_500_CT;
*|  }
*|  .k_AEB_HiSpdGasRateExitTrhd_str {
*|  :description = "gas pedal position rate relay threshold to inhibit AEB under high speed mode";
*|  :units = "none";
*|  :type = caltype.int16_m500_500_CT;
*|  }
*|  .k_AEB_HiSpdGasRateEnTime_str {
*|  :description = "min time required to to active gas pedal inhibit under high speed";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_HiSpdGasInhibtHdTm_str {
*|  :description = "latch time when gas pedal inhibit was actived under high speed mode";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_UnIdeLowestConfInPathTrhd_str {
*|  :description = "Minimal In-path age need to be waitted for AEB engage under lowest confidence for un-identified vehi\
*|  cle target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_UnIdeLowConfInPathTrhd_str {
*|  :description = "Minimal In-path age need to be waitted for AEB engage under low confidence for un-identified vehicle\
*|   target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_UnIdeMedConfInPathTrhd_str {
*|  :description = "Minimal In-path age need to be waitted for AEB engage under low confidence for un-identified vehicle\
*|   target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_UnIdeHiConfInPathTrhd_str {
*|  :description = "Minimal In-path age need to be waitted for AEB engage under low confidence for un-identified vehicle\
*|   target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_LowestConfInPathAgeTrhd_str {
*|  :description = "Minimal In-path age need to be waitted for AEB engage under lowest confidence";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_TTCReduceLatOfstBrkPoint_str {
*|  :description = "Break points of lateral offset exceed the minimal threshold, which no TTC reductionw will applied";
*|  :units = "m";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_HiConfLBTTCReduceFactor_str {
*|  :description = "Low brake TTC reduction factor that will apply to original TTC threshold when lateral offset detecte\
*|  d on non-corssing target";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_HiConfHBTTCReduceFactor_str {
*|  :description = "High brake TTC reduction factor that will apply to original TTC threshold when lateral offset detect\
*|  ed on non-corssing target";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_HiConfDBSTTCReduceFactor_str {
*|  :description = "IBA TTC reduction factor that will apply to original TTC threshold when lateral offset detected on n\
*|  on-corssing target";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_NoTTCReduceLatEstTrhd_str {
*|  :description = "AEB VRU TTC will have no reduction when its lateral estimate less than this threshold";
*|  :units = "m";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_LastBrkYposHaloTime_str {
*|  :description = "Will latch the signals of last brake Ypos and ID for this amount of time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_VRUFusHiConfLvl_str {
*|  :description = "Fusion high confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_AEB_VRUFusMedConfLvl_str {
*|  :description = "Fusion medium confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_AEB_VRUVisMedConfLvl_str {
*|  :description = "vision medium confidence level";
*|  :units = "uint8";
*|  :type = caltype.uint8_1_10_CT;
*|  }
*|  .k_AEB_FusHiMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion high confidence le\
*|  vel crossing target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_FusHiMinInPAgeTrhdLong_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion high confidence le\
*|  vel longitudinal target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_FusMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion medium confidence \
*|  level crossing target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VisMedMinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for vision on medium confiden\
*|  ce level crossing target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VisMedMinInPAgeTrhdLong_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for vision medium confidence \
*|  level longitudinal target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_FusMedMinInPAgeTrhdLong_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for Fusion medium confidence \
*|  level longitudinal target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_MinInPAgeTrhd_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for low confidence level cros\
*|  sing target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_MinInPAgeTrhdLong_str {
*|  :description = "Minimal in path age that has to wait before steady selection confirmed for lowh confidence level lon\
*|  gitudinal target";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_DrvBrkVRURlsEnTime_str {
*|  :description = "Minimal time required for driver to release VRU high brake through applying braking pressure above a\
*|   threshold value";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_GeneralSpdPoints_str {
*|  :description = "Speed point input of a table that determine maximum range allowed for high brake holder.";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_OvtkMaxTTCTrhd_str {
*|  :description = "driver ovetake TTC reduction will not affect when TTC large than this value";
*|  :units = "sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_OTMinXolcPercent_str {
*|  :description = "driver ovetake TTC reduction will not affect when xolc less than this value*half vehicle width";
*|  :units = "m";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_OneWayXolcChgCountTrhd_str {
*|  :description = "Xolc shall either continuesly increase or decrease for this amount of cycle before driver overtaking\
*|   can be initialied.";
*|  :units = "none";
*|  :type = caltype.uint8_0_32_CT;
*|  }
*|  .k_AEB_OvtkGasPdlHaloTime_str {
*|  :description = "How long driver pressing gas pedal for overtaking will be hold after he release the gas";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_OvtkReducHaloTime_str {
*|  :description = "How long driver overtaking will be hold after trigger";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_TTCReduceXolcBrkPoint_str {
*|  :description = "xolc input of TTC reduction factor table";
*|  :units = "mps";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_PrefillTTCReduceFactor_str {
*|  :description = "TTC reduction factor of prefill when driver overtaking is identified";
*|  :units = "m";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_LowTTCReduceFactor_str {
*|  :description = "TTC reduction factor of low brake when driver overtaking is identified";
*|  :units = "none";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_HBTTCReduceFactor_str {
*|  :description = "TTC reduction factor high brake when driver overtaking is identified";
*|  :units = "none";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_DBSTTCReduceFactor_str {
*|  :description = "TTC reduction factor of IBA when driver overtaking is identified";
*|  :units = "none";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_NeedDecelFilterGain_str {
*|  :description = "low pass filter gain of close loop need decel output";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_UseTrackerLeadAeecl_str {
*|  :description = "When this value set to true, close loop AEB will use lead acceleration reported by tracker directly";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_LeadVehDecelTrhd_str {
*|  :description = "Below this threshold, TTC before fully stop will used instead of raw TTC when calculating close loop\
*|   AEB required decel";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_DecelDiffBrkPoints_str {
*|  :description = "break points of deceleration gap between command decel and IMU";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_ESPSettlingTime_str {
*|  :description = "time for ESP to take before it can achieve commmand deceleration.";
*|  :units = "sec";
*|  :type = caltype.single_m1_1_CT;
*|  }
*|  .k_AEB_DesireStopDistance_str {
*|  :description = "What is the target minimal stop distance between ego vehicle and target vehicle before AEB can exit.";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_UseCloseLoopDecel_str {
*|  :description = "When this value set to true, AEB will send out calculated deceleration in real time.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_CLRampDownFactor_str {
*|  :description = "Ramp down factor used close loop deceleration command that send out";
*|  :units = "mpss";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_CLDecelBrkRelseTrhd_str {
*|  :description = "Threshold value of deceleration value that can determine brake is no longer requried.";
*|  :units = "mpss";
*|  :type = caltype.single_m5_5_CT;
*|  }
*|  .k_AEB_CLDecelBrkRelseEnTime_str {
*|  :description = "Minimal time required before high brake release can be trigger by close loop command deceleration";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_EgoTartAccelBrkPoints_str {
*|  :description = "break points of absoultely value of deceleration of both ego vehicle and target vehicle";
*|  :units = "mpss";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_TartInforFilterGain_str {
*|  :description = "table of low pass filter gain used for target lead velocity and lead acceleartion reported by tracke\
*|  r";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_TartLeadSpdOffset_str {
*|  :description = "ego vehicle need to have this amount of speed less than lead vehicle before AEB can";
*|  :units = "mps";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_LBDrvEngReducFactor_str {
*|  :description = "Low brake will be trigger using its normal TTC times this amount of factor to achieve delay effect.";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_HBDrvEngReducFactor_str {
*|  :description = "High brake will be trigger using its normal TTC times this amount of factor to achieve delay effect.";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_DBSDrvEngReducFactor_str {
*|  :description = "IBA will be trigger using its normal TTC times this amount of factor to achieve delay effect.";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_PFDrvEngReducFactor_str {
*|  :description = "prefill will be trigger using its normal TTC times this amount of factor to achieve delay effect.";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_VehDBSDrvEngTypeSltd_str {
*|  :description = "Vehicle high brake will be inhibit by driver engage manuver by following type: 1 driver steer;2drive\
*|  r brake; 4driver accel";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_IgrDBSDrvEng_str {
*|  :description = "when this set to true, driver enagge will not affect IBA function";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_PredTimeRRBrkPoint_str {
*|  :description = "break points of rangerate used determine predict time for close loop deceleration calculation";
*|  :units = "mps";
*|  :type = caltype.single_m20_20_CT;
*|  }
*|  .k_AEB_PredTimeRAccelBrkPoint_str {
*|  :description = "break points of range acceleration used determine predict time for close loop deceleration calculati\
*|  on";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_MaxPredictTime_str {
*|  :description = "table value of prediction time used to calculation close loop required deceleration.";
*|  :units = "sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_DrvEngUseTTCReduc_str {
*|  :description = "When this is set to true, AEB will be delay when driver engage detected.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_NoESPDisDecelTrhd_str {
*|  :description = "no limination deceleration value that below which ESP delay distance will no longer be applied for t\
*|  he calculation of ego allowed distance.";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_NoESPDisRangeTrhd_str {
*|  :description = "no limination range value that below which ESP delay distance will no longer be applied for the calc\
*|  ulation of ego allowed distance.";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_EgoAllowDisScalFactor_str {
*|  :description = "Scalling factor used to calculate deltaspd_needdecel, default value is 2 while it can be used to adj\
*|  uts system response.";
*|  :units = "none";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_EgoHiDynamicAccelTrhd_str {
*|  :description = "absoultely value of ego acceleration/deceleration thereshold above which ego vehicle is believed und\
*|  er high dynamic state.";
*|  :units = "mpss";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_LongVelFullHiDymic_str {
*|  :description = "absoultely thereshold value of target velocity above which true value will be used under ego vehicle\
*|   high dynamic state";
*|  :units = "mps";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_LongVelFull_str {
*|  :description = "absoultely thereshold value of target velocity above which true value will be used";
*|  :units = "mps";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_LongVelNegliHiDymic_str {
*|  :description = "absoultely thereshold value of target velocity below which value will be ignored under ego vehicle h\
*|  igh dynamic state";
*|  :units = "mps";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_LongVelNegli_str {
*|  :description = "absoultely thereshold value of target velocity below which value will be ignored";
*|  :units = "mps";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_MovLeadVelNegliEnTime_str {
*|  :description = "Lead speed of moveable target has to less than threshold value for consective amount of time.";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_MovLeadVelNegliHaloTime_str {
*|  :description = "How long lead vehicle speed will be ignored";
*|  :units = "msec";
*|  :type = caltype.uint16_0_50000_CT;
*|  }
*|  .k_AEB_NonProceedVRUFullChkEnbl_str {
*|  :description = "Enable full brake condition check for nbsm/crossing vru";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_ESPDelayDisFadingTime_str {
*|  :description = "How many cycles for close loop AEB to fading the ESP delay distance affect when it comes to close ra\
*|  nge";
*|  :units = "sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_AccuAngEgoStopHaloTime_str {
*|  :description = "How long lead vehicle speed will be ignored";
*|  :units = "msec";
*|  :type = caltype.uint32_0_100000_CT;
*|  }
*|  .k_AEB_MaxAllowVehHeadAngTime_str {
*|  :description = "Maximum time allowed for vehicle heading angle accumulation in one time";
*|  :units = "Sec";
*|  :type = caltype.single_0_60_CT;
*|  }
*|  .k_AEB_TTTUseTrtWidth_str {
*|  :description = "Target vehicle width will be used for TTT calculation, otherwise use host vehicle width instead";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_TTTPersistXolcTrhd_str {
*|  :description = "TTT will not change until target xolc large than this threshold";
*|  :units = "meter";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_BrkPressurePositionSel_str {
*|  :description = "the swithc value of Brake pressure/Brake position";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_HiBrkUseRangeTrigger_str {
*|  :description = "When this is set to true, AEB high brake will be trigger using range threshold instead of TTC thresh\
*|  old";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HiBrkTrigMovRangeOffset_str {
*|  :description = "Rangerate based AEB high braking range threshold offset";
*|  :units = "m";
*|  :type = caltype.single_m20_20_CT;
*|  }
*|  .k_AEB_HiBrkTrigStatRangeOffset_str {
*|  :description = "Ego speed based AEB high braking range threshold offset";
*|  :units = "m";
*|  :type = caltype.single_m20_20_CT;
*|  }
*|  .k_AEB_LoBrkTrigMovDuration_str {
*|  :description = "Rangerate based AEB low braking duration offset before high brake";
*|  :units = "sec";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_LoBrkTrigStatDuration_str {
*|  :description = "Ego speed based AEB low braking duration offset before high brake";
*|  :units = "sec";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_PrefillTrigMovDuration_str {
*|  :description = "Rangerate based AEB prefill duration offset before low brake";
*|  :units = "sec";
*|  :type = caltype.single_0_3_CT;
*|  }
*|  .k_AEB_PrefillTrigStatDuration_str {
*|  :description = "Ego speed based AEB prefill duration offset before low brake";
*|  :units = "sec";
*|  :type = caltype.single_0_3_CT;
*|  }
*|  .k_AEB_FLBATrigMovDuration_str {
*|  :description = "Rangerate based AEB FLBA duration offset before low brake";
*|  :units = "sec";
*|  :type = caltype.single_0_3_CT;
*|  }
*|  .k_AEB_FLBATrigStatDuration_str {
*|  :description = "Ego speed based AEB FLBA duration offset before low brake";
*|  :units = "sec";
*|  :type = caltype.single_0_3_CT;
*|  }
*|  .k_AEB_MinStopTrigMovDuration_str {
*|  :description = "Rangerate based AEB MinStop duration offset before low brake";
*|  :units = "sec";
*|  :type = caltype.single_0_3_CT;
*|  }
*|  .k_AEB_MinStopTrigStatDuration_str {
*|  :description = "Ego speed based AEB MinStop duration offset before low brake";
*|  :units = "sec";
*|  :type = caltype.single_0_3_CT;
*|  }
*|  .k_AEB_FusionFLBAMaskWrd_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_FusionPFMaskWrd_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_FusionLBMaskWrd_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_FusionHBMaskWrd_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_FusionFBMaskWrd_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_FusionVRUFLBAMaskWrd_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_FusionVRUPFMaskWrd_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_FusionVRULBMaskWrd_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_FusionVRUHBMaskWrd_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_FusionVRUFBMaskWrd_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_FusionVRUTOIMaskWrd_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_VehWithIboostNoESP_str {
*|  :description = "Set to one if vehicle is iboost not ESP";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_PedEnable_str {
*|  :description = "Enable AEB braking to pedestraian and cyclist";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreDecelCheckInPCS_str {
*|  :description = "When this value set to true, PCS entry gate will ignore deceleration check fot ego vehicle.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DesiredVehHitSpd_str {
*|  :description = "desired hit speed with vehicle target";
*|  :units = "m/s";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_FullBrkLvl_mps_offset_str {
*|  :description = "full brake deceleration value offset when calculating full duration time";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_HiBrkLvl_mps_offset_str {
*|  :description = "High brake deceleration value offset when calculating high duration time";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_Adjust_XOLC_MovementLimit_str {
*|  :description = "Adjust Movement in limits of TOI";
*|  :units = "none";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_LongBikePFDuration_str {
*|  :description = "Annoy duration between prefill and low brake for VRU";
*|  :units = "Sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_DBSMaxDecel_mps_str {
*|  :description = "Max activation deceleration for IBA";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_VRUMinTTC_sec_str {
*|  :description = "VRU min TTC check threshold";
*|  :units = "Sec";
*|  :type = caltype.single_m25p5_25p5_CT;
*|  }
*|  .k_AEB_PFNearTrgt_RedFac_str {
*|  :description = "TTC reduction for too many VRUs near interested VRU for prefill";
*|  :units = "";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_LBNearTrgt_RedFac_str {
*|  :description = "TTC reduction for too many VRUs near interested VRU for LB";
*|  :units = "";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_HBNearTrgt_RedFac_str {
*|  :description = "TTC reduction for too many VRUs near interested VRU for HB";
*|  :units = "";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_NearTrgt_KneePoints_str {
*|  :description = "VRUs number knee points";
*|  :units = "";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_AEB_enb_veh_sta_check_str {
*|  :description = "Set to one if enable status check for veh coasted status";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_veh_coasted_enb_cont_str {
*|  :description = "AEB veh valid counter when status changes from updated to coasted";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_InpathNowReduceFactor_str {
*|  :description = "Reduction factor of Inpath now xolc when steering wheel angle rate is high";
*|  :units = "m";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_InpathLaterReduceFactor_str {
*|  :description = "Reduction factor of Inpath later xolc when steering wheel angle rate is high";
*|  :units = "m";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_StrAngRtLatEstReduceFac_str {
*|  :description = "Reduction factor of VRU latearl offest when steering wheel angle rate is high";
*|  :units = "m";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_StrAngRatePoints_str {
*|  :description = "Steering wheel angle rate";
*|  :units = "m";
*|  :type = caltype.single_0_500_CT;
*|  }
*|  .k_AEB_BrkInhibitLowSpdTrhd_str {
*|  :description = "When speed below this thres, brake pedal AEB inhibit will switch to low speed mode";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_BrkInhibitHiSpdTrhd_str {
*|  :description = "When speed above this thres, brake pedal AEB inhibit will switch to high speed mode";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_HiSpdBrkEngageHdTm_str {
*|  :description = "Brake pedal engage hold time in high spd";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_BrkEngagePresFactor_str {
*|  :description = "Brake pedal pressure engagement factor";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_HiSpdBrkEngagePresFactor_str {
*|  :description = "Brake pedal pressure engagement factor in high speed";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_HiSpdBrkEngPosEntryTrhd_str {
*|  :description = "Brake pedal position threshold to inhibit AEB in high speed";
*|  :units = "none";
*|  :type = caltype.uint8_0_100_CT;
*|  }
*|  .k_AEB_VRULatEstFunnelExitFac_str {
*|  :description = "When AEB brake for VRU is active, Lateral estimate offset limit will be higher.";
*|  :units = "none";
*|  :type = caltype.single_1_2_CT;
*|  }
*|  .k_AEB_HiSpdBrkEngPosExitTrhd_str {
*|  :description = "brake position threshold relay in high speed";
*|  :units = "none";
*|  :type = caltype.uint8_0_100_CT;
*|  }
*|  .k_AEB_VRUPFVehBehType_str {
*|  :description = "VRU prefill will be delayed by vehicle behavior  by following type: 1. Wipper; 2. HazLight; 3. Left \
*|  turning lamp; 4. Right turning lamp";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VRULBVehBehType_str {
*|  :description = "VRU low brake will be delayed by vehicle behavior  by following type: 1. Wipper; 2. HazLight; 3. Lef\
*|  t turning lamp; 4. Right turning lamp";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VRUHBVehBehType_str {
*|  :description = "VRU high brake will be delayed by vehicle behavior  by following type: 1. Wipper; 2. HazLight; 3. Le\
*|  ft turning lamp; 4. Right turning lamp";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VRUPFVBCTTCRedFac_str {
*|  :description = "prefill TTC reduction according to vehicle behavior";
*|  :units = "";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_VRULBVBCTTCRedFac_str {
*|  :description = "LB TTC reduction according to vehicle behavior";
*|  :units = "";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_VRUHBVBCTTCRedFac_str {
*|  :description = "HB TTC reduction according to vehicle behavior";
*|  :units = "";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_IgrHiBrkVehBeh_str {
*|  :description = "When set to true, veh high brake will not consider vehicle behavior";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRUHBInhVehBehType_str {
*|  :description = "Veh high brake will be inhibited by vehicle behavior  by following type: 1. Wipper; 2. HazLight; 3. \
*|  Left turning lamp; 4. Right turning lamp";
*|  :units = "none";
*|  :type = caltype.uint32_0_255_CT;
*|  }
*|  .k_AEB_VehBehChkLowSpdTrhd_str {
*|  :description = "When speed below this thres, vehicle behavior check will switch to low speed mode";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_VehBehChkHiSpdTrhd_str {
*|  :description = "When speed above this thres, vehicle behavior check will switch to high speed mode";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_StrRateReductionHdTm_str {
*|  :description = "steering angle rate reduction hold time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_StrReductionHdTm_str {
*|  :description = "steering angle reduction hold time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_BrkReductionHdTm_str {
*|  :description = "brake reduction hold time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_GasPdlReductionHdTm_str {
*|  :description = "gas pedal reduction hold time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_GasPdlReductionEntryTrhd_str {
*|  :description = "gas pedal position entry threshold for driver reduction";
*|  :units = "none";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_GasPdlReductionExitTrhd_str {
*|  :description = "gas pedal position exit threshold for driver reduction";
*|  :units = "none";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_StrRateReductionEntryTrhd_str {
*|  :description = "steering angle rate entry threshold for driver reduction";
*|  :units = "none";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_StrRateReductionExitTrhd_str {
*|  :description = "steering angle rate exit threshold for driver reduction";
*|  :units = "none";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_StrReductionEntryTrhd_str {
*|  :description = "steering angle entry threshold for driver reduction";
*|  :units = "none";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_StrReductionExitTrhd_str {
*|  :description = "steering angle exit threshold for driver reduction";
*|  :units = "none";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_StrRateReductionFactor_str {
*|  :description = "steering angle rate reduction factor";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_StrReductionFactor_str {
*|  :description = "steering angle reduction factor";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_BrkReductionFactor_str {
*|  :description = "brake reduction factor";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_GasPdlReductionFactor_str {
*|  :description = "gas pedal reduction factor";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_BrkReductionSource_str {
*|  :description = "brake reduction signal source selection";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRUFLBAVehBehType_str {
*|  :description = "VRU FLBA will be delayed by vehicle behavior  by following type: 1. Wipper; 2. HazLight; 3. Left tur\
*|  ning lamp; 4. Right turning lamp";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VRUFLBAVBCTTCRedFac_str {
*|  :description = "FLBA TTC reduction according to vehicle behavior";
*|  :units = "";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_GateMinRangeVRU_str {
*|  :description = "Minimal range below which the is no discrimination for VRU";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_ClsFstDectVRUIPAOffset_str {
*|  :description = "Number of cycles that will add to VRU normal in-path age when their first detected range is less tha\
*|  n this value.";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_RoadCondLowSpdTrhd_str {
*|  :description = "When speed below this thres, vehicle behavior check will switch to low speed mode";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_RoadCondHiSpdTrhd_str {
*|  :description = "When speed above this thres, vehicle behavior check will switch to high speed mode";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_VRUNumThres_str {
*|  :description = "min number of VRU when it is VRU road situation";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VRURadarLatErrThres_str {
*|  :description = "VRU permited lateral error between fusion information and radar information";
*|  :units = "m";
*|  :type = caltype.single_0_150_CT;
*|  }
*|  .k_AEB_VRUVisionLongErrThres_str {
*|  :description = "VRU permited longitude error between fusion information and vision information";
*|  :units = "m";
*|  :type = caltype.single_0_150_CT;
*|  }
*|  .k_AEB_VRUXolcChkLowSpdTrhd_str {
*|  :description = "When speed is below this thres, it will check VRU xolc if it is in vehicle width.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_VRUXolcChkHiSpdTrhd_str {
*|  :description = "When speed is above this thres, it will check VRU xolc if it is in vehicle width.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_MomErrorThresLong_str {
*|  :description = "Longitudinal momentary error check will fail when moment error exceed this threshold value";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_VehMomErrorThresLong_str {
*|  :description = "Longitudinal momentary error check will fail when moment error exceed this threshold value";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_TrtRangRateBrkPoints_str {
*|  :description = "When speed is above this thres, it will check VRU xolc if it is in vehicle width.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_TrtLatRRBrkPoints_str {
*|  :description = "Lateral relative speed break points";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_MomErrorThresLat_str {
*|  :description = "Lateral momentary error check will fail when momentary error exceed this threshold value";
*|  :units = "m/sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_VRUXolcChkVelGapThres_str {
*|  :description = "min VRU long velocity and lat velocity gap when do VRU XOLC check.(According to long proceeding VRU \
*|  condition)";
*|  :units = "m/sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_VRUXolcChkLongVelThres_str {
*|  :description = "min VRU long velocity thres when do VRU XOLC check.(According to long proceeding VRU condition)";
*|  :units = "m/sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_DesireStopDistanceLowSpd_str {
*|  :description = "What is the target minimal stop distance between ego vehicle and target vehicle before AEB can exit.\
*|   (low speed condition)";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_VRUHiSpdCrossThres_str {
*|  :description = "Speed threshold which determines it is a high VRU crossing situation.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_VRUHiSpdCrossXolcLimit_str {
*|  :description = "When it is a high VRU crossing situation, xolc should be limited in this thres.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_VRUMinReductionFac_str {
*|  :description = "The minimum reduction factor for VRUAEB TTC";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_VehMinReductionFac_str {
*|  :description = "The minimum reduction factor for VehAEB";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_VehBasicCheckFailHldTime_str {
*|  :description = "When Vehicle kinematics check fails, the fail will hold";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_VRUBasicCheckFailHldTime_str {
*|  :description = "When VRU kinematics check fails, the fail will hold";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_TrgtNumTrhdForVRUCmplx_str {
*|  :description = "When the object number of near range is higher than this value, AEB VRU TTC threshold will be redued";
*|  :units = "none";
*|  :type = caltype.uint8_0_15_CT;
*|  }
*|  .k_AEB_TrgtNumTrhdForVehCmplx_str {
*|  :description = "When the object number of near range is higher than this value, AEB Vehicle TTC or range threshold w\
*|  ill be redued";
*|  :units = "none";
*|  :type = caltype.uint8_0_15_CT;
*|  }
*|  .k_AEB_VehCmplxReduceFac_str {
*|  :description = "AEBVRU reduce factor for large object number of near range";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_VRUCmplxReduceFac_str {
*|  :description = "AEBVeh reduce factor for large object number of near range";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_VRUHBMinReductionFac_str {
*|  :description = "The minimum reduction factor for VRUAEB TTC in HB";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_VehHBMinReductionFac_str {
*|  :description = "The minimum reduction factor for VehAEB";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_NotChkSpdInFB_str {
*|  :description = "When this varible is set to 0, vehicle spped will be chekced so that if speed is higher than full br\
*|  ake maximum speed during full brake, AEB will exit.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_RE_EndRangeOffset_str {
*|  :description = "The offset for end distance of road edge.";
*|  :units = "m";
*|  :type = caltype.single_m5_5_CT;
*|  }
*|  .k_AEB_RE_StartRangeOffset_str {
*|  :description = "The offset for start distance of road edge.";
*|  :units = "m";
*|  :type = caltype.single_m5_5_CT;
*|  }
*|  .k_AEB_Reduce_GasPdlTrhd_str {
*|  :description = "When gas pedal is higher than this value, AEB active threshold will be reduced.";
*|  :units = "none";
*|  :type = caltype.single_0_255_CT;
*|  }
*|  .k_GasPdlReduceDelayTime_str {
*|  :description = "Delay time for gas pedel reduction acitive";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_Use_TTE_In_CCR_str {
*|  :description = "When this varible is set to 0, AEB CCR TTC threshold will not consider TTB and TTT, which is useful \
*|  for commercial vehicle.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_MinLostRangeVRU_str {
*|  :description = "Minimal lost range of VRU";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_MinLostLatPosVRU_str {
*|  :description = "Minimal lost lat pos of VRU";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_MinLostRangeVeh_str {
*|  :description = "Minimal lost range of Veh";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_MinLostLatPosVeh_str {
*|  :description = "Minimal lost lat pos of Veh";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_CloseLostHold_Enabled_str {
*|  :description = "For commercial vehicle, set the value 1 to enable close target lost hold function, and for passenger\
*|   vehicle, set the value to 0";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_MinLostLatEstVRU_str {
*|  :description = "Minimal lost lat estimated pos of VRU";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_GdRail_RangeOffset_str {
*|  :description = "The offset for range of guardrail";
*|  :units = "m";
*|  :type = caltype.single_m5_5_CT;
*|  }
*|  .k_AEB_NearTrgt_RedFac_str {
*|  :description = "TTC reduction for too many VRUs near interested VRU";
*|  :units = "";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_VRUVehBehType_str {
*|  :description = "AEBVRU will be delayed by vehicle behavior  by following type: 1. Wipper; 2. HazLight; 3. Left turni\
*|  ng lamp; 4. Right turning lamp";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VRUVBCTTCRedFac_str {
*|  :description = "AEBVRU TTC reduction according to vehicle behavior";
*|  :units = "";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_TTBAvgBrkDelay_Full_str {
*|  :description = "Average brake system delay during full";
*|  :units = "Sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_HiToFuBrakingLvlMov_mps_str {
*|  :description = "High to full brake deceleration value applied to moveable objects";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_LwBrakingLvl_Factor_str {
*|  :description = "AEB low braking deceleration factor according to AEB CCR range based AEB low brake period";
*|  :units = "m/sec^2";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_UseCSMdlToLwBrkRngCal_str {
*|  :description = "Use constant speed model for target vehicle according to low brake range threshold calculation";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_CloseLost_VRUEnableMask_str {
*|  :description = "AEBVRU Close lost mask: bit0-moveable;bit1-NBSM;bit2-Stop;bit3-Crossing;bit4-Proceeding;bit5-OC.";
*|  :units = "none";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_DBSStatTimeGap_str {
*|  :description = "The time gap is used to calculate the distance for IBA  (Stationary object)";
*|  :units = "sec";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_DBSMovTimeGap_str {
*|  :description = "The time gap is used to calculate the distance for IBA  (moveable object)";
*|  :units = "sec";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_DBSUseRangeTrigger_str {
*|  :description = "When this is set to true, IBA will be trigger using range threshold instead of TTC threshold";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_TTCAccelBasedCalMode_str {
*|  :description = "When this is set to true, TTC calculation method will consider the lead vehcile speed lower limit.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DBSBrakingLvl_Factor_str {
*|  :description = "AEB low braking deceleration factor according to AEB CCR range based IBA brake period";
*|  :units = "m/sec^2";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_LowBrkMaxRangeStat_str {
*|  :description = "If the range is higher than this value, Low brake will not be activr for stationary target";
*|  :units = "m";
*|  :type = caltype.single_0_150_CT;
*|  }
*|  .k_AEB_LowBrkMaxRangeMov_str {
*|  :description = "If the range is higher than this value, Low brake will not be activr for moving target";
*|  :units = "m";
*|  :type = caltype.single_0_150_CT;
*|  }
*|  .k_AEB_MovTrgtFlyInMaxRange_str {
*|  :description = "Higher than this value, will not be considered as fly-in target (moving).";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_StatTrgtFlyInMaxRange_str {
*|  :description = "Higher than this value, will not be considered as fly-in target (Stationary).";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_TrgtFlyInMaxLatPos_str {
*|  :description = "Higher than this value, will not be considered as fly-in target";
*|  :units = "m";
*|  :type = caltype.single_0_3_CT;
*|  }
*|  .k_AEB_TrgtFlyInMaxAge_str {
*|  :description = "Target's age higher than this value, the target will not be considered as fly-in object";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_FlyInDectIPAOffset_str {
*|  :description = "Number of cycles that will add to normal in-path age when targets fly in";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_DBSBrkMaxStatRange_str {
*|  :description = "Maximum IBA range for Moveable objects";
*|  :units = "m";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AEB_DBSBrkMaxMovRange_str {
*|  :description = "Maximum IBA range for stationary objects";
*|  :units = "m";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AEB_ExtraInpathAgeCounter_z_str {
*|  :description = "Extra in path age counter look up table";
*|  :units = "none";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AEB_ExtraInpathAgeCounter_x_str {
*|  :description = "Extra in path age counter look up table, X input(host speed)";
*|  :units = "m/sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_ExtraInpathAgeCounter_y_str {
*|  :description = "Extra in path age counter look up table, Y input(Yaw rate)";
*|  :units = "deg/sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_LongBikeHB_TTCMax_str {
*|  :description = "Max TTC for CBLA high brake";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_LongBikeLB_TTCMax_str {
*|  :description = "Max TTC for CBLA low brake";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_LongBikePF_TTCMax_str {
*|  :description = "Max TTC for CBLA prefill";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_VRUNoPredictLongVelThres_str {
*|  :description = "Long velocity threshold if only considering VRU's current position as selecting evidence.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_ROCDecelLimit_tbl_y_str {
*|  :description = "When the vehicle is in a narrow curve, Deceleration will be limit -table output";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_AEB_ROCDecelLimit_tbl_x_str {
*|  :description = "When the vehicle is in a narrow curve, Deceleration will be limit -table Input";
*|  :units = "m";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_LoadDecelLimit_tbl_y_str {
*|  :description = "When the load of vehicle is high, Deceleration will be limit -table Output";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_AEB_LoadDecelLimit_tbl_x_str {
*|  :description = "When the load of vehicle is high, Deceleration will be limit -table Input";
*|  :units = "kg";
*|  :type = caltype.single_0_100000_CT;
*|  }
*|  .k_AEB_SpdDecelLimit_tbl_y_str {
*|  :description = "When the velocity of vehicle is high, Deceleration will be limit -table Output";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_AEB_SpdDecelLimit_tbl_x_str {
*|  :description = "When the velocity of vehicle is high, Decelaration will be limit -table Intput";
*|  :units = "m/sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_VRU_BrkRls_en_str {
*|  :description = "When this value is ture, speed reduction will be limited for VRU object.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRU_SpdReduction_max_str {
*|  :description = "Maximum speed reduction limited for VRU object.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_BrkAct_LimitDecel_en_str {
*|  :description = "When this value is ture, if brake pedal pressed and IMU longitudinal acceleration is low, AEB decele\
*|  ration will be limited";
*|  :units = "m/sec";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DetBrkAct_AccelMax_str {
*|  :description = "When k_AEB_BrkAct_LimitDecel_en is ture, if brake pedal pressed and IMU longitudinal acceleration lo\
*|  wer than this value, AEB deceleration will be limited";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_AEB_PedDecelerateDetectAccel_str {
*|  :description = "Ped deceleration detection acceleration threshold";
*|  :units = "mpss";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_TWDecelerateDetectAccel_str {
*|  :description = "TW deceleration detection acceleration threshold";
*|  :units = "mpss";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_VRUDecelerateDetectHdTm_str {
*|  :description = "VRU deceleration detection hold time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_XolcLaterEntryGate_str {
*|  :description = "Threshold for checking xolc later when aeb is not active.";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_XolcLaterExitGate_str {
*|  :description = "Threshold for checking xolc later when aeb is active.";
*|  :units = "m";
*|  :type = caltype.single_0_12p5_CT;
*|  }
*|  .k_AEB_IniMethodVRUIPAOffset_str {
*|  :description = "Number of cycles that will add to VRU normal in-path age when VRU initail method is not mature.";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_HldRls_AccelPos_str {
*|  :description = "Gas pedal position above this value, Hold will be release";
*|  :units = "percent";
*|  :type = caltype.uint8_0_100_CT;
*|  }
*|  .k_AEB_CCRB_MinActiveAccel_str {
*|  :description = "When the object accelearion is above this value, CCRB scenario will be ignored";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_AEB_CCRB_ActiveDelay_str {
*|  :description = "Delay time for CCRB acitive";
*|  :units = "sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_CCRB_ActiveDelaySpdPoints_str {
*|  :description = "Speed points for CCRB acitive delay time.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_CCRB_IgnoreClassCheck_str {
*|  :description = "CCRB will not check object class whether it is car, truck or motorcycle. If false, AEB will not trig\
*|   for motorcycle";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_CCRB_ActiveHldTime_str {
*|  :description = "Hold time for CCRB acitive";
*|  :units = "msec";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_HldAllowMaxVRUSpd_str {
*|  :description = "If the Long speed of VRU obj is above this value, hold will not be allowed.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_HldAllowMaxVehSpd_str {
*|  :description = "If the Long speed of Veh obj is above this value, hold will not be allowed.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_HldAllowMaxVRURange_str {
*|  :description = "If the range of VRU obj is above this value, hold will not be allowed.";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_HldAllowMaxVehRange_str {
*|  :description = "If the range of Veh obj is above this value, hold will not be allowed.";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_HldEntryIgnObjCheck_str {
*|  :description = "If this value is false, object kinematics will be checked for hold";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HldRlsMinVRULatEst_str {
*|  :description = "If the LatEst of VRU obj is below than this value, hold will not release.";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_HldRlsMinVRULatPos_str {
*|  :description = "If the Lateral position of VRU obj is below than this value, hold will not release.";
*|  :units = "m";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_HldRlsMinVehLatEst_str {
*|  :description = "If the LatEst of Veh obj is below than this value, hold will not release.";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_HldRlsMinVehLatPos_str {
*|  :description = "If the  Lateral position of Veh obj is below than this value, hold will not release.";
*|  :units = "m";
*|  :type = caltype.single_0_3_CT;
*|  }
*|  .k_AEB_HldRlsMinVehSpd_str {
*|  :description = "If the Long speed of Veh obj is above this value, hold will be released.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_HldRlsMinVehRange_str {
*|  :description = "If the range of Veh obj is above this value, hold will be released.";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_HldRlsMinVRURange_str {
*|  :description = "If the range of VRU obj is above this value, hold will be released.";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_HoldBrkPdlPosThres_str {
*|  :description = "If drive brake pedal pos more than this value, hold will be released.";
*|  :units = "none";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_DrvActInHoldTm_str {
*|  :description = "If drive brake and hold this value time, hold will be released.";
*|  :units = "sec";
*|  :type = caltype.single_0_2000_CT;
*|  }
*|  .k_AEB_UseHoldTrigDly_str {
*|  :description = "Flag if use hold trig delay logic.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_CheckIniMethodMaxAge_str {
*|  :description = "When the age of VRU is above this value, the additional in-path age for initial will be ignored.";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_IBA_DecelCalMod_str {
*|  :description = "Mode switch for deceleration calculation method.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IBA_BypassBrkPosPrs_str {
*|  :description = "When this value is true, if IBA active, brake pedal position and pressure do not need to check";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IBA_BypassDecel_str {
*|  :description = "When this value is true, if IBA active, deceleration does not need to check";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreCBLATTBCal_str {
*|  :description = "Ignore TTC calculation output when tuning CBLA scenario.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HighSpdCrsLatVel_str {
*|  :description = "When VRU lat vel is beyond this threshold, it will use TWDecelerateDetectAccel.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_VehMaxAllowSpdStep_str {
*|  :description = "If obj veh speed change step is below this value, radar info will be checked pass.";
*|  :units = "mps";
*|  :type = caltype.single_m1_50_CT;
*|  }
*|  .k_AEB_VehMaxAllowAgeStep_str {
*|  :description = "If obj veh age change step is below this value, radar info will be checked pass.";
*|  :units = "m";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_IgnVRUInpathAgeChk_str {
*|  :description = "If this value is true, high brake will ignore in path age check";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VehRdrInfoChkFailHldTime_str {
*|  :description = "When radar info check fails, the fail will hold";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_VRUIDChgChkHoldTime_str {
*|  :description = "If VRU ID change during AEBVRU acti.ve, in path age check for high brake will not be ignored";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_VRUHiBrkIgnLatAccEn_str {
*|  :description = "If this value is true, high brake will ignore too high lateral acceleration.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_host_straightly_yaw_thrh_str {
*|  :description = "";
*|  :units = "Deg/sec";
*|  :type = caltype.single_0_15_CT;
*|  }
*|  .k_AEB_VRUHiBrkIgnLatEstEn_str {
*|  :description = "When this value is true, if the product of latpos and latest is less than 0, LatEst will not be chec\
*|  ked for High Brake";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRUHiBrkUseRangeTrigger_str {
*|  :description = "When this is set to true, AEB VRU high brake will be trigger using range threshold instead of TTC th\
*|  reshold";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_BikeHitSpdDes_mps_str {
*|  :description = "Desired collision velocity for crossing bike";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_BikeStatHitSpdDes_mps_str {
*|  :description = "Desired collision velocity for stationary bike";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_LongBikeHitSpdDes_mps_str {
*|  :description = "Desired collision velocity for proceeding bike";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_OCBikeHitSpdDes_mps_str {
*|  :description = "Desired collision velocity for oncoming bike";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_PedHitSpdDes_mps_str {
*|  :description = "Desired collision velocity for pedestrain";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_OCPedHitSpdDes_mps_str {
*|  :description = "Desired collision velocity for oncoming pedestrain";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_VRUTTBAvgBrkDelay_str {
*|  :description = "Average brake delay for VRU high brake range threshold calculation";
*|  :units = "Sec";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_VRUTTBAvgBrkDelay_Full_str {
*|  :description = "Average brake delay during full for VRU high brake range threshold calculation";
*|  :units = "Sec";
*|  :type = caltype.single_0_2_CT;
*|  }
*|  .k_AEB_DesHitSpdInputTbl_mps_str {
*|  :description = "Input for AEB VRU desired hit speed";
*|  :units = "m/sec";
*|  :type = caltype.single_0_30_CT;
*|  }
*|  .k_AEB_VRULowBrkMaxRng_m_str {
*|  :description = "Max range allowed for AEB VRU";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_VRULowBrkMaxTTC_sec_str {
*|  :description = "Max TTC allowed for VRU low brake";
*|  :units = "Sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_VRUPFMaxRng_m_str {
*|  :description = "Max range allowed for VRU prefill";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_VRUPFMaxTTC_sec_str {
*|  :description = "Max TTC allowed for VRU prefill";
*|  :units = "Sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_VRUPFTrigDuration_str {
*|  :description = "Rangerate based AEBVRU prefill duration offset before low brake";
*|  :units = "sec";
*|  :type = caltype.single_0_3_CT;
*|  }
*|  .k_AEB_VRUFLBATrigDuration_str {
*|  :description = "Rangerate based AEBVRU FLBA duration offset before low brake";
*|  :units = "sec";
*|  :type = caltype.single_0_3_CT;
*|  }
*|  .k_AEB_VRUMinStopTrigDuration_str {
*|  :description = "Rangerate based AEBVRU MinStop duration offset before low brake";
*|  :units = "sec";
*|  :type = caltype.single_0_3_CT;
*|  }
*|  .k_AEB_BikeLBDuration_sec_str {
*|  :description = "Low brake duration for crossing bike";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_BikeStatLBDuration_sec_str {
*|  :description = "Low brake duration for stationary bike";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_LongBikeLBDuration_sec_str {
*|  :description = "Low brake duration for proceeding bike";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_OCBikeLBDuration_sec_str {
*|  :description = "Low brake duration for oncoming bike";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_PedLBDuration_sec_str {
*|  :description = "Low brake duration for pedestrain";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_OCPedLBDuration_sec_str {
*|  :description = "Low brake duration for oncoming pedestrain";
*|  :units = "Sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_IgnoreEstHitDistChk_str {
*|  :description = "For veh in path later logic, ignore est hit distance check.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreEstYawDistChk_str {
*|  :description = "For veh in path later logic, ignore est yaw distance check.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreXolcLaterChk_str {
*|  :description = "For veh in path later logic, ignore xolc later check.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_NonCrsPed_MinSpd_mps_str {
*|  :description = "Min host speed to trigger AEB for non crossing pedestraian";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_NonCrsPed_LBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger AEB for non crossing pedestraian";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_CrsPed_LBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger AEB for crossing pedestraian";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_StatBike_LBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger AEB for stationary bike";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_CrsBike_LBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger AEB for crossing bike";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_LongBike_LBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger AEB for proceeding bike";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_OCPed_LBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger AEB for oncoming pedestrain";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_OCBike_LBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger AEB for Oncoming bike";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_CrsPed_HBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger high brake for crossing pedestraian";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_NonCrsPed_HBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger high brake for non crossing pedestraian";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_StatBike_HBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger high brake for stationary bike";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_CrsBike_HBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger high brake for crossing bike";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_LongBike_HBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger high brake for proceeding bike";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_OCPed_HBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger high brake for oncoming pedestrain";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_OCBike_HBMaxSpd_mps_str {
*|  :description = "Max host speed to trigger high brake for Oncoming bike";
*|  :units = "mps";
*|  :type = caltype.single_0_128_CT;
*|  }
*|  .k_AEB_BikeIBADuration_sec_str {
*|  :description = "IBA duration for crossing bike";
*|  :units = "m/sec";
*|  :type = caltype.single_m10_25p5_CT;
*|  }
*|  .k_AEB_BikeStatIBADuration_sec_str {
*|  :description = "IBA duration for stationary bike";
*|  :units = "m/sec";
*|  :type = caltype.single_m10_25p5_CT;
*|  }
*|  .k_AEB_LongBikeIBADuration_sec_str {
*|  :description = "IBA duration for proceeding bike";
*|  :units = "m/sec";
*|  :type = caltype.single_m10_25p5_CT;
*|  }
*|  .k_AEB_OCBikeIBADuration_sec_str {
*|  :description = "IBA duration for oncoming bike";
*|  :units = "m/sec";
*|  :type = caltype.single_m10_25p5_CT;
*|  }
*|  .k_AEB_PedIBADuration_sec_str {
*|  :description = "IBA duration for pedestrain";
*|  :units = "m/sec";
*|  :type = caltype.single_m10_25p5_CT;
*|  }
*|  .k_AEB_OCPedIBADuration_sec_str {
*|  :description = "IBA duration for oncoming pedestrain";
*|  :units = "Sec";
*|  :type = caltype.single_m10_25p5_CT;
*|  }
*|  .k_AEB_DBSBrkVRUMaxRange_str {
*|  :description = "Maximum IBA range for stationary objects";
*|  :units = "m";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AEB_DBSVRUMinSpdChkEnbl_str {
*|  :description = "When this set to true, minimal speed will be checked before VRU IBA allowed";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRUDBSMaxDecel_mps_str {
*|  :description = "Max activation deceleration for IBA";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_DBSVRUMinVehicleSpd_str {
*|  :description = "Minimal host speed for IBA to engage";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_IBAVRU_BypassDecel_str {
*|  :description = "When this value is true, if VRU IBA active, deceleration does not need to check";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_TWLatEstComp_str {
*|  :description = "Lat est compensation for TW when considering In_CIBPredictFunnel condition.";
*|  :units = "m";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_VRUHiBrkLvl_mps_offset_str {
*|  :description = "VRU High brake deceleration value offset when calculating high duration time";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_HiBrkLongBikeRangeOffset_str {
*|  :description = "Due to the distance between CoG and the closet point of bike";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_HiBrkRefRange_str {
*|  :description = "reference value for high brake range threshold";
*|  :units = "m";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_VRUHiBrkRefRange_str {
*|  :description = "reference value for VRU high brake range threshold";
*|  :units = "m";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_SpdReduction_max_str {
*|  :description = "Maximum speed reduction limited for VRU object.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_Veh_BrkRls_en_str {
*|  :description = "When this value is ture, speed reduction will be limited for Veh object.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_BrkPdlEngageLgAccThres_str {
*|  :description = "Host long acceleration threshold while checking driver brake engage";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_BrkPosConfirmEn_str {
*|  :description = "If this value is false, AEB will take brake pedal position into consideration no matter which kind o\
*|  f braking actuator is.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_BrkPrsConfirmEn_str {
*|  :description = "If this value is false, AEB will take master cylinder pressure into consideration no matter which ki\
*|  nd of braking actuator is.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRULoBrkIgnLatEstEn_str {
*|  :description = "When this value is true, if the product of latpos and latest is less than 0, LatEst will not be chec\
*|  ked for Low Brake";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRULoBrkHoldXolcThres_str {
*|  :description = "if the product of latpos and latest is less than 0,and XOLC is less than this threshold, LatEst will\
*|   not be checked for Low Brake";
*|  :units = "m";
*|  :type = caltype.single_0_30_CT;
*|  }
*|  .k_AEB_VRUHiBrkRefRange_IBST_str {
*|  :description = "Stop distance for calculating range threshold of high brake to VRU (IBOOSTER vehicle)";
*|  :units = "m";
*|  :type = caltype.single_m3_6_CT;
*|  }
*|  .k_AEB_VRUHiBrkRefRange_ESP_str {
*|  :description = "Stop distance for calculating range threshold of high brake to VRU (ESP vehicle)";
*|  :units = "m";
*|  :type = caltype.single_m3_6_CT;
*|  }
*|  .k_AEB_LongPedLBDuration_sec_str {
*|  :description = "Low brake duration for long proceeding pedestrain";
*|  :units = "m/sec";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_HiBrkRefRange_IBST_str {
*|  :description = "reference value for high brake range threshold (IBST Vehicle)";
*|  :units = "m";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_HiBrkRefRange_ESP_str {
*|  :description = "reference value for high brake range threshold (ESP Vehicle)";
*|  :units = "m";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_VruHBCrossingRangeOffset_str {
*|  :description = "LongSafe_cal.k_AEB_VruHBCrossingRangeOffset";
*|  :units = "m";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_DesireStopDistance_IBST_str {
*|  :description = "What is the target minimal stop distance between ego vehicle and target vehicle before AEB can exit.\
*|   (For Ibooster)";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_DesireStopDistance_ESP_str {
*|  :description = "What is the target minimal stop distance between ego vehicle and target vehicle before AEB can exit.\
*|   (For ESP)";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_CLHiBrkNeedDecelLimt_IBA_str {
*|  :description = "Close loop deceleration value limitation during high brake (For IBA function)";
*|  :units = "m/sec^2";
*|  :type = caltype.single_m12p5_0_CT;
*|  }
*|  .k_AEB_VRUXolcUpLimit_str {
*|  :description = "AEB will not be acitive when the xolc is higher than this value.";
*|  :units = "m/sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_VRUXolcDownLimit_str {
*|  :description = "AEB will not be acitive when the xolc is lower than this value.";
*|  :units = "m/sec";
*|  :type = caltype.single_m10_0_CT;
*|  }
*|  .k_AEB_TapVehIgnStrOvrdMask_str {
*|  :description = "0: Forward; 1: CCFTAP; 2: SCP.";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_TapVRUIgnStrOvrdMask_str {
*|  :description = "0: Forward; 1: CBTA; 2: CPTA";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_IgnDrvBehRedToFunnel_str {
*|  :description = "when it sets to 1, it will ignore driver behavior reduction to VRU predicted funnel.";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DrvOvrdBasePreFac_FLBA_str {
*|  :description = "Driver override pressure factor for FLBA.";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_DrvOvrdBasePosFac_FLBA_str {
*|  :description = "Driver override position factor for FLBA.";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_DrvOvrdBasePreFac_PF_str {
*|  :description = "Driver override pressure factor for prefill.";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_DrvOvrdBasePosFac_PF_str {
*|  :description = "Driver override position factor for prefill.";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_DrvOvrdBasePreFac_LB_str {
*|  :description = "Driver override pressure factor for LB.";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_DrvOvrdBasePosFac_LB_str {
*|  :description = "Driver override position factor for LB.";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_DrvOvrdBasePreFac_HB_str {
*|  :description = "Driver override pressure factor for HB.";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_DrvOvrdBasePosFac_HB_str {
*|  :description = "Driver override position factor for HB.";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_DrvOvrdBasePreFac_FB_str {
*|  :description = "Driver override pressure factor for FB.";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_DrvOvrdBasePosFac_FB_str {
*|  :description = "Driver override position factor for FB.";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_HiSpdBrkEngPresEnblTm_str {
*|  :description = "Minimal time required to trigger brake pedal pressure inhibit";
*|  :units = "sec";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_HiSpdBrkEngPosEnTime_str {
*|  :description = "min time required to to active brake brake inhibit";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_GasRateEngHdTm_str {
*|  :description = "latch time when gas pedal rate inhibit was actived";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_HiSpdGasRateEngHdTm_str {
*|  :description = "latch time when gas pedal rate inhibit was actived with high speed";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_GasRateCntThres_str {
*|  :description = "Gas pedal rate counter threshold while checking driver gas pedal rate engage";
*|  :units = "";
*|  :type = caltype.uint8_0_40_CT;
*|  }
*|  .k_AEB_HiSpdGasRateCntThres_str {
*|  :description = "Gas pedal rate counter threshold while checking driver gas pedal rate engage with high speed";
*|  :units = "";
*|  :type = caltype.uint8_0_40_CT;
*|  }
*|  .k_AEB_DrvEngUseTTCReduc_IBA_str {
*|  :description = "When this is set to true, IBA will be reduced when driver engage detected.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_BrkPdlEngageMode_str {
*|  :description = "1= use brake Pos/pressure for brake driver engage; 0= use brake status for driver engage";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_BrkEngStatusEnTime_str {
*|  :description = "min time required to to active brake status driver engage";
*|  :units = "sec";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_BrkResetHaloTime_ms_str {
*|  :description = "Minimum Brake status reset  Halo Time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_IgnoreBrkResetChk_str {
*|  :description = "When it is set to true,fusion system will ignore brake status check for ReleaseBrake.";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IBA_UseBrkPedal_str {
*|  :description = "0= use brake Pos/pressure for IBA active ; 1= use brake status for IBA active";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_EnBrkResetChk_str {
*|  :description = "1= Enable Brk pedal reset check; 0 = ignore brk pedal reset check";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_LeadVel_OCDead_str {
*|  :description = "Oncoming dead lead velocity of VRU TW object while calculating high brake range threshold";
*|  :units = "m/sec";
*|  :type = caltype.single_m5_0_CT;
*|  }
*|  .k_AEB_IBA_PermitAccelGap_str {
*|  :description = "Requested acceleration gap between IBA acceleration and current acceleration.";
*|  :units = "sec";
*|  :type = caltype.single_m5_5_CT;
*|  }
*|  .k_AEB_BrkPosIgnore_str {
*|  :description = "If this value is true, AEB will ignore brake position check";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_BrkPrsIgnore_str {
*|  :description = "If this value is true, AEB will ignore brake pressure check";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_BikeHiConfMaxHeadError_str {
*|  :description = "If the degree between bicycle's heading and moving direction larger than this value, the confidence \
*|  will not be set to high";
*|  :units = "Deg";
*|  :type = caltype.single_0_180_CT;
*|  }
*|  .k_AEB_HostSpdEstUsed_str {
*|  :description = "When this value is true, estimated host velocity will adopted";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_MovHiBrkRefRange_IBST_str {
*|  :description = "reference value for high brake range threshold (IBST Vehicle)";
*|  :units = "m";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_MovHiBrkRefRange_ESP_str {
*|  :description = "reference value for high brake range threshold (ESP Vehicle)";
*|  :units = "m";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_CrossHiBrkRefRange_ESP_str {
*|  :description = "reference value for high brake range threshold (ESP Vehicle)";
*|  :units = "m";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_Brk_Reduc_ToFunnel_str {
*|  :description = "when BrkPedal active reduce the funnel";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_Spd_Reduc_ToFunnel_str {
*|  :description = "when low vehspd  reduce the funnel";
*|  :units = "Enum";
*|  :type = caltype.single_0_25p5_CT;
*|  }
*|  .k_AEB_NearTrgtReducHdTm_str {
*|  :description = "NumOfNearTrgt engage hold time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AEB_GateMinLatPosVRU_str {
*|  :description = "Minimal LatPos below which the is no discrimination for VRU";
*|  :units = "m";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_VehMinMatchConf_str {
*|  :description = "Minimum Match confidence for veh Target";
*|  :units = "";
*|  :type = caltype.uint8_0_5_CT;
*|  }
*|  .k_AEB_BigXolc_RedFac_str {
*|  :description = "Low brake TTC reduction factor that will apply to original TTC threshold when lateral offset detecte\
*|  d on non-corssing target";
*|  :units = "none";
*|  :type = caltype.single_0_1_CT;
*|  }
*|  .k_AEB_VRURangeBrkPoints_str {
*|  :description = "Range break points for DSTT and DMRT long pos check.";
*|  :units = "Sec";
*|  :type = caltype.array_9_k_AEB_VRURangeBrkPoints_single_m25p5_1000_CT;
*|  :annotation = caltype.anns_Changing;
*|  }
*|  .k_AEB_IgnoreVRUFusChk_str {
*|  :description = "If Check VRU Fusion Position";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_HostStraightlyYawThrh_str {
*|  :description = "";
*|  :units = "degpsec";
*|  :type = caltype.single_0_15_CT;
*|  }
*|  .k_AEB_VRUHB_UseDefaultOfst_str {
*|  :description = "If use vru highbrake offset with default offset";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VRUHB_LongBikeOffset_str {
*|  :description = "vru high brake offset for long bike";
*|  :units = "m";
*|  :type = caltype.single_m25p5_1000_CT;
*|  }
*|  .k_AEB_VRUHB_CrossBikeOffset_str {
*|  :description = "vru high brake offset for cross bike";
*|  :units = "m";
*|  :type = caltype.single_m25p5_1000_CT;
*|  }
*|  .k_AEB_VRUHB_StatBikeOffset_str {
*|  :description = "vru high brake offset for station bike";
*|  :units = "m";
*|  :type = caltype.single_m25p5_1000_CT;
*|  }
*|  .k_AEB_VRUHB_LongPedOffset_str {
*|  :description = "vru high brake offset for long ped";
*|  :units = "m";
*|  :type = caltype.single_m25p5_1000_CT;
*|  }
*|  .k_AEB_VRUHB_CrossPedOffset_str {
*|  :description = "vru high brake offset for cross ped";
*|  :units = "m";
*|  :type = caltype.single_m25p5_1000_CT;
*|  }
*|  .k_AEB_VRUHB_StatPedOffset_str {
*|  :description = "vru high brake offset for station ped";
*|  :units = "m";
*|  :type = caltype.single_m25p5_1000_CT;
*|  }
*|  .k_AEB_UseLgSfJAVehCusSet_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseLgSfJAPedCusSet_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_PedVisLatEstChkDisable_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_PedOCPedExitThres_str {
*|  :description = "";
*|  :units = "mps";
*|  :type = caltype.single_m4_4_CT;
*|  }
*|  .k_AEB_PedOCCrossingAllow_str {
*|  :description = "When this set to true, oncoming crossing pedestrain will be selected but with no lateral prediction";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_PedIgnoreVisPlauCheck_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_PedUseVisionTTC_str {
*|  :description = "When this is enbale, Fusion VRU will ignore vision only TTC when fused tagret is vision only type";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DisblAEBOCBicycle_str {
*|  :description = "when k_ped_DisblAEBBicycle is reset, and this cal is true, then oncoming bicycle will be output as v\
*|  alid AEB target";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DisblAEBBicycle_str {
*|  :description = "When this cal set to true, no bicycle target will be output as valid AEB target Fusion_AEB_PSel none";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DisblAEBPed_str {
*|  :description = "When this cal set to true, no Pedestrain target will be output";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DisblAEBOCPed_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseRRFunelInput_str {
*|  :description = "When this DD set to true, all selection funnel will use absoultely vaue of range rate as input inste\
*|  ad of host speed";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_EnableYawRateRedc_str {
*|  :description = "Set to true when enable yaw rate based funnel reduction";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreLongVelForCrsScene_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseTapTTCForVRU_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreVRUXolcChk_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreVehFusionCheck_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreVehRadarCheck_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreVRUBasicCheck_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseTapThresFunc_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_mi_VisLowConf_str {
*|  :description = "reserved for future use";
*|  :units = "none";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_AEB_AllowFCWOCBicycle_str {
*|  :description = "When k_ped_DisblFCWBicycle not set, and this set to true, then oncoming bicycle target will be outpu\
*|  t as valie FCW target";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DisblFCWBicycle_str {
*|  :description = "When this cal set to true, no bicycle target will be output as valid FCW target";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_AllowFCWOCPed_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_DisblFCWPed_str {
*|  :description = "When this cal set to true, no pedestrian target will be output as valid FCW target";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_ABALevel_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_AEB_AWBLevel_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_AEB_NotUseBrakeTypeFlag_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseShadowMode_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreFusVisCheck_str {
*|  :description = "when value set to 1, Ignore fusion/vision long position check.";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_AWBAutoBrkTyp_Mask_str {
*|  :description = "";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_MaxTime_ms_AWBReq_str {
*|  :description = "ms timer to limit the max time for AWB Req";
*|  :units = "msec";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_AEB_DRTVisLongErrThres_str {
*|  :description = "Long pos error threshold between vision and fusion object for DSRT and DMRT.";
*|  :units = "m";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_DRTVisLongChkDelayTime_str {
*|  :description = "long check delay time for pass status";
*|  :units = "msec";
*|  :type = caltype.uint32_0_100000_CT;
*|  }
*|  .k_AEB_FullLatVel_str {
*|  :description = "Dead band filter widh for lateral velocity";
*|  :units = "mps";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_NegligibleLatVel_str {
*|  :description = "Negligable lateral velocity within the dead band";
*|  :units = "mps";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_YawRateIgnoreLatVel_str {
*|  :description = "Yawrate Threshold to ignore the Lateral Velocity";
*|  :units = "deg/s";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_LatVelMinStepsize_str {
*|  :description = "Minimum Lateral Velocity Input StepSize for quantizer";
*|  :units = "m/sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_LongVelMinStepsize_str {
*|  :description = "Minimum Lontitudnal Velocity Input StepSize for quantizer";
*|  :units = "m/sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_UseVelTrackAngle_str {
*|  :description = "Enable Usage of VCS velocity based angle computation for Lead vehicle velocity";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseLatVelforRR_str {
*|  :description = "Enable Usage of VCS lateral velocity for Lead vehicle velocity computation";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_UseHostSpdBsdRR_str {
*|  :description = "Enable Usage of Host Speed based Range Rate computation";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_LatVelVisionConfirmIgnr_str {
*|  :description = "Ignore Detection Sensor Type for lateral Velocity Computation";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_Default_Time_Offset_str {
*|  :description = "Delay in Range calculation from the the detection of the target by the radar";
*|  :units = "sec";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_VehRangeBrkPoints_str {
*|  :description = "Range breakpoint of target of interest";
*|  :units = "m";
*|  :type = caltype.single_0_600_CT;
*|  }
*|  .k_AEB_VehRangRateBrkPoints_str {
*|  :description = "range rate breask points";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_VehLongRangeErrorThres_str {
*|  :description = "Maximum range difference between fusion reported range and vision reported range";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_VehLatRangeErrorThres_str {
*|  :description = "Maximum range difference between fusion reported range and vision reported range";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_TgtMomErrorThresLong_str {
*|  :description = "Longitudinal momentary error check will fail when moment error exceed this threshold value";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_TgtMomErrorThresLat_str {
*|  :description = "Lateral momentary error check will fail when momentary error exceed this threshold value";
*|  :units = "m";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_VehLatRRBrkPoints_str {
*|  :description = "Lateral relative speed break points";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_VehAccuErrorChkOnLong_str {
*|  :description = "Switch that enable longitudinal accumulated error check when set to true";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VehAccuErrorChkOnLat_str {
*|  :description = "Switch that enable lateral accumulated error check when set to true";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VehMomeErrorChkOnLong_str {
*|  :description = "Switch that enable longitudinal momentary error check when set to true";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VehMomeErrorChkOnLat_str {
*|  :description = "Switch that enable lateral momentary error check when set to true";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VehBaseChkFailEnblTime_str {
*|  :description = "PCA Range accumalated error time keep this time, it will output check fail";
*|  :units = "msec";
*|  :type = caltype.uint32_0_100000_CT;
*|  }
*|  .k_AEB_VehBaseChkFailHoldTime_str {
*|  :description = "If Range Check fail, it will be latched this time";
*|  :units = "msec";
*|  :type = caltype.uint32_0_100000_CT;
*|  }
*|  .k_AEB_VehErrorAccuPerdLong_str {
*|  :description = "Longitudinal accumulated period that define how long the error will be accumulated without truncated";
*|  :units = "m";
*|  :type = caltype.uint16_0_1000_CT;
*|  }
*|  .k_AEB_VehErrorAccuPerdLat_str {
*|  :description = "lateral accumulated period that define how long the error will be accumulated without truncated";
*|  :units = "m";
*|  :type = caltype.uint16_0_1000_CT;
*|  }
*|  .k_AEB_VehLongRangeChkEnbl_str {
*|  :description = "Will enbale PCA longitudinal range chek when set to 1";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VehLatRangeChkEnbl_str {
*|  :description = "Will enbale PCA lateral range chek when set to 1";
*|  :units = "boolean";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VehFusionMinAgeCount_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VehMulTrklMinAgeCount_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VehSingleTrkMinAgeCount_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VehVisionMinAgeCount_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VehMinAgeCount_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_VehDetStatus_str {
*|  :description = "Detection Status Enumenration for PCA Target";
*|  :units = "enum";
*|  :type = caltype.uint8_0_15_CT;
*|  }
*|  .k_AEB_VehIgnoreDetProfile_str {
*|  :description = "When this value is true, dectection profile for DMRT&DSRT will be ignored.";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VehIgnoreDetProfileLatPos_str {
*|  :description = "When lateral position of object is larger than this value, dectection profile for DMRT&DSRT will be \
*|  ignored.";
*|  :units = "m";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AEB_VehProfileChk_HdTm_str {
*|  :description = "If profile check fails, it will be latched this time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_VehRadarIDChk_HdTm_str {
*|  :description = "If Radar ID Check fail, it will be latched this time";
*|  :units = "msec";
*|  :type = caltype.uint16_0_65535_CT;
*|  }
*|  .k_AEB_VehRadarIDChkRangeThres_str {
*|  :description = "Range threshold for DSRT and DMRT Radar ID check.";
*|  :units = "m";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_VehRangeRate_BrkPoints_str {
*|  :description = "Range break points for DSRT/DMRT radar ID check";
*|  :units = "m";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_VehRadarIDChk_str {
*|  :description = "when value set to 1, Ignore tracklets ID check.";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_VehRAIDChk_MinLongAccel_str {
*|  :description = "When vehicle accel or decelerate over this threshold value, radar ID change can be enabled";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_IgnoreAEBPedConfCheck_str {
*|  :description = "If Use Confidence Check";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreConfCheck_str {
*|  :description = "If Use Confidence Check";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreInPathAgeCheck_str {
*|  :description = "If Use Confidence Check";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_IgnoreAebInhibit_str {
*|  :description = "AebInhibit";
*|  :units = "msec";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_AEB_IgnoreAebFault_str {
*|  :description = "AebFault";
*|  :units = "msec";
*|  :type = caltype.uint16_0_255_CT;
*|  }
*|  .k_AEB_Vehicle_Mass_str {
*|  :description = "Vehicle mass.";
*|  :units = "kg";
*|  :type = caltype.uint16_0_5000_CT;
*|  }
*|  .k_AEB_EPB_Present_str {
*|  :description = "Vehicle Configuration Data - Set this calibration TRUE if the vehicle has an Electric Park Brake, ot\
*|  herwise set this calibration FALSE.";
*|  :units = "bit";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_EspRespTime_str {
*|  :description = "Atuator response time.";
*|  :units = "ms";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_EspRespMaxJerk_str {
*|  :description = "Atuator response max jerk.";
*|  :units = "mpsss";
*|  :type = caltype.single_m30_30_CT;
*|  }
*|  .k_AEB_ESPRespomseTime_str {
*|  :description = "Atuator response time.";
*|  :units = "ms";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_ESPTmSpdBrkPoints_str {
*|  :description = "The x-axis with speed break points.";
*|  :units = "mps";
*|  :type = caltype.single_0_50_CT;
*|  }
*|  .k_AEB_ESPDecelDiffBrkPoints_str {
*|  :description = "break points of deceleration gap between command decel and IMU.";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_ESPDelayTime_str {
*|  :description = "Atuator delay time for desired value.";
*|  :units = "ms";
*|  :type = caltype.single_0_5_CT;
*|  }
*|  .k_AEB_UseOriginRangeCal_str {
*|  :description = "The switch using raw range.";
*|  :units = "none";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AEB_ESPRespTmHB2FB_str {
*|  :description = "The Atuator response time hb to fb.";
*|  :units = "mpss";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AEB_ESPDeftResponseTime_str {
*|  :description = "Response Time breakPoint";
*|  :units = "m";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AEB_VRURlsMinXolc_str {
*|  :description = "If xolc of VRU is lower than this value,  AEB VRU release will not release.";
*|  :units = "boolean";
*|  :type = caltype.single_m3_3_CT;
*|  }
*|  .k_AEB_VehIgnCstMask_str {
*|  :description = "When (bit0: LB, bit1: HB, bit2: FB,bit3:  IBA, bit4: prefill) is active, the status of vehicle will \
*|  not  be checked.";
*|  :units = "boolean";
*|  :type = caltype.uint16_0_255_CT;
*|  }
*|  .k_AEB_PedInterestChk_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_255_CT;
*|  }
*|  .k_AEB_VehHighestConf_str {
*|  :description = "Highest confidence Enumenration for PCA Target";
*|  :units = "enum";
*|  :type = caltype.uint8_0_3_CT;
*|  }
*|  .k_AEB_VehHiConf_str {
*|  :description = "High confidence Enumenration for PCA Target";
*|  :units = "enum";
*|  :type = caltype.uint8_0_3_CT;
*|  }
*|  .k_AEB_GateTOIAngle_Arr_str {
*|  :description = "LongSafe_cal.k_AEB_GateTOIAngle_Arr";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AEB_GateTOIPosi_x_str {
*|  :description = "LongSafe_cal.k_AEB_GateTOIPosi_x";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_Cal_LgSafe_minor_version_str {
*|  :description = "calibration file version control, minor_version";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*|  .k_Cal_LgSafe_major_version_str {
*|  :description = "calibration file version control, major_version";
*|  :units = "none";
*|  :type = caltype.uint8_0_255_CT;
*|  }
*| }
*/
