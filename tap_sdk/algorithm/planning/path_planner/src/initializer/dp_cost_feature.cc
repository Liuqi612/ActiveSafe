

#include "initializer/dp_cost_feature.h"

#include <array>
#include <boost/algorithm/clamp.hpp>
#include <cmath>
#include <ostream>
#include <utility>

#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include "common/log.h"

#include "initializer/geometry/geometry_form.h"
#include "initializer/geometry/geometry_state.h"
#include "initializer/motion_form.h"
#include "initializer/motion_state.h"
#include "math/frenet_common.h"
#include "math/geometry/box2d.h"
#include "math/geometry/util.h"
#include "math/util.h"
#include "math/vec.h"
#include "object/spacetime_object_state.h"
#include "object/spacetime_object_trajectory.h"
#include "plan/planner_defs.h"
#include "plan/planner_flags.h"
#include "prediction/prediction_defs.h"
#include "pncx_trajectory_point.pb.h"
#include "util/status_macros.h"

namespace pnc_x {
namespace planning {
namespace {

constexpr double kIgnoreLateralAccelSpeedLimit = 2.0;
constexpr double kLateralAccelHardLimit = 2.5;
constexpr double kLateralAccelSoftLimit = 1.0;
constexpr double kInvLateralAccelSoftLimit = 1.0 / kLateralAccelSoftLimit;
constexpr double kIgnoreLateralJerkSpeedLimit = 3.0;
constexpr double kLateralJerkLimit = 2.0;
constexpr double kInvLateralJerkLimit = 1.0 / kLateralJerkLimit;

constexpr double kCurvatureRegularizer = 0.1;
constexpr double kInvCurvatureRegularizer = 1.0 / kCurvatureRegularizer;

constexpr double kRefSpeedRegularizer = 3.0;
constexpr double kInvRefSpeedRegularizer = 1.0 / kRefSpeedRegularizer;

constexpr std::array<double, 11> kInterpT = {0.0, 0.9, 1.9, 2.9, 3.9, 4.9,
                                             5.9, 6.9, 7.9, 8.9, 9.9};
constexpr int kGroupLen = 10;
constexpr int kMaxGroupSize = prediction::kPredictionPointNum / kGroupLen;
constexpr double kHysteresis = 2.0;
constexpr double kEnterLaneLateralDistanceThreshold = 1.0;
constexpr double kInvEnterLaneLateralDistanceThreshold =
    1 / kEnterLaneLateralDistanceThreshold;
constexpr double kLeadingObjectLateralOffsetWeight = 10.0;

const PiecewiseLinearFunction<double> kCurvatureVelocityPlf(
    {1.0, 2.0, 3.0, 4.0, 5.0}, {0.05, 0.1, 0.2, 0.2, 1.0});

enum TransformType {
    kL1Norm = 0,
    kL2Norm = 1,
};

template <TransformType type>
double Transform(double val) {
    switch (type) {
        case kL1Norm:
            return std::fabs(val);
        case kL2Norm:
            return Sqr(val);
    }
}

inline void SetZeroCost(absl::Span<double> cost) {
    for (auto &val : cost) val = 0.0;
}

std::array<double, 5> CalculatePathSlCostRatio(double s,
                                               double l,
                                               const PathSlBoundary &path_sl,
                                               double sdc_half_width) {
    constexpr double kEpsilon = 1e-8;
    const double ref_center_l = path_sl.QueryReferenceCenterL(s);
    const double ref_l_ratio = boost::algorithm::clamp(
        (l - ref_center_l) * (1.0 / kDefaultHalfLaneWidth), -1.0, 1.0);

    const auto target_boundary_pair = path_sl.QueryTargetBoundaryL(s);
    const double l_target_right = target_boundary_pair.first;
    const double l_target_left = target_boundary_pair.second;
    const double target_right_border = sdc_half_width + l_target_right;
    const double target_left_border = l_target_left - sdc_half_width;
    const double target_right_ratio = boost::algorithm::clamp(
        (ref_center_l - l) / (ref_center_l - target_right_border + kEpsilon),
        0.0, 1.0);
    const double target_left_ratio = boost::algorithm::clamp(
        (l - ref_center_l) / (target_left_border - ref_center_l + kEpsilon),
        0.0, 1.0);

    const auto boundary_pair = path_sl.QueryBoundaryL(s);
    const double l_right = boundary_pair.first;
    const double l_left = boundary_pair.second;
    const double right_border = sdc_half_width + l_right;
    const double left_border = l_left - sdc_half_width;
    const double right_ratio = boost::algorithm::clamp(
        (ref_center_l - l) / (ref_center_l - right_border + kEpsilon), 0.0,
        1.0);
    const double left_ratio = boost::algorithm::clamp(
        (l - ref_center_l) / (left_border - ref_center_l + kEpsilon), 0.0, 1.0);

    return {ref_l_ratio, target_right_ratio, target_left_ratio, right_ratio,
            left_ratio};
}

absl::StatusOr<double> FilterAndGetBoxMinS(const DrivePassage &passage,
                                           const Box2d &box) {
    ASSIGN_OR_RETURN(const auto frenet_box, passage.QueryFrenetBoxAt(box),
                     absl::NotFoundError(
                         "Cannot project the object box onto drive passage."));
    ASSIGN_OR_RETURN(const auto passage_tangent,
                     passage.QueryTangentAtS(frenet_box.center_s()),
                     absl::NotFoundError(
                         "Cannot find passage tangent near the object box."));

    if (std::abs(NormalizeAngle(passage_tangent.FastAngle() - box.heading())) >
        M_PI_2) {
        return absl::NotFoundError(
            "Oncoming object ignored for leading object.");
    }

    return frenet_box.s_min;
}

PiecewiseLinearFunction<double> GetTrajTimeAccumulatedSPlf(
    const DrivePassage &drive_passage,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const std::vector<std::string> &leading_trajs) {
    std::vector<double> ty(kInterpT.size(),
                           std::numeric_limits<double>::infinity());
    for (const auto &object_id : leading_trajs) {
        absl::Span<const SpacetimeObjectTrajectory *const>
            leading_object_trajectorys =
                st_traj_mgr.FindTrajectoriesByObjectId(object_id);
        if (leading_object_trajectorys.empty()) {
            continue;
        }
        const auto &states = leading_object_trajectorys[0]->states();
        const auto box_min_s_or =
            FilterAndGetBoxMinS(drive_passage, states.front().box);
        if (box_min_s_or.ok()) {
            ty[0] = std::min(ty[0], *box_min_s_or);
        }

        for (int i = 1; i <= kMaxGroupSize; ++i) {
            const int state_idx = (i * kGroupLen) - 1;
            if (state_idx >= states.size()) break;

            ASSIGN_OR_CONTINUE(
                const auto box_min_s,
                FilterAndGetBoxMinS(drive_passage, states[static_cast<std::size_t>(state_idx)].box));
            ty[static_cast<std::size_t>(i)] = std::min(ty[static_cast<std::size_t>(i)], box_min_s);
        }
    }
    return PiecewiseLinearFunction<double>({kInterpT.begin(), kInterpT.end()},
                                           std::move(ty));
}

}  // namespace

void DpAccelerationFeatureCost::ComputeCost(const MotionEdgeInfo &edge_info,
                                            absl::Span<double> cost) const {
    const auto get_normalize_a = [this](double a) {
        return (a < 0.0) ? max_decel_constraint_ : max_accel_constraint_;
    };
    if (!XCHECK_EQ(cost.size(), 1)) {
        return;
    }
    const auto &states = edge_info.equal_interval_states;
    if (!XCHECK_GT(states.size(), 1)) {
        return;
    }
    cost[0] = 0.0;
    const double borrow_factor =
        (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type_) ? 0.4
                                                                      : 1.0;
    const std::size_t states_size = states.size();
    for (std::size_t i = 0; i < states_size; ++i) {
        const double cur_cost = Transform<TransformType::kL2Norm>(
            states[i].a / get_normalize_a(states[i].a));
        const double sign_factor = (states[i].a < 0.0) ? 4.0 : 1.0;
        const double factor =
            ((i == 0) || (i == (states.size() - 1))) ? 1.0 : 2.0;
        cost[0] += (sign_factor * factor * cur_cost);
    }

    const double dt = states[1].t - states[0].t;
    cost[0] = 0.5 * dt * cost[0] * borrow_factor;
}

void DpLaneBoundaryFeatureCost::ComputeCost(const MotionEdgeInfo &edge_info,
                                            absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 3)) {
        return;
    }
    SetZeroCost(cost);
    const auto &states = edge_info.equal_interval_states;
    if (!XCHECK_GT(states.size(), 1)) {
        return;
    }
    const double center_factor =
        (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type_) ? 0.15
                                                                      : 1.0;
    const double inner_factor =
        (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type_) ? 0.25
                                                                      : 1.0;
    const double outer_factor =
        (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type_) ? 0.35
                                                                      : 1.0;
    const std::vector<double> borrow_factor = {center_factor, inner_factor,
                                               outer_factor};
    const std::size_t states_size = states.size();
    for (std::size_t i = 0; i < states_size; ++i) {
        const auto l2ratios = CalculatePathSlCostRatio(
            states[i].accumulated_s, states[i].l, *path_sl_, sdc_half_width_);
        const double ref_l_ratio = l2ratios[0];
        const double cur_cost0 = Transform<TransformType::kL2Norm>(ref_l_ratio);
        const double target_right_ratio = l2ratios[1];
        const double target_left_ratio = l2ratios[2];
        const double cur_cost1 =
            Transform<TransformType::kL2Norm>(target_right_ratio) +
            Transform<TransformType::kL2Norm>(target_left_ratio);
        const double right_ratio = l2ratios[3];
        const double left_ratio = l2ratios[4];
        const double cur_cost2 =
            Transform<TransformType::kL2Norm>(right_ratio) +
            Transform<TransformType::kL2Norm>(left_ratio);
        const double factor =
            ((i == 0) || (i == (states.size() - 1))) ? 1.0 : 2.0;
        cost[0] += (factor * cur_cost0);
        cost[1] += (factor * cur_cost1);
        cost[2] += (factor * cur_cost2);
    }
    const double dt = states[1].t - states[0].t;
    for (int i = 0; i < 3; ++i) {
        cost[static_cast<std::size_t>(i)] =
            0.5 * dt * cost[static_cast<std::size_t>(i)] *
            borrow_factor[static_cast<std::size_t>(i)];
    }
}

void DpCurvatureFeatureCost::ComputeCost(const MotionEdgeInfo &edge_info,
                                         absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 1)) {
        return;
    }
    cost[0] = 0.0;
    const auto &states = edge_info.equal_interval_states;

    const std::size_t states_size = states.size();
    for (std::size_t i = 0; i < states_size; ++i) {
        const double relax_factor = kCurvatureVelocityPlf(states[i].v);
        const double cur_cost =
            Transform<TransformType::kL2Norm>((states[i].k - states[i].ref_k) *
                                              kInvCurvatureRegularizer) *
            relax_factor;
        const double factor =
            ((i == 0) || (i == (states.size() - 1))) ? 1.0 : 2.0;
        cost[0] += (factor * cur_cost);
    }

    const double dt = states[1].t - states[0].t;
    cost[0] = 0.5 * dt * cost[0];
}

void DpLateralAccelerationFeatureCost::ComputeCost(
    const MotionEdgeInfo &edge_info, absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 3)) {
        return;
    }
    SetZeroCost(cost);
    const auto &states = edge_info.equal_interval_states;
    if (!XCHECK_GT(states.size(), 1)) {
        return;
    }
    const double duration = states.back().t - states.front().t;
    const double dt = states[1].t - states[0].t;

    const double soft_factor =
        (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type_) ? 4.0
                                                                      : 1.0;
    const double jerk_factor =
        (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type_) ? 4.0
                                                                      : 1.0;
    const std::vector<double> borrow_factor = {1.0, soft_factor, jerk_factor};

    const std::size_t states_size = static_cast<std::size_t>(states.size());
    for (std::size_t i = 0; i < states_size; ++i) {
        if (states[i].v < kIgnoreLateralAccelSpeedLimit) continue;

        const double abs_lat_acc =
            std::abs((states[i].k - states[i].ref_k) * Sqr(states[i].v));
        if (abs_lat_acc > kLateralAccelHardLimit) {
            cost[0] = 1.0 * duration;
        }
        double cur_lat_cost = 0.0;
        if (abs_lat_acc > kLateralAccelSoftLimit) {
            cur_lat_cost = Transform<TransformType::kL2Norm>(
                std::max(0.0, (abs_lat_acc * kInvLateralAccelSoftLimit) - 1.0));
        }

        const double factor =
            ((i == 0) || (i == (states.size() - 1))) ? 1.0 : 2.0;
        cost[1] += (factor * cur_lat_cost);
    }
    cost[1] = 0.5 * dt * cost[1] * borrow_factor[1];

    if (!is_lane_change_) {
        for (std::size_t i = 0; i < states_size; ++i) {
            const double dddl =
                states[i].dddl.has_value() ? (*states[i].dddl) : 0;
            const double jerk_ratio =
                (states[i].v < kIgnoreLateralJerkSpeedLimit)
                    ? 0.0
                    : boost::algorithm::clamp(dddl * kInvLateralJerkLimit, -1.0,
                                              1.0);
            const double cur_cost =
                Transform<TransformType::kL2Norm>(jerk_ratio);

            const double factor =
                ((i == 0) || (i == (states.size() - 1))) ? 1.0 : 2.0;
            cost[2] += (factor * cur_cost);
        }
        cost[2] = 0.5 * dt * cost[2] * borrow_factor[2];
    }
}

void DpStopConstraintFeatureCost::ComputeCost(const MotionEdgeInfo &edge_info,
                                              absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 1)) {
        return;
    }
    const auto &states = edge_info.equal_interval_states;
    if (!XCHECK_GT(states.size(), 1)) {
        return;
    }
    const double last_s = states.back().accumulated_s;
    cost[0] = std::max(0.0, last_s - nearest_stop_s_);
}

void DpRefSpeedFeatureCost::ComputeCost(const MotionEdgeInfo &edge_info,
                                        absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 3)) {
        return;
    }
    SetZeroCost(cost);

    const auto &states = edge_info.equal_interval_states;
    if (!XCHECK_GT(states.size(), 1)) {
        return;
    }

    const double exceed_limit_factor =
        (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type_) ? 0.4
                                                                      : 1.0;
    const double exceed_ref_factor =
        (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type_) ? 0.4
                                                                      : 1.0;
    const double below_ref_factor =
        (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type_) ? 8.0
                                                                      : 1.0;
    const std::vector<double> borrow_factor = {
        exceed_limit_factor, exceed_ref_factor, below_ref_factor};

    const std::size_t states_size = states.size();
    for (std::size_t i = 0; i < states_size; ++i) {
        const double t = states[i].t + edge_info.start_t;
        const double accumulated_s = states[i].accumulated_s;
        const auto speed_pair =
            ref_speed_table_->LookUpRefSpeed(t, accumulated_s);
        const double v_limit = speed_pair.first;
        const double v_ref = speed_pair.second;
        const double v = states[i].v;

        const double factor =
            ((i == 0) || (i == (states.size() - 1))) ? 1.0 : 2.0;

        cost[0] += factor * Transform<TransformType::kL2Norm>(
                                (v > v_limit) ? (v - v_limit) : 0.0);

        const double exceed_speed = std::max(v - v_ref, 0.0);
        cost[1] +=
            factor * Transform<TransformType::kL2Norm>(boost::algorithm::clamp(
                         exceed_speed * kInvRefSpeedRegularizer, 0.0, 1.0));

        const double below_speed = std::max(v_ref - v, 0.0);
        cost[2] +=
            factor * Transform<TransformType::kL2Norm>(boost::algorithm::clamp(
                         below_speed * kInvRefSpeedRegularizer, 0.0, 1.0));
    }
    const double dt = states[1].t - states[0].t;
    for (int i = 0; i < 3; ++i) {
        cost[static_cast<std::size_t>(i)] =
            0.5 * dt * cost[static_cast<std::size_t>(i)] *
            borrow_factor[static_cast<std::size_t>(i)];
    }
}

DpDynamicCollisionFeatureCost::DpDynamicCollisionFeatureCost(
    const CollisionChecker *collision_checker)
    : FeatureCost("dp_dynamic_collision"),
      cc_(XCHECK_NOTNULL(collision_checker)) {}

void DpDynamicCollisionFeatureCost::ComputeCost(const MotionEdgeInfo &edge_info,
                                                absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 1)) {
        return;
    }
    CollisionInfo collision_info;
    const auto start_time = edge_info.start_t;
    cc_->CheckCollisionWithTrajectories(
        start_time, edge_info.const_interval_states, {}, &collision_info);
    if (collision_info.collision_objects.empty()) {
        cost[0] = 0.0;
    } else {
        cost[0] = 1.0;
    }
}

IgnoreTrajMap DpDynamicCollisionFeatureCost::ComputeInteractiveCost(
    const MotionEdgeInfo &edge_info,
    const IgnoreTrajMap &ignored_trajs,
    absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 1)) {
        return ignored_trajs;
    }
    CollisionInfo collision_info;
    const auto start_time = edge_info.start_t;
    cc_->CheckCollisionWithTrajectories(start_time,
                                        edge_info.const_interval_states,
                                        ignored_trajs, &collision_info);
    cost[0] = 0.0;
    auto new_ignored_trajs = ignored_trajs;
    for (const auto &collision_obj : collision_info.collision_objects) {
        if (collision_obj.collision_configuration.has_value()) {
            if (*collision_obj.collision_configuration !=
                CollisionConfiguration::BACK) {
                cost[0] = 1.0;
            } else {
                new_ignored_trajs[collision_obj.traj->traj_id()] =
                    CollisionConfigurationInfo{
                        .time_idx = collision_obj.time,
                        .collision_config =
                            *collision_obj.collision_configuration,
                    };
            }
        }
    }
    return new_ignored_trajs;
}

DpLeadingObjectFeatureCost::DpLeadingObjectFeatureCost(
    const DrivePassage &drive_passage,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const std::vector<std::string> &leading_trajs,
    double ego_front_to_ra)
    : FeatureCost("dp_leading_object"), ego_front_to_ra_(ego_front_to_ra) {
    max_s_t_ =
        GetTrajTimeAccumulatedSPlf(drive_passage, st_traj_mgr, leading_trajs);
}

void DpLeadingObjectFeatureCost::ComputeCost(const MotionEdgeInfo &edge_info,
                                             absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 1)) {
        return;
    }
    cost[0] = 0.0;
    const auto &states = edge_info.equal_interval_states;
    const std::size_t states_size = states.size();
    for (std::size_t i = 0; i < states_size; ++i) {
        const double t = states[i].t + edge_info.start_t;
        const double max_s = max_s_t_(t);
        const double ego_max_s = states[i].accumulated_s + ego_front_to_ra_ +
                                 kInitializerMinFollowDistance;
        double cur_cost = std::max(0.0, ego_max_s - max_s - kHysteresis);
        const double lateral_ratio =
            std::max(
                kEnterLaneLateralDistanceThreshold - std::fabs(states[i].l),
                0.0) *
            kInvEnterLaneLateralDistanceThreshold;
        if (states[i].accumulated_s > max_s) {
            cur_cost += kLeadingObjectLateralOffsetWeight *
                        Transform<kL2Norm>(lateral_ratio);
        }
        double factor = ((i == 0) || (i == (states.size() - 1))) ? 1.0 : 2.0;

        cost[0] += (cur_cost * factor);
    }
    const double dt = states[1].t - states[0].t;
    cost[0] = 0.5 * dt * cost[0];
}

void DpFinalProgressFeatureCost::ComputeCost(const MotionEdgeInfo &edge_info,
                                             absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), 2)) {
        return;
    }
    cost[0] = cost[1] = 0.0;
    const double end_time =
        edge_info.start_t + edge_info.motion_form->duration();
    if (end_time >= kInitializerTrajectoryTimeHorizon) {
        const auto end_state = edge_info.motion_form->State(
            kInitializerTrajectoryTimeHorizon - edge_info.start_t);
        const double kStandardSDiffRatio =
            (InitializerSceneType::INIT_SCENE_BORROW == init_scene_type_) ? 0.07
                                                                          : 0.2;
        cost[0] = std::max(((1.0 - kStandardSDiffRatio) * max_accumulated_s_) -
                               end_state.accumulated_s,
                           0.0) /
                  (kStandardSDiffRatio * max_accumulated_s_);

        const double ref_center_l =
            path_sl_->QueryReferenceCenterL(end_state.accumulated_s);
        constexpr double kEpsilon = 0.1;
        if ((edge_info.motion_form->geometry() != nullptr) &&
            (std::abs(edge_info.motion_form->geometry()->states().back().l -
                      ref_center_l) < kEpsilon)) {
            cost[1] = 0.0;
        } else {
            cost[1] = std::abs(end_state.l - ref_center_l) *
                      (1.0 / kDefaultHalfLaneWidth);
        }
    }
}
}  // namespace planning
}  // namespace pnc_x
