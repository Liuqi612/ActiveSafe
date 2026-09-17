/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#ifndef TAP_SDK_ALGORITHM_LONGSAFE_2024_PARAM_AS_PARAM_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_2024_PARAM_AS_PARAM_H_
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>
namespace senseAD {
namespace tap {

typedef struct {
    float k_dist_to_rear_axle;
    float k_host_width;
    float k_host_length;
    float k_rear_cornering_compliance;
    float k_steer_ratio;
    float k_wheel_base;
    float k_vcs_camera_long_posn;
    float k_vcs_camera_lat_posn;
} AsVehicleParam;

typedef struct {
    uint8_t k_LgSf_UseShadowMode;
    uint8_t k_LgSf_AEB_Enable;
    uint8_t k_LgSf_EnCone;
    uint8_t k_LgSf_EnBarrier;
    float   k_LgSf_PosnLgtOffset;
    uint8_t k_LgSf_EnConfInhibit;
    uint8_t k_LgSf_EnEgoConfInhibit;
    uint8_t k_LgSf_EnObsConfInhibit;
    uint8_t k_LgSf_EnSceniaroCheck;
    uint8_t k_LgSf_EnAWB;
    float   k_LgSf_MinAebDecelValue;
    uint8_t k_LgSf_EnHighMiles;
    uint8_t k_LgSf_EnSimulationMode;
    uint8_t k_LgSf_ActiveSafeMode;
    uint8_t k_ignore_roadedge_check;
    uint8_t k_LgSf_EnTestScene;
    uint8_t k_LgSf_EnOcc;
    uint8_t k_LgSf_EnAebDecelNoFilter;
    float   k_LgSf_AebVehSpdRednLim;
    float   k_AEB_FullBrkSpdThres;
    float   k_AEB_HighReqDecel;
} AsParamConfig_T;

typedef struct {
    uint8_t k_enable_aeb_diag;
    uint8_t k_enable_lka_diag;
    uint8_t k_enable_esa_diag;
    uint8_t k_enable_aes_diag;
    uint8_t k_enable_elk_diag;
    uint8_t k_enable_locp_diag;
    uint8_t k_enable_fcta_diag;
    uint8_t k_enable_rcta_diag;
    uint8_t k_enable_dow_diag;
    uint8_t k_enable_bsd_diag;
    uint8_t k_enable_rcw_diag;
    uint8_t k_enable_ldw_diag;

} AsDiagParam_T;

} // namespace tap
} // namespace senseAD
#endif // TAP_SDK_ALGORITHM_LONGSAFE_2024_PARAM_AS_PARAM_H_
