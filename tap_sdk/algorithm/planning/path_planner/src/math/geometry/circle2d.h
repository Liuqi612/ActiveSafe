
#pragma once

#include <algorithm>
#include <string>
#include <absl/strings/str_cat.h>

#include "path_planner/src/common/throw_check.h"
#include "path_planner/src/math/util.h"
#include "path_planner/src/math/vec.h"

namespace pnc_x {

class Circle2d {
 public:
    Circle2d() = default;
    Circle2d(const Vec2d &center_in, double radius_in)
        : center_(center_in), radius_(radius_in) {
        XCHECK_GE(radius_, 0.0);
    }

    Vec2d center() const { return center_; }
    double radius() const { return radius_; }

    bool Inside(const Vec2d &v) const {
        return Sqr(radius_) >= Vec2d(v - center_).Sqr();
    }

    bool HasOverlap(const Circle2d &other) const {
        return center().DistanceSquareTo(other.center()) <=
               Sqr(radius() + other.radius());
    }

    std::string DebugString() const {
        return absl::StrCat("center: ", center_.DebugString(),
                            ", radius: ", radius_);
    }

    Vec2d PointAtUnit(const Vec2d &unit) const {
        return unit * radius_ + center_;
    }

    bool IsPointOn(const Vec2d &point, double epsilon) const {
        epsilon = std::max(0.0, epsilon);
        const double max_dist_sqr = Sqr(radius_ + epsilon);
        const double min_dist_sqr = Sqr(std::max(radius_ - epsilon, 0.0));
        const double dist_sqr = (point - center_).Sqr();
        return (min_dist_sqr <= dist_sqr) && (dist_sqr <= max_dist_sqr);
    }

 private:
    Vec2d center_;
    double radius_ = 0.0;
};
}  // namespace pnc_x
