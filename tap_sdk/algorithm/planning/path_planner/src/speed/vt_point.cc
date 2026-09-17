
#include <string>

#include "speed/vt_point.h"

namespace pnc_x {
namespace planning {

VtPoint::VtPoint(double v, double t) : v_(v), t_(t) {}

double VtPoint::v() const { return v_; }

double VtPoint::t() const { return t_; }

void VtPoint::set_v(double v) { v_ = v; }

void VtPoint::set_t(double t) { t_ = t; }

std::string VtPoint::DebugString() const {
    return absl::StrFormat("{ t : %.6f, v : %.6f }", t(), v());
}

Vec2d ToVec2d(const VtPoint &point) { return Vec2d(point.t(), point.v()); }

}  // namespace planning
}  // namespace pnc_x
