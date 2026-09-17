
#pragma once

#include <optional>
#include <utility>

#include "path_planner/src/util/loop_guard.h"
#include "path_planner/src/math/geometry/arc2d.h"
#include "path_planner/src/math/geometry/circle2d.h"
#include "path_planner/src/math/geometry/halfplane.h"
#include "path_planner/src/math/geometry/polyline2d.h"
#include "path_planner/src/math/geometry/segment2d.h"
#include "path_planner/src/math/vec.h"

namespace pnc_x {

bool FindIntersectionBetweenLinesWithTangents(const Vec2d &p0,
                                              const Vec2d &t0,
                                              const Vec2d &p1,
                                              const Vec2d &t1,
                                              double *s0,
                                              double *s1,
                                              Vec2d *inter_point);

bool FindIntersectionBetweenLinesWithTangents(const Vec2d &p0,
                                              const Vec2d &t0,
                                              const Vec2d &p1,
                                              const Vec2d &t1,
                                              Vec2d *inter_point);

bool FindFirstIntersectionBetweenCurves(const Polyline2d &curve1,
                                        const Polyline2d &curve2,
                                        Vec2d *inter_point,
                                        double *arc_len1,
                                        double *arc_len2);

bool ClampSegment2dByHalfPlane(const HalfPlane &plane, Segment2d *segment);

std::pair<boost::optional<Vec2d>, boost::optional<Vec2d>>
FindIntersectionBetweenCircle2dSegment2d(const Circle2d &circle,
                                         const Segment2d &segment);

std::pair<boost::optional<Vec2d>, boost::optional<Vec2d>>
FindIntersectionBetweenArc2dHRSegment2d(const Arc2dHR &arc_hr,
                                        const Segment2d &segment);

std::pair<boost::optional<Vec2d>, boost::optional<Vec2d>>
FindIntersectionBetweenArc2dHRs(const Arc2dHR &a1, const Arc2dHR &a2);

}  // namespace pnc_x
