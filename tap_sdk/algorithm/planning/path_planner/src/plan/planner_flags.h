#pragma once

// #include <gflags/gflags.h>

// DECLARE_int32(planner_debug);

// DECLARE_int32(planner_thread_pool_size);

// DECLARE_double(planner_lateral_reset_error);

// DECLARE_double(planner_max_allowed_iteration_time);

// DECLARE_double(planner_max_localization_transform_delay);
// DECLARE_double(planner_max_perception_delay);
// DECLARE_double(planner_max_pose_delay);

// DECLARE_bool(planner_allow_async_in_main_thread);
// DECLARE_bool(planner_allow_multi_threads_in_est);
// DECLARE_bool(planner_multi_est_in_parallel);

// DECLARE_double(planner_check_trajectory_engage_condition_duration);

// DECLARE_bool(planner_consider_objects);
// DECLARE_double(planner_filter_reflected_object_distance);
// DECLARE_int32(planner_lookforward_time_ms);
// DECLARE_double(planner_prediction_probability_threshold);
// DECLARE_uint32(planner_low_confidence_lv_threshold);
// DECLARE_bool(planner_only_use_most_likely_trajectory);
// DECLARE_int32(planner_task_init_type);
// DECLARE_bool(planner_export_all_prediction_to_speed_considered);
// DECLARE_bool(planner_check_aeb);
// DECLARE_bool(planner_publish_chart_data);
// DECLARE_bool(planner_simplify_debug_proto);

// DECLARE_int32(planner_running_platform);

// DECLARE_bool(planner_dumping_initializer_features);
// DECLARE_bool(planner_dumping_selector_features);
// DECLARE_bool(planner_filter_selector_intention);
// DECLARE_bool(planner_dumping_ml_data_in_simulation);

// DECLARE_bool(planner_open_door_at_route_end);
// DECLARE_double(planner_door_state_override_waiting_time);

// DECLARE_bool(planner_regard_green_flashing_as_green);

// DECLARE_bool(planner_enable_occluded_objects_inference);
// DECLARE_bool(planner_enable_crosswalk_occluded_objects_inference);
// DECLARE_bool(planner_ignore_stalled_objects_on_tl_controlled_leftmost_lane);
// DECLARE_bool(planner_enable_un_tl_controlled_intersection_reasoning);

// DECLARE_int32(planner_est_parallel_branch_num);
// DECLARE_bool(planner_est_scheduler_seperate_lc_pause);
// DECLARE_bool(planner_est_scheduler_allow_borrow);
// DECLARE_bool(planner_send_lane_graph_to_canvas);
// DECLARE_bool(planner_consider_all_lanes_virtual);

// DECLARE_int32(planner_initializer_debug_level);
// DECLARE_bool(planner_initializer_only_activate_nodes_near_capnet_traj);
// DECLARE_bool(planner_initializer_only_activate_nodes_near_refline);
// DECLARE_int32(planner_initializer_max_multi_traj_num);
// DECLARE_bool(planner_initializer_enable_post_evaluation);
// DECLARE_bool(planner_initializer_enable_clip);

// DECLARE_bool(planner_st_traj_mgr_use_all);

// DECLARE_bool(planner_auto_tuning_mode);
// DECLARE_bool(planner_optimizer_data_cleaning);
// DECLARE_bool(planner_update_learned_alphas);
// DECLARE_bool(planner_update_learned_alphas_except_lane_change);
// DECLARE_string(planner_traj_opt_params_file_address);
// DECLARE_bool(planner_compare_different_weight);
// DECLARE_bool(planner_compare_based_on_original_weight);

// DECLARE_bool(planner_use_tuned_selector_params);
// DECLARE_string(planner_selector_params_file_address);

// DECLARE_int32(planner_drive_passage_debug_level);
// DECLARE_double(planner_path_start_point_time_diff_limit);
// DECLARE_bool(planner_enable_path_start_point_look_ahead);
// DECLARE_int32(planner_local_lane_map_debug_level);

// DECLARE_int32(planner_runtime_uturn_level);

// DECLARE_bool(planner_enable_dynamic_lane_speed_limit);

// DECLARE_double(planner_override_lane_speed_limit_proportion);


// DECLARE_bool(planner_rebuild_route_navi_info);

// DECLARE_bool(planner_enable_lane_change_in_intersection);
// DECLARE_bool(planner_enable_cross_solid_boundary);
// DECLARE_int32(planner_begin_lane_change_frame);
// DECLARE_int32(planner_begin_signal_frame);
// DECLARE_int32(planner_begin_signal_frame_city_noa);
// DECLARE_double(planner_allow_lc_time_after_activate_selector);
// DECLARE_double(planner_allow_lc_time_after_give_up_lc);
// DECLARE_double(planner_allow_opposite_lc_time_after_paddle_lc);
// DECLARE_int32(planner_begin_radical_lane_change_frame);
// DECLARE_double(planner_max_allow_lc_time_before_give_up);

// DECLARE_int32(planner_begin_lane_change_frame_progress);
// DECLARE_int32(planner_begin_lane_change_frame_progress_city_noa);

// DECLARE_bool(planner_enable_safe_invariance_supervisor_debug);

// DECLARE_bool(planner_safe_invariance_supervisor_consider_curb);
// DECLARE_bool(planner_safe_invariance_supervisor_path_follow_lane);
// DECLARE_bool(planner_safe_invariance_supervisor_skip_m);
// DECLARE_bool(planner_safe_invariance_problem_consider_kgr);

// DECLARE_int32(planner_safe_invariance_canvas_level);

// DECLARE_bool(planner_enable_cross_iteration_tf);

// DECLARE_bool(planner_force_no_map);

// DECLARE_bool(planner_enable_lc_style_params);

// DECLARE_bool(planner_enable_lc_dynamic_headway_time_params);
// DECLARE_double(planner_dynamic_headway_time_increase);
// DECLARE_double(planner_dynamic_headway_time_decrease);

// DECLARE_bool(planner_enable_acc_loss_cipv_acceleration);

// DECLARE_double(planner_paddle_lane_change_max_prepare_time);

// DECLARE_bool(
//     planner_st_path_planner_lookahead_for_trajectory_optimizer_synchronization);

// DECLARE_bool(planner_traj_opt_init_traj_uses_last_optimized_trajectory);

// DECLARE_bool(planner_force_route_filtered_smm);

// DECLARE_bool(planner_mapless_status);
// DECLARE_bool(lon_decision_enable_use_game_theory);
// DECLARE_bool(replay_timestamp_enable);

// DECLARE_double(planner_ego_back_distance_to_look_at_object);
// DECLARE_double(planner_speed_ratio_of_evaded_object_to_ego_speed);

// DECLARE_bool(planner_enable_traffic_jam_state_keeping);
// DECLARE_double(planner_k_thw_traffic_jam_keeping);
// DECLARE_double(planner_k_accel_comfort_drive_style);
// DECLARE_double(planner_k_accel_normal_drive_style);
// DECLARE_double(planner_k_accel_effic_drive_style);
// DECLARE_double(planner_mrc_slow_down_decel);
// DECLARE_double(planner_mrc_slow_down_jerk);

#include <string>
#include <cstdint>

extern int FLAGS_planner_debug;
extern int FLAGS_planner_thread_pool_size;
extern double FLAGS_planner_lateral_reset_error;
extern double FLAGS_planner_max_allowed_iteration_time;
extern double FLAGS_planner_max_localization_transform_delay;
extern double FLAGS_planner_max_perception_delay;
extern double FLAGS_planner_max_pose_delay;
extern bool FLAGS_planner_allow_async_in_main_thread;
extern bool FLAGS_planner_allow_multi_threads_in_est;
extern bool FLAGS_planner_multi_est_in_parallel;
extern bool FLAGS_planner_consider_objects;
extern double FLAGS_planner_check_trajectory_engage_condition_duration;
extern double FLAGS_planner_filter_reflected_object_distance;
extern int FLAGS_planner_lookforward_time_ms;
extern double FLAGS_planner_prediction_probability_threshold;
extern uint32_t FLAGS_planner_low_confidence_lv_threshold;
extern bool FLAGS_planner_only_use_most_likely_trajectory;
extern bool FLAGS_planner_open_door_at_route_end;
extern double FLAGS_planner_door_state_override_waiting_time;
extern bool FLAGS_planner_regard_green_flashing_as_green;
extern bool FLAGS_planner_enable_occluded_objects_inference;
extern bool FLAGS_planner_enable_crosswalk_occluded_objects_inference;
extern bool FLAGS_planner_ignore_stalled_objects_on_tl_controlled_leftmost_lane;
extern bool FLAGS_planner_enable_un_tl_controlled_intersection_reasoning;
extern int FLAGS_planner_task_init_type;
extern bool FLAGS_planner_export_all_prediction_to_speed_considered;
extern bool FLAGS_planner_check_aeb;
extern bool FLAGS_planner_publish_chart_data;
extern bool FLAGS_planner_simplify_debug_proto;
extern int FLAGS_planner_running_platform;
extern int FLAGS_planner_est_parallel_branch_num;
extern bool FLAGS_planner_est_scheduler_seperate_lc_pause;
extern bool FLAGS_planner_est_scheduler_allow_borrow;
extern bool FLAGS_planner_send_lane_graph_to_canvas;
extern bool FLAGS_planner_consider_all_lanes_virtual;
extern int FLAGS_planner_initializer_debug_level;
extern bool FLAGS_planner_initializer_only_activate_nodes_near_capnet_traj;
extern bool FLAGS_planner_initializer_only_activate_nodes_near_refline;
extern int FLAGS_planner_initializer_max_multi_traj_num;
extern bool FLAGS_planner_initializer_enable_post_evaluation;
extern bool FLAGS_planner_initializer_enable_clip;
extern bool FLAGS_planner_dumping_initializer_features;
extern bool FLAGS_planner_dumping_selector_features;
extern bool FLAGS_planner_filter_selector_intention;
extern bool FLAGS_planner_dumping_ml_data_in_simulation;
extern bool FLAGS_planner_st_traj_mgr_use_all;
extern bool FLAGS_planner_auto_tuning_mode;
extern bool FLAGS_planner_optimizer_data_cleaning;
extern bool FLAGS_planner_update_learned_alphas;
extern bool FLAGS_planner_update_learned_alphas_except_lane_change;
extern std::string FLAGS_planner_traj_opt_params_file_address;
extern bool FLAGS_planner_compare_different_weight;
extern bool FLAGS_planner_compare_based_on_original_weight;
extern bool FLAGS_planner_use_tuned_selector_params;
extern std::string FLAGS_planner_selector_params_file_address;
extern int FLAGS_planner_drive_passage_debug_level;
extern double FLAGS_planner_path_start_point_time_diff_limit;
extern bool FLAGS_planner_enable_path_start_point_look_ahead;
extern int FLAGS_planner_local_lane_map_debug_level;
extern int FLAGS_planner_runtime_uturn_level;
extern bool FLAGS_planner_enable_dynamic_lane_speed_limit;
extern double FLAGS_planner_override_lane_speed_limit_proportion;
extern bool FLAGS_planner_rebuild_route_navi_info;
extern bool FLAGS_planner_enable_lane_change_in_intersection;
extern bool FLAGS_planner_enable_cross_solid_boundary;
extern int FLAGS_planner_begin_lane_change_frame;
extern int FLAGS_planner_begin_signal_frame;
extern int FLAGS_planner_begin_signal_frame_city_noa;
extern int FLAGS_planner_begin_lane_change_frame_progress;
extern int FLAGS_planner_begin_lane_change_frame_progress_city_noa;
extern double FLAGS_planner_allow_lc_time_after_activate_selector;
extern double FLAGS_planner_allow_lc_time_after_give_up_lc;
extern double FLAGS_planner_allow_opposite_lc_time_after_paddle_lc;
extern int FLAGS_planner_begin_radical_lane_change_frame;
extern double FLAGS_planner_max_allow_lc_time_before_give_up;
extern bool FLAGS_planner_enable_safe_invariance_supervisor_debug;
extern bool FLAGS_planner_safe_invariance_supervisor_consider_curb;
extern bool FLAGS_planner_safe_invariance_supervisor_path_follow_lane;
extern bool FLAGS_planner_safe_invariance_supervisor_skip_m;
extern bool FLAGS_planner_safe_invariance_problem_consider_kgr;
extern int FLAGS_planner_safe_invariance_canvas_level;
extern bool FLAGS_planner_enable_cross_iteration_tf;
extern bool FLAGS_planner_force_no_map;
extern bool FLAGS_planner_enable_lc_style_params;
extern bool FLAGS_planner_enable_lc_dynamic_headway_time_params;
extern double FLAGS_planner_dynamic_headway_time_increase;
extern double FLAGS_planner_dynamic_headway_time_decrease;
extern bool FLAGS_planner_enable_acc_loss_cipv_acceleration;
extern double FLAGS_planner_paddle_lane_change_max_prepare_time;
extern bool
    FLAGS_planner_st_path_planner_lookahead_for_trajectory_optimizer_synchronization;
extern bool FLAGS_planner_traj_opt_init_traj_uses_last_optimized_trajectory;
extern bool FLAGS_planner_force_route_filtered_smm;
extern bool FLAGS_planner_mapless_status;
extern bool FLAGS_lon_decision_enable_use_game_theory;
extern bool FLAGS_replay_timestamp_enable;
extern double FLAGS_planner_ego_back_distance_to_look_at_object;
extern double FLAGS_planner_speed_ratio_of_evaded_object_to_ego_speed;
extern bool FLAGS_planner_enable_traffic_jam_state_keeping;
extern double FLAGS_planner_k_thw_traffic_jam_keeping;
extern double FLAGS_planner_k_accel_comfort_drive_style;
extern double FLAGS_planner_k_accel_normal_drive_style;
extern double FLAGS_planner_k_accel_effic_drive_style;
extern double FLAGS_planner_mrc_slow_down_decel;
extern double FLAGS_planner_mrc_slow_down_jerk;
