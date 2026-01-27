/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'LongSafe_SWC'.
 *
 * Model version                  : 7.3237
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Thu Nov 20 16:40:24 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 64-bit (LP64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. ROM efficiency
 *    3. RAM efficiency
 *    4. Traceability
 *    5. Safety precaution
 *    6. Debugging
 *    7. MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>            /* This example main program uses printf/fflush */
#include "LongSafe_SWC.h"              /* Model's header file */

static RT_MODEL_LongSafe_SWC_T LongSafe_SWC_M_;
static RT_MODEL_LongSafe_SWC_T *const LongSafe_SWC_MPtr = &LongSafe_SWC_M_;/* Real-time model */
static B_LongSafe_SWC_T LongSafe_SWC_B;/* Observable signals */
static DW_LongSafe_SWC_T LongSafe_SWC_DW;/* Observable states */

/* '<Root>/Vse' */
static AsVseOut LongSafe_SWC_U_Vse;

/* '<Root>/CoreOut' */
static AsCoreOut_T LongSafe_SWC_U_CoreOut;

/* '<Root>/ParamConfig' */
static AsParamConfig_T LongSafe_SWC_U_ParamConfig;

/* '<Root>/LgSafe' */
static LgSafe_T LongSafe_SWC_Y_LgSafe;

/* '<Root>/AsCmdLgSafe' */
static AsCmdLgSafe_T LongSafe_SWC_Y_AsCmdLgSafe;

/* '<Root>/AsDisplayLgSafe' */
static AsDisplayLgSafe_T LongSafe_SWC_Y_AsDisplayLgSafe;

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(RT_MODEL_LongSafe_SWC_T *const LongSafe_SWC_M);
void rt_OneStep(RT_MODEL_LongSafe_SWC_T *const LongSafe_SWC_M)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(LongSafe_SWC_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  LongSafe_SWC_step(LongSafe_SWC_M, &LongSafe_SWC_U_Vse, &LongSafe_SWC_U_CoreOut,
                    &LongSafe_SWC_U_ParamConfig, &LongSafe_SWC_Y_LgSafe,
                    &LongSafe_SWC_Y_AsCmdLgSafe, &LongSafe_SWC_Y_AsDisplayLgSafe);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_LongSafe_SWC_T *const LongSafe_SWC_M = LongSafe_SWC_MPtr;

  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Pack model data into RTM */
  LongSafe_SWC_M->blockIO = &LongSafe_SWC_B;
  LongSafe_SWC_M->dwork = &LongSafe_SWC_DW;

  /* Initialize model */
  LongSafe_SWC_initialize(LongSafe_SWC_M, &LongSafe_SWC_U_Vse,
    &LongSafe_SWC_U_CoreOut, &LongSafe_SWC_U_ParamConfig, &LongSafe_SWC_Y_LgSafe,
    &LongSafe_SWC_Y_AsCmdLgSafe, &LongSafe_SWC_Y_AsDisplayLgSafe);

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.2 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep(LongSafe_SWC_M);
   */
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(LongSafe_SWC_M) == (NULL)) {
    /*  Perform application tasks here */
  }

  /* Disable rt_OneStep here */
  /* Terminate model */
  LongSafe_SWC_terminate(LongSafe_SWC_M);
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
