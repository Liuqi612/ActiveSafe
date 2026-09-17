
#pragma once

#include <limits>

#include "optimization/problem/mixed_fourth_order_bicycle.h"
#include "plan/planner_defs.h"

namespace pnc_x {
namespace planning {
namespace optimizer {

using Mfob = MixedFourthOrderBicycle;

struct LeadingInfo {
    double s = std::numeric_limits<double>::infinity();
    double v = std::numeric_limits<double>::infinity();
};

}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
