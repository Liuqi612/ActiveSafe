#ifndef TAP_SDK_MATH_SIGNALPROCESS_RELAY_BLOCK_RELAY_OFF_DELAY_BLOCK_H_
#define TAP_SDK_MATH_SIGNALPROCESS_RELAY_BLOCK_RELAY_OFF_DELAY_BLOCK_H_

namespace active_safety {
namespace math {
/**
 * @brief 带释放延时的滞回比较器
 *
 * 逻辑：
 * - 输入大于等于 turn_on_point 时，立即输出 output_when_on
 * - 输入持续小于等于 turn_off_point 达到 off_delay_time_s 后，输出 output_when_off
 * - 输入位于 turn_off_point 和 turn_on_point 之间时，保持上一状态
 */
class RelayOffDelayBlock {
  public:
    RelayOffDelayBlock()  = default;
    ~RelayOffDelayBlock() = default;

    bool process(float input, float turn_on_point, float turn_off_point, float off_delay_time_s, float unit_time_s,
                 bool output_when_on = false, bool output_when_off = true);

    inline bool getOutput() const { return output_; }
    void reset(bool initial_output = false);

  private:
    void normalizeThresholds(float& turn_on_point, float& turn_off_point) const;

  private:
    bool relay_is_on_           = false;
    bool output_                = false;
    float off_delay_time_acc_s_ = 0.0F;
}; // RelayOffDelayBlock
} // namespace math
} // namespace active_safety
#endif // TAP_SDK_MATH_SIGNALPROCESS_RELAY_BLOCK_RELAY_OFF_DELAY_BLOCK_H_
