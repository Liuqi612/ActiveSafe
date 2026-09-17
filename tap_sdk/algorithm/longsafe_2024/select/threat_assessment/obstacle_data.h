/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_THREAT_ASSESSMENT_OBSTACLE_DATA_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_THREAT_ASSESSMENT_OBSTACLE_DATA_H_
#include "algorithm/longsafe_2024/scenario_analysis/society_scene.h"
#include "coll_eval.h"
#include "inpath_decision.h"
#include "safemargin_evaluator.h"
namespace senseAD {
namespace tap {
struct AsObstacleData;
using AsObstacleDataList = std::array<AsObstacleData, active_safety::kMaxFusionObject>;
struct AsObstacleData {
    AsObstacleData();
    ~AsObstacleData() noexcept;

    void Clear();
    void ObjectPreProcess(const active_safety::AsObstacle &obj, const AsEgoPath &curv_path, const AsVseOut &vse_out,
                          const AsSocietyScene &society_scene);

    const CollisionEvaluator &GetCollisionEvalData() const;
    const SafetyMarginEvaluator &GetSafeMarginEvalData() const;
    const AsInPathDecision &GetInpathData() const;

  private:
    SafetyMarginEvaluator safe_margin;
    AsInPathDecision inpath_des;
    CollisionEvaluator coll_eva;
};
} // namespace tap
} // namespace senseAD
#endif // TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_THREAT_ASSESSMENT_OBSTACLE_DATA_H_
