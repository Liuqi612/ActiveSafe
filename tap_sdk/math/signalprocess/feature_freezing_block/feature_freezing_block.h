

#ifndef TAP_SDK_MATH_SIGNALPROCESS_FEATURE_FREEZING_BLOCK_FEATURE_FREEZING_BLOCK_H_
#define TAP_SDK_MATH_SIGNALPROCESS_FEATURE_FREEZING_BLOCK_FEATURE_FREEZING_BLOCK_H_
#include <cstdint>

#include "../signal_process/SignalProcess.h"
namespace active_safety {
namespace math {
class FeatureFreezingBlock : public SignalProcess {
 public:
  FeatureFreezingBlock() = default;
  ~FeatureFreezingBlock() = default;
  /* input:
    current_state：原始输入
    delay_time：需要延迟的时间
    unit_time：模块运行周期(s)
    output：
    功能是否在冷却中*/
  bool featureFreezing(bool current_state, float delay_time, float unit_time_s);
  //获取功能是否在冷却中
  inline bool getfeatureFreezing() const { return is_featrue_freezing_; }

 private:
  bool is_featrue_freezing_ = false;

};  // SignalHoldBlock
}  // namespace math
}  // namespace active_safety
#endif // TAP_SDK_MATH_SIGNALPROCESS_FEATURE_FREEZING_BLOCK_FEATURE_FREEZING_BLOCK_H_
