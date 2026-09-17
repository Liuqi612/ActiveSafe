#pragma once

#include <algorithm>
#include <array>
#include <boost/optional.hpp>
#include <cmath>
#include <limits>
#include <map>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/type_def.h"
#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>
#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <absl/strings/string_view.h>
#include <absl/types/optional.h>

#include "math/vec2d.h"
#include "object/spacetime_object_trajectory.h"
#include "pncx_vehicle.pb.h"

using SLBoundary = ads_x::planning::SLBoundary;
using SLPoint = ads_x::planning::SLPoint;
using PredictedTrajectoryPoint = pnc_x::prediction::PredictedTrajectoryPoint;

namespace pnc_x {
namespace planning {

struct Point2D {
    double x = 0.0;
    double y = 0.0;
    Point2D() = default;
    Point2D(double x, double y) : x(x), y(y) {}
};

struct PointSL {
    double s = 0.0;
    double l = 0.0;
    PointSL() = default;
    PointSL(double s, double l) : s(s), l(l) {}
};

typedef std::vector<std::vector<Point2D>> LeftRightXYBoundPoints;
typedef std::vector<std::vector<PointSL>> LeftRightSLBoundPoints;

enum class GridStatus : uint8_t {
    kUnknown = 0,
    kFree,
    kOccupied,
};

enum class SearchResult : uint8_t {
    kSearchSuccess = 0,
    kSearchFailed,
};

enum class FallBackTrajType : uint8_t {
    kUnknown = 0,
    kBreakTraj,
    kUniformVelTraj,
    kFollowTraj,
};

enum class SpatioTemporalModality : uint8_t {
    kLaneKeep = 0,
    kLeftLaneChange,
    kRightLaneChange,
};

struct GridMapInformation {
    double x_translation = 0.0;
    double y_translation = 0.0;
    double rotation_angle = 0.0;
    double x_length = 0.0;
    double y_length = 0.0;
    double x_resolution = 0.0;
    double y_resolution = 0.0;
};

template <typename T>
struct GridMapInfo {
    int row_size;
    int column_size;
    double resolution;
    pnc_x::Vec2d translation_vec_ego2refline;
    std::pair<pnc_x::Vec2d, pnc_x::Vec2d> roatation_matrix_ego2refline;
    std::vector<std::vector<T>> grid;

    absl::string_view DebugString() const {
        return absl::StrCat("map_row: ", row_size, "; map_col: ", column_size,
                            "; resolution: ", resolution);
    }
};

enum class ObstacleRelativePosition : uint8_t {
    kFront = 0,
    kBack,
    kLeftSide,
    kLeftFront,
    kLeftBack,
    kRightSide,
    kRightFront,
    kRightBack,
};

enum class NudgeDirection : uint8_t {
    kNoNudge = 0,
    kNudgeLeft,
    kNudgeRight,
    kBorrowLeft,
    kBorrowRight,
};

enum class OvertakeYieldType : uint8_t {
    kIgnore = 0,
    kOvertake,
    kYield,
};

enum class ObstacleMovingType : uint8_t {
    kDynamic = 0,
    kDead,
    kQueued,
    kStationary,
};

struct ObstacleDecisionTag {
    NudgeDirection lat_decision_tag = NudgeDirection::kNoNudge;
    OvertakeYieldType lon_decision_tag = OvertakeYieldType::kIgnore;
    int counter = 0;

    ObstacleDecisionTag() = default;
    ObstacleDecisionTag(NudgeDirection lat_tag, OvertakeYieldType lon_tag)
        : lat_decision_tag(lat_tag), lon_decision_tag(lon_tag) {}

    bool operator==(const ObstacleDecisionTag &other) const {
        return lat_decision_tag == other.lat_decision_tag &&
               lon_decision_tag == other.lon_decision_tag;
    }
};

struct ObstaclePointInfo {
    SLBoundary sl_boundary;
    SLPoint center_sl;
    Box2d box_2d;
    PredictedTrajectoryPoint traj_point;
    ObstaclePointInfo() = default;
    ObstaclePointInfo(SLBoundary sl_boundary,
                      SLPoint center_sl,
                      Box2d box_2d,
                      PredictedTrajectoryPoint traj_point)
        : sl_boundary(sl_boundary),
          center_sl(center_sl),
          box_2d(std::move(box_2d)),
          traj_point(std::move(traj_point)) {}
};

struct ObstacleDecision {
    std::string obj_id;
    ObstacleDecisionTag decision_tag;
    ObstacleMovingType obs_moving_type;
    ObjectType object_type;

    bool has_modified_pred = false;
    std::vector<ObstaclePointInfo> modified_pred_traj;
    std::vector<ObstaclePointInfo> src_tail_pred_traj;

    ObstacleDecision() = default;
    ObstacleDecision(std::string obj_id, ObstacleDecisionTag decision_tag)
        : obj_id(std::move(obj_id)), decision_tag(std::move(decision_tag)) {}
    ObstacleDecision(std::string obj_id,
                     double distance_to_ego,
                     ObstacleDecisionTag decision_tag,
                     ObstacleMovingType obs_moving_type)
        : obj_id(std::move(obj_id)),
          decision_tag(std::move(decision_tag)),
          obs_moving_type(std::move(obs_moving_type)) {}

    bool operator==(const ObstacleDecision &od) const {
        return obj_id == od.obj_id && decision_tag == od.decision_tag;
    }
};

struct ObsDecisionGap {
    int selected_index = -1;
    std::pair<bool, int> is_merge_safe = {false, 0};
    std::pair<bool, int> is_merge_not_safe = {false, 0};
    boost::optional<std::string> lead_obj_id = boost::none;
    boost::optional<std::string> tail_obj_id = boost::none;
    boost::optional<std::string> ori_lead_obj_id = boost::none;
    boost::optional<double> acc_gap_target_a = boost::none;
    boost::optional<double> dec_gap_target_a = boost::none;
    int counter = 0;

    bool operator==(const ObsDecisionGap &other) const {
        return lead_obj_id == other.lead_obj_id &&
               tail_obj_id == other.tail_obj_id;
    }
    bool operator!=(const ObsDecisionGap &other) const {
        return lead_obj_id != other.lead_obj_id ||
               tail_obj_id != other.tail_obj_id;
    }
};

struct ObstacleDecisionGroup {
    double traj_time_step = 0.0;
    std::unordered_map<std::string, ObstacleDecision> obstacles_decision;
    SpatioTemporalModality cruise_borrow_task;

    ObsDecisionGap obs_goal_gap;
    boost::optional<std::string> ori_lead_obj_id = boost::none;
};

struct RefVelocityInGap {
    double v_to_lead = -1.0;
    double v_to_tail = -1.0;
    double v_to_tail_origin = -1.0;
    double ori_dist = 0.0;
};

}  // namespace planning
}  // namespace pnc_x
