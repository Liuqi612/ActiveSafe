#pragma once

#include <vector>

#include "initializer/interactive_search/common/common.h"
#include "initializer/motion_form.h"
#include "initializer/motion_graph.h"
#include "initializer/motion_state.h"
#include "pncx_trajectory_point.pb.h"

namespace pnc_x {
namespace planning {

ApolloTrajectoryPointProto MotionState2TrajPoint(
    const MotionState &motion_state, double s, double current_t);

void ResampleTrajectoryPoints(
    const std::vector<const MotionForm *> &motions,
    std::vector<ApolloTrajectoryPointProto> &traj_points);

std::vector<ApolloTrajectoryPointProto> ConstructStationaryTraj(
    const MotionState &sdc_motion);

MotionState PrepareStartMotionNode(
    const GeometryGraph &geometry,
    const std::vector<GeometryNodeIndex> &first_layer,
    const ApolloTrajectoryPointProto &start_point,
    int *start_node_idx_on_first_layer);

std::vector<double> AddCost(absl::Span<const double> vec1,
                            absl::Span<const double> vec2);

absl::StatusOr<std::vector<ApolloTrajectoryPointProto>> ResampleDenseTrajectory(
    const std::vector<ApolloTrajectoryPointProto> &trajectory,
    double time_step);

void ConstructTrajResult(std::vector<ApolloTrajectoryPointProto> *traj,
                         double time_step,
                         int min_traj_size);

absl::StatusOr<std::vector<ApolloTrajectoryPointProto>> ConstructTrajResult(
    const std::vector<ApolloTrajectoryPointProto> &selected_traj,
    double time_step,
    int min_traj_size);

void VisualizeObsTrajs(
    const std::vector<ObstacleDecisionGroup> &decision_groups,
    const std::string &prefix);

void VisualizeTrajResult(const std::vector<ApolloTrajectoryPointProto> &traj,
                         const std::string &prefix);

}  // namespace planning
}  // namespace pnc_x
