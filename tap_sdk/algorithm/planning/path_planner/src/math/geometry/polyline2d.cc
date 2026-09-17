

#include "path_planner/src/math/geometry/polyline2d.h"

#include <algorithm>
#include <memory>
#include <utility>

#include "path_planner/src/math/util.h"
#include "path_planner/src/util/loop_guard.h"

namespace pnc_x {

Polyline2d::Polyline2d(std::vector<Vec2d> points)
    : points_(std::move(points)), aabb_(points_.front(), points_.back()) {
    XCHECK(!points_.empty());
    XCHECK_GT(points_.size(), 1);

    point_s_.reserve(points_.size() + 1);
    point_s_.push_back(0.0);
    for (int i = 0; (i + 1) < static_cast<int>(points_.size()); ++i) {
        point_s_.push_back(points_[static_cast<size_t>(i)].DistanceTo(
                               points_[static_cast<size_t>(i) + 1U]) +
                           point_s_.back());
    }
}

Polyline2d::Polyline2d(std::vector<Vec2d> points, std::vector<double> point_s)
    : points_(std::move(points)),
      point_s_(std::move(point_s)),
      aabb_(points_.front(), points_.back()) {
    XCHECK(!points_.empty());
    XCHECK_GT(points_.size(), 1);
    XCHECK_EQ(point_s_.size(), points_.size());
    XCHECK_EQ(point_s_[0], 0.0);
}

Vec2d Polyline2d::Sample(double s) const {
    const int i = GetSegmentIndexFromS(s);
    const double alpha =
        (s - point_s_[static_cast<size_t>(i)]) /
        (point_s_[static_cast<size_t>(i) + 1U] - point_s_[static_cast<size_t>(i)]);
    (void)XCHECK_GE(alpha, 0.0);
    (void)XCHECK_LE(alpha, 1.0);

    return Lerp(points_[static_cast<size_t>(i)],
                points_[static_cast<size_t>(i) + 1U], alpha);
}

std::vector<Vec2d> Polyline2d::Sample(const std::vector<double> &s) const {
    (void)XCHECK(!s.empty());
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        (void)XCHECK_GE(s[static_cast<size_t>(i)], 0.0);
        (void)XCHECK_LE(s[static_cast<size_t>(i)], point_s_.back());
        if (i > 0) {
            (void)XCHECK_GT(s[static_cast<size_t>(i)],
                            s[static_cast<size_t>(i) - 1U]);
        }
    }

    std::vector<Vec2d> res;
    res.reserve(s.size());
    int index = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i == 0) {
            index = GetSegmentIndexFromS(s[i]);
        } else {
            auto loop_guard = DEFAULT_LOOP_GUARD();
            while ((s[static_cast<size_t>(i)] >=
                    point_s_[static_cast<size_t>(index) + 1U]) &&
                   ((index + 1) < static_cast<int>(point_s_.size())) &&
                   loop_guard) {
                index++;
            }
        }
        const double alpha =
            (s[static_cast<size_t>(i)] - point_s_[static_cast<size_t>(index)]) /
            (point_s_[static_cast<size_t>(index) + 1U] -
             point_s_[static_cast<size_t>(index)]);
        res.push_back(Lerp(points_[static_cast<size_t>(index)],
                           points_[static_cast<size_t>(index) + 1U], alpha));
    }

    return res;
}

Vec2d Polyline2d::SampleTangent(double s) const {
    const int i = GetSegmentIndexFromS(s);

    return (points_[static_cast<size_t>(i) + 1U] -
            points_[static_cast<size_t>(i)]).normalized();
}
std::vector<Vec2d> Polyline2d::SampleTangent(
    const std::vector<double> &s) const {
    (void)XCHECK(!s.empty());
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        (void)XCHECK_GE(s[static_cast<size_t>(i)], 0.0);
        (void)XCHECK_LE(s[static_cast<size_t>(i)], point_s_.back());
        if (i > 0) {
            (void)XCHECK_GT(s[static_cast<size_t>(i)],
                            s[static_cast<size_t>(i) - 1U]);
        }
    }

    std::vector<Vec2d> res;
    res.reserve(s.size());
    int index = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i == 0) {
            index = GetSegmentIndexFromS(s[i]);
        } else {
            auto loop_guard = DEFAULT_LOOP_GUARD();
            while ((s[static_cast<size_t>(i)] >=
                    point_s_[static_cast<size_t>(index) + 1U]) &&
                   ((index + 1) < static_cast<int>(point_s_.size())) &&
                   loop_guard) {
                index++;
            }
        }
        res.push_back(
            (points_[static_cast<size_t>(i) + 1U] -
             points_[static_cast<size_t>(i)]).normalized());
    }

    return res;
}

int Polyline2d::GetSegmentIndexFromS(double s) const {
    XCHECK_GE(s, 0.0);
    XCHECK_LE(s, point_s_.back());

    int index = (std::upper_bound(point_s_.begin(), point_s_.end(), s) -
                 point_s_.begin()) -
                1;
    if (index == static_cast<int>(point_s_.size()) - 1) {
        (void)XCHECK_EQ(s, point_s_.back());
        index -= 1;
    }

    return index;
}

SampledPolyline2d::SampledPolyline2d(std::vector<Vec2d> points, double interval)
    : Polyline2d(std::move(points)), interval_(interval) {
    XCHECK_GT(interval_, 0);

    BuildSamples();
}

SampledPolyline2d::SampledPolyline2d(std::vector<Vec2d> points,
                                     std::vector<double> point_s,
                                     double interval)
    : Polyline2d(std::move(points), std::move(point_s)), interval_(interval) {
    XCHECK_GT(interval_, 0);

    BuildSamples();
}

int SampledPolyline2d::GetSampleSegmentIndexFromS(double s) const {
    XCHECK_GE(s, 0.0);
    XCHECK_LE(s, sample_s_.back());

    int index = (std::upper_bound(sample_s_.begin(), sample_s_.end(), s) -
                 sample_s_.begin()) -
                1;
    if (index == static_cast<int>(sample_s_.size()) - 1) {
        (void)XCHECK_EQ(s, sample_s_.back());
        index -= 1;
    }

    return index;
}

void SampledPolyline2d::BuildSamples() {
    const int estimated_num_samples =
        static_cast<int>(point_s_.back() / interval_);
    samples_.reserve(estimated_num_samples);
    sample_s_.reserve(estimated_num_samples);
    tangents_.reserve(estimated_num_samples);

    int index = 0;
    double s = 0.0;
    auto loop_guard1 = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (true && loop_guard1) {
        auto loop_guard2 = DEFAULT_LOOP_GUARD();
        while (((index + 1) < static_cast<int>(point_s_.size())) &&
               (s > point_s_[static_cast<size_t>(index) + 1U]) &&
               loop_guard2) {
            ++index;
        }
        if (index + 1 >= point_s_.size()) break;
        const double alpha =
            (s - point_s_[static_cast<size_t>(index)]) /
            (point_s_[static_cast<size_t>(index) + 1U] -
             point_s_[static_cast<size_t>(index)]);
        samples_.push_back(Lerp(points_[static_cast<size_t>(index)],
                                points_[static_cast<size_t>(index) + 1U], alpha));
        sample_s_.push_back(s);
        tangents_.push_back(
            Vec2d(points_[static_cast<size_t>(index) + 1U] -
                  points_[static_cast<size_t>(index)]).normalized());
        constexpr double kEpsilon = 0.01;
        if (s < (point_s_.back() - kEpsilon) &&
            (s + interval_) > point_s_.back()) {
            s = point_s_.back();
        } else {
            s += interval_;
        }
    }
    samples_.back() = points_.back();
    sample_s_.back() = point_s_.back();
}

}  // namespace pnc_x
