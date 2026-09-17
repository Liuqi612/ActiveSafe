
#pragma once

#include <string>
#include <vector>

#include "common/path_sl_boundary.h"
#include "pncx_hmi_content.pb.h"
#include "maps/lane_path.h"
#include "pncx_perception.pb.h"
#include "router/drive_passage.h"
#include "pncx_selector_state.pb.h"
#include "pncx_trajectory_point.pb.h"

namespace pnc_x {
namespace planning {

struct NudgeObjectInfo {
    enum Type {
        NORMAL = 0,
        LARGE_VEHICLE = 1,
    };
    enum NudgeState {
        NUDGE = 0,
        BORROW = 1,
    };

    enum BorrowLaneStatus {
        kDefault = 0,
        kBorrowSolidLane = 1,
        kBorrowDashedLane = 2,
    };

    std::string id;
    bool is_stationary;
    int direction;
    double arc_dist_to_object;
    double l_nudge_max;
    ObjectType type;
    NudgeState nudge_state;
    BorrowLaneStatus borrow_lane_status;
};

struct HmiContentInput {
    const mapping::LanePath *lane_path = nullptr;
    const DrivePassage *drive_passage = nullptr;
    const std::vector<ApolloTrajectoryPointProto> *traj_points = nullptr;
    const std::string *alerted_front_vehicle = nullptr;
    LaneChangeReason lane_change_reason;
    bool borrow_lane = false;
    bool request_help_lane_change_by_route = false;
    const double *distance_to_traffic_light_stop_line = nullptr;
    const double *distance_to_roadblock = nullptr;
    const std::vector<std::string> *unsafe_object_ids = nullptr;
    const mapping::LanePath *plc_target_lane_path = nullptr;
    const NudgeObjectInfo *nudge_object_info = nullptr;
};

HmiContentProto ReportHmiContent(const HmiContentInput &input);

HmiPathBoundaryProto ReportBoundaryPointsToHmiContent(
    const std::vector<Vec2d> &points,
    bool is_left,
    HmiPathBoundaryProto::BoundaryRenderStyle style);

HmiPathBoundaryProto ReportPathBoundaryToHmiContent(
    const PathSlBoundary *sl_boundary,
    HmiPathBoundaryProto::BoundaryRenderStyle left_style =
        HmiPathBoundaryProto::STYLE_NORMAL,
    HmiPathBoundaryProto::BoundaryRenderStyle right_style =
        HmiPathBoundaryProto::STYLE_NORMAL);
}  // namespace planning
}  // namespace pnc_x
