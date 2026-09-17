
#pragma once

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

#include "math/geometry/polygon2d.h"
#include "pncx_perception.pb.h"
#include "pncx_prediction.pb.h"
#include "prediction/predicted_trajectory.h"
#include "pncx_prediction_common.pb.h"

namespace pnc_x {
namespace prediction {

struct ObjectLongTermBehavior {
    double avg_speed;
    double obs_duration = 0.0;
    std::vector<double> accel_history;

    void FromProto(const ObjectLongTermBehaviorProto &proto);

    void ToProto(ObjectLongTermBehaviorProto *proto) const;
};

class ObjectPrediction {
 public:
    ObjectPrediction() = default;

    explicit ObjectPrediction(const ObjectProto &object_proto)
        : perception_object_(object_proto) {}

    ObjectPrediction(std::vector<PredictedTrajectory> trajectories,
                     const ObjectProto &object);

    explicit ObjectPrediction(const ObjectPredictionProto &proto);

    ObjectPrediction(const ObjectPredictionProto &proto,
                     double shift_time,
                     const ObjectProto &object);

    const ObjectProto &perception_object() const;

    double timestamp() const;

    const std::string &id() const;
    const std::vector<PredictedTrajectory> &trajectories() const;
    double trajectory_prob_sum() const;
    double trajectory_max_prob() const;

    double trajectory_min_prob() const;

    const Polygon2d &contour() const;

    void set_id(std::string id);

    std::vector<PredictedTrajectory> *mutable_trajectories();

    std::vector<std::string> DebugStringList() const;

    const ObjectStopTimeProto &stop_time() const;
    const ObjectLongTermBehavior &long_term_behavior() const;

    void FromProto(const ObjectPredictionProto &proto);
    void ToProto(ObjectPredictionProto *proto) const;

 private:
    void FromProto(const ObjectPredictionProto &proto,
                   double shift_time,
                   const ObjectProto &object);

    std::vector<PredictedTrajectory> trajectories_;
    Polygon2d contour_;

    ObjectProto perception_object_;

    ObjectStopTimeProto stop_time_;

    ObjectLongTermBehavior long_term_behavior_;
};

}  // namespace prediction
}  // namespace pnc_x
