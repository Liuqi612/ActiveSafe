#pragma once
#include "algorithm/obstacle/obstacle.h"
#include "cts_cals.h"
#include "math/geometry/geometry.h"

namespace active_safety {
namespace cts {

enum ObsApproachSide { CTA_APPROACH_FROM_LEFT, CTA_APPROACH_FROM_RIGHT, CTA_APPROACH_UNDEFINED };
enum class CtsDirection { FRONT, REAR };

struct ObsAttribute {
    CtsDirection direction;
    math::Point2D reference_pt;

    math::Point2D intersect_pt;
    uint32_t reference_index;

    bool f_in_zone;
    float ttc;
    float radial_distance;
    int counter_val[CTS_MAX_LEVEL];
    int last_level = 0;

    void Reset() {
        reference_pt.x = 100.0f;
        reference_pt.y = 100.0f;
        intersect_pt.x = 100.0f;
        intersect_pt.y = 100.0f;
        reference_index = 0;
        f_in_zone = false;
        ttc = 25.0f;
        radial_distance = 100.0f;
        last_level = 0;
        for (int i = 0; i < CTS_MAX_LEVEL; ++i)
            counter_val[i] = 0;
    }
};

struct CtsObsData {
  public:
    CtsObsData() {
        obs = std::make_shared<AsObstacle>();
        attr[0].direction = CtsDirection::FRONT;
        attr[1].direction = CtsDirection::REAR;
        persistent.last_object_pos.x = 100.0f;
        persistent.last_object_pos.y = 100.0f;
    }
    std::shared_ptr<AsObstacle> obs = nullptr;

    math::Point2D corner_pts[8];
    ObsApproachSide approach_side;
    math::Point2D relative_velocity;
    float angle_diff = 0.0f;
    bool f_stationary = false;
    bool f_turning = false;

    struct Persistent {
        uint8_t filter_counter = 0;
        math::Point2D last_object_pos;
        math::Point2D last_pos_filtered;
    } persistent;

    // 0:front 1:rear
    ObsAttribute attr[2];
};

} // namespace cts
} // namespace active_safety
