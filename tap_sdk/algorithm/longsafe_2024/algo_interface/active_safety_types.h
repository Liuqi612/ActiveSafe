/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#ifndef TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_ACTIVE_SAFETY_TYPES_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_ACTIVE_SAFETY_TYPES_H_
#include <cstddef>
#include <cstdint>

namespace senseAD {
namespace tap {

typedef struct {
  uint32_t id;
  uint32_t type;
  uint32_t source;
  float posx;
  float posy;
  float spdx;
  float spdy;
  float accelx;
  float accely;
  float heading;
  float ttc;
  float width;
  float length;
} AsTargetInfo_T;

} // namespace tap
} // namespace senseAD
#endif // TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_ACTIVE_SAFETY_TYPES_H_
