#pragma once

#include <unordered_map>
#include <vector>

#include "initializer/interactive_search/common/common.h"
#include "initializer/select_nudge_object.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "plan/trajectory_point.h"
#include "router/drive_passage.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

typedef std::unordered_map<std::string, OvertakeYieldType> ObjectLongDecision;
typedef std::unordered_map<std::string, ObstacleDecision> ObjectDecisions;

absl::StatusOr<ObjectDecisions> ParseObjectDecisions(
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const NudgeInfos &nudge_infos,
    const ObjectLongDecision &long_decisons,
    const boost::optional<std::string> &leader_id,
    const boost::optional<std::string> &follower_id);

absl::StatusOr<ObjectLongDecision> ParseObjectLongDecisions(
    bool is_lane_change,
    const DrivePassage &drive_passage,
    const std::vector<TrajectoryPoint> &result_points,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const VehicleGeometryParamsProto &vehicle_geometry_params);

ObjectDecisions StabilizeObjectDecisions(
    const ObjectDecisions *pre_object_decisions,
    const ObjectDecisions &object_decisions);

ObjectDecisions ExtractObjectDecisions(
    const std::vector<ApolloTrajectoryPointProto> &traj_result,
    bool is_lane_change,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_sl_boundary,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const VehicleGeometryParamsProto &vehicle_geometry_params,
    const std::string &prefix,
    const int plan_id,
    NudgeInfos *nudge_info,
    const ObsDecisionGap &best_gap_result,
    const ObjectDecisions *pre_object_decisions);

}  // namespace planning
}  // namespace pnc_x
