
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "math/geometry/box2d.h"
#include "math/geometry/polygon2d.h"
#include "object/planner_object.h"
#include "object/spacetime_object_state.h"
#include "pncx_perception.pb.h"
#include "plan/second_order_trajectory_point.h"
#include "prediction/predicted_trajectory.h"
#include "prediction/prediction.h"
#include "speed/speed_point.h"
#include <absl/status/statusor.h>
#include <absl/strings/str_format.h>
#include <absl/strings/str_split.h>
#include <absl/strings/string_view.h>
#include <absl/types/span.h>

namespace pnc_x {
namespace planning {

class SpacetimeObjectTrajectory {
 public:
    SpacetimeObjectTrajectory(const PlannerObject &planner_object,
                              int traj_index,
                              double required_lateral_gap);

    SpacetimeObjectTrajectory(const PlannerObject &planner_object,
                              std::vector<SpacetimeObjectState> states,
                              int traj_index,
                              double required_lateral_gap);

    SpacetimeObjectTrajectory(const PlannerObject &planner_object,
                              prediction::PredictedTrajectory traj,
                              int traj_index,
                              double required_lateral_gap);

    SpacetimeObjectTrajectory(const SpacetimeObjectTrajectory &other);
    SpacetimeObjectTrajectory &operator=(
        const SpacetimeObjectTrajectory &other);

    SpacetimeObjectTrajectory(const SpacetimeObjectTrajectory &other,
                              const size_t &modify_size);

    SpacetimeObjectTrajectory(SpacetimeObjectTrajectory &&other) = default;
    SpacetimeObjectTrajectory &operator=(SpacetimeObjectTrajectory &&other) =
        default;

    absl::StatusOr<SpacetimeObjectTrajectory> CreateTruncatedCopy(
        double start_offset, double end_t) const;

    std::vector<SpeedPoint> GenerateConstAccelSpeedPoints(
        double init_v,
        double init_s,
        double init_t,
        double accel,
        double step_time,
        double acc_time,
        double duration) const;

    absl::StatusOr<SpacetimeObjectTrajectory> CreateExtendTrajectory(
        int extend_steps, double time_step) const;

    SpacetimeObjectTrajectory CreateTrajectoryMutatedInstance(
        prediction::PredictedTrajectory traj) const {
        return SpacetimeObjectTrajectory(planner_object_, std::move(traj),
                                         traj_index_, required_lateral_gap_);
    }

    SpacetimeObjectTrajectory CreateLateralGapMutatedInstance(
        double lateral_gap) const {
        return SpacetimeObjectTrajectory(planner_object_, traj_index_,
                                         lateral_gap);
    }

    absl::Span<const SpacetimeObjectState> states() const { return states_; }

    std::vector<SpacetimeObjectState> *mutable_states() { return &states_; }

    std::string traj_id() const { return traj_id_; }

    int traj_index() const { return traj_index_; }
    void set_traj_index(int idx) { traj_index_ = idx; }

    double required_lateral_gap() const { return required_lateral_gap_; }

    bool is_stationary() const { return is_stationary_; }

    std::string object_id() const { return planner_object_.id(); }

    ObjectType object_type() const { return planner_object_.type(); }

    const prediction::ObjectLongTermBehavior long_term_behavior() const {
        return planner_object_.long_term_behavior();
    }

    const SecondOrderTrajectoryPoint &pose() const {
        return *states_[0].traj_point;
    }

    const Polygon2d &contour() const { return states_[0].contour; }

    const Box2d &bounding_box() const { return states_[0].box; }

    const PlannerObject &planner_object() const { return planner_object_; }

    const prediction::PredictedTrajectory &trajectory() const {
        return trajectory_;
    }

    prediction::PredictedTrajectory *mutable_trajectory() {
        return &trajectory_;
    }

    std::vector<double> *mutable_lateral_gaps_for_merge();

    const std::vector<double> &lateral_gaps_for_merge() const;

    static std::string MakeTrajectoryId(std::string obj_id, int traj_index) {
        return fmt::format("{}-idx{}", obj_id, traj_index);
    }

    static std::string GetObjectIdFromTrajectoryId(std::string traj_id) {
        const std::vector<std::string> tokens = absl::StrSplit(traj_id, "-");
        if (!XCHECK(!tokens.empty())) {
            return "";
        }
        return tokens.front();
    }

 private:
    int traj_index_{};

    std::string traj_id_;
    bool is_stationary_;
    PlannerObject planner_object_;
    double required_lateral_gap_;
    std::vector<SpacetimeObjectState> states_;
    std::vector<double> lateral_gaps_for_merge_;
    prediction::PredictedTrajectory trajectory_;
};

}  // namespace planning
}  // namespace pnc_x
