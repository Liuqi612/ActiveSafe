
#pragma once

#include <map>
#include <string>
#include <vector>

#include "initializer/geometry/geometry_graph.h"
#include "initializer/initializer_output.h"
#include "initializer/ref_speed_table.h"
#include <absl/status/statusor.h>
#include <absl/strings/string_view.h>
#include <absl/types/span.h>

#include "pncx_constraint.pb.h"
#include "pncx_initializer.pb.h"
#include "router/drive_passage.h"
#include "pncx_trajectory_point.pb.h"

namespace pnc_x {
namespace planning {

absl::StatusOr<std::vector<ApolloTrajectoryPointProto>>
GenerateConstLateralAccelConstSpeedTraj(
    const DrivePassage &drive_passage,
    double ego_front_to_ra,
    double target_l,
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        &leading_trajs,
    absl::Span<const ConstraintProto::StopLineProto> stop_line,
    const ApolloTrajectoryPointProto &plan_start_point,
    int traj_steps);

void ParseMotionSearchOutputToMotionSearchDebugProto(
    const MotionSearchOutput &search_output, MotionSearchDebugProto *proto);

void ParseMotionSearchOutputToMultiTrajDebugProto(
    const MotionSearchOutput &search_output, MultiTrajDebugProto *proto);

void ParseMotionSearchOutputToInitializerResult(
    const MotionSearchOutput &search_output, InitializerDebugProto *proto);

std::vector<double> GetXYRange(const PathSlBoundary &sl_boundary);

InitializerOutput MakeAebInitializerOutput(
    ApolloTrajectoryPointProto plan_start_point,
    InitializerStateProto new_state,
    const std::string &message,
    InitializerDebugProto *debug_proto,
    const std::vector<LeadingGroup> &leading_groups,
    const std::unique_ptr<ConstraintProto::LeadingObjectProto>
        &blocking_static_traj,
    const MotionConstraintParamsProto *motion_constraint_params);

void ParseFeaturesDumpingProto(
    const MotionSearchOutput &search_output,
    ExpertEvaluationProto *expert_proto,
    SampledDpMotionEvaluationProto *candidates_proto);

}  // namespace planning
}  // namespace pnc_x
