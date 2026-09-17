/****************************************************************************
 * Calibration file for AES_ESA production code.
 * DD uses version 5 of the bas file.
 * File Name: E:\user\AES_ESA_Module_0413_bak\AES_ESA_Module_0907\02_DataDictionary\AES\AES_ESA_cal.c
 * Created: 2026/9/14       10:59:36 
 * From Excel file: DataDictionary_AES_A02.xlsx
 * Calibration Values for project         
 * Calibrations for full application.
 * Set Description:         Initial Value
 *****************************************************************************/

#include "rtwtypes.h"
#include "AES_ESA_cal.h"


/*
 *  COMPONENT:  \AES_ESA
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


#define AES_ESA_START_SEC_CAL_UNSPECIFIED
#include "MemMap.h"

const AES_ESA_cal_T AES_ESA_Cal_DF_V = {

 /* k_AES_LaneWdth_filt_tau_str */   (uint16)   200 ,

 /* k_AES_minROC_acceptable_str */   (uint16)   500 ,

 /* k_AES_minROC_Hyst_str */   (uint16)   800 ,

 /* k_AES_NrOfNcssryFrames_str */   (uint8)   2 ,

 /* k_AES_NrOfNcssryIndcns_str */   (uint8)   2 ,

 /* k_AES_ObjDrvOffEnaFlg_str */   (boolean)   1 ,

 /* k_AES_SteerAgMdlEnaFlg_str */   (boolean)   1 ,

 /* k_AES_SysInitdLatCtrlEnaFlg_str */   (boolean)   1 ,

 /* k_AES_TRUE_str */   (boolean)   1 ,

 /* k_AES_UseMainSwtEnaFlg_str */   (boolean)   1 ,

 /* k_AES_UseLCKPIDController_str */   (boolean)   1 ,

 /* k_AES_UseVirtualData_str */   (boolean)   0 ,

 /* k_AES_mTot_str */   (float32)  1948.3F,

 /* k_AES_m_str */   (float32)  1637.2F,

 /* k_AES_DefaultTTC_str */   (float32)  20.0F,

 /* k_AES_ObjVirtX_str */   (float32)  50.0F,

 /* k_AES_SecondPlan_EndX_str */   (float32)  50.0F,

 /* k_AES_MaxDecelByAEB_str */   (float32)  -5.0F,

 /* k_AES_MaxDecelRearObj_str */   (float32)  -5.0F,

 /* k_AES_SteerWhlTqChgRateThd_str */   (float32)  30.0F,

 /* k_AES_EgoVDerivRateLim_str */   (float32)  20.0F,

 /* k_AES_ML_TIME_MSEC_str */   (float32)  20.0F,

 /* k_AES_Bx_str */   (float32)  19.0398F,

 /* k_AES_MaxCritLatAccThd_str */   (float32)  16.0F,

 /* k_AES_OvrallSteerRat_str */   (float32)  14.88F,

 /* k_AES_By_str */   (float32)  12.8885F,

 /* k_AES_Reset_EnTime_str */   (float32)  8.0F,

 /* k_AES_LLM_minRng_str */   (float32)  7.0F,

 /* k_AES_SteerWhlAgDzThd_str */   (float32)  50.0F,

 /* k_AES_CheckObsDistMinFront_str[ 16 ]*/   { (float32)50.0F, (float32)50.0F, (float32)50.0F, (float32)45.0F, (float32)40.0F, (float32)35.0F, (float32)30.0F, (float32)25.0F, (float32)20.0F, (float32)15.0F, (float32)15.0F, (float32)10.0F, (float32)10.0F, (float32)10.0F, (float32)10.0F, (float32)10.0F},

 /* k_AES_CheckObsDistMinRear_str[ 16 ]*/   { (float32)50.0F, (float32)50.0F, (float32)50.0F, (float32)45.0F, (float32)40.0F, (float32)35.0F, (float32)30.0F, (float32)25.0F, (float32)20.0F, (float32)15.0F, (float32)15.0F, (float32)10.0F, (float32)10.0F, (float32)10.0F, (float32)10.0F, (float32)10.0F},

 /* k_AES_EgoAOverGndObsvrL2_str */   (float32)  5.0F,

 /* k_AES_MaxLatAForPlanning_str */   (float32)  5.0F,

 /* k_AES_maxLnWdth_str */   (float32)  4.6F,

 /* k_AES_maxLnWdthHyst_str */   (float32)  4.5F,

 /* k_AES_maxSPPLnWdth_str */   (float32)  4.4F,

 /* k_AES_maxSPPLnWdthHyst_str */   (float32)  4.2F,

 /* k_AES_SteerWhlAgDifAbortThd_str */   (float32)  50.0F,

 /* k_AES_KntRiPosnY_str */   (float32)  -3.25F,

 /* k_AES_Jz_str */   (float32)  2480.8F,

 /* k_AES_KntLePosnX_str */   (float32)  500.0F,

 /* k_AES_KntRiPosnX_str */   (float32)  500.0F,

 /* k_AES_TorqueRate_Limit_str */   (float32)  200.0F,

 /* k_AES_IntvStrtMaxVelThd_str */   (float32)  36.1111F,

 /* k_AES_IntvAbrtLatAccThd_str */   (float32)  20.0F,

 /* k_AES_IntvStrtMinVelThd_str */   (float32)  3.0F,

 /* k_AES_KntLePosnY_str */   (float32)  3.25F,

 /* k_AES_Functional_Torque_Limit_str */   (float32)  3.0F,

 /* k_AES_MaxIntvDurnThd_str */   (float32)  15.0F,

 /* k_AES_ttcTresholdBeep_str */   (float32)  7.0F,

 /* k_AES_l_str */   (float32)  2.708F,

 /* k_AES_WhlBase_str */   (float32)  2.737F,

 /* k_AES_ttcPartialBrake_str */   (float32)  6.0F,

 /* k_AES_LLM_maxA0_str */   (float32)  2.8F,

 /* k_AES_minSPPLnWdth_str */   (float32)  2.7F,

 /* k_AES_minSPPLnWdthHyst_str */   (float32)  2.6F,

 /* k_AES_ttcTresholdLLCD_str */   (float32)  4.0F,

 /* k_AES_minLnWdth_str */   (float32)  2.2F,

 /* k_AES_IntvStrtLatAccThd_str */   (float32)  5.0F,

 /* k_AES_MaxLatADiffThd_str */   (float32)  2.0F,

 /* k_AES_MaxLongADiffThd_str */   (float32)  2.0F,

 /* k_AES_MinCritLatAccThd_str */   (float32)  1.5F,

 /* k_AES_ObjVirtWidth_str */   (float32)  2.0F,

 /* k_AES_SteerWhlTqThd_str */   (float32)  2.0F,

 /* k_AES_minLnWdthHyst_str */   (float32)  2.0F,

 /* k_AES_lh_str */   (float32)  1.6051F,

 /* k_AES_Cx_str */   (float32)  1.65F,

 /* k_AES_EgoWidth_str */   (float32)  1.8F,

 /* k_AES_ObjVirtY_str */   (float32)  -1.5F,

 /* k_AES_SteerWhlAgSpdThd_str */   (float32)  75.0F,

 /* k_AES_lv_str */   (float32)  1.1319F,

 /* k_AES_l_r_str */   (float32)  1.355F,

 /* k_AES_l_f_str */   (float32)  1.353F,

 /* k_AES_EgoAYMeanDevThd_str */   (float32)  1.5F,

 /* k_AES_LaneChangeFrontMinTTC_str */   (float32)  1.5F,

 /* k_AES_LaneChangeRearMinTTC_str */   (float32)  1.5F,

 /* k_AES_YPosDevThd_str */   (float32)  3.0F,

 /* k_AES_Cy_str */   (float32)  1.3F,

 /* k_AES_phiTraj_str */   (float32)  1.2F,

 /* k_AES_NotFsblCritVal_str */   (float32)  1.0001F,

 /* k_AES_EgoAOverGndObsvrL1_str */   (float32)  1.0F,

 /* k_AES_EgoVMinToActvt_str */   (float32)  1.0F,

 /* k_AES_EgoVMinToCncl_str */   (float32)  1.0F,

 /* k_AES_ObjVirtIdx_str */   (float32)  1.0F,

 /* k_AES_ObjVirtRlsEgoVThd_str */   (float32)  1.0F,

 /* k_AES_SftyDstLat_str */   (float32)  0.5F,

 /* k_AES_TiStbMin_str */   (float32)  1.0F,

 /* k_AES_TimeGapDistFrontWeight_str */   (float32)  1.0F,

 /* k_AES_TimeGapDistRearWeight_str */   (float32)  1.0F,

 /* k_AES_mue_str */   (float32)  1.0F,

 /* k_AES_y_str */   (float32)  1.0F,

 /* k_AES_iBreak_str */   (float32)  0.50037F,

 /* k_AES_SteerWhlAgMeanDeThd_str */   (float32)  30.0F,

 /* k_AES_h_str */   (float32)  0.5259F,

 /* k_AES_A1Diff_str */   (float32)  0.1F,

 /* k_AES_SysInitdSteerThd_str */   (float32)  0.12F,

 /* k_AES_LnCetr_SP_A1Init_hys_str */   (float32)  0.015F,

 /* k_AES_LatADiffLowDurnThd_str */   (float32)  0.5F,

 /* k_AES_LnCetr_SP_A0Init_str */   (float32)  0.5F,

 /* k_AES_LongADiffLowDurnThd_str */   (float32)  0.5F,

 /* k_AES_RearObsTimeGap_str */   (float32)  0.5F,

 /* k_AES_LatTolrSigm_str */   (float32)  0.05F,

 /* k_AES_EgoAXDiffRateLim_str */   (float32)  0.4F,

 /* k_AES_FrontObsTimeGap_str */   (float32)  0.4F,

 /* k_AES_UndrStrCoeff_str */   (float32)  0.004F,

 /* k_AES_LaneWdth_RateLmt_str */   (float32)  3.0F,

 /* k_AES_LnCetr_SP_A0Init_hys_str */   (float32)  0.3F,

 /* k_AES_P_alpha_str */   (float32)  0.3F,

 /* k_AES_lambdaMax_str */   (float32)  0.2F,

 /* k_AES_LnCetr_SP_A1Init_str */   (float32)  0.02F,

 /* k_AES_ML_TIME_SEC_str */   (float32)  0.02F,

 /* k_AES_A1Diff_CnclTime_str */   (float32)  0.1F,

 /* k_AES_A1Diff_EnTime_str */   (float32)  0.1F,

 /* k_AES_Conf_CanclTime_str */   (float32)  0.1F,

 /* k_AES_Conf_EnTime_str */   (float32)  0.1F,

 /* k_AES_LnCetr_DlyTmInit_str */   (float32)  0.1F,

 /* k_AES_LnWdth_EnTime_str */   (float32)  0.1F,

 /* k_AES_NxtLnWdth_filt_tau_str */   (float32)  0.1F,

 /* k_AES_ROC_CanclTime_str */   (float32)  0.1F,

 /* k_AES_ROC_EnTime_str */   (float32)  0.1F,

 /* k_AES_SPPLnWdth_CnclTime_str */   (float32)  0.1F,

 /* k_AES_SPPLnWdth_EnTime_str */   (float32)  0.1F,

 /* k_AES_P_y_str */   (float32)  0.01F,

 /* k_AES_SMALL_NUMBER_str */   (float32)  0.0001F,

 /* k_AES_ObjVirtAX_str */   (float32)  0.0F,

 /* k_AES_ObjVirtVX_str */   (float32)  0.0F,

 /* k_AES_Obs_l_hys_str */   (float32)  0.0F,

 /* k_AES_RearSecLaneLatArea_str */   (float32)  0.0F,

 /* k_AES_ZERO_str */   (float32)  0.0F,

 /* k_AES_Steering_Rate_Deadband_str[ 5 ]*/   { (float32)400.0F, (float32)400.0F, (float32)350.0F, (float32)300.0F, (float32)300.0F},

 /* k_AES_Damping_Torque_Gain_str[ 5 ]*/   { (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F},

 /* k_AES_Proportinal_Gain_str[ 5 ]*/   { (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)1.7F, (float32)1.7F},

 /* k_AES_AMatrixPredAES_str[ 2 ][ 2 ]*/   {
                            { (float32)1.0F, (float32)0.02F},
                            { (float32)0.0F, (float32)1.0F}},

 /* k_AES_Derivative_Gain_str[ 5 ]*/   { (float32)0.4F, (float32)0.4F, (float32)0.4F, (float32)0.4F, (float32)0.3F},

 /* k_AES_lambdaRange_str[ 61 ]*/   { (float32)-0.3F, (float32)-0.29F, (float32)-0.28F, (float32)-0.27F, (float32)-0.26F, (float32)-0.25F, (float32)-0.24F, (float32)-0.23F, (float32)-0.22F, (float32)-0.21F, (float32)-0.2F, (float32)-0.19F, (float32)-0.18F, (float32)-0.17F, (float32)-0.16F, (float32)-0.15F, (float32)-0.14F, (float32)-0.13F, (float32)-0.12F, (float32)-0.11F, (float32)-0.1F, (float32)-0.09F, (float32)-0.08F, (float32)-0.07F, (float32)-0.06F, (float32)-0.05F, (float32)-0.04F, (float32)-0.03F, (float32)-0.02F, (float32)-0.01F, (float32)0.0F, (float32)0.01F, (float32)0.02F, (float32)0.03F, (float32)0.04F, (float32)0.05F, (float32)0.06F, (float32)0.07F, (float32)0.08F, (float32)0.09F, (float32)0.1F, (float32)0.11F, (float32)0.12F, (float32)0.13F, (float32)0.14F, (float32)0.15F, (float32)0.16F, (float32)0.17F, (float32)0.18F, (float32)0.19F, (float32)0.2F, (float32)0.21F, (float32)0.22F, (float32)0.23F, (float32)0.24F, (float32)0.25F, (float32)0.26F, (float32)0.27F, (float32)0.28F, (float32)0.29F, (float32)0.3F},

 /* k_AES_Setpoint_BrkPs_str[ 11 ]*/   { (float32)0.017453F, (float32)0.034907F, (float32)0.087266F, (float32)0.17453F, (float32)0.5236F, (float32)1.0472F, (float32)1.5708F, (float32)2.0944F, (float32)3.1416F, (float32)6.2832F, (float32)9.4248F},

 /* k_AES_BMatrixPredAES_str[ 2 ][ 1 ]*/   {
                            { (float32)0.0002F},
                            { (float32)0.02F}},

 /* k_AES_v_map_str[ 5 ]*/   { (float32)0.0F, (float32)2.7778F, (float32)11.1111F, (float32)19.4444F, (float32)27.7778F},

 /* k_AES_Feedforward_Map_str[ 11 ][ 5 ]*/   {
                            { (float32)0.0F, (float32)0.0667F, (float32)0.1176F, (float32)0.12F, (float32)0.375F},
                            { (float32)0.0F, (float32)0.1333F, (float32)0.2353F, (float32)0.23F, (float32)0.75F},
                            { (float32)0.0F, (float32)0.3333F, (float32)0.5882F, (float32)0.6F, (float32)1.875F},
                            { (float32)0.0F, (float32)0.6667F, (float32)1.1765F, (float32)1.2F, (float32)3.2F},
                            { (float32)0.0F, (float32)2.0F, (float32)3.0763F, (float32)3.1F, (float32)4.375F},
                            { (float32)0.0F, (float32)3.2727F, (float32)3.5847F, (float32)3.6F, (float32)5.0F},
                            { (float32)0.0F, (float32)3.8182F, (float32)4.0F, (float32)5.0F, (float32)5.0F},
                            { (float32)0.0F, (float32)4.0F, (float32)4.0F, (float32)5.0F, (float32)4.4444F},
                            { (float32)0.0F, (float32)3.4286F, (float32)4.0F, (float32)3.75F, (float32)3.3333F},
                            { (float32)0.0F, (float32)1.7143F, (float32)2.0F, (float32)0.0F, (float32)0.0F},
                            { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F}},

 /* k_AES_Steering_Angle_Deadband_str[ 5 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_AES_accelerationFullBrake_str */   (float32)  -9.0F,

 /* k_AES_cAlphaR_str */   (float32)  65000.0F,

 /* k_AES_cAlphaF_str */   (float32)  50000.0F,

 /* k_AES_accelerationPartialBrake_str */   (float32)  -3.5F,

 /* k_AES_cLambdaF_str */   (float32)  130000.0F,

 /* k_AES_cLambdaR_str */   (float32)  130000.0F,

 /* k_AES_c_h_str */   (float32)  127960.0F,

 /* k_AES_c_v_str */   (float32)  117980.0F,

 /* k_AES_Ey_str */   (float32)  -1.8646F,

 /* k_AES_deltaT_phi_str */   (float32)  1.6F,

 /* k_AES_durationPartialBrake_str */   (float32)  1.0F,

 /* k_AES_Ex_str */   (float32)  0.96379F,

 /* k_AES_alphaMax_str */   (float32)  0.12217F,

 /* k_AES_curv_str */   (float32)  0.15F,

 /* k_AES_IntvStrtLatAccDurThd_str */   (float32)  0.5F,

 /* k_AES_evasionTimeOffs_str */   (float32)  0.5F,

 /* k_AES_IntvAbrtLatAccDurThd_str */   (float32)  0.1F,

 /* k_AES_LMType_CanclTime_str */   (float32)  0.1F,

 /* k_AES_LMType_EnTime_str */   (float32)  0.1F,

 /* k_AES_FrontSecLaneLatArea_str */   (float32)  0.0F,

 /* k_AES_KntLeCrvt_str */   (float32)  0.0F,

 /* k_AES_KntLeYawAg_str */   (float32)  0.0F,

 /* k_AES_KntRiCrvt_str */   (float32)  0.0F,

 /* k_AES_KntRiYawAg_str */   (float32)  0.0F,

 /* k_AES_cAlpha_str[ 13 ]*/   { (float32)20000.0F, (float32)25000.0F, (float32)30000.0F, (float32)35000.0F, (float32)40000.0F, (float32)45000.0F, (float32)50000.0F, (float32)55000.0F, (float32)60000.0F, (float32)65000.0F, (float32)70000.0F, (float32)75000.0F, (float32)80000.0F},

 /* k_AES_cLambda_str[ 27 ]*/   { (float32)20000.0F, (float32)25000.0F, (float32)30000.0F, (float32)35000.0F, (float32)40000.0F, (float32)45000.0F, (float32)50000.0F, (float32)55000.0F, (float32)60000.0F, (float32)65000.0F, (float32)70000.0F, (float32)75000.0F, (float32)80000.0F, (float32)85000.0F, (float32)90000.0F, (float32)95000.0F, (float32)100000.0F, (float32)105000.0F, (float32)110000.0F, (float32)115000.0F, (float32)120000.0F, (float32)125000.0F, (float32)130000.0F, (float32)135000.0F, (float32)140000.0F, (float32)145000.0F, (float32)150000.0F},

 /* k_AES_dfydalpha_str[ 13 ][ 1 ]*/   {
                            { (float32)4.1826F},
                            { (float32)5.2282F},
                            { (float32)6.2739F},
                            { (float32)7.3195F},
                            { (float32)8.3652F},
                            { (float32)9.4108F},
                            { (float32)10.4565F},
                            { (float32)11.5021F},
                            { (float32)12.5477F},
                            { (float32)13.5934F},
                            { (float32)14.639F},
                            { (float32)15.6847F},
                            { (float32)16.7303F}},

 /* k_AES_Integral_Gain_str[ 5 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_AES_LMConLo_str */   (sint16)  -50 ,

 /* k_AES_LMConfAccumuLmtHi_str */   (sint16)   300 ,

 /* k_AES_LMConHi_str */   (sint16)   50 ,

 /* k_AES_LMConfAccumuLmtLo_str */   (sint16)  -300 ,

 /* k_AES_BRKG_EMGY_BRKG_ALLWD_str */   (sint8)   3 ,

 /* k_AES_BRKG_PTL_BRKG_ALLWD_str */   (sint8)   2 ,

 /* k_AES_STEER_LAT_CTRL_ALLWD_str */   (sint8)   2 ,

 /* k_AES_BRKG_CNCL_INTV_str */   (sint8)  -1 ,

 /* k_AES_EVASN_DIR_RIGHT_str */   (sint8)  -1 ,

 /* k_AES_STEER_CNCL_INTV_str */   (sint8)  -1 ,

 /* k_AES_BRKG_WARN_ALLWD_str */   (sint8)   1 ,

 /* k_AES_EVASN_DIR_LEFT_str */   (sint8)   1 ,

 /* k_AES_STEER_WARN_ALLWD_str */   (sint8)   1 ,

 /* k_AES_BRKG_NO_INTV_STRT_ALLWD_str */   (sint8)   0 ,

 /* k_AES_EVASN_DIR_NONE_str */   (sint8)   0 ,

 /* k_AES_STEER_NO_INTV_STRT_ALLWD_str */   (sint8)   0 ,

 /* k_AES_FALSE_str */   (boolean)   0 ,

 /* k_AES_LgtCtrlrEnaFlg_str */   (boolean)   0 ,

 /* k_AES_ObjVirtRls_str */   (boolean)   0 ,

 /* k_AES_TestModVirtObjEnaFlg_str */   (boolean)   0 ,

 /* k_AES_UseSigmdPathEnaFlg_str */   (boolean)   0 ,

 /* k_AES_AEBTarDistance_str */   (float32)  50.0F,

 /* k_AES_UseVirtualAEB_str */   (boolean)   0 ,

 /* k_AES_UseCrticalTTC_str */   (uint8)   1 ,

 /* k_AES_FinishDureTimeThd_str */   (float32)  2.0F,

 /* k_AES_UseRawLatYLogic_str */   (boolean)   0 ,

 /* k_AES_UseRealObsLatY_str */   (boolean)   1 ,

 /* k_AES_PlnMaxAyWeight_str */   (float32)  10.0F,

 /* k_AES_ObsLatYWeight_str */   (float32)  100.0F,

 /* k_AES_VehLatYWeight_str */   (float32)  10.0F,

 /* k_AES_UseSecondPlanner_str */   (boolean)   0 ,

 /* k_AES_VirtualMainSwitch_str */   (boolean)   1 ,

 /* k_AES_FirstPlanEndXMinThrd_str */   (float32)  15.0F,

 /* k_AES_FirstCompltXThrd_str */   (float32)  0.0F,

 /* k_AES_UseNextNextLaneC0_str */   (boolean)   1 ,

 /* k_AES_DyErrorFilterCon_str */   (float32)  50.0F,

 /* k_AES_DyDotErrorFilterCon_str */   (float32)  50.0F,

 /* k_AES_HeadErrorFilterCon_str */   (float32)  50.0F,

 /* k_AES_HeadDotErrorFilterCon_str */   (float32)  50.0F,

 /* k_AES_PhiDotErrorFilterCon_str */   (float32)  50.0F,

 /* k_AES_FFCurveFilterCon_str */   (float32)  50.0F,

 /* k_AES_LatCtrl_PosPID_Kp_Near_str */   (float32)  2.2F,

 /* k_AES_LatCtrl_PosPID_Kp_Far_str */   (float32)  1.0F,

 /* k_AES_LatCtrl_PosPID_KI_str */   (float32)  0.5F,

 /* k_AES_LatCtrl_PosPID_Kd_Near_str */   (float32)  0.8F,

 /* k_AES_LatCtrl_PosPID_Kd_Far_str */   (float32)  0.8F,

 /* k_AES_LatCtrl_HeadPID_Kp_str */   (float32)  1.0F,

 /* k_AES_LatCtrl_HeadPID_Kd_str */   (float32)  1.6F,

 /* k_AES_RatLmtFac_TorqCmd_Vspd_str[ 16 ]*/   { (float32)400.0F, (float32)500.0F, (float32)500.0F, (float32)500.0F, (float32)500.0F, (float32)300.0F, (float32)250.0F, (float32)250.0F, (float32)200.0F, (float32)180.0F, (float32)150.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F, (float32)100.0F},

 /* k_AES_VspdBks_str[ 16 ]*/   { (float32)0.0F, (float32)3.0F, (float32)10.0F, (float32)20.0F, (float32)30.0F, (float32)40.0F, (float32)50.0F, (float32)60.0F, (float32)70.0F, (float32)80.0F, (float32)90.0F, (float32)100.0F, (float32)110.0F, (float32)120.0F, (float32)130.0F, (float32)140.0F},

 /* k_AES_VspdBks_OnCome_str[ 11 ]*/   { (float32)-240.0F, (float32)-200.0F, (float32)-160.0F, (float32)-140.0F, (float32)-120.0F, (float32)-100.0F, (float32)-80.0F, (float32)-60.0F, (float32)-40.0F, (float32)-20.0F, (float32)0.0F},

 /* k_AES_CtrlPredTime_str[ 16 ]*/   { (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.25F, (float32)0.2F, (float32)0.2F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F},

 /* k_AES_UseRealTimeEndPointY_str */   (boolean)   0 ,

 /* k_AES_UseRealTimeEndPointDY_str */   (boolean)   0 ,

 /* k_AES_UseRealTimeEndPointDDY_str */   (boolean)   0 ,

 /* k_AES_PathPredC2Thrd_str */   (float32)  0.0015F,

 /* k_AES_PathPred_Time_str */   (float32)  0.05F,

 /* k_AES_CtrlStartPredTime_str[ 16 ]*/   { (float32)0.15F, (float32)0.15F, (float32)0.15F, (float32)0.15F, (float32)0.15F, (float32)0.15F, (float32)0.15F, (float32)0.18F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F, (float32)0.05F},

 /* k_AES_AySatisfyOnDelayTime_str */   (float32)  0.06F,

 /* k_AES_TrajColl_DiscreteDist_str */   (float32)  0.5F,

 /* k_AES_ActiveMaxDyThr_str */   (float32)  0.45F,

 /* k_AES_EgoVehicle_HalfWidth_str */   (float32)  0.95F,

 /* k_AES_SafetyDistanceThr_str */   (float32)  0.28F,

 /* k_AES_FeedForward_CurveAxis_str[ 17 ]*/   { (float32)0.00001F, (float32)0.0002F, (float32)0.000333F, (float32)0.0005F, (float32)0.000667F, (float32)0.001F, (float32)0.00125F, (float32)0.001667F, (float32)0.002F, (float32)0.004F, (float32)0.005F, (float32)0.00875F, (float32)0.0125F, (float32)0.02F, (float32)0.04F, (float32)0.07F, (float32)0.1F},

 /* k_AES_FeedForward_SpdAxis_str[ 11 ]*/   { (float32)0.0F, (float32)10.0F, (float32)30.0F, (float32)50.0F, (float32)60.0F, (float32)70.0F, (float32)80.0F, (float32)90.0F, (float32)100.0F, (float32)110.0F, (float32)120.0F},

 /* k_AES_FeedForward_Coef_First_L_str[ 17 ][ 11 ]*/   {
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.6087F, (float32)1.2513F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)1.089F, (float32)0.99F, (float32)0.99F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.6087F, (float32)1.2513F, (float32)1.1005F, (float32)1.1005F, (float32)1.002F, (float32)1.1022F, (float32)0.95F, (float32)0.95F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.7548F, (float32)1.4915F, (float32)1.173F, (float32)1.173F, (float32)1.0679F, (float32)1.1747F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.7548F, (float32)1.5792F, (float32)1.242F, (float32)1.242F, (float32)1.1307F, (float32)1.2438F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.8582F, (float32)1.6669F, (float32)1.311F, (float32)1.1832F, (float32)1.0772F, (float32)1.1849F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.8582F, (float32)1.6669F, (float32)1.311F, (float32)1.1832F, (float32)1.0772F, (float32)1.1849F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.9614F, (float32)1.6669F, (float32)1.311F, (float32)1.1832F, (float32)1.0772F, (float32)1.1849F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.9614F, (float32)1.7547F, (float32)1.38F, (float32)1.2455F, (float32)1.1339F, (float32)1.2473F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.9614F, (float32)1.7547F, (float32)1.38F, (float32)1.2455F, (float32)1.1339F, (float32)1.2473F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)2.0646F, (float32)1.7547F, (float32)1.38F, (float32)1.2455F, (float32)1.1339F, (float32)1.2473F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)2.0646F, (float32)1.7547F, (float32)1.38F, (float32)1.2455F, (float32)1.1339F, (float32)1.2473F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.0F, (float32)0.99F, (float32)1.425F, (float32)2.0646F, (float32)1.7547F, (float32)1.6284F, (float32)1.4696F, (float32)1.338F, (float32)1.4718F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.05F, (float32)1.1F, (float32)1.47F, (float32)2.0646F, (float32)1.8345F, (float32)1.6284F, (float32)1.4696F, (float32)1.338F, (float32)1.4718F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.14F, (float32)1.2F, (float32)1.65F, (float32)2.1583F, (float32)1.8345F, (float32)1.6284F, (float32)1.4696F, (float32)1.338F, (float32)1.4718F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.8F, (float32)2.2147F, (float32)1.8823F, (float32)1.725F, (float32)1.5568F, (float32)1.4173F, (float32)1.559F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.8F, (float32)2.2147F, (float32)1.8823F, (float32)1.725F, (float32)1.5568F, (float32)1.4173F, (float32)1.559F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.8F, (float32)2.2147F, (float32)1.8823F, (float32)1.725F, (float32)1.5568F, (float32)1.4173F, (float32)1.559F, (float32)1.7F, (float32)1.8F}},

 /* k_AES_FeedForward_Coef_First_R_str[ 17 ][ 11 ]*/   {
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.6087F, (float32)1.2513F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)1.089F, (float32)0.99F, (float32)0.99F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.6087F, (float32)1.2513F, (float32)1.1005F, (float32)1.1005F, (float32)1.002F, (float32)1.1022F, (float32)0.95F, (float32)0.95F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.7548F, (float32)1.4915F, (float32)1.173F, (float32)1.173F, (float32)1.0679F, (float32)1.1747F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.7548F, (float32)1.5792F, (float32)1.242F, (float32)1.242F, (float32)1.1307F, (float32)1.2438F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.8582F, (float32)1.6669F, (float32)1.311F, (float32)1.1832F, (float32)1.0772F, (float32)1.1849F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.8582F, (float32)1.6669F, (float32)1.311F, (float32)1.1832F, (float32)1.0772F, (float32)1.1849F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.9614F, (float32)1.6669F, (float32)1.311F, (float32)1.1832F, (float32)1.0772F, (float32)1.1849F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.9614F, (float32)1.7547F, (float32)1.38F, (float32)1.2455F, (float32)1.1339F, (float32)1.2473F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)1.9614F, (float32)1.7547F, (float32)1.38F, (float32)1.2455F, (float32)1.1339F, (float32)1.2473F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)2.0646F, (float32)1.7547F, (float32)1.38F, (float32)1.2455F, (float32)1.1339F, (float32)1.2473F, (float32)1.7F, (float32)1.8F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.2F, (float32)2.0646F, (float32)1.7547F, (float32)1.38F, (float32)1.2455F, (float32)1.1339F, (float32)1.2473F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.0F, (float32)0.99F, (float32)1.425F, (float32)2.0646F, (float32)1.7547F, (float32)1.6284F, (float32)1.4696F, (float32)1.338F, (float32)1.4718F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.05F, (float32)1.1F, (float32)1.47F, (float32)2.0646F, (float32)1.8345F, (float32)1.6284F, (float32)1.4696F, (float32)1.338F, (float32)1.4718F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.14F, (float32)1.2F, (float32)1.65F, (float32)2.1583F, (float32)1.8345F, (float32)1.6284F, (float32)1.4696F, (float32)1.338F, (float32)1.4718F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.8F, (float32)2.2147F, (float32)1.8823F, (float32)1.725F, (float32)1.5568F, (float32)1.4173F, (float32)1.559F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.8F, (float32)2.2147F, (float32)1.8823F, (float32)1.725F, (float32)1.5568F, (float32)1.4173F, (float32)1.559F, (float32)1.7F, (float32)1.8F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.8F, (float32)2.2147F, (float32)1.8823F, (float32)1.725F, (float32)1.5568F, (float32)1.4173F, (float32)1.559F, (float32)1.7F, (float32)1.8F}},

 /* k_AES_FeedForward_Coef_Sec_L_str[ 17 ][ 11 ]*/   {
                            { (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F},
                            { (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.9171F, (float32)0.9171F, (float32)1.002F, (float32)1.002F, (float32)0.95F, (float32)0.95F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.85F, (float32)0.9775F, (float32)0.9775F, (float32)0.9775F, (float32)1.0679F, (float32)1.0679F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.85F, (float32)1.035F, (float32)1.035F, (float32)1.035F, (float32)1.1307F, (float32)1.1307F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.9F, (float32)1.0925F, (float32)1.0925F, (float32)0.986F, (float32)1.0772F, (float32)1.0772F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.9F, (float32)1.0925F, (float32)1.0925F, (float32)0.986F, (float32)1.0772F, (float32)1.0772F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.95F, (float32)1.0925F, (float32)1.0925F, (float32)0.986F, (float32)1.0772F, (float32)1.0772F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)0.95F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)0.95F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)1.0F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)1.0F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.0F, (float32)0.99F, (float32)0.95F, (float32)1.0F, (float32)1.265F, (float32)1.357F, (float32)1.2247F, (float32)1.338F, (float32)1.338F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.05F, (float32)1.1F, (float32)0.98F, (float32)1.0F, (float32)1.3225F, (float32)1.357F, (float32)1.2247F, (float32)1.338F, (float32)1.338F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.14F, (float32)1.2F, (float32)1.1F, (float32)1.15F, (float32)1.3225F, (float32)1.357F, (float32)1.2247F, (float32)1.338F, (float32)1.338F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.18F, (float32)1.357F, (float32)1.4375F, (float32)1.2973F, (float32)1.4173F, (float32)1.4173F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.18F, (float32)1.357F, (float32)1.4375F, (float32)1.2973F, (float32)1.4173F, (float32)1.4173F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.18F, (float32)1.357F, (float32)1.4375F, (float32)1.2973F, (float32)1.4173F, (float32)1.4173F, (float32)1.2F, (float32)1.4F}},

 /* k_AES_FeedForward_Coef_Sec_R_str[ 17 ][ 11 ]*/   {
                            { (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F},
                            { (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.9171F, (float32)0.9171F, (float32)1.002F, (float32)1.002F, (float32)0.95F, (float32)0.95F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.85F, (float32)0.9775F, (float32)0.9775F, (float32)0.9775F, (float32)1.0679F, (float32)1.0679F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.85F, (float32)1.035F, (float32)1.035F, (float32)1.035F, (float32)1.1307F, (float32)1.1307F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.9F, (float32)1.0925F, (float32)1.0925F, (float32)0.986F, (float32)1.0772F, (float32)1.0772F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.9F, (float32)1.0925F, (float32)1.0925F, (float32)0.986F, (float32)1.0772F, (float32)1.0772F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.95F, (float32)1.0925F, (float32)1.0925F, (float32)0.986F, (float32)1.0772F, (float32)1.0772F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)0.95F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)0.95F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)1.0F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)1.0F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.0F, (float32)0.99F, (float32)0.95F, (float32)1.0F, (float32)1.265F, (float32)1.357F, (float32)1.2247F, (float32)1.338F, (float32)1.338F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.05F, (float32)1.1F, (float32)0.98F, (float32)1.0F, (float32)1.3225F, (float32)1.357F, (float32)1.2247F, (float32)1.338F, (float32)1.338F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.14F, (float32)1.2F, (float32)1.1F, (float32)1.15F, (float32)1.3225F, (float32)1.357F, (float32)1.2247F, (float32)1.338F, (float32)1.338F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.18F, (float32)1.357F, (float32)1.4375F, (float32)1.2973F, (float32)1.4173F, (float32)1.4173F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.18F, (float32)1.357F, (float32)1.4375F, (float32)1.2973F, (float32)1.4173F, (float32)1.4173F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.18F, (float32)1.357F, (float32)1.4375F, (float32)1.2973F, (float32)1.4173F, (float32)1.4173F, (float32)1.2F, (float32)1.4F}},

 /* k_AES_RadBks_str[ 25 ]*/   { (float32)5.0F, (float32)10.0F, (float32)20.0F, (float32)30.0F, (float32)40.0F, (float32)50.0F, (float32)60.0F, (float32)70.0F, (float32)80.0F, (float32)90.0F, (float32)100.0F, (float32)150.0F, (float32)200.0F, (float32)300.0F, (float32)400.0F, (float32)500.0F, (float32)600.0F, (float32)700.0F, (float32)800.0F, (float32)900.0F, (float32)1000.0F, (float32)1500.0F, (float32)2000.0F, (float32)3000.0F, (float32)5000.0F},

 /* k_AES_Lat_PFac_Rad_str[ 25 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.5F, (float32)1.0F, (float32)1.5F, (float32)1.5F, (float32)1.5F, (float32)1.3F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_AES_Lat_IFac_Rad_str[ 25 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F},

 /* k_AES_Lat_DFac_Rad_str[ 25 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.5F, (float32)0.5F, (float32)1.0F, (float32)1.5F, (float32)1.5F, (float32)1.3F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_AES_Hed_PFac_Rad_str[ 25 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.5F, (float32)0.5F, (float32)1.0F, (float32)1.5F, (float32)1.5F, (float32)1.3F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_AES_Hed_DFac_Rad_str[ 25 ]*/   { (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.0F, (float32)0.5F, (float32)0.5F, (float32)1.0F, (float32)1.5F, (float32)1.5F, (float32)1.3F, (float32)1.0F, (float32)1.0F, (float32)1.0F},

 /* k_AES_DisableLeftTurning_str */   (boolean)   0 ,

 /* k_AES_DisableRightTurning_str */   (boolean)   0 ,

 /* k_AES_Dis_EgoRAxleToFBumper_str */   (float32)  3.9F,

 /* k_AES_EgoVehicle_Width_str */   (float32)  1.9F,

 /* k_AES_AverageTurnAccelMax_str */   (float32)  8.0F,

 /* k_AES_LastPntToStr_SafeDis_str */   (float32)  0.15F,

 /* k_AES_Obj_PredictedTime_str */   (float32)  0.0F,

 /* k_AES_CheckDriverAvoid_SafeDis_str */   (float32)  0.15F,

 /* k_AES_EnterEgoSpeed_MaxThr_str */   (float32)  135.0F,

 /* k_AES_EnterEgoSpeed_MinThr_str */   (float32)  50.0F,

 /* k_AES_ExitEgoSpeed_MaxThr_str */   (float32)  140.0F,

 /* k_AES_ExitEgoSpeed_MinThr_str */   (float32)  45.0F,

 /* k_AES_EnterEgoYawRate_Thr_str */   (float32)  0.2F,

 /* k_AES_ExitEgoYawRate_Thr_str */   (float32)  0.25F,

 /* k_AES_t_EnterEgoYawRate_OnDly_str */   (float32)  1.0F,

 /* k_AES_EnterEgoAy_Thr_str */   (float32)  2.5F,

 /* k_AES_t_EnterEgoAy_OnDly_str */   (float32)  1.0F,

 /* k_AES_ExitEgoAy_Thr_str */   (float32)  5.0F,

 /* k_AES_EnterEgoAccelPer_Thr_str */   (float32)  60.0F,

 /* k_AES_EnterEgoBrakePer_Thr_str */   (float32)  60.0F,

 /* k_AES_t_EnterPedalPer_OnDly_str */   (float32)  0.3F,

 /* k_AES_ExitEgoAccelPer_Thr_str */   (float32)  65.0F,

 /* k_AES_ExitEgoBrakePer_Thr_str */   (float32)  70.0F,

 /* k_AES_EnterStrAng_Thr_str */   (float32)  100.0F,

 /* k_AES_t_EnterStrAng_OnDly_str */   (float32)  0.2F,

 /* k_AES_ExitStrAng_Thr_str */   (float32)  120.0F,

 /* k_AES_t_ExitStrAng_OnDly_str */   (float32)  0.1F,

 /* k_AES_EnterTrajMaxAy_Thr_str */   (float32)  15.0F,

 /* k_AES_StateUseTrajMaxAyThr_str */   (boolean)   0 ,

 /* k_AES_EnterAES_HandTorq_Thr_str */   (float32)  1.5F,

 /* k_AES_EnterESA_HandTorq_Thr_str */   (float32)  2.0F,

 /* k_AES_t_DriverStrJudge_OnDly_str */   (float32)  0.04F,

 /* k_AES_AESAbortHTorq_SameDirThr_str */   (float32)  5.0F,

 /* k_AES_AESAbortHTorq_DiffDirThr_str */   (float32)  4.5F,

 /* k_AES_ESAAbortHTorq_SameDirThr_str */   (float32)  5.0F,

 /* k_AES_ESAAbortHTorq_DiffDirThr_str */   (float32)  4.5F,

 /* k_AES_AbortEgoAccelPer_Thr_str */   (float32)  70.0F,

 /* k_AES_AbortEgoBrakePer_Thr_str */   (float32)  25.0F,

 /* k_AES_AbortEgoYawRate_Thr_str */   (float32)  0.5F,

 /* k_AES_AbortEgoAy_Thr_str */   (float32)  10.0F,

 /* k_AES_AbortStrAng_Thr_str */   (float32)  175.0F,

 /* k_AES_t_AbortEgoAccelPer_OnDly_str */   (float32)  0.15F,

 /* k_AES_t_AbortEgoBrakePer_OnDly_str */   (float32)  0.06F,

 /* k_AES_t_AbortEgoYawRate_OnDly_str */   (float32)  0.25F,

 /* k_AES_t_AbortEgoAy_OnDly_str */   (float32)  0.25F,

 /* k_AES_t_AbortStrAng_OnDly_str */   (float32)  0.0F,

 /* k_AES_t_AbortHandTorq_OnDly_str */   (float32)  0.25F,

 /* k_AES_t_AbortESCActive_OnDly_str */   (float32)  1.5F,

 /* k_AES_CompletedC0_Thr_str */   (float32)  0.2F,

 /* k_AES_CompletedC1_Thr_str */   (float32)  0.02F,

 /* k_AES_t_CompletedC0C1_OnDly_str */   (float32)  3.0F,

 /* k_AES_t_DriverAvoidObj_OnDly_str */   (float32)  3.0F,

 /* k_AES_AngLimitMax_Vspd_str[ 16 ]*/   { (float32)450.0F, (float32)450.0F, (float32)450.0F, (float32)380.0F, (float32)250.0F, (float32)82.5F, (float32)80.0F, (float32)80.0F, (float32)80.0F, (float32)70.0F, (float32)70.0F, (float32)60.0F, (float32)40.0F, (float32)40.0F, (float32)40.0F, (float32)40.0F},

 /* k_AES_Lat_KpKdSlopeLmt_str */   (float32)  8.0F,

 /* k_AES_Hed_KpKdSlopeLmt_str */   (float32)  5.0F,

 /* k_AES_t_FCWObstacleValid_OnDly_str */   (float32)  0.04F,

 /* k_AES_CsderEgoLen2PlanEndX_str */   (boolean)   1 ,

 /* k_AES_DefaultPassLaneLineCheck_str */   (boolean)   0 ,

 /* k_AES_DefaultPassObstacleCheck_str */   (boolean)   0 ,

 /* k_AES_StrWhlAngFilterCon_str */   (float32)  20.0F,

 /* k_AES_useFeedbackFirstPln_str */   (boolean)   0 ,

 /* k_AES_EnterEgoSpeed_MaxThr_VRU_str */   (float32)  135.0F,

 /* k_AES_EnterEgoSpeed_MinThr_VRU_str */   (float32)  50.0F,

 /* k_AES_ExitEgoSpeed_MaxThr_VRU_str */   (float32)  140.0F,

 /* k_AES_ExitEgoSpeed_MinThr_VRU_str */   (float32)  45.0F,

 /* k_AES_FeedForward_Coef_Second_str[ 17 ][ 11 ]*/   {
                            { (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F},
                            { (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.9171F, (float32)0.9171F, (float32)1.002F, (float32)1.002F, (float32)0.95F, (float32)0.95F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.85F, (float32)0.9775F, (float32)0.9775F, (float32)0.9775F, (float32)1.0679F, (float32)1.0679F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.85F, (float32)1.035F, (float32)1.035F, (float32)1.035F, (float32)1.1307F, (float32)1.1307F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.9F, (float32)1.0925F, (float32)1.0925F, (float32)0.986F, (float32)1.0772F, (float32)1.0772F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.9F, (float32)1.0925F, (float32)1.0925F, (float32)0.986F, (float32)1.0772F, (float32)1.0772F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.95F, (float32)1.0925F, (float32)1.0925F, (float32)0.986F, (float32)1.0772F, (float32)1.0772F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)0.95F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)0.95F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)1.0F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)1.0F, (float32)1.15F, (float32)1.15F, (float32)1.0379F, (float32)1.1339F, (float32)1.1339F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.0F, (float32)0.99F, (float32)0.95F, (float32)1.0F, (float32)1.265F, (float32)1.357F, (float32)1.2247F, (float32)1.338F, (float32)1.338F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.05F, (float32)1.1F, (float32)0.98F, (float32)1.0F, (float32)1.3225F, (float32)1.357F, (float32)1.2247F, (float32)1.338F, (float32)1.338F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.14F, (float32)1.2F, (float32)1.1F, (float32)1.15F, (float32)1.3225F, (float32)1.357F, (float32)1.2247F, (float32)1.338F, (float32)1.338F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.18F, (float32)1.357F, (float32)1.4375F, (float32)1.2973F, (float32)1.4173F, (float32)1.4173F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.18F, (float32)1.357F, (float32)1.4375F, (float32)1.2973F, (float32)1.4173F, (float32)1.4173F, (float32)1.2F, (float32)1.4F},
                            { (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.18F, (float32)1.357F, (float32)1.4375F, (float32)1.2973F, (float32)1.4173F, (float32)1.4173F, (float32)1.2F, (float32)1.4F}},

 /* k_AES_FeedForwardGain_SlopeLmt_str */   (float32)  0.5F,

 /* k_AES_AEBObjUseISOcoordinate_str */   (sint8)   1 ,

 /* k_AES_t_DriverQuickStr_OffDly_str */   (float32)  3.0F,

 /* k_AES_HostLaneObsOffset_str */   (float32)  5.0F,

 /* k_AES_FeedForward_First_ESA_L_str[ 17 ][ 11 ]*/   {
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F}},

 /* k_AES_FeedForward_First_ESA_R_str[ 17 ][ 11 ]*/   {
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.9171F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.9775F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)1.035F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.986F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.986F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.986F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F},
                            { (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)0.6F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F}},

 /* k_AES_FeedForward_Sec_ESA_L_str[ 17 ][ 11 ]*/   {
                            { (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)1.089F, (float32)1.188F, (float32)1.188F, (float32)1.188F, (float32)1.188F, (float32)1.188F},
                            { (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)1.0088F, (float32)1.1005F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.85F, (float32)0.9775F, (float32)1.0753F, (float32)1.173F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.85F, (float32)1.0F, (float32)1.1F, (float32)1.242F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.9F, (float32)1.0F, (float32)1.1F, (float32)1.1832F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.9F, (float32)1.0F, (float32)1.1F, (float32)1.1832F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.95F, (float32)1.0F, (float32)1.1F, (float32)1.1832F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)0.95F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)0.95F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)0.99F, (float32)0.95F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)1.0F, (float32)0.98F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F}},

 /* k_AES_FeedForward_Sec_ESA_R_str[ 17 ][ 11 ]*/   {
                            { (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)1.089F, (float32)1.188F, (float32)1.188F, (float32)1.188F, (float32)1.188F, (float32)1.188F},
                            { (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)0.99F, (float32)1.0088F, (float32)1.1005F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.85F, (float32)0.9775F, (float32)1.0753F, (float32)1.173F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.85F, (float32)1.0F, (float32)1.1F, (float32)1.242F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.9F, (float32)1.0F, (float32)1.1F, (float32)1.1832F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.9F, (float32)1.0F, (float32)1.1F, (float32)1.1832F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.08F, (float32)0.95F, (float32)1.0F, (float32)1.1F, (float32)1.1832F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)0.95F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)0.95F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)0.99F, (float32)0.99F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)0.99F, (float32)0.95F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)1.0F, (float32)0.98F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F},
                            { (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.0F, (float32)1.1F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F}},

 /* k_AES_t_TTCValid_OnDly_str */   (float32)  0.04F,

 /* k_AES_EnableAllTypeForAES_str */   (boolean)   0 ,

 /* k_AES_PlanAddDist_Static_str[ 16 ]*/   { (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F},

 /* k_AES_PlanAddDist_SlowSpd_str[ 16 ]*/   { (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)8.0F, (float32)8.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F, (float32)5.0F},

 /* k_AES_PlanAddDist_OnCome_str[ 11 ]*/   { (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F},

 /* k_AES_LastPntBrk_TTC_OC_str[ 16 ]*/   { (float32)1.4F, (float32)1.4F, (float32)1.4F, (float32)1.4F, (float32)1.4F, (float32)1.4F, (float32)1.4F, (float32)1.4F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F},

 /* k_AES_LastPntBrk_TTC_OC_ESA_str[ 16 ]*/   { (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F, (float32)2.0F},

 /* k_AES_MaxBrakeDecelProtect_str[ 16 ]*/   { (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.2F, (float32)1.25F, (float32)1.25F, (float32)1.25F, (float32)1.4F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F, (float32)1.8F},

 /* k_AES_MaxBrakeDecelProtect_ESA_str[ 16 ]*/   { (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.6F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)1.7F, (float32)2.2F, (float32)2.2F, (float32)2.2F, (float32)2.2F, (float32)2.2F, (float32)2.2F},

 /* k_AES_FCWObsSlowSpd_OnDly_str */   (float32)  0.5F,

 /* k_AES_MaxBrakeDecelThr_str[ 16 ]*/   { (float32)-2.0F, (float32)-2.0F, (float32)-2.0F, (float32)-2.0F, (float32)-2.0F, (float32)-4.0F, (float32)-4.0F, (float32)-4.0F, (float32)-6.5F, (float32)-8.0F, (float32)-8.5F, (float32)-9.0F, (float32)-10.0F, (float32)-12.0F, (float32)-12.0F, (float32)-12.0F},

 /* k_AES_MaxBrakeDecelThr_ESA_str[ 16 ]*/   { (float32)-3.0F, (float32)-3.0F, (float32)-3.0F, (float32)-3.0F, (float32)-3.0F, (float32)-3.0F, (float32)-3.0F, (float32)-3.0F, (float32)-4.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F, (float32)-5.0F},

 /* k_AES_MaxBrkDeThr_SlowSpd_str[ 16 ]*/   { (float32)-2.0F, (float32)-2.0F, (float32)-2.0F, (float32)-2.0F, (float32)-2.0F, (float32)-4.0F, (float32)-4.5F, (float32)-5.0F, (float32)-7.0F, (float32)-7.5F, (float32)-8.0F, (float32)-8.5F, (float32)-9.5F, (float32)-10.0F, (float32)-10.0F, (float32)-10.0F},

 /* k_AES_LeftLongSafeDistance_str */   (float32)  1.0F,

 /* k_AES_RightLongSafeDistance_str */   (float32)  1.0F,

 /* k_AES_t_ActiveMaxTimeThr_str[ 16 ]*/   { (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)4.5F, (float32)4.5F, (float32)4.5F, (float32)4.5F, (float32)4.5F},

 /* k_AES_ObjFilterLonMaxTTC_str */   (float32)  4.0F,

 /* k_AES_DriverStrJudge_AngSpdThr_str[ 16 ]*/   { (float32)30.0F, (float32)30.0F, (float32)30.0F, (float32)30.0F, (float32)30.0F, (float32)30.0F, (float32)30.0F, (float32)30.0F, (float32)30.0F, (float32)30.0F, (float32)20.0F, (float32)15.0F, (float32)10.0F, (float32)10.0F, (float32)10.0F, (float32)10.0F},

 /* k_AES_DriverStrJudge_AngThr_str[ 16 ]*/   { (float32)8.0F, (float32)8.0F, (float32)8.0F, (float32)8.0F, (float32)8.0F, (float32)8.0F, (float32)8.0F, (float32)8.0F, (float32)8.0F, (float32)8.0F, (float32)8.0F, (float32)6.0F, (float32)6.0F, (float32)6.0F, (float32)5.0F, (float32)5.0F},

 /* k_AES_ObjOverLapLatThrsd_str */   (float32)  1.5F,

 /* k_AES_DisableESAObj_str */   (boolean)   1 ,

 /* k_AES_FCWObstacleLatOverLap_str */   (float32)  2.5F,

 /* k_AES_FCWObstacleLatVel_str */   (float32)  0.3F,

 /* k_AES_RoadEdgeValid_MaxThd_str */   (float32)  15.0F,

 /* k_AES_RoadEdgeValid_MinThd_str */   (float32)  5.0F,

 /* k_AES_NoLaneLine_LatMoveThd_str */   (float32)  3.0F,

 /* k_AES_NoLaneLine_Flag_str */   (uint8)   0 ,

 /* k_AES_CTL_heading_spd_str[ 10 ]*/   { (float32)40.0F, (float32)50.0F, (float32)60.0F, (float32)70.0F, (float32)80.0F, (float32)90.0F, (float32)100.0F, (float32)110.0F, (float32)120.0F, (float32)130.0F},

 /* k_AES_CTL_heading_error_factor_str[ 10 ]*/   { (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F, (float32)0.2F},

 /* k_AES_FCWObstacleLatOverLap_AES_str */   (float32)  1.8F,

};
#define AES_ESA_STOP_SEC_CAL_UNSPECIFIED
#include "MemMap.h"
/*
*| aes_esa_cal.AES_ESA_Cal_DF_V {
*|  :is_calconst;
*|  .k_AES_LaneWdth_filt_tau_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AES_minROC_acceptable_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AES_minROC_Hyst_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint16_0_10000_CT;
*|  }
*|  .k_AES_NrOfNcssryFrames_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_AES_NrOfNcssryIndcns_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_10_CT;
*|  }
*|  .k_AES_ObjDrvOffEnaFlg_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_SteerAgMdlEnaFlg_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_SysInitdLatCtrlEnaFlg_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_TRUE_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_UseMainSwtEnaFlg_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_UseLCKPIDController_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_UseVirtualData_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_mTot_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_m_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_DefaultTTC_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_20000_CT;
*|  }
*|  .k_AES_ObjVirtX_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_SecondPlan_EndX_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_MaxDecelByAEB_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m100_100_CT;
*|  }
*|  .k_AES_MaxDecelRearObj_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m100_100_CT;
*|  }
*|  .k_AES_SteerWhlTqChgRateThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_EgoVDerivRateLim_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_ML_TIME_MSEC_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_Bx_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_MaxCritLatAccThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_OvrallSteerRat_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_By_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_Reset_EnTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_LLM_minRng_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_SteerWhlAgDzThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_500_CT;
*|  }
*|  .k_AES_CheckObsDistMinFront_str {
*|  :description = "AES_ESA_cal.k_AES_CheckObsDistMinFront";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_CheckObsDistMinRear_str {
*|  :description = "AES_ESA_cal.k_AES_CheckObsDistMinRear";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_EgoAOverGndObsvrL2_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_MaxLatAForPlanning_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_maxLnWdth_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_maxLnWdthHyst_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_maxSPPLnWdth_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_maxSPPLnWdthHyst_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_SteerWhlAgDifAbortThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_500_CT;
*|  }
*|  .k_AES_KntRiPosnY_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AES_Jz_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_KntLePosnX_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_KntRiPosnX_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_TorqueRate_Limit_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_IntvStrtMaxVelThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AES_IntvAbrtLatAccThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AES_IntvStrtMinVelThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_KntLePosnY_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_Functional_Torque_Limit_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_MaxIntvDurnThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_ttcTresholdBeep_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_l_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_WhlBase_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ttcPartialBrake_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_LLM_maxA0_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_minSPPLnWdth_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_minSPPLnWdthHyst_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ttcTresholdLLCD_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_minLnWdth_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_IntvStrtLatAccThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_20_CT;
*|  }
*|  .k_AES_MaxLatADiffThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_20_CT;
*|  }
*|  .k_AES_MaxLongADiffThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_20_CT;
*|  }
*|  .k_AES_MinCritLatAccThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_20_CT;
*|  }
*|  .k_AES_ObjVirtWidth_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_20_CT;
*|  }
*|  .k_AES_SteerWhlTqThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_20_CT;
*|  }
*|  .k_AES_minLnWdthHyst_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_20_CT;
*|  }
*|  .k_AES_lh_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_Cx_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_EgoWidth_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ObjVirtY_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AES_SteerWhlAgSpdThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_lv_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_l_r_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_l_f_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_EgoAYMeanDevThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LaneChangeFrontMinTTC_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LaneChangeRearMinTTC_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_YPosDevThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_Cy_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_phiTraj_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_NotFsblCritVal_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_EgoAOverGndObsvrL1_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_EgoVMinToActvt_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_EgoVMinToCncl_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ObjVirtIdx_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ObjVirtRlsEgoVThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_SftyDstLat_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_TiStbMin_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_TimeGapDistFrontWeight_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_TimeGapDistRearWeight_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_mue_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_y_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_iBreak_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_SteerWhlAgMeanDeThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_h_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_A1Diff_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_SysInitdSteerThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LnCetr_SP_A1Init_hys_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LatADiffLowDurnThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LnCetr_SP_A0Init_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LongADiffLowDurnThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_RearObsTimeGap_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LatTolrSigm_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_EgoAXDiffRateLim_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_FrontObsTimeGap_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_UndrStrCoeff_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LaneWdth_RateLmt_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LnCetr_SP_A0Init_hys_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_P_alpha_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_lambdaMax_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LnCetr_SP_A1Init_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ML_TIME_SEC_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_A1Diff_CnclTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_A1Diff_EnTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_Conf_CanclTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_Conf_EnTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LnCetr_DlyTmInit_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LnWdth_EnTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_NxtLnWdth_filt_tau_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ROC_CanclTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ROC_EnTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_SPPLnWdth_CnclTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_SPPLnWdth_EnTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_P_y_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_SMALL_NUMBER_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ObjVirtAX_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ObjVirtVX_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_Obs_l_hys_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_RearSecLaneLatArea_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ZERO_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_Steering_Rate_Deadband_str {
*|  :description = "AES_ESA_cal.k_AES_Steering_Rate_Deadband";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_Damping_Torque_Gain_str {
*|  :description = "AES_ESA_cal.k_AES_Damping_Torque_Gain";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_Proportinal_Gain_str {
*|  :description = "AES_ESA_cal.k_AES_Proportinal_Gain";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_AMatrixPredAES_str {
*|  :description = "AES_ESA_cal.k_AES_AMatrixPredAES";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_Derivative_Gain_str {
*|  :description = "AES_ESA_cal.k_AES_Derivative_Gain";
*|  :units = "";
*|  :type = caltype.single_m10_100_CT;
*|  }
*|  .k_AES_lambdaRange_str {
*|  :description = "AES_ESA_cal.k_AES_lambdaRange";
*|  :units = "";
*|  :type = caltype.single_m10_100_CT;
*|  }
*|  .k_AES_Setpoint_BrkPs_str {
*|  :description = "AES_ESA_cal.k_AES_Setpoint_BrkPs";
*|  :units = "";
*|  :type = caltype.single_m10_100_CT;
*|  }
*|  .k_AES_BMatrixPredAES_str {
*|  :description = "AES_ESA_cal.k_AES_BMatrixPredAES";
*|  :units = "";
*|  :type = caltype.single_m10_100_CT;
*|  }
*|  .k_AES_v_map_str {
*|  :description = "AES_ESA_cal.k_AES_v_map";
*|  :units = "";
*|  :type = caltype.single_m10_100_CT;
*|  }
*|  .k_AES_Feedforward_Map_str {
*|  :description = "AES_ESA_cal.k_AES_Feedforward_Map";
*|  :units = "";
*|  :type = caltype.single_m10_100_CT;
*|  }
*|  .k_AES_Steering_Angle_Deadband_str {
*|  :description = "AES_ESA_cal.k_AES_Steering_Angle_Deadband";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_accelerationFullBrake_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m100_10_CT;
*|  }
*|  .k_AES_cAlphaR_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100000_CT;
*|  }
*|  .k_AES_cAlphaF_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100000_CT;
*|  }
*|  .k_AES_accelerationPartialBrake_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AES_cLambdaF_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_200000_CT;
*|  }
*|  .k_AES_cLambdaR_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_200000_CT;
*|  }
*|  .k_AES_c_h_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_200000_CT;
*|  }
*|  .k_AES_c_v_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_200000_CT;
*|  }
*|  .k_AES_Ey_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AES_deltaT_phi_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_durationPartialBrake_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_Ex_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_alphaMax_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_curv_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_IntvStrtLatAccDurThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_evasionTimeOffs_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_IntvAbrtLatAccDurThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LMType_CanclTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LMType_EnTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_FrontSecLaneLatArea_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_KntLeCrvt_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_KntLeYawAg_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_KntRiCrvt_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_KntRiYawAg_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_cAlpha_str {
*|  :description = "AES_ESA_cal.k_AES_cAlpha";
*|  :units = "";
*|  :type = caltype.single_0_200000_CT;
*|  }
*|  .k_AES_cLambda_str {
*|  :description = "AES_ESA_cal.k_AES_cLambda";
*|  :units = "";
*|  :type = caltype.single_0_200000_CT;
*|  }
*|  .k_AES_dfydalpha_str {
*|  :description = "AES_ESA_cal.k_AES_dfydalpha";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_Integral_Gain_str {
*|  :description = "AES_ESA_cal.k_AES_Integral_Gain";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_LMConLo_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int16_m100_100_CT;
*|  }
*|  .k_AES_LMConfAccumuLmtHi_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int16_0_1000_CT;
*|  }
*|  .k_AES_LMConHi_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int16_0_1000_CT;
*|  }
*|  .k_AES_LMConfAccumuLmtLo_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int16_m1000_1000_CT;
*|  }
*|  .k_AES_BRKG_EMGY_BRKG_ALLWD_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_0_10_CT;
*|  }
*|  .k_AES_BRKG_PTL_BRKG_ALLWD_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_0_10_CT;
*|  }
*|  .k_AES_STEER_LAT_CTRL_ALLWD_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_0_10_CT;
*|  }
*|  .k_AES_BRKG_CNCL_INTV_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_m10_10_CT;
*|  }
*|  .k_AES_EVASN_DIR_RIGHT_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_m10_10_CT;
*|  }
*|  .k_AES_STEER_CNCL_INTV_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_m10_10_CT;
*|  }
*|  .k_AES_BRKG_WARN_ALLWD_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_0_10_CT;
*|  }
*|  .k_AES_EVASN_DIR_LEFT_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_0_10_CT;
*|  }
*|  .k_AES_STEER_WARN_ALLWD_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_0_10_CT;
*|  }
*|  .k_AES_BRKG_NO_INTV_STRT_ALLWD_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_0_10_CT;
*|  }
*|  .k_AES_EVASN_DIR_NONE_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_0_10_CT;
*|  }
*|  .k_AES_STEER_NO_INTV_STRT_ALLWD_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_0_1_CT;
*|  }
*|  .k_AES_FALSE_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_LgtCtrlrEnaFlg_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_ObjVirtRls_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_TestModVirtObjEnaFlg_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_UseSigmdPathEnaFlg_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_AEBTarDistance_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_UseVirtualAEB_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_UseCrticalTTC_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_250_CT;
*|  }
*|  .k_AES_FinishDureTimeThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_UseRawLatYLogic_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_UseRealObsLatY_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_PlnMaxAyWeight_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_ObsLatYWeight_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_VehLatYWeight_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_UseSecondPlanner_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_VirtualMainSwitch_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_FirstPlanEndXMinThrd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_FirstCompltXThrd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_UseNextNextLaneC0_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_DyErrorFilterCon_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_DyDotErrorFilterCon_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_HeadErrorFilterCon_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_HeadDotErrorFilterCon_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_PhiDotErrorFilterCon_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_FFCurveFilterCon_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_LatCtrl_PosPID_Kp_Near_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_LatCtrl_PosPID_Kp_Far_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_LatCtrl_PosPID_KI_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_LatCtrl_PosPID_Kd_Near_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_LatCtrl_PosPID_Kd_Far_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_LatCtrl_HeadPID_Kp_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_LatCtrl_HeadPID_Kd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_RatLmtFac_TorqCmd_Vspd_str {
*|  :description = "AES_ESA_cal.k_AES_RatLmtFac_TorqCmd_Vspd";
*|  :units = "";
*|  :type = caltype.single_0_600_CT;
*|  }
*|  .k_AES_VspdBks_str {
*|  :description = "AES_ESA_cal.k_AES_VspdBks";
*|  :units = "";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AES_VspdBks_OnCome_str {
*|  :description = "AES_ESA_cal.k_AES_VspdBks_OnCome";
*|  :units = "";
*|  :type = caltype.single_m300_300_CT;
*|  }
*|  .k_AES_CtrlPredTime_str {
*|  :description = "AES_ESA_cal.k_AES_CtrlPredTime";
*|  :units = "";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AES_UseRealTimeEndPointY_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_UseRealTimeEndPointDY_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_UseRealTimeEndPointDDY_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_PathPredC2Thrd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AES_PathPred_Time_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_CtrlStartPredTime_str {
*|  :description = "AES_ESA_cal.k_AES_CtrlStartPredTime";
*|  :units = "";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AES_AySatisfyOnDelayTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_TrajColl_DiscreteDist_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AES_ActiveMaxDyThr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_EgoVehicle_HalfWidth_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_SafetyDistanceThr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_FeedForward_CurveAxis_str {
*|  :description = "AES_ESA_cal.k_AES_FeedForward_CurveAxis";
*|  :units = "N";
*|  :type = caltype.single_0_100000_CT;
*|  }
*|  .k_AES_FeedForward_SpdAxis_str {
*|  :description = "AES_ESA_cal.k_AES_FeedForward_SpdAxis";
*|  :units = "N";
*|  :type = caltype.single_m1_10000_CT;
*|  }
*|  .k_AES_FeedForward_Coef_First_L_str {
*|  :description = "AES_ESA_cal.k_AES_FeedForward_Coef_First_L";
*|  :units = "N";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_FeedForward_Coef_First_R_str {
*|  :description = "AES_ESA_cal.k_AES_FeedForward_Coef_First_R";
*|  :units = "N";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_FeedForward_Coef_Sec_L_str {
*|  :description = "AES_ESA_cal.k_AES_FeedForward_Coef_Sec_L";
*|  :units = "N";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_FeedForward_Coef_Sec_R_str {
*|  :description = "AES_ESA_cal.k_AES_FeedForward_Coef_Sec_R";
*|  :units = "N";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_RadBks_str {
*|  :description = "AES_ESA_cal.k_AES_RadBks";
*|  :units = "";
*|  :type = caltype.single_0_20000_CT;
*|  }
*|  .k_AES_Lat_PFac_Rad_str {
*|  :description = "AES_ESA_cal.k_AES_Lat_PFac_Rad";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_Lat_IFac_Rad_str {
*|  :description = "AES_ESA_cal.k_AES_Lat_IFac_Rad";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_Lat_DFac_Rad_str {
*|  :description = "AES_ESA_cal.k_AES_Lat_DFac_Rad";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_Hed_PFac_Rad_str {
*|  :description = "AES_ESA_cal.k_AES_Hed_PFac_Rad";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_Hed_DFac_Rad_str {
*|  :description = "AES_ESA_cal.k_AES_Hed_DFac_Rad";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_DisableLeftTurning_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_DisableRightTurning_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_Dis_EgoRAxleToFBumper_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_EgoVehicle_Width_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_AverageTurnAccelMax_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m20_20_CT;
*|  }
*|  .k_AES_LastPntToStr_SafeDis_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m20_20_CT;
*|  }
*|  .k_AES_Obj_PredictedTime_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m20_20_CT;
*|  }
*|  .k_AES_CheckDriverAvoid_SafeDis_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m20_20_CT;
*|  }
*|  .k_AES_EnterEgoSpeed_MaxThr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_EnterEgoSpeed_MinThr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_ExitEgoSpeed_MaxThr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_ExitEgoSpeed_MinThr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_EnterEgoYawRate_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_ExitEgoYawRate_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_t_EnterEgoYawRate_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_EnterEgoAy_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_t_EnterEgoAy_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_ExitEgoAy_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_EnterEgoAccelPer_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_EnterEgoBrakePer_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_t_EnterPedalPer_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_ExitEgoAccelPer_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_ExitEgoBrakePer_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_EnterStrAng_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_t_EnterStrAng_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_ExitStrAng_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_t_ExitStrAng_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_EnterTrajMaxAy_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_StateUseTrajMaxAyThr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_EnterAES_HandTorq_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_EnterESA_HandTorq_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_t_DriverStrJudge_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_AESAbortHTorq_SameDirThr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_AESAbortHTorq_DiffDirThr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_ESAAbortHTorq_SameDirThr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_ESAAbortHTorq_DiffDirThr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_AbortEgoAccelPer_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_AbortEgoBrakePer_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_AbortEgoYawRate_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_AbortEgoAy_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_AbortStrAng_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_t_AbortEgoAccelPer_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_t_AbortEgoBrakePer_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_t_AbortEgoYawRate_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_t_AbortEgoAy_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_t_AbortStrAng_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_t_AbortHandTorq_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_t_AbortESCActive_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_CompletedC0_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_CompletedC1_Thr_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_t_CompletedC0C1_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_t_DriverAvoidObj_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_AngLimitMax_Vspd_str {
*|  :description = "AES_ESA_cal.k_AES_AngLimitMax_Vspd";
*|  :units = "deg";
*|  :type = caltype.single_0_500_CT;
*|  }
*|  .k_AES_Lat_KpKdSlopeLmt_str {
*|  :description = "";
*|  :units = "N";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_Hed_KpKdSlopeLmt_str {
*|  :description = "";
*|  :units = "N";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_t_FCWObstacleValid_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m1000_1000_CT;
*|  }
*|  .k_AES_CsderEgoLen2PlanEndX_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_DefaultPassLaneLineCheck_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_DefaultPassObstacleCheck_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_StrWhlAngFilterCon_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_1000_CT;
*|  }
*|  .k_AES_useFeedbackFirstPln_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_EnterEgoSpeed_MaxThr_VRU_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_EnterEgoSpeed_MinThr_VRU_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_ExitEgoSpeed_MaxThr_VRU_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_ExitEgoSpeed_MinThr_VRU_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_FeedForward_Coef_Second_str {
*|  :description = "AES_ESA_cal.k_AES_FeedForward_Coef_Second";
*|  :units = "N";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_FeedForwardGain_SlopeLmt_str {
*|  :description = "";
*|  :units = "N";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_AEBObjUseISOcoordinate_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.int8_m1_1_CT;
*|  }
*|  .k_AES_t_DriverQuickStr_OffDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_HostLaneObsOffset_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_FeedForward_First_ESA_L_str {
*|  :description = "AES_ESA_cal.k_AES_FeedForward_First_ESA_L";
*|  :units = "N";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_FeedForward_First_ESA_R_str {
*|  :description = "AES_ESA_cal.k_AES_FeedForward_First_ESA_R";
*|  :units = "N";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_FeedForward_Sec_ESA_L_str {
*|  :description = "AES_ESA_cal.k_AES_FeedForward_Sec_ESA_L";
*|  :units = "N";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_FeedForward_Sec_ESA_R_str {
*|  :description = "AES_ESA_cal.k_AES_FeedForward_Sec_ESA_R";
*|  :units = "N";
*|  :type = caltype.single_0_10000_CT;
*|  }
*|  .k_AES_t_TTCValid_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_EnableAllTypeForAES_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_PlanAddDist_Static_str {
*|  :description = "AES_ESA_cal.k_AES_PlanAddDist_Static";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_PlanAddDist_SlowSpd_str {
*|  :description = "AES_ESA_cal.k_AES_PlanAddDist_SlowSpd";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_PlanAddDist_OnCome_str {
*|  :description = "AES_ESA_cal.k_AES_PlanAddDist_OnCome";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_LastPntBrk_TTC_OC_str {
*|  :description = "AES_ESA_cal.k_AES_LastPntBrk_TTC_OC";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_LastPntBrk_TTC_OC_ESA_str {
*|  :description = "AES_ESA_cal.k_AES_LastPntBrk_TTC_OC_ESA";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_MaxBrakeDecelProtect_str {
*|  :description = "AES_ESA_cal.k_AES_MaxBrakeDecelProtect";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_MaxBrakeDecelProtect_ESA_str {
*|  :description = "AES_ESA_cal.k_AES_MaxBrakeDecelProtect_ESA";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_FCWObsSlowSpd_OnDly_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_MaxBrakeDecelThr_str {
*|  :description = "AES_ESA_cal.k_AES_MaxBrakeDecelThr";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_MaxBrakeDecelThr_ESA_str {
*|  :description = "AES_ESA_cal.k_AES_MaxBrakeDecelThr_ESA";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_MaxBrkDeThr_SlowSpd_str {
*|  :description = "AES_ESA_cal.k_AES_MaxBrkDeThr_SlowSpd";
*|  :units = "";
*|  :type = caltype.single_m200_200_CT;
*|  }
*|  .k_AES_LeftLongSafeDistance_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AES_RightLongSafeDistance_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AES_t_ActiveMaxTimeThr_str {
*|  :description = "AES_ESA_cal.k_AES_t_ActiveMaxTimeThr";
*|  :units = "";
*|  :type = caltype.single_0_10_CT;
*|  }
*|  .k_AES_ObjFilterLonMaxTTC_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AES_DriverStrJudge_AngSpdThr_str {
*|  :description = "AES_ESA_cal.k_AES_DriverStrJudge_AngSpdThr";
*|  :units = "";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AES_DriverStrJudge_AngThr_str {
*|  :description = "AES_ESA_cal.k_AES_DriverStrJudge_AngThr";
*|  :units = "";
*|  :type = caltype.single_0_200_CT;
*|  }
*|  .k_AES_ObjOverLapLatThrsd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_m10_10_CT;
*|  }
*|  .k_AES_DisableESAObj_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.boolean_0_1_CT;
*|  }
*|  .k_AES_FCWObstacleLatOverLap_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_FCWObstacleLatVel_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_RoadEdgeValid_MaxThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_RoadEdgeValid_MinThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_NoLaneLine_LatMoveThd_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*|  .k_AES_NoLaneLine_Flag_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.uint8_0_250_CT;
*|  }
*|  .k_AES_CTL_heading_spd_str {
*|  :description = "AES_ESA_cal.k_AES_CTL_heading_spd";
*|  :units = "";
*|  :type = caltype.single_m10_200_CT;
*|  }
*|  .k_AES_CTL_heading_error_factor_str {
*|  :description = "AES_ESA_cal.k_AES_CTL_heading_error_factor";
*|  :units = "";
*|  :type = caltype.single_m10_100_CT;
*|  }
*|  .k_AES_FCWObstacleLatOverLap_AES_str {
*|  :description = "";
*|  :units = "";
*|  :type = caltype.single_0_100_CT;
*|  }
*| }
*/
