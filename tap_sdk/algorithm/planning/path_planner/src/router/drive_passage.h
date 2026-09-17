
#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "container/strong_vector.h"
#include <absl/status/status.h>
#include <absl/container/flat_hash_set.h>
#include <absl/status/statusor.h>
#include <absl/types/span.h>
#include "common/log.h"

#include "maps/lane_path.h"
#include "maps/lane_point.h"
#include "maps/map_def.h"
#include "maps/semantic_map_defs.h"
#include "math/frenet_common.h"
#include "math/frenet_frame.h"
#include "math/geometry/box2d.h"
#include "math/geometry/polygon2d.h"
#include "math/geometry/segment2d.h"
#include "math/vec.h"
#include "async/future.h"
#include "maps/map_def.h"
#include "maps/semantic_map_defs.h"
#include "async/async_macro.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace pnc_x {
namespace planning {

DECLARE_STRONG_VECTOR(Station);

using LaneType = ads_x::planning::LaneType;
using TurnType = ads_x::planning::TurnType;
using SplitTopology = ads_x::planning::SplitTopology;
using MergeTopology = ads_x::planning::MergeTopology;

enum class StationSplitInfo { NO_SPLIT, SPLIT_FROM, SPLIT_TO };

enum class AD_FunctionType {
    None = 0,
    ACC = 1,
    LFP = 2,
    HNOP = 3,
    CNOP = 4,
    MNOP = 5
};

enum struct AD_LateralState {
    LANE_KEEP = 0,
    LEFT_PRE_LANE_CHANGE = 1,
    RIGHT_PRE_LANE_CHANGE = 2,
    LEFT_LANE_CHANGE = 3,
    RIGHT_LANE_CHANGE = 4,
    LEFT_LANE_CHANGE_HOLD = 5,
    RIGHT_LANE_CHANGE_HOLD = 6,
    LEFT_LANE_CHANGE_CANCEL = 7,
    RIGHT_LANE_CHANGE_CANCEL = 8,
    LEFT_LANE_CHANGE_FINISH = 9,
    RIGHT_LANE_CHANGE_FINISH = 10,
    LEFT_LANE_BORROW = 11,
    RIGHT_LANE_BORROW = 12,
    LEFT_LANE_CHANGE_FAIL = 13,
    RIGHT_LANE_CHANGE_FAIL = 14,
    LANE_SELECT = 15, 
    LANE_SELECT_FINISH = 16,
};

struct StationInfo {
    bool is_in_intersection = false;
    bool is_exclusive_right_turn = false;
    bool is_in_roundabout = false;
    bool is_in_wide_lane = false;
    double speed_limit = DBL_MAX;
    LaneType lane_type = LaneType::LANE_NORMAL;
    TurnType turn_type = TurnType::NO_TURN;
    SplitTopology split_topo = SplitTopology::TOPOLOGY_SPLIT_NONE;
    MergeTopology merge_topo = MergeTopology::TOPOLOGY_MERGE_NONE;
    StationSplitInfo station_split_info = StationSplitInfo::NO_SPLIT;
};

struct StationCenter {
    mapping::ElementId lane_id = mapping::kInvalidElementId;
    double fraction = 0.0;
    Vec2d xy;
    Vec2d tangent;
    double accum_s = 0.0;
    double speed_limit = 0.0;
    bool is_virtual = false;
    bool is_backward_extended = false;
    bool is_merging = false;
    bool is_splitting = false;
    bool is_in_intersection = false;
    bool is_in_wide_lane = false;
    bool has_cross_curb = false;
    ads_x::planning::TurnType turn_type;
    StationInfo station_info;

    mapping::LanePoint GetLanePoint() const;

    Vec2d lat_point(double signed_offset) const;
    Vec2d lon_point(double signed_offset) const;
    double lat_offset(const Vec2d &v) const;
    double lon_offset(const Vec2d &v) const;
};

enum StationBoundaryType {

    BROKEN_WHITE = 0,
    SOLID_WHITE = 1,
    BROKEN_YELLOW = 2,
    SOLID_YELLOW = 3,
    SOLID_DOUBLE_YELLOW = 4,
    CURB = 5,
    VIRTUAL_CURB = 6,
    BROKEN_LEFT_DOUBLE_WHITE = 7,
    BROKEN_RIGHT_DOUBLE_WHITE = 8,
    VIRTUAL_LANE = 9,

    UNKNOWN_TYPE = 99
};

std::string StationBoundaryTypeName(StationBoundaryType type);

struct StationBoundary {
    StationBoundaryType type;
    double lat_offset;

    bool IsSolid(double query_lat_offset) const;
};

using OptionalBoundary = boost::optional<StationBoundary>;
struct BoundaryQueryResponse {
    OptionalBoundary right;
    OptionalBoundary left;
};

class Station {
 public:
    explicit Station(StationCenter center, std::vector<StationBoundary> bounds);

    mapping::ElementId lane_id() const;
    const Vec2d &xy() const;
    const Vec2d &tangent() const;
    double accumulated_s() const;
    double speed_limit() const;
    bool is_virtual() const;

    StationInfo station_info() const;
    bool is_merging() const;
    bool is_splitting() const;
    bool is_in_wide_lane() const;
    bool is_in_intersection() const;
    bool has_cross_curb() const;
    ads_x::planning::TurnType turn_type() const;

    Vec2d lat_point(double signed_offset) const;
    Vec2d lon_point(double signed_offset) const;
    double lat_offset(const Vec2d &v) const;
    double lon_offset(const Vec2d &v) const;

    absl::Span<const StationBoundary> boundaries() const;

    absl::StatusOr<std::pair<double, double>> QueryCurbOffsetAt(
        double signed_lat) const;

    absl::StatusOr<BoundaryQueryResponse> QueryEnclosingLaneBoundariesAt(
        double signed_lat) const;

    mapping::LanePoint GetLanePoint() const;

 private:
    StationCenter center_;

    std::vector<StationBoundary> boundaries_;
};

struct StationWaypoint {
    StationIndex station_index;
    double lon_offset;
    double accum_s;
};

struct ImpassableBoundaryInfo {
    Segment2d segment;
    std::string id;
    boost::optional<double> height;
    ads_x::planning::RoadBoundaryType type;
};

class DrivePassage {
 public:
    DrivePassage() = default;
    DrivePassage(StationVector<Station> stations,
                 mapping::LanePath lane_path,
                 mapping::LanePath extend_lane_path,
                 double lane_path_start_s,
                 bool reach_destination,
                 FrenetFrameType type,
                 std::vector<int> change_index,
                 ads_x::planning::LaneSeqInfoPtr lane_seq_info = nullptr);

    DrivePassage(DrivePassage const &o);

    DrivePassage &operator=(DrivePassage const &o);

    DrivePassage(DrivePassage &&o) = default;
    DrivePassage &operator=(DrivePassage &&o) = default;

    absl::StatusOr<double> QuerySpeedLimitAt(const Vec2d &point) const;
    absl::StatusOr<double> QuerySpeedLimitAtS(double s) const;

    absl::StatusOr<std::pair<double, double>> QueryCurbOffsetAt(
        const Vec2d &point) const;
    absl::StatusOr<std::pair<double, double>> QueryCurbOffsetAtS(
        double s) const;

    absl::StatusOr<std::pair<double, double>> QueryNearestBoundaryLateralOffset(
        double s) const;

    absl::StatusOr<std::pair<Vec2d, Vec2d>> QueryCurbPointAt(
        const Vec2d &point) const;

    absl::StatusOr<std::pair<Vec2d, Vec2d>> QueryCurbPointAtS(double s) const;

    absl::StatusOr<BoundaryQueryResponse> QueryEnclosingLaneBoundariesAt(
        const Vec2d &point) const;
    BoundaryQueryResponse QueryEnclosingLaneBoundariesAtS(double s) const;

    absl::StatusOr<Vec2d> QueryLaterallyUnboundedTangentAt(
        const Vec2d &point) const;

    absl::StatusOr<Vec2d> QueryTangentAt(const Vec2d &point) const;
    absl::StatusOr<Vec2d> QueryTangentAtS(double s) const;
    absl::StatusOr<double> QueryTangentAngleAtS(double s) const;

    absl::StatusOr<Vec2d> QueryPointXYAtS(double s) const;

    absl::StatusOr<Vec2d> QueryPointXYAtSL(double s, double l) const;

    absl::StatusOr<StationWaypoint> QueryFrenetLonOffsetAt(
        const Vec2d &point) const;

    absl::StatusOr<double> QueryFrenetLatOffsetAt(const Vec2d &point) const;

    absl::StatusOr<FrenetCoordinate> QueryFrenetCoordinateAt(
        const Vec2d &point) const;

    absl::StatusOr<FrenetBox> QueryFrenetBoxAt(const Box2d &box,
                                               bool zone_checking = true) const;

    absl::StatusOr<FrenetBox> QueryFrenetBoxAtContour(
        const Polygon2d &contour, bool zone_checking = true) const;

    absl::StatusOr<FrenetCoordinate> QueryLaterallyUnboundedFrenetCoordinateAt(
        const Vec2d &point) const;

    absl::StatusOr<FrenetCoordinate> QueryUnboundedFrenetCoordinateAt(
        const Vec2d &point) const;

    absl::StatusOr<std::vector<boost::optional<FrenetBox>>>
    BatchQueryFrenetBoxes(absl::Span<const Box2d> boxes,
                          bool laterally_bounded) const;

    absl::StatusOr<Vec2d> FindNearestPointOnCenterLine(
        const Vec2d &point) const;

    StationIndex FindNearestStationIndex(const Vec2d &point) const;
    const Station &FindNearestStation(const Vec2d &point) const;

    StationIndex FindNearestStationIndexAtS(double s) const;
    const Station &FindNearestStationAtS(double s) const;

    double end_s() const;
    double front_s() const;
    double lane_path_start_s() const;
    bool beyond_lane_path() const;
    bool reach_destination() const;

    bool ContainIntersection(const int check_step) const;
    double GetDistanceToIntersection(const Vec2d &point) const;
    double GetDistanceToNonIntersection(const Vec2d &point) const;
    const Station &GetFirstNonIntersectionStation(const Vec2d &point) const;

    bool empty() const;
    int size() const;

    const Station &station(StationIndex index) const;
    const StationVector<Station> &stations() const;
    StationIndex last_real_station_index() const;
    const std::vector<int> &change_index() const;

    const FrenetFrame *frenet_frame() const;

    const mapping::LanePath &extend_lane_path() const;

    const mapping::LanePath &lane_path() const;

    const std::vector<Segment2d> &segments() const;
    const ads_x::planning::LaneSeqInfoPtr lane_seq_info() const;

    const bool GetIsChangeAbnormal() const;
    void SetIsChangeAbnormal(bool is_change_abnormal);
    const bool GetIsChangeAbnormalForDegrade() const;
    void SetIsChangeAbnormalForDegrade(bool is_change_abnormal_for_degrade);

    const int GetAbnormalStep() const;
    void SetAbnormalStep(int abnormal_step);

    // add ego turn type and has_split
    void SetEgoTurnType(TurnType ego_turn_type);
    TurnType GetEgoTurnType() const;

    void SetHasSplit(bool has_split);
    bool GetHasSplit() const;

    void SetIsOnRamp(bool has_split);
    bool GetIsOnRamp() const;

    void SetAdFunctionType(AD_FunctionType ad_function_type);
    AD_FunctionType GetAdFunctionType() const;

    void SetAdLateralState(AD_LateralState ad_lateral_state);
    AD_LateralState GetAdLateralState() const;

    absl::StatusOr<std::pair<Station, Station>> GetNearStation(double s) const;

    std::unordered_map<uint64_t, ads_x::planning::LanePtr> GetLaneMap() const {
        return lane_map_;
    };
    // std::vector<ads_x::planning::LaneConstPtr> GetLanes() const {
    //     return lanes_;
    // };
    std::unordered_map<uint64_t, ads_x::planning::LaneBoundaryPtr>
    GetLaneBoundaryMap() const {
        return lane_boundary_map_;
    };
    std::unordered_map<uint64_t, ads_x::planning::RoadBoundaryPtr>
    GetRoadBoundaryMap() const {
        return road_boundary_map_;
    };

    ads_x::planning::RoadBoundaryConstPtr GetRoadBoundaryById(
        const uint64_t id) const;

    void InitRoadBoundaryRTree();
    std::vector<ads_x::planning::RoadBoundaryConstPtr>
    FindRoadBoundariesInRadius(double lon, double lat, double radius) const;
    std::vector<pnc_x::mapping::v2::Segment> FindRoadBoundarySegmentsInRadius(
        double lon, double lat, double radius) const;
    std::vector<ImpassableBoundaryInfo> GetImpassableBoundariesInfo(
        const Vec2d &smooth_coord, double radius) const;
    std::vector<ads_x::planning::RoadBoundaryConstPtr> GetRoadBoundaries(
        const Vec2d &smooth_coord, double radius) const;

    ads_x::planning::MapInfo map_info;
    std::unordered_map<uint64_t, ads_x::planning::LanePtr> lane_map_;
    // std::vector<ads_x::planning::LaneConstPtr> lanes_;
    std::unordered_map<uint64_t, ads_x::planning::LaneBoundaryPtr>
        lane_boundary_map_;
    std::unordered_map<uint64_t, ads_x::planning::RoadBoundaryPtr>
        road_boundary_map_;

 private:
    struct ProjectionResult {
        StationIndex station_index_1;
        StationIndex station_index_2;
        StationIndex near_station_index;
        double accum_s;
        double signed_l;
        double lerp_factor;
    };

    absl::StatusOr<ProjectionResult> ProjectPointToStations(
        const Vec2d &point, bool allow_extrapolation) const;
    absl::StatusOr<ProjectionResult> ProjectPointToStationsWithinRadius(
        const Vec2d &point,
        const ProjectionResult &projection,
        const Vec2d &prev_point,
        double search_radius) const;
    absl::Status IsProjectionResultOnDrivePassage(
        const ProjectionResult &res) const;
    absl::StatusOr<boost::optional<FrenetBox>> QueryFrenetBoxWithinRadius(
        const Box2d &box,
        const ProjectionResult &center_projection,
        double search_radius,
        bool laterally_bounded) const;
    absl::StatusOr<FrenetBox> QueryFrenetBoxAtContourPoints(
        absl::Span<const Vec2d> contour_points,
        bool zone_checking = true) const;

    struct BinarySeachResult {
        StationIndex station_index_1;
        StationIndex station_index_2;
        StationIndex near_station_index;
        double ds;
    };

    BinarySeachResult BinarySearchForNearStation(double s) const;

    void BuildFrenetFrame();

    StationVector<Station> stations_;
    StationIndex last_real_station_index_;

    std::vector<double> center_seg_inv_len_;
    mapping::LanePath lane_path_;
    mapping::LanePath extend_lane_path_;
    bool beyond_lane_path_;
    bool reach_destination_;
    double lane_path_start_s_;
    std::vector<Segment2d> segments_;

    FrenetFrameType type_;
    ads_x::planning::LaneSeqInfoPtr lane_seq_info_ = nullptr;
    std::vector<int> change_index_;
    std::unique_ptr<FrenetFrame> frenet_frame_;

    bool is_change_abnormal_ = false;
    bool is_change_abnormal_for_degrade_ = false;
    int abnormal_step_ = 0;

    TurnType ego_turn_type_;
    bool has_split_ = false;
    bool is_on_ramp_ = false;
    AD_FunctionType ad_function_type_ = AD_FunctionType::None;
    AD_LateralState ad_lateral_state_ = AD_LateralState::LANE_KEEP;
    struct SmoothPoint {
        double x;
        double y;
    };

    using RTreePoint = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>;
    using RTreeBox = boost::geometry::model::box<RTreePoint>;
    using RTreeValue = std::pair<RTreeBox, std::pair<pnc_x::mapping::ElementId, pnc_x::mapping::SegmentId>>;
    using RoadBoundaryRTree = boost::geometry::index::rtree<RTreeValue, boost::geometry::index::quadratic<16>>; 
    
    RoadBoundaryRTree road_boundary_rtree_;
};

}  // namespace planning
}  // namespace pnc_x
