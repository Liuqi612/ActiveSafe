#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "async/thread_pool.h"
#include "common/path_sl_boundary.h"
#include "common/plan_start_point_info.h"
#include "initializer/search_motion.h"
#include "maps/lane_path.h"
#include "maps/lane_path_data.h"
#include "math/frenet_frame.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "optimization/ddp/trajectory_optimizer.h"
#include "optimization/ddp/trajectory_optimizer_util.h"
#include "pncx_initializer_config.pb.h"
#include "pncx_optimizer.pb.h"
#include "pncx_planner_params.pb.h"
#include "pncx_trajectory_point.pb.h"
#include "pncx_vehicle.pb.h"
#include "router/drive_passage.h"
#include "scheduler/lane_evasion_status.h"
#include "scheduler/scheduler_output.h"
#include "util/file_util.h"

namespace {

using pnc_x::planning::TrajectoryOptimizerDebugProto;

using pnc_x::FrenetBox;
using pnc_x::ThreadPool;
using pnc_x::Vec2d;
using pnc_x::planning::DrivePassage;
using pnc_x::planning::LaneEvadeInfo;
using pnc_x::planning::PathSlBoundary;
using pnc_x::planning::SpacetimePlannerObjectTrajectories;
using pnc_x::planning::SpacetimeTrajectoryManager;
using pnc_x::planning::Station;
using pnc_x::planning::StationBoundary;
using pnc_x::planning::StationBoundaryType;
using pnc_x::planning::StationCenter;
using pnc_x::planning::StationVector;
using pnc_x::planning::StPathPlanStartPointInfo;

DrivePassage MakeStraightDrivePassage() {
    // A synthetic centre line is sufficient for a deterministic algorithm
    // smoke: all stations share one lane and have constant tangent/width.
    constexpr int kStationCount = 101;
    StationVector<Station> stations;
    stations.reserve(kStationCount);
    for (int i = 0; i < kStationCount; ++i) {
        StationCenter center;
        center.lane_id = 1;
        center.fraction = static_cast<double>(i) / (kStationCount - 1);
        center.xy = Vec2d(static_cast<double>(i), 0.0);
        center.tangent = Vec2d(1.0, 0.0);
        center.accum_s = static_cast<double>(i);
        center.speed_limit = 15.0;
        center.turn_type = ads_x::planning::NO_TURN;
        center.station_info.speed_limit = 15.0;
        stations.emplace_back(center,
                              std::vector<StationBoundary>{
                                  {StationBoundaryType::BROKEN_WHITE, -2.0},
                                  {StationBoundaryType::BROKEN_WHITE, 2.0}});
    }

    const pnc_x::mapping::LanePathData lane_path_data(0.0, 1.0, {1});
    const pnc_x::mapping::LanePath lane_path(lane_path_data, {0.0, 100.0},
                                             {100.0});
    return DrivePassage(std::move(stations), lane_path, lane_path, 0.0, false,
                        pnc_x::FrenetFrameType::kBruteFroce, {});
}

PathSlBoundary MakeStraightPathBoundary() {
    std::vector<double> s;
    std::vector<double> ref_l;
    std::vector<double> right_l;
    std::vector<double> left_l;
    std::vector<Vec2d> ref_xy;
    std::vector<Vec2d> right_xy;
    std::vector<Vec2d> left_xy;
    for (int i = 0; i <= 10; ++i) {
        const double station_s = i * 10.0;
        s.push_back(station_s);
        ref_l.push_back(0.0);
        right_l.push_back(-2.0);
        left_l.push_back(2.0);
        ref_xy.emplace_back(station_s, 0.0);
        right_xy.emplace_back(station_s, -2.0);
        left_xy.emplace_back(station_s, 2.0);
    }
    const auto opt_right_l = right_l;
    const auto opt_left_l = left_l;
    const auto target_right_l = right_l;
    const auto target_left_l = left_l;
    const auto opt_right_xy = right_xy;
    const auto opt_left_xy = left_xy;
    const auto target_right_xy = right_xy;
    const auto target_left_xy = left_xy;
    return PathSlBoundary(std::move(s), std::move(ref_l), std::move(right_l),
                          std::move(left_l), opt_right_l, opt_left_l,
                          target_right_l, target_left_l, std::move(ref_xy),
                          std::move(right_xy), std::move(left_xy), opt_right_xy,
                          opt_left_xy, target_right_xy, target_left_xy);
}

pnc_x::ApolloTrajectoryPointProto MakeStartPoint() {
    pnc_x::ApolloTrajectoryPointProto point;
    auto *path = point.mutable_path_point();
    path->set_x(0.0);
    path->set_y(0.0);
    path->set_s(0.0);
    path->set_theta(0.0);
    path->set_kappa(0.0);
    point.set_v(5.0);
    point.set_a(0.0);
    point.set_j(0.0);
    point.set_relative_time(0.0);
    return point;
}

pnc_x::VehicleParamsProto MakeVehicleParams() {
    pnc_x::VehicleParamsProto params;
    auto *geometry = params.mutable_vehicle_geometry_params();
    geometry->set_front_edge_to_center(3.5);
    geometry->set_back_edge_to_center(1.0);
    geometry->set_left_edge_to_center(1.0);
    geometry->set_right_edge_to_center(1.0);
    geometry->set_length(4.5);
    geometry->set_width(2.0);
    geometry->set_wheel_base(2.7);
    auto *drive = params.mutable_vehicle_drive_params();
    drive->set_steer_ratio(16.0);
    drive->set_max_steer_angle(0.6);
    return params;
}

bool LoadTestProto(const std::string &file_name,
                   google::protobuf::Message *message) {
    // 使用原 Planning Node 的完整 Normal 配置，避免测试夹具手工猜测算法
    // 参数或遗漏 PLF 等隐式必填项。配置只用于测试，不进入生产目标。
    const std::string config_path =
        std::string(TAP_PLANNING_TEST_DATA_DIR) + "/" + file_name;
    if (!pnc_x::file_util::TextFileToProto(config_path, message)) {
        std::cerr << "Failed to load Planning test config: " << config_path
                  << '\n';
        return false;
    }
    return true;
}

}  // namespace

int main() {
    // First prove the complete Normal path with no RSCL messages involved.
    // This is intentionally a small, deterministic fixture: it exercises the
    // same stage boundary as production while making failures attributable to
    // the algorithm port rather than to an unavailable map/replay input.
    const auto drive_passage = MakeStraightDrivePassage();
    const auto path_sl_boundary = MakeStraightPathBoundary();
    const auto start_point = MakeStartPoint();
    const auto vehicle_params = MakeVehicleParams();
    pnc_x::PlannerParamsProto planner_params;
    pnc_x::TrajectoryOptimizerParamsProto trajectory_optimizer_params;
    if (!LoadTestProto("planner_default_params.pb.txt", &planner_params) ||
        !LoadTestProto("trajectory_optimizer_default_params.pb.txt",
                       &trajectory_optimizer_params)) {
        return 1;
    }
    const auto initializer_params = planner_params.initializer_params();
#if TAP_PLANNING_DP_SMOKE
    // DP is a reference-only build/smoke target.  It is deliberately selected
    // here, outside the production TAP runtime target.
    auto selected_initializer_params = initializer_params;
    selected_initializer_params.set_search_algorithm(
        pnc_x::planning::InitializerConfig::DP);
#else
    if (initializer_params.search_algorithm() !=
        pnc_x::planning::InitializerConfig::InteractiveAStar) {
        std::cerr << "Emergency test config does not select Interactive A*\n";
        return 1;
    }
    const auto &selected_initializer_params = initializer_params;
#endif
    const absl::Time plan_time = absl::FromUnixSeconds(1000);

    ThreadPool thread_pool(0);
    SpacetimeTrajectoryManager st_traj_mgr;
    SpacetimePlannerObjectTrajectories st_planner_object_traj;
    st_planner_object_traj.SetExtendTrajectoryMap();
    pnc_x::LaneChangeStateProto lane_change_state;
    lane_change_state.set_stage(pnc_x::LaneChangeStage::LCS_NONE);
    absl::flat_hash_set<std::string> stalled_objects;
    pnc_x::planning::InitializerStateProto previous_initializer_state;
    pnc_x::DecisionConstraintConfigProto decision_config;
    pnc_x::planning::LaneEvadeInfo lane_evade_info;
    pnc_x::FrenetBox ego_frenet_box;
    ego_frenet_box.s_min = 0.0;
    ego_frenet_box.s_max = 4.5;
    ego_frenet_box.l_min = -1.0;
    ego_frenet_box.l_max = 1.0;
    std::map<std::string, pnc_x::planning::ConstraintProto::LeadingObjectProto>
        leading_trajs;
    std::unordered_map<std::string, std::shared_ptr<DrivePassage>>
        drive_passages;
    drive_passages.emplace("lk", std::make_shared<DrivePassage>(drive_passage));

    StPathPlanStartPointInfo path_start_point_info;
    path_start_point_info.reset = true;
    path_start_point_info.relative_index_from_plan_start_point = 0;
    path_start_point_info.start_point = start_point;
    path_start_point_info.plan_time = plan_time;
    pnc_x::planning::PlanStartPointInfo start_point_info;
    start_point_info.reset = true;
    start_point_info.start_point = start_point;
    start_point_info.plan_time = plan_time;

    pnc_x::planning::InitializerInput initializer_input;
    initializer_input.path_start_point_info = &path_start_point_info;
    initializer_input.path_look_ahead_duration = absl::Seconds(6);
    initializer_input.lane_change_state = &lane_change_state;
    initializer_input.drive_passage = &drive_passage;
    initializer_input.st_traj_mgr = &st_traj_mgr;
    initializer_input.sl_boundary = &path_sl_boundary;
    initializer_input.prev_initializer_state = &previous_initializer_state;
    initializer_input.decision_constraint_config = &decision_config;
    initializer_input.initializer_params = &selected_initializer_params;
    pnc_x::MotionConstraintParamsProto motion_constraint_params;
    motion_constraint_params.set_default_speed_limit(15.0);
    motion_constraint_params.set_default_reverse_speed_limit(0.0);
    motion_constraint_params.set_max_deceleration(-5.0);
    motion_constraint_params.set_max_acceleration(2.0);
    motion_constraint_params.set_max_decel_jerk(-5.0);
    motion_constraint_params.set_max_accel_jerk(5.0);
    motion_constraint_params.set_max_psi(0.2);
    motion_constraint_params.set_max_lateral_accel(2.7);
    motion_constraint_params.set_max_lateral_jerk(2.3);
    motion_constraint_params.set_max_chi(0.2);
    initializer_input.motion_constraint_params = &motion_constraint_params;
    initializer_input.vehicle_params = &vehicle_params;
    initializer_input.st_planner_object_traj = &st_planner_object_traj;
    initializer_input.leading_trajs = &leading_trajs;
    initializer_input.av_frenet_box = &ego_frenet_box;
    initializer_input.stalled_objects = &stalled_objects;
    initializer_input.start_point_info = &start_point_info;
    initializer_input.lane_evade_info = &lane_evade_info;
    initializer_input.drive_passages = &drive_passages;

    pnc_x::planning::SchedulerOutput scheduler_output;
    pnc_x::planning::DeciderOutput decider_output;
    pnc_x::planning::InitializerDebugProto initializer_debug;
    absl::flat_hash_set<std::string> unsafe_object_ids;
    std::map<std::string, bool> object_leading;
    auto lane_change_status = pnc_x::planning::PlannerStatusProto::OK;
    double last_lane_offset = 0.0;
    const auto initializer_or = pnc_x::planning::RunInitializer(
        initializer_input, &unsafe_object_ids, &scheduler_output,
        &decider_output, &initializer_debug, &thread_pool, &object_leading,
        &lane_change_status, &last_lane_offset);
    if (!initializer_or.ok()) {
        std::cerr << "Interactive A* initializer failed: "
                  << initializer_or.status().message() << '\n';
        return 1;
    }
    const auto &initializer_output = initializer_or.value();
    if (initializer_output.traj_points.size() < 10) {
        std::cerr << "Interactive A* returned only "
                  << initializer_output.traj_points.size() << " points\n";
        return 1;
    }

    pnc_x::PlannerVehicleModelParamsProto vehicle_models_params;
    auto *circle_model =
        vehicle_models_params
            .mutable_trajectory_optimizer_vehicle_model_params();
    auto *circle = circle_model->add_circles();
    circle->set_dist_to_rac(0.0);
    circle->set_angle_to_axis(0.0);
    circle->set_radius(1.1);
    pnc_x::PlannerFunctionsParamsProto planner_functions_params;
    ads_x::planning::EntryFuncSmoothInfo entry_func_smooth_info;
    pnc_x::planning::ConstraintManager constraint_manager =
        decider_output.constraint_manager;
    pnc_x::planning::TrajectoryOptimizerInput optimizer_input;
    optimizer_input.trajectory = initializer_output.traj_points;
    optimizer_input.st_traj_mgr = &st_traj_mgr;
    optimizer_input.st_planner_object_traj = &st_planner_object_traj;
    optimizer_input.drive_passage = &drive_passage;
    optimizer_input.path_sl_boundary = &path_sl_boundary;
    optimizer_input.constraint_mgr = &constraint_manager;
    optimizer_input.leading_trajs = &initializer_output.leading_trajs;
    optimizer_input.lane_evade_info = &lane_evade_info;
    optimizer_input.plan_start_point = start_point;
    optimizer_input.plan_start_time = plan_time;
    optimizer_input.plan_id = 1;
    optimizer_input.lc_stage = pnc_x::LaneChangeStage::LCS_NONE;
    optimizer_input.lane_change_state = lane_change_state;
    optimizer_input.trajectory_optimizer_params = &trajectory_optimizer_params;
    optimizer_input.motion_constraint_params = &motion_constraint_params;
    optimizer_input.planner_functions_params = &planner_functions_params;
    optimizer_input.vehicle_models_params = &vehicle_models_params;
    optimizer_input.veh_geo_params = &vehicle_params.vehicle_geometry_params();
    optimizer_input.veh_drive_params = &vehicle_params.vehicle_drive_params();
    optimizer_input.entry_func_smooth_info = &entry_func_smooth_info;
    optimizer_input.ego_frenet_box = &ego_frenet_box;
    optimizer_input.dynamic_time_headway = 1.5;

    TrajectoryOptimizerDebugProto optimizer_debug;
    const auto optimized_or = pnc_x::planning::OptimizeTrajectory(
        optimizer_input, &optimizer_debug, false, &thread_pool);
    if (!optimized_or.ok()) {
        std::cerr << "DDP optimization failed: "
                  << optimized_or.status().message() << '\n';
        return 1;
    }
    if (optimized_or->trajectory.size() < 10) {
        std::cerr << "DDP returned only " << optimized_or->trajectory.size()
                  << " points\n";
        return 1;
    }

    const auto valid = pnc_x::planning::optimizer::ValidateTrajectory(
        optimized_or->trajectory,
        trajectory_optimizer_params.trajectory_optimizer_validation_params(),
        optimizer_debug, vehicle_params.vehicle_geometry_params().wheel_base(),
        vehicle_params.vehicle_drive_params().steer_ratio());
    if (!valid.ok()) {
        std::cerr << "DDP trajectory validation failed: " << valid.message()
                  << '\n';
        return 1;
    }

    auto params =
        trajectory_optimizer_params.trajectory_optimizer_validation_params();
    params.set_max_final_cost(-1.0);
    const auto invalid = pnc_x::planning::optimizer::ValidateTrajectory(
        optimized_or->trajectory, params, optimizer_debug,
        vehicle_params.vehicle_geometry_params().wheel_base(),
        vehicle_params.vehicle_drive_params().steer_ratio());
    if (invalid.ok()) {
        std::cerr << "invalid final-cost limit was accepted\n";
        return 1;
    }

    std::cout << "Emergency smoke passed: initializer="
              << (selected_initializer_params.search_algorithm() ==
                          pnc_x::planning::InitializerConfig::DP
                      ? "DP(reference)"
                      : "Interactive A*")
              << " points=" << initializer_output.traj_points.size()
              << ", DDP points=" << optimized_or->trajectory.size()
              << ", ValidateTrajectory=passed\n";
    return 0;
}
