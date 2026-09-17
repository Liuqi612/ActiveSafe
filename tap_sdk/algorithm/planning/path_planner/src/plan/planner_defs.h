
#pragma once

#include "math/util.h"
#include <absl/time/time.h>

namespace pnc_x {
namespace planning {

#ifdef __X9HP__
constexpr int kTrajectorySteps = 80;
constexpr int kInitializerTrajectorySteps = 80;
constexpr int kInitializerCostEvalStep = 3;
constexpr double kPlanningTimeHorizon = 13.0;
#else
constexpr int kTrajectorySteps = 80;
constexpr int kInitializerTrajectorySteps = 80;
constexpr int kInitializerTrajectoryExtendSteps = 100;
constexpr int kMinCoarseTrajectorySize = 10;
constexpr int kInitializerCostEvalStep = 3;
constexpr double kPlanningTimeHorizon = 12.0;
#endif

constexpr absl::Duration kPlannerMainLoopInterval = absl::Milliseconds(100);

constexpr double kTrajectoryTimeStep = 0.1;
constexpr int kTrajectoryStepsMinus1 = kTrajectorySteps - 1;
constexpr double kTrajectoryTimeHorizon =
    static_cast<double>(kTrajectoryStepsMinus1) * kTrajectoryTimeStep;
constexpr double kMaxLatAccCheckTime = 3.0;

constexpr int kInitializerTrajectoryStepsMinus1 = kInitializerTrajectorySteps - 1;
constexpr double kInitializerTrajectoryTimeHorizon =
    static_cast<double>(kInitializerTrajectoryStepsMinus1) * kTrajectoryTimeStep;

// Production TAP is emergency-only; the independent DP reference keeps the
// upstream horizon while the A* production variant is bounded to three seconds.
#if TAP_PLANNING_EMERGENCY_ONLY
constexpr double kActiveInitializerTrajectoryTimeHorizon = 3.0;
#else
constexpr double kActiveInitializerTrajectoryTimeHorizon =
    kInitializerTrajectoryTimeHorizon;
#endif

constexpr int kAccTrajectorySteps = 80;
constexpr int kAccTrajectoryStepsMinus1 = kAccTrajectorySteps - 1;
constexpr double kAccTrajectoryTimeHorizon =
    static_cast<double>(kAccTrajectoryStepsMinus1) * kTrajectoryTimeStep;
constexpr double kSpacetimePlannerTrajectoryHorizon =
    kTrajectoryTimeStep * kTrajectorySteps;

constexpr double kSpacetimePlannerBehindCarTrajectoryHorizon = 1.0;
constexpr double kSpacetimePlannerVRUTrajectoryHorizon = 2.0;

constexpr double kSpacetimePlannerInCrossingTrajectoryHorizon = 3.0;

constexpr double kPathSampleInterval = 0.2;
constexpr int kSpeedFinderMaxTrajectorySteps = 80;

constexpr int kMaxPastPointNum = 50;
constexpr int kMaxAccPastPointNum = 5;

constexpr double kSpaceTimeVisualizationDefaultTimeScale = 10.0;

constexpr double kMinLCSpeed = 5.0 / 3.6;
constexpr double kMinLcLaneLength = 20.0;

constexpr double kDefaultLaneWidth = 3.5;
constexpr double kDefaultHalfLaneWidth = 0.5 * kDefaultLaneWidth;
constexpr double kDefaultMaxLaneWidth = 3.75;
constexpr double kDefaultMaxHalfLaneWidth = 0.5 * kDefaultMaxLaneWidth;
constexpr double kMaxHalfLaneWidth = 2.7;
constexpr double kMinLaneWidth = 2.6;
constexpr double kMinHalfLaneWidth = kMinLaneWidth * 0.5;

constexpr double kMaxLateralOffset = 10.0;
constexpr double kMaxLaneKeepLateralOffset = 0.4;

constexpr double kRouteStationUnitStep = 2.0;

constexpr double kDrivePassageKeepBehindLength = 25.0;

constexpr double kLaneChangeCheckForwardLength = 180.0;
constexpr double kLaneChangeCheckBackwardLength = 100.0;

constexpr double kMaxTravelDistanceBetweenFrames = 200.0;

constexpr double kInitializerMinFollowDistance = 3.0;

constexpr double kPlannerLaneGraphLength = 200.0;

constexpr double kCurvatureLimitRange = 6.0;

constexpr double kUTurnCurbGain = 0.3;

constexpr double kCurbGain = 1.0;

constexpr double kNormalToVirtual = 20.0;
constexpr double kVirtualToNormal = 50.0;

constexpr double kShortSegmentLength = 10.0;
constexpr double kLongSegmentLength = 10.0;
constexpr double kMinInvolvedChangePointLength = 50.0;
constexpr double kMinInvolvedChangePointTime = 4.0;
constexpr double KRefPathDeviationGains = 0.2;
constexpr double KRefPathDeviationGainsWideLane = 1.0;
constexpr double KRefPathHeadingDeviationGains = 0.5;

const char SoftNameString[] = "Soft";
const char HardNameString[] = "Hard";

const std::string kNullLeadingObjectId = "null_leading_object_id";

constexpr double kAlternateRouteAllowRoundaboutDist = 2000.0;

const std::string kInvalidOnlineMapId = "";

constexpr int kAsyncCounterInitVal = -1;

constexpr int kMaxCenterNum = 20;
}  // namespace planning
}  // namespace pnc_x
