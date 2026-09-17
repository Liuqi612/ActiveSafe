/*
 * File: AES_ESA_SWC_private.h
 *
 * Code generated for Simulink model 'AES_ESA_SWC'.
 *
 * Model version                  : 7.1440
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Thu Aug 20 15:34:07 2026
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

#ifndef RTW_HEADER_AES_ESA_SWC_private_h_
#define RTW_HEADER_AES_ESA_SWC_private_h_
#include "rtwtypes.h"
#include "AES_ESA_SWC.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong/long check: insufficient preprocessor integer range. */

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */
extern const real32_T rtCP_pooled_7FD9MuxeLem4[10];
extern const real32_T rtCP_pooled_hs6A1ot8Med6[10];
extern const real32_T rtCP_pooled_YGy8xfeDkUV1[11];
extern const real32_T rtCP_pooled_ANqBe5eVDeOy[11];
extern const real32_T rtCP_pooled_tVlzOybOo1gt[11];
extern const real32_T rtCP_pooled_t3UaEcnv5J2J[11];
extern const real32_T rtCP_pooled_uFgp6veOwbJr[12];
extern const real32_T rtCP_pooled_J1nG2y4kK5g8[12];
extern const real32_T rtCP_pooled_NOB3JK8nWAWy[11];
extern const real32_T rtCP_pooled_OFAhO0Hxfftj[10];
extern const real32_T rtCP_pooled_PLN0BcMwo3RJ[10];
extern const real32_T rtCP_pooled_2WedpTKc8tPB[17];
extern const real32_T rtCP_pooled_ruazQtYuMQEl[17];
extern const real32_T rtCP_pooled_AERGpJtuOiCL[11];
extern const real32_T rtCP_pooled_C72LhqHmwJDY[12];
extern const real32_T rtCP_pooled_EeEdzTFWeaGG[10];
extern const real32_T rtCP_pooled_CnzdVABL7ytS[10];
extern const real32_T rtCP_pooled_nCUsinBYydvn[10];
extern const real32_T rtCP_pooled_qxjwu8dERLGO[10];
extern const real32_T rtCP_pooled_vKn4to5E1Z6Q[11];
extern const real32_T rtCP_pooled_vUbeu9Jxp1uh[12];
extern const real32_T rtCP_pooled_TWnlCf4YlNC5[10];
extern const real32_T rtCP_pooled_QhRf7YGSYCR9[17];
extern const real32_T rtCP_pooled_KMZQQSUkZmqN[11];
extern const real32_T rtCP_pooled_aQQqEkjYjoKT[12];
extern const real32_T rtCP_pooled_HZWbBkTTstYz[10];
extern const real32_T rtCP_pooled_94F4rMG31VTQ[10];
extern const real32_T rtCP_pooled_X7iGqPkU9jgT[17];
extern const real32_T rtCP_pooled_5xKRScUrwDAL[11];
extern const real32_T rtCP_pooled_0qB9d9Ti0ezq[12];
extern const real32_T rtCP_pooled_5y7p1Y6rQfjH[10];
extern const real32_T rtCP_pooled_z6rdt4Ch3n3u[9];
extern const real32_T rtCP_pooled_2yjH4v1jGEcX[9];
extern const real32_T rtCP_pooled_wHAI0WuvDj0o[11];
extern const real32_T rtCP_pooled_aGG6wDzy2PMq[10];
extern const real32_T rtCP_pooled_JOy6SDwSsJpb[11];
extern const real32_T rtCP_pooled_pdoeikaY5Pil[10];
extern const real32_T rtCP_pooled_tCBQL9XNDSJc[9];
extern const real32_T rtCP_pooled_MfnrVuTzHZ57[11];
extern const real32_T rtCP_pooled_PbZZKph3oBHN[10];
extern const real32_T rtCP_pooled_dHTqtMhH3K1s[25];
extern const real32_T rtCP_pooled_L8sKmEs9AFNx[25];
extern const real32_T rtCP_pooled_VmpF5tPu88oT[7];
extern const real32_T rtCP_pooled_O5WuuIHQtFxZ[7];
extern const real32_T rtCP_pooled_ZpkRq10KeFqv[7];
extern const real32_T rtCP_pooled_Yx3cFbQ50Kcz[7];
extern const real32_T rtCP_pooled_msWiEr6M56yg[10];
extern const real32_T rtCP_pooled_sVLq5jEL5kTL[7];
extern const real32_T rtCP_pooled_JCmDQfCvvSFC[7];
extern const real32_T rtCP_pooled_pQIrG8oDesBy[10];
extern const real32_T rtCP_pooled_Jz1o1kh4a8mR[10];
extern const real32_T rtCP_pooled_4thx6vFB7oVG[7];
extern const real32_T rtCP_pooled_xi5KKlSE061C[10];
extern const real32_T rtCP_pooled_Sh9VKuQQkN6v[10];
extern const real32_T rtCP_pooled_S0nqbvYSTipR[7];
extern const real32_T rtCP_pooled_4YHtzxZgY4US[10];
extern const real32_T rtCP_pooled_qBQGEendi0j1[7];
extern const real32_T rtCP_pooled_lL5oJdUHT7tR[10];
extern const real32_T rtCP_pooled_WYB6ZGyHahp0[10];
extern const real32_T rtCP_pooled_6JsYnnhavet1[7];
extern const real32_T rtCP_pooled_z9gQSgdZRyfA[10];
extern const real32_T rtCP_pooled_lRr9Z1VaM0pl[7];
extern const real32_T rtCP_pooled_1UcTWvzOnEGN[10];
extern const real32_T rtCP_pooled_mttavJ0ePDP4[10];
extern const real32_T rtCP_pooled_NynOYN1i678a[5];
extern const real32_T rtCP_pooled_Rm2imhcZnLF7[5];
extern const real32_T rtCP_pooled_spemi9UwOWT1[10];
extern const real32_T rtCP_pooled_ovUKZJCk7OaV[10];
extern const real32_T rtCP_pooled_04HRrDLg9sIL[3];
extern const real32_T rtCP_pooled_ytDj22Dz6KfZ[3];
extern const real32_T rtCP_pooled_GDZEzIGBMxhl[16];
extern const real32_T rtCP_pooled_wyAtreVwbgY0[16];
extern const real32_T rtCP_pooled_PCQrJTsv5Rch[16];
extern const real32_T rtCP_pooled_XlEfkoncwqz7[16];
extern const real32_T rtCP_pooled_zRP3sa5avWcJ[11];
extern const real32_T rtCP_pooled_DEJenjAKKM1B[11];
extern const real32_T rtCP_pooled_51zjmbhmYjQC[16];
extern const real32_T rtCP_pooled_GLxWItLib4MO[16];
extern const real32_T rtCP_pooled_nAYkNCkeQ5Zu[16];
extern const real32_T rtCP_pooled_ZuXklMUcaRLk[16];
extern const real32_T rtCP_pooled_qxbK72THXvZ8[16];
extern const real32_T rtCP_pooled_82pXAT5Rfjz0[16];
extern const real32_T rtCP_pooled_IyX34OLiDM9Z[16];
extern const real32_T rtCP_pooled_5n8GhXTkTpfl[16];
extern const real32_T rtCP_pooled_lvczVsh0sqm1[16];
extern const real32_T rtCP_pooled_mMphMpPQ0M0D[10];
extern const real32_T rtCP_pooled_d9oRdPrnPHrD[10];
extern const real32_T rtCP_pooled_crPphVIzvBYe[10];
extern const real32_T rtCP_pooled_2nSHyvncZyWM[16];
extern const real32_T rtCP_pooled_bPjubG2jBP7T[25];
extern const real32_T rtCP_pooled_iIkGlYiK9wlQ[25];
extern const real32_T rtCP_pooled_Ac3UoDbw1dH5[8];
extern const real32_T rtCP_pooled_LFhH9R8Z4ht9[8];
extern const real32_T rtCP_pooled_88jVNLqjXmYA[9];
extern const real32_T rtCP_pooled_lNhCnUVOwtsg[9];
extern const real32_T rtCP_pooled_6JJiBX5UPSQW[16];
extern const real32_T rtCP_pooled_H1cXDZ2Lq1nY[25];
extern const real32_T rtCP_pooled_IcuJlKcRDFh2[10];
extern const real32_T rtCP_pooled_P5xXudurO9xU[10];
extern const real32_T rtCP_pooled_fVOTTwHBkPPk[16];
extern const real32_T rtCP_pooled_gDgXjOZyQqjp[16];
extern const real32_T rtCP_pooled_rImJ8dSTrsP3[25];
extern const real32_T rtCP_pooled_FEsDbHqghr1u[25];
extern const real32_T rtCP_pooled_gVfm9HBLUkeB[10];
extern const real32_T rtCP_pooled_E4ldb50aMGcM[10];
extern const real32_T rtCP_pooled_wijWNQNDrJJz[16];
extern const real32_T rtCP_pooled_nTqZY1GCDPLw[10];
extern const real32_T rtCP_pooled_kpZnQ3QJgCmv[10];
extern const real32_T rtCP_pooled_o8kxm5wWoEwg[10];
extern const real32_T rtCP_pooled_Wg6vXJEVxGyr[10];
extern const real32_T rtCP_pooled_A6tJBFOT32pp[8];
extern const real32_T rtCP_pooled_BWElJYhsz4Op[10];
extern const real32_T rtCP_pooled_8LGPKP4aEWgd[10];
extern const real32_T rtCP_pooled_TMjb4C3adP2n[16];
extern const real32_T rtCP_pooled_ZvOmhgjHOhqM[10];
extern const real32_T rtCP_pooled_U73z2OXFRuBw[10];
extern const real32_T rtCP_pooled_UaLlzDn9fJQh[16];
extern const real32_T rtCP_pooled_SoitG0gJsR2R[10];
extern const real32_T rtCP_pooled_Qzkjpg3yvtTm[10];
extern const real32_T rtCP_pooled_zEd7nzb7SMTA[187];
extern const real32_T rtCP_pooled_8sP0O9iNT9q5[17];
extern const real32_T rtCP_pooled_cDsXXBwQSWGf[11];
extern const real32_T rtCP_pooled_fhcehgpNMabX[187];
extern const real32_T rtCP_pooled_5j5BuIKCOzqT[187];
extern const real32_T rtCP_pooled_HyQPYUKHldo5[187];
extern const real32_T rtCP_pooled_OAy3gkrrGkg9[187];
extern const real32_T rtCP_pooled_5l6Lc1Tpf8Rb[16];
extern const real32_T rtCP_pooled_1mptqMGmVIwo[16];
extern const real32_T rtCP_pooled_9mdxtsdyLM6V[16];
extern const real32_T rtCP_pooled_cbskrKm6H8Sw[16];
extern const real32_T rtCP_pooled_jQFkffI1hTWR[16];
extern const uint32_T rtCP_pooled_6REO3tGqzuma[2];
extern const boolean_T rtCP_pooled_2ukhhMbQGsh4[16];

#define rtCP_k_LCG_LftILCRghtCur_A1gain_P1_T1_tableData rtCP_pooled_7FD9MuxeLem4/* Expression: k_LCG_LftILCRghtCur_A1gain_P1_z
                                                                      * Referenced by: '<S677>/k_LCG_LftILCRghtCur_A1gain_P1_T1'
                                                                      */
#define rtCP_k_LCG_LftILCRghtCur_A1gain_P1_T1_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LftILCRghtCur_A1gain_P1_T1'
                                                                      */
#define rtCP_k_LCG_A1_gain_P1Lft_T_tableData rtCP_pooled_YGy8xfeDkUV1/* Expression: k_LCG_A1_gain_P1Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_A1_gain_P1Lft_T'
                                                                      */
#define rtCP_k_LCG_A1_gain_P1Lft_T_bp01Data rtCP_pooled_ANqBe5eVDeOy/* Expression: k_LCG_A1_gain_P1Lft_x
                                                                     * Referenced by: '<S677>/k_LCG_A1_gain_P1Lft_T'
                                                                     */
#define rtCP_k_LCG_SP_A1_gain_P1Lft_T_tableData rtCP_pooled_tVlzOybOo1gt/* Expression: k_LCG_SP_A1_gain_P1Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_SP_A1_gain_P1Lft_T'
                                                                      */
#define rtCP_k_LCG_SP_A1_gain_P1Lft_T_bp01Data rtCP_pooled_t3UaEcnv5J2J/* Expression: k_LCG_SP_A1_gain_P1Lft_x
                                                                      * Referenced by: '<S677>/k_LCG_SP_A1_gain_P1Lft_T'
                                                                      */
#define rtCP_k_LCG_LnWd_A1_gain_P1Lft_T1_tableData rtCP_pooled_uFgp6veOwbJr/* Expression: k_LCG_LnWd_A1_gain_P1Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A1_gain_P1Lft_T1'
                                                                      */
#define rtCP_k_LCG_LnWd_A1_gain_P1Lft_T1_bp01Data rtCP_pooled_J1nG2y4kK5g8/* Expression: k_LCG_LnWd_gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A1_gain_P1Lft_T1'
                                                                      */
#define rtCP_k_ILC_P1_SP_A1_Comp_Left_tableData rtCP_pooled_NOB3JK8nWAWy/* Expression: k_ILC_P1_SP_A1_Comp_Left_z
                                                                      * Referenced by: '<S677>/k_ILC_P1_SP_A1_Comp_Left'
                                                                      */
#define rtCP_k_ILC_P1_SP_A1_Comp_Left_bp01Data rtCP_pooled_NOB3JK8nWAWy/* Expression: k_ILC_P1_SP_A1_Comp_Left_x
                                                                      * Referenced by: '<S677>/k_ILC_P1_SP_A1_Comp_Left'
                                                                      */
#define rtCP_k_LCG_LftILCLftCur_A1gain_P1_T1_tableData rtCP_pooled_OFAhO0Hxfftj/* Expression: k_LCG_LftILCLftCur_A1gain_P1_z
                                                                      * Referenced by: '<S677>/k_LCG_LftILCLftCur_A1gain_P1_T1'
                                                                      */
#define rtCP_k_LCG_LftILCLftCur_A1gain_P1_T1_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LftILCLftCur_A1gain_P1_T1'
                                                                      */
#define rtCP_k_LCG_LftILCRgtCur_A1gain_P2_T1_tableData rtCP_pooled_PLN0BcMwo3RJ/* Expression: k_LCG_LftILCRghtCur_A1gain_P2_z
                                                                      * Referenced by: '<S677>/k_LCG_LftILCRgtCur_A1gain_P2_T1'
                                                                      */
#define rtCP_k_LCG_LftILCRgtCur_A1gain_P2_T1_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LftILCRgtCur_A1gain_P2_T1'
                                                                      */
#define rtCP_k_LCG_A1_gain_P2Lft_T1_tableData rtCP_pooled_2WedpTKc8tPB/* Expression: k_LCG_A1_gain_P2Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_A1_gain_P2Lft_T1'
                                                                      */
#define rtCP_k_LCG_A1_gain_P2Lft_T1_bp01Data rtCP_pooled_ruazQtYuMQEl/* Expression: k_LCG_A1_gain_P2Lft_x
                                                                      * Referenced by: '<S677>/k_LCG_A1_gain_P2Lft_T1'
                                                                      */
#define rtCP_k_LCG_SP_A1_gain_P2Lft_T_tableData rtCP_pooled_AERGpJtuOiCL/* Expression: k_LCG_SP_A1_gain_P2Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_SP_A1_gain_P2Lft_T'
                                                                      */
#define rtCP_k_LCG_SP_A1_gain_P2Lft_T_bp01Data rtCP_pooled_t3UaEcnv5J2J/* Expression: k_LCG_SP_A1_gain_P2Lft_x
                                                                      * Referenced by: '<S677>/k_LCG_SP_A1_gain_P2Lft_T'
                                                                      */
#define rtCP_k_LCG_LnWd_A1_gain_P2Lft_T2_tableData rtCP_pooled_C72LhqHmwJDY/* Expression: k_LCG_LnWd_A1_gain_P2Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A1_gain_P2Lft_T2'
                                                                      */
#define rtCP_k_LCG_LnWd_A1_gain_P2Lft_T2_bp01Data rtCP_pooled_J1nG2y4kK5g8/* Expression: k_LCG_LnWd_gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A1_gain_P2Lft_T2'
                                                                      */
#define rtCP_k_A02A1_gain_P2Lft_RCrv_T_tableData rtCP_pooled_EeEdzTFWeaGG/* Expression: k_A02A1_gain_P2Lft_RCrv_z
                                                                      * Referenced by: '<S677>/k_A02A1_gain_P2Lft_RCrv_T'
                                                                      */
#define rtCP_k_A02A1_gain_P2Lft_RCrv_T_bp01Data rtCP_pooled_CnzdVABL7ytS/* Expression: k_LCG_A02A1_P2gain_x
                                                                      * Referenced by: '<S677>/k_A02A1_gain_P2Lft_RCrv_T'
                                                                      */
#define rtCP_k_LCG_LftILCLftCur_A1gain_P2_T1_tableData rtCP_pooled_OFAhO0Hxfftj/* Expression: k_LCG_LftILCLftCur_A1gain_P2_z
                                                                      * Referenced by: '<S677>/k_LCG_LftILCLftCur_A1gain_P2_T1'
                                                                      */
#define rtCP_k_LCG_LftILCLftCur_A1gain_P2_T1_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LftILCLftCur_A1gain_P2_T1'
                                                                      */
#define rtCP_k_A02A1_gain_P2Lft_LCrv_T_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_A02A1_gain_P2Lft_LCrv_z
                                                                      * Referenced by: '<S677>/k_A02A1_gain_P2Lft_LCrv_T'
                                                                      */
#define rtCP_k_A02A1_gain_P2Lft_LCrv_T_bp01Data rtCP_pooled_CnzdVABL7ytS/* Expression: k_LCG_A02A1_P2gain_x
                                                                      * Referenced by: '<S677>/k_A02A1_gain_P2Lft_LCrv_T'
                                                                      */
#define rtCP_k_LCG_A02A1_gain_P2Lft_T_tableData rtCP_pooled_qxjwu8dERLGO/* Expression: k_LCG_A02A1_gain_P2Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_A02A1_gain_P2Lft_T'
                                                                      */
#define rtCP_k_LCG_A02A1_gain_P2Lft_T_bp01Data rtCP_pooled_CnzdVABL7ytS/* Expression: k_LCG_A02A1_P2gain_x
                                                                      * Referenced by: '<S677>/k_LCG_A02A1_gain_P2Lft_T'
                                                                      */
#define rtCP_k_LCG_RghtILCRgtCur_A1gain_P1_T_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_LCG_RghtILCRgtCur_A1gain_P1_z
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCRgtCur_A1gain_P1_T'
                                                                      */
#define rtCP_k_LCG_RghtILCRgtCur_A1gain_P1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCRgtCur_A1gain_P1_T'
                                                                      */
#define rtCP_k_LCG_A1_gain_P1Rght_T_tableData rtCP_pooled_YGy8xfeDkUV1/* Expression: k_LCG_A1_gain_P1Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_A1_gain_P1Rght_T'
                                                                      */
#define rtCP_k_LCG_A1_gain_P1Rght_T_bp01Data rtCP_pooled_ANqBe5eVDeOy/* Expression: k_LCG_A1_gain_P1Rght_x
                                                                      * Referenced by: '<S677>/k_LCG_A1_gain_P1Rght_T'
                                                                      */
#define rtCP_k_LCG_SP_A1_gain_P1Rght_T1_tableData rtCP_pooled_vKn4to5E1Z6Q/* Expression: k_LCG_SP_A1_gain_P1Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_SP_A1_gain_P1Rght_T1'
                                                                      */
#define rtCP_k_LCG_SP_A1_gain_P1Rght_T1_bp01Data rtCP_pooled_t3UaEcnv5J2J/* Expression: k_LCG_SP_A1_gain_P1Rght_x
                                                                      * Referenced by: '<S677>/k_LCG_SP_A1_gain_P1Rght_T1'
                                                                      */
#define rtCP_k_LCG_LnWd_A1_gain_P1Rght_T_tableData rtCP_pooled_vUbeu9Jxp1uh/* Expression: k_LCG_LnWd_A1_gain_P1Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A1_gain_P1Rght_T'
                                                                      */
#define rtCP_k_LCG_LnWd_A1_gain_P1Rght_T_bp01Data rtCP_pooled_J1nG2y4kK5g8/* Expression: k_LCG_LnWd_gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A1_gain_P1Rght_T'
                                                                      */
#define rtCP_k_ILC_P1_SP_A1_Comp_Right_tableData rtCP_pooled_NOB3JK8nWAWy/* Expression: k_ILC_P1_SP_A1_Comp_Right_z
                                                                      * Referenced by: '<S677>/k_ILC_P1_SP_A1_Comp_Right'
                                                                      */
#define rtCP_k_ILC_P1_SP_A1_Comp_Right_bp01Data rtCP_pooled_NOB3JK8nWAWy/* Expression: k_ILC_P1_SP_A1_Comp_Right_x
                                                                      * Referenced by: '<S677>/k_ILC_P1_SP_A1_Comp_Right'
                                                                      */
#define rtCP_k_LCG_RghtILCLftCur_A1gain_P1_T_tableData rtCP_pooled_7FD9MuxeLem4/* Expression: k_LCG_RghtILCLftCur_A1gain_P1_z
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCLftCur_A1gain_P1_T'
                                                                      */
#define rtCP_k_LCG_RghtILCLftCur_A1gain_P1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCLftCur_A1gain_P1_T'
                                                                      */
#define rtCP_k_LCG_RghtILCRgtCur_A1gain_P2_T1_tableData rtCP_pooled_TWnlCf4YlNC5/* Expression: k_LCG_RghtILCRgtCur_A1gain_P2_z
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCRgtCur_A1gain_P2_T1'
                                                                      */
#define rtCP_k_LCG_RghtILCRgtCur_A1gain_P2_T1_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCRgtCur_A1gain_P2_T1'
                                                                      */
#define rtCP_k_LCG_A1_gain_P2Rght_T_tableData rtCP_pooled_QhRf7YGSYCR9/* Expression: k_LCG_A1_gain_P2Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_A1_gain_P2Rght_T'
                                                                      */
#define rtCP_k_LCG_A1_gain_P2Rght_T_bp01Data rtCP_pooled_ruazQtYuMQEl/* Expression: k_LCG_A1_gain_P2Rght_x
                                                                      * Referenced by: '<S677>/k_LCG_A1_gain_P2Rght_T'
                                                                      */
#define rtCP_k_LCG_SP_A1_gain_P2Rght_T_tableData rtCP_pooled_KMZQQSUkZmqN/* Expression: k_LCG_SP_A1_gain_P2Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_SP_A1_gain_P2Rght_T'
                                                                      */
#define rtCP_k_LCG_SP_A1_gain_P2Rght_T_bp01Data rtCP_pooled_t3UaEcnv5J2J/* Expression: k_LCG_SP_A1_gain_P2Rght_x
                                                                      * Referenced by: '<S677>/k_LCG_SP_A1_gain_P2Rght_T'
                                                                      */
#define rtCP_k_LCG_LnWd_A1_gain_P2Rght_T1_tableData rtCP_pooled_aQQqEkjYjoKT/* Expression: k_LCG_LnWd_A1_gain_P2Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A1_gain_P2Rght_T1'
                                                                      */
#define rtCP_k_LCG_LnWd_A1_gain_P2Rght_T1_bp01Data rtCP_pooled_J1nG2y4kK5g8/* Expression: k_LCG_LnWd_gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A1_gain_P2Rght_T1'
                                                                      */
#define rtCP_k_A02A1_gain_P2Rght_RCrv_T_tableData rtCP_pooled_EeEdzTFWeaGG/* Expression: k_A02A1_gain_P2Rght_RCrv_z
                                                                      * Referenced by: '<S677>/k_A02A1_gain_P2Rght_RCrv_T'
                                                                      */
#define rtCP_k_A02A1_gain_P2Rght_RCrv_T_bp01Data rtCP_pooled_CnzdVABL7ytS/* Expression: k_LCG_A02A1_P2gain_x
                                                                      * Referenced by: '<S677>/k_A02A1_gain_P2Rght_RCrv_T'
                                                                      */
#define rtCP_k_LCG_RghtILCLftCur_A1gain_P2_T1_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_LCG_RghtILCLftCur_A1gain_P2_z
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCLftCur_A1gain_P2_T1'
                                                                      */
#define rtCP_k_LCG_RghtILCLftCur_A1gain_P2_T1_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCLftCur_A1gain_P2_T1'
                                                                      */
#define rtCP_k_A02A1_gain_P2Rght_LCrv_T_tableData rtCP_pooled_HZWbBkTTstYz/* Expression: k_A02A1_gain_P2Rght_LCrv_z
                                                                      * Referenced by: '<S677>/k_A02A1_gain_P2Rght_LCrv_T'
                                                                      */
#define rtCP_k_A02A1_gain_P2Rght_LCrv_T_bp01Data rtCP_pooled_CnzdVABL7ytS/* Expression: k_LCG_A02A1_P2gain_x
                                                                      * Referenced by: '<S677>/k_A02A1_gain_P2Rght_LCrv_T'
                                                                      */
#define rtCP_k_LCG_A02A1_gain_P2Rght_T_tableData rtCP_pooled_94F4rMG31VTQ/* Expression: k_LCG_A02A1_gain_P2Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_A02A1_gain_P2Rght_T'
                                                                      */
#define rtCP_k_LCG_A02A1_gain_P2Rght_T_bp01Data rtCP_pooled_CnzdVABL7ytS/* Expression: k_LCG_A02A1_P2gain_x
                                                                      * Referenced by: '<S677>/k_LCG_A02A1_gain_P2Rght_T'
                                                                      */
#define rtCP_k_LCG_SP_A1_Map_tableData rtCP_pooled_X7iGqPkU9jgT  /* Expression: k_LCG_SP_A1_Map_z
                                                                  * Referenced by: '<S677>/k_LCG_SP_A1_Map'
                                                                  */
#define rtCP_k_LCG_SP_A1_Map_bp01Data  rtCP_pooled_X7iGqPkU9jgT  /* Expression: k_LCG_SP_A1_Map_x
                                                                  * Referenced by: '<S677>/k_LCG_SP_A1_Map'
                                                                  */
#define rtCP_k_LCG_LftILCRghtCur_A0gain_P1_T_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_LCG_LftILCRghtCur_A0gain_P1_z
                                                                      * Referenced by: '<S677>/k_LCG_LftILCRghtCur_A0gain_P1_T'
                                                                      */
#define rtCP_k_LCG_LftILCRghtCur_A0gain_P1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LftILCRghtCur_A0gain_P1_T'
                                                                      */
#define rtCP_k_LCG_SP_A0_gain_P1Lft_T_tableData rtCP_pooled_5xKRScUrwDAL/* Expression: k_LCG_SP_A0_gain_P1Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_SP_A0_gain_P1Lft_T'
                                                                      */
#define rtCP_k_LCG_SP_A0_gain_P1Lft_T_bp01Data rtCP_pooled_t3UaEcnv5J2J/* Expression: k_LCG_SP_A0_gain_P1Lft_x
                                                                      * Referenced by: '<S677>/k_LCG_SP_A0_gain_P1Lft_T'
                                                                      */
#define rtCP_k_LCG_LnWd_A0_gain_P1Lft_T_tableData rtCP_pooled_0qB9d9Ti0ezq/* Expression: k_LCG_LnWd_A0_gain_P1Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A0_gain_P1Lft_T'
                                                                      */
#define rtCP_k_LCG_LnWd_A0_gain_P1Lft_T_bp01Data rtCP_pooled_J1nG2y4kK5g8/* Expression: k_LCG_LnWd_gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A0_gain_P1Lft_T'
                                                                      */
#define rtCP_k_LCG_LftILCLftCur_A0gain_P1_T_tableData rtCP_pooled_5y7p1Y6rQfjH/* Expression: k_LCG_LftILCLftCur_A0gain_P1_z
                                                                      * Referenced by: '<S677>/k_LCG_LftILCLftCur_A0gain_P1_T'
                                                                      */
#define rtCP_k_LCG_LftILCLftCur_A0gain_P1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LftILCLftCur_A0gain_P1_T'
                                                                      */
#define rtCP_k_LCG_LftILCRghtCur_A0gain_P2_T_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_LCG_LftILCRghtCur_A0gain_P2_z
                                                                      * Referenced by: '<S677>/k_LCG_LftILCRghtCur_A0gain_P2_T'
                                                                      */
#define rtCP_k_LCG_LftILCRghtCur_A0gain_P2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LftILCRghtCur_A0gain_P2_T'
                                                                      */
#define rtCP_k_LCG_A0_gain_P2Lft_T_tableData rtCP_pooled_z6rdt4Ch3n3u/* Expression: k_LCG_A0_gain_P2Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_A0_gain_P2Lft_T'
                                                                      */
#define rtCP_k_LCG_A0_gain_P2Lft_T_bp01Data rtCP_pooled_2yjH4v1jGEcX/* Expression: k_LCG_A0_gain_P2Lft_x
                                                                     * Referenced by: '<S677>/k_LCG_A0_gain_P2Lft_T'
                                                                     */
#define rtCP_k_LCG_SP_A0_gain_P2Lft_T_tableData rtCP_pooled_wHAI0WuvDj0o/* Expression: k_LCG_SP_A0_gain_P2Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_SP_A0_gain_P2Lft_T'
                                                                      */
#define rtCP_k_LCG_SP_A0_gain_P2Lft_T_bp01Data rtCP_pooled_t3UaEcnv5J2J/* Expression: k_LCG_SP_A0_gain_P2Lft_x
                                                                      * Referenced by: '<S677>/k_LCG_SP_A0_gain_P2Lft_T'
                                                                      */
#define rtCP_k_LCG_LnWd_A0_gain_P2Lft_T1_tableData rtCP_pooled_0qB9d9Ti0ezq/* Expression: k_LCG_LnWd_A0_gain_P2Lft_z
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A0_gain_P2Lft_T1'
                                                                      */
#define rtCP_k_LCG_LnWd_A0_gain_P2Lft_T1_bp01Data rtCP_pooled_J1nG2y4kK5g8/* Expression: k_LCG_LnWd_gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A0_gain_P2Lft_T1'
                                                                      */
#define rtCP_k_LCG_LftILCLftCur_A0gain_P2_T_tableData rtCP_pooled_aGG6wDzy2PMq/* Expression: k_LCG_LftILCLftCur_A0gain_P2_z
                                                                      * Referenced by: '<S677>/k_LCG_LftILCLftCur_A0gain_P2_T'
                                                                      */
#define rtCP_k_LCG_LftILCLftCur_A0gain_P2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LftILCLftCur_A0gain_P2_T'
                                                                      */
#define rtCP_k_LCG_RghtILCRgtCur_A0gain_P1_T1_tableData rtCP_pooled_aGG6wDzy2PMq/* Expression: k_LCG_RghtILCRgtCur_A0gain_P1_z
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCRgtCur_A0gain_P1_T1'
                                                                      */
#define rtCP_k_LCG_RghtILCRgtCur_A0gain_P1_T1_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCRgtCur_A0gain_P1_T1'
                                                                      */
#define rtCP_k_LCG_SP_A0_gain_P1Rght_T1_tableData rtCP_pooled_JOy6SDwSsJpb/* Expression: k_LCG_SP_A0_gain_P1Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_SP_A0_gain_P1Rght_T1'
                                                                      */
#define rtCP_k_LCG_SP_A0_gain_P1Rght_T1_bp01Data rtCP_pooled_t3UaEcnv5J2J/* Expression: k_LCG_SP_A0_gain_P1Rght_x
                                                                      * Referenced by: '<S677>/k_LCG_SP_A0_gain_P1Rght_T1'
                                                                      */
#define rtCP_k_LCG_LnWd_A0_gain_P1Rght_T_tableData rtCP_pooled_0qB9d9Ti0ezq/* Expression: k_LCG_LnWd_A0_gain_P1Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A0_gain_P1Rght_T'
                                                                      */
#define rtCP_k_LCG_LnWd_A0_gain_P1Rght_T_bp01Data rtCP_pooled_J1nG2y4kK5g8/* Expression: k_LCG_LnWd_gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A0_gain_P1Rght_T'
                                                                      */
#define rtCP_k_LCG_RghtILCLftCur_A0gain_P1_T_tableData rtCP_pooled_pdoeikaY5Pil/* Expression: k_LCG_RghtILCLftCur_A0gain_P1_z
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCLftCur_A0gain_P1_T'
                                                                      */
#define rtCP_k_LCG_RghtILCLftCur_A0gain_P1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCLftCur_A0gain_P1_T'
                                                                      */
#define rtCP_k_LCG_RghtILCRgtCur_A0gain_P2_T_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_LCG_RghtILCRgtCur_A0gain_P2_z
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCRgtCur_A0gain_P2_T'
                                                                      */
#define rtCP_k_LCG_RghtILCRgtCur_A0gain_P2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCRgtCur_A0gain_P2_T'
                                                                      */
#define rtCP_k_LCG_A0_gain_P2Rght_T2_tableData rtCP_pooled_tCBQL9XNDSJc/* Expression: k_LCG_A0_gain_P2Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_A0_gain_P2Rght_T2'
                                                                      */
#define rtCP_k_LCG_A0_gain_P2Rght_T2_bp01Data rtCP_pooled_2yjH4v1jGEcX/* Expression: k_LCG_A0_gain_P2Rght_x
                                                                      * Referenced by: '<S677>/k_LCG_A0_gain_P2Rght_T2'
                                                                      */
#define rtCP_k_LCG_SP_A0_gain_P2Rght_T1_tableData rtCP_pooled_MfnrVuTzHZ57/* Expression: k_LCG_SP_A0_gain_P2Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_SP_A0_gain_P2Rght_T1'
                                                                      */
#define rtCP_k_LCG_SP_A0_gain_P2Rght_T1_bp01Data rtCP_pooled_t3UaEcnv5J2J/* Expression: k_LCG_SP_A0_gain_P2Rght_x
                                                                      * Referenced by: '<S677>/k_LCG_SP_A0_gain_P2Rght_T1'
                                                                      */
#define rtCP_k_LCG_LnWd_A0_gain_P2Rght_T1_tableData rtCP_pooled_0qB9d9Ti0ezq/* Expression: k_LCG_LnWd_A0_gain_P2Rght_z
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A0_gain_P2Rght_T1'
                                                                      */
#define rtCP_k_LCG_LnWd_A0_gain_P2Rght_T1_bp01Data rtCP_pooled_J1nG2y4kK5g8/* Expression: k_LCG_LnWd_gain_x
                                                                      * Referenced by: '<S677>/k_LCG_LnWd_A0_gain_P2Rght_T1'
                                                                      */
#define rtCP_k_LCG_RghtILCLftCur_A0gain_P2_T_tableData rtCP_pooled_PbZZKph3oBHN/* Expression: k_LCG_RghtILCLftCur_A0gain_P2_z
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCLftCur_A0gain_P2_T'
                                                                      */
#define rtCP_k_LCG_RghtILCLftCur_A0gain_P2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_LCG_Cur_A0A1gain_x
                                                                      * Referenced by: '<S677>/k_LCG_RghtILCLftCur_A0gain_P2_T'
                                                                      */
#define rtCP_k_LCG_SP_A0_Map_tableData rtCP_pooled_dHTqtMhH3K1s  /* Expression: k_LCG_SP_A0_Map_z
                                                                  * Referenced by: '<S677>/k_LCG_SP_A0_Map'
                                                                  */
#define rtCP_k_LCG_SP_A0_Map_bp01Data  rtCP_pooled_L8sKmEs9AFNx  /* Expression: k_LCG_SP_A0_Map_x
                                                                  * Referenced by: '<S677>/k_LCG_SP_A0_Map'
                                                                  */
#define rtCP_k_ILC_SP_A0_RateLimitLeft_T_tableData rtCP_pooled_VmpF5tPu88oT/* Expression: k_ILC_SP_A0_RateLimitLeft_z
                                                                      * Referenced by: '<S677>/k_ILC_SP_A0_RateLimitLeft_T'
                                                                      */
#define rtCP_k_ILC_SP_A0_RateLimitLeft_T_bp01Data rtCP_pooled_O5WuuIHQtFxZ/* Expression: k_ILC_SP_A0_RateLimit_x
                                                                      * Referenced by: '<S677>/k_ILC_SP_A0_RateLimitLeft_T'
                                                                      */
#define rtCP_k_ILC_SP_A0_RateLimitRight_T_tableData rtCP_pooled_ZpkRq10KeFqv/* Expression: k_ILC_SP_A0_RateLimitRight_z
                                                                      * Referenced by: '<S677>/k_ILC_SP_A0_RateLimitRight_T'
                                                                      */
#define rtCP_k_ILC_SP_A0_RateLimitRight_T_bp01Data rtCP_pooled_O5WuuIHQtFxZ/* Expression: k_ILC_SP_A0_RateLimit_x
                                                                      * Referenced by: '<S677>/k_ILC_SP_A0_RateLimitRight_T'
                                                                      */
#define rtCP_k_ILC_TgtLatSpdLeft_T_tableData rtCP_pooled_Yx3cFbQ50Kcz/* Expression: k_ILC_TgtLatSpdLeft_z
                                                                      * Referenced by: '<S677>/k_ILC_TgtLatSpdLeft_T'
                                                                      */
#define rtCP_k_ILC_TgtLatSpdLeft_T_bp01Data rtCP_pooled_O5WuuIHQtFxZ/* Expression: k_ILC_TgtLatSpd_x
                                                                     * Referenced by: '<S677>/k_ILC_TgtLatSpdLeft_T'
                                                                     */
#define rtCP_k_ILC_TgtLatSpdRight_T_tableData rtCP_pooled_Yx3cFbQ50Kcz/* Expression: k_ILC_TgtLatSpdRight_z
                                                                      * Referenced by: '<S677>/k_ILC_TgtLatSpdRight_T'
                                                                      */
#define rtCP_k_ILC_TgtLatSpdRight_T_bp01Data rtCP_pooled_O5WuuIHQtFxZ/* Expression: k_ILC_TgtLatSpd_x
                                                                      * Referenced by: '<S677>/k_ILC_TgtLatSpdRight_T'
                                                                      */
#define rtCP_k_ILC_LftILCRghtCur_XRefP1_T_tableData rtCP_pooled_msWiEr6M56yg/* Expression: k_ILC_LftILCRghtCur_XRefP1_z
                                                                      * Referenced by: '<S763>/k_ILC_LftILCRghtCur_XRefP1_T'
                                                                      */
#define rtCP_k_ILC_LftILCRghtCur_XRefP1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_LftILCRghtCur_XRefP1_T'
                                                                      */
#define rtCP_k_ILC_CoeffPreXRef_LftP1_tableData rtCP_pooled_sVLq5jEL5kTL/* Expression: k_ILC_CoeffPreXRef_LftP1_z
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreXRef_LftP1'
                                                                      */
#define rtCP_k_ILC_CoeffPreXRef_LftP1_bp01Data rtCP_pooled_JCmDQfCvvSFC/* Expression: k_ILC_CoeffDrvDis_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreXRef_LftP1'
                                                                      */
#define rtCP_k_ILC_LftILCLftCur_XRefP1_T_tableData rtCP_pooled_pQIrG8oDesBy/* Expression: k_ILC_LftILCLftCur_XRefP1_z
                                                                      * Referenced by: '<S763>/k_ILC_LftILCLftCur_XRefP1_T'
                                                                      */
#define rtCP_k_ILC_LftILCLftCur_XRefP1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_LftILCLftCur_XRefP1_T'
                                                                      */
#define rtCP_k_ILC_RghtILCRghtCur_XRefP1_T_tableData rtCP_pooled_Jz1o1kh4a8mR/* Expression: k_ILC_RghtILCRghtCur_XRefP1_z
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCRghtCur_XRefP1_T'
                                                                      */
#define rtCP_k_ILC_RghtILCRghtCur_XRefP1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCRghtCur_XRefP1_T'
                                                                      */
#define rtCP_k_ILC_CoeffPreXRef_RghtP1_tableData rtCP_pooled_4thx6vFB7oVG/* Expression: k_ILC_CoeffPreXRef_RghtP1_z
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreXRef_RghtP1'
                                                                      */
#define rtCP_k_ILC_CoeffPreXRef_RghtP1_bp01Data rtCP_pooled_JCmDQfCvvSFC/* Expression: k_ILC_CoeffDrvDis_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreXRef_RghtP1'
                                                                      */
#define rtCP_k_ILC_RghtILCLftCur_XRefP1_T_tableData rtCP_pooled_xi5KKlSE061C/* Expression: k_ILC_RghtILCLftCur_XRefP1_z
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCLftCur_XRefP1_T'
                                                                      */
#define rtCP_k_ILC_RghtILCLftCur_XRefP1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCLftCur_XRefP1_T'
                                                                      */
#define rtCP_k_ILC_LftILCRghtCur_DrvDsP1_T_tableData rtCP_pooled_Sh9VKuQQkN6v/* Expression: k_ILC_LftILCRghtCur_DrvDsP1_z
                                                                      * Referenced by: '<S763>/k_ILC_LftILCRghtCur_DrvDsP1_T'
                                                                      */
#define rtCP_k_ILC_LftILCRghtCur_DrvDsP1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_LftILCRghtCur_DrvDsP1_T'
                                                                      */
#define rtCP_k_ILC_CoeffPreDrvDs_LftP1_tableData rtCP_pooled_S0nqbvYSTipR/* Expression: k_ILC_CoeffPreDrvDs_LftP1_z
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreDrvDs_LftP1'
                                                                      */
#define rtCP_k_ILC_CoeffPreDrvDs_LftP1_bp01Data rtCP_pooled_JCmDQfCvvSFC/* Expression: k_ILC_CoeffDrvDis_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreDrvDs_LftP1'
                                                                      */
#define rtCP_k_ILC_LftILCLftCur_DrvDsP1_T_tableData rtCP_pooled_Sh9VKuQQkN6v/* Expression: k_ILC_LftILCLftCur_DrvDsP1_z
                                                                      * Referenced by: '<S763>/k_ILC_LftILCLftCur_DrvDsP1_T'
                                                                      */
#define rtCP_k_ILC_LftILCLftCur_DrvDsP1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_LftILCLftCur_DrvDsP1_T'
                                                                      */
#define rtCP_k_ILC_RghtILCRghtCur_DrvDsP1_T_tableData rtCP_pooled_Sh9VKuQQkN6v/* Expression: k_ILC_RghtILCRghtCur_DrvDsP1_z
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCRghtCur_DrvDsP1_T'
                                                                      */
#define rtCP_k_ILC_RghtILCRghtCur_DrvDsP1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCRghtCur_DrvDsP1_T'
                                                                      */
#define rtCP_k_ILC_CoeffPreDrvDs_RghtP1_tableData rtCP_pooled_S0nqbvYSTipR/* Expression: k_ILC_CoeffPreDrvDs_RghtP1_z
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreDrvDs_RghtP1'
                                                                      */
#define rtCP_k_ILC_CoeffPreDrvDs_RghtP1_bp01Data rtCP_pooled_JCmDQfCvvSFC/* Expression: k_ILC_CoeffDrvDis_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreDrvDs_RghtP1'
                                                                      */
#define rtCP_k_ILC_RghtILCLftCur_DrvDsP1_T_tableData rtCP_pooled_Sh9VKuQQkN6v/* Expression: k_ILC_RghtILCLftCur_DrvDsP1_z
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCLftCur_DrvDsP1_T'
                                                                      */
#define rtCP_k_ILC_RghtILCLftCur_DrvDsP1_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCLftCur_DrvDsP1_T'
                                                                      */
#define rtCP_k_ILC_LftILCRghtCur_XRefP2_T_tableData rtCP_pooled_4YHtzxZgY4US/* Expression: k_ILC_LftILCRghtCur_XRefP2_z
                                                                      * Referenced by: '<S763>/k_ILC_LftILCRghtCur_XRefP2_T'
                                                                      */
#define rtCP_k_ILC_LftILCRghtCur_XRefP2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_LftILCRghtCur_XRefP2_T'
                                                                      */
#define rtCP_k_ILC_CoeffPreXRef_LftP2_tableData rtCP_pooled_qBQGEendi0j1/* Expression: k_ILC_CoeffPreXRef_LftP2_z
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreXRef_LftP2'
                                                                      */
#define rtCP_k_ILC_CoeffPreXRef_LftP2_bp01Data rtCP_pooled_JCmDQfCvvSFC/* Expression: k_ILC_CoeffDrvDis_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreXRef_LftP2'
                                                                      */
#define rtCP_k_ILC_LftILCLftCur_XRefP2_T_tableData rtCP_pooled_lL5oJdUHT7tR/* Expression: k_ILC_LftILCLftCur_XRefP2_z
                                                                      * Referenced by: '<S763>/k_ILC_LftILCLftCur_XRefP2_T'
                                                                      */
#define rtCP_k_ILC_LftILCLftCur_XRefP2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_LftILCLftCur_XRefP2_T'
                                                                      */
#define rtCP_k_ILC_RghtILCRghtCur_XRefP2_T_tableData rtCP_pooled_WYB6ZGyHahp0/* Expression: k_ILC_RghtILCRghtCur_XRefP2_z
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCRghtCur_XRefP2_T'
                                                                      */
#define rtCP_k_ILC_RghtILCRghtCur_XRefP2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCRghtCur_XRefP2_T'
                                                                      */
#define rtCP_k_ILC_CoeffPreXRef_RghtP2_tableData rtCP_pooled_6JsYnnhavet1/* Expression: k_ILC_CoeffPreXRef_RghtP2_z
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreXRef_RghtP2'
                                                                      */
#define rtCP_k_ILC_CoeffPreXRef_RghtP2_bp01Data rtCP_pooled_JCmDQfCvvSFC/* Expression: k_ILC_CoeffDrvDis_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreXRef_RghtP2'
                                                                      */
#define rtCP_k_ILC_RghtILCLftCur_XRefP2_T_tableData rtCP_pooled_z9gQSgdZRyfA/* Expression: k_ILC_RghtILCLftCur_XRefP2_z
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCLftCur_XRefP2_T'
                                                                      */
#define rtCP_k_ILC_RghtILCLftCur_XRefP2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCLftCur_XRefP2_T'
                                                                      */
#define rtCP_k_ILC_LftILCRghtCur_DrvDsP2_T_tableData rtCP_pooled_Sh9VKuQQkN6v/* Expression: k_ILC_LftILCRghtCur_DrvDsP2_z
                                                                      * Referenced by: '<S763>/k_ILC_LftILCRghtCur_DrvDsP2_T'
                                                                      */
#define rtCP_k_ILC_LftILCRghtCur_DrvDsP2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_LftILCRghtCur_DrvDsP2_T'
                                                                      */
#define rtCP_k_ILC_CoeffPreDrvDs_LftP2_tableData rtCP_pooled_lRr9Z1VaM0pl/* Expression: k_ILC_CoeffPreDrvDs_LftP2_z
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreDrvDs_LftP2'
                                                                      */
#define rtCP_k_ILC_CoeffPreDrvDs_LftP2_bp01Data rtCP_pooled_JCmDQfCvvSFC/* Expression: k_ILC_CoeffDrvDis_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreDrvDs_LftP2'
                                                                      */
#define rtCP_k_ILC_LftILCLftCur_DrvDsP2_T_tableData rtCP_pooled_pQIrG8oDesBy/* Expression: k_ILC_LftILCLftCur_DrvDsP2_z
                                                                      * Referenced by: '<S763>/k_ILC_LftILCLftCur_DrvDsP2_T'
                                                                      */
#define rtCP_k_ILC_LftILCLftCur_DrvDsP2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_LftILCLftCur_DrvDsP2_T'
                                                                      */
#define rtCP_k_ILC_RghtILCRghtCur_DrvDsP2_T_tableData rtCP_pooled_Sh9VKuQQkN6v/* Expression: k_ILC_RghtILCRghtCur_DrvDsP2_z
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCRghtCur_DrvDsP2_T'
                                                                      */
#define rtCP_k_ILC_RghtILCRghtCur_DrvDsP2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCRghtCur_DrvDsP2_T'
                                                                      */
#define rtCP_k_ILC_CoeffPreDrvDs_RghtP2_tableData rtCP_pooled_lRr9Z1VaM0pl/* Expression: k_ILC_CoeffPreDrvDs_RghtP2_z
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreDrvDs_RghtP2'
                                                                      */
#define rtCP_k_ILC_CoeffPreDrvDs_RghtP2_bp01Data rtCP_pooled_JCmDQfCvvSFC/* Expression: k_ILC_CoeffDrvDis_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_CoeffPreDrvDs_RghtP2'
                                                                      */
#define rtCP_k_ILC_RghtILCLftCur_DrvDsP2_T_tableData rtCP_pooled_Sh9VKuQQkN6v/* Expression: k_ILC_RghtILCLftCur_DrvDsP2_z
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCLftCur_DrvDsP2_T'
                                                                      */
#define rtCP_k_ILC_RghtILCLftCur_DrvDsP2_T_bp01Data rtCP_pooled_hs6A1ot8Med6/* Expression: k_ILC_ROC_XRef_P1P2_x
                                                                      * Referenced by: '<S763>/k_ILC_RghtILCLftCur_DrvDsP2_T'
                                                                      */
#define rtCP_k_SPP_A1_filt_tau_table_tableData rtCP_pooled_1UcTWvzOnEGN/* Expression: k_SPP_A1_filt_tau_z
                                                                      * Referenced by: '<S828>/k_SPP_A1_filt_tau_table'
                                                                      */
#define rtCP_k_SPP_A1_filt_tau_table_bp01Data rtCP_pooled_mttavJ0ePDP4/* Expression: k_SPP_A1_filt_tau_x
                                                                      * Referenced by: '<S828>/k_SPP_A1_filt_tau_table'
                                                                      */
#define rtCP_uDLookupTable_tableData   rtCP_pooled_NynOYN1i678a  /* Expression: k_TJA_ME_valid_range_z
                                                                  * Referenced by: '<S682>/1-D Lookup Table'
                                                                  */
#define rtCP_uDLookupTable_bp01Data    rtCP_pooled_Rm2imhcZnLF7  /* Expression: k_TJA_ME_valid_range_x
                                                                  * Referenced by: '<S682>/1-D Lookup Table'
                                                                  */
#define rtCP_k_LBS_LaneBiasOvrdRateLmt_z_tableData rtCP_pooled_spemi9UwOWT1/* Expression: k_LBS_LaneBiasOvrdRateLmt_z
                                                                      * Referenced by: '<S836>/k_LBS_LaneBiasOvrdRateLmt_z'
                                                                      */
#define rtCP_k_LBS_LaneBiasOvrdRateLmt_z_bp01Data rtCP_pooled_ovUKZJCk7OaV/* Expression: k_LBS_LaneBiasOvrdRateLmt_x
                                                                      * Referenced by: '<S836>/k_LBS_LaneBiasOvrdRateLmt_z'
                                                                      */
#define rtCP_k_A2ToA3Term_gain_tableData rtCP_pooled_04HRrDLg9sIL/* Expression: k_A2ToA3Term_gain_z
                                                                  * Referenced by: '<S621>/k_A2ToA3Term_gain'
                                                                  */
#define rtCP_k_A2ToA3Term_gain_bp01Data rtCP_pooled_ytDj22Dz6KfZ /* Expression: k_A2ToA3Term_gain_x
                                                                  * Referenced by: '<S621>/k_A2ToA3Term_gain'
                                                                  */
#define rtCP_uDLookupTable1_tableData  rtCP_pooled_GDZEzIGBMxhl  /* Expression: k_AES_DriverStrJudge_AngSpdThr
                                                                  * Referenced by: '<S268>/1-D Lookup Table1'
                                                                  */
#define rtCP_uDLookupTable1_bp01Data   rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S268>/1-D Lookup Table1'
                                                                  */
#define rtCP_uDLookupTable4_tableData  rtCP_pooled_PCQrJTsv5Rch  /* Expression: k_AES_DriverStrJudge_AngThr
                                                                  * Referenced by: '<S268>/1-D Lookup Table4'
                                                                  */
#define rtCP_uDLookupTable4_bp01Data   rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S268>/1-D Lookup Table4'
                                                                  */
#define rtCP_uDLookupTable1_tableData_e rtCP_pooled_XlEfkoncwqz7 /* Expression: k_AES_PlanAddDist_SlowSpd
                                                                  * Referenced by: '<S8>/1-D Lookup Table1'
                                                                  */
#define rtCP_uDLookupTable1_bp01Data_j rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S8>/1-D Lookup Table1'
                                                                  */
#define rtCP_uDLookupTable2_tableData  rtCP_pooled_zRP3sa5avWcJ  /* Expression: k_AES_PlanAddDist_OnCome
                                                                  * Referenced by: '<S8>/1-D Lookup Table2'
                                                                  */
#define rtCP_uDLookupTable2_bp01Data   rtCP_pooled_DEJenjAKKM1B  /* Expression: k_AES_VspdBks_OnCome
                                                                  * Referenced by: '<S8>/1-D Lookup Table2'
                                                                  */
#define rtCP_uDLookupTable_tableData_h rtCP_pooled_51zjmbhmYjQC  /* Expression: k_AES_PlanAddDist_Static
                                                                  * Referenced by: '<S8>/1-D Lookup Table'
                                                                  */
#define rtCP_uDLookupTable_bp01Data_p  rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S8>/1-D Lookup Table'
                                                                  */
#define rtCP_uDLookupTable_tableData_m rtCP_pooled_GLxWItLib4MO  /* Expression: k_AES_CtrlPredTime
                                                                  * Referenced by: '<S913>/1-D Lookup Table'
                                                                  */
#define rtCP_uDLookupTable_bp01Data_i  rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S913>/1-D Lookup Table'
                                                                  */
#define rtCP_uDLookupTable1_tableData_j rtCP_pooled_nAYkNCkeQ5Zu /* Expression: k_AES_CheckObsDistMinFront
                                                                  * Referenced by: '<S260>/1-D Lookup Table1'
                                                                  */
#define rtCP_uDLookupTable1_bp01Data_b rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S260>/1-D Lookup Table1'
                                                                  */
#define rtCP_uDLookupTable2_tableData_l rtCP_pooled_nAYkNCkeQ5Zu /* Expression: k_AES_CheckObsDistMinRear
                                                                  * Referenced by: '<S260>/1-D Lookup Table2'
                                                                  */
#define rtCP_uDLookupTable2_bp01Data_g rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S260>/1-D Lookup Table2'
                                                                  */
#define rtCP_uDLookupTable3_tableData  rtCP_pooled_nAYkNCkeQ5Zu  /* Expression: k_AES_CheckObsDistMinFront
                                                                  * Referenced by: '<S260>/1-D Lookup Table3'
                                                                  */
#define rtCP_uDLookupTable3_bp01Data   rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S260>/1-D Lookup Table3'
                                                                  */
#define rtCP_uDLookupTable4_tableData_l rtCP_pooled_nAYkNCkeQ5Zu /* Expression: k_AES_CheckObsDistMinRear
                                                                  * Referenced by: '<S260>/1-D Lookup Table4'
                                                                  */
#define rtCP_uDLookupTable4_bp01Data_d rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S260>/1-D Lookup Table4'
                                                                  */
#define rtCP_uDLookupTable2_tableData_n rtCP_pooled_ZuXklMUcaRLk /* Expression: k_AES_LastPntBrk_TTC_OC
                                                                  * Referenced by: '<S9>/1-D Lookup Table2'
                                                                  */
#define rtCP_uDLookupTable2_bp01Data_k rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S9>/1-D Lookup Table2'
                                                                  */
#define rtCP_uDLookupTable4_tableData_c rtCP_pooled_qxbK72THXvZ8 /* Expression: k_AES_MaxBrakeDecelProtect
                                                                  * Referenced by: '<S9>/1-D Lookup Table4'
                                                                  */
#define rtCP_uDLookupTable4_bp01Data_f rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S9>/1-D Lookup Table4'
                                                                  */
#define rtCP_uDLookupTable3_tableData_b rtCP_pooled_82pXAT5Rfjz0 /* Expression: k_AES_LastPntBrk_TTC_OC_ESA
                                                                  * Referenced by: '<S9>/1-D Lookup Table3'
                                                                  */
#define rtCP_uDLookupTable3_bp01Data_o rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S9>/1-D Lookup Table3'
                                                                  */
#define rtCP_uDLookupTable5_tableData  rtCP_pooled_IyX34OLiDM9Z  /* Expression: k_AES_MaxBrakeDecelProtect_ESA
                                                                  * Referenced by: '<S9>/1-D Lookup Table5'
                                                                  */
#define rtCP_uDLookupTable5_bp01Data   rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S9>/1-D Lookup Table5'
                                                                  */
#define rtCP_uDLookupTable4_tableData_p rtCP_pooled_5n8GhXTkTpfl /* Expression: k_AES_t_ActiveMaxTimeThr
                                                                  * Referenced by: '<S1016>/1-D Lookup Table4'
                                                                  */
#define rtCP_uDLookupTable4_bp01Data_n rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S1016>/1-D Lookup Table4'
                                                                  */
#define rtCP_uDLookupTable1_tableData_f rtCP_pooled_GLxWItLib4MO /* Expression: k_AES_CtrlPredTime
                                                                  * Referenced by: '<S12>/1-D Lookup Table1'
                                                                  */
#define rtCP_uDLookupTable1_bp01Data_i rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S12>/1-D Lookup Table1'
                                                                  */
#define rtCP_uDLookupTable2_tableData_h rtCP_pooled_lvczVsh0sqm1 /* Expression: k_AES_CtrlStartPredTime
                                                                  * Referenced by: '<S11>/1-D Lookup Table2'
                                                                  */
#define rtCP_uDLookupTable2_bp01Data_a rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S11>/1-D Lookup Table2'
                                                                  */
#define rtCP_uDLookupTable1_tableData_a rtCP_pooled_GLxWItLib4MO /* Expression: k_AES_CtrlPredTime
                                                                  * Referenced by: '<S11>/1-D Lookup Table1'
                                                                  */
#define rtCP_uDLookupTable1_bp01Data_l rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S11>/1-D Lookup Table1'
                                                                  */
#define rtCP_k_LCK_Lat_PFac_Dy_StraLan_tableData rtCP_pooled_mMphMpPQ0M0D/* Expression: k_LCK_Lat_PFac_Dy_StraLan
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_StraLan_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_DyBks
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_InnerLftCurv_tableData rtCP_pooled_crPphVIzvBYe/* Expression: k_LCK_Lat_PFac_Dy_InnerLftCurv
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_InnerLftCurv'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_InnerLftCurv_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_DyBks
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_InnerLftCurv'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_OuterLftCurv_tableData rtCP_pooled_crPphVIzvBYe/* Expression: k_LCK_Lat_PFac_Dy_OuterLftCurv
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_OuterLftCurv'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_OuterLftCurv_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_DyBks
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_OuterLftCurv'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_InnerRgtCurv_tableData rtCP_pooled_crPphVIzvBYe/* Expression: k_LCK_Lat_PFac_Dy_InnerRgtCurv
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_InnerRgtCurv'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_InnerRgtCurv_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_DyBks
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_InnerRgtCurv'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_OuterRgtCurv_tableData rtCP_pooled_crPphVIzvBYe/* Expression: k_LCK_Lat_PFac_Dy_OuterRgtCurv
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_OuterRgtCurv'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_OuterRgtCurv_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_DyBks
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_OuterRgtCurv'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Vspd_tableData rtCP_pooled_2nSHyvncZyWM/* Expression: k_LCK_Lat_PFac_Vspd
                                                                    * Referenced by: '<S100>/k_LCK_Lat_PFac_Vspd'
                                                                    */
#define rtCP_k_LCK_Lat_PFac_Vspd_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_LCK_VspdBks
                                                                   * Referenced by: '<S100>/k_LCK_Lat_PFac_Vspd'
                                                                   */
#define rtCP_k_LCK_Lat_PFac_Rad_tableData rtCP_pooled_bPjubG2jBP7T/* Expression: k_AES_Lat_PFac_Rad
                                                                   * Referenced by: '<S98>/k_LCK_Lat_PFac_Rad'
                                                                   */
#define rtCP_k_LCK_Lat_PFac_Rad_bp01Data rtCP_pooled_iIkGlYiK9wlQ/* Expression: k_AES_RadBks
                                                                  * Referenced by: '<S98>/k_LCK_Lat_PFac_Rad'
                                                                  */
#define rtCP_k_LCK_Lat_PFac_SS_StraLan_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Lat_PFac_SS_StraLan
                                                                      * Referenced by: '<S99>/k_LCK_Lat_PFac_SS_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_SS_StraLan_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S99>/k_LCK_Lat_PFac_SS_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_SS_CurvLan_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Lat_PFac_SS_CurvLan
                                                                      * Referenced by: '<S99>/k_LCK_Lat_PFac_SS_CurvLan'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_SS_CurvLan_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S99>/k_LCK_Lat_PFac_SS_CurvLan'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_LW_tableData rtCP_pooled_88jVNLqjXmYA/* Expression: k_LCK_Lat_PFac_LaneWdth
                                                                  * Referenced by: '<S96>/k_LCK_Lat_PFac_LW'
                                                                  */
#define rtCP_k_LCK_Lat_PFac_LW_bp01Data rtCP_pooled_lNhCnUVOwtsg /* Expression: k_LCK_LaneWdth_Bks
                                                                  * Referenced by: '<S96>/k_LCK_Lat_PFac_LW'
                                                                  */
#define rtCP_k_LCK_Lat_PFac_Dy_StraLan1_tableData rtCP_pooled_mMphMpPQ0M0D/* Expression: k_LCK_Lat_PFac_Dy_StraLan
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_StraLan1'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_StraLan1_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_DyBks
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_StraLan1'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_InnerLftCurv1_tableData rtCP_pooled_crPphVIzvBYe/* Expression: k_LCK_Lat_PFac_Dy_InnerLftCurv
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_InnerLftCurv1'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_InnerLftCurv1_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_DyBks
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_InnerLftCurv1'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_InnerRgtCurv1_tableData rtCP_pooled_crPphVIzvBYe/* Expression: k_LCK_Lat_PFac_Dy_InnerRgtCurv
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_InnerRgtCurv1'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_InnerRgtCurv1_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_DyBks
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_InnerRgtCurv1'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_OuterRgtCurv1_tableData rtCP_pooled_crPphVIzvBYe/* Expression: k_LCK_Lat_PFac_Dy_OuterRgtCurv
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_OuterRgtCurv1'
                                                                      */
#define rtCP_k_LCK_Lat_PFac_Dy_OuterRgtCurv1_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_DyBks
                                                                      * Referenced by: '<S94>/k_LCK_Lat_PFac_Dy_OuterRgtCurv1'
                                                                      */
#define rtCP_k_LCK_Lat_IFac_Vspd_tableData rtCP_pooled_6JJiBX5UPSQW/* Expression: k_LCK_Lat_IFac_Vspd
                                                                    * Referenced by: '<S100>/k_LCK_Lat_IFac_Vspd'
                                                                    */
#define rtCP_k_LCK_Lat_IFac_Vspd_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_LCK_VspdBks
                                                                   * Referenced by: '<S100>/k_LCK_Lat_IFac_Vspd'
                                                                   */
#define rtCP_k_LCK_Lat_IFac_Rad_tableData rtCP_pooled_H1cXDZ2Lq1nY/* Expression: k_AES_Lat_IFac_Rad
                                                                   * Referenced by: '<S98>/k_LCK_Lat_IFac_Rad'
                                                                   */
#define rtCP_k_LCK_Lat_IFac_Rad_bp01Data rtCP_pooled_iIkGlYiK9wlQ/* Expression: k_AES_RadBks
                                                                  * Referenced by: '<S98>/k_LCK_Lat_IFac_Rad'
                                                                  */
#define rtCP_k_LCK_Lat_ILmtFac_Dy_StraLan_tableData rtCP_pooled_IcuJlKcRDFh2/* Expression: k_LCK_Lat_ILmtFac_Dy_StraLan
                                                                      * Referenced by: '<S93>/k_LCK_Lat_ILmtFac_Dy_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_ILmtFac_Dy_StraLan_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_DyBks
                                                                      * Referenced by: '<S93>/k_LCK_Lat_ILmtFac_Dy_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_ILmtFac_Dy_CurvLan_tableData rtCP_pooled_P5xXudurO9xU/* Expression: k_LCK_Lat_ILmtFac_Dy_CurvLan
                                                                      * Referenced by: '<S93>/k_LCK_Lat_ILmtFac_Dy_CurvLan'
                                                                      */
#define rtCP_k_LCK_Lat_ILmtFac_Dy_CurvLan_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_DyBks
                                                                      * Referenced by: '<S93>/k_LCK_Lat_ILmtFac_Dy_CurvLan'
                                                                      */
#define rtCP_k_LCK_Lat_ILmtFac_Vspd_StraLan_tableData rtCP_pooled_fVOTTwHBkPPk/* Expression: k_LCK_Lat_ILmtFac_Vspd_StraLan
                                                                      * Referenced by: '<S93>/k_LCK_Lat_ILmtFac_Vspd_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_ILmtFac_Vspd_StraLan_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_LCK_VspdBks
                                                                      * Referenced by: '<S93>/k_LCK_Lat_ILmtFac_Vspd_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_ILmt_Vspd_CurvLan_tableData rtCP_pooled_gDgXjOZyQqjp/* Expression: k_LCK_Lat_ILmtFac_Vspd_CurvLan
                                                                      * Referenced by: '<S93>/k_LCK_Lat_ILmt_Vspd_CurvLan'
                                                                      */
#define rtCP_k_LCK_Lat_ILmt_Vspd_CurvLan_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_LCK_VspdBks
                                                                      * Referenced by: '<S93>/k_LCK_Lat_ILmt_Vspd_CurvLan'
                                                                      */
#define rtCP_k_LCK_Lat_ILmtFar_Rad_tableData rtCP_pooled_rImJ8dSTrsP3/* Expression: k_LCK_Lat_ILmtFar_Rad
                                                                      * Referenced by: '<S93>/k_LCK_Lat_ILmtFar_Rad'
                                                                      */
#define rtCP_k_LCK_Lat_ILmtFar_Rad_bp01Data rtCP_pooled_iIkGlYiK9wlQ/* Expression: k_LCK_RadBks
                                                                     * Referenced by: '<S93>/k_LCK_Lat_ILmtFar_Rad'
                                                                     */
#define rtCP_k_LCK_Lat_ILmtNear_Rad_tableData rtCP_pooled_rImJ8dSTrsP3/* Expression: k_LCK_Lat_ILmtNear_Rad
                                                                      * Referenced by: '<S93>/k_LCK_Lat_ILmtNear_Rad'
                                                                      */
#define rtCP_k_LCK_Lat_ILmtNear_Rad_bp01Data rtCP_pooled_iIkGlYiK9wlQ/* Expression: k_LCK_RadBks
                                                                      * Referenced by: '<S93>/k_LCK_Lat_ILmtNear_Rad'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_Vspd_tableData rtCP_pooled_2nSHyvncZyWM/* Expression: k_LCK_Lat_DFac_Vspd
                                                                    * Referenced by: '<S100>/k_LCK_Lat_DFac_Vspd'
                                                                    */
#define rtCP_k_LCK_Lat_DFac_Vspd_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_LCK_VspdBks
                                                                   * Referenced by: '<S100>/k_LCK_Lat_DFac_Vspd'
                                                                   */
#define rtCP_k_LCK_Lat_DFac_Rad_tableData rtCP_pooled_FEsDbHqghr1u/* Expression: k_AES_Lat_DFac_Rad
                                                                   * Referenced by: '<S98>/k_LCK_Lat_DFac_Rad'
                                                                   */
#define rtCP_k_LCK_Lat_DFac_Rad_bp01Data rtCP_pooled_iIkGlYiK9wlQ/* Expression: k_AES_RadBks
                                                                  * Referenced by: '<S98>/k_LCK_Lat_DFac_Rad'
                                                                  */
#define rtCP_k_LCK_Lat_DFac_SS_StraLan_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Lat_DFac_SS_StraLan
                                                                      * Referenced by: '<S99>/k_LCK_Lat_DFac_SS_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_SS_StraLan_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S99>/k_LCK_Lat_DFac_SS_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_SS_CurvLan_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Lat_DFac_SS_CurvLan
                                                                      * Referenced by: '<S99>/k_LCK_Lat_DFac_SS_CurvLan'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_SS_CurvLan_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S99>/k_LCK_Lat_DFac_SS_CurvLan'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_LatRate_StraLan_tableData rtCP_pooled_gVfm9HBLUkeB/* Expression: k_LCK_Lat_DFac_LatRate_StraLan
                                                                      * Referenced by: '<S97>/k_LCK_Lat_DFac_LatRate_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_LatRate_StraLan_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_LatRateBks
                                                                      * Referenced by: '<S97>/k_LCK_Lat_DFac_LatRate_StraLan'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_LatRate_CurvLan_tableData rtCP_pooled_E4ldb50aMGcM/* Expression: k_LCK_Lat_DFac_LatRate_CurvLan
                                                                      * Referenced by: '<S97>/k_LCK_Lat_DFac_LatRate_CurvLan'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_LatRate_CurvLan_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_LatRateBks
                                                                      * Referenced by: '<S97>/k_LCK_Lat_DFac_LatRate_CurvLan'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_LW_tableData rtCP_pooled_88jVNLqjXmYA/* Expression: k_LCK_Lat_DFac_LaneWdth
                                                                  * Referenced by: '<S96>/k_LCK_Lat_DFac_LW'
                                                                  */
#define rtCP_k_LCK_Lat_DFac_LW_bp01Data rtCP_pooled_lNhCnUVOwtsg /* Expression: k_LCK_LaneWdth_Bks
                                                                  * Referenced by: '<S96>/k_LCK_Lat_DFac_LW'
                                                                  */
#define rtCP_k_LCK_Lat_DFac_LatRate_StraLan1_tableData rtCP_pooled_gVfm9HBLUkeB/* Expression: k_LCK_Lat_DFac_LatRate_StraLan
                                                                      * Referenced by: '<S97>/k_LCK_Lat_DFac_LatRate_StraLan1'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_LatRate_StraLan1_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_LatRateBks
                                                                      * Referenced by: '<S97>/k_LCK_Lat_DFac_LatRate_StraLan1'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_LatRate_CurvLan1_tableData rtCP_pooled_E4ldb50aMGcM/* Expression: k_LCK_Lat_DFac_LatRate_CurvLan
                                                                      * Referenced by: '<S97>/k_LCK_Lat_DFac_LatRate_CurvLan1'
                                                                      */
#define rtCP_k_LCK_Lat_DFac_LatRate_CurvLan1_bp01Data rtCP_pooled_d9oRdPrnPHrD/* Expression: k_LCK_Lat_LatRateBks
                                                                      * Referenced by: '<S97>/k_LCK_Lat_DFac_LatRate_CurvLan1'
                                                                      */
#define rtCP_k_LCK_HedCtrl_PFac_Rgt_tableData rtCP_pooled_wijWNQNDrJJz/* Expression: k_LCK_HedCtrl_PFac_Rgt
                                                                      * Referenced by: '<S71>/k_LCK_HedCtrl_PFac_Rgt'
                                                                      */
#define rtCP_k_LCK_HedCtrl_PFac_Rgt_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_LCK_VspdBks
                                                                      * Referenced by: '<S71>/k_LCK_HedCtrl_PFac_Rgt'
                                                                      */
#define rtCP_k_LCK_HedCtrl_PFac_Lft_tableData rtCP_pooled_wijWNQNDrJJz/* Expression: k_LCK_HedCtrl_PFac_Lft
                                                                      * Referenced by: '<S71>/k_LCK_HedCtrl_PFac_Lft'
                                                                      */
#define rtCP_k_LCK_HedCtrl_PFac_Lft_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_LCK_VspdBks
                                                                      * Referenced by: '<S71>/k_LCK_HedCtrl_PFac_Lft'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HA_StraCent_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_LCK_Hed_PFac_HA_StraCent
                                                                      * Referenced by: '<S73>/k_LCK_Hed_PFac_HA_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HA_StraCent_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngDiffBks
                                                                      * Referenced by: '<S73>/k_LCK_Hed_PFac_HA_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HA_StraSide_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_LCK_Hed_PFac_HA_StraSide
                                                                      * Referenced by: '<S73>/k_LCK_Hed_PFac_HA_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HA_StraSide_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngDiffBks
                                                                      * Referenced by: '<S73>/k_LCK_Hed_PFac_HA_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HA_CurvCent_tableData rtCP_pooled_kpZnQ3QJgCmv/* Expression: k_LCK_Hed_PFac_HA_CurvCent
                                                                      * Referenced by: '<S73>/k_LCK_Hed_PFac_HA_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HA_CurvCent_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngDiffBks
                                                                      * Referenced by: '<S73>/k_LCK_Hed_PFac_HA_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HA_CurvSide_tableData rtCP_pooled_kpZnQ3QJgCmv/* Expression: k_LCK_Hed_PFac_HA_CurvSide
                                                                      * Referenced by: '<S73>/k_LCK_Hed_PFac_HA_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HA_CurvSide_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngDiffBks
                                                                      * Referenced by: '<S73>/k_LCK_Hed_PFac_HA_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HAR_StraCent_tableData rtCP_pooled_o8kxm5wWoEwg/* Expression: k_LCK_Hed_PFac_HAR_StraCent
                                                                      * Referenced by: '<S74>/k_LCK_Hed_PFac_HAR_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HAR_StraCent_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngRateDiffBks
                                                                      * Referenced by: '<S74>/k_LCK_Hed_PFac_HAR_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HAR_StraSide_tableData rtCP_pooled_Wg6vXJEVxGyr/* Expression: k_LCK_Hed_PFac_HAR_StraSide
                                                                      * Referenced by: '<S74>/k_LCK_Hed_PFac_HAR_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HAR_StraSide_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngRateDiffBks
                                                                      * Referenced by: '<S74>/k_LCK_Hed_PFac_HAR_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HAR_CurvCent_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_LCK_Hed_PFac_HAR_CurvCent
                                                                      * Referenced by: '<S74>/k_LCK_Hed_PFac_HAR_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HAR_CurvCent_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngRateDiffBks
                                                                      * Referenced by: '<S74>/k_LCK_Hed_PFac_HAR_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HAR_CurvSide_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_LCK_Hed_PFac_HAR_CurvSide
                                                                      * Referenced by: '<S74>/k_LCK_Hed_PFac_HAR_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_HAR_CurvSide_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngRateDiffBks
                                                                      * Referenced by: '<S74>/k_LCK_Hed_PFac_HAR_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SA_StraCent_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_PFac_SA_StraCent
                                                                      * Referenced by: '<S77>/k_LCK_Hed_PFac_SA_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SA_StraCent_bp01Data rtCP_pooled_A6tJBFOT32pp/* Expression: k_LCK_StrAngBks
                                                                      * Referenced by: '<S77>/k_LCK_Hed_PFac_SA_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SA_StraSide_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_PFac_SA_StraSide
                                                                      * Referenced by: '<S77>/k_LCK_Hed_PFac_SA_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SA_StraSide_bp01Data rtCP_pooled_A6tJBFOT32pp/* Expression: k_LCK_StrAngBks
                                                                      * Referenced by: '<S77>/k_LCK_Hed_PFac_SA_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SA_CurvCent_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_PFac_SA_CurvCent
                                                                      * Referenced by: '<S77>/k_LCK_Hed_PFac_SA_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SA_CurvCent_bp01Data rtCP_pooled_A6tJBFOT32pp/* Expression: k_LCK_StrAngBks
                                                                      * Referenced by: '<S77>/k_LCK_Hed_PFac_SA_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SA_CurvSide_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_PFac_SA_CurvSide
                                                                      * Referenced by: '<S77>/k_LCK_Hed_PFac_SA_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SA_CurvSide_bp01Data rtCP_pooled_A6tJBFOT32pp/* Expression: k_LCK_StrAngBks
                                                                      * Referenced by: '<S77>/k_LCK_Hed_PFac_SA_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SS_StraCent_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_PFac_SS_StraCent
                                                                      * Referenced by: '<S78>/k_LCK_Hed_PFac_SS_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SS_StraCent_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S78>/k_LCK_Hed_PFac_SS_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SS_StraSide_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_PFac_SS_StraSide
                                                                      * Referenced by: '<S78>/k_LCK_Hed_PFac_SS_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SS_StraSide_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S78>/k_LCK_Hed_PFac_SS_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SS_CurvCent_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_PFac_SS_CurvCent
                                                                      * Referenced by: '<S78>/k_LCK_Hed_PFac_SS_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SS_CurvCent_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S78>/k_LCK_Hed_PFac_SS_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SS_CurvSide_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_PFac_SS_CurvSide
                                                                      * Referenced by: '<S78>/k_LCK_Hed_PFac_SS_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_SS_CurvSide_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S78>/k_LCK_Hed_PFac_SS_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_Dy_tableData rtCP_pooled_BWElJYhsz4Op/* Expression: k_LCK_Hed_PFac_Dy
                                                                  * Referenced by: '<S72>/k_LCK_Hed_PFac_Dy'
                                                                  */
#define rtCP_k_LCK_Hed_PFac_Dy_bp01Data rtCP_pooled_8LGPKP4aEWgd /* Expression: k_LCK_Hed_DyBks
                                                                  * Referenced by: '<S72>/k_LCK_Hed_PFac_Dy'
                                                                  */
#define rtCP_k_LCK_Hed_PFac_Dy_Curv_tableData rtCP_pooled_BWElJYhsz4Op/* Expression: k_LCK_Hed_PFac_Dy_Curv
                                                                      * Referenced by: '<S72>/k_LCK_Hed_PFac_Dy_Curv'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_Dy_Curv_bp01Data rtCP_pooled_8LGPKP4aEWgd/* Expression: k_LCK_Hed_DyBks
                                                                      * Referenced by: '<S72>/k_LCK_Hed_PFac_Dy_Curv'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_Vspd_tableData rtCP_pooled_TMjb4C3adP2n/* Expression: k_LCK_Hed_PFac_Vspd
                                                                    * Referenced by: '<S79>/k_LCK_Hed_PFac_Vspd'
                                                                    */
#define rtCP_k_LCK_Hed_PFac_Vspd_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_LCK_VspdBks
                                                                   * Referenced by: '<S79>/k_LCK_Hed_PFac_Vspd'
                                                                   */
#define rtCP_k_LCK_Hed_PFac_Rad_tableData rtCP_pooled_FEsDbHqghr1u/* Expression: k_AES_Hed_PFac_Rad
                                                                   * Referenced by: '<S76>/k_LCK_Hed_PFac_Rad'
                                                                   */
#define rtCP_k_LCK_Hed_PFac_Rad_bp01Data rtCP_pooled_iIkGlYiK9wlQ/* Expression: k_AES_RadBks
                                                                  * Referenced by: '<S76>/k_LCK_Hed_PFac_Rad'
                                                                  */
#define rtCP_k_LCK_Hed_PFac_Lane_Width_tableData rtCP_pooled_88jVNLqjXmYA/* Expression: k_LCK_Hed_PFac_LaneWdth
                                                                      * Referenced by: '<S75>/k_LCK_Hed_PFac_Lane_Width'
                                                                      */
#define rtCP_k_LCK_Hed_PFac_Lane_Width_bp01Data rtCP_pooled_lNhCnUVOwtsg/* Expression: k_LCK_LaneWdth_Bks
                                                                      * Referenced by: '<S75>/k_LCK_Hed_PFac_Lane_Width'
                                                                      */
#define rtCP_k_LCK_HedCtrl_DFac_Rgt_tableData rtCP_pooled_wijWNQNDrJJz/* Expression: k_LCK_HedCtrl_DFac_Rgt
                                                                      * Referenced by: '<S71>/k_LCK_HedCtrl_DFac_Rgt'
                                                                      */
#define rtCP_k_LCK_HedCtrl_DFac_Rgt_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_LCK_VspdBks
                                                                      * Referenced by: '<S71>/k_LCK_HedCtrl_DFac_Rgt'
                                                                      */
#define rtCP_k_LCK_HedCtrl_DFac_Lft_tableData rtCP_pooled_wijWNQNDrJJz/* Expression: k_LCK_HedCtrl_DFac_Lft
                                                                      * Referenced by: '<S71>/k_LCK_HedCtrl_DFac_Lft'
                                                                      */
#define rtCP_k_LCK_HedCtrl_DFac_Lft_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_LCK_VspdBks
                                                                      * Referenced by: '<S71>/k_LCK_HedCtrl_DFac_Lft'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HA_StraCent_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_LCK_Hed_DFac_HA_StraCent
                                                                      * Referenced by: '<S73>/k_LCK_Hed_DFac_HA_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HA_StraCent_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngDiffBks
                                                                      * Referenced by: '<S73>/k_LCK_Hed_DFac_HA_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HA_StraSide_tableData rtCP_pooled_nCUsinBYydvn/* Expression: k_LCK_Hed_DFac_HA_StraSide
                                                                      * Referenced by: '<S73>/k_LCK_Hed_DFac_HA_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HA_StraSide_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngDiffBks
                                                                      * Referenced by: '<S73>/k_LCK_Hed_DFac_HA_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HA_CurvCent_tableData rtCP_pooled_kpZnQ3QJgCmv/* Expression: k_LCK_Hed_DFac_HA_CurvCent
                                                                      * Referenced by: '<S73>/k_LCK_Hed_DFac_HA_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HA_CurvCent_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngDiffBks
                                                                      * Referenced by: '<S73>/k_LCK_Hed_DFac_HA_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HA_CurvSide_tableData rtCP_pooled_kpZnQ3QJgCmv/* Expression: k_LCK_Hed_DFac_HA_CurvSide
                                                                      * Referenced by: '<S73>/k_LCK_Hed_DFac_HA_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HA_CurvSide_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngDiffBks
                                                                      * Referenced by: '<S73>/k_LCK_Hed_DFac_HA_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HAR_StraCent_tableData rtCP_pooled_ZvOmhgjHOhqM/* Expression: k_LCK_Hed_DFac_HAR_StraCent
                                                                      * Referenced by: '<S74>/k_LCK_Hed_DFac_HAR_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HAR_StraCent_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngRateDiffBks
                                                                      * Referenced by: '<S74>/k_LCK_Hed_DFac_HAR_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HAR_StraSide_tableData rtCP_pooled_ZvOmhgjHOhqM/* Expression: k_LCK_Hed_DFac_HAR_StraSide
                                                                      * Referenced by: '<S74>/k_LCK_Hed_DFac_HAR_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HAR_StraSide_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngRateDiffBks
                                                                      * Referenced by: '<S74>/k_LCK_Hed_DFac_HAR_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HAR_CurvCent_tableData rtCP_pooled_U73z2OXFRuBw/* Expression: k_LCK_Hed_DFac_HAR_CurvCent
                                                                      * Referenced by: '<S74>/k_LCK_Hed_DFac_HAR_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HAR_CurvCent_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngRateDiffBks
                                                                      * Referenced by: '<S74>/k_LCK_Hed_DFac_HAR_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HAR_CurvSide_tableData rtCP_pooled_U73z2OXFRuBw/* Expression: k_LCK_Hed_DFac_HAR_CurvSide
                                                                      * Referenced by: '<S74>/k_LCK_Hed_DFac_HAR_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_HAR_CurvSide_bp01Data rtCP_pooled_nTqZY1GCDPLw/* Expression: k_LCK_HedAngRateDiffBks
                                                                      * Referenced by: '<S74>/k_LCK_Hed_DFac_HAR_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SA_StraCent_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_DFac_SA_StraCent
                                                                      * Referenced by: '<S77>/k_LCK_Hed_DFac_SA_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SA_StraCent_bp01Data rtCP_pooled_A6tJBFOT32pp/* Expression: k_LCK_StrAngBks
                                                                      * Referenced by: '<S77>/k_LCK_Hed_DFac_SA_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SA_StraSide_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_DFac_SA_StraSide
                                                                      * Referenced by: '<S77>/k_LCK_Hed_DFac_SA_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SA_StraSide_bp01Data rtCP_pooled_A6tJBFOT32pp/* Expression: k_LCK_StrAngBks
                                                                      * Referenced by: '<S77>/k_LCK_Hed_DFac_SA_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SA_CurvCent_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_DFac_SA_CurvCent
                                                                      * Referenced by: '<S77>/k_LCK_Hed_DFac_SA_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SA_CurvCent_bp01Data rtCP_pooled_A6tJBFOT32pp/* Expression: k_LCK_StrAngBks
                                                                      * Referenced by: '<S77>/k_LCK_Hed_DFac_SA_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SA_CurvSide_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_DFac_SA_CurvSide
                                                                      * Referenced by: '<S77>/k_LCK_Hed_DFac_SA_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SA_CurvSide_bp01Data rtCP_pooled_A6tJBFOT32pp/* Expression: k_LCK_StrAngBks
                                                                      * Referenced by: '<S77>/k_LCK_Hed_DFac_SA_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SS_StraCent_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_DFac_SS_StraCent
                                                                      * Referenced by: '<S78>/k_LCK_Hed_DFac_SS_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SS_StraCent_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S78>/k_LCK_Hed_DFac_SS_StraCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SS_StraSide_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_DFac_SS_StraSide
                                                                      * Referenced by: '<S78>/k_LCK_Hed_DFac_SS_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SS_StraSide_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S78>/k_LCK_Hed_DFac_SS_StraSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SS_CurvCent_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_DFac_SS_CurvCent
                                                                      * Referenced by: '<S78>/k_LCK_Hed_DFac_SS_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SS_CurvCent_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S78>/k_LCK_Hed_DFac_SS_CurvCent'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SS_CurvSide_tableData rtCP_pooled_Ac3UoDbw1dH5/* Expression: k_LCK_Hed_DFac_SS_CurvSide
                                                                      * Referenced by: '<S78>/k_LCK_Hed_DFac_SS_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_SS_CurvSide_bp01Data rtCP_pooled_LFhH9R8Z4ht9/* Expression: k_LCK_StrSpdBks
                                                                      * Referenced by: '<S78>/k_LCK_Hed_DFac_SS_CurvSide'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_Dy_tableData rtCP_pooled_BWElJYhsz4Op/* Expression: k_LCK_Hed_DFac_Dy
                                                                  * Referenced by: '<S72>/k_LCK_Hed_DFac_Dy'
                                                                  */
#define rtCP_k_LCK_Hed_DFac_Dy_bp01Data rtCP_pooled_8LGPKP4aEWgd /* Expression: k_LCK_Hed_DyBks
                                                                  * Referenced by: '<S72>/k_LCK_Hed_DFac_Dy'
                                                                  */
#define rtCP_k_LCK_Hed_DFac_Dy_Curv_tableData rtCP_pooled_BWElJYhsz4Op/* Expression: k_LCK_Hed_DFac_Dy_Curv
                                                                      * Referenced by: '<S72>/k_LCK_Hed_DFac_Dy_Curv'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_Dy_Curv_bp01Data rtCP_pooled_8LGPKP4aEWgd/* Expression: k_LCK_Hed_DyBks
                                                                      * Referenced by: '<S72>/k_LCK_Hed_DFac_Dy_Curv'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_Vspd_tableData rtCP_pooled_UaLlzDn9fJQh/* Expression: k_LCK_Hed_DFac_Vspd
                                                                    * Referenced by: '<S79>/k_LCK_Hed_DFac_Vspd'
                                                                    */
#define rtCP_k_LCK_Hed_DFac_Vspd_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_LCK_VspdBks
                                                                   * Referenced by: '<S79>/k_LCK_Hed_DFac_Vspd'
                                                                   */
#define rtCP_k_LCK_Hed_DFac_Rad_tableData rtCP_pooled_FEsDbHqghr1u/* Expression: k_AES_Hed_DFac_Rad
                                                                   * Referenced by: '<S76>/k_LCK_Hed_DFac_Rad'
                                                                   */
#define rtCP_k_LCK_Hed_DFac_Rad_bp01Data rtCP_pooled_iIkGlYiK9wlQ/* Expression: k_AES_RadBks
                                                                  * Referenced by: '<S76>/k_LCK_Hed_DFac_Rad'
                                                                  */
#define rtCP_k_LCK_Hed_DFac_LaneWidth_tableData rtCP_pooled_88jVNLqjXmYA/* Expression: k_LCK_Hed_DFac_LaneWdth
                                                                      * Referenced by: '<S75>/k_LCK_Hed_DFac_LaneWidth'
                                                                      */
#define rtCP_k_LCK_Hed_DFac_LaneWidth_bp01Data rtCP_pooled_lNhCnUVOwtsg/* Expression: k_LCK_LaneWdth_Bks
                                                                      * Referenced by: '<S75>/k_LCK_Hed_DFac_LaneWidth'
                                                                      */
#define rtCP_k_AES_CTL_heading_error_factor_tableData rtCP_pooled_SoitG0gJsR2R/* Expression: k_AES_CTL_heading_error_factor
                                                                      * Referenced by: '<S20>/k_AES_CTL_heading_error_factor'
                                                                      */
#define rtCP_k_AES_CTL_heading_error_factor_bp01Data rtCP_pooled_Qzkjpg3yvtTm/* Expression: k_AES_CTL_heading_spd
                                                                      * Referenced by: '<S20>/k_AES_CTL_heading_error_factor'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z2_tableData rtCP_pooled_zEd7nzb7SMTA/* Expression: k_AES_FeedForward_Sec_ESA_L
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z2'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z2_bp01Data rtCP_pooled_8sP0O9iNT9q5/* Expression: k_AES_FeedForward_CurveAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z2'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z2_bp02Data rtCP_pooled_cDsXXBwQSWGf/* Expression: k_AES_FeedForward_SpdAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z2'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z3_tableData rtCP_pooled_fhcehgpNMabX/* Expression: k_AES_FeedForward_First_ESA_L
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z3'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z3_bp01Data rtCP_pooled_8sP0O9iNT9q5/* Expression: k_AES_FeedForward_CurveAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z3'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z3_bp02Data rtCP_pooled_cDsXXBwQSWGf/* Expression: k_AES_FeedForward_SpdAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z3'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z4_tableData rtCP_pooled_zEd7nzb7SMTA/* Expression: k_AES_FeedForward_Sec_ESA_R
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z4'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z4_bp01Data rtCP_pooled_8sP0O9iNT9q5/* Expression: k_AES_FeedForward_CurveAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z4'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z4_bp02Data rtCP_pooled_cDsXXBwQSWGf/* Expression: k_AES_FeedForward_SpdAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z4'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z5_tableData rtCP_pooled_5j5BuIKCOzqT/* Expression: k_AES_FeedForward_First_ESA_R
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z5'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z5_bp01Data rtCP_pooled_8sP0O9iNT9q5/* Expression: k_AES_FeedForward_CurveAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z5'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z5_bp02Data rtCP_pooled_cDsXXBwQSWGf/* Expression: k_AES_FeedForward_SpdAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z5'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z_tableData rtCP_pooled_HyQPYUKHldo5/* Expression: k_AES_FeedForward_Coef_Sec_L
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z_bp01Data rtCP_pooled_8sP0O9iNT9q5/* Expression: k_AES_FeedForward_CurveAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z_bp02Data rtCP_pooled_cDsXXBwQSWGf/* Expression: k_AES_FeedForward_SpdAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z1_tableData rtCP_pooled_OAy3gkrrGkg9/* Expression: k_AES_FeedForward_Coef_First_L
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z1'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z1_bp01Data rtCP_pooled_8sP0O9iNT9q5/* Expression: k_AES_FeedForward_CurveAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z1'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z1_bp02Data rtCP_pooled_cDsXXBwQSWGf/* Expression: k_AES_FeedForward_SpdAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z1'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z6_tableData rtCP_pooled_HyQPYUKHldo5/* Expression: k_AES_FeedForward_Coef_Sec_R
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z6'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z6_bp01Data rtCP_pooled_8sP0O9iNT9q5/* Expression: k_AES_FeedForward_CurveAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z6'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z6_bp02Data rtCP_pooled_cDsXXBwQSWGf/* Expression: k_AES_FeedForward_SpdAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z6'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z7_tableData rtCP_pooled_OAy3gkrrGkg9/* Expression: k_AES_FeedForward_Coef_First_R
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z7'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z7_bp01Data rtCP_pooled_8sP0O9iNT9q5/* Expression: k_AES_FeedForward_CurveAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z7'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z7_bp02Data rtCP_pooled_cDsXXBwQSWGf/* Expression: k_AES_FeedForward_SpdAxis
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z7'
                                                                      */
#define rtCP_k_LCK_AngLimitMax_Vspd_tableData rtCP_pooled_5l6Lc1Tpf8Rb/* Expression: k_AES_AngLimitMax_Vspd
                                                                      * Referenced by: '<S170>/k_LCK_AngLimitMax_Vspd'
                                                                      */
#define rtCP_k_LCK_AngLimitMax_Vspd_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_AES_VspdBks
                                                                      * Referenced by: '<S170>/k_LCK_AngLimitMax_Vspd'
                                                                      */
#define rtCP_k_LCK_RatLmtFac_TorqCmd_Vspd_tableData rtCP_pooled_1mptqMGmVIwo/* Expression: k_AES_RatLmtFac_TorqCmd_Vspd
                                                                      * Referenced by: '<S169>/k_LCK_RatLmtFac_TorqCmd_Vspd'
                                                                      */
#define rtCP_k_LCK_RatLmtFac_TorqCmd_Vspd_bp01Data rtCP_pooled_wyAtreVwbgY0/* Expression: k_AES_VspdBks
                                                                      * Referenced by: '<S169>/k_LCK_RatLmtFac_TorqCmd_Vspd'
                                                                      */
#define rtCP_uDLookupTable_tableData_d rtCP_pooled_9mdxtsdyLM6V  /* Expression: k_AES_MaxBrakeDecelThr
                                                                  * Referenced by: '<S9>/1-D Lookup Table'
                                                                  */
#define rtCP_uDLookupTable_bp01Data_m  rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S9>/1-D Lookup Table'
                                                                  */
#define rtCP_uDLookupTable6_tableData  rtCP_pooled_cbskrKm6H8Sw  /* Expression: k_AES_MaxBrkDeThr_SlowSpd
                                                                  * Referenced by: '<S9>/1-D Lookup Table6'
                                                                  */
#define rtCP_uDLookupTable6_bp01Data   rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S9>/1-D Lookup Table6'
                                                                  */
#define rtCP_uDLookupTable1_tableData_o rtCP_pooled_jQFkffI1hTWR /* Expression: k_AES_MaxBrakeDecelThr_ESA
                                                                  * Referenced by: '<S9>/1-D Lookup Table1'
                                                                  */
#define rtCP_uDLookupTable1_bp01Data_h rtCP_pooled_wyAtreVwbgY0  /* Expression: k_AES_VspdBks
                                                                  * Referenced by: '<S9>/1-D Lookup Table1'
                                                                  */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z2_maxIndex rtCP_pooled_6REO3tGqzuma/* Computed Parameter: rtCP_KtLCCS_FacFFTermCrvtAndSpd_z2_maxIndex
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z2'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z3_maxIndex rtCP_pooled_6REO3tGqzuma/* Computed Parameter: rtCP_KtLCCS_FacFFTermCrvtAndSpd_z3_maxIndex
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z3'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z4_maxIndex rtCP_pooled_6REO3tGqzuma/* Computed Parameter: rtCP_KtLCCS_FacFFTermCrvtAndSpd_z4_maxIndex
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z4'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z5_maxIndex rtCP_pooled_6REO3tGqzuma/* Computed Parameter: rtCP_KtLCCS_FacFFTermCrvtAndSpd_z5_maxIndex
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z5'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z_maxIndex rtCP_pooled_6REO3tGqzuma/* Computed Parameter: rtCP_KtLCCS_FacFFTermCrvtAndSpd_z_maxIndex
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z1_maxIndex rtCP_pooled_6REO3tGqzuma/* Computed Parameter: rtCP_KtLCCS_FacFFTermCrvtAndSpd_z1_maxIndex
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z1'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z6_maxIndex rtCP_pooled_6REO3tGqzuma/* Computed Parameter: rtCP_KtLCCS_FacFFTermCrvtAndSpd_z6_maxIndex
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z6'
                                                                      */
#define rtCP_KtLCCS_FacFFTermCrvtAndSpd_z7_maxIndex rtCP_pooled_6REO3tGqzuma/* Computed Parameter: rtCP_KtLCCS_FacFFTermCrvtAndSpd_z7_maxIndex
                                                                      * Referenced by: '<S39>/KtLCCS_FacFFTermCrvtAndSpd_z7'
                                                                      */
#define rtCP_Logic_table               rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table
                                                                  * Referenced by: '<S738>/Logic'
                                                                  */
#define rtCP_Logic_table_o             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_o
                                                                  * Referenced by: '<S739>/Logic'
                                                                  */
#define rtCP_Logic_table_n             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_n
                                                                  * Referenced by: '<S935>/Logic'
                                                                  */
#define rtCP_Logic_table_e             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_e
                                                                  * Referenced by: '<S959>/Logic'
                                                                  */
#define rtCP_Logic_table_k             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_k
                                                                  * Referenced by: '<S1131>/Logic'
                                                                  */
#define rtCP_Logic_table_m             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_m
                                                                  * Referenced by: '<S970>/Logic'
                                                                  */
#define rtCP_Logic_table_i             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_i
                                                                  * Referenced by: '<S1015>/Logic'
                                                                  */
#define rtCP_Logic_table_h             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_h
                                                                  * Referenced by: '<S253>/Logic'
                                                                  */
#define rtCP_Logic_table_p             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_p
                                                                  * Referenced by: '<S210>/Logic'
                                                                  */

/* Pooled Parameter (Mixed Expressions)
 * Referenced by:
 *   '<S971>/SfD1'
 *   '<S1024>/SfD1'
 *   '<S1025>/SfD1'
 *   '<S1134>/SfD1'
 *   '<S1135>/SfD1'
 *   '<S925>/SfD1'
 *   '<S949>/SfD1'
 */
#define rtCP_pooled1                   (0.01F)

/* Computed Parameter: rtCP_TriggerHold_ML_TIME_MSEC
 * Referenced by: '<S65>/Trigger Hold'
 */
#define rtCP_TriggerHold_ML_TIME_MSEC  (20.0)

/* Computed Parameter: rtCP_Delay_Trig_k_AES_ML_TIME_SEC
 * Referenced by: '<S302>/Delay_Trig'
 */
#define rtCP_Delay_Trig_k_AES_ML_TIME_SEC (0.019999999552965164)

/* Expression: 0
 * Referenced by: '<S269>/Constant2'
 */
#define rtCP_Constant2_Value           (0.0)

/* Expression: 10.1
 * Referenced by: '<S460>/Constant'
 */
#define rtCP_Constant_Value            (10.1)

/* Expression: 10.1
 * Referenced by: '<S461>/Constant1'
 */
#define rtCP_Constant1_Value           (10.1)

/* Expression: 0.37
 * Referenced by: '<S621>/k_Path_Deviation_Filter_Gain1'
 */
#define rtCP_k_Path_Deviation_Filter_Gain1_Value_d (0.37)

/* Expression: 1
 * Referenced by: '<S438>/Choose_SP_conf'
 */
#define rtCP_Choose_SP_conf_Value      (1.0)

/* Expression: 1.825
 * Referenced by: '<S862>/Constant'
 */
#define rtCP_Constant_Value_m          (1.825)

/* Expression: 0.02
 * Referenced by: '<S863>/Ts'
 */
#define rtCP_Ts_Value                  (0.02)

/* Expression: 0
 * Referenced by: '<S865>/Constant1'
 */
#define rtCP_Constant1_Value_j4        (0.0)

/* Expression: 0
 * Referenced by: '<S865>/Constant2'
 */
#define rtCP_Constant2_Value_i         (0.0)

/* Expression: 0.01
 * Referenced by: '<S865>/Constant3'
 */
#define rtCP_Constant3_Value_a         (0.01)

/* Expression: 57.3
 * Referenced by: '<S865>/Constant4'
 */
#define rtCP_Constant4_Value_p         (57.3)

/* Expression: 12.88
 * Referenced by: '<S865>/Constant5'
 */
#define rtCP_Constant5_Value_g         (12.88)

/* Expression: 1.5
 * Referenced by: '<S865>/Constant6'
 */
#define rtCP_Constant6_Value_o         (1.5)

/* Expression: 3.089
 * Referenced by: '<S865>/WheelBase'
 */
#define rtCP_WheelBase_Value           (3.089)

/* Expression: 1e10
 * Referenced by: '<S52>/Constant'
 */
#define rtCP_Constant_Value_mf         (1.0E+10)

/* Expression: 1e10
 * Referenced by: '<S52>/Constant1'
 */
#define rtCP_Constant1_Value_i         (1.0E+10)

/* Expression: 200
 * Referenced by: '<S58>/k_LCK_HeadingRateLimitHldTim'
 */
#define rtCP_k_LCK_HeadingRateLimitHldTim_Value (200.0)

/* Expression: 200
 * Referenced by: '<S59>/k_LCK_HRRateLimitHldTim'
 */
#define rtCP_k_LCK_HRRateLimitHldTim_Value (200.0)

/* Expression: 1
 * Referenced by: '<S78>/Constant'
 */
#define rtCP_Constant_Value_a          (1.0)

/* Expression: 1
 * Referenced by: '<S78>/Constant1'
 */
#define rtCP_Constant1_Value_e         (1.0)

/* Expression: 1
 * Referenced by: '<S99>/Constant'
 */
#define rtCP_Constant_Value_n          (1.0)

/* Expression: 1
 * Referenced by: '<S99>/Constant1'
 */
#define rtCP_Constant1_Value_o         (1.0)

/* Expression: const
 * Referenced by: '<S187>/Constant'
 */
#define rtCP_Constant_Value_p          (1.0E-6)

/* Expression: 1
 * Referenced by: '<S209>/Constant9'
 */
#define rtCP_Constant9_Value_f         (1.0)

/* Expression: 3
 * Referenced by: '<S260>/Constant'
 */
#define rtCP_Constant_Value_c          (3.0)

/* Expression: 3
 * Referenced by: '<S260>/Constant2'
 */
#define rtCP_Constant2_Value_e         (3.0)

/* Expression: 0
 * Referenced by: '<S260>/Constant50'
 */
#define rtCP_Constant50_Value          (0.0)

/* Expression: 0
 * Referenced by: '<S260>/Constant51'
 */
#define rtCP_Constant51_Value          (0.0)

/* Expression: 2
 * Referenced by: '<S880>/Constant'
 */
#define rtCP_Constant_Value_b          (2.0)

/* Expression: 0
 * Referenced by: '<S880>/Constant1'
 */
#define rtCP_Constant1_Value_c         (0.0)

/* Expression: 2
 * Referenced by: '<S885>/Constant'
 */
#define rtCP_Constant_Value_e          (2.0)

/* Expression: 0
 * Referenced by: '<S885>/Constant1'
 */
#define rtCP_Constant1_Value_p         (0.0)

/* Expression: 2
 * Referenced by: '<S890>/Constant'
 */
#define rtCP_Constant_Value_d          (2.0)

/* Expression: 0
 * Referenced by: '<S890>/Constant1'
 */
#define rtCP_Constant1_Value_g         (0.0)

/* Expression: 2
 * Referenced by: '<S904>/Constant'
 */
#define rtCP_Constant_Value_m5         (2.0)

/* Expression: 0
 * Referenced by: '<S904>/Constant1'
 */
#define rtCP_Constant1_Value_ct        (0.0)

/* Expression: 0
 * Referenced by: '<S909>/Constant10'
 */
#define rtCP_Constant10_Value_l        (0.0)

/* Expression: 7
 * Referenced by: '<S909>/Constant8'
 */
#define rtCP_Constant8_Value_p         (7.0)

/* Expression: 1
 * Referenced by: '<S909>/Constant9'
 */
#define rtCP_Constant9_Value_p         (1.0)

/* Expression: 0
 * Referenced by: '<S910>/Constant10'
 */
#define rtCP_Constant10_Value_k        (0.0)

/* Expression: 7
 * Referenced by: '<S910>/Constant8'
 */
#define rtCP_Constant8_Value_m         (7.0)

/* Expression: 1
 * Referenced by: '<S910>/Constant9'
 */
#define rtCP_Constant9_Value_g         (1.0)

/* Expression: 1
 * Referenced by: '<S926>/Constant4'
 */
#define rtCP_Constant4_Value_n         (1.0)

/* Expression: 1
 * Referenced by: '<S928>/Constant4'
 */
#define rtCP_Constant4_Value_n0        (1.0)

/* Expression: 1
 * Referenced by: '<S950>/Constant4'
 */
#define rtCP_Constant4_Value_ed        (1.0)

/* Expression: 1
 * Referenced by: '<S952>/Constant4'
 */
#define rtCP_Constant4_Value_e0        (1.0)

/* Expression: 3.95
 * Referenced by: '<S8>/Constant9'
 */
#define rtCP_Constant9_Value_g2        (3.95)

/* Expression: 1.75
 * Referenced by: '<S981>/Constant'
 */
#define rtCP_Constant_Value_ek         (1.75)

/* Expression: -1.75
 * Referenced by: '<S981>/Constant1'
 */
#define rtCP_Constant1_Value_gn        (-1.75)

/* Expression: 0
 * Referenced by: '<S1000>/Constant3'
 */
#define rtCP_Constant3_Value_i0        (0.0)

/* Expression: 2
 * Referenced by: '<S1014>/Constant'
 */
#define rtCP_Constant_Value_as         (2.0)

/* Expression: 0.5
 * Referenced by: '<S62>/Switch3'
 */
#define rtCP_Switch3_Threshold         (0.5)

/* Expression: 0.5
 * Referenced by: '<S61>/Switch3'
 */
#define rtCP_Switch3_Threshold_i       (0.5)

/* Expression: k_ROC_CURVE_EXIT
 * Referenced by: '<S516>/k_ROC_CURVE_EXIT'
 */
#define rtCP_k_ROC_CURVE_EXIT_Value    (9500)

/* Computed Parameter: rtCP_Saturation_UpperSat
 * Referenced by: '<S110>/Saturation'
 */
#define rtCP_Saturation_UpperSat       (65535.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat
 * Referenced by: '<S110>/Saturation'
 */
#define rtCP_Saturation_LowerSat       (-65535.0F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S204>/Delay_Trig'
 */
#define rtCP_Delay_Trig_ML_TIME_SEC    (0.02F)

/* Computed Parameter: rtCP_RampDownOut_Y0
 * Referenced by: '<S215>/RampDownOut'
 */
#define rtCP_RampDownOut_Y0            (0.0F)

/* Computed Parameter: rtCP_RampDownTarget_Value
 * Referenced by: '<S215>/RampDownTarget'
 */
#define rtCP_RampDownTarget_Value      (0.0F)

/* Computed Parameter: rtCP_UnitDelay1_InitialCondition_l
 * Referenced by: '<S217>/Unit Delay1'
 */
#define rtCP_UnitDelay1_InitialCondition_l (0.0F)

/* Computed Parameter: rtCP_RampUpOut_Y0
 * Referenced by: '<S216>/RampUpOut'
 */
#define rtCP_RampUpOut_Y0              (0.0F)

/* Computed Parameter: rtCP_UnitDelay1_InitialCondition_b
 * Referenced by: '<S218>/Unit Delay1'
 */
#define rtCP_UnitDelay1_InitialCondition_b (0.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_m
 * Referenced by: '<S222>/Saturation'
 */
#define rtCP_Saturation_UpperSat_m     (65535.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_e
 * Referenced by: '<S222>/Saturation'
 */
#define rtCP_Saturation_LowerSat_e     (-65535.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_k0
 * Referenced by: '<S288>/Saturation'
 */
#define rtCP_Saturation_UpperSat_k0    (65535.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_h
 * Referenced by: '<S288>/Saturation'
 */
#define rtCP_Saturation_LowerSat_h     (-65535.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_jj
 * Referenced by: '<S390>/Saturation'
 */
#define rtCP_Saturation_UpperSat_jj    (65535.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_lw
 * Referenced by: '<S390>/Saturation'
 */
#define rtCP_Saturation_LowerSat_lw    (-65535.0F)

/* Expression: k_AES_ML_TIME_SEC
 * Referenced by: '<S282>/lane_edge_age_check'
 */
#define rtCP_lane_edge_age_check_k_AES_ML_TIME_SEC (0.02F)

/* Expression: k_AES_TrajColl_DiscreteDist
 * Referenced by: '<S269>/Constant10'
 */
#define rtCP_Constant10_Value_f        (0.5F)

/* Expression: k_AES_LeftLongSafeDistance
 * Referenced by: '<S269>/Constant11'
 */
#define rtCP_Constant11_Value          (1.0F)

/* Expression: k_AES_RightLongSafeDistance
 * Referenced by: '<S269>/Constant12'
 */
#define rtCP_Constant12_Value          (1.0F)

/* Expression: k_AES_Dis_EgoRAxleToFBumper
 * Referenced by: '<S269>/Constant6'
 */
#define rtCP_Constant6_Value_j         (3.9F)

/* Expression: k_AES_TrajColl_DiscreteDist
 * Referenced by: '<S269>/Constant7'
 */
#define rtCP_Constant7_Value_j         (0.5F)

/* Expression: k_AES_Obj_PredictedTime
 * Referenced by: '<S269>/Constant8'
 */
#define rtCP_Constant8_Value_e         (0.0F)

/* Expression: k_AES_EgoVehicle_Width
 * Referenced by: '<S269>/Constant9'
 */
#define rtCP_Constant9_Value_e         (1.9F)

/* Computed Parameter: rtCP_Constant13_Value
 * Referenced by: '<S428>/Constant13'
 */
#define rtCP_Constant13_Value          (0.0F)

/* Computed Parameter: rtCP_Constant14_Value
 * Referenced by: '<S428>/Constant14'
 */
#define rtCP_Constant14_Value          (0.0F)

/* Computed Parameter: rtCP_RE_MinValidSfConfThreshold_Value
 * Referenced by: '<S431>/RE_MinValidSfConfThreshold'
 */
#define rtCP_RE_MinValidSfConfThreshold_Value (0.5F)

/* Computed Parameter: rtCP_RE_MinValidSfConfThreshold_Value_h
 * Referenced by: '<S432>/RE_MinValidSfConfThreshold'
 */
#define rtCP_RE_MinValidSfConfThreshold_Value_h (0.5F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S469>/Det_LM_Flicker'
 */
#define rtCP_Det_LM_Flicker_ML_TIME_SEC (0.02F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S470>/Det_LM_Flicker'
 */
#define rtCP_Det_LM_Flicker_ML_TIME_SEC_l (0.02F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S471>/Det_LM_Flicker'
 */
#define rtCP_Det_LM_Flicker_ML_TIME_SEC_lr (0.02F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S475>/signal_sustain'
 */
#define rtCP_signal_sustain_ML_TIME_MSEC (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S476>/hold_then_fade'
 */
#define rtCP_hold_then_fade_ML_TIME_MSEC (20.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_iu
 * Referenced by: '<S495>/Unit Delay'
 */
#define rtCP_UnitDelay_InitialCondition_iu (-0.86F)

/* Computed Parameter: rtCP_Saturation_UpperSat_kp
 * Referenced by: '<S495>/Saturation'
 */
#define rtCP_Saturation_UpperSat_kp    (65535.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_lj
 * Referenced by: '<S495>/Saturation'
 */
#define rtCP_Saturation_LowerSat_lj    (-65535.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S505>/Sustain_wo_reset'
 */
#define rtCP_Sustain_wo_reset_ML_TIME_MSEC (20.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_jy
 * Referenced by: '<S515>/Saturation'
 */
#define rtCP_Saturation_UpperSat_jy    (65535.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_a
 * Referenced by: '<S515>/Saturation'
 */
#define rtCP_Saturation_LowerSat_a     (-65535.0F)

/* Expression: C_NEARZERO
 * Referenced by: '<S516>/C_NEARZERO'
 */
#define rtCP_C_NEARZERO_Value_h        (0.0001F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S516>/Constant'
 */
#define rtCP_Constant_Value_et         (1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_d
 * Referenced by: '<S516>/Gain1'
 */
#define rtCP_Gain1_Gain_d              (2.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S531>/hold_then_fade'
 */
#define rtCP_hold_then_fade_ML_TIME_MSEC_g (20.0F)

/* Computed Parameter: rtCP_Constant_Value_h4
 * Referenced by: '<S533>/Constant'
 */
#define rtCP_Constant_Value_h4         (2.0F)

/* Computed Parameter: rtCP_neg_Gain
 * Referenced by: '<S533>/neg'
 */
#define rtCP_neg_Gain                  (-1.0F)

/* Expression: C_DEG2RAD
 * Referenced by: '<S533>/Deg2Rad'
 */
#define rtCP_Deg2Rad_Gain              (0.017453F)

/* Expression: C_DEG2RAD
 * Referenced by: '<S533>/Deg2Rad1'
 */
#define rtCP_Deg2Rad1_Gain             (0.017453F)

/* Computed Parameter: rtCP_Saturation1_UpperSat
 * Referenced by: '<S533>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat      (100.0F)

/* Computed Parameter: rtCP_Saturation1_LowerSat
 * Referenced by: '<S533>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat      (1.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_a0
 * Referenced by: '<S586>/Unit Delay'
 */
#define rtCP_UnitDelay_InitialCondition_a0 (0.86F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S618>/Chart'
 */
#define rtCP_Chart_ML_TIME_MSEC        (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S629>/Delay_set'
 */
#define rtCP_Delay_set_ML_TIME_MSEC    (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S627>/Trigger_Hold'
 */
#define rtCP_Trigger_Hold_ML_TIME_MSEC (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S634>/Chart'
 */
#define rtCP_Chart_ML_TIME_MSEC_e      (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S642>/Chart'
 */
#define rtCP_Chart_ML_TIME_MSEC_bz     (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S655>/Chart'
 */
#define rtCP_Chart_ML_TIME_MSEC_d      (20.0F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S676>/Mem_LM_high_spd'
 */
#define rtCP_Mem_LM_high_spd_ML_TIME_SEC (0.02F)

/* Computed Parameter: rtCP_Saturation_UpperSat_k4
 * Referenced by: '<S726>/Saturation'
 */
#define rtCP_Saturation_UpperSat_k4    (65535.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_nd
 * Referenced by: '<S726>/Saturation'
 */
#define rtCP_Saturation_LowerSat_nd    (-65535.0F)

/* Computed Parameter: rtCP_k_ovrly_torq_rate_min1_Value_f
 * Referenced by: '<S733>/k_ovrly_torq_rate_min1'
 */
#define rtCP_k_ovrly_torq_rate_min1_Value_f (1000.0F)

/* Computed Parameter: rtCP_k_ovrly_torq_rate_min2_Value_f
 * Referenced by: '<S733>/k_ovrly_torq_rate_min2'
 */
#define rtCP_k_ovrly_torq_rate_min2_Value_f (1000.0F)

/* Computed Parameter: rtCP_Gain2_Gain_c
 * Referenced by: '<S733>/Gain2'
 */
#define rtCP_Gain2_Gain_c              (-1.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S733>/Gain'
 */
#define rtCP_Gain_Gain_n               (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S733>/Gain1'
 */
#define rtCP_Gain1_Gain_k              (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S740>/Trigger Hold'
 */
#define rtCP_TriggerHold_ML_TIME_MSEC_d (20.0F)

/* Expression: C_NEARZERO
 * Referenced by: '<S677>/C_NEARZERO'
 */
#define rtCP_C_NEARZERO_Value_n        (0.0001F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S677>/C_ZERO1'
 */
#define rtCP_C_ZERO1_Value             (0.0F)

/* Computed Parameter: rtCP_Constant_Value_k
 * Referenced by: '<S677>/Constant'
 */
#define rtCP_Constant_Value_k          (10000.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S677>/Constant1'
 */
#define rtCP_Constant1_Value_gv        (1.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S677>/Constant17'
 */
#define rtCP_Constant17_Value          (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_em
 * Referenced by: '<S677>/Constant2'
 */
#define rtCP_Constant2_Value_em        (-10000.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S677>/Constant22'
 */
#define rtCP_Constant22_Value          (1.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S677>/Constant3'
 */
#define rtCP_Constant3_Value_d         (0.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S677>/Constant4'
 */
#define rtCP_Constant4_Value_j         (1.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S677>/Constant5'
 */
#define rtCP_Constant5_Value_e         (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S677>/Constant7'
 */
#define rtCP_Constant7_Value_b         (0.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S677>/ML_TIME_MSEC1'
 */
#define rtCP_ML_TIME_MSEC1_Value       (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S677>/ML_TIME_MSEC4'
 */
#define rtCP_ML_TIME_MSEC4_Value       (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S677>/ML_TIME_MSEC5'
 */
#define rtCP_ML_TIME_MSEC5_Value       (20.0F)

/* Expression: k_ILC_SPA0_LockA1
 * Referenced by: '<S729>/k_ILC_SPA0_LockA1'
 */
#define rtCP_k_ILC_SPA0_LockA1_Value   (2.5F)

/* Expression: k_ILC_rel_LowSpd
 * Referenced by: '<S677>/k_ILC_rel_LowSpd'
 */
#define rtCP_k_ILC_rel_LowSpd_Value    (17.88F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S677>/ML_TIME_SEC'
 */
#define rtCP_ML_TIME_SEC_Value         (0.02F)

/* Expression: k_ILC_A0Range_A1Jmp
 * Referenced by: '<S677>/k_ILC_A0Range_A1Jmp'
 */
#define rtCP_k_ILC_A0Range_A1Jmp_Value (1.0F)

/* Expression: k_ILC_A0Range_A2Jmp
 * Referenced by: '<S677>/k_ILC_A0Range_A2Jmp'
 */
#define rtCP_k_ILC_A0Range_A2Jmp_Value (1.0F)

/* Expression: k_ILC_A1Change_Left
 * Referenced by: '<S677>/k_ILC_A1Change_Left'
 */
#define rtCP_k_ILC_A1Change_Left_Value (0.006F)

/* Expression: k_ILC_A1Change_Rght
 * Referenced by: '<S677>/k_ILC_A1Change_Rght'
 */
#define rtCP_k_ILC_A1Change_Rght_Value (0.006F)

/* Expression: k_ILC_A1Jmp_RateLimit
 * Referenced by: '<S677>/k_ILC_A1Jmp_RateLimit'
 */
#define rtCP_k_ILC_A1Jmp_RateLimit_Value (0.008F)

/* Expression: k_ILC_A1JumpLmt
 * Referenced by: '<S677>/k_ILC_A1JumpLmt'
 */
#define rtCP_k_ILC_A1JumpLmt_Value     (0.004F)

/* Expression: k_ILC_LatSpdInteg_UpLimit
 * Referenced by: '<S677>/k_ILC_LatSpdInteg_UpLimit'
 */
#define rtCP_k_ILC_LatSpdInteg_UpLimit_Value (3.6F)

/* Expression: k_ILC_SP_A1_RateLimit
 * Referenced by: '<S677>/k_ILC_SP_A1_RateLimit1'
 */
#define rtCP_k_ILC_SP_A1_RateLimit1_Value (0.05F)

/* Computed Parameter: rtCP_Gain13_Gain
 * Referenced by: '<S677>/Gain13'
 */
#define rtCP_Gain13_Gain               (0.5F)

/* Expression: C_KPH2MPS
 * Referenced by: '<S677>/KPH2MPS'
 */
#define rtCP_KPH2MPS_Gain              (0.277777791F)

/* Computed Parameter: rtCP_Gain14_Gain
 * Referenced by: '<S677>/Gain14'
 */
#define rtCP_Gain14_Gain               (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_p
 * Referenced by: '<S677>/Gain2'
 */
#define rtCP_Gain2_Gain_p              (2.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_mq
 * Referenced by: '<S840>/Saturation'
 */
#define rtCP_Saturation_UpperSat_mq    (65535.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_b3
 * Referenced by: '<S840>/Saturation'
 */
#define rtCP_Saturation_LowerSat_b3    (-65535.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S853>/Trigger Hold'
 */
#define rtCP_TriggerHold_ML_TIME_MSEC_o3 (20.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S466>/Constant13'
 */
#define rtCP_Constant13_Value_n        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S466>/Constant2'
 */
#define rtCP_Constant2_Value_c         (0.0F)

/* Computed Parameter: rtCP_Constant11_Value_e
 * Referenced by: '<S674>/Constant11'
 */
#define rtCP_Constant11_Value_e        (-8.0F)

/* Computed Parameter: rtCP_Constant14_Value_p
 * Referenced by: '<S674>/Constant14'
 */
#define rtCP_Constant14_Value_p        (8.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S678>/Constant1'
 */
#define rtCP_Constant1_Value_l         (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S678>/Constant4'
 */
#define rtCP_Constant4_Value_d         (0.0F)

/* Expression: C_NEARZERO
 * Referenced by: '<S775>/C_NEARZERO'
 */
#define rtCP_C_NEARZERO_Value_hu       (0.0001F)

/* Expression: C_NEARZERO
 * Referenced by: '<S775>/C_NEARZERO1'
 */
#define rtCP_C_NEARZERO1_Value_p       (0.0001F)

/* Expression: C_NEARZERO
 * Referenced by: '<S775>/C_NEARZERO2'
 */
#define rtCP_C_NEARZERO2_Value         (0.0001F)

/* Computed Parameter: rtCP_Constant_Value_pw
 * Referenced by: '<S775>/Constant'
 */
#define rtCP_Constant_Value_pw         (2.0F)

/* Computed Parameter: rtCP_Constant1_Value_a
 * Referenced by: '<S775>/Constant1'
 */
#define rtCP_Constant1_Value_a         (3.0F)

/* Computed Parameter: rtCP_Constant10_Value_kb
 * Referenced by: '<S775>/Constant10'
 */
#define rtCP_Constant10_Value_kb       (2.0F)

/* Computed Parameter: rtCP_Constant11_Value_a
 * Referenced by: '<S775>/Constant11'
 */
#define rtCP_Constant11_Value_a        (6.0F)

/* Computed Parameter: rtCP_Constant2_Value_g
 * Referenced by: '<S775>/Constant2'
 */
#define rtCP_Constant2_Value_g         (2.0F)

/* Computed Parameter: rtCP_Constant3_Value_g
 * Referenced by: '<S775>/Constant3'
 */
#define rtCP_Constant3_Value_g         (6.0F)

/* Computed Parameter: rtCP_Constant4_Value_b1
 * Referenced by: '<S775>/Constant4'
 */
#define rtCP_Constant4_Value_b1        (2.0F)

/* Computed Parameter: rtCP_Constant5_Value_go
 * Referenced by: '<S775>/Constant5'
 */
#define rtCP_Constant5_Value_go        (3.0F)

/* Computed Parameter: rtCP_Constant6_Value_g
 * Referenced by: '<S775>/Constant6'
 */
#define rtCP_Constant6_Value_g         (2.0F)

/* Computed Parameter: rtCP_Constant7_Value_a
 * Referenced by: '<S775>/Constant7'
 */
#define rtCP_Constant7_Value_a         (6.0F)

/* Computed Parameter: rtCP_Constant8_Value_k
 * Referenced by: '<S775>/Constant8'
 */
#define rtCP_Constant8_Value_k         (2.0F)

/* Computed Parameter: rtCP_Constant9_Value_p1
 * Referenced by: '<S775>/Constant9'
 */
#define rtCP_Constant9_Value_p1        (3.0F)

/* Expression: k_ILC_HlfLnWdth_Time
 * Referenced by: '<S775>/k_ILC_HlfLnWdth_Time'
 */
#define rtCP_k_ILC_HlfLnWdth_Time_Value (3.5F)

/* Expression: k_ILC_HlfLnWdth_Time
 * Referenced by: '<S775>/k_ILC_HlfLnWdth_Time1'
 */
#define rtCP_k_ILC_HlfLnWdth_Time1_Value (3.5F)

/* Expression: k_ILC_HlfLnWdth_Time
 * Referenced by: '<S775>/k_ILC_HlfLnWdth_Time2'
 */
#define rtCP_k_ILC_HlfLnWdth_Time2_Value (3.5F)

/* Expression: k_ILC_maxCoeffLW_Lft
 * Referenced by: '<S775>/k_ILC_maxCoeffLW_Lft'
 */
#define rtCP_k_ILC_maxCoeffLW_Lft_Value (1.05F)

/* Expression: k_ILC_maxCoeffLW_Rght
 * Referenced by: '<S775>/k_ILC_maxCoeffLW_Rght'
 */
#define rtCP_k_ILC_maxCoeffLW_Rght_Value (1.05F)

/* Expression: k_ILC_tMinEndPoint
 * Referenced by: '<S775>/k_ILC_tMinEndPoint'
 */
#define rtCP_k_ILC_tMinEndPoint_Value  (4.0F)

/* Expression: k_ILC_tMinEndPoint
 * Referenced by: '<S775>/k_ILC_tMinEndPoint1'
 */
#define rtCP_k_ILC_tMinEndPoint1_Value (4.0F)

/* Expression: k_ILC_tMinEndPoint
 * Referenced by: '<S775>/k_ILC_tMinEndPoint2'
 */
#define rtCP_k_ILC_tMinEndPoint2_Value (4.0F)

/* Expression: k_ILC_x_f_max
 * Referenced by: '<S775>/k_ILC_x_f_max'
 */
#define rtCP_k_ILC_x_f_max_Value       (300.0F)

/* Expression: k_ILC_x_f_max
 * Referenced by: '<S775>/k_ILC_x_f_max1'
 */
#define rtCP_k_ILC_x_f_max1_Value      (300.0F)

/* Expression: k_ILC_x_f_max
 * Referenced by: '<S775>/k_ILC_x_f_max2'
 */
#define rtCP_k_ILC_x_f_max2_Value      (300.0F)

/* Expression: k_ILC_x_f_min
 * Referenced by: '<S775>/k_ILC_x_f_min'
 */
#define rtCP_k_ILC_x_f_min_Value       (20.0F)

/* Expression: k_ILC_x_f_min
 * Referenced by: '<S775>/k_ILC_x_f_min1'
 */
#define rtCP_k_ILC_x_f_min1_Value      (20.0F)

/* Expression: k_ILC_x_f_min
 * Referenced by: '<S775>/k_ILC_x_f_min2'
 */
#define rtCP_k_ILC_x_f_min2_Value      (20.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S776>/Constant6'
 */
#define rtCP_Constant6_Value_m         (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S776>/Constant7'
 */
#define rtCP_Constant7_Value_bb        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S776>/Constant8'
 */
#define rtCP_Constant8_Value_a         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ha
 * Referenced by: '<S776>/Constant'
 */
#define rtCP_Constant_Value_ha         (3.0F)

/* Computed Parameter: rtCP_Constant1_Value_o3
 * Referenced by: '<S776>/Constant1'
 */
#define rtCP_Constant1_Value_o3        (4.0F)

/* Computed Parameter: rtCP_Constant2_Value_o
 * Referenced by: '<S776>/Constant2'
 */
#define rtCP_Constant2_Value_o         (5.0F)

/* Computed Parameter: rtCP_Constant3_Value_p
 * Referenced by: '<S776>/Constant3'
 */
#define rtCP_Constant3_Value_p         (6.0F)

/* Computed Parameter: rtCP_Constant4_Value_nc
 * Referenced by: '<S776>/Constant4'
 */
#define rtCP_Constant4_Value_nc        (12.0F)

/* Computed Parameter: rtCP_Constant5_Value_f
 * Referenced by: '<S776>/Constant5'
 */
#define rtCP_Constant5_Value_f         (20.0F)

/* Computed Parameter: rtCP_Constant2_Value_f
 * Referenced by: '<S781>/Constant2'
 */
#define rtCP_Constant2_Value_f         (0.0F)

/* Computed Parameter: rtCP_Epsilon_Value
 * Referenced by: '<S781>/Epsilon'
 */
#define rtCP_Epsilon_Value             (0.017453F)

/* Computed Parameter: rtCP_Constant2_Value_i4
 * Referenced by: '<S782>/Constant2'
 */
#define rtCP_Constant2_Value_i4        (0.0F)

/* Computed Parameter: rtCP_Epsilon_Value_i
 * Referenced by: '<S782>/Epsilon'
 */
#define rtCP_Epsilon_Value_i           (0.017453F)

/* Computed Parameter: rtCP_Constant2_Value_b
 * Referenced by: '<S783>/Constant2'
 */
#define rtCP_Constant2_Value_b         (0.0F)

/* Computed Parameter: rtCP_Epsilon_Value_b
 * Referenced by: '<S783>/Epsilon'
 */
#define rtCP_Epsilon_Value_b           (0.017453F)

/* Expression: C_NEARZERO
 * Referenced by: '<S763>/C_NEARZERO'
 */
#define rtCP_C_NEARZERO_Value_a        (0.0001F)

/* Computed Parameter: rtCP_Constant10_Value_e
 * Referenced by: '<S763>/Constant10'
 */
#define rtCP_Constant10_Value_e        (-10000.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S763>/Constant22'
 */
#define rtCP_Constant22_Value_m        (1.0F)

/* Computed Parameter: rtCP_Constant7_Value_c
 * Referenced by: '<S763>/Constant7'
 */
#define rtCP_Constant7_Value_c         (10000.0F)

/* Expression: k_ILC_maxCoeffXRef_P1
 * Referenced by: '<S786>/k_ILC_maxCoeffXRef_P1'
 */
#define rtCP_k_ILC_maxCoeffXRef_P1_Value (0.3F)

/* Expression: k_ILC_maxCoeffXRef_P2
 * Referenced by: '<S786>/k_ILC_maxCoeffXRef_P2'
 */
#define rtCP_k_ILC_maxCoeffXRef_P2_Value (0.4F)

/* Expression: k_ILC_minCoeffXRef_P2
 * Referenced by: '<S786>/k_ILC_minCoeffXRef_P2'
 */
#define rtCP_k_ILC_minCoeffXRef_P2_Value (0.15F)

/* Computed Parameter: rtCP_Constant_Value_g
 * Referenced by: '<S787>/Constant'
 */
#define rtCP_Constant_Value_g          (2.0F)

/* Computed Parameter: rtCP_Constant1_Value_ow
 * Referenced by: '<S787>/Constant1'
 */
#define rtCP_Constant1_Value_ow        (3.0F)

/* Computed Parameter: rtCP_Constant10_Value_h
 * Referenced by: '<S787>/Constant10'
 */
#define rtCP_Constant10_Value_h        (24.0F)

/* Computed Parameter: rtCP_Constant11_Value_m
 * Referenced by: '<S787>/Constant11'
 */
#define rtCP_Constant11_Value_m        (60.0F)

/* Computed Parameter: rtCP_Constant2_Value_h
 * Referenced by: '<S787>/Constant2'
 */
#define rtCP_Constant2_Value_h         (4.0F)

/* Computed Parameter: rtCP_Constant3_Value_j
 * Referenced by: '<S787>/Constant3'
 */
#define rtCP_Constant3_Value_j         (5.0F)

/* Computed Parameter: rtCP_Constant4_Value_g
 * Referenced by: '<S787>/Constant4'
 */
#define rtCP_Constant4_Value_g         (2.0F)

/* Computed Parameter: rtCP_Constant5_Value_fd
 * Referenced by: '<S787>/Constant5'
 */
#define rtCP_Constant5_Value_fd        (6.0F)

/* Computed Parameter: rtCP_Constant6_Value_jq
 * Referenced by: '<S787>/Constant6'
 */
#define rtCP_Constant6_Value_jq        (12.0F)

/* Computed Parameter: rtCP_Constant7_Value_e
 * Referenced by: '<S787>/Constant7'
 */
#define rtCP_Constant7_Value_e         (20.0F)

/* Computed Parameter: rtCP_Constant9_Value_n
 * Referenced by: '<S787>/Constant9'
 */
#define rtCP_Constant9_Value_n         (6.0F)

/* Expression: k_ILC_rel_LowSpd
 * Referenced by: '<S678>/k_ILC_rel_LowSpd'
 */
#define rtCP_k_ILC_rel_LowSpd_Value_p  (17.88F)

/* Expression: k_ILC_maxLnWdth_m
 * Referenced by: '<S788>/k_ILC_maxLnWdth_m'
 */
#define rtCP_k_ILC_maxLnWdth_m_Value   (4.0F)

/* Expression: k_ILC_minLnWdth_m
 * Referenced by: '<S788>/k_ILC_minLnWdth_m'
 */
#define rtCP_k_ILC_minLnWdth_m_Value   (2.7F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S766>/ML_TIME_MSEC6'
 */
#define rtCP_ML_TIME_MSEC6_Value_m     (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S766>/ML_TIME_MSEC9'
 */
#define rtCP_ML_TIME_MSEC9_Value       (20.0F)

/* Computed Parameter: rtCP_Constant_Value_ai
 * Referenced by: '<S799>/Constant'
 */
#define rtCP_Constant_Value_ai         (2.0F)

/* Computed Parameter: rtCP_Constant1_Value_pu
 * Referenced by: '<S799>/Constant1'
 */
#define rtCP_Constant1_Value_pu        (6.0F)

/* Computed Parameter: rtCP_Constant2_Value_gn
 * Referenced by: '<S799>/Constant2'
 */
#define rtCP_Constant2_Value_gn        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_kb
 * Referenced by: '<S800>/Constant'
 */
#define rtCP_Constant_Value_kb         (2.0F)

/* Computed Parameter: rtCP_Constant1_Value_d
 * Referenced by: '<S800>/Constant1'
 */
#define rtCP_Constant1_Value_d         (6.0F)

/* Computed Parameter: rtCP_Constant2_Value_c5
 * Referenced by: '<S800>/Constant2'
 */
#define rtCP_Constant2_Value_c5        (0.5F)

/* Expression: k_ILC_A0Range_A1Flt
 * Referenced by: '<S766>/k_ILC_A0Range_A1Flt'
 */
#define rtCP_k_ILC_A0Range_A1Flt_Value (2.0F)

/* Expression: k_ILC_A0Range_A2Flt
 * Referenced by: '<S766>/k_ILC_A0Range_A2Flt'
 */
#define rtCP_k_ILC_A0Range_A2Flt_Value (2.0F)

/* Expression: k_ILC_A1SrcAvdJmp_RateLimit
 * Referenced by: '<S766>/k_ILC_A1SrcAvdJmp_RateLimit'
 */
#define rtCP_k_ILC_A1SrcAvdJmp_RateLimit_Value (0.035F)

/* Expression: k_ILC_A1Src_RateLimit
 * Referenced by: '<S766>/k_ILC_A1Src_RateLimit'
 */
#define rtCP_k_ILC_A1Src_RateLimit_Value (0.035F)

/* Expression: k_ILC_A2SrcAvdJmp_RateLimit
 * Referenced by: '<S766>/k_ILC_A2SrcAvdJmp_RateLimit'
 */
#define rtCP_k_ILC_A2SrcAvdJmp_RateLimit_Value (1.0F)

/* Expression: k_ILC_A2Src_RateLimit
 * Referenced by: '<S766>/k_ILC_A2Src_RateLimit'
 */
#define rtCP_k_ILC_A2Src_RateLimit_Value (1.0F)

/* Expression: k_ILC_SmpTime
 * Referenced by: '<S766>/k_ILC_SmpTime'
 */
#define rtCP_k_ILC_SmpTime_Value       (0.02F)

/* Expression: k_ILC_SmpTime
 * Referenced by: '<S766>/k_ILC_SmpTime1'
 */
#define rtCP_k_ILC_SmpTime1_Value      (0.02F)

/* Expression: k_ILC_SmpTime
 * Referenced by: '<S678>/k_ILC_SmpTim'
 */
#define rtCP_k_ILC_SmpTim_Value        (0.02F)

/* Expression: k_ILC_YawRt_Drctn_ISO
 * Referenced by: '<S678>/k_ILC_YawRt_Drctn_ISO'
 */
#define rtCP_k_ILC_YawRt_Drctn_ISO_Value (1.0F)

/* Expression: k_ILC_minDrvDis
 * Referenced by: '<S678>/k_ILC_minDrvDis'
 */
#define rtCP_k_ILC_minDrvDis_Value     (0.0F)

/* Computed Parameter: rtCP_Constant_Value_o
 * Referenced by: '<S830>/Constant'
 */
#define rtCP_Constant_Value_o          (3.0F)

/* Computed Parameter: rtCP_Constant2_Value_d
 * Referenced by: '<S824>/Constant2'
 */
#define rtCP_Constant2_Value_d         (10.0F)

/* Computed Parameter: rtCP_Constant3_Value_c
 * Referenced by: '<S824>/Constant3'
 */
#define rtCP_Constant3_Value_c         (10.0F)

/* Expression: k_ILC_SP_A0_RateLimit
 * Referenced by: '<S824>/k_ILC_SP_A0_RateLimit1'
 */
#define rtCP_k_ILC_SP_A0_RateLimit1_Value (1000.0F)

/* Expression: k_ILC_SP_A1_RateLimit
 * Referenced by: '<S824>/k_ILC_SP_A1_RateLimit'
 */
#define rtCP_k_ILC_SP_A1_RateLimit_Value (0.05F)

/* Expression: k_LCK_SP_A0_RateLimit
 * Referenced by: '<S824>/k_LCK_SP_A0_RateLimit'
 */
#define rtCP_k_LCK_SP_A0_RateLimit_Value (1000.0F)

/* Expression: k_LCK_SP_A1_RateLimit
 * Referenced by: '<S824>/k_LCK_SP_A1_RateLimit'
 */
#define rtCP_k_LCK_SP_A1_RateLimit_Value (0.1F)

/* Computed Parameter: rtCP_Constant_Value_o1
 * Referenced by: '<S837>/Constant'
 */
#define rtCP_Constant_Value_o1         (0.0F)

/* Expression: k_LBS_LaneBiasOffsetRightComp
 * Referenced by: '<S836>/Constant2'
 */
#define rtCP_Constant2_Value_j         (1.0F)

/* Expression: k_LBS_LaneBiasOffsetLeftComp
 * Referenced by: '<S836>/Constant3'
 */
#define rtCP_Constant3_Value_h         (1.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S836>/Constant8'
 */
#define rtCP_Constant8_Value_kd        (0.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S827>/ML_TIME_MSEC'
 */
#define rtCP_ML_TIME_MSEC_Value_l      (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S827>/ML_TIME_MSEC2'
 */
#define rtCP_ML_TIME_MSEC2_Value_h     (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S827>/ML_TIME_MSEC3'
 */
#define rtCP_ML_TIME_MSEC3_Value_f     (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S827>/ML_TIME_MSEC4'
 */
#define rtCP_ML_TIME_MSEC4_Value_l     (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S827>/ML_TIME_MSEC5'
 */
#define rtCP_ML_TIME_MSEC5_Value_c     (20.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S827>/ML_TIME_MSEC1'
 */
#define rtCP_ML_TIME_MSEC1_Value_b     (20.0F)

/* Computed Parameter: rtCP_k_SP_A1_Bias_Value
 * Referenced by: '<S827>/k_SP_A1_Bias'
 */
#define rtCP_k_SP_A1_Bias_Value        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_aj
 * Referenced by: '<S828>/Constant1'
 */
#define rtCP_Constant1_Value_aj        (5000.0F)

/* Expression: k_LCK_POHdgThrdDeg
 * Referenced by: '<S855>/Constant'
 */
#define rtCP_Constant_Value_j          (5.0F)

/* Computed Parameter: rtCP_Constant2_Value_gy
 * Referenced by: '<S858>/Constant2'
 */
#define rtCP_Constant2_Value_gy        (0.0F)

/* Computed Parameter: rtCP_Epsilon_Value_f
 * Referenced by: '<S858>/Epsilon'
 */
#define rtCP_Epsilon_Value_f           (0.001F)

/* Computed Parameter: rtCP_Constant2_Value_p
 * Referenced by: '<S859>/Constant2'
 */
#define rtCP_Constant2_Value_p         (0.0F)

/* Computed Parameter: rtCP_Epsilon_Value_j
 * Referenced by: '<S859>/Epsilon'
 */
#define rtCP_Epsilon_Value_j           (0.001F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S683>/Constant'
 */
#define rtCP_Constant_Value_lj         (1.0F)

/* Computed Parameter: rtCP_Gain_Gain_j
 * Referenced by: '<S466>/Gain'
 */
#define rtCP_Gain_Gain_j               (1.0F)

/* Computed Parameter: rtCP_Gain39_Gain
 * Referenced by: '<S466>/Gain39'
 */
#define rtCP_Gain39_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain38_Gain
 * Referenced by: '<S466>/Gain38'
 */
#define rtCP_Gain38_Gain               (1.0F)

/* Expression: C_KPH2MPS
 * Referenced by: '<S678>/KPH2MPS'
 */
#define rtCP_KPH2MPS_Gain_a            (0.277777791F)

/* Computed Parameter: rtCP_Gain_Gain_dv
 * Referenced by: '<S766>/Gain'
 */
#define rtCP_Gain_Gain_dv              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_dk
 * Referenced by: '<S788>/Gain1'
 */
#define rtCP_Gain1_Gain_dk             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_ez
 * Referenced by: '<S466>/Gain2'
 */
#define rtCP_Gain2_Gain_ez             (1.0F)

/* Computed Parameter: rtCP_Gain14_Gain_a
 * Referenced by: '<S766>/Gain14'
 */
#define rtCP_Gain14_Gain_a             (0.5F)

/* Computed Parameter: rtCP_Gain4_Gain_a
 * Referenced by: '<S763>/Gain4'
 */
#define rtCP_Gain4_Gain_a              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_nb
 * Referenced by: '<S787>/Gain'
 */
#define rtCP_Gain_Gain_nb              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_lt
 * Referenced by: '<S787>/Gain1'
 */
#define rtCP_Gain1_Gain_lt             (0.166666672F)

/* Computed Parameter: rtCP_Gain1_Gain_lg
 * Referenced by: '<S466>/Gain1'
 */
#define rtCP_Gain1_Gain_lg             (1.0F)

/* Computed Parameter: rtCP_Gain3_Gain_k
 * Referenced by: '<S466>/Gain3'
 */
#define rtCP_Gain3_Gain_k              (1.0F)

/* Computed Parameter: rtCP_Gain34_Gain
 * Referenced by: '<S466>/Gain34'
 */
#define rtCP_Gain34_Gain               (1.0F)

/* Expression: k_SPP_clearance_RE
 * Referenced by: '<S684>/k_SPP_clearance_RE'
 */
#define rtCP_k_SPP_clearance_RE_Value  (0.0F)

/* Expression: k_LCK_Valid_Range_Remain_Tm_s
 * Referenced by: '<S819>/k_LCK_Valid_Range_Remain_Tm_s'
 */
#define rtCP_k_LCK_Valid_Range_Remain_Tm_s_Value (0.1F)

/* Expression: k_LCK_Valid_Range_Remain_Tm_s
 * Referenced by: '<S818>/k_LCK_Valid_Range_Remain_Tm_s'
 */
#define rtCP_k_LCK_Valid_Range_Remain_Tm_s_Value_c (0.1F)

/* Expression: k_LCK_Valid_Range_Remain_Tm_s
 * Referenced by: '<S690>/k_LCK_Valid_Range_Remain_Tm_s'
 */
#define rtCP_k_LCK_Valid_Range_Remain_Tm_s_Value_j (0.1F)

/* Expression: k_SPP_clearance_VisBarr
 * Referenced by: '<S684>/k_SPP_clearance_VisBarr'
 */
#define rtCP_k_SPP_clearance_VisBarr_Value (0.0F)

/* Expression: k_LCK_Valid_Range_Remain_Tm_s
 * Referenced by: '<S688>/k_LCK_Valid_Range_Remain_Tm_s'
 */
#define rtCP_k_LCK_Valid_Range_Remain_Tm_s_Value_k (0.1F)

/* Expression: k_SPP_clearance_FusGdr
 * Referenced by: '<S684>/k_SPP_clearance_FusGdr'
 */
#define rtCP_k_SPP_clearance_FusGdr_Value (0.0F)

/* Expression: k_LCK_Valid_Range_Remain_Tm_s
 * Referenced by: '<S689>/k_LCK_Valid_Range_Remain_Tm_s'
 */
#define rtCP_k_LCK_Valid_Range_Remain_Tm_s_Value_f (0.1F)

/* Expression: k_SPP_clearance_RE
 * Referenced by: '<S687>/k_SPP_clearance_RE'
 */
#define rtCP_k_SPP_clearance_RE_Value_k (0.0F)

/* Expression: k_LCK_Valid_Range_Remain_Tm_s
 * Referenced by: '<S699>/k_LCK_Valid_Range_Remain_Tm_s'
 */
#define rtCP_k_LCK_Valid_Range_Remain_Tm_s_Value_n (0.1F)

/* Expression: k_SPP_clearance_VisBarr
 * Referenced by: '<S687>/k_SPP_clearance_VisBarr'
 */
#define rtCP_k_SPP_clearance_VisBarr_Value_j (0.0F)

/* Expression: k_LCK_Valid_Range_Remain_Tm_s
 * Referenced by: '<S697>/k_LCK_Valid_Range_Remain_Tm_s'
 */
#define rtCP_k_LCK_Valid_Range_Remain_Tm_s_Value_o (0.1F)

/* Expression: k_SPP_clearance_FusGdr
 * Referenced by: '<S687>/k_SPP_clearance_FusGdr'
 */
#define rtCP_k_SPP_clearance_FusGdr_Value_m (0.0F)

/* Expression: k_LCK_Valid_Range_Remain_Tm_s
 * Referenced by: '<S698>/k_LCK_Valid_Range_Remain_Tm_s'
 */
#define rtCP_k_LCK_Valid_Range_Remain_Tm_s_Value_d (0.1F)

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER1_Value
 * Referenced by: '<S685>/POLY_TYPE_LM_BARRIER1'
 */
#define rtCP_POLY_TYPE_LM_BARRIER1_Value (1.2F)

/* Computed Parameter: rtCP_POLY_TYPE_FUSED_BARRIER1_Value
 * Referenced by: '<S685>/POLY_TYPE_FUSED_BARRIER1'
 */
#define rtCP_POLY_TYPE_FUSED_BARRIER1_Value (2.5F)

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER1_Value_j
 * Referenced by: '<S686>/POLY_TYPE_LM_BARRIER1'
 */
#define rtCP_POLY_TYPE_LM_BARRIER1_Value_j (1.2F)

/* Computed Parameter: rtCP_POLY_TYPE_FUSED_BARRIER1_Value_p
 * Referenced by: '<S686>/POLY_TYPE_FUSED_BARRIER1'
 */
#define rtCP_POLY_TYPE_FUSED_BARRIER1_Value_p (2.5F)

/* Expression: C_KPH2MPS
 * Referenced by: '<S682>/Gain12'
 */
#define rtCP_Gain12_Gain               (0.277777791F)

/* Expression: k_SPP_POOnly_status_low
 * Referenced by: '<S855>/TJA_SP_CONF_MEDHIGH2'
 */
#define rtCP_TJA_SP_CONF_MEDHIGH2_Value (4.0F)

/* Expression: k_SPP_POOnly_status_high
 * Referenced by: '<S855>/TJA_SP_CONF_MEDHIGH1'
 */
#define rtCP_TJA_SP_CONF_MEDHIGH1_Value (4.0F)

/* Expression: k_LCK_POMaxLatPos_m
 * Referenced by: '<S855>/k_LCK_POMaxLatPos_m'
 */
#define rtCP_k_LCK_POMaxLatPos_m_Value (2.0F)

/* Expression: k_LCK_POMaxRange_m
 * Referenced by: '<S855>/k_LCK_POMaxRange_m'
 */
#define rtCP_k_LCK_POMaxRange_m_Value  (70.0F)

/* Computed Parameter: rtCP_Gain14_Gain_c
 * Referenced by: '<S466>/Gain14'
 */
#define rtCP_Gain14_Gain_c             (1.0F)

/* Computed Parameter: rtCP_Gain15_Gain
 * Referenced by: '<S466>/Gain15'
 */
#define rtCP_Gain15_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain_Gain_c
 * Referenced by: '<S855>/Gain'
 */
#define rtCP_Gain_Gain_c               (2.0F)

/* Computed Parameter: rtCP_Gain16_Gain
 * Referenced by: '<S466>/Gain16'
 */
#define rtCP_Gain16_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_bv
 * Referenced by: '<S855>/Gain1'
 */
#define rtCP_Gain1_Gain_bv             (3.0F)

/* Computed Parameter: rtCP_Gain2_Gain_f5
 * Referenced by: '<S855>/Gain2'
 */
#define rtCP_Gain2_Gain_f5             (57.3248405F)

/* Computed Parameter: rtCP_Gain12_Gain_b
 * Referenced by: '<S466>/Gain12'
 */
#define rtCP_Gain12_Gain_b             (1.0F)

/* Computed Parameter: rtCP_Gain21_Gain
 * Referenced by: '<S466>/Gain21'
 */
#define rtCP_Gain21_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain25_Gain
 * Referenced by: '<S466>/Gain25'
 */
#define rtCP_Gain25_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain26_Gain
 * Referenced by: '<S466>/Gain26'
 */
#define rtCP_Gain26_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain27_Gain
 * Referenced by: '<S466>/Gain27'
 */
#define rtCP_Gain27_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain28_Gain
 * Referenced by: '<S466>/Gain28'
 */
#define rtCP_Gain28_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain4_Gain_h
 * Referenced by: '<S466>/Gain4'
 */
#define rtCP_Gain4_Gain_h              (1.0F)

/* Computed Parameter: rtCP_Gain5_Gain
 * Referenced by: '<S466>/Gain5'
 */
#define rtCP_Gain5_Gain                (1.0F)

/* Computed Parameter: rtCP_Gain6_Gain
 * Referenced by: '<S466>/Gain6'
 */
#define rtCP_Gain6_Gain                (1.0F)

/* Computed Parameter: rtCP_Gain7_Gain
 * Referenced by: '<S466>/Gain7'
 */
#define rtCP_Gain7_Gain                (1.0F)

/* Computed Parameter: rtCP_Gain8_Gain
 * Referenced by: '<S466>/Gain8'
 */
#define rtCP_Gain8_Gain                (1.0F)

/* Computed Parameter: rtCP_Gain9_Gain
 * Referenced by: '<S466>/Gain9'
 */
#define rtCP_Gain9_Gain                (1.0F)

/* Computed Parameter: rtCP_Gain10_Gain
 * Referenced by: '<S466>/Gain10'
 */
#define rtCP_Gain10_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain11_Gain
 * Referenced by: '<S466>/Gain11'
 */
#define rtCP_Gain11_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain29_Gain
 * Referenced by: '<S466>/Gain29'
 */
#define rtCP_Gain29_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain30_Gain
 * Referenced by: '<S466>/Gain30'
 */
#define rtCP_Gain30_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain13_Gain_m
 * Referenced by: '<S466>/Gain13'
 */
#define rtCP_Gain13_Gain_m             (1.0F)

/* Computed Parameter: rtCP_Gain35_Gain
 * Referenced by: '<S466>/Gain35'
 */
#define rtCP_Gain35_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain32_Gain
 * Referenced by: '<S466>/Gain32'
 */
#define rtCP_Gain32_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain33_Gain
 * Referenced by: '<S466>/Gain33'
 */
#define rtCP_Gain33_Gain               (1.0F)

/* Computed Parameter: rtCP_Gain4_Gain_n
 * Referenced by: '<S766>/Gain4'
 */
#define rtCP_Gain4_Gain_n              (0.5F)

/* Computed Parameter: rtCP_Gain3_Gain_c
 * Referenced by: '<S766>/Gain3'
 */
#define rtCP_Gain3_Gain_c              (0.5F)

/* Computed Parameter: rtCP_Gain13_Gain_h
 * Referenced by: '<S766>/Gain13'
 */
#define rtCP_Gain13_Gain_h             (0.5F)

/* Computed Parameter: rtCP_flip_polarity_Gain
 * Referenced by: '<S678>/flip_polarity'
 */
#define rtCP_flip_polarity_Gain        (-1.0F)

/* Computed Parameter: rtCP_KPH2MPS3_Gain
 * Referenced by: '<S766>/KPH2MPS3'
 */
#define rtCP_KPH2MPS3_Gain             (-1.0F)

/* Expression: C_DEG2RAD
 * Referenced by: '<S766>/KPH2MPS4'
 */
#define rtCP_KPH2MPS4_Gain             (0.017453F)

/* Computed Parameter: rtCP_Gain2_Gain_gf
 * Referenced by: '<S766>/Gain2'
 */
#define rtCP_Gain2_Gain_gf             (0.5F)

/* Computed Parameter: rtCP_KPH2MPS1_Gain
 * Referenced by: '<S766>/KPH2MPS1'
 */
#define rtCP_KPH2MPS1_Gain             (-1.0F)

/* Expression: C_DEG2RAD
 * Referenced by: '<S766>/KPH2MPS2'
 */
#define rtCP_KPH2MPS2_Gain             (0.017453F)

/* Computed Parameter: rtCP_Gain1_Gain_cd
 * Referenced by: '<S766>/Gain1'
 */
#define rtCP_Gain1_Gain_cd             (0.5F)

/* Computed Parameter: rtCP_Constant_Value_mp
 * Referenced by: '<S434>/Constant'
 */
#define rtCP_Constant_Value_mp         (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_ct
 * Referenced by: '<S434>/Constant2'
 */
#define rtCP_Constant2_Value_ct        (-1.0F)

/* Computed Parameter: rtCP_Constant2_Value_pe
 * Referenced by: '<S439>/Constant2'
 */
#define rtCP_Constant2_Value_pe        (0.5F)

/* Computed Parameter: rtCP_Constant3_Value_m
 * Referenced by: '<S439>/Constant3'
 */
#define rtCP_Constant3_Value_m         (0.5F)

/* Computed Parameter: rtCP_Constant2_Value_cd
 * Referenced by: '<S440>/Constant2'
 */
#define rtCP_Constant2_Value_cd        (0.5F)

/* Computed Parameter: rtCP_Constant3_Value_l
 * Referenced by: '<S440>/Constant3'
 */
#define rtCP_Constant3_Value_l         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_nn
 * Referenced by: '<S441>/Constant'
 */
#define rtCP_Constant_Value_nn         (2.5F)

/* Computed Parameter: rtCP_Constant_Value_en
 * Referenced by: '<S442>/Constant'
 */
#define rtCP_Constant_Value_en         (2.5F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant16'
 */
#define rtCP_Constant16_Value          (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant18'
 */
#define rtCP_Constant18_Value_b        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant20'
 */
#define rtCP_Constant20_Value          (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant24'
 */
#define rtCP_Constant24_Value          (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant26'
 */
#define rtCP_Constant26_Value          (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant28'
 */
#define rtCP_Constant28_Value          (0.0F)

/* Expression: k_EP_sfconf_VH_thold
 * Referenced by: '<S443>/k_sfconf_VH_thold'
 */
#define rtCP_k_sfconf_VH_thold_Value   (0.0F)

/* Expression: k_EP_sfconf_hi_thold
 * Referenced by: '<S443>/k_sfconf_hi_thold'
 */
#define rtCP_k_sfconf_hi_thold_Value   (0.0F)

/* Expression: k_EP_sfconf_VH_thold
 * Referenced by: '<S444>/k_sfconf_VH_thold'
 */
#define rtCP_k_sfconf_VH_thold_Value_c (0.0F)

/* Expression: k_EP_sfconf_hi_thold
 * Referenced by: '<S444>/k_sfconf_hi_thold'
 */
#define rtCP_k_sfconf_hi_thold_Value_g (0.0F)

/* Expression: k_EP_sfconf_VH_thold
 * Referenced by: '<S445>/k_sfconf_VH_thold'
 */
#define rtCP_k_sfconf_VH_thold_Value_cy (0.0F)

/* Expression: k_EP_sfconf_hi_thold
 * Referenced by: '<S445>/k_sfconf_hi_thold'
 */
#define rtCP_k_sfconf_hi_thold_Value_h (0.0F)

/* Expression: k_EP_sfconf_VH_thold
 * Referenced by: '<S447>/k_sfconf_VH_thold'
 */
#define rtCP_k_sfconf_VH_thold_Value_o (0.0F)

/* Expression: k_EP_sfconf_hi_thold
 * Referenced by: '<S447>/k_sfconf_hi_thold'
 */
#define rtCP_k_sfconf_hi_thold_Value_hg (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant1'
 */
#define rtCP_Constant1_Value_f         (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant11'
 */
#define rtCP_Constant11_Value_b        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant13'
 */
#define rtCP_Constant13_Value_h        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant32'
 */
#define rtCP_Constant32_Value          (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant5'
 */
#define rtCP_Constant5_Value_n         (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S436>/Constant7'
 */
#define rtCP_Constant7_Value_f         (0.0F)

/* Expression: C_NEARZERO
 * Referenced by: '<S454>/C_NEARZERO'
 */
#define rtCP_C_NEARZERO_Value_b        (0.0001F)

/* Computed Parameter: rtCP_C_NEARZERO_1_Value
 * Referenced by: '<S454>/C_NEARZERO_1'
 */
#define rtCP_C_NEARZERO_1_Value        (1.0E-5F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S454>/Constant'
 */
#define rtCP_Constant_Value_h3         (1.0F)

/* Expression: k_simlmedgehigh
 * Referenced by: '<S437>/Constant'
 */
#define rtCP_Constant_Value_af         (2.0F)

/* Expression: k_simlmedgemed
 * Referenced by: '<S437>/Constant1'
 */
#define rtCP_Constant1_Value_jj        (5.5F)

/* Expression: k_simlmedgehigh_hyst
 * Referenced by: '<S437>/Constant3'
 */
#define rtCP_Constant3_Value_gg        (3.0F)

/* Expression: k_simlmedgemed_hyst
 * Referenced by: '<S437>/Constant4'
 */
#define rtCP_Constant4_Value_f         (6.5F)

/* Expression: k_simflagthreshold
 * Referenced by: '<S437>/Constant6'
 */
#define rtCP_Constant6_Value_l         (1.3F)

/* Expression: k_LM_disable_yaw_high_thresh
 * Referenced by: '<S469>/k_LM_disable_yaw_high_thresh'
 */
#define rtCP_k_LM_disable_yaw_high_thresh_Value (5.0F)

/* Expression: k_SPEED_MIN
 * Referenced by: '<S469>/k_SPEED_MIN'
 */
#define rtCP_k_SPEED_MIN_Value         (1.0F)

/* Expression: k_LM_disable_yaw_high_thresh
 * Referenced by: '<S470>/k_LM_disable_yaw_high_thresh'
 */
#define rtCP_k_LM_disable_yaw_high_thresh_Value_a (5.0F)

/* Expression: k_SPEED_MIN
 * Referenced by: '<S470>/k_SPEED_MIN'
 */
#define rtCP_k_SPEED_MIN_Value_i       (1.0F)

/* Expression: k_LM_disable_yaw_high_thresh
 * Referenced by: '<S471>/k_LM_disable_yaw_high_thresh'
 */
#define rtCP_k_LM_disable_yaw_high_thresh_Value_l (5.0F)

/* Expression: k_SPEED_MIN
 * Referenced by: '<S471>/k_SPEED_MIN'
 */
#define rtCP_k_SPEED_MIN_Value_n       (1.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S476>/Constant'
 */
#define rtCP_Constant_Value_g4         (0.0F)

/* Computed Parameter: rtCP_k_abs_posn_fade_gain_Value
 * Referenced by: '<S476>/k_abs_posn_fade_gain'
 */
#define rtCP_k_abs_posn_fade_gain_Value (0.95F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S477>/Constant'
 */
#define rtCP_Constant_Value_pg         (0.0F)

/* Computed Parameter: rtCP_k_abs_posn_fade_gain_Value_l
 * Referenced by: '<S477>/k_abs_posn_fade_gain'
 */
#define rtCP_k_abs_posn_fade_gain_Value_l (0.95F)

/* Computed Parameter: rtCP_Constant_Value_ny
 * Referenced by: '<S478>/Constant'
 */
#define rtCP_Constant_Value_ny         (2.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S479>/Constant'
 */
#define rtCP_Constant_Value_fj         (0.0F)

/* Expression: k_ME_MAX_LANE_WIDTH
 * Referenced by: '<S480>/const'
 */
#define rtCP_const_Value               (8.0F)

/* Expression: k_assumed_lane_width_m
 * Referenced by: '<S480>/k_assumed_lane_width_m'
 */
#define rtCP_k_assumed_lane_width_m_Value (3.5F)

/* Expression: k_assumed_lane_width_m
 * Referenced by: '<S480>/k_assumed_lane_width_m1'
 */
#define rtCP_k_assumed_lane_width_m1_Value (3.5F)

/* Expression: k_assumed_lane_width_m
 * Referenced by: '<S480>/k_assumed_lane_width_m3'
 */
#define rtCP_k_assumed_lane_width_m3_Value (3.5F)

/* Expression: k_invalid_lane_width_jump_thold
 * Referenced by: '<S480>/k_invalid_lane_width_jump_thold'
 */
#define rtCP_k_invalid_lane_width_jump_thold_Value (0.7F)

/* Expression: k_ME_MAX_LANE_WIDTH
 * Referenced by: '<S481>/const'
 */
#define rtCP_const_Value_i             (8.0F)

/* Expression: k_assumed_lane_width_m
 * Referenced by: '<S481>/k_assumed_lane_width_m'
 */
#define rtCP_k_assumed_lane_width_m_Value_f (3.5F)

/* Expression: k_assumed_lane_width_m
 * Referenced by: '<S481>/k_assumed_lane_width_m1'
 */
#define rtCP_k_assumed_lane_width_m1_Value_h (3.5F)

/* Expression: k_assumed_lane_width_m
 * Referenced by: '<S481>/k_assumed_lane_width_m3'
 */
#define rtCP_k_assumed_lane_width_m3_Value_m (3.5F)

/* Expression: k_invalid_lane_width_jump_thold
 * Referenced by: '<S481>/k_invalid_lane_width_jump_thold'
 */
#define rtCP_k_invalid_lane_width_jump_thold_Value_a (0.7F)

/* Computed Parameter: rtCP_Constant_Value_aig
 * Referenced by: '<S457>/Constant'
 */
#define rtCP_Constant_Value_aig        (-2.0F)

/* Computed Parameter: rtCP_Constant1_Value_d5
 * Referenced by: '<S457>/Constant1'
 */
#define rtCP_Constant1_Value_d5        (-2.0F)

/* Expression: k_lane_change_offset_margin
 * Referenced by: '<S457>/k_lane_change_offset_margin'
 */
#define rtCP_k_lane_change_offset_margin_Value (0.35F)

/* Expression: k_lane_change_offset_margin
 * Referenced by: '<S457>/k_lane_change_offset_margin1'
 */
#define rtCP_k_lane_change_offset_margin1_Value (0.35F)

/* Expression: k_EP_left_offset_for_LC
 * Referenced by: '<S457>/k_left_offset_for_lane_change'
 */
#define rtCP_k_left_offset_for_lane_change_Value (-1.5F)

/* Expression: k_EP_right_offset_for_LC
 * Referenced by: '<S457>/k_right_offset_for_lane_change'
 */
#define rtCP_k_right_offset_for_lane_change_Value (-1.5F)

/* Computed Parameter: rtCP_Constant_Value_on
 * Referenced by: '<S458>/Constant'
 */
#define rtCP_Constant_Value_on         (2.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S458>/Constant1'
 */
#define rtCP_Constant1_Value_b         (0.0F)

/* Expression: k_fut_lat_rate_pre_time
 * Referenced by: '<S459>/k_fut_lat_rate_pre_time'
 */
#define rtCP_k_fut_lat_rate_pre_time_Value (0.8F)

/* Computed Parameter: rtCP_min_const_Value
 * Referenced by: '<S521>/min_const'
 */
#define rtCP_min_const_Value           (0.001F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S460>/Constant10'
 */
#define rtCP_Constant10_Value_g        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S460>/Constant11'
 */
#define rtCP_Constant11_Value_l        (0.0F)

/* Computed Parameter: rtCP_Constant6_Value_p
 * Referenced by: '<S460>/Constant6'
 */
#define rtCP_Constant6_Value_p         (0.9F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S460>/Constant7'
 */
#define rtCP_Constant7_Value_l         (0.0F)

/* Computed Parameter: rtCP_Constant8_Value_d
 * Referenced by: '<S460>/Constant8'
 */
#define rtCP_Constant8_Value_d         (0.9F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S460>/Constant9'
 */
#define rtCP_Constant9_Value_i         (0.0F)

/* Computed Parameter: rtCP_min_const_Value_k
 * Referenced by: '<S522>/min_const'
 */
#define rtCP_min_const_Value_k         (-0.001F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S461>/Constant10'
 */
#define rtCP_Constant10_Value_jf       (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S461>/Constant11'
 */
#define rtCP_Constant11_Value_p        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S461>/Constant12'
 */
#define rtCP_Constant12_Value_m        (0.0F)

/* Computed Parameter: rtCP_Constant7_Value_j4
 * Referenced by: '<S461>/Constant7'
 */
#define rtCP_Constant7_Value_j4        (0.9F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S461>/Constant8'
 */
#define rtCP_Constant8_Value_er        (0.0F)

/* Computed Parameter: rtCP_Constant9_Value_gv
 * Referenced by: '<S461>/Constant9'
 */
#define rtCP_Constant9_Value_gv        (0.9F)

/* Computed Parameter: rtCP_min_const_Value_a
 * Referenced by: '<S523>/min_const'
 */
#define rtCP_min_const_Value_a         (0.001F)

/* Computed Parameter: rtCP_min_const_Value_a4
 * Referenced by: '<S524>/min_const'
 */
#define rtCP_min_const_Value_a4        (-0.001F)

/* Expression: k_ELK_RE_torq_baseline
 * Referenced by: '<S531>/Constant'
 */
#define rtCP_Constant_Value_n5         (1.5F)

/* Expression: k_ELK_RE_torq_baseline
 * Referenced by: '<S531>/Constant1'
 */
#define rtCP_Constant1_Value_n         (1.5F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S531>/Constant4'
 */
#define rtCP_Constant4_Value_je        (0.0F)

/* Computed Parameter: rtCP_k_abs_posn_fade_gain_Value_k
 * Referenced by: '<S531>/k_abs_posn_fade_gain'
 */
#define rtCP_k_abs_posn_fade_gain_Value_k (0.95F)

/* Expression: k_ELK_RE_torq_baseline
 * Referenced by: '<S532>/Constant'
 */
#define rtCP_Constant_Value_ou         (1.5F)

/* Expression: k_ELK_RE_torq_baseline
 * Referenced by: '<S532>/Constant1'
 */
#define rtCP_Constant1_Value_m         (1.5F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S532>/Constant4'
 */
#define rtCP_Constant4_Value_aj        (0.0F)

/* Computed Parameter: rtCP_k_abs_posn_fade_gain_Value_kk
 * Referenced by: '<S532>/k_abs_posn_fade_gain'
 */
#define rtCP_k_abs_posn_fade_gain_Value_kk (0.95F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S534>/Constant2'
 */
#define rtCP_Constant2_Value_k         (0.0F)

/* Expression: k_EP_left_offset_for_LC
 * Referenced by: '<S526>/k_left_offset_for_lane_change'
 */
#define rtCP_k_left_offset_for_lane_change_Value_f (-1.5F)

/* Expression: k_EP_right_offset_for_LC
 * Referenced by: '<S526>/k_right_offset_for_lane_change'
 */
#define rtCP_k_right_offset_for_lane_change_Value_n (-1.5F)

/* Computed Parameter: rtCP_Constant12_Value_n
 * Referenced by: '<S527>/Constant12'
 */
#define rtCP_Constant12_Value_n        (100.0F)

/* Computed Parameter: rtCP_Constant2_Value_m4
 * Referenced by: '<S527>/Constant2'
 */
#define rtCP_Constant2_Value_m4        (100.0F)

/* Expression: const
 * Referenced by: '<S559>/Constant'
 */
#define rtCP_Constant_Value_dr         (0.001F)

/* Computed Parameter: rtCP_Constant2_Value_gr
 * Referenced by: '<S556>/Constant2'
 */
#define rtCP_Constant2_Value_gr        (2.0F)

/* Computed Parameter: rtCP_Constant3_Value_o
 * Referenced by: '<S556>/Constant3'
 */
#define rtCP_Constant3_Value_o         (3.0F)

/* Computed Parameter: rtCP_Constant4_Value_n3
 * Referenced by: '<S556>/Constant4'
 */
#define rtCP_Constant4_Value_n3        (3.0F)

/* Expression: k_EP_host_wheel_base
 * Referenced by: '<S437>/k_WheelBase'
 */
#define rtCP_k_WheelBase_Value         (3.089F)

/* Expression: k_EP_sfconf_VH_thold
 * Referenced by: '<S556>/k_sfconf_VH_thold1'
 */
#define rtCP_k_sfconf_VH_thold1_Value  (0.0F)

/* Expression: k_EP_sfconf_hi_thold
 * Referenced by: '<S556>/k_sfconf_hi_thold'
 */
#define rtCP_k_sfconf_hi_thold_Value_l (0.0F)

/* Expression: k_EP_left_a0_cal_bias
 * Referenced by: '<S527>/k_right_a0_cal_bias'
 */
#define rtCP_k_right_a0_cal_bias_Value (0.0F)

/* Expression: k_EP_left_a0_cal_bias
 * Referenced by: '<S527>/k_right_a0_cal_bias1'
 */
#define rtCP_k_right_a0_cal_bias1_Value (0.0F)

/* Computed Parameter: rtCP_Constant12_Value_p
 * Referenced by: '<S528>/Constant12'
 */
#define rtCP_Constant12_Value_p        (100.0F)

/* Computed Parameter: rtCP_Constant2_Value_mj
 * Referenced by: '<S528>/Constant2'
 */
#define rtCP_Constant2_Value_mj        (100.0F)

/* Expression: const
 * Referenced by: '<S566>/Constant'
 */
#define rtCP_Constant_Value_m0         (0.001F)

/* Computed Parameter: rtCP_Constant3_Value_li
 * Referenced by: '<S563>/Constant3'
 */
#define rtCP_Constant3_Value_li        (2.0F)

/* Computed Parameter: rtCP_Constant4_Value_gs
 * Referenced by: '<S563>/Constant4'
 */
#define rtCP_Constant4_Value_gs        (3.0F)

/* Computed Parameter: rtCP_Constant5_Value_k
 * Referenced by: '<S563>/Constant5'
 */
#define rtCP_Constant5_Value_k         (3.0F)

/* Expression: k_EP_sfconf_VH_thold
 * Referenced by: '<S563>/k_sfconf_VH_thold1'
 */
#define rtCP_k_sfconf_VH_thold1_Value_n (0.0F)

/* Expression: k_EP_sfconf_hi_thold
 * Referenced by: '<S563>/k_sfconf_hi_thold'
 */
#define rtCP_k_sfconf_hi_thold_Value_hf (0.0F)

/* Expression: k_EP_right_a0_cal_bias
 * Referenced by: '<S528>/k_right_a0_cal_bias'
 */
#define rtCP_k_right_a0_cal_bias_Value_j (0.0F)

/* Expression: k_EP_right_a0_cal_bias
 * Referenced by: '<S528>/k_right_a0_cal_bias1'
 */
#define rtCP_k_right_a0_cal_bias1_Value_o (0.0F)

/* Computed Parameter: rtCP_InvalidTTLC3_Value
 * Referenced by: '<S462>/InvalidTTLC3'
 */
#define rtCP_InvalidTTLC3_Value        (10.1F)

/* Computed Parameter: rtCP_InvalidTTLC4_Value
 * Referenced by: '<S462>/InvalidTTLC4'
 */
#define rtCP_InvalidTTLC4_Value        (10.1F)

/* Expression: k_EP_A1_max_comp
 * Referenced by: '<S567>/k_A1_max_comp'
 */
#define rtCP_k_A1_max_comp_Value       (0.2F)

/* Expression: k_EP_long_dist_camera_to_tire
 * Referenced by: '<S567>/k_long_dist_camera_to_tire'
 */
#define rtCP_k_long_dist_camera_to_tire_Value (1.5F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S529>/InvalidTTLC'
 */
#define rtCP_InvalidTTLC_Value         (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S529>/InvalidTTLC1'
 */
#define rtCP_InvalidTTLC1_Value        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S529>/InvalidTTLC2'
 */
#define rtCP_InvalidTTLC2_Value        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S529>/InvalidTTLC3'
 */
#define rtCP_InvalidTTLC3_Value_k      (0.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S529>/InvalidTTLC6'
 */
#define rtCP_InvalidTTLC6_Value        (1.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S529>/InvalidTTLC7'
 */
#define rtCP_InvalidTTLC7_Value        (1.0F)

/* Expression: k_EP_left_a0_cal_bias
 * Referenced by: '<S529>/k_left_a0_cal_bias'
 */
#define rtCP_k_left_a0_cal_bias_Value  (0.0F)

/* Expression: k_EP_left_a0_cal_bias
 * Referenced by: '<S529>/k_left_a0_cal_bias_2'
 */
#define rtCP_k_left_a0_cal_bias_2_Value (0.0F)

/* Expression: k_EP_A1_max_comp
 * Referenced by: '<S578>/k_A1_max_comp'
 */
#define rtCP_k_A1_max_comp_Value_g     (0.2F)

/* Expression: k_EP_long_dist_camera_to_tire
 * Referenced by: '<S578>/k_long_dist_camera_to_tire'
 */
#define rtCP_k_long_dist_camera_to_tire_Value_e (1.5F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S530>/InvalidTTLC1'
 */
#define rtCP_InvalidTTLC1_Value_i      (0.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S530>/InvalidTTLC2'
 */
#define rtCP_InvalidTTLC2_Value_h      (1.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S530>/InvalidTTLC3'
 */
#define rtCP_InvalidTTLC3_Value_a      (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S530>/InvalidTTLC4'
 */
#define rtCP_InvalidTTLC4_Value_l      (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S530>/InvalidTTLC6'
 */
#define rtCP_InvalidTTLC6_Value_f      (0.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S530>/InvalidTTLC9'
 */
#define rtCP_InvalidTTLC9_Value        (1.0F)

/* Expression: k_EP_right_a0_cal_bias
 * Referenced by: '<S530>/k_right_a0_cal_bias'
 */
#define rtCP_k_right_a0_cal_bias_Value_e (0.0F)

/* Expression: k_EP_right_a0_cal_bias
 * Referenced by: '<S530>/k_right_a0_cal_bias_2'
 */
#define rtCP_k_right_a0_cal_bias_2_Value (0.0F)

/* Expression: k_EP_A1_max_comp
 * Referenced by: '<S594>/k_A1_max_comp'
 */
#define rtCP_k_A1_max_comp_Value_f     (0.2F)

/* Expression: k_EP_long_dist_camera_to_tire
 * Referenced by: '<S594>/k_long_dist_camera_to_tire'
 */
#define rtCP_k_long_dist_camera_to_tire_Value_i (1.5F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S589>/InvalidTTLC'
 */
#define rtCP_InvalidTTLC_Value_n       (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S589>/InvalidTTLC1'
 */
#define rtCP_InvalidTTLC1_Value_h      (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S589>/InvalidTTLC2'
 */
#define rtCP_InvalidTTLC2_Value_e      (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S589>/InvalidTTLC3'
 */
#define rtCP_InvalidTTLC3_Value_c      (0.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S589>/InvalidTTLC6'
 */
#define rtCP_InvalidTTLC6_Value_fb     (1.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S589>/InvalidTTLC7'
 */
#define rtCP_InvalidTTLC7_Value_c      (1.0F)

/* Expression: k_EP_left_a0_cal_bias
 * Referenced by: '<S589>/k_left_a0_cal_bias'
 */
#define rtCP_k_left_a0_cal_bias_Value_c (0.0F)

/* Expression: k_EP_left_a0_cal_bias
 * Referenced by: '<S589>/k_left_a0_cal_bias_2'
 */
#define rtCP_k_left_a0_cal_bias_2_Value_c (0.0F)

/* Expression: k_LKA_min_lane_width_enable_lo
 * Referenced by: '<S590>/Constant'
 */
#define rtCP_Constant_Value_h3f        (2.5F)

/* Expression: k_LKA_min_lane_width_enable_hi
 * Referenced by: '<S590>/Constant1'
 */
#define rtCP_Constant1_Value_ju        (2.6F)

/* Expression: k_EP_C0_maxPos
 * Referenced by: '<S590>/Constant11'
 */
#define rtCP_Constant11_Value_bz       (3.0F)

/* Expression: k_EP_C0Jmp_Thr
 * Referenced by: '<S590>/Constant24'
 */
#define rtCP_Constant24_Value_j        (0.5F)

/* Expression: k_LKA_max_lane_width_enable_hi
 * Referenced by: '<S590>/Constant4'
 */
#define rtCP_Constant4_Value_h         (5.5F)

/* Expression: k_LKA_max_lane_width_enable_lo
 * Referenced by: '<S590>/Constant5'
 */
#define rtCP_Constant5_Value_i         (5.4F)

/* Expression: k_EP_C0_minNeg
 * Referenced by: '<S590>/Constant8'
 */
#define rtCP_Constant8_Value_o         (-0.02F)

/* Expression: const
 * Referenced by: '<S605>/Constant'
 */
#define rtCP_Constant_Value_k0         (0.001F)

/* Computed Parameter: rtCP_Constant2_Value_l0
 * Referenced by: '<S591>/Constant2'
 */
#define rtCP_Constant2_Value_l0        (2.0F)

/* Computed Parameter: rtCP_Constant3_Value_nr
 * Referenced by: '<S591>/Constant3'
 */
#define rtCP_Constant3_Value_nr        (3.0F)

/* Computed Parameter: rtCP_Constant4_Value_b3
 * Referenced by: '<S591>/Constant4'
 */
#define rtCP_Constant4_Value_b3        (3.0F)

/* Expression: k_EP_sfconf_VH_thold
 * Referenced by: '<S591>/k_sfconf_VH_thold1'
 */
#define rtCP_k_sfconf_VH_thold1_Value_h (0.0F)

/* Expression: k_EP_sfconf_hi_thold
 * Referenced by: '<S591>/k_sfconf_hi_thold'
 */
#define rtCP_k_sfconf_hi_thold_Value_f (0.0F)

/* Expression: const
 * Referenced by: '<S606>/Constant'
 */
#define rtCP_Constant_Value_aa         (0.001F)

/* Computed Parameter: rtCP_Constant3_Value_ga
 * Referenced by: '<S592>/Constant3'
 */
#define rtCP_Constant3_Value_ga        (2.0F)

/* Computed Parameter: rtCP_Constant4_Value_di
 * Referenced by: '<S592>/Constant4'
 */
#define rtCP_Constant4_Value_di        (3.0F)

/* Computed Parameter: rtCP_Constant5_Value_ol
 * Referenced by: '<S592>/Constant5'
 */
#define rtCP_Constant5_Value_ol        (3.0F)

/* Expression: k_EP_sfconf_VH_thold
 * Referenced by: '<S592>/k_sfconf_VH_thold1'
 */
#define rtCP_k_sfconf_VH_thold1_Value_p (0.0F)

/* Expression: k_EP_sfconf_hi_thold
 * Referenced by: '<S592>/k_sfconf_hi_thold'
 */
#define rtCP_k_sfconf_hi_thold_Value_n (0.0F)

/* Expression: k_EP_A1_max_comp
 * Referenced by: '<S607>/k_A1_max_comp'
 */
#define rtCP_k_A1_max_comp_Value_i     (0.2F)

/* Expression: k_EP_long_dist_camera_to_tire
 * Referenced by: '<S607>/k_long_dist_camera_to_tire'
 */
#define rtCP_k_long_dist_camera_to_tire_Value_b (1.5F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S593>/InvalidTTLC1'
 */
#define rtCP_InvalidTTLC1_Value_b      (0.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S593>/InvalidTTLC2'
 */
#define rtCP_InvalidTTLC2_Value_o      (1.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S593>/InvalidTTLC3'
 */
#define rtCP_InvalidTTLC3_Value_g      (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S593>/InvalidTTLC4'
 */
#define rtCP_InvalidTTLC4_Value_c      (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S593>/InvalidTTLC6'
 */
#define rtCP_InvalidTTLC6_Value_a      (0.0F)

/* Expression: C_ONE_SINGLE
 * Referenced by: '<S593>/InvalidTTLC9'
 */
#define rtCP_InvalidTTLC9_Value_i      (1.0F)

/* Expression: k_EP_right_a0_cal_bias
 * Referenced by: '<S593>/k_right_a0_cal_bias'
 */
#define rtCP_k_right_a0_cal_bias_Value_i (0.0F)

/* Expression: k_EP_right_a0_cal_bias
 * Referenced by: '<S593>/k_right_a0_cal_bias_2'
 */
#define rtCP_k_right_a0_cal_bias_2_Value_g (0.0F)

/* Expression: k_LostLane_HoldTime_LV2
 * Referenced by: '<S618>/k_LostLane_HoldTime_LV1'
 */
#define rtCP_k_LostLane_HoldTime_LV1_Value (1000.0F)

/* Computed Parameter: rtCP_Constant_Value_gj
 * Referenced by: '<S618>/Constant'
 */
#define rtCP_Constant_Value_gj         (2.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S618>/Constant1'
 */
#define rtCP_Constant1_Value_ns        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S618>/Constant11'
 */
#define rtCP_Constant11_Value_c        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S618>/Constant2'
 */
#define rtCP_Constant2_Value_lz        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_ek
 * Referenced by: '<S618>/Constant3'
 */
#define rtCP_Constant3_Value_ek        (3.6F)

/* Computed Parameter: rtCP_Constant5_Value_nw
 * Referenced by: '<S618>/Constant5'
 */
#define rtCP_Constant5_Value_nw        (4.4E-5F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S618>/Constant6'
 */
#define rtCP_Constant6_Value_h         (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S618>/Constant8'
 */
#define rtCP_Constant8_Value_i5        (0.0F)

/* Expression: k_rs_curv_thold_high
 * Referenced by: '<S618>/k_rs_curv_thold_high'
 */
#define rtCP_k_rs_curv_thold_high_Value (0.0005F)

/* Expression: k_rs_curv_thold_low
 * Referenced by: '<S618>/k_rs_curv_thold_low'
 */
#define rtCP_k_rs_curv_thold_low_Value (0.0002F)

/* Expression: k_rs_yaw_thold_high
 * Referenced by: '<S618>/k_rs_yaw_thold_high'
 */
#define rtCP_k_rs_yaw_thold_high_Value (1.5F)

/* Expression: k_rs_yaw_thold_low
 * Referenced by: '<S618>/k_rs_yaw_thold_low'
 */
#define rtCP_k_rs_yaw_thold_low_Value  (0.8F)

/* Expression: k_LKA_MIN_SPEED_HI
 * Referenced by: '<S618>/k_LKA_MIN_SPEED_HI'
 */
#define rtCP_k_LKA_MIN_SPEED_HI_Value  (40.0F)

/* Expression: k_Path_Deviation_Filter_Gain
 * Referenced by: '<S618>/k_Path_Deviation_Filter_Gain'
 */
#define rtCP_k_Path_Deviation_Filter_Gain_Value (0.05F)

/* Computed Parameter: rtCP_Constant_Value_pf
 * Referenced by: '<S619>/Constant'
 */
#define rtCP_Constant_Value_pf         (0.0005F)

/* Computed Parameter: rtCP_Constant1_Value_ih
 * Referenced by: '<S619>/Constant1'
 */
#define rtCP_Constant1_Value_ih        (0.001F)

/* Computed Parameter: rtCP_Constant2_Value_a
 * Referenced by: '<S619>/Constant2'
 */
#define rtCP_Constant2_Value_a         (0.0005F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S619>/Constant3'
 */
#define rtCP_Constant3_Value_m5        (0.0F)

/* Expression: k_LostLane_HoldTime_LV2
 * Referenced by: '<S634>/k_LostLane_HoldTime_LV1'
 */
#define rtCP_k_LostLane_HoldTime_LV1_Value_i (1000.0F)

/* Expression: k_LostLane_HoldTime_LV2
 * Referenced by: '<S634>/k_LostLane_HoldTime_LV3'
 */
#define rtCP_k_LostLane_HoldTime_LV3_Value (1000.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S634>/Constant4'
 */
#define rtCP_Constant4_Value_i         (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S634>/Constant6'
 */
#define rtCP_Constant6_Value_k         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mc
 * Referenced by: '<S620>/Constant'
 */
#define rtCP_Constant_Value_mc         (0.0005F)

/* Computed Parameter: rtCP_Constant1_Value_jux
 * Referenced by: '<S620>/Constant1'
 */
#define rtCP_Constant1_Value_jux       (0.001F)

/* Computed Parameter: rtCP_Constant2_Value_b0
 * Referenced by: '<S620>/Constant2'
 */
#define rtCP_Constant2_Value_b0        (0.0005F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S620>/Constant3'
 */
#define rtCP_Constant3_Value_pw        (0.0F)

/* Expression: k_LostLane_HoldTime_LV2
 * Referenced by: '<S642>/k_LostLane_HoldTime_LV1'
 */
#define rtCP_k_LostLane_HoldTime_LV1_Value_d (1000.0F)

/* Expression: k_LostLane_HoldTime_LV2
 * Referenced by: '<S642>/k_LostLane_HoldTime_LV3'
 */
#define rtCP_k_LostLane_HoldTime_LV3_Value_o (1000.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S642>/Constant4'
 */
#define rtCP_Constant4_Value_n1        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S642>/Constant6'
 */
#define rtCP_Constant6_Value_mh        (0.0F)

/* Computed Parameter: rtCP_HeadWay_Index_Value
 * Referenced by: '<S621>/HeadWay_Index'
 */
#define rtCP_HeadWay_Index_Value       (3.6F)

/* Expression: k_LostLane_HoldTime_LV2
 * Referenced by: '<S655>/k_LostLane_HoldTime_LV1'
 */
#define rtCP_k_LostLane_HoldTime_LV1_Value_l (1000.0F)

/* Expression: k_LostLane_HoldTime_LV2
 * Referenced by: '<S655>/k_LostLane_HoldTime_LV3'
 */
#define rtCP_k_LostLane_HoldTime_LV3_Value_e (1000.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S655>/Constant4'
 */
#define rtCP_Constant4_Value_je5       (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S655>/Constant6'
 */
#define rtCP_Constant6_Value_c         (0.0F)

/* Computed Parameter: rtCP_step1_Value
 * Referenced by: '<S670>/step1'
 */
#define rtCP_step1_Value               (5.0E-7F)

/* Computed Parameter: rtCP_step1_Value_f
 * Referenced by: '<S656>/step1'
 */
#define rtCP_step1_Value_f             (0.0015F)

/* Expression: k_EP_host_veh_width
 * Referenced by: '<S437>/k_host_veh_width'
 */
#define rtCP_k_host_veh_width_Value    (1.86F)

/* Expression: k_EP_lm_preview_time_sec
 * Referenced by: '<S437>/k_lane_marker_preview_time_sec'
 */
#define rtCP_k_lane_marker_preview_time_sec_Value (0.8F)

/* Computed Parameter: rtCP_Gain6_Gain_a
 * Referenced by: '<S556>/Gain6'
 */
#define rtCP_Gain6_Gain_a              (-1.0F)

/* Computed Parameter: rtCP_Gain7_Gain_l
 * Referenced by: '<S556>/Gain7'
 */
#define rtCP_Gain7_Gain_l              (-1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_m
 * Referenced by: '<S556>/Gain8'
 */
#define rtCP_Gain8_Gain_m              (-1.0F)

/* Computed Parameter: rtCP_Gain5_Gain_c
 * Referenced by: '<S556>/Gain5'
 */
#define rtCP_Gain5_Gain_c              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_pe
 * Referenced by: '<S424>/Gain1'
 */
#define rtCP_Gain1_Gain_pe             (1.0F)

/* Computed Parameter: rtCP_Gain_Gain_nq
 * Referenced by: '<S527>/Gain'
 */
#define rtCP_Gain_Gain_nq              (0.5F)

/* Computed Parameter: rtCP_flip_for_left_side1_Gain
 * Referenced by: '<S527>/flip_for_left_side1'
 */
#define rtCP_flip_for_left_side1_Gain  (-1.0F)

/* Computed Parameter: rtCP_flip_for_left_side2_Gain
 * Referenced by: '<S527>/flip_for_left_side2'
 */
#define rtCP_flip_for_left_side2_Gain  (-1.0F)

/* Expression: C_RAD2DEG
 * Referenced by: '<S529>/Gain1'
 */
#define rtCP_Gain1_Gain_bvy            (57.2957802F)

/* Computed Parameter: rtCP_Gain4_Gain_j
 * Referenced by: '<S529>/Gain4'
 */
#define rtCP_Gain4_Gain_j              (2.0F)

/* Computed Parameter: rtCP_Gain5_Gain_cx
 * Referenced by: '<S591>/Gain5'
 */
#define rtCP_Gain5_Gain_cx             (-1.0F)

/* Computed Parameter: rtCP_Gain6_Gain_h
 * Referenced by: '<S591>/Gain6'
 */
#define rtCP_Gain6_Gain_h              (-1.0F)

/* Computed Parameter: rtCP_Gain7_Gain_p
 * Referenced by: '<S591>/Gain7'
 */
#define rtCP_Gain7_Gain_p              (-1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_o
 * Referenced by: '<S591>/Gain8'
 */
#define rtCP_Gain8_Gain_o              (-1.0F)

/* Expression: C_RAD2DEG
 * Referenced by: '<S589>/Gain1'
 */
#define rtCP_Gain1_Gain_nh             (57.2957802F)

/* Computed Parameter: rtCP_Gain4_Gain_o
 * Referenced by: '<S589>/Gain4'
 */
#define rtCP_Gain4_Gain_o              (2.0F)

/* Computed Parameter: rtCP_Gain5_Gain_j
 * Referenced by: '<S589>/Gain5'
 */
#define rtCP_Gain5_Gain_j              (6.0F)

/* Computed Parameter: rtCP_Gain5_Gain_m
 * Referenced by: '<S529>/Gain5'
 */
#define rtCP_Gain5_Gain_m              (6.0F)

/* Computed Parameter: rtCP_Gain6_Gain_n
 * Referenced by: '<S563>/Gain6'
 */
#define rtCP_Gain6_Gain_n              (-1.0F)

/* Computed Parameter: rtCP_Gain7_Gain_e
 * Referenced by: '<S563>/Gain7'
 */
#define rtCP_Gain7_Gain_e              (-1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_n
 * Referenced by: '<S563>/Gain8'
 */
#define rtCP_Gain8_Gain_n              (-1.0F)

/* Computed Parameter: rtCP_Gain5_Gain_l
 * Referenced by: '<S563>/Gain5'
 */
#define rtCP_Gain5_Gain_l              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_oh
 * Referenced by: '<S528>/Gain'
 */
#define rtCP_Gain_Gain_oh              (0.5F)

/* Expression: C_RAD2DEG
 * Referenced by: '<S530>/Gain2'
 */
#define rtCP_Gain2_Gain_l2             (57.2957802F)

/* Computed Parameter: rtCP_Gain3_Gain_n
 * Referenced by: '<S530>/Gain3'
 */
#define rtCP_Gain3_Gain_n              (2.0F)

/* Computed Parameter: rtCP_Gain5_Gain_e
 * Referenced by: '<S592>/Gain5'
 */
#define rtCP_Gain5_Gain_e              (-1.0F)

/* Computed Parameter: rtCP_Gain6_Gain_f
 * Referenced by: '<S592>/Gain6'
 */
#define rtCP_Gain6_Gain_f              (-1.0F)

/* Computed Parameter: rtCP_Gain7_Gain_lg
 * Referenced by: '<S592>/Gain7'
 */
#define rtCP_Gain7_Gain_lg             (-1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_p
 * Referenced by: '<S592>/Gain8'
 */
#define rtCP_Gain8_Gain_p              (-1.0F)

/* Expression: C_RAD2DEG
 * Referenced by: '<S593>/Gain2'
 */
#define rtCP_Gain2_Gain_d5             (57.2957802F)

/* Computed Parameter: rtCP_Gain3_Gain_h
 * Referenced by: '<S593>/Gain3'
 */
#define rtCP_Gain3_Gain_h              (2.0F)

/* Computed Parameter: rtCP_Gain6_Gain_l
 * Referenced by: '<S593>/Gain6'
 */
#define rtCP_Gain6_Gain_l              (6.0F)

/* Computed Parameter: rtCP_Gain6_Gain_d
 * Referenced by: '<S530>/Gain6'
 */
#define rtCP_Gain6_Gain_d              (6.0F)

/* Expression: C_KPH2MPS
 * Referenced by: '<S437>/KPH2MPS'
 */
#define rtCP_KPH2MPS_Gain_c            (0.277777791F)

/* Computed Parameter: rtCP_Saturation_UpperSat_aq
 * Referenced by: '<S437>/Saturation'
 */
#define rtCP_Saturation_UpperSat_aq    (200.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_kf
 * Referenced by: '<S437>/Saturation'
 */
#define rtCP_Saturation_LowerSat_kf    (1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_j
 * Referenced by: '<S529>/Gain8'
 */
#define rtCP_Gain8_Gain_j              (0.5F)

/* Computed Parameter: rtCP_flip_for_left_side_Gain
 * Referenced by: '<S529>/flip_for_left_side'
 */
#define rtCP_flip_for_left_side_Gain   (-1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_a
 * Referenced by: '<S530>/Gain8'
 */
#define rtCP_Gain8_Gain_a              (0.5F)

/* Computed Parameter: rtCP_flip_for_left_side1_Gain_k
 * Referenced by: '<S529>/flip_for_left_side1'
 */
#define rtCP_flip_for_left_side1_Gain_k (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_gm
 * Referenced by: '<S530>/Gain'
 */
#define rtCP_Gain_Gain_gm              (-1.0F)

/* Computed Parameter: rtCP_Sat_0L_10H_UpperSat
 * Referenced by: '<S523>/Sat_0L_10H'
 */
#define rtCP_Sat_0L_10H_UpperSat       (10.0F)

/* Computed Parameter: rtCP_Sat_0L_10H_LowerSat
 * Referenced by: '<S523>/Sat_0L_10H'
 */
#define rtCP_Sat_0L_10H_LowerSat       (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_dl
 * Referenced by: '<S524>/Gain'
 */
#define rtCP_Gain_Gain_dl              (-1.0F)

/* Computed Parameter: rtCP_Sat_0L_10H_UpperSat_e
 * Referenced by: '<S524>/Sat_0L_10H'
 */
#define rtCP_Sat_0L_10H_UpperSat_e     (10.0F)

/* Computed Parameter: rtCP_Sat_0L_10H_LowerSat_n
 * Referenced by: '<S524>/Sat_0L_10H'
 */
#define rtCP_Sat_0L_10H_LowerSat_n     (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ju
 * Referenced by: '<S531>/Gain2'
 */
#define rtCP_Gain2_Gain_ju             (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_i1
 * Referenced by: '<S531>/Gain1'
 */
#define rtCP_Gain1_Gain_i1             (0.5F)

/* Computed Parameter: rtCP_Gain4_Gain_ox
 * Referenced by: '<S531>/Gain4'
 */
#define rtCP_Gain4_Gain_ox             (-1.0F)

/* Expression: k_ELK_laneedge_absposn_max
 * Referenced by: '<S531>/Saturation'
 */
#define rtCP_Saturation_UpperSat_mv    (1.5F)

/* Expression: k_ELK_laneedge_absposn_min
 * Referenced by: '<S531>/Saturation'
 */
#define rtCP_Saturation_LowerSat_cy    (-1.5F)

/* Computed Parameter: rtCP_flip_polarity_Gain_d
 * Referenced by: '<S437>/flip_polarity'
 */
#define rtCP_flip_polarity_Gain_d      (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_in
 * Referenced by: '<S532>/Gain2'
 */
#define rtCP_Gain2_Gain_in             (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_hg
 * Referenced by: '<S532>/Gain1'
 */
#define rtCP_Gain1_Gain_hg             (0.5F)

/* Computed Parameter: rtCP_Gain4_Gain_e
 * Referenced by: '<S532>/Gain4'
 */
#define rtCP_Gain4_Gain_e              (-1.0F)

/* Expression: k_ELK_laneedge_absposn_max
 * Referenced by: '<S532>/Saturation'
 */
#define rtCP_Saturation_UpperSat_di    (1.5F)

/* Expression: k_ELK_laneedge_absposn_min
 * Referenced by: '<S532>/Saturation'
 */
#define rtCP_Saturation_LowerSat_pe    (-1.5F)

/* Computed Parameter: rtCP_Gain9_Gain_f
 * Referenced by: '<S424>/Gain9'
 */
#define rtCP_Gain9_Gain_f              (1.0F)

/* Computed Parameter: rtCP_Gain10_Gain_a
 * Referenced by: '<S424>/Gain10'
 */
#define rtCP_Gain10_Gain_a             (1.0F)

/* Computed Parameter: rtCP_Gain12_Gain_i
 * Referenced by: '<S424>/Gain12'
 */
#define rtCP_Gain12_Gain_i             (1.0F)

/* Computed Parameter: rtCP_Gain13_Gain_b
 * Referenced by: '<S424>/Gain13'
 */
#define rtCP_Gain13_Gain_b             (1.0F)

/* Computed Parameter: rtCP_Gain11_Gain_i
 * Referenced by: '<S424>/Gain11'
 */
#define rtCP_Gain11_Gain_i             (1.0F)

/* Computed Parameter: rtCP_Gain14_Gain_g
 * Referenced by: '<S424>/Gain14'
 */
#define rtCP_Gain14_Gain_g             (1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_e
 * Referenced by: '<S589>/Gain8'
 */
#define rtCP_Gain8_Gain_e              (0.5F)

/* Computed Parameter: rtCP_flip_for_left_side1_Gain_m
 * Referenced by: '<S589>/flip_for_left_side1'
 */
#define rtCP_flip_for_left_side1_Gain_m (-1.0F)

/* Computed Parameter: rtCP_Sat_0L_10H_UpperSat_d
 * Referenced by: '<S521>/Sat_0L_10H'
 */
#define rtCP_Sat_0L_10H_UpperSat_d     (10.0F)

/* Computed Parameter: rtCP_Sat_0L_10H_LowerSat_c
 * Referenced by: '<S521>/Sat_0L_10H'
 */
#define rtCP_Sat_0L_10H_LowerSat_c     (0.0F)

/* Computed Parameter: rtCP_Gain8_Gain_i
 * Referenced by: '<S593>/Gain8'
 */
#define rtCP_Gain8_Gain_i              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_hv
 * Referenced by: '<S593>/Gain'
 */
#define rtCP_Gain_Gain_hv              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_pk
 * Referenced by: '<S522>/Gain'
 */
#define rtCP_Gain_Gain_pk              (-1.0F)

/* Computed Parameter: rtCP_Sat_0L_10H_UpperSat_h
 * Referenced by: '<S522>/Sat_0L_10H'
 */
#define rtCP_Sat_0L_10H_UpperSat_h     (10.0F)

/* Computed Parameter: rtCP_Sat_0L_10H_LowerSat_l
 * Referenced by: '<S522>/Sat_0L_10H'
 */
#define rtCP_Sat_0L_10H_LowerSat_l     (0.0F)

/* Computed Parameter: rtCP_flip_for_left_side_Gain_k
 * Referenced by: '<S589>/flip_for_left_side'
 */
#define rtCP_flip_for_left_side_Gain_k (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_os
 * Referenced by: '<S476>/Gain1'
 */
#define rtCP_Gain1_Gain_os             (0.5F)

/* Expression: k_ELK_max_LW_for_tq
 * Referenced by: '<S476>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_e    (5.5F)

/* Computed Parameter: rtCP_Saturation1_LowerSat_h
 * Referenced by: '<S476>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_h    (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_lp
 * Referenced by: '<S476>/Gain'
 */
#define rtCP_Gain_Gain_lp              (0.5F)

/* Computed Parameter: rtCP_Gain3_Gain_o
 * Referenced by: '<S476>/Gain3'
 */
#define rtCP_Gain3_Gain_o              (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_mc
 * Referenced by: '<S476>/Gain2'
 */
#define rtCP_Gain2_Gain_mc             (0.5F)

/* Computed Parameter: rtCP_Gain4_Gain_l
 * Referenced by: '<S476>/Gain4'
 */
#define rtCP_Gain4_Gain_l              (-1.0F)

/* Computed Parameter: rtCP_Gain5_Gain_h
 * Referenced by: '<S476>/Gain5'
 */
#define rtCP_Gain5_Gain_h              (0.5F)

/* Expression: k_laneboundary_absposn_max
 * Referenced by: '<S476>/Saturation'
 */
#define rtCP_Saturation_UpperSat_gs    (1.75F)

/* Expression: k_laneboundary_absposn_min
 * Referenced by: '<S476>/Saturation'
 */
#define rtCP_Saturation_LowerSat_jz    (-1.75F)

/* Computed Parameter: rtCP_Gain_Gain_k1
 * Referenced by: '<S479>/Gain'
 */
#define rtCP_Gain_Gain_k1              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_jy
 * Referenced by: '<S477>/Gain1'
 */
#define rtCP_Gain1_Gain_jy             (0.5F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_ky
 * Referenced by: '<S501>/Unit Delay'
 */
#define rtCP_UnitDelay_InitialCondition_ky (3.5F)

/* Computed Parameter: rtCP_Saturation_UpperSat_jl
 * Referenced by: '<S501>/Saturation'
 */
#define rtCP_Saturation_UpperSat_jl    (65535.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_du
 * Referenced by: '<S501>/Saturation'
 */
#define rtCP_Saturation_LowerSat_du    (-65535.0F)

/* Expression: k_ELK_max_LW_for_tq
 * Referenced by: '<S477>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_g    (5.5F)

/* Computed Parameter: rtCP_Saturation1_LowerSat_b
 * Referenced by: '<S477>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_b    (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_gh
 * Referenced by: '<S477>/Gain'
 */
#define rtCP_Gain_Gain_gh              (0.5F)

/* Computed Parameter: rtCP_Gain3_Gain_nx
 * Referenced by: '<S477>/Gain3'
 */
#define rtCP_Gain3_Gain_nx             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_lh
 * Referenced by: '<S477>/Gain2'
 */
#define rtCP_Gain2_Gain_lh             (0.5F)

/* Computed Parameter: rtCP_Gain4_Gain_f
 * Referenced by: '<S477>/Gain4'
 */
#define rtCP_Gain4_Gain_f              (-1.0F)

/* Computed Parameter: rtCP_Gain5_Gain_n
 * Referenced by: '<S477>/Gain5'
 */
#define rtCP_Gain5_Gain_n              (0.5F)

/* Expression: k_laneboundary_absposn_max
 * Referenced by: '<S477>/Saturation'
 */
#define rtCP_Saturation_UpperSat_ga    (1.75F)

/* Expression: k_laneboundary_absposn_min
 * Referenced by: '<S477>/Saturation'
 */
#define rtCP_Saturation_LowerSat_ff    (-1.75F)

/* Computed Parameter: rtCP_Gain_Gain_ec
 * Referenced by: '<S478>/Gain'
 */
#define rtCP_Gain_Gain_ec              (-1.0F)

/* Expression: C_DEG2RAD
 * Referenced by: '<S478>/Gain1'
 */
#define rtCP_Gain1_Gain_jg             (0.017453F)

/* Expression: C_DEG2RAD
 * Referenced by: '<S478>/Gain2'
 */
#define rtCP_Gain2_Gain_gl             (0.017453F)

/* Computed Parameter: rtCP_Saturation_UpperSat_fu
 * Referenced by: '<S478>/Saturation'
 */
#define rtCP_Saturation_UpperSat_fu    (100.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_o
 * Referenced by: '<S478>/Saturation'
 */
#define rtCP_Saturation_LowerSat_o     (1.0F)

/* Computed Parameter: rtCP_Gain_Gain_ox
 * Referenced by: '<S459>/Gain'
 */
#define rtCP_Gain_Gain_ox              (-1.0F)

/* Expression: C_RAD2DEG
 * Referenced by: '<S459>/C_RAD2DEG'
 */
#define rtCP_C_RAD2DEG_Gain            (57.2957802F)

/* Expression: C_DEG2RAD
 * Referenced by: '<S459>/C_DEG2RAD'
 */
#define rtCP_C_DEG2RAD_Gain            (0.017453F)

/* Expression: C_DEG2RAD
 * Referenced by: '<S459>/C_DEG2RAD1'
 */
#define rtCP_C_DEG2RAD1_Gain           (0.017453F)

/* Expression: C_MPS2KPH
 * Referenced by: '<S470>/C_MPS2KPH'
 */
#define rtCP_C_MPS2KPH_Gain            (3.6F)

/* Expression: C_MPS2KPH
 * Referenced by: '<S471>/C_MPS2KPH'
 */
#define rtCP_C_MPS2KPH_Gain_h          (3.6F)

/* Expression: C_MPS2KPH
 * Referenced by: '<S469>/C_MPS2KPH'
 */
#define rtCP_C_MPS2KPH_Gain_f          (3.6F)

/* Expression: C_ONE_HALF
 * Referenced by: '<S454>/C_ONE_HALF'
 */
#define rtCP_C_ONE_HALF_Gain           (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_hu
 * Referenced by: '<S436>/Gain'
 */
#define rtCP_Gain_Gain_hu              (1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_dk
 * Referenced by: '<S436>/Gain2'
 */
#define rtCP_Gain2_Gain_dk             (1.0F)

/* Computed Parameter: rtCP_Gain3_Gain_g
 * Referenced by: '<S436>/Gain3'
 */
#define rtCP_Gain3_Gain_g              (1.0F)

/* Computed Parameter: rtCP_Gain4_Gain_i
 * Referenced by: '<S436>/Gain4'
 */
#define rtCP_Gain4_Gain_i              (1.0F)

/* Computed Parameter: rtCP_Gain_Gain_ae
 * Referenced by: '<S864>/Gain'
 */
#define rtCP_Gain_Gain_ae              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_fv
 * Referenced by: '<S438>/Gain'
 */
#define rtCP_Gain_Gain_fv              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_m
 * Referenced by: '<S438>/Gain1'
 */
#define rtCP_Gain1_Gain_m              (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_e1
 * Referenced by: '<S438>/Gain2'
 */
#define rtCP_Gain2_Gain_e1             (-1.0F)

/* Computed Parameter: rtCP_Gain3_Gain_b
 * Referenced by: '<S438>/Gain3'
 */
#define rtCP_Gain3_Gain_b              (-1.0F)

/* Computed Parameter: rtCP_Gain4_Gain_p
 * Referenced by: '<S438>/Gain4'
 */
#define rtCP_Gain4_Gain_p              (-1.0F)

/* Computed Parameter: rtCP_Gain5_Gain_d
 * Referenced by: '<S438>/Gain5'
 */
#define rtCP_Gain5_Gain_d              (-1.0F)

/* Computed Parameter: rtCP_Gain6_Gain_m
 * Referenced by: '<S438>/Gain6'
 */
#define rtCP_Gain6_Gain_m              (-1.0F)

/* Computed Parameter: rtCP_Gain7_Gain_pr
 * Referenced by: '<S438>/Gain7'
 */
#define rtCP_Gain7_Gain_pr             (-1.0F)

/* Expression: C_KPH2MPS
 * Referenced by: '<S865>/KPH2MPS'
 */
#define rtCP_KPH2MPS_Gain_b            (0.277777791F)

/* Computed Parameter: rtCP_Gain9_Gain_c
 * Referenced by: '<S436>/Gain9'
 */
#define rtCP_Gain9_Gain_c              (1.0F)

/* Computed Parameter: rtCP_Gain12_Gain_c
 * Referenced by: '<S436>/Gain12'
 */
#define rtCP_Gain12_Gain_c             (1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_k
 * Referenced by: '<S436>/Gain8'
 */
#define rtCP_Gain8_Gain_k              (1.0F)

/* Computed Parameter: rtCP_Gain16_Gain_h
 * Referenced by: '<S436>/Gain16'
 */
#define rtCP_Gain16_Gain_h             (1.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_br
 * Referenced by: '<S434>/Unit Delay'
 */
#define rtCP_UnitDelay_InitialCondition_br (-1.0F)

/* Computed Parameter: rtCP_Gain7_Gain_p0
 * Referenced by: '<S619>/Gain7'
 */
#define rtCP_Gain7_Gain_p0             (2.0F)

/* Computed Parameter: rtCP_Gain1_Gain_k5
 * Referenced by: '<S619>/Gain1'
 */
#define rtCP_Gain1_Gain_k5             (6.0F)

/* Computed Parameter: rtCP_Gain7_Gain_a
 * Referenced by: '<S620>/Gain7'
 */
#define rtCP_Gain7_Gain_a              (2.0F)

/* Computed Parameter: rtCP_Gain1_Gain_b2
 * Referenced by: '<S620>/Gain1'
 */
#define rtCP_Gain1_Gain_b2             (6.0F)

/* Computed Parameter: rtCP_Gain7_Gain_er
 * Referenced by: '<S621>/Gain7'
 */
#define rtCP_Gain7_Gain_er             (2.0F)

/* Computed Parameter: rtCP_Gain1_Gain_dd
 * Referenced by: '<S621>/Gain1'
 */
#define rtCP_Gain1_Gain_dd             (6.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_e0
 * Referenced by: '<S621>/Saturation'
 */
#define rtCP_Saturation_UpperSat_e0    (50.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_pl
 * Referenced by: '<S621>/Saturation'
 */
#define rtCP_Saturation_LowerSat_pl    (0.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_bz
 * Referenced by: '<S657>/Saturation'
 */
#define rtCP_Saturation_UpperSat_bz    (0.002F)

/* Computed Parameter: rtCP_Saturation_LowerSat_mq
 * Referenced by: '<S657>/Saturation'
 */
#define rtCP_Saturation_LowerSat_mq    (-0.002F)

/* Expression: C_MPS2KPH
 * Referenced by: '<S618>/Gain'
 */
#define rtCP_Gain_Gain_lh              (3.6F)

/* Computed Parameter: rtCP_Gain1_Gain_cy
 * Referenced by: '<S618>/Gain1'
 */
#define rtCP_Gain1_Gain_cy             (0.5F)

/* Expression: k_Path_Deviation_Threshold_On
 * Referenced by: '<S618>/Path_Deviation_Threshold'
 */
#define rtCP_Path_Deviation_Threshold_OnVal (2.0F)

/* Expression: k_Path_Deviation_Threshold_Off
 * Referenced by: '<S618>/Path_Deviation_Threshold'
 */
#define rtCP_Path_Deviation_Threshold_OffVal (1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_gv
 * Referenced by: '<S618>/Gain2'
 */
#define rtCP_Gain2_Gain_gv             (2.0F)

/* Computed Parameter: rtCP_Gain3_Gain_f
 * Referenced by: '<S618>/Gain3'
 */
#define rtCP_Gain3_Gain_f              (2.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_ce
 * Referenced by: '<S497>/Unit Delay'
 */
#define rtCP_UnitDelay_InitialCondition_ce (3.5F)

/* Computed Parameter: rtCP_Saturation_UpperSat_no
 * Referenced by: '<S497>/Saturation'
 */
#define rtCP_Saturation_UpperSat_no    (65535.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_nb
 * Referenced by: '<S497>/Saturation'
 */
#define rtCP_Saturation_LowerSat_nb    (-65535.0F)

/* Computed Parameter: rtCP_Gain13_Gain_i
 * Referenced by: '<S436>/Gain13'
 */
#define rtCP_Gain13_Gain_i             (1.0F)

/* Computed Parameter: rtCP_Constant1_Value_j5
 * Referenced by: '<S914>/Constant1'
 */
#define rtCP_Constant1_Value_j5        (0.5F)

/* Computed Parameter: rtCP_Constant2_Value_gn0
 * Referenced by: '<S914>/Constant2'
 */
#define rtCP_Constant2_Value_gn0       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pt
 * Referenced by: '<S918>/Constant'
 */
#define rtCP_Constant_Value_pt         (5.0F)

/* Computed Parameter: rtCP_Constant1_Value_em
 * Referenced by: '<S918>/Constant1'
 */
#define rtCP_Constant1_Value_em        (2.0F)

/* Computed Parameter: rtCP_Constant2_Value_kx
 * Referenced by: '<S918>/Constant2'
 */
#define rtCP_Constant2_Value_kx        (3.0F)

/* Computed Parameter: rtCP_Constant3_Value_me
 * Referenced by: '<S918>/Constant3'
 */
#define rtCP_Constant3_Value_me        (1.0F)

/* Computed Parameter: rtCP_Constant5_Value_fn
 * Referenced by: '<S918>/Constant5'
 */
#define rtCP_Constant5_Value_fn        (4.0F)

/* Computed Parameter: rtCP_Constant_Value_iw
 * Referenced by: '<S937>/Constant'
 */
#define rtCP_Constant_Value_iw         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_nr
 * Referenced by: '<S936>/Constant1'
 */
#define rtCP_Constant1_Value_nr        (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_px
 * Referenced by: '<S936>/Constant2'
 */
#define rtCP_Constant2_Value_px        (-1.0F)

/* Computed Parameter: rtCP_Constant1_Value_cl
 * Referenced by: '<S938>/Constant1'
 */
#define rtCP_Constant1_Value_cl        (0.5F)

/* Computed Parameter: rtCP_Constant2_Value_ds
 * Referenced by: '<S938>/Constant2'
 */
#define rtCP_Constant2_Value_ds        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pm
 * Referenced by: '<S942>/Constant'
 */
#define rtCP_Constant_Value_pm         (5.0F)

/* Computed Parameter: rtCP_Constant1_Value_m5
 * Referenced by: '<S942>/Constant1'
 */
#define rtCP_Constant1_Value_m5        (2.0F)

/* Computed Parameter: rtCP_Constant2_Value_bl
 * Referenced by: '<S942>/Constant2'
 */
#define rtCP_Constant2_Value_bl        (3.0F)

/* Computed Parameter: rtCP_Constant3_Value_k
 * Referenced by: '<S942>/Constant3'
 */
#define rtCP_Constant3_Value_k         (1.0F)

/* Computed Parameter: rtCP_Constant5_Value_p
 * Referenced by: '<S942>/Constant5'
 */
#define rtCP_Constant5_Value_p         (4.0F)

/* Expression: k_AES_FinishDureTimeThd
 * Referenced by: '<S9>/AESESA_Mode_Manager'
 */
#define rtCP_AESESA_Mode_Manager_k_AES_FinishDureTimeThd (2.0F)

/* Expression: k_AES_ML_TIME_SEC
 * Referenced by: '<S9>/AESESA_Mode_Manager'
 */
#define rtCP_AESESA_Mode_Manager_k_AES_ML_TIME_SEC (0.02F)

/* Expression: k_AES_ML_TIME_SEC
 * Referenced by: '<S1000>/OnDelay'
 */
#define rtCP_OnDelay_k_AES_ML_TIME_SEC (0.02F)

/* Computed Parameter: rtCP_Constant12_Value_k
 * Referenced by: '<S11>/Constant12'
 */
#define rtCP_Constant12_Value_k        (1.0F)

/* Computed Parameter: rtCP_Constant13_Value_a
 * Referenced by: '<S11>/Constant13'
 */
#define rtCP_Constant13_Value_a        (0.0F)

/* Computed Parameter: rtCP_Constant14_Value_j
 * Referenced by: '<S11>/Constant14'
 */
#define rtCP_Constant14_Value_j        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_jf
 * Referenced by: '<S53>/Constant'
 */
#define rtCP_Constant_Value_jf         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_l5
 * Referenced by: '<S54>/Constant'
 */
#define rtCP_Constant_Value_l5         (0.0F)

/* Computed Parameter: rtCP_k_Reset_I_IntoCurve_CurvRateThr_Value
 * Referenced by: '<S52>/k_Reset_I_IntoCurve_CurvRateThr'
 */
#define rtCP_k_Reset_I_IntoCurve_CurvRateThr_Value (2.0E-6F)

/* Computed Parameter: rtCP_k_Reset_I_IntoCurve_CurvThr_Value
 * Referenced by: '<S52>/k_Reset_I_IntoCurve_CurvThr'
 */
#define rtCP_k_Reset_I_IntoCurve_CurvThr_Value (0.000125F)

/* Computed Parameter: rtCP_k_Reset_I_OutCurve_CurvRateThr_Value
 * Referenced by: '<S52>/k_Reset_I_OutCurve_CurvRateThr'
 */
#define rtCP_k_Reset_I_OutCurve_CurvRateThr_Value (1.0E-6F)

/* Computed Parameter: rtCP_k_Reset_I_OutCurve_CurvThr2_Value
 * Referenced by: '<S52>/k_Reset_I_OutCurve_CurvThr2'
 */
#define rtCP_k_Reset_I_OutCurve_CurvThr2_Value (0.000167F)

/* Expression: single(10)
 * Referenced by: '<S58>/AbnormalHeadingThreshold'
 */
#define rtCP_AbnormalHeadingThreshold_Value (10.0F)

/* Expression: single(10)
 * Referenced by: '<S59>/AbnormalHeadingRateThreshold'
 */
#define rtCP_AbnormalHeadingRateThreshold_Value (10.0F)

/* Expression: k_LCK_Hed_PTermMax
 * Referenced by: '<S55>/k_LCK_Hed_PTermMax'
 */
#define rtCP_k_LCK_Hed_PTermMax_Value  (200.0F)

/* Expression: k_LCK_Hed_DTermMax
 * Referenced by: '<S55>/k_LCK_Hed_DTermMax'
 */
#define rtCP_k_LCK_Hed_DTermMax_Value  (200.0F)

/* Computed Parameter: rtCP_Constant_Value_i0
 * Referenced by: '<S20>/Constant'
 */
#define rtCP_Constant_Value_i0         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_m2
 * Referenced by: '<S56>/Constant'
 */
#define rtCP_Constant_Value_m2         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_f1
 * Referenced by: '<S56>/Constant1'
 */
#define rtCP_Constant1_Value_f1        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_no
 * Referenced by: '<S56>/Constant2'
 */
#define rtCP_Constant2_Value_no        (0.0F)

/* Computed Parameter: rtCP_Constant8_Value_au
 * Referenced by: '<S56>/Constant8'
 */
#define rtCP_Constant8_Value_au        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ox
 * Referenced by: '<S83>/Constant'
 */
#define rtCP_Constant_Value_ox         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gl
 * Referenced by: '<S84>/Constant'
 */
#define rtCP_Constant_Value_gl         (0.0F)

/* Expression: k_LCK_ParaSteerSpdFac_Swh
 * Referenced by: '<S78>/k_LCK_ParaSteerSpdFac_Swh'
 */
#define rtCP_k_LCK_ParaSteerSpdFac_Swh_Value (0.0F)

/* Expression: k_AES_LatCtrl_HeadPID_Kd
 * Referenced by: '<S81>/k_LCK_HedCtrl_Kd'
 */
#define rtCP_k_LCK_HedCtrl_Kd_Value    (1.6F)

/* Expression: k_AES_LatCtrl_HeadPID_Kp
 * Referenced by: '<S82>/k_LCK_HedCtrl_Kp'
 */
#define rtCP_k_LCK_HedCtrl_Kp_Value    (1.0F)

/* Expression: k_AES_OvrallSteerRat
 * Referenced by: '<S20>/p_EmcAes_OvrallSteerRat'
 */
#define rtCP_p_EmcAes_OvrallSteerRat_Value (14.88F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S85>/Constant1'
 */
#define rtCP_Constant1_Value_ax        (0.0F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S85>/Constant3'
 */
#define rtCP_Constant3_Value_i5        (0.02F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S85>/Constant4'
 */
#define rtCP_Constant4_Value_ae        (0.0F)

/* Expression: k_LCK_Lat_PTermMax
 * Referenced by: '<S85>/k_LCK_Lat_PTermMax'
 */
#define rtCP_k_LCK_Lat_PTermMax_Value  (100.0F)

/* Computed Parameter: rtCP_Constant_Value_k5
 * Referenced by: '<S86>/Constant'
 */
#define rtCP_Constant_Value_k5         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ia
 * Referenced by: '<S86>/Constant1'
 */
#define rtCP_Constant1_Value_ia        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_bz
 * Referenced by: '<S86>/Constant2'
 */
#define rtCP_Constant2_Value_bz        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_lm
 * Referenced by: '<S86>/Constant3'
 */
#define rtCP_Constant3_Value_lm        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_dj
 * Referenced by: '<S86>/Constant4'
 */
#define rtCP_Constant4_Value_dj        (0.0F)

/* Computed Parameter: rtCP_Constant5_Value_n5
 * Referenced by: '<S86>/Constant5'
 */
#define rtCP_Constant5_Value_n5        (0.0F)

/* Computed Parameter: rtCP_Constant6_Value_b
 * Referenced by: '<S86>/Constant6'
 */
#define rtCP_Constant6_Value_b         (0.0F)

/* Computed Parameter: rtCP_Constant8_Value_g
 * Referenced by: '<S86>/Constant8'
 */
#define rtCP_Constant8_Value_g         (0.0F)

/* Expression: k_LCK_LatCtrl_PFac_Lft
 * Referenced by: '<S95>/k_LCK_LatCtrl_PFac_Lft'
 */
#define rtCP_k_LCK_LatCtrl_PFac_Lft_Value (1.0F)

/* Expression: k_LCK_LatCtrl_PFac_Rgt
 * Referenced by: '<S95>/k_LCK_LatCtrl_PFac_Rgt'
 */
#define rtCP_k_LCK_LatCtrl_PFac_Rgt_Value (1.0F)

/* Expression: k_LCK_LatCtrl_DFac_Lft
 * Referenced by: '<S95>/k_LCK_LatCtrl_DFac_Lft'
 */
#define rtCP_k_LCK_LatCtrl_DFac_Lft_Value (1.0F)

/* Expression: k_LCK_LatCtrl_DFac_Rgt
 * Referenced by: '<S95>/k_LCK_LatCtrl_DFac_Rgt'
 */
#define rtCP_k_LCK_LatCtrl_DFac_Rgt_Value (1.0F)

/* Computed Parameter: rtCP_Constant_Value_o1j
 * Referenced by: '<S108>/Constant'
 */
#define rtCP_Constant_Value_o1j        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pn
 * Referenced by: '<S109>/Constant'
 */
#define rtCP_Constant_Value_pn         (0.0F)

/* Expression: k_LCK_ParaSteerSpdFac_Swh
 * Referenced by: '<S99>/k_LCK_ParaSteerSpdFac_Swh'
 */
#define rtCP_k_LCK_ParaSteerSpdFac_Swh_Value_l (0.0F)

/* Expression: k_AES_LatCtrl_PosPID_Kd_Far
 * Referenced by: '<S105>/k_AES_LatCtrl_PosPID_Kd_Far'
 */
#define rtCP_k_AES_LatCtrl_PosPID_Kd_Far_Value (0.8F)

/* Expression: k_AES_LatCtrl_PosPID_Kd_Near
 * Referenced by: '<S105>/k_AES_LatCtrl_PosPID_Kd_Near'
 */
#define rtCP_k_AES_LatCtrl_PosPID_Kd_Near_Value (0.8F)

/* Expression: k_AES_LatCtrl_PosPID_KI
 * Referenced by: '<S106>/k_AES_LatCtrl_PosPID_KI'
 */
#define rtCP_k_AES_LatCtrl_PosPID_KI_Value (0.5F)

/* Expression: k_AES_LatCtrl_PosPID_Kp_Far
 * Referenced by: '<S107>/k_AES_LatCtrl_PosPID_Kp_Far'
 */
#define rtCP_k_AES_LatCtrl_PosPID_Kp_Far_Value (1.0F)

/* Expression: k_AES_LatCtrl_PosPID_Kp_Near
 * Referenced by: '<S107>/k_AES_LatCtrl_PosPID_Kp_Near'
 */
#define rtCP_k_AES_LatCtrl_PosPID_Kp_Near_Value (2.2F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S22>/Constant1'
 */
#define rtCP_Constant1_Value_ft        (0.02F)

/* Expression: k_LCK_SteerSpd_Swh
 * Referenced by: '<S22>/k_LCK_SteerSpd_Swh'
 */
#define rtCP_k_LCK_SteerSpd_Swh_Value  (1.0F)

/* Computed Parameter: rtCP_Constant_Value_av
 * Referenced by: '<S114>/Constant'
 */
#define rtCP_Constant_Value_av         (4.0E-5F)

/* Computed Parameter: rtCP_Constant_Value_b3
 * Referenced by: '<S115>/Constant'
 */
#define rtCP_Constant_Value_b3         (4.0E-5F)

/* Computed Parameter: rtCP_Constant1_Value_hq
 * Referenced by: '<S23>/Constant1'
 */
#define rtCP_Constant1_Value_hq        (0.0F)

/* Computed Parameter: rtCP_Constant22_Value_e
 * Referenced by: '<S23>/Constant22'
 */
#define rtCP_Constant22_Value_e        (0.0F)

/* Computed Parameter: rtCP_C_NEARZERO_Value_i
 * Referenced by: '<S24>/C_NEARZERO'
 */
#define rtCP_C_NEARZERO_Value_i        (0.0001F)

/* Computed Parameter: rtCP_Constant_Value_d2
 * Referenced by: '<S118>/Constant'
 */
#define rtCP_Constant_Value_d2         (4.0E-5F)

/* Computed Parameter: rtCP_Constant_Value_i1
 * Referenced by: '<S119>/Constant'
 */
#define rtCP_Constant_Value_i1         (4.0E-5F)

/* Computed Parameter: rtCP_Constant2_Value_bm
 * Referenced by: '<S24>/Constant2'
 */
#define rtCP_Constant2_Value_bm        (1.0F)

/* Computed Parameter: rtCP_Constant22_Value_j
 * Referenced by: '<S24>/Constant22'
 */
#define rtCP_Constant22_Value_j        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_cd
 * Referenced by: '<S24>/Constant3'
 */
#define rtCP_Constant3_Value_cd        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_kk
 * Referenced by: '<S12>/Constant1'
 */
#define rtCP_Constant1_Value_kk        (-3.375F)

/* Computed Parameter: rtCP_Constant2_Value_c2
 * Referenced by: '<S12>/Constant2'
 */
#define rtCP_Constant2_Value_c2        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_dv
 * Referenced by: '<S12>/Constant3'
 */
#define rtCP_Constant3_Value_dv        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_nb
 * Referenced by: '<S12>/Constant4'
 */
#define rtCP_Constant4_Value_nb        (0.0F)

/* Computed Parameter: rtCP_Constant5_Value_j
 * Referenced by: '<S12>/Constant5'
 */
#define rtCP_Constant5_Value_j         (3.375F)

/* Computed Parameter: rtCP_Constant6_Value_jt
 * Referenced by: '<S12>/Constant6'
 */
#define rtCP_Constant6_Value_jt        (0.0F)

/* Computed Parameter: rtCP_Constant7_Value_cc
 * Referenced by: '<S12>/Constant7'
 */
#define rtCP_Constant7_Value_cc        (0.0F)

/* Computed Parameter: rtCP_Constant8_Value_n
 * Referenced by: '<S12>/Constant8'
 */
#define rtCP_Constant8_Value_n         (0.2F)

/* Computed Parameter: rtCP_Constant9_Value_p1w
 * Referenced by: '<S12>/Constant9'
 */
#define rtCP_Constant9_Value_p1w       (0.0F)

/* Computed Parameter: rtCP_k_LCK_Dy_VehInCurvLanCentLowLmt_Value
 * Referenced by: '<S128>/k_LCK_Dy_VehInCurvLanCentLowLmt'
 */
#define rtCP_k_LCK_Dy_VehInCurvLanCentLowLmt_Value (0.25F)

/* Computed Parameter: rtCP_k_LCK_Dy_VehInCurvLanCentUpLmt_Value
 * Referenced by: '<S128>/k_LCK_Dy_VehInCurvLanCentUpLmt'
 */
#define rtCP_k_LCK_Dy_VehInCurvLanCentUpLmt_Value (0.35F)

/* Computed Parameter: rtCP_k_LCK_Dy_VehInStraLanCentLowLmt_Value
 * Referenced by: '<S128>/k_LCK_Dy_VehInStraLanCentLowLmt'
 */
#define rtCP_k_LCK_Dy_VehInStraLanCentLowLmt_Value (0.2F)

/* Computed Parameter: rtCP_k_LCK_Dy_VehInStraLanCentUpLmt_Value
 * Referenced by: '<S128>/k_LCK_Dy_VehInStraLanCentUpLmt'
 */
#define rtCP_k_LCK_Dy_VehInStraLanCentUpLmt_Value (0.3F)

/* Computed Parameter: rtCP_k_LCK_VehInCurvRadUpLmt_Value
 * Referenced by: '<S129>/k_LCK_VehInCurvRadUpLmt'
 */
#define rtCP_k_LCK_VehInCurvRadUpLmt_Value (4000.0F)

/* Computed Parameter: rtCP_k_LCK_VehInCurvRadLowLmt_Value
 * Referenced by: '<S129>/k_LCK_VehInCurvRadLowLmt'
 */
#define rtCP_k_LCK_VehInCurvRadLowLmt_Value (3800.0F)

/* Computed Parameter: rtCP_Constant_Value_er
 * Referenced by: '<S133>/Constant'
 */
#define rtCP_Constant_Value_er         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_es
 * Referenced by: '<S134>/Constant'
 */
#define rtCP_Constant_Value_es         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kf
 * Referenced by: '<S135>/Constant'
 */
#define rtCP_Constant_Value_kf         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ao
 * Referenced by: '<S136>/Constant'
 */
#define rtCP_Constant_Value_ao         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dt
 * Referenced by: '<S137>/Constant'
 */
#define rtCP_Constant_Value_dt         (0.0F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S34>/Constant1'
 */
#define rtCP_Constant1_Value_gb        (0.02F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S36>/Constant1'
 */
#define rtCP_Constant1_Value_jo        (0.02F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S37>/Constant1'
 */
#define rtCP_Constant1_Value_bb        (0.02F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S38>/Constant1'
 */
#define rtCP_Constant1_Value_ml        (0.02F)

/* Expression: k_AES_OvrallSteerRat
 * Referenced by: '<S39>/p_EmcAes_OvrallSteerRat'
 */
#define rtCP_p_EmcAes_OvrallSteerRat_Value_l (14.88F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S40>/Constant1'
 */
#define rtCP_Constant1_Value_gvr       (0.02F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S41>/Constant1'
 */
#define rtCP_Constant1_Value_ht        (0.02F)

/* Computed Parameter: rtCP_Constant_Value_hn
 * Referenced by: '<S171>/Constant'
 */
#define rtCP_Constant_Value_hn         (0.0F)

/* Computed Parameter: rtCP_THRLEVEL_Value
 * Referenced by: '<S172>/THRLEVEL'
 */
#define rtCP_THRLEVEL_Value            (2.0F)

/* Computed Parameter: rtCP_THRSHAKE2_Value
 * Referenced by: '<S172>/THRSHAKE2'
 */
#define rtCP_THRSHAKE2_Value           (0.8F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S183>/Constant4'
 */
#define rtCP_Constant4_Value_id        (0.02F)

/* Expression: k_AdjustComp_sustaintime
 * Referenced by: '<S178>/k_AdjustComp_sustaintime'
 */
#define rtCP_k_AdjustComp_sustaintime_Value (2.0F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S183>/Constant1'
 */
#define rtCP_Constant1_Value_gi        (0.02F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S183>/Constant3'
 */
#define rtCP_Constant3_Value_f         (0.02F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S183>/Constant2'
 */
#define rtCP_Constant2_Value_oe        (0.02F)

/* Computed Parameter: rtCP_Constant_Value_jk
 * Referenced by: '<S193>/Constant'
 */
#define rtCP_Constant_Value_jk         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_iq
 * Referenced by: '<S194>/Constant'
 */
#define rtCP_Constant_Value_iq         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ev
 * Referenced by: '<S195>/Constant'
 */
#define rtCP_Constant_Value_ev         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ff
 * Referenced by: '<S196>/Constant'
 */
#define rtCP_Constant_Value_ff         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mv
 * Referenced by: '<S197>/Constant'
 */
#define rtCP_Constant_Value_mv         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_is
 * Referenced by: '<S199>/Constant'
 */
#define rtCP_Constant_Value_is         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_m0i
 * Referenced by: '<S201>/Constant'
 */
#define rtCP_Constant_Value_m0i        (0.0F)

/* Expression: const
 * Referenced by: '<S202>/Constant'
 */
#define rtCP_Constant_Value_jn         (10.0F)

/* Computed Parameter: rtCP_Constant_Value_hf
 * Referenced by: '<S203>/Constant'
 */
#define rtCP_Constant_Value_hf         (0.0F)

/* Expression: k_AdjustComp_OffsetThr_m
 * Referenced by: '<S178>/k_AdjustComp_OffsetThr_m'
 */
#define rtCP_k_AdjustComp_OffsetThr_m_Value (0.1F)

/* Expression: k_AdjustCompStep
 * Referenced by: '<S178>/k_AdjustCompStep'
 */
#define rtCP_k_AdjustCompStep_Value    (0.1F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S178>/Constant4'
 */
#define rtCP_Constant4_Value_m         (0.02F)

/* Expression: k_AdjustStepTime
 * Referenced by: '<S178>/k_AdjustStepTime'
 */
#define rtCP_k_AdjustStepTime_Value    (2.0F)

/* Expression: k_AdjustThr_basedIniValue
 * Referenced by: '<S178>/k_AdjustThr'
 */
#define rtCP_k_AdjustThr_Value         (0.3F)

/* Computed Parameter: rtCP_k_LCK_StrWhlAngComp_RampTime_Value
 * Referenced by: '<S209>/k_LCK_StrWhlAngComp_RampTime'
 */
#define rtCP_k_LCK_StrWhlAngComp_RampTime_Value (2.0F)

/* Expression: k_LCK_StrWhlAngCompConst
 * Referenced by: '<S179>/k_LCK_StrWhlAngCompConst'
 */
#define rtCP_k_LCK_StrWhlAngCompConst_Value (0.7F)

/* Expression: k_StopSWALimitThr
 * Referenced by: '<S179>/k_StopSWALimitThr'
 */
#define rtCP_k_StopSWALimitThr_Value   (0.3F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S181>/Constant2'
 */
#define rtCP_Constant2_Value_eo        (0.0F)

/* Expression: k_LCK_MaxTorqCmdLmt
 * Referenced by: '<S168>/k_LCK_MaxTorqCmdLmt'
 */
#define rtCP_k_LCK_MaxTorqCmdLmt_Value (80.0F)

/* Expression: k_LCK_RmpUpEn_TorqCmd
 * Referenced by: '<S181>/k_LCK_RmpUpEn_TorqCmd'
 */
#define rtCP_k_LCK_RmpUpEn_TorqCmd_Value (1.0F)

/* Expression: k_LCK_RmpDwnEn_TorqCmd
 * Referenced by: '<S181>/k_LCK_RmpDwnEn_TorqCmd'
 */
#define rtCP_k_LCK_RmpDwnEn_TorqCmd_Value (1.0F)

/* Computed Parameter: rtCP_Constant1_Value_jq
 * Referenced by: '<S169>/Constant1'
 */
#define rtCP_Constant1_Value_jq        (0.0F)

/* Computed Parameter: rtCP_const_Value_ai
 * Referenced by: '<S169>/const'
 */
#define rtCP_const_Value_ai            (1000.0F)

/* Computed Parameter: rtCP_const1_Value_ee
 * Referenced by: '<S169>/const1'
 */
#define rtCP_const1_Value_ee           (1000.0F)

/* Computed Parameter: rtCP_Constant7_Value_d
 * Referenced by: '<S3>/Constant7'
 */
#define rtCP_Constant7_Value_d         (0.0F)

/* Expression: k_AES_ML_TIME_SEC
 * Referenced by: '<S13>/Constant1'
 */
#define rtCP_Constant1_Value_kg        (0.02F)

/* Computed Parameter: rtCP_Constant_Value_hb
 * Referenced by: '<S245>/Constant'
 */
#define rtCP_Constant_Value_hb         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hm
 * Referenced by: '<S248>/Constant'
 */
#define rtCP_Constant_Value_hm         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pf2
 * Referenced by: '<S4>/Constant'
 */
#define rtCP_Constant_Value_pf2        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_ho
 * Referenced by: '<S9>/Constant4'
 */
#define rtCP_Constant4_Value_ho        (0.75F)

/* Computed Parameter: rtCP_Constant1_Value_ai
 * Referenced by: '<S270>/Constant1'
 */
#define rtCP_Constant1_Value_ai        (1.83F)

/* Computed Parameter: rtCP_Constant2_Value_kb
 * Referenced by: '<S270>/Constant2'
 */
#define rtCP_Constant2_Value_kb        (2.0F)

/* Computed Parameter: rtCP_Constant3_Value_bz
 * Referenced by: '<S270>/Constant3'
 */
#define rtCP_Constant3_Value_bz        (2.0F)

/* Computed Parameter: rtCP_Constant5_Value_b
 * Referenced by: '<S270>/Constant5'
 */
#define rtCP_Constant5_Value_b         (-5.1F)

/* Computed Parameter: rtCP_Constant6_Value_by
 * Referenced by: '<S270>/Constant6'
 */
#define rtCP_Constant6_Value_by        (4.7F)

/* Computed Parameter: rtCP_Constant7_Value_bv
 * Referenced by: '<S270>/Constant7'
 */
#define rtCP_Constant7_Value_bv        (-1.7F)

/* Computed Parameter: rtCP_Constant_Value_g0
 * Referenced by: '<S301>/Constant'
 */
#define rtCP_Constant_Value_g0         (0.01F)

/* Computed Parameter: rtCP_Constant_Value_p1
 * Referenced by: '<S307>/Constant'
 */
#define rtCP_Constant_Value_p1         (0.01F)

/* Computed Parameter: rtCP_Constant_Value_hdo
 * Referenced by: '<S304>/Constant'
 */
#define rtCP_Constant_Value_hdo        (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ly
 * Referenced by: '<S310>/Constant'
 */
#define rtCP_Constant_Value_ly         (0.01F)

/* Expression: const
 * Referenced by: '<S276>/Constant'
 */
#define rtCP_Constant_Value_cl         (7.0F)

/* Expression: const
 * Referenced by: '<S278>/Constant'
 */
#define rtCP_Constant_Value_jc         (7.0F)

/* Expression: k_AES_A1Diff
 * Referenced by: '<S317>/k_ESS_A1Diff'
 */
#define rtCP_k_ESS_A1Diff_Value        (0.1F)

/* Expression: k_AES_A1Diff
 * Referenced by: '<S318>/k_ESS_A1Diff'
 */
#define rtCP_k_ESS_A1Diff_Value_j      (0.1F)

/* Computed Parameter: rtCP_Constant1_Value_js
 * Referenced by: '<S281>/Constant1'
 */
#define rtCP_Constant1_Value_js        (2.0F)

/* Computed Parameter: rtCP_Constant19_Value_b
 * Referenced by: '<S281>/Constant19'
 */
#define rtCP_Constant19_Value_b        (1.75F)

/* Computed Parameter: rtCP_Constant20_Value_p
 * Referenced by: '<S281>/Constant20'
 */
#define rtCP_Constant20_Value_p        (-1.75F)

/* Computed Parameter: rtCP_Constant3_Value_ou
 * Referenced by: '<S281>/Constant3'
 */
#define rtCP_Constant3_Value_ou        (2.0F)

/* Computed Parameter: rtCP_Constant4_Value_m4
 * Referenced by: '<S281>/Constant4'
 */
#define rtCP_Constant4_Value_m4        (0.0F)

/* Computed Parameter: rtCP_Constant5_Value_o1
 * Referenced by: '<S281>/Constant5'
 */
#define rtCP_Constant5_Value_o1        (0.0F)

/* Computed Parameter: rtCP_Constant6_Value_m2
 * Referenced by: '<S281>/Constant6'
 */
#define rtCP_Constant6_Value_m2        (3.75F)

/* Computed Parameter: rtCP_Constant7_Value_na
 * Referenced by: '<S281>/Constant7'
 */
#define rtCP_Constant7_Value_na        (-0.2F)

/* Computed Parameter: rtCP_Constant8_Value_ek
 * Referenced by: '<S281>/Constant8'
 */
#define rtCP_Constant8_Value_ek        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_eth
 * Referenced by: '<S337>/Constant'
 */
#define rtCP_Constant_Value_eth        (0.01F)

/* Computed Parameter: rtCP_Constant_Value_hj
 * Referenced by: '<S343>/Constant'
 */
#define rtCP_Constant_Value_hj         (0.01F)

/* Computed Parameter: rtCP_Constant_Value_iy
 * Referenced by: '<S340>/Constant'
 */
#define rtCP_Constant_Value_iy         (0.01F)

/* Computed Parameter: rtCP_Constant_Value_je
 * Referenced by: '<S346>/Constant'
 */
#define rtCP_Constant_Value_je         (0.01F)

/* Computed Parameter: rtCP_Constant_Value_os
 * Referenced by: '<S368>/Constant'
 */
#define rtCP_Constant_Value_os         (2.0F)

/* Computed Parameter: rtCP_Constant_Value_il
 * Referenced by: '<S370>/Constant'
 */
#define rtCP_Constant_Value_il         (4.0F)

/* Computed Parameter: rtCP_Constant_Value_cd
 * Referenced by: '<S371>/Constant'
 */
#define rtCP_Constant_Value_cd         (3.0F)

/* Computed Parameter: rtCP_Constant_Value_fc
 * Referenced by: '<S372>/Constant'
 */
#define rtCP_Constant_Value_fc         (1.0F)

/* Computed Parameter: rtCP_Constant_Value_f3
 * Referenced by: '<S373>/Constant'
 */
#define rtCP_Constant_Value_f3         (4.0F)

/* Computed Parameter: rtCP_Constant_Value_m2c
 * Referenced by: '<S369>/Constant'
 */
#define rtCP_Constant_Value_m2c        (4.0F)

/* Computed Parameter: rtCP_Constant_Value_cr
 * Referenced by: '<S374>/Constant'
 */
#define rtCP_Constant_Value_cr         (2.0F)

/* Computed Parameter: rtCP_Constant_Value_lm
 * Referenced by: '<S375>/Constant'
 */
#define rtCP_Constant_Value_lm         (4.0F)

/* Computed Parameter: rtCP_Constant_Value_eo
 * Referenced by: '<S376>/Constant'
 */
#define rtCP_Constant_Value_eo         (3.0F)

/* Computed Parameter: rtCP_Constant_Value_b1
 * Referenced by: '<S377>/Constant'
 */
#define rtCP_Constant_Value_b1         (2.0F)

/* Computed Parameter: rtCP_Constant_Value_jz
 * Referenced by: '<S397>/Constant'
 */
#define rtCP_Constant_Value_jz         (1.0F)

/* Expression: k_AES_RoadEdgeValid_MaxThd
 * Referenced by: '<S282>/Constant'
 */
#define rtCP_Constant_Value_cp         (15.0F)

/* Expression: k_AES_RoadEdgeValid_MinThd
 * Referenced by: '<S282>/Constant1'
 */
#define rtCP_Constant1_Value_jg        (5.0F)

/* Computed Parameter: rtCP_Constant_Value_fn
 * Referenced by: '<S399>/Constant'
 */
#define rtCP_Constant_Value_fn         (1.0F)

/* Expression: k_AES_RoadEdgeValid_MaxThd
 * Referenced by: '<S283>/Constant'
 */
#define rtCP_Constant_Value_eov        (15.0F)

/* Expression: k_AES_RoadEdgeValid_MinThd
 * Referenced by: '<S283>/Constant1'
 */
#define rtCP_Constant1_Value_dc        (5.0F)

/* Computed Parameter: rtCP_Constant11_Value_lw
 * Referenced by: '<S260>/Constant11'
 */
#define rtCP_Constant11_Value_lw       (4.0F)

/* Computed Parameter: rtCP_Constant12_Value_b
 * Referenced by: '<S260>/Constant12'
 */
#define rtCP_Constant12_Value_b        (1.0F)

/* Computed Parameter: rtCP_Constant24_Value_i
 * Referenced by: '<S260>/Constant24'
 */
#define rtCP_Constant24_Value_i        (4.0F)

/* Computed Parameter: rtCP_Constant25_Value_c
 * Referenced by: '<S260>/Constant25'
 */
#define rtCP_Constant25_Value_c        (1.0F)

/* Computed Parameter: rtCP_Constant17_Value_gt
 * Referenced by: '<S260>/Constant17'
 */
#define rtCP_Constant17_Value_gt       (5.0F)

/* Computed Parameter: rtCP_Constant18_Value_j
 * Referenced by: '<S260>/Constant18'
 */
#define rtCP_Constant18_Value_j        (0.0F)

/* Computed Parameter: rtCP_Constant19_Value_l
 * Referenced by: '<S260>/Constant19'
 */
#define rtCP_Constant19_Value_l        (0.0F)

/* Computed Parameter: rtCP_Constant20_Value_m
 * Referenced by: '<S260>/Constant20'
 */
#define rtCP_Constant20_Value_m        (0.0F)

/* Computed Parameter: rtCP_Constant30_Value
 * Referenced by: '<S260>/Constant30'
 */
#define rtCP_Constant30_Value          (-5.0F)

/* Computed Parameter: rtCP_Constant31_Value
 * Referenced by: '<S260>/Constant31'
 */
#define rtCP_Constant31_Value          (0.0F)

/* Computed Parameter: rtCP_Constant32_Value_c
 * Referenced by: '<S260>/Constant32'
 */
#define rtCP_Constant32_Value_c        (0.0F)

/* Computed Parameter: rtCP_Constant34_Value
 * Referenced by: '<S260>/Constant34'
 */
#define rtCP_Constant34_Value          (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_la
 * Referenced by: '<S5>/Constant1'
 */
#define rtCP_Constant1_Value_la        (0.0F)

/* Computed Parameter: rtCP_Constant10_Value_fg
 * Referenced by: '<S5>/Constant10'
 */
#define rtCP_Constant10_Value_fg       (0.0F)

/* Computed Parameter: rtCP_Constant24_Value_iz
 * Referenced by: '<S5>/Constant24'
 */
#define rtCP_Constant24_Value_iz       (0.0F)

/* Computed Parameter: rtCP_Constant5_Value_nm
 * Referenced by: '<S5>/Constant5'
 */
#define rtCP_Constant5_Value_nm        (0.0F)

/* Computed Parameter: rtCP_Constant6_Value_hm
 * Referenced by: '<S5>/Constant6'
 */
#define rtCP_Constant6_Value_hm        (0.0F)

/* Computed Parameter: rtCP_Constant9_Value_ev
 * Referenced by: '<S5>/Constant9'
 */
#define rtCP_Constant9_Value_ev        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lq
 * Referenced by: '<S268>/Constant'
 */
#define rtCP_Constant_Value_lq         (100.0F)

/* Expression: k_AES_t_DriverStrJudge_OnDly
 * Referenced by: '<S268>/Constant9'
 */
#define rtCP_Constant9_Value_b         (0.04F)

/* Expression: k_AES_PlnMaxAyWeight
 * Referenced by: '<S414>/Constant'
 */
#define rtCP_Constant_Value_eh         (10.0F)

/* Expression: k_AES_ObsLatYWeight
 * Referenced by: '<S414>/Constant1'
 */
#define rtCP_Constant1_Value_h2        (100.0F)

/* Expression: k_AES_VehLatYWeight
 * Referenced by: '<S414>/Constant2'
 */
#define rtCP_Constant2_Value_g2        (10.0F)

/* Computed Parameter: rtCP_Constant3_Value_n2
 * Referenced by: '<S414>/Constant3'
 */
#define rtCP_Constant3_Value_n2        (0.0F)

/* Expression: k_AES_PlnMaxAyWeight
 * Referenced by: '<S415>/Constant'
 */
#define rtCP_Constant_Value_gr         (10.0F)

/* Expression: k_AES_ObsLatYWeight
 * Referenced by: '<S415>/Constant1'
 */
#define rtCP_Constant1_Value_fm        (100.0F)

/* Expression: k_AES_VehLatYWeight
 * Referenced by: '<S415>/Constant2'
 */
#define rtCP_Constant2_Value_pg        (10.0F)

/* Computed Parameter: rtCP_Constant3_Value_f3
 * Referenced by: '<S415>/Constant3'
 */
#define rtCP_Constant3_Value_f3        (0.0F)

/* Computed Parameter: rtCP_k_WheelBase_Value_d
 * Referenced by: '<S6>/k_WheelBase'
 */
#define rtCP_k_WheelBase_Value_d       (2.92F)

/* Computed Parameter: rtCP_k_LineHighConfThr_Value
 * Referenced by: '<S880>/k_LineHighConfThr'
 */
#define rtCP_k_LineHighConfThr_Value   (0.5F)

/* Computed Parameter: rtCP_k_LineHighConfThr_Value_n
 * Referenced by: '<S885>/k_LineHighConfThr'
 */
#define rtCP_k_LineHighConfThr_Value_n (0.5F)

/* Computed Parameter: rtCP_k_LineHighConfThr_Value_j
 * Referenced by: '<S890>/k_LineHighConfThr'
 */
#define rtCP_k_LineHighConfThr_Value_j (0.5F)

/* Computed Parameter: rtCP_k_LineHighConfThr_Value_o
 * Referenced by: '<S904>/k_LineHighConfThr'
 */
#define rtCP_k_LineHighConfThr_Value_o (0.5F)

/* Computed Parameter: rtCP_Constant24_Value_n
 * Referenced by: '<S915>/Constant24'
 */
#define rtCP_Constant24_Value_n        (0.0F)

/* Computed Parameter: rtCP_Constant25_Value_g
 * Referenced by: '<S915>/Constant25'
 */
#define rtCP_Constant25_Value_g        (0.0F)

/* Computed Parameter: rtCP_Constant19_Value_i
 * Referenced by: '<S915>/Constant19'
 */
#define rtCP_Constant19_Value_i        (0.0F)

/* Computed Parameter: rtCP_Constant20_Value_i
 * Referenced by: '<S915>/Constant20'
 */
#define rtCP_Constant20_Value_i        (1.0F)

/* Computed Parameter: rtCP_Constant21_Value_i
 * Referenced by: '<S915>/Constant21'
 */
#define rtCP_Constant21_Value_i        (1.0F)

/* Computed Parameter: rtCP_Constant23_Value
 * Referenced by: '<S915>/Constant23'
 */
#define rtCP_Constant23_Value          (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_kl
 * Referenced by: '<S925>/Constant2'
 */
#define rtCP_Constant2_Value_kl        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ct
 * Referenced by: '<S934>/Constant'
 */
#define rtCP_Constant_Value_ct         (1.0F)

/* Computed Parameter: rtCP_Constant_Value_fe
 * Referenced by: '<S923>/Constant'
 */
#define rtCP_Constant_Value_fe         (100.0F)

/* Computed Parameter: rtCP_Constant2_Value_af
 * Referenced by: '<S923>/Constant2'
 */
#define rtCP_Constant2_Value_af        (100.0F)

/* Computed Parameter: rtCP_Constant4_Value_o
 * Referenced by: '<S923>/Constant4'
 */
#define rtCP_Constant4_Value_o         (1.0F)

/* Computed Parameter: rtCP_Constant_Value_kk
 * Referenced by: '<S924>/Constant'
 */
#define rtCP_Constant_Value_kk         (100.0F)

/* Computed Parameter: rtCP_Constant2_Value_kw
 * Referenced by: '<S924>/Constant2'
 */
#define rtCP_Constant2_Value_kw        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_di
 * Referenced by: '<S924>/Constant3'
 */
#define rtCP_Constant3_Value_di        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_l
 * Referenced by: '<S924>/Constant4'
 */
#define rtCP_Constant4_Value_l         (0.0F)

/* Computed Parameter: rtCP_Constant8_Value_eq
 * Referenced by: '<S924>/Constant8'
 */
#define rtCP_Constant8_Value_eq        (3.375F)

/* Computed Parameter: rtCP_Constant14_Value_d5
 * Referenced by: '<S916>/Constant14'
 */
#define rtCP_Constant14_Value_d5       (0.5F)

/* Computed Parameter: rtCP_Constant24_Value_p
 * Referenced by: '<S939>/Constant24'
 */
#define rtCP_Constant24_Value_p        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_gu
 * Referenced by: '<S939>/Constant4'
 */
#define rtCP_Constant4_Value_gu        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ls
 * Referenced by: '<S939>/Constant1'
 */
#define rtCP_Constant1_Value_ls        (0.0F)

/* Computed Parameter: rtCP_Constant17_Value_a
 * Referenced by: '<S939>/Constant17'
 */
#define rtCP_Constant17_Value_a        (0.0F)

/* Computed Parameter: rtCP_Constant18_Value_n
 * Referenced by: '<S939>/Constant18'
 */
#define rtCP_Constant18_Value_n        (1.0F)

/* Computed Parameter: rtCP_Constant19_Value_m
 * Referenced by: '<S939>/Constant19'
 */
#define rtCP_Constant19_Value_m        (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_cc
 * Referenced by: '<S949>/Constant2'
 */
#define rtCP_Constant2_Value_cc        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_eg
 * Referenced by: '<S958>/Constant'
 */
#define rtCP_Constant_Value_eg         (1.0F)

/* Computed Parameter: rtCP_Constant_Value_fea
 * Referenced by: '<S947>/Constant'
 */
#define rtCP_Constant_Value_fea        (100.0F)

/* Computed Parameter: rtCP_Constant2_Value_ol
 * Referenced by: '<S947>/Constant2'
 */
#define rtCP_Constant2_Value_ol        (100.0F)

/* Computed Parameter: rtCP_Constant4_Value_hv
 * Referenced by: '<S947>/Constant4'
 */
#define rtCP_Constant4_Value_hv        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_aj
 * Referenced by: '<S948>/Constant'
 */
#define rtCP_Constant_Value_aj         (100.0F)

/* Computed Parameter: rtCP_Constant2_Value_md
 * Referenced by: '<S948>/Constant2'
 */
#define rtCP_Constant2_Value_md        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_jm
 * Referenced by: '<S948>/Constant3'
 */
#define rtCP_Constant3_Value_jm        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_oc
 * Referenced by: '<S948>/Constant4'
 */
#define rtCP_Constant4_Value_oc        (0.0F)

/* Computed Parameter: rtCP_Constant8_Value_l
 * Referenced by: '<S948>/Constant8'
 */
#define rtCP_Constant8_Value_l         (-3.375F)

/* Computed Parameter: rtCP_Constant14_Value_o
 * Referenced by: '<S940>/Constant14'
 */
#define rtCP_Constant14_Value_o        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_hi
 * Referenced by: '<S965>/Constant'
 */
#define rtCP_Constant_Value_hi         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pl
 * Referenced by: '<S967>/Constant'
 */
#define rtCP_Constant_Value_pl         (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_a4
 * Referenced by: '<S971>/Constant3'
 */
#define rtCP_Constant3_Value_a4        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_hk
 * Referenced by: '<S973>/Constant'
 */
#define rtCP_Constant_Value_hk         (0.0F)

/* Expression: k_AES_Dis_EgoRAxleToFBumper
 * Referenced by: '<S8>/Constant1'
 */
#define rtCP_Constant1_Value_od        (3.9F)

/* Computed Parameter: rtCP_Constant11_Value_k
 * Referenced by: '<S8>/Constant11'
 */
#define rtCP_Constant11_Value_k        (2.1F)

/* Computed Parameter: rtCP_Constant12_Value_kr
 * Referenced by: '<S8>/Constant12'
 */
#define rtCP_Constant12_Value_kr       (4.8F)

/* Expression: k_AES_FCWObsSlowSpd_OnDly
 * Referenced by: '<S8>/Constant27'
 */
#define rtCP_Constant27_Value_m        (0.5F)

/* Computed Parameter: rtCP_Constant3_Value_k1
 * Referenced by: '<S8>/Constant3'
 */
#define rtCP_Constant3_Value_k1        (150.0F)

/* Computed Parameter: rtCP_Constant4_Value_nw
 * Referenced by: '<S8>/Constant4'
 */
#define rtCP_Constant4_Value_nw        (10.0F)

/* Computed Parameter: rtCP_Constant5_Value_io
 * Referenced by: '<S8>/Constant5'
 */
#define rtCP_Constant5_Value_io        (0.0F)

/* Computed Parameter: rtCP_Constant6_Value_nz
 * Referenced by: '<S8>/Constant6'
 */
#define rtCP_Constant6_Value_nz        (1.0F)

/* Expression: k_AES_ML_TIME_SEC
 * Referenced by: '<S8>/Constant7'
 */
#define rtCP_Constant7_Value_eq        (0.02F)

/* Computed Parameter: rtCP_Constant8_Value_mw
 * Referenced by: '<S8>/Constant8'
 */
#define rtCP_Constant8_Value_mw        (-0.5F)

/* Expression: k_AES_ML_TIME_SEC
 * Referenced by: '<S985>/FSA_AES_SAMPLE_TIME'
 */
#define rtCP_FSA_AES_SAMPLE_TIME_Value (0.02F)

/* Expression: k_AES_EgoAOverGndObsvrL1
 * Referenced by: '<S985>/p_FsaAes_EgoAOverGndObsvrL1'
 */
#define rtCP_p_FsaAes_EgoAOverGndObsvrL1_Value (1.0F)

/* Expression: k_AES_EgoAOverGndObsvrL2
 * Referenced by: '<S985>/p_FsaAes_EgoAOverGndObsvrL2'
 */
#define rtCP_p_FsaAes_EgoAOverGndObsvrL2_Value (5.0F)

/* Expression: k_AES_DefaultTTC
 * Referenced by: '<S976>/p_FsaAes_DefaultTTC'
 */
#define rtCP_p_FsaAes_DefaultTTC_Value (20.0F)

/* Computed Parameter: rtCP_Constant1_Value_mt
 * Referenced by: '<S992>/Constant1'
 */
#define rtCP_Constant1_Value_mt        (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_h0
 * Referenced by: '<S992>/Constant2'
 */
#define rtCP_Constant2_Value_h0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fu
 * Referenced by: '<S994>/Constant'
 */
#define rtCP_Constant_Value_fu         (1.0F)

/* Computed Parameter: rtCP_Constant11_Value_cq
 * Referenced by: '<S981>/Constant11'
 */
#define rtCP_Constant11_Value_cq       (0.0F)

/* Computed Parameter: rtCP_Constant12_Value_a
 * Referenced by: '<S981>/Constant12'
 */
#define rtCP_Constant12_Value_a        (0.0F)

/* Computed Parameter: rtCP_Constant13_Value_k
 * Referenced by: '<S981>/Constant13'
 */
#define rtCP_Constant13_Value_k        (0.0F)

/* Computed Parameter: rtCP_Constant15_Value_b
 * Referenced by: '<S981>/Constant15'
 */
#define rtCP_Constant15_Value_b        (0.0F)

/* Computed Parameter: rtCP_Constant16_Value_i
 * Referenced by: '<S981>/Constant16'
 */
#define rtCP_Constant16_Value_i        (0.0F)

/* Computed Parameter: rtCP_Constant17_Value_o
 * Referenced by: '<S981>/Constant17'
 */
#define rtCP_Constant17_Value_o        (0.0F)

/* Computed Parameter: rtCP_Constant19_Value_a
 * Referenced by: '<S981>/Constant19'
 */
#define rtCP_Constant19_Value_a        (0.0F)

/* Computed Parameter: rtCP_Constant21_Value_j
 * Referenced by: '<S981>/Constant21'
 */
#define rtCP_Constant21_Value_j        (0.0F)

/* Computed Parameter: rtCP_Constant9_Value_k
 * Referenced by: '<S9>/Constant9'
 */
#define rtCP_Constant9_Value_k         (-1.0F)

/* Computed Parameter: rtCP_Constant2_Value_j1
 * Referenced by: '<S9>/Constant2'
 */
#define rtCP_Constant2_Value_j1        (-1.0F)

/* Computed Parameter: rtCP_Constant2_Value_dw
 * Referenced by: '<S1000>/Constant2'
 */
#define rtCP_Constant2_Value_dw        (0.0F)

/* Expression: k_LCK_ratio_steer_const
 * Referenced by: '<S1000>/Constant'
 */
#define rtCP_Constant_Value_b3v        (14.22F)

/* Computed Parameter: rtCP_Constant1_Value_kw
 * Referenced by: '<S1000>/Constant1'
 */
#define rtCP_Constant1_Value_kw        (57.3F)

/* Expression: k_AES_t_DriverAvoidObj_OnDly
 * Referenced by: '<S1000>/DriverAvoidObj_Ondelaytime'
 */
#define rtCP_DriverAvoidObj_Ondelaytime_Value (3.0F)

/* Computed Parameter: rtCP_Constant_Value_gf
 * Referenced by: '<S9>/Constant'
 */
#define rtCP_Constant_Value_gf         (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_po
 * Referenced by: '<S1024>/Constant3'
 */
#define rtCP_Constant3_Value_po        (1.0F)

/* Computed Parameter: rtCP_Constant3_Value_pq
 * Referenced by: '<S1025>/Constant3'
 */
#define rtCP_Constant3_Value_pq        (1.0F)

/* Expression: const
 * Referenced by: '<S1026>/Constant'
 */
#define rtCP_Constant_Value_nh         (135.0F)

/* Expression: const
 * Referenced by: '<S1027>/Constant'
 */
#define rtCP_Constant_Value_jeg        (50.0F)

/* Expression: const
 * Referenced by: '<S1032>/Constant'
 */
#define rtCP_Constant_Value_d3         (45.0F)

/* Expression: const
 * Referenced by: '<S1033>/Constant'
 */
#define rtCP_Constant_Value_c3         (140.0F)

/* Expression: const
 * Referenced by: '<S1034>/Constant'
 */
#define rtCP_Constant_Value_md         (0.25F)

/* Expression: const
 * Referenced by: '<S1035>/Constant'
 */
#define rtCP_Constant_Value_aiu        (5.0F)

/* Expression: const
 * Referenced by: '<S1038>/Constant'
 */
#define rtCP_Constant_Value_mg         (0.2F)

/* Expression: const
 * Referenced by: '<S1039>/Constant'
 */
#define rtCP_Constant_Value_lk         (65.0F)

/* Expression: const
 * Referenced by: '<S1040>/Constant'
 */
#define rtCP_Constant_Value_pg5        (70.0F)

/* Expression: const
 * Referenced by: '<S1041>/Constant'
 */
#define rtCP_Constant_Value_eq         (120.0F)

/* Expression: const
 * Referenced by: '<S1049>/Constant'
 */
#define rtCP_Constant_Value_c1         (2.5F)

/* Expression: const
 * Referenced by: '<S1050>/Constant'
 */
#define rtCP_Constant_Value_awu        (15.0F)

/* Expression: const
 * Referenced by: '<S1051>/Constant'
 */
#define rtCP_Constant_Value_js         (2.0F)

/* Expression: const
 * Referenced by: '<S1056>/Constant'
 */
#define rtCP_Constant_Value_ml         (15.0F)

/* Expression: const
 * Referenced by: '<S1061>/Constant'
 */
#define rtCP_Constant_Value_cj         (70.0F)

/* Expression: const
 * Referenced by: '<S1069>/Constant'
 */
#define rtCP_Constant_Value_nz         (25.0F)

/* Expression: const
 * Referenced by: '<S1070>/Constant'
 */
#define rtCP_Constant_Value_bo         (0.5F)

/* Expression: const
 * Referenced by: '<S1072>/Constant'
 */
#define rtCP_Constant_Value_cu         (10.0F)

/* Expression: const
 * Referenced by: '<S1073>/Constant'
 */
#define rtCP_Constant_Value_cb         (175.0F)

/* Expression: const
 * Referenced by: '<S1082>/Constant'
 */
#define rtCP_Constant_Value_ps         (60.0F)

/* Expression: const
 * Referenced by: '<S1093>/Constant'
 */
#define rtCP_Constant_Value_fr         (60.0F)

/* Expression: const
 * Referenced by: '<S1098>/Constant'
 */
#define rtCP_Constant_Value_n3         (135.0F)

/* Expression: const
 * Referenced by: '<S1099>/Constant'
 */
#define rtCP_Constant_Value_ay         (40.0F)

/* Expression: const
 * Referenced by: '<S1100>/Constant'
 */
#define rtCP_Constant_Value_hz         (35.0F)

/* Expression: const
 * Referenced by: '<S1101>/Constant'
 */
#define rtCP_Constant_Value_bbb        (140.0F)

/* Expression: const
 * Referenced by: '<S1103>/Constant'
 */
#define rtCP_Constant_Value_l53        (4.4F)

/* Expression: const
 * Referenced by: '<S1104>/Constant'
 */
#define rtCP_Constant_Value_ok         (100.0F)

/* Computed Parameter: rtCP_Constant_Value_dn
 * Referenced by: '<S1105>/Constant'
 */
#define rtCP_Constant_Value_dn         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_o3v
 * Referenced by: '<S1106>/Constant'
 */
#define rtCP_Constant_Value_o3v        (0.0F)

/* Expression: k_AES_t_EnterEgoYawRate_OnDly
 * Referenced by: '<S1016>/Constant'
 */
#define rtCP_Constant_Value_bc         (1.0F)

/* Expression: k_AES_t_EnterEgoAy_OnDly
 * Referenced by: '<S1016>/Constant1'
 */
#define rtCP_Constant1_Value_ef        (1.0F)

/* Expression: k_AES_AESAbortHTorq_SameDirThr
 * Referenced by: '<S1016>/Constant10'
 */
#define rtCP_Constant10_Value_l3       (5.0F)

/* Expression: k_AES_AESAbortHTorq_DiffDirThr
 * Referenced by: '<S1016>/Constant11'
 */
#define rtCP_Constant11_Value_g        (4.5F)

/* Expression: k_AES_ESAAbortHTorq_SameDirThr
 * Referenced by: '<S1016>/Constant12'
 */
#define rtCP_Constant12_Value_e        (5.0F)

/* Expression: k_AES_ESAAbortHTorq_DiffDirThr
 * Referenced by: '<S1016>/Constant13'
 */
#define rtCP_Constant13_Value_oq       (4.5F)

/* Expression: k_AES_t_AbortHandTorq_OnDly
 * Referenced by: '<S1016>/Constant14'
 */
#define rtCP_Constant14_Value_jl       (0.25F)

/* Expression: k_AES_t_AbortEgoAccelPer_OnDly
 * Referenced by: '<S1016>/Constant15'
 */
#define rtCP_Constant15_Value_g        (0.15F)

/* Expression: k_AES_t_AbortEgoBrakePer_OnDly
 * Referenced by: '<S1016>/Constant16'
 */
#define rtCP_Constant16_Value_g        (0.06F)

/* Expression: k_AES_t_AbortEgoYawRate_OnDly
 * Referenced by: '<S1016>/Constant17'
 */
#define rtCP_Constant17_Value_ax       (0.25F)

/* Expression: k_AES_t_AbortEgoAy_OnDly
 * Referenced by: '<S1016>/Constant18'
 */
#define rtCP_Constant18_Value_bn       (0.25F)

/* Expression: k_AES_t_AbortStrAng_OnDly
 * Referenced by: '<S1016>/Constant19'
 */
#define rtCP_Constant19_Value_e        (0.0F)

/* Expression: k_AES_t_EnterPedalPer_OnDly
 * Referenced by: '<S1016>/Constant2'
 */
#define rtCP_Constant2_Value_d0        (0.3F)

/* Expression: k_AES_t_AbortESCActive_OnDly
 * Referenced by: '<S1016>/Constant20'
 */
#define rtCP_Constant20_Value_b        (0.5F)

/* Expression: k_AES_CompletedC0_Thr
 * Referenced by: '<S1016>/Constant21'
 */
#define rtCP_Constant21_Value_j1       (0.2F)

/* Expression: k_AES_CompletedC1_Thr
 * Referenced by: '<S1016>/Constant22'
 */
#define rtCP_Constant22_Value_o        (0.02F)

/* Expression: k_AES_t_CompletedC0C1_OnDly
 * Referenced by: '<S1016>/Constant23'
 */
#define rtCP_Constant23_Value_l        (3.0F)

/* Expression: k_AES_FCWObstacleLatOverLap
 * Referenced by: '<S1016>/Constant24'
 */
#define rtCP_Constant24_Value_b        (2.5F)

/* Expression: k_AES_t_FCWObstacleValid_OnDly
 * Referenced by: '<S1016>/Constant27'
 */
#define rtCP_Constant27_Value_f        (0.04F)

/* Expression: k_AES_t_FCWObstacleValid_OnDly
 * Referenced by: '<S1016>/Constant29'
 */
#define rtCP_Constant29_Value_e        (0.04F)

/* Expression: k_AES_t_EnterPedalPer_OnDly
 * Referenced by: '<S1016>/Constant3'
 */
#define rtCP_Constant3_Value_n3        (0.3F)

/* Expression: k_AES_FCWObstacleLatOverLap
 * Referenced by: '<S1016>/Constant36'
 */
#define rtCP_Constant36_Value          (2.5F)

/* Expression: k_AES_t_EnterStrAng_OnDly
 * Referenced by: '<S1016>/Constant4'
 */
#define rtCP_Constant4_Value_nh        (0.2F)

/* Expression: k_AES_t_TTCValid_OnDly
 * Referenced by: '<S1016>/Constant5'
 */
#define rtCP_Constant5_Value_m         (0.04F)

/* Expression: k_AES_t_ExitStrAng_OnDly
 * Referenced by: '<S1016>/Constant6'
 */
#define rtCP_Constant6_Value_ch        (0.1F)

/* Expression: k_AES_t_TTCValid_OnDly
 * Referenced by: '<S1016>/Constant9'
 */
#define rtCP_Constant9_Value_d         (0.04F)

/* Computed Parameter: rtCP_Constant_Value_as3
 * Referenced by: '<S1142>/Constant'
 */
#define rtCP_Constant_Value_as3        (2.0F)

/* Computed Parameter: rtCP_Constant_Value_cg3
 * Referenced by: '<S1143>/Constant'
 */
#define rtCP_Constant_Value_cg3        (2.0F)

/* Computed Parameter: rtCP_Constant3_Value_b1
 * Referenced by: '<S1134>/Constant3'
 */
#define rtCP_Constant3_Value_b1        (1.0F)

/* Computed Parameter: rtCP_Constant3_Value_p1
 * Referenced by: '<S1135>/Constant3'
 */
#define rtCP_Constant3_Value_p1        (1.0F)

/* Expression: k_AES_CheckDriverAvoid_SafeDis
 * Referenced by: '<S9>/safedis'
 */
#define rtCP_safedis_Value             (0.15F)

/* Computed Parameter: rtCP_Constant_Value_ir
 * Referenced by: '<S1150>/Constant'
 */
#define rtCP_Constant_Value_ir         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jq
 * Referenced by: '<S1151>/Constant'
 */
#define rtCP_Constant_Value_jq         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ez
 * Referenced by: '<S1152>/Constant'
 */
#define rtCP_Constant_Value_ez         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ljb
 * Referenced by: '<S1153>/Constant'
 */
#define rtCP_Constant_Value_ljb        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_le
 * Referenced by: '<S1154>/Constant'
 */
#define rtCP_Constant_Value_le         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aq
 * Referenced by: '<S1155>/Constant'
 */
#define rtCP_Constant_Value_aq         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ix
 * Referenced by: '<S1156>/Constant'
 */
#define rtCP_Constant_Value_ix         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_px
 * Referenced by: '<S1157>/Constant'
 */
#define rtCP_Constant_Value_px         (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_nx
 * Referenced by: '<S5>/Gain'
 */
#define rtCP_Gain_Gain_nx              (3.6F)

/* Computed Parameter: rtCP_Gain_Gain_b1
 * Referenced by: '<S6>/Gain'
 */
#define rtCP_Gain_Gain_b1              (3.6F)

/* Computed Parameter: rtCP_Gain_Gain_iz
 * Referenced by: '<S10>/Gain'
 */
#define rtCP_Gain_Gain_iz              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_nw
 * Referenced by: '<S10>/Gain1'
 */
#define rtCP_Gain1_Gain_nw             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_a
 * Referenced by: '<S10>/Gain2'
 */
#define rtCP_Gain2_Gain_a              (-1.0F)

/* Computed Parameter: rtCP_Gain3_Gain_i
 * Referenced by: '<S10>/Gain3'
 */
#define rtCP_Gain3_Gain_i              (-1.0F)

/* Computed Parameter: rtCP_Gain4_Gain_h1
 * Referenced by: '<S10>/Gain4'
 */
#define rtCP_Gain4_Gain_h1             (-1.0F)

/* Computed Parameter: rtCP_Gain7_Gain_b
 * Referenced by: '<S10>/Gain7'
 */
#define rtCP_Gain7_Gain_b              (-1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_om
 * Referenced by: '<S10>/Gain8'
 */
#define rtCP_Gain8_Gain_om             (-1.0F)

/* Computed Parameter: rtCP_Gain9_Gain_cl
 * Referenced by: '<S10>/Gain9'
 */
#define rtCP_Gain9_Gain_cl             (-1.0F)

/* Expression: k_AES_minSPPLnWdth
 * Referenced by: '<S324>/ESS_MinLnWdth_Hyst4'
 */
#define rtCP_ESS_MinLnWdth_Hyst4_OnVal (2.7F)

/* Expression: k_AES_minSPPLnWdthHyst
 * Referenced by: '<S324>/ESS_MinLnWdth_Hyst4'
 */
#define rtCP_ESS_MinLnWdth_Hyst4_OffVal (2.6F)

/* Expression: k_AES_maxSPPLnWdth
 * Referenced by: '<S324>/ESS_MaxLnWdth_Hyst4'
 */
#define rtCP_ESS_MaxLnWdth_Hyst4_OnVal (4.4F)

/* Expression: k_AES_maxSPPLnWdthHyst
 * Referenced by: '<S324>/ESS_MaxLnWdth_Hyst4'
 */
#define rtCP_ESS_MaxLnWdth_Hyst4_OffVal (4.2F)

/* Computed Parameter: rtCP_Gain2_Gain_pc
 * Referenced by: '<S361>/Gain2'
 */
#define rtCP_Gain2_Gain_pc             (0.3333F)

/* Expression: k_AES_minLnWdth
 * Referenced by: '<S286>/AES_MinLnWdth_Hyst'
 */
#define rtCP_AES_MinLnWdth_Hyst_OnVal  (2.2F)

/* Expression: k_AES_minLnWdthHyst
 * Referenced by: '<S286>/AES_MinLnWdth_Hyst'
 */
#define rtCP_AES_MinLnWdth_Hyst_OffVal (2.0F)

/* Expression: k_AES_maxLnWdth
 * Referenced by: '<S286>/AES_MaxLnWdth_Hyst'
 */
#define rtCP_AES_MaxLnWdth_Hyst_OnVal  (4.6F)

/* Expression: k_AES_maxLnWdthHyst
 * Referenced by: '<S286>/AES_MaxLnWdth_Hyst'
 */
#define rtCP_AES_MaxLnWdth_Hyst_OffVal (4.5F)

/* Computed Parameter: rtCP_Gain_Gain_mh
 * Referenced by: '<S977>/Gain'
 */
#define rtCP_Gain_Gain_mh              (0.5F)

/* Computed Parameter: rtCP_Gain36_Gain
 * Referenced by: '<S915>/Gain36'
 */
#define rtCP_Gain36_Gain               (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_be
 * Referenced by: '<S977>/Gain1'
 */
#define rtCP_Gain1_Gain_be             (0.5F)

/* Computed Parameter: rtCP_Gain37_Gain
 * Referenced by: '<S915>/Gain37'
 */
#define rtCP_Gain37_Gain               (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_kr
 * Referenced by: '<S977>/Gain2'
 */
#define rtCP_Gain2_Gain_kr             (0.5F)

/* Computed Parameter: rtCP_Gain38_Gain_h
 * Referenced by: '<S915>/Gain38'
 */
#define rtCP_Gain38_Gain_h             (-1.0F)

/* Computed Parameter: rtCP_Gain3_Gain_fs
 * Referenced by: '<S977>/Gain3'
 */
#define rtCP_Gain3_Gain_fs             (0.5F)

/* Computed Parameter: rtCP_Gain39_Gain_j
 * Referenced by: '<S915>/Gain39'
 */
#define rtCP_Gain39_Gain_j             (-1.0F)

/* Computed Parameter: rtCP_Gain5_Gain_f
 * Referenced by: '<S925>/Gain5'
 */
#define rtCP_Gain5_Gain_f              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_br
 * Referenced by: '<S992>/Gain'
 */
#define rtCP_Gain_Gain_br              (0.5F)

/* Computed Parameter: rtCP_up5_mps_Threshold
 * Referenced by: '<S992>/0p5_mps'
 */
#define rtCP_up5_mps_Threshold         (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_er
 * Referenced by: '<S991>/Gain1'
 */
#define rtCP_Gain1_Gain_er             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_i3
 * Referenced by: '<S991>/Gain'
 */
#define rtCP_Gain_Gain_i3              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_fz
 * Referenced by: '<S981>/Gain'
 */
#define rtCP_Gain_Gain_fz              (1.0F)

/* Computed Parameter: rtCP_Gain6_Gain_o
 * Referenced by: '<S981>/Gain6'
 */
#define rtCP_Gain6_Gain_o              (-1.0F)

/* Computed Parameter: rtCP_Gain7_Gain_f
 * Referenced by: '<S981>/Gain7'
 */
#define rtCP_Gain7_Gain_f              (-1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_a2
 * Referenced by: '<S981>/Gain8'
 */
#define rtCP_Gain8_Gain_a2             (-1.0F)

/* Computed Parameter: rtCP_Gain9_Gain_g
 * Referenced by: '<S981>/Gain9'
 */
#define rtCP_Gain9_Gain_g              (-1.0F)

/* Computed Parameter: rtCP_Gain10_Gain_g
 * Referenced by: '<S981>/Gain10'
 */
#define rtCP_Gain10_Gain_g             (-1.0F)

/* Computed Parameter: rtCP_Gain11_Gain_i3
 * Referenced by: '<S981>/Gain11'
 */
#define rtCP_Gain11_Gain_i3            (-1.0F)

/* Computed Parameter: rtCP_Gain12_Gain_d
 * Referenced by: '<S981>/Gain12'
 */
#define rtCP_Gain12_Gain_d             (-1.0F)

/* Computed Parameter: rtCP_Gain13_Gain_io
 * Referenced by: '<S981>/Gain13'
 */
#define rtCP_Gain13_Gain_io            (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_fr
 * Referenced by: '<S976>/Gain'
 */
#define rtCP_Gain_Gain_fr              (2.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_hv
 * Referenced by: '<S976>/Saturation'
 */
#define rtCP_Saturation_UpperSat_hv    (100.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_bc
 * Referenced by: '<S976>/Saturation'
 */
#define rtCP_Saturation_LowerSat_bc    (0.01F)

/* Computed Parameter: rtCP_Relay_OnVal
 * Referenced by: '<S976>/Relay'
 */
#define rtCP_Relay_OnVal               (0.001F)

/* Computed Parameter: rtCP_Relay_OffVal
 * Referenced by: '<S976>/Relay'
 */
#define rtCP_Relay_OffVal              (-0.0001F)

/* Computed Parameter: rtCP_Relay_YOn
 * Referenced by: '<S976>/Relay'
 */
#define rtCP_Relay_YOn                 (1.0F)

/* Computed Parameter: rtCP_Relay_YOff
 * Referenced by: '<S976>/Relay'
 */
#define rtCP_Relay_YOff                (-1.0F)

/* Computed Parameter: rtCP_avoid2_UpperSat
 * Referenced by: '<S976>/avoid 2'
 */
#define rtCP_avoid2_UpperSat           (1.0E+6F)

/* Computed Parameter: rtCP_avoid2_LowerSat
 * Referenced by: '<S976>/avoid 2'
 */
#define rtCP_avoid2_LowerSat           (0.0F)

/* Computed Parameter: rtCP_Switch_Threshold
 * Referenced by: '<S976>/Switch'
 */
#define rtCP_Switch_Threshold          (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_g1
 * Referenced by: '<S8>/Gain1'
 */
#define rtCP_Gain1_Gain_g1             (3.6F)

/* Computed Parameter: rtCP_Gain5_Gain_a
 * Referenced by: '<S981>/Gain5'
 */
#define rtCP_Gain5_Gain_a              (1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_do
 * Referenced by: '<S8>/Gain2'
 */
#define rtCP_Gain2_Gain_do             (57.32F)

/* Computed Parameter: rtCP_Gain3_Gain_kt
 * Referenced by: '<S8>/Gain3'
 */
#define rtCP_Gain3_Gain_kt             (3.6F)

/* Computed Parameter: rtCP_Gain_Gain_me4
 * Referenced by: '<S8>/Gain'
 */
#define rtCP_Gain_Gain_me4             (57.32F)

/* Computed Parameter: rtCP_Gain4_Gain_el
 * Referenced by: '<S8>/Gain4'
 */
#define rtCP_Gain4_Gain_el             (3.6F)

/* Computed Parameter: rtCP_Saturation_UpperSat_e02
 * Referenced by: '<S8>/Saturation'
 */
#define rtCP_Saturation_UpperSat_e02   (150.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_a2
 * Referenced by: '<S8>/Saturation'
 */
#define rtCP_Saturation_LowerSat_a2    (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_i3
 * Referenced by: '<S923>/Gain1'
 */
#define rtCP_Gain1_Gain_i3             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_in
 * Referenced by: '<S923>/Gain'
 */
#define rtCP_Gain_Gain_in              (-1.0F)

/* Computed Parameter: rtCP_Gain12_Gain_p
 * Referenced by: '<S923>/Gain12'
 */
#define rtCP_Gain12_Gain_p             (-1.0F)

/* Computed Parameter: rtCP_Gain11_Gain_j
 * Referenced by: '<S923>/Gain11'
 */
#define rtCP_Gain11_Gain_j             (0.5F)

/* Computed Parameter: rtCP_Gain9_Gain_l
 * Referenced by: '<S923>/Gain9'
 */
#define rtCP_Gain9_Gain_l              (0.5F)

/* Computed Parameter: rtCP_Gain5_Gain_ez
 * Referenced by: '<S923>/Gain5'
 */
#define rtCP_Gain5_Gain_ez             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_iy
 * Referenced by: '<S923>/Gain2'
 */
#define rtCP_Gain2_Gain_iy             (-1.0F)

/* Computed Parameter: rtCP_Gain6_Gain_i
 * Referenced by: '<S923>/Gain6'
 */
#define rtCP_Gain6_Gain_i              (-1.0F)

/* Computed Parameter: rtCP_Gain3_Gain_jw
 * Referenced by: '<S923>/Gain3'
 */
#define rtCP_Gain3_Gain_jw             (-1.0F)

/* Computed Parameter: rtCP_Gain7_Gain_d
 * Referenced by: '<S923>/Gain7'
 */
#define rtCP_Gain7_Gain_d              (-1.0F)

/* Computed Parameter: rtCP_Gain4_Gain_k
 * Referenced by: '<S923>/Gain4'
 */
#define rtCP_Gain4_Gain_k              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_pk
 * Referenced by: '<S928>/Gain1'
 */
#define rtCP_Gain1_Gain_pk             (2.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ce
 * Referenced by: '<S928>/Gain2'
 */
#define rtCP_Gain2_Gain_ce             (3.0F)

/* Computed Parameter: rtCP_Gain4_Gain_lj
 * Referenced by: '<S928>/Gain4'
 */
#define rtCP_Gain4_Gain_lj             (3.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ap
 * Referenced by: '<S929>/Gain1'
 */
#define rtCP_Gain1_Gain_ap             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_h4
 * Referenced by: '<S929>/Gain'
 */
#define rtCP_Gain_Gain_h4              (3.0F)

/* Computed Parameter: rtCP_Gain1_Gain_fr
 * Referenced by: '<S930>/Gain1'
 */
#define rtCP_Gain1_Gain_fr             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_oxf
 * Referenced by: '<S930>/Gain'
 */
#define rtCP_Gain_Gain_oxf             (3.0F)

/* Computed Parameter: rtCP_Gain1_Gain_lr
 * Referenced by: '<S926>/Gain1'
 */
#define rtCP_Gain1_Gain_lr             (2.0F)

/* Computed Parameter: rtCP_Gain4_Gain_hz
 * Referenced by: '<S926>/Gain4'
 */
#define rtCP_Gain4_Gain_hz             (3.0F)

/* Computed Parameter: rtCP_Gain1_Gain_m0
 * Referenced by: '<S931>/Gain1'
 */
#define rtCP_Gain1_Gain_m0             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_ij
 * Referenced by: '<S931>/Gain'
 */
#define rtCP_Gain_Gain_ij              (6.0F)

/* Computed Parameter: rtCP_Gain36_Gain_i
 * Referenced by: '<S939>/Gain36'
 */
#define rtCP_Gain36_Gain_i             (-1.0F)

/* Computed Parameter: rtCP_Gain37_Gain_e
 * Referenced by: '<S939>/Gain37'
 */
#define rtCP_Gain37_Gain_e             (-1.0F)

/* Computed Parameter: rtCP_Gain38_Gain_p
 * Referenced by: '<S939>/Gain38'
 */
#define rtCP_Gain38_Gain_p             (-1.0F)

/* Computed Parameter: rtCP_Gain39_Gain_l
 * Referenced by: '<S939>/Gain39'
 */
#define rtCP_Gain39_Gain_l             (-1.0F)

/* Computed Parameter: rtCP_Gain5_Gain_nk
 * Referenced by: '<S949>/Gain5'
 */
#define rtCP_Gain5_Gain_nk             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_cr
 * Referenced by: '<S947>/Gain'
 */
#define rtCP_Gain_Gain_cr              (-1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_d
 * Referenced by: '<S947>/Gain8'
 */
#define rtCP_Gain8_Gain_d              (0.5F)

/* Computed Parameter: rtCP_Gain9_Gain_m
 * Referenced by: '<S947>/Gain9'
 */
#define rtCP_Gain9_Gain_m              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_bz
 * Referenced by: '<S947>/Gain1'
 */
#define rtCP_Gain1_Gain_bz             (-1.0F)

/* Computed Parameter: rtCP_Gain5_Gain_hr
 * Referenced by: '<S947>/Gain5'
 */
#define rtCP_Gain5_Gain_hr             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_fu
 * Referenced by: '<S947>/Gain2'
 */
#define rtCP_Gain2_Gain_fu             (-1.0F)

/* Computed Parameter: rtCP_Gain6_Gain_c
 * Referenced by: '<S947>/Gain6'
 */
#define rtCP_Gain6_Gain_c              (-1.0F)

/* Computed Parameter: rtCP_Gain3_Gain_l
 * Referenced by: '<S947>/Gain3'
 */
#define rtCP_Gain3_Gain_l              (-1.0F)

/* Computed Parameter: rtCP_Gain7_Gain_m
 * Referenced by: '<S947>/Gain7'
 */
#define rtCP_Gain7_Gain_m              (-1.0F)

/* Computed Parameter: rtCP_Gain4_Gain_hj
 * Referenced by: '<S947>/Gain4'
 */
#define rtCP_Gain4_Gain_hj             (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ml
 * Referenced by: '<S952>/Gain1'
 */
#define rtCP_Gain1_Gain_ml             (2.0F)

/* Computed Parameter: rtCP_Gain2_Gain_db
 * Referenced by: '<S952>/Gain2'
 */
#define rtCP_Gain2_Gain_db             (3.0F)

/* Computed Parameter: rtCP_Gain4_Gain_db
 * Referenced by: '<S952>/Gain4'
 */
#define rtCP_Gain4_Gain_db             (3.0F)

/* Computed Parameter: rtCP_Gain1_Gain_n4
 * Referenced by: '<S953>/Gain1'
 */
#define rtCP_Gain1_Gain_n4             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_dv0
 * Referenced by: '<S953>/Gain'
 */
#define rtCP_Gain_Gain_dv0             (3.0F)

/* Computed Parameter: rtCP_Gain1_Gain_bm
 * Referenced by: '<S954>/Gain1'
 */
#define rtCP_Gain1_Gain_bm             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_fi
 * Referenced by: '<S954>/Gain'
 */
#define rtCP_Gain_Gain_fi              (3.0F)

/* Computed Parameter: rtCP_Gain1_Gain_gs
 * Referenced by: '<S950>/Gain1'
 */
#define rtCP_Gain1_Gain_gs             (2.0F)

/* Computed Parameter: rtCP_Gain4_Gain_g
 * Referenced by: '<S950>/Gain4'
 */
#define rtCP_Gain4_Gain_g              (3.0F)

/* Computed Parameter: rtCP_Gain1_Gain_lf
 * Referenced by: '<S955>/Gain1'
 */
#define rtCP_Gain1_Gain_lf             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_j3
 * Referenced by: '<S955>/Gain'
 */
#define rtCP_Gain_Gain_j3              (6.0F)

/* Computed Parameter: rtCP_Gain2_Gain_bk
 * Referenced by: '<S364>/Gain2'
 */
#define rtCP_Gain2_Gain_bk             (0.3333F)

/* Expression: k_AES_minLnWdth
 * Referenced by: '<S287>/AES_MinLnWdth_Hyst'
 */
#define rtCP_AES_MinLnWdth_Hyst_OnVal_j (2.2F)

/* Expression: k_AES_minLnWdthHyst
 * Referenced by: '<S287>/AES_MinLnWdth_Hyst'
 */
#define rtCP_AES_MinLnWdth_Hyst_OffVal_a (2.0F)

/* Expression: k_AES_maxLnWdth
 * Referenced by: '<S287>/AES_MaxLnWdth_Hyst'
 */
#define rtCP_AES_MaxLnWdth_Hyst_OnVal_m (4.6F)

/* Expression: k_AES_maxLnWdthHyst
 * Referenced by: '<S287>/AES_MaxLnWdth_Hyst'
 */
#define rtCP_AES_MaxLnWdth_Hyst_OffVal_n (4.5F)

/* Computed Parameter: rtCP_Gain32_Gain_j
 * Referenced by: '<S913>/Gain32'
 */
#define rtCP_Gain32_Gain_j             (3.6F)

/* Computed Parameter: rtCP_opposite4_Gain
 * Referenced by: '<S260>/opposite4'
 */
#define rtCP_opposite4_Gain            (-1.0F)

/* Computed Parameter: rtCP_opposite_Gain
 * Referenced by: '<S260>/opposite'
 */
#define rtCP_opposite_Gain             (-1.0F)

/* Expression: k_AES_LaneChangeFrontMinTTC
 * Referenced by: '<S260>/Constant52'
 */
#define rtCP_Constant52_Value          (1.5F)

/* Expression: k_AES_LaneChangeRearMinTTC
 * Referenced by: '<S260>/Constant53'
 */
#define rtCP_Constant53_Value          (1.5F)

/* Expression: k_AES_FrontObsTimeGap
 * Referenced by: '<S260>/Constant4'
 */
#define rtCP_Constant4_Value_bk        (0.4F)

/* Expression: k_AES_RearObsTimeGap
 * Referenced by: '<S260>/Constant5'
 */
#define rtCP_Constant5_Value_bg        (0.5F)

/* Expression: k_AES_MaxDecelByAEB
 * Referenced by: '<S260>/Constant6'
 */
#define rtCP_Constant6_Value_a         (-5.0F)

/* Expression: k_AES_TimeGapDistFrontWeight
 * Referenced by: '<S260>/Constant7'
 */
#define rtCP_Constant7_Value_ci        (1.0F)

/* Expression: k_AES_TimeGapDistRearWeight
 * Referenced by: '<S260>/Constant8'
 */
#define rtCP_Constant8_Value_iw        (1.0F)

/* Expression: k_AES_MaxDecelRearObj
 * Referenced by: '<S260>/Constant65'
 */
#define rtCP_Constant65_Value          (-5.0F)

/* Computed Parameter: rtCP_Gain_Gain_dy
 * Referenced by: '<S260>/Gain'
 */
#define rtCP_Gain_Gain_dy              (3.6F)

/* Computed Parameter: rtCP_Gain1_Gain_f5
 * Referenced by: '<S260>/Gain1'
 */
#define rtCP_Gain1_Gain_f5             (3.6F)

/* Computed Parameter: rtCP_opposite5_Gain
 * Referenced by: '<S260>/opposite5'
 */
#define rtCP_opposite5_Gain            (-1.0F)

/* Computed Parameter: rtCP_opposite6_Gain
 * Referenced by: '<S260>/opposite6'
 */
#define rtCP_opposite6_Gain            (-1.0F)

/* Computed Parameter: rtCP_opposite7_Gain
 * Referenced by: '<S260>/opposite7'
 */
#define rtCP_opposite7_Gain            (-1.0F)

/* Expression: k_AES_FrontSecLaneLatArea
 * Referenced by: '<S260>/Constant98'
 */
#define rtCP_Constant98_Value          (0.0F)

/* Expression: k_AES_RearSecLaneLatArea
 * Referenced by: '<S260>/Constant99'
 */
#define rtCP_Constant99_Value          (0.0F)

/* Expression: k_AES_Obs_l_hys
 * Referenced by: '<S260>/Constant85'
 */
#define rtCP_Constant85_Value          (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_led
 * Referenced by: '<S981>/Gain2'
 */
#define rtCP_Gain2_Gain_led            (1.0F)

/* Computed Parameter: rtCP_opposite12_Gain
 * Referenced by: '<S260>/opposite12'
 */
#define rtCP_opposite12_Gain           (-1.0F)

/* Computed Parameter: rtCP_opposite8_Gain
 * Referenced by: '<S260>/opposite8'
 */
#define rtCP_opposite8_Gain            (-1.0F)

/* Expression: k_AES_LaneChangeFrontMinTTC
 * Referenced by: '<S260>/Constant56'
 */
#define rtCP_Constant56_Value          (1.5F)

/* Expression: k_AES_LaneChangeRearMinTTC
 * Referenced by: '<S260>/Constant57'
 */
#define rtCP_Constant57_Value_i        (1.5F)

/* Expression: k_AES_FrontObsTimeGap
 * Referenced by: '<S260>/Constant9'
 */
#define rtCP_Constant9_Value_o         (0.4F)

/* Expression: k_AES_RearObsTimeGap
 * Referenced by: '<S260>/Constant10'
 */
#define rtCP_Constant10_Value_lb       (0.5F)

/* Expression: k_AES_MaxDecelByAEB
 * Referenced by: '<S260>/Constant60'
 */
#define rtCP_Constant60_Value          (-5.0F)

/* Expression: k_AES_TimeGapDistFrontWeight
 * Referenced by: '<S260>/Constant62'
 */
#define rtCP_Constant62_Value          (1.0F)

/* Expression: k_AES_TimeGapDistRearWeight
 * Referenced by: '<S260>/Constant63'
 */
#define rtCP_Constant63_Value          (1.0F)

/* Expression: k_AES_MaxDecelRearObj
 * Referenced by: '<S260>/Constant61'
 */
#define rtCP_Constant61_Value          (-5.0F)

/* Computed Parameter: rtCP_Gain2_Gain_fn
 * Referenced by: '<S260>/Gain2'
 */
#define rtCP_Gain2_Gain_fn             (3.6F)

/* Computed Parameter: rtCP_Gain3_Gain_g4
 * Referenced by: '<S260>/Gain3'
 */
#define rtCP_Gain3_Gain_g4             (3.6F)

/* Computed Parameter: rtCP_opposite13_Gain
 * Referenced by: '<S260>/opposite13'
 */
#define rtCP_opposite13_Gain           (-1.0F)

/* Computed Parameter: rtCP_opposite14_Gain
 * Referenced by: '<S260>/opposite14'
 */
#define rtCP_opposite14_Gain           (-1.0F)

/* Computed Parameter: rtCP_opposite15_Gain
 * Referenced by: '<S260>/opposite15'
 */
#define rtCP_opposite15_Gain           (-1.0F)

/* Expression: k_AES_RearSecLaneLatArea
 * Referenced by: '<S260>/Constant37'
 */
#define rtCP_Constant37_Value          (0.0F)

/* Expression: k_AES_Obs_l_hys
 * Referenced by: '<S260>/Constant23'
 */
#define rtCP_Constant23_Value_f        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_do
 * Referenced by: '<S268>/Gain'
 */
#define rtCP_Gain_Gain_do              (-1.0F)

/* Computed Parameter: rtCP_Gain5_Gain_o
 * Referenced by: '<S268>/Gain5'
 */
#define rtCP_Gain5_Gain_o              (-1.0F)

/* Computed Parameter: rtCP_Gain10_Gain_j
 * Referenced by: '<S268>/Gain10'
 */
#define rtCP_Gain10_Gain_j             (-1.0F)

/* Computed Parameter: rtCP_Gain11_Gain_o
 * Referenced by: '<S268>/Gain11'
 */
#define rtCP_Gain11_Gain_o             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_pf
 * Referenced by: '<S9>/Gain'
 */
#define rtCP_Gain_Gain_pf              (3.6F)

/* Computed Parameter: rtCP_Gain13_Gain_e
 * Referenced by: '<S12>/Gain13'
 */
#define rtCP_Gain13_Gain_e             (-1.0F)

/* Computed Parameter: rtCP_Gain12_Gain_ic
 * Referenced by: '<S12>/Gain12'
 */
#define rtCP_Gain12_Gain_ic            (0.5F)

/* Computed Parameter: rtCP_Gain3_Gain_l4
 * Referenced by: '<S12>/Gain3'
 */
#define rtCP_Gain3_Gain_l4             (-1.0F)

/* Computed Parameter: rtCP_Gain11_Gain_a
 * Referenced by: '<S12>/Gain11'
 */
#define rtCP_Gain11_Gain_a             (-1.0F)

/* Computed Parameter: rtCP_Gain6_Gain_hb
 * Referenced by: '<S12>/Gain6'
 */
#define rtCP_Gain6_Gain_hb             (-1.0F)

/* Computed Parameter: rtCP_Gain10_Gain_d
 * Referenced by: '<S12>/Gain10'
 */
#define rtCP_Gain10_Gain_d             (-1.0F)

/* Computed Parameter: rtCP_Gain7_Gain_az
 * Referenced by: '<S12>/Gain7'
 */
#define rtCP_Gain7_Gain_az             (-1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_l
 * Referenced by: '<S12>/Gain8'
 */
#define rtCP_Gain8_Gain_l              (-1.0F)

/* Computed Parameter: rtCP_Gain9_Gain_d
 * Referenced by: '<S12>/Gain9'
 */
#define rtCP_Gain9_Gain_d              (3.6F)

/* Computed Parameter: rtCP_Gain2_Gain_bx
 * Referenced by: '<S12>/Gain2'
 */
#define rtCP_Gain2_Gain_bx             (57.32F)

/* Computed Parameter: rtCP_Gain4_Gain_h2j
 * Referenced by: '<S12>/Gain4'
 */
#define rtCP_Gain4_Gain_h2j            (57.32F)

/* Computed Parameter: rtCP_Gain_Gain_ir
 * Referenced by: '<S12>/Gain'
 */
#define rtCP_Gain_Gain_ir              (3.6F)

/* Computed Parameter: rtCP_Gain3_Gain_a4
 * Referenced by: '<S112>/Gain3'
 */
#define rtCP_Gain3_Gain_a4             (0.2778F)

/* Computed Parameter: rtCP_Gain1_Gain_gu
 * Referenced by: '<S12>/Gain1'
 */
#define rtCP_Gain1_Gain_gu             (57.32F)

/* Computed Parameter: rtCP_Gain3_Gain_ly
 * Referenced by: '<S113>/Gain3'
 */
#define rtCP_Gain3_Gain_ly             (0.2778F)

/* Computed Parameter: rtCP_Gain1_Gain_cyy
 * Referenced by: '<S11>/Gain1'
 */
#define rtCP_Gain1_Gain_cyy            (3.6F)

/* Computed Parameter: rtCP_Gain2_Gain_jc
 * Referenced by: '<S11>/Gain2'
 */
#define rtCP_Gain2_Gain_jc             (3.6F)

/* Computed Parameter: rtCP_Gain5_Gain_k0
 * Referenced by: '<S12>/Gain5'
 */
#define rtCP_Gain5_Gain_k0             (57.32F)

/* Computed Parameter: rtCP_Relay_OnVal_h
 * Referenced by: '<S95>/Relay'
 */
#define rtCP_Relay_OnVal_h             (0.02F)

/* Computed Parameter: rtCP_Relay_OffVal_n
 * Referenced by: '<S95>/Relay'
 */
#define rtCP_Relay_OffVal_n            (-0.02F)

/* Computed Parameter: rtCP_Switch5_Threshold
 * Referenced by: '<S128>/Switch5'
 */
#define rtCP_Switch5_Threshold         (0.0F)

/* Computed Parameter: rtCP_Switch2_Threshold
 * Referenced by: '<S128>/Switch2'
 */
#define rtCP_Switch2_Threshold         (0.0F)

/* Computed Parameter: rtCP_Relay_OnVal_e
 * Referenced by: '<S130>/Relay'
 */
#define rtCP_Relay_OnVal_e             (0.02F)

/* Computed Parameter: rtCP_Relay_OffVal_g
 * Referenced by: '<S130>/Relay'
 */
#define rtCP_Relay_OffVal_g            (-0.02F)

/* Computed Parameter: rtCP_Relay_YOn_n
 * Referenced by: '<S130>/Relay'
 */
#define rtCP_Relay_YOn_n               (1.0F)

/* Computed Parameter: rtCP_Relay_YOff_o
 * Referenced by: '<S130>/Relay'
 */
#define rtCP_Relay_YOff_o              (-1.0F)

/* Computed Parameter: rtCP_Relay1_OnVal
 * Referenced by: '<S130>/Relay1'
 */
#define rtCP_Relay1_OnVal              (0.02F)

/* Computed Parameter: rtCP_Relay1_OffVal
 * Referenced by: '<S130>/Relay1'
 */
#define rtCP_Relay1_OffVal             (-0.02F)

/* Computed Parameter: rtCP_Relay1_YOn
 * Referenced by: '<S130>/Relay1'
 */
#define rtCP_Relay1_YOn                (1.0F)

/* Computed Parameter: rtCP_Relay1_YOff
 * Referenced by: '<S130>/Relay1'
 */
#define rtCP_Relay1_YOff               (-1.0F)

/* Computed Parameter: rtCP_Switch7_Threshold
 * Referenced by: '<S22>/Switch7'
 */
#define rtCP_Switch7_Threshold         (0.5F)

/* Computed Parameter: rtCP_DeadZone_Start
 * Referenced by: '<S99>/Dead Zone'
 */
#define rtCP_DeadZone_Start            (-0.1F)

/* Computed Parameter: rtCP_DeadZone_End
 * Referenced by: '<S99>/Dead Zone'
 */
#define rtCP_DeadZone_End              (0.1F)

/* Computed Parameter: rtCP_Gain1_Gain_eri
 * Referenced by: '<S85>/Gain1'
 */
#define rtCP_Gain1_Gain_eri            (1.0F)

/* Computed Parameter: rtCP_Gain4_Gain_kn
 * Referenced by: '<S85>/Gain4'
 */
#define rtCP_Gain4_Gain_kn             (1.0F)

/* Expression: single(2)
 * Referenced by: '<S52>/Gain'
 */
#define rtCP_Gain_Gain_am              (2.0F)

/* Expression: single(2)
 * Referenced by: '<S52>/Gain1'
 */
#define rtCP_Gain1_Gain_idh            (2.0F)

/* Computed Parameter: rtCP_Gain5_Gain_l3
 * Referenced by: '<S85>/Gain5'
 */
#define rtCP_Gain5_Gain_l3             (1.0F)

/* Computed Parameter: rtCP_Gain8_Gain_aw
 * Referenced by: '<S85>/Gain8'
 */
#define rtCP_Gain8_Gain_aw             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_no
 * Referenced by: '<S85>/Gain2'
 */
#define rtCP_Gain2_Gain_no             (-1.0F)

/* Computed Parameter: rtCP_Relay2_OnVal
 * Referenced by: '<S95>/Relay2'
 */
#define rtCP_Relay2_OnVal              (0.02F)

/* Computed Parameter: rtCP_Relay2_OffVal
 * Referenced by: '<S95>/Relay2'
 */
#define rtCP_Relay2_OffVal             (-0.02F)

/* Computed Parameter: rtCP_DeadZone1_Start
 * Referenced by: '<S99>/Dead Zone1'
 */
#define rtCP_DeadZone1_Start           (-0.1F)

/* Computed Parameter: rtCP_DeadZone1_End
 * Referenced by: '<S99>/Dead Zone1'
 */
#define rtCP_DeadZone1_End             (0.1F)

/* Computed Parameter: rtCP_Gain3_Gain_e
 * Referenced by: '<S85>/Gain3'
 */
#define rtCP_Gain3_Gain_e              (1.0F)

/* Computed Parameter: rtCP_Gain6_Gain_on
 * Referenced by: '<S85>/Gain6'
 */
#define rtCP_Gain6_Gain_on             (1.0F)

/* Computed Parameter: rtCP_TrqSaturation_UpperSat
 * Referenced by: '<S85>/TrqSaturation'
 */
#define rtCP_TrqSaturation_UpperSat    (3.0F)

/* Computed Parameter: rtCP_TrqSaturation_LowerSat
 * Referenced by: '<S85>/TrqSaturation'
 */
#define rtCP_TrqSaturation_LowerSat    (-3.0F)

/* Computed Parameter: rtCP_AngleSaturation_UpperSat
 * Referenced by: '<S85>/AngleSaturation'
 */
#define rtCP_AngleSaturation_UpperSat  (350.0F)

/* Computed Parameter: rtCP_AngleSaturation_LowerSat
 * Referenced by: '<S85>/AngleSaturation'
 */
#define rtCP_AngleSaturation_LowerSat  (-350.0F)

/* Computed Parameter: rtCP_Relay_OnVal_g
 * Referenced by: '<S71>/Relay'
 */
#define rtCP_Relay_OnVal_g             (0.05F)

/* Computed Parameter: rtCP_Relay_OffVal_f
 * Referenced by: '<S71>/Relay'
 */
#define rtCP_Relay_OffVal_f            (-0.05F)

/* Computed Parameter: rtCP_DeadZone_Start_l
 * Referenced by: '<S78>/Dead Zone'
 */
#define rtCP_DeadZone_Start_l          (-0.1F)

/* Computed Parameter: rtCP_DeadZone_End_a
 * Referenced by: '<S78>/Dead Zone'
 */
#define rtCP_DeadZone_End_a            (0.1F)

/* Computed Parameter: rtCP_Gain1_Gain_lv
 * Referenced by: '<S55>/Gain1'
 */
#define rtCP_Gain1_Gain_lv             (1.0F)

/* Computed Parameter: rtCP_Relay1_OnVal_l
 * Referenced by: '<S71>/Relay1'
 */
#define rtCP_Relay1_OnVal_l            (0.05F)

/* Computed Parameter: rtCP_Relay1_OffVal_p
 * Referenced by: '<S71>/Relay1'
 */
#define rtCP_Relay1_OffVal_p           (-0.05F)

/* Computed Parameter: rtCP_DeadZone1_Start_a
 * Referenced by: '<S78>/Dead Zone1'
 */
#define rtCP_DeadZone1_Start_a         (-0.1F)

/* Computed Parameter: rtCP_DeadZone1_End_m
 * Referenced by: '<S78>/Dead Zone1'
 */
#define rtCP_DeadZone1_End_m           (0.1F)

/* Computed Parameter: rtCP_Gain3_Gain_og
 * Referenced by: '<S55>/Gain3'
 */
#define rtCP_Gain3_Gain_og             (1.0F)

/* Computed Parameter: rtCP_TrqSaturation_UpperSat_j
 * Referenced by: '<S55>/TrqSaturation'
 */
#define rtCP_TrqSaturation_UpperSat_j  (3.0F)

/* Computed Parameter: rtCP_TrqSaturation_LowerSat_m
 * Referenced by: '<S55>/TrqSaturation'
 */
#define rtCP_TrqSaturation_LowerSat_m  (-3.0F)

/* Computed Parameter: rtCP_AngleSaturation_UpperSat_h
 * Referenced by: '<S55>/AngleSaturation'
 */
#define rtCP_AngleSaturation_UpperSat_h (350.0F)

/* Computed Parameter: rtCP_AngleSaturation_LowerSat_e
 * Referenced by: '<S55>/AngleSaturation'
 */
#define rtCP_AngleSaturation_LowerSat_e (-350.0F)

/* Computed Parameter: rtCP_YawAngleInt_gainval
 * Referenced by: '<S988>/YawAngleInt'
 */
#define rtCP_YawAngleInt_gainval       (0.02F)

/* Computed Parameter: rtCP_YawAngleInt_IC
 * Referenced by: '<S988>/YawAngleInt'
 */
#define rtCP_YawAngleInt_IC            (0.0F)

/* Computed Parameter: rtCP_rad2deg_Gain
 * Referenced by: '<S20>/rad2deg'
 */
#define rtCP_rad2deg_Gain              (57.32F)

/* Computed Parameter: rtCP_Gain3_Gain_p5
 * Referenced by: '<S39>/Gain3'
 */
#define rtCP_Gain3_Gain_p5             (0.2778F)

/* Computed Parameter: rtCP_rad2deg_Gain_c
 * Referenced by: '<S39>/rad2deg'
 */
#define rtCP_rad2deg_Gain_c            (57.32F)

/* Computed Parameter: rtCP_TrqSaturation1_UpperSat
 * Referenced by: '<S170>/TrqSaturation1'
 */
#define rtCP_TrqSaturation1_UpperSat   (3.0F)

/* Computed Parameter: rtCP_TrqSaturation1_LowerSat
 * Referenced by: '<S170>/TrqSaturation1'
 */
#define rtCP_TrqSaturation1_LowerSat   (-3.0F)

/* Computed Parameter: rtCP_Gain7_Gain_bt
 * Referenced by: '<S170>/Gain7'
 */
#define rtCP_Gain7_Gain_bt             (-1.0F)

/* Expression: 1/ML_TIME_SEC
 * Referenced by: '<S170>/Gain2'
 */
#define rtCP_Gain2_Gain_mm             (50.0F)

/* Computed Parameter: rtCP_TrqSaturation2_UpperSat
 * Referenced by: '<S170>/TrqSaturation2'
 */
#define rtCP_TrqSaturation2_UpperSat   (5.0F)

/* Computed Parameter: rtCP_TrqSaturation2_LowerSat
 * Referenced by: '<S170>/TrqSaturation2'
 */
#define rtCP_TrqSaturation2_LowerSat   (-5.0F)

/* Computed Parameter: rtCP_AngleSaturation2_UpperSat
 * Referenced by: '<S170>/AngleSaturation2'
 */
#define rtCP_AngleSaturation2_UpperSat (50.0F)

/* Computed Parameter: rtCP_AngleSaturation2_LowerSat
 * Referenced by: '<S170>/AngleSaturation2'
 */
#define rtCP_AngleSaturation2_LowerSat (-50.0F)

/* Expression: ML_TIME_SEC
 * Referenced by: '<S170>/Gain1'
 */
#define rtCP_Gain1_Gain_de             (0.02F)

/* Expression: 1/ML_TIME_SEC
 * Referenced by: '<S173>/Gain2'
 */
#define rtCP_Gain2_Gain_mv             (50.0F)

/* Computed Parameter: rtCP_Switch5_Threshold_m
 * Referenced by: '<S179>/Switch5'
 */
#define rtCP_Switch5_Threshold_m       (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_ijj
 * Referenced by: '<S168>/Gain'
 */
#define rtCP_Gain_Gain_ijj             (-1.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S169>/Gain1'
 */
#define rtCP_Gain1_Gain_jw             (20.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ic
 * Referenced by: '<S169>/Gain2'
 */
#define rtCP_Gain2_Gain_ic             (-1.0F)

/* Expression: ML_TIME_MSEC
 * Referenced by: '<S169>/Gain'
 */
#define rtCP_Gain_Gain_pa              (20.0F)

/* Computed Parameter: rtCP_TSamp_WtEt
 * Referenced by: '<S35>/TSamp'
 */
#define rtCP_TSamp_WtEt                (50.0F)

/* Computed Parameter: rtCP_yActOut_gainval
 * Referenced by: '<S987>/yActOut'
 */
#define rtCP_yActOut_gainval           (0.02F)

/* Computed Parameter: rtCP_yActOut_IC
 * Referenced by: '<S987>/yActOut'
 */
#define rtCP_yActOut_IC                (0.0F)

/* Expression: k_AES_LnCetr_SP_A1Init
 * Referenced by: '<S319>/ESS_SPA1_Hyst'
 */
#define rtCP_ESS_SPA1_Hyst_OnVal       (0.02F)

/* Expression: k_AES_LnCetr_SP_A1Init_hys
 * Referenced by: '<S319>/ESS_SPA1_Hyst'
 */
#define rtCP_ESS_SPA1_Hyst_OffVal      (0.015F)

/* Expression: k_AES_LnCetr_SP_A0Init
 * Referenced by: '<S319>/ESS_SPA0_Hyst'
 */
#define rtCP_ESS_SPA0_Hyst_OnVal       (0.5F)

/* Expression: k_AES_LnCetr_SP_A0Init_hys
 * Referenced by: '<S319>/ESS_SPA0_Hyst'
 */
#define rtCP_ESS_SPA0_Hyst_OffVal      (0.3F)

/* Computed Parameter: rtCP_Gain2_Gain_et
 * Referenced by: '<S355>/Gain2'
 */
#define rtCP_Gain2_Gain_et             (0.3333F)

/* Computed Parameter: rtCP_Gain2_Gain_mw
 * Referenced by: '<S358>/Gain2'
 */
#define rtCP_Gain2_Gain_mw             (0.3333F)

/* Expression: k_AES_minSPPLnWdth
 * Referenced by: '<S324>/ESS_MinLnWdth_Hyst1'
 */
#define rtCP_ESS_MinLnWdth_Hyst1_OnVal (2.7F)

/* Expression: k_AES_minSPPLnWdthHyst
 * Referenced by: '<S324>/ESS_MinLnWdth_Hyst1'
 */
#define rtCP_ESS_MinLnWdth_Hyst1_OffVal (2.6F)

/* Expression: k_AES_maxSPPLnWdth
 * Referenced by: '<S324>/ESS_MaxLnWdth_Hyst1'
 */
#define rtCP_ESS_MaxLnWdth_Hyst1_OnVal (4.4F)

/* Expression: k_AES_maxSPPLnWdthHyst
 * Referenced by: '<S324>/ESS_MaxLnWdth_Hyst1'
 */
#define rtCP_ESS_MaxLnWdth_Hyst1_OffVal (4.2F)

/* Computed Parameter: rtCP_Saturation_UpperSat_fp
 * Referenced by: '<S1000>/Saturation'
 */
#define rtCP_Saturation_UpperSat_fp    (0.7F)

/* Computed Parameter: rtCP_Saturation_LowerSat_ca
 * Referenced by: '<S1000>/Saturation'
 */
#define rtCP_Saturation_LowerSat_ca    (0.0029F)

/* Computed Parameter: rtCP_Gain1_Gain_gf
 * Referenced by: '<S1000>/Gain1'
 */
#define rtCP_Gain1_Gain_gf             (-1.0F)

/* Computed Parameter: rtCP_Switch_Threshold_l
 * Referenced by: '<S1000>/Switch'
 */
#define rtCP_Switch_Threshold_l        (0.0F)

/* Computed Parameter: rtCP_Relay3_OnVal
 * Referenced by: '<S95>/Relay3'
 */
#define rtCP_Relay3_OnVal              (0.02F)

/* Computed Parameter: rtCP_Relay3_OffVal
 * Referenced by: '<S95>/Relay3'
 */
#define rtCP_Relay3_OffVal             (-0.02F)

/* Computed Parameter: rtCP_Relay1_OnVal_c
 * Referenced by: '<S95>/Relay1'
 */
#define rtCP_Relay1_OnVal_c            (0.02F)

/* Computed Parameter: rtCP_Relay1_OffVal_l
 * Referenced by: '<S95>/Relay1'
 */
#define rtCP_Relay1_OffVal_l           (-0.02F)

/* Expression: k_AES_maxLnWdth
 * Referenced by: '<S287>/AES_MaxLnWdth_Hyst1'
 */
#define rtCP_AES_MaxLnWdth_Hyst1_OnVal (4.6F)

/* Expression: k_AES_maxLnWdthHyst
 * Referenced by: '<S287>/AES_MaxLnWdth_Hyst1'
 */
#define rtCP_AES_MaxLnWdth_Hyst1_OffVal (4.5F)

/* Expression: k_AES_minLnWdth
 * Referenced by: '<S287>/AES_MinLnWdth_Hyst1'
 */
#define rtCP_AES_MinLnWdth_Hyst1_OnVal (2.2F)

/* Expression: k_AES_minLnWdthHyst
 * Referenced by: '<S287>/AES_MinLnWdth_Hyst1'
 */
#define rtCP_AES_MinLnWdth_Hyst1_OffVal (2.0F)

/* Computed Parameter: rtCP_sRoadOut_gainval
 * Referenced by: '<S986>/sRoadOut'
 */
#define rtCP_sRoadOut_gainval          (0.02F)

/* Computed Parameter: rtCP_sRoadOut_IC
 * Referenced by: '<S986>/sRoadOut'
 */
#define rtCP_sRoadOut_IC               (0.0F)

/* Expression: k_AES_maxLnWdth
 * Referenced by: '<S286>/AES_MaxLnWdth_Hyst1'
 */
#define rtCP_AES_MaxLnWdth_Hyst1_OnVal_l (4.6F)

/* Expression: k_AES_maxLnWdthHyst
 * Referenced by: '<S286>/AES_MaxLnWdth_Hyst1'
 */
#define rtCP_AES_MaxLnWdth_Hyst1_OffVal_d (4.5F)

/* Expression: k_AES_minLnWdth
 * Referenced by: '<S286>/AES_MinLnWdth_Hyst1'
 */
#define rtCP_AES_MinLnWdth_Hyst1_OnVal_d (2.2F)

/* Expression: k_AES_minLnWdthHyst
 * Referenced by: '<S286>/AES_MinLnWdth_Hyst1'
 */
#define rtCP_AES_MinLnWdth_Hyst1_OffVal_e (2.0F)

/* Computed Parameter: rtCP_avoid0_UpperSat
 * Referenced by: '<S989>/avoid 0'
 */
#define rtCP_avoid0_UpperSat           (70.0F)

/* Computed Parameter: rtCP_avoid0_LowerSat
 * Referenced by: '<S989>/avoid 0'
 */
#define rtCP_avoid0_LowerSat           (0.001F)

/* Computed Parameter: rtCP_AES_ESA_Major_Version_Value
 * Referenced by: '<S1>/AES_ESA_Major_Version'
 */
#define rtCP_AES_ESA_Major_Version_Value (260821U)

/* Computed Parameter: rtCP_Constant10_Value_c
 * Referenced by: '<S4>/Constant10'
 */
#define rtCP_Constant10_Value_c        (61U)

/* Computed Parameter: rtCP_Constant11_Value_e3
 * Referenced by: '<S4>/Constant11'
 */
#define rtCP_Constant11_Value_e3       (253U)

/* Computed Parameter: rtCP_TgtSelec_bit0_Value
 * Referenced by: '<S271>/TgtSelec_bit0'
 */
#define rtCP_TgtSelec_bit0_Value       (1U)

/* Computed Parameter: rtCP_TgtSelec_bit1_Value
 * Referenced by: '<S271>/TgtSelec_bit1'
 */
#define rtCP_TgtSelec_bit1_Value       (2U)

/* Computed Parameter: rtCP_TgtSelec_bit3_Value
 * Referenced by: '<S271>/TgtSelec_bit3'
 */
#define rtCP_TgtSelec_bit3_Value       (8U)

/* Computed Parameter: rtCP_TgtSelec_bit4_Value
 * Referenced by: '<S271>/TgtSelec_bit4'
 */
#define rtCP_TgtSelec_bit4_Value       (16U)

/* Computed Parameter: rtCP_TgtSelec_bit5_Value
 * Referenced by: '<S271>/TgtSelec_bit5'
 */
#define rtCP_TgtSelec_bit5_Value       (32U)

/* Computed Parameter: rtCP_TgtSelec_bit6_Value
 * Referenced by: '<S271>/TgtSelec_bit6'
 */
#define rtCP_TgtSelec_bit6_Value       (64U)

/* Computed Parameter: rtCP_TgtSelec_bit7_Value
 * Referenced by: '<S271>/TgtSelec_bit7'
 */
#define rtCP_TgtSelec_bit7_Value       (128U)

/* Computed Parameter: rtCP_TgtSelec_bit8_Value
 * Referenced by: '<S271>/TgtSelec_bit8'
 */
#define rtCP_TgtSelec_bit8_Value       (256U)

/* Computed Parameter: rtCP_TgtSelec_bit0_Value_j
 * Referenced by: '<S272>/TgtSelec_bit0'
 */
#define rtCP_TgtSelec_bit0_Value_j     (1U)

/* Computed Parameter: rtCP_TgtSelec_bit1_Value_p
 * Referenced by: '<S272>/TgtSelec_bit1'
 */
#define rtCP_TgtSelec_bit1_Value_p     (2U)

/* Computed Parameter: rtCP_TgtSelec_bit3_Value_l
 * Referenced by: '<S272>/TgtSelec_bit3'
 */
#define rtCP_TgtSelec_bit3_Value_l     (8U)

/* Computed Parameter: rtCP_TgtSelec_bit4_Value_o
 * Referenced by: '<S272>/TgtSelec_bit4'
 */
#define rtCP_TgtSelec_bit4_Value_o     (16U)

/* Computed Parameter: rtCP_TgtSelec_bit5_Value_j
 * Referenced by: '<S272>/TgtSelec_bit5'
 */
#define rtCP_TgtSelec_bit5_Value_j     (32U)

/* Computed Parameter: rtCP_TgtSelec_bit6_Value_g
 * Referenced by: '<S272>/TgtSelec_bit6'
 */
#define rtCP_TgtSelec_bit6_Value_g     (64U)

/* Computed Parameter: rtCP_TgtSelec_bit7_Value_o
 * Referenced by: '<S272>/TgtSelec_bit7'
 */
#define rtCP_TgtSelec_bit7_Value_o     (128U)

/* Computed Parameter: rtCP_TgtSelec_bit8_Value_l
 * Referenced by: '<S272>/TgtSelec_bit8'
 */
#define rtCP_TgtSelec_bit8_Value_l     (256U)

/* Computed Parameter: rtCP_Constant15_Value_k
 * Referenced by: '<S259>/Constant15'
 */
#define rtCP_Constant15_Value_k        (4095U)

/* Computed Parameter: rtCP_Constant17_Value_l
 * Referenced by: '<S259>/Constant17'
 */
#define rtCP_Constant17_Value_l        (4095U)

/* Computed Parameter: rtCP_Constant_Value_my
 * Referenced by: '<S974>/Constant'
 */
#define rtCP_Constant_Value_my         (0U)

/* Computed Parameter: rtCP_Constant_Value_asr
 * Referenced by: '<S995>/Constant'
 */
#define rtCP_Constant_Value_asr        (0U)

/* Computed Parameter: rtCP_Constant3_Value_op
 * Referenced by: '<S9>/Constant3'
 */
#define rtCP_Constant3_Value_op        (6U)

/* Computed Parameter: rtCP_Constant_Value_fs
 * Referenced by: '<S1107>/Constant'
 */
#define rtCP_Constant_Value_fs         (2U)

/* Computed Parameter: rtCP_Constant_Value_j3
 * Referenced by: '<S1108>/Constant'
 */
#define rtCP_Constant_Value_j3         (9U)

/* Computed Parameter: rtCP_Constant_Value_f5
 * Referenced by: '<S1109>/Constant'
 */
#define rtCP_Constant_Value_f5         (4U)

/* Computed Parameter: rtCP_Constant_Value_bf
 * Referenced by: '<S1110>/Constant'
 */
#define rtCP_Constant_Value_bf         (1U)

/* Computed Parameter: rtCP_Constant_Value_jr
 * Referenced by: '<S1111>/Constant'
 */
#define rtCP_Constant_Value_jr         (3U)

/* Computed Parameter: rtCP_Constant_Value_me
 * Referenced by: '<S1112>/Constant'
 */
#define rtCP_Constant_Value_me         (10U)

/* Computed Parameter: rtCP_Constant_Value_aft
 * Referenced by: '<S1113>/Constant'
 */
#define rtCP_Constant_Value_aft        (0U)

/* Computed Parameter: rtCP_Constant_Value_m24
 * Referenced by: '<S198>/Constant'
 */
#define rtCP_Constant_Value_m24        (9000)

/* Computed Parameter: rtCP_Constant30_Value_a
 * Referenced by: '<S294>/Constant30'
 */
#define rtCP_Constant30_Value_a        (3)

/* Computed Parameter: rtCP_Constant57_Value_c
 * Referenced by: '<S294>/Constant57'
 */
#define rtCP_Constant57_Value_c        (1)

/* Computed Parameter: rtCP_Constant58_Value
 * Referenced by: '<S294>/Constant58'
 */
#define rtCP_Constant58_Value          (-1)

/* Computed Parameter: rtCP_Constant59_Value
 * Referenced by: '<S294>/Constant59'
 */
#define rtCP_Constant59_Value          (-3)

/* Computed Parameter: rtCP_Constant30_Value_b
 * Referenced by: '<S295>/Constant30'
 */
#define rtCP_Constant30_Value_b        (3)

/* Computed Parameter: rtCP_Constant57_Value_k
 * Referenced by: '<S295>/Constant57'
 */
#define rtCP_Constant57_Value_k        (1)

/* Computed Parameter: rtCP_Constant58_Value_l
 * Referenced by: '<S295>/Constant58'
 */
#define rtCP_Constant58_Value_l        (-1)

/* Computed Parameter: rtCP_Constant59_Value_a
 * Referenced by: '<S295>/Constant59'
 */
#define rtCP_Constant59_Value_a        (-3)

/* Expression: k_AES_LMConfAccumuLmtHi
 * Referenced by: '<S294>/Saturation'
 */
#define rtCP_Saturation_UpperSat_p5    (300)

/* Expression: k_AES_LMConfAccumuLmtLo
 * Referenced by: '<S294>/Saturation'
 */
#define rtCP_Saturation_LowerSat_ob    (-300)

/* Expression: k_AES_LMConfAccumuLmtHi
 * Referenced by: '<S295>/Saturation'
 */
#define rtCP_Saturation_UpperSat_gm    (300)

/* Expression: k_AES_LMConfAccumuLmtLo
 * Referenced by: '<S295>/Saturation'
 */
#define rtCP_Saturation_LowerSat_oy    (-300)

/* Expression: k_ILC_A0_TypeTransFilter
 * Referenced by: '<S677>/k_ILC_A0_TypeTransFilter'
 */
#define rtCP_k_ILC_A0_TypeTransFilter_Value (((uint16_T)200U))

/* Expression: k_ILC_A1Jmp_Filter
 * Referenced by: '<S677>/k_ILC_A1Jmp_Filter'
 */
#define rtCP_k_ILC_A1Jmp_Filter_Value  (((uint16_T)300U))

/* Expression: k_ILC_A1_TypeTransFilter
 * Referenced by: '<S677>/k_ILC_A1_TypeTransFilter'
 */
#define rtCP_k_ILC_A1_TypeTransFilter_Value (((uint16_T)200U))

/* Expression: k_ILC_A2_Bigfilt_tau
 * Referenced by: '<S677>/k_ILC_A2_Bigfilt_tau'
 */
#define rtCP_k_ILC_A2_Bigfilt_tau_Value (((uint16_T)1000U))

/* Expression: k_ILC_A2_filt_tau
 * Referenced by: '<S677>/k_ILC_A2_filt_tau'
 */
#define rtCP_k_ILC_A2_filt_tau_Value   (((uint16_T)1000U))

/* Expression: k_ILC_SP_A0_Filter
 * Referenced by: '<S677>/k_ILC_SP_A0_Filter'
 */
#define rtCP_k_ILC_SP_A0_Filter_Value  (((uint16_T)60U))

/* Expression: k_ILC_SP_A0_Filter
 * Referenced by: '<S677>/k_ILC_SP_A0_Filter2'
 */
#define rtCP_k_ILC_SP_A0_Filter2_Value (((uint16_T)60U))

/* Expression: k_ILC_SP_A1_Filter
 * Referenced by: '<S677>/k_ILC_SP_A1_Filter'
 */
#define rtCP_k_ILC_SP_A1_Filter_Value  (((uint16_T)200U))

/* Expression: k_ILC_SP_A1_Filter
 * Referenced by: '<S677>/k_ILC_SP_A1_Filter3'
 */
#define rtCP_k_ILC_SP_A1_Filter3_Value (((uint16_T)200U))

/* Expression: k_ILC_A1SrcAvdJmp_filt_tau
 * Referenced by: '<S766>/k_ILC_A1SrcAvdJmp_filt_tau'
 */
#define rtCP_k_ILC_A1SrcAvdJmp_filt_tau_Value (((uint16_T)100U))

/* Expression: k_ILC_A1Src_filt_tau
 * Referenced by: '<S766>/k_ILC_A1Src_filt_tau'
 */
#define rtCP_k_ILC_A1Src_filt_tau_Value (((uint16_T)40U))

/* Expression: k_ILC_A2SrcAvdJmp_filt_tau
 * Referenced by: '<S766>/k_ILC_A2SrcAvdJmp_filt_tau'
 */
#define rtCP_k_ILC_A2SrcAvdJmp_filt_tau_Value (((uint16_T)100U))

/* Expression: k_ILC_A2Src_filt_tau
 * Referenced by: '<S766>/k_ILC_A2Src_filt_tau'
 */
#define rtCP_k_ILC_A2Src_filt_tau_Value (((uint16_T)40U))

/* Expression: k_SPP_Normal_filt_tau
 * Referenced by: '<S828>/k_SPP_Normal_filt_tau'
 */
#define rtCP_k_SPP_Normal_filt_tau_Value (((uint16_T)0U))

/* Expression: k_SPP_Strong_filt_tau
 * Referenced by: '<S828>/k_SPP_Strong_filt_tau'
 */
#define rtCP_k_SPP_Strong_filt_tau_Value (((uint16_T)0U))

/* Expression: k_LCK_HostLowSpd_Thd_kph
 * Referenced by: '<S682>/k_LCK_HostLowSpd_Thd_kph'
 */
#define rtCP_k_LCK_HostLowSpd_Thd_kph_Value (((uint16_T)50U))

/* Expression: k_LCK_HostLowSpd_Thd_Hys_kph
 * Referenced by: '<S682>/k_LCK_HostLowSpd_Thd_Hys_kph'
 */
#define rtCP_k_LCK_HostLowSpd_Thd_Hys_kph_Value (((uint16_T)10U))

/* Expression: k_LCK_MemLane_MaxTm_s
 * Referenced by: '<S682>/k_LCK_MemLane_MaxTm_s2'
 */
#define rtCP_k_LCK_MemLane_MaxTm_s2_Value (((uint16_T)180U))

/* Expression: k_LCK_MemLane_MaxTm_s
 * Referenced by: '<S682>/k_LCK_MemLane_MaxTm_s1'
 */
#define rtCP_k_LCK_MemLane_MaxTm_s1_Value (((uint16_T)180U))

/* Computed Parameter: rtCP_Constant10_Value_o
 * Referenced by: '<S172>/Constant10'
 */
#define rtCP_Constant10_Value_o        (((uint16_T)1U))

/* Computed Parameter: rtCP_Constant11_Value_n
 * Referenced by: '<S172>/Constant11'
 */
#define rtCP_Constant11_Value_n        (((uint16_T)10U))

/* Computed Parameter: rtCP_Constant12_Value_j
 * Referenced by: '<S172>/Constant12'
 */
#define rtCP_Constant12_Value_j        (((uint16_T)1U))

/* Computed Parameter: rtCP_Constant13_Value_oz
 * Referenced by: '<S172>/Constant13'
 */
#define rtCP_Constant13_Value_oz       (((uint16_T)10U))

/* Computed Parameter: rtCP_Constant15_Value_h
 * Referenced by: '<S172>/Constant15'
 */
#define rtCP_Constant15_Value_h        (((uint16_T)0U))

/* Computed Parameter: rtCP_Constant17_Value_k
 * Referenced by: '<S172>/Constant17'
 */
#define rtCP_Constant17_Value_k        (((uint16_T)5U))

/* Computed Parameter: rtCP_Constant9_Value_c
 * Referenced by: '<S172>/Constant9'
 */
#define rtCP_Constant9_Value_c         (((uint16_T)0U))

/* Computed Parameter: rtCP_MAXCOEFF_Value
 * Referenced by: '<S172>/MAXCOEFF'
 */
#define rtCP_MAXCOEFF_Value            (((uint16_T)200U))

/* Computed Parameter: rtCP_Constant15_Value_o
 * Referenced by: '<S916>/Constant15'
 */
#define rtCP_Constant15_Value_o        (((uint16_T)400U))

/* Computed Parameter: rtCP_Constant15_Value_h4
 * Referenced by: '<S940>/Constant15'
 */
#define rtCP_Constant15_Value_h4       (((uint16_T)400U))

/* Computed Parameter: rtCP_CallFrequencyOneLoop_Value
 * Referenced by: '<S982>/CallFrequencyOneLoop'
 */
#define rtCP_CallFrequencyOneLoop_Value (((uint16_T)1U))

/* Computed Parameter: rtCP_Constant4_Value_ia
 * Referenced by: '<S982>/Constant4'
 */
#define rtCP_Constant4_Value_ia        (((uint16_T)0U))

/* Computed Parameter: rtCP_CallFrequencyOneLoop_Value_k
 * Referenced by: '<S1136>/CallFrequencyOneLoop'
 */
#define rtCP_CallFrequencyOneLoop_Value_k (((uint16_T)1U))

/* Computed Parameter: rtCP_Constant4_Value_mh
 * Referenced by: '<S1136>/Constant4'
 */
#define rtCP_Constant4_Value_mh        (((uint16_T)0U))

/* Computed Parameter: rtCP_CallFrequencyOneLoop_Value_h
 * Referenced by: '<S1139>/CallFrequencyOneLoop'
 */
#define rtCP_CallFrequencyOneLoop_Value_h (((uint16_T)1U))

/* Computed Parameter: rtCP_Constant4_Value_bn
 * Referenced by: '<S1139>/Constant4'
 */
#define rtCP_Constant4_Value_bn        (((uint16_T)0U))

/* Computed Parameter: rtCP_CallFrequencyOneLoop_Value_l
 * Referenced by: '<S1144>/CallFrequencyOneLoop'
 */
#define rtCP_CallFrequencyOneLoop_Value_l (((uint16_T)1U))

/* Computed Parameter: rtCP_Constant4_Value_k
 * Referenced by: '<S1144>/Constant4'
 */
#define rtCP_Constant4_Value_k         (((uint16_T)0U))

/* Computed Parameter: rtCP_CallFrequencyOneLoop_Value_j
 * Referenced by: '<S1147>/CallFrequencyOneLoop'
 */
#define rtCP_CallFrequencyOneLoop_Value_j (((uint16_T)1U))

/* Computed Parameter: rtCP_Constant4_Value_nl
 * Referenced by: '<S1147>/Constant4'
 */
#define rtCP_Constant4_Value_nl        (((uint16_T)0U))

/* Computed Parameter: rtCP_Saturation_UpperSat_ke
 * Referenced by: '<S982>/Saturation'
 */
#define rtCP_Saturation_UpperSat_ke    (((uint16_T)65534U))

/* Computed Parameter: rtCP_Saturation_UpperSat_l
 * Referenced by: '<S1136>/Saturation'
 */
#define rtCP_Saturation_UpperSat_l     (((uint16_T)65534U))

/* Computed Parameter: rtCP_Saturation_UpperSat_de
 * Referenced by: '<S1144>/Saturation'
 */
#define rtCP_Saturation_UpperSat_de    (((uint16_T)65534U))

/* Computed Parameter: rtCP_Saturation_UpperSat_nk
 * Referenced by: '<S1139>/Saturation'
 */
#define rtCP_Saturation_UpperSat_nk    (((uint16_T)65534U))

/* Computed Parameter: rtCP_Saturation_UpperSat_j5
 * Referenced by: '<S1147>/Saturation'
 */
#define rtCP_Saturation_UpperSat_j5    (((uint16_T)65534U))

/* Computed Parameter: rtCP_RampDownEND_Y0
 * Referenced by: '<S215>/RampDownEND'
 */
#define rtCP_RampDownEND_Y0            (false)

/* Expression: C_TRUE
 * Referenced by: '<S217>/Constant'
 */
#define rtCP_Constant_Value_an         (true)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_jk
 * Referenced by: '<S217>/Unit Delay'
 */
#define rtCP_UnitDelay_InitialCondition_jk (false)

/* Computed Parameter: rtCP_RampUpEND_Y0
 * Referenced by: '<S216>/RampUpEND'
 */
#define rtCP_RampUpEND_Y0              (false)

/* Expression: C_TRUE
 * Referenced by: '<S218>/Constant'
 */
#define rtCP_Constant_Value_ll         (true)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_lh
 * Referenced by: '<S218>/Unit Delay'
 */
#define rtCP_UnitDelay_InitialCondition_lh (false)

/* Computed Parameter: rtCP_Constant42_Value
 * Referenced by: '<S428>/Constant42'
 */
#define rtCP_Constant42_Value          (false)

/* Computed Parameter: rtCP_Constant44_Value
 * Referenced by: '<S428>/Constant44'
 */
#define rtCP_Constant44_Value          (false)

/* Expression: C_TRUE
 * Referenced by: '<S618>/Chart'
 */
#define rtCP_Chart_C_TRUE              (true)

/* Expression: C_TRUE
 * Referenced by: '<S634>/Chart'
 */
#define rtCP_Chart_C_TRUE_d            (true)

/* Expression: C_TRUE
 * Referenced by: '<S642>/Chart'
 */
#define rtCP_Chart_C_TRUE_b            (true)

/* Expression: C_TRUE
 * Referenced by: '<S655>/Chart'
 */
#define rtCP_Chart_C_TRUE_c            (true)

/* Expression: C_FALSE
 * Referenced by: '<S677>/Constant18'
 */
#define rtCP_Constant18_Value_m        (false)

/* Expression: k_ILC_swtLckPhase1End
 * Referenced by: '<S677>/k_ILC_swtLckPhase1End'
 */
#define rtCP_k_ILC_swtLckPhase1End_Value (true)

/* Expression: k_ILC_swtLckILCEnd
 * Referenced by: '<S677>/k_ILC_swtLckILCEnd'
 */
#define rtCP_k_ILC_swtLckILCEnd_Value  (true)

/* Expression: k_ILC_swtLckPhase1
 * Referenced by: '<S677>/k_ILC_swtLckPhase1'
 */
#define rtCP_k_ILC_swtLckPhase1_Value  (true)

/* Expression: k_ILC_TgtLatSpdSelWdth
 * Referenced by: '<S677>/k_ILC_TgtLatSpdSelWdth'
 */
#define rtCP_k_ILC_TgtLatSpdSelWdth_Value (true)

/* Expression: C_FALSE
 * Referenced by: '<S466>/Constant'
 */
#define rtCP_Constant_Value_mlq        (false)

/* Expression: C_FALSE
 * Referenced by: '<S466>/Constant3'
 */
#define rtCP_Constant3_Value_kd        (false)

/* Computed Parameter: rtCP_Constant_Value_mpd
 * Referenced by: '<S706>/Constant'
 */
#define rtCP_Constant_Value_mpd        (false)

/* Computed Parameter: rtCP_Constant_Value_nf
 * Referenced by: '<S707>/Constant'
 */
#define rtCP_Constant_Value_nf         (false)

/* Computed Parameter: rtCP_Constant_Value_d3w
 * Referenced by: '<S708>/Constant'
 */
#define rtCP_Constant_Value_d3w        (false)

/* Expression: k_ILC_swtILCInput
 * Referenced by: '<S675>/k_ILC_swtILCInput'
 */
#define rtCP_k_ILC_swtILCInput_Value   (false)

/* Expression: k_ILC_SrcSelSwt
 * Referenced by: '<S766>/k_ILC_SrcSelSwt'
 */
#define rtCP_k_ILC_SrcSelSwt_Value     (true)

/* Expression: k_ILC_SrcSelSwt
 * Referenced by: '<S766>/k_ILC_SrcSelSwt11'
 */
#define rtCP_k_ILC_SrcSelSwt11_Value   (true)

/* Expression: k_ILC_SrcSelSwt
 * Referenced by: '<S766>/k_ILC_SrcSelSwt4'
 */
#define rtCP_k_ILC_SrcSelSwt4_Value    (true)

/* Expression: k_ILC_SrcSelSwt
 * Referenced by: '<S766>/k_ILC_SrcSelSwt5'
 */
#define rtCP_k_ILC_SrcSelSwt5_Value    (true)

/* Expression: k_ILC_SrcSelSwt
 * Referenced by: '<S766>/k_ILC_SrcSelSwt6'
 */
#define rtCP_k_ILC_SrcSelSwt6_Value    (true)

/* Expression: k_ILC_swtSPPorLRM
 * Referenced by: '<S766>/k_ILC_swtSPPorLRM'
 */
#define rtCP_k_ILC_swtSPPorLRM_Value   (false)

/* Expression: k_ILC_use_transform_SPP
 * Referenced by: '<S766>/k_ILC_use_transform_SPP'
 */
#define rtCP_k_ILC_use_transform_SPP_Value (false)

/* Expression: k_ILC_swtDrvDisZERO
 * Referenced by: '<S678>/k_ILC_swtDrvDisZERO'
 */
#define rtCP_k_ILC_swtDrvDisZERO_Value (true)

/* Computed Parameter: rtCP_Constant_Value_b3o
 * Referenced by: '<S831>/Constant'
 */
#define rtCP_Constant_Value_b3o        (false)

/* Computed Parameter: rtCP_Constant_Value_n0
 * Referenced by: '<S832>/Constant'
 */
#define rtCP_Constant_Value_n0         (false)

/* Expression: k_SPP_A1_flt_tauSwt
 * Referenced by: '<S828>/k_SPP_A1_flt_tauSwt'
 */
#define rtCP_k_SPP_A1_flt_tauSwt_Value (true)

/* Expression: k_LCK_SP_ConfBoost_POSLM
 * Referenced by: '<S681>/k_LCK_SP_ConfBoost_POSLM'
 */
#define rtCP_k_LCK_SP_ConfBoost_POSLM_Value (true)

/* Expression: k_LCK_use_SPP
 * Referenced by: '<S466>/k_LCK_use_SPP'
 */
#define rtCP_k_LCK_use_SPP_Value       (true)

/* Expression: k_ILC_CtrlSwh
 * Referenced by: '<S675>/k_ILC_CtrlSwh'
 */
#define rtCP_k_ILC_CtrlSwh_Value       (true)

/* Expression: k_ILC_CtrlSwh
 * Referenced by: '<S824>/k_ILC_CtrlSwh4'
 */
#define rtCP_k_ILC_CtrlSwh4_Value      (true)

/* Expression: k_ILC_CtrlSwh
 * Referenced by: '<S824>/k_ILC_CtrlSwh3'
 */
#define rtCP_k_ILC_CtrlSwh3_Value      (true)

/* Expression: k_ILC_CtrlSwh
 * Referenced by: '<S675>/k_ILC_CtrlSwh1'
 */
#define rtCP_k_ILC_CtrlSwh1_Value      (true)

/* Expression: k_ILC_CtrlSwh
 * Referenced by: '<S675>/k_ILC_CtrlSwh2'
 */
#define rtCP_k_ILC_CtrlSwh2_Value      (true)

/* Expression: k_SPP_use_RdgeBarr
 * Referenced by: '<S674>/C_FALSE1'
 */
#define rtCP_C_FALSE1_Value            (true)

/* Expression: C_FALSE
 * Referenced by: '<S674>/C_FALSE'
 */
#define rtCP_C_FALSE_Value             (false)

/* Expression: k_LCK_use_SPP_mem
 * Referenced by: '<S466>/k_LCK_use_SPP_mem'
 */
#define rtCP_k_LCK_use_SPP_mem_Value   (true)

/* Expression: k_LCK_use_SPP_mem
 * Referenced by: '<S466>/k_LCK_use_SPP_mem1'
 */
#define rtCP_k_LCK_use_SPP_mem1_Value  (true)

/* Expression: k_simusehyst
 * Referenced by: '<S437>/Constant5'
 */
#define rtCP_Constant5_Value_i3        (true)

/* Expression: C_FALSE
 * Referenced by: '<S456>/Constant1'
 */
#define rtCP_Constant1_Value_bz        (false)

/* Expression: C_FALSE
 * Referenced by: '<S456>/Constant2'
 */
#define rtCP_Constant2_Value_ee        (false)

/* Expression: C_FALSE
 * Referenced by: '<S456>/Constant3'
 */
#define rtCP_Constant3_Value_jr        (false)

/* Computed Parameter: rtCP_Constant_Value_iv
 * Referenced by: '<S489>/Constant'
 */
#define rtCP_Constant_Value_iv         (false)

/* Computed Parameter: rtCP_Constant_Value_hl
 * Referenced by: '<S490>/Constant'
 */
#define rtCP_Constant_Value_hl         (false)

/* Expression: k_allow_abs_posn_fade
 * Referenced by: '<S476>/k_allow_abs_posn_fade'
 */
#define rtCP_k_allow_abs_posn_fade_Value (true)

/* Computed Parameter: rtCP_Constant_Value_di
 * Referenced by: '<S492>/Constant'
 */
#define rtCP_Constant_Value_di         (false)

/* Computed Parameter: rtCP_Constant_Value_enp
 * Referenced by: '<S493>/Constant'
 */
#define rtCP_Constant_Value_enp        (false)

/* Expression: k_allow_abs_posn_fade
 * Referenced by: '<S477>/k_allow_abs_posn_fade'
 */
#define rtCP_k_allow_abs_posn_fade_Value_d (true)

/* Expression: C_TRUE
 * Referenced by: '<S498>/Constant'
 */
#define rtCP_Constant_Value_nz3        (true)

/* Expression: k_both_lane_req
 * Referenced by: '<S480>/k_both_lane_req'
 */
#define rtCP_k_both_lane_req_Value     (false)

/* Expression: C_TRUE
 * Referenced by: '<S502>/Constant'
 */
#define rtCP_Constant_Value_okj        (true)

/* Expression: k_both_lane_req
 * Referenced by: '<S481>/k_both_lane_req'
 */
#define rtCP_k_both_lane_req_Value_d   (false)

/* Expression: k_both_lane_req
 * Referenced by: '<S482>/k_both_lane_req'
 */
#define rtCP_k_both_lane_req_Value_f   (false)

/* Expression: C_FALSE
 * Referenced by: '<S460>/Constant1'
 */
#define rtCP_Constant1_Value_mp        (false)

/* Expression: C_FALSE
 * Referenced by: '<S460>/Constant2'
 */
#define rtCP_Constant2_Value_cb        (false)

/* Expression: C_FALSE
 * Referenced by: '<S461>/Constant3'
 */
#define rtCP_Constant3_Value_fs        (false)

/* Expression: C_FALSE
 * Referenced by: '<S461>/Constant4'
 */
#define rtCP_Constant4_Value_c         (false)

/* Expression: k_allow_abs_posn_fade
 * Referenced by: '<S531>/k_allow_abs_posn_fade'
 */
#define rtCP_k_allow_abs_posn_fade_Value_l (true)

/* Expression: k_allow_abs_posn_fade
 * Referenced by: '<S532>/k_allow_abs_posn_fade'
 */
#define rtCP_k_allow_abs_posn_fade_Value_p (true)

/* Expression: C_FALSE
 * Referenced by: '<S535>/Constant'
 */
#define rtCP_Constant_Value_bi         (false)

/* Expression: C_FALSE
 * Referenced by: '<S536>/Constant1'
 */
#define rtCP_Constant1_Value_ds        (false)

/* Expression: k_EP_enable_A1_comp
 * Referenced by: '<S567>/k_enable_A1_comp'
 */
#define rtCP_k_enable_A1_comp_Value    (false)

/* Computed Parameter: rtCP_Constant_Value_a11
 * Referenced by: '<S568>/Constant'
 */
#define rtCP_Constant_Value_a11        (false)

/* Computed Parameter: rtCP_Constant_Value_fjw
 * Referenced by: '<S569>/Constant'
 */
#define rtCP_Constant_Value_fjw        (false)

/* Computed Parameter: rtCP_Constant_Value_ji
 * Referenced by: '<S570>/Constant'
 */
#define rtCP_Constant_Value_ji         (false)

/* Computed Parameter: rtCP_Constant_Value_e2
 * Referenced by: '<S571>/Constant'
 */
#define rtCP_Constant_Value_e2         (false)

/* Computed Parameter: rtCP_Constant_Value_bz
 * Referenced by: '<S572>/Constant'
 */
#define rtCP_Constant_Value_bz         (false)

/* Computed Parameter: rtCP_Constant_Value_du
 * Referenced by: '<S573>/Constant'
 */
#define rtCP_Constant_Value_du         (false)

/* Expression: k_EP_enable_A1_comp
 * Referenced by: '<S578>/k_enable_A1_comp'
 */
#define rtCP_k_enable_A1_comp_Value_p  (false)

/* Computed Parameter: rtCP_Constant_Value_pv
 * Referenced by: '<S579>/Constant'
 */
#define rtCP_Constant_Value_pv         (false)

/* Computed Parameter: rtCP_Constant_Value_by
 * Referenced by: '<S580>/Constant'
 */
#define rtCP_Constant_Value_by         (false)

/* Computed Parameter: rtCP_Constant_Value_ea
 * Referenced by: '<S581>/Constant'
 */
#define rtCP_Constant_Value_ea         (false)

/* Computed Parameter: rtCP_Constant_Value_np
 * Referenced by: '<S582>/Constant'
 */
#define rtCP_Constant_Value_np         (false)

/* Computed Parameter: rtCP_Constant_Value_kn
 * Referenced by: '<S583>/Constant'
 */
#define rtCP_Constant_Value_kn         (false)

/* Computed Parameter: rtCP_Constant_Value_ke
 * Referenced by: '<S584>/Constant'
 */
#define rtCP_Constant_Value_ke         (false)

/* Expression: k_EP_enable_A1_comp
 * Referenced by: '<S594>/k_enable_A1_comp'
 */
#define rtCP_k_enable_A1_comp_Value_l  (false)

/* Computed Parameter: rtCP_Constant_Value_kw
 * Referenced by: '<S595>/Constant'
 */
#define rtCP_Constant_Value_kw         (false)

/* Computed Parameter: rtCP_Constant_Value_ab
 * Referenced by: '<S596>/Constant'
 */
#define rtCP_Constant_Value_ab         (false)

/* Computed Parameter: rtCP_Constant_Value_ft
 * Referenced by: '<S597>/Constant'
 */
#define rtCP_Constant_Value_ft         (false)

/* Computed Parameter: rtCP_Constant_Value_f0
 * Referenced by: '<S598>/Constant'
 */
#define rtCP_Constant_Value_f0         (false)

/* Computed Parameter: rtCP_Constant_Value_oo
 * Referenced by: '<S599>/Constant'
 */
#define rtCP_Constant_Value_oo         (false)

/* Computed Parameter: rtCP_Constant_Value_nw
 * Referenced by: '<S600>/Constant'
 */
#define rtCP_Constant_Value_nw         (false)

/* Expression: false
 * Referenced by: '<S590>/Constant10'
 */
#define rtCP_Constant10_Value_hp       (false)

/* Expression: false
 * Referenced by: '<S590>/Constant12'
 */
#define rtCP_Constant12_Value_at       (false)

/* Expression: true
 * Referenced by: '<S590>/Constant13'
 */
#define rtCP_Constant13_Value_bn       (true)

/* Expression: false
 * Referenced by: '<S590>/Constant16'
 */
#define rtCP_Constant16_Value_n        (false)

/* Expression: true
 * Referenced by: '<S590>/Constant19'
 */
#define rtCP_Constant19_Value_g        (true)

/* Expression: true
 * Referenced by: '<S590>/Constant2'
 */
#define rtCP_Constant2_Value_dq        (true)

/* Expression: false
 * Referenced by: '<S590>/Constant20'
 */
#define rtCP_Constant20_Value_j        (false)

/* Expression: true
 * Referenced by: '<S590>/Constant21'
 */
#define rtCP_Constant21_Value_p        (true)

/* Expression: false
 * Referenced by: '<S590>/Constant3'
 */
#define rtCP_Constant3_Value_dq        (false)

/* Expression: true
 * Referenced by: '<S590>/Constant6'
 */
#define rtCP_Constant6_Value_e         (true)

/* Expression: false
 * Referenced by: '<S590>/Constant7'
 */
#define rtCP_Constant7_Value_n1        (false)

/* Expression: true
 * Referenced by: '<S590>/Constant9'
 */
#define rtCP_Constant9_Value_gx        (true)

/* Expression: k_EP_enable_A1_comp
 * Referenced by: '<S607>/k_enable_A1_comp'
 */
#define rtCP_k_enable_A1_comp_Value_h  (false)

/* Computed Parameter: rtCP_Constant_Value_ax
 * Referenced by: '<S608>/Constant'
 */
#define rtCP_Constant_Value_ax         (false)

/* Computed Parameter: rtCP_Constant_Value_pmg
 * Referenced by: '<S609>/Constant'
 */
#define rtCP_Constant_Value_pmg        (false)

/* Computed Parameter: rtCP_Constant_Value_pb
 * Referenced by: '<S610>/Constant'
 */
#define rtCP_Constant_Value_pb         (false)

/* Computed Parameter: rtCP_Constant_Value_og
 * Referenced by: '<S611>/Constant'
 */
#define rtCP_Constant_Value_og         (false)

/* Computed Parameter: rtCP_Constant_Value_d33
 * Referenced by: '<S612>/Constant'
 */
#define rtCP_Constant_Value_d33        (false)

/* Computed Parameter: rtCP_Constant_Value_ko
 * Referenced by: '<S613>/Constant'
 */
#define rtCP_Constant_Value_ko         (false)

/* Expression: C_TRUE
 * Referenced by: '<S618>/Constant12'
 */
#define rtCP_Constant12_Value_bc       (true)

/* Expression: C_FALSE
 * Referenced by: '<S618>/Constant13'
 */
#define rtCP_Constant13_Value_hg       (false)

/* Expression: C_TRUE
 * Referenced by: '<S618>/Constant7'
 */
#define rtCP_Constant7_Value_cf        (true)

/* Expression: C_TRUE
 * Referenced by: '<S634>/Constant1'
 */
#define rtCP_Constant1_Value_mf        (true)

/* Expression: C_FALSE
 * Referenced by: '<S634>/Constant5'
 */
#define rtCP_Constant5_Value_hb        (false)

/* Expression: C_TRUE
 * Referenced by: '<S642>/Constant1'
 */
#define rtCP_Constant1_Value_fmo       (true)

/* Expression: C_FALSE
 * Referenced by: '<S642>/Constant5'
 */
#define rtCP_Constant5_Value_d         (false)

/* Expression: C_TRUE
 * Referenced by: '<S655>/Constant1'
 */
#define rtCP_Constant1_Value_kb        (true)

/* Expression: k_SpdLmtFppConfSelect
 * Referenced by: '<S655>/Constant12'
 */
#define rtCP_Constant12_Value_ai       (true)

/* Expression: C_FALSE
 * Referenced by: '<S655>/Constant5'
 */
#define rtCP_Constant5_Value_dp        (false)

/* Expression: k_SpdLmtFppConfSelect
 * Referenced by: '<S655>/Constant9'
 */
#define rtCP_Constant9_Value_mh        (true)

/* Expression: k_EP_use_platform_veh_width
 * Referenced by: '<S437>/k_use_platform_veh_width'
 */
#define rtCP_k_use_platform_veh_width_Value (false)

/* Computed Parameter: rtCP_Path_Deviation_Threshold_YOn
 * Referenced by: '<S618>/Path_Deviation_Threshold'
 */
#define rtCP_Path_Deviation_Threshold_YOn (true)

/* Computed Parameter: rtCP_Path_Deviation_Threshold_YOff
 * Referenced by: '<S618>/Path_Deviation_Threshold'
 */
#define rtCP_Path_Deviation_Threshold_YOff (false)

/* Computed Parameter: rtCP_k_EnableResetITerm_IntoCurv_Value
 * Referenced by: '<S52>/k_EnableResetITerm_IntoCurv'
 */
#define rtCP_k_EnableResetITerm_IntoCurv_Value (false)

/* Computed Parameter: rtCP_k_EnableResetITerm_OutCurv_Value
 * Referenced by: '<S52>/k_EnableResetITerm_OutCurv'
 */
#define rtCP_k_EnableResetITerm_OutCurv_Value (true)

/* Expression: k_LCK_Cmd_Type
 * Referenced by: '<S55>/k_LCK_Cmd_Type'
 */
#define rtCP_k_LCK_Cmd_Type_Value      (false)

/* Expression: k_LCK_Cmd_Type
 * Referenced by: '<S85>/k_LCK_Cmd_Type'
 */
#define rtCP_k_LCK_Cmd_Type_Value_l    (false)

/* Computed Parameter: rtCP_Constant_Value_lf
 * Referenced by: '<S12>/Constant'
 */
#define rtCP_Constant_Value_lf         (true)

/* Expression: k_Use_EPS_Comp
 * Referenced by: '<S170>/Constant'
 */
#define rtCP_Constant_Value_iz         (false)

/* Expression: C_FALSE
 * Referenced by: '<S172>/Constant14'
 */
#define rtCP_Constant14_Value_n        (false)

/* Expression: C_TRUE
 * Referenced by: '<S172>/Constant16'
 */
#define rtCP_Constant16_Value_k        (true)

/* Expression: C_FALSE
 * Referenced by: '<S172>/Constant3'
 */
#define rtCP_Constant3_Value_hv        (false)

/* Expression: C_TRUE
 * Referenced by: '<S172>/Constant4'
 */
#define rtCP_Constant4_Value_is        (true)

/* Expression: C_TRUE
 * Referenced by: '<S172>/Constant8'
 */
#define rtCP_Constant8_Value_a0        (true)

/* Expression: C_FALSE
 * Referenced by: '<S176>/Constant5'
 */
#define rtCP_Constant5_Value_kd        (false)

/* Expression: C_TRUE
 * Referenced by: '<S177>/Constant'
 */
#define rtCP_Constant_Value_ae         (true)

/* Expression: k_LCK_Cmd_Type
 * Referenced by: '<S170>/k_LCK_Cmd_Type'
 */
#define rtCP_k_LCK_Cmd_Type_Value_ls   (false)

/* Expression: k_LCK_Cmd_Type
 * Referenced by: '<S170>/k_LCK_Cmd_Type1'
 */
#define rtCP_k_LCK_Cmd_Type1_Value     (false)

/* Computed Parameter: rtCP_Constant9_Value_pf
 * Referenced by: '<S18>/Constant9'
 */
#define rtCP_Constant9_Value_pf        (false)

/* Computed Parameter: rtCP_Constant1_Value_ae
 * Referenced by: '<S4>/Constant1'
 */
#define rtCP_Constant1_Value_ae        (false)

/* Computed Parameter: rtCP_Constant2_Value_lh
 * Referenced by: '<S4>/Constant2'
 */
#define rtCP_Constant2_Value_lh        (false)

/* Computed Parameter: rtCP_Constant_Value_i1p
 * Referenced by: '<S256>/Constant'
 */
#define rtCP_Constant_Value_i1p        (false)

/* Computed Parameter: rtCP_Constant_Value_l5j
 * Referenced by: '<S257>/Constant'
 */
#define rtCP_Constant_Value_l5j        (true)

/* Expression: k_AES_UseVirtualData
 * Referenced by: '<S270>/Constant10'
 */
#define rtCP_Constant10_Value_a        (false)

/* Computed Parameter: rtCP_Constant_Value_mw
 * Referenced by: '<S292>/Constant'
 */
#define rtCP_Constant_Value_mw         (true)

/* Computed Parameter: rtCP_Constant_Value_plm
 * Referenced by: '<S293>/Constant'
 */
#define rtCP_Constant_Value_plm        (true)

/* Computed Parameter: rtCP_Constant_Value_fm
 * Referenced by: '<S285>/Constant'
 */
#define rtCP_Constant_Value_fm         (true)

/* Computed Parameter: rtCP_Constant2_Value_au
 * Referenced by: '<S285>/Constant2'
 */
#define rtCP_Constant2_Value_au        (true)

/* Computed Parameter: rtCP_Constant_Value_dj
 * Referenced by: '<S313>/Constant'
 */
#define rtCP_Constant_Value_dj         (true)

/* Computed Parameter: rtCP_Constant_Value_e0
 * Referenced by: '<S286>/Constant'
 */
#define rtCP_Constant_Value_e0         (true)

/* Computed Parameter: rtCP_Constant_Value_gi
 * Referenced by: '<S314>/Constant'
 */
#define rtCP_Constant_Value_gi         (true)

/* Computed Parameter: rtCP_Constant1_Value_hh
 * Referenced by: '<S287>/Constant1'
 */
#define rtCP_Constant1_Value_hh        (true)

/* Computed Parameter: rtCP_Constant_Value_hh
 * Referenced by: '<S273>/Constant'
 */
#define rtCP_Constant_Value_hh         (true)

/* Computed Parameter: rtCP_Constant_Value_a3o
 * Referenced by: '<S274>/Constant'
 */
#define rtCP_Constant_Value_a3o        (true)

/* Expression: k_AES_DefaultPassLaneLineCheck
 * Referenced by: '<S259>/Constant1'
 */
#define rtCP_Constant1_Value_kj        (false)

/* Expression: k_AES_DefaultPassLaneLineCheck
 * Referenced by: '<S259>/Constant10'
 */
#define rtCP_Constant10_Value_fm       (false)

/* Computed Parameter: rtCP_Constant11_Value_cl
 * Referenced by: '<S259>/Constant11'
 */
#define rtCP_Constant11_Value_cl       (true)

/* Expression: k_AES_UseVirtualData
 * Referenced by: '<S259>/Constant12'
 */
#define rtCP_Constant12_Value_l        (false)

/* Computed Parameter: rtCP_Constant13_Value_ma
 * Referenced by: '<S259>/Constant13'
 */
#define rtCP_Constant13_Value_ma       (true)

/* Computed Parameter: rtCP_Constant3_Value_fu
 * Referenced by: '<S259>/Constant3'
 */
#define rtCP_Constant3_Value_fu        (true)

/* Computed Parameter: rtCP_Constant4_Value_dm
 * Referenced by: '<S259>/Constant4'
 */
#define rtCP_Constant4_Value_dm        (true)

/* Computed Parameter: rtCP_Constant48_Value
 * Referenced by: '<S259>/Constant48'
 */
#define rtCP_Constant48_Value          (true)

/* Expression: k_AES_UseVirtualData
 * Referenced by: '<S259>/Constant7'
 */
#define rtCP_Constant7_Value_h2        (false)

/* Computed Parameter: rtCP_Constant8_Value_b
 * Referenced by: '<S259>/Constant8'
 */
#define rtCP_Constant8_Value_b         (true)

/* Expression: k_AES_UseVirtualData
 * Referenced by: '<S259>/Constant9'
 */
#define rtCP_Constant9_Value_l         (false)

/* Expression: k_AES_UseVirtualData
 * Referenced by: '<S281>/Constant13'
 */
#define rtCP_Constant13_Value_g        (false)

/* Expression: k_AES_UseVirtualData
 * Referenced by: '<S281>/Constant14'
 */
#define rtCP_Constant14_Value_k        (false)

/* Computed Parameter: rtCP_Constant3_Value_ka
 * Referenced by: '<S260>/Constant3'
 */
#define rtCP_Constant3_Value_ka        (true)

/* Computed Parameter: rtCP_Constant35_Value
 * Referenced by: '<S260>/Constant35'
 */
#define rtCP_Constant35_Value          (true)

/* Expression: k_AES_DefaultPassObstacleCheck
 * Referenced by: '<S260>/Constant1'
 */
#define rtCP_Constant1_Value_j4u       (false)

/* Computed Parameter: rtCP_Constant22_Value_p
 * Referenced by: '<S260>/Constant22'
 */
#define rtCP_Constant22_Value_p        (false)

/* Expression: k_AES_DefaultPassObstacleCheck
 * Referenced by: '<S260>/Constant39'
 */
#define rtCP_Constant39_Value          (false)

/* Computed Parameter: rtCP_Constant40_Value
 * Referenced by: '<S260>/Constant40'
 */
#define rtCP_Constant40_Value          (false)

/* Computed Parameter: rtCP_Constant_Value_dd
 * Referenced by: '<S261>/Constant'
 */
#define rtCP_Constant_Value_dd         (false)

/* Expression: k_AES_UseSecondPlanner
 * Referenced by: '<S268>/Constant1'
 */
#define rtCP_Constant1_Value_dp        (false)

/* Expression: k_AES_UseSecondPlanner
 * Referenced by: '<S268>/Constant2'
 */
#define rtCP_Constant2_Value_gs        (false)

/* Computed Parameter: rtCP_Constant18_Value_o
 * Referenced by: '<S913>/Constant18'
 */
#define rtCP_Constant18_Value_o        (false)

/* Computed Parameter: rtCP_Constant_Value_bfj
 * Referenced by: '<S8>/Constant'
 */
#define rtCP_Constant_Value_bfj        (false)

/* Expression: k_AES_CsderEgoLen2PlanEndX
 * Referenced by: '<S8>/Constant2'
 */
#define rtCP_Constant2_Value_ac        (true)

/* Computed Parameter: rtCP_Constant14_Value_f
 * Referenced by: '<S981>/Constant14'
 */
#define rtCP_Constant14_Value_f        (false)

/* Expression: k_AES_VirtualMainSwitch
 * Referenced by: '<S9>/Constant7'
 */
#define rtCP_Constant7_Value_ng        (true)

/* Computed Parameter: rtCP_Constant_Value_kkm
 * Referenced by: '<S1047>/Constant'
 */
#define rtCP_Constant_Value_kkm        (true)

/* Computed Parameter: rtCP_Constant_Value_n0g
 * Referenced by: '<S1048>/Constant'
 */
#define rtCP_Constant_Value_n0g        (false)

/* Computed Parameter: rtCP_Constant_Value_l1
 * Referenced by: '<S1028>/Constant'
 */
#define rtCP_Constant_Value_l1         (false)

/* Computed Parameter: rtCP_Constant_Value_pse
 * Referenced by: '<S1029>/Constant'
 */
#define rtCP_Constant_Value_pse        (false)

/* Computed Parameter: rtCP_Constant_Value_my5
 * Referenced by: '<S1031>/Constant'
 */
#define rtCP_Constant_Value_my5        (true)

/* Computed Parameter: rtCP_Constant_Value_i0s
 * Referenced by: '<S1036>/Constant'
 */
#define rtCP_Constant_Value_i0s        (false)

/* Computed Parameter: rtCP_Constant_Value_oq
 * Referenced by: '<S1037>/Constant'
 */
#define rtCP_Constant_Value_oq         (false)

/* Computed Parameter: rtCP_Constant_Value_p5
 * Referenced by: '<S1042>/Constant'
 */
#define rtCP_Constant_Value_p5         (false)

/* Computed Parameter: rtCP_Constant_Value_gi0
 * Referenced by: '<S1043>/Constant'
 */
#define rtCP_Constant_Value_gi0        (true)

/* Computed Parameter: rtCP_Constant_Value_mi
 * Referenced by: '<S1044>/Constant'
 */
#define rtCP_Constant_Value_mi         (true)

/* Computed Parameter: rtCP_Constant_Value_hs
 * Referenced by: '<S1046>/Constant'
 */
#define rtCP_Constant_Value_hs         (false)

/* Computed Parameter: rtCP_Constant_Value_fmf
 * Referenced by: '<S1054>/Constant'
 */
#define rtCP_Constant_Value_fmf        (true)

/* Computed Parameter: rtCP_Constant_Value_pfx
 * Referenced by: '<S1055>/Constant'
 */
#define rtCP_Constant_Value_pfx        (false)

/* Computed Parameter: rtCP_Constant_Value_bw
 * Referenced by: '<S1060>/Constant'
 */
#define rtCP_Constant_Value_bw         (true)

/* Computed Parameter: rtCP_Constant_Value_px4
 * Referenced by: '<S1071>/Constant'
 */
#define rtCP_Constant_Value_px4        (true)

/* Computed Parameter: rtCP_Constant_Value_hx
 * Referenced by: '<S1074>/Constant'
 */
#define rtCP_Constant_Value_hx         (true)

/* Computed Parameter: rtCP_Constant_Value_c3p
 * Referenced by: '<S1076>/Constant'
 */
#define rtCP_Constant_Value_c3p        (false)

/* Computed Parameter: rtCP_Constant_Value_dks
 * Referenced by: '<S1089>/Constant'
 */
#define rtCP_Constant_Value_dks        (true)

/* Computed Parameter: rtCP_Constant_Value_e3
 * Referenced by: '<S1090>/Constant'
 */
#define rtCP_Constant_Value_e3         (false)

/* Computed Parameter: rtCP_Constant_Value_lx
 * Referenced by: '<S1102>/Constant'
 */
#define rtCP_Constant_Value_lx         (true)

/* Computed Parameter: rtCP_Constant_Value_lu
 * Referenced by: '<S1114>/Constant'
 */
#define rtCP_Constant_Value_lu         (true)

/* Expression: k_AES_StateUseTrajMaxAyThr
 * Referenced by: '<S1016>/Constant25'
 */
#define rtCP_Constant25_Value_kb       (false)

/* Computed Parameter: rtCP_Constant28_Value_k
 * Referenced by: '<S1016>/Constant28'
 */
#define rtCP_Constant28_Value_k        (false)

/* Computed Parameter: rtCP_Constant30_Value_c
 * Referenced by: '<S1016>/Constant30'
 */
#define rtCP_Constant30_Value_c        (false)

/* Computed Parameter: rtCP_Constant31_Value_o
 * Referenced by: '<S1016>/Constant31'
 */
#define rtCP_Constant31_Value_o        (true)

/* Expression: k_AES_EnableAllTypeForAES
 * Referenced by: '<S1016>/Constant32'
 */
#define rtCP_Constant32_Value_h        (false)

/* Expression: k_AES_StateUseTrajMaxAyThr
 * Referenced by: '<S1016>/Constant7'
 */
#define rtCP_Constant7_Value_p3        (false)

/* Computed Parameter: rtCP_Constant_Value_nq
 * Referenced by: '<S1084>/Constant'
 */
#define rtCP_Constant_Value_nq         (true)

/* Computed Parameter: rtCP_Constant_Value_po
 * Referenced by: '<S1085>/Constant'
 */
#define rtCP_Constant_Value_po         (false)

/* Computed Parameter: rtCP_Constant_Value_jw
 * Referenced by: '<S1086>/Constant'
 */
#define rtCP_Constant_Value_jw         (true)

/* Computed Parameter: rtCP_Constant_Value_cgg
 * Referenced by: '<S1087>/Constant'
 */
#define rtCP_Constant_Value_cgg        (false)

/* Expression: k_AES_UseMainSwtEnaFlg
 * Referenced by: '<S9>/p_EmcAes_UseAdasMainSwtEnaFlg1'
 */
#define rtCP_p_EmcAes_UseAdasMainSwtEnaFlg1_Value (true)

/* Computed Parameter: rtCP_ESS_MinLnWdth_Hyst4_YOn
 * Referenced by: '<S324>/ESS_MinLnWdth_Hyst4'
 */
#define rtCP_ESS_MinLnWdth_Hyst4_YOn   (true)

/* Computed Parameter: rtCP_ESS_MinLnWdth_Hyst4_YOff
 * Referenced by: '<S324>/ESS_MinLnWdth_Hyst4'
 */
#define rtCP_ESS_MinLnWdth_Hyst4_YOff  (false)

/* Computed Parameter: rtCP_ESS_MaxLnWdth_Hyst4_YOn
 * Referenced by: '<S324>/ESS_MaxLnWdth_Hyst4'
 */
#define rtCP_ESS_MaxLnWdth_Hyst4_YOn   (false)

/* Computed Parameter: rtCP_ESS_MaxLnWdth_Hyst4_YOff
 * Referenced by: '<S324>/ESS_MaxLnWdth_Hyst4'
 */
#define rtCP_ESS_MaxLnWdth_Hyst4_YOff  (true)

/* Computed Parameter: rtCP_AES_MinLnWdth_Hyst_YOn
 * Referenced by: '<S286>/AES_MinLnWdth_Hyst'
 */
#define rtCP_AES_MinLnWdth_Hyst_YOn    (true)

/* Computed Parameter: rtCP_AES_MinLnWdth_Hyst_YOff
 * Referenced by: '<S286>/AES_MinLnWdth_Hyst'
 */
#define rtCP_AES_MinLnWdth_Hyst_YOff   (false)

/* Computed Parameter: rtCP_AES_MaxLnWdth_Hyst_YOn
 * Referenced by: '<S286>/AES_MaxLnWdth_Hyst'
 */
#define rtCP_AES_MaxLnWdth_Hyst_YOn    (false)

/* Computed Parameter: rtCP_AES_MaxLnWdth_Hyst_YOff
 * Referenced by: '<S286>/AES_MaxLnWdth_Hyst'
 */
#define rtCP_AES_MaxLnWdth_Hyst_YOff   (true)

/* Computed Parameter: rtCP_AES_MinLnWdth_Hyst_YOn_p
 * Referenced by: '<S287>/AES_MinLnWdth_Hyst'
 */
#define rtCP_AES_MinLnWdth_Hyst_YOn_p  (true)

/* Computed Parameter: rtCP_AES_MinLnWdth_Hyst_YOff_e
 * Referenced by: '<S287>/AES_MinLnWdth_Hyst'
 */
#define rtCP_AES_MinLnWdth_Hyst_YOff_e (false)

/* Computed Parameter: rtCP_AES_MaxLnWdth_Hyst_YOn_l
 * Referenced by: '<S287>/AES_MaxLnWdth_Hyst'
 */
#define rtCP_AES_MaxLnWdth_Hyst_YOn_l  (false)

/* Computed Parameter: rtCP_AES_MaxLnWdth_Hyst_YOff_j
 * Referenced by: '<S287>/AES_MaxLnWdth_Hyst'
 */
#define rtCP_AES_MaxLnWdth_Hyst_YOff_j (true)

/* Computed Parameter: rtCP_Relay_YOn_i
 * Referenced by: '<S95>/Relay'
 */
#define rtCP_Relay_YOn_i               (true)

/* Computed Parameter: rtCP_Relay_YOff_e
 * Referenced by: '<S95>/Relay'
 */
#define rtCP_Relay_YOff_e              (false)

/* Computed Parameter: rtCP_Relay2_YOn
 * Referenced by: '<S95>/Relay2'
 */
#define rtCP_Relay2_YOn                (true)

/* Computed Parameter: rtCP_Relay2_YOff
 * Referenced by: '<S95>/Relay2'
 */
#define rtCP_Relay2_YOff               (false)

/* Computed Parameter: rtCP_Relay_YOn_o
 * Referenced by: '<S71>/Relay'
 */
#define rtCP_Relay_YOn_o               (true)

/* Computed Parameter: rtCP_Relay_YOff_oe
 * Referenced by: '<S71>/Relay'
 */
#define rtCP_Relay_YOff_oe             (false)

/* Computed Parameter: rtCP_Relay1_YOn_g
 * Referenced by: '<S71>/Relay1'
 */
#define rtCP_Relay1_YOn_g              (true)

/* Computed Parameter: rtCP_Relay1_YOff_l
 * Referenced by: '<S71>/Relay1'
 */
#define rtCP_Relay1_YOff_l             (false)

/* Computed Parameter: rtCP_ESS_SPA1_Hyst_YOn
 * Referenced by: '<S319>/ESS_SPA1_Hyst'
 */
#define rtCP_ESS_SPA1_Hyst_YOn         (false)

/* Computed Parameter: rtCP_ESS_SPA1_Hyst_YOff
 * Referenced by: '<S319>/ESS_SPA1_Hyst'
 */
#define rtCP_ESS_SPA1_Hyst_YOff        (true)

/* Computed Parameter: rtCP_ESS_SPA0_Hyst_YOn
 * Referenced by: '<S319>/ESS_SPA0_Hyst'
 */
#define rtCP_ESS_SPA0_Hyst_YOn         (false)

/* Computed Parameter: rtCP_ESS_SPA0_Hyst_YOff
 * Referenced by: '<S319>/ESS_SPA0_Hyst'
 */
#define rtCP_ESS_SPA0_Hyst_YOff        (true)

/* Computed Parameter: rtCP_ESS_MinLnWdth_Hyst1_YOn
 * Referenced by: '<S324>/ESS_MinLnWdth_Hyst1'
 */
#define rtCP_ESS_MinLnWdth_Hyst1_YOn   (true)

/* Computed Parameter: rtCP_ESS_MinLnWdth_Hyst1_YOff
 * Referenced by: '<S324>/ESS_MinLnWdth_Hyst1'
 */
#define rtCP_ESS_MinLnWdth_Hyst1_YOff  (false)

/* Computed Parameter: rtCP_ESS_MaxLnWdth_Hyst1_YOn
 * Referenced by: '<S324>/ESS_MaxLnWdth_Hyst1'
 */
#define rtCP_ESS_MaxLnWdth_Hyst1_YOn   (false)

/* Computed Parameter: rtCP_ESS_MaxLnWdth_Hyst1_YOff
 * Referenced by: '<S324>/ESS_MaxLnWdth_Hyst1'
 */
#define rtCP_ESS_MaxLnWdth_Hyst1_YOff  (true)

/* Computed Parameter: rtCP_Constant10_Value_k5
 * Referenced by: '<S835>/Constant10'
 */
#define rtCP_Constant10_Value_k5       (0)

/* Computed Parameter: rtCP_Constant9_Value_pe
 * Referenced by: '<S835>/Constant9'
 */
#define rtCP_Constant9_Value_pe        (-1)

/* Expression: k_YawRate_Direction_ISO
 * Referenced by: '<S437>/Constant2'
 */
#define rtCP_Constant2_Value_gni       (-1)

/* Computed Parameter: rtCP_Gain8_Gain_mw
 * Referenced by: '<S1016>/Gain8'
 */
#define rtCP_Gain8_Gain_mw             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain24_Gain
 * Referenced by: '<S1016>/Gain24'
 */
#define rtCP_Gain24_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain42_Gain
 * Referenced by: '<S1016>/Gain42'
 */
#define rtCP_Gain42_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain9_Gain_d2
 * Referenced by: '<S1016>/Gain9'
 */
#define rtCP_Gain9_Gain_d2             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain25_Gain_h
 * Referenced by: '<S1016>/Gain25'
 */
#define rtCP_Gain25_Gain_h             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain50_Gain
 * Referenced by: '<S1016>/Gain50'
 */
#define rtCP_Gain50_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain10_Gain_h
 * Referenced by: '<S1016>/Gain10'
 */
#define rtCP_Gain10_Gain_h             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain15_Gain_k
 * Referenced by: '<S1016>/Gain15'
 */
#define rtCP_Gain15_Gain_k             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain12_Gain_h
 * Referenced by: '<S1016>/Gain12'
 */
#define rtCP_Gain12_Gain_h             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain17_Gain_f
 * Referenced by: '<S1016>/Gain17'
 */
#define rtCP_Gain17_Gain_f             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain45_Gain
 * Referenced by: '<S1016>/Gain45'
 */
#define rtCP_Gain45_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain46_Gain
 * Referenced by: '<S1016>/Gain46'
 */
#define rtCP_Gain46_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain51_Gain
 * Referenced by: '<S1016>/Gain51'
 */
#define rtCP_Gain51_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain6_Gain_hw
 * Referenced by: '<S1016>/Gain6'
 */
#define rtCP_Gain6_Gain_hw             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain22_Gain
 * Referenced by: '<S1016>/Gain22'
 */
#define rtCP_Gain22_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain40_Gain
 * Referenced by: '<S1016>/Gain40'
 */
#define rtCP_Gain40_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain54_Gain
 * Referenced by: '<S1016>/Gain54'
 */
#define rtCP_Gain54_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain5_Gain_ob
 * Referenced by: '<S1016>/Gain5'
 */
#define rtCP_Gain5_Gain_ob             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain21_Gain_m
 * Referenced by: '<S1016>/Gain21'
 */
#define rtCP_Gain21_Gain_m             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain39_Gain_jr
 * Referenced by: '<S1016>/Gain39'
 */
#define rtCP_Gain39_Gain_jr            (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain47_Gain
 * Referenced by: '<S1016>/Gain47'
 */
#define rtCP_Gain47_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain4_Gain_k0
 * Referenced by: '<S1016>/Gain4'
 */
#define rtCP_Gain4_Gain_k0             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain20_Gain
 * Referenced by: '<S1016>/Gain20'
 */
#define rtCP_Gain20_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain38_Gain_k
 * Referenced by: '<S1016>/Gain38'
 */
#define rtCP_Gain38_Gain_k             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain29_Gain_p
 * Referenced by: '<S1016>/Gain29'
 */
#define rtCP_Gain29_Gain_p             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain33_Gain_o
 * Referenced by: '<S1016>/Gain33'
 */
#define rtCP_Gain33_Gain_o             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain2_Gain_iq
 * Referenced by: '<S4>/Gain2'
 */
#define rtCP_Gain2_Gain_iq             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain3_Gain_d
 * Referenced by: '<S1016>/Gain3'
 */
#define rtCP_Gain3_Gain_d              (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain19_Gain
 * Referenced by: '<S1016>/Gain19'
 */
#define rtCP_Gain19_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain37_Gain_j
 * Referenced by: '<S1016>/Gain37'
 */
#define rtCP_Gain37_Gain_j             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain_Gain_pag
 * Referenced by: '<S684>/Gain'
 */
#define rtCP_Gain_Gain_pag             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain_Gain_fv3
 * Referenced by: '<S687>/Gain'
 */
#define rtCP_Gain_Gain_fv3             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain28_Gain_l
 * Referenced by: '<S1016>/Gain28'
 */
#define rtCP_Gain28_Gain_l             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain32_Gain_n
 * Referenced by: '<S1016>/Gain32'
 */
#define rtCP_Gain32_Gain_n             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain1_Gain_hgb
 * Referenced by: '<S4>/Gain1'
 */
#define rtCP_Gain1_Gain_hgb            (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain2_Gain_dt
 * Referenced by: '<S1016>/Gain2'
 */
#define rtCP_Gain2_Gain_dt             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain18_Gain
 * Referenced by: '<S1016>/Gain18'
 */
#define rtCP_Gain18_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain36_Gain_j
 * Referenced by: '<S1016>/Gain36'
 */
#define rtCP_Gain36_Gain_j             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain1_Gain_hgx
 * Referenced by: '<S684>/Gain1'
 */
#define rtCP_Gain1_Gain_hgx            (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain1_Gain_ev
 * Referenced by: '<S687>/Gain1'
 */
#define rtCP_Gain1_Gain_ev             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain27_Gain_o
 * Referenced by: '<S1016>/Gain27'
 */
#define rtCP_Gain27_Gain_o             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain31_Gain
 * Referenced by: '<S1016>/Gain31'
 */
#define rtCP_Gain31_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain_Gain_g5
 * Referenced by: '<S4>/Gain'
 */
#define rtCP_Gain_Gain_g5              (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain1_Gain_ia
 * Referenced by: '<S1016>/Gain1'
 */
#define rtCP_Gain1_Gain_ia             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain14_Gain_p
 * Referenced by: '<S1016>/Gain14'
 */
#define rtCP_Gain14_Gain_p             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain35_Gain_k
 * Referenced by: '<S1016>/Gain35'
 */
#define rtCP_Gain35_Gain_k             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain44_Gain
 * Referenced by: '<S1016>/Gain44'
 */
#define rtCP_Gain44_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain_Gain_md5
 * Referenced by: '<S516>/Gain'
 */
#define rtCP_Gain_Gain_md5             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain31_Gain_m
 * Referenced by: '<S466>/Gain31'
 */
#define rtCP_Gain31_Gain_m             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain17_Gain_c
 * Referenced by: '<S466>/Gain17'
 */
#define rtCP_Gain17_Gain_c             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain18_Gain_n
 * Referenced by: '<S466>/Gain18'
 */
#define rtCP_Gain18_Gain_n             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain19_Gain_h
 * Referenced by: '<S466>/Gain19'
 */
#define rtCP_Gain19_Gain_h             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain20_Gain_m
 * Referenced by: '<S466>/Gain20'
 */
#define rtCP_Gain20_Gain_m             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain22_Gain_b
 * Referenced by: '<S466>/Gain22'
 */
#define rtCP_Gain22_Gain_b             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain23_Gain
 * Referenced by: '<S466>/Gain23'
 */
#define rtCP_Gain23_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain24_Gain_o
 * Referenced by: '<S466>/Gain24'
 */
#define rtCP_Gain24_Gain_o             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain2_Gain_bk2
 * Referenced by: '<S424>/Gain2'
 */
#define rtCP_Gain2_Gain_bk2            (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain5_Gain_dc
 * Referenced by: '<S424>/Gain5'
 */
#define rtCP_Gain5_Gain_dc             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain6_Gain_ot
 * Referenced by: '<S424>/Gain6'
 */
#define rtCP_Gain6_Gain_ot             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain7_Gain_c
 * Referenced by: '<S424>/Gain7'
 */
#define rtCP_Gain7_Gain_c              (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain8_Gain_ih
 * Referenced by: '<S424>/Gain8'
 */
#define rtCP_Gain8_Gain_ih             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain6_Gain_c2
 * Referenced by: '<S436>/Gain6'
 */
#define rtCP_Gain6_Gain_c2             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain26_Gain_l
 * Referenced by: '<S1016>/Gain26'
 */
#define rtCP_Gain26_Gain_l             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain30_Gain_f
 * Referenced by: '<S1016>/Gain30'
 */
#define rtCP_Gain30_Gain_f             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain_Gain_mtf
 * Referenced by: '<S1016>/Gain'
 */
#define rtCP_Gain_Gain_mtf             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain13_Gain_il
 * Referenced by: '<S1016>/Gain13'
 */
#define rtCP_Gain13_Gain_il            (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain34_Gain_e
 * Referenced by: '<S1016>/Gain34'
 */
#define rtCP_Gain34_Gain_e             (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain43_Gain
 * Referenced by: '<S1016>/Gain43'
 */
#define rtCP_Gain43_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Constant18_Value_p
 * Referenced by: '<S428>/Constant18'
 */
#define rtCP_Constant18_Value_p        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant2_Value_hq
 * Referenced by: '<S429>/Constant2'
 */
#define rtCP_Constant2_Value_hq        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant2_Value_dqs
 * Referenced by: '<S430>/Constant2'
 */
#define rtCP_Constant2_Value_dqs       (((uint8_T)1U))

/* Computed Parameter: rtCP_RE_Left_CONFIDENCE4_Value
 * Referenced by: '<S431>/RE_Left_CONFIDENCE4'
 */
#define rtCP_RE_Left_CONFIDENCE4_Value (((uint8_T)0U))

/* Computed Parameter: rtCP_RE_Left_CONFIDENCE5_Value
 * Referenced by: '<S431>/RE_Left_CONFIDENCE5'
 */
#define rtCP_RE_Left_CONFIDENCE5_Value (((uint8_T)3U))

/* Computed Parameter: rtCP_RE_Left_CONFIDENCE4_Value_p
 * Referenced by: '<S432>/RE_Left_CONFIDENCE4'
 */
#define rtCP_RE_Left_CONFIDENCE4_Value_p (((uint8_T)0U))

/* Computed Parameter: rtCP_RE_Left_CONFIDENCE5_Value_k
 * Referenced by: '<S432>/RE_Left_CONFIDENCE5'
 */
#define rtCP_RE_Left_CONFIDENCE5_Value_k (((uint8_T)3U))

/* Expression: LS_LEFT_CURVE
 * Referenced by: '<S516>/Determine_Lane_State'
 */
#define rtCP_Determine_Lane_State_LS_LEFT_CURVE (((uint8_T)2U))

/* Expression: LS_LEFT_CURVE_ENTRY
 * Referenced by: '<S516>/Determine_Lane_State'
 */
#define rtCP_Determine_Lane_State_LS_LEFT_CURVE_ENTRY (((uint8_T)1U))

/* Expression: LS_LEFT_CURVE_EXIT
 * Referenced by: '<S516>/Determine_Lane_State'
 */
#define rtCP_Determine_Lane_State_LS_LEFT_CURVE_EXIT (((uint8_T)3U))

/* Expression: LS_RIGHT_CURVE
 * Referenced by: '<S516>/Determine_Lane_State'
 */
#define rtCP_Determine_Lane_State_LS_RIGHT_CURVE (((uint8_T)5U))

/* Expression: LS_RIGHT_CURVE_ENTRY
 * Referenced by: '<S516>/Determine_Lane_State'
 */
#define rtCP_Determine_Lane_State_LS_RIGHT_CURVE_ENTRY (((uint8_T)4U))

/* Expression: LS_RIGHT_CURVE_EXIT
 * Referenced by: '<S516>/Determine_Lane_State'
 */
#define rtCP_Determine_Lane_State_LS_RIGHT_CURVE_EXIT (((uint8_T)6U))

/* Expression: LS_STRAIGHT
 * Referenced by: '<S516>/Determine_Lane_State'
 */
#define rtCP_Determine_Lane_State_LS_STRAIGHT (((uint8_T)0U))

/* Expression: RS_LEFT_CURVE
 * Referenced by: '<S618>/Determine_Road_State'
 */
#define rtCP_Determine_Road_State_RS_LEFT_CURVE (((uint8_T)2U))

/* Expression: RS_LEFT_CURVE_ENTRY
 * Referenced by: '<S618>/Determine_Road_State'
 */
#define rtCP_Determine_Road_State_RS_LEFT_CURVE_ENTRY (((uint8_T)1U))

/* Expression: RS_LEFT_CURVE_EXIT
 * Referenced by: '<S618>/Determine_Road_State'
 */
#define rtCP_Determine_Road_State_RS_LEFT_CURVE_EXIT (((uint8_T)3U))

/* Expression: RS_RIGHT_CURVE
 * Referenced by: '<S618>/Determine_Road_State'
 */
#define rtCP_Determine_Road_State_RS_RIGHT_CURVE (((uint8_T)5U))

/* Expression: RS_RIGHT_CURVE_ENTRY
 * Referenced by: '<S618>/Determine_Road_State'
 */
#define rtCP_Determine_Road_State_RS_RIGHT_CURVE_ENTRY (((uint8_T)4U))

/* Expression: RS_RIGHT_CURVE_EXIT
 * Referenced by: '<S618>/Determine_Road_State'
 */
#define rtCP_Determine_Road_State_RS_RIGHT_CURVE_EXIT (((uint8_T)6U))

/* Expression: RS_STRAIGHT
 * Referenced by: '<S618>/Determine_Road_State'
 */
#define rtCP_Determine_Road_State_RS_STRAIGHT (((uint8_T)0U))

/* Expression: SIMLMANDEDGE_HIGH
 * Referenced by: '<S465>/LftSimFlag'
 */
#define rtCP_LftSimFlag_SIMLMANDEDGE_HIGH (((uint8_T)3U))

/* Expression: SIMLMANDEDGE_LOW
 * Referenced by: '<S465>/LftSimFlag'
 */
#define rtCP_LftSimFlag_SIMLMANDEDGE_LOW (((uint8_T)1U))

/* Expression: SIMLMANDEDGE_MED
 * Referenced by: '<S465>/LftSimFlag'
 */
#define rtCP_LftSimFlag_SIMLMANDEDGE_MED (((uint8_T)2U))

/* Expression: SIMLMANDEDGE_HIGH
 * Referenced by: '<S465>/RgtSimFlag'
 */
#define rtCP_RgtSimFlag_SIMLMANDEDGE_HIGH (((uint8_T)3U))

/* Expression: SIMLMANDEDGE_LOW
 * Referenced by: '<S465>/RgtSimFlag'
 */
#define rtCP_RgtSimFlag_SIMLMANDEDGE_LOW (((uint8_T)1U))

/* Expression: SIMLMANDEDGE_MED
 * Referenced by: '<S465>/RgtSimFlag'
 */
#define rtCP_RgtSimFlag_SIMLMANDEDGE_MED (((uint8_T)2U))

/* Expression: TJA_SP_TYPE_BLMONLY
 * Referenced by: '<S676>/Mem_LM_high_spd'
 */
#define rtCP_Mem_LM_high_spd_TJA_SP_TYPE_BLMONLY (((uint8_T)3U))

/* Expression: ILC_DEFAULT
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_ILC_DEFAULT  (((uint8_T)0U))

/* Expression: LCK_MODE_LeftLaneChange
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_LCK_MODE_LeftLaneChange (((uint8_T)9U))

/* Expression: LCK_MODE_RightLaneChange
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_LCK_MODE_RightLaneChange (((uint8_T)10U))

/* Expression: LEFTILC_LEFTCURVE
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_LEFTILC_LEFTCURVE (((uint8_T)3U))

/* Expression: LEFTILC_LOWSPEED
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_LEFTILC_LOWSPEED (((uint8_T)7U))

/* Expression: LEFTILC_RIGHTCURVE
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_LEFTILC_RIGHTCURVE (((uint8_T)5U))

/* Expression: LEFTILC_STRIGHT
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_LEFTILC_STRIGHT (((uint8_T)1U))

/* Expression: LS_LEFT_CURVE_ENTRY
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_LS_LEFT_CURVE_ENTRY (((uint8_T)1U))

/* Expression: LS_LEFT_CURVE_EXIT
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_LS_LEFT_CURVE_EXIT (((uint8_T)3U))

/* Expression: LS_RIGHT_CURVE_ENTRY
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_LS_RIGHT_CURVE_ENTRY (((uint8_T)4U))

/* Expression: LS_RIGHT_CURVE_EXIT
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_LS_RIGHT_CURVE_EXIT (((uint8_T)6U))

/* Expression: LS_STRAIGHT
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_LS_STRAIGHT  (((uint8_T)0U))

/* Expression: RIGHTILC_LEFTCURVE
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_RIGHTILC_LEFTCURVE (((uint8_T)4U))

/* Expression: RIGHTILC_LOWSPEED
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_RIGHTILC_LOWSPEED (((uint8_T)8U))

/* Expression: RIGHTILC_RIGHTCURVE
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_RIGHTILC_RIGHTCURVE (((uint8_T)6U))

/* Expression: RIGHTILC_STRIGHT
 * Referenced by: '<S677>/ILC_TypeJdge'
 */
#define rtCP_ILC_TypeJdge_RIGHTILC_STRIGHT (((uint8_T)2U))

/* Expression: ILC_DEFAULT
 * Referenced by: '<S677>/ILC_DEFAULT'
 */
#define rtCP_ILC_DEFAULT_Value         (((uint8_T)0U))

/* Expression: ILC_LANECHAGING
 * Referenced by: '<S677>/ILC_LANECHAGING10'
 */
#define rtCP_ILC_LANECHAGING10_Value   (((uint8_T)4U))

/* Expression: ILC_LANECHAGING
 * Referenced by: '<S677>/ILC_LANECHAGING9'
 */
#define rtCP_ILC_LANECHAGING9_Value    (((uint8_T)4U))

/* Expression: LEFTILC_LEFTCURVE
 * Referenced by: '<S677>/LEFTILC_LEFTCURVE'
 */
#define rtCP_LEFTILC_LEFTCURVE_Value   (((uint8_T)3U))

/* Expression: LEFTILC_RIGHTCURVE
 * Referenced by: '<S677>/LEFTILC_RIGHTCURVE'
 */
#define rtCP_LEFTILC_RIGHTCURVE_Value  (((uint8_T)5U))

/* Expression: RIGHTILC_LEFTCURVE
 * Referenced by: '<S677>/RIGHTILC_LEFTCURVE'
 */
#define rtCP_RIGHTILC_LEFTCURVE_Value  (((uint8_T)4U))

/* Expression: RIGHTILC_RIGHTCURVE
 * Referenced by: '<S677>/RIGHTILC_RIGHTCURVE'
 */
#define rtCP_RIGHTILC_RIGHTCURVE_Value (((uint8_T)6U))

/* Expression: k_SPPA1ForILC_swt
 * Referenced by: '<S677>/k_SPPA1ForILC_swt'
 */
#define rtCP_k_SPPA1ForILC_swt_Value   (((uint8_T)2U))

/* Expression: k_SPPA2ForILC_swt
 * Referenced by: '<S677>/k_SPPA2ForILC_swt'
 */
#define rtCP_k_SPPA2ForILC_swt_Value   (((uint8_T)2U))

/* Expression: C_ZERO
 * Referenced by: '<S466>/Constant1'
 */
#define rtCP_Constant1_Value_aq        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S466>/Constant4'
 */
#define rtCP_Constant4_Value_fu        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S466>/Constant5'
 */
#define rtCP_Constant5_Value_fdj       (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S466>/Constant6'
 */
#define rtCP_Constant6_Value_e4        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S466>/Constant9'
 */
#define rtCP_Constant9_Value_bn        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S711>/Constant2'
 */
#define rtCP_Constant2_Value_hi        (((uint8_T)0U))

/* Expression: C_ONE
 * Referenced by: '<S711>/Constant3'
 */
#define rtCP_Constant3_Value_ew        (((uint8_T)1U))

/* Expression: C_ZERO
 * Referenced by: '<S711>/switch'
 */
#define rtCP_switch_Value              (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S709>/Constant2'
 */
#define rtCP_Constant2_Value_ix        (((uint8_T)0U))

/* Expression: C_ONE
 * Referenced by: '<S709>/Constant3'
 */
#define rtCP_Constant3_Value_gn        (((uint8_T)1U))

/* Expression: C_ZERO
 * Referenced by: '<S709>/switch'
 */
#define rtCP_switch_Value_i            (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S710>/Constant2'
 */
#define rtCP_Constant2_Value_bc        (((uint8_T)0U))

/* Expression: C_ONE
 * Referenced by: '<S710>/Constant3'
 */
#define rtCP_Constant3_Value_ne        (((uint8_T)1U))

/* Expression: C_ZERO
 * Referenced by: '<S710>/switch'
 */
#define rtCP_switch_Value_a            (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_bs
 * Referenced by: '<S712>/Constant'
 */
#define rtCP_Constant_Value_bs         (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant1_Value_pz
 * Referenced by: '<S712>/Constant1'
 */
#define rtCP_Constant1_Value_pz        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant2_Value_ph
 * Referenced by: '<S712>/Constant2'
 */
#define rtCP_Constant2_Value_ph        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant3_Value_hf
 * Referenced by: '<S712>/Constant3'
 */
#define rtCP_Constant3_Value_hf        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant4_Value_kl
 * Referenced by: '<S712>/Constant4'
 */
#define rtCP_Constant4_Value_kl        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant5_Value_nf
 * Referenced by: '<S712>/Constant5'
 */
#define rtCP_Constant5_Value_nf        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant6_Value_f
 * Referenced by: '<S712>/Constant6'
 */
#define rtCP_Constant6_Value_f         (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant7_Value_io
 * Referenced by: '<S712>/Constant7'
 */
#define rtCP_Constant7_Value_io        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant8_Value_dc
 * Referenced by: '<S712>/Constant8'
 */
#define rtCP_Constant8_Value_dc        (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant_Value_gk
 * Referenced by: '<S713>/Constant'
 */
#define rtCP_Constant_Value_gk         (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant1_Value_le
 * Referenced by: '<S713>/Constant1'
 */
#define rtCP_Constant1_Value_le        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant2_Value_io
 * Referenced by: '<S713>/Constant2'
 */
#define rtCP_Constant2_Value_io        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant3_Value_oh
 * Referenced by: '<S713>/Constant3'
 */
#define rtCP_Constant3_Value_oh        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant4_Value_pd
 * Referenced by: '<S713>/Constant4'
 */
#define rtCP_Constant4_Value_pd        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant5_Value_hj
 * Referenced by: '<S713>/Constant5'
 */
#define rtCP_Constant5_Value_hj        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant6_Value_f3
 * Referenced by: '<S713>/Constant6'
 */
#define rtCP_Constant6_Value_f3        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant7_Value_js
 * Referenced by: '<S713>/Constant7'
 */
#define rtCP_Constant7_Value_js        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant8_Value_ge
 * Referenced by: '<S713>/Constant8'
 */
#define rtCP_Constant8_Value_ge        (((uint8_T)4U))

/* Expression: k_SPP_BLM_MinConf
 * Referenced by: '<S676>/k_SPP_BLM_MinConf'
 */
#define rtCP_k_SPP_BLM_MinConf_Value   (((uint8_T)1U))

/* Expression: k_SPP_BLM_MemMinConf
 * Referenced by: '<S676>/k_SPP_BLM_MemMinConf'
 */
#define rtCP_k_SPP_BLM_MemMinConf_Value (((uint8_T)1U))

/* Expression: k_SPP_SLM_MemMinConf
 * Referenced by: '<S676>/k_SPP_SLM_MemMinConf'
 */
#define rtCP_k_SPP_SLM_MemMinConf_Value (((uint8_T)1U))

/* Expression: LEFTILC_LEFTCURVE
 * Referenced by: '<S763>/LEFTILC_LEFTCURVE'
 */
#define rtCP_LEFTILC_LEFTCURVE_Value_i (((uint8_T)3U))

/* Expression: LEFTILC_RIGHTCURVE
 * Referenced by: '<S763>/LEFTILC_RIGHTCURVE'
 */
#define rtCP_LEFTILC_RIGHTCURVE_Value_i (((uint8_T)5U))

/* Expression: RIGHTILC_LEFTCURVE
 * Referenced by: '<S763>/RIGHTILC_LEFTCURVE'
 */
#define rtCP_RIGHTILC_LEFTCURVE_Value_m (((uint8_T)4U))

/* Expression: RIGHTILC_RIGHTCURVE
 * Referenced by: '<S763>/RIGHTILC_RIGHTCURVE'
 */
#define rtCP_RIGHTILC_RIGHTCURVE_Value_k (((uint8_T)6U))

/* Expression: LANECHANGE_TARGET
 * Referenced by: '<S678>/LANECHANGE_TARGET7'
 */
#define rtCP_LANECHANGE_TARGET7_Value  (((uint8_T)2U))

/* Expression: ILC_LANECHAGING
 * Referenced by: '<S766>/ILC_LANECHAGING11'
 */
#define rtCP_ILC_LANECHAGING11_Value   (((uint8_T)4U))

/* Expression: ILC_LANECHAGING
 * Referenced by: '<S766>/ILC_LANECHAGING2'
 */
#define rtCP_ILC_LANECHAGING2_Value_g  (((uint8_T)4U))

/* Expression: ILC_LANECHAGING
 * Referenced by: '<S766>/ILC_LANECHAGING3'
 */
#define rtCP_ILC_LANECHAGING3_Value_l  (((uint8_T)4U))

/* Expression: ILC_LANECHAGING
 * Referenced by: '<S766>/ILC_LANECHAGING9'
 */
#define rtCP_ILC_LANECHAGING9_Value_k  (((uint8_T)4U))

/* Expression: k_ILC_A1SrcSel
 * Referenced by: '<S766>/k_ILC_A1SrcSel'
 */
#define rtCP_k_ILC_A1SrcSel_Value      (((uint8_T)2U))

/* Expression: k_ILC_A2SrcSel
 * Referenced by: '<S766>/k_ILC_A2SrcSel'
 */
#define rtCP_k_ILC_A2SrcSel_Value      (((uint8_T)2U))

/* Expression: C_ZERO
 * Referenced by: '<S826>/Constant'
 */
#define rtCP_Constant_Value_glb        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant1_Value_cs
 * Referenced by: '<S835>/Constant1'
 */
#define rtCP_Constant1_Value_cs        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S835>/Constant12'
 */
#define rtCP_Constant12_Value_ao       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant4_Value_hu
 * Referenced by: '<S835>/Constant4'
 */
#define rtCP_Constant4_Value_hu        (((uint8_T)1U))

/* Expression: C_ZERO
 * Referenced by: '<S836>/Constant7'
 */
#define rtCP_Constant7_Value_lh        (((uint8_T)0U))

/* Expression: k_LBS_LaneBiasOvrdEn
 * Referenced by: '<S827>/k_LBS_LaneBiasOvrdEn'
 */
#define rtCP_k_LBS_LaneBiasOvrdEn_Value (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_gp
 * Referenced by: '<S828>/Constant'
 */
#define rtCP_Constant_Value_gp         (((uint8_T)2U))

/* Expression: TJA_SP_TYPE_POBLM
 * Referenced by: '<S829>/TJA_SP_TYPE_POBLM6'
 */
#define rtCP_TJA_SP_TYPE_POBLM6_Value  (((uint8_T)7U))

/* Expression: TJA_SP_TYPE_POHPP
 * Referenced by: '<S829>/TJA_SP_TYPE_POHPP'
 */
#define rtCP_TJA_SP_TYPE_POHPP_Value   (((uint8_T)8U))

/* Expression: k_LCK_RFC_HiConf_SPTYPE_1
 * Referenced by: '<S683>/k_LCK_RFC_HiConf_SPTYPE_1'
 */
#define rtCP_k_LCK_RFC_HiConf_SPTYPE_1_Value (((uint8_T)8U))

/* Expression: k_LCK_RFC_HiConf_SPTYPE_2
 * Referenced by: '<S683>/k_LCK_RFC_HiConf_SPTYPE_2'
 */
#define rtCP_k_LCK_RFC_HiConf_SPTYPE_2_Value (((uint8_T)8U))

/* Expression: k_LCK_RFC_HiConf_SPTYPE_3
 * Referenced by: '<S683>/k_LCK_RFC_HiConf_SPTYPE_3'
 */
#define rtCP_k_LCK_RFC_HiConf_SPTYPE_3_Value (((uint8_T)8U))

/* Expression: k_LCK_RFC_HiConf_SPTYPE_4
 * Referenced by: '<S683>/k_LCK_RFC_HiConf_SPTYPE_4'
 */
#define rtCP_k_LCK_RFC_HiConf_SPTYPE_4_Value (((uint8_T)8U))

/* Expression: k_LCK_ValidLane_MinRange_m
 * Referenced by: '<S682>/k_LCK_ValidLane_MinRange_m'
 */
#define rtCP_k_LCK_ValidLane_MinRange_m_Value (((uint8_T)15U))

/* Computed Parameter: rtCP_update_measure_Value
 * Referenced by: '<S690>/update_measure'
 */
#define rtCP_update_measure_Value      (((uint8_T)5U))

/* Computed Parameter: rtCP_coast_measure_Value
 * Referenced by: '<S690>/coast_measure'
 */
#define rtCP_coast_measure_Value       (((uint8_T)6U))

/* Expression: TJA_SP_CONF_LOW
 * Referenced by: '<S690>/TJA_SP_CONF_LOW'
 */
#define rtCP_TJA_SP_CONF_LOW_Value     (((uint8_T)1U))

/* Computed Parameter: rtCP_update_measure_Value_n
 * Referenced by: '<S688>/update_measure'
 */
#define rtCP_update_measure_Value_n    (((uint8_T)5U))

/* Computed Parameter: rtCP_coast_measure_Value_a
 * Referenced by: '<S688>/coast_measure'
 */
#define rtCP_coast_measure_Value_a     (((uint8_T)6U))

/* Expression: TJA_SP_CONF_LOW
 * Referenced by: '<S688>/TJA_SP_CONF_LOW'
 */
#define rtCP_TJA_SP_CONF_LOW_Value_o   (((uint8_T)1U))

/* Computed Parameter: rtCP_update_measure_Value_d
 * Referenced by: '<S689>/update_measure'
 */
#define rtCP_update_measure_Value_d    (((uint8_T)5U))

/* Computed Parameter: rtCP_coast_measure_Value_o
 * Referenced by: '<S689>/coast_measure'
 */
#define rtCP_coast_measure_Value_o     (((uint8_T)6U))

/* Expression: TJA_SP_CONF_LOW
 * Referenced by: '<S689>/TJA_SP_CONF_LOW'
 */
#define rtCP_TJA_SP_CONF_LOW_Value_n   (((uint8_T)1U))

/* Computed Parameter: rtCP_update_measure_Value_m
 * Referenced by: '<S699>/update_measure'
 */
#define rtCP_update_measure_Value_m    (((uint8_T)5U))

/* Computed Parameter: rtCP_coast_measure_Value_p
 * Referenced by: '<S699>/coast_measure'
 */
#define rtCP_coast_measure_Value_p     (((uint8_T)6U))

/* Expression: TJA_SP_CONF_LOW
 * Referenced by: '<S699>/TJA_SP_CONF_LOW'
 */
#define rtCP_TJA_SP_CONF_LOW_Value_b   (((uint8_T)1U))

/* Computed Parameter: rtCP_update_measure_Value_k
 * Referenced by: '<S697>/update_measure'
 */
#define rtCP_update_measure_Value_k    (((uint8_T)5U))

/* Computed Parameter: rtCP_coast_measure_Value_e
 * Referenced by: '<S697>/coast_measure'
 */
#define rtCP_coast_measure_Value_e     (((uint8_T)6U))

/* Expression: TJA_SP_CONF_LOW
 * Referenced by: '<S697>/TJA_SP_CONF_LOW'
 */
#define rtCP_TJA_SP_CONF_LOW_Value_l   (((uint8_T)1U))

/* Computed Parameter: rtCP_update_measure_Value_p
 * Referenced by: '<S698>/update_measure'
 */
#define rtCP_update_measure_Value_p    (((uint8_T)5U))

/* Computed Parameter: rtCP_coast_measure_Value_h
 * Referenced by: '<S698>/coast_measure'
 */
#define rtCP_coast_measure_Value_h     (((uint8_T)6U))

/* Expression: TJA_SP_CONF_LOW
 * Referenced by: '<S698>/TJA_SP_CONF_LOW'
 */
#define rtCP_TJA_SP_CONF_LOW_Value_a   (((uint8_T)1U))

/* Expression: TJA_SP_TYPE_POONLY
 * Referenced by: '<S681>/TJA_SP_TYPE_POBLM1'
 */
#define rtCP_TJA_SP_TYPE_POBLM1_Value  (((uint8_T)4U))

/* Expression: TJA_SP_TYPE_POBLM
 * Referenced by: '<S681>/TJA_SP_TYPE_POBLM'
 */
#define rtCP_TJA_SP_TYPE_POBLM_Value   (((uint8_T)7U))

/* Expression: TJA_SP_TYPE_BLMONLY
 * Referenced by: '<S682>/TJA_SP_TYPE_BLMONLY1'
 */
#define rtCP_TJA_SP_TYPE_BLMONLY1_Value (((uint8_T)3U))

/* Expression: TJA_SP_TYPE_POONLY
 * Referenced by: '<S676>/TJA_SP_TYPE_POBLM2'
 */
#define rtCP_TJA_SP_TYPE_POBLM2_Value  (((uint8_T)4U))

/* Expression: TJA_SP_TYPE_LLMONLY
 * Referenced by: '<S681>/TJA_SP_TYPE_LLMONLY'
 */
#define rtCP_TJA_SP_TYPE_LLMONLY_Value (((uint8_T)1U))

/* Computed Parameter: rtCP_update_measure_Value_nn
 * Referenced by: '<S819>/update_measure'
 */
#define rtCP_update_measure_Value_nn   (((uint8_T)5U))

/* Computed Parameter: rtCP_coast_measure_Value_i
 * Referenced by: '<S819>/coast_measure'
 */
#define rtCP_coast_measure_Value_i     (((uint8_T)6U))

/* Expression: TJA_SP_CONF_LOW
 * Referenced by: '<S819>/TJA_SP_CONF_LOW'
 */
#define rtCP_TJA_SP_CONF_LOW_Value_p   (((uint8_T)1U))

/* Expression: TJA_SP_TYPE_RLMONLY
 * Referenced by: '<S681>/TJA_SP_TYPE_RLMONLY'
 */
#define rtCP_TJA_SP_TYPE_RLMONLY_Value (((uint8_T)2U))

/* Computed Parameter: rtCP_update_measure_Value_mv
 * Referenced by: '<S818>/update_measure'
 */
#define rtCP_update_measure_Value_mv   (((uint8_T)5U))

/* Computed Parameter: rtCP_coast_measure_Value_pt
 * Referenced by: '<S818>/coast_measure'
 */
#define rtCP_coast_measure_Value_pt    (((uint8_T)6U))

/* Expression: TJA_SP_CONF_LOW
 * Referenced by: '<S818>/TJA_SP_CONF_LOW'
 */
#define rtCP_TJA_SP_CONF_LOW_Value_k   (((uint8_T)1U))

/* Expression: TJA_SP_TYPE_RLMONLY
 * Referenced by: '<S674>/TJA_SP_TYPE_RLMONLY1'
 */
#define rtCP_TJA_SP_TYPE_RLMONLY1_Value (((uint8_T)2U))

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER2_Value
 * Referenced by: '<S685>/POLY_TYPE_LM_BARRIER2'
 */
#define rtCP_POLY_TYPE_LM_BARRIER2_Value (((uint8_T)1U))

/* Computed Parameter: rtCP_POLY_TYPE_FUSED_BARRIER2_Value
 * Referenced by: '<S685>/POLY_TYPE_FUSED_BARRIER2'
 */
#define rtCP_POLY_TYPE_FUSED_BARRIER2_Value (((uint8_T)3U))

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER3_Value
 * Referenced by: '<S685>/POLY_TYPE_LM_BARRIER3'
 */
#define rtCP_POLY_TYPE_LM_BARRIER3_Value (((uint8_T)9U))

/* Computed Parameter: rtCP_POLY_TYPE_FUSED_BARRIER3_Value
 * Referenced by: '<S685>/POLY_TYPE_FUSED_BARRIER3'
 */
#define rtCP_POLY_TYPE_FUSED_BARRIER3_Value (((uint8_T)12U))

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER_Value
 * Referenced by: '<S685>/POLY_TYPE_LM_BARRIER'
 */
#define rtCP_POLY_TYPE_LM_BARRIER_Value (((uint8_T)5U))

/* Computed Parameter: rtCP_POLY_TYPE_FUSED_BARRIER_Value
 * Referenced by: '<S685>/POLY_TYPE_FUSED_BARRIER'
 */
#define rtCP_POLY_TYPE_FUSED_BARRIER_Value (((uint8_T)8U))

/* Expression: TJA_SP_TYPE_LLMONLY
 * Referenced by: '<S674>/TJA_SP_TYPE_LLMONLY1'
 */
#define rtCP_TJA_SP_TYPE_LLMONLY1_Value (((uint8_T)1U))

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER2_Value_b
 * Referenced by: '<S686>/POLY_TYPE_LM_BARRIER2'
 */
#define rtCP_POLY_TYPE_LM_BARRIER2_Value_b (((uint8_T)1U))

/* Computed Parameter: rtCP_POLY_TYPE_FUSED_BARRIER2_Value_k
 * Referenced by: '<S686>/POLY_TYPE_FUSED_BARRIER2'
 */
#define rtCP_POLY_TYPE_FUSED_BARRIER2_Value_k (((uint8_T)3U))

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER3_Value_p
 * Referenced by: '<S686>/POLY_TYPE_LM_BARRIER3'
 */
#define rtCP_POLY_TYPE_LM_BARRIER3_Value_p (((uint8_T)9U))

/* Computed Parameter: rtCP_POLY_TYPE_FUSED_BARRIER3_Value_n
 * Referenced by: '<S686>/POLY_TYPE_FUSED_BARRIER3'
 */
#define rtCP_POLY_TYPE_FUSED_BARRIER3_Value_n (((uint8_T)12U))

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER_Value_c
 * Referenced by: '<S686>/POLY_TYPE_LM_BARRIER'
 */
#define rtCP_POLY_TYPE_LM_BARRIER_Value_c (((uint8_T)5U))

/* Computed Parameter: rtCP_POLY_TYPE_FUSED_BARRIER_Value_f
 * Referenced by: '<S686>/POLY_TYPE_FUSED_BARRIER'
 */
#define rtCP_POLY_TYPE_FUSED_BARRIER_Value_f (((uint8_T)8U))

/* Expression: TJA_SP_TYPE_POONLY
 * Referenced by: '<S682>/TJA_SP_TYPE_POONLY'
 */
#define rtCP_TJA_SP_TYPE_POONLY_Value  (((uint8_T)4U))

/* Expression: k_LCK_MemBLane_MaxDist_m
 * Referenced by: '<S682>/k_LCK_MemBLane_MaxDist_m'
 */
#define rtCP_k_LCK_MemBLane_MaxDist_m_Value (((uint8_T)50U))

/* Expression: k_LCK_MemSLane_MaxDist_m
 * Referenced by: '<S682>/k_LCK_MemSLane_MaxDist_m'
 */
#define rtCP_k_LCK_MemSLane_MaxDist_m_Value (((uint8_T)20U))

/* Expression: TJA_SP_TYPE_POONLY
 * Referenced by: '<S676>/TJA_SP_TYPE_POBLM3'
 */
#define rtCP_TJA_SP_TYPE_POBLM3_Value  (((uint8_T)4U))

/* Expression: TJA_SP_CONF_MEDHIGH
 * Referenced by: '<S681>/TJA_SP_CONF_MEDHIGH4'
 */
#define rtCP_TJA_SP_CONF_MEDHIGH4_Value (((uint8_T)3U))

/* Expression: TJA_SP_TYPE_PORLM
 * Referenced by: '<S681>/TJA_SP_TYPE_POBLM4'
 */
#define rtCP_TJA_SP_TYPE_POBLM4_Value  (((uint8_T)6U))

/* Expression: TJA_SP_TYPE_POLLM
 * Referenced by: '<S681>/TJA_SP_TYPE_POBLM5'
 */
#define rtCP_TJA_SP_TYPE_POBLM5_Value  (((uint8_T)5U))

/* Expression: TJA_SP_CONF_MEDIUM
 * Referenced by: '<S681>/TJA_SP_CONF_MEDHIGH1'
 */
#define rtCP_TJA_SP_CONF_MEDHIGH1_Value_f (((uint8_T)2U))

/* Expression: TJA_SP_CONF_MEDHIGH
 * Referenced by: '<S681>/TJA_SP_CONF_MEDHIGH'
 */
#define rtCP_TJA_SP_CONF_MEDHIGH_Value (((uint8_T)3U))

/* Expression: k_LCK_POMaxRangeHys_m
 * Referenced by: '<S855>/k_LCK_POMaxRangeHys_m'
 */
#define rtCP_k_LCK_POMaxRangeHys_m_Value (((uint8_T)10U))

/* Expression: k_SPP_BLM_LowSpdMinConf
 * Referenced by: '<S681>/TJA_SP_CONF_MEDHIGH2'
 */
#define rtCP_TJA_SP_CONF_MEDHIGH2_Value_c (((uint8_T)1U))

/* Expression: TJA_SP_TYPE_BLMONLY
 * Referenced by: '<S681>/TJA_SP_TYPE_BLMONLY'
 */
#define rtCP_TJA_SP_TYPE_BLMONLY_Value (((uint8_T)3U))

/* Expression: k_SPP_SLM_LowSpdMinConf
 * Referenced by: '<S681>/TJA_SP_CONF_MEDHIGH3'
 */
#define rtCP_TJA_SP_CONF_MEDHIGH3_Value (((uint8_T)1U))

/* Expression: k_LBS_LaneBiasOvrdEn
 * Referenced by: '<S835>/k_LBS_LaneBiasOvrdEn'
 */
#define rtCP_k_LBS_LaneBiasOvrdEn_Value_e (((uint8_T)1U))

/* Expression: C_ZERO
 * Referenced by: '<S424>/Constant'
 */
#define rtCP_Constant_Value_kz         (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S424>/Constant1'
 */
#define rtCP_Constant1_Value_ea        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S436>/Constant15'
 */
#define rtCP_Constant15_Value_n        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_lle
 * Referenced by: '<S443>/Constant'
 */
#define rtCP_Constant_Value_lle        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant3_Value_o0
 * Referenced by: '<S443>/Constant3'
 */
#define rtCP_Constant3_Value_o0        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant4_Value_l3
 * Referenced by: '<S443>/Constant4'
 */
#define rtCP_Constant4_Value_l3        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_c1n
 * Referenced by: '<S444>/Constant'
 */
#define rtCP_Constant_Value_c1n        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant3_Value_j1
 * Referenced by: '<S444>/Constant3'
 */
#define rtCP_Constant3_Value_j1        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant4_Value_gm
 * Referenced by: '<S444>/Constant4'
 */
#define rtCP_Constant4_Value_gm        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_due
 * Referenced by: '<S445>/Constant'
 */
#define rtCP_Constant_Value_due        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant3_Value_bp
 * Referenced by: '<S445>/Constant3'
 */
#define rtCP_Constant3_Value_bp        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant4_Value_jen
 * Referenced by: '<S445>/Constant4'
 */
#define rtCP_Constant4_Value_jen       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_io
 * Referenced by: '<S447>/Constant'
 */
#define rtCP_Constant_Value_io         (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant3_Value_d5
 * Referenced by: '<S447>/Constant3'
 */
#define rtCP_Constant3_Value_d5        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant4_Value_an
 * Referenced by: '<S447>/Constant4'
 */
#define rtCP_Constant4_Value_an        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S448>/invalid'
 */
#define rtCP_invalid_Value             (((uint8_T)0U))

/* Computed Parameter: rtCP_new_Value
 * Referenced by: '<S448>/new'
 */
#define rtCP_new_Value                 (((uint8_T)2U))

/* Computed Parameter: rtCP_updated_Value
 * Referenced by: '<S448>/updated'
 */
#define rtCP_updated_Value             (((uint8_T)5U))

/* Expression: C_ZERO
 * Referenced by: '<S449>/invalid'
 */
#define rtCP_invalid_Value_d           (((uint8_T)0U))

/* Computed Parameter: rtCP_new_Value_a
 * Referenced by: '<S449>/new'
 */
#define rtCP_new_Value_a               (((uint8_T)2U))

/* Computed Parameter: rtCP_updated_Value_a
 * Referenced by: '<S449>/updated'
 */
#define rtCP_updated_Value_a           (((uint8_T)5U))

/* Expression: C_ZERO
 * Referenced by: '<S450>/invalid'
 */
#define rtCP_invalid_Value_n           (((uint8_T)0U))

/* Computed Parameter: rtCP_new_Value_k
 * Referenced by: '<S450>/new'
 */
#define rtCP_new_Value_k               (((uint8_T)2U))

/* Computed Parameter: rtCP_updated_Value_e
 * Referenced by: '<S450>/updated'
 */
#define rtCP_updated_Value_e           (((uint8_T)5U))

/* Expression: C_ZERO
 * Referenced by: '<S451>/invalid'
 */
#define rtCP_invalid_Value_j           (((uint8_T)0U))

/* Computed Parameter: rtCP_new_Value_l
 * Referenced by: '<S451>/new'
 */
#define rtCP_new_Value_l               (((uint8_T)2U))

/* Computed Parameter: rtCP_updated_Value_i
 * Referenced by: '<S451>/updated'
 */
#define rtCP_updated_Value_i           (((uint8_T)5U))

/* Computed Parameter: rtCP_Botts_Value
 * Referenced by: '<S452>/Botts'
 */
#define rtCP_Botts_Value               (((uint8_T)4U))

/* Computed Parameter: rtCP_DLM_Value
 * Referenced by: '<S452>/DLM'
 */
#define rtCP_DLM_Value                 (((uint8_T)8U))

/* Computed Parameter: rtCP_Dashed_Value
 * Referenced by: '<S452>/Dashed'
 */
#define rtCP_Dashed_Value              (((uint8_T)2U))

/* Computed Parameter: rtCP_Decel_Value
 * Referenced by: '<S452>/Decel'
 */
#define rtCP_Decel_Value               (((uint8_T)3U))

/* Computed Parameter: rtCP_Invalid_Value
 * Referenced by: '<S452>/Invalid'
 */
#define rtCP_Invalid_Value             (((uint8_T)0U))

/* Computed Parameter: rtCP_Solid_Value
 * Referenced by: '<S452>/Solid'
 */
#define rtCP_Solid_Value               (((uint8_T)1U))

/* Computed Parameter: rtCP_Undecided_Value
 * Referenced by: '<S452>/Undecided'
 */
#define rtCP_Undecided_Value           (((uint8_T)7U))

/* Computed Parameter: rtCP_Botts_Value_n
 * Referenced by: '<S453>/Botts'
 */
#define rtCP_Botts_Value_n             (((uint8_T)4U))

/* Computed Parameter: rtCP_DLM_Value_e
 * Referenced by: '<S453>/DLM'
 */
#define rtCP_DLM_Value_e               (((uint8_T)8U))

/* Computed Parameter: rtCP_Dashed_Value_n
 * Referenced by: '<S453>/Dashed'
 */
#define rtCP_Dashed_Value_n            (((uint8_T)2U))

/* Computed Parameter: rtCP_Decel_Value_o
 * Referenced by: '<S453>/Decel'
 */
#define rtCP_Decel_Value_o             (((uint8_T)3U))

/* Computed Parameter: rtCP_Invalid_Value_f
 * Referenced by: '<S453>/Invalid'
 */
#define rtCP_Invalid_Value_f           (((uint8_T)0U))

/* Computed Parameter: rtCP_Solid_Value_e
 * Referenced by: '<S453>/Solid'
 */
#define rtCP_Solid_Value_e             (((uint8_T)1U))

/* Computed Parameter: rtCP_Undecided_Value_g
 * Referenced by: '<S453>/Undecided'
 */
#define rtCP_Undecided_Value_g         (((uint8_T)7U))

/* Expression: C_ZERO
 * Referenced by: '<S436>/Constant14'
 */
#define rtCP_Constant14_Value_np       (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S436>/Constant6'
 */
#define rtCP_Constant6_Value_b0        (((uint8_T)0U))

/* Expression: k_LM_disable_window_sec
 * Referenced by: '<S469>/k_LM_disable_window_sec'
 */
#define rtCP_k_LM_disable_window_sec_Value (((uint8_T)10U))

/* Expression: k_LM_disable_LM_drops
 * Referenced by: '<S469>/k_LM_disable_LM_drops'
 */
#define rtCP_k_LM_disable_LM_drops_Value (((uint8_T)50U))

/* Expression: k_LM_disable_window_sec
 * Referenced by: '<S470>/k_LM_disable_window_sec'
 */
#define rtCP_k_LM_disable_window_sec_Value_i (((uint8_T)10U))

/* Expression: k_LM_disable_LM_drops
 * Referenced by: '<S470>/k_LM_disable_LM_drops'
 */
#define rtCP_k_LM_disable_LM_drops_Value_g (((uint8_T)50U))

/* Expression: k_LM_disable_window_sec
 * Referenced by: '<S471>/k_LM_disable_window_sec'
 */
#define rtCP_k_LM_disable_window_sec_Value_g (((uint8_T)10U))

/* Expression: k_LM_disable_LM_drops
 * Referenced by: '<S471>/k_LM_disable_LM_drops'
 */
#define rtCP_k_LM_disable_LM_drops_Value_o (((uint8_T)50U))

/* Expression: TYPE_RE
 * Referenced by: '<S484>/Constant'
 */
#define rtCP_Constant_Value_g1         (((uint8_T)2U))

/* Expression: TYPE_BARRIER
 * Referenced by: '<S484>/Constant4'
 */
#define rtCP_Constant4_Value_nm        (((uint8_T)3U))

/* Expression: TYPE_RE
 * Referenced by: '<S484>/Constant5'
 */
#define rtCP_Constant5_Value_ng        (((uint8_T)2U))

/* Expression: TYPE_BARRIER
 * Referenced by: '<S484>/Constant6'
 */
#define rtCP_Constant6_Value_md        (((uint8_T)3U))

/* Expression: TYPE_LM
 * Referenced by: '<S460>/Constant3'
 */
#define rtCP_Constant3_Value_ct        (((uint8_T)1U))

/* Expression: TYPE_NONE
 * Referenced by: '<S460>/Constant5'
 */
#define rtCP_Constant5_Value_b5        (((uint8_T)0U))

/* Expression: k_EP_sel_lane_boundary_source
 * Referenced by: '<S460>/k_sel_lane_boundary_source'
 */
#define rtCP_k_sel_lane_boundary_source_Value (((uint8_T)1U))

/* Expression: TYPE_LM
 * Referenced by: '<S461>/Constant5'
 */
#define rtCP_Constant5_Value_kp        (((uint8_T)1U))

/* Expression: TYPE_NONE
 * Referenced by: '<S461>/Constant6'
 */
#define rtCP_Constant6_Value_g0        (((uint8_T)0U))

/* Expression: k_EP_sel_lane_boundary_source
 * Referenced by: '<S461>/k_sel_lane_boundary_source'
 */
#define rtCP_k_sel_lane_boundary_source_Value_a (((uint8_T)1U))

/* Expression: TYPE_RE
 * Referenced by: '<S527>/Constant3'
 */
#define rtCP_Constant3_Value_lu        (((uint8_T)2U))

/* Expression: TYPE_BARRIER
 * Referenced by: '<S527>/Constant4'
 */
#define rtCP_Constant4_Value_nf        (((uint8_T)3U))

/* Expression: k_ME_Lane_Edge_Source
 * Referenced by: '<S527>/k_ME_Lane_Edge_Source'
 */
#define rtCP_k_ME_Lane_Edge_Source_Value (((uint8_T)0U))

/* Expression: TYPE_RE
 * Referenced by: '<S528>/Constant3'
 */
#define rtCP_Constant3_Value_lk        (((uint8_T)2U))

/* Expression: TYPE_BARRIER
 * Referenced by: '<S528>/Constant4'
 */
#define rtCP_Constant4_Value_dr        (((uint8_T)3U))

/* Expression: k_ME_Lane_Edge_Source
 * Referenced by: '<S528>/k_ME_Lane_Edge_Source'
 */
#define rtCP_k_ME_Lane_Edge_Source_Value_k (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S464>/Constant'
 */
#define rtCP_Constant_Value_n4         (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant10_Value_d
 * Referenced by: '<S618>/Constant10'
 */
#define rtCP_Constant10_Value_d        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant9_Value_j
 * Referenced by: '<S618>/Constant9'
 */
#define rtCP_Constant9_Value_j         (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_f05
 * Referenced by: '<S634>/Constant'
 */
#define rtCP_Constant_Value_f05        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant2_Value_nhf
 * Referenced by: '<S634>/Constant2'
 */
#define rtCP_Constant2_Value_nhf       (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant_Value_mw3
 * Referenced by: '<S642>/Constant'
 */
#define rtCP_Constant_Value_mw3        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant2_Value_co
 * Referenced by: '<S642>/Constant2'
 */
#define rtCP_Constant2_Value_co        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant1_Value_jf
 * Referenced by: '<S621>/Constant1'
 */
#define rtCP_Constant1_Value_jf        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant7_Value_jv
 * Referenced by: '<S621>/Constant7'
 */
#define rtCP_Constant7_Value_jv        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant10_Value_af
 * Referenced by: '<S655>/Constant10'
 */
#define rtCP_Constant10_Value_af       (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant11_Value_ms
 * Referenced by: '<S655>/Constant11'
 */
#define rtCP_Constant11_Value_ms       (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant2_Value_cv
 * Referenced by: '<S655>/Constant2'
 */
#define rtCP_Constant2_Value_cv        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant7_Value_ix
 * Referenced by: '<S655>/Constant7'
 */
#define rtCP_Constant7_Value_ix        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant8_Value_gg
 * Referenced by: '<S655>/Constant8'
 */
#define rtCP_Constant8_Value_gg        (((uint8_T)1U))

/* Computed Parameter: rtCP_k_EP_major_version_Value
 * Referenced by: '<S424>/k_EP_major_version'
 */
#define rtCP_k_EP_major_version_Value  (((uint8_T)0U))

/* Computed Parameter: rtCP_k_EP_minor_version_Value
 * Referenced by: '<S424>/k_EP_minor_version'
 */
#define rtCP_k_EP_minor_version_Value  (((uint8_T)7U))

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER_Value_n
 * Referenced by: '<S865>/POLY_TYPE_LM_BARRIER'
 */
#define rtCP_POLY_TYPE_LM_BARRIER_Value_n (((uint8_T)5U))

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER1_Value_n
 * Referenced by: '<S865>/POLY_TYPE_LM_BARRIER1'
 */
#define rtCP_POLY_TYPE_LM_BARRIER1_Value_n (((uint8_T)0U))

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER3_Value_a
 * Referenced by: '<S865>/POLY_TYPE_LM_BARRIER3'
 */
#define rtCP_POLY_TYPE_LM_BARRIER3_Value_a (((uint8_T)5U))

/* Computed Parameter: rtCP_POLY_TYPE_LM_BARRIER4_Value
 * Referenced by: '<S865>/POLY_TYPE_LM_BARRIER4'
 */
#define rtCP_POLY_TYPE_LM_BARRIER4_Value (((uint8_T)0U))

/* Expression: AES_ESA_MODE_ABORTED
 * Referenced by: '<S9>/AESESA_Mode_Manager'
 */
#define rtCP_AESESA_Mode_Manager_AES_ESA_MODE_ABORTED (((uint8_T)7U))

/* Expression: AES_ESA_MODE_AESACTIVE
 * Referenced by: '<S9>/AESESA_Mode_Manager'
 */
#define rtCP_AESESA_Mode_Manager_AES_ESA_MODE_AESACTIVE (((uint8_T)4U))

/* Expression: AES_ESA_MODE_COMPLETED
 * Referenced by: '<S9>/AESESA_Mode_Manager'
 */
#define rtCP_AESESA_Mode_Manager_AES_ESA_MODE_COMPLETED (((uint8_T)6U))

/* Expression: AES_ESA_MODE_ESAACTIVE
 * Referenced by: '<S9>/AESESA_Mode_Manager'
 */
#define rtCP_AESESA_Mode_Manager_AES_ESA_MODE_ESAACTIVE (((uint8_T)5U))

/* Expression: AES_ESA_MODE_FAILURE
 * Referenced by: '<S9>/AESESA_Mode_Manager'
 */
#define rtCP_AESESA_Mode_Manager_AES_ESA_MODE_FAILURE (((uint8_T)0U))

/* Expression: AES_ESA_MODE_OFF
 * Referenced by: '<S9>/AESESA_Mode_Manager'
 */
#define rtCP_AESESA_Mode_Manager_AES_ESA_MODE_OFF (((uint8_T)1U))

/* Expression: AES_ESA_MODE_PASSIVE
 * Referenced by: '<S9>/AESESA_Mode_Manager'
 */
#define rtCP_AESESA_Mode_Manager_AES_ESA_MODE_PASSIVE (((uint8_T)2U))

/* Expression: AES_ESA_MODE_STANDBY
 * Referenced by: '<S9>/AESESA_Mode_Manager'
 */
#define rtCP_AESESA_Mode_Manager_AES_ESA_MODE_STANDBY (((uint8_T)3U))

/* Computed Parameter: rtCP_AES_ESA_Minor_Version_Value
 * Referenced by: '<S1>/AES_ESA_Minor_Version'
 */
#define rtCP_AES_ESA_Minor_Version_Value (((uint8_T)7U))

/* Expression: k_AES_NoLaneLine_Flag
 * Referenced by: '<S1>/Constant1'
 */
#define rtCP_Constant1_Value_bg        (((uint8_T)0U))

/* Expression: uint8(1)
 * Referenced by: '<S58>/k_LCK_useAbnormalTrajHeadingLimit'
 */
#define rtCP_k_LCK_useAbnormalTrajHeadingLimit_Value (((uint8_T)1U))

/* Expression: uint8(1)
 * Referenced by: '<S59>/k_LCK_useAbnormalTrajRateLimit'
 */
#define rtCP_k_LCK_useAbnormalTrajRateLimit_Value (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_jx
 * Referenced by: '<S26>/Constant'
 */
#define rtCP_Constant_Value_jx         (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant_Value_jg
 * Referenced by: '<S27>/Constant'
 */
#define rtCP_Constant_Value_jg         (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant_Value_bk
 * Referenced by: '<S28>/Constant'
 */
#define rtCP_Constant_Value_bk         (((uint8_T)2U))

/* Expression: const
 * Referenced by: '<S29>/Constant'
 */
#define rtCP_Constant_Value_mfw        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant_Value_ebs
 * Referenced by: '<S30>/Constant'
 */
#define rtCP_Constant_Value_ebs        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant_Value_mfx
 * Referenced by: '<S31>/Constant'
 */
#define rtCP_Constant_Value_mfx        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_fer
 * Referenced by: '<S32>/Constant'
 */
#define rtCP_Constant_Value_fer        (((uint8_T)3U))

/* Expression: const
 * Referenced by: '<S152>/Constant'
 */
#define rtCP_Constant_Value_a5         (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant_Value_of
 * Referenced by: '<S154>/Constant'
 */
#define rtCP_Constant_Value_of         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_f4
 * Referenced by: '<S155>/Constant'
 */
#define rtCP_Constant_Value_f4         (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant_Value_g2
 * Referenced by: '<S156>/Constant'
 */
#define rtCP_Constant_Value_g2         (((uint8_T)5U))

/* Expression: C_ZERO
 * Referenced by: '<S172>/Constant19'
 */
#define rtCP_Constant19_Value_h        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S176>/Constant6'
 */
#define rtCP_Constant6_Value_es        (((uint8_T)0U))

/* Expression: C_ONE
 * Referenced by: '<S176>/Constant7'
 */
#define rtCP_Constant7_Value_h5        (((uint8_T)1U))

/* Expression: C_ZERO
 * Referenced by: '<S177>/Constant1'
 */
#define rtCP_Constant1_Value_fe        (((uint8_T)0U))

/* Expression: C_ONE
 * Referenced by: '<S177>/Constant2'
 */
#define rtCP_Constant2_Value_gsp       (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_n3w
 * Referenced by: '<S200>/Constant'
 */
#define rtCP_Constant_Value_n3w        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_cti
 * Referenced by: '<S185>/Constant'
 */
#define rtCP_Constant_Value_cti        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_o5
 * Referenced by: '<S186>/Constant'
 */
#define rtCP_Constant_Value_o5         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_b4
 * Referenced by: '<S188>/Constant'
 */
#define rtCP_Constant_Value_b4         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_lg
 * Referenced by: '<S206>/Constant'
 */
#define rtCP_Constant_Value_lg         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_m53
 * Referenced by: '<S207>/Constant'
 */
#define rtCP_Constant_Value_m53        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_cs
 * Referenced by: '<S208>/Constant'
 */
#define rtCP_Constant_Value_cs         (((uint8_T)1U))

/* Expression: k_LCK_Use_AdaptWhlAngComp
 * Referenced by: '<S179>/k_LCK_Use_AdaptWhlAngComp'
 */
#define rtCP_k_LCK_Use_AdaptWhlAngComp_Value (((uint8_T)0U))

/* Expression: k_LCK_Use_WhlAngComp
 * Referenced by: '<S179>/k_LCK_Use_WhlAngComp'
 */
#define rtCP_k_LCK_Use_WhlAngComp_Value (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_pk
 * Referenced by: '<S212>/Constant'
 */
#define rtCP_Constant_Value_pk         (((uint8_T)1U))

/* Expression: C_FOUR
 * Referenced by: '<S213>/Constant'
 */
#define rtCP_Constant_Value_hh3        (((uint8_T)4U))

/* Expression: C_THREE
 * Referenced by: '<S213>/Constant1'
 */
#define rtCP_Constant1_Value_b4        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant_Value_ck
 * Referenced by: '<S220>/Constant'
 */
#define rtCP_Constant_Value_ck         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_ire
 * Referenced by: '<S246>/Constant'
 */
#define rtCP_Constant_Value_ire        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_nl
 * Referenced by: '<S247>/Constant'
 */
#define rtCP_Constant_Value_nl         (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant_Value_jem
 * Referenced by: '<S249>/Constant'
 */
#define rtCP_Constant_Value_jem        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant_Value_mr
 * Referenced by: '<S250>/Constant'
 */
#define rtCP_Constant_Value_mr         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_egl
 * Referenced by: '<S251>/Constant'
 */
#define rtCP_Constant_Value_egl        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant_Value_m2w
 * Referenced by: '<S252>/Constant'
 */
#define rtCP_Constant_Value_m2w        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant13_Value_o5
 * Referenced by: '<S4>/Constant13'
 */
#define rtCP_Constant13_Value_o5       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant14_Value_js
 * Referenced by: '<S4>/Constant14'
 */
#define rtCP_Constant14_Value_js       (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant_Value_a4
 * Referenced by: '<S258>/Constant'
 */
#define rtCP_Constant_Value_a4         (((uint8_T)255U))

/* Expression: uint8(1)
 * Referenced by: '<S254>/Constant'
 */
#define rtCP_Constant_Value_lw         (((uint8_T)1U))

/* Expression: uint8(0)
 * Referenced by: '<S254>/Constant1'
 */
#define rtCP_Constant1_Value_pa        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant15_Value_a
 * Referenced by: '<S281>/Constant15'
 */
#define rtCP_Constant15_Value_a        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant17_Value_gf
 * Referenced by: '<S281>/Constant17'
 */
#define rtCP_Constant17_Value_gf       (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_oc
 * Referenced by: '<S367>/Constant'
 */
#define rtCP_Constant_Value_oc         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_or
 * Referenced by: '<S366>/Constant'
 */
#define rtCP_Constant_Value_or         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_ld
 * Referenced by: '<S262>/Constant'
 */
#define rtCP_Constant_Value_ld         (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant_Value_cc
 * Referenced by: '<S263>/Constant'
 */
#define rtCP_Constant_Value_cc         (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant_Value_nt
 * Referenced by: '<S264>/Constant'
 */
#define rtCP_Constant_Value_nt         (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_ds
 * Referenced by: '<S265>/Constant'
 */
#define rtCP_Constant_Value_ds         (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant_Value_kl
 * Referenced by: '<S266>/Constant'
 */
#define rtCP_Constant_Value_kl         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_dq
 * Referenced by: '<S267>/Constant'
 */
#define rtCP_Constant_Value_dq         (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant_Value_pj
 * Referenced by: '<S5>/Constant'
 */
#define rtCP_Constant_Value_pj         (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_fx
 * Referenced by: '<S407>/Constant'
 */
#define rtCP_Constant_Value_fx         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_hc
 * Referenced by: '<S408>/Constant'
 */
#define rtCP_Constant_Value_hc         (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_ih
 * Referenced by: '<S409>/Constant'
 */
#define rtCP_Constant_Value_ih         (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_ci
 * Referenced by: '<S410>/Constant'
 */
#define rtCP_Constant_Value_ci         (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant11_Value_i2
 * Referenced by: '<S268>/Constant11'
 */
#define rtCP_Constant11_Value_i2       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant12_Value_nc
 * Referenced by: '<S268>/Constant12'
 */
#define rtCP_Constant12_Value_nc       (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant3_Value_ij
 * Referenced by: '<S268>/Constant3'
 */
#define rtCP_Constant3_Value_ij        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant4_Value_pu
 * Referenced by: '<S268>/Constant4'
 */
#define rtCP_Constant4_Value_pu        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant6_Value_fy
 * Referenced by: '<S268>/Constant6'
 */
#define rtCP_Constant6_Value_fy        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant7_Value_it
 * Referenced by: '<S268>/Constant7'
 */
#define rtCP_Constant7_Value_it        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant8_Value_eq1
 * Referenced by: '<S268>/Constant8'
 */
#define rtCP_Constant8_Value_eq1       (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant1_Value_m4
 * Referenced by: '<S877>/Constant1'
 */
#define rtCP_Constant1_Value_m4        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant11_Value_o4
 * Referenced by: '<S877>/Constant11'
 */
#define rtCP_Constant11_Value_o4       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant2_Value_at
 * Referenced by: '<S877>/Constant2'
 */
#define rtCP_Constant2_Value_at        (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant3_Value_ab
 * Referenced by: '<S877>/Constant3'
 */
#define rtCP_Constant3_Value_ab        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant4_Value_hb
 * Referenced by: '<S877>/Constant4'
 */
#define rtCP_Constant4_Value_hb        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant5_Value_hq
 * Referenced by: '<S877>/Constant5'
 */
#define rtCP_Constant5_Value_hq        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant6_Value_mx
 * Referenced by: '<S877>/Constant6'
 */
#define rtCP_Constant6_Value_mx        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant7_Value_jj
 * Referenced by: '<S877>/Constant7'
 */
#define rtCP_Constant7_Value_jj        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant8_Value_n0
 * Referenced by: '<S877>/Constant8'
 */
#define rtCP_Constant8_Value_n0        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant9_Value_on
 * Referenced by: '<S877>/Constant9'
 */
#define rtCP_Constant9_Value_on        (((uint8_T)7U))

/* Computed Parameter: rtCP_Constant_Value_pno
 * Referenced by: '<S881>/Constant'
 */
#define rtCP_Constant_Value_pno        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant1_Value_ao
 * Referenced by: '<S881>/Constant1'
 */
#define rtCP_Constant1_Value_ao        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant10_Value_k5p
 * Referenced by: '<S881>/Constant10'
 */
#define rtCP_Constant10_Value_k5p      (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant11_Value_bl
 * Referenced by: '<S881>/Constant11'
 */
#define rtCP_Constant11_Value_bl       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant12_Value_bj
 * Referenced by: '<S881>/Constant12'
 */
#define rtCP_Constant12_Value_bj       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant13_Value_m4
 * Referenced by: '<S881>/Constant13'
 */
#define rtCP_Constant13_Value_m4       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant14_Value_jn
 * Referenced by: '<S881>/Constant14'
 */
#define rtCP_Constant14_Value_jn       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant15_Value_d
 * Referenced by: '<S881>/Constant15'
 */
#define rtCP_Constant15_Value_d        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant16_Value_b
 * Referenced by: '<S881>/Constant16'
 */
#define rtCP_Constant16_Value_b        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant17_Value_a2
 * Referenced by: '<S881>/Constant17'
 */
#define rtCP_Constant17_Value_a2       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant18_Value_pp
 * Referenced by: '<S881>/Constant18'
 */
#define rtCP_Constant18_Value_pp       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant19_Value_lz
 * Referenced by: '<S881>/Constant19'
 */
#define rtCP_Constant19_Value_lz       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant2_Value_cot
 * Referenced by: '<S881>/Constant2'
 */
#define rtCP_Constant2_Value_cot       (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant20_Value_on
 * Referenced by: '<S881>/Constant20'
 */
#define rtCP_Constant20_Value_on       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant21_Value_n
 * Referenced by: '<S881>/Constant21'
 */
#define rtCP_Constant21_Value_n        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant22_Value_d
 * Referenced by: '<S881>/Constant22'
 */
#define rtCP_Constant22_Value_d        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant23_Value_e
 * Referenced by: '<S881>/Constant23'
 */
#define rtCP_Constant23_Value_e        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant24_Value_l
 * Referenced by: '<S881>/Constant24'
 */
#define rtCP_Constant24_Value_l        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant25_Value_j
 * Referenced by: '<S881>/Constant25'
 */
#define rtCP_Constant25_Value_j        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant26_Value_p
 * Referenced by: '<S881>/Constant26'
 */
#define rtCP_Constant26_Value_p        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant27_Value_j
 * Referenced by: '<S881>/Constant27'
 */
#define rtCP_Constant27_Value_j        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant28_Value_m
 * Referenced by: '<S881>/Constant28'
 */
#define rtCP_Constant28_Value_m        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant29_Value_ez
 * Referenced by: '<S881>/Constant29'
 */
#define rtCP_Constant29_Value_ez       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant3_Value_gz
 * Referenced by: '<S881>/Constant3'
 */
#define rtCP_Constant3_Value_gz        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant30_Value_k
 * Referenced by: '<S881>/Constant30'
 */
#define rtCP_Constant30_Value_k        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant31_Value_m
 * Referenced by: '<S881>/Constant31'
 */
#define rtCP_Constant31_Value_m        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant32_Value_m
 * Referenced by: '<S881>/Constant32'
 */
#define rtCP_Constant32_Value_m        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant33_Value_k
 * Referenced by: '<S881>/Constant33'
 */
#define rtCP_Constant33_Value_k        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant34_Value_i
 * Referenced by: '<S881>/Constant34'
 */
#define rtCP_Constant34_Value_i        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant4_Value_mn
 * Referenced by: '<S881>/Constant4'
 */
#define rtCP_Constant4_Value_mn        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant5_Value_bh
 * Referenced by: '<S881>/Constant5'
 */
#define rtCP_Constant5_Value_bh        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant6_Value_km
 * Referenced by: '<S881>/Constant6'
 */
#define rtCP_Constant6_Value_km        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant7_Value_o
 * Referenced by: '<S881>/Constant7'
 */
#define rtCP_Constant7_Value_o         (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant8_Value_ey
 * Referenced by: '<S881>/Constant8'
 */
#define rtCP_Constant8_Value_ey        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant9_Value_bh
 * Referenced by: '<S881>/Constant9'
 */
#define rtCP_Constant9_Value_bh        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant1_Value_go
 * Referenced by: '<S882>/Constant1'
 */
#define rtCP_Constant1_Value_go        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant11_Value_bb
 * Referenced by: '<S882>/Constant11'
 */
#define rtCP_Constant11_Value_bb       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant2_Value_ew
 * Referenced by: '<S882>/Constant2'
 */
#define rtCP_Constant2_Value_ew        (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant3_Value_ei
 * Referenced by: '<S882>/Constant3'
 */
#define rtCP_Constant3_Value_ei        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant4_Value_nn
 * Referenced by: '<S882>/Constant4'
 */
#define rtCP_Constant4_Value_nn        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant5_Value_nt
 * Referenced by: '<S882>/Constant5'
 */
#define rtCP_Constant5_Value_nt        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant6_Value_na
 * Referenced by: '<S882>/Constant6'
 */
#define rtCP_Constant6_Value_na        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant7_Value_c2
 * Referenced by: '<S882>/Constant7'
 */
#define rtCP_Constant7_Value_c2        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant8_Value_e2
 * Referenced by: '<S882>/Constant8'
 */
#define rtCP_Constant8_Value_e2        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant9_Value_iu
 * Referenced by: '<S882>/Constant9'
 */
#define rtCP_Constant9_Value_iu        (((uint8_T)7U))

/* Computed Parameter: rtCP_Constant_Value_pc
 * Referenced by: '<S886>/Constant'
 */
#define rtCP_Constant_Value_pc         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant1_Value_au
 * Referenced by: '<S886>/Constant1'
 */
#define rtCP_Constant1_Value_au        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant10_Value_e4
 * Referenced by: '<S886>/Constant10'
 */
#define rtCP_Constant10_Value_e4       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant11_Value_bf
 * Referenced by: '<S886>/Constant11'
 */
#define rtCP_Constant11_Value_bf       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant12_Value_d
 * Referenced by: '<S886>/Constant12'
 */
#define rtCP_Constant12_Value_d        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant13_Value_i
 * Referenced by: '<S886>/Constant13'
 */
#define rtCP_Constant13_Value_i        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant14_Value_p1
 * Referenced by: '<S886>/Constant14'
 */
#define rtCP_Constant14_Value_p1       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant15_Value_e
 * Referenced by: '<S886>/Constant15'
 */
#define rtCP_Constant15_Value_e        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant16_Value_ia
 * Referenced by: '<S886>/Constant16'
 */
#define rtCP_Constant16_Value_ia       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant17_Value_ky
 * Referenced by: '<S886>/Constant17'
 */
#define rtCP_Constant17_Value_ky       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant18_Value_pn
 * Referenced by: '<S886>/Constant18'
 */
#define rtCP_Constant18_Value_pn       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant19_Value_hl
 * Referenced by: '<S886>/Constant19'
 */
#define rtCP_Constant19_Value_hl       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant2_Value_jj
 * Referenced by: '<S886>/Constant2'
 */
#define rtCP_Constant2_Value_jj        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant20_Value_n
 * Referenced by: '<S886>/Constant20'
 */
#define rtCP_Constant20_Value_n        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant21_Value_jw
 * Referenced by: '<S886>/Constant21'
 */
#define rtCP_Constant21_Value_jw       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant22_Value_i
 * Referenced by: '<S886>/Constant22'
 */
#define rtCP_Constant22_Value_i        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant23_Value_h
 * Referenced by: '<S886>/Constant23'
 */
#define rtCP_Constant23_Value_h        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant24_Value_e
 * Referenced by: '<S886>/Constant24'
 */
#define rtCP_Constant24_Value_e        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant25_Value_h2
 * Referenced by: '<S886>/Constant25'
 */
#define rtCP_Constant25_Value_h2       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant26_Value_n
 * Referenced by: '<S886>/Constant26'
 */
#define rtCP_Constant26_Value_n        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant27_Value_fl
 * Referenced by: '<S886>/Constant27'
 */
#define rtCP_Constant27_Value_fl       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant28_Value_l
 * Referenced by: '<S886>/Constant28'
 */
#define rtCP_Constant28_Value_l        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant29_Value_p
 * Referenced by: '<S886>/Constant29'
 */
#define rtCP_Constant29_Value_p        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant3_Value_dh
 * Referenced by: '<S886>/Constant3'
 */
#define rtCP_Constant3_Value_dh        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant30_Value_cw
 * Referenced by: '<S886>/Constant30'
 */
#define rtCP_Constant30_Value_cw       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant31_Value_d
 * Referenced by: '<S886>/Constant31'
 */
#define rtCP_Constant31_Value_d        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant32_Value_l
 * Referenced by: '<S886>/Constant32'
 */
#define rtCP_Constant32_Value_l        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant33_Value_d
 * Referenced by: '<S886>/Constant33'
 */
#define rtCP_Constant33_Value_d        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant34_Value_jf
 * Referenced by: '<S886>/Constant34'
 */
#define rtCP_Constant34_Value_jf       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant4_Value_gr
 * Referenced by: '<S886>/Constant4'
 */
#define rtCP_Constant4_Value_gr        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant5_Value_ho
 * Referenced by: '<S886>/Constant5'
 */
#define rtCP_Constant5_Value_ho        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant6_Value_kg
 * Referenced by: '<S886>/Constant6'
 */
#define rtCP_Constant6_Value_kg        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant7_Value_mr
 * Referenced by: '<S886>/Constant7'
 */
#define rtCP_Constant7_Value_mr        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant8_Value_li
 * Referenced by: '<S886>/Constant8'
 */
#define rtCP_Constant8_Value_li        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant9_Value_ak
 * Referenced by: '<S886>/Constant9'
 */
#define rtCP_Constant9_Value_ak        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant_Value_pbt
 * Referenced by: '<S7>/Constant'
 */
#define rtCP_Constant_Value_pbt        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant1_Value_my
 * Referenced by: '<S7>/Constant1'
 */
#define rtCP_Constant1_Value_my        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_cix
 * Referenced by: '<S962>/Constant'
 */
#define rtCP_Constant_Value_cix        (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant_Value_az
 * Referenced by: '<S963>/Constant'
 */
#define rtCP_Constant_Value_az         (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant_Value_ec
 * Referenced by: '<S964>/Constant'
 */
#define rtCP_Constant_Value_ec         (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_iv5
 * Referenced by: '<S966>/Constant'
 */
#define rtCP_Constant_Value_iv5        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant_Value_o4
 * Referenced by: '<S968>/Constant'
 */
#define rtCP_Constant_Value_o4         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_ed
 * Referenced by: '<S969>/Constant'
 */
#define rtCP_Constant_Value_ed         (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant_Value_ky
 * Referenced by: '<S1001>/Constant'
 */
#define rtCP_Constant_Value_ky         (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_lj4
 * Referenced by: '<S1002>/Constant'
 */
#define rtCP_Constant_Value_lj4        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_fx3
 * Referenced by: '<S1003>/Constant'
 */
#define rtCP_Constant_Value_fx3        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant_Value_oh
 * Referenced by: '<S1004>/Constant'
 */
#define rtCP_Constant_Value_oh         (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant_Value_c1v
 * Referenced by: '<S1005>/Constant'
 */
#define rtCP_Constant_Value_c1v        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_eza
 * Referenced by: '<S1006>/Constant'
 */
#define rtCP_Constant_Value_eza        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_gk3
 * Referenced by: '<S1007>/Constant'
 */
#define rtCP_Constant_Value_gk3        (((uint8_T)3U))

/* Expression: const
 * Referenced by: '<S1008>/Constant'
 */
#define rtCP_Constant_Value_i4         (((uint8_T)4U))

/* Expression: const
 * Referenced by: '<S1009>/Constant'
 */
#define rtCP_Constant_Value_bzq        (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant_Value_nu
 * Referenced by: '<S1010>/Constant'
 */
#define rtCP_Constant_Value_nu         (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant_Value_gi3
 * Referenced by: '<S1011>/Constant'
 */
#define rtCP_Constant_Value_gi3        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_l3
 * Referenced by: '<S1012>/Constant'
 */
#define rtCP_Constant_Value_l3         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_ii
 * Referenced by: '<S1013>/Constant'
 */
#define rtCP_Constant_Value_ii         (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant5_Value_gf
 * Referenced by: '<S9>/Constant5'
 */
#define rtCP_Constant5_Value_gf        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_pbc
 * Referenced by: '<S1052>/Constant'
 */
#define rtCP_Constant_Value_pbc        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_k3
 * Referenced by: '<S1058>/Constant'
 */
#define rtCP_Constant_Value_k3         (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant_Value_hfj
 * Referenced by: '<S1059>/Constant'
 */
#define rtCP_Constant_Value_hfj        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_lwj
 * Referenced by: '<S1063>/Constant'
 */
#define rtCP_Constant_Value_lwj        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant_Value_hfa
 * Referenced by: '<S1064>/Constant'
 */
#define rtCP_Constant_Value_hfa        (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant_Value_nu0
 * Referenced by: '<S1065>/Constant'
 */
#define rtCP_Constant_Value_nu0        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_abd
 * Referenced by: '<S1066>/Constant'
 */
#define rtCP_Constant_Value_abd        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant_Value_aj0
 * Referenced by: '<S1067>/Constant'
 */
#define rtCP_Constant_Value_aj0        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_e5
 * Referenced by: '<S1068>/Constant'
 */
#define rtCP_Constant_Value_e5         (((uint8_T)0U))

/* Expression: const
 * Referenced by: '<S1081>/Constant'
 */
#define rtCP_Constant_Value_em         (((uint8_T)4U))

/* Expression: const
 * Referenced by: '<S1083>/Constant'
 */
#define rtCP_Constant_Value_j5         (((uint8_T)5U))

/* Computed Parameter: rtCP_Constant_Value_gh
 * Referenced by: '<S1091>/Constant'
 */
#define rtCP_Constant_Value_gh         (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_eo4
 * Referenced by: '<S1092>/Constant'
 */
#define rtCP_Constant_Value_eo4        (((uint8_T)9U))

/* Computed Parameter: rtCP_Constant_Value_nfu
 * Referenced by: '<S1094>/Constant'
 */
#define rtCP_Constant_Value_nfu        (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant_Value_ei
 * Referenced by: '<S1095>/Constant'
 */
#define rtCP_Constant_Value_ei         (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_gjl
 * Referenced by: '<S1096>/Constant'
 */
#define rtCP_Constant_Value_gjl        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant_Value_if
 * Referenced by: '<S1097>/Constant'
 */
#define rtCP_Constant_Value_if         (((uint8_T)10U))

/* Expression: AES_ESA_MODE_ESAACTIVE
 * Referenced by: '<S1016>/Constant26'
 */
#define rtCP_Constant26_Value_il       (((uint8_T)5U))

/* Expression: AES_ESA_MODE_AESACTIVE
 * Referenced by: '<S1016>/Constant8'
 */
#define rtCP_Constant8_Value_id3       (((uint8_T)4U))

/* Expression: AES_ESA_MODE_OFF
 * Referenced by: '<S9>/Unit Delay1'
 */
#define rtCP_UnitDelay1_InitialCondition_ft (((uint8_T)1U))

/* Computed Parameter: rtCP_Gain52_Gain
 * Referenced by: '<S1016>/Gain52'
 */
#define rtCP_Gain52_Gain               (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain7_Gain_j
 * Referenced by: '<S1016>/Gain7'
 */
#define rtCP_Gain7_Gain_j              (((uint8_T)128U))

/* Computed Parameter: rtCP_Gain23_Gain_g
 * Referenced by: '<S1016>/Gain23'
 */
#define rtCP_Gain23_Gain_g             (((uint8_T)128U))

extern void AES_ESA_SWC_TriggerHold_Init(real_T *rty_Out, real_T *rty_count);
extern void AES_ESA_SWC_TriggerHold(real_T rtu_Trigger, real_T rtu_hold_time,
  real_T *rty_Out, real_T *rty_count);
extern real32_T AES_ESA_SWC_First_Order_Lag_Filter(real32_T rtu_unfiltered_input,
  const ConstB_First_Order_Lag_Filter_AES_ESA_SWC_T *localC,
  DW_First_Order_Lag_Filter_AES_ESA_SWC_T *localDW);
extern real32_T AES_ESA_SWC_First_Order_Lag_Filter_LIB(real32_T
  rtu_unfiltered_input, const ConstB_First_Order_Lag_Filter_LIB_AES_ESA_SWC_T
  *localC, DW_First_Order_Lag_Filter_LIB_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_Chart_Init(boolean_T *rty_f_DecStrWhlAngComp, real32_T
  *rty_Time);
extern void AES_ESA_SWC_Chart(boolean_T rtu_f_OffsetOk, real32_T rtu_ML_Time_Sec,
  real32_T rtu_SustainTime, real32_T rtu_Time_n_1, boolean_T
  *rty_f_DecStrWhlAngComp, real32_T *rty_Time);
extern void AES_ESA_SWC_Delay_Trig_Init(boolean_T *rty_Delay_Trig,
  DW_Delay_Trig_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_Delay_Trig(real32_T rtu_Input, real32_T
  rtu_Delay_Trig_Time, boolean_T *rty_Delay_Trig, DW_Delay_Trig_AES_ESA_SWC_T
  *localDW);
extern void AES_ESA_SWC_MATLABFunction(real32_T rtu_C0, real32_T rtu_C1,
  real32_T rtu_C2, real32_T rtu_C3, real32_T rtu_C4, real32_T rtu_C5, real32_T
  rtu_pred_xx, real32_T *rty_pred_y, real32_T *rty_pred_dy, real32_T
  *rty_pred_ddy, real32_T *rty_pred_curve);
extern void AES_ESA_SWC_AES_Ramp_Coe_Chart_Init(real32_T *rty_Out,
  DW_AES_Ramp_Coe_Chart_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_AES_Ramp_Coe_Chart(boolean_T rtu_Actv, real32_T
  rtu_TmeThd, boolean_T rtu_Active_Raise, real32_T *rty_Out,
  DW_AES_Ramp_Coe_Chart_AES_ESA_SWC_T *localDW);
extern real32_T AES_ESA_SWC_First_Order_Lag_Filter_LIB1(real32_T
  rtu_unfiltered_input, const ConstB_First_Order_Lag_Filter_LIB1_AES_ESA_SWC_T
  *localC, DW_First_Order_Lag_Filter_LIB1_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_Delay_Trig_k_Init(boolean_T *rty_Delay_Trig,
  DW_Delay_Trig_AES_ESA_SWC_a_T *localDW);
extern void AES_ESA_SWC_Delay_Trig_h(real32_T rtu_Input, real32_T
  rtu_Delay_Trig_Time, boolean_T *rty_Delay_Trig, DW_Delay_Trig_AES_ESA_SWC_a_T *
  localDW);
extern real32_T AES_ESA_SWC_Rate_Limiter1(real32_T rtu_Rate_Limited_Input, const
  ConstB_Rate_Limiter1_AES_ESA_SWC_T *localC, DW_Rate_Limiter1_AES_ESA_SWC_T
  *localDW);
extern void AES_ESA_SWC_lane_edge_age_check_Init(real32_T *rty_mature, real32_T *
  rty_i, DW_lane_edge_age_check_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_lane_edge_age_check(boolean_T rtu_marker_valid, real32_T
  rtu_k_AES_DuringTime, real32_T *rty_mature, real32_T *rty_i,
  DW_lane_edge_age_check_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_OnDelay5_Init(uint8_T *rty_flg,
  DW_OnDelay5_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_OnDelay5(boolean_T rtu_in, real32_T rtu_delay_time,
  uint8_T *rty_flg, DW_OnDelay5_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_signal_sustain_Init(real32_T *rty_sustain_value,
  DW_signal_sustain_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_signal_sustain(real32_T rtu_input, real32_T
  rtu_sustain_time, boolean_T rtu_clear, real32_T *rty_sustain_value,
  DW_signal_sustain_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_hold_then_fade_Init(real32_T *rty_gain,
  DW_hold_then_fade_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_hold_then_fade(real32_T rtu_hold_dur_msec, boolean_T
  rtu_valid_state, boolean_T rtu_enable_gain, real32_T rtu_fading_gain, real32_T
  *rty_gain, DW_hold_then_fade_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_First_Order_Lag_Filter_w_IC_LIB_Init
  (DW_First_Order_Lag_Filter_w_IC_LIB_AES_ESA_SWC_T *localDW);
extern real32_T AES_ESA_SWC_First_Order_Lag_Filter_w_IC_LIB(real32_T
  rtu_unfiltered_input, const
  ConstB_First_Order_Lag_Filter_w_IC_LIB_AES_ESA_SWC_T *localC,
  DW_First_Order_Lag_Filter_w_IC_LIB_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_signal_hold_until_trig_Init(boolean_T *rty_hold_output,
  DW_signal_hold_until_trig_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_signal_hold_until_trig(boolean_T rtu_set, boolean_T
  rtu_clear, boolean_T *rty_hold_output, DW_signal_hold_until_trig_AES_ESA_SWC_T
  *localDW);
extern void AES_ESA_SWC_Sustain_wo_reset_Init(real32_T *rty_sustain_value,
  DW_Sustain_wo_reset_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_Sustain_wo_reset(real32_T rtu_input, real32_T
  rtu_sustain_time, real32_T *rty_sustain_value,
  DW_Sustain_wo_reset_AES_ESA_SWC_T *localDW);
extern real32_T AES_ESA_SWC_First_Order_Lag_Filter_LIB2(real32_T
  rtu_unfiltered_input, const ConstB_First_Order_Lag_Filter_LIB2_AES_ESA_SWC_T
  *localC, DW_First_Order_Lag_Filter_LIB2_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_hold_then_fade_n_Init(real32_T *rty_gain,
  DW_hold_then_fade_AES_ESA_SWC_h_T *localDW);
extern void AES_ESA_SWC_hold_then_fade_h(real32_T rtu_hold_dur_msec, real32_T
  rtu_valid_state, boolean_T rtu_enable_gain, real32_T rtu_fading_gain, real32_T
  *rty_gain, DW_hold_then_fade_AES_ESA_SWC_h_T *localDW);
extern void AES_ESA_SWC_First_Order_Lag_Filter_w_IC1_Init
  (DW_First_Order_Lag_Filter_w_IC1_AES_ESA_SWC_T *localDW);
extern real32_T AES_ESA_SWC_First_Order_Lag_Filter_w_IC1(real32_T
  rtu_unfiltered_input, const ConstB_First_Order_Lag_Filter_w_IC1_AES_ESA_SWC_T *
  localC, DW_First_Order_Lag_Filter_w_IC1_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_Delay_set_Init(boolean_T *rty_y,
  DW_Delay_set_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_Delay_set(real32_T rtu_x, real32_T rtu_delay, boolean_T *
  rty_y, DW_Delay_set_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_Delay_set_EP_Init(boolean_T *rty_y,
  DW_Delay_set_EP_AES_ESA_SWC_T *localDW);
extern boolean_T AES_ESA_SWC_Delay_set_EP(boolean_T rtu_x, const
  ConstB_Delay_set_EP_AES_ESA_SWC_T *localC, DW_Delay_set_EP_AES_ESA_SWC_T
  *localDW);
extern void AES_ESA_SWC_Trigger_Hold_Init(boolean_T *rty_Out,
  DW_Trigger_Hold_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_Trigger_Hold(boolean_T rtu_Trigger, real32_T
  rtu_hold_time, boolean_T *rty_Out, DW_Trigger_Hold_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_Chart_c_Init(real32_T *rty_OutPut,
  DW_Chart_AES_ESA_SWC_k_T *localDW);
extern void AES_ESA_SWC_Chart_f(real32_T rtu_Triger, real32_T rtu_Sustain_Time,
  real32_T rtu_Input, real32_T rtu_Input_n_1, real32_T *rty_OutPut,
  DW_Chart_AES_ESA_SWC_k_T *localDW);
extern void AES_ESA_SWC_Chart_g_Init(real32_T *rty_OutPut,
  DW_Chart_AES_ESA_SWC_c_T *localDW);
extern void AES_ESA_SWC_Chart_i(boolean_T rtu_Triger, real32_T rtu_Sustain_Time,
  real32_T rtu_Input, real32_T rtu_Input_n_1, real32_T *rty_OutPut,
  DW_Chart_AES_ESA_SWC_c_T *localDW);
extern real32_T AES_ESA_SWC_IMULonAcc_Filter(real32_T rtu_unfiltered_input,
  real32_T rtu_filter_gain, DW_IMULonAcc_Filter_AES_ESA_SWC_T *localDW);
extern real32_T AES_ESA_SWC_First_Order_Lag_Filter_LIB4(real32_T
  rtu_unfiltered_input, uint16_T rtu_filt_tau_msec, real32_T
  rtu_filt_loop_time_msec, DW_First_Order_Lag_Filter_LIB4_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_ILC_TypeJdge_Init(real32_T *rty_ILC_Type);
extern void AES_ESA_SWC_ILC_TypeJdge(uint8_T rtu_LaneState, real32_T
  rtu_LCK_mode, real32_T rtu_speed_mps, real32_T rtu_k_ILC_rel_LowSpeed,
  real32_T *rty_ILC_Type);
extern real32_T AES_ESA_SWC_Rate_Limiter2(real32_T rtu_Rate_Limited_Input,
  real32_T rtu_Rate_Max, DW_Rate_Limiter2_AES_ESA_SWC_T *localDW);
extern void AES_ESA_SWC_TriggerHold_c_Init(boolean_T *rty_Out, real32_T
  *rty_count);
extern void AES_ESA_SWC_TriggerHold_d(boolean_T rtu_Trigger, real32_T
  rtu_hold_time, boolean_T *rty_Out, real32_T *rty_count);
extern void AES_ESA_SWC_CalcLCCS_quintic_polynomial2(real32_T rtu_pln_startPoint,
  real32_T rtu_pln_startPoint_h, real32_T rtu_pln_startPoint_o, real32_T
  rtu_pln_startPoint_g, real32_T rtu_pln_EndPoint, real32_T rtu_pln_EndPoint_o,
  real32_T rtu_pln_EndPoint_g, real32_T rtu_pln_EndPoint_c, real32_T
  rtu_target_lane_center, real32_T rtu_target_lane_center_h, real32_T
  rtu_target_lane_center_g, real32_T rtu_target_lane_center_n, real32_T
  rtu_target_lane_center_k, real32_T rtu_target_lane_center_hr, real32_T
  rty_quintic_polynomial[6]);
extern void AES_ESA_SWC_MATLABFunction1_Init(DW_MATLABFunction1_AES_ESA_SWC_T
  *localDW);
extern void AES_ESA_SWC_MATLABFunction1(real32_T rtu_PlnStartX, real32_T
  rtu_PlnStartY, real32_T rtu_PlnStartDy, real32_T rtu_PlnStartDDy, real32_T
  rtu_CoordinateTransform, real32_T rtu_CoordinateTransform_n, real32_T
  rtu_CoordinateTransform_nd, real32_T rtu_CoordinateTransform_e, real32_T
  rtu_CoordinateTransform_j, boolean_T rtu_AES_Active, boolean_T
  rtu_AES_Active_Pre, real32_T *rty_new_x, real32_T *rty_new_y, real32_T
  *rty_new_dy, real32_T *rty_new_ddy, DW_MATLABFunction1_AES_ESA_SWC_T *localDW);
extern real32_T AES_ESA_SWC_SfD1(real32_T rtu_Num_In, real32_T rtu_Den_In,
  real32_T rtp_Den_In_Min);
extern real32_T AES_ESA_SWC_SfD1_f(real32_T rtu_Num_In, real32_T rtp_Den_In_Min,
  const ConstB_SfD1_AES_ESA_SWC_g_T *localC);
extern void AES_ESA_SWC_CheckOutsideCircle_LF(real32_T rtu_Obj_Corner_x,
  real32_T rtu_Obj_Corner_y, real32_T rtu_circle_center_x, real32_T
  rtu_circle_center_y, real32_T rtu_Radius_safe, boolean_T *rty_SafeFlg,
  real32_T *rty_dis);
extern void AES_ESA_SWC_CheckOutsideCircle_LR(real32_T rtu_Obj_Corner_x,
  real32_T rtu_Obj_Corner_y, real32_T rtu_circle_center_x, real32_T
  rtu_circle_center_y, real32_T rtu_Radius_safe, boolean_T *rty_SafeFlg);

#endif                                 /* RTW_HEADER_AES_ESA_SWC_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
