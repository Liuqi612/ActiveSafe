
#include "maps/road_boundaries.h"
#include "common/gflags.h"
namespace ads_x {
namespace planning {
RoadBoundaries::RoadBoundaries(
    const std::vector<RoadBoundaryConstPtr> &boundaries) {
    for (auto boundary_ptr : boundaries) {
        if (!boundary_ptr->IsValid()) {
            continue;
        }
        boundaries_.emplace_back(boundary_ptr);
    }
}
}  // namespace planning
}  // namespace ads_x