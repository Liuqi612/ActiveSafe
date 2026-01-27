/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include <array>
namespace senseAD {
namespace tap {
#define USE_SENSOR_CHECK false
struct AsCipEvaluatorParam {
  std::array<float, 8> k_xolc_funnel_range_points{
      {4.0, 12.0, 20.0, 40.0, 60.0, 80.0, 100.0, 150.0}};
  std::array<float, 8> k_xolc_funnel_width{
      {1.8, 2.5, 2.3, 2.2, 2.0, 1.8, 1.8, 1.8}};
};

struct AsHostEvaluatorParam {
  float k_host_spd_at_curve_thres = 9.0f;
  float k_host_curvature_at_curve_enter_thres = 0.001f;
  float k_host_curvature_at_curve_exit_thres = 0.0005f;
  uint16_t k_host_in_curve_reset_cnt = 5000;
  uint8_t k_host_fast_steer_cnt_thres = 10;
};
} // namespace tap
} // namespace senseAD
