#ifndef TAP_SDK_ALGORITHM_LDW_LDW_FUNCTION_H_
#define TAP_SDK_ALGORITHM_LDW_LDW_FUNCTION_H_

#include "algorithm/elk/environment_processing.h"
#include "common/global_config.h"
#include "interface/active_safety_vse.h"
#include "interface/lane_marker.h"
#include "ldw_state_machine.h"

namespace active_safety {
namespace ldw {

class LdwFunction {
  public:
    using LdwState = LdwStateMachine::State;

    LdwFunction() = default;
    ~LdwFunction() = default;

    // 执行一帧 LDW 主流程，消费 ELK 已计算好的共享车道环境。
    void Update(const AsVseOut &vse_out, const elk::EnvironmentProcessing &env_proc, const GlobalConfig &config);

    const LdwStateMachine &getLdwStateMachineObj() const { return ldw_state_machine_; }
    const LdwOutput &GetOutput() const { return ldw_output_; }

  private:
    // 将内部状态机结果和车道特征整理成 LDW 输出。
    void FillOutput(const elk::EnvironmentProcessing &env_proc);

    uint8_t rolling_count_ = 0;
    LdwStateMachine ldw_state_machine_;
    LdwOutput ldw_output_;
};

} // namespace ldw
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LDW_LDW_FUNCTION_H_
