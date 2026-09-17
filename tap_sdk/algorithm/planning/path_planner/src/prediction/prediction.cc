

#include <boost/optional.hpp>
#include <utility>

#include "prediction/prediction.h"
#include <absl/strings/str_format.h>

#include "prediction/perception_util.h"

namespace pnc_x {
namespace prediction {

namespace {

Polygon2d GetPolygonFromPerception(const ObjectProto &object) {
    boost::optional<Polygon2d> maybe_contour =
        Polygon2d::FromPoints(object.contour(), true);
    XCHECK(maybe_contour.has_value());
    return std::move(maybe_contour.value());
}

}  // namespace

void ObjectLongTermBehavior::FromProto(
    const ObjectLongTermBehaviorProto &proto) {
    avg_speed = proto.average_speed();
    obs_duration = proto.observation_duration();

    accel_history.reserve(static_cast<size_t>(proto.accel_history_size()));
    for (double accel : proto.accel_history()) {
        accel_history.push_back(accel);
    }
}

void ObjectLongTermBehavior::ToProto(ObjectLongTermBehaviorProto *proto) const {
    proto->set_average_speed(avg_speed);
    proto->set_observation_duration(obs_duration);

    auto *accel_hist = proto->mutable_accel_history();
    accel_hist->Reserve(static_cast<int>(accel_history.size()));
    for (double accel : accel_history) accel_hist->Add(accel);
}

ObjectPrediction::ObjectPrediction(
    std::vector<PredictedTrajectory> trajectories, const ObjectProto &object)
    : trajectories_(std::move(trajectories)),
      contour_(GetPolygonFromPerception(object)),
      perception_object_(object) {}

ObjectPrediction::ObjectPrediction(const ObjectPredictionProto &proto,
                                   double shift_time,
                                   const ObjectProto &object) {
    FromProto(proto, shift_time, object);
    contour_ = GetPolygonFromPerception(object);
}

ObjectPrediction::ObjectPrediction(const ObjectPredictionProto &proto)
    : ObjectPrediction(proto, 0.0, proto.perception_object()) {}

std::vector<std::string> ObjectPrediction::DebugStringList() const {
    std::vector<std::string> ret;
    ret.reserve(trajectories_.size() + 1);
    ret.emplace_back(absl::StrFormat(
        "obj:%s,t:%7.3f,total_prob:%6.5f, max_prob:"
        "%7.6f,min_prob:%7.6f",
        perception_object_.id(), timestamp(), trajectory_prob_sum(),
        trajectory_max_prob(), trajectory_min_prob()));
    for (size_t i = 0; i < trajectories_.size(); ++i) {
        ret.emplace_back(absl::StrCat(
            absl::StrFormat("traj%d/%d:", i + 1, trajectories_.size()),
            trajectories_.at(i).DebugString()));
    }
    return ret;
}

void ObjectPrediction::FromProto(const ObjectPredictionProto &proto) {
    FromProto(proto, 0.0, proto.perception_object());
}

void ObjectPrediction::FromProto(const ObjectPredictionProto &proto,
                                 double shift_time,
                                 const ObjectProto &object) {
    perception_object_ = object;
    constexpr double kTimeShiftThreshold = 1e-6;
    if (shift_time > kTimeShiftThreshold) {
        AlignPerceptionObjectTime(shift_time + object.timestamp(),
                                  &perception_object_)
            .IgnoreError();
    }

    trajectories_.reserve(static_cast<size_t>(proto.trajectories_size()));
    for (const auto &trajectory_proto : proto.trajectories()) {
        trajectories_.emplace_back(shift_time, trajectory_proto);
        if (trajectories_.back().points().empty()) {
            trajectories_.pop_back();
        }
    }

    stop_time_ = proto.stop_time();

    long_term_behavior_.FromProto(proto.long_term_behavior());
}

void ObjectPrediction::ToProto(ObjectPredictionProto *proto) const {
    proto->Clear();
    proto->set_id(perception_object_.id());

    proto->mutable_perception_object()->CopyFrom(perception_object_);

    for (const auto &trajectory : trajectories_) {
        trajectory.ToProto(proto->add_trajectories(), false);
    }

    proto->mutable_stop_time()->CopyFrom(stop_time_);

    long_term_behavior_.ToProto(proto->mutable_long_term_behavior());
}

const ObjectProto &ObjectPrediction::perception_object() const {
    return perception_object_;
}

double ObjectPrediction::timestamp() const {
    return perception_object_.timestamp();
}

const std::string &ObjectPrediction::id() const {
    return perception_object_.id();
}
const std::vector<PredictedTrajectory> &ObjectPrediction::trajectories() const {
    return trajectories_;
}
double ObjectPrediction::trajectory_prob_sum() const {
    return std::accumulate(trajectories_.begin(), trajectories_.end(), 0.0,
                           [](const double sum, const auto &traj) {
                               return sum + traj.probability();
                           });
}
double ObjectPrediction::trajectory_max_prob() const {
    return std::accumulate(trajectories_.begin(), trajectories_.end(), 0.0,
                           [](const double max, const auto &traj) {
                               return std::max(max, traj.probability());
                           });
}
double ObjectPrediction::trajectory_min_prob() const {
    return std::accumulate(trajectories_.begin(), trajectories_.end(), 1.0,
                           [](const double min, const auto &traj) {
                               return std::min(min, traj.probability());
                           });
}

const Polygon2d &ObjectPrediction::contour() const { return contour_; }

void ObjectPrediction::set_id(std::string id) { perception_object_.set_id(id); }

std::vector<PredictedTrajectory> *ObjectPrediction::mutable_trajectories() {
    return &trajectories_;
}

const ObjectStopTimeProto &ObjectPrediction::stop_time() const {
    return stop_time_;
}
const ObjectLongTermBehavior &ObjectPrediction::long_term_behavior() const {
    return long_term_behavior_;
}

}  // namespace prediction
}  // namespace pnc_x
