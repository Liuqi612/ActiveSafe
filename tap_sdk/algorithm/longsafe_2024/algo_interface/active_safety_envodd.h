/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */

#pragma once
#include <stdint.h>
namespace senseAD {
namespace tap {
enum class SceneBrightness : uint8_t {
  UNKNOWN = 0,
  DAYTIME = 1,
  NIGHT_BRIGHT = 2,
  NIGHT_DARK = 3
};

enum class WeatherSceneInfo : uint8_t {
  UNKNOWN = 0,
  OVERCAST = 1,
  SUNNY = 2,
  RAINY = 3,
  FOGGY = 4,
  SNOWY = 5,
  SANDY = 6,
  OTHERS = 7,
};

enum class SceneEnvironmentInfo : uint8_t {
  UNKNOWN = 0,
  OPEN_ROAD = 1,
  CLOSED_ROAD = 2,
  TUNNEL = 3,
};

enum class BlobBrightnessState : uint8_t {
  UNKNOWN = 0,
  BRIGHT = 1,
  DARK = 2,
};

struct SceneInfo {
  SceneBrightness scene_brightness;
  WeatherSceneInfo scene_weather;
  SceneEnvironmentInfo scene_environment;
  uint8_t resv1;
};

struct AsEnvOddInfo {
  uint64_t frame_timestamp_ns;
  //   int16_t sensor_id;
  SceneInfo scene_info;
  BlobBrightnessState city_lights_info;
  uint8_t resv1;
  int16_t resv2;
};

} // namespace tap
} // namespace senseAD
