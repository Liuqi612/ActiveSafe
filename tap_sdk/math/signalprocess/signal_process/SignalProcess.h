

#ifndef TAP_SDK_MATH_SIGNALPROCESS_SIGNAL_PROCESS_SIGNALPROCESS_H_
#define TAP_SDK_MATH_SIGNALPROCESS_SIGNAL_PROCESS_SIGNALPROCESS_H_
#include <algorithm>
#include <cstdint>

namespace active_safety {
namespace math {
class SignalProcess {
  //
 private:
  //
 public:
  SignalProcess() = default;
  ~SignalProcess() = default;

  //获取当前计数
  inline uint32_t getCurCount() const { return count_; }
  //获取当前延迟时间
  inline float getCurDelayTime() const { return cur_delay_time_; }
  //获取上升沿
  inline bool getRisingEdge() const { return rising_edge_; }
  //获取下降沿
  inline bool getFallingEdge() const { return falling_edge_; }

 protected:
  bool detectRisingEdge(bool current_state);
  bool detectFallingEdge(bool current_state);
  void increaseTime(float unit_time);
  void resetTime();
  //
  float delayTimeLimit(float delay_time);
  float unitTimeLimit(float unit_time);
  //
 protected:
  bool rising_edge_ = false;
  bool falling_edge_ = false;
  uint32_t count_ = 0U;
  bool last_state_ = false;
  float cur_delay_time_ = 0.0F;

};  // signalProcess
}  // namespace math
}  // namespace active_safety
#endif // TAP_SDK_MATH_SIGNALPROCESS_SIGNAL_PROCESS_SIGNALPROCESS_H_
