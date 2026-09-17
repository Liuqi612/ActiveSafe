
#pragma once

#include <boost/optional.hpp>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "async/thread_pool.h"
#include "maps/map_def.h"
#include "maps/semantic_map_defs.h"
#include "math/geometry/segment2d.h"
#include "math/vec.h"
#include <absl/status/status.h>

namespace pnc_x {
namespace planning {

constexpr double kDefaultMaxSpeedLimit = 50.0;

struct PlannerSemanticMapModification {
    std::map<mapping::ElementId, double> lane_speed_limit_map;
    double max_speed_limit = kDefaultMaxSpeedLimit;

    bool IsEmpty() const;
};

// struct ImpassableBoundaryInfo {
//     Segment2d segment;
//     std::string id;
//     boost::optional<double> height;
//     ads_x::planning::RoadBoundaryType type;
// };

}  // namespace planning
}  // namespace pnc_x
