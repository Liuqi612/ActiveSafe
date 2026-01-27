/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#include "lookuptable.h"
namespace active_safety {
namespace math {

float LookUpTable::LinearInterpolation(float x, float x0, float y0, float x1,
                                       float y1) {
                                        
  return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
}

} // namespace math
} // namespace active_safety