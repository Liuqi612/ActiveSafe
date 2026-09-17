

#include "plan/planner_flags.h"

// DEFINE_int32(planner_debug, 0, "How much do you want to debug me?");

// DEFINE_int32(planner_thread_pool_size, 3, "Planner thread pool size.");

// DEFINE_double(planner_lateral_reset_error, 0.7,
//               "Lateral reset error for EstPlanner.");

// DEFINE_double(planner_max_allowed_iteration_time, 0.45,
//               "The maximum allowed planner iteration time in seconds.");

// DEFINE_double(planner_max_localization_transform_delay, 5.0,
//               "The max delay allowed to use a localization transform
//               message.");
// DEFINE_double(planner_max_perception_delay, 3.0,
//               "The max delay allowed for perception message.");
// DEFINE_double(planner_max_pose_delay, 0.1,
//               "The max delay allowed for pose message in seconds.");

// DEFINE_bool(planner_allow_async_in_main_thread, true,
//             "Whether to allow async operations in planner\'s main thread.");

// DEFINE_bool(planner_allow_multi_threads_in_est, true,
//             "Whether to allow multiple threads in est-planner.");

// DEFINE_bool(planner_multi_est_in_parallel, true,
//             "Whether to run multiple est-planners in parallel.");

// DEFINE_bool(
//     planner_consider_objects, true,
//     "Planner consider objects in perception and prediction. This is "
//     "useful for testing mode that does not have perception or prediction.");

// DEFINE_double(
//     planner_check_trajectory_engage_condition_duration, 1.0,
//     "Validate if we can engage in the trajectory's first this amount of
//     time.");

// DEFINE_double(
//     planner_filter_reflected_object_distance, 0.3,
//     "Filter reflected objects that in AV's current position's proximity and "
//     "the distance to SDC is less than this value (in meters). Reflected "
//     "objects are fake unknown stationary perception objects "
//     "that are near SDC body. When this value is less than zero, we "
//     "will not filter reflected object.");

// DEFINE_int32(planner_lookforward_time_ms, 200,
//              "The planner look forward time when computing trajectory.");

// DEFINE_double(planner_prediction_probability_threshold, 0.1,
//               "The threshold on probability below which a predicted behavior
//               / " "trajectory will be ignored (use at your risk)");

// DEFINE_uint32(
//     planner_low_confidence_lv_threshold, 1,
//     "The threshold on confidence level below and equal which an object"
//     "will be ignored (use at your risk)");

// DEFINE_bool(planner_only_use_most_likely_trajectory, false,
//             "Only use the most likely trajectory.");

// DEFINE_bool(planner_open_door_at_route_end, false,
//             "Open door when AV is at end of route and fully stopped.");

// DEFINE_double(
//     planner_door_state_override_waiting_time, 40.0,
//     "Don't change door state for so many seconds after door state override. "
//     "This value should be less than the duration for the AV to travel from
//     one " "station to another. This is used to prevent software open door "
//     "immediately after driver closed the door.");

// DEFINE_bool(planner_regard_green_flashing_as_green, true,
//             "Regard green flashing light as green light.");

// DEFINE_bool(planner_enable_occluded_objects_inference, true,
//             "Enable reasoning occluded objects according sensor fov.");
// DEFINE_bool(
//     planner_enable_crosswalk_occluded_objects_inference, false,
//     "Enable reasoning occluded objects according sensor fov on crosswalks.");

// DEFINE_bool(
//     planner_ignore_stalled_objects_on_tl_controlled_leftmost_lane, false,
//     " Don't make stalled object decision for  objects on left most lane");

// DEFINE_bool(
//     planner_enable_un_tl_controlled_intersection_reasoning, true,
//     "Enable scene reasoning on un traffic light controlled intersection.");

// DEFINE_int32(
//     planner_task_init_type, 1,
//     "0: NOA only; 1:Dynamic switch; 2: ACC only; 3:LCC only; 4:Mapless NOA");

// DEFINE_bool(planner_export_all_prediction_to_speed_considered, false,
//             "Whether to send all time-aligned predictions to speed considered
//             " "prediction. Set it true only for simulation debugging
//             purpose.");

// DEFINE_bool(planner_check_aeb, true, "Whether to check emergency stop.");

// DEFINE_bool(planner_publish_chart_data, true,
//             "Whether to publish charts data proto.");

// DEFINE_bool(planner_simplify_debug_proto, false,
//             "Only return limited fields in planenr debug proto if true.");

// DEFINE_int32(planner_running_platform, 0, "0: IPC; 1: Orin; 2: X9");

// DEFINE_int32(
//     planner_est_parallel_branch_num, 2,
//     "The maximal amount of target lane paths to be generated for multi-task "
//     "est planner. Note that a borrow-lane branch will be created if this flag
//     " "is set to 1, so if only one branch is desired, you should also set the
//     " "next flag to false to prohibit lane borrowing.");
// DEFINE_bool(planner_est_scheduler_seperate_lc_pause, false,
//             "Whether to create a seperate lc pause scheduler branch along
//             with " "a lc executing branch.");
// DEFINE_bool(planner_est_scheduler_allow_borrow, true,
//             "Whether to allow a borrow path boundary if only one target lane
//             " "is chosen.");
// DEFINE_bool(planner_send_lane_graph_to_canvas, false,
//             "Whether to send lane graph to canvas.");
// DEFINE_bool(planner_consider_all_lanes_virtual, false,
//             "Whether to consider all lanes\' type as VIRTUAL, for scenarios "
//             "with one single lane for mixed use.");

// DEFINE_int32(planner_initializer_debug_level, 0,
//              "Initializer debug level: 0: Nothing; 1: Debug info for world "
//              "renderer; 2: Debug info for canvas and terminal.");
// DEFINE_bool(planner_initializer_only_activate_nodes_near_capnet_traj, false,
//             "Only activate geometry nodes near the reference traj provided by
//             " "captain net for motion search.");
// DEFINE_bool(
//     planner_initializer_only_activate_nodes_near_refline, false,
//     "Only activate geometry nodes near the reference line for motion
//     search.");
// DEFINE_int32(
//     planner_initializer_max_multi_traj_num, 3,
//     "The maximal amount of leading groups that should be considered for "
//     "initializer multiple trajectory selection in certain situations.");
// DEFINE_bool(planner_initializer_enable_post_evaluation, false,
//             "Whether to re-evaluate the top k trajectories from the
//             hand-tuned " "initializer params with learned params and select
//             the best as the " "final output.");
// DEFINE_bool(planner_initializer_enable_clip, true,
//             "Whether to enable to clip initializer for faster calculation.");

// DEFINE_bool(
//     planner_dumping_initializer_features, false,
//     "Whether reading and dumping initializer features' cost of manual driving
//     " "trajectory for offline learning");

// DEFINE_bool(
//     planner_dumping_selector_features, false,
//     "Whether reading and dumping selector features' cost of manual driving "
//     "trajectory for offline learning");

// DEFINE_bool(planner_filter_selector_intention, false,
//             "Whether filtering the selector features dumping based on if
//             their " "intentions are same as expert. Only work when "
//             "planner_dumping_selector_features is true.");

// DEFINE_bool(
//     planner_dumping_ml_data_in_simulation, false,
//     "Whether to use oracle trajectory and dump data for ml to
//     planner_debug");

// DEFINE_bool(planner_st_traj_mgr_use_all, false,
//             "Spacetime trajectory manager uses all objects and
//             trajectories.");

// DEFINE_bool(planner_auto_tuning_mode, false,
//             "When auto tuning mode is on, the optimizer will generate and
//             save " "one more output which are the accumulated discounted
//             costs for " "different cost type.");
// DEFINE_bool(planner_optimizer_data_cleaning, false,
//             "Whether to do data cleaning/filtering for optimizer and run "
//             "snapshot in optimizer data cleaning mode.");
// DEFINE_bool(
//     planner_update_learned_alphas, false,
//     "Whether to use the cost weight alphas learned in auto tuning mode.");
// DEFINE_bool(
//     planner_update_learned_alphas_except_lane_change, true,
//     "Whether to use the cost weight alphas learned in auto tuning mode when "
//     "lane change. Only worked when planner_update_learned_alphas is true. So
//     " "this will " "not influence training process but will influence "
//     "evaluation/validation/testing.");
// DEFINE_string(planner_traj_opt_params_file_address,
//               "./config/compared_trajectory_optimizer_params.pb.txt",
//               "The address of the trajectory optimizer params proto file.");
// DEFINE_bool(
//     planner_compare_different_weight, false,
//     "Whether to compare different cost weight learned in auto tuning mode.");
// DEFINE_bool(planner_compare_based_on_original_weight, false,
//             "Whether to compare the cost weight based on original cost "
//             "weight(true) or auto tuned cost weight(false), only works when "
//             "planner_compare_different_weight is true.");

// DEFINE_bool(planner_use_tuned_selector_params, false,
//             "Whether to use the auto tuned selector cost weight params.");
// DEFINE_string(
//     planner_selector_params_file_address,
//     "offboard/planner/ml/models/selector_auto_tuning/selector_params.pb.txt",
//     "The address of the auto tuned selector params proto file.");

// DEFINE_int32(planner_drive_passage_debug_level, 0,
//              "Debug level for drive passage: 0: no debug info; "
//              "1: send to canvas for viz; 2: some other options)");
// DEFINE_double(planner_path_start_point_time_diff_limit, 0.5,
//               "If relative time of closest point on prev traj from plan "
//               "start point larger than this time, set path plan start point
//               to " "current close point.");
// DEFINE_bool(
//     planner_enable_path_start_point_look_ahead, true,
//     "Whether to use logic about planner_path_start_point_time_diff_limit.");
// DEFINE_int32(planner_local_lane_map_debug_level, 0,
//              "Debug level for local lane map: 0: no debug info; 1: send to "
//              "canvas for viz; 2: some other options");

// DEFINE_int32(planner_runtime_uturn_level, 1,
//              "0: Disable three point turn by force; 1: Enable by params; 2: "
//              "Enable by force.");

// DEFINE_bool(planner_enable_dynamic_lane_speed_limit, true,
//             "Whether to enable dynamic lane speedlimit");

// DEFINE_double(planner_override_lane_speed_limit_proportion, 0.0,
//               "Modify lane speed limit by a given proportion");


// DEFINE_bool(planner_rebuild_route_navi_info, false,
//             "alway rebuild route navi info in snapshot");

// DEFINE_bool(planner_enable_lane_change_in_intersection, true,
//             "whether to allow lane change in intersection");
// DEFINE_bool(planner_enable_cross_solid_boundary, false,
//             "whether to allow cross solid boundary");
// DEFINE_int32(planner_begin_lane_change_frame, 3,
//              "Can not change until lane change trajectory is better than "
//              "lane keep trajectory in successive frames");

// DEFINE_int32(planner_begin_signal_frame, 5,
//              "Turn pre lane change when lane change trajectory is better than
//              " "lane keep trajectory in successive frames");
// DEFINE_int32(planner_begin_signal_frame_city_noa, 2,
//              "Turn pre lane change when lane change trajectory is better than
//              " "lane keep trajectory in successive frames");
// DEFINE_int32(
//     planner_begin_lane_change_frame_progress, 20,
//     "Can not change until lane change trajectory is better than "
//     "lane keep trajectory in successive frames when lc reason is progress");
// DEFINE_int32(
//     planner_begin_lane_change_frame_progress_city_noa, 5,
//     "Can not change until lane change trajectory is better than "
//     "lane keep trajectory in successive frames when lc reason is progress");
// DEFINE_double(planner_allow_lc_time_after_activate_selector, 3.0,
//               "After activating selector, how long lane change is allowed");

// DEFINE_double(planner_allow_lc_time_after_give_up_lc, 15.0,
//               "After lc giving up,how long lane change is allowed");

// DEFINE_double(planner_allow_opposite_lc_time_after_paddle_lc, 30.0,
//               "After paddle lc, how long opposite lane change is allowed");
// DEFINE_int32(planner_begin_radical_lane_change_frame, 5,
//              "In certain situations, accelerate lane change decision.");
// DEFINE_double(planner_max_allow_lc_time_before_give_up, 15.0,
//               "How long is maximum allowed duration for a lane change");
// DEFINE_bool(
//     planner_enable_safe_invariance_supervisor_debug, true,
//     "If enabled, safe invariance supervisor will run with rich debug info, "
//     "which may slow down the overall performance.");

// DEFINE_bool(
//     planner_safe_invariance_supervisor_consider_curb, true,
//     "If enabled, safe invariance supervisor will consider curb in general.");
// DEFINE_bool(planner_safe_invariance_supervisor_path_follow_lane, true,
//             "If enabled,  safe invariance supervisor reshape path according
//             to " "lane info.");

// DEFINE_bool(
//     planner_safe_invariance_supervisor_skip_m, false,
//     "If enabled, safe invariance supervisor will not run harmony result.");

// DEFINE_bool(planner_safe_invariance_problem_consider_kgr, false,
//             "If enabled, safe invariance problem respect adv's KGR.");
// DEFINE_int32(planner_safe_invariance_canvas_level, 0,
//              "Canvas level of safe invariance problem.");

// DEFINE_bool(
//     planner_enable_cross_iteration_tf, true,
//     "Whether to enable cross-interation smooth coordinate transformation to "
//     "compensate for smooth coordinate origin drift.");

// DEFINE_bool(planner_force_no_map, false, "Force to not use map.");

// DEFINE_bool(planner_enable_lc_style_params, true,
//             "Whether to enable stylistic planner params in lc.");

// DEFINE_bool(planner_enable_lc_dynamic_headway_time_params, true,
//             "Whether to enable dynamic headway time modify in lc.");
// DEFINE_double(planner_dynamic_headway_time_increase, 0.01,
//               "plan dynamic headway time increase");
// DEFINE_double(planner_dynamic_headway_time_decrease, -0.2,
//               "plan dynamic headway time decrease");

// DEFINE_bool(planner_enable_acc_loss_cipv_acceleration, true,
//             "enable acc cipv loss acceleration");

// DEFINE_double(planner_paddle_lane_change_max_prepare_time, 6.0,
//               "Max allowed duration for staying in ALC_PREPARE state after "
//               "having triggered paddle lane change.");

// DEFINE_bool(
//     planner_st_path_planner_lookahead_for_trajectory_optimizer_synchronization,
//     true,
//     "When enabled, st path planner start point will be further prolonged.");

// DEFINE_bool(planner_traj_opt_init_traj_uses_last_optimized_trajectory, true,
//             "If enabled, optimizer will try to "
//             "use last optimized trajectory as its init solution.");

// DEFINE_bool(planner_force_route_filtered_smm, false,
//             "if enabled, filter elements in smm with route.");

// DEFINE_bool(planner_mapless_status, false, "check whether mapless status");

// DEFINE_bool(lon_decision_enable_use_game_theory, false,
//             "if enable, use game theory");
// DEFINE_bool(
//     replay_timestamp_enable, false,
//     "if enable, use observedtimestamp of localization as plan_start_time");

// DEFINE_double(planner_ego_back_distance_to_look_at_object, 0.0,
//               "The distance of look at object to evade in advance, which is "
//               "set from the object position.");
// DEFINE_double(planner_speed_ratio_of_evaded_object_to_ego_speed, 0.3,
//               "The ratio of the object speed to the ego one.");

// DEFINE_bool(planner_enable_traffic_jam_state_keeping, true,
//             "if enable, when traffic jam state keeping, thw * 0.95");
// DEFINE_double(planner_k_thw_traffic_jam_keeping, 0.95,
//               "traffic jam keeping thw scale factor");
// DEFINE_double(planner_k_accel_comfort_drive_style, 0.95,
//               "comfortable drive style k_accel");
// DEFINE_double(planner_k_accel_normal_drive_style, 1.0,
//               "normal drive style k_accel");
// DEFINE_double(planner_k_accel_effic_drive_style, 1.2,
//               "efficient drive style k_accel");
// DEFINE_double(planner_mrc_slow_down_decel, -1.5, "mrc slow down decel");
// DEFINE_double(planner_mrc_slow_down_jerk, -1.5, "mrc slow down jerk");

int FLAGS_planner_debug = 0;
int FLAGS_planner_thread_pool_size = 3;
double FLAGS_planner_lateral_reset_error = 0.7;
double FLAGS_planner_max_allowed_iteration_time = 0.45;
double FLAGS_planner_max_localization_transform_delay = 5.0;
double FLAGS_planner_max_perception_delay = 3.0;
double FLAGS_planner_max_pose_delay = 0.1;
bool FLAGS_planner_allow_async_in_main_thread = true;
bool FLAGS_planner_allow_multi_threads_in_est = true;
bool FLAGS_planner_multi_est_in_parallel = true;
bool FLAGS_planner_consider_objects = true;
double FLAGS_planner_check_trajectory_engage_condition_duration = 1.0;
double FLAGS_planner_filter_reflected_object_distance = 0.3;
int FLAGS_planner_lookforward_time_ms = 200;
double FLAGS_planner_prediction_probability_threshold = 0.1;
uint32_t FLAGS_planner_low_confidence_lv_threshold = 1;
bool FLAGS_planner_only_use_most_likely_trajectory = false;
bool FLAGS_planner_open_door_at_route_end = false;
double FLAGS_planner_door_state_override_waiting_time = 40.0;
bool FLAGS_planner_regard_green_flashing_as_green = true;
bool FLAGS_planner_enable_occluded_objects_inference = true;
bool FLAGS_planner_enable_crosswalk_occluded_objects_inference = false;
bool FLAGS_planner_ignore_stalled_objects_on_tl_controlled_leftmost_lane =
    false;
bool FLAGS_planner_enable_un_tl_controlled_intersection_reasoning = true;
int FLAGS_planner_task_init_type = 1;
bool FLAGS_planner_export_all_prediction_to_speed_considered = false;
bool FLAGS_planner_check_aeb = true;
bool FLAGS_planner_publish_chart_data = true;
bool FLAGS_planner_simplify_debug_proto = false;
int FLAGS_planner_running_platform = 0;
int FLAGS_planner_est_parallel_branch_num = 2;
bool FLAGS_planner_est_scheduler_seperate_lc_pause = false;
bool FLAGS_planner_est_scheduler_allow_borrow = true;
bool FLAGS_planner_send_lane_graph_to_canvas = false;
bool FLAGS_planner_consider_all_lanes_virtual = false;
int FLAGS_planner_initializer_debug_level = 0;
bool FLAGS_planner_initializer_only_activate_nodes_near_capnet_traj = false;
bool FLAGS_planner_initializer_only_activate_nodes_near_refline = false;
int FLAGS_planner_initializer_max_multi_traj_num = 3;
bool FLAGS_planner_initializer_enable_post_evaluation = false;
bool FLAGS_planner_initializer_enable_clip = true;
bool FLAGS_planner_dumping_initializer_features = false;
bool FLAGS_planner_dumping_selector_features = false;
bool FLAGS_planner_filter_selector_intention = false;
bool FLAGS_planner_dumping_ml_data_in_simulation = false;
bool FLAGS_planner_st_traj_mgr_use_all = false;
bool FLAGS_planner_auto_tuning_mode = false;
bool FLAGS_planner_optimizer_data_cleaning = false;
bool FLAGS_planner_update_learned_alphas = false;
bool FLAGS_planner_update_learned_alphas_except_lane_change = true;
std::string FLAGS_planner_traj_opt_params_file_address =
    "./config/compared_trajectory_optimizer_params.pb.txt";
bool FLAGS_planner_compare_different_weight = false;
bool FLAGS_planner_compare_based_on_original_weight = false;
bool FLAGS_planner_use_tuned_selector_params = false;
std::string FLAGS_planner_selector_params_file_address =
    "offboard/planner/ml/models/selector_auto_tuning/selector_params.pb.txt";
int FLAGS_planner_drive_passage_debug_level = 0;
double FLAGS_planner_path_start_point_time_diff_limit = 0.5;
bool FLAGS_planner_enable_path_start_point_look_ahead = true;
int FLAGS_planner_local_lane_map_debug_level = 0;
int FLAGS_planner_runtime_uturn_level = 1;
bool FLAGS_planner_enable_dynamic_lane_speed_limit = true;
double FLAGS_planner_override_lane_speed_limit_proportion = 0.0;
bool FLAGS_planner_rebuild_route_navi_info = false;
bool FLAGS_planner_enable_lane_change_in_intersection = true;
bool FLAGS_planner_enable_cross_solid_boundary = false;
int FLAGS_planner_begin_lane_change_frame = 3;
int FLAGS_planner_begin_signal_frame = 5;
int FLAGS_planner_begin_signal_frame_city_noa = 2;
int FLAGS_planner_begin_lane_change_frame_progress = 20;
int FLAGS_planner_begin_lane_change_frame_progress_city_noa = 5;
double FLAGS_planner_allow_lc_time_after_activate_selector = 3.0;
double FLAGS_planner_allow_lc_time_after_give_up_lc = 15.0;
double FLAGS_planner_allow_opposite_lc_time_after_paddle_lc = 30.0;
int FLAGS_planner_begin_radical_lane_change_frame = 5;
double FLAGS_planner_max_allow_lc_time_before_give_up = 15.0;
bool FLAGS_planner_enable_safe_invariance_supervisor_debug = true;
bool FLAGS_planner_safe_invariance_supervisor_consider_curb = true;
bool FLAGS_planner_safe_invariance_supervisor_path_follow_lane = true;
bool FLAGS_planner_safe_invariance_supervisor_skip_m = false;
bool FLAGS_planner_safe_invariance_problem_consider_kgr = false;
int FLAGS_planner_safe_invariance_canvas_level = 0;
bool FLAGS_planner_enable_cross_iteration_tf = true;
bool FLAGS_planner_force_no_map = false;
bool FLAGS_planner_enable_lc_style_params = true;
bool FLAGS_planner_enable_lc_dynamic_headway_time_params = true;
double FLAGS_planner_dynamic_headway_time_increase = 0.01;
double FLAGS_planner_dynamic_headway_time_decrease = -0.2;
bool FLAGS_planner_enable_acc_loss_cipv_acceleration = true;
double FLAGS_planner_paddle_lane_change_max_prepare_time = 6.0;
bool
    FLAGS_planner_st_path_planner_lookahead_for_trajectory_optimizer_synchronization =
        true;
bool FLAGS_planner_traj_opt_init_traj_uses_last_optimized_trajectory = true;
bool FLAGS_planner_force_route_filtered_smm = false;
bool FLAGS_planner_mapless_status = false;
bool FLAGS_lon_decision_enable_use_game_theory = false;
bool FLAGS_replay_timestamp_enable = false;
double FLAGS_planner_ego_back_distance_to_look_at_object = 0.0;
double FLAGS_planner_speed_ratio_of_evaded_object_to_ego_speed = 0.3;
bool FLAGS_planner_enable_traffic_jam_state_keeping = true;
double FLAGS_planner_k_thw_traffic_jam_keeping = 0.95;
double FLAGS_planner_k_accel_comfort_drive_style = 0.95;
double FLAGS_planner_k_accel_normal_drive_style = 1.0;
double FLAGS_planner_k_accel_effic_drive_style = 1.2;
double FLAGS_planner_mrc_slow_down_decel = -1.5;
double FLAGS_planner_mrc_slow_down_jerk = -1.5;
