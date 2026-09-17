
#pragma once

#include <cmath>

#include "math/util.h"
#include "math/vec.h"
#include "pncx_trajectory_point.pb.h"

namespace pnc_x {
namespace planning {

void LerpPathPoint(const PathPoint &p0,
                   const PathPoint &p1,
                   double alpha,
                   PathPoint *p);

PathPoint LerpPathPoint(const PathPoint &p0, const PathPoint &p1, double alpha);

Vec2d ToVec2d(const PathPoint &point);

double DistanceTo(const PathPoint &from, const PathPoint &to);

Vec2d Heading(const PathPoint &from, const PathPoint &to);

PathPoint GetPathPointAlongCircle(const PathPoint &point, double s);

}  // namespace planning
}  // namespace pnc_x
