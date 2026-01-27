/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include "algorithm/longsafe_2024/algo_interface/active_safety_vse.h"
#include "algorithm/longsafe_2024/algo_interface/as_fusion_object.h"
#include "algorithm/longsafe_2024/algo_interface/as_lane_marker.h"
#include "algorithm/obstacle/obstacle.h"
#include "evaluator_base.h"
#include "obj_eval_types.h"

/*AsCtapEvaluator: Check for tap Objecet*/

namespace senseAD {
namespace tap {
class AsCtapEvaluator : public AsBaseEvaluator {
public:
  AsCtapEvaluator();
  ~AsCtapEvaluator();
  void ProcessScpEvaluator(const active_safety::AsObstacle &scp_obj,
                           const active_safety::AsObstacleList &obj_list, const AsVseOut &vse_out,
                           const AS_LaneMarkerInfo_T &lane, bool isHostInCurve);

private:
  void CheckIsCtapScene(bool isHostInCurve);
  // void CheckNudge();
  bool ctap_flag = false;
};
} // namespace tap
} // namespace senseAD
