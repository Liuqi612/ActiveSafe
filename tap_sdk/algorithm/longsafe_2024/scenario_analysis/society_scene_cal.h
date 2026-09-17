/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_ALGORITHM_LONGSAFE_2024_SCENARIO_ANALYSIS_SOCIETY_SCENE_CAL_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_2024_SCENARIO_ANALYSIS_SOCIETY_SCENE_CAL_H_
#include <array>
namespace senseAD {
namespace tap {
#define LOOP_TIME_SOCIETY 20
struct AsSocietySceneParam {
    float k_sc_moving_veh = 1.5F;
    float k_sc_moving_truck = 1.5F;
    float k_sc_max_child_height = 1.65F;
    float k_cpfao_max_ped_car_delt_Poselgt = 13.0F;
    float k_cbnao_max_ped_car_delt_Poselgt = 13.0F;
    float k_csfao_max_ped_car_delt_Poselgt = 13.0F;
    float k_csfao_max_car_car_delt_Poselgt = 50.0F;
    std::array<float, 5> k_cpnco_scene_hostspd_brakepoints{{5.55, 8.33, 11.11, 13.88, 16.67}};
    std::array<float, 5> k_cpnco_scene_statcar_longposthres{{10.0, 10.0, 10.0, 13.0, 16.0}};
    std::array<float, 5> k_cpnco_scene_child_longposthres{{7.0, 20.0, 30.0, 30.0, 30.0}};
    std::array<float, 4> k_scp_scene_hostspd_brakepoints{{8.33, 11.11, 13.88, 16.67}};
    std::array<float, 4> k_scp_scene_obj_latspd_brakepoints{{4.0, 6.0, 9.0, 10.0}};
    std::array<float, 4> k_scp_scene_obj_highlatspd_brakepoints{{6.0, 9.0, 13.0, 15.0F}};
    std::array<float, 4> k_scp_scene_obj_highlatspd_select_brakepoints{{13.0, 13.0, 13.0F, 13.0}};
    std::array<float, 4> k_scp_scene_obj_longpos_brakepoints{{20.0F, 25.0F, 30.0F, 30.0F}};

    std::array<float, 6> k_host_spd_brakepoints{{10, 20, 30, 40.0, 50.0, 60.0}};
    std::array<float, 6> k_brake_distance_brakepoints{{8.0, 11.0, 14.0, 19.0, 37.0, 42.0}};
    float k_scp_scene_obj_longvel_thres = 4.0F;

    int k_ego_constant_spd_cnt_thrd = 4 * 50;
    int k_ego_constant_highspd_cnt_thrd = 4 * 50;
    int k_ego_not_constant_spd_cnt_thrd = 4 * 50;
    float k_constand_spd_max_err = 1.2F;
    float k_constand_highspd_max_err = 1.2F;
    float k_stationary2start_max_valid_time = 60 * 50;
    float k_enable_cross_special_select = true;

    int k_cpta_l_low_cnt_thrd = 4 * 50;
    int k_cpta_l_mid_cnt_thrd = 4 * 50;
    float k_turn_left_steerangle_lowspd_thrd = 80;
    float k_turn_left_steerangle_midspd_thrd = 60;

    int k_csta_rn_cnt_lowspd_thrd = 4 * 50;
    int k_csta_rn_cnt_midspd_thrd = 4 * 50;
    float k_turn_right_steerangle_midthrd = -3;
    float k_turn_right_steerangle_lowthrd = -10;

    float k_cpfao_barrier_car_thrd_ = 3.0F * 50;
    float k_cpfao_barrier_car_highspd_thrd_ = 2.4F * 50;
    float k_cbnao_barrier_car_highspd_thrd_ = 2.4F * 50;
    float k_cbnao_barrier_car_thrd_ = 3.0F * 50;
    float k_csfao_barrier_car_highspd_thrd_ = 2.4F * 50;
    float k_csfao_barrier_car_thrd_ = 3.0F * 50;
    float k_scpo_barrier_car_thrd_ = 3.0F * 50;
    float k_scpo_barrier_car_highspd_thrd_ = 2.4 * 50;

    float k_disable_testscene_brake_pose_thd = 5;
    float k_disable_testscene_accel_pose_thd = 90;

    float k_constant_spd_allow_max_curv = 0.01;
    uint32_t k_simulation_max_steps = 40 * 50; // 仿真预热调用次数阈值，按 50 Hz 约为 40 秒；0 表示跳过预热
    int k_MaxConfirmCount = 600;         // 车速确认计数上限
    int k_DecStep = 50;  // 计数递减步长
};

} // namespace tap
} // namespace senseAD
#endif // TAP_SDK_ALGORITHM_LONGSAFE_2024_SCENARIO_ANALYSIS_SOCIETY_SCENE_CAL_H_
