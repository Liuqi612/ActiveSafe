#ifndef __WRAPPER__
#define __WRAPPER__

#include "AES_ESA_SWC.h"

extern void AES_ESA_SWC_init(void);
extern void AES_ESA_SWC_s(LanesInfo *AES_ESA_SWC_U_LanesInfo_n,
                          AsVseOut *AES_ESA_SWC_U_AsVseOut_f,
                          ElkInfo *AES_ESA_SWC_U_ElkInfo_c,
                          AsTarget *AES_ESA_SWC_U_AsTarget_aeb,
                          AS_FusionInfo *AES_ESA_SWC_U_AS_FusionInfo_a,
                          Reserved_Input *AES_ESA_SWC_U_Reserved_Input_h,
                          AES_ESA_T *AES_ESA_SWC_Y_AES_ESA);

#endif
