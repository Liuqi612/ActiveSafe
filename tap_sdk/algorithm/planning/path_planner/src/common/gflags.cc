

#include "common/gflags.h"

// DEFINE_int32(pnc_x_planning_log_level, 0,
//              "log level, 0 = DEBUG, 1 = INFO, 2 = WARN, 3 = ERROR, 4 =
//              FATAL");
// DEFINE_double(planner_max_drop_cruising_speed_limit, 3.0,
//               "m/s, delete it later.");

// DEFINE_int32(
//     pnc_x_city_planner_pool_size, 1,
//     "The number of threads in the default thread pool for city planner");

// DEFINE_int32(pnc_x_planning_future_wait_timeout, 60,
//              "time for future get timeout in second");
// DEFINE_double(pnc_x_planning_zero_threshold, 1e-6,
//               "zero threshold for pnc_x_planning");

// DEFINE_string(pnc_x_planning_folder, "../", "config parent folder");
// DEFINE_string(pnc_x_vehicle_model, "haibao", "vehicle model");
// DEFINE_int32(pnc_x_enable_sdk, 1, "1 enable, 0 disable");
// DEFINE_int32(
//     pnc_x_stalled_obstacle_alert_info, 0,
//     "Status flag for stalled obstacle alert scenario: "
//     "0 - No stalled obstacle encountered; "
//     "1 - Stalled obstacle encountered in path; "
//     "2 - TTC to stalled obstacle is too small, trigger takeover alert.");
// DEFINE_int32(pnc_x_main_target_object_type, 0,
//              "1 is traffic participant, "
//              "2 is static obstacles like cones, "
//              "3 is road boundaries or others, "
//              "0 is default");

// DEFINE_bool(pnc_x_use_e2e_planning, false, "use e2e planning");
// DEFINE_bool(pnc_x_only_use_e2e_planning, false, "only use e2e planning");

// DEFINE_double(pnc_x_planning_map_search_heading_limit, 1.04719755,
//               "heading limit for search lane by point");
// DEFINE_double(pnc_x_planning_map_minimum_boundary_search_radius, 3.5,
//               "minimun search radius for searching lane");
// DEFINE_double(pnc_x_planning_map_point_distance_threshold, 0.01,
//               "skip map point by distance (between two map points)");
// DEFINE_double(pnc_x_planning_map_boundary_gap_threshold, 1.0,
//               "distance of gap between two boundaries");
// DEFINE_double(pnc_x_planning_boundary_interpolate_dist, 1.0,
//               "The distance for boundary interpolate");
// DEFINE_uint32(pnc_x_planning_lane_polyline_vector_num, 32,
//               "Number of lane/boundary polyline vector size");
// DEFINE_uint32(pnc_x_planning_lane_vector_dim, 24, "dimension of lane
// vector");

// DEFINE_uint32(pnc_x_planning_road_boundary_polyline_vector_num, 32,
//               "Number of road_boundary polyline vector size");
// DEFINE_uint32(pnc_x_planning_road_boundary_vector_dim, 16,
//               "dimension of road boundary vector");

// DEFINE_uint32(pnc_x_planning_polygon_polyline_vector_num, 32,
//               "Number of polygon(crosswalk/junction) polyline vector size");
// DEFINE_uint32(pnc_x_planning_polygon_polyline_vector_dim, 8,
//               "dimension of polygon polyline vector");

// DEFINE_double(pnc_x_current_lane_search_dist, 20,
//               "lane search distance for osbtacle current lane");
// DEFINE_uint32(pnc_x_planning_max_obstacle_vector_size, 20,
//               "max number of obstacle vector size");
// DEFINE_uint32(pnc_x_planning_dynamic_obstacle_vector_dim, 24,
//               "dynamic obstacle vector dimension");
// DEFINE_uint32(pnc_x_planning_static_obstacle_vector_dim, 8,
//               "static obstacle vector dimension");

// DEFINE_string(pnc_x_planning_test_data, "test/", "test data path");

// DEFINE_string(pnc_x_city_config, "conf/", "config for city plannner");
// DEFINE_string(pnc_x_vehicle_params_path, "vehicle_params.pb.txt",
//               "vehicle params file suffix");

// DEFINE_double(pnc_x_local_speed_0, 0.0, "plan_local_speed_0");
// DEFINE_double(pnc_x_local_speed_30, 7.94, "plan_local_speed_30");
// DEFINE_double(pnc_x_local_speed_40, 10.58, "plan_local_speed_40");
// DEFINE_double(pnc_x_local_speed_50, 13.23, "plan_local_speed_50");
// DEFINE_double(pnc_x_local_speed_60, 15.87, "plan_local_speed_60");
// DEFINE_double(pnc_x_local_speed_70, 18.79, "plan_local_speed_70");
// DEFINE_double(pnc_x_local_speed_80, 21.48, "plan_local_speed_80");
// DEFINE_double(pnc_x_local_speed_90, 24.18, "plan_local_speed_90");
// DEFINE_double(pnc_x_local_speed_100, 26.87, "plan_local_speed_100");
// DEFINE_double(pnc_x_local_speed_110, 29.57, "plan_local_speed_110");
// DEFINE_double(pnc_x_local_speed_120, 32.27, "plan_local_speed_120");
// DEFINE_double(pnc_x_local_speed_130, 34.97, "plan_local_speed_130");
// DEFINE_double(pnc_x_local_speed_140, 37.67, "plan_local_speed_140");
// DEFINE_bool(pnc_x_speed_mapping_voyafree_enalbe, true,
//             "pnc_x_speed_mapping_voyafree_enalbe");
// DEFINE_bool(pnc_x_dynamic_speed_mapping_mix_car_enalbe, true,
//             "pnc_x_dynamic_speed_mapping_mix_car_enalbe");

// DEFINE_bool(pnc_x_use_astar_search_algorithm, true,
//             "pnc_x_use_astar_search_algorithm");
// DEFINE_bool(planner_dumping_astar_search_process, false,
//             "Whether reading and dumping astar search process data");
// DEFINE_bool(planner_enable_astar_search_visualize, false,
//             "whether enable astar search 3d visualize");

// DEFINE_int32(pnc_x_fvsr_result, 0, "pnc_x_fvsr_result");

// DEFINE_int32(planner_search_fail_level, 0, "choose search fail log level");
// DEFINE_bool(planner_print_search_info, false,
//             "if enable, open search info debug");

int FLAGS_pnc_x_planning_log_level = 0;
double FLAGS_planner_max_drop_cruising_speed_limit = 3.0;

int FLAGS_pnc_x_city_planner_pool_size = 1;

int FLAGS_pnc_x_planning_future_wait_timeout = 60;
double FLAGS_pnc_x_planning_zero_threshold = 1e-6;

std::string FLAGS_pnc_x_planning_folder = "../";
std::string FLAGS_pnc_x_vehicle_model = "haibao";
int FLAGS_pnc_x_enable_sdk = 1;
int FLAGS_pnc_x_stalled_obstacle_alert_info = 0;
int FLAGS_pnc_x_main_target_object_type = 0;

bool FLAGS_pnc_x_use_e2e_planning = false;
bool FLAGS_pnc_x_only_use_e2e_planning = false;

double FLAGS_pnc_x_planning_map_search_heading_limit = 1.04719755;
double FLAGS_pnc_x_planning_map_minimum_boundary_search_radius = 3.5;
double FLAGS_pnc_x_planning_map_point_distance_threshold = 0.01;
double FLAGS_pnc_x_planning_map_boundary_gap_threshold = 1.0;
double FLAGS_pnc_x_planning_boundary_interpolate_dist = 1.0;
double FLAGS_pnc_x_planning_boundary_gap_threshold = 1.0;

uint32_t FLAGS_pnc_x_planning_lane_polyline_vector_num = 32;
uint32_t FLAGS_pnc_x_planning_lane_vector_dim = 24;
uint32_t FLAGS_pnc_x_planning_road_boundary_polyline_vector_num = 32;
uint32_t FLAGS_pnc_x_planning_road_boundary_vector_dim = 16;
uint32_t FLAGS_pnc_x_planning_polygon_polyline_vector_num = 32;
uint32_t FLAGS_pnc_x_planning_polygon_polyline_vector_dim = 8;

double FLAGS_pnc_x_current_lane_search_dist = 20;
uint32_t FLAGS_pnc_x_planning_max_obstacle_vector_size = 20;
uint32_t FLAGS_pnc_x_planning_dynamic_obstacle_vector_dim = 24;
uint32_t FLAGS_pnc_x_planning_static_obstacle_vector_dim = 8;

std::string FLAGS_pnc_x_planning_test_data = "test/";

std::string FLAGS_pnc_x_city_config = "conf/";
std::string FLAGS_pnc_x_vehicle_params_path = "vehicle_params.pb.txt";

double FLAGS_pnc_x_local_speed_0 = 0.0;
double FLAGS_pnc_x_local_speed_30 = 7.94;
double FLAGS_pnc_x_local_speed_40 = 10.58;
double FLAGS_pnc_x_local_speed_50 = 13.23;
double FLAGS_pnc_x_local_speed_60 = 15.87;
double FLAGS_pnc_x_local_speed_70 = 18.79;
double FLAGS_pnc_x_local_speed_80 = 21.48;
double FLAGS_pnc_x_local_speed_90 = 24.18;
double FLAGS_pnc_x_local_speed_100 = 26.87;
double FLAGS_pnc_x_local_speed_110 = 29.57;
double FLAGS_pnc_x_local_speed_120 = 32.27;
double FLAGS_pnc_x_local_speed_130 = 34.97;
double FLAGS_pnc_x_local_speed_140 = 37.67;

bool FLAGS_pnc_x_speed_mapping_voyafree_enalbe = true;
bool FLAGS_pnc_x_dynamic_speed_mapping_mix_car_enalbe = true;

bool FLAGS_pnc_x_use_astar_search_algorithm = true;
bool FLAGS_planner_dumping_astar_search_process = false;
bool FLAGS_planner_enable_astar_search_visualize = false;

int FLAGS_pnc_x_fvsr_result = 0;

int FLAGS_planner_search_fail_level = 0;
bool FLAGS_planner_print_search_info = false;

int FLAGS_mfob_trajectory_smoother_verbosity_level = 0;