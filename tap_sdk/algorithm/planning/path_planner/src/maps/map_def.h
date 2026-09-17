
#pragma once

#include <optional>
#include <string>
#include <vector>

#include "common/type_def.h"

namespace ads_x {
namespace planning {
enum FeatureType {
    FEATURETYPE_LANE = 0,
    FEATURETYPE_LANEBOUNDARY = 1,
    FEATURETYPE_ROADBOUNDARY = 2,
    FEATURETYPE_STOPLINE = 3,
    FEATURETYPE_JUNCTION = 4,
    FEATURETYPE_CROSSWALK = 5,
    FEATURETYPE_SPEEDBUMP = 6,
    FEATURETYPE_CLEARAREA = 7,
};

enum LineColor {
    COLOR_UNKNOWN = 0,
    COLOR_WHITE = 1,
    COLOR_YELLOW = 2,
    COLOR_ORANGE = 3,
    COLOR_BLUE = 4,
    COLOR_GREEN = 5,
    COLOR_GRAY = 6,
    LEFT_GRAY_RIGHT_YELLOW = 7,
    LEFT_YELLOW_RIGHT_WHITE = 8,
    LEFT_WHITE_RIGHT_YELLOW = 9,
    OTHER = 10
};

enum LineType {
    UNKNOWN = 0,
    SOLID = 1,
    DASHED = 2,
    SOLID_SOLID = 3,
    DASHED_DASHED = 4,
    SOLID_DASHED = 5,
    DASHED_SOLID = 6,
    SHADED_AREA = 7,
    VIRTUAL_LANE = 8,
    VIRTUAL_JUNCTION = 9,
    RAMP = 10,
    FISH_LINE = 11,
    CURB_LINE = 12,
    FISH_SOLID = 13,
    FISH_DASH = 14,
    SHADED_AREA_MARKING = 15,
    PREDICTION_LANE = 16,
};

enum BoundaryType {
    UNKNOWN_BOUNDARY = 0,
    LANELINE = 1,
    CURB = 2,
    CENTER = 3,
    GUARDRAIL = 4,
    CONCRETE_BARRIER = 5,
    FENCE = 6,
    WALL = 7,
    CANOPY = 8,
    PAVE = 9,
    DITCH = 10,
    PUNCHEON = 11,
    VIRTUAL = 12,
    LIDAR_UU = 13,
    OCC_UU = 14,
    OCC_CURB = 15,
    OCC_VEGETATION = 16,
    OCC_CONJECTURE = 17,
    WATERFILLED = 18,
    CONEBARRIER = 19
};

enum LaneType {
    LANE_UNKNOWN = 0,
    LANE_NORMAL = 1,
    LANE_ACC = 2,
    LANE_DEC = 3,
    LANE_RAMP = 4,
    LANE_EMERGENCY = 5,
    LANE_ACC_DCC = 6,
    LANE_BUS_NORMAL = 7,
    LANE_HOV_NORMAL = 8,
    LANE_NON_MOTOR = 9,
    LANE_LEFT_WAIT = 10,
    LANE_VIRTUAL_COMMON = 11,
    LANE_VIRTUAL_JUNCTION = 12,
    LANE_ROUND_ABOUT = 13,
    LANE_INTERSECTION = 14,
    LANE_VIRTUAL = 15,
    LANE_WIDE = 16
};

enum class CompositeTurnType {
    NORMAL_TURN = 0,
    LEFT_STRAIGHT = 1,
    STRAIGHT_RIGHT = 2,
    LEFT_RIGHT = 3,
    LEFT_STRAIGHT_RIGHT = 4
};

enum LightStatus {
    NONE_LIGHT = 0,
    GREEN_LIGHT = 1,
    YELLOW_LIGHT = 2,
    RED_LIGHT = 3,
    UNKNOWN_LIGHT = 4,
    YELLOW_BLINKING = 5,
    FAIL_DETECTION = 6,
    BLOCK_FAIL = 7
};

enum StopLineReason {
    REASON_NONE = 0,
    REASON_LIGHT_RED = 1,
    REASON_LIGHT_YELLOW = 2,
    REASON_CONFIRM = 3
};

enum StopLineInterface {
    STOP_LINE_NONE = 0,
    STOP_LINE_RED = 1,
    STOP_LINE_YELLOW = 2,
    STOP_LINE_CONFIRM = 3,
    STOP_LINE_UNKNOWN = 4,
    STOP_LINE_FAIL_DETECT = 5,
    STOP_LINE_LCC_TURN = 6,
    STOP_LINE_T_JUNCTION = 10
};

struct FsdTrafficLightDeciderInfo {
    double dist_to_stopline = std::numeric_limits<double>::max();
    double dist_to_leftwait_stopline = std::numeric_limits<double>::max();
    bool ego_is_in_leftwait = false;
    bool first_virtual_lane_is_leftwait = false;
    uint64_t first_virtual_lane = 0;
    uint64_t focus_lane = 0;
    uint64_t left_wait_lane = 0;
    LightStatus first_virtual_lane_light = NONE_LIGHT;
    LightStatus focus_lane_light = NONE_LIGHT;
    LightStatus left_wait_lane_light = NONE_LIGHT;
};

struct TrafficLightStatus {
    uint64_t lane_id;
    uint64_t junction_id = 0;
    LightStatus light_status = LightStatus::NONE_LIGHT;
    bool stop_line = false;
    bool is_left_wait_lane = false;

    double tl_stop_s_;
    bool tl_is_stop_ = false;
    bool have_light_ = false;
    double max_speed_ = 70.0;
};

using TrafficLightStatusMap = std::unordered_map<uint64_t, TrafficLightStatus>;

enum MergeTopology {
    TOPOLOGY_MERGE_NONE = 0,
    TOPOLOGY_MERGE_LEFT = 1,
    TOPOLOGY_MERGE_RIGHT = 2,
    TOPOLOGY_TO_BE_MERGED = 3,
    TOPOLOGY_MERGE_UNKNOWN = 4
};

enum SplitTopology {
    TOPOLOGY_SPLIT_NONE = 0,
    TOPOLOGY_SPLIT_LEFT = 1,
    TOPOLOGY_SPLIT_RIGHT = 2,
    TOPOLOGY_SPLIT_UNKNOWN = 3
};

enum class MergeTopoSubType : int {
    MERGE_UNKNOWN = 0,
    MERGE_FROM_LEFT = 1,
    MERGE_FROM_RIGHT = 2,
    MERGE_CONTINUATION_ON_LEFT = 3,
    MERGE_CONTINUATION_ON_RIGHT = 4,
    Y_MERGE_FROM_LEFT = 5,
    Y_MERGE_FROM_RIGHT = 6
};

struct MergeInfo {
    std::string id = "";
    MergeTopoSubType merge_subtype = MergeTopoSubType::MERGE_UNKNOWN;
    MergeTopology merge_topo = MergeTopology::TOPOLOGY_MERGE_NONE;
    std::string main_lane_id = "";
    std::string merge_lane_id = "";
};

enum NoneOddType { TYPE_NONE = 0, TYPE_TOLL = 1, TYPE_CONSTRUCTION = 2 };

enum MapRoadClass {
    RC_UNKNOWN = 0,
    RC_EXPRESSWAY = 1,
    RC_URBAN_EXPRESSWAY = 2,
    RC_NATION_ROAD = 3,
    RC_PROVINCE_ROAD = 4,
    RC_RESERVE = 5,
    RC_COUNTRY_ROAD = 6,
    RC_TOWN_ROAD = 7,
    RC_SPECIAL_ROAD = 8,
    RC_WALK_ROAD = 9,
    RC_PEOPLE_FERRY = 10,
    RC_FERRY = 11,
    RC_OTHERS = 99
};

enum SectionType {
    Unknown = 0,
    Main = 1,
    Auxiliary = 2,
    EntryRamp = 3,
    ExitRamp = 4,
    Ramp = 5,
    JCT = 6,
    Service = 7,
    Intersection = 8,
    Roundabout = 9,
    Pedestrian = 10,
    Parallel = 11,
    TollBooth = 12,
    Tunnel = 13,
    Bridge = 14,
    Viaduct = 15,
    TollGate = 16,
    TollEntry = 17,
    TollExit = 18,
    Breakup = 19,
    MultipleCarriageWay = 20,
    SingleCarriageWay = 21,
    CrossLink = 22,
    SlipRoad = 23,
    SideRoad = 24,
    SlipAndJCT = 25,
    TurnRightLineA = 26,
    TurnRightLineB = 27,
    TurnLeftLineA = 28,
    TurnLeftLineB = 29,
    TurnLeftRightLine = 30,
    ServiceAndSlipRoad = 31,
    ServiceAndJCT = 32,
    ServiceAndSlipRoadAndJCT = 33,
    NextToRamp = 254,
    Other = 255,
};
enum PoiType {
    Poi_NaviEnd = 0,
    Poi_Split = 1,
    Poi_To_Be_Merged = 2,
    Poi_Merge = 3,
    Poi_Enter_Mainboard = 4,
    Poi_Exit_Mainboard = 5,
    Poi_To_Avoidance = 6,
    Poi_To_Long_Solid_Left = 7,
    Poi_To_Long_Solid_Right = 8
};

enum XRoadType {
    XRoadType_Ramp = 0,
    XRoadType_NoneOdd = 1,
    XRoadType_Tunnel = 2
};

enum ImpassableAeraType {
    UNKNOWN_KIND = 0,
    FLOWERBED = 1,
    SENTRY_BOX = 2,
    PHYSICAL_SAFE_ISLAND = 3,
    LINEAR_SAFE_ISLAND = 4
};
enum StopLineType {
    STOPLINETYPE_UNKNOWN = 0,
    STOPLINETYPE_STRAIGHT = 1,
    STOPLINETYPE_LEFT_WAIT = 2
};

enum class LinkType : uint32_t {
    NONE = 0,
    Continue = 1,
    Split = 2,
    Merge = 3,
    WideStepByStep = 4,
    NarrowStepByStep = 5,
    OpeningAndEnding = 6,
    EndingAndOpening = 7,
    TurnLeft = 8,
    TurnRight = 9,
    TurnLeftAround = 10,
    TurnRightAround = 11,
    TurnLeftArea = 12,
    Straight = 13,
    StraightArea = 14,
    Stitch = 15,
    Others = 16,
    LinkType_MIN = 17,
    LinkType_MAX = 18,
    Unknown = 19
};

struct RoadBoundaryInfo {
    uint64_t id;
    double width = 0.0;
    std::vector<Point2d> points;
    BoundaryType boundary_type = UNKNOWN_BOUNDARY;
};

struct RoadBoundaryType {
    double s = 0.0;
    double width = 0.0;
    BoundaryType boundary_type = UNKNOWN_BOUNDARY;
};

struct LaneBoundarySegmentInfo {
    std::string id;
    std::vector<Point2d> points;
    LineType line_type = UNKNOWN;
    LineColor line_color = COLOR_UNKNOWN;
};

struct LaneBoundaryType {
    double s = 0.0;
    LineType line_type = UNKNOWN;
    LineColor line_color = COLOR_UNKNOWN;
};

struct LaneBoundaryInfo {
    uint64_t id;
    std::vector<Point2d> points;
    LaneBoundaryType boundary_type;
};

struct LaneLinkData {
    uint64_t link_id = 0;
    std::pair<uint64_t, uint64_t> from_to_lane_id;
    LinkType link_type;
    std::vector<math::Vec2d> points;
    double length = 0.0;
};

struct LaneInfo {
    uint64_t id = 0;
    uint64_t section_id = 0;
    uint64_t junction_id = 0;
    uint64_t left_lane_id = 0;
    uint64_t right_lane_id = 0;
    std::vector<uint64_t> next_lane_ids;
    std::vector<uint64_t> left_lane_boundary_ids;
    std::vector<uint64_t> right_lane_boundary_ids;
    std::vector<uint64_t> left_road_boundary_ids;
    std::vector<uint64_t> right_road_boundary_ids;
    LaneType type = LANE_NORMAL;
    NoneOddType none_odd_type = TYPE_NONE;
    uint32_t turn_type_v3 = 0;
    TurnType turn_type = NO_TURN;
    TurnType turn_type_v2 = NO_TURN;
    LightStatus light_status = NONE_LIGHT;
    SplitTopology split_topology = TOPOLOGY_SPLIT_NONE;
    MergeTopology merge_topology = TOPOLOGY_MERGE_NONE;
    std::vector<Point2d> points;
    std::vector<double> lane_widths;
    double length = 0.0;
    double speed_limit = 135 / 3.6;
    bool is_virtual = false;
    bool is_navigation = false;
    bool stop_line = false;
    std::vector<uint64_t> cross_walks;
    std::vector<uint64_t> speed_bumps;
    std::vector<uint64_t> parking_spaces;
    std::vector<uint64_t> clear_areas;
    std::vector<uint64_t> traffic_stop_lines;
    std::vector<uint64_t> traffic_lights;
    std::vector<std::pair<double, double>> length_curvature_pairs_;
    int32_t lane_operation_type = 0;
    std::vector<double> coeffs;
    int32_t arrow_type = 0;

    std::vector<LaneLinkData> lane_links;

    bool RampAshore = false;
    bool RampExit = false;
    bool force_avoidance_line = false;
};
struct SectionInfo {
    uint64_t id = 0;
    double length = 0.0;
    bool is_highway = false;
    NoneOddType none_odd_type = TYPE_NONE;
    std::vector<uint64_t> lane_ids;
    uint64_t navi_priority_lane_id = 0;
    MapRoadClass road_class = MapRoadClass::RC_UNKNOWN;
    int is_valid = 0;
    void Clear() {
        id = 0;
        length = 0.0;
        is_highway = false;
        none_odd_type = TYPE_NONE;
        lane_ids.clear();
        navi_priority_lane_id = 0;
        road_class = MapRoadClass::RC_UNKNOWN;
        is_valid = 0;
    }
};
struct NaviPosition {
    uint64_t section_id;
    double s_offset;
};
struct RouteInfo {
    uint64_t id;
    NaviPosition navi_start;
    NaviPosition navi_end;
    std::vector<SectionInfo> sections;
    double trusted_curvature_path_s_max =
        std::numeric_limits<double>::infinity();
};

enum class NoaTrafficLightStatus : std::uint8_t {
    Unknown = 0,
    Invalid = 1,
    Off = 2,
    Green = 3,
    Yellow = 4,
    Red = 5,
    GreenFlash = 6,
    YellowFlash = 7,
    RedFlash = 8
};

enum class NoaTrafficLightShape : std::uint8_t {
    None = 0,
    Unknown = 1,
    Circle = 2,
    Pedestrian = 3,
    LeftArrow = 4,
    StraightArrow = 5,
    RightArrow = 6,
    AroundArrow = 7,
    LeftStraightArrow = 8,
    LeftAroundArrow = 9,
    RightStraightArrow = 10,
    Bicycle = 11,
    TrafficClose = 12,
    Timer = 13,
    TrafficAllow = 14,
    Other = 255,
};

struct NoaTrafficSignal {
    NoaTrafficLightShape shape = NoaTrafficLightShape::None;
    NoaTrafficLightStatus status = NoaTrafficLightStatus::Unknown;
};

enum class NoaDetectionStatus : std::uint8_t {
    Unknown = 0,
    PurePerception = 1,
    PureHDM = 2,
    Fusion = 3,
};

struct NoaTrafficLightInfo {
    uint64_t id;
    std::vector<uint64_t> lane_ids;
    std::vector<Point2d> points;
    NoaDetectionStatus detection_status = NoaDetectionStatus::Unknown;
    int16_t countdown = -1;
    double confidence = 1.0;
    double length = 0.0;
    double width = 0.0;
    double height = 0.0;
    std::vector<NoaTrafficSignal> signals;
};

struct StopLineInfo {
    uint64_t id;
    std::vector<uint64_t> lane_ids;
    std::vector<Point2d> points;
    StopLineType type;
    LightStatus light_type;
    int8_t sub_type;
    int8_t virtual_type;
};
struct JunctionInfo {
    uint64_t id;
    uint64_t type;
    std::vector<Point2d> points;
    std::vector<uint64_t> from_section_ids;
    std::vector<uint64_t> to_section_ids;
};
struct CrossWalkInfo {
    uint64_t id;
    std::vector<Point2d> points;
};
struct SpeedBumpInfo {
    uint64_t id;
    std::vector<Point2d> points;
};
struct ParkingSpaceInfo {
    uint64_t id;
    std::vector<Point2d> points;
};
struct ClearAreaInfo {
    uint64_t id;
    ImpassableAeraType type;
    std::vector<Point2d> points;
};

enum JunctionType {
    kDefault = 0,
    kGateway = 1,
    kCross = 2,
    kRoundabout = 3,
    kUturn = 4,
    kLaneMerge = 5,
    kLaneSplit = 6,
    kRoadDeadEnd = 7,
    kGatewayWithinCity = 8,
    kTollgate = 9,
    kRoadMergeOrSplit = 10,
    kNOA = 11,
};
struct V2RoadClass {
    double start_s = 0.0;
    double end_s = 0.0;
    enum V2RoadClassType {
        UNKNOWN_ROAD = 0,
        HIGH_WAY_ROAD = 1,
        EXPRESS_WAY_ROAD = 2,
        NATIOANL_ROAD = 3,
        PROVINCIAL_ROAD = 4,
        MAIN_ROAD = 5,
        SUB_ROAD = 6
    };
    V2RoadClassType type = UNKNOWN_ROAD;
};

struct V2TrafficFlow {
    double start_s = 0.0;
    double end_s = 0.0;
    enum V2TrafficFlowType {
        UNKNOWN_FLOW = 0,
        SMOOTH_FLOW = 1,
        SLOW_FLOW = 2,
        JAMMED_FLOW = 3,
        SERVERE_JAMMED_FLOW = 4,
        NO_FLOW = 5
    };
    V2TrafficFlowType type = UNKNOWN_FLOW;
};

struct RoadInfo {
    int road_class = 0;
    int lane_num = 0;
};

struct PassInfo {
    int curr_index = -1;
    int index_num = -1;
};

struct V2TurnInfo {
    std::string id = "";
    bool is_valid = false;
    enum V2TurnType {
        UNKNOWN = 0,
        LEFT = 1,
        RIGHT = 2,
        STRAIGHT = 3,
        U_TURN_LEFT = 4,
        U_TURN_RIGHT = 5,
        MERGE_LEFT = 6,
        MERGE_RIGHT = 7,
        RAMP_LEFT = 11,
        RAMP_RIGHT = 12,
        RAMP_STRAIGHT = 13,
        RAMP_U_TURN_LEFT = 14,
        RAMP_U_TURN_RIGHT = 15,
    };
    V2TurnType turn_type = UNKNOWN;
    enum V2DetailTurnType {
        NONE = 0,
        TURN_LEFT = 2,
        TURN_RIGHT = 3,
        SLIGHT_LEFT = 4,
        SLIGHT_RIGHT = 5,
        TURN_HARD_LEFT = 6,
        TURN_HARD_RIGHT = 7,
        UTURN = 8,
        CONTINUE = 9,
        TURN_RIGHT_ONLY = 10,
        UTURN_RIGHT = 19,
        LEFT_MERGE = 65,
        RIGHT_MERGE = 66,
    };
    V2DetailTurnType detail_turn_type = NONE;
    double dist = 0.0;
    uint32_t original_dist = 0;
    RoadInfo before_turn;
    RoadInfo after_turn;
    std::vector<std::string> infos;
    PassInfo straight_pass_info;
};

struct EHPV2Info {
    bool has_navigation = false;
    double dist_to_ramp = 0.0;
    double dist_to_toll = 0.0;
    std::vector<V2RoadClass> road_class;
    std::vector<V2TrafficFlow> traffic_flow;
    std::vector<V2TurnInfo> turn_info;
};

struct LaneLinkRepo {
    std::unordered_map<uint64_t, std::vector<LaneLinkData>> next_links;
};

enum class TrafficLightStatusIdl : std::uint8_t {
    Unknown = 0,
    Invalid = 1,
    Off = 2,
    Green = 3,
    Yellow = 4,
    Red = 5,
    GreenFlash = 6,
    YellowFlash = 7,
    RedFlash = 8,
    Masked = 9
};

enum class TrafficLightShapeIdl : std::uint8_t {
    None = 0,
    Unknown = 1,
    Circle = 2,
    Pedestrian = 3,
    LeftArrow = 4,
    StraightArrow = 5,
    RightArrow = 6,
    AroundArrow = 7,
    LeftStraightArrow = 8,
    LeftAroundArrow = 9,
    RightStraightArrow = 10,
    Bicycle = 11,
    TrafficClose = 12,
    Timer = 13,
    TrafficAllow = 14,
    Other = 255,
};

struct TrafficLightInfoIdl {
    TrafficLightShapeIdl shape = TrafficLightShapeIdl::None;
    TrafficLightStatusIdl status = TrafficLightStatusIdl::Unknown;
    float count_down = -1.0F;
    uint16_t shape_confidence = -1;
    uint16_t status_confidence = -1;
    uint16_t count_down_confidence = -1;
    std::vector<uint64_t> traffic_light_ids;
};

struct PassableInfo {
    TrafficLightInfoIdl straight_tfl_info;
    TrafficLightInfoIdl left_tfl_info;
    TrafficLightInfoIdl right_tfl_info;
    TrafficLightInfoIdl uturn_tfl_info;
};

struct MapInfo {
    MapType type = BEV_MAP;
    MapSubType sub_type{HIGHWAY_HD};
    double timestamp = 0.0;
    int64_t seq = 0;
    bool is_on_highway = false;
    std::vector<LaneInfo> all_lanes_vec;
    std::vector<LaneBoundaryInfo> all_lane_boundaries_vec;
    std::vector<RoadBoundaryInfo> all_road_boundaries_vec;
    std::vector<StopLineInfo> all_stop_lines_vec;
    std::vector<JunctionInfo> all_junctions_vec;
    std::vector<CrossWalkInfo> all_cross_walks_vec;
    std::vector<SpeedBumpInfo> all_speed_bumps_vec;
    std::vector<NoaTrafficLightInfo> all_traffic_lights_vec;
    std::vector<ParkingSpaceInfo> all_parking_spaces_vec;
    std::vector<ClearAreaInfo> all_clear_areas_vec;
    RouteInfo route;
    EHPV2Info v2_info;
    PassableInfo passable_info;
    LaneLinkRepo lane_link_info;
    uint64_t cur_lane_id = 0;
    uint64_t cur_junction_id = 0;
    uint32_t map_usage = 0;
};

}  // namespace planning
}  // namespace ads_x
