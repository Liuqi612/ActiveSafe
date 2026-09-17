#ifndef TAP_SDK_ALGORITHM_ELK_ELK_DEBUG_LOGGER_H_
#define TAP_SDK_ALGORITHM_ELK_ELK_DEBUG_LOGGER_H_

#include "elk_state_machine.h"
#include "interface/active_safety_coreout.h"

#include <cstdint>

namespace active_safety {
namespace elk {

uint64_t BuildBoundaryFalseTriggerDebugBus(const LaneBoundaryParameters &lane_boundary);

void LogElkFrame(const AsVseOut &vse_out,
                 const LanesInfo &road_info,
                 const GlobalConfig &config,
                 const LaneBoundaryParameters &lane_boundary,
                 const LaneCenterParameters &lane_center,
                 const ElkTaSl &ta_info,
                 const ElkThreatDebugSnapshot &threat_debug,
                 const AsOnComingOut &oncoming_out,
                 const AsOverTakingOut &overtaking_out,
                 const ElkStateMachine &state_machine,
                 uint8_t rolling_counter);

} // namespace elk
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_ELK_ELK_DEBUG_LOGGER_H_