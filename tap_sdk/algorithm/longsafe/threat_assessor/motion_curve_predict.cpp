#include "motion_curve_predict.h"

namespace active_safety {
namespace longsafe {

MotionCurvePredict::MotionCurvePredict() {
}
MotionCurvePredict::~MotionCurvePredict() = default;

MotionPredict MotionCurvePredict::CalcDefaultMotion(const AsObstacle& obs, float time) {
    MotionPredict motion_predict;

    return motion_predict;
}

}  // namespace longsafe
}  // namespace active_safety
