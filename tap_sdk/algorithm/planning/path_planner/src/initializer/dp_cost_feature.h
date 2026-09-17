
#pragma once

#include <algorithm>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

#include "common/path_sl_boundary.h"
#include "initializer/collision_checker.h"
#include "initializer/motion_search_types.h"
#include "initializer/cost_feature.h"
#include "initializer/ref_speed_table.h"
#include "math/piecewise_linear_function.h"
#include <absl/types/span.h>

#include "object/spacetime_trajectory_manager.h"
#include "pncx_planner_params.pb.h"
#include "router/drive_passage.h"

namespace pnc_x {
namespace planning {
class DpAccelerationFeatureCost : public FeatureCost {
 public:
    explicit DpAccelerationFeatureCost(
        const MotionConstraintParamsProto &motion_constraint_params,
        const InitializerSceneType init_scene_type)
        : FeatureCost("dp_acceleration"),
          init_scene_type_(init_scene_type),
          max_accel_constraint_(motion_constraint_params.max_acceleration()),
          max_decel_constraint_(motion_constraint_params.max_deceleration()) {}
    void ComputeCost(const MotionEdgeInfo &edge_info,
                     absl::Span<double> cost) const override;

 private:
    const InitializerSceneType init_scene_type_;
    double max_accel_constraint_;
    double max_decel_constraint_;
};

class DpLaneBoundaryFeatureCost : public FeatureCost {
 public:
    explicit DpLaneBoundaryFeatureCost(
        const PathSlBoundary *path_sl,
        const InitializerSceneType init_scene_type,
        double sdc_half_width)
        : FeatureCost("dp_lane_boundary"),
          path_sl_(path_sl),
          init_scene_type_(init_scene_type),
          sdc_half_width_(sdc_half_width) {}

    void ComputeCost(const MotionEdgeInfo &,
                     absl::Span<double> cost) const override;

 private:
    const PathSlBoundary *path_sl_;
    const InitializerSceneType init_scene_type_;
    double sdc_half_width_;
};

class DpCurvatureFeatureCost : public FeatureCost {
 public:
    DpCurvatureFeatureCost() : FeatureCost("dp_curvature") {}

    void ComputeCost(const MotionEdgeInfo &edge_info,
                     absl::Span<double> cost) const override;
};

class DpLateralAccelerationFeatureCost : public FeatureCost {
 public:
    explicit DpLateralAccelerationFeatureCost(
        const InitializerSceneType init_scene_type, bool is_lane_change)
        : FeatureCost("dp_lateral_acceleration"),
          init_scene_type_(init_scene_type),
          is_lane_change_(is_lane_change) {}

    void ComputeCost(const MotionEdgeInfo &edge_info,
                     absl::Span<double> cost) const override;

 private:
    const InitializerSceneType init_scene_type_;
    bool is_lane_change_;
};

class DpStopConstraintFeatureCost : public FeatureCost {
 public:
    explicit DpStopConstraintFeatureCost(const std::vector<double> &stop_s)
        : FeatureCost("dp_stop_constraint"),
          nearest_stop_s_(stop_s.empty() ? std::numeric_limits<double>::max()
                                         : *std::min_element(stop_s.begin(),
                                                             stop_s.end())) {}

    void ComputeCost(const MotionEdgeInfo &edge_info,
                     absl::Span<double> cost) const override;

 private:
    double nearest_stop_s_;
};

class DpRefSpeedFeatureCost : public FeatureCost {
 public:
    explicit DpRefSpeedFeatureCost(const RefSpeedTable *ref_speed_table,
                                   const InitializerSceneType init_scene_type)
        : FeatureCost("dp_ref_speed"),
          ref_speed_table_(ref_speed_table),
          init_scene_type_(init_scene_type) {}

    void ComputeCost(const MotionEdgeInfo &edge_info,
                     absl::Span<double> cost) const override;

 private:
    const RefSpeedTable *ref_speed_table_;
    const InitializerSceneType init_scene_type_;
};

class DpDynamicCollisionFeatureCost : public FeatureCost {
 public:
    explicit DpDynamicCollisionFeatureCost(
        const CollisionChecker *collision_checker);

    void ComputeCost(const MotionEdgeInfo &edge_info,
                     absl::Span<double> cost) const override;

    IgnoreTrajMap ComputeInteractiveCost(const MotionEdgeInfo &edge_info,
                                         const IgnoreTrajMap &ignored_trajs,
                                         absl::Span<double> cost) const;

 private:
    const CollisionChecker *cc_;
};

class DpLeadingObjectFeatureCost : public FeatureCost {
 public:
    explicit DpLeadingObjectFeatureCost(
        const DrivePassage &drive_passage,
        const SpacetimeTrajectoryManager &st_traj_mgr,
        const std::vector<std::string> &leading_trajs,
        double ego_front_to_ra);

    void ComputeCost(const MotionEdgeInfo &edge_info,
                     absl::Span<double> cost) const override;

 private:
    double ego_front_to_ra_;
    PiecewiseLinearFunction<double> max_s_t_;
};

class DpFinalProgressFeatureCost : public FeatureCost {
 public:
    explicit DpFinalProgressFeatureCost(
        const PathSlBoundary *path_sl,
        const InitializerSceneType init_scene_type,
        double max_accumulated_s)
        : FeatureCost("dp_final_progress"),
          path_sl_(path_sl),
          init_scene_type_(init_scene_type),
          max_accumulated_s_(max_accumulated_s) {}

    void ComputeCost(const MotionEdgeInfo &edge_info,
                     absl::Span<double> cost) const override;

 private:
    const PathSlBoundary *path_sl_;
    const InitializerSceneType init_scene_type_;
    double max_accumulated_s_;
};

}  // namespace planning
}  // namespace pnc_x
