
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "common/path_sl_boundary.h"
#include "common/plan_start_point_info.h"
#include "decision/leading_groups_builder.h"
#include "decision/obstacle_intention_estimation.h"

#include "pncx_initializer.pb.h"
#include "initializer/collision_checker.h"
#include "initializer/geometry/geometry_form_builder.h"
#include "initializer/geometry/geometry_graph.h"

#include "pncx_driving_style.pb.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "pncx_planner.pb.h"
#include "pncx_planner_params.pb.h"
#include "router/drive_passage.h"
#include "scheduler/lane_evasion_status.h"
#include "scheduler/scheduler_output.h"
#include "scheduler/smooth_reference_line_result.h"

#include "pncx_behavior.pb.h"
#include "initializer/interactive_search/common/common.h"
#include "initializer/interactive_search/decision_extractor/object_decision.h"
#include "object/object_history.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {
using PushDirection = ads_x::planning::PushDirection;

enum class InitializerSceneType {
    INIT_SCENE_NONE = 0,
    INIT_SCENE_FOLLOW = 1,
    INIT_SCENE_NUDGE = 2,
    INIT_SCENE_BORROW = 3,
    INIT_SCENE_LANE_CHANGE = 4
};

struct MotionSearchInput {
    const ApolloTrajectoryPointProto *start_point = nullptr;
    absl::Duration path_look_ahead_duration = absl::ZeroDuration();
    absl::Time plan_time;
    const DrivePassage *drive_passage = nullptr;
    const PathSlBoundary *sl_boundary = nullptr;
    const SpacetimeTrajectoryManager *st_traj_mgr = nullptr;
    const SpacetimePlannerObjectTrajectories *st_planner_object_traj = nullptr;
    const InitializerConfig *initializer_params = nullptr;
    const MotionConstraintParamsProto *motion_constraint_params = nullptr;
    const VehicleParamsProto *vehicle_params = nullptr;
    const GeometryGraph *geom_graph = nullptr;
    const GeometryFormBuilder *form_builder = nullptr;
    const CollisionChecker *collision_checker = nullptr;
    const std::vector<double> *stop_s_vec = nullptr;
    const std::vector<LeadingGroup> *leading_groups = nullptr;
    const ConstraintProto::LeadingObjectProto *blocking_static_traj = nullptr;
    const std::unordered_map<std::string, ObstacleBehavior>
        *obstacles_behavior_map = nullptr;
    const std::vector<std::vector<std::string>> *insertion_orders = nullptr;
    const LaneChangeStateProto *lane_change_state = nullptr;
    const std::string *current_path_leader_id = nullptr;
    const ObjectDecisions *pre_object_decisions = nullptr;
    boost::optional<std::string> nullable_nearest_vru_object_id = boost::none;
    const ObsDecisionGap *pre_obs_gap = nullptr;
    const FrenetBox *av_frenet_box = nullptr;

    double passage_speed_limit = 10.0;
    const InitializerSceneType init_scene_type;
    bool is_lane_change = false;
    bool is_manual_lane_change = false;
    bool eval_safety = false;
    LaneChangeStyle lc_style = LC_STYLE_NORMAL;

    LaneChangeStage lc_state = LCS_PAUSE;
    LaneChangeStage prev_lc_stage = LCS_NONE;
    PushDirection push_dir = PushDirection::Push_None;
    bool borrow_lane = false;
    const std::vector<double> *xy_range;
    const std::unordered_map<std::string, std::shared_ptr<DrivePassage>>
        *drive_passages;
};

struct InitializerInput {
    const StPathPlanStartPointInfo *path_start_point_info = nullptr;
    absl::Duration path_look_ahead_duration = absl::ZeroDuration();
    const LaneChangeStateProto *lane_change_state = nullptr;
    LaneChangeStage prev_lc_stage = LaneChangeStage::LCS_NONE;
    LaneChangeStyle lane_change_style = LaneChangeStyle::LC_STYLE_NORMAL;
    const absl::flat_hash_set<std::string> *stalled_objects = nullptr;
    const DrivePassage *drive_passage = nullptr;
    const SpacetimeTrajectoryManager *st_traj_mgr = nullptr;
    const PathSlBoundary *sl_boundary = nullptr;
    const InitializerStateProto *prev_initializer_state = nullptr;
    const DecisionConstraintConfigProto *decision_constraint_config = nullptr;
    const InitializerConfig *initializer_params = nullptr;
    const MotionConstraintParamsProto *motion_constraint_params = nullptr;
    const VehicleParamsProto *vehicle_params = nullptr;
    const SpacetimePlannerObjectTrajectories *st_planner_object_traj = nullptr;
    int plan_id = 0;
    std::map<std::string, ConstraintProto::LeadingObjectProto>* leading_trajs;

    const SceneOutputProto *scene_reasoning = nullptr;
    bool borrow_lane = false;
    bool is_manual_lane_change = false;
    const FrenetBox *av_frenet_box = nullptr;

    const PlanStartPointInfo *start_point_info = nullptr;
    const SmoothedReferenceLineResultMap *smooth_result_map = nullptr;

    const LaneEvadeInfo *lane_evade_info = nullptr;
    const ads_x::planning::TrafficLightStatusMap *traffic_light_status_map =
        nullptr;
    const DeciderStateProto *prev_decider_state = nullptr;

    const ObjectHistoryManager *obs_history = nullptr;
    const Behavior *behavior = nullptr;
    int cur_lc_num = 0;
    std::string leading_id = "";
    double left_navi_dist = 999.0;
    PushDirection push_dir = PushDirection::Push_None;
    const NudgeObjectInfo *nudge_object_info = nullptr;
    const ObjectDecisions *pre_object_decisions = nullptr;
    const ObsDecisionGap *pre_obs_gap = nullptr;

    double last_used_target_lane_offset = 0.0;
    boost::optional<double> ref_centered_compensation_offset = boost::none;
    const std::unordered_map<std::string, std::shared_ptr<DrivePassage>>
        *drive_passages;
    NaviDistForCurLaneSeq force_lc_navi_dist;
    double traffic_congestion_factor = 0.0;
    double nearest_stop_s = 0.0;
};

struct ReferenceLineSearcherInput {
    const GeometryGraph *geometry_graph = nullptr;
    const DrivePassage *drive_passage = nullptr;
    const PathSlBoundary *sl_boundary = nullptr;
    const InitializerConfig *initializer_params = nullptr;
    const VehicleGeometryParamsProto *vehicle_geom = nullptr;
    const VehicleDriveParamsProto *vehicle_drive = nullptr;
    const SpacetimePlannerObjectTrajectories *st_planner_object_traj = nullptr;
};

}  // namespace planning
}  // namespace pnc_x
