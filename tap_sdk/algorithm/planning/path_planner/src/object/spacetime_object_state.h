
#pragma once

#include <vector>

#include "math/geometry/box2d.h"
#include "math/geometry/polygon2d.h"
#include "math/vec.h"
#include "prediction/predicted_trajectory.h"

namespace pnc_x {
namespace planning {

struct SpacetimeObjectState {
    const prediction::PredictedTrajectoryPoint *traj_point;

    Box2d box;
    Polygon2d contour;
};

std::vector<SpacetimeObjectState> SampleTrajectoryStates(
    const prediction::PredictedTrajectory &pred_traj,
    const Vec2d &init_pos,
    const Polygon2d &init_contour,
    const Box2d &init_box);

void SampleTrajectoryStates(
    const prediction::PredictedTrajectory &pred_traj,
    const Vec2d &init_pos,
    const Polygon2d &init_contour,
    const Box2d &init_box,
    std::vector<SpacetimeObjectState> *states);
}  // namespace planning
}  // namespace pnc_x
