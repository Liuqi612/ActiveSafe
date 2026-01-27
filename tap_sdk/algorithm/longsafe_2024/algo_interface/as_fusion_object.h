/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#pragma once
#include "as_enum_type.h"

#include <cstddef>
#include <cstdint>
namespace senseAD {
namespace tap {
constexpr std::size_t kMaxFusionObject{96};
constexpr std::size_t kMaxNormalObject{80};
constexpr std::size_t kMaxGopObject{16};
typedef struct {
    uint8_t      track_id;
    uint8_t      vis_trk_id;
    uint16_t     age;
    int32_t      fus_trkID;
    int32_t      vis_trkID;
    float        speed;
    float        lat_posn;
    float        long_posn;
    float        lat_vel;
    float        long_vel;
    float        lat_accel;
    float        long_accel;
    float        heading;
    float        confidence;
    TrackStatus  status;
    ObjectClass  object_class;
    FusionSource fusion_source;
    uint8_t      resv1;
    float        length;
    float        width;
    float        height;
} AS_FusObject_T;

typedef struct {
    uint32_t       look_index;
    uint64_t       time;
    AS_FusObject_T trk[kMaxFusionObject];
    uint32_t       gop_cnt;
    uint64_t       gop_time;
} AS_FusionInfo_T;

} // namespace tap
} // namespace senseAD
