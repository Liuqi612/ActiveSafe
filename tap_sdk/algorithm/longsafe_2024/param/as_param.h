/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#pragma once
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

} AsParamConfig_T;

} // namespace tap
} // namespace senseAD
