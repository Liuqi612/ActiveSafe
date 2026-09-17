
#pragma once

#include <map>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "common/path_sl_boundary.h"
#include "pncx_constraint.pb.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "plan/trajectory_point.h"
#include "router/drive_passage.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

namespace optimizer {

class PathTimeCorridor {
 public:
    struct BoundaryInfo {
        enum Type {
            CURB = 0,
            LANE_BOUNDARY = 1,
            VRU = 2,
            VEHICLE = 3,
            LARGE_VEHICLE = 4,
            STATIC = 5,
        };
        Type type;
        double l_outer_boundary;
        double l_boundary;
        double l_outer_object;
        double l_object;
        double l_curb;
        const SpacetimeObjectTrajectory *object_ptr = nullptr;

        static Type GetType(StationBoundaryType type);

        static Type GetObjectType(const ObjectType &object_type);
    };
    enum PositionType {
        POSITION_UNKNOWN = 0,
        POSITION_LEFT = 1,
        POSITION_RIGHT = 2
    };
    struct ObjectPositionInfo {
        bool is_static;
        double check_time;
        double object_s;
        double object_l;
        double init_object_s;
        double init_object_l;
        PositionType position_type;
    };
    using ObjectPositionInfos =
        std::unordered_map<std::string, std::vector<ObjectPositionInfo>>;

    PathTimeCorridor(const DrivePassage *drive_passage,
                     const PathSlBoundary *path_sl_boundary,
                     std::vector<std::vector<BoundaryInfo>> left_boundary,
                     std::vector<std::vector<BoundaryInfo>> right_boundary,
                     std::vector<int> time_indices,
                     ObjectPositionInfos object_position_infos);

    std::pair<BoundaryInfo, BoundaryInfo> QueryBoundaryL(double s,
                                                         double t) const;

    std::vector<ObjectPositionInfo> QueryObjectPositionInfo(
        std::string object_id) const;

 private:
    const DrivePassage *drive_passage_;
    const PathSlBoundary *path_sl_boundary_;
    std::vector<std::vector<BoundaryInfo>> left_boundary_;
    std::vector<std::vector<BoundaryInfo>> right_boundary_;
    std::vector<int> time_indices_;
    ObjectPositionInfos object_position_infos_;
};

absl::StatusOr<PathTimeCorridor> BuildPathTimeCorridor(
    const int plan_id,
    std::string base_name,
    const std::vector<TrajectoryPoint> &init_traj,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_sl_boundary,
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        &leading_trajs,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const VehicleGeometryParamsProto &veh_geo_params,
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step);

}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
