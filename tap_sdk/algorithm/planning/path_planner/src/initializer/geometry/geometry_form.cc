

#include "initializer/geometry/geometry_form.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

#include "common/throw_check.h"
#include "math/util.h"
#include "util/loop_guard.h"

namespace pnc_x {
namespace planning {
using pnc_x::Lerp;
using pnc_x::LerpAngle;
namespace {
constexpr double kEpsilon = 1e-4;
constexpr double kDenselySampleSResolution = 0.2;
const double kInvDenselySampleSResolution = 1.0 / kDenselySampleSResolution;
std::pair<int, double> FindLerpInfo(double s,
                                    absl::Span<const double> vec_s,
                                    int start,
                                    int end) {
    if (!XCHECK_GE(vec_s.size(), 2)) {
        return std::make_pair(0, 0);
    }
    auto it =
        std::lower_bound(vec_s.begin() + start, vec_s.begin() + end + 1, s);

    if (it == vec_s.begin()) {
        return std::make_pair(0, s - vec_s.front());
    }

    if (it == vec_s.end()) {
        return std::make_pair(vec_s.size() - 2, s - vec_s[vec_s.size() - 2]);
    }
    return std::make_pair(std::distance(vec_s.begin(), it - 1), s - *(it - 1));
}
std::vector<GeometryState> SampleWithOrderedS(
    absl::Span<const double> vec_s,
    absl::Span<const GeometryState> states,
    absl::Span<const double> states_s) {
    XCHECK(!vec_s.empty());
    std::vector<GeometryState> dense_states;
    dense_states.resize(vec_s.size());
    int index = 0;
    for (int i = 0; i < vec_s.size(); i++) {
        const auto &cur_s = vec_s[i];
        auto loop_guard = DEFAULT_LOOP_GUARD();
        while ((cur_s > states_s[index + 1] + kEpsilon) && loop_guard) {
            ++index;
        }
        const auto factor =
            (cur_s - states_s[index]) / (states_s[index + 1] - states_s[index]);
        dense_states[i] = {
            .xy = Lerp(states[index].xy, states[index + 1].xy, factor),
            .h = NormalizeAngle(
                LerpAngle(states[index].h, states[index + 1].h, factor)),
            .k = Lerp(states[index].k, states[index + 1].k, factor),
            .ref_k = Lerp(states[index].ref_k, states[index + 1].ref_k, factor),
            .accumulated_s = Lerp(states[index].accumulated_s,
                                  states[index + 1].accumulated_s, factor),
            .l = Lerp(states[index].l, states[index + 1].l, factor)};
    }

    return dense_states;
}
}  // namespace

StraightLineGeometry::StraightLineGeometry(const Vec2d &start, const Vec2d &end)
    : start_(start), end_(end) {
    const Vec2d v = end - start;
    unit_ = v.Unit();
    densely_discretized_states_ = Sample(kDenselySampleSResolution);
}

double StraightLineGeometry::length() const {
    return unit_.Dot((end_ - start_));
}

GeometryState StraightLineGeometry::State(double delta_s) const {
    return {.xy = start_ + unit_ * delta_s, .h = unit_.FastAngle(), .k = 0.0};
}

const GeometryState &StraightLineGeometry::FastState(double delta_s) const {
    const int idx =
        std::min<int>(RoundToInt(delta_s * kInvDenselySampleSResolution),
                      densely_discretized_states_.size() - 1);
    return densely_discretized_states_[idx];
}

std::vector<GeometryState> StraightLineGeometry::Sample(double delta_s) const {
    const double heading = unit_.FastAngle();
    const double len = length();

    std::vector<GeometryState> states;
    states.reserve(CeilToInt(len / delta_s) + 1);

    double s = 0.0;
    const double lookforward = 0.9 * delta_s;
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (((s + lookforward) < len) && loop_guard) {
        states.push_back({.xy = start_ + unit_ * s, .h = heading, .k = 0.0});
        s += delta_s;
    }

    states.push_back({.xy = end_, .h = heading, .k = 0.0});

    return states;
}

PiecewiseLinearGeometry::PiecewiseLinearGeometry(
    absl::Span<const GeometryState> states)
    : states_(std::vector<GeometryState>(states.begin(), states.end())) {
    if (!XCHECK_GT(states.size(), 1)) {
        return;
    }
    vec_s_.clear();
    vec_s_.reserve(states.size());
    double curve_s = 0.0;
    auto prev_xy = states.front().xy;
    for (int i = 0; i < states.size(); ++i) {
        const auto &state = states[i];
        if (i != 0) {
            curve_s = curve_s + state.xy.DistanceTo(prev_xy);
        }
        vec_s_.push_back(curve_s);
        prev_xy = state.xy;
    }

    length_ = vec_s_.back();
    densely_discretized_states_ = Sample(kDenselySampleSResolution);
    dense_state_size_ = densely_discretized_states_.size();
    XCHECK_GT(dense_state_size_, 0);
}

std::vector<GeometryState> PiecewiseLinearGeometry::Sample(
    double delta_s) const {
    const int reserved_slots = CeilToInt(length_ / delta_s) + 1;

    double s = 0.0;
    const double lookforward = 0.9 * delta_s;
    std::vector<double> queries;
    queries.reserve(reserved_slots);
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (((s + lookforward) < length_) && loop_guard) {
        queries.push_back(s);
        s += delta_s;
    }
    queries.push_back(length_);
    return SampleWithOrderedS(queries, states_, vec_s_);
}

const GeometryState &PiecewiseLinearGeometry::FastState(double delta_s) const {
    const int idx = std::min(RoundToInt(delta_s * kInvDenselySampleSResolution),
                             dense_state_size_ - 1);
    return densely_discretized_states_[idx];
}

GeometryState PiecewiseLinearGeometry::State(double s) const {
    auto lerp_info = FindLerpInfo(s, vec_s_, 0, vec_s_.size() - 1);
    int index = lerp_info.first;
    double dist = lerp_info.second;
    double factor = dist / (vec_s_[index + 1] - vec_s_[index]);
    GeometryState state;
    state.xy = Lerp(states_[index].xy, states_[index + 1].xy, factor);
    state.h = NormalizeAngle(
        LerpAngle(states_[index].h, states_[index + 1].h, factor));
    state.k = Lerp(states_[index].k, states_[index + 1].k, factor);
    state.ref_k = Lerp(states_[index].ref_k, states_[index + 1].ref_k, factor);
    state.accumulated_s = Lerp(states_[index].accumulated_s,
                               states_[index + 1].accumulated_s, factor);
    state.l = Lerp(states_[index].l, states_[index + 1].l, factor);
    return state;
}

}  // namespace planning
}  // namespace pnc_x
