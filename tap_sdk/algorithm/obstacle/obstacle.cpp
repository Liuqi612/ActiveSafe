#include "obstacle.h"

#include "./math/utils/util_math.h"


#include "algorithm/longsafe/threat_assessor/motion_linear_predict.h"

#include <algorithm>
#include <climits>
#include <cmath>

namespace active_safety {

AsObstacle::AsObstacle() {
    //存储1s的数据
    fus_pos.set_size(50);
    fus_vel.set_size(50);
    fus_heading.set_size(50);
}

AsObstacle::~AsObstacle() = default;

AsObstacleCal AsObstacle::obj_param;

void AsObstacle::UpdateObstacle(const FusionObs &obs, const AsVseOut &vse_out, const ObsTimeComp &obs_time_comp,
                                const Eigen::Vector3f &delta_ego_last_cycle) {
    track_id = obs.track_id;
    age = obs.age;
    if (obs.fus_trkID != fus_trkID) {
        fus_pos.clear();
        fus_vel.clear();
        fus_heading.clear();
    }
    fus_trkID = obs.fus_trkID;
    vis_trkID = obs.vis_trkID;

    lat_posn = obs.lat_posn;
    long_posn = obs.long_posn;
    lat_vel = obs.lat_vel;
    long_vel = obs.long_vel;
    lat_accel_raw = obs.lat_accel;
    long_accel_raw = obs.long_accel;
    long_accel_raw = obs.long_accel;
    speed = obs.speed;
    long_accel = obs.long_accel;
    heading = obs.heading;
    heading_raw = obs.heading;
    confidence = obs.confidence;
    curvature = 0.0F;
    status = obs.status;
    object_class = obs.object_class;
    fusion_source = obs.fusion_source;
    length = obs.length;
    width = obs.width;
    height = obs.height;

    if (object_class == ObjectClass::PEDESTRIAN) {
        long_accel = 0.0F;
    }
    bool t_is_vru = ((object_class == ObjectClass::MOTORCYCLE) || (object_class == ObjectClass::ESCOOTER) || (object_class == ObjectClass::BICYCLE) ||
                     (object_class == ObjectClass::PEDESTRIAN));
    // Keep the legacy VRU noise filter, but retain measured lateral acceleration for other targets.
    lat_accel = t_is_vru ? 0.0F : obs.lat_accel;
    accel = sqrt(powf(obs.long_accel, 2.0F) + powf(obs.lat_accel, 2.0F));
    float m_a_temp = sqrtf(powf(obs.long_accel, 2.0) + powf(obs.lat_accel, 2.0));

    if (fabs(long_vel) > fabs(lat_vel)) {
        accel = long_vel < -1.5 ? -math::SignF(long_accel) * m_a_temp : math::SignF(long_accel) * m_a_temp;
    } else {
        accel = lat_vel < 1.5 ? -math::SignF(long_accel) * m_a_temp : math::SignF(long_accel) * m_a_temp;
    }

    if (speed <= 1.0) {
        motion_pattern = AS_OBS_MP_STATIONARY;
    } else {
        if ((fabs(heading) > 1.7F)  &&  (long_vel < -2.0F)) {
            motion_pattern = AS_OBS_MP_MOV_TO_SELF;
        } else {
            motion_pattern = AS_OBS_MP_MOV_FROM_SELF;
        }
    }

    if ((motion_pattern == AS_OBS_MP_STATIONARY)  &&  (object_class == ObjectClass::PEDESTRIAN)) {
        heading = 0.0F;
    }

    // 步骤1：使用帧间位移转换历史轨迹到当前自车坐标系
    if (fus_trkID != 0 &&
        (std::abs(delta_ego_last_cycle[0]) > 1e-6F || std::abs(delta_ego_last_cycle[1]) > 1e-6F || std::abs(delta_ego_last_cycle[2]) > 1e-6F)) {
        float cosAngle = std::cos(delta_ego_last_cycle[2]);
        float sinAngle = std::sin(delta_ego_last_cycle[2]);

        // 转换历史位置
        for (size_t i = 0; i < fus_pos.size(); ++i) {
            Point2D pos = fus_pos.get_frame(i);
            float d_long = cosAngle * pos.x + sinAngle * pos.y - delta_ego_last_cycle[0];
            float d_lat = -sinAngle * pos.x + cosAngle * pos.y - delta_ego_last_cycle[1];
            fus_pos.modify_frame(i, Point2D(d_long, d_lat));
        }

        // 转换历史速度
        for (size_t i = 0; i < fus_vel.size(); ++i) {
            Point2D vel = fus_vel.get_frame(i);
            float d_vx = cosAngle * vel.x + sinAngle * vel.y;
            float d_vy = -sinAngle * vel.x + cosAngle * vel.y;
            fus_vel.modify_frame(i, Point2D(d_vx, d_vy));
        }

        // 转换历史航向角（角度需要减去自车旋转角度并归一化到 [-π, π]）
        for (size_t i = 0; i < fus_heading.size(); ++i) {
            float hist_heading = fus_heading.get_frame(i);
            float transformed_heading =
                std::atan2(std::sin(hist_heading - delta_ego_last_cycle[2]), std::cos(hist_heading - delta_ego_last_cycle[2]));
            fus_heading.modify_frame(i, transformed_heading);
        }
    }

    // 步骤2：使用测量延时补偿处理当前点
    if ((object_class == ObjectClass::GENOBJ)  ||  (object_class == ObjectClass::GOD)) {
        PositionUpdateForLatency(obs_time_comp.gop_comp.delta_ego, obs_time_comp.gop_comp.delta_time, obs_time_comp.gop_comp.f_input_update);
    } else {
        PositionUpdateForLatency(obs_time_comp.fus_comp.delta_ego, obs_time_comp.fus_comp.delta_time, obs_time_comp.fus_comp.f_input_update);
    }

    ConvertVCSToCurvi(vse_out);
    CorrectAttributes();
}

void AsObstacle::CorrectAttributes() {
    CorrectObstacleType();
    CorrectObstacleCrvt();
    CheckTurning();
    CheckCrossDecel();
}

void AsObstacle::CorrectObstacleType() {
    float speed = sqrt(powf(long_vel, 2) + powf(lat_vel, 2));
    f_is_vehicle = false;
    f_is_bicycle = false;
    f_is_motor_vehicle = false;
    if ((object_class == ObjectClass::BICYCLE)  &&  (speed > 4.8)) {
        object_class = ObjectClass::ESCOOTER;
    }

    if ((object_class == ObjectClass::CAR)  ||  (object_class == ObjectClass::TRUCK)  ||  (object_class == ObjectClass::UNIDENTIFIED_VEHICLE)) {
        f_is_vehicle = true;
    }
    if (object_class == ObjectClass::CAR || object_class == ObjectClass::TRUCK || object_class == ObjectClass::UNIDENTIFIED_VEHICLE ||
        object_class == ObjectClass::MOTORCYCLE || object_class == ObjectClass::ESCOOTER) {
        f_is_motor_vehicle = true;
    }

    if ((object_class == ObjectClass::BICYCLE)  ||  (object_class == ObjectClass::MOTORCYCLE)  ||  (object_class == ObjectClass::ESCOOTER)) {
        f_is_bicycle = true;
    }
}

void AsObstacle::CheckTurning() {
    f_turning = false;

    const size_t min_history_size = 5;
    if (fus_heading.size() < min_history_size) {
        return;
    }

    if (speed < 0.5F) {
        return;
    }

    float min_heading = fus_heading.get_frame(0);
    float max_heading = min_heading;
    float sum_heading = min_heading;

    for (size_t i = 1; i < fus_heading.size(); ++i) {
        float h = fus_heading.get_frame(i);
        sum_heading += h;

        float diff_min = std::atan2(std::sin(h - min_heading), std::cos(h - min_heading));
        float diff_max = std::atan2(std::sin(h - max_heading), std::cos(h - max_heading));

        if (diff_min < 0.0F) {
            min_heading = h;
        }
        if (diff_max > 0.0F) {
            max_heading = h;
        }
    }
    float heading_range = std::atan2(std::sin(max_heading - min_heading), std::cos(max_heading - min_heading));
    heading_range = std::abs(heading_range);
    const float heading_range_threshold = 0.2F; // 约 11.5 度

    if (heading_range > heading_range_threshold) {
        f_turning = true;
    }
}

void AsObstacle::CheckCrossDecel() {
    f_obs_straight_cross = false;
    for (int i = 0; i < fus_heading.size() && i < 5; ++i) {
        if (fabs(fabs(fus_heading.get_frame(i)) - 1.57F) < 0.25F) {
            f_obs_straight_cross = true;
        } else {
            f_obs_straight_cross = false;
        }
    }
    //检查历史10帧的横向速度变化
    f_cross_decel = false;
    int compare_lat_vel_cnt = 0;
    for (int i = 1; i < fus_vel.size() && i < 10; ++i) {
        if (fabs(fus_vel.get_frame(i).y) - fabs(fus_vel.get_frame(i - 1).y) > m_eps) {
            compare_lat_vel_cnt++;
        } else {
            compare_lat_vel_cnt = std::max(compare_lat_vel_cnt - 1, 0);
        }
    }
    f_cross_decel = compare_lat_vel_cnt > 6;
}

void AsObstacle::CorrectObstacleCrvt() {
    float max_a_lat;
    switch (object_class) {
        case ObjectClass::MOTORCYCLE: {
            max_a_lat = obj_param.k_motorcycle_max_a_lgt;
            break;
        }
        case ObjectClass::TRUCK: {
            max_a_lat = obj_param.k_truck_max_a_lgt;
            break;
        }
        case ObjectClass::CAR: {
            max_a_lat = obj_param.k_car_max_a_lgt;
            break;
        }
        case ObjectClass::UNIDENTIFIED_VEHICLE: {
            max_a_lat = obj_param.k_veh_unkwn_type_max_a_lgt;
            break;
        }
        default: {
            max_a_lat = 0.0F;
            break;
        }
    }

    float sqrt_spd = speed * speed;
    float k_max_curv = math::SafeDivide(max_a_lat, sqrt_spd);
    if (k_max_curv > obj_param.k_max_value_for_self_dev) {
        k_max_curv = obj_param.k_max_value_for_self_dev;
    } else if (k_max_curv < -obj_param.k_max_value_for_self_dev) {
        k_max_curv = -obj_param.k_max_value_for_self_dev;
    } else {
    }

    if (k_max_curv > obj_param.k_max_curv) {
        k_max_curv = obj_param.k_max_curv;
    } else if (k_max_curv < -obj_param.k_max_curv) {
        k_max_curv = -obj_param.k_max_curv;
    } else {
    }

    k_max_curv = fabsf(k_max_curv);
    if (curvature > k_max_curv) {
        curvature = k_max_curv;
    } else if (curvature < -k_max_curv) {
        curvature = -k_max_curv;
    } else {
    }
}

void AsObstacle::PositionUpdateForLatency(Eigen::Vector3f deltaEgo, float deltaTm, bool f_input_update) {
    float deltaTm_sec = deltaTm * 0.001F;

    // 使用 longsafe 中的实现
    longsafe::MotionLinearPredict::LinearPredictWithStop(long_posn, long_vel, long_accel, deltaTm_sec, true);
    longsafe::MotionLinearPredict::LinearPredictWithStop(lat_posn, lat_vel, lat_accel, deltaTm_sec, true);

    // 步骤3：将当前点坐标转换到当前自车坐标系（测量延时补偿）
    float cosAngle = std::cos(deltaEgo[2]);
    float sinAngle = std::sin(deltaEgo[2]);
    float d_long_posn = cosAngle * long_posn + sinAngle * lat_posn - deltaEgo[0];
    lat_posn = -sinAngle * long_posn + cosAngle * lat_posn - deltaEgo[1];
    long_posn = d_long_posn;

    // 转换当前点速度到当前自车坐标系
    float d_long_vel = cosAngle * long_vel + sinAngle * lat_vel;
    lat_vel = -sinAngle * long_vel + cosAngle * lat_vel;
    long_vel = d_long_vel;

    // 转换当前点加速度到当前自车坐标系
    float d_long_accel = cosAngle * long_accel + sinAngle * lat_accel;
    lat_accel = -sinAngle * long_accel + cosAngle * lat_accel;
    long_accel = d_long_accel;

    // 转换当前点航向角到当前自车坐标系
    heading = std::atan2(std::sin(heading - deltaEgo[2]), std::cos(heading - deltaEgo[2]));

    // 步骤4：将转换后的当前点推入历史缓冲区
    if (fus_trkID == 0) {
        fus_pos.clear();
        fus_vel.clear();
        fus_heading.clear();
    } else {
        if (f_input_update  &&  (confidence == ObsConfidence::HIGH_CONF)) {
            fus_pos.push(Point2D(long_posn, lat_posn));
            fus_vel.push(Point2D(long_vel, lat_vel));
            fus_heading.push(heading);
        }
    }
}

void AsObstacle::ConvertVCSToCurvi(const AsVseOut &ego) {
    float rotated_x;
    float sign_rotated_x;
    float rotated_y;
    float abs_curvature;
    float posn_squared;
    float temp_posn;
    float r;
    float sign_r;
    float rhat;
    float x_squared;
    float rhat_squared;
    float temp;
    float num;
    float sign_num;
    float ratio;
    float atan_ratio;
    float alpha;
    float cos_alpha;
    float sin_alpha;
    uint8_t f_abs_curvature_LT_cal;
    // apply vcs to curvi if ego speed was below threshold.
    if (std::abs(ego.speed) < 10) {
        curvi_long_posn = long_posn;
        curvi_lat_posn = lat_posn;
        curvi_long_vel = long_vel;
        curvi_lat_vel = lat_vel;
        curvi_long_accel = long_accel;
        curvi_lat_accel = lat_accel;
        curvi_long_vel_rel = long_vel - ego.vcs_long_vel;
        curvi_lat_vel_rel = lat_vel - ego.vcs_lat_vel;
        curvi_heading = heading;
    } else {
        abs_curvature = std::abs(ego.rear_curvature);
        f_abs_curvature_LT_cal = (abs_curvature < 0.001); // 0.001
        /*% convert position based on host sideslip and curvature*/
        rotated_x = long_posn * std::cos(ego.vcs_sideslip) + lat_posn * std::sin(ego.vcs_sideslip);

        rotated_y = -long_posn * sin(ego.vcs_sideslip) + lat_posn * cos(ego.vcs_sideslip);
        if (f_abs_curvature_LT_cal) {
            /*% small curvature, use clothoid model*/
            posn_squared = long_posn * long_posn;
            temp_posn = 0.5F * ego.rear_curvature * posn_squared;
            curvi_long_posn = rotated_x;
            curvi_lat_posn = rotated_y - temp_posn;
        } else {
            /*% large curvature, use exact solution*/
            r = 1.0F / ego.rear_curvature;
            if (r == 0.0F) {
                sign_r = 0.0F;
            } else if (r < 0.0F) {
                sign_r = -1.0F;
            } else {
                sign_r = 1.0F;
            }

            rhat = r - rotated_y;
            /*temp = hypot(rotated_x,rhat); */
            x_squared = rotated_x * rotated_x;
            rhat_squared = rhat * rhat;
            temp = sqrtf(x_squared + rhat_squared);
            num = (temp - sign_r * rhat);
            if (num == 0) {
                sign_num = 0;
            } else if (num < 0) {
                sign_num = -1;
            } else {
                sign_num = 1;
            }

            if (rotated_x == 0) {
                sign_rotated_x = 0;
            } else if (rotated_x < 0) {
                sign_rotated_x = -1;
            } else {
                sign_rotated_x = 1;
            }

            if (fabsf(rotated_x) > 1e-7) {
                ratio = num / rotated_x;
                atan_ratio = atanf(ratio);
            } else if (sign_num == sign_rotated_x) {
                atan_ratio = m_pi;
            } else {
                atan_ratio = -m_pi;
            }
            curvi_long_posn = 2.0F * temp * atan_ratio;
            curvi_lat_posn = r - sign_r * temp;

        } /*end if */

        /*% convert velocity and acceleration based on tangent to curve at
         * target longitudinal coordinate*/
        alpha = curvi_long_posn * ego.rear_curvature;
        cos_alpha = cosf(alpha);
        sin_alpha = sinf(alpha);
        curvi_long_vel = cos_alpha * long_vel + sin_alpha * lat_vel;
        curvi_long_accel = cos_alpha * long_accel + sin_alpha * lat_accel;
        curvi_lat_vel = -sin_alpha * long_vel + cos_alpha * lat_vel;
        curvi_lat_accel = -sin_alpha * long_accel + cos_alpha * lat_accel;

        /*% compute relative velocities*/
        curvi_long_vel_rel = curvi_long_vel - ego.vcs_long_vel;
        curvi_lat_vel_rel = curvi_lat_vel - ego.vcs_lat_vel;

        /*% compute heading*/
        curvi_heading = heading - alpha;
    }
}

void AsObstacle::Clear() {
    track_id = 0;
    age = 0;
    fus_trkID = 0;
    vis_trkID = 0;
    lat_posn = 20.0F;
    long_posn = 200.0F;
    lat_vel = 0.0F;
    long_vel = 0.0F;
    lat_accel = 0.0F;
    long_accel = 0.0F;
    curvi_long_posn = 0.0F;
    curvi_lat_posn = 0.0F;
    curvi_long_vel = 0.0F;
    curvi_lat_vel = 0.0F;
    curvi_long_accel = 0.0F;
    curvi_lat_accel = 0.0F;
    curvi_long_vel_rel = 0.0F;
    curvi_lat_vel_rel = 0.0F;
    curvi_heading = 0.0F;
    speed = 0.0F;
    accel = 0.0F;
    heading = 0.0F;
    lat_accel_raw = 0.0F;
    long_accel_raw = 0.0F;
    heading_raw = 0.0F;
    confidence = ObsConfidence::LOW_CONF;
    curvature = 0.0F;
    length = 0.0F;
    width = 0.0F;
    height = 0.0F;
    f_is_vehicle = false;
    f_is_bicycle = false;

    fus_pos.clear();
    fus_vel.clear();
    fus_heading.clear();
    status = TrackStatus::INVALID;
    object_class = ObjectClass::UNDETERMINED;
    fusion_source = FusionSource::SRR_ONLY;
}

} // namespace active_safety
