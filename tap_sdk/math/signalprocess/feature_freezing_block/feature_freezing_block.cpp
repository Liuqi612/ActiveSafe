
#include "feature_freezing_block.h"
namespace active_safety {
namespace math {
//

bool FeatureFreezingBlock::featureFreezing(bool current_state, float delay_time,
                                           float unit_time_s) {
  // 限幅处理
  delay_time = SignalProcess::delayTimeLimit(delay_time);
  unit_time_s = SignalProcess::unitTimeLimit(unit_time_s);
  //识别下降沿，开始计时，输出抑制触发
  if (true == SignalProcess::detectFallingEdge(current_state)) {
    SignalProcess::resetTime();
    SignalProcess::increaseTime(unit_time_s);
    is_featrue_freezing_ = true;

    //计时累积，持续输出抑制
  } else if (cur_delay_time_ > 0 && cur_delay_time_ < delay_time) {
    SignalProcess::increaseTime(unit_time_s);
    is_featrue_freezing_ = true;
    //计时清零，消除抑制

  } else {
    SignalProcess::resetTime();
    is_featrue_freezing_ = false;
  }
  // 更新last_state_
  last_state_ = current_state;
  // 返回功能是否正在冷却标志位
  return is_featrue_freezing_;
}

}  // namespace math
}  // namespace active_safety