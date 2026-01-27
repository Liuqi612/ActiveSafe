
#include "on_delay_block.h"
namespace active_safety {
namespace math {
bool OnDelayBlock::onDelay(bool current_state, float delay_time,
                           float unit_time_s) {
  // 限幅处理
  delay_time = SignalProcess::delayTimeLimit(delay_time);
  unit_time_s = SignalProcess::unitTimeLimit(unit_time_s);
  //识别上升沿，状态置false
  if (true == SignalProcess::detectRisingEdge(current_state)) {
    SignalProcess::resetTime();
    SignalProcess::increaseTime(unit_time_s);
    state_out_ = false;
    //持续置位，计时累积，状态置false
  } else if (current_state == true && cur_delay_time_ < delay_time) {
    SignalProcess::increaseTime(unit_time_s);
    state_out_ = false;
    //持续置位，计时满足，透传状态
  } else if (current_state == true && cur_delay_time_ >= delay_time) {
    state_out_ = current_state;
  } else {
    //状态及计时没有满足，计时清零，状态置false
    SignalProcess::resetTime();
    state_out_ = false;
  }
  // 更新last_state_
  last_state_ = current_state;
  //
  return state_out_;
}

}  // namespace math
}  // namespace active_safety
