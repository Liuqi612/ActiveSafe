
#pragma once

#include <memory>

#include "maps/lane_boundary.h"
#include "maps/map_def.h"
#include "math/line_curve2d.h"

namespace ads_x {
namespace planning {
class LaneBoundaries {
 public:
    explicit LaneBoundaries(
        const std::vector<LaneBoundaryConstPtr> &boundaries);
    ~LaneBoundaries() = default;

    const math::LineCurve2d &line_curve() const { return line_curve_; }

    const std::vector<LaneBoundaryType> &boundary_types() const {
        return boundary_types_;
    }

    const std::vector<LaneBoundaryConstPtr> &lane_boundaries() const {
        return boundaries_;
    };

    const int32_t GetBoundarySegmentIndex(const double &s) const;
    const bool CanCrossFromLeft() const { return can_cross_from_left_; }
    const bool CanCrossFromRight() const { return can_cross_from_right_; }
    const double GetRealLength() const;

 private:
    std::vector<LaneBoundaryConstPtr> boundaries_;
    std::vector<LaneBoundaryType> boundary_types_;
    math::LineCurve2d line_curve_;
    bool can_cross_from_left_ = false;
    bool can_cross_from_right_ = false;
    double real_length_ = 0.0;
};

using LaneBoundariesPtr = std::shared_ptr<LaneBoundaries>;
using LaneBoundariesConstPtr = std::shared_ptr<const LaneBoundaries>;

}  // namespace planning
}  // namespace ads_x
