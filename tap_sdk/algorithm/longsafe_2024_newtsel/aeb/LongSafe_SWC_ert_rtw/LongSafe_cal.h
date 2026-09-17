#ifndef LongSafe_CAL_H
#define LongSafe_CAL_H
/****************************************************************************
 * Calibration file for LongSafe production code.
 * DD uses version 5 of the bas file.
 * File Name: D:\00ST\00Git\00_LongSafeCtrl\02_DataDictionary\LongSafe\LongSafe_cal.h
 * Created: 2025/7/8        20:05:55 
 * From Excel file: DataDictionary_LongSafe_DF.xls
 * Calibration Values for project         
 * Calibrations for full application.
 * Set Description:         Initial Value
 ****************************************************************************/

#include "rtwtypes.h"

/*
 *  COMPONENT:  \AEB
*/

/*
 *  COMPONENT:  \Version Control
*/


#define LongSafe_CAL_SIZE  11348 

typedef struct {
   boolean k_AEB_FLBA_Enabled_str;
   boolean k_AEB_DBS_Enabled_str;
   boolean k_AEB_UseTestSceneFlag_str;
   boolean k_AEB_UseSpecialSceneFullBrk_str;
   boolean k_AEB_MinStop_Enabled_str;
   float32 k_AEB_AccelMinGasPedPosInhbt_str;
   float32 k_AEB_AccelTrhdMov_str;
   float32 k_AEB_AccelTrhdStat_str;
   float32 k_AEB_SpecScenHostSpdMax_str;
   float32 k_AEB_SpecScenFBHostHiSpd_str;
   float32 k_AEB_SpecScenFBHostMidSpd_str;
   float32 k_AEB_SpecScenFBHostLowSpd_str;
   float32 k_AEB_SpecScenFBThresInHiSpd_str;
   float32 k_AEB_SpecScenFBThresInMidSpd_str;
   float32 k_AEB_SpecScenFBThresInLowSpd_str;
   float32 k_AEB_SpecScenFBThresInElseSpd_str;
   float32 k_AEB_SpecScenHostSpdMin_str;
   uint16 k_AEB_AlgInternalLpTm_ms_str;
   float32 k_AEB_BrkHdTmAfterTrig_ms_str;
   boolean k_AEB_Enable_str;
   boolean k_AEB_UseHoldTrigAfterStand_str;
   float32 k_AEB_AlgLpTm_sec_str;
   float32 k_AEB_BrkingRampToHiStep_mps_str;
   float32 k_AEB_BrkingRampToLoStep_mps_str;
   float32 k_AEB_BrakingRampToZeroStep_str;
   float32 k_AEB_DecelTrhdMov_str;
   float32 k_AEB_DecelTrhdStat_str;
   float32 k_AEB_DrvAppRefTmForAdj_str;
   float32 k_AEB_DrvOvrdBasePressure_str;
   float32 k_AEB_RdrTimeStep_sec_str;
   uint8 k_AEB_GasPedalMargin_str;
   uint8 k_AEB_GasPedalPositionMax_str;
   uint16 k_AEB_GasPedalOvrdTm_ms_str;
   float32 k_AEB_GateClosingRngRtTrhd_str;
   float32 k_AEB_ZeroSpdTrhd1_str;
   float32 k_AEB_ZeroSpdTrhd2_str;
   float32 k_AEB_GateMaxObjAngle_str;
   float32 k_AEB_GateMaxObjOffset_str;
   float32 k_AEB_GateMaxOpeningRngRt_str;
   float32 k_AEB_GateMaxRangeMov_str;
   float32 k_AEB_GateMaxRangeStat_str;
   float32 k_AEB_GateMaxTOIAngle_str;
   uint16 k_AEB_GateMinROC_str;
   boolean k_AEB_UseInFunnelChk_str;
   float32 k_AEB_HiBrkHdTm_str;
   float32 k_AEB_HiBrkLdTmStat_sec_str[ 15 ];
   float32 k_AEB_AEBEgoSpdKneePoints_str[ 15 ];
   float32 k_AEB_MEAEBEgoSpdKneePoints_str[ 8 ];
   float32 k_AEB_HiBrkLdTmMov_sec_str[ 15 ];
   uint8 k_AEB_VehHiBrkLowPersistanceCnt_str;
   uint8 k_AEB_VRUHiBrkLowPersistanceCnt_str;
   uint8 k_AEB_HiBrkACCStrongBrkCnt_str;
   float32 k_AEB_HiBrkMaxSpdMov_str;
   float32 k_AEB_HiBrkMaxSpdStat_str;
   float32 k_AEB_HiBrkMinRlsTm_str;
   float32 k_AEB_HiBrakingLvlMov_mps_str;
   float32 k_AEB_HiBrakingLvlStat_mps_str;
   float32 k_AEB_LittleBrakeDecel_mps_str;
   boolean k_AEB_HiBrkMinSpdChkEnbl_str;
   boolean k_AEB_HoldDrvActionWithBrk_str;
   float32 k_AEB_DBSAbsMaxDecel_str;
   float32 k_AEB_DBSLdTmMov_sec_str[ 15 ];
   float32 k_AEB_DBSLdTmStat_sec_str[ 15 ];
   uint16 k_AEB_WrapperLpTm_ms_str;
   float32 k_AEB_LCHighFactor_str;
   float32 k_AEB_LCHdTm_str;
   float32 k_AEB_LCLongTermSteerGain_str;
   float32 k_AEB_LCSpdIntercept_str;
   float32 k_AEB_LCSpdSlope_str;
   float32 k_AEB_LwBrkLateralLimit_str;
   float32 k_AEB_LwBrkLdTmMov_sec_str[ 15 ];
   float32 k_AEB_LwBrkLdTmStat_sec_str[ 15 ];
   float32 k_AEB_LwBrkMaxSpdMov_str;
   float32 k_AEB_LwBrkMaxSpdStat_str;
   boolean k_AEB_LwBrkMinSpdChkEnbl_str;
   uint8 k_AEB_LwBrkPersistanceCnt_str;
   float32 k_AEB_LwBrakingLvl_mps_str;
   float32 k_AEB_LwBrakingThrshACCBrk_str;
   float32 k_AEB_MinClosingSpd_str;
   float32 k_AEB_MinVehicleSpd_str;
   float32 k_AEB_MovingAwayNoiseLvlNeg_str;
   float32 k_AEB_MovingAwayNoiseLvlPos_str;
   float32 k_AEB_PathFarWidthEntryGate_str;
   float32 k_AEB_PathFarWidthExitGate_str;
   float32 k_AEB_PathHitDistanceEntryGate_str;
   float32 k_AEB_PathHitDistanceExitGate_str;
   float32 k_AEB_PathNearFarTransitRng_str;
   float32 k_AEB_PathNearWidthEntryGate_str;
   float32 k_AEB_PathNearWidthExitGate_str;
   float32 k_AEB_PathYawDistanceEntryGate_str;
   float32 k_AEB_PathYawDistanceExitGate_str;
   float32 k_AEB_DBSPathYawDistExitGate_str;
   float32 k_AEB_PrefillLateralLimit_str;
   float32 k_AEB_PrefillLdTmMov_sec_str[ 15 ];
   float32 k_AEB_PrefillLdTmStat_sec_str[ 15 ];
   boolean k_AEB_PrefillMinSpdChkEnbl_str;
   boolean k_AEB_ReferLowToTTEMinStat_str;
   boolean k_AEB_UseTwoLevelDecel_str;
   uint16 k_AEB_ReleaseOvrdTime_ms_str;
   uint16 k_AEB_SteeringInhibitHaloTime_str;
   float32 k_AEB_SteeringAngleRtTrhd_str[ 6 ];
   float32 k_AEB_OvrdSteeringRateMax_str;
   uint16 k_AEB_JAOvrdSteeringRateMax_str;
   float32 k_AEB_JAOvrdYawRateMax_str;
   float32 k_AEB_SteeringRtOvrdGain_str;
   float32 k_AEB_TTBAccBrkDelay_str;
   float32 k_AEB_TTBAvgBrkDelay_str;
   float32 k_AEB_TTBMaxSpd_str;
   float32 k_AEB_TTCIntegAccelEntry_str;
   float32 k_AEB_TTCIntegAccelExit_str;
   float32 k_AEB_TTCIntegDecelEntry_str;
   float32 k_AEB_TTCIntegDecelExit_str;
   uint8 k_AEB_TTCIntegMaxSteps_str;
   float32 k_AEB_TTCIntegMaxTime_str;
   float32 k_AEB_TTCIntegTimeStep_str;
   float32 k_AEB_TTCLowerClip_x_str[ 5 ];
   float32 k_AEB_TTCLowerClip_z_str[ 5 ];
   float32 k_AEB_TTCMax_str;
   float32 k_AEB_TTCMaxEvalTime_str;
   float32 k_AEB_TTCMinEvalTime_str;
   float32 k_AEB_TTTAverageTurnAccel_str;
   float32 k_AEB_TTCMinClipSpd_str;
   float32 k_AEB_TTCMinClipRR_str;
   float32 k_AEB_TTCUpperClip_x_str[ 5 ];
   float32 k_AEB_TTCUpperClip_z_str[ 5 ];
   float32 k_AEB_TTTMinLatMovement_str;
   float32 k_AEB_WheelSpdFilterGain_str;
   float32 k_AEB_YawNeutral_str;
   float32 k_AEB_YawNoiseFloorForXolc_str;
   float32 k_AEB_HostAcceAeblRdcFac_str[ 9 ];
   float32 k_AEB_HostAccelPoints_str[ 9 ];
   boolean k_AEB_HMIBrakingEnbld_str;
   boolean k_AEB_LowBrakeAlertEnbl_str;
   boolean k_AEB_PrefillBrakeAlertEnbl_str;
   float32 k_AEB_OvrdYawRateMax_str;
   float32 k_AEB_SteerOvrdOffHdTm_str;
   float32 k_AEB_SteerOvrdOffTTEMinMinusX_str;
   uint8 k_AEB_VehSSettingValue_str;
   uint16 k_AEB_FLBALatchTime_str;
   uint16 k_AEB_PrefillLatchTime_str;
   boolean k_AEB_UsePrefillOverride_str;
   boolean k_AEB_UseUnclippedComTTC_str;
   boolean k_AEB_OnlyCommonTTC_str;
   float32 k_AEB_RCSFilterGain_str;
   boolean k_AEB_AllowHiBrkUnclipped_str;
   float32 k_AEB_HeavyHighSpdTrhd_str;
   float32 k_AEB_HeavyFullSpdTrhd_str;
   float32 k_AEB_MinHeavyFullSpdTrhd_str;
   float32 k_AEB_MaxHeavyFullSpdTrhd_str;
   float32 k_AEB_FullBrakingLvlMov_mps_str;
   float32 k_AEB_FullBrakingLvlStat_mps_str;
   float32 k_AEB_MaxDecelRadarOnly_str;
   boolean k_AEB_CnfmByCameraEnbl_str;
   float32 k_AEB_HiBrkSpdTrhd_str;
   float32 k_AEB_ZeroSpdTrhd_str;
   uint16 k_AEB_CIBEventLatchTime_str;
   uint16 k_AEB_BrkHdTmAfterStop_str;
   uint16 k_AEB_TestSceneHdTm_ms_str;
   float32 k_AEB_FltGainLateralAccel_str;
   float32 k_AEB_VRUHiBrkMaxSpd_str;
   float32 k_AEB_OCBike_ABAMaxSpd_mps_str;
   float32 k_AEB_LongBike_ABAMaxSpd_mps_str;
   float32 k_AEB_CrsBike_ABAMaxSpd_mps_str;
   float32 k_AEB_StatBike_ABAMaxSpd_mps_str;
   float32 k_AEB_OCPed_ABAMaxSpd_mps_str;
   float32 k_AEB_NonCrsPed_ABAMaxSpd_mps_str;
   float32 k_AEB_CrsPed_ABAMaxSpd_mps_str;
   float32 k_AEB_OCBike_IBAMaxSpd_mps_str;
   float32 k_AEB_LongBike_IBAMaxSpd_mps_str;
   float32 k_AEB_CrsBike_IBAMaxSpd_mps_str;
   float32 k_AEB_StatBike_IBAMaxSpd_mps_str;
   float32 k_AEB_OCPed_IBAMaxSpd_mps_str;
   float32 k_AEB_NonCrsPed_IBAMaxSpd_mps_str;
   float32 k_AEB_CrsPed_IBAMaxSpd_mps_str;
   float32 k_AEB_NonCrsPed_IBAMinSpd_mps_str;
   float32 k_AEB_VRUMinHostSpd_mps_str;
   float32 k_AEB_VRUMaxHostSpd_mps_str;
   float32 k_AEB_PFVRUMaxHostSpd_mps_str;
   float32 k_AEB_VRULongRange_str[ 7 ];
   float32 k_AEB_VRULatOffsetTrhd_str[ 7 ];
   boolean k_AEB_VRUEnable_str;
   boolean k_AEB_EnableOncoming_str;
   boolean k_AEB_UseHostLatAccel_str;
   float32 k_AEB_VRUYPosHoldOnTrhd_str;
   uint8 k_AEB_MinMatchConfMov_str;
   uint8 k_AEB_MinMatchConfStat_str;
   boolean k_AEB_UseROCXolc_str;
   sint8 k_AEB_HostLatAccelSign_str;
   boolean k_AEB_RevGearHoldRlsEnbl_str;
   float32 k_AEB_TTCAnnoyOffset_str;
   boolean k_AEB_TTCAnnoyMinEnbl_str;
   float32 k_AEB_TTCAnnoyMax_str;
   boolean k_AEB_ReferLeadAccel_str;
   float32 k_AEB_GateMinOpeningRange_str;
   boolean k_AEB_UseMinTrkAccel_str;
   float32 k_AEB_HighBrkAnnoyTTCThrs_str;
   float32 k_AEB_HighBrkLeadDecelTrhd_str;
   float32 k_AEB_HiBrkLdTmStop_sec_str[ 10 ];
   float32 k_AEB_HiBrkLdTmStop_mps_str[ 10 ];
   float32 k_AEB_AlertOnlyTTCTrhd_str;
   float32 k_AEB_HostAccelInhbtTrhd_str;
   boolean k_AEB_UseLeadAccelFCW_str;
   float32 k_AEB_BrkPedPosFiltgain_str;
   float32 k_AEB_DBSDrvBrkPdlPosThres_str;
   float32 k_AEB_DBSDrvBrkPdlPrsThres_str;
   float32 k_AEB_DBSPedRateEnblTm_str;
   uint16 k_AEB_DBSPedRateHdTm_str;
   float32 k_AEB_DBSActiveMinPedPos_str;
   float32 k_AEB_DBSPedPosEnblTm_str;
   sint32 k_AEB_DBSMinBrkPedRateOff_str;
   float32 k_AEB_DBSPedRateDsblTm_str;
   float32 k_AEB_DBSReleaseMinPedPos_str;
   float32 k_AEB_DBSPedPosDisableTime_str;
   sint32 k_AEB_DBSMinBrkPedRateOn_str;
   sint32 k_AEB_DBSLBMinBrkPedRateOn_str;
   sint32 k_AEB_DBSHBMinBrkPedRateOn_str;
   sint32 k_AEB_DBSFBMinBrkPedRateOn_str;
   float32 k_AEB_DrvBrkPressFiltgain_str;
   uint16 k_AEB_DBSMinDrvAppBrkPresOn_str;
   float32 k_AEB_DBSPressEnblTm_str;
   sint32 k_AEB_DBSDrvBrkPrsRateOn_str;
   float32 k_AEB_DBSPrsRateEnblTm_str;
   uint16 k_AEB_DBSMinDrvAppBrkPresOff_str;
   float32 k_AEB_DBSPressDisableTime_str;
   sint32 k_AEB_DBSDrvBrkPrsRateOff_str;
   float32 k_AEB_DBSPrsRateDisableTime_str;
   float32 k_AEB_DBSAccelOffset_sec_str[ 8 ];
   float32 k_AEB_DBSAccelOffset_mpss_str[ 8 ];
   boolean k_AEB_DBSWhlSpdAcceEnbl_str;
   float32 k_AEB_DBSTTCBsdRampdownRate_str[ 5 ];
   float32 k_AEB_DBSTTCBsdRampdown_sec_str[ 5 ];
   float32 k_AEB_DBSTTCBsdRampupRate_str[ 5 ];
   float32 k_AEB_DBSTTCBsdRampup_sec_str[ 5 ];
   boolean k_AEB_DBSBrkPedPosOnlyEnbl_str;
   boolean k_AEB_DBSDrvBrkPrsOnlyEnbl_str;
   float32 k_AEB_DBSMinLeadAccel_str;
   float32 k_AEB_DBSMinRangeAccel_str;
   float32 k_AEB_DBSLeadAccelFact_str;
   float32 k_AEB_DBSHostDecelThrsFac_str;
   float32 k_AEB_DBSMinDecelRampOut_str;
   uint16 k_AEB_HostAccelInhbtHaloTime_str;
   boolean k_AEB_DBSBrkDualCnfmEnbl_str;
   uint16 k_AEB_DBSDualConfirmMaxTime_str;
   uint16 k_AEB_DBSMaxActivationWindow_str;
   boolean k_AEB_DBSBrakeCnfmEnbl_str;
   float32 k_AEB_DBSLeadAclOfst_sec_str[ 8 ];
   float32 k_AEB_DBSLeadAclOfst_mpss_str[ 8 ];
   float32 k_AEB_DBSMinStopDistance_str;
   float32 k_AEB_DBSMinStopDistanceLmt_str;
   float32 k_AEB_DBSRRAccelFiltGain_str;
   float32 k_AEB_DBSRngAccelFiltGain_str;
   boolean k_AEB_DBSRngBsdAccelEnbl_str;
   boolean k_AEB_DBSLdAclBsdAccelEnbl_str;
   float32 k_AEB_DrvOvrdBaseBrkPdPos_str;
   float32 k_AEB_PrefillMaxSpdMov_str;
   float32 k_AEB_PrefillMaxSpdStat_str;
   float32 k_AEB_FLBALdTmMov_sec_str[ 15 ];
   float32 k_AEB_FLBALdTmStat_sec_str[ 15 ];
   float32 k_AEB_MSLdTmMov_sec_str[ 15 ];
   float32 k_AEB_MSLdTmStat_sec_str[ 15 ];
   boolean k_AEB_FLBAMinSpdChkEnbl_str;
   float32 k_AEB_FLBAMaxSpdMov_str;
   float32 k_AEB_FLBAMaxSpdStat_str;
   boolean k_AEB_MSMinSpdChkEnbl_str;
   float32 k_AEB_MSMaxSpdMov_str;
   float32 k_AEB_MSMaxSpdStat_str;
   float32 k_AEB_DBSMaxSpdMov_str;
   float32 k_AEB_DBSMaxSpdStat_str;
   uint8 k_AEB_VRUMinMatchConf_str;
   boolean k_AEB_VRUDBSEnbl_str;
   float32 k_AEB_SteerOvrdOffTTEMin_str;
   boolean k_AEB_FLBADefaultEnbl_str;
   boolean k_AEB_FLBAIgnoreHMIStng_str;
   uint8 k_AEB_FLBAHMICustStng_str;
   boolean k_AEB_MinStopDefaultEnbl_str;
   boolean k_AEB_MinStopIgnoreHMIStng_str;
   uint8 k_AEB_MinStopHMICustStng_str;
   boolean k_AEB_DBSIgnoreHMIStng_str;
   uint8 k_AEB_DBSHMICustStng_str;
   boolean k_AEB_IgnLowBrkHBTimerReset_str;
   float32 k_AEB_DBSMaxDecelExitTime_str;
   float32 k_AEB_PrefillExitTime_str;
   float32 k_AEB_FLBAExitTime_str;
   float32 k_AEB_MinStopExitTime_str;
   float32 k_AEB_MaxDecelExitTime_str;
   uint16 k_AEB_HoldRelPressure_str;
   boolean k_AEB_UseOnlyBrkPrsHldRel_str;
   uint32 k_AEB_NoEPBBrakeHdTm_str;
   boolean k_AEB_VRUOncomingEnbl_str;
   float32 k_AEB_HiConfOCBikePFTTC_sec_str[ 15 ];
   float32 k_AEB_HiConfOCBikeLoBrkTTC_sec_str[ 15 ];
   float32 k_AEB_HiConfOCBikeHiBrkTTC_sec_str[ 15 ];
   float32 k_AEB_HiConfOCPedPrefillTTC_sec_str[ 15 ];
   float32 k_AEB_HiConfOCPedLoBrkTTC_sec_str[ 15 ];
   float32 k_AEB_HiConfOCPedHiBrkTTC_sec_str[ 15 ];
   float32 k_AEB_AccelOffsetRangeBrkPoints_str[ 7 ];
   uint8 k_AEB_SteerOvrdDisbleType_str;
   float32 k_AEB_HighBrkAnnoyTTCLose_str;
   float32 k_AEB_LowBrkAnnoyTTLose_str;
   float32 k_AEB_RangeDecelTrhd_str;
   float32 k_AEB_LeadDecelTrhd_str;
   boolean k_AEB_DBSMinSpdChkEnbl_str;
   boolean k_AEB_DBSUseDefaultDecel_str;
   boolean k_AEB_IgnoreObjClassChk_str;
   float32 k_AEB_MinEgoSpdRadarOnly_str;
   uint8 k_AEB_MinMatchConfMovLowSpd_str;
   float32 k_AEB_HardTurnInhibitSpdPoints_str[ 6 ];
   float32 k_AEB_HardTurnStrAngleTrhd_str[ 9 ];
   float32 k_AEB_StrAngInhibitEnblTm_str;
   float32 k_AEB_BrkEngagePresEnblTm_str;
   uint16 k_AEB_BrkEngageHdTm_str;
   boolean k_AEB_IgrLowBrkDrvEng_str;
   float32 k_AEB_DBSMinVehicleSpd_str;
   float32 k_AEB_BcyMaxRangeRate_str;
   boolean k_AEB_IgrHiBrkDrvEng_str;
   float32 k_AEB_DrvEngInhibitSpd_str;
   uint8 k_AEB_VRUHBMinConf_str;
   float32 k_AEB_HBHdTmLowAge_str;
   float32 k_AEB_OtherTrgtMinDeltaYpos_str;
   float32 k_AEB_VRULatDeSelTrhd_str[ 7 ];
   float32 k_AEB_GasInhibitLowSpdTrhd_str;
   float32 k_AEB_GasInhibitHiSpdTrhd_str;
   uint8 k_AEB_VehHBDrvEngTypeSltd_str;
   uint8 k_AEB_VehLBDrvEngTypeSltd_str;
   uint8 k_AEB_VehPFDrvEngTypeSltd_str;
   boolean k_AEB_IgrPrefillDrvEng_str;
   uint8 k_AEB_VRUHBDrvEngTypeSltd_str;
   uint8 k_AEB_VRULBDrvEngTypeSltd_str;
   boolean k_AEB_IgrVRUPFDrvEng_str;
   uint8 k_AEB_VRUPFDrvEngTypeSltd_str;
   uint16 k_AEB_HiBrkDropWaitTime_str;
   float32 k_AEB_VRUHBHoldMaxRngAllow_str[ 9 ];
   float32 k_AEB_HBHoldMaxRngAllow_str[ 9 ];
   boolean k_AEB_DRTClassHoldEnbl_str;
   float32 k_AEB_GateMinRangeMov_str;
   float32 k_AEB_GateMinRangeStat_str;
   uint8 k_AEB_ClsFstDectIPAOffset_str;
   float32 k_AEB_OvtkStrAngleTrhd_str[ 9 ];
   float32 k_AEB_OvtkGasPedalTrhd_str[ 9 ];
   float32 k_AEB_LongBikePFLdTm_mps_str[ 10 ];
   float32 k_AEB_LongBikePFLdTm_sec_str[ 15 ];
   float32 k_AEB_LongBikeLBLdTm_mps_str[ 10 ];
   float32 k_AEB_LongBikeLBLdTm_sec_str[ 15 ];
   float32 k_AEB_LongBikeHBLdTm_sec_str[ 15 ];
   float32 k_AEB_LongBikeFLBALdTm_sec_str[ 15 ];
   float32 k_AEB_LongBikeMSLdTm_sec_str[ 15 ];
   float32 k_AEB_LongBikeDBSLdTm_sec_str[ 15 ];
   float32 k_AEB_HiConfBikeStaPFTTC_mps_str[ 10 ];
   float32 k_AEB_HiConfBikeStaPFTTC_sec_str[ 15 ];
   float32 k_AEB_BikeStaLBTTC_sec_str[ 15 ];
   float32 k_AEB_HiConfBikeStaHBTTC_sec_str[ 15 ];
   float32 k_AEB_HiConfBikeStaFLBATTC_sec_str[ 15 ];
   float32 k_AEB_HiConfBikeStaMSTTC_sec_str[ 15 ];
   float32 k_AEB_HiConfBikeStaDBSTTC_sec_str[ 15 ];
   uint8 k_AEB_FullBrakeHiBrkCnt_str;
   uint8 k_AEB_JAFullBrakeHiBrkCnt_str;
   float32 k_AEB_FullBrkDuringTimer_mps_str;
   boolean k_AEB_IgnLowBrkFBTimerReset_str;
   boolean k_AEB_IgnHiBrkFBTimerReset_str;
   float32 k_AEB_VRUAEBXolcTrhd_str[ 7 ];
   uint8 k_AEB_HiBrkLowPerstCntJA_str;
   float32 k_AEB_DBSHostAccelTrhd_str;
   uint16 k_AEB_SuppressTime_str;
   float32 k_AEB_CLHiBrkNeedDecelLimt_str;
   boolean k_AEB_NoAEBSuppressEnbl_str;
   uint16 k_AEB_HeadingAngOCTAPTrhd_str;
   uint16 k_AEB_HeadingAngCPTATrhd_str;
   float32 k_AEB_SensorInputLpTm_str;
   float32 k_AEB_VcanInputLpTm_str;
   boolean k_AEB_StationaryVehFullChkEnbl_str;
   boolean k_AEB_LongMovBikeFullChkEnbl_str;
   float32 k_AEB_leadAccelEnFullBrk_str;
   float32 k_AEB_FullBrkRangePoints_str[ 8 ];
   float32 k_AEB_FullBrkRngRtPoints_str[ 7 ];
   float32 k_AEB_FullBrakeChkEnbl_str[ 7 ][ 8 ];
   uint16 k_AEB_AxleTorqueFiltTime_ms_str;
   uint16 k_AEB_AxleTorqueRateMax_str;
   sint16 k_AEB_AxleTorqueRateMin_str;
   uint16 k_AEB_BrakeAccelFiltTime_ms_str;
   uint16 k_AEB_BrakeAccelRateMax_str;
   sint16 k_AEB_BrakeAccelRateMin_str;
   sint16 k_AEB_DrvIntndAxlTrqMinNegOffst_str;
   float32 k_AEB_BrakeAccelFinalLimit_str;
   boolean k_AEB_HoldDecelEnbl_str;
   boolean k_AEB_HoldBrkReqEnbl_str;
   boolean k_AEB_UseAxleTrqtoBrk_str;
   boolean k_AEB_IgnorePedTTCChk_str;
   boolean k_AEB_IgnorePedRngChk_str;
   float32 k_AEB_VRUMaxTTCAllowed_str;
   float32 k_AEB_VRUMinTTCAllowed_str;
   float32 k_AEB_VRUMaxRngAllowed_str;
   float32 k_AEB_VRUMinRngAllowed_str;
   boolean k_AEB_EPBStateAffectHold_str;
   uint8 k_AEB_MinConfSRRDegrade_str;
   boolean k_AEB_MovSRRMisAlignChkEnbl_str;
   boolean k_AEB_DBSReleaseAEBDisbl_str;
   uint8 k_AEB_LowConfInPathAgeTrhd_str;
   uint8 k_AEB_MedConfInPathAgeTrhd_str;
   uint8 k_AEB_HiConfInPathAgeTrhd_str;
   float32 k_AEB_HiBrkMinReleaseDist_str;
   boolean k_AEB_EnVRUClutterShutDown_str;
   boolean k_AEB_HiBrkVisConfirmDisable_str;
   boolean k_AEB_LowBrkVisConfirmDisable_str;
   float32 k_AEB_GasEngagePosEnTime_str;
   uint8 k_AEB_GasEngagePosEntryTrhd_str;
   uint8 k_AEB_GasEngagePosExitTrhd_str;
   sint16 k_AEB_GasPosRateEntryTrhd_str;
   sint16 k_AEB_GasPosRateExitTrhd_str;
   float32 k_AEB_GasPosRateEnTime_str;
   uint16 k_AEB_GasEngageHdTm_str;
   uint8 k_AEB_BrkEngagePosEntryTrhd_str;
   uint8 k_AEB_BrkEngagePosExitTrhd_str;
   float32 k_AEB_BrkEngagePosEnTime_str;
   uint8 k_AEB_HBNoVisFlagMinConf_str;
   uint8 k_AEB_LBNoVisFlagMinConf_str;
   uint8 k_AEB_UseNewPrefillCounter_str;
   boolean k_AEB_AllowOutFunAEBPRelease_str;
   float32 k_AEB_VRUHBMinConfEnblTime_str;
   uint8 k_AEB_HBHdTmAgeTrhd_str;
   uint8 k_AEB_VRUHBHdTmAgeTrhd_str;
   uint16 k_AEB_ExtendUsePedHdTm_str;
   uint16 k_AEB_LastValHaloTime_str;
   uint8 k_AEB_VRULBMinConf_str;
   float32 k_AEB_VRULBMinConfEnblTm_str;
   uint16 k_AEB_IDChangeHaloTime_str;
   sint16 k_AEB_HiSpdGasRateEntryTrhd_str;
   sint16 k_AEB_HiSpdGasRateExitTrhd_str;
   float32 k_AEB_HiSpdGasRateEnTime_str;
   uint16 k_AEB_HiSpdGasInhibtHdTm_str;
   uint8 k_AEB_UnIdeLowestConfInPathTrhd_str;
   uint8 k_AEB_UnIdeLowConfInPathTrhd_str;
   uint8 k_AEB_UnIdeMedConfInPathTrhd_str;
   uint8 k_AEB_UnIdeHiConfInPathTrhd_str;
   uint8 k_AEB_LowestConfInPathAgeTrhd_str;
   float32 k_AEB_TTCReduceLatOfstBrkPoint_str[ 9 ];
   float32 k_AEB_HiConfLBTTCReduceFactor_str[ 9 ];
   float32 k_AEB_HiConfHBTTCReduceFactor_str[ 9 ];
   float32 k_AEB_HiConfDBSTTCReduceFactor_str[ 9 ];
   float32 k_AEB_NoTTCReduceLatEstTrhd_str;
   uint16 k_AEB_LastBrkYposHaloTime_str;
   uint8 k_AEB_VRUFusHiConfLvl_str;
   uint8 k_AEB_VRUFusMedConfLvl_str;
   uint8 k_AEB_VRUVisMedConfLvl_str;
   uint8 k_AEB_FusHiMinInPAgeTrhd_str;
   uint8 k_AEB_FusHiMinInPAgeTrhdLong_str;
   uint8 k_AEB_FusMedMinInPAgeTrhd_str;
   uint8 k_AEB_VisMedMinInPAgeTrhd_str;
   uint8 k_AEB_VisMedMinInPAgeTrhdLong_str;
   uint8 k_AEB_FusMedMinInPAgeTrhdLong_str;
   uint8 k_AEB_MinInPAgeTrhd_str;
   uint8 k_AEB_MinInPAgeTrhdLong_str;
   float32 k_AEB_DrvBrkVRURlsEnTime_str;
   float32 k_AEB_GeneralSpdPoints_str[ 9 ];
   float32 k_AEB_OvtkMaxTTCTrhd_str;
   float32 k_AEB_OTMinXolcPercent_str;
   uint8 k_AEB_OneWayXolcChgCountTrhd_str;
   uint16 k_AEB_OvtkGasPdlHaloTime_str;
   uint16 k_AEB_OvtkReducHaloTime_str;
   float32 k_AEB_TTCReduceXolcBrkPoint_str[ 10 ];
   float32 k_AEB_PrefillTTCReduceFactor_str[ 9 ];
   float32 k_AEB_LowTTCReduceFactor_str[ 9 ];
   float32 k_AEB_HBTTCReduceFactor_str[ 10 ];
   float32 k_AEB_DBSTTCReduceFactor_str[ 10 ];
   float32 k_AEB_NeedDecelFilterGain_str;
   boolean k_AEB_UseTrackerLeadAeecl_str;
   float32 k_AEB_LeadVehDecelTrhd_str;
   float32 k_AEB_DecelDiffBrkPoints_str[ 13 ];
   float32 k_AEB_ESPSettlingTime_str[ 13 ];
   float32 k_AEB_DesireStopDistance_str[ 15 ];
   boolean k_AEB_UseCloseLoopDecel_str;
   float32 k_AEB_CLRampDownFactor_str[ 13 ];
   float32 k_AEB_CLDecelBrkRelseTrhd_str;
   float32 k_AEB_CLDecelBrkRelseEnTime_str;
   float32 k_AEB_EgoTartAccelBrkPoints_str[ 7 ];
   float32 k_AEB_TartInforFilterGain_str[ 7 ];
   float32 k_AEB_TartLeadSpdOffset_str;
   float32 k_AEB_LBDrvEngReducFactor_str;
   float32 k_AEB_HBDrvEngReducFactor_str;
   float32 k_AEB_DBSDrvEngReducFactor_str;
   float32 k_AEB_PFDrvEngReducFactor_str;
   uint8 k_AEB_VehDBSDrvEngTypeSltd_str;
   boolean k_AEB_IgrDBSDrvEng_str;
   float32 k_AEB_PredTimeRRBrkPoint_str[ 11 ];
   float32 k_AEB_PredTimeRAccelBrkPoint_str[ 5 ];
   float32 k_AEB_MaxPredictTime_str[ 5 ][ 11 ];
   boolean k_AEB_DrvEngUseTTCReduc_str;
   float32 k_AEB_NoESPDisDecelTrhd_str;
   float32 k_AEB_NoESPDisRangeTrhd_str;
   float32 k_AEB_EgoAllowDisScalFactor_str;
   float32 k_AEB_EgoHiDynamicAccelTrhd_str;
   float32 k_AEB_LongVelFullHiDymic_str;
   float32 k_AEB_LongVelFull_str;
   float32 k_AEB_LongVelNegliHiDymic_str;
   float32 k_AEB_LongVelNegli_str;
   float32 k_AEB_MovLeadVelNegliEnTime_str;
   uint16 k_AEB_MovLeadVelNegliHaloTime_str;
   boolean k_AEB_NonProceedVRUFullChkEnbl_str;
   float32 k_AEB_ESPDelayDisFadingTime_str;
   uint32 k_AEB_AccuAngEgoStopHaloTime_str;
   float32 k_AEB_MaxAllowVehHeadAngTime_str;
   boolean k_AEB_TTTUseTrtWidth_str;
   float32 k_AEB_TTTPersistXolcTrhd_str;
   uint16 k_AEB_BrkPressurePositionSel_str;
   boolean k_AEB_HiBrkUseRangeTrigger_str;
   float32 k_AEB_HiBrkTrigMovRangeOffset_str[ 15 ];
   float32 k_AEB_HiBrkTrigStatRangeOffset_str[ 15 ];
   float32 k_AEB_LoBrkTrigMovDuration_str[ 15 ];
   float32 k_AEB_LoBrkTrigStatDuration_str[ 15 ];
   float32 k_AEB_PrefillTrigMovDuration_str[ 15 ];
   float32 k_AEB_PrefillTrigStatDuration_str[ 15 ];
   float32 k_AEB_FLBATrigMovDuration_str[ 15 ];
   float32 k_AEB_FLBATrigStatDuration_str[ 15 ];
   float32 k_AEB_MinStopTrigMovDuration_str[ 15 ];
   float32 k_AEB_MinStopTrigStatDuration_str[ 15 ];
   uint16 k_AEB_FusionFLBAMaskWrd_str;
   uint16 k_AEB_FusionPFMaskWrd_str;
   uint16 k_AEB_FusionLBMaskWrd_str;
   uint16 k_AEB_FusionHBMaskWrd_str;
   uint16 k_AEB_FusionFBMaskWrd_str;
   uint16 k_AEB_FusionVRUFLBAMaskWrd_str;
   uint16 k_AEB_FusionVRUPFMaskWrd_str;
   uint16 k_AEB_FusionVRULBMaskWrd_str;
   uint16 k_AEB_FusionVRUHBMaskWrd_str;
   uint16 k_AEB_FusionVRUFBMaskWrd_str;
   uint16 k_AEB_FusionVRUTOIMaskWrd_str;
   boolean k_AEB_VehWithIboostNoESP_str;
   boolean k_AEB_PedEnable_str;
   boolean k_AEB_IgnoreDecelCheckInPCS_str;
   float32 k_AEB_DesiredVehHitSpd_str;
   float32 k_AEB_FullBrkLvl_mps_offset_str;
   float32 k_AEB_HiBrkLvl_mps_offset_str;
   float32 k_AEB_Adjust_XOLC_MovementLimit_str;
   float32 k_AEB_LongBikePFDuration_str;
   float32 k_AEB_DBSMaxDecel_mps_str;
   float32 k_AEB_VRUMinTTC_sec_str;
   float32 k_AEB_PFNearTrgt_RedFac_str[ 5 ];
   float32 k_AEB_LBNearTrgt_RedFac_str[ 5 ];
   float32 k_AEB_HBNearTrgt_RedFac_str[ 5 ];
   uint8 k_AEB_NearTrgt_KneePoints_str[ 5 ];
   boolean k_AEB_enb_veh_sta_check_str;
   uint8 k_AEB_veh_coasted_enb_cont_str;
   float32 k_AEB_InpathNowReduceFactor_str[ 7 ];
   float32 k_AEB_InpathLaterReduceFactor_str[ 7 ];
   float32 k_AEB_StrAngRtLatEstReduceFac_str[ 7 ];
   float32 k_AEB_StrAngRatePoints_str[ 7 ];
   float32 k_AEB_BrkInhibitLowSpdTrhd_str;
   float32 k_AEB_BrkInhibitHiSpdTrhd_str;
   uint16 k_AEB_HiSpdBrkEngageHdTm_str;
   float32 k_AEB_BrkEngagePresFactor_str;
   float32 k_AEB_HiSpdBrkEngagePresFactor_str;
   uint8 k_AEB_HiSpdBrkEngPosEntryTrhd_str;
   float32 k_AEB_VRULatEstFunnelExitFac_str;
   uint8 k_AEB_HiSpdBrkEngPosExitTrhd_str;
   uint8 k_AEB_VRUPFVehBehType_str;
   uint8 k_AEB_VRULBVehBehType_str;
   uint8 k_AEB_VRUHBVehBehType_str;
   float32 k_AEB_VRUPFVBCTTCRedFac_str;
   float32 k_AEB_VRULBVBCTTCRedFac_str;
   float32 k_AEB_VRUHBVBCTTCRedFac_str;
   boolean k_AEB_IgrHiBrkVehBeh_str;
   uint32 k_AEB_VRUHBInhVehBehType_str;
   float32 k_AEB_VehBehChkLowSpdTrhd_str;
   float32 k_AEB_VehBehChkHiSpdTrhd_str;
   uint16 k_AEB_StrRateReductionHdTm_str;
   uint16 k_AEB_StrReductionHdTm_str;
   uint16 k_AEB_BrkReductionHdTm_str;
   uint16 k_AEB_GasPdlReductionHdTm_str;
   float32 k_AEB_GasPdlReductionEntryTrhd_str;
   float32 k_AEB_GasPdlReductionExitTrhd_str;
   float32 k_AEB_StrRateReductionEntryTrhd_str;
   float32 k_AEB_StrRateReductionExitTrhd_str;
   float32 k_AEB_StrReductionEntryTrhd_str;
   float32 k_AEB_StrReductionExitTrhd_str;
   float32 k_AEB_StrRateReductionFactor_str;
   float32 k_AEB_StrReductionFactor_str;
   float32 k_AEB_BrkReductionFactor_str;
   float32 k_AEB_GasPdlReductionFactor_str;
   boolean k_AEB_BrkReductionSource_str;
   uint8 k_AEB_VRUFLBAVehBehType_str;
   float32 k_AEB_VRUFLBAVBCTTCRedFac_str;
   float32 k_AEB_GateMinRangeVRU_str;
   uint8 k_AEB_ClsFstDectVRUIPAOffset_str;
   float32 k_AEB_RoadCondLowSpdTrhd_str;
   float32 k_AEB_RoadCondHiSpdTrhd_str;
   uint8 k_AEB_VRUNumThres_str;
   float32 k_AEB_VRURadarLatErrThres_str;
   float32 k_AEB_VRUVisionLongErrThres_str[ 9 ];
   float32 k_AEB_VRUXolcChkLowSpdTrhd_str;
   float32 k_AEB_VRUXolcChkHiSpdTrhd_str;
   float32 k_AEB_MomErrorThresLong_str[ 7 ];
   float32 k_AEB_VehMomErrorThresLong_str[ 7 ];
   float32 k_AEB_TrtRangRateBrkPoints_str[ 7 ];
   float32 k_AEB_TrtLatRRBrkPoints_str[ 8 ];
   float32 k_AEB_MomErrorThresLat_str[ 8 ];
   float32 k_AEB_VRUXolcChkVelGapThres_str;
   float32 k_AEB_VRUXolcChkLongVelThres_str;
   float32 k_AEB_DesireStopDistanceLowSpd_str;
   float32 k_AEB_VRUHiSpdCrossThres_str;
   float32 k_AEB_VRUHiSpdCrossXolcLimit_str;
   float32 k_AEB_VRUMinReductionFac_str;
   float32 k_AEB_VehMinReductionFac_str;
   uint16 k_AEB_VehBasicCheckFailHldTime_str;
   uint16 k_AEB_VRUBasicCheckFailHldTime_str;
   uint8 k_AEB_TrgtNumTrhdForVRUCmplx_str;
   uint8 k_AEB_TrgtNumTrhdForVehCmplx_str;
   float32 k_AEB_VehCmplxReduceFac_str;
   float32 k_AEB_VRUCmplxReduceFac_str;
   float32 k_AEB_VRUHBMinReductionFac_str;
   float32 k_AEB_VehHBMinReductionFac_str;
   boolean k_AEB_NotChkSpdInFB_str;
   float32 k_AEB_RE_EndRangeOffset_str;
   float32 k_AEB_RE_StartRangeOffset_str;
   float32 k_AEB_Reduce_GasPdlTrhd_str[ 9 ];
   float32 k_GasPdlReduceDelayTime_str;
   boolean k_AEB_Use_TTE_In_CCR_str;
   float32 k_AEB_MinLostRangeVRU_str;
   float32 k_AEB_MinLostLatPosVRU_str;
   float32 k_AEB_MinLostRangeVeh_str;
   float32 k_AEB_MinLostLatPosVeh_str;
   boolean k_AEB_CloseLostHold_Enabled_str;
   float32 k_AEB_MinLostLatEstVRU_str;
   float32 k_AEB_GdRail_RangeOffset_str;
   float32 k_AEB_NearTrgt_RedFac_str[ 5 ];
   uint8 k_AEB_VRUVehBehType_str;
   float32 k_AEB_VRUVBCTTCRedFac_str;
   float32 k_AEB_TTBAvgBrkDelay_Full_str;
   float32 k_AEB_HiToFuBrakingLvlMov_mps_str;
   float32 k_AEB_LwBrakingLvl_Factor_str;
   boolean k_AEB_UseCSMdlToLwBrkRngCal_str;
   uint16 k_AEB_CloseLost_VRUEnableMask_str;
   float32 k_AEB_DBSStatTimeGap_str[ 15 ];
   float32 k_AEB_DBSMovTimeGap_str[ 15 ];
   boolean k_AEB_DBSUseRangeTrigger_str;
   boolean k_AEB_TTCAccelBasedCalMode_str;
   float32 k_AEB_DBSBrakingLvl_Factor_str;
   float32 k_AEB_LowBrkMaxRangeStat_str;
   float32 k_AEB_LowBrkMaxRangeMov_str;
   float32 k_AEB_MovTrgtFlyInMaxRange_str;
   float32 k_AEB_StatTrgtFlyInMaxRange_str;
   float32 k_AEB_TrgtFlyInMaxLatPos_str;
   uint8 k_AEB_TrgtFlyInMaxAge_str;
   uint8 k_AEB_FlyInDectIPAOffset_str;
   float32 k_AEB_DBSBrkMaxStatRange_str;
   float32 k_AEB_DBSBrkMaxMovRange_str;
   float32 k_AEB_ExtraInpathAgeCounter_z_str[ 12 ][ 12 ];
   float32 k_AEB_ExtraInpathAgeCounter_x_str[ 12 ];
   float32 k_AEB_ExtraInpathAgeCounter_y_str[ 12 ];
   float32 k_AEB_LongBikeHB_TTCMax_str;
   float32 k_AEB_LongBikeLB_TTCMax_str;
   float32 k_AEB_LongBikePF_TTCMax_str;
   float32 k_AEB_VRUNoPredictLongVelThres_str;
   float32 k_AEB_ROCDecelLimit_tbl_y_str[ 5 ];
   float32 k_AEB_ROCDecelLimit_tbl_x_str[ 5 ];
   float32 k_AEB_LoadDecelLimit_tbl_y_str[ 6 ];
   float32 k_AEB_LoadDecelLimit_tbl_x_str[ 6 ];
   float32 k_AEB_SpdDecelLimit_tbl_y_str[ 6 ];
   float32 k_AEB_SpdDecelLimit_tbl_x_str[ 6 ];
   boolean k_AEB_VRU_BrkRls_en_str;
   float32 k_AEB_VRU_SpdReduction_max_str;
   boolean k_AEB_BrkAct_LimitDecel_en_str;
   float32 k_AEB_DetBrkAct_AccelMax_str;
   float32 k_AEB_PedDecelerateDetectAccel_str;
   float32 k_AEB_TWDecelerateDetectAccel_str;
   uint16 k_AEB_VRUDecelerateDetectHdTm_str;
   float32 k_AEB_XolcLaterEntryGate_str;
   float32 k_AEB_XolcLaterExitGate_str;
   uint8 k_AEB_IniMethodVRUIPAOffset_str;
   uint8 k_AEB_HldRls_AccelPos_str;
   float32 k_AEB_CCRB_MinActiveAccel_str;
   float32 k_AEB_CCRB_ActiveDelay_str[ 12 ];
   float32 k_AEB_CCRB_ActiveDelaySpdPoints_str[ 12 ];
   boolean k_AEB_CCRB_IgnoreClassCheck_str;
   uint16 k_AEB_CCRB_ActiveHldTime_str;
   float32 k_AEB_HldAllowMaxVRUSpd_str;
   float32 k_AEB_HldAllowMaxVehSpd_str;
   float32 k_AEB_HldAllowMaxVRURange_str;
   float32 k_AEB_HldAllowMaxVehRange_str;
   boolean k_AEB_HldEntryIgnObjCheck_str;
   float32 k_AEB_HldRlsMinVRULatEst_str;
   float32 k_AEB_HldRlsMinVRULatPos_str;
   float32 k_AEB_HldRlsMinVehLatEst_str;
   float32 k_AEB_HldRlsMinVehLatPos_str;
   float32 k_AEB_HldRlsMinVehSpd_str;
   float32 k_AEB_HldRlsMinVehRange_str;
   float32 k_AEB_HldRlsMinVRURange_str;
   float32 k_AEB_HoldBrkPdlPosThres_str;
   float32 k_AEB_DrvActInHoldTm_str;
   boolean k_AEB_UseHoldTrigDly_str;
   uint8 k_AEB_CheckIniMethodMaxAge_str;
   boolean k_AEB_IBA_DecelCalMod_str;
   boolean k_AEB_IBA_BypassBrkPosPrs_str;
   boolean k_AEB_IBA_BypassDecel_str;
   boolean k_AEB_IgnoreCBLATTBCal_str;
   float32 k_AEB_HighSpdCrsLatVel_str;
   float32 k_AEB_VehMaxAllowSpdStep_str;
   uint8 k_AEB_VehMaxAllowAgeStep_str;
   boolean k_AEB_IgnVRUInpathAgeChk_str;
   uint16 k_AEB_VehRdrInfoChkFailHldTime_str;
   uint16 k_AEB_VRUIDChgChkHoldTime_str;
   boolean k_AEB_VRUHiBrkIgnLatAccEn_str;
   float32 k_AEB_host_straightly_yaw_thrh_str;
   boolean k_AEB_VRUHiBrkIgnLatEstEn_str;
   boolean k_AEB_VRUHiBrkUseRangeTrigger_str;
   float32 k_AEB_BikeHitSpdDes_mps_str[ 10 ];
   float32 k_AEB_BikeStatHitSpdDes_mps_str[ 10 ];
   float32 k_AEB_LongBikeHitSpdDes_mps_str[ 10 ];
   float32 k_AEB_OCBikeHitSpdDes_mps_str[ 10 ];
   float32 k_AEB_PedHitSpdDes_mps_str[ 10 ];
   float32 k_AEB_OCPedHitSpdDes_mps_str[ 10 ];
   float32 k_AEB_VRUTTBAvgBrkDelay_str;
   float32 k_AEB_VRUTTBAvgBrkDelay_Full_str;
   float32 k_AEB_DesHitSpdInputTbl_mps_str[ 10 ];
   float32 k_AEB_VRULowBrkMaxRng_m_str;
   float32 k_AEB_VRULowBrkMaxTTC_sec_str;
   float32 k_AEB_VRUPFMaxRng_m_str;
   float32 k_AEB_VRUPFMaxTTC_sec_str;
   float32 k_AEB_VRUPFTrigDuration_str[ 15 ];
   float32 k_AEB_VRUFLBATrigDuration_str[ 15 ];
   float32 k_AEB_VRUMinStopTrigDuration_str[ 15 ];
   float32 k_AEB_BikeLBDuration_sec_str[ 15 ];
   float32 k_AEB_BikeStatLBDuration_sec_str[ 15 ];
   float32 k_AEB_LongBikeLBDuration_sec_str[ 15 ];
   float32 k_AEB_OCBikeLBDuration_sec_str[ 15 ];
   float32 k_AEB_PedLBDuration_sec_str[ 15 ];
   float32 k_AEB_OCPedLBDuration_sec_str[ 15 ];
   boolean k_AEB_IgnoreEstHitDistChk_str;
   boolean k_AEB_IgnoreEstYawDistChk_str;
   boolean k_AEB_IgnoreXolcLaterChk_str;
   float32 k_AEB_NonCrsPed_MinSpd_mps_str;
   float32 k_AEB_NonCrsPed_LBMaxSpd_mps_str;
   float32 k_AEB_CrsPed_LBMaxSpd_mps_str;
   float32 k_AEB_StatBike_LBMaxSpd_mps_str;
   float32 k_AEB_CrsBike_LBMaxSpd_mps_str;
   float32 k_AEB_LongBike_LBMaxSpd_mps_str;
   float32 k_AEB_OCPed_LBMaxSpd_mps_str;
   float32 k_AEB_OCBike_LBMaxSpd_mps_str;
   float32 k_AEB_CrsPed_HBMaxSpd_mps_str;
   float32 k_AEB_NonCrsPed_HBMaxSpd_mps_str;
   float32 k_AEB_StatBike_HBMaxSpd_mps_str;
   float32 k_AEB_CrsBike_HBMaxSpd_mps_str;
   float32 k_AEB_LongBike_HBMaxSpd_mps_str;
   float32 k_AEB_OCPed_HBMaxSpd_mps_str;
   float32 k_AEB_OCBike_HBMaxSpd_mps_str;
   float32 k_AEB_BikeIBADuration_sec_str[ 15 ];
   float32 k_AEB_BikeStatIBADuration_sec_str[ 15 ];
   float32 k_AEB_LongBikeIBADuration_sec_str[ 15 ];
   float32 k_AEB_OCBikeIBADuration_sec_str[ 15 ];
   float32 k_AEB_PedIBADuration_sec_str[ 15 ];
   float32 k_AEB_OCPedIBADuration_sec_str[ 15 ];
   float32 k_AEB_DBSBrkVRUMaxRange_str;
   boolean k_AEB_DBSVRUMinSpdChkEnbl_str;
   float32 k_AEB_VRUDBSMaxDecel_mps_str;
   float32 k_AEB_DBSVRUMinVehicleSpd_str;
   boolean k_AEB_IBAVRU_BypassDecel_str;
   float32 k_AEB_TWLatEstComp_str;
   float32 k_AEB_VRUHiBrkLvl_mps_offset_str;
   float32 k_AEB_HiBrkLongBikeRangeOffset_str;
   float32 k_AEB_HiBrkRefRange_str;
   float32 k_AEB_VRUHiBrkRefRange_str;
   float32 k_AEB_SpdReduction_max_str;
   boolean k_AEB_Veh_BrkRls_en_str;
   float32 k_AEB_BrkPdlEngageLgAccThres_str;
   boolean k_AEB_BrkPosConfirmEn_str;
   boolean k_AEB_BrkPrsConfirmEn_str;
   boolean k_AEB_VRULoBrkIgnLatEstEn_str;
   float32 k_AEB_VRULoBrkHoldXolcThres_str;
   float32 k_AEB_VRUHiBrkRefRange_IBST_str[ 15 ];
   float32 k_AEB_VRUHiBrkRefRange_ESP_str[ 15 ];
   float32 k_AEB_LongPedLBDuration_sec_str[ 15 ];
   float32 k_AEB_HiBrkRefRange_IBST_str[ 15 ];
   float32 k_AEB_HiBrkRefRange_ESP_str[ 15 ];
   float32 k_AEB_VruHBCrossingRangeOffset_str[ 15 ];
   float32 k_AEB_DesireStopDistance_IBST_str[ 15 ];
   float32 k_AEB_DesireStopDistance_ESP_str[ 15 ];
   float32 k_AEB_CLHiBrkNeedDecelLimt_IBA_str;
   float32 k_AEB_VRUXolcUpLimit_str;
   float32 k_AEB_VRUXolcDownLimit_str;
   uint8 k_AEB_TapVehIgnStrOvrdMask_str;
   uint8 k_AEB_TapVRUIgnStrOvrdMask_str;
   boolean k_AEB_IgnDrvBehRedToFunnel_str;
   float32 k_AEB_DrvOvrdBasePreFac_FLBA_str;
   float32 k_AEB_DrvOvrdBasePosFac_FLBA_str;
   float32 k_AEB_DrvOvrdBasePreFac_PF_str;
   float32 k_AEB_DrvOvrdBasePosFac_PF_str;
   float32 k_AEB_DrvOvrdBasePreFac_LB_str;
   float32 k_AEB_DrvOvrdBasePosFac_LB_str;
   float32 k_AEB_DrvOvrdBasePreFac_HB_str;
   float32 k_AEB_DrvOvrdBasePosFac_HB_str;
   float32 k_AEB_DrvOvrdBasePreFac_FB_str;
   float32 k_AEB_DrvOvrdBasePosFac_FB_str;
   float32 k_AEB_HiSpdBrkEngPresEnblTm_str;
   float32 k_AEB_HiSpdBrkEngPosEnTime_str;
   uint16 k_AEB_GasRateEngHdTm_str;
   uint16 k_AEB_HiSpdGasRateEngHdTm_str;
   uint8 k_AEB_GasRateCntThres_str;
   uint8 k_AEB_HiSpdGasRateCntThres_str;
   boolean k_AEB_DrvEngUseTTCReduc_IBA_str;
   boolean k_AEB_BrkPdlEngageMode_str;
   float32 k_AEB_BrkEngStatusEnTime_str;
   uint16 k_AEB_BrkResetHaloTime_ms_str;
   boolean k_AEB_IgnoreBrkResetChk_str;
   boolean k_AEB_IBA_UseBrkPedal_str;
   boolean k_AEB_EnBrkResetChk_str;
   float32 k_AEB_LeadVel_OCDead_str;
   float32 k_AEB_IBA_PermitAccelGap_str;
   boolean k_AEB_BrkPosIgnore_str;
   boolean k_AEB_BrkPrsIgnore_str;
   float32 k_AEB_BikeHiConfMaxHeadError_str;
   boolean k_AEB_HostSpdEstUsed_str;
   float32 k_AEB_MovHiBrkRefRange_IBST_str[ 15 ];
   float32 k_AEB_MovHiBrkRefRange_ESP_str[ 15 ];
   float32 k_AEB_CrossHiBrkRefRange_ESP_str[ 15 ];
   float32 k_AEB_Brk_Reduc_ToFunnel_str;
   float32 k_AEB_Spd_Reduc_ToFunnel_str[ 9 ];
   uint16 k_AEB_NearTrgtReducHdTm_str;
   float32 k_AEB_GateMinLatPosVRU_str;
   uint8 k_AEB_VehMinMatchConf_str;
   float32 k_AEB_BigXolc_RedFac_str[ 9 ];
   float32 k_AEB_VRURangeBrkPoints_str[ 9 ];
   boolean k_AEB_IgnoreVRUFusChk_str;
   float32 k_AEB_HostStraightlyYawThrh_str;
   boolean k_AEB_VRUHB_UseDefaultOfst_str;
   float32 k_AEB_VRUHB_LongBikeOffset_str[ 15 ];
   float32 k_AEB_VRUHB_CrossBikeOffset_str[ 15 ];
   float32 k_AEB_VRUHB_StatBikeOffset_str[ 15 ];
   float32 k_AEB_VRUHB_LongPedOffset_str[ 15 ];
   float32 k_AEB_VRUHB_CrossPedOffset_str[ 15 ];
   float32 k_AEB_VRUHB_StatPedOffset_str[ 15 ];
   boolean k_AEB_UseLgSfJAVehCusSet_str;
   boolean k_AEB_UseLgSfJAPedCusSet_str;
   boolean k_AEB_PedVisLatEstChkDisable_str;
   float32 k_AEB_PedOCPedExitThres_str;
   boolean k_AEB_PedOCCrossingAllow_str;
   boolean k_AEB_PedIgnoreVisPlauCheck_str;
   boolean k_AEB_PedUseVisionTTC_str;
   boolean k_AEB_DisblAEBOCBicycle_str;
   boolean k_AEB_DisblAEBBicycle_str;
   boolean k_AEB_DisblAEBPed_str;
   boolean k_AEB_DisblAEBOCPed_str;
   boolean k_AEB_UseRRFunelInput_str;
   boolean k_AEB_EnableYawRateRedc_str;
   boolean k_AEB_IgnoreLongVelForCrsScene_str;
   boolean k_AEB_UseTapTTCForVRU_str;
   boolean k_AEB_IgnoreVRUXolcChk_str;
   boolean k_AEB_IgnoreVehFusionCheck_str;
   boolean k_AEB_IgnoreVehRadarCheck_str;
   boolean k_AEB_IgnoreVRUBasicCheck_str;
   boolean k_AEB_UseTapThresFunc_str;
   uint8 k_AEB_mi_VisLowConf_str;
   boolean k_AEB_AllowFCWOCBicycle_str;
   boolean k_AEB_DisblFCWBicycle_str;
   boolean k_AEB_AllowFCWOCPed_str;
   boolean k_AEB_DisblFCWPed_str;
   uint8 k_AEB_ABALevel_str;
   uint8 k_AEB_AWBLevel_str;
   boolean k_AEB_NotUseBrakeTypeFlag_str;
   boolean k_AEB_UseShadowMode_str;
   boolean k_AEB_IgnoreFusVisCheck_str;
   uint8 k_AEB_AWBAutoBrkTyp_Mask_str;
   uint16 k_AEB_MaxTime_ms_AWBReq_str;
   float32 k_AEB_DRTVisLongErrThres_str[ 9 ];
   uint32 k_AEB_DRTVisLongChkDelayTime_str;
   float32 k_AEB_FullLatVel_str;
   float32 k_AEB_NegligibleLatVel_str;
   float32 k_AEB_YawRateIgnoreLatVel_str;
   float32 k_AEB_LatVelMinStepsize_str;
   float32 k_AEB_LongVelMinStepsize_str;
   boolean k_AEB_UseVelTrackAngle_str;
   boolean k_AEB_UseLatVelforRR_str;
   boolean k_AEB_UseHostSpdBsdRR_str;
   boolean k_AEB_LatVelVisionConfirmIgnr_str;
   float32 k_AEB_Default_Time_Offset_str;
   float32 k_AEB_VehRangeBrkPoints_str[ 9 ];
   float32 k_AEB_VehRangRateBrkPoints_str[ 7 ];
   float32 k_AEB_VehLongRangeErrorThres_str[ 7 ][ 9 ];
   float32 k_AEB_VehLatRangeErrorThres_str[ 8 ];
   float32 k_AEB_TgtMomErrorThresLong_str[ 7 ];
   float32 k_AEB_TgtMomErrorThresLat_str[ 8 ];
   float32 k_AEB_VehLatRRBrkPoints_str[ 8 ];
   boolean k_AEB_VehAccuErrorChkOnLong_str;
   boolean k_AEB_VehAccuErrorChkOnLat_str;
   boolean k_AEB_VehMomeErrorChkOnLong_str;
   boolean k_AEB_VehMomeErrorChkOnLat_str;
   uint32 k_AEB_VehBaseChkFailEnblTime_str;
   uint32 k_AEB_VehBaseChkFailHoldTime_str;
   uint16 k_AEB_VehErrorAccuPerdLong_str;
   uint16 k_AEB_VehErrorAccuPerdLat_str;
   boolean k_AEB_VehLongRangeChkEnbl_str;
   boolean k_AEB_VehLatRangeChkEnbl_str;
   uint8 k_AEB_VehFusionMinAgeCount_str;
   uint8 k_AEB_VehMulTrklMinAgeCount_str;
   uint8 k_AEB_VehSingleTrkMinAgeCount_str;
   uint8 k_AEB_VehVisionMinAgeCount_str;
   uint8 k_AEB_VehMinAgeCount_str;
   uint8 k_AEB_VehDetStatus_str;
   boolean k_AEB_VehIgnoreDetProfile_str;
   float32 k_AEB_VehIgnoreDetProfileLatPos_str;
   uint16 k_AEB_VehProfileChk_HdTm_str;
   uint16 k_AEB_VehRadarIDChk_HdTm_str;
   float32 k_AEB_VehRadarIDChkRangeThres_str[ 9 ];
   float32 k_AEB_VehRangeRate_BrkPoints_str[ 9 ];
   boolean k_AEB_VehRadarIDChk_str;
   float32 k_AEB_VehRAIDChk_MinLongAccel_str;
   boolean k_AEB_IgnoreAEBPedConfCheck_str;
   boolean k_AEB_IgnoreConfCheck_str;
   boolean k_AEB_IgnoreInPathAgeCheck_str;
   uint8 k_AEB_IgnoreAebInhibit_str;
   uint16 k_AEB_IgnoreAebFault_str;
   uint16 k_AEB_Vehicle_Mass_str;
   boolean k_AEB_EPB_Present_str;
   float32 k_AEB_EspRespTime_str;
   float32 k_AEB_EspRespMaxJerk_str;
   float32 k_AEB_ESPRespomseTime_str[ 8 ];
   float32 k_AEB_ESPTmSpdBrkPoints_str[ 8 ];
   float32 k_AEB_ESPDecelDiffBrkPoints_str[ 6 ];
   float32 k_AEB_ESPDelayTime_str[ 6 ];
   boolean k_AEB_UseOriginRangeCal_str;
   float32 k_AEB_ESPRespTmHB2FB_str;
   float32 k_AEB_ESPDeftResponseTime_str;
   float32 k_AEB_VRURlsMinXolc_str;
   uint16 k_AEB_VehIgnCstMask_str;
   uint16 k_AEB_PedInterestChk_str;
   uint8 k_AEB_VehHighestConf_str;
   uint8 k_AEB_VehHiConf_str;
   float32 k_AEB_GateTOIAngle_Arr_str[ 3 ];
   float32 k_AEB_GateTOIPosi_x_str[ 3 ];
   uint8 k_Cal_LgSafe_minor_version_str;
   uint8 k_Cal_LgSafe_major_version_str;
} LongSafe_cal_T;

#define LongSafe_START_SEC_CAL_UNSPECIFIED
extern LongSafe_cal_T LongSafe_Cal_DF_V;
#define LongSafe_STOP_SEC_CAL_UNSPECIFIED
/* Access Macros for the structure elements. Please note that application
* does not use data flash memory directly and uses the RAM copy of data flash.Though
* following macros start with K_ they actually point to RAM image of calibrations.
*/

#define k_AEB_FLBA_Enabled    (LongSafe_Cal_DF_V.k_AEB_FLBA_Enabled_str)
#define k_AEB_DBS_Enabled    (LongSafe_Cal_DF_V.k_AEB_DBS_Enabled_str)
#define k_AEB_UseTestSceneFlag    (LongSafe_Cal_DF_V.k_AEB_UseTestSceneFlag_str)
#define k_AEB_UseSpecialSceneFullBrk    (LongSafe_Cal_DF_V.k_AEB_UseSpecialSceneFullBrk_str)
#define k_AEB_MinStop_Enabled    (LongSafe_Cal_DF_V.k_AEB_MinStop_Enabled_str)
#define k_AEB_AccelMinGasPedPosInhbt    (LongSafe_Cal_DF_V.k_AEB_AccelMinGasPedPosInhbt_str)
#define k_AEB_AccelTrhdMov    (LongSafe_Cal_DF_V.k_AEB_AccelTrhdMov_str)
#define k_AEB_AccelTrhdStat    (LongSafe_Cal_DF_V.k_AEB_AccelTrhdStat_str)
#define k_AEB_SpecScenHostSpdMax    (LongSafe_Cal_DF_V.k_AEB_SpecScenHostSpdMax_str)
#define k_AEB_SpecScenFBHostHiSpd    (LongSafe_Cal_DF_V.k_AEB_SpecScenFBHostHiSpd_str)
#define k_AEB_SpecScenFBHostMidSpd    (LongSafe_Cal_DF_V.k_AEB_SpecScenFBHostMidSpd_str)
#define k_AEB_SpecScenFBHostLowSpd    (LongSafe_Cal_DF_V.k_AEB_SpecScenFBHostLowSpd_str)
#define k_AEB_SpecScenFBThresInHiSpd    (LongSafe_Cal_DF_V.k_AEB_SpecScenFBThresInHiSpd_str)
#define k_AEB_SpecScenFBThresInMidSpd    (LongSafe_Cal_DF_V.k_AEB_SpecScenFBThresInMidSpd_str)
#define k_AEB_SpecScenFBThresInLowSpd    (LongSafe_Cal_DF_V.k_AEB_SpecScenFBThresInLowSpd_str)
#define k_AEB_SpecScenFBThresInElseSpd    (LongSafe_Cal_DF_V.k_AEB_SpecScenFBThresInElseSpd_str)
#define k_AEB_SpecScenHostSpdMin    (LongSafe_Cal_DF_V.k_AEB_SpecScenHostSpdMin_str)
#define k_AEB_AlgInternalLpTm_ms    (LongSafe_Cal_DF_V.k_AEB_AlgInternalLpTm_ms_str)
#define k_AEB_BrkHdTmAfterTrig_ms    (LongSafe_Cal_DF_V.k_AEB_BrkHdTmAfterTrig_ms_str)
#define k_AEB_Enable    (LongSafe_Cal_DF_V.k_AEB_Enable_str)
#define k_AEB_UseHoldTrigAfterStand    (LongSafe_Cal_DF_V.k_AEB_UseHoldTrigAfterStand_str)
#define k_AEB_AlgLpTm_sec    (LongSafe_Cal_DF_V.k_AEB_AlgLpTm_sec_str)
#define k_AEB_BrkingRampToHiStep_mps    (LongSafe_Cal_DF_V.k_AEB_BrkingRampToHiStep_mps_str)
#define k_AEB_BrkingRampToLoStep_mps    (LongSafe_Cal_DF_V.k_AEB_BrkingRampToLoStep_mps_str)
#define k_AEB_BrakingRampToZeroStep    (LongSafe_Cal_DF_V.k_AEB_BrakingRampToZeroStep_str)
#define k_AEB_DecelTrhdMov    (LongSafe_Cal_DF_V.k_AEB_DecelTrhdMov_str)
#define k_AEB_DecelTrhdStat    (LongSafe_Cal_DF_V.k_AEB_DecelTrhdStat_str)
#define k_AEB_DrvAppRefTmForAdj    (LongSafe_Cal_DF_V.k_AEB_DrvAppRefTmForAdj_str)
#define k_AEB_DrvOvrdBasePressure    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBasePressure_str)
#define k_AEB_RdrTimeStep_sec    (LongSafe_Cal_DF_V.k_AEB_RdrTimeStep_sec_str)
#define k_AEB_GasPedalMargin    (LongSafe_Cal_DF_V.k_AEB_GasPedalMargin_str)
#define k_AEB_GasPedalPositionMax    (LongSafe_Cal_DF_V.k_AEB_GasPedalPositionMax_str)
#define k_AEB_GasPedalOvrdTm_ms    (LongSafe_Cal_DF_V.k_AEB_GasPedalOvrdTm_ms_str)
#define k_AEB_GateClosingRngRtTrhd    (LongSafe_Cal_DF_V.k_AEB_GateClosingRngRtTrhd_str)
#define k_AEB_ZeroSpdTrhd1    (LongSafe_Cal_DF_V.k_AEB_ZeroSpdTrhd1_str)
#define k_AEB_ZeroSpdTrhd2    (LongSafe_Cal_DF_V.k_AEB_ZeroSpdTrhd2_str)
#define k_AEB_GateMaxObjAngle    (LongSafe_Cal_DF_V.k_AEB_GateMaxObjAngle_str)
#define k_AEB_GateMaxObjOffset    (LongSafe_Cal_DF_V.k_AEB_GateMaxObjOffset_str)
#define k_AEB_GateMaxOpeningRngRt    (LongSafe_Cal_DF_V.k_AEB_GateMaxOpeningRngRt_str)
#define k_AEB_GateMaxRangeMov    (LongSafe_Cal_DF_V.k_AEB_GateMaxRangeMov_str)
#define k_AEB_GateMaxRangeStat    (LongSafe_Cal_DF_V.k_AEB_GateMaxRangeStat_str)
#define k_AEB_GateMaxTOIAngle    (LongSafe_Cal_DF_V.k_AEB_GateMaxTOIAngle_str)
#define k_AEB_GateMinROC    (LongSafe_Cal_DF_V.k_AEB_GateMinROC_str)
#define k_AEB_UseInFunnelChk    (LongSafe_Cal_DF_V.k_AEB_UseInFunnelChk_str)
#define k_AEB_HiBrkHdTm    (LongSafe_Cal_DF_V.k_AEB_HiBrkHdTm_str)
#define k_AEB_HiBrkLdTmStat_sec    (LongSafe_Cal_DF_V.k_AEB_HiBrkLdTmStat_sec_str)
#define k_AEB_AEBEgoSpdKneePoints    (LongSafe_Cal_DF_V.k_AEB_AEBEgoSpdKneePoints_str)
#define k_AEB_MEAEBEgoSpdKneePoints    (LongSafe_Cal_DF_V.k_AEB_MEAEBEgoSpdKneePoints_str)
#define k_AEB_HiBrkLdTmMov_sec    (LongSafe_Cal_DF_V.k_AEB_HiBrkLdTmMov_sec_str)
#define k_AEB_VehHiBrkLowPersistanceCnt    (LongSafe_Cal_DF_V.k_AEB_VehHiBrkLowPersistanceCnt_str)
#define k_AEB_VRUHiBrkLowPersistanceCnt    (LongSafe_Cal_DF_V.k_AEB_VRUHiBrkLowPersistanceCnt_str)
#define k_AEB_HiBrkACCStrongBrkCnt    (LongSafe_Cal_DF_V.k_AEB_HiBrkACCStrongBrkCnt_str)
#define k_AEB_HiBrkMaxSpdMov    (LongSafe_Cal_DF_V.k_AEB_HiBrkMaxSpdMov_str)
#define k_AEB_HiBrkMaxSpdStat    (LongSafe_Cal_DF_V.k_AEB_HiBrkMaxSpdStat_str)
#define k_AEB_HiBrkMinRlsTm    (LongSafe_Cal_DF_V.k_AEB_HiBrkMinRlsTm_str)
#define k_AEB_HiBrakingLvlMov_mps    (LongSafe_Cal_DF_V.k_AEB_HiBrakingLvlMov_mps_str)
#define k_AEB_HiBrakingLvlStat_mps    (LongSafe_Cal_DF_V.k_AEB_HiBrakingLvlStat_mps_str)
#define k_AEB_LittleBrakeDecel_mps    (LongSafe_Cal_DF_V.k_AEB_LittleBrakeDecel_mps_str)
#define k_AEB_HiBrkMinSpdChkEnbl    (LongSafe_Cal_DF_V.k_AEB_HiBrkMinSpdChkEnbl_str)
#define k_AEB_HoldDrvActionWithBrk    (LongSafe_Cal_DF_V.k_AEB_HoldDrvActionWithBrk_str)
#define k_AEB_DBSAbsMaxDecel    (LongSafe_Cal_DF_V.k_AEB_DBSAbsMaxDecel_str)
#define k_AEB_DBSLdTmMov_sec    (LongSafe_Cal_DF_V.k_AEB_DBSLdTmMov_sec_str)
#define k_AEB_DBSLdTmStat_sec    (LongSafe_Cal_DF_V.k_AEB_DBSLdTmStat_sec_str)
#define k_AEB_WrapperLpTm_ms    (LongSafe_Cal_DF_V.k_AEB_WrapperLpTm_ms_str)
#define k_AEB_LCHighFactor    (LongSafe_Cal_DF_V.k_AEB_LCHighFactor_str)
#define k_AEB_LCHdTm    (LongSafe_Cal_DF_V.k_AEB_LCHdTm_str)
#define k_AEB_LCLongTermSteerGain    (LongSafe_Cal_DF_V.k_AEB_LCLongTermSteerGain_str)
#define k_AEB_LCSpdIntercept    (LongSafe_Cal_DF_V.k_AEB_LCSpdIntercept_str)
#define k_AEB_LCSpdSlope    (LongSafe_Cal_DF_V.k_AEB_LCSpdSlope_str)
#define k_AEB_LwBrkLateralLimit    (LongSafe_Cal_DF_V.k_AEB_LwBrkLateralLimit_str)
#define k_AEB_LwBrkLdTmMov_sec    (LongSafe_Cal_DF_V.k_AEB_LwBrkLdTmMov_sec_str)
#define k_AEB_LwBrkLdTmStat_sec    (LongSafe_Cal_DF_V.k_AEB_LwBrkLdTmStat_sec_str)
#define k_AEB_LwBrkMaxSpdMov    (LongSafe_Cal_DF_V.k_AEB_LwBrkMaxSpdMov_str)
#define k_AEB_LwBrkMaxSpdStat    (LongSafe_Cal_DF_V.k_AEB_LwBrkMaxSpdStat_str)
#define k_AEB_LwBrkMinSpdChkEnbl    (LongSafe_Cal_DF_V.k_AEB_LwBrkMinSpdChkEnbl_str)
#define k_AEB_LwBrkPersistanceCnt    (LongSafe_Cal_DF_V.k_AEB_LwBrkPersistanceCnt_str)
#define k_AEB_LwBrakingLvl_mps    (LongSafe_Cal_DF_V.k_AEB_LwBrakingLvl_mps_str)
#define k_AEB_LwBrakingThrshACCBrk    (LongSafe_Cal_DF_V.k_AEB_LwBrakingThrshACCBrk_str)
#define k_AEB_MinClosingSpd    (LongSafe_Cal_DF_V.k_AEB_MinClosingSpd_str)
#define k_AEB_MinVehicleSpd    (LongSafe_Cal_DF_V.k_AEB_MinVehicleSpd_str)
#define k_AEB_MovingAwayNoiseLvlNeg    (LongSafe_Cal_DF_V.k_AEB_MovingAwayNoiseLvlNeg_str)
#define k_AEB_MovingAwayNoiseLvlPos    (LongSafe_Cal_DF_V.k_AEB_MovingAwayNoiseLvlPos_str)
#define k_AEB_PathFarWidthEntryGate    (LongSafe_Cal_DF_V.k_AEB_PathFarWidthEntryGate_str)
#define k_AEB_PathFarWidthExitGate    (LongSafe_Cal_DF_V.k_AEB_PathFarWidthExitGate_str)
#define k_AEB_PathHitDistanceEntryGate    (LongSafe_Cal_DF_V.k_AEB_PathHitDistanceEntryGate_str)
#define k_AEB_PathHitDistanceExitGate    (LongSafe_Cal_DF_V.k_AEB_PathHitDistanceExitGate_str)
#define k_AEB_PathNearFarTransitRng    (LongSafe_Cal_DF_V.k_AEB_PathNearFarTransitRng_str)
#define k_AEB_PathNearWidthEntryGate    (LongSafe_Cal_DF_V.k_AEB_PathNearWidthEntryGate_str)
#define k_AEB_PathNearWidthExitGate    (LongSafe_Cal_DF_V.k_AEB_PathNearWidthExitGate_str)
#define k_AEB_PathYawDistanceEntryGate    (LongSafe_Cal_DF_V.k_AEB_PathYawDistanceEntryGate_str)
#define k_AEB_PathYawDistanceExitGate    (LongSafe_Cal_DF_V.k_AEB_PathYawDistanceExitGate_str)
#define k_AEB_DBSPathYawDistExitGate    (LongSafe_Cal_DF_V.k_AEB_DBSPathYawDistExitGate_str)
#define k_AEB_PrefillLateralLimit    (LongSafe_Cal_DF_V.k_AEB_PrefillLateralLimit_str)
#define k_AEB_PrefillLdTmMov_sec    (LongSafe_Cal_DF_V.k_AEB_PrefillLdTmMov_sec_str)
#define k_AEB_PrefillLdTmStat_sec    (LongSafe_Cal_DF_V.k_AEB_PrefillLdTmStat_sec_str)
#define k_AEB_PrefillMinSpdChkEnbl    (LongSafe_Cal_DF_V.k_AEB_PrefillMinSpdChkEnbl_str)
#define k_AEB_ReferLowToTTEMinStat    (LongSafe_Cal_DF_V.k_AEB_ReferLowToTTEMinStat_str)
#define k_AEB_UseTwoLevelDecel    (LongSafe_Cal_DF_V.k_AEB_UseTwoLevelDecel_str)
#define k_AEB_ReleaseOvrdTime_ms    (LongSafe_Cal_DF_V.k_AEB_ReleaseOvrdTime_ms_str)
#define k_AEB_SteeringInhibitHaloTime    (LongSafe_Cal_DF_V.k_AEB_SteeringInhibitHaloTime_str)
#define k_AEB_SteeringAngleRtTrhd    (LongSafe_Cal_DF_V.k_AEB_SteeringAngleRtTrhd_str)
#define k_AEB_OvrdSteeringRateMax    (LongSafe_Cal_DF_V.k_AEB_OvrdSteeringRateMax_str)
#define k_AEB_JAOvrdSteeringRateMax    (LongSafe_Cal_DF_V.k_AEB_JAOvrdSteeringRateMax_str)
#define k_AEB_JAOvrdYawRateMax    (LongSafe_Cal_DF_V.k_AEB_JAOvrdYawRateMax_str)
#define k_AEB_SteeringRtOvrdGain    (LongSafe_Cal_DF_V.k_AEB_SteeringRtOvrdGain_str)
#define k_AEB_TTBAccBrkDelay    (LongSafe_Cal_DF_V.k_AEB_TTBAccBrkDelay_str)
#define k_AEB_TTBAvgBrkDelay    (LongSafe_Cal_DF_V.k_AEB_TTBAvgBrkDelay_str)
#define k_AEB_TTBMaxSpd    (LongSafe_Cal_DF_V.k_AEB_TTBMaxSpd_str)
#define k_AEB_TTCIntegAccelEntry    (LongSafe_Cal_DF_V.k_AEB_TTCIntegAccelEntry_str)
#define k_AEB_TTCIntegAccelExit    (LongSafe_Cal_DF_V.k_AEB_TTCIntegAccelExit_str)
#define k_AEB_TTCIntegDecelEntry    (LongSafe_Cal_DF_V.k_AEB_TTCIntegDecelEntry_str)
#define k_AEB_TTCIntegDecelExit    (LongSafe_Cal_DF_V.k_AEB_TTCIntegDecelExit_str)
#define k_AEB_TTCIntegMaxSteps    (LongSafe_Cal_DF_V.k_AEB_TTCIntegMaxSteps_str)
#define k_AEB_TTCIntegMaxTime    (LongSafe_Cal_DF_V.k_AEB_TTCIntegMaxTime_str)
#define k_AEB_TTCIntegTimeStep    (LongSafe_Cal_DF_V.k_AEB_TTCIntegTimeStep_str)
#define k_AEB_TTCLowerClip_x    (LongSafe_Cal_DF_V.k_AEB_TTCLowerClip_x_str)
#define k_AEB_TTCLowerClip_z    (LongSafe_Cal_DF_V.k_AEB_TTCLowerClip_z_str)
#define k_AEB_TTCMax    (LongSafe_Cal_DF_V.k_AEB_TTCMax_str)
#define k_AEB_TTCMaxEvalTime    (LongSafe_Cal_DF_V.k_AEB_TTCMaxEvalTime_str)
#define k_AEB_TTCMinEvalTime    (LongSafe_Cal_DF_V.k_AEB_TTCMinEvalTime_str)
#define k_AEB_TTTAverageTurnAccel    (LongSafe_Cal_DF_V.k_AEB_TTTAverageTurnAccel_str)
#define k_AEB_TTCMinClipSpd    (LongSafe_Cal_DF_V.k_AEB_TTCMinClipSpd_str)
#define k_AEB_TTCMinClipRR    (LongSafe_Cal_DF_V.k_AEB_TTCMinClipRR_str)
#define k_AEB_TTCUpperClip_x    (LongSafe_Cal_DF_V.k_AEB_TTCUpperClip_x_str)
#define k_AEB_TTCUpperClip_z    (LongSafe_Cal_DF_V.k_AEB_TTCUpperClip_z_str)
#define k_AEB_TTTMinLatMovement    (LongSafe_Cal_DF_V.k_AEB_TTTMinLatMovement_str)
#define k_AEB_WheelSpdFilterGain    (LongSafe_Cal_DF_V.k_AEB_WheelSpdFilterGain_str)
#define k_AEB_YawNeutral    (LongSafe_Cal_DF_V.k_AEB_YawNeutral_str)
#define k_AEB_YawNoiseFloorForXolc    (LongSafe_Cal_DF_V.k_AEB_YawNoiseFloorForXolc_str)
#define k_AEB_HostAcceAeblRdcFac    (LongSafe_Cal_DF_V.k_AEB_HostAcceAeblRdcFac_str)
#define k_AEB_HostAccelPoints    (LongSafe_Cal_DF_V.k_AEB_HostAccelPoints_str)
#define k_AEB_HMIBrakingEnbld    (LongSafe_Cal_DF_V.k_AEB_HMIBrakingEnbld_str)
#define k_AEB_LowBrakeAlertEnbl    (LongSafe_Cal_DF_V.k_AEB_LowBrakeAlertEnbl_str)
#define k_AEB_PrefillBrakeAlertEnbl    (LongSafe_Cal_DF_V.k_AEB_PrefillBrakeAlertEnbl_str)
#define k_AEB_OvrdYawRateMax    (LongSafe_Cal_DF_V.k_AEB_OvrdYawRateMax_str)
#define k_AEB_SteerOvrdOffHdTm    (LongSafe_Cal_DF_V.k_AEB_SteerOvrdOffHdTm_str)
#define k_AEB_SteerOvrdOffTTEMinMinusX    (LongSafe_Cal_DF_V.k_AEB_SteerOvrdOffTTEMinMinusX_str)
#define k_AEB_VehSSettingValue    (LongSafe_Cal_DF_V.k_AEB_VehSSettingValue_str)
#define k_AEB_FLBALatchTime    (LongSafe_Cal_DF_V.k_AEB_FLBALatchTime_str)
#define k_AEB_PrefillLatchTime    (LongSafe_Cal_DF_V.k_AEB_PrefillLatchTime_str)
#define k_AEB_UsePrefillOverride    (LongSafe_Cal_DF_V.k_AEB_UsePrefillOverride_str)
#define k_AEB_UseUnclippedComTTC    (LongSafe_Cal_DF_V.k_AEB_UseUnclippedComTTC_str)
#define k_AEB_OnlyCommonTTC    (LongSafe_Cal_DF_V.k_AEB_OnlyCommonTTC_str)
#define k_AEB_RCSFilterGain    (LongSafe_Cal_DF_V.k_AEB_RCSFilterGain_str)
#define k_AEB_AllowHiBrkUnclipped    (LongSafe_Cal_DF_V.k_AEB_AllowHiBrkUnclipped_str)
#define k_AEB_HeavyHighSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_HeavyHighSpdTrhd_str)
#define k_AEB_HeavyFullSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_HeavyFullSpdTrhd_str)
#define k_AEB_MinHeavyFullSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_MinHeavyFullSpdTrhd_str)
#define k_AEB_MaxHeavyFullSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_MaxHeavyFullSpdTrhd_str)
#define k_AEB_FullBrakingLvlMov_mps    (LongSafe_Cal_DF_V.k_AEB_FullBrakingLvlMov_mps_str)
#define k_AEB_FullBrakingLvlStat_mps    (LongSafe_Cal_DF_V.k_AEB_FullBrakingLvlStat_mps_str)
#define k_AEB_MaxDecelRadarOnly    (LongSafe_Cal_DF_V.k_AEB_MaxDecelRadarOnly_str)
#define k_AEB_CnfmByCameraEnbl    (LongSafe_Cal_DF_V.k_AEB_CnfmByCameraEnbl_str)
#define k_AEB_HiBrkSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_HiBrkSpdTrhd_str)
#define k_AEB_ZeroSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_ZeroSpdTrhd_str)
#define k_AEB_CIBEventLatchTime    (LongSafe_Cal_DF_V.k_AEB_CIBEventLatchTime_str)
#define k_AEB_BrkHdTmAfterStop    (LongSafe_Cal_DF_V.k_AEB_BrkHdTmAfterStop_str)
#define k_AEB_TestSceneHdTm_ms    (LongSafe_Cal_DF_V.k_AEB_TestSceneHdTm_ms_str)
#define k_AEB_FltGainLateralAccel    (LongSafe_Cal_DF_V.k_AEB_FltGainLateralAccel_str)
#define k_AEB_VRUHiBrkMaxSpd    (LongSafe_Cal_DF_V.k_AEB_VRUHiBrkMaxSpd_str)
#define k_AEB_OCBike_ABAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_OCBike_ABAMaxSpd_mps_str)
#define k_AEB_LongBike_ABAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_LongBike_ABAMaxSpd_mps_str)
#define k_AEB_CrsBike_ABAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_CrsBike_ABAMaxSpd_mps_str)
#define k_AEB_StatBike_ABAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_StatBike_ABAMaxSpd_mps_str)
#define k_AEB_OCPed_ABAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_OCPed_ABAMaxSpd_mps_str)
#define k_AEB_NonCrsPed_ABAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_NonCrsPed_ABAMaxSpd_mps_str)
#define k_AEB_CrsPed_ABAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_CrsPed_ABAMaxSpd_mps_str)
#define k_AEB_OCBike_IBAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_OCBike_IBAMaxSpd_mps_str)
#define k_AEB_LongBike_IBAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_LongBike_IBAMaxSpd_mps_str)
#define k_AEB_CrsBike_IBAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_CrsBike_IBAMaxSpd_mps_str)
#define k_AEB_StatBike_IBAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_StatBike_IBAMaxSpd_mps_str)
#define k_AEB_OCPed_IBAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_OCPed_IBAMaxSpd_mps_str)
#define k_AEB_NonCrsPed_IBAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_NonCrsPed_IBAMaxSpd_mps_str)
#define k_AEB_CrsPed_IBAMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_CrsPed_IBAMaxSpd_mps_str)
#define k_AEB_NonCrsPed_IBAMinSpd_mps    (LongSafe_Cal_DF_V.k_AEB_NonCrsPed_IBAMinSpd_mps_str)
#define k_AEB_VRUMinHostSpd_mps    (LongSafe_Cal_DF_V.k_AEB_VRUMinHostSpd_mps_str)
#define k_AEB_VRUMaxHostSpd_mps    (LongSafe_Cal_DF_V.k_AEB_VRUMaxHostSpd_mps_str)
#define k_AEB_PFVRUMaxHostSpd_mps    (LongSafe_Cal_DF_V.k_AEB_PFVRUMaxHostSpd_mps_str)
#define k_AEB_VRULongRange    (LongSafe_Cal_DF_V.k_AEB_VRULongRange_str)
#define k_AEB_VRULatOffsetTrhd    (LongSafe_Cal_DF_V.k_AEB_VRULatOffsetTrhd_str)
#define k_AEB_VRUEnable    (LongSafe_Cal_DF_V.k_AEB_VRUEnable_str)
#define k_AEB_EnableOncoming    (LongSafe_Cal_DF_V.k_AEB_EnableOncoming_str)
#define k_AEB_UseHostLatAccel    (LongSafe_Cal_DF_V.k_AEB_UseHostLatAccel_str)
#define k_AEB_VRUYPosHoldOnTrhd    (LongSafe_Cal_DF_V.k_AEB_VRUYPosHoldOnTrhd_str)
#define k_AEB_MinMatchConfMov    (LongSafe_Cal_DF_V.k_AEB_MinMatchConfMov_str)
#define k_AEB_MinMatchConfStat    (LongSafe_Cal_DF_V.k_AEB_MinMatchConfStat_str)
#define k_AEB_UseROCXolc    (LongSafe_Cal_DF_V.k_AEB_UseROCXolc_str)
#define k_AEB_HostLatAccelSign    (LongSafe_Cal_DF_V.k_AEB_HostLatAccelSign_str)
#define k_AEB_RevGearHoldRlsEnbl    (LongSafe_Cal_DF_V.k_AEB_RevGearHoldRlsEnbl_str)
#define k_AEB_TTCAnnoyOffset    (LongSafe_Cal_DF_V.k_AEB_TTCAnnoyOffset_str)
#define k_AEB_TTCAnnoyMinEnbl    (LongSafe_Cal_DF_V.k_AEB_TTCAnnoyMinEnbl_str)
#define k_AEB_TTCAnnoyMax    (LongSafe_Cal_DF_V.k_AEB_TTCAnnoyMax_str)
#define k_AEB_ReferLeadAccel    (LongSafe_Cal_DF_V.k_AEB_ReferLeadAccel_str)
#define k_AEB_GateMinOpeningRange    (LongSafe_Cal_DF_V.k_AEB_GateMinOpeningRange_str)
#define k_AEB_UseMinTrkAccel    (LongSafe_Cal_DF_V.k_AEB_UseMinTrkAccel_str)
#define k_AEB_HighBrkAnnoyTTCThrs    (LongSafe_Cal_DF_V.k_AEB_HighBrkAnnoyTTCThrs_str)
#define k_AEB_HighBrkLeadDecelTrhd    (LongSafe_Cal_DF_V.k_AEB_HighBrkLeadDecelTrhd_str)
#define k_AEB_HiBrkLdTmStop_sec    (LongSafe_Cal_DF_V.k_AEB_HiBrkLdTmStop_sec_str)
#define k_AEB_HiBrkLdTmStop_mps    (LongSafe_Cal_DF_V.k_AEB_HiBrkLdTmStop_mps_str)
#define k_AEB_AlertOnlyTTCTrhd    (LongSafe_Cal_DF_V.k_AEB_AlertOnlyTTCTrhd_str)
#define k_AEB_HostAccelInhbtTrhd    (LongSafe_Cal_DF_V.k_AEB_HostAccelInhbtTrhd_str)
#define k_AEB_UseLeadAccelFCW    (LongSafe_Cal_DF_V.k_AEB_UseLeadAccelFCW_str)
#define k_AEB_BrkPedPosFiltgain    (LongSafe_Cal_DF_V.k_AEB_BrkPedPosFiltgain_str)
#define k_AEB_DBSDrvBrkPdlPosThres    (LongSafe_Cal_DF_V.k_AEB_DBSDrvBrkPdlPosThres_str)
#define k_AEB_DBSDrvBrkPdlPrsThres    (LongSafe_Cal_DF_V.k_AEB_DBSDrvBrkPdlPrsThres_str)
#define k_AEB_DBSPedRateEnblTm    (LongSafe_Cal_DF_V.k_AEB_DBSPedRateEnblTm_str)
#define k_AEB_DBSPedRateHdTm    (LongSafe_Cal_DF_V.k_AEB_DBSPedRateHdTm_str)
#define k_AEB_DBSActiveMinPedPos    (LongSafe_Cal_DF_V.k_AEB_DBSActiveMinPedPos_str)
#define k_AEB_DBSPedPosEnblTm    (LongSafe_Cal_DF_V.k_AEB_DBSPedPosEnblTm_str)
#define k_AEB_DBSMinBrkPedRateOff    (LongSafe_Cal_DF_V.k_AEB_DBSMinBrkPedRateOff_str)
#define k_AEB_DBSPedRateDsblTm    (LongSafe_Cal_DF_V.k_AEB_DBSPedRateDsblTm_str)
#define k_AEB_DBSReleaseMinPedPos    (LongSafe_Cal_DF_V.k_AEB_DBSReleaseMinPedPos_str)
#define k_AEB_DBSPedPosDisableTime    (LongSafe_Cal_DF_V.k_AEB_DBSPedPosDisableTime_str)
#define k_AEB_DBSMinBrkPedRateOn    (LongSafe_Cal_DF_V.k_AEB_DBSMinBrkPedRateOn_str)
#define k_AEB_DBSLBMinBrkPedRateOn    (LongSafe_Cal_DF_V.k_AEB_DBSLBMinBrkPedRateOn_str)
#define k_AEB_DBSHBMinBrkPedRateOn    (LongSafe_Cal_DF_V.k_AEB_DBSHBMinBrkPedRateOn_str)
#define k_AEB_DBSFBMinBrkPedRateOn    (LongSafe_Cal_DF_V.k_AEB_DBSFBMinBrkPedRateOn_str)
#define k_AEB_DrvBrkPressFiltgain    (LongSafe_Cal_DF_V.k_AEB_DrvBrkPressFiltgain_str)
#define k_AEB_DBSMinDrvAppBrkPresOn    (LongSafe_Cal_DF_V.k_AEB_DBSMinDrvAppBrkPresOn_str)
#define k_AEB_DBSPressEnblTm    (LongSafe_Cal_DF_V.k_AEB_DBSPressEnblTm_str)
#define k_AEB_DBSDrvBrkPrsRateOn    (LongSafe_Cal_DF_V.k_AEB_DBSDrvBrkPrsRateOn_str)
#define k_AEB_DBSPrsRateEnblTm    (LongSafe_Cal_DF_V.k_AEB_DBSPrsRateEnblTm_str)
#define k_AEB_DBSMinDrvAppBrkPresOff    (LongSafe_Cal_DF_V.k_AEB_DBSMinDrvAppBrkPresOff_str)
#define k_AEB_DBSPressDisableTime    (LongSafe_Cal_DF_V.k_AEB_DBSPressDisableTime_str)
#define k_AEB_DBSDrvBrkPrsRateOff    (LongSafe_Cal_DF_V.k_AEB_DBSDrvBrkPrsRateOff_str)
#define k_AEB_DBSPrsRateDisableTime    (LongSafe_Cal_DF_V.k_AEB_DBSPrsRateDisableTime_str)
#define k_AEB_DBSAccelOffset_sec    (LongSafe_Cal_DF_V.k_AEB_DBSAccelOffset_sec_str)
#define k_AEB_DBSAccelOffset_mpss    (LongSafe_Cal_DF_V.k_AEB_DBSAccelOffset_mpss_str)
#define k_AEB_DBSWhlSpdAcceEnbl    (LongSafe_Cal_DF_V.k_AEB_DBSWhlSpdAcceEnbl_str)
#define k_AEB_DBSTTCBsdRampdownRate    (LongSafe_Cal_DF_V.k_AEB_DBSTTCBsdRampdownRate_str)
#define k_AEB_DBSTTCBsdRampdown_sec    (LongSafe_Cal_DF_V.k_AEB_DBSTTCBsdRampdown_sec_str)
#define k_AEB_DBSTTCBsdRampupRate    (LongSafe_Cal_DF_V.k_AEB_DBSTTCBsdRampupRate_str)
#define k_AEB_DBSTTCBsdRampup_sec    (LongSafe_Cal_DF_V.k_AEB_DBSTTCBsdRampup_sec_str)
#define k_AEB_DBSBrkPedPosOnlyEnbl    (LongSafe_Cal_DF_V.k_AEB_DBSBrkPedPosOnlyEnbl_str)
#define k_AEB_DBSDrvBrkPrsOnlyEnbl    (LongSafe_Cal_DF_V.k_AEB_DBSDrvBrkPrsOnlyEnbl_str)
#define k_AEB_DBSMinLeadAccel    (LongSafe_Cal_DF_V.k_AEB_DBSMinLeadAccel_str)
#define k_AEB_DBSMinRangeAccel    (LongSafe_Cal_DF_V.k_AEB_DBSMinRangeAccel_str)
#define k_AEB_DBSLeadAccelFact    (LongSafe_Cal_DF_V.k_AEB_DBSLeadAccelFact_str)
#define k_AEB_DBSHostDecelThrsFac    (LongSafe_Cal_DF_V.k_AEB_DBSHostDecelThrsFac_str)
#define k_AEB_DBSMinDecelRampOut    (LongSafe_Cal_DF_V.k_AEB_DBSMinDecelRampOut_str)
#define k_AEB_HostAccelInhbtHaloTime    (LongSafe_Cal_DF_V.k_AEB_HostAccelInhbtHaloTime_str)
#define k_AEB_DBSBrkDualCnfmEnbl    (LongSafe_Cal_DF_V.k_AEB_DBSBrkDualCnfmEnbl_str)
#define k_AEB_DBSDualConfirmMaxTime    (LongSafe_Cal_DF_V.k_AEB_DBSDualConfirmMaxTime_str)
#define k_AEB_DBSMaxActivationWindow    (LongSafe_Cal_DF_V.k_AEB_DBSMaxActivationWindow_str)
#define k_AEB_DBSBrakeCnfmEnbl    (LongSafe_Cal_DF_V.k_AEB_DBSBrakeCnfmEnbl_str)
#define k_AEB_DBSLeadAclOfst_sec    (LongSafe_Cal_DF_V.k_AEB_DBSLeadAclOfst_sec_str)
#define k_AEB_DBSLeadAclOfst_mpss    (LongSafe_Cal_DF_V.k_AEB_DBSLeadAclOfst_mpss_str)
#define k_AEB_DBSMinStopDistance    (LongSafe_Cal_DF_V.k_AEB_DBSMinStopDistance_str)
#define k_AEB_DBSMinStopDistanceLmt    (LongSafe_Cal_DF_V.k_AEB_DBSMinStopDistanceLmt_str)
#define k_AEB_DBSRRAccelFiltGain    (LongSafe_Cal_DF_V.k_AEB_DBSRRAccelFiltGain_str)
#define k_AEB_DBSRngAccelFiltGain    (LongSafe_Cal_DF_V.k_AEB_DBSRngAccelFiltGain_str)
#define k_AEB_DBSRngBsdAccelEnbl    (LongSafe_Cal_DF_V.k_AEB_DBSRngBsdAccelEnbl_str)
#define k_AEB_DBSLdAclBsdAccelEnbl    (LongSafe_Cal_DF_V.k_AEB_DBSLdAclBsdAccelEnbl_str)
#define k_AEB_DrvOvrdBaseBrkPdPos    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBaseBrkPdPos_str)
#define k_AEB_PrefillMaxSpdMov    (LongSafe_Cal_DF_V.k_AEB_PrefillMaxSpdMov_str)
#define k_AEB_PrefillMaxSpdStat    (LongSafe_Cal_DF_V.k_AEB_PrefillMaxSpdStat_str)
#define k_AEB_FLBALdTmMov_sec    (LongSafe_Cal_DF_V.k_AEB_FLBALdTmMov_sec_str)
#define k_AEB_FLBALdTmStat_sec    (LongSafe_Cal_DF_V.k_AEB_FLBALdTmStat_sec_str)
#define k_AEB_MSLdTmMov_sec    (LongSafe_Cal_DF_V.k_AEB_MSLdTmMov_sec_str)
#define k_AEB_MSLdTmStat_sec    (LongSafe_Cal_DF_V.k_AEB_MSLdTmStat_sec_str)
#define k_AEB_FLBAMinSpdChkEnbl    (LongSafe_Cal_DF_V.k_AEB_FLBAMinSpdChkEnbl_str)
#define k_AEB_FLBAMaxSpdMov    (LongSafe_Cal_DF_V.k_AEB_FLBAMaxSpdMov_str)
#define k_AEB_FLBAMaxSpdStat    (LongSafe_Cal_DF_V.k_AEB_FLBAMaxSpdStat_str)
#define k_AEB_MSMinSpdChkEnbl    (LongSafe_Cal_DF_V.k_AEB_MSMinSpdChkEnbl_str)
#define k_AEB_MSMaxSpdMov    (LongSafe_Cal_DF_V.k_AEB_MSMaxSpdMov_str)
#define k_AEB_MSMaxSpdStat    (LongSafe_Cal_DF_V.k_AEB_MSMaxSpdStat_str)
#define k_AEB_DBSMaxSpdMov    (LongSafe_Cal_DF_V.k_AEB_DBSMaxSpdMov_str)
#define k_AEB_DBSMaxSpdStat    (LongSafe_Cal_DF_V.k_AEB_DBSMaxSpdStat_str)
#define k_AEB_VRUMinMatchConf    (LongSafe_Cal_DF_V.k_AEB_VRUMinMatchConf_str)
#define k_AEB_VRUDBSEnbl    (LongSafe_Cal_DF_V.k_AEB_VRUDBSEnbl_str)
#define k_AEB_SteerOvrdOffTTEMin    (LongSafe_Cal_DF_V.k_AEB_SteerOvrdOffTTEMin_str)
#define k_AEB_FLBADefaultEnbl    (LongSafe_Cal_DF_V.k_AEB_FLBADefaultEnbl_str)
#define k_AEB_FLBAIgnoreHMIStng    (LongSafe_Cal_DF_V.k_AEB_FLBAIgnoreHMIStng_str)
#define k_AEB_FLBAHMICustStng    (LongSafe_Cal_DF_V.k_AEB_FLBAHMICustStng_str)
#define k_AEB_MinStopDefaultEnbl    (LongSafe_Cal_DF_V.k_AEB_MinStopDefaultEnbl_str)
#define k_AEB_MinStopIgnoreHMIStng    (LongSafe_Cal_DF_V.k_AEB_MinStopIgnoreHMIStng_str)
#define k_AEB_MinStopHMICustStng    (LongSafe_Cal_DF_V.k_AEB_MinStopHMICustStng_str)
#define k_AEB_DBSIgnoreHMIStng    (LongSafe_Cal_DF_V.k_AEB_DBSIgnoreHMIStng_str)
#define k_AEB_DBSHMICustStng    (LongSafe_Cal_DF_V.k_AEB_DBSHMICustStng_str)
#define k_AEB_IgnLowBrkHBTimerReset    (LongSafe_Cal_DF_V.k_AEB_IgnLowBrkHBTimerReset_str)
#define k_AEB_DBSMaxDecelExitTime    (LongSafe_Cal_DF_V.k_AEB_DBSMaxDecelExitTime_str)
#define k_AEB_PrefillExitTime    (LongSafe_Cal_DF_V.k_AEB_PrefillExitTime_str)
#define k_AEB_FLBAExitTime    (LongSafe_Cal_DF_V.k_AEB_FLBAExitTime_str)
#define k_AEB_MinStopExitTime    (LongSafe_Cal_DF_V.k_AEB_MinStopExitTime_str)
#define k_AEB_MaxDecelExitTime    (LongSafe_Cal_DF_V.k_AEB_MaxDecelExitTime_str)
#define k_AEB_HoldRelPressure    (LongSafe_Cal_DF_V.k_AEB_HoldRelPressure_str)
#define k_AEB_UseOnlyBrkPrsHldRel    (LongSafe_Cal_DF_V.k_AEB_UseOnlyBrkPrsHldRel_str)
#define k_AEB_NoEPBBrakeHdTm    (LongSafe_Cal_DF_V.k_AEB_NoEPBBrakeHdTm_str)
#define k_AEB_VRUOncomingEnbl    (LongSafe_Cal_DF_V.k_AEB_VRUOncomingEnbl_str)
#define k_AEB_HiConfOCBikePFTTC_sec    (LongSafe_Cal_DF_V.k_AEB_HiConfOCBikePFTTC_sec_str)
#define k_AEB_HiConfOCBikeLoBrkTTC_sec    (LongSafe_Cal_DF_V.k_AEB_HiConfOCBikeLoBrkTTC_sec_str)
#define k_AEB_HiConfOCBikeHiBrkTTC_sec    (LongSafe_Cal_DF_V.k_AEB_HiConfOCBikeHiBrkTTC_sec_str)
#define k_AEB_HiConfOCPedPrefillTTC_sec    (LongSafe_Cal_DF_V.k_AEB_HiConfOCPedPrefillTTC_sec_str)
#define k_AEB_HiConfOCPedLoBrkTTC_sec    (LongSafe_Cal_DF_V.k_AEB_HiConfOCPedLoBrkTTC_sec_str)
#define k_AEB_HiConfOCPedHiBrkTTC_sec    (LongSafe_Cal_DF_V.k_AEB_HiConfOCPedHiBrkTTC_sec_str)
#define k_AEB_AccelOffsetRangeBrkPoints    (LongSafe_Cal_DF_V.k_AEB_AccelOffsetRangeBrkPoints_str)
#define k_AEB_SteerOvrdDisbleType    (LongSafe_Cal_DF_V.k_AEB_SteerOvrdDisbleType_str)
#define k_AEB_HighBrkAnnoyTTCLose    (LongSafe_Cal_DF_V.k_AEB_HighBrkAnnoyTTCLose_str)
#define k_AEB_LowBrkAnnoyTTLose    (LongSafe_Cal_DF_V.k_AEB_LowBrkAnnoyTTLose_str)
#define k_AEB_RangeDecelTrhd    (LongSafe_Cal_DF_V.k_AEB_RangeDecelTrhd_str)
#define k_AEB_LeadDecelTrhd    (LongSafe_Cal_DF_V.k_AEB_LeadDecelTrhd_str)
#define k_AEB_DBSMinSpdChkEnbl    (LongSafe_Cal_DF_V.k_AEB_DBSMinSpdChkEnbl_str)
#define k_AEB_DBSUseDefaultDecel    (LongSafe_Cal_DF_V.k_AEB_DBSUseDefaultDecel_str)
#define k_AEB_IgnoreObjClassChk    (LongSafe_Cal_DF_V.k_AEB_IgnoreObjClassChk_str)
#define k_AEB_MinEgoSpdRadarOnly    (LongSafe_Cal_DF_V.k_AEB_MinEgoSpdRadarOnly_str)
#define k_AEB_MinMatchConfMovLowSpd    (LongSafe_Cal_DF_V.k_AEB_MinMatchConfMovLowSpd_str)
#define k_AEB_HardTurnInhibitSpdPoints    (LongSafe_Cal_DF_V.k_AEB_HardTurnInhibitSpdPoints_str)
#define k_AEB_HardTurnStrAngleTrhd    (LongSafe_Cal_DF_V.k_AEB_HardTurnStrAngleTrhd_str)
#define k_AEB_StrAngInhibitEnblTm    (LongSafe_Cal_DF_V.k_AEB_StrAngInhibitEnblTm_str)
#define k_AEB_BrkEngagePresEnblTm    (LongSafe_Cal_DF_V.k_AEB_BrkEngagePresEnblTm_str)
#define k_AEB_BrkEngageHdTm    (LongSafe_Cal_DF_V.k_AEB_BrkEngageHdTm_str)
#define k_AEB_IgrLowBrkDrvEng    (LongSafe_Cal_DF_V.k_AEB_IgrLowBrkDrvEng_str)
#define k_AEB_DBSMinVehicleSpd    (LongSafe_Cal_DF_V.k_AEB_DBSMinVehicleSpd_str)
#define k_AEB_BcyMaxRangeRate    (LongSafe_Cal_DF_V.k_AEB_BcyMaxRangeRate_str)
#define k_AEB_IgrHiBrkDrvEng    (LongSafe_Cal_DF_V.k_AEB_IgrHiBrkDrvEng_str)
#define k_AEB_DrvEngInhibitSpd    (LongSafe_Cal_DF_V.k_AEB_DrvEngInhibitSpd_str)
#define k_AEB_VRUHBMinConf    (LongSafe_Cal_DF_V.k_AEB_VRUHBMinConf_str)
#define k_AEB_HBHdTmLowAge    (LongSafe_Cal_DF_V.k_AEB_HBHdTmLowAge_str)
#define k_AEB_OtherTrgtMinDeltaYpos    (LongSafe_Cal_DF_V.k_AEB_OtherTrgtMinDeltaYpos_str)
#define k_AEB_VRULatDeSelTrhd    (LongSafe_Cal_DF_V.k_AEB_VRULatDeSelTrhd_str)
#define k_AEB_GasInhibitLowSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_GasInhibitLowSpdTrhd_str)
#define k_AEB_GasInhibitHiSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_GasInhibitHiSpdTrhd_str)
#define k_AEB_VehHBDrvEngTypeSltd    (LongSafe_Cal_DF_V.k_AEB_VehHBDrvEngTypeSltd_str)
#define k_AEB_VehLBDrvEngTypeSltd    (LongSafe_Cal_DF_V.k_AEB_VehLBDrvEngTypeSltd_str)
#define k_AEB_VehPFDrvEngTypeSltd    (LongSafe_Cal_DF_V.k_AEB_VehPFDrvEngTypeSltd_str)
#define k_AEB_IgrPrefillDrvEng    (LongSafe_Cal_DF_V.k_AEB_IgrPrefillDrvEng_str)
#define k_AEB_VRUHBDrvEngTypeSltd    (LongSafe_Cal_DF_V.k_AEB_VRUHBDrvEngTypeSltd_str)
#define k_AEB_VRULBDrvEngTypeSltd    (LongSafe_Cal_DF_V.k_AEB_VRULBDrvEngTypeSltd_str)
#define k_AEB_IgrVRUPFDrvEng    (LongSafe_Cal_DF_V.k_AEB_IgrVRUPFDrvEng_str)
#define k_AEB_VRUPFDrvEngTypeSltd    (LongSafe_Cal_DF_V.k_AEB_VRUPFDrvEngTypeSltd_str)
#define k_AEB_HiBrkDropWaitTime    (LongSafe_Cal_DF_V.k_AEB_HiBrkDropWaitTime_str)
#define k_AEB_VRUHBHoldMaxRngAllow    (LongSafe_Cal_DF_V.k_AEB_VRUHBHoldMaxRngAllow_str)
#define k_AEB_HBHoldMaxRngAllow    (LongSafe_Cal_DF_V.k_AEB_HBHoldMaxRngAllow_str)
#define k_AEB_DRTClassHoldEnbl    (LongSafe_Cal_DF_V.k_AEB_DRTClassHoldEnbl_str)
#define k_AEB_GateMinRangeMov    (LongSafe_Cal_DF_V.k_AEB_GateMinRangeMov_str)
#define k_AEB_GateMinRangeStat    (LongSafe_Cal_DF_V.k_AEB_GateMinRangeStat_str)
#define k_AEB_ClsFstDectIPAOffset    (LongSafe_Cal_DF_V.k_AEB_ClsFstDectIPAOffset_str)
#define k_AEB_OvtkStrAngleTrhd    (LongSafe_Cal_DF_V.k_AEB_OvtkStrAngleTrhd_str)
#define k_AEB_OvtkGasPedalTrhd    (LongSafe_Cal_DF_V.k_AEB_OvtkGasPedalTrhd_str)
#define k_AEB_LongBikePFLdTm_mps    (LongSafe_Cal_DF_V.k_AEB_LongBikePFLdTm_mps_str)
#define k_AEB_LongBikePFLdTm_sec    (LongSafe_Cal_DF_V.k_AEB_LongBikePFLdTm_sec_str)
#define k_AEB_LongBikeLBLdTm_mps    (LongSafe_Cal_DF_V.k_AEB_LongBikeLBLdTm_mps_str)
#define k_AEB_LongBikeLBLdTm_sec    (LongSafe_Cal_DF_V.k_AEB_LongBikeLBLdTm_sec_str)
#define k_AEB_LongBikeHBLdTm_sec    (LongSafe_Cal_DF_V.k_AEB_LongBikeHBLdTm_sec_str)
#define k_AEB_LongBikeFLBALdTm_sec    (LongSafe_Cal_DF_V.k_AEB_LongBikeFLBALdTm_sec_str)
#define k_AEB_LongBikeMSLdTm_sec    (LongSafe_Cal_DF_V.k_AEB_LongBikeMSLdTm_sec_str)
#define k_AEB_LongBikeDBSLdTm_sec    (LongSafe_Cal_DF_V.k_AEB_LongBikeDBSLdTm_sec_str)
#define k_AEB_HiConfBikeStaPFTTC_mps    (LongSafe_Cal_DF_V.k_AEB_HiConfBikeStaPFTTC_mps_str)
#define k_AEB_HiConfBikeStaPFTTC_sec    (LongSafe_Cal_DF_V.k_AEB_HiConfBikeStaPFTTC_sec_str)
#define k_AEB_BikeStaLBTTC_sec    (LongSafe_Cal_DF_V.k_AEB_BikeStaLBTTC_sec_str)
#define k_AEB_HiConfBikeStaHBTTC_sec    (LongSafe_Cal_DF_V.k_AEB_HiConfBikeStaHBTTC_sec_str)
#define k_AEB_HiConfBikeStaFLBATTC_sec    (LongSafe_Cal_DF_V.k_AEB_HiConfBikeStaFLBATTC_sec_str)
#define k_AEB_HiConfBikeStaMSTTC_sec    (LongSafe_Cal_DF_V.k_AEB_HiConfBikeStaMSTTC_sec_str)
#define k_AEB_HiConfBikeStaDBSTTC_sec    (LongSafe_Cal_DF_V.k_AEB_HiConfBikeStaDBSTTC_sec_str)
#define k_AEB_FullBrakeHiBrkCnt    (LongSafe_Cal_DF_V.k_AEB_FullBrakeHiBrkCnt_str)
#define k_AEB_JAFullBrakeHiBrkCnt    (LongSafe_Cal_DF_V.k_AEB_JAFullBrakeHiBrkCnt_str)
#define k_AEB_FullBrkDuringTimer_mps    (LongSafe_Cal_DF_V.k_AEB_FullBrkDuringTimer_mps_str)
#define k_AEB_IgnLowBrkFBTimerReset    (LongSafe_Cal_DF_V.k_AEB_IgnLowBrkFBTimerReset_str)
#define k_AEB_IgnHiBrkFBTimerReset    (LongSafe_Cal_DF_V.k_AEB_IgnHiBrkFBTimerReset_str)
#define k_AEB_VRUAEBXolcTrhd    (LongSafe_Cal_DF_V.k_AEB_VRUAEBXolcTrhd_str)
#define k_AEB_HiBrkLowPerstCntJA    (LongSafe_Cal_DF_V.k_AEB_HiBrkLowPerstCntJA_str)
#define k_AEB_DBSHostAccelTrhd    (LongSafe_Cal_DF_V.k_AEB_DBSHostAccelTrhd_str)
#define k_AEB_SuppressTime    (LongSafe_Cal_DF_V.k_AEB_SuppressTime_str)
#define k_AEB_CLHiBrkNeedDecelLimt    (LongSafe_Cal_DF_V.k_AEB_CLHiBrkNeedDecelLimt_str)
#define k_AEB_NoAEBSuppressEnbl    (LongSafe_Cal_DF_V.k_AEB_NoAEBSuppressEnbl_str)
#define k_AEB_HeadingAngOCTAPTrhd    (LongSafe_Cal_DF_V.k_AEB_HeadingAngOCTAPTrhd_str)
#define k_AEB_HeadingAngCPTATrhd    (LongSafe_Cal_DF_V.k_AEB_HeadingAngCPTATrhd_str)
#define k_AEB_SensorInputLpTm    (LongSafe_Cal_DF_V.k_AEB_SensorInputLpTm_str)
#define k_AEB_VcanInputLpTm    (LongSafe_Cal_DF_V.k_AEB_VcanInputLpTm_str)
#define k_AEB_StationaryVehFullChkEnbl    (LongSafe_Cal_DF_V.k_AEB_StationaryVehFullChkEnbl_str)
#define k_AEB_LongMovBikeFullChkEnbl    (LongSafe_Cal_DF_V.k_AEB_LongMovBikeFullChkEnbl_str)
#define k_AEB_leadAccelEnFullBrk    (LongSafe_Cal_DF_V.k_AEB_leadAccelEnFullBrk_str)
#define k_AEB_FullBrkRangePoints    (LongSafe_Cal_DF_V.k_AEB_FullBrkRangePoints_str)
#define k_AEB_FullBrkRngRtPoints    (LongSafe_Cal_DF_V.k_AEB_FullBrkRngRtPoints_str)
#define k_AEB_FullBrakeChkEnbl    (LongSafe_Cal_DF_V.k_AEB_FullBrakeChkEnbl_str[0])
#define k_AEB_AxleTorqueFiltTime_ms    (LongSafe_Cal_DF_V.k_AEB_AxleTorqueFiltTime_ms_str)
#define k_AEB_AxleTorqueRateMax    (LongSafe_Cal_DF_V.k_AEB_AxleTorqueRateMax_str)
#define k_AEB_AxleTorqueRateMin    (LongSafe_Cal_DF_V.k_AEB_AxleTorqueRateMin_str)
#define k_AEB_BrakeAccelFiltTime_ms    (LongSafe_Cal_DF_V.k_AEB_BrakeAccelFiltTime_ms_str)
#define k_AEB_BrakeAccelRateMax    (LongSafe_Cal_DF_V.k_AEB_BrakeAccelRateMax_str)
#define k_AEB_BrakeAccelRateMin    (LongSafe_Cal_DF_V.k_AEB_BrakeAccelRateMin_str)
#define k_AEB_DrvIntndAxlTrqMinNegOffst    (LongSafe_Cal_DF_V.k_AEB_DrvIntndAxlTrqMinNegOffst_str)
#define k_AEB_BrakeAccelFinalLimit    (LongSafe_Cal_DF_V.k_AEB_BrakeAccelFinalLimit_str)
#define k_AEB_HoldDecelEnbl    (LongSafe_Cal_DF_V.k_AEB_HoldDecelEnbl_str)
#define k_AEB_HoldBrkReqEnbl    (LongSafe_Cal_DF_V.k_AEB_HoldBrkReqEnbl_str)
#define k_AEB_UseAxleTrqtoBrk    (LongSafe_Cal_DF_V.k_AEB_UseAxleTrqtoBrk_str)
#define k_AEB_IgnorePedTTCChk    (LongSafe_Cal_DF_V.k_AEB_IgnorePedTTCChk_str)
#define k_AEB_IgnorePedRngChk    (LongSafe_Cal_DF_V.k_AEB_IgnorePedRngChk_str)
#define k_AEB_VRUMaxTTCAllowed    (LongSafe_Cal_DF_V.k_AEB_VRUMaxTTCAllowed_str)
#define k_AEB_VRUMinTTCAllowed    (LongSafe_Cal_DF_V.k_AEB_VRUMinTTCAllowed_str)
#define k_AEB_VRUMaxRngAllowed    (LongSafe_Cal_DF_V.k_AEB_VRUMaxRngAllowed_str)
#define k_AEB_VRUMinRngAllowed    (LongSafe_Cal_DF_V.k_AEB_VRUMinRngAllowed_str)
#define k_AEB_EPBStateAffectHold    (LongSafe_Cal_DF_V.k_AEB_EPBStateAffectHold_str)
#define k_AEB_MinConfSRRDegrade    (LongSafe_Cal_DF_V.k_AEB_MinConfSRRDegrade_str)
#define k_AEB_MovSRRMisAlignChkEnbl    (LongSafe_Cal_DF_V.k_AEB_MovSRRMisAlignChkEnbl_str)
#define k_AEB_DBSReleaseAEBDisbl    (LongSafe_Cal_DF_V.k_AEB_DBSReleaseAEBDisbl_str)
#define k_AEB_LowConfInPathAgeTrhd    (LongSafe_Cal_DF_V.k_AEB_LowConfInPathAgeTrhd_str)
#define k_AEB_MedConfInPathAgeTrhd    (LongSafe_Cal_DF_V.k_AEB_MedConfInPathAgeTrhd_str)
#define k_AEB_HiConfInPathAgeTrhd    (LongSafe_Cal_DF_V.k_AEB_HiConfInPathAgeTrhd_str)
#define k_AEB_HiBrkMinReleaseDist    (LongSafe_Cal_DF_V.k_AEB_HiBrkMinReleaseDist_str)
#define k_AEB_EnVRUClutterShutDown    (LongSafe_Cal_DF_V.k_AEB_EnVRUClutterShutDown_str)
#define k_AEB_HiBrkVisConfirmDisable    (LongSafe_Cal_DF_V.k_AEB_HiBrkVisConfirmDisable_str)
#define k_AEB_LowBrkVisConfirmDisable    (LongSafe_Cal_DF_V.k_AEB_LowBrkVisConfirmDisable_str)
#define k_AEB_GasEngagePosEnTime    (LongSafe_Cal_DF_V.k_AEB_GasEngagePosEnTime_str)
#define k_AEB_GasEngagePosEntryTrhd    (LongSafe_Cal_DF_V.k_AEB_GasEngagePosEntryTrhd_str)
#define k_AEB_GasEngagePosExitTrhd    (LongSafe_Cal_DF_V.k_AEB_GasEngagePosExitTrhd_str)
#define k_AEB_GasPosRateEntryTrhd    (LongSafe_Cal_DF_V.k_AEB_GasPosRateEntryTrhd_str)
#define k_AEB_GasPosRateExitTrhd    (LongSafe_Cal_DF_V.k_AEB_GasPosRateExitTrhd_str)
#define k_AEB_GasPosRateEnTime    (LongSafe_Cal_DF_V.k_AEB_GasPosRateEnTime_str)
#define k_AEB_GasEngageHdTm    (LongSafe_Cal_DF_V.k_AEB_GasEngageHdTm_str)
#define k_AEB_BrkEngagePosEntryTrhd    (LongSafe_Cal_DF_V.k_AEB_BrkEngagePosEntryTrhd_str)
#define k_AEB_BrkEngagePosExitTrhd    (LongSafe_Cal_DF_V.k_AEB_BrkEngagePosExitTrhd_str)
#define k_AEB_BrkEngagePosEnTime    (LongSafe_Cal_DF_V.k_AEB_BrkEngagePosEnTime_str)
#define k_AEB_HBNoVisFlagMinConf    (LongSafe_Cal_DF_V.k_AEB_HBNoVisFlagMinConf_str)
#define k_AEB_LBNoVisFlagMinConf    (LongSafe_Cal_DF_V.k_AEB_LBNoVisFlagMinConf_str)
#define k_AEB_UseNewPrefillCounter    (LongSafe_Cal_DF_V.k_AEB_UseNewPrefillCounter_str)
#define k_AEB_AllowOutFunAEBPRelease    (LongSafe_Cal_DF_V.k_AEB_AllowOutFunAEBPRelease_str)
#define k_AEB_VRUHBMinConfEnblTime    (LongSafe_Cal_DF_V.k_AEB_VRUHBMinConfEnblTime_str)
#define k_AEB_HBHdTmAgeTrhd    (LongSafe_Cal_DF_V.k_AEB_HBHdTmAgeTrhd_str)
#define k_AEB_VRUHBHdTmAgeTrhd    (LongSafe_Cal_DF_V.k_AEB_VRUHBHdTmAgeTrhd_str)
#define k_AEB_ExtendUsePedHdTm    (LongSafe_Cal_DF_V.k_AEB_ExtendUsePedHdTm_str)
#define k_AEB_LastValHaloTime    (LongSafe_Cal_DF_V.k_AEB_LastValHaloTime_str)
#define k_AEB_VRULBMinConf    (LongSafe_Cal_DF_V.k_AEB_VRULBMinConf_str)
#define k_AEB_VRULBMinConfEnblTm    (LongSafe_Cal_DF_V.k_AEB_VRULBMinConfEnblTm_str)
#define k_AEB_IDChangeHaloTime    (LongSafe_Cal_DF_V.k_AEB_IDChangeHaloTime_str)
#define k_AEB_HiSpdGasRateEntryTrhd    (LongSafe_Cal_DF_V.k_AEB_HiSpdGasRateEntryTrhd_str)
#define k_AEB_HiSpdGasRateExitTrhd    (LongSafe_Cal_DF_V.k_AEB_HiSpdGasRateExitTrhd_str)
#define k_AEB_HiSpdGasRateEnTime    (LongSafe_Cal_DF_V.k_AEB_HiSpdGasRateEnTime_str)
#define k_AEB_HiSpdGasInhibtHdTm    (LongSafe_Cal_DF_V.k_AEB_HiSpdGasInhibtHdTm_str)
#define k_AEB_UnIdeLowestConfInPathTrhd    (LongSafe_Cal_DF_V.k_AEB_UnIdeLowestConfInPathTrhd_str)
#define k_AEB_UnIdeLowConfInPathTrhd    (LongSafe_Cal_DF_V.k_AEB_UnIdeLowConfInPathTrhd_str)
#define k_AEB_UnIdeMedConfInPathTrhd    (LongSafe_Cal_DF_V.k_AEB_UnIdeMedConfInPathTrhd_str)
#define k_AEB_UnIdeHiConfInPathTrhd    (LongSafe_Cal_DF_V.k_AEB_UnIdeHiConfInPathTrhd_str)
#define k_AEB_LowestConfInPathAgeTrhd    (LongSafe_Cal_DF_V.k_AEB_LowestConfInPathAgeTrhd_str)
#define k_AEB_TTCReduceLatOfstBrkPoint    (LongSafe_Cal_DF_V.k_AEB_TTCReduceLatOfstBrkPoint_str)
#define k_AEB_HiConfLBTTCReduceFactor    (LongSafe_Cal_DF_V.k_AEB_HiConfLBTTCReduceFactor_str)
#define k_AEB_HiConfHBTTCReduceFactor    (LongSafe_Cal_DF_V.k_AEB_HiConfHBTTCReduceFactor_str)
#define k_AEB_HiConfDBSTTCReduceFactor    (LongSafe_Cal_DF_V.k_AEB_HiConfDBSTTCReduceFactor_str)
#define k_AEB_NoTTCReduceLatEstTrhd    (LongSafe_Cal_DF_V.k_AEB_NoTTCReduceLatEstTrhd_str)
#define k_AEB_LastBrkYposHaloTime    (LongSafe_Cal_DF_V.k_AEB_LastBrkYposHaloTime_str)
#define k_AEB_VRUFusHiConfLvl    (LongSafe_Cal_DF_V.k_AEB_VRUFusHiConfLvl_str)
#define k_AEB_VRUFusMedConfLvl    (LongSafe_Cal_DF_V.k_AEB_VRUFusMedConfLvl_str)
#define k_AEB_VRUVisMedConfLvl    (LongSafe_Cal_DF_V.k_AEB_VRUVisMedConfLvl_str)
#define k_AEB_FusHiMinInPAgeTrhd    (LongSafe_Cal_DF_V.k_AEB_FusHiMinInPAgeTrhd_str)
#define k_AEB_FusHiMinInPAgeTrhdLong    (LongSafe_Cal_DF_V.k_AEB_FusHiMinInPAgeTrhdLong_str)
#define k_AEB_FusMedMinInPAgeTrhd    (LongSafe_Cal_DF_V.k_AEB_FusMedMinInPAgeTrhd_str)
#define k_AEB_VisMedMinInPAgeTrhd    (LongSafe_Cal_DF_V.k_AEB_VisMedMinInPAgeTrhd_str)
#define k_AEB_VisMedMinInPAgeTrhdLong    (LongSafe_Cal_DF_V.k_AEB_VisMedMinInPAgeTrhdLong_str)
#define k_AEB_FusMedMinInPAgeTrhdLong    (LongSafe_Cal_DF_V.k_AEB_FusMedMinInPAgeTrhdLong_str)
#define k_AEB_MinInPAgeTrhd    (LongSafe_Cal_DF_V.k_AEB_MinInPAgeTrhd_str)
#define k_AEB_MinInPAgeTrhdLong    (LongSafe_Cal_DF_V.k_AEB_MinInPAgeTrhdLong_str)
#define k_AEB_DrvBrkVRURlsEnTime    (LongSafe_Cal_DF_V.k_AEB_DrvBrkVRURlsEnTime_str)
#define k_AEB_GeneralSpdPoints    (LongSafe_Cal_DF_V.k_AEB_GeneralSpdPoints_str)
#define k_AEB_OvtkMaxTTCTrhd    (LongSafe_Cal_DF_V.k_AEB_OvtkMaxTTCTrhd_str)
#define k_AEB_OTMinXolcPercent    (LongSafe_Cal_DF_V.k_AEB_OTMinXolcPercent_str)
#define k_AEB_OneWayXolcChgCountTrhd    (LongSafe_Cal_DF_V.k_AEB_OneWayXolcChgCountTrhd_str)
#define k_AEB_OvtkGasPdlHaloTime    (LongSafe_Cal_DF_V.k_AEB_OvtkGasPdlHaloTime_str)
#define k_AEB_OvtkReducHaloTime    (LongSafe_Cal_DF_V.k_AEB_OvtkReducHaloTime_str)
#define k_AEB_TTCReduceXolcBrkPoint    (LongSafe_Cal_DF_V.k_AEB_TTCReduceXolcBrkPoint_str)
#define k_AEB_PrefillTTCReduceFactor    (LongSafe_Cal_DF_V.k_AEB_PrefillTTCReduceFactor_str)
#define k_AEB_LowTTCReduceFactor    (LongSafe_Cal_DF_V.k_AEB_LowTTCReduceFactor_str)
#define k_AEB_HBTTCReduceFactor    (LongSafe_Cal_DF_V.k_AEB_HBTTCReduceFactor_str)
#define k_AEB_DBSTTCReduceFactor    (LongSafe_Cal_DF_V.k_AEB_DBSTTCReduceFactor_str)
#define k_AEB_NeedDecelFilterGain    (LongSafe_Cal_DF_V.k_AEB_NeedDecelFilterGain_str)
#define k_AEB_UseTrackerLeadAeecl    (LongSafe_Cal_DF_V.k_AEB_UseTrackerLeadAeecl_str)
#define k_AEB_LeadVehDecelTrhd    (LongSafe_Cal_DF_V.k_AEB_LeadVehDecelTrhd_str)
#define k_AEB_DecelDiffBrkPoints    (LongSafe_Cal_DF_V.k_AEB_DecelDiffBrkPoints_str)
#define k_AEB_ESPSettlingTime    (LongSafe_Cal_DF_V.k_AEB_ESPSettlingTime_str)
#define k_AEB_DesireStopDistance    (LongSafe_Cal_DF_V.k_AEB_DesireStopDistance_str)
#define k_AEB_UseCloseLoopDecel    (LongSafe_Cal_DF_V.k_AEB_UseCloseLoopDecel_str)
#define k_AEB_CLRampDownFactor    (LongSafe_Cal_DF_V.k_AEB_CLRampDownFactor_str)
#define k_AEB_CLDecelBrkRelseTrhd    (LongSafe_Cal_DF_V.k_AEB_CLDecelBrkRelseTrhd_str)
#define k_AEB_CLDecelBrkRelseEnTime    (LongSafe_Cal_DF_V.k_AEB_CLDecelBrkRelseEnTime_str)
#define k_AEB_EgoTartAccelBrkPoints    (LongSafe_Cal_DF_V.k_AEB_EgoTartAccelBrkPoints_str)
#define k_AEB_TartInforFilterGain    (LongSafe_Cal_DF_V.k_AEB_TartInforFilterGain_str)
#define k_AEB_TartLeadSpdOffset    (LongSafe_Cal_DF_V.k_AEB_TartLeadSpdOffset_str)
#define k_AEB_LBDrvEngReducFactor    (LongSafe_Cal_DF_V.k_AEB_LBDrvEngReducFactor_str)
#define k_AEB_HBDrvEngReducFactor    (LongSafe_Cal_DF_V.k_AEB_HBDrvEngReducFactor_str)
#define k_AEB_DBSDrvEngReducFactor    (LongSafe_Cal_DF_V.k_AEB_DBSDrvEngReducFactor_str)
#define k_AEB_PFDrvEngReducFactor    (LongSafe_Cal_DF_V.k_AEB_PFDrvEngReducFactor_str)
#define k_AEB_VehDBSDrvEngTypeSltd    (LongSafe_Cal_DF_V.k_AEB_VehDBSDrvEngTypeSltd_str)
#define k_AEB_IgrDBSDrvEng    (LongSafe_Cal_DF_V.k_AEB_IgrDBSDrvEng_str)
#define k_AEB_PredTimeRRBrkPoint    (LongSafe_Cal_DF_V.k_AEB_PredTimeRRBrkPoint_str)
#define k_AEB_PredTimeRAccelBrkPoint    (LongSafe_Cal_DF_V.k_AEB_PredTimeRAccelBrkPoint_str)
#define k_AEB_MaxPredictTime    (LongSafe_Cal_DF_V.k_AEB_MaxPredictTime_str[0])
#define k_AEB_DrvEngUseTTCReduc    (LongSafe_Cal_DF_V.k_AEB_DrvEngUseTTCReduc_str)
#define k_AEB_NoESPDisDecelTrhd    (LongSafe_Cal_DF_V.k_AEB_NoESPDisDecelTrhd_str)
#define k_AEB_NoESPDisRangeTrhd    (LongSafe_Cal_DF_V.k_AEB_NoESPDisRangeTrhd_str)
#define k_AEB_EgoAllowDisScalFactor    (LongSafe_Cal_DF_V.k_AEB_EgoAllowDisScalFactor_str)
#define k_AEB_EgoHiDynamicAccelTrhd    (LongSafe_Cal_DF_V.k_AEB_EgoHiDynamicAccelTrhd_str)
#define k_AEB_LongVelFullHiDymic    (LongSafe_Cal_DF_V.k_AEB_LongVelFullHiDymic_str)
#define k_AEB_LongVelFull    (LongSafe_Cal_DF_V.k_AEB_LongVelFull_str)
#define k_AEB_LongVelNegliHiDymic    (LongSafe_Cal_DF_V.k_AEB_LongVelNegliHiDymic_str)
#define k_AEB_LongVelNegli    (LongSafe_Cal_DF_V.k_AEB_LongVelNegli_str)
#define k_AEB_MovLeadVelNegliEnTime    (LongSafe_Cal_DF_V.k_AEB_MovLeadVelNegliEnTime_str)
#define k_AEB_MovLeadVelNegliHaloTime    (LongSafe_Cal_DF_V.k_AEB_MovLeadVelNegliHaloTime_str)
#define k_AEB_NonProceedVRUFullChkEnbl    (LongSafe_Cal_DF_V.k_AEB_NonProceedVRUFullChkEnbl_str)
#define k_AEB_ESPDelayDisFadingTime    (LongSafe_Cal_DF_V.k_AEB_ESPDelayDisFadingTime_str)
#define k_AEB_AccuAngEgoStopHaloTime    (LongSafe_Cal_DF_V.k_AEB_AccuAngEgoStopHaloTime_str)
#define k_AEB_MaxAllowVehHeadAngTime    (LongSafe_Cal_DF_V.k_AEB_MaxAllowVehHeadAngTime_str)
#define k_AEB_TTTUseTrtWidth    (LongSafe_Cal_DF_V.k_AEB_TTTUseTrtWidth_str)
#define k_AEB_TTTPersistXolcTrhd    (LongSafe_Cal_DF_V.k_AEB_TTTPersistXolcTrhd_str)
#define k_AEB_BrkPressurePositionSel    (LongSafe_Cal_DF_V.k_AEB_BrkPressurePositionSel_str)
#define k_AEB_HiBrkUseRangeTrigger    (LongSafe_Cal_DF_V.k_AEB_HiBrkUseRangeTrigger_str)
#define k_AEB_HiBrkTrigMovRangeOffset    (LongSafe_Cal_DF_V.k_AEB_HiBrkTrigMovRangeOffset_str)
#define k_AEB_HiBrkTrigStatRangeOffset    (LongSafe_Cal_DF_V.k_AEB_HiBrkTrigStatRangeOffset_str)
#define k_AEB_LoBrkTrigMovDuration    (LongSafe_Cal_DF_V.k_AEB_LoBrkTrigMovDuration_str)
#define k_AEB_LoBrkTrigStatDuration    (LongSafe_Cal_DF_V.k_AEB_LoBrkTrigStatDuration_str)
#define k_AEB_PrefillTrigMovDuration    (LongSafe_Cal_DF_V.k_AEB_PrefillTrigMovDuration_str)
#define k_AEB_PrefillTrigStatDuration    (LongSafe_Cal_DF_V.k_AEB_PrefillTrigStatDuration_str)
#define k_AEB_FLBATrigMovDuration    (LongSafe_Cal_DF_V.k_AEB_FLBATrigMovDuration_str)
#define k_AEB_FLBATrigStatDuration    (LongSafe_Cal_DF_V.k_AEB_FLBATrigStatDuration_str)
#define k_AEB_MinStopTrigMovDuration    (LongSafe_Cal_DF_V.k_AEB_MinStopTrigMovDuration_str)
#define k_AEB_MinStopTrigStatDuration    (LongSafe_Cal_DF_V.k_AEB_MinStopTrigStatDuration_str)
#define k_AEB_FusionFLBAMaskWrd    (LongSafe_Cal_DF_V.k_AEB_FusionFLBAMaskWrd_str)
#define k_AEB_FusionPFMaskWrd    (LongSafe_Cal_DF_V.k_AEB_FusionPFMaskWrd_str)
#define k_AEB_FusionLBMaskWrd    (LongSafe_Cal_DF_V.k_AEB_FusionLBMaskWrd_str)
#define k_AEB_FusionHBMaskWrd    (LongSafe_Cal_DF_V.k_AEB_FusionHBMaskWrd_str)
#define k_AEB_FusionFBMaskWrd    (LongSafe_Cal_DF_V.k_AEB_FusionFBMaskWrd_str)
#define k_AEB_FusionVRUFLBAMaskWrd    (LongSafe_Cal_DF_V.k_AEB_FusionVRUFLBAMaskWrd_str)
#define k_AEB_FusionVRUPFMaskWrd    (LongSafe_Cal_DF_V.k_AEB_FusionVRUPFMaskWrd_str)
#define k_AEB_FusionVRULBMaskWrd    (LongSafe_Cal_DF_V.k_AEB_FusionVRULBMaskWrd_str)
#define k_AEB_FusionVRUHBMaskWrd    (LongSafe_Cal_DF_V.k_AEB_FusionVRUHBMaskWrd_str)
#define k_AEB_FusionVRUFBMaskWrd    (LongSafe_Cal_DF_V.k_AEB_FusionVRUFBMaskWrd_str)
#define k_AEB_FusionVRUTOIMaskWrd    (LongSafe_Cal_DF_V.k_AEB_FusionVRUTOIMaskWrd_str)
#define k_AEB_VehWithIboostNoESP    (LongSafe_Cal_DF_V.k_AEB_VehWithIboostNoESP_str)
#define k_AEB_PedEnable    (LongSafe_Cal_DF_V.k_AEB_PedEnable_str)
#define k_AEB_IgnoreDecelCheckInPCS    (LongSafe_Cal_DF_V.k_AEB_IgnoreDecelCheckInPCS_str)
#define k_AEB_DesiredVehHitSpd    (LongSafe_Cal_DF_V.k_AEB_DesiredVehHitSpd_str)
#define k_AEB_FullBrkLvl_mps_offset    (LongSafe_Cal_DF_V.k_AEB_FullBrkLvl_mps_offset_str)
#define k_AEB_HiBrkLvl_mps_offset    (LongSafe_Cal_DF_V.k_AEB_HiBrkLvl_mps_offset_str)
#define k_AEB_Adjust_XOLC_MovementLimit    (LongSafe_Cal_DF_V.k_AEB_Adjust_XOLC_MovementLimit_str)
#define k_AEB_LongBikePFDuration    (LongSafe_Cal_DF_V.k_AEB_LongBikePFDuration_str)
#define k_AEB_DBSMaxDecel_mps    (LongSafe_Cal_DF_V.k_AEB_DBSMaxDecel_mps_str)
#define k_AEB_VRUMinTTC_sec    (LongSafe_Cal_DF_V.k_AEB_VRUMinTTC_sec_str)
#define k_AEB_PFNearTrgt_RedFac    (LongSafe_Cal_DF_V.k_AEB_PFNearTrgt_RedFac_str)
#define k_AEB_LBNearTrgt_RedFac    (LongSafe_Cal_DF_V.k_AEB_LBNearTrgt_RedFac_str)
#define k_AEB_HBNearTrgt_RedFac    (LongSafe_Cal_DF_V.k_AEB_HBNearTrgt_RedFac_str)
#define k_AEB_NearTrgt_KneePoints    (LongSafe_Cal_DF_V.k_AEB_NearTrgt_KneePoints_str)
#define k_AEB_enb_veh_sta_check    (LongSafe_Cal_DF_V.k_AEB_enb_veh_sta_check_str)
#define k_AEB_veh_coasted_enb_cont    (LongSafe_Cal_DF_V.k_AEB_veh_coasted_enb_cont_str)
#define k_AEB_InpathNowReduceFactor    (LongSafe_Cal_DF_V.k_AEB_InpathNowReduceFactor_str)
#define k_AEB_InpathLaterReduceFactor    (LongSafe_Cal_DF_V.k_AEB_InpathLaterReduceFactor_str)
#define k_AEB_StrAngRtLatEstReduceFac    (LongSafe_Cal_DF_V.k_AEB_StrAngRtLatEstReduceFac_str)
#define k_AEB_StrAngRatePoints    (LongSafe_Cal_DF_V.k_AEB_StrAngRatePoints_str)
#define k_AEB_BrkInhibitLowSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_BrkInhibitLowSpdTrhd_str)
#define k_AEB_BrkInhibitHiSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_BrkInhibitHiSpdTrhd_str)
#define k_AEB_HiSpdBrkEngageHdTm    (LongSafe_Cal_DF_V.k_AEB_HiSpdBrkEngageHdTm_str)
#define k_AEB_BrkEngagePresFactor    (LongSafe_Cal_DF_V.k_AEB_BrkEngagePresFactor_str)
#define k_AEB_HiSpdBrkEngagePresFactor    (LongSafe_Cal_DF_V.k_AEB_HiSpdBrkEngagePresFactor_str)
#define k_AEB_HiSpdBrkEngPosEntryTrhd    (LongSafe_Cal_DF_V.k_AEB_HiSpdBrkEngPosEntryTrhd_str)
#define k_AEB_VRULatEstFunnelExitFac    (LongSafe_Cal_DF_V.k_AEB_VRULatEstFunnelExitFac_str)
#define k_AEB_HiSpdBrkEngPosExitTrhd    (LongSafe_Cal_DF_V.k_AEB_HiSpdBrkEngPosExitTrhd_str)
#define k_AEB_VRUPFVehBehType    (LongSafe_Cal_DF_V.k_AEB_VRUPFVehBehType_str)
#define k_AEB_VRULBVehBehType    (LongSafe_Cal_DF_V.k_AEB_VRULBVehBehType_str)
#define k_AEB_VRUHBVehBehType    (LongSafe_Cal_DF_V.k_AEB_VRUHBVehBehType_str)
#define k_AEB_VRUPFVBCTTCRedFac    (LongSafe_Cal_DF_V.k_AEB_VRUPFVBCTTCRedFac_str)
#define k_AEB_VRULBVBCTTCRedFac    (LongSafe_Cal_DF_V.k_AEB_VRULBVBCTTCRedFac_str)
#define k_AEB_VRUHBVBCTTCRedFac    (LongSafe_Cal_DF_V.k_AEB_VRUHBVBCTTCRedFac_str)
#define k_AEB_IgrHiBrkVehBeh    (LongSafe_Cal_DF_V.k_AEB_IgrHiBrkVehBeh_str)
#define k_AEB_VRUHBInhVehBehType    (LongSafe_Cal_DF_V.k_AEB_VRUHBInhVehBehType_str)
#define k_AEB_VehBehChkLowSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_VehBehChkLowSpdTrhd_str)
#define k_AEB_VehBehChkHiSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_VehBehChkHiSpdTrhd_str)
#define k_AEB_StrRateReductionHdTm    (LongSafe_Cal_DF_V.k_AEB_StrRateReductionHdTm_str)
#define k_AEB_StrReductionHdTm    (LongSafe_Cal_DF_V.k_AEB_StrReductionHdTm_str)
#define k_AEB_BrkReductionHdTm    (LongSafe_Cal_DF_V.k_AEB_BrkReductionHdTm_str)
#define k_AEB_GasPdlReductionHdTm    (LongSafe_Cal_DF_V.k_AEB_GasPdlReductionHdTm_str)
#define k_AEB_GasPdlReductionEntryTrhd    (LongSafe_Cal_DF_V.k_AEB_GasPdlReductionEntryTrhd_str)
#define k_AEB_GasPdlReductionExitTrhd    (LongSafe_Cal_DF_V.k_AEB_GasPdlReductionExitTrhd_str)
#define k_AEB_StrRateReductionEntryTrhd    (LongSafe_Cal_DF_V.k_AEB_StrRateReductionEntryTrhd_str)
#define k_AEB_StrRateReductionExitTrhd    (LongSafe_Cal_DF_V.k_AEB_StrRateReductionExitTrhd_str)
#define k_AEB_StrReductionEntryTrhd    (LongSafe_Cal_DF_V.k_AEB_StrReductionEntryTrhd_str)
#define k_AEB_StrReductionExitTrhd    (LongSafe_Cal_DF_V.k_AEB_StrReductionExitTrhd_str)
#define k_AEB_StrRateReductionFactor    (LongSafe_Cal_DF_V.k_AEB_StrRateReductionFactor_str)
#define k_AEB_StrReductionFactor    (LongSafe_Cal_DF_V.k_AEB_StrReductionFactor_str)
#define k_AEB_BrkReductionFactor    (LongSafe_Cal_DF_V.k_AEB_BrkReductionFactor_str)
#define k_AEB_GasPdlReductionFactor    (LongSafe_Cal_DF_V.k_AEB_GasPdlReductionFactor_str)
#define k_AEB_BrkReductionSource    (LongSafe_Cal_DF_V.k_AEB_BrkReductionSource_str)
#define k_AEB_VRUFLBAVehBehType    (LongSafe_Cal_DF_V.k_AEB_VRUFLBAVehBehType_str)
#define k_AEB_VRUFLBAVBCTTCRedFac    (LongSafe_Cal_DF_V.k_AEB_VRUFLBAVBCTTCRedFac_str)
#define k_AEB_GateMinRangeVRU    (LongSafe_Cal_DF_V.k_AEB_GateMinRangeVRU_str)
#define k_AEB_ClsFstDectVRUIPAOffset    (LongSafe_Cal_DF_V.k_AEB_ClsFstDectVRUIPAOffset_str)
#define k_AEB_RoadCondLowSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_RoadCondLowSpdTrhd_str)
#define k_AEB_RoadCondHiSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_RoadCondHiSpdTrhd_str)
#define k_AEB_VRUNumThres    (LongSafe_Cal_DF_V.k_AEB_VRUNumThres_str)
#define k_AEB_VRURadarLatErrThres    (LongSafe_Cal_DF_V.k_AEB_VRURadarLatErrThres_str)
#define k_AEB_VRUVisionLongErrThres    (LongSafe_Cal_DF_V.k_AEB_VRUVisionLongErrThres_str)
#define k_AEB_VRUXolcChkLowSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_VRUXolcChkLowSpdTrhd_str)
#define k_AEB_VRUXolcChkHiSpdTrhd    (LongSafe_Cal_DF_V.k_AEB_VRUXolcChkHiSpdTrhd_str)
#define k_AEB_MomErrorThresLong    (LongSafe_Cal_DF_V.k_AEB_MomErrorThresLong_str)
#define k_AEB_VehMomErrorThresLong    (LongSafe_Cal_DF_V.k_AEB_VehMomErrorThresLong_str)
#define k_AEB_TrtRangRateBrkPoints    (LongSafe_Cal_DF_V.k_AEB_TrtRangRateBrkPoints_str)
#define k_AEB_TrtLatRRBrkPoints    (LongSafe_Cal_DF_V.k_AEB_TrtLatRRBrkPoints_str)
#define k_AEB_MomErrorThresLat    (LongSafe_Cal_DF_V.k_AEB_MomErrorThresLat_str)
#define k_AEB_VRUXolcChkVelGapThres    (LongSafe_Cal_DF_V.k_AEB_VRUXolcChkVelGapThres_str)
#define k_AEB_VRUXolcChkLongVelThres    (LongSafe_Cal_DF_V.k_AEB_VRUXolcChkLongVelThres_str)
#define k_AEB_DesireStopDistanceLowSpd    (LongSafe_Cal_DF_V.k_AEB_DesireStopDistanceLowSpd_str)
#define k_AEB_VRUHiSpdCrossThres    (LongSafe_Cal_DF_V.k_AEB_VRUHiSpdCrossThres_str)
#define k_AEB_VRUHiSpdCrossXolcLimit    (LongSafe_Cal_DF_V.k_AEB_VRUHiSpdCrossXolcLimit_str)
#define k_AEB_VRUMinReductionFac    (LongSafe_Cal_DF_V.k_AEB_VRUMinReductionFac_str)
#define k_AEB_VehMinReductionFac    (LongSafe_Cal_DF_V.k_AEB_VehMinReductionFac_str)
#define k_AEB_VehBasicCheckFailHldTime    (LongSafe_Cal_DF_V.k_AEB_VehBasicCheckFailHldTime_str)
#define k_AEB_VRUBasicCheckFailHldTime    (LongSafe_Cal_DF_V.k_AEB_VRUBasicCheckFailHldTime_str)
#define k_AEB_TrgtNumTrhdForVRUCmplx    (LongSafe_Cal_DF_V.k_AEB_TrgtNumTrhdForVRUCmplx_str)
#define k_AEB_TrgtNumTrhdForVehCmplx    (LongSafe_Cal_DF_V.k_AEB_TrgtNumTrhdForVehCmplx_str)
#define k_AEB_VehCmplxReduceFac    (LongSafe_Cal_DF_V.k_AEB_VehCmplxReduceFac_str)
#define k_AEB_VRUCmplxReduceFac    (LongSafe_Cal_DF_V.k_AEB_VRUCmplxReduceFac_str)
#define k_AEB_VRUHBMinReductionFac    (LongSafe_Cal_DF_V.k_AEB_VRUHBMinReductionFac_str)
#define k_AEB_VehHBMinReductionFac    (LongSafe_Cal_DF_V.k_AEB_VehHBMinReductionFac_str)
#define k_AEB_NotChkSpdInFB    (LongSafe_Cal_DF_V.k_AEB_NotChkSpdInFB_str)
#define k_AEB_RE_EndRangeOffset    (LongSafe_Cal_DF_V.k_AEB_RE_EndRangeOffset_str)
#define k_AEB_RE_StartRangeOffset    (LongSafe_Cal_DF_V.k_AEB_RE_StartRangeOffset_str)
#define k_AEB_Reduce_GasPdlTrhd    (LongSafe_Cal_DF_V.k_AEB_Reduce_GasPdlTrhd_str)
#define k_GasPdlReduceDelayTime    (LongSafe_Cal_DF_V.k_GasPdlReduceDelayTime_str)
#define k_AEB_Use_TTE_In_CCR    (LongSafe_Cal_DF_V.k_AEB_Use_TTE_In_CCR_str)
#define k_AEB_MinLostRangeVRU    (LongSafe_Cal_DF_V.k_AEB_MinLostRangeVRU_str)
#define k_AEB_MinLostLatPosVRU    (LongSafe_Cal_DF_V.k_AEB_MinLostLatPosVRU_str)
#define k_AEB_MinLostRangeVeh    (LongSafe_Cal_DF_V.k_AEB_MinLostRangeVeh_str)
#define k_AEB_MinLostLatPosVeh    (LongSafe_Cal_DF_V.k_AEB_MinLostLatPosVeh_str)
#define k_AEB_CloseLostHold_Enabled    (LongSafe_Cal_DF_V.k_AEB_CloseLostHold_Enabled_str)
#define k_AEB_MinLostLatEstVRU    (LongSafe_Cal_DF_V.k_AEB_MinLostLatEstVRU_str)
#define k_AEB_GdRail_RangeOffset    (LongSafe_Cal_DF_V.k_AEB_GdRail_RangeOffset_str)
#define k_AEB_NearTrgt_RedFac    (LongSafe_Cal_DF_V.k_AEB_NearTrgt_RedFac_str)
#define k_AEB_VRUVehBehType    (LongSafe_Cal_DF_V.k_AEB_VRUVehBehType_str)
#define k_AEB_VRUVBCTTCRedFac    (LongSafe_Cal_DF_V.k_AEB_VRUVBCTTCRedFac_str)
#define k_AEB_TTBAvgBrkDelay_Full    (LongSafe_Cal_DF_V.k_AEB_TTBAvgBrkDelay_Full_str)
#define k_AEB_HiToFuBrakingLvlMov_mps    (LongSafe_Cal_DF_V.k_AEB_HiToFuBrakingLvlMov_mps_str)
#define k_AEB_LwBrakingLvl_Factor    (LongSafe_Cal_DF_V.k_AEB_LwBrakingLvl_Factor_str)
#define k_AEB_UseCSMdlToLwBrkRngCal    (LongSafe_Cal_DF_V.k_AEB_UseCSMdlToLwBrkRngCal_str)
#define k_AEB_CloseLost_VRUEnableMask    (LongSafe_Cal_DF_V.k_AEB_CloseLost_VRUEnableMask_str)
#define k_AEB_DBSStatTimeGap    (LongSafe_Cal_DF_V.k_AEB_DBSStatTimeGap_str)
#define k_AEB_DBSMovTimeGap    (LongSafe_Cal_DF_V.k_AEB_DBSMovTimeGap_str)
#define k_AEB_DBSUseRangeTrigger    (LongSafe_Cal_DF_V.k_AEB_DBSUseRangeTrigger_str)
#define k_AEB_TTCAccelBasedCalMode    (LongSafe_Cal_DF_V.k_AEB_TTCAccelBasedCalMode_str)
#define k_AEB_DBSBrakingLvl_Factor    (LongSafe_Cal_DF_V.k_AEB_DBSBrakingLvl_Factor_str)
#define k_AEB_LowBrkMaxRangeStat    (LongSafe_Cal_DF_V.k_AEB_LowBrkMaxRangeStat_str)
#define k_AEB_LowBrkMaxRangeMov    (LongSafe_Cal_DF_V.k_AEB_LowBrkMaxRangeMov_str)
#define k_AEB_MovTrgtFlyInMaxRange    (LongSafe_Cal_DF_V.k_AEB_MovTrgtFlyInMaxRange_str)
#define k_AEB_StatTrgtFlyInMaxRange    (LongSafe_Cal_DF_V.k_AEB_StatTrgtFlyInMaxRange_str)
#define k_AEB_TrgtFlyInMaxLatPos    (LongSafe_Cal_DF_V.k_AEB_TrgtFlyInMaxLatPos_str)
#define k_AEB_TrgtFlyInMaxAge    (LongSafe_Cal_DF_V.k_AEB_TrgtFlyInMaxAge_str)
#define k_AEB_FlyInDectIPAOffset    (LongSafe_Cal_DF_V.k_AEB_FlyInDectIPAOffset_str)
#define k_AEB_DBSBrkMaxStatRange    (LongSafe_Cal_DF_V.k_AEB_DBSBrkMaxStatRange_str)
#define k_AEB_DBSBrkMaxMovRange    (LongSafe_Cal_DF_V.k_AEB_DBSBrkMaxMovRange_str)
#define k_AEB_ExtraInpathAgeCounter_z    (LongSafe_Cal_DF_V.k_AEB_ExtraInpathAgeCounter_z_str[0])
#define k_AEB_ExtraInpathAgeCounter_x    (LongSafe_Cal_DF_V.k_AEB_ExtraInpathAgeCounter_x_str)
#define k_AEB_ExtraInpathAgeCounter_y    (LongSafe_Cal_DF_V.k_AEB_ExtraInpathAgeCounter_y_str)
#define k_AEB_LongBikeHB_TTCMax    (LongSafe_Cal_DF_V.k_AEB_LongBikeHB_TTCMax_str)
#define k_AEB_LongBikeLB_TTCMax    (LongSafe_Cal_DF_V.k_AEB_LongBikeLB_TTCMax_str)
#define k_AEB_LongBikePF_TTCMax    (LongSafe_Cal_DF_V.k_AEB_LongBikePF_TTCMax_str)
#define k_AEB_VRUNoPredictLongVelThres    (LongSafe_Cal_DF_V.k_AEB_VRUNoPredictLongVelThres_str)
#define k_AEB_ROCDecelLimit_tbl_y    (LongSafe_Cal_DF_V.k_AEB_ROCDecelLimit_tbl_y_str)
#define k_AEB_ROCDecelLimit_tbl_x    (LongSafe_Cal_DF_V.k_AEB_ROCDecelLimit_tbl_x_str)
#define k_AEB_LoadDecelLimit_tbl_y    (LongSafe_Cal_DF_V.k_AEB_LoadDecelLimit_tbl_y_str)
#define k_AEB_LoadDecelLimit_tbl_x    (LongSafe_Cal_DF_V.k_AEB_LoadDecelLimit_tbl_x_str)
#define k_AEB_SpdDecelLimit_tbl_y    (LongSafe_Cal_DF_V.k_AEB_SpdDecelLimit_tbl_y_str)
#define k_AEB_SpdDecelLimit_tbl_x    (LongSafe_Cal_DF_V.k_AEB_SpdDecelLimit_tbl_x_str)
#define k_AEB_VRU_BrkRls_en    (LongSafe_Cal_DF_V.k_AEB_VRU_BrkRls_en_str)
#define k_AEB_VRU_SpdReduction_max    (LongSafe_Cal_DF_V.k_AEB_VRU_SpdReduction_max_str)
#define k_AEB_BrkAct_LimitDecel_en    (LongSafe_Cal_DF_V.k_AEB_BrkAct_LimitDecel_en_str)
#define k_AEB_DetBrkAct_AccelMax    (LongSafe_Cal_DF_V.k_AEB_DetBrkAct_AccelMax_str)
#define k_AEB_PedDecelerateDetectAccel    (LongSafe_Cal_DF_V.k_AEB_PedDecelerateDetectAccel_str)
#define k_AEB_TWDecelerateDetectAccel    (LongSafe_Cal_DF_V.k_AEB_TWDecelerateDetectAccel_str)
#define k_AEB_VRUDecelerateDetectHdTm    (LongSafe_Cal_DF_V.k_AEB_VRUDecelerateDetectHdTm_str)
#define k_AEB_XolcLaterEntryGate    (LongSafe_Cal_DF_V.k_AEB_XolcLaterEntryGate_str)
#define k_AEB_XolcLaterExitGate    (LongSafe_Cal_DF_V.k_AEB_XolcLaterExitGate_str)
#define k_AEB_IniMethodVRUIPAOffset    (LongSafe_Cal_DF_V.k_AEB_IniMethodVRUIPAOffset_str)
#define k_AEB_HldRls_AccelPos    (LongSafe_Cal_DF_V.k_AEB_HldRls_AccelPos_str)
#define k_AEB_CCRB_MinActiveAccel    (LongSafe_Cal_DF_V.k_AEB_CCRB_MinActiveAccel_str)
#define k_AEB_CCRB_ActiveDelay    (LongSafe_Cal_DF_V.k_AEB_CCRB_ActiveDelay_str)
#define k_AEB_CCRB_ActiveDelaySpdPoints    (LongSafe_Cal_DF_V.k_AEB_CCRB_ActiveDelaySpdPoints_str)
#define k_AEB_CCRB_IgnoreClassCheck    (LongSafe_Cal_DF_V.k_AEB_CCRB_IgnoreClassCheck_str)
#define k_AEB_CCRB_ActiveHldTime    (LongSafe_Cal_DF_V.k_AEB_CCRB_ActiveHldTime_str)
#define k_AEB_HldAllowMaxVRUSpd    (LongSafe_Cal_DF_V.k_AEB_HldAllowMaxVRUSpd_str)
#define k_AEB_HldAllowMaxVehSpd    (LongSafe_Cal_DF_V.k_AEB_HldAllowMaxVehSpd_str)
#define k_AEB_HldAllowMaxVRURange    (LongSafe_Cal_DF_V.k_AEB_HldAllowMaxVRURange_str)
#define k_AEB_HldAllowMaxVehRange    (LongSafe_Cal_DF_V.k_AEB_HldAllowMaxVehRange_str)
#define k_AEB_HldEntryIgnObjCheck    (LongSafe_Cal_DF_V.k_AEB_HldEntryIgnObjCheck_str)
#define k_AEB_HldRlsMinVRULatEst    (LongSafe_Cal_DF_V.k_AEB_HldRlsMinVRULatEst_str)
#define k_AEB_HldRlsMinVRULatPos    (LongSafe_Cal_DF_V.k_AEB_HldRlsMinVRULatPos_str)
#define k_AEB_HldRlsMinVehLatEst    (LongSafe_Cal_DF_V.k_AEB_HldRlsMinVehLatEst_str)
#define k_AEB_HldRlsMinVehLatPos    (LongSafe_Cal_DF_V.k_AEB_HldRlsMinVehLatPos_str)
#define k_AEB_HldRlsMinVehSpd    (LongSafe_Cal_DF_V.k_AEB_HldRlsMinVehSpd_str)
#define k_AEB_HldRlsMinVehRange    (LongSafe_Cal_DF_V.k_AEB_HldRlsMinVehRange_str)
#define k_AEB_HldRlsMinVRURange    (LongSafe_Cal_DF_V.k_AEB_HldRlsMinVRURange_str)
#define k_AEB_HoldBrkPdlPosThres    (LongSafe_Cal_DF_V.k_AEB_HoldBrkPdlPosThres_str)
#define k_AEB_DrvActInHoldTm    (LongSafe_Cal_DF_V.k_AEB_DrvActInHoldTm_str)
#define k_AEB_UseHoldTrigDly    (LongSafe_Cal_DF_V.k_AEB_UseHoldTrigDly_str)
#define k_AEB_CheckIniMethodMaxAge    (LongSafe_Cal_DF_V.k_AEB_CheckIniMethodMaxAge_str)
#define k_AEB_IBA_DecelCalMod    (LongSafe_Cal_DF_V.k_AEB_IBA_DecelCalMod_str)
#define k_AEB_IBA_BypassBrkPosPrs    (LongSafe_Cal_DF_V.k_AEB_IBA_BypassBrkPosPrs_str)
#define k_AEB_IBA_BypassDecel    (LongSafe_Cal_DF_V.k_AEB_IBA_BypassDecel_str)
#define k_AEB_IgnoreCBLATTBCal    (LongSafe_Cal_DF_V.k_AEB_IgnoreCBLATTBCal_str)
#define k_AEB_HighSpdCrsLatVel    (LongSafe_Cal_DF_V.k_AEB_HighSpdCrsLatVel_str)
#define k_AEB_VehMaxAllowSpdStep    (LongSafe_Cal_DF_V.k_AEB_VehMaxAllowSpdStep_str)
#define k_AEB_VehMaxAllowAgeStep    (LongSafe_Cal_DF_V.k_AEB_VehMaxAllowAgeStep_str)
#define k_AEB_IgnVRUInpathAgeChk    (LongSafe_Cal_DF_V.k_AEB_IgnVRUInpathAgeChk_str)
#define k_AEB_VehRdrInfoChkFailHldTime    (LongSafe_Cal_DF_V.k_AEB_VehRdrInfoChkFailHldTime_str)
#define k_AEB_VRUIDChgChkHoldTime    (LongSafe_Cal_DF_V.k_AEB_VRUIDChgChkHoldTime_str)
#define k_AEB_VRUHiBrkIgnLatAccEn    (LongSafe_Cal_DF_V.k_AEB_VRUHiBrkIgnLatAccEn_str)
#define k_AEB_host_straightly_yaw_thrh    (LongSafe_Cal_DF_V.k_AEB_host_straightly_yaw_thrh_str)
#define k_AEB_VRUHiBrkIgnLatEstEn    (LongSafe_Cal_DF_V.k_AEB_VRUHiBrkIgnLatEstEn_str)
#define k_AEB_VRUHiBrkUseRangeTrigger    (LongSafe_Cal_DF_V.k_AEB_VRUHiBrkUseRangeTrigger_str)
#define k_AEB_BikeHitSpdDes_mps    (LongSafe_Cal_DF_V.k_AEB_BikeHitSpdDes_mps_str)
#define k_AEB_BikeStatHitSpdDes_mps    (LongSafe_Cal_DF_V.k_AEB_BikeStatHitSpdDes_mps_str)
#define k_AEB_LongBikeHitSpdDes_mps    (LongSafe_Cal_DF_V.k_AEB_LongBikeHitSpdDes_mps_str)
#define k_AEB_OCBikeHitSpdDes_mps    (LongSafe_Cal_DF_V.k_AEB_OCBikeHitSpdDes_mps_str)
#define k_AEB_PedHitSpdDes_mps    (LongSafe_Cal_DF_V.k_AEB_PedHitSpdDes_mps_str)
#define k_AEB_OCPedHitSpdDes_mps    (LongSafe_Cal_DF_V.k_AEB_OCPedHitSpdDes_mps_str)
#define k_AEB_VRUTTBAvgBrkDelay    (LongSafe_Cal_DF_V.k_AEB_VRUTTBAvgBrkDelay_str)
#define k_AEB_VRUTTBAvgBrkDelay_Full    (LongSafe_Cal_DF_V.k_AEB_VRUTTBAvgBrkDelay_Full_str)
#define k_AEB_DesHitSpdInputTbl_mps    (LongSafe_Cal_DF_V.k_AEB_DesHitSpdInputTbl_mps_str)
#define k_AEB_VRULowBrkMaxRng_m    (LongSafe_Cal_DF_V.k_AEB_VRULowBrkMaxRng_m_str)
#define k_AEB_VRULowBrkMaxTTC_sec    (LongSafe_Cal_DF_V.k_AEB_VRULowBrkMaxTTC_sec_str)
#define k_AEB_VRUPFMaxRng_m    (LongSafe_Cal_DF_V.k_AEB_VRUPFMaxRng_m_str)
#define k_AEB_VRUPFMaxTTC_sec    (LongSafe_Cal_DF_V.k_AEB_VRUPFMaxTTC_sec_str)
#define k_AEB_VRUPFTrigDuration    (LongSafe_Cal_DF_V.k_AEB_VRUPFTrigDuration_str)
#define k_AEB_VRUFLBATrigDuration    (LongSafe_Cal_DF_V.k_AEB_VRUFLBATrigDuration_str)
#define k_AEB_VRUMinStopTrigDuration    (LongSafe_Cal_DF_V.k_AEB_VRUMinStopTrigDuration_str)
#define k_AEB_BikeLBDuration_sec    (LongSafe_Cal_DF_V.k_AEB_BikeLBDuration_sec_str)
#define k_AEB_BikeStatLBDuration_sec    (LongSafe_Cal_DF_V.k_AEB_BikeStatLBDuration_sec_str)
#define k_AEB_LongBikeLBDuration_sec    (LongSafe_Cal_DF_V.k_AEB_LongBikeLBDuration_sec_str)
#define k_AEB_OCBikeLBDuration_sec    (LongSafe_Cal_DF_V.k_AEB_OCBikeLBDuration_sec_str)
#define k_AEB_PedLBDuration_sec    (LongSafe_Cal_DF_V.k_AEB_PedLBDuration_sec_str)
#define k_AEB_OCPedLBDuration_sec    (LongSafe_Cal_DF_V.k_AEB_OCPedLBDuration_sec_str)
#define k_AEB_IgnoreEstHitDistChk    (LongSafe_Cal_DF_V.k_AEB_IgnoreEstHitDistChk_str)
#define k_AEB_IgnoreEstYawDistChk    (LongSafe_Cal_DF_V.k_AEB_IgnoreEstYawDistChk_str)
#define k_AEB_IgnoreXolcLaterChk    (LongSafe_Cal_DF_V.k_AEB_IgnoreXolcLaterChk_str)
#define k_AEB_NonCrsPed_MinSpd_mps    (LongSafe_Cal_DF_V.k_AEB_NonCrsPed_MinSpd_mps_str)
#define k_AEB_NonCrsPed_LBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_NonCrsPed_LBMaxSpd_mps_str)
#define k_AEB_CrsPed_LBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_CrsPed_LBMaxSpd_mps_str)
#define k_AEB_StatBike_LBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_StatBike_LBMaxSpd_mps_str)
#define k_AEB_CrsBike_LBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_CrsBike_LBMaxSpd_mps_str)
#define k_AEB_LongBike_LBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_LongBike_LBMaxSpd_mps_str)
#define k_AEB_OCPed_LBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_OCPed_LBMaxSpd_mps_str)
#define k_AEB_OCBike_LBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_OCBike_LBMaxSpd_mps_str)
#define k_AEB_CrsPed_HBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_CrsPed_HBMaxSpd_mps_str)
#define k_AEB_NonCrsPed_HBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_NonCrsPed_HBMaxSpd_mps_str)
#define k_AEB_StatBike_HBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_StatBike_HBMaxSpd_mps_str)
#define k_AEB_CrsBike_HBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_CrsBike_HBMaxSpd_mps_str)
#define k_AEB_LongBike_HBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_LongBike_HBMaxSpd_mps_str)
#define k_AEB_OCPed_HBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_OCPed_HBMaxSpd_mps_str)
#define k_AEB_OCBike_HBMaxSpd_mps    (LongSafe_Cal_DF_V.k_AEB_OCBike_HBMaxSpd_mps_str)
#define k_AEB_BikeIBADuration_sec    (LongSafe_Cal_DF_V.k_AEB_BikeIBADuration_sec_str)
#define k_AEB_BikeStatIBADuration_sec    (LongSafe_Cal_DF_V.k_AEB_BikeStatIBADuration_sec_str)
#define k_AEB_LongBikeIBADuration_sec    (LongSafe_Cal_DF_V.k_AEB_LongBikeIBADuration_sec_str)
#define k_AEB_OCBikeIBADuration_sec    (LongSafe_Cal_DF_V.k_AEB_OCBikeIBADuration_sec_str)
#define k_AEB_PedIBADuration_sec    (LongSafe_Cal_DF_V.k_AEB_PedIBADuration_sec_str)
#define k_AEB_OCPedIBADuration_sec    (LongSafe_Cal_DF_V.k_AEB_OCPedIBADuration_sec_str)
#define k_AEB_DBSBrkVRUMaxRange    (LongSafe_Cal_DF_V.k_AEB_DBSBrkVRUMaxRange_str)
#define k_AEB_DBSVRUMinSpdChkEnbl    (LongSafe_Cal_DF_V.k_AEB_DBSVRUMinSpdChkEnbl_str)
#define k_AEB_VRUDBSMaxDecel_mps    (LongSafe_Cal_DF_V.k_AEB_VRUDBSMaxDecel_mps_str)
#define k_AEB_DBSVRUMinVehicleSpd    (LongSafe_Cal_DF_V.k_AEB_DBSVRUMinVehicleSpd_str)
#define k_AEB_IBAVRU_BypassDecel    (LongSafe_Cal_DF_V.k_AEB_IBAVRU_BypassDecel_str)
#define k_AEB_TWLatEstComp    (LongSafe_Cal_DF_V.k_AEB_TWLatEstComp_str)
#define k_AEB_VRUHiBrkLvl_mps_offset    (LongSafe_Cal_DF_V.k_AEB_VRUHiBrkLvl_mps_offset_str)
#define k_AEB_HiBrkLongBikeRangeOffset    (LongSafe_Cal_DF_V.k_AEB_HiBrkLongBikeRangeOffset_str)
#define k_AEB_HiBrkRefRange    (LongSafe_Cal_DF_V.k_AEB_HiBrkRefRange_str)
#define k_AEB_VRUHiBrkRefRange    (LongSafe_Cal_DF_V.k_AEB_VRUHiBrkRefRange_str)
#define k_AEB_SpdReduction_max    (LongSafe_Cal_DF_V.k_AEB_SpdReduction_max_str)
#define k_AEB_Veh_BrkRls_en    (LongSafe_Cal_DF_V.k_AEB_Veh_BrkRls_en_str)
#define k_AEB_BrkPdlEngageLgAccThres    (LongSafe_Cal_DF_V.k_AEB_BrkPdlEngageLgAccThres_str)
#define k_AEB_BrkPosConfirmEn    (LongSafe_Cal_DF_V.k_AEB_BrkPosConfirmEn_str)
#define k_AEB_BrkPrsConfirmEn    (LongSafe_Cal_DF_V.k_AEB_BrkPrsConfirmEn_str)
#define k_AEB_VRULoBrkIgnLatEstEn    (LongSafe_Cal_DF_V.k_AEB_VRULoBrkIgnLatEstEn_str)
#define k_AEB_VRULoBrkHoldXolcThres    (LongSafe_Cal_DF_V.k_AEB_VRULoBrkHoldXolcThres_str)
#define k_AEB_VRUHiBrkRefRange_IBST    (LongSafe_Cal_DF_V.k_AEB_VRUHiBrkRefRange_IBST_str)
#define k_AEB_VRUHiBrkRefRange_ESP    (LongSafe_Cal_DF_V.k_AEB_VRUHiBrkRefRange_ESP_str)
#define k_AEB_LongPedLBDuration_sec    (LongSafe_Cal_DF_V.k_AEB_LongPedLBDuration_sec_str)
#define k_AEB_HiBrkRefRange_IBST    (LongSafe_Cal_DF_V.k_AEB_HiBrkRefRange_IBST_str)
#define k_AEB_HiBrkRefRange_ESP    (LongSafe_Cal_DF_V.k_AEB_HiBrkRefRange_ESP_str)
#define k_AEB_VruHBCrossingRangeOffset    (LongSafe_Cal_DF_V.k_AEB_VruHBCrossingRangeOffset_str)
#define k_AEB_DesireStopDistance_IBST    (LongSafe_Cal_DF_V.k_AEB_DesireStopDistance_IBST_str)
#define k_AEB_DesireStopDistance_ESP    (LongSafe_Cal_DF_V.k_AEB_DesireStopDistance_ESP_str)
#define k_AEB_CLHiBrkNeedDecelLimt_IBA    (LongSafe_Cal_DF_V.k_AEB_CLHiBrkNeedDecelLimt_IBA_str)
#define k_AEB_VRUXolcUpLimit    (LongSafe_Cal_DF_V.k_AEB_VRUXolcUpLimit_str)
#define k_AEB_VRUXolcDownLimit    (LongSafe_Cal_DF_V.k_AEB_VRUXolcDownLimit_str)
#define k_AEB_TapVehIgnStrOvrdMask    (LongSafe_Cal_DF_V.k_AEB_TapVehIgnStrOvrdMask_str)
#define k_AEB_TapVRUIgnStrOvrdMask    (LongSafe_Cal_DF_V.k_AEB_TapVRUIgnStrOvrdMask_str)
#define k_AEB_IgnDrvBehRedToFunnel    (LongSafe_Cal_DF_V.k_AEB_IgnDrvBehRedToFunnel_str)
#define k_AEB_DrvOvrdBasePreFac_FLBA    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBasePreFac_FLBA_str)
#define k_AEB_DrvOvrdBasePosFac_FLBA    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBasePosFac_FLBA_str)
#define k_AEB_DrvOvrdBasePreFac_PF    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBasePreFac_PF_str)
#define k_AEB_DrvOvrdBasePosFac_PF    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBasePosFac_PF_str)
#define k_AEB_DrvOvrdBasePreFac_LB    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBasePreFac_LB_str)
#define k_AEB_DrvOvrdBasePosFac_LB    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBasePosFac_LB_str)
#define k_AEB_DrvOvrdBasePreFac_HB    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBasePreFac_HB_str)
#define k_AEB_DrvOvrdBasePosFac_HB    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBasePosFac_HB_str)
#define k_AEB_DrvOvrdBasePreFac_FB    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBasePreFac_FB_str)
#define k_AEB_DrvOvrdBasePosFac_FB    (LongSafe_Cal_DF_V.k_AEB_DrvOvrdBasePosFac_FB_str)
#define k_AEB_HiSpdBrkEngPresEnblTm    (LongSafe_Cal_DF_V.k_AEB_HiSpdBrkEngPresEnblTm_str)
#define k_AEB_HiSpdBrkEngPosEnTime    (LongSafe_Cal_DF_V.k_AEB_HiSpdBrkEngPosEnTime_str)
#define k_AEB_GasRateEngHdTm    (LongSafe_Cal_DF_V.k_AEB_GasRateEngHdTm_str)
#define k_AEB_HiSpdGasRateEngHdTm    (LongSafe_Cal_DF_V.k_AEB_HiSpdGasRateEngHdTm_str)
#define k_AEB_GasRateCntThres    (LongSafe_Cal_DF_V.k_AEB_GasRateCntThres_str)
#define k_AEB_HiSpdGasRateCntThres    (LongSafe_Cal_DF_V.k_AEB_HiSpdGasRateCntThres_str)
#define k_AEB_DrvEngUseTTCReduc_IBA    (LongSafe_Cal_DF_V.k_AEB_DrvEngUseTTCReduc_IBA_str)
#define k_AEB_BrkPdlEngageMode    (LongSafe_Cal_DF_V.k_AEB_BrkPdlEngageMode_str)
#define k_AEB_BrkEngStatusEnTime    (LongSafe_Cal_DF_V.k_AEB_BrkEngStatusEnTime_str)
#define k_AEB_BrkResetHaloTime_ms    (LongSafe_Cal_DF_V.k_AEB_BrkResetHaloTime_ms_str)
#define k_AEB_IgnoreBrkResetChk    (LongSafe_Cal_DF_V.k_AEB_IgnoreBrkResetChk_str)
#define k_AEB_IBA_UseBrkPedal    (LongSafe_Cal_DF_V.k_AEB_IBA_UseBrkPedal_str)
#define k_AEB_EnBrkResetChk    (LongSafe_Cal_DF_V.k_AEB_EnBrkResetChk_str)
#define k_AEB_LeadVel_OCDead    (LongSafe_Cal_DF_V.k_AEB_LeadVel_OCDead_str)
#define k_AEB_IBA_PermitAccelGap    (LongSafe_Cal_DF_V.k_AEB_IBA_PermitAccelGap_str)
#define k_AEB_BrkPosIgnore    (LongSafe_Cal_DF_V.k_AEB_BrkPosIgnore_str)
#define k_AEB_BrkPrsIgnore    (LongSafe_Cal_DF_V.k_AEB_BrkPrsIgnore_str)
#define k_AEB_BikeHiConfMaxHeadError    (LongSafe_Cal_DF_V.k_AEB_BikeHiConfMaxHeadError_str)
#define k_AEB_HostSpdEstUsed    (LongSafe_Cal_DF_V.k_AEB_HostSpdEstUsed_str)
#define k_AEB_MovHiBrkRefRange_IBST    (LongSafe_Cal_DF_V.k_AEB_MovHiBrkRefRange_IBST_str)
#define k_AEB_MovHiBrkRefRange_ESP    (LongSafe_Cal_DF_V.k_AEB_MovHiBrkRefRange_ESP_str)
#define k_AEB_CrossHiBrkRefRange_ESP    (LongSafe_Cal_DF_V.k_AEB_CrossHiBrkRefRange_ESP_str)
#define k_AEB_Brk_Reduc_ToFunnel    (LongSafe_Cal_DF_V.k_AEB_Brk_Reduc_ToFunnel_str)
#define k_AEB_Spd_Reduc_ToFunnel    (LongSafe_Cal_DF_V.k_AEB_Spd_Reduc_ToFunnel_str)
#define k_AEB_NearTrgtReducHdTm    (LongSafe_Cal_DF_V.k_AEB_NearTrgtReducHdTm_str)
#define k_AEB_GateMinLatPosVRU    (LongSafe_Cal_DF_V.k_AEB_GateMinLatPosVRU_str)
#define k_AEB_VehMinMatchConf    (LongSafe_Cal_DF_V.k_AEB_VehMinMatchConf_str)
#define k_AEB_BigXolc_RedFac    (LongSafe_Cal_DF_V.k_AEB_BigXolc_RedFac_str)
#define k_AEB_VRURangeBrkPoints    (LongSafe_Cal_DF_V.k_AEB_VRURangeBrkPoints_str)
#define k_AEB_IgnoreVRUFusChk    (LongSafe_Cal_DF_V.k_AEB_IgnoreVRUFusChk_str)
#define k_AEB_HostStraightlyYawThrh    (LongSafe_Cal_DF_V.k_AEB_HostStraightlyYawThrh_str)
#define k_AEB_VRUHB_UseDefaultOfst    (LongSafe_Cal_DF_V.k_AEB_VRUHB_UseDefaultOfst_str)
#define k_AEB_VRUHB_LongBikeOffset    (LongSafe_Cal_DF_V.k_AEB_VRUHB_LongBikeOffset_str)
#define k_AEB_VRUHB_CrossBikeOffset    (LongSafe_Cal_DF_V.k_AEB_VRUHB_CrossBikeOffset_str)
#define k_AEB_VRUHB_StatBikeOffset    (LongSafe_Cal_DF_V.k_AEB_VRUHB_StatBikeOffset_str)
#define k_AEB_VRUHB_LongPedOffset    (LongSafe_Cal_DF_V.k_AEB_VRUHB_LongPedOffset_str)
#define k_AEB_VRUHB_CrossPedOffset    (LongSafe_Cal_DF_V.k_AEB_VRUHB_CrossPedOffset_str)
#define k_AEB_VRUHB_StatPedOffset    (LongSafe_Cal_DF_V.k_AEB_VRUHB_StatPedOffset_str)
#define k_AEB_UseLgSfJAVehCusSet    (LongSafe_Cal_DF_V.k_AEB_UseLgSfJAVehCusSet_str)
#define k_AEB_UseLgSfJAPedCusSet    (LongSafe_Cal_DF_V.k_AEB_UseLgSfJAPedCusSet_str)
#define k_AEB_PedVisLatEstChkDisable    (LongSafe_Cal_DF_V.k_AEB_PedVisLatEstChkDisable_str)
#define k_AEB_PedOCPedExitThres    (LongSafe_Cal_DF_V.k_AEB_PedOCPedExitThres_str)
#define k_AEB_PedOCCrossingAllow    (LongSafe_Cal_DF_V.k_AEB_PedOCCrossingAllow_str)
#define k_AEB_PedIgnoreVisPlauCheck    (LongSafe_Cal_DF_V.k_AEB_PedIgnoreVisPlauCheck_str)
#define k_AEB_PedUseVisionTTC    (LongSafe_Cal_DF_V.k_AEB_PedUseVisionTTC_str)
#define k_AEB_DisblAEBOCBicycle    (LongSafe_Cal_DF_V.k_AEB_DisblAEBOCBicycle_str)
#define k_AEB_DisblAEBBicycle    (LongSafe_Cal_DF_V.k_AEB_DisblAEBBicycle_str)
#define k_AEB_DisblAEBPed    (LongSafe_Cal_DF_V.k_AEB_DisblAEBPed_str)
#define k_AEB_DisblAEBOCPed    (LongSafe_Cal_DF_V.k_AEB_DisblAEBOCPed_str)
#define k_AEB_UseRRFunelInput    (LongSafe_Cal_DF_V.k_AEB_UseRRFunelInput_str)
#define k_AEB_EnableYawRateRedc    (LongSafe_Cal_DF_V.k_AEB_EnableYawRateRedc_str)
#define k_AEB_IgnoreLongVelForCrsScene    (LongSafe_Cal_DF_V.k_AEB_IgnoreLongVelForCrsScene_str)
#define k_AEB_UseTapTTCForVRU    (LongSafe_Cal_DF_V.k_AEB_UseTapTTCForVRU_str)
#define k_AEB_IgnoreVRUXolcChk    (LongSafe_Cal_DF_V.k_AEB_IgnoreVRUXolcChk_str)
#define k_AEB_IgnoreVehFusionCheck    (LongSafe_Cal_DF_V.k_AEB_IgnoreVehFusionCheck_str)
#define k_AEB_IgnoreVehRadarCheck    (LongSafe_Cal_DF_V.k_AEB_IgnoreVehRadarCheck_str)
#define k_AEB_IgnoreVRUBasicCheck    (LongSafe_Cal_DF_V.k_AEB_IgnoreVRUBasicCheck_str)
#define k_AEB_UseTapThresFunc    (LongSafe_Cal_DF_V.k_AEB_UseTapThresFunc_str)
#define k_AEB_mi_VisLowConf    (LongSafe_Cal_DF_V.k_AEB_mi_VisLowConf_str)
#define k_AEB_AllowFCWOCBicycle    (LongSafe_Cal_DF_V.k_AEB_AllowFCWOCBicycle_str)
#define k_AEB_DisblFCWBicycle    (LongSafe_Cal_DF_V.k_AEB_DisblFCWBicycle_str)
#define k_AEB_AllowFCWOCPed    (LongSafe_Cal_DF_V.k_AEB_AllowFCWOCPed_str)
#define k_AEB_DisblFCWPed    (LongSafe_Cal_DF_V.k_AEB_DisblFCWPed_str)
#define k_AEB_ABALevel    (LongSafe_Cal_DF_V.k_AEB_ABALevel_str)
#define k_AEB_AWBLevel    (LongSafe_Cal_DF_V.k_AEB_AWBLevel_str)
#define k_AEB_NotUseBrakeTypeFlag    (LongSafe_Cal_DF_V.k_AEB_NotUseBrakeTypeFlag_str)
#define k_AEB_UseShadowMode    (LongSafe_Cal_DF_V.k_AEB_UseShadowMode_str)
#define k_AEB_IgnoreFusVisCheck    (LongSafe_Cal_DF_V.k_AEB_IgnoreFusVisCheck_str)
#define k_AEB_AWBAutoBrkTyp_Mask    (LongSafe_Cal_DF_V.k_AEB_AWBAutoBrkTyp_Mask_str)
#define k_AEB_MaxTime_ms_AWBReq    (LongSafe_Cal_DF_V.k_AEB_MaxTime_ms_AWBReq_str)
#define k_AEB_DRTVisLongErrThres    (LongSafe_Cal_DF_V.k_AEB_DRTVisLongErrThres_str)
#define k_AEB_DRTVisLongChkDelayTime    (LongSafe_Cal_DF_V.k_AEB_DRTVisLongChkDelayTime_str)
#define k_AEB_FullLatVel    (LongSafe_Cal_DF_V.k_AEB_FullLatVel_str)
#define k_AEB_NegligibleLatVel    (LongSafe_Cal_DF_V.k_AEB_NegligibleLatVel_str)
#define k_AEB_YawRateIgnoreLatVel    (LongSafe_Cal_DF_V.k_AEB_YawRateIgnoreLatVel_str)
#define k_AEB_LatVelMinStepsize    (LongSafe_Cal_DF_V.k_AEB_LatVelMinStepsize_str)
#define k_AEB_LongVelMinStepsize    (LongSafe_Cal_DF_V.k_AEB_LongVelMinStepsize_str)
#define k_AEB_UseVelTrackAngle    (LongSafe_Cal_DF_V.k_AEB_UseVelTrackAngle_str)
#define k_AEB_UseLatVelforRR    (LongSafe_Cal_DF_V.k_AEB_UseLatVelforRR_str)
#define k_AEB_UseHostSpdBsdRR    (LongSafe_Cal_DF_V.k_AEB_UseHostSpdBsdRR_str)
#define k_AEB_LatVelVisionConfirmIgnr    (LongSafe_Cal_DF_V.k_AEB_LatVelVisionConfirmIgnr_str)
#define k_AEB_Default_Time_Offset    (LongSafe_Cal_DF_V.k_AEB_Default_Time_Offset_str)
#define k_AEB_VehRangeBrkPoints    (LongSafe_Cal_DF_V.k_AEB_VehRangeBrkPoints_str)
#define k_AEB_VehRangRateBrkPoints    (LongSafe_Cal_DF_V.k_AEB_VehRangRateBrkPoints_str)
#define k_AEB_VehLongRangeErrorThres    (LongSafe_Cal_DF_V.k_AEB_VehLongRangeErrorThres_str[0])
#define k_AEB_VehLatRangeErrorThres    (LongSafe_Cal_DF_V.k_AEB_VehLatRangeErrorThres_str)
#define k_AEB_TgtMomErrorThresLong    (LongSafe_Cal_DF_V.k_AEB_TgtMomErrorThresLong_str)
#define k_AEB_TgtMomErrorThresLat    (LongSafe_Cal_DF_V.k_AEB_TgtMomErrorThresLat_str)
#define k_AEB_VehLatRRBrkPoints    (LongSafe_Cal_DF_V.k_AEB_VehLatRRBrkPoints_str)
#define k_AEB_VehAccuErrorChkOnLong    (LongSafe_Cal_DF_V.k_AEB_VehAccuErrorChkOnLong_str)
#define k_AEB_VehAccuErrorChkOnLat    (LongSafe_Cal_DF_V.k_AEB_VehAccuErrorChkOnLat_str)
#define k_AEB_VehMomeErrorChkOnLong    (LongSafe_Cal_DF_V.k_AEB_VehMomeErrorChkOnLong_str)
#define k_AEB_VehMomeErrorChkOnLat    (LongSafe_Cal_DF_V.k_AEB_VehMomeErrorChkOnLat_str)
#define k_AEB_VehBaseChkFailEnblTime    (LongSafe_Cal_DF_V.k_AEB_VehBaseChkFailEnblTime_str)
#define k_AEB_VehBaseChkFailHoldTime    (LongSafe_Cal_DF_V.k_AEB_VehBaseChkFailHoldTime_str)
#define k_AEB_VehErrorAccuPerdLong    (LongSafe_Cal_DF_V.k_AEB_VehErrorAccuPerdLong_str)
#define k_AEB_VehErrorAccuPerdLat    (LongSafe_Cal_DF_V.k_AEB_VehErrorAccuPerdLat_str)
#define k_AEB_VehLongRangeChkEnbl    (LongSafe_Cal_DF_V.k_AEB_VehLongRangeChkEnbl_str)
#define k_AEB_VehLatRangeChkEnbl    (LongSafe_Cal_DF_V.k_AEB_VehLatRangeChkEnbl_str)
#define k_AEB_VehFusionMinAgeCount    (LongSafe_Cal_DF_V.k_AEB_VehFusionMinAgeCount_str)
#define k_AEB_VehMulTrklMinAgeCount    (LongSafe_Cal_DF_V.k_AEB_VehMulTrklMinAgeCount_str)
#define k_AEB_VehSingleTrkMinAgeCount    (LongSafe_Cal_DF_V.k_AEB_VehSingleTrkMinAgeCount_str)
#define k_AEB_VehVisionMinAgeCount    (LongSafe_Cal_DF_V.k_AEB_VehVisionMinAgeCount_str)
#define k_AEB_VehMinAgeCount    (LongSafe_Cal_DF_V.k_AEB_VehMinAgeCount_str)
#define k_AEB_VehDetStatus    (LongSafe_Cal_DF_V.k_AEB_VehDetStatus_str)
#define k_AEB_VehIgnoreDetProfile    (LongSafe_Cal_DF_V.k_AEB_VehIgnoreDetProfile_str)
#define k_AEB_VehIgnoreDetProfileLatPos    (LongSafe_Cal_DF_V.k_AEB_VehIgnoreDetProfileLatPos_str)
#define k_AEB_VehProfileChk_HdTm    (LongSafe_Cal_DF_V.k_AEB_VehProfileChk_HdTm_str)
#define k_AEB_VehRadarIDChk_HdTm    (LongSafe_Cal_DF_V.k_AEB_VehRadarIDChk_HdTm_str)
#define k_AEB_VehRadarIDChkRangeThres    (LongSafe_Cal_DF_V.k_AEB_VehRadarIDChkRangeThres_str)
#define k_AEB_VehRangeRate_BrkPoints    (LongSafe_Cal_DF_V.k_AEB_VehRangeRate_BrkPoints_str)
#define k_AEB_VehRadarIDChk    (LongSafe_Cal_DF_V.k_AEB_VehRadarIDChk_str)
#define k_AEB_VehRAIDChk_MinLongAccel    (LongSafe_Cal_DF_V.k_AEB_VehRAIDChk_MinLongAccel_str)
#define k_AEB_IgnoreAEBPedConfCheck    (LongSafe_Cal_DF_V.k_AEB_IgnoreAEBPedConfCheck_str)
#define k_AEB_IgnoreConfCheck    (LongSafe_Cal_DF_V.k_AEB_IgnoreConfCheck_str)
#define k_AEB_IgnoreInPathAgeCheck    (LongSafe_Cal_DF_V.k_AEB_IgnoreInPathAgeCheck_str)
#define k_AEB_IgnoreAebInhibit    (LongSafe_Cal_DF_V.k_AEB_IgnoreAebInhibit_str)
#define k_AEB_IgnoreAebFault    (LongSafe_Cal_DF_V.k_AEB_IgnoreAebFault_str)
#define k_AEB_Vehicle_Mass    (LongSafe_Cal_DF_V.k_AEB_Vehicle_Mass_str)
#define k_AEB_EPB_Present    (LongSafe_Cal_DF_V.k_AEB_EPB_Present_str)
#define k_AEB_EspRespTime    (LongSafe_Cal_DF_V.k_AEB_EspRespTime_str)
#define k_AEB_EspRespMaxJerk    (LongSafe_Cal_DF_V.k_AEB_EspRespMaxJerk_str)
#define k_AEB_ESPRespomseTime    (LongSafe_Cal_DF_V.k_AEB_ESPRespomseTime_str)
#define k_AEB_ESPTmSpdBrkPoints    (LongSafe_Cal_DF_V.k_AEB_ESPTmSpdBrkPoints_str)
#define k_AEB_ESPDecelDiffBrkPoints    (LongSafe_Cal_DF_V.k_AEB_ESPDecelDiffBrkPoints_str)
#define k_AEB_ESPDelayTime    (LongSafe_Cal_DF_V.k_AEB_ESPDelayTime_str)
#define k_AEB_UseOriginRangeCal    (LongSafe_Cal_DF_V.k_AEB_UseOriginRangeCal_str)
#define k_AEB_ESPRespTmHB2FB    (LongSafe_Cal_DF_V.k_AEB_ESPRespTmHB2FB_str)
#define k_AEB_ESPDeftResponseTime    (LongSafe_Cal_DF_V.k_AEB_ESPDeftResponseTime_str)
#define k_AEB_VRURlsMinXolc    (LongSafe_Cal_DF_V.k_AEB_VRURlsMinXolc_str)
#define k_AEB_VehIgnCstMask    (LongSafe_Cal_DF_V.k_AEB_VehIgnCstMask_str)
#define k_AEB_PedInterestChk    (LongSafe_Cal_DF_V.k_AEB_PedInterestChk_str)
#define k_AEB_VehHighestConf    (LongSafe_Cal_DF_V.k_AEB_VehHighestConf_str)
#define k_AEB_VehHiConf    (LongSafe_Cal_DF_V.k_AEB_VehHiConf_str)
#define k_AEB_GateTOIAngle_Arr    (LongSafe_Cal_DF_V.k_AEB_GateTOIAngle_Arr_str)
#define k_AEB_GateTOIPosi_x    (LongSafe_Cal_DF_V.k_AEB_GateTOIPosi_x_str)
#define k_Cal_LgSafe_minor_version    (LongSafe_Cal_DF_V.k_Cal_LgSafe_minor_version_str)
#define k_Cal_LgSafe_major_version    (LongSafe_Cal_DF_V.k_Cal_LgSafe_major_version_str)

#endif  /* _CAL_H */
