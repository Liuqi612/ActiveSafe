
#pragma once

namespace pnc_x {
namespace planning {

struct OverlapInfo {
    double time = 0.0;

    int obj_idx = 0;

    int av_start_idx = 0;

    int av_end_idx = 0;
};

}  // namespace planning
}  // namespace pnc_x
