#include "rcw_function.h"

#include <cmath>

namespace active_safety {
namespace rcw {

void RcwFunction::RcwThreatEvaluator(const AsVseOut &vse_out, const GlobalConfig &config) {

    if (CheckObjectInfo(vse_out, m_rcw_tar)) {
        CrashProbSteerBrake(vse_out, m_rcw_tar);
    } else {
        ResetPersistant(m_rcw_tar);
    }

    Calculate_WarnLevel(vse_out);
}

void RcwFunction::CrashProbSteerBrake(const AsVseOut &vse_out, RcwObsData &obs_data) {

    float range_to_rear_bumper = (obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle + vse_out.config.k_host_length + obs_data.obs->length);

    float neededBrakeAcceleration =
        GetBrakeAccToAvoidRearEndColl(vse_out.long_accel, obs_data.obs->long_vel - vse_out.vcs_long_vel, range_to_rear_bumper);

    float ttc_thres_pcr = 0.0f;
    if (m_rcw_cal.k_rcw_enable_ttc_dependent_std_factor) {
        ttc_thres_pcr =
            m_rcw_cal.k_rcw_ttc_acute_alert / m_rcw_cal.k_rcw_thresh_velocity_long_for_ttc_max * (obs_data.obs->long_vel - vse_out.vcs_long_vel);
    }

    float effective_rel_lon_vel, effective_rel_lat_vel;
    if (m_rcw_cal.k_rcw_enable_heading_filter) {
        effective_rel_lon_vel = obs_data.effective_rel_vel.x;
        effective_rel_lat_vel = (obs_data.ttc < ttc_thres_pcr) ? (obs_data.obs->lat_vel - vse_out.vcs_lat_vel) : obs_data.effective_rel_vel.y;
    } else {
        effective_rel_lon_vel = obs_data.obs->long_vel - vse_out.vcs_long_vel;
        effective_rel_lat_vel = obs_data.obs->lat_vel - vse_out.vcs_lat_vel;
    }

    float neededSteeringAcceleration =
        GetSteerAccToAvoidRearEndColl(vse_out, obs_data, effective_rel_lon_vel, effective_rel_lat_vel, range_to_rear_bumper);

    obs_data.crash_prob_braking =
        math::LookUpTable::LookupTable1D<6>(m_rcw_cal.k_rcw_breakDecel, m_rcw_cal.k_rcw_PrBreakDecel, neededBrakeAcceleration);

    obs_data.crash_prob_steering =
        math::LookUpTable::LookupTable1D<6>(m_rcw_cal.k_rcw_steerAccel, m_rcw_cal.k_rcw_PrSteerAccel, neededSteeringAcceleration);

    obs_data.crash_prob_combined = fmin(obs_data.crash_prob_braking, obs_data.crash_prob_steering);

    if (obs_data.crash_prob_combined < m_rcw_cal.k_rcw_crash_prob_min) {
        obs_data.crash_prob_combined = 0.0f;
    }

    // 记录关键目标风险评估结果
    if (m_rcw_cal.k_rcw_debug_log_enable) {
        m_debug.target.crash_prob_braking = obs_data.crash_prob_braking;
        m_debug.target.crash_prob_steering = obs_data.crash_prob_steering;
        m_debug.target.crash_prob_combined = obs_data.crash_prob_combined;
    }
}

void RcwFunction::Calculate_TTC(const AsVseOut &vse_out, RcwObsData &obs_data) {
    obs_data.ttc = m_rcw_cal.k_rcw_default_ttc;

    // 计算自车后保险杠到目标前保险杠的距离（取绝对值）
    float lon_dist_rb_fb = obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle +
                               vse_out.config.k_host_length + 0.5f * obs_data.obs->length;

    float lon_rel_vel = obs_data.obs->long_vel - vse_out.vcs_long_vel;
    float lon_rel_acc = obs_data.obs->long_accel - vse_out.long_accel;

    const float latency = m_rcw_cal.k_rcw_AverageSensorLatency;

    // 最近点在自车后屁股前方
    if (lon_dist_rb_fb >= 0.0f) {
        return;
    }

    // 相对静止或后车速度低于自车
    if (fabs(lon_rel_vel) < m_rcw_cal.k_rcw_rel_vel_near_zero_thres || lon_rel_vel <= 0.0f) {
        return;
    }

    if (fabs(lon_rel_acc) < m_rcw_cal.k_rcw_rel_acc_near_zero_thres) {
        // 匀速接近，TTC = 距离 / 相对速度
        float ttc_linear = lon_dist_rb_fb / -lon_rel_vel;
        ttc_linear -= latency;
        obs_data.ttc = fmax(ttc_linear, 0.0f);
    } else {
        // 相对运动方程：0.5*a*t² + v*t + d = 0
        // 其中d是距离的绝对值，v是相对速度（正数，因为目标在靠近）
        float radicand = lon_rel_vel * lon_rel_vel - 2.0f * lon_rel_acc * (lon_dist_rb_fb);

        if (radicand >= 0.0f) {
            float sqrt_term = sqrtf(radicand);
            float sol1 = (-lon_rel_vel + sqrt_term) / lon_rel_acc;
            float sol2 = (-lon_rel_vel - sqrt_term) / lon_rel_acc;

            // TTC 取合理的正根
            float ttc_sol = m_rcw_cal.k_rcw_default_ttc;
            if (sol1 > 0 && sol2 > 0) {
                // 选择较小的正根
                ttc_sol = fmin(sol1, sol2);
            } else if (sol1 > 0) {
                ttc_sol = sol1;
            } else if (sol2 > 0) {
                ttc_sol = sol2;
            }

            ttc_sol -= latency;
            obs_data.ttc = fmax(ttc_sol, 0.0f);
        }
    }

    // 最终限幅
    obs_data.ttc = math::Clamp(obs_data.ttc, 0.0f, m_rcw_cal.k_rcw_default_ttc);
}

float RcwFunction::GetBrakeAccToAvoidRearEndColl(const float vcs_long_acc, float lon_rel_vel_obj, float lon_pos_bumper_obj) {
    float retVal = 0.0f;

    if ((lon_rel_vel_obj < 0.0f) || (lon_pos_bumper_obj > 0.0f)) {
        retVal = 0.0f;
    } else if (fabs(lon_pos_bumper_obj) < 0.001f) {
        retVal = m_rcw_cal.k_rcw_brake_acc_at_zero_dist;
    } else {
        retVal = (0.5f * (lon_rel_vel_obj * lon_rel_vel_obj) / lon_pos_bumper_obj) + vcs_long_acc;
    }

    return (-retVal);
}

float RcwFunction::GetSteerAccToAvoidRearEndColl(const AsVseOut &vse_out, RcwObsData &obs_data, float lon_rel_vel_obj, const float lat_rel_vel_obj,
                                                 float lon_pos_bumper_obj) {
    float lat_pos_front_object = obs_data.obs->lat_posn + std::sin(obs_data.obs->heading) * obs_data.obs->length;
    float lat_part_width_obj = 0.5f * std::cos(obs_data.obs->heading) * obs_data.obs->width;
    float corner_FL_obj = lat_pos_front_object + lat_part_width_obj;
    float corner_FR_obj = lat_pos_front_object - lat_part_width_obj;

    float retVal = 0.0f;
    float corner_lat_pos_RR_host = -0.5f * vse_out.config.k_host_width * m_rcw_cal.k_rcw_FactorEgoWidth;
    float corner_lat_pos_RL_host = 0.5f * vse_out.config.k_host_width * m_rcw_cal.k_rcw_FactorEgoWidth;

    if ((lon_rel_vel_obj < 0.0f) || (lon_pos_bumper_obj > 0.0f)) {
        retVal = 0.0f;
    } else if (fabs(lon_pos_bumper_obj) < 0.001f) {
        if ((corner_FL_obj < corner_lat_pos_RR_host) || (corner_FR_obj > corner_lat_pos_RL_host)) {
            retVal = 0.0f;
        } else {
            retVal = m_rcw_cal.k_rcw_steer_acc_at_zero_dist;
        }
    } else {
        float term2_left;
        float term2_right;
        float accLeft = 0.0f;
        float accRight = 0.0f;

        float pow2_reci_lon_pos_bumper_obj = 1.0f / (lon_pos_bumper_obj * lon_pos_bumper_obj);

        float term1 = 2.0f * lon_rel_vel_obj * lon_rel_vel_obj;
        float term2 = 2.0f * lon_rel_vel_obj * lon_pos_bumper_obj;

        term2_left = term2 * (-lat_rel_vel_obj);
        accLeft = ((((corner_FR_obj - corner_lat_pos_RL_host) * term1) + term2_left) * pow2_reci_lon_pos_bumper_obj) + vse_out.lat_accel;

        term2_right = term2 * (lat_rel_vel_obj);
        accRight = ((((corner_FL_obj - corner_lat_pos_RR_host) * term1) + term2_right) * pow2_reci_lon_pos_bumper_obj) + vse_out.lat_accel;

        retVal = fmin(std::abs(accLeft), std::abs(accRight));
    }

    return retVal;
}

void RcwFunction::Calculate_WarnLevel(const AsVseOut &vse_out) {

    m_rcw_active = {false,false};

    EvaluateTarBehavior();

    for (int i = 0; i < 2; i++) {

        float relative_speed = std::copysignf(sqrtf(std::pow(m_rcw_tar.obs->curvi_lat_vel_rel, 2) + powf(m_rcw_tar.obs->curvi_long_vel_rel, 2)),
                                              m_rcw_tar.obs->curvi_long_vel_rel);
        float warning_ttc_threshold =
            math::LookUpTable::LookupTable1D<5>(m_rcw_cal.k_rcw_RelVelocity, m_rcw_cal.k_rcw_warn_level[i].ttc_lookuptable, relative_speed);

        if (m_short_ttc_offdly.getStateOut()) {
            warning_ttc_threshold = fmax(warning_ttc_threshold - m_rcw_cal.k_rcw_short_ttc_thres_offset, 0);
        }

        if ((m_rcw_tar.ttc < warning_ttc_threshold) && (m_rcw_tar.ttc >= m_rcw_cal.k_rcw_warn_level[i].min_ttc_threshold) &&
            (m_rcw_tar.crash_prob_combined >= m_rcw_cal.k_rcw_warn_level[i].min_crash_prob)) {
            m_rcw_active[i] = true;
        }

        float warning_ttc_threshold_deactive =
            math::LookUpTable::LookupTable1D<5>(m_rcw_cal.k_rcw_RelVelocity, m_rcw_cal.k_rcw_ttc_lookuptable_deactive[i], relative_speed);

        if (m_rcw_out.state == RcwState::ACTIVE && m_rcw_tar.ttc > warning_ttc_threshold_deactive) {
            m_rcw_active[i] = false;
        }

        if (m_rcw_out.state != RcwState::ACTIVE && relative_speed <= m_rcw_cal.k_rcw_vel_rel_min) {
            m_rcw_active[i] = false;
        }

        if (m_rcw_out.state != RcwState::ACTIVE && vse_out.speed < m_rcw_cal.k_rcw_steerang_host_speed_max &&
            fabs(vse_out.steerwheelangle) >= m_rcw_cal.k_rcw_steerang_max) {
            m_rcw_active[i] = false;
        }

        // 记录本级 TTC/概率判据(与 m_rcw_active[i] 最终值一致)
        if (m_rcw_cal.k_rcw_debug_log_enable) {
            RcwLevelDebug &ld = m_debug.target.levels[i];
            ld.relative_speed = relative_speed;
            ld.ttc = m_rcw_tar.ttc;
            ld.warn_ttc_thres = warning_ttc_threshold;
            ld.min_ttc_thres = m_rcw_cal.k_rcw_warn_level[i].min_ttc_threshold;
            ld.crash_prob = m_rcw_tar.crash_prob_combined;
            ld.min_crash_prob = m_rcw_cal.k_rcw_warn_level[i].min_crash_prob;
            ld.warn_ttc_thres_deactive = warning_ttc_threshold_deactive;
            ld.active = m_rcw_active[i];
        }
    }

    // 记录关键目标概览量(路径/有效性/TTC)
    if (m_rcw_cal.k_rcw_debug_log_enable) {
        m_debug.target.is_valid = m_rcw_tar.is_valid;
        m_debug.target.is_inpath = m_rcw_tar.is_inpath;
        m_debug.target.is_current_inpath = m_rcw_tar.is_current_inpath;
        m_debug.target.is_pred_inpath = m_rcw_tar.is_pred_inpath;
        m_debug.target.ttc = m_rcw_tar.ttc;
        m_debug.target.crash_prob_combined = m_rcw_tar.crash_prob_combined;
    }
}

void RcwFunction::EvaluateTarBehavior() {
    // 1: check tar cross away
    bool is_tar_cross_away = false;
    is_tar_cross_away = fabs(m_rcw_tar.obs->lat_vel) > m_rcw_cal.k_rcw_cross_vlat_min;

    // 2: check tar decel
    bool is_tar_decel = false;
    is_tar_decel = m_rcw_tar.obs->long_accel < m_rcw_cal.k_rcw_decel_acccel_thres;

    // 3: check tar type
    bool is_not_motor_vehicle = false;
    is_not_motor_vehicle = !m_rcw_tar.obs->f_is_motor_vehicle;

    m_short_ttc_flag =  is_tar_cross_away || is_tar_decel || is_not_motor_vehicle;

    m_short_ttc_offdly.offDelay(m_short_ttc_flag, m_rcw_cal.k_rcw_short_ttc_offdly_time, m_rcw_cal.k_rcw_step_time);

}

} // namespace rcw
} // namespace active_safety
