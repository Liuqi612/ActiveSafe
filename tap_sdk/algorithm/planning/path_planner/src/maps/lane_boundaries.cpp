
#include "maps/lane_boundaries.h"
#include "common/gflags.h"
namespace ads_x {
namespace planning {
LaneBoundaries::LaneBoundaries(
    const std::vector<LaneBoundaryConstPtr> &boundaries) {
    double length = 0.0;
    std::vector<Point2d> points;
    std::set<uint64_t> used_boundry;

    for (auto boundary_ptr : boundaries) {
        if ((boundary_ptr->type().line_type == LineType::DASHED) ||
            (boundary_ptr->type().line_type == LineType::SOLID_DASHED) ||
            (boundary_ptr->type().line_type == LineType::DASHED_DASHED) ||
            (boundary_ptr->type().line_type == LineType::FISH_DASH)) {
            can_cross_from_right_ = true;
        }
        if ((boundary_ptr->type().line_type == LineType::DASHED) ||
            (boundary_ptr->type().line_type == LineType::DASHED_SOLID) ||
            (boundary_ptr->type().line_type == LineType::DASHED_DASHED) ||
            (boundary_ptr->type().line_type == LineType::FISH_DASH)) {
            can_cross_from_left_ = true;
        }
    }
    for (auto boundary_ptr : boundaries) {
        if (!boundary_ptr->IsValid()) {
            continue;
        }

        if (!points.empty()) {
            double dist =
                points.back().DistanceTo(boundary_ptr->points().front());
            if (dist > FLAGS_pnc_x_planning_map_boundary_gap_threshold) {
                LaneBoundaryType boundary_type = boundary_ptr->type();
                length += dist;
                boundary_type.s = length;
                boundary_types_.emplace_back(std::move(boundary_type));

                LaneBoundaryInfo boundary_info;
                boundary_info.points.emplace_back(points.back());
                boundary_info.points.emplace_back(
                    boundary_ptr->points().front());
                boundaries_.emplace_back(
                    std::make_shared<LaneBoundary>(boundary_info));
            }
        }

        for (const auto &pt : boundary_ptr->points()) {
            if (points.empty()) {
                points.emplace_back(pt);
                continue;
            }
            double dist = points.back().DistanceTo(pt);
            if (dist < FLAGS_pnc_x_planning_map_point_distance_threshold) {
                continue;
            }
            length += dist;
            points.emplace_back(pt);
        }
        LaneBoundaryType boundary_type = boundary_ptr->type();
        boundary_type.s = length;
        std::unordered_set<LineType> used_boundry_set{
            LineType::VIRTUAL_LANE, LineType::VIRTUAL_JUNCTION,
            LineType::UNKNOWN, LineType::PREDICTION_LANE};
        if (!used_boundry.count(boundary_ptr->id()) &&
            (used_boundry_set.count(boundary_type.line_type) == 0)) {
            used_boundry.insert(boundary_ptr->id());
            this->real_length_ += boundary_ptr->curve_length();
        }

        boundary_types_.emplace_back(std::move(boundary_type));
        boundaries_.emplace_back(boundary_ptr);
    }
    line_curve_.InitializePoints(points);
}

const double LaneBoundaries::GetRealLength() const { return real_length_; }

const int32_t LaneBoundaries::GetBoundarySegmentIndex(const double &s) const {
    int32_t index = -1;
    for (int32_t i = 0; i < static_cast<int32_t>(boundary_types_.size()); ++i) {
        if (boundary_types_.at(i).s > s) {
            index = i;
            break;
        }
    }
    return index;
}
}  // namespace planning
}  // namespace ads_x
