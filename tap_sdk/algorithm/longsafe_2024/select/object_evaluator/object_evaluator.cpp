/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#include "object_evaluator.h"

#include "obj_eval_param.h"

namespace senseAD {
namespace tap {
AsScenarioDisc::AsScenarioDisc() {
}
AsScenarioDisc::~AsScenarioDisc() {
}

uint32_t AsScenarioDisc::GetAsScenarioDisc() const {
    return scenario_define;
}

void AsScenarioDisc::ProcessAsScenarioDisc(const active_safety::AsObstacle &prm_tgt, const active_safety::AsObstacleList &obj_list,
                                           const AsVseOut &vse_out, const AS_LaneMarkerInfo_T &lane) {
    cip.ProcessCipEvaluator(prm_tgt, vse_out);
    scp.ProcessScpEvaluator(prm_tgt, obj_list, vse_out, lane);
    scenario_define = AsBaseEvaluator::Get();
}

} // namespace tap
} // namespace senseAD
