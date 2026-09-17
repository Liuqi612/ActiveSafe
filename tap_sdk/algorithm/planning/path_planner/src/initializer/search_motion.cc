

#include "initializer/search_motion.h"

#include <algorithm>
#include <map>
#include <memory>
#include <ostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "async/async_util.h"
#include "common/timer.h"
#include "maps/map_def.h"
#include <absl/container/flat_hash_set.h>
#include <absl/status/status.h>
#include <absl/strings/str_cat.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>
#include <absl/types/span.h>
#include "common/log.h"

#include "common/path_sl_boundary.h"
#include "common/plan_start_point_info.h"
#include "pncx_constraint.pb.h"
#include "decision/decider_input.h"
#include "decision/decision_util.h"
#include "decision/obstacle_intention_estimation.h"
#include "pncx_initializer.pb.h"
#include "initializer/collision_checker.h"
#include "initializer/geometry/geometry_form_builder.h"
#include "initializer/geometry/geometry_graph.h"
#include "initializer/geometry/geometry_graph_builder.h"
#include "initializer/geometry/geometry_graph_cache.h"
#include "initializer/initializer_util.h"
#include "initializer/motion_searcher.h"
#include "initializer/reference_line_searcher.h"
#include "pncx_initializer_config.pb.h"
#include "pncx_lane_change.pb.h"
#include "scheduler/path_boundary_builder.h"

#include "math/frenet_common.h"
#include "math/geometry/util.h"
#include "math/util.h"
#include "math/vec.h"

#include "object/planner_object.h"
#include "object/spacetime_object_trajectory.h"
#include "object/spacetime_trajectory_manager.h"

#include "common/planning_macros.h"
#include "initializer/interactive_search/map/grid_map.h"
#include "plan/planner_defs.h"
#include "plan/planner_flags.h"
#include "router/drive_passage.h"
#include "pncx_trajectory_point.pb.h"
#include "util/status_builder.h"
#include "util/status_macros.h"
#include "util/time_util.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {
namespace {

constexpr double kHighSpeedThreshold = 14.0;
constexpr double kMediumSpeedThreshold = 8.0;
constexpr double kLowSpeedThreshold = 2.0;
constexpr double kSpeedHysteresis = 1.0;
constexpr double kStationaryObjectCollisionBuffer = 0.3;
constexpr double kMovingObjectCollisionBuffer = 0.5;
constexpr double kReduceStaticBufferThresholdS = 15.0;
constexpr double kMaxSamplingDistance = 220.0;
constexpr double kMaxSamplingLookForwardTime = 8.0;
constexpr double kMinSamplingDistance = 60.0;
constexpr double kInitializerLKTimeConsumptionReportThreshold = 30.0;
constexpr double kInitializerLCTimeConsumptionReportThreshold = 50.0;
constexpr double kQeventSeconds = 5.0;

GeometryGraphSamplingStrategy ParseStrategy(
    const InitializerConfig::InitializerSamplePattern &sample_pattern,
    bool is_lane_change) {
    GeometryGraphSamplingStrategy strategy;

    strategy.is_lane_change = is_lane_change;
    const int config_len = sample_pattern.config().range().size();
    strategy.range_list.reserve(static_cast<std::size_t>(config_len));
    strategy.layer_gap_list.reserve(static_cast<std::size_t>(config_len));
    strategy.lateral_resolution_list.reserve(static_cast<std::size_t>(config_len));
    strategy.cross_layer_connection_list.reserve(static_cast<std::size_t>(config_len));
    strategy.unit_length_lateral_span_list.reserve(static_cast<std::size_t>(config_len));

    for (const auto &val : sample_pattern.config().range()) {
        strategy.range_list.push_back(val);
    }
    for (const auto &val : sample_pattern.config().layer_gap()) {
        strategy.layer_gap_list.push_back(val);
    }
    for (const auto &val : sample_pattern.config().lateral_resolution()) {
        strategy.lateral_resolution_list.push_back(val);
    }
    for (const auto &val : sample_pattern.config().cross_layer_connection()) {
        strategy.cross_layer_connection_list.push_back(static_cast<int>(val));
    }
    for (const auto &val : sample_pattern.config().unit_length_lateral_span()) {
        strategy.unit_length_lateral_span_list.push_back(val);
    }
    return strategy;
}

GeometryGraphSamplingStrategy FindStrategy(
    InitializerSamplePatternConfig sample_pattern_config,
    const InitializerConfig &initializer_config,
    bool is_lane_change) {
    const auto scenario =
        is_lane_change
            ? InitializerConfig::InitializerSamplePattern::SCENARIO_LANE_CHANGE
            : InitializerConfig::InitializerSamplePattern::
                  SCENARIO_LANE_KEEPING;

    for (const auto &sample_pattern : initializer_config.sample_patterns()) {
        if (sample_pattern.config_name() == sample_pattern_config &&
            sample_pattern.scenario() == scenario) {
            return ParseStrategy(sample_pattern, is_lane_change);
        }
    }

    XCHECK(false);
    return GeometryGraphSamplingStrategy();
}

InitializerSamplePatternConfig FindPattern(
    double cur_v, InitializerSamplePatternConfig prev_sample_config) {
    double high_speed_threshold = kHighSpeedThreshold;
    double medium_speed_threshold = kMediumSpeedThreshold;
    double low_speed_threshold = kLowSpeedThreshold;
    switch (prev_sample_config) {
        case InitializerSamplePatternConfig::ISC_NONE:
            break;
        case InitializerSamplePatternConfig::ISC_HIGH_SPEED:
            high_speed_threshold = high_speed_threshold - kSpeedHysteresis;
            break;
        case InitializerSamplePatternConfig::ISC_MEDIUM_SPEED:
            medium_speed_threshold = medium_speed_threshold - kSpeedHysteresis;
            break;
        case InitializerSamplePatternConfig::ISC_LOW_SPEED:
            break;
        case InitializerSamplePatternConfig::ISC_CREEP_SPEED:

            low_speed_threshold = low_speed_threshold + kSpeedHysteresis;
            break;
    }
    if (cur_v > high_speed_threshold) {
        return InitializerSamplePatternConfig::ISC_HIGH_SPEED;
    } else if (cur_v > medium_speed_threshold) {
        return InitializerSamplePatternConfig::ISC_MEDIUM_SPEED;
    } else if (cur_v > low_speed_threshold) {
        return InitializerSamplePatternConfig::ISC_LOW_SPEED;
    } else {
        return InitializerSamplePatternConfig::ISC_CREEP_SPEED;
    }
}

std::pair<InitializerSamplePatternConfig, GeometryGraphSamplingStrategy>
GetSamplingStrategy(const InitializerConfig &config,
                    bool is_lane_change,
                    double cur_v,
                    InitializerSamplePatternConfig prev_sample_config) {
    InitializerSamplePatternConfig cur_pattern =
        FindPattern(cur_v, prev_sample_config);
    GeometryGraphSamplingStrategy strategy =
        FindStrategy(cur_pattern, config, is_lane_change);
    return std::make_pair(cur_pattern, std::move(strategy));
}

std::vector<double> ConvertStoplineToStopS(
    absl::Span<const ConstraintProto::StopLineProto> stoplines,
    double front_to_ra) {
    std::vector<double> stop_s;
    stop_s.reserve(stoplines.size());
    for (const auto &stop_line : stoplines) {
        stop_s.push_back(std::max(stop_line.s() - front_to_ra, 0.0));
    }
    return stop_s;
}

bool EnableInitializerLaneChangeTargetDecision(
    const LaneChangeStateProto &lc_state, const FrenetBox &av_frenet_box) {
    return (lc_state.stage() == LaneChangeStage::LCS_EXECUTING ||
            lc_state.stage() == LaneChangeStage::LCS_PAUSE);
}

}  // namespace

absl::StatusOr<MotionSearchOutput> SearchMotion(const MotionSearchInput &input,
                                                ThreadPool *thread_pool,
                                                int plan_id) {
    SCOPED_TRACE("EstPlanner/SearchMotion");

    absl::StatusOr<MotionSearchOutput> output_or;

    output_or = SearchForRawTrajectory(input, thread_pool, plan_id);

    return output_or;
}

absl::StatusOr<TrafficGapResult> EvaluateBestGapFromSearch(
    const MotionSearchOutput &motion_out, const InitializerConfig &config) {
    if (motion_out.traj_points.empty()) {
        return absl::NotFoundError("trajectory points empty");
    }

    if (!motion_out.first_safe_to_gap_index.has_value() ||
        motion_out.first_safe_to_gap_index.value() < 0 ||
        motion_out.first_safe_to_gap_index.value() >=
            motion_out.traj_points.size()) {
        return absl::NotFoundError("first safe to gap index not valid");
    }

    TrafficGapResult gap;
    VTCurve vt_curve;

    for (const auto &pt : motion_out.traj_points) {
        vt_curve.AddPoint(pt.relative_time(), pt.v());
    }

    gap.gap_vt_curve = std::move(vt_curve);

    if (motion_out.obs_gap.is_merge_safe.first) {
        gap.leader_id = motion_out.obs_gap.lead_obj_id;
        gap.follower_id = motion_out.obs_gap.tail_obj_id;
    }

    const auto first_point = motion_out.traj_points[1];
    const auto target_point =
        motion_out.traj_points[static_cast<std::size_t>(motion_out.first_safe_to_gap_index.value())];

    double a = 0.0;
    if (motion_out.first_safe_to_gap_index.value() < 2) {
        a = first_point.a();
    } else {
        a = (target_point.v() - first_point.v()) /
            (target_point.relative_time() - first_point.relative_time());
    }
    const auto &safety_config =
        config.interactive_astar_search_config().gap_safety_check_param();
    if (a < 0.0) {
        gap.dec_gap_target_a = a;
        gap.dec_gap_target_speed = target_point.v();
    } else {
        gap.acc_gap_target_a = a;
        gap.acc_gap_target_speed = target_point.v();

        gap.ori_lead_id = motion_out.obs_gap.ori_lead_obj_id;
        gap.bargain_ori_lead_headway = motion_out.thw[2] + 0.3;
    }

    return gap;
}

inline std::string ExtractBaseId(const std::string &obj_id) {
    auto pos = obj_id.find("-idx");
    if (pos != std::string::npos) {
        return obj_id.substr(0, pos);
    }
    return obj_id;
}

std::vector<ConstraintProto::LeadingObjectProto> FindLeadingObjects(
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        &leading_trajs,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const DrivePassage &passage) {
    std::vector<ConstraintProto::LeadingObjectProto> leading_objects;
    leading_objects.reserve(leading_trajs.size());

    for (const auto &kv : leading_trajs) {
        const std::string &obj_id = kv.first;
        const auto &hint = kv.second;

        absl::Span<const SpacetimeObjectTrajectory *const>
            leading_object_trajectorys =
                st_traj_mgr.FindTrajectoriesByObjectId(ExtractBaseId(obj_id));
        if (leading_object_trajectorys.empty() ||
            leading_object_trajectorys[0] == nullptr) {
            continue;
        }

        ConstraintProto::LeadingObjectProto leading_object = hint;
        leading_object.mutable_gap_proto()->set_leader_id(obj_id);
        leading_object.mutable_gap_proto()->set_follower_id("");
        leading_objects.push_back(std::move(leading_object));
    }

#if 0
    const auto find_traj = [&st_planner_object_traj](const std::string &id)
        -> boost::optional<SpacetimeObjectTrajectory> {
        for (const auto &it : *st_planner_object_traj.extended_trajectories) {
            if (id == it.object_id()) {
                return it;
            }
        }
        return {};
    };

    for (const auto &traj_info : st_planner_object_traj.trajectory_infos) {
        auto &id = traj_info.object_id;
        if (traj_info.reason ==
            SpacetimePlannerObjectTrajectoryReason::LEADING) {
            auto traj = find_traj(traj_info.object_id);
            if (!traj.has_value()) {
                continue;
            }
            ConstraintProto::LeadingObjectProto leading_object =
                CreateLeadingObject(
                    traj.value(), passage,
                    ConstraintProto::LeadingObjectProto::UNABLE_TO_OVERTAKE);
            leading_object.mutable_gap_proto()->set_leader_id(
                traj_info.object_id);
            leading_object.mutable_gap_proto()->set_follower_id("");
            leading_objects.push_back(std::move(leading_object));
        }
    }

#endif

    return leading_objects;
}

absl::StatusOr<InitializerOutput> RunInitializer(
    const InitializerInput &initializer_input,
    absl::flat_hash_set<std::string> *unsafe_object_ids,
    SchedulerOutput *scheduler_output,
    DeciderOutput *decider_output,
    InitializerDebugProto *debug_proto,
    ThreadPool *thread_pool,
    std::map<std::string, bool> *obj_leading,
    PlannerStatusProto::PlannerStatusCode *lc_status_code,
    double *last_lane_offset) {
    SCOPED_TRACE("EstPlanner/RunInitializer");
    Timer timer(__FUNCTION__);

    if (initializer_input.path_start_point_info == nullptr ||
        initializer_input.vehicle_params == nullptr ||
        scheduler_output == nullptr || debug_proto == nullptr ||
        thread_pool == nullptr || initializer_input.st_traj_mgr == nullptr ||
        initializer_input.drive_passages == nullptr) {
        // LOG(ERROR) << "Failed to initialize GeometryFormBuilder!";
        return absl::InternalError("Failed to initialize GeometryFormBuilder.");
        // return InitializerOutput{};
    }

    const auto plan_time = initializer_input.path_start_point_info->plan_time;
    const auto &lane_change_state = *initializer_input.lane_change_state;
    const auto &prev_lane_change_stage = initializer_input.prev_lc_stage;

    const auto &drive_passage = *initializer_input.drive_passage;
    const auto &st_traj_mgr = *initializer_input.st_traj_mgr;
    const auto &vehicle_geom =
        initializer_input.vehicle_params->vehicle_geometry_params();
    const auto &vehicle_drive =
        initializer_input.vehicle_params->vehicle_drive_params();
    auto path_sl_boundary = *initializer_input.sl_boundary;
    const auto &initializer_state = *initializer_input.prev_initializer_state;
    const auto &decision_constraint_config =
        *initializer_input.decision_constraint_config;
    const auto &initializer_params = *initializer_input.initializer_params;
    const auto &motion_constraint_params =
        *initializer_input.motion_constraint_params;
    const auto plan_id = initializer_input.plan_id;
    const auto &stalled_objects = *initializer_input.stalled_objects;
    const auto &st_planner_object_traj =
        *initializer_input.st_planner_object_traj;
    const auto &av_frenet_box = *initializer_input.av_frenet_box;
    ads_x::planning::TrafficLightStatusMap temp_tl_status_map;
    const auto &tl_status_map =
        (nullptr == initializer_input.traffic_light_status_map)
            ? temp_tl_status_map
            : *initializer_input.traffic_light_status_map;
    const auto &cur_leading_trajs = *initializer_input.leading_trajs;

    auto mutable_start_point =
        initializer_input.path_start_point_info->start_point;
    mutable_start_point.mutable_path_point()->set_theta(
        NormalizeAngle(mutable_start_point.path_point().theta()));
    const auto &path_start_point = mutable_start_point;

    const bool is_lane_change =
        (lane_change_state.stage() == LaneChangeStage::LCS_EXECUTING ||

         lane_change_state.stage() == LaneChangeStage::LCS_PAUSE);
    const bool is_uturn_scene =
        drive_passage.GetEgoTurnType() == ads_x::planning::U_TURN;

    if (initializer_input.push_dir == PushDirection::Push_Normal_Left) {
        scheduler_output->lane_change_state.set_push_state(
            PushState::LEFT_PUSH);
    } else if (initializer_input.push_dir == PushDirection::Push_Normal_Right) {
        scheduler_output->lane_change_state.set_push_state(
            PushState::RIGHT_PUSH);
    } else if (initializer_input.push_dir ==
               PushDirection::Push_Congestion_Left) {
        scheduler_output->lane_change_state.set_push_state(
            PushState::CONGESTION_LEFT_PUSH);
    } else if (initializer_input.push_dir ==
               PushDirection::Push_Congestion_Right) {
        scheduler_output->lane_change_state.set_push_state(
            PushState::CONGESTION_RIGHT_PUSH);
    } else {
        scheduler_output->lane_change_state.set_push_state(
            PushState::NONE_PUSH);
    }

    double last_used_target_lane_offset =
        initializer_input.last_used_target_lane_offset;
    bool is_evade = false;
    if (initializer_input.lane_evade_info != nullptr) {
        is_evade = initializer_input.lane_evade_info->is_evade;
    }

    if (scheduler_output->lane_change_state.push_state() !=
            PushState::NONE_PUSH ||
        is_evade || std::abs(last_used_target_lane_offset) > 1e-6 ||
        initializer_input.ref_centered_compensation_offset.has_value()) {
        ASSIGN_OR_RETURN(
            scheduler_output->sl_boundary,
            BuildPathBoundaryFromPose(
                drive_passage, initializer_input.start_point_info->start_point,
                *initializer_input.lane_evade_info, vehicle_geom, st_traj_mgr,
                scheduler_output->lane_change_state,
                *initializer_input.smooth_result_map,
                scheduler_output->borrow_lane, scheduler_output->should_smooth,
                &last_used_target_lane_offset,
                initializer_input.ref_centered_compensation_offset,
                scheduler_output->is_force_lc,
                scheduler_output->force_lc_offset_ratio,
                false, nullptr, false, false, is_uturn_scene),
            _ << " Lc_pushing Rebuilding path boundary failed.");

        path_sl_boundary = scheduler_output->sl_boundary;
        *last_lane_offset = last_used_target_lane_offset;
    }

    const auto ego_pos = Vec2dFromApolloTrajectoryPointProto(path_start_point);
    ASSIGN_OR_RETURN(const auto ego_sl,
                     drive_passage.QueryFrenetCoordinateAt(ego_pos),
                     _ << "Failed to project ego position on drive passage.");

    debug_proto->set_trajectory_start_timestamp(ToUnixDoubleSeconds(plan_time));

    double speed_limit = 0.0;
    for (const auto &station : drive_passage.stations()) {
        speed_limit += station.speed_limit();
    }
    speed_limit /= std::max(1, drive_passage.stations().size());
    const double passage_speed_limit =
        std::fmax(speed_limit, kMinSpeedForFinalCost);

    const double speed_dist =
        path_start_point.v() > passage_speed_limit
            ? path_start_point.v() * kMaxSamplingLookForwardTime
            : (passage_speed_limit - path_start_point.v() >
                       kMaxSamplingLookForwardTime
                   ? path_start_point.v() * kMaxSamplingLookForwardTime +
                         0.5 * kMaxSamplingLookForwardTime *
                             kMaxSamplingLookForwardTime
                   : 0.5 * (passage_speed_limit * passage_speed_limit -
                            path_start_point.v() * path_start_point.v()) +
                         passage_speed_limit *
                             (kMaxSamplingLookForwardTime -
                              passage_speed_limit + path_start_point.v()));
    const double sampling_dist_by_speed =
        initializer_input.borrow_lane
            ? std::fmax(speed_dist, kMinSamplingDistance)
            : std::fmax(path_start_point.v() * kMaxSamplingLookForwardTime,
                        kMinSamplingDistance);
    const double max_sampling_acc_s = std::min(
        drive_passage.end_s(),
        std::min(kMaxSamplingDistance, sampling_dist_by_speed) + ego_sl.s);

    double s_from_start = 0.0;
    if (!initializer_input.path_start_point_info->reset) {
        if (initializer_state.has_s_from_start() &&
            initializer_state.has_prev_start_point()) {
            const auto prev_pos = Vec2dFromApolloTrajectoryPointProto(
                initializer_state.prev_start_point());
            ASSIGN_OR_RETURN(const auto prev_sl,
                             drive_passage.QueryFrenetCoordinateAt(prev_pos),
                             _ << "Failed to project previous ego position ("
                               << prev_pos.transpose()
                               << ") on drive passage.");
            s_from_start =
                initializer_state.s_from_start() - prev_sl.s + ego_sl.s;
        }
    }

    const double s_from_start_with_diff = s_from_start - ego_sl.s;

    std::unique_ptr<GeometryFormBuilder> form_builder;
#if !TAP_PLANNING_EMERGENCY_ONLY
    if (initializer_params.search_algorithm() == InitializerConfig::DP) {
        form_builder = std::make_unique<GeometryFormBuilder>(
            &drive_passage, max_sampling_acc_s, s_from_start_with_diff);
        if (form_builder && !form_builder->InitResult()) {
            // LOG(ERROR) << "Failed to initialize GeometryFormBuilder!";
            return absl::InternalError(
                "Failed to initialize GeometryFormBuilder.");
        }
    } else {
        form_builder = std::make_unique<GeometryFormBuilder>();
    }
#else
    form_builder = std::make_unique<GeometryFormBuilder>();
#endif

    const double nearest_stop_s = initializer_input.nearest_stop_s;
    std::vector<double> stop_s_vec{nearest_stop_s};

    std::unordered_map<std::string, ObstacleBehavior> obstacles_behavior_map =
        InferObstaclesBehavior(drive_passage, path_sl_boundary, av_frenet_box,
                               st_planner_object_traj, path_start_point,
                               lane_change_state.lc_left(), is_lane_change);

    const bool enable_lc_multi_traj = EnableInitializerLaneChangeTargetDecision(
        lane_change_state, av_frenet_box);
    std::vector<LeadingGroup> leading_groups;
    std::vector<std::vector<std::string>> insertion_orders;
    bool is_first_lead = false;
    bool must_borrow = false;
    const bool is_astar_searcher = initializer_params.search_algorithm() ==
                                   InitializerConfig::InteractiveAStar;
    std::string current_path_leader_id;
    boost::optional<std::string> nullable_nearest_vru_object_id = boost::none;
    if (enable_lc_multi_traj) {
        // VLOG(3) << "lc_multiple_traj true: constructing leading object groups";
        leading_groups = FindMultipleLeadingGroups(
            drive_passage, path_sl_boundary, lane_change_state.lc_left(),
            st_planner_object_traj, stalled_objects, path_start_point,
            av_frenet_box, vehicle_geom, is_astar_searcher, &insertion_orders,
            &current_path_leader_id, initializer_input.drive_passages);
        leading_groups.push_back({});
        insertion_orders.push_back({});
        if (leading_groups.size() > 1 &&
            insertion_orders.size() == leading_groups.size()) {
            scheduler_output->leading_id = insertion_orders.front().front();
        }
    } else {
        std::vector<ConstraintProto::LeadingObjectProto> leading_trajs;
        leading_trajs =
            FindLeadingObjects(st_traj_mgr, cur_leading_trajs,
                               st_planner_object_traj, drive_passage);

        if (!leading_trajs.empty()) {
            current_path_leader_id =
                leading_trajs.front().gap_proto().leader_id();
        }
        leading_groups.push_back({});
        insertion_orders.push_back({});
        auto &traj_group = leading_groups.back();
        auto &group_order = insertion_orders.back();
        std::set<std::string> object_ids;
        for (auto &leading_traj : leading_trajs) {
            const std::string obj_id = leading_traj.gap_proto().leader_id();
            if (!object_ids.count(obj_id)) {
                object_ids.insert(obj_id);
                group_order.push_back(leading_traj.traj_id());
                traj_group.emplace(leading_traj.traj_id(),
                                   std::move(leading_traj));
            }
        }
    }

    std::unique_ptr<CollisionChecker> collision_checker =
        std::make_unique<BoxGroupCollisionChecker>(
            &st_planner_object_traj, &vehicle_geom,
            MotionForm::kConstTimeIntervalSampleStep,
            kStationaryObjectCollisionBuffer, kMovingObjectCollisionBuffer,
            path_start_point, must_borrow);

    InitializerStateProto new_state;
    XYGeometryGraph geom_graph;
    auto graph_cache = std::make_unique<GeometryGraphCache>();
    std::unique_ptr<ConstraintProto::LeadingObjectProto> blocking_static_traj =
        nullptr;
    LeftRightXYBoundPoints left_right_xy_bound_pts;
    switch (initializer_params.search_algorithm()) {
#if !TAP_PLANNING_EMERGENCY_ONLY
        case InitializerConfig::DP: {
            InitializerSamplePatternConfig prev_config =
                initializer_state.has_sample_pattern_config()
                    ? initializer_state.sample_pattern_config()
                    : InitializerSamplePatternConfig::ISC_NONE;
            auto sampling_strategy_pair =
                GetSamplingStrategy(initializer_params, is_lane_change,
                                    path_start_point.v(), prev_config);
            const auto &sample_pattern = sampling_strategy_pair.first;
            const auto &sample_strategy = sampling_strategy_pair.second;
            new_state.set_sample_pattern_config(sample_pattern);
            new_state.set_s_from_start(s_from_start);
            *new_state.mutable_prev_start_point() = path_start_point;
            const CurvyGeometryGraphBuilderInput geom_graph_builder_input = {
                .passage = &drive_passage,
                .sl_boundary = &path_sl_boundary,
                .stop_s_vec = &stop_s_vec,
                .leading_groups = &leading_groups,
                .st_traj_mgr = &st_traj_mgr,
                .plan_start_point = &path_start_point,
                .s_from_start = s_from_start,
                .vehicle_geom = &vehicle_geom,
                .collision_checker = collision_checker.get(),
                .sampling_params = &sample_strategy,
                .vehicle_drive = &vehicle_drive,
                .form_builder = form_builder.get(),
                .lc_multiple_traj = enable_lc_multi_traj};
            ASSIGN_OR_RETURN(
                geom_graph,
                BuildCurvyGeometryGraph(geom_graph_builder_input, false,
                                        graph_cache.get(), thread_pool,
                                        debug_proto),
                [&]() {
                    return MakeAebInitializerOutput(
                        std::move(mutable_start_point), std::move(new_state),
                        std::string(_.JoinMessageToStatus().message()),
                        debug_proto, leading_groups, blocking_static_traj,
                        &motion_constraint_params);
                }());

            const auto &geom_end_info = geom_graph.GetGeometryGraphEndInfo();
            if (geom_end_info.end_reason() ==
                    GeometryGraphProto::END_STATIC_OBJ &&
                geom_end_info.end_accumulated_s() - ego_sl.s <
                    kReduceStaticBufferThresholdS) {
                // VLOG(2) << "Failed to construct graph, try a smaller "
                //            "stationary object "
                //            "buffer.";
                collision_checker->UpdateStationaryObjectBuffer(
                    0.5 * kStationaryObjectCollisionBuffer);
                ASSIGN_OR_RETURN(
                    geom_graph,
                    BuildCurvyGeometryGraph(geom_graph_builder_input, true,
                                            graph_cache.get(), thread_pool,
                                            debug_proto),
                    [&]() {
                        return MakeAebInitializerOutput(
                            std::move(mutable_start_point),
                            std::move(new_state),
                            std::string(_.JoinMessageToStatus().message()),
                            debug_proto, leading_groups, blocking_static_traj,
                            &motion_constraint_params);
                    }());
            }

            if (geom_end_info.end_reason() ==
                    GeometryGraphProto::END_STATIC_OBJ &&
                !stalled_objects.contains(geom_end_info.object_id())) {
                const auto blocking_frenet_box_or =
                    drive_passage.QueryFrenetBoxAt(
                        st_traj_mgr
                            .FindObjectByObjectId(geom_end_info.object_id())
                            ->bounding_box());
                if (blocking_frenet_box_or.ok() &&
                    blocking_frenet_box_or->s_min > av_frenet_box.s_max) {
                    const auto trajs = st_traj_mgr.FindTrajectoriesByObjectId(
                        geom_end_info.object_id());

                    if (!trajs.empty() && trajs[0] != nullptr) {
                        blocking_static_traj = std::make_unique<
                            ConstraintProto::LeadingObjectProto>(
                            CreateLeadingObject(
                                *trajs[0], drive_passage,
                                ConstraintProto::LeadingObjectProto::
                                    BLOCKING_STATIC));
                    }
                }
            }
            if (nullptr != blocking_static_traj) {
            }

            auto *graph_proto = debug_proto->mutable_geom_graph();
            graph_proto->Clear();

            if (FLAGS_planner_initializer_only_activate_nodes_near_capnet_traj) {
            } else if (
                !is_lane_change &&
                FLAGS_planner_initializer_only_activate_nodes_near_refline) {
                ReferenceLineSearcherInput ref_line_search_input{
                    .geometry_graph = &geom_graph,
                    .drive_passage = &drive_passage,
                    .sl_boundary = &path_sl_boundary,
                    .initializer_params = &initializer_params,
                    .vehicle_geom = &vehicle_geom,
                    .vehicle_drive = &vehicle_drive,
                    .st_planner_object_traj = &st_planner_object_traj,
                };
                const auto ref_line_output_or = SearchReferenceLine(
                    ref_line_search_input, debug_proto, thread_pool);

                if (ref_line_output_or.ok()) {
                    RETURN_IF_ERROR(DeactivateFarGeometries(
                        *ref_line_output_or, path_sl_boundary, &geom_graph));
                    if (FLAGS_planner_initializer_debug_level >= 1) {
                        ParseReferenceLineResultToProto(*ref_line_output_or,
                                                        graph_proto);
                    }
                }
            }

            if (FLAGS_planner_initializer_debug_level >= 1) {
                geom_graph.ToProto(graph_proto);
                form_builder->FillSmoothDrivePassage(graph_proto);
            }
        } break;
#endif
        case InitializerConfig::InteractiveAStar: {
        } break;
    }
    // VLOG(3) << "Done build geometry graph";
    const bool eval_safety =
        !FLAGS_planner_est_scheduler_seperate_lc_pause && is_lane_change &&
        (lane_change_state.stage() != LaneChangeStage::LCS_PAUSE) &&
        !(lane_change_state.force_merge() ||
          lane_change_state.entered_target_lane());

    InitializerSceneType init_scene_type =
        InitializerSceneType::INIT_SCENE_NONE;
    if (is_lane_change) {
        init_scene_type = InitializerSceneType::INIT_SCENE_LANE_CHANGE;
    } else if (is_first_lead) {
        init_scene_type = InitializerSceneType::INIT_SCENE_FOLLOW;
    } else {
        init_scene_type = initializer_input.borrow_lane
                              ? InitializerSceneType::INIT_SCENE_BORROW
                              : InitializerSceneType::INIT_SCENE_NUDGE;
    }

    const auto &xy_range = GetXYRange(path_sl_boundary);

    MotionSearchInput motion_search_input{
        .start_point = &path_start_point,
        .path_look_ahead_duration = initializer_input.path_look_ahead_duration,
        .plan_time = plan_time,
        .drive_passage = &drive_passage,
        .sl_boundary = &path_sl_boundary,
        .st_traj_mgr = &st_traj_mgr,
        .st_planner_object_traj = &st_planner_object_traj,
        .initializer_params = &initializer_params,
        .motion_constraint_params = &motion_constraint_params,
        .vehicle_params = initializer_input.vehicle_params,
        .geom_graph = &geom_graph,
        .form_builder = form_builder.get(),
        .collision_checker = collision_checker.get(),
        .stop_s_vec = &stop_s_vec,
        .leading_groups = &leading_groups,
        .blocking_static_traj = blocking_static_traj.get(),
        .obstacles_behavior_map = &obstacles_behavior_map,
        .insertion_orders = &insertion_orders,
        .lane_change_state = initializer_input.lane_change_state,
        .current_path_leader_id = &current_path_leader_id,
        .pre_object_decisions = initializer_input.pre_object_decisions,
        .nullable_nearest_vru_object_id = nullable_nearest_vru_object_id,
        .pre_obs_gap = initializer_input.pre_obs_gap,
        .av_frenet_box = initializer_input.av_frenet_box,

        .passage_speed_limit = passage_speed_limit,
        .init_scene_type = init_scene_type,
        .is_lane_change = is_lane_change,
        .is_manual_lane_change = initializer_input.is_manual_lane_change,
        .eval_safety = eval_safety,
        .lc_style = initializer_input.lane_change_style,

        .lc_state = lane_change_state.stage(),
        .prev_lc_stage = prev_lane_change_stage,
        .push_dir = initializer_input.push_dir,
        .borrow_lane = initializer_input.borrow_lane,
        .xy_range = &xy_range,
        .drive_passages = initializer_input.drive_passages};

    ASSIGN_OR_RETURN(
        auto motion_output,
        SearchMotion(motion_search_input, thread_pool, plan_id), [&]() {
            return MakeAebInitializerOutput(
                std::move(mutable_start_point), std::move(new_state),
                std::string(_.JoinMessageToStatus().message()), debug_proto,
                leading_groups, blocking_static_traj,
                &motion_constraint_params);
        }());
    if (!motion_output.result_status.ok()) {
        return absl::CancelledError(
            absl::StrCat("Motion search output invalid: ",
                         motion_output.result_status.message()));
    }

    std::string lc_lead_obj_id = "none";

    if (enable_lc_multi_traj) {
        double min_traj_cost = std::numeric_limits<double>::max();
        for (const auto &traj : motion_output.multi_traj_candidates) {
            if (traj.total_cost < min_traj_cost - 1.0) {
                min_traj_cost = traj.total_cost;
                lc_lead_obj_id = traj.leading_traj_ids.empty()
                                     ? ""
                                     : traj.leading_traj_ids.front();
            }
        }
        if ("none" != lc_lead_obj_id && "" != lc_lead_obj_id) {
            const auto found = lc_lead_obj_id.find("-idx");
            lc_lead_obj_id = (std::string::npos == found)
                                 ? ""
                                 : lc_lead_obj_id.substr(0, found);
        }
    }

    std::string best_gap_info = " ";

    DrivePassage *first_lk_drive_passage = nullptr;
    bool is_ego_corner_across_lane_bound = false;
    constexpr double kMaxHalfLaneWidth = 2.7;
    auto boundaries =
        drive_passage.QueryEnclosingLaneBoundariesAtS(av_frenet_box.center_s());
    const auto &right_boundary = boundaries.right;
    const auto &left_boundary = boundaries.left;
    const double boundary_right_l =
        right_boundary.has_value()
            ? std::max(right_boundary->lat_offset, -kMaxHalfLaneWidth)
            : -kMaxHalfLaneWidth;
    const double boundary_left_l =
        left_boundary.has_value()
            ? std::min(left_boundary->lat_offset, kMaxHalfLaneWidth)
            : kMaxHalfLaneWidth;
    is_ego_corner_across_lane_bound = (av_frenet_box.l_min < boundary_left_l) &&
                                      (av_frenet_box.l_max > boundary_right_l);

    if ((initializer_params.search_algorithm() ==
            InitializerConfig::InteractiveAStar) &&
        !motion_output.obs_gap.is_merge_safe.first &&
        (scheduler_output->lane_change_state.stage() ==
            LaneChangeStage::LCS_EXECUTING)) {
        // scheduler_output->sl_boundary.DumpToDebugFrame(plan_id, "origin");
        auto lane_change_state = scheduler_output->lane_change_state;
        lane_change_state.set_stage(LaneChangeStage::LCS_PAUSE);
        double last_used_target_lane_offset =
            initializer_input.last_used_target_lane_offset;
        bool has_found_lane_keep_passage = false;
        if (initializer_input.drive_passages != nullptr) {
            for (const auto &pair : *initializer_input.drive_passages) {
                const std::string &key = pair.first;
                const std::shared_ptr<DrivePassage> &passage_ptr = pair.second;
                std::regex lk_pattern("^lk.*");
                if (std::regex_match(key, lk_pattern) &&
                    (passage_ptr.get() != nullptr)) {
                    ASSIGN_OR_RETURN(
                        scheduler_output->sl_boundary,
                        BuildPathBoundaryFromPose(
                            drive_passage,
                            initializer_input.start_point_info->start_point,
                            *initializer_input.lane_evade_info, vehicle_geom,
                            st_traj_mgr, lane_change_state,
                            *initializer_input.smooth_result_map,
                            scheduler_output->borrow_lane,
                            scheduler_output->should_smooth,
                            &last_used_target_lane_offset,
                            initializer_input.ref_centered_compensation_offset,
                            scheduler_output->is_force_lc,
                            scheduler_output->force_lc_offset_ratio,
                            is_ego_corner_across_lane_bound, passage_ptr.get(),
                            true, false, is_uturn_scene),
                        _ << "Rebuilding path boundary failed.");

                    has_found_lane_keep_passage = true;
                    first_lk_drive_passage = passage_ptr.get();
                    break;
                }
            }
        }

        if (!has_found_lane_keep_passage) {
            ASSIGN_OR_RETURN(
                scheduler_output->sl_boundary,
                BuildPathBoundaryFromPose(
                    drive_passage,
                    initializer_input.start_point_info->start_point,
                    *initializer_input.lane_evade_info, vehicle_geom,
                    st_traj_mgr, lane_change_state,
                    *initializer_input.smooth_result_map,
                    scheduler_output->borrow_lane,
                    scheduler_output->should_smooth,
                    &last_used_target_lane_offset,
                    initializer_input.ref_centered_compensation_offset,
                    scheduler_output->is_force_lc,
                    scheduler_output->force_lc_offset_ratio, false, nullptr,
                    false, false, is_uturn_scene),
                _ << "Rebuilding path boundary failed.");
        }

        *last_lane_offset = last_used_target_lane_offset;

        boost::optional<std::string> nullable_nearest_vru_object_id =
            boost::none;
        std::vector<ConstraintProto::LeadingObjectProto> leading_trajs;
        leading_trajs =
            FindLeadingObjects(st_traj_mgr, cur_leading_trajs,
                               st_planner_object_traj, drive_passage);
        for (auto &leading_traj : leading_trajs) {
            motion_output.leading_trajs.emplace(leading_traj.traj_id(),
                                                std::move(leading_traj));
        }
    }

    if (motion_output.is_lc_pause) {
        // scheduler_output->sl_boundary.DumpToDebugFrame(plan_id, "origin");
        best_gap_info += "is lc pause.";
        bool must_borrow = false;
        *unsafe_object_ids = std::move(motion_output.unsafe_object_ids);

        scheduler_output->lane_change_state.set_stage(
            LaneChangeStage::LCS_PAUSE);
        scheduler_output->lane_change_state.set_pause_shift_l(
            initializer_input.lane_change_state->pause_shift_l());
        scheduler_output->lane_change_state.set_lc_left(
            initializer_input.lane_change_state->lc_left());

        int is_force_lc = 0;
        double force_lc_offset_ratio = 0.;
        NaviDistForCurLaneSeq force_lc_navi_dist_out;
        // TODO:(xc) Replace with CalcForceLcInput
        // CalcForceLcInput(
        //     planner_semantic_map_manager, *(initializer_input.behavior),
        //     drive_passage, initializer_input.force_lc_navi_dist,
        //     scheduler_output->lane_change_state,
        //     initializer_input.prev_lc_stage, is_force_lc,
        //     force_lc_offset_ratio, force_lc_navi_dist_out);
        double last_used_target_lane_offset =
            initializer_input.last_used_target_lane_offset;
        constexpr double kTrafficCongestionFactor = 0.6;
        constexpr double kSlowSceneSpeed = 20.0;
        const bool is_slow_and_traffic_congestion_scene =
            (initializer_input.traffic_congestion_factor >
                kTrafficCongestionFactor) &&
            (Mps2Kph(initializer_input.start_point_info->start_point.v()) <
                kSlowSceneSpeed);
        ASSIGN_OR_RETURN(
            scheduler_output->sl_boundary,
            BuildPathBoundaryFromPose(
                drive_passage, initializer_input.start_point_info->start_point,
                *initializer_input.lane_evade_info, vehicle_geom, st_traj_mgr,
                scheduler_output->lane_change_state,
                *initializer_input.smooth_result_map,
                scheduler_output->borrow_lane, scheduler_output->should_smooth,
                &last_used_target_lane_offset,
                initializer_input.ref_centered_compensation_offset,
                scheduler_output->is_force_lc,
                scheduler_output->force_lc_offset_ratio,
                is_ego_corner_across_lane_bound, first_lk_drive_passage,
                is_slow_and_traffic_congestion_scene, false, is_uturn_scene),
            _ << "Rebuilding path boundary failed.");
        *last_lane_offset = last_used_target_lane_offset;

        boost::optional<std::string> nullable_nearest_vru_object_id =
            boost::none;
        std::vector<ConstraintProto::LeadingObjectProto> leading_trajs;
        leading_trajs =
            FindLeadingObjects(st_traj_mgr, cur_leading_trajs,
                               st_planner_object_traj, drive_passage);
        for (auto &leading_traj : leading_trajs) {
            motion_output.leading_trajs.emplace(leading_traj.traj_id(),
                                                std::move(leading_traj));
        }

        DeciderInput decider_input{
            .plan_id = 99,
            .vehicle_geometry_params = &vehicle_geom,
            .motion_constraint_params = &motion_constraint_params,
            .config = &decision_constraint_config,
            .lc_state = &scheduler_output->lane_change_state,
            .plan_start_point =
                &initializer_input.start_point_info->start_point,
            // TODO:(xc)
            .lane_path_before_lc = nullptr,
            .passage = &drive_passage,
            .sl_boundary = &scheduler_output->sl_boundary,
            .borrow_lane_boundary = scheduler_output->borrow_lane,
            .st_traj_mgr = &st_traj_mgr,

            .traffic_light_status_map =
                initializer_input.traffic_light_status_map,
            .pre_decider_state = initializer_input.prev_decider_state,

            .max_reach_length = initializer_input.left_navi_dist,
            .lc_num = initializer_input.cur_lc_num,
            .leading_id = initializer_input.leading_id,

            .plan_time = initializer_input.start_point_info->plan_time,
            // .scene_reasoning = initializer_input.scene_reasoning,
            .behavior = initializer_input.behavior,
            .is_lc_pause = motion_output.is_lc_pause,
            .is_using_rule_based_gap = false};

        // TODO:(xc)
        // ASSIGN_OR_RETURN(auto lcp_decider_output,
        // BuildConstraints(decider_input),
        //                  _ << "Rebuilding decision constraints failed.");
        // *decider_output = std::move(lcp_decider_output);

        const double target_l =
            scheduler_output->sl_boundary.QueryReferenceCenterL(ego_sl.s);
        ASSIGN_OR_RETURN(auto lcp_traj,
                         GenerateConstLateralAccelConstSpeedTraj(
                             drive_passage, vehicle_geom.front_edge_to_center(),
                             target_l, motion_output.leading_trajs,
                             decider_output->constraint_manager.StopLine(),
                             path_start_point, kInitializerTrajectorySteps),
                         _ << "Generating lc pause trajectory failed.");
        motion_output.multi_traj_candidates.insert(
            motion_output.multi_traj_candidates.begin(),
            MotionSearchOutput::MultiTrajCandidate{.trajectory = lcp_traj});
        motion_output.traj_points = std::move(lcp_traj);
    } else if (is_lane_change) {
        best_gap_info += "is lc.\n";
        auto gap_or =
            EvaluateBestGapFromSearch(motion_output, initializer_params);

        auto gap_index = motion_output.first_safe_to_gap_index;

        if (gap_or.ok() && (initializer_params.search_algorithm() ==
                               InitializerConfig::InteractiveAStar)) {
            decider_output->constraint_manager.SetTrafficGap(
                std::move(gap_or).value());
            if (gap_or.value().acc_gap_target_a.has_value() &&
                gap_or.value().acc_gap_target_speed.has_value()) {
                const auto acc_gap_a = gap_or.value().acc_gap_target_a.value();
                const auto acc_gap_v =
                    gap_or.value().acc_gap_target_speed.value();
                motion_output.obs_gap.acc_gap_target_a = acc_gap_a;

                absl::StrAppend(&best_gap_info,
                                absl::StrCat("acc_gap_a: ", acc_gap_a,
                                             " acc_gap_v: ", acc_gap_v));
            }
            if (gap_or.value().dec_gap_target_a.has_value() &&
                gap_or.value().dec_gap_target_speed.has_value()) {
                const auto dec_gap_a = gap_or.value().dec_gap_target_a.value();
                const auto dec_gap_v =
                    gap_or.value().dec_gap_target_speed.value();
                motion_output.obs_gap.dec_gap_target_a = dec_gap_a;

                absl::StrAppend(&best_gap_info,
                                absl::StrCat("dec_gap_a: ", dec_gap_a,
                                             " dec_gap_v: ", dec_gap_v));
            }
        }
    } else {
        best_gap_info += "is lk.";
    }

    ParseMotionSearchOutputToInitializerResult(motion_output, debug_proto);
    ParseMotionSearchOutputToMultiTrajDebugProto(
        motion_output, debug_proto->mutable_multi_traj_debug());
    if (FLAGS_planner_initializer_debug_level >= 1) {
        if (!motion_output.is_lc_pause) {
            ParseMotionSearchOutputToMotionSearchDebugProto(
                motion_output, debug_proto->mutable_motion_search_debug());
            const auto search_proto = debug_proto->motion_search_debug();

            int motion_idx = 0;

            for (int i = 0; i < search_proto.top_k_trajs().size(); i++) {
                if ((3 < i) && (0 != i % 9) &&
                    (search_proto.top_k_trajs().size() - 1 != i)) {
                    continue;
                }
                const auto &traj_info = search_proto.top_k_trajs(i);

                std::vector<double> xss, yss;
                xss.reserve(static_cast<std::size_t>(traj_info.traj_points().size()));
                yss.reserve(static_cast<std::size_t>(traj_info.traj_points().size()));
                for (const auto &point : traj_info.traj_points()) {
                    xss.emplace_back(point.pos().x());
                    yss.emplace_back(point.pos().y());
                }
                double motion_z = i == 0 ? 2.0 : 1.5;

                motion_idx++;
            }

        } else {
            std::vector<double> xs, ys;
            xs.reserve(motion_output.traj_points.size());
            ys.reserve(motion_output.traj_points.size());
            for (const auto &point : motion_output.traj_points) {
                xs.push_back(point.path_point().x());
                ys.push_back(point.path_point().y());
            }
        }
    }

    DestroyContainerAsyncMarkSource(std::move(form_builder), "form_builder");
    DestroyContainerAsyncMarkSource(std::move(graph_cache),
                                    "geometry_graph_cache");

    if (FLAGS_planner_dumping_initializer_features) {
        ParseFeaturesDumpingProto(motion_output,
                                  debug_proto->mutable_expert_evaluation(),
                                  debug_proto->mutable_candidates_evaluation());
    }

    auto &leading_trajs = motion_output.leading_trajs;

    if (blocking_static_traj != nullptr &&
        leading_trajs.find(blocking_static_traj->traj_id()) ==
            leading_trajs.end()) {
        const auto obj_id =
            SpacetimeObjectTrajectory::GetObjectIdFromTrajectoryId(
                blocking_static_traj->traj_id());
        if (!stalled_objects.contains(obj_id)) {
            (*obj_leading)[obj_id] = true;
            leading_trajs.emplace(blocking_static_traj->traj_id(),
                                  *blocking_static_traj);
        }
    }
    for (auto it = leading_trajs.begin(); it != leading_trajs.end(); ++it) {
        *debug_proto->add_leading_objects() = it->second;
    }

    boost::optional<bool> is_modify_speed = boost::none;
    if (initializer_params.search_algorithm() ==
        InitializerConfig::InteractiveAStar) {
        is_modify_speed =
            lane_change_state.stage() == LaneChangeStage::LCS_EXECUTING
                ? (motion_output.obs_gap.is_merge_safe.first ? false : true)
                : false;
    }

    if (motion_output.leading_trajs.empty()) {
        for (const auto &it : leading_groups.back()) {
            motion_output.leading_trajs.emplace(it);
        }
    }

    return InitializerOutput{
        .follower_set = std::move(motion_output.follower_set),
        .leader_set = std::move(motion_output.leader_set),
        .follower_max_decel = motion_output.follower_max_decel,
        .is_lc_pause = motion_output.is_lc_pause,
        .traj_points = std::move(motion_output.traj_points),
        .initializer_state = std::move(new_state),
        .leading_trajs = std::move(leading_trajs),
        .nudge_info = std::move(motion_output.nudge_info),
        .object_decisions = std::move(motion_output.object_decisions),
        .obs_gap = std::move(motion_output.obs_gap),
        .speed_response_style = std::move(motion_output.speed_response_style),
        .lc_status_code = std::move(motion_output.lc_status_code),
        .is_init_follow_scene =
            (InitializerSceneType::INIT_SCENE_FOLLOW == init_scene_type),
        .lc_lead_obj_id = lc_lead_obj_id,
        .is_aeb_result = false,
        .is_modify_speed = std::move(is_modify_speed)};
}

}  // namespace planning
}  // namespace pnc_x
