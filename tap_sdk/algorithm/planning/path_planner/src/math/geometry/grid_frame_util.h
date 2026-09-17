
#pragma once

#include "path_planner/src/math/geometry/circle2d.h"
#include "path_planner/src/math/geometry/grid_frame.h"
#include "path_planner/src/math/geometry/polygon2d.h"
#include "path_planner/src/math/vec.h"
#include <absl/types/span.h>

namespace pnc_x {

YMonotonicGridSet2di CalculateGridsTouchingConvexPolygon(
    const GridFrame2d &grid_frame, const Polygon2d &polygon);

YMonotonicGridSet2di CalculateGridsTouchingConvexPolygonPoints(
    const GridFrame2d &grid_frame, absl::Span<const Vec2d> points);

YMonotonicGridSet2di CalculateGridsTouchingCircle(const GridFrame2d &grid_frame,
                                                  const Circle2d &circle);

}  // namespace pnc_x
