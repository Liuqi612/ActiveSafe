#ifndef TAP_SDK_ALGORITHM_BSD_BSD_OBS_H_
#define TAP_SDK_ALGORITHM_BSD_BSD_OBS_H_
#include "algorithm/obstacle/obstacle.h"
#include "math/geometry/geometry.h"
namespace active_safety {
namespace bsd {

enum class ObsValidType { OBS_NONE, OBS_BSW, OBS_CVW, OBS_BSW_AND_CVW };
enum class ObsSide { Left, Right };
enum class FallbackState { FALLBACK_NONE = 0, FALLBACK_ACTIVE = 1, FALLBACK_PREVIOUS = 2 };

class BsdObsData {
  public:
    BsdObsData() { m_obs = std::make_shared<AsObstacle>(); }
    std::shared_ptr<AsObstacle> m_obs = nullptr;

    ObsValidType  m_obs_vld_type;
    ObsSide       m_side;
    math::Polygon m_polygon;
    math::Polygon m_bsw_polygon;
    math::Polygon m_cvw_polygon;

    FallbackState m_fallback_state;

    int  m_bsw_in_zone_cnt          = 0;
    int  m_cvw_in_zone_cnt          = 0;
    bool m_stationary               = false;
    bool m_bsw_in_zone              = false;
    bool m_cvw_in_zone              = false;
    bool m_is_prev_cvw_active_obj   = false;
    bool m_is_prev_bsw_active_obj   = false;
    bool m_bsw_in_ego_lane          = false;
    bool m_cvw_in_ego_lane          = false;

    float m_curvi_long_vel_rel_filt = 0.0f;
    float m_curvi_lat_posn_filt = 0.0f;
    float m_ttc = 25.0f;
};
} // namespace bsd
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_BSD_BSD_OBS_H_
