#include "bsd_function.h"
namespace active_safety {
namespace bsd {

BsdFunction::BsdFunction() {
}

BsdFunction::~BsdFunction() = default;

void BsdFunction::Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list) {
    m_bsw_alert_active = {false, false};
    m_bsw_alert_fusId = {-1, -1};
    m_closest_cvw_obs_dist = {-1000.0F, -1000.0F};
    m_cvw_alert_active = {false, false};
    m_cvw_alert_fusId = {-1, -1};

    // 清空上一帧的关键目标逐条明细快照（仅在开启调试记录时进行）
    if (m_bsd_cal.k_bsd_debug_log_enable) {
        for (int side = 0; side < 2; ++side) {
            m_debug.bsw[side] = BsdBswTargetDebug{};
            m_debug.cvw[side] = BsdCvwTargetDebug{};
        }
    }

    for (std::size_t idx = 0; idx < kMaxNormalObject; ++idx) {
        m_obs_data[idx].m_obs = obs_list[idx];
        GetObjClass(m_obs_data[idx]);
        FilterCurviDataAndCheckSide(m_obs_data[idx]);

        int side = static_cast<int>(m_obs_data[idx].m_side);
        bool alertActive = false;
        if ((m_prev_data[side].prev_cvw_active) && (m_obs_data[idx].m_obs->fus_trkID == m_prev_data[side].prev_cvw_alert_obs_id)) {
            alertActive = true;
        }
        m_obs_data[idx].m_is_prev_cvw_active_obj = alertActive;
        alertActive = false;
        if ((m_prev_data[side].prev_bsw_active) && (m_obs_data[idx].m_obs->fus_trkID == m_prev_data[side].prev_bsw_alert_obs_id)) {
            alertActive = true;
        }
        m_obs_data[idx].m_is_prev_bsw_active_obj = alertActive;
        CalcObsPolygon(m_obs_data[idx]);
        CalcValidZone(vse_out.config, m_obs_data[idx], vse_out);
        CalcTTc(vse_out.config, m_obs_data[idx]);
        UpdateCriticalObsInBswZone(vse_out, m_obs_data[idx]);
        UpdateCriticalObsInCvwZone(vse_out, m_obs_data[idx]);
    }
    WarnJudgement();
    StateMachine(config, vse_out);

    // 回灌调试：打印本帧影响 BSD 输出的所有关键条件（可重定向到文件）
    if (m_bsd_cal.k_bsd_debug_log_enable) {
        DumpDebugFrame(vse_out, config);
    }
}

} // namespace bsd
} // namespace active_safety
