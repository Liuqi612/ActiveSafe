
#pragma once

#include <map>
#include <string>
#include <vector>

#include "common/path_sl_boundary.h"
#include "pncx_constraint.pb.h"
#include "math/frenet_common.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "router/drive_passage.h"
#include "pncx_vehicle.pb.h"
#include <absl/container/flat_hash_set.h>

namespace pnc_x {

namespace planning {

enum class ObstacleDirection : uint8_t {
    kOncoming = 0,
    kSameDirection,
};

enum class ObstacleIntention : uint8_t {
    kUnknown = 0,
    kNoIntention,
    kIgnore,
    kLeftCross,
    kRightCross,
    kLeftCrossBack,
    kRightCrossBack,
    kLeftCutin,
    kRightCutin,
    kLeftLeftCutin,
    kRightRightCutin,
    kCutoutLeft,
    kCutoutRight,
    kCutoutLeftLeft,
    kCutoutRightRight,
};

struct ObstacleBehavior {
    ObstacleBehavior()
        : obs_intent(ObstacleIntention::kUnknown),
          obs_direction(ObstacleDirection::kSameDirection) {}
    ObstacleIntention obs_intent;
    ObstacleDirection obs_direction;
};

std::unordered_map<std::string, ObstacleBehavior> InferObstaclesBehavior(
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_boundary,
    const FrenetBox &ego_frenet_box,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const ApolloTrajectoryPointProto &plan_start_point,
    bool lc_left,
    bool is_lane_change);

}  // namespace planning

}  // namespace pnc_x
