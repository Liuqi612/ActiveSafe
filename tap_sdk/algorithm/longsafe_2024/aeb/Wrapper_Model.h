#ifndef __WRAPPER__
#define __WRAPPER__

#include "algorithm/longsafe_2024/aeb/LongSafe_SWC_ert_rtw/LongSafe_SWC.h"

extern void LongSafe_Control_Init(B_LongSafe_Control_T *localB,
                                  DW_LongSafe_Control_T *localDW);
extern void LongSafe_SWC_init(void);
extern void LongSafe_SWC_s(AsVseOut *LongSafe_SWC_U_Vse,
                           AsCoreOut_T *LongSafe_SWC_U_CoreOut,
                           AsParamConfig_T *LongSafe_SWC_U_ParamConfig,
                           LgSafe_T *LongSafe_SWC_Y_LgSafe,
                           AsCmdLgSafe_T *LongSafe_SWC_Y_AsCmdLgSafe,
                           AsDisplayLgSafe_T *LongSafe_SWC_Y_AsDisplayLgSafe);

#endif
