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
    OCC = 16
};

enum class FusionSource : uint8_t {
    SINGLE_TRACKLET = 0,
    MULTIPLE_TRACKLET = 1,
    VISION_ONLY = 2,
    RADAR_VISION = 3,
    SRR_ONLY = 4,
};

enum class ObsConfidence : uint8_t { LOW_CONF = 0, HIGH_CONF = 1 };

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
    LCA = (1 << 13),
    AES = (1 << 14),
    ESA = (1 << 15),
    SCENE1 = (1 << 16),
    SCENE2 = (1 << 17),
    LDW = (1 << 18),
    LKA = (1 << 19),
    ELK = (1 << 20)
};

enum class OnOffStatus : uint8_t { NotActive = 0, Active = 1 };

// 实际档位 actual_gear（VSE 映射: trans_estd_gear 12→3,13→2,14→1,15→0,其余→4）
enum class GearPosition : uint8_t { PARK = 0, REVERSE = 1, NEUTRAL = 2, DRIVE = 3, UNKNOWN = 4 };

// 转向灯开关档位 turn_light_switch_pos: 0x0:Neutral, 0x1:Left, 0x2:illegal combination, 0x3:Right
enum class TurnLightSwitchPos : uint8_t { NEUTRAL = 0, LEFT = 1, ILLEGAL = 2, RIGHT = 3 };

// 危险报警灯状态 hazard_lamp_st: 0:Not Pressed, 1:Pressed
enum class HazardLampStatus : uint8_t { NOT_PRESSED = 0, PRESSED = 1 };

// 车门状态 fl/fr/rl/rr_door_st: 0:Not Open, 1:Open
enum class DoorStatus : uint8_t { NOT_OPEN = 0, OPEN = 1 };

// 自动制动系统可用性掩码 esp_brake_available_st（来源 WI_AutoBrkSysAvailMask）
// Bit0:AebAvailable, Bit1:AbpAvailable, Bit2:AwbAvailable, Bit3:AbaAvailable
enum class BrakeSysAvailMask : uint32_t {
    AEB = 1 << 0,
    ABP = 1 << 1,
    AWB = 1 << 2,
    ABA = 1 << 3,
};

// function_did_config 中各功能故障诊断标志的序号
enum class FunctionDid : uint8_t {
    AEB       = 0,
    AES       = 1,
    ESA       = 2,
    ELK       = 3,
    FCTA_FCTB = 4,
    RCTA_RCTB = 5,
    RCW       = 6,
    BSD       = 7,
    DOW       = 8,
    LKA       = 9,
    LDW       = 10
};


// switch_req 输出码: 0:Default 1:灯光+声音 2:关闭 3:灯光
enum class SwitchReqOut : uint8_t { DEFAULT = 0, LIGHT_AND_SOUND = 1, OFF = 2, LIGHT = 3 };

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

enum class FunctionInhibitMask {
    AEB = 1 << 0,
    LKA = 1 << 1,
    ESA = 1 << 2,
    AES = 1 << 3,
    ELK = 1 << 4,
    LOCP = 1 << 5,
    FCTA_B = 1 << 6,
    RCTA_B = 1 << 7,
    DOW = 1 << 8,
    FCW = 1 << 9,
    BSD = 1 << 10,
    RCW = 1 << 11,
    LDW = 1 << 12
};

} // namespace active_safety
