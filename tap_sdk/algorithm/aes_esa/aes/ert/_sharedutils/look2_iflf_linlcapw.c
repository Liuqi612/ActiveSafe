/*
 * File: look2_iflf_linlcapw.c
 *
 * Code generated for Simulink model 'AES_ESA_SWC'.
 *
 * Model version                  : 7.1420
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Fri Aug  7 14:45:11 2026
 */

#include "rtwtypes.h"
#include "look2_iflf_linlcapw.h"

real32_T look2_iflf_linlcapw(real32_T u0, real32_T u1, const real32_T bp0[],
  const real32_T bp1[], const real32_T table[], const uint32_T maxIndex[],
  uint32_T stride)
{
  real32_T fractions[2];
  real32_T frac;
  real32_T y;
  real32_T yL_0d0;
  uint32_T bpIndices[2];
  uint32_T bpIdx;
  uint32_T offset_1d;

  /* Row-major Lookup 2-D
     Search method: 'linear'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = 0.0F;
  } else if (u0 < bp0[maxIndex[1U]]) {
    /* Linear Search */
    for (bpIdx = maxIndex[1U] >> 1U; u0 < bp0[bpIdx]; bpIdx = bpIdx - 1U) {
    }

    while (u0 >= bp0[bpIdx + 1U]) {
      bpIdx = bpIdx + 1U;
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex[1U];
    frac = 0.0F;
  }

  fractions[1U] = frac;
  bpIndices[1U] = bpIdx;

  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    bpIdx = 0U;
    frac = 0.0F;
  } else if (u1 < bp1[maxIndex[0U]]) {
    /* Linear Search */
    for (bpIdx = maxIndex[0U] >> 1U; u1 < bp1[bpIdx]; bpIdx = bpIdx - 1U) {
    }

    while (u1 >= bp1[bpIdx + 1U]) {
      bpIdx = bpIdx + 1U;
    }

    frac = (u1 - bp1[bpIdx]) / (bp1[bpIdx + 1U] - bp1[bpIdx]);
  } else {
    bpIdx = maxIndex[0U];
    frac = 0.0F;
  }

  /* Row-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'portable wrapping'
   */
  offset_1d = bpIndices[1U] * stride + bpIdx;
  if (bpIdx == maxIndex[0U]) {
    y = table[offset_1d];
  } else {
    yL_0d0 = table[offset_1d];
    y = (table[offset_1d + 1U] - yL_0d0) * frac + yL_0d0;
  }

  if (bpIndices[1U] == maxIndex[1U]) {
  } else {
    offset_1d = offset_1d + stride;
    if (bpIdx == maxIndex[0U]) {
      yL_0d0 = table[offset_1d];
    } else {
      yL_0d0 = table[offset_1d];
      yL_0d0 = (table[offset_1d + 1U] - yL_0d0) * frac + yL_0d0;
    }

    y = (yL_0d0 - y) * fractions[1U] + y;
  }

  return y;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
