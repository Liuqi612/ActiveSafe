
#pragma once

#include "path_planner/src/math/frenet_common.h"
#include "path_planner/src/math/vec.h"
#include <absl/types/span.h>

namespace pnc_x {
namespace frenet_frame_util {

Vec2d SLToXY(const FrenetCoordinate &sl,
             absl::Span<const Vec2d> anchor_points,
             absl::Span<const double> anchor_s);
FrenetCoordinate XYToSLBruteForce(const Vec2d &xy,
                                  absl::Span<const Vec2d> anchor_points,
                                  absl::Span<const double> anchor_s);

}  // namespace frenet_frame_util
}  // namespace pnc_x
