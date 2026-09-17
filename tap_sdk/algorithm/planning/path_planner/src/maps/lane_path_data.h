
#pragma once

#include <stddef.h>

#include <string>
#include <utility>
#include <vector>

#include "pncx_lane_path.pb.h"
#include "maps/lane_point.h"
#include "maps/semantic_map_defs.h"
#include "common/log.h"

namespace pnc_x {
namespace mapping {

class LanePathData {
 public:
    LanePathData() = default;
    LanePathData(double start_fraction,
                 double end_fraction,
                 std::vector<ElementId> lane_ids,
                 bool lane_path_in_forward_direction = true);
    explicit LanePathData(const LanePathProto &lane_path_proto);

    explicit LanePathData(const LanePoint &lane_point);

    bool empty() const;
    size_t size() const;

    double start_fraction() const;
    double end_fraction() const;
    bool lane_path_in_forward_direction() const;

    const std::vector<ElementId> &lane_ids() const;
    ElementId lane_id(size_t index) const;

    LanePoint start_point() const;

    LanePoint end_point() const;

    bool operator==(const LanePathData &other) const;

    bool operator!=(const LanePathData &other) const;

    void FromLanePathProto(const LanePathProto &lane_path_proto);
    void ToLanePathProto(LanePathProto *lane_path_proto) const;

    void Clear();

    std::string DebugString() const;

    struct LaneSegmentData {
        ElementId lane_id;
        double start_fraction;
        double end_fraction;
    };

    LaneSegmentData lane_segment_data(int index) const;
    LaneSegmentData front() const;
    LaneSegmentData back() const;

 private:
    double start_fraction_ = 0.0;
    double end_fraction_ = 0.0;
    std::vector<ElementId> lane_ids_;
    bool lane_path_in_forward_direction_ = true;
};

}  // namespace mapping
}  // namespace pnc_x
