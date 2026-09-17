#include "motion_static_predict.h"

namespace active_safety {
namespace longsafe {

MotionStaticPredict::MotionStaticPredict() {
}

MotionStaticPredict::~MotionStaticPredict() = default;

void MotionStaticPredict::CalcStaticObjMotion(const AsCurvaturePath &ego_path, const VehicleConfig &veh_config, const LgSfObsData &obs_data,
                                              MotionPredictInfo &pred_info) {
    for (int i = 0; i < MAX_PREDICT_NUM; i++) {
        float pred_time = 0.02F * static_cast<float>(i);

        const MotionStateAtTime &host_state = ego_path.GetHostState(pred_time);

        //计算目标预测位置
        pred_info.motion_info[i].motion.long_pos   = obs_data.obs->long_posn;
        pred_info.motion_info[i].motion.lat_pos    = obs_data.obs->lat_posn;
        pred_info.motion_info[i].motion.long_vel   = 0.0F;
        pred_info.motion_info[i].motion.lat_vel    = 0.0F;
        pred_info.motion_info[i].motion.long_accel = 0.0F;
        pred_info.motion_info[i].motion.lat_accel  = 0.0F;
        pred_info.motion_info[i].motion.speed      = 0.0F;
        pred_info.motion_info[i].motion.accel      = 0.0F;
        pred_info.motion_info[i].motion.heading    = obs_data.obs->heading;
        pred_info.motion_info[i].motion.curvature  = 0.0F;
        //计算和自车相对信息
        PredictRelativeInfo::CalcRelativeInfo(host_state, veh_config, obs_data, obs_data.aeb_atv_target, pred_info.motion_info[i], pred_time);
    }
    PredictRelativeInfo::CalculateTTRAndTTP(pred_info);
}

} // namespace longsafe
} // namespace active_safety
