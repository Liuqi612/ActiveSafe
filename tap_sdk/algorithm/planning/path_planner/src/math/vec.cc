

#include "path_planner/src/math/vec.h"

namespace pnc_x {

std::string DebugStringFullPrecision(absl::Span<const Vec2d> vec) {
    const auto to_str = [](std::string *out, const Vec2d &v) {
        return out->append(v.DebugStringFullPrecision());
    };
    return absl::StrJoin(vec, ", ", to_str);
}

}  // namespace pnc_x
