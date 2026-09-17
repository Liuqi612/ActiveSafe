#ifndef TAP_SDK_ALGORITHM_RCW_RCW_OBS_H_
#define TAP_SDK_ALGORITHM_RCW_RCW_OBS_H_
#include "algorithm/obstacle/obstacle.h"

#include <memory>
#include <vector>

namespace active_safety {
namespace rcw {

struct RcwObsData {
  public:
    RcwObsData() { obs = std::make_shared<AsObstacle>(); }
    std::shared_ptr<AsObstacle> obs = nullptr;

    // TTC 成员默认初始值；注意运行期默认/上限用的是 k_rcw_default_ttc(25.5)，此处历史值为 25.0
    static constexpr float k_rcw_ttc_init = 25.0f;

    float age = 0.0f;
    bool is_valid_obj_last_cycle = false;
    bool is_in_lane = false;
    bool is_inpath = false;
    bool is_current_inpath = false;
    bool is_pred_inpath = false;
    bool is_valid = false;
    int object_within_lane_counter = 0;
    float ttc = k_rcw_ttc_init;
    float filtered_heading = 0.0f;

    math::Point2D filtered_diff_pos;
    math::Point2D effective_rel_vel;
    math::Point2D last_object_pos;
    math::Point2D last_object_pos_filtered;

    int filter_counter = 0;
    float crash_prob_braking = 0.0f;
    float crash_prob_steering = 0.0f;
    float crash_prob_combined = 0.0f;
};

} // namespace rcw
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_RCW_RCW_OBS_H_
