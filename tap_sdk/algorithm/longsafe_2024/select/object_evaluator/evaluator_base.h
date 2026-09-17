/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_OBJECT_EVALUATOR_EVALUATOR_BASE_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_OBJECT_EVALUATOR_EVALUATOR_BASE_H_
#include <stdint.h>
namespace senseAD {
namespace tap {
class AsBaseEvaluator {
public:
  AsBaseEvaluator();
  ~AsBaseEvaluator();
  static uint32_t Get();

protected:
  void Set(bool flag, uint32_t behv);
  static uint32_t behavior;
};
} // namespace tap
} // namespace senseAD
#endif // TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_OBJECT_EVALUATOR_EVALUATOR_BASE_H_
