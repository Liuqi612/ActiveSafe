
#pragma once

#include <optional>
#include <vector>

#include "path_planner/src/common/type_def.h"
#include "pncx_constraint.pb.h"
#include "path_planner/src/decision/constraint_manager.h"

namespace pnc_x {
namespace planning {

struct DeciderOutput {
    ConstraintManager constraint_manager;
    DeciderStateProto decider_state;
    boost::optional<double> distance_to_traffic_light_stop_line = boost::none;
    int tl_stop_interface = 0;
};

}  // namespace planning
}  // namespace pnc_x
