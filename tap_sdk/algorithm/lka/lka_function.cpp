#include "lka_function.h"

namespace active_safety {
namespace lka {

// 串联 LKA 各处理阶段，完成单周期更新。
void LkaFunction::Update(const AsVseOut &vse_out,
                         const elk::EnvironmentProcessing &env_proc,
                         const GlobalConfig &config,
                         uint8_t elk_mode,
                         bool mcu_lfp_actv_cdt,
                         uint64_t control_time_ns) {
    // 处理链路：
    // 复用 ELK 已计算的环境特征 -> 状态机 -> 对外输出。
    lka_state_machine_.Update(vse_out, env_proc.getLaneBoundaryInfo(), env_proc.getLaneCenterInfo(), config);
    FillOutput(env_proc);
    const uint64_t handoff_time_ns = control_time_ns != 0U ? control_time_ns : vse_out.veh_time_stamp;
    handoff_warning_.Update(static_cast<uint8_t>(lka_state_machine_.getCurrentState()),
                            elk_mode,
                            vse_out.torsion_bar_trq,
                            vse_out.hod_hands_monitor,
                            config.k_LKA_HODHandsOffConfirmTime,
                            config.k_LKA_HODHandsOnConfirmTime,
                            mcu_lfp_actv_cdt,
                            config.k_LKA_HandoffWarningEnable,
                            config.k_use_shadowmode,
                            handoff_time_ns);
}

// 汇总本周期的状态机结果和关键车道特征。
void LkaFunction::FillOutput(const elk::EnvironmentProcessing &env_proc) {
    rolling_count_ = static_cast<uint8_t>(rolling_count_ + 1U);
    const auto lane_center = env_proc.getLaneCenterInfo();
    const auto lane_boundary = env_proc.getLaneBoundaryInfo();

    // 输出紧凑状态结果，供 wrapper 集成和调试使用。
    lka_output_.rolling_count = rolling_count_;
    lka_output_.state = static_cast<uint8_t>(lka_state_machine_.getCurrentState());
    lka_output_.available = lka_state_machine_.isAvailable();
    lka_output_.left_intervention = lka_state_machine_.isLeftTriggerActive();
    lka_output_.right_intervention = lka_state_machine_.isRightTriggerActive();
    lka_output_.lane_center_offset = lane_center.c0;
    lka_output_.lane_center_heading = lane_center.heading;
    lka_output_.lane_boundary_info.curLftDisToBdry = lane_boundary.curLftDisToBdry;
    lka_output_.lane_boundary_info.curRgtDisToBdry = lane_boundary.curRgtDisToBdry;
    lka_output_.lane_boundary_info.lftBdryHdgDeg = lane_boundary.lftBdryHdgDeg;
    lka_output_.lane_boundary_info.rgtBdryHdgDeg = lane_boundary.rgtBdryHdgDeg;
    lka_output_.lane_boundary_info.lftBdryLatRt = lane_boundary.lftBdryLatRt;
    lka_output_.lane_boundary_info.rgtBdryLatRt = lane_boundary.rgtBdryLatRt;
    lka_output_.lane_boundary_info.lftBdryCurv = lane_boundary.lftBdryCurv;
    lka_output_.lane_boundary_info.rgtBdryCurv = lane_boundary.rgtBdryCurv;
    lka_output_.lane_boundary_info.lftBdryCurvRt = lane_boundary.lftBdryCurvRt;
    lka_output_.lane_boundary_info.rgtBdryCurvRt = lane_boundary.rgtBdryCurvRt;
    lka_output_.lane_boundary_info.lftBdryTtlc = lane_boundary.lftBdryTtlc;
    lka_output_.lane_boundary_info.rgtBdryTtlc = lane_boundary.rgtBdryTtlc;
    lka_output_.lane_boundary_info.laneWidth = lane_boundary.laneWidth;
    lka_output_.lane_boundary_info.frtAxlCurv = lane_boundary.frtAxlCurv;
    lka_output_.lane_boundary_info.lftBdryVld = lane_boundary.lftBdryVld;
    lka_output_.lane_boundary_info.rgtBdryVld = lane_boundary.rgtBdryVld;
    lka_output_.suppress_mask = lka_state_machine_.getSuppressMask();
    lka_output_.enable_mask = lka_state_machine_.getEnableMask();
}

} // namespace lka
} // namespace active_safety
