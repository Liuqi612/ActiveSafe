
#pragma once

#include <string>

#include "math/vec.h"
#include <absl/strings/str_cat.h>

namespace pnc_x {
namespace planning {

struct GeometryState {
    Vec2d xy;
    double h = 0.0;
    double k = 0.0;
    double ref_k = 0.0;

    double accumulated_s = 0.0;
    double l = 0.0;
    std::string DebugString() const {
        return absl::StrCat("xy: ", xy.DebugString(), " h: ", h, " k: ", k,
                            " accumulated_s:", accumulated_s, " l: ", l,
                            " dk:", dk, " ddk: ", ddk);
    }
    double dk = 0.0;
    double ddk = 0.0;
};

}  // namespace planning
}  // namespace pnc_x
