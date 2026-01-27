
#include "signal_release_block.h"
namespace active_safety {
namespace math {

bool SignalReleaseBlock::signalRelease(bool current_state, float delay_time,
                                       float unit_time_s) {
  // 限幅处理
  delay_time = SignalProcess::delayTimeLimit(delay_time);
  unit_time_s = SignalProcess::unitTimeLimit(unit_time_s);
  //识别上升沿，开始计数，信号不需要释放
  if (true == SignalProcess::detectRisingEdge(current_state)) {
    SignalProcess::resetTime();
    SignalProcess::increaseTime(unit_time_s);
    signal_release_ = false;

    //当前状态置位，计时累积，未达到阈值，信号不需要释放
  } else if ((current_state == true) &&
             (cur_delay_time_ > 0 && cur_delay_time_ < delay_time)) {
    SignalProcess::increaseTime(unit_time_s);
    signal_release_ = false;

    //当前状态置位，时间达阈值，信号释放，
  } else if ((current_state == true) && (cur_delay_time_ >= delay_time)) {
    SignalProcess::increaseTime(unit_time_s);
    signal_release_ = true;

    // 当前状态不置位，计数清零，信号不需要释放
  } else if (current_state == false) {
    SignalProcess::resetTime();
    signal_release_ = false;

    //默认信号不需要释放
  } else {
    signal_release_ = false;
  }
  // 更新last_state_
  last_state_ = current_state;
  //
  return signal_release_;
}  // namespace common

}  // namespace math
}  // namespace active_safety
