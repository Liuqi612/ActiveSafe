#include "elk_target_selection.h"

#include "interface/fusion_object.h"

#include "ad_log/ad_log.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>

namespace active_safety {
namespace elk {

ElkTargetSelection::ElkTargetSelection() {
    Init();
}

void ElkTargetSelection::Init() {
    std::memset(&oncom_out_, 0, sizeof(oncom_out_));
    std::memset(&overtake_out_, 0, sizeof(overtake_out_));

    // Initialize persistents (following as_elk)
    oncom_persistents_.LM_properties.host_lane_width = elk_cal_.k_default_lane_width;
    oncom_persistents_.LM_properties.host_leaning_direction = ElkLane::CENTER;
    oncom_persistents_.LM_properties.f_host_left = false;
    oncom_persistents_.LM_properties.f_host_right = false;
    oncom_persistents_.candidate_pool_ID_left.fill(0);
    oncom_persistents_.candidate_pool_ID_right.fill(0);
    oncom_persistents_.oncom_left_id_pool.fill(0);
    oncom_persistents_.oncom_right_id_pool.fill(0);
    oncom_persistents_.num_oncom_left_trks = 0;
    oncom_persistents_.num_oncom_right_trks = 0;

    overtake_persistents_.LM_properties.host_lane_width = elk_cal_.k_default_lane_width;
    overtake_persistents_.LM_properties.host_leaning_direction = ElkLane::CENTER;
    overtake_persistents_.LM_properties.f_host_left = false;
    overtake_persistents_.LM_properties.f_host_right = false;
    overtake_persistents_.candidate_pool_ID_rear_left.fill(0);
    overtake_persistents_.candidate_pool_ID_rear_right.fill(0);
    overtake_persistents_.candidate_pool_ID_front_left.fill(0);
    overtake_persistents_.candidate_pool_ID_front_right.fill(0);
    overtake_persistents_.overtake_rear_left_id_pool.fill(0);
    overtake_persistents_.overtake_rear_right_id_pool.fill(0);
    overtake_persistents_.overtake_front_left_id_pool.fill(0);
    overtake_persistents_.overtake_front_right_id_pool.fill(0);
    overtake_persistents_.num_overtake_rear_left_trks = 0;
    overtake_persistents_.num_overtake_rear_right_trks = 0;
    overtake_persistents_.num_overtake_front_left_trks = 0;
    overtake_persistents_.num_overtake_front_right_trks = 0;

    oncom_rollcnt_ = 0;
    overtake_rollcnt_ = 0;
}

void ElkTargetSelection::Update(const AsVseOut &vse_out, const LanesInfo &road_info, const GlobalConfig &config, const AsObstacleList &obs_list) {
    // Clear outputs at the beginning of each cycle (following as_elk: outputs are fresh each cycle)
    std::memset(&oncom_out_, 0, sizeof(oncom_out_));
    std::memset(&overtake_out_, 0, sizeof(overtake_out_));

    // AD_LINFO(ElkTargetSelection::Update) << "New road_info in elk tsel:";
    // AD_LINFO(ElkTargetSelection::Update) << "left c0 is:" << road_info.HostLeftLaneMarker.LinePolyC0
    //      << ", right c0 is:" << road_info.HostRightLaneMarker.LinePolyC0;
    // AD_LINFO(ElkTargetSelection::Update) << "left edge info: c0 is:" << road_info.LeftRoadEdge.LinePolyC0
    //      << ", start range is:" << road_info.LeftRoadEdge.LineViewRangeStart
    //      << ", end range is:" << road_info.LeftRoadEdge.LineViewRangeEnd;
    // AD_LINFO(ElkTargetSelection::Update) << "right edge info: c0 is:" << road_info.RightRoadEdge.LinePolyC0
    //      << ", start range is:" << road_info.RightRoadEdge.LineViewRangeStart
    //      << ", end range is:" << road_info.RightRoadEdge.LineViewRangeEnd;

    // Initialize obs_data from obs_list (following as_elk: fus_trks->trk is passed to oncomTrkPropertiesUpdate)
    for (size_t i = 0; i < kMaxNormalObject; ++i) {
        const auto current_obs = obs_list[i];
        const int32_t current_fus_id = current_obs ? current_obs->fus_trkID : -1;
        const int32_t prev_fus_id = obs_data_[i].persistent.prev_fusTrkID;
        const bool invalid_current =
            (!current_obs) || (current_fus_id <= 0) ||
            (current_obs->status == TrackStatus::NEW) || (current_obs->status == TrackStatus::INVALID);
        const bool id_changed = (current_fus_id > 0) && (prev_fus_id > 0) && (current_fus_id != prev_fus_id);

        if (invalid_current || id_changed) {
            obs_data_[i].Reset();
        }
        obs_data_[i].obs = current_obs ? current_obs : std::make_shared<AsObstacle>();
    }

    // Following as_elk 100%: oncomTargetSelection flow
    if (elk_cal_.k_enable_oncom_selection) {
        // 1. Check lane marker valid
        CheckLaneMarkerValid(road_info);

        // 2. Update host departure direction
        UpdateHostDepartureDirection(road_info);

        // 3. Update object properties
        OncomTrkPropertiesUpdate(road_info, vse_out.rear_curvature);

        // 4. Threat computation
        OncomThreatComputation(vse_out.vcs_long_vel);

        // 5. Down selection
        OncomDownSelection();

        // 6. Select targets
        OncomSelect();

        // 7. Update target properties
        UpdateOncomTgtTrkProperties();
    }

    // Following as_elk 100%: overtakeTargetSelection flow
    if (elk_cal_.k_enable_overtake_selection) {
        // 1. Check lane marker valid
        // CheckLaneMarkerValid(road_info);

        // 2. Update host departure direction
        UpdateHostDepartureDirection(road_info);

        // 3. Update object properties
        OvertakeTrkPropertiesUpdate(road_info, vse_out.rear_curvature);

        // 4. Threat computation
        OvertakeThreatComputation(vse_out.vcs_long_vel);

        // 5. Down selection
        OvertakeDownSelection();

        // 6. Select targets
        OvertakeSelect();

        // 7. Update target properties
        UpdateOvertakeTgtTrkProperties();

    }

    // Fill previous-frame object identity after all target-selection paths finish.
    // Slot-level histories are only valid while the same fusion track stays in the slot.
    for (auto i = 0; i < kMaxNormalObject; i++) {
        auto &memory = obs_data_[i].persistent;
        memory.prev_fusTrkID = obs_data_[i].obs->fus_trkID;
        memory.prev_fusion_source = obs_data_[i].obs->fusion_source;
        memory.prev_visTrkID = obs_data_[i].obs->vis_trkID;
        memory.prev_object_class = obs_data_[i].obs->object_class;
    }

    // AD_LINFO(ElkTargetSelection::Update) << "New frame in elk tsel:";
    // for (size_t i = 0; i < kMaxNormalObject; ++i) {
    //     if (obs_list[i]->fus_trkID > 0) {

    //         AD_LINFO(ElkTargetSelection::Update) << "obj slot num is:" << i
    //             << ", fusion id is:" << obs_list[i]->fus_trkID
    //             << ", long pos is:" << obs_list[i]->long_posn
    //             << ", dist is:" << obs_data_[i].dist
    //             << ", f_beyond_border is:" << obs_data_[i].f_beyond_border
    //             << ", lane is:" << (int)obs_data_[i].lane
    //             << ", dist mode is:" << (int)obs_data_[i].dist_mode
    //             << ", f_front_zone_interest is:" << obs_data_[i].persistent.f_front_zone_interest
    //             << ", f_rear_zone_interest is:" <<  obs_data_[i].persistent.f_rear_zone_interest
    //             << ", f_zone_interest is:" << obs_data_[i].persistent.f_zone_interest;

    //     }
    // }
    // AD_LINFO(ElkTargetSelection::Update) << "New resout in elk tsel:";
    // if (overtake_out_.overtake_target_rear_left.track_id > 0) {
    //     AD_LINFO(ElkTargetSelection::Update) << "obj rear left ot is : " << (int)overtake_out_.overtake_target_rear_left.track_id;
    // }
    // if (overtake_out_.overtake_target_rear_right.track_id > 0) {
    //     AD_LINFO(ElkTargetSelection::Update) << "obj rear right ot is : " << (int)overtake_out_.overtake_target_rear_right.track_id;
    // }
    // if (oncom_out_.oncom_target_1.track_id > 0) {
    //     AD_LINFO(ElkTargetSelection::Update) << "obj front left oc is : " << (int)oncom_out_.oncom_target_1.track_id;
    // }
    // if (oncom_out_.oncom_target_2.track_id > 0) {
    //     AD_LINFO(ElkTargetSelection::Update) << "obj front right oc is : " << (int)oncom_out_.oncom_target_2.track_id;
    // }
    
    // Fill Outputs
    FillOncomOutput();
    FillOvertakeOutput();
}

// Following as_elk 100%: OncomTrkPropertiesUpdate
void ElkTargetSelection::OncomTrkPropertiesUpdate(const LanesInfo &lane_info, float rear_curvature) {
    for (size_t i = 0; i < kMaxNormalObject; ++i) {
        // Following as_elk: updateTrkOncomConfidence uses prev_* from last frame
        UpdateTrkOncomConfidence(i);

        // Update lane assignment
        UpdateLaneAssignment(i, lane_info, rear_curvature);

        // Check valid zone
        CheckOncomValidZone(i);

        // OC/OT only relies on the lane marker between ego and target.
        // Road edges belong to ROR and must not reject an OC target.
        obs_data_[i].f_beyond_border = false;
    }
}

// Following as_elk 100%: OvertakeTrkPropertiesUpdate
void ElkTargetSelection::OvertakeTrkPropertiesUpdate(const LanesInfo &lane_info, float rear_curvature) {
    for (size_t i = 0; i < kMaxNormalObject; ++i) {
        // updateTrk OvertakeConfidence
        UpdateTrkOvertakeConfidence(i);

        // Update lane assignment
        // UpdateLaneAssignment(i, lane_info, rear_curvature);

        // Check valid zone
        CheckOvertakeValidZone(i);

        // Check beyond border
        // CheckObjectBeyondBarrier(i, lane_info);
    }
}

// Following as_elk 100%: UpdateTrkOncomConfidence
void ElkTargetSelection::UpdateTrkOncomConfidence(size_t obs_idx) {
    auto &obs = obs_data_[obs_idx].obs;
    auto &memory = obs_data_[obs_idx].persistent;

    bool f_available_class = (obs->object_class == ObjectClass::CAR || obs->object_class == ObjectClass::TRUCK);
    bool f_available_status = (obs->status == TrackStatus::UPDATED || obs->status == TrackStatus::COASTED);
    bool f_available_source = (obs->fusion_source == FusionSource::RADAR_VISION || obs->fusion_source == FusionSource::MULTIPLE_TRACKLET);
    bool f_low_conf = false; // Following as_elk: always false
    bool f_high_conf = true; // Following as_elk: always true
    bool f_available_motion = (obs->long_vel <= -elk_cal_.k_ELK_OC_MinOncomingSpeed); // 当前帧必须明确反向接近
    bool f_available_heading = (std::abs(obs->heading) >= elk_cal_.k_oc_trk_heading);
    bool f_object_class_change = (obs->object_class != memory.prev_object_class);
    bool f_visionID_change = (obs->vis_trkID != memory.prev_visTrkID);

    // if (obs->fus_trkID == 55407) {
    //     AD_LINFO(ElkTargetSelection::UpdateTrkOncomConfidence) << "long_vel is: " << obs->long_vel
    //         << ", f_available_motion is: " << f_available_motion;
    // }

    if (!f_available_heading) {
        memory.cnt_not_availble_heading_age = std::min((uint8_t)255, (uint8_t)(memory.cnt_not_availble_heading_age + 1));
    } else {
        memory.cnt_not_availble_heading_age = 0;
    }

    if (!f_available_class) {
        memory.cnt_not_available_object_class_age = std::min((uint8_t)255, (uint8_t)(memory.cnt_not_available_object_class_age + 1));
    } else {
        memory.cnt_not_available_object_class_age = 0;
    }

    if (!f_available_motion) {
        memory.cnt_not_oncoming_age = std::min((uint8_t)255, (uint8_t)(memory.cnt_not_oncoming_age + 1));
    } else {
        memory.cnt_not_oncoming_age = 0;
    }

    memory.f_object_class_change = f_object_class_change;
    memory.f_visionID_change = f_visionID_change;

    // Confidence state machine (following as_elk 100%)
    switch (memory.oncom_confidence) {
        case Confidence::LOW:
            if (f_available_class && f_available_status && f_available_source && f_low_conf && f_available_motion) {
                memory.oncom_confidence = Confidence::MED;
                memory.oncom_age = 1;
            } else if (f_available_class && f_available_status && f_available_source && f_high_conf && f_available_motion && f_available_heading) {
                memory.oncom_confidence = Confidence::HIGH;
                memory.oncom_age = 1;
            } else {
                memory.oncom_age = std::min((uint8_t)255, (uint8_t)(memory.oncom_age + 1));
            }
            break;
        case Confidence::MED:
            if ((memory.cnt_not_available_object_class_age > 3)  ||  !f_available_status  ||  (memory.cnt_not_oncoming_age > 3)) {
                memory.oncom_confidence = Confidence::LOW;
                memory.oncom_age = 1;
            } else if (f_available_class && !f_object_class_change && !f_visionID_change && f_available_source && memory.oncom_age > 3 &&
                       f_available_motion && f_available_heading && f_high_conf) {
                memory.oncom_confidence = Confidence::HIGH;
                memory.oncom_age = 1;
            } else {
                memory.oncom_age = std::min((uint8_t)255, (uint8_t)(memory.oncom_age + 1));
            }
            break;
        case Confidence::HIGH:
            if ((memory.cnt_not_available_object_class_age > 3)  ||  !f_available_status  ||  (memory.cnt_not_oncoming_age > 3)) {
                memory.oncom_confidence = Confidence::LOW;
                memory.oncom_age = 1;
            } else if (f_available_class && f_available_motion &&
                       (memory.cnt_not_availble_heading_age > 3U || f_low_conf || f_object_class_change || f_visionID_change)) {
                memory.oncom_confidence = Confidence::MED;
                memory.oncom_age = 1;
            } else {
                memory.oncom_age = std::min((uint8_t)255, (uint8_t)(memory.oncom_age + 1));
            }
            break;
    }
}

bool ElkTargetSelection::IsCurrentOncomingMotion(const AsObstacle &obs) const {
    return (obs.long_vel <= -elk_cal_.k_ELK_OC_MinOncomingSpeed) &&
        (std::abs(obs.heading) >= elk_cal_.k_oc_trk_heading);
}

// Following as_elk 100%: UpdateTrkOvertakeConfidence (simplified, as_elk doesn't have overtake confidence state machine)
void ElkTargetSelection::UpdateTrkOvertakeConfidence(size_t obs_idx) {
    // Overtake confidence is not used in as_elk, keeping for compatibility
    auto &obs = obs_data_[obs_idx].obs;
    auto &memory = obs_data_[obs_idx].persistent;

    bool f_available_class = (obs->object_class == ObjectClass::CAR || obs->object_class == ObjectClass::TRUCK);
    bool f_low_conf = false; // Following as_elk: always false
    bool f_high_conf = true; // Following as_elk: always true
    bool f_available_motion = (obs->long_vel > elk_cal_.k_ot_min_speed); // 剔除静止目标
    bool f_available_heading = (obs->heading < elk_cal_.k_ot_trk_heading && obs->heading > -elk_cal_.k_ot_trk_heading);

    // if (obs->fus_trkID == 50655) {
    //     AD_LINFO(ElkTargetSelection::UpdateTrkOvertakeConfidence) << "f_available_class is: " << f_available_class
    //         << ", f_available_heading is: " << f_available_heading
    //         << ", f_available_motion is: " << f_available_motion;
    // }

    if (f_available_class && f_high_conf && f_available_motion && f_available_heading) {
        memory.overtake_confidence = Confidence::HIGH;
    } else if (f_available_class && f_low_conf && f_available_motion && f_available_heading) {
        memory.overtake_confidence = Confidence::MED;
    } else {
        memory.overtake_confidence = Confidence::LOW;
    }
}

// Following as_elk 100%: CheckOncomValidZone
void ElkTargetSelection::CheckOncomValidZone(size_t obs_idx) {
    auto &obs_data = obs_data_[obs_idx];
    auto &memory = obs_data.persistent;

    float tmp = (obs_data.obs->object_class == ObjectClass::TRUCK) ? elk_cal_.k_neighbor_factor_truck : elk_cal_.k_neighbor_factor;
    tmp *= oncom_persistents_.LM_properties.host_lane_width;

    memory.f_zone_interest =
        (obs_data.obs->long_posn > elk_cal_.k_oc_min_x && obs_data.obs->long_posn < elk_cal_.k_oncom_long_thres && std::abs(obs_data.dist) < tmp);
}

// Following as_elk 100%: CheckOvertakeValidZone
void ElkTargetSelection::CheckOvertakeValidZone(size_t obs_idx) {
    auto &obs_data = obs_data_[obs_idx];
    auto &memory = obs_data.persistent;

    float tmp = (obs_data.obs->object_class == ObjectClass::TRUCK) ? elk_cal_.k_neighbor_factor_truck : elk_cal_.k_neighbor_factor;
    tmp *= overtake_persistents_.LM_properties.host_lane_width;

    bool bLatInterest = std::abs(obs_data.dist) < tmp;

    float xFrtAxl = obs_data.obs->long_posn + 0.5 * obs_data.obs->length * std::cos(obs_data.obs->heading); // 前轴中心纵向位置

    // 针对后向overtaking筛选纵向范围设置迟滞buffer，即严进宽出; 目标id改变时reset历史值
    if ((xFrtAxl > elk_cal_.k_ot_rear_min_x)  &&  (xFrtAxl < elk_cal_.k_ot_rear_max_x)  &&  bLatInterest) {
        memory.f_rear_zone_interest = true;
    } else if (xFrtAxl < elk_cal_.k_ot_rear_min_x - elk_cal_.k_ot_rear_hysteretic_x ||
             xFrtAxl > elk_cal_.k_ot_rear_max_x + elk_cal_.k_ot_rear_hysteretic_x || bLatInterest
    ) {
        memory.f_rear_zone_interest = false;
    } else if (memory.prev_fusTrkID != obs_data.obs->fus_trkID) {
        memory.f_rear_zone_interest = false;
    }

    memory.f_front_zone_interest =
        (obs_data.obs->long_posn > elk_cal_.k_ot_front_min_x && obs_data.obs->long_posn < elk_cal_.k_ot_front_max_x && bLatInterest);
}

// Following as_elk 100%: OncomThreatComputation
void ElkTargetSelection::OncomThreatComputation(float host_speed) {
    for (size_t i = 0; i < kMaxNormalObject; ++i) {
        auto &obs_data = obs_data_[i];
        auto &memory = obs_data.persistent;

        if (memory.oncom_confidence > Confidence::LOW && memory.f_zone_interest &&
            !obs_data.f_beyond_border && IsCurrentOncomingMotion(*obs_data.obs)) {

            float dv = host_speed - obs_data.obs->long_vel;
            float ttc = 99.0F;
            if (std::abs(dv) > 0.001F) {
                ttc = std::abs(obs_data.obs->long_posn / dv);
            }

            CollisionProbability collision_prob;
            if (obs_data.lane == oncom_persistents_.LM_properties.host_leaning_direction) {
                if (ttc < elk_cal_.k_oc_ttc_thrd) {
                    collision_prob = CollisionProbability::HIGH;
                } else {
                    collision_prob = CollisionProbability::MED;
                }
            } else if (ttc < elk_cal_.k_oc_ttc_thrd) {
                collision_prob = CollisionProbability::MED;
            } else {
                collision_prob = CollisionProbability::LOW;
            }

            obs_data.ttc = ttc;
            obs_data.collision_prob = collision_prob;
        } else {
            obs_data.collision_prob = CollisionProbability::NONE;
            obs_data.ttc = 100.0F;
        }
    }
}

// Following as_elk 100%: OvertakeThreatComputation
void ElkTargetSelection::OvertakeThreatComputation(float host_speed) {
    for (size_t i = 0; i < kMaxNormalObject; ++i) {
        auto &obs_data = obs_data_[i];

        if (!obs_data.f_beyond_border  &&  (obs_data.persistent.overtake_confidence > Confidence::LOW)) {
            float dv = host_speed - obs_data.obs->long_vel;
            float ttc = 99.0F;
            if (std::abs(dv) > 0.001F) {
                ttc = std::abs(obs_data.obs->long_posn / dv);
            }

            CollisionProbability collision_prob;
            if (obs_data.lane == overtake_persistents_.LM_properties.host_leaning_direction) {
                if (ttc < elk_cal_.k_ot_ttc_thrd) {
                    collision_prob = CollisionProbability::HIGH;
                } else {
                    collision_prob = CollisionProbability::MED;
                }
            } else if (ttc < elk_cal_.k_ot_ttc_thrd) {
                collision_prob = CollisionProbability::MED;
            } else {
                collision_prob = CollisionProbability::LOW;
            }

            obs_data.ttc = ttc;
            obs_data.collision_prob = collision_prob;
        } else {
            obs_data.collision_prob = CollisionProbability::NONE;
            obs_data.ttc = 100.0F;
        }
    }
}

void ElkTargetSelection::ProcessLaneMarkers(const LanesInfo &lane_info) {
    // This function is now replaced by CheckLaneMarkerValid
    // Keeping for backward compatibility
}

void ElkTargetSelection::ProcessObjects(const AsVseOut &vse_out, const LanesInfo &road_info, const AsObstacleList &obs_list) {
    // Initialize obs_data from obs_list
    // This function is now replaced by OncomTrkPropertiesUpdate/OvertakeTrkPropertiesUpdate
    // Keeping for backward compatibility
    for (size_t i = 0; i < kMaxNormalObject; ++i) {
        obs_data_[i].obs = obs_list[i];

        if ((obs_data_[i].obs->status == TrackStatus::NEW)  ||  (obs_data_[i].obs->status == TrackStatus::INVALID)) {
            obs_data_[i].Reset();
            obs_data_[i].obs = obs_list[i];
        }
    }
}

// Following as_elk: updateLaneAssignment (100% complete)
void ElkTargetSelection::UpdateLaneAssignment(size_t obs_idx, const LanesInfo &lane_info, float rear_curvature) {
    auto &obs_data = obs_data_[obs_idx];
    // Convert object position from ISO (left+, right-) to as_elk (left-, right+)
    float trk_vcs_lat_posn = -obs_data.obs->lat_posn;  // Negate to convert coordinate system
    float trk_vcs_long_posn = obs_data.obs->long_posn; // Longitudinal position doesn't change

    float x2 = trk_vcs_long_posn * trk_vcs_long_posn;

    // Convert from ISO (left+, right-) to as_elk (left-, right+)
    // Negate all polynomial coefficients to convert coordinate system
    float offset_left = -lane_info.HostLeftLaneMarker.LinePolyC0 + (-lane_info.HostLeftLaneMarker.LinePolyC1) * trk_vcs_long_posn +
        (-lane_info.HostLeftLaneMarker.LinePolyC2) * x2 + (-lane_info.HostLeftLaneMarker.LinePolyC3) * x2 * trk_vcs_long_posn;

    float offset_right = -lane_info.HostRightLaneMarker.LinePolyC0 + (-lane_info.HostRightLaneMarker.LinePolyC1) * trk_vcs_long_posn +
        (-lane_info.HostRightLaneMarker.LinePolyC2) * x2 + (-lane_info.HostRightLaneMarker.LinePolyC3) * x2 * trk_vcs_long_posn;

    float dist = 0.0F;
    ElkLane lane_num = ElkLane::CENTER;
    DistMode dist_mode = DistMode::NONE;
    bool f_host_left = oncom_persistents_.LM_properties.f_host_left;
    bool f_host_right = oncom_persistents_.LM_properties.f_host_right;

    if ((!f_host_left) && (!f_host_right)) {
        dist_mode = DistMode::YAW_ONLY;
        dist = trk_vcs_lat_posn - 0.5F * rear_curvature * x2;
        if (dist > elk_cal_.k_default_lane_width * 0.5F) {
            lane_num = ElkLane::RIGHT;
            dist -= elk_cal_.k_default_lane_width * 0.5F;
        } else if (dist < -elk_cal_.k_default_lane_width * 0.5F) {
            lane_num = ElkLane::LEFT;
            dist += elk_cal_.k_default_lane_width * 0.5F;
        } else {
            dist = 0.0F;
        }
    } else if (f_host_left && f_host_right) {
        dist_mode = DistMode::VISION_LM;
        if (offset_right < trk_vcs_lat_posn) {
            lane_num = ElkLane::RIGHT;
            dist = trk_vcs_lat_posn - offset_right;
        } else {
            if (offset_left > trk_vcs_lat_posn) {
                lane_num = ElkLane::LEFT;
                dist = trk_vcs_lat_posn - offset_left;
            }
        }
    } else if (f_host_left) {
        if (offset_left > trk_vcs_lat_posn) {
            lane_num = ElkLane::LEFT;
            dist_mode = DistMode::VISION_LM;
            dist = trk_vcs_lat_posn - offset_left;
        } else {
            offset_right = offset_left + elk_cal_.k_default_lane_width;
            if (offset_right < trk_vcs_lat_posn) {
                lane_num = ElkLane::RIGHT;
                dist_mode = DistMode::VISION_LM_PROJ;
                dist = trk_vcs_lat_posn - offset_right;
            } else {
                dist_mode = DistMode::VISION_LM_PROJ;
            }
        }
    } else {
        if (f_host_right) {
            if (offset_right < trk_vcs_lat_posn) {
                lane_num = ElkLane::RIGHT;
                dist_mode = DistMode::VISION_LM;
                dist = trk_vcs_lat_posn - offset_right;
            } else {
                offset_left = offset_right - elk_cal_.k_default_lane_width;
                if (offset_left > trk_vcs_lat_posn) {
                    lane_num = ElkLane::LEFT;
                    dist_mode = DistMode::VISION_LM_PROJ;
                    dist = trk_vcs_lat_posn - offset_left;
                } else {
                    dist_mode = DistMode::VISION_LM_PROJ;
                }
            }
        }
    }

    obs_data.lane = lane_num;
    obs_data.dist_mode = dist_mode;
    obs_data.dist = dist;
}

// Following as_elk: OncomTargetSelection is now replaced by the flow in Update()
void ElkTargetSelection::OncomTargetSelection(const AsVseOut &vse_out) {
    // This function is now replaced by the flow in Update()
    // Keeping for backward compatibility
}

// Following as_elk: OvertakeTargetSelection is now replaced by the flow in Update()
void ElkTargetSelection::OvertakeTargetSelection(const AsVseOut &vse_out) {
    // This function is now replaced by the flow in Update()
    // Keeping for backward compatibility
}

// Following as_elk 100%: FillOncomOutput (targets are already selected in OncomSelect)
void ElkTargetSelection::FillOncomOutput() {
    // Targets are already filled in OncomSelect via FillTargetInfo
    // oncom_target_3 is memset to 0 (following as_elk)
    std::memset(&oncom_out_.oncom_target_3, 0, sizeof(AsOnComingObject));

    // Roll counter (following as_elk)
    oncom_out_.as_oncoming_rollcnt = oncom_rollcnt_;
    if (oncom_rollcnt_ == 255) {
        oncom_rollcnt_ = 0;
    } else {
        oncom_rollcnt_++;
    }

    oncom_out_.oncoming_major_version = 1;
    oncom_out_.oncoming_minor_version = 3;
    oncom_out_.u8_reserve1 = 0;
}

// Following as_elk 100%: FillOvertakeOutput (targets are already selected in OvertakeSelect)
void ElkTargetSelection::FillOvertakeOutput() {
    // Targets are already filled in OvertakeSelect via FillTargetInfo

    // Roll counter (following as_elk)
    overtake_out_.as_overtaking_rollcnt = overtake_rollcnt_;
    if (overtake_rollcnt_ == 255) {
        overtake_rollcnt_ = 0;
    } else {
        overtake_rollcnt_++;
    }

    overtake_out_.overtaking_major_version = 1;
    overtake_out_.overtaking_minor_version = 3;
    overtake_out_.u8_reserve1 = 0;
}

// Following as_elk 100%: FillTargetInfo for OnComing (ERHA_ELK_TSEL_AS_OC)
// Note: Convert coordinate system from ISO (left+, right-) to as_elk (left-, right+)
void ElkTargetSelection::FillTargetInfo(const ElkObsData &obs_data, AsOnComingObject &oncom_tgt) {
    const auto &obs = obs_data.obs;

    // Position and velocity (following as_elk 100%)
    oncom_tgt.vcs_long_posn = obs->long_posn;
    oncom_tgt.vcs_long_vel = obs->long_vel;
    oncom_tgt.vcs_long_accel = obs->long_accel;
    // Convert lateral coordinates from ISO (left+, right-) to as_elk (left-, right+)
    oncom_tgt.vcs_lat_posn = -obs->lat_posn;   // Negate to convert coordinate system
    oncom_tgt.vcs_lat_vel = -obs->lat_vel;     // Negate to convert coordinate system
    oncom_tgt.vcs_lat_accel = -obs->lat_accel; // Negate to convert coordinate system

    // Size
    oncom_tgt.width = obs->width;
    oncom_tgt.length = obs->length;

    // Distance and heading (following as_elk: vcs_rm_dis = dist, curv_heading = vcs_heading)
    // Note: dist is already in as_elk coordinate system (from UpdateLaneAssignment conversion)
    oncom_tgt.vcs_rm_dis = obs_data.dist; // Following as_elk: use dist from lane assignment
    oncom_tgt.curv_heading = obs->heading;

    // Object properties
    oncom_tgt.object_class = static_cast<uint8_t>(obs->object_class);
    oncom_tgt.fusion_source = static_cast<uint8_t>(obs->fusion_source);
    oncom_tgt.track_status = static_cast<uint8_t>(obs->status);

    // Movement calculation (following as_elk 100%)
    uint8_t movement = 0; // NA
    if (obs->long_vel > 0.1F) {
        movement = 3; // TrackMoving
    }
    bool f_oncoming = (obs->long_vel < 0.01F);
    if (f_oncoming) {
        if (obs->long_vel < -0.01F) {
            movement = 4; // TrackOncoming
        } else {
            movement = 1; // TrackStationary
        }
    }
    oncom_tgt.movement = movement;

    // Confidence fields (following as_elk: cmbbPrimaryConfidence = 195, FcwConfidence = 195, maturity = 3)
    oncom_tgt.cmbbPrimaryConfidence = 195;
    oncom_tgt.FcwConfidence = 195;
    oncom_tgt.maturity = 3;

    // Tracking IDs
    oncom_tgt.visTrkID = (obs->vis_trkID > 0 && obs->vis_trkID < 256) ? static_cast<uint8_t>(obs->vis_trkID) : 0;
    oncom_tgt.track_id = obs->track_id;

    // ELK specific
    oncom_tgt.f_oncoming = f_oncoming ? 1 : 0;
    oncom_tgt.oncom_confidence = static_cast<uint8_t>(obs_data.persistent.oncom_confidence);
    oncom_tgt.collision_prob = static_cast<uint8_t>(obs_data.collision_prob);
}

// Following as_elk 100%: FillTargetInfo for OverTaking (ERHA_ELK_TSEL_AS_OT)
// Note: Convert coordinate system from ISO (left+, right-) to as_elk (left-, right+)
void ElkTargetSelection::FillTargetInfo(const ElkObsData &obs_data, AsOverTakingObject &overtake_tgt) {
    const auto &obs = obs_data.obs;

    // Position and velocity (following as_elk 100%)
    overtake_tgt.vcs_long_posn = obs->long_posn;
    overtake_tgt.vcs_long_vel = obs->long_vel;
    overtake_tgt.vcs_long_accel = obs->long_accel;
    // Convert lateral coordinates from ISO (left+, right-) to as_elk (left-, right+)
    overtake_tgt.vcs_lat_posn = -obs->lat_posn;   // Negate to convert coordinate system
    overtake_tgt.vcs_lat_vel = -obs->lat_vel;     // Negate to convert coordinate system
    overtake_tgt.vcs_lat_accel = -obs->lat_accel; // Negate to convert coordinate system

    // Size
    overtake_tgt.width = obs->width;
    overtake_tgt.length = obs->length;

    // Heading (following as_elk: vcs_heading = curv_heading = vcs_heading)
    overtake_tgt.vcs_heading = obs->heading;

    // Confidence (following as_elk: always 0.0F)
    overtake_tgt.confidence = 0.0F;

    // Object properties
    overtake_tgt.object_class = static_cast<uint8_t>(obs->object_class);
    overtake_tgt.fusion_source = static_cast<uint8_t>(obs->fusion_source);
    overtake_tgt.track_status = static_cast<uint8_t>(obs->status);

    // Tracking IDs
    overtake_tgt.visTrkID = (obs->vis_trkID > 0 && obs->vis_trkID < 256) ? static_cast<uint8_t>(obs->vis_trkID) : 0;
    overtake_tgt.track_id = obs->track_id;
}

// Following as_elk 100%: UpdateOncomCandidatePool
void ElkTargetSelection::UpdateOncomCandidatePool() {
    std::array<float, 3> candidate_pool_long_posn_left = {elk_cal_.k_oncom_long_thres, elk_cal_.k_oncom_long_thres, elk_cal_.k_oncom_long_thres};
    std::array<CollisionProbability, 3> candidate_collision_prob_pool_left = {CollisionProbability::NONE, CollisionProbability::NONE,
                                                                              CollisionProbability::NONE};
    oncom_persistents_.candidate_pool_ID_left.fill(0);

    std::array<float, 3> candidate_pool_long_posn_right = {elk_cal_.k_oncom_long_thres, elk_cal_.k_oncom_long_thres, elk_cal_.k_oncom_long_thres};
    std::array<CollisionProbability, 3> candidate_collision_prob_pool_right = {CollisionProbability::NONE, CollisionProbability::NONE,
                                                                               CollisionProbability::NONE};
    oncom_persistents_.candidate_pool_ID_right.fill(0);

    uint8_t j_left = 1;
    uint8_t j_right = 1;

    // Following as_elk: iterate from 1 to k_ETSEL_MAX_CIP_TRKS (track_id is 1-based in as_elk)
    for (size_t i = 0; i < kMaxNormalObject; ++i) {
        uint8_t track_id = static_cast<uint8_t>(i + 1); // Convert to 1-based

        if ((obs_data_[i].collision_prob > CollisionProbability::NONE)  &&  IsCurrentOncomingMotion(*obs_data_[i].obs)) {
            // Left pool
            if (!IsMemberOfArray(track_id, oncom_persistents_.oncom_left_id_pool) && obs_data_[i].persistent.oncom_confidence > Confidence::LOW &&
                obs_data_[i].lane == ElkLane::LEFT) {

                // Fix: Limit index to array size to prevent out-of-bounds access
                uint8_t pool_size = static_cast<uint8_t>(oncom_persistents_.candidate_pool_ID_left.size());
                uint8_t max_pool_idx = (elk_cal_.k_Max_Oncom_Pool_Trks > pool_size) ? (pool_size - 1) : (elk_cal_.k_Max_Oncom_Pool_Trks - 1);

                if (j_left > elk_cal_.k_Max_Oncom_Pool_Trks) {
                    RankCandidate(oncom_persistents_.candidate_pool_ID_left, candidate_pool_long_posn_left, candidate_collision_prob_pool_left);

                    if (max_pool_idx < candidate_collision_prob_pool_left.size() &&
                        (obs_data_[i].collision_prob > candidate_collision_prob_pool_left[max_pool_idx] ||
                         (obs_data_[i].collision_prob == candidate_collision_prob_pool_left[max_pool_idx] &&
                          obs_data_[i].obs->long_posn < candidate_pool_long_posn_left[max_pool_idx]))) {
                        if (max_pool_idx < oncom_persistents_.candidate_pool_ID_left.size()) {
                            oncom_persistents_.candidate_pool_ID_left[max_pool_idx] = track_id;
                            candidate_pool_long_posn_left[max_pool_idx] = obs_data_[i].obs->long_posn;
                            candidate_collision_prob_pool_left[max_pool_idx] = obs_data_[i].collision_prob;
                        }
                    }
                } else {
                    if ((j_left - 1) < oncom_persistents_.candidate_pool_ID_left.size()) {
                        oncom_persistents_.candidate_pool_ID_left[j_left - 1] = track_id;
                        candidate_pool_long_posn_left[j_left - 1] = obs_data_[i].obs->long_posn;
                        candidate_collision_prob_pool_left[j_left - 1] = obs_data_[i].collision_prob;
                        j_left++;
                    }
                }
            }

            // Right pool
            if (!IsMemberOfArray(track_id, oncom_persistents_.oncom_right_id_pool) && obs_data_[i].persistent.oncom_confidence > Confidence::LOW &&
                obs_data_[i].lane == ElkLane::RIGHT) {

                // Fix: Limit index to array size to prevent out-of-bounds access
                uint8_t pool_size = static_cast<uint8_t>(oncom_persistents_.candidate_pool_ID_right.size());
                uint8_t max_pool_idx = (elk_cal_.k_Max_Oncom_Pool_Trks > pool_size) ? (pool_size - 1) : (elk_cal_.k_Max_Oncom_Pool_Trks - 1);

                if (j_right > elk_cal_.k_Max_Oncom_Pool_Trks) {
                    RankCandidate(oncom_persistents_.candidate_pool_ID_right, candidate_pool_long_posn_right, candidate_collision_prob_pool_right);

                    if (max_pool_idx < candidate_collision_prob_pool_right.size() &&
                        (obs_data_[i].collision_prob > candidate_collision_prob_pool_right[max_pool_idx] ||
                         (obs_data_[i].collision_prob == candidate_collision_prob_pool_right[max_pool_idx] &&
                          obs_data_[i].obs->long_posn < candidate_pool_long_posn_right[max_pool_idx]))) {
                        if (max_pool_idx < oncom_persistents_.candidate_pool_ID_right.size()) {
                            oncom_persistents_.candidate_pool_ID_right[max_pool_idx] = track_id;
                            candidate_pool_long_posn_right[max_pool_idx] = obs_data_[i].obs->long_posn;
                            candidate_collision_prob_pool_right[max_pool_idx] = obs_data_[i].collision_prob;
                        }
                    }
                } else {
                    if ((j_right - 1) < oncom_persistents_.candidate_pool_ID_right.size()) {
                        oncom_persistents_.candidate_pool_ID_right[j_right - 1] = track_id;
                        candidate_pool_long_posn_right[j_right - 1] = obs_data_[i].obs->long_posn;
                        candidate_collision_prob_pool_right[j_right - 1] = obs_data_[i].collision_prob;
                        j_right++;
                    }
                }
            }
        }
    }

    if (j_left > 2) {
        RankCandidate(oncom_persistents_.candidate_pool_ID_left, candidate_pool_long_posn_left, candidate_collision_prob_pool_left);
    }

    if (j_right > 2) {
        RankCandidate(oncom_persistents_.candidate_pool_ID_right, candidate_pool_long_posn_right, candidate_collision_prob_pool_right);
    }
}

// Following as_elk 100%: UpdateOvertakeCandidatePool
void ElkTargetSelection::UpdateOvertakeCandidatePool() {
    std::array<float, 3> candidate_pool_long_posn_rear_left = {elk_cal_.k_ot_front_max_x, elk_cal_.k_ot_front_max_x, elk_cal_.k_ot_front_max_x};
    std::array<CollisionProbability, 3> candidate_collision_prob_pool_rear_left = {CollisionProbability::NONE, CollisionProbability::NONE,
                                                                                   CollisionProbability::NONE};
    overtake_persistents_.candidate_pool_ID_rear_left.fill(0);
    uint8_t j_rear_left = 1;

    std::array<float, 3> candidate_pool_long_posn_rear_right = {elk_cal_.k_ot_front_max_x, elk_cal_.k_ot_front_max_x, elk_cal_.k_ot_front_max_x};
    std::array<CollisionProbability, 3> candidate_collision_prob_pool_rear_right = {CollisionProbability::NONE, CollisionProbability::NONE,
                                                                                    CollisionProbability::NONE};
    overtake_persistents_.candidate_pool_ID_rear_right.fill(0);
    uint8_t j_rear_right = 1;

    std::array<float, 3> candidate_pool_long_posn_front_left = {elk_cal_.k_ot_front_max_x, elk_cal_.k_ot_front_max_x, elk_cal_.k_ot_front_max_x};
    std::array<CollisionProbability, 3> candidate_collision_prob_pool_front_left = {CollisionProbability::NONE, CollisionProbability::NONE,
                                                                                    CollisionProbability::NONE};
    overtake_persistents_.candidate_pool_ID_front_left.fill(0);
    uint8_t j_front_left = 1;

    std::array<float, 3> candidate_pool_long_posn_front_right = {elk_cal_.k_ot_front_max_x, elk_cal_.k_ot_front_max_x, elk_cal_.k_ot_front_max_x};
    std::array<CollisionProbability, 3> candidate_collision_prob_pool_front_right = {CollisionProbability::NONE, CollisionProbability::NONE,
                                                                                     CollisionProbability::NONE};
    overtake_persistents_.candidate_pool_ID_front_right.fill(0);
    uint8_t j_front_right = 1;

    for (size_t i = 0; i < kMaxNormalObject; ++i) {
        uint8_t track_id = static_cast<uint8_t>(i + 1); // Convert to 1-based

        if (obs_data_[i].collision_prob > CollisionProbability::NONE) {
            // Rear left
            if (!IsMemberOfArray(track_id, overtake_persistents_.overtake_rear_left_id_pool) && obs_data_[i].lane == ElkLane::LEFT &&
                obs_data_[i].persistent.f_rear_zone_interest) {

                // Fix: Limit index to array size to prevent out-of-bounds access
                uint8_t pool_size = static_cast<uint8_t>(overtake_persistents_.candidate_pool_ID_rear_left.size());
                uint8_t max_pool_idx = (elk_cal_.k_Max_Overtake_Pool_Trks > pool_size) ? (pool_size - 1) : (elk_cal_.k_Max_Overtake_Pool_Trks - 1);

                if (j_rear_left > elk_cal_.k_Max_Overtake_Pool_Trks) {
                    RankCandidate(overtake_persistents_.candidate_pool_ID_rear_left, candidate_pool_long_posn_rear_left,
                                  candidate_collision_prob_pool_rear_left);

                    if (max_pool_idx < candidate_collision_prob_pool_rear_left.size() &&
                        (obs_data_[i].collision_prob > candidate_collision_prob_pool_rear_left[max_pool_idx] ||
                         (obs_data_[i].collision_prob == candidate_collision_prob_pool_rear_left[max_pool_idx] &&
                          std::abs(obs_data_[i].obs->long_posn) < candidate_pool_long_posn_rear_left[max_pool_idx]))) {
                        if (max_pool_idx < overtake_persistents_.candidate_pool_ID_rear_left.size()) {
                            overtake_persistents_.candidate_pool_ID_rear_left[max_pool_idx] = track_id;
                            candidate_pool_long_posn_rear_left[max_pool_idx] = std::abs(obs_data_[i].obs->long_posn);
                            candidate_collision_prob_pool_rear_left[max_pool_idx] = obs_data_[i].collision_prob;
                        }
                    }
                } else {
                    if ((j_rear_left - 1) < overtake_persistents_.candidate_pool_ID_rear_left.size()) {
                        overtake_persistents_.candidate_pool_ID_rear_left[j_rear_left - 1] = track_id;
                        candidate_pool_long_posn_rear_left[j_rear_left - 1] = std::abs(obs_data_[i].obs->long_posn);
                        candidate_collision_prob_pool_rear_left[j_rear_left - 1] = obs_data_[i].collision_prob;
                        j_rear_left++;
                    }
                }
            }

            // Rear right
            if (!IsMemberOfArray(track_id, overtake_persistents_.overtake_rear_right_id_pool) && obs_data_[i].lane == ElkLane::RIGHT &&
                obs_data_[i].persistent.f_rear_zone_interest) {

                // Fix: Limit index to array size to prevent out-of-bounds access
                uint8_t pool_size = static_cast<uint8_t>(overtake_persistents_.candidate_pool_ID_rear_right.size());
                uint8_t max_pool_idx = (elk_cal_.k_Max_Overtake_Pool_Trks > pool_size) ? (pool_size - 1) : (elk_cal_.k_Max_Overtake_Pool_Trks - 1);

                if (j_rear_right > elk_cal_.k_Max_Overtake_Pool_Trks) {
                    RankCandidate(overtake_persistents_.candidate_pool_ID_rear_right, candidate_pool_long_posn_rear_right,
                                  candidate_collision_prob_pool_rear_right);

                    if (max_pool_idx < candidate_collision_prob_pool_rear_right.size() &&
                        (obs_data_[i].collision_prob > candidate_collision_prob_pool_rear_right[max_pool_idx] ||
                         (obs_data_[i].collision_prob == candidate_collision_prob_pool_rear_right[max_pool_idx] &&
                          std::abs(obs_data_[i].obs->long_posn) < candidate_pool_long_posn_rear_right[max_pool_idx]))) {
                        if (max_pool_idx < overtake_persistents_.candidate_pool_ID_rear_right.size()) {
                            overtake_persistents_.candidate_pool_ID_rear_right[max_pool_idx] = track_id;
                            candidate_pool_long_posn_rear_right[max_pool_idx] = std::abs(obs_data_[i].obs->long_posn);
                            candidate_collision_prob_pool_rear_right[max_pool_idx] = obs_data_[i].collision_prob;
                        }
                    }
                } else {
                    if ((j_rear_right - 1) < overtake_persistents_.candidate_pool_ID_rear_right.size()) {
                        overtake_persistents_.candidate_pool_ID_rear_right[j_rear_right - 1] = track_id;
                        candidate_pool_long_posn_rear_right[j_rear_right - 1] = std::abs(obs_data_[i].obs->long_posn);
                        candidate_collision_prob_pool_rear_right[j_rear_right - 1] = obs_data_[i].collision_prob;
                        j_rear_right++;
                    }
                }
            }

            // Front left
            if (!IsMemberOfArray(track_id, overtake_persistents_.overtake_front_left_id_pool) && obs_data_[i].lane == ElkLane::LEFT &&
                obs_data_[i].persistent.f_front_zone_interest) {

                // Fix: Limit index to array size to prevent out-of-bounds access
                uint8_t pool_size = static_cast<uint8_t>(overtake_persistents_.candidate_pool_ID_front_left.size());
                uint8_t max_pool_idx = (elk_cal_.k_Max_Overtake_Pool_Trks > pool_size) ? (pool_size - 1) : (elk_cal_.k_Max_Overtake_Pool_Trks - 1);

                if (j_front_left > elk_cal_.k_Max_Overtake_Pool_Trks) {
                    RankCandidate(overtake_persistents_.candidate_pool_ID_front_left, candidate_pool_long_posn_front_left,
                                  candidate_collision_prob_pool_front_left);

                    if (max_pool_idx < candidate_collision_prob_pool_front_left.size() &&
                        (obs_data_[i].collision_prob > candidate_collision_prob_pool_front_left[max_pool_idx] ||
                         (obs_data_[i].collision_prob == candidate_collision_prob_pool_front_left[max_pool_idx] &&
                          obs_data_[i].obs->long_posn < candidate_pool_long_posn_front_left[max_pool_idx]))) {
                        if (max_pool_idx < overtake_persistents_.candidate_pool_ID_front_left.size()) {
                            overtake_persistents_.candidate_pool_ID_front_left[max_pool_idx] = track_id;
                            candidate_pool_long_posn_front_left[max_pool_idx] = obs_data_[i].obs->long_posn;
                            candidate_collision_prob_pool_front_left[max_pool_idx] = obs_data_[i].collision_prob;
                        }
                    }
                } else {
                    if ((j_front_left - 1) < overtake_persistents_.candidate_pool_ID_front_left.size()) {
                        overtake_persistents_.candidate_pool_ID_front_left[j_front_left - 1] = track_id;
                        candidate_pool_long_posn_front_left[j_front_left - 1] = obs_data_[i].obs->long_posn;
                        candidate_collision_prob_pool_front_left[j_front_left - 1] = obs_data_[i].collision_prob;
                        j_front_left++;
                    }
                }
            }

            // Front right
            if (!IsMemberOfArray(track_id, overtake_persistents_.overtake_front_right_id_pool) && obs_data_[i].lane == ElkLane::RIGHT &&
                obs_data_[i].persistent.f_front_zone_interest) {

                // Fix: Limit index to array size to prevent out-of-bounds access
                uint8_t pool_size = static_cast<uint8_t>(overtake_persistents_.candidate_pool_ID_front_right.size());
                uint8_t max_pool_idx = (elk_cal_.k_Max_Overtake_Pool_Trks > pool_size) ? (pool_size - 1) : (elk_cal_.k_Max_Overtake_Pool_Trks - 1);

                if (j_front_right > elk_cal_.k_Max_Overtake_Pool_Trks) {
                    RankCandidate(overtake_persistents_.candidate_pool_ID_front_right, candidate_pool_long_posn_front_right,
                                  candidate_collision_prob_pool_front_right);

                    if (max_pool_idx < candidate_collision_prob_pool_front_right.size() &&
                        (obs_data_[i].collision_prob > candidate_collision_prob_pool_front_right[max_pool_idx] ||
                         (obs_data_[i].collision_prob == candidate_collision_prob_pool_front_right[max_pool_idx] &&
                          obs_data_[i].obs->long_posn < candidate_pool_long_posn_front_right[max_pool_idx]))) {
                        if (max_pool_idx < overtake_persistents_.candidate_pool_ID_front_right.size()) {
                            overtake_persistents_.candidate_pool_ID_front_right[max_pool_idx] = track_id;
                            candidate_pool_long_posn_front_right[max_pool_idx] = obs_data_[i].obs->long_posn;
                            candidate_collision_prob_pool_front_right[max_pool_idx] = obs_data_[i].collision_prob;
                        }
                    }
                } else {
                    if ((j_front_right - 1) < overtake_persistents_.candidate_pool_ID_front_right.size()) {
                        overtake_persistents_.candidate_pool_ID_front_right[j_front_right - 1] = track_id;
                        candidate_pool_long_posn_front_right[j_front_right - 1] = obs_data_[i].obs->long_posn;
                        candidate_collision_prob_pool_front_right[j_front_right - 1] = obs_data_[i].collision_prob;
                        j_front_right++;
                    }
                }
            }
        }
    }

    if (j_rear_left > 2) {
        RankCandidate(overtake_persistents_.candidate_pool_ID_rear_left, candidate_pool_long_posn_rear_left, candidate_collision_prob_pool_rear_left);
    }
    if (j_rear_right > 2) {
        RankCandidate(overtake_persistents_.candidate_pool_ID_rear_right, candidate_pool_long_posn_rear_right,
                      candidate_collision_prob_pool_rear_right);
    }
    if (j_front_left > 2) {
        RankCandidate(overtake_persistents_.candidate_pool_ID_front_left, candidate_pool_long_posn_front_left,
                      candidate_collision_prob_pool_front_left);
    }
    if (j_front_right > 2) {
        RankCandidate(overtake_persistents_.candidate_pool_ID_front_right, candidate_pool_long_posn_front_right,
                      candidate_collision_prob_pool_front_right);
    }
}

// Following as_elk 100%: UpdateOncomTargetPool
uint8_t ElkTargetSelection::UpdateOncomTargetPool(const std::array<uint8_t, 3> &candidate_pool_ID, ElkLane laneEnum) {
    std::array<uint8_t, 3> &oncom_id_pool =
        (laneEnum == ElkLane::LEFT) ? oncom_persistents_.oncom_left_id_pool : oncom_persistents_.oncom_right_id_pool;

    uint8_t max_tsel_trks = elk_cal_.k_Max_Oncom_Pool_Trks;
    // Ensure loop bound doesn't exceed array size (following as_elk: max_tsel_trks should be 3)
    uint8_t loop_bound = (max_tsel_trks > oncom_id_pool.size()) ? static_cast<uint8_t>(oncom_id_pool.size()) : max_tsel_trks;

    // Check if previous targets should be released
    for (uint8_t i = 0; i < loop_bound; ++i) {
        uint8_t track_ID = oncom_id_pool[i];
        if (track_ID > 0) {
            size_t obs_idx = track_ID - 1;
            if (obs_idx < kMaxNormalObject) {
                if (obs_data_[obs_idx].persistent.oncom_confidence == Confidence::LOW ||
                    obs_data_[obs_idx].collision_prob == CollisionProbability::NONE || obs_data_[obs_idx].lane != laneEnum) {
                    oncom_id_pool[i] = static_cast<uint8_t>(0);
                }
            }
        }
    }

    // Find empty slots and candidate slots
    std::array<uint8_t, 3> index_oncom_empty = {0, 0, 0};
    std::array<uint8_t, 3> index_oncom_candidate = {0, 0, 0};
    uint8_t len_empty = 0;
    uint8_t len_candidate = 0;

    for (uint8_t i = 0; i < loop_bound; ++i) {
        if (oncom_id_pool[i] == 0) {
            index_oncom_empty[len_empty] = i;
            len_empty++;
        }
        if (candidate_pool_ID[i] > 0) {
            index_oncom_candidate[len_candidate] = i;
            len_candidate++;
        }
    }

    uint8_t num_update = (len_empty < len_candidate) ? len_empty : len_candidate;

    // Fill empty slots with candidates
    if (len_candidate > 0) {
        for (uint8_t i = 0; i < num_update; ++i) {
            uint8_t ind_empty = index_oncom_empty[i];
            uint8_t ind_candidate = index_oncom_candidate[i];
            oncom_id_pool[ind_empty] = candidate_pool_ID[ind_candidate];
        }

        // Handle extra candidates using reArrangePool
        if (len_empty < len_candidate) {
            std::array<uint8_t, 3> extra_id = {0, 0, 0};
            uint8_t extra_id_valid_length = 0;

            for (uint8_t i = len_empty; i < len_candidate; ++i) {
                uint8_t ind_candidate = index_oncom_candidate[i];
                extra_id[extra_id_valid_length] = candidate_pool_ID[ind_candidate];
                extra_id_valid_length++;
            }

            ReArrangePool(extra_id, extra_id_valid_length, oncom_id_pool);
        }
    }

    // Count valid targets
    uint8_t num_oncom_trks = 0;
    for (uint8_t i = 0; i < loop_bound; ++i) {
        if (oncom_id_pool[i] > 0) {
            num_oncom_trks++;
        }
    }

    return num_oncom_trks;
}

// Following as_elk 100%: UpdateOvertakeTargetPool
uint8_t ElkTargetSelection::UpdateOvertakeTargetPool(const std::array<uint8_t, 3> &candidate_pool_ID, bool frontFlag, bool rearFlag, ElkLane laneEnum,
                                              std::array<uint8_t, 3> &id_pool) {
    uint8_t max_tsel_trks = elk_cal_.k_Max_Overtake_Pool_Trks;
    // Ensure loop bound doesn't exceed array size (id_pool is size 3, but max_tsel_trks might be 5)
    uint8_t loop_bound = (max_tsel_trks > id_pool.size()) ? static_cast<uint8_t>(id_pool.size()) : max_tsel_trks;

    // Check if previous targets should be released
    for (uint8_t i = 0; i < loop_bound; ++i) {
        uint8_t track_ID = id_pool[i];
        if (track_ID > 0) {
            size_t obs_idx = track_ID - 1;
            if (obs_idx < kMaxNormalObject) {
                // bool b_vld_long_zone = ((obs_data_[obs_idx].persistent.f_front_zone_interest == frontFlag) &&
                //                         (obs_data_[obs_idx].persistent.f_rear_zone_interest == rearFlag)) ||
                //     (obs_data_[obs_idx].persistent.f_front_zone_interest && obs_data_[obs_idx].persistent.f_rear_zone_interest);
                bool b_vld_long_zone = (obs_data_[obs_idx].persistent.f_front_zone_interest == frontFlag) ||
                                    (obs_data_[obs_idx].persistent.f_rear_zone_interest == rearFlag);

                if (!b_vld_long_zone  ||  (obs_data_[obs_idx].collision_prob == CollisionProbability::NONE)  ||  (obs_data_[obs_idx].lane != laneEnum)) {
                    //AD_LINFO(ElkTargetSelection::UpdateOvertakeTargetPool) << "remove slot id " << id_pool[i] << " from overtak id_pool";
                    id_pool[i] = 0;
                }
            }
        }
    }

    // Find empty slots and candidate slots
    std::array<uint8_t, 3> index_empty = {0, 0, 0};
    std::array<uint8_t, 3> index_candidate = {0, 0, 0};
    uint8_t len_empty = 0;
    uint8_t len_candidate = 0;

    for (uint8_t i = 0; i < loop_bound; ++i) {
        if (id_pool[i] == 0) {
            index_empty[len_empty] = i;
            len_empty++;
        }
        if (candidate_pool_ID[i] > 0) {
            index_candidate[len_candidate] = i;
            len_candidate++;
        }
    }

    uint8_t num_update = (len_empty < len_candidate) ? len_empty : len_candidate;

    // Fill empty slots with candidates
    if (len_candidate > 0) {
        for (uint8_t i = 0; i < num_update; ++i) {
            uint8_t ind_empty = index_empty[i];
            uint8_t ind_candidate = index_candidate[i];
            id_pool[ind_empty] = candidate_pool_ID[ind_candidate];
        }

        // Handle extra candidates using reArrangePool
        if (len_empty < len_candidate) {
            std::array<uint8_t, 3> extra_id = {0, 0, 0};
            uint8_t extra_id_valid_length = 0;

            for (uint8_t i = len_empty; i < len_candidate; ++i) {
                uint8_t ind_candidate = index_candidate[i];
                extra_id[extra_id_valid_length] = candidate_pool_ID[ind_candidate];
                extra_id_valid_length++;
            }

            ReArrangePool(extra_id, extra_id_valid_length, id_pool);
        }
    }

    // Count valid targets
    uint8_t num_trks = 0;
    for (uint8_t i = 0; i < loop_bound; ++i) {
        if (id_pool[i] > 0) {
            num_trks++;
        }
    }

    return num_trks;
}

// Following as_elk 100%: ReArrangePool
void ElkTargetSelection::ReArrangePool(const std::array<uint8_t, 3> &extra_id, uint8_t extra_id_valid_length, std::array<uint8_t, 3> &id_pool) {
    std::array<uint8_t, 3> avail_id = {0, 0, 0};
    std::array<uint8_t, 3> avail_id_index = {0, 0, 0};
    uint8_t avail_id_valid_length = 0;

    // Copy current id_pool to avail_id
    // Fix: Limit loop to array size to prevent out-of-bounds access
    uint8_t pool_size = static_cast<uint8_t>(id_pool.size());
    uint8_t max_loop = pool_size;
    for (uint8_t i = 0; i < max_loop; ++i) {
        if (id_pool[i] > 0) {
            avail_id_index[avail_id_valid_length] = i;
            avail_id[avail_id_valid_length] = id_pool[i];
            avail_id_valid_length++;
        }
    }

    // Try to insert extra_id into id_pool
    for (uint8_t i = 0; i < extra_id_valid_length; ++i) {
        CollisionProbability temp_prob = CollisionProbability::HIGH;
        float temp_dist = -255.0F;
        uint8_t temp_index = 0;
        bool f_insert = false;
        uint8_t candidate_id = extra_id[i];

        if ((candidate_id == 0)  ||  (candidate_id > kMaxNormalObject))
            continue;
        size_t candidate_idx = candidate_id - 1;

        for (uint8_t j = 0; j < avail_id_valid_length; ++j) {
            uint8_t track_id = avail_id[j];
            if ((track_id == 0)  ||  (track_id > kMaxNormalObject))
                continue;
            size_t track_idx = track_id - 1;

            CollisionProbability collision_prob = obs_data_[track_idx].collision_prob;
            float long_posn = std::abs(obs_data_[track_idx].obs->long_posn);

            if ((obs_data_[candidate_idx].collision_prob > collision_prob && temp_prob > collision_prob) ||
                (temp_dist < long_posn && std::abs(obs_data_[candidate_idx].obs->long_posn) < long_posn)) {
                temp_index = avail_id_index[j];
                temp_prob = collision_prob;
                temp_dist = long_posn;
                f_insert = true;
            }
        }

        if (f_insert) {
            // Fix: Check temp_index bounds to prevent out-of-bounds access
            if (temp_index < id_pool.size()) {
                id_pool[temp_index] = candidate_id;
                if (temp_index < avail_id.size()) {
                    avail_id[temp_index] = candidate_id;
                }
            }
        } else {
            break;
        }
    }
}

// Following as_elk 100%: OncomDownSelection
void ElkTargetSelection::OncomDownSelection() {
    UpdateOncomCandidatePool();

    oncom_persistents_.num_oncom_left_trks = UpdateOncomTargetPool(oncom_persistents_.candidate_pool_ID_left, ElkLane::LEFT);

    oncom_persistents_.num_oncom_right_trks = UpdateOncomTargetPool(oncom_persistents_.candidate_pool_ID_right, ElkLane::RIGHT);
}

// Following as_elk 100%: UpdateOvertakePool
void ElkTargetSelection::UpdateOvertakePool() {
    overtake_persistents_.num_overtake_rear_left_trks = UpdateOvertakeTargetPool(overtake_persistents_.candidate_pool_ID_rear_left, false, true,
                                                                                ElkLane::LEFT, overtake_persistents_.overtake_rear_left_id_pool);

    overtake_persistents_.num_overtake_rear_right_trks = UpdateOvertakeTargetPool(overtake_persistents_.candidate_pool_ID_rear_right, false, true,
                                                                                ElkLane::RIGHT, overtake_persistents_.overtake_rear_right_id_pool);

    overtake_persistents_.num_overtake_front_left_trks = UpdateOvertakeTargetPool(overtake_persistents_.candidate_pool_ID_front_left, true, false,
                                                                                ElkLane::LEFT, overtake_persistents_.overtake_front_left_id_pool);

    overtake_persistents_.num_overtake_front_right_trks = UpdateOvertakeTargetPool(overtake_persistents_.candidate_pool_ID_front_right, true, false, 
                                                                                ElkLane::RIGHT, overtake_persistents_.overtake_front_right_id_pool);
}

// Following as_elk 100%: OvertakeDownSelection
void ElkTargetSelection::OvertakeDownSelection() {
    UpdateOvertakeCandidatePool();
    UpdateOvertakePool();
}

// Following as_elk 100%: OncomSelect
void ElkTargetSelection::OncomSelect() {
    // Following as_elk: oncomSelect logic
    std::array<uint8_t, 3> elk_leftLanTrkId = {0, 0, 0};
    std::array<float, 3> elk_leftLanTrkDist = {0.0F, 0.0F, 0.0F};
    std::array<uint8_t, 3> elk_rightLanTrkId = {0, 0, 0};
    std::array<float, 3> elk_rightLanTrkDist = {0.0F, 0.0F, 0.0F};

    uint8_t elk_num_left = 0;
    uint8_t elk_num_right = 0;

    // Collect left targets
    // Fix: Limit loop to array size to prevent out-of-bounds access
    uint8_t max_candidate = (elk_cal_.k_Max_Candidate > oncom_persistents_.oncom_left_id_pool.size())
        ? static_cast<uint8_t>(oncom_persistents_.oncom_left_id_pool.size())
        : elk_cal_.k_Max_Candidate;
    for (uint8_t i = 0; i < max_candidate; ++i) {
        uint8_t trkid_left = oncom_persistents_.oncom_left_id_pool[i];
        if ((trkid_left > 0)  &&  (trkid_left <= kMaxNormalObject)) {
            size_t obs_idx = trkid_left - 1;
            if (elk_num_left < elk_leftLanTrkId.size()) {
                elk_leftLanTrkId[elk_num_left] = trkid_left;
                elk_leftLanTrkDist[elk_num_left] = obs_data_[obs_idx].obs->long_posn;
                elk_num_left++;
            }
        }

        uint8_t trkid_right = oncom_persistents_.oncom_right_id_pool[i];
        if ((trkid_right > 0)  &&  (trkid_right <= kMaxNormalObject)) {
            size_t obs_idx = trkid_right - 1;
            if (elk_num_right < elk_rightLanTrkId.size()) {
                elk_rightLanTrkId[elk_num_right] = trkid_right;
                elk_rightLanTrkDist[elk_num_right] = obs_data_[obs_idx].obs->long_posn;
                elk_num_right++;
            }
        }
    }

    // Select closest from left
    if (elk_num_left < 1) {
        // oncom_target_1 will be memset to 0 in FillOncomOutput
    } else {
        uint8_t elk_indx = FindMinIndex(elk_leftLanTrkDist, 1, elk_num_left);
        // Fix: Check elk_indx bounds to prevent out-of-bounds access
        if ((elk_indx >= 1)  &&  (elk_indx <= elk_num_left)  &&  ((elk_indx - 1) < elk_leftLanTrkId.size())) {
            uint8_t traker_idx = elk_leftLanTrkId[elk_indx - 1];
            if ((traker_idx > 0)  &&  (traker_idx <= kMaxNormalObject)) {
                size_t obs_idx = traker_idx - 1;
                FillTargetInfo(obs_data_[obs_idx], oncom_out_.oncom_target_1);
            }
        }
    }

    // Select closest from right
    if (elk_num_right < 1) {
        // oncom_target_2 will be memset to 0 in FillOncomOutput
    } else {
        uint8_t elk_indx = FindMinIndex(elk_rightLanTrkDist, 1, elk_num_right);
        // Fix: Check elk_indx bounds to prevent out-of-bounds access
        if ((elk_indx >= 1)  &&  (elk_indx <= elk_num_right)  &&  ((elk_indx - 1) < elk_rightLanTrkId.size())) {
            uint8_t traker_idx = elk_rightLanTrkId[elk_indx - 1];
            if ((traker_idx > 0)  &&  (traker_idx <= kMaxNormalObject)) {
                size_t obs_idx = traker_idx - 1;
                FillTargetInfo(obs_data_[obs_idx], oncom_out_.oncom_target_2);
            }
        }
    }
}

// Following as_elk 100%: OvertakeSelect
void ElkTargetSelection::OvertakeSelect() {
    // Following as_elk: overtakeSelect logic
    std::array<uint8_t, 3> elk_TrkId_rear_left = {0, 0, 0};
    std::array<float, 3> elk_TrkDist_rear_left = {0.0F, 0.0F, 0.0F};
    std::array<uint8_t, 3> elk_TrkId_rear_right = {0, 0, 0};
    std::array<float, 3> elk_TrkDist_rear_right = {0.0F, 0.0F, 0.0F};
    std::array<uint8_t, 3> elk_TrkId_front_left = {0, 0, 0};
    std::array<float, 3> elk_TrkDist_front_left = {0.0F, 0.0F, 0.0F};
    std::array<uint8_t, 3> elk_TrkId_front_right = {0, 0, 0};
    std::array<float, 3> elk_TrkDist_front_right = {0.0F, 0.0F, 0.0F};

    uint8_t elk_num_rear_left = 0;
    uint8_t elk_num_rear_right = 0;
    uint8_t elk_num_front_left = 0;
    uint8_t elk_num_front_right = 0;

    // Collect targets from each zone
    // Fix: Limit loop to array size to prevent out-of-bounds access
    uint8_t pool_size = static_cast<uint8_t>(overtake_persistents_.overtake_rear_left_id_pool.size());
    uint8_t max_loop = (elk_cal_.k_Max_Overtake_Pool_Trks > pool_size) ? pool_size : elk_cal_.k_Max_Overtake_Pool_Trks;
    for (uint8_t n = 1; n <= max_loop; ++n) {
        uint8_t trkid_rear_left = overtake_persistents_.overtake_rear_left_id_pool[n - 1];
        if ((trkid_rear_left > 0)  &&  (trkid_rear_left <= kMaxNormalObject)) {
            if (elk_num_rear_left < elk_TrkId_rear_left.size()) {
                size_t obs_idx = trkid_rear_left - 1;
                elk_TrkId_rear_left[elk_num_rear_left] = trkid_rear_left;
                elk_TrkDist_rear_left[elk_num_rear_left] = std::abs(obs_data_[obs_idx].obs->long_posn);
                elk_num_rear_left++;
            }
        }

        uint8_t trkid_rear_right = overtake_persistents_.overtake_rear_right_id_pool[n - 1];
        if ((trkid_rear_right > 0)  &&  (trkid_rear_right <= kMaxNormalObject)) {
            if (elk_num_rear_right < elk_TrkId_rear_right.size()) {
                size_t obs_idx = trkid_rear_right - 1;
                elk_TrkId_rear_right[elk_num_rear_right] = trkid_rear_right;
                elk_TrkDist_rear_right[elk_num_rear_right] = std::abs(obs_data_[obs_idx].obs->long_posn);
                elk_num_rear_right++;
            }
        }

        uint8_t trkid_front_left = overtake_persistents_.overtake_front_left_id_pool[n - 1];
        if ((trkid_front_left > 0)  &&  (trkid_front_left <= kMaxNormalObject)) {
            if (elk_num_front_left < elk_TrkId_front_left.size()) {
                size_t obs_idx = trkid_front_left - 1;
                elk_TrkId_front_left[elk_num_front_left] = trkid_front_left;
                elk_TrkDist_front_left[elk_num_front_left] = obs_data_[obs_idx].obs->long_posn;
                elk_num_front_left++;
            }
        }

        uint8_t trkid_front_right = overtake_persistents_.overtake_front_right_id_pool[n - 1];
        if ((trkid_front_right > 0)  &&  (trkid_front_right <= kMaxNormalObject)) {
            if (elk_num_front_right < elk_TrkId_front_right.size()) {
                size_t obs_idx = trkid_front_right - 1;
                elk_TrkId_front_right[elk_num_front_right] = trkid_front_right;
                elk_TrkDist_front_right[elk_num_front_right] = obs_data_[obs_idx].obs->long_posn;
                elk_num_front_right++;
            }
        }
    }

    // Select closest from each zone
    if (elk_num_rear_left < 1) {
        // rear_left will be memset to 0
    } else {
        uint8_t elk_indx = FindMinIndex(elk_TrkDist_rear_left, 1, elk_num_rear_left);
        if ((elk_indx >= 1)  &&  (elk_indx <= elk_num_rear_left)) {
            uint8_t traker_idx = elk_TrkId_rear_left[elk_indx - 1];
            if ((traker_idx > 0)  &&  (traker_idx <= kMaxNormalObject)) {
                FillTargetInfo(obs_data_[traker_idx - 1], overtake_out_.overtake_target_rear_left);
            }
        }
    }

    if (elk_num_rear_right < 1) {
        // rear_right will be memset to 0
    } else {
        uint8_t elk_indx = FindMinIndex(elk_TrkDist_rear_right, 1, elk_num_rear_right);
        if ((elk_indx >= 1)  &&  (elk_indx <= elk_num_rear_right)) {
            uint8_t traker_idx = elk_TrkId_rear_right[elk_indx - 1];
            if ((traker_idx > 0)  &&  (traker_idx <= kMaxNormalObject)) {
                FillTargetInfo(obs_data_[traker_idx - 1], overtake_out_.overtake_target_rear_right);
            }
        }
    }

    if (elk_num_front_left < 1) {
        // front_left will be memset to 0
    } else {
        uint8_t elk_indx = FindMinIndex(elk_TrkDist_front_left, 1, elk_num_front_left);
        if ((elk_indx >= 1)  &&  (elk_indx <= elk_num_front_left)) {
            uint8_t traker_idx = elk_TrkId_front_left[elk_indx - 1];
            if ((traker_idx > 0)  &&  (traker_idx <= kMaxNormalObject)) {
                FillTargetInfo(obs_data_[traker_idx - 1], overtake_out_.overtake_target_front_left);
            }
        }
    }

    if (elk_num_front_right < 1) {
        // front_right will be memset to 0
    } else {
        uint8_t elk_indx = FindMinIndex(elk_TrkDist_front_right, 1, elk_num_front_right);
        if ((elk_indx >= 1)  &&  (elk_indx <= elk_num_front_right)) {
            uint8_t traker_idx = elk_TrkId_front_right[elk_indx - 1];
            if ((traker_idx > 0)  &&  (traker_idx <= kMaxNormalObject)) {
                FillTargetInfo(obs_data_[traker_idx - 1], overtake_out_.overtake_target_front_right);
            }
        }
    }
}

// Following as_elk 100%: UpdateOncomTgtTrkProperties
void ElkTargetSelection::UpdateOncomTgtTrkProperties() {
    // Following as_elk: updateOncomTgtTrkProperties
    // This function updates the target properties after selection
    // In as_elk, this fills struct_oncom_target_trk_prop from selected targets (track_id)
    // We need to update all 3 targets (oncom_target_1, oncom_target_2, oncom_target_3)

    AsOnComingObject *targets[3] = {&oncom_out_.oncom_target_1, &oncom_out_.oncom_target_2, &oncom_out_.oncom_target_3};

    for (uint8_t i = 0; i < 3; ++i) {
        if ((targets[i]->track_id > 0)  &&  (targets[i]->track_id <= kMaxNormalObject)) {
            size_t obs_idx = targets[i]->track_id - 1;

            if ((obs_idx < kMaxNormalObject)  &&  obs_data_[obs_idx].obs) {
                const auto &obs = obs_data_[obs_idx].obs;

                // Update all properties (following as_elk 100%)
                targets[i]->vcs_long_posn = obs->long_posn;
                targets[i]->vcs_long_vel = obs->long_vel;
                targets[i]->vcs_long_accel = obs->long_accel;
                // Convert lateral coordinates from ISO (left+, right-) to as_elk (left-, right+)
                targets[i]->vcs_lat_posn = -obs->lat_posn;
                targets[i]->vcs_lat_vel = -obs->lat_vel;
                targets[i]->vcs_lat_accel = -obs->lat_accel;

                targets[i]->width = obs->width;
                targets[i]->length = obs->length;
                targets[i]->vcs_rm_dis = obs_data_[obs_idx].dist; // Following as_elk: use dist from lane assignment
                targets[i]->curv_heading = obs->heading;

                targets[i]->object_class = static_cast<uint8_t>(obs->object_class);
                targets[i]->fusion_source = static_cast<uint8_t>(obs->fusion_source);
                targets[i]->track_status = static_cast<uint8_t>(obs->status);

                targets[i]->cmbbPrimaryConfidence = 195; // Following as_elk
                targets[i]->FcwConfidence = 195;         // Following as_elk
                targets[i]->maturity = 3;                // Following as_elk
                targets[i]->visTrkID = (obs->vis_trkID > 0 && obs->vis_trkID < 256) ? static_cast<uint8_t>(obs->vis_trkID) : 0;

                // Movement calculation (following as_elk 100%)
                bool f_oncoming = (obs->long_vel < 0.01F);
                targets[i]->f_oncoming = f_oncoming ? 1 : 0;

                uint8_t movement = 0; // NA
                if (obs->long_vel > 0.1F) {
                    movement = 3; // TrackMoving
                }
                if (f_oncoming) {
                    if (obs->long_vel < -0.01F) {
                        movement = 4; // TrackOncoming
                    } else {
                        movement = 1; // TrackStationary
                    }
                }
                targets[i]->movement = movement;

                // Following as_elk: track_id, oncom_confidence, collision_prob are from oncom_target, not updated here
                // These fields are already set by FillTargetInfo in OncomSelect
                // We only update the properties from obs_data_ and obs
            }
        } else {
            // Following as_elk: set all fields to 0 or default values if track_id is invalid
            targets[i]->vcs_long_posn = 0.0F;
            targets[i]->vcs_long_vel = 0.0F;
            targets[i]->vcs_long_accel = 0.0F;
            targets[i]->vcs_lat_posn = 0.0F;
            targets[i]->vcs_lat_vel = 0.0F;
            targets[i]->vcs_lat_accel = 0.0F;
            targets[i]->width = 0.0F;
            targets[i]->length = 0.0F;
            targets[i]->vcs_rm_dis = 0.0F;
            targets[i]->curv_heading = 0.0F;
            targets[i]->object_class = static_cast<uint8_t>(ObjectClass::UNDETERMINED);
            targets[i]->fusion_source = static_cast<uint8_t>(FusionSource::SINGLE_TRACKLET);
            targets[i]->track_status = static_cast<uint8_t>(TrackStatus::INVALID);
            targets[i]->movement = 0; // NA
            targets[i]->cmbbPrimaryConfidence = static_cast<uint8_t>(Confidence::LOW);
            targets[i]->FcwConfidence = static_cast<uint8_t>(Confidence::LOW);
            targets[i]->maturity = 0; // INVALID
            targets[i]->visTrkID = 0;
            targets[i]->f_oncoming = 0;
            targets[i]->track_id = 0;
            targets[i]->oncom_confidence = 0;
            targets[i]->collision_prob = 0;
        }
    }
}

// Following as_elk 100%: UpdateOvertakeTgtTrkProperties
void ElkTargetSelection::UpdateOvertakeTgtTrkProperties() {
    // Following as_elk: updateOvertakeTgtTrkProperties
    // This function updates the target properties after selection
    // In as_elk, this fills struct_elk_target_trk_prop from selected targets (track_id)
    // We need to update all 5 targets (rear_left, rear_right, front_left, front_right, and one more)

    AsOverTakingObject *targets[4] = {&overtake_out_.overtake_target_rear_left, &overtake_out_.overtake_target_rear_right,
                                      &overtake_out_.overtake_target_front_left, &overtake_out_.overtake_target_front_right};

    for (uint8_t i = 0; i < 4; ++i) {
        if ((targets[i]->track_id > 0)  &&  (targets[i]->track_id <= kMaxNormalObject)) {
            size_t obs_idx = targets[i]->track_id - 1;

            if ((obs_idx < kMaxNormalObject)  &&  obs_data_[obs_idx].obs) {
                const auto &obs = obs_data_[obs_idx].obs;

                // Update all properties (following as_elk 100%)
                targets[i]->vcs_long_posn = obs->long_posn;
                targets[i]->vcs_long_vel = obs->long_vel;
                targets[i]->vcs_long_accel = obs->long_accel;
                // Convert lateral coordinates from ISO (left+, right-) to as_elk (left-, right+)
                targets[i]->vcs_lat_posn = -obs->lat_posn;
                targets[i]->vcs_lat_vel = -obs->lat_vel;
                targets[i]->vcs_lat_accel = -obs->lat_accel;

                targets[i]->width = obs->width;
                targets[i]->length = obs->length;
                targets[i]->vcs_heading = obs->heading;
                targets[i]->confidence = 0.0F; // Following as_elk: always 0.0F

                targets[i]->object_class = static_cast<uint8_t>(obs->object_class);
                targets[i]->fusion_source = static_cast<uint8_t>(obs->fusion_source);
                targets[i]->track_status = static_cast<uint8_t>(obs->status);

                targets[i]->visTrkID = (obs->vis_trkID > 0 && obs->vis_trkID < 256) ? static_cast<uint8_t>(obs->vis_trkID) : 0;
            }
        } else {
            // Following as_elk: set all fields to 0 or default values if track_id is invalid
            targets[i]->vcs_long_posn = 0.0F;
            targets[i]->vcs_long_vel = 0.0F;
            targets[i]->vcs_long_accel = 0.0F;
            targets[i]->vcs_lat_posn = 0.0F;
            targets[i]->vcs_lat_vel = 0.0F;
            targets[i]->vcs_lat_accel = 0.0F;
            targets[i]->width = 0.0F;
            targets[i]->length = 0.0F;
            targets[i]->vcs_heading = 0.0F;
            targets[i]->confidence = 0.0F;
            targets[i]->object_class = static_cast<uint8_t>(ObjectClass::UNDETERMINED);
            targets[i]->fusion_source = static_cast<uint8_t>(FusionSource::SINGLE_TRACKLET);
            targets[i]->track_status = static_cast<uint8_t>(TrackStatus::INVALID);
            targets[i]->visTrkID = 0;
            targets[i]->track_id = 0;
        }
    }
}

// Following as_elk: checkLaneMarkerValid
// Note: Input coordinate system is ISO (left positive, right negative)
// as_elk expects (left negative, right positive), so we need to negate the values
void ElkTargetSelection::CheckLaneMarkerValid(const LanesInfo &lane_info) {
    // Convert from ISO (left+, right-) to as_elk (left-, right+)
    float left_c0 = -lane_info.HostLeftLaneMarker.LinePolyC0;   // Negate left (ISO + -> as_elk -)
    float right_c0 = -lane_info.HostRightLaneMarker.LinePolyC0; // Negate right (ISO - -> as_elk +)

    oncom_persistents_.LM_properties.f_host_left = (lane_info.HostLeftLaneMarker.LineConf >= elk_cal_.k_lineconf_vld_thr) &&
        (lane_info.HostLeftLaneMarker.LineViewRangeEnd > elk_cal_.k_range_lm) && (left_c0 <= elk_cal_.k_offset_small) &&
        (left_c0 >= -elk_cal_.k_offset_big);

    oncom_persistents_.LM_properties.f_host_right = (lane_info.HostRightLaneMarker.LineConf >= elk_cal_.k_lineconf_vld_thr) &&
        (lane_info.HostRightLaneMarker.LineViewRangeEnd > elk_cal_.k_range_lm) && (right_c0 >= -elk_cal_.k_offset_small) &&
        (right_c0 <= elk_cal_.k_offset_big);

    // Also update overtake persistents
    overtake_persistents_.LM_properties.f_host_left = oncom_persistents_.LM_properties.f_host_left;
    overtake_persistents_.LM_properties.f_host_right = oncom_persistents_.LM_properties.f_host_right;
}

// Following as_elk: updateHostDepartureDirection
// Note: Input coordinate system is ISO (left positive, right negative)
// as_elk expects (left negative, right positive), so we need to negate the values
void ElkTargetSelection::UpdateHostDepartureDirection(const LanesInfo &lane_info) {
    ElkLane host_leaning_direction = ElkLane::CENTER;
    float host_lane_width = elk_cal_.k_default_lane_width;
    float tmp;

    // Convert from ISO (left+, right-) to as_elk (left-, right+)
    float left_c0 = -lane_info.HostLeftLaneMarker.LinePolyC0;   // Negate left (ISO + -> as_elk -)
    float right_c0 = -lane_info.HostRightLaneMarker.LinePolyC0; // Negate right (ISO - -> as_elk +)

    if ((!oncom_persistents_.LM_properties.f_host_left) && (!oncom_persistents_.LM_properties.f_host_right)) {
        host_leaning_direction = ElkLane::CENTER;
        host_lane_width = elk_cal_.k_default_lane_width;
    } else if (oncom_persistents_.LM_properties.f_host_left && oncom_persistents_.LM_properties.f_host_right) {
        host_lane_width = right_c0 - left_c0; // Use converted values
        tmp = elk_cal_.k_lm_pad_two * host_lane_width;

        if (std::abs(right_c0) - std::abs(left_c0) > tmp) {
            host_leaning_direction = ElkLane::LEFT;
        } else if (std::abs(left_c0) - std::abs(right_c0) > tmp) {
            host_leaning_direction = ElkLane::RIGHT;
        } else {
            host_leaning_direction = ElkLane::CENTER;
        }
    } else if (oncom_persistents_.LM_properties.f_host_right) {
        host_lane_width = elk_cal_.k_default_lane_width;
        if (std::abs(right_c0) < elk_cal_.k_lm_pad_one * host_lane_width) {
            host_leaning_direction = ElkLane::RIGHT;
        } else {
            host_leaning_direction = ElkLane::CENTER;
        }
    } else {
        if (oncom_persistents_.LM_properties.f_host_left) {
            host_lane_width = elk_cal_.k_default_lane_width;
            if (std::abs(left_c0) < elk_cal_.k_lm_pad_one * host_lane_width) {
                host_leaning_direction = ElkLane::LEFT;
            } else {
                host_leaning_direction = ElkLane::CENTER;
            }
        }
    }

    oncom_persistents_.LM_properties.host_leaning_direction = host_leaning_direction;
    oncom_persistents_.LM_properties.host_lane_width = host_lane_width;
    overtake_persistents_.LM_properties.host_leaning_direction = host_leaning_direction;
    overtake_persistents_.LM_properties.host_lane_width = host_lane_width;
}

// Following as_elk: checkObjectBeyondBarrier (100% complete)
// Note: Input coordinate system is ISO (left positive, right negative)
// as_elk expects (left negative, right positive), so we need to negate both road edge and object positions
void ElkTargetSelection::CheckObjectBeyondBarrier(size_t obs_idx, const LanesInfo &lane_info) {
    auto &obs_data = obs_data_[obs_idx];
    // Convert object position from ISO (left+, right-) to as_elk (left-, right+)
    float trk_vcs_lat_posn = -obs_data.obs->lat_posn;  // Negate to convert coordinate system
    float trk_vcs_long_posn = obs_data.obs->long_posn; // Longitudinal position doesn't change

    bool f_beyond_border = false;
    float offset_on_edge_left = -100.0F;
    float offset_on_edge_right = 100.0F;
    float x2 = trk_vcs_long_posn * trk_vcs_long_posn;

    // Convert from ISO (left+, right-) to as_elk (left-, right+)
    // Check condition: as_elk expects LeftRoadEdge.LinePolyC0 <= -k_offset_small (negative)
    // In ISO, LeftRoadEdge is positive, so we check -LinePolyC0 <= -k_offset_small, i.e., LinePolyC0 >= k_offset_small
    if ((lane_info.LeftRoadEdge.LineViewRangeEnd > trk_vcs_long_posn) && 
        (lane_info.LeftRoadEdge.LineViewRangeStart < elk_cal_.k_max_start_range_re) &&
        (lane_info.LeftRoadEdge.LineConf >= elk_cal_.k_lineconf_vld_thr) &&
        (lane_info.LeftRoadEdge.LinePolyC0 >= elk_cal_.k_offset_small)) { // ISO: left is positive, so >= k_offset_small
        // Negate all polynomial coefficients to convert coordinate system
        offset_on_edge_left = -lane_info.LeftRoadEdge.LinePolyC0 + (-lane_info.LeftRoadEdge.LinePolyC1) * trk_vcs_long_posn +
            (-lane_info.LeftRoadEdge.LinePolyC2) * x2 + (-lane_info.LeftRoadEdge.LinePolyC3) * x2 * trk_vcs_long_posn;
    }

    // Check condition: as_elk expects RightRoadEdge.LinePolyC0 >= k_offset_small (positive)
    // In ISO, RightRoadEdge is negative, so we check -LinePolyC0 >= k_offset_small, i.e., LinePolyC0 <= -k_offset_small
    if ((lane_info.RightRoadEdge.LineViewRangeEnd > trk_vcs_long_posn) && 
        (lane_info.RightRoadEdge.LineViewRangeStart < elk_cal_.k_max_start_range_re) &&
        (lane_info.RightRoadEdge.LineConf >= elk_cal_.k_lineconf_vld_thr) &&
        (lane_info.RightRoadEdge.LinePolyC0 <= -elk_cal_.k_offset_small)) { // ISO: right is negative, so <= -k_offset_small
        // Negate all polynomial coefficients to convert coordinate system
        offset_on_edge_right = -lane_info.RightRoadEdge.LinePolyC0 + (-lane_info.RightRoadEdge.LinePolyC1) * trk_vcs_long_posn +
            (-lane_info.RightRoadEdge.LinePolyC2) * x2 + (-lane_info.RightRoadEdge.LinePolyC3) * x2 * trk_vcs_long_posn;
    }

    if ((trk_vcs_lat_posn < offset_on_edge_left) || (trk_vcs_lat_posn > offset_on_edge_right)) {
        f_beyond_border = true;
    }

    obs_data.f_beyond_border = f_beyond_border;
}

// Following as_elk: findMinIndex
uint8_t ElkTargetSelection::FindMinIndex(const std::array<float, 3> &array, uint8_t startIdx, uint8_t endIdx) {
    uint8_t min_indx = 1;
    float minVal = 3.402823466E+38F;
    // Fix: Limit endIdx to array size to prevent out-of-bounds access
    uint8_t max_end = (endIdx > static_cast<uint8_t>(array.size())) ? static_cast<uint8_t>(array.size()) : endIdx;
    for (uint8_t i = startIdx; i <= max_end; ++i) {
        if ((i >= 1)  &&  ((i - 1) < array.size())) {
            float tmp = array[i - 1];
            if (tmp < minVal) {
                minVal = tmp;
                min_indx = i;
            }
        }
    }
    return min_indx;
}

// Following as_elk: isMemberberOfArray
bool ElkTargetSelection::IsMemberOfArray(uint8_t val, const std::array<uint8_t, 3> &array) {
    for (uint8_t i = 0; i < 3; ++i) {
        if (val == array[i]) {
            return true;
        }
    }
    return false;
}

// Following as_elk: rankCandidate
void ElkTargetSelection::RankCandidate(std::array<uint8_t, 3> &candidate_pool_ID, std::array<float, 3> &candidate_pool_long_posn,
                                std::array<CollisionProbability, 3> &candidate_collision_prob_pool) {
    uint8_t num_candidate = 0;
    for (uint8_t k = 0; k < 3; ++k) {
        if (candidate_pool_ID[k] > 0)
            num_candidate++;
    }

    for (uint8_t i = 1; i <= num_candidate; ++i) {
        for (uint8_t j = i + 1; j <= num_candidate; ++j) {
            if ((candidate_collision_prob_pool[i - 1] < candidate_collision_prob_pool[j - 1]) ||
                ((candidate_collision_prob_pool[i - 1] == candidate_collision_prob_pool[j - 1]) &&
                 (candidate_pool_long_posn[i - 1] > candidate_pool_long_posn[j - 1]))) {
                // Swap
                uint8_t tmp_id = candidate_pool_ID[i - 1];
                candidate_pool_ID[i - 1] = candidate_pool_ID[j - 1];
                candidate_pool_ID[j - 1] = tmp_id;

                CollisionProbability tmp_prob = candidate_collision_prob_pool[i - 1];
                candidate_collision_prob_pool[i - 1] = candidate_collision_prob_pool[j - 1];
                candidate_collision_prob_pool[j - 1] = tmp_prob;

                float tmp_posn = candidate_pool_long_posn[i - 1];
                candidate_pool_long_posn[i - 1] = candidate_pool_long_posn[j - 1];
                candidate_pool_long_posn[j - 1] = tmp_posn;
            }
        }
    }
}

} // namespace elk
} // namespace active_safety
