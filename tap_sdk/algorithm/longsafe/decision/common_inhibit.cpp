#include "common_inhibit.h"

namespace active_safety {
namespace longsafe {

CommonInhibit::CommonInhibit() {
}
CommonInhibit::~CommonInhibit() = default;

void CommonInhibit::Update(const AsVseOut &vse_out, const LongSafeObject &obs, const ThreatAssessor &threat_assessor) {

    SpdInhibit(obs, vse_out);
    HostAvoidInhibit(vse_out, threat_assessor);
    LtapInhibit(obs, vse_out);
    CheckInPathAgeInhibit(obs);
    inhibit_res_ = (ltap_inhibit_flag_ || spd_inhibit_ || host_avoid_inhibit_ || inpath_age_inhibit_);
};

void CommonInhibit::SpdInhibit(const LongSafeObject &obs, const AsVseOut &vse_out) {

    float ego_speed = vse_out.speed;
    float pred_spd  = ego_speed + math::Clamp(obs.ttr, 0.0F, 1.3F) * vse_out.long_accel;
    if (((ego_speed < common_inhibit_cal_.k_min_spd_inhibit) && (pred_spd < common_inhibit_cal_.k_pred_min_spd_inhibit)) || (ego_speed < 0.0F)) {
        spd_inhibit_ = true;
    } else {
        spd_inhibit_ = false;
    }
}

void CommonInhibit::HostAvoidInhibit(const AsVseOut &vse_out, const ThreatAssessor &threat_assessor) {

    // 评估驾驶员制动达到避撞
    //    bool brake_avoid_collision = vse_out.long_accel < threat_assessor.rqrd_neg_lgt_accel_ * common_inhibit_cal_.k_neg_lgt_factor;
    bool brake_avoid_collision = false;

    // 评估驾驶员转向达到避撞
    //    float ego_alat  = vse_out.lat_accel;
    //    float squre_spd = vse_out.speed * vse_out.speed;

    //    float left_need_ego_alat        = threat_assessor.rqrd_left_crvt_ * squre_spd;
    //    bool  turn_left_avoid_collision = (left_need_ego_alat - ego_alat) < common_inhibit_cal_.k_turn_allowed_alat_thrd;
    bool turn_left_avoid_collision = false;

    //    float right_need_ego_alat        = threat_assessor.rqrd_right_crvt_ * squre_spd;
    //    bool  turn_right_avoid_collision = (right_need_ego_alat - ego_alat) > -1 * common_inhibit_cal_.k_turn_allowed_alat_thrd;
    bool turn_right_avoid_collision = false;

    //     需引入单独计算的Alat alat_enough = fabs(alat) < k_turn_allowed_alat_thrd
    //    (turn_left_avoid_collision || turn_right_avoid_collision)&&need_alat
    //        bool alat_enough = false;

    host_avoid_inhibit_ = brake_avoid_collision || turn_left_avoid_collision || turn_right_avoid_collision;
}

void CommonInhibit::CheckInPathAgeInhibit(const LongSafeObject &obs) {
    static int32_t last_obs_id = 0;
    if ((obs.fus_trkID > 0)  &&  (last_obs_id == obs.fus_trkID)) {
        inpath_age_ = std::min(++inpath_age_, 255);

    } else {
        inpath_age_ = 0;
    }
    last_obs_id          = obs.fus_trkID;
    int inpath_age_thres = 2;
    if (obs.man_type & ObsMotionMantype::CROSS_LEAN_TO_STRAIGHT_BY_SPD) {
        inpath_age_thres += 5;
    }

    inpath_age_inhibit_ = (inpath_age_ < inpath_age_thres);
}

void CommonInhibit::LtapInhibit(const LongSafeObject &obs, const AsVseOut &vse_out) {

    // 大曲率目标抑制
    ltap_inhibit_.target_high_curvature_inhibit = fabs(obs.curvature) > common_inhibit_cal_.k_target_high_crvt_thrd;

    // 检查目标head
    float integ_angle = CalcIntegAngle(vse_out);
    float target_head = atan2f(obs.lat_vel, obs.long_vel);

    float modify_angle_turn_start = fabs(math::MapAngToInterval(static_cast<float>(M_PI), target_head + integ_angle));

    ltap_inhibit_.target_heading_inhibit = modify_angle_turn_start < common_inhibit_cal_.k_oncoming_target_head_thrd;

    // 检查是否在S弯道
    CheckScurvature(vse_out);

    // 检查自车是否转弯      CCFT需要注意此处的阈值
    float curv_thd = math::LookUpTable::LookupTable1D<8>(common_inhibit_cal_.k_spd_crvt_str_move_to_self,
                                                         common_inhibit_cal_.k_crvt_to_str_move_to_self, vse_out.speed);

    ltap_inhibit_.no_turning_inhibit = fabsf(vse_out.rear_curvature) < curv_thd;

    // check ego recent no turn change
    bool  steer_spd_change  = false;
    float steer_whl_spd_thd = 0.0F;
    // check obj type for CCFtap optimization
    if (ObjectClass::CAR == obs.type) {
        steer_whl_spd_thd = common_inhibit_cal_.k_steer_ang_spd_thd_oncoming_veh;
    } else {
        steer_whl_spd_thd = common_inhibit_cal_.k_steer_ang_spd_thd_oncoming_vru;
    }

    if (fabsf(vse_out.steerwheelangle_rate) > steer_whl_spd_thd) {
        steer_spd_change = true;
    } else {
        steer_spd_change = false;
    }

    no_recent_turn_change_ = !(recent_turn_change_offdelay_.offDelay(steer_spd_change, common_inhibit_cal_.k_store_no_steer_change_duration,
                                                                     common_inhibit_cal_.k_ltap_inhibit_cycle_time));

    // check ego just started

    bool ego_stationary = false;
    if (fabs(vse_out.speed) < 0.1F) {
        ego_stationary = true;
    }

    ego_no_just_started_ = ego_just_started_.offDelay(ego_stationary, common_inhibit_cal_.k_store_no_steer_change_duration,
                                                      common_inhibit_cal_.k_ltap_inhibit_cycle_time);

    if (ego_no_just_started_ && no_recent_turn_change_) {
        ltap_inhibit_.not_tap_inhibit = true;
    } else {
        ltap_inhibit_.not_tap_inhibit = false;
    }

    // 掉头场景抑制
    CheckEgoTurnLongTime(vse_out);

    // unknow type

    if (obs.type == ObjectClass::UNIDENTIFIED_VEHICLE) {
        ltap_inhibit_.target_type_inhibit = true;
    } else {
        ltap_inhibit_.target_type_inhibit = false;
    }

    CheckTarOncoming(obs);

    if (target_oncoming_confirm_ && (ltap_inhibit_.target_high_curvature_inhibit || ltap_inhibit_.target_heading_inhibit ||
                                     ltap_inhibit_.recent_s_curvature_inhibit || ltap_inhibit_.no_turning_inhibit || ltap_inhibit_.not_tap_inhibit ||
                                     ltap_inhibit_.target_type_inhibit || ltap_inhibit_.ego_turning_longtime)) {
        ltap_inhibit_flag_ = true;
    } else {
        ltap_inhibit_flag_ = false;
    }
}
float CommonInhibit::CalcIntegAngle(const AsVseOut &vse_out) {
    float cur_yaw_rate = vse_out.speed * vse_out.rear_curvature;

    yaw_rate_sum_                         = yaw_rate_sum_ - yaw_rate_vector_[yaw_rate_vec_index_];
    yaw_rate_vector_[yaw_rate_vec_index_] = cur_yaw_rate * common_inhibit_cal_.k_ltap_inhibit_cycle_time;
    yaw_rate_sum_ += yaw_rate_vector_[yaw_rate_vec_index_];
    yaw_rate_vec_index_ += 1;

    if (yaw_rate_vec_index_ >= YAW_RATE_NUM) {
        yaw_rate_vec_index_ = 0;
    }

    return yaw_rate_sum_;
}
void CommonInhibit::CheckScurvature(const AsVseOut &vse_out) {
    bool is_curvature_left;
    bool is_curvature_right;

    if (last_curvature_left_ &&
        vse_out.rear_curvature > (common_inhibit_cal_.k_cruvature_thd_for_turn - common_inhibit_cal_.k_curvature_hysteretic_for_turn * 0.5)) {
        is_curvature_left = true;
    } else if ((!last_curvature_left_) && (vse_out.rear_curvature > (common_inhibit_cal_.k_cruvature_thd_for_turn +
                                                                     common_inhibit_cal_.k_curvature_hysteretic_for_turn * 0.5))) {
        is_curvature_left = true;
    }

    else {
        is_curvature_left = false;
    }

    if (last_curvature_right_ &&
        vse_out.rear_curvature < -(common_inhibit_cal_.k_cruvature_thd_for_turn - common_inhibit_cal_.k_curvature_hysteretic_for_turn * 0.5)) {
        is_curvature_right = true;
    } else if ((!last_curvature_right_) && (vse_out.rear_curvature < -(common_inhibit_cal_.k_cruvature_thd_for_turn +
                                                                       common_inhibit_cal_.k_curvature_hysteretic_for_turn * 0.5))) {
        is_curvature_right = true;
    }

    else {
        is_curvature_right = false;
    }

    bool curvature_exit_left = last_curvature_left_ && !is_curvature_left;
    bool curve_exit_right    = last_curvature_right_ && !is_curvature_right;

    if (curvature_exit_left) {
        last_curvature_exit_left = true;
    } else if (!curvature_exit_left && curve_exit_right) {
        last_curvature_exit_left = false;
    }

    bool s_curvature = (last_curvature_exit_left) ^ (vse_out.rear_curvature > 0.0);

    bool over_thd = false;
    if (fabsf(vse_out.rear_curvature) > common_inhibit_cal_.k_turn_for_oncoming_crvt_thd) {
        over_thd = true;
    } else {
        over_thd = false;
    }
    // check recent turn
    bool ego_recent_turn = false;
    bool ego_turning     = false;
    if (curvature_exit_left || curve_exit_right) {
        ego_turning = true;
    } else {
        ego_turning = false;
    }

    ego_recent_turn =
        ego_turning_offdelay_.offDelay(ego_turning, common_inhibit_cal_.k_curvature_exit_delay_time, common_inhibit_cal_.k_ltap_inhibit_cycle_time);

    bool recent_s_curvature;
    if ((s_curvature) && (over_thd) && (ego_recent_turn)) {
        recent_s_curvature = true;
    } else {
        recent_s_curvature = false;
    }

    ltap_inhibit_.recent_s_curvature_inhibit = s_curvature_offdelay_.offDelay(recent_s_curvature, common_inhibit_cal_.k_curvature_exit_delay_time,
                                                                              common_inhibit_cal_.k_ltap_inhibit_cycle_time);

    last_curvature_left_  = is_curvature_left;
    last_curvature_right_ = is_curvature_right;
}

void CommonInhibit::CheckEgoTurnLongTime(const AsVseOut &vse_out) {

    bool ego_turning_around            = (vse_out.speed < 5.0F) && (fabsf(vse_out.rear_curvature_radius) < 15.0F);
    bool ego_turn_around_confirm       = ego_turn_around_ondelay_.onDelay(ego_turning_around, common_inhibit_cal_.k_ego_turn_around_confim_ti,
                                                                    common_inhibit_cal_.k_ltap_inhibit_cycle_time);
    ltap_inhibit_.ego_turning_longtime = ego_turning_longtime_offdelay_.offDelay(
        ego_turn_around_confirm, common_inhibit_cal_.k_ego_turn_around_delay_ti, common_inhibit_cal_.k_ltap_inhibit_cycle_time);
}

void CommonInhibit::CheckTarOncoming(const LongSafeObject &obs) {
    bool speedmet = false;

    speedmet = sqrt(pow(obs.long_vel, 2) + pow(obs.lat_vel, 2)) > common_inhibit_cal_.k_target_oncoming_spd_thd;

    bool headmet = false;

    headmet = fabs(atan2(obs.lat_vel, obs.long_vel)) > common_inhibit_cal_.k_target_oncoming_angle_thd;

    bool non_bicycle_oncoming = (obs.type != ObjectClass::BICYCLE) && (obs.oncoming);

    bool bicycle_or_nonstationary = false;

    if (obs.type == ObjectClass::BICYCLE) {
        bicycle_or_nonstationary = true;

    } else if (!(obs.stationary)) {
        bicycle_or_nonstationary = true;
    } else {
        // do thing
    }
    target_oncoming_confirm_ = speedmet && (headmet || non_bicycle_oncoming) && bicycle_or_nonstationary;
}
} // namespace longsafe
} // namespace active_safety
