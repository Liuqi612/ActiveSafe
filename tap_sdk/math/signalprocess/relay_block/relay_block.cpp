
#include "relay_block.h"

namespace active_safety {
namespace math {

bool RelayBlock::process(float input, float turn_on_point, float turn_off_point, bool output_when_on, bool output_when_off) {
    // 确保开启点 >= 关闭点（否则交换）
    if (turn_on_point < turn_off_point) {
        float temp     = turn_on_point;
        turn_on_point  = turn_off_point;
        turn_off_point = temp;
    }

    if (input >= turn_on_point) {
        output_ = output_when_on;
    } else if (input <= turn_off_point) {
        output_ = output_when_off;
    }

    return output_;
}

void RelayBlock::reset(bool initial_output) {
    output_ = initial_output;
}

} // namespace math
} // namespace active_safety
