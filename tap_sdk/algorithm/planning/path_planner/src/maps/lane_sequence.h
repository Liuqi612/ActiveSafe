
#pragma once

#include <boost/optional.hpp>
#include <limits>
#include <vector>

#include "maps/lane.h"
#include "maps/map_def.h"
#include <cstdint>

namespace ads_x {
namespace planning {
class LaneSequence {
 public:
    explicit LaneSequence(const std::vector<LaneConstPtr> &lanes_ptr_vec);
    ~LaneSequence() = default;
    const std::vector<LaneConstPtr> &lanes() const;
    std::vector<LaneConstPtr> &mutable_lanes();

    LaneConstPtr front_lane() const;

    bool IsValid();

    double GetTrueLength() const;
    double GetPointsLength() const;

    bool SamplePoints(double start_s,
                      std::vector<Point2d> *const points,
                      double interval = 3.0) const;

    bool AddLane(const LaneConstPtr &lane);

    math::Vec2d GetPointAtS(double s) const;

    double GetWidthAtS(double s) const;

    math::Vec2d GetTangentAtS(double s) const;

    double GetProjectionDistance(const double &x, const double &y) const;

    double GetProjectionDistance(const math::Vec2d &point) const;

    LaneConstPtr GetNearestLane(const math::Vec2d &point,
                                double *dis = nullptr,
                                bool use_ego_heading = false,
                                double ego_heading = 0.0) const;

    double GetProjectionDistance(const math::Vec2d &point,
                                 double *s_offset,
                                 double *l_offset = nullptr) const;

    double GetDistanceToPOI(const PoiType &poi_type,
                            const double &x,
                            const double &y);

    double GetDistanceToPOI(
        const PoiType &poi_type,
        const double &x,
        const double &y,
        LaneConstPtr &poi_lane,
        const ads_x::planning::NaviPosition *navi_start = nullptr);

    void GetBoundaryTypeFromS(
        const bool &is_left,
        const double &s,
        std::vector<LaneBoundaryType> &boundary_type) const;

    void GetBoundaryTypeFromPoint(
        const bool &is_left,
        const math::Vec2d &point,
        std::vector<LaneBoundaryType> &boundary_type) const;
    void GetRoadSegments(const bool is_left,
                         std::vector<math::LineSegment2d> *road_segs) const;

    double GetDistanceToJunction(
        LaneConstPtr &poi_lane,
        const ads_x::planning::NaviPosition &navi_start,
        bool end_check = false,
        bool special_check = false) const;

    double GetDistanceBetweenJunction(const uint64_t begin_junction_id,
                                      LaneConstPtr &next_virtual_lane) const;
    double GetDistanceToJunction(const double &x,
                                 const double &y,
                                 LaneConstPtr &poi_lane) const;

    double GetDistanceExitJunction(
        const ads_x::planning::NaviPosition &navi_start) const;

    bool CanPassJunction(const ads_x::planning::NaviPosition &navi_start,
                         double *dist_to_junction = nullptr,
                         bool next_junction = false);
    bool IsTurnLeft(const double &x, const double &y);
    bool IsTurnRight(const double &x, const double &y);

    bool IsOnLaneSequence(const LaneConstPtr &lane) const;
    const LanePtr GetPreLaneOnLaneSequence(const LaneConstPtr &lane) const;

    double GetDistanceToTargetLaneType(
        LaneConstPtr &poi_lane,
        const std::unordered_set<LaneType> &lane_type_set,
        const ads_x::planning::NaviPosition &navi_start) const;
    double GetDistanceToCustomSpeedLimit(
        const ads_x::planning::NaviPosition &navi_start,
        double *speed_limit) const;
    boost::optional<LaneConstPtr> FindPreLaneOnLaneseq(Lane lane);
    double GetLeftSolidLength() const { return left_solid_length_; };
    double GetRightSolidLength() const { return right_solid_length_; };

 private:
    std::vector<LaneConstPtr> lanes_;
    double left_solid_length_ = 0.0;
    double right_solid_length_ = 0.0;
};

class NavigableLaneSequence : public LaneSequence {
 public:
    explicit NavigableLaneSequence(
        const std::vector<LaneConstPtr> &lanes_ptr_vec);
    ~NavigableLaneSequence() = default;
    void SetNaviDistance(const float navi_dis);
    void SetNearestObstacleVel(const float nearest_obstacle_vel);
    void SetNearestObstacleDistance(const float nearest_obstacle_distance);
    void SetDistanceToEgoCar(const float distance_to_ego_car);
    void SetSequenceIdx(const float sequence_idx);
    void SetIsNaviSequence(const bool is_navi_sequence);
    void SetProbability(const float probability);
    void SetLcReason(const LcReason lc_reason);
    void SetDebugContent(const std::string &debug_content);
    void SetProjectionPoint(const Point2d &projection_point);
    void SetIsOccupyLaneSeq(bool is_occupy_lane_seq);
    void SetIsOptimalLaneSeq(bool is_optimal_lane_seq);
    void SetCompleteSequences(
        std::vector<std::vector<LaneConstPtr>> &complete_sequences);
    void SetNearestObstacle(const ObstacleForLane &obstacle);
    void SetRightRoundaboutLanesNum(
        const std::int32_t right_roundabout_lanes_num);
    void SetRightLanesNum(const std::int32_t right_lanes_num);
    void SetScoreInStraightJunction(const float score_in_straight_junction);
    void AddObstacleInSequence(
        const std::pair<std::string, double> &obstacle_in_sequence);
    const float GetNaviDistance();
    const float GetSequenceIdx();
    const float GetNearestObstacleVel();
    const float GetNearestObstacleDistance();
    const float GetDistanceToEgoCar() const;
    const float GetProbability() const;
    const LcReason &GetLcReason() const;
    bool IsOverLap(const std::vector<LaneConstPtr> &other_lane_sequence);
    bool IsTwoSplitLane(const std::vector<LaneConstPtr> &other_lane_sequence);
    const bool GetIsNaviSequence();
    const bool GetIsOccupyLaneSeq();
    const bool GetIsOptimalLaneSeq();
    const std::int32_t GetRightRoundaboutLanesNum();
    const std::int32_t GetRightLanesNum();
    const std::vector<std::pair<std::string, double>> GetObstaclesInSequence();
    const std::string GetDebugContent();
    const Point2d GetProjectionPoint();
    const std::vector<std::vector<LaneConstPtr>> GetCompleteSequences();
    const ObstacleForLane GetNearestObstacle();
    const float GetScoreInStraightJunction();
    uint64_t FindSamePrevLane(
        const std::vector<LaneConstPtr> &other_lane_sequence);

 private:
    bool is_occupy_lane_seq_ = false;
    bool is_optimal_lane_seq_ = false;
    float navi_distance_ = 1000.0;
    float sequence_idx_ = 0.0;
    float nearest_obstacle_vel_ = 0.0;
    float nearest_obstacle_distance_ = 150;
    float distance_to_ego_car_ = 0.0;
    float score_in_straight_junction_ = 0.0;
    bool is_navi_sequence_ = false;
    std::int32_t right_roundabout_lanes_num_ = -1;
    std::int32_t right_lanes_num_ = -1;
    std::string debug_content_;
    Point2d projection_point_;
    std::vector<std::vector<LaneConstPtr>> complete_sequences_;
    std::vector<std::pair<std::string, double>> obstacles_in_sequence_;
    float probability_ = 0.0;
    LcReason lc_reason_ = LcReason::LC_REASON_NONE;
    ObstacleForLane nearest_obstacle_;
};

typedef std::shared_ptr<NavigableLaneSequence> NavigableLaneSequencePtr;
typedef std::shared_ptr<LaneSequence> LaneSequencePtr;

using CandidateSequencesPtr =
    std::shared_ptr<std::vector<NavigableLaneSequencePtr>>;
using CandidateSequencesConstPtr =
    std::shared_ptr<const std::vector<NavigableLaneSequencePtr>>;

enum BehaviorCommand {
    Command_Invalid = 0,
    Command_LaneChangeLeft = 1,
    Command_LaneChangeRight = 2,
    Command_LaneChangeCancel = 3
};
enum LaneChangeDir { Lc_Straight = 0, Lc_Left = 1, Lc_Right = 2 };
struct LaneSeqInfo {
    SectionInfo cur_section;
    int cur_section_lane_num = 0;
    int cur_lane_position = -1;

    LaneSequencePtr lane_seq = nullptr;
    LaneConstPtr nearest_lane = nullptr;
    LaneConstPtr navi_end_lane = nullptr;
    LaneConstPtr junction_lane = nullptr;
    double dist_to_navi_end = std::numeric_limits<double>::infinity();
    bool lane_seq_connect_navi_end = false;
    bool is_current = false;
    BehaviorCommand lc_dir = Command_Invalid;

    double dist_to_left_solid_line = std::numeric_limits<double>::infinity();
    double dist_to_right_solid_line = std::numeric_limits<double>::infinity();

    LaneConstPtr merge_lane = nullptr;
    LaneConstPtr be_merged_lane = nullptr;
    BehaviorCommand merge_command = Command_Invalid;

    double dist_to_junction = std::numeric_limits<double>::infinity();
    double dist_to_junction_id = std::numeric_limits<double>::infinity();
    double left_solid_dist = std::numeric_limits<double>::infinity();
    double right_solid_dist = std::numeric_limits<double>::infinity();
    BehaviorCommand navi_lc_command = Command_Invalid;

    int lc_num = 0;

    int cur_lc_num = 0;
    bool next_junction_turn = false;

    double dist_to_enter_mainboard = std::numeric_limits<double>::infinity();
    double dist_to_exit_mainboard = std::numeric_limits<double>::infinity();

    BehaviorCommand overtake_lc_command = Command_Invalid;

    double dist_to_bus_lane = std::numeric_limits<double>::infinity();

    int pnp_top1_lc_reason = 0;

    LcReason lc_reason = LC_REASON_NONE;

    double dist_to_merge = std::numeric_limits<double>::infinity();
    double dist_to_split = std::numeric_limits<double>::infinity();
    double dist_to_be_merged = std::numeric_limits<double>::infinity();
    double dist_to_left_long_solid = std::numeric_limits<double>::infinity();
    double dist_to_right_long_solid = std::numeric_limits<double>::infinity();
    double left_solid_length = std::numeric_limits<double>::infinity();
    double right_solid_length = std::numeric_limits<double>::infinity();
    double dist_to_avoidance = std::numeric_limits<double>::infinity();

    double dist_to_junction_v2 = std::numeric_limits<double>::infinity();
    double dist_to_navi_end_v2 = std::numeric_limits<double>::infinity();
    ads_x::planning::V2TurnInfo::V2DetailTurnType nearest_turn_type_v2 =
        ads_x::planning::V2TurnInfo::V2DetailTurnType::NONE;
    ads_x::planning::V2TurnInfo::V2DetailTurnType last_turn_type_v2 =
        ads_x::planning::V2TurnInfo::V2DetailTurnType::NONE;
};
typedef std::shared_ptr<LaneSeqInfo> LaneSeqInfoPtr;
}  // namespace planning
}  // namespace ads_x
