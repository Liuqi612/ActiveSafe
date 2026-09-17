
#pragma once

#include <limits>
#include <string>
#include <vector>

#include "common/path_sl_boundary.h"

#include "pncx_behavior.pb.h"
#include "common/type_def.h"
#include "initializer/initializer_output.h"
#include "pncx_lane_change.pb.h"
#include "maps/map_def.h"
#include "object/object_history.h"
#include "object/spacetime_trajectory_manager.h"
#include "pncx_perception.pb.h"
#include "pncx_planner_params.pb.h"
#include "router/drive_passage.h"
#include "pncx_scene_understanding.pb.h"
#include "scheduler/scheduler_output.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {
using PushDirection = ads_x::planning::PushDirection;
using BehaviorCommand = ads_x::planning::BehaviorCommand;
struct DeciderInput {
    int plan_id = 0;
    const pnc_x::VehicleGeometryParamsProto *vehicle_geometry_params = nullptr;
    const MotionConstraintParamsProto *motion_constraint_params = nullptr;
    const DecisionConstraintConfigProto *config = nullptr;
    const LaneChangeStateProto *lc_state;
    const ApolloTrajectoryPointProto *plan_start_point = nullptr;
    double target_offset_from_start = 0.0;
    const mapping::LanePath *lane_path_before_lc = nullptr;
    const DrivePassage *passage = nullptr;
    const PathSlBoundary *sl_boundary = nullptr;
    bool borrow_lane_boundary = false;
    const ObjectHistoryManager *obs_history = nullptr;
    const SpacetimeTrajectoryManager *st_traj_mgr = nullptr;

    const ads_x::planning::TrafficLightStatusMap *traffic_light_status_map =
        nullptr;
    const DeciderStateProto *pre_decider_state = nullptr;

    bool enable_tl_ok_btn = false;
    bool override_passable = false;

    double max_reach_length = std::numeric_limits<double>::max();

    int lc_num = 0;
    double dist_to_merge = std::numeric_limits<double>::max();
    std::string leading_id = "";
    absl::Time plan_time;

    const Behavior *behavior = nullptr;
    double cur_dist_to_junction = std::numeric_limits<double>::max();
    std::vector<std::string> lc_lead_obj_ids;
    PushDirection push_dir = PushDirection::Push_None;
    BehaviorCommand navi_lc_command = BehaviorCommand::Command_Invalid;
    bool is_lc_pause = false;
    bool is_using_rule_based_gap = false;
};

}  // namespace planning
}  // namespace pnc_x
