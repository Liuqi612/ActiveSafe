/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_OBJECT_EVALUATOR_OBJ_EVAL_TYPES_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_OBJECT_EVALUATOR_OBJ_EVAL_TYPES_H_

namespace senseAD {
namespace tap {

enum AsScenarioDiscInfo {
  AS_NORMAL_SCENARIO = (1 << 0),
  AS_CIP_LOW_OVERLAP = (1 << 1),
  AS_SCP_TURN_LONG_MOVING = (1 << 2),
  AS_SCP_BOUNDARY_IN_OPPOSITESIDE = (1 << 3),
  AS_SCP_OBJ_NEARSIDE = (1 << 4),
  AS_SCP_HOST_WILL_STEER = (1 << 5),
  AS_TAP_IN_NUDGE = (1 << 6),
  AS_CIP_OBJ_CLOSE_FITST_DETECT = (1 << 7),
  AS_SCP_SPD_LEAN_TO_STRAIGHT = (1 << 8)
};

//struct active_safety::AsObstacle;
//using active_safety::AsObstacleList = std::array<active_safety::AsObstacle, kMaxFusionObject>;

} // namespace tap
} // namespace senseAD
#endif // TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_OBJECT_EVALUATOR_OBJ_EVAL_TYPES_H_
