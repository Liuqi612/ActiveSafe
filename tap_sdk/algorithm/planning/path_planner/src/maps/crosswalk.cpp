

#include "maps/crosswalk.h"
#include "math/geometry/polygon2d.h"
namespace ads_x {
namespace planning {
Crosswalk::Crosswalk(const CrossWalkInfo &cross_walk_info) {
    id_ = cross_walk_info.id;
    points_.assign(cross_walk_info.points.begin(),
                   cross_walk_info.points.end());
    is_polygon_convex_ = math::Polygon2d::ComputeConvexHull(points_, &polygon_);
    bone_axis_smooth_ = pnc_x::Polygon2d(points_).GetPrincipalAxis();
}

double Crosswalk::DistanceTo(const Point2d &point) const {
    if (is_polygon_convex_) return polygon_.DistanceTo(point);
    return std::numeric_limits<double>::max();
}

const uint64_t Crosswalk::id() const { return id_; }
const std::vector<Point2d> &Crosswalk::points() const { return points_; }
const bool Crosswalk::IsValid() const { return is_polygon_convex_; }

const math::Polygon2d &Crosswalk::polygon() const { return polygon_; };

void Crosswalk::add_intersected_lanes(const uint64_t lane_id) {
    intersected_lanes_.insert(lane_id);
}

pnc_x::Segment2d Crosswalk::bone_axis_smooth() const {
    return bone_axis_smooth_;
}

}  // namespace planning
}  // namespace ads_x
