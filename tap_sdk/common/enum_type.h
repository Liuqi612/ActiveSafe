#pragma once
#include <cstddef>
#include <cstdint>
namespace active_safety {
enum class TrackStatus : uint8_t {
    INVALID = 0,
    MERGED = 1,
    NEW = 2,
    NEW_COASTED = 3,
    NEW_UPDATED = 4,
    UPDATED = 5,
    COASTED = 6,
    RESERVED = 7,
};
enum class ObjectClass : uint8_t {
    UNDETERMINED = 0,
    CAR = 1,
    MOTORCYCLE = 2,
    TRUCK = 3,
    PEDESTRIAN = 4,
    POLE = 5,
    TREE = 6,
    ANIMAL = 7,
    GOD = 8,
    BICYCLE = 9,
    UNIDENTIFIED_VEHICLE = 10,
    THREEWHEEl_VEHICLE = 11,
    ESCOOTER = 12,
    GENOBJ = 13,
    BUS = 14,
    CONE = 15,
};

enum class FusionSource : uint8_t {
    SINGLE_TRACKLET = 0,
    MULTIPLE_TRACKLET = 1,
    VISION_ONLY = 2,
    RADAR_VISION = 3,
    SRR_ONLY = 4,
};

enum AsObstacleMotionPattern { AS_OBS_MP_UNKNOWN, AS_OBS_MP_STATIONARY, AS_OBS_MP_MOV_FROM_SELF, AS_OBS_MP_MOV_TO_SELF };

enum AsShadowMode {
    UNKNOWN = 0,
    SHADOWMODE = (1 << 0),
    AEB = (1 << 1),
    EBA = (1 << 2),
    FCW = (1 << 3),
    DW = (1 << 4),
    AWB = (1 << 5),
    DOW = (1 << 6),
    RCW = (1 << 7),
    FCTA = (1 << 8),
    FCTB = (1 << 9),
    RCTA = (1 << 10),
    RCTB = (1 << 11),
    BSD = (1 << 12),
    LCA = (1 << 13)
};

enum class OnOffStatus : uint8_t { NotActive = 0, Active = 1 };

enum class AebStatus : uint8_t { AEB_OFF = 0, AEB_Fault = 1, AEB_Inhibit = 2, AEB_Standby = 3, AEB_Active = 4, EBA_Active = 5 };

enum class FcwStatus : uint8_t { FCW_OFF = 0, FCW_Inhibit = 1, FCW_Standby = 2, FCW_Active = 3, FCW_Fault = 4 };

enum class BsdState { OFF, FAULT, INHIBIT, STANDBY, ACTIVE };
enum class DowState { OFF, FAULT, INHIBIT, STANDBY, ACTIVE };
enum class RcwState { OFF, FAULT, INHIBIT, STANDBY, ACTIVE };
enum class CtsState { OFF, FAULT, INHIBIT, STANDBY, ACTIVE };

enum class TargetObjColor : uint8_t { NONE = 0, YELLOW = 1, RED = 2 };

enum class DisplayStatus : uint8_t { OFF = 0, ON = 1, FAILURE = 2, INHIBITED = 3 };

enum FcwWarnDist { NORMAL = 0, NEAR = 1, FAR = 2 };

enum class WarnLevel : uint8_t { NO_REQUEST = 0, LEVEL_1 = 1, LEVEL_2 = 2, LEVEL_3 = 3 };

enum FcwAebTextInfo {
    DEFAULT_TEXT = 0,
    FCW_IS_ACTIVE = 1,
    FCW_IS_SWITCHED_ON = 2,
    UNABLE_TO_SWITCH_ON_FCW = 3,
    FCW_IS_SWITCHED_OFF = 4,
    FCW_IS_IN_ERROR_MODE = 5,
    AEB_IS_ACTIVE = 6,
    AEB_IS_SWITCHED_ON = 7,
    UNABLE_TO_SWITCH_ON_AEB = 8,
    AEB_IS_SWITCHED_OFF = 9,
    AEB_IS_IN_ERROR_MODE = 10
};

enum DrivingSoundWarn { DEFAULT_WARNING = 0, TIP_WARNING = 1, ACTIVE_WARNING = 2, FAILED_WARNING = 3, SAFETY_WARNING = 4, WARNING_SOUND = 5 };

enum CtaWorkingStatus { DEFAULT = 0, OFF = 1, ONLY_WARING = 2, WARING_BRAKE = 3 };

enum CtbCollisionDir { No_Collsion = 0, LEFT = 1, RIGHT = 2, LEFT_RIGHT = 3 };

enum class FaultAlarmId {
    ConfigLoadError = 7300,
    FusionFaild = 7310,         // ObjId: 1:No fusion target input, 2: Fusion target timestamp error
    PerceptionLaneFaild = 7320, // ObjId: 1:No lane perception input,2:Lane perception timestamp error
    McuMsgFalid = 7340,         // ObjId: 1:No MCU control input,2:MCU control timestamp error
    PerceptionGopFaild = 7350,  // ObjId: 1:No /perception/lidar_gop/object input,2:/perception/lidar_gop/object timestamp error
    OccMsgFaild = 7360          // ObjId: 1:No /perception/nv_cameras/occ_info input 2:/perception/nv_cameras/occ_info timestamp error
};

enum class FaultType { Config = 1 << 0, Fusion = 1 << 1, Lane = 1 << 2, Vehicle = 1 << 3, Gop = 1 << 4 };

} // namespace active_safety
