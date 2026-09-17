
#include <algorithm>
#include <boost/optional.hpp>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "async/parallel_for.h"
#include "common/timer.h"
#include "optimization/ddp/trajectory_optimizer.h"
#include <absl/cleanup/cleanup.h>
#include <absl/status/status.h>
#include <absl/strings/str_cat.h>
#include <absl/strings/str_format.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>
// #include <gflags/gflags.h>
#include "common/log.h"

#include "common/path_sl_boundary.h"
#include "pncx_constraint.pb.h"
#include "decision/constraint_manager.h"
#include "math/fast_math.h"
#include "math/frenet_common.h"
#include "math/geometry/segment2d.h"
#include "math/piecewise_linear_function.h"
#include "math/util.h"
#include "math/vec.h"
#include "plan/mfob_trajectory_smoother.h"

#include "async/async_util.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "optimization/ddp/ddp_optimizer.h"
#include "optimization/ddp/ddp_optimizer_debug_hook.h"
#include "optimization/ddp/object_cost_util.h"
#include "optimization/ddp/path_time_corridor.h"
#include "optimization/ddp/speed_limit_cost_util.h"
#include "optimization/ddp/static_boundary_cost_util.h"
#include "optimization/ddp/trajectory_optimizer_defs.h"
#include "optimization/ddp/trajectory_optimizer_util.h"
#include "optimization/problem/av_model_helper.h"
#include "optimization/problem/center_line_query_helper.h"
#include "optimization/problem/cost.h"
#include "optimization/problem/curvature_cost.h"
#include "optimization/problem/curvature_deviation_cost.h"
#include "optimization/problem/end_heading_cost.h"
#include "optimization/problem/forward_speed_cost.h"
#include "optimization/problem/intrinsic_jerk_cost.h"
#include "optimization/problem/lateral_acceleration_cost.h"
#include "optimization/problem/longitudinal_acceleration_cost.h"
#include "optimization/problem/mfob_curvature_rate_cost.h"
#include "optimization/problem/mfob_curvature_rate_rate_cost.h"
#include "optimization/problem/mfob_intrinsic_lateral_snap_cost.h"
#include "optimization/problem/mfob_lateral_jerk_cost.h"
#include "optimization/problem/mixed_fourth_order_bicycle.h"
#include "optimization/problem/reference_control_deviation_cost.h"
#include "optimization/problem/reference_line_deviation_cost.h"
#include "optimization/problem/reference_longitudinal_jerk_deviation_cost.h"
#include "optimization/problem/reference_single_state_deviation_cost.h"
#include "optimization/problem/reference_state_deviation_cost.h"
#include "plan/planner_defs.h"
#include "plan/planner_flags.h"
#include "plan/planner_semantic_map_manager.h"
#include "plan/planner_util.h"
#include "plan/trajectory_point.h"
#include "plan/trajectory_util.h"
#include "router/drive_passage.h"
#include "pncx_trajectory.pb.h"
#include "pncx_trajectory_point.pb.h"
#include "util/file_util.h"
#include "util/loop_guard.h"
#include "util/occ_ddp_csv_debug_writer.h"
#include "util/path_util.h"
#include "util/status_macros.h"
#include "util/time_util.h"
#include "util/vehicle_geometry_util.h"
#include "common/planning_macros.h"

#include "optimization/ddp/per_step_cost_recorder_hook.h"

// DEFINE_bool(send_traj_optimizer_result_to_canvas, false,
//             "Whether to send trajectory optimizer result to canvas.");
// DEFINE_int32(traj_opt_canvas_level, 0, "Traj opt canvas level.");
// DEFINE_int32(traj_opt_verbosity_level, 2, "Traj opt verbosity level.");
// DEFINE_double(auto_tuning_gamma, 0.99,
//               "Only used in auto tuning mode, gamma is the discounted
//               rate.");
// DEFINE_bool(enable_ipopt_solver, false,
//             "Whether to enable ipopt solver to be used for being compared
//             with " "ddp optimizer.");
// DEFINE_bool(traj_opt_draw_circle, false, "Whether to draw av model.");
// DECLARE_bool(msd_static_boundary_cost_v2);

bool FLAGS_send_traj_optimizer_result_to_canvas = false;
bool FLAGS_enable_ipopt_solver = false;
bool FLAGS_traj_opt_draw_circle = false;
int FLAGS_traj_opt_canvas_level = 0;
int FLAGS_traj_opt_verbosity_level = 2;
double FLAGS_auto_tuning_gamma = 0.99;
extern bool FLAGS_msd_static_boundary_cost_v2;

namespace pnc_x {
namespace planning {
namespace {

using Mfob = optimizer::Mfob;

bool IsPathPlannerDebugProtoEnabled() {
    static const bool enabled = [] {
        const char* value = std::getenv("PP_PATH_PLANNER_DEBUG_PROTO");
        return value == nullptr || value[0] != '0';
    }();
    return enabled;
}

std::vector<Vec2d> ExtractTrajectoryPositions(
    const std::vector<TrajectoryPoint> &traj_points) {
    std::vector<Vec2d> points;
    points.reserve(traj_points.size());
    for (const auto &pt : traj_points) {
        points.push_back(pt.pos());
    }
    return points;
}

std::string SummarizeTopNamedCosts(const std::vector<NamedCostEntry> &named_costs,
                                   int top_k) {
    if (named_costs.empty() || (top_k <= 0)) {
        return "none";
    }

    std::vector<NamedCostEntry> sorted_costs = named_costs;
    const int count = std::min<int>(top_k, sorted_costs.size());
    std::partial_sort(
        sorted_costs.begin(), sorted_costs.begin() + count, sorted_costs.end(),
        [](const NamedCostEntry &lhs, const NamedCostEntry &rhs) {
            return lhs.value > rhs.value;
        });

    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    for (int i = 0; i < count; ++i) {
        if (i > 0) {
            ss << ", ";
        }
        ss << sorted_costs[i].name << "=" << sorted_costs[i].value;
    }
    return ss.str();
}

std::string BuildDdpValidationFailureMessage(
    const OptimizerSolverDebugHook<Mfob> &solver_debug_hook,
    const absl::Status &validation_status) {
    std::ostringstream ss;
    ss << validation_status.message();
    ss << ", ddp_iterations=" << solver_debug_hook.iterations.size();
    ss << ", init_cost=" << solver_debug_hook.init_costs.cost;
    ss << ", final_cost=" << solver_debug_hook.final_costs.cost;

    if (!solver_debug_hook.final_costs.ddp_costs.empty()) {
        ss << ", top_final_costs=["
           << SummarizeTopNamedCosts(solver_debug_hook.final_costs.ddp_costs, 5)
           << "]";
    } else if (!solver_debug_hook.init_costs.ddp_costs.empty()) {
        ss << ", top_init_costs=["
           << SummarizeTopNamedCosts(solver_debug_hook.init_costs.ddp_costs, 5)
           << "]";
    }

    if (!solver_debug_hook.iterations.empty()) {
        const auto &last_iter = solver_debug_hook.iterations.back();
        ss << ", last_js0=" << last_iter.js0;
        ss << ", last_iter_final_cost=" << last_iter.final_cost;
        if (!last_iter.line_search_costs.empty()) {
            const auto best_cost_it = std::min_element(
                last_iter.line_search_costs.begin(),
                last_iter.line_search_costs.end());
            ss << ", last_line_search_best_cost=" << *best_cost_it;
        }
    }
    return ss.str();
}

void ToDebugProto(const std::vector<TrajectoryPoint> &init_traj,
                  const std::vector<TrajectoryPoint> &solver_init_traj,
                  const std::vector<TrajectoryPoint> &result_traj,
                  const OptimizerSolverDebugHook<Mfob> &solver_debug_hook,
                  const PerStepCostRecorderHook<Mfob>& perstep_hook,
                  const DdpOptimizerDebugProto::SolverInitialTrajectorySource
                      &solver_init_traj_source,
                  TrajectoryOptimizerDebugProto *traj_opt_debug_proto,
                  ThreadPool *thread_pool) {

  DdpOptimizerDebugProto *ddp_debug = traj_opt_debug_proto->mutable_ddp();
  ddp_debug->mutable_init_traj()->Reserve(init_traj.size());
  for (const auto & k : init_traj) {
    k.ToProto(ddp_debug->add_init_traj());
  }

  ddp_debug->mutable_solver_initial_trajectory()->Reserve(
      solver_init_traj.size());
  for (const auto & k : solver_init_traj) {
    k.ToProto(ddp_debug->add_solver_initial_trajectory());
  }
  ddp_debug->set_solver_initial_trajectory_source(solver_init_traj_source);

  ddp_debug->mutable_final_traj()->Reserve(result_traj.size());
  for (const auto & k : result_traj) {
    k.ToProto(ddp_debug->add_final_traj());
  }

  const auto &init_costs = solver_debug_hook.init_costs;
  ddp_debug->mutable_init_costs()->set_cost(init_costs.cost);
  for (int i = 0; i < init_costs.ddp_costs.size(); ++i) {
    TrajectoryOptimizerCost *cost_proto =
        ddp_debug->mutable_init_costs()->add_costs();
    cost_proto->set_name(init_costs.ddp_costs[i].name);
    cost_proto->set_cost(init_costs.ddp_costs[i].value);
  }
  const auto &final_costs = solver_debug_hook.final_costs;
  ddp_debug->mutable_final_costs()->set_cost(final_costs.cost);
  for (int i = 0; i < final_costs.ddp_costs.size(); ++i) {
    TrajectoryOptimizerCost *cost_proto =
        ddp_debug->mutable_final_costs()->add_costs();
    cost_proto->set_name(final_costs.ddp_costs[i].name);
    cost_proto->set_cost(final_costs.ddp_costs[i].value);
  }

  const int num_iters = solver_debug_hook.iterations.size();
  ddp_debug->mutable_iterations()->Reserve(num_iters);
  for (int i = 0; i < num_iters; ++i) {
    ddp_debug->add_iterations();
  }

  ParallelFor(0, num_iters, thread_pool, [&](int i) {
    const auto &iteration = solver_debug_hook.iterations[i];
    DdpOptimizerDebugProto::Iteration *iteration_proto =
        ddp_debug->mutable_iterations()->Mutable(i);
    XCHECK_EQ(iteration.alphas.size(), iteration.line_search_costs.size());
    for (int i = 0; i < iteration.alphas.size(); ++i) {
      iteration_proto->add_line_search_alphas(iteration.alphas[i]);
      iteration_proto->add_line_search_costs(iteration.line_search_costs[i]);
    }
    XCHECK_EQ(iteration.k_s.size(), iteration.stepsize_adjustment_costs.size());
    for (int i = 0; i < iteration.k_s.size(); ++i) {
      iteration_proto->add_step_size_adjustment_ks(iteration.k_s[i]);
      iteration_proto->add_step_size_adjustment_costs(
          iteration.stepsize_adjustment_costs[i]);
    }
    iteration_proto->set_final_cost(iteration.final_cost);
    iteration_proto->set_js0(iteration.js0);
  });

  const auto &rows = perstep_hook.table();
  auto *out = ddp_debug->mutable_per_step_costs();
  out->Reserve(static_cast<int>(rows.size()));
  for (const auto &r : rows) {
    auto *row_pb = out->Add();
    row_pb->set_name(r.name);
    row_pb->set_is_soft(r.is_soft);
    row_pb->set_total(r.total);
    row_pb->mutable_values()->Reserve(static_cast<int>(r.values.size()));
    for (double v : r.values) {
      row_pb->add_values(v);
    }
  }

  ddp_debug->set_num_iters(num_iters);

  for (const auto &response : solver_debug_hook.object_responses) {
    *traj_opt_debug_proto->add_object_responses() = response;
  }
}

absl::Status CheckInputQuality(const TrajectoryOptimizerInput &input) {
    constexpr int kMinTrajectoryLength = 10;
    if (input.trajectory.size() < kMinTrajectoryLength) {
        return absl::FailedPreconditionError(absl::StrFormat(
            "Input trajectory is not long enough: %d time steps.",
            input.trajectory.size()));
    }
    return absl::OkStatus();
}

void AddRegularizersCost(
    const std::vector<TrajectoryPoint> &init_traj,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs) {
    const Mfob::StateType x0 = Mfob::FitInitialState(init_traj);
    const Mfob::ControlsType init_us = Mfob::FitControl(init_traj, x0);
    const Mfob::StatesType init_xs = Mfob::FitState(init_traj);

    std::vector<double> state_regularization_weights(init_xs.size(), 0.0);
    std::vector<double> control_regularization_weights(init_us.size(), 0.0);
    for (int i = 0; i < init_traj.size(); ++i) {
        for (int j = 0; j < Mfob::kStateSize; ++j) {
            state_regularization_weights[i * Mfob::kStateSize + j] =
                cost_weight_params.state_regularization_coeffs().w(j);
        }
        for (int j = 0; j < Mfob::kControlSize; ++j) {
            control_regularization_weights[i * Mfob::kControlSize + j] =
                cost_weight_params.control_regularization_coeffs().w(j);
        }
    }
    costs->emplace_back(std::make_unique<ReferenceStateDeviationCost<Mfob>>(
        init_xs, std::move(state_regularization_weights),
        "MfobReferenceStateDeviationCost: StateRegularization",
        cost_weight_params.state_regularization_coeffs().multiplier(),
        Cost<Mfob>::CostType::MUST_HAVE));
    costs->emplace_back(std::make_unique<ReferenceControlDeviationCost<Mfob>>(
        init_us, std::move(control_regularization_weights),
        "MfobReferenceControlDeviationCost: ControlRegularization",
        cost_weight_params.control_regularization_coeffs().multiplier(),
        Cost<Mfob>::CostType::MUST_HAVE));
}

void AddAccelAndJerkCost(
    double trajectory_time_step,
    const TrajectoryPoint &plan_start_point,
    const DrivePassage &drive_passage,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const MotionConstraintParamsProto &motion_constraint_params,
    const TrajectoryOptimizerValidationParamsProto
        &trajectory_optimizer_validation_params,
    const boost::optional<double> &extra_curb_buffer,
    const boost::optional<double> &lane_width,
    const bool &is_narrow_scene,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs,
    const bool borrow_lane,
    const bool is_near_toll_station) {
    std::vector<double> accel_cascade_buffers;
    std::vector<double> accel_cascade_gains;
    std::vector<double> decel_cascade_buffers;
    std::vector<double> decel_cascade_gains;
    const double borrow_gain =
        borrow_lane ? cost_weight_params.borrow_lane_lonngitudinal_gain() : 1.0;
    for (const auto &cascade :
         cost_weight_params.longitudinal_acceleration_cost_params()
             .accel_cascade()) {
        accel_cascade_buffers.push_back(cascade.buffer());
        accel_cascade_gains.push_back(cascade.gain() * borrow_gain);
    }
    for (const auto &cascade :
         cost_weight_params.longitudinal_acceleration_cost_params()
             .decel_cascade()) {
        decel_cascade_buffers.push_back(cascade.buffer());
        decel_cascade_gains.push_back(cascade.gain());
    }
    constexpr double kAccelerationBufferRatio = 1.0;
    constexpr double kJerkBufferRatio = 0.75;
    const double lateral_gain =
        is_near_toll_station
            ? cost_weight_params.lateral_acceleration_toll_station_gain()
            : 1.0;
    const double lateral_jerk_gain =
        is_near_toll_station
            ? cost_weight_params.lateral_jerk_toll_station_gain()
            : 1.0;

    costs->emplace_back(std::make_unique<LongitudinalAccelerationCost<Mfob>>(
        motion_constraint_params.max_acceleration() * kAccelerationBufferRatio,
        motion_constraint_params.max_deceleration() * kAccelerationBufferRatio,
        std::move(accel_cascade_buffers), std::move(accel_cascade_gains),
        std::move(decel_cascade_buffers), std::move(decel_cascade_gains),
        "MfobLongitudinalAccelerationCost",
        cost_weight_params.longitudinal_acceleration_cost_weight(),
        Cost<Mfob>::CostType::MUST_HAVE));
    costs->emplace_back(std::make_unique<LateralAccelerationCost<Mfob>>(
        true, "MfobLateralAccelerationCost",
        cost_weight_params.lateral_acceleration_cost_weight() * lateral_gain,
        Cost<Mfob>::CostType::MUST_HAVE));
    costs->emplace_back(std::make_unique<IntrinsicJerkCost<Mfob>>(
        motion_constraint_params.max_accel_jerk() * kJerkBufferRatio,
        motion_constraint_params.max_decel_jerk() * kJerkBufferRatio,
        "MfobIntrinsicJerkCost",
        cost_weight_params.intrinsic_jerk_cost_weight() * borrow_gain,
        Cost<Mfob>::CostType::MUST_HAVE));
    costs->emplace_back(std::make_unique<MfobLateralJerkCost<Mfob>>(
        true, "MfobLateralJerkCost",
        cost_weight_params.lateral_jerk_cost_weight() * lateral_jerk_gain,
        Cost<Mfob>::CostType::MUST_HAVE));

    std::vector<std::pair<double, Vec2d>> plan_start_circles;
    std::vector<std::pair<double, Vec2d>> plan_start_mirror_circles;
    for (const auto &circle :
         trajectory_optimizer_vehicle_model_params.circles()) {
        const Vec2d tangent = Vec2d::FastUnitFromAngle(
            plan_start_point.theta() + circle.angle_to_axis());
        plan_start_circles.emplace_back(
            circle.radius(),
            plan_start_point.pos() + circle.dist_to_rac() * tangent);
    }
    for (const auto &circle :
         trajectory_optimizer_vehicle_model_params.mirror_circles()) {
        const Vec2d tangent = Vec2d::FastUnitFromAngle(
            plan_start_point.theta() + circle.angle_to_axis());
        plan_start_mirror_circles.emplace_back(
            circle.radius(),
            plan_start_point.pos() + circle.dist_to_rac() * tangent);
    }
    const double min_mirror_height_avg =
        ComputeMinMaxMirrorAverageHeight(veh_geo_params).first;

    constexpr double kNearbyDistance = 10.0;
    double nearest_dist = kNearbyDistance;
    const std::vector<ImpassableBoundaryInfo> boundaries_info =
        drive_passage.GetImpassableBoundariesInfo(plan_start_point.pos(),
                                                  kNearbyDistance);
    // TODO:(xc)
    // = psmm.GetImpassableBoundariesInfo(plan_start_point.pos(),
    // kNearbyDistance);
    for (const auto &boundary_info : boundaries_info) {
        const bool consider_mirrors =
            boundary_info.height.has_value()
                ? (boundary_info.height.value() > min_mirror_height_avg)
                : trajectory_optimizer_vehicle_model_params
                      .consider_mirrors_by_default();
        for (const auto &circle : plan_start_circles) {
            nearest_dist = std::min(
                nearest_dist,
                boundary_info.segment.DistanceTo(circle.second) - circle.first);
        }
        if (consider_mirrors) {
            for (const auto &circle : plan_start_mirror_circles) {
                nearest_dist =
                    std::min(nearest_dist,
                             boundary_info.segment.DistanceTo(circle.second) -
                                 circle.first);
            }
        }
    }

    double penetration_distance = 0.0;

    const double extra_buffer =
        extra_curb_buffer.has_value() ? *extra_curb_buffer : 0.0;
    if (FLAGS_msd_static_boundary_cost_v2) {
        const auto speed_buffer_plf = PiecewiseLinearFunctionFromProto(
            cost_weight_params.speed_rel_hard_curb_clearance_plf());
        double speed_debug = speed_buffer_plf(plan_start_point.v());

        double penetration_distance_max =
            extra_buffer + speed_buffer_plf(plan_start_point.v());
        penetration_distance =
            std::max(0.0, penetration_distance_max - nearest_dist);

        std::string debug_msg = absl::StrCat(
            "penetration_distance: ", penetration_distance,
            ", extra_buffer: ", extra_buffer,
            ", speed_buffer_plf: ", speed_debug,
            ", nearest_dist: ", nearest_dist,
            ", penetration_distance_max: ", penetration_distance_max);
    }

    const auto penetration_gain_plf = PiecewiseLinearFunctionFromProto(
        cost_weight_params.curb_penetration_lateral_snap_gain_plf());
    const double lateral_snap_gain = penetration_gain_plf(penetration_distance);

    double lateral_snap_gain_extra = 0.0;

    const PiecewiseLinearFunction<double> speed_relative_gain =
        PiecewiseLinearFunctionFromProto(
            cost_weight_params.lateral_snap_speed_gain_plf());
    costs->emplace_back(std::make_unique<MfobIntrinsicLateralSnapCost<Mfob>>(
        "MfobIntrinsicLateralSnapCost",
        (lateral_snap_gain + lateral_snap_gain_extra) *
            cost_weight_params.intrinsic_lateral_snap_weight() *
            speed_relative_gain(plan_start_point.v()),
        Cost<Mfob>::CostType::MUST_HAVE));
}

void AddCurvatureCost(
    const SamplingTrajectoryInfo &sampling_trajectory_info,
    const TrajectoryPoint &plan_start_point,
    const ConstraintManager &constraint_manager,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        &leading_trajs,
    const DrivePassage &drive_passage,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const VehicleDriveParamsProto &vehicle_drive_params,
    const MotionConstraintParamsProto &motion_constraint_params,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs,
    bool &is_kappa_inhibit_scene) {
    int curvature_limit_index = 0;
    if ((sampling_trajectory_info.dense_trajectory_steps *
             sampling_trajectory_info.dense_trajectory_time_step >
         kCurvatureLimitRange)) {
        curvature_limit_index = static_cast<int>(
            kCurvatureLimitRange /
            sampling_trajectory_info.dense_trajectory_time_step);
    } else {
        curvature_limit_index =
            static_cast<int>(
                (kCurvatureLimitRange -
                 sampling_trajectory_info.dense_trajectory_steps *
                     sampling_trajectory_info.dense_trajectory_time_step) /
                sampling_trajectory_info.sparse_trajectory_time_step) +
            sampling_trajectory_info.dense_trajectory_steps;
    }

    constexpr double kCurvatureBufferRatio = 0.98;
    constexpr double kCurvatureRateBufferRatio = 0.75;
    constexpr double kUTurnCurvatureBufferRatio = 1.5;
    constexpr double kUTurnCurvatureRateBufferRatio = 1.2;
    const bool is_uturn_mode =
        drive_passage.GetEgoTurnType() == ads_x::planning::U_TURN;
    const double curvature_buffer_ratio =
        is_uturn_mode ? kUTurnCurvatureBufferRatio : kCurvatureBufferRatio;
    const double curvature_rate_buffer_ratio =
        is_uturn_mode ? kUTurnCurvatureRateBufferRatio
                      : kCurvatureRateBufferRatio;

    const double acc_standstill_standoff =
        cost_weight_params.object_cost_params().acc_standstill_standoff();

    const auto &spacetime_trajs = *st_planner_object_traj.trajectories;

    double distance_to_intersection =
        drive_passage.GetDistanceToIntersection(plan_start_point.pos());
    bool is_intersection =
        distance_to_intersection < veh_geo_params.front_edge_to_center();

    double curvature_scale = 1.0;
    if (plan_start_point.v() < 2.0 && !is_intersection) {
        const auto &stop_lines = constraint_manager.StopLine();
        double first_stop_line_s = std::numeric_limits<double>::infinity();
        for (const auto &stop_line : stop_lines) {
            first_stop_line_s = std::min(
                first_stop_line_s, stop_line.s() - stop_line.standoff() -
                                       veh_geo_params.front_edge_to_center());
        }
        if (std::abs(first_stop_line_s) < 3.0) {
            curvature_scale = 500.0;
            is_kappa_inhibit_scene = true;
        }

        for (const auto &traj : spacetime_trajs) {
            const bool is_leading =
                leading_trajs.find(std::string(traj.traj_id())) !=
                leading_trajs.end();
            if (is_leading && (traj.pose().v() < 1.0)) {
                const Polygon2d &contour = traj.contour();
                const auto frenet_box_or =
                    drive_passage.QueryFrenetBoxAtContour(contour);
                if (!frenet_box_or.ok()) {
                    continue;
                }
                if (frenet_box_or->s_min - acc_standstill_standoff -
                        veh_geo_params.front_edge_to_center() <
                    10.0) {
                    curvature_scale = 500.0;
                    is_kappa_inhibit_scene = true;
                }
            }
        }
    }

    int free_index = 0;
    if ((sampling_trajectory_info.dense_trajectory_steps *
             sampling_trajectory_info.dense_trajectory_time_step >
         kTrajectoryTimeHorizon)) {
        free_index = static_cast<int>(
            kTrajectoryTimeHorizon /
            sampling_trajectory_info.dense_trajectory_time_step);
    } else {
        free_index =
            static_cast<int>(
                (kTrajectoryTimeHorizon -
                 sampling_trajectory_info.dense_trajectory_steps *
                     sampling_trajectory_info.dense_trajectory_time_step) /
                sampling_trajectory_info.sparse_trajectory_time_step) +
            sampling_trajectory_info.dense_trajectory_steps;
    }

    costs->emplace_back(std::make_unique<CurvatureCost<Mfob>>(
        ComputeCenterMaxCurvature(veh_geo_params, vehicle_drive_params) *
            curvature_buffer_ratio,
        curvature_limit_index, free_index, curvature_scale, "MfobCurvatureCost",
        cost_weight_params.curvature_cost_weight(),
        Cost<Mfob>::CostType::MUST_HAVE));
    costs->emplace_back(std::make_unique<MfobCurvatureRateCost<Mfob>>(
        motion_constraint_params.max_psi() * curvature_rate_buffer_ratio,
        "MfobCurvatureRateCost",
        cost_weight_params.curvature_rate_cost_weight(),
        Cost<Mfob>::CostType::MUST_HAVE));
    costs->emplace_back(std::make_unique<MfobCurvatureRateRateCost<Mfob>>(
        motion_constraint_params.max_chi(), "MfobCurvatureRateRateCost",
        cost_weight_params.curvature_rate_rate_cost_weight(),
        Cost<Mfob>::CostType::MUST_HAVE));
}


/**
 *  帧间吸引cost: 参考历史轨迹的 jerk / s / kappa
 *
 *  构造两类代价函数：
 *  1. 纵向 jerk 偏差代价
 *  2. 横向曲率偏差代价
 *      根据不同场景（路口、异常区域），动态调整代价权重
 */
void AddImmediateFutureCost(
    const SamplingTrajectoryInfo &sampling_trajectory_info,

    const std::vector<TrajectoryPoint> &prev_traj,
    double v_now,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const DrivePassage &drive_passage,
    const ApolloTrajectoryPointProto &plan_start_point,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs,
    const int plan_id) {
    if (prev_traj.size() < 2) return;
    const Mfob::StateType x0 = Mfob::FitInitialState(prev_traj);
    const Mfob::ControlsType ref_us = Mfob::FitControl(prev_traj, x0);
    const Mfob::StatesType ref_xs = Mfob::FitState(prev_traj);

    std::vector<double> ref_jerk;
    std::vector<double> ref_s;
    std::vector<double> ref_kappa;
    const int trajectory_steps =
        sampling_trajectory_info.dense_trajectory_steps +
        sampling_trajectory_info.sparse_trajectory_steps;
    ref_jerk.reserve(trajectory_steps);
    ref_s.reserve(trajectory_steps);
    ref_kappa.reserve(trajectory_steps);
    for (int i = 0; i < trajectory_steps; ++i) {
        ref_jerk.push_back(Mfob::j(ref_us, i));
        ref_s.push_back(Mfob::s(ref_xs, i));
        ref_kappa.push_back(Mfob::kappa(ref_xs, i));
    }

    constexpr double kImmediateJGain = 0.1;
    const PiecewiseLinearFunction<double> lon_weight_plf =
        PiecewiseLinearFunctionFromProto(
            cost_weight_params.immediate_future_cost_params().lon_weight_plf());
    std::vector<double> lon_weights;
    lon_weights.reserve(trajectory_steps);
    XCHECK_EQ(prev_traj.size(), trajectory_steps);
    for (int i = 0; i < trajectory_steps; ++i) {
        const auto &prev_traj_point = prev_traj[i];
        const double lon_weight_plf_t = lon_weight_plf(prev_traj_point.t());
        lon_weights.push_back(kImmediateJGain * lon_weight_plf_t);
    }
    costs->push_back(
        std::make_unique<ReferenceLongitudinalJerkDeviationCost<Mfob>>(
            std::move(ref_jerk), std::move(lon_weights),
            "MfobReferenceLongitudinalJerkDeviationCost: ImmediateFuture",
            cost_weight_params.immediate_future_cost_weight(),
            Cost<Mfob>::CostType::GROUP_IMMEDIATE_FUTURE));

    constexpr double kCurvatureDeviationCostWeight = 500.0;
    const PiecewiseLinearFunction<double> lat_weight_plf =
        PiecewiseLinearFunctionFromProto(
            cost_weight_params.immediate_future_cost_params().lat_weight_plf());
    const PiecewiseLinearFunction<double> intersection_lat_weight_plf =
        PiecewiseLinearFunctionFromProto(
            cost_weight_params.immediate_future_cost_params()
                .intersection_lat_weight_plf());

    std::vector<double> lat_weights;
    lat_weights.reserve(trajectory_steps);

    int cur_station_index =
        drive_passage
            .FindNearestStationIndex(Vec2d(plan_start_point.path_point().x(),
                                           plan_start_point.path_point().y()))
            .value();
    const Station &cur_station =
        drive_passage.station(StationIndex(cur_station_index));
    if (cur_station.station_info().is_in_intersection &&
        ((cur_station.station_info().turn_type ==
             ads_x::planning::TurnType::LEFT_TURN) ||
         (cur_station.station_info().turn_type ==
             ads_x::planning::TurnType::RIGHT_TURN))) {
        for (int i = 0; i < trajectory_steps; ++i) {
            const double t =
                i <= sampling_trajectory_info.dense_trajectory_steps
                    ? static_cast<double>(
                          i *
                          sampling_trajectory_info.dense_trajectory_time_step)
                    : static_cast<double>(
                          sampling_trajectory_info.dense_trajectory_steps *
                              sampling_trajectory_info
                                  .dense_trajectory_time_step +
                          (i -
                           sampling_trajectory_info.dense_trajectory_steps) *
                              sampling_trajectory_info
                                  .sparse_trajectory_time_step);
            lat_weights.push_back(
                intersection_lat_weight_plf(static_cast<double>(t)));
        }
    } else {
        for (int i = 0; i < trajectory_steps; ++i) {
            const double t =
                i <= sampling_trajectory_info.dense_trajectory_steps
                    ? static_cast<double>(
                          i *
                          sampling_trajectory_info.dense_trajectory_time_step)
                    : static_cast<double>(
                          sampling_trajectory_info.dense_trajectory_steps *
                              sampling_trajectory_info
                                  .dense_trajectory_time_step +
                          (i -
                           sampling_trajectory_info.dense_trajectory_steps) *
                              sampling_trajectory_info
                                  .sparse_trajectory_time_step);
            lat_weights.push_back(lat_weight_plf(static_cast<double>(t)));
        }
    }

    double MaxAbnormalGain =
        cost_weight_params.immediate_future_cost_params().abnormal_max_gain();
    double MinAbnormalGain =
        cost_weight_params.immediate_future_cost_params().abnormal_min_gain();
    double KAlpha = cost_weight_params.immediate_future_cost_params()
                        .abnormal_gain_factor();
    double AbnormalGain = 1.0;
    const int abnormal_time_step = drive_passage.GetAbnormalStep();
    if (drive_passage.GetIsChangeAbnormal()) {
        AbnormalGain =
            (MaxAbnormalGain - MinAbnormalGain) *
                std::exp(-KAlpha *
                         (static_cast<double>(abnormal_time_step) - 1.0)) +
            MinAbnormalGain;
    } else {
        AbnormalGain = 1.0;
    }

    constexpr double kPlanStartSpeedThreshold = 5.0/3.6;
    if (plan_start_point.v() > kPlanStartSpeedThreshold) {
        costs->push_back(std::make_unique<CurvatureDeviationCost<Mfob>>(
            ref_s, ref_kappa, std::move(lat_weights),
            "MfobCurvatureDeviationCost: ImmediateFuture",
            cost_weight_params
                    .curvature_deviation_immediate_future_cost_weight() *
                kCurvatureDeviationCostWeight * AbnormalGain));
    }
}

void GetReferencePathGainForRouteDestinationStopLine(
    const DrivePassage &drive_passage,
    const ConstraintManager &constraint_manager,
    const VehicleGeometryParamsProto &veh_geo_params,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    std::vector<double> *ref_path_deviation_gains,
    std::vector<double> *ref_heading_deviation_gains) {
    const auto &stop_lines = constraint_manager.StopLine();
    XCHECK_EQ(ref_path_deviation_gains->size(),
              ref_heading_deviation_gains->size());

    boost::optional<double> route_destination_stop_line_s;
    for (const auto &stop_line : stop_lines) {
        if (stop_line.source().type_case() ==
            SourceProto::TypeCase::kRouteDestination) {
            route_destination_stop_line_s =
                stop_line.s() - stop_line.standoff() -
                veh_geo_params.front_edge_to_center();
            break;
        }
    }
    if (!route_destination_stop_line_s.has_value()) {
        return;
    }

    const int count = ref_path_deviation_gains->size();
    const StationIndex route_destination_index =
        drive_passage.FindNearestStationIndexAtS(
            *route_destination_stop_line_s);
    for (int k = route_destination_index.value(); k < count; ++k) {
        (*ref_path_deviation_gains)[k] =
            cost_weight_params.reference_path_cost_weight()
                .destination_path_gain();
        (*ref_heading_deviation_gains)[k] =
            cost_weight_params.reference_path_cost_weight()
                .destination_theta_gain();
    }
}

bool IsDetourRequired(
    const DrivePassage &drive_passage,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        &leading_trajs,
    const ApolloTrajectoryPointProto &plan_start_point,
    const VehicleGeometryParamsProto &veh_geo_params) {
    constexpr double kSafetyBuffer = 0.3;
    constexpr double kMinForwardCheckDistance = 50.0;
    constexpr double kMinForwardSpeedFactor = 3.0;
    const double ego_half_width = veh_geo_params.width() / 2.0;
    const double plan_start_s = plan_start_point.path_point().s();
    const double plan_start_v = plan_start_point.v();
    for (const auto &obj_traj : *st_planner_object_traj.trajectories) {
        ASSIGN_OR_CONTINUE(
            const auto obj_frenet_box,
            drive_passage.QueryFrenetBoxAtContour(obj_traj.contour()));
        if (leading_trajs.find(std::string(obj_traj.traj_id())) !=
            leading_trajs.end()) {
            continue;
        }
        if ((obj_frenet_box.center_s() < plan_start_s) ||
            (obj_frenet_box.center_s() >
                std::max(kMinForwardSpeedFactor * plan_start_v, kMinForwardCheckDistance))) {
            continue;
        }

        if ((std::abs(obj_frenet_box.l_min) < ego_half_width + kSafetyBuffer) ||
            (std::abs(obj_frenet_box.l_max) < ego_half_width + kSafetyBuffer)) {
            return true;
        }
    }
    return false;
}

void GetReferencePathGainForVirtualNormalLane(
    const DrivePassage &drive_passage,
    const VehicleGeometryParamsProto &veh_geo_params,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const ApolloTrajectoryPointProto &plan_start_point,
    const LaneChangeStage lc_stage,
    const NudgeInfos &nudge_info,
    const bool is_detour_required,
    std::vector<double> *ref_path_deviation_gains,
    std::vector<double> *ref_heading_deviation_gains,
    bool &virtual_normal_gain) {
    std::vector<int> change_indexs = drive_passage.change_index();

    if (!((lc_stage == LaneChangeStage::LCS_NONE) && !change_indexs.empty())) {
        return;
    }

    const bool detour_required =
        !nudge_info.nudgeInfos.empty() || is_detour_required;
    if (detour_required) {
        return;
    }

    int index =
        drive_passage
            .FindNearestStationIndex(Vec2d(plan_start_point.path_point().x(),
                                           plan_start_point.path_point().y()))
            .value();

    double plan_start_s = plan_start_point.path_point().s();

    const auto dp_size = drive_passage.size();
    bool first_normal_to_virtual = false;
    int first_normal_to_virtual_index = index;
    double first_normal_to_virtual_s = plan_start_s;
    bool first_virtual_to_normal = false;
    double first_virtual_to_normal_s = plan_start_s;
    int first_virtual_to_normal_index = index;

    for (int i = 0; i < change_indexs.size(); i++) {
        const Station &cur_station =
            drive_passage.station(StationIndex(change_indexs[i]));
        const Station &pre_station =
            drive_passage.station(StationIndex(change_indexs[i] - 1));

        constexpr double kIntersectionPathGainFactor = 2.0;
        if (cur_station.station_info().is_in_intersection &&
            ((cur_station.station_info().turn_type ==
                 ads_x::planning::TurnType::LEFT_TURN) ||
             (cur_station.station_info().turn_type ==
                 ads_x::planning::TurnType::RIGHT_TURN))) {
            (*ref_path_deviation_gains)[change_indexs[i]] = kIntersectionPathGainFactor * 0.1;
            (*ref_heading_deviation_gains)[change_indexs[i]] = 0.1;
        }

        if (((pre_station.station_info().turn_type ==
                 ads_x::planning::TurnType::NO_TURN) &&
             (cur_station.station_info().turn_type !=
                 ads_x::planning::TurnType::NO_TURN)) ||
            ((pre_station.station_info().split_topo ==
                 ads_x::planning::SplitTopology::TOPOLOGY_SPLIT_NONE) &&
             (cur_station.station_info().split_topo !=
                 ads_x::planning::SplitTopology::TOPOLOGY_SPLIT_NONE))) {
            first_normal_to_virtual = true;
            first_normal_to_virtual_s =
                drive_passage.station(StationIndex(change_indexs[i]))
                    .accumulated_s();
            first_normal_to_virtual_index = change_indexs[i];
        } else if (((pre_station.station_info().turn_type !=
                        ads_x::planning::TurnType::NO_TURN) &&
                    (cur_station.station_info().turn_type ==
                        ads_x::planning::TurnType::NO_TURN)) ||
                   ((pre_station.station_info().split_topo !=
                        ads_x::planning::SplitTopology::TOPOLOGY_SPLIT_NONE) &&
                    (cur_station.station_info().split_topo ==
                        ads_x::planning::SplitTopology::TOPOLOGY_SPLIT_NONE))) {
            first_virtual_to_normal = true;
            first_virtual_to_normal_s =
                drive_passage.station(StationIndex(change_indexs[i]))
                    .accumulated_s();
            first_virtual_to_normal_index = change_indexs[i];
        }

        if (first_virtual_to_normal && first_normal_to_virtual) {
            break;
        }
    }

    virtual_normal_gain = first_normal_to_virtual || first_virtual_to_normal;

    const int count = ref_path_deviation_gains->size();

    if (first_normal_to_virtual && !first_virtual_to_normal) {
        for (int i = index; (i < first_normal_to_virtual_index) && (i < count);
             i++) {
            if (first_normal_to_virtual_s -
                    drive_passage.station(StationIndex(i)).accumulated_s() <
                kNormalToVirtual) {
                (*ref_path_deviation_gains)[i] =
                    2.0 * cost_weight_params.reference_path_cost_weight()
                              .intersection_path_gain();
                (*ref_heading_deviation_gains)[i] =
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_theta_gain();
            }
        }
    } else if (first_normal_to_virtual && first_virtual_to_normal &&
               (first_normal_to_virtual_s < first_virtual_to_normal_s)) {
        for (int i = index; (i < first_normal_to_virtual_index) && (i < count);
             i++) {
            if (first_normal_to_virtual_s -
                    drive_passage.station(StationIndex(i)).accumulated_s() <
                kNormalToVirtual) {
                (*ref_path_deviation_gains)[i] =
                    2.0 * cost_weight_params.reference_path_cost_weight()
                              .intersection_path_gain();
                (*ref_heading_deviation_gains)[i] =
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_theta_gain();
            }
        }
        for (int i = first_virtual_to_normal_index; i < count; i++) {
            if (drive_passage.station(StationIndex(i)).accumulated_s() -
                    first_virtual_to_normal_s <
                kVirtualToNormal) {
                (*ref_path_deviation_gains)[i] =
                    2.0 * cost_weight_params.reference_path_cost_weight()
                              .intersection_path_gain();
                (*ref_heading_deviation_gains)[i] =
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_theta_gain();
            }
        }
    } else if (!first_normal_to_virtual && first_virtual_to_normal) {
        for (int i = first_virtual_to_normal_index; i < count; i++) {
            if (drive_passage.station(StationIndex(i)).accumulated_s() -
                    first_virtual_to_normal_s <
                kVirtualToNormal) {
                (*ref_path_deviation_gains)[i] =
                    0.8 *

                    2.0 *
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_path_gain();
                (*ref_heading_deviation_gains)[i] =
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_theta_gain();
            }
        }
    } else if (first_normal_to_virtual && first_virtual_to_normal &&
               (first_normal_to_virtual_s > first_virtual_to_normal_s)) {
        for (int i = first_virtual_to_normal_index; i < count; i++) {
            if (drive_passage.station(StationIndex(i)).accumulated_s() -
                    first_virtual_to_normal_s <
                kVirtualToNormal) {
                (*ref_path_deviation_gains)[i] =
                    2.0 * cost_weight_params.reference_path_cost_weight()
                              .intersection_path_gain();
                (*ref_heading_deviation_gains)[i] =
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_theta_gain();
            }
        }
    } else {
        virtual_normal_gain = false;
    }
}

std::vector<pnc_x::planning::ChangIndexInfo> GetSplitAndMergeInfo(
    const DrivePassage &drive_passage,
    const ApolloTrajectoryPointProto &plan_start_point) {
    std::vector<int> change_indexs = drive_passage.change_index();
    int index =
        drive_passage
            .FindNearestStationIndex(Vec2d(plan_start_point.path_point().x(),
                                           plan_start_point.path_point().y()))
            .value();

    std::vector<pnc_x::planning::ChangIndexInfo> result;

    for (int i = 1; i < drive_passage.size(); i++) {
        pnc_x::planning::ChangIndexInfo Info;
        Info.start_point_index = index;
        const Station &cur_station = drive_passage.station(StationIndex(i));
        const Station &pre_station = drive_passage.station(StationIndex(i - 1));

        if ((pre_station.station_info().station_split_info !=
                StationSplitInfo::NO_SPLIT) &&
            (pre_station.lane_id() != cur_station.lane_id())) {
            Info.topo_action =
                pnc_x::planning::ChangIndexInfo::TopoActionType::TYPE_SPLIT;
            Info.key_point_index = i;
            Info.key_point_s =
                drive_passage.station(StationIndex(i)).accumulated_s();
            result.push_back(Info);
        } else if ((pre_station.station_info().merge_topo !=
                       ads_x::planning::MergeTopology::TOPOLOGY_MERGE_NONE) &&
                   (cur_station.station_info().merge_topo ==
                       ads_x::planning::MergeTopology::TOPOLOGY_MERGE_NONE)) {
            Info.topo_action =
                pnc_x::planning::ChangIndexInfo::TopoActionType::TYPE_MERGE;
            Info.key_point_index = i;
            Info.key_point_s =
                drive_passage.station(StationIndex(i)).accumulated_s();
            result.push_back(Info);
        }
    }

    return result;
}

std::tuple<bool, int, double, bool, int, double, int> GetTurnInfo(
    const DrivePassage &drive_passage,
    const ApolloTrajectoryPointProto &plan_start_point) {
    std::vector<int> change_indexs = drive_passage.change_index();
    int index =
        drive_passage
            .FindNearestStationIndex(Vec2d(plan_start_point.path_point().x(),
                                           plan_start_point.path_point().y()))
            .value();

    double plan_start_s = plan_start_point.path_point().s();

    const auto dp_size = drive_passage.size();
    bool first_normal_to_virtual = false;
    int first_normal_to_virtual_index = index;
    double first_normal_to_virtual_s = plan_start_s;
    bool first_virtual_to_normal = false;
    double first_virtual_to_normal_s = plan_start_s;
    int first_virtual_to_normal_index = index;

    for (int i = 0; i < change_indexs.size(); i++) {
        const Station &cur_station =
            drive_passage.station(StationIndex(change_indexs[i]));
        const Station &pre_station =
            drive_passage.station(StationIndex(change_indexs[i] - 1));

        if (((pre_station.station_info().turn_type ==
                 ads_x::planning::TurnType::NO_TURN) &&
             (cur_station.station_info().turn_type ==
                 ads_x::planning::TurnType::LEFT_TURN)) ||
            ((pre_station.station_info().turn_type ==
                 ads_x::planning::TurnType::NO_TURN) &&
             (cur_station.station_info().turn_type ==
                 ads_x::planning::TurnType::RIGHT_TURN))) {
            first_normal_to_virtual = true;
            first_normal_to_virtual_s =
                drive_passage.station(StationIndex(change_indexs[i]))
                    .accumulated_s();
            first_normal_to_virtual_index = change_indexs[i];
        } else if (((pre_station.station_info().turn_type ==
                        ads_x::planning::TurnType::LEFT_TURN) &&
                    (cur_station.station_info().turn_type ==
                        ads_x::planning::TurnType::NO_TURN)) ||
                   ((pre_station.station_info().turn_type ==
                        ads_x::planning::TurnType::RIGHT_TURN) &&
                    (cur_station.station_info().turn_type ==
                        ads_x::planning::TurnType::NO_TURN))) {
            first_virtual_to_normal = true;
            first_virtual_to_normal_s =
                drive_passage.station(StationIndex(change_indexs[i]))
                    .accumulated_s();
            first_virtual_to_normal_index = change_indexs[i];
        }

        if (first_virtual_to_normal && first_normal_to_virtual) {
            break;
        }
    }

    return std::tuple<bool, int, double, bool, int, double, int>(
        first_normal_to_virtual, first_normal_to_virtual_index,
        first_normal_to_virtual_s, first_virtual_to_normal,
        first_virtual_to_normal_s, first_virtual_to_normal_index, index);
}

void ChangeReferencePathGainForMergeAndSplit(
    const DrivePassage &drive_passage,
    const std::vector<pnc_x::planning::ChangIndexInfo> &change_info,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const ApolloTrajectoryPointProto &plan_start_point,
    std::vector<double> *ref_path_deviation_gains,
    std::vector<double> *ref_heading_deviation_gains,
    bool *virtual_normal_gain) {
    if ((virtual_normal_gain == nullptr) || (ref_path_deviation_gains == nullptr) ||
        (ref_heading_deviation_gains == nullptr)) {
        return;
    }
    *virtual_normal_gain = false;
    if (change_info.empty()) {
        *virtual_normal_gain = false;
        return;
    }

    const int count = ref_path_deviation_gains->size();
    const double start_point_s =
        drive_passage
            .station(StationIndex(change_info.front().start_point_index))
            .accumulated_s();
    const double kInvolvedChangePointLength =
        std::fmax(kMinInvolvedChangePointLength,
                  kMinInvolvedChangePointTime * plan_start_point.v());
    for (const auto &one_change_info : change_info) {
        if ((one_change_info.topo_action ==
                pnc_x::planning::ChangIndexInfo::TopoActionType::TYPE_SPLIT) &&
            (std::abs(start_point_s - one_change_info.key_point_s) <
                kInvolvedChangePointLength)) {
            *virtual_normal_gain = true;
            for (int i = one_change_info.start_point_index;
                 (i < count) && (i < one_change_info.key_point_index); ++i) {
                if (one_change_info.key_point_s -
                        drive_passage.station(StationIndex(i)).accumulated_s() <
                    kShortSegmentLength) {
                    (*ref_path_deviation_gains)[i] = KRefPathDeviationGains;
                    (*ref_heading_deviation_gains)[i] =
                        KRefPathHeadingDeviationGains;
                }
            }
            for (int i = one_change_info.key_point_index; i < count; ++i) {
                if (drive_passage.station(StationIndex(i)).accumulated_s() -
                        one_change_info.key_point_s <
                    kLongSegmentLength) {
                    (*ref_path_deviation_gains)[i] = KRefPathDeviationGains;
                    (*ref_heading_deviation_gains)[i] =
                        KRefPathHeadingDeviationGains;
                } else {
                    break;
                }
            }

        } else if ((one_change_info.topo_action ==
                       pnc_x::planning::ChangIndexInfo::TopoActionType::
                           TYPE_MERGE) &&
                   (std::abs(start_point_s - one_change_info.key_point_s) <
                       kInvolvedChangePointLength)) {
            *virtual_normal_gain = true;
            for (int i = one_change_info.start_point_index;
                 (i < count) && (i < one_change_info.key_point_index); ++i) {
                if (one_change_info.key_point_s -
                        drive_passage.station(StationIndex(i)).accumulated_s() <
                    kLongSegmentLength) {
                    (*ref_path_deviation_gains)[i] = KRefPathDeviationGains;
                    (*ref_heading_deviation_gains)[i] =
                        KRefPathHeadingDeviationGains;
                }
            }
            for (int i = one_change_info.key_point_index; i < count; ++i) {
                if (drive_passage.station(StationIndex(i)).accumulated_s() -
                        one_change_info.key_point_s <
                    kShortSegmentLength) {
                    (*ref_path_deviation_gains)[i] = KRefPathDeviationGains;
                    (*ref_heading_deviation_gains)[i] =
                        KRefPathHeadingDeviationGains;
                } else {
                    break;
                }
            }
        }
    }
}

void ChangeReferencePathGainForRoam(
    const DrivePassage &drive_passage,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const ApolloTrajectoryPointProto &plan_start_point,
    std::vector<double> *ref_path_deviation_gains,
    std::vector<double> *ref_heading_deviation_gains,
    bool *virtual_normal_gain) {
    if ((virtual_normal_gain == nullptr) || (ref_path_deviation_gains == nullptr) ||
        (ref_heading_deviation_gains == nullptr)) {
        return;
    }
    // *virtual_normal_gain = false;

    int start_point_index =
        drive_passage
            .FindNearestStationIndex(Vec2d(plan_start_point.path_point().x(),
                                           plan_start_point.path_point().y()))
            .value();

    const int count = ref_path_deviation_gains->size();
    const double start_point_s =
        drive_passage.station(StationIndex(start_point_index)).accumulated_s();

    const double kInvolvedChangePointLength =
        std::fmax(kMinInvolvedChangePointLength,
                  kMinInvolvedChangePointTime * plan_start_point.v());

    *virtual_normal_gain = true;
    for (int i = start_point_index; i < count; ++i) {
        if (drive_passage.station(StationIndex(i)).accumulated_s() <
            kInvolvedChangePointLength) {
            (*ref_path_deviation_gains)[i] = KRefPathDeviationGains;
            (*ref_heading_deviation_gains)[i] = KRefPathHeadingDeviationGains;
        } else {
            break;
        }
    }
}

void ChangeReferencePathGain(
    const DrivePassage &drive_passage,
    std::tuple<bool, int, double, bool, int, double, int> &change_info,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    std::vector<double> *ref_path_deviation_gains,
    std::vector<double> *ref_heading_deviation_gains,
    bool &virtual_normal_gain) {
    bool first_normal_to_virtual = std::get<0>(change_info);
    int first_normal_to_virtual_index = std::get<1>(change_info);
    double first_normal_to_virtual_s = std::get<2>(change_info);
    bool first_virtual_to_normal = std::get<3>(change_info);
    double first_virtual_to_normal_s = std::get<4>(change_info);
    int first_virtual_to_normal_index = std::get<5>(change_info);
    int index = std::get<6>(change_info);

    virtual_normal_gain = first_normal_to_virtual || first_virtual_to_normal;

    const int count = ref_path_deviation_gains->size();

    if (first_normal_to_virtual && !first_virtual_to_normal) {
        for (int i = index; (i < first_normal_to_virtual_index) && (i < count);
             i++) {
            if (first_normal_to_virtual_s -
                    drive_passage.station(StationIndex(i)).accumulated_s() <
                kNormalToVirtual) {
                (*ref_path_deviation_gains)[i] =
                    2.0 * cost_weight_params.reference_path_cost_weight()
                              .intersection_path_gain();
                (*ref_heading_deviation_gains)[i] =
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_theta_gain();
            }
        }
    } else if (first_normal_to_virtual && first_virtual_to_normal &&
               (first_normal_to_virtual_s < first_virtual_to_normal_s)) {
        for (int i = index; (i < first_normal_to_virtual_index) && (i < count);
             i++) {
            if (first_normal_to_virtual_s -
                    drive_passage.station(StationIndex(i)).accumulated_s() <
                kNormalToVirtual) {
                (*ref_path_deviation_gains)[i] =
                    2.0 * cost_weight_params.reference_path_cost_weight()
                              .intersection_path_gain();
                (*ref_heading_deviation_gains)[i] =
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_theta_gain();
            }
        }
        for (int i = first_virtual_to_normal_index; i < count; i++) {
            if ((drive_passage.station(StationIndex(i)).accumulated_s() -
                        first_virtual_to_normal_s <
                    kVirtualToNormal) &&
                (drive_passage.station(StationIndex(i))
                        .station_info()
                        .turn_type == ads_x::planning::TurnType::NO_TURN)) {
                (*ref_path_deviation_gains)[i] =
                    2.0 * cost_weight_params.reference_path_cost_weight()
                              .intersection_path_gain();
                (*ref_heading_deviation_gains)[i] =
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_theta_gain();
            }
        }
    } else if (!first_normal_to_virtual && first_virtual_to_normal) {
        for (int i = first_virtual_to_normal_index; i < count; i++) {
            if ((drive_passage.station(StationIndex(i)).accumulated_s() -
                        first_virtual_to_normal_s <
                    kVirtualToNormal) &&
                (drive_passage.station(StationIndex(i))
                        .station_info()
                        .turn_type == ads_x::planning::TurnType::NO_TURN)) {
                (*ref_path_deviation_gains)[i] =
                    1.0 *

                    2.0 *
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_path_gain();
                (*ref_heading_deviation_gains)[i] =
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_theta_gain();
            }
        }
    } else if (first_normal_to_virtual && first_virtual_to_normal &&
               (first_normal_to_virtual_s > first_virtual_to_normal_s)) {
        for (int i = first_virtual_to_normal_index; i < count; i++) {
            if (drive_passage.station(StationIndex(i)).accumulated_s() -
                    first_virtual_to_normal_s <
                kVirtualToNormal) {
                (*ref_path_deviation_gains)[i] =
                    2.0 * cost_weight_params.reference_path_cost_weight()
                              .intersection_path_gain();
                (*ref_heading_deviation_gains)[i] =
                    cost_weight_params.reference_path_cost_weight()
                        .intersection_theta_gain();
            }
        }
    } else {
        virtual_normal_gain = false;
    }
}

void GetReferencePathGainForSplit(
    const DrivePassage &drive_passage,
    const NudgeInfos &nudge_info,
    const VehicleGeometryParamsProto &veh_geo_params,
    const bool is_detour_required,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const ApolloTrajectoryPointProto &plan_start_point,
    const LaneChangeStage lc_stage,
    std::vector<double> *ref_path_deviation_gains,
    std::vector<double> *ref_heading_deviation_gains,
    bool *virtual_normal_gain) {
    std::vector<int> change_indexs = drive_passage.change_index();
    if ((lc_stage != LaneChangeStage::LCS_NONE) ||
        (virtual_normal_gain == nullptr)) {
        return;
    }

    if (is_detour_required) {
        return;
    }
    auto split_merge_change_info =
        GetSplitAndMergeInfo(drive_passage, plan_start_point);

    ChangeReferencePathGainForMergeAndSplit(
        drive_passage, split_merge_change_info, cost_weight_params,
        plan_start_point, ref_path_deviation_gains, ref_heading_deviation_gains,
        virtual_normal_gain);
}

void GetReferencePathGainForRoam(
    const DrivePassage &drive_passage,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const ApolloTrajectoryPointProto &plan_start_point,
    const LaneChangeStage lc_stage,
    std::vector<double> *ref_path_deviation_gains,
    std::vector<double> *ref_heading_deviation_gains,
    bool *virtual_normal_gain) {
    // std::vector<int> change_indexs = drive_passage.change_index();
    // if (lc_stage != LaneChangeStage::LCS_NONE ||
    //     virtual_normal_gain == nullptr) {
    //     return;
    // }

    ChangeReferencePathGainForRoam(drive_passage, cost_weight_params,
                                   plan_start_point, ref_path_deviation_gains,
                                   ref_heading_deviation_gains,
                                   virtual_normal_gain);
}

void GetReferencePathGainForTurn(
    const DrivePassage &drive_passage,
    const NudgeInfos &nudge_info,
    const VehicleGeometryParamsProto &veh_geo_params,
    const bool is_detour_required,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const ApolloTrajectoryPointProto &plan_start_point,
    const LaneChangeStage lc_stage,
    std::vector<double> *ref_path_deviation_gains,
    std::vector<double> *ref_heading_deviation_gains,
    bool &virtual_normal_gain) {
    std::vector<int> change_indexs = drive_passage.change_index();
    if (!((lc_stage == LaneChangeStage::LCS_NONE) && !change_indexs.empty())) {
        return;
    }

    if (is_detour_required) {
        return;
    }
    auto turn_change_info = GetTurnInfo(drive_passage, plan_start_point);

    ChangeReferencePathGain(drive_passage, turn_change_info, cost_weight_params,
                            ref_path_deviation_gains,
                            ref_heading_deviation_gains, virtual_normal_gain);
}

void GetReferencePathGainForCenterAlign(
    const DrivePassage &drive_passage,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const ApolloTrajectoryPointProto &plan_start_point,
    const LaneChangeStage lc_stage,
    const NudgeInfos &nudge_info,
    const VehicleGeometryParamsProto &veh_geo_params,
    const bool is_detour_required,
    const bool is_kappa_inhibit_scene,
    std::vector<double> *ref_path_deviation_gains,
    std::vector<double> *ref_heading_deviation_gains,
    const ads_x::planning::EntryFuncSmoothInfo *entry_func_smooth_info,
    const int plan_id, bool is_quick_lane_change) {
  if (lc_stage != LaneChangeStage::LCS_NONE) {
    if (lc_stage == LaneChangeStage::LCS_EXECUTING) {
      const auto& ref_weight = cost_weight_params.reference_path_cost_weight();

      const auto& path_plf_proto =
          is_quick_lane_change
              ? ref_weight.quick_lc_speed_lane_change_path_deviation_gain_plf()
              : ref_weight.speed_lane_change_path_deviation_gain_plf();

      const auto& heading_plf_proto =
          is_quick_lane_change
              ? ref_weight.quick_lc_speed_lane_change_heading_deviation_gain_plf()
              : ref_weight.speed_lane_change_heading_deviation_gain_plf();

      const auto path_gain_plf = PiecewiseLinearFunctionFromProto(path_plf_proto);
      const auto heading_gain_plf = PiecewiseLinearFunctionFromProto(heading_plf_proto);

      const double v = plan_start_point.v();
      const double base_path_gain = path_gain_plf(v);
      const double base_heading_gain = heading_gain_plf(v);

      // 设定衰减起始点，暂设10个点后
      const auto& decay_start_index = ref_weight.quick_lc_decay_start_index();
      // 设定衰减速率，暂设 0.1
      const auto& kQuickLcDecayRate = ref_weight.quick_lc_decay_rate();

      for (size_t i = 0; i < ref_path_deviation_gains->size(); ++i) {
        double decay = 1.0;
        if (is_quick_lane_change && (i > decay_start_index)) {
          // 只有当是快速变道 且 超过起始点后 才开始衰减
          const int decay_offset = i - decay_start_index;
          decay = std::max(
              0.1, 1.0 - (kQuickLcDecayRate * static_cast<double>(decay_offset)));
        }
        (*ref_path_deviation_gains)[i] = base_path_gain * decay;
        (*ref_heading_deviation_gains)[i] = base_heading_gain * decay;
      }
    }
    return;
  }
    const bool is_change_abnormal = drive_passage.GetIsChangeAbnormal();
    if (is_detour_required && !is_change_abnormal) {
        return;
    }
    XCHECK_EQ(ref_path_deviation_gains->size(),
              ref_heading_deviation_gains->size());
    const auto reference_weight =
        cost_weight_params.reference_path_cost_weight();
    double path_gain = is_kappa_inhibit_scene
                           ? 1.0
                           : reference_weight.center_alignment_path_gain();
    double theta_gain = is_kappa_inhibit_scene
                            ? 1.0
                            : reference_weight.center_alignment_theta_gain();

    const double max_abnormal_path_gain = path_gain;
    const double min_abnormal_path_gain =
        is_change_abnormal ? reference_weight.abnormal_min_path_gain()
                           : reference_weight.init_entry_func_min_path_gain();
    const double max_abnormal_theta_gain = theta_gain;
    const double min_abnormal_theta_gain =
        is_change_abnormal ? reference_weight.abnormal_min_theta_gain()
                           : reference_weight.init_entry_func_min_theta_gain();
    const double path_alpha =
        is_change_abnormal ? reference_weight.abnormal_path_alpha()
                           : reference_weight.init_entry_func_path_alpha();
    const double theta_alhpa =
        is_change_abnormal ? reference_weight.abnormal_theta_alpha()
                           : reference_weight.init_entry_func_theta_alpha();
    const double path_inflection_step =
        is_change_abnormal
            ? reference_weight.abnormal_path_inflection_step()
            : reference_weight.init_entry_func_path_inflection_step();
    const double theta_inflection_step =
        is_change_abnormal
            ? reference_weight.abnormal_theta_inflection_step()
            : reference_weight.init_entry_func_theta_inflection_step();
    const int abnormal_time_step = is_change_abnormal
                                       ? drive_passage.GetAbnormalStep()
                                       : entry_func_smooth_info->step;
    if (is_change_abnormal ||
        entry_func_smooth_info->is_entry_func_need_smooth) {
        const double start_value_path =
            1.0F /
            (1.0F + std::exp(-path_alpha * (1.0F - path_inflection_step)));
        const double now_value_path =
            1.0F / (1.0F + std::exp(-path_alpha *
                                    (static_cast<double>(abnormal_time_step) -
                                     path_inflection_step)));
        path_gain = min_abnormal_path_gain +
                    (max_abnormal_path_gain - min_abnormal_path_gain) *
                        (now_value_path - start_value_path) /
                        (1 - start_value_path);

        const double start_value_theta =
            1.0F /
            (1.0F + std::exp(-theta_alhpa * (1.0F - theta_inflection_step)));
        const double now_value_theta =
            1.0F / (1.0F + std::exp(-theta_alhpa *
                                    (static_cast<double>(abnormal_time_step) -
                                     theta_inflection_step)));
        theta_gain = min_abnormal_theta_gain +
                     (max_abnormal_theta_gain - min_abnormal_theta_gain) *
                         (now_value_theta - start_value_theta) /
                         (1 - start_value_theta);
    }

    std::string abnormal_debug_name =
        absl::StrCat("center_abnormal_task_", plan_id);
    std::string abnormal_debug_string = "is_change_abnormal: ";
    absl::StrAppend(&abnormal_debug_string, is_change_abnormal,
                    ", not_match_count: ", abnormal_time_step,
                    ", gain: ", path_gain, " & ", theta_gain);

    std::fill(ref_path_deviation_gains->begin(),
              ref_path_deviation_gains->end(), path_gain);
    std::fill(ref_heading_deviation_gains->begin(),
              ref_heading_deviation_gains->end(), theta_gain);

    for (int i = 0;
         (i < ref_path_deviation_gains->size()) && (i < drive_passage.size());
         ++i) {
        if (drive_passage.station(StationIndex(i)).is_in_wide_lane()) {
            (*ref_path_deviation_gains)[i] = KRefPathDeviationGainsWideLane;
        }
    }
}

void GetReferencePathGainForLaneEvasion(
    const LaneEvadeInfo &lane_evade_info,
    std::vector<double> *ref_path_deviation_gains,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params) {
    double lane_evasion_gain = 1.0;
    const auto reference_weight =
        cost_weight_params.reference_path_cost_weight();
    if (lane_evade_info.is_evade) {
        lane_evasion_gain = reference_weight.lane_evasion_gain();
    } else if (lane_evade_info.is_ramp_out) {
        lane_evasion_gain = reference_weight.lane_evasion_ramp_out_gain();
    }
    std::transform(
        ref_path_deviation_gains->begin(), ref_path_deviation_gains->end(),
        ref_path_deviation_gains->begin(),
        [lane_evasion_gain](double val) { return val * lane_evasion_gain; });
}

/**
 * @brief “弯道检测 + 增益放大器”，在确认车辆行驶在 detour 场景时，让中性线吸引权重更大

    1.判定是否“绕行段”
        取当前起点前后约 10m 的走廊站点，计算局部平均曲率
        用阈值滞回 (0.002 / 0.0014) 判断是否属于 detour 场景

    2.场景条件过滤
        不在变道、不是虚拟分叉/转弯、没有避让/匝道退出、无特殊保持/暂停、轨迹起点 lateral 差小于 0.5m

    3.增益调整
        如果两者（走廊几何 + 上一条轨迹）都显示在 detour → 把 *mutable_path_gain *= 15
 */
void GetReferencePathGainForDetour(
    const int plan_id,
    const LaneChangeStage &lc_stage,
    const bool keep_and_push_or_pause,
    const LaneEvadeInfo &lane_evade_info,
    const bool virtual_normal_gain_turn,
    const bool virtual_normal_gain_split,
    const std::vector<TrajectoryPoint> &prev_traj,
    const ApolloTrajectoryPointProto &plan_start_point,
    const DrivePassage &drive_passage,
    double *mutable_path_gain) {
    if (mutable_path_gain == nullptr || (prev_traj.empty()) ||
        drive_passage.empty()) {
        return;
    }

    auto calculateAbsCurvature = [](const Vec2d &front_pos,
                                    const Vec2d &target_pos,
                                    const Vec2d &back_pos) {
        double x0 = front_pos.x(), y0 = front_pos.y();
        double x1 = target_pos.x(), y1 = target_pos.y();
        double x2 = back_pos.x(), y2 = back_pos.y();
        double dx1 = x1 - x0, dy1 = y1 - y0;
        double dx2 = x2 - x0, dy2 = y2 - y0;
        double dx3 = x2 - x1, dy3 = y2 - y1;

        double numerator = 2 * std::abs(dx1 * dy2 - dx2 * dy1);
        double denominator =
            std::sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) *
                      (dx3 * dx3 + dy3 * dy3));

        return denominator < 1e-6 ? 0.0 : numerator / denominator;
    };

    static bool virtual_path_gain_detour = false;
    constexpr double gain_tune_start_kappa = 0.002;
    constexpr double gain_tune_end_kappa = 0.0014;
    constexpr int max_kappa_considered_size = 5;
    constexpr double path_gain_ratio = 15.0;
    constexpr double start_l_diff_threshold = 0.5;
    constexpr double front_station_s_threshold = 10.0;
    constexpr double back_station_s_threshold = 10.0;

    const auto &prev_start_point_pos = prev_traj.front().pos();
    const Vec2d cur_start_point_pos(plan_start_point.path_point().x(),
                                    plan_start_point.path_point().y());
    const auto prev_start_point_sl_status =
        drive_passage.QueryFrenetCoordinateAt(prev_start_point_pos);
    const auto cur_start_point_sl_status =
        drive_passage.QueryFrenetCoordinateAt(cur_start_point_pos);
    double start_l_diff = 0.0;
    if (prev_start_point_sl_status.ok() && cur_start_point_sl_status.ok()) {
        start_l_diff = std::abs(prev_start_point_sl_status->l -
                                cur_start_point_sl_status->l);
    }

    static bool is_drive_passage_detour = false;
    int start_station_index =
        drive_passage.FindNearestStationIndex(cur_start_point_pos).value();
    double start_station_s =
        drive_passage.station(StationIndex(start_station_index))
            .accumulated_s();
    int front_station_index = start_station_index,
        back_station_index = start_station_index;
    for (int i = start_station_index; i >= 0; i--) {
        front_station_index = i;
        if (start_station_s -
                drive_passage.station(StationIndex(i)).accumulated_s() >
            front_station_s_threshold) {
            break;
        }
    }
    for (int i = start_station_index; i < drive_passage.size(); i++) {
        back_station_index = i;
        if (drive_passage.station(StationIndex(i)).accumulated_s() -
                start_station_s >
            back_station_s_threshold) {
            break;
        }
    }

    int back_back_station_index =
        std::max(std::min(2 * back_station_index - start_station_index,
                          drive_passage.size() - 1),
                 0);

    const Vec2d &start_station_pos =
        drive_passage.station(StationIndex(start_station_index)).xy();
    const Vec2d &front_station_pos =
        drive_passage.station(StationIndex(front_station_index)).xy();
    const Vec2d &back_station_pos =
        drive_passage.station(StationIndex(back_station_index)).xy();
    const Vec2d &back_back_station_pos =
        drive_passage.station(StationIndex(back_back_station_index)).xy();
    double start_station_curvature = calculateAbsCurvature(
        front_station_pos, start_station_pos, back_station_pos);
    double back_station_curvature = calculateAbsCurvature(
        start_station_pos, back_station_pos, back_back_station_pos);
    double average_curvature =
        0.5 * (start_station_curvature + back_station_curvature);
    if (average_curvature > gain_tune_start_kappa) {
        is_drive_passage_detour = true;
    } else if ((average_curvature > gain_tune_end_kappa) &&
               is_drive_passage_detour) {
        is_drive_passage_detour = true;
    } else {
        is_drive_passage_detour = false;
    }

    if (lc_stage == LaneChangeStage::LCS_NONE && (is_drive_passage_detour) &&
        !virtual_normal_gain_turn && !virtual_normal_gain_split &&
        !lane_evade_info.is_evade && !lane_evade_info.is_ramp_out &&
        (!keep_and_push_or_pause) && !prev_traj.empty() &&
        start_l_diff < start_l_diff_threshold) {
        double average_prev_traj_kappa = 0.0;
        const int kappa_considered_size = std::min(
            static_cast<int>(prev_traj.size()), max_kappa_considered_size);
        for (int i = 0; i < kappa_considered_size; ++i) {
            average_prev_traj_kappa += prev_traj[i].kappa();
        }
        average_prev_traj_kappa /= kappa_considered_size;
        if (std::abs(average_prev_traj_kappa) > gain_tune_start_kappa) {
            (*mutable_path_gain) *= path_gain_ratio;
            virtual_path_gain_detour = true;
        } else if ((std::abs(average_prev_traj_kappa) > gain_tune_end_kappa) &&
                   virtual_path_gain_detour) {
            (*mutable_path_gain) *= path_gain_ratio;
            virtual_path_gain_detour = true;
        } else {
            virtual_path_gain_detour = false;
        }
    } else {
        virtual_path_gain_detour = false;
    }
}

void AddReferencePathCost(
    int trajectory_steps,
    const PathSlBoundary &path_sl_boundary,
    std::vector<double> ref_path_deviation_gains,
    std::vector<double> ref_heading_deviation_gains,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const double mutable_path_gain,
    const std::unique_ptr<CenterLineQueryHelper<Mfob>>
        &reference_center_query_helper,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs) {
    std::vector<double> ref_ls(
        path_sl_boundary.reference_center_l_vector().begin(),
        path_sl_boundary.reference_center_l_vector().end());

    ref_ls.pop_back();
    costs->emplace_back(std::make_unique<ReferenceLineDeviationCost<Mfob>>(
        trajectory_steps, mutable_path_gain,
        cost_weight_params.reference_path_cost_weight().end_state_gain(),
        std::move(ref_ls), reference_center_query_helper->points(),
        reference_center_query_helper.get(),
        std::move(ref_path_deviation_gains), "MfobReferenceLineDeviationCost",
        cost_weight_params.reference_path_cost_weight()
            .reference_path_cost_weight(),
        Cost<Mfob>::CostType::MUST_HAVE));

    const std::vector<Vec2d> ref_path_vector(
        path_sl_boundary.reference_center_xy_vector().begin(),
        path_sl_boundary.reference_center_xy_vector().end());
    std::vector<double> ref_thetas;
    ref_thetas.reserve(ref_path_vector.size() - 1);
    for (int i = 1; i < ref_path_vector.size(); ++i) {
        ref_thetas.push_back(
            (ref_path_vector[i] - ref_path_vector[i - 1]).FastAngle());
    }
    costs->emplace_back(std::make_unique<EndHeadingCost<Mfob>>(
        trajectory_steps, std::move(ref_thetas),
        reference_center_query_helper->points(),
        reference_center_query_helper.get(),
        std::move(ref_heading_deviation_gains), "MfobEndHeadingCost",
        cost_weight_params.reference_path_cost_weight()
            .reference_heading_cost_weight(),
        Cost<Mfob>::CostType::MUST_HAVE));
}

void AddCaptainReferenceTrajectoryCost(
    int trajectory_steps,
    std::string base_name,
    const std::vector<TrajectoryPoint> &captain_traj,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs) {
    if (captain_traj.empty()) return;

    auto captain_ref_traj = captain_traj;
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while ((captain_ref_traj.size() < trajectory_steps) && loop_guard) {
        captain_ref_traj.push_back(TrajectoryPoint());
    }
    auto ref_xs = Mfob::FitState(captain_ref_traj);
    std::vector<double> captain_ref_weights(ref_xs.size(), 0.0);

    constexpr double kCaptainRefPosWeight = 1.0;
    constexpr double kCaptainRefHeadingWeight = 5.0;
    for (int i = 0; i < captain_traj.size(); ++i) {
        captain_ref_weights[i * Mfob::kStateSize + Mfob::kStateXIndex] =
            kCaptainRefPosWeight;
        captain_ref_weights[i * Mfob::kStateSize + Mfob::kStateYIndex] =
            kCaptainRefPosWeight;
        captain_ref_weights[i * Mfob::kStateSize + Mfob::kStateThetaIndex] =
            kCaptainRefHeadingWeight;
    }
    costs->emplace_back(std::make_unique<ReferenceStateDeviationCost<Mfob>>(
        std::move(ref_xs), std::move(captain_ref_weights),
        "MfobReferenceStateDeviationCost: CaptainReference", 1.0,
        Cost<Mfob>::CostType::MUST_HAVE));
}

void AddReferenceEndStateCost(
    int trajectory_steps,
    double ref_end_state_s,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs) {
    const auto &end_state_cost_params =
        cost_weight_params.end_state_cost_params();
    Mfob::StateType end_state = Mfob::StateType::Zero();
    end_state[Mfob::kStateSIndex] = ref_end_state_s;

    std::vector<double> state_regularization_weights(end_state.size(), 0.0);
    std::vector<double> base_numbers(end_state.size(),
                                     std::numeric_limits<double>::infinity());
    for (int i = 0; i < Mfob::kStateSize; ++i) {
        state_regularization_weights[i] = end_state_cost_params.w(i);
        base_numbers[i] = end_state_cost_params.base_numbers(i);
    }
    costs->emplace_back(
        std::make_unique<ReferenceSingleStateDeviationCost<Mfob>>(
            std::move(end_state), trajectory_steps - 1,
            std::move(state_regularization_weights), std::move(base_numbers),
            "MfobReferenceStateDeviationCost: EndStateAttraction",
            end_state_cost_params.weight(), Cost<Mfob>::CostType::MUST_HAVE));
}

bool NarrowScene(const DrivePassage &drive_passage,
                 const ApolloTrajectoryPointProto &plan_start_point,
                 double *lane_width) {
    const auto ego_lane_boundary_info =
        drive_passage.QueryEnclosingLaneBoundariesAtS(
            plan_start_point.path_point().s());
    *lane_width = ego_lane_boundary_info.left->lat_offset -
                  ego_lane_boundary_info.right->lat_offset;
    constexpr double narrow_lane_width = 2.9;

    return (*lane_width) < narrow_lane_width ? true : false;
}

absl::Status AddCosts(
    const int plan_id,
    const long long plan_start_stamp_us,
    const SamplingTrajectoryInfo &sampling_traj_info,
    double avoid_dynamic_obj_early_time,
    const std::string &base_name,
    const ApolloTrajectoryPointProto &plan_start_point,
    const LaneChangeStage lc_stage,
    ads_x::planning::PushDirection push_dir,
    const bool borrow_lane,
    const NudgeInfos &nudge_info,
    const ObjectDecisions &object_decisions,
    const std::vector<TrajectoryPoint> &initializer_traj,
    const std::vector<TrajectoryPoint> &prev_traj,
    const std::vector<TrajectoryPoint> &captain_traj,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_sl_boundary,
    const std::vector<senseAD::planning_pilot::BgPolygon> *occ_polygon,
    const ConstraintManager &constraint_manager,
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        &leading_trajs,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const LaneEvadeInfo &lane_evade_info,
    double v_now,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const TrajectoryOptimizerCostConfigProto &cost_config,
    const TrajectoryOptimizerValidationParamsProto
        &trajectory_optimizer_validation_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const VehicleDriveParamsProto &vehicle_drive_params,
    const MotionConstraintParamsProto &motion_constraint_params,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    const PlannerFunctionsParamsProto &planner_functions_params,
    const std::unique_ptr<CenterLineQueryHelper<Mfob>> &stations_query_helper,
    const std::unique_ptr<AvModelHelper<Mfob>> &av_model_helpers,
    const bool is_narrow_scene,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs,
    TrajectoryOptimizerDebugProto *traj_opt_debug_proto,
    ThreadPool *thread_pool,
    optimizer::TurnType ego_turn_type,
    const ads_x::planning::EntryFuncSmoothInfo *entry_func_smooth_info,
    const FrenetBox *av_frenet_box,
    const double follow_time,
    const ObjectHistoryManager *obs_history,
    const boost::optional<bool> &is_modify_speed,
    const NudgeObjectInfo *prev_nudge_object_info,
    const LaneChangeStateProto lane_change_state,
    std::vector<std::string> *static_object_ids,
    bool is_quick_lane_change) {
    Timer timer(__FUNCTION__);

    int dense_trajectory_steps = sampling_traj_info.dense_trajectory_steps;
    int sparse_trajectory_steps = sampling_traj_info.sparse_trajectory_steps;
    double dense_trajectory_time_step =
        sampling_traj_info.dense_trajectory_time_step;
    double sparse_trajectory_time_step =
        sampling_traj_info.sparse_trajectory_time_step;
    int trajectory_steps = dense_trajectory_steps + sparse_trajectory_steps;

    XCHECK_GT(trajectory_steps, 0);
    XCHECK_GT(dense_trajectory_time_step, 0.0);
    int free_index = 0;
    if ((dense_trajectory_steps * dense_trajectory_time_step >
         (kTrajectorySteps - 1) * kTrajectoryTimeStep)) {
        free_index =
            static_cast<int>((kTrajectorySteps - 1) * kTrajectoryTimeStep /
                             dense_trajectory_time_step);
    } else {
        free_index = static_cast<int>(
                         ((kTrajectorySteps - 1) * kTrajectoryTimeStep -
                          dense_trajectory_steps * dense_trajectory_time_step) /
                         sparse_trajectory_time_step) +
                     dense_trajectory_steps;
    }

    bool is_near_toll_station = false;
    // TODO:(xc)
    // const auto &poi_infos = psmm.map_ptr()->GetTrafficPoiInfo();
    // ads_x::planning::TrafficPoiInfo poi_toll_station;
    // for (const auto &poi : poi_infos) {
    //   if (poi.poi_type ==
    //           ads_x::planning::TrafficPoiInfo::PoiType::kTollStation &&
    //       poi.poi_distance < poi_toll_station.poi_distance) {
    //     poi_toll_station = poi;
    //   }
    // }
    // if (poi_toll_station.poi_distance < 10.0)
    //   is_near_toll_station = true;

    if (cost_config.enable_regularizers_cost()) {
        AddRegularizersCost(initializer_traj, cost_weight_params, costs);
    }
    bool is_kappa_inhibit_scene = false;

    // 加入 kappa、dkappa、ddkappa 约束
    if (cost_config.enable_curvature_cost()) {
        AddCurvatureCost(
            sampling_traj_info, initializer_traj.front(), constraint_manager,
            st_planner_object_traj, leading_trajs, drive_passage,
            cost_weight_params, veh_geo_params, vehicle_drive_params,
            motion_constraint_params, costs, is_kappa_inhibit_scene);
    }
    // 加入 V < 0 的情况cost,避免倒车的情况
    if (cost_config.enable_forward_speed_cost()) {
        costs->emplace_back(std::make_unique<ForwardSpeedCost<Mfob>>(
            "MfobForwardSpeedCost",
            cost_weight_params.forward_speed_cost_weight(),

            Cost<Mfob>::CostType::MUST_HAVE));
    }

    // 如果换道暂停，就先别换道
    // 如果现在没有换道，但是想加塞那就去加塞
    const bool keep_and_push_or_pause_default =
        ((push_dir != ads_x::planning::PushDirection::Push_None) &&
         (lc_stage == LCS_NONE)) ||
        (lc_stage == LCS_PAUSE);
    const bool keep_and_push_or_pause = keep_and_push_or_pause_default;
    // 类似帧间约束的cost，对上一帧轨迹的得到的 jerk 和 kappa 偏差进行约束
    if (cost_config.enable_immediate_future_cost() && !keep_and_push_or_pause) {
        AddImmediateFutureCost(sampling_traj_info, prev_traj, v_now,
                               cost_weight_params, drive_passage,
                               plan_start_point, costs, plan_id);
    }

    std::vector<double> inner_path_boudnary_gains(path_sl_boundary.size(), 1.0);
    std::vector<optimizer::LeadingInfo> leading_min_s(
        free_index + 1, {
                            std::numeric_limits<double>::infinity(),
                            std::numeric_limits<double>::infinity(),
                        });
    boost::optional<optimizer::PathTimeCorridor> path_time_corridor =
        boost::none;
    const bool need_path_time_corridor =
        cost_config.enable_static_boundary_cost() ||
        (cost_config.enable_object_cost() && !keep_and_push_or_pause);
    if (need_path_time_corridor) {
        const auto path_time_corridor_or = optimizer::BuildPathTimeCorridor(
            plan_id, base_name, initializer_traj, drive_passage,
            path_sl_boundary, leading_trajs, st_traj_mgr,
            st_planner_object_traj, veh_geo_params, dense_trajectory_steps,
            sparse_trajectory_steps, dense_trajectory_time_step,
            sparse_trajectory_time_step);
        if (path_time_corridor_or.ok()) {
            path_time_corridor = *path_time_corridor_or;
        }
    }

    if (cost_config.enable_object_cost() && !keep_and_push_or_pause) {
        bool is_acc_mode =
            (drive_passage.GetAdFunctionType() == AD_FunctionType::ACC);
        // TODO:(xc)
        // psmm.GetFunctionId() != Behavior_FunctionId_ACC
        if (path_time_corridor.has_value() && !is_acc_mode) {
            auto object_cost_weight_params = cost_weight_params;
            // std::cout << "path_time_corridor ok" << std::endl;
            optimizer::AddObjectCosts(
                plan_id, lc_stage, borrow_lane, nudge_info, object_decisions,
                dense_trajectory_steps, sparse_trajectory_steps,
                dense_trajectory_time_step, sparse_trajectory_time_step,
                avoid_dynamic_obj_early_time, base_name, initializer_traj,
                drive_passage, path_sl_boundary, *path_time_corridor,
                leading_trajs, st_traj_mgr, st_planner_object_traj,
                object_cost_weight_params, veh_geo_params, motion_constraint_params,
                trajectory_optimizer_vehicle_model_params, av_model_helpers,
                is_narrow_scene, &leading_min_s, &inner_path_boudnary_gains,
                costs, thread_pool, ego_turn_type, prev_traj, av_frenet_box,
                follow_time, obs_history, is_modify_speed,
                lane_change_state, prev_nudge_object_info, plan_start_point,
                stations_query_helper, static_object_ids);
        }
    }

    double ref_end_state_s = std::numeric_limits<double>::infinity();

    if (cost_config.enable_speed_limit_cost()) {
        optimizer::AddSpeedLimitCost(
            lc_stage, dense_trajectory_steps, sparse_trajectory_steps,
            dense_trajectory_time_step, sparse_trajectory_time_step,
            initializer_traj.front(), drive_passage, constraint_manager,
            cost_weight_params, motion_constraint_params, veh_geo_params,
            stations_query_helper, leading_min_s, &ref_end_state_s, costs,
            traj_opt_debug_proto, borrow_lane);
    }

    // 终端约束cost
    if (cost_config.enable_reference_end_state_cost()) {
        AddReferenceEndStateCost(trajectory_steps, ref_end_state_s,
                                 cost_weight_params, costs);
    }

    if (cost_config.enable_reference_path_cost()) {
        std::vector<double> ref_path_deviation_gains(
            stations_query_helper->points().size() - 1, 1.0);
        std::vector<double> ref_heading_deviation_gains(
            stations_query_helper->points().size() - 1, 1.0);

        bool is_init_nudge = false;
        if (!nudge_info.nudgeInfos.empty()) {
            const auto nudge_id = nudge_info.nudgeInfos.front().id;
            const auto nudge_object =
                st_traj_mgr.FindObjectByObjectId(nudge_id);
            const auto nudge_object_station =
                drive_passage.FindNearestStation(nudge_object->pose().pos());
            is_init_nudge = !nudge_object_station.is_in_intersection();
        }
        const bool is_detour_required =
            is_init_nudge ||
            IsDetourRequired(drive_passage, st_planner_object_traj,
                             leading_trajs, plan_start_point, veh_geo_params);
        GetReferencePathGainForRouteDestinationStopLine(
            drive_passage, constraint_manager, veh_geo_params,
            cost_weight_params, &ref_path_deviation_gains,
            &ref_heading_deviation_gains);
        bool virtual_normal_gain_turn = false;
        bool virtual_normal_gain_split = false;
        const auto &current_station = drive_passage.FindNearestStation(
            Vec2dFromApolloTrajectoryPointProto(plan_start_point));
        const bool virtual_normal_gain_intersection =
            current_station.is_in_intersection();
        GetReferencePathGainForTurn(
            drive_passage, nudge_info, veh_geo_params, is_init_nudge,
            cost_weight_params, plan_start_point, lc_stage,
            &ref_path_deviation_gains, &ref_heading_deviation_gains,
            virtual_normal_gain_turn);
        GetReferencePathGainForSplit(
            drive_passage, nudge_info, veh_geo_params, is_init_nudge,
            cost_weight_params, plan_start_point, lc_stage,
            &ref_path_deviation_gains, &ref_heading_deviation_gains,
            &virtual_normal_gain_split);

        if (lane_change_state.is_roam()) {
            GetReferencePathGainForRoam(
                drive_passage, cost_weight_params, plan_start_point, lc_stage,
                &ref_path_deviation_gains, &ref_heading_deviation_gains,
                &virtual_normal_gain_split);
        }

        const bool is_change_abnormal = drive_passage.GetIsChangeAbnormal();
        is_kappa_inhibit_scene =
            ((virtual_normal_gain_intersection && is_change_abnormal) ||
             (is_near_toll_station && is_change_abnormal) ||
             (is_detour_required && is_change_abnormal))
                ? true
                : is_kappa_inhibit_scene;
        if (!virtual_normal_gain_split && !virtual_normal_gain_turn &&
            !(virtual_normal_gain_intersection && !is_change_abnormal) &&
            !(is_near_toll_station && !is_change_abnormal)) {
          GetReferencePathGainForCenterAlign(
              drive_passage, cost_weight_params, plan_start_point, lc_stage,
              nudge_info, veh_geo_params, is_detour_required,
              is_kappa_inhibit_scene, &ref_path_deviation_gains,
              &ref_heading_deviation_gains, entry_func_smooth_info, plan_id,
              is_quick_lane_change);
          GetReferencePathGainForLaneEvasion(
              lane_evade_info, &ref_path_deviation_gains, cost_weight_params);
        }

        if (keep_and_push_or_pause) {
            std::fill(ref_path_deviation_gains.begin(),
                      ref_path_deviation_gains.end(),
                      cost_weight_params.reference_path_cost_weight()
                          .push_path_gain());
            std::fill(ref_heading_deviation_gains.begin(),
                      ref_heading_deviation_gains.end(),
                      cost_weight_params.reference_path_cost_weight()
                          .push_theta_gain());
        }

        double mutable_path_gain =
            cost_weight_params.reference_path_cost_weight().path_gain();
        GetReferencePathGainForDetour(
            plan_id, lc_stage, keep_and_push_or_pause, lane_evade_info,
            virtual_normal_gain_turn, virtual_normal_gain_split, prev_traj,
            plan_start_point, drive_passage, &mutable_path_gain);

        AddReferencePathCost(trajectory_steps, path_sl_boundary,
                             std::move(ref_path_deviation_gains),
                             std::move(ref_heading_deviation_gains),
                             cost_weight_params, mutable_path_gain,
                             stations_query_helper, costs);
    }

    boost::optional<double> extra_curb_buffer = boost::none;
    const auto ego_lane_boundary_info =
        drive_passage.QueryEnclosingLaneBoundariesAtS(
            plan_start_point.path_point().s());
    double lane_width = ego_lane_boundary_info.left->lat_offset -
                        ego_lane_boundary_info.right->lat_offset;
    const Station &ego_station =
        drive_passage.FindNearestStationAtS(plan_start_point.path_point().s());

    if (ego_station.is_in_intersection()) {
        const Station &normal_station =
            drive_passage.GetFirstNonIntersectionStation(
                Vec2d(plan_start_point.path_point().x(),
                      plan_start_point.path_point().y()));
        const auto first_non_intersection_lane_boundary_info =
            normal_station.QueryEnclosingLaneBoundariesAt(0.0).value();
        lane_width =
            first_non_intersection_lane_boundary_info.left->lat_offset -
            first_non_intersection_lane_boundary_info.right->lat_offset;
    }

    auto const left_lane_type = ego_lane_boundary_info.left->type;
    auto const right_lane_type = ego_lane_boundary_info.right->type;

    const auto lane_width_buffer_plf = PiecewiseLinearFunctionFromProto(
        cost_weight_params.lane_width_rel_hard_curb_clearance_plf());

    const boost::optional<double> lane_width_curb_buffer_opt =
        lane_width_buffer_plf(lane_width);
    bool is_acc_mode =
        (drive_passage.GetAdFunctionType() == AD_FunctionType::ACC);

    // TODO:(xiaochang)
    // psmm.GetFunctionId() != Behavior_FunctionId_ACC
    if (cost_config.enable_static_boundary_cost() && !is_acc_mode) {
        constexpr int kUTurnLevel2 = 2;
        const bool enable_three_point_turn =
            ((FLAGS_planner_runtime_uturn_level == kUTurnLevel2) ||
             ((FLAGS_planner_runtime_uturn_level == 1) &&
              planner_functions_params.enable_three_point_turn()));

        optimizer::AddStaticBoundaryCosts(
            trajectory_steps, base_name, plan_id, plan_start_stamp_us,
            enable_three_point_turn,
            initializer_traj.front(), drive_passage, nudge_info,
            path_sl_boundary, occ_polygon, inner_path_boudnary_gains,
            cost_weight_params,
            veh_geo_params, trajectory_optimizer_vehicle_model_params,
            stations_query_helper,
            path_time_corridor.has_value() ? &path_time_corridor.value()
                                           : nullptr,
            lane_width_curb_buffer_opt, lane_width, &extra_curb_buffer, costs,
            lc_stage, borrow_lane);
    }
    if (cost_config.enable_acceleration_and_jerk_cost()) {
        AddAccelAndJerkCost(
            dense_trajectory_time_step, initializer_traj.front(), drive_passage,
            trajectory_optimizer_vehicle_model_params, veh_geo_params,
            cost_weight_params, motion_constraint_params,
            trajectory_optimizer_validation_params, extra_curb_buffer,
            lane_width, is_narrow_scene, costs, borrow_lane,
            is_near_toll_station);
    }
    if (cost_config.enable_captain_reference_trajectory_cost()) {
        AddCaptainReferenceTrajectoryCost(trajectory_steps, base_name,
                                          captain_traj, costs);
    }
    return absl::OkStatus();
}

absl::Status AddStationQueryHelper(
    int trajectory_steps,
    std::string base_name,
    const DrivePassage &drive_passage,
    std::unique_ptr<CenterLineQueryHelper<Mfob>> *station_query_helper) {
    std::vector<Vec2d> station_points;
    station_points.reserve(drive_passage.size());
    for (const auto &station : drive_passage.stations()) {
        station_points.push_back(station.xy());
    }
    *station_query_helper = std::make_unique<CenterLineQueryHelper<Mfob>>(
        trajectory_steps, station_points,
        drive_passage.last_real_station_index().value(),
        "MfobStationQueryHelper", true);
    return absl::OkStatus();
}

std::unique_ptr<AvModelHelper<Mfob>> AddAvModelHelpers(
    int trajectory_steps,
    const std::string &base_name,
    const VehicleGeometryParamsProto &veh_geo_params,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params) {
    std::vector<double> dists_to_rac;
    std::vector<double> angles_to_axis;
    const int circle_size =
        trajectory_optimizer_vehicle_model_params.circles_size() +
        trajectory_optimizer_vehicle_model_params.mirror_circles_size();
    dists_to_rac.reserve(circle_size);
    angles_to_axis.reserve(circle_size);
    for (const auto &circle :
         trajectory_optimizer_vehicle_model_params.circles()) {
        dists_to_rac.push_back(circle.dist_to_rac());
        angles_to_axis.push_back(circle.angle_to_axis());
    }
    for (const auto &circle :
         trajectory_optimizer_vehicle_model_params.mirror_circles()) {
        dists_to_rac.push_back(circle.dist_to_rac());
        angles_to_axis.push_back(circle.angle_to_axis());
    }
    return std::make_unique<AvModelHelper<Mfob>>(
        trajectory_steps, dists_to_rac, angles_to_axis, "MfobAvModelHelper");
}

std::vector<TrajectoryPoint> GetExtendStateByPurePursuit(
    int dense_target_trajectory_steps,
    int sparse_target_trajectory_steps,
    double dense_target_trajectory_time_step,
    double sparse_target_trajectory_time_step,
    const TrajectoryPoint &extend_start_point,
    int k_extend_steps,
    double target_v,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_sl_boundary,
    const VehicleGeometryParamsProto &veh_geo_params,
    const MotionConstraintParamsProto &motion_constraint_params,
    int plan_id) {
    const int trajectory_steps =
        dense_target_trajectory_steps + sparse_target_trajectory_steps;
    XCHECK_GT(dense_target_trajectory_time_step, 0.0);
    XCHECK_GT(trajectory_steps, 0);

    constexpr double kLateralLookAhead = 0.6;
    Mfob::StateType x = Mfob::MakeState(
        extend_start_point.pos().x(), extend_start_point.pos().y(),
        extend_start_point.theta(), extend_start_point.v(),
        extend_start_point.kappa(), extend_start_point.a(),
        extend_start_point.psi(), extend_start_point.s());
    std::vector<TrajectoryPoint> res;
    const double time_base = extend_start_point.t();
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();

    // 防止 step_ratio 取 0
    int step_ratio = static_cast<int>(sparse_target_trajectory_time_step /
                                      dense_target_trajectory_time_step);
    if (step_ratio < 1) step_ratio = 1;

    auto finite = [](double z) { return std::isfinite(z); };

    int step_count = 0;
    while ((res.size() < static_cast<size_t>(k_extend_steps)) && loop_guard) {
        const double a = boost::algorithm::clamp<double>(
            (target_v - Mfob::StateGetV(x)) / dense_target_trajectory_time_step,
            motion_constraint_params.max_deceleration(),
            motion_constraint_params.max_acceleration());
        const double j = boost::algorithm::clamp<double>(
            (a - Mfob::StateGetA(x)) / dense_target_trajectory_time_step,
            motion_constraint_params.max_decel_jerk(),
            motion_constraint_params.max_accel_jerk());

        // stations() 判空
        Vec2d lateral_target_pos = drive_passage.stations().size() == 0
                                       ? (Mfob::StateGetPos(x) +
                                          (Vec2d::FastUnitFromAngle(Mfob::StateGetTheta(x)) *
                                              std::max(veh_geo_params.wheel_base(), 1e-3)))
                                       : drive_passage.stations().back().xy();

        // lookahead 下限与有限性
        constexpr double kLookAheadDistMin = 1e-3;
        double lateral_look_ahead_dist =
            (kLateralLookAhead * Mfob::StateGetV(x)) +
            veh_geo_params.wheel_base();
        if (!finite(lateral_look_ahead_dist) || (lateral_look_ahead_dist < kLookAheadDistMin)) {
            lateral_look_ahead_dist = kLookAheadDistMin;
        }

        const auto lateral_nearest_point_status =
            drive_passage.QueryFrenetCoordinateAt(Mfob::StateGetPos(x));
        if (lateral_nearest_point_status.ok()) {
            lateral_target_pos = path_sl_boundary.QueryReferenceCenterXY(
                lateral_look_ahead_dist + lateral_nearest_point_status->s);
        } else {
            lateral_target_pos = path_sl_boundary.QueryReferenceCenterXY(
                lateral_look_ahead_dist + Mfob::StateGetS(x));
        }

        // Query 坐标非法则退化为沿朝向直推
        if (!finite(lateral_target_pos.x()) || !finite(lateral_target_pos.y())) {
            lateral_target_pos =
                Mfob::StateGetPos(x) +
                Vec2d::FastUnitFromAngle(Mfob::StateGetTheta(x)) * lateral_look_ahead_dist;
        }

        // 目标向量零长度保护 + 角度归一化
        Vec2d d = lateral_target_pos - Mfob::StateGetPos(x);
        if (d.Length() < 1e-8) {
            d = Vec2d::FastUnitFromAngle(Mfob::StateGetTheta(x));
        }
        double alpha = d.Angle() - Mfob::StateGetTheta(x);
        alpha = NormalizeAngle(alpha);

        const double kappa =
            2.0 * fast_math::Sin(alpha) / lateral_look_ahead_dist;
        double psi = (kappa - Mfob::StateGetKappa(x)) /
                     dense_target_trajectory_time_step;

        double chi =
            (psi - Mfob::StateGetPsi(x)) / dense_target_trajectory_time_step;

        // 中间变量兜底
        double kappa_safe = finite(kappa) ? kappa : Mfob::StateGetKappa(x);
        double psi_safe   = finite(psi)   ? psi   : 0.0;
        double chi_safe   = finite(chi)   ? chi   : 0.0;
        double j_safe     = finite(j)     ? j     : 0.0;

        const auto u = Mfob::MakeControl(chi_safe, j_safe);

        // 首步避免传 -1 索引
        const int eval_idx = static_cast<int>(res.size());
        x = Mfob::EvaluateF(eval_idx, x, u,
                            dense_target_trajectory_time_step);

        if (trajectory_steps - k_extend_steps + res.size() >
            static_cast<size_t>(dense_target_trajectory_steps)) {
            step_count++;
            if (step_count < step_ratio) {
                continue;
            }
        }
        step_count = 0;
        const double dt = (trajectory_steps - k_extend_steps + res.size() <=
                           static_cast<size_t>(dense_target_trajectory_steps))
                              ? dense_target_trajectory_time_step
                              : sparse_target_trajectory_time_step;
        TrajectoryPoint next_pt;
        next_pt.set_pos(Mfob::StateGetPos(x));
        next_pt.set_theta(Mfob::StateGetTheta(x));
        next_pt.set_kappa(Mfob::StateGetKappa(x));
        next_pt.set_psi(Mfob::StateGetPsi(x));
        next_pt.set_v(Mfob::StateGetV(x));
        next_pt.set_a(Mfob::StateGetA(x));
        next_pt.set_s(Mfob::StateGetS(x));
        next_pt.set_t((res.empty() ? time_base : res.back().t()) + dt);

        // 坏点时不再 continue，而是“用前一个点外推”后直接
        bool ok_point =
            finite(next_pt.pos().x()) && finite(next_pt.pos().y()) &&
            finite(next_pt.theta())  && finite(next_pt.kappa())    &&
            finite(next_pt.v())      && finite(next_pt.a())        &&
            finite(next_pt.psi())    && finite(next_pt.s())        &&
            finite(next_pt.t());

        if (!ok_point) {
            TrajectoryPoint fill;
            if (!res.empty()) {
                const auto &last = res.back();
                fill = last;
                // 匀速沿上一个点的朝向外推 dt
                const double v = std::max(0.0, last.v());
                fill.set_pos(last.pos() + Vec2d::FastUnitFromAngle(last.theta()) * v * dt);
                fill.set_t(last.t() + dt);
                fill.set_s(last.s() + v * dt);
                fill.set_a(0.0);
                fill.set_psi(0.0);
                // theta/kappa 保持上一帧
            } else {
                // 第一帧就坏：用起点做一次外推
                fill = extend_start_point;
                const double v0 = std::max(0.0, extend_start_point.v());
                fill.set_pos(extend_start_point.pos() +
                             Vec2d::FastUnitFromAngle(extend_start_point.theta()) * v0 * dt);
                fill.set_t(time_base + dt);
                fill.set_s(extend_start_point.s() + v0 * dt);
                fill.set_a(0.0);
                fill.set_psi(0.0);
                // theta/kappa 保持起点
            }
            res.push_back(std::move(fill));
            continue;
        }

        res.push_back(std::move(next_pt));
    }

    return res;
}

/**
 *整体采样逻辑：
 * 1. 按密集/稀疏采样
 * 2. 判断末点是否越界

function ToTrajectoryOptimizerInput(...):
    // 1. 从原轨迹按密段/疏段采样
    res = sample_two_phase(input_traj, dense_dt, sparse_dt, dense_steps,
sparse_steps)

    if 已经够 target_steps:
        return res

    // 2. 判断末点是否越界
    if 末点不在通道或超边界:
        // 外推补齐
        res = extend_by_kinematics(res, dense_dt, sparse_dt, target_steps,
motion_limits) else:
        // Pure Pursuit 扩展
        res = extend_by_pure_pursuit(res, target_steps, passage, sl_boundary,
motion_limits, vehicle_params)

    return res
 */
std::vector<TrajectoryPoint> ToTrajectoryOptimizerInput(
    const std::vector<TrajectoryPoint> &input_traj,
    const SamplingTrajectoryInfo &sampling_traj_info,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_sl_boundary,
    const MotionConstraintParamsProto &motion_constraint_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    int plan_id) {
    int dense_target_trajectory_steps =
        sampling_traj_info.dense_trajectory_steps;
    int sparse_target_trajectory_steps =
        sampling_traj_info.sparse_trajectory_steps;
    double dense_target_trajectory_time_step =
        sampling_traj_info.dense_trajectory_time_step;
    double sparse_target_trajectory_time_step =
        sampling_traj_info.sparse_trajectory_time_step;
    int target_trajectory_steps =
        dense_target_trajectory_steps + sparse_target_trajectory_steps;

    // const int target_trajectory_steps =
    //     dense_target_trajectory_steps + sparse_target_trajectory_steps;

    XCHECK_GT(dense_target_trajectory_time_step, 0.0);
    XCHECK_GT(target_trajectory_steps, 0);

    if (input_traj.empty()) return input_traj;

    constexpr double kMinTimeStep = 1e-3;
    const int input_traj_size = static_cast<int>(input_traj.size());
    double input_trajectory_time_step = kTrajectoryTimeStep;
    for (int i = 1; i < input_traj_size; ++i) {
        const double dt = input_traj[i].t() - input_traj[i - 1].t();
        if (std::isfinite(dt) && (dt > kMinTimeStep)) {
            input_trajectory_time_step = dt;
            break;
        }
    }

    const int dense_sample_step =
        std::max(1, static_cast<int>(dense_target_trajectory_time_step /
                                         input_trajectory_time_step +
                                     0.5));
    const int sparse_sample_step =
        std::max(1, static_cast<int>(sparse_target_trajectory_time_step /
                                         input_trajectory_time_step +
                                     0.5));
    const int dense_end_step = dense_target_trajectory_steps * dense_sample_step;

    std::vector<TrajectoryPoint> res;
    res.reserve(target_trajectory_steps);
    for (int i = 0; i < target_trajectory_steps; ++i) {
        int cur_steps = 0;
        if (i <= dense_target_trajectory_steps) {
            cur_steps = i * dense_sample_step;
        } else {
            cur_steps = ((i - dense_target_trajectory_steps) * sparse_sample_step) +
                        dense_end_step;
        }
        if (cur_steps >= input_traj_size) break;
        if (std::isnan(input_traj[cur_steps].pos().x())) {
          printf("oops!\n");
        }
        res.push_back(input_traj[cur_steps]);
    }
    if (res.size() == target_trajectory_steps) return res;

    const double input_traj_end_v = input_traj.back().v();
    const auto traj_end_sl_status =
        drive_passage.QueryFrenetCoordinateAt(input_traj.back().pos());
    if (!traj_end_sl_status.ok() ||
        (traj_end_sl_status->s > path_sl_boundary.end_s())) {

        constexpr double kMinSpeed = 1e-6;

        auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();

        // 统一有限性检查
        auto finite = [](double z) { return std::isfinite(z); };

        while ((res.size() < target_trajectory_steps) && loop_guard) {
            const double dt =
                res.size() <= dense_target_trajectory_steps
                    ? dense_target_trajectory_time_step
                    : sparse_target_trajectory_time_step;

            auto &pt = res.back();

            // dist 有限性与下限保护
            double dist = pt.v() * dt + 0.5 * pt.a() * dt * dt;
            // if (!finite(dist)) dist = 0.0;
            // dist = std::max(kMinDist, dist);

            PathPoint path_point;
            Vec2d pos_safe = (finite(pt.pos().x()) && finite(pt.pos().y()))
                                ? pt.pos()
                                : Vec2d(0.0, 0.0);
            path_point.set_x(pos_safe.x());
            path_point.set_y(pos_safe.y());
            path_point.set_s(finite(pt.s()) ? pt.s() : 0.0);
            path_point.set_theta(finite(pt.theta()) ? pt.theta() : 0.0);
            path_point.set_kappa(finite(pt.kappa()) ? pt.kappa() : 0.0);
            path_point.set_lambda(finite(pt.lambda()) ? pt.lambda() : 0.0);

            const auto next_path_point = GetPathPointAlongCircle(path_point, dist);

            auto next_pt = pt;
            next_pt.set_t(pt.t() + dt);
            next_pt.set_pos(ToVec2d(next_path_point));
            next_pt.set_s(next_path_point.s());
            next_pt.set_theta(next_path_point.theta());
            next_pt.set_kappa(next_path_point.kappa());

            double v_next = pt.v() + (pt.a() * dt);
            if (!finite(v_next)) v_next = 0.0;
            next_pt.set_v(std::max(kMinSpeed, v_next));

            double a_next = std::max(pt.a(), -1.0 * next_pt.v() / dt);
            if (!finite(a_next)) a_next = 0.0;
            next_pt.set_a(a_next);

            double jerk_raw = (next_pt.a() - pt.a()) / dt;
            if (!finite(jerk_raw)) jerk_raw = 0.0;
            double jerk = boost::algorithm::clamp(
                jerk_raw,
                motion_constraint_params.max_decel_jerk(),
                motion_constraint_params.max_accel_jerk());
            next_pt.set_j(jerk);

            double psi_next = next_path_point.lambda() * next_pt.v();
            if (!finite(psi_next)) psi_next = 0.0;
            next_pt.set_psi(psi_next);

            // push
            bool ok_point =
                finite(next_pt.pos().x()) && finite(next_pt.pos().y()) &&
                finite(next_pt.theta())  && finite(next_pt.kappa())    &&
                finite(next_pt.v())      && finite(next_pt.a())        &&
                finite(next_pt.psi())    && finite(next_pt.s())        &&
                finite(next_pt.t())      && finite(next_pt.j());

            if (!ok_point) {
                auto fill = pt;
                const double v = std::max(0.0, pt.v());
                fill.set_pos(pt.pos() + Vec2d::FastUnitFromAngle(pt.theta()) * v * dt);
                fill.set_t(pt.t() + dt);
                fill.set_s(pt.s() + v * dt);
                fill.set_a(0.0);
                fill.set_psi(0.0);
                fill.set_j(0.0);
                res.push_back(std::move(fill));
            } else {
                res.push_back(std::move(next_pt));
            }
        }

        if (res.size() >= 2) {
            res.back().set_j((res.rbegin() + 1)->j());
        } else if (res.size() == 1) {
            res.back().set_j(0.0);
        }

        return res;
    }

    double time_to_extend = 0.0;
    if (res.size() <= dense_target_trajectory_steps) {
        time_to_extend = dense_target_trajectory_time_step *
                             (dense_target_trajectory_steps - res.size() + 1) +
                         sparse_target_trajectory_time_step *
                             (sparse_target_trajectory_steps);
    } else {
        time_to_extend = sparse_target_trajectory_time_step *
                         (target_trajectory_steps - res.size() + 1);
    }
    constexpr double kMinEndSpeed = 2.0;
    constexpr double kMinTimeToExtend = 1e-3;
    const double remain_s =
        std::max(0.0, path_sl_boundary.end_s() - traj_end_sl_status->s);
    const double speed_upper_bound_by_dist =
        remain_s / std::max(time_to_extend, kMinTimeToExtend);
    const double target_v = std::max(
        kMinEndSpeed, std::min(std::max(kMinEndSpeed, input_traj_end_v),
                               speed_upper_bound_by_dist));

    const auto extend_state = GetExtendStateByPurePursuit(
        dense_target_trajectory_steps, sparse_target_trajectory_steps,
        dense_target_trajectory_time_step, sparse_target_trajectory_time_step,
        res.back(), target_trajectory_steps - res.size(), target_v,
        drive_passage, path_sl_boundary, veh_geo_params,
        motion_constraint_params, plan_id);

    for (int k = 0; k < extend_state.size(); ++k) {
      if (std::isnan(extend_state[k].pos().x())) {
        printf("oops!\n");
      }
        res.push_back(extend_state[k]);
    }
    return res;
}

boost::optional<std::vector<TrajectoryPoint>> BuildUsablePrevInitTrajectory(
    int plan_id,
    const SamplingTrajectoryInfo &sampling_traj_info,
    const Mfob &problem,
    const DdpOptimizerParamsProto &params,
    absl::Time plan_start_time,
    absl::Time last_plan_start_time,
    const std::vector<TrajectoryPoint> &initializer_traj,
    const std::vector<TrajectoryPoint> &last_optimized_traj,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const bool is_motion_aeb_result,
    const boost::optional<bool> &is_modify_speed,
    boost::optional<std::vector<TrajectoryPoint>> *pre_traj,
    boost::optional<double> *pre_traj_cost) {
    const int trajectory_steps = sampling_traj_info.dense_trajectory_steps +
                                 sampling_traj_info.sparse_trajectory_steps;

    if (initializer_traj.empty()) {
        return boost::none;
    }
    if (last_optimized_traj.size() < trajectory_steps) {
        return boost::none;
    }

    constexpr double kEpsilon = 1e-6;
    constexpr double kMaxShiftTime = 1.0;
    const absl::Duration dt = plan_start_time - last_plan_start_time;
    const double shift_time = absl::ToDoubleSeconds(dt);

    if ((shift_time < -kEpsilon) || (shift_time > kMaxShiftTime)) {
        return boost::none;
    }

    std::vector<TrajectoryPoint> shifted_last_optimized_traj =
        last_optimized_traj;
    ShiftTrajectoryByTime(shift_time, &shifted_last_optimized_traj);

    constexpr double kSearchFailMaxAdaptionCost = 10000.0;
    constexpr double kNormalMaxAdaptionCost = 500.0;
    const bool consider_use_initializer_traj =
        is_modify_speed.has_value() ? (is_modify_speed.value() ? false : true)
                                    : true;
    const double max_adaption_cost =
        (is_motion_aeb_result || !consider_use_initializer_traj)
            ? kSearchFailMaxAdaptionCost
            : kNormalMaxAdaptionCost;
    boost::optional<std::vector<TrajectoryPoint>> prev_init_traj =
        optimizer::AdaptTrajectoryToGivenPlanStartPoint(
            plan_id, sampling_traj_info.dense_trajectory_steps,
            sampling_traj_info.sparse_trajectory_steps, problem, params,
            max_adaption_cost, initializer_traj.front(),
            shifted_last_optimized_traj, pre_traj, pre_traj_cost);

    int use_object_num =
        static_cast<int>(sampling_traj_info.dense_trajectory_steps +
                         sampling_traj_info.sparse_trajectory_steps);
    if (prev_init_traj.has_value() && !is_motion_aeb_result &&
        consider_use_initializer_traj) {
        for (const auto &obj_traj : *st_planner_object_traj.trajectories) {
          if (!optimizer::HasSameDecisionOverSpacetimeObject(
                  initializer_traj, *prev_init_traj,
                  optimizer::SampleObjectStates(
                      sampling_traj_info.dense_trajectory_steps,
                      sampling_traj_info.sparse_trajectory_steps,
                      sampling_traj_info.dense_trajectory_time_step,
                      sampling_traj_info.sparse_trajectory_time_step,
                      use_object_num, false,
                      obj_traj.states()))) {
            return boost::none;
          }
        }
    }

    return prev_init_traj;
}

void AddSteerAngleToPoints(double wheel_base,
                           double steer_ratio,
                           std::vector<TrajectoryPoint> *result_points) {
    if (result_points == nullptr) {
        return;
    }
    for (TrajectoryPoint &point : *result_points) {
        point.set_steer_angle(
            fast_math::Atan2(point.kappa() * wheel_base, 1.0) * steer_ratio);
    }
}

optimizer::TurnType GetEgoTurnType(const DrivePassage &drive_passage) {
    // TODO:(xc)
    optimizer::TurnType ego_turn_type = optimizer::TurnType::kStraight;
    switch (drive_passage.GetEgoTurnType()) {
        case ads_x::planning::NO_TURN:
            ego_turn_type = optimizer::TurnType::kStraight;
            break;
        case ads_x::planning::LEFT_TURN:
            ego_turn_type = optimizer::TurnType::kLeftTurn;
            break;
        case ads_x::planning::RIGHT_TURN:
            ego_turn_type = optimizer::TurnType::kRightTurn;
            break;
        case ads_x::planning::U_TURN:
            ego_turn_type = optimizer::TurnType::kUTurn;
            break;
        default:
            ego_turn_type = optimizer::TurnType::kStraight;
    }
    return ego_turn_type;
}

SamplingTrajectoryInfo set_sampling_trajectory(
    const TrajectoryOptimizerParamsProto *trajectory_optimizer_params) {
    const int dense_trajectory_steps =
        trajectory_optimizer_params->dense_trajectory_steps();
    const int sparse_trajectory_steps =
        trajectory_optimizer_params->sparse_trajectory_steps();
    const double dense_trajectory_time_step =
        trajectory_optimizer_params->dense_trajectory_time_step();
    const double sparse_trajectory_time_step =
        trajectory_optimizer_params->sparse_trajectory_time_step();

    XCHECK_GT(dense_trajectory_time_step, 0.0);

    XCHECK_LT(dense_trajectory_steps * dense_trajectory_time_step +
                  sparse_trajectory_steps * sparse_trajectory_time_step,
              kPlanningTimeHorizon);
    const int trajectory_steps =
        dense_trajectory_steps + sparse_trajectory_steps;

    SamplingTrajectoryInfo sampling_trajectory{};
    sampling_trajectory.dense_trajectory_steps = dense_trajectory_steps;
    sampling_trajectory.sparse_trajectory_steps = sparse_trajectory_steps;
    sampling_trajectory.dense_trajectory_time_step = dense_trajectory_time_step;
    sampling_trajectory.sparse_trajectory_time_step =
        sparse_trajectory_time_step;
    sampling_trajectory.trajectory_steps = trajectory_steps;

    return sampling_trajectory;
}

}  // namespace
// #pragma GCC optimize("O0")
absl::StatusOr<TrajectoryOptimizerOutput> OptimizeTrajectory(
    const TrajectoryOptimizerInput &input,
    TrajectoryOptimizerDebugProto *optimizer_debug,
    bool is_compare_weight,
    ThreadPool *thread_pool) {
    SCOPED_TRACE("EstPlanner/OptimizeTrajectory");
    Timer timer(__FUNCTION__);

    if (!XCHECK_NOTNULL(input.st_traj_mgr) ||
        !XCHECK_NOTNULL(input.drive_passage) ||
        !XCHECK_NOTNULL(input.path_sl_boundary) ||
        !XCHECK_NOTNULL(input.constraint_mgr) ||
        !XCHECK_NOTNULL(input.leading_trajs) ||
        !XCHECK_NOTNULL(input.st_planner_object_traj)) {
        return absl::InternalError("input error");
    }

    const auto &trajectory_optimizer_params =
        *XCHECK_NOTNULL(input.trajectory_optimizer_params);
    const auto &motion_constraint_params =
        *XCHECK_NOTNULL(input.motion_constraint_params);
    const auto &planner_functions_params =
        *XCHECK_NOTNULL(input.planner_functions_params);
    const auto &vehicle_models_params =
        *XCHECK_NOTNULL(input.vehicle_models_params);
    const auto &veh_geo_params = *XCHECK_NOTNULL(input.veh_geo_params);
    const auto &veh_drive_params = *XCHECK_NOTNULL(input.veh_drive_params);

    auto input_status = CheckInputQuality(input);
    if (!input_status.ok()) {
        return input_status;
    }
    const double follow_time = input.prev_time_headway.has_value()
                                   ? input.prev_time_headway.value()
                                   : input.dynamic_time_headway;
    const long long plan_start_stamp_us =
        absl::ToUnixMicros(input.plan_start_time);
    const OccDdpCsvFrameContext csv_ctx{input.plan_id, plan_start_stamp_us};

    const double avoid_dynamic_obj_early_time =
        trajectory_optimizer_params.avoid_dynamic_obj_early_time();

    auto sample_traj_info =
        set_sampling_trajectory(input.trajectory_optimizer_params);

    const auto &drive_passage = *input.drive_passage;
    const auto &plan_start_point = input.plan_start_point;

    optimizer_debug->set_trajectory_start_timestamp(
        ToUnixDoubleSeconds(input.plan_start_time));

    std::vector<TrajectoryPoint> optimizer_input_traj =
        ToTrajectoryPointFromSecondOrderApollo(input.trajectory);
    constexpr double kStartSquareDistThreshold = 1.0;
    constexpr double kStartVDiffThreshold = 2.0;
    bool use_plan_start = false;
    if (!optimizer_input_traj.empty()) {
        const auto &input_start_point = optimizer_input_traj.front();
        const double start_square_dist =
            (Vec2d(plan_start_point.path_point().x(),
                   plan_start_point.path_point().y()) -
             input_start_point.pos())
                .squaredNorm();
        const double start_v_diff =
            plan_start_point.v() - input_start_point.v();
        use_plan_start =
            start_square_dist < kStartSquareDistThreshold &&
            std::abs(start_v_diff) < kStartVDiffThreshold;
    }
    if (use_plan_start) {
        optimizer::AlignInputTrajectoryToPlanStart(plan_start_point,
                                                   drive_passage,
                                                   &optimizer_input_traj);
    }

    std::vector<TrajectoryPoint> initializer_traj = ToTrajectoryOptimizerInput(
        optimizer_input_traj,
        sample_traj_info, *input.drive_passage, *input.path_sl_boundary,
        motion_constraint_params, veh_geo_params, input.plan_id);
    // The debug hook uses the same normalized start state as the optimizer.
    // Keep this alias next to the conversion so it cannot drift from the
    // initializer trajectory after input adaptation.
    const auto &initializer_traj_start_point = initializer_traj.front();

    // const std::vector<TrajectoryPoint> prev_traj = ToTrajectoryOptimizerInput(
    //     ToTrajectoryPoint(input.previous_trajectory), sample_traj_info,
    //     *input.drive_passage, *input.path_sl_boundary, motion_constraint_params,
    //     veh_geo_params, input.plan_id);

    constexpr double kEpsilon = 1e-6;
    constexpr double kMaxShiftTime = 1.0;
    absl::Time last_plan_start_time =
        (input.trajectory_optimizer_state)
            ? input.trajectory_optimizer_state->last_plan_start_time
            : absl::InfinitePast();
    const absl::Duration dt = input.plan_start_time - last_plan_start_time;
    const double shift_time = absl::ToDoubleSeconds(dt);

    std::vector<TrajectoryPoint> prev_traj;
    if ((shift_time < -kEpsilon) || (shift_time > kMaxShiftTime)) {
      prev_traj.clear();
    } else {
      prev_traj = ToTrajectoryPoint(input.previous_trajectory);
      ShiftTrajectoryByTime(shift_time, &prev_traj);
    }

    XCHECK(prev_traj.empty() || (prev_traj.size() == initializer_traj.size()));

    const std::string base_name_with_plan_id =
        absl::StrFormat("traj_opt_%d", input.plan_id);
    const std::string base_name = "traj_opt";

    const auto &path_sl_boundary = *input.path_sl_boundary;
    const auto &constraint_manager = *input.constraint_mgr;
    const auto &leading_trajs = *input.leading_trajs;
    const auto &st_traj_mgr = *input.st_traj_mgr;
    const double v_now = plan_start_point.v();
    const auto &st_planner_object_traj = *input.st_planner_object_traj;

    double lane_width = 0.0;
    const bool is_narrow_scene =
        NarrowScene(drive_passage, plan_start_point, &lane_width);

    std::unique_ptr<CenterLineQueryHelper<Mfob>> stations_query_helper;
    absl::Status add_helper_status = AddStationQueryHelper(
        sample_traj_info.trajectory_steps, base_name_with_plan_id,
        drive_passage, &stations_query_helper);
    XCHECK_EQ(add_helper_status.ok(), true);

    std::unique_ptr<AvModelHelper<Mfob>> av_model_helpers = AddAvModelHelpers(
        sample_traj_info.trajectory_steps, base_name_with_plan_id,
        veh_geo_params,
        vehicle_models_params.trajectory_optimizer_vehicle_model_params());

    Timer add_cost_start_time;
    std::vector<std::unique_ptr<Cost<Mfob>>> costs;

    std::vector<std::string> static_object_ids;

    optimizer::TurnType ego_turn_type = optimizer::TurnType::kUnknown;
    // TODO:(xc)
    ego_turn_type = GetEgoTurnType(*input.drive_passage);
    auto lc_weight_debug_string =
        absl::StrCat("lateral_acceleration_cost_weight:",
                     trajectory_optimizer_params.cost_weight_params()
                         .lateral_acceleration_cost_weight());

    const std::vector<TrajectoryPoint> &captain_trajectory_vec =
        input.captain_trajectory == nullptr ? std::vector<TrajectoryPoint>()
                                            : *input.captain_trajectory;
    TrajectoryOptimizerState output_trajectory_optimizer_state =
        input.trajectory_optimizer_state.value_or(TrajectoryOptimizerState());
    absl::Status add_cost_status = AddCosts(
        input.plan_id, plan_start_stamp_us, sample_traj_info,
        avoid_dynamic_obj_early_time, base_name_with_plan_id,
        input.plan_start_point, input.lc_stage, input.push_dir,
        input.borrow_lane, input.nudge_info, input.object_decisions,
        initializer_traj, prev_traj, captain_trajectory_vec, drive_passage,
        path_sl_boundary, input.occ_polygon, constraint_manager, leading_trajs,
        st_traj_mgr, st_planner_object_traj, *input.lane_evade_info, v_now,
        trajectory_optimizer_params.cost_weight_params(),
        trajectory_optimizer_params.cost_config(),
        trajectory_optimizer_params.trajectory_optimizer_validation_params(),
        veh_geo_params, veh_drive_params, motion_constraint_params,
        vehicle_models_params.trajectory_optimizer_vehicle_model_params(),
        planner_functions_params, stations_query_helper, av_model_helpers,
        is_narrow_scene, &costs, optimizer_debug, thread_pool, ego_turn_type,
        input.entry_func_smooth_info, input.ego_frenet_box, follow_time,
        input.obs_history, input.is_modify_speed, input.nudge_object_info,
        input.lane_change_state, &static_object_ids,
        input.is_quick_lane_change);
    XCHECK_EQ(add_cost_status.ok(), true);

    const double add_cost_time = add_cost_start_time.TimeNs() / 1e6;

    auto problem = std::make_unique<Mfob>(
        &motion_constraint_params, &veh_geo_params, &veh_drive_params,
        sample_traj_info.dense_trajectory_steps,
        sample_traj_info.sparse_trajectory_steps,
        sample_traj_info.dense_trajectory_time_step,
        sample_traj_info.sparse_trajectory_time_step, false, false);
    problem->AddCostHelper(std::move(stations_query_helper));
    problem->AddCostHelper(std::move(av_model_helpers));
    for (auto &cost : costs) {
        problem->AddCost(std::move(cost));
    }

    std::string solver_init_method = "none";
    DdpOptimizerDebugProto::SolverInitialTrajectorySource
        solver_init_traj_source;
    boost::optional<std::vector<TrajectoryPoint>> solver_init_traj;
    boost::optional<std::vector<TrajectoryPoint>> pre_traj = boost::none;
    boost::optional<double> pre_traj_cost = boost::none;

    if (FLAGS_planner_traj_opt_init_traj_uses_last_optimized_trajectory) {
        if (input.trajectory_optimizer_state.has_value() &&
            (input.trajectory_optimizer_state->last_optimized_trajectory.size() >
                0)) {
            solver_init_traj = BuildUsablePrevInitTrajectory(
                input.plan_id, sample_traj_info, *problem,
                trajectory_optimizer_params.optimizer_params(),
                input.plan_start_time,
                input.trajectory_optimizer_state->last_plan_start_time,
                initializer_traj,
                input.trajectory_optimizer_state->last_optimized_trajectory,
                st_planner_object_traj, input.is_motion_aeb_result,
                input.is_modify_speed, &pre_traj, &pre_traj_cost);
            if (solver_init_traj.has_value()) {
                solver_init_traj_source =
                    DdpOptimizerDebugProto::PREV_OPTIMIZATION;
                solver_init_method = "prev";
            }
        }
    }

    /**
     * 对上游采样的结果过一遍ddp，这一次优化仅加入一些硬约束
     * 至于是否采用，须通过对比求结果cost和上一针轨迹作为初始值的cost大小，取较小者
     */
    if (!solver_init_traj.has_value()) {
        boost::optional<double> smooth_init_cost = boost::none;
        constexpr double kAbnormalInitSmoothCostValue = 1000.0;
        double offset = input.lane_evade_info->is_evade ? input.lane_evade_info->offset
                             : 0.0;
        std::vector<double> ref_l_offset(initializer_traj.size() - 1, offset);

        solver_init_traj = SmoothTrajectoryByMixedFourthOrderDdp(
            input.plan_id, sample_traj_info.dense_trajectory_steps,
            sample_traj_info.sparse_trajectory_steps,
            sample_traj_info.dense_trajectory_time_step,
            sample_traj_info.sparse_trajectory_time_step, initializer_traj,
            drive_passage, base_name_with_plan_id,
            trajectory_optimizer_params.smoother_params(),
            motion_constraint_params, veh_geo_params, veh_drive_params,
            &smooth_init_cost, ref_l_offset);

        // if (smooth_init_cost.has_value() &&
        //     smooth_init_cost.value() > 10000) {
        //     std::stringstream ss_input_traj;
        //     ss_input_traj << std::fixed << std::setprecision(3);
        //     ss_input_traj << "[traj_opt][abnormal_smooth] smooth_init_cost="
        //                   << smooth_init_cost.value() << " raw_input_traj: ";
        //     for (size_t i = 0; i < input.trajectory.size(); ++i) {
        //         const auto &pt = input.trajectory[i];
        //         ss_input_traj << "[" << i << "]("
        //                       << "x=" << pt.path_point().x()
        //                       << ", y=" << pt.path_point().y()
        //                       << ", s=" << pt.path_point().s()
        //                       << ", t=" << pt.relative_time()
        //                       << ", theta=" << pt.path_point().theta()
        //                       << ", v=" << pt.v()
        //                       << ", a=" << pt.a()
        //                       << ", kappa=" << pt.path_point().kappa()
        //                       << "), ";
        //     }
        //     std::printf("%s\n", ss_input_traj.str().c_str());

        //     std::stringstream ss_initializer_traj;
        //     ss_initializer_traj << std::fixed << std::setprecision(3);
        //     ss_initializer_traj << "[traj_opt][abnormal_smooth] initializer_traj: ";
        //     for (size_t i = 0; i < initializer_traj.size(); ++i) {
        //         const auto &pt = initializer_traj[i];
        //         ss_initializer_traj << "[" << i << "]("
        //                             << "x=" << pt.pos().x()
        //                             << ", y=" << pt.pos().y()
        //                             << ", s=" << pt.s()
        //                             << ", t=" << pt.t()
        //                             << ", theta=" << pt.theta()
        //                             << ", v=" << pt.v()
        //                             << ", a=" << pt.a()
        //                             << ", j=" << pt.j()
        //                             << ", kappa=" << pt.kappa()
        //                             << ", psi=" << pt.psi()
        //                             << ", chi=" << pt.chi()
        //                             << "), ";
        //     }
        //     std::printf("%s\n", ss_initializer_traj.str().c_str());

        //     if (solver_init_traj.has_value()) {
        //         std::stringstream ss_smooth_traj;
        //         ss_smooth_traj << std::fixed << std::setprecision(3);
        //         ss_smooth_traj << "[traj_opt][abnormal_smooth] smooth_traj: ";
        //         for (size_t i = 0; i < solver_init_traj->size(); ++i) {
        //             const auto &pt = (*solver_init_traj)[i];
        //             ss_smooth_traj << "[" << i << "]("
        //                            << "x=" << pt.pos().x()
        //                            << ", y=" << pt.pos().y()
        //                            << ", s=" << pt.s()
        //                            << ", t=" << pt.t()
        //                            << ", theta=" << pt.theta()
        //                            << ", v=" << pt.v()
        //                            << ", a=" << pt.a()
        //                            << ", j=" << pt.j()
        //                            << ", kappa=" << pt.kappa()
        //                            << "), ";
        //         }
        //         std::printf("%s\n", ss_smooth_traj.str().c_str());
        //     }
        //     std::printf("xxxx");
        // }

        if (smooth_init_cost.has_value() &&
            smooth_init_cost.value() > kAbnormalInitSmoothCostValue &&
            pre_traj.has_value() && pre_traj_cost.has_value() &&
            pre_traj_cost.value() < smooth_init_cost.value()) {
            solver_init_traj = pre_traj.value();
            solver_init_traj_source = DdpOptimizerDebugProto::PREV_OPTIMIZATION;
            solver_init_method = "abnormal_prev";
        } else {
            solver_init_traj_source =
                DdpOptimizerDebugProto::SMOOTHED_INITIALIZER;
            solver_init_method = "smooth";
        }
    }

    XCHECK(solver_init_traj.has_value());
    if (IsOccDebugEnabled()) {
        WriteOccDdpCsvPolyline(
            csv_ctx, "ego_traj_init", "ego_traj_init",
            ExtractTrajectoryPositions(*solver_init_traj));
    }

    std::vector<std::unique_ptr<Cost<Mfob>>> solver_helper_costs;
    if ((input.lc_stage == LaneChangeStage::LCS_NONE) && !input.borrow_lane) {
        auto extent_lant_path = drive_passage.extend_lane_path();
        auto lane_ids = extent_lant_path.lane_ids();
        bool has_split = false;
        bool is_construction_scene = false;
        // TODO:(xiaochang)
        has_split = drive_passage.GetHasSplit();
        // for (const auto &lane_id : lane_ids) {
        //   auto lane_info =
        //       input.planner_semantic_map_mgr->map_ptr()->GetLaneById(lane_id);
        //   if (lane_info && (lane_info->split_topology() ==
        //                         ads_x::planning::TOPOLOGY_SPLIT_LEFT ||
        //                     lane_info->split_topology() ==
        //                         ads_x::planning::TOPOLOGY_SPLIT_RIGHT)) {
        //     has_split = true;
        //     break;
        //   }
        // }

        for (const auto &stationary_obj : st_traj_mgr.stationary_objects()) {
            if (stationary_obj.planner_object.type() !=
                    (ObjectType::OT_UNKNOWN_STATIC) &&
                (stationary_obj.planner_object.type() !=
                    ObjectType::OT_WARNING_TRIANGLE) &&
                (stationary_obj.planner_object.type() != ObjectType::OT_CONE) &&
                stationary_obj.planner_object.type() !=
                    ObjectType::OT_BARRIER) {
                continue;
            }
            ASSIGN_OR_CONTINUE(const auto frenet_box,
                               drive_passage.QueryFrenetBoxAtContour(
                                   stationary_obj.planner_object.contour()));
            if (frenet_box.s_min < std::max(40.0, 4.0 * plan_start_point.v())) {
                auto target_boundary_l =
                    path_sl_boundary.QueryTargetBoundaryL(frenet_box.s_min);
                double right_l = target_boundary_l.first;
                double left_l = target_boundary_l.second;
                if ((frenet_box.l_min > right_l) && (frenet_box.l_max < left_l)) {
                    is_construction_scene = true;
                    break;
                }
            }
        }

        if (!has_split && !is_construction_scene) {
            optimizer::AddSolidWhiteLineCost(
                sample_traj_info.trajectory_steps, base_name_with_plan_id,
                *solver_init_traj, constraint_manager, initializer_traj.front(),
                trajectory_optimizer_params.cost_weight_params(),
                veh_geo_params,
                vehicle_models_params
                    .trajectory_optimizer_vehicle_model_params(),
                stations_query_helper, &solver_helper_costs);
        }
    }

    for (auto &cost : solver_helper_costs) {
        problem->AddCost(std::move(cost));
    }

    /**
     *这一层会加入一些体感优化的cost
     */
    DdpOptimizer<Mfob> solver(
        input.plan_id, problem.get(), sample_traj_info.dense_trajectory_steps,
        sample_traj_info.sparse_trajectory_steps, "trajectory_optimizer",
        FLAGS_traj_opt_verbosity_level,
        trajectory_optimizer_params.optimizer_params());

    TrajectoryOptimizerOutput output;

    // 1) 构造 solver_debug_hook（原来在栈上，现在交给 ddp_debug_args 持有）
    output.ddp_debug_args.solver_debug_hook =
        std::make_unique<OptimizerSolverDebugHook<Mfob>>(
            sample_traj_info.trajectory_steps, initializer_traj_start_point,
            st_traj_mgr);

    // 2) 收集同一批 cost 指针
    std::vector<Cost<Mfob> *> costs_ptrs;
    costs_ptrs.reserve(problem->costs().size());
    for (const auto &c : problem->costs()) {
      costs_ptrs.push_back(c.get());
    }

    // 3) 构造 perstep_hook，同样由 ddp_debug_args 持有
    output.ddp_debug_args.perstep_hook =
        std::make_unique<PerStepCostRecorderHook<Mfob>>(
            sample_traj_info.trajectory_steps, costs_ptrs,
            /* enable = */ true,
            /* tol = */ 1e-4);

    // Hooks are useful for HMI cost breakdown, but their end-of-solve state
    // copies and per-step cost replay are not needed by the onboard solver.
    // Keep the objects alive for the existing debug-message path, while
    // allowing latency-sensitive replay to skip registering them.
    const char* debug_hooks_env = std::getenv("PP_DDP_DEBUG_HOOKS");
    const bool enable_debug_hooks =
        IsPathPlannerDebugProtoEnabled() &&
        (debug_hooks_env == nullptr || debug_hooks_env[0] != '0');
    if (enable_debug_hooks) {
        solver.AddHook(output.ddp_debug_args.solver_debug_hook.get());
        solver.AddHook(output.ddp_debug_args.perstep_hook.get());
    }

    std::vector<TrajectoryPoint> result_points;

    std::string error_code;
    bool optimizer_solve_success = true;

    Timer solve_start_time;
    auto solver_output = solver.Solve(
        *solver_init_traj, DdpOptimizer<Mfob>::SolveConfig::Onboard(),
        is_compare_weight);
    const double solve_time = solve_start_time.TimeNs() / 1e6;

    if (!solver_output.ok()) {
        error_code = std::string(solver_output.status().message());
        optimizer_solve_success = false;
    } else {
        result_points = std::move(*solver_output);
        AddSteerAngleToPoints(veh_geo_params.wheel_base(),
                              veh_drive_params.steer_ratio(), &result_points);
        if (IsOccDebugEnabled()) {
            WriteOccDdpCsvPolyline(
                csv_ctx, "ego_traj_final", "ego_traj_final",
                ExtractTrajectoryPositions(result_points));
        }
    }


    // ToDebugProto(initializer_traj, solver_init_traj.get(), result_points,
    //              solver_debug_hook, perstep_hook, solver_init_traj_source,
    //              optimizer_debug, thread_pool);


    output.ddp_debug_args.solve_time_ms = solve_time;
    output.ddp_debug_args.add_cost_time_ms = add_cost_time;
    output.sample_step_info = sample_traj_info;

    if (IsPathPlannerDebugProtoEnabled()) {
        output.ddp_debug_args.astart_traj = optimizer_input_traj;
        output.ddp_debug_args.solve_init_traj = solver_init_traj.get();
        output.ddp_debug_args.final_traj = result_points;
        output.ddp_debug_args.solver_init_traj_source =
            absl::StrCat(solver_init_method, "+",
                         use_plan_start ? "use-plan-start"
                                        : "keep-init-start");
        output.ddp_debug_args.nudge_infos = input.nudge_info;

        for (const auto &id : static_object_ids) {
          NudgeObjectInfo static_nudge_info;
          static_nudge_info.id = id;
          output.ddp_debug_args.nudge_infos.addStaticNudgeInfo(static_nudge_info);
        }

        output.ddp_debug_args.solve_init_traj_l_info.reserve(result_points.size());
        output.ddp_debug_args.final_traj_l_info.reserve(result_points.size());

        const auto& frenet_frame = drive_passage.frenet_frame();
        const size_t n = std::min(solver_init_traj->size(), result_points.size());
        for (size_t i = 0; i < n; ++i) {
            const auto& init_pos = (*solver_init_traj)[i].pos();
            const auto& final_pos = result_points[i].pos();

            const auto init_sl = frenet_frame->XYToSL(init_pos);
            const auto final_sl = frenet_frame->XYToSL(final_pos);

            output.ddp_debug_args.solve_init_traj_l_info.emplace_back(init_sl.l);
            output.ddp_debug_args.final_traj_l_info.emplace_back(final_sl.l);
        }
    }

    DestroyContainerAsyncMarkSource(std::move(problem), std::string{});

    if (!optimizer_solve_success) {
        return absl::InternalError(error_code);
    }
    const auto validation_status = optimizer::ValidateTrajectory(
        result_points,
        trajectory_optimizer_params.trajectory_optimizer_validation_params(),
        *optimizer_debug, veh_geo_params.wheel_base(),
        veh_drive_params.steer_ratio());
    if (!validation_status.ok()) {
        return absl::InternalError(BuildDdpValidationFailureMessage(
            *output.ddp_debug_args.solver_debug_hook, validation_status));
    }



    // TODO:(xc)
    // const auto nudge_object_info = optimizer::ExtractNudgeObjectId(
    //     dense_trajectory_steps, sparse_trajectory_steps,
    //     dense_trajectory_time_step, sparse_trajectory_time_step,
    //     input.lc_stage, drive_passage, path_sl_boundary, result_points,
    //     input.previous_trajectory, st_planner_object_traj, veh_geo_params,
    //     input.nudge_object_info, input.borrow_lane,
    //     &output.borrow_direction);
    // if (nudge_object_info.ok()) {
    //   output.nudge_object_info = *nudge_object_info;
    //   if (output.nudge_object_info.has_value()) {
    //   }
    // }

    // 记录上一帧轨迹信息
    std::vector<ApolloTrajectoryPointProto> output_traj =
        ToApolloTrajectoryPointProto(result_points);
    output_trajectory_optimizer_state.last_optimized_trajectory = result_points;
    output_trajectory_optimizer_state.apollo_last_optimized_trajectory =
        output_traj;
    output_trajectory_optimizer_state.last_plan_start_time = input.plan_start_time;
    output.trajectory_optimizer_state = std::move(output_trajectory_optimizer_state);

    if (IsPathPlannerDebugProtoEnabled()) {
        output.trajectory_proto = ToApolloTrajectoryPointProto(result_points);
    }
    output.trajectory = std::move(result_points);
    return output;
}

}  // namespace planning
}  // namespace pnc_x
