
#pragma once

#include <algorithm>
#include <cmath>
#include <string>

#include "pncx_arc2d.pb.h"
#include "path_planner/src/math/geometry/circle2d.h"
#include "path_planner/src/math/geometry/halfplane.h"
#include "path_planner/src/math/util.h"
#include "path_planner/src/math/vec.h"
#include <absl/strings/str_cat.h>

namespace pnc_x {

class Arc2dHR {
 public:
    Arc2dHR() = default;

    Arc2dHR(const Vec2d &center,
            double radius,
            const Vec2d &start_unit,
            const Vec2d &end_unit);

    const Circle2d &circle() const;

    const HalfPlane &start_bound() const;

    const HalfPlane &end_bound() const;

    bool is_inferior_arc() const;

    bool IsPointInBound(const Vec2d &point, double tolerance = 0.0) const;

    bool IsPointIn(const Vec2d &point, double epsilon) const;

    std::string DebugStringFullPrecision() const;

    static boost::optional<Arc2dHR> FromProto(const Arc2dHRProto &proto);

    void ToProto(Arc2dHRProto *proto) const;

 private:
    Circle2d circle_;
    HalfPlane start_bound_;
    HalfPlane end_bound_;
    bool is_inferior_arc_ = false;
};

class Arc2dAR {
 public:
    static constexpr double kMinRadius = 1e-10;
    static constexpr double kMaxRadius = 1e7;
    static constexpr double kMaxRadiusUsingFastMath = 1e2;

    static double NormalizeAngleZeroToTwoPi(double angle);

    Arc2dAR() = default;

    Arc2dAR(const Vec2d &center,
            double radius,
            double start_angle,
            double angle_span,
            bool use_fast_math = false);

    static Arc2dAR FromArc2dHR(const Arc2dHR &arc_hr,
                               bool use_fast_math = false);

    double arc_length() const;

    double angle_span() const;

    const Circle2d &circle() const;

    Vec2d UnitAtS(double s) const;

    double AngleAtS(double s) const;

    Vec2d PointAtUnit(const Vec2d &unit) const;

    Vec2d PointAtS(double s) const;

    std::string DebugString() const;

    std::string DebugStringFullPrecision() const;

    static boost::optional<Arc2dAR> FromProto(const Arc2dARProto &proto);

    void ToProto(Arc2dARProto *proto) const;

 private:
    Circle2d circle_;
    double start_angle_ = 0.0;
    double angle_span_ = 0.0;
    double arc_length_ = 0.0;
    double radius_inv_ = 0.0;
    bool use_fast_math_ = false;
};

}  // namespace pnc_x
