/*
 * File: minimum_0CGLafEO.c
 *
 * Code generated for Simulink model 'LongSafe_SWC'.
 *
 * Model version                  : 7.3237
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Thu Nov 20 16:40:24 2025
 */

#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "minimum_0CGLafEO.h"

/* Function for MATLAB Function: '<S1690>/FindClosestEdges' */
real32_T minimum_0CGLafEO(const real32_T x[60])
{
  int32_T idx;
  real32_T ex;
  if (!rtIsNaNF(x[0])) {
    idx = 1;
  } else {
    int32_T k;
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 61)) {
      if (!rtIsNaNF(x[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    ex = x[0];
  } else {
    ex = x[idx - 1];
    while (idx + 1 <= 60) {
      if (ex > x[idx]) {
        ex = x[idx];
      }

      idx++;
    }
  }

  return ex;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
