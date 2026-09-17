
#pragma once

#include <memory>

#include "common/type_def.h"
#include "maps/map_def.h"
#include "math/polygon2d.h"

namespace ads_x {
namespace planning {
class Crosswalk {
 public:
    Crosswalk() = default;
    Crosswalk(const CrossWalkInfo &cross_walk_info);

    const uint64_t id() const;
    const std::vector<Point2d> &points() const;
    const bool IsValid() const;

    double DistanceTo(const Point2d &point) const;
    const math::Polygon2d &polygon() const;

    void add_intersected_lanes(const uint64_t lane_id);

    pnc_x::Segment2d bone_axis_smooth() const;

 protected:
    std::vector<Point2d> points_;
    math::Polygon2d polygon_;
    uint64_t id_;
    bool is_polygon_convex_ = false;
    std::set<uint64_t> intersected_lanes_;
    pnc_x::Segment2d bone_axis_smooth_;
};

using CrosswalkPtr = std::shared_ptr<Crosswalk>;
using CrosswalkConstPtr = std::shared_ptr<const Crosswalk>;

}  // namespace planning
}  // namespace ads_x
