
#pragma once

#include "math/geometry/aabox2d.h"
#include "math/geometry/segment2d.h"
#include "math/vec.h"

namespace pnc_x {
namespace planning {

namespace qtfm_util {

bool SegmentRatioRangeInHalfPlane(const Vec2d &p0,
                                  const Vec2d &p1,
                                  const Segment2d &hp,
                                  bool reverse,
                                  double *start,
                                  double *end);

bool SegmentIntersectsFanRegion(const Vec2d &p0,
                                const Vec2d &p1,
                                const Segment2d &right_bound,
                                const Segment2d &left_bound);

bool NoReverseRegion(const AABox2d &box,
                     const Segment2d &prev_div,
                     const Segment2d &cur_div);

}  // namespace qtfm_util

}  // namespace planning
}  // namespace pnc_x
