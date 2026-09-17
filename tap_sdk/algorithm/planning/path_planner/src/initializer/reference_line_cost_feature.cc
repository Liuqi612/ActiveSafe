

#include <array>
#include <cmath>

#include "initializer/geometry/geometry_state.h"
#include "initializer/reference_line_cost_feature.h"
#include "math/geometry/box2d.h"
#include "math/util.h"
#include "math/vec.h"
#include "common/log.h"

namespace pnc_x {
namespace planning {
namespace {

constexpr double kLongitudinalHysterisis = 0.5;

std::array<double, 5> ComputeLateralRatio(const PathSlBoundary &path_sl,
                                          const GeometryState &state) {
    const auto s = state.accumulated_s;
    const auto l = state.l;
    auto boundary = path_sl.QueryBoundaryL(s);
    const auto l_right = boundary.first;
    const auto l_left = boundary.second;
    auto target_boundary = path_sl.QueryTargetBoundaryL(s);
    const auto l_target_right = target_boundary.first;
    const auto l_target_left = target_boundary.second;
    const auto l_center = path_sl.QueryReferenceCenterL(s);
    const auto l_diff_center = l - l_center;
    const auto l_left_ratio =
        std::max(0.0, l_diff_center / (l_left - l_center));
    const auto l_right_ratio =
        std::max(0.0, l_diff_center / (l_right - l_center));
    const auto l_target_left_ratio =
        std::max(0.0, l_diff_center / (l_target_left - l_center));
    const auto l_target_right_ratio =
        std::max(0.0, l_diff_center / (l_target_right - l_center));
    return {l_right_ratio, l_left_ratio, l_target_right_ratio,
            l_target_left_ratio, l_diff_center};
}

}  // namespace

void RefLineStationaryObjectFeatureCost::ComputeCost(
    const GeometryEdgeInfo &edge_info, absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 1)) {
        return;
    }
    cost[0] = 0.0;
    double sum_cost = 0.0;
    const auto &sdc_states = edge_info.states;
    for (int i = 0, n = sdc_states.size() - 1; i < n; i += sample_step_) {
        const auto &sdc_state = sdc_states[i];
        Vec2d sum = Vec2d::Zero();
        for (const auto &obj_state : stationary_obj_states_) {
            const auto &obj_box = obj_state.box;
            const auto r_vec = obj_box.center() - sdc_state.xy;
            const double r_len = r_vec.Length();
            sum += 1.0 / Cube(r_len) * r_vec;
        }
        sum_cost += sum.Length();
    }
    cost[0] = sum_cost / round(sdc_states.size() / sample_step_);
}

void RefLineProgressFeatureCost::ComputeCost(const GeometryEdgeInfo &edge_info,
                                             absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 2)) {
        return;
    }

    cost[0] = cost[1] = 0.0;
    const auto &states = edge_info.states;

    if (edge_info.terminating) {
        const auto &final_state = states.back();
        const double long_diff =
            std::fabs(geom_graph_max_accum_s_ - final_state.accumulated_s);
        cost[0] = long_diff > kLongitudinalHysterisis ? long_diff : 0.0;
        const auto l_center =
            path_sl_boundary_->QueryReferenceCenterL(final_state.accumulated_s);
        cost[1] = std::fabs(l_center - final_state.l);
    }
}

void RefLinePathBoundaryFeatureCost::ComputeCost(
    const GeometryEdgeInfo &edge_info, absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 3)) {
        return;
    }
    cost[0] = cost[1] = cost[2] = 0.0;

    constexpr double kFavorLeftSideCostFactor = 1.2;
    const auto &states = edge_info.states;

    for (const auto &state : states) {
        auto lateral_ratios = ComputeLateralRatio(*path_sl_boundary_, state);
        double l_right_ratio = lateral_ratios[0];
        double l_left_ratio = lateral_ratios[1];
        double l_target_right_ratio = lateral_ratios[2];
        double l_target_left_ratio = lateral_ratios[3];
        // double l_diff_center = lateral_ratios[4]; // unused

        cost[1] += kFavorLeftSideCostFactor * Sqr(l_target_right_ratio) +
                   Sqr(l_target_left_ratio);

        cost[2] +=
            kFavorLeftSideCostFactor * Sqr(l_right_ratio) + Sqr(l_left_ratio);
    }

    cost[1] = cost[1] / states.size();
    cost[2] = cost[2] / states.size();
}

void RefLineCurvatureFeatureCost::ComputeCost(const GeometryEdgeInfo &edge_info,
                                              absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 1)) {
        return;
    }

    cost[0] = 0.0;
    double cost_sum = 0.0;
    const auto &states = edge_info.states;

    for (const auto &state : states) {
        cost_sum += Sqr(state.k * inv_relaxed_center_max_curvature_);
    }
    cost[0] = cost_sum / states.size();
}

}  // namespace planning
}  // namespace pnc_x
