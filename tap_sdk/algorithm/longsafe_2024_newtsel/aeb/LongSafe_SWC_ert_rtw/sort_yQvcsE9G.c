/*
 * File: sort_yQvcsE9G.c
 *
 * Code generated for Simulink model 'LongSafe_SWC'.
 *
 * Model version                  : 7.3237
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Thu Nov 20 16:40:24 2025
 */

#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "sort_yQvcsE9G.h"

/* Function for MATLAB Function: '<S1690>/FindClosestEdges' */
void sort_yQvcsE9G(real32_T x[4], int32_T idx[4])
{
  int32_T b_idx[4];
  int32_T idx4[4];
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T ib;
  int32_T nNaNs;
  real32_T b_x[4];
  real32_T x4[4];
  real32_T xwork[4];
  int8_T perm[4];
  b_idx[0] = 0;
  b_x[0] = x[0];
  x4[0] = 0.0F;
  idx4[0] = 0;
  xwork[0] = 0.0F;
  b_idx[1] = 0;
  b_x[1] = x[1];
  x4[1] = 0.0F;
  idx4[1] = 0;
  xwork[1] = 0.0F;
  b_idx[2] = 0;
  b_x[2] = x[2];
  x4[2] = 0.0F;
  idx4[2] = 0;
  xwork[2] = 0.0F;
  b_idx[3] = 0;
  b_x[3] = x[3];
  x4[3] = 0.0F;
  idx4[3] = 0;
  xwork[3] = 0.0F;
  nNaNs = -3;
  ib = 0;
  if (rtIsNaNF(x[0])) {
    b_idx[3] = 1;
    xwork[3] = x[0];
    nNaNs = -2;
  } else {
    ib = 1;
    idx4[0] = 1;
    x4[0] = x[0];
  }

  if (rtIsNaNF(x[1])) {
    b_idx[-nNaNs] = 2;
    xwork[-nNaNs] = x[1];
    nNaNs++;
  } else {
    ib++;
    idx4[ib - 1] = 2;
    x4[ib - 1] = x[1];
  }

  if (rtIsNaNF(x[2])) {
    b_idx[-nNaNs] = 3;
    xwork[-nNaNs] = x[2];
    nNaNs++;
  } else {
    ib++;
    idx4[ib - 1] = 3;
    x4[ib - 1] = x[2];
  }

  if (rtIsNaNF(x[3])) {
    b_idx[-nNaNs] = 4;
    xwork[-nNaNs] = x[3];
    nNaNs++;
  } else {
    ib++;
    idx4[ib - 1] = 4;
    x4[ib - 1] = x[3];
    if (ib == 4) {
      real32_T tmp;
      real32_T tmp_0;
      if (x4[0] <= x4[1]) {
        ib = 1;
        i2 = 2;
      } else {
        ib = 2;
        i2 = 1;
      }

      if (x4[2] <= x4[3]) {
        i3 = 3;
        i4 = 4;
      } else {
        i3 = 4;
        i4 = 3;
      }

      tmp = x4[ib - 1];
      tmp_0 = x4[i3 - 1];
      if (tmp <= tmp_0) {
        tmp = x4[i2 - 1];
        if (tmp <= tmp_0) {
          perm[0] = (int8_T)ib;
          perm[1] = (int8_T)i2;
          perm[2] = (int8_T)i3;
          perm[3] = (int8_T)i4;
        } else if (tmp <= x4[i4 - 1]) {
          perm[0] = (int8_T)ib;
          perm[1] = (int8_T)i3;
          perm[2] = (int8_T)i2;
          perm[3] = (int8_T)i4;
        } else {
          perm[0] = (int8_T)ib;
          perm[1] = (int8_T)i3;
          perm[2] = (int8_T)i4;
          perm[3] = (int8_T)i2;
        }
      } else {
        tmp_0 = x4[i4 - 1];
        if (tmp <= tmp_0) {
          if (x4[i2 - 1] <= tmp_0) {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)ib;
            perm[2] = (int8_T)i2;
            perm[3] = (int8_T)i4;
          } else {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)ib;
            perm[2] = (int8_T)i4;
            perm[3] = (int8_T)i2;
          }
        } else {
          perm[0] = (int8_T)i3;
          perm[1] = (int8_T)i4;
          perm[2] = (int8_T)ib;
          perm[3] = (int8_T)i2;
        }
      }

      b_idx[-(nNaNs + 3)] = idx4[perm[0] - 1];
      b_idx[-(nNaNs + 2)] = idx4[perm[1] - 1];
      b_idx[-(nNaNs + 1)] = idx4[perm[2] - 1];
      b_idx[-nNaNs] = idx4[perm[3] - 1];
      b_x[-(nNaNs + 3)] = x4[perm[0] - 1];
      b_x[-(nNaNs + 2)] = x4[perm[1] - 1];
      b_x[-(nNaNs + 1)] = x4[perm[2] - 1];
      b_x[-nNaNs] = x4[perm[3] - 1];
      ib = 0;
    }
  }

  if (ib > 0) {
    perm[1] = 0;
    perm[2] = 0;
    perm[3] = 0;
    switch (ib) {
     case 1:
      perm[0] = 1;
      break;

     case 2:
      if (x4[0] <= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
      break;

     default:
      if (x4[0] <= x4[1]) {
        if (x4[1] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }
      break;
    }

    for (i2 = 0; i2 < ib; i2++) {
      i3 = perm[i2] - 1;
      i4 = ((-nNaNs - ib) + i2) + 1;
      b_idx[i4] = idx4[i3];
      b_x[i4] = x4[i3];
    }
  }

  ib = ((nNaNs + 3) >> 1) + 1;
  for (i2 = 1; i2 - 1 <= ib - 2; i2++) {
    i3 = i2 - nNaNs;
    i4 = b_idx[i3];
    b_idx[i3] = b_idx[4 - i2];
    b_idx[4 - i2] = i4;
    b_x[i3] = xwork[4 - i2];
    b_x[4 - i2] = xwork[i3];
  }

  if (((nNaNs + 3) & 1U) != 0U) {
    ib -= nNaNs;
    b_x[ib] = xwork[ib];
  }

  idx[0] = b_idx[0];
  idx[1] = b_idx[1];
  idx[2] = b_idx[2];
  idx[3] = b_idx[3];
  x[0] = b_x[0];
  x[1] = b_x[1];
  x[2] = b_x[2];
  x[3] = b_x[3];
  if (1 - nNaNs > 1) {
    idx[0] = b_idx[0];
    idx[1] = b_idx[1];
    idx[2] = b_idx[2];
    idx[3] = b_idx[3];
    x[0] = b_x[0];
    x[1] = b_x[1];
    x[2] = b_x[2];
    x[3] = b_x[3];
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
