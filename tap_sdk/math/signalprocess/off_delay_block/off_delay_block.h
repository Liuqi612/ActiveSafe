

#pragma once
#include <cstdint>

#include "../signal_process/SignalProcess.h"
namespace active_safety {
namespace math {
class OffDelayBlock : public SignalProcess {
 public:
  OffDelayBlock() = default;
  ~OffDelayBlock() = default;
  /* input:
  current_state：原始输入
  delay_time：需要延迟的时间
  unit_time：模块运行周期(s)
  output:
  delay后输出状态*/
  bool offDelay(bool current_state, float delay_time, float unit_time_s);
  //获取输出状态
  inline bool getStateOut() const { return state_out_; }

 private:
  bool state_out_ = false;

};  // OffDelayBlock

}  // namespace math
}  // namespace active_safety