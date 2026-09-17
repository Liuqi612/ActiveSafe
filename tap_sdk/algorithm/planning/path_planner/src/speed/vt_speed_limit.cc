

#include "speed/vt_speed_limit.h"

#include <memory>

namespace pnc_x {
namespace planning {

void MergeVtSpeedLimit(const VtSpeedLimit &source, VtSpeedLimit *target) {
    if (source.size() != target->size()) {
        return;
    }
    for (int i = 0; static_cast<unsigned long>(i) < source.size(); ++i) {
        if (source[static_cast<unsigned long>(i)].speed_limit <
            (*target)[static_cast<unsigned long>(i)].speed_limit) {
            (*target)[static_cast<unsigned long>(i)] =
                source[static_cast<unsigned long>(i)];
        }
    }
    return;
}

}  // namespace planning
}  // namespace pnc_x
