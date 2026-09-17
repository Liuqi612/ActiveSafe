#include <ostream>
#include <utility>

#include "path_planner/src/common/log.h"
#include "path_planner/src/math/geometry/box2d.h"
#include "path_planner/src/math/util.h"

#if defined(__ARM_NEON)
#include <arm_neon.h>
#elif defined(__AVX__) || defined(__SSE2__)
#include <immintrin.h>
#endif

namespace pnc_x {
namespace {

double CrossProd(const Vec2d &start_point,
                 const Vec2d &end_point_1,
                 const Vec2d &end_point_2) {
    return Vec2d(end_point_1 - start_point)
        .CrossProd(end_point_2 - start_point);
}

double PtSegDistance(double query_x,
                     double query_y,
                     double start_x,
                     double start_y,
                     double end_x,
                     double end_y,
                     double length) {
    const double x0 = query_x - start_x;
    const double y0 = query_y - start_y;
    const double dx = end_x - start_x;
    const double dy = end_y - start_y;
    const double proj = (x0 * dx) + (y0 * dy);
    if (proj <= 0.0) {
        return Hypot(x0, y0);
    }
    if (proj >= (length * length)) {
        return Hypot(x0 - dx, y0 - dy);
    }
    return std::abs((x0 * dy) - (y0 * dx)) / length;
}

}  // namespace

double Box2d::DistanceTo(const Segment2d &line_segment) const {
    if (line_segment.length() <= kEpsilon) {
        return DistanceTo(line_segment.start());
    }
    const double ref_x1 = line_segment.start().x() - center_.x();
    const double ref_y1 = line_segment.start().y() - center_.y();
    double x1 = (ref_x1 * cos_heading_) + (ref_y1 * sin_heading_);
    double y1 = (ref_x1 * sin_heading_) - (ref_y1 * cos_heading_);
    double box_x = half_length_;
    double box_y = half_width_;
    int gx1 = x1 >= box_x ? 1 : (x1 <= -box_x ? -1 : 0);
    int gy1 = y1 >= box_y ? 1 : (y1 <= -box_y ? -1 : 0);
    if ((gx1 == 0) && (gy1 == 0)) {
        return 0.0;
    }
    const double ref_x2 = line_segment.end().x() - center_.x();
    const double ref_y2 = line_segment.end().y() - center_.y();
    double x2 = (ref_x2 * cos_heading_) + (ref_y2 * sin_heading_);
    double y2 = (ref_x2 * sin_heading_) - (ref_y2 * cos_heading_);
    int gx2 = x2 >= box_x ? 1 : (x2 <= -box_x ? -1 : 0);
    int gy2 = y2 >= box_y ? 1 : (y2 <= -box_y ? -1 : 0);
    if ((gx2 == 0) && (gy2 == 0)) {
        return 0.0;
    }
    if ((gx1 < 0) || ((gx1 == 0) && (gx2 < 0))) {
        x1 = -x1;
        gx1 = -gx1;
        x2 = -x2;
        gx2 = -gx2;
    }
    if ((gy1 < 0) || ((gy1 == 0) && (gy2 < 0))) {
        y1 = -y1;
        gy1 = -gy1;
        y2 = -y2;
        gy2 = -gy2;
    }
    if ((gx1 < gy1) || ((gx1 == gy1) && (gx2 < gy2))) {
        std::swap(x1, y1);
        std::swap(gx1, gy1);
        std::swap(x2, y2);
        std::swap(gx2, gy2);
        std::swap(box_x, box_y);
    }
    if ((gx1 == 1) && (gy1 == 1)) {
        switch ((gx2 * 3) + gy2) {
            case 4:
                return PtSegDistance(box_x, box_y, x1, y1, x2, y2,
                                     line_segment.length());
            case 3:
                return (x1 > x2) ? (x2 - box_x)
                                 : PtSegDistance(box_x, box_y, x1, y1, x2, y2,
                                                 line_segment.length());
            case 2:
                return (x1 > x2) ? PtSegDistance(box_x, -box_y, x1, y1, x2, y2,
                                                 line_segment.length())
                                 : PtSegDistance(box_x, box_y, x1, y1, x2, y2,
                                                 line_segment.length());
            case -1:
                return CrossProd({x1, y1}, {x2, y2}, {box_x, -box_y}) >= 0.0
                           ? 0.0
                           : PtSegDistance(box_x, -box_y, x1, y1, x2, y2,
                                           line_segment.length());
            case -4:
                return CrossProd({x1, y1}, {x2, y2}, {box_x, -box_y}) <= 0.0
                           ? PtSegDistance(box_x, -box_y, x1, y1, x2, y2,
                                           line_segment.length())
                           : (CrossProd({x1, y1}, {x2, y2}, {-box_x, box_y}) <=
                                      0.0
                                  ? 0.0
                                  : PtSegDistance(-box_x, box_y, x1, y1, x2, y2,
                                                  line_segment.length()));
        }
    } else {
        switch ((gx2 * 3) + gy2) {
            case 4:
                return (x1 < x2) ? (x1 - box_x)
                                 : PtSegDistance(box_x, box_y, x1, y1, x2, y2,
                                                 line_segment.length());
            case 3:
                return std::min(x1, x2) - box_x;
            case 1:
            case -2:
                return CrossProd({x1, y1}, {x2, y2}, {box_x, box_y}) <= 0.0
                           ? 0.0
                           : PtSegDistance(box_x, box_y, x1, y1, x2, y2,
                                           line_segment.length());
            case -3:
                return 0.0;
        }
    }
    // AD_LINFO(PP) << "unimplemented state: " << gx1 << " " << gy1 << " " <<
    // gx2
    //              << " " << gy2;
    return 0.0;
}

bool Box2d::HasOverlapWithBuffer(const Segment2d &line_segment,
                                 double lat_buffer,
                                 double lon_buffer) const {
    if (line_segment.length() <= kEpsilon) {
        return IsPointInWithBuffer(line_segment.start(), lat_buffer,
                                   lon_buffer);
    }

    double box_x = half_length_ + lon_buffer;
    double box_y = half_width_ + lat_buffer;
    const double center_diff_sqr =
        (line_segment.center() - center_).squaredNorm();
    if (center_diff_sqr >
        (Sqr(box_x) + Sqr(box_y) + (line_segment.length_sqr() * 0.25)) * 2.0) {
        return false;
    }

    const double ref_x1 = line_segment.start().x() - center_.x();
    const double ref_y1 = line_segment.start().y() - center_.y();
    double x1 = (ref_x1 * cos_heading_) + (ref_y1 * sin_heading_);
    double y1 = (ref_x1 * sin_heading_) - (ref_y1 * cos_heading_);
    int gx1 = x1 > box_x ? 1 : (x1 < -box_x ? -1 : 0);
    int gy1 = y1 > box_y ? 1 : (y1 < -box_y ? -1 : 0);
    if ((gx1 == 0) && (gy1 == 0)) {
        return true;
    }
    const double ref_x2 = line_segment.end().x() - center_.x();
    const double ref_y2 = line_segment.end().y() - center_.y();
    double x2 = (ref_x2 * cos_heading_) + (ref_y2 * sin_heading_);
    double y2 = (ref_x2 * sin_heading_) - (ref_y2 * cos_heading_);
    int gx2 = x2 >= box_x ? 1 : (x2 <= -box_x ? -1 : 0);
    int gy2 = y2 >= box_y ? 1 : (y2 <= -box_y ? -1 : 0);
    if ((gx2 == 0) && (gy2 == 0)) {
        return true;
    }
    if ((gx1 < 0) || ((gx1 == 0) && (gx2 < 0))) {
        x1 = -x1;
        gx1 = -gx1;
        x2 = -x2;
        gx2 = -gx2;
    }
    if ((gy1 < 0) || ((gy1 == 0) && (gy2 < 0))) {
        y1 = -y1;
        gy1 = -gy1;
        y2 = -y2;
        gy2 = -gy2;
    }
    if ((gx1 < gy1) || ((gx1 == gy1) && (gx2 < gy2))) {
        std::swap(x1, y1);
        std::swap(gx1, gy1);
        std::swap(x2, y2);
        std::swap(gx2, gy2);
        std::swap(box_x, box_y);
    }
    if ((gx1 == 1) && (gy1 == 1)) {
        switch ((gx2 * 3) + gy2) {
            case 4:
            case 3:
            case 2:
                return false;
            case -1:
                return CrossProd({x1, y1}, {x2, y2}, {box_x, -box_y}) >= 0.0;
            case -4:
                return CrossProd({x1, y1}, {x2, y2}, {box_x, -box_y}) <= 0.0
                           ? false
                           : (CrossProd({x1, y1}, {x2, y2}, {-box_x, box_y}) <=
                              0.0);
        }
    } else {
        switch ((gx2 * 3) + gy2) {
            case 4:
            case 3:
                return false;
            case 1:
            case -2:
                return CrossProd({x1, y1}, {x2, y2}, {box_x, box_y}) <= 0.0;
            case -3:
                return true;
        }
    }
    // AD_LINFO(PP) << "unimplemented state: " << gx1 << " " << gy1 << " " <<
    // gx2
    //              << " " << gy2;
    return true;
}

bool Box2d::HasOverlapWithBuffer(const Box2d &box,
                                 double lat_buffer,
                                 double lon_buffer) const {
    const double shift_x = box.center_x() - center_.x();
    const double shift_y = box.center_y() - center_.y();

    double box_x = half_length_ + lon_buffer;
    double box_y = half_width_ + lat_buffer;
    if (Sqr(shift_x) + Sqr(shift_y) >
        (Sqr(box_x) + Sqr(box_y) + Sqr(box.half_length()) +
         Sqr(box.half_width())) *
            2.0) {
        return false;
    }

    const double dx1 = cos_heading_ * box_x;
    const double dy1 = sin_heading_ * box_x;
    const double dx2 = sin_heading_ * box_y;
    const double dy2 = -cos_heading_ * box_y;
    const double dx3 = box.cos_heading() * box.half_length();
    const double dy3 = box.sin_heading() * box.half_length();
    const double dx4 = box.sin_heading() * box.half_width();
    const double dy4 = -box.cos_heading() * box.half_width();

    return (std::abs((shift_x * cos_heading_) + (shift_y * sin_heading_)) <=
               (std::abs((dx3 * cos_heading_) + (dy3 * sin_heading_))
                   +                    std::abs((dx4 * cos_heading_) + (dy4 * sin_heading_)) + box_x)) &&
           (std::abs((shift_x * sin_heading_) - (shift_y * cos_heading_)) <=
               (std::abs((dx3 * sin_heading_) - (dy3 * cos_heading_)) +
                   std::abs((dx4 * sin_heading_) - (dy4 * cos_heading_)) + box_y)) &&
           (std::abs((shift_x * box.cos_heading()) +
                    (shift_y * box.sin_heading())) <=
               (std::abs((dx1 * box.cos_heading()) + (dy1 * box.sin_heading())) +
                   std::abs((dx2 * box.cos_heading()) + (dy2 * box.sin_heading())) +
                   box.half_length())) &&
           (std::abs((shift_x * box.sin_heading()) -
                    (shift_y * box.cos_heading())) <=
               (std::abs((dx1 * box.sin_heading()) - (dy1 * box.cos_heading())) +
                   std::abs((dx2 * box.sin_heading()) - (dy2 * box.cos_heading())) +
                   box.half_width()));
}

void Box2d::GetAllCorners(std::vector<Vec2d> *const corners) const {
    if (corners == nullptr) {
        return;
    }
    *corners = corners_;
}

const std::vector<Vec2d> &Box2d::GetAllCorners() const { return corners_; }

void Box2d::InitCorners() {
    const double dx1 = cos_heading_ * half_length_;
    const double dy1 = sin_heading_ * half_length_;
    const double dx2 = sin_heading_ * half_width_;
    const double dy2 = -cos_heading_ * half_width_;
    corners_.resize(4);
    corners_[0] = Vec2d(center_.x() + dx1 + dx2, center_.y() + dy1 + dy2);
    corners_[1] = Vec2d(center_.x() + dx1 - dx2, center_.y() + dy1 - dy2);
    corners_[2] = Vec2d(center_.x() - dx1 - dx2, center_.y() - dy1 - dy2);
    corners_[3] = Vec2d(center_.x() - dx1 + dx2, center_.y() - dy1 + dy2);

    // SIMD 优化的 min/max 计算
#if defined(__ARM_NEON)
    // ARM NEON 实现
    float x_vals[4] = {static_cast<float>(corners_[0].x()), 
                       static_cast<float>(corners_[1].x()),
                       static_cast<float>(corners_[2].x()), 
                       static_cast<float>(corners_[3].x())};
    float y_vals[4] = {static_cast<float>(corners_[0].y()), 
                       static_cast<float>(corners_[1].y()),
                       static_cast<float>(corners_[2].y()), 
                       static_cast<float>(corners_[3].y())};
    
    float32x4_t x_vec = vld1q_f32(x_vals);
    float32x4_t y_vec = vld1q_f32(y_vals);
    
    // 水平 min/max
    float32x2_t x_low = vget_low_f32(x_vec);
    float32x2_t x_high = vget_high_f32(x_vec);
    float32x2_t x_min_pair = vpmin_f32(x_low, x_high);
    float32x2_t x_max_pair = vpmax_f32(x_low, x_high);
    min_x_ = std::min(vget_lane_f32(x_min_pair, 0), vget_lane_f32(x_min_pair, 1));
    max_x_ = std::max(vget_lane_f32(x_max_pair, 0), vget_lane_f32(x_max_pair, 1));
    
    float32x2_t y_low = vget_low_f32(y_vec);
    float32x2_t y_high = vget_high_f32(y_vec);
    float32x2_t y_min_pair = vpmin_f32(y_low, y_high);
    float32x2_t y_max_pair = vpmax_f32(y_low, y_high);
    min_y_ = std::min(vget_lane_f32(y_min_pair, 0), vget_lane_f32(y_min_pair, 1));
    max_y_ = std::max(vget_lane_f32(y_max_pair, 0), vget_lane_f32(y_max_pair, 1));
    
#elif defined(__SSE2__)
    // x86 SSE2/AVX 实现
    float x_vals[4] = {static_cast<float>(corners_[0].x()), 
                       static_cast<float>(corners_[1].x()),
                       static_cast<float>(corners_[2].x()), 
                       static_cast<float>(corners_[3].x())};
    float y_vals[4] = {static_cast<float>(corners_[0].y()), 
                       static_cast<float>(corners_[1].y()),
                       static_cast<float>(corners_[2].y()), 
                       static_cast<float>(corners_[3].y())};
    
    __m128 x_vec = _mm_loadu_ps(x_vals);
    __m128 y_vec = _mm_loadu_ps(y_vals);
    
    // 水平 min/max
    __m128 x_shuf = static_cast<__m128>(
        _mm_shuffle_ps(x_vec, x_vec, static_cast<int>(_MM_SHUFFLE(1, 0, 3, 2))));
    __m128 x_minmax1 = _mm_min_ps(x_vec, x_shuf);
    __m128 x_maxmax1 = _mm_max_ps(x_vec, x_shuf);
    __m128 x_shuf2 = static_cast<__m128>(_mm_shuffle_ps(
        x_minmax1, x_minmax1, static_cast<int>(_MM_SHUFFLE(2, 3, 0, 1))));
    __m128 x_minmax2 = _mm_min_ps(x_minmax1, x_shuf2);
    __m128 x_maxmax2 = _mm_max_ps(x_maxmax1, x_shuf2);
    min_x_ = _mm_cvtss_f32(x_minmax2);
    max_x_ = _mm_cvtss_f32(x_maxmax2);
    
    __m128 y_shuf = static_cast<__m128>(
        _mm_shuffle_ps(y_vec, y_vec, static_cast<int>(_MM_SHUFFLE(1, 0, 3, 2))));
    __m128 y_minmax1 = _mm_min_ps(y_vec, y_shuf);
    __m128 y_maxmax1 = _mm_max_ps(y_vec, y_shuf);
    __m128 y_shuf2 = static_cast<__m128>(_mm_shuffle_ps(
        y_minmax1, y_minmax1, static_cast<int>(_MM_SHUFFLE(2, 3, 0, 1))));
    __m128 y_minmax2 = _mm_min_ps(y_minmax1, y_shuf2);
    __m128 y_maxmax2 = _mm_max_ps(y_maxmax1, y_shuf2);
    min_y_ = _mm_cvtss_f32(y_minmax2);
    max_y_ = _mm_cvtss_f32(y_maxmax2);
    
#else
    // 标量优化版本：两两比较
    const float x0 = static_cast<float>(corners_[0].x());
    const float x1 = static_cast<float>(corners_[1].x());
    const float x2 = static_cast<float>(corners_[2].x());
    const float x3 = static_cast<float>(corners_[3].x());
    
    const float y0 = static_cast<float>(corners_[0].y());
    const float y1 = static_cast<float>(corners_[1].y());
    const float y2 = static_cast<float>(corners_[2].y());
    const float y3 = static_cast<float>(corners_[3].y());
    
    const float min_x01 = std::min(x0, x1);
    const float max_x01 = std::max(x0, x1);
    const float min_x23 = std::min(x2, x3);
    const float max_x23 = std::max(x2, x3);
    min_x_ = std::min(min_x01, min_x23);
    max_x_ = std::max(max_x01, max_x23);
    
    const float min_y01 = std::min(y0, y1);
    const float max_y01 = std::max(y0, y1);
    const float min_y23 = std::min(y2, y3);
    const float max_y23 = std::max(y2, y3);
    min_y_ = std::min(min_y01, min_y23);
    max_y_ = std::max(max_y01, max_y23);
#endif
}

AABox2d Box2d::aabox() const { return GetAABox(); }

double Box2d::DistanceSquareTo(const Vec2d &point) const {
    const double x0 = point.x() - center_.x();
    const double y0 = point.y() - center_.y();
    const double dx =
        std::abs((x0 * cos_heading_) + (y0 * sin_heading_)) - half_length_;
    const double dy =
        std::abs((x0 * sin_heading_) - (y0 * cos_heading_)) - half_width_;
    if (dx <= 0.0) {
        return Sqr(std::max(0.0, dy));
    }
    if (dy <= 0.0) {
        return Sqr(dx);
    }
    return Sqr(dx) + Sqr(dy);
}

Box2d::Box2d(const Vec2d &center, double heading, double length, double width)
    : Box2d(length * 0.5, width * 0.5, center, heading) {}

Box2d::Box2d(const Vec2d &center, double heading, double cos_heading, double sin_heading, double length, double width)
    : Box2d(length * 0.5, width * 0.5, center, heading, cos_heading, sin_heading) {}

Box2d::Box2d(double half_length,
             double half_width,
             const Vec2d &center,
             double heading)
    : center_(center),
      half_length_(half_length),
      half_width_(half_width),
      heading_(heading),
      cos_heading_(cos(heading)),
      sin_heading_(sin(heading)) {
    // XCHECK_GT(half_length_, -kEpsilon);
    // XCHECK_GT(half_width_, -kEpsilon);
    InitCorners();
}

Box2d::Box2d(double half_length,
             double half_width,
             const Vec2d &center,
             double heading,
             double cos_heading,
             double sin_heading)
    : center_(center),
      half_length_(half_length),
      half_width_(half_width),
      heading_(heading),
      cos_heading_(cos_heading),
      sin_heading_(sin_heading) {
    // XCHECK_GT(half_length_, -kEpsilon);
    // XCHECK_GT(half_width_, -kEpsilon);
    InitCorners();
}

Box2d::Box2d(double half_length,
             double half_width,
             const Vec2d &center,
             double heading,
             const Vec2d &tangent)
    : center_(center),
      half_length_(half_length),
      half_width_(half_width),
      heading_(heading),
      cos_heading_(tangent.x()),
      sin_heading_(tangent.y()) {
    // XCHECK_GT(half_length_, -kEpsilon);
    // XCHECK_GT(half_width_, -kEpsilon);
    InitCorners();
}

Box2d::Box2d(const Vec2d &center,
             const Vec2d &tangent,
             double length,
             double width)
    : Box2d(length * 0.5, width * 0.5, center, tangent) {}

Box2d::Box2d(double half_length,
             double half_width,
             const Vec2d &center,
             const Vec2d &tangent)
    : center_(center),
      half_length_(half_length),
      half_width_(half_width),
      heading_(tangent.Angle()),
      cos_heading_(tangent.x()),
      sin_heading_(tangent.y()) {
    // XCHECK_GT(half_length_, -kEpsilon);
    // XCHECK_GT(half_width_, -kEpsilon);

    // XCHECK_LT(std::abs(tangent.Sqr() - 1.0), 1e-6);
    InitCorners();
}

Box2d::Box2d(const Segment2d &axis, double width)
    : center_(axis.center()),
      half_length_(axis.length() * 0.5),
      half_width_(width * 0.5),
      heading_(axis.heading()),
      cos_heading_(axis.cos_heading()),
      sin_heading_(axis.sin_heading()) {
    // XCHECK_GT(half_length_, -kEpsilon);
    // XCHECK_GT(half_width_, -kEpsilon);
    InitCorners();
}

Box2d::Box2d(const AABox2d &aabox)
    : center_(aabox.center()),
      half_length_(aabox.half_length()),
      half_width_(aabox.half_width()),
      heading_(0.0),
      cos_heading_(1.0),
      sin_heading_(0.0) {
    // XCHECK_GT(half_length_, -kEpsilon);
    // XCHECK_GT(half_width_, -kEpsilon);
    InitCorners();
}

Box2d::Box2d(const Box2dProto &proto) {
    *this = Box2d(Vec2d(proto.x(), proto.y()), proto.heading(), std::fabs(proto.length()),
                  std::fabs(proto.width()));
}

std::vector<Vec2d> Box2d::GetCornersWithBufferCounterClockwise(
    double lat_buffer, double lon_buffer) const {
    const Vec2d unit(cos_heading_, sin_heading_);
    const Vec2d h = unit * (half_length_ + lon_buffer);
    const Vec2d w = unit.Perp() * (half_width_ + lat_buffer);
    return {
        center_ + h + w,
        center_ - h + w,
        center_ - h - w,
        center_ + h - w,
    };
}

std::array<Segment2d, 4UL> Box2d::GetEdgesWithBufferCounterClockwise(
    double lat_buffer, double lon_buffer) const {
    const Vec2d unit(cos_heading_, sin_heading_);
    const Vec2d unit_perp = unit.Perp();

    const double buffered_half_length = half_length_ + lon_buffer;
    const double buffered_half_width = half_width_ + lat_buffer;

    const double buffered_length = 2.0 * buffered_half_length;
    const double buffered_width = 2.0 * buffered_half_width;

    const Vec2d h = unit * buffered_half_length;
    const Vec2d w = unit_perp * buffered_half_width;

    return {Segment2d(buffered_length, center_ + h + w, -unit),
            Segment2d(buffered_width, center_ - h + w, -unit_perp),
            Segment2d(buffered_length, center_ - h - w, unit),
            Segment2d(buffered_width, center_ + h - w, unit_perp)};
}

std::array<Segment2d, 4UL> Box2d::GetEdgesCounterClockwise() const {
    return GetEdgesWithBufferCounterClockwise(0.0, 0.0);
}

Vec2d Box2d::GetCorner(Corner corner) const {
    const Vec2d unit(cos_heading_, sin_heading_);
    const Vec2d h = unit * half_length_;
    const Vec2d w = unit.Perp() * half_width_;
    switch (corner) {
        case FRONT_LEFT:
            return center_ + h + w;
        case REAR_LEFT:
            return center_ - h + w;
        case REAR_RIGHT:
            return center_ - h - w;
        case FRONT_RIGHT:
            return center_ + h - w;
        default:

            // AD_LINFO(PP) << "unexpected enum";
            return unit;
    }
}

Vec2d Box2d::FrontCenterPoint() const {
    const Vec2d unit(cos_heading_, sin_heading_);
    const Vec2d h = unit * half_length_;
    return center_ + h;
}

Vec2d Box2d::RearCenterPoint() const {
    const Vec2d unit(cos_heading_, sin_heading_);
    const Vec2d h = unit * half_length_;
    return center_ - h;
}

Box2d Box2d::CreateAABox(const Vec2d &one_corner,
                         const Vec2d &opposite_corner) {
    const double x1 = std::min(one_corner.x(), opposite_corner.x());
    const double x2 = std::max(one_corner.x(), opposite_corner.x());
    const double y1 = std::min(one_corner.y(), opposite_corner.y());
    const double y2 = std::max(one_corner.y(), opposite_corner.y());
    return Box2d({(x1 + x2) * 0.5, (y1 + y2) * 0.5}, 0.0, x2 - x1, y2 - y1);
}

bool Box2d::IsPointInWithBuffer(const Vec2d &point,
                                double lat_buffer,
                                double lon_buffer) const {
    const double x0 = point.x() - center_.x();
    const double y0 = point.y() - center_.y();
    const double dx = std::abs((x0 * cos_heading_) + (y0 * sin_heading_));
    const double dy = std::abs((-x0 * sin_heading_) + (y0 * cos_heading_));
    const double box_x = half_length_ + lon_buffer;
    const double box_y = half_width_ + lat_buffer;
    return (dx <= (box_x + kEpsilon)) && (dy <= (box_y + kEpsilon));
}

bool Box2d::IsPointOnBoundary(const Vec2d &point) const {
    const double x0 = point.x() - center_.x();
    const double y0 = point.y() - center_.y();
    const double dx = std::abs((x0 * cos_heading_) + (y0 * sin_heading_));
    const double dy = std::abs((x0 * sin_heading_) - (y0 * cos_heading_));
    return ((std::abs(dx - half_length_) <= kEpsilon) &&
            (dy <= (half_width_ + kEpsilon))) ||
           ((std::abs(dy - half_width_) <= kEpsilon) &&
            (dx <= (half_length_ + kEpsilon)));
}

bool Box2d::IsInAABox(const AABox2d &aabox) const {
    return aabox.Contains(GetAABox());
}

double Box2d::DistanceTo(const Vec2d &point) const {
    const double x0 = point.x() - center_.x();
    const double y0 = point.y() - center_.y();
    const double dx =
        std::abs((x0 * cos_heading_) + (y0 * sin_heading_)) - half_length_;
    const double dy =
        std::abs((x0 * sin_heading_) - (y0 * cos_heading_)) - half_width_;
    if (dx <= 0.0) {
        return std::max(0.0, dy);
    }
    if (dy <= 0.0) {
        return dx;
    }
    return Hypot(dx, dy);
}

bool Box2d::HasOverlap(const AABox2d &aabox) const {
    const double shift_x = aabox.center_x() - center_.x();
    const double shift_y = aabox.center_y() - center_.y();

    const double dx1 = cos_heading_ * half_length_;
    const double dy1 = sin_heading_ * half_length_;
    const double dx2 = sin_heading_ * half_width_;
    const double dy2 = -cos_heading_ * half_width_;

    const double dx3 = aabox.half_length();
    const double dy4 = -aabox.half_width();

    return (std::abs((shift_x * cos_heading_) + (shift_y * sin_heading_)) <=
               (std::abs(dx3 * cos_heading_) + std::abs(dy4 * sin_heading_) +
                   half_length_)) &&
           (std::abs((shift_x * sin_heading_) - (shift_y * cos_heading_)) <=
               (std::abs(dx3 * sin_heading_) + std::abs(-dy4 * cos_heading_) +
                   half_width_)) &&
           (std::abs(shift_x) <= (std::abs(dx1) + std::abs(dx2) + dx3)) &&
           (std::abs(shift_y) <= (std::abs(dy1) + std::abs(dy2) - dy4));
}

double Box2d::DistanceTo(const Box2d &box) const {
    if (HasOverlap(box)) {
        return 0.0;
    }
    double distance_sqr = std::numeric_limits<double>::infinity();
    const auto self_corners = GetCornersCounterClockwise();
    for (const auto &corner : self_corners) {
        distance_sqr = std::min(distance_sqr, box.DistanceSquareTo(corner));
    }
    const auto other_corners = box.GetCornersCounterClockwise();
    for (const auto &corner : other_corners) {
        distance_sqr = std::min(distance_sqr, DistanceSquareTo(corner));
    }
    return std::sqrt(distance_sqr);
}

AABox2d Box2d::GetAABox() const {
    const double dx1 = std::abs(cos_heading_ * half_length_);
    const double dy1 = std::abs(sin_heading_ * half_length_);
    const double dx2 = std::abs(sin_heading_ * half_width_);
    const double dy2 = std::abs(cos_heading_ * half_width_);
    return AABox2d(center_, (dx1 + dx2) * 2.0, (dy1 + dy2) * 2.0);
}

void Box2d::RotateFromCenter(const double rotate_angle) {
    heading_ = NormalizeAngle(heading_ + rotate_angle);
    cos_heading_ = std::cos(heading_);
    sin_heading_ = std::sin(heading_);
}

void Box2d::Shift(const Vec2d &shift_vec) { center_ += shift_vec; }

void Box2d::MirrorByX() {
    center_.y() = -center_.y();
    heading_ = -heading_;
    sin_heading_ = -sin_heading_;
}

Box2d Box2d::Transform(const Vec2d &translation) const {
    Box2d box(*this);
    box.Shift(translation);
    return box;
}

Box2d Box2d::Transform(double rotation) const {
    const double heading = NormalizeAngle(heading_ + rotation);
    return Box2d(half_length_, half_width_, center_, heading);
}

Box2d Box2d::Transform(const Vec2d &translation, double rotation) const {
    const Vec2d center = center_ + translation;
    const double heading = NormalizeAngle(heading_ + rotation);
    return Box2d(half_length_, half_width_, center, heading);
}

Box2d Box2d::AffineTransform(double rotation) const {
    const Vec2d center = center_.Rotate(rotation);
    const double heading = NormalizeAngle(heading_ + rotation);
    return Box2d(half_length_, half_width_, center, heading);
}

Box2d Box2d::AffineTransform(const Vec2d &translation, double rotation) const {
    const Vec2d center = center_.Rotate(rotation) + translation;
    const double heading = NormalizeAngle(heading_ + rotation);
    return Box2d(half_length_, half_width_, center, heading);
}

void Box2d::LongitudinalExtend(const double extension_length) {
    half_length_ += extension_length * 0.5;
}
Box2d Box2d::ExtendedAtFront(double extension_length) const {
    Box2d new_box = *this;
    const double half_ext_len = 0.5 * extension_length;
    new_box.Shift(half_ext_len * Vec2d(cos_heading_, sin_heading_));
    new_box.LongitudinalExtend(half_ext_len);
    return new_box;
}
Box2d Box2d::ExtendedAtRear(double extension_length) const {
    Box2d new_box = *this;
    const double half_ext_len = 0.5 * extension_length;
    new_box.Shift(-half_ext_len * Vec2d(cos_heading_, sin_heading_));
    new_box.LongitudinalExtend(half_ext_len);
    return new_box;
}

void Box2d::LateralExtend(const double extension_length) {
    half_width_ += extension_length * 0.5;
}

void Box2d::LongitudinalExtendByRatio(double extension_ratio) {
    half_length_ *= extension_ratio;
}

void Box2d::LateralExtendByRatio(double extension_ratio) {
    half_width_ *= extension_ratio;
}

void Box2d::FromProto(const Box2dProto &proto) {
    *this = Box2d(Vec2d(proto.x(), proto.y()), proto.heading(), proto.length(),
                  proto.width());
}

void Box2d::ToProto(Box2dProto *proto) const {
    proto->set_x(center().x());
    proto->set_y(center().y());
    proto->set_heading(heading());
    proto->set_length(length());
    proto->set_width(width());
}

std::string Box2d::DebugString() const {
    return absl::StrCat("box2d ( center = ", center_.DebugString(),
                        "  heading = ", heading_, "  length = ", length(),
                        "  width = ", width(), " )");
}

std::string Box2d::DebugStringFullPrecision() const {
    return absl::StrFormat(
        "Box2d(/*half_length=*/%.*e, /*half_width=*/%.*e, /*center=*/%s, "
        "/*heading=*/%.*e)",
        DECIMAL_DIG, half_length_, DECIMAL_DIG, half_width_,
        center_.DebugStringFullPrecision(), DECIMAL_DIG, heading_);
}

const Vec2d &Box2d::center() const { return center_; }

double Box2d::center_x() const { return center_.x(); }

double Box2d::center_y() const { return center_.y(); }

double Box2d::length() const { return half_length_ * 2.0; }

double Box2d::width() const { return half_width_ * 2.0; }

double Box2d::half_length() const { return half_length_; }

double Box2d::half_width() const { return half_width_; }

double Box2d::radius() const { return Hypot(half_length_, half_width_); }

double Box2d::heading() const { return heading_; }

double Box2d::cos_heading() const { return cos_heading_; }

double Box2d::sin_heading() const { return sin_heading_; }

double Box2d::area() const { return half_length_ * half_width_ * 4.0; }

double Box2d::diagonal() const {
    return Hypot(half_length_, half_width_) * 2.0;
}

Vec2d Box2d::tangent() const { return Vec2d(cos_heading_, sin_heading_); }

std::vector<Vec2d> Box2d::GetCornersCounterClockwise() const {
    return GetCornersWithBufferCounterClockwise(0.0, 0.0);
}

bool Box2d::IsPointIn(const Vec2d &point) const {
    return IsPointInWithBuffer(point, 0.0, 0.0);
}

bool Box2d::HasOverlap(const Box2d &box) const {
    return HasOverlapWithBuffer(box, 0.0, 0.0);
}

bool Box2d::HasOverlap(const Segment2d &line_segment) const {
    return HasOverlapWithBuffer(line_segment, 0.0, 0.0);
}

}  // namespace pnc_x
