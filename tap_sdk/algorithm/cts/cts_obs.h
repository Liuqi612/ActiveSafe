#ifndef TAP_SDK_ALGORITHM_CTS_CTS_OBS_H_
#define TAP_SDK_ALGORITHM_CTS_CTS_OBS_H_
#include "algorithm/obstacle/obstacle.h"
#include "cts_cals.h"
#include "math/geometry/geometry.h"
#include "math/signalprocess/off_delay_block/off_delay_block.h"

#include <vector>

namespace active_safety {
namespace cts {

enum ObsApproachSide { CTA_APPROACH_FROM_LEFT, CTA_APPROACH_FROM_RIGHT, CTA_APPROACH_UNDEFINED };
enum class CtsDirection { FRONT, REAR };

struct ObsAttribute {
    CtsDirection direction;
    math::Point2D reference_pt;

    math::Point2D intersect_pt;
    uint32_t reference_index;

    bool in_zone;
    float lat_ttc;
    float lgt_ttc;
    float radial_distance;
    int counter_val[CTS_MAX_LEVEL];
    int last_level = 0;

    // Reset 中各成员的无效初始值（成员就地初始化无法引用 cal，故用类内常量）
    static constexpr float k_cta_pos_invalid_init = 100.0F; // 参考点/交叉点/径向距离无效初始值(m)
    static constexpr float k_cta_ttc_invalid_init = 25.0F;  // 纵向/横向TTC默认初始值(s)

    void Reset() {
        reference_pt.x = k_cta_pos_invalid_init;
        reference_pt.y = k_cta_pos_invalid_init;
        intersect_pt.x = k_cta_pos_invalid_init;
        intersect_pt.y = k_cta_pos_invalid_init;
        reference_index = 0;
        in_zone = false;
        lgt_ttc = k_cta_ttc_invalid_init;
        lat_ttc = k_cta_ttc_invalid_init;
        radial_distance = k_cta_pos_invalid_init;
        last_level = 0;
        for (int i = 0; i < CTS_MAX_LEVEL; ++i)
            counter_val[i] = 0;
    }
};

class CtsObsData {
  public:
    CtsObsData() {
        m_obs = std::make_shared<AsObstacle>();
        m_attr[0].direction = CtsDirection::FRONT;
        m_attr[1].direction = CtsDirection::REAR;
        m_persistent.last_object_pos.x = ObsAttribute::k_cta_pos_invalid_init;
        m_persistent.last_object_pos.y = ObsAttribute::k_cta_pos_invalid_init;
    }
    std::shared_ptr<AsObstacle> m_obs = nullptr;

    math::Point2D m_corner_pts[8];
    ObsApproachSide m_approach_side;
    math::Point2D m_relative_velocity;
    math::Polygon m_during_obs_to_host_zone;
    std::vector<int32_t> m_dur_obs_to_host_ids;

    float m_angle_diff = 0.0F;

    bool m_stationary = false;
    bool m_cross_decel = false;
    float m_init_cross_decel_lat_vel = 0.0F;
    math::OffDelayBlock m_cross_decel_offdly;

    struct Persistent {
        uint8_t filter_counter = 0;
        math::Point2D last_object_pos;
        math::Point2D last_pos_filtered;
    } m_persistent;

    // 0:front 1:rear
    ObsAttribute m_attr[2];
};

} // namespace cts
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_CTS_CTS_OBS_H_
