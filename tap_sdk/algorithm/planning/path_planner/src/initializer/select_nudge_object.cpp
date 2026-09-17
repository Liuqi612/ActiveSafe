

#include <algorithm>
#include <cmath>
#include <limits>

#include <string>
#include <utility>
#include <vector>

#include "initializer/select_nudge_object.h"
#include "math/frenet_common.h"
#include "math/util.h"
#include "object/spacetime_object_state.h"
#include "object/spacetime_object_trajectory.h"
#include "plan/trajectory_point.h"
#include "util/vehicle_geometry_util.h"
#include <absl/status/statusor.h>

namespace pnc_x {
namespace planning {

boost::optional<NudgeObjectInfo> NudgeInfos::findNudgeInfoById(
    const std::string &id) const {
    for (const auto &info : nudgeInfos) {
        if (info.id == id) {
            return info;
        }
    }
    return boost::none;
}

namespace initializer {

constexpr double kLOffsetThreshold = 0.1;
constexpr double kThetaThreshold = 0.08;
constexpr int kNudgeEffectiveIndexRange = 5;
constexpr double kMaxNudgeBuffer = 0.2;
constexpr int kNudgeEffectiveStartIndex = 5;
constexpr double kSRangeExtend = 0.0;
constexpr double kMaxNudgeLDiff = 3.5;
constexpr double kBorrowLOffsetThreshold = 0.75;

struct NudgeState {
    double l_min = std::numeric_limits<double>::infinity();
    double l_min_lon_s = std::numeric_limits<double>::infinity();
    const SpacetimeObjectTrajectory *min_dist_object_ptr = nullptr;

    void reset() {
        l_min = std::numeric_limits<double>::infinity();
        l_min_lon_s = std::numeric_limits<double>::infinity();
        min_dist_object_ptr = nullptr;
    }
};

absl::StatusOr<FrenetBox> QueryXY2SLMapByBox(const DrivePassage &drive_passage,
                                             const Box2d &box) {
    constexpr double kEpsilon = 1e-6;
    FrenetBox frenet_box;
    absl::StatusOr<FrenetBox> fbox = drive_passage.QueryFrenetBoxAt(box);
    if (fbox.ok()) {
        frenet_box = std::move(fbox.value());
        return frenet_box;
    }
    if ((frenet_box.s_max + kEpsilon) < frenet_box.s_min) {
        return absl::NotFoundError("Box has no overlap with drive passage.");
    }
    return frenet_box;
}

std::vector<SpacetimeObjectState> SampleObjectStates(
    int trajectory_steps,
    double trajectory_time_step,
    absl::Span<const SpacetimeObjectState> states) {
    XCHECK_GT(trajectory_steps, 0);
    XCHECK_GT(trajectory_time_step, 0.0);
    const int sample_step =
        static_cast<int>((trajectory_time_step / kTrajectoryTimeStep) + 0.5);
    std::vector<SpacetimeObjectState> sampled_states;
    sampled_states.reserve(states.size() / static_cast<size_t>(sample_step));
    for (int i = 0; i < trajectory_steps; ++i) {
        const size_t idx = static_cast<size_t>(i * sample_step);
        if (idx >= states.size()) break;
        sampled_states.push_back(states[idx]);
    }
    return sampled_states;
}

void ExtendObjectStatesBy(int trajectory_steps,
                          double trajectory_time_step,
                          std::vector<SpacetimeObjectState> *states) {
    if (states->empty() || (states->size() >= trajectory_steps)) {
        return;
    }
    XCHECK_GT(trajectory_steps, 0);
    XCHECK_GT(trajectory_time_step, 0.0);
    const int sample_step =
        static_cast<int>((trajectory_time_step / kTrajectoryTimeStep) + 0.5);
    const auto last_state = states->back();
    const int state_size = static_cast<int>(states->size());
    states->reserve(static_cast<size_t>(trajectory_steps));
    for (int i = state_size + 1; i < trajectory_steps; ++i) {
        if ((i * sample_step) >= trajectory_steps) break;
        states->emplace_back(last_state);
    }
}

bool IsIntervalEffective(double plan_start_point_theta_diff_to_lane,
                         int free_index,
                         int start_nudge_index,
                         int direction,
                         int end_nudge_index,
                         double l_nudge_max) {
    const bool in_loop_effective =
        (start_nudge_index < free_index) ||
        ((Sign(plan_start_point_theta_diff_to_lane) == static_cast<double>(direction)) &&
         (std::abs(plan_start_point_theta_diff_to_lane) > kThetaThreshold));

    return in_loop_effective &&
           ((end_nudge_index - start_nudge_index) > kNudgeEffectiveIndexRange) &&
           (std::abs(l_nudge_max) > kMaxNudgeBuffer);
}

void GetNudgeObjectIdForStep(
    double &l_min,
    const SpacetimeObjectTrajectory *&min_dist_object_ptr,
    double &l_min_lon_s,
    int direction,
    const FrenetBox &object_frenet_box,
    const FrenetBox &av_frenet_box,
    const SpacetimeObjectTrajectory *object_ptr) {
    int object_side = 0;
    if (av_frenet_box.l_min > object_frenet_box.l_max) {
        object_side = 1;
    } else if (object_frenet_box.l_min > av_frenet_box.l_max) {
        object_side = -1;
    }
    if (object_side == direction) {
        const bool has_s_overlap =
            (((object_frenet_box.s_min + kSRangeExtend) > av_frenet_box.s_min) &&
             ((object_frenet_box.s_min + kSRangeExtend) < av_frenet_box.s_max)) ||
            (((object_frenet_box.s_max + kSRangeExtend) > av_frenet_box.s_min) &&
             ((object_frenet_box.s_max + kSRangeExtend) < av_frenet_box.s_max));
        if (has_s_overlap) {
            double l_diff = 0.0;
            if (direction > 0) {
                l_diff = av_frenet_box.l_min - object_frenet_box.l_max;
            } else {
                l_diff = object_frenet_box.l_min - av_frenet_box.l_max;
            }
            if (l_diff < l_min) {
                l_min = l_diff;
                l_min_lon_s = object_frenet_box.center_s();
                min_dist_object_ptr = object_ptr;
            }
        }
    }
}

absl::StatusOr<NudgeInfos> SelectNudgeObjectId(
    int trajectory_steps,
    double trajectory_time_step,
    bool is_lane_change,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_sl_boundary,
    const std::vector<TrajectoryPoint> &result_points,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const VehicleGeometryParamsProto &vehicle_geometry_params,
    const int plan_id,
    std::string *nudge_debug) {
    XCHECK_GT(trajectory_steps, 0);
    XCHECK_GT(trajectory_time_step, 0.0);
    const int fixed_index = static_cast<int>(
        static_cast<double>(kTrajectoryStepsMinus1) * kTrajectoryTimeStep / trajectory_time_step);
    const int free_index = static_cast<int>(result_points.size());
    NudgeInfos nudge_object_infos;

    if (is_lane_change) return nudge_object_infos;

    const auto &plan_start_point = result_points.front();
    absl::StatusOr<pnc_x::FrenetCoordinate> plan_start_frenet_point;
    plan_start_frenet_point =
        drive_passage.QueryFrenetCoordinateAt(plan_start_point.pos());
    if (!plan_start_frenet_point.ok()) {
        return absl::OutOfRangeError(
            "Plan start point don't in drive passage range.");
    }
    const auto start_point_lane_theta =
        drive_passage.QueryTangentAngleAtS(plan_start_frenet_point->s);
    if (!start_point_lane_theta.ok()) {
        return absl::OutOfRangeError(
            "Plan start point s don't in drive passage range.");
    }
    const double plan_start_point_theta_diff_to_lane =
        NormalizeAngle(plan_start_point.theta() - *start_point_lane_theta);

    boost::optional<int> direction;
    boost::optional<double> l_nudge_max;
    boost::optional<int> start_nudge_index;
    boost::optional<int> end_nudge_index;

    for (int k = 0; k < free_index; ++k) {
        const auto &traj_point = result_points[static_cast<size_t>(k)];

        absl::StatusOr<pnc_x::FrenetCoordinate> frenet_pt;
        frenet_pt = drive_passage.QueryFrenetCoordinateAt(traj_point.pos());
        if (!frenet_pt.ok()) {
            return absl::OutOfRangeError(absl::StrFormat(
                "%d traj point out of drive passage range.", k));
        }
        const double center_l_at_s =
            path_sl_boundary.QueryReferenceCenterL(frenet_pt->s);
        const double l_offset = frenet_pt->l - center_l_at_s;
        if (!start_nudge_index.has_value() &&
            (std::abs(l_offset) > kLOffsetThreshold)) {
            start_nudge_index = k;
            *nudge_debug +=
                "START INDEX: " + std::to_string(start_nudge_index.value()) +
                "\n";
        }
        if (start_nudge_index.has_value()) {
            if (!l_nudge_max.has_value()) {
                l_nudge_max = l_offset;
                direction = Sign(l_offset);
            } else {
                if (Sign(l_offset) == static_cast<double>(*direction)) {
                    if (*direction > 0) {
                        l_nudge_max = std::max(*l_nudge_max, l_offset);
                    } else {
                        l_nudge_max = std::min(*l_nudge_max, l_offset);
                    }
                }
            }
        }
        const bool l_offset_noneffective =
            !direction.has_value() ||
            ((*direction > 0) ? (l_offset <= kLOffsetThreshold)
                              : (l_offset >= -kLOffsetThreshold)) ||
            (k == (free_index - 1));
        if (l_nudge_max.has_value() && !end_nudge_index.has_value() &&
            l_offset_noneffective) {
            end_nudge_index = k - 1;
            *nudge_debug +=
                "direction: " + std::to_string(*direction) +
                ", l_nudge_max: " + std::to_string(l_nudge_max.value()) + "\n";
            *nudge_debug +=
                "END INDEX: " + std::to_string(end_nudge_index.value()) + "\n";
            bool is_interval_effective = IsIntervalEffective(
                plan_start_point_theta_diff_to_lane, free_index,
                *start_nudge_index, *direction, *end_nudge_index, *l_nudge_max);
            *nudge_debug +=
                "interval effective: " + std::to_string(is_interval_effective) +
                "\n";
            if ((*end_nudge_index > kNudgeEffectiveStartIndex) &&
                is_interval_effective) {
                NudgeState nudgeState;
                std::vector<FrenetBox> av_sl_boxes;

                av_sl_boxes.reserve(static_cast<size_t>(free_index));
                for (int k = 0; k < free_index; ++k) {
                    const auto &traj_point = result_points[static_cast<size_t>(k)];
                    const auto box =
                        ComputeAvBox(traj_point.pos(), traj_point.theta(),
                                     vehicle_geometry_params);

                    absl::StatusOr<pnc_x::FrenetBox> frenet_box;
                    frenet_box = drive_passage.QueryFrenetBoxAt(box);
                    if (!frenet_box.ok()) {
                        return absl::OutOfRangeError(absl::StrFormat(
                            "%d traj point box out of drive passage range.",
                            k));
                    }
                    av_sl_boxes.push_back(*frenet_box);
                }
                const auto &spacetime_trajs =
                    *st_planner_object_traj.extended_trajectories;
                const int num_trajs = static_cast<int>(spacetime_trajs.size());

                for (int i = 0; i < num_trajs; ++i) {
                    const auto &traj = spacetime_trajs[static_cast<size_t>(i)];
                    *nudge_debug +=
                        "obj id: " + std::string(traj.object_id()) + "\n";
                    auto states = SampleObjectStates(
                        trajectory_steps, trajectory_time_step, traj.states());
                    ExtendObjectStatesBy(trajectory_steps, trajectory_time_step,
                                         &states);
                    boost::optional<FrenetBox> stationary_object_frenet_box;
                    if (traj.is_stationary()) {
                        absl::StatusOr<pnc_x::FrenetBox> frenet_box_or;
                        frenet_box_or = drive_passage.QueryFrenetBoxAt(
                            traj.bounding_box(), false);
                        if (!frenet_box_or.ok()) {
                            break;
                        }
                        stationary_object_frenet_box = *frenet_box_or;
                    }
                    for (int k = *start_nudge_index;
                         (k < *end_nudge_index) && (k < states.size()) &&
                         (k < free_index);
                         ++k) {
                        if (stationary_object_frenet_box.has_value()) {
                            GetNudgeObjectIdForStep(
                                nudgeState.l_min,
                                nudgeState.min_dist_object_ptr,
                                nudgeState.l_min_lon_s, *direction,
                                *stationary_object_frenet_box, av_sl_boxes[static_cast<size_t>(k)],
                                &traj);
                            if (k == *start_nudge_index) {
                                *nudge_debug +=
                                    "start s max: ego: " +
                                    std::to_string(av_sl_boxes[static_cast<size_t>(k)].s_min) +
                                    ", obj: " +
                                    std::to_string(
                                        stationary_object_frenet_box->s_min) +
                                    "\n";
                            }
                            if (k ==
                                std::min(*end_nudge_index - 1,
                                         static_cast<int>(states.size()) - 1)) {
                                *nudge_debug +=
                                    "end s max: ego: " +
                                    std::to_string(av_sl_boxes[static_cast<size_t>(k)].s_max) +
                                    ", obj: " +
                                    std::to_string(
                                        stationary_object_frenet_box->s_max) +
                                    "\n";
                            }
                        } else {
                            const auto &state = states[static_cast<size_t>(k)];

                            absl::StatusOr<pnc_x::FrenetBox> frenet_box_or;
                            frenet_box_or = drive_passage.QueryFrenetBoxAt(
                                state.box, false);
                            if (!frenet_box_or.ok()) {
                                break;
                            }
                            if (k == *start_nudge_index) {
                                *nudge_debug +=
                                    "start s max: ego: " +
                                    std::to_string(av_sl_boxes[static_cast<size_t>(k)].s_max) +
                                    ", obj: " +
                                    std::to_string(frenet_box_or->s_max) + "\n";
                            }
                            if (k ==
                                std::min(*end_nudge_index - 1,
                                         static_cast<int>(states.size()) - 1)) {
                                *nudge_debug +=
                                    "end s max: ego: " +
                                    std::to_string(av_sl_boxes[static_cast<size_t>(k)].s_max) +
                                    ", obj: " +
                                    std::to_string(frenet_box_or->s_max) + "\n";
                            }
                            GetNudgeObjectIdForStep(
                                nudgeState.l_min,
                                nudgeState.min_dist_object_ptr,
                                nudgeState.l_min_lon_s, *direction,
                                *frenet_box_or, av_sl_boxes[static_cast<size_t>(k)], &traj);
                        }
                    }
                    const double trajectory_max_dis =
                        result_points.back().s() +
                        vehicle_geometry_params.front_edge_to_center();
                    *nudge_debug +=
                        "l_min: " + std::to_string(nudgeState.l_min) +
                        ", s at l_min: " +
                        std::to_string(nudgeState.l_min_lon_s) + "\n";
                    if ((nudgeState.l_min < kMaxNudgeLDiff) &&
                        l_nudge_max.has_value() &&
                        (nudgeState.l_min_lon_s < trajectory_max_dis)) {
                        NudgeObjectInfo nudge_object_info;
                        nudge_object_info.id = std::string(
                            nudgeState.min_dist_object_ptr->object_id());
                        nudge_object_info.direction = *direction;

                        absl::StatusOr<pnc_x::FrenetBox> object_frenet_box;
                        object_frenet_box = drive_passage.QueryFrenetBoxAt(
                            nudgeState.min_dist_object_ptr->bounding_box());
                        if (!object_frenet_box.ok()) {
                            return absl::OutOfRangeError(
                                "Object is not on drive passage.");
                        }
                        nudge_object_info.arc_dist_to_object =
                            std::max(0.0, object_frenet_box->s_min -
                                              av_sl_boxes.front().s_max);
                        nudge_object_info.type =
                            nudgeState.min_dist_object_ptr->object_type();
                        nudge_object_info.nudge_state =
                            NudgeObjectInfo::NudgeState::NUDGE;
                        if (std::fabs(l_nudge_max.value()) >
                            kBorrowLOffsetThreshold) {
                            nudge_object_info.nudge_state =
                                NudgeObjectInfo::NudgeState::BORROW;
                        }
                        nudge_object_infos.addNudgeInfo(
                            std::move(nudge_object_info));
                        nudgeState.reset();
                    }
                }
            }
            direction.reset();
            l_nudge_max.reset();
            start_nudge_index.reset();
            end_nudge_index.reset();
        }
    }
    return nudge_object_infos;
}
}  // namespace initializer
}  // namespace planning
}  // namespace pnc_x
