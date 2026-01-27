/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include "algorithm/longsafe_2024/as_box2d.h"
#include "math/utils/util_math.h"
#include <array>
#include <cmath>
#include <string>

namespace senseAD {
namespace tap {

namespace math = active_safety::math;
using namespace active_safety::math;
struct EgoMotionStateAtTime {
    float long_pos;
    float lat_pos;
    float lat_vel;
    float long_vel;
    float long_accel;
    float lat_accel;
    float heading_angle;
    float pred_curv;
    EgoMotionStateAtTime()
        : long_pos(0.0f),
          lat_pos(0.0f),
          lat_vel(0.0f),
          long_vel(0.0f),
          long_accel(0.0f),
          lat_accel(0.0),
          heading_angle(0.0f),
          pred_curv(0.0) {}

    std::string ToString() {
        return std::string("(") + std::to_string(long_pos) + ", " +
               std::to_string(lat_pos) + ", " + std::to_string(heading_angle) +
               "), (" + std::to_string(long_vel) + ", " +
               std::to_string(lat_vel) + ")";
    }
};

class AsEgoPath {
 public:
    AsEgoPath() {}
    ~AsEgoPath() {}
    void UpdatePath(float vlgt,
                    float algt,
                    float c0,
                    float c1,
                    float width,
                    float length,
                    float distRearToFnt);

    EgoMotionStateAtTime GetHostState(float time) const;
    Box2D GetHostBoudingBox(float time) const;
    float GetEndTimeOfPath() const;

 public:
    struct VehicleMotionStateT1 {
        float position_long{0.0};
        float position_lat{0.0};
        float speed{0.0};
        float accel{0.0};
        float vel_long{0.0};
        float vel_lat{0.0};
        float accel_long{0.0};
        float accel_lat{0.0};
        float curvature{0.0};
        float heading_angle{0.0};
    };

    struct VehicleMotionStateT0 {
        float position_long{0.0};
        float vel_long{0.0};
        float accel{0.0};
        float accel_long{0.0};
        float position_lat{0.0};
        float vel_lat{0.0};
        float accel_lat{0.0};
        float speed{0.0};
        float curvature{0.0};
        float curvature_rate{0.0};
        float heading_angle{0.0};
    };

    struct PathEstimnInfo {
        float ctrl_point_long_p0{0.0};
        float ctrl_point_long_p1{0.0};
        float ctrl_point_long_p2{0.0};
        float ctrl_point_long_p3{0.0};
        float ctrl_point_lat_p0{0.0};
        float ctrl_point_lat_p1{0.0};
        float ctrl_point_lat_p2{0.0};
        float ctrl_point_lat_p3{0.0};
        float t0{0.0};
        float t1{0.0};
    };

    struct HostStateAtTime {
        EgoMotionStateAtTime host_state;
        Box2D host_box;
    };

 private:
    std::size_t Time2Num(float time) const;
    std::size_t SelectSegment(float time);
    float EstimedPosn(float p0,
                      float p1,
                      float p2,
                      float p3,
                      float tau,
                      float squrdTau,
                      float thirdTau) const;
    float EstimedPosnDerivative(float p0,
                                float p1,
                                float p2,
                                float p3,
                                float tau,
                                float squrdTau) const;
    float EstimedVelDerivative(
        float p0, float p1, float p2, float p3, float tau) const;
    EgoMotionStateAtTime GetHostStateAtTime(float time);

 private:
    const float spd_thres_in_evaluation = 0.2f;
    static constexpr std::size_t SIZEOFHOST = 201;
    PathEstimnInfo path_estimn[4];
    std::array<HostStateAtTime, SIZEOFHOST> hostPosInfo;
};
}  // namespace tap
}  // namespace senseAD
