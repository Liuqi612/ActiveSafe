
#pragma once

#include <memory>
#include <unordered_set>

#include "common/type_def.h"
#include "maps/crosswalk.h"
#include "maps/lane_boundaries.h"
#include "maps/map_def.h"
#include "maps/road_boundaries.h"
#include "maps/road_boundary.h"
#include "math/curve_limits.h"
#include "math/line_curve2d.h"

namespace ads_x {
namespace planning {
enum ValidationRule {
    LANE_TO_CURB_DIST = 1,
    LANE_MAX_LENGTH = 2,
    TL_BIND = 3,
    LANE_TOPOLOGICAL_CONNECTION = 4,
    LANE_CURVATURE = 5,
    LANE_DIRECTION = 6,
    CURB_CONNECTION = 7,
    LANE_INTERSECT_IN_INTERSECTION = 8,
    SECTION_VALIDITY = 9,
    TL_HEADING = 10,
    REPEATING_FEATURE = 11
};

struct ValidationRecord {
    ValidationRule rule;
    std::string note;
};

struct LaneInteraction {
    uint64_t other_lane_id = 0;

    enum GeometricConfiguration { CROSS = 1, MERGE = 2 };
    GeometricConfiguration geometric_configuration;

    enum ReactionRule {

        STOP = 1,

        BOTH_STOP = 2,

        YIELD = 3,

        PROCEED = 4,

        YIELD_ON_RED = 6,

        YIELD_ON_GREEN_CIRCLE = 7,

        FFA = 5,

        YIELD_MERGE = 8,

        PROCEED_MERGE = 9
    };
    ReactionRule reaction_rule;
    std::string intersection_id;
    double this_lane_fraction;
    double other_lane_fraction;
    bool keep_it;
    int32_t belonging_levels;
    ValidationRecord skip_records;
};

class Lane {
 public:
    struct SampledWidth {
        double s = 0.0;
        double dist = 0.0;
    };
    Lane(const LaneInfo &lane_info,
         LaneBoundariesConstPtr left_boundary,
         LaneBoundariesConstPtr right_boundary,
         RoadBoundariesConstPtr left_road_boundary,
         RoadBoundariesConstPtr right_road_boundary);
    ~Lane() = default;

    void SetValidPredLaneIds(const std::vector<uint64_t> &lane_ids);
    void SetValidNextLaneIds(const std::vector<uint64_t> &lane_ids);
    void SetNextTurnTypes(const std::unordered_set<TurnType> &turn_types);
    void SetSortedNextLaneIds(const std::vector<uint64_t> &lane_ids);
    void SetLaneIndInSection(std::size_t lane_ind_in_section);

    void SetSplitTopology(const SplitTopology &split_topology);
    void SetMergeTopology(const MergeTopology &merge_topology);
    void SetIsHighway(bool local_is_highway) { is_highway_ = local_is_highway; }

    const uint64_t id() const;
    const uint64_t section_id() const;
    const uint64_t junction_id() const;
    const LaneType &type() const;
    const bool &is_navigation() const;
    const bool &stop_line() const;
    const double &speed_limit() const;
    const bool &is_highway() const { return is_highway_; }
    const SplitTopology &split_topology() const;
    const MergeTopology &merge_topology() const;

    const double topo_length() const;
    const double curve_length() const;
    const NoneOddType &none_odd_type() const;
    const uint32_t &turn_type_v3() const;
    const TurnType &turn_type() const;
    const TurnType &turn_type_V2() const;
    const LightStatus &light_status() const;
    const uint64_t left_lane_id() const;
    const uint64_t right_lane_id() const;
    const std::vector<uint64_t> &pre_lane_ids() const;
    const std::vector<uint64_t> &next_lane_ids() const;
    const std::vector<uint64_t> &valid_pre_lane_ids() const;
    const std::vector<uint64_t> &valid_next_lane_ids() const;
    const std::unordered_set<TurnType> &next_turn_types() const;
    const LaneInfo &lane_info() const;
    const LaneBoundariesConstPtr &left_boundary() const;
    const LaneBoundariesConstPtr &right_boundary() const;
    const RoadBoundariesConstPtr &left_road_boundary() const;
    const RoadBoundariesConstPtr &right_road_boundary() const;
    const bool can_pass_left_lane_boundaries() const;
    const bool can_pass_right_lane_boundaries() const;
    const std::vector<uint64_t> &sorted_next_lane_ids() const;
    const bool IsValid() const;
    const bool IsWidthValid() const;
    const bool IsValidV2() const;
    const bool IsVirtual() const;
    const bool IsVirtualForHeavyMap() const;
    const std::vector<uint64_t> crosswalks() const;
    const std::size_t lane_ind_in_section() const;
    const int32_t lane_operation_type() const;
    const int32_t arrow_type() const;
    bool GetCustomSpeedLimit(double *custom_speed_limit) const;

    void forward_boundary_type(
        const bool &is_left,
        const double &s,
        std::vector<LaneBoundaryType> &boundary_type) const;

    void forward_boundary_type(
        const bool &is_left,
        const Point2d &point,
        std::vector<LaneBoundaryType> &boundary_type) const;

    const math::LineCurve2d &center_line() const;
    const std::vector<Point2d> &points() const;

    const std::vector<uint64_t> &overlap_cross_walks() const;
    const std::vector<uint64_t> &overlap_speed_bumps() const;
    const std::vector<uint64_t> &overlap_parking_spaces() const;
    const std::vector<uint64_t> &overlap_clear_areas() const;
    const std::vector<uint64_t> &overlap_stop_lines() const;
    const std::vector<uint64_t> &overlap_trafficlights() const;

    bool IsOnLane(const math::Vec2d &point) const;
    bool IsOnLaneSrange(const math::Vec2d &point) const;

    void GetWidthAtAccumS(const double &s,
                          double &left_w,
                          double &right_w) const;

    double GetWidthAtPoint(const double &x, const double &y) const;

    double GetWidthAtAccumS(const double &s) const;

    bool IsPrecede(const uint64_t lane_id) const;

    bool IsNext(const uint64_t lane_id) const;

    bool GetSLWithLimit(const math::Vec2d &query_point,
                        SLPoint *const sl_point) const;
    bool GetSLWithoutLimit(const math::Vec2d &query_point,
                           SLPoint *const sl_point) const;
    bool GetSLWithoutLimitV2(const math::Vec2d &query_point,
                             SLPoint *const sl_point) const;
    bool GetXYWithoutLimit(const SLPoint &sl_point,
                           math::Vec2d *const xy_point) const;
    bool GetHeadingFromS(const double &query_s, double *const heading) const;
    bool GetWidthFromS(const double &query_s,
                       double *const lw,
                       double *const rw) const;
    bool IsAvoidanceLane() const;
    double navi_distance() const;
    int navi_section_cnt() const;

    bool endpoint_toll() const;

    void SetIsNavigation(const bool &is_navi,
                         const double navi_distance,
                         const int navi_section_cnt);
    void SetIsNavigation(const bool &is_navi);
    void SetSectionId(const uint64_t id);
    void SetTrueLength(const double &length);
    void AddPreviousLane(const uint64_t id);
    std::vector<LaneLinkData> GetLanelinks() const;

    double LaneFraction(int segment, double segment_fraction) const;

    std::pair<int, double> SegmentFraction(double lane_fraction) const;

    bool GetTangent(double fraction, math::Vec2d *tangent) const;

    math::Vec2d GetTangent(double fraction) const;

    math::Vec2d LerpPointFromFraction(double fraction) const;

    std::vector<std::string> startpoint_associated_traffic_lights() const;
    std::vector<LaneInteraction> interactions() const;
    void AddInteractions(const LaneInteraction &interact);

 private:
    double CalculateWidth(math::LineSegment2d &base, Point2d &p, int lr) const;
    void GenerateSampleWidth(LaneBoundariesConstPtr &boundary,
                             std::list<SampledWidth> *const sample_width);
    double GetDistanceFromSample(
        const double &query_s,
        const std::list<SampledWidth> *const sampled_widths) const;

 private:
    std::list<SampledWidth> sampled_left_width_;
    std::list<SampledWidth> sampled_right_width_;

    LaneInfo lane_info_;
    std::vector<uint64_t> prev_lane_ids_;
    std::vector<uint64_t> valid_pre_lane_ids_;
    std::vector<uint64_t> valid_next_lane_ids_;
    std::vector<uint64_t> sorted_next_lane_ids_;
    LaneBoundariesConstPtr left_boundary_ = nullptr;
    LaneBoundariesConstPtr right_boundary_ = nullptr;
    RoadBoundariesConstPtr left_road_boundary_ = nullptr;
    RoadBoundariesConstPtr right_road_boundary_ = nullptr;
    math::LineCurve2d center_line_;
    double navi_distance_ = 0.0;
    int navi_section_cnt_ = 0;
    std::unordered_set<TurnType> next_turn_types_;
    std::size_t lane_ind_in_section_ = 0U;
    std::vector<LaneInteraction> interactions_;
    bool is_highway_ = false;

    bool endpoint_toll_ = false;
};

using LanePtr = std::shared_ptr<Lane>;
using LaneConstPtr = std::shared_ptr<const Lane>;

}  // namespace planning
}  // namespace ads_x
