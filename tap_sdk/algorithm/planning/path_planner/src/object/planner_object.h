
#pragma once

#include <optional>
#include <string>
#include <vector>

#include "math/geometry/aabox2d.h"
#include "math/geometry/box2d.h"
#include "math/geometry/polygon2d.h"
#include "math/vec.h"
#include "pncx_perception.pb.h"
#include "plan/second_order_trajectory_point.h"
#include "pncx_planner_object.pb.h"
#include "pncx_prediction.pb.h"
#include "prediction/predicted_trajectory.h"
#include "prediction/prediction.h"

namespace pnc_x {
namespace planning {

class PlannerObject {
 public:
    PlannerObject() = default;

    explicit PlannerObject(prediction::ObjectPrediction object_prediction);

    void ToPlannerObjectProto(PlannerObjectProto *planner_object_proto) const;

    const std::string &id() const;

    int num_trajs() const;

    const prediction::PredictedTrajectory &traj(int i) const;

    const ObjectStopTimeProto &stop_time_info() const;

    const prediction::ObjectLongTermBehavior &long_term_behavior() const;

    boost::optional<int> MostLikelyTrajectory() const;

    ObjectType type() const;
    void set_type(ObjectType otype);

    ObjectIntention object_intention() const;
    void set_object_intention(ObjectIntention obj_intention);

    const ObjectProto &object_proto() const;

    const SecondOrderTrajectoryPoint &pose() const;

    Vec2d velocity() const;

    const Polygon2d &contour() const;

    const AABox2d &aabox() const;

    void set_stationary(bool stationary);

    bool is_stationary() const;

    const prediction::ObjectPrediction &prediction() const;
    prediction::ObjectPrediction *mutable_prediction();

    const Box2d &bounding_box() const;

    const Box2d &perception_bbox() const;

    double proto_timestamp() const;

    bool is_sim_agent() const;

    bool is_large_vehicle() const;

    bool is_vru() const;
    const std::string &base_id() const;

    uint32_t confidence_level() const;

    void set_confidence_level(uint32_t confidence_level);

 private:
    void FromPrediction(const prediction::ObjectPrediction &prediction);

    bool is_stationary_ = false;
    SecondOrderTrajectoryPoint pose_;
    Vec2d velocity_;
    Polygon2d contour_;
    Box2d bounding_box_;
    Box2d perception_bbox_;
    AABox2d aabox_;
    prediction::ObjectPrediction prediction_;

    ObjectProto object_proto_;

    bool is_sim_agent_ = false;
    bool is_large_vehicle_ = false;
    bool is_vru_ = false;
    std::string base_id_;
    uint32_t confidence_level_ = 3;

    friend class PlannerObjectBuilder;
};

}  // namespace planning
}  // namespace pnc_x
