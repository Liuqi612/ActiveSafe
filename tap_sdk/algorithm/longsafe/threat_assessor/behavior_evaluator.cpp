#include "behavior_evaluator.h"

#include "math/lookuptable/lookuptable.h"
namespace active_safety {
namespace longsafe {
BehaviorEvaluator::BehaviorEvaluator() {
}
BehaviorEvaluator::~BehaviorEvaluator() = default;

BehaviorEvaluatorCal BehaviorEvaluator::behavior_cal_;

void BehaviorEvaluator::ObjBehaviorEvaluator(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    CalcObjAvoidanceManoeuvers(obs_data);
    MotionBehaviorEvaluator(obs_data);
    DetectObsCutIn(vse_out, obs_data);
}

void BehaviorEvaluator::UpdateObsManType(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    EvalObsCrossLeanToStraightBySpd(vse_out, obs_data);
}

void BehaviorEvaluator::EvalObsCrossLeanToStraightBySpd(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    if (fabs(vse_out.yawrate) > 0.03F || fabs(obs_data.obs->lat_vel) < 1.0F || fabs(obs_data.obs->long_vel) > 2.0F ||
        (obs_data.obs->object_class != ObjectClass::CAR && obs_data.obs->object_class != ObjectClass::BICYCLE &&
         obs_data.obs->object_class != ObjectClass::ESCOOTER && obs_data.obs->object_class != ObjectClass::MOTORCYCLE)) {
        obs_data.mans_type &= ~ObsMotionMantype::CROSS_LEAN_TO_STRAIGHT_BY_SPD;
        return;
    }
    int   rate_up_cnt      = 0;
    float prev_moving_rate = 0.0F;

    const int rate_up_cnt_thres = 6;
    for (std::size_t i = 0; i < obs_data.obs->fus_vel.size(); i++) {
        float vel_y = obs_data.obs->fus_vel.get_frame(i).y;
        if (fabs(vel_y) < 0.01F) {
            vel_y = 0.01F;
        }
        float moving_rate = fabs(obs_data.obs->fus_vel.get_frame(i).x / vel_y);
        if (i == 0) {
            prev_moving_rate = moving_rate;
        } else {
            if (moving_rate < prev_moving_rate) {
                rate_up_cnt++;
            } else {
                if (rate_up_cnt > 1) {
                    rate_up_cnt--;
                } else {
                    rate_up_cnt = 0;
                }
            }
            prev_moving_rate = moving_rate;
        }
        if (rate_up_cnt >= rate_up_cnt_thres) {
            break;
        }
    }
    if (rate_up_cnt >= rate_up_cnt_thres) {
        obs_data.mans_type |= ObsMotionMantype::CROSS_LEAN_TO_STRAIGHT_BY_SPD;
    } else {
        obs_data.mans_type &= ~ObsMotionMantype::CROSS_LEAN_TO_STRAIGHT_BY_SPD;
    }
}

void BehaviorEvaluator::DetectObsCutIn(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    CalcInputMeasure(vse_out, obs_data);
    if ((obs_data.obs->object_class != ObjectClass::CAR && obs_data.obs->object_class != ObjectClass::TRUCK &&
         obs_data.obs->object_class != ObjectClass::BICYCLE && obs_data.obs->object_class != ObjectClass::MOTORCYCLE &&
         obs_data.obs->object_class != ObjectClass::ESCOOTER)) {
        return;
    }
    if (fabs(obs_data.xoxp_meas) >= 2.5F) {
        return;
    }

    CalcProbability(obs_data);
}
void BehaviorEvaluator::CalcInputMeasure(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    float half_length = 0.5F * obs_data.obs->length;
    float half_width  = 0.5F * obs_data.obs->width;
    float cos_hdg     = cosf(obs_data.obs->heading);
    float sin_hdg     = sinf(obs_data.obs->heading);

    obs_data.xoxp_meas = obs_data.obs->lat_posn - CalcRoadModelLatOffs(0.0F, vse_out.rear_curvature, 0.0F, obs_data.obs->long_posn);
    //计算目标角点：
    // 前左角（fl）
    obs_data.corner_pt_.corner_fl_lgt = obs_data.obs->long_posn + cos_hdg * half_length - sin_hdg * half_width;
    obs_data.corner_pt_.corner_fl_lat = obs_data.obs->lat_posn + sin_hdg * half_length + cos_hdg * half_width;

    float lateral_offset = CalcRoadModelLatOffs(0.0F, vse_out.rear_curvature, 0.0F, obs_data.corner_pt_.corner_fl_lgt);

    obs_data.corner_pt_.corved_corner_fl_lat = obs_data.corner_pt_.corner_fl_lat - lateral_offset;

    // 前右角（fr）
    obs_data.corner_pt_.corner_fr_lgt = obs_data.obs->long_posn + cos_hdg * half_length + sin_hdg * half_width;
    obs_data.corner_pt_.corner_fr_lat = obs_data.obs->lat_posn + sin_hdg * half_length - cos_hdg * half_width;

    lateral_offset = CalcRoadModelLatOffs(0.0F, vse_out.rear_curvature, 0.0F, obs_data.corner_pt_.corner_fr_lgt);

    obs_data.corner_pt_.corved_corner_fr_lat = obs_data.corner_pt_.corner_fr_lat - lateral_offset;

    // 后左角（rl）
    obs_data.corner_pt_.corner_rl_lgt = obs_data.obs->long_posn - cos_hdg * half_length - sin_hdg * half_width;
    obs_data.corner_pt_.corner_rl_lat = obs_data.obs->lat_posn - sin_hdg * half_length + cos_hdg * half_width;

    lateral_offset = CalcRoadModelLatOffs(0.0F, vse_out.rear_curvature, 0.0F, obs_data.corner_pt_.corner_rl_lgt);

    obs_data.corner_pt_.corved_corner_rl_lat = obs_data.corner_pt_.corner_rl_lat - lateral_offset;

    // 后右角（rr）
    obs_data.corner_pt_.corner_rr_lgt = obs_data.obs->long_posn - cos_hdg * half_length + sin_hdg * half_width;
    obs_data.corner_pt_.corner_rr_lat = obs_data.obs->lat_posn - sin_hdg * half_length - cos_hdg * half_width;

    lateral_offset = CalcRoadModelLatOffs(0.0F, vse_out.rear_curvature, 0.0F, obs_data.corner_pt_.corner_rr_lgt);

    obs_data.corner_pt_.corved_corner_rr_lat = obs_data.corner_pt_.corner_rr_lat - lateral_offset;

    if (obs_data.obs->lat_posn > 0) {
        obs_data.lat_dist_to_host = std::min({obs_data.corner_pt_.corner_fl_lat, obs_data.corner_pt_.corner_fr_lat, obs_data.corner_pt_.corner_rr_lat,
                                              obs_data.corner_pt_.corner_rl_lat});
    } else {
        obs_data.lat_dist_to_host = std::max({obs_data.corner_pt_.corner_fl_lat, obs_data.corner_pt_.corner_fr_lat, obs_data.corner_pt_.corner_rr_lat,
                                              obs_data.corner_pt_.corner_rl_lat});
    }
    obs_data.lat_vel_to_host = obs_data.obs->lat_vel;
    obs_data.heading_to_host = obs_data.obs->heading - CalcRoadModelHeading(0.0F, vse_out.rear_curvature, 0.0, obs_data.obs->long_posn);
}

void BehaviorEvaluator::CalcProbability(LgSfObsData &obs_data) {
    float valid_max_lat_dist =
        LookUpTable::LookupTable1D<4>(behavior_cal_.k_cutin_lat_dist_range_x, behavior_cal_.k_cutin_lat_dist_range_y, obs_data.obs->long_posn);

    float prob_lat_dist = 0.0F;
    float abs_lat_dist  = fabs(obs_data.lat_dist_to_host);

    if ((abs_lat_dist <= valid_max_lat_dist)  &&  (valid_max_lat_dist > 0.0F)) {
        // 归一化横向距离 [0, 1]
        float normalized_lat_dist = math::SafeDivide(abs_lat_dist, valid_max_lat_dist);
        // 高斯分布：距离越近，概率越高
        // 使用归一化距离的平方除以sigma，控制概率衰减速度
        float sigma   = behavior_cal_.k_cutin_lat_dist_sigma;
        prob_lat_dist = expf(-math::SafeDivide(normalized_lat_dist * normalized_lat_dist, sigma));
        prob_lat_dist = math::Clamp(prob_lat_dist, 0.0F, 1.0F);
    }

    float lat_vel_threshold = behavior_cal_.k_cutin_lat_vel_threshold_default;

    if (obs_data.obs->lat_posn > 0.0F) {
        lat_vel_threshold = -lat_vel_threshold;
    }

    float prob_lat_vel = fminf(math::SafeDivide(obs_data.lat_vel_to_host, lat_vel_threshold), 1.0F);

    float prob_tto = 0.0F;
    // float valid_max_tto = LookUpTable::LookupTable1D<2>(
    //     behavior_cal_.k_cutin_tto_range_x,
    //     behavior_cal_.k_cutin_tto_range_y,
    //     obs_data.obs->long_posn
    // );
    // if (obs_data.ttlc < valid_max_tto) {
    //     prob_tto = expf(-obs_data.ttlc / valid_max_tto);
    // }

    float abs_heading = fabsf(obs_data.heading_to_host);

    bool is_away_from_host =
        (obs_data.obs->lat_posn > 0.0F && obs_data.heading_to_host > 0.0F) || (obs_data.obs->lat_posn < 0.0F && obs_data.heading_to_host < 0.0F);

    float prob_heading = 0.0F;
    float full_thres   = behavior_cal_.k_cutin_heading_full_thres; // 约15°（概率峰值）

    if (!is_away_from_host) {
        prob_heading = fminf(math::SafeDivide(abs_heading, full_thres), 1.0F);
    }

    prob_heading = math::Clamp(prob_heading, 0.0F, 1.0F);

    float weight_lat_dist = behavior_cal_.k_cutin_weight_lat_dist;
    float weight_lat_vel  = behavior_cal_.k_cutin_weight_lat_vel;
    float weight_tto      = behavior_cal_.k_cutin_weight_tto;
    float weight_heading  = behavior_cal_.k_cutin_weight_heading;

    float sum_weight = weight_lat_dist + weight_lat_vel + weight_tto + weight_heading;
    if (sum_weight > 1.0F) {
        weight_lat_dist = weight_lat_dist / sum_weight;
        weight_lat_vel  = weight_lat_vel / sum_weight;
        weight_tto      = weight_tto / sum_weight;
        weight_heading  = weight_heading / sum_weight;
    }

    // 加权求和得到最终Cut-in概率
    obs_data.cutin_prob = prob_lat_dist * weight_lat_dist + prob_lat_vel * weight_lat_vel + prob_tto * weight_tto + prob_heading * weight_heading;

    // 确保概率在[0, 1]范围内
    obs_data.cutin_prob = math::Clamp(obs_data.cutin_prob, 0.0F, 1.0F);
}

void BehaviorEvaluator::MotionBehaviorEvaluator(LgSfObsData &obs_data) {
    //判断目标静止
    if (obs_data.obs->object_class == ObjectClass::PEDESTRIAN || obs_data.obs->object_class == ObjectClass::BICYCLE ||
        obs_data.obs->object_class == ObjectClass::ESCOOTER) {
        float moving_spd_thres = behavior_cal_.k_vru_moving_spd_thres;
        if (obs_data.stationary) {
            moving_spd_thres = moving_spd_thres * 1.1F;
        }
        obs_data.stationary = fabsf(obs_data.obs->speed) < moving_spd_thres;
    } else if (obs_data.obs->f_is_vehicle) {
        float moving_spd_thres = behavior_cal_.k_veh_moving_spd_thres;
        if (obs_data.stationary) {
            moving_spd_thres = moving_spd_thres * 1.1F;
        }
        obs_data.stationary = fabsf(obs_data.obs->speed) < moving_spd_thres;
    } else {
        obs_data.stationary = true;
    }
    //如果目标静止，则不存在其他运动状态
    if (obs_data.stationary) {
        obs_data.oncoming     = false;
        obs_data.curve_motion = false;
        return;
    }
    // 判断目标oncoming：目标纵向速度 < -2 m/s（朝自车方向运动）
    obs_data.oncoming = (obs_data.obs->long_vel < behavior_cal_.k_oncoming_lgtvel_thd);
}

void BehaviorEvaluator::CalcObjAvoidanceManoeuvers(LgSfObsData &obs_data) {
    switch (obs_data.obs->object_class) {
        case ObjectClass::PEDESTRIAN: {
            obs_data.pred_decel      = behavior_cal_.k_ped_pred_decel;
            obs_data.lat_steer_accel = behavior_cal_.k_ped_alat_steer_pred;
            break;
        }
        case ObjectClass::ANIMAL:
        case ObjectClass::GENOBJ: {
            obs_data.pred_decel      = 0.0F;
            obs_data.lat_steer_accel = 0.0F;
            break;
        }
        case ObjectClass::BICYCLE: {
            obs_data.pred_decel      = behavior_cal_.k_bike_pred_decel;
            obs_data.lat_steer_accel = behavior_cal_.k_bike_alat_steer_pred;
            break;
        }
        case ObjectClass::MOTORCYCLE:
        case ObjectClass::ESCOOTER:
        case ObjectClass::CAR:
        case ObjectClass::TRUCK:
        case ObjectClass::UNIDENTIFIED_VEHICLE: {
            obs_data.pred_decel      = CalcDeclerationForAovidance(obs_data.obs->speed, obs_data.obs->accel, behavior_cal_.k_veh_pred_decel);
            obs_data.lat_steer_accel = math::LookUpTable::LookupTable1D<9>(behavior_cal_.k_obj_veh_spd_steer, behavior_cal_.k_veh_alat_steer_pred,
                                                                           fabsf(obs_data.obs->speed));
            break;
        }
        default: {
            obs_data.pred_decel      = 0.0F;
            obs_data.lat_steer_accel = 0.0F;
            break;
        }
    }
}

float BehaviorEvaluator::CalcDeclerationForAovidance(float speed, float accel, float default_value) {
    float decel     = 0.0F;
    float signDecel = default_value * math::SignF(speed);
    if (speed < 0.0F) {
        decel = fmaxf(signDecel, accel);
    } else {
        decel = fminf(signDecel, accel);
    }
    return decel;
}

float BehaviorEvaluator::CalcRoadModelLatOffs(float heading, float c0, float c1, float x) {
    float sqrd_x = x * x;
    return heading * x + c0 * 0.5F * sqrd_x + c1 * 0.16667F * sqrd_x * x;
}

float BehaviorEvaluator::CalcRoadModelHeading(float heading, float c0, float c1, float x) {
    return heading + c0 * x + c1 * 0.5F * x * x;
}

} // namespace longsafe
} // namespace active_safety
