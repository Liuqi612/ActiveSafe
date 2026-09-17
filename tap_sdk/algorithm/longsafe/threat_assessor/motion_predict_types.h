#ifndef TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_PREDICT_TYPES_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_PREDICT_TYPES_H_
#include <array>

#define MAX_PREDICT_NUM 151

namespace active_safety {
namespace longsafe {

struct MotionPredict {
    float long_pos   = 0.0F;
    float lat_pos    = 0.0F;
    float long_vel   = 0.0F;
    float lat_vel    = 0.0F;
    float long_accel = 0.0F;
    float lat_accel  = 0.0F;
    float speed      = 0.0F;
    float accel      = 0.0F;
    float heading    = 0.0F;
    float curvature  = 0.0F;
};

struct RelativePosPredict {
    bool  inpath           = false;
    float long_pos         = 0.0F;
    float lat_pos          = 0.0F;
    float heading          = 0.0F;
    float abs_cos_hdg      = 0.0F;
    float abs_sin_hdg      = 0.0F;
    float safe_long_margin = 0.0F;
    float safe_lat_margin  = 0.0F;
    float lat_overlap_rate = 0.0F; // 目标横向投影落入第一轮自车横向包络的比例，[0, 1]
};

struct ObsMotionInfo {
    MotionPredict      motion;
    RelativePosPredict rel_info;
    // CheckGeometryInpath 当前预测周期的失败原因，数值对应 PredInpathFailReason
    int pred_inpath_fail_reason = 0;
};

struct MotionPredictInfo {
    std::array<ObsMotionInfo, MAX_PREDICT_NUM> motion_info;

    int   ttr_index = -1;
    int   ttp_index = -1;
    float ttr       = -100;
    float ttp       = -100;
    float ttr_lat_overlap_rate = 0.0F;
};

enum MotionType { Default, Brake, LeftTurn, RightTurn };

// CheckGeometryInpath 各检查的中间量，对应导致 pred_inpath_fail 的判定。
// 只记录导致失败的那一组（与原 cout 调试输出一致），便于排查 pred inpath 失败原因。
struct PredInpathDebug {
    // 条件1：自车系纵向检查
    float rel_lgt = 0.0F;     // obs_motion.rel_info.long_pos
    float front_limit = 0.0F; // host_front_lgt_pos + safe_long_margin
    float rear_limit = 0.0F;  // host_rear_lgt_pos
    // 条件2：自车系横向检查
    float safe_lat = 0.0F;        // |lat_pos| - safe_lat_margin
    float half_host_width = 0.0F; // 0.5*k_host_width + host_lat_offs
    // 条件3：目标系纵向检查
    float host_rel_obs_lgt = 0.0F;       // |host_rel_obs_lgtpos|
    float obs_lgt_safe_space = 0.0F;     // host_rel_obs_lgtsafe_space + half_obs_length
    // 条件4：目标系横向检查
    float host_rel_obs_lat = 0.0F;       // |host_rel_obs_latpos|
    float obs_lat_safe_space = 0.0F;     // host_rel_obs_latsafe_space + half_obs_width + obs_lat_offs

    void Reset() {
        rel_lgt = 0.0F;
        front_limit = 0.0F;
        rear_limit = 0.0F;
        safe_lat = 0.0F;
        half_host_width = 0.0F;
        host_rel_obs_lgt = 0.0F;
        obs_lgt_safe_space = 0.0F;
        host_rel_obs_lat = 0.0F;
        obs_lat_safe_space = 0.0F;
    }
};

} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_PREDICT_TYPES_H_
