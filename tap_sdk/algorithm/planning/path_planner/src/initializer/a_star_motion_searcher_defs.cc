
#include "initializer/a_star_motion_searcher_defs.h"

namespace pnc_x {
namespace planning {

void AStarSearchNode::SetIndex(const GeometryGraph &geom_graph,
                               const InitializerConfig &initializer_params) {
    const auto &astar_search_config = initializer_params.astar_search_config();
    uint64_t pos_size = static_cast<uint64_t>(geom_graph.nodes().size());
    uint64_t discrete_v = motion_form->GetEndMotionState().v /
                          astar_search_config.velocity_resolution();
    uint64_t discrete_t = accumulated_t / astar_search_config.time_resolution();
    uint64_t v_size = astar_search_config.max_velocity() /
                      astar_search_config.velocity_resolution();
    uint64_t t_size =
        astar_search_config.max_time() / astar_search_config.time_resolution();
    index = static_cast<uint64_t>(geom_node_idx.value()) + (discrete_v * pos_size) +
            (discrete_t * v_size * pos_size);
}

std::ostream &operator<<(std::ostream &os, const AStarSearchNode &node) {
    if (node.is_start) {
        os << ", t: " << node.accumulated_t << ", gcost: " << node.g_cost
           << ", hcost: " << node.h_cost << ", total_cost: " << node.total_cost
           << "\n";
    } else {
        os << ", t: " << node.accumulated_t
           << ", v: " << node.motion_form->GetEndMotionState().v
           << ", gcost: " << node.g_cost << ", hcost: " << node.h_cost
           << ", total_cost: " << node.total_cost << "\n";
    }
    return os;
}

}  // namespace planning
}  // namespace pnc_x
