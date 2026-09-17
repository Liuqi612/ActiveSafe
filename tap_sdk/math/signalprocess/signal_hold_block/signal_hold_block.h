

#ifndef TAP_SDK_MATH_SIGNALPROCESS_SIGNAL_HOLD_BLOCK_SIGNAL_HOLD_BLOCK_H_
#define TAP_SDK_MATH_SIGNALPROCESS_SIGNAL_HOLD_BLOCK_SIGNAL_HOLD_BLOCK_H_
#include <cstdint>

#include "../signal_process/SignalProcess.h"
namespace active_safety {
namespace math {
class SignalHoldBlock : public SignalProcess {
 public:
  SignalHoldBlock() = default;
  ~SignalHoldBlock() = default;
  /* input:
    current_state：原始输入
    delay_time：需要延迟的时间
    unit_time：模块运行周期(s)
    output:
    信号保持后输出状态*/
  bool signalHold(bool current_state, float delay_time, float unit_time_s);
  //获取输出状态
  inline bool getStateOut() const { return state_out_; }
  //
 private:
  bool state_out_ = false;

};  // SignalHoldBlock
}  // namespace math
}  // namespace active_safety
#endif // TAP_SDK_MATH_SIGNALPROCESS_SIGNAL_HOLD_BLOCK_SIGNAL_HOLD_BLOCK_H_
