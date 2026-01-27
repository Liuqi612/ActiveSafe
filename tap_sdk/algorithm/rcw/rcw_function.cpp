#include "rcw_function.h"

#include <algorithm>
#include <cmath>
#include <string.h>

namespace active_safety {
namespace rcw {

RcwFunction::RcwFunction() {
    Init();
}

RcwFunction::~RcwFunction() {
}

void RcwFunction::Init() {
    for (int i = 0; i < 2; i++) {
        debounce_counter_[i].hold                  = 255;
        debounce_counter_[i].suppress              = 0;
        debounce_counter_[i].warn_duration         = 0;
        debounce_counter_[i].was_active_last_cycle = false;
        is_warnlevel_active_[i]                    = false;
    }
}

void RcwFunction::Update(const AsVseOut &vse_out, const GlobalConfig &config, AsObstacleList &obs_list) {
    highest_critical_index = -1;
    for (std::size_t idx = 0; idx < kMaxNormalObject; ++idx) {
        obs_data_[idx].obs = obs_list[idx];

        if (IsValidObject(vse_out, obs_data_[idx]) == false) {
            ResetPersistant(obs_data_[idx]);
            continue;
        }

        CrashProbSteerBrake(vse_out, obs_data_[idx]);

        if (highest_critical_index == -1 || UpdateHighestCritObject(obs_data_[idx])) {
            highest_critical_index = idx;
        }
    }

    Calculate_WarnLevel();
    StateMachine(config, vse_out);
}

bool RcwFunction::IsValidObject(const AsVseOut &vse_out, RcwObsData &obs_data) {
    if (obs_data.obs->fus_trkID <= 0) {
        obs_data.f_need_clear_all = true;
        return false;
    }
    if (obs_data.obs->status != TrackStatus::COASTED && obs_data.obs->status != TrackStatus::UPDATED) {
        obs_data.f_need_clear_all = true;
        return false;
    }
    obs_data.f_need_clear_all = false;

    if (obs_data.age < 255) {
        obs_data.age += 1;
    }

    Is_Object_Permanent_Within_Ego_Lane(vse_out, obs_data);
    Calculate_TTC(vse_out, obs_data);
    Filter_Object_Heading(vse_out, obs_data);

    float maxApproachAngle = rcw_cal_.k_recw_MaxApproachAngle;
    float minRelativeSpeed = rcw_cal_.k_recw_MinRelativeSpeedPreCrash;
    if (obs_data.f_is_valid_obj_last_cycle) {
        maxApproachAngle += rcw_cal_.k_recw_MaxApproachAngleHysteresis;
        minRelativeSpeed -= rcw_cal_.k_recw_MinRelativeSpeedPreCrashHysteresis;
    }

    bool f_moving_obj   = (obs_data.obs->speed >= 0.5f);
    bool f_obj_counter  = (obs_data.age > rcw_cal_.k_recw_MinObjectAge);
    bool f_valid_length = (obs_data.obs->length > 1.0f);

    bool f_valid_heading = false;
    if (rcw_cal_.enable_heading_filter) {
        f_valid_heading = fabs(obs_data.filtered_heading) < maxApproachAngle;
    } else {
        f_valid_heading = fabs(obs_data.obs->heading) < maxApproachAngle;
    }

    float rel_vel_long               = obs_data.obs->long_vel - vse_out.vcs_long_vel;
    bool  f_valid_min_relative_speed = (rel_vel_long > minRelativeSpeed);
    bool  f_valid_max_relative_speed = (rel_vel_long < rcw_cal_.k_recw_MaxRelativeSpeedPreCrash);

    bool f_valid_longpos = (obs_data.obs->long_posn < 0);
    bool f_valid_latpos  = (fabsf(obs_data.obs->lat_posn) < 0.5f * vse_out.config.k_host_width);

    bool f_inline = obs_data.is_in_lane;
    if (obs_data.f_is_valid_obj_last_cycle) {
        f_inline = true;
    }
    f_inline = (f_inline || (rcw_cal_.k_recw_f_apply_lane_filter));

    bool f_valid_obj_width = (obs_data.obs->width < rcw_cal_.k_recw_max_object_width_warn_on);

    bool f_valid_x_relative_speed = (fabs(rel_vel_long - obs_data.effective_rel_vel.x) < rcw_cal_.k_max_allowed_rel_vel_long_diff);

    obs_data.f_is_valid_obj_last_cycle =
        (f_moving_obj && f_obj_counter && f_valid_length && f_valid_heading && f_valid_min_relative_speed && f_valid_max_relative_speed &&
         f_valid_longpos && f_inline && f_valid_obj_width && f_valid_x_relative_speed && f_valid_latpos);

    return obs_data.f_is_valid_obj_last_cycle;
}

void RcwFunction::Is_Object_Permanent_Within_Ego_Lane(const AsVseOut &vse_out, RcwObsData &obs_data) {
    obs_data.is_in_lane        = false;
    float curvi_lon_pos        = obs_data.obs->curvi_long_posn - vse_out.config.k_dist_to_rear_axle;
    float effective_lane_width = rcw_cal_.k_recw_lane_filter_width + (rcw_cal_.k_recw_lane_width_slope * fabs(curvi_lon_pos));

    if (fabs(obs_data.obs->lat_posn) < (0.5f * effective_lane_width)) {
        if (obs_data.object_within_lane_counter > rcw_cal_.k_recw_lane_filter_num_consecutive_cycles) {
            obs_data.is_in_lane = true;
        } else {
            obs_data.object_within_lane_counter++;
        }
    } else {
        obs_data.object_within_lane_counter = 0;
    }
}

void RcwFunction::Filter_Object_Heading(const AsVseOut &vse_out, RcwObsData &obs_data) {
    float filter_coeff;
    float diff_pos_x, diff_pos_y;

    obs_data.filtered_heading = obs_data.obs->heading;

    if (obs_data.last_object_pos.x < 100.0f) {
        diff_pos_x = obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle - obs_data.last_object_pos.x;
        diff_pos_y = obs_data.obs->lat_posn - obs_data.last_object_pos.y;

        if (obs_data.filter_counter < 8) {
            obs_data.filter_counter++;
        }

        filter_coeff = math::SafeDivide(1.0f, (float)obs_data.filter_counter);

        // Lowpass
        obs_data.filtered_diff_pos.x = (1.0f - filter_coeff) * obs_data.last_object_pos_filtered.x + (filter_coeff * diff_pos_x);
        obs_data.filtered_diff_pos.y = (1.0f - filter_coeff) * obs_data.last_object_pos_filtered.y + (filter_coeff * diff_pos_y);

        if (obs_data.filter_counter == 8 && rcw_cal_.enable_pos_diff_rel_vel) {
            obs_data.effective_rel_vel.x = obs_data.filtered_diff_pos.x / rcw_cal_.k_rcw_step_time;
            obs_data.effective_rel_vel.y = obs_data.filtered_diff_pos.y / rcw_cal_.k_rcw_step_time;

            if (obs_data.filtered_diff_pos.x > 1.0e-2) {
                obs_data.filtered_heading = std::atan2(obs_data.filtered_diff_pos.y, obs_data.filtered_diff_pos.x);
            }
        } else {
            obs_data.effective_rel_vel.x = obs_data.obs->long_vel - vse_out.vcs_long_vel;
            obs_data.effective_rel_vel.y = obs_data.obs->lat_vel - vse_out.vcs_lat_vel;
        }
    }

    obs_data.last_object_pos.x          = obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle;
    obs_data.last_object_pos.y          = obs_data.obs->lat_posn;
    obs_data.last_object_pos_filtered.x = obs_data.filtered_diff_pos.x;
    obs_data.last_object_pos_filtered.y = obs_data.filtered_diff_pos.y;
}

void RcwFunction::CrashProbSteerBrake(const AsVseOut &vse_out, RcwObsData &obs_data) {

    float lon_pos_bumper_obj   = obs_data.obs->long_posn + (0.5f * obs_data.obs->length);
    float range_to_rear_bumper = (obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle + vse_out.config.k_host_length + obs_data.obs->length);

    float neededBrakeAcceleration =
        GetBrakeAccToAvoidRearEndColl(vse_out.long_accel, obs_data.obs->long_vel - vse_out.vcs_long_vel, range_to_rear_bumper);

    float ttc_thres_pcr = 0.0f;
    if (rcw_cal_.enable_ttc_dependent_std_factor) {
        ttc_thres_pcr =
            rcw_cal_.k_recw_ttc_acute_alert / rcw_cal_.k_recw_thresh_velocity_long_for_max_ttc * (obs_data.obs->long_vel - vse_out.vcs_long_vel);
    }

    float effective_rel_lon_vel, effective_rel_lat_vel;
    if (rcw_cal_.enable_heading_filter) {
        effective_rel_lon_vel = obs_data.effective_rel_vel.x;
        effective_rel_lat_vel = (obs_data.ttc < ttc_thres_pcr) ? (obs_data.obs->lat_vel - vse_out.vcs_lat_vel) : obs_data.effective_rel_vel.y;
    } else {
        effective_rel_lon_vel = obs_data.obs->long_vel - vse_out.vcs_long_vel;
        effective_rel_lat_vel = obs_data.obs->lat_vel - vse_out.vcs_lat_vel;
    }

    float neededSteeringAcceleration =
        GetSteerAccToAvoidRearEndColl(vse_out, obs_data, effective_rel_lon_vel, effective_rel_lat_vel, range_to_rear_bumper);

    obs_data.crash_prob_braking  = math::LookUpTable::LookupTable2D<5, 6>(rcw_cal_.k_recw_BreakTrkAbsSpeed, rcw_cal_.k_recw_breakDecel,
                                                                         rcw_cal_.k_recw_PrBreakDecel, obs_data.obs->speed, neededBrakeAcceleration);
    obs_data.crash_prob_steering = math::LookUpTable::LookupTable2D<5, 6>(
        rcw_cal_.k_recw_SteerTrkAbsSpeed, rcw_cal_.k_recw_steerAccel, rcw_cal_.k_recw_PrSteerAccel, obs_data.obs->speed, neededSteeringAcceleration);

    obs_data.crash_prob_combined = fmin(obs_data.crash_prob_braking, obs_data.crash_prob_steering);

    if (obs_data.crash_prob_combined > rcw_cal_.k_recw_minCpDebouncingThres) {
        if (obs_data.consecutive_min_crash_prob_counter > rcw_cal_.k_recw_minNumberOfCpDebouncingCycles) {
            obs_data.consecutive_min_crash_prob_counter = 255;
        } else {
            obs_data.consecutive_min_crash_prob_counter++;
        }
    } else {
        obs_data.consecutive_min_crash_prob_counter = 0;
        obs_data.crash_prob_combined                = 0.0f;
    }
}

void RcwFunction::Calculate_TTC(const AsVseOut &vse_out, RcwObsData &obs_data) {
    obs_data.ttc = 25.5f;

    float lon_dist_rb_fb =
        obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle + vse_out.config.k_host_length + (0.5f * obs_data.obs->length);
    float lon_rel_vel = obs_data.obs->long_vel - vse_out.vcs_long_vel;
    float lon_rel_acc = obs_data.obs->long_accel - vse_out.long_accel;

    // 2. 如果相对加速度极小，使用线性模型
    if (fabs(lon_rel_acc) < 0.01f) {
        if (fabs(lon_rel_vel) < 0.001f) {
            // 特殊情况：如果距离已经非常近（0.5m内），视为立即碰撞
            if (lon_dist_rb_fb > -0.5f && lon_dist_rb_fb < 0.5f) {
                obs_data.ttc = 0.0f;
            } else {
                obs_data.ttc = 25.5f;
            }
        } else {
            // 线性 TTC = -d / v
            obs_data.ttc = -(lon_dist_rb_fb / lon_rel_vel) - rcw_cal_.k_recw_AverageSensorLatency;
        }
    } else {
        // 3. 使用二阶模型 (公式: 0.5*a*t^2 + v*t + d = 0)
        float radicand = (lon_rel_vel * lon_rel_vel) - (2.0f * lon_rel_acc * lon_dist_rb_fb);
        if (radicand < 0.0f) {
            obs_data.ttc = 25.5f; // 判别式小于0，物理上按当前加速度不相撞
        } else {
            float sqrt_term = sqrtf(radicand);
            float sol1      = (-lon_rel_vel + sqrt_term) / lon_rel_acc;
            float sol2      = (-lon_rel_vel - sqrt_term) / lon_rel_acc;

            // 选取合理的正根（最小的正数解）
            if (sol1 > 0.0f && sol2 > 0.0f) {
                obs_data.ttc = fmin(sol1, sol2) - rcw_cal_.k_recw_AverageSensorLatency;
            } else if (sol1 > 0.0f || sol2 > 0.0f) {
                obs_data.ttc = fmax(sol1, sol2) - rcw_cal_.k_recw_AverageSensorLatency;
            } else {
                obs_data.ttc = 25.5f;
            }
        }
    }

    obs_data.ttc = math::Clamp(obs_data.ttc, 0.0f, 25.5f);
}

float RcwFunction::GetBrakeAccToAvoidRearEndColl(const float vcs_long_acc, float lon_rel_vel_obj, float lon_pos_bumper_obj) {
    float retVal = 0.0f;

    if ((lon_rel_vel_obj < 0.0f) || (lon_pos_bumper_obj > 0.0f)) {
        retVal = 0.0f;
    } else if (fabs(lon_pos_bumper_obj) < 0.001f) {
        retVal = -20.0f;
    } else {
        retVal = (0.5f * (lon_rel_vel_obj * lon_rel_vel_obj) / lon_pos_bumper_obj) + vcs_long_acc;
    }

    return (-retVal);
}

float RcwFunction::GetSteerAccToAvoidRearEndColl(const AsVseOut &vse_out, RcwObsData &obs_data, float lon_rel_vel_obj, const float lat_rel_vel_obj,
                                                 float lon_pos_bumper_obj) {
    float lat_pos_front_object = obs_data.obs->lat_posn + std::sin(obs_data.obs->heading) * obs_data.obs->length;
    float lat_part_width_obj   = 0.5f * std::cos(obs_data.obs->heading) * obs_data.obs->width;
    float corner_FL_obj        = lat_pos_front_object + lat_part_width_obj;
    float corner_FR_obj        = lat_pos_front_object - lat_part_width_obj;

    float retVal                 = 0.0f;
    float corner_lat_pos_RR_host = -0.5f * vse_out.config.k_host_width * rcw_cal_.k_recw_FactorEgoWidth;
    float corner_lat_pos_RL_host = corner_lat_pos_RR_host;

    if ((lon_rel_vel_obj < 0.0f) || (lon_pos_bumper_obj > 0.0f)) {
        retVal = 0.0f;
    } else if (fabs(lon_pos_bumper_obj) < 0.001f) {
        if ((corner_FL_obj < corner_lat_pos_RR_host) || (corner_FR_obj > corner_lat_pos_RL_host)) {
            retVal = 0.0f;
        } else {
            retVal = -20.0f;
        }
    } else {
        float term2_left;
        float term2_right;
        float accLeft  = 0.0f;
        float accRight = 0.0f;

        float pow2_reci_lon_pos_bumper_obj = 1.0f / (lon_pos_bumper_obj * lon_pos_bumper_obj);

        float term1 = 2.0f * lon_rel_vel_obj * lon_rel_vel_obj;
        float term2 = 2.0f * lon_rel_vel_obj * lon_pos_bumper_obj;

        term2_left = term2 * (lat_rel_vel_obj);
        accLeft    = ((((corner_FR_obj - corner_lat_pos_RL_host) * term1) + term2_left) * pow2_reci_lon_pos_bumper_obj) + vse_out.lat_accel;

        term2_right = term2 * (lat_rel_vel_obj);
        accRight    = ((((corner_FL_obj - corner_lat_pos_RR_host) * term1) + term2_right) * pow2_reci_lon_pos_bumper_obj) + vse_out.lat_accel;

        retVal = fmin(std::abs(accLeft), std::abs(accRight));
    }

    return retVal;
}

bool RcwFunction::UpdateHighestCritObject(RcwObsData &obs_data) {
    const RcwObsData &highest_obs = obs_data_[highest_critical_index];
    if (obs_data.crash_prob_combined > highest_obs.crash_prob_combined) {
        return true;
    }
    if (fabs(obs_data.crash_prob_combined - highest_obs.crash_prob_combined) < m_eps) {
        if (obs_data.ttc < highest_obs.ttc && 0.0f < obs_data.ttc && 0.0f < highest_obs.ttc) {
            return true;
        }
    }
    return false;
}

void RcwFunction::Calculate_WarnLevel() {
    if (highest_critical_index < 0) {
        for (int i = 0; i < 2; i++) {
            debounce_counter_[i].hold                  = 255;
            debounce_counter_[i].suppress              = 0;
            debounce_counter_[i].warn_duration         = 0;
            debounce_counter_[i].was_active_last_cycle = false;
        }
        return;
    }
    const RcwObsData &obs_data = obs_data_[highest_critical_index];
    for (int i = 0; i < 2; i++) {
        bool should_trigger = false;

        float relative_speed = sqrtf(std::pow(obs_data.obs->curvi_lat_vel_rel, 2) + powf(obs_data.obs->curvi_long_vel_rel, 2));
        float warning_ttc_threshold =
            math::LookUpTable::LookupTable1D<5>(rcw_cal_.k_recw_RelVelocity, rcw_cal_.warn_level[i].ttc_lookuptable, relative_speed);

        if ((obs_data.ttc < warning_ttc_threshold) && (obs_data.ttc >= rcw_cal_.warn_level[i].min_ttc_threshold) &&
            ((obs_data.crash_prob_combined >= rcw_cal_.warn_level[i].min_crash_prob))) {
            should_trigger = true;
        }
        is_warnlevel_active_[i] = Handle_Warnlevel_Debounce_Counter(should_trigger, rcw_cal_.warn_level[i], debounce_counter_[i]);
    }
}

void RcwFunction::StateMachine(const GlobalConfig &config, const AsVseOut &vse_out) {
    memset(&rcw_out_, 0, sizeof(rcw_out_));

    // 报警时间限制和冷却时间逻辑
    bool is_active = (is_warnlevel_active_[0] || is_warnlevel_active_[1]);
    rcw_release_.signalRelease(is_active, rcw_cal_.k_rcw_alert_time_max, rcw_cal_.k_rcw_step_time);
    rcw_freezing_.featureFreezing(is_active, rcw_cal_.k_rcw_freezing_time, rcw_cal_.k_rcw_step_time);

    // 如果超过最长报警时间或在冷却期，抑制报警
    bool is_suppressed = rcw_release_.getSignalRelease() || rcw_freezing_.getfeatureFreezing();

    rcw_mode_cond_.state_off     = (vse_out.rcw_switch == 0);
    rcw_mode_cond_.state_fault   = false;
    rcw_mode_cond_.state_inhibit = (vse_out.speed > rcw_cal_.k_rcw_inhibit_speed || vse_out.actual_gear != 3);
    rcw_mode_cond_.state_active  = is_active && !is_suppressed;

    rcw_mode_cond_.off2inhibit     = !rcw_mode_cond_.state_off && !rcw_mode_cond_.state_fault;
    rcw_mode_cond_.fault2inhibit   = !rcw_mode_cond_.state_off && !rcw_mode_cond_.state_fault;
    rcw_mode_cond_.inhibit2standby = !rcw_mode_cond_.state_inhibit;
    rcw_mode_cond_.inhibit2active  = !rcw_mode_cond_.state_inhibit && rcw_mode_cond_.state_active;
    rcw_mode_cond_.standby2active  = !rcw_mode_cond_.state_inhibit && rcw_mode_cond_.state_active;
    rcw_mode_cond_.active2standby  = !rcw_mode_cond_.state_inhibit && !rcw_mode_cond_.state_active;

    rcw_mode_context_.setCondition(rcw_mode_cond_);
    rcw_mode_.update(rcw_mode_context_);

    if (highest_critical_index >= 0) {
        FillTargetInfo(obs_data_[highest_critical_index], rcw_out_.tgt_rcw);
    }
    switch (rcw_mode_.getCurrentSubState()) {
        case math::ModeState::OFF:
            rcw_out_.state = RcwState::OFF;
            break;
        case math::ModeState::FAULT:
            rcw_out_.state = RcwState::FAULT;
            break;
        case math::ModeState::INHIBIT:
            rcw_out_.state = RcwState::INHIBIT;
            break;
        case math::ModeState::STANDBY:
            rcw_out_.state = RcwState::STANDBY;
            break;
        case math::ModeState::ACTIVE:
            rcw_out_.rcw_collision_warn = OnOffStatus::Active;
            rcw_out_.state              = RcwState::ACTIVE;
            break;
        default:
            rcw_out_.state = RcwState::INHIBIT;
            break;
    }
    if (vse_out.rcw_switch) {
        rcw_out_.switch_req = 1;
    } else {
        rcw_out_.switch_req = 2;
    }
    if (config.k_use_shadowmode || !config.k_rcw_enable) {
        rcw_out_.rcw_collision_warn = OnOffStatus::NotActive;
    }
}

void RcwFunction::FillTargetInfo(const RcwObsData &obs_data, AsTargetInfo_T &tgt_info) {
    tgt_info.id      = obs_data.obs->fus_trkID;
    tgt_info.type    = static_cast<uint32_t>(obs_data.obs->object_class);
    tgt_info.source  = static_cast<uint32_t>(obs_data.obs->fusion_source);
    tgt_info.posx    = obs_data.obs->long_posn;
    tgt_info.posy    = obs_data.obs->lat_posn;
    tgt_info.spdx    = obs_data.obs->long_vel;
    tgt_info.spdy    = obs_data.obs->lat_vel;
    tgt_info.accelx  = obs_data.obs->long_accel;
    tgt_info.accely  = obs_data.obs->lat_accel;
    tgt_info.heading = obs_data.obs->heading;
    tgt_info.ttc     = obs_data.ttc;
}

void RcwFunction::ResetPersistant(RcwObsData &obs_data) {
    if (obs_data.f_need_clear_all) {
        obs_data.age = 0;
    }
    obs_data.f_is_valid_obj_last_cycle  = false;
    obs_data.object_within_lane_counter = 0;
    obs_data.ttc                        = 25.5f;
    obs_data.crash_prob_combined        = 0.0f;
    obs_data.is_in_lane                 = 0.0f;
    obs_data.filtered_heading           = 0.0f;
    obs_data.filtered_diff_pos.x        = 0.0f;
    obs_data.filtered_diff_pos.y        = 0.0f;
    obs_data.effective_rel_vel.x        = 0.0f;
    obs_data.effective_rel_vel.y        = 0.0f;
    obs_data.last_object_pos.x          = 0.0f;
    obs_data.last_object_pos.y          = 0.0f;
    obs_data.last_object_pos_filtered.x = 0.0f;
    obs_data.last_object_pos_filtered.y = 0.0f;
    obs_data.filter_counter             = 0;
}

bool RcwFunction::Handle_Warnlevel_Debounce_Counter(const bool should_warning_be_active, const RcwWarnLevel &warn_level,
                                                    RcwWarnDebounceCounter &debounce_counter) {
    bool         retValue   = false;
    RcwWarnState warn_state = WARNING_OFF;

    warn_state = Identify_Current_Warning_State(should_warning_be_active, debounce_counter.was_active_last_cycle);

    if (warn_state == WARNING_SUPPRESS) {
        retValue = Handle_Warn_State_Suppress(warn_level, debounce_counter);
    } else if (warn_state == WARNING_HOLD) {
        retValue = Handle_Warn_State_Hold(warn_level, debounce_counter);
    } else if (warn_state == WARNING_ON) {
        retValue = Handle_Warn_State_On(warn_level, debounce_counter);
    } else if (warn_state == WARNING_OFF) {
        retValue = Handle_Warn_State_Off(debounce_counter);
    } else {
        /*Do nothing*/
    }

#ifdef USING_RCW_TSEL_DEBUG
    AD_LERROR() << "warn_state:" << (int)warn_state << " should_warning_be_active:" << (int)should_warning_be_active;
    AD_LERROR() << "hold_cycles:" << (int)warn_level.hold_cycles << " suppress_cycles:" << (int)warn_level.suppress_cycles;
    AD_LERROR() << "retValue:" << (int)retValue;
#endif

    debounce_counter.was_active_last_cycle = retValue;

    return retValue;
}

RcwWarnState RcwFunction::Identify_Current_Warning_State(const bool should_warning_be_active, const bool was_active_last_cycle) {
    RcwWarnState warn_state = WARNING_OFF;

    if ((true == should_warning_be_active) && (false == was_active_last_cycle)) {
        warn_state = WARNING_SUPPRESS;
    } else if ((false == should_warning_be_active) && (true == was_active_last_cycle)) {
        warn_state = WARNING_HOLD;
    } else if ((true == should_warning_be_active) && (true == was_active_last_cycle)) {
        warn_state = WARNING_ON;
    } else if ((false == should_warning_be_active) && (false == was_active_last_cycle)) {
        warn_state = WARNING_OFF;
    } else {
        /*do nothing*/
    }

    return warn_state;
}

bool RcwFunction::Handle_Warn_State_Suppress(const RcwWarnLevel &warn_level, RcwWarnDebounceCounter &debounce_counter) {
    bool retValue;

    if (debounce_counter.suppress > warn_level.suppress_cycles) {
        retValue                  = true;
        debounce_counter.suppress = 255;
        debounce_counter.hold     = 0;
    } else {
        retValue = false;
        debounce_counter.suppress++;
    }

    return retValue;
}

bool RcwFunction::Handle_Warn_State_Hold(const RcwWarnLevel &warn_level, RcwWarnDebounceCounter &debounce_counter) {
    bool retValue;

    if (debounce_counter.hold > warn_level.hold_cycles) {
        retValue                  = false;
        debounce_counter.hold     = 255;
        debounce_counter.suppress = 0;
    } else {
        retValue = true;
        debounce_counter.hold++;
    }

    return retValue;
}

bool RcwFunction::Handle_Warn_State_On(const RcwWarnLevel &warn_level, RcwWarnDebounceCounter &debounce_counter) {
    bool retValue;

    debounce_counter.hold = 0;
    retValue              = !(Is_Max_Warn_Duration_Exceeded(warn_level, debounce_counter));

    return retValue;
}

bool RcwFunction::Is_Max_Warn_Duration_Exceeded(const RcwWarnLevel &warn_level, RcwWarnDebounceCounter &debounce_counter) {
    bool f_is_max_warn_duration_exceeded;

    if (debounce_counter.warn_duration > warn_level.max_warn_cycles) {
        f_is_max_warn_duration_exceeded = true;
        debounce_counter.warn_duration  = 255;
    } else {
        f_is_max_warn_duration_exceeded = false;
        debounce_counter.warn_duration++;
    }

    return f_is_max_warn_duration_exceeded;
}

bool RcwFunction::Handle_Warn_State_Off(RcwWarnDebounceCounter &debounce_counter) {
    bool retValue;

    debounce_counter.warn_duration = 0;
    debounce_counter.suppress      = 0;
    retValue                       = false;

    return retValue;
}
} // namespace rcw
} // namespace active_safety
