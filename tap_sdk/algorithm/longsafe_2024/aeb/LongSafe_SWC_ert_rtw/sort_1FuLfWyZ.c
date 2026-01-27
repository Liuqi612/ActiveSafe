/*
 * File: sort_1FuLfWyZ.c
 *
 * Code generated for Simulink model 'LongSafe_SWC'.
 *
 * Model version                  : 7.3237
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Thu Nov 20 16:40:24 2025
 */

#include "rtwtypes.h"
#include "sort_1FuLfWyZ.h"

/* Function for MATLAB Function: '<S1682>/FindEdgePositionsAroundTTI' */
void sort_1FuLfWyZ(int8_T x[2])
{
  int8_T x4[4];
  int8_T perm_idx_0;
  int8_T perm_idx_1;
  x4[2] = 0;
  x4[3] = 0;
  x4[0] = x[0];
  x4[1] = x[1];
  if (x[0] <= x[1]) {
    perm_idx_0 = 1;
    perm_idx_1 = 2;
  } else {
    perm_idx_0 = 2;
    perm_idx_1 = 1;
  }

  x[0] = x4[perm_idx_0 - 1];
  x[1] = x4[perm_idx_1 - 1];
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
