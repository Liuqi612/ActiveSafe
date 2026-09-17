

#include "prediction/predicted_trajectory.h"

#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

#include <absl/strings/str_format.h>

#include "math/geometry/util.h"
#include "prediction/prediction_defs.h"
#include "util/loop_guard.h"

namespace pnc_x {
namespace prediction {

PredictedTrajectoryPoint::PredictedTrajectoryPoint(
    const PredictedTrajectoryPointProto &proto) {
    FromProto(proto);
}

PredictedTrajectoryPoint::PredictedTrajectoryPoint(
    const planning::SecondOrderTrajectoryPoint &point)
    : planning::SecondOrderTrajectoryPoint(point) {}

void PredictedTrajectoryPoint::FromProto(
    const PredictedTrajectoryPointProto &proto) {
    set_pos(Vec2dFromProto(proto.pos()));
    set_s(proto.s());
    set_theta(proto.theta());
    set_kappa(proto.kappa());

    set_t(proto.t());
    set_v(proto.v());
    set_a(proto.a());
}

void PredictedTrajectoryPoint::ToProto(
    PredictedTrajectoryPointProto *proto) const {
    Vec2dToProto(pos(), proto->mutable_pos());
    proto->set_s(s());
    proto->set_theta(theta());
    proto->set_kappa(kappa());
    proto->set_t(t());
    proto->set_v(v());
    proto->set_a(a());
}

PredictedTrajectory::PredictedTrajectory() {}
PredictedTrajectory::PredictedTrajectory(
    const PredictedTrajectoryProto &proto) {
    FromProto(0.0, proto);
}

PredictedTrajectory::PredictedTrajectory(
    double shift_time, const PredictedTrajectoryProto &proto) {
    FromProto(shift_time, proto);
}

double PredictedTrajectory::probability() const { return probability_; }
PredictionType PredictedTrajectory::type() const { return type_; }
bool PredictedTrajectory::is_reversed() const { return is_reversed_; }
int PredictedTrajectory::index() const { return index_; }
const std::vector<PredictedTrajectoryPoint> &PredictedTrajectory::points()
    const {
    return points_;
}
void PredictedTrajectory::set_probability(double probability) {
    probability_ = probability;
}
void PredictedTrajectory::set_index(int index) { index_ = index; }
void PredictedTrajectory::set_type(PredictionType type) { type_ = type; }
void PredictedTrajectory::set_intention(const TrajectoryIntention &intention) {
    intention_ = intention;
}

std::vector<PredictedTrajectoryPoint> *PredictedTrajectory::mutable_points() {
    return &points_;
}
TrajectoryIntention PredictedTrajectory::intention() const {
    return intention_;
}

std::string PredictedTrajectory::DebugString() const {
    return absl::StrFormat("type:%s(%d),prob:%7.6f,size:%d,is_reversed:%d",
                           PredictionType_Name(type_), type_, probability_,
                           points_.size(), is_reversed_);
}

void PredictedTrajectory::FromProto(const PredictedTrajectoryProto &proto) {
    FromProto(0.0, proto);
}

void PredictedTrajectory::FromProto(double shift_time,
                                    const PredictedTrajectoryProto &proto) {
    probability_ = proto.probability();
    type_ = proto.type();
    index_ = proto.index();
    is_reversed_ = proto.is_reversed();
    intention_ = proto.intention();
    points_.reserve(static_cast<size_t>(proto.points_size()));
    if (proto.points_size() > 0) {
        if (type_ == PT_STATIONARY) {
            const auto &pt = proto.points(0);
            for (int i = 0; i < kPredictionPointNum; ++i) {
                points_.emplace_back();
                points_.back().FromProto(pt);
                points_.back().set_t(static_cast<double>(i) * kPredictionTimeStep);
            }
        } else {
            int i = 0;
            auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
            while ((i < proto.points_size()) &&
                   (proto.points(i).t() < shift_time) && loop_guard) {
                ++i;
            }
            for (int j = i; j < proto.points_size(); ++j) {
                points_.emplace_back(proto.points(j));
                points_.back().set_t(points_.back().t() - proto.points(i).t());
                points_.back().set_s(points_.back().s() - proto.points(i).s());
            }
        }
    }
}

void PredictedTrajectory::ToProto(PredictedTrajectoryProto *proto,
                                  bool compress_traj) const {
    proto->Clear();
    proto->set_probability(probability_);
    proto->set_type(type_);
    proto->set_index(index_);

    proto->set_is_reversed(is_reversed_);

    if (!points_.empty()) {
        if (type_ == PT_STATIONARY) {
            points_.front().ToProto(proto->add_points());
        } else {
            for (const auto &point : points_) {
                point.ToProto(proto->add_points());
            }
        }
    }
}

}  // namespace prediction
}  // namespace pnc_x
