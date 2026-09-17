
#include "path_planner/src/math/geometry/halfplane.h"

namespace pnc_x {

HalfPlane::HalfPlane(const HalfPlaneProto &proto) { FromProto(proto); }

HalfPlane::HalfPlane(const Vec2d &start, const Vec2d &end, const Vec2d &dir)
    : start_(start), end_(end), center_((start + end) * 0.5), tangent_(dir) {}

HalfPlane::HalfPlane(const Vec2d &start, const Vec2d &end)
    : start_(start), end_(end), center_((start + end) * 0.5) {
    const Vec2d d = end - start;
    tangent_ = d.Unit();
}

HalfPlane HalfPlane::Inversed() const {
    return HalfPlane(end_, start_, -tangent_);
}

const Vec2d &HalfPlane::start() const { return start_; }
const Vec2d &HalfPlane::end() const { return end_; }
const Vec2d &HalfPlane::center() const { return center_; }
const Vec2d &HalfPlane::tangent() const { return tangent_; }
double HalfPlane::length() const { return tangent_.Dot(end_ - start_); }

double HalfPlane::lon_proj(const Vec2d &p) const {
    return tangent_.Dot(p - start_);
}

double HalfPlane::lat_proj(const Vec2d &p) const {
    return tangent_.CrossProd(p - start_);
}

Vec2d HalfPlane::Transform(const Vec2d &p) const {
    const Vec2d diff = p - start_;
    return Vec2d(tangent_.Dot(diff), tangent_.CrossProd(diff));
}

Vec2d HalfPlane::InvTransform(const Vec2d &p) const {
    const Vec2d neg_y_dir(tangent_.x(), -tangent_.y());
    return Vec2d(neg_y_dir.Dot(p), neg_y_dir.CrossProd(p)) + start_;
}

bool HalfPlane::IsPointInside(const Vec2d &p) const {
    return tangent_.CrossProd(p - start_) > 0.0;
}

void HalfPlane::FromProto(const HalfPlaneProto &proto) {
    *this =
        HalfPlane(Vec2dFromProto(proto.start()), Vec2dFromProto(proto.end()));
}

void HalfPlane::ToProto(HalfPlaneProto *proto) const {
    ToProto(start_, end_, proto);
}

std::string HalfPlane::DebugString() const {
    return absl::StrCat("HalfPlane({", start_.x(), ", ", start_.y(), "}", ",{",
                        end_.x(), ", ", end_.y(), "})");
}

void HalfPlane::ToProto(const Vec2d &start,
                        const Vec2d &end,
                        HalfPlaneProto *proto) {
    XCHECK_NOTNULL(proto)->mutable_start()->set_x(start.x());
    proto->mutable_start()->set_y(start.y());
    proto->mutable_end()->set_x(end.x());
    proto->mutable_end()->set_y(end.y());
}

}  // namespace pnc_x
