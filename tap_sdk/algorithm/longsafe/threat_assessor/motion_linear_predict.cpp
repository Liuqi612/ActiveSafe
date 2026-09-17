#include "motion_linear_predict.h"

namespace active_safety {
namespace longsafe {

MotionLinearPredict::MotionLinearPredict() {
}

MotionLinearPredict::~MotionLinearPredict() = default;

void MotionLinearPredict::CalcDefaultMotion(const AsCurvaturePath &ego_path, const VehicleConfig &veh_config, LgSfObsData &obs_data) {
    for (int i = 0; i < MAX_PREDICT_NUM; ++i) {
        float time = 0.02F * static_cast<float>(i);

        ObsMotionInfo &obs_motion = obs_data.pred_info[MotionType::Default].motion_info[i];

        const MotionStateAtTime &host_state = ego_path.GetHostState(time);
        // Long predict
        obs_motion.motion.long_pos   = obs_data.obs->long_posn;
        obs_motion.motion.long_vel   = obs_data.obs->long_vel;
        obs_motion.motion.long_accel = obs_data.obs->long_accel;
        (void)LinearPredictWithStop(obs_motion.motion.long_pos, obs_motion.motion.long_vel, obs_motion.motion.long_accel, time, true);

        // Lat predict
        obs_motion.motion.lat_pos   = obs_data.obs->lat_posn;
        obs_motion.motion.lat_vel   = obs_data.obs->lat_vel;
        obs_motion.motion.lat_accel = obs_data.obs->lat_accel;
        (void)LinearPredictWithStop(obs_motion.motion.lat_pos, obs_motion.motion.lat_vel, obs_motion.motion.lat_accel, time, true);

        if (obs_data.use_moving_heading) {
            obs_motion.motion.heading = atan2f(obs_motion.motion.lat_vel, obs_motion.motion.long_vel);
        } else {
            obs_motion.motion.heading = obs_data.obs->heading;
        }

        obs_motion.motion.curvature = 0.0F;

        PredictRelativeInfo::CalcRelativeInfo(host_state, veh_config, obs_data, obs_data.aeb_atv_target, obs_motion, time);
    }
    PredictRelativeInfo::CalculateTTRAndTTP(obs_data.pred_info[MotionType::Default]);
}

void MotionLinearPredict::CalcBrakeMotion(const AsCurvaturePath &ego_path, const VehicleConfig &veh_config, LgSfObsData &obs_data,
                                          float predict_brake_decel) {
    for (int i = 0; i < MAX_PREDICT_NUM; ++i) {
        float time = 0.02F * static_cast<float>(i);

        ObsMotionInfo &obs_motion = obs_data.pred_info[MotionType::Brake].motion_info[i];

        float a_steer = obs_data.obs->lat_accel * cosf(obs_data.obs->heading) - obs_data.obs->long_accel * sinf(obs_data.obs->heading);
        float a_long  = predict_brake_decel * cosf(obs_data.obs->heading) - a_steer * sinf(obs_data.obs->heading);
        float a_lat   = predict_brake_decel * sinf(obs_data.obs->heading) + a_steer * cosf(obs_data.obs->heading);

        obs_motion.motion.long_pos   = obs_data.obs->long_posn;
        obs_motion.motion.long_vel   = obs_data.obs->long_vel;
        obs_motion.motion.lat_pos    = obs_data.obs->lat_posn;
        obs_motion.motion.lat_vel    = obs_data.obs->lat_vel;
        obs_motion.motion.lat_accel  = a_lat;
        obs_motion.motion.long_accel = a_long;
        obs_motion.motion.curvature  = 0.0F;

        bool is_long_stop = LinearPredictWithStop(obs_motion.motion.long_pos, obs_motion.motion.long_vel, obs_motion.motion.long_accel, time, true);
        bool is_lat_stop  = LinearPredictWithStop(obs_motion.motion.lat_pos, obs_motion.motion.lat_vel, obs_motion.motion.lat_accel, time, true);

        if (is_long_stop && is_lat_stop) {
            obs_motion.motion.heading = obs_data.obs->heading;
        } else {
            if (obs_data.use_moving_heading) {
                obs_motion.motion.heading = atan2f(obs_motion.motion.lat_vel, obs_motion.motion.long_vel);
            } else {
                obs_motion.motion.heading = obs_data.obs->heading;
            }
        }
        const MotionStateAtTime &host_state = ego_path.GetHostState(time);

        PredictRelativeInfo::CalcRelativeInfo(host_state, veh_config, obs_data, obs_data.aeb_atv_target, obs_motion, time);
    }
    PredictRelativeInfo::CalculateTTRAndTTP(obs_data.pred_info[MotionType::Brake]);
}

void MotionLinearPredict::CalcLeftSteerMotion(const AsCurvaturePath &ego_path, const VehicleConfig &veh_config, LgSfObsData &obs_data,
                                              float predict_steer_accel) {
    for (int i = 0; i < MAX_PREDICT_NUM; ++i) {
        float time = 0.02F * static_cast<float>(i);

        MotionPredictInfo &pred_info = obs_data.pred_info[MotionType::LeftTurn];

        ObsMotionInfo &obs_motion = pred_info.motion_info[i];

        obs_motion.motion.curvature = obs_data.obs->curvature;

        obs_motion.motion.long_accel = obs_data.obs->long_accel - predict_steer_accel * sinf(obs_data.obs->heading);
        obs_motion.motion.lat_accel  = obs_data.obs->lat_accel + predict_steer_accel * cosf(obs_data.obs->heading);

        // Calculate the translate position
        obs_motion.motion.long_pos = obs_data.obs->long_posn;
        obs_motion.motion.lat_pos  = obs_data.obs->lat_posn;
        obs_motion.motion.long_vel = obs_data.obs->long_vel;
        obs_motion.motion.lat_vel  = obs_data.obs->lat_vel;

        (void)LinearPredictWithStop(obs_motion.motion.long_pos, obs_motion.motion.long_vel, obs_motion.motion.long_accel, time, false);
        (void)LinearPredictWithStop(obs_motion.motion.lat_pos, obs_motion.motion.lat_vel, obs_motion.motion.lat_accel, time, false);

        if (obs_data.use_moving_heading) {
            obs_motion.motion.heading = atan2f(obs_motion.motion.lat_vel, obs_motion.motion.long_vel);
        } else {
            obs_motion.motion.heading = obs_data.obs->heading;
        }

        const MotionStateAtTime &host_state = ego_path.GetHostState(time);
        PredictRelativeInfo::CalcRelativeInfo(host_state, veh_config, obs_data, obs_data.aeb_atv_target, obs_motion, time);
    }
    PredictRelativeInfo::CalculateTTRAndTTP(obs_data.pred_info[MotionType::LeftTurn]);
}

void MotionLinearPredict::CalcRightSteerMotion(const AsCurvaturePath &ego_path, const VehicleConfig &veh_config, LgSfObsData &obs_data,
                                               float predict_steer_accel) {
    for (int i = 0; i < MAX_PREDICT_NUM; ++i) {
        float time = 0.02F * static_cast<float>(i);

        MotionPredictInfo &pred_info = obs_data.pred_info[MotionType::RightTurn];

        ObsMotionInfo &obs_motion = pred_info.motion_info[i];

        obs_motion.motion.curvature = obs_data.obs->curvature;

        obs_motion.motion.long_accel = obs_data.obs->long_accel + predict_steer_accel * sinf(obs_data.obs->heading);
        obs_motion.motion.lat_accel  = obs_data.obs->lat_accel - predict_steer_accel * cosf(obs_data.obs->heading);

        // Calculate the translate position
        obs_motion.motion.long_pos = obs_data.obs->long_posn;
        obs_motion.motion.lat_pos  = obs_data.obs->lat_posn;
        obs_motion.motion.long_vel = obs_data.obs->long_vel;
        obs_motion.motion.lat_vel  = obs_data.obs->lat_vel;

        (void)LinearPredictWithStop(obs_motion.motion.long_pos, obs_motion.motion.long_vel, obs_motion.motion.long_accel, time, false);
        (void)LinearPredictWithStop(obs_motion.motion.lat_pos, obs_motion.motion.lat_vel, obs_motion.motion.lat_accel, time, false);

        if (obs_data.use_moving_heading) {
            obs_motion.motion.heading = atan2f(obs_motion.motion.lat_vel, obs_motion.motion.long_vel);
        } else {
            obs_motion.motion.heading = obs_data.obs->heading;
        }

        const MotionStateAtTime &host_state = ego_path.GetHostState(time);
        PredictRelativeInfo::CalcRelativeInfo(host_state, veh_config, obs_data, obs_data.aeb_atv_target, obs_motion, time);
    }
    PredictRelativeInfo::CalculateTTRAndTTP(obs_data.pred_info[MotionType::RightTurn]);
}

bool MotionLinearPredict::LinearPredictWithStop(float &pos, float &vel, float &acc, float time, bool check_stop) {
    // calc stop time
    const float stop_time = -math::SafeDivide(vel, acc);

    float min_time = time;
    if (check_stop  &&  (stop_time >= 0.0F)) {
        min_time = fminf(min_time, stop_time);
    }

    float squrd_time = min_time * min_time;

    pos = pos + vel * min_time + 0.5F * acc * squrd_time;
    vel = vel + acc * min_time;

    // check if stop
    if (fabs(time - min_time) > m_eps) {
        vel = 0.0F;
        acc = 0.0F;
        return true;
    }
    return false;
}

} // namespace longsafe
} // namespace active_safety
