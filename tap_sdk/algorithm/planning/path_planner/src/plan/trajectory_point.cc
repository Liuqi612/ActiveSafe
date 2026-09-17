

#include "plan/trajectory_point.h"
#include "math/vec.h"
#include <absl/strings/str_format.h>

namespace pnc_x {
namespace planning {

double TrajectoryPoint::kSpeedEps = 0.001;

TrajectoryPoint::TrajectoryPoint(const TrajectoryPointProto &proto) {
    FromProto(proto);
}
TrajectoryPoint::TrajectoryPoint(const ApolloTrajectoryPointProto &proto) {
    FromProto(proto);
}

double TrajectoryPoint::ComputeLambda(double v, double psi) {
    const double clamped_v = (v < 0.0) ? std::min(v, -kSpeedEps) :
                                        std::max(v, kSpeedEps);
    return psi / clamped_v;
}

double TrajectoryPoint::ComputeMu(double v,
                                  double a,
                                  double lambda,
                                  double chi) {
    return (chi - (a * lambda)) / std::max(Sqr(v), Sqr(kSpeedEps));
}
double TrajectoryPoint::lambda() const { return ComputeLambda(v_, psi_); }
double TrajectoryPoint::mu() const { return ComputeMu(v_, a_, lambda(), chi_); }

double TrajectoryPoint::j() const { return j_; }
void TrajectoryPoint::set_j(double j) { j_ = j; }

double TrajectoryPoint::psi() const { return psi_; }
double TrajectoryPoint::chi() const { return chi_; }
void TrajectoryPoint::set_psi(double psi) { psi_ = psi; }
void TrajectoryPoint::set_chi(double chi) { chi_ = chi; }

void TrajectoryPoint::FromProto(const TrajectoryPointProto &proto) {
    SecondOrderTrajectoryPoint::FromProto(proto);
    j_ = proto.j();
    psi_ = proto.psi();
    chi_ = proto.chi();
}

void TrajectoryPoint::ToProto(TrajectoryPointProto *proto) const {
    SecondOrderTrajectoryPoint::ToProto(proto);
    proto->set_j(j_);
    proto->set_psi(psi_);
    proto->set_chi(chi_);
}

void TrajectoryPoint::FromProto(const ApolloTrajectoryPointProto &proto) {
    set_pos({proto.path_point().x(), proto.path_point().y()});
    set_s(proto.path_point().s());
    set_theta(proto.path_point().theta());
    set_kappa(proto.path_point().kappa());
    set_steer_angle(proto.path_point().steer_angle());
    set_psi(proto.path_point().lambda() * proto.v());

    set_t(proto.relative_time());
    set_v(proto.v());
    set_a(proto.a());
    set_j(proto.j());
}

void TrajectoryPoint::ToProto(ApolloTrajectoryPointProto *proto) const {
    proto->mutable_path_point()->set_x(pos_.x());
    proto->mutable_path_point()->set_y(pos_.y());
    proto->mutable_path_point()->set_s(s_);
    proto->mutable_path_point()->set_theta(theta_);
    proto->mutable_path_point()->set_kappa(kappa_);
    proto->mutable_path_point()->set_lambda(lambda());
    proto->mutable_path_point()->set_steer_angle(steer_angle_);

    proto->set_relative_time(t_);
    proto->set_v(v_);
    proto->set_a(a_);
    proto->set_j(j_);
    proto->set_yaw_rate(kappa_ * v_);
}

void TrajectoryPoint::ToProto(PoseTrajectoryPointProto *proto) const {
    SecondOrderTrajectoryPoint::ToProto(proto);
}

std::string TrajectoryPoint::DebugString() const {
    return absl::StrFormat(
        "pos: (%.4f %.4f) s: %.4f theta: %.5f kappa: %.4f psi: %.4f t: %.3f v: "
        "%.3f a: "
        "%.3f j: %.3f steer_angle: %.3f",
        pos().x(), pos().y(), s(), theta(), kappa(), psi(), t(), v(), a(), j(),
        steer_angle());
}

}  // namespace planning
}  // namespace pnc_x
