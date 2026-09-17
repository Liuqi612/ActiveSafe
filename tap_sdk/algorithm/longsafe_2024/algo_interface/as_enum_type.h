/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#ifndef TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_AS_ENUM_TYPE_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_AS_ENUM_TYPE_H_
#include <cstddef>
#include <cstdint>
#include "../../../common/enum_type.h"
namespace senseAD {
namespace tap {
using active_safety::OnOffStatus;
enum class LongSafeFunction : uint8_t {
  FCW = 0,
  AEB = 1,
};
enum class ObjectConf : uint8_t {
  NONE = 0,
  LOW = 1,
  MED = 2,
  HIGH = 3,
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
enum AsObstacleSideNear {
  AS_OBS_SD_UNKNOWN = 0,
  AS_OBS_SD_FRONT,
  AS_OBS_SD_REAR,
  AS_OBS_SD_LEFT,
  AS_OBS_SD_RIGHT
};

} // namespace tap
} // namespace senseAD
#endif // TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_AS_ENUM_TYPE_H_
