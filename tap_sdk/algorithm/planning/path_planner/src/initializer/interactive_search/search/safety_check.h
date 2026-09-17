#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "decision/obstacle_intention_estimation.h"
#include "initializer/interactive_search/common/common.h"
#include "math/vec2d.h"
#include "object/spacetime_trajectory_manager.h"
#include "pncx_planner_params.pb.h"
#include "router/drive_passage.h"
#include "pncx_vehicle.pb.h"
// #include <gflags/gflags.h>

namespace pnc_x {
namespace planning {

struct Pose {
    double x = 0.0;
    double y = 0.0;
    double yaw = 0.0;
    Pose(double intput_x, double intput_y, double intput_yaw) {
        x = intput_x;
        y = intput_y;
        yaw = intput_yaw;
    }
};

class SafetyCheck final {
 public:
    SafetyCheck() = default;
    explicit SafetyCheck(const ObstacleDecisionGroup *decision_group,
                         const std::unordered_map<std::string, ObstacleBehavior>
                             *obs_behavior_map,
                         const VehicleParamsProto *vehicle_params,
                         const InitializerConfig &initializer_params,
                         const DrivePassage *drive_passage,
                         const PathSlBoundary *sl_boundary,
                         const std::vector<double> &thw,
                         double tail_ttc)
        : pred_traj_time_step_(decision_group->traj_time_step),
          decision_group_(decision_group),
          obs_behavior_map_(obs_behavior_map),
          vehicle_params_(vehicle_params),
          initializer_params_(initializer_params),
          drive_passage_(drive_passage),
          sl_boundary_(sl_boundary),
          gap_lead_thw_(thw[0]),
          gap_tail_thw_(thw[1]),
          ori_lead_thw_(thw[2]),
          gap_tail_ttc_(tail_ttc) {
        const auto &vehicle_geometry =
            vehicle_params_->vehicle_geometry_params();
        ego_radius_ =
            std::hypot(vehicle_geometry.length() * 0.5,
                       vehicle_geometry.width() * 0.5);
        kDevidedByPredTrajTimeStep_ = 1.0 / pred_traj_time_step_;
        for (const auto &pair : decision_group_->obstacles_decision) {
            const auto &trajectory = pair.second.modified_pred_traj;
            if (trajectory.empty()) {
                continue;
            }
            const auto &box = trajectory.front().box_2d;
            const double half_length = box.half_length() + 0.5;
            const double half_width = box.half_width() + 0.5;
            obstacle_shape_cache_.emplace(
                &pair.second,
                ObstacleShape{half_length, half_width,
                              std::hypot(half_length, half_width)});
        }
        if (decision_group->obs_goal_gap.lead_obj_id.has_value()) {
            lead_id_ = decision_group_->obs_goal_gap.lead_obj_id.value();
        }
        if (decision_group->obs_goal_gap.tail_obj_id.has_value()) {
            tail_id_ = decision_group_->obs_goal_gap.tail_obj_id.value();
        }
        if (decision_group->ori_lead_obj_id.has_value()) {
            ori_lead_id_ = decision_group->ori_lead_obj_id.value();
        }
        debug_str_ = "";

        UpdateIsObstacleLeavingTargetTable();
    };
    ~SafetyCheck(){};

    bool IsCollisionFree(
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
        double half_x_succ,
        double half_y_succ,
        double half_mid_v,
        double half_mid_theta,
        double half_accumulated_time,
        const std::string &group_prefix,
        std::string *infos,
        bool is_pre_safe = false,
        boost::optional<StationBoundary> *target_right_boundary = nullptr,
        boost::optional<StationBoundary> *target_left_boundary = nullptr,
        RefVelocityInGap *ref_velocity = nullptr);

    void clear_debug_msg() { debug_str_.clear(); }

    const std::string *debug_str_ptr() const { return &debug_str_; }

    const std::unordered_map<std::string, std::vector<bool>> &
    GetIsObstacleLeavingTargetTable() const {
        return is_obstacle_leaving_target_table_;
    }

 private:
    struct ObstacleShape {
        double half_length;
        double half_width;
        double radius;
    };

    bool PreCollisionFreeCheck() {
        double center_to_obs = (ego_center_ - obs_center_).Length();
        return center_to_obs > (ego_radius_ + obs_radius_);
    }

    bool IsSafeWithObstacles(
        double t,
        bool is_lane_change,
        bool node_pred_safe,
        double *ego_to_safety_dis,
        const std::string &group_prefix,
        std::string *infos,
        bool is_pre_safe = false,
        boost::optional<StationBoundary> *target_right_boundary = nullptr,
        boost::optional<StationBoundary> *target_left_boundary = nullptr,
        RefVelocityInGap *ref_velocity = nullptr);

    bool IsSafeWithSingleObs(
        const ObstacleDecision &object_decision,
        double t,
        bool is_lane_change,
        bool node_pred_safe,
        double *ego_to_safety_dis,
        const std::string &group_prefix,
        std::string *infos,
        bool is_pre_safe = false,
        boost::optional<StationBoundary> *target_right_boundary = nullptr,
        boost::optional<StationBoundary> *target_left_boundary = nullptr,
        RefVelocityInGap *ref_velocity = nullptr);

    bool IsSafeWithDynamicObs(const ObstacleDecision &object_decision,
                              double t,
                              bool is_lane_change,
                              double *ego_to_safety_dis);

    bool IsObstacleLeavingTarget(const ObstacleDecision &object_decision,
                                 int pred_pt_index);

    bool IsSafeWithCutinObs(const ObstacleDecision &object_decision,
                            int pred_pt_index);

    bool IsSafeWithCrossObs(const ObstacleDecision &object_decision,
                            int pred_pt_index);

    bool IsSafeWithSideObs(const ObstacleDecision &object_decision,
                           int pred_pt_index);

    bool CheckBox();

    void CalculateEgoSymmetryShape(double ego_x,
                                   double ego_y,
                                   double ego_yaw,
                                   double front_edge_to_center,
                                   double rear_edge_to_center,
                                   double width);

    Pose GetDynamicObsPointByTime(const ObstacleDecision &object_decision,
                                  double t);

    bool CheckLCGapSafety(
        const ObstacleDecision &obs_decision,
        double t,
        bool node_pred_safe,
        double *ego_to_safety_dis,
        const std::string &group_prefix,
        std::string *infos,
        bool is_pre_safe = false,
        boost::optional<StationBoundary> *target_right_boundary = nullptr,
        boost::optional<StationBoundary> *target_left_boundary = nullptr,
        RefVelocityInGap *ref_velocity = nullptr);

    void CheckEgoPosWithLane(
        bool *ego_corner_across_lane_bound,
        bool *ego_center_across_lane_bound,
        boost::optional<StationBoundary> *target_right_boundary = nullptr,
        boost::optional<StationBoundary> *target_left_boundary = nullptr);

    double PiecewiseLinearFunction(double x, double k1, double k2, double y0);

    void UpdateIsObstacleLeavingTargetTable();

 private:
    double ego_yaw_ = 0.0;
    double ego_radius_ = 0.0;
    double ego_v_ = 0.0;
    double ego_s_ = 0.0;
    double ego_l_ = 0.0;
    double ego_x_ = 0.0;
    double ego_y_ = 0.0;

    double half_ego_length_ = 0.0;
    double half_ego_width_ = 0.0;
    double sin_ego_yaw_ = 0.0;
    double cos_ego_yaw_ = 1.0;
    pnc_x::Vec2d ego_center_;
    pnc_x::Vec2d obs_center_;
    double obs_yaw_ = 0.0;
    double obs_radius_ = 0.0;
    double half_obs_length_ = 0.0;
    double half_obs_width_ = 0.0;

    std::string lead_id_ = "";
    std::string tail_id_ = "";
    std::string ori_lead_id_ = "";

    double pred_traj_time_step_ = 0.0;
    double kDevidedByPredTrajTimeStep_ = 10.0;

    std::string debug_str_;

    const ObstacleDecisionGroup *decision_group_;
    const std::unordered_map<std::string, ObstacleBehavior> *obs_behavior_map_;
    const VehicleParamsProto *vehicle_params_;
    const InitializerConfig &initializer_params_;
    const DrivePassage *drive_passage_;
    const PathSlBoundary *sl_boundary_;
    std::unordered_map<std::string, std::vector<bool>>
        is_obstacle_leaving_target_table_;
    std::unordered_map<const ObstacleDecision *, ObstacleShape>
        obstacle_shape_cache_;

    double gap_lead_thw_ = 0.0;
    double gap_tail_thw_ = 0.0;
    double ori_lead_thw_ = 0.0;
    double gap_tail_ttc_ = 0.0;
};

}  // namespace planning
}  // namespace pnc_x
