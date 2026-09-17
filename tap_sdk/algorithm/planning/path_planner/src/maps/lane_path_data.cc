

#include "maps/lane_path_data.h"
#include <absl/strings/str_format.h>
#include <absl/strings/str_join.h>

namespace pnc_x {
namespace mapping {
LanePathData::LanePathData(double start_fraction,
                           double end_fraction,
                           std::vector<ElementId> lane_ids,
                           bool lane_path_in_forward_direction)
    : start_fraction_(start_fraction),
      end_fraction_(end_fraction),
      lane_ids_(std::move(lane_ids)),
      lane_path_in_forward_direction_(lane_path_in_forward_direction) {}

LanePathData::LanePathData(const LanePathProto &lane_path_proto) {
    FromLanePathProto(lane_path_proto);
}

LanePathData::LanePathData(const LanePoint &lane_point)
    : start_fraction_(lane_point.fraction()),
      end_fraction_(lane_point.fraction()),
      lane_ids_({lane_point.lane_id()}),
      lane_path_in_forward_direction_(true) {}

bool LanePathData::empty() const { return lane_ids_.empty(); }
size_t LanePathData::size() const { return lane_ids_.size(); }

double LanePathData::start_fraction() const { return start_fraction_; }
double LanePathData::end_fraction() const { return end_fraction_; }
bool LanePathData::lane_path_in_forward_direction() const {
    return lane_path_in_forward_direction_;
}

const std::vector<ElementId> &LanePathData::lane_ids() const {
    return lane_ids_;
}
ElementId LanePathData::lane_id(size_t index) const {
    if (!XCHECK_LT(index, lane_ids_.size())) {
        return 0UL;
    }
    return lane_ids_[index];
}

LanePoint LanePathData::start_point() const {
    if (!XCHECK(!empty())) {
        return {};
    }
    return {lane_ids_.front(), start_fraction_};
}

LanePoint LanePathData::end_point() const {
    if (!XCHECK(!empty())) {
        return {};
    }
    return {lane_ids_.back(), end_fraction_};
}

bool LanePathData::operator==(const LanePathData &other) const {
    if (start_fraction_ != other.start_fraction()) return false;
    if (end_fraction_ != other.end_fraction()) return false;
    if (lane_path_in_forward_direction_ !=
        other.lane_path_in_forward_direction())
        return false;

    if (lane_ids_.size() != other.size()) return false;
    for (size_t i = 0; i < lane_ids_.size(); ++i) {
        if (lane_ids_[i] != other.lane_id(i)) return false;
    }
    return true;
}

bool LanePathData::operator!=(const LanePathData &other) const {
    return !(*this == other);
}

LanePathData::LaneSegmentData LanePathData::front() const {
    if (!XCHECK_GE(size(), 1)) {
        return {};
    }
    return lane_segment_data(0);
}
LanePathData::LaneSegmentData LanePathData::back() const {
    if (!XCHECK_GE(size(), 1)) {
        return {};
    }
    return lane_segment_data(static_cast<int>(size()) - 1);
}

void LanePathData::FromLanePathProto(const LanePathProto &lane_path_proto) {
    lane_ids_.clear();
    lane_ids_.reserve(static_cast<size_t>(lane_path_proto.lane_ids_size()));
    for (const auto &lane_id : lane_path_proto.lane_ids()) {
        lane_ids_.push_back(ElementId(lane_id));
    }
    start_fraction_ = lane_path_proto.start_fraction();
    end_fraction_ = lane_path_proto.end_fraction();
    if (lane_path_proto.has_lane_path_in_forward_direction()) {
        lane_path_in_forward_direction_ =
            lane_path_proto.lane_path_in_forward_direction();
    } else {
        lane_path_in_forward_direction_ = true;
    }
}

void LanePathData::ToLanePathProto(LanePathProto *lane_path_proto) const {
    lane_path_proto->Clear();
    lane_path_proto->mutable_lane_ids()->Reserve(static_cast<int>(lane_ids_.size()));
    for (const auto &lane_id : lane_ids_) {
        lane_path_proto->add_lane_ids(lane_id);
    }
    lane_path_proto->set_start_fraction(start_fraction_);
    lane_path_proto->set_end_fraction(end_fraction_);
    lane_path_proto->set_lane_path_in_forward_direction(
        lane_path_in_forward_direction_);
}

void LanePathData::Clear() {
    start_fraction_ = 0.0;
    end_fraction_ = 0.0;
    lane_ids_.clear();
}

std::string LanePathData::DebugString() const {
    return absl::StrFormat(
        "lane ids: %s, start_fraction: %f, end_fraction: %f.",
        absl::StrJoin(lane_ids_, ", "), start_fraction_, end_fraction_);
}

LanePathData::LaneSegmentData LanePathData::lane_segment_data(int index) const {
    if (!XCHECK_GE(index, 0) || !XCHECK_LT(index, size())) {
        return {};
    }
    return LaneSegmentData{
        .lane_id = lane_id(static_cast<unsigned long>(index)),
        .start_fraction = (index == 0) ? start_fraction_ : 0.0,
        .end_fraction = (static_cast<unsigned long>(index) + 1UL == size())
                            ? end_fraction_
                            : 1.0,
    };
}

}  // namespace mapping
}  // namespace pnc_x
