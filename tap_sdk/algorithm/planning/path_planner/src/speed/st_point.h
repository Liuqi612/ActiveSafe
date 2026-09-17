
#pragma once

#include <string>

#include "math/vec.h"
#include <absl/strings/str_format.h>

namespace pnc_x {
namespace planning {

class StPoint {
 public:
    StPoint() = default;

    StPoint(double s, double t);

    double s() const;

    double t() const;

    void set_s(double s);

    void set_t(double t);

    std::string DebugString() const;

 private:
    double s_ = 0.0;
    double t_ = 0.0;
};

Vec2d ToVec2d(const StPoint &point);

}  // namespace planning
}  // namespace pnc_x
