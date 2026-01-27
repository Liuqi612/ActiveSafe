/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */

#pragma once
#include <cstddef>
#include <cstdint>
namespace senseAD {
namespace tap {
// LongSafe
typedef struct {
  uint8_t LgSf_ObjTOI;
  uint8_t LgSf_ObjInPathAge;
  uint8_t LgSf_ObjInPathAgeThres;
  uint8_t LgSf_DriveEngage;
  uint16_t LgSf_ObjU16Resv1;
  uint16_t LgSf_ObjTOIFlag;
  float LgSf_ObjLeadVel;
  float LgSf_ObjTTC;
  float LgSf_ObjDesiredHitSpd;
  float LgSf_BaseRange;
  float LgSf_DistNear;
  float LgSf_ObjXolc;
  float LgSf_HitDist;
  float LgSf_YawDist;
  float LgSf_HBOffset;
  float LgSf_LBOffset;
  float LgSf_PFOffset;
  float LgSf_IBAOffset;
  float LgSf_ABAOffset;
  float LgSf_OverallRdcFac;
  float LgSf_EbaOverallRdcFac;
  float LgSf_NearTgtRdcFac;
  float LgSf_VehBehvRdcFac;
  float LgSf_XolcRdcFac;
  float LgSf_HBRangeThres;
  float LgSf_LBRangeThres;
  float LgSf_PFRangeThres;
  float LgSf_IBARangeThres;
  float LgSf_ABARangeThres;
  float LgSf_ReqDecelCloseLoop;
  float LgSf_ReqDecel;
  uint8_t LgSf_DecelRelease;
  uint8_t LgSf_ABAReq;
  uint8_t LgSf_HoldReq;
  uint8_t LgSf_BrkLevel;
  uint16_t LgSf_EbaReqFlag;
  uint16_t LgSf_HBReqFlag;
  uint16_t LgSf_LBReqFlag;
  uint16_t LgSf_PFReqFlag;
  uint16_t LgSf_ABAReqFlag;
  uint16_t LgSf_U16Resv1;
} LgSf_CibDebug_T;

typedef struct {
  float LgSf_FcwTTCThres;
  float LgSf_ObjTTC;
  uint8_t LgSf_ChimeSuppress;
  uint8_t LgSf_LatWarningReq;
  uint8_t LgSf_PreWarningReq;
  uint8_t LgSf_AWBReq;
  uint8_t LgSf_AWBLevel;
  uint8_t LgSf_U8Resv1;
  uint8_t LgSf_U8Resv2;
  uint8_t LgSf_U8Resv3;
  uint16_t LgSf_ChimeSuppressFlag;
  uint16_t LgSf_LatWarningFlag;
  uint16_t LgSf_PreWarningFlag;
  uint16_t LgSf_AWBFlag;
} LgSf_FcwDebug_T;

enum class AebState : uint8_t {
  Aeb_Off,
  Aeb_Fault,
  Aeb_Passive,
  Aeb_Standby,
  Prefill_Active,
  Aeb_Active,
  Eba_Active
};

enum class FcwState : uint8_t {
  Fcw_Off,
  Fcw_Fault,
  Fcw_Passive,
  Fcw_Standby,
  Fcw_FirstLevel,
  Fcw_SecondLevel,
  Fcw_ThirdLevel
};
enum class AwbState : uint8_t {
  Awb_Off,
  Awb_Fault,
  Awb_Passive,
  Awb_Standby,
  Awb_Active
};

typedef struct {
  float LgSf_TarReqDecel;
  uint8_t LgSf_AebReq;
  uint8_t LgSf_AebTarDecVld;
  uint8_t LgSf_AwbReqLvl;
  uint8_t LgSf_AbaReq;
  uint8_t LgSf_AbaLvl;
  uint8_t LgSf_HWReq;
  uint8_t LgSf_HaLightReq;
  uint8_t LgSf_BeltReq;
  AebState LgSf_AebState;
  FcwState LgSf_FcwState;
  AwbState LgSf_AwbState;
  uint16_t LgSf_ShadowMode;
  int32_t LgSf_ObjId;
  int32_t LgSf_ObjVisId;
  int32_t LgSf_ObjClass;
  float LgSf_ObjPosX;
  float LgSf_ObjPosY;
  float LgSf_ObjVelX;
  float LgSf_ObjVelY;
  float LgSf_ObjAccX;
  float LgSf_ObjAccY;
  float LgSf_ObjTTC;
  LgSf_CibDebug_T cib;
  LgSf_FcwDebug_T fcw;
} LgSf_LongScene_T;

typedef struct {
  uint8_t AEBState;
  uint8_t FCWState;
  uint8_t AWBState;
  uint8_t AWB_Level;
  uint8_t HBAState;
  uint8_t HBA_Level;
  uint8_t PrefillState;
  uint8_t DWState;
} MachineSts;

typedef struct {
  float ALatRqrd;
  int32_t ALatRqrdQly;
  float APosLgtRqrd;
  float ANegLgtRqrd;
  float JerkNegLgtRqrd;
  float CrvtRateRqrdLe;
  float CrvtRateRqrdRi;
  float CrvtRqrdLe;
  float CrvtRqrdRi;
} MtnRqrdIntv;

typedef struct {
  float ALatRqrd;
  int32_t ALatRqrdQly;
  float ANegLgtRqrdForWarn;
  float ANegLgtRqrdForIntv;
} MtnRqrdWarn;

typedef struct {
  MtnRqrdIntv MtnRqrd_Intv;
  MtnRqrdWarn MtnRqrd_Warn;
  float ANegLgtRqrdForPrimTarWarn;
} MtnRqrd_DIAG;

typedef struct {
  float PreBrakeAccReqLimit;
  float FullBrakeAccelerationRequest;
} DIAG_AccelRequest;

typedef struct {
  uint8_t Deactivate;
  uint8_t VehicleStationaryLongerThanXSeconds;
  uint8_t CollisionAvoidedByBraking;
  uint8_t ObjConfNotOK;
  uint8_t ObjIdChanged;
  uint8_t DelayDeactivation;
  uint8_t ObjStateDeactivation;
  uint8_t reserved;
} DIAG_Deactivate;

typedef struct {
  uint8_t TargetHighCurvature;
  uint8_t TargetAngleNotValid;
  uint8_t reserved1;
  uint8_t reserved2;
  float HostCrvt;
  uint8_t RecentSCurve;
  uint8_t NotTurningNow;
  uint8_t NoRecentAngleSpeed;
  uint8_t NoRecentStart;
  uint8_t MoreHeadOn;
  uint8_t IsVehicleOfUnknownClass;
  uint8_t reserved3;
  uint8_t reserved4;
} DIAG_OncomingInhibit;

typedef struct {
  uint8_t SpdInhibit;
  uint8_t reserved;
  uint8_t HostAvoidInhibit;
  uint8_t HostDrivingStraightAndTargetIsOncoming;
  DIAG_OncomingInhibit OncomingInhibit;
} DIAG_CommonInhibit;

typedef struct {
  uint8_t FullBrakingThreat;
  uint8_t SteeringThreat;
  uint8_t BrakingThreat;
  uint8_t AccelerationThreat;
  uint8_t ObjectConfOk;
  uint8_t reserved1;
  uint8_t reserved2;
  uint8_t reserved3;
} DIAG_Fullbraking;

typedef struct {
  uint8_t PreBrakingThreat;
  uint8_t SteeringThreat;
  uint8_t BrakingThreat;
  uint8_t AccelerationThreat;
  uint8_t ObjConfOK;
  uint8_t reserved1;
  uint8_t reserved2;
  uint8_t reserved3;
} DIAG_PreBraking;

typedef struct {
  DIAG_Deactivate Deactivate;
  DIAG_CommonInhibit CommonInhibit;
  DIAG_Fullbraking Fullbraking;
  DIAG_PreBraking PreBraking;
} DIAG_CritLgtEval;

typedef struct {
  DIAG_AccelRequest AccelRequest;
  DIAG_CritLgtEval CritLgtEval;
  uint8_t CMbBStatus;
  uint8_t reserved1;
  uint8_t reserved2;
  uint8_t reserved3;
} CMBB_DIAG;

typedef struct {
  uint8_t Btn_AboveLimit;
  float brakeThreatNumber;
  uint8_t objectIsValid;
  uint8_t driverCanNotEasilySteerAway;
  uint8_t BtnTrigger;
  uint8_t cmbbTrigger;
  uint8_t visionOnlyTrigger;
  uint8_t startConditionsMet;
  uint8_t warningType;
  uint8_t brakeGainConditionsMet;
  uint8_t comfortDistanceTrigger;
  uint8_t BrakeGainConditionsBit;
  uint8_t warningState;
  uint8_t resv1;
} Diag_StartConditions;

typedef struct {
  uint8_t inhibitFcw;
  uint8_t belowLowSpeedLimit;
  uint8_t vehicleNotRollingForward;
  uint8_t fcwDisabledByFaultManager;
  uint8_t SceniaroCheckNotOk;
  uint8_t resv1;
  uint8_t resv2;
  uint8_t resv3;
} Diag_InhibitCdnSts;

typedef struct {
  float DecelReq;
  uint8_t DecelEna;
  float BrkGainReq;
  float BrkGainMaxDecel;
  uint8_t BrkGainEna;
  uint8_t CllsnThreat;
  uint8_t BltLvl;
  uint8_t DwActive;
  uint8_t WarnReq;
  uint8_t WarnObjType;
} CllsnFwdWarnCtrl_Debug;

typedef struct {
  Diag_StartConditions StartConditions;
  Diag_InhibitCdnSts InhibitCdnSts;
  CllsnFwdWarnCtrl_Debug ActtnDataFromCllsnFwdWarnCtrl;
  uint8_t resv1;
  uint8_t resv2;
} FCW_DIAG;

typedef struct {
  uint8_t CllsnThreat;
  uint8_t BrkArbResult;
  uint8_t AsySftyDecelReqDendBySpdRedn;
  uint8_t reserved;
  float DecelRequestBrkArb;
} BrkArb_DIAG;

typedef struct {
  uint8_t EgoMotionType;
  uint8_t SceniaroClass;
  uint8_t AEBSceniaroResult;
  uint8_t FCWSceniaroResult;
  uint8_t ConfDelay;
  uint8_t SceniaroFailReason;
  uint8_t reserved1;
  uint8_t reserved2;
} Sceniaro_DIAG;

typedef struct {
  MtnRqrd_DIAG MtnRqrd;
  CMBB_DIAG CMBB;
  FCW_DIAG FCW;
  BrkArb_DIAG BrkArb;
  Sceniaro_DIAG Sceniaro;
} DIAG_AEBFunc;

typedef struct {
  MachineSts StateMachine;
  DIAG_AEBFunc AEBFunc;
} LgSf_Ltap_T;

typedef struct {
  uint32_t LgSf_InhibitMask;
  uint32_t LgSf_DiagFlag;
} LgSf_DiagInfo_T;

typedef struct {
  LgSf_LongScene_T LgSf_LongScene;
  LgSf_Ltap_T LgSf_Ltap;
  LgSf_DiagInfo_T LgSf_Diag;
  uint8_t LgSf_UseLtap;
  uint8_t LgSf_MajorVersion;
  uint8_t LgSf_MinorVersion;
  uint8_t LgSf_RLC;
} LgSafe_T;

// CTS
typedef struct {
  uint8_t Cta_Main_Switch;
  uint8_t Actual_Gear;
  uint8_t Risk_Side_Infreezing;
  uint8_t Inhibit;
  uint8_t Left_Alert;
  uint8_t Right_Alert;
  uint8_t Padding[2];
  float Active_Time;
  uint8_t On_Max_Active_Time;
  uint8_t Deactive;
  uint8_t Main_state;
  uint8_t Run_State;
} Cta_T;

typedef struct {
  uint8_t Ctb_Main_Switch;
  uint8_t Infreezing;
  uint8_t Inhibit;
  uint8_t Padding;
  float TTC;
  float TTC_Thrd;
  uint8_t Active;
  uint8_t Deactive;
  uint8_t Main_state;
  uint8_t Run_State;
} Ctb_T;

typedef struct {
  Cta_T Fcta;
  Ctb_T Fctb;
  Cta_T Rcta;
  Ctb_T Rctb;
  uint8_t Cts_MajorVersion;
  uint8_t Cts_MinorVersion;
  uint8_t Cts_RLC;
  uint8_t Padding;
} Cts_T;

typedef struct {
  LgSafe_T lgsf;
  Cts_T cts;
  uint8_t dowState;
  uint8_t rcwState;
  uint8_t bsdState;
} AsControl_T;
} // namespace tap
} // namespace senseAD
