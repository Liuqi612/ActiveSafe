#include "driver_evaluator.h"

#include "math/utils/util_math.h"

namespace active_safety {
namespace longsafe {

DriverEvaluator::DriverEvaluator() : accel_delay_(4) {
}
DriverEvaluator::~DriverEvaluator() = default;

void DriverEvaluator::Run(const AsVseOut &vse_out, const LongSafeObject &obs) {
    //   drvr_mode_analysis_.Run();
    CalcMotionLimit(vse_out);
    CheckDriverBehaviorEvaluator(vse_out, obs);
}
void DriverEvaluator::CalcMotionLimit(const AsVseOut &vse_out) {
    CalcCompensationFactor(vse_out);
    MaxLatJerkAndAccelEstimed(vse_out);
    MinLongAccelEstimed(vse_out);
    LongPositiveAccEstimed(vse_out.brake_pedal_apld);
}

void DriverEvaluator::CheckDriverBehaviorEvaluator(const AsVseOut &vse_out, const LongSafeObject &obs) {

    CheckDriverDecelerating(vse_out);
    CheckDriverBraking(vse_out);
    CheckDriverAccelerating(vse_out, obs);
    CheckDriverSteer(vse_out);
}

void DriverEvaluator::CheckDriverDecelerating(const AsVseOut &vse_out) {

    drvr_actv_sts_.drvr_decel = vse_out.brake_pedal_apld && vse_out.long_accel < drvr_cal_.k_algt_lim_for_drvr_decel;
}

void DriverEvaluator::CheckDriverBraking(const AsVseOut &vse_out) {

    drvr_actv_sts_.drvr_braking = vse_out.brake_pedal_apld;
}

void DriverEvaluator::CheckDriverAccelerating(const AsVseOut &vse_out, const LongSafeObject &obs) {

    bool drvr_accel = vse_out.long_accel > drvr_cal_.k_algt_lim_for_drvr_accel && vse_out.gas_pedal_pos > drvr_cal_.k_acc_pose_lim_for_drvr_accel &&
        !vse_out.long_ctrl_brake_active;

    drvr_actv_sts_.drvr_accelerating = drvr_accel_.offDelay(drvr_accel, drvr_cal_.k_drvr_accel_delay_ti, LGSF_FUNC_TIME_STEP) &&
        obs.long_accel > drvr_cal_.k_tar_brake_hard_lim_algt_lim;
}

void DriverEvaluator::CheckDriverSteer(const AsVseOut &vse_out) {
    if (fabs(vse_out.yawrate) > 0.1F) {
        drvr_actv_sts_.drvr_steer = false;
        drvr_actv_sts_.drvr_steer_fast = false;
    }
    (void)drvr_steer_angle_relay_.process(fabs(vse_out.steerwheelangle), drvr_cal_.k_drvr_str_ang_up, drvr_cal_.k_drvr_str_ang_low, true, false);
    drvr_actv_sts_.drvr_steer =
        drvr_steer_angle_offdly.offDelay(drvr_steer_angle_relay_.getOutput(), drvr_cal_.k_drvr_str_hold_time, LGSF_FUNC_TIME_STEP);

    (void)drvr_steer_angle_fast_relay_.process(fabs(vse_out.steerwheelangle_rate), drvr_cal_.k_drvr_str_ang_fast_up, drvr_cal_.k_drvr_str_ang_fast_low,
                                         true, false);
    drvr_actv_sts_.drvr_steer_fast =
        drvr_steer_angle_fast_offdly.offDelay(drvr_steer_angle_fast_relay_.getOutput(), drvr_cal_.k_drvr_str_fast_hold_time, LGSF_FUNC_TIME_STEP);
}

void DriverEvaluator::CalcCompensationFactor(const AsVseOut &vse_out) {
    motion_factor_.frct_and_mass_factor = 1.00F;

    // SelectIndividualActiveFactors
    contributing_factors_[0] = false;
    contributing_factors_[1] = (drvr_tran_mode == OvtkTgt);
    contributing_factors_[2] = drvr_actv_sts_.city_driving;
    contributing_factors_[3] = false;
    contributing_factors_[4] = false;

    // check predict strang
    float prd_tm = drvr_cal_.k_steer_wheel_angle_hold_time;
    float prd_ang = prd_tm * vse_out.steerwheelangle_rate + vse_out.steerwheelangle;
    contributing_factors_[5] = fabs(prd_ang) > drvr_cal_.k_high_steer_wheel_angle;

    // check fcw snvty.
    contributing_factors_[6] = (vse_out.fcw_warn_dist == 2);
    contributing_factors_[7] = (vse_out.fcw_warn_dist == 0);

    // check target has braked.
    contributing_factors_[8] = false;

    // check driver aggressive.
    contributing_factors_[9] = false;

    // Override Non Compatible Factors.
    for (std::size_t i = 0; i < drvr_cal_.k_comp_ovrd_matrix.size(); ++i) {
        for (std::size_t j = 0; j < drvr_cal_.k_comp_ovrd_matrix[0].size(); ++j) {
            if (drvr_cal_.k_comp_ovrd_matrix[i][j] && contributing_factors_[i]) {
                contributing_factors_[j] = false;
            }
        }
    }

    // Combine Compensation Factor
    motion_factor_.cmft_lat_comp_factor = drvr_cal_.k_turn_value_defaut_for_cmp;
    motion_factor_.crit_lat_comp_factor = drvr_cal_.k_turn_value_defaut_for_cmp;
    motion_factor_.cmft_long_comp_factor = drvr_cal_.k_turn_value_defaut_for_cmp;
    for (std::size_t i = 0; i < INDIVIDUAL_ACTIVE_ARRAY_SIZE; ++i) {
        motion_factor_.cmft_lat_comp_factor += drvr_cal_.k_turn_value_cmp_a_lat_cmft[i] * contributing_factors_[i];
        motion_factor_.crit_lat_comp_factor += drvr_cal_.k_turn_value_cmp_a_lat_crit[i] * contributing_factors_[i];
        motion_factor_.cmft_long_comp_factor += drvr_cal_.k_turn_value_cmp_a_lgt_cmft[i] * contributing_factors_[i];
    }
}

void DriverEvaluator::MaxLatJerkAndAccelEstimed(const AsVseOut &vse_out) {
    //   CalcCurvatureToSteerWheel
    float curvature_to_steering_angle_fac = std::pow(vse_out.speed, 2.0F) * vse_out.config.k_steer_gradient + vse_out.config.k_wheel_base;

    curvature_to_steering_wheel_coeffcient_ = curvature_to_steering_angle_fac * vse_out.config.k_steer_ratio;

    // ConvertStrLimtToAccAndCrvtLimtCrit
    motion_limit_.max_abs_lat_jerk = drvr_cal_.k_jerk_lateral_absolute_critical;
    motion_limit_.max_abs_lat_accel = drvr_cal_.k_accel_lateral_absolute_critical;

    float squard_speed = std::pow(vse_out.speed, 2.0F);

    float curvature_rate_from_lat_accel = math::SafeDivide(drvr_cal_.k_jerk_lateral_absolute_critical, squard_speed);
    float curvature_rate_from_strwhlrate = math::SafeDivide(drvr_cal_.k_max_steer_wheel_angle_rate_critical, curvature_to_steering_wheel_coeffcient_);
    motion_limit_.max_abs_crvt_rate = std::min(curvature_rate_from_lat_accel, curvature_rate_from_strwhlrate) * motion_factor_.crit_lat_comp_factor;
    motion_limit_.max_abs_crvt_rate = math::Clamp(motion_limit_.max_abs_crvt_rate, 0.0, drvr_cal_.k_max_abs_curvate_rate);

    float curvature_from_lat_accel = math::SafeDivide(drvr_cal_.k_accel_lateral_absolute_critical, squard_speed);
    float curvature_from_strwhl = math::SafeDivide(drvr_cal_.k_max_steer_wheel_angle_critical, curvature_to_steering_wheel_coeffcient_);
    motion_limit_.max_abs_crvt = std::min(curvature_from_lat_accel, curvature_from_strwhl) * motion_factor_.crit_lat_comp_factor;
    motion_limit_.max_abs_crvt = math::Clamp(motion_limit_.max_abs_crvt, 0.0, drvr_cal_.k_max_abs_curvate_rate);

    // ConvertStrLimtToAccAndCrvtLimtCmft
    motion_limit_.cmft_abs_lat_jerk = drvr_cal_.k_jerk_lateral_absolute_comfort;
    motion_limit_.cmft_abs_lat_accel = drvr_cal_.k_accel_lateral_absolute_comfort;

    curvature_rate_from_lat_accel = math::SafeDivide(drvr_cal_.k_jerk_lateral_absolute_comfort, squard_speed);
    curvature_rate_from_strwhlrate = math::SafeDivide(drvr_cal_.k_max_steer_wheel_angle_rate_comfort, curvature_to_steering_wheel_coeffcient_);
    motion_limit_.cmft_abs_crvt_rate = std::min(curvature_rate_from_lat_accel, curvature_rate_from_strwhlrate) * motion_factor_.crit_lat_comp_factor;
    motion_limit_.cmft_abs_crvt_rate = math::Clamp(motion_limit_.cmft_abs_crvt_rate, 0.0, drvr_cal_.k_max_abs_curvate_rate);

    curvature_from_lat_accel = math::SafeDivide(drvr_cal_.k_accel_lateral_absolute_comfort, squard_speed);
    curvature_from_strwhl = math::SafeDivide(drvr_cal_.k_max_steer_wheel_angle_comfort, curvature_to_steering_wheel_coeffcient_);
    motion_limit_.cmft_abs_crvt = std::min(curvature_from_lat_accel, curvature_from_strwhl) * motion_factor_.crit_lat_comp_factor;
    motion_limit_.cmft_abs_crvt = math::Clamp(motion_limit_.cmft_abs_crvt, 0.0, drvr_cal_.k_max_abs_curvate_rate);
}

void DriverEvaluator::MinLongAccelEstimed(const AsVseOut &vse_out) {
    // JerkLongNegEstimed
    float host_accel = math::Clamp(vse_out.long_accel, -m_inf, 0.0F);

    float delta_accel = host_accel - accel_delay_.get_frame(3);
    float jerk_estimed = delta_accel / (4 * drvr_cal_.k_period_time);
    accel_delay_.push(host_accel);

    jerk_estimed = fminf(jerk_estimed, drvr_cal_.k_max_jerk_negative);
    jerk_estimed = fminf(jerk_estimed, jerk_meas_neg_k1_);
    jerk_meas_neg_k1_ = jerk_estimed * sqrtf(drvr_cal_.k_a_lgt_half_life);

    motion_limit_.long_jerk_measd = jerk_estimed;

    // AccelLongNegEstimed
    float accel_neg_meas = fminf(vse_out.long_accel, drvr_cal_.k_max_long_acc_negative);
    accel_neg_meas = fminf(accel_neg_meas, longacc_meas_neg_k1_);
    longacc_meas_neg_k1_ = accel_neg_meas * sqrtf(drvr_cal_.k_a_lgt_half_life);

    motion_limit_.long_neg_accel_measd = accel_neg_meas;

    // EstimedMinNegAccJerk
    motion_limit_.min_long_neg_jerk = motion_factor_.frct_and_mass_factor > drvr_cal_.k_jerk_dec_thres_during_fric
        ? drvr_cal_.k_jerk_neg_min
        : drvr_cal_.k_jerk_neg_min * drvr_cal_.k_jerk_neg_min_gain;

    motion_limit_.min_long_neg_accel = fminf(drvr_cal_.k_min_long_neg_accel, motion_factor_.frct_and_mass_factor * drvr_cal_.k_gravity_accel);

    // ComfortLongAccel
    // 1.calculate predict driver deceleration
    float predict_drvr_decel = 0.0;
    if (drvr_actv_sts_.city_driving) {
        switch (vse_out.fcw_warn_dist) {
            case 1: // normal
                predict_drvr_decel = drvr_cal_.k_predict_default_drvr_decel;
                break;

            case 2: // close
                predict_drvr_decel = drvr_cal_.k_predict_low_drvr_decel;
                break;

            case 3: // far
                predict_drvr_decel = drvr_cal_.k_predict_high_drvr_decel;
                break;

            default:
                predict_drvr_decel = drvr_cal_.k_predict_default_drvr_decel;
                break;
        }
    } else {
        switch (vse_out.fcw_warn_dist) {
            case 1: // normal
                predict_drvr_decel = CalcPredDrvrDecel(vse_out.speed, drvr_cal_.k_predict_default_slop, drvr_cal_.k_predict_default_offset,
                                                       drvr_cal_.k_predict_default_limit);
                break;

            case 2: // close
                predict_drvr_decel =
                    CalcPredDrvrDecel(vse_out.speed, drvr_cal_.k_predict_low_slop, drvr_cal_.k_predict_low_offset, drvr_cal_.k_predict_low_limit);
                break;

            case 3: // far
                predict_drvr_decel =
                    CalcPredDrvrDecel(vse_out.speed, drvr_cal_.k_predict_high_slop, drvr_cal_.k_predict_high_offset, drvr_cal_.k_predict_high_limit);
                break;

            default:
                predict_drvr_decel = CalcPredDrvrDecel(vse_out.speed, drvr_cal_.k_predict_default_slop, drvr_cal_.k_predict_default_offset,
                                                       drvr_cal_.k_predict_default_limit);
                break;
        }
    }
    // 2.comfort negative long accel.
    float comp_factor = 1.0F;
    motion_limit_.cmft_long_neg_accel = predict_drvr_decel * math::Clamp(comp_factor * motion_factor_.frct_and_mass_factor, 0.3, 1.3);
}

float DriverEvaluator::CalcPredDrvrDecel(float host_speed, float slope, float offset, float predict_accel_limit) {
    return fmaxf(drvr_cal_.k_gravity_accel * (host_speed * slope + offset), predict_accel_limit);
}

void DriverEvaluator::LongPositiveAccEstimed(bool brake_pedal_apld) {
    if (brake_pedal_apld) {
        motion_limit_.cmft_long_pos_accel = drvr_cal_.k_a_lgt_pos_brak_cmft;
        motion_limit_.max_long_pos_accel = drvr_cal_.k_a_lgt_pos_brak;
    } else {
        motion_limit_.cmft_long_pos_accel = drvr_cal_.k_a_lgt_pos_no_brak_cmft;
        motion_limit_.max_long_pos_accel = drvr_cal_.k_a_lgt_pos_no_brak;
    }
    motion_limit_.max_long_pos_jerk = drvr_cal_.k_jerk_pos_max;
    motion_limit_.cmft_long_pos_jerk = drvr_cal_.k_jerk_pos_max;
}

} // namespace longsafe
} // namespace active_safety