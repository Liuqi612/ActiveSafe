
#pragma once

#include <map>
#include <utility>
#include <vector>

#include "maps/lane_point.h"
#include "maps/semantic_map_defs.h"
#include "math/piecewise_linear_function.h"
#include "util/map_util.h"
#include "util/status_macros.h"
#include <absl/container/flat_hash_map.h>
#include <absl/hash/hash.h>
#include <absl/status/status.h>
#include <absl/status/statusor.h>

namespace pnc_x {
namespace planning {

struct SmoothedReferenceCenterResult {
    absl::flat_hash_map<pnc_x::mapping::ElementId,
                        PiecewiseLinearFunction<double, double>>
        lane_id_to_smoothed_lateral_offset;

    absl::StatusOr<double> GetSmoothedLateralOffset(
        const mapping::LanePoint &lane_point) const;
};

using SmoothedResultMap =
    std::map<std::vector<mapping::ElementId>, SmoothedReferenceCenterResult>;

class SmoothedReferenceLineResultMap {
 public:
    SmoothedReferenceLineResultMap() = default;

    bool Contains(const std::vector<mapping::ElementId> &lane_ids) const;

    void AddResult(std::vector<mapping::ElementId> lane_ids,
                   SmoothedReferenceCenterResult smoothed_results);

    void DeleteResult(const std::vector<mapping::ElementId> &lane_ids);

    void Clear();

    const SmoothedResultMap &smoothed_result_map() const;

    absl::StatusOr<std::vector<mapping::ElementId>> FindOverlapSmoothedLaneIds(
        const std::vector<mapping::ElementId> &lane_ids) const;

    absl::StatusOr<SmoothedReferenceCenterResult> FindOverlapSmoothedResult(
        const std::vector<mapping::ElementId> &lane_ids) const;

    void AddSmoothLaneForRamp(mapping::ElementId id, bool is_end);

    bool IfSmoothLaneForRamp(mapping::ElementId id) const;

    bool IsSmoothLaneEnd(mapping::ElementId id) const;

    const std::unordered_map<mapping::ElementId, bool> &GetSmoothLaneForRamp();

    void ClearSmoothLanesForRamp();

    void SetSmoothReferencelineForRamp(bool &should_smooth);

    bool GetSmoothReferencelineForRamp() const;

 private:
    SmoothedResultMap smoothed_result_map_;
    std::unordered_map<mapping::ElementId, bool> need_smooth_lanes_for_ramp_{};
    bool if_smooth_referenceline_for_ramp_{false};
};

}  // namespace planning
}  // namespace pnc_x
