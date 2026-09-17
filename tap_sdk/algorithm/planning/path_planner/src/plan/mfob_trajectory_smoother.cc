

#include "plan/mfob_trajectory_smoother.h"

#include <algorithm>
#include <complex>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <Eigen/Eigen>
#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>
#include "common/log.h"
#include "common/gflags.h"
#include "common/timer.h"
#include "math/piecewise_linear_function.h"
#include "math/util.h"
#include "math/vec.h"
#include "optimization/ddp/ddp_optimizer.h"
#include "optimization/problem/curvature_cost.h"
#include "optimization/problem/forward_speed_cost.h"
#include "optimization/problem/longitudinal_acceleration_cost.h"
#include "optimization/problem/mfob_curvature_rate_cost.h"
#include "optimization/problem/mixed_fourth_order_bicycle.h"
#include "optimization/problem/reference_control_deviation_cost.h"
#include "optimization/problem/reference_line_deviation_cost.h"
#include "optimization/problem/reference_state_deviation_cost.h"
#include "optimization/problem/static_boundary_cost_lite.h"
#include "plan/trajectory_point.h"

#include "util/vehicle_geometry_util.h"

// DEFINE_int32(mfob_trajectory_smoother_canvas_level,
//              0,
//              "Mfob trajectory smoother canvas verbosity level");
// DEFINE_int32(mfob_trajectory_smoother_verbosity_level,
//              0,
//              "Mfob trajectory smoother verbosity level");

namespace pnc_x {
namespace planning {
namespace {

using Mfob = MixedFourthOrderBicycle;
using StatesType = Mfob::StatesType;
using StateType = Mfob::StateType;
using ControlsType = Mfob::ControlsType;
using ControlType = Mfob::ControlType;

std::vector<TrajectoryPoint> GeneratePurePursuitInitTraj(
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
    const Mfob &problem,
    const std::vector<TrajectoryPoint> &init_traj,
    const VehicleGeometryParamsProto &veh_geo_params,
    const double dense_longitudinal_lookahead_time,
    const double sparse_longitudinal_lookahead_time,
    const double lateral_lookahead_time) {
    const int trajectory_steps =
        dense_trajectory_steps + sparse_trajectory_steps;
    XCHECK_GT(trajectory_steps, 0);
    XCHECK_GT(dense_trajectory_time_step, 0.0);

    const int dense_longitudinal_lookahead_steps = RoundToInt(
        dense_longitudinal_lookahead_time / dense_trajectory_time_step);

    StatesType init_xs = Mfob::FitState(init_traj);

    const int dense_total_steps = dense_trajectory_steps + dense_longitudinal_lookahead_steps;
    std::vector<StateType> dense_longitudinal_extended_xs(
        static_cast<size_t>(dense_total_steps));
    for (int k = 0; k < dense_trajectory_steps; ++k) {
        dense_longitudinal_extended_xs[k] = Mfob::GetStateAtStep(init_xs, k);
    }
    StateType x_dense =
        Mfob::GetStateAtStep(init_xs, dense_trajectory_steps - 1);
    for (int k = 0; k < dense_longitudinal_lookahead_steps; ++k) {
        x_dense = problem.EvaluateF(k, x_dense, ControlType::Zero(),
                                    dense_trajectory_time_step);
        dense_longitudinal_extended_xs[static_cast<size_t>(dense_trajectory_steps) + static_cast<size_t>(k)] = x_dense;
    }

    const int sparse_longitudinal_lookahead_steps =
        (sparse_trajectory_time_step > 1e-6)
            ? RoundToInt(sparse_longitudinal_lookahead_time /
                         sparse_trajectory_time_step)
            : 0;
    const int sparse_total_steps = sparse_trajectory_steps + sparse_longitudinal_lookahead_steps;
    std::vector<StateType> sparse_longitudinal_extended_xs(
        static_cast<size_t>(sparse_total_steps));
    for (int k = 0; k < sparse_trajectory_steps; ++k) {
        sparse_longitudinal_extended_xs[k] =
            Mfob::GetStateAtStep(init_xs, k + dense_trajectory_steps);
    }
    StateType x_sparse = Mfob::GetStateAtStep(
        init_xs, dense_trajectory_steps + sparse_trajectory_steps - 1);
    for (int k = 0; k < sparse_longitudinal_lookahead_steps; ++k) {
        x_sparse = problem.EvaluateF(k, x_sparse, ControlType::Zero(),
                                     sparse_trajectory_time_step);
        sparse_longitudinal_extended_xs[static_cast<size_t>(sparse_trajectory_steps) + static_cast<size_t>(k)] = x_sparse;
    }
    const auto get_longitudinal_target =
        [&dense_longitudinal_extended_xs, dense_longitudinal_lookahead_steps,
         sparse_longitudinal_extended_xs, sparse_longitudinal_lookahead_steps,
         dense_trajectory_steps](int index) -> StateType {
        if (index < dense_trajectory_steps) {
            XCHECK_LT(index + dense_longitudinal_lookahead_steps,
                      dense_longitudinal_extended_xs.size());
            return dense_longitudinal_extended_xs
                [index + dense_longitudinal_lookahead_steps];
        }
        XCHECK_LT(index - dense_trajectory_steps +
                      sparse_longitudinal_lookahead_steps,
                  sparse_longitudinal_extended_xs.size());
        return sparse_longitudinal_extended_xs
            [index - dense_trajectory_steps +
             sparse_longitudinal_lookahead_steps];
    };

    std::vector<StateType> lateral_extended_xs(trajectory_steps);
    std::vector<double> lateral_extened_xs_s(trajectory_steps);
    for (int k = 0; k < trajectory_steps; ++k) {
        lateral_extended_xs[k] = Mfob::GetStateAtStep(init_xs, k);
        lateral_extened_xs_s[k] = Mfob::s(init_xs, k);
    }

    const double init_traj_s = Mfob::StateGetS(lateral_extended_xs.back());
    const PiecewiseLinearFunction<StateType, double> lateral_reference_plf(
        lateral_extened_xs_s, lateral_extended_xs);
    const auto get_lateral_target =
        [&lateral_reference_plf, &lateral_extended_xs, &init_traj_s](
            const StateType &state,
            double lateral_look_ahead_dist) -> StateType {
        const double target_s =
            lateral_look_ahead_dist + Mfob::StateGetS(state);
        if (target_s >= init_traj_s) {
            StateType target = lateral_extended_xs.back();
            Vec2d target_theta_tangent =
                Vec2d::UnitFromAngle(Mfob::StateGetTheta(target));
            Mfob::StateSetPos(
                Mfob::StateGetPos(target) +
                    ((target_s - init_traj_s) * target_theta_tangent),
                &target);
            return target;
        } else {
            return lateral_reference_plf(target_s);
        }
    };

    ControlsType us = ControlsType::Zero(trajectory_steps * Mfob::kControlSize);
    StatesType xs = StatesType::Zero(trajectory_steps * Mfob::kStateSize);
    StateType x = Mfob::GetStateAtStep(init_xs, 0);
    for (int k = 0; k < trajectory_steps; ++k) {
        Mfob::SetStateAtStep(x, k, &xs);
        StateType longitudinal_target = get_longitudinal_target(k);
        const double lateral_look_ahead_dist =
            (lateral_lookahead_time * Mfob::StateGetV(x)) +
            veh_geo_params.wheel_base();
        StateType lateral_target =
            get_lateral_target(x, lateral_look_ahead_dist);
        double lookahead_time = (k < dense_trajectory_steps)
                                    ? (dense_longitudinal_lookahead_steps *
                                       dense_trajectory_time_step)
                                    : (sparse_longitudinal_lookahead_steps *
                                       sparse_trajectory_time_step);
        ControlType u = problem.PurePursuitController(
            k, x, longitudinal_target, lateral_target, lookahead_time,
            lateral_look_ahead_dist);
        x = problem.EvaluateF(k, x, u);
        Mfob::SetControlAtStep(u, k, &us);
    }

    std::vector<TrajectoryPoint> res(trajectory_steps);
    for (int k = 0; k < trajectory_steps; ++k) {
        TrajectoryPoint &point = res[k];
        problem.ExtractTrajectoryPoint(k, Mfob::GetStateAtStep(xs, k),
                                       Mfob::GetControlAtStep(us, k), &point);
    }
    return res;
}

void AddStaticBoundaryCost(
    int trajectory_steps,
    const DrivePassage &drive_passage,
    const VehicleGeometryParamsProto &veh_geo_params,
    const TrajectorySmootherCostWeightParamsProto &smoother_params,
    Mfob *problem) {
    XCHECK_NOTNULL(problem);
    XCHECK_GT(trajectory_steps, 0);
    const int drive_passage_size = drive_passage.stations().size();
    std::vector<Vec2d> path_points;
    std::vector<double> l_max;
    std::vector<double> l_min;

    path_points.reserve(drive_passage_size);
    l_min.reserve(drive_passage_size);
    l_max.reserve(drive_passage_size);

    for (int i = 0; i < drive_passage_size; ++i) {
        const Station &station = drive_passage.stations()[StationIndex(i)];
        const auto curb_pair_or = station.QueryCurbOffsetAt(0.0);

        path_points.push_back(station.xy());
        l_min.push_back(curb_pair_or->first);
        l_max.push_back(curb_pair_or->second);
    }

    problem->AddCost(std::make_unique<StaticBoundaryCostLite<Mfob>>(
        trajectory_steps, std::move(path_points), std::move(l_min),
        std::move(l_max),
        (veh_geo_params.width() * 0.5) +
            smoother_params.static_boundary_cost_buffer(),
        "StaticBoundaryCostLite",
        smoother_params.static_boundary_cost_weight()));
}

}  // namespace

/**
 * 整体平滑逻辑：
 * 1. 构建优化问题（动力学模型 + 约束条件）
 * 2. 基于参考轨迹添加代价函数
 * 3. Pure Pursuit 生成可行初值
 * 4. 用 DDP 优化轨迹
 * 5. 返回优化结果（失败则回退参考轨迹）

function SmoothTrajectoryByMixedFourthOrderDdp(...):
    // 1. 构建问题
    problem = build_problem(dense_steps, sparse_steps, dense_dt, sparse_dt,
                            motion_constraints, vehicle_params)

    // 2. 添加代价（路径、状态、控制、曲率、边界、加速度等）
    add_costs_from_ref_traj(problem, ref_traj, smoother_params)

    // 3. Pure Pursuit 生成初值（主要是生成控制量）
    init_traj = pure_pursuit_init(ref_traj, lookahead_times, vehicle_params)

    // 4. DDP 优化
    result = DDP.solve(init_traj)

    // 5. 返回
    if result.ok:
        return result.trajectory
    else:
        return ref_traj (对上游重采样的结果)
 */

std::vector<TrajectoryPoint> SmoothTrajectoryByMixedFourthOrderDdp(
    int plan_id,
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
    const std::vector<TrajectoryPoint> &ref_traj,
    const DrivePassage &drive_passage,
    const std::string &owner,
    const TrajectorySmootherCostWeightParamsProto &smoother_params,
    const MotionConstraintParamsProto &motion_constraint_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const VehicleDriveParamsProto &veh_drive_params,
    boost::optional<double> *smooth_init_cost,
    const std::vector<double> &ref_ls) {
    const int trajectory_steps =
        dense_trajectory_steps + sparse_trajectory_steps;
    XCHECK_GT(trajectory_steps, 0);
    XCHECK_GT(dense_trajectory_time_step, 0.0);

    ControlsType ref_us =
        ControlsType::Zero(trajectory_steps * Mfob::kControlSize);
    StatesType ref_xs = Mfob::FitState(ref_traj);

    Mfob problem(&motion_constraint_params, &veh_geo_params, &veh_drive_params,
                 dense_trajectory_steps, sparse_trajectory_steps,
                 dense_trajectory_time_step, sparse_trajectory_time_step, false,
                 false);

    std::vector<Vec2d> ref_path_points;
    ref_path_points.reserve(ref_traj.size() + 1);
    for (const auto &i : ref_traj) {
        ref_path_points.push_back(i.pos());
    }

    constexpr double kTailLength = 0.2;
    ref_path_points.push_back(
        ref_traj.back().pos() +
        (kTailLength * Vec2d::FastUnitFromAngle(ref_traj.back().theta())));

    const int state_size = trajectory_steps * Mfob::kStateSize;
    std::vector<double> state_deviation_weights(
        static_cast<size_t>(state_size),
        smoother_params.state_deviation_gain());
    const int control_size = trajectory_steps * Mfob::kControlSize;
    std::vector<double> control_penalty_weights(
        static_cast<size_t>(control_size),
        smoother_params.jerk_penalty_gain());
    const double corrected_chi_penalty_gain =
        smoother_params.chi_penalty_gain() *
        std::max(smoother_params.chi_penalty_gain_min_factor(),
                 smoother_params.chi_penalty_speed_gain() *
                     Sqr(ref_traj.front().v()));
    for (size_t i = 0; i < static_cast<size_t>(trajectory_steps); ++i) {
        state_deviation_weights[(i * static_cast<size_t>(Mfob::kStateSize)) + static_cast<size_t>(Mfob::kStateVIndex)] =
            smoother_params.v_deviation_gain();
        control_penalty_weights[(i * static_cast<size_t>(Mfob::kControlSize)) +
                                static_cast<size_t>(Mfob::kControlChiIndex)] =
            corrected_chi_penalty_gain;
    }

    const size_t last_idx = static_cast<size_t>(trajectory_steps - 1);
    state_deviation_weights[(last_idx * static_cast<size_t>(Mfob::kStateSize)) +
                            static_cast<size_t>(Mfob::kStateXIndex)] =
        smoother_params.end_pose_deviation_gain();
    state_deviation_weights[(last_idx * static_cast<size_t>(Mfob::kStateSize)) +
                            static_cast<size_t>(Mfob::kStateYIndex)] =
        smoother_params.end_pose_deviation_gain();
    state_deviation_weights[(last_idx * static_cast<size_t>(Mfob::kStateSize)) +
                            static_cast<size_t>(Mfob::kStateThetaIndex)] =
        smoother_params.end_heading_deviation_gain();

    std::vector<Vec2d> points;
    points.reserve(ref_path_points.size());
    constexpr double kMinSampleDistanceSqr = 0.01;
    points.push_back(ref_path_points.front());
    for (size_t i = 1; i < ref_path_points.size(); ++i) {
        const double distance_sqr =
            ref_path_points[i].DistanceSquareTo(points.back());
        if (distance_sqr < kMinSampleDistanceSqr) {
            continue;
        }
        points.push_back(ref_path_points[i]);
    }

    // std::vector<double> ref_ls(points.size() - 1, offset);
    std::vector<double> ref_path_deviation_gains(points.size() - 1, 1.0);

    problem.AddCost(std::make_unique<ReferenceLineDeviationCost<Mfob>>(
        trajectory_steps, smoother_params.path_gain(),
        smoother_params.end_state_gain(), std::move(ref_ls), points, nullptr,
        std::move(ref_path_deviation_gains),
        "MfobTrajSmooth::ReferenceLineDeviationCost",
        smoother_params.ref_path_deviation_gain()));
    problem.AddCost(std::make_unique<ReferenceStateDeviationCost<Mfob>>(
        std::move(ref_xs), std::move(state_deviation_weights),
        "MfobTrajSmooth::StateRegularization", smoother_params.scale()));
    problem.AddCost(std::make_unique<ReferenceControlDeviationCost<Mfob>>(
        std::move(ref_us), std::move(control_penalty_weights),
        "MfobTrajSmooth::ControlRegularization", smoother_params.scale()));
    constexpr double kCurvatureBufferRatio = 0.8;
    constexpr double kCurvatureRateBufferRatio = 0.8;
    problem.AddCost(std::make_unique<CurvatureCost<Mfob>>(
        ComputeCenterMaxCurvature(veh_geo_params, veh_drive_params) *
            kCurvatureBufferRatio,
        trajectory_steps, trajectory_steps, 1.0,
        "MfobTrajSmooth::MfobCurvatureCost",
        smoother_params.curvature_penalty()));
    problem.AddCost(std::make_unique<MfobCurvatureRateCost<Mfob>>(
        motion_constraint_params.max_psi() * kCurvatureRateBufferRatio,
        "MfobTrajSmooth::MfobCurvatureRateCost",
        smoother_params.curvature_rate_penalty()));
    problem.AddCost(std::make_unique<ForwardSpeedCost<Mfob>>(
        "MfobTrajSmooth::MfobForwardSpeedCost",
        smoother_params.forward_speed_cost_weight()));
    AddStaticBoundaryCost(trajectory_steps, drive_passage, veh_geo_params,
                          smoother_params, &problem);

    constexpr double kAccelerationBufferRatio = 1.0;
    const std::vector<double> accel_cascade_buffers = {0.0};
    const std::vector<double> accel_cascade_gains = {smoother_params.scale()};
    const std::vector<double> decel_cascade_buffers = {0.0};
    const std::vector<double> decel_cascade_gains = {smoother_params.scale()};

    problem.AddCost(std::make_unique<LongitudinalAccelerationCost<Mfob>>(
        motion_constraint_params.max_acceleration() * kAccelerationBufferRatio,
        motion_constraint_params.max_deceleration() * kAccelerationBufferRatio,
        accel_cascade_buffers, accel_cascade_gains, decel_cascade_buffers,
        decel_cascade_gains, "MfobTrajSmooth::MfobLongitudinalAccelerationCost",
        smoother_params.longitudinal_acceleration_cost_weight()));

    DdpOptimizer<Mfob> smoother(plan_id, &problem, dense_trajectory_steps,
                                sparse_trajectory_steps, "mfob_smoother",
                                FLAGS_mfob_trajectory_smoother_verbosity_level,
                                smoother_params.optimizer_params());
    const double dense_longitudinal_lookahead_time =
        smoother_params.pure_pursuit_params()
            .dense_longitudinal_lookahead_time();
    const double sparse_longitudinal_lookahead_time =
        smoother_params.pure_pursuit_params()
            .sparse_longitudinal_lookahead_time();
    const double lateral_lookahead_time =
        smoother_params.pure_pursuit_params().lateral_lookahead_time();
    std::vector<TrajectoryPoint> init_vals = GeneratePurePursuitInitTraj(
        dense_trajectory_steps, sparse_trajectory_steps,
        dense_trajectory_time_step, sparse_trajectory_time_step, problem,
        ref_traj, veh_geo_params, dense_longitudinal_lookahead_time,
        sparse_longitudinal_lookahead_time, lateral_lookahead_time);

    Timer solve_start_time;
    auto output =
        smoother.Solve(init_vals, DdpOptimizer<Mfob>::SolveConfig::Onboard());

    if (!output.ok()) {
        // AD_LWARN(PP) << "trajectory smoother solve failed: "
        //              << output.status().message();
        return ref_traj;
    } else {
        if (smooth_init_cost) {
            *smooth_init_cost = smoother.GetFinalTotalCost();
            // if (smooth_init_cost->value() > 500) {
            //     printf("***");
            // }
        }
    }

    std::vector<TrajectoryPoint> res = std::move(*output);

    // if (PNC_VLOG_IS_ON(4)) {
    //     for (int i = 0; i < ref_traj.size(); i++) {
    //         VLOG(4) << "ref_traj " << i << "  " << ref_traj[i].DebugString();
    //     }
    //     for (int i = 0; i < init_vals.size(); i++) {
    //         VLOG(4) << "pp_traj " << i << "  " << init_vals[i].DebugString();
    //     }
    //     for (int i = 0; i < res.size(); i++) {
    //         VLOG(4) << "res " << i << "  " << res[i].DebugString();
    //     }
    // }

    return res;
}

}  // namespace planning
}  // namespace pnc_x
