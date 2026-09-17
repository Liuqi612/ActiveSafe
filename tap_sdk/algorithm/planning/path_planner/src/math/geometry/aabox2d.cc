

#include <ostream>
#include <utility>

#include "path_planner/src/math/geometry/aabox2d.h"

namespace pnc_x {
namespace {

double CrossProd(const Vec2d &start_point,
                 const Vec2d &end_point_1,
                 const Vec2d &end_point_2) {
    return Vec2d(end_point_1 - start_point)
        .CrossProd(end_point_2 - start_point);
}

}  // namespace

bool AABox2d::HasOverlap(const Segment2d &line_segment) const {
    if (line_segment.length() <= kEpsilon) {
        return IsPointIn(line_segment.start());
    }

    const double center_diff_sqr =
        (line_segment.center() - center_).squaredNorm();
    if (center_diff_sqr > ((Sqr(half_length_) + Sqr(half_width_) +
                            (line_segment.length_sqr() * 0.25)) *
                           2.0)) {
        return false;
    }

    const double ref_x1 = line_segment.start().x() - center_.x();
    const double ref_y1 = line_segment.start().y() - center_.y();
    double x1 = ref_x1;
    double y1 = -ref_y1;
    double box_x = half_length_;
    double box_y = half_width_;
    int gx1;
    if (x1 > box_x) { gx1 = 1; } else if (x1 < -box_x) { gx1 = -1; } else { gx1 = 0; }
    int gy1;
    if (y1 > box_y) { gy1 = 1; } else if (y1 < -box_y) { gy1 = -1; } else { gy1 = 0; }
    if ((gx1 == 0) && (gy1 == 0)) {
        return true;
    }
    const double ref_x2 = line_segment.end().x() - center_.x();
    const double ref_y2 = line_segment.end().y() - center_.y();
    double x2 = ref_x2;
    double y2 = -ref_y2;
    int gx2;
    if (x2 >= box_x) { gx2 = 1; } else if (x2 <= -box_x) { gx2 = -1; } else { gx2 = 0; }
    int gy2;
    if (y2 >= box_y) { gy2 = 1; } else if (y2 <= -box_y) { gy2 = -1; } else { gy2 = 0; }
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
                return (CrossProd({x1, y1}, {x2, y2}, {box_x, -box_y}) <= 0.0)
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
    // AD_LINFO(PP) << "unimplemented state: " << gx1 << " " << gy1 << " " << gx2
    //               << " " << gy2;
    return true;
}

}  // namespace pnc_x
