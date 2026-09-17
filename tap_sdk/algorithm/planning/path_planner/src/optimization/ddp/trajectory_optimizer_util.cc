

#include "optimization/ddp/trajectory_optimizer_util.h"

#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <absl/container/btree_map.h>
#include <absl/container/flat_hash_map.h>
#include <absl/strings/str_cat.h>
#include <absl/strings/str_format.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>
// #include <gflags/gflags.h>
#include "common/log.h"

#include "math/piecewise_linear_function.h"
#include "math/vec.h"

#include "optimization/ddp/ddp_optimizer.h"
#include "plan/planner_util.h"
#include "util/file_util.h"

// DEFINE_string(
//     traj_opt_compare_log_file_folder,
//     "offboard/planner/optimizer/compare/data/",
//     "Only used in comparison mode, it is the folder name of a log file."
//     "Make sure the folder exists, see the default value as example.");
// DEFINE_int32(traj_opt_ipopt_canvas_level, 0,
//              "Traj opt ipopt solver canvas level.");

std::string FLAGS_traj_opt_compare_log_file_folder =
    "offboard/planner/optimizer/compare/data/";
int FLAGS_traj_opt_ipopt_canvas_level = 0;

namespace pnc_x {
namespace planning {
namespace optimizer {

namespace {

absl::Status ExportToFile(const DdpOptimizerDebugProto &ddp_debug_proto,
                          const IpoptSolverDebugProto &ipopt_debug_proto) {
    TrajectoryOptimizerCompareProto debug_proto;
    *debug_proto.mutable_ddp() = ddp_debug_proto;
    *debug_proto.mutable_ipopt() = ipopt_debug_proto;
    const auto time_current = absl::Now();
    file_util::ProtoToTextFile(
        debug_proto,
        absl::StrFormat(
            "%s%s_%d.pb.txt", FLAGS_traj_opt_compare_log_file_folder, "data",
            static_cast<double>(absl::ToUnixMillis(time_current))
                ));
    return absl::OkStatus();
}

}  // namespace

void AlignInputTrajectoryToPlanStart(
    const ApolloTrajectoryPointProto &plan_start_point,
    const DrivePassage &drive_passage,
    std::vector<TrajectoryPoint> *input_traj) {
    if (input_traj == nullptr || input_traj->empty()) {
        return;
    }

    constexpr double kMinDeltaS = 1e-3;
    constexpr double kMinDeltaT = 1e-3;
    TrajectoryPoint start_point;
    start_point.FromProto(plan_start_point);
    start_point.set_t(0.0);
    const double start_s = start_point.s();

    std::vector<TrajectoryPoint> projected_traj;
    projected_traj.reserve(input_traj->size());
    for (auto point : *input_traj) {
        const auto sl = drive_passage.QueryFrenetCoordinateAt(point.pos());
        if (!sl.ok()) {
            continue;
        }
        point.set_s(sl->s);
        projected_traj.push_back(std::move(point));
    }

    double start_t_in_input =
        projected_traj.empty() ? 0.0 : projected_traj.front().t();
    for (size_t i = 1; i < projected_traj.size(); ++i) {
        const double prev_s = projected_traj[i - 1].s();
        const double cur_s = projected_traj[i].s();
        if (prev_s <= start_s && start_s <= cur_s &&
            cur_s > prev_s + kMinDeltaS) {
            const double ratio = (start_s - prev_s) / (cur_s - prev_s);
            start_t_in_input =
                projected_traj[i - 1].t() +
                ratio * (projected_traj[i].t() - projected_traj[i - 1].t());
            break;
        }
    }

    std::vector<TrajectoryPoint> aligned_traj;
    aligned_traj.reserve(projected_traj.size() + 1);
    aligned_traj.push_back(start_point);
    for (auto point : projected_traj) {
        if (point.s() <= start_s + kMinDeltaS) {
            continue;
        }
        point.set_t(point.t() - start_t_in_input);
        if (point.t() <= aligned_traj.back().t() + kMinDeltaT ||
            point.s() <= aligned_traj.back().s() + kMinDeltaS) {
            continue;
        }
        aligned_traj.push_back(std::move(point));
    }
    *input_traj = std::move(aligned_traj);
}

absl::Status ValidateTrajectory(
    const std::vector<TrajectoryPoint> &trajectory_points,
    const TrajectoryOptimizerValidationParamsProto
        &trajectory_optimizer_validation_params,
    const TrajectoryOptimizerDebugProto &optimizer_debug,
    const double wheel_base,
    const double steer_ratio) {
    const double final_cost = optimizer_debug.ddp().final_costs().cost();
    if (final_cost > trajectory_optimizer_validation_params.max_final_cost()) {
        return absl::InternalError(absl::StrCat(
            "Traj opt final cost too large, current cost is ", final_cost,
            " max final cost is: ",
            trajectory_optimizer_validation_params.max_final_cost()));
    }

    double max_abs_lateral_acc = 0.0;
    double max_abs_lateral_jerk = 0.0;
    const double max_check_time =
        std::min({trajectory_points.crbegin()->t(), kTrajectoryTimeHorizon,
                  kMaxLatAccCheckTime});
    for (const auto &pt : trajectory_points) {
        if (pt.t() > max_check_time) {
            break;
        }
        max_abs_lateral_acc = std::max(std::abs(ComputeLateralAcceleration(pt)),
                                       max_abs_lateral_acc);
        max_abs_lateral_jerk =
            std::max(std::abs(ComputeLateralJerk(pt)), max_abs_lateral_jerk);
    }
    if (max_abs_lateral_acc >
        trajectory_optimizer_validation_params.max_lateral_acc()) {
        return absl::InternalError(absl::StrCat(
            "Traj opt abs lateral acc to large, abs max lateral acc is ",
            max_abs_lateral_acc, " max abs lateral acc is: ",
            trajectory_optimizer_validation_params.max_lateral_acc()));
    }

    if (max_abs_lateral_jerk >
        trajectory_optimizer_validation_params.max_lateral_jerk()) {
        return absl::InternalError(absl::StrCat(
            "Traj opt abs lateral jerk too large, abs max lateral jerk is ",
            max_abs_lateral_jerk, " max abs lateral jerk is: ",
            trajectory_optimizer_validation_params.max_lateral_jerk()));
    }

    PiecewiseLinearFunction<double, double> max_steer_angle_plf(
        {0.0, 5.56, 8.33, 11.11, 13.89, 16.67, 22.22, 27.78, 33.33, 38.89},
        {410.0, 390.0, 290.0, 140.0, 50.0, 34.0, 16.0, 10.0, 10.0, 10.0});
    PiecewiseLinearFunction<double, double> max_steer_angle_rate_plf(
        {0.0, 5.56, 8.33, 9.0, 10.0, 11.11, 13.89, 16.67, 22.22, 27.78, 33.33,
         38.89},
        {300.0, 270.0, 160.0, 120.0, 75.0, 68.0, 38.0, 25.0, 15.0, 12.0, 10.0,
         10.0});

    for (const auto &pt : trajectory_points) {
        if (pt.t() > max_check_time) {
            break;
        }
        double max_steer_angle = max_steer_angle_plf(pt.v());
        double max_kappa = max_steer_angle / (steer_ratio * wheel_base);
        if (std::abs(pt.kappa()) > max_kappa) {
            // LOG(ERROR) << "Traj opt abs kappa is too large, abs pt kappa is "
            //            << std::abs(pt.kappa()) << "max kappa is: " <<
            //            max_kappa;
            return absl::InternalError(absl::StrCat(
                "Traj opt abs kappa is too large, abs pt kappa is ",
                std::abs(pt.kappa()), "max kappa is: ", max_kappa));
        }
        double max_steer_angle_rate = max_steer_angle_rate_plf(pt.v());
        double max_psi = max_steer_angle_rate / (steer_ratio * wheel_base);
        if (std::abs(pt.psi()) > max_psi) {
            // LOG(ERROR) << "Traj opt abs psi is too large, abs max pt psi is "
            //            << std::abs(pt.psi()) << "max psi is: " << max_psi;
            return absl::InternalError(absl::StrCat(
                "Traj opt abs psi is too large, abs max pt psi is ",
                std::abs(pt.psi()), "max psi is: ", max_psi));
        }
    }

    bool possible_twist = false;
    for (const auto &pt : trajectory_points) {
        if (pt.t() > max_check_time) {
            break;
        }
        if (pt.a() <
                trajectory_optimizer_validation_params.max_deceleration() &&
            std::abs(pt.psi()) >
                trajectory_optimizer_validation_params.max_psi()) {
            possible_twist = true;
            break;
        }
    }
    if (possible_twist) {
        double max_theta = -std::numeric_limits<double>::infinity();
        double min_theta = std::numeric_limits<double>::infinity();
        double min_jerk = std::numeric_limits<double>::infinity();
        double abs_max_psi = -std::numeric_limits<double>::infinity();
        double min_acceleration = std::numeric_limits<double>::infinity();
        const double min_jerk_check_time =
            trajectory_optimizer_validation_params.min_jerk_check_time();
        for (const auto &pt : trajectory_points) {
            if (pt.t() > max_check_time) {
                break;
            }
            max_theta = std::max(max_theta, pt.theta());
            min_theta = std::min(min_theta, pt.theta());
            abs_max_psi = std::min(abs_max_psi, std::abs(pt.psi()));
            min_acceleration = std::min(min_acceleration, pt.a());
            if (pt.t() < min_jerk_check_time) {
                min_jerk = std::min(min_jerk, pt.j());
            }
        }
        const double theta_diff = NormalizeAngle(min_theta - max_theta);
        if (std::abs(NormalizeAngle(min_theta - max_theta)) >
                trajectory_optimizer_validation_params.theta_diff() &&
            min_jerk < trajectory_optimizer_validation_params.min_jerk()) {
            return absl::InternalError(
                absl::StrCat("Traj opt result twist: theta_diff is ",
                             theta_diff, ", min_jerk is ", min_jerk));
        }
    }
    return absl::OkStatus();
}

boost::optional<std::vector<TrajectoryPoint>>
AdaptTrajectoryToGivenPlanStartPoint(
    int plan_id,
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    const Mfob &problem,
    const DdpOptimizerParamsProto &params,
    double max_adaption_cost,
    const TrajectoryPoint &plan_start_point,
    std::vector<TrajectoryPoint> trajectory,
    boost::optional<std::vector<TrajectoryPoint>> *pre_traj,
    boost::optional<double> *pre_traj_cost) {
    XCHECK_GE(trajectory.size(),
              dense_trajectory_steps + sparse_trajectory_steps);

    trajectory.front() = plan_start_point;

    DdpOptimizer<Mfob> solver(plan_id, &problem, dense_trajectory_steps,
                              sparse_trajectory_steps,
                              "trajectory_optimizer_refit", 0, params);

    constexpr int kAdaptTrajectorySolveIteration = 1;
    DdpOptimizer<Mfob>::SolveConfig config =
        DdpOptimizer<Mfob>::SolveConfig::Default();
    config.max_iteration = kAdaptTrajectorySolveIteration;
    absl::StatusOr<std::vector<TrajectoryPoint>> refitted_trajectory =
        solver.Solve(trajectory, config);

    if (refitted_trajectory.ok()) {
        const double refit_cost =
            solver.EvaluateCostForTrajectory(refitted_trajectory.value());
        if (pre_traj_cost) {
            *pre_traj_cost = solver.GetFinalTotalCost();
        }
        if (pre_traj) {
            *pre_traj = refitted_trajectory.value();
        }
        if (refit_cost <= max_adaption_cost) {
            return std::move(refitted_trajectory.value());
        }
    }

    return boost::none;
}

bool HasSameDecisionOverSpacetimeObject(
    const std::vector<TrajectoryPoint> &traj_1,
    const std::vector<TrajectoryPoint> &traj_2,
    const std::vector<SpacetimeObjectState> &spacetime_object_states) {
    const int n = static_cast<int>(std::min(
        {traj_1.size(), traj_2.size(), spacetime_object_states.size()}));
    if (n < 1) {
        return true;
    }

    std::vector<double> traj_1_angles;
    std::vector<double> traj_2_angles;
    traj_1_angles.reserve(n);
    traj_2_angles.reserve(n);
    for (int i = 0; i < n; ++i) {
        const Vec2d traj_1_offset =
            traj_1[i].pos() - spacetime_object_states[i].box.center();
        const Vec2d traj_2_offset =
            traj_2[i].pos() - spacetime_object_states[i].box.center();

        constexpr double kEpsilon = 1e-9;
        traj_1_angles.push_back(
            (traj_1_offset.Sqr() < kEpsilon) ? 0.0 : traj_1_offset.FastAngle());
        traj_2_angles.push_back(
            (traj_2_offset.Sqr() < kEpsilon) ? 0.0 : traj_2_offset.FastAngle());
    }

    const double start_angle_diff =
        NormalizeAngle(traj_1_angles.front() - traj_2_angles.front());
    if (std::abs(start_angle_diff) > M_PI_2) {
        return false;
    }
    const double end_angle_diff =
        NormalizeAngle(traj_1_angles.back() - traj_2_angles.back());
    if (std::abs(end_angle_diff) > M_PI_2) {
        return false;
    }

    double angle_sum = start_angle_diff - end_angle_diff;
    for (std::size_t i = 0, limit = static_cast<std::size_t>(n) - 1U; i < limit; ++i) {
        (void)(angle_sum += NormalizeAngle(traj_1_angles[i + 1U] - traj_1_angles[i]));
        (void)(angle_sum += NormalizeAngle(traj_2_angles[i] - traj_2_angles[i + 1U]));
    }

    constexpr double kNoCirclingThreshold = M_PI;
    return std::abs(angle_sum) < kNoCirclingThreshold;
}

}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
