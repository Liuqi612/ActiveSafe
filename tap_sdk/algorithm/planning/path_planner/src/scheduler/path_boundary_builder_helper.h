
#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include <absl/types/span.h>

#include "common/path_sl_boundary.h"
#include "pncx_lane_change.pb.h"
#include "maps/semantic_map_defs.h"
#include "math/frenet_common.h"
#include "math/vec.h"
#include "object/spacetime_trajectory_manager.h"
#include "router/drive_passage.h"
#include "scheduler/smooth_reference_line_result.h"
#include "pncx_trajectory_point.pb.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

class PathBoundary {
 public:
    PathBoundary(std::vector<double> right, std::vector<double> left);

    const std::vector<double> &right_vec() const;

    const std::vector<double> &left_vec() const;

    std::vector<double> *mutable_right_vec();

    std::vector<double> *mutable_left_vec();

    std::vector<double> &&moved_left_vec();
    std::vector<double> &&moved_right_vec();

    double right(int i) const;

    double left(int i) const;

    void ExtendLeftTo(double uniform_left);

    void ExtendRightTo(double uniform_right);

    void ShiftLeftBy(double offset);

    void ShiftRightBy(double offset);

    void ShiftLeftByIndex(int index, double offset);

    void ShiftRightByIndex(int index, double offset);

    void OuterClampRightByIndex(int index, double right_l);

    void OuterClampLeftByIndex(int index, double left_l);

    void InnerClampRightByIndex(int index, double right_l);

    void InnerClampLeftByIndex(int index, double left_l);

    void OuterClampBy(const PathBoundary &other);

    void SoftOuterClampBy(const PathBoundary &other,
                          const std::pair<int, int> &left_split_range,
                          const std::pair<int, int> &right_split_range);

    void InnerClampBy(const PathBoundary &other);

    void EraseFrom(int index);

    int size() const;

 private:
    std::vector<double> right_;
    std::vector<double> left_;
};

PathBoundary BuildPathBoundaryFromTargetLane(
    const DrivePassage &drive_passage,
    const double &ego_v,
    const std::pair<int, int> &left_split_range,
    const std::pair<int, int> &right_split_range,
    double min_half_lane_width,
    bool borrow_lane_boundary);

PathBoundary BuildCurbPathBoundary(const DrivePassage &drive_passage);

PathBoundary BuildSolidPathBoundary(
    const DrivePassage &drive_passage,
    const FrenetCoordinate &cur_sl,
    const VehicleGeometryParamsProto &vehicle_geom,
    const ApolloTrajectoryPointProto &plan_start_point,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const LaneChangeStateProto &lc_state,
    double target_lane_offset,
    const std::pair<int, int> &left_split_range,
    const std::pair<int, int> &right_split_range,
    const std::vector<double> &center_l);

PathBoundary BuildPathBoundaryFromAvKinematics(
    const DrivePassage &drive_passage,
    const ApolloTrajectoryPointProto &plan_start_point,
    const VehicleGeometryParamsProto &vehicle_geom,
    const FrenetCoordinate &cur_sl,
    const FrenetBox &sl_box,
    const LaneChangeStateProto &lc_state,
    absl::Span<const double> s_vec,
    double target_lane_offset,
    double max_lane_change_lat_accel,
    bool lane_change_pause);

PathBoundary ShrinkPathBoundaryForLaneChangePause(
    const VehicleGeometryParamsProto &vehicle_geom,
    const FrenetBox &sl_box,
    const LaneChangeStateProto &lc_state,
    PathBoundary boundary,
    double target_lane_offset,
    const std::vector<double> &center_l);

PathBoundary ExtendPathBoundaryForLaneChangePause(
    const LaneChangeStateProto &lc_state,
    const double half_lane_width,
    PathBoundary boundary,
    const std::vector<double> &smooth_center_offset);

PathBoundary ShrinkPathBoundaryForObject(
    const DrivePassage &drive_passage,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const ApolloTrajectoryPointProto &plan_start_point,
    absl::Span<const double> s_vec,
    absl::Span<const double> center_l,
    absl::Span<const Vec2d> center_xy,
    const PathBoundary &inner_boundary,
    const PathBoundary &curb_boundary,
    PathBoundary boundary,
    const FrenetBox &sl_box,
    const bool &borrow_lane);

bool ObstsacleFilter(const SpacetimeObjectTrajectory *traj,
                     const DrivePassage &drive_passage,
                     const ApolloTrajectoryPointProto &plan_start_point);

double ComputeTargetLaneOffset(
    const DrivePassage &drive_passage,
    const FrenetCoordinate &cur_sl,
    const LaneChangeStateProto &lc_state,
    const ApolloTrajectoryPointProto &plan_start_point,
    double half_av_width,
    int is_force_lc,
    double force_lc_offset_ratio,
    absl::Span<const SpacetimeObjectTrajectory> obj_trajs);

PathSlBoundary BuildPathSlBoundary(const DrivePassage &drive_passage,
                                   std::vector<double> s_vec,
                                   std::vector<double> ref_center_l,
                                   PathBoundary inner_boundary,
                                   PathBoundary outer_boundary,
                                   PathBoundary opt_outer_boundary);

std::vector<double> ComputeSmoothedReferenceLine(
    const DrivePassage &drive_passage,
    const SmoothedReferenceLineResultMap &smooth_result_map);

absl::StatusOr<SmoothedReferenceLineResultMap> GenerateSmoothedResultMap(
    ads_x::planning::LaneSequencePtr lane_sequence_ptr);

std::vector<double> ComputeCompensationRefLine(
    const DrivePassage &drive_passage,
    const std::vector<double> &center_l,
    const ApolloTrajectoryPointProto &plan_start_point,
    const boost::optional<double> &ref_centered_compensation_offset);
}  // namespace planning
}  // namespace pnc_x
