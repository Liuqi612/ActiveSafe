/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */

#pragma once
#include "active_safety_control.h"
#include "active_safety_coreout.h"
#include "active_safety_vse.h"
#include <cstddef>
#include <cstdint>
namespace senseAD {
namespace tap {
struct AsDebug_T {
  AsVseOut vse;
  AsCoreOut_T core_out;
  AsControl_T ctrl;
};
} // namespace tap
} // namespace senseAD
