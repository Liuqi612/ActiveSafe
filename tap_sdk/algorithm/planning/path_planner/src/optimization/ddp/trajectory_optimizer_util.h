
#pragma once

#include <string>
#include <vector>

#include "object/spacetime_object_state.h"
#include "optimization/ddp/trajectory_optimizer_defs.h"
#include "pncx_optimizer.pb.h"
#include "plan/trajectory_point.h"
#include "router/drive_passage.h"
#include <absl/status/status.h>

namespace pnc_x {
namespace planning {
namespace optimizer {

void AlignInputTrajectoryToPlanStart(
    const ApolloTrajectoryPointProto &plan_start_point,
    const DrivePassage &drive_passage,
    std::vector<TrajectoryPoint> *input_traj);

boost::optional<std::vector<TrajectoryPoint>>
AdaptTrajectoryToGivenPlanStartPoint(
    int plan_id,
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    const Mfob &problem,
    const DdpOptimizerParamsProto &params,
    double max_adaption_cost,
    const TrajectoryPoint &plan_start_point,
    std::vector<TrajectoryPoint> trajectory,
    boost::optional<std::vector<TrajectoryPoint>> *pre_traj,
    boost::optional<double> *pre_traj_cost);

absl::Status ValidateTrajectory(
    const std::vector<TrajectoryPoint> &trajectory_points,
    const TrajectoryOptimizerValidationParamsProto
        &trajectory_optimizer_validation_params,
    const TrajectoryOptimizerDebugProto &optimizer_debug,
    const double wheel_base,
    const double steer_ratio);

bool HasSameDecisionOverSpacetimeObject(
    const std::vector<TrajectoryPoint> &traj_1,
    const std::vector<TrajectoryPoint> &traj_2,
    const std::vector<SpacetimeObjectState> &space_time_object_states);

}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
