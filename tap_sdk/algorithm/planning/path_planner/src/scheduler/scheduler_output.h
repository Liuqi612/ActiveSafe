
#pragma once

#include <limits>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "common/path_sl_boundary.h"
#include "common/type_def.h"
#include "pncx_lane_change.pb.h"
#include "math/frenet_frame.h"
#include "object/spacetime_trajectory_manager.h"
#include "router/drive_passage.h"
#include "pncx_turn_signal.pb.h"
#include <absl/hash/hash.h>

namespace pnc_x {
namespace planning {
struct NaviDistForCurLaneSeq {
    double dist_to_enter_mainboard = std::numeric_limits<double>::infinity();
    double dist_to_exit_mainboard = std::numeric_limits<double>::infinity();
    double dist_to_merge = std::numeric_limits<double>::infinity();
    double dist_to_split = std::numeric_limits<double>::infinity();
};

struct SchedulerOutput {
    bool is_fallback = false;
    bool is_expert = false;
    DrivePassage drive_passage;

    PathSlBoundary sl_boundary;

    double target_offset_from_start = 0.0;
    LaneChangeStateProto lane_change_state;
    ads_x::planning::LcReason lc_reason = ads_x::planning::LC_REASON_NONE;

    double length_along_route = std::numeric_limits<double>::max();
    double max_reach_length = std::numeric_limits<double>::max();
    int lc_num = 0;
    std::string leading_id = "";
    double standard_congestion_factor = 0.0;
    double traffic_congestion_factor = 0.0;
    bool should_smooth = false;
    bool borrow_lane = false;
    FrenetBox av_frenet_box_on_drive_passage;

    bool request_help_lane_change_by_route = false;
    bool switch_alternate_route = false;
    TurnSignal planner_turn_signal = TURN_SIGNAL_NONE;
    TurnSignalReason turn_signal_reason = TURN_SIGNAL_OFF;
    bool miss_navi_scenario = false;
    double last_used_target_lane_offset = 0.0;
    bool is_target_switched = false;
    bool is_end_2_end = false;
    int is_force_lc = false;
    double force_lc_offset_ratio = 0.0;
    NaviDistForCurLaneSeq force_lc_navi_dist_out;
};

}  // namespace planning
}  // namespace pnc_x
