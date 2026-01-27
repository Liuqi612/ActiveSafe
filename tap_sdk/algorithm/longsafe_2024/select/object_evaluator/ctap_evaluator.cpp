#include "ctap_evaluator.h"
#include <cmath>
namespace senseAD {
namespace tap {
AsCtapEvaluator::AsCtapEvaluator() {}
AsCtapEvaluator::~AsCtapEvaluator() {}

void AsCtapEvaluator::ProcessScpEvaluator(const active_safety::AsObstacle &scp_obj,
                                          const active_safety::AsObstacleList &obj_list,
                                          const AsVseOut &vse_out,
                                          const AS_LaneMarkerInfo_T &lane,
                                          bool isHostInCurve) {
  (void)(scp_obj);
  (void)(obj_list);
  (void)(vse_out);
  (void)(lane);
  CheckIsCtapScene(isHostInCurve);
}

void AsCtapEvaluator::CheckIsCtapScene(bool isHostInCurve) {
  if (!isHostInCurve) {
    ctap_flag = false;
  } else {
    ctap_flag = true;
  }
}

} // namespace tap
} // namespace senseAD
