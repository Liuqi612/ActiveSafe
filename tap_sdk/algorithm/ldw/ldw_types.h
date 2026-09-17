#ifndef TAP_SDK_ALGORITHM_LDW_LDW_TYPES_H_
#define TAP_SDK_ALGORITHM_LDW_LDW_TYPES_H_

#include "algorithm/elk/environment_processing.h"

#include <cstdint>

namespace active_safety {
namespace ldw {

using LaneBoundaryParameters = active_safety::elk::LaneBoundaryParameters;
using LaneCenterParameters = active_safety::elk::LaneCenterParameters;

struct LdwOutput {
    uint8_t rolling_count = 0;
    uint8_t major_version = 1;
    uint8_t minor_version = 3;
    uint8_t state = 0;
    bool available = false;
    bool left_warning = false;
    bool right_warning = false;
    bool left_departure_detected = false;
    bool right_departure_detected = false;
    float lane_center_offset = 0.0F;
    float lane_center_heading = 0.0F;
    uint32_t suppress_mask = 0;
    uint16_t enable_mask = 0;
};

} // namespace ldw
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LDW_LDW_TYPES_H_
