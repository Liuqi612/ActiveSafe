

#include <algorithm>
#include <boost/algorithm/clamp.hpp>
#include <cmath>
#include <limits>
#include <ostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "decision/decision_util.h"
#include "decision/leading_groups_builder.h"
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

constexpr double kLateralEnterThres = 0.8;
constexpr double kLateralOutThres = 0.8;
struct LeadingObjectTrajectoryInfo {
    std::string object_id;
    std::string traj_id;
    double front_s = 0.0;
    double rear_s = 0.0;
    double first_t = 0.0;
    double first_v = 0.0;
};

bool HasEnteredSlBoundary(const PathSlBoundary &path_boundary,
                          const FrenetBox &fbox,
                          bool lc_left) {
    auto boundaries = CalcSlBoundaries(path_boundary, fbox);
    double boundary_left_l = boundaries.first;
    double boundary_right_l = boundaries.second;
    double l_center = path_boundary.QueryReferenceCenterL(fbox.center_s());

    if (lc_left) {
        return fbox.l_min < boundary_left_l - kLateralEnterThres &&
               fbox.l_max > l_center - kLateralOutThres;
    } else {
        return fbox.l_max > boundary_right_l + kLateralEnterThres &&
               fbox.l_min < l_center + kLateralOutThres;
    }
}

bool HasEnteredEnclosingSlBoundary(const DrivePassage &drive_passage,
                                   const FrenetBox &fbox,
                                   bool lc_left) {
    auto boundary = drive_passage.QueryEnclosingLaneBoundariesAtS(fbox.s_min);
    auto target_right_boundary = boundary.right;
    auto target_left_boundary = boundary.left;
    const double boundary_right_l =
        target_right_boundary.has_value()
            ? std::max(target_right_boundary->lat_offset, -kMaxHalfLaneWidth)
            : -kMaxHalfLaneWidth;
    const double boundary_left_l =
        target_left_boundary.has_value()
            ? std::min(target_left_boundary->lat_offset, kMaxHalfLaneWidth)
            : kMaxHalfLaneWidth;

    return lc_left ? fbox.l_min < boundary_left_l - kLateralEnterThres &&
                         fbox.l_max > -kLateralOutThres
                   : fbox.l_max > boundary_right_l + kLateralEnterThres &&
                         fbox.l_min < kLateralOutThres;
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

bool ShouldConsiderInteraction(const SpacetimeObjectTrajectory &traj,
                               double ego_heading,
                               const FrenetBox &ego_frenet_box,
                               const DrivePassage &drive_passage,
                               bool lc_left,
                               LeadingObjectTrajectoryInfo *traj_info) {
    const auto &states = traj.states();
    if (std::abs(NormalizeAngle(ego_heading -
                                states.front().traj_point->theta())) > M_PI_2) {
        return false;
    }

    const absl::StatusOr<FrenetBox> result =
        QueryXY2SLMapByBox(drive_passage, states.front().box);

    if (result.ok()) {
        if (HasEnteredEnclosingSlBoundary(drive_passage, result.value(),
                                          lc_left)) {
            traj_info->object_id = traj.object_id();
            traj_info->traj_id = traj.traj_id();
            traj_info->front_s = result.value().s_max;
            traj_info->rear_s = result.value().s_min;
            traj_info->first_t = 0.0;
            traj_info->first_v = states.front().traj_point->v();
            return true;
        }
    }

    constexpr int kEvalStep = 2;
    constexpr double kLookAheadTime = 5.0;
    constexpr int kEnterSRangeStep =
        static_cast<int>(kLookAheadTime / kTrajectoryTimeStep);
    bool is_valid = false;
    int projected_states = 1, along_path_states = 0;
    double front_s{0.0}, rear_s{0.0}, first_t{0.0}, first_v{0.0};
    for (int i = 1; i < states.size(); i += kEvalStep) {
        if (i > kEnterSRangeStep) {
            break;
        }

        ASSIGN_OR_CONTINUE(const auto fbox,
                           QueryXY2SLMapByBox(drive_passage, states[static_cast<size_t>(i)].box));
        ++projected_states;
        if (!is_valid) {
            is_valid = true;
            front_s = fbox.s_max;
            rear_s = fbox.s_min;
            first_t = i * kTrajectoryTimeStep;
            first_v = states[static_cast<size_t>(i)].traj_point->v();
        }

        if (HasEnteredEnclosingSlBoundary(drive_passage, fbox, lc_left)) {
            ++along_path_states;
        }
    }

    constexpr double kMoveAlongPathPercentageThreshold = 0.5;
    const double on_path_ratio = static_cast<double>(along_path_states) /
                                 static_cast<double>(projected_states);
    if (on_path_ratio > kMoveAlongPathPercentageThreshold) {
        traj_info->object_id = traj.object_id();
        traj_info->traj_id = traj.traj_id();
        traj_info->front_s = front_s;
        traj_info->rear_s = rear_s;
        traj_info->first_t = first_t;
        traj_info->first_v = first_v;
        return true;
    }
    return false;
}

bool ShouldConsiderInteraction(const SpacetimeObjectTrajectory &traj,
                               double ego_heading,
                               const FrenetBox &ego_frenet_box,
                               const PathSlBoundary &path_boundary,
                               const DrivePassage &drive_passage,
                               bool lc_left,
                               LeadingObjectTrajectoryInfo *traj_info) {
    const auto &states = traj.states();
    if (std::abs(NormalizeAngle(ego_heading -
                                states.front().traj_point->theta())) > M_PI_2) {
        return false;
    }

    const absl::StatusOr<FrenetBox> result =
        QueryXY2SLMapByBox(drive_passage, states.front().box);
    if (result.ok()) {
        if (HasEnteredSlBoundary(path_boundary, result.value(), lc_left)) {
            traj_info->object_id = traj.object_id();
            traj_info->traj_id = traj.traj_id();
            traj_info->front_s = result.value().s_max;
            traj_info->rear_s = result.value().s_min;
            traj_info->first_t = 0.0;
            traj_info->first_v = states.front().traj_point->v();
            return true;
        }
    }

    constexpr int kEvalStep = 2;
    constexpr double kLookAheadTime = 5.0;
    constexpr int kEnterSRangeStep =
        static_cast<int>(kLookAheadTime / kTrajectoryTimeStep);
    bool is_valid = false;
    int projected_states = 1, along_path_states = 0;
    double front_s{0.0}, rear_s{0.0}, first_t{0.0}, first_v{0.0};
    for (int i = 1; i < states.size(); i += kEvalStep) {
        if (i > kEnterSRangeStep) {
            break;
        }

        ASSIGN_OR_CONTINUE(const auto fbox,
                           QueryXY2SLMapByBox(drive_passage, states[static_cast<size_t>(i)].box));
        ++projected_states;
        if (!is_valid) {
            is_valid = true;
            front_s = fbox.s_max;
            rear_s = fbox.s_min;
            first_t = i * kTrajectoryTimeStep;
            first_v = states[static_cast<size_t>(i)].traj_point->v();
        }
        if (HasEnteredSlBoundary(path_boundary, fbox, lc_left)) {
            ++along_path_states;
        }
    }

    constexpr double kMoveAlongPathPercentageThreshold = 0.5;
    const double on_path_ratio = static_cast<double>(along_path_states) /
                                 static_cast<double>(projected_states);
    if (on_path_ratio > kMoveAlongPathPercentageThreshold) {
        traj_info->object_id = traj.object_id();
        traj_info->traj_id = traj.traj_id();
        traj_info->front_s = front_s;
        traj_info->rear_s = rear_s;
        traj_info->first_t = first_t;
        traj_info->first_v = first_v;
        return true;
    }

    return false;
}

absl::StatusOr<FrenetBox> FilterObjectViaDrivePassage(
    const PlannerObject &object,
    const DrivePassage &passage,
    const PathSlBoundary &sl_boundary,
    const FrenetBox &ego_frenet_box,
    double trusted_max_s) {
    ASSIGN_OR_RETURN(const auto object_frenet_box,
                     passage.QueryFrenetBoxAt(object.bounding_box()));

    if (object_frenet_box.s_min > trusted_max_s) {
        return absl::OutOfRangeError(absl::StrFormat(
            "Object %s out of trusted s max boundary, min_s > "
            "trusted_max_s: (%.2f > %.2f)",
            object.id(), object_frenet_box.s_min, trusted_max_s));
    }
    constexpr double kLateralEnterThres = 0.5;
    auto boundaries = CalcSlBoundaries(sl_boundary, object_frenet_box);
    const double boundary_l_max = boundaries.first;
    const double boundary_l_min = boundaries.second;

    if (object_frenet_box.l_min > boundary_l_max - kLateralEnterThres ||
        object_frenet_box.l_max < boundary_l_min + kLateralEnterThres) {
        return absl::OutOfRangeError(absl::StrFormat(
            "Object %s out of lateral boundary, l range: (%.2f, %.2f)",
            object.id(), object_frenet_box.l_min, object_frenet_box.l_max));
    }

    if (object_frenet_box.s_min < ego_frenet_box.s_max ||
        object_frenet_box.s_min > sl_boundary.end_s()) {
        return absl::OutOfRangeError(absl::StrFormat(
            "Object %s out of longitudinal boundary, s range: ( %.2f, %.2f)",
            object.id(), object_frenet_box.s_min, object_frenet_box.s_max));
    }
    return object_frenet_box;
}

absl::StatusOr<FrenetBox> FilterObjectViaDrivePassage(
    const PlannerObject &object,
    const DrivePassage &passage,
    const FrenetBox &ego_frenet_box,
    double trusted_max_s) {
    ASSIGN_OR_RETURN(const auto object_frenet_box,
                     passage.QueryFrenetBoxAt(object.bounding_box()));
    if (object_frenet_box.s_min > trusted_max_s) {
        return absl::OutOfRangeError(absl::StrFormat(
            "Object %s out of trusted s max boundary, min_s > "
            "trusted_max_s: (%.2f > %.2f)",
            object.id(), object_frenet_box.s_min, trusted_max_s));
    }

    constexpr double kLateralEnterThres = 0.5;
    auto boundary =
        passage.QueryEnclosingLaneBoundariesAtS(object_frenet_box.s_min);
    auto target_right_boundary = boundary.right;
    auto target_left_boundary = boundary.left;
    const double boundary_right_l =
        target_right_boundary.has_value()
            ? std::max(target_right_boundary->lat_offset, -kMaxHalfLaneWidth)
            : -kMaxHalfLaneWidth;
    const double boundary_left_l =
        target_left_boundary.has_value()
            ? std::min(target_left_boundary->lat_offset, kMaxHalfLaneWidth)
            : kMaxHalfLaneWidth;
    if (object_frenet_box.l_min > boundary_left_l - kLateralEnterThres ||
        object_frenet_box.l_max < boundary_right_l + kLateralEnterThres) {
        return absl::OutOfRangeError(absl::StrFormat(
            "Object %s out of lateral boundary, l range: (%.2f, %.2f)",
            object.id(), object_frenet_box.l_min, object_frenet_box.l_max));
    }
    return object_frenet_box;
}

absl::StatusOr<bool> IsOncomingObjectJudgeByDrivePassage(
    const DrivePassage &passage, const SecondOrderTrajectoryPoint &obj_pose) {
    ASSIGN_OR_RETURN(const auto tangent,
                     passage.QueryTangentAt(obj_pose.pos()));
    const double passage_angle = tangent.Angle();
    const double angle_diff =
        std::abs(NormalizeAngle(passage_angle - obj_pose.theta()));

    return angle_diff > M_PI_2;
}

std::string FindFrontObjectIdOnCurrentLane(
    const DrivePassage &passage,
    const PathSlBoundary &sl_boundary,
    const absl::Span<const SpacetimeObjectTrajectory> &st_trajs,
    const FrenetBox &ego_frenet_box,
    const absl::flat_hash_set<std::string> &stalled_objects,
    const std::vector<LeadingObjectTrajectoryInfo> &filtered_trajs) {
    const double kUntrustedSBeforeStitchS = 45.0;
    const double trusted_max_s = 200;
    // TODO:(xc)
    // std::max(100.0, (psmm.map_ptr()->trusted_curvature_path_s_max() -
    //                  kUntrustedSBeforeStitchS));
    std::string front_object_id;
    double front_s = std::numeric_limits<double>::max();
    std::unordered_set<std::string> filtered_ids;

    for (const auto &filtered_traj : filtered_trajs) {
        filtered_ids.insert(filtered_traj.object_id);
    }
    for (const auto &st_traj : st_trajs) {
        if (filtered_ids.find(st_traj.planner_object().id()) !=
            filtered_ids.end()) {
            continue;
        }

        if (!IsLeadingObjectType(st_traj.planner_object().type())) {
            continue;
        }

        const auto res =
            IsOncomingObjectJudgeByDrivePassage(passage, st_traj.pose());
        if ((!res.ok() || *res == true) &&
            stalled_objects.find(st_traj.planner_object().id()) ==
                stalled_objects.end()) {
            continue;
        }

        ASSIGN_OR_CONTINUE(const auto obj_fbox,
                           FilterObjectViaDrivePassage(
                               st_traj.planner_object(), passage, sl_boundary,
                               ego_frenet_box, trusted_max_s));
        if (obj_fbox.s_min < front_s && obj_fbox.s_min > 0.0) {
            front_s = obj_fbox.s_min;
            front_object_id = std::string(st_traj.object_id());
        }
    }
    return front_object_id;
}

std::string FindFrontObjectIdOnCurrentLane(
    const DrivePassage &passage,
    const PathSlBoundary &sl_boundary,
    const absl::Span<const SpacetimeObjectTrajectory> &st_trajs,
    const FrenetBox &ego_frenet_box,
    const absl::flat_hash_set<std::string> &stalled_objects,
    const DrivePassage *passage_lk) {
    if (passage_lk == nullptr) {
        return "";
    }
    const double kUntrustedSBeforeStitchS = 45.0;
    const double trusted_max_s = 200;
    // TODO:(xc)
    // std::max(100.0, (psmm.map_ptr()->trusted_curvature_path_s_max() -
    //                  kUntrustedSBeforeStitchS));
    std::string front_object_id;
    double front_s = std::numeric_limits<double>::max();
    for (const auto &st_traj : st_trajs) {
        if (!IsLeadingObjectType(st_traj.planner_object().type())) {
            continue;
        }

        const auto res =
            IsOncomingObjectJudgeByDrivePassage(passage, st_traj.pose());
        if ((!res.ok() || *res == true) &&
            stalled_objects.find(st_traj.planner_object().id()) ==
                stalled_objects.end()) {
            continue;
        }

        ASSIGN_OR_CONTINUE(
            const auto obj_fbox,
            FilterObjectViaDrivePassage(st_traj.planner_object(), *passage_lk,
                                        ego_frenet_box, trusted_max_s));
        if (obj_fbox.s_min < front_s && obj_fbox.s_min > 0.0) {
            front_s = obj_fbox.s_min;
            front_object_id = std::string(st_traj.object_id());
        }
    }
    return front_object_id;
}

}  // namespace

std::vector<LeadingGroup> FindMultipleLeadingGroups(
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_boundary,
    bool lc_left,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const absl::flat_hash_set<std::string> &stalled_objects,
    const ApolloTrajectoryPointProto &plan_start_point,
    const FrenetBox &ego_frenet_box,
    const VehicleGeometryParamsProto &vehicle_geom,
    bool is_astar_searcher,
    std::vector<std::vector<std::string>> *insertion_orders,
    std::string *current_path_leader_id,
    const std::unordered_map<std::string, std::shared_ptr<DrivePassage>>
        *drive_passages) {
    std::vector<LeadingGroup> leading_groups;

    const auto &considered_trajectories =
        *st_planner_object_traj.extended_trajectories;
    const double ego_heading = plan_start_point.path_point().theta();
    const double ego_speed = plan_start_point.v();
    std::vector<LeadingObjectTrajectoryInfo> filtered_trajs;
    std::vector<LeadingObjectTrajectoryInfo> filtered_trajs_for_ori_lead;
    DrivePassage *lk_passage = nullptr;
    if (drive_passages != nullptr) {
        for (const auto &kv : *drive_passages) {
            const std::string &key = kv.first;
            const std::shared_ptr<DrivePassage> &passage_ptr = kv.second;
            const std::regex lk_pattern("^lk.*");
            if (std::regex_match(key, lk_pattern)) {
                lk_passage = passage_ptr.get();
                break;
            }
        }
    }
    constexpr double kHighSpeedCyclist = 3.0;
    for (const auto &traj : considered_trajectories) {
        // VLOG(3) << "Consider traj: " << traj.traj_id();
        const auto object_type = traj.planner_object().type();
        LeadingObjectTrajectoryInfo traj_info;
        LeadingObjectTrajectoryInfo traj_info_for_ori_lead;

        if (traj.states().empty()) {
            continue;
        }
        const auto &first_state = traj.states().front();
        if (first_state.traj_point == nullptr) {
            continue;
        }
        const bool is_low_speed_cyclist =
            (object_type == ObjectType::OT_CYCLIST ||
             object_type == ObjectType::OT_TRICYCLIST) &&
            (first_state.traj_point->v() < kHighSpeedCyclist);
        if (is_low_speed_cyclist) {
            continue;
        }

        if (IsLeadingObjectType(object_type) &&
            ShouldConsiderInteraction(traj, ego_heading, ego_frenet_box,
                                      drive_passage, lc_left, &traj_info)) {
            filtered_trajs.push_back(traj_info);
        }
        if ((lk_passage == nullptr) &&
            (IsLeadingObjectType(object_type) &&
             ShouldConsiderInteraction(traj, ego_heading, ego_frenet_box,
                                       path_boundary, drive_passage, lc_left,
                                       &traj_info_for_ori_lead))) {
            filtered_trajs_for_ori_lead.push_back(traj_info_for_ori_lead);
        }
    }

    constexpr double kDrivePassageMinS = -60.0;
    constexpr double kMaxTimeStepDistance = 6.0;
    std::stable_sort(
        filtered_trajs.begin(), filtered_trajs.end(),
        [](const LeadingObjectTrajectoryInfo &traj1,
           const LeadingObjectTrajectoryInfo &traj2) {
            if (traj1.front_s - kDrivePassageMinS < kMaxTimeStepDistance &&
                traj2.front_s - kDrivePassageMinS < kMaxTimeStepDistance) {
                return traj1.first_t > traj2.first_t;
            } else if (std::fabs(traj1.rear_s - traj2.rear_s) > kMathEpsilon) {
                return traj1.rear_s < traj2.rear_s;
            } else {
                return traj1.front_s < traj2.front_s;
            }
        });
    if (filtered_trajs.empty()) {
        return leading_groups;
    }

    if (lk_passage != nullptr) {
        *current_path_leader_id = FindFrontObjectIdOnCurrentLane(
            drive_passage, path_boundary,
            *st_planner_object_traj.extended_trajectories, ego_frenet_box,
            stalled_objects, lk_passage);
    } else {
        *current_path_leader_id = FindFrontObjectIdOnCurrentLane(
            drive_passage, path_boundary,
            *st_planner_object_traj.extended_trajectories, ego_frenet_box,
            stalled_objects, filtered_trajs_for_ori_lead);
    }

    LeadingGroup traj_group;
    std::vector<std::string> group_order;
    std::set<std::string> object_ids;
    std::string pre_object_id;
    const double min_gap = vehicle_geom.length() * 2.0;
    double previous_s = std::numeric_limits<double>::lowest();
    constexpr double kFrontTailMaxS = 80.0;
    constexpr double kFrontTailMinS = 30.0;
    constexpr double kGapStaticDistT = 8.0;
    const double gap_static_dist_threshold = boost::algorithm::clamp(
        ego_speed * kGapStaticDistT, kFrontTailMinS, kFrontTailMaxS);
    bool is_faraway_tail = false;
    const double kUntrustedSBeforeStitchS = 45;
    const double trusted_max_s = 200;
    // TODO:(xc)
    // std::max(100.0, (psmm.map_ptr()->trusted_curvature_path_s_max() -
    //                  kUntrustedSBeforeStitchS));
    for (size_t i = 0; i < filtered_trajs.size(); ++i) {
        if ((filtered_trajs[i].front_s >= path_boundary.end_s() ||
             filtered_trajs[i].rear_s >= trusted_max_s) ||
            is_faraway_tail)
            break;
        if (object_ids.count(filtered_trajs[i].object_id)) continue;

        object_ids.insert(filtered_trajs[i].object_id);
        if (!traj_group.empty() && !group_order.empty()) {
            const double current_gap =
                (filtered_trajs[i].rear_s -
                 filtered_trajs[i].first_t * filtered_trajs[i].first_v) -
                previous_s;
            if (current_gap >= min_gap) {
                if (filtered_trajs[i].front_s > ego_frenet_box.s_max) {
                    insertion_orders->push_back(group_order);
                    leading_groups.push_back(traj_group);
                    group_order.clear();
                    traj_group.clear();
                } else {
                    group_order.clear();
                    traj_group.clear();
                }
            }
        }

        if (!stalled_objects.contains(filtered_trajs[i].object_id)) {
            ConstraintProto::LeadingObjectProto leading_object =
                CreateLeadingObject(
                    *st_planner_object_traj.FindTrajectoryById(
                        filtered_trajs[i].traj_id),
                    drive_passage,
                    ConstraintProto::LeadingObjectProto::LANE_CHANGE_TARGET,
                    traj_group.empty());
            leading_object.mutable_gap_proto()->set_leader_id(
                filtered_trajs[i].object_id);
            leading_object.mutable_gap_proto()->set_follower_id(pre_object_id);
            group_order.push_back(filtered_trajs[i].traj_id);
            traj_group.emplace(filtered_trajs[i].traj_id,
                               std::move(leading_object));
        }
        previous_s = filtered_trajs[i].front_s -
                     filtered_trajs[i].first_t * filtered_trajs[i].first_v;
        pre_object_id = filtered_trajs[i].object_id;
        const double static_gap_with_ego =
            filtered_trajs[i].rear_s - ego_frenet_box.s_max;
        is_faraway_tail = gap_static_dist_threshold < static_gap_with_ego;
        const int max_multi_traj_num_minus1 =
            FLAGS_planner_initializer_max_multi_traj_num - 1;
        if (leading_groups.size() ==
            static_cast<size_t>(max_multi_traj_num_minus1)) {
            break;
        }
    }
    if (!traj_group.empty() && !group_order.empty()) {
        leading_groups.push_back(traj_group);
        insertion_orders->push_back(group_order);
        group_order.clear();
        traj_group.clear();
    }
    if (is_astar_searcher &&
        insertion_orders->size() <
            FLAGS_planner_initializer_max_multi_traj_num &&
        !stalled_objects.contains(filtered_trajs.back().object_id) &&
        !is_faraway_tail) {
        ConstraintProto::LeadingObjectProto null_leading_object;
        null_leading_object.set_traj_id("");
        null_leading_object.mutable_gap_proto()->set_leader_id(
            kNullLeadingObjectId);
        null_leading_object.mutable_gap_proto()->set_follower_id(pre_object_id);
        group_order.push_back(kNullLeadingObjectId);
        traj_group.emplace(kNullLeadingObjectId,
                           std::move(null_leading_object));
        leading_groups.push_back(traj_group);
        insertion_orders->push_back(group_order);
    }
    return leading_groups;
}

}  // namespace planning
}  // namespace pnc_x
