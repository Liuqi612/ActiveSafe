
#include "speed/st_point.h"
#include <string>

namespace pnc_x {
namespace planning {

StPoint::StPoint(double s, double t) : s_(s), t_(t) {}

double StPoint::s() const { return s_; }

double StPoint::t() const { return t_; }

void StPoint::set_s(double s) { s_ = s; }

void StPoint::set_t(double t) { t_ = t; }

std::string StPoint::DebugString() const {
    return absl::StrFormat("{ t : %.6f, s : %.6f }", t(), s());
}

Vec2d ToVec2d(const StPoint &point) { return Vec2d(point.t(), point.s()); }

}  // namespace planning
}  // namespace pnc_x
