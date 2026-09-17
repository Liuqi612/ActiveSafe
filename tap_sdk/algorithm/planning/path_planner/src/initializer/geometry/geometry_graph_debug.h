
#pragma once

#include <string>
#include <vector>

#include "pncx_initializer.pb.h"
#include "initializer/geometry/geometry_graph.h"
#include <absl/status/status.h>
#include <absl/strings/str_cat.h>

namespace pnc_x {
namespace planning {

enum class ResampleReason {
    RESAMPLED = 1,
    NR_ZERO_REACHABLE = 2,
    NR_ALL_REACHABLE = 3,
    NR_INVALID_RANGE = 4,
    NR_LATERAL_RESOLUTION = 5,
    NOT_INITIALIZED = 6
};

struct EdgeDebugInfo {
    int start_layer_idx;
    int start_node_on_layer_idx;
    int end_layer_idx;
    int end_node_on_layer_idx;
    int start_station_idx;
    int end_station_idx;

    std::string Debug() const {
        std::string debug_str =
            "\n\tLayer Idx\tNode on Layer Idx\tStation Idx\n";
        debug_str += absl::StrCat("Start\t", start_layer_idx, "\t",
                                  start_node_on_layer_idx, "\t",
                                  start_station_idx, "\n");
        debug_str +=
            absl::StrCat("End\t", end_layer_idx, "\t", end_node_on_layer_idx,
                         "\t", end_station_idx, "\n");
        debug_str += "\n---------------------------------------------";
        return debug_str;
    }
};

absl::Status CheckGeometryGraphConnectivity(const GeometryGraph &graph);

}  // namespace planning
}  // namespace pnc_x
