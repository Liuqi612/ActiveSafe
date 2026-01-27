/*
 * File: LongSafe_SWC_types.h
 *
 * Code generated for Simulink model 'LongSafe_SWC'.
 *
 * Model version                  : 7.3239
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Fri Jan 16 11:06:54 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 64-bit (LP64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. ROM efficiency
 *    3. RAM efficiency
 *    4. Traceability
 *    5. Safety precaution
 *    6. Debugging
 *    7. MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_LongSafe_SWC_types_h_
#define RTW_HEADER_LongSafe_SWC_types_h_
#include "rtwtypes.h"
#include "CllsnRednByBrkgPostStsArbn1Vcc.h"
#include "BrkArb_DIAG.h"
#include "Sceniaro_DIAG.h"
#include "DiagPathGeneration0.h"

/* Model Code Variants */
#ifndef DEFINED_TYPEDEF_FOR_NoYes1_
#define DEFINED_TYPEDEF_FOR_NoYes1_

typedef enum {
  NoYes1_No = 0,                       /* Default value */
  NoYes1_Yes
} NoYes1;

#endif

#ifndef DEFINED_TYPEDEF_FOR_NoYes1Vcc_
#define DEFINED_TYPEDEF_FOR_NoYes1Vcc_

typedef enum {
  NoYes1Vcc_No = 0,                    /* Default value */
  NoYes1Vcc_Yes
} NoYes1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ActtnDataFromCllsnRednByBrkgCtrl1VccSteerGainEna0_
#define DEFINED_TYPEDEF_FOR_ActtnDataFromCllsnRednByBrkgCtrl1VccSteerGainEna0_

typedef enum {
  ActtnDataFromCllsnRednByBrkgCtrl1VccSteerGainEna0_TRUE = 1,/* Default value */
  ActtnDataFromCllsnRednByBrkgCtrl1VccSteerGainEna0_FALSE = 0
} ActtnDataFromCllsnRednByBrkgCtrl1VccSteerGainEna0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_OnOff1_
#define DEFINED_TYPEDEF_FOR_OnOff1_

typedef enum {
  OnOff1_Off = 0,                      /* Default value */
  OnOff1_On
} OnOff1;

#endif

#ifndef DEFINED_TYPEDEF_FOR_OnOff1Vcc_
#define DEFINED_TYPEDEF_FOR_OnOff1Vcc_

typedef enum {
  OnOff1Vcc_Off = 0,                   /* Default value */
  OnOff1Vcc_On
} OnOff1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsySftyDecelReqDendBySpdRedn0_
#define DEFINED_TYPEDEF_FOR_AsySftyDecelReqDendBySpdRedn0_

typedef enum {
  AsySftyDecelReqDendBySpdRedn0_TRUE = 1,/* Default value */
  AsySftyDecelReqDendBySpdRedn0_FALSE = 0
} AsySftyDecelReqDendBySpdRedn0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PrimTarWarn1VccPrimTarInPahNow0_
#define DEFINED_TYPEDEF_FOR_PrimTarWarn1VccPrimTarInPahNow0_

typedef enum {
  PrimTarWarn1VccPrimTarInPahNow0_TRUE = 1,/* Default value */
  PrimTarWarn1VccPrimTarInPahNow0_FALSE = 0
} PrimTarWarn1VccPrimTarInPahNow0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CllsnRednByBrkgWarnReq0_
#define DEFINED_TYPEDEF_FOR_CllsnRednByBrkgWarnReq0_

typedef enum {
  CllsnRednByBrkgWarnReq0_TRUE = 1,    /* Default value */
  CllsnRednByBrkgWarnReq0_FALSE = 0
} CllsnRednByBrkgWarnReq0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjClassn3Vcc_
#define DEFINED_TYPEDEF_FOR_ObjClassn3Vcc_

typedef enum {
  ObjClassn3Vcc_UkwnClass = 0,         /* Default value */
  ObjClassn3Vcc_Car = 1,
  ObjClassn3Vcc_Motorcycle = 2,
  ObjClassn3Vcc_Truck = 3,
  ObjClassn3Vcc_Ped = 4,
  ObjClassn3Vcc_Anim = 7,
  ObjClassn3Vcc_ObjGen = 8,
  ObjClassn3Vcc_Bicycle = 9,
  ObjClassn3Vcc_VehOfUkwnClass = 10,
  ObjClassn3Vcc_God = 11
} ObjClassn3Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CllsnWarnFwdQlyVcc_
#define DEFINED_TYPEDEF_FOR_CllsnWarnFwdQlyVcc_

typedef enum {
  CllsnWarnFwdQlyVcc_NotRelbl = 0,     /* Default value */
  CllsnWarnFwdQlyVcc_Relbl
} CllsnWarnFwdQlyVcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_
#define DEFINED_TYPEDEF_FOR_HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_

typedef enum {
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_UkwnClass = 0,/* Default value */
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Car,
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Motorcycle,
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Truck,
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Ped,
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_NotInUse1,
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_NotInUse2,
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Anim,
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_ObjGen,
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Bicycle,
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_VehOfUkwnClass
} HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsyBltLvl1Vcc_
#define DEFINED_TYPEDEF_FOR_AsyBltLvl1Vcc_

typedef enum {
  AsyBltLvl1Vcc_NoActvn = 0,           /* Default value */
  AsyBltLvl1Vcc_ActvnFLo,
  AsyBltLvl1Vcc_ActvnFHi
} AsyBltLvl1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CllsnFwdWarnCtrlCllsnThreat1Vcc_
#define DEFINED_TYPEDEF_FOR_CllsnFwdWarnCtrlCllsnThreat1Vcc_

typedef enum {
  CllsnFwdWarnCtrlCllsnThreat1Vcc_Ukwn = 0,/* Default value */
  CllsnFwdWarnCtrlCllsnThreat1Vcc_ThreatLo
} CllsnFwdWarnCtrlCllsnThreat1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VehMtnStSafeGroup0VehMtnSt0_
#define DEFINED_TYPEDEF_FOR_VehMtnStSafeGroup0VehMtnSt0_

typedef enum {
  VehMtnStSafeGroup0VehMtnSt0_Ukwn = 0,/* Default value */
  VehMtnStSafeGroup0VehMtnSt0_StandStillVal1,
  VehMtnStSafeGroup0VehMtnSt0_StandStillVal2,
  VehMtnStSafeGroup0VehMtnSt0_StandStillVal3,
  VehMtnStSafeGroup0VehMtnSt0_RollgFwdVal1,
  VehMtnStSafeGroup0VehMtnSt0_RollgFwdVal2,
  VehMtnStSafeGroup0VehMtnSt0_RollgBackwVal1,
  VehMtnStSafeGroup0VehMtnSt0_RollgBackwVal2
} VehMtnStSafeGroup0VehMtnSt0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CllsnMtgtnByBrkgPrimQlyVcc_
#define DEFINED_TYPEDEF_FOR_CllsnMtgtnByBrkgPrimQlyVcc_

typedef enum {
  CllsnMtgtnByBrkgPrimQlyVcc_NotRelbl = 0,/* Default value */
  CllsnMtgtnByBrkgPrimQlyVcc_CoastRelbl,
  CllsnMtgtnByBrkgPrimQlyVcc_BrkSpprtRelbl,
  CllsnMtgtnByBrkgPrimQlyVcc_BrkgRelbl
} CllsnMtgtnByBrkgPrimQlyVcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ReqSts1Vcc_
#define DEFINED_TYPEDEF_FOR_ReqSts1Vcc_

typedef enum {
  ReqSts1Vcc_Ukwn = 0,                 /* Default value */
  ReqSts1Vcc_Resd1,
  ReqSts1Vcc_ThreatMed,
  ReqSts1Vcc_ThreatHi
} ReqSts1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_TqAllwdPosAndNeg_
#define DEFINED_TYPEDEF_FOR_TqAllwdPosAndNeg_

typedef enum {
  TqAllwdPosAndNeg_NoTq = 0,           /* Default value */
  TqAllwdPosAndNeg_Pos,
  TqAllwdPosAndNeg_Neg,
  TqAllwdPosAndNeg_PosAndNeg
} TqAllwdPosAndNeg;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AccSts1_
#define DEFINED_TYPEDEF_FOR_AccSts1_

typedef enum {
  AccSts1_Off = 1,                     /* Default value */
  AccSts1_Stb,
  AccSts1_Stop,
  AccSts1_StopTmp,
  AccSts1_Actv
} AccSts1;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Relbl1Vcc_
#define DEFINED_TYPEDEF_FOR_Relbl1Vcc_

typedef enum {
  Relbl1Vcc_NotRelbl = 0,              /* Default value */
  Relbl1Vcc_Relbl
} Relbl1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_EgoMotionState_
#define DEFINED_TYPEDEF_FOR_EgoMotionState_

typedef enum {
  EgoMotionState_Standby = 1,          /* Default value */
  EgoMotionState_Straight,
  EgoMotionState_MidRadius,
  EgoMotionState_SmallRadius
} EgoMotionState;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PreSceniaroClass_
#define DEFINED_TYPEDEF_FOR_PreSceniaroClass_

typedef enum {
  PreSceniaroClass_SceniaroInhibit = 1,/* Default value */
  PreSceniaroClass_Pre_CCFT,
  PreSceniaroClass_Pre_CCSCP,
  PreSceniaroClass_Pre_CCStrightInpath,
  PreSceniaroClass_Pre_CSTA_LN,
  PreSceniaroClass_Pre_CSTA_RN,
  PreSceniaroClass_Pre_CSFAO_CBNAO,
  PreSceniaroClass_Pre_CBStrightInpath,
  PreSceniaroClass_Pre_CPTA_LN,
  PreSceniaroClass_Pre_CPTA_LF,
  PreSceniaroClass_Pre_CPTA_RF,
  PreSceniaroClass_Pre_CPNCFA,
  PreSceniaroClass_Pre_CPStrightInpath,
  PreSceniaroClass_Pre_GenObjStrightInpath,
  PreSceniaroClass_Pre_GenTA,
  PreSceniaroClass_CarPosnLatInValidHostStright,
  PreSceniaroClass_MotorPosnLatInValidHostStright,
  PreSceniaroClass_PedPosnLatInValidHostStright,
  PreSceniaroClass_AEBCarPosnInValidHostStright
} PreSceniaroClass;

#endif

#ifndef DEFINED_TYPEDEF_FOR_InhbBrkgForPahTurnOverLe0InhbBrkgForALgt0_
#define DEFINED_TYPEDEF_FOR_InhbBrkgForPahTurnOverLe0InhbBrkgForALgt0_

typedef enum {
  InhbBrkgForPahTurnOverLe0InhbBrkgForALgt0_TRUE = 1,/* Default value */
  InhbBrkgForPahTurnOverLe0InhbBrkgForALgt0_FALSE = 0
} InhbBrkgForPahTurnOverLe0InhbBrkgForALgt0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_InhbBrkgForPahTurnOverLe0PahTurnOverLe0_
#define DEFINED_TYPEDEF_FOR_InhbBrkgForPahTurnOverLe0PahTurnOverLe0_

typedef enum {
  InhbBrkgForPahTurnOverLe0PahTurnOverLe0_TRUE = 1,/* Default value */
  InhbBrkgForPahTurnOverLe0PahTurnOverLe0_FALSE = 0
} InhbBrkgForPahTurnOverLe0PahTurnOverLe0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Ctry1VccDrvgSideQly0_
#define DEFINED_TYPEDEF_FOR_Ctry1VccDrvgSideQly0_

typedef enum {
  Ctry1VccDrvgSideQly0_NotRelbl = 0,   /* Default value */
  Ctry1VccDrvgSideQly0_Relbl,
  Ctry1VccDrvgSideQly0_HighRelbl
} Ctry1VccDrvgSideQly0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DrvgSide3Vcc_
#define DEFINED_TYPEDEF_FOR_DrvgSide3Vcc_

typedef enum {
  DrvgSide3Vcc_Ukwn = 0,               /* Default value */
  DrvgSide3Vcc_Le,
  DrvgSide3Vcc_Ri
} DrvgSide3Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjMtnPat1Vcc_
#define DEFINED_TYPEDEF_FOR_ObjMtnPat1Vcc_

typedef enum {
  ObjMtnPat1Vcc_Ukwn = 0,              /* Default value */
  ObjMtnPat1Vcc_Staty,
  ObjMtnPat1Vcc_MovgFromSelf,
  ObjMtnPat1Vcc_MovgToSelf,
  ObjMtnPat1Vcc_MovgToAndStaty
} ObjMtnPat1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SceniaroInvalidReason_
#define DEFINED_TYPEDEF_FOR_SceniaroInvalidReason_

typedef int8_T SceniaroInvalidReason;

/* enum SceniaroInvalidReason */
#define SceniaroInvalidReason_Normal   ((SceniaroInvalidReason)1) /* Default value */
#define SceniaroInvalidReason_CCFT_VlatInValid ((SceniaroInvalidReason)2)
#define SceniaroInvalidReason_CCFT_PosnlatInValid ((SceniaroInvalidReason)3)
#define SceniaroInvalidReason_CCFT_SpdInValid ((SceniaroInvalidReason)4)
#define SceniaroInvalidReason_CCFT_HeadingInValid ((SceniaroInvalidReason)5)
#define SceniaroInvalidReason_CCFT_HostInValid ((SceniaroInvalidReason)6)
#define SceniaroInvalidReason_CCSCP_VlgtInValid ((SceniaroInvalidReason)7)
#define SceniaroInvalidReason_CCSCP_HeadingInValid ((SceniaroInvalidReason)8)
#define SceniaroInvalidReason_CCStrightInpath_VlgtInValid ((SceniaroInvalidReason)9)
#define SceniaroInvalidReason_C2CSceniaroInValid ((SceniaroInvalidReason)10)
#define SceniaroInvalidReason_CPNA_VlgtInValid ((SceniaroInvalidReason)11)
#define SceniaroInvalidReason_CPNA_HeadingInValid ((SceniaroInvalidReason)12)
#define SceniaroInvalidReason_CPStrightInpath_VlgtInValid ((SceniaroInvalidReason)13)
#define SceniaroInvalidReason_CBFANA_VlgtInValid ((SceniaroInvalidReason)14)
#define SceniaroInvalidReason_CBFANA_HeadingInValid ((SceniaroInvalidReason)15)
#define SceniaroInvalidReason_CBStrightInpath_VlgtInValid ((SceniaroInvalidReason)16)
#define SceniaroInvalidReason_CBInValidSceniaro ((SceniaroInvalidReason)17)
#define SceniaroInvalidReason_CPInValidSceniaro ((SceniaroInvalidReason)18)
#define SceniaroInvalidReason_CCSCP_HostVlgtInValid ((SceniaroInvalidReason)19)
#define SceniaroInvalidReason_CCFT_HostAndPrimSpdErrInvalid ((SceniaroInvalidReason)20)
#define SceniaroInvalidReason_InValidSceniaro ((SceniaroInvalidReason)21)
#define SceniaroInvalidReason_TTCMoreLarge ((SceniaroInvalidReason)22)
#define SceniaroInvalidReason_CSTA_RN_PosnlatInValid ((SceniaroInvalidReason)23)
#define SceniaroInvalidReason_CSTA_RN_SpdInValid ((SceniaroInvalidReason)24)
#define SceniaroInvalidReason_CSTA_RN_HeadingInValid ((SceniaroInvalidReason)25)
#define SceniaroInvalidReason_CSTA_RN_HostInValid ((SceniaroInvalidReason)26)
#define SceniaroInvalidReason_PrimTar_CSTA_LN_VlatValid ((SceniaroInvalidReason)28)
#define SceniaroInvalidReason_PrimTar_CSTA_LN_PosnlatValid ((SceniaroInvalidReason)29)
#define SceniaroInvalidReason_PrimTar_CSTA_LN_SpdValid ((SceniaroInvalidReason)30)
#define SceniaroInvalidReason_PrimTar_CSTA_LN_HeadingValid ((SceniaroInvalidReason)31)
#define SceniaroInvalidReason_CSTA_LN_HostInValid ((SceniaroInvalidReason)32)
#define SceniaroInvalidReason_PrimTar_CSTA_LN_PosnLgtInValid ((SceniaroInvalidReason)35)
#define SceniaroInvalidReason_PrimTar_CSTA_RN_PosnLgtInValid ((SceniaroInvalidReason)36)
#define SceniaroInvalidReason_PrimTar_CPTA_LF_SpdInValid ((SceniaroInvalidReason)37)
#define SceniaroInvalidReason_PrimTar_CPTA_L_PosnLatInValid ((SceniaroInvalidReason)38)
#define SceniaroInvalidReason_PrimTar_CPTA_LF_PosnLgtInValid ((SceniaroInvalidReason)39)
#define SceniaroInvalidReason_PrimTar_CPTA_LF_HostSpdInValid ((SceniaroInvalidReason)40)
#define SceniaroInvalidReason_PrimTar_CPTA_LN_SpdInValid ((SceniaroInvalidReason)41)
#define SceniaroInvalidReason_PrimTar_CPTA_LN_HostSpdInValid ((SceniaroInvalidReason)42)
#define SceniaroInvalidReason_PrimTar_CPTA_RF_InValid ((SceniaroInvalidReason)43)
#define SceniaroInvalidReason_PrimTar_CPTA_RF_HostSpdInValid ((SceniaroInvalidReason)44)
#define SceniaroInvalidReason_PrimTar_CPTA_RF_PosnLgtInValid ((SceniaroInvalidReason)45)
#define SceniaroInvalidReason_IntvCaptureFail ((SceniaroInvalidReason)46)
#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjMtnPatHist1Vcc_
#define DEFINED_TYPEDEF_FOR_ObjMtnPatHist1Vcc_

typedef enum {
  ObjMtnPatHist1Vcc_Ukwn = 0,          /* Default value */
  ObjMtnPatHist1Vcc_NotMovg,
  ObjMtnPatHist1Vcc_PrevMovmtFromSelf,
  ObjMtnPatHist1Vcc_PrevMovmtToSelf
} ObjMtnPatHist1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PrimTarIntv1VccPrimTarInPahNow0_
#define DEFINED_TYPEDEF_FOR_PrimTarIntv1VccPrimTarInPahNow0_

typedef enum {
  PrimTarIntv1VccPrimTarInPahNow0_TRUE = 1,/* Default value */
  PrimTarIntv1VccPrimTarInPahNow0_FALSE = 0
} PrimTarIntv1VccPrimTarInPahNow0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_GenQf1_
#define DEFINED_TYPEDEF_FOR_GenQf1_

typedef enum {
  GenQf1_UndefindDataAccur = 0,        /* Default value */
  GenQf1_TmpUndefdData,
  GenQf1_DataAccurNotWithinSpcn,
  GenQf1_AccurData
} GenQf1;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CritLgtCdnForWarn0ObjALrgDetd0_
#define DEFINED_TYPEDEF_FOR_CritLgtCdnForWarn0ObjALrgDetd0_

typedef enum {
  CritLgtCdnForWarn0ObjALrgDetd0_TRUE = 1,/* Default value */
  CritLgtCdnForWarn0ObjALrgDetd0_FALSE = 0
} CritLgtCdnForWarn0ObjALrgDetd0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Side1Vcc_
#define DEFINED_TYPEDEF_FOR_Side1Vcc_

typedef enum {
  Side1Vcc_Re = 0,                     /* Default value */
  Side1Vcc_Frnt,
  Side1Vcc_RiSide,
  Side1Vcc_LeSide,
  Side1Vcc_Ukwn
} Side1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DiagcBusForDrvrStEstimr1VccUseRoadBasedPath0_
#define DEFINED_TYPEDEF_FOR_DiagcBusForDrvrStEstimr1VccUseRoadBasedPath0_

typedef enum {
  DiagcBusForDrvrStEstimr1VccUseRoadBasedPath0_TRUE = 1,/* Default value */
  DiagcBusForDrvrStEstimr1VccUseRoadBasedPath0_FALSE = 0
} DiagcBusForDrvrStEstimr1VccUseRoadBasedPath0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Snvty1_
#define DEFINED_TYPEDEF_FOR_Snvty1_

typedef enum {
  Snvty1_NotInUse = 0,                 /* Default value */
  Snvty1_LoSnvty,
  Snvty1_NormSnvty,
  Snvty1_HiSnvty
} Snvty1;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AEBState_
#define DEFINED_TYPEDEF_FOR_AEBState_

typedef enum {
  AEB_OFF = 0,                         /* Default value */
  AEB_INITIALIZE,
  AEB_PASSIVE,
  AEB_STANDBY,
  AEB_ACTIVE,
  AEB_FAILURE,
  AEB_HOLD
} AEBState;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AWBState_
#define DEFINED_TYPEDEF_FOR_AWBState_

typedef enum {
  AWB_INITIALIZE = 1,                  /* Default value */
  AWB_STANDBY,
  AWB_PREACTIVE,
  AWB_FAILURE,
  AWB_ACTIVE,
  AWB_COOL
} AWBState;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PrefillState_
#define DEFINED_TYPEDEF_FOR_PrefillState_

typedef enum {
  Prefill_INITIALIZE = 1,              /* Default value */
  Prefill_STANDBY,
  Prefill_ACTIVE
} PrefillState;

#endif

#ifndef DEFINED_TYPEDEF_FOR_HBAState_
#define DEFINED_TYPEDEF_FOR_HBAState_

typedef enum {
  HBA_INITIALIZE = 1,                  /* Default value */
  HBA_STANDBY,
  HBA_ACTIVE
} HBAState;

#endif

#ifndef DEFINED_TYPEDEF_FOR_FCWState_
#define DEFINED_TYPEDEF_FOR_FCWState_

typedef enum {
  FCW_OFF = 0,                         /* Default value */
  FCW_INITIALIZE,
  FCW_PASSIVE,
  FCW_STANDBY,
  FCW_ACTIVE,
  FCW_FAILURE
} FCWState;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsVseHeader_
#define DEFINED_TYPEDEF_FOR_AsVseHeader_

typedef struct {
  uint8_T vse_version_major;
  uint8_T vse_version_minor;
  uint16_T u16_vse_reserve01;
  uint32_T Start_timestamp_ms;
  uint32_T Start_timestamp_us_high;
  uint32_T Start_timestamp_us_low;
  uint32_T End_timestamp_ms;
  uint32_T End_timestamp_us_high;
  uint32_T End_timestamp_us_low;
} AsVseHeader;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsVseSeries_
#define DEFINED_TYPEDEF_FOR_AsVseSeries_

typedef struct {
  uint64_T timestamp[20];
  real32_T yawrate_rps[20];
  real32_T speed_mps[20];
  real32_T slip_rad[20];
  real32_T rear_position_long_m[20];
  real32_T rear_position_lat_m[20];
  real32_T heading_rad[20];
  real32_T pitch_rad[20];
  real32_T roll_rad[20];
} AsVseSeries;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsVseOut_
#define DEFINED_TYPEDEF_FOR_AsVseOut_

typedef struct {
  AsVseHeader vse_header;
  AsVseSeries state_series;
  real32_T host_length;
  real32_T host_width;
  real32_T host_dist_to_front;
  real32_T speed;
  real32_T display_speed;
  real32_T yawrate;
  real32_T yawrate_unfiltered_rps;
  real32_T long_accel;
  real32_T lat_accel;
  real32_T host_pitch_rad;
  real32_T host_roll_rad;
  real32_T vcs_sideslip;
  real32_T vcs_long_vel;
  real32_T vcs_lat_vel;
  real32_T sensor_sideslip;
  real32_T sensor_long_vel;
  real32_T sensor_lat_vel;
  real32_T rear_curvature;
  real32_T rear_curvaturerate;
  real32_T rear_curvature_radius;
  real32_T rear_sideslip;
  real32_T host_steerwheelangle;
  real32_T host_steerwheelangle_rate;
  real32_T host_slope_long_rad;
  real32_T host_slope_lat_rad;
  real32_T gas_pedal_pos;
  real32_T brake_pedal_pos;
  real32_T brake_pressure;
  real32_T gas_pedal_pos_rate;
  real32_T brake_pedal_pos_rate;
  real32_T brake_pressure_rate;
  real32_T acc_brake_cmd;
  uint8_T hazard_lamp_st;
  uint8_T front_fog_lamp_st;
  uint8_T back_fog_lamp_st;
  uint8_T left_light_fault_st;
  uint8_T right_light_fault_st;
  uint8_T epb_applied;
  uint8_T high_bream_st;
  uint8_T vdc_active_st;
  uint8_T tcs_active_st;
  uint8_T hdc_active_st;
  uint8_T esc_off_st;
  uint8_T fl_door_st;
  uint8_T fr_door_st;
  uint8_T rl_door_st;
  uint8_T rr_door_st;
  uint8_T turn_light_switch_pos;
  uint8_T left_light_st;
  uint8_T right_light_st;
  uint8_T eng_hood_unlock_warn;
  uint8_T trunk_st;
  uint8_T front_wiper_work_st;
  uint8_T f_reverse_status;
  uint8_T driver_belt_switch_st;
  uint8_T actual_gear;
  uint8_T brake_pedal_type;
  uint8_T fcw_warn_dist;
  uint8_T longsafe_switch;
  uint8_T bsd_switch;
  uint8_T dow_switch;
  uint8_T fctb_switch;
  uint8_T rctb_switch;
  uint8_T rcw_switch;
  boolean_T brake_pedal_apld;
  uint8_T abs_active;
  uint8_T aeb_active;
  uint8_T power_mode;
  boolean_T long_ctrl_brake_active;
  boolean_T straight_driving;
  boolean_T high_dynamic;
  uint16_T host_state;
  uint32_T esp_brake_available_st;
  uint32_T function_did_config;
} AsVseOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsLongSafeObject_
#define DEFINED_TYPEDEF_FOR_AsLongSafeObject_

typedef struct {
  uint8_T Trk_Index;
  uint8_T Status;
  uint16_T Age;
  int32_T Vis_TrkID;
  int32_T Fusion_TrackID;
  int32_T ObjectClass;
  int32_T Detection_Sensor;
  real32_T PosnLgt;
  real32_T PosnLat;
  real32_T Heading;
  real32_T Speed;
  real32_T VLat;
  real32_T VLgt;
  real32_T ALat;
  real32_T ALgt;
  real32_T TTC;
  real32_T Xolc;
  real32_T LatEst;
  real32_T ALatReq;
  real32_T ALgtReq;
  real32_T Length;
  real32_T Width;
  real32_T Pred_ALgt;
  real32_T Pred_ALat;
  real32_T Pred_A;
  real32_T Pred_Cvt;
  real32_T OffsetLgt_Pred;
  real32_T OffsetLat_Pred;
  real32_T Offs_LatManoeuvre;
  real32_T Offs_LatInPathPrimaryTarget;
  real32_T Offs_LatInPathCloseEdge;
  real32_T Offs_LatInPathFarEdge;
  real32_T Offs_LatIntersection;
  real32_T Offs_LatMultiTarget;
  real32_T Abs_Heading;
  real32_T LengthSide_Lgt;
  real32_T LengthSide_Lat;
  real32_T Sin_rotation;
  real32_T Cos_rotation;
  uint8_T Inpath_current;
  uint8_T Inpath_Predict;
  uint8_T Match_Conf;
  uint8_T Motion_Type;
  boolean_T Stationary;
  boolean_T OnComing;
  boolean_T Pred_parallel;
  boolean_T IsVehicle;
  boolean_T IsVehicleMotor;
  uint8_T CurvedMotion;
  uint8_T SideClosest;
} AsLongSafeObject;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsScenarioInfo_
#define DEFINED_TYPEDEF_FOR_AsScenarioInfo_

typedef struct {
  uint32_T obj_evaluator;
  uint32_T resv1;
  uint32_T resv2;
  uint32_T resv3;
} AsScenarioInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsLongSafeOut_
#define DEFINED_TYPEDEF_FOR_AsLongSafeOut_

typedef struct {
  AsLongSafeObject longsafe_aeb;
  AsLongSafeObject longsafe_fcw;
  AsScenarioInfo longsafe_scenario;
  uint8_T longsafe_roll_cnt;
  uint8_T longsafe_major_version;
  uint8_T longsafe_minor_version;
} AsLongSafeOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsSfObjInfo_
#define DEFINED_TYPEDEF_FOR_AsSfObjInfo_

typedef struct {
  int32_T objID;
  real32_T crashPointXl;
  real32_T crashProb;
  real32_T objTTC;
  real32_T objHeading;
  real32_T objLongPos;
  real32_T objLatPos;
  real32_T objLongVel;
  real32_T objLatVel;
  real32_T objLongAccel;
  real32_T objLatAceel;
  real32_T objAlertCnt;
  real32_T objAlertCntThresh;
  real32_T objInZone;
  real32_T objAlertLevel;
} AsSfObjInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsDowOut_
#define DEFINED_TYPEDEF_FOR_AsDowOut_

typedef struct {
  uint32_T left_alert;
  uint32_T right_alert;
  AsSfObjInfo left_obj;
  AsSfObjInfo right_obj;
} AsDowOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsLcdaOut_
#define DEFINED_TYPEDEF_FOR_AsLcdaOut_

typedef struct {
  uint32_T bsd_left_alert;
  uint32_T bsd_right_alert;
  uint32_T cvw_left_alert;
  uint32_T cvw_right_alert;
  AsSfObjInfo bsd_left_obj;
  AsSfObjInfo bsd_right_obj;
  AsSfObjInfo cvw_left_obj;
  AsSfObjInfo cvw_right_obj;
} AsLcdaOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsCtsOut_
#define DEFINED_TYPEDEF_FOR_AsCtsOut_

typedef struct {
  uint32_T fcta_left_alert;
  uint32_T fcta_right_alert;
  uint32_T rcta_left_alert;
  uint32_T rcta_right_alert;
  AsSfObjInfo fcta_left_obj;
  AsSfObjInfo fcta_right_obj;
  AsSfObjInfo rcta_left_obj;
  AsSfObjInfo rcta_right_obj;
} AsCtsOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsRcwOut_
#define DEFINED_TYPEDEF_FOR_AsRcwOut_

typedef struct {
  uint32_T rcw_alert;
  AsSfObjInfo obj;
} AsRcwOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsSideFeatureOut_
#define DEFINED_TYPEDEF_FOR_AsSideFeatureOut_

typedef struct {
  uint8_T sf_rollingcnt;
  uint8_T sf_major_version;
  uint8_T sf_minor_version;
  uint8_T resv1;
  AsDowOut dow;
  AsLcdaOut lcda;
  AsCtsOut cts;
  AsRcwOut rcw;
} AsSideFeatureOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsOnComingObject_
#define DEFINED_TYPEDEF_FOR_AsOnComingObject_

typedef struct {
  real32_T vcs_long_posn;
  real32_T vcs_long_vel;
  real32_T vcs_long_accel;
  real32_T vcs_lat_posn;
  real32_T vcs_lat_vel;
  real32_T vcs_lat_accel;
  real32_T width;
  real32_T length;
  real32_T vcs_rm_dis;
  real32_T curv_heading;
  uint8_T object_class;
  uint8_T fusion_source;
  uint8_T track_status;
  uint8_T movement;
  uint8_T cmbbPrimaryConfidence;
  uint8_T FcwConfidence;
  uint8_T maturity;
  uint8_T visTrkID;
  boolean_T f_oncoming;
  uint8_T track_id;
  uint8_T oncom_confidence;
  uint8_T collision_prob;
} AsOnComingObject;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsOnComingOut_
#define DEFINED_TYPEDEF_FOR_AsOnComingOut_

typedef struct {
  AsOnComingObject oncom_target_1;
  AsOnComingObject oncom_target_2;
  AsOnComingObject oncom_target_3;
  uint8_T as_oncoming_rollcnt;
  uint8_T oncoming_major_version;
  uint8_T oncoming_minor_version;
  uint8_T u8_reserve1;
} AsOnComingOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsOverTakingObject_
#define DEFINED_TYPEDEF_FOR_AsOverTakingObject_

typedef struct {
  real32_T vcs_long_posn;
  real32_T vcs_long_vel;
  real32_T vcs_long_accel;
  real32_T vcs_lat_posn;
  real32_T vcs_lat_vel;
  real32_T vcs_lat_accel;
  real32_T width;
  real32_T length;
  real32_T vcs_heading;
  real32_T confidence;
  uint8_T object_class;
  uint8_T fusion_source;
  uint8_T track_status;
  uint8_T visTrkID;
  uint8_T track_id;
} AsOverTakingObject;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsOverTakingOut_
#define DEFINED_TYPEDEF_FOR_AsOverTakingOut_

typedef struct {
  AsOverTakingObject overtake_target_rear_left;
  AsOverTakingObject overtake_target_rear_right;
  AsOverTakingObject overtake_target_front_left;
  AsOverTakingObject overtake_target_front_right;
  uint8_T as_overtaking_rollcnt;
  uint8_T overtaking_major_version;
  uint8_T overtaking_minor_version;
  uint8_T u8_reserve1;
} AsOverTakingOut;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsTimeInfo_
#define DEFINED_TYPEDEF_FOR_AsTimeInfo_

typedef struct {
  uint64_T cur_time;
  uint64_T fus_time;
  uint64_T roadgeometry_time;
  uint64_T vehicle_time;
  uint64_T gop_time;
  uint64_T vehicle_cmd_time;
  uint64_T occ_time;
  uint64_T resv1_time;
  uint64_T resv2_time;
  uint64_T resv3_time;
  uint64_T tap_mode;
  uint8_T tsel_lgsf_cnt;
  uint8_T tsel_sf_cnt;
  uint8_T ctrl_lgsf_cnt;
  uint8_T ctrl_sf_cnt;
} AsTimeInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsCoreOut_T_
#define DEFINED_TYPEDEF_FOR_AsCoreOut_T_

typedef struct {
  AsLongSafeOut longsafe;
  AsSideFeatureOut sidefeature;
  AsOnComingOut oncoming;
  AsOverTakingOut overtaking;
  AsTimeInfo time;
  uint8_T activesafety_rollingcnt;
  uint8_T major_version;
  uint8_T middle_version;
  uint8_T minor_version;
} AsCoreOut_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsParamConfig_T_
#define DEFINED_TYPEDEF_FOR_AsParamConfig_T_

typedef struct {
  boolean_T k_LgSf_UseShadowMode;
  boolean_T k_LgSf_AEB_Enable;
  boolean_T k_LgSf_EnCone;
  boolean_T k_LgSf_EnBarrier;
  real32_T k_LgSf_PosnLgtOffset;
  boolean_T k_LgSf_EnConfInhibit;
  boolean_T k_LgSf_EnEgoConfInhibit;
  boolean_T k_LgSf_EnObsConfInhibit;
  boolean_T k_LgSf_EnSceniaroCheck;
  boolean_T k_LgSf_EnAWB;
  real32_T k_LgSf_MinAebDecelValue;
  boolean_T k_LgSf_EnHighMiles;
  boolean_T k_LgSf_EnSimulationMode;
  uint8_T k_LgSf_ActiveSafeMode;
  uint8_T k_ignore_roadedge_check;
  uint8_T k_LgSf_EnTestScene;
} AsParamConfig_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Diag_InhibitCdnSts_
#define DEFINED_TYPEDEF_FOR_Diag_InhibitCdnSts_

typedef struct {
  uint8_T inhibitFcw;
  uint8_T belowLowSpeedLimit;
  uint8_T vehicleNotRollingForward;
  uint8_T fcwDisabledByFaultManager;
  uint8_T SceniaroCheckNotOk;
  uint8_T resv1;
  uint8_T resv2;
  uint8_T resv3;
} Diag_InhibitCdnSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Diag_StartConditions_
#define DEFINED_TYPEDEF_FOR_Diag_StartConditions_

typedef struct {
  uint8_T Btn_AboveLimit;
  real32_T brakeThreatNumber;
  uint8_T objectIsValid;
  uint8_T driverCanNotEasilySteerAway;
  uint8_T BtnTrigger;
  uint8_T cmbbTrigger;
  uint8_T visionOnlyTrigger;
  uint8_T startConditionsMet;
  uint8_T warningType;
  uint8_T brakeGainConditionsMet;
  uint8_T comfortDistanceTrigger;
  uint8_T BrakeGainConditionsBit;
  uint8_T warningState;
  uint8_T resv1;
} Diag_StartConditions;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ActtnDataFromCllsnFwdWarnCtrl1Vcc_
#define DEFINED_TYPEDEF_FOR_ActtnDataFromCllsnFwdWarnCtrl1Vcc_

typedef struct {
  real32_T DecelReq;
  OnOff1Vcc DecelEna;
  real32_T BrkGainReq;
  real32_T BrkGainMaxDecel;
  OnOff1Vcc BrkGainEna;
  CllsnFwdWarnCtrlCllsnThreat1Vcc CllsnThreat;
  AsyBltLvl1Vcc BltLvl;
  boolean_T DwActive;
} ActtnDataFromCllsnFwdWarnCtrl1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ActtnDataFromCllsnRednByBrkgCtrl1Vcc_
#define DEFINED_TYPEDEF_FOR_ActtnDataFromCllsnRednByBrkgCtrl1Vcc_

typedef struct {
  real32_T DecelReq;
  NoYes1Vcc DamprReq;
  OnOff1Vcc DecelEna;
  OnOff1 SteerAsEna;
  OnOff1Vcc CrsCnclReq;
  OnOff1Vcc StandStillReq;
  AsyBltLvl1Vcc BltLvl;
  ReqSts1Vcc CllsnThreat;
  TqAllwdPosAndNeg SteerTqSgnReq;
  ActtnDataFromCllsnRednByBrkgCtrl1VccSteerGainEna0 SteerGainEna;
} ActtnDataFromCllsnRednByBrkgCtrl1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MtnRqrdIntv_
#define DEFINED_TYPEDEF_FOR_MtnRqrdIntv_

typedef struct {
  real32_T ALatRqrd;
  int32_T ALatRqrdQly;
  real32_T APosLgtRqrd;
  real32_T ANegLgtRqrd;
  real32_T JerkNegLgtRqrd;
  real32_T CrvtRateRqrdLe;
  real32_T CrvtRateRqrdRi;
  real32_T CrvtRqrdLe;
  real32_T CrvtRqrdRi;
} MtnRqrdIntv;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MtnRqrdWarn_
#define DEFINED_TYPEDEF_FOR_MtnRqrdWarn_

typedef struct {
  real32_T ALatRqrd;
  int32_T ALatRqrdQly;
  real32_T ANegLgtRqrdForWarn;
  real32_T ANegLgtRqrdForIntv;
} MtnRqrdWarn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MtnRqrd_DIAG_
#define DEFINED_TYPEDEF_FOR_MtnRqrd_DIAG_

typedef struct {
  MtnRqrdIntv MtnRqrd_Intv;
  MtnRqrdWarn MtnRqrd_Warn;
  real32_T ANegLgtRqrdForPrimTarWarn;
} MtnRqrd_DIAG;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DIAG_AccelRequest_
#define DEFINED_TYPEDEF_FOR_DIAG_AccelRequest_

typedef struct {
  real32_T PreBrakeAccReqLimit;
  real32_T FullBrakeAccelerationRequest;
} DIAG_AccelRequest;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DIAG_Deactivate_
#define DEFINED_TYPEDEF_FOR_DIAG_Deactivate_

typedef struct {
  boolean_T Deactivate;
  boolean_T VehicleStationaryLongerThanXSeconds;
  boolean_T CollisionAvoidedByBraking;
  boolean_T ObjConfNotOK;
  boolean_T ObjIdChanged;
  boolean_T DelayDeactivation;
  boolean_T ObjStateDeactivation;
  uint8_T reserved;
} DIAG_Deactivate;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DIAG_OncomingInhibit_
#define DEFINED_TYPEDEF_FOR_DIAG_OncomingInhibit_

typedef struct {
  boolean_T TargetHighCurvature;
  boolean_T TargetAngleNotValid;
  uint8_T reserved1;
  uint8_T reserved2;
  real32_T HostCrvt;
  boolean_T RecentSCurve;
  boolean_T NotTurningNow;
  boolean_T NoRecentAngleSpeed;
  boolean_T NoRecentStart;
  boolean_T MoreHeadOn;
  boolean_T IsVehicleOfUnknownClass;
  uint8_T reserved3;
  uint8_T reserved4;
} DIAG_OncomingInhibit;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DIAG_CommonInhibit_
#define DEFINED_TYPEDEF_FOR_DIAG_CommonInhibit_

typedef struct {
  boolean_T SpdInhibit;
  uint8_T reserved;
  boolean_T HostAvoidInhibit;
  boolean_T HostDrivingStraightAndTargetIsOncoming;
  DIAG_OncomingInhibit OncomingInhibit;
} DIAG_CommonInhibit;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DIAG_Fullbraking_
#define DEFINED_TYPEDEF_FOR_DIAG_Fullbraking_

typedef struct {
  boolean_T FullBrakingThreat;
  boolean_T SteeringThreat;
  boolean_T BrakingThreat;
  boolean_T AccelerationThreat;
  boolean_T ObjectConfOk;
  uint8_T reserved1;
  uint8_T reserved2;
  uint8_T reserved3;
} DIAG_Fullbraking;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DIAG_PreBraking_
#define DEFINED_TYPEDEF_FOR_DIAG_PreBraking_

typedef struct {
  boolean_T PreBrakingThreat;
  boolean_T SteeringThreat;
  boolean_T BrakingThreat;
  boolean_T AccelerationThreat;
  boolean_T ObjConfOK;
  uint8_T reserved1;
  uint8_T reserved2;
  uint8_T reserved3;
} DIAG_PreBraking;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DIAG_CritLgtEval_
#define DEFINED_TYPEDEF_FOR_DIAG_CritLgtEval_

typedef struct {
  DIAG_Deactivate Deactivate;
  DIAG_CommonInhibit CommonInhibit;
  DIAG_Fullbraking Fullbraking;
  DIAG_PreBraking PreBraking;
} DIAG_CritLgtEval;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CMBB_DIAG_
#define DEFINED_TYPEDEF_FOR_CMBB_DIAG_

typedef struct {
  DIAG_AccelRequest AccelRequest;
  DIAG_CritLgtEval CritLgtEval;
  uint8_T CMbBStatus;
  uint8_T reserved1;
  uint8_T reserved2;
  uint8_T reserved3;
} CMBB_DIAG;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CllsnFwdWarnCtrl_Debug_
#define DEFINED_TYPEDEF_FOR_CllsnFwdWarnCtrl_Debug_

typedef struct {
  real32_T DecelReq;
  uint8_T DecelEna;
  real32_T BrkGainReq;
  real32_T BrkGainMaxDecel;
  uint8_T BrkGainEna;
  uint8_T CllsnThreat;
  uint8_T BltLvl;
  uint8_T DwActive;
  uint8_T WarnReq;
  uint8_T WarnObjType;
} CllsnFwdWarnCtrl_Debug;

#endif

#ifndef DEFINED_TYPEDEF_FOR_FCW_DIAG_
#define DEFINED_TYPEDEF_FOR_FCW_DIAG_

typedef struct {
  Diag_StartConditions StartConditions;
  Diag_InhibitCdnSts InhibitCdnSts;
  CllsnFwdWarnCtrl_Debug ActtnDataFromCllsnFwdWarnCtrl;
  uint8_T resv1;
  uint8_T resv2;
} FCW_DIAG;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DIAG_AEBFunc_
#define DEFINED_TYPEDEF_FOR_DIAG_AEBFunc_

typedef struct {
  MtnRqrd_DIAG MtnRqrd;
  CMBB_DIAG CMBB;
  FCW_DIAG FCW;
  BrkArb_DIAG BrkArb;
  Sceniaro_DIAG Sceniaro;
} DIAG_AEBFunc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_BrkPedlPsdRec_
#define DEFINED_TYPEDEF_FOR_BrkPedlPsdRec_

typedef struct {
  NoYes1 BrkPedlPsd;
  GenQf1 BrkPedlPsdQf;
  uint8_T BrkPedlPsdCntr;
  uint8_T BrkPedlPsdChks;
  NoYes1 BrkPedlNotPsdSafe;
} BrkPedlPsdRec;

#endif

#ifndef DEFINED_TYPEDEF_FOR_IdPen_
#define DEFINED_TYPEDEF_FOR_IdPen_

typedef enum {
  IdPen_ProfUkwn = 0,                  /* Default value */
  IdPen_Prof1,
  IdPen_Prof2,
  IdPen_Prof3,
  IdPen_Prof4,
  IdPen_Prof5,
  IdPen_Prof6,
  IdPen_Prof7,
  IdPen_Prof8,
  IdPen_Prof9,
  IdPen_Prof10,
  IdPen_Prof11,
  IdPen_Prof12,
  IdPen_Prof13,
  IdPen_Resd14,
  IdPen_ProfAll
} IdPen;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SnvtyPen1_
#define DEFINED_TYPEDEF_FOR_SnvtyPen1_

typedef struct {
  Snvty1 CllsnAidSnvtySeldSts;
  IdPen CllsnAidSnvtySeldPen;
} SnvtyPen1;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MtnRqrdWarn1Vcc_
#define DEFINED_TYPEDEF_FOR_MtnRqrdWarn1Vcc_

typedef struct {
  real32_T ALatRqrd;
  Relbl1Vcc ALatRqrdQly;
  real32_T ANegLgtRqrdForWarn;
  real32_T ANegLgtRqrdForIntv;
} MtnRqrdWarn1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PrimTarWarn1Vcc_
#define DEFINED_TYPEDEF_FOR_PrimTarWarn1Vcc_

typedef struct {
  real32_T PinionSteerAgSpd;
  real32_T ALgt;
  real32_T Hei;
  uint32_T Idn;
  ObjClassn3Vcc ObjTyp;
  real32_T PosnLat;
  real32_T PosnLgt;
  CllsnWarnFwdQlyVcc QlyWarn;
  real32_T TiToCllsn;
  uint32_T VisnId;
  real32_T VLgt;
  real32_T VLat;
  real32_T Width;
  PrimTarWarn1VccPrimTarInPahNow0 PrimTarInPahNow;
} PrimTarWarn1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CritLgtCdnForWarn0_
#define DEFINED_TYPEDEF_FOR_CritLgtCdnForWarn0_

typedef struct {
  MtnRqrdWarn1Vcc MtnRqrdWarn;
  PrimTarWarn1Vcc PrimTarWarn;
  CritLgtCdnForWarn0ObjALrgDetd0 ObjALrgDetd;
  uint8_T ObjALrgIdn;
} CritLgtCdnForWarn0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MtnLimn1Vcc_
#define DEFINED_TYPEDEF_FOR_MtnLimn1Vcc_

typedef struct {
  real32_T ALatAbsltCmft;
  real32_T ALatAbsltMax;
  real32_T ALgtNegCmft;
  real32_T ALgtNegMeasd;
  real32_T ALgtNegMin;
  real32_T ALgtPosCmft;
  real32_T ALgtPosMax;
  real32_T CrvtAbsltCmft;
  real32_T CrvtAbsltMax;
  real32_T CrvtRateAbsltCmft;
  real32_T CrvtRateAbsltMax;
  real32_T JerkLatAbsltCmft;
  real32_T JerkLatAbsltMax;
  real32_T JerkLgtNegCmft;
  real32_T JerkLgtNegMeasd;
  real32_T JerkLgtNegMin;
  real32_T JerkLgtPosCmft;
  real32_T JerkLgtPosMax;
} MtnLimn1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VehMtnStSafeGroup0_
#define DEFINED_TYPEDEF_FOR_VehMtnStSafeGroup0_

typedef struct {
  VehMtnStSafeGroup0VehMtnSt0 VehMtnSt;
  uint8_T VehMtnStChks;
  uint8_T VehMtnStCntr;
} VehMtnStSafeGroup0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VehSelf1Vcc_
#define DEFINED_TYPEDEF_FOR_VehSelf1Vcc_

typedef struct {
  real32_T VLgt;
  real32_T VLgtCmpFac;
  real32_T ALgt;
  real32_T ALgtRaw;
  real32_T ALatRaw;
  real32_T YawRate;
  real32_T YawRateRaw;
  real32_T PosnLgtDelta;
  real32_T PosnLatDelta;
  real32_T AgDirDelta;
  real32_T Curvature;
  real32_T CurvatureRate;
  real32_T CurvatureRadius;
  boolean_T CMbBActive;
  uint8_T EgoMotionType;
  uint8_T GearSts;
  boolean_T SubScene;
  real32_T DisVehSpd_kph;
  boolean_T APA_BrakeFlag;
  real32_T HostALgtRaw;
  real32_T acc_brake_cmd;
  boolean_T ACC_BrakeActive;
} VehSelf1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DynCalPrmForAccStopNGo0_
#define DEFINED_TYPEDEF_FOR_DynCalPrmForAccStopNGo0_

typedef enum {
  DynCalPrmForAccStopNGo0_Yes = 1,     /* Default value */
  DynCalPrmForAccStopNGo0_No = 0
} DynCalPrmForAccStopNGo0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VehDataForCllsnFwdWarn_
#define DEFINED_TYPEDEF_FOR_VehDataForCllsnFwdWarn_

typedef struct {
  real32_T vehicleSpeed;
  real32_T actualLongitudinalAccr;
  real32_T actualLongitudinalAccrRaw;
  boolean_T brakePedalPressed;
  real32_T driverDecelerationRequest;
  boolean_T autDrvActive;
  real32_T distanceFromRearAxleToFront;
  boolean_T vehicleRollingForward;
  real32_T pinionSteerAgSpd;
  uint8_T propulsionType;
  uint8_T aggregateType;
  uint8_T vehicleType;
} VehDataForCllsnFwdWarn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_HmiDataFromCllsnFwdWarnCtrl1Vcc_
#define DEFINED_TYPEDEF_FOR_HmiDataFromCllsnFwdWarnCtrl1Vcc_

typedef struct {
  OnOff1Vcc WarnReq;
  HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0 ObjTyp;
} HmiDataFromCllsnFwdWarnCtrl1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DrvBehaviorData_
#define DEFINED_TYPEDEF_FOR_DrvBehaviorData_

typedef struct {
  uint8_T BrakePedalSts;
  uint8_T BrakePedalStsValid;
  uint8_T AccelPedalValid;
  real32_T AccelPedalPose;
  real32_T AccelPedalPoseRate;
  real32_T BrakePedalPos;
} DrvBehaviorData;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsyALgtReqForCmftRec1_
#define DEFINED_TYPEDEF_FOR_AsyALgtReqForCmftRec1_

typedef struct {
  real32_T AsyALgtReqForCmft;
  real32_T AsyCmftLgtNegLimForJerk;
  real32_T AsyCmftLgtPosLimForJerk;
} AsyALgtReqForCmftRec1;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MtnRqrdIntv1Vcc_
#define DEFINED_TYPEDEF_FOR_MtnRqrdIntv1Vcc_

typedef struct {
  real32_T ALatRqrd;
  Relbl1Vcc ALatRqrdQly;
  real32_T APosLgtRqrd;
  real32_T ANegLgtRqrd;
  real32_T JerkNegLgtRqrd;
  real32_T CrvtRateRqrdLe;
  real32_T CrvtRateRqrdRi;
  real32_T CrvtRqrdLe;
  real32_T CrvtRqrdRi;
} MtnRqrdIntv1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PrimTarIntv1Vcc_
#define DEFINED_TYPEDEF_FOR_PrimTarIntv1Vcc_

typedef struct {
  real32_T ALat;
  real32_T ALgt;
  real32_T Hei;
  real32_T Crvt;
  uint32_T Idn;
  ObjMtnPat1Vcc MtnPat;
  ObjMtnPatHist1Vcc MtnPatHist;
  ObjClassn3Vcc ObjTyp;
  real32_T PosnLat;
  real32_T PosnLgt;
  CllsnMtgtnByBrkgPrimQlyVcc QlyIntv;
  real32_T TiToCllsn;
  uint32_T VisnId;
  real32_T VLat;
  real32_T VLgt;
  real32_T Width;
  PrimTarIntv1VccPrimTarInPahNow0 PrimTarInPahNow;
  boolean_T InPathPredict;
  uint64_T Object_Age;
} PrimTarIntv1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CritLgtCdnForIntv0_
#define DEFINED_TYPEDEF_FOR_CritLgtCdnForIntv0_

typedef struct {
  MtnRqrdIntv1Vcc MtnRqrdIntv;
  PrimTarIntv1Vcc PrimTarIntv;
  real32_T ANegLgtRqrdForPrimTarWarn;
  real32_T ALatRqrdMplTar;
  Relbl1Vcc ALatRqrdMplTarQly;
} CritLgtCdnForIntv0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_OvrdDecelByDrvr0_
#define DEFINED_TYPEDEF_FOR_OvrdDecelByDrvr0_

typedef struct {
  NoYes1 OvrdDecelByDrvr;
  uint8_T OvrdDecelByDrvrGroupChks;
  uint8_T OvrdDecelByDrvrGroupCntr;
} OvrdDecelByDrvr0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Mkt1Vcc_
#define DEFINED_TYPEDEF_FOR_Mkt1Vcc_

typedef enum {
  Mkt1Vcc_Ukwn = 0,                    /* Default value */
  Mkt1Vcc_MktPrim,
  Mkt1Vcc_Europe,
  Mkt1Vcc_Uk,
  Mkt1Vcc_Us,
  Mkt1Vcc_Canada
} Mkt1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Ctry1Vcc_
#define DEFINED_TYPEDEF_FOR_Ctry1Vcc_

typedef struct {
  uint16_T Idn;
  DrvgSide3Vcc DrvgSide;
  Ctry1VccDrvgSideQly0 DrvgSideQly;
  Mkt1Vcc MktActSgn;
} Ctry1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_HmiDataFromCllsnRednByBrkgCtrl1Vcc_
#define DEFINED_TYPEDEF_FOR_HmiDataFromCllsnRednByBrkgCtrl1Vcc_

typedef struct {
  NoYes1Vcc PostEve;
} HmiDataFromCllsnRednByBrkgCtrl1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DiagcBusForCllsnRednByBrkg1Vcc_
#define DEFINED_TYPEDEF_FOR_DiagcBusForCllsnRednByBrkg1Vcc_

typedef struct {
  CllsnRednByBrkgPostStsArbn1Vcc CllsnRednByBrkgPostStsArbn;
} DiagcBusForCllsnRednByBrkg1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DynCalPrmForCllsnRednByBrkg1_
#define DEFINED_TYPEDEF_FOR_DynCalPrmForCllsnRednByBrkg1_

typedef struct {
  real32_T DynCalPrmForAxleDstReToVehFrnt;
  real32_T CmnCalPrmForMinThdForALatAvl;
  real32_T DynCalPrmForVehSteerWhlAgRat;
  real32_T DynCalPrmForVehWhlBas;
  uint8_T DynCalPrmForSteerWhlPosn;
  real32_T DynCalPrmForBicycleMdlAxleDistFrnt;
  real32_T DynCalPrmForBicycleMdlCornrgStfnFrnt;
  real32_T DynCalPrmForBicycleMdlCornrgStfnRe;
  real32_T DynCalPrmForVehM;
} DynCalPrmForCllsnRednByBrkg1;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AccInfoBusForCllsnRednByBrkg1_
#define DEFINED_TYPEDEF_FOR_AccInfoBusForCllsnRednByBrkg1_

typedef struct {
  AccSts1 AccSts;
  real32_T AsyALgtReqForCmft;
  real32_T AsyALgtActvAftLim;
} AccInfoBusForCllsnRednByBrkg1;

#endif

#ifndef DEFINED_TYPEDEF_FOR_InhbBrkgForPahTurnOverLe0_
#define DEFINED_TYPEDEF_FOR_InhbBrkgForPahTurnOverLe0_

typedef struct {
  InhbBrkgForPahTurnOverLe0PahTurnOverLe0 PahTurnOverLe;
  InhbBrkgForPahTurnOverLe0InhbBrkgForALgt0 InhbBrkgForALgt;
  uint32_T ObjIdSeldTar;
  CllsnMtgtnByBrkgPrimQlyVcc QlySeldTar;
  ObjClassn3Vcc ObjTypSeldTar;
  real32_T TiToCllsnSeldTar;
} InhbBrkgForPahTurnOverLe0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjEstimn1Vcc_
#define DEFINED_TYPEDEF_FOR_ObjEstimn1Vcc_

typedef struct {
  real32_T PosnLgt;
  real32_T PosnLat;
  real32_T Spd;
  real32_T VLgt;
  real32_T VLat;
  real32_T A;
  real32_T ALgt;
  real32_T ALat;
  real32_T AgDir;
  real32_T Crvt;
} ObjEstimn1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_IndcrTurn1Vcc_
#define DEFINED_TYPEDEF_FOR_IndcrTurn1Vcc_

typedef enum {
  IndcrTurn1Vcc_NoIndcn = 0,           /* Default value */
  IndcrTurn1Vcc_Le,
  IndcrTurn1Vcc_Ri,
  IndcrTurn1Vcc_Ukwn
} IndcrTurn1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_LiSts1Vcc_
#define DEFINED_TYPEDEF_FOR_LiSts1Vcc_

typedef enum {
  LiSts1Vcc_Ukwn = 0,                  /* Default value */
  LiSts1Vcc_Off,
  LiSts1Vcc_On
} LiSts1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjInfo1Vcc_
#define DEFINED_TYPEDEF_FOR_ObjInfo1Vcc_

typedef struct {
  ObjClassn3Vcc Typ;
  real32_T Width;
  real32_T Length;
  real32_T Hei;
  Side1Vcc SideNear;
  IndcrTurn1Vcc IndcrTurn;
  LiSts1Vcc IndcrBrkLi;
  LiSts1Vcc IndcrHzrdLi;
  ObjMtnPat1Vcc MtnPat;
  ObjMtnPatHist1Vcc MtnPatHist;
  real32_T DstLatFromMidOfLaneSelf;
} ObjInfo1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SnsrDataSts1Vcc_
#define DEFINED_TYPEDEF_FOR_SnsrDataSts1Vcc_

typedef enum {
  SnsrDataSts1Vcc_Invld = 0,           /* Default value */
  SnsrDataSts1Vcc_Fusn,
  SnsrDataSts1Vcc_New,
  SnsrDataSts1Vcc_PredNew,
  SnsrDataSts1Vcc_UpdNew,
  SnsrDataSts1Vcc_Upd,
  SnsrDataSts1Vcc_Pred
} SnsrDataSts1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjPpty1VccMdlOfMtn0_
#define DEFINED_TYPEDEF_FOR_ObjPpty1VccMdlOfMtn0_

typedef enum {
  ObjPpty1VccMdlOfMtn0_MdlACon = 0,    /* Default value */
  ObjPpty1VccMdlOfMtn0_MdlBicycle
} ObjPpty1VccMdlOfMtn0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjPpty1VccTrfcSceno0_
#define DEFINED_TYPEDEF_FOR_ObjPpty1VccTrfcSceno0_

typedef enum {
  ObjPpty1VccTrfcSceno0_None = 0,      /* Default value */
  ObjPpty1VccTrfcSceno0_TurnAcrssPah
} ObjPpty1VccTrfcSceno0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Relbl4Vcc_
#define DEFINED_TYPEDEF_FOR_Relbl4Vcc_

typedef enum {
  Relbl4Vcc_NotRelbl = 0,              /* Default value */
  Relbl4Vcc_CoastRelbl,
  Relbl4Vcc_BrkSpprtRelbl,
  Relbl4Vcc_BrkgRelbl
} Relbl4Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjPpty1VccTrfcJamAssiQly0_
#define DEFINED_TYPEDEF_FOR_ObjPpty1VccTrfcJamAssiQly0_

typedef enum {
  ObjPpty1VccTrfcJamAssiQly0_NotRelbl = 0,/* Default value */
  ObjPpty1VccTrfcJamAssiQly0_Relbl,
  ObjPpty1VccTrfcJamAssiQly0_HighRelbl
} ObjPpty1VccTrfcJamAssiQly0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Relbl3Vcc_
#define DEFINED_TYPEDEF_FOR_Relbl3Vcc_

typedef enum {
  Relbl3Vcc_NotRelbl = 0,              /* Default value */
  Relbl3Vcc_SoonNotRelbl,
  Relbl3Vcc_LowRelbl,
  Relbl3Vcc_HigherRelbl,
  Relbl3Vcc_HighestRelbl
} Relbl3Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjPpty1VccEmgyLaneKeepAidPosnQly0_
#define DEFINED_TYPEDEF_FOR_ObjPpty1VccEmgyLaneKeepAidPosnQly0_

typedef enum {
  ObjPpty1VccEmgyLaneKeepAidPosnQly0_NotRelbl = 0,/* Default value */
  ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,
  ObjPpty1VccEmgyLaneKeepAidPosnQly0_HighRelbl
} ObjPpty1VccEmgyLaneKeepAidPosnQly0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjPpty1Vcc_
#define DEFINED_TYPEDEF_FOR_ObjPpty1Vcc_

typedef struct {
  uint32_T Idn;
  uint32_T VisnId;
  SnsrDataSts1Vcc Sts;
  ObjPpty1VccMdlOfMtn0 MdlOfMtn;
  ObjPpty1VccTrfcSceno0 TrfcSceno;
  Relbl4Vcc CllsnMtgtnByBrkgPrimQly;
  Relbl1Vcc CllsnMtgtnByBrkgSecQly;
  Relbl1Vcc CllsnWarnFwdQly;
  ObjPpty1VccTrfcJamAssiQly0 TrfcJamAssiQly;
  Relbl3Vcc DstLatFromMidOfLaneSelfQly;
  ObjPpty1VccEmgyLaneKeepAidPosnQly0 EmgyLaneKeepAidPosnQly;
  real32_T PosnLgtStdDe;
  real32_T PosnLatStdDe;
  real32_T AgDirStdDe;
  real32_T SpdStdDe;
  real32_T AStdDe;
  uint8_T FusnSrc;
  uint64_T Object_Age;
} ObjPpty1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjGroup1Vcc_
#define DEFINED_TYPEDEF_FOR_ObjGroup1Vcc_

typedef struct {
  ObjEstimn1Vcc Estimn;
  ObjInfo1Vcc Info;
  ObjPpty1Vcc Ppty;
} ObjGroup1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MotionType0_
#define DEFINED_TYPEDEF_FOR_MotionType0_

typedef struct {
  boolean_T Stationary;
  boolean_T MovingOncoming;
  boolean_T ParallellVehicleLongPred;
  boolean_T ParallellVehicleShortPred;
  boolean_T ObjectIsVehicle;
  boolean_T ObjectIsMotorVehicle;
  boolean_T CurvedMotion;
  boolean_T SideIsClosest;
  real32_T AbsHeading;
} MotionType0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_BoundingBox0_
#define DEFINED_TYPEDEF_FOR_BoundingBox0_

typedef struct {
  real32_T LengthSideLat;
  real32_T LengthSideLgt;
  real32_T SinRotation;
  real32_T CosRotation;
  real32_T RotationAngle;
} BoundingBox0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Offsets0_
#define DEFINED_TYPEDEF_FOR_Offsets0_

typedef struct {
  real32_T OffsLgtLongPred;
  real32_T OffsLatLongPred;
  real32_T OffsLgtShortPred;
  real32_T OffsLatShortPred;
  real32_T OffsLatManoeuvre;
  real32_T OffsLatInPathPrimaryTarget;
  real32_T OffsLatInPathCloseEdge;
  real32_T OffsLatInPathFarEdge;
  real32_T OffsLatIntersection;
  real32_T OffsLatMplTar;
} Offsets0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SafetyMarginData_
#define DEFINED_TYPEDEF_FOR_SafetyMarginData_

typedef struct {
  real32_T TimeToReachLgt;
  real32_T TimeToMiddleLgt;
  real32_T TimeToPassLgt;
  boolean_T TTMSelected;
  boolean_T InPath;
  boolean_T ObjOnCmngAndBrkg;
  real32_T ALgt;
  real32_T ALat;
  real32_T A;
  real32_T Crvt;
} SafetyMarginData;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ObjData_
#define DEFINED_TYPEDEF_FOR_ObjData_

typedef struct {
  MotionType0 MotionType;
  BoundingBox0 BoundingBox;
  boolean_T InPathAtCurrentPosition;
  boolean_T PredictionValid;
  Offsets0 Offsets;
  SafetyMarginData LongPredTime;
  SafetyMarginData ShortPredTime;
  uint32_T Idn;
} ObjData;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ConfReason_
#define DEFINED_TYPEDEF_FOR_ConfReason_

typedef enum {
  DrvDecelDelay = 0,                   /* Default value */
  HighSteerSpdDelay,
  DrvDetectRisk,
  TruckVLatConf,
  ObjJumpConf,
  ObjConfirmConf,
  BehindObjConf,
  Normal,
  CrossingInhibitFlag,
  DrvDetectNoRisk,
  DrvDetectRisk2Turn
} ConfReason;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DynCalPrm_
#define DEFINED_TYPEDEF_FOR_DynCalPrm_

typedef struct {
  real32_T CmnCalPrmForMinThdForALatAvl;
  real32_T DynCalPrmForAxleDstReToVehFrnt;
  real32_T DynCalPrmForBicycleMdlAxleDistFrnt;
  real32_T DynCalPrmForBicycleMdlCornrgStfnFrnt;
  real32_T DynCalPrmForBicycleMdlCornrgStfnRe;
  real32_T DynCalPrmForVehLen;
  real32_T DynCalPrmForVehM;
  real32_T DynCalPrmForVehSteerWhlAgRat;
  real32_T DynCalPrmForVehWghtDistbn;
  real32_T DynCalPrmForVehWhlBas;
  real32_T DynCalPrmForVehWidth;
  real32_T HalfVehWidth;
  real32_T DynCalPrmForBicycleMdlCornrgStfnFrntByVehSpd[8];
  real32_T DynCalPrmForBicycleMdlCornrgStfnReByVehSpd[8];
  real32_T DynCalPrmForFacToScaForVehALat;
  real32_T DynCalPrmForVehicleSpdForBicycleMdlCornrgStfn[8];
} DynCalPrm;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Capture_EgoInfo_
#define DEFINED_TYPEDEF_FOR_Capture_EgoInfo_

typedef struct {
  real32_T EnterCruv_HostDisSpd_kph;
  real32_T EnterCruv_HostAlgt;
} Capture_EgoInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Capture_IntvInfo_
#define DEFINED_TYPEDEF_FOR_Capture_IntvInfo_

typedef struct {
  int32_T Capture_IntvId;
  ObjClassn3Vcc Capture_IntvType;
} Capture_IntvInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PahEstimnGroup1Vcc_
#define DEFINED_TYPEDEF_FOR_PahEstimnGroup1Vcc_

typedef struct {
  real32_T CtrlAryLat[4];
  real32_T CtrlAryLgt[4];
  real32_T TiAry[2];
} PahEstimnGroup1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RqrdALgtLogging_
#define DEFINED_TYPEDEF_FOR_RqrdALgtLogging_

typedef struct {
  real32_T AgDirRel;
  real32_T PosnLgtRel;
  real32_T PosnLatRel;
  real32_T CloseEdgeDistance;
  real32_T FarEdgeDistance;
  real32_T TTR;
  real32_T TTP;
  uint32_T Idn;
  real32_T VLatRel;
} RqrdALgtLogging;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VehSelfData_
#define DEFINED_TYPEDEF_FOR_VehSelfData_

typedef struct {
  real32_T Curvature;
  real32_T CurvatureRate;
  real32_T CurvatureRadius;
  real32_T DrvrALgt;
  boolean_T CMbBActive;
  uint8_T EgoMotionType;
} VehSelfData;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MtnRqrdLTAP_
#define DEFINED_TYPEDEF_FOR_MtnRqrdLTAP_

typedef struct {
  real32_T ANegLgtRqrd;
  real32_T APosLgtRqrd;
  real32_T CrvtRateRqrdLe;
  real32_T CrvtRateRqrdRi;
  real32_T CrvtRqrdLe;
  real32_T CrvtRqrdRi;
  real32_T JerkNegLgtRqrd;
} MtnRqrdLTAP;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VehicleState_
#define DEFINED_TYPEDEF_FOR_VehicleState_

typedef struct {
  real32_T c0;
  real32_T v0;
  real32_T a0;
  real32_T amin;
  real32_T tj_brake;
  real32_T amax;
  real32_T tj_accel;
  real32_T cmax;
  real32_T L;
  real32_T W;
  real32_T d;
  real32_T ttheta_left;
  real32_T ttheta_right;
} VehicleState;

#endif

#ifndef DEFINED_TYPEDEF_FOR_LtapLgtInpathSts_
#define DEFINED_TYPEDEF_FOR_LtapLgtInpathSts_

typedef enum {
  LtapLgtInpathSts_NotInpath = 0,      /* Default value */
  LtapLgtInpathSts_Stright_PartInPathFrontHost,
  LtapLgtInpathSts_Stright_EntireInPathFrontHost,
  LtapLgtInpathSts_Turn_PartInPathFrontHost,
  LtapLgtInpathSts_Turn_EntireInPathFrontHost,
  LtapLgtInpathSts_IsInPathFrontHost,
  LtapLgtInpathSts_Stright_NotInpath,
  LtapLgtInpathSts_Turn_NotInpath,
  LtapLgtInpathSts_Turn_IntersectionExist,
  LtapLgtInpathSts_Turn_IntersectionValidArea,
  LtapLgtInpathSts_Turn_AllLineInArea
} LtapLgtInpathSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PinionSteerAgGroup_
#define DEFINED_TYPEDEF_FOR_PinionSteerAgGroup_

typedef struct {
  uint8_T PinionSteerAgGroupCntr;
  uint8_T PinionSteerAgGroupChks;
  GenQf1 PinionSteerAgGroupSteerWhlTqQf;
  real32_T PinionSteerAgGroupSteerWhlTq;
  GenQf1 PinionSteerAgGroupPinionSteerAgSpd1Qf;
  real32_T PinionSteerAgGroupPinionSteerAgSpd1;
  GenQf1 PinionSteerAgGroupPinionSteerAg1Qf;
  real32_T PinionSteerAgGroupPinionSteerAg1;
} PinionSteerAgGroup;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VehMtnSt2_
#define DEFINED_TYPEDEF_FOR_VehMtnSt2_

typedef uint8_T VehMtnSt2;

/* enum VehMtnSt2 */
#define VehMtnSt2_Ukwn                 ((VehMtnSt2)0U)           /* Default value */
#define VehMtnSt2_StandStillVal1       ((VehMtnSt2)1U)
#define VehMtnSt2_StandStillVal2       ((VehMtnSt2)2U)
#define VehMtnSt2_StandStillVal3       ((VehMtnSt2)3U)
#define VehMtnSt2_RollgFwdVal1         ((VehMtnSt2)4U)
#define VehMtnSt2_RollgFwdVal2         ((VehMtnSt2)5U)
#define VehMtnSt2_RollgBackwVal1       ((VehMtnSt2)6U)
#define VehMtnSt2_RollgBackwVal2       ((VehMtnSt2)7U)
#endif

#ifndef DEFINED_TYPEDEF_FOR_RoadPpty1Vcc_
#define DEFINED_TYPEDEF_FOR_RoadPpty1Vcc_

typedef struct {
  real32_T LaneWidth;
  real32_T OffsLat;
  real32_T AgDir;
  real32_T Crvt;
  real32_T CrvtRate[3];
  real32_T SegLen[3];
  NoYes1Vcc Strtd;
  NoYes1Vcc Vld;
  real32_T TiToHiQly[32];
  uint32_T ObjIdTiToHiQly[32];
} RoadPpty1Vcc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DynCalPrmForJapanMod0_
#define DEFINED_TYPEDEF_FOR_DynCalPrmForJapanMod0_

typedef enum {
  DynCalPrmForJapanMod0_TRUE = 1,      /* Default value */
  DynCalPrmForJapanMod0_FALSE = 0
} DynCalPrmForJapanMod0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DynCalPrmDSE_
#define DEFINED_TYPEDEF_FOR_DynCalPrmDSE_

typedef struct {
  real32_T DynCalPrmForBicycleMdlAxleDistFrnt;
  real32_T DynCalPrmForBicycleMdlCornrgStfnFrnt;
  real32_T DynCalPrmForBicycleMdlCornrgStfnRe;
  DynCalPrmForJapanMod0 DynCalPrmForJapanMod;
  real32_T DynCalPrmForSteerGrdt;
  real32_T DynCalPrmForVehLen;
  real32_T DynCalPrmForVehM;
  real32_T DynCalPrmForVehSteerWhlAgRat;
  real32_T DynCalPrmForVehWghtDistbn;
  real32_T DynCalPrmForVehWhlBas;
  real32_T DynCalPrmForVehWidth;
} DynCalPrmDSE;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DiagPathSelection0_
#define DEFINED_TYPEDEF_FOR_DiagPathSelection0_

typedef struct {
  DiagcBusForDrvrStEstimr1VccUseRoadBasedPath0 UseRoadBasedPath;
  real32_T ACenterMin;
  real32_T ACenterMax;
  real32_T ACenterInitial;
} DiagPathSelection0;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MachineSts_
#define DEFINED_TYPEDEF_FOR_MachineSts_

typedef struct {
  uint8_T AEBState;
  uint8_T FCWState;
  uint8_T AWBState;
  uint8_T AWB_Level;
  uint8_T HBAState;
  uint8_T HBA_Level;
  uint8_T PrefillState;
  uint8_T DWState;
} MachineSts;

#endif

#ifndef DEFINED_TYPEDEF_FOR_LgSf_Ltap_T_
#define DEFINED_TYPEDEF_FOR_LgSf_Ltap_T_

typedef struct {
  MachineSts StateMachine;
  DIAG_AEBFunc AEBFunc;
} LgSf_Ltap_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AebState_
#define DEFINED_TYPEDEF_FOR_AebState_

typedef uint8_T AebState;

/* enum AebState */
#define Aeb_Off                        ((AebState)0U)            /* Default value */
#define Aeb_Fault                      ((AebState)1U)
#define Aeb_Passive                    ((AebState)2U)
#define Aeb_Standby                    ((AebState)3U)
#define Prefill_Active                 ((AebState)4U)
#define Aeb_Active                     ((AebState)5U)
#define Eba_Active                     ((AebState)6U)
#endif

#ifndef DEFINED_TYPEDEF_FOR_FcwState_
#define DEFINED_TYPEDEF_FOR_FcwState_

typedef uint8_T FcwState;

/* enum FcwState */
#define Fcw_Off                        ((FcwState)0U)            /* Default value */
#define Fcw_Fault                      ((FcwState)1U)
#define Fcw_Passive                    ((FcwState)2U)
#define Fcw_Standby                    ((FcwState)3U)
#define Fcw_FirstLevel                 ((FcwState)4U)
#define Fcw_SecondLevel                ((FcwState)5U)
#define Fcw_ThirdLevel                 ((FcwState)6U)
#endif

#ifndef DEFINED_TYPEDEF_FOR_AwbState_
#define DEFINED_TYPEDEF_FOR_AwbState_

typedef uint8_T AwbState;

/* enum AwbState */
#define Awb_Off                        ((AwbState)0U)            /* Default value */
#define Awb_Fault                      ((AwbState)1U)
#define Awb_Passive                    ((AwbState)2U)
#define Awb_Standby                    ((AwbState)3U)
#define Awb_Active                     ((AwbState)4U)
#endif

#ifndef DEFINED_TYPEDEF_FOR_LgSf_CibDebug_T_
#define DEFINED_TYPEDEF_FOR_LgSf_CibDebug_T_

typedef struct {
  boolean_T LgSf_ObjTOI;
  uint8_T LgSf_ObjInPathAge;
  uint8_T LgSf_ObjInPathAgeThres;
  uint8_T LgSf_DriveEngage;
  uint16_T LgSf_ObjU16Resv1;
  uint16_T LgSf_ObjTOIFlag;
  real32_T LgSf_ObjLeadVel;
  real32_T LgSf_ObjTTC;
  real32_T LgSf_ObjDesiredHitSpd;
  real32_T LgSf_BaseRange;
  real32_T LgSf_DistNear;
  real32_T LgSf_ObjXolc;
  real32_T LgSf_HitDist;
  real32_T LgSf_YawDist;
  real32_T LgSf_HBOffset;
  real32_T LgSf_LBOffset;
  real32_T LgSf_PFOffset;
  real32_T LgSf_IBAOffset;
  real32_T LgSf_ABAOffset;
  real32_T LgSf_OverallRdcFac;
  real32_T LgSf_EbaOverallRdcFac;
  real32_T LgSf_NearTgtRdcFac;
  real32_T LgSf_VehBehvRdcFac;
  real32_T LgSf_XolcRdcFac;
  real32_T LgSf_HBRangeThres;
  real32_T LgSf_LBRangeThres;
  real32_T LgSf_PFRangeThres;
  real32_T LgSf_IBARangeThres;
  real32_T LgSf_ABARangeThres;
  real32_T LgSf_ReqDecelCloseLoop;
  real32_T LgSf_ReqDecel;
  boolean_T LgSf_DecelRelease;
  boolean_T LgSf_ABAReq;
  boolean_T LgSf_HoldReq;
  uint8_T LgSf_BrkLevel;
  uint16_T LgSf_EbaReqFlag;
  uint16_T LgSf_HBReqFlag;
  uint16_T LgSf_LBReqFlag;
  uint16_T LgSf_PFReqFlag;
  uint16_T LgSf_ABAReqFlag;
  uint16_T LgSf_U16Reserve;
} LgSf_CibDebug_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_LgSf_FcwDebug_T_
#define DEFINED_TYPEDEF_FOR_LgSf_FcwDebug_T_

typedef struct {
  real32_T LgSf_FcwTTCThres;
  real32_T LgSf_ObjTTC;
  boolean_T LgSf_ChimeSuppress;
  boolean_T LgSf_LatWarningReq;
  boolean_T LgSf_PreWarningReq;
  boolean_T LgSf_AWBReq;
  uint8_T LgSf_AWBLevel;
  uint8_T LgSf_U8Resv1;
  uint8_T LgSf_U8Resv2;
  uint8_T LgSf_U8Resv3;
  uint16_T LgSf_ChimeSuppressFlag;
  uint16_T LgSf_LatWarningFlag;
  uint16_T LgSf_PreWarningFlag;
  uint16_T LgSf_AWBFlag;
} LgSf_FcwDebug_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_LgSf_LongScene_T_
#define DEFINED_TYPEDEF_FOR_LgSf_LongScene_T_

typedef struct {
  real32_T LgSf_TarReqDecel;
  boolean_T LgSf_AebReq;
  boolean_T LgSf_AebTarDecVld;
  uint8_T LgSf_AwbReqLvl;
  boolean_T LgSf_AbaReq;
  uint8_T LgSf_AbaLvl;
  boolean_T LgSf_HWReq;
  boolean_T LgSf_HaLightReq;
  boolean_T LgSf_BeltReq;
  AebState LgSf_AebState;
  FcwState LgSf_FcwState;
  AwbState LgSf_AwbState;
  uint16_T LgSg_ShadowMode;
  int32_T LgSf_ObjId;
  int32_T LgSf_ObjVisId;
  int32_T LgSf_ObjClass;
  real32_T LgSf_ObjPosX;
  real32_T LgSf_ObjPosY;
  real32_T LgSf_ObjVelX;
  real32_T LgSf_ObjVelY;
  real32_T LgSf_ObjAccX;
  real32_T LgSf_ObjAccY;
  real32_T LgSf_ObjTTC;
  LgSf_CibDebug_T cib;
  LgSf_FcwDebug_T fcw;
} LgSf_LongScene_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_LgSf_DiagInfo_T_
#define DEFINED_TYPEDEF_FOR_LgSf_DiagInfo_T_

typedef struct {
  uint32_T LgSf_InhibitMask;
  uint32_T LgSf_DiagFlag;
} LgSf_DiagInfo_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_LgSafe_T_
#define DEFINED_TYPEDEF_FOR_LgSafe_T_

typedef struct {
  LgSf_LongScene_T LgSf_LongScene;
  LgSf_Ltap_T LgSf_Ltap;
  LgSf_DiagInfo_T LgSf_Diag;
  uint8_T LgSf_UseLtap;
  uint8_T LgSf_MajorVersion;
  uint8_T LgSf_MinorVersion;
  uint8_T LgSf_RLC;
} LgSafe_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsTargetInfo_T_
#define DEFINED_TYPEDEF_FOR_AsTargetInfo_T_

typedef struct {
  uint32_T id;
  uint32_T type;
  uint32_T source;
  real32_T posx;
  real32_T posy;
  real32_T spdx;
  real32_T spdy;
  real32_T accelx;
  real32_T accely;
  real32_T heading;
  real32_T ttc;
} AsTargetInfo_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsCmdLgSafe_T_
#define DEFINED_TYPEDEF_FOR_AsCmdLgSafe_T_

typedef struct {
  AsTargetInfo_T lgsf_target;
  real32_T aeb_tar_dec;
  uint32_T hold_type;
  boolean_T aeb_req;
  boolean_T awb_req;
  boolean_T prefill_req;
  boolean_T aba_req;
  boolean_T belt_req;
  uint8_T aeb_status;
  uint8_T fcw_status;
  uint8_T fcw_mode;
  uint8_T aba_level;
  uint8_T awb_level;
  boolean_T aeb_req_valid;
  uint8_T shadow_mode;
  uint32_T resv1;
  real32_T resv2;
  real32_T resv3;
} AsCmdLgSafe_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsDisplayLgSafe_T_
#define DEFINED_TYPEDEF_FOR_AsDisplayLgSafe_T_

typedef struct {
  AsTargetInfo_T target_lgsf;
  uint32_T target_color;
  uint32_T fcw_sts;
  uint32_T aeb_sts;
  uint32_T fcw_warn_dist;
  uint32_T fcw_active_sts;
  uint32_T aeb_active_sts;
  uint32_T fcw_aeb_text_info;
  uint32_T driving_sound_warn;
} AsDisplayLgSafe_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_w6CpqOprWE2lahr4C3QteG_
#define DEFINED_TYPEDEF_FOR_struct_w6CpqOprWE2lahr4C3QteG_

typedef struct {
  real32_T PredPosnLgt;
  real32_T PredVLgtObj;
  real32_T PredALgtObj;
  real32_T PredPosnLat;
  real32_T PredVLatObj;
  real32_T PredALatObj;
} struct_w6CpqOprWE2lahr4C3QteG;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_LongSafe_SWC_T RT_MODEL_LongSafe_SWC_T;

#endif                                 /* RTW_HEADER_LongSafe_SWC_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
