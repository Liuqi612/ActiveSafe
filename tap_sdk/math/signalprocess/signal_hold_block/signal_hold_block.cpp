
#include "signal_hold_block.h"
namespace active_safety {
namespace math {
bool SignalHoldBlock::signalHold(bool current_state, float delay_time,
                                 float unit_time_s) {
  //识别上升沿，开始信号保持
  if (true == SignalProcess::detectRisingEdge(current_state)) {
    SignalProcess::resetTime();
    SignalProcess::increaseTime(unit_time_s);
    state_out_ = true;

    //计时累积，信号维持置位
  } else if (cur_delay_time_ > 0 && cur_delay_time_ < delay_time) {
    SignalProcess::increaseTime(unit_time_s);
    state_out_ = true;

    //达到时间，或不满足条件，透传
  } else {
    SignalProcess::resetTime();
    state_out_ = current_state;
  }
  // 更新last_state_
  last_state_ = current_state;
  //
  return state_out_;
}

}  // namespace math
}  // namespace active_safety