/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#include "./vehicle_state_estimed.h"

namespace active_safety {

VehicleStateEstimed::VehicleStateEstimed() : curvature_filter_(2, 1), speed_filter_(1, 1, 1) {
}

void VehicleStateEstimed::Init() {
    //    memset(&vse_ipc_, 0, sizeof(AsVseOut));
    time_series.set_size(His_State_Num);
    yawrate_series.set_size(His_State_Num);
    rear_sideslip_series.set_size(His_State_Num);
    rear_curv_series.set_size(His_State_Num);
    rear_posx_series.set_size(His_State_Num);
    rear_posy_series.set_size(His_State_Num);
    speed_series.set_size(His_State_Num);
    heading_series.set_size(His_State_Num);
    time_series.clear();
    yawrate_series.clear();
    rear_sideslip_series.clear();
    rear_curv_series.clear();
    rear_posx_series.clear();
    rear_posy_series.clear();
    speed_series.clear();
    heading_series.clear();
    // 初始化曲率卡尔曼滤波器 (状态维度2，观测维度1)
    curvature_filter_ = math::KalmanFilter(2, 1);

    // 设置系统模型参数
    Eigen::Matrix2d F;       // 状态转移矩阵
    Eigen::Vector2d B;       // 控制输入矩阵
    Eigen::RowVector2d H;    // 观测矩阵
    Eigen::Matrix2d Q;       // 过程噪声协方差
    Eigen::MatrixXd R(1, 1); // 观测噪声协方差

    B << 0, 1;    // 控制输入影响
    H << 1, 0;    // 只能观测到第一个状态(曲率)
    Q << 0.01, 0, // 过程噪声
        0, 0.01;
    R << 0.1; // 观测噪声

    curvature_filter_.init(F, B, H, Q, R);

    // 初始状态和协方差
    Eigen::Vector2d x0;
    Eigen::Matrix2d P0;
    x0 << 0, 0;
    P0 << 1, 0, 0, 1;
    curvature_filter_.reset(x0, P0);

    // 初始化速度卡尔曼滤波器 (状态维度1：速度，观测维度1：速度，控制维度1：加速度)
    speed_filter_ = math::KalmanFilter(1, 1, 1);

    // 设置速度估计系统模型参数
    Eigen::MatrixXd F_speed(1, 1); // 状态转移矩阵 (速度保持不变，由加速度控制)
    Eigen::MatrixXd B_speed(1, 1); // 控制输入矩阵 (加速度影响速度)
    Eigen::MatrixXd H_speed(1, 1); // 观测矩阵 (直接观测速度)
    Eigen::MatrixXd Q_speed(1, 1); // 过程噪声协方差
    Eigen::MatrixXd R_speed(1, 1); // 观测噪声协方差

    F_speed << 1.0;                                   // 速度状态保持不变（由控制输入更新）
    B_speed << 1.0;                                   // 加速度直接影响速度变化
    H_speed << 1.0;                                   // 直接观测速度
    Q_speed << vse_cal_.k_speed_kalman_process_noise; // 过程噪声（速度估计的不确定性）
    R_speed << vse_cal_.k_speed_kalman_measure_noise; // 观测噪声（底盘速度测量的不确定性）

    speed_filter_.init(F_speed, B_speed, H_speed, Q_speed, R_speed);

    // 初始状态和协方差
    Eigen::VectorXd x0_speed(1);
    Eigen::MatrixXd P0_speed(1, 1);
    x0_speed << 0.0;
    P0_speed << 1.0;
    speed_filter_.reset(x0_speed, P0_speed);
}

void VehicleStateEstimed::Run(const VseInput &vse_input, uint64_t curtime, const GlobalConfig &config) {
    vse_ipc_.veh_time_stamp = curtime;
    curtime_ms_ = curtime / 1000000;
    vse_inport_ = vse_input;
    UpdateBcmAcuBcsInfo();
    UpdateSteerInfo();
    CalcLongVelocityAndAccel();
    if (config.k_Lgsf_ForOldRsclBag) {
        TransClusterSpeed();
    }
    CalcCurvatureAndSideSlip();
    CheckHostStraightDriving();
    CalcLatVelocityAndAccel();
    SeriesRecord();
    // TransClusterSpeed();
    prev_time_ = curtime_ms_;
}
void VehicleStateEstimed::UpdateSteerInfo() {
    vse_ipc_.steerwheelangle = vse_inport_.steer_wheel_angle;
    vse_ipc_.steerwheelangle_rate =
        math::LowPassFilter(vse_inport_.steer_wheel_angle_rate, vse_ipc_.steerwheelangle_rate, vse_cal_.k_steer_angle_rate_gain);
    vse_ipc_.yawrate = FilterYawRate(vse_inport_.master_imu_yawrate * m_pi / 180.0F);
}
void VehicleStateEstimed::CalcLongVelocityAndAccel() {
    float raw_speed = vse_inport_.esp_hosd_spd;
    vse_ipc_.long_accel = vse_inport_.master_imu_longaccel;
    vse_ipc_.display_speed  = vse_inport_.display_speed;
    vse_ipc_.display_speed = vse_ipc_.speed > 0.0F ? vse_ipc_.display_speed : (vse_ipc_.speed < 0.0F ? -vse_ipc_.display_speed : 0.0F);
    const bool is_reverse = (vse_ipc_.f_reverse_status || vse_ipc_.actual_gear == 1);
    const float signed_raw_speed = is_reverse ? -raw_speed : raw_speed;
    if ((curtime_ms_ > prev_time_)  &&  (prev_time_ > 0)) {
        uint64_t delta_t_ms = curtime_ms_ - prev_time_;
        float delta_t_s = static_cast<float>(delta_t_ms) / 1000.0F;
        float prev_speed = speed_series.get_frame(0);

        float predicted_speed_change = vse_ipc_.long_accel * delta_t_s;

        float speed_change_rate = (signed_raw_speed - prev_speed) / delta_t_s;
        bool speed_change_valid = fabs(speed_change_rate) <= vse_cal_.k_max_speed_change_rate;

        bool speed_accel_consistent = true;
        if (fabs(vse_ipc_.long_accel) > vse_cal_.k_speed_accel_consistency_thresh) {
            float speed_diff = signed_raw_speed - prev_speed;
            if ((vse_ipc_.long_accel > 0.0F && speed_diff < -vse_cal_.k_speed_accel_consistency_thresh * delta_t_s) ||
                (vse_ipc_.long_accel < 0.0F && speed_diff > vse_cal_.k_speed_accel_consistency_thresh * delta_t_s)) {
                speed_accel_consistent = false;
            }
        }

        if ((speed_change_valid && speed_accel_consistent) || (vse_ipc_.aeb_active && raw_speed < 0.3F && speed_filter_.getState()(0) >= raw_speed)) {
            vse_ipc_.speed = raw_speed;

            Eigen::VectorXd control(1);
            control << vse_ipc_.long_accel * delta_t_s;
            (void)speed_filter_.predict(control);

            Eigen::VectorXd measurement(1);
            measurement << vse_ipc_.speed;
            (void)speed_filter_.update(measurement);
        } else {
            Eigen::VectorXd control(1);
            control << vse_ipc_.long_accel * delta_t_s;

            (void)speed_filter_.predict(control);

            Eigen::VectorXd measurement(1);
            measurement << raw_speed;
            (void)speed_filter_.update(measurement);

            float estimated_speed = static_cast<float>(speed_filter_.getState()(0));
            if (fabs(estimated_speed - prev_speed) > 20.0F * delta_t_s) {
                float predicted_speed = prev_speed + predicted_speed_change;
                float weight_pred = vse_cal_.k_speed_fusion_weight_pred;
                float weight_updated = 1.0F - weight_pred;
                estimated_speed = weight_pred * predicted_speed + weight_updated * estimated_speed;
                Eigen::VectorXd x_fused(1);
                x_fused << estimated_speed;
                speed_filter_.reset(x_fused, speed_filter_.getCovariance());
            }
            if (estimated_speed < 0.0F) {
                estimated_speed = 0.0F;
                // 重置滤波器状态
                Eigen::VectorXd x0(1);
                Eigen::MatrixXd P0(1, 1);
                x0 << 0.0;
                P0 << 1.0;
                speed_filter_.reset(x0, P0);
            }

            vse_ipc_.speed = estimated_speed;
        }
    } else {
        vse_ipc_.speed = raw_speed;

        // 初始化卡尔曼滤波器状态
        Eigen::VectorXd x0(1);
        Eigen::MatrixXd P0(1, 1);
        x0 << vse_ipc_.speed;
        P0 << 1.0;
        speed_filter_.reset(x0, P0);
    }

    vse_ipc_.sensor_long_vel = raw_speed;
    vse_ipc_.vcs_long_vel = vse_ipc_.speed;
    if (is_reverse) {
        vse_ipc_.sensor_long_vel = -raw_speed;
        vse_ipc_.vcs_long_vel = -vse_ipc_.speed;
        vse_ipc_.speed = -vse_ipc_.speed;
    }
}

void VehicleStateEstimed::CalcLatVelocityAndAccel() {
    vse_ipc_.sensor_lat_vel = vse_ipc_.speed * tan(vse_ipc_.sensor_sideslip);
    vse_ipc_.vcs_lat_vel = vse_ipc_.speed * tan(vse_ipc_.vcs_sideslip);
    vse_ipc_.lat_accel = vse_inport_.master_imu_lataccel;
}

void VehicleStateEstimed::UpdateBcmAcuBcsInfo() {
    // BCM
    vse_ipc_.fl_door_st = vse_inport_.drvr_door_open;
    vse_ipc_.fr_door_st = vse_inport_.psngr_door_ajar_st;
    vse_ipc_.rl_door_st = vse_inport_.rl_door_ajar_st;
    vse_ipc_.rr_door_st = vse_inport_.rr_door_ajar_st;
    vse_ipc_.trunk_st = vse_inport_.trunk_ajar_st;
    vse_ipc_.eng_hood_unlock_warn = vse_inport_.trunk_ajar_st;
    vse_ipc_.hazard_lamp_st = vse_inport_.hazard_light_stat;
    vse_ipc_.front_wiper_work_st = vse_inport_.wind_shield_wiper_active;
    vse_ipc_.driver_belt_switch_st = vse_inport_.drvr_sb_fasten;
    vse_ipc_.high_beam_st = vse_inport_.hl_beam_sw_stat;
    vse_ipc_.turn_light_switch_pos = vse_inport_.turn_lamp_switchpos;
    if (vse_ipc_.turn_light_switch_pos == 1) {
        vse_ipc_.left_light_st = 1;
    } else {
        vse_ipc_.left_light_st = 0;
    }
    if (vse_ipc_.turn_light_switch_pos == 3) {
        vse_ipc_.right_light_st = 1;
    } else {
        vse_ipc_.right_light_st = 0;
    }
    vse_ipc_.front_fog_lamp_st = vse_inport_.frnt_fog_lmp_stat;
    vse_ipc_.back_fog_lamp_st = vse_inport_.rear_fog_lmp_stat;
    vse_ipc_.left_light_fault_st = vse_inport_.lturn_lmp_fault_st;
    vse_ipc_.right_light_fault_st = vse_inport_.rturn_lmp_fault_st;
    vse_ipc_.epb_applied = (vse_inport_.epb_stat == 1);
    if (vse_inport_.trans_estd_gear == 12) {
        vse_ipc_.actual_gear = 3;
    } else if (vse_inport_.trans_estd_gear == 13) {
        vse_ipc_.actual_gear = 2;
    } else if (vse_inport_.trans_estd_gear == 14) {
        vse_ipc_.actual_gear = 1;
    } else if (vse_inport_.trans_estd_gear == 15) {
        vse_ipc_.actual_gear = 0;
    } else {
        vse_ipc_.actual_gear = 4;
    }
    vse_ipc_.brake_pedal_apld = vse_inport_.brk_pedal_prsd;
    // ACU
    // 暂时给默认值:等后续WI适配
    // if (vse_inport_.longsafe_cus_set == 3 &&
    //     vse_inport_.fcaclnwarn_cus_set == 2) {
    //   vse_ipc_.longsafe_switch = 3; // Brake And Warn
    // } else if (vse_inport_.longsafe_cus_set == 3 &&
    //            vse_inport_.fcaclnwarn_cus_set != 2) {
    //   vse_ipc_.longsafe_switch = 2; // Only Brake
    // } else if (vse_inport_.longsafe_cus_set != 3 &&
    //            vse_inport_.fcaclnwarn_cus_set == 2) {
    //   vse_ipc_.longsafe_switch = 1; // Only Warn
    // } else {
    //   vse_ipc_.longsafe_switch = 0; // Not Use
    // }
    // bsd/dow/fctb/rctb/rcw 输入侧为脉冲信号，脉冲值即目标状态，非0时更新并保持，0时维持上次值
    if (vse_inport_.bsd_switch_req != 0U) {
        vse_ipc_.bsd_switch = vse_inport_.bsd_switch_req;
    }
    if (vse_inport_.dow_switch_req != 0U) {
        vse_ipc_.dow_switch = vse_inport_.dow_switch_req;
    }
    if (vse_inport_.fcta_switch_req != 0U) {
        vse_ipc_.fctb_switch = vse_inport_.fcta_switch_req;
    }
    if (vse_inport_.rcta_switch_req != 0U) {
        vse_ipc_.rctb_switch = vse_inport_.rcta_switch_req;
    }
    if (vse_inport_.rcw_switch_req != 0U) {
        vse_ipc_.rcw_switch = vse_inport_.rcw_switch_req;
    }
    //  vse_ipc_.fcw_warn_dist = vse_inport_.fcw_snvty_set;
    vse_ipc_.longsafe_switch = 3;
    vse_ipc_.lss_switch      = vse_inport_.lss_switch;
    vse_ipc_.lss_sensitivity = vse_inport_.lss_sensitivity;
    vse_ipc_.elk_switch      = vse_inport_.elk_switch;
    vse_ipc_.ldw_switch      = vse_inport_.ldw_switch;
    vse_ipc_.lka_switch      = vse_inport_.lka_switch;
    vse_ipc_.esa_switch      = vse_inport_.esa_switch;
    vse_ipc_.aes_switch      = vse_inport_.aes_switch;
    //为aes触发临时bypass开关
    //vse_ipc_.esa_switch      = 1; //暂时给1
    //vse_ipc_.aes_switch      = 1; //暂时给1
    // vse_ipc_.bsd_switch      = 2;
    // vse_ipc_.dow_switch      = 1;
    // vse_ipc_.fctb_switch     = 3;
    // vse_ipc_.rctb_switch     = 3;
    // vse_ipc_.rcw_switch      = 1;
    vse_ipc_.aeb_switch      = vse_inport_.aeb_switch;
    vse_ipc_.fcw_switch      = vse_inport_.fcw_switch;
    vse_ipc_.fcw_sensitivity_set = vse_inport_.fcw_snvty_set;
    vse_ipc_.fcw_warn_dist   = vse_inport_.fcw_snvty_set;
    // BCS
    vse_ipc_.vdc_active_st          = vse_inport_.vse_act;
    vse_ipc_.veh_dyn_cntl_stat      = vse_inport_.veh_dyn_cntl_stat;
    vse_ipc_.tcs_active_st          = vse_inport_.tcs_act;
    vse_ipc_.tcs_sta                = vse_inport_.tcs_sta;
    vse_ipc_.hdc_active_st          = (vse_inport_.hdc_stat == 2);
    vse_ipc_.lgctrl_trq_req_sts     = vse_inport_.lgctrl_trq_req_sts;
    vse_ipc_.veh_crash              = (vse_inport_.veh_crash == 1);
    vse_ipc_.esc_off_st             = (vse_inport_.tcs_mod == 0);
    vse_ipc_.airbag_virt_dev_avl    = vse_inport_.airbag_virt_dev_avl;
    vse_ipc_.tire_presr_fault       = vse_inport_.tire_presr_fault;
    vse_ipc_.lka_trq_ovl_dlvd_stat  = vse_inport_.lka_trq_ovl_dlvd_stat;
    vse_ipc_.esp_brake_available_st = vse_inport_.brake_sys_avail_mask;
    vse_ipc_.abs_active = vse_inport_.abs_active;
    vse_ipc_.long_ctrl_brake_active = vse_inport_.long_ctrl_active;
    // vse_ipc_.aeb_active             = (vse_inport_.brake_sys_active_mask & 1) > 0;
    vse_ipc_.aeb_active = ((vse_inport_.long_ctrl_active == false)  &&  (vse_inport_.auto_brake_active == true));
    vse_ipc_.f_reverse_status =
        ((vse_inport_.right_notdriven_wheel_rotdir == uint8_t(2)) || (vse_inport_.left_notdriven_wheel_rotdir == uint8_t(2)) ||
         (vse_inport_.right_driven_wheel_rotdir == uint8_t(2)) || (vse_inport_.left_driven_wheel_rotdir == uint8_t(2)));
    vse_ipc_.power_mode = (vse_inport_.sys_pwr_mod == 2);
    // VCU
    float brake_pedal_pos_rate_unfilt = (vse_inport_.brk_pedal_pos - vse_ipc_.brake_pedal_pos) / vse_cal_.k_vse_step_time;
    float gas_pedal_pos_rate_unfilt = (vse_inport_.accel_ped_pos - vse_ipc_.gas_pedal_pos) / vse_cal_.k_vse_step_time;
    float brake_press_rate_unfilt = (vse_inport_.brk_pdl_drvr_apld_prs - vse_ipc_.brake_pressure) / vse_cal_.k_vse_step_time;
    vse_ipc_.brake_pedal_pos_rate = math::LowPassFilter(brake_pedal_pos_rate_unfilt, vse_ipc_.brake_pedal_pos_rate, vse_cal_.k_brake_pedal_rate_gain);
    vse_ipc_.gas_pedal_pos_rate   = math::LowPassFilter(gas_pedal_pos_rate_unfilt, vse_ipc_.gas_pedal_pos_rate, vse_cal_.k_gas_pedal_rate_gain);
    vse_ipc_.brake_pressure_rate  = math::LowPassFilter(brake_press_rate_unfilt, vse_ipc_.brake_pressure_rate, vse_cal_.k_brake_press_rate_gain);
    vse_ipc_.gas_pedal_pos        = vse_inport_.accel_ped_pos;
    vse_ipc_.brake_pedal_pos      = vse_inport_.brk_pedal_pos;
    vse_ipc_.brake_pressure       = vse_inport_.brk_pdl_drvr_apld_prs;
    vse_ipc_.torsion_bar_trq      = vse_inport_.torsion_bar_trq;//手力矩
    vse_ipc_.hod_hands_monitor    = vse_inport_.hod_hands_monitor;
    // 手力矩逻辑需要做，为aes不受抑制
    vse_ipc_.brake_pedal_type     = 0;  
    vse_ipc_.function_did_config  = vse_inport_.function_did_config;
}
void VehicleStateEstimed::CalcCurvatureAndSideSlip() {
    if (curtime_ms_ > prev_time_) {
        uint64_t delta_t = curtime_ms_ - prev_time_;
        float dt = static_cast<float>(delta_t) / 1000.0F;

        curv_dist_ = curv_dist_ + vse_ipc_.speed * dt;

        if (fabs(vse_ipc_.speed) > vse_cal_.k_dist_based_curv_speed_thresh) {
            curv_integ_yaw_ = curv_integ_yaw_ + vse_ipc_.yawrate * dt;
        }

        if (fabs(curv_dist_) > vse_cal_.k_dist_based_curv_discrete_distance_interval) {
            // 计算过程噪声和观测噪声
            float Q = vse_cal_.k_curv_kalman_gain_1 / fmax(powf(vse_ipc_.speed, 4), 1.0F);
            float R = vse_cal_.k_curv_kalman_gain_2 / fmax(powf(vse_ipc_.speed, 2), 1.0F);

            // 动态设置状态转移矩阵
            Eigen::Matrix2d F;
            F << 1, dt, 0, 1;
            curvature_filter_.setStateTransitionMatrix(F);

            // 更新滤波器噪声参数
            Eigen::Matrix2d Q_matrix;
            Q_matrix << Q, 0, 0, Q;
            curvature_filter_.setProcessNoiseCov(Q_matrix);

            // 更新量测噪声参数
            Eigen::MatrixXd R_matrix(1, 1);
            R_matrix << R;
            curvature_filter_.setMeasurementNoiseCov(R_matrix);

            // 获取观测值
            float rawCurv = curv_integ_yaw_ / curv_dist_;
            Eigen::VectorXd measurement(1);
            measurement << rawCurv;

            // 执行卡尔曼滤波更新
            (void)curvature_filter_.predict();
            (void)curvature_filter_.update(measurement);

            // 重置积分量
            curv_integ_yaw_ = 0;
            curv_dist_ = 0;
        }
        // 获取当前状态估计
        Eigen::VectorXd state = curvature_filter_.getState();
        float estimated_curvature = state[0];
        float estimated_curvature_rate = state[1];

        // 计算混合曲率 (基于速度的权重)
        float Curv_fac;
        if (vse_ipc_.speed > vse_cal_.k_cal_curv_use_yawrte_speed_mps) {
            Curv_fac = 1;
        } else if (vse_ipc_.speed > vse_cal_.k_cal_curv_use_steering_speed_mps) {
            Curv_fac = (vse_ipc_.speed - vse_cal_.k_cal_curv_use_steering_speed_mps) /
                (vse_cal_.k_cal_curv_use_yawrte_speed_mps - vse_cal_.k_cal_curv_use_steering_speed_mps);
        } else {
            Curv_fac = 0;
        }

        // 计算基于转向的曲率
        float wheel_base = fmaxf(vse_ipc_.config.k_wheel_base, 0.1F);
        float rear_curv_base_str = tan((vse_inport_.steer_wheel_angle / vse_ipc_.config.k_steer_ratio) * m_pi / 180.0F) / wheel_base;

        // 混合曲率估计
        vse_ipc_.rear_curvature = estimated_curvature * Curv_fac + (1 - Curv_fac) * rear_curv_base_str;
        vse_ipc_.rear_curvaturerate = estimated_curvature_rate;

        if (vse_ipc_.speed >= 0) {
            vse_ipc_.rear_sideslip = vse_ipc_.config.k_rear_cornering_compliance * vse_ipc_.rear_curvature * (vse_ipc_.speed) * (vse_ipc_.speed);
            vse_ipc_.vcs_sideslip = atan(vse_ipc_.rear_curvature * fabs(vse_ipc_.config.k_dist_to_rear_axle) + tan(vse_ipc_.rear_sideslip));
            vse_ipc_.sensor_sideslip =
                atan(vse_ipc_.rear_curvature * (fabs(vse_ipc_.config.k_dist_to_rear_axle) - fabs(vse_ipc_.config.k_vcs_camera_long_posn)) +
                     tan(vse_ipc_.rear_sideslip));
        } else {
            vse_ipc_.rear_sideslip =
                vse_ipc_.config.k_rear_cornering_compliance * vse_ipc_.rear_curvature * (vse_ipc_.speed) * (vse_ipc_.speed) + m_pi;
            vse_ipc_.vcs_sideslip = atan(vse_ipc_.rear_curvature * fabs(vse_ipc_.config.k_dist_to_rear_axle) - tan(vse_ipc_.rear_sideslip)) + m_pi;
            vse_ipc_.sensor_sideslip =
                atan(vse_ipc_.rear_curvature * (fabs(vse_ipc_.config.k_dist_to_rear_axle) - fabs(vse_ipc_.config.k_vcs_camera_long_posn)) -
                     tan(vse_ipc_.rear_sideslip)) +
                m_pi;
        }
    }
    if (fabs(vse_ipc_.speed) < 0.2) {
        Eigen::Vector2d x0;
        Eigen::Matrix2d P0;
        x0 << 0, 0;
        P0 << 0, 0, 0, 0;
        curvature_filter_.reset(x0, P0);
    }
    vse_ipc_.rear_curvature_radius = math::SafeDivide(1.0F, vse_ipc_.rear_curvature);
}
void VehicleStateEstimed::CheckHostStraightDriving() {
    // 判断自车是否直行
    if (vse_ipc_.straight_driving) {
        if (std::abs(vse_ipc_.rear_curvature) > 0.01) {
            vse_ipc_.straight_driving = false;
        }
    } else {
        if (std::abs(vse_ipc_.rear_curvature) > 0.005) {
            vse_ipc_.straight_driving = false;
        } else {
            vse_ipc_.straight_driving = true;
        }
    }
}

void VehicleStateEstimed::SeriesRecord() {
    if (curtime_ms_ > prev_time_) {
        time_series.push(curtime_ms_);
        yawrate_series.push(vse_ipc_.yawrate);
        rear_sideslip_series.push(vse_ipc_.rear_sideslip);
        rear_curv_series.push(vse_ipc_.rear_curvature);
        speed_series.push(vse_ipc_.speed);
        CalcHeadingSeries();
        CalcTrajectorySeries();
    }
}

Eigen::Vector3f VehicleStateEstimed::TransformPosForDelay(float deltaTm) const {
    std::size_t sz = 0;
    for (std::size_t idx = 1; idx < time_series.capacity() - 1; ++idx) {
        if (time_series.get_frame(0) - time_series.get_frame(idx - 1) > deltaTm) {
            sz = idx - 2;
            break;
        }
    }
    // Saturation.
    if (sz >= time_series.capacity()) {
        sz = time_series.capacity() - 1;
    }

    Eigen::Vector3f deltaEgo;
    deltaEgo[0] = rear_posx_series.get_frame(0) - rear_posx_series.get_frame(sz);
    deltaEgo[1] = rear_posy_series.get_frame(0) - rear_posy_series.get_frame(sz);
    deltaEgo[2] = heading_series.get_frame(0) - heading_series.get_frame(sz);

    return deltaEgo;
}

float VehicleStateEstimed::FilterYawRate(float yawrate_rps) {
    float YawrateFilterFac;
    vse_ipc_.yawrate_unfiltered_rps = yawrate_rps;
    // Determine the filter factor based on the change in yaw rate
    if (std::abs(vse_ipc_.steerwheelangle) > 8.0F) {
        YawrateFilterFac = 0.3F;
    } else {
        if ((fabs(yawrate_rps - yawrate_filtered_) < vse_cal_.k_min_yawrate_delta)  ||  (vse_ipc_.long_accel < -5.0F)) {
            YawrateFilterFac = vse_cal_.k_yawrate_filter_gain * 0.2F; // Decrease influence if change is small
        } else {
            YawrateFilterFac = vse_cal_.k_yawrate_filter_gain; // Normal influence
        }
    }
    yawrate_filtered_ = (yawrate_rps - yawrate_filtered_) * YawrateFilterFac + yawrate_filtered_;
    return yawrate_filtered_;
}

void VehicleStateEstimed::CalcHeadingSeries() {
    float deltaTm = 0.0F;
    float hdg_rad = yawrate_series.get_frame(0) * deltaTm;

    heading_series.push(hdg_rad);

    for (std::size_t i = 1; i < heading_series.capacity(); i++) {
        deltaTm = (float)(static_cast<int64_t>(time_series.get_frame(i - 1) - time_series.get_frame(i))) / 1000.0F;
        hdg_rad = heading_series.get_frame(i - 1) - yawrate_series.get_frame(i - 1) * deltaTm;
        heading_series.modify_frame(i, hdg_rad);
    }
}

void VehicleStateEstimed::CalcTrajectorySeries() {
    float deltaTm = 0.0F;
    float pos_x_series = cos(heading_series.get_frame(0) + rear_sideslip_series.get_frame(0)) * speed_series.get_frame(0) * deltaTm;
    rear_posx_series.push(pos_x_series);
    float PosY_series = sin(heading_series.get_frame(0) + rear_sideslip_series.get_frame(0)) * speed_series.get_frame(0) * deltaTm;
    rear_posy_series.push(PosY_series);
    for (std::size_t i = 1; i < rear_posx_series.capacity(); i++) {
        float SideSlip = rear_sideslip_series.get_frame(i);

        if (speed_series.get_frame(i) < 0.0F) {
            SideSlip = rear_sideslip_series.get_frame(i) - m_pi;
        }

        deltaTm = (float)(static_cast<int64_t>(time_series.get_frame(i) - time_series.get_frame(i - 1))) / 1000.0F;
        pos_x_series = cos(heading_series.get_frame(i) + SideSlip) * speed_series.get_frame(i) * deltaTm + rear_posx_series.get_frame(i - 1);
        rear_posx_series.modify_frame(i, pos_x_series);
        PosY_series = sin(heading_series.get_frame(i) + SideSlip) * speed_series.get_frame(i) * deltaTm + rear_posy_series.get_frame(i - 1);
        rear_posy_series.modify_frame(i, PosY_series);
    }
}

void VehicleStateEstimed::TransClusterSpeed() {
    float clu_fac, clu_ofs;
    float vspd_kph = 3.6F * vse_ipc_.speed;
    const std::array<float, 14> k_Cluster_NonLinear_Factor_x{{0.0F, 10.0F, 11.0F, 40.0F, 60.0F, 80.0F, 100.0F, 120.F, 140.0F, 160.0F, 180.0F, 200.0F, 220.0F, 240.0F}};
    const std::array<float, 14> k_Cluster_NonLinear_Factor_z{{1.0F, 1.02F, 1.02F, 1.02F, 1.02F, 1.02F, 1.02F, 1.02F, 1.02F, 1.02F, 1.02F, 1.02F, 1.02F, 1.02F}};
    const std::array<float, 14> k_Cluster_Offset_z{{0.0F, 0.0F, 2.0F, 2.0F, 2.0F, 2.0F, 2.0F, 2.0F, 2.0F, 2.0F, 2.0F, 2.0F, 2.0F, 2.0F}};
    clu_fac = math::LookUpTable::LookupTable1D<14>(k_Cluster_NonLinear_Factor_x, k_Cluster_NonLinear_Factor_z, vspd_kph);
    clu_ofs = math::LookUpTable::LookupTable1D<14>(k_Cluster_NonLinear_Factor_x, k_Cluster_Offset_z, vspd_kph);
    vse_ipc_.display_speed = std::round(vspd_kph * clu_fac + clu_ofs);
}

} // namespace active_safety
