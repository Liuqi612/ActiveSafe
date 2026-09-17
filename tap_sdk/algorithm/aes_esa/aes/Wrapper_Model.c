#include "Wrapper_Model.h"

static RT_MODEL_AES_ESA_SWC_T AES_ESA_SWC_M_;
static RT_MODEL_AES_ESA_SWC_T *const AES_ESA_SWC_MPtr =
    &AES_ESA_SWC_M_; /* Real-time model */
static B_AES_ESA_SWC_T  AES_ESA_SWC_B;  /* Observable signals */
static DW_AES_ESA_SWC_T AES_ESA_SWC_DW; /* Observable states  */

void AES_ESA_SWC_init(void) {
  RT_MODEL_AES_ESA_SWC_T *const AES_ESA_SWC_M = AES_ESA_SWC_MPtr;

  /* Pack model data into RTM */
  AES_ESA_SWC_M->blockIO = &AES_ESA_SWC_B;
  AES_ESA_SWC_M->dwork   = &AES_ESA_SWC_DW;

  B_AES_ESA_SWC_T  *AES_ESA_SWC_B  = AES_ESA_SWC_M->blockIO;
  DW_AES_ESA_SWC_T *AES_ESA_SWC_DW = AES_ESA_SWC_M->dwork;

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* block I/O */
  (void)memset((void *)AES_ESA_SWC_B,  0, sizeof(B_AES_ESA_SWC_T));

  /* states (dwork) */
  (void)memset((void *)AES_ESA_SWC_DW, 0, sizeof(DW_AES_ESA_SWC_T));
}

void AES_ESA_SWC_s(LanesInfo *AES_ESA_SWC_U_LanesInfo_n,
                   AsVseOut *AES_ESA_SWC_U_AsVseOut_f,
                   ElkInfo *AES_ESA_SWC_U_ElkInfo_c,
                   AsTarget *AES_ESA_SWC_U_AsTarget_aeb,
                   AS_FusionInfo *AES_ESA_SWC_U_AS_FusionInfo_a,
                   Reserved_Input *AES_ESA_SWC_U_Reserved_Input_h,
                   AES_ESA_T *AES_ESA_SWC_Y_AES_ESA) {
  RT_MODEL_AES_ESA_SWC_T *const AES_ESA_SWC_M = AES_ESA_SWC_MPtr;

  AES_ESA_SWC_step(AES_ESA_SWC_M,
                   AES_ESA_SWC_U_LanesInfo_n,
                   AES_ESA_SWC_U_AsVseOut_f,
                   AES_ESA_SWC_U_ElkInfo_c,
                   AES_ESA_SWC_U_AsTarget_aeb,
                   AES_ESA_SWC_U_AS_FusionInfo_a,
                   AES_ESA_SWC_U_Reserved_Input_h,
                   AES_ESA_SWC_Y_AES_ESA);
}
