#ifndef TAP_SDK_ALGORITHM_ELK_ELK_OBS_H_
#define TAP_SDK_ALGORITHM_ELK_ELK_OBS_H_
#include "algorithm/obstacle/obstacle.h"
#include "elk_types.h"

#include <memory>

namespace active_safety {
namespace elk {

struct ElkObsData {
  public:
    ElkObsData() { obs = std::make_shared<AsObstacle>(); }

    std::shared_ptr<AsObstacle> obs;

    // Current cycle properties
    float dist = 0.0F;
    float ttc = 25.0F;
    ElkLane lane = ElkLane::CENTER;
    CollisionProbability collision_prob = CollisionProbability::NONE;
    DistMode dist_mode = DistMode::NONE;
    bool f_beyond_border = false;

    // Persistent properties
    struct Persistent {
        ObjectClass prev_object_class = ObjectClass::UNDETERMINED;
        FusionSource prev_fusion_source = FusionSource::SRR_ONLY;
        int32_t prev_fusTrkID = -1;
        int32_t prev_visTrkID = -1;
        bool f_object_class_change = false;
        bool f_visionID_change = false;

        // Oncoming specific (following as_elk field names exactly)
        Confidence oncom_confidence = Confidence::LOW;
        bool f_zone_interest = false;
        uint8_t oncom_age = 0;
        uint8_t cnt_not_availble_heading_age = 0;       // Following as_elk: cnt_not_availble_heading_age
        uint8_t cnt_not_available_object_class_age = 0; // Following as_elk: cnt_not_available_object_class_age
        uint8_t cnt_not_oncoming_age = 0;               // Following as_elk: cnt_not_oncoming_age

        // Overtake specific (following as_elk field names exactly)
        Confidence overtake_confidence = Confidence::LOW;
        bool f_front_zone_interest = false;
        bool f_rear_zone_interest = false;
        uint8_t overtake_age = 0;
        uint8_t cnt_not_availble_heading_age_ot = 0;       // Following as_elk: cnt_not_availble_heading_age
        uint8_t cnt_not_available_object_class_age_ot = 0; // Following as_elk: cnt_not_available_object_class_age
        uint8_t cnt_not_overtake_age = 0;                  // Following as_elk: cnt_not_overtake_age
    } persistent;

    void Reset() {
        obs = nullptr;
        dist = 0.0F;
        ttc = 25.0F;
        lane = ElkLane::CENTER;
        collision_prob = CollisionProbability::NONE;
        dist_mode = DistMode::NONE;
        f_beyond_border = false;
        persistent = Persistent();
    }
};

struct ElkLaneProperties {
    float host_lane_width = 3.75F;
    ElkLane host_leaning_direction = ElkLane::CENTER;
    bool f_host_left_valid = false;
    bool f_host_right_valid = false;
    bool f_host_left = false;  // Following as_elk: checkLaneMarkerValid result
    bool f_host_right = false; // Following as_elk: checkLaneMarkerValid result
};

// Following as_elk: persistent state for oncoming selection
struct OncomPersistents {
    ElkLaneProperties LM_properties;
    std::array<uint8_t, 3> candidate_pool_ID_left = {0, 0, 0};
    std::array<uint8_t, 3> candidate_pool_ID_right = {0, 0, 0};
    std::array<uint8_t, 3> oncom_left_id_pool = {0, 0, 0};
    std::array<uint8_t, 3> oncom_right_id_pool = {0, 0, 0};
    uint8_t num_oncom_left_trks = 0;
    uint8_t num_oncom_right_trks = 0;
};

// Following as_elk: persistent state for overtaking selection
struct OvertakePersistents {
    ElkLaneProperties LM_properties;
    std::array<uint8_t, 3> candidate_pool_ID_rear_left = {0, 0, 0};
    std::array<uint8_t, 3> candidate_pool_ID_rear_right = {0, 0, 0};
    std::array<uint8_t, 3> candidate_pool_ID_front_left = {0, 0, 0};
    std::array<uint8_t, 3> candidate_pool_ID_front_right = {0, 0, 0};
    std::array<uint8_t, 3> overtake_rear_left_id_pool = {0, 0, 0};
    std::array<uint8_t, 3> overtake_rear_right_id_pool = {0, 0, 0};
    std::array<uint8_t, 3> overtake_front_left_id_pool = {0, 0, 0};
    std::array<uint8_t, 3> overtake_front_right_id_pool = {0, 0, 0};
    uint8_t num_overtake_rear_left_trks = 0;
    uint8_t num_overtake_rear_right_trks = 0;
    uint8_t num_overtake_front_left_trks = 0;
    uint8_t num_overtake_front_right_trks = 0;
};

} // namespace elk
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_ELK_ELK_OBS_H_
