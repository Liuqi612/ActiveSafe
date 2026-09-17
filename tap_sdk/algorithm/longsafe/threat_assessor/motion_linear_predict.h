#ifndef TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_LINEAR_PREDICT_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_LINEAR_PREDICT_H_

#include "motion_predict.h"

namespace active_safety {
namespace longsafe {

class MotionLinearPredict {
  public:
    MotionLinearPredict();
    ~MotionLinearPredict();

    static bool LinearPredictWithStop(float &pos, float &vel, float &acc, float time, bool check_stop = false);

    static void CalcDefaultMotion(const AsCurvaturePath &ego_path, const VehicleConfig &veh_config, LgSfObsData &obs_data);

    static void CalcBrakeMotion(const AsCurvaturePath &ego_path, const VehicleConfig &veh_config, LgSfObsData &obs_data, float predict_brake_decel);

    static void CalcLeftSteerMotion(const AsCurvaturePath &ego_path, const VehicleConfig &veh_config, LgSfObsData &obs_data,
                                    float predict_steer_accel);

    static void CalcRightSteerMotion(const AsCurvaturePath &ego_path, const VehicleConfig &veh_config, LgSfObsData &obs_data,
                                     float predict_steer_accel);
};
} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_LINEAR_PREDICT_H_
