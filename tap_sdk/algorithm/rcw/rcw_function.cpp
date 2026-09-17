#include "rcw_function.h"

#include <algorithm>
#include <cmath>

namespace active_safety {
namespace rcw {

RcwFunction::RcwFunction() {
}

RcwFunction::~RcwFunction() = default;

void RcwFunction::Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list) {
    // 清空上一帧的关键目标/状态机调试快照
    if (m_rcw_cal.k_rcw_debug_log_enable) {
        m_debug.target = RcwTargetDebug{};
        m_debug.state = RcwStateDebug{};
    }

    // select inpath closest target
    m_inpath_index.clear();
    for (std::size_t idx = 0; idx < kMaxNormalObject; ++idx) {
        m_obs_data[idx].obs = obs_list[idx];
        IsRcwValidObj(vse_out, m_obs_data[idx]);

        if (m_obs_data[idx].is_valid) {
            ObjInPathEvaluator(vse_out, m_obs_data[idx]);
        } else {
            ResetPersistant(m_obs_data[idx]);
        }

        if (m_obs_data[idx].is_inpath) {
            m_inpath_index.push_back(idx);
        }
    }

    // vehicle类型直接参与到距离排序 非vehicle进入危险阈值ttc 2.0 才能参与到距离排序
    m_min_dist_idx = -1;
    m_min_dist = k_rcw_min_dist_init;
    if (!m_inpath_index.empty()) {
        for (std::size_t i = 0; i < m_inpath_index.size(); ++i) {
            if (m_min_dist <= m_obs_data[m_inpath_index[i]].obs->long_posn &&
                (m_obs_data[m_inpath_index[i]].ttc < m_rcw_cal.k_rcw_valid_tar_ttc_thd_min || m_obs_data[m_inpath_index[i]].obs->f_is_vehicle)) {
                m_min_dist_idx = m_inpath_index[i];
                m_min_dist = m_obs_data[m_inpath_index[i]].obs->long_posn;
            }
        }
    }

    if (m_min_dist_idx != -1) {
        if (m_obs_data[m_min_dist_idx].obs->fus_trkID == m_rcw_tar.obs->fus_trkID) {
            m_rcw_tar.obs = m_obs_data[m_min_dist_idx].obs;
            m_rcw_tar.ttc = m_obs_data[m_min_dist_idx].ttc;
            m_rcw_tar.is_inpath = m_obs_data[m_min_dist_idx].is_inpath;
            m_rcw_tar.is_valid = m_obs_data[m_min_dist_idx].is_valid;
        } else {
            m_rcw_tar = m_obs_data[m_min_dist_idx];
        }
        RcwThreatEvaluator(vse_out, config);
    } else {
        ResetPersistant(m_rcw_tar);
    }

    StateMachine(config, vse_out);

    // 记录目标选择概览并打印本帧调试快照(须在状态机之后，作为每帧更新的最后一步)
    if (m_rcw_cal.k_rcw_debug_log_enable) {
        m_debug.min_dist_idx = m_min_dist_idx;
        m_debug.min_dist = m_min_dist;
        m_debug.inpath_count = static_cast<int>(m_inpath_index.size());
        DumpDebugFrame(vse_out, config);
    }
}

} // namespace rcw
} // namespace active_safety
