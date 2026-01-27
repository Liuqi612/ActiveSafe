/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#pragma once
#include <cstddef>
#include <cstdint>
namespace active_safety {

typedef struct {
    uint32_t id;
    uint32_t type;
    uint32_t source;
    float    posx;
    float    posy;
    float    spdx;
    float    spdy;
    float    accelx;
    float    accely;
    float    heading;
    float    ttc;
} AsTargetInfo_T;

} // namespace active_safety