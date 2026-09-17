#include <cmath>
#include <memory>

#include <math.h>

#include "common/gflags.h"
#include "common/vehicle_speed_config_helper.h"
#include "initializer/interactive_search/search/interaction_cost.h"
#include "initializer/interactive_search/search/node.h"
#include <absl/status/status.h>
#include <absl/status/statusor.h>

namespace pnc_x {
namespace planning {

namespace {
const double V_RESOLUTION = 0.2;
const double THETA_RESOLUTION = 0.087;
const double X_RESOLUTION = 0.3;
const double Y_RESOLUTION = 0.3;

const double V_MAX = 40.0;
const double THETA_MAX = M_PI;
const double THETA_MIN = -M_PI;

constexpr double kDefaultRefSpeed = 33.3;
constexpr double kNormalizeBaseTime = 6.0;
constexpr double kNormalizeBaseReflineCost = 3.75 / 2.0 - 1.852 / 2.0;
constexpr double kNormalizeBaseLDiffCost = 3.75 / 2.0 + 0.3;
constexpr double kNormalizeBaseLaneBoundCost = 3.75 / 2.0;
constexpr double kMaxAccumulatedTime = 1000.0;
constexpr double kRadian2Degree = 180.0;

constexpr double kFarStationHorizonRatio = 1.0 - 0.3;
constexpr double kPlanningHorizon = 200.0;
constexpr double kRouteStationUnitStep = 1.0;
constexpr double kFarRouteStationStep = 2.0 * kRouteStationUnitStep;

constexpr double kMaxHalfLaneWidth = 2.7;
}  // namespace

bool Node::equal_to(const Node &rhs) const {
    return static_cast<int>(x_ / X_RESOLUTION) ==
               static_cast<int>(rhs.X() / X_RESOLUTION) &&
           static_cast<int>(y_ / Y_RESOLUTION) ==
               static_cast<int>(rhs.Y() / Y_RESOLUTION) &&
           static_cast<int>(v_ / V_RESOLUTION) ==
               static_cast<int>(rhs.V() / V_RESOLUTION) &&
           static_cast<int>(theta_ / THETA_RESOLUTION) ==
               static_cast<int>(rhs.Theta() / THETA_RESOLUTION);
}

uint64_t Node::SetIndex(const InitializerConfig &initializer_params,
                        const std::vector<double> &xy_range) {
    const auto &search_config_params =
        initializer_params.interactive_astar_search_config();
    double X_MIN = xy_range[static_cast<size_t>(0)];
    double X_MAX = xy_range[static_cast<size_t>(1)];
    double Y_MIN = xy_range[static_cast<size_t>(2)];
    double Y_MAX = xy_range[static_cast<size_t>(3)];
    uint64_t x_size = (X_MAX - X_MIN) / X_RESOLUTION;
    uint64_t y_size = (Y_MAX - Y_MIN) / Y_RESOLUTION;
    uint64_t theta_size = (THETA_MAX - THETA_MIN) / THETA_RESOLUTION;
    uint64_t v_size = V_MAX / V_RESOLUTION;
    index_ =
        (uint64_t)((accumulated_time_) /
                   search_config_params.time_resolution()) *
            x_size * y_size * theta_size * v_size +
        (uint64_t)((v_) / V_RESOLUTION) * x_size * y_size * theta_size +
        (uint64_t)((theta_ - THETA_MIN) / THETA_RESOLUTION) * x_size * y_size +
        (uint64_t)((y_ - Y_MIN) / Y_RESOLUTION) * x_size +
        (uint64_t)(x_ - X_MIN / X_RESOLUTION);
    return index_;
}

std::unique_ptr<Node> Node::CreateSuccessor(
    const std::unordered_map<uint64_t, Node> &nodes_map,
    double omega,
    double acc,
    std::vector<double> &speed_limits,
    const std::shared_ptr<SafetyCheck> &safety_checker,
    const VehicleParamsProto *vehicle_params,
    const InitializerConfig &initializer_params,
    const DrivePassage &drive_passage,
    bool is_lane_change,
    const PathSlBoundary *sl_boundary,
    const std::string &group_prefix,
    bool is_pre_safe) {
    double time_resolution =
        initializer_params.interactive_astar_search_config().time_resolution();
    double theta_succ = omega * time_resolution + theta_;
    double v_succ = v_ + acc * time_resolution;
    double mid_theta = NormalizeAngle(0.5 * (theta_ + theta_succ));
    double mid_v = 0.5 * (v_ + v_succ);
    const double cos_mid_theta = cos(mid_theta);
    const double sin_mid_theta = sin(mid_theta);
    double x_succ = x_ + time_resolution * mid_v * cos_mid_theta;
    double y_succ = y_ + time_resolution * mid_v * sin_mid_theta;
    double accumulated_time = accumulated_time_ + time_resolution;

    double omega_rate = (omega - omega_) / time_resolution;
    double jerk = (acc - acc_) / time_resolution;

    double half_time_duration = time_resolution / 2.0;
    double mid_accumulated_time = accumulated_time_ + half_time_duration;
    double mid_x_succ = x_ + half_time_duration * mid_v * cos_mid_theta;
    double mid_y_succ = y_ + half_time_duration * mid_v * sin_mid_theta;

    double s_succ = 0.0;
    double l_succ = 0.0;
    boost::optional<StationBoundary> right_boundary = boost::none;
    boost::optional<StationBoundary> left_boundary = boost::none;
    if (!IsValid(nodes_map, drive_passage, sl_boundary, x_succ, y_succ,
                 NormalizeAngle(theta_succ), v_succ, accumulated_time,
                 kMaxAccumulatedTime, speed_limits, time_resolution,
                 vehicle_params, &s_succ, &l_succ, is_lane_change, group_prefix,
                 right_boundary, left_boundary)) {
        if (FLAGS_planner_search_fail_level == 1) {
            if (is_lane_change) {
                std::vector<double> xs, ys;
                xs.push_back(x_succ);
                ys.push_back(y_succ);
            } else {
            }
        }

        return nullptr;
    }

    double ego_to_safety_dis = 0.0;
    RefVelocityInGap ref_velocity_lon;
    double ori_l_succ = 0.0;

    bool node_pred_safe = !start_ && ego_to_safety_dis_ < 1e-6;
    std::string safety_check_info = " ";
    if (!safety_checker->IsCollisionFree(
            is_lane_change, x_succ, y_succ, v_succ, theta_succ,
            accumulated_time, s_succ, l_succ, node_pred_safe,
            &ego_to_safety_dis, mid_x_succ, mid_y_succ, mid_v, mid_theta,
            mid_accumulated_time, group_prefix, &safety_check_info, is_pre_safe,
            &right_boundary, &left_boundary, &ref_velocity_lon)) {
        if (FLAGS_planner_search_fail_level == 1) {
            if (is_lane_change) {
            } else {
            }
        }

        return nullptr;
    }

    return std::make_unique<Node>(
        index_, x_succ, y_succ, theta_succ, v_succ, s_succ, l_succ, ori_l_succ,
        acc, jerk, omega, omega_rate, accumulated_time, ego_to_safety_dis,
        safety_check_info, ref_velocity_lon);
}

bool Node::IsValid(const std::unordered_map<uint64_t, Node> &nodes_map,
                   const DrivePassage &drive_passage,
                   const PathSlBoundary *sl_boundary,
                   double x_succ,
                   double y_succ,
                   double theta,
                   double v,
                   double time,
                   double time_limit,
                   std::vector<double> &speed_limits,
                   double time_reso,
                   const VehicleParamsProto *vehicle_params,
                   double *s_succ,
                   double *l_succ,
                   bool is_lane_change,
                   const std::string &group_prefix,
                   boost::optional<StationBoundary> &right_boundary,
                   boost::optional<StationBoundary> &left_boundary) {
    if (v + kEpsilon < 0.0) {
        return false;
    }
    if (time > time_limit || time_reso < kEpsilon) {
        return false;
    }

    double max_acc_jerk =
        ads_x::planning::VehicleSpeedConfigHelper::GetMaxAccelJerk();
    double max_dec_jerk =
        ads_x::planning::VehicleSpeedConfigHelper::GetMaxDecelJerk();
    if (jerk_ < max_dec_jerk || jerk_ > max_acc_jerk) {
        return false;
    }

    if (s_succ == nullptr || l_succ == nullptr ||
        !QueryXY2SLmap(drive_passage, x_succ, y_succ, s_succ, l_succ)) {
        if (FLAGS_planner_search_fail_level >= 11) {
            std::vector<double> xs, ys;
            xs.push_back(x_succ);
            ys.push_back(y_succ);
        }
        return false;
    }

    const int index = static_cast<int>(time / time_reso);
    if (index >= speed_limits.size() || v > speed_limits[index]) {
        if (FLAGS_planner_search_fail_level >= 11) {
            if (is_lane_change) {
                std::vector<double> xs, ys;
                xs.push_back(x_succ);
                ys.push_back(y_succ);
            } else {
            }
        }
        return false;
    }

    double ego_half_width =
        0.5 * vehicle_params->vehicle_geometry_params().width();
    double ego_max_l = *l_succ + ego_half_width;
    double ego_min_l = *l_succ - ego_half_width;

    auto boundaries = drive_passage.QueryEnclosingLaneBoundariesAtS(*s_succ);
    right_boundary = boundaries.right;
    left_boundary = boundaries.left;
    const double boundary_right_l =
        right_boundary.has_value()
            ? std::max(right_boundary->lat_offset, -kMaxHalfLaneWidth)
            : -kMaxHalfLaneWidth;
    const double boundary_left_l =
        left_boundary.has_value()
            ? std::min(left_boundary->lat_offset, kMaxHalfLaneWidth)
            : kMaxHalfLaneWidth;
    bool pred_node_in_lane = false;
    const auto pred_node_it = nodes_map.find(pred_index_);
    if (!start_ && pred_node_it != nodes_map.end()) {
        double pred_ego_max_l = pred_node_it->second.L() + ego_half_width;
        double pred_ego_min_l = pred_node_it->second.L() - ego_half_width;
        pred_node_in_lane = pred_ego_max_l < boundary_left_l &&
                            pred_ego_min_l > boundary_right_l;
    }

    const auto lane_boundary = sl_boundary->QueryOptBoundaryL(*s_succ);
    double right_width = lane_boundary.first;
    double left_width = lane_boundary.second;
    if (pred_node_in_lane) {
        return ego_max_l < left_width && ego_min_l > right_width;
    } else {
        if (ego_max_l > left_width || ego_min_l < right_width) {
            if (FLAGS_planner_search_fail_level >= 11) {
                if (is_lane_change) {
                    std::vector<double> xs, ys;
                    xs.push_back(x_succ);
                    ys.push_back(y_succ);
                } else {
                }
            }
            return false;
        }
    }

    return true;
}

void Node::UpdateGCost(
    const DrivePassage &drive_passage,
    double yaw_rate_limit,
    double pred_g_cost,
    bool lane_change,
    bool is_manual_lane_change,
    const InitializerConfig &initializer_params,
    const VehicleParamsProto *vehicle_params,
    const ObstacleDecisionGroup &decision_group,
    const std::unordered_map<std::string, ObstacleBehavior> *obs_behavior_map) {
    const auto &astar_config =
        initializer_params.interactive_astar_search_config();
    bool near_junction = false;

    omega_cost_ = astar_config.g_cost_weight().omega_weight() *
                  GetOmegaCost(yaw_rate_limit);

    const double omega_rate_sq = omega_rate_ * omega_rate_;
    omega_rate_cost_ = astar_config.g_cost_weight().omega_rate_weight() *
                       omega_rate_sq * omega_rate_sq;

    double acc_cost = GetAccCost(acc_);
    acc_cost_ =
        acc_ > 0.0
            ? astar_config.g_cost_weight().acc_weight() * acc_cost
            : (lane_change && is_manual_lane_change
                   ? astar_config.g_cost_weight().manual_mode_decel_weight() *
                         acc_cost
                   : astar_config.g_cost_weight().decel_weight() * acc_cost);
    const auto jerk_weight =
        (lane_change && is_manual_lane_change && acc_ < 0.0)
            ? astar_config.g_cost_weight().jerk_manual_mode_weight()
            : astar_config.g_cost_weight().jerk_weight();
    const double jerk_sq = jerk_ * jerk_;
    jerk_cost_ = jerk_weight * jerk_sq * jerk_sq;

    const double centripetal_acc = omega_ * v_;
    centripetal_acc_cost_ =
        astar_config.g_cost_weight().centripetal_acc_weight() *
        centripetal_acc * centripetal_acc;

    ref_l_cost_ =
        astar_config.g_cost_weight().ref_l_weight() * GetReflCost(lane_change);

    ref_heading_cost_ = astar_config.g_cost_weight().ref_heading_weight() *
                        GetRefHeadingCost(drive_passage, lane_change);

    interaction_cost_ = astar_config.g_cost_weight().interaction_weight() *
                        InteractionCost::GetInteractionCost(
                            vehicle_params, decision_group, obs_behavior_map,
                            accumulated_time_, s_, v_, l_, lane_change);

    g_cost_ = pred_g_cost + omega_cost_ + omega_rate_cost_ + acc_cost_ +
              jerk_cost_ + centripetal_acc_cost_ + ref_l_cost_ +
              ref_heading_cost_

              + interaction_cost_;
}

void Node::UpdateHCost(double goal_s,
                       bool is_lane_change,
                       bool is_manual_lane_change,
                       const InitializerConfig &initializer_params) {
    double diff_to_goal_s = s_ > goal_s ? 0.0 : goal_s - s_;
    double diff_l = std::fabs(l_);
    const auto &astar_config =
        initializer_params.interactive_astar_search_config();

    if (is_lane_change) {
        const auto safety_dis_weight =
            is_manual_lane_change
                ? astar_config.h_cost_weight().safety_dis_manual_mode_weight()
                : astar_config.h_cost_weight().safety_dis_weight();
        double v_lat_ref = -0.3 * l_;
        double v_lat_ = v_ * sin(diff_heading_sign_);
        double v_lon_ = v_ * cos(diff_heading_sign_);
        safety_cost_ = safety_dis_weight * ego_to_safety_dis_;

        diff_v_lat_ = std::fabs(v_lat_ref - v_lat_);
        diff_v_lon_ = 1.1 * (v_safe_to_lead_ < 0.0
                                 ? 0.0
                                 : std::fabs(v_safe_to_lead_ - v_lon_)) +
                      0.5 * (v_safe_to_tail_ < 0.0
                                 ? 0.0
                                 : std::fabs(v_safe_to_tail_ - v_lon_)) +
                      0.75 * (v_safe_to_tail_origin_ < 0.0
                                  ? 0.0
                                  : std::fabs(v_safe_to_tail_origin_ - v_lon_));

        diff_ori_s_lon_ = astar_config.h_cost_weight().ori_dis_weight() *
                          (s_safe_to_ori_ < kEpsilon ? 0.0 : s_safe_to_ori_);
        if (ego_to_safety_dis_ > 1e-6) {
            h_cost_ =
                astar_config.h_cost_weight().goal_s_weight() * diff_to_goal_s +

                astar_config.h_cost_weight().diff_v_lon_weight() * diff_v_lon_ +
                safety_cost_ + diff_ori_s_lon_;
        } else {
            h_cost_ =
                astar_config.h_cost_weight().goal_s_weight() * diff_to_goal_s +
                astar_config.h_cost_weight().goal_l_weight() * diff_l +
                astar_config.h_cost_weight().diff_v_lon_weight() * diff_v_lon_ +
                diff_v_lat_ + safety_cost_ + diff_ori_s_lon_;
        }
    } else {
        h_cost_ =
            astar_config.h_cost_weight().goal_s_weight() * diff_to_goal_s +
            astar_config.h_cost_weight().goal_l_weight() * diff_l;
    }
}

double Node::GetRefHeadingCost(const DrivePassage &drive_passage,
                               bool lane_change) {
    const auto ref_heading = drive_passage.QueryTangentAngleAtS(s_);
    if (ref_heading.ok()) {
        diff_heading_sign_ = NormalizeAngle(theta_ - *ref_heading);
        // NormalizeAngle is odd around the [-pi, pi) interval, so the
        // absolute heading error is exactly the magnitude of the signed one.
        // Avoid normalizing the same pair a second time for every successor.
        diff_heading_ = std::fabs(diff_heading_sign_);
    }

    return diff_heading_ * kRadian2Degree / M_PI;
}

double Node::GetOmegaCost(double yaw_rate_limit) const {
    return omega_ * omega_;
}

double Node::GetAccCost(double acc) const { return acc * acc; }

double Node::GetReflCost(bool lane_change) { return l_ * l_; }

void Node::SetRefVelocityInGap(const RefVelocityInGap &ref_velocity_lon) {
    v_safe_to_lead_ = ref_velocity_lon.v_to_lead;
    v_safe_to_tail_ = ref_velocity_lon.v_to_tail;
    v_safe_to_tail_origin_ = ref_velocity_lon.v_to_tail_origin;
}

}  // namespace planning
}  // namespace pnc_x
