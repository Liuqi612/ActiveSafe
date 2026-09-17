#ifndef TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_BEHAVIOR_EVALUATOR_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_BEHAVIOR_EVALUATOR_H_
#include "longsafe_obs.h"
namespace active_safety {
namespace longsafe {

using math::LookUpTable;

class BehaviorEvaluator {
  public:
    BehaviorEvaluator();
    ~BehaviorEvaluator();
    static void ObjBehaviorEvaluator(const AsVseOut &vse_out, LgSfObsData &obs_data);
    static void UpdateObsManType(const AsVseOut &vse_out, LgSfObsData &obs_data);

  private:
    static void  CalcObjAvoidanceManoeuvers(LgSfObsData &obs_data); // calculate avoidance motion
    static float CalcDeclerationForAovidance(float speed, float accel, float default_value);
    static void  MotionBehaviorEvaluator(LgSfObsData &obs_data);
    // cut in evaluator.
    static void  DetectObsCutIn(const AsVseOut &vse_out, LgSfObsData &obs_data);
    static void  CalcInputMeasure(const AsVseOut &vse_out, LgSfObsData &obs_data);
    static void  CalcProbability(LgSfObsData &obs_data);
    static float CalcRoadModelLatOffs(float heading, float c0, float c1, float x);
    static float CalcRoadModelHeading(float heading, float c0, float c1, float x);

    // Manues Type Evaluator.
    static void EvalObsCrossLeanToStraightBySpd(const AsVseOut &vse_out, LgSfObsData &obs_data);

    static BehaviorEvaluatorCal behavior_cal_;
};

} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_BEHAVIOR_EVALUATOR_H_
