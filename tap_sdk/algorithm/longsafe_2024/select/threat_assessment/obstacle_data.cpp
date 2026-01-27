#include "obstacle_data.h"

namespace senseAD {
namespace tap {

AsObstacleData::AsObstacleData() {
}

AsObstacleData::~AsObstacleData() {
}

void AsObstacleData::ObjectPreProcess(const active_safety::AsObstacle &obj, const AsEgoPath &curv_path, const AsVseOut &vse_out,
                                      const AsSocietyScene &society_scene) {
    coll_eva.ProcessCollisionEvaluator(obj, vse_out, curv_path, society_scene);
    safe_margin.ProcessSafetyMarginEvaluator(obj, coll_eva, curv_path, vse_out);
    inpath_des.ProcessInPathDecision(obj, coll_eva, safe_margin, vse_out, curv_path);
}
void AsObstacleData::Clear() {
    safe_margin.Clear();
    coll_eva.Clear();
    inpath_des.Clear();
}
const CollisionEvaluator &AsObstacleData::GetCollisionEvalData() const {
    return coll_eva;
}
const SafetyMarginEvaluator &AsObstacleData::GetSafeMarginEvalData() const {
    return safe_margin;
}
const AsInPathDecision &AsObstacleData::GetInpathData() const {
    return inpath_des;
}

} // namespace tap
} // namespace senseAD
