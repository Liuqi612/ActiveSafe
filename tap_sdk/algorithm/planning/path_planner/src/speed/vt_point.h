
#pragma once

#include <string>

#include "math/vec.h"
#include <absl/strings/str_format.h>

namespace pnc_x {
namespace planning {

class VtPoint {
 public:
    VtPoint() = default;

    VtPoint(double v, double t);

    double v() const;

    double t() const;

    void set_v(double v);

    void set_t(double t);

    std::string DebugString() const;

 private:
    double v_ = 0.0;
    double t_ = 0.0;
};

Vec2d ToVec2d(const VtPoint &point);

}  // namespace planning
}  // namespace pnc_x
