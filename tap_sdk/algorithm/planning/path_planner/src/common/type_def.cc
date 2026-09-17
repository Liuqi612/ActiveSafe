
#include "common/type_def.h"

namespace ads_x {
namespace planning {

SLPoint::SLPoint(double _s, double _l) {
    s = _s;
    l = _l;
}

STPoint::STPoint(double _s, double _t) : s(_s), t(_t){};

FrenetPoint::FrenetPoint(
    double _s, double _ds, double _dds, double _l, double _dl, double _ddl)
    : s(_s), ds(_ds), dds(_dds), l(_l), dl(_dl), ddl(_ddl) {}

SpeedPoint::SpeedPoint(double _t, double _s, double _v, double _a, double _j)
    : t(_t), s(_s), v(_v), a(_a), j(_j){};

TransformInfo::TransformInfo(double _x, double _y, double _yaw)
    : delta_x(_x), delta_y(_y), delta_yaw(_yaw) {}

SLPoint SLBoundary::center() const {
    return {(s_min + s_max) * 0.5, (l_min + l_max) * 0.5};
}
double SLBoundary::width() const {
    return (l_max > l_min) ? (l_max - l_min) : 0.0;
}
double SLBoundary::length() const {
    return (s_max > s_min) ? (s_max - s_min) : 0.0;
}
bool SLBoundary::IsValid() const { return (l_max > l_min) && (s_max > s_min); }

void SpeedState::Reset() {
    attention_obj_id = "";
    lcc_keep_brake = false;
    yield_to_vru = false;
    vru_interact_timer = 0.0;
    infront_vru_ids.clear();
}

FormOfWayInfo::FormOfWayInfo(int32_t _start, int32_t _end, RoadType _roadType)
    : start(_start), end(_end), road_type(_roadType){};

RoundaboutInfo::RoundaboutInfo(int32_t _is_in_roundabout,
                               int32_t _junction_num_enter_roundabout,
                               int32_t _junction_num_exit_roundabout,
                               int32_t _distance_to_enter_roundabout,
                               int32_t _distance_to_exit_roundabout)
    : is_in_roundabout(_is_in_roundabout),
      junction_num_enter_roundabout(_junction_num_enter_roundabout),
      junction_num_exit_roundabout(_junction_num_exit_roundabout),
      distance_to_enter_roundabout(_distance_to_enter_roundabout),
      distance_to_exit_roundabout(_distance_to_exit_roundabout){};

}  // namespace planning
}  // namespace ads_x
