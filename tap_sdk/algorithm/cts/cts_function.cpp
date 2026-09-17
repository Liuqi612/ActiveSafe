#include "cts_function.h"

namespace active_safety {
namespace cts {
CtsFunction::CtsFunction() {
}
CtsFunction::~CtsFunction() = default;

void CtsFunction::Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list) {
    SetThresData(vse_out);
    CheckCommonInhibit(vse_out);
    CheckDrvBehavior(vse_out);
    // Reset max levels for this cycle
    for (int i = 0; i < CTS_MAX_SIDE; ++i) {
        m_fcts_info[i].max_level = 0;
        m_fcts_info[i].highest_critical_obs_idx = -1;
        m_rcts_info[i].max_level = 0;
        m_rcts_info[i].highest_critical_obs_idx = -1;
        // 清空上一帧的关键目标逐级明细（仅在开启调试记录时进行）
        if (m_cts_cal.k_cts_debug_log_enable) {
            m_debug.target[0][i] = CtsTargetDebug{};
            m_debug.target[1][i] = CtsTargetDebug{};
        }
    }
    if (m_cts_cal.k_cts_debug_log_enable) {
        for (auto &direction_targets : m_debug.invalid_target) {
            for (auto &target : direction_targets) {
                target = CtsInvalidTargetDebug{};
            }
        }
    }

    for (std::size_t idx = 0; idx < kMaxNormalObject; ++idx) {
        m_obs_data[idx].m_obs = obs_list[idx];
        CheckApproachSide(m_obs_data[idx]);
        CalculateTargetCornersPoint(m_obs_data[idx]);
        CalculateRelativeVelocity(vse_out, m_obs_data[idx]);
        CheckMotion(m_obs_data[idx]);
        CheckCTA(vse_out, m_fcts_thres, m_obs_data[idx], m_obs_data[idx].m_attr[0], m_fcts_info, CtsDirection::FRONT);
        CheckCTA(vse_out, m_rcts_thres, m_obs_data[idx], m_obs_data[idx].m_attr[1], m_rcts_info, CtsDirection::REAR);
    }

    ProcessThreatLevel(m_fcts_info, CtsDirection::FRONT);
    ProcessThreatLevel(m_rcts_info, CtsDirection::REAR);

    CtsDecision(vse_out, config);

    FillOutput(vse_out, config, m_fcts_info, m_front, CtsDirection::FRONT);
    FillOutput(vse_out, config, m_rcts_info, m_rear, CtsDirection::REAR);

    // 回灌调试：打印本帧影响 CTS 输出的所有关键条件（可重定向到文件）
    if (m_cts_cal.k_cts_debug_log_enable) {
        DumpDebugFrame(vse_out, config);
    }
}

} // namespace cts
} // namespace active_safety
