
#include <string>

#include "math/vec.h"
#include "speed/speed_point.h"
#include "pncx_speed_finder.pb.h"
#include <absl/strings/str_format.h>

namespace pnc_x {
namespace planning {

SpeedPoint::SpeedPoint(double in_t, double in_s, double in_v, double in_a, double in_j)
    : t_(in_t), s_(in_s), v_(in_v), a_(in_a), j_(in_j) {}

double SpeedPoint::t() const { return t_; }

void SpeedPoint::set_t(double in_t) { t_ = in_t; }

double SpeedPoint::s() const { return s_; }

void SpeedPoint::set_s(double in_s) { s_ = in_s; }

double SpeedPoint::v() const { return v_; }

void SpeedPoint::set_v(double in_v) { v_ = in_v; }

double SpeedPoint::a() const { return a_; }

void SpeedPoint::set_a(double in_a) { a_ = in_a; }

double SpeedPoint::j() const { return j_; }

void SpeedPoint::set_j(double in_j) { j_ = in_j; }

void SpeedPoint::FromProto(const SpeedPointProto &proto) {
    t_ = proto.t();
    s_ = proto.s();
    v_ = proto.v();
    a_ = proto.a();
    j_ = proto.j();
}
void SpeedPoint::ToProto(SpeedPointProto *proto) const {
    proto->set_t(t_);
    proto->set_s(s_);
    proto->set_v(v_);
    proto->set_a(a_);
    proto->set_j(j_);
}

std::string SpeedPoint::DebugString() const {
    return absl::StrFormat(
        "{ t : %.6f, s : %.6f, v : %.6f, a : %.6f, j : %.6f }", t(), s(), v(),
        a(), j());
}

}  // namespace planning
}  // namespace pnc_x
