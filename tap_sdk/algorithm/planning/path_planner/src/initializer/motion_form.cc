

#include "initializer/motion_form.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <ostream>

#include "math/util.h"
#include "plan/planner_defs.h"
#include "prediction/prediction_defs.h"
#include "util/loop_guard.h"
namespace pnc_x {
namespace planning {
int MotionForm::kConstTimeIntervalSampleStep = 2;
int MotionForm::kMinEqualTimeIntervalSampleStep = 4;
int MotionForm::kMaxEqualTimeIntervalSampleStep = 11;
double MotionForm::kDesireEqualTimeInterval = 0.5;

namespace {
constexpr double kZeroAccEpsilon = 0.05;
constexpr double kPositionEpsilon = 0.1;
constexpr double kZeroSpeedEpsilon = 0.1;
constexpr double kNeedPreciseSamplingDuration = 0.5;

template <bool is_fast_sample>
std::vector<MotionState> SampleWithChoice(const GeometryForm &geometry,
                                          double d_t,
                                          double duration,
                                          double init_v,
                                          double a,
                                          double stop_time,
                                          double stop_dist) {
    const int tentative_num_samples = CeilToInt(duration / d_t) + 2;
    double len = geometry.length();
    double t = 0.0;
    double v = init_v;
    double s = 0.0;
    double cur_a = a;
    const double lookforward = 0.9 * d_t;
    std::vector<MotionState> states;
    states.reserve(tentative_num_samples);
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (((t + lookforward) < duration) && loop_guard) {
        const double cur_s = std::min(s, len);
        const auto &geometry_state =
            is_fast_sample ? geometry.FastState(cur_s) : geometry.State(cur_s);
        states.push_back(
            MotionState{.xy = geometry_state.xy,
                        .h = geometry_state.h,
                        .k = geometry_state.k,
                        .ref_k = geometry_state.ref_k,
                        .t = t,
                        .v = v,
                        .a = cur_a,
                        .accumulated_s = geometry_state.accumulated_s,
                        .s = cur_s,
                        .l = geometry_state.l});

        t += d_t;
        if (t < stop_time) {
            s += (v + (0.5 * a * d_t)) * d_t;
            v += d_t * a;
        } else {
            s = stop_dist;
            v = 0.0;
            cur_a = 0.0;
        }
    }
    const double cur_s = std::min(s, len);
    const auto &geometry_state =
        is_fast_sample ? geometry.FastState(cur_s) : geometry.State(cur_s);
    states.push_back(MotionState{.xy = geometry_state.xy,
                                 .h = geometry_state.h,
                                 .k = geometry_state.k,
                                 .ref_k = geometry_state.ref_k,
                                 .t = duration,
                                 .v = v,
                                 .a = cur_a,
                                 .accumulated_s = geometry_state.accumulated_s,
                                 .s = cur_s,
                                 .l = geometry_state.l});
    return states;
}

void EstimateDerivatives(absl::Span<const MotionState> const_interval_states,
                         double dt,
                         MotionState *state) {
    if (!XCHECK(!const_interval_states.empty())) {
        return;
    }
    int size = static_cast<int>(const_interval_states.size());
    const double cur_t = state->t;
    ptrdiff_t nearest_idx_ptrdiff =
        std::lower_bound(
            const_interval_states.begin(), const_interval_states.end(), cur_t,
            [](const MotionState &target, double t) { return target.t < t; }) -
        const_interval_states.begin();
    int nearest_idx = static_cast<int>(nearest_idx_ptrdiff);
    if (nearest_idx == const_interval_states.size()) {
        nearest_idx--;
    }
    const auto &cur_state = const_interval_states[static_cast<size_t>(nearest_idx)];
    int n_idx = std::min(nearest_idx + 1, size - 1);
    const auto &n_state = const_interval_states[static_cast<size_t>(n_idx)];
    int nn_idx = std::min(nearest_idx + 2, size - 1);
    const auto &nn_state = const_interval_states[static_cast<size_t>(nn_idx)];
    int p_idx = std::max(nearest_idx - 1, 0);
    const auto &p_state = const_interval_states[static_cast<size_t>(p_idx)];
    int pp_idx = std::max(nearest_idx - 2, 0);
    const auto &pp_state = const_interval_states[static_cast<size_t>(pp_idx)];
    state->dl =
        (n_state.l - p_state.l) / (static_cast<double>(2) * dt);
    state->ddl =
        (n_state.l + p_state.l - (static_cast<double>(2) * cur_state.l)) /
        (dt * dt);
    state->dddl =
        (nn_state.l - (static_cast<double>(2) * n_state.l) +
         (static_cast<double>(2) * p_state.l) - pp_state.l) /
        (static_cast<double>(2) * dt * dt * dt);
}

}  // namespace
SampledMotionFormStates ConstAccelMotion::SampleStates() const {
    const double const_step_dt = prediction::kPredictionTimeStep *
                                 static_cast<double>(MotionForm::kConstTimeIntervalSampleStep);
    SampledMotionFormStates res;
    res.const_interval_states =
        SampleWithChoice<true>(*geometry_, const_step_dt, duration_, init_v_,
                               a_, stop_time_, stop_distance_);

    int desired_equal_dist_steps =
        static_cast<int>(duration_ / kDesireEqualTimeInterval) + 1;
    desired_equal_dist_steps = boost::algorithm::clamp<int>(
        desired_equal_dist_steps, kMinEqualTimeIntervalSampleStep,
        kMaxEqualTimeIntervalSampleStep);
    const double equal_time_divisor = static_cast<double>(desired_equal_dist_steps - 1);
    const double equal_time_dt = duration_ / equal_time_divisor;
    if (duration_ < kNeedPreciseSamplingDuration) {
        res.equal_interval_states =
            SampleWithChoice<false>(*geometry_, equal_time_dt, duration_,
                                    init_v_, a_, stop_time_, stop_distance_);
    } else {
        res.equal_interval_states =
            SampleWithChoice<true>(*geometry_, equal_time_dt, duration_,
                                   init_v_, a_, stop_time_, stop_distance_);
    }

    if (res.const_interval_states.size() > res.equal_interval_states.size()) {
        for (auto &state : res.equal_interval_states) {
            EstimateDerivatives(res.const_interval_states, const_step_dt,
                                &state);
        }
    } else {
        for (auto &state : res.equal_interval_states) {
            EstimateDerivatives(res.equal_interval_states, equal_time_dt,
                                &state);
        }
    }
    return res;
}

std::vector<MotionState> ConstAccelMotion::SampleEqualIntervalStates() const {
    int desired_equal_dist_steps =
        static_cast<int>(duration_ / kDesireEqualTimeInterval) + 1;
    desired_equal_dist_steps = boost::algorithm::clamp<int>(
        desired_equal_dist_steps, kMinEqualTimeIntervalSampleStep,
        kMaxEqualTimeIntervalSampleStep);
    const double equal_time_divisor = static_cast<double>(desired_equal_dist_steps - 1);
    const double equal_time_dt = duration_ / equal_time_divisor;
    if (duration_ < kNeedPreciseSamplingDuration) {
        return SampleWithChoice<false>(*geometry_, equal_time_dt, duration_,
                                       init_v_, a_, stop_time_, stop_distance_);
    } else {
        return SampleWithChoice<true>(*geometry_, equal_time_dt, duration_,
                                      init_v_, a_, stop_time_, stop_distance_);
    }
}
ConstAccelMotion::ConstAccelMotion(double init_v,
                                   double init_a,
                                   const GeometryForm *geometry)
    : init_v_(init_v),
      a_(init_a),
      stop_time_(std::numeric_limits<double>::max()),
      stop_distance_(std::numeric_limits<double>::max()),
      geometry_(geometry) {
    if ((std::fabs(a_) < kZeroAccEpsilon) && (init_v < kZeroSpeedEpsilon)) {
        a_ = -kZeroAccEpsilon;
    }

    if (a_ < 0.0) {
        const double inv_a = 1.0 / a_;
        stop_distance_ = std::fabs(0.5 * init_v_ * init_v_ * inv_a);
        if (stop_distance_ < (geometry_->length() + kPositionEpsilon)) {
            duration_ = kTrajectoryTimeStep * static_cast<double>(kInitializerTrajectorySteps);
            stop_time_ = std::fabs(init_v_ * inv_a);
            return;
        }
    }

    const auto roots = QuadraticRoot(0.5 * a_, init_v_, -geometry_->length());
    bool found_root = false;
    for (auto root : roots) {
        if (root > 0.0) {
            duration_ = root;
            found_root = true;
            break;
        }
    }
    XCHECK(found_root);
}

ConstAccelMotion::ConstAccelMotion(std::pair<double, double> v_pair,
                                   const GeometryForm *geometry)
    : init_v_(v_pair.first),
      stop_time_(std::numeric_limits<double>::max()),
      stop_distance_(std::numeric_limits<double>::max()),
      geometry_(geometry) {
    XCHECK_GE(v_pair.second, 0.0);
    XCHECK_GE(v_pair.first, 0.0);
    XCHECK(!((v_pair.first == 0) && (v_pair.second == 0.0)));

    a_ = (Sqr(v_pair.second) - Sqr(init_v_)) * 0.5 / geometry_->length();
    duration_ = geometry_->length() * 2.0 / (init_v_ + v_pair.second);
}

MotionState ConstAccelMotion::GetStartMotionState() const { return State(0.0); }

MotionState ConstAccelMotion::GetEndMotionState() const {
    return State(duration_);
}

MotionState ConstAccelMotion::State(double t) const {
    double s = 0.0;

    if (t < stop_time_) {
        s = (init_v_ + (0.5 * a_ * t)) * t;
        const auto &geo_state = geometry()->State(s);
        return MotionState{.xy = geo_state.xy,
                           .h = geo_state.h,
                           .k = geo_state.k,
                           .ref_k = geo_state.ref_k,
                           .t = t,
                           .v = init_v_ + (a_ * t),
                           .a = a_,
                           .accumulated_s = geo_state.accumulated_s,
                           .s = s,
                           .l = geo_state.l};
    }

    s = stop_distance_;
    const auto &geo_state = geometry()->State(s);
    return MotionState{.xy = geo_state.xy,
                       .h = geo_state.h,
                       .k = geo_state.k,
                       .ref_k = geo_state.ref_k,
                       .t = t,
                       .v = 0.0,
                       .a = 0.0,
                       .accumulated_s = geo_state.accumulated_s,
                       .s = s,
                       .l = geo_state.l};
}
SampledMotionFormStates StationaryMotion::SampleStates() const {
    const double const_step_dt = prediction::kPredictionTimeStep *
                                 static_cast<double>(MotionForm::kConstTimeIntervalSampleStep);
    SampledMotionFormStates res;
    res.const_interval_states = Sample(const_step_dt);

    int desired_equal_dist_steps =
        static_cast<int>(duration_ / kDesireEqualTimeInterval) + 1;
    desired_equal_dist_steps = boost::algorithm::clamp<int>(
        desired_equal_dist_steps, kMinEqualTimeIntervalSampleStep,
        kMaxEqualTimeIntervalSampleStep);
    const double equal_time_divisor = static_cast<double>(desired_equal_dist_steps - 1);
    const double equal_time_dt = duration_ / equal_time_divisor;
    res.equal_interval_states = Sample(equal_time_dt);
    return res;
}
std::vector<MotionState> StationaryMotion::SampleEqualIntervalStates() const {
    int desired_equal_dist_steps =
        static_cast<int>(duration_ / kDesireEqualTimeInterval) + 1;
    desired_equal_dist_steps = boost::algorithm::clamp<int>(
        desired_equal_dist_steps, kMinEqualTimeIntervalSampleStep,
        kMaxEqualTimeIntervalSampleStep);
    const double equal_time_divisor = static_cast<double>(desired_equal_dist_steps - 1);
    const double equal_time_dt = duration_ / equal_time_divisor;
    return Sample(equal_time_dt);
}

std::vector<MotionState> StationaryMotion::Sample(double d_t) const {
    std::vector<MotionState> states;
    const int reserve_count = CeilToInt(duration() / d_t) + 1;
    states.reserve(static_cast<size_t>(reserve_count));
    GeometryState geo_state = geometry_->State(0.0);
    MotionState state{.xy = geo_state.xy,
                      .h = geo_state.h,
                      .k = geo_state.k,
                      .ref_k = geo_state.ref_k,
                      .t = 0.0,
                      .v = 0.0,
                      .a = 0.0,
                      .accumulated_s = geo_state.accumulated_s,
                      .s = 0.0,
                      .l = geo_state.l};
    double t = 0.0;
    const double lookforward = 0.9 * d_t;
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (((t + lookforward) < duration()) && loop_guard) {
        state.t = t;
        states.push_back(state);
        t += d_t;
    }
    state.t = duration();
    states.push_back(state);
    return states;
}

MotionState StationaryMotion::GetStartMotionState() const { return State(0.0); }

MotionState StationaryMotion::GetEndMotionState() const {
    return State(duration_);
}

MotionState StationaryMotion::State(double t) const {
    GeometryState geom_state = geometry_->State(0.0);
    return MotionState{.xy = geom_state.xy,
                       .h = geom_state.h,
                       .k = geom_state.k,
                       .ref_k = geom_state.ref_k,
                       .t = t,
                       .v = 0.0,
                       .a = 0.0,
                       .accumulated_s = geom_state.accumulated_s,
                       .s = 0.0,
                       .l = geom_state.l};
}

}  // namespace planning
}  // namespace pnc_x
