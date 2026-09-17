#ifndef TAP_SDK_ALGORITHM_DOW_DOW_OBS_H_
#define TAP_SDK_ALGORITHM_DOW_DOW_OBS_H_
#include "algorithm/obstacle/obstacle.h"
#include "math/geometry/geometry.h"

#include <memory>

namespace active_safety {
namespace dow {

enum class OverlapType { NO_OVERLAP = 0, OVERLAP_REAR_RIGHT = 1, OVERLAP_REAR_LEFT = 2, OVERLAP_FRONT_RIGHT = 3, OVERLAP_FRONT_LEFT = 4 };

enum class DowObjectSide { UNDEF_SIDE = 0, EGO_LANE = 1, EGO_LEFT_SIDE = 2, EGO_RIGHT_SIDE = 3 };

enum class TravelEgoDirection { UNDEF_DIRECTION, REAR_LEFT_DIRECTION, REAR_RIGHT_DIRECTION, FRONT_LEFT_DIRECTION, FRONT_RIGHT_DIRECTION };

class DowObsData {
  public:
    DowObsData() { m_obs = std::make_shared<AsObstacle>(); }
    std::shared_ptr<AsObstacle> m_obs = nullptr;

    static constexpr float k_dow_ttc_init = 25.0F; // TTC默认初始值[s]

    bool  m_stationary       = false;
    bool  m_in_zone          = false; //未使用
    bool  m_alert            = false;
    float m_ttc                = k_dow_ttc_init;
    float m_distance           = 0.0F;
    float m_intersec_point_lat = 0.0F;

    OverlapType        m_overlap                   = OverlapType::NO_OVERLAP;
    DowObjectSide      m_location_side             = DowObjectSide::UNDEF_SIDE;
    TravelEgoDirection m_direction_relative_to_ego = TravelEgoDirection::UNDEF_DIRECTION;
    math::Point2D      m_reference_point;

    uint8_t m_cycle_of_alert = 0;
};

} // namespace dow
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_DOW_DOW_OBS_H_
