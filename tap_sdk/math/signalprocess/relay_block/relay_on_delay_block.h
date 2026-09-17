#ifndef TAP_SDK_MATH_SIGNALPROCESS_RELAY_BLOCK_RELAY_ON_DELAY_BLOCK_H_
#define TAP_SDK_MATH_SIGNALPROCESS_RELAY_BLOCK_RELAY_ON_DELAY_BLOCK_H_

namespace active_safety {
namespace math {
/**
 * @brief 带吸合延时的滞回比较器
 *
 * 逻辑：
 * - 输入持续大于等于 turn_on_point 达到 on_delay_time_s 后，输出 output_when_on
 * - 输入小于等于 turn_off_point 时，立即输出 output_when_off
 * - 输入位于 turn_off_point 和 turn_on_point 之间时，保持上一状态
 */
class RelayOnDelayBlock {
  public:
    RelayOnDelayBlock()  = default;
    ~RelayOnDelayBlock() = default;

    bool process(float input, float turn_on_point, float turn_off_point, float on_delay_time_s, float unit_time_s,
                      bool output_when_on = false, bool output_when_off = true);

    inline bool getOutput() const { return output_; }
    void reset(bool initial_output = false);

  private:
    void normalizeThresholds(float& turn_on_point, float& turn_off_point) const;

  private:
    bool relay_is_on_       = false;
    bool output_            = false;
    float on_delay_time_s_  = 0.0F;
}; // RelayOnDelayBlock
} // namespace math
} // namespace active_safety
#endif // TAP_SDK_MATH_SIGNALPROCESS_RELAY_BLOCK_RELAY_ON_DELAY_BLOCK_H_
