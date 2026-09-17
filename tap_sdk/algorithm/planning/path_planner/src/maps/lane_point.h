
#pragma once

#include <algorithm>
#include <string>

#include "pncx_lane_point.pb.h"
#include "maps/semantic_map_defs.h"
#include "math/vec.h"
#include <absl/strings/str_format.h>

namespace pnc_x {
namespace mapping {

class LanePoint {
 public:
    LanePoint() = default;
    LanePoint(ElementId lane_id, double fraction);
    explicit LanePoint(const LanePointProto &proto);

    ElementId lane_id() const;
    double fraction() const;
    void set_fraction(double fraction);

    bool Valid() const;

    std::string DebugString() const;

    bool operator==(const LanePoint &other) const;
    bool operator!=(const LanePoint &other) const;

    void ToProto(LanePointProto *proto) const;

    void FromProto(const LanePointProto &proto);

 private:
    ElementId lane_id_ = mapping::kInvalidElementId;
    double fraction_ = 0.0;
};

}  // namespace mapping
}  // namespace pnc_x
