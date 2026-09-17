

#ifndef TAP_SDK_MATH_SIGNALPROCESS_ON_DELAY_BLOCK_ON_DELAY_BLOCK_H_
#define TAP_SDK_MATH_SIGNALPROCESS_ON_DELAY_BLOCK_ON_DELAY_BLOCK_H_
#include "../signal_process/SignalProcess.h"

#include <cstdint>
namespace active_safety {
namespace math {
class OnDelayBlock : public SignalProcess {
  public:
    OnDelayBlock() = default;
    ~OnDelayBlock() = default;
    /* input:
      current_state：原始输入
      delay_time：需要延迟的时间
      unit_time：模块运行周期(s)
      output:
      delay后输出状态*/
    bool onDelay(bool current_state, float delay_time, float unit_time_s);
    //获取输出状态
    inline bool getStateOut() const { return state_out_; }

  private:
    bool state_out_ = false;

}; // OnDelayBlock
} // namespace math
} // namespace active_safety
#endif // TAP_SDK_MATH_SIGNALPROCESS_ON_DELAY_BLOCK_ON_DELAY_BLOCK_H_
