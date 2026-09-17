/*
 * File: interp1_bctxPKq7.c
 *
 * Code generated for Simulink model 'LongSafe_SWC'.
 *
 * Model version                  : 7.3237
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Thu Nov 20 16:40:24 2025
 */

#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include <string.h>
#include "interp1_bctxPKq7.h"

/* Function for MATLAB Function: '<S1690>/FindClosestEdges' */
real32_T interp1_bctxPKq7(const real32_T varargin_1[60], const real32_T
  varargin_2[60], real32_T varargin_3)
{
  int32_T high_i;
  real32_T x[60];
  real32_T y[60];
  real32_T Vq;
  memcpy(&y[0], &varargin_2[0], 60U * sizeof(real32_T));
  memcpy(&x[0], &varargin_1[0], 60U * sizeof(real32_T));
  Vq = (rtNaNF);
  high_i = 0;
  int32_T exitg1;
  do {
    exitg1 = 0;
    if (high_i < 60) {
      if (rtIsNaNF(varargin_1[high_i])) {
        exitg1 = 1;
      } else {
        high_i++;
      }
    } else {
      real32_T xtmp;
      if (varargin_1[1] < varargin_1[0]) {
        for (high_i = 0; high_i < 30; high_i++) {
          xtmp = x[high_i];
          x[high_i] = x[59 - high_i];
          x[59 - high_i] = xtmp;
          xtmp = y[high_i];
          y[high_i] = y[59 - high_i];
          y[59 - high_i] = xtmp;
        }
      }

      if ((!rtIsNaNF(varargin_3)) && (!(varargin_3 > x[59])) && (!(varargin_3 <
            x[0]))) {
        int32_T low_i;
        int32_T low_ip1;
        high_i = 60;
        low_i = 1;
        low_ip1 = 2;
        while (high_i > low_ip1) {
          int32_T mid_i;
          mid_i = (low_i + high_i) >> 1;
          if (varargin_3 >= x[mid_i - 1]) {
            low_i = mid_i;
            low_ip1 = mid_i + 1;
          } else {
            high_i = mid_i;
          }
        }

        xtmp = x[low_i - 1];
        xtmp = (varargin_3 - xtmp) / (x[low_i] - xtmp);
        if (xtmp == 0.0F) {
          Vq = y[low_i - 1];
        } else if (xtmp == 1.0F) {
          Vq = y[low_i];
        } else {
          Vq = y[low_i - 1];
          if (!(Vq == y[low_i])) {
            Vq = (1.0F - xtmp) * Vq + xtmp * y[low_i];
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Vq;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
