/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#pragma once
#include "common/enum_type.h"

#include <cstddef>
#include <cstdint>

namespace active_safety {

constexpr std::size_t kMaxFusionObject{96};
constexpr std::size_t kMaxNormalObject{80};
constexpr std::size_t kMaxGopObject{16};

typedef struct {
    uint8_t track_id;
    uint8_t vis_trk_id;
    int32_t fus_trkID;
    int32_t vis_trkID;

    float speed;
    float age;
    float lat_posn;
    float long_posn;
    float lat_vel;
    float long_vel;
    float lat_accel;
    float long_accel;
    float heading;

    ObsConfidence confidence;
    TrackStatus status;
    ObjectClass object_class;
    FusionSource fusion_source;

    uint8_t resv1;
    float length;
    float width;
    float height;
} FusionObs;

typedef struct {
    uint64_t time;
    uint32_t seq_num;
    uint64_t gop_time;
    uint32_t gop_seq_num;
    FusionObs trk[kMaxFusionObject];
} FusionInfo;

} // namespace active_safety
