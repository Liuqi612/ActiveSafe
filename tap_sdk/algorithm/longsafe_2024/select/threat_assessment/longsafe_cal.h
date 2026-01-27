/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include <array>
namespace senseAD {
namespace tap {

#define SWITCH_FOR_TTM true
#define LOOP_TIME_TSEL 20

struct AsObsCollEvaCal {
  float k_spd_thd_for_stat_lgt = 0.5;
  float k_spd_thd_for_stat_lat = 0.5;

  float k_obs_heading_thd_in_path_long = 1.57;
  float k_obs_heading_thd_in_path_short = 1.57;
  float k_bicycle_heading_thd_in_path = 0.4;

  float k_crvt_thd_for_curved_motion = 0.002;

  float k_tti_low = -100.0;
  float k_tti_uppr = 100.0;

  float k_bike_width = 0.5;
  float k_bike_spd_thd = 2.0;

  float k_car_length = 5.0;
  float k_barrier_max_length = 1.5;
  float k_barrier_max_width = 0.5;
  float k_motor_tiny_length = 3.0;
  float k_veh_unknown_length = 0.01;
  float k_motorcycle_length = 2.0;
  float k_bicycle_length = 1.5;
  float k_truck_length = 8.0;

  float k_bike_low_thd = 2.0;
};

struct AsSensorPlauCal {
  bool k_ignore_sense_plaus_check = false;
  float k_vision_lat_vel_thres_use_pctchk = 0.5;
  float k_vision_lat_pos_thres_use_pctchk = 0.5;
  int k_notsel_lat_pos_fail_cnt_thres = -2;
  int k_sel_lat_pos_fail_cnt_thres = -10;
  int k_notsel_lat_vel_fail_cnt_thres = -2;
  int k_sel_lat_vel_fail_cnt_thres = -10;
  std::array<float, 9> k_target_range_points{
      {0.0, 3.0, 5.0, 10.0, 15.0, 20.0, 25.0, 40.0, 50.0}};
  std::array<float, 9> k_ped_lat_pospct_plausthres{
      {1.0, 0.6, 0.4, 0.34, 0.34, 0.34, 0.44, 0.5, 0.6}};
  std::array<float, 9> k_ped_lat_velpct_plausthres{
      {1.0, 0.6, 0.4, 0.34, 0.34, 0.34, 0.44, 0.5, 0.6}};
  std::array<float, 9> k_veh_lat_pospct_plausthres{
      {1.0, 0.8, 0.7, 0.6, 0.44, 0.4, 0.44, 0.5, 0.6}};
  std::array<float, 9> k_veh_lat_velpct_plausthres{
      {1.0, 0.8, 0.7, 0.6, 0.44, 0.4, 0.44, 0.5, 0.6}};
  std::array<float, 7> k_target_rangerate_points{
      {1.5, 2.8, 5.55, 8.33, 11.1, 13.38, 20.0}};
  std::array<float, 7> k_target_long_momerror_thres{
      {0.8, 0.8, 0.8, 0.8, 1.0, 1.0, 1.0}};
  std::array<float, 7> k_target_latrate_points{
      {0.0f, 1.0f, 5.5f, 8.33, 11.1, 13.38, 20.0}};
  std::array<float, 7> k_target_lat_momerror_thres{
      {0.8, 0.8, 0.8, 1.0, 1.0, 1.5, 2.0}};
  uint32_t k_target_basic_check_fail_reset_time = 1000;
};

struct SafetyMarginEvalatorCal {
  float k_max_aeb_active_ttr_thd = 1.40;
  float k_max_pred_tti_thd = 3.0;
  float k_max_pred_dist_thd = 50.0;
  float k_min_pred_spd_thd = 1.0;
  float k_ag_dir_spd_thd = 10.0;
  float k_min_bike_spd_thd = 2.0;
  float k_bike_width_offset = 0.5;
  float k_bike_length_offset = 1.50;
  float k_ang_dir_for_brk_thd = 0.0;
  float k_fast_bike_spd_thd = 2.78;
  float k_stationary_bike_spd_thd = 1.2;
  float k_fast_ped_spd_thd = 0.6;

  float k_inpath_ltap_latoffs_veh = 0.3;
  float k_inpath_obj_detect_spdthd = 0.2;

  float k_vel_offs_lgt = 1.0;

  float k_bike_inpath_lat_spd_thd = 0.8;
  float k_ped_inpath_lat_spd_thdcrvt_rot_thd = 0.7;
  float k_min_lat_cmbb = 0.3;
  float k_gop_min_lat_cmbb = 0.1;

  std::array<float, 8> k_longlgt_vlgtrel{
      {0.0, 4.0, 8.0, 12.0, 16.0, 20.0, 24.0, 28.0}};
  std::array<float, 8> k_longlgt_vlgt_vru_offs{
      {0.1, 0.1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}};
  std::array<float, 8> k_longlgt_vlgt_veh_offs{
      {0.1, 0.1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}};
  std::array<float, 8> k_longlat_vlgtrel{
      {2.0, 4.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0}};
  std::array<float, 8> k_longlat_vlatrel{
      {0.0, 0.25, 0.5, 0.75, 1.0, 1.1, 1.2, 1.3}};
  std::array<float, 8> k_longlat_vlatabs{
      {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0}};
  std::array<float, 9> k_longlat_algtraw{
      {-10.0, -8.0, -6.0, -5.0, -4.0, -3.0, -1.5, 0.0, 1.0}};
  std::array<float, 9> k_longlat_algt_veh_offs{
      {0.5, 0.45, 0.4, 0.35, 0.25, 0.05, 0.0, 0.0, 0.0}};
  std::array<std::array<float, 8>, 8> k_longlat_vlgt_vlat_vru{
      {{{0.75, 0.65, 0.55, 0.65, 0.75, 0.75, 0.75, 0.75}},
       {{0.95, 0.83, 0.71, 0.83, 0.95, 0.95, 0.95, 0.95}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}}}};
  std::array<std::array<float, 8>, 8> k_longlat_vlgt_vlat_veh{
      {{{-0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1}},
       {{-0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1}},
       {{-0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1}},
       {{0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15}},
       {{0.62, 0.62, 0.62, 0.62, 0.62, 0.62, 0.62, 0.62}},
       {{0.69, 0.69, 0.69, 0.69, 0.69, 0.69, 0.69, 0.69}},
       {{0.72, 0.72, 0.72, 0.72, 0.72, 0.72, 0.72, 0.72}},
       {{0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80}}}};

  std::array<float, 8> k_shortlgt_vlgtrel{
      {0.0, 4.0, 8.0, 12.0, 16.0, 20.0, 24.0, 28.0}};
  std::array<float, 8> k_shortlgt_vlgt_vru_offs{
      {0.45, 0.55, 0.65, 0.75, 0.75, 0.75, 0.75, 0.75}};
  std::array<float, 8> k_shortlgt_poslgt{
      {0.0, 2.3, 2.5, 3.0, 5.0, 7.0, 10.0, 50.0}};
  std::array<float, 8> k_shortlgt_poslgt_veh_offs{
      {0.0, 0.20, 0.40, 0.50, 0.50, 0.50, 0.50, 0.50}};
  std::array<float, 8> k_shortlat_vlgtrel{
      {2.0, 4.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0}};
  std::array<float, 8> k_shortlat_vlatabs{
      {0.0, 0.25, 0.5, 0.75, 1.0, 1.1, 1.2, 1.30}};
  std::array<float, 8> k_shortlat_vlgtrel_cyclist{
      {0.0, 3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0}};
  std::array<float, 8> k_shortlat_vlatabs_cyclist{
      {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0}};

  std::array<float, 8> k_shortlat_vlgtrel_veh{
      {0.0, 3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0}};
  std::array<float, 8> k_shortlat_vlatrel_veh{
      {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0}};

  std::array<std::array<float, 8>, 8> k_shortlat_vlgt_vlat_vru{
      {{{0.75, 0.65, 0.55, 0.65, 0.75, 0.75, 0.75, 0.75}},
       {{0.95, 0.83, 0.71, 0.83, 0.95, 0.95, 0.95, 0.95}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}}}};
  std::array<std::array<float, 8>, 8> k_shortlat_vlgt_vlat_cyclist{
      {{{0.6, 0.6, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}},
       {{0.6, 0.7, 0.7, 0.6, 0.6, 0.6, 0.6, 0.6}},
       {{0.7, 0.9, 0.9, 0.7, 0.7, 0.7, 0.7, 0.7}},
       {{0.7, 0.9, 0.9, 0.7, 0.7, 0.7, 0.7, 0.7}},
       {{0.8, 1.05, 0.95, 0.8, 0.8, 0.8, 0.8, 0.8}},
       {{0.8, 1.05, 0.95, 0.78, 0.78, 0.78, 0.78, 0.78}},
       {{1.0, 1.05, 0.95, 0.72, 0.72, 0.72, 0.72, 0.72}},
       {{1.0, 1.05, 1.05, 0.8, 0.8, 0.8, 0.8, 0.8}}}};
  std::array<std::array<float, 8>, 8> k_shortlat_vlgt_vlat_veh{
      {{{-0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1}},
       {{-0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1}},
       {{-0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1}},
       {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
       {{0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8}},
       {{0.8, 0.78, 0.78, 0.78, 0.78, 0.78, 0.78, 0.78}},
       {{1.4, 0.72, 0.72, 0.72, 0.72, 0.72, 0.72, 0.72}},
       {{1.4, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.8}}}};
  std::array<float, 9> k_shortlat_algtabs{
      {-10.0, -8.0, -6.0, -5.0, -4.0, -3.0, -1.50, 0.0, 1.0}};
  std::array<float, 9> k_shortlat_algt_veh_offs{
      {0.50, 0.45, 0.40, 0.35, 0.25, 0.050, 0.0, 0.0, 0.0}};

  std::array<float, 8> k_manv_vlgt_ego{
      {0.0, 2.50, 3.0, 6.0, 10.0, 15.0, 25.0, 30.0}};
  std::array<float, 8> k_manv_vlgt_rel{
      {3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0}};
  std::array<float, 8> k_manv_latoffs_vru{
      {0.0, 0.0, 0.2, 0.5, 0.7, 0.7, 0.7, 0.7}};
  std::array<float, 8> k_manv_latoffs_bike{
      {-0.05, -0.05, 0.0, 0.1, 0.1, 0.1, 0.1, 0.1}};
  std::array<float, 8> k_manv_latoffs_veh{
      {-0.05, -0.05, -0.05, -0.05, -0.05, -0.05, -0.05, -0.05}};

  std::array<float, 8> k_inpath_vlgt_ego_ped{
      {0.0, 3.5, 4.5, 6.0, 10.0, 15.0, 25.0, 30.0}};
  std::array<float, 8> k_inpath_vlgt_ped_offs{
      {-0.2, -0.3, -0.2, -0.2, -0.2, -0.1, -0.1, 0.0}};
  std::array<float, 8> k_inpath_vlgt_gop_offs{
      {-0.2, -0.3, -0.2, -0.2, -0.2, -0.2, -0.1, 0.0}};
  std::array<float, 8> k_inpath_vlgt_ego_bike{
      {0.0, 2.50, 4.0, 6.0, 10.0, 15.0, 25.0, 30.0}};
  std::array<float, 8> k_inpath_vlgt_bike_offs{
      {-0.1, -0.3, -0.2, -0.2, -0.2, -0.2, -0.2, 0.0}};
  std::array<float, 11> k_inpath_posnlgt_truck{
      {0.0, 2.0, 8.0, 10.0, 12.0, 20.0, 30.0, 40.0, 60.0, 80.0, 100.0}};
  std::array<float, 11> k_inpath_posnlgt_truck_offs{
      {-0.8, -0.8, -0.7, -0.65, -0.6, -0.4, -0.3, -0.1, 0.0, 0.0, -0.2}};
  std::array<float, 11> k_inpath_posnlgt_veh{
      {0.0, 2.0, 8.0, 10.0, 12.0, 20.0, 30.0, 40.0, 60.0, 80.0, 100.0}};
  std::array<float, 11> k_inpath_posnlgt_veh_offs{
      {-0.1, -0.2, -0.2, -0.2, -0.1, -0.1, -0.1, -0.1, 0.0, 0.0, 0.0}};
  std::array<float, 11> k_inpath_posnlgt_lowspd_veh_offs{
      {-0.5, -0.5, -0.5, -0.5, -0.5, -0.4, -0.3, -0.1, -0.1, -0.1, -0.1}};


  // the
  // optional
  // choice
  std::array<std::array<float, 8>, 8> k_inpath_offset_optional{
      {{{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
       {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
       {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
       {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
       {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
       {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
       {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
       {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}}},
  };
  std::array<float, 8> k_inpath_vlgt{
      {0.0, 2.5, 3.0, 6.0, 10.0, 15.0, 25.0, 30.0}};
  std::array<float, 8> k_inpath_yaw_rate{
      {0.0, 0.02, 0.03, 0.05, 0.09, 0.1, 0.2, 0.3}};

  std::array<float, 9> k_inpath_dist_host{
      {1.5, 1.75, 1.8, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5}};
  std::array<float, 9> k_inpath_add_dist_offs{
      {0.0, 0.2, 5.0, 5.25, 5.25, 5.25, 5.25, 5.25, 5.25}};
  std::array<float, 5> k_inpath_vlgt_ego_add{{0.0, 2.0, 4.0, 6.0, 8.0}};
  std::array<float, 5> k_inpath_vlgt_lim_offs{{0.0, 0.1, 0.3, 0.7, 0.7}};
  std::array<float, 9> k_in_path_rem_edge{
      {0.2, 0.3, 0.4, 0.6, 0.8, 1.0, 1.1, 1.3, 2.0}};
  std::array<float, 9> k_inpath_add_dist_offs1{
      {0.0, 0.1, 0.1, 0.30, 0.50, 0.7, 0.7, 0.7, 0.7}};

  std::array<float, 8> k_intersec_vlgtrel{
      {0.0, 5.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0}};
  std::array<float, 8> k_intersec_latoffs_all{
      {0.1, 0.1, 0.1, 0.1, 0.18, 0.18, 0.2, 0.2}};

  std::array<float, 8> k_muti_vlgt_rel{
      {-21.0, -18.0, -15.0, -12.0, -9.0, -6.0, -3.0, 0.0}};
  std::array<float, 8> k_muti_vlat_abs{
      {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0}};
  std::array<float, 9> k_muti_algt_raw{
      {-10.0, -8.0, -6.0, -5.0, -4.0, -3.0, -1.50, 0.0, 1.0}};
  std::array<std::array<float, 8>, 8> k_muti_vlgt_vlat_vru{
      {{{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{1.25, 1.05, 0.95, 1.05, 1.25, 1.25, 1.25, 1.25}},
       {{0.95, 0.83, 0.71, 0.83, 0.95, 0.95, 0.95, 0.95}},
       {{0.75, 0.65, 0.55, 0.65, 0.75, 0.75, 0.75, 0.75}}}};
  std::array<float, 9> k_muti_algt_veh_offs{
      {0.5, 0.45, 0.4, 0.35, 0.25, 0.05, 0.0, 0.0, 0.0}};
  std::array<std::array<float, 8>, 8> k_muti_vlgt_vlat_veh{
      {{{-0.10, -0.10, -0.10, 0.80, 0.80, 0.80, 0.80, 0.80}},
       {{-0.18, -0.18, -0.18, -0.18, -0.18, -0.18, -0.18, -0.18}},
       {{-0.21, -0.21, -0.21, -0.21, -0.21, -0.21, -0.21, -0.21}},
       {{-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}},
       {{-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}},
       {{-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}},
       {{-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}},
       {{-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}}}};
  std::array<float, 8> k_manv_latoffs_diff_vru{
      {0.0, 0.51, 0.39, 0.15, 0.3, 0.55, 0.8, 0.74}};
  std::array<float, 8> k_manv_latoffs_diff_bike{
      {0.0, 0.0, 0.0, 0.0, 0.0, 0.41, 1.43, 1.43}};
  std::array<float, 8> k_manv_latoffs_diff_veh{
      {0.0, 0.0, 0.0, 0.8, 0.8, 0.8, 1.59, 1.59}};
  std::array<float, 8> k_manv_latoffs_diff_mot_ltap{
      {0.0, 0.5, 0.6, 0.7, 0.0, 0.0, 0.0, 0.0}};
  std::array<float, 8> k_manv_latoffs_diff_bike_ltap{
      {0.0, 0.3, 0.3, 0.4, 0.0, 0.0, 0.0, 0.0}};
};
struct InPathDecisionCal {
  float k_ped_decel_long_pred = -0.65;
  float k_bike_decel_long_pred = -0.65;
  float k_veh_decel_long_pred = -0.65;
  float k_ped_decel_short_pred = -2.0;
  float k_bike_decel_short_pred = -2.0;
  float k_veh_decel_short_pred = -2.0;

  float k_ped_alat_steer_pred = 2.0;
  float k_bike_alat_steer_pred = 1.4;

  float k_veh_half_width = 0.9;
  float k_uppr_lim_ttr = 3.0;
  float k_ang_dir_for_bicycle_steer_thd = 0.4;
  float k_ang_dir_for_steer_thd = 2.38;

  float k_min_heading_bike_steer = 0.4;
  float k_min_heading_steer = 2.38;
  float k_min_heading_brake = 1.0;
  float k_max_spd_obj_mov_to_self = 5.0;

  float k_bike_inpath_lat_spd_thd = 0.8;
  float k_ped_inpath_lat_spd_thdcrvt_rot_thd = 0.7;
  float k_obj_crvt_rot_thd = 0.001;

  bool k_overwrite_offset_short = true;

  std::array<float, 9> k_obj_veh_spd_steer{
      {0.0, 2.8, 5.0, 8.3, 11.0, 14.0, 17.0, 19.0, 22.0}};
  std::array<float, 9> k_veh_alat_steer_pred{
      {0.0, 0.2, 0.4, 1.1, 1.7, 2.0, 2.0, 2.0, 2.0}};
};
struct AsThreatAssessorCal {
  float k_max_spd_warn_qly_check = 60.0;
  float k_max_spd_mov_to_self_for_warn = -2.0;
  float k_max_spd_mov_to_self_for_intv = 60.0;
  float k_min_pred_spd_for_intv = 2.0;
  float k_driver_brk_dely_time = 0.20;
  float k_min_brakedelay_thd = 0.01;
  float k_max_brakedelay_thd = 1.0;
  float k_max_stop_time_obj_for_intv = 5.0;
  float k_min_pred_time_thd_for_warn = 3.0;
  float k_max_pred_dist_thd_for_warn = 50.0;
  float k_min_pred_spd_thd_for_warn = 1.0;
  float k_max_pred_spd_thd_for_ag_dir_warn = 10.0;
  float k_min_a_lat_req_limit_for_warn = -20.0;
  float k_max_a_lat_req_limit_for_warn = 20.0;
  float k_max_dist_movment_for_intv = 3.5;
  float k_v_lgt_obj_noise_thd = 0.20;
  float k_v_lat_obj_nosie_thd = 0.20;
  float k_a_lgt_obj_nosie_thd = 0.20;
  float k_a_lat_obj_nosie_thd = 0.20;
  float k_max_target_select_long_pos_thres = 100.0f;
  std::array<float, 10> k_ego_algt{
      {-5.0, -4.0, -3.0, -2.0, -1.0, -0.5, -0.3, 0.3, 1.0, 3.0}};
  std::array<float, 10> k_brake_delay_value{
      {0.03, 0.03, 0.06, 0.06, 0.25, 0.30, 0.36, 0.38, 0.50, 0.50}};
};
struct AsLongSafeCal {
  uint8_t k_longsafe_major_version = 0;
  uint8_t k_longsafe_minor_version = 0;
};
struct SafetyObsColliDetecConfig{
    // 
    float k_ccft_oncoming_spd_max = -3;
    float k_csta_oncoming_spd_max = -3;
    float k_csta_fromself_spd_max =  3;
    float k_cpta_oncoming_spd_max = -0.8;
    float k_cpta_fromself_spd_max =  0.8;
    float k_turn_left_radius = 70;
    float k_turn_right_radius = -70;

    
    //ccft
    std::array<float, 3> ccft_obj_speed = {5.56, 11.11, 13.89};
    std::array<float, 3> ccft_ego_speed = {2.78, 5.56, 8.33};
    std::array<std::array<float, 3>, 3> ccft_width_offset = {
        {{0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}}};
    std::array<std::array<float, 3>, 3> ccft_length_offset = {
        {{0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}}};

    //cpta
    std::array<float, 3> cpta_obj_speed = {0.0,  1.39, 1.80};
    std::array<float, 3> cpta_ego_speed = {2.78, 5.56, 8.33};
    std::array<std::array<float, 3>, 3> cpta_ln_width_offset = {
        {{0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}}};
    std::array<std::array<float, 3>, 3> cpta_lf_width_offset = {
        {{0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}}};
    std::array<std::array<float, 3>, 3> cpta_rf_width_offset = {
        {{0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}}};
    std::array<std::array<float, 3>, 3> cpta_ln_length_offset = {
        {{0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}}};
    std::array<std::array<float, 3>, 3> cpta_lf_length_offset = {
        {{0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}}};
    std::array<std::array<float, 3>, 3> cpta_rf_length_offset = {
        {{0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}}};

    //csta
    std::array<float, 3> csta_obj_speed = {0.0,  5.55, 8.33};
    std::array<float, 3> csta_ego_speed = {2.78, 5.56, 8.33};
    std::array<std::array<float, 3>, 3> csta_ln_width_offset = {
        {{0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}}};

    std::array<std::array<float, 3>, 3> csta_rn_width_offset = {
           {{0.5, 0.5, 0.4},
            {0.5, 0.5, 0.4},
            {0.5, 0.5, 0.4}}};
    std::array<std::array<float, 3>, 3> csta_ln_length_offset = {
        {{0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}}};

    std::array<std::array<float, 3>, 3> csta_rn_length_offset = {
        {{0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0}}};

};
} // namespace tap
} // namespace senseAD
