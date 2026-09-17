
#pragma once

#include <string>
#include <utility>

#include "math/geometry/aabox2d.h"
#include "math/geometry/segment2d.h"

namespace pnc_x {

class AABoxInfo {
 public:
    explicit AABoxInfo(const Segment2d &seg);
    AABoxInfo(const Segment2d &seg, int64_t index);

    AABox2d ComputeAABox() const;

    double DistanceSquareTo(const Vec2d &point) const;

    int64_t index() const;

    const Segment2d &segment() const;

 private:
    Segment2d segment_;

    int64_t index_ = -1;
};
static_assert(sizeof(AABoxInfo) == 80);

inline AABoxInfo::AABoxInfo(const Segment2d &seg) : segment_(seg) {
    XCHECK((segment_.start() != segment_.end()));
}

inline AABoxInfo::AABoxInfo(const Segment2d &seg, int64_t index)
    : segment_(seg), index_(index) {
    XCHECK((segment_.start() != segment_.end()));
}

inline AABox2d AABoxInfo::ComputeAABox() const {
    return AABox2d(segment_.start(), segment_.end());
}

inline double AABoxInfo::DistanceSquareTo(const Vec2d &point) const {
    return segment_.DistanceSquareTo(point);
}

inline int64_t AABoxInfo::index() const { return index_; }

inline const Segment2d &AABoxInfo::segment() const { return segment_; }

}  // namespace pnc_x
