
#pragma once

#include <memory>
#include <vector>

#include "object/planner_object.h"
#include "pncx_planner.pb.h"
#include "prediction/predicted_trajectory.h"

namespace pnc_x {
namespace planning {

class TrajectoryFilter {
 public:
    virtual FilterReason::Type Filter(
        const PlannerObject &object,
        const prediction::PredictedTrajectory &traj) const = 0;

    virtual ~TrajectoryFilter() {}
};

}  // namespace planning
}  // namespace pnc_x
