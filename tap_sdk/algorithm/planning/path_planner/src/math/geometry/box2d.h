

#pragma once

#include <float.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <absl/strings/str_cat.h>
#include <absl/strings/str_format.h>

#include "pncx_box2d.pb.h"
#include "path_planner/src/math/geometry/aabox2d.h"
#include "path_planner/src/math/geometry/segment2d.h"
#include "path_planner/src/math/util.h"
#include "path_planner/src/math/vec.h"
#include "path_planner/src/common/log.h"

namespace pnc_x {

class Box2d {
 public:
    enum Corner {
        FRONT_LEFT = 0,
        REAR_LEFT = 1,
        REAR_RIGHT = 2,
        FRONT_RIGHT = 3,
    };
    Box2d() = default;

    Box2d(const Vec2d &center, double heading, double length, double width);

    Box2d(const Vec2d &center, double heading, double cos_heading, double sin_heading, double length, double width);

    Box2d(double half_length,
          double half_width,
          const Vec2d &center,
          double heading);

    Box2d(double half_length,
          double half_width,
          const Vec2d &center,
          double heading,
          double cos_heading,
          double sin_heading);

    Box2d(double half_length,
          double half_width,
          const Vec2d &center,
          double heading,
          const Vec2d &tangent);

    explicit Box2d(const Box2dProto &proto);

    Box2d(const Vec2d &center,
          const Vec2d &tangent,
          double length,
          double width);

    Box2d(double half_length,
          double half_width,
          const Vec2d &center,
          const Vec2d &tangent);

    Box2d(const Segment2d &axis, double width);

    explicit Box2d(const AABox2d &aabox);

    static Box2d CreateAABox(const Vec2d &one_corner,
                             const Vec2d &opposite_corner);

    const Vec2d &center() const;

    double center_x() const;

    double center_y() const;

    double length() const;

    double width() const;

    double half_length() const;

    double half_width() const;

    double radius() const;

    double heading() const;

    double cos_heading() const;

    double sin_heading() const;

    double area() const;

    double diagonal() const;

    Vec2d tangent() const;

    Vec2d GetCorner(Corner corner) const;

    Vec2d FrontCenterPoint() const;

    Vec2d RearCenterPoint() const;
    void InitCorners();

    std::vector<Vec2d> GetCornersWithBufferCounterClockwise(
        double lat_buffer, double lon_buffer) const;

    std::array<Segment2d, 4> GetEdgesWithBufferCounterClockwise(
        double lat_buffer, double lon_buffer) const;

    std::array<Segment2d, 4> GetEdgesCounterClockwise() const;

    std::vector<Vec2d> GetCornersCounterClockwise() const;
    void GetAllCorners(std::vector<Vec2d> *const corners) const;

    const std::vector<Vec2d> &GetAllCorners() const;

    bool IsPointInWithBuffer(const Vec2d &point,
                             double lat_buffer,
                             double lon_buffer) const;

    bool IsPointIn(const Vec2d &point) const;

    bool IsPointOnBoundary(const Vec2d &point) const;

    bool IsInAABox(const AABox2d &aabox) const;

    double DistanceTo(const Vec2d &point) const;

    double DistanceTo(const Segment2d &line_segment) const;

    double DistanceTo(const Box2d &box) const;

    bool HasOverlapWithBuffer(const Segment2d &line_segment,
                              double lat_buffer,
                              double lon_buffer) const;

    bool HasOverlap(const Segment2d &line_segment) const;

    bool HasOverlapWithBuffer(const Box2d &box,
                              double lat_buffer,
                              double lon_buffer) const;

    bool HasOverlap(const Box2d &box) const;

    bool HasOverlap(const AABox2d &aabox) const;

    [[nodiscard]] AABox2d GetAABox() const;

    void RotateFromCenter(double rotate_angle);

    void Shift(const Vec2d &shift_vec);

    void MirrorByX();

    [[nodiscard]] Box2d Transform(const Vec2d &translation) const;

    [[nodiscard]] Box2d Transform(double rotation) const;

    [[nodiscard]] Box2d Transform(const Vec2d &translation,
                                  double rotation) const;

    [[nodiscard]] Box2d AffineTransform(double rotation) const;

    [[nodiscard]] Box2d AffineTransform(const Vec2d &translation,
                                        double rotation) const;

    void LongitudinalExtend(double extension_length);
    [[nodiscard]] Box2d ExtendedAtFront(double extension_length) const;
    [[nodiscard]] Box2d ExtendedAtRear(double extension_length) const;

    void LateralExtend(double extension_length);

    void LongitudinalExtendByRatio(double extension_ratio);

    void LateralExtendByRatio(double extension_ratio);

    void FromProto(const Box2dProto &proto);

    void ToProto(Box2dProto *proto) const;

    std::string DebugString() const;
    std::string DebugStringFullPrecision() const;
    AABox2d aabox() const;
    double DistanceSquareTo(const Vec2d &point) const;

 private:
    static constexpr double kEpsilon = 1e-10;

    Vec2d center_;
    double half_length_ = 0.0;
    double half_width_ = 0.0;
    double heading_ = 0.0;
    double cos_heading_ = 1.0;
    double sin_heading_ = 0.0;
    std::vector<Vec2d> corners_;

    double max_x_ = std::numeric_limits<double>::lowest();
    double min_x_ = std::numeric_limits<double>::max();
    double max_y_ = std::numeric_limits<double>::lowest();
    double min_y_ = std::numeric_limits<double>::max();
};

}  // namespace pnc_x
