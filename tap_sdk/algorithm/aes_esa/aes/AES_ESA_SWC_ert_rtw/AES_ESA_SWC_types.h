/*
 * File: AES_ESA_SWC_types.h
 *
 * Code generated for Simulink model 'AES_ESA_SWC'.
 *
 * Model version                  : 7.1509
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Mon Sep 14 15:48:50 2026
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

#ifndef RTW_HEADER_AES_ESA_SWC_types_h_
#define RTW_HEADER_AES_ESA_SWC_types_h_
#include "rtwtypes.h"
#include "AES_SceneType.h"

/* Model Code Variants */
#ifndef DEFINED_TYPEDEF_FOR_LaneMarker_t_
#define DEFINED_TYPEDEF_FOR_LaneMarker_t_

typedef struct {
  uint8_T LineObjectsRollingCounter;
  uint8_T LineValid;
  uint8_T LineColor;
  uint8_T LineType;
  real32_T LineConf;
  real32_T LineViewRangeStart;
  real32_T LineViewRangeEnd;
  real32_T LineMakerWidth;
  real32_T LinePolyC0;
  real32_T LinePolyC1;
  real32_T LinePolyC2;
  real32_T LinePolyC3;
} LaneMarker_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_RoadEdge_t_
#define DEFINED_TYPEDEF_FOR_RoadEdge_t_

typedef struct {
  uint8_T LineObjectsRollingCounter;
  uint8_T LineValid;
  uint8_T LineColor;
  uint8_T LineType;
  real32_T LineConf;
  real32_T LineViewRangeStart;
  real32_T LineViewRangeEnd;
  real32_T LineMakerWidth;
  real32_T LinePolyC0;
  real32_T LinePolyC1;
  real32_T LinePolyC2;
  real32_T LinePolyC3;
} RoadEdge_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_LanesInfo_
#define DEFINED_TYPEDEF_FOR_LanesInfo_

typedef struct {
  uint64_T seq_num;
  uint64_T time;
  LaneMarker_t HostLeftLaneMarker;
  LaneMarker_t HostRightLaneMarker;
  LaneMarker_t LeftLaneLeftLaneMarker;
  LaneMarker_t LeftLaneRightLaneMarker;
  LaneMarker_t RightLaneLeftLaneMarker;
  LaneMarker_t RightLaneRightLaneMarker;
  LaneMarker_t RearLaneLeftLaneMarker;
  LaneMarker_t RearLaneRightLaneMarker;
  RoadEdge_t LeftRoadEdge;
  RoadEdge_t RightRoadEdge;
} LanesInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VehicleConfig_
#define DEFINED_TYPEDEF_FOR_VehicleConfig_

typedef struct {
  real32_T k_dist_to_rear_axle;
  real32_T k_host_width;
  real32_T k_host_length;
  real32_T k_steer_gradient;
  real32_T k_rear_cornering_compliance;
  real32_T k_steer_ratio;
  real32_T k_wheel_base;
  real32_T k_vcs_camera_long_posn;
  real32_T k_vcs_camera_lat_posn;
} VehicleConfig;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsVseOut_
#define DEFINED_TYPEDEF_FOR_AsVseOut_

typedef struct {
  VehicleConfig config;
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
  real32_T steerwheelangle;
  real32_T steerwheelangle_rate;
  real32_T slope_long_rad;
  real32_T slope_lat_rad;
  real32_T gas_pedal_pos;
  real32_T brake_pedal_pos;
  real32_T brake_pressure;
  real32_T torsion_bar_trq;
  real32_T gas_pedal_pos_rate;
  real32_T brake_pedal_pos_rate;
  real32_T brake_pressure_rate;
  uint8_T hazard_lamp_st;
  uint8_T front_fog_lamp_st;
  uint8_T back_fog_lamp_st;
  uint8_T left_light_fault_st;
  uint8_T right_light_fault_st;
  uint8_T epb_applied;
  uint8_T high_beam_st;
  uint8_T vdc_active_st;
  uint8_T veh_dyn_cntl_stat;
  uint8_T tcs_active_st;
  uint8_T hdc_active_st;
  uint8_T esc_off_st;
  uint8_T airbag_virt_dev_avl;
  uint8_T tire_presr_fault;
  uint8_T lka_trq_ovl_dlvd_stat;
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
  uint8_T esa_switch;
  uint8_T aes_switch;
  uint8_T bsd_switch;
  uint8_T dow_switch;
  uint8_T fctb_switch;
  uint8_T rctb_switch;
  uint8_T rcw_switch;
  boolean_T brake_pedal_apld;
  boolean_T abs_active;
  boolean_T aeb_active;
  uint8_T power_mode;
  boolean_T long_ctrl_brake_active;
  boolean_T straight_driving;
  uint32_T esp_brake_available_st;
  uint32_T function_did_config;
  uint64_T veh_time_stamp;
} AsVseOut;

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
  uint8_T cmbb_primary_confidence;
  uint8_T fcw_confidence;
  uint8_T maturity;
  uint8_T visTrkID;
  uint8_T f_oncoming;
  uint8_T track_id;
  uint8_T oncom_confidence;
  uint8_T collision_prob;
} AsOnComingObject;

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
  uint8_T fusTrkID;
  uint8_T track_id;
  uint8_T pad0;
  uint8_T pad1;
  uint8_T pad2;
} AsOverTakingObject;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ElkInfo_
#define DEFINED_TYPEDEF_FOR_ElkInfo_

typedef struct {
  AsOnComingObject oncom_target1;
  AsOnComingObject oncom_target2;
  AsOnComingObject oncom_target3;
  AsOverTakingObject overtake_target_rear_left;
  AsOverTakingObject overtake_target_rear_right;
  AsOverTakingObject overtake_target_front_left;
  AsOverTakingObject overtake_target_front_right;
} ElkInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AsTarget_
#define DEFINED_TYPEDEF_FOR_AsTarget_

typedef struct {
  uint32_T id;
  uint8_T type;
  uint8_T source;
  uint8_T color;
  uint8_T padding;
  real32_T posX;
  real32_T posY;
  real32_T spdX;
  real32_T spdY;
  real32_T accelX;
  real32_T accelY;
  real32_T heading;
  real32_T length;
  real32_T width;
  real32_T ttc;
  uint8_T fcw_active;
} AsTarget;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AS_FusObject_
#define DEFINED_TYPEDEF_FOR_AS_FusObject_

typedef struct {
  uint8_T track_id;
  uint8_T vis_trk_id;
  uint16_T age;
  int32_T fus_trkID;
  int32_T vis_trkID;
  real32_T speed;
  real32_T lat_posn;
  real32_T long_posn;
  real32_T lat_vel;
  real32_T long_vel;
  real32_T lat_accel;
  real32_T long_accel;
  real32_T heading;
  real32_T confidence;
  uint8_T status;
  uint8_T object_class;
  uint8_T fusion_source;
  uint8_T resv1;
  real32_T length;
  real32_T width;
  real32_T height;
} AS_FusObject;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AS_FusionInfo_
#define DEFINED_TYPEDEF_FOR_AS_FusionInfo_

typedef struct {
  uint32_T look_index;
  uint64_T time;
  AS_FusObject trk[96];
  uint32_T gop_cnt;
  uint64_T gop_time;
} AS_FusionInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Reserved_Input_
#define DEFINED_TYPEDEF_FOR_Reserved_Input_

typedef struct {
  uint32_T aes_uint32_digmsk;
  boolean_T last_aes_active;
  uint32_T aes_uint32_reserv1;
  uint32_T aes_uint32_reserv2;
  uint32_T aes_uint32_reserv3;
  real32_T aes_float_reserv1;
  real32_T aes_float_reserv2;
  real32_T aes_float_reserv3;
} Reserved_Input;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Heading_Ctrl_Info_T_
#define DEFINED_TYPEDEF_FOR_Heading_Ctrl_Info_T_

typedef struct {
  real32_T LAT_Ctrl_Torq_HedingAngle;
  real32_T LAT_Ctrl_Torq_HedCtrl_P;
  real32_T LAT_Ctrl_Torq_HedCtrl_D;
  real32_T LAT_Ctrl_Gain_P_HedCtrl;
  real32_T LAT_Ctrl_Gain_D_HedCtrl;
} Heading_Ctrl_Info_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Lat_Offset_Ctrl_Info_T_
#define DEFINED_TYPEDEF_FOR_Lat_Offset_Ctrl_Info_T_

typedef struct {
  real32_T LAT_Ctrl_Torq_LatOffset;
  real32_T LAT_Ctrl_Torq_P_LatOfset;
  real32_T LAT_Ctrl_Torq_I_LatOfset;
  real32_T LAT_Ctrl_Torq_D_LatOfset;
  real32_T LAT_Ctrl_Torq_P_Near;
  real32_T LAT_Ctrl_Torq_P_Far;
  real32_T LAT_Ctrl_Torq_I_Near;
  real32_T LAT_Ctrl_Torq_I_Far;
  real32_T LAT_Ctrl_Gain_D_LatOfset;
  real32_T LAT_Ctrl_Gain_I_LatOfset;
  real32_T LAT_Ctrl_Gain_P_Near;
  real32_T LAT_Ctrl_Gain_P_Far;
} Lat_Offset_Ctrl_Info_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PID_Control_Signals_T_
#define DEFINED_TYPEDEF_FOR_PID_Control_Signals_T_

typedef struct {
  real32_T LAT_Ctrl_Var_Far_Offset;
  real32_T LAT_Ctrl_Var_Near_Offset;
  real32_T LAT_Ctrl_Var_HedAngle;
  real32_T LAT_Ctrl_Var_LatRate;
  real32_T LAT_Ctrl_Var_HedRate;
} PID_Control_Signals_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_I_Term_CtrlState_T_
#define DEFINED_TYPEDEF_FOR_I_Term_CtrlState_T_

typedef struct {
  boolean_T LAT_Ctrl_IS_I_Reset;
  boolean_T LAT_Ctrl_IS_I_Frozen;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
} I_Term_CtrlState_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Veh_Pos_and_Lane_Info_T_
#define DEFINED_TYPEDEF_FOR_Veh_Pos_and_Lane_Info_T_

typedef struct {
  boolean_T LAT_Ctrl_IS_Staight_Lane;
  boolean_T LAT_Ctrl_IS_In_Lane_Central;
  boolean_T LAT_Ctrl_IS_In_InnerCurv_Far;
  boolean_T LAT_Ctrl_IS_In_InnerCurv_Near;
  boolean_T LAT_Ctrl_IS_Lft_Curv;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Veh_Pos_and_Lane_Info_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Curve_Parameters_T_
#define DEFINED_TYPEDEF_FOR_Curve_Parameters_T_

typedef struct {
  int16_T LAT_Ctrl_Var_Lane_Radius;
  uint16_T uint16_reserve1;
  real32_T LAT_Ctrl_Var_Near_Curv;
  real32_T LAT_Ctrl_Var_Far_Curv;
  real32_T LAT_Ctrl_Var_CurvRate;
} Curve_Parameters_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AES_ESA_PathPolyCoeBus_
#define DEFINED_TYPEDEF_FOR_AES_ESA_PathPolyCoeBus_

typedef struct {
  real32_T AESPath_ConCoeff;
  real32_T AESPath_FirstCoeff;
  real32_T AESPath_SecCoeff;
  real32_T AESPath_ThrdCoeff;
  real32_T AESPath_FourCoeff;
  real32_T AESPath_FiveCoeff;
} AES_ESA_PathPolyCoeBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AES_ESA_Controller_DebugSignal_
#define DEFINED_TYPEDEF_FOR_AES_ESA_Controller_DebugSignal_

typedef struct {
  real32_T AES_ESA_StrWhlAngReq;
  real32_T AES_ESA_StrWhlAngReqSpd;
  real32_T AES_ESA_Ctrl_Var_Curve;
  real32_T AES_ESA_Ctrl_Var_Lane_Radius;
  real32_T AES_ESA_Ctrl_Var_Far_Offset;
  real32_T AES_ESA_Ctrl_Var_Near_Offset;
  real32_T AES_ESA_Ctrl_Var_HedAngle;
  real32_T AES_ESA_Ctrl_Var_LatRate_Near;
  real32_T AES_ESA_Ctrl_Var_HedRate;
  real32_T AES_ESA_LatOffset_StrAngReq;
  real32_T AES_ESA_Heading_StrAngReq;
  real32_T AES_ESA_FeedForward_StrAngReq;
} AES_ESA_Controller_DebugSignal;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AES_ESA_PrimaryTarget_
#define DEFINED_TYPEDEF_FOR_AES_ESA_PrimaryTarget_

typedef struct {
  uint32_T id;
  uint32_T vaild;
  real32_T LonPos;
  real32_T latPos;
  real32_T LonVel;
  real32_T latVel;
  real32_T LonAccel;
  real32_T Heading;
  real32_T Length;
  real32_T Width;
} AES_ESA_PrimaryTarget;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AES_ESA_PlanningStartAndEndPoint_
#define DEFINED_TYPEDEF_FOR_AES_ESA_PlanningStartAndEndPoint_

typedef struct {
  real32_T x;
  real32_T y;
  real32_T dy;
  real32_T ddy;
} AES_ESA_PlanningStartAndEndPoint;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AES_ESA_Planning_DebugSignal_
#define DEFINED_TYPEDEF_FOR_AES_ESA_Planning_DebugSignal_

typedef struct {
  real32_T AES_ESA_PathMaxLatAcc_Left;
  real32_T AES_ESA_PathMaxLatAcc_Right;
  uint8_T AES_ESA_FirstPlanCompleteFlg;
  uint8_T AES_ESA_FirstSecPlan_PredTrigger;
  uint8_T padding_1;
  uint8_T padding_2;
  AES_ESA_PathPolyCoeBus AES_ESA_PathPolyCoe_Left;
  AES_ESA_PlanningStartAndEndPoint AES_ESA_PathStartPoint;
  AES_ESA_PlanningStartAndEndPoint AES_ESA_PathEndPoint_Left;
  AES_ESA_PathPolyCoeBus AES_ESA_PathPolyCoe_Right;
  AES_ESA_PlanningStartAndEndPoint AES_ESA_PathEndPoint_Right;
} AES_ESA_Planning_DebugSignal;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AES_ESA_CornerBus_
#define DEFINED_TYPEDEF_FOR_AES_ESA_CornerBus_

typedef struct {
  real32_T AES_ESA_Obj_CornerLR_x;
  real32_T AES_ESA_Obj_CornerLR_y;
  real32_T AES_ESA_Obj_CornerRR_x;
  real32_T AES_ESA_Obj_CornerRR_y;
  real32_T AES_ESA_Obj_CornerLF_x;
  real32_T AES_ESA_Obj_CornerLF_y;
  real32_T AES_ESA_Obj_CornerRF_x;
  real32_T AES_ESA_Obj_CornerRF_y;
  real32_T AES_ESA_Obj_CornerLR_heading;
  real32_T AES_ESA_Obj_CornerRR_heading;
  real32_T AES_ESA_Obj_CornerLF_heading;
  real32_T AES_ESA_Obj_CornerRF_heading;
  real32_T AES_ESA_Ego_CornerLF_x;
  real32_T AES_ESA_Ego_CornerLF_y;
  real32_T AES_ESA_Ego_CornerRF_x;
  real32_T AES_ESA_Ego_CornerRF_y;
} AES_ESA_CornerBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AES_ESA_Decision_DebugSignal_
#define DEFINED_TYPEDEF_FOR_AES_ESA_Decision_DebugSignal_

typedef struct {
  uint8_T AES_ESA_PlanEnable_Left;
  uint8_T AES_ESA_PlanEnable_Right;
  uint8_T AES_ESA_LaneLineVd_Left;
  uint8_T AES_ESA_LaneLineVd_Right;
  uint8_T AES_ESA_HasObstacle_Left;
  uint8_T AES_ESA_HasObstacle_Right;
  uint8_T AES_ESA_DecisionDirection;
  uint8_T padding_1;
  real32_T AES_ESA_DirectCost_Left;
  real32_T AES_ESA_DirectCost_Right;
  AES_ESA_CornerBus AES_ESA_CornerInfor;
} AES_ESA_Decision_DebugSignal;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AES_ESA_Mode_DebugSignal_
#define DEFINED_TYPEDEF_FOR_AES_ESA_Mode_DebugSignal_

typedef struct {
  uint32_T AES_ESA_Mode_T3_Debug;
  uint32_T AES_ESA_Mode_T4_Debug;
  uint32_T AES_ESA_Mode_T5_Debug;
  uint32_T AES_ESA_Mode_T6_Debug;
  uint32_T AES_ESA_Mode_T7T8_Debug;
  uint32_T AES_ESA_Mode_T9T10_Debug;
} AES_ESA_Mode_DebugSignal;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AES_ESA_T_
#define DEFINED_TYPEDEF_FOR_AES_ESA_T_

typedef struct {
  uint8_T AES_ESA_EvasionDirection;
  uint8_T AES_ESA_ActiveFlag;
  uint8_T AES_ESA_ActiveFlagLastFrame;
  uint8_T AES_ESA_Mode;
  real32_T AES_ESA_StrWhlAngReq;
  real32_T AES_ESA_StrWhlTorqReq;
  uint8_T AES_ESA_CmdBrkgFlg;
  uint8_T AES_ESA_DrvrSteerTrigFlg;
  uint8_T AES_ESA_LeftHasObstacle;
  uint8_T AES_ESA_RightHasObstacle;
  uint8_T AES_ESA_LeftLaneLineValid;
  uint8_T AES_ESA_RightLaneLineValid;
  uint8_T AES_ESA_IsFromAebObstacle;
  uint8_T AES_ESA_TrigBrkgFlg;
  real32_T AES_ESA_CritObjTTC;
  real32_T AES_LastPntToBrk_TTC_Final;
  real32_T AES_LastPntToStr_TTC_Left;
  real32_T AES_LastPntToStr_TTC_Right;
  uint32_T AES_ESA_Major_Version;
  uint32_T AES_ESA_Minor_Version;
  real32_T padding_1;
  real32_T padding_2;
  real32_T padding_3;
  real32_T padding_4;
  uint32_T padding_5;
  uint32_T padding_6;
  uint32_T padding_7;
  uint32_T padding_8;
  AES_ESA_PrimaryTarget AES_ESA_PrimaryTarget;
  AES_ESA_Planning_DebugSignal AES_ESA_Planning_Debug;
  AES_ESA_Decision_DebugSignal AES_ESA_Decision_Debug;
  AES_ESA_Mode_DebugSignal AES_ESA_Mode_Debug;
  AES_ESA_Controller_DebugSignal AES_ESA_Controller_Debug;
} AES_ESA_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_lane_marker_
#define DEFINED_TYPEDEF_FOR_lane_marker_

typedef struct {
  real32_T c0_position;
  real32_T c1_heading;
  real32_T c2_curvature;
  real32_T c3_curvature_derivative;
} lane_marker;

#endif

#ifndef DEFINED_TYPEDEF_FOR_OBJ_Obstacle_
#define DEFINED_TYPEDEF_FOR_OBJ_Obstacle_

typedef struct {
  uint8_T id;
  real32_T nearest_point_s;
  real32_T nearest_point_l;
  real32_T obstacle_l_min;
  real32_T obstacle_l_max;
  real32_T front_nearest_point_s;
  real32_T rear_nearest_point_s;
  real32_T speed;
  real32_T acceleration;
  real32_T heading;
  real32_T delta_speed;
  real32_T delta_acceleration;
  real32_T lateral_speed;
  real32_T lateral_acceleration;
  real32_T confidence;
  uint8_T oncoming_flag;
  real32_T length;
  real32_T width;
} OBJ_Obstacle;

#endif

#ifndef DEFINED_TYPEDEF_FOR_OBJ_DataBus_
#define DEFINED_TYPEDEF_FOR_OBJ_DataBus_

typedef struct {
  OBJ_Obstacle obstacles[2];
} OBJ_DataBus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_LaneChangeData_
#define DEFINED_TYPEDEF_FOR_LaneChangeData_

typedef struct {
  real32_T ObsRearBumper2Host;
  real32_T ObsFrontBumper2Host;
  real32_T FrontBrakeDistance;
  real32_T RearBrakeDistance;
  real32_T ObjCheckDistForward;
  real32_T ObjCheckDistBackward;
} LaneChangeData;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PP_LightSpotHeader_t_
#define DEFINED_TYPEDEF_FOR_PP_LightSpotHeader_t_

typedef struct {
  uint8_T LS_ErrorWords;
  uint8_T LS_MajorVersion;
  uint8_T LS_MinorVersion;
  uint8_T LS_RollingCounter;
  uint32_T LS_TimeStampSec;
  uint32_T LS_TimeStampNSec;
  uint32_T LS_Number;
  uint8_T LS_InhibitReason;
  uint8_T LS_ClearFieldOfView;
  uint8_T LS_DayTimeStatus;
  uint8_T LS_InTunnel;
  uint8_T LS_StreetLightsNumber;
  real32_T LS_StreetLightsNearstDis;
} PP_LightSpotHeader_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PP_LightSpotObj_t_
#define DEFINED_TYPEDEF_FOR_PP_LightSpotObj_t_

typedef struct {
  uint8_T LS_RollingCounter;
  uint32_T LS_ID;
  uint8_T LS_Classification;
  real32_T LS_LongPos;
  real32_T LS_LeftAngle;
  real32_T LS_RightAngle;
  real32_T LS_TopAngle;
  real32_T LS_BottomAngle;
} PP_LightSpotObj_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_PP_LightSpotInfo_t_
#define DEFINED_TYPEDEF_FOR_PP_LightSpotInfo_t_

typedef struct {
  PP_LightSpotHeader_t LightSpotHeader;
  PP_LightSpotObj_t LightSpotObj[15];
} PP_LightSpotInfo_t;

#endif

#ifndef DEFINED_TYPEDEF_FOR_IFVS600VehicleInfo_
#define DEFINED_TYPEDEF_FOR_IFVS600VehicleInfo_

typedef struct {
  uint8_T speedValid;
  uint8_T yawValid;
  uint8_T debug41BReserve;
  real32_T speedKPH;
  real32_T speedMPS;
  real32_T yawRateDPS;
  real32_T yawRateRPS;
  uint16_T gearState;
  uint8_T turnState;
  uint8_T brakeState;
  real32_T steerWheelAngle;
  real32_T longAcc;
} IFVS600VehicleInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VISION_AEB_INFO_T_
#define DEFINED_TYPEDEF_FOR_VISION_AEB_INFO_T_

typedef struct {
  uint32_T timestamp_us;
  uint32_T frameIndex;
  uint32_T vehIndexUsed;
  uint32_T visOnlyVRUBrake;
  uint16_T crc_16;
  uint16_T imageIndex;
  uint8_T rollingFrameCount;
  uint8_T visOnlyVRUWarning;
  uint8_T visOnlyVehWarning;
  uint8_T visOnlyVRUPPartialBrake;
  uint8_T visOnlyVehPartialBrake;
  uint8_T visOnlyVehBrake;
  uint8_T visOnlyVehBrakeDBS;
  uint8_T visOnlyPCAiWarning;
  uint8_T visOnlyPCAiPartialBrake;
  uint8_T visOnlyPCAiBrake;
  uint8_T roadFreeDetection;
  uint8_T visOnlyVehHighBrake;
  uint8_T visOnlyVRUBrakeDBS;
  uint8_T visOnlyVRUPrefill;
  uint8_T visOnlyVRUNotify;
  uint8_T visOnlyVRUBrakeJerk;
  uint8_T visOnlyVRUHighBrake;
} VISION_AEB_INFO_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MET_VIS_AEB_INFO_MSG_
#define DEFINED_TYPEDEF_FOR_MET_VIS_AEB_INFO_MSG_

typedef struct {
  uint32_T timestamp_image_ms;
  uint32_T timestamp_ms;
  VISION_AEB_INFO_T vision_aeb_info_t;
} MET_VIS_AEB_INFO_MSG;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_OBJECT_PHYSICAL_STATE_T_
#define DEFINED_TYPEDEF_FOR_VIS_OBJECT_PHYSICAL_STATE_T_

typedef struct {
  real32_T width;
  real32_T widthStd;
  real32_T length;
  real32_T lengthStd;
  real32_T height;
  real32_T heightStd;
  real32_T absoluteLongVelocity;
  real32_T absoluteLongVelocityStd;
  real32_T absoluteLatVelocity;
  real32_T absoluteLatVelocityStd;
  real32_T absoluteLongAcc;
  real32_T absoluteLongAccStd;
  real32_T absoluteLatAcc;
  real32_T absoluteLatAccStd;
  real32_T longDistance;
  real32_T longDistanceStd;
  real32_T latDistance;
  real32_T latDistanceStd;
  real32_T heading;
  real32_T wz;
} VIS_OBJECT_PHYSICAL_STATE_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_OBJECT_ANGULAR_STATE_T_
#define DEFINED_TYPEDEF_FOR_VIS_OBJECT_ANGULAR_STATE_T_

typedef struct {
  real32_T angleRight;
  real32_T angleRightStd;
  real32_T angleLeft;
  real32_T angleLeftStd;
  real32_T angleSide;
  real32_T angleSideStd;
  real32_T angleMid;
  real32_T angleMidStd;
  real32_T angularSpeed;
  real32_T angularSpeedStd;
} VIS_OBJECT_ANGULAR_STATE_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_RECT_T_
#define DEFINED_TYPEDEF_FOR_VIS_RECT_T_

typedef struct {
  uint32_T padding;
  int16_T xLeftCoord;
  int16_T xRightCoord;
  int8_T yTopCoord;
  int8_T yBottomCoord;
} VIS_RECT_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_VERTICAL_EDGE_T_
#define DEFINED_TYPEDEF_FOR_VIS_VERTICAL_EDGE_T_

typedef struct {
  uint32_T padding;
  int16_T xCoord;
  int16_T yTopCoord;
  int16_T yBottomCoord;
  uint8_T isOccluded;
  uint8_T valid;
} VIS_VERTICAL_EDGE_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_OBJECT_IMAGE_BOX_T_
#define DEFINED_TYPEDEF_FOR_VIS_OBJECT_IMAGE_BOX_T_

typedef struct {
  VIS_RECT_T vis_rect_t;
  VIS_VERTICAL_EDGE_T vis_vertical_edge_t;
  uint8_T visibleRect;
  uint8_T visibleSide;
  uint8_T detectionProfile;
  uint8_T detectionProfileSide;
  uint8_T detectionProfileRear;
} VIS_OBJECT_IMAGE_BOX_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_OBJECT_MOBILITY_STATE_T_
#define DEFINED_TYPEDEF_FOR_VIS_OBJECT_MOBILITY_STATE_T_

typedef struct {
  real32_T cutinPercentage;
  uint8_T motionStatus;
  uint8_T motionCategory;
  uint8_T motionOrientation;
  uint8_T detectionStatus;
  uint8_T goe_confirmed_Status;
  uint8_T close_cutin_Status;
  uint8_T close_cutin_Valid;
} VIS_OBJECT_MOBILITY_STATE_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_OBJECT_LIGHT_INDICATOR_T_
#define DEFINED_TYPEDEF_FOR_VIS_OBJECT_LIGHT_INDICATOR_T_

typedef struct {
  uint32_T padding;
  uint8_T valid;
  uint8_T brake;
  uint8_T turn;
  uint8_T initMethod;
} VIS_OBJECT_LIGHT_INDICATOR_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VISION_OBJECT_T_
#define DEFINED_TYPEDEF_FOR_VISION_OBJECT_T_

typedef struct {
  VIS_OBJECT_PHYSICAL_STATE_T vis_object_physical_state_t;
  VIS_OBJECT_ANGULAR_STATE_T vis_object_angular_state_t;
  VIS_OBJECT_IMAGE_BOX_T vis_object_image_box_t;
  VIS_OBJECT_MOBILITY_STATE_T vis_object_mobility_state_t;
  VIS_OBJECT_LIGHT_INDICATOR_T vis_object_light_indicator_t;
  real32_T confidence;
  real32_T ttc_const_vel;
  uint32_T age;
  uint16_T id;
  uint16_T crc_16;
  uint8_T rollingFrameCount;
  uint8_T classification;
  uint8_T isCipv;
  int8_T laneAssignment;
  real32_T objLanePercentageLeft;
  real32_T objLanePercentageRight;
} VISION_OBJECT_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VISION_OBSTACLES_INFO_T_
#define DEFINED_TYPEDEF_FOR_VISION_OBSTACLES_INFO_T_

typedef struct {
  uint32_T timestamp_us;
  uint32_T frameIndex;
  uint32_T vehIndexUsed;
  VISION_OBJECT_T vision_object_t;
  uint16_T crc_16;
  uint8_T isPredicted;
  uint8_T isInDrivableArea;
  uint8_T isVeryClose;
} VISION_OBSTACLES_INFO_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MET_VIS_OBSTACLES_MSG_
#define DEFINED_TYPEDEF_FOR_MET_VIS_OBSTACLES_MSG_

typedef struct {
  uint32_T timestamp_image_ms;
  uint32_T timestamp_ms;
  VISION_OBSTACLES_INFO_T vision_obstacles_info_t[64];
  uint16_T imageIndex;
  uint8_T rollingFrameCount;
} MET_VIS_OBSTACLES_MSG;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_POLYNOMIAL_MODEL_T_
#define DEFINED_TYPEDEF_FOR_VIS_POLYNOMIAL_MODEL_T_

typedef struct {
  real32_T a0;
  real32_T a1;
  real32_T a2;
  real32_T a3;
  real32_T startRange;
  real32_T endRange;
  real32_T endRangeMeasured;
} VIS_POLYNOMIAL_MODEL_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_CONFIDENCE_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_CONFIDENCE_T_

typedef struct {
  real32_T sfConf;
  uint16_T padding;
  uint8_T confidence;
} VIS_ROAD_CONFIDENCE_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_STATUS_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_STATUS_T_

typedef struct {
  real32_T laneMarkerWidth;
  uint8_T laneMarkerType;
  uint8_T dlmType;
  uint8_T decelType;
  uint8_T laneMarkerColor;
  uint8_T f_SCurve;
  uint8_T f_DashTurnSolid;
} VIS_ROAD_STATUS_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKER_HOST_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKER_HOST_T_

typedef struct {
  VIS_POLYNOMIAL_MODEL_T vis_polynomial_model_t_first;
  VIS_POLYNOMIAL_MODEL_T vis_polynomial_model_t_second;
  VIS_ROAD_CONFIDENCE_T vis_road_confidence_t;
  VIS_ROAD_STATUS_T vis_road_status_t;
} VIS_ROAD_MARKER_HOST_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKER_NEIGHBOR_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKER_NEIGHBOR_T_

typedef struct {
  VIS_POLYNOMIAL_MODEL_T vis_polynomial_model_t;
  VIS_ROAD_CONFIDENCE_T vis_road_confidence_t;
  VIS_ROAD_STATUS_T vis_road_status_t;
} VIS_ROAD_MARKER_NEIGHBOR_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKER_INFO_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKER_INFO_T_

typedef struct {
  VIS_ROAD_MARKER_HOST_T vis_road_marker_t_HL;
  VIS_ROAD_MARKER_HOST_T vis_road_marker_t_HR;
  VIS_ROAD_MARKER_NEIGHBOR_T vis_road_marker_t_LNL;
  VIS_ROAD_MARKER_NEIGHBOR_T vis_road_marker_t_LNR;
  VIS_ROAD_MARKER_NEIGHBOR_T vis_road_marker_t_RNR;
  VIS_ROAD_MARKER_NEIGHBOR_T vis_road_marker_t_RNL;
  uint8_T ambiguousLinePatternLeft;
  uint8_T ambiguousLinePatternRight;
  uint8_T constructionArea;
  uint8_T roadPredictionLeft;
  uint8_T roadPredictionRight;
} VIS_ROAD_MARKER_INFO_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_BORDER_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_BORDER_T_

typedef struct {
  VIS_POLYNOMIAL_MODEL_T vis_polynomial_model_t;
  VIS_ROAD_CONFIDENCE_T vis_road_confidence_t;
  real32_T roadBorderHeight;
  uint8_T roadBorderType;
} VIS_ROAD_BORDER_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_BORDER_INFO_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_BORDER_INFO_T_

typedef struct {
  VIS_ROAD_BORDER_T vis_road_border_t_RLB;
  VIS_ROAD_BORDER_T vis_road_border_t_RRB;
} VIS_ROAD_BORDER_INFO_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_WPP_FUSION_INFO_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_WPP_FUSION_INFO_T_

typedef struct {
  VIS_POLYNOMIAL_MODEL_T vis_polynomial_model_t_HC_First;
  VIS_POLYNOMIAL_MODEL_T vis_polynomial_model_t_HC_Second;
  real32_T roadFusionConf;
  real32_T halfWidth;
  real32_T wppLeftWeight;
  real32_T wppCenterWeight;
  real32_T wppRightWeight;
  real32_T roadLeftWeight;
  real32_T roadRightWeight;
} VIS_ROAD_WPP_FUSION_INFO_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_TRANSITION_POINT_T_
#define DEFINED_TYPEDEF_FOR_VIS_TRANSITION_POINT_T_

typedef struct {
  real32_T transitionLongPosition;
  real32_T transitionLatPosition;
  real32_T transitionProbability;
  uint8_T transitionType;
  uint8_T isStart;
  uint8_T transitionLineRole;
} VIS_TRANSITION_POINT_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_FAREND_MARKER_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_FAREND_MARKER_T_

typedef struct {
  VIS_POLYNOMIAL_MODEL_T vis_polynomial_model_t;
  VIS_ROAD_CONFIDENCE_T vis_road_confidence_t;
  VIS_ROAD_STATUS_T vis_road_status_t;
} VIS_ROAD_FAREND_MARKER_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_DISCONTINUOUS_FAREND_INFOR_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_DISCONTINUOUS_FAREND_INFOR_T_

typedef struct {
  VIS_ROAD_FAREND_MARKER_T vis_road_discontinuous_farend_info_t[4];
} VIS_ROAD_DISCONTINUOUS_FAREND_INFOR_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_INFO_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_INFO_T_

typedef struct {
  uint32_T timestamp_us;
  VIS_ROAD_MARKER_INFO_T vis_road_marker_info_t;
  VIS_ROAD_BORDER_INFO_T vis_road_border_info_t;
  VIS_ROAD_WPP_FUSION_INFO_T vis_road_wpp_fusion_info_t;
  VIS_TRANSITION_POINT_T vis_transition_point_t[2];
  VIS_ROAD_DISCONTINUOUS_FAREND_INFOR_T vis_road_marker_t_fared_Info;
  uint32_T frameIndex;
  uint32_T vehIndexUsed;
  uint16_T crc_16;
  uint16_T imageIndex;
  uint16_T road_info_crc_16;
  uint8_T road_info_rfc_16;
  uint8_T rollingFrameCount;
  uint8_T drivingSide;
  uint8_T laneChange;
  uint8_T hwExitLeft;
  uint8_T hwExitRight;
  uint8_T hwEntryLeft;
  uint8_T hwEntryRight;
  uint8_T multiClothoidHostLeftMarker;
  uint8_T multiClothoidHostRightMaker;
  uint8_T multiClothoidHostCenter;
} VIS_ROAD_INFO_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MET_VIS_ROAD_DATA_MSG_
#define DEFINED_TYPEDEF_FOR_MET_VIS_ROAD_DATA_MSG_

typedef struct {
  uint32_T timestamp_image_ms;
  uint32_T timestamp_ms;
  VIS_ROAD_INFO_T vis_road_info_t;
} MET_VIS_ROAD_DATA_MSG;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_TRAFFIC_SIGN_T_
#define DEFINED_TYPEDEF_FOR_VIS_TRAFFIC_SIGN_T_

typedef struct {
  real32_T signLongPosition;
  real32_T signLatPosition;
  real32_T signHeight;
  real32_T signConfidence;
  real32_T signMeasurementsConfidence;
  real32_T signSupp1Confidence;
  real32_T signSupp2Confidence;
  real32_T relevancyConfidence;
  real32_T signValue;
  uint16_T signPositionBottom;
  uint16_T signPositionLeft;
  uint16_T signPositionRight;
  uint16_T signPositionTop;
  uint16_T signType;
  uint8_T signEnumValue;
  uint8_T signSupplementalType1;
  uint8_T signSupplementalType2;
  uint8_T signID;
  uint8_T signRelevantDecision;
  uint8_T signFilterType;
  uint8_T signEmbeddedFlag;
  uint8_T signElectronicSignFlag;
  uint8_T signAboveRoadFlag;
  uint8_T signTrackingStatus;
} VIS_TRAFFIC_SIGN_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_TRAFFIC_LIGHT_T_
#define DEFINED_TYPEDEF_FOR_VIS_TRAFFIC_LIGHT_T_

typedef struct {
  real32_T lightLongPosition;
  real32_T lightLatPosition;
  real32_T lightHeight;
  real32_T lightConfidence;
  real32_T leftAngle;
  real32_T rightAngle;
  real32_T topAngle;
  real32_T bottomAngle;
  uint16_T lightPositionLeft;
  uint16_T lightPositionRight;
  uint16_T lightPositionTop;
  uint16_T lightPositionBottom;
  uint8_T lightRemainingTime;
  uint8_T lightType;
  uint8_T lightID;
  uint8_T lightColorType;
  uint8_T lightLaneAssignment;
  uint8_T numberOfTrafficLights;
} VIS_TRAFFIC_LIGHT_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKINGS_STOPLINE_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKINGS_STOPLINE_T_

typedef struct {
  real32_T lateralDistance;
  real32_T longitudinalDistance;
  real32_T confidence;
  real32_T angle;
  uint8_T isRelevant;
  uint8_T stopLineStatus;
  uint8_T id;
  uint8_T stopLineType;
  uint8_T stopLineColorType;
} VIS_ROAD_MARKINGS_STOPLINE_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKING_ARROW_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKING_ARROW_T_

typedef struct {
  real32_T arrowLatPosition;
  real32_T arrowLongPosition;
  real32_T confidence;
  uint16_T arrowType;
  uint8_T id;
} VIS_ROAD_MARKING_ARROW_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKING_SPEEDLIMIT_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKING_SPEEDLIMIT_T_

typedef struct {
  real32_T speedLimitLatPosition;
  real32_T speedLimitLongPosition;
  real32_T confidence;
  uint16_T speedLimitType;
  uint8_T id;
} VIS_ROAD_MARKING_SPEEDLIMIT_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKING_ZEBRA_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKING_ZEBRA_T_

typedef struct {
  real32_T zebraLatPosition;
  real32_T zebraLongPosition;
  real32_T zoneHeading;
  real32_T segmentHeading;
  real32_T width;
  real32_T height;
  real32_T confidence;
  uint8_T trackID;
  uint16_T zebraType;
} VIS_ROAD_MARKING_ZEBRA_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKING_INFO_T_
#define DEFINED_TYPEDEF_FOR_VIS_ROAD_MARKING_INFO_T_

typedef struct {
  VIS_ROAD_MARKINGS_STOPLINE_T vis_road_markings_stopline_t[4];
  VIS_ROAD_MARKING_ARROW_T vis_road_marking_arrow_t[4];
  VIS_ROAD_MARKING_SPEEDLIMIT_T vis_road_marking_speedlimit_t[4];
  VIS_ROAD_MARKING_ZEBRA_T vis_road_marking_zebra_t[6];
  uint8_T numberOfArrowsMarkings;
  uint8_T numberOfStopLinesMarkings;
  uint8_T numberOfSpeedLimitMarkings;
  uint8_T numberOfCrossingMarkings;
} VIS_ROAD_MARKING_INFO_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_TRAFFIC_SIGN_INFO_T_
#define DEFINED_TYPEDEF_FOR_VIS_TRAFFIC_SIGN_INFO_T_

typedef struct {
  uint32_T timestamp_us;
  uint32_T frameIndex;
  uint32_T vehIndexUsed;
  VIS_TRAFFIC_SIGN_T vis_traffic_sign_t_Info[8];
  VIS_TRAFFIC_LIGHT_T vis_traffic_light_t_Info[8];
  VIS_ROAD_MARKING_INFO_T vis_road_marking_info_t;
  uint16_T imageIndex;
  uint8_T currentMarket;
  uint8_T numbeTrafficSigns;
} VIS_TRAFFIC_SIGN_INFO_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MET_VIS_TRAFFIC_SIGNS_MSG_
#define DEFINED_TYPEDEF_FOR_MET_VIS_TRAFFIC_SIGNS_MSG_

typedef struct {
  uint32_T timestamp_image_ms;
  uint32_T timestamp_ms;
  VIS_TRAFFIC_SIGN_INFO_T vis_traffic_sign_info_t;
} MET_VIS_TRAFFIC_SIGNS_MSG;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ACTIVE_LIGTH_SPOT_T_
#define DEFINED_TYPEDEF_FOR_VIS_ACTIVE_LIGTH_SPOT_T_

typedef struct {
  real32_T leftAngle;
  real32_T rightAngle;
  real32_T topAngle;
  real32_T bottomAngle;
  uint32_T Id;
  uint16_T vdID;
  uint16_T longPos;
  uint16_T pixelTop;
  uint16_T pixelBottom;
  uint16_T pixelLeft;
  uint16_T pixelRight;
  uint8_T classification;
  uint8_T isTruck;
} VIS_ACTIVE_LIGTH_SPOT_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_REFIECTIVE_SIGNS_T_
#define DEFINED_TYPEDEF_FOR_VIS_REFIECTIVE_SIGNS_T_

typedef struct {
  real32_T lightSignLeftAngle;
  real32_T lightSignRightAngle;
  real32_T lightSignBottomAngle;
  real32_T lightSignTopAngle;
  uint16_T lightSignDistance;
  uint8_T lightSignID;
  uint8_T lightSignGlareLevelMax;
  uint8_T lightSignGlareLevelCurrent;
} VIS_REFIECTIVE_SIGNS_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VIS_ACTIVE_LIGHT_SENSOR_INFO_T_
#define DEFINED_TYPEDEF_FOR_VIS_ACTIVE_LIGHT_SENSOR_INFO_T_

typedef struct {
  uint32_T timestamp_us;
  uint32_T frameIndex;
  uint32_T vehIndexUsed;
  VIS_ACTIVE_LIGTH_SPOT_T vis_active_ligth_spot_t[15];
  VIS_REFIECTIVE_SIGNS_T vis_refiective_signs_t;
  uint16_T imageIndex;
  uint16_T eventsDetected;
  uint8_T ahbcAvailable;
  uint8_T gridFrequency;
  uint8_T numOfActiveLightSpots;
  uint8_T numOfReflectiveSigns;
  uint8_T clearFieldOfView;
  uint8_T beamRequest;
  uint8_T inTunnel;
  uint8_T fogDetected;
  uint8_T highwayDetected;
  uint8_T villageDetected;
  uint8_T oncomingLaneNotDark;
  uint8_T approachingJunction;
  uint8_T lightNosiyScene;
  uint8_T lightCone;
} VIS_ACTIVE_LIGHT_SENSOR_INFO_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MET_VIS_LIGHT_SENSOR_DATA_MSG_
#define DEFINED_TYPEDEF_FOR_MET_VIS_LIGHT_SENSOR_DATA_MSG_

typedef struct {
  uint32_T timestamp_image_ms;
  uint32_T timestamp_ms;
  VIS_ACTIVE_LIGHT_SENSOR_INFO_T vis_active_light_sensor_info_t;
} MET_VIS_LIGHT_SENSOR_DATA_MSG;

#endif

#ifndef DEFINED_TYPEDEF_FOR_METGOTrkRstElement_T_
#define DEFINED_TYPEDEF_FOR_METGOTrkRstElement_T_

typedef struct {
  uint32_T timestamp_image_ms;
  uint32_T timestamp_ms;
  uint32_T frameId;
  uint8_T status[16];
  uint8_T trackID[16];
  uint8_T objClass[16];
  uint16_T age[16];
  real32_T confidence[16];
  real32_T wWidth[16];
  real32_T wHeight[16];
  real32_T wLength[16];
  real32_T longPos[16];
  real32_T latPos[16];
  real32_T wz[16];
  uint32_T Reserved[16];
  int8_T laneAssignment[16];
} METGOTrkRstElement_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MET_VISION_RESULT_
#define DEFINED_TYPEDEF_FOR_MET_VISION_RESULT_

typedef struct {
  IFVS600VehicleInfo IFVS600_Vehicle_Info;
  MET_VIS_AEB_INFO_MSG met_vis_aeb_info_msg;
  MET_VIS_OBSTACLES_MSG met_vis_obstacles_msg;
  MET_VIS_ROAD_DATA_MSG met_vis_road_data_msg;
  MET_VIS_TRAFFIC_SIGNS_MSG met_vis_traffic_signs_msg;
  MET_VIS_LIGHT_SENSOR_DATA_MSG met_vis_light_sensor_data_msg;
  METGOTrkRstElement_T met_gotrkst_element_msg;
} MET_VISION_RESULT;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_TransitionPoint_T_
#define DEFINED_TYPEDEF_FOR_Struct_TransitionPoint_T_

typedef struct {
  real32_T LongPosition;
  real32_T LatPosition;
  real32_T LatProbability;
  uint8_T Type;
  uint8_T isStart;
  uint8_T LineRole;
  uint8_T uint8_reserve1;
} Struct_TransitionPoint_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_Right_Edge_T_
#define DEFINED_TYPEDEF_FOR_Struct_Right_Edge_T_

typedef struct {
  real32_T Road_Edge_Right_C0;
  real32_T Road_Edge_Right_C1;
  real32_T Road_Edge_Right_C2;
  real32_T Road_Edge_Right_C3;
  real32_T Road_Edge_Right_STARTRANGE;
  real32_T Road_Edge_Right_ENDRANGE;
  real32_T Road_Edge_Right_SFCONF;
  real32_T Road_Edge_Right_HEIGHT;
  real32_T Road_Edge_Right_TYPE;
  uint8_T Road_Edge_Right_CONFIDENCE;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Struct_Right_Edge_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_Host_Lane_Right_1st_T_
#define DEFINED_TYPEDEF_FOR_Struct_Host_Lane_Right_1st_T_

typedef struct {
  real32_T Host_Lane_Right_1st_C0;
  real32_T Host_Lane_Right_1st_C2;
  real32_T Host_Lane_Right_1st_C1;
  real32_T Host_Lane_Right_1st_RANGE;
  real32_T Host_Lane_Right_1st_C3;
  uint8_T Host_Lane_Right_1st_COLOR;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Struct_Host_Lane_Right_1st_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_LN_Left_Lane_T_
#define DEFINED_TYPEDEF_FOR_Struct_LN_Left_Lane_T_

typedef struct {
  real32_T LN_Left_C0;
  real32_T LN_Left_C1;
  real32_T LN_Left_C2;
  real32_T LN_Left_C3;
  real32_T LN_Left_STARTRANGE;
  real32_T LN_Left_ENDRANGE;
  real32_T LN_Left_SFCONF;
  real32_T LN_Left_WIDTH;
  uint8_T LN_Left_CONF;
  uint8_T LN_Left_TYPE;
  uint8_T LN_Left_DLMTYPE;
  uint8_T LN_Left_DECELTYPE;
  uint8_T LN_Left_COLOR;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Struct_LN_Left_Lane_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_Host_Lane_Left_1st_T_
#define DEFINED_TYPEDEF_FOR_Struct_Host_Lane_Left_1st_T_

typedef struct {
  real32_T Host_Lane_Left_1st_C0;
  real32_T Host_Lane_Left_1st_C2;
  real32_T Host_Lane_Left_1st_C1;
  real32_T Host_Lane_Left_1st_RANGE;
  real32_T Host_Lane_Left_1st_C3;
  uint8_T Host_Lane_Left_COLOR;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Struct_Host_Lane_Left_1st_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_LN_Right_Lane_T_
#define DEFINED_TYPEDEF_FOR_Struct_LN_Right_Lane_T_

typedef struct {
  real32_T LN_Right_C0;
  real32_T LN_Right_C1;
  real32_T LN_Right_C2;
  real32_T LN_Right_C3;
  real32_T LN_Right_STARTRANGE;
  real32_T LN_Right_ENDRANGE;
  real32_T LN_Right_SFCONF;
  real32_T LN_Right_WIDTH;
  uint8_T LN_Right_CONF;
  uint8_T LN_Right_TYPE;
  uint8_T LN_Right_DLMTYPE;
  uint8_T LN_Right_DECELTYPE;
  uint8_T LN_Right_COLOR;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Struct_LN_Right_Lane_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_RN_Left_Lane_T_
#define DEFINED_TYPEDEF_FOR_Struct_RN_Left_Lane_T_

typedef struct {
  real32_T RN_Left_C0;
  real32_T RN_Left_C1;
  real32_T RN_Left_C2;
  real32_T RN_Left_C3;
  real32_T RN_Left_STARTRANGE;
  real32_T RN_Left_ENDRANGE;
  real32_T RN_Left_SFCONF;
  real32_T RN_Left_WIDTH;
  uint8_T RN_Left_CONF;
  uint8_T RN_Left_TYPE;
  uint8_T RN_Left_DLMTYPE;
  uint8_T RN_Left_DECELTYPE;
  uint8_T RN_Left_COLOR;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Struct_RN_Left_Lane_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_Left_Edge_T_
#define DEFINED_TYPEDEF_FOR_Struct_Left_Edge_T_

typedef struct {
  real32_T Road_Edge_Left_C0;
  real32_T Road_Edge_Left_C1;
  real32_T Road_Edge_Left_C2;
  real32_T Road_Edge_Left_C3;
  real32_T Road_Edge_Left_STARTRANGE;
  real32_T Road_Edge_Left_ENDRANGE;
  real32_T Road_Edge_Left_SFCONF;
  real32_T Road_Edge_Left_HEIGHT;
  real32_T Road_Edge_Left_TYPE;
  uint8_T Road_Edge_Left_CONFIDENCE;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Struct_Left_Edge_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_Host_Lane_Conf_1st_T_
#define DEFINED_TYPEDEF_FOR_Struct_Host_Lane_Conf_1st_T_

typedef struct {
  real32_T Host_LANE_LEFT_1st_SFCONF;
  real32_T Host_LANE_RIGHT_1st_SFCONF;
  uint8_T Host_LANE_LEFT_1st_TYPE;
  uint8_T Host_LANE_RIGHT_1st_TYPE;
  uint8_T Host_LANE_LEFT_1st_DLMTYPE;
  uint8_T Host_LANE_RIGHT_1st_DLMTYPE;
  uint8_T Host_LANE_CHANGE;
  uint8_T CAN_DRIVING_SIDE;
  uint8_T f_Left_SCurve;
  uint8_T f_Left_DashTurnSolid;
  uint8_T f_Right_SCurve;
  uint8_T f_Right_DashTurnSolid;
  uint8_T ReservedUint8_1;
  uint8_T ReservedUint8_2;
  uint8_T ReservedUint8_3;
  uint8_T ReservedUint8_4;
  uint8_T ReservedUint8_5;
  uint8_T ReservedUint8_6;
  real32_T Reservedfloat_1;
  real32_T Reservedfloat_2;
  real32_T Reservedfloat_3;
  real32_T Reservedfloat_4;
} Struct_Host_Lane_Conf_1st_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_Host_Lane_Status_T_
#define DEFINED_TYPEDEF_FOR_Struct_Host_Lane_Status_T_

typedef struct {
  real32_T HOST_PREDICTION_INFO_L;
  real32_T HOST_PREDICTION_INFO_R;
  uint8_T Host_Lane_Left_1st_Conf;
  uint8_T Host_Lane_Right_1st_Conf;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
} Struct_Host_Lane_Status_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_Host_Lane_Center_1st_T_
#define DEFINED_TYPEDEF_FOR_Struct_Host_Lane_Center_1st_T_

typedef struct {
  real32_T Host_Lane_Center_1st_C0;
  real32_T Host_Lane_Center_1st_C1;
  real32_T Host_Lane_Center_1st_C2;
  real32_T Host_Lane_Center_1st_C3;
  real32_T Host_Lane_Center_1st_HalfWidth;
  real32_T Host_Lane_Center_1st_FusConf;
} Struct_Host_Lane_Center_1st_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_HighWay_Lane_T_
#define DEFINED_TYPEDEF_FOR_Struct_HighWay_Lane_T_

typedef struct {
  boolean_T Host_HW_EXIT_LEFT;
  boolean_T Host_HW_EXIT_RIGHT;
  boolean_T Host_HW_ENRTY_LEFT;
  boolean_T Host_HW_ENRTY_RIGHT;
} Struct_HighWay_Lane_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_RN_Right_Lane_T_
#define DEFINED_TYPEDEF_FOR_Struct_RN_Right_Lane_T_

typedef struct {
  real32_T RN_Right_C0;
  real32_T RN_Right_C1;
  real32_T RN_Right_C2;
  real32_T RN_Right_C3;
  real32_T RN_Right_STARTRANGE;
  real32_T RN_Right_ENDRANGE;
  real32_T RN_Right_SFCONF;
  real32_T RN_Right_WIDTH;
  uint8_T RN_Right_CONF;
  uint8_T RN_Right_TYPE;
  uint8_T RN_Right_DLMTYPE;
  uint8_T RN_Right_DECELTYPE;
  uint8_T RN_Right_COLOR;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Struct_RN_Right_Lane_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_VISION_LANE_T_
#define DEFINED_TYPEDEF_FOR_Struct_VISION_LANE_T_

typedef struct {
  Struct_Host_Lane_Left_1st_T Host_Lane_Left_1st;
  Struct_Host_Lane_Right_1st_T Host_Lane_Right_1st;
  Struct_Host_Lane_Conf_1st_T Host_Lane_Conf_1st;
  Struct_Host_Lane_Status_T Host_Lane_Status_1st;
  Struct_Host_Lane_Center_1st_T Host_Lane_Center_1st;
  Struct_Left_Edge_T Road_Left_Border;
  Struct_Right_Edge_T Road_Right_Border;
  Struct_HighWay_Lane_T HighWay_Lane;
  Struct_LN_Right_Lane_T Left_Neighbor_Right;
  Struct_RN_Left_Lane_T Right_Neighbor_Left;
  Struct_LN_Left_Lane_T Left_Neighbor_Left;
  Struct_RN_Right_Lane_T Right_Neighbor_Right;
  Struct_TransitionPoint_T TransitionPoint_01;
  Struct_TransitionPoint_T TransitionPoint_02;
} Struct_VISION_LANE_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_EP_LaneSignEdge_T_
#define DEFINED_TYPEDEF_FOR_EP_LaneSignEdge_T_

typedef struct {
  real32_T EP_FutLftDistToEdge;
  real32_T EP_FutRgtDistToEdge;
  real32_T EP_CurrLftDistToEdge;
  real32_T EP_CurrRgtDistToEdge;
  real32_T EP_LftEdgeHdgDeg;
  real32_T EP_LftEdgeCurv;
  real32_T EP_LftEdgeLatRt;
  real32_T EP_RgtEdgeLatRt;
  real32_T EP_RgtEdgeHdgDeg;
  real32_T EP_RgtEdgeCurv;
  boolean_T EP_FLftEdgeHiConf;
  boolean_T EP_FRgtEdgeHiConf;
  boolean_T EP_FLftEdgeVhConf;
  boolean_T EP_FRgtEdgeVhConf;
  real32_T EP_LftEdgeTtlc;
  real32_T EP_RgtEdgeTtlc;
  real32_T EP_CurrAbsOfstSet;
  real32_T EP_FutHostAbsOfstSet;
  boolean_T EP_RunOffRoadLft;
  boolean_T EP_RunOffRoafRgt;
  boolean_T EP_LftEdgeValidHeld;
  boolean_T EP_RgtEdgeValidHeld;
  boolean_T EP_ValidMMLaneEdgeLft;
  boolean_T EP_ValidMMLaneEdgeRgt;
  boolean_T EP_LftSimFlag;
  boolean_T EP_RgtSimFlag;
  real32_T EP_LftEdgeRange;
  real32_T EP_RgtEdgeRange;
} EP_LaneSignEdge_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_EP_Vis_Lane_ILC_T_
#define DEFINED_TYPEDEF_FOR_EP_Vis_Lane_ILC_T_

typedef struct {
  uint8_T EP_VisLaneLaneChange;
  boolean_T EP_VisHwExitLft;
  boolean_T EP_VisHwExitRgt;
  uint8_T EP_VisNextllmConf;
  uint8_T EP_VisNextrlmConf;
  uint8_T EP_VisLaneLftIndividDlmType;
  uint8_T EP_VisLaneRgtIndividDlmType;
  real32_T EP_VisNextllmA0;
  real32_T EP_VisNextrlmA0;
  real32_T EP_VisLaneLftIndividA0;
  real32_T EP_VisLaneRgtIndividA0;
  real32_T EP_VisLaneLftIndividRng;
  real32_T EP_VisLaneRgtIndividRng;
} EP_Vis_Lane_ILC_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_EP_LaneSignBdry_T_
#define DEFINED_TYPEDEF_FOR_EP_LaneSignBdry_T_

typedef struct {
  real32_T EP_LftBdryTtlc;
  real32_T EP_RgtBdryTtlc;
  real32_T EP_FutLftDistToBdry;
  real32_T EP_FutRgtDistToBdry;
  real32_T EP_LftBdryHdgDeg;
  real32_T EP_RgtBdryHdgDeg;
  real32_T EP_CurrAbsLaneBdryPosn;
  real32_T EP_CurrLaneBdryWdth;
  real32_T EP_CompHeadingDegBdry;
  real32_T EP_LftBdryLatRt;
  real32_T EP_RgtBdryLatRt;
  boolean_T EP_LftBdryHiConf;
  boolean_T EP_RgtBdryHiConf;
  boolean_T EP_LftLaneChangeBdry;
  boolean_T EP_RgtLaneChangeBdry;
  real32_T EP_CurrLftDistToBdry;
  real32_T EP_CurrRgtDistToBdry;
  real32_T EP_FutHostAbsLaneBdryPosn;
  real32_T EP_RgtBdryCurv;
  real32_T EP_LftBdryCurv;
  real32_T EP_CompLaneBdryCurv;
  boolean_T EP_BothBdryValidHeld;
  boolean_T EP_LftBdryVhConf;
  boolean_T EP_RgtBdryVhConf;
  boolean_T EP_LftBdryValidHeld;
  boolean_T EP_RgtBdryValidHeld;
  uint8_T EP_TypeSourceBdryLft;
  uint8_T EP_TypeSourceBdryRgt;
  boolean_T EP_ValidMmLaneMarker;
  boolean_T EP_ValidMmLaneBdryLft;
  boolean_T EP_ValidMmLaneBdryRgt;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  real32_T EP_BdryHeadingAngleCR;
  real32_T EP_FutLftBdryLatRt;
  real32_T EP_FutRgtBdryLatRt;
  real32_T EP_LftCurvRt;
  real32_T EP_RgtCurvRt;
} EP_LaneSignBdry_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_EP_LaneSignLCC_T_
#define DEFINED_TYPEDEF_FOR_EP_LaneSignLCC_T_

typedef struct {
  boolean_T EP_LlmValid;
  boolean_T EP_RlmValid;
  boolean_T EP_BlmValid;
  boolean_T EP_LaneConf;
  real32_T EP_LmRoc;
  real32_T EP_FppLaneWdth;
} EP_LaneSignLCC_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SPP_SP_PolyCoeff_T_
#define DEFINED_TYPEDEF_FOR_SPP_SP_PolyCoeff_T_

typedef struct {
  real32_T EP_FppA0;
  real32_T EP_FppA1;
  real32_T EP_FppA2;
  real32_T EP_FppA3;
  real32_T EP_FppA2Raw;
  real32_T EP_FppA1Rate;
} SPP_SP_PolyCoeff_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SPP_SP_Info_1_T_
#define DEFINED_TYPEDEF_FOR_SPP_SP_Info_1_T_

typedef struct {
  uint8_T EP_FppType;
  uint8_T EP_FppConf;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  real32_T EP_FppMaxRng;
  real32_T EP_RoadFusionconf;
} SPP_SP_Info_1_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SPP_SP_Info_2_T_
#define DEFINED_TYPEDEF_FOR_SPP_SP_Info_2_T_

typedef struct {
  real32_T EP_FppLaneWdth;
  uint8_T EP_FppLlmRlmSmilrty;
  uint8_T EP_FppLlmPoSmilrty;
  uint8_T EP_FppRlmPoSmilrty;
  uint8_T EP_FppPredLmrkrMode;
  real32_T EP_FppTypeAge;
  uint8_T EP_FPpLmPredictedStatus;
  uint8_T EP_FppPoBlmSmilrty;
  uint8_T EP_FppLwState;
  real32_T EP_FppMaxCoaDist;
  real32_T EP_FppDefaultLaneWdth;
  real32_T EP_FppMaxPoAcqRng;
  real32_T EP_FppMaxPoRetRng;
} SPP_SP_Info_2_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SPP_LLM_Info_1_T_
#define DEFINED_TYPEDEF_FOR_SPP_LLM_Info_1_T_

typedef struct {
  uint8_T EP_LlmConf;
  uint8_T EP_LlmStatus;
  uint8_T EP_LlmType;
  real32_T EP_LlmMaxRng;
} SPP_LLM_Info_1_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SPP_RLM_Info_1_T_
#define DEFINED_TYPEDEF_FOR_SPP_RLM_Info_1_T_

typedef struct {
  uint8_T EP_RlmConf;
  uint8_T EP_RlmStatus;
  uint8_T EP_RlmType;
  real32_T EP_RlmMaxRng;
} SPP_RLM_Info_1_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_EP_FppDebug_T_
#define DEFINED_TYPEDEF_FOR_EP_FppDebug_T_

typedef struct {
  real32_T EP_FppMemBlmMaxTmS;
  real32_T EP_FppMemSlmMaxTmS;
  uint8_T EP_FppTypeMem;
  uint8_T EP_FppConfMem;
  uint8_T EP_HighSpdMemState;
  boolean_T EP_HostLowSpdFlg;
  boolean_T EP_BlmValid;
  boolean_T EP_LlmValid;
  boolean_T EP_RlmValid;
  boolean_T EP_OthersideValid;
  boolean_T EP_OthersideRdgeBarrValid;
  uint8_T EP_LftRdgeBarrSel;
  uint8_T EP_RgtRdgeBarrSel;
  boolean_T EP_PoValid;
} EP_FppDebug_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ILC_Coeff_TrjPln_T_
#define DEFINED_TYPEDEF_FOR_ILC_Coeff_TrjPln_T_

typedef struct {
  real32_T EP_IlcA0;
  real32_T EP_IlcA1;
  real32_T EP_IlcA2;
  real32_T EP_IlcA3;
  real32_T EP_IlcA4;
  real32_T EP_IlcA5;
} ILC_Coeff_TrjPln_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ILC_Coeff_TrjPlnCalPara_T_
#define DEFINED_TYPEDEF_FOR_ILC_Coeff_TrjPlnCalPara_T_

typedef struct {
  real32_T ILC_x_f_ref;
  real32_T ILC_y_f_ref;
  real32_T ILC_HeadingAngle_f_ref;
  real32_T ILC_Curveture_f_ref;
  real32_T ILC_LaneChangeTime;
  real32_T ILC_DrvDis;
  real32_T ILC_PrevDistance;
} ILC_Coeff_TrjPlnCalPara_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ILC_Coeff_Ctl_T_
#define DEFINED_TYPEDEF_FOR_ILC_Coeff_Ctl_T_

typedef struct {
  real32_T ILC_L0_Prev;
  real32_T ILC_L1_Prev;
  real32_T ILC_L2_Prev;
  real32_T ILC_L3_Prev;
  real32_T EP_IlcL0PrevFlt;
  real32_T EP_IlcL1PrevFlt;
  real32_T EP_IlcL2PrevFlt;
  real32_T EP_IlcL3PrevFlt;
} ILC_Coeff_Ctl_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ILC_Signals_T_
#define DEFINED_TYPEDEF_FOR_ILC_Signals_T_

typedef struct {
  real32_T SP_A0_ILC;
  real32_T SP_A1_ILC;
  real32_T ILC_I_Term_Offset;
  real32_T SP_A0;
  real32_T SP_A1;
  real32_T SP_ROC;
  real32_T ILC_RoadType;
  ILC_Coeff_TrjPln_T ILC_Coeff_TrjPln;
  ILC_Coeff_TrjPlnCalPara_T ILC_Coeff_TrjPlnCalPara;
  ILC_Coeff_Ctl_T ILC_Coeff_Ctl;
} ILC_Signals_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SPP_LLM_PolyCoeff_T_
#define DEFINED_TYPEDEF_FOR_SPP_LLM_PolyCoeff_T_

typedef struct {
  real32_T EP_LlmA0;
  real32_T EP_LlmA1;
  real32_T EP_LlmA2;
  real32_T EP_LlmA3;
} SPP_LLM_PolyCoeff_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SPP_RLM_PolyCoeff_T_
#define DEFINED_TYPEDEF_FOR_SPP_RLM_PolyCoeff_T_

typedef struct {
  real32_T EP_RlmA0;
  real32_T EP_RlmA1;
  real32_T EP_RlmA2;
  real32_T EP_RlmA3;
} SPP_RLM_PolyCoeff_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SPP_PO_PolyCoeff_T_
#define DEFINED_TYPEDEF_FOR_SPP_PO_PolyCoeff_T_

typedef struct {
  real32_T EP_PoA0;
  real32_T EP_PoA1;
  real32_T EP_PoA2;
  real32_T EP_PoA3;
  real32_T EP_PoA1Rate;
} SPP_PO_PolyCoeff_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SPP_ActTrj_PolyCoeff_T_
#define DEFINED_TYPEDEF_FOR_SPP_ActTrj_PolyCoeff_T_

typedef struct {
  real32_T Fpp_ActTrj_C0;
  real32_T Fpp_ActTrj_C1;
} SPP_ActTrj_PolyCoeff_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_EP_VisFpp_T_
#define DEFINED_TYPEDEF_FOR_EP_VisFpp_T_

typedef struct {
  SPP_SP_PolyCoeff_T SPP_SP_PolyCoeff;
  SPP_SP_Info_1_T SPP_SP_Info_1;
  SPP_SP_Info_2_T SPP_SP_Info_2;
  SPP_LLM_Info_1_T SPP_LLM_Info_1;
  SPP_RLM_Info_1_T SPP_RLM_Info_1;
  boolean_T EP_KUseFpp;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
  EP_FppDebug_T EP_FppDebug;
  ILC_Signals_T ILC_Signals;
  SPP_LLM_PolyCoeff_T SPP_LLM_PolyCoeff;
  SPP_RLM_PolyCoeff_T SPP_RLM_PolyCoeff;
  real32_T EP_LftRdgeBarrGdrlMinOfst;
  real32_T EP_RgtRdgeBarrGdrlMinOfst;
  real32_T EP_FppPolyCoeffA0;
  real32_T EP_FppPolyCoeffA1;
  SPP_PO_PolyCoeff_T SPP_PO_PolyCoeff;
  SPP_ActTrj_PolyCoeff_T SPP_ActTrjPoly;
} EP_VisFpp_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_EP_RoadFutCurv_T_
#define DEFINED_TYPEDEF_FOR_EP_RoadFutCurv_T_

typedef struct {
  real32_T EP_FutureCurveLft;
  real32_T EP_FutureCurveRgt;
  real32_T EP_FutureCurveFpp;
  boolean_T EP_VehicleSCurveLft;
  boolean_T EP_VehicleSCurveRgt;
  boolean_T EP_VehicleInCurve;
  uint8_T uint8_reserve1;
} EP_RoadFutCurv_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_EP_LaneSignals_T_
#define DEFINED_TYPEDEF_FOR_EP_LaneSignals_T_

typedef struct {
  EP_LaneSignLCC_T EP_LaneSignLCC;
  EP_LaneSignEdge_T EP_LaneSignEdge;
  EP_LaneSignBdry_T EP_LaneSignBdry;
  real32_T EP_PreviewRng;
  uint8_T EP_RoadState;
  uint8_T EP_RLC;
  uint8_T EP_MajorVer;
  uint8_T EP_MinorVer;
  EP_VisFpp_T EP_VisFpp;
  EP_RoadFutCurv_T EP_RoadFutCurv;
  real32_T EP_CamLatMountOfst;
  real32_T EP_HostVehWdth;
  EP_Vis_Lane_ILC_T Vis_Lane_ILC;
  real32_T EP_LaneCurveHMI;
} EP_LaneSignals_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Fusion_GUARD_LEFT_HandCode_Wrapped_T_
#define DEFINED_TYPEDEF_FOR_Fusion_GUARD_LEFT_HandCode_Wrapped_T_

typedef struct {
  real32_T FUS_GUARD_LEFT_OFFSET;
  real32_T FUS_GUARD_LEFT_C0;
  real32_T FUS_GUARD_LEFT_HEADING;
  real32_T FUS_GUARD_LEFT_RANGE;
  real32_T FUS_GUARD_LEFT_C1;
  uint8_T FUS_GUARD_LEFT_STATUS;
  uint8_T FUS_GUARD_LEFT_LKACONF;
  uint8_T FUS_GUARD_LEFT_TJACONF;
  uint8_T uint8_reserve1;
} Fusion_GUARD_LEFT_HandCode_Wrapped_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Fusion_GUARD_RIGHT_HandCode_Wrapped_T_
#define DEFINED_TYPEDEF_FOR_Fusion_GUARD_RIGHT_HandCode_Wrapped_T_

typedef struct {
  real32_T FUS_GUARD_RIGHT_OFFSET;
  real32_T FUS_GUARD_RIGHT_C0;
  real32_T FUS_GUARD_RIGHT_HEADING;
  real32_T FUS_GUARD_RIGHT_RANGE;
  real32_T FUS_GUARD_RIGHT_C1;
  uint8_T FUS_GUARD_RIGHT_STATUS;
  uint8_T FUS_GUARD_RIGHT_LKACONF;
  uint8_T FUS_GUARD_RIGHT_TJACONF;
  uint8_T uint8_reserve1;
} Fusion_GUARD_RIGHT_HandCode_Wrapped_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Fusion_GdRail_HandCode_Wrapped_T_
#define DEFINED_TYPEDEF_FOR_Fusion_GdRail_HandCode_Wrapped_T_

typedef struct {
  Fusion_GUARD_LEFT_HandCode_Wrapped_T Fusion_GUARD_LEFT;
  Fusion_GUARD_RIGHT_HandCode_Wrapped_T Fusion_GUARD_RIGHT;
} Fusion_GdRail_HandCode_Wrapped_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_SP_Info_2_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_SP_Info_2_T_

typedef struct {
  real32_T FPP_SP_lane_width;
  real32_T FPP_SP_type_age;
  real32_T FPP_SP_max_coast_dist;
  real32_T FPP_SP_default_lane_width;
  real32_T FPP_SP_max_po_acq_range;
  real32_T FPP_SP_max_po_ret_range;
  uint8_T FPP_SP_LLM_RLM_similarity;
  uint8_T FPP_SP_LLM_PO_similarity;
  uint8_T FPP_SP_RLM_PO_similarity;
  uint8_T FPP_SP_pred_lmrkr_mode;
  uint8_T FPP_SP_LM_predicted_status;
  uint8_T FPP_SP_PO_BLM_similarity;
  uint8_T FPP_SP_LW_state;
  uint8_T uin8_reserve1;
} Struct_FPP_SP_Info_2_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_Poly_Coeff_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_Poly_Coeff_T_

typedef struct {
  real32_T FPP_POLY_COEFF_C0;
  real32_T FPP_POLY_COEFF_C1;
  real32_T FPP_POLY_COEFF_C2;
  real32_T FPP_POLY_COEFF_C3;
  real32_T FPP_POLY_COEFF_C1_Rate;
} Struct_FPP_Poly_Coeff_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_SP_Info_1_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_SP_Info_1_T_

typedef struct {
  real32_T FPP_SP_status;
  real32_T FPP_SP_age;
  real32_T FPP_SP_state_age;
  real32_T FPP_SP_LM_Exit_Check;
  real32_T FPP_SP_LM_Exit_enabled;
  real32_T FPP_SP_conf_mode;
  real32_T FPP_SP_max_range;
  real32_T FPP_SP_min_lane_width;
  real32_T FPP_SP_max_lane_width;
  real32_T FPP_SP_measured_lane_width;
  real32_T FPP_roadFusionConf;
  uint8_T FPP_SP_type;
  uint8_T FPP_SP_conf;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
} Struct_FPP_SP_Info_1_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_VisPlaus_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_VisPlaus_T_

typedef struct {
  real32_T FPP_VP_llm_valid;
  real32_T FPP_VP_llm_delta_valid;
  real32_T FPP_VP_llm_straddle;
  real32_T FPP_VP_rlm_valid;
  real32_T FPP_VP_rlm_delta_valid;
  real32_T FPP_VP_rlm_straddle;
  real32_T FPP_VP_pred_lw_valid;
  real32_T FPP_VP_overall_lmrkr_valid;
  real32_T FPP_VP_diverging;
  real32_T FPP_VP_MPC_v;
  real32_T FPP_VP_pred_lw;
  real32_T FPP_VP_llm_lwhl_offset;
  real32_T FPP_VP_rlm_rhwl_offset;
  real32_T FPP_VP_llm_input_sim_v;
  real32_T FPP_VP_rlm_input_sim_v;
  real32_T FPP_VP_blm_input_sim_v;
  real32_T FPP_VP_po_input_sim_v;
} Struct_FPP_VisPlaus_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_PO_Poly_Coeff_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_PO_Poly_Coeff_T_

typedef struct {
  real32_T FPP_PO_Coeff_C0;
  real32_T FPP_PO_Coeff_C1;
  real32_T FPP_PO_Coeff_C2;
  real32_T FPP_PO_Coeff_C3;
  real32_T FPP_PO_Coeff_C1_Rate;
} Struct_FPP_PO_Poly_Coeff_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_PO_Info_1_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_PO_Info_1_T_

typedef struct {
  real32_T FPP_PO_max_range;
  uint8_T FPP_PO_status;
  uint8_T FPP_PO_type;
  uint8_T FPP_PO_age;
  uint8_T FPP_PO_state_age;
  uint8_T FPP_PO_conf;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Struct_FPP_PO_Info_1_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_PO_Info_2_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_PO_Info_2_T_

typedef struct {
  real32_T FPP_PO_corrCoeff;
  real32_T FPP_PO_lat_pos;
  real32_T FPP_PO_lng_pos;
  real32_T FPP_PO_cutout;
  real32_T FPP_PO_yawrate_cutout;
  real32_T FPP_PO_LLM_heading_cutout;
  real32_T FPP_PO_RLM_heading_cutout;
  real32_T FPP_PO_LLM_extent_cutout;
  real32_T FPP_PO_RLM_extent_cutout;
  real32_T FPP_PO_use_cutout_output;
  uint8_T FPP_PO_fusTrackId;
  uint8_T FPP_PO_trail_ID;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
} Struct_FPP_PO_Info_2_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_LLM_Poly_Coeff_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_LLM_Poly_Coeff_T_

typedef struct {
  real32_T FPP_LLM_C0;
  real32_T FPP_LLM_C1;
  real32_T FPP_LLM_C2;
  real32_T FPP_LLM_C3;
} Struct_FPP_LLM_Poly_Coeff_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_LLM_Info_1_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_LLM_Info_1_T_

typedef struct {
  real32_T FPP_LLM_max_range;
  real32_T PRED_divLaneMrkPredict;
  real32_T PRED_othSideBsdPredict;
  real32_T PRED_mergePredict;
  real32_T PRED_extrapolation;
  real32_T PRED_occlLmrkrExtrapolation;
  real32_T PRED_hdwayOrntExtrapolation;
  uint8_T FPP_LLM_status;
  uint8_T FPP_LLM_type;
  uint8_T FPP_LLM_age;
  uint8_T FPP_LLM_state_age;
  uint8_T FPP_LLM_conf;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Struct_FPP_LLM_Info_1_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_RLM_Poly_Coeff_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_RLM_Poly_Coeff_T_

typedef struct {
  real32_T FPP_RLM_C0;
  real32_T FPP_RLM_C1;
  real32_T FPP_RLM_C2;
  real32_T FPP_RLM_C3;
} Struct_FPP_RLM_Poly_Coeff_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_RLM_Info_1_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_RLM_Info_1_T_

typedef struct {
  real32_T FPP_RLM_max_range;
  real32_T PRED_divLaneMrkPredict;
  real32_T PRED_othSideBsdPredict;
  real32_T PRED_mergePredict;
  real32_T PRED_extrapolation;
  real32_T PRED_occlLmrkrExtrapolation;
  real32_T PRED_hdwayOrntExtrapolation;
  uint8_T FPP_RLM_status;
  uint8_T FPP_RLM_type;
  uint8_T FPP_RLM_age;
  uint8_T FPP_RLM_state_age;
  uint8_T FPP_RLM_conf;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
  uint8_T uint8_reserve3;
} Struct_FPP_RLM_Info_1_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_BLM_Info_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_BLM_Info_T_

typedef struct {
  uint8_T FPP_BLM_status;
  uint8_T FPP_BLM_age;
  uint8_T FPP_BLM_state_age;
  uint8_T FPP_BLM_conf;
  real32_T FPP_BLM_max_range;
} Struct_FPP_BLM_Info_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_SP_Info_3_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_SP_Info_3_T_

typedef struct {
  real32_T FPP_min_lm_range;
  real32_T FPP_min_lm_headway;
  real32_T FPP_spd_thresh_strdl;
  real32_T FPP_strdl_margin_hi;
  real32_T FPP_strdl_margin_lo;
  real32_T FPP_LD_low_conf_llm;
  real32_T FPP_LD_low_conf_rlm;
  real32_T FPP_LD_plaus_fail_llm;
  real32_T FPP_LD_plaus_fail_rlm;
  real32_T FPP_LD_max_lw;
  real32_T FPP_LD_min_lw;
  real32_T FPP_LD_lw_coast_distance;
  real32_T FPP_LD_barrier_adjustment;
} Struct_FPP_SP_Info_3_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_LW_Info_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_LW_Info_T_

typedef struct {
  real32_T FPP_LW_max_coast_distance;
  real32_T FPP_LW_distance_in_state;
  real32_T FPP_LW_slope_to_meas;
  real32_T FPP_LW_slope_to_preset;
  real32_T FPP_LW_coast_dist_v_meas_lw;
  real32_T FPP_LW_leftGR_plaus;
  real32_T FPP_LW_rightGR_plaus;
  real32_T FPP_LW_leftVRE_plaus;
  real32_T FPP_LW_rightVRE_plaus;
  real32_T FPP_LW_leftGR_spp_sim;
  real32_T FPP_LW_rightGR_spp_sim;
  real32_T FPP_LW_leftGR_VRE_sim;
  real32_T FPP_LW_rightGR_VRE_sim;
  real32_T FPP_LW_leftVRE_llm_sim;
  real32_T FPP_LW_rightVRE_rlm_sim;
  uint8_T FPP_LW_left_bound_type;
  uint8_T FPP_LW_right_bound_type;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
} Struct_FPP_LW_Info_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ENV_FUSION_PATH_PLANNING1_T_
#define DEFINED_TYPEDEF_FOR_ENV_FUSION_PATH_PLANNING1_T_

typedef struct {
  real32_T FPP_POLY_COEFF_C3;
  real32_T FPP_POLY_COEFF_C2;
  real32_T FPP_POLY_COEFF_C1;
  real32_T FPP_POLY_COEFF_C0;
  real32_T FPP_POLY_COEFF_C0_Rate;
  real32_T measured_lane_width_m;
  real32_T FPP_roadFusionConf;
  real32_T FPP_SP_max_lane_width;
  real32_T FPP_SP_min_lane_width;
  real32_T FPP_max_po_ret_range;
  real32_T FPP_lm_predicted_status;
  real32_T FPP_max_po_acq_range;
  real32_T FPP_default_lane_width;
  real32_T FPP_max_coast_dist;
  real32_T FPP_PO_C3;
  real32_T FPP_PO_C2;
  real32_T FPP_PO_C1;
  real32_T FPP_PO_C0_Rate;
  real32_T FPP_PO_C0;
  real32_T pobj_model_max_range;
  real32_T FPP_po_state_age;
  real32_T FPP_po_use_cutout_output;
  real32_T FPP_po_rlm_extent_cutout;
  real32_T FPP_po_llm_extent_cutout;
  real32_T FPP_po_rlm_heading_cutout;
  real32_T FPP_po_llm_heading_cutout;
  real32_T FPP_po_yawrate_cutout;
  real32_T FPP_po_cutout;
  real32_T lon_pos;
  real32_T lat_pos;
  real32_T poly_correlation_coeff;
  int32_T sim_blm_po;
  int32_T sim_rlm_po;
  int32_T sim_llm_po;
  int32_T sim_llm_rlm;
  int32_T pobj_model_age;
  int32_T type_age;
  int32_T trail_ID;
  int32_T fusTrack_ID;
  uint8_T path_model_type;
  uint8_T steer_path_out_conf;
  uint8_T FPP_SP_status;
  uint8_T llm_model_conf;
  uint8_T rlm_model_conf;
  uint8_T lane_width_out_state;
  uint8_T FPP_pred_lmrkr_mode;
  uint8_T path_model_conf;
  uint8_T pobj_model_type;
  uint8_T po_out_status;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
} ENV_FUSION_PATH_PLANNING1_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ENV_FUSION_PATH_PLANNING2_T_
#define DEFINED_TYPEDEF_FOR_ENV_FUSION_PATH_PLANNING2_T_

typedef struct {
  real32_T FPP_llm_model_C3;
  real32_T FPP_llm_model_C2;
  real32_T FPP_llm_model_C1;
  real32_T FPP_llm_model_C0;
  real32_T FPP_llm_road_prediction_type;
  real32_T llm_model_max_range;
  real32_T FPP_llm_state_age;
  real32_T FPP_llm_age;
  real32_T FPP_rlm_model_C3;
  real32_T FPP_rlm_model_C2;
  real32_T FPP_rlm_model_C1;
  real32_T FPP_rlm_model_C0;
  real32_T FPP_rlm_road_prediction_type;
  real32_T rlm_model_max_range;
  real32_T FPP_rlm_state_age;
  real32_T FPP_rlm_age;
  real32_T FPP_lw_rightVRE_rlm_sim;
  real32_T FPP_lw_leftVRE_llm_sim;
  real32_T FPP_lw_rightGR_VRE_sim;
  real32_T FPP_lw_leftGR_VRE_sim;
  real32_T FPP_lw_rightVRE_plaus;
  real32_T FPP_lw_rightGR_spp_sim;
  real32_T FPP_lw_leftVRE_plaus;
  real32_T FPP_lw_leftGR_spp_sim;
  real32_T FPP_lw_rightGR_plaus;
  real32_T FPP_lw_leftGR_plaus;
  uint8_T llm_model_conf;
  uint8_T llm_model_lm_type;
  uint8_T FPP_llm_status;
  uint8_T rlm_model_conf;
  uint8_T rlm_model_type;
  uint8_T FPP_rlm_status;
  uint8_T right_bound_type;
  uint8_T left_bound_type;
  real32_T coast_distance_valid_measured_lw_m;
  real32_T FPP_lw_slope_to_preset;
  real32_T FPP_lw_slope_to_meas;
  real32_T distance_in_state_m;
  real32_T FPP_lw_max_coast_distance;
  real32_T FPP_vp_rlm_input_sim;
  real32_T FPP_vp_po_input_sim;
  real32_T FPP_vp_llm_input_sim;
  real32_T FPP_vp_blm_input_sim;
  real32_T FPP_vp_MPC;
  real32_T rwhl_rlm_offset;
  real32_T lwhl_llm_offset;
  real32_T FPP_vp_rlm_valid;
  real32_T FPP_vp_rlm_delta_valid;
  real32_T FPP_vp_pred_lw_valid;
  real32_T FPP_vp_pred_lw;
  real32_T FPP_vp_overall_lmrkr_valid;
  real32_T FPP_vp_llm_valid;
  real32_T FPP_vp_llm_delta_valid;
  real32_T FPP_vp_diverging;
  boolean_T rlm_straddle;
  boolean_T llm_straddle;
  uint8_T uint8_reserve1;
  uint8_T uint8_reserve2;
} ENV_FUSION_PATH_PLANNING2_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ENV_FUSION_PATH_PLANNING_T_
#define DEFINED_TYPEDEF_FOR_ENV_FUSION_PATH_PLANNING_T_

typedef struct {
  ENV_FUSION_PATH_PLANNING1_T ENV_FUSION_PATH_PLANNING1;
  ENV_FUSION_PATH_PLANNING2_T ENV_FUSION_PATH_PLANNING2;
} ENV_FUSION_PATH_PLANNING_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_spp_yaw_roadmodel_
#define DEFINED_TYPEDEF_FOR_struct_spp_yaw_roadmodel_

typedef struct {
  real32_T yawbased_path_valid_length;
  real32_T yawbased_path_coef_c0;
  real32_T yawbased_path_coef_c1;
  real32_T yawbased_path_coef_k;
  real32_T yawbased_path_coef_m;
  real32_T yawbased_path_confidence;
  real32_T yawbased_path_lane_width;
  real32_T yawbased_path_lane_center_offset;
} struct_spp_yaw_roadmodel;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_LaneBias_Out_T_
#define DEFINED_TYPEDEF_FOR_Struct_LaneBias_Out_T_

typedef struct {
  real32_T BiasCoastingDistance;
  real32_T Bias_A0_Offset_Unfiltered;
  real32_T Bias_A0_Offset;
  uint32_T RightBiasObjId;
  uint32_T LeftBiasObjId;
  uint8_T LaneBiasRequest;
  uint8_T LaneBiasStatus;
  uint8_T RightBiasReason;
  uint8_T LeftBiasReason;
} Struct_LaneBias_Out_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Struct_FPP_All_T_
#define DEFINED_TYPEDEF_FOR_Struct_FPP_All_T_

typedef struct {
  Struct_FPP_Poly_Coeff_T FPP_SP_PolyCoeff;
  Struct_FPP_SP_Info_1_T FPP_SP_Info_1;
  Struct_FPP_SP_Info_2_T FPP_SP_Info_2;
  Struct_FPP_VisPlaus_T FPP_VisPlaus;
  Struct_FPP_PO_Poly_Coeff_T FPP_PO_PolyCoeff;
  Struct_FPP_PO_Info_1_T FPP_PO_Info_1;
  Struct_FPP_PO_Info_2_T FPP_PO_Info_2;
  Struct_FPP_LLM_Poly_Coeff_T FPP_LLM_PolyCoeff;
  Struct_FPP_LLM_Info_1_T FPP_LLM_Info_1;
  Struct_FPP_RLM_Poly_Coeff_T FPP_RLM_PolyCoeff;
  Struct_FPP_RLM_Info_1_T FPP_RLM_Info_1;
  Struct_FPP_BLM_Info_T FPP_BLM_Info;
  Struct_FPP_SP_Info_3_T FPP_SP_Info_3;
  Struct_FPP_LW_Info_T FPP_LW_Info;
  ENV_FUSION_PATH_PLANNING_T ENV_FUSION_PATH_PLANNING;
  struct_spp_yaw_roadmodel FPP_YawRate_RM;
  Struct_LaneBias_Out_T LaneBias_Out;
  real32_T k_use_SPP;
  uint8_T FPP_RLC;
  uint8_T FPP_MajorVer;
  uint8_T FPP_MinorVer;
} Struct_FPP_All_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AES_Objs_
#define DEFINED_TYPEDEF_FOR_AES_Objs_

typedef struct {
  uint32_T id;
  uint32_T type;
  real32_T length;
  real32_T width;
  real32_T position_x;
  real32_T position_y;
  real32_T vx;
  real32_T vy;
  real32_T ax;
  real32_T ay;
  real32_T heading;
  real32_T leftbottom_latdis;
  real32_T leftbottom_lngdis;
  real32_T righttop_latdis;
  real32_T righttop_lngdis;
  real32_T rel_vx;
  real32_T rel_ax;
  real32_T ttc;
  AES_SceneType scenetype;
} AES_Objs;

#endif

#ifndef DEFINED_TYPEDEF_FOR_AES_CIPVTarget_
#define DEFINED_TYPEDEF_FOR_AES_CIPVTarget_

typedef struct {
  boolean_T CIPV_Valid;
  real32_T CIPV_LonPos;
  real32_T CIPV_LatPos;
  real32_T CIPV_LonVelRel;
  real32_T CIPV_LatVel;
  real32_T CIPV_LonAccel;
  real32_T CIPV_Heading;
  real32_T CIPV_Length;
  real32_T CIPV_Width;
} AES_CIPVTarget;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_AES_ESA_SWC_T RT_MODEL_AES_ESA_SWC_T;

#endif                                 /* RTW_HEADER_AES_ESA_SWC_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
