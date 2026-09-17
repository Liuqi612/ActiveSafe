
#pragma once

#include <map>
#include <string>
#include <vector>

#include "common/path_sl_boundary.h"
#include "pncx_constraint.pb.h"
#include "math/frenet_common.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "router/drive_passage.h"
#include "pncx_vehicle.pb.h"
#include <absl/container/flat_hash_set.h>

namespace pnc_x {
namespace planning {

using LeadingGroup = std::map<std::string, ConstraintProto::LeadingObjectProto>;

std::vector<LeadingGroup> FindMultipleLeadingGroups(
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_boundary,
    bool lc_left,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const absl::flat_hash_set<std::string> &stalled_objects,
    const ApolloTrajectoryPointProto &plan_start_point,
    const FrenetBox &ego_frenet_box,
    const VehicleGeometryParamsProto &vehicle_geom,
    bool is_astar_searcher,
    std::vector<std::vector<std::string>> *insertion_orders,
    std::string *current_path_leader_id,
    const std::unordered_map<std::string, std::shared_ptr<DrivePassage>>
        *drive_passages = nullptr);

}  // namespace planning
}  // namespace pnc_x
