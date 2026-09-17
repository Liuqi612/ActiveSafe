#include "relay_on_delay_block.h"

namespace active_safety {
namespace math {

void RelayOnDelayBlock::normalizeThresholds(float& turn_on_point, float& turn_off_point) const {
    if (turn_on_point < turn_off_point) {
        const float temp = turn_on_point;
        turn_on_point = turn_off_point;
        turn_off_point = temp;
    }
}

bool RelayOnDelayBlock::process(float input, float turn_on_point, float turn_off_point, float on_delay_time_s, float unit_time_s,
                                     bool output_when_on, bool output_when_off) {
    normalizeThresholds(turn_on_point, turn_off_point);

    if (input <= turn_off_point) {
        relay_is_on_ = false;
        on_delay_time_s_ = 0.0F;
    } else if (input >= turn_on_point) {
        if (!relay_is_on_) {
            on_delay_time_s_ += unit_time_s;
            if (on_delay_time_s_ >= on_delay_time_s) {
                relay_is_on_ = true;
                on_delay_time_s_ = 0.0F;
            }
        } else {
            on_delay_time_s_ = 0.0F;
        }
    } else {
        on_delay_time_s_ = 0.0F;
    }

    output_ = relay_is_on_ ? output_when_on : output_when_off;
    return output_;
}

void RelayOnDelayBlock::reset(bool initial_output) {
    relay_is_on_ = initial_output;
    output_ = initial_output;
    on_delay_time_s_ = 0.0F;
}

} // namespace math
} // namespace active_safety
