/*
 * File: sort_ovJyqU1u.c
 *
 * Code generated for Simulink model 'AES_ESA_SWC'.
 *
 * Model version                  : 7.1293
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue Apr 28 17:15:49 2026
 */

#include "rtwtypes.h"
#include <string.h>
#include "merge_58LgYLQi.h"
#include "rt_nonfinite.h"
#include "sort_ovJyqU1u.h"

/* Function for MATLAB Function: '<S955>/MATLAB Function' */
void sort_ovJyqU1u(real32_T x[96], int32_T idx[96])
{
  int32_T iwork[96];
  int32_T i1;
  int32_T i2;
  int32_T ib;
  int32_T m;
  int32_T nNaNs;
  real32_T xwork[96];
  real32_T x4[4];
  int8_T idx4[4];
  int8_T perm[4];
  x4[0] = 0.0F;
  idx4[0] = 0;
  x4[1] = 0.0F;
  idx4[1] = 0;
  x4[2] = 0.0F;
  idx4[2] = 0;
  x4[3] = 0.0F;
  idx4[3] = 0;
  memset(&idx[0], 0, 96U * sizeof(int32_T));
  memset(&xwork[0], 0, 96U * sizeof(real32_T));
  nNaNs = -95;
  ib = 0;
  for (m = 0; m < 96; m++) {
    if (rtIsNaNF(x[m])) {
      idx[-nNaNs] = m + 1;
      xwork[-nNaNs] = x[m];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = (int8_T)(m + 1);
      x4[ib - 1] = x[m];
      if (ib == 4) {
        int32_T i3;
        int32_T i4;
        real32_T tmp;
        real32_T tmp_0;
        ib = (m - nNaNs) - 98;
        if (x4[0] <= x4[1]) {
          i1 = 1;
          i2 = 2;
        } else {
          i1 = 2;
          i2 = 1;
        }

        if (x4[2] <= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }

        tmp = x4[i1 - 1];
        tmp_0 = x4[i3 - 1];
        if (tmp <= tmp_0) {
          tmp = x4[i2 - 1];
          if (tmp <= tmp_0) {
            perm[0] = (int8_T)i1;
            perm[1] = (int8_T)i2;
            perm[2] = (int8_T)i3;
            perm[3] = (int8_T)i4;
          } else if (tmp <= x4[i4 - 1]) {
            perm[0] = (int8_T)i1;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)i2;
            perm[3] = (int8_T)i4;
          } else {
            perm[0] = (int8_T)i1;
            perm[1] = (int8_T)i3;
            perm[2] = (int8_T)i4;
            perm[3] = (int8_T)i2;
          }
        } else {
          tmp_0 = x4[i4 - 1];
          if (tmp <= tmp_0) {
            if (x4[i2 - 1] <= tmp_0) {
              perm[0] = (int8_T)i3;
              perm[1] = (int8_T)i1;
              perm[2] = (int8_T)i2;
              perm[3] = (int8_T)i4;
            } else {
              perm[0] = (int8_T)i3;
              perm[1] = (int8_T)i1;
              perm[2] = (int8_T)i4;
              perm[3] = (int8_T)i2;
            }
          } else {
            perm[0] = (int8_T)i3;
            perm[1] = (int8_T)i4;
            perm[2] = (int8_T)i1;
            perm[3] = (int8_T)i2;
          }
        }

        idx[ib] = idx4[perm[0] - 1];
        idx[ib + 1] = idx4[perm[1] - 1];
        idx[ib + 2] = idx4[perm[2] - 1];
        idx[ib + 3] = idx4[perm[3] - 1];
        x[ib] = x4[perm[0] - 1];
        x[ib + 1] = x4[perm[1] - 1];
        x[ib + 2] = x4[perm[2] - 1];
        x[ib + 3] = x4[perm[3] - 1];
        ib = 0;
      }
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

    for (m = 0; m < ib; m++) {
      i1 = perm[m] - 1;
      i2 = ((-nNaNs - ib) + m) + 1;
      idx[i2] = idx4[i1];
      x[i2] = x4[i1];
    }
  }

  m = ((nNaNs + 95) >> 1) + 1;
  for (ib = 1; ib - 1 <= m - 2; ib++) {
    i1 = ib - nNaNs;
    i2 = idx[i1];
    idx[i1] = idx[96 - ib];
    idx[96 - ib] = i2;
    x[i1] = xwork[96 - ib];
    x[96 - ib] = xwork[i1];
  }

  if (((nNaNs + 95) & 1U) != 0U) {
    m -= nNaNs;
    x[m] = xwork[m];
  }

  if (1 - nNaNs > 1) {
    memset(&iwork[0], 0, 96U * sizeof(int32_T));
    ib = (1 - nNaNs) >> 2;
    m = 4;
    while (ib > 1) {
      if ((ib & 1U) != 0U) {
        ib--;
        i1 = m * ib;
        i2 = 1 - (nNaNs + i1);
        if (i2 > m) {
          merge_58LgYLQi(idx, x, i1, m, i2 - m, iwork, xwork);
        }
      }

      i1 = m << 1;
      ib >>= 1;
      for (i2 = 0; i2 < ib; i2++) {
        merge_58LgYLQi(idx, x, i2 * i1, m, m, iwork, xwork);
      }

      m = i1;
    }

    if (1 - nNaNs > m) {
      merge_58LgYLQi(idx, x, 0, m, 1 - (nNaNs + m), iwork, xwork);
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
