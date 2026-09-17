

#include "path_planner/src/math/geometry/arc2d.h"

namespace pnc_x {

// Define static constexpr members
constexpr double Arc2dAR::kMinRadius;
constexpr double Arc2dAR::kMaxRadius;
constexpr double Arc2dAR::kMaxRadiusUsingFastMath;

Arc2dHR::Arc2dHR(const Vec2d &center,
                 double radius,
                 const Vec2d &start_unit,
                 const Vec2d &end_unit)
    : circle_(center, radius),
      start_bound_(center, center + radius * start_unit, start_unit),
      end_bound_(center, center + radius * end_unit, end_unit),
      is_inferior_arc_(start_bound_.IsPointInside(end_bound_.end())) {}

const Circle2d &Arc2dHR::circle() const { return circle_; }

const HalfPlane &Arc2dHR::start_bound() const { return start_bound_; }

const HalfPlane &Arc2dHR::end_bound() const { return end_bound_; }

bool Arc2dHR::is_inferior_arc() const { return is_inferior_arc_; }

bool Arc2dHR::IsPointInBound(const Vec2d &point, double tolerance) const {
    const bool in_start_bound = start_bound_.lat_proj(point) >= -tolerance;
    const bool in_end_bound = end_bound_.lat_proj(point) <= tolerance;
    if (is_inferior_arc_) {
        return in_start_bound && in_end_bound;
    } else {
        return in_start_bound || in_end_bound;
    }
}

bool Arc2dHR::IsPointIn(const Vec2d &point, double epsilon) const {
    return IsPointInBound(point, epsilon) && circle_.IsPointOn(point, epsilon);
}

std::string Arc2dHR::DebugStringFullPrecision() const {
    return absl::StrFormat(
        "Arc2dHR(/*center=*/%s, /*radius=*/%s, "
        "/*start_unit=*/%s,/*end_unit=*/%s)",
        circle_.center().DebugStringFullPrecision(),
        absl::StrFormat("%.*e", DBL_DIG, circle_.radius()),
        start_bound_.tangent().DebugStringFullPrecision(),
        end_bound_.tangent().DebugStringFullPrecision());
}

boost::optional<Arc2dHR> Arc2dHR::FromProto(const Arc2dHRProto &proto) {
    const Vec2d circle_center = Vec2dFromProto(proto.circle_center());
    const double radius = proto.radius();

    if (radius <= 0.0) {
        return boost::none;
    }

    return Arc2dHR(circle_center, radius, Vec2dFromProto(proto.start_unit()),
                   Vec2dFromProto(proto.end_unit()));
}

void Arc2dHR::ToProto(Arc2dHRProto *proto) const {
    circle_.center().ToProto(proto->mutable_circle_center());
    proto->set_radius(circle_.radius());

    start_bound_.tangent().ToProto(proto->mutable_start_unit());
    end_bound_.tangent().ToProto(proto->mutable_end_unit());
}

double Arc2dAR::NormalizeAngleZeroToTwoPi(double angle) {
    return std::max(NormalizeAngle(angle - M_PI) + M_PI, 0.0);
}

Arc2dAR::Arc2dAR(const Vec2d &center,
                 double radius,
                 double start_angle,
                 double angle_span,
                 bool use_fast_math)
    : circle_(center, radius),
      start_angle_(NormalizeAngle(start_angle)),
      angle_span_(NormalizeAngleZeroToTwoPi(angle_span)),
      arc_length_(angle_span_ * radius),
      radius_inv_(1.0 / radius),
      use_fast_math_(use_fast_math) {
    XCHECK_GE(radius, kMinRadius);
    XCHECK_LE(radius, use_fast_math_ ? kMaxRadiusUsingFastMath : kMaxRadius);
}

Arc2dAR Arc2dAR::FromArc2dHR(const Arc2dHR &arc_hr, bool use_fast_math) {
    const double start_angle = arc_hr.start_bound().tangent().Angle();
    const double end_angle = arc_hr.end_bound().tangent().Angle();
    const double local_angle_span =
        NormalizeAngleZeroToTwoPi(end_angle - start_angle);
    return Arc2dAR(arc_hr.circle().center(), arc_hr.circle().radius(),
                   start_angle, local_angle_span, use_fast_math);
}

double Arc2dAR::arc_length() const { return arc_length_; }

double Arc2dAR::angle_span() const { return angle_span_; }

const Circle2d &Arc2dAR::circle() const { return circle_; }

Vec2d Arc2dAR::UnitAtS(double s) const {
    const double angle_offset = s * radius_inv_;
    return use_fast_math_
               ? Vec2d::FastUnitFromAngle(start_angle_ + angle_offset)
               : Vec2d::UnitFromAngle(start_angle_ + angle_offset);
}

double Arc2dAR::AngleAtS(double s) const {
    return NormalizeAngle(start_angle_ + (s * radius_inv_));
}

Vec2d Arc2dAR::PointAtUnit(const Vec2d &unit) const {
    return circle().PointAtUnit(unit);
}

Vec2d Arc2dAR::PointAtS(double s) const { return PointAtUnit(UnitAtS(s)); }

std::string Arc2dAR::DebugString() const {
    return absl::StrCat("circle:(", circle_.DebugString(),
                        "),start_angle:", start_angle_,
                        ",angle_span:", angle_span_);
}

std::string Arc2dAR::DebugStringFullPrecision() const {
    return absl::StrFormat(
        "Arc2dAR(/*center=*/%s, /*radius=*/%s, "
        "/*start_angle=*/%s,/*angle_span=*/%s,"
        "/*use_fast_math=*/%d)",
        circle_.center().DebugStringFullPrecision(),
        absl::StrFormat("%.*e", DBL_DIG, circle_.radius()),
        absl::StrFormat("%.*e", DBL_DIG, start_angle_),
        absl::StrFormat("%.*e", DBL_DIG, angle_span_), use_fast_math_);
}

boost::optional<Arc2dAR> Arc2dAR::FromProto(const Arc2dARProto &proto) {
    const Vec2d circle_center = Vec2dFromProto(proto.circle_center());
    const double radius = proto.radius();
    if (radius <= 0.0) {
        return boost::none;
    }

    return Arc2dAR(circle_center, radius, proto.start_angle(),
                   proto.angle_span(), proto.use_fast_math());
}

void Arc2dAR::ToProto(Arc2dARProto *proto) const {
    circle_.center().ToProto(proto->mutable_circle_center());
    proto->set_radius(circle_.radius());

    proto->set_start_angle(start_angle_);
    proto->set_angle_span(angle_span_);
    proto->set_use_fast_math(use_fast_math_);
}

}  // namespace pnc_x
