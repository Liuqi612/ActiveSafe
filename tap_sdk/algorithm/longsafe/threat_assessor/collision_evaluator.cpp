#include "collision_evaluator.h"
#include <iostream>
namespace active_safety {
namespace longsafe {

CollisionEvaluator::CollisionEvaluator() {
}
CollisionEvaluator::~CollisionEvaluator() = default;

void CollisionEvaluator::ObjInPathEvaluator(const AsVseOut &vse_out, const AsCurvaturePath &ego_path, LgSfObsData &obs_data) {
    // InPath Current
    DecideInPathCurrent(vse_out, obs_data);
    // InPath Predict
    DecideInPathPredict(vse_out, ego_path, obs_data);
    // Select Path Result
    //先用底盘的判断，后续改成内部的
    SelectInPathResult(obs_data, vse_out.aeb_active);
}

void CollisionEvaluator::DecideInPathCurrent(const AsVseOut &vse_out, LgSfObsData &obs_data) {

    //统一动态调节 offs_lat_inpath_current 滤除低偏置目标
    float current_inpath_thres = vse_out.config.k_host_width * 0.5F + obs_data.offs_lat_inpath_current;
    float half_length = 0;
    //大角度车辆引入角点计算 || AEB激活标志位
    if (((obs_data.obs->f_is_vehicle) && (1.2F < fabs(obs_data.obs->heading) && fabs(obs_data.obs->heading) < 2.79F)) || (vse_out.aeb_active)) {
        half_length = 0.5F * obs_data.obs->length;
    }
    CornerPoints corner_points;

    float half_width = 0.5F * obs_data.side_width;
    float cos_hdg = cosf(obs_data.obs->heading);
    float sin_hdg = sinf(obs_data.obs->heading);
    int sign_count = 0;

    //计算目标角点：
    // 前左角（fl）
    corner_points.corner_fl_lgt = obs_data.obs->long_posn + cos_hdg * half_length - sin_hdg * half_width;
    corner_points.corner_fl_lat = obs_data.obs->lat_posn + sin_hdg * half_length + cos_hdg * half_width;

    float lateral_offset = CalcYawRtModelPredLatPos(corner_points.corner_fl_lgt, vse_out.rear_curvature,obs_data,vse_out.speed);

    corner_points.corved_corner_fl_lat = corner_points.corner_fl_lat - lateral_offset;
    if (corner_points.corved_corner_fl_lat > 0.0F) {
        sign_count += 1;
    } else {
        sign_count -= 1;
    }

    // 前右角（fr）
    corner_points.corner_fr_lgt = obs_data.obs->long_posn + cos_hdg * half_length + sin_hdg * half_width;
    corner_points.corner_fr_lat = obs_data.obs->lat_posn + sin_hdg * half_length - cos_hdg * half_width;

    lateral_offset = CalcYawRtModelPredLatPos(corner_points.corner_fr_lgt, vse_out.rear_curvature,obs_data,vse_out.speed);

    corner_points.corved_corner_fr_lat = corner_points.corner_fr_lat - lateral_offset;
    if (corner_points.corved_corner_fr_lat > 0.0F) {
        sign_count += 1;
    } else {
        sign_count -= 1;
    }

    // 后左角（rl）
    corner_points.corner_rl_lgt = obs_data.obs->long_posn - cos_hdg * half_length - sin_hdg * half_width;
    corner_points.corner_rl_lat = obs_data.obs->lat_posn - sin_hdg * half_length + cos_hdg * half_width;

    lateral_offset = CalcYawRtModelPredLatPos(corner_points.corner_rl_lgt, vse_out.rear_curvature,obs_data,vse_out.speed);

    corner_points.corved_corner_rl_lat = corner_points.corner_rl_lat - lateral_offset;
    if (corner_points.corved_corner_rl_lat > 0.0F) {
        sign_count += 1;
    } else {
        sign_count -= 1;
    }

    // 后右角（rr）
    corner_points.corner_rr_lgt = obs_data.obs->long_posn - cos_hdg * half_length + sin_hdg * half_width;
    corner_points.corner_rr_lat = obs_data.obs->lat_posn - sin_hdg * half_length - cos_hdg * half_width;

    lateral_offset = CalcYawRtModelPredLatPos(corner_points.corner_rr_lgt, vse_out.rear_curvature,obs_data,vse_out.speed);

    corner_points.corved_corner_rr_lat = corner_points.corner_rr_lat - lateral_offset;
    if (corner_points.corved_corner_rr_lat > 0.0F) {
        sign_count += 1;
    } else {
        sign_count -= 1;
    }

    //判断是否和目标有交叉
    if ((sign_count == 4)  ||  (sign_count == -4)) {
        float min_lat = 100.0F;

        min_lat = fmin(min_lat, fabs(corner_points.corved_corner_fl_lat));
        min_lat = fmin(min_lat, fabs(corner_points.corved_corner_fr_lat));
        min_lat = fmin(min_lat, fabs(corner_points.corved_corner_rl_lat));
        min_lat = fmin(min_lat, fabs(corner_points.corved_corner_rr_lat));

        if (min_lat < current_inpath_thres) {
            //若和目标角点仍不满足，则判断最近一个角点横向位置
            obs_data.inpath_current = true;

        } else {
            obs_data.inpath_current = false;
        }

    } else {
        obs_data.inpath_current = true;
    }
}

void CollisionEvaluator::DecideInPathPredict(const AsVseOut &vse_out, const AsCurvaturePath &ego_path, LgSfObsData &obs_data) {
    //目标预测
    if (obs_data.curve_motion) {
        //曲率运动预测
    } else if (obs_data.curve_motion == false && obs_data.stationary) {
        MotionStaticPredict::CalcStaticObjMotion(ego_path, vse_out.config, obs_data, obs_data.pred_info[MotionType::Default]);
    } else {
        MotionLinearPredict::CalcDefaultMotion(ego_path, vse_out.config, obs_data);
    }

    if (obs_data.pred_info[MotionType::Default].ttr_index > 0) {
        int idx = obs_data.pred_info[MotionType::Default].ttr_index;
        float pred_time = 0.02F * static_cast<float>(idx);

        const MotionStateAtTime &host_state = ego_path.GetHostState(pred_time);

        const ObsMotionInfo &obs_motion = obs_data.pred_info[MotionType::Default].motion_info[idx];
        // AEB激活前最好不要动纵向补偿，标定横向补偿进行优化 防止纵向补偿带来的TTR变动连带影响后面激活阈值的变化
        bool pred_inpath = PredictRelativeInfo::CheckGeometryInpath(host_state, obs_motion, vse_out.config, obs_data.side_length, obs_data.side_width,
                                                                    obs_data.offs_lgt_inpath_pred_edge, obs_data.offs_lat_inpath_pred_edge,
                                                                    obs_data.offs_obs_lat_pred, 0, obs_data.pred_inpath_fail_reason,
                                                                    &obs_data.pred_inpath_debug);
        // 第二轮失败原因只保留当前 TTR 采样点的结果，不再使用 TTP 采样点重算覆盖。

        //默认运动不在inpath，则返回false，静止目标采用默认运动结果
        if ((pred_inpath == false)  ||  obs_data.stationary) {
            obs_data.inpath_predict = pred_inpath;
            return;
        }
        //当前还是采用默认条件下结果
        obs_data.inpath_predict = pred_inpath;
        //【TODO】：若目标是刹车、转向，则inpath_predict为默认和目标避让行为后的结果同时满足inpath
    } else {
        obs_data.inpath_predict = false;
        // ttr_index<=0：预测周期内目标从未进入 inpath，无 TTR 时刻可供第二轮检查。
        obs_data.pred_inpath_fail_reason = PredInpathFailReason::NONE;
        obs_data.pred_inpath_debug.Reset();
    }
}

void CollisionEvaluator::SelectInPathResult(LgSfObsData &obs_data, bool aeb_active_cmbb) {
    obs_data.predict_valid = false;
    // Check predict valid.
    float ttr = obs_data.pred_info[0].ttr;
    float obs_motion_dist = obs_data.obs->speed * ttr;
    bool spd_ok = (obs_data.obs->f_is_motor_vehicle == false || obs_data.obs->speed > 1.0F)&&(!obs_data.stationary);
    bool pred_distance = (obs_data.obs->f_is_motor_vehicle == false || obs_motion_dist < 50.0F);
    bool ttr_valid = ttr > 0.0F && ttr < 3.0F;
    bool pred_type_valid = (obs_data.obs->object_class != ObjectClass::UNIDENTIFIED_VEHICLE) &&
        (obs_data.obs->object_class != ObjectClass::UNDETERMINED) && obs_data.obs->object_class != ObjectClass::CONE &&
        obs_data.obs->object_class != ObjectClass::GENOBJ && obs_data.obs->object_class != ObjectClass::GOD &&obs_data.obs->object_class != ObjectClass::OCC;
    if (spd_ok && pred_distance && ttr_valid && pred_type_valid) {
        obs_data.predict_valid = true;
    }
    // 记录 predict_valid 各子判据，调试日志据此说明目标为何未被选中
    obs_data.predict_valid_spd_ok          = spd_ok;
    obs_data.predict_valid_pred_distance   = pred_distance;
    obs_data.predict_valid_ttr_valid       = ttr_valid;
    obs_data.predict_valid_pred_type_valid = pred_type_valid;
    //如果预测无效，直接用当前判断结果
    if (obs_data.predict_valid == false) {
        obs_data.inpath_res = obs_data.inpath_current;
        return;
    }

    if (aeb_active_cmbb) {
        // AEB激活后，当前Inpath不满足或预测inpath为true，则用预测结果.
        obs_data.inpath_res = ((obs_data.inpath_current == true)  ||  (obs_data.inpath_predict == true));
    } else {
        // AEB没激活，判断是否需要同时满足Cur和Pred
        bool strict_inpath_check = false;
        bool f_low_lat_spd_obj = CheckLowLatSpdObject(obs_data.obs->object_class, obs_data.obs->lat_vel);
        strict_inpath_check = f_low_lat_spd_obj;
        // 如果需要同时满足，则只有CurInpath和PredInpath都为true时，inpath结果才为true.
        if (strict_inpath_check) {
            obs_data.inpath_res = ((obs_data.inpath_current == true)  &&  (obs_data.inpath_predict == true));
        } else {
            obs_data.inpath_res = obs_data.inpath_predict;
        }
    }
}

bool CollisionEvaluator::CheckLowLatSpdObject(ObjectClass obj_class, float obj_lat_vel) {
    switch (obj_class) {
        case ObjectClass::BICYCLE: {
            if (fabs(obj_lat_vel) < 0.8) {
                return true;
            }
            break;
        }
        case ObjectClass::PEDESTRIAN: {
            if (fabs(obj_lat_vel) < 0.7) {
                return true;
            }
            break;
        }
        case ObjectClass::GENOBJ: {
            return true;
            break;
        }
        default:
            break;
    }
    return false;
}

float CollisionEvaluator::CalcYawRtModelPredLatPos(float posx, float c0, LgSfObsData &obs_data,float speed)
{
    // 特殊目标类型 + 极小曲率时，横向偏移置0
    const bool is_special_obj = (obs_data.obs->object_class == ObjectClass::GOD ||
                                 obs_data.obs->object_class == ObjectClass::GENOBJ);
    const bool is_small_curvature = (std::fabs(c0) < 0.004f);

    if ((is_special_obj && is_small_curvature)||((std::fabs(c0) < 0.0005f)&&(speed > 25.0)))
    {
        return 0.0f;
    }

    // 常规二次曲线横向偏移计算
    return c0 * 0.5f * posx * posx;
}

} // namespace longsafe
} // namespace active_safety
