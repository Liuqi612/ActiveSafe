
#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "speed/att_point.h"
#include "speed/st_boundary.h"
#include "speed/st_point.h"
#include "speed/vt_point.h"
#include "pncx_speed_finder.pb.h"
#include <absl/strings/string_view.h>

namespace pnc_x {
namespace planning {

class StBoundaryWithDecision {
 public:
    explicit StBoundaryWithDecision(StBoundaryRef raw_st_boundary);

    StBoundaryWithDecision(StBoundaryRef raw_st_boundary,
                           StBoundaryProto::DecisionType decision_type,
                           StBoundaryProto::DecisionReason decision_reason);

    StBoundaryWithDecision(StBoundaryRef raw_st_boundary,
                           StBoundaryProto::DecisionType decision_type,
                           StBoundaryProto::DecisionReason decision_reason,
                           std::string decision_info,
                           double follow_standstill_distance,
                           double lead_standstill_distance,
                           double pass_time,
                           double yield_time);

    boost::optional<std::pair<double, double>> GetUnblockSRange(
        double curr_time, double path_end_s) const;

    const StBoundary *st_boundary() const;
    void set_st_boundary(StBoundaryRef st_boundary);

    const StBoundary *raw_st_boundary() const;
    StBoundary *mutable_raw_st_boundary() const;

    StBoundaryProto::DecisionType decision_type() const;
    void set_decision_type(StBoundaryProto::DecisionType decision_type);

    const std::string &id() const;
    void set_id(const std::string &id);

    const double ds() const;
    const double dl() const;
    const FrenetPolygon obj_frenet_polygon() const;

    const std::vector<NearestSlPoint> &nearest_sl_points() const;

    const ObjectDecisionParam decision_param() const;

    const boost::optional<std::string> &traj_id() const;
    const boost::optional<std::string> &object_id() const;

    void InitSTPoints(std::vector<std::pair<StPoint, StPoint>> st_point_pairs);
    void InitSpeedPoints(std::vector<VtPoint> vt_points);

    StBoundaryProto::DecisionReason decision_reason() const;
    void set_decision_reason(StBoundaryProto::DecisionReason decision_reason);

    StBoundaryProto::IgnoreReason ignore_reason() const;
    void set_ignore_reason(StBoundaryProto::IgnoreReason ignore_reason);
    double follow_standstill_distance() const;
    void set_follow_standstill_distance(double follow_standstill_distance);
    double lead_standstill_distance() const;
    void set_lead_standstill_distance(double lead_standstill_distance);

    double pass_time() const;
    double yield_time() const;
    void SetTimeBuffer(double pass_time, double yield_time);

    std::string decision_info() const;
    void set_decision_info(std::string str);

    void set_decision_prob(double yield, double pass);

    StBoundaryProto::DecisionProb decision_prob() const;

    SecondOrderTrajectoryPoint obj_pose_info() const;

    const std::vector<AttPoint> &pred_fut_acc_info() const {
        return pred_fut_acc_info_;
    }

    void set_pred_fut_acc_info(const std::vector<AttPoint> &att_info) {
        pred_fut_acc_info_ = att_info;
    }

    std::pair<double, double> GetPredFutAccInfoAtT(double t) const;

 private:
    StBoundaryRef raw_st_boundary_;

    StBoundaryRef st_boundary_;

    StBoundaryProto::DecisionType decision_type_ = StBoundaryProto::UNKNOWN;
    StBoundaryProto::DecisionReason decision_reason_ =
        StBoundaryProto::UNKNOWN_REASON;
    StBoundaryProto::IgnoreReason ignore_reason_ = StBoundaryProto::NONE;
    std::string decision_info_;
    StBoundaryProto::DecisionProb decision_prob_;
    std::vector<AttPoint> pred_fut_acc_info_;

    double follow_standstill_distance_ = 0.0;
    double lead_standstill_distance_ = 0.0;

    double pass_time_ = 0.0;
    double yield_time_ = 0.0;
};

}  // namespace planning
}  // namespace pnc_x
