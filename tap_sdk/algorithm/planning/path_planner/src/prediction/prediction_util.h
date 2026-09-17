
#pragma once

#include <algorithm>
#include <vector>

#include "pncx_constraint.pb.h"
#include "object/spacetime_object_trajectory.h"
#include "pncx_prediction.pb.h"
#include "prediction/predicted_trajectory.h"
#include "prediction/prediction.h"
#include "prediction/prediction_defs.h"

namespace pnc_x {
namespace prediction {

bool IsStationaryTrajectory(const PredictedTrajectoryProto &traj);

bool IsStationaryTrajectory(const prediction::PredictedTrajectory &traj);

bool IsStationaryPrediction(const ObjectPredictionProto &pred);

bool IsStationaryPrediction(const ObjectPrediction &pred);

void ExtendPredictionTraj(
    const planning::SpacetimeObjectTrajectory &traj,
    planning::ConstraintProto::LeadingObjectProto *leading_obj);

void ExtendPredictionTraj(planning::SpacetimeObjectTrajectory &traj);

bool RefineTrajByAcc(PredictedTrajectory *const trajectory,
                     const double curr_acc,
                     const double acc_ts_sec);

bool CheckTrajValidity(const planning::SpacetimeObjectTrajectory &traj,
                       std::string &invalidity_info);

void RefineTrajByTrajAcc(PredictedTrajectory *const trajectory,
                         double acc_confidence);

}  // namespace prediction
}  // namespace pnc_x
