
#pragma once

#include <cstdint>
#include <limits>
#include <utility>

#include "container/strong_int.h"
#include <absl/container/flat_hash_map.h>

namespace pnc_x {
namespace mapping {

DEFINE_STRONG_INT_TYPE(SegmentId, int64_t);

using ElementId = uint64_t;
using SectionId = uint64_t;

const ElementId kInvalidElementId = 0;
const SectionId kInvalidSectionId = 0;

using SectionConnection = std::pair<SectionId, SectionId>;
using SectionConnectionDistance =
    absl::flat_hash_map<SectionConnection, double>;
namespace v2 {
struct Segment {
    ElementId element_id;

    SegmentId segment_id;
};
}  // namespace v2

}  // namespace mapping
}  // namespace pnc_x
