
#pragma once

#include <memory>

#include "maps/lane_boundary.h"
#include "maps/map_def.h"
#include "math/line_curve2d.h"

namespace ads_x {
namespace planning {
class LaneBoundary {
 public:
    explicit LaneBoundary(const LaneBoundaryInfo &boundary_info);
    ~LaneBoundary() = default;

    void PushLeftLane(const uint64_t lane_id);
    void PushRightLane(const uint64_t lane_id);

    const uint64_t id() const;
    const std::vector<Point2d> &points() const;
    const std::vector<Point2d> &curve_points() const;
    const math::LineCurve2d &line_curve() const;
    const LaneBoundaryType &type() const;
    const double &curve_length() const;
    const std::vector<uint64_t> &left_lanes() const;
    const std::vector<uint64_t> &right_lanes() const;
    const double length() const;
    bool IsValid() const;

    void set_section_id(const uint64_t section_id);
    const uint64_t section_id() const;

 private:
    void InterpolatePoints();

 private:
    uint64_t id_;
    std::vector<Point2d> points_;
    std::vector<uint64_t> left_lanes_;
    std::vector<uint64_t> right_lanes_;
    math::LineCurve2d line_curve_;
    LaneBoundaryType type_;
    double length_ = 0.0;
    double curve_length_ = 0.0;

    uint64_t section_id_ = 0;
};

using LaneBoundaryPtr = std::shared_ptr<LaneBoundary>;
using LaneBoundaryConstPtr = std::shared_ptr<const LaneBoundary>;

}  // namespace planning
}  // namespace ads_x
