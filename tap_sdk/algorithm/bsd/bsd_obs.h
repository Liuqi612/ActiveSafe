#pragma once
#include "algorithm/obstacle/obstacle.h"
#include "math/geometry/geometry.h"
namespace active_safety {
namespace bsd {

enum class ObsValidType { OBS_NONE, OBS_BSW, OBS_CVW, OBS_BSW_AND_CVW };
enum class ObsSide { Left, Right };
enum class FallbackState { FALLBACK_NONE = 0, FALLBACK_ACTIVE = 1, FALLBACK_PREVIOUS = 2 };

struct BsdObsData {
  public:
    BsdObsData() { obs = std::make_shared<AsObstacle>(); }
    std::shared_ptr<AsObstacle> obs = nullptr;

    ObsValidType  obs_vld_type;
    ObsSide       side;
    math::Polygon polygon;
    math::Polygon bsw_polygon;
    math::Polygon cvw_polygon;

    FallbackState fallback_state;

    int  bsw_in_zone_cnt          = 0;
    int  cvw_in_zone_cnt          = 0;
    bool f_stationary             = false;
    bool f_bsw_in_zone            = false;
    bool f_cvw_in_zone            = false;
    bool f_is_prev_cvw_active_obj = false;
    bool f_is_prev_bsw_active_obj = false;
    bool f_bsw_in_ego_lane        = false;
    bool f_cvw_in_ego_lane        = false;

    float curvi_long_vel_rel_filt;
    float curvi_lat_posn_filt;
    float ttc;
};
} // namespace bsd
} // namespace active_safety