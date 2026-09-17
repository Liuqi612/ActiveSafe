
#pragma once

#include <absl/container/flat_hash_set.h>
#include <boost/optional.hpp>
#include <limits>

#include "common/path_sl_boundary.h"
#include "pncx_constraint.pb.h"
#include "pncx_lane_change.pb.h"
#include "object/spacetime_object_trajectory.h"
#include "router/drive_passage.h"
#include "util/hmi_content_util.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

class SpacetimePlannerObjectTrajectoriesFilter {
 public:
    virtual bool Filter(const SpacetimeObjectTrajectory &traj) const = 0;
    virtual ~SpacetimePlannerObjectTrajectoriesFilter() = default;
};

class CutInSpacetimePlannerObjectTrajectoriesFilter
    : public SpacetimePlannerObjectTrajectoriesFilter {
 public:
    CutInSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage,
        const LaneChangeStateProto *lane_change_state,
        const Box2d &av_box,
        double av_speed);
    bool Filter(const SpacetimeObjectTrajectory &traj) const override;

 private:
    const DrivePassage *drive_passage_;
    const LaneChangeStateProto *lane_change_state_;
    Box2d av_box_;
    boost::optional<FrenetBox> av_sl_box_;
    double av_speed_;
};

class CutInVehicleSpacetimePlannerObjectTrajectoriesFilter
    : public SpacetimePlannerObjectTrajectoriesFilter {
 public:
    CutInVehicleSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage,
        const LaneChangeStateProto *lane_change_state,
        const Box2d &av_box,
        double av_speed);
    bool Filter(const SpacetimeObjectTrajectory &traj) const override;

 private:
    const DrivePassage *drive_passage_;
    const LaneChangeStateProto *lane_change_state_;
    Box2d av_box_;
    boost::optional<FrenetBox> av_sl_box_;
    double av_speed_;
};

class CrossingSpacetimePlannerObjectTrajectoriesFilter
    : public SpacetimePlannerObjectTrajectoriesFilter {
 public:
    CrossingSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage);
    bool Filter(const SpacetimeObjectTrajectory &traj) const override;

 private:
    const DrivePassage *drive_passage_;
};

class ReverseVehicleSpacetimePlannerObjectTrajectoriesFilter
    : public SpacetimePlannerObjectTrajectoriesFilter {
 public:
    ReverseVehicleSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage,
        const VehicleGeometryParamsProto *vehicle_geometry_params,
        const PathSlBoundary *sl_boundary,
        const NudgeObjectInfo *nudge_object_info,
        Box2d av_box,
        double av_speed);
    bool Filter(const SpacetimeObjectTrajectory &traj) const override;

 private:
    const DrivePassage *drive_passage_;
    const VehicleGeometryParamsProto *vehicle_geometry_params_;
    const PathSlBoundary *sl_boundary_;
    const NudgeObjectInfo *nudge_object_info_;
    const Box2d av_box_;
    const double av_speed_;
};

class BeyondStopLineSpacetimePlannerObjectTrajectoriesFilter
    : public SpacetimePlannerObjectTrajectoriesFilter {
 public:
    BeyondStopLineSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage,
        absl::Span<const ConstraintProto::StopLineProto> stop_lines);
    bool Filter(const SpacetimeObjectTrajectory &traj) const override;

 private:
    const DrivePassage *drive_passage_;
    double first_stop_line_s_ = std::numeric_limits<double>::infinity();
};

bool IsCutInObjectTrajectory(const DrivePassage &drive_passage,
                             const bool is_lane_change,
                             const double av_speed,
                             const FrenetBox &av_sl_box,
                             const SpacetimeObjectTrajectory &traj);

class DecisionSpacetimePlannerObjectTrajectoriesFilter
    : public SpacetimePlannerObjectTrajectoriesFilter {
 public:
    DecisionSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage,
        const SpacetimePlannerObjectTrajectoriesProto *prev_st_trajs,
        const VehicleGeometryParamsProto *vehicle_geometry_params,
        Box2d av_box,
        double av_speed);
    bool Filter(const SpacetimeObjectTrajectory &traj) const override;

 private:
    const DrivePassage *drive_passage_;
    Box2d av_box_;
    double av_speed_;
    const VehicleGeometryParamsProto *veh_geo_;
    boost::optional<FrenetBox> av_sl_box_;
    absl::flat_hash_set<std::string> prev_st_planner_obj_id_;
};

}  // namespace planning
}  // namespace pnc_x
