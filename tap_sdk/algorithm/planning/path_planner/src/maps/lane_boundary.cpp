
#include "maps/lane_boundary.h"
#include "common/gflags.h"
namespace ads_x {
namespace planning {

LaneBoundary::LaneBoundary(const LaneBoundaryInfo &boundary_info) {
    points_.assign(boundary_info.points.begin(), boundary_info.points.end());
    id_ = boundary_info.id;
    type_ = boundary_info.boundary_type;
    InterpolatePoints();
}

void LaneBoundary::InterpolatePoints() {
    if (points_.size() < 2U) {
        return;
    }
    std::vector<Point2d> interpolate_points;
    interpolate_points.reserve(points_.size() * 2);
    interpolate_points.emplace_back(points_.front());
    const double map_gap_threshold_sqr =
        FLAGS_pnc_x_planning_map_point_distance_threshold *
        FLAGS_pnc_x_planning_map_point_distance_threshold;
    double total_length = 0.0;
    for (std::size_t i = 1; i < points_.size(); ++i) {
        total_length += points_.at(i).DistanceTo(points_.at(i - 1));
    }
    math::LineCurve2d tmp_curve(points_);
    tmp_curve.SamplePoints(0, total_length, &interpolate_points,
                           FLAGS_pnc_x_planning_boundary_interpolate_dist);
    if (interpolate_points.empty()) {
        interpolate_points.emplace_back(points_.front());
        interpolate_points.emplace_back(points_.back());
    } else if (interpolate_points.back().DistanceSquareTo(points_.back()) >
               map_gap_threshold_sqr) {
        interpolate_points.emplace_back(points_.back());
    }
    line_curve_.InitializePoints(interpolate_points);
    curve_length_ = line_curve_.length();
}

void LaneBoundary::PushLeftLane(const uint64_t lane_id) {
    left_lanes_.emplace_back(lane_id);
}
void LaneBoundary::PushRightLane(const uint64_t lane_id) {
    right_lanes_.emplace_back(lane_id);
}

const uint64_t LaneBoundary::id() const { return id_; };
const std::vector<Point2d> &LaneBoundary::points() const { return points_; }
const std::vector<Point2d> &LaneBoundary::curve_points() const {
    return line_curve_.points();
}
const math::LineCurve2d &LaneBoundary::line_curve() const {
    return line_curve_;
}
const LaneBoundaryType &LaneBoundary::type() const { return type_; }
const double &LaneBoundary::curve_length() const { return curve_length_; }
const std::vector<uint64_t> &LaneBoundary::left_lanes() const {
    return left_lanes_;
};
const std::vector<uint64_t> &LaneBoundary::right_lanes() const {
    return right_lanes_;
};
const double LaneBoundary::length() const { return length_; }
bool LaneBoundary::IsValid() const {
    return (points_.size() > 1U) && (line_curve_.points().size() > 1U);
}

void LaneBoundary::set_section_id(const uint64_t local_section_id) {
    section_id_ = local_section_id;
}
const uint64_t LaneBoundary::section_id() const { return section_id_; }

}  // namespace planning
}  // namespace ads_x
