#include <algorithm>
#include <cmath>

#include <string>
#include <utility>
#include <vector>

#include "initializer/interactive_search/decision_extractor/object_decision.h"
#include "math/frenet_common.h"
#include "math/util.h"
#include "object/spacetime_object_trajectory.h"
#include "plan/trajectory_point.h"
#include "util/status_macros.h"
#include "util/vehicle_geometry_util.h"
#include <absl/status/statusor.h>

namespace pnc_x {
namespace planning {

absl::StatusOr<ObjectDecisions> ParseObjectDecisions(
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const NudgeInfos &nudge_infos,
    const ObjectLongDecision &long_decisons,
    const boost::optional<std::string> &leader_id,
    const boost::optional<std::string> &follower_id) {
    ObjectDecisions object_decisions;
    const auto &obj_trajs = *st_planner_object_traj.extended_trajectories;
    for (const auto &obj_traj : obj_trajs) {
        NudgeDirection lat_decision_tag = NudgeDirection::kNoNudge;
        OvertakeYieldType lon_decision_tag = OvertakeYieldType::kIgnore;
        const auto &nudge_info_out =
            nudge_infos.findNudgeInfoById(std::string(obj_traj.object_id()));
        if (nudge_info_out.has_value()) {
            if (nudge_info_out.value().direction == 1) {
                if (nudge_info_out.value().nudge_state ==
                    NudgeObjectInfo::NudgeState::NUDGE) {
                    lat_decision_tag = NudgeDirection::kNudgeLeft;
                } else {
                    lat_decision_tag = NudgeDirection::kBorrowLeft;
                }
            } else {
                if (nudge_info_out.value().nudge_state ==
                    NudgeObjectInfo::NudgeState::NUDGE) {
                    lat_decision_tag = NudgeDirection::kNudgeRight;
                } else {
                    lat_decision_tag = NudgeDirection::kBorrowRight;
                }
            }
        }
        if (leader_id.has_value() &&
            leader_id.value() == obj_traj.object_id()) {
            lon_decision_tag = OvertakeYieldType::kYield;
        } else if (follower_id.has_value() &&
                   follower_id.value() == obj_traj.object_id()) {
            lon_decision_tag = OvertakeYieldType::kOvertake;
        } else {
            auto iter = long_decisons.find(std::string(obj_traj.object_id()));
            if (iter != long_decisons.end()) {
                lon_decision_tag = iter->second;
            }
        }

        ObstacleDecisionTag tag{lat_decision_tag, lon_decision_tag};
        ObstacleDecision decision{std::string(obj_traj.object_id()), tag};
        object_decisions[std::string(obj_traj.object_id())] = decision;
    }
    return object_decisions;
}

absl::StatusOr<ObjectLongDecision> ParseObjectLongDecisions(
    bool is_lane_change,
    const DrivePassage &drive_passage,
    const std::vector<TrajectoryPoint> &result_points,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const VehicleGeometryParamsProto &vehicle_geometry_params) {
    ObjectLongDecision long_decision;
    if (is_lane_change) return long_decision;

    const auto &ego_start_box =
        ComputeAvBox(result_points.front().pos(), result_points.front().theta(),
                     vehicle_geometry_params);
    const auto &ego_end_box =
        ComputeAvBox(result_points.back().pos(), result_points.back().theta(),
                     vehicle_geometry_params);
    ASSIGN_OR_RETURN(const auto ego_start_sl_box,
                     drive_passage.QueryFrenetBoxAt(ego_start_box),
                     long_decision);
    ASSIGN_OR_RETURN(const auto ego_end_sl_box,
                     drive_passage.QueryFrenetBoxAt(ego_end_box),
                     long_decision);

    const auto &spacetime_trajs =
        *st_planner_object_traj.extended_trajectories;
    const int num_trajs = static_cast<int>(spacetime_trajs.size());
    for (int i = 0; i < num_trajs; ++i) {
        const auto &traj = spacetime_trajs[i];
        boost::optional<FrenetBox> obj_start_sl_box_or;
        boost::optional<FrenetBox> obj_end_sl_box_or;
        if (traj.is_stationary()) {
            const auto &frenet_box_or =
                drive_passage.QueryFrenetBoxAtContour(traj.contour(), false);
            if (!frenet_box_or.ok()) {
                break;
            }
            obj_start_sl_box_or = *frenet_box_or;
            obj_end_sl_box_or = *frenet_box_or;
        } else {
            const auto &start_frenet_box_or =
                drive_passage.QueryFrenetBoxAtContour(
                    traj.states().front().contour, false);

            const int end_index =
                std::fmin(result_points.size(), traj.states().size()) - 1;
            const auto &end_frenet_box_or =
                drive_passage.QueryFrenetBoxAtContour(
                    traj.states()[end_index].contour, false);
            if (!start_frenet_box_or.ok() || !end_frenet_box_or.ok()) {
                break;
            }
            obj_start_sl_box_or = *start_frenet_box_or;
            obj_end_sl_box_or = *end_frenet_box_or;
        }
        const bool ego_is_front_start =
            ego_start_sl_box.s_min > obj_start_sl_box_or->s_max;
        const bool ego_is_front_end =
            ego_end_sl_box.s_min > obj_end_sl_box_or->s_max;

        if ((ego_is_front_start && ego_is_front_end)) {
            long_decision[std::string(traj.object_id())] =
                OvertakeYieldType::kIgnore;
        } else if ((ego_is_front_start && !ego_is_front_end)) {
            long_decision[std::string(traj.object_id())] =
                OvertakeYieldType::kYield;
        } else if ((!ego_is_front_start && ego_is_front_end)) {
            long_decision[std::string(traj.object_id())] =
                OvertakeYieldType::kOvertake;
        } else {
            long_decision[std::string(traj.object_id())] =
                OvertakeYieldType::kYield;
        }
    }
    return long_decision;
}

ObjectDecisions StabilizeObjectDecisions(
    const ObjectDecisions *pre_object_decisions,
    const ObjectDecisions &object_decisions) {
    if (pre_object_decisions == nullptr) {
        return object_decisions;
    }

    ObjectDecisions res_decisions;

    constexpr int kMaxTagCounter = 10;
    constexpr int kStabilizeTagCounter = 3;
    for (const auto &decision : object_decisions) {
        auto pre_it = pre_object_decisions->find(decision.first);
        if (pre_it == object_decisions.end()) {
            res_decisions[decision.first] = decision.second;
            res_decisions[decision.first].decision_tag.counter = 1;
            continue;
        }
        if (pre_it->second.decision_tag == decision.second.decision_tag) {
            res_decisions[decision.first] = decision.second;
            res_decisions[decision.first].decision_tag.counter = std::min(
                pre_it->second.decision_tag.counter + 1, kMaxTagCounter);
            continue;
        }

        if (pre_it->second.decision_tag.counter < kStabilizeTagCounter) {
            res_decisions[decision.first] = pre_it->second;
            res_decisions[decision.first].decision_tag.counter = std::min(
                pre_it->second.decision_tag.counter + 1, kMaxTagCounter);
        } else {
            res_decisions[decision.first] = decision.second;
            res_decisions[decision.first].decision_tag.counter = 1;
        }
    }
    return res_decisions;
}

ObjectDecisions ExtractObjectDecisions(
    const std::vector<ApolloTrajectoryPointProto> &traj_result,
    bool is_lane_change,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_sl_boundary,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const VehicleGeometryParamsProto &vehicle_geometry_params,
    const std::string &prefix,
    const int plan_id,
    NudgeInfos *nudge_info,
    const ObsDecisionGap &best_gap_result,
    const ObjectDecisions *pre_object_decisions) {
    ObjectLongDecision lon_decision_info;
    ObjectDecisions object_decisions;
    std::vector<TrajectoryPoint> init_traj_points;
    TrajectoryPoint traj_point;

    for (const auto &point : traj_result) {
        traj_point.FromProto(point);
        init_traj_points.emplace_back(traj_point);
    }

    std::string nudge_debug = "";
    const auto nudge_object_infos = initializer::SelectNudgeObjectId(
        static_cast<int>(init_traj_points.size()), kTrajectoryTimeStep, is_lane_change,
        drive_passage, path_sl_boundary, init_traj_points,
        st_planner_object_traj, vehicle_geometry_params, plan_id, &nudge_debug);

    if (nudge_object_infos.ok()) {
        *nudge_info = nudge_object_infos.value();
    }

    const auto objects_long_decision_out_or = ParseObjectLongDecisions(
        is_lane_change, drive_passage, init_traj_points, st_planner_object_traj,
        vehicle_geometry_params);

    if (objects_long_decision_out_or.ok()) {
        lon_decision_info = objects_long_decision_out_or.value();
    }

    const auto object_decison_out_or = ParseObjectDecisions(
        st_planner_object_traj, *nudge_info, lon_decision_info,
        best_gap_result.lead_obj_id, best_gap_result.tail_obj_id);

    if (object_decison_out_or.ok()) {
        object_decisions = object_decison_out_or.value();
    }

    auto stabilized_out =
        StabilizeObjectDecisions(pre_object_decisions, object_decisions);
    std::string decision_infos;
    decision_infos.reserve(stabilized_out.size());
    for (const auto &decision : stabilized_out) {
        const auto &tag = decision.second.decision_tag;
        absl::StrAppend(&decision_infos, "id: ", decision.first,
                        ", lat tag: ", static_cast<int>(tag.lat_decision_tag),
                        ", lon tag: ", static_cast<int>(tag.lon_decision_tag),
                        "\n");
    }
    return stabilized_out;
}

}  // namespace planning
}  // namespace pnc_x
