#ifndef TAP_SDK_ALGORITHM_LKA_LKA_FUNCTION_H_
#define TAP_SDK_ALGORITHM_LKA_LKA_FUNCTION_H_

#include "algorithm/elk/environment_processing.h"
#include "common/global_config.h"
#include "interface/active_safety_vse.h"
#include "interface/lane_marker.h"
#include "lka_handoff_warning.h"
#include "lka_state_machine.h"

namespace active_safety {
namespace lka {

using EnvironmentProcessing = active_safety::elk::EnvironmentProcessing;

// LKA 顶层功能封装，接口形式与 ELK 保持一致。
class LkaFunction {
  public:
    using LkaState = LkaStateMachine::State;

    LkaFunction() = default;
    ~LkaFunction() = default;

    // 执行一帧 LKA 主流程，消费 ELK 已计算好的环境特征。
    void Update(const AsVseOut &vse_out,
                const elk::EnvironmentProcessing &env_proc,
                const GlobalConfig &config,
                uint8_t elk_mode,
                bool mcu_lfp_actv_cdt,
                uint64_t control_time_ns);

    const LkaStateMachine &getLkaStateMachineObj() const { return lka_state_machine_; }
    const LkaOutput &GetOutput() const { return lka_output_; }
    const HandoffWarningOutput &GetHandoffWarningOutput() const { return handoff_warning_.GetOutput(); }

  private:
    // 将内部状态机结果整理为 wrapper 可消费的紧凑输出。
    void FillOutput(const elk::EnvironmentProcessing &env_proc);

    uint8_t rolling_count_ = 0;
    LkaStateMachine lka_state_machine_;
    LkaOutput lka_output_;
    LkaElkHandoffWarning handoff_warning_;
};

} // namespace lka
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LKA_LKA_FUNCTION_H_
