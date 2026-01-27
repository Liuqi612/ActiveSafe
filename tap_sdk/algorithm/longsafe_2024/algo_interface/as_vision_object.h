/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#pragma once
#include <cstddef>
#include <cstdint>
namespace senseAD {
namespace tap {

constexpr std::size_t kMaxVisionObj{64};
typedef struct {
  uint8_t ObstaclesErrorWords;
  uint8_t ObstaclesMajorVersion;
  uint8_t ObstaclesMinorVersion;
  uint8_t pad1;
  uint8_t ObstaclesRollingCounter;
  uint8_t ObstaclesNum;
  uint8_t pad2;
  uint8_t pad3;
  uint64_t ObstaclesTimestampNSec;
} VisObjHeader_t;

typedef struct {
  uint8_t VisObstaclesRollingCounter;
  uint8_t VisObjClass;
  uint8_t VisTrackStatus;
  uint8_t visMovingStatus;
  uint32_t VisTrackAgeMs;
  int32_t VisTrkID_Raw;
  // change from uint8_t VisObjID
  uint32_t VisObjID;
  float VisClassConf;
  float VisLongPos;
  float VisLatPos;
  float VisLongVel;
  float VisLatVel;
  float VisHeading;
  float VisWidth;
  float VisHeight;
  float VisLength;
  float visLongAcc;
  float visLatAcc;
} VisObj_t;

typedef struct {
  VisObjHeader_t VisObjHeader;
  VisObj_t VisObj[kMaxVisionObj];
} AS_VisionObj_Info_T;

} // namespace tap
} // namespace senseAD
