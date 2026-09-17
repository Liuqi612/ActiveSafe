
#include "speed/st_boundary_with_decision.h"
#include <cmath>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "speed/st_boundary.h"
#include "speed/st_point.h"
#include "speed/vt_point.h"
#include "pncx_speed_finder.pb.h"
#include <absl/strings/string_view.h>

namespace pnc_x {
namespace planning {

StBoundaryWithDecision::StBoundaryWithDecision(StBoundaryRef raw_st_boundary)
    : raw_st_boundary_(std::move(raw_st_boundary)),
      st_boundary_(StBoundary::CopyInstance(*raw_st_boundary_)) {}

StBoundaryWithDecision::StBoundaryWithDecision(
    StBoundaryRef raw_st_boundary,
    StBoundaryProto::DecisionType decision_type,
    StBoundaryProto::DecisionReason decision_reason)
    : raw_st_boundary_(std::move(raw_st_boundary)),
      st_boundary_(StBoundary::CopyInstance(*raw_st_boundary_)),
      decision_type_(decision_type),
      decision_reason_(decision_reason) {}

StBoundaryWithDecision::StBoundaryWithDecision(
    StBoundaryRef raw_st_boundary,
    StBoundaryProto::DecisionType decision_type,
    StBoundaryProto::DecisionReason decision_reason,
    std::string decision_info,
    double follow_standstill_distance,
    double lead_standstill_distance,
    double pass_time,
    double yield_time)
    : raw_st_boundary_(std::move(raw_st_boundary)),
      st_boundary_(StBoundary::CopyInstance(*raw_st_boundary_)),
      decision_type_(decision_type),
      decision_reason_(decision_reason),
      decision_info_(std::move(decision_info)),
      follow_standstill_distance_(follow_standstill_distance),
      lead_standstill_distance_(lead_standstill_distance) {
    SetTimeBuffer(pass_time, yield_time);
}

void StBoundaryWithDecision::SetTimeBuffer(double pass_time,
                                           double yield_time) {
    st_boundary_ = StBoundary::CopyInstance(*raw_st_boundary_);
    pass_time_ = pass_time;
    yield_time_ = yield_time;
    st_boundary_->ExpandByT(pass_time_, yield_time_);
}

boost::optional<std::pair<double, double>>
StBoundaryWithDecision::GetUnblockSRange(double curr_time,
                                         double path_end_s) const {
    if ((curr_time < st_boundary()->min_t()) ||
        (curr_time > st_boundary()->max_t())) {
        return boost::none;
    }

    int left = 0;
    int right = 0;
    const auto &lower_points = st_boundary()->lower_points();
    const auto &upper_points = st_boundary()->upper_points();
    if (!st_boundary()->GetLowerPointsIndexRange(curr_time, &left, &right)) {
        // AD_LWARN(PP) << "Fail to get index range.";
        return boost::none;
    }
    XCHECK_NE(left, right);

    const double alpha = (curr_time - upper_points[left].t()) /
                         (upper_points[right].t() - upper_points[left].t());
    const double upper_cross_s =
        upper_points[left].s() +
        (alpha * (upper_points[right].s() - upper_points[left].s()));
    const double lower_cross_s =
        lower_points[left].s() +
        (alpha * (lower_points[right].s() - lower_points[left].s()));

    double lower_s = 0.0;
    double upper_s = path_end_s;
    if ((decision_type_ == StBoundaryProto::YIELD) ||
        (decision_type_ == StBoundaryProto::FOLLOW)) {
        upper_s = std::fmin(upper_s, lower_cross_s);
    } else if (decision_type_ == StBoundaryProto::OVERTAKE) {
        lower_s = std::fmax(lower_s, upper_cross_s);
    } else {
        // LOG(FATAL) << "boundary_type is not supported. boundary_type: "
        //            << StBoundaryProto::DecisionType_Name(decision_type_);
        return boost::none;
    }
    return std::make_pair(lower_s, upper_s);
}

const StBoundary *StBoundaryWithDecision::st_boundary() const {
    return st_boundary_.get();
}
void StBoundaryWithDecision::set_st_boundary(StBoundaryRef st_boundary) {
    st_boundary_ = std::move(st_boundary);
}

const StBoundary *StBoundaryWithDecision::raw_st_boundary() const {
    return raw_st_boundary_.get();
}
StBoundary *StBoundaryWithDecision::mutable_raw_st_boundary() const {
    return raw_st_boundary_.get();
}

StBoundaryProto::DecisionType StBoundaryWithDecision::decision_type() const {
    return decision_type_;
}
void StBoundaryWithDecision::set_decision_type(
    StBoundaryProto::DecisionType decision_type) {
    decision_type_ = decision_type;
}

const std::string &StBoundaryWithDecision::id() const {
    return st_boundary()->id();
}
void StBoundaryWithDecision::set_id(const std::string &id) {
    st_boundary_->set_id(id);
}

const double StBoundaryWithDecision::ds() const {
    return raw_st_boundary_->obj_sl_info().ds;
}
const double StBoundaryWithDecision::dl() const {
    return raw_st_boundary_->obj_sl_info().dl;
}
const FrenetPolygon StBoundaryWithDecision::obj_frenet_polygon() const {
    return raw_st_boundary_->obj_sl_info().frenet_polygon;
}

const std::vector<NearestSlPoint> &StBoundaryWithDecision::nearest_sl_points()
    const {
    return raw_st_boundary_->nearest_sl_points();
}

const ObjectDecisionParam StBoundaryWithDecision::decision_param() const {
    return raw_st_boundary_->obj_scenario_info().obj_decision_param;
}

const boost::optional<std::string> &StBoundaryWithDecision::traj_id() const {
    return st_boundary()->traj_id();
}
const boost::optional<std::string> &StBoundaryWithDecision::object_id() const {
    return st_boundary()->object_id();
}

void StBoundaryWithDecision::InitSTPoints(
    std::vector<std::pair<StPoint, StPoint>> st_point_pairs) {
    st_boundary_->Init(std::move(st_point_pairs));
}
void StBoundaryWithDecision::InitSpeedPoints(std::vector<VtPoint> vt_points) {
    st_boundary_->set_speed_points(std::move(vt_points));
}

StBoundaryProto::DecisionReason StBoundaryWithDecision::decision_reason()
    const {
    return decision_reason_;
}
void StBoundaryWithDecision::set_decision_reason(
    StBoundaryProto::DecisionReason decision_reason) {
    decision_reason_ = decision_reason;
}

StBoundaryProto::IgnoreReason StBoundaryWithDecision::ignore_reason() const {
    return ignore_reason_;
}
void StBoundaryWithDecision::set_ignore_reason(
    StBoundaryProto::IgnoreReason ignore_reason) {
    ignore_reason_ = ignore_reason;
}

double StBoundaryWithDecision::follow_standstill_distance() const {
    return follow_standstill_distance_;
}
void StBoundaryWithDecision::set_follow_standstill_distance(
    double follow_standstill_distance) {
    follow_standstill_distance_ = follow_standstill_distance;
}
double StBoundaryWithDecision::lead_standstill_distance() const {
    return lead_standstill_distance_;
}
void StBoundaryWithDecision::set_lead_standstill_distance(
    double lead_standstill_distance) {
    lead_standstill_distance_ = lead_standstill_distance;
}

double StBoundaryWithDecision::pass_time() const { return pass_time_; }
double StBoundaryWithDecision::yield_time() const { return yield_time_; }

std::string StBoundaryWithDecision::decision_info() const {
    return decision_info_;
}
void StBoundaryWithDecision::set_decision_info(std::string str) {
    decision_info_ = str;
}

void StBoundaryWithDecision::set_decision_prob(double yield, double pass) {
    decision_prob_.set_yield(yield);
    decision_prob_.set_pass(pass);
}

StBoundaryProto::DecisionProb StBoundaryWithDecision::decision_prob() const {
    return decision_prob_;
}

SecondOrderTrajectoryPoint StBoundaryWithDecision::obj_pose_info() const {
    return raw_st_boundary_->obj_pose_info();
}

std::pair<double, double> StBoundaryWithDecision::GetPredFutAccInfoAtT(
    double t) const {
    if (pred_fut_acc_info_.size() < 2) {
        return std::make_pair(0.0, 0.0);
    }

    if (t < (pred_fut_acc_info_.front().t() + 1e-6)) {
        return std::make_pair(pred_fut_acc_info_.front().a(),
                              pred_fut_acc_info_.front().dur());
    }

    if (t > (pred_fut_acc_info_.back().t() - 1e-6)) {
        return std::make_pair(pred_fut_acc_info_.back().a(),
                              pred_fut_acc_info_.back().dur());
    }

    int left = 0;
    int right = 0;
    const auto it = std::lower_bound(
        pred_fut_acc_info_.begin(), pred_fut_acc_info_.end(), t,
        [](const AttPoint &p, double t) { return p.t() < t; });
    const int index = static_cast<int>(std::distance(pred_fut_acc_info_.begin(), it));
    if (index == 0) {
        left = 0;
        right = left + 1;
    } else if (it == pred_fut_acc_info_.end()) {
        left = static_cast<int>(pred_fut_acc_info_.size()) - 1;
        right = left - 1;
    } else {
        left = index - 1;
        right = index;
    }

    double pred_fut_acc =
        Lerp(pred_fut_acc_info_[left].a(), pred_fut_acc_info_[left].t(),
             pred_fut_acc_info_[right].a(), pred_fut_acc_info_[right].t(), t);
    double pred_fut_dur =
        Lerp(pred_fut_acc_info_[left].dur(), pred_fut_acc_info_[left].t(),
             pred_fut_acc_info_[right].dur(), pred_fut_acc_info_[right].t(), t);

    return std::make_pair(pred_fut_acc, pred_fut_dur);
}

}  // namespace planning
}  // namespace pnc_x
