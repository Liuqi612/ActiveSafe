#include "dow_function.h"

namespace active_safety {
namespace dow {

DowFunction::DowFunction(const VehicleConfig &vehcfg) {
    InitZone(vehcfg);
}

DowFunction::~DowFunction() = default;

void DowFunction::Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list) {

    // 回灌调试：每帧先清空目标级快照，随后在各处理阶段就地填充
    const bool dbg_on = m_dow_cal.k_dow_debug_log_enable;
    if (dbg_on) {
        m_debug.obj.fill(DowObjDebug{});
    }

    for (std::size_t idx = 0; idx < kMaxNormalObject; ++idx) {
        m_obs_data[idx].m_obs = obs_list[idx];
        if (m_obs_data[idx].m_obs->fus_trkID <= 0) {
            ResetObjectPersistent(m_obs_data[idx]);
            continue;
        }
        if (dbg_on) {
            m_debug.obj[idx].used      = true;
            m_debug.obj[idx].fus_trkID = m_obs_data[idx].m_obs->fus_trkID;
        }

        if (!IsObjectValid(m_obs_data[idx])) {
            ResetObjectPersistent(m_obs_data[idx]);
            continue;
        }

        if (!IsObjectRelevant(vse_out, m_obs_data[idx])) {
            ResetObjectPersistent(m_obs_data[idx]);
            continue;
        }

        UpdateCriticalObs(vse_out, m_obs_data[idx]);
    }
    FindThreatWarn();
    StateMachine(config, vse_out);

    // 回灌调试：作为本帧最后一步，打印结构化快照
    if (m_dow_cal.k_dow_debug_log_enable) {
        DumpDebugFrame(vse_out, config);
    }
}

} // namespace dow
} // namespace active_safety
