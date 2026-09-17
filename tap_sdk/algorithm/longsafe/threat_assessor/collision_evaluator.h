#ifndef TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_COLLISION_EVALUATOR_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_COLLISION_EVALUATOR_H_
#include "algorithm/longsafe/ego/curvature_path.h"
#include "algorithm/longsafe/threat_assessor/motion_curve_predict.h"
#include "algorithm/longsafe/threat_assessor/motion_linear_predict.h"
#include "algorithm/longsafe/threat_assessor/motion_static_predict.h"
#include "algorithm/vse/vehicle_state_estimed.h"
#include "longsafe_obs.h"

#include <vector>

namespace active_safety {
namespace longsafe {

class CollisionEvaluator {
  public:
    CollisionEvaluator();
    ~CollisionEvaluator();
    static void ObjInPathEvaluator(const AsVseOut &vse_out, const AsCurvaturePath &ego_path, LgSfObsData &obs_data);

  private:
    static void DecideInPathCurrent(const AsVseOut &vse_out, LgSfObsData &obs_data);

    static void DecideInPathPredict(const AsVseOut &vse_out, const AsCurvaturePath &ego_path, LgSfObsData &obs_data);

    static void SelectInPathResult(LgSfObsData &obs_data, bool aeb_active_cmbb);

    static float CalcYawRtModelPredLatPos(float posx, float c0,LgSfObsData &obs_data,float speed);

    static bool CheckLowLatSpdObject(ObjectClass obj_class, float obj_lat_vel);
};
} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_COLLISION_EVALUATOR_H_
