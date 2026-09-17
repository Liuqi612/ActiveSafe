

#include "plan/second_order_trajectory_point.h"
#include "math/geometry/util.h"
#include <absl/strings/str_format.h>
#include <cmath>

namespace pnc_x {
namespace planning {

SecondOrderTrajectoryPoint::SecondOrderTrajectoryPoint(
    const TrajectoryPointProto &proto) {
    FromProto(proto);
}

const Vec2d &SecondOrderTrajectoryPoint::pos() const { return pos_; }

double SecondOrderTrajectoryPoint::s() const { return s_; }
double SecondOrderTrajectoryPoint::theta() const { return theta_; }
double SecondOrderTrajectoryPoint::cos_theta() const { return cos_theta_; }
double SecondOrderTrajectoryPoint::sin_theta() const { return sin_theta_; }
double SecondOrderTrajectoryPoint::kappa() const { return kappa_; }
double SecondOrderTrajectoryPoint::steer_angle() const { return steer_angle_; }
void SecondOrderTrajectoryPoint::set_pos(const Vec2d &pos) { pos_ = pos; }
void SecondOrderTrajectoryPoint::set_s(double s) { s_ = s; }
void SecondOrderTrajectoryPoint::set_theta(double theta) {
    theta_ = theta;
    cos_theta_ = std::cos(theta_);
    sin_theta_ = std::sin(theta_);
}
void SecondOrderTrajectoryPoint::set_kappa(double kappa) { kappa_ = kappa; }
void SecondOrderTrajectoryPoint::set_steer_angle(double steer_angle) {
    steer_angle_ = steer_angle;
}

double SecondOrderTrajectoryPoint::t() const { return t_; }
double SecondOrderTrajectoryPoint::v() const { return v_; }
double SecondOrderTrajectoryPoint::a() const { return a_; }
void SecondOrderTrajectoryPoint::set_t(double t) { t_ = t; }
void SecondOrderTrajectoryPoint::set_v(double v) { v_ = v; }
void SecondOrderTrajectoryPoint::set_a(double a) { a_ = a; }

void SecondOrderTrajectoryPoint::FromProto(
    const SecondOrderTrajectoryPointProto &proto) {
    pos_ = Vec2dFromProto(proto.pos());
    s_ = proto.s();
    theta_ = proto.theta();
    kappa_ = proto.kappa();
    steer_angle_ = proto.steer_angle();

    cos_theta_ = std::cos(theta_);
    sin_theta_ = std::sin(theta_);

    t_ = proto.t();
    v_ = proto.v();
    a_ = proto.a();
}

void SecondOrderTrajectoryPoint::ToProto(
    SecondOrderTrajectoryPointProto *proto) const {
    Vec2dToProto(pos_, proto->mutable_pos());
    proto->set_s(s_);
    proto->set_theta(theta_);
    proto->set_kappa(kappa_);
    proto->set_steer_angle(steer_angle_);

    proto->set_t(t_);
    proto->set_v(v_);
    proto->set_a(a_);
}

void SecondOrderTrajectoryPoint::FromProto(const TrajectoryPointProto &proto) {
    pos_ = Vec2dFromProto(proto.pos());
    s_ = proto.s();
    theta_ = proto.theta();
    kappa_ = proto.kappa();
    steer_angle_ = proto.steer_angle();

    cos_theta_ = std::cos(theta_);
    sin_theta_ = std::sin(theta_);

    t_ = proto.t();
    v_ = proto.v();
    a_ = proto.a();
}

void SecondOrderTrajectoryPoint::ToProto(TrajectoryPointProto *proto) const {
    Vec2dToProto(pos_, proto->mutable_pos());
    proto->set_s(s_);
    proto->set_theta(theta_);
    proto->set_kappa(kappa_);
    proto->set_steer_angle(steer_angle_);

    proto->set_t(t_);
    proto->set_v(v_);
    proto->set_a(a_);
}

void SecondOrderTrajectoryPoint::ToProto(
    PoseTrajectoryPointProto *proto) const {
    Vec2dToProto(pos_, proto->mutable_pos());
    proto->set_theta(theta_);
    proto->set_t(t_);
}

std::string SecondOrderTrajectoryPoint::DebugString() const {
    return absl::StrFormat(
        "pos: (%.4f %.4f) s: %.4f theta: %.5f kappa: %.4f t: %.3f v: %.3f a: "
        "%.3f steer_angle: %.3f",
        pos().x(), pos().y(), s(), theta(), kappa(), t(), v(), a(),
        steer_angle());
}

}  // namespace planning
}  // namespace pnc_x
