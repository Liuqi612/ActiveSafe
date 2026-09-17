#ifndef TAP_SDK_ALGORITHM_OBSTACLE_OBSTACLE_DEFINE_H_
#define TAP_SDK_ALGORITHM_OBSTACLE_OBSTACLE_DEFINE_H_
#include <array>
namespace active_safety {


struct AsObstacleCal {
  bool k_ignore_barrier_check = false;

  float k_motorcycle_max_a_lgt = 3.0F;
  float k_truck_max_a_lgt = 1.5F;
  float k_car_max_a_lgt = 3.0F;
  float k_veh_unkwn_type_max_a_lgt = 2.0;

  float k_max_value_for_self_dev = 1000000.0F;
  float k_max_curv = 0.2;

  float k_ped_length = 0.4F;
  float k_anim_length = 2.5F;
  float k_obj_length = 1.0;
};

} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_OBSTACLE_OBSTACLE_DEFINE_H_
