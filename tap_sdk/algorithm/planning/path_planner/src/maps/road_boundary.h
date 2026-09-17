
#pragma once

#include <memory>

#include "maps/map_def.h"
#include "maps/road_boundary.h"
#include "math/line_curve2d.h"
namespace ads_x {
namespace planning {
class RoadBoundary {
 public:
    explicit RoadBoundary(const RoadBoundaryInfo &road_boundary_info);
    ~RoadBoundary() = default;

    const uint64_t id() const;
    const std::vector<Point2d> &points() const;
    const std::vector<Point2d> &curve_points() const;
    const math::LineCurve2d &line_curve() const;
    const RoadBoundaryType &type() const;
    const double &curve_length() const;
    const double length() const;
    bool IsValid() const;

    void set_section_id(const uint64_t section_id);
    const uint64_t section_id() const;

    static bool GetRoadBoundaryPoints(
        const std::vector<Point2d> &center_pts,
        const std::vector<math::LineSegment2d> &road_segs,
        const std::pair<double, double> &lat_dist_range,
        std::vector<Point2d> *road_pts);

    bool has_height() const;
    double height() const;

 private:
    void InterpolatePoints();

 private:
    uint64_t id_;
    std::vector<Point2d> points_;
    math::LineCurve2d line_curve_;
    RoadBoundaryType type_;
    double length_ = 0.0;
    double curve_length_ = 0.0;

    uint64_t section_id_ = 0;
};
using RoadBoundaryPtr = std::shared_ptr<RoadBoundary>;
using RoadBoundaryConstPtr = std::shared_ptr<const RoadBoundary>;
}  // namespace planning
}  // namespace ads_x
