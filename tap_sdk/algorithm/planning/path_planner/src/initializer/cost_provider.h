
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "common/path_sl_boundary.h"
#include "initializer/collision_checker.h"
#include "initializer/cost_feature.h"
#include "initializer/geometry/geometry_form.h"
#include "initializer/motion_form.h"
#include "initializer/ref_speed_table.h"
#include <absl/types/span.h>

#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "pncx_planner_params.pb.h"
#include "router/drive_passage.h"
#include "pncx_vehicle.pb.h"
namespace pnc_x {
namespace planning {

class CostProviderBase {
 public:
    absl::Span<const std::string> cost_names() const { return cost_names_; }

    absl::Span<const double> weights() const { return weights_; }

    void ComputeDpCost(double start_t,
                       const MotionForm *motion_form,
                       absl::Span<double> cost) const;
    // Shared dynamic interaction cost used by Interactive A* and the
    // reference DP search.  The name deliberately describes the shared
    // contract rather than making A* appear to depend on the DP algorithm.
    IgnoreTrajMap ComputeInteractiveCost(double start_t,
                                         const MotionForm *motion_form,
                                         const IgnoreTrajMap &ignored_trajs,
                                         absl::Span<double> cost) const;
    void ComputeDpLeadingObjCost(double start_t,
                                 const MotionForm *motion_form,
                                 absl::Span<double> cost) const;
    void ComputeRefLineCost(const GeometryForm *geometry_form,
                            bool terminating,
                            absl::Span<double> cost) const;

 protected:
    template <typename Config>
    void BuildWeightTable(const Config &cost_config);

    std::vector<std::unique_ptr<FeatureCost>> features_;

 private:
    std::vector<std::string> cost_names_;

    std::vector<double> weights_;

    std::vector<int> feature_size_;
};

class CostProvider : public CostProviderBase {
 public:
    CostProvider(const DrivePassage &drive_passage,
                 const InitializerConfig &initializer_params,
                 const MotionConstraintParamsProto &motion_constraint_params,
                 const std::vector<double> &stop_s_vec,
                 const SpacetimeTrajectoryManager &st_traj_mgr,
                 const std::vector<std::string> &leading_trajs,
                 const VehicleGeometryParamsProto &vehicle_geom,
                 const CollisionChecker *collision_checker,
                 const PathSlBoundary *path_sl,
                 const RefSpeedTable *ref_speed_table,

                 const InitializerSceneType init_scene_type,
                 bool is_lane_change,
                 double max_accumulated_s,
                 bool is_post_evaluation = false);
};

class RefLineCostProvider : public CostProviderBase {
 public:
    RefLineCostProvider(
        const SpacetimePlannerObjectTrajectories *st_planner_object_traj,
        const DrivePassage *drive_passage,
        const PathSlBoundary *path_sl,
        double geom_graph_mac_accum_s,
        double relaxed_center_max_curvature,
        const InitializerConfig &initializer_params);
};

}  // namespace planning
}  // namespace pnc_x
