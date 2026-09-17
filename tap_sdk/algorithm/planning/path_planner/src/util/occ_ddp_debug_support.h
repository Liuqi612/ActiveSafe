#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>

namespace pnc_x {
namespace planning {

extern bool FLAGS_planner_enable_occ_debug;

struct OccDdpCsvFrameContext {
    int frame_id = -1;
    long long stamp_us = 0;
};

enum class OccDdpCsvRejectReason {
    kNone = 0,
    kSkipShort,
    kSkipCap,
    kSkipCross,
    kSkipSide,
    kSkipHeading,
    kSkipFarLateral,
    kSkipPolygonFarLateral,
    kSkipPolygonShape,
    kSkipDominantEdge,
};

inline const char* OccDdpCsvRejectReasonName(OccDdpCsvRejectReason reason) {
    switch (reason) {
        case OccDdpCsvRejectReason::kSkipShort:
            return "skip_short";
        case OccDdpCsvRejectReason::kSkipCap:
            return "skip_cap";
        case OccDdpCsvRejectReason::kSkipCross:
            return "skip_cross";
        case OccDdpCsvRejectReason::kSkipSide:
            return "skip_side";
        case OccDdpCsvRejectReason::kSkipHeading:
            return "skip_heading";
        case OccDdpCsvRejectReason::kSkipFarLateral:
            return "skip_far_lateral";
        case OccDdpCsvRejectReason::kSkipPolygonFarLateral:
            return "skip_polygon_far_lateral";
        case OccDdpCsvRejectReason::kSkipPolygonShape:
            return "skip_polygon_shape";
        case OccDdpCsvRejectReason::kSkipDominantEdge:
            return "skip_dominant_edge";
        case OccDdpCsvRejectReason::kNone:
        default:
            return "";
    }
}

struct OccSegmentCollectionStats {
    size_t polygon_count = 0;
    size_t accepted_polygon_count = 0;
    size_t accepted_segment_count = 0;
    size_t skip_short_segment_count = 0;
    size_t skip_cap_edge_count = 0;
    size_t skip_cross_ref_count = 0;
    size_t skip_side_ambiguous_count = 0;
    size_t skip_heading_count = 0;
    size_t skip_far_lateral_count = 0;
    size_t skip_polygon_far_lateral_count = 0;
    size_t skip_polygon_shape_count = 0;
    size_t skip_dominant_edge_count = 0;
};

struct OccBufferConfigDebugInfo {
    std::string source_name;
    double soft_extra = 0.0;
    double hard_extra = 0.0;
    double cutoff_distance = 0.0;
};

struct OccStaticBoundarySummaryDebugInfo {
    size_t map_below_count = 0;
    size_t map_above_count = 0;
    size_t occ_segment_count = 0;
    size_t occ_start_count = 0;
    size_t below_count = 0;
    size_t below_start_count = 0;
    size_t above_count = 0;
    size_t above_start_count = 0;
    size_t uturn_count = 0;
    size_t uturn_start_count = 0;
    OccSegmentCollectionStats occ_stats;
};

struct OccStaticBoundaryCallDebugInfo {
    std::string source_name;
    size_t segment_count = 0;
    size_t start_count = 0;
    double nearest_dist = 0.0;
    double lane_width = 0.0;
};

struct OccUpdateCostGateDebugInfo {
    std::string cost_name;
    int horizon = 0;
    int last_real_point_index = -1;
    bool enable_station_gate = false;
    const std::vector<int>* indices = nullptr;
    int calc_steps = 0;
    int gated_steps = 0;
    int first_calc_step = -1;
    int first_gated_step = -1;
};

inline bool IsOccDebugEnabled() { return FLAGS_planner_enable_occ_debug; }

inline void OccDebugPrintBufferConfig(const OccBufferConfigDebugInfo& info) {
    if (!IsOccDebugEnabled()) {
        return;
    }
    std::printf(
        "[occ][AddMsdStaticBoundaryCostV2] source=%s soft_extra=%.3f "
        "hard_extra=%.3f disable_decay=1 cutoff=%.3f\n",
        info.source_name.c_str(), info.soft_extra, info.hard_extra,
        info.cutoff_distance);
}

inline void OccDebugPrintStaticBoundarySummary(
    const OccStaticBoundarySummaryDebugInfo& info) {
    if (!IsOccDebugEnabled()) {
        return;
    }
    std::printf(
        "[occ][AddStaticBoundaryCosts] map_below=%zu map_above=%zu "
        "occ_segments=%zu occ_starts=%zu below=%zu below_start=%zu above=%zu "
        "above_start=%zu uturn=%zu uturn_start=%zu occ_polygons=%zu "
        "occ_accept_polygons=%zu occ_accept_segs=%zu occ_skip_short=%zu "
        "occ_skip_cap=%zu occ_skip_cross=%zu occ_skip_side=%zu "
        "occ_skip_heading=%zu occ_skip_far_lateral=%zu "
        "occ_skip_polygon_far_lateral=%zu occ_skip_polygon_shape=%zu "
        "occ_skip_dominant_edge=%zu\n",
        info.map_below_count, info.map_above_count, info.occ_segment_count,
        info.occ_start_count, info.below_count, info.below_start_count,
        info.above_count, info.above_start_count, info.uturn_count,
        info.uturn_start_count, info.occ_stats.polygon_count,
        info.occ_stats.accepted_polygon_count,
        info.occ_stats.accepted_segment_count,
        info.occ_stats.skip_short_segment_count,
        info.occ_stats.skip_cap_edge_count,
        info.occ_stats.skip_cross_ref_count,
        info.occ_stats.skip_side_ambiguous_count,
        info.occ_stats.skip_heading_count,
        info.occ_stats.skip_far_lateral_count,
        info.occ_stats.skip_polygon_far_lateral_count,
        info.occ_stats.skip_polygon_shape_count,
        info.occ_stats.skip_dominant_edge_count);
}

inline void OccDebugPrintStaticBoundaryCall(
    const OccStaticBoundaryCallDebugInfo& info) {
    if (!IsOccDebugEnabled()) {
        return;
    }
    std::printf(
        "[occ][AddStaticBoundaryCosts] call V2 source=%s "
        "segments=%zu starts=%zu nearest_dist=%.3f lane_width=%.3f\n",
        info.source_name.c_str(), info.segment_count, info.start_count,
        info.nearest_dist, info.lane_width);
}

inline void OccDebugPrintUpdateCostNoHelper(const std::string& cost_name,
                                            int horizon) {
    if (!IsOccDebugEnabled()) {
        return;
    }
    std::printf(
        "[occ][UpdateCost] name=%s helper=null horizon=%d calc_steps=%d "
        "gated_steps=0\n",
        cost_name.c_str(), horizon, horizon);
}

inline void OccDebugPrintUpdateCostGate(
    const OccUpdateCostGateDebugInfo& info) {
    if (!IsOccDebugEnabled()) {
        return;
    }
    const std::vector<int> empty_indices;
    const std::vector<int>& indices =
        info.indices == nullptr ? empty_indices : *info.indices;
    std::stringstream ss;
    ss << "[occ][UpdateCost] name=" << info.cost_name
       << " horizon=" << info.horizon
       << " last_real_point_index=" << info.last_real_point_index
       << " enable_station_gate=" << info.enable_station_gate
       << " indices_size=" << indices.size()
       << " calc_steps=" << info.calc_steps
       << " gated_steps=" << info.gated_steps
       << " first_calc_step=" << info.first_calc_step
       << " first_gated_step=" << info.first_gated_step
       << " first_indices=[";
    const int preview_n = std::min<int>(static_cast<int>(indices.size()), 8);
    for (int i = 0; i < preview_n; ++i) {
        if (i > 0) {
            ss << ",";
        }
        ss << indices[i];
    }
    ss << "]";
    std::printf("%s\n", ss.str().c_str());
}

}  // namespace planning
}  // namespace pnc_x
