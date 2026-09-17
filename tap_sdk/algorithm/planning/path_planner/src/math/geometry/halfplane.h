
#pragma once

#include <absl/strings/str_cat.h>
#include <string>

#include "pncx_affine_transformation.pb.h"
#include "pncx_halfplane.pb.h"
#include "path_planner/src/math/geometry/util.h"
#include "path_planner/src/math/vec.h"

namespace pnc_x {

class HalfPlane {
 public:
    HalfPlane() = default;

    explicit HalfPlane(const HalfPlaneProto &proto);

    HalfPlane(const Vec2d &start, const Vec2d &end, const Vec2d &dir);
    HalfPlane(const Vec2d &start, const Vec2d &end);

    HalfPlane Inversed() const;

    const Vec2d &start() const;
    const Vec2d &end() const;
    const Vec2d &center() const;
    const Vec2d &tangent() const;
    double length() const;

    double lon_proj(const Vec2d &p) const;

    double lat_proj(const Vec2d &p) const;

    Vec2d Transform(const Vec2d &p) const;

    Vec2d InvTransform(const Vec2d &p) const;

    bool IsPointInside(const Vec2d &p) const;

    void FromProto(const HalfPlaneProto &proto);

    void ToProto(HalfPlaneProto *proto) const;

    std::string DebugString() const;

    static void ToProto(const Vec2d &start,
                        const Vec2d &end,
                        HalfPlaneProto *proto);

 private:
    Vec2d start_;
    Vec2d end_;
    Vec2d center_;

    Vec2d tangent_;
};

}  // namespace pnc_x
