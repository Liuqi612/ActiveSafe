#ifndef TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_SINGLE_THREAT_TARGET_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_SINGLE_THREAT_TARGET_H_
#include "algorithm/longsafe/longsafe_cals.h"
#include "behavior_evaluator.h"
#include "collision_evaluator.h"
#include "longsafe_obs.h"
#include "safe_margin.h"

#include <array>
#include <vector>

namespace active_safety {
namespace longsafe {

// 单个预筛选候选目标的筛选过程调试信息。
// 汇总该目标 current/pred inpath 判定及各子判据，便于排查目标为何未被选中。
// 后续将映射到 capnp ActiveSafetyDebug 输出至 rsclbag。
struct TselObjDebug {
    bool valid = false; // 槽位是否被占用(目标存在)。按 fus_trkID 锁定槽位，目标丢失则置 false
    int32_t fus_trkID = 0;
    int32_t vis_trkID = 0;
    int32_t object_class = 0;
    int index = -1; // obs_data_ 中的索引

    float long_posn = 0.0F;
    float lat_posn = 0.0F;
    float long_vel = 0.0F;
    float lat_vel = 0.0F;
    float long_accel = 0.0F;
    float lat_accel = 0.0F;
    float heading = 0.0F;
    float speed = 0.0F;

    // 运动行为
    bool stationary = false;
    bool oncoming = false;
    bool curve_motion = false;
    bool cutin = false;
    float cutin_prob = 0.0F;

    // inpath 相关偏置
    float offs_lat_inpath_current = 0.0F;
    float offs_lgt_inpath_pred_edge = 0.0F;
    float offs_lat_inpath_pred_edge = 0.0F;

    // 预测有效性及其子判据
    bool predict_valid = false;
    bool predict_valid_spd_ok = false;
    bool predict_valid_pred_distance = false;
    bool predict_valid_ttr_valid = false;
    bool predict_valid_pred_type_valid = false;
    float ttr = 0.0F;
    float ttp = 0.0F;     // 脱离时刻(s)，目标离开 inpath 的时间
    int ttp_index = -1;   // 脱离点预测周期索引
    float ttr_lat_overlap_rate = 0.0F; // 第一轮TTR时刻的横向重叠率

    // inpath 判定结果
    bool inpath_current = false;
    bool inpath_predict = false;
    int pred_inpath_fail_reason = 0; // PredInpathFailReason
    bool inpath_res = false;

    // pred inpath 失败时各检查的中间量 (与 pred_inpath_fail_reason 对应)
    float pi_rel_lgt = 0.0F;
    float pi_front_limit = 0.0F;
    float pi_rear_limit = 0.0F;
    float pi_safe_lat = 0.0F;
    float pi_half_host_width = 0.0F;
    float pi_host_rel_obs_lgt = 0.0F;
    float pi_obs_lgt_safe_space = 0.0F;
    float pi_host_rel_obs_lat = 0.0F;
    float pi_obs_lat_safe_space = 0.0F;

    bool is_inpath = false;   // 是否进入 inpath_index
    bool is_selected = false; // 是否被选为最终 aeb_target

    // 清空槽位(目标丢失)，仅复位为无效，保留槽位本身以维持 index 稳定
    void Clear() { *this = TselObjDebug(); }
};

// 整帧目标筛选调试信息。
struct TselDebugInfo {
    // 自车状态快照
    float ego_spd = 0.0F;
    float ego_accel = 0.0F;
    float ego_yawrate = 0.0F;
    float ego_curvature = 0.0F;
    bool aeb_active = false;

    // 各阶段目标数量统计
    int presel_num = 0;            // 预筛选候选数 (sort_index)
    int inpath_num = 0;            // inpath 目标数
    int cur_inpath_num = 0;        // current inpath 目标数
    int pred_inpath_num = 0;       // pred inpath 目标数
    int only_pred_inpath_num = 0;  // 仅 pred inpath 目标数

    // 是否选中最终目标
    bool has_target = false;

    // 固定槽位的候选目标信息。按 fus_trkID 锁定槽位：目标持续存在则保持在同一槽，
    // 目标丢失则该槽 valid=false。保证同一目标跨帧 index 稳定，便于观察。
    std::array<TselObjDebug, PRE_TSEL_OBJ_NUM> objs;

    // 仅复位帧级统计量，不清空 objs 槽位(槽位生命周期由 fus_trkID 维护)。
    void Reset() {
        ego_spd = 0.0F;
        ego_accel = 0.0F;
        ego_yawrate = 0.0F;
        ego_curvature = 0.0F;
        aeb_active = false;
        presel_num = 0;
        inpath_num = 0;
        cur_inpath_num = 0;
        pred_inpath_num = 0;
        only_pred_inpath_num = 0;
        has_target = false;
    }
};

class SingleThreatTarget {
  public:
    SingleThreatTarget();
    ~SingleThreatTarget();

    void SelectLongThreatTgt(const AsVseOut &vse_out, AsObstacleList &obs_list, const GlobalConfig &config,
                             bool clamp_inpath_pred_offsets = false);
    void LongThreatTarget(const AsVseOut &vse_out);

    //预筛选目标
    std::vector<int> sort_index;
    std::vector<int> sort_valid_index;

    // inpath的目标
    std::vector<int> inpath_index;
    std::vector<int> cur_inpath_index;
    std::vector<int> pred_inpath_index;
    std::vector<int> only_pred_inpath_index;

    //最终选择目标信息
    LongSafeObject aeb_target;
    LongSafeObject fcw_target;

    longsafe::AsCurvaturePath ego_path_;

    std::array<LgSfObsData, kMaxFusionObject> obs_data_;

    // 目标筛选调试信息，每帧由 UpdateDebugInfo 填充，后续映射 capnp 输出 rsclbag。
    TselDebugInfo tsel_debug_;

  private:
    void SortByIdAndTTC(std::vector<int> &ids, std::vector<float> &ttcs);
    void Preprocess(const AsVseOut &vse_out, const GlobalConfig &config);
    void UpdateDebugInfo(const AsVseOut &vse_out);

    static SingleThreatTargetCal single_tgt_cal_;
};

} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_SINGLE_THREAT_TARGET_H_
