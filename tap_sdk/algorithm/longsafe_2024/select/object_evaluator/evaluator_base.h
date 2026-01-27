/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
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
