#include "Wrapper_Model.h"
static RT_MODEL_LongSafe_SWC_T LongSafe_SWC_M_;
static RT_MODEL_LongSafe_SWC_T *const LongSafe_SWC_MPtr =
    &LongSafe_SWC_M_;                     /* Real-time model */
static B_LongSafe_SWC_T LongSafe_SWC_B;   /* Observable signals */
static DW_LongSafe_SWC_T LongSafe_SWC_DW; /* Observable states */

void LongSafe_SWC_init(void) {
  RT_MODEL_LongSafe_SWC_T *const LongSafe_SWC_M = LongSafe_SWC_MPtr;

  /* Pack model data into RTM */
  LongSafe_SWC_M->blockIO = &LongSafe_SWC_B;
  LongSafe_SWC_M->dwork = &LongSafe_SWC_DW;

  B_LongSafe_SWC_T *LongSafe_SWC_B = LongSafe_SWC_M->blockIO;
  DW_LongSafe_SWC_T *LongSafe_SWC_DW = LongSafe_SWC_M->dwork;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* block I/O */
  (void)memset(((void *)LongSafe_SWC_B), 0, sizeof(B_LongSafe_SWC_T));

    {
    LongSafe_SWC_B->AEB.Ltap.AEB.HBA_State = HBA_INITIALIZE;
    LongSafe_SWC_B->AEB.Ltap.AEB.FCW_State = FCW_OFF;
    LongSafe_SWC_B->AEB.Ltap.AEB.AWB_State = AWB_INITIALIZE;
    LongSafe_SWC_B->AEB.Ltap.AEB.AEB_State = AEB_OFF;
  }

  /* states (dwork) */
  (void)memset((void *)LongSafe_SWC_DW, 0, sizeof(DW_LongSafe_SWC_T));

  /* SystemInitialize for Atomic SubSystem: '<Root>/AEB' */
  LongSafe_Control_Init(&LongSafe_SWC_B->AEB,
                        &LongSafe_SWC_DW->AEB);
}
void LongSafe_SWC_s(AsVseOut *LongSafe_SWC_U_Vse,
                    AsCoreOut_T *LongSafe_SWC_U_CoreOut,
                    AsParamConfig_T *LongSafe_SWC_U_ParamConfig,
                    LgSafe_T *LongSafe_SWC_Y_LgSafe,
                    AsCmdLgSafe_T *LongSafe_SWC_Y_AsCmdLgSafe,
                    AsDisplayLgSafe_T *LongSafe_SWC_Y_AsDisplayLgSafe) {
  RT_MODEL_LongSafe_SWC_T *const LongSafe_SWC_M = LongSafe_SWC_MPtr;
  LongSafe_SWC_step(LongSafe_SWC_M, LongSafe_SWC_U_Vse, LongSafe_SWC_U_CoreOut,
                    LongSafe_SWC_U_ParamConfig, LongSafe_SWC_Y_LgSafe,
                    LongSafe_SWC_Y_AsCmdLgSafe, LongSafe_SWC_Y_AsDisplayLgSafe);
}
