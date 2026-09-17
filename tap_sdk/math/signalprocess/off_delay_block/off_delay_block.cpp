
#include "off_delay_block.h"
namespace active_safety {
namespace math {
bool OffDelayBlock::offDelay(bool current_state, float delay_time, float unit_time_s) {
    // 限幅处理
    delay_time = SignalProcess::delayTimeLimit(delay_time);
    unit_time_s = SignalProcess::unitTimeLimit(unit_time_s);
    //识别下降沿
    if (true == SignalProcess::detectFallingEdge(current_state)) {
        SignalProcess::resetTime();
        SignalProcess::increaseTime(unit_time_s);
        state_out_ = true;
        //持续delay
    } else if (cur_delay_time_ > 0.0F && cur_delay_time_ < delay_time) {
        SignalProcess::increaseTime(unit_time_s);
        state_out_ = true;
        //结束delay
    } else if (cur_delay_time_ >= delay_time) {
        //透传当前状态
        SignalProcess::resetTime();
        state_out_ = current_state;
    } else {
        SignalProcess::resetTime();
        state_out_ = current_state;
    }
    // 更新last_state_
    last_state_ = current_state;
    //
    return state_out_;
}

 void  OffDelayBlock::Reset(){
       //延迟计时器复位
        SignalProcess::resetTime();
        state_out_ = false;
 }

} // namespace math
} // namespace active_safety
