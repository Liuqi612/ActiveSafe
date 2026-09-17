

#include <algorithm>
#include <utility>
#include <absl/strings/str_cat.h>

#include "path_planner/src/common/throw_check.h"
#include "path_planner/src/math/double.h"
#include "path_planner/src/math/geometry/segment2d.h"
#include "path_planner/src/math/util.h"
#include "path_planner/src/common/log.h"
namespace pnc_x {

Vec2d Segment2d::rotate_expand(const double angle, const double local_length) const {
    Vec2d diff_vec = end_ - start_;
    diff_vec.SelfRotate(angle);
    (void)diff_vec.Normalize();
    return start_ + (diff_vec * local_length);
}

void Segment2d::Reset(const Vec2d &start, const Vec2d &end) {
    start_ = start;
    end_ = end;
    const double dx = end_.x() - start_.x();
    const double dy = end_.y() - start_.y();
    length_ = hypot(dx, dy);
    unit_direction_ =
        (ads_x::planning::math::Double::Compare(length_, 0.0) !=
                 ads_x::planning::math::Double::CompareType::GREATER
             ? Vec2d(0, 0)
             : Vec2d(dx / length_, dy / length_));
    heading_ = unit_direction_.Angle();
}

double Segment2d::DistanceTo(const Vec2d &point,
                             Vec2d *const nearest_pt) const {
    if (length_ <= kEpsilon) {
        if (nearest_pt != nullptr) *nearest_pt = start_;
        return point.DistanceTo(start_);
    }
    const double x0 = point.x() - start_.x();
    const double y0 = point.y() - start_.y();
    const double proj = (x0 * unit_direction_.x()) + (y0 * unit_direction_.y());
    if (proj < 0.0) {
        if (nearest_pt != nullptr) *nearest_pt = start_;
        return Hypot(x0, y0);
    }
    if (proj > length_) {
        if (nearest_pt != nullptr) *nearest_pt = end_;
        return point.DistanceTo(end_);
    }
    if (nearest_pt != nullptr) *nearest_pt = start_ + (unit_direction_ * proj);
    return std::abs((x0 * unit_direction_.y()) - (y0 * unit_direction_.x()));
}

double Segment2d::DistanceTo(const Segment2d &segment) const {
    Vec2d nearest_pt;
    Vec2d other_nearest_pt;
    return DistanceTo(segment, &nearest_pt, &other_nearest_pt);
}

double Segment2d::DistanceTo(const Segment2d &segment,
                             Vec2d *nearest_pt,
                             Vec2d *other_nearest_pt) const {
    Vec2d intersection_point;
    if (GetIntersect(segment, &intersection_point)) {
        if (nearest_pt != nullptr) *nearest_pt = intersection_point;
        if (other_nearest_pt != nullptr) *other_nearest_pt = intersection_point;
        return 0.0;
    }

    Vec2d nearest_pt_start;
    Vec2d nearest_pt_end;
    const double dist_start = DistanceTo(segment.start(), &nearest_pt_start);
    const double dist_end = DistanceTo(segment.end(), &nearest_pt_end);

    Vec2d other_nearest_pt_start;
    Vec2d other_nearest_pt_end;
    const double other_dist_start =
        segment.DistanceTo(start(), &other_nearest_pt_start);
    const double other_dist_end =
        segment.DistanceTo(end(), &other_nearest_pt_end);

    const double min_dist =
        std::min(std::min(dist_start, dist_end),
                 std::min(other_dist_start, other_dist_end));
    if (min_dist == dist_start) {
        if (nearest_pt != nullptr) *nearest_pt = nearest_pt_start;
        if (other_nearest_pt != nullptr) *other_nearest_pt = segment.start();
    } else if (min_dist == dist_end) {
        if (nearest_pt != nullptr) *nearest_pt = nearest_pt_end;
        if (other_nearest_pt != nullptr) *other_nearest_pt = segment.end();
    } else if (min_dist == other_dist_start) {
        if (nearest_pt != nullptr) *nearest_pt = start();
        if (other_nearest_pt != nullptr)
            *other_nearest_pt = other_nearest_pt_start;
    } else if (min_dist == other_dist_end) {
        if (nearest_pt != nullptr) *nearest_pt = end();
        if (other_nearest_pt != nullptr)
            *other_nearest_pt = other_nearest_pt_end;
    }
    return min_dist;
}

bool Segment2d::HasIntersect(const Segment2d &other_segment) const {
    if (IsPointIn(other_segment.start()) || IsPointIn(other_segment.end()) ||
        other_segment.IsPointIn(start_) || other_segment.IsPointIn(end_)) {
        return true;
    }
    if ((length_ <= kEpsilon) || (other_segment.length() <= kEpsilon)) {
        return false;
    }
    const double cc1 = CrossProd(start_, end_, other_segment.start());
    const double cc2 = CrossProd(start_, end_, other_segment.end());
    if ((cc1 * cc2) >= -kEpsilon) {
        return false;
    }
    const double cc3 =
        CrossProd(other_segment.start(), other_segment.end(), start_);
    const double cc4 =
        CrossProd(other_segment.start(), other_segment.end(), end_);
    if ((cc3 * cc4) >= -kEpsilon) {
        return false;
    }
    return true;
}

bool Segment2d::GetIntersect(const Segment2d &other_segment,
                             Vec2d *const point) const {
    if (!XCHECK_NOTNULL(point)) {
        return false;
    }
    if (IsPointIn(other_segment.start())) {
        *point = other_segment.start();
        return true;
    }
    if (IsPointIn(other_segment.end())) {
        *point = other_segment.end();
        return true;
    }
    if (other_segment.IsPointIn(start_)) {
        *point = start_;
        return true;
    }
    if (other_segment.IsPointIn(end_)) {
        *point = end_;
        return true;
    }
    if ((length_ <= kEpsilon) || (other_segment.length() <= kEpsilon)) {
        return false;
    }
    const double cc1 = CrossProd(start_, end_, other_segment.start());
    const double cc2 = CrossProd(start_, end_, other_segment.end());
    if ((cc1 * cc2) >= -kEpsilon) {
        return false;
    }
    const double cc3 =
        CrossProd(other_segment.start(), other_segment.end(), start_);
    const double cc4 =
        CrossProd(other_segment.start(), other_segment.end(), end_);
    if ((cc3 * cc4) >= -kEpsilon) {
        return false;
    }
    const double ratio = cc4 / (cc4 - cc3);
    *point = Vec2d((start_.x() * ratio) + (end_.x() * (1.0 - ratio)),
                   (start_.y() * ratio) + (end_.y() * (1.0 - ratio)));
    return true;
}

double Segment2d::GetPerpendicularFoot(const Vec2d &point,
                                       Vec2d *const foot_point) const {
    if (!XCHECK_NOTNULL(foot_point)) {
        return 0.0;
    }
    if (length_ <= kEpsilon) {
        *foot_point = start_;
        return point.DistanceTo(start_);
    }
    const double x0 = point.x() - start_.x();
    const double y0 = point.y() - start_.y();
    const double proj = (x0 * unit_direction_.x()) + (y0 * unit_direction_.y());
    if (proj <= 0.0) {
        *foot_point = start_;
        return point.DistanceTo(start_);
    }
    if (proj >= length_) {
        *foot_point = end_;
        return point.DistanceTo(end_);
    }
    *foot_point = start_ + (unit_direction_ * proj);
    return std::abs((x0 * unit_direction_.y()) - (y0 * unit_direction_.x()));
}

double Segment2d::GetPerpendicularFootAndDir(const Vec2d &point,
                                             Vec2d *const foot,
                                             Vec2d *const dir) const {
    if (!XCHECK_NOTNULL(foot) || !XCHECK_NOTNULL(dir)) {
        return 0.0;
    }

    double dist = GetPerpendicularFoot(point, foot);

    Vec2d v = point - *foot;

    if (v.Length() > 1e-12) {
        *dir = v.normalized();
    } else {
        // 退化：point≈foot，fallback 用法向
        double prod = ProductOntoUnit(point);
        *dir =
            (prod >= 0.0) ? unit_direction().Perp() : -unit_direction().Perp();
    }

    return dist;
}

void Segment2d::Reverse() {
    std::swap(start_, end_);
    const double dx = end_.x() - start_.x();
    const double dy = end_.y() - start_.y();
    unit_direction_ =
        (length_ <= kEpsilon ? Vec2d(0, 0) : Vec2d(dx / length_, dy / length_));
}

void Segment2d::ClampByYMax(double y_max) {
    const double seg_y_min = min_y();
    const double seg_y_max = max_y();
    XCHECK_LE(seg_y_min, y_max);

    if (seg_y_max > (y_max + kEpsilon)) {
        const double ratio_from_start =
            (y_max - start_.y()) / (end_.y() - start_.y());
        const double x_at_y_max = Lerp(start_.x(), end_.x(), ratio_from_start);

        if (start_.y() < end_.y()) {
            end_ = Vec2d{x_at_y_max, y_max};
            length_ *= ratio_from_start;
        } else {
            start_ = Vec2d{x_at_y_max, y_max};
            length_ *= 1.0 - ratio_from_start;
        }
    }
}

void Segment2d::ClampByYMin(double y_min) {
    const double seg_y_min = min_y();
    const double seg_y_max = max_y();
    XCHECK_GE(seg_y_max, y_min);

    if (seg_y_min < (y_min - kEpsilon)) {
        const double ratio_from_start =
            (y_min - start_.y()) / (end_.y() - start_.y());
        const double x_at_y_min = Lerp(start_.x(), end_.x(), ratio_from_start);

        if (start_.y() > end_.y()) {
            end_ = Vec2d{x_at_y_min, y_min};
            length_ *= ratio_from_start;
        } else {
            start_ = Vec2d{x_at_y_min, y_min};
            length_ *= 1.0 - ratio_from_start;
        }
    }
}

void Segment2d::Shift(const Vec2d &offset) {
    start_ += offset;
    end_ += offset;
}

void Segment2d::Scale(double gain) {
    XCHECK_GE(gain, 0.0);
    XCHECK(std::isfinite(gain));
    end_ = Lerp(start_, end_, gain);
    length_ *= gain;
}

std::string Segment2d::DebugString() const {
    return absl::StrCat("Segment2d(/*start=*/", start_.DebugString(),
                        ", /*end=*/", end_.DebugString(), ")");
}

std::string Segment2d::DebugStringFullPrecision() const {
    return absl::StrCat("Segment2d(/*start=*/",
                        start_.DebugStringFullPrecision(), ", /*end=*/",
                        end_.DebugStringFullPrecision(), ")");
}

Segment2d::Segment2d()
    : unit_direction_(1, 0),
      heading_(std::numeric_limits<double>::quiet_NaN()) {}

const Vec2d &Segment2d::start() const { return start_; }

const Vec2d &Segment2d::end() const { return end_; }

const Vec2d &Segment2d::unit_direction() const { return unit_direction_; }

Vec2d Segment2d::center() const { return (start_ + end_) * 0.5; }

double Segment2d::heading() const {
    double local_heading = heading_.load(std::memory_order_acquire);
    if (std::isnan(local_heading)) {
        local_heading = unit_direction_.Angle();
        heading_.store(local_heading, std::memory_order_release);
    }
    return local_heading;
}

double Segment2d::cos_heading() const { return unit_direction_.x(); }

double Segment2d::sin_heading() const { return unit_direction_.y(); }

double Segment2d::length() const { return length_; }
double Segment2d::length_sqr() const { return length_ * length_; }

double Segment2d::min_x() const { return std::min(start_.x(), end_.x()); }

double Segment2d::max_x() const { return std::max(start_.x(), end_.x()); }

double Segment2d::min_y() const { return std::min(start_.y(), end_.y()); }

double Segment2d::max_y() const { return std::max(start_.y(), end_.y()); }

Segment2d::Segment2d(const Vec2d &start, const Vec2d &end)
    : start_(start),
      end_(end),
      heading_(std::numeric_limits<double>::quiet_NaN()) {
    const Vec2d d = end_ - start_;
    length_ = d.Length();
    unit_direction_ = length_ <= kEpsilon ? Vec2d(0, 0) : d / length_;
}

Segment2d::Segment2d(double local_length, const Vec2d &start, const Vec2d &tangent)
    : start_(start),
      end_(start + local_length * tangent),
      unit_direction_(tangent),
      length_(local_length),
      heading_(std::numeric_limits<double>::quiet_NaN()) {
    XCHECK_GT(local_length, 0.0);
}

Segment2d::Segment2d(const Segment2d &s)
    : start_(s.start()),
      end_(s.end()),
      unit_direction_(s.unit_direction()),
      length_(s.length()),
      heading_(s.heading_.load()) {}

Segment2d &Segment2d::operator=(const Segment2d &s) {
    start_ = s.start();
    end_ = s.end();
    unit_direction_ = s.unit_direction();
    length_ = s.length();
    heading_.store(s.heading_.load());
    return *this;
}

void Segment2d::set_length(double local_length) {
    XCHECK_GT(local_length, 0.0);
    length_ = local_length;
    end_ = start_ + unit_direction_ * length_;
}

double Segment2d::SignedDistanceTo(const Vec2d &point) const {
    if (length_ <= kEpsilon) return point.DistanceTo(start_);
    const Vec2d v = point - start_;
    const double signed_lateral = v.CrossProd(unit_direction_);
    const double proj = v.Dot(unit_direction_);
    if (proj <= 0.0) {
        return signed_lateral > 0.0 ? v.norm() : -v.norm();
    }
    if (proj >= length_) {
        return signed_lateral > 0.0 ? point.DistanceTo(end_)
                                    : -point.DistanceTo(end_);
    }
    return signed_lateral;
}

double Segment2d::DistanceTo(const Vec2d &point) const {
    if (length_ <= kEpsilon) {
        return point.DistanceTo(start_);
    }
    const double x0 = point.x() - start_.x();
    const double y0 = point.y() - start_.y();
    const double proj = (x0 * unit_direction_.x()) + (y0 * unit_direction_.y());
    if (proj <= 0.0) {
        return Hypot(x0, y0);
    }
    if (proj >= length_) {
        return point.DistanceTo(end_);
    }
    return std::abs((x0 * unit_direction_.y()) - (y0 * unit_direction_.x()));
}

bool Segment2d::IsPointIn(const Vec2d &point) const {
    if (length_ <= kEpsilon) {
        return std::abs(point.x() - start_.x()) <= kEpsilon &&
               std::abs(point.y() - start_.y()) <= kEpsilon;
    }
    const double prod = CrossProd(point, start_, end_);
    if (std::abs(prod) > kEpsilon) {
        return false;
    }
    return IsWithin(point.x(), start_.x(), end_.x()) &&
           IsWithin(point.y(), start_.y(), end_.y());
}

double Segment2d::DistanceSquareTo(const Vec2d &point) const {
    if (UNLIKELY(length_ <= kEpsilon)) {
        return point.DistanceSquareTo(start_);
    }
    const double x0 = point.x() - start_.x();
    const double y0 = point.y() - start_.y();
    const double proj = (x0 * unit_direction_.x()) + (y0 * unit_direction_.y());
    if (proj <= 0.0) {
        return Sqr(x0) + Sqr(y0);
    }
    if (proj >= length_) {
        return point.DistanceSquareTo(end_);
    }
    return Sqr((x0 * unit_direction_.y()) - (y0 * unit_direction_.x()));
}

double Segment2d::DistanceSquareTo(const Vec2d &point,
                                   Vec2d *const nearest_pt) const {
    if (!XCHECK_NOTNULL(nearest_pt)) {
        return 0.0;
    }
    if (UNLIKELY(length_ <= kEpsilon)) {
        *nearest_pt = start_;
        return point.DistanceSquareTo(start_);
    }
    const double x0 = point.x() - start_.x();
    const double y0 = point.y() - start_.y();
    const double proj = (x0 * unit_direction_.x()) + (y0 * unit_direction_.y());
    if (proj <= 0.0) {
        *nearest_pt = start_;
        return Sqr(x0) + Sqr(y0);
    }
    if (proj >= length_) {
        *nearest_pt = end_;
        return point.DistanceSquareTo(end_);
    }
    *nearest_pt = start_ + unit_direction_ * proj;
    return Sqr((x0 * unit_direction_.y()) - (y0 * unit_direction_.x()));
}

double Segment2d::ProjectOntoUnit(const Vec2d &point) const {
    return unit_direction_.dot(point - start_);
}

double Segment2d::ProductOntoUnit(const Vec2d &point) const {
    return unit_direction_.CrossProd(point - start_);
}

double Segment2d::CrossProd(const Vec2d &start_point,
                            const Vec2d &end_point_1,
                            const Vec2d &end_point_2) {
    return Vec2d(end_point_1 - start_point)
        .CrossProd(end_point_2 - start_point);
}

bool Segment2d::IsWithin(double val, double bound1, double bound2) {
    if (bound1 > bound2) {
        std::swap(bound1, bound2);
    }
    return (val >= (bound1 - kEpsilon)) && (val <= (bound2 + kEpsilon));
}

}  // namespace pnc_x
