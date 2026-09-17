#ifndef TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_STATIC_PREDICT_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_STATIC_PREDICT_H_
#include "motion_predict.h"

namespace active_safety {
namespace longsafe {

class MotionStaticPredict {
  public:
    MotionStaticPredict();
    ~MotionStaticPredict();

    static void CalcStaticObjMotion(const AsCurvaturePath &ego_path, const VehicleConfig &veh_config, const LgSfObsData &obs_data,
                                    MotionPredictInfo &pred_info);
};
} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_STATIC_PREDICT_H_
