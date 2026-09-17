

#include "initializer/initializer_util.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include <absl/container/flat_hash_set.h>
#include <absl/status/statusor.h>
#include <absl/strings/str_cat.h>
#include <absl/strings/str_format.h>
#include <absl/strings/str_join.h>
#include <absl/types/span.h>
#include "common/log.h"

#include "pncx_constraint.pb.h"
#include "initializer/cost_provider.h"
#include "initializer/geometry/geometry_form.h"
#include "initializer/geometry/geometry_state.h"
#include "initializer/motion_graph.h"
#include "math/frenet_common.h"
#include "math/geometry/util.h"
#include "math/util.h"
#include "math/vec.h"
#include "plan/planner_defs.h"
#include "plan/trajectory_util.h"
#include "util/path_util.h"
#include "util/status_builder.h"
#include "util/status_macros.h"

namespace pnc_x {
namespace planning {

namespace {

double FindRequiredLonDecel(
    double ego_front_to_ra,
    double ego_s,
    double ego_v,
    absl::Span<const ConstraintProto::StopLineProto> stop_lines,
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        &leading_trajs,
    int traj_steps) {
    ego_s += ego_front_to_ra;
    const double traj_time = traj_steps * kTrajectoryTimeStep;
    double decel = 0.0;
    if (!stop_lines.empty()) {
        const double min_stop_s = stop_lines.front().s();
        decel = 2.0 * (min_stop_s - ego_s - ego_v * traj_time) / Sqr(traj_time);
    }
    constexpr double kLeadingLonBuffer = 0.3;
    ego_s += kLeadingLonBuffer;
    for (const auto &pair : leading_trajs) {
        const auto &leading_traj = pair.second;
        for (const auto &st_constraint : leading_traj.st_constraints()) {
            decel = std::min(
                decel,
                2.0 * (st_constraint.s() - ego_s - ego_v * st_constraint.t()) /
                    Sqr(st_constraint.t() - kTrajectoryTimeStep));
        }
    }
    return decel;
}

}  // namespace

void SendSingleTrajectoryToCanvas(
    const MotionSearchOutput::MultiTrajCandidate &traj_info,
    int idx,
    int planner_id) {}

absl::StatusOr<std::vector<ApolloTrajectoryPointProto>>
GenerateConstLateralAccelConstSpeedTraj(
    const DrivePassage &drive_passage,
    double ego_front_to_ra,
    double target_l,
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        &leading_trajs,
    absl::Span<const ConstraintProto::StopLineProto> stop_lines,
    const ApolloTrajectoryPointProto &plan_start_point,
    int traj_steps) {
    XCHECK_GT(traj_steps, 0);
    constexpr double kStationarySpeedThres = 0.1;
    if (plan_start_point.v() < kStationarySpeedThres) {
        std::vector<ApolloTrajectoryPointProto> stationary_traj(
            static_cast<std::size_t>(traj_steps), plan_start_point);
        for (int i = 1; i < traj_steps; ++i) {
            stationary_traj[static_cast<std::size_t>(i)].set_relative_time(i * kTrajectoryTimeStep);
        }
        return stationary_traj;
    }

    const auto ego_pos = Vec2dFromApolloTrajectoryPointProto(plan_start_point);
    ASSIGN_OR_RETURN(const auto ego_sl,
                     drive_passage.QueryFrenetCoordinateAt(ego_pos),
                     _ << "Unable to project ego position onto drive passage.");
    ASSIGN_OR_RETURN(const auto lane_tangent,
                     drive_passage.QueryTangentAtS(ego_sl.s),
                     _ << "Unable to find lane tangent at ego position.");

    const double required_lon_decel =
        FindRequiredLonDecel(ego_front_to_ra, ego_sl.s, plan_start_point.v(),
                             stop_lines, leading_trajs, traj_steps);

    constexpr double kMaxLaneChangeCancelLatAccel = 0.5;
    constexpr double kZeroLateralVelThreshold = 0.01;
    constexpr double kZeroLongitudinalVelThreshold = 1.0;
    constexpr double kDt = kTrajectoryTimeStep;

    const auto heading_tangent =
        Vec2d::FastUnitFromAngle(plan_start_point.path_point().theta());
    double lon_v = plan_start_point.v() * lane_tangent.Dot(heading_tangent);
    double lat_v =
        plan_start_point.v() * lane_tangent.CrossProd(heading_tangent);
    lat_v = std::fabs(lat_v) < kZeroLateralVelThreshold ? 0.0 : lat_v;
    const double lon_a =
        std::min(plan_start_point.a() * lane_tangent.Dot(heading_tangent),
                 required_lon_decel);
    double lat_a =
        plan_start_point.a() * lane_tangent.CrossProd(heading_tangent) +
        Sqr(plan_start_point.v()) * lane_tangent.Dot(heading_tangent) *
            plan_start_point.path_point().kappa();

    std::vector<FrenetCoordinate> traj_sl;
    traj_sl.reserve(static_cast<std::size_t>(traj_steps));
    traj_sl.push_back(ego_sl);
    double s = ego_sl.s, l = ego_sl.l;

    constexpr double kMaxComfortLatJerk = 1.0;
    const double expect_lat_a =
        std::copysign(kMaxLaneChangeCancelLatAccel, lat_v);
    const int const_lat_jerk_steps =
        CeilToInt(std::abs(expect_lat_a - lat_a) / (kMaxComfortLatJerk * kDt));
    for (int i = 1; i < const_lat_jerk_steps + 1; ++i) {
        s += lon_v * kDt;
        l += lat_v * kDt;
        traj_sl.push_back(FrenetCoordinate{.s = s, .l = l});

        lon_v = std::max(0.0, lon_v + lon_a * kDt);
        lat_v += lat_a * kDt;
        lat_a += std::copysign(
            std::min(kMaxComfortLatJerk * kDt, std::abs(expect_lat_a - lat_a)),
            expect_lat_a - lat_a);
        if (std::abs(lon_v) < kZeroLongitudinalVelThreshold) break;
    }

    constexpr double kReachTargetLaneThreshold = 0.1;
    constexpr double kMaxLaneChangeLatAccel = 0.09;
    const double l_diff = l - target_l;
    constexpr double kNearTargetLaneThreshold = 0.3;
    lat_a = std::abs(l_diff) < kNearTargetLaneThreshold
                ? kMaxLaneChangeCancelLatAccel
                : (lat_v * l_diff < 0.0 ? kMaxLaneChangeLatAccel
                                        : kMaxLaneChangeCancelLatAccel);
    lat_a = std::copysign(lat_a, -l_diff);
    for (int i = traj_sl.size(); i < traj_steps; ++i) {
        if (std::abs(lon_v) < kZeroLongitudinalVelThreshold) break;
        const double new_l = l + lat_v * kDt;
        if ((std::fabs(new_l - target_l) < kReachTargetLaneThreshold &&
             std::fabs(lat_v) < kZeroLateralVelThreshold) ||
            (new_l - target_l) * (l - target_l) < 0.0) {
            break;
        }

        s += lon_v * kDt;
        l += lat_v * kDt;
        traj_sl.push_back(FrenetCoordinate{.s = s, .l = l});

        lon_v = std::max(0.0, lon_v + lon_a * kDt);
        lat_v += lat_a * kDt;
    }

    for (int i = traj_sl.size(); i < traj_steps; ++i) {
        s += lon_v * kDt;
        lon_v = std::max(0.0, lon_v + lon_a * kDt);
        traj_sl.push_back(FrenetCoordinate{.s = s, .l = l});
    }
    const double max_accum_s = drive_passage.end_s();
    if (traj_sl.back().s > max_accum_s) {
        const double ratio = max_accum_s / traj_sl.back().s;
        for (auto &pt_sl : traj_sl) pt_sl.s *= ratio;
    }

    std::vector<Vec2d> traj_xy;
    traj_xy.reserve(traj_sl.size());
    for (const auto &pt_sl : traj_sl) {
        ASSIGN_OR_RETURN(const auto pt_xy,
                         drive_passage.QueryPointXYAtSL(pt_sl.s, pt_sl.l),
                         _ << "Lc pause trajectory out of drive passage.");
        traj_xy.push_back(pt_xy);
    }
    std::vector<double> traj_v(static_cast<std::size_t>(traj_steps)), traj_a(static_cast<std::size_t>(traj_steps));
    for (int i = 1; i + 1 < traj_steps; ++i) {
        traj_v[static_cast<std::size_t>(i)] = traj_xy[static_cast<std::size_t>(i + 1)].DistanceTo(traj_xy[static_cast<std::size_t>(i)]) / kDt;
    }
    traj_v[static_cast<std::size_t>(traj_steps - 1)] = traj_v[static_cast<std::size_t>(traj_steps - 2)];
    for (int i = 1; i + 1 < traj_steps; ++i) {
        traj_a[static_cast<std::size_t>(i)] = (traj_v[static_cast<std::size_t>(i + 1)] - traj_v[static_cast<std::size_t>(i)]) / kDt;
    }
    traj_a[static_cast<std::size_t>(traj_steps - 1)] = traj_a[static_cast<std::size_t>(traj_steps - 2)];

    constexpr double kEpsilon = 1e-3;

    std::vector<ApolloTrajectoryPointProto> traj_pts;
    traj_pts.reserve(static_cast<std::size_t>(traj_steps));
    traj_pts.push_back(plan_start_point);
    for (int i = 1; i < traj_steps; ++i) {
        PathPoint path_pt;
        path_pt.set_x(traj_xy[static_cast<std::size_t>(i)].x());
        path_pt.set_y(traj_xy[static_cast<std::size_t>(i)].y());
        path_pt.set_z(0.0);
        const double dist2prev = traj_xy[static_cast<std::size_t>(i)].DistanceTo(traj_xy[static_cast<std::size_t>(i - 1)]);
        const double cur_theta =
            ((i + 1 == traj_steps) ||
             (traj_xy[static_cast<std::size_t>(i + 1)].DistanceTo(traj_xy[static_cast<std::size_t>(i)]) < kEpsilon))
                ? traj_pts[static_cast<std::size_t>(i - 1)].path_point().theta()
                : (traj_xy[static_cast<std::size_t>(i + 1)] - traj_xy[static_cast<std::size_t>(i)]).FastAngle();
        path_pt.set_theta(cur_theta);
        path_pt.set_kappa(
            dist2prev < kEpsilon
                ? 0.0
                : NormalizeAngle(cur_theta -
                                 traj_pts[static_cast<std::size_t>(i - 1)].path_point().theta()) /
                      dist2prev);
        path_pt.set_s(traj_pts[static_cast<std::size_t>(i - 1)].path_point().s() + dist2prev);

        ApolloTrajectoryPointProto traj_point;
        *traj_point.mutable_path_point() = std::move(path_pt);
        traj_point.set_v(traj_v[static_cast<std::size_t>(i)]);
        traj_point.set_a(traj_a[static_cast<std::size_t>(i)]);
        traj_point.set_relative_time(i * kTrajectoryTimeStep);

        traj_pts.push_back(std::move(traj_point));
    }

    return traj_pts;
}

void ParseMotionSearchOutputToMotionSearchDebugProto(
    const MotionSearchOutput &search_output, MotionSearchDebugProto *proto) {
    proto->Clear();

    for (const auto &name : search_output.cost_provider->cost_names()) {
        auto *cost_name = proto->add_cost_names();
        *cost_name = name;
    }

    search_output.motion_graph->ToProto(proto->mutable_motion_graph());

    proto->mutable_edge_costs()->Reserve(
        search_output.motion_graph->edge_size());
    for (const auto &edge_cost : search_output.search_costs) {
        auto *edge_cost_proto = proto->add_edge_costs();
        edge_cost_proto->mutable_costs()->Reserve(
            static_cast<int>(edge_cost.feature_cost.size()));
        for (const double c : edge_cost.feature_cost) {
            edge_cost_proto->add_costs(c);
        }
        XCHECK_EQ(edge_cost_proto->costs_size(), proto->cost_names_size());
        edge_cost_proto->set_cum_cost(edge_cost.cost_to_come);
    }

    proto->set_best_last_edge_index(search_output.best_last_edge_index.value());

    proto->mutable_top_k_trajs()->Reserve(static_cast<int>(search_output.top_k_trajs.size()));
    for (int i = 0; i < search_output.top_k_trajs.size(); ++i) {
        const auto last_edge = search_output.top_k_edges[static_cast<std::size_t>(i)];
        auto *traj_info_proto = proto->add_top_k_trajs();

        traj_info_proto->mutable_costs()->Reserve(
            static_cast<int>(search_output.cost_provider->cost_names().size()));
        for (const double c :
             search_output.search_costs[last_edge].feature_cost) {
            traj_info_proto->add_costs(c);
        }
        traj_info_proto->set_total_cost(search_output.top_k_total_costs[static_cast<std::size_t>(i)]);
        traj_info_proto->set_last_edge_idx(last_edge.value());
        for (const auto &point : search_output.top_k_trajs[static_cast<std::size_t>(i)]) {
            *traj_info_proto->add_traj_points() =
                ToPoseTrajectoryPointProto(point);
        }
    }
}

void ParseMotionSearchOutputToMultiTrajDebugProto(
    const MotionSearchOutput &search_output, MultiTrajDebugProto *proto) {
    const auto &multi_trajs = search_output.multi_traj_candidates;
    proto->Clear();

    proto->mutable_multi_traj_candidates()->Reserve(static_cast<int>(multi_trajs.size()));
    for (const auto &traj : multi_trajs) {
        auto *traj_proto = proto->add_multi_traj_candidates();

        traj_proto->mutable_traj_points()->Reserve(static_cast<int>(traj.trajectory.size()));
        for (const auto &point : traj.trajectory) {
            *traj_proto->add_traj_points() = ToPoseTrajectoryPointProto(point);
        }

        traj_proto->mutable_leading_traj_ids()->Reserve(
            static_cast<int>(traj.leading_traj_ids.size()));
        for (const auto &lead_traj_id : traj.leading_traj_ids) {
            traj_proto->add_leading_traj_ids(lead_traj_id);
        }
        traj_proto->mutable_ignored_trajs()->Reserve(static_cast<int>(traj.ignored_trajs.size()));
        for (const auto &pair : traj.ignored_trajs) {
            const auto &traj_id = pair.first;
            const auto &info = pair.second;
            MultiTrajDebugProto::IgnoredObjectTrajectoryProto ignored_traj;
            ignored_traj.set_traj_id(traj_id);
            ignored_traj.set_time_idx(info.time_idx);
            ignored_traj.set_collision_config(
                static_cast<int>(info.collision_config));
            *traj_proto->add_ignored_trajs() = std::move(ignored_traj);
        }

        traj_proto->set_total_cost(traj.total_cost);
    }
}

void ParseMotionSearchOutputToInitializerResult(
    const MotionSearchOutput &search_output, InitializerDebugProto *proto) {
    proto->set_lc_pause(search_output.is_lc_pause);

    auto *follower_set = proto->mutable_follower_objects();
    follower_set->Clear();
    for (const auto &obj_id : search_output.follower_set) {
        *follower_set->Add() = obj_id;
    }

    auto *leader_set = proto->mutable_leader_objects();
    leader_set->Clear();
    for (const auto &obj_id : search_output.leader_set) {
        *leader_set->Add() = obj_id;
    }

    auto *resampled_traj = proto->mutable_resampled_trajectory();
    resampled_traj->Clear();
    resampled_traj->mutable_trajectory_points()->Reserve(
        static_cast<int>(search_output.traj_points.size()));
    for (const auto &point : search_output.traj_points) {
        *resampled_traj->add_trajectory_points() = point;
    }
}

std::vector<double> GetXYRange(const PathSlBoundary &sl_boundary) {
    double xmin = std::numeric_limits<double>::max(),
           ymin = std::numeric_limits<double>::max();
    double xmax = std::numeric_limits<double>::lowest(),
           ymax = std::numeric_limits<double>::lowest();
    for (const auto &val : sl_boundary.left_xy_vector()) {
        xmin = std::min(val.x(), xmin);
        xmax = std::max(val.x(), xmax);
        ymin = std::min(val.y(), ymin);
        ymax = std::max(val.y(), ymax);
    }
    for (const auto &val : sl_boundary.right_xy_vector()) {
        xmin = std::min(val.x(), xmin);
        xmax = std::max(val.x(), xmax);
        ymin = std::min(val.y(), ymin);
        ymax = std::max(val.y(), ymax);
    }

    return std::vector<double>({xmin, xmax, ymin, ymax});
}

InitializerOutput MakeAebInitializerOutput(
    ApolloTrajectoryPointProto plan_start_point,
    InitializerStateProto new_state,
    const std::string &message,
    InitializerDebugProto *debug_proto,
    const std::vector<LeadingGroup> &leading_groups,
    const std::unique_ptr<ConstraintProto::LeadingObjectProto>
        &blocking_static_traj,
    const MotionConstraintParamsProto *motion_constraint_params) {
    AD_LWARN(PP) << message << "Initializer will output an AEB trajectory!";
    const auto &kAebMaxDecel = motion_constraint_params->max_deceleration();
    const auto &kAebMaxJerk = motion_constraint_params->max_decel_jerk();
    std::vector<ApolloTrajectoryPointProto> aeb_traj;
    aeb_traj.reserve(static_cast<std::size_t>(kInitializerTrajectorySteps));
    ApolloTrajectoryPointProto cur_point = std::move(plan_start_point);
    double jerk = kAebMaxJerk;
    double decel = cur_point.a();
    double speed = cur_point.v();
    for (int i = 0; i < kInitializerTrajectorySteps; ++i) {
        decel = boost::algorithm::clamp(decel + jerk * kTrajectoryTimeStep,
                                        kAebMaxDecel, 0.0);
        if (decel <= kAebMaxDecel) {
            jerk = 0;
        }
        speed = std::max(speed + decel * kTrajectoryTimeStep, 0.0);
        if (speed <= 0.0) {
            decel = 0;
        }
        const double dist =
            std::max(0.0, (cur_point.v() + 0.5 * decel * kTrajectoryTimeStep) *
                              kTrajectoryTimeStep);
        ApolloTrajectoryPointProto next_point;
        *next_point.mutable_path_point() =
            GetPathPointAlongCircle(cur_point.path_point(), dist);
        next_point.set_relative_time((static_cast<double>(i) + 1.0) * kTrajectoryTimeStep);
        next_point.set_v(speed);
        next_point.set_a(decel);
        cur_point.set_j(jerk);
        aeb_traj.push_back(std::move(cur_point));
        cur_point = std::move(next_point);
    }

    debug_proto->mutable_multi_traj_debug()
        ->mutable_multi_traj_candidates()
        ->Clear();
    auto &debug_traj = *debug_proto->mutable_multi_traj_debug()
                            ->add_multi_traj_candidates()
                            ->mutable_traj_points();
    debug_traj.Clear();
    debug_traj.Reserve(static_cast<int>(aeb_traj.size()));
    for (const auto &traj_pt : aeb_traj) {
        *debug_traj.Add() = ToPoseTrajectoryPointProto(traj_pt);
    }
    std::map<std::string, ConstraintProto::LeadingObjectProto> leading_trajs;
    for (const auto &leading : leading_groups) {
        leading_trajs.insert(leading.begin(), leading.end());
    }
    if (blocking_static_traj != nullptr) {
        leading_trajs.insert(
            {blocking_static_traj->traj_id(), *blocking_static_traj});
    }

    return InitializerOutput{.traj_points = std::move(aeb_traj),
                             .initializer_state = std::move(new_state),
                             .leading_trajs = std::move(leading_trajs),
                             .is_aeb_result = true};
}

void ParseFeaturesDumpingProto(
    const MotionSearchOutput &search_output,
    ExpertEvaluationProto *expert_proto,
    SampledDpMotionEvaluationProto *candidates_proto) {
    if (search_output.expert_evaluation.traj.empty() ||
        search_output.candidates_evaluation.empty()) {
        AD_LWARN(PP) << "No expert evaluation or candidates evaluation for "
                        "ParseFeaturesDumpingProto.";
        return;
    }

    expert_proto->Clear();

    for (const auto &name : search_output.cost_provider->cost_names()) {
        *expert_proto->add_cost_names() = name;
    }

    expert_proto->mutable_costs()->Reserve(expert_proto->cost_names_size());
    for (const auto &c : search_output.expert_evaluation.feature_costs) {
        expert_proto->add_costs(c);
    }

    expert_proto->set_total_cost(
        search_output.expert_evaluation.weighted_total_cost);

    expert_proto->mutable_trajectory()->mutable_trajectory_points()->Reserve(
        static_cast<int>(search_output.expert_evaluation.traj.size()));
    for (const auto &point : search_output.expert_evaluation.traj) {
        auto *new_trajectory_point =
            expert_proto->mutable_trajectory()->add_trajectory_points();
        *new_trajectory_point = point;
    }

    *expert_proto->mutable_weights() = {
        search_output.cost_provider->weights().begin(),
        search_output.cost_provider->weights().end()};

    expert_proto->mutable_is_filtered_reasons()->set_is_out_of_bound(
        search_output.expert_evaluation.is_filtered_reasons.is_out_of_bound);
    expert_proto->mutable_is_filtered_reasons()
        ->set_is_violating_stop_constraint(
            search_output.expert_evaluation.is_filtered_reasons
                .is_violating_stop_constraint);
    expert_proto->mutable_is_filtered_reasons()->set_is_dynamic_collision(
        search_output.expert_evaluation.is_filtered_reasons
            .is_dynamic_collision);
    expert_proto->mutable_is_filtered_reasons()
        ->set_is_violating_leading_objects(
            search_output.expert_evaluation.is_filtered_reasons
                .is_violating_leading_objects);

    candidates_proto->Clear();

    auto candidates_cost_name = candidates_proto->mutable_cost_names();
    candidates_cost_name->CopyFrom(expert_proto->cost_names());

    candidates_proto->mutable_traj_costs()->Reserve(
        static_cast<int>(search_output.candidates_evaluation.size()));
    candidates_proto->mutable_trajectory()->Reserve(
        static_cast<int>(search_output.candidates_evaluation.size()));
    for (const auto &traj_eval : search_output.candidates_evaluation) {
        auto *traj_cost = candidates_proto->add_traj_costs();
        for (const auto &c : traj_eval.feature_costs) {
            traj_cost->add_costs(c);
        }
        traj_cost->set_total_cost(traj_eval.weighted_total_cost);

        auto *traj_proto = candidates_proto->add_trajectory();
        traj_proto->mutable_trajectory_points()->Reserve(static_cast<int>(traj_eval.traj.size()));
        for (const auto &point : traj_eval.traj) {
            auto *new_trajectory_point = traj_proto->add_trajectory_points();
            *new_trajectory_point = point;
        }
    }

    candidates_proto->set_min_cost(search_output.min_cost);
    *candidates_proto->mutable_weights() = {
        search_output.cost_provider->weights().begin(),
        search_output.cost_provider->weights().end()};
}
}  // namespace planning
}  // namespace pnc_x
