#include "tap_adapter/core/planning_runtime_adapter.h"

#include <cmath>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include <absl/container/flat_hash_set.h>
#include <absl/status/status.h>
#include <absl/strings/str_cat.h>
#include <absl/time/time.h>

#include "tap_adapter/core/planning_core_adapter.h"
#include "tap_adapter/core/planning_object_adapter.h"

#include "async/thread_pool.h"
#include "common/plan_start_point_info.h"
#include "initializer/initializer_input.h"
#include "initializer/search_motion.h"
#include "math/vec.h"
#include "optimization/ddp/trajectory_optimizer.h"
#include "optimization/ddp/trajectory_optimizer_util.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "path_planner/src/util/file_util.h"
#include "pncx_planner_params.pb.h"
#include "pncx_traffic_light.pb.h"
#include "pncx_vehicle.pb.h"
#include "plan/trajectory_point.h"
#include "scheduler/smooth_reference_line_result.h"
#include "util/hmi_content_util.h"
#include "util/vehicle_geometry_util.h"

namespace tap {
namespace planning_adapter {
namespace core {

namespace {

absl::Status LoadTextProto(const std::string &path,
                           google::protobuf::Message *message) {
    if (path.empty() || message == nullptr ||
        !pnc_x::file_util::TextFileToProto(path, message)) {
        return absl::NotFoundError(
            absl::StrCat("failed to load emergency Planning config: ", path));
    }
    return absl::OkStatus();
}

void BuildTrajectoryOptimizerVehicleModel(
    const pnc_x::VehicleGeometryParamsProto &geometry,
    pnc_x::PlannerVehicleModelParamsProto *models) {
    auto *model = models->mutable_trajectory_optimizer_vehicle_model_params();
    const double half_width = 0.5 * geometry.width();
    model->clear_circles();
    model->clear_mirror_circles();

    auto add_circle = [model](double distance, double angle, double radius,
                              const char *name) {
        auto *circle = model->add_circles();
        circle->set_dist_to_rac(distance);
        circle->set_angle_to_axis(angle);
        circle->set_radius(radius);
        circle->set_name(name);
    };
    add_circle(half_width - geometry.back_edge_to_center(), 0.0, half_width,
               "Rear axis center");
    add_circle(geometry.front_edge_to_center() - half_width, 0.0, half_width,
               "Front axis center");
    if (geometry.length() / std::max(geometry.width(), 1e-3) > 3.0) {
        add_circle(
            (2.0 / 3.0) * (geometry.front_edge_to_center() - half_width) +
                (1.0 / 3.0) * (half_width - geometry.back_edge_to_center()),
            0.0, half_width, "Middle Front axis center");
        add_circle(
            (1.0 / 3.0) * (geometry.front_edge_to_center() - half_width) +
                (2.0 / 3.0) * (half_width - geometry.back_edge_to_center()),
            0.0, half_width, "Middle Rear axis center");
    } else if (!model->use_less_circles()) {
        add_circle(0.5 * (geometry.front_edge_to_center() -
                          geometry.back_edge_to_center()),
                   0.0, half_width, "Middle axis center");
    }
    if (!model->use_less_circles()) {
        constexpr double kCornerRadius = 0.3;
        const double distance =
            std::hypot(half_width - kCornerRadius,
                       geometry.front_edge_to_center() - kCornerRadius);
        const double angle =
            std::atan2(half_width - kCornerRadius,
                       geometry.front_edge_to_center() - kCornerRadius);
        add_circle(distance, angle, kCornerRadius * 1.414, "Front left corner");
        add_circle(distance, -angle, kCornerRadius * 1.414,
                   "Front right corner");
    }
}

absl::Status ValidateConfig(const pnc_x::PlannerParamsProto &planner,
                            const pnc_x::TrajectoryOptimizerParamsProto &ddp,
                            const pnc_x::VehicleParamsProto &vehicle) {
    if (planner.initializer_params().search_algorithm() !=
        pnc_x::planning::InitializerConfig::InteractiveAStar) {
        return absl::InvalidArgumentError(
            "Emergency runtime requires Interactive A* initializer config");
    }
    const auto &geometry = vehicle.vehicle_geometry_params();
    const auto &drive = vehicle.vehicle_drive_params();
    if (geometry.width() <= 0.0 || geometry.length() <= 0.0 ||
        geometry.wheel_base() <= 0.0 || drive.steer_ratio() <= 0.0 ||
        drive.max_steer_angle() <= 0.0 ||
        ddp.trajectory_optimizer_validation_params().max_final_cost() == 0.0) {
        return absl::InvalidArgumentError(
            "Emergency runtime config has incomplete vehicle or DDP fields");
    }
    return absl::OkStatus();
}

NormalizedTrajectoryPoint ToNormalizedPoint(
    const pnc_x::planning::TrajectoryPoint &point) {
    NormalizedTrajectoryPoint result;
    result.x = point.pos().x();
    result.y = point.pos().y();
    result.s = point.s();
    result.heading = point.theta();
    result.curvature = point.kappa();
    result.relative_time = point.t();
    result.speed = point.v();
    result.acceleration = point.a();
    result.jerk = point.j();
    result.steer_angle = point.steer_angle();
    return result;
}

double TrajectoryTime(const pnc_x::ApolloTrajectoryPointProto &point) {
    return point.relative_time();
}

double TrajectoryTime(const pnc_x::planning::TrajectoryPoint &point) {
    return point.t();
}

pnc_x::Vec2d TrajectoryPosition(
    const pnc_x::ApolloTrajectoryPointProto &point) {
    return pnc_x::Vec2d(point.path_point().x(), point.path_point().y());
}

pnc_x::Vec2d TrajectoryPosition(const pnc_x::planning::TrajectoryPoint &point) {
    return point.pos();
}

double TrajectoryHeading(const pnc_x::ApolloTrajectoryPointProto &point) {
    return point.path_point().theta();
}

double TrajectoryHeading(const pnc_x::planning::TrajectoryPoint &point) {
    return point.theta();
}

// The upstream Initializer checks all objects while searching, and DDP adds
// object/static-boundary costs while optimizing.  Those checks are necessary
// but are not a hard postcondition on the final DDP trajectory: the optimizer
// may trade a soft object cost against another cost.  Keep one adapter-side
// safety gate for both the A* coarse result and the final DDP result.
//
// LongSafe's selected object is not the only collision-relevant object.  Every
// Prediction branch is checked.  The selected object additionally receives the
// product safety margin and must be present when an emergency request is
// active.  This separates the generic "do not collide with any object" rule
// from the LongSafe contract without duplicating collision logic in Node.
template <typename TrajectoryPointType>
bool IsTrajectoryCollisionFreeForObjects(
    const pnc_x::planning::SpacetimeTrajectoryManager &spacetime,
    const std::vector<TrajectoryPointType> &trajectory,
    const pnc_x::VehicleGeometryParamsProto &vehicle_geometry,
    const std::string &required_object_id,
    double required_object_safety_margin_m,
    double generic_object_safety_margin_m,
    std::string *failure) {
    bool required_object_found = required_object_id.empty();
    for (const auto &trajectory_record : spacetime.trajectories()) {
        const auto *object_trajectory = &trajectory_record;
        if (object_trajectory == nullptr ||
            object_trajectory->states().empty()) {
            if (failure != nullptr) {
                *failure = "Prediction trajectory is empty";
            }
            return false;
        }
        const bool is_required_object =
            !required_object_id.empty() &&
            object_trajectory->planner_object().id() == required_object_id;
        required_object_found = required_object_found || is_required_object;
        const double safety_margin_m =
            is_required_object ? required_object_safety_margin_m
                               : generic_object_safety_margin_m;
        const auto states = object_trajectory->states();
        if (states.front().traj_point == nullptr ||
            states.back().traj_point == nullptr) {
            if (failure != nullptr) {
                *failure = "target Prediction state has null point";
            }
            return false;
        }
        const double prediction_end_time = states.back().traj_point->t();
        for (const auto &point : trajectory) {
            // A moving Prediction branch may legitimately end before the
            // published trajectory.  Do not clamp all later ego points to
            // the branch's last state: that would turn an unknown future
            // into a false collision.  Stationary branches are expanded by
            // the upstream Prediction adapter and therefore remain covered.
            if (TrajectoryTime(point) > prediction_end_time + 1e-6) {
                continue;
            }
            // Prediction messages may use 50/100/200 ms spacing and
            // stationary trajectories are expanded by the upstream adapter.
            // Interpolate the object box at the ego point's actual time rather
            // than assuming a fixed prediction grid or snapping to a nearby
            // state, which can miss a short overlap between samples.
            size_t state_index = 0U;
            size_t next_state_index = 0U;
            for (size_t i = 1U; i < states.size(); ++i) {
                if (states[i].traj_point == nullptr) {
                    if (failure != nullptr) {
                        *failure = "target Prediction state has null point";
                    }
                    return false;
                }
                if (states[i].traj_point->t() >= TrajectoryTime(point)) {
                    state_index = i - 1U;
                    next_state_index = i;
                    break;
                }
            }
            if (next_state_index == 0U) {
                state_index = states.size() - 1U;
                next_state_index = state_index;
            }
            const auto &lower = states[state_index];
            const auto &upper = states[next_state_index];
            const double lower_t = lower.traj_point->t();
            const double upper_t = upper.traj_point->t();
            const double ratio =
                next_state_index == state_index || upper_t <= lower_t
                    ? 0.0
                    : std::max(0.0, std::min(
                                    1.0, (TrajectoryTime(point) - lower_t) /
                                             (upper_t - lower_t)));
            const auto center = lower.box.center() * (1.0 - ratio) +
                                upper.box.center() * ratio;
            const auto object_box = pnc_x::Box2d(
                center,
                lower.box.heading() * (1.0 - ratio) +
                    upper.box.heading() * ratio,
                lower.box.length() * (1.0 - ratio) +
                    upper.box.length() * ratio,
                lower.box.width() * (1.0 - ratio) +
                    upper.box.width() * ratio);
            const auto ego_box = pnc_x::planning::ComputeAvBox(
                TrajectoryPosition(point), TrajectoryHeading(point),
                vehicle_geometry);
            // LongSafe 的目标验证额外使用对称安全间距；上游 A*/DDP 的
            // 搜索和代价仍保持原始配置，避免把适配层策略混入算法实现。
            if (object_box.HasOverlapWithBuffer(
                    ego_box, safety_margin_m, safety_margin_m)) {
                if (failure != nullptr) {
                    *failure = absl::StrCat(
                        "collision with object=",
                        object_trajectory->planner_object().id(),
                        ", trajectory=", object_trajectory->traj_id(),
                        ", t=", TrajectoryTime(point));
                }
                return false;
            }
        }
    }

    if (!required_object_found) {
        if (failure != nullptr) {
            *failure = absl::StrCat(
                "required LongSafe object '", required_object_id,
                "' has no Prediction trajectory");
        }
        return false;
    }
    return true;
}

}  // namespace

class EmergencyPlanningRuntime::Impl {
 public:
    explicit Impl(EmergencyPlanningRuntimeConfig runtime_config)
        : config(std::move(runtime_config)), thread_pool(1) {}

    absl::Status Initialize() {
        const auto &dir = config.parameter_directory;
        auto status = LoadTextProto(dir + "/planner_default_params.pb.txt",
                                    &planner_params);
        if (!status.ok()) return status;
        status =
            LoadTextProto(dir + "/trajectory_optimizer_default_params.pb.txt",
                          &trajectory_optimizer_params);
        if (!status.ok()) return status;
        status = LoadTextProto(dir + "/mix_car/mix_car_vehicle_params.pb.txt",
                               &vehicle_params);
        if (!status.ok()) return status;
        planner_params.mutable_trajectory_optimizer_params()->CopyFrom(
            trajectory_optimizer_params);
        BuildTrajectoryOptimizerVehicleModel(
            vehicle_params.vehicle_geometry_params(),
            planner_params.mutable_vehicle_models_params());
        status = ValidateConfig(planner_params, trajectory_optimizer_params,
                                vehicle_params);
        if (!status.ok()) return status;
        initialized = true;
        return absl::OkStatus();
    }

    absl::StatusOr<EmergencyPlanningResult> Plan(
        const NormalizedEgoState &ego,
        const NormalizedRoadCorridor &corridor,
        const std::vector<NormalizedPredictedObject> &objects,
        const EmergencyPlanningRequest &emergency_request) {
        if (!initialized) {
            return absl::FailedPreconditionError(
                "Emergency Planning runtime is not initialized");
        }
        if (!std::isfinite(config.emergency_ttc_threshold_s) ||
            config.emergency_ttc_threshold_s < 0.0 ||
            !std::isfinite(config.emergency_safety_margin_m) ||
            config.emergency_safety_margin_m < 0.0 ||
            !std::isfinite(config.object_safety_margin_m) ||
            config.object_safety_margin_m < 0.0) {
            return absl::InvalidArgumentError(
                "invalid emergency TTC threshold or safety margin");
        }
        auto geometry = BuildPlanningGeometry(ego, corridor);
        if (!geometry.ok()) return geometry.status();
        auto spacetime = BuildSpacetimeTrajectoryManager(objects);
        if (!spacetime.ok()) return spacetime.status();

        if (emergency_request.enabled &&
            (emergency_request.target_id.empty() ||
             !std::isfinite(emergency_request.ttc_s) ||
             emergency_request.ttc_s < 0.0 ||
             emergency_request.ttc_s > config.emergency_ttc_threshold_s)) {
            return absl::InvalidArgumentError(
                "invalid or out-of-threshold emergency Planning request");
        }

        const auto ego_box = pnc_x::planning::ComputeAvBox(
            pnc_x::Vec2d(ego.x, ego.y), ego.heading,
            vehicle_params.vehicle_geometry_params());
        const auto ego_frenet_box =
            geometry->drive_passage.QueryFrenetBoxAt(ego_box);
        if (!ego_frenet_box.ok()) {
            return absl::OutOfRangeError(
                absl::StrCat("failed to project ego vehicle box: ",
                             ego_frenet_box.status().message()));
        }

        pnc_x::planning::SpacetimePlannerObjectTrajectories planner_objects;
        // Emergency Planning consumes this second, decision-oriented view of the
        // same predictions.  Keeping it empty would make both Interactive A*
        // and DDP silently ignore every obstacle even though the spacetime
        // manager had already validated and constructed their trajectories.
        // Every trajectory remains in collision checking.  The matched
        // LongSafe target only receives the upstream emergency-avoidance
        // reason; unmatched trajectories keep the Normal ALL reason.
        bool emergency_target_matched = false;
        std::size_t emergency_prediction_branch_count = 0U;
        for (const auto &trajectory : spacetime->trajectories()) {
            const bool is_emergency_target =
                emergency_request.enabled &&
                trajectory.planner_object().id() == emergency_request.target_id;
            planner_objects.AddSpacetimePlannerObjectTrajectory(
                trajectory,
                is_emergency_target
                    ? pnc_x::planning::SpacetimePlannerObjectTrajectoryReason::
                          EMERGENCY_AVOIDANCE
                    : pnc_x::planning::SpacetimePlannerObjectTrajectoryReason::
                          ALL);
            emergency_target_matched =
                emergency_target_matched || is_emergency_target;
            if (is_emergency_target) {
                ++emergency_prediction_branch_count;
            }
        }
        planner_objects.SetExtendTrajectoryMap();
        if (emergency_request.enabled && !emergency_target_matched) {
            return absl::NotFoundError(
                absl::StrCat("LongSafe target '", emergency_request.target_id,
                             "' is absent from Prediction"));
        }
        pnc_x::LaneChangeStateProto lane_change_state;
        lane_change_state.set_stage(pnc_x::LaneChangeStage::LCS_NONE);
        pnc_x::planning::StPathPlanStartPointInfo path_start_point_info;
        path_start_point_info.reset = reset;
        path_start_point_info.relative_index_from_plan_start_point = 0;
        path_start_point_info.start_point = geometry->start_point;
        path_start_point_info.plan_time =
            absl::FromUnixNanos(static_cast<int64_t>(ego.source_timestamp_ns));
        pnc_x::planning::PlanStartPointInfo start_point_info;
        start_point_info.reset = reset;
        start_point_info.start_point = geometry->start_point;
        start_point_info.plan_time = path_start_point_info.plan_time;

        pnc_x::planning::InitializerStateProto next_initializer_state;
        pnc_x::DecisionConstraintConfigProto decision_config =
            planner_params.decision_constraint_config();
        pnc_x::planning::LaneEvadeInfo lane_evade_info;
        // These are intentionally explicit empty state objects for the first
        // frame.  The upstream Initializer treats them as optional in some
        // branches, but several Normal branches dereference the references;
        // passing nullptr makes the runtime scene-dependent and unsafe.
        pnc_x::planning::NudgeObjectInfo nudge_object_info{};
        pnc_x::planning::ObjectDecisions pre_object_decisions;
        pnc_x::planning::ObsDecisionGap pre_obs_gap;
        pnc_x::planning::SmoothedReferenceLineResultMap smooth_result_map;
        std::map<std::string,
                 pnc_x::planning::ConstraintProto::LeadingObjectProto>
            leading_trajs;
        std::unordered_map<std::string,
                           std::shared_ptr<pnc_x::planning::DrivePassage>>
            drive_passages;
        drive_passages.emplace("normal",
                               std::make_shared<pnc_x::planning::DrivePassage>(
                                   geometry->drive_passage));
        absl::flat_hash_set<std::string> stalled_objects;
        absl::flat_hash_set<std::string> unsafe_object_ids;
        std::map<std::string, bool> object_leading;
        auto lane_change_status = pnc_x::planning::PlannerStatusProto::OK;
        double last_lane_offset = previous_lane_offset;

        // Emergency A* uses a three-second search profile.  Keep the DDP
        // sampling contract from the reviewed upstream configuration until a
        // dedicated short-horizon optimizer profile is validated independently.
        auto emergency_initializer_params = planner_params.initializer_params();
        emergency_initializer_params.mutable_astar_search_config()
            ->set_goal_time(3.0);
        emergency_initializer_params.mutable_astar_search_config()
            ->set_goal_time_upper_bound(3.0);
        emergency_initializer_params.mutable_interactive_astar_search_config()
            ->set_goal_time(3.0);
        emergency_initializer_params.mutable_interactive_astar_search_config()
            ->set_goal_time_upper_bound(3.0);
        pnc_x::planning::InitializerInput initializer_input;
        initializer_input.path_start_point_info = &path_start_point_info;
        initializer_input.path_look_ahead_duration = absl::Seconds(3);
        initializer_input.lane_change_state = &lane_change_state;
        initializer_input.stalled_objects = &stalled_objects;
        initializer_input.drive_passage = &geometry->drive_passage;
        initializer_input.st_traj_mgr = &*spacetime;
        initializer_input.sl_boundary = &geometry->path_boundary;
        initializer_input.prev_initializer_state = &previous_initializer_state;
        initializer_input.decision_constraint_config = &decision_config;
        initializer_input.initializer_params = &emergency_initializer_params;
        initializer_input.motion_constraint_params =
            &planner_params.motion_constraint_params();
        initializer_input.vehicle_params = &vehicle_params;
        initializer_input.st_planner_object_traj = &planner_objects;
        initializer_input.leading_trajs = &leading_trajs;
        initializer_input.av_frenet_box = &*ego_frenet_box;
        initializer_input.start_point_info = &start_point_info;
        initializer_input.lane_evade_info = &lane_evade_info;
        initializer_input.smooth_result_map = &smooth_result_map;
        initializer_input.nudge_object_info = &nudge_object_info;
        initializer_input.pre_object_decisions = &pre_object_decisions;
        initializer_input.pre_obs_gap = &pre_obs_gap;
        initializer_input.drive_passages = &drive_passages;
        pnc_x::planning::SchedulerOutput scheduler_output;
        pnc_x::planning::DeciderOutput decider_output;
        pnc_x::planning::InitializerDebugProto initializer_debug;
        const auto initializer = pnc_x::planning::RunInitializer(
            initializer_input, &unsafe_object_ids, &scheduler_output,
            &decider_output, &initializer_debug, &thread_pool, &object_leading,
            &lane_change_status, &last_lane_offset);
        if (!initializer.ok()) return initializer.status();
        if (initializer->traj_points.empty()) {
            return absl::NotFoundError("Interactive A* returned no trajectory");
        }

        std::string coarse_failure;
        if (!IsTrajectoryCollisionFreeForObjects(
                *spacetime, initializer->traj_points,
                vehicle_params.vehicle_geometry_params(),
                emergency_request.enabled ? emergency_request.target_id
                                           : std::string{},
                emergency_request.enabled ? config.emergency_safety_margin_m
                                           : config.object_safety_margin_m,
                config.object_safety_margin_m,
                &coarse_failure)) {
            return absl::FailedPreconditionError(
                absl::StrCat("Interactive A* trajectory collision check failed: ",
                             coarse_failure));
        }

        pnc_x::PlannerFunctionsParamsProto planner_functions_params =
            planner_params.planner_functions_params();
        pnc_x::PlannerVehicleModelParamsProto vehicle_models_params =
            planner_params.vehicle_models_params();
        ads_x::planning::EntryFuncSmoothInfo entry_func_smooth_info;
        pnc_x::planning::TrajectoryOptimizerInput optimizer_input;
        optimizer_input.trajectory = initializer->traj_points;
        optimizer_input.st_traj_mgr = &*spacetime;
        optimizer_input.st_planner_object_traj = &planner_objects;
        optimizer_input.drive_passage = &geometry->drive_passage;
        optimizer_input.path_sl_boundary = &geometry->path_boundary;
        optimizer_input.constraint_mgr = &decider_output.constraint_manager;
        optimizer_input.leading_trajs = &initializer->leading_trajs;
        optimizer_input.lane_evade_info = &lane_evade_info;
        optimizer_input.object_decisions = pre_object_decisions;
        optimizer_input.obs_gap = pre_obs_gap;
        optimizer_input.plan_start_point = geometry->start_point;
        optimizer_input.plan_start_time = path_start_point_info.plan_time;
        optimizer_input.plan_id = plan_id;
        optimizer_input.lc_stage = pnc_x::LaneChangeStage::LCS_NONE;
        optimizer_input.lane_change_state = lane_change_state;
        optimizer_input.trajectory_optimizer_params =
            &trajectory_optimizer_params;
        optimizer_input.motion_constraint_params =
            &planner_params.motion_constraint_params();
        optimizer_input.planner_functions_params = &planner_functions_params;
        optimizer_input.vehicle_models_params = &vehicle_models_params;
        optimizer_input.veh_geo_params =
            &vehicle_params.vehicle_geometry_params();
        optimizer_input.veh_drive_params =
            &vehicle_params.vehicle_drive_params();
        optimizer_input.nudge_object_info = &nudge_object_info;
        optimizer_input.entry_func_smooth_info = &entry_func_smooth_info;
        optimizer_input.ego_frenet_box = &*ego_frenet_box;
        optimizer_input.dynamic_time_headway = 1.0;
        optimizer_input.is_motion_aeb_result = emergency_request.enabled;
        if (!emergency_request.enabled && previous_optimizer_state.has_value()) {
            optimizer_input.trajectory_optimizer_state =
                previous_optimizer_state;
            optimizer_input.previous_trajectory = previous_trajectory;
        }
        pnc_x::planning::TrajectoryOptimizerDebugProto optimizer_debug;
        const auto optimized = pnc_x::planning::OptimizeTrajectory(
            optimizer_input, &optimizer_debug, false, &thread_pool);
        if (!optimized.ok()) return optimized.status();
        const auto valid = pnc_x::planning::optimizer::ValidateTrajectory(
            optimized->trajectory,
            trajectory_optimizer_params
                .trajectory_optimizer_validation_params(),
            optimizer_debug,
            vehicle_params.vehicle_geometry_params().wheel_base(),
            vehicle_params.vehicle_drive_params().steer_ratio());
        if (!valid.ok()) return valid;

        if (!IsTrajectoryCollisionFreeForObjects(
                *spacetime, optimized->trajectory,
                vehicle_params.vehicle_geometry_params(),
                emergency_request.enabled ? emergency_request.target_id
                                           : std::string{},
                emergency_request.enabled ? config.emergency_safety_margin_m
                                           : config.object_safety_margin_m,
                config.object_safety_margin_m,
                &coarse_failure)) {
            return absl::FailedPreconditionError(absl::StrCat(
                "DDP trajectory collision check failed: ",
                coarse_failure));
        }

        EmergencyPlanningResult result;
        result.source_timestamp_ns = ego.source_timestamp_ns;
        if (emergency_target_matched) {
            result.emergency_target_id = emergency_request.target_id;
            result.emergency_target_ttc_s = emergency_request.ttc_s;
            result.emergency_prediction_branch_count =
                emergency_prediction_branch_count;
        }
        result.initializer_trajectory.reserve(initializer->traj_points.size());
        for (const auto &point : initializer->traj_points) {
            result.initializer_trajectory.push_back(
                ToNormalizedPoint(pnc_x::planning::TrajectoryPoint(point)));
        }
        result.trajectory.reserve(optimized->trajectory.size());
        for (const auto &point : optimized->trajectory) {
            result.trajectory.push_back(ToNormalizedPoint(point));
        }
        if (result.trajectory.empty()) {
            return absl::NotFoundError("DDP returned no trajectory");
        }
        previous_initializer_state = initializer->initializer_state;
        previous_optimizer_state = optimized->trajectory_optimizer_state;
        previous_trajectory = optimized->trajectory_proto;
        previous_lane_offset = last_lane_offset;
        reset = false;
        ++plan_id;
        return result;
    }

    EmergencyPlanningRuntimeConfig config;
    pnc_x::PlannerParamsProto planner_params;
    pnc_x::TrajectoryOptimizerParamsProto trajectory_optimizer_params;
    pnc_x::VehicleParamsProto vehicle_params;
    pnc_x::ThreadPool thread_pool;
    boost::optional<pnc_x::planning::TrajectoryOptimizerState>
        previous_optimizer_state;
    std::vector<pnc_x::ApolloTrajectoryPointProto> previous_trajectory;
    pnc_x::planning::InitializerStateProto previous_initializer_state;
    int plan_id = 0;
    double previous_lane_offset = 0.0;
    bool initialized = false;
    bool reset = true;
};

EmergencyPlanningRuntime::EmergencyPlanningRuntime(
    EmergencyPlanningRuntimeConfig config)
    : impl_(std::make_unique<Impl>(std::move(config))) {}

EmergencyPlanningRuntime::~EmergencyPlanningRuntime() = default;
EmergencyPlanningRuntime::EmergencyPlanningRuntime(
    EmergencyPlanningRuntime &&) noexcept = default;
EmergencyPlanningRuntime &EmergencyPlanningRuntime::operator=(
    EmergencyPlanningRuntime &&) noexcept = default;

absl::Status EmergencyPlanningRuntime::Initialize() { return impl_->Initialize(); }

absl::StatusOr<EmergencyPlanningResult> EmergencyPlanningRuntime::Plan(
    const NormalizedEgoState &ego,
    const NormalizedRoadCorridor &corridor,
    const std::vector<NormalizedPredictedObject> &objects,
    const EmergencyPlanningRequest &emergency_request) {
    return impl_->Plan(ego, corridor, objects, emergency_request);
}

absl::StatusOr<EmergencyPlanningResult> EmergencyPlanningRuntime::Plan(
    const NormalizedEgoState &ego,
    const NormalizedRoadCorridor &corridor,
    const std::vector<NormalizedPredictedObject> &objects,
    const std::string &emergency_target_id) {
    EmergencyPlanningRequest request;
    request.enabled = !emergency_target_id.empty();
    request.target_id = emergency_target_id;
    request.ttc_s = 0.0;
    request.trigger_reason = request.enabled ? "legacy_target_id" : "";
    return impl_->Plan(ego, corridor, objects, request);
}

absl::Status ValidatePlanningCoreInputs(
    const NormalizedEgoState &ego,
    const NormalizedRoadCorridor &corridor,
    const std::vector<NormalizedPredictedObject> &objects) {
    const auto geometry = BuildPlanningGeometry(ego, corridor);
    if (!geometry.ok()) {
        return geometry.status();
    }
    const auto spacetime = BuildSpacetimeTrajectoryManager(objects);
    if (!spacetime.ok()) {
        return spacetime.status();
    }
    return absl::OkStatus();
}

}  // namespace core
}  // namespace planning_adapter
}  // namespace tap
