#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "object/spacetime_object_trajectory.h"
#include "object/spacetime_planner_object_trajectories.h"
#include "object/spacetime_trajectory_manager.h"
#include "optimization/ddp/buffer_calc_util.h"
#include "optimization/ddp/object_cost_util.h"
#include "optimization/ddp/path_time_corridor.h"
#include "plan/planner_util.h"
#include "plan/trajectory_point.h"
#include "plan/trajectory_util.h"
#include "pncx_trajectory.pb.h"
#include "pncx_trajectory_point.pb.h"
#include "util/perception_util.h"
#include "util/loop_guard.h"

namespace pnc_x {
namespace planning {
namespace optimizer {

namespace {

enum class StaticObjectNudgeType {
    kSmallVehicle = 0,
    kLargeVehicle = 1,
    kOtherStatic = 2,
};

struct StationaryObjectNudgeConfig {
    double default_buffer;
    double lane_change_buffer;
    double min_buffer;
    double max_buffer_base;
    double extra_buffer;
};

StaticObjectNudgeType GetStaticObjectNudgeType(
    const SpacetimeObjectTrajectory &traj) {
    if (traj.object_type() == ObjectType::OT_LARGE_VEHICLE ||
        IsLargeVehicle(traj.planner_object().object_proto())) {
        return StaticObjectNudgeType::kLargeVehicle;
    }
    if (traj.object_type() == ObjectType::OT_VEHICLE) {
        return StaticObjectNudgeType::kSmallVehicle;
    }
    return StaticObjectNudgeType::kOtherStatic;
}

StationaryObjectNudgeConfig GetStationaryObjectNudgeConfig(
    const SpacetimeObjectTrajectory &traj) {
    switch (GetStaticObjectNudgeType(traj)) {
        case StaticObjectNudgeType::kLargeVehicle:
            return {0.75, 0.90, 0.70, 1.10, 0.08};
        case StaticObjectNudgeType::kSmallVehicle:
            return {0.65, 0.80, 0.65, 1.00, 0.05};
        case StaticObjectNudgeType::kOtherStatic:
            return {0.60, 0.75, 0.60, 0.85, 0.00};
    }
    /*
        default_buffer;
        lane_change_buffer;
        min_buffer;
        max_buffer_base;
        extra_buffer;
    */
    return {0.65, 0.80, 0.65, 1.00, 0.05};
}

}  // namespace

void NudgeBufferManager::CalcNudgeBuffers(
    const PathTimeCorridor &path_time_corridor,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const std::vector<TrajectoryPoint> &prev_traje,
    const std::vector<TrajectoryPoint> &init_traj,
    const DrivePassage &drive_passage) {
    const auto &trajs = *st_planner_object_traj.trajectories;
    std::vector<PlannerObject> uu;
    std::vector<ads_x::planning::RoadBoundaryConstPtr> curb;
    std::vector<PlannerObject> static_objects;
    std::vector<PlannerObject> dynmic_objects;
    for (const auto &traj : trajs) {
        if (traj.object_type() == ObjectType::OT_UNKNOWN_MOVABLE) {
            uu.emplace_back(traj.planner_object());
        } else if (traj.is_stationary()) {
            static_objects.emplace_back(traj.planner_object());
        } else if (!traj.is_stationary()) {
            dynmic_objects.emplace_back(traj.planner_object());
        }
    }
    std::unordered_set<mapping::ElementId> curb_boundaries;
    for (int i = 1; i < drive_passage.size(); ++i) {
        if (i > drive_passage.last_real_station_index().value()) {
            break;
        }
        const Vec2d p0 = drive_passage.station(StationIndex(i - 1)).xy();
        const Vec2d &p1 = drive_passage.station(StationIndex(i)).xy();
        const double search_radius =
            kMaxLateralOffset + ((p1 - p0).Length() * 0.5);
        const Vec2d search_center = 0.5 * (p0 + p1);
        const std::vector<ads_x::planning::RoadBoundaryConstPtr>
            candidate_boundaries;
        // = psmm.GetRoadBoundaries(search_center, search_radius);
        for (const auto &candidate_boundary : candidate_boundaries) {
            curb_boundaries.insert(candidate_boundary->id());
            curb.emplace_back(candidate_boundary);
        }
    }
}

const NudgeBufferWeightInfo NudgeBufferManager::GenerateNudgeBufferDynamic(
    const int plan_id,
    const LaneChangeStage lc_stage,
    const bool borrow_lane,
    const std::vector<SpacetimeObjectState> &states,
    const std::vector<pnc_x::planning::TrajectoryPoint> &init_traj,
    bool is_camera_object,
    const Vec2d &object_velocity,
    const Polygon2d &object_contour,
    const TrajectoryPoint &plan_start_point,
    const DrivePassage &drive_passage,
    const double lane_width,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const SpacetimeObjectTrajectory &traj,
    const PathSlBoundary &path_boundary,
    const PathTimeCorridor &path_time_corridor,
    pnc_x::planning::optimizer::TurnType ego_turn_type,
    const std::vector<pnc_x::planning::TrajectoryPoint> &prev_traj) {
    const PiecewiseLinearFunction<double> nudge_buffer_av_speed_plf =
        PiecewiseLinearFunctionFromProto(
            cost_weight_params.object_cost_params()
                .nudge_front_buffer_object_speed_plf());
    const PiecewiseLinearFunction<double>
        nudge_buffer_gain_object_speed_diff_plf =
            PiecewiseLinearFunctionFromProto(
                cost_weight_params.object_cost_params()
                    .nudge_buffer_gain_object_speed_diff_plf());
    const PiecewiseLinearFunction<double> min_nudge_buffer_speed_plf =
        PiecewiseLinearFunctionFromProto(cost_weight_params.object_cost_params()
                                             .min_nudge_buffer_speed_plf());
    const Vec2d av_local_dir =
        Vec2d::FastUnitFromAngle(plan_start_point.theta());
    const double obj_v_av_local = object_velocity.dot(av_local_dir);
    const double speed_diff = obj_v_av_local - plan_start_point.v();

    double nudge_buffer = (lc_stage == LaneChangeStage::LCS_NONE)
                              ? boost::algorithm::clamp(
                                    0.4 + (0.45 * (lane_width - 2.7)), 0.4, 0.85)
                              : 0.85;
    const double heading_diff_cos = std::cos(NormalizeAngle(
        plan_start_point.theta() - traj.bounding_box().heading()));
    bool is_oppsite_obj = heading_diff_cos < -0.707;
    if (is_oppsite_obj) {
        nudge_buffer = std::max(0.75, nudge_buffer);
    }
    double min_nudge_buffer_dyn = 0.5;
    double max_nudge_buffer_dyn = 1.0;
    // 0.4 ~ 0.85
    double nudge_buffer_base = std::max(
        min_nudge_buffer_dyn,
        nudge_buffer * nudge_buffer_av_speed_plf(plan_start_point.v()));

    if (traj.object_type() == OT_VEHICLE ||
        traj.object_type() == OT_LARGE_VEHICLE) {
        nudge_buffer_base += 0.1; // (0.1 + 0.5 = 0.6)
    }

    if (traj.object_type() == OT_MOTORCYCLIST ||
        traj.object_type() == OT_CYCLIST ||
        traj.object_type() == OT_PEDESTRIAN ||
        traj.object_type() == OT_TRICYCLIST) {
        nudge_buffer_base =
            borrow_lane ? (nudge_buffer_base + 0.1) : (nudge_buffer_base + 0.15); // ()
        min_nudge_buffer_dyn = borrow_lane ? 0.6 : 0.7;
        max_nudge_buffer_dyn = borrow_lane ? 1.0 : 1.1;
    } else if (traj.object_type() == OT_VEHICLE) {
        nudge_buffer_base += 0.20; // (0.20 + 0.6 = 0.80)
        min_nudge_buffer_dyn += 0.15;
        max_nudge_buffer_dyn += 0.35; // (0.65~1.35)
    } else if (traj.object_type() == OT_LARGE_VEHICLE) {
        nudge_buffer_base += 0.55; // (0.65 + 0.6 = 1.25)
        min_nudge_buffer_dyn += 0.55;
        max_nudge_buffer_dyn += 0.65; // (1.05~1.65)
    }

    double nudge_buffer_consider_lane = nudge_buffer;
    const auto object_frenet_box_output =
        drive_passage.QueryFrenetBoxAtContour(object_contour);
    if (object_frenet_box_output.ok()) {
        const auto &object_frenet_box = object_frenet_box_output.value();
        const double object_s = object_frenet_box.center_s();
        const auto object_lane_boundary_info =
            drive_passage.QueryEnclosingLaneBoundariesAtS(object_s);
        constexpr double kNudgeBufferLaneWidthGain = 1.1;
        if (object_frenet_box.l_max < 0.0) {
            if (object_lane_boundary_info.right.has_value()) {
                nudge_buffer_consider_lane = boost::algorithm::clamp(
                    (-object_lane_boundary_info.right->lat_offset -
                     (veh_geo_params.width() * 0.5)) *
                        kNudgeBufferLaneWidthGain,
                    min_nudge_buffer_dyn, nudge_buffer_base);
            }
        } else if (object_frenet_box.l_min > 0.0) {
            if (object_lane_boundary_info.left.has_value()) {
                nudge_buffer_consider_lane = boost::algorithm::clamp(
                    (object_lane_boundary_info.left->lat_offset -
                     (veh_geo_params.width() * 0.5)) *
                        kNudgeBufferLaneWidthGain,
                    min_nudge_buffer_dyn, nudge_buffer_base);
            }
        }

        if (object_lane_boundary_info.right.has_value() &&
            object_lane_boundary_info.left.has_value()) {
            nudge_buffer_consider_lane =
                std::min(nudge_buffer_consider_lane,
                         boost::algorithm::clamp(
                             (((object_lane_boundary_info.left->lat_offset -
                               object_lane_boundary_info.right->lat_offset) *
                                  0.5) -
                              (veh_geo_params.width() * 0.5)) *
                                 kNudgeBufferLaneWidthGain,
                             min_nudge_buffer_dyn, nudge_buffer_base));
            const double nudge_buffer_min =
                nudge_buffer_base * min_nudge_buffer_speed_plf(std::max(
                                        obj_v_av_local, plan_start_point.v()));
            nudge_buffer =
                std::max(nudge_buffer_consider_lane, nudge_buffer_min);
            if (ego_turn_type != TurnType::kLeftTurn) {
                nudge_buffer *=
                    nudge_buffer_gain_object_speed_diff_plf(speed_diff);
            }
            nudge_buffer_base = std::max(nudge_buffer, min_nudge_buffer_dyn);
        }
    } else {
        nudge_buffer_base = 0.8;
    }

    double nudge_buffer_base_fix = nudge_buffer_base;
    std::vector<double> buffer_value;
    std::vector<bool> has_curb_value;
    std::vector<double> weight_gains_value;
    std::vector<double> s_obj_states;
    std::vector<double> l_left_obj_states;
    std::vector<double> l_right_obj_states;
    const auto object_position_info =
        path_time_corridor.QueryObjectPositionInfo(
            std::string(traj.object_id()));
    for (size_t i = 0U; i < states.size(); ++i) {
        bool has_curb = false;
        double current_weight_gain = 1.0;
        const auto object_frenet_box_dt_output =
            drive_passage.QueryFrenetBoxAtContour(states[i].contour);
        if (!object_frenet_box_dt_output.ok()) {
            buffer_value.push_back(nudge_buffer_base);
            has_curb_value.push_back(has_curb);
            weight_gains_value.push_back(current_weight_gain);
            continue;
        }
        const auto &object_frenet_box_dt = object_frenet_box_dt_output.value();
        const double object_s_dt = object_frenet_box_dt.center_s();
        s_obj_states.push_back(object_s_dt);
        const auto &st_corridor = path_time_corridor.QueryBoundaryL(
            object_s_dt, states.at(i).traj_point->t());
        l_left_obj_states.push_back(st_corridor.second.l_object);
        l_right_obj_states.push_back(st_corridor.first.l_object);

        const auto object_station_point =
            drive_passage.FindNearestStation(states[i].traj_point->pos());
        const double heading_point_diff_cos = std::cos(
            NormalizeAngle(init_traj[i].theta() - states[i].box.heading()));
        bool is_oppsite_obj_point = heading_point_diff_cos < -0.707;
        bool is_obj_point_junction = object_station_point.is_in_intersection();
        if (object_station_point.station_info().turn_type ==
                ads_x::planning::TurnType::RIGHT_TURN &&
            is_obj_point_junction && is_oppsite_obj_point) {
            if (traj.object_type() == OT_LARGE_VEHICLE) {
                nudge_buffer_base_fix = nudge_buffer_base + 0.5;
            } else {
                nudge_buffer_base_fix = nudge_buffer_base + 0.2;
            }
        }

        // first是右，second是左
        if (object_position_info.at(i).position_type ==
            PathTimeCorridor::PositionType::POSITION_LEFT) {
            double coef_space_obj = 0.5;
            double min_dyn_local  = min_nudge_buffer_dyn;  // 局部下限=全局
            if (st_corridor.second.type ==
                    PathTimeCorridor::BoundaryInfo::VRU ||
                IsVulnerableRoadUserType(traj.object_type())) {
                switch (st_corridor.first.type) {
                    case PathTimeCorridor::BoundaryInfo::VRU:
                    case PathTimeCorridor::BoundaryInfo::CURB:
                    case PathTimeCorridor::BoundaryInfo::STATIC:
                        coef_space_obj = 0.05;
                        min_dyn_local = 0.0;
                        has_curb = true;
                        break;
                    case PathTimeCorridor::BoundaryInfo::LARGE_VEHICLE:
                    case PathTimeCorridor::BoundaryInfo::VEHICLE:
                        coef_space_obj = 0.7;
                        break;
                    case PathTimeCorridor::BoundaryInfo::LANE_BOUNDARY:
                        coef_space_obj = 0.8;
                        break;
                    default:
                        coef_space_obj = 0.5;
                        break;
                }
            } else if (st_corridor.second.type ==
                           PathTimeCorridor::BoundaryInfo::VEHICLE ||
                       traj.object_type() == OT_VEHICLE) {
                switch (st_corridor.first.type) {
                    case PathTimeCorridor::BoundaryInfo::VRU:
                    case PathTimeCorridor::BoundaryInfo::CURB:
                        coef_space_obj = 0.05;
                        min_dyn_local = 0.0;
                        has_curb = true;
                        break;
                    case PathTimeCorridor::BoundaryInfo::LARGE_VEHICLE:
                        // 左边是小车，右边是大车，增大小车的权重
                        current_weight_gain = 3.0;
                        coef_space_obj = 0.5;
                        break;
                    case PathTimeCorridor::BoundaryInfo::VEHICLE:
                    case PathTimeCorridor::BoundaryInfo::STATIC:
                      coef_space_obj = 0.5;
                      break;
                    case PathTimeCorridor::BoundaryInfo::LANE_BOUNDARY:
                        coef_space_obj = 0.5;
                      break;
                    default:
                        coef_space_obj = 0.5;
                        break;
                }
            } else if (st_corridor.second.type ==
                           PathTimeCorridor::BoundaryInfo::LARGE_VEHICLE ||
                       traj.object_type() == OT_LARGE_VEHICLE) {
                switch (st_corridor.first.type) {
                    case PathTimeCorridor::BoundaryInfo::VRU:
                    case PathTimeCorridor::BoundaryInfo::CURB:
                        coef_space_obj = 0.05;
                        min_dyn_local = 0.0;
                        has_curb = true;
                        break;
                    case PathTimeCorridor::BoundaryInfo::LARGE_VEHICLE:
                        coef_space_obj = 0.5;
                        break;
                    case PathTimeCorridor::BoundaryInfo::VEHICLE:
                        // 左边是小车，右边是大车，增加大车的buffer
                        coef_space_obj = 0.65;
                        break;
                    case PathTimeCorridor::BoundaryInfo::STATIC:
                    case PathTimeCorridor::BoundaryInfo::LANE_BOUNDARY:
                        coef_space_obj = 0.6;
                        break;
                    default:
                        coef_space_obj = 0.5;
                        break;
                }
            }

            double dis_space =
                st_corridor.second.l_object - st_corridor.first.l_object;
            nudge_buffer = std::max(
                0.0, (dis_space - veh_geo_params.width()) * coef_space_obj);
            nudge_buffer = boost::algorithm::clamp(
                nudge_buffer, min_dyn_local, max_nudge_buffer_dyn);
        } else if (object_position_info.at(i).position_type ==
                   PathTimeCorridor::PositionType::POSITION_RIGHT) {
            double coef_space_obj = 0.5;
            double min_dyn_local  = min_nudge_buffer_dyn;  // 局部下限=全局
            if (st_corridor.first.type == PathTimeCorridor::BoundaryInfo::VRU ||
                IsVulnerableRoadUserType(traj.object_type())) {
                switch (st_corridor.second.type) {
                    case PathTimeCorridor::BoundaryInfo::VRU:
                    case PathTimeCorridor::BoundaryInfo::CURB:
                    case PathTimeCorridor::BoundaryInfo::STATIC:
                        coef_space_obj = 0.05;
                        min_dyn_local = 0.0;
                        has_curb = true;
                        break;
                    case PathTimeCorridor::BoundaryInfo::LARGE_VEHICLE:
                    case PathTimeCorridor::BoundaryInfo::VEHICLE:
                        coef_space_obj = 0.6;
                        break;
                    case PathTimeCorridor::BoundaryInfo::LANE_BOUNDARY:
                        coef_space_obj = 0.8;
                        break;
                    default:
                        coef_space_obj = 0.5;
                        break;
                }
            } else if (st_corridor.first.type ==
                           PathTimeCorridor::BoundaryInfo::VEHICLE ||
                       traj.object_type() == OT_VEHICLE) {
                switch (st_corridor.second.type) {
                    case PathTimeCorridor::BoundaryInfo::VRU:
                    case PathTimeCorridor::BoundaryInfo::CURB:
                        coef_space_obj = 0.05;
                        min_dyn_local = 0.0;
                        has_curb = true;
                        break;
                    case PathTimeCorridor::BoundaryInfo::LARGE_VEHICLE:
                        // 右边是小车，左边是大车，增大小车的权重
                        current_weight_gain = 3.0;
                        coef_space_obj = 0.5;
                        break;
                        break;
                    case PathTimeCorridor::BoundaryInfo::VEHICLE:
                    case PathTimeCorridor::BoundaryInfo::STATIC:
                    case PathTimeCorridor::BoundaryInfo::LANE_BOUNDARY:
                        coef_space_obj = 0.5;
                      break;
                    default:
                        coef_space_obj = 0.5;
                        break;
                }
            } else if (st_corridor.first.type ==
                           PathTimeCorridor::BoundaryInfo::LARGE_VEHICLE ||
                       traj.object_type() == OT_LARGE_VEHICLE) {
                //  右边是大车，按照左边的不同障碍物类型，调整buffer和权重系数
                switch (st_corridor.second.type) {
                    case PathTimeCorridor::BoundaryInfo::VRU:
                    case PathTimeCorridor::BoundaryInfo::CURB:
                        coef_space_obj = 0.05;
                        min_dyn_local = 0.0;
                        has_curb = true;
                        break;
                    case PathTimeCorridor::BoundaryInfo::LARGE_VEHICLE:
                        coef_space_obj = 0.5;
                        break;
                    case PathTimeCorridor::BoundaryInfo::VEHICLE:
                        // 右边是大车，左边是小车，增大大车的buffer
                        coef_space_obj = 0.65;
                    case PathTimeCorridor::BoundaryInfo::STATIC:
                    case PathTimeCorridor::BoundaryInfo::LANE_BOUNDARY:
                      coef_space_obj = 0.6;
                      break;
                    default:
                        coef_space_obj = 0.5;
                        break;
                }
            }

            double dis_space =
                borrow_lane
                    ? (st_corridor.second.l_object - st_corridor.first.l_object -
                          0.5)
                    : (st_corridor.second.l_object - st_corridor.first.l_object);
            nudge_buffer = std::max(
                0.0, (dis_space - veh_geo_params.width()) * coef_space_obj);
             nudge_buffer = boost::algorithm::clamp(
                nudge_buffer, min_dyn_local, max_nudge_buffer_dyn);
        } else {
            nudge_buffer = nudge_buffer_base_fix;
        }
        nudge_buffer = std::max(nudge_buffer_base_fix, nudge_buffer);
        constexpr double kMinBufferForEgoTurnRight = 0.7;
        if (ego_turn_type == TurnType::kRightTurn) {
            nudge_buffer = std::max(nudge_buffer, kMinBufferForEgoTurnRight);
        }
        constexpr double kOncomingbuffer = 1.5;
        if (is_oppsite_obj) {
            nudge_buffer = std::max(nudge_buffer, kOncomingbuffer);
        }
        buffer_value.push_back(nudge_buffer);
        has_curb_value.push_back(has_curb);
        weight_gains_value.push_back(current_weight_gain);
    }

    // const std::string base_name_with_plan_id =
    //     absl::StrFormat("opt_task_%d", plan_id);

    NudgeBufferWeightInfo result;
    result.buffer_value = buffer_value;
    result.has_curb = has_curb_value;
    result.weight_gains = weight_gains_value;

    return result;
}

const std::vector<double> NudgeBufferManager::GenerateNudgeBufferStationary(
    const int plan_id,
    const LaneChangeStage lc_stage,
    const std::vector<SpacetimeObjectState> &states,
    bool is_camera_object,
    bool is_static,
    const Vec2d &object_velocity,
    const Polygon2d &object_contour,
    const std::vector<pnc_x::planning::TrajectoryPoint> &init_traj,
    const DrivePassage &drive_passage,
    const double lane_width,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const SpacetimeObjectTrajectory &traj,
    const PathSlBoundary &path_boundary,
    const PathTimeCorridor &path_time_corridor,
    TurnType ego_turn_type) {
    const auto object_frenet_box_output =
        drive_passage.QueryFrenetBoxAtContour(object_contour);
    const auto nudge_config = GetStationaryObjectNudgeConfig(traj);
    if (!object_frenet_box_output.ok())
        return std::vector<double>(states.size(), nudge_config.default_buffer);
    const auto &object_frenet_box = object_frenet_box_output.value();
    const double object_s = object_frenet_box.center_s();

    double bypass_time = 15.0;
    size_t bypass_traj_point_idx = 0UL;
    if (!init_traj.empty()) {
        size_t next_traj_point_idx = init_traj.size() - 1;
        auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((next_traj_point_idx - bypass_traj_point_idx) > 1 && loop_guard) {
            size_t mid_idx = (next_traj_point_idx + bypass_traj_point_idx) >> 1;
            if (init_traj.at(mid_idx).s() < object_s) {
                bypass_traj_point_idx = mid_idx;
            } else {
                next_traj_point_idx = mid_idx;
            }
        }
        bypass_time = init_traj.at(bypass_traj_point_idx).t();
    }

    if (init_traj.empty()) {
        return std::vector<double>(states.size(), nudge_config.default_buffer);
    }

    const double angle_diff = fabs(NormalizeAngle(
        init_traj.front().theta() - traj.bounding_box().heading()));
    const double heading_diff_sin =
        (angle_diff < (M_PI / 3.0)) ? 0.0 : std::sin(angle_diff);
    double buffer_factor = 1.0 + (0.4 * heading_diff_sin);
    auto corridor_bound =
        path_time_corridor.QueryBoundaryL(object_s, bypass_time);
    for (size_t i = 0UL; i < bypass_traj_point_idx; ++i) {
        const double s = init_traj.at(i).s();
        const double t = init_traj.at(i).t();
        auto bound = path_time_corridor.QueryBoundaryL(s, t);
        corridor_bound.first.l_object =
            std::max(corridor_bound.first.l_object, bound.first.l_object);
        corridor_bound.second.l_object =
            std::min(corridor_bound.second.l_object, bound.second.l_object);
    }
    const auto object_position_info =
        path_time_corridor.QueryObjectPositionInfo(
            std::string(traj.object_id()));

    if (object_position_info.empty()) {
        return std::vector<double>(states.size(),
                                   nudge_config.default_buffer * buffer_factor);
    }
    if (lc_stage == LaneChangeStage::LCS_EXECUTING) {
        return std::vector<double>(states.size(),
                                   nudge_config.lane_change_buffer *
                                       buffer_factor);
    }
    double nudge_buffer = nudge_config.default_buffer;
    const auto object_sl_boundary_info = path_boundary.QueryBoundaryL(object_s);
    const auto object_sl_boundary_info_target =
        path_boundary.QueryTargetBoundaryL(object_s);
    double object_sl_boundary_info_target_first = std::max(
        object_sl_boundary_info_target.first, corridor_bound.first.l_object);
    double object_sl_boundary_info_target_second = std::min(
        object_sl_boundary_info_target.second, corridor_bound.second.l_object);
    double extra_buffer_left = 0.0;
    double extra_buffer_right = 0.0;
    if (init_traj.empty()) {
        return std::vector<double>(states.size(), nudge_config.default_buffer);
    }
    double ego_speed_factor = boost::algorithm::clamp(
        (init_traj.front().v() - 8.333) / 8.333, 0.0, 1.0);
    const double kMinNudgeBuffer = nudge_config.min_buffer;
    const double kMaxNudgeBuffer =
        nudge_config.max_buffer_base + (0.2 * ego_speed_factor);
    if (object_position_info.front().position_type ==
        PathTimeCorridor::PositionType::POSITION_LEFT) {
        double object_invade_dist =
            object_sl_boundary_info_target.second - object_frenet_box.l_min;
        if (object_invade_dist < 0.0) {
            return std::vector<double>(states.size(),
                                       nudge_config.default_buffer *
                                           buffer_factor);
        }
        double extra_buffer_factor = boost::algorithm::clamp(
            (object_invade_dist - 0.15) * 5.0, 0.0, 1.0);
        nudge_buffer = boost::algorithm::clamp(
            (object_frenet_box.l_min - object_sl_boundary_info_target_first -
             veh_geo_params.width()) *
                0.5,
            kMinNudgeBuffer, kMaxNudgeBuffer);
        extra_buffer_right = (nudge_buffer < 0.75)
                                 ? ((object_sl_boundary_info_target_first -
                                    object_sl_boundary_info.first) *
                                       0.20 * extra_buffer_factor)
                                 : 0.0;
        nudge_buffer += std::min(extra_buffer_right, 0.4);
    } else if (object_position_info.front().position_type ==
               PathTimeCorridor::PositionType::POSITION_RIGHT) {
        double object_invade_dist =
            object_frenet_box.l_max - object_sl_boundary_info_target.first;
        if (object_invade_dist < 0.0) {
            return std::vector<double>(states.size(),
                                       nudge_config.default_buffer *
                                           buffer_factor);
        }
        double extra_buffer_factor = boost::algorithm::clamp(
            (object_invade_dist - 0.15) * 5.0, 0.0, 1.0);
        nudge_buffer = boost::algorithm::clamp(
            (object_sl_boundary_info_target_second - object_frenet_box.l_max -
             veh_geo_params.width()) *
                0.5,
            kMinNudgeBuffer, kMaxNudgeBuffer);
        extra_buffer_left = (nudge_buffer < 0.75)
                                ? ((object_sl_boundary_info.second -
                                   object_sl_boundary_info_target_second) *
                                      0.20 * extra_buffer_factor)
                                : 0.0;
        nudge_buffer += std::min(extra_buffer_left, 0.4);
    } else {
        nudge_buffer = nudge_config.default_buffer;
    }
    nudge_buffer = std::min((nudge_buffer * buffer_factor) +
                                nudge_config.extra_buffer,
                            kMaxNudgeBuffer);
    // const std::string base_name_with_plan_id =
    //     absl::StrFormat("opt_task_%d", plan_id);

    return std::vector<double>(states.size(), nudge_buffer);
}

bool NudgeBufferManager::GenerateNudgeBufferUU(
    const int plan_id,
    double trajectory_time_step,
    std::string base_name,
    const LaneChangeStage lc_stage,
    const TrajectoryPoint &plan_start_point,
    const PathTimeCorridor &path_time_corridor,
    absl::Span<const SpacetimeObjectTrajectory *const> spacetime_trajs,
    double min_mirror_height_avg,
    double max_mirror_height_avg,
    const double lane_width_l,
    const double lane_width_r,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    const VehicleGeometryParamsProto &veh_geo_params) {
    std::vector<Segment2d> segments;
    std::vector<Segment2d> segments_consider_mirrors;
    constexpr int kEstimateLineCountsPerObject = 6;
    if (!XCHECK_GT(trajectory_time_step, 0.0)) {
        return false;
    }
    const int kTrajStepsMinus1 = kTrajectorySteps - 1;
    const int free_index = static_cast<int>(
        (static_cast<double>(kTrajStepsMinus1) * kTrajectoryTimeStep) / trajectory_time_step);
    segments.reserve(static_cast<size_t>(kEstimateLineCountsPerObject) * spacetime_trajs.size());
    segments_consider_mirrors.reserve(static_cast<size_t>(kEstimateLineCountsPerObject) *
                                      spacetime_trajs.size());
    const double lane_width = lane_width_l - lane_width_r;
    std::vector<bool> obj_within_lane_vec;
    for (int idx = 0; idx < spacetime_trajs.size(); ++idx) {
        const auto &traj = *spacetime_trajs[idx];
        auto obejct_position = path_time_corridor.QueryObjectPositionInfo(
            std::string(traj.object_id()));
        auto obj_boundary_info =
            path_time_corridor.QueryBoundaryL(obejct_position[0UL].object_s, 0);
        auto lane_width_obj = obj_boundary_info.second.l_boundary -
                              obj_boundary_info.first.l_boundary;

        const bool obj_within_lane =
            obejct_position[0].object_l < lane_width_l &&
            obejct_position[0].object_l > lane_width_r;

        obj_within_lane_vec.emplace_back(obj_within_lane);
    }

    bool need_lane_width_buffer = false;
    for (bool objinlane : obj_within_lane_vec) {
        if (objinlane) {
            need_lane_width_buffer = true;
            break;
        }
    }

    if (segments.empty() && segments_consider_mirrors.empty()) {
        return true;
    }

    constexpr double kSafeBuffer = 0.6;

    const std::vector<double> station_inside_sl_boundary_static_max_speed = {
        3.0, 10.0, 20.0, 30.0};
    const std::vector<double> close_object_distance = {0.5, 0.65, 0.8, 1.0};
    const std::vector<double> lane_width_vec = {2.7, 2.8, 2.9, 3.0, 4.0};
    const std::vector<double> nudge_buffers_vec = {0.05, 0.05, 0.05, 0.05, 0.3};

    const PiecewiseLinearFunction<double> nudge_buffer_lane_width_plf(
        lane_width_vec, nudge_buffers_vec);

    const PiecewiseLinearFunction<double> nudge_buffer_speed_plf(
        station_inside_sl_boundary_static_max_speed, close_object_distance);
    double nudge_buffer_soft = std::max(
        kSafeBuffer, nudge_buffer_speed_plf(plan_start_point.v()) + 0.1);
    if (need_lane_width_buffer) {
        nudge_buffer_soft = std::max(
            kSafeBuffer, nudge_buffer_speed_plf(plan_start_point.v()) +
                             nudge_buffer_lane_width_plf(lane_width) + 0.1);
    }

    const double nudge_buffer_hard = kSafeBuffer;
    return true;
}

}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
