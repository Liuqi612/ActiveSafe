#pragma once
#include "algorithm/obstacle/obstacle.h"

#include <memory>
#include <vector>

namespace active_safety {
namespace rcw {

struct RcwWarnDebounceCounter {
    uint8_t hold;
    uint8_t suppress;
    uint8_t warn_duration;
    bool    was_active_last_cycle;
};

struct RcwObsData {
  public:
    RcwObsData() { obs = std::make_shared<AsObstacle>(); }
    std::shared_ptr<AsObstacle> obs = nullptr;

    bool  f_need_clear_all;
    int   age;
    bool  f_is_valid_obj_last_cycle;
    bool  is_in_lane;
    int   object_within_lane_counter;
    float ttc;
    float filtered_heading;

    math::Point2D filtered_diff_pos;
    math::Point2D effective_rel_vel;
    math::Point2D last_object_pos;
    math::Point2D last_object_pos_filtered;

    int   filter_counter;
    float crash_prob_braking;
    float crash_prob_steering;
    float crash_prob_filtered;
    float crash_prob_combined;
    int   consecutive_min_crash_prob_counter;
};

} // namespace rcw
} // namespace active_safety
