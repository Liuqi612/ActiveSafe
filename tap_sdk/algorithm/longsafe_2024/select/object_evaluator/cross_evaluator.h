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

/*AsCrossEvaluator: Check for cross Objecet*/

namespace senseAD {
namespace tap {
class AsCrossEvaluator : public AsBaseEvaluator {
public:
  AsCrossEvaluator();
  ~AsCrossEvaluator();
  void ProcessScpEvaluator(const active_safety::AsObstacle &scp_obj,
                           const active_safety::AsObstacleList &obj_list, const AsVseOut &vse_out,
                           const AS_LaneMarkerInfo_T &lane);

private:
  void CheckIsScpScene(const active_safety::AsObstacle &scp_obj, const AsVseOut &vse_out);
  void CheckObjectCorrectDirection(const active_safety::AsObstacle &scp_obj,
                                   const AsVseOut &vse_out);
  void CheckObjectNearSideScpObj(const active_safety::AsObstacle &scp_obj,
                                 const active_safety::AsObstacleList &obj_list);
  void CheckObjBoundaryInOppsiteSide(const active_safety::AsObstacle &scp_obj,
                                     const AsVseOut &vse_out,
                                     const AS_LaneMarkerInfo_T &lane);
  void CheckHostTryToSteer(const AsVseOut &vse_out);
  void CheckObjSpdLeanToStraight(const active_safety::AsObstacle &scp_obj);
  bool scp_flag = false;
};
} // namespace tap
} // namespace senseAD
