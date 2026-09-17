#include <algorithm>
#include <cmath>
#include <limits>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "decision/decision_util.h"
#include "decision/obstacle_intention_estimation.h"
#include "math/util.h"
#include "object/planner_object.h"
#include "object/spacetime_object_state.h"
#include "object/spacetime_object_trajectory.h"
#include "plan/planner_defs.h"
#include "plan/planner_flags.h"
#include "prediction/predicted_trajectory.h"
#include "util/status_macros.h"
#include <absl/status/statusor.h>
#include <absl/strings/string_view.h>
#include <absl/types/span.h>
#include "common/log.h"

namespace pnc_x {

namespace planning {

namespace {

const char *ObstacleDirectionToString(ObstacleDirection direction) {
    switch (direction) {
        case ObstacleDirection::kOncoming:
            return "kOncoming";
        case ObstacleDirection::kSameDirection:
            return "kSameDirection";
        default:
            return "Unknown";
    }
}

const char *ObstacleIntentionToString(ObstacleIntention intention) {
    switch (intention) {
        case ObstacleIntention::kUnknown:
            return "kUnknown";
        case ObstacleIntention::kNoIntention:
            return "kNoIntention";
        case ObstacleIntention::kIgnore:
            return "kIgnore";
        case ObstacleIntention::kLeftCross:
            return "kLeftCross";
        case ObstacleIntention::kRightCross:
            return "kRightCross";
        case ObstacleIntention::kLeftCrossBack:
            return "kLeftCrossBack";
        case ObstacleIntention::kRightCrossBack:
            return "kRightCrossBack";
        case ObstacleIntention::kLeftCutin:
            return "kLeftCutin";
        case ObstacleIntention::kRightCutin:
            return "kRightCutin";
        case ObstacleIntention::kLeftLeftCutin:
            return "kLeftLeftCutin";
        case ObstacleIntention::kRightRightCutin:
            return "kRightRightCutin";
        case ObstacleIntention::kCutoutLeft:
            return "kCutoutLeft";
        case ObstacleIntention::kCutoutRight:
            return "kCutoutRight";
        case ObstacleIntention::kCutoutLeftLeft:
            return "kCutoutLeftLeft";
        case ObstacleIntention::kCutoutRightRight:
            return "kCutoutRightRight";
        default:
            return "Unknown";
    }
}

bool HasEnteredSlBoundary(const PathSlBoundary &path_boundary,
                          const FrenetBox &fbox,
                          bool lc_left) {
    constexpr double kLateralEnterThres = 0.8;
    constexpr double kLateralOutThres = 0.8;
    double boundary_left_l = 0.0;
    double boundary_right_l = 0.0;
    std::tie(boundary_left_l, boundary_right_l) =
        CalcSlBoundaries(path_boundary, fbox);
    const double l_center =
        path_boundary.QueryReferenceCenterL(fbox.center_s());

    return lc_left ? fbox.l_min < boundary_left_l - kLateralEnterThres &&
                         fbox.l_max > l_center - kLateralOutThres
                   : fbox.l_max > boundary_right_l + kLateralEnterThres &&
                         fbox.l_min < l_center + kLateralOutThres;
}

absl::StatusOr<FrenetBox> QueryXY2SLMapByBox(const DrivePassage &drive_passage,
                                             const Box2d &box) {
    constexpr double kEpsilon = 1e-6;
    FrenetBox frenet_box;
    absl::StatusOr<FrenetBox> fbox = drive_passage.QueryFrenetBoxAt(box);
    if (fbox.ok()) {
        frenet_box = std::move(fbox.value());
        return frenet_box;
    }
    if (frenet_box.s_max + kEpsilon < frenet_box.s_min) {
        return absl::NotFoundError("Box has no overlap with drive passage.");
    }
    return frenet_box;
}

bool ShouldConsiderObject(const SpacetimeObjectTrajectory &traj,
                          const PathSlBoundary &path_boundary,
                          const DrivePassage &drive_passage,
                          bool lc_left) {
    const auto &states = traj.states();

    const absl::StatusOr<FrenetBox> fbox =
        QueryXY2SLMapByBox(drive_passage, states.front().box);

    if (fbox.ok() &&
        HasEnteredSlBoundary(path_boundary, fbox.value(), lc_left)) {
        return true;
    }

    constexpr double kPreviewTime = 4.0;
    constexpr int kEvalStep = 2;
    constexpr int kEnterTRangeStep =
        static_cast<int>(kPreviewTime / kTrajectoryTimeStep);

    int projected_states = 1;
    int along_path_states = 0;
    double front_s{0.0};
    double rear_s{0.0};
    for (int i = 1; i < states.size(); i += kEvalStep) {
        if (i > kEnterTRangeStep) {
            return false;
        }

        ASSIGN_OR_CONTINUE(const auto fbox_at,
                           QueryXY2SLMapByBox(drive_passage, states[static_cast<size_t>(i)].box));
        if (HasEnteredSlBoundary(path_boundary, fbox_at, lc_left)) {
            return true;
        }
    }
    return false;
}

bool IsCutInObjectTrajectory(const DrivePassage &drive_passage,
                             const bool is_lane_change,
                             const double av_speed,
                             const FrenetBox &av_sl_box,
                             const SpacetimeObjectTrajectory &traj) {
    if (is_lane_change) return false;

    if ((traj.object_type() != ObjectType::OT_VEHICLE) &&
        (traj.object_type() != ObjectType::OT_LARGE_VEHICLE)) {
        return false;
    }

    const double object_speed = traj.pose().v();
    if ((av_speed - object_speed) < 1.5) {
        return false;
    }

    const auto frenet_start_point =
        drive_passage.QueryUnboundedFrenetCoordinateAt(
            traj.states().front().traj_point->pos());
    if (!frenet_start_point.ok()) {
        return false;
    }
    const auto lane_theta_at_pose =
        drive_passage.QueryTangentAngleAtS(frenet_start_point->s);
    if (!lane_theta_at_pose.ok()) {
        return false;
    }
    const bool object_reverse_flag =
        std::abs(NormalizeAngle((*lane_theta_at_pose) + M_PI -
                                traj.states().front().traj_point->theta())) <
        M_PI / 3;
    if (object_reverse_flag) {
        return false;
    }

    const double kObjectDistThreshold = 0.8;
    const double kBrakeAcc = 3.0;
    const double min_brake_dist = (av_speed - object_speed) *
                                  (av_speed - object_speed) / (kBrakeAcc * 2.0);
    const auto &object_box = traj.bounding_box();

    const absl::StatusOr<FrenetBox> object_frenet_box =
        QueryXY2SLMapByBox(drive_passage, object_box);
    if (!object_frenet_box.ok()) {
        return false;
    }
    if (object_frenet_box->s_min - av_sl_box.s_max <
        std::fmax(kObjectDistThreshold, min_brake_dist)) {
        return false;
    }

    const double center_range = 1.5;
    if ((object_frenet_box->l_min >
            0.6 * ads_x::planning::Constants::DEFAULT_LANE_WIDTH) ||
        (object_frenet_box->l_max <
            -0.6 * ads_x::planning::Constants::DEFAULT_LANE_WIDTH) ||
        (std::fabs(object_frenet_box->center_l()) < center_range)) {
        return false;
    }

    const double cutin_l_threshold = 1.0;
    const double delta_l_threshold = 0.2;
    double prev_l = object_frenet_box->l_min > ads_x::planning::Constants::ZERO
                        ? object_frenet_box->l_min
                        : object_frenet_box->l_max;
    for (const auto &object_state : traj.states()) {
        const absl::StatusOr<FrenetBox> pred_box =
            QueryXY2SLMapByBox(drive_passage, object_state.box);
        if (!pred_box.ok()) {
            break;
        }
        if (object_frenet_box->center_l() > ads_x::planning::Constants::ZERO) {
            if ((pred_box->l_min < cutin_l_threshold) &&
                (object_frenet_box->l_min - pred_box->l_min >
                    delta_l_threshold)) {
                return true;
            }
            prev_l = pred_box->l_min;
        } else if (object_frenet_box->center_l() <
                   -ads_x::planning::Constants::ZERO) {
            if ((pred_box->l_max > -cutin_l_threshold) &&
                (pred_box->l_max - object_frenet_box->l_max >
                    delta_l_threshold)) {
                return true;
            }
            prev_l = pred_box->l_max;
        }
    }

    return false;
}

bool IsStaticObjectType(ObjectType type) {
    return (type == OT_UNKNOWN_STATIC) || (type == OT_VEGETATION) ||
           (type == OT_FOD) || (type == OT_BARRIER) || (type == OT_CONE);
}

bool IsVru(const SpacetimeObjectTrajectory &traj) {
    return (traj.object_type() == ObjectType::OT_MOTORCYCLIST) ||
           (traj.object_type() == ObjectType::OT_CYCLIST) ||
           (traj.object_type() == ObjectType::OT_TRICYCLIST) ||
           (traj.object_type() == ObjectType::OT_PEDESTRIAN);
}

bool IsCrossingTrajectory(const DrivePassage &drive_passage,
                          const SpacetimeObjectTrajectory &traj) {
    return false;
}

ObstacleBehavior ObstacleIntentionEstimation(
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_boundary,
    const FrenetBox &object_frenet_box,
    const FrenetBox &ego_frenet_box,
    const SpacetimeObjectTrajectory &traj,
    const ApolloTrajectoryPointProto &plan_start_point,
    bool lc_left,
    bool is_lane_change) {
    const auto &id = traj.traj_id();
    ObstacleBehavior object_behavior;
    object_behavior.obs_intent = ObstacleIntention::kUnknown;
    object_behavior.obs_direction = ObstacleDirection::kOncoming;

    const double ego_heading_angle = plan_start_point.path_point().theta();
    const double object_heading_angle = traj.pose().theta();
    const double angle_diff =
        std::abs(NormalizeAngle(ego_heading_angle - object_heading_angle));
    const bool is_cross_trajectory = IsCrossingTrajectory(drive_passage, traj);

    if (is_cross_trajectory) {
        if (angle_diff < 0.0) {
            object_behavior.obs_intent = ObstacleIntention::kLeftCross;
            return object_behavior;
        }

        if (angle_diff > 0.0) {
            object_behavior.obs_intent = ObstacleIntention::kRightCross;
            return object_behavior;
        }
    }

    if (std::fabs(angle_diff) > 3 * M_PI / 4) {
        object_behavior.obs_direction = ObstacleDirection::kOncoming;
    } else {
        object_behavior.obs_direction = ObstacleDirection::kSameDirection;
    }

    const bool is_cutin_object =
        IsCutInObjectTrajectory(drive_passage, is_lane_change,
                                plan_start_point.v(), ego_frenet_box, traj);
    if (!is_cutin_object) {
        return object_behavior;
    }

    const double object_centre_l = object_frenet_box.center_l();
    bool is_to_right = is_lane_change && !lc_left;
    bool is_to_left = is_lane_change && lc_left;

    double cur_lane_width = 0.0;

    double cur_lane_right_width = 0.0;
    double cur_lane_left_width = 0.0;
    std::tie(cur_lane_right_width, cur_lane_left_width) =
        path_boundary.QueryTargetBoundaryL(object_frenet_box.center_s());

    int kIndex = -1;
    int sgx = 0;
    if (((object_behavior.obs_direction == ObstacleDirection::kOncoming) &&
         is_to_right) ||
        ((object_behavior.obs_direction != ObstacleDirection::kOncoming) &&
         is_to_left)) {
        kIndex = 2;
        sgx = -1;
        cur_lane_width = cur_lane_right_width;
    } else if (((object_behavior.obs_direction ==
                 ObstacleDirection::kOncoming) &&
                is_to_left) ||
               ((object_behavior.obs_direction !=
                 ObstacleDirection::kOncoming) &&
                is_to_right)) {
        kIndex = 0;
        sgx = 1;
        cur_lane_width = cur_lane_left_width;
    }

    if ((object_centre_l <= cur_lane_left_width) &&
        (object_centre_l >= -cur_lane_right_width)) {
        object_behavior.obs_intent = (sgx > 0) ? ObstacleIntention::kCutoutRight
                                               : ObstacleIntention::kCutoutLeft;
    } else if (((-sgx * object_centre_l) > cur_lane_width) &&
               ((-sgx * object_centre_l) < (3 * cur_lane_width))) {
        object_behavior.obs_intent = (sgx > 0)
                                         ? ObstacleIntention::kCutoutRightRight
                                         : ObstacleIntention::kCutoutLeftLeft;
    } else {
        object_behavior.obs_intent = ObstacleIntention::kIgnore;
    }

    if (object_behavior.obs_intent < ObstacleIntention::kCutoutLeft) {
        if (((sgx * object_centre_l) > cur_lane_width) &&
            ((sgx * object_centre_l) < ((2 * cur_lane_width) + 0.3))) {
            object_behavior.obs_intent = (sgx > 0)
                                             ? ObstacleIntention::kLeftCutin
                                             : ObstacleIntention::kRightCutin;
        } else if (((sgx * object_centre_l) >= (3 * cur_lane_width)) &&
                   ((sgx * object_centre_l) < ((4 * cur_lane_width) + 0.3))) {
            object_behavior.obs_intent =
                (sgx > 0) ? ObstacleIntention::kLeftLeftCutin
                          : ObstacleIntention::kRightRightCutin;
        } else {
            object_behavior.obs_intent = ObstacleIntention::kIgnore;
        }
    }
    return object_behavior;
}

}  // namespace

std::unordered_map<std::string, ObstacleBehavior> InferObstaclesBehavior(
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_boundary,
    const FrenetBox &ego_frenet_box,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const ApolloTrajectoryPointProto &plan_start_point,
    bool lc_left,
    bool is_lane_change) {
    std::unordered_map<std::string, ObstacleBehavior> obstacles_behavior_map;
    const auto &extended_trajectories =
        *st_planner_object_traj.extended_trajectories;
    for (const auto &traj : extended_trajectories) {
        if (ShouldConsiderObject(traj, path_boundary, drive_passage, lc_left)) {
            const absl::StatusOr<FrenetBox> object_frenet_box =
                QueryXY2SLMapByBox(drive_passage, traj.bounding_box());
            if (!object_frenet_box.ok()) {
                obstacles_behavior_map[traj.traj_id()] = ObstacleBehavior();

                continue;
            }
            ObstacleBehavior object_behavior = ObstacleIntentionEstimation(
                drive_passage, path_boundary, object_frenet_box.value(),
                ego_frenet_box, traj, plan_start_point, lc_left,
                is_lane_change);

            obstacles_behavior_map[traj.traj_id()] = std::move(object_behavior);
        } else {
            obstacles_behavior_map[traj.traj_id()] = ObstacleBehavior();
        }
    }
    return obstacles_behavior_map;
}

}  // namespace planning

}  // namespace pnc_x
