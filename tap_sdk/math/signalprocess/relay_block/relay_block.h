
#ifndef TAP_SDK_MATH_SIGNALPROCESS_RELAY_BLOCK_RELAY_BLOCK_H_
#define TAP_SDK_MATH_SIGNALPROCESS_RELAY_BLOCK_RELAY_BLOCK_H_
#include <cstdint>

namespace active_safety {
namespace math {
/**
 * @brief Relay block - 滞回比较器
 *
 * 通过将输入与指定的阈值进行比较，输出指定的'on'或'off'值。
 * 中继的 on/off 状态不受上限和下限之间输入的影响（滞回特性）。
 *
 * 逻辑：
 * - 如果输入 >= 开启点 (turn_on_point)，输出 = 打开时的输出 (output_when_on)
 * - 如果输入 <= 关闭点 (turn_off_point)，输出 = 关闭时的输出 (output_when_off)
 * - 如果输入在关闭点和开启点之间，输出保持上一次的值（滞回特性）
 */
class RelayBlock {
  public:
    RelayBlock()  = default;
    ~RelayBlock() = default;

    /**
     * @brief 处理输入信号
     * @param input 输入值
     * @param turn_on_point 开启点（当输入 >= 此值时，输出为 output_when_on）
     * @param turn_off_point 关闭点（当输入 <= 此值时，输出为 output_when_off）
     * @param output_when_on 打开时的输出值（默认false）
     * @param output_when_off 关闭时的输出值（默认true）
     * @return 输出值（bool）
     */
    bool process(float input, float turn_on_point, float turn_off_point, bool output_when_on = false, bool output_when_off = true);

    // 获取当前输出状态
    inline bool getOutput() const { return output_; }

    // 重置状态（将输出重置为初始值）
    void reset(bool initial_output = false);

  private:
    bool output_ = false; // 当前输出值

}; // RelayBlock
} // namespace math
} // namespace active_safety
#endif // TAP_SDK_MATH_SIGNALPROCESS_RELAY_BLOCK_RELAY_BLOCK_H_
