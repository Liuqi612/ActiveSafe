/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 * Hu Gongman <hugongman@senseauto.com>
 */

#pragma once
#include <cstddef>
#include <cstdint>
// 0x2
namespace senseAD {
namespace tap {
struct LaneMarker_t {
  uint8_t LineObjectsRollingCounter;
  uint8_t LineValid;
  uint8_t LineColor;
  uint8_t LineType;

  float LineConf;

  float LineViewRangeStart;
  float LineViewRangeEnd;

  float LineMakerWidth;
  float LinePolyC0;
  float LinePolyC1;
  float LinePolyC2;
  float LinePolyC3;
};

struct RoadEdge_t {
  uint8_t LineObjectsRollingCounter;
  uint8_t LineValid;
  uint8_t LineColor;
  uint8_t LineType;

  float LineConf;
  float LineViewRangeStart;
  float LineViewRangeEnd;
  float LineMakerWidth;
  float LinePolyC0;
  float LinePolyC1;
  float LinePolyC2;
  float LinePolyC3;
};

struct LaneMarkerHeader_t {
  uint8_t LineObjectsErrorWords;
  uint8_t LineObjectsRollingCounter;
  uint8_t LineObjectsMajorVersion;
  uint8_t LineObjectsMinorVersion;
  // @LaneMarkerHeader_t, change from xxxstampMS
  // to spliting xxxstampSec and xxxstampNSec
  uint32_t LineObjectsTimeStampSec;
  uint32_t LineObjectsTimeStampNSec;
};

struct AS_LaneMarkerInfo_T {
  LaneMarkerHeader_t LaneMarkerHeader;
  LaneMarker_t HostLeftLaneMarker;
  LaneMarker_t HostRightLaneMarker;
  LaneMarker_t LeftLaneLeftLaneMarker;
  LaneMarker_t LeftLaneRightLaneMarker;
  LaneMarker_t RightLaneLeftLaneMarker;
  LaneMarker_t RightLaneRightLaneMarker;
  LaneMarker_t RearLaneLeftLaneMarker;
  LaneMarker_t RearLaneRightLaneMarker;
  RoadEdge_t LeftRoadEdge;
  RoadEdge_t RightRoadEdge;
};

} // namespace tap
} // namespace senseAD
