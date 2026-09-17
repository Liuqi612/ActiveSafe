#include "optimization/ddp/object_cost_util.h"

#include <absl/status/statusor.h>
#include <absl/strings/str_format.h>
#include <absl/strings/string_view.h>
#include <absl/types/span.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "async/parallel_for.h"
#include "plan/planner_flags.h"
// #include <gflags/gflags.h>
#include "common/log.h"
#include "common/vehicle_speed_config_helper.h"
#include "math/frenet_common.h"
#include "math/piecewise_const_function.h"
#include "math/piecewise_linear_function.h"
#include "math/util.h"
#include "object/planner_object.h"
#include "object/spacetime_object_state.h"
#include "object/spacetime_object_trajectory.h"
#include "optimization/problem/aggregate_static_object_cost.h"
#include "optimization/problem/center_line_query_helper.h"
#include "optimization/problem/partitioned_object_cost.h"
#include "optimization/problem/unidirectional_object_cost.h"
#include "plan/planner_defs.h"
#include "plan/planner_util.h"
#include "plan/second_order_trajectory_point.h"
#include "plan/trajectory_point.h"
#include "prediction/predicted_trajectory.h"
#include "util/map_util.h"
#include "util/perception_util.h"
#include "util/vehicle_geometry_util.h"
#include "optimization/ddp/curve_defensive_util.h"

// DEFINE_bool(traj_opt_draw_object_canvas, false,
//             "If send object cost reults to canvas.");

bool FLAGS_traj_opt_draw_object_canvas = false;

namespace pnc_x {
namespace planning {
namespace optimizer {
namespace {

enum class StaticObjectNudgeType {
    kSmallVehicle = 0,
    kLargeVehicle = 1,
    kOtherStatic = 2,
};

struct AggregateStaticObjectNudgeConfig {
    std::vector<double> station_inside_sl_boundary_static_max_speed;
    std::vector<double> close_object_distance;
    std::vector<double> lane_width_vec;
    std::vector<double> lane_width_buffers;
    absl::string_view debug_name;
};

struct AggregateStaticObjectBucket {
    std::vector<Segment2d> segments;
    std::vector<Segment2d> segments_consider_mirrors;
    bool has_object_within_lane = false;
};

StaticObjectNudgeType GetStaticObjectNudgeType(
    const SpacetimeObjectTrajectory &traj) {
    if ((traj.object_type() == ObjectType::OT_LARGE_VEHICLE) ||
        IsLargeVehicle(traj.planner_object().object_proto())) {
        return StaticObjectNudgeType::kLargeVehicle;
    }
    if (traj.object_type() == ObjectType::OT_VEHICLE) {
        return StaticObjectNudgeType::kSmallVehicle;
    }
    return StaticObjectNudgeType::kOtherStatic;
}

enum class LaneChangeDefensiveSide {
    kNone = 0,
    kLeft = 1,
    kRight = 2,
};

LaneChangeDefensiveSide GetLaneChangeDefensiveSide(
    const LaneChangeStateProto &lane_change_state) {
    const PushState push_state =
        lane_change_state.has_push_state()
            ? lane_change_state.push_state()
            : PushState::NONE_PUSH;
    switch (push_state) {
        case PushState::LEFT_PUSH:
        case PushState::CONGESTION_LEFT_PUSH:
            return LaneChangeDefensiveSide::kLeft;
        case PushState::RIGHT_PUSH:
        case PushState::CONGESTION_RIGHT_PUSH:
            return LaneChangeDefensiveSide::kRight;
        case PushState::NONE_PUSH:
            break;
    }
    if (lane_change_state.has_lc_left()) {
        return lane_change_state.lc_left() ? LaneChangeDefensiveSide::kLeft
                                           : LaneChangeDefensiveSide::kRight;
    }
    return LaneChangeDefensiveSide::kNone;
}

bool IsLaneChangeDefensiveTarget(
    LaneChangeDefensiveSide side,
    double init_object_l) {
    constexpr double kSideEps = 0.1;
    if (std::abs(init_object_l) < kSideEps) {
        return false;
    }
    return (side == LaneChangeDefensiveSide::kLeft &&
            init_object_l > 0.0) ||
           (side == LaneChangeDefensiveSide::kRight &&
            init_object_l < 0.0);
}

AggregateStaticObjectNudgeConfig GetAggregateStaticObjectNudgeConfig(
    StaticObjectNudgeType nudge_type) {
    switch (nudge_type) {
        case StaticObjectNudgeType::kLargeVehicle:
            return {{3.0, 10.0, 20.0, 30.0},
                    {0.75, 0.8, 0.9, 1.1},
                    {2.7, 2.8, 2.9, 3.0, 4.0},
                    {0.05, 0.05, 0.05, 0.10, 0.45},
                    "Large Vehicle"};
        case StaticObjectNudgeType::kSmallVehicle:
            return {{3.0, 10.0, 20.0, 30.0},
                    {0.65, 0.7, 0.8, 1.0},
                    {2.7, 2.8, 2.9, 3.0, 4.0},
                    {0.05, 0.05, 0.05, 0.05, 0.40},
                    "Small Vehicle"};
        case StaticObjectNudgeType::kOtherStatic:
            return {{3.0, 10.0, 20.0, 30.0},
                    {0.60, 0.65, 0.75, 0.90},
                    {2.7, 2.8, 2.9, 3.0, 4.0},
                    {0.05, 0.05, 0.05, 0.05, 0.25},
                    "Other Static"};
    }
    return {// station_inside_sl_boundary_static_max_speed 自车速度区间
            {3.0, 10.0, 20.0, 30.0},
            // close_object_distance ： 自车3m/s 时，基础 buffer 是 0.65 m
            {0.65, 0.7, 0.8, 1.0},
            // lane_width_vec：车道宽度区间
            {2.7, 2.8, 2.9, 3.0, 4.0},
            // lane_width_buffers：对应 lane_width_vec 的额外 buffer
            {0.05, 0.05, 0.05, 0.05, 0.40},
            "Small Vehicle"};
}

// 预测轨迹可能出现不满足运动学的情况（速度突变/角速度异常/加速度异常等）。
struct KinematicsCheckResult {
    bool ok = true;
    const char *reason = "";
    int failed_index = -1;      // 失败发生的索引位置，便于调试
    double failed_value = 0.0;  // 失败时的具体数值
};

KinematicsCheckResult CheckObjectTrajectoryKinematics(
    absl::Span<const SpacetimeObjectState> sampled_states) {
    KinematicsCheckResult ret;
    if (sampled_states.size() < 3) {
        return ret;
    }

    // ---- 可调阈值（保守） ----
    constexpr double kMinDt = 1e-3;
    constexpr double kMaxAbsV = 60.0;       // m/s
    constexpr double kMaxAbsA = 12.0;       // m/s^2
    constexpr double kMaxAbsJerk = 30.0;    // m/s^3
    constexpr double kMaxAbsYawRate = 2.0;  // rad/s
    constexpr double kMaxAbsYawAcc = 6.0;   // rad/s^2
    // kappa consistency (kappa ~= yaw_rate / v)
    // 低速下 kappa 数值会被放大，因此需要做保护。
    constexpr double kMinKappaSpeed = 1.0;    // m/s
    constexpr double kMaxAbsKappa = 0.7;      // 1/m
    constexpr double kMaxAbsKappaRate = 1.2;  // 1/(m*s)

    // 辅助函数：安全获取轨迹点属性，空指针返回 NaN 以便后续检测
    auto get_t = [](const SpacetimeObjectState &s) -> double {
        return s.traj_point ? s.traj_point->t()
                            : std::numeric_limits<double>::quiet_NaN();
    };
    auto get_theta = [](const SpacetimeObjectState &s) -> double {
        return s.traj_point ? s.traj_point->theta()
                            : std::numeric_limits<double>::quiet_NaN();
    };
    auto get_v = [](const SpacetimeObjectState &s) -> double {
        return s.traj_point ? s.traj_point->v()
                            : std::numeric_limits<double>::quiet_NaN();
    };
    auto get_a = [](const SpacetimeObjectState &s) -> double {
        return s.traj_point ? s.traj_point->a()
                            : std::numeric_limits<double>::quiet_NaN();
    };

    auto check_value = [&ret](double val, double max_abs, const char *reason,
                              int index) -> bool {
        if (!std::isfinite(val) || std::abs(val) > max_abs) {
            ret.ok = false;
            ret.reason = reason;
            ret.failed_index = index;
            ret.failed_value = val;
            return false;
        }
        return true;
    };

    // 第一遍遍历：检查基础状态量 (v, a)
    for (int i = 0; i < static_cast<int>(sampled_states.size()); ++i) {
        const std::size_t i_idx = static_cast<std::size_t>(i);
        const double v = get_v(sampled_states[i_idx]);
        const double a = get_a(sampled_states[i_idx]);
        if (!std::isfinite(v) || !std::isfinite(a)) {
            ret.ok = false;
            ret.reason = "nan_v_or_a";
            ret.failed_index = i;
            return ret;
        }
        // if (!check_value(v, kMaxAbsV, "v_too_large", i)) return ret;
        // if (!check_value(a, kMaxAbsA, "a_too_large", i)) return ret;
    }

    // 第二遍遍历：检查导数量 (yaw_rate, yaw_acc, jerk, kappa)
    double prev_yaw_rate = 0.0;
    double prev_a = get_a(sampled_states[0]);
    double prev_kappa = 0.0;
    bool kappa_initialized = false;  // 标记 kappa 是否已初始化

    for (int i = 1; i < static_cast<int>(sampled_states.size()); ++i) {
        const std::size_t i_idx = static_cast<std::size_t>(i);
        const double dt =
            get_t(sampled_states[i_idx]) - get_t(sampled_states[i_idx - 1U]);
        if (!(dt > kMinDt) || !std::isfinite(dt)) {
            ret.ok = false;
            ret.reason = "bad_dt";
            ret.failed_index = i;
            ret.failed_value = dt;
            return ret;
        }

        // yaw_rate 检查
        const double dtheta = NormalizeAngle(get_theta(sampled_states[i_idx]) -
                                             get_theta(sampled_states[i_idx - 1U]));
        const double yaw_rate = dtheta / dt;
        if (!check_value(yaw_rate, kMaxAbsYawRate, "yaw_rate_abnormal", i)) {
            return ret;
        }

        // yaw_acc 检查：跳过第一次迭代（i==1），因为 prev_yaw_rate 初始化为 0
        // if (i > 1) {
        //     const double yaw_acc = (yaw_rate - prev_yaw_rate) / dt;
        //     if (!check_value(yaw_acc, kMaxAbsYawAcc, "yaw_acc_abnormal", i))
        //     {
        //         return ret;
        //     }
        // }

        // kappa 检查：kappa ~= yaw_rate / v
        // v 可能为 0（行人/静止障碍物），低速时不做强约束以避免误判
        const double v_i = std::abs(get_v(sampled_states[i_idx]));
        if (v_i >= kMinKappaSpeed) {
            const double kappa = yaw_rate / v_i;
            if (!check_value(kappa, kMaxAbsKappa, "kappa_abnormal", i)) {
                return ret;
            }
            // kappa_rate 检查：只在 kappa 已初始化后才检查
            // if (kappa_initialized) {
            //     const double kappa_rate = (kappa - prev_kappa) / dt;
            //     if (!check_value(kappa_rate, kMaxAbsKappaRate,
            //                      "kappa_rate_abnormal", i)) {
            //         return ret;
            //     }
            // }
            prev_kappa = kappa;
            kappa_initialized = true;
        }
        prev_yaw_rate = yaw_rate;

        // jerk 检查
        // const double a = get_a(sampled_states[i]);
        // const double jerk = (a - prev_a) / dt;
        // if (!check_value(jerk, kMaxAbsJerk, "jerk_abnormal", i)) {
        //     return ret;
        // }
        // prev_a = a;
    }

    return ret;
}

boost::optional<double> SolveCatchDist(const double &acc,
                                       const double &v0,
                                       const double &v1,
                                       const double &s0) {
    constexpr double kEpsilon = 1e-5;
    if (s0 <= kEpsilon) {
        return 0.0;
    }
    const double coefficient_a = 0.5 * acc;
    const double coefficient_b = (v0 - v1);
    const double coefficient_c = -s0;
    if (acc < kEpsilon) {
        if (coefficient_b < kEpsilon) {
            return boost::none;
        }
        return s0 * v0 / coefficient_b;
    }

    const double discriminant =
        (coefficient_b * coefficient_b) - (4.0 * coefficient_a * coefficient_c);
    if (discriminant < 0.0) {
        return boost::none;
    }
    const double sqrt_d = std::sqrt(discriminant);
    const double t1 = (-coefficient_b - sqrt_d) / (2.0 * coefficient_a);
    const double t2 = (-coefficient_b + sqrt_d) / (2.0 * coefficient_a);

    double t_catch = -1.0;
    if (t1 > 0.0 && t2 > 0.0) {
        t_catch = std::min(t1, t2);
    } else if (t1 > 0.0) {
        t_catch = t1;
    } else if (t2 > 0.0) {
        t_catch = t2;
    } else {
        return boost::none;
    }

    double catch_dist = (v0 * t_catch) + (0.5 * acc * t_catch * t_catch);
    return catch_dist;
}

boost::optional<std::vector<SpacetimeObjectState>> VRUTrajectoryCorrection(
    const int plan_id,
    const int &dense_trajectory_steps,
    const int &sparse_trajectory_steps,
    const double &dense_trajectory_time_step,
    const double &sparse_trajectory_time_step,
    const LaneChangeStage lc_stage,
    const bool borrow_lane,
    std::string obj_id,
    const ObjectType &obj_type,
    const std::vector<SpacetimeObjectState> &states,
    bool is_stationary,
    const double &object_velocity,
    const FrenetBox &object_frenet_box,
    const double &heading_diff_cos,
    const double &speed_diff,
    const double &obj_av_cross,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_boundary,
    const VehicleGeometryParamsProto &veh_geo_params,
    const double &use_follow_time,
    const TrajectoryPoint &init_start_point,
    const NudgeObjectInfo *prev_nudge_object_info,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    std::string &debug_string) {
    debug_string = absl::StrFormat("task:%d,obj id:%s,obj type:%d \n", plan_id,
                                   obj_id, static_cast<int>(obj_type));

    if (!cost_weight_params.object_cost_params().enable_correction_vru()) {
        absl::StrAppend(&debug_string, "function off!");
        return boost::none;
    }

    if (!IsVulnerableRoadUserType(obj_type) ||
        (lc_stage != LaneChangeStage::LCS_NONE)) {
        absl::StrAppend(&debug_string,
                        absl::StrFormat("return,is vru: %d,lc: %d",
                                        static_cast<int>(
                                            IsVulnerableRoadUserType(obj_type)),
                                        static_cast<int>(lc_stage)));
        return boost::none;
    }

    if (states.size() < 3) {
        absl::StrAppend(&debug_string, absl::StrFormat("return,size < 3"));
        return boost::none;
    }

    if (!borrow_lane && cost_weight_params.object_cost_params()
                            .only_correction_vru_in_borrow()) {
        absl::StrAppend(&debug_string, "not borrow task");
        return boost::none;
    }

    constexpr double speed_debounce = -1.5;
    if (is_stationary || speed_diff < speed_debounce) {
        absl::StrAppend(
            &debug_string,
            absl::StrFormat("return, is static:%d,spd_diff:%f",
                            static_cast<int>(is_stationary), speed_diff));
        return boost::none;
    }
    if (object_velocity > 16) {
        absl::StrAppend(
            &debug_string,
            absl::StrFormat("object too fast,spd:%f,return", object_velocity));
        return boost::none;
    }

    constexpr double KCos45DegreesValue = 0.707;
    if (heading_diff_cos <= KCos45DegreesValue) {
        absl::StrAppend(
            &debug_string,
            absl::StrFormat("return,heading_diff_cos:%f", heading_diff_cos));
        return boost::none;
    }

    if (object_frenet_box.s_min < veh_geo_params.front_edge_to_center()) {
        absl::StrAppend(&debug_string,
                        absl::StrFormat("return,s_min:%f,vehicle_front:%f",
                                        object_frenet_box.s_min,
                                        veh_geo_params.front_edge_to_center()));
        return boost::none;
    }

    const auto obj_station =
        drive_passage.FindNearestStationAtS(object_frenet_box.s_max);
    const auto ego_station = drive_passage.FindNearestStationAtS(
        veh_geo_params.front_edge_to_center());
    if (obj_station.is_in_intersection() || ego_station.is_in_intersection()) {
        absl::StrAppend(
            &debug_string,
            absl::StrFormat(
                "return,vru smax :%f,vehicle_front:%f,in intersection!",
                object_frenet_box.s_max,
                veh_geo_params.front_edge_to_center()));
        return boost::none;
    }
    const bool is_contain_intersection = drive_passage.ContainIntersection(10);
    constexpr double kProhibitedCorrectionDist = 30.0;
    constexpr double kConsiderIntersectionDist = 150.0;
    const double dist_to_intersection =
        drive_passage.GetDistanceToIntersection(init_start_point.pos());
    if (dist_to_intersection < kConsiderIntersectionDist &&
        dist_to_intersection > 0.0 && prev_nudge_object_info == nullptr) {
        if (dist_to_intersection < kProhibitedCorrectionDist) {
            absl::StrAppend(&debug_string,
                            absl::StrFormat("return,dist to intersection :%f!",
                                            dist_to_intersection));
            return boost::none;
        }
        const double max_acc =
            ads_x::planning::VehicleSpeedConfigHelper::GetMaxAcceleration();
        const double current_acc = init_start_point.a();
        const double pursuit_acc = std::max(
            0.0, current_acc > max_acc ? current_acc
                                       : ((current_acc + max_acc) * 0.5));
        const double pursuit_dist =
            object_frenet_box.s_max - veh_geo_params.front_edge_to_center();
        auto target_dist = SolveCatchDist(pursuit_acc, init_start_point.v(),
                                          object_velocity, pursuit_dist);

        if (target_dist.has_value()) {
            absl::StrAppend(
                &debug_string,
                absl::StrFormat(
                    "max_acc:%f,current_acc:%f,pursuit_acc:%f,pursuit_dist:%f,"
                    "target_dist:%f,dist_to_intersection:%f\n",
                    max_acc, current_acc, pursuit_acc, pursuit_dist,
                    target_dist.value(), dist_to_intersection));
            if (target_dist.value() + kProhibitedCorrectionDist >
                dist_to_intersection) {
                absl::StrAppend(&debug_string,
                                "return,approaching the intersection!");
                return boost::none;
            }
        }
    }

    auto calculateAbsCurvature = [](const Vec2d &front_pos,
                                    const Vec2d &target_pos,
                                    const Vec2d &back_pos) {
        double x0 = front_pos.x(), y0 = front_pos.y();
        double x1 = target_pos.x(), y1 = target_pos.y();
        double x2 = back_pos.x(), y2 = back_pos.y();
        double dx1 = x1 - x0, dy1 = y1 - y0;
        double dx2 = x2 - x0, dy2 = y2 - y0;
        double dx3 = x2 - x1, dy3 = y2 - y1;

        double numerator = 2 * std::abs((dx1 * dy2) - (dx2 * dy1));
        double denominator = std::sqrt(((dx1 * dx1) + (dy1 * dy1)) *
                                       ((dx2 * dx2) + (dy2 * dy2)) *
                                       ((dx3 * dx3) + (dy3 * dy3)));

        return denominator < 1e-6 ? 0.0 : numerator / denominator;
    };
    const Vec2d &front_station_pos =
        drive_passage.FindNearestStation(init_start_point.pos()).xy();
    const Vec2d &target_station_pos =
        drive_passage.FindNearestStation(states.front().traj_point->pos()).xy();
    const Vec2d &back_station_pos =
        drive_passage.FindNearestStation(states.back().traj_point->pos()).xy();
    const auto lane_kappa = calculateAbsCurvature(
        front_station_pos, target_station_pos, back_station_pos);
    constexpr double kSafeKappa = 0.002;
    absl::StrAppend(&debug_string,
                    absl::StrFormat("traj_size:%d,lane_kappa:%f\n",
                                    states.size(), lane_kappa));
    if (lane_kappa > kSafeKappa) {
        absl::StrAppend(&debug_string, "not safe kappa.return");
        return boost::none;
    }

    double lane_boundary_left_offset = std::numeric_limits<double>::infinity();
    double lane_boundary_right_offset =
        -std::numeric_limits<double>::infinity();
    for (double sample_s = object_frenet_box.s_min;
         sample_s <= object_frenet_box.s_max; sample_s += 0.5) {
        const auto lane_boundary =
            drive_passage.QueryEnclosingLaneBoundariesAtS(sample_s);
        if (!lane_boundary.left.has_value() ||
            !lane_boundary.right.has_value()) {
            absl::StrAppend(&debug_string, "query lane boundary fail,return!");
            return boost::none;
        }
        lane_boundary_left_offset =
            std::min(lane_boundary_left_offset, lane_boundary.left->lat_offset);
        lane_boundary_right_offset = std::max(lane_boundary_right_offset,
                                              lane_boundary.right->lat_offset);
    }
    const bool object_on_target_lane =
        (object_frenet_box.center_l() < lane_boundary_left_offset &&
         object_frenet_box.center_l() > lane_boundary_right_offset);
    absl::StrAppend(
        &debug_string,
        absl::StrFormat("in_lane:%d,center_l:%f,boundary:%f,%f\n",
                        static_cast<int>(object_on_target_lane),
                        object_frenet_box.center_l(), lane_boundary_left_offset,
                        lane_boundary_right_offset));
    if (borrow_lane && !object_on_target_lane) return boost::none;

    int object_on_target_lane_count = 1;
    double object_l_min = object_frenet_box.l_min;
    double object_l_max = object_frenet_box.l_max;
    double object_s_at_l_min = object_frenet_box.center_s();
    double object_s_at_l_max = object_frenet_box.center_s();
    constexpr double KTrajectoryOccupancyPrecent = 0.5;
    std::vector<FrenetBox> object_frenet_boxs;
    object_frenet_boxs.reserve(states.size());
    object_frenet_boxs.push_back(object_frenet_box);
    for (size_t i = 1; i < states.size(); ++i) {
        const auto object_station_point =
            drive_passage.FindNearestStation(states[i].traj_point->pos());
        if (object_station_point.station_info().turn_type !=
            ads_x::planning::TurnType::NO_TURN) {
            absl::StrAppend(&debug_string, "has turn type lane ,return!");
            return boost::none;
        }
        const auto frenet_box_dt_or =
            drive_passage.QueryFrenetBoxAtContour(states[i].contour);
        if (!frenet_box_dt_or.ok()) {
            absl::StrAppend(&debug_string, "query frenet box fail,return!");
            return boost::none;
        }
        const auto frenet_box_dt = frenet_box_dt_or.value();
        object_frenet_boxs.push_back(frenet_box_dt);
        if (borrow_lane) {
            const auto boundary = drive_passage.QueryEnclosingLaneBoundariesAtS(
                frenet_box_dt.center_s());
            if (!boundary.left.has_value() || !boundary.right.has_value()) {
                absl::StrAppend(&debug_string,
                                "query lane boundary fail,return!");
                return boost::none;
            }
            if (frenet_box_dt.center_l() < boundary.left->lat_offset &&
                frenet_box_dt.center_l() > boundary.right->lat_offset) {
                object_on_target_lane_count++;
            }
        }
        if (frenet_box_dt.l_min < object_l_min) {
            object_l_min = frenet_box_dt.l_min;
            object_s_at_l_min = frenet_box_dt.center_s();
        }
        if (frenet_box_dt.l_max > object_l_max) {
            object_l_max = frenet_box_dt.l_max;
            object_s_at_l_max = frenet_box_dt.center_s();
        }
    }
    absl::StrAppend(
        &debug_string,
        absl::StrFormat("count:%d,obj_l_max:%f,%f,obj_l_min:%f,%f\n",
                        object_on_target_lane_count, object_l_max,
                        object_s_at_l_max, object_l_min, object_s_at_l_min));

    const double delta_l_max = object_l_max - object_frenet_box.l_max;
    const double delta_l_min = object_frenet_box.l_min - object_l_min;
    const auto target_boundary_at_l_max =
        drive_passage.QueryEnclosingLaneBoundariesAtS(object_s_at_l_max);
    if (!target_boundary_at_l_max.left.has_value() ||
        !target_boundary_at_l_max.right.has_value()) {
        absl::StrAppend(&debug_string,
                        "query lane boundary at lmax fail,return!");
        return boost::none;
    }
    if (borrow_lane) {
        const double occ_precent =
            static_cast<double>(object_on_target_lane_count) / static_cast<double>(states.size());
        const double risk_l_max =
            (target_boundary_at_l_max.left->lat_offset * 0.5);
        constexpr double kRiskDeltaLMax = 0.5;
        bool is_borrow_risk_traj =
            object_frenet_box.center_l() < 0.0
                ? ((delta_l_max > kRiskDeltaLMax) && (object_l_max > risk_l_max))
                : (object_l_max > risk_l_max);
        absl::StrAppend(
            &debug_string,
            absl::StrFormat(
                "delta_l_max:%f,center_l:%f,state_size:%f,occ_precent:%"
                "f,risk_l_max:%f,risk_traj:%d\n",
                delta_l_max, object_frenet_box.center_l(), states.size(),
                occ_precent, risk_l_max,
                static_cast<int>(is_borrow_risk_traj)));
        if (is_borrow_risk_traj || (occ_precent < KTrajectoryOccupancyPrecent))
            return boost::none;
    } else {
        constexpr double kRiskFactor = 0.4;
        constexpr double kRiskMaxDeltaL = 2.0;
        const double risk_delta_l =
            ((target_boundary_at_l_max.left->lat_offset -
              target_boundary_at_l_max.right->lat_offset) *
             kRiskFactor);
        const bool is_risk_traj =
            (object_frenet_box.center_l() < 0.0 ? (delta_l_max > risk_delta_l)
                                              : (delta_l_min > risk_delta_l)) ||
            (std::max(delta_l_max, delta_l_min) > kRiskMaxDeltaL);
        absl::StrAppend(
            &debug_string,
            absl::StrFormat("risk_delta_l:%f,center_l:%f,delta_l_max:%"
                            "f,delta_l_min:%f,is_risk_traj:%d\n",
                            risk_delta_l, object_frenet_box.center_l(),
                            delta_l_max, delta_l_min,
                            static_cast<int>(is_risk_traj)));
        if (is_risk_traj) return boost::none;
    }

    constexpr double kBorrowSafeBufferTime = 0.3;
    constexpr double kLkFollowTime = 0.5;
    constexpr double kFollowSMin = 2.5;
    constexpr double kMinFollowTime = 0.3;
    constexpr double kMaxFollowTime = 1.8;
    const double follow_time =
        std::max(kMinFollowTime,
                 std::min(kMaxFollowTime,
                          (borrow_lane ? use_follow_time - kBorrowSafeBufferTime
                                       : kLkFollowTime)));
    const double s_correction_offset =
        (object_velocity * follow_time) + kFollowSMin;
    absl::StrAppend(
        &debug_string,
        absl::StrFormat("obj_spd:%f,orin_time:%f,follow_time:%f,s_c:%f\n",
                        object_velocity, use_follow_time, follow_time,
                        s_correction_offset));

    double l_correction = 0.0;
    bool correction_l_max = false;
    bool correction_l_min = false;
    constexpr double l_safe_buffer = 0.0;
    if (object_frenet_box.center_l() < 0.0 &&
        (obj_av_cross < 0.0 && obj_av_cross > -0.5) &&
        !(!object_on_target_lane && object_l_max > 0.0)) {
        correction_l_max = true;
        l_correction = object_l_max + l_safe_buffer;
    }
    if (object_frenet_box.center_l() >= 0.0 &&
        (obj_av_cross > 0.0 && obj_av_cross < 0.5) &&
        !(!object_on_target_lane && object_l_min < 0.0)) {
        correction_l_min = true;
        l_correction = object_l_min - l_safe_buffer;
    }
    absl::StrAppend(
        &debug_string,
        absl::StrFormat("c_l_max:%d,c_l_min:%d,c_l:%f\n",
                        static_cast<int>(correction_l_max),
                        static_cast<int>(correction_l_min), l_correction));
    int correction_idx = 0;
    if (follow_time <= static_cast<double>(dense_trajectory_steps) * dense_trajectory_time_step) {
        correction_idx = static_cast<int>(
            std::ceil(follow_time / dense_trajectory_time_step));
    } else {
        correction_idx = static_cast<int>(std::ceil(
                             ((follow_time - static_cast<double>(dense_trajectory_steps) *
                                                 dense_trajectory_time_step) /
                              sparse_trajectory_time_step))) +
                         dense_trajectory_steps;
    }
    absl::StrAppend(&debug_string,
                    absl::StrFormat("correction idx:%d\n", correction_idx));
    constexpr double s_safety_buffer = 3.0;
    std::vector<SpacetimeObjectState> correction_trajectory(states);
    if (correction_trajectory.size() != object_frenet_boxs.size()) {
        absl::StrAppend(&debug_string, "error size,return!");
        return boost::none;
    }
    for (size_t i = static_cast<size_t>(correction_idx); i < correction_trajectory.size(); ++i) {
        const double box_s_max = object_frenet_boxs[i].s_max;
        const double box_s_min = std::min(
            object_frenet_boxs[i].s_min,
            std::max((object_frenet_boxs[i].s_min - s_correction_offset),
                     veh_geo_params.front_edge_to_center() + s_safety_buffer));
        const double box_l_max =
            correction_l_max ? l_correction : object_frenet_boxs[i].l_max;
        const double box_l_min =
            correction_l_min ? l_correction : object_frenet_boxs[i].l_min;
        const auto box_front_right_point =
            drive_passage.QueryPointXYAtSL(box_s_max, box_l_min);
        const auto box_back_right_point =
            drive_passage.QueryPointXYAtSL(box_s_min, box_l_min);
        const auto box_front_left_point =
            drive_passage.QueryPointXYAtSL(box_s_max, box_l_max);
        const auto box_back_left_point =
            drive_passage.QueryPointXYAtSL(box_s_min, box_l_max);
        if (!box_front_right_point.ok() || !box_back_right_point.ok() ||
            !box_front_left_point.ok() || !box_back_left_point.ok()) {
            absl::StrAppend(&debug_string, "query xy point fail,return!");
            return boost::none;
        }
        std::vector<Vec2d> obj_box_corner_points = {
            box_front_left_point.value(), box_back_left_point.value(),
            box_back_right_point.value(), box_front_right_point.value()};
        auto &state = correction_trajectory[i];
        state.contour = Polygon2d(obj_box_corner_points);
    }
    absl::StrAppend(&debug_string, "correction finish!");
    return correction_trajectory;
}

// 障碍物类型枚举
enum class ObjectBehaviorType {
    NORMAL = 0,                  // 普通障碍物
    CUTTING_IN = 1,              // 前方切入障碍物
    ONCOMING = 2,                // 对向障碍物
    CUTTING_IN_FROM_BEHIND = 3,  // 后方切入障碍物
    CROSSING = 4,  // 前方切入且L符号翻转（穿越参考线）
    CROSSING_FROM_BEHIND = 5  // 后方切入且L符号翻转（穿越参考线）
};

// 判断障碍物行为类型（cutting in / oncoming / normal）
struct ObjectBehaviorInfo {
    ObjectBehaviorType type = ObjectBehaviorType::NORMAL;
    int index = -1;  // 发生行为的索引位置
};

ObjectBehaviorInfo IsCuttingOncomingObject(
    const SpacetimeObjectTrajectory &traj,
    const FrenetFrame &ref_path,
    const std::vector<TrajectoryPoint> &ego_traj,
    const VehicleGeometryParamsProto &veh_geo_params) {
    namespace bgs = boost::geometry::strategy::buffer;
    namespace bg = boost::geometry;
    using Point = bg::model::d2::point_xy<double>;
    using Line = bg::model::linestring<Point>;
    using Polygon = bg::model::polygon<Point>;

    int index = -1;
    if (traj.states().size() < 2) {
        return {ObjectBehaviorType::NORMAL, index};
    }

    const auto &obj_traj = traj.trajectory().points();
    const int size = static_cast<int>(obj_traj.size());
    if (size < 2) {
        return {ObjectBehaviorType::NORMAL, index};
    }

    if (ego_traj.empty()) {
        return {ObjectBehaviorType::NORMAL, index};
    }

    // ---- 可调阈值 ----
    const double kVehicleWidth = veh_geo_params.width();  // 使用真实车宽
    constexpr double kEnvelopeShrink = 0.3;  // 预期包络缩减（米）
    constexpr double kOncomingAngleThreshold = 2.356;  // 135度（弧度）
    constexpr double kBehindThresholdS = -2.0;   // 后方判定阈值（米）
    constexpr double kLateralThreshold = 2.0;    // 横向距离阈值（米）
    constexpr double kCuttingTrajMaxTime = 3.0;  // 仅检查3s内轨迹

    const double half_width = (kVehicleWidth / 2.0) - kEnvelopeShrink;

    // ---- 获取自车当前在参考线上的frenet坐标 ----
    FrenetCoordinate ego_sl;
    Vec2d ego_normal;
    int ego_ref_index = -1;
    double ego_alpha = 0.0;
    ref_path.XYToSL(ego_traj.front().pos(), &ego_sl, &ego_normal,
                    &ego_ref_index, &ego_alpha);

    if (ego_ref_index < 0 || ego_ref_index >= ref_path.points().size()) {
        return {ObjectBehaviorType::NORMAL, index};
    }

    // ---- 采样障碍物轨迹点并获取frenet坐标 (优化：仅投影第一个点) ----
    const auto &first_pt = obj_traj.front();
    Vec2d first_obj_pos{first_pt.pos().x(), first_pt.pos().y()};
    FrenetCoordinate first_obj_sl;
    Vec2d first_normal;
    int first_ref_index = -1;
    double first_alpha = 0.0;
    ref_path.XYToSL(first_obj_pos, &first_obj_sl, &first_normal,
                    &first_ref_index, &first_alpha);

    // ---- 判断是否为 oncoming 障碍物 ----
    if (first_ref_index >= 0 && first_ref_index < ref_path.points().size()) {
        // 获取参考线在障碍物位置的切线方向

        // 计算参考线切线角度
        Vec2d ref_tangent{1.0, 0.0};
        if (first_ref_index + 1 < ref_path.points().size()) {
            const std::size_t fri = static_cast<std::size_t>(first_ref_index);
            const auto &pt1 = ref_path.points()[fri];
            const auto &pt2 = ref_path.points()[fri + 1U];
            ref_tangent =
                Vec2d{pt2.x() - pt1.x(), pt2.y() - pt1.y()}.normalized();
        }
        const double ref_heading = std::atan2(ref_tangent.y(), ref_tangent.x());

        // 计算航向差
        const double heading_diff =
            std::abs(NormalizeAngle(first_pt.theta() - ref_heading));

        // 如果航向差大于135度，认为是对向车
        if (heading_diff > kOncomingAngleThreshold) {
            return {ObjectBehaviorType::ONCOMING, index};
        }
    }

    // ---- 判断障碍物初始位置是否在自车后方 ----
    bool is_initially_behind = false;
    double ds = first_obj_sl.s - ego_sl.s;
    if (ds < kBehindThresholdS) {
        is_initially_behind = true;
    }

    // ---- 获取障碍物轨迹状态 ----
    const auto &obj_states = traj.states();

    // ---- 获取障碍物初始位置的frenet坐标用于判断是否cutting ----
    const double initial_lateral_dist = std::abs(first_obj_sl.l);

    // ---- 遍历障碍物轨迹，检查是否从侧面切入参考线预期包络区域 (使用SL检查
    // 代替 geometry buffer) ---- 降采样步长
    constexpr int kCheckStep = 3;

    const double initial_l = first_obj_sl.l;
    bool is_cutting = false;
    bool is_crossing = false;

    for (int k = 0; k < static_cast<int>(obj_states.size()); k += kCheckStep) {
        const auto &state = obj_states[static_cast<std::size_t>(k)];
        if (state.traj_point->t() > kCuttingTrajMaxTime) {
            break;
        }

        // 获取当前状态的frenet坐标
        Vec2d obj_pos = state.traj_point->pos();
        FrenetCoordinate obj_sl;
        Vec2d normal_temp;
        int ref_index_temp = -1;
        double alpha_temp = 0.0;
        ref_path.XYToSL(obj_pos, &obj_sl, &normal_temp, &ref_index_temp,
                        &alpha_temp);

        // 只检查在自车前方的障碍物（后方切入情况除外）
        if (!is_initially_behind && obj_sl.s < ego_sl.s - 5.0) {
            continue;
        }

        // 已确认 cutting，后续只需检查 L 符号是否翻转（跳过粗筛）
        if (is_cutting) {
            if (initial_l * obj_sl.l < 0.0) {
                is_crossing = true;
                break;
            }
            continue;
        }

        // 粗筛：如果中心点L过大，直接跳过 (假设车宽最大3m)
        if (std::abs(obj_sl.l) > half_width + 2.5) {
            continue;
        }

        const auto &obj_contour = state.contour;
        const auto &obj_points = obj_contour.points();
        if (obj_points.size() < 3) {
            continue;
        }

        bool intersects = false;
        // 检查多边形顶点是否进入半宽区域
        for (const auto &pt : obj_points) {
            FrenetCoordinate pt_sl;
            Vec2d pt_normal;
            int pt_idx = -1;
            double pt_alpha = 0.0;
            ref_path.XYToSL(Vec2d(pt.x(), pt.y()), &pt_sl, &pt_normal, &pt_idx,
                            &pt_alpha);
            if (std::abs(pt_sl.l) < half_width) {
                intersects = true;
                break;
            }
        }

        // 检查是否与参考线膨胀区域相交
        if (intersects && initial_lateral_dist > kLateralThreshold) {
            index = k;
            is_cutting = true;
            // 当前点也检查一下 crossing
            if (initial_l * obj_sl.l < 0.0) {
                is_crossing = true;
                break;
            }
        }
    }

    if (is_cutting) {
        if (is_initially_behind) {
            return {is_crossing ? ObjectBehaviorType::CROSSING_FROM_BEHIND
                                : ObjectBehaviorType::CUTTING_IN_FROM_BEHIND,
                    index};
        } else {
            return {is_crossing ? ObjectBehaviorType::CROSSING
                                : ObjectBehaviorType::CUTTING_IN,
                    index};
        }
    }

    // 没有相交，判断为普通障碍物
    return {ObjectBehaviorType::NORMAL, index};
}

// Cutting-in crossing 障碍物轨迹截断：
// crossing 判断已在 IsCuttingOncomingObject 中完成，这里直接截断。
void CorrectCuttingInTrajectoryAfterCrossing(
    int crossing_index,
    absl::Span<const SpacetimeObjectState> raw_states,
    std::vector<SpacetimeObjectState> *sampled_states) {
    if ((sampled_states == nullptr) || sampled_states->empty()) return;
    if ((crossing_index < 0) ||
        (crossing_index >= static_cast<int>(raw_states.size()))) {
        return;
    }

    const double crossing_t = raw_states[static_cast<std::size_t>(crossing_index)].traj_point->t();
    for (size_t k = 0; k < sampled_states->size(); ++k) {
        if ((*sampled_states)[k].traj_point->t() >= crossing_t) {
            const size_t keep = std::max(k, static_cast<size_t>(1));
            sampled_states->resize(keep);
            return;
        }
    }
}

void DumpCuttingInCorrectionCsv(
    const std::string &csv_path,
    const DrivePassage &drive_passage,
    const std::vector<TrajectoryPoint> &ego_traj,
    const std::vector<SpacetimeObjectState> &states_before,
    const std::vector<SpacetimeObjectState> &states_after) {
    // 线程安全的帧计数器
    static std::atomic<int> frame_counter{0};
    const int frame_id = frame_counter.fetch_add(1);

    // 第一帧覆盖写（带 header），后续帧追加
    const bool is_first_frame = frame_id == 0;
    std::ofstream ofs(csv_path, is_first_frame ? std::ios::out : std::ios::app);
    if (!ofs.is_open()) {
        LOG_WARN("[CuttingInDump] failed to open " << csv_path);
        return;
    }
    ofs << std::fixed << std::setprecision(6);

    if (is_first_frame) {
        ofs << "frame_id,type,index,t,cx,cy,s,l,theta,"
               "contour_x0,contour_y0,"
               "contour_x1,contour_y1,"
               "contour_x2,contour_y2,"
               "contour_x3,contour_y3\n";
    }

    // helper: 写一行 contour 数据
    auto write_contour = [&](const Polygon2d &contour) {
        const auto &pts = contour.points();
        for (int ci = 0; ci < 4; ++ci) {
            if (ci < static_cast<int>(pts.size())) {
                ofs << "," << pts[ci].x() << "," << pts[ci].y();
            } else {
                ofs << ",0,0";
            }
        }
    };

    // 1) 参考线
    const auto &stations = drive_passage.stations();
    int ref_i = 0;
    for (const auto &st : stations) {
        ofs << frame_id << ",ref_line," << ref_i << ",0," << st.xy().x() << ","
            << st.xy().y() << "," << st.accumulated_s() << ",0,0,"
            << "0,0,0,0,0,0,0,0\n";
        ++ref_i;
    }

    // 2) 自车轨迹
    for (int i = 0; i < static_cast<int>(ego_traj.size()); ++i) {
        const std::size_t i_idx = static_cast<std::size_t>(i);
        const auto &pt = ego_traj[i_idx];
        ofs << frame_id << ",ego," << i << "," << pt.t() << "," << pt.pos().x()
            << "," << pt.pos().y() << "," << pt.s() << ",0," << pt.theta()
            << ","
            << "0,0,0,0,0,0,0,0\n";
    }

    // 3) 障碍物修改前
    for (int i = 0; i < static_cast<int>(states_before.size()); ++i) {
        const std::size_t i_idx = static_cast<std::size_t>(i);
        const auto &state = states_before[i_idx];
        const auto fb_or = drive_passage.QueryFrenetBoxAtContour(state.contour);
        double s = 0.0, l = 0.0;
        if (fb_or.ok()) {
            s = fb_or->center_s();
            l = fb_or->center_l();
        }
        ofs << frame_id << ",obj_before," << i << "," << state.traj_point->t()
            << "," << state.traj_point->pos().x() << ","
            << state.traj_point->pos().y() << "," << s << "," << l << ","
            << state.traj_point->theta();
        write_contour(state.contour);
        ofs << "\n";
    }

    // 4) 障碍物修改后 — cx/cy 用 box.center()（修正后已更新到 contour 质心）
    for (int i = 0; i < static_cast<int>(states_after.size()); ++i) {
        const std::size_t i_idx = static_cast<std::size_t>(i);
        const auto &state = states_after[i_idx];
        const auto fb_or = drive_passage.QueryFrenetBoxAtContour(state.contour);
        double s = 0.0, l = 0.0;
        if (fb_or.ok()) {
            s = fb_or->center_s();
            l = fb_or->center_l();
        }
        const auto &center = state.box.center();
        ofs << frame_id << ",obj_after," << i << "," << state.traj_point->t()
            << "," << center.x() << "," << center.y() << "," << s << "," << l
            << "," << state.traj_point->theta();
        write_contour(state.contour);
        ofs << "\n";
    }

    ofs.close();
    LOG_INFO("[CuttingInDump] frame " << frame_id << " appended to "
                                      << csv_path);
}

bool AddPartitionAvObjectCost(
    const int plan_id,
    std::string obj_id,
    const ObjectType &obj_type,
    const LaneChangeStage lc_stage,
    const bool borrow_lane,
    const NudgeInfos &nudge_info,
    const ObjectDecisions &object_decisions,
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
    const PathTimeCorridor &path_time_corridor,
    double avoid_dynamic_obj_early_time,
    std::string base_name,
    const std::vector<double> &nudge_buffer,
    const std::vector<bool> &has_curb,
    bool consider_mirrors,
    const std::vector<SpacetimeObjectState> &states,
    const std::vector<TrajectoryPoint> &init_traj,
    bool is_stationary,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_boundary,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    const std::unique_ptr<AvModelHelper<Mfob>> &av_model_helpers,
    std::string traj_id,
    double probability,
    const Vec2d &object_velocity,
    const VehicleGeometryParamsProto &veh_geo_params,
    const double use_follow_time,
    const NudgeObjectInfo *prev_nudge_object_info,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs,
    const std::unique_ptr<CenterLineQueryHelper<Mfob>> &stations_query_helper,
    ObjectBehaviorType behavior_type,
    const std::vector<double> &weight_gains,
    const std::string &traj_check_res) {
    using ObjectCost = PartitionedObjectCost<Mfob>;
    XCHECK_GT(dense_trajectory_time_step, 0.0);
    XCHECK_GT(dense_trajectory_steps, 0);

    constexpr double kSafeBufferNormal = 0.5;
    constexpr double kSafeBufferSameDirectionVRU = 0.6;
    constexpr double kHighWayTTC = 6.0;
    // 静转动：低速障碍物gain保底阈值
    constexpr double kLowSpeedObjVThreshold = 2.5;
    double safe_buffer_base = kSafeBufferNormal;
    const int num_points = static_cast<int>(states.size());

    std::vector<double> cascade_gains = {
        cost_weight_params.object_cost_params().object_b_cost_weight(),
        cost_weight_params.object_cost_params().object_a_cost_weight()};

    const double heading_diff_cos = std::cos(NormalizeAngle(
        init_traj.front().theta() - states.front().box.heading()));
    const auto object_frenet_box_output =
        drive_passage.QueryFrenetBoxAtContour(states[0].contour);
    if (!object_frenet_box_output.ok()) {
        return false;
    }
    const auto &object_frenet_box = object_frenet_box_output.value();
    const double object_s = object_frenet_box.center_s();
    const double object_l = object_frenet_box.center_l();
    const Vec2d av_local_dir =
        Vec2d::FastUnitFromAngle(init_traj.front().theta());
    const double obj_v_av_local = object_velocity.dot(av_local_dir);
    const double speed_diff = init_traj.front().v() - obj_v_av_local;
    double ds = std::max(
        object_frenet_box.s_min - veh_geo_params.front_edge_to_center(), 0.0);
    double ttc = ds / ((std::abs(speed_diff)) + 0.001);

    const auto object_position_info =
        path_time_corridor.QueryObjectPositionInfo(obj_id);
    const Vec2d obj_local_dir =
        Vec2d::FastUnitFromAngle(states.front().box.heading());
    double obj_av_cross = obj_local_dir.CrossProd(av_local_dir);

    const auto &plan_start_frenet_point =
        drive_passage.QueryFrenetCoordinateAt(init_traj.front().pos());
    const auto lane_heading =
        drive_passage.QueryTangentAngleAtS(plan_start_frenet_point->s);
    if (!lane_heading.ok()) {
        return false;
    }
    const Vec2d unit_cur_lane = Vec2d::FastUnitFromAngle(*lane_heading);
    double lane_av_cross = unit_cur_lane.CrossProd(av_local_dir);
    double lane_obj_cross = obj_local_dir.CrossProd(unit_cur_lane);
    const std::string plan_id_and_obj_id =
        absl::StrFormat("opt_task_%d,%s", plan_id, obj_id);

    if (!is_stationary && IsVulnerableRoadUserType(obj_type) &&
        (heading_diff_cos >= 0.707)) {
        safe_buffer_base = kSafeBufferSameDirectionVRU;
    }
    // 非机动车，同向，ttc范围内，l方向范围内
    if (!is_stationary && IsVulnerableRoadUserType(obj_type) && ttc < 3.0 &&
        heading_diff_cos > 0.0 && std::abs(object_l) < 5.0) {
        // 障碍物在自车右侧，方向在30°以内 (基本同向)
        if (object_position_info.at(0).position_type ==
                PathTimeCorridor::PositionType::POSITION_RIGHT &&
            obj_av_cross < 0.0 && obj_av_cross > -0.5) {
            double cost_a_vru_wight = boost::algorithm::clamp(
                std::abs(obj_av_cross) * 600.0,
                cost_weight_params.object_cost_params().object_a_cost_weight(),
                300.0);
            cascade_gains = {200.0, cost_a_vru_wight};
        }
        // 障碍物在自车左侧，方向在30°以内 (基本同向)
        if (object_position_info.at(0).position_type ==
                PathTimeCorridor::PositionType::POSITION_LEFT &&
            obj_av_cross > 0.0 && obj_av_cross < 0.5) {
            double cost_a_vru_wight = boost::algorithm::clamp(
                std::abs(obj_av_cross) * 600.0,
                cost_weight_params.object_cost_params().object_a_cost_weight(),
                300.0);
            cascade_gains = {200.0, cost_a_vru_wight};
        }
    }
    // 针对机动车
    if (!is_stationary &&
        (obj_type == OT_LARGE_VEHICLE || obj_type == OT_VEHICLE) &&
        ttc < kHighWayTTC && heading_diff_cos > 0.0 &&
        std::abs(object_l) < 5.0) {
        if (object_position_info.at(0).position_type ==
                PathTimeCorridor::PositionType::POSITION_RIGHT &&
            obj_av_cross < 0.0 && obj_av_cross > -0.5) {
            double cost_a_car_wight = boost::algorithm::clamp(
                std::abs(obj_av_cross) * 400.0,
                cost_weight_params.object_cost_params().object_a_cost_weight(),
                200.0);
            cascade_gains = {200.0, cost_a_car_wight};
        }
        if (object_position_info.at(0).position_type ==
                PathTimeCorridor::PositionType::POSITION_LEFT &&
            obj_av_cross > 0.0 && obj_av_cross < 0.5) {
            double cost_a_car_wight = boost::algorithm::clamp(
                std::abs(obj_av_cross) * 400.0,
                cost_weight_params.object_cost_params().object_a_cost_weight(),
                200.0);
            cascade_gains = {200.0, cost_a_car_wight};
        }
    }

    // heading_diff_cos ≥ 0.707 ≈ 同向（≤45°），≤ -0.707 ≈ 反向（≥135°）。
    if (heading_diff_cos < -0.707 && !IsVulnerableRoadUserType(obj_type) &&
        object_position_info.at(0).position_type ==
            PathTimeCorridor::PositionType::POSITION_LEFT &&
        ttc < 3.0 && std::abs(object_l) < 5.0) {
        double cost_a_oppsite_wight = boost::algorithm::clamp(
            speed_diff * 4.0 * std::max(1.0, lane_av_cross * 20.0),

            cost_weight_params.object_cost_params().object_a_cost_weight(),
            300.0);
        cascade_gains = {
            cost_weight_params.object_cost_params().object_b_cost_weight(),
            cost_a_oppsite_wight};
    }

    google::protobuf::RepeatedPtrField<
        ::pnc_x::VehicleCircleModelParamsProto_CircleParams>
        circles = trajectory_optimizer_vehicle_model_params.circles();
    if (consider_mirrors) {
        for (const auto &circle :
             trajectory_optimizer_vehicle_model_params.mirror_circles()) {
            *circles.Add() = circle;
        }
    }

    const int circle_size = static_cast<int>(circles.size());
    std::vector<double> dists_to_rac;
    std::vector<double> angles_to_axis;
    std::vector<double> circles_radius;
    dists_to_rac.reserve(static_cast<std::size_t>(circle_size));
    angles_to_axis.reserve(static_cast<std::size_t>(circle_size));
    circles_radius.reserve(static_cast<std::size_t>(circle_size));

    double max_model_dist = 0.0;
    for (const auto &circle : circles) {
        dists_to_rac.push_back(circle.dist_to_rac());
        angles_to_axis.push_back(circle.angle_to_axis());
        circles_radius.push_back(circle.radius());

        max_model_dist = std::max(max_model_dist, circle.dist_to_rac());
    }

    std::vector<ObjectCost::filter> filters;
    std::vector<std::vector<ObjectCost::Object>> objects;
    objects.resize(static_cast<std::size_t>(num_points));
    filters.resize(static_cast<std::size_t>(num_points));

    const PiecewiseConstFunction<double, double> nudge_buffer_time_gain_pcf =
        PiecewiseConstFunctionFromProto(cost_weight_params.object_cost_params()
                                            .nudge_buffer_time_gain_pcf());

    const PiecewiseConstFunction<double, double>
        large_vehicle_nudge_buffer_time_gain_pcf =
            PiecewiseConstFunctionFromProto(
                cost_weight_params.object_cost_params()
                    .large_vehicle_nudge_buffer_time_gain_pcf());
    const PiecewiseConstFunction<double, double>
        small_vehicle_nudge_buffer_time_gain_pcf =
            PiecewiseConstFunctionFromProto(
                cost_weight_params.object_cost_params()
                    .small_vehicle_nudge_buffer_time_gain_pcf());
    struct FakeSpacetimeObjectState {
        Vec2d traj_point;
        Polygon2d contour;
    };
    std::vector<FakeSpacetimeObjectState> fake_states;
    bool is_num_points_add_fake = false;
    int fake_obj_num = 0;

    std::string debug_string;
    boost::optional<std::vector<SpacetimeObjectState>> correction_states;
    const auto &use_states =
        correction_states.has_value() ? correction_states.value() : states;

    const auto &decay_nudge_gain_func = PiecewiseLinearFunctionFromProto(
        cost_weight_params.object_cost_params().decay_nudge_gain_with_speed());
    double ego_v = init_traj.front().v();
    double decay_nudge_gain = decay_nudge_gain_func(ego_v);
    constexpr double kEps = 1e-3;
    bool trigger_decay_nudge_gain = (decay_nudge_gain + kEps) < 1.0;

    for (int k = 0; k < num_points; ++k) {
        const std::size_t k_idx = static_cast<std::size_t>(k);
        double max_buffer_plus_radius = 0.0;
        const std::vector<double> nudge_buffers = {safe_buffer_base,
                                                   nudge_buffer.at(k_idx)};
        bool has_curb_k = has_curb.at(k_idx);
        auto &objects_k = objects[k_idx];
        Vec2d x;
        Vec2d obj_x;
        Polygon2d contour;
        x = init_traj[k_idx].pos();
        const auto &traj_point = *(use_states[k_idx].traj_point);

        obj_x = use_states[k_idx].box.center();
        contour = use_states[k_idx].contour;

        double t = 0.0;
        if (k <= dense_trajectory_steps) {
            t = static_cast<double>(k) * dense_trajectory_time_step;
        } else {
            const int sparse_offset = k - dense_trajectory_steps;
            t = (static_cast<double>(sparse_offset) *
                 sparse_trajectory_time_step) +
                (static_cast<double>(dense_trajectory_steps) *
                 dense_trajectory_time_step);
        }
        double gain = is_stationary ? 1.0 : nudge_buffer_time_gain_pcf(t);
        double large_vehicle_gain =
            is_stationary ? 1.0 : large_vehicle_nudge_buffer_time_gain_pcf(t);
        double small_vehicle_gain =
            is_stationary ? 1.0 : small_vehicle_nudge_buffer_time_gain_pcf(t);

        if (obj_type == OT_LARGE_VEHICLE) {
            gain = large_vehicle_gain;
        }

        if (obj_type == OT_VEHICLE) {
            gain = small_vehicle_gain;
        }

        if (has_curb_k || behavior_type == ObjectBehaviorType::CUTTING_IN ||
            behavior_type == ObjectBehaviorType::CROSSING) {
            double decay_gain = cost_weight_params.object_cost_params()
                                    .decay_nudge_gain_with_cutting();
            gain *= decay_gain;
        } else if (trigger_decay_nudge_gain) {
            gain *= decay_nudge_gain;
        }

        if ((behavior_type == ObjectBehaviorType::CUTTING_IN_FROM_BEHIND) ||
            (behavior_type == ObjectBehaviorType::CROSSING_FROM_BEHIND)) {
            constexpr double kBehindCutGainScale = 0.05;
            gain *= kBehindCutGainScale;
        }

        // 静转动：低速障碍物gain保底，防止衰减链导致避让幅度骤降
        // constexpr double kLowSpeedGainFloor = 0.8;
        // if (obj_v_av_local >= 0.0 && obj_v_av_local < kLowSpeedObjVThreshold &&
        //     behavior_type == ObjectBehaviorType::NORMAL) {
        //     trigger_decay_nudge_gain =
        //         false;  // 不触发衰减，保持低速障碍物较高的gain
        //     gain = std::max(gain, kLowSpeedGainFloor);
        // }

        const auto object_station_point =
            drive_passage.FindNearestStation(obj_x);
        const double heading_point_diff_cos = std::cos(
            NormalizeAngle(init_traj[k_idx].theta() - use_states[k_idx].box.heading()));
        bool is_oppsite_obj_point = heading_point_diff_cos < -0.707;
        std::vector<double> gain_point = {1.0, 1.0};
        if (object_station_point.station_info().turn_type ==
                ads_x::planning::TurnType::RIGHT_TURN &&
            object_station_point.is_in_intersection() && is_oppsite_obj_point) {
            if (obj_type == OT_LARGE_VEHICLE) {
                gain_point = {10.0, 10.0};
            } else {
                gain_point = {6.0, 6.0};
            }
        }

        if (k_idx < weight_gains.size()) {
            for (auto &gp : gain_point) {
                gp *= weight_gains[k_idx];
            }
        }

        for (int idx = 0; idx < circle_size; ++idx) {
            const std::size_t idx_sz = static_cast<std::size_t>(idx);
            max_buffer_plus_radius =
                std::max(max_buffer_plus_radius,
                         (*std::max_element(nudge_buffers.begin(),
                                            nudge_buffers.end())) +
                             circles[idx].radius());

            const Vec2d tangent = Vec2d::FastUnitFromAngle(
                init_traj[k_idx].theta() + angles_to_axis[idx_sz]);
            const Vec2d x_center = x + tangent * dists_to_rac[idx_sz];
            std::vector<Segment2d> lines;
            Vec2d ref_x;
            Vec2d ref_tangent;
            double offset = 0.0;
            const double circle_radius = circles_radius[idx_sz];
            CalcPartitionHalfContourInfo(
                x_center, obj_x, contour,
                (*std::max_element(nudge_buffers.begin(),
                                   nudge_buffers.end())) +
                    circle_radius,
                &lines, &ref_x, &ref_tangent, &offset);
            XCHECK(!lines.empty());
            std::vector<double> circle_buffers = nudge_buffers;
            for (int i = 0; i < circle_buffers.size(); ++i) {
                circle_buffers[i] = (nudge_buffers[i] * gain) + circle_radius;
            }
            objects_k.push_back(
                ObjectCost::Object{.lines = lines,
                                   .buffers = std::move(circle_buffers),
                                   .gains = gain_point,
                                   .ref_x = ref_x,
                                   .offset = offset,
                                   .ref_tangent = ref_tangent,
                                   .enable = true});
        }

        Vec2d ref_x = {0.0, 0.0};
        Vec2d ref_tangent = {0.0, 0.0};
        for (const auto &object : objects_k) {
            ref_x += object.ref_x;
            ref_tangent += object.ref_tangent;
        }
        ref_x /= static_cast<double>(objects_k.size());
        ref_tangent /= static_cast<double>(objects_k.size());
        ref_tangent = ref_tangent.normalized();

        Vec2d front;
        Vec2d back;
        int front_index;
        int back_index;
        contour.ExtremePoints(ref_tangent, &back_index, &front_index, &back,
                              &front);
        const double filter_offset = max_buffer_plus_radius + max_model_dist;
        const double offset = (front - ref_x).dot(ref_tangent) + filter_offset;

        ObjectCost::filter &filter = filters[k_idx];
        filter.ref_x = std::move(ref_x);
        filter.ref_tangent = std::move(ref_tangent);
        filter.offset = offset;
    }

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << decay_nudge_gain;
    std::string decay_gain = oss.str();

    // _low_speed_gain 只描述 NORMAL 障碍物走 ego 低速衰减/保底链路的情况；
    // cut-in 对象已经通过 _cutting_xxx 记录切入增益，避免 debug 同时出现
    // "_cutting" 和 "_low_speed_gain" 造成误读。
    std::string ego_low_speed_decay =
        trigger_decay_nudge_gain && behavior_type == ObjectBehaviorType::NORMAL
            ? ("_low_speed_gain: " + decay_gain)
            : " ";
    std::string cutting_gain =
        std::to_string(cost_weight_params.object_cost_params()
                           .decay_nudge_gain_with_cutting());
    std::string is_cutting_str =
        (behavior_type == ObjectBehaviorType::CUTTING_IN ||
         behavior_type == ObjectBehaviorType::CROSSING)
            ? ("_cutting_" + cutting_gain)
            : " ";
    std::string is_cutting_behind_str =
        (behavior_type == ObjectBehaviorType::CUTTING_IN_FROM_BEHIND ||
         behavior_type == ObjectBehaviorType::CROSSING_FROM_BEHIND)
            ? "_cutting_behind_0.05"
            : " ";
    std::string is_oncoming_str =
        (behavior_type == ObjectBehaviorType::ONCOMING) ? "_oncoming" : " ";
    std::string is_crossing_str =
        (behavior_type == ObjectBehaviorType::CROSSING ||
         behavior_type == ObjectBehaviorType::CROSSING_FROM_BEHIND)
            ? "_crossing"
            : " ";
    std::string use_step = "_use_step:" + std::to_string(num_points);
    std::string use_object_step =
        (num_points == 1) ? "_use_step:1_check:" + traj_check_res : use_step;

    // 非cutingin 障碍物概率为1.0
    if (behavior_type == ObjectBehaviorType::NORMAL) {
        probability = 1.0;
    } else if (behavior_type == ObjectBehaviorType::CUTTING_IN ||
               behavior_type == ObjectBehaviorType::CROSSING) {
        if (probability < 0.55) {
            probability *= 0.5;
            is_cutting_str += "_prob_0.55_half";
        }
        probability *= cost_weight_params.object_cost_params()
                           .decay_nudge_gain_with_cutting();
    } else if (behavior_type == ObjectBehaviorType::CUTTING_IN_FROM_BEHIND ||
               behavior_type == ObjectBehaviorType::CROSSING_FROM_BEHIND) {
        if (probability < 0.55) {
            probability *= 0.5;
            is_cutting_behind_str += "_prob_0.55_half";
        }
        probability *= 0.3;
    } else if (behavior_type == ObjectBehaviorType::ONCOMING) {
        probability *= 1.3;
    }

    std::string object_traj_prob = "_prob:" + std::to_string(probability);

    const std::string object_info = absl::StrFormat(
        "Partition AV Object: for %s%s%s%s%s%s%s%s", traj_id, is_cutting_str,
        is_cutting_behind_str, is_oncoming_str, is_crossing_str,
        ego_low_speed_decay, use_object_step, object_traj_prob);

    costs->emplace_back(std::make_unique<ObjectCost>(
        std::move(objects), std::move(filters), std::move(dists_to_rac),
        std::move(angles_to_axis), std::move(cascade_gains),
        av_model_helpers.get(), std::vector<std::string>({"Inner", "Outer"}),
        true, object_info,
        probability * cost_weight_params.object_cost_weight(),
        Cost<Mfob>::CostType::GROUP_OBJECT));
    return true;
}

bool AddUnidirectionalObjectCost(
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
    std::string base_name,
    const std::vector<SpacetimeObjectState> &states,
    const std::vector<TrajectoryPoint> &init_traj,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_boundary,
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        &leading_trajs,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const MotionConstraintParamsProto &motion_constraint_params,
    std::string traj_id,
    double gain,
    std::vector<LeadingInfo> *leading_min_s,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs) {
    XCHECK_GT(dense_trajectory_time_step, 0.0);
    XCHECK_GT(dense_trajectory_steps, 0);

    XCHECK_GE(leading_min_s->size(), states.size());

    using ObjectCost = UnidirectionalObjectCost<Mfob>;
    const auto &object_cost_params = cost_weight_params.object_cost_params();

    const double follow_buffer = object_cost_params.acc_standstill_standoff();
    const double half_width = 0.5 * veh_geo_params.width();
    const std::vector<double> buffers = {
        follow_buffer + half_width,
        object_cost_params.acc_safe_standstill_standoff() + half_width};

    std::vector<ObjectCost::Object> objects;
    const int num_points = static_cast<int>(states.size());
    objects.reserve(static_cast<std::size_t>(num_points));

    double t_range = kSpacetimePlannerTrajectoryHorizon;
    const Vec2d x = init_traj.front().pos();
    const Vec2d tangent = Vec2d::FastUnitFromAngle(init_traj.front().theta());
    const double dist_to_rac =
        veh_geo_params.front_edge_to_center() - half_width;
    const Vec2d circle_center = x + (tangent * dist_to_rac);

    const auto &leading_object_proto =
        FindOrNull(leading_trajs, std::string(traj_id));
    if (leading_object_proto != nullptr &&
        !leading_object_proto->st_constraints().empty()) {
        const int st_constraints_length =
            leading_object_proto->st_constraints_size();
        t_range =
            leading_object_proto->st_constraints(st_constraints_length - 1).t();
    }

    const double plan_start_point_v = init_traj.front().v();
    const auto plan_start_point_sl_or =
        drive_passage.QueryFrenetCoordinateAt(circle_center);
    if (!plan_start_point_sl_or.ok()) {
        return false;
    }
    const double plan_start_point_s_on_drive_passage =
        plan_start_point_sl_or->s;
    double max_deceleration = motion_constraint_params.max_deceleration();

    if (!leading_object_proto->modified_trajectory().empty()) {
        const double object_a =
            leading_object_proto->modified_trajectory(0).a();
        if (object_a < 0.0) {
            max_deceleration = std::max((5.0 * (object_a - 1.0)), -10.0);
        }
    }

    const double slow_down_zero_time =
        std::max(0.0, (plan_start_point_v / -max_deceleration));
    constexpr double kPenetrationOffset = 1.0;

    for (int k = 0; k < states.size(); ++k) {
        const auto &traj_point = *states[k].traj_point;
        if (traj_point.t() > t_range) {
            break;
        }
        const Polygon2d &contour = states[k].contour;

        double t = 0.0;
        if (k <= dense_trajectory_steps) {
            t = std::min(static_cast<double>(k) * dense_trajectory_time_step,
                         slow_down_zero_time);
        } else {
            const int sparse_offset_k = k - dense_trajectory_steps;
            t = std::min((static_cast<double>(sparse_offset_k) *
                          sparse_trajectory_time_step) +
                             (static_cast<double>(dense_trajectory_steps) *
                              dense_trajectory_time_step),
                         slow_down_zero_time);
        }

        const double leading_min_s_on_drive_passage =
            plan_start_point_s_on_drive_passage + (plan_start_point_v * t) +
            (0.5 * max_deceleration * Sqr(t)) + follow_buffer + half_width -
            kPenetrationOffset;

        const auto frenet_box_or =
            drive_passage.QueryFrenetBoxAtContour(contour);
        if (!frenet_box_or.ok()) {
            break;
        }

        const auto &frenet_box = *frenet_box_or;
        if (frenet_box.s_min > path_boundary.end_s()) {
            break;
        }

        const double leading_cost_s =
            std::max(leading_min_s_on_drive_passage, frenet_box.s_min);
        (*leading_min_s)[k] = LeadingInfo{leading_cost_s, traj_point.v()};

        auto boundary_points = path_boundary.QueryBoundaryXY(leading_cost_s);
        const Vec2d &right_boundary_point = boundary_points.first;
        const Vec2d &left_boundary_point = boundary_points.second;
        Segment2d mid_line(left_boundary_point, right_boundary_point);

        objects.push_back(ObjectCost::Object{
            .dir = -mid_line.unit_direction().Perp(),
            .ref = ((mid_line.start() + mid_line.end()) * 0.5),
            .lateral_extent = mid_line.length() * 0.5,
            .buffers = buffers,
            .gains = {object_cost_params.leading_object_a_cost_weight(),
                      object_cost_params.leading_object_b_cost_weight()},
            .enable = true});
    }

    std::vector<double> dist_to_rac_vec = {dist_to_rac};
    std::vector<double> angle_to_axis_vec = {0.0};
    costs->emplace_back(std::make_unique<ObjectCost>(
        std::move(objects), std::move(dist_to_rac_vec),
        std::move(angle_to_axis_vec),
        std::vector<std::string>({SoftNameString, HardNameString}), true,
        absl::StrFormat("Leading Object (F): for %s", traj_id),
        gain * cost_weight_params.object_cost_weight(),
        Cost<Mfob>::CostType::GROUP_OBJECT));
    return true;
}

void GetClosestLeadingObjectInfo(
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
    const DrivePassage &drive_passage,
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        &leading_trajs,
    absl::Span<const SpacetimeObjectTrajectory *const> spacetime_trajs,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    boost::optional<
        std::pair<std::vector<FrenetBox>, const SpacetimeObjectTrajectory *>>
        *stationary_closest_leading_object_info,
    boost::optional<
        std::pair<std::vector<FrenetBox>, const SpacetimeObjectTrajectory *>>
        *moving_closest_leading_object_info) {
    XCHECK_GT(dense_trajectory_steps, 0);
    XCHECK_GT(dense_trajectory_time_step, 0.0);

    double stationary_closest_min_s = std::numeric_limits<double>::infinity();
    double moving_closest_min_s = std::numeric_limits<double>::infinity();
    const double acc_standstill_standoff =
        cost_weight_params.object_cost_params().acc_standstill_standoff();

    for (const auto &traj_ptr : spacetime_trajs) {
        const bool is_leading =
            leading_trajs.find(std::string(traj_ptr->traj_id())) !=
            leading_trajs.end();
        if (is_leading) {
            const Polygon2d &contour = traj_ptr->contour();
            const auto frenet_box_or =
                drive_passage.QueryFrenetBoxAtContour(contour);
            if (!frenet_box_or.ok()) {
                continue;
            }
            if (traj_ptr->is_stationary()) {
                double leading_s =
                    frenet_box_or->s_min - acc_standstill_standoff;
                if (leading_s < stationary_closest_min_s) {
                    *stationary_closest_leading_object_info = std::make_pair(
                        std::vector<FrenetBox>{*frenet_box_or}, traj_ptr);
                    stationary_closest_min_s = leading_s;
                }
            } else {
                double leading_s =
                    frenet_box_or->s_min - acc_standstill_standoff;
                if (leading_s < moving_closest_min_s) {
                    *moving_closest_leading_object_info =
                        std::make_pair(std::vector<FrenetBox>(), traj_ptr);
                    moving_closest_min_s = leading_s;
                }
            }
        }
    }
    if (moving_closest_leading_object_info->has_value() &&
        moving_closest_leading_object_info->value().second != nullptr) {
        const auto states = SampleObjectStates(
            dense_trajectory_steps, sparse_trajectory_steps,
            dense_trajectory_time_step, sparse_trajectory_time_step,
            static_cast<int>(dense_trajectory_steps + sparse_trajectory_steps),
            false,
            moving_closest_leading_object_info->value().second->states());
        std::vector<FrenetBox> &frenet_boxes =
            moving_closest_leading_object_info->value().first;
        frenet_boxes.reserve(states.size());
        for (const auto &state : states) {
            const Polygon2d &contour = state.contour;
            const auto frenet_box_or =
                drive_passage.QueryFrenetBoxAtContour(contour);
            if (!frenet_box_or.ok()) {
                return;
            }
            frenet_boxes.push_back(frenet_box_or.value());
        }
    }
}

bool IgnoreObjectCost(
    std::string base_name,
    const SpacetimeObjectTrajectory &traj,
    const std::vector<SpacetimeObjectState> &sampled_states,
    const DrivePassage &drive_passage,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const boost::optional<
        std::pair<std::vector<FrenetBox>, const SpacetimeObjectTrajectory *>>
        &stationary_closest_leading_object_info,
    const boost::optional<
        std::pair<std::vector<FrenetBox>, const SpacetimeObjectTrajectory *>>
        &moving_closest_leading_object_info,
    const FrenetBox *ego_frenet_box) {
    if (!stationary_closest_leading_object_info.has_value() &&
        !moving_closest_leading_object_info.has_value()) {
        return false;
    }

    if (stationary_closest_leading_object_info.has_value() &&
        traj.traj_id() ==
            stationary_closest_leading_object_info->second->traj_id()) {
        return false;
    }

    const double acc_standstill_standoff =
        cost_weight_params.object_cost_params().acc_standstill_standoff();
    if (stationary_closest_leading_object_info.has_value()) {
        const double ignore_s =
            stationary_closest_leading_object_info->first.front().s_min;
        if (traj.is_stationary()) {
            const auto frenet_box_or =
                drive_passage.QueryFrenetBoxAtContour(traj.contour());
            if (!frenet_box_or.ok()) {
                return true;
            }
            if ((frenet_box_or->s_min - acc_standstill_standoff) < ignore_s) {
                return false;
            }
        } else {
            for (int k = 0; k < static_cast<int>(sampled_states.size()); ++k) {
                const Polygon2d &contour = sampled_states[k].contour;
                const auto frenet_box_or =
                    drive_passage.QueryFrenetBoxAtContour(contour);
                if (!frenet_box_or.ok()) {
                    return true;
                }
                if ((frenet_box_or->s_min - acc_standstill_standoff) <
                    ignore_s) {
                    return false;
                }
            }
        }
    }

    if (moving_closest_leading_object_info.has_value() &&
        traj.traj_id() ==
            moving_closest_leading_object_info->second->traj_id()) {
        return false;
    }
    if (moving_closest_leading_object_info.has_value()) {
        const std::vector<FrenetBox> &leading_frenet_boxes =
            moving_closest_leading_object_info->first;
        if (sampled_states.size() > leading_frenet_boxes.size()) {
            return false;
        }
        for (int k = 0; k < static_cast<int>(sampled_states.size()); ++k) {
            const Polygon2d &contour = sampled_states[k].contour;
            const auto frenet_box_or =
                drive_passage.QueryFrenetBoxAtContour(contour);
            if (!frenet_box_or.ok()) {
                return true;
            }
            const FrenetBox &leading_frenet_box = leading_frenet_boxes[k];
            if ((frenet_box_or->s_min - acc_standstill_standoff) <
                leading_frenet_box.s_min) {
                return false;
            }
        }
    }
    return true;
}

bool AddAggregateStaticObjectCost(
    const int plan_id,
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
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
    const VehicleGeometryParamsProto &veh_geo_params,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs) {
    AggregateStaticObjectBucket small_vehicle_bucket;
    AggregateStaticObjectBucket large_vehicle_bucket;
    AggregateStaticObjectBucket other_static_bucket;
    constexpr int kEstimateLineCountsPerObject = 6;
    XCHECK_GT(dense_trajectory_time_step, 0.0);
    XCHECK_GT(dense_trajectory_steps, 0);

    int free_index = 0;
    const double kTrajectoryStepsMinus1 = static_cast<double>(kTrajectorySteps - 1);
    if (((dense_trajectory_steps * dense_trajectory_time_step) >
         (kTrajectoryStepsMinus1 * kTrajectoryTimeStep))) {
        free_index =
            static_cast<int>(kTrajectoryStepsMinus1 * kTrajectoryTimeStep /
                             dense_trajectory_time_step);
    } else {
        free_index =
            static_cast<int>(
                ((kTrajectoryStepsMinus1 * kTrajectoryTimeStep) -
                 (dense_trajectory_steps * dense_trajectory_time_step)) /
                sparse_trajectory_time_step) +
            dense_trajectory_steps;
    }
    const std::size_t trajs_size = spacetime_trajs.size();
    const std::size_t reserve_count =
        static_cast<std::size_t>(kEstimateLineCountsPerObject) * trajs_size;
    small_vehicle_bucket.segments.reserve(reserve_count);
    small_vehicle_bucket.segments_consider_mirrors.reserve(reserve_count);
    large_vehicle_bucket.segments.reserve(reserve_count);
    large_vehicle_bucket.segments_consider_mirrors.reserve(reserve_count);
    other_static_bucket.segments.reserve(reserve_count);
    other_static_bucket.segments_consider_mirrors.reserve(reserve_count);
    const double lane_width = lane_width_l - lane_width_r;
    for (int idx = 0; idx < static_cast<int>(spacetime_trajs.size()); ++idx) {
        const auto &traj = *spacetime_trajs[idx];
        auto obejct_position = path_time_corridor.QueryObjectPositionInfo(
            std::string(traj.object_id()));
        if (obejct_position.empty()) {
            continue;
        }
        auto obj_boundary_info =
            path_time_corridor.QueryBoundaryL(obejct_position[0].object_s, 0.0);
        auto lane_width_obj = obj_boundary_info.second.l_boundary -
                              obj_boundary_info.first.l_boundary;

        constexpr double kNarrowLaneWidthThreshold = 3.0;  // m
        const bool obj_within_lane =
            ((lane_width_obj < kNarrowLaneWidthThreshold) &&
             (obejct_position[0].object_l <
                 obj_boundary_info.second.l_boundary) &&
             obejct_position[0].object_l >
                 (obj_boundary_info.first.l_boundary)) ||
            (((lane_width_obj > kNarrowLaneWidthThreshold) ||
              lane_width_obj == kNarrowLaneWidthThreshold) &&
             (obejct_position[0].object_l <
                 obj_boundary_info.second.l_boundary - 0.1) &&
             obejct_position[0].object_l >
                 obj_boundary_info.first.l_boundary + 0.1);

        AggregateStaticObjectBucket *bucket = &other_static_bucket;
        switch (GetStaticObjectNudgeType(traj)) {
            case StaticObjectNudgeType::kSmallVehicle:
                bucket = &small_vehicle_bucket;
                break;
            case StaticObjectNudgeType::kLargeVehicle:
                bucket = &large_vehicle_bucket;
                break;
            case StaticObjectNudgeType::kOtherStatic:
                bucket = &other_static_bucket;
                break;
        }
        bucket->has_object_within_lane =
            bucket->has_object_within_lane || obj_within_lane;

        const auto &object_segments = traj.contour().line_segments();

        if (IsConsiderMirrorObject(traj.planner_object().object_proto(),
                                   min_mirror_height_avg,
                                   max_mirror_height_avg)) {
            bucket->segments_consider_mirrors.insert(
                bucket->segments_consider_mirrors.end(),
                object_segments.begin(), object_segments.end());
        } else {
            bucket->segments.insert(bucket->segments.end(),
                                    object_segments.begin(),
                                    object_segments.end());
        }
    }

    if (small_vehicle_bucket.segments.empty() &&
        small_vehicle_bucket.segments_consider_mirrors.empty() &&
        large_vehicle_bucket.segments.empty() &&
        large_vehicle_bucket.segments_consider_mirrors.empty() &&
        other_static_bucket.segments.empty() &&
        other_static_bucket.segments_consider_mirrors.empty()) {
        return true;
    }

    constexpr double kSafeBuffer = 0.5;
    const auto append_bucket_cost = [&](const AggregateStaticObjectBucket
                                            &bucket,
                                        StaticObjectNudgeType nudge_type) {
        if (bucket.segments.empty() &&
            bucket.segments_consider_mirrors.empty()) {
            return;
        }

        const auto config = GetAggregateStaticObjectNudgeConfig(nudge_type);
        const PiecewiseLinearFunction<double> nudge_buffer_lane_width_plf(
            config.lane_width_vec, config.lane_width_buffers);
        const PiecewiseLinearFunction<double> nudge_buffer_speed_plf(
            config.station_inside_sl_boundary_static_max_speed,
            config.close_object_distance);
        double nudge_buffer_soft =
            std::max(kSafeBuffer, nudge_buffer_speed_plf(plan_start_point.v()));
        if (bucket.has_object_within_lane) {
            nudge_buffer_soft = std::max(
                kSafeBuffer, nudge_buffer_speed_plf(plan_start_point.v()) +
                                 nudge_buffer_lane_width_plf(lane_width));
        }

        const double nudge_buffer_hard = kSafeBuffer;
        const std::vector<double> gains = {
            cost_weight_params.object_cost_params().object_a_cost_weight(),
            cost_weight_params.object_cost_params().object_b_cost_weight()};
        const std::vector<std::string> sub_names = {"soft", "hard"};

        if (!bucket.segments.empty()) {
            std::vector<double> dist_to_rac;
            std::vector<double> angle_to_axis;
            std::vector<std::vector<double>> buffers;
            const auto &circles =
                trajectory_optimizer_vehicle_model_params.circles();
            dist_to_rac.reserve(circles.size());
            angle_to_axis.reserve(circles.size());
            buffers.reserve(circles.size());
            for (const auto &circle : circles) {
                dist_to_rac.push_back(circle.dist_to_rac());
                angle_to_axis.push_back(circle.angle_to_axis());
                buffers.push_back({nudge_buffer_soft + circle.radius(),
                                   nudge_buffer_hard + circle.radius()});
            }
            costs->push_back(std::make_unique<AggregateStaticObjectCost<Mfob>>(
                bucket.segments, std::move(dist_to_rac),
                std::move(angle_to_axis), std::move(buffers), gains, sub_names,
                free_index, true,
                absl::StrFormat("Aggregate Static Object %s",
                                config.debug_name),
                cost_weight_params.object_cost_weight(),
                Cost<Mfob>::CostType::GROUP_OBJECT));
        }

        if (!bucket.segments_consider_mirrors.empty()) {
            std::vector<double> dist_to_rac;
            std::vector<double> angle_to_axis;
            std::vector<std::vector<double>> buffers;
            const auto &circles =
                trajectory_optimizer_vehicle_model_params.circles();
            const auto &mirror_circles =
                trajectory_optimizer_vehicle_model_params.mirror_circles();
            dist_to_rac.reserve(circles.size() + mirror_circles.size());
            angle_to_axis.reserve(circles.size() + mirror_circles.size());
            buffers.reserve(circles.size() + mirror_circles.size());
            for (const auto &circle : circles) {
                dist_to_rac.push_back(circle.dist_to_rac());
                angle_to_axis.push_back(circle.angle_to_axis());
                buffers.push_back({nudge_buffer_soft + circle.radius(),
                                   nudge_buffer_hard + circle.radius()});
            }
            for (const auto &circle : mirror_circles) {
                dist_to_rac.push_back(circle.dist_to_rac());
                angle_to_axis.push_back(circle.angle_to_axis());
                buffers.push_back({nudge_buffer_soft + circle.radius(),
                                   nudge_buffer_hard + circle.radius()});
            }
            costs->push_back(std::make_unique<AggregateStaticObjectCost<Mfob>>(
                bucket.segments_consider_mirrors, std::move(dist_to_rac),
                std::move(angle_to_axis), std::move(buffers), gains, sub_names,
                free_index, true,
                absl::StrFormat("Aggregate Static Object %s Consider Mirrors",
                                config.debug_name),
                cost_weight_params.object_cost_weight(),
                Cost<Mfob>::CostType::GROUP_OBJECT));
        }
    };

    append_bucket_cost(small_vehicle_bucket,
                       StaticObjectNudgeType::kSmallVehicle);
    append_bucket_cost(large_vehicle_bucket,
                       StaticObjectNudgeType::kLargeVehicle);
    append_bucket_cost(other_static_bucket,
                       StaticObjectNudgeType::kOtherStatic);
    return true;
}

void DecayInnerPathBoundaryGains(
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_boundary,
    bool is_stationary,
    const TrajectoryPoint &plan_start_point,
    const SecondOrderTrajectoryPoint &object_pose,
    const Polygon2d &object_contour,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    std::vector<double> *path_boundary_gains,
    char *is_gain_update) {
    XCHECK(path_boundary_gains != nullptr);
    XCHECK_EQ(path_boundary_gains->size(), path_boundary.size());
    if (is_stationary) {
        bool contour_out_boundary = true;
        const auto &contour_points = object_contour.points();
        constexpr double kSafeBuffer = 0.5;
        for (const auto &pt : contour_points) {
            const auto frenet_pt = drive_passage.QueryFrenetCoordinateAt(pt);
            if (!frenet_pt.ok()) {
                return;
            }
            const auto boundary_l = path_boundary.QueryBoundaryL(frenet_pt->s);
            if ((frenet_pt->l > (boundary_l.first - kSafeBuffer)) &&
                (frenet_pt->l < (boundary_l.second + kSafeBuffer))) {
                contour_out_boundary = false;
                break;
            }
        }
        if (contour_out_boundary) return;

        *is_gain_update = true;
        const auto obj_min_dist_dp_station_pt_index =
            drive_passage.FindNearestStationIndex(object_pose.pos());
        const auto &obj_min_dist_dp_station_pt =
            drive_passage.station(obj_min_dist_dp_station_pt_index);
        const Vec2d &min_dist_dp_station_pt_theta_tangent =
            obj_min_dist_dp_station_pt.tangent();
        const double min_dist_pt_s = obj_min_dist_dp_station_pt.accumulated_s();

        Vec2d front;
        Vec2d back;
        object_contour.ExtremePoints(min_dist_dp_station_pt_theta_tangent,
                                     &back, &front);
        const double contour_length =
            (front - back).dot(min_dist_dp_station_pt_theta_tangent);

        constexpr double kGainSRangeBase = 5.0;
        constexpr double kGainSRangeCoeff = 0.5;
        const double gain_s = kGainSRangeBase +
                              (kGainSRangeCoeff * Sqr(plan_start_point.v())) +
                              (contour_length * 0.5);
        const double s_max = min_dist_pt_s + gain_s;
        const double s_min = min_dist_pt_s - gain_s;

        // constexpr double kMinGain = 0.01;
        // const auto kMinGain_func = PiecewiseLinearFunctionFromProto(
        //     cost_weight_params.path_boundary_cost_params()
        //     .decay_inner_path_boundary_gains());
        // const double kMinGain = kMinGain_func(plan_start_point.v());
        double kMinGain = cost_weight_params.path_boundary_cost_params()
                              .default_decay_inner_path_boundary_gains();
        const auto &path_boundary_s_vector = path_boundary.s_vector();
        int mid_path_boundary_index = obj_min_dist_dp_station_pt_index.value();
        for (int i = mid_path_boundary_index;
             (i < path_boundary.size()) && (path_boundary_s_vector[i] < s_max);
             ++i) {
            const double factor =
                ((s_max - path_boundary_s_vector[i]) / gain_s);
            (*path_boundary_gains)[i] =
                std::min((*path_boundary_gains)[i], std::pow(kMinGain, factor));
        }

        for (int i = std::min(mid_path_boundary_index,
                              static_cast<int>(path_boundary.size()) - 1);
             (i >= 0) && (path_boundary_s_vector[i] > s_min); --i) {
            const double factor =
                ((path_boundary_s_vector[i] - s_min) / gain_s);
            (*path_boundary_gains)[i] =
                std::min((*path_boundary_gains)[i], std::pow(kMinGain, factor));
        }
    }
}

}  // namespace

int CalcObjectTrajectoryStepsByMaxTime(
    double max_time,
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step) {
    const int trajectory_steps =
        dense_trajectory_steps + sparse_trajectory_steps;
    if (trajectory_steps <= 0 || max_time <= 0.0 ||
        dense_trajectory_time_step <= 0.0 ||
        sparse_trajectory_time_step <= 0.0) {
        return 1;
    }
    int limited_steps = 1;
    if (max_time <= dense_trajectory_steps * dense_trajectory_time_step) {
        limited_steps = static_cast<int>(max_time / dense_trajectory_time_step);
    } else {
        limited_steps =
            dense_trajectory_steps +
            static_cast<int>((max_time - dense_trajectory_steps *
                                           dense_trajectory_time_step) /
                             sparse_trajectory_time_step);
    }
    limited_steps = std::max(1, limited_steps);
    return std::min(limited_steps, trajectory_steps);
}

void AddObjectCosts(
    const int plan_id,
    const LaneChangeStage lc_stage,
    const bool borrow_lane,
    const NudgeInfos &nudge_info,
    const ObjectDecisions &object_decisions,
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
    double avoid_dynamic_obj_early_time,
    std::string base_name,
    const std::vector<TrajectoryPoint> &init_traj,
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_boundary,
    const PathTimeCorridor &path_time_corridor,
    const std::map<std::string, ConstraintProto::LeadingObjectProto>
        &leading_trajs,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const SpacetimePlannerObjectTrajectories &st_planner_object_traj,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const MotionConstraintParamsProto &motion_constraint_params,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    const std::unique_ptr<AvModelHelper<Mfob>> &av_model_helpers,
    const bool is_narrow_scene,
    std::vector<LeadingInfo> *leading_min_s,
    std::vector<double> *inner_path_boundary_gains,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs,
    ThreadPool *thread_pool,
    TurnType ego_turn_type,
    const std::vector<TrajectoryPoint> &prev_traj,
    const FrenetBox *ego_frenet_box,
    const double follow_time,
    const ObjectHistoryManager *obs_history,
    const boost::optional<bool> &is_modify_speed,
    const LaneChangeStateProto &lane_change_state,
    const NudgeObjectInfo *prev_nudge_object_info,
    const ApolloTrajectoryPointProto &plan_start_point,
    const std::unique_ptr<CenterLineQueryHelper<Mfob>> &stations_query_helper,
    std::vector<std::string> *static_object_ids) {
    const int trajectory_steps =
        dense_trajectory_steps + sparse_trajectory_steps;
    XCHECK_GT(trajectory_steps, 0);
    XCHECK_GT(dense_trajectory_time_step, 0.0);

    int free_index = 0;
    const double kTrajectoryStepsMinus1 = static_cast<double>(kTrajectorySteps - 1);
    if (((dense_trajectory_steps * dense_trajectory_time_step) >
         (kTrajectoryStepsMinus1 * kTrajectoryTimeStep))) {
        free_index =
            static_cast<int>(kTrajectoryStepsMinus1 * kTrajectoryTimeStep /
                             dense_trajectory_time_step);
    } else {
        free_index =
            static_cast<int>(
                ((kTrajectoryStepsMinus1 * kTrajectoryTimeStep) -
                 (dense_trajectory_steps * dense_trajectory_time_step)) /
                sparse_trajectory_time_step) +
            dense_trajectory_steps;
    }
    XCHECK_GE(init_traj.size(), trajectory_steps);

    const auto &spacetime_trajs = *st_planner_object_traj.trajectories;
    const int num_trajs = static_cast<int>(spacetime_trajs.size());

    std::vector<const SpacetimeObjectTrajectory *> static_spacetime_trajs;

    std::vector<const SpacetimeObjectTrajectory *> generic_spacetime_trajs;

    static_spacetime_trajs.reserve(static_cast<std::size_t>(num_trajs));
    generic_spacetime_trajs.reserve(static_cast<std::size_t>(num_trajs));
    for (const auto &traj : spacetime_trajs) {
        bool is_static_obj =
            IsStaticObjectType(traj.object_type()) || traj.is_stationary();
        bool removed_gop = traj.traj_index() == -1;
        if (removed_gop) {
            continue;
        }
        if (is_static_obj && leading_trajs.find(std::string(traj.traj_id())) ==
                                 leading_trajs.end()) {
            static_spacetime_trajs.push_back(&traj);
            static_object_ids->push_back(traj.traj_id());
        } else {
            generic_spacetime_trajs.push_back(&traj);
        }
    }

    const auto min_max_mirror_average_height =
        ComputeMinMaxMirrorAverageHeight(veh_geo_params);

    const double min_mirror_height_avg = min_max_mirror_average_height.first;
    const double max_mirror_height_avg = min_max_mirror_average_height.second;

    const auto ego_lane_boundary_info =
        drive_passage.QueryEnclosingLaneBoundariesAtS(init_traj.front().s());
    const double lane_width = ego_lane_boundary_info.left->lat_offset -
                              ego_lane_boundary_info.right->lat_offset;
    const double lane_width_l = ego_lane_boundary_info.left->lat_offset;
    const double lane_width_r = ego_lane_boundary_info.right->lat_offset;

    // 弯道外侧防御性避让ODD条件判断
    const double ego_v = init_traj.front().v();
    const double curve_look_ahead_dist = std::max(30.0, ego_v * 2.0);
    bool curve_defensive_enabled = ego_v > kCurveDefensiveMinSpeed;
    if (curve_defensive_enabled) {
        // 用init_traj的theta差分检查前方是否有连续高曲率段
        constexpr int kRequiredConsecutiveCount = 10;
        constexpr double kMinCurvatureForCurve = 0.00333;
        int consecutive_count = 0;
        curve_defensive_enabled = false;
        for (int i = 1; i < static_cast<int>(init_traj.size()); ++i) {
            const double ds = init_traj[i].s() - init_traj[i - 1].s();
            if (ds < 0.1) {
                continue;
            }
            if (init_traj[i].s() - init_traj[0].s() > curve_look_ahead_dist) {
                break;
            }
            const double kappa = std::abs(
                NormalizeAngle(init_traj[i].theta() - init_traj[i - 1].theta()) / ds);
            if (kappa > kMinCurvatureForCurve) {
                ++consecutive_count;
                if (consecutive_count >= kRequiredConsecutiveCount) {
                    curve_defensive_enabled = true;
                    break;
                }
            } else {
                consecutive_count = 0;
            }
        }
    }

    constexpr double kLaneChangeDefensiveMinEgoSpeed = 5.0;
    const bool lane_change_defensive_enabled =
        ((lc_stage == LaneChangeStage::LCS_EXECUTING) ||
         (lc_stage == LaneChangeStage::LCS_PAUSE)) &&
        (ego_v > kLaneChangeDefensiveMinEgoSpeed);
    const LaneChangeDefensiveSide lane_change_defensive_side =
        lane_change_defensive_enabled
            ? GetLaneChangeDefensiveSide(lane_change_state)
            : LaneChangeDefensiveSide::kNone;
    double ego_lat_v_t0 = 0.0;
    const auto ego_lane_heading_t0 =
        drive_passage.QueryTangentAngleAtS(init_traj.front().s());
    if (ego_lane_heading_t0.ok()) {
        ego_lat_v_t0 = init_traj.front().v() *
                       std::sin(NormalizeAngle(init_traj.front().theta() -
                                               *ego_lane_heading_t0));
    }

    AddAggregateStaticObjectCost(
        plan_id, dense_trajectory_steps, sparse_trajectory_steps,
        dense_trajectory_time_step, sparse_trajectory_time_step, base_name,
        lc_stage, init_traj.front(), path_time_corridor, static_spacetime_trajs,
        min_mirror_height_avg, max_mirror_height_avg, lane_width_l,
        lane_width_r, cost_weight_params,
        trajectory_optimizer_vehicle_model_params, veh_geo_params, costs);

    for (const auto &traj : static_spacetime_trajs) {
        char is_gain_update = false;
        DecayInnerPathBoundaryGains(
            drive_passage, path_boundary, traj->is_stationary(),
            init_traj.front(), traj->pose(), traj->contour(),
            cost_weight_params, inner_path_boundary_gains, &is_gain_update);
    }

    const int num_generic_spacetime_trajs = static_cast<int>(generic_spacetime_trajs.size());
    std::vector<std::vector<double>> inner_path_boundary_gains_all_trajs(
        static_cast<std::size_t>(num_generic_spacetime_trajs),
        std::vector<double>(inner_path_boundary_gains->size(), 1.0));
    std::vector<std::vector<std::unique_ptr<Cost<Mfob>>>> costs_all_trajs(
        static_cast<std::size_t>(num_generic_spacetime_trajs));
    std::vector<char> is_gains_update(static_cast<std::size_t>(num_generic_spacetime_trajs), false);
    std::vector<std::vector<LeadingInfo>> leading_min_s_all_trajs(
        static_cast<std::size_t>(num_generic_spacetime_trajs), *leading_min_s);

    boost::optional<
        std::pair<std::vector<FrenetBox>, const SpacetimeObjectTrajectory *>>
        stationary_closest_leading_object_info,
        moving_closest_leading_object_info;
    GetClosestLeadingObjectInfo(
        dense_trajectory_steps, sparse_trajectory_steps,
        dense_trajectory_time_step, sparse_trajectory_time_step, drive_passage,
        leading_trajs, generic_spacetime_trajs, cost_weight_params,
        &stationary_closest_leading_object_info,
        &moving_closest_leading_object_info);

    bool consider_unidirectional_object =
        is_modify_speed.has_value() ? (is_modify_speed.value() ? false : true)
                                    : true;

    auto ref_path_or =
        BuildBVHFrenetFrame(stations_query_helper->points(), false);
    XCHECK(ref_path_or.ok());
    const auto ref_path_ptr = std::move(ref_path_or).value();

    ThreadPool *used_tp =
        FLAGS_traj_opt_draw_object_canvas ? nullptr : thread_pool;
    std::vector<ObjectBehaviorInfo> obj_behavior_infos(
        num_generic_spacetime_trajs);
    ParallelFor(0, num_generic_spacetime_trajs, used_tp, [&](int i) {
        obj_behavior_infos[i] = IsCuttingOncomingObject(
            *generic_spacetime_trajs[i], *ref_path_ptr, init_traj,
            veh_geo_params);
    });

    ParallelFor(0, num_generic_spacetime_trajs, used_tp, [&](int i) {
        const auto &traj = *(generic_spacetime_trajs[i]);

        const auto &obj_behavior_info = obj_behavior_infos[i];
        const int is_cutting_index = obj_behavior_info.index;

        // 计算使用的轨迹步数
        int use_object_steps =
            static_cast<int>(dense_trajectory_steps + sparse_trajectory_steps);
        bool ignore_after_frozen = false;

        // 低速/中速场景：预测轨迹可靠性较差时，限制消费的轨迹时长
        // 目标速度 < 2.5m/s：只消费前 0.5s 轨迹
        // 目标速度在 2.5m/s～4m/s：只消费前 1.0s 轨迹
        constexpr double kLowSpeedObjectVThreshold = 2.5;
        constexpr double kLowSpeedObjectMaxTime = 0.5;
        constexpr double kMediumSpeedObjectMaxVThreshold = 4.0;
        constexpr double kMediumSpeedObjectMaxTime = 1.0;
        const double ego_v0 = init_traj.front().v();
        const double obj_v0 = traj.planner_object().velocity().Length();
        if (!traj.is_stationary()) {
            double limit_time = -1.0;
            if (obj_v0 < kLowSpeedObjectVThreshold) {
                limit_time = kLowSpeedObjectMaxTime;
            } else if (obj_v0 <= kMediumSpeedObjectMaxVThreshold) {
                limit_time = kMediumSpeedObjectMaxTime;
            }
            if (limit_time > 0.0) {
                int limit_steps = 1;
                if (limit_time <=
                    dense_trajectory_steps * dense_trajectory_time_step) {
                    limit_steps = static_cast<int>(
                        std::ceil(limit_time / dense_trajectory_time_step));
                } else {
                    limit_steps =
                        dense_trajectory_steps +
                        static_cast<int>(std::ceil(
                            (limit_time - dense_trajectory_steps *
                                              dense_trajectory_time_step) /
                            sparse_trajectory_time_step));
                }
                limit_steps = std::max(1, limit_steps);
                use_object_steps = std::min(use_object_steps, limit_steps);
            }
        }

        if (obj_behavior_info.type == ObjectBehaviorType::ONCOMING) {
            bool oncoming_in_intersection = false;
            const auto ego_station =
                drive_passage.FindNearestStationAtS(init_traj.front().s());
            oncoming_in_intersection = ego_station.is_in_intersection();
            // oncoming 目标非路口只使用前 1s 轨迹；路口内最多使用前 3s 轨迹。
            ignore_after_frozen = true;
            if (!oncoming_in_intersection) {
                constexpr double kOncomingMaxTime = 1.0;
                use_object_steps = CalcObjectTrajectoryStepsByMaxTime(
                    kOncomingMaxTime, dense_trajectory_steps,
                    sparse_trajectory_steps, dense_trajectory_time_step,
                    sparse_trajectory_time_step);
            } else {
                constexpr double kIntersectionOncomingMaxTime = 3.0;
                const int oncoming_max_steps = CalcObjectTrajectoryStepsByMaxTime(
                    kIntersectionOncomingMaxTime, dense_trajectory_steps,
                    sparse_trajectory_steps, dense_trajectory_time_step,
                    sparse_trajectory_time_step);
                use_object_steps = std::min(use_object_steps, oncoming_max_steps);
            }
        }

        // 统一做下界保护，避免采样为空
        use_object_steps = std::max(1, use_object_steps);

        // 检查预测轨迹运动学合理性，不满足时只保留第一个轨迹点
        const auto kin_check = CheckObjectTrajectoryKinematics(traj.states());
        std::string traj_check_res = " ";
        if (!kin_check.ok && traj.states().size() > 1) {
            // 只保留第一个轨迹点，避免使用不可靠的预测轨迹
            use_object_steps = 1;
            traj_check_res = kin_check.reason;
        }
        double use_follow_time = follow_time;
        bool is_nudge_obj = false;
        if (obs_history) {
            const auto obs_info =
                obs_history->GetObjLatestFrame(std::string(traj.object_id()));
            if (obs_info && obs_info->desired_follow_time_headway.has_value()) {
                use_follow_time = obs_info->desired_follow_time_headway.value();
            }
        }
        auto states = SampleObjectStates(
            dense_trajectory_steps, sparse_trajectory_steps,
            dense_trajectory_time_step, sparse_trajectory_time_step,
            use_object_steps, ignore_after_frozen, traj.states());

        if ((obj_behavior_info.type == ObjectBehaviorType::CROSSING ||
             obj_behavior_info.type ==
                 ObjectBehaviorType::CROSSING_FROM_BEHIND) &&
            is_cutting_index >= 0) {
            // const auto states_before = states;  // 保存修改前副本
            CorrectCuttingInTrajectoryAfterCrossing(is_cutting_index,
                                                    traj.states(), &states);
            // DumpCuttingInCorrectionCsv(
            //     "/home/sensetime/ws/csv_debug/cutting_in_correction_debug.csv",
            //     drive_passage, init_traj, states_before, states);
        }

        const bool ignore_object_cost = IgnoreObjectCost(
            base_name, traj, states, drive_passage, cost_weight_params,
            stationary_closest_leading_object_info,
            moving_closest_leading_object_info, ego_frenet_box);
        if (!ignore_object_cost) {
            const bool is_static = IsStaticObjectType(traj.object_type());
            const bool is_leading_object =
                leading_trajs.find(std::string(traj.traj_id())) !=
                leading_trajs.end();
            if (is_leading_object) {
                if (!cost_weight_params.object_cost_params().ignore_leading() &&
                    lc_stage != LaneChangeStage::LCS_NONE &&
                    consider_unidirectional_object) {
                    AddUnidirectionalObjectCost(
                        dense_trajectory_steps, sparse_trajectory_steps,
                        dense_trajectory_time_step, sparse_trajectory_time_step,
                        base_name, states, init_traj, drive_passage,
                        path_boundary, leading_trajs, cost_weight_params,
                        veh_geo_params, motion_constraint_params,
                        std::string(traj.traj_id()),
                        traj.trajectory().probability(),
                        &leading_min_s_all_trajs[i], &costs_all_trajs[i]);
                }
            } else {
                NudgeBufferManager nudge_buffer_manager;
                std::vector<double> nudge_buffer;
                std::vector<bool> has_curb;

                std::vector<double> weight_gains;
                const auto object_position_info =
                    path_time_corridor.QueryObjectPositionInfo(
                        std::string(traj.object_id()));
                if (traj.is_stationary() || is_static) {
                    nudge_buffer =
                        nudge_buffer_manager.GenerateNudgeBufferStationary(
                            plan_id, lc_stage, states,
                            IsCameraObject(
                                traj.planner_object().object_proto()),
                            is_static, traj.planner_object().velocity(),
                            traj.contour(), init_traj, drive_passage,
                            lane_width, cost_weight_params, veh_geo_params,
                            traj, path_boundary, path_time_corridor,
                            ego_turn_type);
                    has_curb = std::vector<bool>(nudge_buffer.size(), false);
                    weight_gains =
                        std::vector<double>(nudge_buffer.size(), 1.0);
                } else {
                    const auto &curb_nudge_info =
                        nudge_buffer_manager.GenerateNudgeBufferDynamic(
                            plan_id, lc_stage, borrow_lane, states, init_traj,
                            IsCameraObject(
                                traj.planner_object().object_proto()),
                            traj.planner_object().velocity(), traj.contour(),
                            init_traj.front(), drive_passage, lane_width,
                            cost_weight_params, veh_geo_params, traj,
                            path_boundary, path_time_corridor, ego_turn_type,
                            prev_traj);

                    nudge_buffer = curb_nudge_info.buffer_value;
                    has_curb = curb_nudge_info.has_curb;
                    weight_gains = curb_nudge_info.weight_gains;
                }

                // 弯道外侧防御性避让：对外侧障碍物额外增加buffer
                if (curve_defensive_enabled && !states.empty()) {
                    for (int k = 0; k < static_cast<int>(nudge_buffer.size()) &&
                                    k < static_cast<int>(states.size()); ++k) {
                        if (k >= static_cast<int>(object_position_info.size())) {
                            break;
                        }
                        const auto pos_type =
                            object_position_info[k].position_type;
                        if (pos_type == PathTimeCorridor::PositionType::POSITION_UNKNOWN) {
                            continue;
                        }
                        // 用init_traj对应时间步的theta差分估算signed kappa
                        const int traj_idx = std::min(k, static_cast<int>(init_traj.size()) - 2);
                        if (traj_idx < 1) {
                            continue;
                        }
                        const double ds = init_traj[traj_idx + 1].s() - init_traj[traj_idx - 1].s();
                        if (ds < 0.2) {
                            continue;
                        }
                        const double signed_kappa = NormalizeAngle(
                            init_traj[traj_idx + 1].theta() - init_traj[traj_idx - 1].theta()) / ds;
                        // 外侧判断：右弯(kappa<0)+左侧障碍物 或 左弯(kappa>0)+右侧障碍物
                        const bool is_outer =
                            (signed_kappa < 0.0 && pos_type == PathTimeCorridor::PositionType::POSITION_LEFT) ||
                            (signed_kappa > 0.0 && pos_type == PathTimeCorridor::PositionType::POSITION_RIGHT);
                        if (is_outer) {
                            const double roc = 1.0 / std::max(std::abs(signed_kappa), 1e-6);
                            nudge_buffer[k] += GetCurveDefensiveBuffer(roc);
                        }
                    }
                }

                // 变道方向防御性避让：只对初解显示会进入的那一侧目标额外加buffer
                if (lane_change_defensive_side !=
                        LaneChangeDefensiveSide::kNone &&
                    !init_traj.empty() && !object_position_info.empty()) {
                    const double object_initial_l =
                        object_position_info.front().init_object_l;
                    if (IsLaneChangeDefensiveTarget(
                            lane_change_defensive_side, object_initial_l)) {
                        const double lane_change_buffer =
                            GetLaneChangeDefensiveBuffer(std::fabs(ego_lat_v_t0));
                        for (int k = 0;
                             k < static_cast<int>(nudge_buffer.size()) &&
                             k < static_cast<int>(states.size()) &&
                             k < static_cast<int>(init_traj.size());
                             ++k) {
                            nudge_buffer[k] += lane_change_buffer;
                        }
                    }
                }

                const bool consider_mirrors = IsConsiderMirrorObject(
                    traj.planner_object().object_proto(), min_mirror_height_avg,
                    max_mirror_height_avg);

                AddPartitionAvObjectCost(
                    plan_id, std::string(traj.object_id()), traj.object_type(),
                    lc_stage, borrow_lane, nudge_info, object_decisions,
                    dense_trajectory_steps, sparse_trajectory_steps,
                    dense_trajectory_time_step, sparse_trajectory_time_step,
                    path_time_corridor, avoid_dynamic_obj_early_time, base_name,
                    nudge_buffer, has_curb, consider_mirrors, states, init_traj,
                    traj.is_stationary(), drive_passage, path_boundary,
                    cost_weight_params,
                    trajectory_optimizer_vehicle_model_params, av_model_helpers,
                    std::string(traj.traj_id()),
                    traj.trajectory().probability(),
                    traj.planner_object().velocity(), veh_geo_params,
                    use_follow_time, prev_nudge_object_info,
                    &costs_all_trajs[i], stations_query_helper,
                    obj_behavior_info.type, weight_gains, traj_check_res);
            }
            DecayInnerPathBoundaryGains(
                drive_passage, path_boundary, traj.is_stationary(),
                init_traj.front(), traj.pose(), traj.contour(),
                cost_weight_params, &inner_path_boundary_gains_all_trajs[i],
                &is_gains_update[i]);
        }
    });

    for (int idx = 0; idx < num_generic_spacetime_trajs; ++idx) {
        const auto &leading_min_s_per_traj = leading_min_s_all_trajs[idx];
        for (int i = 0; i <= free_index; ++i) {
            if (leading_min_s_per_traj[i].s < (*leading_min_s)[i].s) {
                (*leading_min_s)[i] = leading_min_s_per_traj[i];
            }
        }
        const auto &gains_per_traj = inner_path_boundary_gains_all_trajs[idx];
        if (is_gains_update[idx]) {
            for (int i = 0; i < static_cast<int>(gains_per_traj.size()); ++i) {
                (*inner_path_boundary_gains)[i] = std::min(
                    (*inner_path_boundary_gains)[i], gains_per_traj[i]);
            }
        }
    }
    for (auto &costs_per_traj : costs_all_trajs) {
        std::move(costs_per_traj.begin(), costs_per_traj.end(),
                  std::back_inserter(*costs));
    }
}

void CalcPartitionHalfContourInfo(const Vec2d &x,
                                  const Vec2d &obj_x,
                                  const Polygon2d &contour,
                                  double buffer,
                                  std::vector<Segment2d> *lines,
                                  Vec2d *ref_x,
                                  Vec2d *ref_tangent,
                                  double *offset) {
    const Vec2d force_dir = (x - obj_x).normalized();
    const Vec2d force_right = -force_dir.Perp();

    Vec2d left;
    Vec2d right;
    Vec2d front;
    Vec2d back;
    int left_index;
    int right_index;
    int front_index;
    int back_index;
    contour.ExtremePoints(force_dir, &back_index, &front_index, &back, &front);
    contour.ExtremePoints(force_right, &left_index, &right_index, &left,
                          &right);

    const auto &contour_lines = contour.line_segments();
    lines->reserve(contour_lines.size());

    constexpr double kBorderExtent = 2.0;
    const Segment2d &right_line = contour_lines[right_index];
    lines->emplace_back(right_line.start() - force_dir * kBorderExtent,
                        right_line.start());
    const std::ptrdiff_t right_idx = right_index;
    const std::ptrdiff_t left_idx = left_index;
    if ((front_index >= right_index) && (front_index <= left_index)) {
        lines->insert(lines->end(), contour_lines.begin() + right_idx,
                      contour_lines.begin() + left_idx);
    } else {
        lines->insert(lines->end(), contour_lines.begin() + right_idx,
                      contour_lines.end());
        if (left_index != 0) {
            lines->insert(lines->end(), contour_lines.begin(),
                          contour_lines.begin() + left_idx);
        }
    }

    const Segment2d &left_line =
        contour_lines[left_index == 0 ? (contour_lines.size() - 1)
                                      : (left_index - 1)];
    lines->emplace_back(left_line.end(),
                        left_line.end() - force_dir * kBorderExtent);

    *ref_x = Vec2d((left.x() + right.x()) * 0.5, (front.y() + back.y()) * 0.5);
    *ref_tangent = force_dir;
    *offset = (front - (*ref_x)).dot(force_dir) + buffer;
}

std::vector<SpacetimeObjectState> SampleObjectStates(
    int dense_trajectory_steps,
    int sparse_trajectory_steps,
    double dense_trajectory_time_step,
    double sparse_trajectory_time_step,
    int use_object_steps,
    bool ignore_after_frozen,
    absl::Span<const SpacetimeObjectState> states) {
    int trajectory_steps = dense_trajectory_steps + sparse_trajectory_steps;
    XCHECK_GT(trajectory_steps, 0);
    XCHECK_GT(dense_trajectory_time_step, 0.0);

    std::vector<SpacetimeObjectState> sampled_states;
    if (states.empty()) {
        return sampled_states;
    }

    const int frozen_after_step =
        std::min(std::max(1, use_object_steps), trajectory_steps);

    sampled_states.reserve(trajectory_steps);

    int sample_steps = 0;
    int frozen_state_index = 0;

    const int states_size = static_cast<int>(states.size());
    for (int i = 0; i < trajectory_steps; ++i) {
        if (sample_steps >= states_size) break;
        if (states.empty()) break;
        const int sample_index =
            std::min(sample_steps, states_size - 1);
        if (i < frozen_after_step) {
            frozen_state_index = sample_index;
        } else if (ignore_after_frozen) {
            break;
        }
        // Copy each selected state only once.  The old implementation first
        // assigned the state to a temporary and then copied that temporary
        // into the result; this is expensive because Polygon2d owns vectors.
        sampled_states.push_back(states[frozen_state_index]);
        const int sample_step =
            i < dense_trajectory_steps
                ? static_cast<int>(
                      (dense_trajectory_time_step / kTrajectoryTimeStep) + 0.5)
                : static_cast<int>(
                      (sparse_trajectory_time_step / kTrajectoryTimeStep) +
                      0.5);
        sample_steps += sample_step;
    }
    return sampled_states;
}
}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
