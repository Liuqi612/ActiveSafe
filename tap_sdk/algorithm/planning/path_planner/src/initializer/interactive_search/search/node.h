#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/path_sl_boundary.h"
#include "initializer/interactive_search/common/common.h"
#include "initializer/interactive_search/map/grid_map.h"
#include "initializer/interactive_search/search/safety_check.h"
#include "object/spacetime_trajectory_manager.h"
#include "router/drive_passage.h"
#include "pncx_vehicle.pb.h"
// #include <gflags/gflags.h>
namespace pnc_x {
namespace planning {

inline bool QueryXY2SLmap(const DrivePassage &drive_passage,
                          double x,
                          double y,
                          double *const s,
                          double *const l) {
    if (nullptr == s || nullptr == l) {
        return false;
    }
    const auto &sl_point =
        drive_passage.QueryUnboundedFrenetCoordinateAt(pnc_x::Vec2d(x, y));
    if (!sl_point.ok()) {
        return false;
    }
    *s = sl_point->s;
    *l = sl_point->l;
    return true;
}

enum class CostLineType {
    LINE_SOLID_YELLOW = 0,
    LINE_DOTTED_YELLOW = 1,
    LINE_SOLID_WHITE = 2,
    LINE_DOTTED_WHITE = 3,
    LINE_HARD_ISOLATION = 4,
    LINE_UNKHOWN = 5,
};

class Node final {
 public:
    Node() : Node(0.0, 0.0, 0.0, 0.0) {}

    Node(double x, double y, double theta, double v)
        : x_(x), y_(y), theta_(theta), v_(v) {}

    Node(uint64_t pred_index,
         double x,
         double y,
         double theta,
         double v,
         double s,
         double l,
         double ori_l,
         double acc,
         double jerk,
         double omega,
         double omega_rate,
         double time,
         double ego_to_safety_dis,
         const std::string &safety_check_info,
         const RefVelocityInGap &ref_velocity_lon)
        : pred_index_(pred_index),
          x_(x),
          y_(y),
          theta_(theta),
          v_(v),
          s_(s),
          l_(l),
          ori_l_(ori_l),
          acc_(acc),
          jerk_(jerk),
          omega_(omega),
          omega_rate_(omega_rate),
          accumulated_time_(time),
          ego_to_safety_dis_(ego_to_safety_dis),
          safety_check_info_(safety_check_info),
          v_safe_to_lead_(ref_velocity_lon.v_to_lead),
          v_safe_to_tail_(ref_velocity_lon.v_to_tail),
          v_safe_to_tail_origin_(ref_velocity_lon.v_to_tail_origin),
          s_safe_to_ori_(ref_velocity_lon.ori_dist) {}

    ~Node() {}

    Node(Node &&) noexcept = default;
    Node &operator=(Node &&) noexcept = default;
    Node(const Node &) = default;
    Node &operator=(const Node &) = default;

    friend std::ostream &operator<<(std::ostream &os, const Node &pt) {
        os << std::fixed << std::setprecision(2)
           << "t: " << pt.accumulated_time_
           << "  safe_dis: " << pt.ego_to_safety_dis_

           << "  theta: " << pt.theta_ << " s: " << pt.s_ << " l: " << pt.l_
           << "  ori_l: " << pt.ori_l_ << " v: " << pt.v_ << " acc: " << pt.acc_
           << "  omega: " << pt.omega_

           << " total: " << pt.total_cost_ << " g: " << pt.g_cost_
           << " h: " << pt.h_cost_ << " ref_l_c: " << pt.ref_l_cost_
           << " ref_h_c: " << pt.ref_heading_cost_ << " acc_c: " << pt.acc_cost_
           << " omega_c: " << pt.omega_cost_ << " jerk_c: " << pt.jerk_cost_
           << " centri_c: " << pt.centripetal_acc_cost_
           << " inter_c: " << pt.interaction_cost_
           << ", hcost_diff_v_lat: " << pt.diff_v_lat_
           << ", hcost_diff_v_lon: " << pt.diff_v_lon_
           << ", hcost_diff_ori_s_lon: " << pt.diff_ori_s_lon_
           << ", safety_cost: " << pt.safety_cost_ << "\n";
        return os;
    }

    std::string ToString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << "t: " << accumulated_time_
            << "  safe_dis: " << ego_to_safety_dis_

            << "  theta: " << theta_ << " s: " << s_ << " l: " << l_
            << "  ori_l: " << ori_l_ << " v: " << v_ << " acc: " << acc_
            << "  omega: " << omega_

            << " total: " << total_cost_ << " g: " << g_cost_
            << " h: " << h_cost_ << " ref_l_c: " << ref_l_cost_
            << " ref_h_c: " << ref_heading_cost_ << " acc_c: " << acc_cost_
            << " omega_c: " << omega_cost_ << " jerk_c: " << jerk_cost_
            << " centri_c: " << centripetal_acc_cost_
            << " inter_c: " << interaction_cost_
            << ", hcost_diff_v_lat: " << diff_v_lat_
            << ", hcost_diff_v_lon: " << diff_v_lon_
            << ", hcost_diff_ori_s_lon: " << diff_ori_s_lon_
            << ", safety_cost: " << safety_cost_ << "\n";
        return oss.str();
    }

    double X() const { return x_; }
    double Y() const { return y_; }
    double S() const { return s_; }
    double L() const { return l_; }
    double Theta() const { return theta_; }
    double V() const { return v_; }
    double Acc() const { return acc_; }
    double Omega() const { return omega_; }
    double AccumulatedTime() const { return accumulated_time_; }
    double DiffHeading() const { return diff_heading_; }

    double GCost() const { return g_cost_; }
    double HCost() const { return h_cost_; }
    double TotalCost() const { return total_cost_; }

    uint64_t Index() const { return index_; }

    bool IsOpen() const { return open_; }
    bool IsClose() const { return close_; }
    bool IsOrigin() const { return origin_; }
    bool IsStart() const { return start_; }
    uint64_t Predecessor() const { return pred_index_; }

    void SetX(double x) { x_ = x; }
    void SetY(double y) { y_ = y; }
    void SetV(double v) { v_ = v; }
    void SetGCost(double g_cost) { g_cost_ = g_cost; }
    void SetHCost(double h_cost) { h_cost_ = h_cost; }
    void SetAcc(double acc) { acc_ = acc; }
    uint64_t SetIndex(const InitializerConfig &initializer_params,
                      const std::vector<double> &xy_range);
    void SetS(double s) { s_ = s; }
    void SetL(double l) { l_ = l; }

    void SetOpen() {
        open_ = true;
        close_ = false;
    }
    void SetClose() {
        close_ = true;
        open_ = false;
    }
    void ResetUnclose() { close_ = false; }
    void SetPredecessor(uint64_t pred_index) { pred_index_ = pred_index; }
    void SetOrigin() { origin_ = true; }
    void SetStart() { start_ = true; }

    void UpdateGCost(const DrivePassage &drive_passage,
                     double yaw_rate_limit,
                     double pred_g_cost,
                     bool lane_change,
                     bool is_manual_lane_change,
                     const InitializerConfig &initializer_params,
                     const VehicleParamsProto *vehicle_params,
                     const ObstacleDecisionGroup &decision_group,
                     const std::unordered_map<std::string, ObstacleBehavior>
                         *obs_behavior_map);
    void UpdateHCost(double goal_s,
                     bool is_lane_change,
                     bool is_manual_lane_change,
                     const InitializerConfig &initializer_params);
    void UpdateTotalCost(double ratio) {
        total_cost_ = g_cost_ + (ratio * h_cost_);
    }
    double GetOmegaCost(double yaw_rate_limit) const;
    double GetAccCost(double acc) const;
    double GetReflCost(bool lane_change);
    double GetRefHeadingCost(const DrivePassage &drive_passage,
                             bool lane_change);
    double GetLaneBoundCost() const;

    double EgoToSafetyDis() const { return ego_to_safety_dis_; };

    std::string SafetyCheckInfo() const { return safety_check_info_; };

    bool equal_to(const Node &rhs) const;

    bool IsValid(const std::unordered_map<uint64_t, Node> &nodes_map,
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
                 boost::optional<StationBoundary> &left_boundary);

    std::unique_ptr<Node> CreateSuccessor(
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
        bool is_pre_safe = false);
    CostLineType CheckLineType() const;

    void SetEgoToSafetyDis(double dis) { ego_to_safety_dis_ = dis; }
    void SetSafetyCheckInfo(std::string info) {
        safety_check_info_ = std::move(info);
    }
    void SetRefVelocityInGap(const RefVelocityInGap &ref_velocity_lon);

 private:
    uint64_t pred_index_ = 0;
    uint64_t index_ = 0;
    double x_ = 0.0;
    double y_ = 0.0;
    double theta_ = 0.0;
    double v_ = 0.0;
    double s_ = 0.0;
    double l_ = 0.0;
    double ori_l_ = 0.0;
    double acc_ = 0.0;
    double jerk_ = 0.0;
    double omega_ = 0.0;
    double omega_rate_ = 0.0;
    double accumulated_time_ = 0.0;
    double diff_heading_ = 0.0;

    double omega_cost_ = 0.0;
    double omega_rate_cost_ = 0.0;
    double acc_cost_ = 0.0;
    double jerk_cost_ = 0.0;
    double centripetal_acc_cost_ = 0.0;
    double ref_l_cost_ = 0.0;
    double ref_heading_cost_ = 0.0;
    double interaction_cost_ = 0.0;
    double lane_bound_cost_ = 0.0;

    double g_cost_ = 0.0;

    double h_cost_ = 0.0;
    double total_cost_ = 0.0;

    bool open_ = false;
    bool close_ = false;
    bool origin_ = false;
    bool start_ = false;

    double ego_to_safety_dis_ = 0.0;
    double safety_cost_ = 0.0;
    std::string safety_check_info_ = " ";

    double diff_heading_sign_ = 0.0;
    double v_safe_to_lead_ = -1.0;
    double v_safe_to_tail_ = -1.0;
    double v_safe_to_tail_origin_ = -1.0;
    double s_safe_to_ori_ = 0.0;
    double diff_v_lat_ = 0.0;
    double diff_v_lon_ = 0.0;
    double diff_ori_s_lon_ = 0.0;
};

}  // namespace planning
}  // namespace pnc_x
