

#include "object/spacetime_planner_object_trajectories_filter.h"

#include <algorithm>
#include <ostream>
#include <string_view>
#include <utility>
#include <vector>

#include "math/linear_interpolation.h"
#include "math/piecewise_linear_function.h"
#include "math/util.h"
#include "object/spacetime_object_state.h"
#include "pncx_perception.pb.h"
#include "plan/planner_util.h"
#include "plan/second_order_trajectory_point.h"
#include "prediction/predicted_trajectory.h"
#include <absl/status/statusor.h>
#include <absl/types/span.h>
#include "common/log.h"

namespace pnc_x {
namespace planning {
namespace {

bool IsMaybeCutInVehicleTrajectory(
    const DrivePassage &drive_passage,
    const LaneChangeStateProto &lane_change_state,
    const Box2d &av_box,
    const FrenetBox &av_sl_box,
    double av_speed,
    const SpacetimeObjectTrajectory &traj) {
    if (lane_change_state.stage() != LCS_NONE) {
        return false;
    }
    if ((traj.object_type() != ObjectType::OT_VEHICLE) &&
        (traj.object_type() != ObjectType::OT_LARGE_VEHICLE)) {
        return false;
    }

    constexpr double kObjectDistThreshold = 0.8;
    const auto &object_box = traj.bounding_box();
    const double dist_to_av_box = object_box.DistanceTo(av_box);

    const auto &object_frenet_box = drive_passage.QueryFrenetBoxAt(object_box);
    if (!object_frenet_box.ok()) {
        return false;
    }
    const auto &states = traj.states();
    const auto &object_start_pt = *states.front().traj_point;
    const auto current_object_sl_pt =
        drive_passage.QueryLaterallyUnboundedFrenetCoordinateAt(
            object_start_pt.pos());
    if (!current_object_sl_pt.ok()) {
        // VLOG(2) << traj.traj_id()
        //         << " current pose not in drive_passage, skip evaluation.";
        return false;
    }
    const auto current_lane_heading =
        drive_passage.QueryTangentAngleAtS(current_object_sl_pt->s);
    if (!current_lane_heading.ok()) {
        // VLOG(2) << traj.traj_id() << " current lane heading query failed.";
        return false;
    }

    constexpr double kLargeLatSpeed = 0.3;
    const double object_lat_speed =
        object_start_pt.v() *
        fast_math::Sin(object_start_pt.theta() - *current_lane_heading);
    const bool lat_speed_large = current_object_sl_pt->l > 0.0
                                     ? object_lat_speed < -kLargeLatSpeed
                                     : object_lat_speed > kLargeLatSpeed;

    constexpr double kObjectSExtent = 2.0;
    const bool cur_lon_overlapped =
        (av_sl_box.s_max > (object_frenet_box->s_min - kObjectSExtent) &&
         av_sl_box.s_max < (object_frenet_box->s_max + kObjectSExtent)) ||
        (av_sl_box.s_min > (object_frenet_box->s_min - kObjectSExtent) &&
         av_sl_box.s_min < (object_frenet_box->s_max + kObjectSExtent));

    const double toward_center_theta_diff =
        current_object_sl_pt->l > 0.0
            ? NormalizeAngle((*current_lane_heading) - traj.pose().theta())
            : NormalizeAngle(traj.pose().theta() - (*current_lane_heading));
    constexpr double kCutInThetaThreshold = 0.05;

    const auto current_lane_boundary_offset =
        drive_passage.QueryNearestBoundaryLateralOffset(
            current_object_sl_pt->s);
    if (!current_lane_boundary_offset.ok()) {
        // VLOG(2) << traj.traj_id() << " current lateral boundary query failed.";
        return false;
    }
    if (current_object_sl_pt->l < current_lane_boundary_offset->second &&
        current_object_sl_pt->l > current_lane_boundary_offset->first) {
        // VLOG(2) << traj.traj_id() << " object in lane.";
        return false;
    }

    double filter_s_thr =
        traj.object_type() == ObjectType::OT_LARGE_VEHICLE ? 2.0 : 0.0;

    bool is_filter = traj.object_type() == ObjectType::OT_LARGE_VEHICLE
                         ? (av_sl_box.center_s() > object_frenet_box->s_max)
                         : (av_sl_box.s_max > object_frenet_box->s_max);

    if (is_filter && toward_center_theta_diff < kCutInThetaThreshold &&
        av_speed > object_start_pt.v() + 1.0) {
        return true;
    }

    if (dist_to_av_box < kObjectDistThreshold) {
        // VLOG(2) << traj.traj_id() << " dist to close " << dist_to_av_box
        //         << "m.";
        return false;
    }

    if (lat_speed_large && cur_lon_overlapped &&
        (dist_to_av_box < kObjectSExtent)) {
        // VLOG(2) << traj.traj_id() << " may be immoral.";
        return false;
    }

    const auto final_object_sl_pt =
        drive_passage.QueryLaterallyUnboundedFrenetCoordinateAt(
            states.back().traj_point->pos());

    if (!final_object_sl_pt.ok()) {
        // VLOG(2) << traj.traj_id()
        //         << " final pose not in drive_passage, skip evaluation.";
        return false;
    }

    const auto final_lane_boundary_offset =
        drive_passage.QueryNearestBoundaryLateralOffset(final_object_sl_pt->s);
    if (!final_lane_boundary_offset.ok()) {
        // VLOG(2) << traj.traj_id() << " fianl lateral boundary query failed.";
        return false;
    }

    constexpr double kCenterOffsetThreshold = 0.8;
    bool is_traj_slope_to_center = false;

    if (current_object_sl_pt->l < current_lane_boundary_offset->first) {
        is_traj_slope_to_center =
            final_object_sl_pt->l > current_lane_boundary_offset->first &&
            final_object_sl_pt->l > current_object_sl_pt->l;
    } else if (current_object_sl_pt->l > current_lane_boundary_offset->second) {
        is_traj_slope_to_center =
            final_object_sl_pt->l < current_lane_boundary_offset->second &&
            final_object_sl_pt->l < current_object_sl_pt->l;
    }
    if (is_traj_slope_to_center) {
        if (toward_center_theta_diff > kCutInThetaThreshold) {
            return true;
        }

        const double toward_center_offset =
            current_object_sl_pt->l > 0.0
                ? current_object_sl_pt->l - final_object_sl_pt->l
                : final_object_sl_pt->l - current_object_sl_pt->l;
        // VLOG(3) << traj.traj_id()
        //         << " toward_center_offset: " << toward_center_offset << " "
        //         << toward_center_theta_diff;
        constexpr double kMaybeCutInThetaThreshold = 0.01;

        if ((toward_center_offset > kCenterOffsetThreshold) &&
            (toward_center_theta_diff > kMaybeCutInThetaThreshold)) {
            // VLOG(2) << traj.traj_id() << " prediction toward center offset "
            //         << toward_center_offset << "m > " << kCenterOffsetThreshold
            //         << "m, toward center theta diff is "
            //         << kMaybeCutInThetaThreshold
            //         << "rad, maybe cutin traj, refuse to nudge.";
            return true;
        }
    }

    return false;
}

bool IsVru(const SpacetimeObjectTrajectory &traj) {
    return (traj.object_type() == ObjectType::OT_MOTORCYCLIST) ||
           (traj.object_type() == ObjectType::OT_CYCLIST) ||
           (traj.object_type() == ObjectType::OT_TRICYCLIST) ||
           (traj.object_type() == ObjectType::OT_PEDESTRIAN);
}

bool IsCrossingTrajectory(const DrivePassage &drive_passage,
                          const SpacetimeObjectTrajectory &traj) {
    return true;
}

bool IsTrajectoryBeyondStopLine(const DrivePassage &drive_passage,
                                double first_stop_line_s,
                                const SpacetimeObjectTrajectory &traj) {
    if (std::isinf(first_stop_line_s)) {
        return false;
    }
    if (traj.is_stationary()) {
        const auto frenet_box =
            drive_passage.QueryFrenetBoxAt(traj.bounding_box());
        if (!frenet_box.ok()) {
            return false;
        }
        if (frenet_box->s_min < first_stop_line_s) {
            return false;
        }
    } else {
        const auto &states = traj.states();
        for (const auto &state : states) {
            const auto frenet_box = drive_passage.QueryFrenetBoxAt(state.box);
            if (!frenet_box.ok()) {
                continue;
            }
            if (frenet_box->s_min < first_stop_line_s) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace

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

    const double obj_speed = traj.pose().v();
    if ((av_speed - obj_speed) < 1.5) {
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
    const bool obs_reverse_flag =
        std::abs(NormalizeAngle((*lane_theta_at_pose) + M_PI -
                                traj.states().front().traj_point->theta())) <
        M_PI / 3.0;
    if (obs_reverse_flag) {
        return false;
    }

    const double kObjectDistThreshold = 0.8;
    const double kBrakeAcc = 3.0;
    const double min_brake_dist =
        (av_speed - obj_speed) * (av_speed - obj_speed) / (kBrakeAcc * 2.0);
    const auto &object_box = traj.bounding_box();
    const auto &obj_frenet_box = drive_passage.QueryFrenetBoxAt(object_box);
    if (!obj_frenet_box.ok()) {
        return false;
    }
    if (obj_frenet_box->s_min - av_sl_box.s_max <
        std::fmax(kObjectDistThreshold, min_brake_dist)) {
        return false;
    }

    const auto &object_frenet_box = drive_passage.QueryFrenetBoxAt(object_box);
    if (!object_frenet_box.ok()) {
        return false;
    }

    const double center_range = 1.5;
    if (object_frenet_box->l_min >
            0.6 * ads_x::planning::Constants::DEFAULT_LANE_WIDTH ||
        object_frenet_box->l_max <
            -0.6 * ads_x::planning::Constants::DEFAULT_LANE_WIDTH ||
        std::fabs(object_frenet_box->center_l()) < center_range) {
        return false;
    }

    const double cutin_l_threshold = 1.0;
    const double delta_l_threshold = 0.2;
    double prev_l = object_frenet_box->l_min > ads_x::planning::Constants::ZERO
                        ? object_frenet_box->l_min
                        : object_frenet_box->l_max;
    for (const auto &obj_state : traj.states()) {
        const auto pred_box = drive_passage.QueryFrenetBoxAt(obj_state.box);
        if (!pred_box.ok()) {
            break;
        }
        if (object_frenet_box->center_l() > ads_x::planning::Constants::ZERO) {
            if (pred_box->l_min < cutin_l_threshold &&
                object_frenet_box->l_min - pred_box->l_min >
                    delta_l_threshold) {
                return true;
            }
            prev_l = pred_box->l_min;
        } else if (object_frenet_box->center_l() <
                   -ads_x::planning::Constants::ZERO) {
            if (pred_box->l_max > -cutin_l_threshold &&
                pred_box->l_max - object_frenet_box->l_max >
                    delta_l_threshold) {
                return true;
            }
            prev_l = pred_box->l_max;
        }
    }

    return false;
}

CutInSpacetimePlannerObjectTrajectoriesFilter::
    CutInSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage,
        const LaneChangeStateProto *lane_change_state,
        const Box2d &av_box,
        double av_speed)
    : drive_passage_(drive_passage),
      lane_change_state_(lane_change_state),
      av_box_(av_box),
      av_speed_(av_speed) {
    const auto av_sl_box_or = drive_passage_->QueryFrenetBoxAt(av_box_);
    if (av_sl_box_or.ok()) {
        av_sl_box_ = *av_sl_box_or;
    }
}

bool CutInSpacetimePlannerObjectTrajectoriesFilter::Filter(
    const SpacetimeObjectTrajectory &traj) const {
    if (!av_sl_box_.has_value()) {
        // VLOG(2) << "AV box can't be mapped on drive passage, skip.";
        return false;
    }
    const bool is_lane_change =
        (((*lane_change_state_).stage() == LaneChangeStage::LCS_EXECUTING) ||
         ((*lane_change_state_).stage() == LaneChangeStage::LCS_RETURN) ||
         ((*lane_change_state_).stage() == LaneChangeStage::LCS_PAUSE));
    return IsCutInObjectTrajectory(*drive_passage_, is_lane_change, av_speed_,
                                   *av_sl_box_, traj);
}

CutInVehicleSpacetimePlannerObjectTrajectoriesFilter::
    CutInVehicleSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage,
        const LaneChangeStateProto *lane_change_state,
        const Box2d &av_box,
        double av_speed)
    : drive_passage_(drive_passage),
      lane_change_state_(lane_change_state),
      av_box_(av_box),
      av_speed_(av_speed) {
    const auto av_sl_box_or = drive_passage_->QueryFrenetBoxAt(av_box_);
    if (av_sl_box_or.ok()) {
        av_sl_box_ = *av_sl_box_or;
    }
}

bool CutInVehicleSpacetimePlannerObjectTrajectoriesFilter::Filter(
    const SpacetimeObjectTrajectory &traj) const {
    if (!av_sl_box_.has_value()) {
        // VLOG(2) << "AV box can't be mapped on drive passage, skip.";
        return false;
    }
    return IsMaybeCutInVehicleTrajectory(*drive_passage_, *lane_change_state_,
                                         av_box_, *av_sl_box_, av_speed_, traj);
}

CrossingSpacetimePlannerObjectTrajectoriesFilter::
    CrossingSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage)
    : drive_passage_(drive_passage) {}

bool CrossingSpacetimePlannerObjectTrajectoriesFilter::Filter(
    const SpacetimeObjectTrajectory &traj) const {
    if (IsCrossingTrajectory(*drive_passage_, traj)) {
        return true;
    }
    return false;
}

BeyondStopLineSpacetimePlannerObjectTrajectoriesFilter::
    BeyondStopLineSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage,
        absl::Span<const ConstraintProto::StopLineProto> stop_lines)
    : drive_passage_(drive_passage) {
    for (const auto &stop_line : stop_lines) {
        first_stop_line_s_ =
            std::min(first_stop_line_s_, stop_line.s() - stop_line.standoff());
    }
}

bool BeyondStopLineSpacetimePlannerObjectTrajectoriesFilter::Filter(
    const SpacetimeObjectTrajectory &traj) const {
    return IsTrajectoryBeyondStopLine(*drive_passage_, first_stop_line_s_,
                                      traj);
}

ReverseVehicleSpacetimePlannerObjectTrajectoriesFilter::
    ReverseVehicleSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage,
        const VehicleGeometryParamsProto *vehicle_geometry_params,
        const PathSlBoundary *sl_boundary,
        const NudgeObjectInfo *nudge_object_info,
        Box2d av_box,
        double av_speed)
    : drive_passage_(drive_passage),
      vehicle_geometry_params_(vehicle_geometry_params),
      sl_boundary_(sl_boundary),
      nudge_object_info_(nudge_object_info),
      av_box_(std::move(av_box)),
      av_speed_(av_speed) {}

bool ReverseVehicleSpacetimePlannerObjectTrajectoriesFilter::Filter(
    const SpacetimeObjectTrajectory &traj) const {
    return true;
}

DecisionSpacetimePlannerObjectTrajectoriesFilter::
    DecisionSpacetimePlannerObjectTrajectoriesFilter(
        const DrivePassage *drive_passage,
        const SpacetimePlannerObjectTrajectoriesProto *prev_st_trajs,
        const VehicleGeometryParamsProto *vehicle_geometry_params,
        Box2d av_box,
        double av_speed)
    : drive_passage_(drive_passage),
      av_box_(av_box),
      av_speed_(av_speed),
      veh_geo_(vehicle_geometry_params) {
    const auto av_sl_box_or = drive_passage_->QueryFrenetBoxAt(av_box_);
    if (av_sl_box_or.ok()) {
        av_sl_box_ = *av_sl_box_or;
    }
    for (const auto &st_traj_proto : prev_st_trajs->trajectory()) {
        prev_st_planner_obj_id_.insert(st_traj_proto.id());
    }
}

bool DecisionSpacetimePlannerObjectTrajectoriesFilter::Filter(
    const SpacetimeObjectTrajectory &traj) const {
    return true;
}

}  // namespace planning
}  // namespace pnc_x
