
#pragma once

// #include <gflags/gflags.h>

// DECLARE_int32(pnc_x_planning_log_level);
// DECLARE_int32(pnc_x_city_planner_pool_size);

// DECLARE_int32(pnc_x_planning_future_wait_timeout);
// DECLARE_double(pnc_x_planning_zero_threshold);
// DECLARE_double(planner_max_drop_cruising_speed_limit);

// DECLARE_string(pnc_x_planning_folder);
// DECLARE_string(pnc_x_vehicle_model);
// DECLARE_int32(pnc_x_enable_sdk);
// DECLARE_int32(pnc_x_main_target_object_type);
// DECLARE_int32(pnc_x_stalled_obstacle_alert_info);

// DECLARE_double(pnc_x_planning_map_search_heading_limit);
// DECLARE_double(pnc_x_planning_map_minimum_boundary_search_radius);
// DECLARE_double(pnc_x_planning_map_point_distance_threshold);
// DECLARE_double(pnc_x_planning_map_boundary_gap_threshold);
// DECLARE_double(pnc_x_planning_boundary_interpolate_dist);
// DECLARE_uint32(pnc_x_planning_lane_polyline_vector_num);
// DECLARE_uint32(pnc_x_planning_lane_vector_dim);
// DECLARE_uint32(pnc_x_planning_road_boundary_polyline_vector_num);
// DECLARE_uint32(pnc_x_planning_road_boundary_vector_dim);

// DECLARE_uint32(pnc_x_planning_polygon_polyline_vector_num);
// DECLARE_uint32(pnc_x_planning_polygon_polyline_vector_dim);

// DECLARE_double(pnc_x_current_lane_search_dist);
// DECLARE_uint32(pnc_x_planning_max_obstacle_vector_size);
// DECLARE_uint32(pnc_x_planning_dynamic_obstacle_vector_dim);
// DECLARE_uint32(pnc_x_planning_static_obstacle_vector_dim);

// DECLARE_string(pnc_x_planning_test_data);

// DECLARE_bool(pnc_x_use_e2e_planning);
// DECLARE_bool(pnc_x_only_use_e2e_planning);

// DECLARE_string(pnc_x_city_config);
// DECLARE_string(pnc_x_vehicle_params_path);
// DECLARE_string(pnc_x_trigger_config);

// DECLARE_double(pnc_x_local_speed_0);
// DECLARE_double(pnc_x_local_speed_30);
// DECLARE_double(pnc_x_local_speed_40);
// DECLARE_double(pnc_x_local_speed_50);
// DECLARE_double(pnc_x_local_speed_60);
// DECLARE_double(pnc_x_local_speed_70);
// DECLARE_double(pnc_x_local_speed_80);
// DECLARE_double(pnc_x_local_speed_90);
// DECLARE_double(pnc_x_local_speed_100);
// DECLARE_double(pnc_x_local_speed_110);
// DECLARE_double(pnc_x_local_speed_120);
// DECLARE_double(pnc_x_local_speed_130);
// DECLARE_double(pnc_x_local_speed_140);
// DECLARE_bool(pnc_x_speed_mapping_voyafree_enalbe);
// DECLARE_bool(pnc_x_dynamic_speed_mapping_mix_car_enalbe);

// DECLARE_bool(pnc_x_use_astar_search_algorithm);
// DECLARE_bool(planner_dumping_astar_search_process);
// DECLARE_bool(planner_enable_astar_search_visualize);

// DECLARE_int32(planner_search_fail_level);
// DECLARE_bool(planner_print_search_info);

// DECLARE_int32(pnc_x_fvsr_result);

#include <string>
#include <cstdint>

extern int FLAGS_pnc_x_planning_log_level;
extern double FLAGS_planner_max_drop_cruising_speed_limit;

extern int FLAGS_pnc_x_city_planner_pool_size;

extern int FLAGS_pnc_x_planning_future_wait_timeout;
extern double FLAGS_pnc_x_planning_zero_threshold;

extern std::string FLAGS_pnc_x_planning_folder;
extern std::string FLAGS_pnc_x_vehicle_model;
extern int FLAGS_pnc_x_enable_sdk;
extern int FLAGS_pnc_x_stalled_obstacle_alert_info;
extern int FLAGS_pnc_x_main_target_object_type;

extern bool FLAGS_pnc_x_use_e2e_planning;
extern bool FLAGS_pnc_x_only_use_e2e_planning;

extern double FLAGS_pnc_x_planning_map_search_heading_limit;
extern double FLAGS_pnc_x_planning_map_minimum_boundary_search_radius;
extern double FLAGS_pnc_x_planning_map_point_distance_threshold;
extern double FLAGS_pnc_x_planning_map_boundary_gap_threshold;
extern double FLAGS_pnc_x_planning_boundary_interpolate_dist;
extern double FLAGS_pnc_x_planning_boundary_gap_threshold;

extern uint32_t FLAGS_pnc_x_planning_lane_polyline_vector_num;
extern uint32_t FLAGS_pnc_x_planning_lane_vector_dim;
extern uint32_t FLAGS_pnc_x_planning_road_boundary_polyline_vector_num;
extern uint32_t FLAGS_pnc_x_planning_road_boundary_vector_dim;
extern uint32_t FLAGS_pnc_x_planning_polygon_polyline_vector_num;
extern uint32_t FLAGS_pnc_x_planning_polygon_polyline_vector_dim;

extern double FLAGS_pnc_x_current_lane_search_dist;
extern uint32_t FLAGS_pnc_x_planning_max_obstacle_vector_size;
extern uint32_t FLAGS_pnc_x_planning_dynamic_obstacle_vector_dim;
extern uint32_t FLAGS_pnc_x_planning_static_obstacle_vector_dim;

extern std::string FLAGS_pnc_x_planning_test_data;

extern std::string FLAGS_pnc_x_city_config;
extern std::string FLAGS_pnc_x_vehicle_params_path;

extern double FLAGS_pnc_x_local_speed_0;
extern double FLAGS_pnc_x_local_speed_30;
extern double FLAGS_pnc_x_local_speed_40;
extern double FLAGS_pnc_x_local_speed_50;
extern double FLAGS_pnc_x_local_speed_60;
extern double FLAGS_pnc_x_local_speed_70;
extern double FLAGS_pnc_x_local_speed_80;
extern double FLAGS_pnc_x_local_speed_90;
extern double FLAGS_pnc_x_local_speed_100;
extern double FLAGS_pnc_x_local_speed_110;
extern double FLAGS_pnc_x_local_speed_120;
extern double FLAGS_pnc_x_local_speed_130;
extern double FLAGS_pnc_x_local_speed_140;

extern bool FLAGS_pnc_x_speed_mapping_voyafree_enalbe;
extern bool FLAGS_pnc_x_dynamic_speed_mapping_mix_car_enalbe;

extern bool FLAGS_pnc_x_use_astar_search_algorithm;
extern bool FLAGS_planner_dumping_astar_search_process;
extern bool FLAGS_planner_enable_astar_search_visualize;

extern int FLAGS_pnc_x_fvsr_result;

extern int FLAGS_planner_search_fail_level;
extern bool FLAGS_planner_print_search_info;

extern int FLAGS_mfob_trajectory_smoother_verbosity_level;