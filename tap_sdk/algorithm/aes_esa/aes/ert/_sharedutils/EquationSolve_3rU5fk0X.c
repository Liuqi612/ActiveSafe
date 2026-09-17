/*
 * File: EquationSolve_3rU5fk0X.c
 *
 * Code generated for Simulink model 'AES_ESA_SWC'.
 *
 * Model version                  : 7.1293
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue Apr 28 17:15:49 2026
 */

#include "rtwtypes.h"
#include <math.h>
#include "EquationSolve_3rU5fk0X.h"

/* Function for MATLAB Function: '<S9>/AES LastPointToSteer' */
real32_T EquationSolve_3rU5fk0X(real32_T CenterCircle_b, real32_T
  IntersectionPoint_y, real32_T CenterCircle_Radius)
{
  real32_T Delta;
  real32_T IntersectionPoint_x;
  Delta = 0.0F - (((IntersectionPoint_y * IntersectionPoint_y - 2.0F *
                    CenterCircle_b * IntersectionPoint_y) + CenterCircle_b *
                   CenterCircle_b) - CenterCircle_Radius * CenterCircle_Radius) *
    4.0F;
  if (Delta < 0.0F) {
    IntersectionPoint_x = 0.1F;
  } else if (Delta == 0.0F) {
    IntersectionPoint_x = 0.0F;
  } else {
    Delta = sqrtf(Delta);
    IntersectionPoint_x = Delta / 2.0F;
    if (!(IntersectionPoint_x >= 0.0F)) {
      IntersectionPoint_x = (0.0F - Delta) / 2.0F;
    }
  }

  return IntersectionPoint_x;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
