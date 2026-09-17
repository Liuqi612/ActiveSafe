#ifndef TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_CURVE_PREDICT_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_CURVE_PREDICT_H_
#include "motion_predict.h"

namespace active_safety {
namespace longsafe {

class MotionCurvePredict {
 public:
  MotionCurvePredict();
  ~MotionCurvePredict();


 private:
 MotionPredict CalcDefaultMotion(const AsObstacle& obs,float time);
//  MotionPredict CalcBrakeMotion();
//  MotionPredict CalcSteerMotion();

};
}  // namespace longsafe
}  // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_CURVE_PREDICT_H_
