#ifndef TAP_SDK_ALGORITHM_ELK_ELK_TARGET_SELECTION_H_
#define TAP_SDK_ALGORITHM_ELK_ELK_TARGET_SELECTION_H_
#include "common/global_config.h"
#include "elk_cals.h"
#include "elk_obs.h"
#include "interface/active_safety_coreout.h"
#include "interface/active_safety_vse.h"
#include "interface/lane_marker.h"

#include <array>
#include <vector>

namespace active_safety {
namespace elk {

class ElkTargetSelection {
  public:
    ElkTargetSelection();
    ~ElkTargetSelection() = default;

    void Update(const AsVseOut &vse_out, const LanesInfo &road_info, const GlobalConfig &config, const AsObstacleList &obs_list);

    const AsOnComingOut &GetOncomingOutput() const { return oncom_out_; }
    const AsOverTakingOut &GetOvertakingOutput() const { return overtake_out_; }

    const std::array<ElkObsData, kMaxNormalObject> getElkObjectDatas() const {return obs_data_; }

  private:
    void Init();

    // Core selection logic
    void ProcessLaneMarkers(const LanesInfo &lane_info);
    void ProcessObjects(const AsVseOut &vse_out, const LanesInfo &lane_info, const AsObstacleList &obs_list);
    void OncomTargetSelection(const AsVseOut &vse_out);
    void OvertakeTargetSelection(const AsVseOut &vse_out);

    // Helper functions for selection (following as_elk 100%)
    void CheckLaneMarkerValid(const LanesInfo &lane_info);
    void UpdateHostDepartureDirection(const LanesInfo &lane_info);
    void UpdateLaneAssignment(size_t obs_idx, const LanesInfo &lane_info, float rear_curvature);
    void CheckObjectBeyondBarrier(size_t obs_idx, const LanesInfo &lane_info);
    void CheckOncomValidZone(size_t obs_idx);
    void CheckOvertakeValidZone(size_t obs_idx);
    void UpdateTrkOncomConfidence(size_t obs_idx);
    void UpdateTrkOvertakeConfidence(size_t obs_idx);
    bool IsCurrentOncomingMotion(const AsObstacle &obs) const;
    void OncomTrkPropertiesUpdate(const LanesInfo &lane_info, float rear_curvature);
    void OvertakeTrkPropertiesUpdate(const LanesInfo &lane_info, float rear_curvature);
    void OncomThreatComputation(float host_speed);
    void OvertakeThreatComputation(float host_speed);

    // Candidate pool management (following as_elk 100%)
    void UpdateOncomCandidatePool();
    void UpdateOvertakeCandidatePool();
    void RankCandidate(std::array<uint8_t, 3> &candidate_pool_ID, std::array<float, 3> &candidate_pool_long_posn,
                       std::array<CollisionProbability, 3> &candidate_collision_prob_pool);
    bool IsMemberOfArray(uint8_t val, const std::array<uint8_t, 3> &array);
    uint8_t FindMinIndex(const std::array<float, 3> &array, uint8_t startIdx, uint8_t endIdx);

    // Target pool management (following as_elk 100%)
    uint8_t UpdateOncomTargetPool(const std::array<uint8_t, 3> &candidate_pool_ID, ElkLane laneEnum);
    uint8_t UpdateOvertakeTargetPool(const std::array<uint8_t, 3> &candidate_pool_ID, bool frontFlag, bool rearFlag, ElkLane laneEnum,
                                     std::array<uint8_t, 3> &id_pool);
    void ReArrangePool(const std::array<uint8_t, 3> &extra_id, uint8_t extra_id_valid_length, std::array<uint8_t, 3> &id_pool);
    void OncomDownSelection();
    void OvertakeDownSelection();
    void UpdateOvertakePool();

    // Selection (following as_elk 100%)
    void OncomSelect();
    void OvertakeSelect();

    // Target properties update (following as_elk 100%)
    void UpdateOncomTgtTrkProperties();
    void UpdateOvertakeTgtTrkProperties();

    // Output generation
    void FillOncomOutput();
    void FillOvertakeOutput();
    void FillTargetInfo(const ElkObsData &obs_data, AsOnComingObject &oncom_tgt);
    void FillTargetInfo(const ElkObsData &obs_data, AsOverTakingObject &overtake_tgt);

    ElkCal elk_cal_;
    ElkLaneProperties lane_props_;
    std::array<ElkObsData, kMaxNormalObject> obs_data_;

    AsOnComingOut oncom_out_;
    AsOverTakingOut overtake_out_;

    // Persistent state (following as_elk architecture)
    OncomPersistents oncom_persistents_;
    OvertakePersistents overtake_persistents_;

    // Roll counters (following as_elk)
    uint8_t oncom_rollcnt_ = 0;
    uint8_t overtake_rollcnt_ = 0;
};

} // namespace elk
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_ELK_ELK_TARGET_SELECTION_H_
