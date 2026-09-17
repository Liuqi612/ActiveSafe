#pragma once
#include <stdint.h>

namespace active_safety {

enum class BrakeMode : uint8_t {
    // # 不请求刹车
    idle,
    // # 请求缓慢刹车(APA发送电刹+机械刹车)
    apaComfortable,
    // # 请求缓慢刹车(LAPA发送-仅电刹车)
    lApaComfortable,
    // # 请求急刹(APA/LAPA发送电刹+机械刹车)
    emergency
};

struct BrakeCmd {
    float     command      = 0.0f;
    uint8_t   commandType  = 0;
    bool      ignore       = false;
    uint32_t  parkingBrake = 0;
    BrakeMode brakeMode    = BrakeMode::idle;
};

struct VehicleCmdInfo {
    uint64_t time;
    BrakeCmd brake;
    bool     is_avp_state = false;
};

struct UicFsmCmdInfo {
    uint64_t time;
    bool     trust_meb_complete = false;
};

struct MebMsgInfo {
    VehicleCmdInfo meb_cmd;
    UicFsmCmdInfo  uic_cmd;
};

struct LongCtrlInfo {
    float    long_ctrl_decel = 0.0f;
    uint64_t time;
};

struct StateMachineInfo {
    uint8_t  state_machine_sts = 0;
    bool mcu_lfp_actv_cdt = false;
    uint64_t time;
};

struct PlanningInfo {
    LongCtrlInfo     long_ctrl;
    StateMachineInfo state_machine;
};
} // namespace active_safety
