#include "motion_predict.h"
#include <fstream>
#include <iostream>

namespace active_safety {
namespace longsafe {

namespace {
constexpr float kMinProjectedWidth = 1.0e-4F;


/*
1：如果目标投影完全被自车宽度包裹，重叠率为 100%。
2：如果自车宽度完全被目标投影包裹，重叠率也为 100%。
3：其他情况属于部分重叠，统一使用自车宽度作为分母：*/
float CalculateLatOverlapRate(float obs_lat_pos,
                              float obs_half_projected_width,
                              float host_half_width) {
    if (obs_half_projected_width <= kMinProjectedWidth ||
        host_half_width <= 0.0F) {
        return 0.0F;
    }

    const float obs_min = obs_lat_pos - obs_half_projected_width;
    const float obs_max = obs_lat_pos + obs_half_projected_width;

    const float host_min = -host_half_width;
    const float host_max = host_half_width;

    // 目标完全被自车横向范围包裹
    const bool obs_contained_by_host =
        obs_min >= host_min && obs_max <= host_max;

    // 自车完全被目标横向投影包裹
    const bool host_contained_by_obs =
        host_min >= obs_min && host_max <= obs_max;

    if (obs_contained_by_host || host_contained_by_obs) {
        return 1.0F;
    }

    const float overlap_width =
        fmaxf(0.0F,
               fminf(host_max, obs_max) -
               fmaxf(host_min, obs_min));

    const float host_width = host_max - host_min;

    return fminf(overlap_width / host_width, 1.0F);
}
} // namespace

void PredictRelativeInfo::CalcObjRelPosDist(const MotionStateAtTime &host_state, const VehicleConfig &ego_param, const MotionPredict &obj_predict,
                                            float obj_length, float obj_width, RelativePosPredict &rel_pos) {
    //计算四个最近点距离
    // 前后保险杠中心
    Point2D host_front_bumper_center;
    host_front_bumper_center.x = host_state.long_pos + ego_param.k_dist_to_rear_axle * cosf(host_state.heading_angle);
    host_front_bumper_center.y = host_state.lat_pos + ego_param.k_dist_to_rear_axle * sinf(host_state.heading_angle);

    Point2D host_rear_bumper_center;

    float l0 = ego_param.k_host_length - ego_param.k_dist_to_rear_axle;

    host_rear_bumper_center.x = host_state.long_pos - l0 * cosf(host_state.heading_angle);
    host_rear_bumper_center.y = host_state.lat_pos - l0 * sinf(host_state.heading_angle);

    float host_hdg = host_state.heading_angle;
    float cos_h    = cosf(host_hdg);
    float sin_h    = sinf(host_hdg);
    float half_hw  = 0.5F * ego_param.k_host_width;

    // 自车前部中心：从前保沿车身纵轴“往后”移动 half_hw
    Point2D host_front_center{host_front_bumper_center.x - half_hw * cos_h, host_front_bumper_center.y - half_hw * sin_h};

    // 自车后部中心：从后保沿车身纵轴“往前”移动 half_hw
    Point2D host_rear_center{host_rear_bumper_center.x + half_hw * cos_h, host_rear_bumper_center.y + half_hw * sin_h};

    float obj_hdg  = obj_predict.heading;
    float cos_hdg  = cosf(obj_hdg);
    float sin_hdg  = sinf(obj_hdg);
    float half_ow  = 0.5F * obj_width;
    float dist_min = fmaxf(obj_length * 0.5F - half_ow, 0.0F);

    // 目标前部中心（纵轴正方向 +L/2-W/2）
    Point2D obj_front_center{obj_predict.long_pos + dist_min * cos_hdg, obj_predict.lat_pos + dist_min * sin_hdg};

    // 目标后部中心（纵轴负方向 -L/2-W/2）
    Point2D obj_rear_center{obj_predict.long_pos - dist_min * cos_hdg, obj_predict.lat_pos - dist_min * sin_hdg};
    //计算四个距离
    // rel_pos.dist_front_host_front = (host_front_center - obj_front_center).Norm();
    // rel_pos.dist_front_host_back  = (host_rear_center - obj_front_center).Norm();
    // rel_pos.dist_back_host_front  = (host_front_center - obj_rear_center).Norm();
    // rel_pos.dist_back_host_back   = (host_rear_center - obj_rear_center).Norm();
}

void PredictRelativeInfo::CalcRelativeInfo(const MotionStateAtTime &host_state, const VehicleConfig &veh_config, const LgSfObsData &obs_data,
                                           bool aeb_active, ObsMotionInfo &obs_motion, float predict_time) {

    const MotionPredict &obj_predict = obs_motion.motion;
    RelativePosPredict & rel         = obs_motion.rel_info;

    float half_obs_length = 0.5F * obs_data.side_length;
    float half_obs_width  = 0.5F * obs_data.side_width;
    //计算相对航向角
    rel.heading     = obj_predict.heading - host_state.heading_angle;
    rel.abs_cos_hdg = fabs(cosf(rel.heading));
    rel.abs_sin_hdg = fabs(sinf(rel.heading));

    float dx = obj_predict.long_pos - host_state.long_pos;
    float dy = obj_predict.lat_pos - host_state.lat_pos;

    float cos_a = cosf(host_state.heading_angle);
    float sin_a = sinf(host_state.heading_angle);

    // 目标在自车位置下的纵向相对位置信息
    rel.long_pos = cos_a * dx + sin_a * dy;
    // 目标在自车位置下的纵向安全空间
    rel.safe_long_margin = rel.abs_cos_hdg * half_obs_length + rel.abs_sin_hdg * half_obs_width;
    // 目标在自车位置下的横向相对位置信息
    rel.lat_pos = -sin_a * dx + cos_a * dy;
    // 目标在自车位置下的横向安全空间
    rel.safe_lat_margin = rel.abs_sin_hdg * half_obs_length + rel.abs_cos_hdg * half_obs_width;
    // 此处重载函数不引入offset 同时上游CalcBoundingBox针对aeb_target 已经进行了部分目标膨胀 不需要进行区分
    
    // 横向重叠率与第一轮轨迹重叠使用相同的自车横向包络口径（参考close_edge far_edge）
    const float host_lat_offs = aeb_active ? 5.0F : 0.0F;
    const float obs_lat_offs = aeb_active ? 1.0F : 0.0F;
    const float half_host_width = 0.5F * veh_config.k_host_width + host_lat_offs;
    rel.lat_overlap_rate = CalculateLatOverlapRate(rel.lat_pos, rel.safe_lat_margin, half_host_width);

    // 仅对指定fus_trkID 输出第一轮 TTR 轨迹重叠遍历记录。
    const uint8_t debug_mode = 0;
    //     (obs_data.obs->fus_trkID == 38) ? 1U : 0U;
    PredInpathFailReason fail_reason = PredInpathFailReason::NONE;
    rel.inpath = CheckGeometryInpath(host_state, obs_motion, veh_config,
                                     obs_data.side_length, obs_data.side_width,
                                     0.0F, host_lat_offs, obs_lat_offs,
                                     debug_mode, fail_reason, nullptr, predict_time);
    obs_motion.pred_inpath_fail_reason = static_cast<int>(fail_reason);

}

int PredictRelativeInfo::FindMinDistIndex(const std::array<RelativePosPredict, MAX_PREDICT_NUM> &rel_info) {
    (void)rel_info;
    int min_index = -1;
    // float min_value = std::numeric_limits<float>::max();

    // for (int i = 0; i < rel_info.size(); ++i) {
    //     const auto &rp = rel_info[i];
    //     // 找出当前元素中四个距离的最小值
    //     // float current_min = std::min({rp.dist_front_host_front, rp.dist_front_host_back, rp.dist_back_host_front, rp.dist_back_host_back});

    //     // 如果当前最小值小于全局最小值，更新索引和值
    //     // if (current_min < min_value) {
    //     //     min_value = current_min;
    //     //     min_index = i;
    //     // }
    // }
    return min_index;
}
/**
 * @brief 检查目标在自车路径上的几何关系
 * @param host_state 自车状态
 * @param obs_pred 目标预测
 * @param veh_config 车辆配置
 * @param obs_length 目标长度
 * @param obs_width 目标宽度
 * @param host_lgt_offs 纵向偏移,以前保向后1m为点，正值代表向前缩放，负值代表向后缩放
 * @param host_lat_offs 横向偏移,以后轴中心为点，正值代表扩大横向，负值代表缩小横向
 * @param debug_mode 0：不进行打印输出 1：第一轮TTR轨迹重叠打印 2：第二轮轨迹重叠 Pred_inpath信息打印
 * @return 是否在路径上
 */
bool PredictRelativeInfo::CheckGeometryInpath(const MotionStateAtTime &host_state, const ObsMotionInfo &obs_motion, const VehicleConfig &veh_config,
                                              float obs_length, float obs_width, float host_lgt_offs, float host_lat_offs,
                                              float obs_lat_offs, uint8_t debug_mode) {
    PredInpathFailReason pred_inpath_reason = PredInpathFailReason::NONE;
    return CheckGeometryInpath(host_state, obs_motion, veh_config, obs_length, obs_width, host_lgt_offs, host_lat_offs, obs_lat_offs, debug_mode, pred_inpath_reason);
}

bool PredictRelativeInfo::CheckGeometryInpath(const MotionStateAtTime &host_state, const ObsMotionInfo &obs_motion, const VehicleConfig &veh_config,
                                              float obs_length, float obs_width, float host_lgt_offs, float host_lat_offs,
                                              float obs_lat_offs, uint8_t debug_mode, PredInpathFailReason &fail_reason,
                                              PredInpathDebug *debug, float predict_time) {

    fail_reason = PredInpathFailReason::NONE;
    if (debug != nullptr) {
        debug->Reset();
    }

    float dx = obs_motion.motion.long_pos - host_state.long_pos;
    float dy = obs_motion.motion.lat_pos - host_state.lat_pos;

    float half_obs_length = 0.5F * obs_length;
    float half_obs_width  = 0.5F * obs_width;

    // ===== 条件1：自车坐标系下纵向检 =====
    // 目标纵向位置超出自车前方(front+安全包络)或在自车后方(rear)则不在路径内
    float host_rear_lgt_pos  = veh_config.k_dist_to_rear_axle - 1.0F;
    float host_front_lgt_pos = veh_config.k_dist_to_rear_axle + host_lgt_offs;
    if (obs_motion.rel_info.long_pos  >(host_front_lgt_pos + obs_motion.rel_info.safe_long_margin)||
        obs_motion.rel_info.long_pos  <host_rear_lgt_pos) {
        fail_reason = PredInpathFailReason::LGT_OUT_OF_RANGE;
        if (debug != nullptr) {
            debug->rel_lgt     = obs_motion.rel_info.long_pos;
            debug->front_limit = host_front_lgt_pos + obs_motion.rel_info.safe_long_margin;
            debug->rear_limit  = host_rear_lgt_pos;
        }
        if (debug_mode == 2) {
            std::cout << "[PredInpath] FAIL: lgt_check rel_lgt:" << obs_motion.rel_info.long_pos
                      << " front_limit:" << host_front_lgt_pos + obs_motion.rel_info.safe_long_margin
                      << "(front:" << host_front_lgt_pos << "+safe:" << obs_motion.rel_info.safe_long_margin
                      << ") rear_limit:" << host_rear_lgt_pos
                      << " host_vel:" << host_state.long_vel
                      << " predict_time:" << predict_time
                      << " obs_lgt_dist:" << obs_motion.rel_info.long_pos << std::endl;
        }else if(debug_mode == 1){
            std::cout << "[TTR_Cal] FAIL: lgt_check rel_lgt:" << obs_motion.rel_info.long_pos
                      << " front_limit:" << host_front_lgt_pos + obs_motion.rel_info.safe_long_margin
                      << "(front:" << host_front_lgt_pos << "+safe:" << obs_motion.rel_info.safe_long_margin
                      << ") rear_limit:" << host_rear_lgt_pos
                      << " host_vel:" << host_state.long_vel
                      << " predict_time:" << predict_time
                      << " obs_lgt_dist:" << obs_motion.rel_info.long_pos << std::endl;
        }
        return false;
    }

    // ===== 条件2：自车坐标系下横向检查 =====
    // 目标横向距离扣除自身包络后仍超出半车宽+offset则不在路径内
    float half_host_width = 0.5F * veh_config.k_host_width + host_lat_offs;
    float safe_lat        = fabs(obs_motion.rel_info.lat_pos) - obs_motion.rel_info.safe_lat_margin;
    if (safe_lat > half_host_width) {
        fail_reason = PredInpathFailReason::LAT_OUT_OF_RANGE;
        if (debug != nullptr) {
            debug->safe_lat        = safe_lat;
            debug->half_host_width = half_host_width;
        }
        if (debug_mode == 2) {
            std::cout << "[PredInpath] FAIL: lat_check safe_lat:" << safe_lat
                      << "(|lat_pos|:" << fabs(obs_motion.rel_info.lat_pos) << " - margin:" << obs_motion.rel_info.safe_lat_margin
                      << ") > half_host_w:" << half_host_width
                      << "(half_w:" << 0.5f * veh_config.k_host_width << " + offs:" << host_lat_offs << ")"
                      << " host_vel:" << host_state.long_vel
                      << " predict_time:" << predict_time
                      << " obs_lgt_dist:" << obs_motion.rel_info.long_pos << std::endl;
        }else if(debug_mode == 1){
            std::cout << "[TTR_Cal] FAIL: lat_check safe_lat:" << safe_lat
                      << "(|lat_pos|:" << fabs(obs_motion.rel_info.lat_pos) << " - margin:" << obs_motion.rel_info.safe_lat_margin
                      << ") > half_host_w:" << half_host_width
                      << "(half_w:" << 0.5f * veh_config.k_host_width << " + offs:" << host_lat_offs << ")"
                      << " host_vel:" << host_state.long_vel
                      << " predict_time:" << predict_time
                      << " obs_lgt_dist:" << obs_motion.rel_info.long_pos << std::endl;
        }
        return false;
    }

    // ===== 条件3：目标坐标系下纵向检查 =====
    // 将自车投影到目标坐标系，纵向投影超出自车包络+目标半长则不重叠
    float cos_b = cosf(obs_motion.motion.heading);
    float sin_b = sinf(obs_motion.motion.heading);
    float host_rel_obs_lgtpos = -cos_b * dx - sin_b * dy;
    float host_rel_obs_lgtsafe_space = obs_motion.rel_info.abs_cos_hdg * host_front_lgt_pos + obs_motion.rel_info.abs_sin_hdg * half_host_width;
    if (fabs(host_rel_obs_lgtpos) > host_rel_obs_lgtsafe_space + half_obs_length) {
        fail_reason = PredInpathFailReason::OBS_LGT_OUT_OF_RANGE;
        if (debug != nullptr) {
            debug->host_rel_obs_lgt   = fabs(host_rel_obs_lgtpos);
            debug->obs_lgt_safe_space = host_rel_obs_lgtsafe_space + half_obs_length;
        }
        if (debug_mode == 2) {
            std::cout << "[PredInpath] FAIL: obs_lgt_check |host_rel_lgt|:" << fabs(host_rel_obs_lgtpos)
                      << " > safe_space:" << host_rel_obs_lgtsafe_space + half_obs_length
                      << "(" << host_rel_obs_lgtsafe_space << " + half_obs_len:" << half_obs_length << ")"
                      << " host_vel:" << host_state.long_vel
                       << " predict_time:" << predict_time
                      << " obs_lgt_dist:" << obs_motion.rel_info.long_pos << std::endl;
        }else if(debug_mode == 1){
             std::cout << "[TTR] FAIL: obs_lgt_check |host_rel_lgt|:" << fabs(host_rel_obs_lgtpos)
                      << " > safe_space:" << host_rel_obs_lgtsafe_space + half_obs_length
                      << "(" << host_rel_obs_lgtsafe_space << " + half_obs_len:" << half_obs_length << ")"
                      << " host_vel:" << host_state.long_vel
                       << " predict_time:" << predict_time
                      << " obs_lgt_dist:" << obs_motion.rel_info.long_pos << std::endl;
        }
        return false;
    }

    // ===== 条件4：目标坐标系下横向检查 =====
    // 将自车投影到目标坐标系，横向投影超出自车包络+目标半宽+obs_width_offs则不重叠
    float host_rel_obs_latpos = sin_b * dx - cos_b * dy;
    float host_rel_obs_latsafe_space = obs_motion.rel_info.abs_sin_hdg * host_front_lgt_pos + obs_motion.rel_info.abs_cos_hdg * half_host_width;
    if (fabs(host_rel_obs_latpos) > host_rel_obs_latsafe_space + half_obs_width + obs_lat_offs) {
        fail_reason = PredInpathFailReason::OBS_LAT_OUT_OF_RANGE;
        if (debug != nullptr) {
            debug->host_rel_obs_lat   = fabs(host_rel_obs_latpos);
            debug->obs_lat_safe_space = host_rel_obs_latsafe_space + half_obs_width + obs_lat_offs;
        }
        if (debug_mode == 2) {
            
            std::cout << "[PredInpath] FAIL: obs_lat_check |host_rel_lat|:" << fabs(host_rel_obs_latpos)
                      << " > safe_space:" << host_rel_obs_latsafe_space + half_obs_width + obs_lat_offs
                      << "(" << host_rel_obs_latsafe_space << " + half_obs_w:" << half_obs_width
                      << " + obs_w_offs:" << obs_lat_offs << ")"
                      << " host_vel:" << host_state.long_vel
                       << " predict_time:" << predict_time
                      << " obs_lgt_dist:" << obs_motion.rel_info.long_pos << std::endl;
        }else if(debug_mode == 1){
            std::cout << "[TTR_Cal] FAIL: obs_lat_check |host_rel_lat|:" << fabs(host_rel_obs_latpos)
                      << " > safe_space:" << host_rel_obs_latsafe_space + half_obs_width + obs_lat_offs
                      << "(" << host_rel_obs_latsafe_space << " + half_obs_w:" << half_obs_width
                      << " + obs_w_offs:" << obs_lat_offs << ")"
                      << " host_vel:" << host_state.long_vel
                       << " predict_time:" << predict_time
                      << " obs_lgt_dist:" << obs_motion.rel_info.long_pos << std::endl;



        }
        return false;
    }

    if (debug_mode == 1) {
        std::cout << "[TTR_Cal] SUCCESS: geometry_inpath"
                  << " rel_lgt:" << obs_motion.rel_info.long_pos
                  << " rel_lat:" << obs_motion.rel_info.lat_pos
                  << " predict_time:" << predict_time
                  << " host_vel:" << host_state.long_vel << std::endl;
    }
    return true;
}

void PredictRelativeInfo::CalculateTTRAndTTP(MotionPredictInfo &pred_info) {
    bool get_ttr_first = false, get_ttp_fitst = false;

    pred_info.ttr = 100.F, pred_info.ttp = 100.F;
    pred_info.ttr_index = -1, pred_info.ttp_index = -1;
    pred_info.ttr_lat_overlap_rate = 0.0F;

    for (int idx = 1; idx < MAX_PREDICT_NUM; ++idx) {
        if ((pred_info.motion_info[idx - 1].rel_info.inpath == false)  &&  (pred_info.motion_info[idx].rel_info.inpath == true)  &&  !get_ttr_first) {
            pred_info.ttr       = 0.02F * static_cast<float>(idx);
            pred_info.ttr_index = idx;
            pred_info.ttr_lat_overlap_rate = pred_info.motion_info[idx].rel_info.lat_overlap_rate;
            get_ttr_first       = true;
        }

        if ((pred_info.motion_info[idx - 1].rel_info.inpath == true)  &&  (pred_info.motion_info[idx].rel_info.inpath == false)  &&  !get_ttp_fitst) {
            pred_info.ttp       = 0.02F * static_cast<float>(idx);
            pred_info.ttp_index = idx;
            get_ttp_fitst       = true;
        }

        if (get_ttr_first && get_ttp_fitst) {
            break;
        }
    }
    if (get_ttr_first && !get_ttp_fitst) {
        pred_info.ttp_index = MAX_PREDICT_NUM - 1;
        pred_info.ttp       = static_cast<float>(pred_info.ttp_index) * 0.02F;
    }
}

} // namespace longsafe
} // namespace active_safety
