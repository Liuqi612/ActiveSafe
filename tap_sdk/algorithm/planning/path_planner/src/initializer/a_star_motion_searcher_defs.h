#pragma once

#include <algorithm>
#include <array>
#include <string>
#include <utility>
#include <vector>

#include "initializer/motion_search_types.h"
#include "initializer/motion_graph.h"
#include "pncx_initializer_config.pb.h"
#include "math/util.h"
#include "plan/planner_defs.h"
#include "pncx_trajectory_point.pb.h"
#include <absl/container/flat_hash_map.h>
#include <absl/hash/hash.h>

namespace pnc_x {
namespace planning {

struct AStarSearchNode {
    double accumulated_t = 0.0;
    uint64_t index = 0;
    uint64_t pred_index = 0;
    GeometryNodeIndex geom_node_idx;
    bool is_start = false;
    bool open = false;
    bool close = false;
    double g_cost = 0.0;
    double h_cost = 0.0;
    double total_cost = 0.0;
    std::vector<double> feature_costs;

    MotionForm *motion_form;
    GeometryEdgeIndex geom_edge_idx;
    IgnoreTrajMap ignored_trajs;
    std::string DebugString() const {
        return absl::StrCat("total_cost: ", total_cost,
                            "\n Space edge index: ", geom_edge_idx.value());
    }

    void SetIndex(const GeometryGraph &geom_graph,
                  const InitializerConfig &initializer_params);

    friend std::ostream &operator<<(std::ostream &os,
                                    const AStarSearchNode &node);
};

class SptDebugNode {
 public:
    SptDebugNode() = default;
    int index_;
    int prev_index_;
    double x_;
    double y_;
    double heading_;
    double v_;
    double omega_;
    double s_;
    double l_;
    double a_;
    double t_;
    double kappa_;
};

}  // namespace planning
}  // namespace pnc_x
