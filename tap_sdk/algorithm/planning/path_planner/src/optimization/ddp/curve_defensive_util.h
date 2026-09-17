#pragma once

#include <cmath>
#include <vector>

#include "math/piecewise_linear_function.h"
#include "plan/discretized_path.h"

namespace pnc_x {
namespace planning {
namespace optimizer {

// 根据曲率半径(ROC)查表返回弯道外侧防御性避让的额外buffer补偿
// ROC越小(弯越急)，补偿越大：<=10m→0.4m, 10~40→0.35, 40~80→0.3,
// 80~150→0.2, 150~300→0.1, >300→0
inline double GetCurveDefensiveBuffer(double roc) {
    static const PiecewiseLinearFunction<double> kRocToBuffer(
        {10.0, 40.0, 80.0, 150.0, 300.0},
        {0.4, 0.35, 0.3, 0.25, 0.2});
    if (roc > 300.0) {
        return 0.0;
    }
    return kRocToBuffer(roc);
}

// 变道过程中，按自车横向速度查表返回对变道方向目标的额外buffer补偿。
// 横向速度越大，说明变道动作越明确，补偿越大。
inline double GetLaneChangeDefensiveBuffer(double lateral_speed) {
    static const PiecewiseLinearFunction<double> kLatVelToBuffer(
        {0.3, 0.4, 0.5, 0.9, 1.0},
        {0.0, 0.20, 0.40, 0.60, 0.80});
    return kLatVelToBuffer(std::abs(lateral_speed));
}

// ODD曲率条件判断：在前方look_ahead_dist范围内，是否存在连续10个采样点
// 的曲率大于0.00333（即曲率半径ROC < 300m），每1m采样一次
inline bool HasConsecutiveHighCurvatureAhead(
    const DiscretizedPath &ref_center_path,
    double ego_s,
    double look_ahead_dist) {
    constexpr double kSampleInterval = 1.0;
    constexpr int kRequiredConsecutiveCount = 10;
    constexpr double kMinCurvatureForCurve = 0.00333;
    int consecutive_count = 0;
    for (double s = ego_s; s <= ego_s + look_ahead_dist;
         s += kSampleInterval) {
        if (s > ref_center_path.length()) {
            break;
        }
        const double kappa = ref_center_path.Evaluate(s).kappa();
        if (kappa > kMinCurvatureForCurve) {
            ++consecutive_count;
            if (consecutive_count >= kRequiredConsecutiveCount) {
                return true;
            }
        } else {
            consecutive_count = 0;
        }
    }
    return false;
}

constexpr double kCurveDefensiveMinSpeed = 10.0;

}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
