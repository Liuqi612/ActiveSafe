

#include <algorithm>
#include <boost/algorithm/clamp.hpp>
#include <cmath>
#include <utility>

#include "common/log.h"
#include "maps/lane.h"
#include "math/double.h"
#include "math/linear_interpolation.h"
#include "util/loop_guard.h"
#include "common/log.h"

namespace {
constexpr double kSpeedKphToMpsDivisor = 3.6;
constexpr double kSpeedLimit30Kph = 30.0;
constexpr double kSpeedLimit40Kph = 40.0;
constexpr double kSpeedLimit50Kph = 50.0;
constexpr double kSpeedLimit60Kph = 60.0;
constexpr double kSpeedLimit70Kph = 70.0;
constexpr double kSpeedLimit80Kph = 80.0;
constexpr int32_t kSpeedLimit30BitMask = 1 << 3;
constexpr int32_t kSpeedLimit40BitMask = 1 << 4;
constexpr int32_t kSpeedLimit50BitMask = 1 << 5;
constexpr int32_t kSpeedLimit60BitMask = 1 << 6;
constexpr int32_t kSpeedLimit70BitMask = 1 << 7;
constexpr int32_t kSpeedLimit80BitMask = 1 << 8;
}  // namespace

namespace ads_x {
namespace planning {
using Vec2d = math::Vec2d;
Lane::Lane(const LaneInfo &lane_info,
           LaneBoundariesConstPtr left_boundary,
           LaneBoundariesConstPtr right_boundary,
           RoadBoundariesConstPtr left_road_boundary,
           RoadBoundariesConstPtr right_road_boundary) {
    lane_info_ = lane_info;
    left_boundary_ = left_boundary;
    right_boundary_ = right_boundary;
    left_road_boundary_ = left_road_boundary;
    right_road_boundary_ = right_road_boundary;
    center_line_.InitializePoints(lane_info.points);
    GenerateSampleWidth(left_boundary_, &sampled_left_width_);
    GenerateSampleWidth(right_boundary_, &sampled_right_width_);
}

const bool Lane::IsValid() const {
    return center_line_.points().size() >= 2U && left_boundary_ != nullptr &&
           right_boundary_ != nullptr &&
           !left_boundary_->lane_boundaries().empty() &&
           !right_boundary_->lane_boundaries().empty();
}

const bool Lane::IsWidthValid() const {
    if (!IsValidV2()) {
        return false;
    }
    if (IsVirtual() || (type() == LaneType::LANE_RAMP) ||
        (split_topology() == TOPOLOGY_SPLIT_LEFT) ||
        (split_topology() == TOPOLOGY_SPLIT_RIGHT) ||
        (merge_topology() == TOPOLOGY_MERGE_LEFT) ||
        (merge_topology() == TOPOLOGY_MERGE_RIGHT)) {
        return true;
    }
    if (lane_info_.lane_widths.size() < 3) {
        return false;
    }

    const double MinWidth = 2.5;

    double width_begin = lane_info_.lane_widths.front();
    double width_mid =
        lane_info_.lane_widths[lane_info_.lane_widths.size() / 2];
    double width_end = lane_info_.lane_widths.back();

    if ((width_begin < MinWidth) && (width_end < MinWidth) &&
        (width_mid < MinWidth)) {
        return false;
    } else {
        return true;
    }
}
const bool Lane::IsValidV2() const {
    return IsValid() ||
           (center_line_.points().size() >= 2U && left_boundary_ != nullptr &&
            right_boundary_ != nullptr && IsVirtual());
}

void Lane::forward_boundary_type(
    const bool &is_left,
    const double &s,
    std::vector<LaneBoundaryType> &boundary_type) const {
    if (!center_line_.IsValid()) return;
    auto pt = center_line_.GetPointAtS(s);
    forward_boundary_type(is_left, pt, boundary_type);
}

void Lane::forward_boundary_type(
    const bool &is_left,
    const Point2d &point,
    std::vector<LaneBoundaryType> &boundary_type) const {
    const LaneBoundariesConstPtr boundary_ptr =
        is_left ? left_boundary_ : right_boundary_;
    if (!center_line_.IsValid() || !boundary_ptr) return;
    double project_s = 0.0;
    double project_l = 0.0;
    boundary_ptr->line_curve().GetProjection(point, &project_s, &project_l);
    const auto &all_boundary_type = boundary_ptr->boundary_types();
    int curr_index = boundary_ptr->GetBoundarySegmentIndex(project_s);
    if (curr_index < 0) return;
    for (std::size_t idx = static_cast<std::size_t>(curr_index); idx < all_boundary_type.size();
         idx++) {
        const auto &curr_bound_type = all_boundary_type[static_cast<std::size_t>(idx)];
        boundary_type.emplace_back(LaneBoundaryType{
            curr_bound_type.s - project_s, curr_bound_type.line_type,
            curr_bound_type.line_color});
    }
}
const bool Lane::can_pass_left_lane_boundaries() const {
    if (!left_boundary_) {
        return false;
    }

    return left_boundary_->CanCrossFromRight();
}
const bool Lane::can_pass_right_lane_boundaries() const {
    if (!right_boundary_) {
        return false;
    }

    return right_boundary_->CanCrossFromLeft();
}

bool Lane::IsOnLane(const math::Vec2d &point) const {
    if (!IsValid()) return false;
    double s = 0.0;
    double l = 0.0;
    center_line_.GetProjection(point, &s, &l);
    if ((s < 0.0) || (s > center_line_.length())) return false;
    double lw = 0.0;
    double rw = 0.0;
    GetWidthFromS(s, &lw, &rw);
    return (math::Double::Compare(lw - l, 0.0) !=
            math::Double::CompareType::LESS) &&
           (math::Double::Compare(l + rw, 0.0) !=
            math::Double::CompareType::LESS);
}
bool Lane::IsOnLaneSrange(const math::Vec2d &point) const {
    if (!IsValid()) return false;
    double s = 0.0;
    double l = 0.0;
    center_line_.GetProjection(point, &s, &l);
    if ((s < 0.0) || (s > center_line_.length())) return false;
    return true;
}
void Lane::GetWidthAtAccumS(const double &s,
                            double &left_w,
                            double &right_w) const {
    const double lane_width = 3.5;
    left_w = 0.5 * lane_width;
    right_w = 0.5 * lane_width;
    if (!center_line_.IsValid()) {
        return;
    }
    Point2d start_p;
    Point2d end_p;
    int idx = center_line_.GetIndexByS(s);
    if (idx < 0) return;
    if (idx == 0) idx = 1;
    const std::size_t uidx = static_cast<std::size_t>(idx);
    start_p = lane_info_.points[uidx - 1U];
    end_p = lane_info_.points[uidx];
    Point2d query_point = center_line_.GetPointAtS(s);
    math::LineSegment2d base_vec(query_point, query_point + end_p - start_p);
    if (left_boundary_ && left_boundary_->line_curve().IsValid()) {
        left_w = CalculateWidth(base_vec, query_point, 1);
    }
    if (right_boundary_ && right_boundary_->line_curve().IsValid()) {
        right_w = CalculateWidth(base_vec, query_point, -1);
    }
}

double Lane::GetWidthAtPoint(const double &x, const double &y) const {
    double accum_s;
    double l;
    center_line_.GetProjection(Point2d{x, y}, &accum_s, &l);
    return GetWidthAtAccumS(accum_s);
}

double Lane::GetWidthAtAccumS(const double &s) const {
    double left_width = 0.0;
    double right_width = 0.0;
    GetWidthAtAccumS(s, left_width, right_width);
    return left_width + right_width;
}

double Lane::CalculateWidth(math::LineSegment2d &base,
                            Point2d &p,
                            int lr) const {
    auto natural_extend = [](const Point2d &p0, const Point2d &p1,
                             const double &length) {
        auto rel_x = p1.x() - p0.x();
        auto rel_y = p1.y() - p0.y();
        auto rel_dis = std::hypot(rel_x, rel_y);
        return Point2d{p0.x() - rel_x / rel_dis * length,
                       p0.y() - rel_y / rel_dis * length};
    };
    double res_l = 1.75;
    math::LineSegment2d normal_vec(
        p, base.rotate_expand(std::copysign(0.5 * M_PI, lr), 10.0));
    LaneBoundariesConstPtr lane_boundary =
        (lr > 0) ? left_boundary_ : right_boundary_;
    auto boundary_pts = lane_boundary->line_curve().points();
    if (boundary_pts.size() > 1) {
        const double extend_dist = 5.0;

        auto front_extend_pt =
            natural_extend(boundary_pts.at(0), boundary_pts.at(1), extend_dist);
        boundary_pts.insert(boundary_pts.begin(), front_extend_pt);

        auto back_extend_pt = natural_extend(
            boundary_pts.at(boundary_pts.size() - 1U),
            boundary_pts.at(boundary_pts.size() - 2U), extend_dist);
        boundary_pts.emplace_back(back_extend_pt);
    }
    math::Vec2d intersect_p;
    for (std::size_t i = 0U; i < (boundary_pts.size() - 1U); ++i) {
        math::LineSegment2d temp_vec(boundary_pts[i], boundary_pts[i + 1U]);
        if (normal_vec.HasIntersect(temp_vec)) {
            normal_vec.GetIntersect(temp_vec, &intersect_p);
            res_l =
                std::hypot(intersect_p.x() - p.x(), intersect_p.y() - p.y());
        }
    }
    return res_l;
}

bool Lane::IsPrecede(const uint64_t lane_id) const {
    auto it = std::find(prev_lane_ids_.begin(), prev_lane_ids_.end(), lane_id);
    return it != prev_lane_ids_.end();
}

bool Lane::IsNext(const uint64_t lane_id) const {
    auto it = std::find(lane_info_.next_lane_ids.begin(),
                        lane_info_.next_lane_ids.end(), lane_id);
    return it != lane_info_.next_lane_ids.end();
}

bool Lane::GetSLWithLimit(const math::Vec2d &query_point,
                          SLPoint *const sl_point) const {
    if (!IsValid()) return false;
    (void)center_line_.GetProjection(query_point, &(sl_point->s), &(sl_point->l));
    if ((sl_point->s < 0.0) || (sl_point->s > center_line_.length())) {
        sl_point->s =
            boost::algorithm::clamp(sl_point->s, 0.0, center_line_.length());
        return false;
    }
    return true;
}

bool Lane::GetSLWithoutLimit(const math::Vec2d &query_point,
                             SLPoint *const sl_point) const {
    if (!IsValid()) return false;
    center_line_.GetProjection(query_point, &(sl_point->s), &(sl_point->l));
    return true;
}

bool Lane::GetSLWithoutLimitV2(const math::Vec2d &query_point,
                               SLPoint *const sl_point) const {
    if (!IsValidV2()) return false;
    center_line_.GetProjection(query_point, &(sl_point->s), &(sl_point->l));
    return true;
}

bool Lane::GetXYWithoutLimit(const SLPoint &sl_point,
                             math::Vec2d *const xy_point) const {
    if (!IsValid()) return false;
    center_line_.GetPoint(sl_point.s, sl_point.l, xy_point);
    return true;
}

bool Lane::GetHeadingFromS(const double &query_s, double *const heading) const {
    return center_line_.GetHeadingFromS(query_s, heading);
}

bool Lane::GetWidthFromS(const double &query_s,
                         double *const lw,
                         double *const rw) const {
    if ((sampled_left_width_.size() < 2U) || (sampled_right_width_.size() < 2U))
        return false;
    if (query_s < 0.0) {
        *lw = sampled_left_width_.front().dist;
        *rw = sampled_right_width_.front().dist;
        return true;
    } else if (query_s > center_line_.length()) {
        *lw = sampled_left_width_.back().dist;
        *rw = sampled_right_width_.back().dist;
        return true;
    }
    *lw = GetDistanceFromSample(query_s, &sampled_left_width_);
    *rw = GetDistanceFromSample(query_s, &sampled_right_width_);
    return true;
}

double Lane::GetDistanceFromSample(
    const double &query_s,
    const std::list<SampledWidth> *const sampled_widths) const {
    if (sampled_widths->empty()) {
        return 0.0;
    }
    double dist = sampled_widths->front().dist;
    double s = sampled_widths->front().s;
    for (const auto &sampled_width : *sampled_widths) {
        if (sampled_width.s > query_s) {
            double s_scope = std::max(sampled_width.s - s, 1e-6);
            dist =
                ((sampled_width.dist - dist) * (query_s - s) / s_scope) + dist;
            break;
        }
        dist = sampled_width.dist;
        s = sampled_width.s;
    }
    return dist;
}

void Lane::GenerateSampleWidth(LaneBoundariesConstPtr &boundary,
                               std::list<SampledWidth> *const sample_widths) {
    const auto &boundary_curve = boundary->line_curve();
    if (!(boundary_curve.IsValid() && center_line_.IsValid() &&
          sample_widths->empty())) {
        return;
    }
    const auto &lane_points = center_line_.points();
    const auto &boundary_points = boundary_curve.points();
    std::size_t lane_pt_idx = 0UL;
    std::size_t bound_pt_idx = 0UL;
    double accumulate_s = 0.0;
    math::LineSegment2d lane_seg(lane_points.at(0), lane_points.at(1));
    const std::size_t max_lane_pt_idx = lane_points.size() - 1U;
    const std::size_t max_bound_pt_idx = boundary_points.size();
    const double min_s_dist = 1.0;
    bool has_input_lane_pt = false;
    auto loop_guard1 = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while ((lane_pt_idx < max_lane_pt_idx) &&
           (bound_pt_idx < max_bound_pt_idx) && loop_guard1) {
        const auto prod =
            lane_seg.ProductOntoUnit(boundary_points.at(bound_pt_idx));
        const auto proj =
            lane_seg.ProjectOntoUnit(boundary_points.at(bound_pt_idx));

        if (!has_input_lane_pt &&
            (sample_widths->empty() ||
             (accumulate_s - sample_widths->back().s) > min_s_dist) &&
            (proj > 0.0) && (proj < lane_seg.length()) && (bound_pt_idx > 0)) {
            const auto &start_bound_pt = boundary_points.at(bound_pt_idx - 1);
            double start_prod = lane_seg.ProductOntoUnit(start_bound_pt);
            double start_proj = lane_seg.ProjectOntoUnit(start_bound_pt);
            SampledWidth sample_width;
            sample_width.s = accumulate_s;
            double s_scope = proj - start_proj;
            s_scope = (s_scope < 0.0) ? std::min(-1e-6, s_scope)
                                      : std::max(1e-6, s_scope);
            sample_width.dist = std::fabs(
                ((-start_proj * (prod - start_prod)) / s_scope) + start_prod);
            sample_widths->emplace_back(std::move(sample_width));
            has_input_lane_pt = true;
        } else if (!has_input_lane_pt &&
                   ((sample_widths->empty() ||
                     (accumulate_s - sample_widths->back().s) > min_s_dist)) &&
                   (proj > 0.0) && (proj < lane_seg.length())) {
            SampledWidth sample_width;
            sample_width.s = accumulate_s;
            sample_width.dist = std::fabs(prod);
            sample_widths->emplace_back(std::move(sample_width));
            has_input_lane_pt = true;
        }

        bool bound_in_lane = proj < lane_seg.length();
        if (bound_in_lane &&
            (sample_widths->empty() ||
             (accumulate_s + proj - sample_widths->back().s) > min_s_dist)) {
            SampledWidth sample_width;
            sample_width.s = proj + accumulate_s;
            sample_width.dist = std::fabs(prod);
            sample_widths->emplace_back(std::move(sample_width));
        }

        if (bound_in_lane) {
            ++bound_pt_idx;
        } else if ((lane_pt_idx + 1UL) < max_lane_pt_idx) {
            accumulate_s += lane_seg.length();
            ++lane_pt_idx;
            lane_seg.Reset(lane_points.at(lane_pt_idx),
                           lane_points.at(lane_pt_idx + 1));
            has_input_lane_pt = false;
        } else {
            ++lane_pt_idx;
            break;
        }
    }

    if (sample_widths->empty()) return;
    if (bound_pt_idx >= max_bound_pt_idx) {
        ++lane_pt_idx;
    }

    auto loop_guard2 = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (lane_pt_idx < lane_points.size() && lane_pt_idx > 0 && loop_guard2) {
        lane_seg.Reset(lane_points.at(lane_pt_idx - 1),
                       lane_points.at(lane_pt_idx));
        if (bound_pt_idx >= max_bound_pt_idx) {
            SampledWidth sample_width;
            sample_width.s = accumulate_s + lane_seg.length();
            sample_width.dist = sample_widths->back().dist;
            if ((sample_width.s - sample_widths->back().s) < min_s_dist &&
                sample_widths->size() > 1U) {
                sample_widths->pop_back();
            }
            ++lane_pt_idx;
            accumulate_s += lane_seg.length();
            sample_widths->emplace_back(std::move(sample_width));
            continue;
        }
        const auto prod =
            lane_seg.ProductOntoUnit(boundary_points.at(bound_pt_idx));
        const auto proj =
            lane_seg.ProjectOntoUnit(boundary_points.at(bound_pt_idx));
        double s_scope = (proj + accumulate_s) - sample_widths->back().s;
        s_scope = (s_scope < 0.0) ? std::min(-1e-6, s_scope)
                                  : std::max(1e-6, s_scope);
        SampledWidth sample_width;
        sample_width.s = accumulate_s + lane_seg.length();
        if ((sample_width.s - sample_widths->back().s) < min_s_dist &&
            sample_widths->size() > 1U) {
            sample_widths->pop_back();
        }
        sample_width.dist =
            ((std::fabs(prod) - sample_widths->back().dist) *
             (sample_width.s - sample_widths->back().s) / s_scope) +
            sample_widths->back().dist;
        sample_widths->emplace_back(std::move(sample_width));
        break;
    }

    const auto cmp_type = math::Double::Compare(sample_widths->front().s, 0.0);
    if (cmp_type == math::Double::CompareType::GREATER) {
        SampledWidth sample_width;
        sample_width.s = 0.0;
        sample_width.dist = sample_widths->front().dist;
        if (sample_widths->front().s < min_s_dist) {
            sample_widths->pop_front();
        }
        sample_widths->emplace_front(std::move(sample_width));
    } else if (cmp_type == math::Double::CompareType::LESS &&
               sample_widths->size() > 1U) {
        double prev_dist = sample_widths->front().dist;
        double prev_s = sample_widths->front().s;
        sample_widths->pop_front();
        auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while (sample_widths->front().s < 0.0 && sample_widths->size() > 1U &&
               loop_guard) {
            prev_dist = sample_widths->front().dist;
            prev_s = sample_widths->front().s;
            sample_widths->pop_front();
        }
        if (sample_widths->front().s > 0.0) {
            SampledWidth sample_width;
            sample_width.s = 0.0;
            double s_scope = std::max(sample_widths->front().s - prev_s, 1e-6);
            sample_width.dist =
                (-prev_s * (sample_widths->front().dist - prev_dist) /
                 s_scope) +
                prev_dist;
            sample_widths->emplace_front(std::move(sample_width));
        }

        if (sample_widths->back().s < 0.0) {
            SampledWidth sample_width;
            sample_width.s = 0.0;
            sample_width.dist = sample_widths->back().dist;
            sample_widths->emplace_back(std::move(sample_width));
        }
    }
}

double Lane::LaneFraction(int segment, double segment_fraction) const {
    XCHECK_GE(segment_fraction, 0.0);
    XCHECK_LE(segment_fraction, 1.0);
    const std::size_t useg = static_cast<std::size_t>(segment);
    return pnc_x::Lerp(center_line_.GetAccuLength()[useg],
                       center_line_.GetAccuLength()[useg + 1U],
                       segment_fraction) /
           center_line_.GetAccuLength().back();
}

std::pair<int, double> Lane::SegmentFraction(double lane_fraction) const {
    XCHECK_GE(center_line_.GetAccuLength().size(), 2);
    XCHECK_GE(lane_fraction, 0.0);
    XCHECK_LE(lane_fraction, 1.0);
    const double cum_length =
        center_line_.GetAccuLength().back() * lane_fraction;
    std::ptrdiff_t index =
        std::upper_bound(center_line_.GetAccuLength().begin(),
                         center_line_.GetAccuLength().end(), cum_length) -
        center_line_.GetAccuLength().begin();
    XCHECK_GT(index, 0);
    if (index == static_cast<std::ptrdiff_t>(center_line_.GetAccuLength().size())) {
        return {static_cast<int>(center_line_.GetAccuLength().size()) - 2, 1.0};
    }
    --index;
    XCHECK_LT(index + 1, center_line_.GetAccuLength().size());
    const std::size_t uidx = static_cast<std::size_t>(index);
    return {static_cast<int>(index), (cum_length - center_line_.GetAccuLength()[uidx]) /
                       (center_line_.GetAccuLength()[uidx + 1U] -
                        center_line_.GetAccuLength()[uidx])};
}

bool Lane::GetTangent(double fraction, math::Vec2d *tangent) const {
    auto pair = SegmentFraction(fraction);
    int index = pair.first;
    const std::size_t uidx = static_cast<std::size_t>(index);
    const math::Vec2d &prev_pt = points()[uidx];
    const math::Vec2d &next_pt = points()[uidx + 1U];
    *tangent = (next_pt - prev_pt).normalized();

    return true;
}

math::Vec2d Lane::GetTangent(double fraction) const {
    const int index = SegmentFraction(fraction).first;
    XCHECK_GE(index, 0);
    XCHECK_LT(index + 1, points().size());
    const std::size_t uidx = static_cast<std::size_t>(index);
    const math::Vec2d prev_to_next = points()[uidx + 1U] - points()[uidx];

    constexpr double kLengthSqrEpsilon = 1e-9;
    return (prev_to_next.Sqr() < kLengthSqrEpsilon) ? math::Vec2d(0.0, 1.0)
                                                    : prev_to_next.normalized();
}

math::Vec2d Lane::LerpPointFromFraction(double fraction) const {
    if (points().size() == 1) {
        return points()[0];
    }
    const auto index = SegmentFraction(fraction);
    const std::size_t idx = static_cast<std::size_t>(index.first);
    return pnc_x::Lerp(points()[idx], points()[idx + 1U],
                       index.second);
}

bool Lane::GetCustomSpeedLimit(double *custom_speed_limit) const {
    if ((custom_speed_limit == nullptr)) return false;
    if ((lane_info_.lane_operation_type & kSpeedLimit30BitMask) != 0) {
        *custom_speed_limit = kSpeedLimit30Kph / kSpeedKphToMpsDivisor;
        return true;
    }
    if ((lane_info_.lane_operation_type & kSpeedLimit40BitMask) != 0) {
        *custom_speed_limit = kSpeedLimit40Kph / kSpeedKphToMpsDivisor;
        return true;
    }
    if ((lane_info_.lane_operation_type & kSpeedLimit50BitMask) != 0) {
        *custom_speed_limit = kSpeedLimit50Kph / kSpeedKphToMpsDivisor;
        return true;
    }
    if ((lane_info_.lane_operation_type & kSpeedLimit60BitMask) != 0) {
        *custom_speed_limit = kSpeedLimit60Kph / kSpeedKphToMpsDivisor;
        return true;
    }
    if ((lane_info_.lane_operation_type & kSpeedLimit70BitMask) != 0) {
        *custom_speed_limit = kSpeedLimit70Kph / kSpeedKphToMpsDivisor;
        return true;
    }
    if ((lane_info_.lane_operation_type & kSpeedLimit80BitMask) != 0) {
        *custom_speed_limit = kSpeedLimit80Kph / kSpeedKphToMpsDivisor;
        return true;
    }
    return false;
}

void Lane::SetValidPredLaneIds(const std::vector<uint64_t> &lane_ids) {
    valid_pre_lane_ids_ = lane_ids;
}
void Lane::SetValidNextLaneIds(const std::vector<uint64_t> &lane_ids) {
    valid_next_lane_ids_ = lane_ids;
}
void Lane::SetNextTurnTypes(const std::unordered_set<TurnType> &turn_types) {
    next_turn_types_ = turn_types;
}
void Lane::SetSortedNextLaneIds(const std::vector<uint64_t> &lane_ids) {
    sorted_next_lane_ids_ = lane_ids;
}
void Lane::SetLaneIndInSection(std::size_t lane_ind_in_section) {
    lane_ind_in_section_ = lane_ind_in_section;
}

void Lane::SetSplitTopology(const SplitTopology &split_topology) {
    lane_info_.split_topology = split_topology;
}
void Lane::SetMergeTopology(const MergeTopology &merge_topology) {
    lane_info_.merge_topology = merge_topology;
}

const uint64_t Lane::id() const { return lane_info_.id; }
const uint64_t Lane::section_id() const { return lane_info_.section_id; }
const uint64_t Lane::junction_id() const { return lane_info_.junction_id; }
const LaneType &Lane::type() const { return lane_info_.type; }
const bool &Lane::is_navigation() const { return lane_info_.is_navigation; }
const bool &Lane::stop_line() const { return lane_info_.stop_line; }
const double &Lane::speed_limit() const { return lane_info_.speed_limit; }
const SplitTopology &Lane::split_topology() const {
    return lane_info_.split_topology;
}
const MergeTopology &Lane::merge_topology() const {
    return lane_info_.merge_topology;
}

bool Lane::IsAvoidanceLane() const { return lane_info_.force_avoidance_line; }

const double Lane::topo_length() const { return lane_info_.length; }
const double Lane::curve_length() const { return center_line_.length(); }
const NoneOddType &Lane::none_odd_type() const {
    return lane_info_.none_odd_type;
}
const uint32_t &Lane::turn_type_v3() const { return lane_info_.turn_type_v3; }
const TurnType &Lane::turn_type() const { return lane_info_.turn_type; }
const TurnType &Lane::turn_type_V2() const { return lane_info_.turn_type_v2; }

const LightStatus &Lane::light_status() const {
    return lane_info_.light_status;
}
const uint64_t Lane::left_lane_id() const { return lane_info_.left_lane_id; }
const uint64_t Lane::right_lane_id() const { return lane_info_.right_lane_id; }
const std::vector<uint64_t> &Lane::pre_lane_ids() const {
    return prev_lane_ids_;
}
const std::vector<uint64_t> &Lane::next_lane_ids() const {
    return lane_info_.next_lane_ids;
}
const std::vector<uint64_t> &Lane::valid_pre_lane_ids() const {
    return valid_pre_lane_ids_;
}
const std::vector<uint64_t> &Lane::valid_next_lane_ids() const {
    return valid_next_lane_ids_;
}
const std::unordered_set<TurnType> &Lane::next_turn_types() const {
    return next_turn_types_;
}
const LaneInfo &Lane::lane_info() const { return lane_info_; }
const LaneBoundariesConstPtr &Lane::left_boundary() const {
    return left_boundary_;
}
const LaneBoundariesConstPtr &Lane::right_boundary() const {
    return right_boundary_;
}
const RoadBoundariesConstPtr &Lane::left_road_boundary() const {
    return left_road_boundary_;
}
const RoadBoundariesConstPtr &Lane::right_road_boundary() const {
    return right_road_boundary_;
}
const std::vector<uint64_t> &Lane::sorted_next_lane_ids() const {
    return sorted_next_lane_ids_;
};
const bool Lane::IsVirtual() const { return lane_info_.is_virtual; }
const bool Lane::IsVirtualForHeavyMap() const {
    if (!center_line_.IsValid() || !left_boundary_ || !right_boundary_)
        return false;

    const auto &left_boundary_types = left_boundary_->boundary_types();
    for (std::size_t idx = 0U; idx < left_boundary_types.size();
         idx++) {
        if (left_boundary_types[idx].line_type == LineType::VIRTUAL_LANE) {
            return true;
        }
    }
    const auto &right_boundary_types = right_boundary_->boundary_types();
    for (std::size_t idx = 0U; idx < right_boundary_types.size();
         idx++) {
        if (right_boundary_types[idx].line_type == LineType::VIRTUAL_LANE) {
            return true;
        }
    }
    return false;
}
const std::vector<uint64_t> Lane::crosswalks() const {
    return lane_info_.cross_walks;
}
const std::size_t Lane::lane_ind_in_section() const {
    return lane_ind_in_section_;
}
const int32_t Lane::lane_operation_type() const {
    return lane_info_.lane_operation_type;
}
const int32_t Lane::arrow_type() const { return lane_info_.arrow_type; }

const math::LineCurve2d &Lane::center_line() const { return center_line_; }
const std::vector<Point2d> &Lane::points() const {
    return center_line_.points();
}

const std::vector<uint64_t> &Lane::overlap_cross_walks() const {
    return lane_info_.cross_walks;
}
const std::vector<uint64_t> &Lane::overlap_speed_bumps() const {
    return lane_info_.speed_bumps;
}
const std::vector<uint64_t> &Lane::overlap_parking_spaces() const {
    return lane_info_.parking_spaces;
}
const std::vector<uint64_t> &Lane::overlap_clear_areas() const {
    return lane_info_.clear_areas;
}

const std::vector<uint64_t> &Lane::overlap_stop_lines() const {
    return lane_info_.traffic_stop_lines;
}
const std::vector<uint64_t> &Lane::overlap_trafficlights() const {
    return lane_info_.traffic_lights;
}

double Lane::navi_distance() const { return navi_distance_; }
int Lane::navi_section_cnt() const { return navi_section_cnt_; }

bool Lane::endpoint_toll() const { return endpoint_toll_; };

void Lane::SetIsNavigation(const bool &is_navi,
                           const double navi_distance,
                           const int navi_section_cnt) {
    lane_info_.is_navigation = is_navi;
    navi_distance_ = is_navi ? navi_distance : 0.0;
    navi_section_cnt_ = is_navi ? navi_section_cnt : 0;
};
void Lane::SetIsNavigation(const bool &is_navi) {
    lane_info_.is_navigation = is_navi;
};
void Lane::SetSectionId(const uint64_t id) {
    if (id != 0UL) {
        lane_info_.section_id = id;
    }
};
void Lane::SetTrueLength(const double &length) { lane_info_.length = length; };
void Lane::AddPreviousLane(const uint64_t id) {
    prev_lane_ids_.emplace_back(id);
}

std::vector<std::string> Lane::startpoint_associated_traffic_lights() const {
    return {};
}
std::vector<LaneInteraction> Lane::interactions() const {
    return interactions_;
}
void Lane::AddInteractions(const LaneInteraction &interact) {
    interactions_.emplace_back(interact);
}
std::vector<LaneLinkData> Lane::GetLanelinks() const {
    return lane_info_.lane_links;
};

}  // namespace planning
}  // namespace ads_x
