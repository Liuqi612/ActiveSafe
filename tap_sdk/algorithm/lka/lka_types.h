#ifndef TAP_SDK_ALGORITHM_LKA_LKA_TYPES_H_
#define TAP_SDK_ALGORITHM_LKA_LKA_TYPES_H_

#include <cstdint>

namespace active_safety {
namespace lka {

// 以前轴坐标系为基准的主车道边界特征。
struct LaneBoundaryParameters {
    float curLftDisToBdry = 0.0F;
    float curRgtDisToBdry = 0.0F;
    float lftBdryHdgDeg = 0.0F;
    float rgtBdryHdgDeg = 0.0F;
    float lftBdryLatRt = 0.0F;
    float rgtBdryLatRt = 0.0F;
    float lftBdryCurv = 0.0F;
    float rgtBdryCurv = 0.0F;
    float lftBdryCurvRt = 0.0F;
    float rgtBdryCurvRt = 0.0F;
    float lftBdryTtlc = 10.0F;
    float rgtBdryTtlc = 10.0F;
    float laneWidth = 3.6F;
    float frtAxlCurv = 0.0F;
    bool  lftBdryVld = false;
    bool  rgtBdryVld = false;
};

// 自车坐标系下的车道中心线多项式参数。
struct LaneCenterParameters {
    float c0 = 0.0F;
    float c1 = 0.0F;
    float c2 = 0.0F;
    float c3 = 0.0F;
    float heading = 0.0F;
    float startRange = 0.0F;
    float endRange = 0.0F;
    bool  vld = false;
};

// 提供给 wrapper 的轻量级 LKA 状态输出。
struct LkaOutput {
    uint8_t  rolling_count = 0;
    uint8_t  major_version = 1;
    uint8_t  minor_version = 3;
    uint8_t  state = 0;
    bool     available = false;
    bool     left_intervention = false;
    bool     right_intervention = false;
    float    lane_center_offset = 0.0F;
    float    lane_center_heading = 0.0F;
    LaneBoundaryParameters lane_boundary_info;
    uint32_t suppress_mask = 0;
    uint16_t enable_mask = 0;
    
};

} // namespace lka
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LKA_LKA_TYPES_H_
