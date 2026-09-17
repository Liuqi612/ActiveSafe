#include "ldw_function.h"

namespace active_safety {
namespace ldw {

// 串联 LDW 的环境处理、状态机和输出生成。
void LdwFunction::Update(const AsVseOut &vse_out, const elk::EnvironmentProcessing &env_proc, const GlobalConfig &config) {
    ldw_state_machine_.Update(vse_out, env_proc.getLaneBoundaryInfo(), env_proc.getLaneCenterInfo(), config);
    FillOutput(env_proc);
}

// 汇总当前告警状态和复用的车道线结果。
void LdwFunction::FillOutput(const elk::EnvironmentProcessing &env_proc) {
    rolling_count_ = static_cast<uint8_t>(rolling_count_ + 1U);

    ldw_output_.rolling_count = rolling_count_;
    ldw_output_.state = static_cast<uint8_t>(ldw_state_machine_.getCurrentState());
    ldw_output_.available = ldw_state_machine_.isAvailable();
    ldw_output_.left_warning = ldw_state_machine_.isLeftWarningActive();
    ldw_output_.right_warning = ldw_state_machine_.isRightWarningActive();
    ldw_output_.left_departure_detected = ldw_state_machine_.isLeftDepartureDetected();
    ldw_output_.right_departure_detected = ldw_state_machine_.isRightDepartureDetected();
    ldw_output_.lane_center_offset = env_proc.getLaneCenterInfo().c0;
    ldw_output_.lane_center_heading = env_proc.getLaneCenterInfo().heading;
    ldw_output_.suppress_mask = ldw_state_machine_.getSuppressMask();
    ldw_output_.enable_mask = ldw_state_machine_.getEnableMask();
}

} // namespace ldw
} // namespace active_safety
