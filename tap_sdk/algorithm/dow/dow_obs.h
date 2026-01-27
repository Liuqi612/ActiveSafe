#pragma once
#include "algorithm/obstacle/obstacle.h"
#include "math/geometry/geometry.h"

#include <memory>

namespace active_safety {
namespace dow {

enum class OverlapType { NO_OVERLAP = 0, OVERLAP_REAR_RIGHT = 1, OVERLAP_REAR_LEFT = 2, OVERLAP_FRONT_RIGHT = 3, OVERLAP_FRONT_LEFT = 4 };

enum class DowObjectSide { UNDEF_SIDE = 0, EGO_LANE = 1, EGO_LEFT_SIDE = 2, EGO_RIGHT_SIDE = 3 };

enum class TravelEgoDirection { UNDEF_DIRECTION, REAR_LEFT_DIRECTION, REAR_RIGHT_DIRECTION, FRONT_LEFT_DIRECTION, FRONT_RIGHT_DIRECTION };

struct DowObsData {
  public:
    DowObsData() { obs = std::make_shared<AsObstacle>(); }
    std::shared_ptr<AsObstacle> obs = nullptr;

    bool  f_stationary       = false;
    bool  f_in_zone          = false;
    bool  f_alert            = false;
    float ttc                = 25.0f;
    float distance           = 0.0f;
    float intersec_point_lat = 0.0f;

    OverlapType        overlap                   = OverlapType::NO_OVERLAP;
    DowObjectSide      location_side             = DowObjectSide::UNDEF_SIDE;
    TravelEgoDirection direction_relative_to_ego = TravelEgoDirection::UNDEF_DIRECTION;
    math::Point2D      reference_point;

    uint8_t cycle_of_alert;
};

} // namespace dow
} // namespace active_safety
