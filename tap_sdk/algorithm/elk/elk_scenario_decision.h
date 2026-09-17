#ifndef TAP_SDK_ALGORITHM_ELK_ELK_SCENARIO_DECISION_H_
#define TAP_SDK_ALGORITHM_ELK_ELK_SCENARIO_DECISION_H_

#include "environment_processing.h"
#include "elk_threat_assessment.h"
#include "interface/active_safety_vse.h"
#include "math/lookuptable/lookuptable.h"
#include "math/signalprocess/on_delay_block/on_delay_block.h"
#include "math/signalprocess/off_delay_block/off_delay_block.h"
#include "math/signalprocess/relay_block/relay_block.h"
#include "math/signalprocess/relay_block/relay_off_delay_block.h"
#include "math/signalprocess/relay_block/relay_on_delay_block.h"
#include "math/signalprocess/relay_block/relay_on_off_delay_block.h"
#include "math/signalprocess/signal_hold_block/signal_hold_block.h"

#include <array>
#include <cstdint>

namespace active_safety {
namespace elk {

class ElkScenarioDecision {
  public:
    struct TtcDebugSignal {
        float ttlc = 0.0F;
        float distance = 0.0F;
        float threshold = 0.0F;
        float nominal_threshold = 0.0F;
        bool history_enabled = false;
        bool low_lat_rate_near = false;
        bool stable_departure = false;
    };

    struct TtcDebugSnapshot {
        TtcDebugSignal left_lct;
        TtcDebugSignal right_lct;
        TtcDebugSignal left_ror;
        TtcDebugSignal right_ror;
        TtcDebugSignal left_sld;
        TtcDebugSignal right_sld;
    };

    ElkScenarioDecision()
        : left_intervention_mask_(0),
          right_intervention_mask_(0),
          left_edge_intervention_mask_(0),
          right_edge_intervention_mask_(0),
          left_solid_intervention_mask_(0),
          right_solid_intervention_mask_(0),
          left_active_source_mask_(0),
          right_active_source_mask_(0),
          left_suppression_mask_(0),
          right_suppression_mask_(0) {}
    ~ElkScenarioDecision() = default;

    bool determineLeftIntervention(const LanesInfo &road_info, 
                                   const LaneBoundaryParameters &lane_boundary, 
                                   const ElkTaSl &ta_info, 
                                   const GlobalConfig &config, 
                                   float vehSpd, 
                                   bool lftMkrVld, 
                                   bool lftEdgVld);
    bool determineLeftInterventionForSuppressedExit(const LanesInfo &road_info,
                                                    const LaneBoundaryParameters &lane_boundary,
                                                    const ElkTaSl &ta_info,
                                                    const GlobalConfig &config,
                                                    float vehSpd,
                                                    bool lftMkrVld,
                                                    bool lftEdgVld);
    bool determineRightIntervention(const LanesInfo &road_info, 
                                    const LaneBoundaryParameters &lane_boundary, 
                                    const ElkTaSl &ta_info, 
                                    const GlobalConfig &config,
                                    float vehSpd, 
                                    bool rgtMkrVld, 
                                    bool rgtEdgVld);
    bool determineRightInterventionForSuppressedExit(const LanesInfo &road_info,
                                                     const LaneBoundaryParameters &lane_boundary,
                                                     const ElkTaSl &ta_info,
                                                     const GlobalConfig &config,
                                                     float vehSpd,
                                                     bool rgtMkrVld,
                                                     bool rgtEdgVld);
    bool determineLeftSuppression(uint32_t suppression_mask);
    bool determineRightSuppression(uint32_t suppression_mask);
    bool checkLeftAligned(const LanesInfo &road_info, const LaneBoundaryParameters &lane_boundary, const LaneCenterParameters &lane_center, const GlobalConfig &config);
    bool checkRightAligned(const LanesInfo &road_info, const LaneBoundaryParameters &lane_boundary, const LaneCenterParameters &lane_center, const GlobalConfig &config);

    uint8_t getLeftInterventionMask() const { return left_intervention_mask_; }
    uint8_t getRightInterventionMask() const { return right_intervention_mask_; }
    uint8_t getLeftEdgeInterventionMask() const { return left_edge_intervention_mask_; }
    uint8_t getRightEdgeInterventionMask() const { return right_edge_intervention_mask_; }
    uint8_t getLeftSolidInterventionMask() const { return left_solid_intervention_mask_; }
    uint8_t getRightSolidInterventionMask() const { return right_solid_intervention_mask_; }
    uint8_t getLeftActiveSourceMask() const { return left_active_source_mask_; }
    uint8_t getRightActiveSourceMask() const { return right_active_source_mask_; }
    uint32_t getLeftSuppressionMask() const { return left_suppression_mask_; }
    uint32_t getRightSuppressionMask() const { return right_suppression_mask_; }
    uint64_t getTtcFalseTriggerDebugMask() const { return ttc_false_trigger_debug_mask_; }
    const TtcDebugSnapshot &getTtcDebugSnapshot() const { return ttc_debug_snapshot_; }

    float getLeftCurvOffsetMarker() const { return k_left_curv_dist_offset_marker_; }
    float getRightCurvOffsetMarker() const { return k_right_curv_dist_offset_marker_; }
    float getLeftCurvOffsetEdge() const { return k_left_curv_dist_offset_edge_; }
    float getRightCurvOffsetEdge() const { return k_right_curv_dist_offset_edge_; }

    bool isLeftEdgeRangeValid() const { return (left_edge_intervention_mask_ & 0x10) != 0; }
    bool isRightEdgeRangeValid() const { return (right_edge_intervention_mask_ & 0x10) != 0; }

    void resetLeftActiveSource() { left_active_source_mask_ = 0x0; }
    void resetRightActiveSource() { right_active_source_mask_ = 0x0; }
    void resetTtcFalseTriggerDebugMask()
    {
        ttc_false_trigger_debug_mask_ = 0ULL;
        ttc_debug_snapshot_ = TtcDebugSnapshot();
    }

  private:

    enum class TtcCheckMode : uint8_t {
        Activation,
        SuppressedExit
    };

    struct TtcHistory {
        std::array<float, 3> ttc = {{0.0F, 0.0F, 0.0F}};
        uint8_t valid_frame_count = 0U;
        uint8_t invalid_ttc_count = 0U;
    };
  
    ElkCal elk_cals_;

    float calcSpeedBasedTtcThreshold(float vehSpd, float lowSpdTtc, float nominalTtc) const;
    bool checkTtcDeparture(TtcHistory &history,
                           float ttlc,
                           float threshold,
                           bool historyEnabled,
                           TtcCheckMode mode);
    bool checkStableTtcDeparture(TtcHistory &history, float ttlc, float threshold, bool historyEnabled);
    void resetTtcHistory(TtcHistory &history);
    void updateTtcFalseTriggerDebugMask(const TtcHistory &history,
                                        float ttlc,
                                        float threshold,
                                        float nominalThreshold,
                                        bool historyEnabled,
                                        bool lowLatRtNear,
                                        bool stableTtcDeparture,
                                        uint8_t historyBit,
                                        uint8_t lowSpeedBit,
                                        uint8_t invalidBit);
    void updateTtcDebugSignal(TtcDebugSignal &signal,
                              float ttlc,
                              float distance,
                              float threshold,
                              float nominalThreshold,
                              bool historyEnabled,
                              bool lowLatRtNear,
                              bool stableTtcDeparture);

    // object
    bool determineLeftInterventionWithTtcMode(const LanesInfo &road_info,
                                             const LaneBoundaryParameters &lane_boundary,
                                             const ElkTaSl &ta_info,
                                             const GlobalConfig &config,
                                             float vehSpd,
                                             bool lftMkrVld,
                                             bool lftEdgVld,
                                             TtcCheckMode ttcMode);
    bool determineRightInterventionWithTtcMode(const LanesInfo &road_info,
                                              const LaneBoundaryParameters &lane_boundary,
                                              const ElkTaSl &ta_info,
                                              const GlobalConfig &config,
                                              float vehSpd,
                                              bool rgtMkrVld,
                                              bool rgtEdgVld,
                                              TtcCheckMode ttcMode);

    bool checkLeftTtlcValid(const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode);
    bool checkLeftDistStable(float dist) const;
    bool determineLeftObstacleIntervention(const LaneBoundaryParameters &lane_boundary, 
                                           const ElkTaSl &ta_info, 
                                           const GlobalConfig &config,
                                           bool lftMkrVld,
                                           float vehSpd,
                                           TtcCheckMode ttcMode);
    bool checkRightTtlcValid(const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode);
    bool checkRightDistStable(float dist) const;
    bool determineRightObstacleIntervention(const LaneBoundaryParameters &lane_boundary, 
                                            const ElkTaSl &ta_info, 
                                            const GlobalConfig &config,
                                            bool rgtMkrVld,
                                            float vehSpd,
                                            TtcCheckMode ttcMode);

    // road edge
    bool checkEdgeRangeValid(float startRange, float endRange, float vehSpd) const;
    bool checkLeftEdgeTtlcValid(const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode);
    bool checkLeftEdgeDistStable(float dist) const;
    bool determineLeftEdgeIntervention(const LaneBoundaryParameters &lane_boundary, 
                                       const RoadEdge_t &left_edge, 
                                       const GlobalConfig &config,
                                       float vehSpd, 
                                       bool lftEdgVld,
                                       TtcCheckMode ttcMode);
    bool checkRightEdgeTtlcValid(const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode);
    bool checkRightEdgeDistStable(float dist) const;
    bool determineRightEdgeIntervention(const LaneBoundaryParameters &lane_boundary, 
                                        const RoadEdge_t &right_edge, 
                                        const GlobalConfig &config,
                                        float vehSpd, 
                                        bool rgtEdgVld,
                                        TtcCheckMode ttcMode);

     // solid
    bool checkLeftSolidTtlcValid(const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode);
    bool checkLeftSolidDistStable(float dist) const;
    bool determineLeftSolidIntervention(const LaneBoundaryParameters &lane_boundary, 
                                        const LaneMarker_t &left_marker, 
                                        const GlobalConfig &config,
                                        float vehSpd, 
                                        bool lftMkrVld,
                                        TtcCheckMode ttcMode);
    bool checkRightSolidTtlcValid(const GlobalConfig &config, float dist, float ttlc, float vehSpd, bool historyEnabled, TtcCheckMode ttcMode);
    bool checkRightSolidDistStable(float dist) const;
    bool determineRightSolidIntervention(const LaneBoundaryParameters &lane_boundary, 
                                         const LaneMarker_t &right_marker, 
                                         const GlobalConfig &config,
                                         float vehSpd, 
                                         bool rgtMkrVld,
                                         TtcCheckMode ttcMode);

    float k_left_curv_dist_offset_marker_ = 0.0F;
    float k_right_curv_dist_offset_marker_ = 0.0F;
    float k_left_curv_dist_offset_edge_ = 0.0F;
    float k_right_curv_dist_offset_edge_ = 0.0F;

    math::OnDelayBlock left_aligned_checker_;
    math::OnDelayBlock right_aligned_checker_;
    TtcHistory left_lct_ttc_history_;
    TtcHistory right_lct_ttc_history_;
    TtcHistory left_edge_ttc_history_;
    TtcHistory right_edge_ttc_history_;
    TtcHistory left_solid_ttc_history_;
    TtcHistory right_solid_ttc_history_;
    TtcDebugSnapshot ttc_debug_snapshot_;
    uint8_t left_intervention_mask_;
    uint8_t right_intervention_mask_;
    uint8_t left_edge_intervention_mask_;
    uint8_t right_edge_intervention_mask_;
    uint8_t left_solid_intervention_mask_;
    uint8_t right_solid_intervention_mask_;
    uint8_t left_active_source_mask_;
    uint8_t right_active_source_mask_;
    uint32_t left_suppression_mask_;
    uint32_t right_suppression_mask_;
    uint64_t ttc_false_trigger_debug_mask_ = 0ULL;
};

} // namespace elk
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_ELK_ELK_SCENARIO_DECISION_H_
