
#pragma once

#include <string>

#include "math/vec.h"
#include "pncx_trajectory_point.pb.h"

namespace pnc_x {
namespace planning {

class SecondOrderTrajectoryPoint {
 public:
    SecondOrderTrajectoryPoint() = default;
    explicit SecondOrderTrajectoryPoint(const TrajectoryPointProto &proto);

    const Vec2d &pos() const;

    double s() const;
    double theta() const;
    double cos_theta() const;
    double sin_theta() const;
    double kappa() const;
    double steer_angle() const;
    void set_pos(const Vec2d &pos);
    void set_s(double s);
    void set_theta(double theta);
    void set_kappa(double kappa);
    void set_steer_angle(double steer_angle);

    double t() const;
    double v() const;
    double a() const;
    void set_t(double t);
    void set_v(double v);
    void set_a(double a);

    void FromProto(const SecondOrderTrajectoryPointProto &proto);
    void ToProto(SecondOrderTrajectoryPointProto *proto) const;

    void FromProto(const TrajectoryPointProto &proto);
    void ToProto(TrajectoryPointProto *proto) const;

    void ToProto(PoseTrajectoryPointProto *proto) const;

    std::string DebugString() const;

 protected:
    Vec2d pos_ = Vec2d::Zero();
    double s_ = 0.0;
    double theta_ = 0.0;
    double kappa_ = 0.0;
    double steer_angle_ = 0.0; // 方向盘转角

    double t_ = 0.0;
    double v_ = 0.0;
    double a_ = 0.0;

    double cos_theta_ = 1.0;
    double sin_theta_ = 0.0;
};

}  // namespace planning
}  // namespace pnc_x
