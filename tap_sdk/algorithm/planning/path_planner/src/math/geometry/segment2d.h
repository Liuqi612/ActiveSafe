

#pragma once

#include <algorithm>
#include <atomic>
#include <cmath>
#include <limits>
#include <string>
#include <utility>

#include "path_planner/src/base/macros.h"
#include "path_planner/src/math/util.h"
#include "path_planner/src/math/vec.h"
#include "path_planner/src/common/log.h"

namespace pnc_x {

class Segment2d {
 public:
    Segment2d();

    Segment2d(const Segment2d &s);

    Segment2d &operator=(const Segment2d &s);

    Segment2d(const Vec2d &start, const Vec2d &end);

    Segment2d(double length, const Vec2d &start, const Vec2d &tangent);

    const Vec2d &start() const;

    const Vec2d &end() const;

    const Vec2d &unit_direction() const;
    Vec2d rotate_expand(const double angle, const double length) const;
    void Reset(const Vec2d &start, const Vec2d &end);

    Vec2d center() const;

    double heading() const;

    double cos_heading() const;

    double sin_heading() const;

    double length() const;

    void set_length(double length);

    void Rotate(const Vec2d &center, const Vec2d &angle_unit);

    double length_sqr() const;

    double min_x() const;

    double max_x() const;

    double min_y() const;

    double max_y() const;

    double SignedDistanceTo(const Vec2d &point) const;

    double DistanceTo(const Vec2d &point) const;

    double DistanceTo(const Vec2d &point, Vec2d *const nearest_pt) const;

    double DistanceTo(const Segment2d &segment) const;

    double DistanceTo(const Segment2d &segment,
                      Vec2d *nearest_pt,
                      Vec2d *other_nearest_pt) const;

    double DistanceSquareTo(const Vec2d &point) const;

    double DistanceSquareTo(const Vec2d &point, Vec2d *const nearest_pt) const;

    bool IsPointIn(const Vec2d &point) const;

    bool HasIntersect(const Segment2d &other_segment) const;

    bool GetIntersect(const Segment2d &other_segment, Vec2d *const point) const;

    double ProjectOntoUnit(const Vec2d &point) const;

    double ProductOntoUnit(const Vec2d &point) const;

    double GetPerpendicularFoot(const Vec2d &point,
                                Vec2d *const foot_point) const;

    double GetPerpendicularFootAndDir(const Vec2d &point, Vec2d *const foot,
                                      Vec2d *const dir) const;

    void ClampByYMax(double y_max);

    void ClampByYMin(double y_min);

    void Shift(const Vec2d &offset);

    void Scale(double gain);

    std::string DebugString() const;
    std::string DebugStringFullPrecision() const;

    void Reverse();

 private:
    static constexpr double kEpsilon = 1e-10;

    static double CrossProd(const Vec2d &start_point,
                            const Vec2d &end_point_1,
                            const Vec2d &end_point_2);

    static bool IsWithin(double val, double bound1, double bound2);

    Vec2d start_;
    Vec2d end_;
    Vec2d unit_direction_;
    double length_ = 0.0;
    mutable std::atomic<double> heading_;
};

}  // namespace pnc_x
