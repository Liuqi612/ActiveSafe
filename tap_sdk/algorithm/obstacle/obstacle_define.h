#pragma once
#include <array>
namespace active_safety {


struct AsObstacleCal {
  bool k_ignore_barrier_check = false;

  float k_ped_width_max = 0.5;
  float k_anim_width_max = 2.0;
  float k_gen_obj_width_max = 2.0;
  float k_motorcycle_width_max = 0.7;
  float k_truck_width_max = 2.6;
  float k_car_width_max = 2.2;

  float k_ped_width_min = 0.5;
  float k_anim_width_min = 0.5;
  float k_gen_obj_width_min = 0.2;
  float k_motorcycle_width_min = 0.5;
  float k_truck_width_min = 1.5;
  float k_car_width_min = 1.8;

  float k_motorcycle_max_a_lgt = 3.0;
  float k_truck_max_a_lgt = 1.5;
  float k_car_max_a_lgt = 3.0;
  float k_veh_unkwn_type_max_a_lgt = 2.0;

  float k_max_value_for_self_dev = 1000000.0;
  float k_max_curv = 0.2;

  float k_ped_length = 0.4;
  float k_anim_length = 2.5;
  float k_obj_length = 1.0;
};

} // namespace active_safety
