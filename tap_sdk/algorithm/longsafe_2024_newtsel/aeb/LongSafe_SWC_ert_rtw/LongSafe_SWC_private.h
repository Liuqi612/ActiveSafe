/*
 * File: LongSafe_SWC_private.h
 *
 * Code generated for Simulink model 'LongSafe_SWC'.
 *
 * Model version                  : 7.3246
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Thu Sep  3 15:58:01 2026
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

#ifndef RTW_HEADER_LongSafe_SWC_private_h_
#define RTW_HEADER_LongSafe_SWC_private_h_
#include "rtwtypes.h"
#include "LongSafe_SWC.h"
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
extern const real32_T rtCP_pooled_PN9J4ZADgHZo[4];
extern const real32_T rtCP_pooled_zcOdeOlOUYLM[60];
extern const real32_T rtCP_pooled_cJTcMumAder1[10];
extern const real32_T rtCP_pooled_i8h9QNvcB151[7];
extern const real32_T rtCP_pooled_2AeIQ2PrK3tN[7];
extern const real32_T rtCP_pooled_mP0gWznDnYub[3];
extern const uint32_T rtCP_pooled_cf46DpFH4W8k[2];
extern const uint32_T rtCP_pooled_nPd1I40s7kOQ[2];
extern const uint32_T rtCP_pooled_UkoYjQXAaa74[2];
extern const uint32_T rtCP_pooled_ybq2kYTVOPDW[2];
extern const uint32_T rtCP_pooled_YLpmxhxRZ0EE[2];
extern const uint32_T rtCP_pooled_QbqRZt5SxXLI[2];
extern const uint32_T rtCP_pooled_nfQ81u46aljE[2];
extern const boolean_T rtCP_pooled_2ukhhMbQGsh4[16];

#define rtCP_PahSegTiStepAryInDrvrStEstimr_Value rtCP_pooled_PN9J4ZADgHZo/* Expression: PahSegTiStepAryInDrvrStEstimr
                                                                      * Referenced by: '<S938>/PahSegTiStepAryInDrvrStEstimr'
                                                                      */
#define rtCP_PahSegTiStepAryInDrvrStEstimr_Value_k rtCP_pooled_PN9J4ZADgHZo/* Expression: PahSegTiStepAryInDrvrStEstimr
                                                                      * Referenced by: '<S875>/PahSegTiStepAryInDrvrStEstimr'
                                                                      */
#define rtCP_PredictionTimeVector1_Value rtCP_pooled_zcOdeOlOUYLM/* Expression: LTAPTimeVector
                                                                  * Referenced by: '<S2281>/PredictionTimeVector1'
                                                                  */
#define rtCP_PredictionTimeVector_Value rtCP_pooled_zcOdeOlOUYLM /* Expression: LTAPTimeVector
                                                                  * Referenced by: '<S2273>/PredictionTimeVector'
                                                                  */
#define rtCP_TimeVectorHighResTTR_Value rtCP_pooled_cJTcMumAder1 /* Expression: LTAPTimeVectorHighResTTR
                                                                  * Referenced by: '<S2260>/TimeVectorHighResTTR'
                                                                  */
#define rtCP_PredictionTimeVector_Value_d rtCP_pooled_zcOdeOlOUYLM/* Expression: LTAPTimeVector
                                                                   * Referenced by: '<S2083>/PredictionTimeVector'
                                                                   */
#define rtCP_LookupTableHighspeed_tableData rtCP_pooled_i8h9QNvcB151/* Expression: K_DrvrDecelReq
                                                                     * Referenced by: '<S6006>/Lookup Table High speed'
                                                                     */
#define rtCP_LookupTableHighspeed_bp01Data rtCP_pooled_2AeIQ2PrK3tN/* Expression: K_CylinderPress
                                                                    * Referenced by: '<S6006>/Lookup Table High speed'
                                                                    */
#define rtCP_uDLookupTable2_bp01Data   rtCP_pooled_mP0gWznDnYub  /* Computed Parameter: rtCP_uDLookupTable2_bp01Data
                                                                  * Referenced by: '<S2190>/1-D Lookup Table2'
                                                                  */
#define rtCP_LookupLongitudinalMarginVeh2_maxIndex rtCP_pooled_cf46DpFH4W8k/* Computed Parameter: rtCP_LookupLongitudinalMarginVeh2_maxIndex
                                                                      * Referenced by: '<S2744>/LookupLongitudinalMarginVeh2'
                                                                      */
#define rtCP_LookupLongitudinalMarginVeh1_maxIndex rtCP_pooled_cf46DpFH4W8k/* Computed Parameter: rtCP_LookupLongitudinalMarginVeh1_maxIndex
                                                                      * Referenced by: '<S2744>/LookupLongitudinalMarginVeh1'
                                                                      */
#define rtCP_LookupLongitudinalMarginVeh2_maxIndex_g rtCP_pooled_cf46DpFH4W8k/* Computed Parameter: rtCP_LookupLongitudinalMarginVeh2_maxIndex_g
                                                                      * Referenced by: '<S2738>/LookupLongitudinalMarginVeh2'
                                                                      */
#define rtCP_LookupLongitudinalMarginVeh1_maxIndex_k rtCP_pooled_cf46DpFH4W8k/* Computed Parameter: rtCP_LookupLongitudinalMarginVeh1_maxIndex_k
                                                                      * Referenced by: '<S2738>/LookupLongitudinalMarginVeh1'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_e rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_e
                                                                      * Referenced by: '<S2731>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupLateralMarginVRU1_maxIndex rtCP_pooled_UkoYjQXAaa74/* Computed Parameter: rtCP_LookupLateralMarginVRU1_maxIndex
                                                                      * Referenced by: '<S2731>/LookupLateralMarginVRU1'
                                                                      */
#define rtCP_LookupLateralMarginVRU2_maxIndex rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU2_maxIndex
                                                                      * Referenced by: '<S2731>/LookupLateralMarginVRU2'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_b rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_b
                                                                      * Referenced by: '<S2731>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex
                                                                      * Referenced by: '<S2731>/LookupVRelPartOfLateralMarginVeh1'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_d rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_d
                                                                      * Referenced by: '<S2730>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupLateralMarginVRU1_maxIndex_e rtCP_pooled_UkoYjQXAaa74/* Computed Parameter: rtCP_LookupLateralMarginVRU1_maxIndex_e
                                                                      * Referenced by: '<S2730>/LookupLateralMarginVRU1'
                                                                      */
#define rtCP_LookupLateralMarginVRU2_maxIndex_l rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU2_maxIndex_l
                                                                      * Referenced by: '<S2730>/LookupLateralMarginVRU2'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_j rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_j
                                                                      * Referenced by: '<S2730>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex_m rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex_m
                                                                      * Referenced by: '<S2730>/LookupVRelPartOfLateralMarginVeh1'
                                                                      */
#define rtCP_InpathOffsetForVehicles_maxIndex rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_InpathOffsetForVehicles_maxIndex
                                                                      * Referenced by: '<S2694>/InpathOffsetForVehicles'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_ds rtCP_pooled_QbqRZt5SxXLI/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_ds
                                                                      * Referenced by: '<S4410>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_c rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_c
                                                                      * Referenced by: '<S4410>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_LookupLongitudinalMarginVeh2_maxIndex_h rtCP_pooled_cf46DpFH4W8k/* Computed Parameter: rtCP_LookupLongitudinalMarginVeh2_maxIndex_h
                                                                      * Referenced by: '<S4429>/LookupLongitudinalMarginVeh2'
                                                                      */
#define rtCP_LookupLongitudinalMarginVeh1_maxIndex_m rtCP_pooled_cf46DpFH4W8k/* Computed Parameter: rtCP_LookupLongitudinalMarginVeh1_maxIndex_m
                                                                      * Referenced by: '<S4429>/LookupLongitudinalMarginVeh1'
                                                                      */
#define rtCP_LookupLongitudinalMarginVeh2_maxIndex_i rtCP_pooled_cf46DpFH4W8k/* Computed Parameter: rtCP_LookupLongitudinalMarginVeh2_maxIndex_i
                                                                      * Referenced by: '<S4423>/LookupLongitudinalMarginVeh2'
                                                                      */
#define rtCP_LookupLongitudinalMarginVeh1_maxIndex_b rtCP_pooled_cf46DpFH4W8k/* Computed Parameter: rtCP_LookupLongitudinalMarginVeh1_maxIndex_b
                                                                      * Referenced by: '<S4423>/LookupLongitudinalMarginVeh1'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_fa rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_fa
                                                                      * Referenced by: '<S4416>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupLateralMarginVRU1_maxIndex_k rtCP_pooled_UkoYjQXAaa74/* Computed Parameter: rtCP_LookupLateralMarginVRU1_maxIndex_k
                                                                      * Referenced by: '<S4416>/LookupLateralMarginVRU1'
                                                                      */
#define rtCP_LookupLateralMarginVRU2_maxIndex_i rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU2_maxIndex_i
                                                                      * Referenced by: '<S4416>/LookupLateralMarginVRU2'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_a rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_a
                                                                      * Referenced by: '<S4416>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex_h rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex_h
                                                                      * Referenced by: '<S4416>/LookupVRelPartOfLateralMarginVeh1'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_a rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_a
                                                                      * Referenced by: '<S4415>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupLateralMarginVRU1_maxIndex_i rtCP_pooled_UkoYjQXAaa74/* Computed Parameter: rtCP_LookupLateralMarginVRU1_maxIndex_i
                                                                      * Referenced by: '<S4415>/LookupLateralMarginVRU1'
                                                                      */
#define rtCP_LookupLateralMarginVRU2_maxIndex_k rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU2_maxIndex_k
                                                                      * Referenced by: '<S4415>/LookupLateralMarginVRU2'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_p rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_p
                                                                      * Referenced by: '<S4415>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex_ml rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex_ml
                                                                      * Referenced by: '<S4415>/LookupVRelPartOfLateralMarginVeh1'
                                                                      */
#define rtCP_InpathOffsetForVehicles_maxIndex_i rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_InpathOffsetForVehicles_maxIndex_i
                                                                      * Referenced by: '<S4379>/InpathOffsetForVehicles'
                                                                      */
#define rtCP_LookupLongitudinalMarginVeh2_maxIndex_p rtCP_pooled_nfQ81u46aljE/* Computed Parameter: rtCP_LookupLongitudinalMarginVeh2_maxIndex_p
                                                                      * Referenced by: '<S2091>/LookupLongitudinalMarginVeh2'
                                                                      */
#define rtCP_Logic_table               rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table
                                                                  * Referenced by: '<S1298>/Logic'
                                                                  */
#define rtCP_Logic_table_b             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_b
                                                                  * Referenced by: '<S1312>/Logic'
                                                                  */
#define rtCP_Logic_table_d             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_d
                                                                  * Referenced by: '<S766>/Logic'
                                                                  */
#define rtCP_Logic_table_dh            rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_dh
                                                                  * Referenced by: '<S591>/Logic'
                                                                  */
#define rtCP_Logic_table_i             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_i
                                                                  * Referenced by: '<S584>/Logic'
                                                                  */
#define rtCP_Logic_table_m             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_m
                                                                  * Referenced by: '<S517>/Logic'
                                                                  */
#define rtCP_Logic_table_n             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_n
                                                                  * Referenced by: '<S518>/Logic'
                                                                  */
#define rtCP_Logic_table_p             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_p
                                                                  * Referenced by: '<S583>/Logic'
                                                                  */

/* Expression: 0
 * Referenced by: '<S1042>/Constant4'
 */
#define rtCP_Constant4_Value           (0.0)

/* Expression: 0
 * Referenced by: '<S1046>/Constant4'
 */
#define rtCP_Constant4_Value_f         (0.0)

/* Expression: 0
 * Referenced by: '<S1071>/Constant4'
 */
#define rtCP_Constant4_Value_h         (0.0)

/* Expression: 0
 * Referenced by: '<S1077>/Constant4'
 */
#define rtCP_Constant4_Value_a         (0.0)

/* Expression: 0
 * Referenced by: '<S1082>/Constant4'
 */
#define rtCP_Constant4_Value_g         (0.0)

/* Expression: 0
 * Referenced by: '<S1234>/Constant4'
 */
#define rtCP_Constant4_Value_fe        (0.0)

/* Expression: 0
 * Referenced by: '<S1250>/Constant4'
 */
#define rtCP_Constant4_Value_i         (0.0)

/* Expression: 0
 * Referenced by: '<S1257>/Constant4'
 */
#define rtCP_Constant4_Value_hf        (0.0)

/* Expression: 0
 * Referenced by: '<S1258>/Constant4'
 */
#define rtCP_Constant4_Value_ar        (0.0)

/* Expression: 0
 * Referenced by: '<S1266>/Constant4'
 */
#define rtCP_Constant4_Value_j         (0.0)

/* Expression: 0
 * Referenced by: '<S1270>/Constant4'
 */
#define rtCP_Constant4_Value_l         (0.0)

/* Expression: 0
 * Referenced by: '<S1275>/Constant4'
 */
#define rtCP_Constant4_Value_o         (0.0)

/* Expression: 0
 * Referenced by: '<S1278>/Constant4'
 */
#define rtCP_Constant4_Value_b         (0.0)

/* Expression: 0
 * Referenced by: '<S1299>/Constant4'
 */
#define rtCP_Constant4_Value_ja        (0.0)

/* Expression: 0
 * Referenced by: '<S1300>/Constant4'
 */
#define rtCP_Constant4_Value_g4        (0.0)

/* Expression: 0
 * Referenced by: '<S1313>/Constant4'
 */
#define rtCP_Constant4_Value_fp        (0.0)

/* Expression: 0
 * Referenced by: '<S1314>/Constant4'
 */
#define rtCP_Constant4_Value_an        (0.0)

/* Expression: 0
 * Referenced by: '<S1324>/Constant4'
 */
#define rtCP_Constant4_Value_d         (0.0)

/* Expression: 0
 * Referenced by: '<S1359>/Constant4'
 */
#define rtCP_Constant4_Value_bl        (0.0)

/* Expression: 0
 * Referenced by: '<S2096>/Constant4'
 */
#define rtCP_Constant4_Value_lu        (0.0)

/* Expression: 0
 * Referenced by: '<S2097>/Constant4'
 */
#define rtCP_Constant4_Value_n         (0.0)

/* Expression: 0
 * Referenced by: '<S2099>/Constant4'
 */
#define rtCP_Constant4_Value_du        (0.0)

/* Expression: 0
 * Referenced by: '<S2100>/Constant4'
 */
#define rtCP_Constant4_Value_p         (0.0)

/* Expression: 0
 * Referenced by: '<S36>/Constant4'
 */
#define rtCP_Constant4_Value_nx        (0.0)

/* Expression: 0
 * Referenced by: '<S37>/Constant4'
 */
#define rtCP_Constant4_Value_c         (0.0)

/* Expression: 0
 * Referenced by: '<S336>/Constant'
 */
#define rtCP_Constant_Value_k          (0.0)

/* Expression: 2
 * Referenced by: '<S336>/Constant1'
 */
#define rtCP_Constant1_Value_p         (2.0)

/* Expression: 0
 * Referenced by: '<S336>/Constant2'
 */
#define rtCP_Constant2_Value_j         (0.0)

/* Expression: 1
 * Referenced by: '<S336>/Constant3'
 */
#define rtCP_Constant3_Value           (1.0)

/* Expression: 0
 * Referenced by: '<S336>/Constant4'
 */
#define rtCP_Constant4_Value_gl        (0.0)

/* Expression: 4
 * Referenced by: '<S336>/Constant5'
 */
#define rtCP_Constant5_Value           (4.0)

/* Expression: 4
 * Referenced by: '<S336>/Constant7'
 */
#define rtCP_Constant7_Value_al        (4.0)

/* Expression: 0
 * Referenced by: '<S494>/Constant4'
 */
#define rtCP_Constant4_Value_dp        (0.0)

/* Expression: 0
 * Referenced by: '<S713>/Constant4'
 */
#define rtCP_Constant4_Value_jt        (0.0)

/* Expression: 0
 * Referenced by: '<S1005>/Constant4'
 */
#define rtCP_Constant4_Value_jj        (0.0)

/* Expression: 0
 * Referenced by: '<S1012>/Constant4'
 */
#define rtCP_Constant4_Value_ft        (0.0)

/* Expression: 0
 * Referenced by: '<S1019>/Constant4'
 */
#define rtCP_Constant4_Value_la        (0.0)

/* Expression: 0.001
 * Referenced by: '<S1023>/Constant1'
 */
#define rtCP_Constant1_Value_b         (0.001)

/* Expression: 0
 * Referenced by: '<S1023>/Constant2'
 */
#define rtCP_Constant2_Value_jp        (0.0)

/* Expression: 0
 * Referenced by: '<S1027>/Constant4'
 */
#define rtCP_Constant4_Value_e         (0.0)

/* Expression: 0.001
 * Referenced by: '<S1031>/Constant1'
 */
#define rtCP_Constant1_Value_bk        (0.001)

/* Expression: 0
 * Referenced by: '<S1031>/Constant2'
 */
#define rtCP_Constant2_Value_jt        (0.0)

/* Expression: 0
 * Referenced by: '<S1063>/Constant4'
 */
#define rtCP_Constant4_Value_ip        (0.0)

/* Expression: 0
 * Referenced by: '<S1065>/Constant4'
 */
#define rtCP_Constant4_Value_ce        (0.0)

/* Expression: 0
 * Referenced by: '<S1067>/Constant4'
 */
#define rtCP_Constant4_Value_d4        (0.0)

/* Expression: 0
 * Referenced by: '<S1069>/Constant4'
 */
#define rtCP_Constant4_Value_nq        (0.0)

/* Expression: 0
 * Referenced by: '<S1074>/Constant4'
 */
#define rtCP_Constant4_Value_jz        (0.0)

/* Expression: 0
 * Referenced by: '<S1085>/Constant4'
 */
#define rtCP_Constant4_Value_m         (0.0)

/* Expression: 0
 * Referenced by: '<S2702>/Constant4'
 */
#define rtCP_Constant4_Value_gj        (0.0)

/* Expression: 0
 * Referenced by: '<S2703>/Constant4'
 */
#define rtCP_Constant4_Value_fpc       (0.0)

/* Expression: 0
 * Referenced by: '<S4387>/Constant4'
 */
#define rtCP_Constant4_Value_ox        (0.0)

/* Expression: 0
 * Referenced by: '<S4388>/Constant4'
 */
#define rtCP_Constant4_Value_cu        (0.0)

/* Expression: 0
 * Referenced by: '<S6112>/Constant4'
 */
#define rtCP_Constant4_Value_pa        (0.0)

/* Expression: 0
 * Referenced by: '<S6131>/Constant4'
 */
#define rtCP_Constant4_Value_iw        (0.0)

/* Expression: 0
 * Referenced by: '<S6132>/Constant4'
 */
#define rtCP_Constant4_Value_ib        (0.0)

/* Expression: 0
 * Referenced by: '<S6135>/Constant4'
 */
#define rtCP_Constant4_Value_gs        (0.0)

/* Expression: 0
 * Referenced by: '<S6144>/Constant4'
 */
#define rtCP_Constant4_Value_jta       (0.0)

/* Expression: 0
 * Referenced by: '<S6145>/Constant4'
 */
#define rtCP_Constant4_Value_an5       (0.0)

/* Expression: 0
 * Referenced by: '<S6202>/Constant4'
 */
#define rtCP_Constant4_Value_i3        (0.0)

/* Expression: 0
 * Referenced by: '<S6203>/Constant4'
 */
#define rtCP_Constant4_Value_a1        (0.0)

/* Expression: 0
 * Referenced by: '<S6204>/Constant4'
 */
#define rtCP_Constant4_Value_hfh       (0.0)

/* Expression: 0
 * Referenced by: '<S6249>/Constant4'
 */
#define rtCP_Constant4_Value_l0        (0.0)

/* Expression: 0
 * Referenced by: '<S6250>/Constant4'
 */
#define rtCP_Constant4_Value_ho        (0.0)

/* Expression: 0
 * Referenced by: '<S6251>/Constant4'
 */
#define rtCP_Constant4_Value_oh        (0.0)

/* Expression: 0
 * Referenced by: '<S6347>/Constant4'
 */
#define rtCP_Constant4_Value_hg        (0.0)

/* Expression: 2
 * Referenced by: '<S6403>/bicycle'
 */
#define rtCP_bicycle_Value             (2.0)

/* Expression: 2
 * Referenced by: '<S6403>/bicycle1'
 */
#define rtCP_bicycle1_Value            (2.0)

/* Expression: 2
 * Referenced by: '<S6403>/bicycle2'
 */
#define rtCP_bicycle2_Value            (2.0)

/* Expression: 3
 * Referenced by: '<S6403>/car'
 */
#define rtCP_car_Value                 (3.0)

/* Expression: 0
 * Referenced by: '<S6403>/notdefined'
 */
#define rtCP_notdefined_Value          (0.0)

/* Expression: 12
 * Referenced by: '<S6403>/other'
 */
#define rtCP_other_Value               (12.0)

/* Expression: 10
 * Referenced by: '<S6403>/other1'
 */
#define rtCP_other1_Value              (10.0)

/* Expression: 1
 * Referenced by: '<S6403>/ped'
 */
#define rtCP_ped_Value                 (1.0)

/* Expression: 4
 * Referenced by: '<S6403>/truck'
 */
#define rtCP_truck_Value               (4.0)

/* Expression: 2
 * Referenced by: '<S6391>/bicycle'
 */
#define rtCP_bicycle_Value_o           (2.0)

/* Expression: 2
 * Referenced by: '<S6391>/motor'
 */
#define rtCP_motor_Value               (2.0)

/* Expression: Sampletime
 * Referenced by: '<S6498>/Constant1'
 */
#define rtCP_Constant1_Value_ba        (0.02)

/* Expression: Sampletime
 * Referenced by: '<S6499>/Constant1'
 */
#define rtCP_Constant1_Value_pu        (0.02)

/* Expression: Sampletime
 * Referenced by: '<S6503>/Constant1'
 */
#define rtCP_Constant1_Value_h         (0.02)

/* Expression: Sampletime
 * Referenced by: '<S6505>/Constant1'
 */
#define rtCP_Constant1_Value_m         (0.02)

/* Computed Parameter: rtCP_Constant56_Value
 * Referenced by: '<S5988>/Constant56'
 */
#define rtCP_Constant56_Value          ((100UL))

/* Computed Parameter: rtCP_Constant56_Value_o
 * Referenced by: '<S5989>/Constant56'
 */
#define rtCP_Constant56_Value_o        ((100UL))

/* Expression: AEBState.AEB_ACTIVE
 * Referenced by: '<S6266>/Constant'
 */
#define rtCP_Constant_Value_kq         (AEB_ACTIVE)

/* Expression: AEBState.AEB_ACTIVE
 * Referenced by: '<S6275>/Constant'
 */
#define rtCP_Constant_Value_kn         (AEB_ACTIVE)

/* Expression: AEBState.AEB_ACTIVE
 * Referenced by: '<S6278>/Constant1'
 */
#define rtCP_Constant1_Value_pp        (AEB_ACTIVE)

/* Expression: AEBState.AEB_ACTIVE
 * Referenced by: '<S6280>/Constant1'
 */
#define rtCP_Constant1_Value_n         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6281>/Constant'
 */
#define rtCP_Constant_Value_d          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6342>/Constant'
 */
#define rtCP_Constant_Value_e          (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6343>/Constant'
 */
#define rtCP_Constant_Value_n          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6366>/Constant'
 */
#define rtCP_Constant_Value_b          (AEB_OFF)

/* Expression: const
 * Referenced by: '<S6367>/Constant'
 */
#define rtCP_Constant_Value_c          (AEB_FAILURE)

/* Expression: const
 * Referenced by: '<S6368>/Constant'
 */
#define rtCP_Constant_Value_d3         (AEB_PASSIVE)

/* Expression: const
 * Referenced by: '<S6369>/Constant'
 */
#define rtCP_Constant_Value_f          (AEB_STANDBY)

/* Expression: const
 * Referenced by: '<S6370>/Constant'
 */
#define rtCP_Constant_Value_m          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6371>/Constant'
 */
#define rtCP_Constant_Value_da         (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6372>/Constant'
 */
#define rtCP_Constant_Value_o          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6373>/Constant'
 */
#define rtCP_Constant_Value_ej         (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6352>/Constant'
 */
#define rtCP_Constant_Value_k0         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6356>/Constant'
 */
#define rtCP_Constant_Value_o2         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6357>/Constant'
 */
#define rtCP_Constant_Value_fc         (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6376>/Constant'
 */
#define rtCP_Constant_Value_p          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6377>/Constant'
 */
#define rtCP_Constant_Value_h          (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6381>/Constant'
 */
#define rtCP_Constant_Value_i          (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6382>/Constant'
 */
#define rtCP_Constant_Value_a          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6383>/Constant'
 */
#define rtCP_Constant_Value_c4         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6399>/Constant'
 */
#define rtCP_Constant_Value_hn         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6401>/Constant'
 */
#define rtCP_Constant_Value_e1         (AEB_FAILURE)

/* Expression: const
 * Referenced by: '<S6402>/Constant'
 */
#define rtCP_Constant_Value_ev         (AEB_OFF)

/* Expression: const
 * Referenced by: '<S6405>/Constant'
 */
#define rtCP_Constant_Value_ov         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6410>/Constant'
 */
#define rtCP_Constant_Value_p4         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6412>/Constant'
 */
#define rtCP_Constant_Value_oz         (AEB_ACTIVE)

/* Expression: AEBState.AEB_STANDBY
 * Referenced by: '<S6306>/Constant1'
 */
#define rtCP_Constant1_Value_nf        (AEB_STANDBY)

/* Expression: const
 * Referenced by: '<S6488>/Constant'
 */
#define rtCP_Constant_Value_dan        (AEB_HOLD)

/* Expression: AWBState.AWB_ACTIVE
 * Referenced by: '<S6273>/Constant'
 */
#define rtCP_Constant_Value_pv         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6282>/Constant'
 */
#define rtCP_Constant_Value_pf         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6354>/Constant'
 */
#define rtCP_Constant_Value_fx         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6374>/Constant'
 */
#define rtCP_Constant_Value_ex         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6379>/Constant'
 */
#define rtCP_Constant_Value_hc         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6407>/Constant'
 */
#define rtCP_Constant_Value_nx         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6414>/Constant'
 */
#define rtCP_Constant_Value_ac         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6417>/Constant'
 */
#define rtCP_Constant_Value_g          (AWB_ACTIVE)

/* Expression: Value
 * Referenced by: '<S545>/Constant'
 */
#define rtCP_Constant_Value_fb         (AccSts1_Actv)

/* Expression: AccSts1.Off
 * Referenced by: '<S5994>/Constant11'
 */
#define rtCP_Constant11_Value          (AccSts1_Off)

/* Expression: AccSts1.Actv
 * Referenced by: '<S5994>/Constant7'
 */
#define rtCP_Constant7_Value_d         (AccSts1_Actv)

/* Expression: Value
 * Referenced by: '<S510>/Constant'
 */
#define rtCP_Constant_Value_p3         (AsyBltLvl1Vcc_ActvnFHi)

/* Expression: Value
 * Referenced by: '<S511>/Constant'
 */
#define rtCP_Constant_Value_eo         (AsyBltLvl1Vcc_ActvnFLo)

/* Expression: Value
 * Referenced by: '<S528>/Constant'
 */
#define rtCP_Constant_Value_d1         (AsyBltLvl1Vcc_NoActvn)

/* Expression: Value
 * Referenced by: '<S30>/Constant'
 */
#define rtCP_Constant_Value_k1         (AsySftyDecelReqDendBySpdRedn0_FALSE)

/* Expression: Value
 * Referenced by: '<S31>/Constant'
 */
#define rtCP_Constant_Value_hcw        (AsySftyDecelReqDendBySpdRedn0_TRUE)

/* Expression: Value
 * Referenced by: '<S555>/Constant'
 */
#define rtCP_Constant_Value_of         (AsySftyDecelReqDendBySpdRedn0_TRUE)

/* Expression: const
 * Referenced by: '<S6486>/Constant'
 */
#define rtCP_Constant_Value_nk         (AsySftyDecelReqDendBySpdRedn0_TRUE)

/* Expression: Value
 * Referenced by: '<S360>/Constant'
 */
#define rtCP_Constant_Value_na         (CllsnFwdWarnCtrlCllsnThreat1Vcc_ThreatLo)

/* Expression: Value
 * Referenced by: '<S361>/Constant'
 */
#define rtCP_Constant_Value_j          (CllsnFwdWarnCtrlCllsnThreat1Vcc_Ukwn)

/* Expression: Value
 * Referenced by: '<S1389>/Constant'
 */
#define rtCP_Constant_Value_kc         (CllsnMtgtnByBrkgPrimQlyVcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S500>/Constant'
 */
#define rtCP_Constant_Value_bo         (CllsnMtgtnByBrkgPrimQlyVcc_BrkgRelbl)

/* Expression: Value
 * Referenced by: '<S578>/Constant'
 */
#define rtCP_Constant_Value_pu         (CllsnMtgtnByBrkgPrimQlyVcc_BrkgRelbl)

/* Expression: Value
 * Referenced by: '<S631>/Constant'
 */
#define rtCP_Constant_Value_bb         (CllsnMtgtnByBrkgPrimQlyVcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S657>/Constant'
 */
#define rtCP_Constant_Value_mj         (CllsnMtgtnByBrkgPrimQlyVcc_BrkgRelbl)

/* Expression: Value
 * Referenced by: '<S705>/Constant'
 */
#define rtCP_Constant_Value_j3         (CllsnMtgtnByBrkgPrimQlyVcc_BrkgRelbl)

/* Expression: Value
 * Referenced by: '<S706>/Constant'
 */
#define rtCP_Constant_Value_bbk        (CllsnMtgtnByBrkgPrimQlyVcc_BrkSpprtRelbl)

/* Expression: Value
 * Referenced by: '<S772>/Constant'
 */
#define rtCP_Constant_Value_b3         (CllsnMtgtnByBrkgPrimQlyVcc_CoastRelbl)

/* Expression: Value
 * Referenced by: '<S773>/Constant'
 */
#define rtCP_Constant_Value_eg         (CllsnMtgtnByBrkgPrimQlyVcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S566>/Constant'
 */
#define rtCP_Constant_Value_i4         (CllsnRednByBrkgPostStsArbn1Vcc_DenByNotEnab)

/* Expression: Value
 * Referenced by: '<S567>/Constant'
 */
#define rtCP_Constant_Value_gc         (CllsnRednByBrkgPostStsArbn1Vcc_DenByOccptSftyPosnNotAvl)

/* Expression: Value
 * Referenced by: '<S572>/Constant'
 */
#define rtCP_Constant_Value_na4        (CllsnRednByBrkgPostStsArbn1Vcc_OvrdByDrvr)

/* Expression: Value
 * Referenced by: '<S568>/Constant'
 */
#define rtCP_Constant_Value_j2         (CllsnRednByBrkgPostStsArbn1Vcc_DenBySpdThd)

/* Expression: Value
 * Referenced by: '<S570>/Constant'
 */
#define rtCP_Constant_Value_br         (CllsnRednByBrkgPostStsArbn1Vcc_FullBrkgActv)

/* Expression: Value
 * Referenced by: '<S574>/Constant'
 */
#define rtCP_Constant_Value_ot         (CllsnRednByBrkgPostStsArbn1Vcc_VisnOnlyVruBrkActv)

/* Expression: Value
 * Referenced by: '<S573>/Constant'
 */
#define rtCP_Constant_Value_ow         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S569>/Constant'
 */
#define rtCP_Constant_Value_pb         (CllsnRednByBrkgPostStsArbn1Vcc_DistBrkgActv)

/* Expression: Value
 * Referenced by: '<S571>/Constant'
 */
#define rtCP_Constant_Value_mt         (CllsnRednByBrkgPostStsArbn1Vcc_NotActv)

/* Expression: Value
 * Referenced by: '<S482>/Constant'
 */
#define rtCP_Constant_Value_ki         (CllsnRednByBrkgPostStsArbn1Vcc_VisnOnlyVruBrkActv)

/* Expression: Value
 * Referenced by: '<S483>/Constant'
 */
#define rtCP_Constant_Value_cq         (CllsnRednByBrkgPostStsArbn1Vcc_DistBrkgActv)

/* Expression: Value
 * Referenced by: '<S484>/Constant'
 */
#define rtCP_Constant_Value_ow3        (CllsnRednByBrkgPostStsArbn1Vcc_DistBrkgActv)

/* Expression: Value
 * Referenced by: '<S501>/Constant'
 */
#define rtCP_Constant_Value_cp         (CllsnRednByBrkgPostStsArbn1Vcc_VisnOnlyVruBrkActv)

/* Expression: Value
 * Referenced by: '<S504>/Constant'
 */
#define rtCP_Constant_Value_ei         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S505>/Constant'
 */
#define rtCP_Constant_Value_l4         (CllsnRednByBrkgPostStsArbn1Vcc_FullBrkgActv)

/* Expression: Value
 * Referenced by: '<S520>/Constant'
 */
#define rtCP_Constant_Value_a3         (CllsnRednByBrkgPostStsArbn1Vcc_FullBrkgActv)

/* Expression: Value
 * Referenced by: '<S521>/Constant'
 */
#define rtCP_Constant_Value_ma         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S523>/Constant'
 */
#define rtCP_Constant_Value_mq         (CllsnRednByBrkgPostStsArbn1Vcc_DistBrkgActv)

/* Expression: Value
 * Referenced by: '<S541>/Constant'
 */
#define rtCP_Constant_Value_ds         (CllsnRednByBrkgPostStsArbn1Vcc_FullBrkgActv)

/* Expression: Value
 * Referenced by: '<S542>/Constant'
 */
#define rtCP_Constant_Value_dd         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S543>/Constant'
 */
#define rtCP_Constant_Value_exo        (CllsnRednByBrkgPostStsArbn1Vcc_VisnOnlyVruBrkActv)

/* Expression: Value
 * Referenced by: '<S544>/Constant'
 */
#define rtCP_Constant_Value_jr         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S579>/Constant'
 */
#define rtCP_Constant_Value_es         (CllsnRednByBrkgPostStsArbn1Vcc_FullBrkgActv)

/* Expression: Value
 * Referenced by: '<S580>/Constant'
 */
#define rtCP_Constant_Value_ey         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S582>/Constant'
 */
#define rtCP_Constant_Value_j4         (CllsnRednByBrkgPostStsArbn1Vcc_DistBrkgActv)

/* Expression: Value
 * Referenced by: '<S585>/Constant'
 */
#define rtCP_Constant_Value_bc         (CllsnRednByBrkgPostStsArbn1Vcc_VisnOnlyVruBrkActv)

/* Expression: Value
 * Referenced by: '<S68>/Constant'
 */
#define rtCP_Constant_Value_hj         (CllsnRednByBrkgWarnReq0_TRUE)

/* Expression: Value
 * Referenced by: '<S783>/Constant'
 */
#define rtCP_Constant_Value_hq         (CllsnRednByBrkgWarnReq0_TRUE)

/* Expression: Value
 * Referenced by: '<S784>/Constant'
 */
#define rtCP_Constant_Value_egr        (CllsnRednByBrkgWarnReq0_FALSE)

/* Expression: Value
 * Referenced by: '<S1412>/Constant'
 */
#define rtCP_Constant_Value_cn         (CllsnWarnFwdQlyVcc_NotRelbl)

/* Expression: const
 * Referenced by: '<S306>/Constant'
 */
#define rtCP_Constant_Value_mjt        (CllsnWarnFwdQlyVcc_Relbl)

/* Expression: Value
 * Referenced by: '<S1001>/Constant'
 */
#define rtCP_Constant_Value_ii         (ClsIn)

/* Expression: Value
 * Referenced by: '<S1002>/Constant'
 */
#define rtCP_Constant_Value_eyk        (ClsIn)

/* Expression: Value
 * Referenced by: '<S1003>/Constant'
 */
#define rtCP_Constant_Value_id         (DrvgFree)

/* Expression: Value
 * Referenced by: '<S1004>/Constant'
 */
#define rtCP_Constant_Value_eil        (Folw)

/* Expression: Value
 * Referenced by: '<S1008>/Constant'
 */
#define rtCP_Constant_Value_p3x        (ClsIn)

/* Expression: Value
 * Referenced by: '<S1009>/Constant'
 */
#define rtCP_Constant_Value_f0         (DrvgFree)

/* Expression: Value
 * Referenced by: '<S1010>/Constant'
 */
#define rtCP_Constant_Value_d0         (DrvgFree)

/* Expression: Value
 * Referenced by: '<S1011>/Constant'
 */
#define rtCP_Constant_Value_d5         (Folw)

/* Expression: Value
 * Referenced by: '<S1015>/Constant'
 */
#define rtCP_Constant_Value_o4         (ClsIn)

/* Expression: Value
 * Referenced by: '<S1016>/Constant'
 */
#define rtCP_Constant_Value_cw         (Folw)

/* Expression: Value
 * Referenced by: '<S1017>/Constant'
 */
#define rtCP_Constant_Value_mqj        (DrvgFree)

/* Expression: Value
 * Referenced by: '<S1018>/Constant'
 */
#define rtCP_Constant_Value_n5         (Folw)

/* Expression: DrvrMod1.DrvgFree
 * Referenced by: '<S990>/Unit Delay'
 */
#define rtCP_UnitDelay_InitialCondition_p (DrvgFree)

/* Expression: const
 * Referenced by: '<S1247>/Constant'
 */
#define rtCP_Constant_Value_hm         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S1273>/Constant'
 */
#define rtCP_Constant_Value_iw         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S1288>/Constant'
 */
#define rtCP_Constant_Value_k2         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S1290>/Constant'
 */
#define rtCP_Constant_Value_hd         (EgoMotionState_SmallRadius)

/* Expression: const
 * Referenced by: '<S1305>/Constant'
 */
#define rtCP_Constant_Value_pp         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S1341>/Constant'
 */
#define rtCP_Constant_Value_dn         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S1342>/Constant'
 */
#define rtCP_Constant_Value_lu         (EgoMotionState_MidRadius)

/* Expression: const
 * Referenced by: '<S1366>/Constant'
 */
#define rtCP_Constant_Value_hp         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S1367>/Constant'
 */
#define rtCP_Constant_Value_pvh        (EgoMotionState_MidRadius)

/* Expression: const
 * Referenced by: '<S2090>/Constant'
 */
#define rtCP_Constant_Value_ovq        (EgoMotionState_SmallRadius)

/* Expression: const
 * Referenced by: '<S2316>/Constant'
 */
#define rtCP_Constant_Value_k2g        (EgoMotionState_SmallRadius)

/* Expression: const
 * Referenced by: '<S625>/Constant'
 */
#define rtCP_Constant_Value_bd         (EgoMotionState_SmallRadius)

/* Expression: const
 * Referenced by: '<S648>/Constant'
 */
#define rtCP_Constant_Value_av         (EgoMotionState_SmallRadius)

/* Expression: const
 * Referenced by: '<S656>/Constant'
 */
#define rtCP_Constant_Value_j0         (EgoMotionState_SmallRadius)

/* Expression: const
 * Referenced by: '<S683>/Constant'
 */
#define rtCP_Constant_Value_pmn        (EgoMotionState_SmallRadius)

/* Expression: const
 * Referenced by: '<S2762>/Constant'
 */
#define rtCP_Constant_Value_gm         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S4447>/Constant'
 */
#define rtCP_Constant_Value_ep         (EgoMotionState_Straight)

/* Expression: FCWState.FCW_STANDBY
 * Referenced by: '<S6276>/Constant'
 */
#define rtCP_Constant_Value_k11        (FCW_STANDBY)

/* Expression: FCWState.FCW_ACTIVE
 * Referenced by: '<S6278>/Constant'
 */
#define rtCP_Constant_Value_aq         (FCW_ACTIVE)

/* Expression: FCWState.FCW_ACTIVE
 * Referenced by: '<S6280>/Constant'
 */
#define rtCP_Constant_Value_nn         (FCW_ACTIVE)

/* Expression: FCWState.FCW_ACTIVE
 * Referenced by: '<S6284>/Constant'
 */
#define rtCP_Constant_Value_ba         (FCW_ACTIVE)

/* Expression: FCWState.FCW_ACTIVE
 * Referenced by: '<S6285>/Constant13'
 */
#define rtCP_Constant13_Value          (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6375>/Constant'
 */
#define rtCP_Constant_Value_o0         (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6380>/Constant'
 */
#define rtCP_Constant_Value_fxg        (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6384>/Constant'
 */
#define rtCP_Constant_Value_esx        (FCW_OFF)

/* Expression: const
 * Referenced by: '<S6385>/Constant'
 */
#define rtCP_Constant_Value_k3         (FCW_FAILURE)

/* Expression: const
 * Referenced by: '<S6386>/Constant'
 */
#define rtCP_Constant_Value_go         (FCW_PASSIVE)

/* Expression: const
 * Referenced by: '<S6387>/Constant'
 */
#define rtCP_Constant_Value_kk         (FCW_STANDBY)

/* Expression: const
 * Referenced by: '<S6388>/Constant'
 */
#define rtCP_Constant_Value_j3z        (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6406>/Constant'
 */
#define rtCP_Constant_Value_gn         (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6408>/Constant'
 */
#define rtCP_Constant_Value_ku         (FCW_OFF)

/* Expression: const
 * Referenced by: '<S6409>/Constant'
 */
#define rtCP_Constant_Value_cg         (FCW_FAILURE)

/* Expression: const
 * Referenced by: '<S6411>/Constant'
 */
#define rtCP_Constant_Value_kd         (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6413>/Constant'
 */
#define rtCP_Constant_Value_ob         (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6416>/Constant'
 */
#define rtCP_Constant_Value_o4w        (FCW_ACTIVE)

/* Expression: FCWState.FCW_ACTIVE
 * Referenced by: '<S6305>/Constant'
 */
#define rtCP_Constant_Value_ou         (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6355>/Constant'
 */
#define rtCP_Constant_Value_hp1        (HBA_ACTIVE)

/* Expression: Value
 * Referenced by: '<S368>/Constant'
 */
#define rtCP_Constant_Value_cgj        (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S369>/Constant'
 */
#define rtCP_Constant_Value_ld         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_UkwnClass)

/* Expression: Value
 * Referenced by: '<S370>/Constant'
 */
#define rtCP_Constant_Value_b0         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Car)

/* Expression: Value
 * Referenced by: '<S371>/Constant'
 */
#define rtCP_Constant_Value_oi         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Motorcycle)

/* Expression: Value
 * Referenced by: '<S372>/Constant'
 */
#define rtCP_Constant_Value_p3g        (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Truck)

/* Expression: Value
 * Referenced by: '<S373>/Constant'
 */
#define rtCP_Constant_Value_lw         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Ped)

/* Expression: Value
 * Referenced by: '<S374>/Constant'
 */
#define rtCP_Constant_Value_fu         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Anim)

/* Expression: Value
 * Referenced by: '<S375>/Constant'
 */
#define rtCP_Constant_Value_fuy        (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_ObjGen)

/* Expression: Value
 * Referenced by: '<S376>/Constant'
 */
#define rtCP_Constant_Value_mjo        (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Bicycle)

/* Expression: Value
 * Referenced by: '<S367>/Constant'
 */
#define rtCP_Constant_Value_ar         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_UkwnClass)

/* Expression: Value
 * Referenced by: '<S180>/Constant'
 */
#define rtCP_Constant_Value_mz         (NoYes1_Yes)

/* Expression: Value
 * Referenced by: '<S590>/Constant'
 */
#define rtCP_Constant_Value_p0         (NoYes1_Yes)

/* Expression: Value
 * Referenced by: '<S728>/Constant'
 */
#define rtCP_Constant_Value_mzx        (NoYes1_Yes)

/* Expression: Value
 * Referenced by: '<S1095>/Constant'
 */
#define rtCP_Constant_Value_gc0        (NoYes1_Yes)

/* Expression: Value
 * Referenced by: '<S793>/Constant'
 */
#define rtCP_Constant_Value_ij         (NoYes1Vcc_Yes)

/* Expression: Value
 * Referenced by: '<S794>/Constant'
 */
#define rtCP_Constant_Value_fi         (NoYes1Vcc_No)

/* Expression: Value
 * Referenced by: '<S1444>/Constant'
 */
#define rtCP_Constant_Value_if         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S1445>/Constant'
 */
#define rtCP_Constant_Value_bxn        (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S1773>/Constant'
 */
#define rtCP_Constant_Value_l0         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S1774>/Constant'
 */
#define rtCP_Constant_Value_lz         (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S2340>/Constant'
 */
#define rtCP_Constant_Value_gf         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S2341>/Constant'
 */
#define rtCP_Constant_Value_g4         (ObjClassn3Vcc_Anim)

/* Expression: const
 * Referenced by: '<S1211>/Constant'
 */
#define rtCP_Constant_Value_kiv        (ObjClassn3Vcc_ObjGen)

/* Expression: const
 * Referenced by: '<S1249>/Constant'
 */
#define rtCP_Constant_Value_nt         (ObjClassn3Vcc_Car)

/* Expression: const
 * Referenced by: '<S1274>/Constant'
 */
#define rtCP_Constant_Value_jp         (ObjClassn3Vcc_ObjGen)

/* Expression: const
 * Referenced by: '<S1287>/Constant'
 */
#define rtCP_Constant_Value_fo         (ObjClassn3Vcc_ObjGen)

/* Expression: const
 * Referenced by: '<S1294>/Constant'
 */
#define rtCP_Constant_Value_hmr        (ObjClassn3Vcc_ObjGen)

/* Expression: const
 * Referenced by: '<S1317>/Constant'
 */
#define rtCP_Constant_Value_py         (ObjClassn3Vcc_Truck)

/* Expression: const
 * Referenced by: '<S1318>/Constant'
 */
#define rtCP_Constant_Value_fe         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: const
 * Referenced by: '<S2149>/Constant'
 */
#define rtCP_Constant_Value_ff         (ObjClassn3Vcc_Car)

/* Expression: Value
 * Referenced by: '<S1392>/Constant'
 */
#define rtCP_Constant_Value_ky         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S1408>/Constant5'
 */
#define rtCP_Constant5_Value_d         (ObjClassn3Vcc_UkwnClass)

/* Expression: const
 * Referenced by: '<S305>/Constant'
 */
#define rtCP_Constant_Value_dm         (ObjClassn3Vcc_ObjGen)

/* Expression: Value
 * Referenced by: '<S522>/Constant'
 */
#define rtCP_Constant_Value_hz         (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S526>/Constant'
 */
#define rtCP_Constant_Value_oq         (ObjClassn3Vcc_Ped)

/* Expression: Value
 * Referenced by: '<S689>/Constant'
 */
#define rtCP_Constant_Value_cd         (ObjClassn3Vcc_Car)

/* Expression: Value
 * Referenced by: '<S690>/Constant'
 */
#define rtCP_Constant_Value_oh         (ObjClassn3Vcc_Truck)

/* Expression: Value
 * Referenced by: '<S693>/Constant'
 */
#define rtCP_Constant_Value_oj         (ObjClassn3Vcc_Ped)

/* Expression: Value
 * Referenced by: '<S694>/Constant'
 */
#define rtCP_Constant_Value_bl         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S695>/Constant'
 */
#define rtCP_Constant_Value_ea         (ObjClassn3Vcc_Motorcycle)

/* Expression: Value
 * Referenced by: '<S696>/Constant'
 */
#define rtCP_Constant_Value_h1         (ObjClassn3Vcc_Ped)

/* Expression: Value
 * Referenced by: '<S697>/Constant'
 */
#define rtCP_Constant_Value_cr         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S698>/Constant'
 */
#define rtCP_Constant_Value_no         (ObjClassn3Vcc_Motorcycle)

/* Expression: Value
 * Referenced by: '<S746>/Constant'
 */
#define rtCP_Constant_Value_ay         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S780>/Constant'
 */
#define rtCP_Constant_Value_j3t        (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S781>/Constant'
 */
#define rtCP_Constant_Value_pft        (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S1087>/Constant'
 */
#define rtCP_Constant_Value_a5         (ObjClassn3Vcc_Car)

/* Expression: Value
 * Referenced by: '<S2655>/Constant'
 */
#define rtCP_Constant_Value_nf         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S2656>/Constant'
 */
#define rtCP_Constant_Value_boa        (ObjClassn3Vcc_Anim)

/* Expression: const
 * Referenced by: '<S2659>/Constant'
 */
#define rtCP_Constant_Value_i0         (ObjClassn3Vcc_Ped)

/* Expression: const
 * Referenced by: '<S2660>/Constant'
 */
#define rtCP_Constant_Value_jg         (ObjClassn3Vcc_ObjGen)

/* Expression: Value
 * Referenced by: '<S2673>/Constant'
 */
#define rtCP_Constant_Value_jt         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S2674>/Constant'
 */
#define rtCP_Constant_Value_a3x        (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S2720>/Constant'
 */
#define rtCP_Constant_Value_i2c        (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S2722>/Constant'
 */
#define rtCP_Constant_Value_hv         (ObjClassn3Vcc_Motorcycle)

/* Expression: const
 * Referenced by: '<S2723>/Constant'
 */
#define rtCP_Constant_Value_dse        (ObjClassn3Vcc_Car)

/* Expression: const
 * Referenced by: '<S2739>/Constant'
 */
#define rtCP_Constant_Value_pq         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S2740>/Constant'
 */
#define rtCP_Constant_Value_lnv        (ObjClassn3Vcc_Car)

/* Expression: const
 * Referenced by: '<S2745>/Constant'
 */
#define rtCP_Constant_Value_g3         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S2746>/Constant'
 */
#define rtCP_Constant_Value_m0         (ObjClassn3Vcc_Car)

/* Expression: Value
 * Referenced by: '<S2791>/Constant'
 */
#define rtCP_Constant_Value_c1         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S2792>/Constant'
 */
#define rtCP_Constant_Value_kv         (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S2800>/Constant'
 */
#define rtCP_Constant_Value_gkt        (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S2801>/Constant'
 */
#define rtCP_Constant_Value_hu         (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S2846>/Constant'
 */
#define rtCP_Constant_Value_dz         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S2847>/Constant'
 */
#define rtCP_Constant_Value_fj         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S3766>/Constant'
 */
#define rtCP_Constant_Value_bk         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S4083>/Constant'
 */
#define rtCP_Constant_Value_pt         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S2633>/Constant1'
 */
#define rtCP_Constant1_Value_d         (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.Bus
 * Referenced by: '<S2633>/Constant10'
 */
#define rtCP_Constant10_Value          (ObjClassn3Vcc_Bus)

/* Expression: ObjClassn3Vcc.Bicycle
 * Referenced by: '<S2633>/Constant11'
 */
#define rtCP_Constant11_Value_i        (ObjClassn3Vcc_Bicycle)

/* Expression: ObjClassn3Vcc.VehOfUkwnClass
 * Referenced by: '<S2633>/Constant12'
 */
#define rtCP_Constant12_Value_j        (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S2633>/Constant13'
 */
#define rtCP_Constant13_Value_b        (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2633>/Constant14'
 */
#define rtCP_Constant14_Value          (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2633>/Constant15'
 */
#define rtCP_Constant15_Value          (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S2633>/Constant16'
 */
#define rtCP_Constant16_Value          (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2633>/Constant17'
 */
#define rtCP_Constant17_Value          (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Cone
 * Referenced by: '<S2633>/Constant19'
 */
#define rtCP_Constant19_Value          (ObjClassn3Vcc_Cone)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2633>/Constant2'
 */
#define rtCP_Constant2_Value_l         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S2633>/Constant20'
 */
#define rtCP_Constant20_Value          (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2633>/Constant21'
 */
#define rtCP_Constant21_Value          (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Car
 * Referenced by: '<S2633>/Constant3'
 */
#define rtCP_Constant3_Value_l         (ObjClassn3Vcc_Car)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S2633>/Constant4'
 */
#define rtCP_Constant4_Value_is        (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.Truck
 * Referenced by: '<S2633>/Constant5'
 */
#define rtCP_Constant5_Value_b         (ObjClassn3Vcc_Truck)

/* Expression: ObjClassn3Vcc.Ped
 * Referenced by: '<S2633>/Constant6'
 */
#define rtCP_Constant6_Value           (ObjClassn3Vcc_Ped)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2633>/Constant7'
 */
#define rtCP_Constant7_Value_n         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2633>/Constant8'
 */
#define rtCP_Constant8_Value           (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Anim
 * Referenced by: '<S2633>/Constant9'
 */
#define rtCP_Constant9_Value           (ObjClassn3Vcc_Anim)

/* Expression: const
 * Referenced by: '<S4344>/Constant'
 */
#define rtCP_Constant_Value_d2         (ObjClassn3Vcc_Ped)

/* Expression: const
 * Referenced by: '<S4345>/Constant'
 */
#define rtCP_Constant_Value_o5         (ObjClassn3Vcc_ObjGen)

/* Expression: Value
 * Referenced by: '<S4358>/Constant'
 */
#define rtCP_Constant_Value_dsj        (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S4359>/Constant'
 */
#define rtCP_Constant_Value_hdv        (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S4413>/Constant'
 */
#define rtCP_Constant_Value_mp         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S4424>/Constant'
 */
#define rtCP_Constant_Value_my         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S4425>/Constant'
 */
#define rtCP_Constant_Value_bdr        (ObjClassn3Vcc_Car)

/* Expression: const
 * Referenced by: '<S4430>/Constant'
 */
#define rtCP_Constant_Value_fl         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S4431>/Constant'
 */
#define rtCP_Constant_Value_h0         (ObjClassn3Vcc_Car)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S4318>/Constant1'
 */
#define rtCP_Constant1_Value_c         (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.Bus
 * Referenced by: '<S4318>/Constant10'
 */
#define rtCP_Constant10_Value_b        (ObjClassn3Vcc_Bus)

/* Expression: ObjClassn3Vcc.Bicycle
 * Referenced by: '<S4318>/Constant11'
 */
#define rtCP_Constant11_Value_k        (ObjClassn3Vcc_Bicycle)

/* Expression: ObjClassn3Vcc.VehOfUkwnClass
 * Referenced by: '<S4318>/Constant12'
 */
#define rtCP_Constant12_Value_n        (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S4318>/Constant13'
 */
#define rtCP_Constant13_Value_a        (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S4318>/Constant14'
 */
#define rtCP_Constant14_Value_b        (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S4318>/Constant15'
 */
#define rtCP_Constant15_Value_i        (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S4318>/Constant16'
 */
#define rtCP_Constant16_Value_j        (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S4318>/Constant17'
 */
#define rtCP_Constant17_Value_m        (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Cone
 * Referenced by: '<S4318>/Constant19'
 */
#define rtCP_Constant19_Value_n        (ObjClassn3Vcc_Cone)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S4318>/Constant2'
 */
#define rtCP_Constant2_Value_n         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S4318>/Constant20'
 */
#define rtCP_Constant20_Value_m        (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S4318>/Constant21'
 */
#define rtCP_Constant21_Value_e        (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Car
 * Referenced by: '<S4318>/Constant3'
 */
#define rtCP_Constant3_Value_n         (ObjClassn3Vcc_Car)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S4318>/Constant4'
 */
#define rtCP_Constant4_Value_a1a       (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.Truck
 * Referenced by: '<S4318>/Constant5'
 */
#define rtCP_Constant5_Value_i         (ObjClassn3Vcc_Truck)

/* Expression: ObjClassn3Vcc.Ped
 * Referenced by: '<S4318>/Constant6'
 */
#define rtCP_Constant6_Value_m         (ObjClassn3Vcc_Ped)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S4318>/Constant7'
 */
#define rtCP_Constant7_Value_o         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S4318>/Constant8'
 */
#define rtCP_Constant8_Value_i         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Anim
 * Referenced by: '<S4318>/Constant9'
 */
#define rtCP_Constant9_Value_f         (ObjClassn3Vcc_Anim)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S6341>/Constant1'
 */
#define rtCP_Constant1_Value_br        (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S6341>/Constant10'
 */
#define rtCP_Constant10_Value_p        (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Bicycle
 * Referenced by: '<S6341>/Constant11'
 */
#define rtCP_Constant11_Value_d        (ObjClassn3Vcc_Bicycle)

/* Expression: ObjClassn3Vcc.VehOfUkwnClass
 * Referenced by: '<S6341>/Constant12'
 */
#define rtCP_Constant12_Value_nt       (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S6341>/Constant13'
 */
#define rtCP_Constant13_Value_j        (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.Bus
 * Referenced by: '<S6341>/Constant14'
 */
#define rtCP_Constant14_Value_p        (ObjClassn3Vcc_Bus)

/* Expression: ObjClassn3Vcc.Cone
 * Referenced by: '<S6341>/Constant15'
 */
#define rtCP_Constant15_Value_c        (ObjClassn3Vcc_Cone)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S6341>/Constant16'
 */
#define rtCP_Constant16_Value_e        (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S6341>/Constant17'
 */
#define rtCP_Constant17_Value_a        (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S6341>/Constant2'
 */
#define rtCP_Constant2_Value_jq        (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Car
 * Referenced by: '<S6341>/Constant3'
 */
#define rtCP_Constant3_Value_d         (ObjClassn3Vcc_Car)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S6341>/Constant4'
 */
#define rtCP_Constant4_Value_n1        (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.Truck
 * Referenced by: '<S6341>/Constant5'
 */
#define rtCP_Constant5_Value_e         (ObjClassn3Vcc_Truck)

/* Expression: ObjClassn3Vcc.Ped
 * Referenced by: '<S6341>/Constant6'
 */
#define rtCP_Constant6_Value_b         (ObjClassn3Vcc_Ped)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S6341>/Constant7'
 */
#define rtCP_Constant7_Value_b         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S6341>/Constant8'
 */
#define rtCP_Constant8_Value_o         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Anim
 * Referenced by: '<S6341>/Constant9'
 */
#define rtCP_Constant9_Value_l         (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S1479>/Constant'
 */
#define rtCP_Constant_Value_d54        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S1683>/Constant'
 */
#define rtCP_Constant_Value_mw         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S1684>/Constant'
 */
#define rtCP_Constant_Value_o2r        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S2012>/Constant'
 */
#define rtCP_Constant_Value_o3         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2013>/Constant'
 */
#define rtCP_Constant_Value_en3        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S2579>/Constant'
 */
#define rtCP_Constant_Value_dj         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2580>/Constant'
 */
#define rtCP_Constant_Value_hl         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: ObjMtnPat1Vcc.MovgToSelf
 * Referenced by: '<S2668>/Constant2'
 */
#define rtCP_Constant2_Value_lv        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: ObjMtnPat1Vcc.Staty
 * Referenced by: '<S2670>/Constant18'
 */
#define rtCP_Constant18_Value          (ObjMtnPat1Vcc_Staty)

/* Expression: ObjMtnPat1Vcc.MovgFromSelf
 * Referenced by: '<S2666>/Constant4'
 */
#define rtCP_Constant4_Value_lun       (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: ObjMtnPat1Vcc.Ukwn
 * Referenced by: '<S2671>/Constant3'
 */
#define rtCP_Constant3_Value_c         (ObjMtnPat1Vcc_Ukwn)

/* Expression: Value
 * Referenced by: '<S2941>/Constant'
 */
#define rtCP_Constant_Value_k3a        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2963>/Constant'
 */
#define rtCP_Constant_Value_nu         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2987>/Constant'
 */
#define rtCP_Constant_Value_c0         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3011>/Constant'
 */
#define rtCP_Constant_Value_il         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3032>/Constant'
 */
#define rtCP_Constant_Value_bt         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3098>/Constant'
 */
#define rtCP_Constant_Value_djl        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3114>/Constant'
 */
#define rtCP_Constant_Value_ce         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3656>/Constant'
 */
#define rtCP_Constant_Value_gg         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3672>/Constant'
 */
#define rtCP_Constant_Value_p0i        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S1255>/Constant'
 */
#define rtCP_Constant_Value_la         (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S1345>/Constant'
 */
#define rtCP_Constant_Value_bn         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S1368>/Constant'
 */
#define rtCP_Constant_Value_ip         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S1390>/Constant'
 */
#define rtCP_Constant_Value_eol        (ObjMtnPat1Vcc_Ukwn)

/* Expression: const
 * Referenced by: '<S688>/Constant'
 */
#define rtCP_Constant_Value_ir         (ObjMtnPat1Vcc_Staty)

/* Expression: Value
 * Referenced by: '<S779>/Constant'
 */
#define rtCP_Constant_Value_hne        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S782>/Constant'
 */
#define rtCP_Constant_Value_cgu        (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S1121>/Constant'
 */
#define rtCP_Constant_Value_l0k        (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S2620>/Constant'
 */
#define rtCP_Constant_Value_lm         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S2621>/Constant'
 */
#define rtCP_Constant_Value_ov0        (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S2622>/Constant'
 */
#define rtCP_Constant_Value_idp        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S2623>/Constant'
 */
#define rtCP_Constant_Value_e2u        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S2658>/Constant'
 */
#define rtCP_Constant_Value_fv         (ObjMtnPat1Vcc_Staty)

/* Expression: Value
 * Referenced by: '<S2672>/Constant'
 */
#define rtCP_Constant_Value_lx         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2675>/Constant'
 */
#define rtCP_Constant_Value_fle        (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S2664>/Constant'
 */
#define rtCP_Constant_Value_for        (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S2665>/Constant'
 */
#define rtCP_Constant_Value_pyj        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3361>/Constant'
 */
#define rtCP_Constant_Value_jd         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3362>/Constant'
 */
#define rtCP_Constant_Value_m1y        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3370>/Constant'
 */
#define rtCP_Constant_Value_e1d        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3371>/Constant'
 */
#define rtCP_Constant_Value_ae         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3379>/Constant'
 */
#define rtCP_Constant_Value_ata        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3380>/Constant'
 */
#define rtCP_Constant_Value_ovn        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3388>/Constant'
 */
#define rtCP_Constant_Value_ny         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3389>/Constant'
 */
#define rtCP_Constant_Value_nxj        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3397>/Constant'
 */
#define rtCP_Constant_Value_n3         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3398>/Constant'
 */
#define rtCP_Constant_Value_gs         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3927>/Constant'
 */
#define rtCP_Constant_Value_ht         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3928>/Constant'
 */
#define rtCP_Constant_Value_ik         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3936>/Constant'
 */
#define rtCP_Constant_Value_pqf        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3937>/Constant'
 */
#define rtCP_Constant_Value_cu         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3945>/Constant'
 */
#define rtCP_Constant_Value_huo        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3946>/Constant'
 */
#define rtCP_Constant_Value_ncy        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3954>/Constant'
 */
#define rtCP_Constant_Value_dp         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3955>/Constant'
 */
#define rtCP_Constant_Value_bo0        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3963>/Constant'
 */
#define rtCP_Constant_Value_c0a        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3964>/Constant'
 */
#define rtCP_Constant_Value_eom        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: const
 * Referenced by: '<S4305>/Constant'
 */
#define rtCP_Constant_Value_pw         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S4306>/Constant'
 */
#define rtCP_Constant_Value_p3o        (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S4307>/Constant'
 */
#define rtCP_Constant_Value_nyr        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S4308>/Constant'
 */
#define rtCP_Constant_Value_hk         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S4343>/Constant'
 */
#define rtCP_Constant_Value_o0n        (ObjMtnPat1Vcc_Staty)

/* Expression: Value
 * Referenced by: '<S4357>/Constant'
 */
#define rtCP_Constant_Value_nou        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S4360>/Constant'
 */
#define rtCP_Constant_Value_kb         (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S4349>/Constant'
 */
#define rtCP_Constant_Value_jf         (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S4350>/Constant'
 */
#define rtCP_Constant_Value_nul        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S5046>/Constant'
 */
#define rtCP_Constant_Value_mmg        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S5047>/Constant'
 */
#define rtCP_Constant_Value_pwy        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S5055>/Constant'
 */
#define rtCP_Constant_Value_bc5        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S5056>/Constant'
 */
#define rtCP_Constant_Value_bw         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S5064>/Constant'
 */
#define rtCP_Constant_Value_jb         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S5065>/Constant'
 */
#define rtCP_Constant_Value_j5         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S5073>/Constant'
 */
#define rtCP_Constant_Value_otu        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S5074>/Constant'
 */
#define rtCP_Constant_Value_kg         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S5082>/Constant'
 */
#define rtCP_Constant_Value_fq         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S5083>/Constant'
 */
#define rtCP_Constant_Value_kl         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S5612>/Constant'
 */
#define rtCP_Constant_Value_bdz        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S5613>/Constant'
 */
#define rtCP_Constant_Value_ipg        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S5621>/Constant'
 */
#define rtCP_Constant_Value_aw         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S5622>/Constant'
 */
#define rtCP_Constant_Value_dy         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S5630>/Constant'
 */
#define rtCP_Constant_Value_lns        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S5631>/Constant'
 */
#define rtCP_Constant_Value_fs         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S532>/Constant'
 */
#define rtCP_Constant_Value_d2n        (OnOff1_Off)

/* Expression: Value
 * Referenced by: '<S536>/Constant'
 */
#define rtCP_Constant_Value_dv         (OnOff1_On)

/* Expression: Value
 * Referenced by: '<S26>/Constant'
 */
#define rtCP_Constant_Value_ovh        (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S377>/Constant'
 */
#define rtCP_Constant_Value_gu         (OnOff1Vcc_Off)

/* Expression: Value
 * Referenced by: '<S378>/Constant'
 */
#define rtCP_Constant_Value_pc         (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S399>/Constant'
 */
#define rtCP_Constant_Value_ggn        (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S400>/Constant'
 */
#define rtCP_Constant_Value_a4         (OnOff1Vcc_Off)

/* Expression: Value
 * Referenced by: '<S358>/Constant'
 */
#define rtCP_Constant_Value_n1u        (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S359>/Constant'
 */
#define rtCP_Constant_Value_oz0        (OnOff1Vcc_Off)

/* Expression: OnOff1Vcc.On
 * Referenced by: '<S464>/Constant'
 */
#define rtCP_Constant_Value_ly         (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S785>/Constant'
 */
#define rtCP_Constant_Value_n0         (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S786>/Constant'
 */
#define rtCP_Constant_Value_gxi        (OnOff1Vcc_Off)

/* Expression: Value
 * Referenced by: '<S787>/Constant'
 */
#define rtCP_Constant_Value_oqt        (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S788>/Constant'
 */
#define rtCP_Constant_Value_f5z        (OnOff1Vcc_Off)

/* Expression: Value
 * Referenced by: '<S789>/Constant'
 */
#define rtCP_Constant_Value_m1i        (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S790>/Constant'
 */
#define rtCP_Constant_Value_ntw        (OnOff1Vcc_Off)

/* Expression: Value
 * Referenced by: '<S6084>/Constant'
 */
#define rtCP_Constant_Value_fou        (OnOff1Vcc_On)

/* Expression: const
 * Referenced by: '<S1356>/Constant'
 */
#define rtCP_Constant_Value_ntx        (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S1340>/Constant'
 */
#define rtCP_Constant_Value_m1r        (PreSceniaroClass_AEBCarPosnInValidHostStright)

/* Expression: const
 * Referenced by: '<S1343>/Constant'
 */
#define rtCP_Constant_Value_cb         (PreSceniaroClass_SceniaroInhibit)

/* Expression: const
 * Referenced by: '<S1361>/Constant'
 */
#define rtCP_Constant_Value_pmw        (PreSceniaroClass_PedPosnLatInValidHostStright)

/* Expression: const
 * Referenced by: '<S1362>/Constant'
 */
#define rtCP_Constant_Value_o4t        (PreSceniaroClass_CarPosnLatInValidHostStright)

/* Expression: const
 * Referenced by: '<S1365>/Constant'
 */
#define rtCP_Constant_Value_ox         (PreSceniaroClass_MotorPosnLatInValidHostStright)

/* Expression: const
 * Referenced by: '<S1369>/Constant'
 */
#define rtCP_Constant_Value_lz4        (PreSceniaroClass_SceniaroInhibit)

/* Expression: const
 * Referenced by: '<S642>/Constant'
 */
#define rtCP_Constant_Value_nd         (PreSceniaroClass_Pre_CCFT)

/* Expression: const
 * Referenced by: '<S643>/Constant'
 */
#define rtCP_Constant_Value_fm         (PreSceniaroClass_Pre_CSTA_LN)

/* Expression: const
 * Referenced by: '<S644>/Constant'
 */
#define rtCP_Constant_Value_o0q        (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S645>/Constant'
 */
#define rtCP_Constant_Value_fc0        (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S646>/Constant'
 */
#define rtCP_Constant_Value_dfr        (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S647>/Constant'
 */
#define rtCP_Constant_Value_px         (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S700>/Constant'
 */
#define rtCP_Constant_Value_jj         (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S703>/Constant'
 */
#define rtCP_Constant_Value_aso        (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S704>/Constant'
 */
#define rtCP_Constant_Value_gt         (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S1125>/Constant'
 */
#define rtCP_Constant_Value_iqp        (PreSceniaroClass_Pre_CCStrightInpath)

/* Expression: const
 * Referenced by: '<S1126>/Constant'
 */
#define rtCP_Constant_Value_dsg        (PreSceniaroClass_Pre_GenObjStrightInpath)

/* Expression: const
 * Referenced by: '<S1127>/Constant'
 */
#define rtCP_Constant_Value_ayt        (PreSceniaroClass_Pre_CBStrightInpath)

/* Expression: const
 * Referenced by: '<S1128>/Constant'
 */
#define rtCP_Constant_Value_fdb        (PreSceniaroClass_Pre_CPStrightInpath)

/* Expression: const
 * Referenced by: '<S2677>/Constant'
 */
#define rtCP_Constant_Value_ig         (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S2678>/Constant'
 */
#define rtCP_Constant_Value_dmu        (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S2679>/Constant'
 */
#define rtCP_Constant_Value_e1a        (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S2680>/Constant'
 */
#define rtCP_Constant_Value_cv         (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S2758>/Constant'
 */
#define rtCP_Constant_Value_h0j        (PreSceniaroClass_Pre_CCStrightInpath)

/* Expression: const
 * Referenced by: '<S4362>/Constant'
 */
#define rtCP_Constant_Value_lmd        (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S4363>/Constant'
 */
#define rtCP_Constant_Value_jg1        (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S4364>/Constant'
 */
#define rtCP_Constant_Value_nys        (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S4365>/Constant'
 */
#define rtCP_Constant_Value_iz         (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S4443>/Constant'
 */
#define rtCP_Constant_Value_g1         (PreSceniaroClass_Pre_CCStrightInpath)

/* Expression: const
 * Referenced by: '<S6168>/Constant'
 */
#define rtCP_Constant_Value_he         (PreSceniaroClass_Pre_CSTA_LN)

/* Expression: const
 * Referenced by: '<S6169>/Constant'
 */
#define rtCP_Constant_Value_ppz        (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S6170>/Constant'
 */
#define rtCP_Constant_Value_eyi        (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S6171>/Constant'
 */
#define rtCP_Constant_Value_cnj        (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S6172>/Constant'
 */
#define rtCP_Constant_Value_nb         (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S6173>/Constant'
 */
#define rtCP_Constant_Value_jfg        (PreSceniaroClass_Pre_CCFT)

/* Expression: const
 * Referenced by: '<S6215>/Constant'
 */
#define rtCP_Constant_Value_l0u        (PreSceniaroClass_Pre_CSTA_LN)

/* Expression: const
 * Referenced by: '<S6216>/Constant'
 */
#define rtCP_Constant_Value_et         (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S6217>/Constant'
 */
#define rtCP_Constant_Value_pvg        (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S6218>/Constant'
 */
#define rtCP_Constant_Value_ok         (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S6219>/Constant'
 */
#define rtCP_Constant_Value_in         (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S6220>/Constant'
 */
#define rtCP_Constant_Value_cwd        (PreSceniaroClass_Pre_CCFT)

/* Expression: const
 * Referenced by: '<S6315>/Constant'
 */
#define rtCP_Constant_Value_c2         (PreSceniaroClass_Pre_CCStrightInpath)

/* Expression: const
 * Referenced by: '<S6316>/Constant'
 */
#define rtCP_Constant_Value_eb0        (PreSceniaroClass_Pre_GenObjStrightInpath)

/* Expression: const
 * Referenced by: '<S6317>/Constant'
 */
#define rtCP_Constant_Value_e5g        (PreSceniaroClass_Pre_CBStrightInpath)

/* Expression: const
 * Referenced by: '<S6318>/Constant'
 */
#define rtCP_Constant_Value_bs         (PreSceniaroClass_Pre_CPStrightInpath)

/* Expression: const
 * Referenced by: '<S6319>/Constant'
 */
#define rtCP_Constant_Value_pcn        (PreSceniaroClass_Pre_CCStrightInpath)

/* Expression: const
 * Referenced by: '<S6320>/Constant'
 */
#define rtCP_Constant_Value_ju         (PreSceniaroClass_Pre_GenObjStrightInpath)

/* Expression: const
 * Referenced by: '<S6321>/Constant'
 */
#define rtCP_Constant_Value_kjr        (PreSceniaroClass_Pre_CBStrightInpath)

/* Expression: const
 * Referenced by: '<S6322>/Constant'
 */
#define rtCP_Constant_Value_ek         (PreSceniaroClass_Pre_CPStrightInpath)

/* Expression: const
 * Referenced by: '<S6329>/Constant'
 */
#define rtCP_Constant_Value_gr         (PreSceniaroClass_Pre_CCFT)

/* Expression: const
 * Referenced by: '<S6330>/Constant'
 */
#define rtCP_Constant_Value_m1s        (PreSceniaroClass_Pre_CSTA_LN)

/* Expression: const
 * Referenced by: '<S6331>/Constant'
 */
#define rtCP_Constant_Value_l2         (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S6332>/Constant'
 */
#define rtCP_Constant_Value_new        (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S6333>/Constant'
 */
#define rtCP_Constant_Value_ez         (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S6334>/Constant'
 */
#define rtCP_Constant_Value_n4         (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S6326>/Constant'
 */
#define rtCP_Constant_Value_o2z        (Prefill_ACTIVE)

/* Expression: const
 * Referenced by: '<S6353>/Constant'
 */
#define rtCP_Constant_Value_me         (Prefill_ACTIVE)

/* Expression: const
 * Referenced by: '<S6415>/Constant'
 */
#define rtCP_Constant_Value_jm         (Prefill_ACTIVE)

/* Expression: Value
 * Referenced by: '<S1413>/Constant'
 */
#define rtCP_Constant_Value_p30        (PrimTarWarn1VccPrimTarInPahNow0_FALSE)

/* Expression: Value
 * Referenced by: '<S1421>/Constant'
 */
#define rtCP_Constant_Value_hjs        (PrimTarWarn1VccPrimTarInPahNow0_TRUE)

/* Expression: Value
 * Referenced by: '<S1422>/Constant'
 */
#define rtCP_Constant_Value_fh         (PrimTarWarn1VccPrimTarInPahNow0_FALSE)

/* Expression: Value
 * Referenced by: '<S67>/Constant'
 */
#define rtCP_Constant_Value_mf         (PrimTarWarn1VccPrimTarInPahNow0_TRUE)

/* Expression: Value
 * Referenced by: '<S2025>/Constant'
 */
#define rtCP_Constant_Value_dx         (Relbl1Vcc_Relbl)

/* Expression: Value
 * Referenced by: '<S2030>/Constant'
 */
#define rtCP_Constant_Value_e55        (Relbl1Vcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S2318>/Constant'
 */
#define rtCP_Constant_Value_a0         (Relbl1Vcc_Relbl)

/* Expression: Value
 * Referenced by: '<S1385>/Constant'
 */
#define rtCP_Constant_Value_ml         (Relbl1Vcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S2326>/Constant'
 */
#define rtCP_Constant_Value_nkj        (Relbl1Vcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S2323>/Constant'
 */
#define rtCP_Constant_Value_a5a        (Relbl1Vcc_Relbl)

/* Expression: Value
 * Referenced by: '<S581>/Constant'
 */
#define rtCP_Constant_Value_dpf        (Relbl1Vcc_Relbl)

/* Expression: Value
 * Referenced by: '<S668>/Constant'
 */
#define rtCP_Constant_Value_ks         (Relbl1Vcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S720>/Constant'
 */
#define rtCP_Constant_Value_ebb        (Relbl1Vcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S529>/Constant'
 */
#define rtCP_Constant_Value_fo1        (ReqSts1Vcc_ThreatHi)

/* Expression: Value
 * Referenced by: '<S530>/Constant'
 */
#define rtCP_Constant_Value_mk         (ReqSts1Vcc_Ukwn)

/* Expression: Value
 * Referenced by: '<S531>/Constant'
 */
#define rtCP_Constant_Value_cj         (ReqSts1Vcc_ThreatMed)

/* Expression: Value
 * Referenced by: '<S6085>/Constant'
 */
#define rtCP_Constant_Value_fp         (ReqSts1Vcc_ThreatMed)

/* Expression: Value
 * Referenced by: '<S6086>/Constant'
 */
#define rtCP_Constant_Value_c3i        (ReqSts1Vcc_ThreatHi)

/* Expression: Value
 * Referenced by: '<S1129>/Constant'
 */
#define rtCP_Constant_Value_guj        (Snvty1_LoSnvty)

/* Expression: Value
 * Referenced by: '<S1130>/Constant'
 */
#define rtCP_Constant_Value_od         (Snvty1_NormSnvty)

/* Expression: Value
 * Referenced by: '<S1131>/Constant'
 */
#define rtCP_Constant_Value_okc        (Snvty1_HiSnvty)

/* Expression: Value
 * Referenced by: '<S533>/Constant'
 */
#define rtCP_Constant_Value_cnf        (TqAllwdPosAndNeg_NoTq)

/* Expression: Value
 * Referenced by: '<S534>/Constant'
 */
#define rtCP_Constant_Value_cdr        (TqAllwdPosAndNeg_Neg)

/* Expression: Value
 * Referenced by: '<S535>/Constant'
 */
#define rtCP_Constant_Value_fy         (TqAllwdPosAndNeg_Pos)

/* Expression: Value
 * Referenced by: '<S449>/Constant'
 */
#define rtCP_Constant_Value_fdh        (VehMtnStSafeGroup0VehMtnSt0_StandStillVal3)

/* Expression: Value
 * Referenced by: '<S450>/Constant'
 */
#define rtCP_Constant_Value_b0z        (VehMtnStSafeGroup0VehMtnSt0_StandStillVal2)

/* Computed Parameter: rtCP_Constant_Value_fcb
 * Referenced by: '<S951>/Constant'
 */
#define rtCP_Constant_Value_fcb        (1)

/* Computed Parameter: rtCP_Constant_Value_gv
 * Referenced by: '<S974>/Constant'
 */
#define rtCP_Constant_Value_gv         (1)

/* Computed Parameter: rtCP_ForIterator_IterationLimit
 * Referenced by: '<S935>/For Iterator'
 */
#define rtCP_ForIterator_IterationLimit (4)

/* Computed Parameter: rtCP_Constant_Value_ly1
 * Referenced by: '<S888>/Constant'
 */
#define rtCP_Constant_Value_ly1        (1)

/* Computed Parameter: rtCP_Constant_Value_jy
 * Referenced by: '<S894>/Constant'
 */
#define rtCP_Constant_Value_jy         (1)

/* Computed Parameter: rtCP_ForIterator_IterationLimit_e
 * Referenced by: '<S872>/For Iterator'
 */
#define rtCP_ForIterator_IterationLimit_e (4)

/* Computed Parameter: rtCP_Constant_Value_nv
 * Referenced by: '<S6194>/Constant'
 */
#define rtCP_Constant_Value_nv         (0)

/* Computed Parameter: rtCP_Constant_Value_jx
 * Referenced by: '<S6195>/Constant'
 */
#define rtCP_Constant_Value_jx         (8)

/* Computed Parameter: rtCP_Constant_Value_c5
 * Referenced by: '<S6196>/Constant'
 */
#define rtCP_Constant_Value_c5         (13)

/* Computed Parameter: rtCP_Constant_Value_df2
 * Referenced by: '<S6198>/Constant'
 */
#define rtCP_Constant_Value_df2        (0)

/* Computed Parameter: rtCP_Constant_Value_n2
 * Referenced by: '<S6199>/Constant'
 */
#define rtCP_Constant_Value_n2         (0)

/* Computed Parameter: rtCP_Constant_Value_dhw
 * Referenced by: '<S6241>/Constant'
 */
#define rtCP_Constant_Value_dhw        (0)

/* Computed Parameter: rtCP_Constant_Value_em
 * Referenced by: '<S6242>/Constant'
 */
#define rtCP_Constant_Value_em         (8)

/* Computed Parameter: rtCP_Constant_Value_brc
 * Referenced by: '<S6243>/Constant'
 */
#define rtCP_Constant_Value_brc        (13)

/* Computed Parameter: rtCP_Constant_Value_avn
 * Referenced by: '<S6245>/Constant'
 */
#define rtCP_Constant_Value_avn        (0)

/* Computed Parameter: rtCP_Constant_Value_hpb
 * Referenced by: '<S6246>/Constant'
 */
#define rtCP_Constant_Value_hpb        (0)

/* Computed Parameter: rtCP_Constant_Value_ck
 * Referenced by: '<S6257>/Constant'
 */
#define rtCP_Constant_Value_ck         (16)

/* Computed Parameter: rtCP_Constant_Value_jz
 * Referenced by: '<S6258>/Constant'
 */
#define rtCP_Constant_Value_jz         (13)

/* Computed Parameter: rtCP_Constant_Value_knx
 * Referenced by: '<S6259>/Constant'
 */
#define rtCP_Constant_Value_knx        (8)

/* Expression: int32(0)
 * Referenced by: '<S6389>/Constant35'
 */
#define rtCP_Constant35_Value          (0)

/* Computed Parameter: rtCP_Constant1_Value_g
 * Referenced by: '<S6400>/Constant1'
 */
#define rtCP_Constant1_Value_g         (1)

/* Computed Parameter: rtCP_Constant2_Value_d
 * Referenced by: '<S6400>/Constant2'
 */
#define rtCP_Constant2_Value_d         (0)

/* Computed Parameter: rtCP_Constant44_Value
 * Referenced by: '<S6400>/Constant44'
 */
#define rtCP_Constant44_Value          (2)

/* Expression: int32(0)
 * Referenced by: '<S6390>/Constant33'
 */
#define rtCP_Constant33_Value          (0)

/* Computed Parameter: rtCP_motor_out_Value
 * Referenced by: '<S6391>/motor_out'
 */
#define rtCP_motor_out_Value           (6)

/* Expression: int32(0)
 * Referenced by: '<S6392>/Constant'
 */
#define rtCP_Constant_Value_jj0        (0)

/* Expression: int32(0)
 * Referenced by: '<S6338>/Constant29'
 */
#define rtCP_Constant29_Value          (0)

/* Expression: int32(0)
 * Referenced by: '<S6338>/Constant34'
 */
#define rtCP_Constant34_Value          (0)

/* Computed Parameter: rtCP_Constant1_Value_nx
 * Referenced by: '<S6393>/Constant1'
 */
#define rtCP_Constant1_Value_nx        (1)

/* Expression: int32(0)
 * Referenced by: '<S6393>/Constant13'
 */
#define rtCP_Constant13_Value_h        (0)

/* Computed Parameter: rtCP_Constant2_Value_p
 * Referenced by: '<S6393>/Constant2'
 */
#define rtCP_Constant2_Value_p         (0)

/* Computed Parameter: rtCP_Constant44_Value_k
 * Referenced by: '<S6393>/Constant44'
 */
#define rtCP_Constant44_Value_k        (2)

/* Expression: int32(6)
 * Referenced by: '<S6394>/Constant1'
 */
#define rtCP_Constant1_Value_go        (6)

/* Expression: int32(0)
 * Referenced by: '<S6394>/Constant13'
 */
#define rtCP_Constant13_Value_f        (0)

/* Expression: int32(1)
 * Referenced by: '<S6394>/Constant2'
 */
#define rtCP_Constant2_Value_dp        (1)

/* Expression: int32(11)
 * Referenced by: '<S6394>/Constant3'
 */
#define rtCP_Constant3_Value_j         (11)

/* Expression: int32(0)
 * Referenced by: '<S6394>/Constant4'
 */
#define rtCP_Constant4_Value_ps        (0)

/* Expression: int32(4)
 * Referenced by: '<S6396>/Constant1'
 */
#define rtCP_Constant1_Value_dp        (4)

/* Expression: int32(0)
 * Referenced by: '<S6396>/Constant13'
 */
#define rtCP_Constant13_Value_l        (0)

/* Expression: int32(0)
 * Referenced by: '<S6396>/Constant38'
 */
#define rtCP_Constant38_Value          (0)

/* Expression: ZeroThreshold
 * Referenced by: '<S615>/QuadraticEquationSolver'
 */
#define rtCP_QuadraticEquationSolver_ZeroThreshold (0.01F)

/* Computed Parameter: rtCP_Constant_Value_juy
 * Referenced by: '<S942>/Constant'
 */
#define rtCP_Constant_Value_juy        (1.0F)

/* Expression: const
 * Referenced by: '<S943>/Constant'
 */
#define rtCP_Constant_Value_jv         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S936>/Constant1'
 */
#define rtCP_Constant1_Value_my        (0.0F)

/* Expression: single(0.1)
 * Referenced by: '<S936>/Constant2'
 */
#define rtCP_Constant2_Value_o         (0.1F)

/* Expression: VehSelfMinSpdInDrvrStEstimr
 * Referenced by: '<S936>/Constant7'
 */
#define rtCP_Constant7_Value_op        (0.2F)

/* Expression: single(0)
 * Referenced by: '<S936>/Constant8'
 */
#define rtCP_Constant8_Value_g         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S946>/Constant'
 */
#define rtCP_Constant_Value_hxt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ars
 * Referenced by: '<S950>/Constant'
 */
#define rtCP_Constant_Value_ars        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_bg
 * Referenced by: '<S938>/Constant1'
 */
#define rtCP_Constant1_Value_bg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dk
 * Referenced by: '<S958>/Constant'
 */
#define rtCP_Constant_Value_dk         (0.0F)

/* Expression: single(3)
 * Referenced by: '<S955>/Constant'
 */
#define rtCP_Constant_Value_o3a        (3.0F)

/* Expression: -single(0.5)
 * Referenced by: '<S955>/Constant1'
 */
#define rtCP_Constant1_Value_ai        (-0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S955>/Constant4'
 */
#define rtCP_Constant4_Value_c5        (0.5F)

/* Expression: single(2)
 * Referenced by: '<S962>/Constant'
 */
#define rtCP_Constant_Value_ak         (2.0F)

/* Expression: single(3)
 * Referenced by: '<S962>/Constant1'
 */
#define rtCP_Constant1_Value_gl        (3.0F)

/* Expression: single(6)
 * Referenced by: '<S962>/Constant2'
 */
#define rtCP_Constant2_Value_je        (6.0F)

/* Expression: single(2)
 * Referenced by: '<S962>/Constant3'
 */
#define rtCP_Constant3_Value_f         (2.0F)

/* Expression: single(0)
 * Referenced by: '<S954>/Constant'
 */
#define rtCP_Constant_Value_ct         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_dz
 * Referenced by: '<S973>/Constant1'
 */
#define rtCP_Constant1_Value_dz        (0.0F)

/* Computed Parameter: rtCP_Constant5_Value_mz
 * Referenced by: '<S973>/Constant5'
 */
#define rtCP_Constant5_Value_mz        (0.0F)

/* Computed Parameter: rtCP_Constant6_Value_l
 * Referenced by: '<S973>/Constant6'
 */
#define rtCP_Constant6_Value_l         (0.0F)

/* Computed Parameter: rtCP_Constant7_Value_a3
 * Referenced by: '<S973>/Constant7'
 */
#define rtCP_Constant7_Value_a3        (0.0F)

/* Computed Parameter: rtCP_Constant9_Value_m
 * Referenced by: '<S973>/Constant9'
 */
#define rtCP_Constant9_Value_m         (0.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_i
 * Referenced by: '<S936>/Saturation'
 */
#define rtCP_Saturation_UpperSat_i     (4.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_o
 * Referenced by: '<S936>/Saturation'
 */
#define rtCP_Saturation_LowerSat_o     (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S936>/Gain1'
 */
#define rtCP_Gain1_Gain                (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S936>/Gain2'
 */
#define rtCP_Gain2_Gain                (0.5F)

/* Expression: single(1/3)
 * Referenced by: '<S953>/Gain9'
 */
#define rtCP_Gain9_Gain                (0.333333343F)

/* Computed Parameter: rtCP_Gain7_Gain
 * Referenced by: '<S953>/Gain7'
 */
#define rtCP_Gain7_Gain                (2.0F)

/* Expression: single(1/6)
 * Referenced by: '<S953>/Gain5'
 */
#define rtCP_Gain5_Gain                (0.166666672F)

/* Computed Parameter: rtCP_Gain9_Gain_p
 * Referenced by: '<S948>/Gain9'
 */
#define rtCP_Gain9_Gain_p              (3.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput
 * Referenced by: '<S957>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput
 * Referenced by: '<S957>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput
 * Referenced by: '<S957>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput
 * Referenced by: '<S957>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput   (0.0F)

/* Expression: single(1/3)
 * Referenced by: '<S953>/Gain8'
 */
#define rtCP_Gain8_Gain                (0.333333343F)

/* Computed Parameter: rtCP_Gain4_Gain
 * Referenced by: '<S953>/Gain4'
 */
#define rtCP_Gain4_Gain                (2.0F)

/* Expression: single(1/6)
 * Referenced by: '<S953>/Gain2'
 */
#define rtCP_Gain2_Gain_l              (0.166666672F)

/* Computed Parameter: rtCP_Gain4_Gain_m
 * Referenced by: '<S948>/Gain4'
 */
#define rtCP_Gain4_Gain_m              (3.0F)

/* Computed Parameter: rtCP_Gain8_Gain_e
 * Referenced by: '<S948>/Gain8'
 */
#define rtCP_Gain8_Gain_e              (3.0F)

/* Computed Parameter: rtCP_Gain_Gain
 * Referenced by: '<S948>/Gain'
 */
#define rtCP_Gain_Gain                 (3.0F)

/* Expression: LoPosValInDrvrStEstimr
 * Referenced by: '<S937>/Saturation'
 */
#define rtCP_Saturation_LowerSat_j     (1.0E-8F)

/* Expression: single(0.1)
 * Referenced by: '<S937>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat      (0.1F)

/* Expression: single(-0.1)
 * Referenced by: '<S937>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat      (-0.1F)

/* Computed Parameter: rtCP_Constant_Value_ow0
 * Referenced by: '<S879>/Constant'
 */
#define rtCP_Constant_Value_ow0        (1.0F)

/* Expression: const
 * Referenced by: '<S880>/Constant'
 */
#define rtCP_Constant_Value_ovr        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S873>/Constant1'
 */
#define rtCP_Constant1_Value_k         (0.0F)

/* Expression: single(0.1)
 * Referenced by: '<S873>/Constant2'
 */
#define rtCP_Constant2_Value_oj        (0.1F)

/* Expression: VehSelfMinSpdInDrvrStEstimr
 * Referenced by: '<S873>/Constant7'
 */
#define rtCP_Constant7_Value_as        (0.2F)

/* Expression: single(0)
 * Referenced by: '<S873>/Constant8'
 */
#define rtCP_Constant8_Value_f         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S883>/Constant'
 */
#define rtCP_Constant_Value_lf         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ft
 * Referenced by: '<S887>/Constant'
 */
#define rtCP_Constant_Value_ft         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_na
 * Referenced by: '<S875>/Constant1'
 */
#define rtCP_Constant1_Value_na        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_o
 * Referenced by: '<S893>/Constant1'
 */
#define rtCP_Constant1_Value_o         (0.0F)

/* Computed Parameter: rtCP_Constant5_Value_l
 * Referenced by: '<S893>/Constant5'
 */
#define rtCP_Constant5_Value_l         (0.0F)

/* Computed Parameter: rtCP_Constant6_Value_m2
 * Referenced by: '<S893>/Constant6'
 */
#define rtCP_Constant6_Value_m2        (0.0F)

/* Computed Parameter: rtCP_Constant7_Value_i
 * Referenced by: '<S893>/Constant7'
 */
#define rtCP_Constant7_Value_i         (0.0F)

/* Computed Parameter: rtCP_Constant9_Value_a
 * Referenced by: '<S893>/Constant9'
 */
#define rtCP_Constant9_Value_a         (0.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_e
 * Referenced by: '<S873>/Saturation'
 */
#define rtCP_Saturation_UpperSat_e     (4.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_h
 * Referenced by: '<S873>/Saturation'
 */
#define rtCP_Saturation_LowerSat_h     (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S873>/Gain1'
 */
#define rtCP_Gain1_Gain_i              (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S873>/Gain2'
 */
#define rtCP_Gain2_Gain_d              (0.5F)

/* Expression: single(1/3)
 * Referenced by: '<S890>/Gain9'
 */
#define rtCP_Gain9_Gain_g              (0.333333343F)

/* Computed Parameter: rtCP_Gain7_Gain_e
 * Referenced by: '<S890>/Gain7'
 */
#define rtCP_Gain7_Gain_e              (2.0F)

/* Expression: single(1/6)
 * Referenced by: '<S890>/Gain5'
 */
#define rtCP_Gain5_Gain_j              (0.166666672F)

/* Computed Parameter: rtCP_Gain9_Gain_gp
 * Referenced by: '<S885>/Gain9'
 */
#define rtCP_Gain9_Gain_gp             (3.0F)

/* Computed Parameter: rtCP_Gain4_Gain_f
 * Referenced by: '<S885>/Gain4'
 */
#define rtCP_Gain4_Gain_f              (3.0F)

/* Expression: single(1/3)
 * Referenced by: '<S890>/Gain8'
 */
#define rtCP_Gain8_Gain_b              (0.333333343F)

/* Computed Parameter: rtCP_Gain4_Gain_k
 * Referenced by: '<S890>/Gain4'
 */
#define rtCP_Gain4_Gain_k              (2.0F)

/* Expression: single(1/6)
 * Referenced by: '<S890>/Gain2'
 */
#define rtCP_Gain2_Gain_m              (0.166666672F)

/* Computed Parameter: rtCP_Gain8_Gain_g
 * Referenced by: '<S885>/Gain8'
 */
#define rtCP_Gain8_Gain_g              (3.0F)

/* Computed Parameter: rtCP_Gain_Gain_k
 * Referenced by: '<S885>/Gain'
 */
#define rtCP_Gain_Gain_k               (3.0F)

/* Expression: LoPosValInDrvrStEstimr
 * Referenced by: '<S874>/Saturation'
 */
#define rtCP_Saturation_LowerSat_n     (1.0E-8F)

/* Expression: single(0.1)
 * Referenced by: '<S874>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_g    (0.1F)

/* Expression: single(-0.1)
 * Referenced by: '<S874>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_c    (-0.1F)

/* Computed Parameter: rtCP_Constant1_Value_l
 * Referenced by: '<S1035>/Constant1'
 */
#define rtCP_Constant1_Value_l         (1.0F)

/* Computed Parameter: rtCP_Constant1_Value_gv
 * Referenced by: '<S1041>/Constant1'
 */
#define rtCP_Constant1_Value_gv        (31.0F)

/* Computed Parameter: rtCP_Constant2_Value_jo
 * Referenced by: '<S1041>/Constant2'
 */
#define rtCP_Constant2_Value_jo        (0.0F)

/* Expression: PerdFctCallInDrvrStEstimr
 * Referenced by: '<S1033>/Constant5'
 */
#define rtCP_Constant5_Value_g         (0.02F)

/* Expression: PerdFctCallInDrvrStEstimr
 * Referenced by: '<S1033>/Constant6'
 */
#define rtCP_Constant6_Value_n         (0.02F)

/* Computed Parameter: rtCP_Constant1_Value_px
 * Referenced by: '<S1080>/Constant1'
 */
#define rtCP_Constant1_Value_px        (31.0F)

/* Computed Parameter: rtCP_Constant2_Value_h
 * Referenced by: '<S1080>/Constant2'
 */
#define rtCP_Constant2_Value_h         (0.0F)

/* Expression: PerdFctCallInDrvrStEstimr
 * Referenced by: '<S1060>/Constant'
 */
#define rtCP_Constant_Value_oko        (0.02F)

/* Computed Parameter: rtCP_Constant2_Value_dt
 * Referenced by: '<S1081>/Constant2'
 */
#define rtCP_Constant2_Value_dt        (1.0F)

/* Computed Parameter: rtCP_Constant4_Value_hj
 * Referenced by: '<S1083>/Constant4'
 */
#define rtCP_Constant4_Value_hj        (1.0F)

/* Expression: AOfGrvyInDrvrStEstimr
 * Referenced by: '<S1198>/g'
 */
#define rtCP_g_Value                   (-9.8F)

/* Expression: AOfGrvyInDrvrStEstimr
 * Referenced by: '<S1199>/g'
 */
#define rtCP_g_Value_f                 (-9.8F)

/* Expression: single(0)
 * Referenced by: '<S1464>/FirstPointInSegment'
 */
#define rtCP_FirstPointInSegment_Value (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1473>/Constant'
 */
#define rtCP_Constant_Value_pvb        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1473>/Constant1'
 */
#define rtCP_Constant1_Value_hq        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1473>/Constant2'
 */
#define rtCP_Constant2_Value_m0        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1473>/Constant3'
 */
#define rtCP_Constant3_Value_i         (0.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S1478>/Constant1'
 */
#define rtCP_Constant1_Value_lc        (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S1478>/Constant2'
 */
#define rtCP_Constant2_Value_g         (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1486>/Constant5'
 */
#define rtCP_Constant5_Value_j         (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_dl
 * Referenced by: '<S1476>/Constant'
 */
#define rtCP_Constant_Value_dl         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pvn
 * Referenced by: '<S1480>/Constant'
 */
#define rtCP_Constant_Value_pvn        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_kh
 * Referenced by: '<S1480>/Constant1'
 */
#define rtCP_Constant1_Value_kh        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1490>/Constant'
 */
#define rtCP_Constant_Value_hb         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_dii
 * Referenced by: '<S1494>/Constant'
 */
#define rtCP_Constant_Value_dii        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value
 * Referenced by: '<S1492>/LimitSource'
 */
#define rtCP_LimitSource_Value         (0.0001F)

/* Computed Parameter: rtCP_Gain_Gain_bo
 * Referenced by: '<S1491>/Gain'
 */
#define rtCP_Gain_Gain_bo              (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_nj
 * Referenced by: '<S1497>/Constant'
 */
#define rtCP_Constant_Value_nj         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_kh4
 * Referenced by: '<S1497>/Constant1'
 */
#define rtCP_Constant1_Value_kh4       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1502>/Constant'
 */
#define rtCP_Constant_Value_akk        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ga
 * Referenced by: '<S1506>/Constant'
 */
#define rtCP_Constant_Value_ga         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_f
 * Referenced by: '<S1504>/LimitSource'
 */
#define rtCP_LimitSource_Value_f       (0.0001F)

/* Expression: single(0.5)
 * Referenced by: '<S1498>/Constant'
 */
#define rtCP_Constant_Value_gkf        (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_h
 * Referenced by: '<S1503>/Gain'
 */
#define rtCP_Gain_Gain_h               (-1.0F)

/* Expression: single(pi)
 * Referenced by: '<S1513>/Saturation'
 */
#define rtCP_Saturation_UpperSat_ir    (3.14159274F)

/* Expression: single(-pi)
 * Referenced by: '<S1513>/Saturation'
 */
#define rtCP_Saturation_LowerSat_he    (-3.14159274F)

/* Expression: single(pi/2)
 * Referenced by: '<S1512>/Constant_1'
 */
#define rtCP_Constant_1_Value          (1.57079637F)

/* Expression: single(pi)
 * Referenced by: '<S1512>/Constant_2'
 */
#define rtCP_Constant_2_Value          (3.14159274F)

/* Computed Parameter: rtCP_Gain_1_Gain_f
 * Referenced by: '<S1512>/Gain_1'
 */
#define rtCP_Gain_1_Gain_f             (-1.0F)

/* Expression: ZeroThreshold
 * Referenced by: '<S1545>/QuadraticEquationSolver'
 */
#define rtCP_QuadraticEquationSolver_ZeroThreshold_l (0.01F)

/* Computed Parameter: rtCP_Constant_Value_mke
 * Referenced by: '<S1546>/Constant'
 */
#define rtCP_Constant_Value_mke        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mr
 * Referenced by: '<S1547>/Constant'
 */
#define rtCP_Constant_Value_mr         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1548>/Constant5'
 */
#define rtCP_Constant5_Value_ih        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_dl5
 * Referenced by: '<S1552>/Constant'
 */
#define rtCP_Constant_Value_dl5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ep5
 * Referenced by: '<S1553>/Constant'
 */
#define rtCP_Constant_Value_ep5        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1554>/Constant5'
 */
#define rtCP_Constant5_Value_lb        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_h4
 * Referenced by: '<S1558>/Constant'
 */
#define rtCP_Constant_Value_h4         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_b1w
 * Referenced by: '<S1561>/Constant'
 */
#define rtCP_Constant_Value_b1w        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_g
 * Referenced by: '<S1543>/Gain'
 */
#define rtCP_Gain_Gain_g               (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_j
 * Referenced by: '<S1544>/Gain'
 */
#define rtCP_Gain_Gain_j               (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_d
 * Referenced by: '<S1545>/Gain'
 */
#define rtCP_Gain_Gain_d               (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ao
 * Referenced by: '<S1565>/Constant'
 */
#define rtCP_Constant_Value_ao         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gf4
 * Referenced by: '<S1566>/Constant'
 */
#define rtCP_Constant_Value_gf4        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1567>/Constant5'
 */
#define rtCP_Constant5_Value_k         (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_bz
 * Referenced by: '<S1571>/Constant'
 */
#define rtCP_Constant_Value_bz         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_e4
 * Referenced by: '<S1572>/Constant'
 */
#define rtCP_Constant_Value_e4         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1573>/Constant5'
 */
#define rtCP_Constant5_Value_kb        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_di5
 * Referenced by: '<S1577>/Constant'
 */
#define rtCP_Constant_Value_di5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kw
 * Referenced by: '<S1580>/Constant'
 */
#define rtCP_Constant_Value_kw         (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_e2
 * Referenced by: '<S1562>/Gain'
 */
#define rtCP_Gain_Gain_e2              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_i
 * Referenced by: '<S1563>/Gain'
 */
#define rtCP_Gain_Gain_i               (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_c
 * Referenced by: '<S1564>/Gain'
 */
#define rtCP_Gain_Gain_c               (0.5F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1668>/Constant5'
 */
#define rtCP_Constant5_Value_p         (1.0E+10F)

/* Computed Parameter: rtCP_Gain3_Gain_h
 * Referenced by: '<S1663>/Gain3'
 */
#define rtCP_Gain3_Gain_h              (-2.0F)

/* Expression: single(1/2)
 * Referenced by: '<S1661>/Constant'
 */
#define rtCP_Constant_Value_n0s        (0.5F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1664>/Constant5'
 */
#define rtCP_Constant5_Value_dn        (1.0E+10F)

/* Computed Parameter: rtCP_Gain_Gain_bz
 * Referenced by: '<S1661>/Gain'
 */
#define rtCP_Gain_Gain_bz              (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_ow3j
 * Referenced by: '<S1650>/Constant'
 */
#define rtCP_Constant_Value_ow3j       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ed
 * Referenced by: '<S1651>/Constant'
 */
#define rtCP_Constant_Value_ed         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1652>/Constant5'
 */
#define rtCP_Constant5_Value_hu        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1657>/Constant5'
 */
#define rtCP_Constant5_Value_ex        (1.0E+10F)

/* Computed Parameter: rtCP_Zero_1_Value
 * Referenced by: '<S1648>/Zero_1'
 */
#define rtCP_Zero_1_Value              (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_e
 * Referenced by: '<S1646>/Gain1'
 */
#define rtCP_Gain1_Gain_e              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_h
 * Referenced by: '<S1648>/Gain1'
 */
#define rtCP_Gain1_Gain_h              (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_g
 * Referenced by: '<S1648>/Gain2'
 */
#define rtCP_Gain2_Gain_g              (2.0F)

/* Expression: single(0)
 * Referenced by: '<S1673>/Zero_1'
 */
#define rtCP_Zero_1_Value_h            (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1675>/Constant5'
 */
#define rtCP_Constant5_Value_de        (1.0E+10F)

/* Computed Parameter: rtCP_Zero_1_Value_k
 * Referenced by: '<S1674>/Zero_1'
 */
#define rtCP_Zero_1_Value_k            (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_d
 * Referenced by: '<S1674>/Gain1'
 */
#define rtCP_Gain1_Gain_d              (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_o
 * Referenced by: '<S1674>/Gain2'
 */
#define rtCP_Gain2_Gain_o              (2.0F)

/* Expression: single(0)
 * Referenced by: '<S1524>/Constant'
 */
#define rtCP_Constant_Value_mzxu       (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_b
 * Referenced by: '<S1532>/LimitSource'
 */
#define rtCP_LimitSource_Value_b       (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ede
 * Referenced by: '<S1533>/Constant'
 */
#define rtCP_Constant_Value_ede        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_myk
 * Referenced by: '<S1534>/Constant'
 */
#define rtCP_Constant_Value_myk        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_g
 * Referenced by: '<S1535>/LimitSource'
 */
#define rtCP_LimitSource_Value_g       (0.01F)

/* Computed Parameter: rtCP_Constant_Value_hdz
 * Referenced by: '<S1536>/Constant'
 */
#define rtCP_Constant_Value_hdz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ksi
 * Referenced by: '<S1537>/Constant'
 */
#define rtCP_Constant_Value_ksi        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_o5v
 * Referenced by: '<S1538>/Constant'
 */
#define rtCP_Constant_Value_o5v        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ojr
 * Referenced by: '<S1539>/Constant'
 */
#define rtCP_Constant_Value_ojr        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_npz
 * Referenced by: '<S1540>/Constant'
 */
#define rtCP_Constant_Value_npz        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1526>/Constant'
 */
#define rtCP_Constant_Value_el         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1526>/Constant1'
 */
#define rtCP_Constant1_Value_j         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_h
 * Referenced by: '<S1621>/LimitSource'
 */
#define rtCP_LimitSource_Value_h       (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_e
 * Referenced by: '<S1622>/LimitSource'
 */
#define rtCP_LimitSource_Value_e       (0.01F)

/* Computed Parameter: rtCP_Constant_Value_dv3
 * Referenced by: '<S1623>/Constant'
 */
#define rtCP_Constant_Value_dv3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_guy
 * Referenced by: '<S1624>/Constant'
 */
#define rtCP_Constant_Value_guy        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_o
 * Referenced by: '<S1625>/LimitSource'
 */
#define rtCP_LimitSource_Value_o       (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_en
 * Referenced by: '<S1626>/LimitSource'
 */
#define rtCP_LimitSource_Value_en      (0.01F)

/* Computed Parameter: rtCP_Zero_Value
 * Referenced by: '<S1632>/Zero'
 */
#define rtCP_Zero_Value                (0.0F)

/* Computed Parameter: rtCP_Constant_Value_eat
 * Referenced by: '<S1633>/Constant'
 */
#define rtCP_Constant_Value_eat        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jw
 * Referenced by: '<S1634>/Constant'
 */
#define rtCP_Constant_Value_jw         (0.0F)

/* Computed Parameter: rtCP_Zero_1_Value_m
 * Referenced by: '<S1627>/Zero_1'
 */
#define rtCP_Zero_1_Value_m            (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1635>/Constant5'
 */
#define rtCP_Constant5_Value_o         (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_dzi
 * Referenced by: '<S1629>/Constant'
 */
#define rtCP_Constant_Value_dzi        (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_hg
 * Referenced by: '<S1644>/Constant'
 */
#define rtCP_Constant_Value_hg         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_bb
 * Referenced by: '<S1645>/LimitSource'
 */
#define rtCP_LimitSource_Value_bb      (0.01F)

/* Expression: single(2)
 * Referenced by: '<S1631>/Constant'
 */
#define rtCP_Constant_Value_hlb        (2.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1679>/Constant'
 */
#define rtCP_Constant_Value_o0y        (0.5F)

/* Expression: single(pi/2)
 * Referenced by: '<S1518>/Constant'
 */
#define rtCP_Constant_Value_iu2        (1.57079637F)

/* Computed Parameter: rtCP_Gain1_Gain_c
 * Referenced by: '<S1526>/Gain1'
 */
#define rtCP_Gain1_Gain_c              (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_a
 * Referenced by: '<S1526>/Gain2'
 */
#define rtCP_Gain2_Gain_a              (-1.0F)

/* Computed Parameter: rtCP_ALgtRqrd_Y0
 * Referenced by: '<S1426>/ALgtRqrd'
 */
#define rtCP_ALgtRqrd_Y0               (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jjg
 * Referenced by: '<S1446>/Constant'
 */
#define rtCP_Constant_Value_jjg        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ki
 * Referenced by: '<S1432>/Constant1'
 */
#define rtCP_Constant1_Value_ki        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pxz
 * Referenced by: '<S1451>/Constant'
 */
#define rtCP_Constant_Value_pxz        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_a
 * Referenced by: '<S1449>/LimitSource'
 */
#define rtCP_LimitSource_Value_a       (0.0001F)

/* Computed Parameter: rtCP_Constant_Value_pbc
 * Referenced by: '<S1685>/Constant'
 */
#define rtCP_Constant_Value_pbc        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mfk
 * Referenced by: '<S1686>/Constant'
 */
#define rtCP_Constant_Value_mfk        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nw
 * Referenced by: '<S1687>/Constant'
 */
#define rtCP_Constant_Value_nw         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i1
 * Referenced by: '<S1688>/Constant'
 */
#define rtCP_Constant_Value_i1         (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_i3
 * Referenced by: '<S1448>/Gain'
 */
#define rtCP_Gain_Gain_i3              (-1.0F)

/* Expression: single(0.001)
 * Referenced by: '<S1457>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_f    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_m
 * Referenced by: '<S1457>/Saturation'
 */
#define rtCP_Saturation_UpperSat_m     (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_h2
 * Referenced by: '<S1457>/Saturation'
 */
#define rtCP_Saturation_LowerSat_h2    (0.0F)

/* Computed Parameter: rtCP_Merge_1_InitialOutput
 * Referenced by: '<S1434>/Merge'
 */
#define rtCP_Merge_1_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_Merge_2_InitialOutput
 * Referenced by: '<S1434>/Merge'
 */
#define rtCP_Merge_2_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_Merge_3_InitialOutput
 * Referenced by: '<S1434>/Merge'
 */
#define rtCP_Merge_3_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_Merge_4_InitialOutput
 * Referenced by: '<S1434>/Merge'
 */
#define rtCP_Merge_4_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_Merge_5_InitialOutput
 * Referenced by: '<S1434>/Merge'
 */
#define rtCP_Merge_5_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_Merge_6_InitialOutput
 * Referenced by: '<S1434>/Merge'
 */
#define rtCP_Merge_6_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_ALatRqrd_Y0
 * Referenced by: '<S1427>/ALatRqrd'
 */
#define rtCP_ALatRqrd_Y0               (0.0F)

/* Computed Parameter: rtCP_PosnLatRelAtTTR_Y0
 * Referenced by: '<S1427>/PosnLatRelAtTTR'
 */
#define rtCP_PosnLatRelAtTTR_Y0        (0.0F)

/* Computed Parameter: rtCP_ProjectedLengthSideLat_Y0
 * Referenced by: '<S1427>/ProjectedLengthSideLat'
 */
#define rtCP_ProjectedLengthSideLat_Y0 (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ap
 * Referenced by: '<S1698>/Constant'
 */
#define rtCP_Constant_Value_ap         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cqy
 * Referenced by: '<S1689>/Constant'
 */
#define rtCP_Constant_Value_cqy        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_nt
 * Referenced by: '<S1689>/Constant1'
 */
#define rtCP_Constant1_Value_nt        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_i
 * Referenced by: '<S1689>/Constant2'
 */
#define rtCP_Constant2_Value_i         (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1690>/Constant'
 */
#define rtCP_Constant_Value_mwm        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_hs
 * Referenced by: '<S1703>/Constant'
 */
#define rtCP_Constant_Value_hs         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_n0h
 * Referenced by: '<S1706>/Constant'
 */
#define rtCP_Constant_Value_n0h        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1694>/Constant'
 */
#define rtCP_Constant_Value_bq2        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_aq5
 * Referenced by: '<S1709>/Constant'
 */
#define rtCP_Constant_Value_aq5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gvy
 * Referenced by: '<S1710>/Constant'
 */
#define rtCP_Constant_Value_gvy        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1695>/Constant2'
 */
#define rtCP_Constant2_Value_em        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1695>/Constant3'
 */
#define rtCP_Constant3_Value_pk        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_h3
 * Referenced by: '<S1691>/Gain'
 */
#define rtCP_Gain_Gain_h3              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_n
 * Referenced by: '<S1692>/Gain'
 */
#define rtCP_Gain_Gain_n               (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_l
 * Referenced by: '<S1695>/Gain1'
 */
#define rtCP_Gain1_Gain_l              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_dg
 * Referenced by: '<S1427>/Gain1'
 */
#define rtCP_Gain1_Gain_dg             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_i
 * Referenced by: '<S1695>/Gain2'
 */
#define rtCP_Gain2_Gain_i              (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_b
 * Referenced by: '<S1696>/Gain2'
 */
#define rtCP_Gain2_Gain_b              (2.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ou
 * Referenced by: '<S1697>/Gain2'
 */
#define rtCP_Gain2_Gain_ou             (2.0F)

/* Computed Parameter: rtCP_Constant_Value_m03
 * Referenced by: '<S1826>/Constant'
 */
#define rtCP_Constant_Value_m03        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_kc
 * Referenced by: '<S1826>/Constant1'
 */
#define rtCP_Constant1_Value_kc        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1831>/Constant'
 */
#define rtCP_Constant_Value_gst        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ef
 * Referenced by: '<S1835>/Constant'
 */
#define rtCP_Constant_Value_ef         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_a4
 * Referenced by: '<S1833>/LimitSource'
 */
#define rtCP_LimitSource_Value_a4      (0.0001F)

/* Expression: single(0.5)
 * Referenced by: '<S1827>/Constant'
 */
#define rtCP_Constant_Value_b1r        (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_l5
 * Referenced by: '<S1832>/Gain'
 */
#define rtCP_Gain_Gain_l5              (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_d2h
 * Referenced by: '<S1875>/Constant'
 */
#define rtCP_Constant_Value_d2h        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fg
 * Referenced by: '<S1876>/Constant'
 */
#define rtCP_Constant_Value_fg         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1877>/Constant5'
 */
#define rtCP_Constant5_Value_ac        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_hjsl
 * Referenced by: '<S1881>/Constant'
 */
#define rtCP_Constant_Value_hjsl       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_poz
 * Referenced by: '<S1882>/Constant'
 */
#define rtCP_Constant_Value_poz        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1883>/Constant5'
 */
#define rtCP_Constant5_Value_lz        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_cm
 * Referenced by: '<S1887>/Constant'
 */
#define rtCP_Constant_Value_cm         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oxo
 * Referenced by: '<S1890>/Constant'
 */
#define rtCP_Constant_Value_oxo        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_eq
 * Referenced by: '<S1872>/Gain'
 */
#define rtCP_Gain_Gain_eq              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_gv
 * Referenced by: '<S1873>/Gain'
 */
#define rtCP_Gain_Gain_gv              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_ha
 * Referenced by: '<S1874>/Gain'
 */
#define rtCP_Gain_Gain_ha              (0.5F)

/* Computed Parameter: rtCP_Constant_Value_duy
 * Referenced by: '<S1894>/Constant'
 */
#define rtCP_Constant_Value_duy        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_js
 * Referenced by: '<S1895>/Constant'
 */
#define rtCP_Constant_Value_js         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1896>/Constant5'
 */
#define rtCP_Constant5_Value_je        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_kf
 * Referenced by: '<S1900>/Constant'
 */
#define rtCP_Constant_Value_kf         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kgu
 * Referenced by: '<S1901>/Constant'
 */
#define rtCP_Constant_Value_kgu        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1902>/Constant5'
 */
#define rtCP_Constant5_Value_al        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_gln
 * Referenced by: '<S1906>/Constant'
 */
#define rtCP_Constant_Value_gln        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kvw
 * Referenced by: '<S1909>/Constant'
 */
#define rtCP_Constant_Value_kvw        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_du
 * Referenced by: '<S1891>/Gain'
 */
#define rtCP_Gain_Gain_du              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_o
 * Referenced by: '<S1892>/Gain'
 */
#define rtCP_Gain_Gain_o               (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_fl
 * Referenced by: '<S1893>/Gain'
 */
#define rtCP_Gain_Gain_fl              (0.5F)

/* Expression: single(0)
 * Referenced by: '<S1853>/Constant'
 */
#define rtCP_Constant_Value_cpw        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ch
 * Referenced by: '<S1861>/LimitSource'
 */
#define rtCP_LimitSource_Value_ch      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_if3
 * Referenced by: '<S1862>/Constant'
 */
#define rtCP_Constant_Value_if3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pk
 * Referenced by: '<S1863>/Constant'
 */
#define rtCP_Constant_Value_pk         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_k
 * Referenced by: '<S1864>/LimitSource'
 */
#define rtCP_LimitSource_Value_k       (0.01F)

/* Computed Parameter: rtCP_Constant_Value_hc4
 * Referenced by: '<S1865>/Constant'
 */
#define rtCP_Constant_Value_hc4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lfu
 * Referenced by: '<S1866>/Constant'
 */
#define rtCP_Constant_Value_lfu        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_b12
 * Referenced by: '<S1867>/Constant'
 */
#define rtCP_Constant_Value_b12        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mo
 * Referenced by: '<S1868>/Constant'
 */
#define rtCP_Constant_Value_mo         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hut
 * Referenced by: '<S1869>/Constant'
 */
#define rtCP_Constant_Value_hut        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1855>/Constant'
 */
#define rtCP_Constant_Value_k0g        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1855>/Constant1'
 */
#define rtCP_Constant1_Value_cw        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ft
 * Referenced by: '<S1950>/LimitSource'
 */
#define rtCP_LimitSource_Value_ft      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_hv
 * Referenced by: '<S1951>/LimitSource'
 */
#define rtCP_LimitSource_Value_hv      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_cy
 * Referenced by: '<S1952>/Constant'
 */
#define rtCP_Constant_Value_cy         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_klb
 * Referenced by: '<S1953>/Constant'
 */
#define rtCP_Constant_Value_klb        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_o0
 * Referenced by: '<S1954>/LimitSource'
 */
#define rtCP_LimitSource_Value_o0      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_fy
 * Referenced by: '<S1955>/LimitSource'
 */
#define rtCP_LimitSource_Value_fy      (0.01F)

/* Computed Parameter: rtCP_Zero_Value_j
 * Referenced by: '<S1961>/Zero'
 */
#define rtCP_Zero_Value_j              (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ike
 * Referenced by: '<S1962>/Constant'
 */
#define rtCP_Constant_Value_ike        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_l2x
 * Referenced by: '<S1963>/Constant'
 */
#define rtCP_Constant_Value_l2x        (0.0F)

/* Computed Parameter: rtCP_Zero_1_Value_i
 * Referenced by: '<S1956>/Zero_1'
 */
#define rtCP_Zero_1_Value_i            (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1964>/Constant5'
 */
#define rtCP_Constant5_Value_gz        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_fjz
 * Referenced by: '<S1958>/Constant'
 */
#define rtCP_Constant_Value_fjz        (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_lo
 * Referenced by: '<S1973>/Constant'
 */
#define rtCP_Constant_Value_lo         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ow
 * Referenced by: '<S1974>/LimitSource'
 */
#define rtCP_LimitSource_Value_ow      (0.01F)

/* Expression: single(2)
 * Referenced by: '<S1960>/Constant'
 */
#define rtCP_Constant_Value_hpv        (2.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2008>/Constant'
 */
#define rtCP_Constant_Value_hqd        (0.5F)

/* Expression: single(pi/2)
 * Referenced by: '<S1847>/Constant'
 */
#define rtCP_Constant_Value_bk4        (1.57079637F)

/* Computed Parameter: rtCP_Gain1_Gain_m
 * Referenced by: '<S1855>/Gain1'
 */
#define rtCP_Gain1_Gain_m              (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_d3
 * Referenced by: '<S1855>/Gain2'
 */
#define rtCP_Gain2_Gain_d3             (-1.0F)

/* Computed Parameter: rtCP_ALgtRqrd_Y0_g
 * Referenced by: '<S1735>/ALgtRqrd'
 */
#define rtCP_ALgtRqrd_Y0_g             (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ja
 * Referenced by: '<S1775>/Constant'
 */
#define rtCP_Constant_Value_ja         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_bl
 * Referenced by: '<S1761>/Constant1'
 */
#define rtCP_Constant1_Value_bl        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lnb
 * Referenced by: '<S1780>/Constant'
 */
#define rtCP_Constant_Value_lnb        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_oq
 * Referenced by: '<S1778>/LimitSource'
 */
#define rtCP_LimitSource_Value_oq      (0.0001F)

/* Computed Parameter: rtCP_Constant_Value_nq
 * Referenced by: '<S2014>/Constant'
 */
#define rtCP_Constant_Value_nq         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bl3
 * Referenced by: '<S2015>/Constant'
 */
#define rtCP_Constant_Value_bl3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_k5
 * Referenced by: '<S2016>/Constant'
 */
#define rtCP_Constant_Value_k5         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lxm
 * Referenced by: '<S2017>/Constant'
 */
#define rtCP_Constant_Value_lxm        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_e2p
 * Referenced by: '<S1777>/Gain'
 */
#define rtCP_Gain_Gain_e2p             (-1.0F)

/* Expression: single(0.001)
 * Referenced by: '<S1786>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_c3   (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_p
 * Referenced by: '<S1786>/Saturation'
 */
#define rtCP_Saturation_UpperSat_p     (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_o5
 * Referenced by: '<S1786>/Saturation'
 */
#define rtCP_Saturation_LowerSat_o5    (0.0F)

/* Computed Parameter: rtCP_Merge_1_InitialOutput_k
 * Referenced by: '<S1763>/Merge'
 */
#define rtCP_Merge_1_InitialOutput_k   (0.0F)

/* Computed Parameter: rtCP_Merge_2_InitialOutput_k
 * Referenced by: '<S1763>/Merge'
 */
#define rtCP_Merge_2_InitialOutput_k   (0.0F)

/* Computed Parameter: rtCP_Merge_3_InitialOutput_k
 * Referenced by: '<S1763>/Merge'
 */
#define rtCP_Merge_3_InitialOutput_k   (0.0F)

/* Computed Parameter: rtCP_Merge_4_InitialOutput_k
 * Referenced by: '<S1763>/Merge'
 */
#define rtCP_Merge_4_InitialOutput_k   (0.0F)

/* Computed Parameter: rtCP_Merge_5_InitialOutput_k
 * Referenced by: '<S1763>/Merge'
 */
#define rtCP_Merge_5_InitialOutput_k   (0.0F)

/* Computed Parameter: rtCP_Merge_6_InitialOutput_k
 * Referenced by: '<S1763>/Merge'
 */
#define rtCP_Merge_6_InitialOutput_k   (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2128>/Constant'
 */
#define rtCP_Constant_Value_ljj        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2128>/Constant1'
 */
#define rtCP_Constant1_Value_jp        (0.0F)

/* Expression: single(0.001)
 * Referenced by: '<S2133>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_n    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_b
 * Referenced by: '<S2133>/Saturation'
 */
#define rtCP_Saturation_UpperSat_b     (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_g
 * Referenced by: '<S2133>/Saturation'
 */
#define rtCP_Saturation_LowerSat_g     (0.0F)

/* Expression: LTAPSampleTime
 * Referenced by: '<S2204>/SampleTime'
 */
#define rtCP_SampleTime_Value          (0.05F)

/* Expression: single(0)
 * Referenced by: '<S2204>/Constant'
 */
#define rtCP_Constant_Value_i5         (0.0F)

/* Expression: LTAPSampleTime
 * Referenced by: '<S2208>/SampleTime'
 */
#define rtCP_SampleTime_Value_n        (0.05F)

/* Expression: single(1)
 * Referenced by: '<S2219>/Constant1'
 */
#define rtCP_Constant1_Value_pd        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S2219>/Constant2'
 */
#define rtCP_Constant2_Value_f         (1.0F)

/* Expression: single(0)
 * Referenced by: '<S2420>/Constant'
 */
#define rtCP_Constant_Value_j22        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ea
 * Referenced by: '<S2428>/LimitSource'
 */
#define rtCP_LimitSource_Value_ea      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ijg
 * Referenced by: '<S2429>/Constant'
 */
#define rtCP_Constant_Value_ijg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_c4f
 * Referenced by: '<S2430>/Constant'
 */
#define rtCP_Constant_Value_c4f        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_fp
 * Referenced by: '<S2431>/LimitSource'
 */
#define rtCP_LimitSource_Value_fp      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_oxm
 * Referenced by: '<S2432>/Constant'
 */
#define rtCP_Constant_Value_oxm        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_af
 * Referenced by: '<S2433>/Constant'
 */
#define rtCP_Constant_Value_af         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_a1
 * Referenced by: '<S2434>/Constant'
 */
#define rtCP_Constant_Value_a1         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dy5
 * Referenced by: '<S2435>/Constant'
 */
#define rtCP_Constant_Value_dy5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_c5i
 * Referenced by: '<S2436>/Constant'
 */
#define rtCP_Constant_Value_c5i        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2422>/Constant'
 */
#define rtCP_Constant_Value_ap0        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2422>/Constant1'
 */
#define rtCP_Constant1_Value_piw       (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_m
 * Referenced by: '<S2517>/LimitSource'
 */
#define rtCP_LimitSource_Value_m       (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_j
 * Referenced by: '<S2518>/LimitSource'
 */
#define rtCP_LimitSource_Value_j       (0.01F)

/* Computed Parameter: rtCP_Constant_Value_d2g
 * Referenced by: '<S2519>/Constant'
 */
#define rtCP_Constant_Value_d2g        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ii5
 * Referenced by: '<S2520>/Constant'
 */
#define rtCP_Constant_Value_ii5        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_js
 * Referenced by: '<S2521>/LimitSource'
 */
#define rtCP_LimitSource_Value_js      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_p
 * Referenced by: '<S2522>/LimitSource'
 */
#define rtCP_LimitSource_Value_p       (0.01F)

/* Computed Parameter: rtCP_Zero_Value_i
 * Referenced by: '<S2528>/Zero'
 */
#define rtCP_Zero_Value_i              (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nxg
 * Referenced by: '<S2529>/Constant'
 */
#define rtCP_Constant_Value_nxg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fz
 * Referenced by: '<S2530>/Constant'
 */
#define rtCP_Constant_Value_fz         (0.0F)

/* Computed Parameter: rtCP_Zero_1_Value_f
 * Referenced by: '<S2523>/Zero_1'
 */
#define rtCP_Zero_1_Value_f            (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2531>/Constant5'
 */
#define rtCP_Constant5_Value_pb        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_aof
 * Referenced by: '<S2525>/Constant'
 */
#define rtCP_Constant_Value_aof        (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_gc3
 * Referenced by: '<S2540>/Constant'
 */
#define rtCP_Constant_Value_gc3        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_fb
 * Referenced by: '<S2541>/LimitSource'
 */
#define rtCP_LimitSource_Value_fb      (0.01F)

/* Expression: single(2)
 * Referenced by: '<S2527>/Constant'
 */
#define rtCP_Constant_Value_iv         (2.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2575>/Constant'
 */
#define rtCP_Constant_Value_kqm        (0.5F)

/* Expression: single(pi/2)
 * Referenced by: '<S2414>/Constant'
 */
#define rtCP_Constant_Value_fjzo       (1.57079637F)

/* Computed Parameter: rtCP_Gain1_Gain_it
 * Referenced by: '<S2422>/Gain1'
 */
#define rtCP_Gain1_Gain_it             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_ee
 * Referenced by: '<S2422>/Gain2'
 */
#define rtCP_Gain2_Gain_ee             (-1.0F)

/* Computed Parameter: rtCP_ALgtRqrd_Y0_f
 * Referenced by: '<S2324>/ALgtRqrd'
 */
#define rtCP_ALgtRqrd_Y0_f             (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ol
 * Referenced by: '<S2342>/Constant'
 */
#define rtCP_Constant_Value_ol         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ll
 * Referenced by: '<S2328>/Constant1'
 */
#define rtCP_Constant1_Value_ll        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cng
 * Referenced by: '<S2347>/Constant'
 */
#define rtCP_Constant_Value_cng        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_gy
 * Referenced by: '<S2345>/LimitSource'
 */
#define rtCP_LimitSource_Value_gy      (0.0001F)

/* Computed Parameter: rtCP_Constant_Value_drn
 * Referenced by: '<S2581>/Constant'
 */
#define rtCP_Constant_Value_drn        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kh
 * Referenced by: '<S2582>/Constant'
 */
#define rtCP_Constant_Value_kh         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pa
 * Referenced by: '<S2583>/Constant'
 */
#define rtCP_Constant_Value_pa         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aww
 * Referenced by: '<S2584>/Constant'
 */
#define rtCP_Constant_Value_aww        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_cr
 * Referenced by: '<S2344>/Gain'
 */
#define rtCP_Gain_Gain_cr              (-1.0F)

/* Expression: single(0.001)
 * Referenced by: '<S2353>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_b    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_h
 * Referenced by: '<S2353>/Saturation'
 */
#define rtCP_Saturation_UpperSat_h     (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_d
 * Referenced by: '<S2353>/Saturation'
 */
#define rtCP_Saturation_LowerSat_d     (0.0F)

/* Computed Parameter: rtCP_Merge_1_InitialOutput_c
 * Referenced by: '<S2330>/Merge'
 */
#define rtCP_Merge_1_InitialOutput_c   (0.0F)

/* Computed Parameter: rtCP_Merge_2_InitialOutput_c
 * Referenced by: '<S2330>/Merge'
 */
#define rtCP_Merge_2_InitialOutput_c   (0.0F)

/* Computed Parameter: rtCP_Merge_3_InitialOutput_c
 * Referenced by: '<S2330>/Merge'
 */
#define rtCP_Merge_3_InitialOutput_c   (0.0F)

/* Computed Parameter: rtCP_Merge_4_InitialOutput_c
 * Referenced by: '<S2330>/Merge'
 */
#define rtCP_Merge_4_InitialOutput_c   (0.0F)

/* Computed Parameter: rtCP_Merge_5_InitialOutput_c
 * Referenced by: '<S2330>/Merge'
 */
#define rtCP_Merge_5_InitialOutput_c   (0.0F)

/* Computed Parameter: rtCP_Merge_6_InitialOutput_c
 * Referenced by: '<S2330>/Merge'
 */
#define rtCP_Merge_6_InitialOutput_c   (0.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S2637>/Constant'
 */
#define rtCP_Constant_Value_ky3        (1.57079637F)

/* Computed Parameter: rtCP_Constant_Value_fh4
 * Referenced by: '<S2640>/Constant'
 */
#define rtCP_Constant_Value_fh4        (0.0F)

/* Expression: single(-1)
 * Referenced by: '<S2637>/Gain'
 */
#define rtCP_Gain_Gain_oo              (-1.0F)

/* Expression: single(pi)
 * Referenced by: '<S2639>/Constant'
 */
#define rtCP_Constant_Value_exi        (3.14159274F)

/* Computed Parameter: rtCP_Constant_Value_guj0
 * Referenced by: '<S2646>/Constant'
 */
#define rtCP_Constant_Value_guj0       (0.0F)

/* Expression: single(pi)
 * Referenced by: '<S2638>/Constant'
 */
#define rtCP_Constant_Value_dt         (3.14159274F)

/* Computed Parameter: rtCP_Constant_Value_gi
 * Referenced by: '<S2643>/Constant'
 */
#define rtCP_Constant_Value_gi         (0.0F)

/* Computed Parameter: rtCP_Zero_1_Value_kb
 * Referenced by: '<S2930>/Zero_1'
 */
#define rtCP_Zero_1_Value_kb           (0.0F)

/* Computed Parameter: rtCP_Zero_2_Value
 * Referenced by: '<S2930>/Zero_2'
 */
#define rtCP_Zero_2_Value              (0.0F)

/* Computed Parameter: rtCP_Zero_3_Value
 * Referenced by: '<S2930>/Zero_3'
 */
#define rtCP_Zero_3_Value              (0.0F)

/* Computed Parameter: rtCP_Zero_5_Value
 * Referenced by: '<S2930>/Zero_5'
 */
#define rtCP_Zero_5_Value              (0.0F)

/* Computed Parameter: rtCP_Zero_6_Value
 * Referenced by: '<S2930>/Zero_6'
 */
#define rtCP_Zero_6_Value              (0.0F)

/* Computed Parameter: rtCP_Zero_4_Value
 * Referenced by: '<S2930>/Zero_4'
 */
#define rtCP_Zero_4_Value              (0.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S2940>/Constant1'
 */
#define rtCP_Constant1_Value_bu        (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S2940>/Constant2'
 */
#define rtCP_Constant2_Value_dg        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2948>/Constant5'
 */
#define rtCP_Constant5_Value_bf        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_d2c
 * Referenced by: '<S2939>/Constant'
 */
#define rtCP_Constant_Value_d2c        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_piz
 * Referenced by: '<S2942>/Constant1'
 */
#define rtCP_Constant1_Value_piz       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2952>/Constant'
 */
#define rtCP_Constant_Value_ouz        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_gq
 * Referenced by: '<S2956>/Constant'
 */
#define rtCP_Constant_Value_gq         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_gq
 * Referenced by: '<S2954>/LimitSource'
 */
#define rtCP_LimitSource_Value_gq      (0.0001F)

/* Expression: single(pi/2)
 * Referenced by: '<S2962>/Constant1'
 */
#define rtCP_Constant1_Value_kw        (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S2962>/Constant2'
 */
#define rtCP_Constant2_Value_fj        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2970>/Constant5'
 */
#define rtCP_Constant5_Value_kk        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_fju
 * Referenced by: '<S2961>/Constant'
 */
#define rtCP_Constant_Value_fju        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_p2
 * Referenced by: '<S2964>/Constant1'
 */
#define rtCP_Constant1_Value_p2        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2974>/Constant'
 */
#define rtCP_Constant_Value_cqn        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_jdv
 * Referenced by: '<S2978>/Constant'
 */
#define rtCP_Constant_Value_jdv        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_n
 * Referenced by: '<S2976>/LimitSource'
 */
#define rtCP_LimitSource_Value_n       (0.0001F)

/* Expression: single(pi/2)
 * Referenced by: '<S2986>/Constant1'
 */
#define rtCP_Constant1_Value_cgr       (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S2986>/Constant2'
 */
#define rtCP_Constant2_Value_eq        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2994>/Constant5'
 */
#define rtCP_Constant5_Value_pqa       (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_ckt
 * Referenced by: '<S2985>/Constant'
 */
#define rtCP_Constant_Value_ckt        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_jc
 * Referenced by: '<S2988>/Constant1'
 */
#define rtCP_Constant1_Value_jc        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2998>/Constant'
 */
#define rtCP_Constant_Value_cy2        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_owj
 * Referenced by: '<S3002>/Constant'
 */
#define rtCP_Constant_Value_owj        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_cy
 * Referenced by: '<S3000>/LimitSource'
 */
#define rtCP_LimitSource_Value_cy      (0.0001F)

/* Expression: single(pi/2)
 * Referenced by: '<S3010>/Constant1'
 */
#define rtCP_Constant1_Value_c2        (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S3010>/Constant2'
 */
#define rtCP_Constant2_Value_l3        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3018>/Constant5'
 */
#define rtCP_Constant5_Value_ggw       (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_cs
 * Referenced by: '<S3009>/Constant'
 */
#define rtCP_Constant_Value_cs         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ij
 * Referenced by: '<S3012>/Constant1'
 */
#define rtCP_Constant1_Value_ij        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3022>/Constant'
 */
#define rtCP_Constant_Value_fr         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_dsu
 * Referenced by: '<S3026>/Constant'
 */
#define rtCP_Constant_Value_dsu        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ov
 * Referenced by: '<S3024>/LimitSource'
 */
#define rtCP_LimitSource_Value_ov      (0.0001F)

/* Expression: single(pi/2)
 * Referenced by: '<S3031>/Constant1'
 */
#define rtCP_Constant1_Value_hl        (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S3031>/Constant2'
 */
#define rtCP_Constant2_Value_du        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3039>/Constant5'
 */
#define rtCP_Constant5_Value_m4        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_bvj
 * Referenced by: '<S3030>/Constant'
 */
#define rtCP_Constant_Value_bvj        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_je
 * Referenced by: '<S3033>/Constant1'
 */
#define rtCP_Constant1_Value_je        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3043>/Constant'
 */
#define rtCP_Constant_Value_jdm        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ayg
 * Referenced by: '<S3047>/Constant'
 */
#define rtCP_Constant_Value_ayg        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_hc
 * Referenced by: '<S3045>/LimitSource'
 */
#define rtCP_LimitSource_Value_hc      (0.0001F)

/* Computed Parameter: rtCP_Gain_Gain_pe
 * Referenced by: '<S2953>/Gain'
 */
#define rtCP_Gain_Gain_pe              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_lx
 * Referenced by: '<S2975>/Gain'
 */
#define rtCP_Gain_Gain_lx              (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_j
 * Referenced by: '<S2981>/Gain_1'
 */
#define rtCP_Gain_1_Gain_j             (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain
 * Referenced by: '<S2981>/Gain_2'
 */
#define rtCP_Gain_2_Gain               (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_l2
 * Referenced by: '<S2999>/Gain'
 */
#define rtCP_Gain_Gain_l2              (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_d
 * Referenced by: '<S3005>/Gain_1'
 */
#define rtCP_Gain_1_Gain_d             (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_a
 * Referenced by: '<S3005>/Gain_2'
 */
#define rtCP_Gain_2_Gain_a             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_jf
 * Referenced by: '<S3023>/Gain'
 */
#define rtCP_Gain_Gain_jf              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_ph
 * Referenced by: '<S3044>/Gain'
 */
#define rtCP_Gain_Gain_ph              (-1.0F)

/* Computed Parameter: rtCP_Constant1_Value_dc
 * Referenced by: '<S3055>/Constant1'
 */
#define rtCP_Constant1_Value_dc        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3062>/Constant'
 */
#define rtCP_Constant_Value_iss        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_p5w
 * Referenced by: '<S3066>/Constant'
 */
#define rtCP_Constant_Value_p5w        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_d
 * Referenced by: '<S3064>/LimitSource'
 */
#define rtCP_LimitSource_Value_d       (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_jcn
 * Referenced by: '<S3056>/Constant1'
 */
#define rtCP_Constant1_Value_jcn       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3069>/Constant'
 */
#define rtCP_Constant_Value_mh         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_mhd
 * Referenced by: '<S3073>/Constant'
 */
#define rtCP_Constant_Value_mhd        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_jh
 * Referenced by: '<S3071>/LimitSource'
 */
#define rtCP_LimitSource_Value_jh      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_l3
 * Referenced by: '<S3076>/Constant1'
 */
#define rtCP_Constant1_Value_l3        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3083>/Constant'
 */
#define rtCP_Constant_Value_exw        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_pnc
 * Referenced by: '<S3087>/Constant'
 */
#define rtCP_Constant_Value_pnc        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_el
 * Referenced by: '<S3085>/LimitSource'
 */
#define rtCP_LimitSource_Value_el      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_pis
 * Referenced by: '<S3077>/Constant1'
 */
#define rtCP_Constant1_Value_pis       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3090>/Constant'
 */
#define rtCP_Constant_Value_a3i        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_pe
 * Referenced by: '<S3094>/Constant'
 */
#define rtCP_Constant_Value_pe         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_mx
 * Referenced by: '<S3092>/LimitSource'
 */
#define rtCP_LimitSource_Value_mx      (0.0001F)

/* Expression: single(0.5)
 * Referenced by: '<S3099>/Constant'
 */
#define rtCP_Constant_Value_h4h        (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S3100>/Constant'
 */
#define rtCP_Constant_Value_jn         (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S3115>/Constant'
 */
#define rtCP_Constant_Value_nl         (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S3116>/Constant'
 */
#define rtCP_Constant_Value_ekk        (0.5F)

/* Computed Parameter: rtCP_Constant1_Value_o1
 * Referenced by: '<S3129>/Constant1'
 */
#define rtCP_Constant1_Value_o1        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3133>/Constant'
 */
#define rtCP_Constant_Value_dle        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ltj
 * Referenced by: '<S3137>/Constant'
 */
#define rtCP_Constant_Value_ltj        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_gp
 * Referenced by: '<S3135>/LimitSource'
 */
#define rtCP_LimitSource_Value_gp      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_pf
 * Referenced by: '<S3130>/Constant1'
 */
#define rtCP_Constant1_Value_pf        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3140>/Constant'
 */
#define rtCP_Constant_Value_m0z        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_iy
 * Referenced by: '<S3144>/Constant'
 */
#define rtCP_Constant_Value_iy         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_i
 * Referenced by: '<S3142>/LimitSource'
 */
#define rtCP_LimitSource_Value_i       (0.0001F)

/* Computed Parameter: rtCP_Gain_Gain_gp
 * Referenced by: '<S3050>/Gain'
 */
#define rtCP_Gain_Gain_gp              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_g1
 * Referenced by: '<S3050>/Gain1'
 */
#define rtCP_Gain1_Gain_g1             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_c5
 * Referenced by: '<S3063>/Gain'
 */
#define rtCP_Gain_Gain_c5              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_n2
 * Referenced by: '<S3070>/Gain'
 */
#define rtCP_Gain_Gain_n2              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_mu
 * Referenced by: '<S3051>/Gain'
 */
#define rtCP_Gain_Gain_mu              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ja
 * Referenced by: '<S3051>/Gain1'
 */
#define rtCP_Gain1_Gain_ja             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_csl
 * Referenced by: '<S3084>/Gain'
 */
#define rtCP_Gain_Gain_csl             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_ay
 * Referenced by: '<S3091>/Gain'
 */
#define rtCP_Gain_Gain_ay              (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_de
 * Referenced by: '<S3097>/Gain_1'
 */
#define rtCP_Gain_1_Gain_de            (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_o
 * Referenced by: '<S3097>/Gain_2'
 */
#define rtCP_Gain_2_Gain_o             (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_k
 * Referenced by: '<S3113>/Gain_1'
 */
#define rtCP_Gain_1_Gain_k             (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_l
 * Referenced by: '<S3113>/Gain_2'
 */
#define rtCP_Gain_2_Gain_l             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_bn
 * Referenced by: '<S3134>/Gain'
 */
#define rtCP_Gain_Gain_bn              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_pg
 * Referenced by: '<S3141>/Gain'
 */
#define rtCP_Gain_Gain_pg              (-1.0F)

/* Computed Parameter: rtCP_Constant1_Value_g0
 * Referenced by: '<S3613>/Constant1'
 */
#define rtCP_Constant1_Value_g0        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3620>/Constant'
 */
#define rtCP_Constant_Value_kd3        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ps
 * Referenced by: '<S3624>/Constant'
 */
#define rtCP_Constant_Value_ps         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ok
 * Referenced by: '<S3622>/LimitSource'
 */
#define rtCP_LimitSource_Value_ok      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_kk
 * Referenced by: '<S3614>/Constant1'
 */
#define rtCP_Constant1_Value_kk        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3627>/Constant'
 */
#define rtCP_Constant_Value_d25        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_lxmb
 * Referenced by: '<S3631>/Constant'
 */
#define rtCP_Constant_Value_lxmb       (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_jj
 * Referenced by: '<S3629>/LimitSource'
 */
#define rtCP_LimitSource_Value_jj      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_et
 * Referenced by: '<S3634>/Constant1'
 */
#define rtCP_Constant1_Value_et        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3641>/Constant'
 */
#define rtCP_Constant_Value_bai        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_lxj
 * Referenced by: '<S3645>/Constant'
 */
#define rtCP_Constant_Value_lxj        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_kz
 * Referenced by: '<S3643>/LimitSource'
 */
#define rtCP_LimitSource_Value_kz      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_jt
 * Referenced by: '<S3635>/Constant1'
 */
#define rtCP_Constant1_Value_jt        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3648>/Constant'
 */
#define rtCP_Constant_Value_er         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_pnj
 * Referenced by: '<S3652>/Constant'
 */
#define rtCP_Constant_Value_pnj        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ftl
 * Referenced by: '<S3650>/LimitSource'
 */
#define rtCP_LimitSource_Value_ftl     (0.0001F)

/* Expression: single(0.5)
 * Referenced by: '<S3657>/Constant'
 */
#define rtCP_Constant_Value_cra        (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S3658>/Constant'
 */
#define rtCP_Constant_Value_af2        (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S3673>/Constant'
 */
#define rtCP_Constant_Value_g0         (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S3674>/Constant'
 */
#define rtCP_Constant_Value_b2         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_h1l
 * Referenced by: '<S3687>/Constant'
 */
#define rtCP_Constant_Value_h1l        (1.0F)

/* Computed Parameter: rtCP_Constant1_Value_knt
 * Referenced by: '<S3688>/Constant1'
 */
#define rtCP_Constant1_Value_knt       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3693>/Constant'
 */
#define rtCP_Constant_Value_gn1        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_crc
 * Referenced by: '<S3697>/Constant'
 */
#define rtCP_Constant_Value_crc        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_mn
 * Referenced by: '<S3695>/LimitSource'
 */
#define rtCP_LimitSource_Value_mn      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_pgp
 * Referenced by: '<S3689>/Constant1'
 */
#define rtCP_Constant1_Value_pgp       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3700>/Constant'
 */
#define rtCP_Constant_Value_dvm        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_pr
 * Referenced by: '<S3704>/Constant'
 */
#define rtCP_Constant_Value_pr         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_h5
 * Referenced by: '<S3702>/LimitSource'
 */
#define rtCP_LimitSource_Value_h5      (0.0001F)

/* Computed Parameter: rtCP_Gain_Gain_dj
 * Referenced by: '<S3608>/Gain'
 */
#define rtCP_Gain_Gain_dj              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ch
 * Referenced by: '<S3608>/Gain1'
 */
#define rtCP_Gain1_Gain_ch             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_p5
 * Referenced by: '<S3621>/Gain'
 */
#define rtCP_Gain_Gain_p5              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_fd
 * Referenced by: '<S3628>/Gain'
 */
#define rtCP_Gain_Gain_fd              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_es
 * Referenced by: '<S3609>/Gain'
 */
#define rtCP_Gain_Gain_es              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_f5
 * Referenced by: '<S3609>/Gain1'
 */
#define rtCP_Gain1_Gain_f5             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_mo
 * Referenced by: '<S3642>/Gain'
 */
#define rtCP_Gain_Gain_mo              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_pv
 * Referenced by: '<S3649>/Gain'
 */
#define rtCP_Gain_Gain_pv              (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_pz
 * Referenced by: '<S3655>/Gain_1'
 */
#define rtCP_Gain_1_Gain_pz            (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_j
 * Referenced by: '<S3655>/Gain_2'
 */
#define rtCP_Gain_2_Gain_j             (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_h
 * Referenced by: '<S3671>/Gain_1'
 */
#define rtCP_Gain_1_Gain_h             (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_i
 * Referenced by: '<S3671>/Gain_2'
 */
#define rtCP_Gain_2_Gain_i             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_hp
 * Referenced by: '<S3694>/Gain'
 */
#define rtCP_Gain_Gain_hp              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_iz
 * Referenced by: '<S3701>/Gain'
 */
#define rtCP_Gain_Gain_iz              (-1.0F)

/* Expression: single(pi)
 * Referenced by: '<S3929>/Constant_1'
 */
#define rtCP_Constant_1_Value_b        (3.14159274F)

/* Expression: single(pi)
 * Referenced by: '<S3929>/Constant_2'
 */
#define rtCP_Constant_2_Value_ou       (3.14159274F)

/* Computed Parameter: rtCP_Gain_1_Gain_fm
 * Referenced by: '<S3929>/Gain_1'
 */
#define rtCP_Gain_1_Gain_fm            (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_cnu
 * Referenced by: '<S4108>/Constant'
 */
#define rtCP_Constant_Value_cnu        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_p5e
 * Referenced by: '<S4109>/Constant'
 */
#define rtCP_Constant_Value_p5e        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4110>/Constant5'
 */
#define rtCP_Constant5_Value_j1        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_g5
 * Referenced by: '<S4111>/LimitSource'
 */
#define rtCP_LimitSource_Value_g5      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_dmv
 * Referenced by: '<S4115>/Constant'
 */
#define rtCP_Constant_Value_dmv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_iyy
 * Referenced by: '<S4116>/Constant'
 */
#define rtCP_Constant_Value_iyy        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4117>/Constant5'
 */
#define rtCP_Constant5_Value_bb        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_al
 * Referenced by: '<S4118>/LimitSource'
 */
#define rtCP_LimitSource_Value_al      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_l3
 * Referenced by: '<S4122>/Constant'
 */
#define rtCP_Constant_Value_l3         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pue
 * Referenced by: '<S4125>/Constant'
 */
#define rtCP_Constant_Value_pue        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_g4
 * Referenced by: '<S4105>/Gain'
 */
#define rtCP_Gain_Gain_g4              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_i5g
 * Referenced by: '<S4106>/Gain'
 */
#define rtCP_Gain_Gain_i5g             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_mo1
 * Referenced by: '<S4107>/Gain'
 */
#define rtCP_Gain_Gain_mo1             (0.5F)

/* Computed Parameter: rtCP_Constant_Value_by
 * Referenced by: '<S4129>/Constant'
 */
#define rtCP_Constant_Value_by         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gj
 * Referenced by: '<S4130>/Constant'
 */
#define rtCP_Constant_Value_gj         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4131>/Constant5'
 */
#define rtCP_Constant5_Value_bs        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_cf
 * Referenced by: '<S4132>/LimitSource'
 */
#define rtCP_LimitSource_Value_cf      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ppc
 * Referenced by: '<S4136>/Constant'
 */
#define rtCP_Constant_Value_ppc        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cpo
 * Referenced by: '<S4137>/Constant'
 */
#define rtCP_Constant_Value_cpo        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4138>/Constant5'
 */
#define rtCP_Constant5_Value_gt        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_nq
 * Referenced by: '<S4139>/LimitSource'
 */
#define rtCP_LimitSource_Value_nq      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_j4m
 * Referenced by: '<S4143>/Constant'
 */
#define rtCP_Constant_Value_j4m        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_exwb
 * Referenced by: '<S4146>/Constant'
 */
#define rtCP_Constant_Value_exwb       (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_ic
 * Referenced by: '<S4126>/Gain'
 */
#define rtCP_Gain_Gain_ic              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_dq
 * Referenced by: '<S4127>/Gain'
 */
#define rtCP_Gain_Gain_dq              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_hsf
 * Referenced by: '<S4128>/Gain'
 */
#define rtCP_Gain_Gain_hsf             (0.5F)

/* Computed Parameter: rtCP_Constant_Value_lwo
 * Referenced by: '<S4150>/Constant'
 */
#define rtCP_Constant_Value_lwo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mgm
 * Referenced by: '<S4151>/Constant'
 */
#define rtCP_Constant_Value_mgm        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4152>/Constant5'
 */
#define rtCP_Constant5_Value_at        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_mm
 * Referenced by: '<S4153>/LimitSource'
 */
#define rtCP_LimitSource_Value_mm      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ozl
 * Referenced by: '<S4157>/Constant'
 */
#define rtCP_Constant_Value_ozl        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ft1
 * Referenced by: '<S4158>/Constant'
 */
#define rtCP_Constant_Value_ft1        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4159>/Constant5'
 */
#define rtCP_Constant5_Value_pk        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_dc
 * Referenced by: '<S4160>/LimitSource'
 */
#define rtCP_LimitSource_Value_dc      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ld5
 * Referenced by: '<S4164>/Constant'
 */
#define rtCP_Constant_Value_ld5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bs2
 * Referenced by: '<S4167>/Constant'
 */
#define rtCP_Constant_Value_bs2        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_d0n
 * Referenced by: '<S4147>/Gain'
 */
#define rtCP_Gain_Gain_d0n             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_er
 * Referenced by: '<S4148>/Gain'
 */
#define rtCP_Gain_Gain_er              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_fh
 * Referenced by: '<S4149>/Gain'
 */
#define rtCP_Gain_Gain_fh              (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S1221>/Constant'
 */
#define rtCP_Constant_Value_o2a        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_mte
 * Referenced by: '<S1226>/Constant'
 */
#define rtCP_Constant_Value_mte        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_k2y
 * Referenced by: '<S1229>/Constant'
 */
#define rtCP_Constant_Value_k2y        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1224>/Constant'
 */
#define rtCP_Constant_Value_f0g        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_gfr
 * Referenced by: '<S1232>/Constant'
 */
#define rtCP_Constant_Value_gfr        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pik
 * Referenced by: '<S1233>/Constant'
 */
#define rtCP_Constant_Value_pik        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1225>/Constant2'
 */
#define rtCP_Constant2_Value_pt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1225>/Constant3'
 */
#define rtCP_Constant3_Value_g         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dz1
 * Referenced by: '<S1243>/Constant'
 */
#define rtCP_Constant_Value_dz1        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ebt
 * Referenced by: '<S1244>/Constant'
 */
#define rtCP_Constant_Value_ebt        (0.9F)

/* Computed Parameter: rtCP_Constant_Value_az
 * Referenced by: '<S1245>/Constant'
 */
#define rtCP_Constant_Value_az         (0.3F)

/* Expression: const
 * Referenced by: '<S1248>/Constant'
 */
#define rtCP_Constant_Value_ikq        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_nz
 * Referenced by: '<S1256>/Constant'
 */
#define rtCP_Constant_Value_nz         (30.0F)

/* Expression: single(0)
 * Referenced by: '<S1259>/Constant3'
 */
#define rtCP_Constant3_Value_a         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_d5f
 * Referenced by: '<S1262>/Constant'
 */
#define rtCP_Constant_Value_d5f        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_jyi
 * Referenced by: '<S1263>/Constant'
 */
#define rtCP_Constant_Value_jyi        (20.0F)

/* Computed Parameter: rtCP_Constant_Value_ezn
 * Referenced by: '<S1264>/Constant'
 */
#define rtCP_Constant_Value_ezn        (5.0F)

/* Computed Parameter: rtCP_Constant_Value_o2l
 * Referenced by: '<S1265>/Constant'
 */
#define rtCP_Constant_Value_o2l        (5.0F)

/* Expression: const
 * Referenced by: '<S1289>/Constant'
 */
#define rtCP_Constant_Value_ij1        (1.0F)

/* Expression: single(0)
 * Referenced by: '<S1291>/Constant3'
 */
#define rtCP_Constant3_Value_kg        (0.0F)

/* Expression: const
 * Referenced by: '<S1295>/Constant'
 */
#define rtCP_Constant_Value_mpa        (1.5F)

/* Computed Parameter: rtCP_Constant_Value_kwq
 * Referenced by: '<S1303>/Constant'
 */
#define rtCP_Constant_Value_kwq        (0.0F)

/* Expression: const
 * Referenced by: '<S1321>/Constant'
 */
#define rtCP_Constant_Value_hzv        (1.5F)

/* Expression: single(0)
 * Referenced by: '<S1284>/Constant'
 */
#define rtCP_Constant_Value_nmx        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gv2
 * Referenced by: '<S1351>/Constant'
 */
#define rtCP_Constant_Value_gv2        (26.0F)

/* Computed Parameter: rtCP_Constant_Value_jwm
 * Referenced by: '<S1355>/Constant'
 */
#define rtCP_Constant_Value_jwm        (0.0F)

/* Expression: const
 * Referenced by: '<S1358>/Constant'
 */
#define rtCP_Constant_Value_k1o        (-2.0F)

/* Expression: single(0)
 * Referenced by: '<S2091>/Constant'
 */
#define rtCP_Constant_Value_ppi        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aik
 * Referenced by: '<S2093>/Constant'
 */
#define rtCP_Constant_Value_aik        (0.5F)

/* Expression: single(0)
 * Referenced by: '<S2092>/Constant'
 */
#define rtCP_Constant_Value_jjt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2092>/Constant1'
 */
#define rtCP_Constant1_Value_hqa       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pwi
 * Referenced by: '<S2102>/Constant'
 */
#define rtCP_Constant_Value_pwi        (0.001F)

/* Computed Parameter: rtCP_Constant_Value_d31
 * Referenced by: '<S2103>/Constant'
 */
#define rtCP_Constant_Value_d31        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dg4
 * Referenced by: '<S2104>/Constant'
 */
#define rtCP_Constant_Value_dg4        (100.0F)

/* Expression: single(200)
 * Referenced by: '<S2085>/Constant'
 */
#define rtCP_Constant_Value_few        (200.0F)

/* Expression: LTAPSampleTime
 * Referenced by: '<S2273>/SampleTime'
 */
#define rtCP_SampleTime_Value_p        (0.05F)
#define rtCP_PredictionTimeVector_Value_EL_0 (rtCP_pooled_zcOdeOlOUYLM[0])
#define rtCP_PredictionTimeVector_Value_EL_1 (rtCP_pooled_zcOdeOlOUYLM[1])
#define rtCP_PredictionTimeVector_Value_EL_2 (rtCP_pooled_zcOdeOlOUYLM[2])
#define rtCP_PredictionTimeVector_Value_EL_3 (rtCP_pooled_zcOdeOlOUYLM[3])
#define rtCP_PredictionTimeVector_Value_EL_4 (rtCP_pooled_zcOdeOlOUYLM[4])
#define rtCP_PredictionTimeVector_Value_EL_5 (rtCP_pooled_zcOdeOlOUYLM[5])
#define rtCP_PredictionTimeVector_Value_EL_6 (rtCP_pooled_zcOdeOlOUYLM[6])
#define rtCP_PredictionTimeVector_Value_EL_7 (rtCP_pooled_zcOdeOlOUYLM[7])
#define rtCP_PredictionTimeVector_Value_EL_8 (rtCP_pooled_zcOdeOlOUYLM[8])
#define rtCP_PredictionTimeVector_Value_EL_9 (rtCP_pooled_zcOdeOlOUYLM[9])
#define rtCP_PredictionTimeVector_Value_EL_10 (rtCP_pooled_zcOdeOlOUYLM[10])
#define rtCP_PredictionTimeVector_Value_EL_11 (rtCP_pooled_zcOdeOlOUYLM[11])
#define rtCP_PredictionTimeVector_Value_EL_12 (rtCP_pooled_zcOdeOlOUYLM[12])
#define rtCP_PredictionTimeVector_Value_EL_13 (rtCP_pooled_zcOdeOlOUYLM[13])
#define rtCP_PredictionTimeVector_Value_EL_14 (rtCP_pooled_zcOdeOlOUYLM[14])
#define rtCP_PredictionTimeVector_Value_EL_15 (rtCP_pooled_zcOdeOlOUYLM[15])
#define rtCP_PredictionTimeVector_Value_EL_16 (rtCP_pooled_zcOdeOlOUYLM[16])
#define rtCP_PredictionTimeVector_Value_EL_17 (rtCP_pooled_zcOdeOlOUYLM[17])
#define rtCP_PredictionTimeVector_Value_EL_18 (rtCP_pooled_zcOdeOlOUYLM[18])
#define rtCP_PredictionTimeVector_Value_EL_19 (rtCP_pooled_zcOdeOlOUYLM[19])
#define rtCP_PredictionTimeVector_Value_EL_20 (rtCP_pooled_zcOdeOlOUYLM[20])
#define rtCP_PredictionTimeVector_Value_EL_21 (rtCP_pooled_zcOdeOlOUYLM[21])
#define rtCP_PredictionTimeVector_Value_EL_22 (rtCP_pooled_zcOdeOlOUYLM[22])
#define rtCP_PredictionTimeVector_Value_EL_23 (rtCP_pooled_zcOdeOlOUYLM[23])
#define rtCP_PredictionTimeVector_Value_EL_24 (rtCP_pooled_zcOdeOlOUYLM[24])
#define rtCP_PredictionTimeVector_Value_EL_25 (rtCP_pooled_zcOdeOlOUYLM[25])
#define rtCP_PredictionTimeVector_Value_EL_26 (rtCP_pooled_zcOdeOlOUYLM[26])
#define rtCP_PredictionTimeVector_Value_EL_27 (rtCP_pooled_zcOdeOlOUYLM[27])
#define rtCP_PredictionTimeVector_Value_EL_28 (rtCP_pooled_zcOdeOlOUYLM[28])
#define rtCP_PredictionTimeVector_Value_EL_29 (rtCP_pooled_zcOdeOlOUYLM[29])
#define rtCP_PredictionTimeVector_Value_EL_30 (rtCP_pooled_zcOdeOlOUYLM[30])
#define rtCP_PredictionTimeVector_Value_EL_31 (rtCP_pooled_zcOdeOlOUYLM[31])
#define rtCP_PredictionTimeVector_Value_EL_32 (rtCP_pooled_zcOdeOlOUYLM[32])
#define rtCP_PredictionTimeVector_Value_EL_33 (rtCP_pooled_zcOdeOlOUYLM[33])
#define rtCP_PredictionTimeVector_Value_EL_34 (rtCP_pooled_zcOdeOlOUYLM[34])
#define rtCP_PredictionTimeVector_Value_EL_35 (rtCP_pooled_zcOdeOlOUYLM[35])
#define rtCP_PredictionTimeVector_Value_EL_36 (rtCP_pooled_zcOdeOlOUYLM[36])
#define rtCP_PredictionTimeVector_Value_EL_37 (rtCP_pooled_zcOdeOlOUYLM[37])
#define rtCP_PredictionTimeVector_Value_EL_38 (rtCP_pooled_zcOdeOlOUYLM[38])
#define rtCP_PredictionTimeVector_Value_EL_39 (rtCP_pooled_zcOdeOlOUYLM[39])
#define rtCP_PredictionTimeVector_Value_EL_40 (rtCP_pooled_zcOdeOlOUYLM[40])
#define rtCP_PredictionTimeVector_Value_EL_41 (rtCP_pooled_zcOdeOlOUYLM[41])
#define rtCP_PredictionTimeVector_Value_EL_42 (rtCP_pooled_zcOdeOlOUYLM[42])
#define rtCP_PredictionTimeVector_Value_EL_43 (rtCP_pooled_zcOdeOlOUYLM[43])
#define rtCP_PredictionTimeVector_Value_EL_44 (rtCP_pooled_zcOdeOlOUYLM[44])
#define rtCP_PredictionTimeVector_Value_EL_45 (rtCP_pooled_zcOdeOlOUYLM[45])
#define rtCP_PredictionTimeVector_Value_EL_46 (rtCP_pooled_zcOdeOlOUYLM[46])
#define rtCP_PredictionTimeVector_Value_EL_47 (rtCP_pooled_zcOdeOlOUYLM[47])
#define rtCP_PredictionTimeVector_Value_EL_48 (rtCP_pooled_zcOdeOlOUYLM[48])
#define rtCP_PredictionTimeVector_Value_EL_49 (rtCP_pooled_zcOdeOlOUYLM[49])
#define rtCP_PredictionTimeVector_Value_EL_50 (rtCP_pooled_zcOdeOlOUYLM[50])
#define rtCP_PredictionTimeVector_Value_EL_51 (rtCP_pooled_zcOdeOlOUYLM[51])
#define rtCP_PredictionTimeVector_Value_EL_52 (rtCP_pooled_zcOdeOlOUYLM[52])
#define rtCP_PredictionTimeVector_Value_EL_53 (rtCP_pooled_zcOdeOlOUYLM[53])
#define rtCP_PredictionTimeVector_Value_EL_54 (rtCP_pooled_zcOdeOlOUYLM[54])
#define rtCP_PredictionTimeVector_Value_EL_55 (rtCP_pooled_zcOdeOlOUYLM[55])
#define rtCP_PredictionTimeVector_Value_EL_56 (rtCP_pooled_zcOdeOlOUYLM[56])
#define rtCP_PredictionTimeVector_Value_EL_57 (rtCP_pooled_zcOdeOlOUYLM[57])
#define rtCP_PredictionTimeVector_Value_EL_58 (rtCP_pooled_zcOdeOlOUYLM[58])
#define rtCP_PredictionTimeVector_Value_EL_59 (rtCP_pooled_zcOdeOlOUYLM[59])

/* Expression: single(0.5)
 * Referenced by: '<S2160>/Constant'
 */
#define rtCP_Constant_Value_hjt        (0.5F)

/* Expression: single(pi)
 * Referenced by: '<S2160>/Constant1'
 */
#define rtCP_Constant1_Value_fl        (3.14159274F)

/* Expression: single(pi/2)
 * Referenced by: '<S2229>/Constant1'
 */
#define rtCP_Constant1_Value_o4m       (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S2229>/Constant2'
 */
#define rtCP_Constant2_Value_od        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2232>/Constant5'
 */
#define rtCP_Constant5_Value_o1        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_iya
 * Referenced by: '<S2228>/Constant'
 */
#define rtCP_Constant_Value_iya        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oyk
 * Referenced by: '<S2230>/Constant'
 */
#define rtCP_Constant_Value_oyk        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ow
 * Referenced by: '<S2230>/Constant1'
 */
#define rtCP_Constant1_Value_ow        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2236>/Constant'
 */
#define rtCP_Constant_Value_fi4        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_p2
 * Referenced by: '<S2240>/Constant'
 */
#define rtCP_Constant_Value_p2         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ir
 * Referenced by: '<S2238>/LimitSource'
 */
#define rtCP_LimitSource_Value_ir      (0.0001F)

/* Expression: single(0.5)
 * Referenced by: '<S2243>/Constant'
 */
#define rtCP_Constant_Value_jyr        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_na1
 * Referenced by: '<S2244>/Constant'
 */
#define rtCP_Constant_Value_na1        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_kig
 * Referenced by: '<S2244>/Constant1'
 */
#define rtCP_Constant1_Value_kig       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2246>/Constant'
 */
#define rtCP_Constant_Value_i5u        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_bnn
 * Referenced by: '<S2250>/Constant'
 */
#define rtCP_Constant_Value_bnn        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_lv
 * Referenced by: '<S2248>/LimitSource'
 */
#define rtCP_LimitSource_Value_lv      (0.0001F)

/* Expression: single(pi)
 * Referenced by: '<S2253>/Constant_2'
 */
#define rtCP_Constant_2_Value_dg       (3.14159274F)

/* Computed Parameter: rtCP_Constant_Value_i3
 * Referenced by: '<S2256>/Constant'
 */
#define rtCP_Constant_Value_i3         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fbr
 * Referenced by: '<S2257>/Constant'
 */
#define rtCP_Constant_Value_fbr        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nnh
 * Referenced by: '<S2258>/Constant'
 */
#define rtCP_Constant_Value_nnh        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ntp
 * Referenced by: '<S2259>/Constant'
 */
#define rtCP_Constant_Value_ntp        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2020>/Constant1'
 */
#define rtCP_Constant1_Value_jv        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2020>/Constant6'
 */
#define rtCP_Constant6_Value_f         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2021>/Constant1'
 */
#define rtCP_Constant1_Value_cgp       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2021>/Constant2'
 */
#define rtCP_Constant2_Value_gs        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2021>/Constant3'
 */
#define rtCP_Constant3_Value_k3        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2021>/Constant4'
 */
#define rtCP_Constant4_Value_b2        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2021>/Constant5'
 */
#define rtCP_Constant5_Value_n5        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2021>/Constant6'
 */
#define rtCP_Constant6_Value_o         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2021>/Constant8'
 */
#define rtCP_Constant8_Value_d         (0.0F)

/* Expression: single(5)
 * Referenced by: '<S2317>/Constant'
 */
#define rtCP_Constant_Value_gjb        (5.0F)

/* Expression: single(-1)
 * Referenced by: '<S2317>/Constant2'
 */
#define rtCP_Constant2_Value_in        (-1.0F)

/* Expression: single(1)
 * Referenced by: '<S2317>/Constant3'
 */
#define rtCP_Constant3_Value_b         (1.0F)

/* Computed Parameter: rtCP_Constant_Value_ib1
 * Referenced by: '<S2319>/Constant'
 */
#define rtCP_Constant_Value_ib1        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1384>/Constant10'
 */
#define rtCP_Constant10_Value_k        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1384>/Constant3'
 */
#define rtCP_Constant3_Value_px        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1384>/Constant5'
 */
#define rtCP_Constant5_Value_p2        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1384>/Constant6'
 */
#define rtCP_Constant6_Value_p         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1384>/Constant8'
 */
#define rtCP_Constant8_Value_e         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1407>/Constant'
 */
#define rtCP_Constant_Value_lkg        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1408>/Constant8'
 */
#define rtCP_Constant8_Value_a         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ac
 * Referenced by: '<S2322>/Constant1'
 */
#define rtCP_Constant1_Value_ac        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_pn
 * Referenced by: '<S2322>/Constant3'
 */
#define rtCP_Constant3_Value_pn        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_pp
 * Referenced by: '<S2322>/Constant4'
 */
#define rtCP_Constant4_Value_pp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_je
 * Referenced by: '<S2607>/Constant'
 */
#define rtCP_Constant_Value_je         (0.0F)

/* Computed Parameter: rtCP_BrakeReductionLimit_Value
 * Referenced by: '<S28>/BrakeReductionLimit'
 */
#define rtCP_BrakeReductionLimit_Value (3.05555558F)

/* Computed Parameter: rtCP_zeroConstant2_Value
 * Referenced by: '<S16>/zeroConstant2'
 */
#define rtCP_zeroConstant2_Value       (0.0F)

/* Computed Parameter: rtCP_zeroConstant3_Value
 * Referenced by: '<S16>/zeroConstant3'
 */
#define rtCP_zeroConstant3_Value       (0.0F)

/* Computed Parameter: rtCP_zeroConstant4_Value
 * Referenced by: '<S16>/zeroConstant4'
 */
#define rtCP_zeroConstant4_Value       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S7>/Constant3'
 */
#define rtCP_Constant3_Value_jw        (0.0F)

/* Computed Parameter: rtCP_LowestSpeedToLimit_Value
 * Referenced by: '<S27>/LowestSpeedToLimit'
 */
#define rtCP_LowestSpeedToLimit_Value  (0.5F)

/* Expression: single(6)
 * Referenced by: '<S27>/ResetTime'
 */
#define rtCP_ResetTime_Value           (6.0F)

/* Computed Parameter: rtCP_Constant_Value_n10
 * Referenced by: '<S33>/Constant'
 */
#define rtCP_Constant_Value_n10        (1.0F)

/* Computed Parameter: rtCP_Constant1_Value_dx
 * Referenced by: '<S33>/Constant1'
 */
#define rtCP_Constant1_Value_dx        (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_e1
 * Referenced by: '<S33>/Constant2'
 */
#define rtCP_Constant2_Value_e1        (1.0F)

/* Computed Parameter: rtCP_Constant3_Value_cz
 * Referenced by: '<S33>/Constant3'
 */
#define rtCP_Constant3_Value_cz        (1.0F)

/* Expression: FCW_TypAvlLgtAccr_Co
 * Referenced by: '<S201>/FCW_TypAvlLgtAccr_Co'
 */
#define rtCP_FCW_TypAvlLgtAccr_Co_Value (-7.0F)

/* Computed Parameter: rtCP_ZERO_Value
 * Referenced by: '<S201>/ZERO'
 */
#define rtCP_ZERO_Value                (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bs0
 * Referenced by: '<S250>/Constant'
 */
#define rtCP_Constant_Value_bs0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pfz
 * Referenced by: '<S202>/Constant'
 */
#define rtCP_Constant_Value_pfz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gd
 * Referenced by: '<S208>/Constant'
 */
#define rtCP_Constant_Value_gd         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_fn
 * Referenced by: '<S208>/Constant1'
 */
#define rtCP_Constant1_Value_fn        (1.0F)

/* Computed Parameter: rtCP_Constant3_Value_h0
 * Referenced by: '<S208>/Constant3'
 */
#define rtCP_Constant3_Value_h0        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_oxn
 * Referenced by: '<S208>/Constant4'
 */
#define rtCP_Constant4_Value_oxn       (1.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S208>/FCW_Freq_Co'
 */
#define rtCP_FCW_Freq_Co_Value         (50.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S208>/FCW_Freq_Co1'
 */
#define rtCP_FCW_Freq_Co1_Value        (50.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S211>/FCW_Freq_Co'
 */
#define rtCP_FCW_Freq_Co_Value_g       (50.0F)

/* Computed Parameter: rtCP_Constant_Value_jk
 * Referenced by: '<S277>/Constant'
 */
#define rtCP_Constant_Value_jk         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_oj
 * Referenced by: '<S277>/Constant1'
 */
#define rtCP_Constant1_Value_oj        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_ls
 * Referenced by: '<S294>/Constant'
 */
#define rtCP_Constant_Value_ls         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_iir
 * Referenced by: '<S308>/Constant'
 */
#define rtCP_Constant_Value_iir        (2.0F)

/* Computed Parameter: rtCP_Constant_Value_pzd
 * Referenced by: '<S309>/Constant'
 */
#define rtCP_Constant_Value_pzd        (13.8888893F)

/* Computed Parameter: rtCP_Constant_Value_n34
 * Referenced by: '<S213>/Constant'
 */
#define rtCP_Constant_Value_n34        (-1.0F)

/* Expression: FCW_TypAvlLatAccr_Co
 * Referenced by: '<S319>/FCW_TypAvlLatAccr_Co'
 */
#define rtCP_FCW_TypAvlLatAccr_Co_Value (2.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S321>/FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca2'
 */
#define rtCP_FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca2_Value (50.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S321>/FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca8'
 */
#define rtCP_FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca8_Value (50.0F)

/* Computed Parameter: rtCP_Constant_Value_jzs
 * Referenced by: '<S324>/Constant'
 */
#define rtCP_Constant_Value_jzs        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ay
 * Referenced by: '<S324>/Constant1'
 */
#define rtCP_Constant1_Value_ay        (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_gd
 * Referenced by: '<S325>/Constant2'
 */
#define rtCP_Constant2_Value_gd        (1.0F)

/* Computed Parameter: rtCP_Constant4_Value_or
 * Referenced by: '<S325>/Constant4'
 */
#define rtCP_Constant4_Value_or        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_loo
 * Referenced by: '<S323>/Constant'
 */
#define rtCP_Constant_Value_loo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_p3b
 * Referenced by: '<S337>/Constant'
 */
#define rtCP_Constant_Value_p3b        (0.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S332>/FCW_Freq_Co'
 */
#define rtCP_FCW_Freq_Co_Value_g0      (50.0F)

/* Expression: single(0)
 * Referenced by: '<S329>/NoDelay'
 */
#define rtCP_NoDelay_Value             (0.0F)

/* Expression: single(0)
 * Referenced by: '<S329>/NoDelay1'
 */
#define rtCP_NoDelay1_Value            (0.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S48>/FCW_Freq_Co'
 */
#define rtCP_FCW_Freq_Co_Value_e       (50.0F)

/* Computed Parameter: rtCP_Constant_Value_eii
 * Referenced by: '<S362>/Constant'
 */
#define rtCP_Constant_Value_eii        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_g0d
 * Referenced by: '<S362>/Constant1'
 */
#define rtCP_Constant1_Value_g0d       (1.0F)

/* Expression: single(0)
 * Referenced by: '<S471>/AccReqNoActivation'
 */
#define rtCP_AccReqNoActivation_Value  (0.0F)

/* Computed Parameter: rtCP_Constant_Value_clu
 * Referenced by: '<S476>/Constant'
 */
#define rtCP_Constant_Value_clu        (0.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S480>/iteration time2'
 */
#define rtCP_iterationtime2_Value      (0.02F)

/* Computed Parameter: rtCP_Constant_Value_pb4
 * Referenced by: '<S481>/Constant'
 */
#define rtCP_Constant_Value_pb4        (0.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S489>/iteration time2'
 */
#define rtCP_iterationtime2_Value_j    (0.02F)

/* Computed Parameter: rtCP_Constant_Value_bq0
 * Referenced by: '<S498>/Constant'
 */
#define rtCP_Constant_Value_bq0        (0.0F)

/* Expression: single(1)
 * Referenced by: '<S503>/PreBrkMaxIncrease'
 */
#define rtCP_PreBrkMaxIncrease_Value   (1.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S503>/iteration time2'
 */
#define rtCP_iterationtime2_Value_j5   (0.02F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S524>/SampleTime'
 */
#define rtCP_SampleTime_Value_l        (0.02F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S519>/SampleTime'
 */
#define rtCP_SampleTime_Value_i        (0.02F)

/* Expression: single(0)
 * Referenced by: '<S475>/Constant1'
 */
#define rtCP_Constant1_Value_gco       (0.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S546>/SampleTime'
 */
#define rtCP_SampleTime_Value_nv       (0.02F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S547>/SampleTime'
 */
#define rtCP_SampleTime_Value_k        (0.02F)

/* Expression: single(0)
 * Referenced by: '<S576>/ZeroAcceleration'
 */
#define rtCP_ZeroAcceleration_Value    (0.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S575>/PeriodFunctionCall'
 */
#define rtCP_PeriodFunctionCall_Value  (0.02F)

/* Expression: CMBB_LoPosValInCllsnRednByBrkg_Co
 * Referenced by: '<S553>/LoPosValInCllsnRednByBrkg  '
 */
#define rtCP_LoPosValInCllsnRednByBrkg_Value (0.0001F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S554>/PeriodFunctionCall'
 */
#define rtCP_PeriodFunctionCall_Value_n (0.02F)

/* Expression: k_AEB_FrqFctCallInCllsnRednByBrkg
 * Referenced by: '<S587>/Constant9'
 */
#define rtCP_Constant9_Value_k         (40.0F)

/* Computed Parameter: rtCP_Constant2_Value_pf
 * Referenced by: '<S592>/Constant2'
 */
#define rtCP_Constant2_Value_pf        (1.0F)

/* Computed Parameter: rtCP_Constant4_Value_jo
 * Referenced by: '<S592>/Constant4'
 */
#define rtCP_Constant4_Value_jo        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S463>/Constant1'
 */
#define rtCP_Constant1_Value_ko        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_es
 * Referenced by: '<S612>/Constant2'
 */
#define rtCP_Constant2_Value_es        (1.0F)

/* Computed Parameter: rtCP_Constant4_Value_d1
 * Referenced by: '<S612>/Constant4'
 */
#define rtCP_Constant4_Value_d1        (0.0F)

/* Expression: k_AEB_FrqFctCallInCllsnRednByBrkg
 * Referenced by: '<S606>/iteration time2'
 */
#define rtCP_iterationtime2_Value_k    (40.0F)

/* Expression: single(100)
 * Referenced by: '<S607>/CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca'
 */
#define rtCP_CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca_Value (100.0F)

/* Expression: single(0)
 * Referenced by: '<S607>/CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca1'
 */
#define rtCP_CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca1_Value (0.0F)

/* Expression: single(0)
 * Referenced by: '<S607>/CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca3'
 */
#define rtCP_CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca3_Value (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aiw
 * Referenced by: '<S616>/Constant'
 */
#define rtCP_Constant_Value_aiw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ea2
 * Referenced by: '<S617>/Constant'
 */
#define rtCP_Constant_Value_ea2        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_jt
 * Referenced by: '<S619>/LimitSource'
 */
#define rtCP_LimitSource_Value_jt      (0.01F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S614>/SampleTime'
 */
#define rtCP_SampleTime_Value_ia       (0.02F)

/* Computed Parameter: rtCP_Constant3_Value_lv
 * Referenced by: '<S615>/Constant3'
 */
#define rtCP_Constant3_Value_lv        (100.0F)

/* Computed Parameter: rtCP_Constant_Value_lc
 * Referenced by: '<S624>/Constant'
 */
#define rtCP_Constant_Value_lc         (0.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S627>/SampleTime'
 */
#define rtCP_SampleTime_Value_j        (0.02F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S632>/PeriodFunctionCall'
 */
#define rtCP_PeriodFunctionCall_Value_p (0.02F)

/* Expression: CMBB_LoPosValInCllsnRednByBrkg_Co
 * Referenced by: '<S611>/LoPosValInCllsnRednByBrkg  '
 */
#define rtCP_LoPosValInCllsnRednByBrkg_Value_k (0.0001F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S634>/SampleTime'
 */
#define rtCP_SampleTime_Value_kv       (0.02F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S600>/PeriodFunctionCall'
 */
#define rtCP_PeriodFunctionCall_Value_na (0.02F)

/* Computed Parameter: rtCP_Constant_Value_pg
 * Referenced by: '<S699>/Constant'
 */
#define rtCP_Constant_Value_pg         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jbm
 * Referenced by: '<S727>/Constant'
 */
#define rtCP_Constant_Value_jbm        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_kb
 * Referenced by: '<S722>/Constant1'
 */
#define rtCP_Constant1_Value_kb        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S733>/Constant3'
 */
#define rtCP_Constant3_Value_kz        (0.0F)

/* Expression: single(pi)
 * Referenced by: '<S739>/Constant4'
 */
#define rtCP_Constant4_Value_nk        (3.14159274F)

/* Expression: k_AEB_FrqFctCallInCllsnRednByBrkg
 * Referenced by: '<S742>/Constant9'
 */
#define rtCP_Constant9_Value_i         (40.0F)

/* Computed Parameter: rtCP_Constant_Value_pl
 * Referenced by: '<S750>/Constant'
 */
#define rtCP_Constant_Value_pl         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_bly
 * Referenced by: '<S750>/Constant1'
 */
#define rtCP_Constant1_Value_bly       (1.0F)

/* Expression: single(pi)
 * Referenced by: '<S753>/Constant5'
 */
#define rtCP_Constant5_Value_ok        (3.14159274F)

/* Expression: single(0)
 * Referenced by: '<S754>/Constant8'
 */
#define rtCP_Constant8_Value_n         (0.0F)

/* Expression: k_AEB_FrqFctCallInCllsnRednByBrkg
 * Referenced by: '<S754>/Constant9'
 */
#define rtCP_Constant9_Value_c         (40.0F)

/* Computed Parameter: rtCP_Constant_Value_bi2
 * Referenced by: '<S765>/Constant'
 */
#define rtCP_Constant_Value_bi2        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_cnfp
 * Referenced by: '<S765>/Constant1'
 */
#define rtCP_Constant1_Value_cnfp      (1.0F)

/* Expression: k_AEB_FrqFctCallInCllsnRednByBrkg
 * Referenced by: '<S757>/Constant9'
 */
#define rtCP_Constant9_Value_p         (40.0F)

/* Computed Parameter: rtCP_Constant_Value_dkl
 * Referenced by: '<S767>/Constant'
 */
#define rtCP_Constant_Value_dkl        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_oc
 * Referenced by: '<S767>/Constant1'
 */
#define rtCP_Constant1_Value_oc        (1.0F)

/* Expression: single(0)
 * Referenced by: '<S725>/Constant'
 */
#define rtCP_Constant_Value_jbg        (0.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S774>/SampleTime'
 */
#define rtCP_SampleTime_Value_c        (0.02F)

/* Expression: single(0)
 * Referenced by: '<S814>/Constant'
 */
#define rtCP_Constant_Value_km         (0.0F)

/* Expression: single(1)
 * Referenced by: '<S826>/Constant1'
 */
#define rtCP_Constant1_Value_pzo       (1.0F)

/* Expression: single(1)
 * Referenced by: '<S827>/Constant'
 */
#define rtCP_Constant_Value_nzx        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S849>/Constant1'
 */
#define rtCP_Constant1_Value_d1n       (1.0F)

/* Expression: single(1)
 * Referenced by: '<S850>/Constant'
 */
#define rtCP_Constant_Value_pud        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S823>/Constant'
 */
#define rtCP_Constant_Value_gnw        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S824>/Constant'
 */
#define rtCP_Constant_Value_bnt        (1.0F)

/* Expression: LoPosValInDrvrStEstimr
 * Referenced by: '<S817>/Constant'
 */
#define rtCP_Constant_Value_p05        (1.0E-8F)

/* Expression: single(0)
 * Referenced by: '<S905>/Constant'
 */
#define rtCP_Constant_Value_paw        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S905>/Constant1'
 */
#define rtCP_Constant1_Value_bo        (0.0F)

/* Expression: TiForLenMinOfPathInDrvrStEstimr
 * Referenced by: '<S907>/NecessaryPredictionTime'
 */
#define rtCP_NecessaryPredictionTime_Value (2.1F)

/* Computed Parameter: rtCP_Constant_Value_mqjn
 * Referenced by: '<S915>/Constant'
 */
#define rtCP_Constant_Value_mqjn       (0.0F)

/* Expression: single(3)
 * Referenced by: '<S914>/Constant'
 */
#define rtCP_Constant_Value_jbz        (3.0F)

/* Expression: -single(0.5)
 * Referenced by: '<S914>/Constant1'
 */
#define rtCP_Constant1_Value_dd        (-0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S914>/Constant3'
 */
#define rtCP_Constant3_Value_do        (0.5F)

/* Expression: single(2)
 * Referenced by: '<S919>/Constant'
 */
#define rtCP_Constant_Value_drm        (2.0F)

/* Expression: single(3)
 * Referenced by: '<S919>/Constant1'
 */
#define rtCP_Constant1_Value_nih       (3.0F)

/* Expression: single(6)
 * Referenced by: '<S919>/Constant2'
 */
#define rtCP_Constant2_Value_kr        (6.0F)

/* Expression: single(2)
 * Referenced by: '<S919>/Constant3'
 */
#define rtCP_Constant3_Value_d5        (2.0F)

/* Expression: ALatAbsMaxForPathChgInDrvrStEstimr
 * Referenced by: '<S928>/Constant1'
 */
#define rtCP_Constant1_Value_ae        (1.2F)

/* Computed Parameter: rtCP_Constant3_Value_ga
 * Referenced by: '<S928>/Constant3'
 */
#define rtCP_Constant3_Value_ga        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_bz
 * Referenced by: '<S928>/Constant4'
 */
#define rtCP_Constant4_Value_bz        (0.0F)

/* Expression: MinimumSpeedForLaneFollowingInDrvrStEstimr
 * Referenced by: '<S929>/MinimumSpeedForLaneFollowing'
 */
#define rtCP_MinimumSpeedForLaneFollowing_Value (9.72222233F)

/* Expression: single(0)
 * Referenced by: '<S1006>/Constant3'
 */
#define rtCP_Constant3_Value_ds        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1013>/Constant3'
 */
#define rtCP_Constant3_Value_he        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1020>/Constant3'
 */
#define rtCP_Constant3_Value_fs        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1028>/Constant3'
 */
#define rtCP_Constant3_Value_bt        (0.0F)

/* Expression: single(2.5)
 * Referenced by: '<S986>/VelocityMinimumDuringVehicleFollowing'
 */
#define rtCP_VelocityMinimumDuringVehicleFollowing_Value (2.5F)

/* Expression: FrqFctCallInDrvrStEstimr
 * Referenced by: '<S1053>/C_Ts'
 */
#define rtCP_C_Ts_Value                (50.0F)

/* Computed Parameter: rtCP_Constant_Value_otz
 * Referenced by: '<S1104>/Constant'
 */
#define rtCP_Constant_Value_otz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cjd
 * Referenced by: '<S1105>/Constant'
 */
#define rtCP_Constant_Value_cjd        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1120>/Constant2'
 */
#define rtCP_Constant2_Value_el        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bxx
 * Referenced by: '<S1124>/Constant'
 */
#define rtCP_Constant_Value_bxx        (1.0F)

/* Expression: FrqFctCallInDrvrStEstimr
 * Referenced by: '<S1134>/CmpFacForALgtCmftInDrvrStEstimr1'
 */
#define rtCP_CmpFacForALgtCmftInDrvrStEstimr1_Value (50.0F)

/* Computed Parameter: rtCP_Constant_Value_iqb
 * Referenced by: '<S1142>/Constant'
 */
#define rtCP_Constant_Value_iqb        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ju
 * Referenced by: '<S1142>/Constant1'
 */
#define rtCP_Constant1_Value_ju        (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_dk
 * Referenced by: '<S1143>/Constant2'
 */
#define rtCP_Constant2_Value_dk        (1.0F)

/* Computed Parameter: rtCP_Constant4_Value_l5
 * Referenced by: '<S1143>/Constant4'
 */
#define rtCP_Constant4_Value_l5        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_gvk
 * Referenced by: '<S1132>/Constant1'
 */
#define rtCP_Constant1_Value_gvk       (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_ny
 * Referenced by: '<S1132>/Constant2'
 */
#define rtCP_Constant2_Value_ny        (1.25F)

/* Computed Parameter: rtCP_Constant6_Value_l5
 * Referenced by: '<S1132>/Constant6'
 */
#define rtCP_Constant6_Value_l5        (1.0F)

/* Expression: PerdFctCallInDrvrStEstimr
 * Referenced by: '<S1183>/updateTime'
 */
#define rtCP_updateTime_Value          (0.02F)

/* Expression: PerdFctCallInDrvrStEstimr
 * Referenced by: '<S1184>/updateTime'
 */
#define rtCP_updateTime_Value_c        (0.02F)

/* Computed Parameter: rtCP_Constant4_Value_duv
 * Referenced by: '<S1182>/Constant4'
 */
#define rtCP_Constant4_Value_duv       (1.0F)

/* Expression: LoPosValInDrvrStEstimr
 * Referenced by: '<S1194>/LoPosVal'
 */
#define rtCP_LoPosVal_Value            (1.0E-8F)

/* Computed Parameter: rtCP_Constant_Value_ouzr
 * Referenced by: '<S1203>/Constant'
 */
#define rtCP_Constant_Value_ouzr       (0.0F)

/* Expression: single(1)
 * Referenced by: '<S2635>/CosHeading'
 */
#define rtCP_CosHeading_Value          (1.0F)

/* Expression: single(0.01)
 * Referenced by: '<S2635>/LengthSideLat'
 */
#define rtCP_LengthSideLat_Value       (0.01F)

/* Expression: single(0.01)
 * Referenced by: '<S2635>/LengthSideLgt'
 */
#define rtCP_LengthSideLgt_Value       (0.01F)

/* Expression: single(0)
 * Referenced by: '<S2635>/RotationAngle'
 */
#define rtCP_RotationAngle_Value       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2635>/SinHeading'
 */
#define rtCP_SinHeading_Value          (0.0F)

/* Expression: single(-1)
 * Referenced by: '<S2636>/Constant'
 */
#define rtCP_Constant_Value_eup        (-1.0F)

/* Expression: single(1)
 * Referenced by: '<S2636>/Constant4'
 */
#define rtCP_Constant4_Value_it        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_n1s
 * Referenced by: '<S2657>/Constant'
 */
#define rtCP_Constant_Value_n1s        (0.0F)

/* Expression: single(2)
 * Referenced by: '<S2608>/Constant13'
 */
#define rtCP_Constant13_Value_hv       (2.0F)

/* Computed Parameter: rtCP_Constant20_Value_i
 * Referenced by: '<S2608>/Constant20'
 */
#define rtCP_Constant20_Value_i        (1.0F)

/* Expression: single(0)
 * Referenced by: '<S2608>/Constant32'
 */
#define rtCP_Constant32_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2608>/Constant33'
 */
#define rtCP_Constant33_Value_n        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2608>/Constant34'
 */
#define rtCP_Constant34_Value_d        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2608>/Constant35'
 */
#define rtCP_Constant35_Value_j        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2608>/Constant36'
 */
#define rtCP_Constant36_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2608>/Constant9'
 */
#define rtCP_Constant9_Value_cd        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2608>/Constant_2'
 */
#define rtCP_Constant_2_Value_c        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2624>/Constant4'
 */
#define rtCP_Constant4_Value_h0        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2685>/Constant5'
 */
#define rtCP_Constant5_Value_l4        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2686>/Constant5'
 */
#define rtCP_Constant5_Value_dj        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_eyw
 * Referenced by: '<S2713>/Constant'
 */
#define rtCP_Constant_Value_eyw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_le4
 * Referenced by: '<S2714>/Constant'
 */
#define rtCP_Constant_Value_le4        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_i1
 * Referenced by: '<S2715>/LimitSource'
 */
#define rtCP_LimitSource_Value_i1      (0.01F)

/* Computed Parameter: rtCP_Zero_Value_p
 * Referenced by: '<S2706>/Zero'
 */
#define rtCP_Zero_Value_p              (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_p3
 * Referenced by: '<S2694>/Constant3'
 */
#define rtCP_Constant3_Value_p3        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2694>/OffsMinForCllsnRednByBrkgActv1'
 */
#define rtCP_OffsMinForCllsnRednByBrkgActv1_Value (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_n3
 * Referenced by: '<S2710>/Constant3'
 */
#define rtCP_Constant3_Value_n3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ksz
 * Referenced by: '<S2716>/Constant'
 */
#define rtCP_Constant_Value_ksz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_eqw
 * Referenced by: '<S2695>/Constant'
 */
#define rtCP_Constant_Value_eqw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nhh
 * Referenced by: '<S2721>/Constant'
 */
#define rtCP_Constant_Value_nhh        (4.0F)

/* Computed Parameter: rtCP_Constant_Value_cey
 * Referenced by: '<S2697>/Constant'
 */
#define rtCP_Constant_Value_cey        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_piu
 * Referenced by: '<S2730>/Constant'
 */
#define rtCP_Constant_Value_piu        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ewy
 * Referenced by: '<S2731>/Constant'
 */
#define rtCP_Constant_Value_ewy        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_if2
 * Referenced by: '<S2736>/Constant'
 */
#define rtCP_Constant_Value_if2        (0.6F)

/* Computed Parameter: rtCP_Constant_Value_ppf
 * Referenced by: '<S2733>/Constant'
 */
#define rtCP_Constant_Value_ppf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aa
 * Referenced by: '<S2741>/Constant'
 */
#define rtCP_Constant_Value_aa         (4.0F)

/* Computed Parameter: rtCP_Constant_Value_bc2
 * Referenced by: '<S2742>/Constant'
 */
#define rtCP_Constant_Value_bc2        (0.65F)

/* Computed Parameter: rtCP_Constant_Value_d5q
 * Referenced by: '<S2734>/Constant'
 */
#define rtCP_Constant_Value_d5q        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f1k
 * Referenced by: '<S2747>/Constant'
 */
#define rtCP_Constant_Value_f1k        (4.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2749>/Constant5'
 */
#define rtCP_Constant5_Value_hj        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2750>/Constant5'
 */
#define rtCP_Constant5_Value_fc        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_gh
 * Referenced by: '<S2751>/LimitSource'
 */
#define rtCP_LimitSource_Value_gh      (1.0E-5F)

/* Computed Parameter: rtCP_Constant_Value_jnt
 * Referenced by: '<S2759>/Constant'
 */
#define rtCP_Constant_Value_jnt        (0.2F)

/* Computed Parameter: rtCP_Constant_Value_in0
 * Referenced by: '<S2760>/Constant'
 */
#define rtCP_Constant_Value_in0        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_cvp
 * Referenced by: '<S2761>/Constant'
 */
#define rtCP_Constant_Value_cvp        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_e2r
 * Referenced by: '<S2763>/Constant'
 */
#define rtCP_Constant_Value_e2r        (1.2F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2775>/Constant5'
 */
#define rtCP_Constant5_Value_cvk       (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2776>/Constant5'
 */
#define rtCP_Constant5_Value_fq        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_dxf
 * Referenced by: '<S2793>/Constant'
 */
#define rtCP_Constant_Value_dxf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cvo
 * Referenced by: '<S2802>/Constant'
 */
#define rtCP_Constant_Value_cvo        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2838>/Constant'
 */
#define rtCP_Constant_Value_do         (0.0F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S2840>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value (0.01F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S2840>/LengthSideLgtNoLength1'
 */
#define rtCP_LengthSideLgtNoLength1_Value (0.01F)

/* Computed Parameter: rtCP_Constant_Value_cmr
 * Referenced by: '<S2863>/Constant'
 */
#define rtCP_Constant_Value_cmr        (4.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2868>/Constant5'
 */
#define rtCP_Constant5_Value_o5        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2869>/Constant5'
 */
#define rtCP_Constant5_Value_iu        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_cvi
 * Referenced by: '<S2870>/LimitSource'
 */
#define rtCP_LimitSource_Value_cvi     (1.0E-5F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2877>/Constant5'
 */
#define rtCP_Constant5_Value_cr        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2878>/Constant5'
 */
#define rtCP_Constant5_Value_fm        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_dp
 * Referenced by: '<S2879>/LimitSource'
 */
#define rtCP_LimitSource_Value_dp      (1.0E-5F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2886>/Constant5'
 */
#define rtCP_Constant5_Value_go        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2887>/Constant5'
 */
#define rtCP_Constant5_Value_hh        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_cwy
 * Referenced by: '<S2888>/LimitSource'
 */
#define rtCP_LimitSource_Value_cwy     (1.0E-5F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2895>/Constant5'
 */
#define rtCP_Constant5_Value_nz        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2896>/Constant5'
 */
#define rtCP_Constant5_Value_a5        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_cft
 * Referenced by: '<S2897>/LimitSource'
 */
#define rtCP_LimitSource_Value_cft     (1.0E-5F)

/* Computed Parameter: rtCP_Constant1_Value_p2j
 * Referenced by: '<S2908>/Constant1'
 */
#define rtCP_Constant1_Value_p2j       (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_ci
 * Referenced by: '<S2908>/Constant2'
 */
#define rtCP_Constant2_Value_ci        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_od
 * Referenced by: '<S2908>/Constant3'
 */
#define rtCP_Constant3_Value_od        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_bj
 * Referenced by: '<S2908>/Constant4'
 */
#define rtCP_Constant4_Value_bj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mim
 * Referenced by: '<S2912>/Constant'
 */
#define rtCP_Constant_Value_mim        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ia
 * Referenced by: '<S2909>/Constant1'
 */
#define rtCP_Constant1_Value_ia        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_aq
 * Referenced by: '<S2909>/Constant2'
 */
#define rtCP_Constant2_Value_aq        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_pe
 * Referenced by: '<S2909>/Constant3'
 */
#define rtCP_Constant3_Value_pe        (0.0F)

/* Computed Parameter: rtCP_Constant8_Value_p
 * Referenced by: '<S2909>/Constant8'
 */
#define rtCP_Constant8_Value_p         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_our
 * Referenced by: '<S2914>/Constant'
 */
#define rtCP_Constant_Value_our        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_dzs
 * Referenced by: '<S2910>/Constant1'
 */
#define rtCP_Constant1_Value_dzs       (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_edp
 * Referenced by: '<S2910>/Constant2'
 */
#define rtCP_Constant2_Value_edp       (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_bp
 * Referenced by: '<S2910>/Constant3'
 */
#define rtCP_Constant3_Value_bp        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_h0x
 * Referenced by: '<S2910>/Constant4'
 */
#define rtCP_Constant4_Value_h0x       (0.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S2928>/Constant_1'
 */
#define rtCP_Constant_1_Value_by       (1.57079637F)

/* Computed Parameter: rtCP_Constant_2_Value_ot
 * Referenced by: '<S2928>/Constant_2'
 */
#define rtCP_Constant_2_Value_ot       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_orz
 * Referenced by: '<S3288>/Constant'
 */
#define rtCP_Constant_Value_orz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pup
 * Referenced by: '<S3289>/Constant'
 */
#define rtCP_Constant_Value_pup        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_bv
 * Referenced by: '<S3290>/LimitSource'
 */
#define rtCP_LimitSource_Value_bv      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_dil
 * Referenced by: '<S3291>/Constant'
 */
#define rtCP_Constant_Value_dil        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_anj
 * Referenced by: '<S3292>/Constant'
 */
#define rtCP_Constant_Value_anj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mtt
 * Referenced by: '<S3293>/Constant'
 */
#define rtCP_Constant_Value_mtt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mg0
 * Referenced by: '<S3294>/Constant'
 */
#define rtCP_Constant_Value_mg0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oc
 * Referenced by: '<S3295>/Constant'
 */
#define rtCP_Constant_Value_oc         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f0v
 * Referenced by: '<S3296>/Constant'
 */
#define rtCP_Constant_Value_f0v        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hys
 * Referenced by: '<S3297>/Constant'
 */
#define rtCP_Constant_Value_hys        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3287>/Constant'
 */
#define rtCP_Constant_Value_jle        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3287>/Constant1'
 */
#define rtCP_Constant1_Value_pm        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_emt
 * Referenced by: '<S3303>/Constant'
 */
#define rtCP_Constant_Value_emt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_l4u
 * Referenced by: '<S3304>/Constant'
 */
#define rtCP_Constant_Value_l4u        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_om
 * Referenced by: '<S3305>/LimitSource'
 */
#define rtCP_LimitSource_Value_om      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_e5s
 * Referenced by: '<S3306>/Constant'
 */
#define rtCP_Constant_Value_e5s        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_clb
 * Referenced by: '<S3307>/Constant'
 */
#define rtCP_Constant_Value_clb        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ltc
 * Referenced by: '<S3308>/Constant'
 */
#define rtCP_Constant_Value_ltc        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fif
 * Referenced by: '<S3309>/Constant'
 */
#define rtCP_Constant_Value_fif        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gon
 * Referenced by: '<S3310>/Constant'
 */
#define rtCP_Constant_Value_gon        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_e3z
 * Referenced by: '<S3311>/Constant'
 */
#define rtCP_Constant_Value_e3z        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i3s
 * Referenced by: '<S3312>/Constant'
 */
#define rtCP_Constant_Value_i3s        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3302>/Constant'
 */
#define rtCP_Constant_Value_am         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3302>/Constant1'
 */
#define rtCP_Constant1_Value_ja        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mb
 * Referenced by: '<S3316>/Constant'
 */
#define rtCP_Constant_Value_mb         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jew
 * Referenced by: '<S3317>/Constant'
 */
#define rtCP_Constant_Value_jew        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nhn
 * Referenced by: '<S3318>/Constant'
 */
#define rtCP_Constant_Value_nhn        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ia
 * Referenced by: '<S3319>/Constant'
 */
#define rtCP_Constant_Value_ia         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_iah
 * Referenced by: '<S3320>/Constant'
 */
#define rtCP_Constant_Value_iah        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dix
 * Referenced by: '<S3321>/Constant'
 */
#define rtCP_Constant_Value_dix        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_axc
 * Referenced by: '<S3322>/Constant'
 */
#define rtCP_Constant_Value_axc        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3315>/Constant'
 */
#define rtCP_Constant_Value_kws        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3315>/Constant1'
 */
#define rtCP_Constant1_Value_bm        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jh
 * Referenced by: '<S3326>/Constant'
 */
#define rtCP_Constant_Value_jh         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ll
 * Referenced by: '<S3327>/Constant'
 */
#define rtCP_Constant_Value_ll         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jbd
 * Referenced by: '<S3328>/Constant'
 */
#define rtCP_Constant_Value_jbd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jf5
 * Referenced by: '<S3329>/Constant'
 */
#define rtCP_Constant_Value_jf5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ix
 * Referenced by: '<S3330>/Constant'
 */
#define rtCP_Constant_Value_ix         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dn5
 * Referenced by: '<S3331>/Constant'
 */
#define rtCP_Constant_Value_dn5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_j54
 * Referenced by: '<S3332>/Constant'
 */
#define rtCP_Constant_Value_j54        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3325>/Constant'
 */
#define rtCP_Constant_Value_mbf        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3325>/Constant1'
 */
#define rtCP_Constant1_Value_ek        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_chl
 * Referenced by: '<S3336>/Constant'
 */
#define rtCP_Constant_Value_chl        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hvc
 * Referenced by: '<S3337>/Constant'
 */
#define rtCP_Constant_Value_hvc        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gly
 * Referenced by: '<S3338>/Constant'
 */
#define rtCP_Constant_Value_gly        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ka
 * Referenced by: '<S3339>/Constant'
 */
#define rtCP_Constant_Value_ka         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ea3
 * Referenced by: '<S3340>/Constant'
 */
#define rtCP_Constant_Value_ea3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lv
 * Referenced by: '<S3341>/Constant'
 */
#define rtCP_Constant_Value_lv         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mzi
 * Referenced by: '<S3342>/Constant'
 */
#define rtCP_Constant_Value_mzi        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3335>/Constant'
 */
#define rtCP_Constant_Value_gcz        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3335>/Constant1'
 */
#define rtCP_Constant1_Value_kc1       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_h0q
 * Referenced by: '<S3346>/Constant'
 */
#define rtCP_Constant_Value_h0q        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_atp
 * Referenced by: '<S3347>/Constant'
 */
#define rtCP_Constant_Value_atp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fg5
 * Referenced by: '<S3348>/Constant'
 */
#define rtCP_Constant_Value_fg5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lmf
 * Referenced by: '<S3349>/Constant'
 */
#define rtCP_Constant_Value_lmf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_afw
 * Referenced by: '<S3350>/Constant'
 */
#define rtCP_Constant_Value_afw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f0z
 * Referenced by: '<S3351>/Constant'
 */
#define rtCP_Constant_Value_f0z        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cl2
 * Referenced by: '<S3352>/Constant'
 */
#define rtCP_Constant_Value_cl2        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3345>/Constant'
 */
#define rtCP_Constant_Value_hdn        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3345>/Constant1'
 */
#define rtCP_Constant1_Value_i4t       (0.0F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S2924>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value_e (0.01F)

/* Expression: single(pi/2)
 * Referenced by: '<S3358>/Constant'
 */
#define rtCP_Constant_Value_dzn        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S3367>/Constant'
 */
#define rtCP_Constant_Value_bca        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S3376>/Constant'
 */
#define rtCP_Constant_Value_f2         (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S3385>/Constant'
 */
#define rtCP_Constant_Value_eoo        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S3394>/Constant'
 */
#define rtCP_Constant_Value_ety        (1.57079637F)

/* Computed Parameter: rtCP_Constant_Value_iel
 * Referenced by: '<S3854>/Constant'
 */
#define rtCP_Constant_Value_iel        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_o04
 * Referenced by: '<S3855>/Constant'
 */
#define rtCP_Constant_Value_o04        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_hz
 * Referenced by: '<S3856>/LimitSource'
 */
#define rtCP_LimitSource_Value_hz      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_jnp
 * Referenced by: '<S3857>/Constant'
 */
#define rtCP_Constant_Value_jnp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lq0
 * Referenced by: '<S3858>/Constant'
 */
#define rtCP_Constant_Value_lq0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oyv
 * Referenced by: '<S3859>/Constant'
 */
#define rtCP_Constant_Value_oyv        (-0.41F)

/* Computed Parameter: rtCP_Constant_Value_on
 * Referenced by: '<S3860>/Constant'
 */
#define rtCP_Constant_Value_on         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bmq
 * Referenced by: '<S3861>/Constant'
 */
#define rtCP_Constant_Value_bmq        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lqo
 * Referenced by: '<S3862>/Constant'
 */
#define rtCP_Constant_Value_lqo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_c3l
 * Referenced by: '<S3863>/Constant'
 */
#define rtCP_Constant_Value_c3l        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3853>/Constant'
 */
#define rtCP_Constant_Value_avu        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3853>/Constant1'
 */
#define rtCP_Constant1_Value_jpd       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mki
 * Referenced by: '<S3869>/Constant'
 */
#define rtCP_Constant_Value_mki        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ii4
 * Referenced by: '<S3870>/Constant'
 */
#define rtCP_Constant_Value_ii4        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_lt
 * Referenced by: '<S3871>/LimitSource'
 */
#define rtCP_LimitSource_Value_lt      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_fyk
 * Referenced by: '<S3872>/Constant'
 */
#define rtCP_Constant_Value_fyk        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ptt
 * Referenced by: '<S3873>/Constant'
 */
#define rtCP_Constant_Value_ptt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hpx
 * Referenced by: '<S3874>/Constant'
 */
#define rtCP_Constant_Value_hpx        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_eh
 * Referenced by: '<S3875>/Constant'
 */
#define rtCP_Constant_Value_eh         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bpd
 * Referenced by: '<S3876>/Constant'
 */
#define rtCP_Constant_Value_bpd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dss
 * Referenced by: '<S3877>/Constant'
 */
#define rtCP_Constant_Value_dss        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f1z
 * Referenced by: '<S3878>/Constant'
 */
#define rtCP_Constant_Value_f1z        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3868>/Constant'
 */
#define rtCP_Constant_Value_gb2        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3868>/Constant1'
 */
#define rtCP_Constant1_Value_g2        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_db
 * Referenced by: '<S3882>/Constant'
 */
#define rtCP_Constant_Value_db         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_myo
 * Referenced by: '<S3883>/Constant'
 */
#define rtCP_Constant_Value_myo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ar1
 * Referenced by: '<S3884>/Constant'
 */
#define rtCP_Constant_Value_ar1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kww
 * Referenced by: '<S3885>/Constant'
 */
#define rtCP_Constant_Value_kww        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_abg
 * Referenced by: '<S3886>/Constant'
 */
#define rtCP_Constant_Value_abg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_apz
 * Referenced by: '<S3887>/Constant'
 */
#define rtCP_Constant_Value_apz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f3
 * Referenced by: '<S3888>/Constant'
 */
#define rtCP_Constant_Value_f3         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3881>/Constant'
 */
#define rtCP_Constant_Value_cbo        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3881>/Constant1'
 */
#define rtCP_Constant1_Value_in        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_njw
 * Referenced by: '<S3892>/Constant'
 */
#define rtCP_Constant_Value_njw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gf4u
 * Referenced by: '<S3893>/Constant'
 */
#define rtCP_Constant_Value_gf4u       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nxw
 * Referenced by: '<S3894>/Constant'
 */
#define rtCP_Constant_Value_nxw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dn1
 * Referenced by: '<S3895>/Constant'
 */
#define rtCP_Constant_Value_dn1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_k2i
 * Referenced by: '<S3896>/Constant'
 */
#define rtCP_Constant_Value_k2i        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hf
 * Referenced by: '<S3897>/Constant'
 */
#define rtCP_Constant_Value_hf         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bjq
 * Referenced by: '<S3898>/Constant'
 */
#define rtCP_Constant_Value_bjq        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3891>/Constant'
 */
#define rtCP_Constant_Value_bxk        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3891>/Constant1'
 */
#define rtCP_Constant1_Value_ed        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lom
 * Referenced by: '<S3902>/Constant'
 */
#define rtCP_Constant_Value_lom        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cmo
 * Referenced by: '<S3903>/Constant'
 */
#define rtCP_Constant_Value_cmo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dxv
 * Referenced by: '<S3904>/Constant'
 */
#define rtCP_Constant_Value_dxv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_js1
 * Referenced by: '<S3905>/Constant'
 */
#define rtCP_Constant_Value_js1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mtx
 * Referenced by: '<S3906>/Constant'
 */
#define rtCP_Constant_Value_mtx        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pnz
 * Referenced by: '<S3907>/Constant'
 */
#define rtCP_Constant_Value_pnz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_he5
 * Referenced by: '<S3908>/Constant'
 */
#define rtCP_Constant_Value_he5        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3901>/Constant'
 */
#define rtCP_Constant_Value_hgp        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3901>/Constant1'
 */
#define rtCP_Constant1_Value_jd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nuq
 * Referenced by: '<S3912>/Constant'
 */
#define rtCP_Constant_Value_nuq        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kgv
 * Referenced by: '<S3913>/Constant'
 */
#define rtCP_Constant_Value_kgv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hgo
 * Referenced by: '<S3914>/Constant'
 */
#define rtCP_Constant_Value_hgo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dc
 * Referenced by: '<S3915>/Constant'
 */
#define rtCP_Constant_Value_dc         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ljf
 * Referenced by: '<S3916>/Constant'
 */
#define rtCP_Constant_Value_ljf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_j1o
 * Referenced by: '<S3917>/Constant'
 */
#define rtCP_Constant_Value_j1o        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lue
 * Referenced by: '<S3918>/Constant'
 */
#define rtCP_Constant_Value_lue        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3911>/Constant'
 */
#define rtCP_Constant_Value_azt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3911>/Constant1'
 */
#define rtCP_Constant1_Value_jo        (0.0F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S3482>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value_f (0.01F)

/* Expression: single(2)
 * Referenced by: '<S3924>/Constant'
 */
#define rtCP_Constant_Value_lne        (2.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S3933>/Constant'
 */
#define rtCP_Constant_Value_efv        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S3942>/Constant'
 */
#define rtCP_Constant_Value_ibv        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S3951>/Constant'
 */
#define rtCP_Constant_Value_de         (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S3960>/Constant'
 */
#define rtCP_Constant_Value_nkw        (1.57079637F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4060>/Constant5'
 */
#define rtCP_Constant5_Value_iy        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4061>/Constant5'
 */
#define rtCP_Constant5_Value_ld        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_o1q
 * Referenced by: '<S4062>/LimitSource'
 */
#define rtCP_LimitSource_Value_o1q     (1.0E-5F)

/* Expression: single(0)
 * Referenced by: '<S4085>/Constant'
 */
#define rtCP_Constant_Value_lff        (0.0F)

/* Expression: single(0.2)
 * Referenced by: '<S4086>/Constant'
 */
#define rtCP_Constant_Value_oj4        (0.2F)

/* Computed Parameter: rtCP_Constant_Value_asc
 * Referenced by: '<S4168>/Constant'
 */
#define rtCP_Constant_Value_asc        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_afz
 * Referenced by: '<S4169>/Constant'
 */
#define rtCP_Constant_Value_afz        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_gpk
 * Referenced by: '<S4170>/LimitSource'
 */
#define rtCP_LimitSource_Value_gpk     (0.01F)

/* Computed Parameter: rtCP_Constant_Value_kp
 * Referenced by: '<S4177>/Constant'
 */
#define rtCP_Constant_Value_kp         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jxt
 * Referenced by: '<S4178>/Constant'
 */
#define rtCP_Constant_Value_jxt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_feg
 * Referenced by: '<S4179>/Constant'
 */
#define rtCP_Constant_Value_feg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fui
 * Referenced by: '<S4180>/Constant'
 */
#define rtCP_Constant_Value_fui        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mij
 * Referenced by: '<S4257>/Constant'
 */
#define rtCP_Constant_Value_mij        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_p0n
 * Referenced by: '<S4258>/Constant'
 */
#define rtCP_Constant_Value_p0n        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_pi
 * Referenced by: '<S4259>/LimitSource'
 */
#define rtCP_LimitSource_Value_pi      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_iyd
 * Referenced by: '<S4266>/Constant'
 */
#define rtCP_Constant_Value_iyd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kzu
 * Referenced by: '<S4267>/Constant'
 */
#define rtCP_Constant_Value_kzu        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ld0
 * Referenced by: '<S4268>/Constant'
 */
#define rtCP_Constant_Value_ld0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_g3c
 * Referenced by: '<S4269>/Constant'
 */
#define rtCP_Constant_Value_g3c        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_dn
 * Referenced by: '<S4276>/LimitSource'
 */
#define rtCP_LimitSource_Value_dn      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_bx
 * Referenced by: '<S4277>/LimitSource'
 */
#define rtCP_LimitSource_Value_bx      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_hex
 * Referenced by: '<S4278>/Constant'
 */
#define rtCP_Constant_Value_hex        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lx5
 * Referenced by: '<S4279>/Constant'
 */
#define rtCP_Constant_Value_lx5        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_m1a
 * Referenced by: '<S4280>/LimitSource'
 */
#define rtCP_LimitSource_Value_m1a     (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_kl
 * Referenced by: '<S4281>/LimitSource'
 */
#define rtCP_LimitSource_Value_kl      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_bb1
 * Referenced by: '<S4282>/Constant'
 */
#define rtCP_Constant_Value_bb1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hrf
 * Referenced by: '<S4283>/Constant'
 */
#define rtCP_Constant_Value_hrf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f0v1
 * Referenced by: '<S4284>/Constant'
 */
#define rtCP_Constant_Value_f0v1       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jmn
 * Referenced by: '<S4285>/Constant'
 */
#define rtCP_Constant_Value_jmn        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ljo
 * Referenced by: '<S4286>/Constant'
 */
#define rtCP_Constant_Value_ljo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lcj
 * Referenced by: '<S4287>/Constant'
 */
#define rtCP_Constant_Value_lcj        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4094>/Constant1'
 */
#define rtCP_Constant1_Value_lz        (0.0F)

/* Expression: single(0.01)
 * Referenced by: '<S4094>/Constant2'
 */
#define rtCP_Constant2_Value_p4        (0.01F)

/* Expression: single(0)
 * Referenced by: '<S4094>/Constant3'
 */
#define rtCP_Constant3_Value_g4        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4094>/Constant4'
 */
#define rtCP_Constant4_Value_di        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4288>/Constant5'
 */
#define rtCP_Constant5_Value_i2        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4289>/Constant5'
 */
#define rtCP_Constant5_Value_mzv       (1.0E+10F)

/* Expression: single(0.5)
 * Referenced by: '<S4290>/Constant'
 */
#define rtCP_Constant_Value_lkf        (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S4291>/Constant'
 */
#define rtCP_Constant_Value_ehp        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_p5j
 * Referenced by: '<S4299>/Constant'
 */
#define rtCP_Constant_Value_p5j        (1.6F)

/* Computed Parameter: rtCP_Constant_Value_mjn
 * Referenced by: '<S4300>/Constant'
 */
#define rtCP_Constant_Value_mjn        (0.6F)

/* Expression: single(1)
 * Referenced by: '<S4320>/CosHeading'
 */
#define rtCP_CosHeading_Value_m        (1.0F)

/* Expression: single(0.01)
 * Referenced by: '<S4320>/LengthSideLat'
 */
#define rtCP_LengthSideLat_Value_l     (0.01F)

/* Expression: single(0.01)
 * Referenced by: '<S4320>/LengthSideLgt'
 */
#define rtCP_LengthSideLgt_Value_h     (0.01F)

/* Expression: single(0)
 * Referenced by: '<S4320>/RotationAngle'
 */
#define rtCP_RotationAngle_Value_g     (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4320>/SinHeading'
 */
#define rtCP_SinHeading_Value_b        (0.0F)

/* Expression: single(-1)
 * Referenced by: '<S4321>/Constant'
 */
#define rtCP_Constant_Value_i3h        (-1.0F)

/* Expression: single(1)
 * Referenced by: '<S4321>/Constant4'
 */
#define rtCP_Constant4_Value_cs        (1.0F)

/* Expression: single(2)
 * Referenced by: '<S2609>/Constant13'
 */
#define rtCP_Constant13_Value_js       (2.0F)

/* Computed Parameter: rtCP_Constant20_Value_md
 * Referenced by: '<S2609>/Constant20'
 */
#define rtCP_Constant20_Value_md       (1.0F)

/* Expression: single(0)
 * Referenced by: '<S2609>/Constant32'
 */
#define rtCP_Constant32_Value_n        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2609>/Constant33'
 */
#define rtCP_Constant33_Value_o        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2609>/Constant34'
 */
#define rtCP_Constant34_Value_m        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2609>/Constant35'
 */
#define rtCP_Constant35_Value_d        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2609>/Constant36'
 */
#define rtCP_Constant36_Value_f        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2609>/Constant9'
 */
#define rtCP_Constant9_Value_d         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2609>/Constant_2'
 */
#define rtCP_Constant_2_Value_fl       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2609>/Constant_25'
 */
#define rtCP_Constant_25_Value_p       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4309>/Constant4'
 */
#define rtCP_Constant4_Value_no        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4370>/Constant5'
 */
#define rtCP_Constant5_Value_f5        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4371>/Constant5'
 */
#define rtCP_Constant5_Value_al2       (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_jv2
 * Referenced by: '<S4398>/Constant'
 */
#define rtCP_Constant_Value_jv2        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bw3
 * Referenced by: '<S4399>/Constant'
 */
#define rtCP_Constant_Value_bw3        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_k3
 * Referenced by: '<S4400>/LimitSource'
 */
#define rtCP_LimitSource_Value_k3      (0.01F)

/* Computed Parameter: rtCP_Zero_Value_n
 * Referenced by: '<S4391>/Zero'
 */
#define rtCP_Zero_Value_n              (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_f5
 * Referenced by: '<S4379>/Constant3'
 */
#define rtCP_Constant3_Value_f5        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4379>/OffsMinForCllsnRednByBrkgActv1'
 */
#define rtCP_OffsMinForCllsnRednByBrkgActv1_Value_n (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_im
 * Referenced by: '<S4395>/Constant3'
 */
#define rtCP_Constant3_Value_im        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jof
 * Referenced by: '<S4401>/Constant'
 */
#define rtCP_Constant_Value_jof        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cp4
 * Referenced by: '<S4382>/Constant'
 */
#define rtCP_Constant_Value_cp4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_km4
 * Referenced by: '<S4410>/Constant'
 */
#define rtCP_Constant_Value_km4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nua
 * Referenced by: '<S4411>/Constant'
 */
#define rtCP_Constant_Value_nua        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_n04
 * Referenced by: '<S4415>/Constant'
 */
#define rtCP_Constant_Value_n04        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_npl
 * Referenced by: '<S4416>/Constant'
 */
#define rtCP_Constant_Value_npl        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ki3
 * Referenced by: '<S4421>/Constant'
 */
#define rtCP_Constant_Value_ki3        (0.6F)

/* Computed Parameter: rtCP_Constant_Value_hwv
 * Referenced by: '<S4418>/Constant'
 */
#define rtCP_Constant_Value_hwv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hwq
 * Referenced by: '<S4426>/Constant'
 */
#define rtCP_Constant_Value_hwq        (4.0F)

/* Computed Parameter: rtCP_Constant_Value_ir1
 * Referenced by: '<S4427>/Constant'
 */
#define rtCP_Constant_Value_ir1        (0.6F)

/* Computed Parameter: rtCP_Constant_Value_lpv
 * Referenced by: '<S4419>/Constant'
 */
#define rtCP_Constant_Value_lpv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cdo
 * Referenced by: '<S4432>/Constant'
 */
#define rtCP_Constant_Value_cdo        (4.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4434>/Constant5'
 */
#define rtCP_Constant5_Value_fr        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4435>/Constant5'
 */
#define rtCP_Constant5_Value_ep        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_fzb
 * Referenced by: '<S4436>/LimitSource'
 */
#define rtCP_LimitSource_Value_fzb     (1.0E-5F)

/* Computed Parameter: rtCP_Constant_Value_jov
 * Referenced by: '<S4444>/Constant'
 */
#define rtCP_Constant_Value_jov        (0.2F)

/* Computed Parameter: rtCP_Constant_Value_oak
 * Referenced by: '<S4445>/Constant'
 */
#define rtCP_Constant_Value_oak        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_chc
 * Referenced by: '<S4446>/Constant'
 */
#define rtCP_Constant_Value_chc        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_ja0
 * Referenced by: '<S4448>/Constant'
 */
#define rtCP_Constant_Value_ja0        (1.2F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4460>/Constant5'
 */
#define rtCP_Constant5_Value_ji        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4461>/Constant5'
 */
#define rtCP_Constant5_Value_iyi       (1.0E+10F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S4525>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value_p (0.01F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S4525>/LengthSideLgtNoLength1'
 */
#define rtCP_LengthSideLgtNoLength1_Value_l (0.01F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4571>/Constant5'
 */
#define rtCP_Constant5_Value_on        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4572>/Constant5'
 */
#define rtCP_Constant5_Value_po        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_b5
 * Referenced by: '<S4573>/LimitSource'
 */
#define rtCP_LimitSource_Value_b5      (1.0E-5F)

/* Computed Parameter: rtCP_Constant1_Value_dt
 * Referenced by: '<S4593>/Constant1'
 */
#define rtCP_Constant1_Value_dt        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_hx
 * Referenced by: '<S4593>/Constant2'
 */
#define rtCP_Constant2_Value_hx        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_p1
 * Referenced by: '<S4593>/Constant3'
 */
#define rtCP_Constant3_Value_p1        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_a2
 * Referenced by: '<S4593>/Constant4'
 */
#define rtCP_Constant4_Value_a2        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oz2
 * Referenced by: '<S4597>/Constant'
 */
#define rtCP_Constant_Value_oz2        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_gld
 * Referenced by: '<S4594>/Constant1'
 */
#define rtCP_Constant1_Value_gld       (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_lay
 * Referenced by: '<S4594>/Constant2'
 */
#define rtCP_Constant2_Value_lay       (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_p2
 * Referenced by: '<S4594>/Constant3'
 */
#define rtCP_Constant3_Value_p2        (0.0F)

/* Computed Parameter: rtCP_Constant8_Value_ou
 * Referenced by: '<S4594>/Constant8'
 */
#define rtCP_Constant8_Value_ou        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oq4
 * Referenced by: '<S4599>/Constant'
 */
#define rtCP_Constant_Value_oq4        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_eh
 * Referenced by: '<S4595>/Constant1'
 */
#define rtCP_Constant1_Value_eh        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_m4
 * Referenced by: '<S4595>/Constant2'
 */
#define rtCP_Constant2_Value_m4        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_hc
 * Referenced by: '<S4595>/Constant3'
 */
#define rtCP_Constant3_Value_hc        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_ee
 * Referenced by: '<S4595>/Constant4'
 */
#define rtCP_Constant4_Value_ee        (0.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S4613>/Constant_1'
 */
#define rtCP_Constant_1_Value_g        (1.57079637F)

/* Computed Parameter: rtCP_Constant_2_Value_jx
 * Referenced by: '<S4613>/Constant_2'
 */
#define rtCP_Constant_2_Value_jx       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pzq
 * Referenced by: '<S4973>/Constant'
 */
#define rtCP_Constant_Value_pzq        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jyb
 * Referenced by: '<S4974>/Constant'
 */
#define rtCP_Constant_Value_jyb        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_c4
 * Referenced by: '<S4975>/LimitSource'
 */
#define rtCP_LimitSource_Value_c4      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_hch
 * Referenced by: '<S4976>/Constant'
 */
#define rtCP_Constant_Value_hch        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_k0r
 * Referenced by: '<S4977>/Constant'
 */
#define rtCP_Constant_Value_k0r        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oya
 * Referenced by: '<S4978>/Constant'
 */
#define rtCP_Constant_Value_oya        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hxv
 * Referenced by: '<S4979>/Constant'
 */
#define rtCP_Constant_Value_hxv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_iab
 * Referenced by: '<S4980>/Constant'
 */
#define rtCP_Constant_Value_iab        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fo5
 * Referenced by: '<S4981>/Constant'
 */
#define rtCP_Constant_Value_fo5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dlec
 * Referenced by: '<S4982>/Constant'
 */
#define rtCP_Constant_Value_dlec       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4972>/Constant'
 */
#define rtCP_Constant_Value_oim        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4972>/Constant1'
 */
#define rtCP_Constant1_Value_ph        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ckn
 * Referenced by: '<S4988>/Constant'
 */
#define rtCP_Constant_Value_ckn        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cof
 * Referenced by: '<S4989>/Constant'
 */
#define rtCP_Constant_Value_cof        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_cg
 * Referenced by: '<S4990>/LimitSource'
 */
#define rtCP_LimitSource_Value_cg      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_h42
 * Referenced by: '<S4991>/Constant'
 */
#define rtCP_Constant_Value_h42        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jnj
 * Referenced by: '<S4992>/Constant'
 */
#define rtCP_Constant_Value_jnj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ivp
 * Referenced by: '<S4993>/Constant'
 */
#define rtCP_Constant_Value_ivp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cjo
 * Referenced by: '<S4994>/Constant'
 */
#define rtCP_Constant_Value_cjo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dud
 * Referenced by: '<S4995>/Constant'
 */
#define rtCP_Constant_Value_dud        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dod
 * Referenced by: '<S4996>/Constant'
 */
#define rtCP_Constant_Value_dod        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hxu
 * Referenced by: '<S4997>/Constant'
 */
#define rtCP_Constant_Value_hxu        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4987>/Constant'
 */
#define rtCP_Constant_Value_afi        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4987>/Constant1'
 */
#define rtCP_Constant1_Value_lr        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mpj
 * Referenced by: '<S5001>/Constant'
 */
#define rtCP_Constant_Value_mpj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dor
 * Referenced by: '<S5002>/Constant'
 */
#define rtCP_Constant_Value_dor        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ljfz
 * Referenced by: '<S5003>/Constant'
 */
#define rtCP_Constant_Value_ljfz       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_frb
 * Referenced by: '<S5004>/Constant'
 */
#define rtCP_Constant_Value_frb        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_btd
 * Referenced by: '<S5005>/Constant'
 */
#define rtCP_Constant_Value_btd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i03
 * Referenced by: '<S5006>/Constant'
 */
#define rtCP_Constant_Value_i03        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_adv
 * Referenced by: '<S5007>/Constant'
 */
#define rtCP_Constant_Value_adv        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5000>/Constant'
 */
#define rtCP_Constant_Value_p3u        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5000>/Constant1'
 */
#define rtCP_Constant1_Value_mz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_irk
 * Referenced by: '<S5011>/Constant'
 */
#define rtCP_Constant_Value_irk        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jvj
 * Referenced by: '<S5012>/Constant'
 */
#define rtCP_Constant_Value_jvj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ak0
 * Referenced by: '<S5013>/Constant'
 */
#define rtCP_Constant_Value_ak0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_l4h
 * Referenced by: '<S5014>/Constant'
 */
#define rtCP_Constant_Value_l4h        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_eh2
 * Referenced by: '<S5015>/Constant'
 */
#define rtCP_Constant_Value_eh2        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_puf
 * Referenced by: '<S5016>/Constant'
 */
#define rtCP_Constant_Value_puf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fcx
 * Referenced by: '<S5017>/Constant'
 */
#define rtCP_Constant_Value_fcx        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5010>/Constant'
 */
#define rtCP_Constant_Value_kgur       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5010>/Constant1'
 */
#define rtCP_Constant1_Value_euv       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lnhq
 * Referenced by: '<S5021>/Constant'
 */
#define rtCP_Constant_Value_lnhq       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cqd
 * Referenced by: '<S5022>/Constant'
 */
#define rtCP_Constant_Value_cqd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gut
 * Referenced by: '<S5023>/Constant'
 */
#define rtCP_Constant_Value_gut        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aj0
 * Referenced by: '<S5024>/Constant'
 */
#define rtCP_Constant_Value_aj0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i0a
 * Referenced by: '<S5025>/Constant'
 */
#define rtCP_Constant_Value_i0a        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_btj
 * Referenced by: '<S5026>/Constant'
 */
#define rtCP_Constant_Value_btj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i5z
 * Referenced by: '<S5027>/Constant'
 */
#define rtCP_Constant_Value_i5z        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5020>/Constant'
 */
#define rtCP_Constant_Value_ke0        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5020>/Constant1'
 */
#define rtCP_Constant1_Value_gz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lh
 * Referenced by: '<S5031>/Constant'
 */
#define rtCP_Constant_Value_lh         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_j3f
 * Referenced by: '<S5032>/Constant'
 */
#define rtCP_Constant_Value_j3f        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aei
 * Referenced by: '<S5033>/Constant'
 */
#define rtCP_Constant_Value_aei        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nq3
 * Referenced by: '<S5034>/Constant'
 */
#define rtCP_Constant_Value_nq3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cc
 * Referenced by: '<S5035>/Constant'
 */
#define rtCP_Constant_Value_cc         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ca
 * Referenced by: '<S5036>/Constant'
 */
#define rtCP_Constant_Value_ca         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dzip
 * Referenced by: '<S5037>/Constant'
 */
#define rtCP_Constant_Value_dzip       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5030>/Constant'
 */
#define rtCP_Constant_Value_i4m        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5030>/Constant1'
 */
#define rtCP_Constant1_Value_imv       (0.0F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S4609>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value_b (0.01F)

/* Expression: single(pi/2)
 * Referenced by: '<S5043>/Constant'
 */
#define rtCP_Constant_Value_cth        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S5052>/Constant'
 */
#define rtCP_Constant_Value_ns         (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S5061>/Constant'
 */
#define rtCP_Constant_Value_hnk        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S5070>/Constant'
 */
#define rtCP_Constant_Value_bmm        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S5079>/Constant'
 */
#define rtCP_Constant_Value_kwz        (1.57079637F)

/* Computed Parameter: rtCP_Constant_Value_n1i
 * Referenced by: '<S5539>/Constant'
 */
#define rtCP_Constant_Value_n1i        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hzvb
 * Referenced by: '<S5540>/Constant'
 */
#define rtCP_Constant_Value_hzvb       (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_i4
 * Referenced by: '<S5541>/LimitSource'
 */
#define rtCP_LimitSource_Value_i4      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_coo
 * Referenced by: '<S5542>/Constant'
 */
#define rtCP_Constant_Value_coo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gd4
 * Referenced by: '<S5543>/Constant'
 */
#define rtCP_Constant_Value_gd4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pyg
 * Referenced by: '<S5544>/Constant'
 */
#define rtCP_Constant_Value_pyg        (-0.41F)

/* Computed Parameter: rtCP_Constant_Value_arb
 * Referenced by: '<S5545>/Constant'
 */
#define rtCP_Constant_Value_arb        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jtw
 * Referenced by: '<S5546>/Constant'
 */
#define rtCP_Constant_Value_jtw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ib0u
 * Referenced by: '<S5547>/Constant'
 */
#define rtCP_Constant_Value_ib0u       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jva
 * Referenced by: '<S5548>/Constant'
 */
#define rtCP_Constant_Value_jva        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5538>/Constant'
 */
#define rtCP_Constant_Value_chn        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5538>/Constant1'
 */
#define rtCP_Constant1_Value_nt2       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_me4
 * Referenced by: '<S5554>/Constant'
 */
#define rtCP_Constant_Value_me4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lng
 * Referenced by: '<S5555>/Constant'
 */
#define rtCP_Constant_Value_lng        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_bh
 * Referenced by: '<S5556>/LimitSource'
 */
#define rtCP_LimitSource_Value_bh      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ewp
 * Referenced by: '<S5557>/Constant'
 */
#define rtCP_Constant_Value_ewp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jow
 * Referenced by: '<S5558>/Constant'
 */
#define rtCP_Constant_Value_jow        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dfe
 * Referenced by: '<S5559>/Constant'
 */
#define rtCP_Constant_Value_dfe        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ap4
 * Referenced by: '<S5560>/Constant'
 */
#define rtCP_Constant_Value_ap4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gw
 * Referenced by: '<S5561>/Constant'
 */
#define rtCP_Constant_Value_gw         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bsm
 * Referenced by: '<S5562>/Constant'
 */
#define rtCP_Constant_Value_bsm        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_agp
 * Referenced by: '<S5563>/Constant'
 */
#define rtCP_Constant_Value_agp        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5553>/Constant'
 */
#define rtCP_Constant_Value_e4i        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5553>/Constant1'
 */
#define rtCP_Constant1_Value_fl5       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kwwh
 * Referenced by: '<S5567>/Constant'
 */
#define rtCP_Constant_Value_kwwh       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_njf
 * Referenced by: '<S5568>/Constant'
 */
#define rtCP_Constant_Value_njf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nfq
 * Referenced by: '<S5569>/Constant'
 */
#define rtCP_Constant_Value_nfq        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gz
 * Referenced by: '<S5570>/Constant'
 */
#define rtCP_Constant_Value_gz         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fq3
 * Referenced by: '<S5571>/Constant'
 */
#define rtCP_Constant_Value_fq3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dpk
 * Referenced by: '<S5572>/Constant'
 */
#define rtCP_Constant_Value_dpk        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_csv
 * Referenced by: '<S5573>/Constant'
 */
#define rtCP_Constant_Value_csv        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5566>/Constant'
 */
#define rtCP_Constant_Value_eykx       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5566>/Constant1'
 */
#define rtCP_Constant1_Value_e4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dxt
 * Referenced by: '<S5577>/Constant'
 */
#define rtCP_Constant_Value_dxt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ioe
 * Referenced by: '<S5578>/Constant'
 */
#define rtCP_Constant_Value_ioe        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cf
 * Referenced by: '<S5579>/Constant'
 */
#define rtCP_Constant_Value_cf         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dh4
 * Referenced by: '<S5580>/Constant'
 */
#define rtCP_Constant_Value_dh4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nzi
 * Referenced by: '<S5581>/Constant'
 */
#define rtCP_Constant_Value_nzi        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nch
 * Referenced by: '<S5582>/Constant'
 */
#define rtCP_Constant_Value_nch        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kzg
 * Referenced by: '<S5583>/Constant'
 */
#define rtCP_Constant_Value_kzg        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5576>/Constant'
 */
#define rtCP_Constant_Value_lkc        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5576>/Constant1'
 */
#define rtCP_Constant1_Value_oz        (0.0F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S5167>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value_c (0.01F)

/* Expression: single(2)
 * Referenced by: '<S5609>/Constant'
 */
#define rtCP_Constant_Value_afe        (2.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S5618>/Constant'
 */
#define rtCP_Constant_Value_k2n        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S5627>/Constant'
 */
#define rtCP_Constant_Value_hpe        (1.57079637F)

/* Expression: single(0)
 * Referenced by: '<S5770>/Constant'
 */
#define rtCP_Constant_Value_dlp        (0.0F)

/* Expression: single(0.2)
 * Referenced by: '<S5771>/Constant'
 */
#define rtCP_Constant_Value_l3u        (0.2F)

/* Computed Parameter: rtCP_Constant_Value_ezg
 * Referenced by: '<S5853>/Constant'
 */
#define rtCP_Constant_Value_ezg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kfk
 * Referenced by: '<S5854>/Constant'
 */
#define rtCP_Constant_Value_kfk        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ms
 * Referenced by: '<S5855>/LimitSource'
 */
#define rtCP_LimitSource_Value_ms      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ehr
 * Referenced by: '<S5862>/Constant'
 */
#define rtCP_Constant_Value_ehr        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_km0
 * Referenced by: '<S5863>/Constant'
 */
#define rtCP_Constant_Value_km0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_evu
 * Referenced by: '<S5864>/Constant'
 */
#define rtCP_Constant_Value_evu        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jro
 * Referenced by: '<S5865>/Constant'
 */
#define rtCP_Constant_Value_jro        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hu1
 * Referenced by: '<S5942>/Constant'
 */
#define rtCP_Constant_Value_hu1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dhq
 * Referenced by: '<S5943>/Constant'
 */
#define rtCP_Constant_Value_dhq        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_do
 * Referenced by: '<S5944>/LimitSource'
 */
#define rtCP_LimitSource_Value_do      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_fbp
 * Referenced by: '<S5951>/Constant'
 */
#define rtCP_Constant_Value_fbp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fwx
 * Referenced by: '<S5952>/Constant'
 */
#define rtCP_Constant_Value_fwx        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_myj
 * Referenced by: '<S5953>/Constant'
 */
#define rtCP_Constant_Value_myj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hpa
 * Referenced by: '<S5954>/Constant'
 */
#define rtCP_Constant_Value_hpa        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_nj
 * Referenced by: '<S5961>/LimitSource'
 */
#define rtCP_LimitSource_Value_nj      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_b4t
 * Referenced by: '<S5962>/LimitSource'
 */
#define rtCP_LimitSource_Value_b4t     (0.01F)

/* Computed Parameter: rtCP_Constant_Value_iuv
 * Referenced by: '<S5963>/Constant'
 */
#define rtCP_Constant_Value_iuv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_g5
 * Referenced by: '<S5964>/Constant'
 */
#define rtCP_Constant_Value_g5         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_j2
 * Referenced by: '<S5965>/LimitSource'
 */
#define rtCP_LimitSource_Value_j2      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_eg
 * Referenced by: '<S5966>/LimitSource'
 */
#define rtCP_LimitSource_Value_eg      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_doj
 * Referenced by: '<S5967>/Constant'
 */
#define rtCP_Constant_Value_doj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_b5y
 * Referenced by: '<S5968>/Constant'
 */
#define rtCP_Constant_Value_b5y        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fyw
 * Referenced by: '<S5969>/Constant'
 */
#define rtCP_Constant_Value_fyw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gc4
 * Referenced by: '<S5970>/Constant'
 */
#define rtCP_Constant_Value_gc4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ci1
 * Referenced by: '<S5971>/Constant'
 */
#define rtCP_Constant_Value_ci1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i2x
 * Referenced by: '<S5972>/Constant'
 */
#define rtCP_Constant_Value_i2x        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5779>/Constant1'
 */
#define rtCP_Constant1_Value_pa        (0.0F)

/* Expression: single(0.01)
 * Referenced by: '<S5779>/Constant2'
 */
#define rtCP_Constant2_Value_d5        (0.01F)

/* Expression: single(0)
 * Referenced by: '<S5779>/Constant3'
 */
#define rtCP_Constant3_Value_gh        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5779>/Constant4'
 */
#define rtCP_Constant4_Value_ez        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S5973>/Constant5'
 */
#define rtCP_Constant5_Value_fl        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S5974>/Constant5'
 */
#define rtCP_Constant5_Value_ncq       (1.0E+10F)

/* Expression: single(0.5)
 * Referenced by: '<S5975>/Constant'
 */
#define rtCP_Constant_Value_men        (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S5976>/Constant'
 */
#define rtCP_Constant_Value_ot1        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_eji
 * Referenced by: '<S5984>/Constant'
 */
#define rtCP_Constant_Value_eji        (1.6F)

/* Computed Parameter: rtCP_Constant_Value_pss
 * Referenced by: '<S5985>/Constant'
 */
#define rtCP_Constant_Value_pss        (0.6F)

/* Expression: single(0)
 * Referenced by: '<S5988>/Constant'
 */
#define rtCP_Constant_Value_bi4        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5988>/Constant1'
 */
#define rtCP_Constant1_Value_py        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5988>/Constant50'
 */
#define rtCP_Constant50_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5988>/Constant51'
 */
#define rtCP_Constant51_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5988>/Constant52'
 */
#define rtCP_Constant52_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5988>/Constant53'
 */
#define rtCP_Constant53_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5988>/Constant54'
 */
#define rtCP_Constant54_Value          (0.0F)

/* Expression: single(1)
 * Referenced by: '<S5988>/Constant61'
 */
#define rtCP_Constant61_Value          (1.0F)

/* Expression: single(0)
 * Referenced by: '<S5989>/Constant'
 */
#define rtCP_Constant_Value_ntt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5989>/Constant1'
 */
#define rtCP_Constant1_Value_ocb       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5989>/Constant50'
 */
#define rtCP_Constant50_Value_i        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5989>/Constant51'
 */
#define rtCP_Constant51_Value_c        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5989>/Constant52'
 */
#define rtCP_Constant52_Value_l        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5989>/Constant53'
 */
#define rtCP_Constant53_Value_h        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5989>/Constant54'
 */
#define rtCP_Constant54_Value_i        (0.0F)

/* Expression: single(1)
 * Referenced by: '<S5989>/Constant61'
 */
#define rtCP_Constant61_Value_k        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S6019>/Constant'
 */
#define rtCP_Constant_Value_fp4        (1.0F)

/* Expression: single(0)
 * Referenced by: '<S6019>/Constant1'
 */
#define rtCP_Constant1_Value_dl        (0.0F)

/* Expression: single(1)
 * Referenced by: '<S6038>/Constant1'
 */
#define rtCP_Constant1_Value_fe        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S6039>/Constant'
 */
#define rtCP_Constant_Value_lio        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S6061>/Constant1'
 */
#define rtCP_Constant1_Value_f2        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S6062>/Constant'
 */
#define rtCP_Constant_Value_jbb        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S6032>/Constant'
 */
#define rtCP_Constant_Value_erj        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S6033>/Constant'
 */
#define rtCP_Constant_Value_hi         (1.0F)

/* Computed Parameter: rtCP_Constant_Value_e4j
 * Referenced by: '<S6100>/Constant'
 */
#define rtCP_Constant_Value_e4j        (12.0F)

/* Computed Parameter: rtCP_Constant_Value_c2k
 * Referenced by: '<S6101>/Constant'
 */
#define rtCP_Constant_Value_c2k        (3.0F)

/* Computed Parameter: rtCP_Constant_Value_jbr
 * Referenced by: '<S6102>/Constant'
 */
#define rtCP_Constant_Value_jbr        (15.0F)

/* Computed Parameter: rtCP_Constant_Value_iqz
 * Referenced by: '<S6104>/Constant'
 */
#define rtCP_Constant_Value_iqz        (5.0F)

/* Expression: single(0)
 * Referenced by: '<S6113>/Constant3'
 */
#define rtCP_Constant3_Value_gb        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6114>/Constant3'
 */
#define rtCP_Constant3_Value_il        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6115>/Constant3'
 */
#define rtCP_Constant3_Value_kzr       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6116>/Constant3'
 */
#define rtCP_Constant3_Value_k1        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6117>/Constant3'
 */
#define rtCP_Constant3_Value_lu        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6118>/Constant3'
 */
#define rtCP_Constant3_Value_nd        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6119>/Constant3'
 */
#define rtCP_Constant3_Value_l1        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6120>/Constant3'
 */
#define rtCP_Constant3_Value_p1n       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_l5g
 * Referenced by: '<S6123>/Constant'
 */
#define rtCP_Constant_Value_l5g        (0.1F)

/* Expression: single(0)
 * Referenced by: '<S6136>/Constant3'
 */
#define rtCP_Constant3_Value_jm        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ilp
 * Referenced by: '<S6140>/Constant'
 */
#define rtCP_Constant_Value_ilp        (0.0F)

/* Expression: const
 * Referenced by: '<S6141>/Constant'
 */
#define rtCP_Constant_Value_menc       (15.0F)

/* Expression: const
 * Referenced by: '<S6142>/Constant'
 */
#define rtCP_Constant_Value_iju        (10.0F)

/* Expression: const
 * Referenced by: '<S6143>/Constant'
 */
#define rtCP_Constant_Value_mcp        (-15.0F)

/* Computed Parameter: rtCP_Constant_Value_b03
 * Referenced by: '<S6159>/Constant'
 */
#define rtCP_Constant_Value_b03        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6006>/Constant3'
 */
#define rtCP_Constant3_Value_bg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ev3
 * Referenced by: '<S6167>/Constant'
 */
#define rtCP_Constant_Value_ev3        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ne
 * Referenced by: '<S6166>/Constant1'
 */
#define rtCP_Constant1_Value_ne        (0.0F)

/* Expression: const
 * Referenced by: '<S6180>/Constant'
 */
#define rtCP_Constant_Value_exk        (8.0F)

/* Expression: const
 * Referenced by: '<S6181>/Constant'
 */
#define rtCP_Constant_Value_je5        (4.0F)

/* Expression: const
 * Referenced by: '<S6182>/Constant'
 */
#define rtCP_Constant_Value_ps2        (8.0F)

/* Expression: const
 * Referenced by: '<S6183>/Constant'
 */
#define rtCP_Constant_Value_ej0        (4.0F)

/* Expression: const
 * Referenced by: '<S6184>/Constant'
 */
#define rtCP_Constant_Value_bnv        (8.0F)

/* Expression: const
 * Referenced by: '<S6185>/Constant'
 */
#define rtCP_Constant_Value_kda        (4.0F)

/* Expression: const
 * Referenced by: '<S6186>/Constant'
 */
#define rtCP_Constant_Value_dhp        (8.0F)

/* Expression: const
 * Referenced by: '<S6187>/Constant'
 */
#define rtCP_Constant_Value_bsf        (4.0F)

/* Expression: const
 * Referenced by: '<S6188>/Constant'
 */
#define rtCP_Constant_Value_nud        (8.0F)

/* Expression: const
 * Referenced by: '<S6189>/Constant'
 */
#define rtCP_Constant_Value_hff        (4.0F)

/* Expression: const
 * Referenced by: '<S6190>/Constant'
 */
#define rtCP_Constant_Value_dz2        (8.0F)

/* Expression: const
 * Referenced by: '<S6191>/Constant'
 */
#define rtCP_Constant_Value_k5r        (4.0F)

/* Computed Parameter: rtCP_Constant_Value_fih
 * Referenced by: '<S6214>/Constant'
 */
#define rtCP_Constant_Value_fih        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_mit
 * Referenced by: '<S6213>/Constant1'
 */
#define rtCP_Constant1_Value_mit       (0.0F)

/* Expression: const
 * Referenced by: '<S6227>/Constant'
 */
#define rtCP_Constant_Value_efr        (8.0F)

/* Expression: const
 * Referenced by: '<S6228>/Constant'
 */
#define rtCP_Constant_Value_crx        (4.0F)

/* Expression: const
 * Referenced by: '<S6229>/Constant'
 */
#define rtCP_Constant_Value_kkr        (8.0F)

/* Expression: const
 * Referenced by: '<S6230>/Constant'
 */
#define rtCP_Constant_Value_mge        (4.0F)

/* Expression: const
 * Referenced by: '<S6231>/Constant'
 */
#define rtCP_Constant_Value_gi3        (8.0F)

/* Expression: const
 * Referenced by: '<S6232>/Constant'
 */
#define rtCP_Constant_Value_fcd        (4.0F)

/* Expression: const
 * Referenced by: '<S6233>/Constant'
 */
#define rtCP_Constant_Value_irl        (8.0F)

/* Expression: const
 * Referenced by: '<S6234>/Constant'
 */
#define rtCP_Constant_Value_ikvv       (4.0F)

/* Expression: const
 * Referenced by: '<S6235>/Constant'
 */
#define rtCP_Constant_Value_kt         (8.0F)

/* Expression: const
 * Referenced by: '<S6236>/Constant'
 */
#define rtCP_Constant_Value_n0y        (4.0F)

/* Expression: const
 * Referenced by: '<S6237>/Constant'
 */
#define rtCP_Constant_Value_hbx        (8.0F)

/* Expression: const
 * Referenced by: '<S6238>/Constant'
 */
#define rtCP_Constant_Value_apr        (4.0F)

/* Computed Parameter: rtCP_Constant_Value_mq3
 * Referenced by: '<S6255>/Constant'
 */
#define rtCP_Constant_Value_mq3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_eu1
 * Referenced by: '<S6256>/Constant'
 */
#define rtCP_Constant_Value_eu1        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2614>/Constant1'
 */
#define rtCP_Constant1_Value_nvl       (0.0F)

/* Expression: single(1)
 * Referenced by: '<S2614>/Constant11'
 */
#define rtCP_Constant11_Value_kx       (1.0F)

/* Expression: single(0)
 * Referenced by: '<S2615>/Constant7'
 */
#define rtCP_Constant7_Value_a4        (0.0F)

/* Computed Parameter: rtCP_Constant29_Value_d
 * Referenced by: '<S6>/Constant29'
 */
#define rtCP_Constant29_Value_d        (0.0F)

/* Computed Parameter: rtCP_Constant31_Value
 * Referenced by: '<S6>/Constant31'
 */
#define rtCP_Constant31_Value          (0.0F)

/* Computed Parameter: rtCP_Constant39_Value
 * Referenced by: '<S6>/Constant39'
 */
#define rtCP_Constant39_Value          (0.0F)

/* Computed Parameter: rtCP_Constant42_Value
 * Referenced by: '<S6>/Constant42'
 */
#define rtCP_Constant42_Value          (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fvs
 * Referenced by: '<S6323>/Constant'
 */
#define rtCP_Constant_Value_fvs        (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_jg
 * Referenced by: '<S6323>/Constant2'
 */
#define rtCP_Constant2_Value_jg        (-1.0F)

/* Expression: single(0)
 * Referenced by: '<S6336>/Constant'
 */
#define rtCP_Constant_Value_pef        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6345>/Constant'
 */
#define rtCP_Constant_Value_d0h        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6345>/Constant3'
 */
#define rtCP_Constant3_Value_g2        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6348>/Constant3'
 */
#define rtCP_Constant3_Value_hj        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S6337>/Constant'
 */
#define rtCP_Constant_Value_kdh        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6337>/Constant20'
 */
#define rtCP_Constant20_Value_j        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6337>/Constant21'
 */
#define rtCP_Constant21_Value_g        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6337>/Constant22'
 */
#define rtCP_Constant22_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6337>/Constant24'
 */
#define rtCP_Constant24_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6337>/Constant9'
 */
#define rtCP_Constant9_Value_n         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6338>/Constant30'
 */
#define rtCP_Constant30_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6338>/Constant31'
 */
#define rtCP_Constant31_Value_m        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6338>/Constant32'
 */
#define rtCP_Constant32_Value_j        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6338>/Constant5'
 */
#define rtCP_Constant5_Value_jt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6338>/Constant6'
 */
#define rtCP_Constant6_Value_j         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6436>/Constant3'
 */
#define rtCP_Constant3_Value_bti       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6437>/Constant3'
 */
#define rtCP_Constant3_Value_io        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6438>/Constant3'
 */
#define rtCP_Constant3_Value_gr        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6439>/Constant3'
 */
#define rtCP_Constant3_Value_dx        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6440>/Constant3'
 */
#define rtCP_Constant3_Value_m         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6441>/Constant3'
 */
#define rtCP_Constant3_Value_ff        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6442>/Constant3'
 */
#define rtCP_Constant3_Value_kc        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6443>/Constant3'
 */
#define rtCP_Constant3_Value_at        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6444>/Constant3'
 */
#define rtCP_Constant3_Value_oz        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6445>/Constant3'
 */
#define rtCP_Constant3_Value_ob        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6446>/Constant3'
 */
#define rtCP_Constant3_Value_hw        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6447>/Constant3'
 */
#define rtCP_Constant3_Value_m3        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6448>/Constant3'
 */
#define rtCP_Constant3_Value_oo        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6449>/Constant3'
 */
#define rtCP_Constant3_Value_hs        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6450>/Constant3'
 */
#define rtCP_Constant3_Value_nl        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6451>/Constant3'
 */
#define rtCP_Constant3_Value_p2i       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6452>/Constant3'
 */
#define rtCP_Constant3_Value_kgx       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6453>/Constant3'
 */
#define rtCP_Constant3_Value_h5        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6454>/Constant3'
 */
#define rtCP_Constant3_Value_p3z       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6455>/Constant3'
 */
#define rtCP_Constant3_Value_gq        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6456>/Constant3'
 */
#define rtCP_Constant3_Value_jx        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6457>/Constant3'
 */
#define rtCP_Constant3_Value_or        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6473>/Constant3'
 */
#define rtCP_Constant3_Value_df        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6474>/Constant3'
 */
#define rtCP_Constant3_Value_iy        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6475>/Constant3'
 */
#define rtCP_Constant3_Value_nq        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6476>/Constant3'
 */
#define rtCP_Constant3_Value_m4        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6477>/Constant3'
 */
#define rtCP_Constant3_Value_e         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6478>/Constant3'
 */
#define rtCP_Constant3_Value_fa        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6479>/Constant3'
 */
#define rtCP_Constant3_Value_cw        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6480>/Constant3'
 */
#define rtCP_Constant3_Value_ip        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6482>/Constant3'
 */
#define rtCP_Constant3_Value_dfg       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6483>/Constant3'
 */
#define rtCP_Constant3_Value_b0        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6484>/Constant3'
 */
#define rtCP_Constant3_Value_kt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6481>/Constant3'
 */
#define rtCP_Constant3_Value_cd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oia
 * Referenced by: '<S6495>/Constant'
 */
#define rtCP_Constant_Value_oia        (2.0F)

/* Computed Parameter: rtCP_Constant_Value_dbv
 * Referenced by: '<S6510>/Constant'
 */
#define rtCP_Constant_Value_dbv        (3.0F)

/* Computed Parameter: rtCP_Constant_Value_ex5
 * Referenced by: '<S6511>/Constant'
 */
#define rtCP_Constant_Value_ex5        (0.5F)

/* Expression: single(0)
 * Referenced by: '<S6512>/Constant3'
 */
#define rtCP_Constant3_Value_nv        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6498>/Constant3'
 */
#define rtCP_Constant3_Value_er        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6499>/Constant3'
 */
#define rtCP_Constant3_Value_jh        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6500>/Constant3'
 */
#define rtCP_Constant3_Value_pxo       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6501>/Constant3'
 */
#define rtCP_Constant3_Value_k5        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6502>/Constant3'
 */
#define rtCP_Constant3_Value_if        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6503>/Constant3'
 */
#define rtCP_Constant3_Value_n1        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6504>/Constant3'
 */
#define rtCP_Constant3_Value_gn        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6505>/Constant3'
 */
#define rtCP_Constant3_Value_i1        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6506>/Constant3'
 */
#define rtCP_Constant3_Value_be        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6507>/Constant3'
 */
#define rtCP_Constant3_Value_gg        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6508>/Constant3'
 */
#define rtCP_Constant3_Value_fn        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6509>/Constant3'
 */
#define rtCP_Constant3_Value_jt        (0.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_n
 * Referenced by: '<S6032>/Saturation'
 */
#define rtCP_Saturation_UpperSat_n     (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_oe
 * Referenced by: '<S6032>/Saturation'
 */
#define rtCP_Saturation_LowerSat_oe    (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_gvl
 * Referenced by: '<S6004>/Gain'
 */
#define rtCP_Gain_Gain_gvl             (0.5F)

/* Expression: single(pi/180)
 * Referenced by: '<S6002>/Gain'
 */
#define rtCP_Gain_Gain_nz              (0.0174532924F)

/* Expression: single(0.3)
 * Referenced by: '<S6019>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_i    (0.3F)

/* Expression: single(-0.3)
 * Referenced by: '<S6019>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_bn   (-0.3F)

/* Computed Parameter: rtCP_Saturation_UpperSat_l4
 * Referenced by: '<S6033>/Saturation'
 */
#define rtCP_Saturation_UpperSat_l4    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_hs
 * Referenced by: '<S6033>/Saturation'
 */
#define rtCP_Saturation_LowerSat_hs    (0.0F)

/* Expression: single(pi/180)
 * Referenced by: '<S6002>/Gain1'
 */
#define rtCP_Gain1_Gain_nu             (0.0174532924F)

/* Expression: single(0.3)
 * Referenced by: '<S6019>/Saturation2'
 */
#define rtCP_Saturation2_UpperSat      (0.3F)

/* Expression: single(-0.3)
 * Referenced by: '<S6019>/Saturation2'
 */
#define rtCP_Saturation2_LowerSat      (-0.3F)

/* Expression: single(180)
 * Referenced by: '<S6088>/Gain1'
 */
#define rtCP_Gain1_Gain_mi             (180.0F)

/* Expression: single(180)
 * Referenced by: '<S6088>/Gain'
 */
#define rtCP_Gain_Gain_bn4             (180.0F)

/* Expression: single(180)
 * Referenced by: '<S6090>/Gain'
 */
#define rtCP_Gain_Gain_cl              (180.0F)

/* Expression: single(180)
 * Referenced by: '<S6090>/Gain1'
 */
#define rtCP_Gain1_Gain_pz             (180.0F)

/* Computed Parameter: rtCP_Switch2_Threshold
 * Referenced by: '<S2636>/Switch2'
 */
#define rtCP_Switch2_Threshold         (2.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_e2
 * Referenced by: '<S4094>/Gain_1'
 */
#define rtCP_Gain_1_Gain_e2            (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_iw
 * Referenced by: '<S4094>/Gain_2'
 */
#define rtCP_Gain_2_Gain_iw            (-1.0F)

/* Expression: single(0.1)
 * Referenced by: '<S902>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_cj   (0.1F)

/* Expression: single(0.5)
 * Referenced by: '<S906>/Gain_2'
 */
#define rtCP_Gain_2_Gain_g5            (0.5F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput_i
 * Referenced by: '<S903>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput_i
 * Referenced by: '<S903>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput_i
 * Referenced by: '<S903>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput_i
 * Referenced by: '<S903>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput_i (0.0F)

/* Expression: single(0.1)
 * Referenced by: '<S928>/Saturation'
 */
#define rtCP_Saturation_LowerSat_eq    (0.1F)

/* Computed Parameter: rtCP_Time_Gain
 * Referenced by: '<S929>/Time'
 */
#define rtCP_Time_Gain                 (4.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_ee
 * Referenced by: '<S823>/Saturation'
 */
#define rtCP_Saturation_UpperSat_ee    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_m
 * Referenced by: '<S823>/Saturation'
 */
#define rtCP_Saturation_LowerSat_m     (0.0F)

/* Expression: single(0.1)
 * Referenced by: '<S814>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_e    (0.1F)

/* Expression: single(-0.1)
 * Referenced by: '<S814>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_cx   (-0.1F)

/* Computed Parameter: rtCP_Saturation_UpperSat_mv
 * Referenced by: '<S824>/Saturation'
 */
#define rtCP_Saturation_UpperSat_mv    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_n2
 * Referenced by: '<S824>/Saturation'
 */
#define rtCP_Saturation_LowerSat_n2    (0.0F)

/* Expression: single(0.1)
 * Referenced by: '<S814>/Saturation'
 */
#define rtCP_Saturation_UpperSat_ea    (0.1F)

/* Expression: single(-0.1)
 * Referenced by: '<S814>/Saturation'
 */
#define rtCP_Saturation_LowerSat_lm    (-0.1F)

/* Expression: single(3.6)
 * Referenced by: '<S1053>/Gain'
 */
#define rtCP_Gain_Gain_fnf             (3.6F)

/* Expression: single(180/pi)
 * Referenced by: '<S1056>/Gain2'
 */
#define rtCP_Gain2_Gain_ca             (57.2957802F)

/* Computed Parameter: rtCP_Gain_Gain_kum
 * Referenced by: '<S1056>/Gain'
 */
#define rtCP_Gain_Gain_kum             (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_pv
 * Referenced by: '<S1056>/Gain1'
 */
#define rtCP_Gain1_Gain_pv             (0.5F)

/* Computed Parameter: rtCP_Switch_Threshold
 * Referenced by: '<S1056>/Switch'
 */
#define rtCP_Switch_Threshold          (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_lg
 * Referenced by: '<S2734>/Gain1'
 */
#define rtCP_Gain1_Gain_lg             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_ib
 * Referenced by: '<S2734>/Gain'
 */
#define rtCP_Gain_Gain_ib              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_bt
 * Referenced by: '<S2733>/Gain1'
 */
#define rtCP_Gain1_Gain_bt             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_lsn
 * Referenced by: '<S2733>/Gain'
 */
#define rtCP_Gain_Gain_lsn             (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_pvi
 * Referenced by: '<S2731>/Gain1'
 */
#define rtCP_Gain1_Gain_pvi            (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ob
 * Referenced by: '<S2731>/Gain2'
 */
#define rtCP_Gain2_Gain_ob             (0.5F)

/* Computed Parameter: rtCP_Gain3_Gain_o
 * Referenced by: '<S2731>/Gain3'
 */
#define rtCP_Gain3_Gain_o              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_hi
 * Referenced by: '<S2731>/Gain'
 */
#define rtCP_Gain_Gain_hi              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_b4
 * Referenced by: '<S2730>/Gain1'
 */
#define rtCP_Gain1_Gain_b4             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_dk
 * Referenced by: '<S2730>/Gain2'
 */
#define rtCP_Gain2_Gain_dk             (0.5F)

/* Computed Parameter: rtCP_Gain3_Gain_c
 * Referenced by: '<S2730>/Gain3'
 */
#define rtCP_Gain3_Gain_c              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_ix
 * Referenced by: '<S2730>/Gain'
 */
#define rtCP_Gain_Gain_ix              (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_os
 * Referenced by: '<S2697>/Gain2'
 */
#define rtCP_Gain2_Gain_os             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_o0
 * Referenced by: '<S2697>/Gain'
 */
#define rtCP_Gain_Gain_o0              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_a5
 * Referenced by: '<S2697>/Gain1'
 */
#define rtCP_Gain1_Gain_a5             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_d5
 * Referenced by: '<S2695>/Gain2'
 */
#define rtCP_Gain2_Gain_d5             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_la
 * Referenced by: '<S2695>/Gain'
 */
#define rtCP_Gain_Gain_la              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_jv
 * Referenced by: '<S2711>/Gain'
 */
#define rtCP_Gain_Gain_jv              (0.5F)

/* Computed Parameter: rtCP_Gain_1_Gain_p1
 * Referenced by: '<S2748>/Gain_1'
 */
#define rtCP_Gain_1_Gain_p1            (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_cn
 * Referenced by: '<S2696>/Gain1'
 */
#define rtCP_Gain1_Gain_cn             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_bgd
 * Referenced by: '<S1222>/Gain'
 */
#define rtCP_Gain_Gain_bgd             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_n42
 * Referenced by: '<S1223>/Gain'
 */
#define rtCP_Gain_Gain_n42             (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_lu
 * Referenced by: '<S1225>/Gain1'
 */
#define rtCP_Gain1_Gain_lu             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_bx
 * Referenced by: '<S1225>/Gain2'
 */
#define rtCP_Gain2_Gain_bx             (0.5F)

/* Expression: single(180/pi)
 * Referenced by: '<S1327>/Gain1'
 */
#define rtCP_Gain1_Gain_nf             (57.2957802F)

/* Expression: single(180/pi)
 * Referenced by: '<S1327>/Gain2'
 */
#define rtCP_Gain2_Gain_e0             (57.2957802F)

/* Computed Parameter: rtCP_Gain_Gain_bfu
 * Referenced by: '<S1215>/Gain'
 */
#define rtCP_Gain_Gain_bfu             (57.2957802F)

/* Computed Parameter: rtCP_Gain1_Gain_l4
 * Referenced by: '<S1215>/Gain1'
 */
#define rtCP_Gain1_Gain_l4             (57.2957802F)

/* Computed Parameter: rtCP_Switch2_Threshold_o
 * Referenced by: '<S4321>/Switch2'
 */
#define rtCP_Switch2_Threshold_o       (2.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_pl
 * Referenced by: '<S5779>/Gain_1'
 */
#define rtCP_Gain_1_Gain_pl            (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_jm
 * Referenced by: '<S5779>/Gain_2'
 */
#define rtCP_Gain_2_Gain_jm            (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ae
 * Referenced by: '<S4411>/Gain1'
 */
#define rtCP_Gain1_Gain_ae             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_j0
 * Referenced by: '<S4411>/Gain'
 */
#define rtCP_Gain_Gain_j0              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_nj
 * Referenced by: '<S4410>/Gain1'
 */
#define rtCP_Gain1_Gain_nj             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_k2
 * Referenced by: '<S4410>/Gain2'
 */
#define rtCP_Gain2_Gain_k2             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_cxi
 * Referenced by: '<S4410>/Gain'
 */
#define rtCP_Gain_Gain_cxi             (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_hh
 * Referenced by: '<S4419>/Gain1'
 */
#define rtCP_Gain1_Gain_hh             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_fx
 * Referenced by: '<S4419>/Gain'
 */
#define rtCP_Gain_Gain_fx              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_e2m
 * Referenced by: '<S4418>/Gain1'
 */
#define rtCP_Gain1_Gain_e2m            (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_pz
 * Referenced by: '<S4418>/Gain'
 */
#define rtCP_Gain_Gain_pz              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_ke
 * Referenced by: '<S4416>/Gain1'
 */
#define rtCP_Gain1_Gain_ke             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ob0
 * Referenced by: '<S4416>/Gain2'
 */
#define rtCP_Gain2_Gain_ob0            (0.5F)

/* Computed Parameter: rtCP_Gain3_Gain_a
 * Referenced by: '<S4416>/Gain3'
 */
#define rtCP_Gain3_Gain_a              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_ne
 * Referenced by: '<S4416>/Gain'
 */
#define rtCP_Gain_Gain_ne              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_jb
 * Referenced by: '<S4415>/Gain1'
 */
#define rtCP_Gain1_Gain_jb             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_bt
 * Referenced by: '<S4415>/Gain2'
 */
#define rtCP_Gain2_Gain_bt             (0.5F)

/* Computed Parameter: rtCP_Gain3_Gain_d
 * Referenced by: '<S4415>/Gain3'
 */
#define rtCP_Gain3_Gain_d              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_k4s
 * Referenced by: '<S4415>/Gain'
 */
#define rtCP_Gain_Gain_k4s             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_iu
 * Referenced by: '<S4382>/Gain2'
 */
#define rtCP_Gain2_Gain_iu             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_jw3
 * Referenced by: '<S4382>/Gain'
 */
#define rtCP_Gain_Gain_jw3             (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_de
 * Referenced by: '<S4382>/Gain1'
 */
#define rtCP_Gain1_Gain_de             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_org
 * Referenced by: '<S4396>/Gain'
 */
#define rtCP_Gain_Gain_org             (0.5F)

/* Computed Parameter: rtCP_Gain_1_Gain_f5
 * Referenced by: '<S4433>/Gain_1'
 */
#define rtCP_Gain_1_Gain_f5            (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_fdf
 * Referenced by: '<S2247>/Gain'
 */
#define rtCP_Gain_Gain_fdf             (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_a1
 * Referenced by: '<S2096>/Gain1'
 */
#define rtCP_Gain1_Gain_a1             (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_nh
 * Referenced by: '<S2097>/Gain1'
 */
#define rtCP_Gain1_Gain_nh             (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ab
 * Referenced by: '<S2099>/Gain1'
 */
#define rtCP_Gain1_Gain_ab             (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_bl
 * Referenced by: '<S2100>/Gain1'
 */
#define rtCP_Gain1_Gain_bl             (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ka
 * Referenced by: '<S2091>/Gain1'
 */
#define rtCP_Gain1_Gain_ka             (-1.0F)

/* Expression: single(0.001)
 * Referenced by: '<S2111>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_l    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_f2
 * Referenced by: '<S2111>/Saturation'
 */
#define rtCP_Saturation_UpperSat_f2    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_jq
 * Referenced by: '<S2111>/Saturation'
 */
#define rtCP_Saturation_LowerSat_jq    (0.0F)

/* Expression: single(1.03)
 * Referenced by: '<S2087>/Gain'
 */
#define rtCP_Gain_Gain_flk             (1.03F)

/* Computed Parameter: rtCP_Saturation_UpperSat_hu
 * Referenced by: '<S1204>/Saturation'
 */
#define rtCP_Saturation_UpperSat_hu    (0.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_ky
 * Referenced by: '<S1142>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_ky (8.64E+7F)

/* Computed Parameter: rtCP_Saturation1_LowerSat_e
 * Referenced by: '<S1151>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_e    (0.0F)

/* Computed Parameter: rtCP_Saturation2_LowerSat_h
 * Referenced by: '<S1151>/Saturation2'
 */
#define rtCP_Saturation2_LowerSat_h    (0.0F)

/* Computed Parameter: rtCP_Saturation1_LowerSat_no
 * Referenced by: '<S1150>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_no   (0.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_pg
 * Referenced by: '<S1150>/Saturation'
 */
#define rtCP_Saturation_LowerSat_pg    (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_og
 * Referenced by: '<S2158>/Gain'
 */
#define rtCP_Gain_Gain_og              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_it3
 * Referenced by: '<S2237>/Gain'
 */
#define rtCP_Gain_Gain_it3             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_fsg
 * Referenced by: '<S2190>/Gain'
 */
#define rtCP_Gain_Gain_fsg             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_if0
 * Referenced by: '<S2280>/Gain'
 */
#define rtCP_Gain_Gain_if0             (2.0F)

/* Expression: single(0.001)
 * Referenced by: '<S2288>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_np   (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_eq
 * Referenced by: '<S2288>/Saturation'
 */
#define rtCP_Saturation_UpperSat_eq    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_og
 * Referenced by: '<S2288>/Saturation'
 */
#define rtCP_Saturation_LowerSat_og    (0.0F)

/* Computed Parameter: rtCP_Sat_3_UpperSat
 * Referenced by: '<S2020>/Sat_3'
 */
#define rtCP_Sat_3_UpperSat            (0.0F)

/* Computed Parameter: rtCP_Sat_4_UpperSat
 * Referenced by: '<S2020>/Sat_4'
 */
#define rtCP_Sat_4_UpperSat            (0.0F)

/* Computed Parameter: rtCP_Sat_3_UpperSat_d
 * Referenced by: '<S2320>/Sat_3'
 */
#define rtCP_Sat_3_UpperSat_d          (0.0F)

/* Computed Parameter: rtCP_Sat_4_UpperSat_g
 * Referenced by: '<S2320>/Sat_4'
 */
#define rtCP_Sat_4_UpperSat_g          (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_as
 * Referenced by: '<S463>/Gain'
 */
#define rtCP_Gain_Gain_as              (-1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_gf
 * Referenced by: '<S725>/Saturation'
 */
#define rtCP_Saturation_LowerSat_gf    (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_m3
 * Referenced by: '<S768>/Gain'
 */
#define rtCP_Gain_Gain_m3              (3.6F)

/* Expression: single(pi/2-0.01)
 * Referenced by: '<S751>/Saturation'
 */
#define rtCP_Saturation_UpperSat_g5    (1.56079638F)

/* Expression: -single(pi/2-0.01)
 * Referenced by: '<S751>/Saturation'
 */
#define rtCP_Saturation_LowerSat_lj    (-1.56079638F)

/* Computed Parameter: rtCP_Gain_Gain_hsk
 * Referenced by: '<S763>/Gain'
 */
#define rtCP_Gain_Gain_hsk             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_ap
 * Referenced by: '<S764>/Gain'
 */
#define rtCP_Gain_Gain_ap              (0.5F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_e
 * Referenced by: '<S765>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_e (8.64E+7F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_et
 * Referenced by: '<S767>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_et (8.64E+7F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_l
 * Referenced by: '<S750>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_l (8.64E+7F)

/* Expression: CMBB_CrvtAbsltMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/CurvatureAbsltMaxThreshold'
 */
#define rtCP_CurvatureAbsltMaxThreshold_UpperSat (0.2F)

/* Expression: CMBB_CrvtAbsltMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/CurvatureAbsltMaxThreshold'
 */
#define rtCP_CurvatureAbsltMaxThreshold_LowerSat (0.0F)

/* Expression: CMBB_CrvtRateAbsltMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/CurvatureRateAbsltMaxThreshold'
 */
#define rtCP_CurvatureRateAbsltMaxThreshold_UpperSat (2.0F)

/* Expression: CMBB_CrvtRateAbsltMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/CurvatureRateAbsltMaxThreshold'
 */
#define rtCP_CurvatureRateAbsltMaxThreshold_LowerSat (0.0F)

/* Expression: CMBB_APosMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/ALatAbsltMaxThreshold'
 */
#define rtCP_ALatAbsltMaxThreshold_UpperSat (10.0F)

/* Expression: CMBB_ALatMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/ALatAbsltMaxThreshold'
 */
#define rtCP_ALatAbsltMaxThreshold_LowerSat (1.0F)

/* Computed Parameter: rtCP_Gain_Gain_fqs
 * Referenced by: '<S660>/Gain'
 */
#define rtCP_Gain_Gain_fqs             (3.6F)

/* Expression: CMBB_JerkNegMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/JerkLgtNegMinThreshold'
 */
#define rtCP_JerkLgtNegMinThreshold_UpperSat (10.0F)

/* Expression: CMBB_JerkNegMinInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/JerkLgtNegMinThreshold'
 */
#define rtCP_JerkLgtNegMinThreshold_LowerSat (-22.0F)

/* Expression: CMBB_CrvtAbsltMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/CurvatureAbsltCmftThreshold'
 */
#define rtCP_CurvatureAbsltCmftThreshold_UpperSat (0.2F)

/* Expression: CMBB_CrvtAbsltMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/CurvatureAbsltCmftThreshold'
 */
#define rtCP_CurvatureAbsltCmftThreshold_LowerSat (0.0F)

/* Expression: CMBB_CrvtRateAbsltMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/CurvatureRateAbsltCmftThreshold'
 */
#define rtCP_CurvatureRateAbsltCmftThreshold_UpperSat (2.0F)

/* Expression: CMBB_CrvtRateAbsltMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/CurvatureRateAbsltCmftThreshold'
 */
#define rtCP_CurvatureRateAbsltCmftThreshold_LowerSat (0.0F)

/* Expression: CMBB_APosMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/ALatAbsltCmftThreshold'
 */
#define rtCP_ALatAbsltCmftThreshold_UpperSat (10.0F)

/* Expression: CMBB_ALatMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S459>/ALatAbsltCmftThreshold'
 */
#define rtCP_ALatAbsltCmftThreshold_LowerSat (1.0F)

/* Computed Parameter: rtCP_Gain_Gain_c0
 * Referenced by: '<S709>/Gain'
 */
#define rtCP_Gain_Gain_c0              (3.6F)

/* Computed Parameter: rtCP_Gain_Gain_pev
 * Referenced by: '<S613>/Gain'
 */
#define rtCP_Gain_Gain_pev             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_hen
 * Referenced by: '<S615>/Gain'
 */
#define rtCP_Gain_Gain_hen             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_ew
 * Referenced by: '<S490>/Gain'
 */
#define rtCP_Gain_Gain_ew              (3.6F)

/* Computed Parameter: rtCP_Saturation_UpperSat_lh
 * Referenced by: '<S201>/Saturation'
 */
#define rtCP_Saturation_UpperSat_lh    (0.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_gfx
 * Referenced by: '<S201>/Saturation'
 */
#define rtCP_Saturation_LowerSat_gfx   (-10.0F)

/* Computed Parameter: rtCP_Saturation1_UpperSat_o
 * Referenced by: '<S201>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_o    (0.0F)

/* Computed Parameter: rtCP_Saturation1_LowerSat_bw
 * Referenced by: '<S201>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_bw   (-10.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_c3
 * Referenced by: '<S277>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_c3 (8.64E+7F)

/* Computed Parameter: rtCP_Gain_Gain_bv
 * Referenced by: '<S334>/Gain'
 */
#define rtCP_Gain_Gain_bv              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_h1
 * Referenced by: '<S333>/Gain'
 */
#define rtCP_Gain_Gain_h1              (10.0F)

/* Expression: FCW_Ts_Co
 * Referenced by: '<S333>/c_FCW_Ts gain'
 */
#define rtCP_c_FCW_Tsgain_Gain         (0.02F)

/* Expression: single(0)
 * Referenced by: '<S333>/Saturation'
 */
#define rtCP_Saturation_LowerSat_k2    (0.0F)

/* Computed Parameter: rtCP_Saturation2_LowerSat_p
 * Referenced by: '<S319>/Saturation2'
 */
#define rtCP_Saturation2_LowerSat_p    (0.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_du
 * Referenced by: '<S319>/Saturation'
 */
#define rtCP_Saturation_UpperSat_du    (3.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_ii
 * Referenced by: '<S319>/Saturation'
 */
#define rtCP_Saturation_LowerSat_ii    (1.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_k0
 * Referenced by: '<S324>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_k0 (8.64E+7F)

/* Computed Parameter: rtCP_Gain_Gain_ko
 * Referenced by: '<S321>/Gain'
 */
#define rtCP_Gain_Gain_ko              (-1.0F)

/* Computed Parameter: rtCP_Saturation3_UpperSat
 * Referenced by: '<S319>/Saturation3'
 */
#define rtCP_Saturation3_UpperSat      (9.8F)

/* Computed Parameter: rtCP_Saturation3_LowerSat
 * Referenced by: '<S319>/Saturation3'
 */
#define rtCP_Saturation3_LowerSat      (0.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_in
 * Referenced by: '<S362>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_in (8.64E+7F)

/* Expression: single(100)
 * Referenced by: '<S191>/Gain'
 */
#define rtCP_Gain_Gain_jm              (100.0F)

/* Expression: single(6)
 * Referenced by: '<S28>/ResetTime'
 */
#define rtCP_ResetTime_Value_i         (6.0F)

/* Computed Parameter: rtCP_ActuationManagerPeriodicity1_Value
 * Referenced by: '<S28>/ActuationManagerPeriodicity1'
 */
#define rtCP_ActuationManagerPeriodicity1_Value (1.0F)

/* Computed Parameter: rtCP_Saturation1_UpperSat_gm
 * Referenced by: '<S7>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_gm   (4.0F)

/* Computed Parameter: rtCP_Saturation1_LowerSat_l1
 * Referenced by: '<S7>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_l1   (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ml
 * Referenced by: '<S2729>/Gain2'
 */
#define rtCP_Gain2_Gain_ml             (0.5F)

/* Expression: -single(pi)
 * Referenced by: '<S2928>/Gain'
 */
#define rtCP_Gain_Gain_gc              (-3.14159274F)

/* Computed Parameter: rtCP_Merge_1_1_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_1_InitialOutput   (0.0F)

/* Expression: single(0.001)
 * Referenced by: '<S3185>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_i    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_mh
 * Referenced by: '<S3185>/Saturation'
 */
#define rtCP_Saturation_UpperSat_mh    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_em
 * Referenced by: '<S3185>/Saturation'
 */
#define rtCP_Saturation_LowerSat_em    (0.0F)

/* Computed Parameter: rtCP_Merge_1_2_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_2_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_a54
 * Referenced by: '<S3287>/Gain1'
 */
#define rtCP_Gain1_Gain_a54            (0.5F)

/* Computed Parameter: rtCP_Merge_1_5_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_5_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_bxy
 * Referenced by: '<S3287>/Gain2'
 */
#define rtCP_Gain2_Gain_bxy            (-1.0F)

/* Computed Parameter: rtCP_Merge_1_3_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_3_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_1_4_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_4_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_1_6_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_6_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_1_7_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_7_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ho
 * Referenced by: '<S3315>/Gain1'
 */
#define rtCP_Gain1_Gain_ho             (0.5F)

/* Computed Parameter: rtCP_Merge_1_10_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_10_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_el
 * Referenced by: '<S3315>/Gain2'
 */
#define rtCP_Gain2_Gain_el             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_16_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_16_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_17_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_17_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_a3
 * Referenced by: '<S3335>/Gain1'
 */
#define rtCP_Gain1_Gain_a3             (0.5F)

/* Computed Parameter: rtCP_Merge_1_20_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_20_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_an
 * Referenced by: '<S3335>/Gain2'
 */
#define rtCP_Gain2_Gain_an             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_21_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_21_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_22_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_22_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_n4
 * Referenced by: '<S3345>/Gain1'
 */
#define rtCP_Gain1_Gain_n4             (0.5F)

/* Computed Parameter: rtCP_Merge_1_25_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_25_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_nq
 * Referenced by: '<S3345>/Gain2'
 */
#define rtCP_Gain2_Gain_nq             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput_k
 * Referenced by: '<S2921>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_2_5_InitialOutput
 * Referenced by: '<S2921>/Merge_2'
 */
#define rtCP_Merge_2_5_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_8_InitialOutput
 * Referenced by: '<S2921>/Merge_2'
 */
#define rtCP_Merge_2_8_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_no
 * Referenced by: '<S3302>/Gain1'
 */
#define rtCP_Gain1_Gain_no             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_gi
 * Referenced by: '<S3302>/Gain2'
 */
#define rtCP_Gain2_Gain_gi             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput_k
 * Referenced by: '<S2921>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_2_6_InitialOutput
 * Referenced by: '<S2921>/Merge_2'
 */
#define rtCP_Merge_2_6_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_7_InitialOutput
 * Referenced by: '<S2921>/Merge_2'
 */
#define rtCP_Merge_2_7_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_9_InitialOutput
 * Referenced by: '<S2921>/Merge_2'
 */
#define rtCP_Merge_2_9_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_10_InitialOutput
 * Referenced by: '<S2921>/Merge_2'
 */
#define rtCP_Merge_2_10_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_1_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_1_InitialOutput_i (0.0F)

/* Expression: single(0.001)
 * Referenced by: '<S3745>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_fp   (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_fl
 * Referenced by: '<S3745>/Saturation'
 */
#define rtCP_Saturation_UpperSat_fl    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_f
 * Referenced by: '<S3745>/Saturation'
 */
#define rtCP_Saturation_LowerSat_f     (0.0F)

/* Computed Parameter: rtCP_Merge_1_2_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_2_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_iv
 * Referenced by: '<S3853>/Gain1'
 */
#define rtCP_Gain1_Gain_iv             (0.5F)

/* Computed Parameter: rtCP_Merge_1_5_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_5_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_he
 * Referenced by: '<S3853>/Gain2'
 */
#define rtCP_Gain2_Gain_he             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_3_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_3_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_4_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_4_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_6_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_6_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_7_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_7_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_a10
 * Referenced by: '<S3881>/Gain1'
 */
#define rtCP_Gain1_Gain_a10            (0.5F)

/* Computed Parameter: rtCP_Merge_1_10_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_10_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_az
 * Referenced by: '<S3881>/Gain2'
 */
#define rtCP_Gain2_Gain_az             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_16_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_16_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_17_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_17_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_d4
 * Referenced by: '<S3901>/Gain1'
 */
#define rtCP_Gain1_Gain_d4             (0.5F)

/* Computed Parameter: rtCP_Merge_1_20_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_20_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_kp
 * Referenced by: '<S3901>/Gain2'
 */
#define rtCP_Gain2_Gain_kp             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_21_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_21_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_22_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_22_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_pg
 * Referenced by: '<S3911>/Gain1'
 */
#define rtCP_Gain1_Gain_pg             (0.5F)

/* Computed Parameter: rtCP_Merge_1_25_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_25_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_hb
 * Referenced by: '<S3911>/Gain2'
 */
#define rtCP_Gain2_Gain_hb             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput_g
 * Referenced by: '<S3478>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_5_InitialOutput_g
 * Referenced by: '<S3478>/Merge_2'
 */
#define rtCP_Merge_2_5_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_8_InitialOutput_g
 * Referenced by: '<S3478>/Merge_2'
 */
#define rtCP_Merge_2_8_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_lvv
 * Referenced by: '<S3868>/Gain1'
 */
#define rtCP_Gain1_Gain_lvv            (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_ns
 * Referenced by: '<S3868>/Gain2'
 */
#define rtCP_Gain2_Gain_ns             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput_g
 * Referenced by: '<S3478>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_6_InitialOutput_g
 * Referenced by: '<S3478>/Merge_2'
 */
#define rtCP_Merge_2_6_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_7_InitialOutput_g
 * Referenced by: '<S3478>/Merge_2'
 */
#define rtCP_Merge_2_7_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_9_InitialOutput_g
 * Referenced by: '<S3478>/Merge_2'
 */
#define rtCP_Merge_2_9_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_10_InitialOutput_g
 * Referenced by: '<S3478>/Merge_2'
 */
#define rtCP_Merge_2_10_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Gain4_Gain_c
 * Referenced by: '<S2840>/Gain4'
 */
#define rtCP_Gain4_Gain_c              (0.5F)

/* Computed Parameter: rtCP_Gain_1_Gain_nn
 * Referenced by: '<S2865>/Gain_1'
 */
#define rtCP_Gain_1_Gain_nn            (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_bj
 * Referenced by: '<S2866>/Gain_1'
 */
#define rtCP_Gain_1_Gain_bj            (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_cj
 * Referenced by: '<S2867>/Gain_1'
 */
#define rtCP_Gain_1_Gain_cj            (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_gw
 * Referenced by: '<S2864>/Gain_1'
 */
#define rtCP_Gain_1_Gain_gw            (-1.0F)

/* Computed Parameter: rtCP_Merge_1_11_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_11_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_12_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_12_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_gx
 * Referenced by: '<S3325>/Gain1'
 */
#define rtCP_Gain1_Gain_gx             (0.5F)

/* Computed Parameter: rtCP_Merge_1_15_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_15_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ant
 * Referenced by: '<S3325>/Gain2'
 */
#define rtCP_Gain2_Gain_ant            (-1.0F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput_k
 * Referenced by: '<S2921>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput_k
 * Referenced by: '<S2921>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_11_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_11_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_12_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_12_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ne
 * Referenced by: '<S3891>/Gain1'
 */
#define rtCP_Gain1_Gain_ne             (0.5F)

/* Computed Parameter: rtCP_Merge_1_15_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_15_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ou2
 * Referenced by: '<S3891>/Gain2'
 */
#define rtCP_Gain2_Gain_ou2            (-1.0F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput_g
 * Referenced by: '<S3478>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput_g
 * Referenced by: '<S3478>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_cl
 * Referenced by: '<S4059>/Gain_1'
 */
#define rtCP_Gain_1_Gain_cl            (-1.0F)

/* Computed Parameter: rtCP_Merge_1_13_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_13_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_14_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_14_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_18_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_18_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_19_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_19_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_23_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_23_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_24_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_24_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_8_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_8_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_1_9_InitialOutput
 * Referenced by: '<S2921>/Merge_1'
 */
#define rtCP_Merge_1_9_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_1_13_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_13_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_14_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_14_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_18_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_18_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_19_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_19_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_23_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_23_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_24_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_24_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_8_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_8_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_9_InitialOutput_i
 * Referenced by: '<S3478>/Merge_1'
 */
#define rtCP_Merge_1_9_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_jd
 * Referenced by: '<S4414>/Gain2'
 */
#define rtCP_Gain2_Gain_jd             (0.5F)

/* Expression: -single(pi)
 * Referenced by: '<S4613>/Gain'
 */
#define rtCP_Gain_Gain_il              (-3.14159274F)

/* Computed Parameter: rtCP_Merge_1_1_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_1_InitialOutput_j (0.0F)

/* Expression: single(0.001)
 * Referenced by: '<S4870>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_o    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_n1
 * Referenced by: '<S4870>/Saturation'
 */
#define rtCP_Saturation_UpperSat_n1    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_pgv
 * Referenced by: '<S4870>/Saturation'
 */
#define rtCP_Saturation_LowerSat_pgv   (0.0F)

/* Computed Parameter: rtCP_Merge_1_2_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_2_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_dl
 * Referenced by: '<S4972>/Gain1'
 */
#define rtCP_Gain1_Gain_dl             (0.5F)

/* Computed Parameter: rtCP_Merge_1_5_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_5_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_dy
 * Referenced by: '<S4972>/Gain2'
 */
#define rtCP_Gain2_Gain_dy             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_3_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_3_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_4_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_4_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_6_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_6_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_7_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_7_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_pi
 * Referenced by: '<S5000>/Gain1'
 */
#define rtCP_Gain1_Gain_pi             (0.5F)

/* Computed Parameter: rtCP_Merge_1_10_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_10_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_fv
 * Referenced by: '<S5000>/Gain2'
 */
#define rtCP_Gain2_Gain_fv             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_16_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_16_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_17_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_17_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_k5
 * Referenced by: '<S5020>/Gain1'
 */
#define rtCP_Gain1_Gain_k5             (0.5F)

/* Computed Parameter: rtCP_Merge_1_20_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_20_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_bk
 * Referenced by: '<S5020>/Gain2'
 */
#define rtCP_Gain2_Gain_bk             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_21_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_21_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_22_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_22_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_lc
 * Referenced by: '<S5030>/Gain1'
 */
#define rtCP_Gain1_Gain_lc             (0.5F)

/* Computed Parameter: rtCP_Merge_1_25_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_25_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_hy
 * Referenced by: '<S5030>/Gain2'
 */
#define rtCP_Gain2_Gain_hy             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput_f
 * Referenced by: '<S4606>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_5_InitialOutput_f
 * Referenced by: '<S4606>/Merge_2'
 */
#define rtCP_Merge_2_5_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_8_InitialOutput_f
 * Referenced by: '<S4606>/Merge_2'
 */
#define rtCP_Merge_2_8_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_cs
 * Referenced by: '<S4987>/Gain1'
 */
#define rtCP_Gain1_Gain_cs             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_hg
 * Referenced by: '<S4987>/Gain2'
 */
#define rtCP_Gain2_Gain_hg             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput_f
 * Referenced by: '<S4606>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_6_InitialOutput_f
 * Referenced by: '<S4606>/Merge_2'
 */
#define rtCP_Merge_2_6_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_7_InitialOutput_f
 * Referenced by: '<S4606>/Merge_2'
 */
#define rtCP_Merge_2_7_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_9_InitialOutput_f
 * Referenced by: '<S4606>/Merge_2'
 */
#define rtCP_Merge_2_9_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_10_InitialOutput_f
 * Referenced by: '<S4606>/Merge_2'
 */
#define rtCP_Merge_2_10_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_1_1_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_1_InitialOutput_k (0.0F)

/* Expression: single(0.001)
 * Referenced by: '<S5430>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_j    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_j
 * Referenced by: '<S5430>/Saturation'
 */
#define rtCP_Saturation_UpperSat_j     (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_hg
 * Referenced by: '<S5430>/Saturation'
 */
#define rtCP_Saturation_LowerSat_hg    (0.0F)

/* Computed Parameter: rtCP_Merge_1_2_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_2_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_og
 * Referenced by: '<S5538>/Gain1'
 */
#define rtCP_Gain1_Gain_og             (0.5F)

/* Computed Parameter: rtCP_Merge_1_5_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_5_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ew
 * Referenced by: '<S5538>/Gain2'
 */
#define rtCP_Gain2_Gain_ew             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_3_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_3_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_4_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_4_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_6_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_6_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_7_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_7_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_kh
 * Referenced by: '<S5566>/Gain1'
 */
#define rtCP_Gain1_Gain_kh             (0.5F)

/* Computed Parameter: rtCP_Merge_1_10_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_10_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_li
 * Referenced by: '<S5566>/Gain2'
 */
#define rtCP_Gain2_Gain_li             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_16_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_16_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_17_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_17_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_20_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_20_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_21_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_21_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_22_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_22_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_25_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_25_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput_j
 * Referenced by: '<S5163>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_5_InitialOutput_j
 * Referenced by: '<S5163>/Merge_2'
 */
#define rtCP_Merge_2_5_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_8_InitialOutput_j
 * Referenced by: '<S5163>/Merge_2'
 */
#define rtCP_Merge_2_8_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ar
 * Referenced by: '<S5553>/Gain1'
 */
#define rtCP_Gain1_Gain_ar             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_lg
 * Referenced by: '<S5553>/Gain2'
 */
#define rtCP_Gain2_Gain_lg             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput_j
 * Referenced by: '<S5163>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_6_InitialOutput_j
 * Referenced by: '<S5163>/Merge_2'
 */
#define rtCP_Merge_2_6_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_7_InitialOutput_j
 * Referenced by: '<S5163>/Merge_2'
 */
#define rtCP_Merge_2_7_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_9_InitialOutput_j
 * Referenced by: '<S5163>/Merge_2'
 */
#define rtCP_Merge_2_9_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_10_InitialOutput_j
 * Referenced by: '<S5163>/Merge_2'
 */
#define rtCP_Merge_2_10_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain4_Gain_h
 * Referenced by: '<S4525>/Gain4'
 */
#define rtCP_Gain4_Gain_h              (0.5F)

/* Computed Parameter: rtCP_Gain_1_Gain_iw
 * Referenced by: '<S4551>/Gain_1'
 */
#define rtCP_Gain_1_Gain_iw            (-1.0F)

/* Computed Parameter: rtCP_Merge_1_11_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_11_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_12_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_12_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_io
 * Referenced by: '<S5010>/Gain1'
 */
#define rtCP_Gain1_Gain_io             (0.5F)

/* Computed Parameter: rtCP_Merge_1_15_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_15_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_jy
 * Referenced by: '<S5010>/Gain2'
 */
#define rtCP_Gain2_Gain_jy             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput_f
 * Referenced by: '<S4606>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput_f
 * Referenced by: '<S4606>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_1_11_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_11_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_12_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_12_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_aa
 * Referenced by: '<S5576>/Gain1'
 */
#define rtCP_Gain1_Gain_aa             (0.5F)

/* Computed Parameter: rtCP_Merge_1_15_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_15_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_j3
 * Referenced by: '<S5576>/Gain2'
 */
#define rtCP_Gain2_Gain_j3             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput_j
 * Referenced by: '<S5163>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput_j
 * Referenced by: '<S5163>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_13_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_13_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_14_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_14_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_18_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_18_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_19_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_19_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_23_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_23_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_24_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_24_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_8_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_8_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_9_InitialOutput_j
 * Referenced by: '<S4606>/Merge_1'
 */
#define rtCP_Merge_1_9_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_13_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_13_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_14_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_14_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_18_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_18_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_19_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_19_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_23_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_23_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_24_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_24_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_8_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_8_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_9_InitialOutput_k
 * Referenced by: '<S5163>/Merge_1'
 */
#define rtCP_Merge_1_9_InitialOutput_k (0.0F)

/* Expression: single(180/pi)
 * Referenced by: '<S6>/Gain1'
 */
#define rtCP_Gain1_Gain_l5z            (57.2957802F)

/* Expression: single(3.6)
 * Referenced by: '<S6>/Gain'
 */
#define rtCP_Gain_Gain_ige             (3.6F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_ih
 * Referenced by: '<S6323>/Unit Delay'
 */
#define rtCP_UnitDelay_InitialCondition_ih (-1.0F)

/* Expression: single(-1)
 * Referenced by: '<S6336>/Gain1'
 */
#define rtCP_Gain1_Gain_el             (-1.0F)

/* Expression: single(3.6)
 * Referenced by: '<S6336>/Gain2'
 */
#define rtCP_Gain2_Gain_eq             (3.6F)

/* Computed Parameter: rtCP_Gain_Gain_ck
 * Referenced by: '<S6395>/Gain'
 */
#define rtCP_Gain_Gain_ck              (57.2957802F)

/* Computed Parameter: rtCP_Idn_Y0
 * Referenced by: '<S1427>/Idn'
 */
#define rtCP_Idn_Y0                    (0U)

/* Computed Parameter: rtCP_Constant_Value_dkh
 * Referenced by: '<S1285>/Constant'
 */
#define rtCP_Constant_Value_dkh        (0U)

/* Computed Parameter: rtCP_Constant_Value_iks
 * Referenced by: '<S1286>/Constant'
 */
#define rtCP_Constant_Value_iks        (0U)

/* Computed Parameter: rtCP_Constant_Value_ks4
 * Referenced by: '<S1292>/Constant'
 */
#define rtCP_Constant_Value_ks4        (0U)

/* Computed Parameter: rtCP_Constant_Value_g3u
 * Referenced by: '<S1293>/Constant'
 */
#define rtCP_Constant_Value_g3u        (0U)

/* Computed Parameter: rtCP_Constant_Value_n5z
 * Referenced by: '<S1296>/Constant'
 */
#define rtCP_Constant_Value_n5z        (0U)

/* Computed Parameter: rtCP_Constant_Value_pda
 * Referenced by: '<S1297>/Constant'
 */
#define rtCP_Constant_Value_pda        (0U)

/* Computed Parameter: rtCP_Constant_Value_mhx
 * Referenced by: '<S1304>/Constant'
 */
#define rtCP_Constant_Value_mhx        (0U)

/* Computed Parameter: rtCP_Constant_Value_nba
 * Referenced by: '<S1306>/Constant'
 */
#define rtCP_Constant_Value_nba        (0U)

/* Computed Parameter: rtCP_Constant_Value_h34
 * Referenced by: '<S1307>/Constant'
 */
#define rtCP_Constant_Value_h34        (0U)

/* Computed Parameter: rtCP_Constant_Value_nd4
 * Referenced by: '<S1310>/Constant'
 */
#define rtCP_Constant_Value_nd4        (0U)

/* Computed Parameter: rtCP_Constant_Value_gfj
 * Referenced by: '<S1311>/Constant'
 */
#define rtCP_Constant_Value_gfj        (0U)

/* Computed Parameter: rtCP_Constant_Value_acl
 * Referenced by: '<S1320>/Constant'
 */
#define rtCP_Constant_Value_acl        (0U)

/* Computed Parameter: rtCP_Constant_Value_eac3
 * Referenced by: '<S1322>/Constant'
 */
#define rtCP_Constant_Value_eac3       (0U)

/* Computed Parameter: rtCP_Constant_Value_pcq
 * Referenced by: '<S1323>/Constant'
 */
#define rtCP_Constant_Value_pcq        (0U)

/* Computed Parameter: rtCP_Constant_Value_f1a
 * Referenced by: '<S2031>/Constant'
 */
#define rtCP_Constant_Value_f1a        (0U)

/* Computed Parameter: rtCP_Constant_Value_p1
 * Referenced by: '<S2032>/Constant'
 */
#define rtCP_Constant_Value_p1         (0U)

/* Expression: uint32(0)
 * Referenced by: '<S1384>/Constant1'
 */
#define rtCP_Constant1_Value_a0        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S1384>/Constant13'
 */
#define rtCP_Constant13_Value_af       (0U)

/* Expression: uint32(0)
 * Referenced by: '<S1408>/Constant12'
 */
#define rtCP_Constant12_Value_l        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S1408>/Constant4'
 */
#define rtCP_Constant4_Value_eq        (0U)

/* Computed Parameter: rtCP_Constant_Value_gin
 * Referenced by: '<S1423>/Constant'
 */
#define rtCP_Constant_Value_gin        (0U)

/* Computed Parameter: rtCP_Constant_Value_ifa
 * Referenced by: '<S1733>/Constant'
 */
#define rtCP_Constant_Value_ifa        (0U)

/* Computed Parameter: rtCP_DefaultId_Value
 * Referenced by: '<S597>/DefaultId'
 */
#define rtCP_DefaultId_Value           (0U)

/* Computed Parameter: rtCP_Constant_Value_ij0
 * Referenced by: '<S2619>/Constant'
 */
#define rtCP_Constant_Value_ij0        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S2840>/Constant'
 */
#define rtCP_Constant_Value_k4         (0U)

/* Computed Parameter: rtCP_Constant_Value_lmo
 * Referenced by: '<S4303>/Constant'
 */
#define rtCP_Constant_Value_lmo        (0U)

/* Computed Parameter: rtCP_Constant_Value_d1i
 * Referenced by: '<S4304>/Constant'
 */
#define rtCP_Constant_Value_d1i        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S4525>/Constant'
 */
#define rtCP_Constant_Value_mu         (0U)

/* Computed Parameter: rtCP_Constant_Value_fw2
 * Referenced by: '<S5986>/Constant'
 */
#define rtCP_Constant_Value_fw2        (0U)

/* Computed Parameter: rtCP_Constant_Value_kwh
 * Referenced by: '<S5987>/Constant'
 */
#define rtCP_Constant_Value_kwh        (0U)

/* Computed Parameter: rtCP_Constant_Value_ggx
 * Referenced by: '<S6024>/Constant'
 */
#define rtCP_Constant_Value_ggx        (0U)

/* Computed Parameter: rtCP_Constant_Value_gd4j
 * Referenced by: '<S6260>/Constant'
 */
#define rtCP_Constant_Value_gd4j       (4U)

/* Computed Parameter: rtCP_Constant_Value_fdc
 * Referenced by: '<S6261>/Constant'
 */
#define rtCP_Constant_Value_fdc        (10U)

/* Expression: uint32(0)
 * Referenced by: '<S6337>/Constant6'
 */
#define rtCP_Constant6_Value_kd        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S6337>/Constant8'
 */
#define rtCP_Constant8_Value_g5        (0U)

/* Expression: uint32(2)
 * Referenced by: '<S6361>/Constant'
 */
#define rtCP_Constant_Value_ms1        (2U)

/* Expression: uint32(0)
 * Referenced by: '<S6361>/Constant1'
 */
#define rtCP_Constant1_Value_op        (0U)

/* Computed Parameter: rtCP_Constant_Value_ise
 * Referenced by: '<S6364>/Constant'
 */
#define rtCP_Constant_Value_ise        (3U)

/* Computed Parameter: rtCP_Constant1_Value_lxj
 * Referenced by: '<S6364>/Constant1'
 */
#define rtCP_Constant1_Value_lxj       (6U)

/* Computed Parameter: rtCP_Constant2_Value_kf
 * Referenced by: '<S6364>/Constant2'
 */
#define rtCP_Constant2_Value_kf        (4U)

/* Computed Parameter: rtCP_Constant3_Value_kzv
 * Referenced by: '<S6364>/Constant3'
 */
#define rtCP_Constant3_Value_kzv       (1U)

/* Computed Parameter: rtCP_Constant4_Value_lp
 * Referenced by: '<S6364>/Constant4'
 */
#define rtCP_Constant4_Value_lp        (2U)

/* Computed Parameter: rtCP_Constant5_Value_gtf
 * Referenced by: '<S6364>/Constant5'
 */
#define rtCP_Constant5_Value_gtf       (2U)

/* Computed Parameter: rtCP_Constant6_Value_fj
 * Referenced by: '<S6364>/Constant6'
 */
#define rtCP_Constant6_Value_fj        (0U)

/* Computed Parameter: rtCP_Constant_Value_c31
 * Referenced by: '<S6404>/Constant'
 */
#define rtCP_Constant_Value_c31        (4U)

/* Computed Parameter: rtCP_Constant1_Value_mc
 * Referenced by: '<S6404>/Constant1'
 */
#define rtCP_Constant1_Value_mc        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S6338>/Constant2'
 */
#define rtCP_Constant2_Value_br        (0U)

/* Computed Parameter: rtCP_One_1_Value
 * Referenced by: '<S525>/One_1'
 */
#define rtCP_One_1_Value               (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_d
 * Referenced by: '<S525>/Zero_2'
 */
#define rtCP_Zero_2_Value_d            (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_m
 * Referenced by: '<S527>/One_1'
 */
#define rtCP_One_1_Value_m             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_l
 * Referenced by: '<S527>/Zero_2'
 */
#define rtCP_Zero_2_Value_l            (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_b
 * Referenced by: '<S548>/One_1'
 */
#define rtCP_One_1_Value_b             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_hb
 * Referenced by: '<S548>/Zero_2'
 */
#define rtCP_Zero_2_Value_hb           (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_f
 * Referenced by: '<S549>/One_1'
 */
#define rtCP_One_1_Value_f             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_e
 * Referenced by: '<S549>/Zero_2'
 */
#define rtCP_Zero_2_Value_e            (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_a
 * Referenced by: '<S621>/One_1'
 */
#define rtCP_One_1_Value_a             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_hg
 * Referenced by: '<S621>/Zero_2'
 */
#define rtCP_Zero_2_Value_hg           (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_c
 * Referenced by: '<S628>/One_1'
 */
#define rtCP_One_1_Value_c             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_hr
 * Referenced by: '<S628>/Zero_2'
 */
#define rtCP_Zero_2_Value_hr           (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_g
 * Referenced by: '<S635>/One_1'
 */
#define rtCP_One_1_Value_g             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_p
 * Referenced by: '<S635>/Zero_2'
 */
#define rtCP_Zero_2_Value_p            (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_gf
 * Referenced by: '<S775>/One_1'
 */
#define rtCP_One_1_Value_gf            (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_c
 * Referenced by: '<S775>/Zero_2'
 */
#define rtCP_Zero_2_Value_c            (((uint16_T)0U))

/* Expression: uint16(4)
 * Referenced by: '<S6362>/Constant10'
 */
#define rtCP_Constant10_Value_bl       (((uint16_T)4U))

/* Expression: uint16(8)
 * Referenced by: '<S6362>/Constant11'
 */
#define rtCP_Constant11_Value_h        (((uint16_T)8U))

/* Expression: uint16(0)
 * Referenced by: '<S6362>/Constant2'
 */
#define rtCP_Constant2_Value_bb        (((uint16_T)0U))

/* Expression: uint16(1)
 * Referenced by: '<S6362>/Constant3'
 */
#define rtCP_Constant3_Value_an        (((uint16_T)1U))

/* Expression: uint16(16)
 * Referenced by: '<S6362>/Constant4'
 */
#define rtCP_Constant4_Value_b3        (((uint16_T)16U))

/* Expression: uint16(32)
 * Referenced by: '<S6362>/Constant5'
 */
#define rtCP_Constant5_Value_px        (((uint16_T)32U))

/* Expression: uint16(2)
 * Referenced by: '<S6362>/Constant7'
 */
#define rtCP_Constant7_Value_p         (((uint16_T)2U))

/* Computed Parameter: rtCP_DataStoreMemory1_InitialValue_d
 * Referenced by: '<S740>/Data Store Memory1'
 */
#define rtCP_DataStoreMemory1_InitialValue_d (((uint16_T)1U))

/* Expression: const
 * Referenced by: '<S1344>/Constant'
 */
#define rtCP_Constant_Value_b14        (SceniaroInvalidReason_CCFT_SpdInValid)

/* Expression: const
 * Referenced by: '<S1346>/Constant'
 */
#define rtCP_Constant_Value_fnk        (SceniaroInvalidReason_CCFT_HostInValid)

/* Expression: const
 * Referenced by: '<S1347>/Constant'
 */
#define rtCP_Constant_Value_pax        (SceniaroInvalidReason_CCSCP_VlgtInValid)

/* Expression: const
 * Referenced by: '<S1348>/Constant'
 */
#define rtCP_Constant_Value_h3g        (SceniaroInvalidReason_CCSCP_HeadingInValid)

/* Expression: const
 * Referenced by: '<S1349>/Constant'
 */
#define rtCP_Constant_Value_ibc        (SceniaroInvalidReason_CBFANA_VlgtInValid)

/* Expression: const
 * Referenced by: '<S1363>/Constant'
 */
#define rtCP_Constant_Value_cou        (SceniaroInvalidReason_CCSCP_HeadingInValid)

/* Expression: const
 * Referenced by: '<S1364>/Constant'
 */
#define rtCP_Constant_Value_d34        (SceniaroInvalidReason_CBFANA_VlgtInValid)

/* Expression: const
 * Referenced by: '<S1370>/Constant'
 */
#define rtCP_Constant_Value_dp2        (SceniaroInvalidReason_CCFT_SpdInValid)

/* Expression: const
 * Referenced by: '<S1371>/Constant'
 */
#define rtCP_Constant_Value_ojd        (SceniaroInvalidReason_CCFT_HostInValid)

/* Expression: const
 * Referenced by: '<S1372>/Constant'
 */
#define rtCP_Constant_Value_jdl        (SceniaroInvalidReason_CCSCP_VlgtInValid)

/* Expression: VehMtnSt2.StandStillVal3
 * Referenced by: '<S6003>/Constant'
 */
#define rtCP_Constant_Value_g4w        (VehMtnSt2_StandStillVal3)

/* Expression: VehMtnSt2.RollgBackwVal1
 * Referenced by: '<S6003>/Constant1'
 */
#define rtCP_Constant1_Value_bxr       (VehMtnSt2_RollgBackwVal1)

/* Expression: VehMtnSt2.RollgFwdVal1
 * Referenced by: '<S6003>/Constant2'
 */
#define rtCP_Constant2_Value_ot        (VehMtnSt2_RollgFwdVal1)

/* Expression: VehMtnSt2.RollgFwdVal2
 * Referenced by: '<S6003>/Constant3'
 */
#define rtCP_Constant3_Value_h5f       (VehMtnSt2_RollgFwdVal2)

/* Computed Parameter: rtCP_Constant3_Value_ax
 * Referenced by: '<S1076>/Constant3'
 */
#define rtCP_Constant3_Value_ax        (true)

/* Computed Parameter: rtCP_Constant4_Value_eu
 * Referenced by: '<S1076>/Constant4'
 */
#define rtCP_Constant4_Value_eu        (false)

/* Expression: true
 * Referenced by: '<S1438>/true1'
 */
#define rtCP_true1_Value               (true)

/* Expression: true
 * Referenced by: '<S1440>/true1'
 */
#define rtCP_true1_Value_l             (true)

/* Expression: true
 * Referenced by: '<S1443>/true1'
 */
#define rtCP_true1_Value_f             (true)

/* Expression: true
 * Referenced by: '<S1767>/true1'
 */
#define rtCP_true1_Value_e             (true)

/* Expression: true
 * Referenced by: '<S1769>/true1'
 */
#define rtCP_true1_Value_g             (true)

/* Expression: true
 * Referenced by: '<S1772>/true1'
 */
#define rtCP_true1_Value_m             (true)

/* Expression: true
 * Referenced by: '<S2334>/true1'
 */
#define rtCP_true1_Value_i             (true)

/* Expression: true
 * Referenced by: '<S2336>/true1'
 */
#define rtCP_true1_Value_b             (true)

/* Expression: true
 * Referenced by: '<S2339>/true1'
 */
#define rtCP_true1_Value_l0            (true)

/* Computed Parameter: rtCP_False_Value
 * Referenced by: '<S2927>/False'
 */
#define rtCP_False_Value               (false)

/* Computed Parameter: rtCP_True_Value
 * Referenced by: '<S2927>/True'
 */
#define rtCP_True_Value                (true)

/* Computed Parameter: rtCP_False_Value_o
 * Referenced by: '<S2929>/False'
 */
#define rtCP_False_Value_o             (false)

/* Computed Parameter: rtCP_True_Value_f
 * Referenced by: '<S2929>/True'
 */
#define rtCP_True_Value_f              (true)

/* Computed Parameter: rtCP_False_Value_i
 * Referenced by: '<S3213>/False'
 */
#define rtCP_False_Value_i             (false)

/* Computed Parameter: rtCP_False_Value_ih
 * Referenced by: '<S3214>/False'
 */
#define rtCP_False_Value_ih            (false)

/* Computed Parameter: rtCP_False_Value_a
 * Referenced by: '<S3487>/False'
 */
#define rtCP_False_Value_a             (false)

/* Computed Parameter: rtCP_True_Value_a
 * Referenced by: '<S3487>/True'
 */
#define rtCP_True_Value_a              (true)

/* Expression: false
 * Referenced by: '<S4105>/Constant'
 */
#define rtCP_Constant_Value_h1i        (false)

/* Expression: false
 * Referenced by: '<S4106>/Constant'
 */
#define rtCP_Constant_Value_da1        (false)

/* Expression: false
 * Referenced by: '<S4126>/Constant'
 */
#define rtCP_Constant_Value_lzs        (false)

/* Expression: false
 * Referenced by: '<S4127>/Constant'
 */
#define rtCP_Constant_Value_ika        (false)

/* Expression: false
 * Referenced by: '<S4147>/Constant'
 */
#define rtCP_Constant_Value_jch        (false)

/* Expression: false
 * Referenced by: '<S4148>/Constant'
 */
#define rtCP_Constant_Value_ehj        (false)

/* Expression: const
 * Referenced by: '<S1246>/Constant'
 */
#define rtCP_Constant_Value_hbn        (false)

/* Expression: const
 * Referenced by: '<S1277>/Constant'
 */
#define rtCP_Constant_Value_bcq        (false)

/* Expression: true
 * Referenced by: '<S1326>/Constant'
 */
#define rtCP_Constant_Value_ivb        (true)

/* Expression: false
 * Referenced by: '<S1326>/Constant1'
 */
#define rtCP_Constant1_Value_jhk       (false)

/* Expression: true
 * Referenced by: '<S1331>/Constant'
 */
#define rtCP_Constant_Value_jyt        (true)

/* Expression: false
 * Referenced by: '<S1331>/Constant1'
 */
#define rtCP_Constant1_Value_h3z       (false)

/* Computed Parameter: rtCP_Constant3_Value_kr
 * Referenced by: '<S2152>/Constant3'
 */
#define rtCP_Constant3_Value_kr        (true)

/* Computed Parameter: rtCP_Constant4_Value_ohp
 * Referenced by: '<S2152>/Constant4'
 */
#define rtCP_Constant4_Value_ohp       (false)

/* Computed Parameter: rtCP_Constant_Value_ioj
 * Referenced by: '<S2320>/Constant'
 */
#define rtCP_Constant_Value_ioj        (true)

/* Computed Parameter: rtCP_Constant2_Value_ce
 * Referenced by: '<S2320>/Constant2'
 */
#define rtCP_Constant2_Value_ce        (true)

/* Expression: false
 * Referenced by: '<S16>/zeroConstant5'
 */
#define rtCP_zeroConstant5_Value       (false)

/* Expression: true
 * Referenced by: '<S7>/true'
 */
#define rtCP_true_Value                (true)

/* Expression: false
 * Referenced by: '<S142>/Constant'
 */
#define rtCP_Constant_Value_cio        (false)

/* Expression: true
 * Referenced by: '<S143>/Constant'
 */
#define rtCP_Constant_Value_cnv        (true)

/* Expression: false
 * Referenced by: '<S143>/Constant1'
 */
#define rtCP_Constant1_Value_aci       (false)

/* Expression: false
 * Referenced by: '<S144>/Constant1'
 */
#define rtCP_Constant1_Value_jrb       (false)

/* Expression: true
 * Referenced by: '<S144>/Constant2'
 */
#define rtCP_Constant2_Value_eu        (true)

/* Computed Parameter: rtCP_Constant_Value_db1
 * Referenced by: '<S228>/Constant'
 */
#define rtCP_Constant_Value_db1        (false)

/* Computed Parameter: rtCP_Constant_Value_kc2x
 * Referenced by: '<S230>/Constant'
 */
#define rtCP_Constant_Value_kc2x       (false)

/* Computed Parameter: rtCP_Constant_Value_p2g
 * Referenced by: '<S232>/Constant'
 */
#define rtCP_Constant_Value_p2g        (false)

/* Computed Parameter: rtCP_Constant_Value_pdc
 * Referenced by: '<S234>/Constant'
 */
#define rtCP_Constant_Value_pdc        (false)

/* Computed Parameter: rtCP_Constant_Value_dmx
 * Referenced by: '<S236>/Constant'
 */
#define rtCP_Constant_Value_dmx        (false)

/* Computed Parameter: rtCP_Constant_Value_ixq
 * Referenced by: '<S238>/Constant'
 */
#define rtCP_Constant_Value_ixq        (false)

/* Computed Parameter: rtCP_Constant_Value_bo53
 * Referenced by: '<S240>/Constant'
 */
#define rtCP_Constant_Value_bo53       (false)

/* Expression: false
 * Referenced by: '<S200>/FCW_DrvrDecelThdForBrkGainInCllsnFwdWarnCtrl_Ca2'
 */
#define rtCP_FCW_DrvrDecelThdForBrkGainInCllsnFwdWarnCtrl_Ca2_Value (false)

/* Expression: false
 * Referenced by: '<S249>/AllowAnimsForAccBrkCapacity'
 */
#define rtCP_AllowAnimsForAccBrkCapacity_Value (false)

/* Expression: false
 * Referenced by: '<S249>/AllowBicForAccBrkCapacity'
 */
#define rtCP_AllowBicForAccBrkCapacity_Value (false)

/* Expression: true
 * Referenced by: '<S249>/AllowCarsForAccBrkCapacity'
 */
#define rtCP_AllowCarsForAccBrkCapacity_Value (true)

/* Expression: true
 * Referenced by: '<S249>/AllowMcsForAccBrkCapacity'
 */
#define rtCP_AllowMcsForAccBrkCapacity_Value (true)

/* Expression: false
 * Referenced by: '<S249>/AllowObjGenForAccBrkCapacity'
 */
#define rtCP_AllowObjGenForAccBrkCapacity_Value (false)

/* Expression: false
 * Referenced by: '<S249>/AllowPedsForAccBrkCapacity'
 */
#define rtCP_AllowPedsForAccBrkCapacity_Value (false)

/* Expression: true
 * Referenced by: '<S249>/AllowTrucksForAccBrkCapacity'
 */
#define rtCP_AllowTrucksForAccBrkCapacity_Value (true)

/* Expression: true
 * Referenced by: '<S249>/AllowVehOfUnknwnClassForAccBrkCapacity'
 */
#define rtCP_AllowVehOfUnknwnClassForAccBrkCapacity_Value (true)

/* Expression: false
 * Referenced by: '<S249>/DefaultState'
 */
#define rtCP_DefaultState_Value        (false)

/* Expression: false
 * Referenced by: '<S202>/false'
 */
#define rtCP_false_Value               (false)

/* Expression: false
 * Referenced by: '<S211>/false10'
 */
#define rtCP_false10_Value             (false)

/* Expression: true
 * Referenced by: '<S295>/AllowOncomingObjects2'
 */
#define rtCP_AllowOncomingObjects2_Value (true)

/* Expression: true
 * Referenced by: '<S295>/false1'
 */
#define rtCP_false1_Value              (true)

/* Expression: false
 * Referenced by: '<S295>/false10'
 */
#define rtCP_false10_Value_e           (false)

/* Expression: true
 * Referenced by: '<S295>/false2'
 */
#define rtCP_false2_Value              (true)

/* Expression: true
 * Referenced by: '<S295>/false3'
 */
#define rtCP_false3_Value              (true)

/* Expression: true
 * Referenced by: '<S295>/false5'
 */
#define rtCP_false5_Value              (true)

/* Expression: true
 * Referenced by: '<S295>/false6'
 */
#define rtCP_false6_Value              (true)

/* Expression: true
 * Referenced by: '<S295>/false7'
 */
#define rtCP_false7_Value              (true)

/* Expression: true
 * Referenced by: '<S295>/false8'
 */
#define rtCP_false8_Value              (true)

/* Expression: true
 * Referenced by: '<S295>/false9'
 */
#define rtCP_false9_Value              (true)

/* Expression: false
 * Referenced by: '<S296>/false1'
 */
#define rtCP_false1_Value_c            (false)

/* Expression: false
 * Referenced by: '<S296>/false10'
 */
#define rtCP_false10_Value_d           (false)

/* Expression: false
 * Referenced by: '<S296>/false2'
 */
#define rtCP_false2_Value_a            (false)

/* Expression: false
 * Referenced by: '<S296>/false3'
 */
#define rtCP_false3_Value_n            (false)

/* Expression: true
 * Referenced by: '<S296>/false4'
 */
#define rtCP_false4_Value              (true)

/* Expression: true
 * Referenced by: '<S296>/false5'
 */
#define rtCP_false5_Value_f            (true)

/* Expression: false
 * Referenced by: '<S296>/false6'
 */
#define rtCP_false6_Value_f            (false)

/* Expression: false
 * Referenced by: '<S296>/false7'
 */
#define rtCP_false7_Value_m            (false)

/* Expression: false
 * Referenced by: '<S296>/false8'
 */
#define rtCP_false8_Value_j            (false)

/* Expression: false
 * Referenced by: '<S296>/false9'
 */
#define rtCP_false9_Value_m            (false)

/* Expression: false
 * Referenced by: '<S213>/DstCmftActvdForBicycleInCllsnFwdWarnCtrl'
 */
#define rtCP_DstCmftActvdForBicycleInCllsnFwdWarnCtrl_Value (false)

/* Expression: false
 * Referenced by: '<S213>/DstCmftActvdForCarInCllsnFwdWarnCtrl'
 */
#define rtCP_DstCmftActvdForCarInCllsnFwdWarnCtrl_Value (false)

/* Expression: false
 * Referenced by: '<S213>/DstCmftActvdForMotorcycleInCllsnFwdWarnCtrl'
 */
#define rtCP_DstCmftActvdForMotorcycleInCllsnFwdWarnCtrl_Value (false)

/* Expression: false
 * Referenced by: '<S213>/DstCmftActvdForPedInCllsnFwdWarnCtrl'
 */
#define rtCP_DstCmftActvdForPedInCllsnFwdWarnCtrl_Value (false)

/* Expression: false
 * Referenced by: '<S213>/DstCmftActvdForTruckInCllsnFwdWarnCtrl'
 */
#define rtCP_DstCmftActvdForTruckInCllsnFwdWarnCtrl_Value (false)

/* Expression: false
 * Referenced by: '<S213>/false'
 */
#define rtCP_false_Value_c             (false)

/* Computed Parameter: rtCP_Constant_Value_it
 * Referenced by: '<S485>/Constant'
 */
#define rtCP_Constant_Value_it         (true)

/* Computed Parameter: rtCP_Constant1_Value_pmt
 * Referenced by: '<S485>/Constant1'
 */
#define rtCP_Constant1_Value_pmt       (false)

/* Expression: false
 * Referenced by: '<S613>/Constant'
 */
#define rtCP_Constant_Value_d3w        (false)

/* Expression: true
 * Referenced by: '<S626>/Constant'
 */
#define rtCP_Constant_Value_auz        (true)

/* Expression: false
 * Referenced by: '<S626>/Constant1'
 */
#define rtCP_Constant1_Value_hls       (false)

/* Computed Parameter: rtCP_Constant_Value_ntk
 * Referenced by: '<S649>/Constant'
 */
#define rtCP_Constant_Value_ntk        (true)

/* Computed Parameter: rtCP_Constant1_Value_brh
 * Referenced by: '<S649>/Constant1'
 */
#define rtCP_Constant1_Value_brh       (false)

/* Expression: true
 * Referenced by: '<S652>/Constant2'
 */
#define rtCP_Constant2_Value_df        (true)

/* Expression: true
 * Referenced by: '<S677>/Constant2'
 */
#define rtCP_Constant2_Value_n3        (true)

/* Computed Parameter: rtCP_Constant3_Value_a1
 * Referenced by: '<S691>/Constant3'
 */
#define rtCP_Constant3_Value_a1        (true)

/* Computed Parameter: rtCP_Constant4_Value_ac
 * Referenced by: '<S691>/Constant4'
 */
#define rtCP_Constant4_Value_ac        (false)

/* Computed Parameter: rtCP_Constant_Value_bil
 * Referenced by: '<S718>/Constant'
 */
#define rtCP_Constant_Value_bil        (true)

/* Computed Parameter: rtCP_Constant1_Value_di
 * Referenced by: '<S718>/Constant1'
 */
#define rtCP_Constant1_Value_di        (false)

/* Expression: false
 * Referenced by: '<S741>/Constant'
 */
#define rtCP_Constant_Value_ewpv       (false)

/* Expression: true
 * Referenced by: '<S768>/Constant3'
 */
#define rtCP_Constant3_Value_i4        (true)

/* Computed Parameter: rtCP_Constant_Value_lbr
 * Referenced by: '<S770>/Constant'
 */
#define rtCP_Constant_Value_lbr        (true)

/* Computed Parameter: rtCP_Constant1_Value_es
 * Referenced by: '<S770>/Constant1'
 */
#define rtCP_Constant1_Value_es        (false)

/* Computed Parameter: rtCP_Denied_Value
 * Referenced by: '<S597>/Denied'
 */
#define rtCP_Denied_Value              (true)

/* Computed Parameter: rtCP_NotDenied_Value
 * Referenced by: '<S597>/NotDenied'
 */
#define rtCP_NotDenied_Value           (false)

/* Computed Parameter: rtCP_NotDenied1_Value
 * Referenced by: '<S597>/NotDenied1'
 */
#define rtCP_NotDenied1_Value          (false)

/* Expression: false
 * Referenced by: '<S598>/Constant2'
 */
#define rtCP_Constant2_Value_co        (false)

/* Expression: false
 * Referenced by: '<S777>/Constant3'
 */
#define rtCP_Constant3_Value_pb        (false)

/* Expression: true
 * Referenced by: '<S777>/Constant5'
 */
#define rtCP_Constant5_Value_na        (true)

/* Expression: true
 * Referenced by: '<S778>/Constant'
 */
#define rtCP_Constant_Value_gl2        (true)

/* Expression: false
 * Referenced by: '<S778>/Constant1'
 */
#define rtCP_Constant1_Value_cnu       (false)

/* Computed Parameter: rtCP_Constant3_Value_cq
 * Referenced by: '<S1088>/Constant3'
 */
#define rtCP_Constant3_Value_cq        (true)

/* Computed Parameter: rtCP_Constant4_Value_it5
 * Referenced by: '<S1088>/Constant4'
 */
#define rtCP_Constant4_Value_it5       (false)

/* Computed Parameter: rtCP_Constant3_Value_ah
 * Referenced by: '<S1089>/Constant3'
 */
#define rtCP_Constant3_Value_ah        (true)

/* Computed Parameter: rtCP_Constant4_Value_ir
 * Referenced by: '<S1089>/Constant4'
 */
#define rtCP_Constant4_Value_ir        (false)

/* Computed Parameter: rtCP_Constant_Value_one
 * Referenced by: '<S1090>/Constant'
 */
#define rtCP_Constant_Value_one        (true)

/* Computed Parameter: rtCP_Constant1_Value_e2n
 * Referenced by: '<S1090>/Constant1'
 */
#define rtCP_Constant1_Value_e2n       (false)

/* Expression: false
 * Referenced by: '<S1133>/false'
 */
#define rtCP_false_Value_i             (false)

/* Expression: true
 * Referenced by: '<S1133>/true'
 */
#define rtCP_true_Value_c              (true)

/* Expression: true
 * Referenced by: '<S1132>/Constant'
 */
#define rtCP_Constant_Value_lpw        (true)

/* Expression: true
 * Referenced by: '<S2649>/true1'
 */
#define rtCP_true1_Value_k             (true)

/* Expression: true
 * Referenced by: '<S2651>/true1'
 */
#define rtCP_true1_Value_n             (true)

/* Expression: true
 * Referenced by: '<S2654>/true1'
 */
#define rtCP_true1_Value_np            (true)

/* Expression: false
 * Referenced by: '<S2608>/Constant_3'
 */
#define rtCP_Constant_3_Value          (false)

/* Expression: false
 * Referenced by: '<S2608>/Constant_4'
 */
#define rtCP_Constant_4_Value          (false)

/* Expression: false
 * Referenced by: '<S2608>/Constant_5'
 */
#define rtCP_Constant_5_Value          (false)

/* Expression: k_AEB_CPTA_EnCPRF_SpdCorrect
 * Referenced by: '<S2624>/Constant11'
 */
#define rtCP_Constant11_Value_do       (true)

/* Expression: k_AEB_CPTA_EnCPRF_SpdCorrect
 * Referenced by: '<S2624>/Constant13'
 */
#define rtCP_Constant13_Value_g        (true)

/* Expression: false
 * Referenced by: '<S2663>/Constant3'
 */
#define rtCP_Constant3_Value_e3        (false)

/* Expression: true
 * Referenced by: '<S2663>/Constant5'
 */
#define rtCP_Constant5_Value_nv        (true)

/* Expression: true
 * Referenced by: '<S2667>/Constant'
 */
#define rtCP_Constant_Value_cyb        (true)

/* Expression: false
 * Referenced by: '<S2667>/Constant1'
 */
#define rtCP_Constant1_Value_hs        (false)

/* Expression: true
 * Referenced by: '<S2625>/Constant'
 */
#define rtCP_Constant_Value_jbdg       (true)

/* Expression: false
 * Referenced by: '<S2625>/Constant1'
 */
#define rtCP_Constant1_Value_hg        (false)

/* Expression: true
 * Referenced by: '<S2785>/true1'
 */
#define rtCP_true1_Value_nf            (true)

/* Expression: true
 * Referenced by: '<S2787>/true1'
 */
#define rtCP_true1_Value_ec            (true)

/* Expression: true
 * Referenced by: '<S2790>/true1'
 */
#define rtCP_true1_Value_h             (true)

/* Expression: true
 * Referenced by: '<S2794>/true1'
 */
#define rtCP_true1_Value_lf            (true)

/* Expression: true
 * Referenced by: '<S2796>/true1'
 */
#define rtCP_true1_Value_he            (true)

/* Expression: true
 * Referenced by: '<S2799>/true1'
 */
#define rtCP_true1_Value_i0            (true)

/* Expression: false
 * Referenced by: '<S2841>/Constant9'
 */
#define rtCP_Constant9_Value_cw        (false)

/* Expression: false
 * Referenced by: '<S2905>/Constant'
 */
#define rtCP_Constant_Value_az1        (false)

/* Expression: false
 * Referenced by: '<S4081>/Constant1'
 */
#define rtCP_Constant1_Value_eum       (false)

/* Expression: false
 * Referenced by: '<S4081>/Constant2'
 */
#define rtCP_Constant2_Value_a4        (false)

/* Expression: true
 * Referenced by: '<S4081>/Constant3'
 */
#define rtCP_Constant3_Value_br        (true)

/* Expression: false
 * Referenced by: '<S4081>/Constant4'
 */
#define rtCP_Constant4_Value_ea        (false)

/* Computed Parameter: rtCP_Constant_Value_jm2
 * Referenced by: '<S4074>/Constant'
 */
#define rtCP_Constant_Value_jm2        (false)

/* Expression: true
 * Referenced by: '<S4075>/Constant_1'
 */
#define rtCP_Constant_1_Value_on       (true)

/* Expression: false
 * Referenced by: '<S4075>/Constant_3'
 */
#define rtCP_Constant_3_Value_k        (false)

/* Expression: false
 * Referenced by: '<S2609>/Constant_21'
 */
#define rtCP_Constant_21_Value_e       (false)

/* Expression: false
 * Referenced by: '<S2609>/Constant_3'
 */
#define rtCP_Constant_3_Value_i        (false)

/* Expression: false
 * Referenced by: '<S2609>/Constant_32'
 */
#define rtCP_Constant_32_Value_h       (false)

/* Expression: false
 * Referenced by: '<S2609>/Constant_4'
 */
#define rtCP_Constant_4_Value_d        (false)

/* Expression: false
 * Referenced by: '<S2609>/Constant_5'
 */
#define rtCP_Constant_5_Value_g        (false)

/* Expression: k_AEB_CPTA_EnCPRF_SpdCorrect
 * Referenced by: '<S4309>/Constant11'
 */
#define rtCP_Constant11_Value_l        (true)

/* Expression: k_AEB_CPTA_EnCPRF_SpdCorrect
 * Referenced by: '<S4309>/Constant13'
 */
#define rtCP_Constant13_Value_n        (true)

/* Expression: false
 * Referenced by: '<S4348>/Constant3'
 */
#define rtCP_Constant3_Value_hej       (false)

/* Expression: true
 * Referenced by: '<S4348>/Constant5'
 */
#define rtCP_Constant5_Value_ak        (true)

/* Expression: true
 * Referenced by: '<S4352>/Constant'
 */
#define rtCP_Constant_Value_bu         (true)

/* Expression: false
 * Referenced by: '<S4352>/Constant1'
 */
#define rtCP_Constant1_Value_k0        (false)

/* Expression: true
 * Referenced by: '<S4310>/Constant'
 */
#define rtCP_Constant_Value_bn0        (true)

/* Expression: false
 * Referenced by: '<S4310>/Constant1'
 */
#define rtCP_Constant1_Value_gzk       (false)

/* Expression: false
 * Referenced by: '<S6008>/Constant'
 */
#define rtCP_Constant_Value_lr         (false)

/* Expression: false
 * Referenced by: '<S6008>/Constant1'
 */
#define rtCP_Constant1_Value_hts       (false)

/* Expression: true
 * Referenced by: '<S6008>/Constant10'
 */
#define rtCP_Constant10_Value_f        (true)

/* Expression: false
 * Referenced by: '<S6008>/Constant2'
 */
#define rtCP_Constant2_Value_gb        (false)

/* Expression: true
 * Referenced by: '<S6008>/Constant3'
 */
#define rtCP_Constant3_Value_f1        (true)

/* Expression: true
 * Referenced by: '<S6008>/Constant8'
 */
#define rtCP_Constant8_Value_ah        (true)

/* Expression: true
 * Referenced by: '<S6008>/Constant9'
 */
#define rtCP_Constant9_Value_i2        (true)

/* Expression: false
 * Referenced by: '<S6011>/Constant'
 */
#define rtCP_Constant_Value_lka        (false)

/* Expression: false
 * Referenced by: '<S6011>/Constant1'
 */
#define rtCP_Constant1_Value_ka        (false)

/* Expression: false
 * Referenced by: '<S6011>/Constant2'
 */
#define rtCP_Constant2_Value_ej        (false)

/* Expression: true
 * Referenced by: '<S6011>/Constant3'
 */
#define rtCP_Constant3_Value_pv        (true)

/* Expression: false
 * Referenced by: '<S6011>/Constant4'
 */
#define rtCP_Constant4_Value_lc        (false)

/* Expression: false
 * Referenced by: '<S6011>/Constant6'
 */
#define rtCP_Constant6_Value_a         (false)

/* Expression: false
 * Referenced by: '<S6011>/Constant7'
 */
#define rtCP_Constant7_Value_ns        (false)

/* Expression: true
 * Referenced by: '<S6026>/Constant'
 */
#define rtCP_Constant_Value_mav        (true)

/* Computed Parameter: rtCP_Constant3_Value_oa
 * Referenced by: '<S6264>/Constant3'
 */
#define rtCP_Constant3_Value_oa        (true)

/* Computed Parameter: rtCP_Constant4_Value_l2
 * Referenced by: '<S6264>/Constant4'
 */
#define rtCP_Constant4_Value_l2        (false)

/* Expression: true
 * Referenced by: '<S2615>/Constant3'
 */
#define rtCP_Constant3_Value_le        (true)

/* Expression: true
 * Referenced by: '<S2615>/Constant4'
 */
#define rtCP_Constant4_Value_hk        (true)

/* Expression: true
 * Referenced by: '<S2615>/Constant5'
 */
#define rtCP_Constant5_Value_eq        (true)

/* Expression: true
 * Referenced by: '<S2615>/Constant6'
 */
#define rtCP_Constant6_Value_ez        (true)

/* Expression: C_TRUE
 * Referenced by: '<S2615>/Constant'
 */
#define rtCP_Constant_Value_jmz        (true)

/* Expression: false
 * Referenced by: '<S6>/Constant38'
 */
#define rtCP_Constant38_Value_d        (false)

/* Expression: true
 * Referenced by: '<S6>/Constant'
 */
#define rtCP_Constant_Value_fk         (true)

/* Expression: true
 * Referenced by: '<S6>/Constant9'
 */
#define rtCP_Constant9_Value_ik        (true)

/* Expression: true
 * Referenced by: '<S6>/Constant11'
 */
#define rtCP_Constant11_Value_gb       (true)

/* Expression: true
 * Referenced by: '<S6>/Constant12'
 */
#define rtCP_Constant12_Value_d        (true)

/* Expression: true
 * Referenced by: '<S6>/Constant4'
 */
#define rtCP_Constant4_Value_en        (true)

/* Expression: true
 * Referenced by: '<S6>/Constant7'
 */
#define rtCP_Constant7_Value_c         (true)

/* Expression: true
 * Referenced by: '<S6>/Constant8'
 */
#define rtCP_Constant8_Value_ns        (true)

/* Expression: true
 * Referenced by: '<S6328>/Constant1'
 */
#define rtCP_Constant1_Value_l3b       (true)

/* Computed Parameter: rtCP_Constant_Value_ay0
 * Referenced by: '<S6358>/Constant'
 */
#define rtCP_Constant_Value_ay0        (false)

/* Computed Parameter: rtCP_Constant_Value_eqg
 * Referenced by: '<S6359>/Constant'
 */
#define rtCP_Constant_Value_eqg        (false)

/* Expression: C_FALSE
 * Referenced by: '<S6337>/Constant11'
 */
#define rtCP_Constant11_Value_jn       (false)

/* Expression: C_FALSE
 * Referenced by: '<S6337>/Constant15'
 */
#define rtCP_Constant15_Value_d        (false)

/* Expression: C_FALSE
 * Referenced by: '<S6337>/Constant23'
 */
#define rtCP_Constant23_Value_a        (false)

/* Expression: C_FALSE
 * Referenced by: '<S6337>/Constant25'
 */
#define rtCP_Constant25_Value          (false)

/* Expression: C_FALSE
 * Referenced by: '<S6337>/Constant5'
 */
#define rtCP_Constant5_Value_gr        (false)

/* Expression: C_FALSE
 * Referenced by: '<S6337>/Constant7'
 */
#define rtCP_Constant7_Value_ci        (false)

/* Expression: true
 * Referenced by: '<S6420>/Constant'
 */
#define rtCP_Constant_Value_nnq        (true)

/* Computed Parameter: rtCP_Constant_Value_j1nl
 * Referenced by: '<S6459>/Constant'
 */
#define rtCP_Constant_Value_j1nl       (false)

/* Expression: false
 * Referenced by: '<S6421>/Constant12'
 */
#define rtCP_Constant12_Value_h        (false)

/* Expression: EnEspOff_AWBActive2Passive
 * Referenced by: '<S6422>/Constant49'
 */
#define rtCP_Constant49_Value          (true)

/* Expression: EnAccPose_HBAActive2Passive
 * Referenced by: '<S6422>/Constant68'
 */
#define rtCP_Constant68_Value          (true)

/* Expression: EnWheelAngle_HBAActive2Passive
 * Referenced by: '<S6422>/Constant71'
 */
#define rtCP_Constant71_Value          (true)

/* Expression: EnNotD_HBAActive2Passive
 * Referenced by: '<S6422>/Constant74'
 */
#define rtCP_Constant74_Value          (true)

/* Computed Parameter: rtCP_ForIterator_IterationLimit_h
 * Referenced by: '<S1460>/For Iterator'
 */
#define rtCP_ForIterator_IterationLimit_h (4)

/* Computed Parameter: rtCP_Gain_Gain_jon
 * Referenced by: '<S2125>/Gain'
 */
#define rtCP_Gain_Gain_jon             (((uint8_T)164U))

/* Computed Parameter: rtCP_FixPtConstant_Value
 * Referenced by: '<S1043>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value       (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition
 * Referenced by: '<S1043>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtConstant_Value_l
 * Referenced by: '<S1047>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_l     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_o
 * Referenced by: '<S1047>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_o (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtConstant_Value_h
 * Referenced by: '<S1072>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_h     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_k
 * Referenced by: '<S1072>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_k (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtConstant_Value_d
 * Referenced by: '<S1078>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_d     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_b
 * Referenced by: '<S1079>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_b     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_d
 * Referenced by: '<S1078>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_d (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_ol
 * Referenced by: '<S1079>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_ol (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtConstant_Value_i
 * Referenced by: '<S1084>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_i     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_f
 * Referenced by: '<S1084>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_f (((uint8_T)1U))

/* Computed Parameter: rtCP_true2_Value
 * Referenced by: '<S1438>/true2'
 */
#define rtCP_true2_Value               (((uint8_T)1U))

/* Expression: uint8([1:4])
 * Referenced by: '<S1458>/Indices'
 */
#define rtCP_Indices_Value_EL_0        (((uint8_T)1U))
#define rtCP_Indices_Value_EL_1        (((uint8_T)2U))
#define rtCP_Indices_Value_EL_2        (((uint8_T)3U))
#define rtCP_Indices_Value_EL_3        (((uint8_T)4U))

/* Computed Parameter: rtCP_true2_Value_o
 * Referenced by: '<S1767>/true2'
 */
#define rtCP_true2_Value_o             (((uint8_T)1U))

/* Expression: uint8([1:4])
 * Referenced by: '<S1787>/Indices'
 */
#define rtCP_Indices_Value_l_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_l_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_l_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_l_EL_3      (((uint8_T)4U))

/* Expression: uint8([1:4])
 * Referenced by: '<S2134>/Indices'
 */
#define rtCP_Indices_Value_k_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_k_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_k_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_k_EL_3      (((uint8_T)4U))

/* Computed Parameter: rtCP_true2_Value_d
 * Referenced by: '<S2334>/true2'
 */
#define rtCP_true2_Value_d             (((uint8_T)1U))

/* Expression: uint8([1:4])
 * Referenced by: '<S2354>/Indices'
 */
#define rtCP_Indices_Value_lp_EL_0     (((uint8_T)1U))
#define rtCP_Indices_Value_lp_EL_1     (((uint8_T)2U))
#define rtCP_Indices_Value_lp_EL_2     (((uint8_T)3U))
#define rtCP_Indices_Value_lp_EL_3     (((uint8_T)4U))

/* Computed Parameter: rtCP_FixPtConstant_Value_k
 * Referenced by: '<S1235>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_k     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_p
 * Referenced by: '<S1251>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_p     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_du
 * Referenced by: '<S1260>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_du    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_g
 * Referenced by: '<S1261>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_g     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_f
 * Referenced by: '<S1267>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_f     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_p3
 * Referenced by: '<S1271>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_p3    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_m
 * Referenced by: '<S1276>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_m     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_o
 * Referenced by: '<S1279>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_o     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_bd
 * Referenced by: '<S1301>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_bd    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_c
 * Referenced by: '<S1302>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_c     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_n
 * Referenced by: '<S1315>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_n     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_mv
 * Referenced by: '<S1316>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_mv    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_c4
 * Referenced by: '<S1325>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_c4    (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_ih
 * Referenced by: '<S1357>/Constant'
 */
#define rtCP_Constant_Value_ih         (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_pb
 * Referenced by: '<S1360>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_pb    (((uint8_T)0U))

/* Expression: uint8([1:4])
 * Referenced by: '<S2112>/Indices'
 */
#define rtCP_Indices_Value_f_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_f_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_f_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_f_EL_3      (((uint8_T)4U))

/* Expression: uint8(150)
 * Referenced by: '<S2107>/Constant1'
 */
#define rtCP_Constant1_Value_ozb       (((uint8_T)150U))

/* Computed Parameter: rtCP_FixPtConstant_Value_gk
 * Referenced by: '<S2153>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_gk    (((uint8_T)0U))

/* Expression: uint8([1:4])
 * Referenced by: '<S2289>/Indices'
 */
#define rtCP_Indices_Value_m_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_m_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_m_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_m_EL_3      (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant4_Value_iv
 * Referenced by: '<S33>/Constant4'
 */
#define rtCP_Constant4_Value_iv        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant5_Value_iyg
 * Referenced by: '<S33>/Constant5'
 */
#define rtCP_Constant5_Value_iyg       (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant6_Value_nc
 * Referenced by: '<S33>/Constant6'
 */
#define rtCP_Constant6_Value_nc        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant7_Value_ol
 * Referenced by: '<S33>/Constant7'
 */
#define rtCP_Constant7_Value_ol        (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtConstant_Value_a
 * Referenced by: '<S38>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_a     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_f4
 * Referenced by: '<S39>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_f4    (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_jrf
 * Referenced by: '<S193>/Constant'
 */
#define rtCP_Constant_Value_jrf        (((uint8_T)16U))

/* Computed Parameter: rtCP_Constant1_Value_fo
 * Referenced by: '<S193>/Constant1'
 */
#define rtCP_Constant1_Value_fo        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant10_Value_oy
 * Referenced by: '<S193>/Constant10'
 */
#define rtCP_Constant10_Value_oy       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant2_Value_hk
 * Referenced by: '<S193>/Constant2'
 */
#define rtCP_Constant2_Value_hk        (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant3_Value_aj
 * Referenced by: '<S193>/Constant3'
 */
#define rtCP_Constant3_Value_aj        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant8_Value_kc
 * Referenced by: '<S193>/Constant8'
 */
#define rtCP_Constant8_Value_kc        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant9_Value_ph
 * Referenced by: '<S193>/Constant9'
 */
#define rtCP_Constant9_Value_ph        (((uint8_T)8U))

/* Expression: uint8(0)
 * Referenced by: '<S321>/FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca7'
 */
#define rtCP_FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca7_Value (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_jdi
 * Referenced by: '<S313>/Constant'
 */
#define rtCP_Constant_Value_jdi        (((uint8_T)16U))

/* Expression: uint8(170)
 * Referenced by: '<S48>/Constant'
 */
#define rtCP_Constant_Value_ox4        (((uint8_T)170U))

/* Expression: uint8(170)
 * Referenced by: '<S48>/Constant1'
 */
#define rtCP_Constant1_Value_mmf       (((uint8_T)170U))

/* Expression: uint8(0)
 * Referenced by: '<S406>/Constant3'
 */
#define rtCP_Constant3_Value_h2        (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_ge
 * Referenced by: '<S488>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_ge    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_mw
 * Referenced by: '<S495>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_mw    (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_jpo
 * Referenced by: '<S564>/Constant'
 */
#define rtCP_Constant_Value_jpo        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant1_Value_g21
 * Referenced by: '<S564>/Constant1'
 */
#define rtCP_Constant1_Value_g21       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_ojy
 * Referenced by: '<S553>/Constant'
 */
#define rtCP_Constant_Value_ojy        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_g32
 * Referenced by: '<S462>/Constant'
 */
#define rtCP_Constant_Value_g32        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_at1
 * Referenced by: '<S463>/Constant'
 */
#define rtCP_Constant_Value_at1        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant1_Value_ep
 * Referenced by: '<S630>/Constant1'
 */
#define rtCP_Constant1_Value_ep        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_hyk
 * Referenced by: '<S610>/Constant'
 */
#define rtCP_Constant_Value_hyk        (((uint8_T)1U))

/* Expression: uint8(0)
 * Referenced by: '<S610>/Constant1'
 */
#define rtCP_Constant1_Value_goe       (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_e
 * Referenced by: '<S651>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_e     (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S602>/Constant1'
 */
#define rtCP_Constant1_Value_jce       (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S602>/Constant2'
 */
#define rtCP_Constant2_Value_gb4       (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S602>/Constant3'
 */
#define rtCP_Constant3_Value_fs4       (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_c3
 * Referenced by: '<S692>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_c3    (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S604>/Constant1'
 */
#define rtCP_Constant1_Value_dv        (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S604>/Constant2'
 */
#define rtCP_Constant2_Value_ca        (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S604>/Constant3'
 */
#define rtCP_Constant3_Value_d2        (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_p0
 * Referenced by: '<S719>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_p0    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_oo
 * Referenced by: '<S721>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_oo    (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S734>/Constant1'
 */
#define rtCP_Constant1_Value_nxr       (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S734>/Constant2'
 */
#define rtCP_Constant2_Value_bv        (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S734>/Constant3'
 */
#define rtCP_Constant3_Value_aon       (((uint8_T)0U))

/* Expression: uint8(2)
 * Referenced by: '<S763>/Constant3'
 */
#define rtCP_Constant3_Value_cza       (((uint8_T)2U))

/* Expression: uint8(2)
 * Referenced by: '<S764>/Constant3'
 */
#define rtCP_Constant3_Value_cyl       (((uint8_T)2U))

/* Computed Parameter: rtCP_FixPtConstant_Value_eo
 * Referenced by: '<S771>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_eo    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_e0
 * Referenced by: '<S1007>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_e0    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_n2
 * Referenced by: '<S1014>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_n2    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_bz
 * Referenced by: '<S1021>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_bz    (((uint8_T)0U))

/* Computed Parameter: rtCP_Zero_Value_f
 * Referenced by: '<S984>/Zero'
 */
#define rtCP_Zero_Value_f              (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_l2
 * Referenced by: '<S1029>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_l2    (((uint8_T)0U))

/* Computed Parameter: rtCP_Zero_Value_fv
 * Referenced by: '<S986>/Zero'
 */
#define rtCP_Zero_Value_fv             (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_kw
 * Referenced by: '<S1064>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_kw    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_nv
 * Referenced by: '<S1066>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_nv    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_hv
 * Referenced by: '<S1068>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_hv    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_cu
 * Referenced by: '<S1070>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_cu    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_br
 * Referenced by: '<S1075>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_br    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_o0
 * Referenced by: '<S1086>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_o0    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_fh
 * Referenced by: '<S1091>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_fh    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_f1
 * Referenced by: '<S1092>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_f1    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_hf
 * Referenced by: '<S1093>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_hf    (((uint8_T)0U))

/* Computed Parameter: rtCP_true2_Value_b
 * Referenced by: '<S2649>/true2'
 */
#define rtCP_true2_Value_b             (((uint8_T)1U))

/* Expression: uint8(3)
 * Referenced by: '<S2608>/Constant37'
 */
#define rtCP_Constant37_Value          (((uint8_T)3U))

/* Computed Parameter: rtCP_FixPtConstant_Value_c2
 * Referenced by: '<S2704>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_c2    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_h2
 * Referenced by: '<S2705>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_h2    (((uint8_T)0U))

/* Computed Parameter: rtCP_true2_Value_ba
 * Referenced by: '<S2785>/true2'
 */
#define rtCP_true2_Value_ba            (((uint8_T)1U))

/* Computed Parameter: rtCP_true2_Value_h
 * Referenced by: '<S2794>/true2'
 */
#define rtCP_true2_Value_h             (((uint8_T)1U))

/* Expression: uint8([1:4])
 * Referenced by: '<S3186>/Indices'
 */
#define rtCP_Indices_Value_g_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_g_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_g_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_g_EL_3      (((uint8_T)4U))

/* Expression: uint8([1:4])
 * Referenced by: '<S3746>/Indices'
 */
#define rtCP_Indices_Value_e_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_e_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_e_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_e_EL_3      (((uint8_T)4U))

/* Expression: uint8(3)
 * Referenced by: '<S2609>/Constant37'
 */
#define rtCP_Constant37_Value_k        (((uint8_T)3U))

/* Computed Parameter: rtCP_FixPtConstant_Value_n1
 * Referenced by: '<S4389>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_n1    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_cz
 * Referenced by: '<S4390>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_cz    (((uint8_T)0U))

/* Expression: uint8([1:4])
 * Referenced by: '<S4871>/Indices'
 */
#define rtCP_Indices_Value_j_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_j_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_j_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_j_EL_3      (((uint8_T)4U))

/* Expression: uint8([1:4])
 * Referenced by: '<S5431>/Indices'
 */
#define rtCP_Indices_Value_n_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_n_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_n_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_n_EL_3      (((uint8_T)4U))

/* Expression: uint8(3)
 * Referenced by: '<S5988>/Constant55'
 */
#define rtCP_Constant55_Value          (((uint8_T)3U))

/* Expression: uint8(3)
 * Referenced by: '<S5989>/Constant55'
 */
#define rtCP_Constant55_Value_e        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant_Value_ffg
 * Referenced by: '<S6009>/Constant'
 */
#define rtCP_Constant_Value_ffg        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_lxr
 * Referenced by: '<S6010>/Constant'
 */
#define rtCP_Constant_Value_lxr        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_kqsl
 * Referenced by: '<S5998>/Constant'
 */
#define rtCP_Constant_Value_kqsl       (((uint8_T)1U))

/* Expression: uint8(0)
 * Referenced by: '<S2611>/Constant1'
 */
#define rtCP_Constant1_Value_on        (((uint8_T)0U))

/* Expression: const
 * Referenced by: '<S6021>/Constant'
 */
#define rtCP_Constant_Value_dhs        (((uint8_T)4U))

/* Expression: const
 * Referenced by: '<S6022>/Constant'
 */
#define rtCP_Constant_Value_eea        (((uint8_T)2U))

/* Expression: const
 * Referenced by: '<S6023>/Constant'
 */
#define rtCP_Constant_Value_p1g        (((uint8_T)3U))

/* Computed Parameter: rtCP_FixPtConstant_Value_p2
 * Referenced by: '<S6121>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_p2    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_mx
 * Referenced by: '<S6133>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_mx    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_a4
 * Referenced by: '<S6134>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_a4    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_do
 * Referenced by: '<S6137>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_do    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_gr
 * Referenced by: '<S6146>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_gr    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_m3
 * Referenced by: '<S6147>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_m3    (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_pam
 * Referenced by: '<S6158>/Constant'
 */
#define rtCP_Constant_Value_pam        (((uint8_T)5U))

/* Computed Parameter: rtCP_FixPtConstant_Value_hi
 * Referenced by: '<S6205>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_hi    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_ps
 * Referenced by: '<S6206>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_ps    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_pa
 * Referenced by: '<S6207>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_pa    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_hd
 * Referenced by: '<S6252>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_hd    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_ev
 * Referenced by: '<S6253>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_ev    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_pl
 * Referenced by: '<S6254>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_pl    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_j
 * Referenced by: '<S6265>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_j     (((uint8_T)0U))

/* Expression: uint8(3)
 * Referenced by: '<S6277>/Constant'
 */
#define rtCP_Constant_Value_mqx        (((uint8_T)3U))

/* Expression: uint8(2)
 * Referenced by: '<S6277>/Constant1'
 */
#define rtCP_Constant1_Value_h4        (((uint8_T)2U))

/* Expression: uint8(1)
 * Referenced by: '<S6277>/Constant2'
 */
#define rtCP_Constant2_Value_fx        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_gxip
 * Referenced by: '<S6314>/Constant'
 */
#define rtCP_Constant_Value_gxip       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_jyd
 * Referenced by: '<S6283>/Constant'
 */
#define rtCP_Constant_Value_jyd        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant1_Value_ol
 * Referenced by: '<S6283>/Constant1'
 */
#define rtCP_Constant1_Value_ol        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant2_Value_fq
 * Referenced by: '<S6283>/Constant2'
 */
#define rtCP_Constant2_Value_fq        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant3_Value_a5
 * Referenced by: '<S6283>/Constant3'
 */
#define rtCP_Constant3_Value_a5        (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_ll
 * Referenced by: '<S6349>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_ll    (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant1_Value_pw
 * Referenced by: '<S6350>/Constant1'
 */
#define rtCP_Constant1_Value_pw        (((uint8_T)7U))

/* Computed Parameter: rtCP_Constant2_Value_h0
 * Referenced by: '<S6350>/Constant2'
 */
#define rtCP_Constant2_Value_h0        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant3_Value_jv
 * Referenced by: '<S6350>/Constant3'
 */
#define rtCP_Constant3_Value_jv        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant4_Value_gz
 * Referenced by: '<S6350>/Constant4'
 */
#define rtCP_Constant4_Value_gz        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant5_Value_h1
 * Referenced by: '<S6350>/Constant5'
 */
#define rtCP_Constant5_Value_h1        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant6_Value_mu
 * Referenced by: '<S6350>/Constant6'
 */
#define rtCP_Constant6_Value_mu        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6337>/Constant10'
 */
#define rtCP_Constant10_Value_g        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6337>/Constant12'
 */
#define rtCP_Constant12_Value_c        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6337>/Constant16'
 */
#define rtCP_Constant16_Value_m        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6337>/Constant17'
 */
#define rtCP_Constant17_Value_g        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6337>/Constant19'
 */
#define rtCP_Constant19_Value_i        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6337>/Constant2'
 */
#define rtCP_Constant2_Value_oo        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_h0z
 * Referenced by: '<S6360>/Constant'
 */
#define rtCP_Constant_Value_h0z        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant1_Value_m0
 * Referenced by: '<S6360>/Constant1'
 */
#define rtCP_Constant1_Value_m0        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant2_Value_lvy
 * Referenced by: '<S6360>/Constant2'
 */
#define rtCP_Constant2_Value_lvy       (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant6_Value_n5
 * Referenced by: '<S6360>/Constant6'
 */
#define rtCP_Constant6_Value_n5        (((uint8_T)2U))

/* Expression: const
 * Referenced by: '<S6378>/Constant'
 */
#define rtCP_Constant_Value_nab        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant1_Value_atl
 * Referenced by: '<S6365>/Constant1'
 */
#define rtCP_Constant1_Value_atl       (((uint8_T)7U))

/* Computed Parameter: rtCP_Constant2_Value_db
 * Referenced by: '<S6365>/Constant2'
 */
#define rtCP_Constant2_Value_db        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant3_Value_ky
 * Referenced by: '<S6365>/Constant3'
 */
#define rtCP_Constant3_Value_ky        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant4_Value_hc
 * Referenced by: '<S6365>/Constant4'
 */
#define rtCP_Constant4_Value_hc        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant5_Value_d3
 * Referenced by: '<S6365>/Constant5'
 */
#define rtCP_Constant5_Value_d3        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant6_Value_jk
 * Referenced by: '<S6365>/Constant6'
 */
#define rtCP_Constant6_Value_jk        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant2_Value_d0
 * Referenced by: '<S6398>/Constant2'
 */
#define rtCP_Constant2_Value_d0        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant44_Value_c
 * Referenced by: '<S6398>/Constant44'
 */
#define rtCP_Constant44_Value_c        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant1_Value_iai
 * Referenced by: '<S6397>/Constant1'
 */
#define rtCP_Constant1_Value_iai       (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant10_Value_m
 * Referenced by: '<S6397>/Constant10'
 */
#define rtCP_Constant10_Value_m        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant2_Value_kj
 * Referenced by: '<S6397>/Constant2'
 */
#define rtCP_Constant2_Value_kj        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant44_Value_b
 * Referenced by: '<S6397>/Constant44'
 */
#define rtCP_Constant44_Value_b        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_poe
 * Referenced by: '<S6419>/Constant'
 */
#define rtCP_Constant_Value_poe        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_cvd
 * Referenced by: '<S6432>/Constant'
 */
#define rtCP_Constant_Value_cvd        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_oq1
 * Referenced by: '<S6470>/Constant'
 */
#define rtCP_Constant_Value_oq1        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_ouv
 * Referenced by: '<S6487>/Constant'
 */
#define rtCP_Constant_Value_ouv        (((uint8_T)11U))

/* Expression: const
 * Referenced by: '<S6489>/Constant'
 */
#define rtCP_Constant_Value_dby        (((uint8_T)2U))

/* Expression: uint8(1)
 * Referenced by: '<S6001>/Delay'
 */
#define rtCP_Delay_InitialCondition_ff (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_kc
 * Referenced by: '<S6121>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_kc (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_kv
 * Referenced by: '<S6137>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_kv (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_l
 * Referenced by: '<S6146>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_l (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_p
 * Referenced by: '<S6147>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_p (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_g
 * Referenced by: '<S6133>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_g (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_b
 * Referenced by: '<S6134>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_b (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_n
 * Referenced by: '<S6207>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_n (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_i
 * Referenced by: '<S6205>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_i (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_pq
 * Referenced by: '<S6206>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_pq (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_bo
 * Referenced by: '<S1075>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_bo (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_l3
 * Referenced by: '<S2704>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_l3 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_ln
 * Referenced by: '<S1066>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_ln (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_oi
 * Referenced by: '<S1086>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_oi (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_fg
 * Referenced by: '<S2705>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_fg (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_c
 * Referenced by: '<S1070>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_c (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_e
 * Referenced by: '<S1235>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_e (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_ce
 * Referenced by: '<S1251>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_ce (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_km
 * Referenced by: '<S1279>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_km (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_dm
 * Referenced by: '<S1271>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_dm (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_dw
 * Referenced by: '<S1260>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_dw (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_l5
 * Referenced by: '<S1261>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_l5 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_cl
 * Referenced by: '<S1267>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_cl (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_pt
 * Referenced by: '<S1325>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_pt (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_pn
 * Referenced by: '<S1301>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_pn (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_j
 * Referenced by: '<S1302>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_j (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_it
 * Referenced by: '<S1315>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_it (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_m
 * Referenced by: '<S1316>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_m (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_cg
 * Referenced by: '<S1276>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_cg (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_kw
 * Referenced by: '<S1360>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_kw (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_l1
 * Referenced by: '<S6254>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_l1 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_mp
 * Referenced by: '<S6252>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_mp (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_lz
 * Referenced by: '<S6253>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_lz (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_fb
 * Referenced by: '<S4389>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_fb (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_bd
 * Referenced by: '<S4390>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_bd (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_nm
 * Referenced by: '<S2153>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_nm (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_h
 * Referenced by: '<S1068>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_h (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_f1
 * Referenced by: '<S1093>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_f1 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_hi
 * Referenced by: '<S1091>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_hi (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_h1
 * Referenced by: '<S1092>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_h1 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_pe
 * Referenced by: '<S771>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_pe (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_b3
 * Referenced by: '<S6265>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_b3 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_dx
 * Referenced by: '<S721>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_dx (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_ma
 * Referenced by: '<S719>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_ma (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_fn
 * Referenced by: '<S692>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_fn (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_lk
 * Referenced by: '<S651>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_lk (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_pen
 * Referenced by: '<S488>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_pen (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_cea
 * Referenced by: '<S495>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_cea (((uint8_T)1U))

/* Expression: BitMask
 * Referenced by: '<S227>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask (((uint8_T)2U))

/* Expression: BitMask
 * Referenced by: '<S229>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_n (((uint8_T)4U))

/* Expression: BitMask
 * Referenced by: '<S231>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_f (((uint8_T)8U))

/* Expression: BitMask
 * Referenced by: '<S233>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_m (((uint8_T)16U))

/* Expression: BitMask
 * Referenced by: '<S235>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_nd (((uint8_T)32U))

/* Expression: BitMask
 * Referenced by: '<S237>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_o (((uint8_T)64U))

/* Expression: BitMask
 * Referenced by: '<S239>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_j (((uint8_T)128U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_m0
 * Referenced by: '<S38>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_m0 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_pf
 * Referenced by: '<S39>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_pf (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_iz
 * Referenced by: '<S1021>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_iz (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_bp
 * Referenced by: '<S1007>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_bp (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_om
 * Referenced by: '<S1014>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_om (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_go
 * Referenced by: '<S1029>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_go (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_g0
 * Referenced by: '<S1064>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_g0 (((uint8_T)1U))

/* Expression: BitMask
 * Referenced by: '<S6435>/Bitwise Operator2'
 */
#define rtCP_BitwiseOperator2_BitMask  (((uint8_T)4U))

/* Expression: BitMask
 * Referenced by: '<S6435>/Bitwise Operator1'
 */
#define rtCP_BitwiseOperator1_BitMask  (((uint8_T)2U))

/* Expression: BitMask
 * Referenced by: '<S6435>/Bitwise Operator'
 */
#define rtCP_BitwiseOperator_BitMask   (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_ow
 * Referenced by: '<S6349>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_ow (((uint8_T)1U))

extern void LongSafe_SWC_CorrectEuclideanParameters(real32_T rtu_A, real32_T
  rtu_Speed, real32_T rtu_HeadingAngle, real32_T rtu_Curvature, real32_T
  *rty_VLgt, real32_T *rty_VLat, real32_T *rty_ALgt, real32_T *rty_ALat);
extern void LongSafe_SWC_BeyondLastSegment(real32_T rtu_PathCoeff, real32_T
  rtu_PathCoeff_p, real32_T rtu_PathCoeff_f, real32_T rtu_PathCoeff_o, real32_T
  rtu_Distance, real32_T rtu_SegmentStart, real32_T *rty_SegCoeff, real32_T
  *rty_SegCoeff_p, real32_T *rty_SegCoeff_f, real32_T *rty_SegCoeff_o, real32_T *
  rty_PosInSegment);
extern void LongSafe_SWC_WithinThirdSegment(real32_T rtu_PathCoeff, real32_T
  rtu_PathCoeff_n, real32_T rtu_PathCoeff_k, real32_T rtu_PathCoeff_b, real32_T
  rtu_Distance, real32_T rtu_SegmentStart, real32_T *rty_SegCoeff, real32_T
  *rty_SegCoeff_n, real32_T *rty_SegCoeff_k, real32_T *rty_SegCoeff_b, real32_T *
  rty_PosInSegment);
extern void LongSafe_SWC_WithinSecondSegment(real32_T rtu_PathCoeff, real32_T
  rtu_PathCoeff_d, real32_T rtu_PathCoeff_i, real32_T rtu_PathCoeff_l, real32_T
  rtu_Distance, real32_T rtu_SegmentStart, real32_T *rty_SegCoeff, real32_T
  *rty_SegCoeff_d, real32_T *rty_SegCoeff_i, real32_T *rty_SegCoeff_l, real32_T *
  rty_PosInSegment);
extern void LongSafe_SWC_WithinFirstSegment(real32_T rtu_PathCoeff, real32_T
  rtu_PathCoeff_p, real32_T rtu_PathCoeff_f, real32_T rtu_PathCoeff_b, real32_T
  rtu_Distance, real32_T *rty_SegCoeff, real32_T *rty_SegCoeff_p, real32_T
  *rty_SegCoeff_f, real32_T *rty_SegCoeff_b, real32_T *rty_PosInSegment);
extern void LongSafe_SWC_ComputeCurvatureBasedControlPoint(real32_T
  rtu_PositionLongitudinal, real32_T rtu_PositionLateral, real32_T rtu_V,
  real32_T rtu_A, real32_T rtu_HeadingAngle, real32_T rtu_Curvature, real32_T
  rtu_CurvatureRate, boolean_T rtu_StopsWithinSegment, real32_T
  rtu_LongitudinalStoppingDistance, real32_T rtu_LateralStoppingDistance,
  real32_T *rty_P3Longitudinal, real32_T *rty_P3Lateral);
extern real32_T LongSafe_SWC_TimeCountUp(boolean_T rtu_r, real32_T rtu_ts,
  DW_TimeCountUp_LongSafe_SWC_T *localDW);
extern real32_T LongSafe_SWC_DSE_TimeCountUp(boolean_T rtu_reset, real32_T
  rtu_increment, DW_DSE_TimeCountUp_LongSafe_SWC_T *localDW);
extern real32_T LongSafe_SWC_DSE_CalcPredDrvrDecel(real32_T rtu_VehicleSpeed,
  real32_T rtu_Slope, real32_T rtu_Offset, real32_T
  rtu_PredictedAccelerationLimit);
extern real32_T LongSafe_SWC_DSE_CalcPredDrvrDecel_d(real32_T rtu_VehicleSpeed,
  real32_T rtu_Slope, real32_T rtu_Offset, real32_T
  rtu_predictedDecelerationLimit);
extern void LongSafe_SWC_PositionAndDerivative(real32_T rtu_P0, real32_T rtu_P1,
  real32_T rtu_P2, real32_T rtu_P3, real32_T rtu_tau, real32_T *rty_x, real32_T *
  rty_dx);
extern void LongSafe_SWC_ExtractVelocitiesAtStartOfSegments(const
  PahEstimnGroup1Vcc rtu_PathEstimn[4], boolean_T rty_SpeedValid[4], real32_T
  rty_SegmentVelocitiesX[4], real32_T rty_SegmentVelocitiesY[4]);
extern void LongSafe_SWC_FindValidIndex(uint8_T rtu_SegmentIndex, const
  boolean_T rtu_SpeedValid[4], uint8_T *rty_ValidSegmentIndex);
extern void LongSafe_SWC_FindValidVelocityVector(boolean_T
  rtu_CurrentVelocityValid, uint8_T rtu_ValidSegmentIndex, real32_T
  rtu_CurrentVelocityX, real32_T rtu_CurrentVelocityY, const real32_T
  rtu_SegmentVelocitiesX[4], const real32_T rtu_SegmentVelocitiesY[4], real32_T *
  rty_ValidVelocityY, real32_T *rty_ValidVelocityX);
extern void LongSafe_SWC_PositionAndDerivative_p(real32_T rtu_P0, real32_T
  rtu_P1, real32_T rtu_P2, real32_T rtu_P3, real32_T rtu_tau, real32_T *rty_x,
  real32_T *rty_dx);
extern void LongSafe_SWC_ForEachSegmentInPahEstimn(const PahEstimnGroup1Vcc
  rtu_PahEstimn[4], real32_T rtu_Time, boolean_T rty_TimeWithinSegment[4], const
  ConstB_ForEachSegmentInPahEstimn_LongSafe_SWC_T *localC);
extern void LongSafe_SWC_NoPrediction(const BoundingBox0 *rtu_BoundingBox, const
  ObjGroup1Vcc *rtu_Obj, real32_T *rty_PredObjMotion, real32_T
  *rty_PredObjMotion_o, real32_T *rty_PredObjMotion_d, real32_T
  *rty_PredObjMotion_d0, real32_T *rty_PredObjMotion_e, real32_T
  *rty_PredObjMotion_g, real32_T *rty_PredObjAgDir);
extern void LongSafe_SWC_CircularPrediction(const ObjGroup1Vcc *rtu_Obj, const
  SafetyMarginData *rtu_SafetyMarginData, real32_T rtu_PredictionTime, const
  BoundingBox0 *rtu_BoundingBox, real32_T *rty_PredObjAgDir, real32_T
  *rty_PredObjMotion, real32_T *rty_PredObjMotion_m, real32_T
  *rty_PredObjMotion_l, real32_T *rty_PredObjMotion_g, real32_T
  *rty_PredObjMotion_h, real32_T *rty_PredObjMotion_p, const
  ConstB_CircularPrediction_LongSafe_SWC_T *localC);
extern void LongSafe_SWC_LinearPrediction(const ObjGroup1Vcc *rtu_Obj, const
  MotionType0 *rtu_MotionType, const SafetyMarginData *rtu_SafetyMarginData,
  real32_T rtu_PredictionTime, real32_T *rty_PredObjMotion, real32_T
  *rty_PredObjMotion_a, real32_T *rty_PredObjMotion_g, real32_T
  *rty_PredObjMotion_i, real32_T *rty_PredObjMotion_aw, real32_T
  *rty_PredObjMotion_h, real32_T *rty_PredObjAgDir);
extern void LongSafe_SWC_StationaryObject(const BoundingBox0 *rtu_BoundingBox,
  real32_T rtu_PredictedHeadingObj, real32_T rtu_PredictedHeadingHost, real32_T *
  rty_SinRelativeRotation, real32_T *rty_CosRelativeRotation, real32_T
  *rty_RelativeHeading);
extern void LongSafe_SWC_MovingObject(real32_T rtu_PredictedHeadingHost,
  real32_T rtu_PredictedHeadingObj, boolean_T rtu_SideIsClosest, real32_T
  *rty_SinRelativeRotation, real32_T *rty_CosRelativeRotation, real32_T
  *rty_RelativeHeading, const ConstB_MovingObject_LongSafe_SWC_T *localC);
extern void LongSafe_SWC_QuadraticEquationSolver(real32_T rtu_a, real32_T rtu_b,
  real32_T rtu_c, real32_T rty_x[2], boolean_T *rty_SolutionFound);
extern void LongSafe_SWC_LeftClosest(real32_T rtu_VLatRel, real32_T rtu_ALatRel,
  real32_T rtu_EdgeDistanceLeftClosest, real32_T rtu_EdgeDistanceRightClosest,
  real32_T *rty_TimeToIntersection, const ConstB_LeftClosest_LongSafe_SWC_T
  *localC);
extern void LongSafe_SWC_RightClosest(real32_T rtu_VLatRel, real32_T rtu_ALatRel,
  real32_T rtu_EdgeDistanceLeftClosest, real32_T rtu_EdgeDistanceRightClosest,
  real32_T *rty_TimeToIntersection, const ConstB_RightClosest_LongSafe_SWC_T
  *localC);
extern void LongSafe_SWC_ObjectIsBraking(real32_T rtu_PosnLgtRelFrnt, real32_T
  rtu_VLgtSelf, real32_T rtu_VLgtObj, real32_T rtu_ALgtObj, real32_T
  *rty_ALgtRqrd, const ConstB_ObjectIsBraking_LongSafe_SWC_T *localC);
extern void LongSafe_SWC_ObjectIsNotBraking(boolean_T rtu_MovingOncoming,
  real32_T rtu_PosnLgtRelFrnt, real32_T rtu_VLgtSelf, real32_T rtu_VLgtObj,
  real32_T rtu_ALgtObj, real32_T *rty_ALgtRqrd, const
  ConstB_ObjectIsNotBraking_LongSafe_SWC_T *localC);
extern void LongSafe_SWC_SimpleLateralAccelerationEstimatorForIntv_Disable
  (uint32_T *rty_Idn, real32_T *rty_ALatRqrd, real32_T *rty_PosnLatRelAtTTR,
   real32_T *rty_ProjectedLengthSideLat);
extern void LongSafe_SWC_SimpleLateralAccelerationEstimatorForIntv(const
  ObjGroup1Vcc *rtu_Obj, const SafetyMarginData *rtu_SafetyMarginData, real32_T
  rtu_OffsLat, boolean_T rtu_ObjectIsVehicle, real32_T rtu_TimeToReach, const
  BoundingBox0 *rtu_BoundingBox, const DynCalPrm *rtu_DynCalPrm, const
  VehSelf1Vcc *rtu_VehSelf, uint32_T *rty_Idn, real32_T *rty_ALatRqrd, real32_T *
  rty_PosnLatRelAtTTR, real32_T *rty_ProjectedLengthSideLat);
extern void LongSafe_SWC_LeftClosest_c(real32_T rtu_VLatRel, real32_T
  rtu_ALatRel, real32_T rtu_EdgeDistanceLeftClosest, real32_T
  rtu_EdgeDistanceRightClosest, real32_T *rty_TimeToIntersection, const
  ConstB_LeftClosest_LongSafe_SWC_d_T *localC);
extern void LongSafe_SWC_RightClosest_i(real32_T rtu_VLatRel, real32_T
  rtu_ALatRel, real32_T rtu_EdgeDistanceLeftClosest, real32_T
  rtu_EdgeDistanceRightClosest, real32_T *rty_TimeToIntersection, const
  ConstB_RightClosest_LongSafe_SWC_k_T *localC);
extern void LongSafe_SWC_MovingOncomingVehicleWhenActive(const ObjGroup1Vcc
  *rtu_Obj, boolean_T rtu_TextScene, BoundingBox0 *rty_BoundingBox, const
  ConstB_MovingOncomingVehicleWhenActive_LongSafe_SWC_T *localC);
extern void LongSafe_SWC_StationaryVehicle(const ObjGroup1Vcc *rtu_Obj,
  BoundingBox0 *rty_BoundingBox, const ConstB_StationaryVehicle_LongSafe_SWC_T
  *localC);
extern void LongSafe_SWC_MovingVehicle(const ObjGroup1Vcc *rtu_Obj, BoundingBox0
  *rty_BoundingBox, const ConstB_MovingVehicle_LongSafe_SWC_T *localC);
extern void LongSafe_SWC_MovgToSelf(ObjMtnPat1Vcc *rty_MovgToSelf);
extern void LongSafe_SWC_Staty(ObjMtnPat1Vcc *rty_Staty);
extern void LongSafe_SWC_FromSelf(ObjMtnPat1Vcc *rty_FromSelf);
extern void LongSafe_SWC_Ukwn(ObjMtnPat1Vcc *rty_Ukwn);
extern void LongSafe_SWC_MotionPat(real32_T rtu_VLgt, real32_T rtu_Speed,
  real32_T rtu_VLat, boolean_T rtu_CPTA_LF, boolean_T rtu_CPTA_LN, boolean_T
  rtu_CPTA_RF, boolean_T rtu_CSTA_RN, ObjMtnPat1Vcc *rty_y);
extern void LongSafe_SWC_MATLABFunction(real32_T rtu_u, boolean_T *rty_out);
extern void LongSafe_SWC_MATLABFunction1(ObjClassn3Vcc rtu_ObjTyp, real32_T
  rtu_VLgt, real32_T *rty_comp);
extern void LongSafe_SWC_MATLABFunction2(real32_T rtu_u, boolean_T *rty_out);
extern void LongSafe_SWC_MATLABFunction_g(boolean_T rtu_EnPosnLatLimit, real32_T
  rtu_PosnLat, real32_T rtu_KeAEB_m_CCRS_PosnLatLimit, real32_T
  *rty_PosnLat_Limit);
extern void LongSafe_SWC_NoPrediction_j(real32_T rtu_HeadingStationary, const
  ObjGroup1Vcc *rtu_Obj, real32_T *rty_PosnObjAtTTR, real32_T
  *rty_PosnObjAtTTR_e, real32_T *rty_PosnObjAtTTR_h, real32_T
  *rty_PosnObjAtTTR_p, real32_T *rty_PosnObjAtTTR_px, real32_T
  *rty_PosnObjAtTTR_e1, real32_T *rty_PosnObjAtTTR_l, real32_T
  *rty_PosnObjAtTTR_hn, real32_T *rty_PosnObjAtTTR_pl, real32_T
  *rty_PosnObjAtTTR_g, real32_T *rty_PosnObjAtTTR_lk, real32_T
  *rty_PosnObjAtTTR_j, real32_T *rty_PosnObjAtTTR_j5, real32_T
  *rty_PosnObjAtTTR_gg, real32_T *rty_PosnObjAtTTR_c, real32_T
  *rty_PosnObjAtTTR_a, real32_T *rty_PosnObjAtTTR_b, real32_T
  *rty_PosnObjAtTTR_p1, real32_T *rty_PosnObjAtTTR_n, real32_T
  *rty_PosnObjAtTTR_px5, real32_T *rty_PosnObjAtTTR_k, real32_T
  *rty_PosnObjAtTTR_kr, real32_T *rty_PosnObjAtTTR_cr, real32_T
  *rty_PosnObjAtTTR_m, real32_T *rty_PosnObjAtTTR_a5, real32_T
  *rty_AObjIfManoeuvering, real32_T *rty_AObjIfManoeuvering_b, real32_T
  *rty_AObjIfManoeuvering_h, real32_T *rty_AObjIfManoeuvering_m, real32_T
  *rty_AObjIfManoeuvering_a, real32_T *rty_AObjIfManoeuvering_k, real32_T
  *rty_AObjIfManoeuvering_l, real32_T *rty_AObjIfManoeuvering_n, real32_T
  *rty_AObjIfManoeuvering_as, real32_T *rty_AObjIfManoeuvering_p);
extern void LongSafe_SWC_CircularPrediction_n(const BoundingBox0
  *rtu_BoundingBox, const ObjGroup1Vcc *rtu_Obj, real32_T rtu_TTR, real32_T
  rtu_AObjAvoidance, real32_T rtu_AObjAvoidance_n, real32_T rtu_AObjAvoidance_j,
  real32_T *rty_PosnObjAtTTR, real32_T *rty_PosnObjAtTTR_g, real32_T
  *rty_PosnObjAtTTR_o, real32_T *rty_PosnObjAtTTR_d, real32_T
  *rty_PosnObjAtTTR_n, real32_T *rty_PosnObjAtTTR_j, real32_T
  *rty_PosnObjAtTTR_i, real32_T *rty_PosnObjAtTTR_j4, real32_T
  *rty_PosnObjAtTTR_e, real32_T *rty_PosnObjAtTTR_ev, real32_T
  *rty_PosnObjAtTTR_m, real32_T *rty_PosnObjAtTTR_c, real32_T
  *rty_PosnObjAtTTR_na, real32_T *rty_PosnObjAtTTR_m2, real32_T
  *rty_PosnObjAtTTR_l, real32_T *rty_PosnObjAtTTR_io, real32_T
  *rty_PosnObjAtTTR_o0, real32_T *rty_PosnObjAtTTR_b, real32_T
  *rty_PosnObjAtTTR_oq, real32_T *rty_PosnObjAtTTR_os, real32_T
  *rty_PosnObjAtTTR_o1, real32_T *rty_PosnObjAtTTR_p, real32_T
  *rty_PosnObjAtTTR_lx, real32_T *rty_PosnObjAtTTR_a, real32_T
  *rty_PosnObjAtTTR_ar, real32_T *rty_AObjIfManoeuvering, real32_T
  *rty_AObjIfManoeuvering_n, real32_T *rty_AObjIfManoeuvering_b, real32_T
  *rty_AObjIfManoeuvering_o, real32_T *rty_AObjIfManoeuvering_m, real32_T
  *rty_AObjIfManoeuvering_k, real32_T *rty_AObjIfManoeuvering_i, real32_T
  *rty_AObjIfManoeuvering_mc, real32_T *rty_AObjIfManoeuvering_h, real32_T
  *rty_AObjIfManoeuvering_p, const ConstB_CircularPrediction_LongSafe_SWC_h_T
  *localC);
extern void LongSafe_SWC_LinearPrediction_a(const BoundingBox0 *rtu_BoundingBox,
  const ObjGroup1Vcc *rtu_Obj, real32_T rtu_TTR, real32_T rtu_AObjAvoidance,
  real32_T rtu_AObjAvoidance_g, real32_T rtu_AObjAvoidance_b, real32_T
  rtu_CosHeading, real32_T rtu_SinHeading, real32_T rtu_HeadingStationary,
  real32_T *rty_PosnObjAtTTR, real32_T *rty_PosnObjAtTTR_d, real32_T
  *rty_PosnObjAtTTR_c, real32_T *rty_PosnObjAtTTR_o, real32_T
  *rty_PosnObjAtTTR_g, real32_T *rty_PosnObjAtTTR_b, real32_T
  *rty_PosnObjAtTTR_dd, real32_T *rty_PosnObjAtTTR_gd, real32_T
  *rty_PosnObjAtTTR_a, real32_T *rty_PosnObjAtTTR_m, real32_T
  *rty_PosnObjAtTTR_ao, real32_T *rty_PosnObjAtTTR_j, real32_T
  *rty_PosnObjAtTTR_co, real32_T *rty_PosnObjAtTTR_ga, real32_T
  *rty_PosnObjAtTTR_i, real32_T *rty_PosnObjAtTTR_cv, real32_T
  *rty_PosnObjAtTTR_gc, real32_T *rty_PosnObjAtTTR_p, real32_T
  *rty_PosnObjAtTTR_l, real32_T *rty_PosnObjAtTTR_k, real32_T
  *rty_PosnObjAtTTR_jj, real32_T *rty_PosnObjAtTTR_mi, real32_T
  *rty_PosnObjAtTTR_n, real32_T *rty_PosnObjAtTTR_a3, real32_T
  *rty_PosnObjAtTTR_f, real32_T *rty_AObjIfManoeuvering, real32_T
  *rty_AObjIfManoeuvering_a, real32_T *rty_AObjIfManoeuvering_b, real32_T
  *rty_AObjIfManoeuvering_p, real32_T *rty_AObjIfManoeuvering_h, real32_T
  *rty_AObjIfManoeuvering_e, real32_T *rty_AObjIfManoeuvering_f, real32_T
  *rty_AObjIfManoeuvering_n, real32_T *rty_AObjIfManoeuvering_c, real32_T
  *rty_AObjIfManoeuvering_cy);
extern void LongSafe_SWC_DetermineObjectManoeuver(boolean_T rtu_InPathDefault,
  boolean_T rtu_OncomingBraking, boolean_T rtu_CanBrake, boolean_T
  rtu_CanSteerLeft, boolean_T rtu_CanSteerRight, real32_T rtu_ABraking, real32_T
  rtu_ATurningLeft, real32_T rtu_ATurningRight, boolean_T *rty_WillBrake,
  boolean_T *rty_WillSteerLeft, boolean_T *rty_WillSteerRight);
extern void LongSafe_SWC_ObjectWillBrake(const ObjGroup1Vcc *rtu_Obj, real32_T
  rtu_PosnLatRelObjBraking, real32_T rtu_AObjBraking, real32_T rtu_AObjBraking_h,
  boolean_T rtu_InPathObjBraking, real32_T rtu_Deceleration, real32_T *rty_A,
  real32_T *rty_ALgt, real32_T *rty_ALat, real32_T *rty_Crvt, real32_T
  *rty_PosnLatRelAtTTR, boolean_T *rty_InPath);
extern void LongSafe_SWC_ObjectWillSteerLeft(const ObjGroup1Vcc *rtu_Obj,
  real32_T rtu_PosnRelAtTTR, real32_T rtu_AObjIfManoeuvering, real32_T
  rtu_AObjIfManoeuvering_k, real32_T rtu_AObjIfManoeuvering_e, real32_T *rty_A,
  real32_T *rty_ALgt, real32_T *rty_ALat, real32_T *rty_Crvt, real32_T
  *rty_PosnLatRelAtTTR, boolean_T *rty_InPath);
extern void LongSafe_SWC_ObjectWillSteerRight(const ObjGroup1Vcc *rtu_Obj,
  real32_T rtu_PosnRelAtTTR, real32_T rtu_AObjIfManoeuvering, real32_T
  rtu_AObjIfManoeuvering_b, real32_T rtu_AObjIfManoeuvering_l, real32_T *rty_A,
  real32_T *rty_ALgt, real32_T *rty_ALat, real32_T *rty_Crvt, real32_T
  *rty_PosnLatRelAtTTR, boolean_T *rty_InPath);
extern void LongSafe_SWC_NoManoeuverZeroLength(const ObjGroup1Vcc *rtu_Obj,
  real32_T rtu_PosnRelAtTTR, boolean_T rtu_InPathDefault, real32_T *rty_A,
  real32_T *rty_ALgt, real32_T *rty_ALat, real32_T *rty_Crvt, real32_T
  *rty_PosnLatRelAtTTR, boolean_T *rty_InPath);
extern void LongSafe_SWC_DetermineObjectManoeuver_k(boolean_T *rty_WillBrake,
  boolean_T *rty_WillSteerLeft, boolean_T *rty_WillSteerRight);
extern void LongSafe_SWC_LinearPrediction_i(const BoundingBox0 *rtu_BoundingBox,
  const ObjGroup1Vcc *rtu_Obj, real32_T rtu_TTR, real32_T rtu_AObjAvoidance,
  real32_T rtu_AObjAvoidance_a, real32_T rtu_AObjAvoidance_k, real32_T
  rtu_CosHeading, real32_T rtu_SinHeading, real32_T rtu_HeadingStationary,
  real32_T *rty_PosnObjAtTTR, real32_T *rty_PosnObjAtTTR_i, real32_T
  *rty_PosnObjAtTTR_c, real32_T *rty_PosnObjAtTTR_m, real32_T
  *rty_PosnObjAtTTR_a, real32_T *rty_PosnObjAtTTR_k, real32_T
  *rty_PosnObjAtTTR_h, real32_T *rty_PosnObjAtTTR_e, real32_T
  *rty_PosnObjAtTTR_f, real32_T *rty_PosnObjAtTTR_o, real32_T
  *rty_PosnObjAtTTR_j, real32_T *rty_PosnObjAtTTR_l, real32_T
  *rty_PosnObjAtTTR_l4, real32_T *rty_PosnObjAtTTR_d, real32_T
  *rty_PosnObjAtTTR_p, real32_T *rty_PosnObjAtTTR_b, real32_T
  *rty_PosnObjAtTTR_mx, real32_T *rty_PosnObjAtTTR_dk, real32_T
  *rty_PosnObjAtTTR_oc, real32_T *rty_PosnObjAtTTR_n, real32_T
  *rty_PosnObjAtTTR_jm, real32_T *rty_PosnObjAtTTR_a2, real32_T
  *rty_PosnObjAtTTR_cy, real32_T *rty_PosnObjAtTTR_cl, real32_T
  *rty_PosnObjAtTTR_hu, real32_T *rty_AObjIfManoeuvering, real32_T
  *rty_AObjIfManoeuvering_p, real32_T *rty_AObjIfManoeuvering_e, real32_T
  *rty_AObjIfManoeuvering_j, real32_T *rty_AObjIfManoeuvering_jn, real32_T
  *rty_AObjIfManoeuvering_i, real32_T *rty_AObjIfManoeuvering_f, real32_T
  *rty_AObjIfManoeuvering_h, real32_T *rty_AObjIfManoeuvering_l, real32_T
  *rty_AObjIfManoeuvering_o);
extern void LongSafe_SWC_DetermineObjectManoeuver_o(boolean_T *rty_WillBrake,
  boolean_T *rty_WillSteerLeft, boolean_T *rty_WillSteerRight);
extern void LongSafe_SWC_MovingObject_e(real32_T rtu_PredictedHeadingHost,
  real32_T rtu_PredictedHeadingObj, boolean_T rtu_SideIsClosest, real32_T
  *rty_SinRelativeRotation, real32_T *rty_CosRelativeRotation, real32_T
  *rty_RelativeHeading, const ConstB_MovingObject_LongSafe_SWC_n_T *localC);
extern void LongSafe_SWC_MATLABFunction_i(real32_T rtu_PosnLat, real32_T
  rtu_VLat, real32_T rtu_VLgt, ObjClassn3Vcc rtu_ObjType, real32_T rtu_TiCal,
  real32_T *rty_time);
extern void LongSafe_SWC_CalculateTTI(real32_T rtu_MotionDataNormalSetup,
  real32_T rtu_MotionDataNormalSetup_l, real32_T rtu_MotionDataNormalSetup_lz,
  real32_T rtu_MotionDataNormalSetup_o, real32_T rtu_MotionDataNormalSetup_m,
  real32_T rtu_MotionDataNormalSetup_c, real32_T rtu_MotionDataAlternativeSetup,
  real32_T rtu_MotionDataAlternativeSetup_h, real32_T
  rtu_MotionDataAlternativeSetup_d, real32_T rtu_MotionDataAlternativeSetup_c,
  real32_T rtu_MotionDataAlternativeSetup_n, real32_T
  rtu_MotionDataAlternativeSetup_m, real32_T rtu_EdgeDistanceNormalSetup,
  real32_T rtu_EdgeDistanceAlternativeSetup, real32_T rtu_StoppingData, real32_T
  rtu_StoppingData_l, real32_T *rty_MovingTTI, real32_T *rty_StationaryHostTTI,
  real32_T *rty_StationaryObjectTTI, boolean_T *rty_MovingSolutionExists,
  boolean_T *rty_StationaryHostSolutionExists, boolean_T
  *rty_StationaryObjectSolutionExists, const ConstB_CalculateTTI_LongSafe_SWC_T *
  localC);
extern void LongSafe_SWC_BothHostAndObjectWillStop(real32_T
  rtu_StationaryObjectTTI, real32_T rtu_StationaryHostTTI, real32_T
  rtu_ObjectStopTime, real32_T rtu_HostStopTime, boolean_T
  rtu_StationaryObjectSolutionExists, boolean_T rtu_StationaryHostSolutionExists,
  real32_T *rty_TimeToIntersection, boolean_T *rty_SolutionExists);
extern void LongSafe_SWC_HostOnlyWillStop(real32_T rtu_StationaryHostTTI,
  boolean_T rtu_StationaryHostSolutionExists, real32_T *rty_TimeToIntersection,
  boolean_T *rty_SolutionExists);
extern void LongSafe_SWC_ObjectOnlyWillStop(real32_T rtu_StationaryObjectTTI,
  boolean_T rtu_StationaryObjectSolutionExists, real32_T *rty_TimeToIntersection,
  boolean_T *rty_SolutionExists);
extern void LongSafe_SWC_HostAndObjectAreMoving(real32_T rtu_MovingTTI,
  boolean_T rtu_MovingSolutionExists, real32_T *rty_TimeToIntersection,
  boolean_T *rty_SolutionExists);
extern void LongSafe_SWC_MATLABFunction_a(real32_T rtu_ALgt, real32_T rtu_ALat,
  real32_T *rty_A);
extern void LongSafe_SWC_MATLABFunction_c(const AsLongSafeObject *rtu_PrimIntv,
  AsLongSafeObject *rty_y);
extern void LongSafe_SWC_PrimIntv_Lacth_Init(DW_PrimIntv_Lacth_LongSafe_SWC_T
  *localDW);
extern void LongSafe_SWC_PrimIntv_Lacth(const AsLongSafeObject *rtu_PrimIntv,
  boolean_T rtu_Trigger, boolean_T rtu_EnKeepPreInformation, boolean_T
  rtu_AEB_Active, real32_T rtu_HostSpeed, const AsLongSafeObject
  *rtu_PrimIntv_reset, real32_T *rty_PosnLgt_Limit, AsLongSafeObject
  *rty_NewPrimIntv, DW_PrimIntv_Lacth_LongSafe_SWC_T *localDW);
extern void LongSafe_SWC_AEB_Init(B_AEB_LongSafe_SWC_T *localB,
  DW_AEB_LongSafe_SWC_T *localDW);
extern void LongSafe_SWC_AEB(const AsLongSafeObject *rtu_LongSafeAEB, const
  AsLongSafeObject *rtu_LongSafeFCW, const AsScenarioInfo *rtu_ScenarioInfo,
  const AsVseOut *rtu_Vse, const AsParamConfig_T *rtu_ParamConfig, AsCmdLgSafe_T
  *rty_AsCmdLgSafe, LgSafe_T *rty_LgSafe_Debug, AsDisplayLgSafe_T
  *rty_AsDisplayLgSafe, B_AEB_LongSafe_SWC_T *localB, const
  ConstB_AEB_LongSafe_SWC_T *localC, DW_AEB_LongSafe_SWC_T *localDW);
extern void LongSafe_SWC_Ltap_Init(B_Ltap_LongSafe_SWC_T *localB,
  DW_Ltap_LongSafe_SWC_T *localDW);
extern void LongSafe_SWC_Ltap(const AsLongSafeObject *rtu_LongSafeAEB, const
  AsLongSafeObject *rtu_LongSafeFCW, const AsScenarioInfo *rtu_ScenarioInfo,
  const AsVseOut *rtu_Vse, const AsParamConfig_T *rtu_ParamConfig, AsCmdLgSafe_T
  *rty_AsCmdLgSafe, LgSafe_T *rty_LgSafe_Debug, AsDisplayLgSafe_T
  *rty_AsDisplayLgSafe, B_Ltap_LongSafe_SWC_T *localB, const
  ConstB_Ltap_LongSafe_SWC_T *localC, DW_Ltap_LongSafe_SWC_T *localDW);
extern void LongSafe_Control_Init(B_LongSafe_Control_T *localB,
  DW_LongSafe_Control_T *localDW);
extern void LongSafe_Control(const AsVseOut *rtu_Vse, const AsCoreOut_T
  *rtu_AS_CoreOut, const AsParamConfig_T *rtu_ParamConfig, LgSafe_T *rty_LgSafe,
  AsCmdLgSafe_T *rty_AsCmdLgSafe, AsDisplayLgSafe_T *rty_AsDisplayLgSafe,
  B_LongSafe_Control_T *localB, const ConstB_LongSafe_Control_T *localC,
  DW_LongSafe_Control_T *localDW);

#endif                                 /* RTW_HEADER_LongSafe_SWC_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
