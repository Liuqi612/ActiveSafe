/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_ALGORITHM_LONGSAFE_EGO_CURVATURE_PATH_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_EGO_CURVATURE_PATH_H_
#include <array>
#include <cmath>
#include <string>

#include "math/geometry/geometry.h"
#include "math/utils/util_math.h"

namespace active_safety {
namespace longsafe {

struct MotionStateAtTime {
  float long_pos;
  float lat_pos;
  float lat_vel;
  float long_vel;
  float long_accel;
  float lat_accel;
  float heading_angle;
  float pred_curv;
  MotionStateAtTime()
      : long_pos(0.0F),
        lat_pos(0.0F),
        lat_vel(0.0F),
        long_vel(0.0F),
        long_accel(0.0F),
        lat_accel(0.0),
        heading_angle(0.0F),
        pred_curv(0.0) {}

  std::string ToString() {
    return std::string("(") + std::to_string(long_pos) + ", " + std::to_string(lat_pos) + ", " +
           std::to_string(heading_angle) + "), (" + std::to_string(long_vel) + ", " + std::to_string(lat_vel) + ")";
  }
};

class AsCurvaturePath {
 public:
  AsCurvaturePath() {}
  ~AsCurvaturePath() = default;
  void UpdatePath(float vlgt, float algt, float c0, float c1, float width, float length, float distRearToFnt,
                  bool enable_reverse = false);

  MotionStateAtTime GetHostState(float time) const;
 public:
  struct VehicleMotionStateT1 {
    float position_long{0.0F};
    float position_lat{0.0F};
    float speed{0.0F};
    float accel{0.0F};
    float vel_long{0.0F};
    float vel_lat{0.0F};
    float accel_long{0.0F};
    float accel_lat{0.0F};
    float curvature{0.0F};
    float heading_angle{0.0};
  };

  struct VehicleMotionStateT0 {
    float position_long{0.0F};
    float vel_long{0.0F};
    float accel{0.0F};
    float accel_long{0.0F};
    float position_lat{0.0F};
    float vel_lat{0.0F};
    float accel_lat{0.0F};
    float speed{0.0F};
    float curvature{0.0F};
    float curvature_rate{0.0F};
    float heading_angle{0.0};
  };

  struct PathEstimnInfo {
    float ctrl_point_long_p0{0.0F};
    float ctrl_point_long_p1{0.0F};
    float ctrl_point_long_p2{0.0F};
    float ctrl_point_long_p3{0.0F};
    float ctrl_point_lat_p0{0.0F};
    float ctrl_point_lat_p1{0.0F};
    float ctrl_point_lat_p2{0.0F};
    float ctrl_point_lat_p3{0.0F};
    float t0{0.0F};
    float t1{0.0};
  };

 private:
  std::size_t Time2Num(float time) const;
  std::size_t SelectSegment(float time);
  float EstimedPosn(float p0, float p1, float p2, float p3, float tau, float squrdTau, float thirdTau) const;
  float EstimedPosnDerivative(float p0, float p1, float p2, float p3, float tau, float squrdTau) const;
  float EstimedVelDerivative(float p0, float p1, float p2, float p3, float tau) const;
  MotionStateAtTime GetHostStateAtTime(float time, bool enable_reverse = false);

 private:
  const float spd_thres_in_evaluation     = 0.2F;
  static constexpr std::size_t SIZEOFHOST = 201;
  PathEstimnInfo path_estimn[4];
  std::array<MotionStateAtTime, SIZEOFHOST> hostPosInfo;
};
}  // namespace longsafe
}  // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_EGO_CURVATURE_PATH_H_
