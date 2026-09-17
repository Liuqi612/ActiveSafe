
#pragma once

#include <algorithm>
#include <iterator>
#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "math/geometry/polygon2d.h"
#include "math/vec.h"
#include "plan/second_order_trajectory_point.h"
#include <absl/types/span.h>

#include "pncx_prediction.pb.h"
#include "pncx_prediction_common.pb.h"

namespace pnc_x {
namespace prediction {
class alignas(64) PredictedTrajectoryPoint
    : public planning::SecondOrderTrajectoryPoint {
 public:
    PredictedTrajectoryPoint() = default;
    explicit PredictedTrajectoryPoint(
        const PredictedTrajectoryPointProto &proto);

    explicit PredictedTrajectoryPoint(
        const planning::SecondOrderTrajectoryPoint &point);

    void FromProto(const PredictedTrajectoryPointProto &proto);
    void ToProto(PredictedTrajectoryPointProto *proto) const;
};

class PredictedTrajectory {
 public:
    PredictedTrajectory();
    explicit PredictedTrajectory(const PredictedTrajectoryProto &proto);

    explicit PredictedTrajectory(double shift_time,
                                 const PredictedTrajectoryProto &proto);

    double probability() const;
    PredictionType type() const;
    bool is_reversed() const;
    int index() const;
    const std::vector<PredictedTrajectoryPoint> &points() const;
    void set_probability(double probability);
    void set_index(int index);
    void set_type(PredictionType type);
    void set_intention(const TrajectoryIntention &intention);

    std::vector<PredictedTrajectoryPoint> *mutable_points();
    TrajectoryIntention intention() const;

    std::string DebugString() const;

    void FromProto(const PredictedTrajectoryProto &proto);
    void ToProto(PredictedTrajectoryProto *proto, bool compress_traj) const;

 private:
    void FromProto(double shift_time, const PredictedTrajectoryProto &proto);

    double probability_ = 0.0;
    PredictionType type_;
    int index_;
    std::vector<PredictedTrajectoryPoint> points_;

    bool is_reversed_ = false;
    TrajectoryIntention intention_ = TrajectoryIntention::INTENTION_UNKNOWN;
};

}  // namespace prediction
}  // namespace pnc_x
