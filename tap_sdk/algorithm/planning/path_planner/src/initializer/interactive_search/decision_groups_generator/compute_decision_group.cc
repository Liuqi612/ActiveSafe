

#include <algorithm>
#include <cmath>
#include <iterator>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "common/gflags.h"
#include "pncx_constraint.pb.h"
#include "initializer/interactive_search/decision_groups_generator/compute_decision_group.h"
#include "initializer/ref_speed_table.h"
#include "math/frenet_common.h"
#include "math/geometry/box2d.h"
#include "math/geometry/util.h"
#include "math/util.h"
#include "object/spacetime_object_state.h"
#include "object/spacetime_object_trajectory.h"
#include "object/spacetime_trajectory_manager.h"
#include "plan/planner_defs.h"
#include "plan/planner_flags.h"
#include "pncx_planner_params.pb.h"
#include "prediction/predicted_trajectory.h"
#include "router/drive_passage.h"
#include "pncx_trajectory_point.pb.h"
#include "util/loop_guard.h"
#include "util/status_macros.h"
#include "util/vehicle_geometry_util.h"
#include "pncx_vehicle.pb.h"
#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>
#include <absl/status/status.h>
#include <absl/strings/str_format.h>
#include <absl/strings/str_join.h>
#include <absl/types/span.h>
#include "common/log.h"

namespace pnc_x {
namespace planning {

namespace {

template <typename T>
double InverseLerp(const T &x, const T &y, const T &v) {
    static_assert(!std::is_enum<T>::value, "InverseLerp doesn't support enum.");
    XCHECK_NE(x, y);
    return static_cast<double>(v - x) / (y - x);
}

double SaturatedLinearFunction(double min_x,
                               double max_x,
                               double y_at_min_x,
                               double y_at_max_x,
                               double x) {
    constexpr double kEpsilon = 1.0e-5;
    XCHECK_GE(max_x - kEpsilon, min_x);
    const double ratio =
        boost::algorithm::clamp(InverseLerp(min_x, max_x, x), 0.0, 1.0);
    return Lerp(y_at_min_x, y_at_max_x, ratio);
}

}  // namespace

std::vector<SpeedPoint> GenerateConstAccelSpeedPoints(double init_v,
                                                      double init_s,
                                                      double init_t,
                                                      double accel,
                                                      double step_time,
                                                      double acc_time,
                                                      double duration) {
    constexpr double kEpsilon = 1e-6;
    std::vector<SpeedPoint> speed_points;
    speed_points.reserve(static_cast<int>(std::ceil(duration / step_time)));
    double prev_v = init_v;
    double prev_s = init_s;
    for (double t = step_time; t < (duration + kEpsilon); t += step_time) {
        SpeedPoint sp;
        sp.set_t(t + init_t);
        if (t <= (acc_time + kEpsilon)) {
            const double v = std::max(0.0, prev_v + (accel * step_time));
            sp.set_t(t + init_t);
            sp.set_a((v - prev_v) / step_time);
            sp.set_v(v);
            sp.set_s(prev_s + (0.5 * (prev_v + v) * step_time));
            sp.set_j(0.0);
        } else {
            sp.set_t(t + init_t);
            sp.set_a(0.0);
            sp.set_v(prev_v);
            sp.set_s(prev_s + (prev_v * step_time));
            sp.set_j(0.0);
        }
        prev_v = sp.v();
        prev_s = sp.s();
        speed_points.emplace_back(std::move(sp));
    }
    return speed_points;
}

std::vector<ObstaclePointInfo> TransferTrajectoryFromXY2SL(
    const DrivePassage &drive_passage, const SpacetimeObjectTrajectory &traj) {
    constexpr double kEpsilon = 1e-6;
    std::vector<ObstaclePointInfo> obstacle_sl_points;
    if (traj.states().empty()) {
        return obstacle_sl_points;
    }
    obstacle_sl_points.reserve(traj.states().size());
    for (const auto &state : traj.states()) {
        FrenetBox frenet_box;
        absl::StatusOr<FrenetBox> fbox =
            drive_passage.QueryFrenetBoxAt(state.box, false);
        if (fbox.ok()) {
            frenet_box = std::move(fbox.value());
        }
        if ((frenet_box.s_max + kEpsilon) < frenet_box.s_min) {
            continue;
        }
        prediction::PredictedTrajectoryPoint traj_point = *state.traj_point;
        SLBoundary sl_boundary = SLBoundary{.s_min = frenet_box.s_min,
                                            .s_max = frenet_box.s_max,
                                            .l_min = frenet_box.l_min,
                                            .l_max = frenet_box.l_max};
        obstacle_sl_points.emplace_back(std::move(sl_boundary),
                                        sl_boundary.center(), state.box,
                                        std::move(traj_point));
    }
    return obstacle_sl_points;
}

SpacetimeObjectTrajectory ModifyDecPredictedTrajectory(
    const DrivePassage &drive_passage,
    const SpacetimeObjectTrajectory &object_trajectory,
    const FrenetBox *av_frenet_box,
    const InitializerConfig *initializer_params,
    double ego_v) {
    if (object_trajectory.states().empty() || av_frenet_box == nullptr) {
        return object_trajectory;
    }
    const auto boundaries =
        drive_passage.QueryEnclosingLaneBoundariesAtS(av_frenet_box->s_max);
    double l_dist = 0.0;
    if ((av_frenet_box->center_l() - boundaries.left->lat_offset) > 0.0) {
        l_dist = av_frenet_box->center_l() - boundaries.left->lat_offset;
    } else if ((av_frenet_box->center_l() - boundaries.right->lat_offset) <
               0.0) {
        l_dist = boundaries.right->lat_offset - av_frenet_box->center_l();
    } else {
        l_dist = 0.0;
    }
    constexpr double kDefaultLaneHalfWidth = 1.8;
    constexpr double kMinSenseTime = 0.01;
    constexpr double kMaxSenseTime = 1.5;
    constexpr double kDefaultDecAcc = -1.0;
    constexpr double kDefaultDecDuration = 3.0;
    constexpr double kFarObjectRatio = 2.0;
    const double large_object_acc =
        (initializer_params == nullptr)
            ? kDefaultDecAcc
            : initializer_params->interactive_astar_search_config()
                  .interactive_param()
                  .tighten_large_object_acc();
    double sense_time = SaturatedLinearFunction(
        0.0, kDefaultLaneHalfWidth, kMinSenseTime, kMaxSenseTime, l_dist);
    double dec_acc = kDefaultDecAcc;
    double dec_duration = kDefaultDecDuration;
    const absl::StatusOr<FrenetBox> result =
        drive_passage.QueryFrenetBoxAt(object_trajectory.states().front().box);
    const bool is_large_object =
        object_trajectory.object_type() == ObjectType::OT_LARGE_VEHICLE;
    if (!result.ok()) {
        sense_time = sense_time / kFarObjectRatio;
        dec_acc = dec_acc * kFarObjectRatio;
        dec_duration = dec_duration * kFarObjectRatio;
    }
    if (is_large_object) {
        dec_acc = large_object_acc;
    }
    const double total_original_time =
        object_trajectory.trajectory().points().back().t();
    if (sense_time < 0.0 || sense_time > total_original_time ||
        object_trajectory.states().size() < 2) {
        return object_trajectory;
    }
    const int object_trajectory_num = object_trajectory.states().size();
    const double planning_traj_time =
        kInitializerTrajectoryExtendSteps * kTrajectoryTimeStep;
    const double all_duration = planning_traj_time - sense_time;
    const int sense_time_index = boost::algorithm::clamp(
        static_cast<int>(sense_time / kTrajectoryTimeStep), 0,
        object_trajectory_num - 1);
    prediction::PredictedTrajectory modified_trajectory(
        object_trajectory.trajectory());
    modified_trajectory.mutable_points()->resize(sense_time_index + 1);
    modified_trajectory.mutable_points()->reserve(
        kInitializerTrajectoryExtendSteps);

    const prediction::PredictedTrajectoryPoint &sense_time_point =
        *(object_trajectory.states()[sense_time_index].traj_point);
    const std::vector<SpeedPoint> &speed_points = GenerateConstAccelSpeedPoints(
        sense_time_point.v(), sense_time_point.s(), sense_time_point.t(),
        dec_acc, kTrajectoryTimeStep, dec_duration, all_duration);
    prediction::PredictedTrajectoryPoint last_point = sense_time_point;
    const double cos_theta = pnc_x::fast_math::Cos(last_point.theta());
    const double sin_theta = pnc_x::fast_math::Sin(last_point.theta());
    for (const auto &sp : speed_points) {
        last_point.set_v(sp.v());
        last_point.set_a(sp.a());
        last_point.set_t(sp.t());
        const double cur_x =
            last_point.pos().x() + (cos_theta * (sp.s() - last_point.s()));
        const double cur_y =
            last_point.pos().y() + (sin_theta * (sp.s() - last_point.s()));
        last_point.set_pos(Vec2d(cur_x, cur_y));
        last_point.set_s(sp.s());
        modified_trajectory.mutable_points()->emplace_back(last_point);
    }
    return SpacetimeObjectTrajectory(object_trajectory.planner_object(),
                                     std::move(modified_trajectory),
                                     object_trajectory.traj_index(),
                                     object_trajectory.required_lateral_gap());
}

std::pair<bool, int> IsPreMergeSafe(
    const std::vector<LeadingGroup> &leading_groups,
    const std::vector<std::vector<std::string>> &insertion_orders,
    const ObsDecisionGap *pre_obs_gap,
    bool is_pre_lane_change) {
    if (pre_obs_gap == nullptr || !pre_obs_gap->is_merge_safe.first ||
        insertion_orders.size() != leading_groups.size() ||
        !is_pre_lane_change) {
        return {false, 0};
    }
    for (int i = 0; i < leading_groups.size(); ++i) {
        if (insertion_orders[i].empty() || leading_groups[i].empty() ||
            insertion_orders[i].size() != leading_groups[i].size() ||
            !leading_groups[i].count(insertion_orders[i].front())) {
            continue;
        }
        const pnc_x::planning::ConstraintProto::LeadingObjectProto
            &leading_object_proto =
                leading_groups[i].at(insertion_orders[i].front());
        const auto &gap_proto = leading_object_proto.gap_proto();
        const bool is_lead_matched =
            gap_proto.leader_id().empty()
                ? (pre_obs_gap->lead_obj_id == boost::none ||
                   pre_obs_gap->lead_obj_id.value().empty())
                : ((pre_obs_gap->lead_obj_id.has_value() &&
                    gap_proto.leader_id() ==
                        pre_obs_gap->lead_obj_id.value()) ||
                   (!pre_obs_gap->lead_obj_id.has_value() &&
                    gap_proto.leader_id() == kNullLeadingObjectId));
        const bool is_tail_matched =
            gap_proto.follower_id().empty()
                ? (pre_obs_gap->tail_obj_id == boost::none ||
                   pre_obs_gap->tail_obj_id.value().empty())
                : (pre_obs_gap->tail_obj_id.has_value() &&
                   gap_proto.follower_id() == pre_obs_gap->tail_obj_id.value());
        if (is_lead_matched && is_tail_matched) {
            return {true, i};
        }
    }
    return {false, 0};
}

std::vector<ObstacleDecisionGroup> ComputeDecisionGroup(
    const DrivePassage &drive_passage,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const std::vector<LeadingGroup> &leading_groups,
    const std::vector<std::vector<std::string>> &insertion_orders,
    const ApolloTrajectoryPointProto &start_point,
    const LaneChangeStateProto &lc_state,
    const std::string *current_path_leader_id,
    const FrenetBox *av_frenet_box,
    const ObsDecisionGap *pre_obs_gap,
    const InitializerConfig *initializer_params,
    const boost::optional<std::string> &nullable_nearest_vru_obj_id,
    int plan_id,
    bool is_lane_change,
    bool is_pre_lane_change) {
    if (insertion_orders.size() != leading_groups.size()) {
        return {};
    }
    const double kUntrustedSBeforeStitchS = 45;
    const double trusted_max_s = 100;

    const int object_num = st_planner_object_traj.extended_trajectories->size();
    std::unordered_map<std::string, std::vector<ObstaclePointInfo>>
        obstale_object_infos;
    obstale_object_infos.reserve(object_num);
    std::unordered_set<std::string> default_objects_id_set;
    default_objects_id_set.reserve(object_num);
    constexpr int kStepNum = 2;
    constexpr double kLookAheadTime = 4.0;
    constexpr int kEnterSRangeStep =
        static_cast<int>(kLookAheadTime / kTrajectoryTimeStep);
    constexpr double kStationBackExtendS = 30.0;
    constexpr double kMinLateralWidth = 2.0;
    constexpr double kMaxLateralWidth = 6.0;
    for (const auto &traj : *st_planner_object_traj.extended_trajectories) {
        std::string obj_id =
            SpacetimeObjectTrajectory::GetObjectIdFromTrajectoryId(
                traj.traj_id());
        if (obj_id.empty() || default_objects_id_set.count(obj_id)) {
            continue;
        }
        default_objects_id_set.insert(obj_id);

        bool is_ignored_object = false;
        if (!is_lane_change) {
            for (int i = 0; i < traj.states().size(); i += kStepNum) {
                if (i > kEnterSRangeStep) {
                    break;
                }
                bool is_in_sl_map = false;
                double s = 0.0, l = 0.0;
                absl::StatusOr<FrenetBox> fbox =
                    drive_passage.QueryFrenetBoxAt(traj.states()[i].box);
                if (fbox.ok() && (fbox.value().s_max < 0.0)) {
                    is_ignored_object = true;
                    break;
                } else if (fbox.ok() && (fbox.value().s_max > 0.0)) {
                    break;
                }
            }
        } else {
            for (int i = 0; i < traj.states().size(); i += kStepNum) {
                if (i > kEnterSRangeStep) {
                    break;
                }
                bool is_in_sl_map = false;
                double s = 0.0, l = 0.0;
                absl::StatusOr<FrenetBox> fbox =
                    drive_passage.QueryFrenetBoxAt(traj.states()[i].box);
                if (fbox.ok() && (fbox.value().s_max < 0.0)) {
                    const double l_distance = SaturatedLinearFunction(
                        -kStationBackExtendS, 0.0, kMinLateralWidth,
                        kMaxLateralWidth, s);
                    const bool is_lateral_far_way =
                        lc_state.lc_left()
                            ? ((fbox.value().center_l() >
                                (2.0 * kMinLateralWidth)) ||
                               (fbox.value().center_l() < -l_distance))
                            : ((fbox.value().center_l() > l_distance) ||
                               (fbox.value().center_l() <
                                -(2.0 * kMinLateralWidth)));
                    if (is_lateral_far_way) {
                        is_ignored_object = true;
                        break;
                    }
                } else if (fbox.ok() && (fbox.value().s_max > 0.0)) {
                    break;
                }
            }
        }
        if (is_ignored_object) {
            continue;
        }
        std::vector<ObstaclePointInfo> modified_pred_default_traj =
            TransferTrajectoryFromXY2SL(drive_passage, traj);
        if (!modified_pred_default_traj.empty()) {
            obstale_object_infos.emplace(obj_id, modified_pred_default_traj);
        }
    }

    std::pair<bool, int> has_pre_safe_gap_pair = IsPreMergeSafe(
        leading_groups, insertion_orders, pre_obs_gap, is_pre_lane_change);

    bool has_no_lead_follow_scene = false;
    std::vector<ObstacleDecisionGroup> decision_groups;
    for (int i = 0; i < leading_groups.size(); ++i) {
        if (has_pre_safe_gap_pair.first && (has_pre_safe_gap_pair.second != i)) {
            continue;
        }
        if (insertion_orders[i].empty() || leading_groups[i].empty() ||
            (insertion_orders[i].size() != leading_groups[i].size()) ||
            !leading_groups[i].count(insertion_orders[i].front())) {
            continue;
        }
        const std::string obj_id =
            SpacetimeObjectTrajectory::GetObjectIdFromTrajectoryId(
                insertion_orders[i].front());
        const pnc_x::planning::ConstraintProto::LeadingObjectProto
            &leading_object_proto =
                leading_groups[i].at(insertion_orders[i].front());
        bool is_both_lead_follow_faraway = true;
        std::unordered_set<std::string> considered_objects_id_set;
        ObstacleDecisionGroup decision_group;
        decision_group.traj_time_step = kTrajectoryTimeStep;
        if (!current_path_leader_id->empty()) {
            considered_objects_id_set.insert(*current_path_leader_id);
        }
        if (!leading_object_proto.gap_proto().leader_id().empty()) {
            considered_objects_id_set.insert(
                leading_object_proto.gap_proto().leader_id());
        }
        if (!leading_object_proto.gap_proto().follower_id().empty()) {
            considered_objects_id_set.insert(
                leading_object_proto.gap_proto().follower_id());
        }

        if (!leading_object_proto.gap_proto().leader_id().empty()) {
            absl::Span<const SpacetimeObjectTrajectory *const>
                leading_object_trajectorys =
                    st_planner_object_traj.FindTrajectoriesByObjectId(obj_id);
            if (!leading_object_trajectorys.empty() &&
                (leading_object_trajectorys[0] != nullptr)) {
                std::vector<ObstaclePointInfo> modified_pred_leading_traj;
                if (obstale_object_infos.count(obj_id)) {
                    modified_pred_leading_traj =
                        obstale_object_infos.at(obj_id);
                } else {
                    modified_pred_leading_traj = TransferTrajectoryFromXY2SL(
                        drive_passage, *leading_object_trajectorys[0]);
                }
                if (!modified_pred_leading_traj.empty()) {
                    ObstacleDecision leading_obs_decision;
                    leading_obs_decision.obj_id =
                        leading_object_proto.gap_proto().leader_id();
                    leading_obs_decision.obs_moving_type =
                        leading_object_trajectorys[0]->is_stationary()
                            ? ObstacleMovingType::kStationary
                            : ObstacleMovingType::kDynamic;
                    leading_obs_decision.decision_tag.lon_decision_tag =
                        OvertakeYieldType::kYield;
                    leading_obs_decision.decision_tag.lat_decision_tag =
                        NudgeDirection::kNoNudge;
                    leading_obs_decision.object_type =
                        leading_object_trajectorys[0]->object_type();
                    leading_obs_decision.modified_pred_traj =
                        std::move(modified_pred_leading_traj);
                    leading_obs_decision.has_modified_pred = false;
                    decision_group.obs_goal_gap.lead_obj_id =
                        leading_object_proto.gap_proto().leader_id();
                    decision_group
                        .obstacles_decision[leading_obs_decision.obj_id] =
                        std::move(leading_obs_decision);
                    is_both_lead_follow_faraway = false;
                } else {
                }
            } else {
                if (leading_object_proto.gap_proto().leader_id() !=
                    kNullLeadingObjectId) {
                }
            }
        }

        if (!current_path_leader_id->empty()) {
            absl::Span<const SpacetimeObjectTrajectory *const>
                origin_object_trajectorys =
                    st_planner_object_traj.FindTrajectoriesByObjectId(
                        *current_path_leader_id);
            if (!origin_object_trajectorys.empty() &&
                (origin_object_trajectorys[0] != nullptr)) {
                std::vector<ObstaclePointInfo> modified_pred_origin_traj;
                if (obstale_object_infos.count(*current_path_leader_id)) {
                    modified_pred_origin_traj =
                        obstale_object_infos.at(*current_path_leader_id);
                } else {
                    modified_pred_origin_traj = TransferTrajectoryFromXY2SL(
                        drive_passage, *origin_object_trajectorys[0]);
                }
                if (!modified_pred_origin_traj.empty()) {
                    ObstacleDecision origin_obs_decision;
                    origin_obs_decision.obj_id = *current_path_leader_id;
                    origin_obs_decision.obs_moving_type =
                        origin_object_trajectorys[0]->is_stationary()
                            ? ObstacleMovingType::kStationary
                            : ObstacleMovingType::kDynamic;
                    origin_obs_decision.decision_tag.lon_decision_tag =
                        OvertakeYieldType::kYield;
                    origin_obs_decision.decision_tag.lat_decision_tag =
                        NudgeDirection::kNoNudge;
                    origin_obs_decision.object_type =
                        origin_object_trajectorys[0]->object_type();
                    origin_obs_decision.modified_pred_traj =
                        std::move(modified_pred_origin_traj);
                    origin_obs_decision.has_modified_pred = false;
                    decision_group.ori_lead_obj_id = *current_path_leader_id;
                    decision_group
                        .obstacles_decision[origin_obs_decision.obj_id] =
                        std::move(origin_obs_decision);
                } else {
                }
            } else {
            }
        }

        if (!leading_object_proto.gap_proto().follower_id().empty()) {
            absl::Span<const SpacetimeObjectTrajectory *const>
                follower_object_trajectorys =
                    st_planner_object_traj.FindTrajectoriesByObjectId(
                        leading_object_proto.gap_proto().follower_id());
            if (!follower_object_trajectorys.empty() &&
                (follower_object_trajectorys[0] != nullptr)) {
                const SpacetimeObjectTrajectory modified_object_trajectory =
                    ModifyDecPredictedTrajectory(
                        drive_passage, *follower_object_trajectorys[0],
                        av_frenet_box, initializer_params, start_point.v());
                std::vector<ObstaclePointInfo> modified_pred_follower_traj =
                    TransferTrajectoryFromXY2SL(drive_passage,
                                                modified_object_trajectory);

                std::vector<ObstaclePointInfo> src_tail_pred_traj;
                if (obstale_object_infos.count(
                        leading_object_proto.gap_proto().follower_id())) {
                    src_tail_pred_traj = obstale_object_infos.at(
                        leading_object_proto.gap_proto().follower_id());
                } else {
                    src_tail_pred_traj = TransferTrajectoryFromXY2SL(
                        drive_passage, *follower_object_trajectorys[0]);
                }
                if (!modified_pred_follower_traj.empty()) {
                    ObstacleDecision follower_obs_decision;
                    follower_obs_decision.obj_id =
                        leading_object_proto.gap_proto().follower_id();
                    follower_obs_decision.obs_moving_type =
                        follower_object_trajectorys[0]->is_stationary()
                            ? ObstacleMovingType::kStationary
                            : ObstacleMovingType::kDynamic;
                    follower_obs_decision.decision_tag.lon_decision_tag =
                        OvertakeYieldType::kOvertake;
                    follower_obs_decision.decision_tag.lat_decision_tag =
                        NudgeDirection::kNoNudge;
                    follower_obs_decision.object_type =
                        follower_object_trajectorys[0]->object_type();
                    follower_obs_decision.modified_pred_traj =
                        std::move(modified_pred_follower_traj);
                    follower_obs_decision.src_tail_pred_traj =
                        std::move(src_tail_pred_traj);
                    follower_obs_decision.has_modified_pred = true;
                    decision_group.obs_goal_gap.tail_obj_id =
                        leading_object_proto.gap_proto().follower_id();
                    decision_group
                        .obstacles_decision[follower_obs_decision.obj_id] =
                        std::move(follower_obs_decision);
                    is_both_lead_follow_faraway = false;
                } else {
                }
            } else {
            }
        }
        if (is_both_lead_follow_faraway) {
            if (has_no_lead_follow_scene) {
                continue;
            } else {
                has_no_lead_follow_scene = true;
            }
        }

        std::unordered_set<std::string> src_default_objects_id_set;
        for (const auto &traj : *st_planner_object_traj.extended_trajectories) {
            std::string obj_id =
                SpacetimeObjectTrajectory::GetObjectIdFromTrajectoryId(
                    traj.traj_id());
            if (obj_id.empty() || considered_objects_id_set.count(obj_id) ||
                src_default_objects_id_set.count(obj_id) ||
                !obstale_object_infos.count(obj_id)) {
                continue;
            }
            src_default_objects_id_set.insert(obj_id);
            std::vector<ObstaclePointInfo> modified_pred_default_traj =
                obstale_object_infos.at(obj_id);
            if (!modified_pred_default_traj.empty()) {
                if (modified_pred_default_traj[0].sl_boundary.s_min >
                    trusted_max_s) {
                    continue;
                }
                ObstacleDecision default_obs_decision;
                default_obs_decision.obj_id = obj_id;
                default_obs_decision.obs_moving_type =
                    traj.is_stationary() ? ObstacleMovingType::kStationary
                                         : ObstacleMovingType::kDynamic;
                default_obs_decision.decision_tag.lon_decision_tag =
                    OvertakeYieldType::kIgnore;
                default_obs_decision.decision_tag.lat_decision_tag =
                    NudgeDirection::kNoNudge;
                default_obs_decision.modified_pred_traj =
                    std::move(modified_pred_default_traj);
                default_obs_decision.has_modified_pred = false;
                decision_group.obstacles_decision[default_obs_decision.obj_id] =
                    std::move(default_obs_decision);
            }
        }

        constexpr double kCenterThreshold = 0.5;
        if (!is_lane_change && nullable_nearest_vru_obj_id.has_value()) {
            ObstacleDecisionGroup nearest_vru_decision_group = decision_group;
            auto it_source = decision_group.obstacles_decision.find(
                nullable_nearest_vru_obj_id.value());
            auto it_new = nearest_vru_decision_group.obstacles_decision.find(
                nullable_nearest_vru_obj_id.value());
            if (it_source != decision_group.obstacles_decision.end()) {
                const absl::StatusOr<pnc_x::FrenetBox> object_frenet_box =
                    drive_passage.QueryFrenetBoxAt(
                        st_planner_object_traj
                            .FindObjectByObjectId(
                                nullable_nearest_vru_obj_id.value())
                            ->bounding_box());
                if (object_frenet_box.ok() &&
                    (object_frenet_box.value().center_l() < -kCenterThreshold)) {
                    it_new->second.decision_tag.lat_decision_tag =
                        NudgeDirection::kNudgeLeft;
                    it_new->second.decision_tag.lon_decision_tag =
                        OvertakeYieldType::kOvertake;
                    decision_groups.emplace_back(
                        std::move(nearest_vru_decision_group));
                    it_source->second.decision_tag.lat_decision_tag =
                        NudgeDirection::kNoNudge;
                    it_source->second.decision_tag.lon_decision_tag =
                        OvertakeYieldType::kYield;
                } else if (object_frenet_box.ok() &&
                           (object_frenet_box.value().center_l() >
                               kCenterThreshold)) {
                    it_new->second.decision_tag.lat_decision_tag =
                        NudgeDirection::kNudgeRight;
                    it_new->second.decision_tag.lon_decision_tag =
                        OvertakeYieldType::kOvertake;
                    decision_groups.emplace_back(
                        std::move(nearest_vru_decision_group));
                    it_source->second.decision_tag.lat_decision_tag =
                        NudgeDirection::kNoNudge;
                    it_source->second.decision_tag.lon_decision_tag =
                        OvertakeYieldType::kYield;
                }
            } else {
                // VLOG(0) << "Error: cannot find vru object: "
                //         << nullable_nearest_vru_obj_id.value();
            }
        }
        decision_groups.emplace_back(std::move(decision_group));
    }
    if (decision_groups.empty()) {
        decision_groups.emplace_back();
        ObstacleDecisionGroup &decision_group = decision_groups.back();
        decision_group.traj_time_step = kTrajectoryTimeStep;
        std::unordered_set<std::string> src_default_objects_id_set;
        for (const auto &traj : *st_planner_object_traj.extended_trajectories) {
            std::string obj_id =
                SpacetimeObjectTrajectory::GetObjectIdFromTrajectoryId(
                    traj.traj_id());
            if (obj_id.empty() || src_default_objects_id_set.count(obj_id) ||
                !obstale_object_infos.count(obj_id)) {
                continue;
            }
            src_default_objects_id_set.insert(obj_id);
            std::vector<ObstaclePointInfo> modified_pred_traj =
                obstale_object_infos.at(obj_id);
            if (!modified_pred_traj.empty()) {
                if (modified_pred_traj[0].sl_boundary.s_min > trusted_max_s) {
                    continue;
                }
                ObstacleDecision obs_decision;
                obs_decision.obj_id = obj_id;
                obs_decision.obs_moving_type =
                    traj.is_stationary() ? ObstacleMovingType::kStationary
                                         : ObstacleMovingType::kDynamic;
                obs_decision.decision_tag.lon_decision_tag =
                    OvertakeYieldType::kIgnore;
                obs_decision.decision_tag.lat_decision_tag =
                    NudgeDirection::kNoNudge;
                obs_decision.modified_pred_traj = std::move(modified_pred_traj);
                obs_decision.has_modified_pred = false;
                decision_group.obstacles_decision[obs_decision.obj_id] =
                    std::move(obs_decision);
            }
        }
    }

    int i = 0;
    std::string decision_groups_info = " ";
    for (const auto &decision_group : decision_groups) {
        absl::StrAppend(&decision_groups_info, "group i: ", (i++), "\n");
        if (decision_group.obstacles_decision.empty()) {
            continue;
        }
        for (auto it = decision_group.obstacles_decision.begin();
             it != decision_group.obstacles_decision.end(); ++it) {
            absl::StrAppend(&decision_groups_info, "obj_ids: ", it->first,
                            "\n");
        }
        absl::StrAppend(
            &decision_groups_info, "lead id: ",
            decision_group.obs_goal_gap.lead_obj_id.value_or("null"), ", ",
            "tail id: ",
            decision_group.obs_goal_gap.tail_obj_id.value_or("null"), ", ",
            "ori lead id: ", decision_group.ori_lead_obj_id.value_or("null"),
            "\n--------------\n");
    }
    return decision_groups;
}

}  // namespace planning
}  // namespace pnc_x
