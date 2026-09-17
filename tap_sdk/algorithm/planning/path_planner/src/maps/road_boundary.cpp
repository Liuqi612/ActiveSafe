

#include "maps/road_boundary.h"
#include "common/gflags.h"
namespace ads_x {
namespace planning {

RoadBoundary::RoadBoundary(const RoadBoundaryInfo &road_boundary_info) {
    points_.assign(road_boundary_info.points.begin(),
                   road_boundary_info.points.end());
    id_ = road_boundary_info.id;
    type_.boundary_type = road_boundary_info.boundary_type;
    type_.width = road_boundary_info.width;
    InterpolatePoints();
}

void RoadBoundary::InterpolatePoints() {
    if (points_.size() < 2U) {
        return;
    }
    std::vector<Point2d> interpolate_points;
    const double map_gap_threshold_sqr =
        FLAGS_pnc_x_planning_map_point_distance_threshold *
        FLAGS_pnc_x_planning_map_point_distance_threshold;
    double total_length = 0.0;
    for (std::size_t i = 1; i < points_.size(); ++i) {
        total_length += points_.at(i).DistanceTo(points_.at(i - 1));
    }

    int insert_cnt = static_cast<int>(
        total_length / FLAGS_pnc_x_planning_boundary_interpolate_dist);
    interpolate_points.reserve(static_cast<size_t>(insert_cnt));
    math::LineCurve2d tmp_curve(points_);
    tmp_curve.SamplePoints(0.0, total_length, &interpolate_points,
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

bool RoadBoundary::GetRoadBoundaryPoints(
    const std::vector<Point2d> &center_pts,
    const std::vector<math::LineSegment2d> &road_segs,
    const std::pair<double, double> &lat_dist_range,
    std::vector<Point2d> *road_pts) {
    road_pts->clear();
    if (lat_dist_range.first < lat_dist_range.second) {
        // LOG(ERROR) << "<GetRoadBoundaryPoints> lat_dist_range errror";
    }

    double kDefaultDist = Constants::DEFAULT_LANE_WIDTH;
    std::vector<math::LineSegment2d> crossprod_vecs;
    for (size_t i = 1; i < center_pts.size(); i++) {
        math::Vec2d center_vec = center_pts[i] - center_pts[i - 1];
        center_vec.Normalize();
        const math::Vec2d lat_vec(-center_vec.y(), center_vec.x());
        crossprod_vecs.emplace_back(center_pts[i - 1] + (kDefaultDist * lat_vec),
                                    center_pts[i - 1] - (kDefaultDist * lat_vec));
        if (i + 1 == center_pts.size()) {
            crossprod_vecs.emplace_back(center_pts[i] + (kDefaultDist * lat_vec),
                                        center_pts[i] - (kDefaultDist * lat_vec));
        }
    }

    bool has_in_range = false;
    for (const auto &cross_vec : crossprod_vecs) {
        double dist_min = DBL_MAX;
        Point2d road_pt;
        for (const auto &road_seg : road_segs) {
            Point2d intersect_pt;
            if (cross_vec.GetIntersect(road_seg, &intersect_pt)) {
                const double dist =
                    kDefaultDist - cross_vec.start().DistanceTo(intersect_pt);
                if (std::abs(dist) < std::abs(dist_min)) {
                    road_pt = intersect_pt;
                    dist_min = dist;
                }
            }
        }

        if ((dist_min < lat_dist_range.first) &&
            (dist_min > lat_dist_range.second)) {
            road_pts->emplace_back(road_pt);
            has_in_range = true;
        }
    }
    return has_in_range;
}

const uint64_t RoadBoundary::id() const { return id_; };
const std::vector<Point2d> &RoadBoundary::points() const { return points_; }
const std::vector<Point2d> &RoadBoundary::curve_points() const {
    return line_curve_.points();
}
const math::LineCurve2d &RoadBoundary::line_curve() const {
    return line_curve_;
}
const RoadBoundaryType &RoadBoundary::type() const { return type_; }
const double &RoadBoundary::curve_length() const { return curve_length_; }
const double RoadBoundary::length() const { return length_; }
bool RoadBoundary::IsValid() const { return points_.size() > 1U; }

void RoadBoundary::set_section_id(const uint64_t section_id) {
    section_id_ = section_id;
}
const uint64_t RoadBoundary::section_id() const { return section_id_; }

bool RoadBoundary::has_height() const { return true; }
double RoadBoundary::height() const { return 0.0; }

}  // namespace planning
}  // namespace ads_x
