
#pragma once

#include <vector>

#include "common/path_sl_boundary.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "plan/planner_defs.h"
#include "plan/trajectory_point.h"
#include "router/drive_passage.h"
#include "util/hmi_content_util.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

struct NudgeInfos {
    std::vector<NudgeObjectInfo> nudgeInfos;
    void addNudgeInfo(const NudgeObjectInfo &info) {
        nudgeInfos.push_back(info);
    }
    boost::optional<NudgeObjectInfo> findNudgeInfoById(
        const std::string &id) const;
    
    std::vector<NudgeObjectInfo> static_nudge_infos;
    void addStaticNudgeInfo(const NudgeObjectInfo &info) {
        static_nudge_infos.push_back(info);
    }

};

namespace initializer {
absl::StatusOr<NudgeInfos> SelectNudgeObjectId(
    int trajectory_steps,
    double trajectory_time_step,
    bool is_lane_change,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_sl_boundary,
    const std::vector<TrajectoryPoint> &result_points,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const VehicleGeometryParamsProto &vehicle_geometry_params,
    const int plan_id,
    std::string *nudge_debug);
}
}  // namespace planning
}  // namespace pnc_x
