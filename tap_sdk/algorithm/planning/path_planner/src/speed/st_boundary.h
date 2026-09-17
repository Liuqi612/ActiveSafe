
#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "common/log.h"

#include "math/frenet_common.h"
#include "math/geometry/box2d.h"
#include "math/geometry/polygon2d.h"
#include "math/vec.h"
#include "pncx_perception.pb.h"
#include "plan/second_order_trajectory_point.h"
#include "speed/overlap_info.h"
#include "speed/st_point.h"
#include "speed/vt_point.h"
#include "pncx_speed_finder.pb.h"

namespace pnc_x {
namespace planning {

class StBoundary;

using StBoundaryRef = std::unique_ptr<StBoundary>;

struct NearestSlPoint {
    double t = 0.0;
    double av_s = 0.0;
    double av_heading = 0.0;
    double obj_v = 0.0;
    double obj_heading = 0.0;
    int obj_idx = 0;
    double lat_dist = 0.0;
    double obj_vl = 0.0;
};

struct ObjectSlInfo {
    double ds = 0.0;
    double dl = 0.0;
    double vs = 0.0;
    double vl = 0.0;
    double yaw_diff = 0.0;
    FrenetPolygon frenet_polygon;
};

enum class InteractionZone {
    Unknown = 0,
    Straight = 1,
    JunctionStraight = 2,
    TurnLeft = 3,
    TurnRight = 4
};

enum class Relationship {
    NotRelevant = 0,
    SameDir = 1,
    OnComing = 2,
    Merge = 3,
    Cross = 4,
    Static = 5,
    Unknown = 6
};

enum class Bearing {
    Unknown = 0,
    Overlap = 1,
    Left = 2,
    Right = 3,
};

struct ObjectDecisionParam {
    double yield_time_factor = 1.0;
    double yield_time_additional_buffer = 0.0;
    double pass_time_factor = 1.0;
    double pass_time_additional_buffer = 0.0;
    double dp_follow_lead_ratio = 0.5;
    bool enable_interact_first_point_decision = true;
    bool enable_interact_last_point_decision = true;
    double interact_av_decel_factor = 1.0;
    double interact_obj_follow_dist_buffer = 0.0;
    bool geometry_theory_use_particular_follow_distance = false;
    double particular_agent_follow_distance = 0.0;
    double geometry_theory_av_follow_distance = 4.0;
    bool enable_add_collision_risk_cost_for_dp = false;
    double agent_reaction_time = 0.0;
    boost::optional<double> desired_follow_time_headway = boost::none;
};

struct ObjectScenarioInfo {
    InteractionZone interaction_zone = InteractionZone::Unknown;
    Relationship relationship = Relationship::Unknown;
    bool is_av_completely_in_obj_fov = false;
    Bearing bearing = Bearing::Unknown;
    double delta_heading;
    ObjectSlInfo obj_sl_info;
    double current_vl = 0.0;
    ObjectDecisionParam obj_decision_param;
};

struct StBoundaryPoints {
    std::vector<StPoint> lower_points;
    std::vector<StPoint> upper_points;
    std::vector<VtPoint> speed_points;
    std::vector<OverlapInfo> overlap_infos;
    std::vector<NearestSlPoint> nearest_sl_points;
    StBoundaryProto::ProtectionType protection_type =
        StBoundaryProto::NON_PROTECTIVE;
    void Reserve(size_t num) {
        lower_points.reserve(num);
        upper_points.reserve(num);
        speed_points.reserve(num);
        overlap_infos.reserve(num);
        nearest_sl_points.reserve(num);
    }
};

class StBoundary : public Polygon2d {
 public:
    explicit StBoundary(const Box2d &box) = delete;
    explicit StBoundary(std::vector<Vec2d> points) = delete;
    StBoundary(const StBoundary &) = delete;
    StBoundary(StBoundary &&) = delete;
    StBoundary &operator=(const StBoundary &) const = delete;
    StBoundary &operator=(StBoundary &&) const = delete;

    void DumpToDebugFrame(int task_i) const;

    static StBoundaryRef CreateInstance(
        const StBoundaryPoints &st_boundary_points,
        StBoundaryProto::ObjectType object_type,
        std::string id,
        double probability,
        bool is_stationary,
        StBoundaryProto::ProtectionType protection_type,
        bool is_large_vehicle,
        bool is_traffic_light,
        SecondOrderTrajectoryPoint pose = SecondOrderTrajectoryPoint(),
        ObjectSlInfo obj_sl_info = ObjectSlInfo(),
        ObjectScenarioInfo obj_scenario_info = ObjectScenarioInfo());

    static StBoundaryRef CopyInstance(const StBoundary &st_boundary);

    virtual ~StBoundary() = default;

    bool IsEmpty() const;

    bool IsPointInBoundary(const StPoint &st_point) const;

    StPoint upper_left_point() const;

    StPoint upper_right_point() const;

    StPoint bottom_left_point() const;

    StPoint bottom_right_point() const;

    void ExpandByT(double left, double right);

    StBoundarySourceTypeProto::Type source_type() const;
    void set_source_type(StBoundarySourceTypeProto::Type source_type);
    static std::string SourceTypeName(
        StBoundarySourceTypeProto::Type source_type);

    static StBoundarySourceTypeProto::Type ObjectTypeToSourceType(
        StBoundaryProto::ObjectType object_type);

    StBoundaryProto::ObjectType object_type() const;

    void set_object_type(StBoundaryProto::ObjectType type);

    const std::string &id() const;
    void set_id(const std::string &id);
    const boost::optional<std::string> &traj_id() const;
    const boost::optional<std::string> &object_id() const;

    double probability() const;
    void set_probability(double probability);

    bool is_stationary() const;
    void set_is_stationary(bool is_stationary);

    bool is_protective() const;

    StBoundaryProto::ProtectionType protection_type() const;
    void set_protection_type(StBoundaryProto::ProtectionType protection_type);

    boost::optional<std::string> protected_st_boundary_id() const;
    void set_protected_st_boundary_id(std::string protected_st_boundary_id);

    bool is_large_vehicle() const;
    bool is_traffic_light() const;
    void set_is_large_vehicle_vehicle(bool is_large_vehicle);

    void set_obj_sl_info(ObjectSlInfo obj_sl_info);

    void set_obj_scenario_info(ObjectScenarioInfo obj_scenario_info);

    boost::optional<std::pair<double, double>> GetBoundarySRange(
        double curr_time) const;

    boost::optional<double> GetStBoundarySpeedAtT(double t) const;

    bool GetLowerPointsIndexRange(double t, int *left, int *right) const;

    bool GetUpperPointsIndexRange(double t, int *left, int *right) const;

    bool GetSpeedPointsIndexRange(double t, int *left, int *right) const;

    double min_s() const;
    double min_t() const;
    double max_s() const;
    double max_t() const;

    ObjectSlInfo obj_sl_info() const;

    ObjectScenarioInfo obj_scenario_info() const;
    ObjectScenarioInfo &mutable_obj_scenario_info();
    SecondOrderTrajectoryPoint obj_pose_info() const;

    const std::vector<StPoint> &upper_points() const;
    const std::vector<StPoint> &lower_points() const;
    const std::vector<VtPoint> &speed_points() const;
    const std::vector<OverlapInfo> &overlap_infos() const;
    const std::vector<NearestSlPoint> &nearest_sl_points() const;

    void set_speed_points(std::vector<VtPoint> speed_points);

    const boost::optional<StOverlapMetaProto> &overlap_meta() const;
    void set_overlap_meta(StOverlapMetaProto meta);

    void Init(std::vector<std::pair<StPoint, StPoint>> point_pairs);

    std::string DebugString() const;

    static boost::optional<std::string> RecoverObjectId(
        const std::string &st_boundary_id,
        StBoundarySourceTypeProto::Type source_type);

    static boost::optional<std::string> RecoverTrajId(
        const std::string &st_boundary_id,
        StBoundarySourceTypeProto::Type source_type);

 private:
    StBoundary(std::vector<std::pair<StPoint, StPoint>> point_pairs,
               std::vector<VtPoint> speed_points,
               std::vector<OverlapInfo> overlap_infos,
               std::vector<NearestSlPoint> nearest_sl_points,
               StBoundaryProto::ObjectType object_type,
               std::string id,
               double probability,
               bool is_stationary,
               StBoundaryProto::ProtectionType protection_type,
               bool is_large_vehicle,
               bool is_traffic_light,
               boost::optional<StOverlapMetaProto> overlap_meta,
               boost::optional<std::string> protected_st_boundary_id,
               ObjectSlInfo obj_sl_info,
               ObjectScenarioInfo obj_scenario_info,
               SecondOrderTrajectoryPoint pose);

    bool IsValid(
        const std::vector<std::pair<StPoint, StPoint>> &point_pairs) const;

    template <typename T>
    bool QueryIndexRange(const std::vector<T> &local_points,
                         double t,
                         int *left,
                         int *right) const;

 private:
    StBoundaryProto::ObjectType object_type_ = StBoundaryProto::UNKNOWN_OBJECT;
    StBoundarySourceTypeProto::Type source_type_ =
        StBoundarySourceTypeProto::UNKNOWN;
    StBoundaryProto::ProtectionType protection_type_ =
        StBoundaryProto::NON_PROTECTIVE;

    std::vector<StPoint> lower_points_;
    std::vector<StPoint> upper_points_;

    std::vector<VtPoint> speed_points_;

    std::vector<OverlapInfo> overlap_infos_;

    std::vector<NearestSlPoint> nearest_sl_points_;

    std::string id_;

    boost::optional<std::string> traj_id_;
    boost::optional<std::string> object_id_;

    double probability_ = 0.0;
    bool is_stationary_ = false;
    bool is_large_vehicle_ = false;
    bool is_traffic_light_ = false;

    double min_s_ = std::numeric_limits<double>::max();
    double max_s_ = std::numeric_limits<double>::lowest();
    double min_t_ = std::numeric_limits<double>::max();
    double max_t_ = std::numeric_limits<double>::lowest();

    boost::optional<StOverlapMetaProto> overlap_meta_;
    boost::optional<std::string> protected_st_boundary_id_ = boost::none;
    ObjectSlInfo obj_sl_info_;
    ObjectScenarioInfo obj_scenario_info_;
    SecondOrderTrajectoryPoint pose_;
};

std::string GetStBoundaryIntegrationId(const StBoundary &st_boundary);

StBoundaryProto::ObjectType ToStBoundaryObjectType(ObjectType type);

}  // namespace planning
}  // namespace pnc_x
