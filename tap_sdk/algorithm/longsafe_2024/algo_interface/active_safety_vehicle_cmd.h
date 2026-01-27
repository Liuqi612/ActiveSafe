/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */

#pragma once
#include <stdint.h>
namespace senseAD {
namespace tap {
enum class BrakeMode : uint8_t {
  // # 不请求刹车
  idle,
  // # 请求缓慢刹车(APA发送电刹+机械刹车)
  apaComfortable,
  // # 请求缓慢刹车(LAPA发送-仅电刹车)
  lApaComfortable,
  // # 请求急刹(APA/LAPA发送电刹+机械刹车)
  emergency
};
struct BrakeCmd {
  float command;
  uint8_t commandType;
  bool ignore;
  uint32_t parkingBrake;
  BrakeMode brakeMode;
};
struct AsVehicleCmdInfo {
  BrakeCmd brake;
  bool is_avp_state;
};
} // namespace tap
} // namespace senseAD
