

#include <algorithm>
#include <vector>

#include "object/planner_object.h"
#include "object/spacetime_object_trajectory.h"
#include "prediction/prediction_util.h"
#include <absl/status/status.h>
#include <absl/strings/str_cat.h>

namespace pnc_x {
namespace planning {

namespace {
constexpr double kEpsilon = 1e-6;
constexpr double kStaticSpeed = 0.5;
}

SpacetimeObjectTrajectory::SpacetimeObjectTrajectory(
    const PlannerObject &planner_object,
    int traj_index,
    double required_lateral_gap)
    : traj_index_(traj_index),
      traj_id_(MakeTrajectoryId(planner_object.id(), traj_index)),
      planner_object_(planner_object),
      required_lateral_gap_(required_lateral_gap) {
    XCHECK_GE(traj_index_, 0);
    XCHECK_LT(traj_index_, planner_object.num_trajs());
    trajectory_ =
        prediction::PredictedTrajectory(planner_object.traj(traj_index_));
    states_ = SampleTrajectoryStates(trajectory_, planner_object_.pose().pos(),
                                     planner_object_.contour(),
                                     planner_object_.bounding_box());
    is_stationary_ = prediction::IsStationaryTrajectory(trajectory_) ||
                     planner_object_.is_stationary() ||
                     (trajectory_.points().front().v() < kStaticSpeed);
}

SpacetimeObjectTrajectory::SpacetimeObjectTrajectory(
    const SpacetimeObjectTrajectory &other) {
    *this = other;
}

SpacetimeObjectTrajectory &SpacetimeObjectTrajectory::operator=(
    const SpacetimeObjectTrajectory &other) {
    if (this != &other) {
        traj_index_ = other.traj_index_;
        traj_id_ = other.traj_id_;
        is_stationary_ = other.is_stationary_;
        planner_object_ = other.planner_object_;
        required_lateral_gap_ = other.required_lateral_gap_;
        trajectory_ = other.trajectory_;

        states_.clear();
        states_.reserve(other.states_.size());
        const auto &traj_points = trajectory_.points();
        for (size_t i = 0; i < other.states_.size(); ++i) {
            const auto &other_state = other.states_[i];
            states_.push_back(
                SpacetimeObjectState{.traj_point = &traj_points[i],
                                     .box = other_state.box,
                                     .contour = other_state.contour});
        }
    }
    return *this;
}

SpacetimeObjectTrajectory::SpacetimeObjectTrajectory(
    const SpacetimeObjectTrajectory &other, const size_t &modify_size)
    : traj_index_(other.traj_index_),
      traj_id_(other.traj_id_),
      is_stationary_(other.is_stationary_),
      planner_object_(other.planner_object_),
      required_lateral_gap_(other.required_lateral_gap_) {
    trajectory_.mutable_points()->reserve(
        std::max(modify_size, other.states_.size()));
    trajectory_ = other.trajectory_;

    states_.clear();
    states_.reserve(other.states_.size());
    const auto &traj_points = trajectory_.points();
    for (size_t i = 0; i < other.states_.size(); ++i) {
        const auto &other_state = other.states_[i];
        states_.push_back(SpacetimeObjectState{.traj_point = &traj_points[i],
                                               .box = other_state.box,
                                               .contour = other_state.contour});
    }
}

absl::StatusOr<SpacetimeObjectTrajectory>
SpacetimeObjectTrajectory::CreateTruncatedCopy(double start_offset,
                                               double horizon) const {
    if (states_.empty()) {
        return absl::FailedPreconditionError(
            absl::StrCat("The trajectory ", traj_id_, " has no states."));
    }
    std::vector<SpacetimeObjectState> truncated_states;
    truncated_states.reserve(states_.size());

    constexpr double kEps = 1e-6;
    const double start_t = states_[0].traj_point->t() + start_offset - kEps;
    for (size_t i = 0, n = states_.size(); i < n; ++i) {
        if (states_[i].traj_point->t() - start_t > horizon) {
            break;
        }
        if (states_[i].traj_point->t() >= start_t) {
            truncated_states.push_back(states_[i]);
        }
    }

    if (truncated_states.empty()) {
        return absl::NotFoundError(
            absl::StrCat("No trajectory left after truncating ", traj_id_,
                         " with horizon ", horizon));
    }
    return SpacetimeObjectTrajectory(planner_object_,
                                     std::move(truncated_states), traj_index_,
                                     required_lateral_gap_);
}

std::vector<SpeedPoint>
SpacetimeObjectTrajectory::GenerateConstAccelSpeedPoints(
    double init_v,
    double init_s,
    double init_t,
    double accel,
    double step_time,
    double acc_time,
    double duration) const {
    std::vector<SpeedPoint> speed_points;
    speed_points.reserve(static_cast<size_t>(std::ceil(duration / step_time)));
    double prev_v = init_v, prev_s = init_s;
    for (double t = step_time; t < duration + kEpsilon; t += step_time) {
        SpeedPoint sp;
        sp.set_t(t + init_t);
        if (t <= acc_time + kEpsilon) {
            const double v = std::max(0.0, prev_v + accel * step_time);
            sp.set_t(t + init_t);
            sp.set_a((v - prev_v) / step_time);
            sp.set_v(v);
            sp.set_s(prev_s + 0.5 * (prev_v + v) * step_time);
            sp.set_j(0.0);
        } else {
            sp.set_t(t + init_t);
            sp.set_a(0.0);
            sp.set_v(prev_v);
            sp.set_s(prev_s + prev_v * step_time);
            sp.set_j(0.0);
        }
        prev_v = sp.v();
        prev_s = sp.s();
        speed_points.emplace_back(std::move(sp));
    }
    return speed_points;
}

absl::StatusOr<SpacetimeObjectTrajectory>
SpacetimeObjectTrajectory::CreateExtendTrajectory(int extend_steps,
                                                  double time_step) const {
    if (states_.empty()) {
        return absl::FailedPreconditionError(
            absl::StrCat("The trajectory ", traj_id_, " has no states."));
    }

    const double extended_time = static_cast<double>(extend_steps) * time_step;
    prediction::PredictedTrajectory extend_traj(trajectory_);
    const double duration = extended_time - states_.back().traj_point->t();
    if (duration <= 0.0) {
        return absl::AbortedError("no need to extend");
    }

    constexpr double kMaxAccTime = 2.0;
    const auto back_point = *states_.back().traj_point;

    const auto speed_points = GenerateConstAccelSpeedPoints(
        back_point.v(), back_point.s(), back_point.t(), back_point.a(),
        time_step, kMaxAccTime, duration);

    prediction::PredictedTrajectoryPoint last_point = back_point;
    const double cos_theta = std::cos(last_point.theta());
    const double sin_theta = std::sin(last_point.theta());
    for (const auto &sp : speed_points) {
        last_point.set_v(sp.v());
        last_point.set_a(sp.a());
        last_point.set_t(sp.t());
        const double cur_x =
            last_point.pos().x() + cos_theta * (sp.s() - last_point.s());
        const double cur_y =
            last_point.pos().y() + sin_theta * (sp.s() - last_point.s());
        last_point.set_pos(Vec2d(cur_x, cur_y));
        last_point.set_s(sp.s());
        extend_traj.mutable_points()->emplace_back(last_point);
    }

    return SpacetimeObjectTrajectory(planner_object_, std::move(extend_traj),
                                     traj_index_, required_lateral_gap_);
}

SpacetimeObjectTrajectory::SpacetimeObjectTrajectory(
    const PlannerObject &planner_object,
    std::vector<SpacetimeObjectState> states,
    int traj_index,
    double required_lateral_gap)
    : traj_index_(traj_index),
      traj_id_(MakeTrajectoryId(planner_object.id(), traj_index)),
      planner_object_(planner_object),
      required_lateral_gap_(required_lateral_gap),
      states_(std::move(states)) {
    XCHECK_GE(traj_index_, 0);
    XCHECK_LT(traj_index_, planner_object.num_trajs());
    trajectory_ =
        prediction::PredictedTrajectory(planner_object.traj(traj_index_));
    is_stationary_ = prediction::IsStationaryTrajectory(trajectory_) ||
                     planner_object.is_stationary();
}

SpacetimeObjectTrajectory::SpacetimeObjectTrajectory(
    const PlannerObject &planner_object,
    prediction::PredictedTrajectory traj,
    int traj_index,
    double required_lateral_gap)
    : traj_index_(traj_index),
      traj_id_(MakeTrajectoryId(planner_object.id(), traj_index)),
      planner_object_(planner_object),
      required_lateral_gap_(required_lateral_gap),
      trajectory_(std::move(traj)) {
    XCHECK_GE(traj_index_, 0);
    XCHECK_LT(traj_index_, planner_object.num_trajs());
    states_ = SampleTrajectoryStates(trajectory_, planner_object_.pose().pos(),
                                     planner_object_.contour(),
                                     planner_object_.bounding_box());
    is_stationary_ = prediction::IsStationaryTrajectory(trajectory_) ||
                     planner_object.is_stationary();
}

std::vector<double>
    *SpacetimeObjectTrajectory::mutable_lateral_gaps_for_merge() {
    return &lateral_gaps_for_merge_;
}

const std::vector<double> &SpacetimeObjectTrajectory::lateral_gaps_for_merge()
    const {
    return lateral_gaps_for_merge_;
}

}  // namespace planning
}  // namespace pnc_x
