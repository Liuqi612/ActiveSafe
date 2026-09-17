

#include "plan/planner_util.h"

#include <algorithm>
#include <boost/algorithm/clamp.hpp>
#include <cmath>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "container/strong_int.h"

#include "pncx_affine_transformation.pb.h"
#include "maps/semantic_map_defs.h"
#include "math/frenet_common.h"
#include "math/geometry/polygon2d.h"
#include "math/geometry/util.h"
#include "math/util.h"
#include "math/vec.h"
#include "plan/discretized_path.h"
#include "plan/planner_defs.h"
#include "util/file_util.h"
#include "util/time_util.h"

namespace pnc_x {
namespace planning {

namespace {

void UpdateToMinSpeedLimit(std::map<mapping::ElementId, double> *map,
                           mapping::ElementId lane_id,
                           double speed_limit) {
    auto pair_it = map->insert({lane_id, speed_limit});
    if (pair_it.second == false) {
        pair_it.first->second = std::min(pair_it.first->second, speed_limit);
    }
}

}  // namespace

double ComputeLongitudinalJerk(const TrajectoryPoint &traj_point) {
    return traj_point.j() - (Cube(traj_point.v()) * Sqr(traj_point.kappa()));
}

double ComputeLateralAcceleration(const TrajectoryPoint &traj_point) {
    return Sqr(traj_point.v()) * traj_point.kappa();
}

double ComputeLateralJerk(const TrajectoryPoint &traj_point) {
    return (3.0 * traj_point.v() * traj_point.a() * traj_point.kappa()) +
           (Sqr(traj_point.v()) * traj_point.psi());
}

bool IsVulnerableRoadUserType(ObjectType type) {
    return (type == OT_PEDESTRIAN) || (type == OT_CYCLIST) ||
           (type == OT_TRICYCLIST) || (type == OT_MOTORCYCLIST);
}

bool IsStaticObjectType(ObjectType type) {
    return (type == OT_UNKNOWN_STATIC) || (type == OT_VEGETATION) ||
           (type == OT_FOD) || (type == OT_BARRIER) || (type == OT_CONE);
}

std::vector<ApolloTrajectoryPointProto> CreatePastPointsList(
    absl::Time plan_time,
    const TrajectoryProto &prev_traj,
    bool reset,
    ResetReasonProto::Reason reset_reason,
    int max_past_point_num) {
    std::vector<ApolloTrajectoryPointProto> past_points;
    const double curr_plan_time = ToUnixDoubleSeconds(plan_time);
    const double prev_traj_start_time = prev_traj.trajectory_start_timestamp();
    if (prev_traj.trajectory_point().empty() ||
        curr_plan_time >
            prev_traj_start_time +
                prev_traj.trajectory_point().rbegin()->relative_time() ||
        curr_plan_time < prev_traj_start_time ||
        (reset && reset_reason != ResetReasonProto::SPEED_ONLY)) {
        return past_points;
    }
    past_points.reserve(static_cast<size_t>(max_past_point_num));
    const int relative_time_index = RoundToInt(
        (curr_plan_time - prev_traj_start_time) / kTrajectoryTimeStep);
    XCHECK_LT(relative_time_index, prev_traj.trajectory_point_size());
    const double relative_s =
        -prev_traj.trajectory_point(relative_time_index).path_point().s();
    for (int i = max_past_point_num; i > 0; --i) {
        const int index = relative_time_index - i;
        if ((index + prev_traj.past_points_size()) < 0) {
            continue;
        }
        auto point =
            index < 0
                ? prev_traj.past_points(index + prev_traj.past_points_size())
                : prev_traj.trajectory_point(index);
        point.set_relative_time(-static_cast<double>(i) * kTrajectoryTimeStep);
        point.mutable_path_point()->set_s(point.path_point().s() + relative_s);
        past_points.push_back(point);
    }
    past_points.shrink_to_fit();

    return past_points;
}

ApolloTrajectoryPointProto ComputePlanStartPointAfterReset(
    const boost::optional<ApolloTrajectoryPointProto> &prev_reset_planned_point,
    const PoseProto &pose,
    double front_wheel_angle,
    const MotionConstraintParamsProto &motion_constraint_params,
    const VehicleGeometryParamsProto &vehicle_geom_params,
    const VehicleDriveParamsProto &vehicle_drive_params,
    bool is_forward_task) {
    ApolloTrajectoryPointProto plan_start_point;
    const Vec2d pose_pos(pose.pos_smooth().x(), pose.pos_smooth().y());
    plan_start_point.mutable_path_point()->set_x(pose.pos_smooth().x());
    plan_start_point.mutable_path_point()->set_y(pose.pos_smooth().y());
    plan_start_point.mutable_path_point()->set_s(0.0);
    plan_start_point.mutable_path_point()->set_theta(pose.yaw());
    const double pose_v = pose.vel_body().x();
    const double abs_pose_v = std::abs(pose_v);
    if (is_forward_task) {
        plan_start_point.set_v(std::max(0.0, pose_v));
    } else {
        plan_start_point.set_v(std::min(0.0, pose_v));
    }

    if (prev_reset_planned_point.has_value()) {
        constexpr double kFullStopSpeedThreshold = 0.05;
        const bool full_stop = prev_reset_planned_point->v() == 0.0 &&
                               abs_pose_v < kFullStopSpeedThreshold;
        if (full_stop) {
            plan_start_point.mutable_path_point()->set_kappa(
                prev_reset_planned_point->path_point().kappa());
            plan_start_point.mutable_path_point()->set_lambda(
                prev_reset_planned_point->path_point().lambda());
            plan_start_point.set_a(0.0);
            plan_start_point.set_j(0.0);
            return plan_start_point;
        }
    }

    constexpr double kLowSpeedThreshold = 1.0;
    if (abs_pose_v < kLowSpeedThreshold) {
        const double kappa =
            std::tan(front_wheel_angle) / vehicle_geom_params.wheel_base();
        plan_start_point.mutable_path_point()->set_kappa(kappa);
        plan_start_point.mutable_path_point()->set_lambda(0.0);
        plan_start_point.set_a(0.0);
        plan_start_point.set_j(0.0);
    } else {
        plan_start_point.mutable_path_point()->set_kappa(pose.ar_smooth().z() /
                                                         pose_v);
        plan_start_point.mutable_path_point()->set_lambda(0.0);
        plan_start_point.set_a(boost::algorithm::clamp(
            pose.accel_body().x(), motion_constraint_params.max_deceleration(),
            motion_constraint_params.max_acceleration()));
        plan_start_point.set_j(0.0);
    }
    return plan_start_point;
}

LineEquation GetLineEquation(const VehiclePose &pos) {
    double tan_theta = tan(pos.heading);
    return {tan_theta, -1, pos.y - (tan_theta * pos.x)};
}

boost::optional<std::pair<double, double>> CalculateIntersection(
    const VehiclePose &pos1, const VehiclePose &pos2) {
    LineEquation line1 = GetLineEquation(pos1);
    LineEquation line2 = GetLineEquation(pos2);

    double det = (line1.A * line2.B) - (line2.A * line1.B);

    if (fabs(det) < 1e-6) {
        return boost::none;
    }

    double x = ((line1.B * line2.C) - (line2.B * line1.C)) / det;
    double y = ((line2.A * line1.C) - (line1.A * line2.C)) / det;

    return std::make_pair(x, y);
}

std::vector<VehiclePose> PredictEgoTrajectory(double x,
                                              double y,
                                              double heading,
                                              double v,
                                              double yaw_rate,
                                              double delta_t,
                                              int steps) {
    std::vector<VehiclePose> trajectory;
    trajectory.reserve(static_cast<size_t>(steps));
    double revised_v = std::fmax(v, 0.1);
    double revised_yaw_rate = v < 0.1 ? 0.0 : yaw_rate;
    double cur_x = x;
    double cur_y = y;
    double cur_heading = heading;
    for (int i = 0; i < steps; ++i) {
        if (fabs(revised_yaw_rate) < 1e-6) {
            cur_x += revised_v * cos(cur_heading) * delta_t;
            cur_y += revised_v * sin(cur_heading) * delta_t;
        } else {
            double radius = revised_v / revised_yaw_rate;
            cur_heading += revised_yaw_rate * delta_t;
            cur_x += radius * (sin(cur_heading) - sin(heading));
            cur_y -= radius * (cos(cur_heading) - cos(heading));
            heading = cur_heading;
        }
        trajectory.push_back({cur_x, cur_y, cur_heading});
    }

    return trajectory;
}
ApolloTrajectoryPointProto ComputePlanStartPointAfterLateralReset(
    const boost::optional<ApolloTrajectoryPointProto> &prev_reset_planned_point,
    const PoseProto &pose,
    double front_wheel_angle,
    const VehicleGeometryParamsProto &vehicle_geom_params,
    const VehicleDriveParamsProto &vehicle_drive_params) {
    ApolloTrajectoryPointProto plan_start_point;
    const Vec2d pose_pos(pose.pos_smooth().x(), pose.pos_smooth().y());
    std::vector<VehiclePose> EgoPredictPoints = PredictEgoTrajectory(
        pose.pos_smooth().x(), pose.pos_smooth().y(), pose.yaw(),
        pose.vel_body().x(), pose.ar_smooth().z(), 0.03, 15);
    VehiclePose nearest_pose = {pose.pos_smooth().x(), pose.pos_smooth().y(),
                                pose.yaw()};
    double min_dis = std::sqrt(
        std::pow(prev_reset_planned_point->path_point().x() - nearest_pose.x,
                 2) +
        std::pow(prev_reset_planned_point->path_point().y() - nearest_pose.y,
                 2));
    for (auto &pos : EgoPredictPoints) {
        double dis = std::sqrt(
            std::pow(prev_reset_planned_point->path_point().x() - pos.x, 2) +
            std::pow(prev_reset_planned_point->path_point().y() - pos.y, 2));
        if (dis < min_dis) {
            min_dis = dis;
            nearest_pose = pos;
        }
    }
    auto intersection = CalculateIntersection(
        nearest_pose,
        {prev_reset_planned_point->path_point().x(),
         prev_reset_planned_point->path_point().y(),
         prev_reset_planned_point->path_point().theta() + (M_PI / 2.0)});
    if (intersection.has_value()) {
        nearest_pose.x = intersection.value().first;
        nearest_pose.y = intersection.value().second;
    }

    plan_start_point.mutable_path_point()->set_x(nearest_pose.x);
    plan_start_point.mutable_path_point()->set_y(nearest_pose.y);
    plan_start_point.mutable_path_point()->set_s(0.0);
    plan_start_point.mutable_path_point()->set_theta(nearest_pose.heading);

    XCHECK(prev_reset_planned_point.has_value());
    plan_start_point.set_v(prev_reset_planned_point->v());
    plan_start_point.set_a(prev_reset_planned_point->a());
    plan_start_point.set_j(prev_reset_planned_point->j());

    const double pose_v = pose.vel_body().x();
    const double abs_pose_v = std::abs(pose_v);
    constexpr double kFullStopSpeedThreshold = 0.05;
    const bool full_stop = prev_reset_planned_point->v() == 0.0 &&
                           abs_pose_v < kFullStopSpeedThreshold;
    if (full_stop) {
        plan_start_point.mutable_path_point()->set_kappa(
            prev_reset_planned_point->path_point().kappa());
        plan_start_point.mutable_path_point()->set_lambda(
            prev_reset_planned_point->path_point().lambda());
        return plan_start_point;
    }

    constexpr double kLowSpeedThreshold = 1.0;
    if (abs_pose_v < kLowSpeedThreshold) {
        const double kappa =
            std::tan(front_wheel_angle) / vehicle_geom_params.wheel_base();
        plan_start_point.mutable_path_point()->set_kappa(kappa);
        plan_start_point.mutable_path_point()->set_lambda(0.0);
    } else {
        plan_start_point.mutable_path_point()->set_kappa(pose.ar_smooth().z() /
                                                         pose_v);
        plan_start_point.mutable_path_point()->set_lambda(0.0);
    }
    return plan_start_point;
}

ApolloTrajectoryPointProto
ComputePlanStartPointAfterLongitudinalResetFromPrevTrajectory(
    const TrajectoryProto &prev_traj,
    const PoseProto &pose,
    double front_wheel_angle,
    const VehicleGeometryParamsProto &vehicle_geom_params,
    const VehicleDriveParamsProto &vehicle_drive_params) {
    ApolloTrajectoryPointProto plan_start_point;

    plan_start_point.set_v(std::max(0.0, pose.vel_body().x()));
    plan_start_point.set_a(pose.accel_body().x());
    plan_start_point.set_j(0.0);

    if (prev_traj.trajectory_point_size() < 2) {
        plan_start_point.mutable_path_point()->set_s(0.0);
        plan_start_point.mutable_path_point()->set_x(pose.pos_smooth().x());
        plan_start_point.mutable_path_point()->set_y(pose.pos_smooth().y());
        plan_start_point.mutable_path_point()->set_theta(pose.yaw());
        constexpr double kLowSpeedThreshold = 1.0;
        if (std::abs(pose.vel_body().x()) < kLowSpeedThreshold) {
            const double kappa =
                std::tan(front_wheel_angle) / vehicle_geom_params.wheel_base();
            plan_start_point.mutable_path_point()->set_kappa(kappa);
            plan_start_point.mutable_path_point()->set_lambda(0.0);
        } else {
            plan_start_point.mutable_path_point()->set_kappa(
                pose.ar_smooth().z() / pose.vel_body().x());
            plan_start_point.mutable_path_point()->set_lambda(0.0);
        }
        return plan_start_point;
    }

    std::vector<PathPoint> prev_traj_path_points;
    prev_traj_path_points.reserve(static_cast<size_t>(prev_traj.trajectory_point_size()));
    for (int i = 0; i < prev_traj.trajectory_point_size(); ++i) {
        prev_traj_path_points.push_back(
            prev_traj.trajectory_point(i).path_point());

        prev_traj_path_points.back().set_s(
            prev_traj.trajectory_point(i).path_point().s() -
            prev_traj.trajectory_point(0).path_point().s());
    }
    DiscretizedPath prev_traj_path(std::move(prev_traj_path_points));
    const auto pose_sl = prev_traj_path.XYToSL(
        Vec2d(pose.pos_smooth().x(), pose.pos_smooth().y()));
    *plan_start_point.mutable_path_point() = prev_traj_path.Evaluate(pose_sl.s);
    plan_start_point.mutable_path_point()->set_s(0.0);
    return plan_start_point;
}

SelectorParamsProto LoadSelectorParamsFromFile(
    const std::string &file_address) {
    SelectorParamsProto selector_params_proto;
    if (!file_util::TextFileToProto(file_address, &selector_params_proto)) {
        // XCHECK(false)
        //     << "Read auto tuned selector params as text file failed!!!!";
    }
    // AD_LINFO(PP) << "New auto tuned selector params are used.";
    return selector_params_proto;
}

}  // namespace planning
}  // namespace pnc_x
