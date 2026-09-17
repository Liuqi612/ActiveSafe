#pragma once
#include <cmath>

namespace pnc_x {
namespace planning {

constexpr double kPredictionStep = 0.1;
constexpr int kDecisionVarValidCnt = 2;
constexpr double kConsideredTime = 6.0;
constexpr double kMinValidDist = 30.0;
constexpr double kMaxValidDist = 200.0;
constexpr double kLaneKeepMaxLateralError = 0.3;
constexpr double kSecondToMicrosecond = 1e3;
constexpr double kDefaultLatAvoidSignedDis = 0.9F;
constexpr double kSteerRatio = 16.0;
constexpr double kAngle2Rad = M_PI / 180.0;
constexpr double kEpsilon = 1e-6;
constexpr double kRoadWidth = 3.75F;
constexpr double kEgoSelfBuffer = 0.6F;
constexpr double kSec2Msec = 1000.0;
constexpr size_t kEgoCornersNum = 4;
constexpr double kLowSpeedThreshold = 2.0;
constexpr int kSearchBoundSize = 2;
constexpr double kJunctionThreshold = 20.0F;
constexpr double kGridMapCellSize = 0.3F;
constexpr double kGridBoundaryPointPerDistance = 0.04F;
constexpr int kXIndex = 0;
constexpr int kYIndex = 1;
constexpr int kBoundNum = 2;
constexpr int kMinInterpolatPointsNum = 2;
constexpr int kLeftBoundIndex = 0;
constexpr int kRightBoundIndex = 1;
constexpr double kOneHalfWidthRatio = 3.0F;
constexpr double kTwoHalfWidthRatio = 5.0F;
constexpr double kHalfWidthRatio = 1.0F;
constexpr double kBackObsSelectCarLengthRatio = 1.0F;
constexpr double kCircleTimeMsWithBuffer = 150.0F;
constexpr double kPlanningFallbackSetSlength = 10.0F;
constexpr double kMinmumSpeedForFallback = 0.5F;
constexpr int kPointNoContinuous = 2;
constexpr double kMillisecondToSecond = 0.001F;
constexpr double kSecondToMillisecond = 1000.0F;
constexpr double kMinAcc = -6.0;
constexpr double kMaxAcc = 4.0;
constexpr double kMinDis = 40.0;
constexpr double kMinSearchConsiderTime = 6.0;
constexpr double kMinMapConsiderTime = 10.0;
constexpr double kGoalL = 1.0;
constexpr float kMaxLaneBorrowWidth = 0.5;
constexpr float kSSampleDistance = 0.5;

}  // namespace planning
}  // namespace pnc_x