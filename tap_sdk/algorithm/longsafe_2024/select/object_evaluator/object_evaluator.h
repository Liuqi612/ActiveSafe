/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include "algorithm/longsafe_2024/algo_interface/active_safety_vse.h"
#include "algorithm/longsafe_2024/select/threat_assessment/long_safe_if.h"
#include "algorithm/obstacle/obstacle.h"
#include "cip_evaluator.h"
#include "cross_evaluator.h"
namespace senseAD {
namespace tap {

class AsScenarioDisc {
  public:
    AsScenarioDisc();
    ~AsScenarioDisc() noexcept;
    uint32_t GetAsScenarioDisc() const;
    void     ProcessAsScenarioDisc(const active_safety::AsObstacle &prm_tgt, const active_safety::AsObstacleList &obj_list, const AsVseOut &vse_out,
                                   const AS_LaneMarkerInfo_T &lane);

  private:
    // Evaluator Set
    AsCipEvaluator   cip;
    AsCrossEvaluator scp;
    uint32_t         scenario_define = 0;
};
} // namespace tap
} // namespace senseAD
