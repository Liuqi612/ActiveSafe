#pragma once
#include <cstdint>

namespace active_safety {
namespace elk {

struct ElkCal {
    float   k_lineconf_vld_thr          = 0.5f;
    float   k_default_lane_width        = 3.75f;
    float   k_oncom_long_thres          = 150.0f;
    float   k_trk_heading               = 0.1f;
    float   k_curvature_speed           = 0.05f;
    float   k_range_lm                  = 100.0f;
    float   k_offset_small              = 0.5f;
    float   k_offset_big                = 1.0f;
    float   k_lm_pad_two                = 0.2f;
    float   k_lm_pad_one                = 0.1f;
    float   k_oc_ttc_thrd               = 5.0f;
    float   k_neighbor_factor           = 1.2f;
    float   k_neighbor_factor_truck     = 1.5f;
    float   k_oc_min_x                  = 0.0f;
    float   k_ot_ttc_thrd               = 4.0f;
    float   k_ot_front_max_x            = 80.0f;
    float   k_ot_front_min_x            = 0.0f;
    float   k_ot_rear_max_x             = 0.0f;
    float   k_ot_rear_min_x             = -80.0f;
    bool    k_enable_oncom_selection    = true;
    bool    k_enable_overtake_selection = true;
    uint8_t k_Max_Oncom_Pool_Trks       = 3;
    uint8_t k_Max_Overtake_Pool_Trks    = 5;
    uint8_t k_Max_Coast_Cycle           = 10;
    uint8_t k_Max_Candidate             = 3;
};

} // namespace elk
} // namespace active_safety
