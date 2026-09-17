#include <cmath>

#include "common/gflags.h"
#include "initializer/interactive_search/search/safety_check.h"
#include "math/linear_interpolation.h"
#include "util/map_util.h"

namespace pnc_x {
namespace planning {

using namespace ads_x::planning::math;

namespace {
constexpr double kYieldPruneLatDisBuffer = 1.5F;
constexpr double kYieldPruneLonDisBuffer = 0.0F;
constexpr double kOvertakePruneLatDisBuffer = 2.6F;
constexpr double kOvertakePruneLonDisBuffer = -0.5F;
constexpr double kMaxHalfLaneWidth = 2.7;
}  // namespace

bool SafetyCheck::IsCollisionFree(
    bool is_lane_change,
    double ego_x,
    double ego_y,
    double ego_v,
    double ego_yaw,
    double t,
    double ego_s,
    double ego_l,
    bool node_pred_safe,
    double *ego_to_safety_dis,
    double mid_ego_x,
    double mid_ego_y,
    double mid_v,
    double mid_theta,
    double mid_accumulated_time,
    const std::string &group_prefix,
    std::string *infos,
    bool is_pre_safe,
    boost::optional<StationBoundary> *target_right_boundary,
    boost::optional<StationBoundary> *target_left_boundary,
    RefVelocityInGap *ref_velocity) {
    ego_v_ = ego_v;
    ego_s_ = ego_s;
    ego_l_ = ego_l;
    ego_x_ = ego_x;
    ego_y_ = ego_y;

    double extend_front_edge_to_center =
        vehicle_params_->vehicle_geometry_params().front_edge_to_center();
    double extend_back_edge_to_center =
        vehicle_params_->vehicle_geometry_params().back_edge_to_center();
    double extend_width = vehicle_params_->vehicle_geometry_params().width();
    CalculateEgoSymmetryShape(ego_x, ego_y, ego_yaw,
                              extend_front_edge_to_center,
                              extend_back_edge_to_center, extend_width);

    if (!IsSafeWithObstacles(t, is_lane_change, node_pred_safe,
                             ego_to_safety_dis, group_prefix, infos,
                             is_pre_safe, target_right_boundary,
                             target_left_boundary, ref_velocity)) {
        return false;
    }

    return true;
}

bool SafetyCheck::IsSafeWithObstacles(
    double t,
    bool is_lane_change,
    bool node_pred_safe,
    double *ego_to_safety_dis,
    const std::string &group_prefix,
    std::string *infos,
    bool is_pre_safe,
    boost::optional<StationBoundary> *target_right_boundary,
    boost::optional<StationBoundary> *target_left_boundary,
    RefVelocityInGap *ref_velocity) {
    for (const auto &pair : decision_group_->obstacles_decision) {
        const auto &object_id = pair.first;
        const auto &obs_decision = pair.second;
        if (!IsSafeWithSingleObs(
                obs_decision, t, is_lane_change, node_pred_safe,
                ego_to_safety_dis, group_prefix, infos, is_pre_safe,
                target_right_boundary, target_left_boundary, ref_velocity)) {
            return false;
        }
    }
    return true;
}

bool SafetyCheck::IsSafeWithSingleObs(
    const ObstacleDecision &obs_decision,
    double t,
    bool is_lane_change,
    bool node_pred_safe,
    double *ego_to_safety_dis,
    const std::string &group_prefix,
    std::string *infos,
    bool is_pre_safe,
    boost::optional<StationBoundary> *target_right_boundary,
    boost::optional<StationBoundary> *target_left_boundary,
    RefVelocityInGap *ref_velocity) {
    const auto &traj = obs_decision.modified_pred_traj;
    if (traj.empty()) {
        return true;
    }
    const auto &obs_pt = traj[0];
    static constexpr double safety_buffer = 0.5;
    const auto shape_it = obstacle_shape_cache_.find(&obs_decision);
    if (shape_it != obstacle_shape_cache_.end()) {
        half_obs_length_ = shape_it->second.half_length;
        half_obs_width_ = shape_it->second.half_width;
        obs_radius_ = shape_it->second.radius;
    } else {
        half_obs_length_ = obs_pt.box_2d.half_length() + safety_buffer;
        half_obs_width_ = obs_pt.box_2d.half_width() + safety_buffer;
        obs_radius_ = std::hypot(half_obs_length_, half_obs_width_);
    }

    if (obs_decision.obs_moving_type == ObstacleMovingType::kStationary) {
        if (obs_decision.obj_id == lead_id_) {
            double ego_max_s =
                ego_s_ + vehicle_params_->vehicle_geometry_params()
                             .front_edge_to_center();
            double obs_min_s =
                obs_decision.modified_pred_traj.front().sl_boundary.s_min;
            if (ego_max_s > obs_min_s) {
                *infos += "t: " + std::to_string(t) + ", static lead " +
                          obs_decision.obj_id + " not safe.\n";
                if (FLAGS_planner_search_fail_level >= 21) {
                    std::vector<double> xs, ys;
                    xs.push_back(ego_x_);
                    ys.push_back(ego_y_);
                }
                return false;
            }
        } else {
            obs_center_.set_x(obs_pt.box_2d.center_x());
            obs_center_.set_y(obs_pt.box_2d.center_y());
            obs_yaw_ = obs_pt.box_2d.heading();

            if (PreCollisionFreeCheck()) {
                return true;
            }
            if (!CheckBox()) {
                *infos += "t: " + std::to_string(t) + ", " +
                          obs_decision.obj_id + " collide.\n";
                if (FLAGS_planner_search_fail_level >= 21) {
                    std::vector<double> xs, ys;
                    xs.push_back(ego_x_);
                    ys.push_back(ego_y_);
                }
                return false;
            }
        }
    }

    if (is_lane_change &&
        (obs_decision.obj_id == lead_id_ || obs_decision.obj_id == tail_id_ ||
         obs_decision.obj_id == ori_lead_id_)) {
        if (!CheckLCGapSafety(obs_decision, t, node_pred_safe,
                              ego_to_safety_dis, group_prefix, infos,
                              is_pre_safe, target_right_boundary,
                              target_left_boundary, ref_velocity)) {
            if (FLAGS_planner_search_fail_level >= 21) {
                std::vector<double> xs, ys;
                xs.push_back(ego_x_);
                ys.push_back(ego_y_);
            }
            return false;
        }
    }

    if (obs_decision.obj_id == lead_id_ || obs_decision.obj_id == tail_id_) {
        return true;
    }
    if (t < 3.5) {
        auto obs_info_based_time = GetDynamicObsPointByTime(obs_decision, t);
        obs_center_.set_x(obs_info_based_time.x);
        obs_center_.set_y(obs_info_based_time.y);
        obs_yaw_ = obs_info_based_time.yaw;

        if (PreCollisionFreeCheck()) {
            return true;
        }
        if (!CheckBox()) {
            if (is_lane_change) {
                if (FLAGS_planner_search_fail_level >= 21) {
                    std::vector<double> xs, ys;
                    xs.push_back(ego_x_);
                    ys.push_back(ego_y_);
                }
            }
            return false;
        }
    }

    return true;
}

bool SafetyCheck::IsObstacleLeavingTarget(const ObstacleDecision &obs_decision,
                                          const int pred_pt_index) {
    if (sl_boundary_ == nullptr || obs_decision.modified_pred_traj.empty() ||
        obs_decision.modified_pred_traj.size() <= pred_pt_index) {
        return false;
    }

    double obs_max_s =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_max;
    double obs_min_s =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_min;
    double obs_max_l =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_max;
    double obs_min_l =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_min;
    double obs_middle_s = 0.5 * (obs_max_s + obs_min_s);
    double obs_half_l = 0.5 * std::abs(obs_max_l - obs_min_l);
    double obs_middle_l = 0.5 * (obs_max_l + obs_min_l);
    double obs_x =
        obs_decision.modified_pred_traj[pred_pt_index].traj_point.pos().x();
    double obs_y =
        obs_decision.modified_pred_traj[pred_pt_index].traj_point.pos().y();

    auto boundary_pair = sl_boundary_->QueryTargetBoundaryL(obs_middle_s);
    double boundary_right_l_t = boundary_pair.first;
    double boundary_left_l_t = boundary_pair.second;
    return (obs_middle_l < boundary_right_l_t) ||
           (obs_middle_l > boundary_left_l_t);
}

void SafetyCheck::CheckEgoPosWithLane(
    bool *ego_corner_across_lane_bound,
    bool *ego_center_across_lane_bound,
    boost::optional<StationBoundary> *target_right_boundary,
    boost::optional<StationBoundary> *target_left_boundary) {
    float ego_max_l =
        ego_l_ + (0.5 * vehicle_params_->vehicle_geometry_params().width());
    float ego_min_l =
        ego_l_ - (0.5 * vehicle_params_->vehicle_geometry_params().width());
    boost::optional<StationBoundary> right_boundary = boost::none;
    boost::optional<StationBoundary> left_boundary = boost::none;
    if ((target_right_boundary == nullptr) ||
        (target_left_boundary == nullptr)) {
        auto boundaries =
            drive_passage_->QueryEnclosingLaneBoundariesAtS(ego_s_);
        right_boundary = boundaries.right;
        left_boundary = boundaries.left;
    } else {
        right_boundary = *target_right_boundary;
        left_boundary = *target_left_boundary;
    }
    const double boundary_right_l =
        right_boundary.has_value()
            ? std::max(right_boundary->lat_offset, -kMaxHalfLaneWidth)
            : -kMaxHalfLaneWidth;
    const double boundary_left_l =
        left_boundary.has_value()
            ? std::min(left_boundary->lat_offset, kMaxHalfLaneWidth)
            : kMaxHalfLaneWidth;

    *ego_corner_across_lane_bound =
        (ego_min_l < boundary_left_l) && (ego_max_l > boundary_right_l);
    *ego_center_across_lane_bound =
        (ego_l_ < boundary_left_l) && (ego_l_ > boundary_right_l);
}

bool SafetyCheck::CheckLCGapSafety(
    const ObstacleDecision &obs_decision,
    double t,
    bool node_pred_safe,
    double *ego_to_safety_dis,
    const std::string &group_prefix,
    std::string *infos,
    bool is_pre_safe,
    boost::optional<StationBoundary> *target_right_boundary,
    boost::optional<StationBoundary> *target_left_boundary,
    RefVelocityInGap *ref_velocity) {
    const int pred_pt_index = t * kDevidedByPredTrajTimeStep_;

    if (pred_pt_index >=
        static_cast<int>(obs_decision.modified_pred_traj.size())) {
        return true;
    }

    if (is_obstacle_leaving_target_table_.find(obs_decision.obj_id) !=
        is_obstacle_leaving_target_table_.end()) {
        const double time_resolution =
            initializer_params_.interactive_astar_search_config()
                .time_resolution();
        const auto &is_obstacle_leaving_target =
            is_obstacle_leaving_target_table_[obs_decision.obj_id];
        const int flag_idx =
            static_cast<int>(round(t / std::max(time_resolution, 1e-6)));
        if (flag_idx < is_obstacle_leaving_target.size() &&
            is_obstacle_leaving_target[flag_idx]) {
            return true;
        }
    }

    constexpr double kDeltaSpeed = 2.0;
    constexpr double kMinLowSpeed = 5.0;
    constexpr double kMaxLowSpeed = 25.0;
    constexpr double kMinLowSpeedCheck = 0.8;

    const double ego_max_s =
        ego_s_ +
        vehicle_params_->vehicle_geometry_params().front_edge_to_center();
    const double ego_min_s =
        ego_s_ -
        vehicle_params_->vehicle_geometry_params().back_edge_to_center();
    double obs_v =
        obs_decision.modified_pred_traj[pred_pt_index].traj_point.v();

    const auto &safety_check_param =
        initializer_params_.interactive_astar_search_config()
            .gap_safety_check_param();
    const auto &interactive_check_param =
        initializer_params_.interactive_astar_search_config()
            .interactive_param();
    const double max_lowspeed_tail_check =
        safety_check_param.tighten_low_speed_tail_dist();
    const double max_lowspeed_lead_check =
        safety_check_param.tighten_low_speed_lead_dist();
    const double tighten_large_object_dist_min =
        interactive_check_param.tighten_large_object_dist_min();
    const double tighten_large_object_dist_max =
        interactive_check_param.tighten_large_object_dist_max();
    const double tighten_large_object_tail_dist =
        lerp(tighten_large_object_dist_min, -kDeltaSpeed,
             tighten_large_object_dist_max, kDeltaSpeed, obs_v - ego_v_, true);
    const double tighten_low_speed_tail_dist =
        is_pre_safe ? 0.0
                    : lerp(max_lowspeed_tail_check, kMinLowSpeed, 0.0,
                           kMaxLowSpeed, obs_v, true);
    const double tighten_low_speed_lead_dist =
        is_pre_safe ? 0.0
                    : lerp(max_lowspeed_lead_check, kMinLowSpeed, 0.0,
                           kMaxLowSpeed, obs_v, true);

    const double v_ref_k1 = -0.2;
    const double v_ref_k2 = -0.02;
    const double v_ref_piecewise = 2.0;

    if (obs_decision.obj_id == lead_id_) {
        double obs_min_s =
            obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_min;
        double yield_s_diff = obs_min_s - ego_max_s;
        double expected_yield_dis =
            tighten_low_speed_lead_dist +
            std::max(gap_lead_thw_ * ego_v_, safety_check_param.gap_lead_dis());
        if (obs_v < ego_v_) {
            expected_yield_dis +=
                safety_check_param.gap_lead_ttc() * (ego_v_ - obs_v);
        }

        if (yield_s_diff < expected_yield_dis) {
            *ego_to_safety_dis = std::fabs(expected_yield_dis - yield_s_diff);
            absl::StrAppend(infos, absl::StrCat("-- NOT SAFE, t: ", t,
                                                ", lead ", obs_decision.obj_id,
                                                " not safe, safe dist: ",
                                                *ego_to_safety_dis, "\n"));
        }
        if (ref_velocity != nullptr) {
            double ref_gap_lead_thw = 0.5;
            double ref_follow_dis_ttc =
                (obs_v < ego_v_)
                    ? (safety_check_param.gap_lead_ttc() * (ego_v_ - obs_v))
                    : 0.0;
            double ref_follow_dis =
                std::max((ref_gap_lead_thw * ego_v_) + ref_follow_dis_ttc,
                         expected_yield_dis + 0.5);
            double ref_follow_s = obs_min_s - ref_follow_dis;
            double v_fb = PiecewiseLinearFunction(
                ego_max_s - ref_follow_s, v_ref_k1, v_ref_k2, v_ref_piecewise);
            double v_ref = std::max(v_fb + obs_v, 1e-6);
            if ((ego_v_ - v_ref) > 0.0) {
                ref_velocity->v_to_lead = v_ref;
            }
        }
    }

    bool ego_corner_across_lane_bound = false;
    bool ego_center_across_lane_bound = false;
    CheckEgoPosWithLane(&ego_corner_across_lane_bound,
                        &ego_center_across_lane_bound, target_right_boundary,
                        target_left_boundary);

    bool no_need_to_check_tail_safety =
        node_pred_safe && ego_center_across_lane_bound;
    if (no_need_to_check_tail_safety && obs_decision.obj_id == tail_id_) {
        return true;
    }

    if (obs_decision.obj_id == tail_id_) {
        const double large_object_distance =
            (obs_decision.object_type == ObjectType::OT_LARGE_VEHICLE)
                ? tighten_large_object_tail_dist
                : 0.0;
        double obs_max_s =
            obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_max;
        double overtake_s_diff = ego_min_s - obs_max_s;
        double expected_overtake_dis = (gap_tail_thw_ * obs_v) +
                                       tighten_low_speed_tail_dist +
                                       large_object_distance;
        if (obs_v > ego_v_) {
            expected_overtake_dis += gap_tail_ttc_ * (obs_v - ego_v_);
        }

        if (overtake_s_diff < expected_overtake_dis) {
            *ego_to_safety_dis =
                std::fabs(expected_overtake_dis - overtake_s_diff);
            absl::StrAppend(infos, absl::StrCat("-- NOT SAFE, t: ", t,
                                                ", tail ", obs_decision.obj_id,
                                                " not safe, safe dist: ",
                                                *ego_to_safety_dis, "\n"));
        }
        if (ref_velocity != nullptr) {
            double ref_gap_tail_thw = 0.5;
            double ref_follow_dis_ttc =
                (obs_v > ego_v_) ? (gap_tail_ttc_ * (obs_v - ego_v_)) : 0.0;
            double ref_follow_dis =
                std::max((ref_gap_tail_thw * obs_v) + ref_follow_dis_ttc,
                         expected_overtake_dis + 0.5);
            double ref_follow_s = obs_max_s + ref_follow_dis;
            double v_fb = PiecewiseLinearFunction(
                ego_min_s - ref_follow_s, v_ref_k1, v_ref_k2, v_ref_piecewise);
            double v_ref = std::min(std::max(v_fb + obs_v, 1e-6), 38.0);
            if ((ego_v_ - v_ref) < 0.0) {
                ref_velocity->v_to_tail = v_ref;
            }
        }

        if (ref_velocity != nullptr &&
            pred_pt_index <
                static_cast<int>(obs_decision.src_tail_pred_traj.size())) {
            double ori_obs_v =
                obs_decision.src_tail_pred_traj[pred_pt_index].traj_point.v();
            double ori_obs_max_s =
                obs_decision.src_tail_pred_traj[pred_pt_index]
                    .sl_boundary.s_max;

            double ori_ref_gap_tail_thw = 0.5;
            double ori_ref_follow_dis_ttc =
                (ori_obs_v > ego_v_) ? (gap_tail_ttc_ * (ori_obs_v - ego_v_))
                                     : 0.0;
            double ori_ref_follow_dis =
                (ori_ref_gap_tail_thw * ori_obs_v) + ori_ref_follow_dis_ttc;
            double ori_ref_follow_s = ori_obs_max_s + ori_ref_follow_dis;
            double v_fb =
                PiecewiseLinearFunction(ego_min_s - ori_ref_follow_s, v_ref_k1,
                                        v_ref_k2, v_ref_piecewise);
            double ori_v_ref = std::min(std::max(v_fb + ori_obs_v, 1e-6), 38.0);
            if ((ego_v_ - ori_v_ref) < 0.0) {
                ref_velocity->v_to_tail_origin = ori_v_ref;
            }
        }
    }

    if ((*ego_to_safety_dis > 1e-6) && ego_corner_across_lane_bound) {
        if (FLAGS_planner_search_fail_level == 211) {
            std::vector<double> xs, ys;
            xs.push_back(ego_x_);
            ys.push_back(ego_y_);
        }
        return false;
    }

    if (!ego_center_across_lane_bound && obs_decision.obj_id == ori_lead_id_) {
        const double vehicle_width =
            vehicle_params_->vehicle_geometry_params().width();
        float ego_max_l = static_cast<float>(ego_l_ + (0.5 * vehicle_width));
        float ego_min_l = static_cast<float>(ego_l_ - (0.5 * vehicle_width));
        double obs_min_l =
            obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_min;
        double obs_max_l =
            obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_max;
        if ((ego_min_l < obs_max_l) && (ego_max_l > obs_min_l)) {
            double obs_min_s = obs_decision.modified_pred_traj[pred_pt_index]
                                   .sl_boundary.s_min;
            double yield_s_diff = obs_min_s - ego_max_s;
            double expected_yield_dis = std::max(
                ori_lead_thw_ * ego_v_, safety_check_param.ori_lead_dis());
            double expected_cost_dis =
                std::max(safety_check_param.ori_lead_cost_thw_ratio() *
                             ori_lead_thw_ * ego_v_,
                         safety_check_param.ori_lead_cost_dis());
            if (obs_v < ego_v_) {
                expected_yield_dis +=
                    safety_check_param.ori_lead_ttc() * (ego_v_ - obs_v);
                expected_cost_dis +=
                    safety_check_param.ori_lead_cost_ttc() * (ego_v_ - obs_v);
            }
            if (yield_s_diff < expected_cost_dis) {
                absl::StrAppend(
                    infos, absl::StrCat("-- NOT SAFE, t: ", t, ", ori lead ",
                                        obs_decision.obj_id, "\n"));
                if (FLAGS_planner_search_fail_level == 211) {
                    std::vector<double> xs, ys;
                    xs.push_back(ego_x_);
                    ys.push_back(ego_y_);
                }
                return false;
            } else if ((yield_s_diff < expected_yield_dis) &&
                       (ref_velocity != nullptr)) {
                const double ori_lead_cost_l_ratio =
                    safety_check_param.ori_lead_cost_l_ratio();
                const double l_ratio =
                    lerp(ori_lead_cost_l_ratio, 0.0, 1.0, vehicle_width,
                         std::min(obs_max_l - ego_min_l, ego_max_l - obs_min_l),
                         true);
                ref_velocity->ori_dist =
                    l_ratio * (expected_yield_dis - yield_s_diff);
            }
        }
    }

    return true;
}

bool SafetyCheck::IsSafeWithDynamicObs(const ObstacleDecision &obs_decision,
                                       double t,
                                       bool is_lane_change,
                                       double *ego_to_safety_dis) {
    const int pred_pt_index = t * kDevidedByPredTrajTimeStep_;
    if (pred_pt_index >=
        static_cast<int>(obs_decision.modified_pred_traj.size())) {
        return true;
    }
    double obs_max_l =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_max;
    double obs_min_l =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_min;
    double obs_min_s =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_min;
    double obs_max_s =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_max;

    double ego_min_l =
        ego_l_ - (0.5 * vehicle_params_->vehicle_geometry_params().width());
    double ego_min_s =
        ego_s_ -
        vehicle_params_->vehicle_geometry_params().back_edge_to_center();
    double ego_max_s =
        ego_s_ +
        vehicle_params_->vehicle_geometry_params().front_edge_to_center();

    const auto *obs_behavior =
        pnc_x::FindOrNull(*obs_behavior_map_, std::string(obs_decision.obj_id));
    if (obs_behavior == nullptr) {
        return true;
    }
    if ((obs_behavior->obs_intent == ObstacleIntention::kLeftCutin ||
         obs_behavior->obs_intent == ObstacleIntention::kRightCutin) &&
        !IsSafeWithCutinObs(obs_decision, pred_pt_index)) {
        return false;
    }
    if ((obs_behavior->obs_intent == ObstacleIntention::kLeftCross ||
         obs_behavior->obs_intent == ObstacleIntention::kRightCross) &&
        !IsSafeWithCrossObs(obs_decision, pred_pt_index)) {
        return false;
    }

    return true;
}

bool SafetyCheck::IsSafeWithCutinObs(const ObstacleDecision &obs_decision,
                                     int pred_pt_index) {
    double obs_max_l =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_max;
    double obs_min_l =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_min;
    bool obs_intruded =
        std::fabs(obs_max_l) < 1.75 || std::fabs(obs_min_l) < 1.75;
    if (!obs_intruded) {
        return true;
    }
    double intruded_dis = 0.0;
    if ((obs_max_l > -1.75) && (obs_min_l < -1.75)) {
        intruded_dis = 1.75 - std::fabs(obs_max_l);
    } else if ((obs_max_l > 1.75) && (obs_min_l < 1.75)) {
        intruded_dis = 1.75 - std::fabs(obs_max_l);
    } else {
        intruded_dis = obs_max_l - obs_min_l;
    }

    double obs_max_s =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_max;
    double obs_min_s =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_min;
    if (obs_decision.decision_tag.lon_decision_tag ==
        OvertakeYieldType::kOvertake) {
        if (ego_s_ > obs_max_s) {
            return false;
        }
    } else if (obs_decision.decision_tag.lon_decision_tag ==
               OvertakeYieldType::kYield) {
        if (ego_s_ < obs_min_s) {
            return false;
        }
    }
    return true;
}

bool SafetyCheck::IsSafeWithCrossObs(const ObstacleDecision &obs_decision,
                                     int pred_pt_index) {
    double obs_max_l =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_max;
    double obs_min_l =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_min;
    if ((obs_min_l > 1.75) && (obs_max_l < -1.75)) {
        return true;
    }

    if (obs_decision.decision_tag.lon_decision_tag ==
        OvertakeYieldType::kOvertake) {
        double obs_max_s =
            obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_max;
        if (ego_s_ > obs_max_s) {
            return false;
        }
    } else if (obs_decision.decision_tag.lon_decision_tag ==
               OvertakeYieldType::kYield) {
        double obs_min_s =
            obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_min;
        if (ego_s_ < obs_min_s) {
            return false;
        }
    }
    return true;
}

bool SafetyCheck::IsSafeWithSideObs(const ObstacleDecision &obs_decision,
                                    int pred_pt_index) {
    double ego_max_l =
        ego_l_ + (0.5 * vehicle_params_->vehicle_geometry_params().width());
    double ego_min_l =
        ego_l_ - (0.5 * vehicle_params_->vehicle_geometry_params().width());
    bool corner_in_side_lane = (ego_min_l > 1.75) || (ego_max_l < -1.75);
    if (!corner_in_side_lane) {
        return true;
    }

    double obs_v =
        obs_decision.modified_pred_traj[pred_pt_index].traj_point.v();
    double obs_max_l =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_max;
    double obs_min_l =
        obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.l_min;
    if (obs_decision.decision_tag.lon_decision_tag ==
        OvertakeYieldType::kOvertake) {
        double obs_max_s =
            obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_max;
        if (ego_s_ > obs_max_s) {
            return false;
        }
    } else if (obs_decision.decision_tag.lon_decision_tag ==
               OvertakeYieldType::kYield) {
        double obs_min_s =
            obs_decision.modified_pred_traj[pred_pt_index].sl_boundary.s_min;
        if (ego_s_ < obs_min_s) {
            return false;
        }
    }
    return true;
}

bool SafetyCheck::CheckBox() {
    const double shift_x = obs_center_.x() - ego_center_.x();
    const double shift_y = obs_center_.y() - ego_center_.y();

    const double sin_ego_yaw = sin_ego_yaw_;
    const double cos_ego_yaw = cos_ego_yaw_;

    const double sin_obs_yaw = pnc_x::fast_math::Sin(obs_yaw_);
    const double cos_obs_yaw = pnc_x::fast_math::Cos(obs_yaw_);

    const double dx1 = cos_ego_yaw * half_ego_length_;
    const double dy1 = sin_ego_yaw * half_ego_length_;
    const double dx2 = sin_ego_yaw * half_ego_width_;
    const double dy2 = -cos_ego_yaw * half_ego_width_;
    const double dx3 = cos_obs_yaw * half_obs_length_;
    const double dy3 = sin_obs_yaw * half_obs_length_;
    const double dx4 = sin_obs_yaw * half_obs_width_;
    const double dy4 = -cos_obs_yaw * half_obs_width_;

    return !((std::fabs((shift_x * cos_ego_yaw) + (shift_y * sin_ego_yaw)) <=
                 std::fabs((dx3 * cos_ego_yaw) + (dy3 * sin_ego_yaw)) +
                     std::fabs((dx4 * cos_ego_yaw) + (dy4 * sin_ego_yaw)) +
                     half_ego_length_) &&
             (std::fabs((shift_x * sin_ego_yaw) - (shift_y * cos_ego_yaw)) <=
                 std::fabs((dx3 * sin_ego_yaw) - (dy3 * cos_ego_yaw)) +
                     std::fabs((dx4 * sin_ego_yaw) - (dy4 * cos_ego_yaw)) +
                     half_ego_width_) &&
             (std::fabs((shift_x * cos_obs_yaw) + (shift_y * sin_obs_yaw)) <=
                 std::fabs((dx1 * cos_obs_yaw) + (dy1 * sin_obs_yaw)) +
                     std::fabs((dx2 * cos_obs_yaw) + (dy2 * sin_obs_yaw)) +
                     half_obs_length_) &&
             (std::fabs((shift_x * sin_obs_yaw) - (shift_y * cos_obs_yaw)) <=
                 std::fabs((dx1 * sin_obs_yaw) - (dy1 * cos_obs_yaw)) +
                     std::fabs((dx2 * sin_obs_yaw) - (dy2 * cos_obs_yaw)) +
                     half_obs_width_));
}

Pose SafetyCheck::GetDynamicObsPointByTime(const ObstacleDecision &obs_decision,
                                           double t) {
    const auto &pred_traj = obs_decision.modified_pred_traj;
    if (pred_traj.empty()) {
        return Pose{0.0, 0.0, 0.0};
    }
    const auto &first_obs_pt = pred_traj.front();
    const int traj_size = static_cast<int>(pred_traj.size());
    const double origin_start_time = first_obs_pt.traj_point.t();
    const double origin_end_time = pred_traj.back().traj_point.t();
    const int traj_size_minus1 = traj_size - 1;
    double traj_end_time =
        std::max(pred_traj_time_step_ * static_cast<double>(traj_size_minus1),
                 origin_end_time);
    if ((t < origin_start_time) || (traj_size < 2)) {
        return Pose(first_obs_pt.box_2d.center_x(),
                    first_obs_pt.box_2d.center_y(),
                    first_obs_pt.box_2d.heading());
    }
    if (t >= traj_end_time) {
        double obs_cur_x_front = pred_traj[traj_size - 2].traj_point.pos().x();
        double obs_cur_y_front = pred_traj[traj_size - 2].traj_point.pos().y();
        double obs_cur_x_back = pred_traj.back().traj_point.pos().x();
        double obs_cur_y_back = pred_traj.back().traj_point.pos().y();
        double obs_cur_theta_back = pred_traj.back().traj_point.theta();
        double obs_cur_y =
            obs_cur_y_back +
            ((t - traj_end_time) * (obs_cur_y_back - obs_cur_y_front) *
             kDevidedByPredTrajTimeStep_);
        double obs_cur_x =
            obs_cur_x_back +
            ((t - traj_end_time) * (obs_cur_x_back - obs_cur_x_front) *
             kDevidedByPredTrajTimeStep_);
        return Pose(obs_cur_x, obs_cur_y, obs_cur_theta_back);
    }

    const int pred_pt_index = t * kDevidedByPredTrajTimeStep_;
    const auto &obs_pt = pred_traj[pred_pt_index];
    return Pose(obs_pt.box_2d.center_x(), obs_pt.box_2d.center_y(),
                obs_pt.box_2d.heading());
}

void SafetyCheck::CalculateEgoSymmetryShape(double ego_x,
                                            double ego_y,
                                            double ego_yaw,
                                            double front_edge_to_center,
                                            double rear_edge_to_center,
                                            double width) {
    double half_length = (front_edge_to_center + rear_edge_to_center) / 2.0;
    double diff = half_length - rear_edge_to_center;
    cos_ego_yaw_ = pnc_x::fast_math::Cos(ego_yaw);
    sin_ego_yaw_ = pnc_x::fast_math::Sin(ego_yaw);
    pnc_x::Vec2d shift_direction(cos_ego_yaw_, sin_ego_yaw_);
    shift_direction *= diff;
    ego_center_.set_x(ego_x);
    ego_center_.set_y(ego_y);
    ego_center_ += shift_direction;

    half_ego_length_ = half_length;
    half_ego_width_ = width / 2.0;
    ego_yaw_ = ego_yaw;
}

double SafetyCheck::PiecewiseLinearFunction(double x,
                                            double k1,
                                            double k2,
                                            double y0) {
    if (std::abs(k1) < 1e-10) {
        return 0.0;
    }

    double x0 = y0 / k1;
    if (x0 < 0.0) {
        x0 *= -1.0;
        y0 *= -1.0;
    }
    if (std::abs(x) <= std::abs(x0)) {
        return k1 * x;
    } else if (x > x0) {
        return y0 + (k2 * (x - x0));
    } else {
        return -y0 + (k2 * (x + x0));
    }
}

void SafetyCheck::UpdateIsObstacleLeavingTargetTable() {
    const double time_resolution =
        initializer_params_.interactive_astar_search_config().time_resolution();
    for (const auto &pair : decision_group_->obstacles_decision) {
        const auto &object_id = pair.first;
        const auto &obs_decision = pair.second;
        if (object_id != lead_id_ && object_id != tail_id_ &&
            object_id != ori_lead_id_) {
            continue;
        }
        if (obs_decision.modified_pred_traj.empty()) {
            continue;
        }
        int flag_size =
            static_cast<int>(
                round(obs_decision.modified_pred_traj.back().traj_point.t() /
                      std::max(time_resolution, 1e-6))) +
            1;
        std::vector<bool> is_obstacle_leaving_target_vec(flag_size, false);
        for (int i = flag_size - 1; i > 0; i--) {
            const int pred_pt_index = static_cast<int>(
                round(i * time_resolution * kDevidedByPredTrajTimeStep_));
            if (pred_pt_index >= obs_decision.modified_pred_traj.size()) {
                is_obstacle_leaving_target_vec[i] = true;
                continue;
            }
            if (IsObstacleLeavingTarget(obs_decision, pred_pt_index)) {
                is_obstacle_leaving_target_vec[i] = true;
            } else {
                break;
            }
        }
        is_obstacle_leaving_target_table_[object_id] =
            std::move(is_obstacle_leaving_target_vec);
    }

    return;
}

}  // namespace planning
}  // namespace pnc_x
