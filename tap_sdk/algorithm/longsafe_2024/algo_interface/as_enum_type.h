/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#pragma once
#include <cstddef>
#include <cstdint>
namespace senseAD {
namespace tap {
enum class LongSafeFunction : uint8_t {
  FCW = 0,
  AEB = 1,
};
enum class TrackStatus : uint8_t {
  INVALID = 0,
  MERGED = 1,
  NEW = 2,
  NEW_COASTED = 3,
  NEW_UPDATED = 4,
  UPDATED = 5,
  COASTED = 6,
  RESERVED = 7,
};
enum class ObjectClass : uint8_t {
  UNDETERMINED = 0,
  CAR = 1,
  MOTORCYCLE = 2,
  TRUCK = 3,
  PEDESTRIAN = 4,
  POLE = 5,
  TREE = 6,
  ANIMAL = 7,
  GOD = 8,
  BICYCLE = 9,
  UNIDENTIFIED_VEHICLE = 10,
  THREEWHEEl_VEHICLE = 11,
  ESCOOTER = 12,
  GENOBJ = 13,
};
enum class ObjectConf : uint8_t {
  NONE = 0,
  LOW = 1,
  MED = 2,
  HIGH = 3,
};
enum class FusionSource : uint8_t {
  SINGLE_TRACKLET = 0,
  MULTIPLE_TRACKLET = 1,
  VISION_ONLY = 2,
  RADAR_VISION = 3,
  SRR_ONLY = 4,
};
enum class SideEnum : uint8_t {
  INVALID = 0,
  LEFT = 1,
  RIGHT = 2,
  LEFT_NEIGHBOUR = 3,
  RIGHT_NEIGHBOUR = 4,
};
enum class TrackRefPosn : uint8_t {
  FRONT_LEFT = 0,
  FRONT = 1,
  FRONT_RIGHT = 2,
  RIGHT = 3,
  REAR_RIGHT = 4,
  REAR = 5,
  REAR_LEFT = 6,
  LEFT = 7,
  CENTER = 8,
  INVALID = 255,
};
enum class PseudoMsmtType : uint8_t {
  PSEUDO_MSMT_NONE = 0,
  PSEUDO_MSMT_RADAR = 1,
  PSEUDO_MSMT_VISION = 2,
  PSEUDO_MSMT_VISION_POSN_ONLY = 3,
  PSEUDO_MSMT_RADARVISION = 4,
  PSEUDO_MSMT_RV_VISION = 5,
  PSEUDO_MSMT_RADAR_TAP = 6,
  PSEUDO_MSMT_RADARVISION_TAP = 7,
  PSEUDO_MSMT_VISION_ONLY_TAP = 8,
  PSEUDO_MSMT_RV_VISION_TAP = 9,
  PSEUDO_MSMT_RADARVISION_TAP_YAWRATE = 10,
  PSEUDO_MSMT_RV_VISION_TAP_YAWRATE = 11,
  PSEUDO_MSMT_RADARVISION_TAP_HEADING = 12,
  PSEUDO_MSMT_RV_VISION_TAP_HEADING = 13,
};
enum class ObjectMotionType : uint8_t {
  UNKNOWN = 0,
  PARRALLELL_STATIONARY,
  HORIZONTAL_STATIONARY,
  PROCEDING,
  LEFT_STRAIGHT_CROSS,
  RIGHT_STRAIGHT_CROSS,
  LEFT_ONCOMING_CROSS,
  RIGHT_OMCOMING_CROSS,
  LEFT_ONCOMING,
  RIGHT_OMCOMING,
  LEFT_PROCEEDING,
  RIGHT_PROCEEDING,
};
enum AsObstacleMotionPattern {
  AS_OBS_MP_UNKNOWN,
  AS_OBS_MP_STATIONARY,
  AS_OBS_MP_MOV_FROM_SELF,
  AS_OBS_MP_MOV_TO_SELF
};
enum AsObstacleSideNear {
  AS_OBS_SD_UNKNOWN = 0,
  AS_OBS_SD_FRONT,
  AS_OBS_SD_REAR,
  AS_OBS_SD_LEFT,
  AS_OBS_SD_RIGHT
};

enum class OnOffStatus : uint8_t { NotActive = 0, Active = 1 };

} // namespace tap
} // namespace senseAD
