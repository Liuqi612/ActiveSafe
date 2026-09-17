

#include "scheduler/smooth_reference_line_result.h"

namespace pnc_x {
namespace planning {

absl::StatusOr<double> SmoothedReferenceCenterResult::GetSmoothedLateralOffset(
    const mapping::LanePoint &lane_point) const {
    const PiecewiseLinearFunction<double, double> *plf =
        FindOrNull(lane_id_to_smoothed_lateral_offset, lane_point.lane_id());
    if (plf == nullptr) {
        return absl::NotFoundError("");
    } else {
        return (*plf)(lane_point.fraction());
    }
}

bool SmoothedReferenceLineResultMap::Contains(
    const std::vector<mapping::ElementId> &lane_ids) const {
    return FindOverlapSmoothedLaneIds(lane_ids).ok();
}

void SmoothedReferenceLineResultMap::AddResult(
    std::vector<mapping::ElementId> lane_ids,
    SmoothedReferenceCenterResult smoothed_results) {
    if (smoothed_result_map_.find(lane_ids) == smoothed_result_map_.end()) {
        smoothed_result_map_.emplace(std::move(lane_ids),
                                     std::move(smoothed_results));
    } else {
        smoothed_result_map_[lane_ids] = std::move(smoothed_results);
    }
}

void SmoothedReferenceLineResultMap::DeleteResult(
    const std::vector<mapping::ElementId> &lane_ids) {
    smoothed_result_map_.erase(lane_ids);
}

void SmoothedReferenceLineResultMap::Clear() { smoothed_result_map_.clear(); }

const SmoothedResultMap &SmoothedReferenceLineResultMap::smoothed_result_map()
    const {
    return smoothed_result_map_;
}

absl::StatusOr<SmoothedReferenceCenterResult>
SmoothedReferenceLineResultMap::FindOverlapSmoothedResult(
    const std::vector<mapping::ElementId> &lane_ids) const {
    ASSIGN_OR_RETURN(const auto overlap_lane_ids,
                     FindOverlapSmoothedLaneIds(lane_ids));
    return smoothed_result_map_.at(overlap_lane_ids);
}

void SmoothedReferenceLineResultMap::AddSmoothLaneForRamp(mapping::ElementId id,
                                                          bool is_end) {
    need_smooth_lanes_for_ramp_.insert(std::make_pair(id, is_end));
}

bool SmoothedReferenceLineResultMap::IfSmoothLaneForRamp(
    mapping::ElementId id) const {
    if (need_smooth_lanes_for_ramp_.find(id) !=
        need_smooth_lanes_for_ramp_.end()) {
        return true;
    }
    return false;
}

bool SmoothedReferenceLineResultMap::IsSmoothLaneEnd(
    mapping::ElementId id) const {
    auto iter = need_smooth_lanes_for_ramp_.find(id);
    if (iter != need_smooth_lanes_for_ramp_.end()) {
        return iter->second;
    }
    return true;
}

const std::unordered_map<mapping::ElementId, bool>
    &SmoothedReferenceLineResultMap::GetSmoothLaneForRamp() {
    return need_smooth_lanes_for_ramp_;
}

void SmoothedReferenceLineResultMap::ClearSmoothLanesForRamp() {
    need_smooth_lanes_for_ramp_.clear();
}

void SmoothedReferenceLineResultMap::SetSmoothReferencelineForRamp(
    bool &should_smooth) {
    if_smooth_referenceline_for_ramp_ = should_smooth;
}

bool SmoothedReferenceLineResultMap::GetSmoothReferencelineForRamp() const {
    return if_smooth_referenceline_for_ramp_;
}

absl::StatusOr<std::vector<mapping::ElementId>>
SmoothedReferenceLineResultMap::FindOverlapSmoothedLaneIds(
    const std::vector<mapping::ElementId> &lane_ids) const {
    if (lane_ids.empty()) { return absl::NotFoundError(""); }

    const auto it = smoothed_result_map_.find(lane_ids);
    if (it != smoothed_result_map_.end()) {
        return it->first;
    }

    for (const auto &pair_it : smoothed_result_map_) {
        if (pair_it.first.size() < lane_ids.size()) {
            continue;
        }

        for (int i = 0; i <= pair_it.first.size() - lane_ids.size(); ++i) {
            if (pair_it.first[i] == lane_ids[0]) {
                for (int j = 1; j < lane_ids.size(); ++j) {
                    if (pair_it.first[i + j] != lane_ids[j]) {
                        return absl::NotFoundError("");
                    }
                }
                return pair_it.first;
            }
        }
    }

    return absl::NotFoundError("");
}

}  // namespace planning
}  // namespace pnc_x
