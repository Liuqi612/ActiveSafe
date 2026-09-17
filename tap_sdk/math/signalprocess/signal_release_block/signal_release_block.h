

#ifndef TAP_SDK_MATH_SIGNALPROCESS_SIGNAL_RELEASE_BLOCK_SIGNAL_RELEASE_BLOCK_H_
#define TAP_SDK_MATH_SIGNALPROCESS_SIGNAL_RELEASE_BLOCK_SIGNAL_RELEASE_BLOCK_H_
#include <cstdint>

#include "../signal_process/SignalProcess.h"
namespace active_safety {
namespace math {
class SignalReleaseBlock : public SignalProcess {
 public:
  SignalReleaseBlock() = default;
  ~SignalReleaseBlock() = default;
  /* input:
    current_state：原始输入
    delay_time：需要延迟的时间
    unit_time：模块运行周期(s)
    output:
    信号是否需要释放*/
  bool signalRelease(bool current_state, float delay_time, float unit_time_s);
  //获取信号是否需要释放（是否达到最大计数）
  inline bool getSignalRelease() const { return signal_release_; }

 private:
  bool signal_release_ = false;

};  // OnDelayBlock
}  // namespace math
}  // namespace active_safety
#endif // TAP_SDK_MATH_SIGNALPROCESS_SIGNAL_RELEASE_BLOCK_SIGNAL_RELEASE_BLOCK_H_
