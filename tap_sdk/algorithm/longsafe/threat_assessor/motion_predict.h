#ifndef TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_PREDICT_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_PREDICT_H_
#include "algorithm/longsafe/ego/curvature_path.h"
#include "algorithm/longsafe/longsafe_cals.h"
#include "algorithm/vse/vehicle_state_estimed.h"
#include "common/global_config.h"
#include "longsafe_obs.h"
#include "math/utils/util_math.h"
#include "motion_predict_types.h"

#include <vector>
#include <cstdint>

namespace active_safety {
namespace longsafe {

using math::Point2D;

class PredictRelativeInfo {
  public:
    PredictRelativeInfo() = default;
    ~PredictRelativeInfo() = default;

    static void CalcObjRelPosDist(const MotionStateAtTime &host_state, const VehicleConfig &ego_param, const MotionPredict &obj_predict,
                                  float obj_length, float obj_width, RelativePosPredict &rel_pos);

    static void CalcRelativeInfo(const MotionStateAtTime &host_state, const VehicleConfig &veh_config, const LgSfObsData &obs_data,
                                 bool aeb_active, ObsMotionInfo &motion_info, float predict_time = 0.0F);

    static int FindMinDistIndex(const std::array<RelativePosPredict, MAX_PREDICT_NUM> &rel_info);

    static bool CheckGeometryInpath(const MotionStateAtTime &host_state, const ObsMotionInfo &obs_motion, const VehicleConfig &veh_config,
                                    float obs_length, float obs_width, float host_lgt_offs = 0.0f, float host_lat_offs = 0.0f,
                                    float obs_lat_offs = 0.0f, uint8_t debug_mode = 0);

    static bool CheckGeometryInpath(const MotionStateAtTime &host_state, const ObsMotionInfo &obs_motion, const VehicleConfig &veh_config,
                                    float obs_length, float obs_width, float host_lgt_offs, float host_lat_offs,
                                    float obs_width_offs, uint8_t debug_mode, PredInpathFailReason &fail_reason,
                                    PredInpathDebug *debug = nullptr, float predict_time = 0.0F);

    static void SetRecordFusTrkID(int32_t fus_trkID);
    static void ClearRecordFusTrkID();

    static void CalculateTTRAndTTP(MotionPredictInfo &pred_info);
};

} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_MOTION_PREDICT_H_
