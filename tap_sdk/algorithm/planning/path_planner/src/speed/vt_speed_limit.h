
#pragma once

#include <vector>

#include "speed/speed_limit.h"

namespace pnc_x {
namespace planning {

using VtSpeedLimit = std::vector<SpeedLimit::SpeedLimitInfo>;

void MergeVtSpeedLimit(const VtSpeedLimit &source, VtSpeedLimit *target);

}  // namespace planning
}  // namespace pnc_x
