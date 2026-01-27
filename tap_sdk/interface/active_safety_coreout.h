/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#pragma once
#include "interface/active_safety_vse.h"

#include <cstddef>
#include <cstdint>

namespace active_safety {

struct AsLongSafeObject {
    uint8_t  index        = 0;
    uint8_t  status       = 0;
    uint16_t age          = 0;
    int32_t  vis_trkId    = 0;
    int32_t  fus_trkId    = 0;
    int32_t  object_class = 0;
    /* 0:SINGLE_TRACKLET;1:MULTIPLE_TRACKLET;2:VISION_ONLY;3:RADAR_VISION;4:SRR_ONLY*/
    int32_t detection_sensor                = 0;
    float   long_posn                       = 0.0f;
    float   lat_posn                        = 0.0f;
    float   heading                         = 0.0f;
    float   speed                           = 0.0f;
    float   lat_vel                         = 0.0f;
    float   long_vel                        = 0.0f;
    float   lat_accel                       = 0.0f;
    float   long_accel                      = 0.0f;
    float   ttc                             = 0.0f;
    float   xolc                            = 0.0f;
    float   lat_est                         = 0.0f;
    float   accel_lat_req                   = 0.0f;
    float   accel_lgt_req                   = 0.0;
    float   length                          = 0.0f;
    float   width                           = 0.0f;
    float   pred_long_accel                 = 0.0f;
    float   pred_lat_accel                  = 0.0f;
    float   pred_accel                      = 0.0f;
    float   pred_cvt                        = 0.0f;
    float   offs_lgt_pred                   = 0.0f;
    float   offs_lat_pred                   = 0.0f;
    float   offs_lat_manoeuvre              = 0.0f;
    float   offs_lat_in_path_primary_target = 0.0f;
    float   offs_lat_in_path_close_edge     = 0.0f;
    float   offs_lat_in_path_far_edge       = 0.0f;
    float   offs_lat_intersection           = 0.0f;
    float   offs_lat_multi_target           = 0.0f;
    float   abs_heading                     = 0.0;
    float   length_side_lgt                 = 0.0f;
    float   length_side_lat                 = 0.0f;
    float   sin_rotation                    = 0.0f;
    float   cos_rotation                    = 0.0f;
    uint8_t inpath_current                  = false;
    uint8_t inpath_predict                  = false;
    uint8_t match_conf                      = 0;
    uint8_t motion_type                     = 0;
    uint8_t stationary                      = false;
    uint8_t moving_oncoming                 = false;
    uint8_t para_veh_pred                   = false;
    uint8_t obs_is_vehicle                  = false;
    uint8_t obs_is_motor_veh                = false;
    uint8_t curved_motion                   = false;
    uint8_t side_closest                    = false;
};

struct AsScenarioInfo {
    uint32_t obj_evaluator;
    uint32_t resv1;
    uint32_t resv2;
    uint32_t resv3;
};

struct AsTimeInfo {
    uint64_t cur_time;
    uint64_t fus_time;
    uint64_t roadgeometry_time;
    uint64_t vehicle_time;
    uint64_t gop_time;
    uint64_t vehicle_cmd_time;
    uint64_t occ_time;
    uint64_t resv1_time;
    uint64_t resv2_time;
    uint64_t resv3_time;
    // 0:default 1:avp_meb
    uint64_t tap_mode;
    uint8_t  tsel_lgsf_cnt;
    uint8_t  tsel_sf_cnt;
    uint8_t  ctrl_lgsf_cnt;
    uint8_t  ctrl_sf_cnt;
};

struct AsLongSafeOut {
    AsLongSafeObject longsafe_aeb;
    AsLongSafeObject longsafe_fcw;
    AsScenarioInfo   longsafe_scenario;
    uint8_t          longsafe_roll_cnt;
    uint8_t          longsafe_major_version;
    uint8_t          longsafe_minor_version;
};

struct AsOnComingObject {
    float   vcs_long_posn;
    float   vcs_long_vel;
    float   vcs_long_accel;
    float   vcs_lat_posn;
    float   vcs_lat_vel;
    float   vcs_lat_accel;
    float   width;
    float   length;
    float   vcs_rm_dis;
    float   curv_heading;
    uint8_t object_class;
    uint8_t fusion_source;
    uint8_t track_status;
    uint8_t movement;
    uint8_t cmbbPrimaryConfidence;
    uint8_t FcwConfidence;
    uint8_t maturity;
    uint8_t visTrkID;
    uint8_t f_oncoming;
    uint8_t track_id;
    uint8_t oncom_confidence;
    uint8_t collision_prob;
};

struct AsOverTakingObject {
    float   vcs_long_posn;
    float   vcs_long_vel;
    float   vcs_long_accel;
    float   vcs_lat_posn;
    float   vcs_lat_vel;
    float   vcs_lat_accel;
    float   width;
    float   length;
    float   vcs_heading;
    float   confidence;
    uint8_t object_class;
    uint8_t fusion_source;
    uint8_t track_status;
    uint8_t visTrkID;
    uint8_t track_id;
};

struct AsOnComingOut {
    AsOnComingObject oncom_target_1;
    AsOnComingObject oncom_target_2;
    AsOnComingObject oncom_target_3;
    uint8_t          as_oncoming_rollcnt;
    uint8_t          oncoming_major_version;
    uint8_t          oncoming_minor_version;
    uint8_t          u8_reserve1;
};

struct AsOverTakingOut {
    AsOverTakingObject overtake_target_rear_left;
    AsOverTakingObject overtake_target_rear_right;
    AsOverTakingObject overtake_target_front_left;
    AsOverTakingObject overtake_target_front_right;
    uint8_t            as_overtaking_rollcnt;
    uint8_t            overtaking_major_version;
    uint8_t            overtaking_minor_version;
    uint8_t            u8_reserve1;
};

struct AsSfObjInfo {
    int32_t objID;
    float   crashPointXl;
    float   crashProb;
    float   objTTC;
    float   objHeading;
    float   objLongPos;
    float   objLatPos;
    float   objLongVel;
    float   objLatVel;
    float   objLongAccel;
    float   objLatAceel;
    float   objAlertCnt;
    float   objAlertCntThresh;
    float   objInZone;
    float   objAlertLevel;
};

struct AsDowOut {
    uint32_t    left_alert;
    uint32_t    right_alert;
    AsSfObjInfo left_obj;
    AsSfObjInfo right_obj;
};

struct AsLcdaOut {
    uint32_t    bsd_left_alert;
    uint32_t    bsd_right_alert;
    uint32_t    cvw_left_alert;
    uint32_t    cvw_right_alert;
    AsSfObjInfo bsd_left_obj;
    AsSfObjInfo bsd_right_obj;
    AsSfObjInfo cvw_left_obj;
    AsSfObjInfo cvw_right_obj;
};

struct AsCtsOut {
    uint32_t    fcta_left_alert;
    uint32_t    fcta_right_alert;
    uint32_t    rcta_left_alert;
    uint32_t    rcta_right_alert;
    AsSfObjInfo fcta_left_obj;
    AsSfObjInfo fcta_right_obj;
    AsSfObjInfo rcta_left_obj;
    AsSfObjInfo rcta_right_obj;
};

struct AsRcwOut {
    uint32_t    rcw_alert;
    AsSfObjInfo obj;
};

struct AsSideFeatureOut {
    uint8_t   sf_rollingcnt;
    uint8_t   sf_major_version;
    uint8_t   sf_minor_version;
    uint8_t   resv1;
    AsDowOut  dow;
    AsLcdaOut lcda;
    AsCtsOut  cts;
    AsRcwOut  rcw;
};

struct AsCoreOut_T {
    AsLongSafeOut    longsafe;
    AsSideFeatureOut sidefeature;
    AsOnComingOut    oncoming;
    AsOverTakingOut  overtaking;
    AsTimeInfo       time;
    uint8_t          activesafety_rollingcnt;
    uint8_t          major_version;
    uint8_t          middle_version;
    uint8_t          minor_version;
};

} // namespace active_safety
