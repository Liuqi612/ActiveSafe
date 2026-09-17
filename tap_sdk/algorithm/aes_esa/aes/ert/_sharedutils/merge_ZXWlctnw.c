/*
 * File: merge_ZXWlctnw.c
 *
 * Code generated for Simulink model 'AES_ESA_SWC'.
 *
 * Model version                  : 7.1293
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue Apr 28 17:15:49 2026
 */

#include "rtwtypes.h"
#include "merge_ZXWlctnw.h"

/* Function for MATLAB Function: '<S955>/MATLAB Function' */
void merge_ZXWlctnw(int32_T idx[96], real_T x[96], int32_T offset, int32_T np,
                    int32_T nq, int32_T iwork[96], real_T xwork[96])
{
  int32_T p;
  if ((np != 0) && (nq != 0)) {
    int32_T iout;
    int32_T offset1;
    int32_T q;
    offset1 = np + nq;
    for (p = 0; p < offset1; p++) {
      q = offset + p;
      iwork[p] = idx[q];
      xwork[p] = x[q];
    }

    p = 0;
    q = np;
    iout = offset - 1;
    int32_T exitg1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork[p] <= xwork[q]) {
        idx[iout] = iwork[p];
        x[iout] = xwork[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx[iout] = iwork[q];
        x[iout] = xwork[q];
        if (q + 1 < offset1) {
          q++;
        } else {
          offset1 = iout - p;
          while (p + 1 <= np) {
            q = (offset1 + p) + 1;
            idx[q] = iwork[p];
            x[q] = xwork[p];
            p++;
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
