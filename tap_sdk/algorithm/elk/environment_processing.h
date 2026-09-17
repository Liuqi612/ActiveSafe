#ifndef TAP_SDK_ALGORITHM_ELK_ENVIRONMENT_PROCESSING_H_
#define TAP_SDK_ALGORITHM_ELK_ENVIRONMENT_PROCESSING_H_
#include "common/global_config.h"
#include "elk_cals.h"
#include "elk_obs.h"
#include "interface/active_safety_coreout.h"
#include "interface/active_safety_vse.h"
#include "interface/lane_marker.h"
#include "math/signalprocess/signal_hold_block/signal_hold_block.h"

#include <algorithm>
#include <array>
#include <vector>

namespace active_safety {
namespace elk {

    struct LaneBoundaryParameters {
        // left marker
        float lftC0Lst;
        float curLftDisToBdry;
        float futLftDisToBdry;
        float lftBdryHdgDeg;
        float lftBdryLatRt;
        float lftBdryCurv;
        float lftBdryCurvRt;
        float lftBdryTtlc;
        float lftLcTm;
        bool  lftBdryVld;
        bool  lftLaneChange;
        bool  lftBdryJump = false;
        bool  lftBdryRangeShort = false;

        // right marker
        float rgtC0Lst;
        float curRgtDisToBdry;
        float curRgtDisToBdry_last;
        float futRgtDisToBdry;
        float rgtBdryHdgDeg;
        float rgtBdryLatRt;
        float rgtBdryCurv;
        float rgtBdryCurvRt;
        float rgtBdryTtlc;
        float rgtLcTm;
        bool  rgtBdryVld;
        bool  rgtLaneChange;
        bool  rgtBdryJump = false;
        bool  rgtBdryRangeShort = false;

        // left edge
        float curLftDisToEdge;
        float futLftDisToEdge;
        float lftEdgeHdgDeg;
        float lftEdgeLatRt;
        float lftEdgeCurv;
        float lftEdgeCurvRt;
        float lftEdgeTtlc;
        bool  lftEdgeVld;
        bool  runOffRoadLft;
        bool  lftEdgeJump = false;
        bool  lftEdgeRangeShort = false;
        bool  lftEdgeLaneMismatch = false;

        // right edge
        float curRgtDisToEdge;
        float futRgtDisToEdge;
        float rgtEdgeHdgDeg;
        float rgtEdgeLatRt;
        float rgtEdgeCurv;
        float rgtEdgeCurvRt;
        float rgtEdgeTtlc;
        bool  rgtEdgeVld;
        bool  runOffRoadRgt;
        bool  rgtEdgeJump = false;
        bool  rgtEdgeRangeShort = false;
        bool  rgtEdgeLaneMismatch = false;

        float laneWidth;
        float frtAxlCurv;
    };

    struct LaneCenterParameters {
        float c0;
        float c1;
        float c2;
        float c3;
        float heading;
        float startRange;
        float endRange;
        bool  vld;
    };

    struct HistoryEnvironmentInfo {
        float lftC0 = 0.0f;
        float lftC1 = 0.0f;
        bool lftVld = false;
        float rgtC0 = 0.0f;
        float rgtC1 = 0.0f;
        bool rgtVld = false;
        float lftEdgeC0 = 0.0f;
        float lftEdgeC1 = 0.0f;
        bool lftEdgeVld = false;
        float rgtEdgeC0 = 0.0f;
        float rgtEdgeC1 = 0.0f;
        bool rgtEdgeVld = false;
    };

    class EnvironmentProcessing {
        public:
            EnvironmentProcessing();
            ~EnvironmentProcessing() = default;

            void Update(const AsVseOut &vse_out, const LanesInfo &road_info);
            const LaneBoundaryParameters getLaneBoundaryInfo() const { return lane_marker_boundary_parms_; };
            const LaneCenterParameters getLaneCenterInfo() const { return lane_center_parms_; };
        private:
            void Init();
            void getLaneMarkerBoundaryParameters(const AsVseOut &vse_out, const LanesInfo &road_info, const VehicleConfig &veh_config);
            void getRoadEdgeBoundaryParameters(const AsVseOut &vse_out, const LanesInfo &road_info, const VehicleConfig &veh_config);
            void updateBoundaryQualityStatus(const LanesInfo &road_info);
            void updateBoundaryHistory(const LanesInfo &road_info);
            void getLaneCenterParameters(const LanesInfo &road_info);
            void detectLaneChangeBoundary(const LanesInfo &road_info);
            bool isBoundaryJump(float c0, float c1, bool valid, float prev_c0, float prev_c1, bool prev_valid) const;
            float calcBoundaryY(float c0, float c1, float c2, float c3, float x) const;
            bool isLeftEdgeLaneMismatch(const LanesInfo &road_info) const;
            bool isRightEdgeLaneMismatch(const LanesInfo &road_info) const;

            LaneBoundaryParameters lane_marker_boundary_parms_;
            LaneCenterParameters lane_center_parms_;
            HistoryEnvironmentInfo his_env_info_;
            ElkCal elk_cal_;
            math::SignalHoldBlock left_lane_change_;
            math::SignalHoldBlock right_lane_change_;
            math::SignalHoldBlock left_run_off_road_;
            math::SignalHoldBlock right_run_off_road_;
            math::SignalHoldBlock left_boundary_jump_;
            math::SignalHoldBlock right_boundary_jump_;
            math::SignalHoldBlock left_edge_jump_;
            math::SignalHoldBlock right_edge_jump_;
    };
    } // namespace elk
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_ELK_ENVIRONMENT_PROCESSING_H_
