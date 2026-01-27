/*
 * File: LongSafe_SWC_private.h
 *
 * Code generated for Simulink model 'LongSafe_SWC'.
 *
 * Model version                  : 7.3239
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue Jan 27 14:45:35 2026
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
extern const uint32_T rtCP_pooled_QbqRZt5SxXLI[2];
extern const uint32_T rtCP_pooled_YLpmxhxRZ0EE[2];
extern const uint32_T rtCP_pooled_nPd1I40s7kOQ[2];
extern const uint32_T rtCP_pooled_UkoYjQXAaa74[2];
extern const uint32_T rtCP_pooled_ybq2kYTVOPDW[2];
extern const boolean_T rtCP_pooled_2ukhhMbQGsh4[16];

#define rtCP_PahSegTiStepAryInDrvrStEstimr_Value rtCP_pooled_PN9J4ZADgHZo/* Expression: PahSegTiStepAryInDrvrStEstimr
                                                                      * Referenced by: '<S5880>/PahSegTiStepAryInDrvrStEstimr'
                                                                      */
#define rtCP_PahSegTiStepAryInDrvrStEstimr_Value_k rtCP_pooled_PN9J4ZADgHZo/* Expression: PahSegTiStepAryInDrvrStEstimr
                                                                      * Referenced by: '<S5817>/PahSegTiStepAryInDrvrStEstimr'
                                                                      */
#define rtCP_PredictionTimeVector1_Value rtCP_pooled_zcOdeOlOUYLM/* Expression: LTAPTimeVector
                                                                  * Referenced by: '<S1762>/PredictionTimeVector1'
                                                                  */
#define rtCP_PredictionTimeVector_Value rtCP_pooled_zcOdeOlOUYLM /* Expression: LTAPTimeVector
                                                                  * Referenced by: '<S1754>/PredictionTimeVector'
                                                                  */
#define rtCP_TimeVectorHighResTTR_Value rtCP_pooled_cJTcMumAder1 /* Expression: LTAPTimeVectorHighResTTR
                                                                  * Referenced by: '<S1741>/TimeVectorHighResTTR'
                                                                  */
#define rtCP_PredictionTimeVector_Value_d rtCP_pooled_zcOdeOlOUYLM/* Expression: LTAPTimeVector
                                                                   * Referenced by: '<S1634>/PredictionTimeVector'
                                                                   */
#define rtCP_LookupTableHighspeed_tableData rtCP_pooled_i8h9QNvcB151/* Expression: K_DrvrDecelReq
                                                                     * Referenced by: '<S5493>/Lookup Table High speed'
                                                                     */
#define rtCP_LookupTableHighspeed_bp01Data rtCP_pooled_2AeIQ2PrK3tN/* Expression: K_CylinderPress
                                                                    * Referenced by: '<S5493>/Lookup Table High speed'
                                                                    */
#define rtCP_uDLookupTable2_bp01Data   rtCP_pooled_mP0gWznDnYub  /* Computed Parameter: rtCP_uDLookupTable2_bp01Data
                                                                  * Referenced by: '<S1671>/1-D Lookup Table2'
                                                                  */
#define rtCP_LookupLateralMarginVRU_maxIndex rtCP_pooled_QbqRZt5SxXLI/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex
                                                                      * Referenced by: '<S2202>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex
                                                                      * Referenced by: '<S2202>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_e rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_e
                                                                      * Referenced by: '<S2215>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupLateralMarginVRU1_maxIndex rtCP_pooled_UkoYjQXAaa74/* Computed Parameter: rtCP_LookupLateralMarginVRU1_maxIndex
                                                                      * Referenced by: '<S2215>/LookupLateralMarginVRU1'
                                                                      */
#define rtCP_LookupLateralMarginVRU2_maxIndex rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU2_maxIndex
                                                                      * Referenced by: '<S2215>/LookupLateralMarginVRU2'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_b rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_b
                                                                      * Referenced by: '<S2215>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex
                                                                      * Referenced by: '<S2215>/LookupVRelPartOfLateralMarginVeh1'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_n rtCP_pooled_QbqRZt5SxXLI/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_n
                                                                      * Referenced by: '<S2214>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_d rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_d
                                                                      * Referenced by: '<S2214>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_InpathOffsetForVehicles_maxIndex rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_InpathOffsetForVehicles_maxIndex
                                                                      * Referenced by: '<S2175>/InpathOffsetForVehicles'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_f rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_f
                                                                      * Referenced by: '<S2201>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_h rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_h
                                                                      * Referenced by: '<S2201>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_d rtCP_pooled_QbqRZt5SxXLI/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_d
                                                                      * Referenced by: '<S3890>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_c rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_c
                                                                      * Referenced by: '<S3890>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_fa rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_fa
                                                                      * Referenced by: '<S3903>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupLateralMarginVRU1_maxIndex_k rtCP_pooled_UkoYjQXAaa74/* Computed Parameter: rtCP_LookupLateralMarginVRU1_maxIndex_k
                                                                      * Referenced by: '<S3903>/LookupLateralMarginVRU1'
                                                                      */
#define rtCP_LookupLateralMarginVRU2_maxIndex_i rtCP_pooled_nPd1I40s7kOQ/* Computed Parameter: rtCP_LookupLateralMarginVRU2_maxIndex_i
                                                                      * Referenced by: '<S3903>/LookupLateralMarginVRU2'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_a rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_a
                                                                      * Referenced by: '<S3903>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex_h rtCP_pooled_ybq2kYTVOPDW/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh1_maxIndex_h
                                                                      * Referenced by: '<S3903>/LookupVRelPartOfLateralMarginVeh1'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_a rtCP_pooled_QbqRZt5SxXLI/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_a
                                                                      * Referenced by: '<S3902>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_p rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_p
                                                                      * Referenced by: '<S3902>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_InpathOffsetForVehicles_maxIndex_i rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_InpathOffsetForVehicles_maxIndex_i
                                                                      * Referenced by: '<S3863>/InpathOffsetForVehicles'
                                                                      */
#define rtCP_LookupLateralMarginVRU_maxIndex_n3 rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_LookupLateralMarginVRU_maxIndex_n3
                                                                      * Referenced by: '<S3889>/LookupLateralMarginVRU'
                                                                      */
#define rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_j rtCP_pooled_YLpmxhxRZ0EE/* Computed Parameter: rtCP_LookupVRelPartOfLateralMarginVeh_maxIndex_j
                                                                      * Referenced by: '<S3889>/LookupVRelPartOfLateralMarginVeh'
                                                                      */
#define rtCP_Logic_table               rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table
                                                                  * Referenced by: '<S850>/Logic'
                                                                  */
#define rtCP_Logic_table_b             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_b
                                                                  * Referenced by: '<S864>/Logic'
                                                                  */
#define rtCP_Logic_table_d             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_d
                                                                  * Referenced by: '<S731>/Logic'
                                                                  */
#define rtCP_Logic_table_dh            rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_dh
                                                                  * Referenced by: '<S569>/Logic'
                                                                  */
#define rtCP_Logic_table_i             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_i
                                                                  * Referenced by: '<S562>/Logic'
                                                                  */
#define rtCP_Logic_table_m             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_m
                                                                  * Referenced by: '<S499>/Logic'
                                                                  */
#define rtCP_Logic_table_n             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_n
                                                                  * Referenced by: '<S500>/Logic'
                                                                  */
#define rtCP_Logic_table_p             rtCP_pooled_2ukhhMbQGsh4  /* Computed Parameter: rtCP_Logic_table_p
                                                                  * Referenced by: '<S561>/Logic'
                                                                  */

/* Expression: 0
 * Referenced by: '<S5940>/Constant4'
 */
#define rtCP_Constant4_Value           (0.0)

/* Expression: 0
 * Referenced by: '<S5947>/Constant4'
 */
#define rtCP_Constant4_Value_k         (0.0)

/* Expression: 0
 * Referenced by: '<S788>/Constant4'
 */
#define rtCP_Constant4_Value_f         (0.0)

/* Expression: 0
 * Referenced by: '<S803>/Constant4'
 */
#define rtCP_Constant4_Value_i         (0.0)

/* Expression: 0
 * Referenced by: '<S810>/Constant4'
 */
#define rtCP_Constant4_Value_h         (0.0)

/* Expression: 0
 * Referenced by: '<S811>/Constant4'
 */
#define rtCP_Constant4_Value_a         (0.0)

/* Expression: 0
 * Referenced by: '<S819>/Constant4'
 */
#define rtCP_Constant4_Value_j         (0.0)

/* Expression: 0
 * Referenced by: '<S823>/Constant4'
 */
#define rtCP_Constant4_Value_l         (0.0)

/* Expression: 0
 * Referenced by: '<S828>/Constant4'
 */
#define rtCP_Constant4_Value_o         (0.0)

/* Expression: 0
 * Referenced by: '<S831>/Constant4'
 */
#define rtCP_Constant4_Value_b         (0.0)

/* Expression: 0
 * Referenced by: '<S851>/Constant4'
 */
#define rtCP_Constant4_Value_ja        (0.0)

/* Expression: 0
 * Referenced by: '<S852>/Constant4'
 */
#define rtCP_Constant4_Value_g         (0.0)

/* Expression: 0
 * Referenced by: '<S865>/Constant4'
 */
#define rtCP_Constant4_Value_fp        (0.0)

/* Expression: 0
 * Referenced by: '<S866>/Constant4'
 */
#define rtCP_Constant4_Value_an        (0.0)

/* Expression: 0
 * Referenced by: '<S876>/Constant4'
 */
#define rtCP_Constant4_Value_d         (0.0)

/* Expression: 0
 * Referenced by: '<S911>/Constant4'
 */
#define rtCP_Constant4_Value_bl        (0.0)

/* Expression: 0
 * Referenced by: '<S328>/Constant'
 */
#define rtCP_Constant_Value_k          (0.0)

/* Expression: 2
 * Referenced by: '<S328>/Constant1'
 */
#define rtCP_Constant1_Value_p         (2.0)

/* Expression: 0
 * Referenced by: '<S328>/Constant2'
 */
#define rtCP_Constant2_Value_j         (0.0)

/* Expression: 1
 * Referenced by: '<S328>/Constant3'
 */
#define rtCP_Constant3_Value           (1.0)

/* Expression: 0
 * Referenced by: '<S328>/Constant4'
 */
#define rtCP_Constant4_Value_gl        (0.0)

/* Expression: 4
 * Referenced by: '<S328>/Constant5'
 */
#define rtCP_Constant5_Value           (4.0)

/* Expression: 4
 * Referenced by: '<S328>/Constant7'
 */
#define rtCP_Constant7_Value_al        (4.0)

/* Expression: 0
 * Referenced by: '<S476>/Constant4'
 */
#define rtCP_Constant4_Value_dp        (0.0)

/* Expression: 0
 * Referenced by: '<S2206>/Constant4'
 */
#define rtCP_Constant4_Value_gj        (0.0)

/* Expression: 0
 * Referenced by: '<S2207>/Constant4'
 */
#define rtCP_Constant4_Value_fpc       (0.0)

/* Expression: 0
 * Referenced by: '<S2223>/Constant4'
 */
#define rtCP_Constant4_Value_ak        (0.0)

/* Expression: 0
 * Referenced by: '<S2224>/Constant4'
 */
#define rtCP_Constant4_Value_fpe       (0.0)

/* Expression: 0
 * Referenced by: '<S3894>/Constant4'
 */
#define rtCP_Constant4_Value_ox        (0.0)

/* Expression: 0
 * Referenced by: '<S3895>/Constant4'
 */
#define rtCP_Constant4_Value_c         (0.0)

/* Expression: 0
 * Referenced by: '<S3911>/Constant4'
 */
#define rtCP_Constant4_Value_is        (0.0)

/* Expression: 0
 * Referenced by: '<S3912>/Constant4'
 */
#define rtCP_Constant4_Value_p         (0.0)

/* Expression: 0
 * Referenced by: '<S5599>/Constant4'
 */
#define rtCP_Constant4_Value_pa        (0.0)

/* Expression: 0
 * Referenced by: '<S5618>/Constant4'
 */
#define rtCP_Constant4_Value_iw        (0.0)

/* Expression: 0
 * Referenced by: '<S5619>/Constant4'
 */
#define rtCP_Constant4_Value_ib        (0.0)

/* Expression: 0
 * Referenced by: '<S5622>/Constant4'
 */
#define rtCP_Constant4_Value_gs        (0.0)

/* Expression: 0
 * Referenced by: '<S5631>/Constant4'
 */
#define rtCP_Constant4_Value_jt        (0.0)

/* Expression: 0
 * Referenced by: '<S5632>/Constant4'
 */
#define rtCP_Constant4_Value_an5       (0.0)

/* Expression: 0
 * Referenced by: '<S5689>/Constant4'
 */
#define rtCP_Constant4_Value_i3        (0.0)

/* Expression: 0
 * Referenced by: '<S5690>/Constant4'
 */
#define rtCP_Constant4_Value_a1        (0.0)

/* Expression: 0
 * Referenced by: '<S5691>/Constant4'
 */
#define rtCP_Constant4_Value_hf        (0.0)

/* Expression: 0
 * Referenced by: '<S5736>/Constant4'
 */
#define rtCP_Constant4_Value_l0        (0.0)

/* Expression: 0
 * Referenced by: '<S5737>/Constant4'
 */
#define rtCP_Constant4_Value_ho        (0.0)

/* Expression: 0
 * Referenced by: '<S5738>/Constant4'
 */
#define rtCP_Constant4_Value_oh        (0.0)

/* Expression: 0
 * Referenced by: '<S5932>/Constant4'
 */
#define rtCP_Constant4_Value_le        (0.0)

/* Expression: 0
 * Referenced by: '<S5934>/Constant4'
 */
#define rtCP_Constant4_Value_bi        (0.0)

/* Expression: 0
 * Referenced by: '<S5936>/Constant4'
 */
#define rtCP_Constant4_Value_d4        (0.0)

/* Expression: 0
 * Referenced by: '<S5938>/Constant4'
 */
#define rtCP_Constant4_Value_gh        (0.0)

/* Expression: 0
 * Referenced by: '<S5950>/Constant4'
 */
#define rtCP_Constant4_Value_aq        (0.0)

/* Expression: 0
 * Referenced by: '<S5981>/Constant4'
 */
#define rtCP_Constant4_Value_jz        (0.0)

/* Expression: Sampletime
 * Referenced by: '<S6114>/Constant1'
 */
#define rtCP_Constant1_Value_k         (0.02)

/* Expression: Sampletime
 * Referenced by: '<S6115>/Constant1'
 */
#define rtCP_Constant1_Value_f         (0.02)

/* Expression: 0
 * Referenced by: '<S6152>/Constant4'
 */
#define rtCP_Constant4_Value_hg        (0.0)

/* Expression: 2
 * Referenced by: '<S6208>/bicycle'
 */
#define rtCP_bicycle_Value             (2.0)

/* Expression: 2
 * Referenced by: '<S6208>/bicycle2'
 */
#define rtCP_bicycle2_Value            (2.0)

/* Expression: 3
 * Referenced by: '<S6208>/car'
 */
#define rtCP_car_Value                 (3.0)

/* Expression: 0
 * Referenced by: '<S6208>/notdefined'
 */
#define rtCP_notdefined_Value          (0.0)

/* Expression: 12
 * Referenced by: '<S6208>/other'
 */
#define rtCP_other_Value               (12.0)

/* Expression: 10
 * Referenced by: '<S6208>/other1'
 */
#define rtCP_other1_Value              (10.0)

/* Expression: 1
 * Referenced by: '<S6208>/ped'
 */
#define rtCP_ped_Value                 (1.0)

/* Expression: 4
 * Referenced by: '<S6208>/truck'
 */
#define rtCP_truck_Value               (4.0)

/* Expression: 2
 * Referenced by: '<S6196>/bicycle'
 */
#define rtCP_bicycle_Value_o           (2.0)

/* Expression: 2
 * Referenced by: '<S6196>/motor'
 */
#define rtCP_motor_Value               (2.0)

/* Expression: Sampletime
 * Referenced by: '<S6298>/Constant1'
 */
#define rtCP_Constant1_Value_b         (0.02)

/* Expression: Sampletime
 * Referenced by: '<S6299>/Constant1'
 */
#define rtCP_Constant1_Value_pu        (0.02)

/* Expression: Sampletime
 * Referenced by: '<S6303>/Constant1'
 */
#define rtCP_Constant1_Value_h         (0.02)

/* Expression: Sampletime
 * Referenced by: '<S6305>/Constant1'
 */
#define rtCP_Constant1_Value_m         (0.02)

/* Computed Parameter: rtCP_Constant56_Value
 * Referenced by: '<S5476>/Constant56'
 */
#define rtCP_Constant56_Value          ((100UL))

/* Computed Parameter: rtCP_Constant56_Value_o
 * Referenced by: '<S5477>/Constant56'
 */
#define rtCP_Constant56_Value_o        ((100UL))

/* Expression: AEBState.AEB_ACTIVE
 * Referenced by: '<S6069>/Constant'
 */
#define rtCP_Constant_Value_kq         (AEB_ACTIVE)

/* Expression: AEBState.AEB_ACTIVE
 * Referenced by: '<S6078>/Constant'
 */
#define rtCP_Constant_Value_kn         (AEB_ACTIVE)

/* Expression: AEBState.AEB_ACTIVE
 * Referenced by: '<S6081>/Constant1'
 */
#define rtCP_Constant1_Value_pp        (AEB_ACTIVE)

/* Expression: AEBState.AEB_ACTIVE
 * Referenced by: '<S6083>/Constant1'
 */
#define rtCP_Constant1_Value_n         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6084>/Constant'
 */
#define rtCP_Constant_Value_d          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6147>/Constant'
 */
#define rtCP_Constant_Value_e          (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6148>/Constant'
 */
#define rtCP_Constant_Value_n          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6171>/Constant'
 */
#define rtCP_Constant_Value_b          (AEB_OFF)

/* Expression: const
 * Referenced by: '<S6172>/Constant'
 */
#define rtCP_Constant_Value_c          (AEB_FAILURE)

/* Expression: const
 * Referenced by: '<S6173>/Constant'
 */
#define rtCP_Constant_Value_d3         (AEB_PASSIVE)

/* Expression: const
 * Referenced by: '<S6174>/Constant'
 */
#define rtCP_Constant_Value_f          (AEB_STANDBY)

/* Expression: const
 * Referenced by: '<S6175>/Constant'
 */
#define rtCP_Constant_Value_m          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6176>/Constant'
 */
#define rtCP_Constant_Value_da         (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6177>/Constant'
 */
#define rtCP_Constant_Value_o          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6178>/Constant'
 */
#define rtCP_Constant_Value_ej         (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6157>/Constant'
 */
#define rtCP_Constant_Value_k0         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6161>/Constant'
 */
#define rtCP_Constant_Value_o2         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6162>/Constant'
 */
#define rtCP_Constant_Value_fc         (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6181>/Constant'
 */
#define rtCP_Constant_Value_p          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6182>/Constant'
 */
#define rtCP_Constant_Value_h          (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6186>/Constant'
 */
#define rtCP_Constant_Value_i          (AEB_HOLD)

/* Expression: const
 * Referenced by: '<S6187>/Constant'
 */
#define rtCP_Constant_Value_a          (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6188>/Constant'
 */
#define rtCP_Constant_Value_c4         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6204>/Constant'
 */
#define rtCP_Constant_Value_hn         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6206>/Constant'
 */
#define rtCP_Constant_Value_e1         (AEB_FAILURE)

/* Expression: const
 * Referenced by: '<S6207>/Constant'
 */
#define rtCP_Constant_Value_ev         (AEB_OFF)

/* Expression: const
 * Referenced by: '<S6210>/Constant'
 */
#define rtCP_Constant_Value_ov         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6215>/Constant'
 */
#define rtCP_Constant_Value_p4         (AEB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6217>/Constant'
 */
#define rtCP_Constant_Value_oz         (AEB_ACTIVE)

/* Expression: AEBState.AEB_STANDBY
 * Referenced by: '<S6109>/Constant1'
 */
#define rtCP_Constant1_Value_nf        (AEB_STANDBY)

/* Expression: const
 * Referenced by: '<S6288>/Constant'
 */
#define rtCP_Constant_Value_dan        (AEB_HOLD)

/* Expression: AWBState.AWB_ACTIVE
 * Referenced by: '<S6076>/Constant'
 */
#define rtCP_Constant_Value_pv         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6085>/Constant'
 */
#define rtCP_Constant_Value_pf         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6159>/Constant'
 */
#define rtCP_Constant_Value_fx         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6179>/Constant'
 */
#define rtCP_Constant_Value_ex         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6184>/Constant'
 */
#define rtCP_Constant_Value_hc         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6212>/Constant'
 */
#define rtCP_Constant_Value_nx         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6219>/Constant'
 */
#define rtCP_Constant_Value_ac         (AWB_ACTIVE)

/* Expression: const
 * Referenced by: '<S6222>/Constant'
 */
#define rtCP_Constant_Value_g          (AWB_ACTIVE)

/* Expression: Value
 * Referenced by: '<S526>/Constant'
 */
#define rtCP_Constant_Value_fb         (AccSts1_Actv)

/* Expression: AccSts1.Off
 * Referenced by: '<S5482>/Constant11'
 */
#define rtCP_Constant11_Value          (AccSts1_Off)

/* Expression: AccSts1.Actv
 * Referenced by: '<S5482>/Constant7'
 */
#define rtCP_Constant7_Value_d         (AccSts1_Actv)

/* Expression: Value
 * Referenced by: '<S492>/Constant'
 */
#define rtCP_Constant_Value_p3         (AsyBltLvl1Vcc_ActvnFHi)

/* Expression: Value
 * Referenced by: '<S493>/Constant'
 */
#define rtCP_Constant_Value_eo         (AsyBltLvl1Vcc_ActvnFLo)

/* Expression: Value
 * Referenced by: '<S509>/Constant'
 */
#define rtCP_Constant_Value_d1         (AsyBltLvl1Vcc_NoActvn)

/* Expression: Value
 * Referenced by: '<S29>/Constant'
 */
#define rtCP_Constant_Value_k1         (AsySftyDecelReqDendBySpdRedn0_FALSE)

/* Expression: Value
 * Referenced by: '<S30>/Constant'
 */
#define rtCP_Constant_Value_hcw        (AsySftyDecelReqDendBySpdRedn0_TRUE)

/* Expression: Value
 * Referenced by: '<S536>/Constant'
 */
#define rtCP_Constant_Value_of         (AsySftyDecelReqDendBySpdRedn0_TRUE)

/* Expression: const
 * Referenced by: '<S6286>/Constant'
 */
#define rtCP_Constant_Value_nk         (AsySftyDecelReqDendBySpdRedn0_TRUE)

/* Expression: Value
 * Referenced by: '<S352>/Constant'
 */
#define rtCP_Constant_Value_na         (CllsnFwdWarnCtrlCllsnThreat1Vcc_ThreatLo)

/* Expression: Value
 * Referenced by: '<S353>/Constant'
 */
#define rtCP_Constant_Value_j          (CllsnFwdWarnCtrlCllsnThreat1Vcc_Ukwn)

/* Expression: Value
 * Referenced by: '<S941>/Constant'
 */
#define rtCP_Constant_Value_kc         (CllsnMtgtnByBrkgPrimQlyVcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S482>/Constant'
 */
#define rtCP_Constant_Value_bo         (CllsnMtgtnByBrkgPrimQlyVcc_BrkgRelbl)

/* Expression: Value
 * Referenced by: '<S557>/Constant'
 */
#define rtCP_Constant_Value_pu         (CllsnMtgtnByBrkgPrimQlyVcc_BrkgRelbl)

/* Expression: Value
 * Referenced by: '<S608>/Constant'
 */
#define rtCP_Constant_Value_bb         (CllsnMtgtnByBrkgPrimQlyVcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S631>/Constant'
 */
#define rtCP_Constant_Value_mj         (CllsnMtgtnByBrkgPrimQlyVcc_BrkgRelbl)

/* Expression: Value
 * Referenced by: '<S673>/Constant'
 */
#define rtCP_Constant_Value_j3         (CllsnMtgtnByBrkgPrimQlyVcc_BrkgRelbl)

/* Expression: Value
 * Referenced by: '<S674>/Constant'
 */
#define rtCP_Constant_Value_bbk        (CllsnMtgtnByBrkgPrimQlyVcc_BrkSpprtRelbl)

/* Expression: Value
 * Referenced by: '<S737>/Constant'
 */
#define rtCP_Constant_Value_b3         (CllsnMtgtnByBrkgPrimQlyVcc_CoastRelbl)

/* Expression: Value
 * Referenced by: '<S738>/Constant'
 */
#define rtCP_Constant_Value_eg         (CllsnMtgtnByBrkgPrimQlyVcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S546>/Constant'
 */
#define rtCP_Constant_Value_i4         (CllsnRednByBrkgPostStsArbn1Vcc_DenByNotEnab)

/* Expression: Value
 * Referenced by: '<S547>/Constant'
 */
#define rtCP_Constant_Value_gc         (CllsnRednByBrkgPostStsArbn1Vcc_DenByOccptSftyPosnNotAvl)

/* Expression: Value
 * Referenced by: '<S551>/Constant'
 */
#define rtCP_Constant_Value_na4        (CllsnRednByBrkgPostStsArbn1Vcc_OvrdByDrvr)

/* Expression: Value
 * Referenced by: '<S548>/Constant'
 */
#define rtCP_Constant_Value_j2         (CllsnRednByBrkgPostStsArbn1Vcc_DenBySpdThd)

/* Expression: Value
 * Referenced by: '<S549>/Constant'
 */
#define rtCP_Constant_Value_br         (CllsnRednByBrkgPostStsArbn1Vcc_FullBrkgActv)

/* Expression: Value
 * Referenced by: '<S553>/Constant'
 */
#define rtCP_Constant_Value_ot         (CllsnRednByBrkgPostStsArbn1Vcc_VisnOnlyVruBrkActv)

/* Expression: Value
 * Referenced by: '<S552>/Constant'
 */
#define rtCP_Constant_Value_ow         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S550>/Constant'
 */
#define rtCP_Constant_Value_mt         (CllsnRednByBrkgPostStsArbn1Vcc_NotActv)

/* Expression: Value
 * Referenced by: '<S483>/Constant'
 */
#define rtCP_Constant_Value_cp         (CllsnRednByBrkgPostStsArbn1Vcc_VisnOnlyVruBrkActv)

/* Expression: Value
 * Referenced by: '<S486>/Constant'
 */
#define rtCP_Constant_Value_ei         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S487>/Constant'
 */
#define rtCP_Constant_Value_l4         (CllsnRednByBrkgPostStsArbn1Vcc_FullBrkgActv)

/* Expression: Value
 * Referenced by: '<S502>/Constant'
 */
#define rtCP_Constant_Value_a3         (CllsnRednByBrkgPostStsArbn1Vcc_FullBrkgActv)

/* Expression: Value
 * Referenced by: '<S503>/Constant'
 */
#define rtCP_Constant_Value_ma         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S522>/Constant'
 */
#define rtCP_Constant_Value_ds         (CllsnRednByBrkgPostStsArbn1Vcc_FullBrkgActv)

/* Expression: Value
 * Referenced by: '<S523>/Constant'
 */
#define rtCP_Constant_Value_dd         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S524>/Constant'
 */
#define rtCP_Constant_Value_exo        (CllsnRednByBrkgPostStsArbn1Vcc_VisnOnlyVruBrkActv)

/* Expression: Value
 * Referenced by: '<S525>/Constant'
 */
#define rtCP_Constant_Value_jr         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S558>/Constant'
 */
#define rtCP_Constant_Value_es         (CllsnRednByBrkgPostStsArbn1Vcc_FullBrkgActv)

/* Expression: Value
 * Referenced by: '<S559>/Constant'
 */
#define rtCP_Constant_Value_ey         (CllsnRednByBrkgPostStsArbn1Vcc_PreBrkgActv)

/* Expression: Value
 * Referenced by: '<S563>/Constant'
 */
#define rtCP_Constant_Value_bc         (CllsnRednByBrkgPostStsArbn1Vcc_VisnOnlyVruBrkActv)

/* Expression: Value
 * Referenced by: '<S60>/Constant'
 */
#define rtCP_Constant_Value_hj         (CllsnRednByBrkgWarnReq0_TRUE)

/* Expression: Value
 * Referenced by: '<S748>/Constant'
 */
#define rtCP_Constant_Value_hq         (CllsnRednByBrkgWarnReq0_TRUE)

/* Expression: Value
 * Referenced by: '<S749>/Constant'
 */
#define rtCP_Constant_Value_egr        (CllsnRednByBrkgWarnReq0_FALSE)

/* Expression: Value
 * Referenced by: '<S964>/Constant'
 */
#define rtCP_Constant_Value_cn         (CllsnWarnFwdQlyVcc_NotRelbl)

/* Expression: const
 * Referenced by: '<S298>/Constant'
 */
#define rtCP_Constant_Value_mjt        (CllsnWarnFwdQlyVcc_Relbl)

/* Expression: const
 * Referenced by: '<S801>/Constant'
 */
#define rtCP_Constant_Value_hm         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S826>/Constant'
 */
#define rtCP_Constant_Value_iw         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S841>/Constant'
 */
#define rtCP_Constant_Value_k2         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S857>/Constant'
 */
#define rtCP_Constant_Value_pp         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S893>/Constant'
 */
#define rtCP_Constant_Value_dn         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S894>/Constant'
 */
#define rtCP_Constant_Value_lu         (EgoMotionState_MidRadius)

/* Expression: const
 * Referenced by: '<S918>/Constant'
 */
#define rtCP_Constant_Value_hp         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S919>/Constant'
 */
#define rtCP_Constant_Value_pvh        (EgoMotionState_MidRadius)

/* Expression: const
 * Referenced by: '<S1797>/Constant'
 */
#define rtCP_Constant_Value_k2g        (EgoMotionState_SmallRadius)

/* Expression: const
 * Referenced by: '<S602>/Constant'
 */
#define rtCP_Constant_Value_bd         (EgoMotionState_SmallRadius)

/* Expression: const
 * Referenced by: '<S628>/Constant'
 */
#define rtCP_Constant_Value_j0         (EgoMotionState_SmallRadius)

/* Expression: const
 * Referenced by: '<S657>/Constant'
 */
#define rtCP_Constant_Value_pm         (EgoMotionState_SmallRadius)

/* Expression: const
 * Referenced by: '<S2247>/Constant'
 */
#define rtCP_Constant_Value_gm         (EgoMotionState_Straight)

/* Expression: const
 * Referenced by: '<S3935>/Constant'
 */
#define rtCP_Constant_Value_ep         (EgoMotionState_Straight)

/* Expression: FCWState.FCW_STANDBY
 * Referenced by: '<S6079>/Constant'
 */
#define rtCP_Constant_Value_k11        (FCW_STANDBY)

/* Expression: FCWState.FCW_ACTIVE
 * Referenced by: '<S6081>/Constant'
 */
#define rtCP_Constant_Value_aq         (FCW_ACTIVE)

/* Expression: FCWState.FCW_ACTIVE
 * Referenced by: '<S6083>/Constant'
 */
#define rtCP_Constant_Value_nn         (FCW_ACTIVE)

/* Expression: FCWState.FCW_ACTIVE
 * Referenced by: '<S6087>/Constant'
 */
#define rtCP_Constant_Value_ba         (FCW_ACTIVE)

/* Expression: FCWState.FCW_ACTIVE
 * Referenced by: '<S6088>/Constant13'
 */
#define rtCP_Constant13_Value          (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6180>/Constant'
 */
#define rtCP_Constant_Value_o0         (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6185>/Constant'
 */
#define rtCP_Constant_Value_fxg        (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6189>/Constant'
 */
#define rtCP_Constant_Value_esx        (FCW_OFF)

/* Expression: const
 * Referenced by: '<S6190>/Constant'
 */
#define rtCP_Constant_Value_k3         (FCW_FAILURE)

/* Expression: const
 * Referenced by: '<S6191>/Constant'
 */
#define rtCP_Constant_Value_go         (FCW_PASSIVE)

/* Expression: const
 * Referenced by: '<S6192>/Constant'
 */
#define rtCP_Constant_Value_kk         (FCW_STANDBY)

/* Expression: const
 * Referenced by: '<S6193>/Constant'
 */
#define rtCP_Constant_Value_j3z        (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6211>/Constant'
 */
#define rtCP_Constant_Value_gn         (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6213>/Constant'
 */
#define rtCP_Constant_Value_ku         (FCW_OFF)

/* Expression: const
 * Referenced by: '<S6214>/Constant'
 */
#define rtCP_Constant_Value_cg         (FCW_FAILURE)

/* Expression: const
 * Referenced by: '<S6216>/Constant'
 */
#define rtCP_Constant_Value_kd         (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6218>/Constant'
 */
#define rtCP_Constant_Value_ob         (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6221>/Constant'
 */
#define rtCP_Constant_Value_o4         (FCW_ACTIVE)

/* Expression: FCWState.FCW_ACTIVE
 * Referenced by: '<S6108>/Constant'
 */
#define rtCP_Constant_Value_ou         (FCW_ACTIVE)

/* Expression: const
 * Referenced by: '<S6160>/Constant'
 */
#define rtCP_Constant_Value_hp1        (HBA_ACTIVE)

/* Expression: const
 * Referenced by: '<S6220>/Constant'
 */
#define rtCP_Constant_Value_jm         (HBA_ACTIVE)

/* Expression: Value
 * Referenced by: '<S360>/Constant'
 */
#define rtCP_Constant_Value_cgj        (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S361>/Constant'
 */
#define rtCP_Constant_Value_ld         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_UkwnClass)

/* Expression: Value
 * Referenced by: '<S362>/Constant'
 */
#define rtCP_Constant_Value_b0         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Car)

/* Expression: Value
 * Referenced by: '<S363>/Constant'
 */
#define rtCP_Constant_Value_oi         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Motorcycle)

/* Expression: Value
 * Referenced by: '<S364>/Constant'
 */
#define rtCP_Constant_Value_p3g        (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Truck)

/* Expression: Value
 * Referenced by: '<S365>/Constant'
 */
#define rtCP_Constant_Value_lw         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Ped)

/* Expression: Value
 * Referenced by: '<S366>/Constant'
 */
#define rtCP_Constant_Value_fu         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Anim)

/* Expression: Value
 * Referenced by: '<S367>/Constant'
 */
#define rtCP_Constant_Value_fuy        (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_ObjGen)

/* Expression: Value
 * Referenced by: '<S368>/Constant'
 */
#define rtCP_Constant_Value_mjo        (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_Bicycle)

/* Expression: Value
 * Referenced by: '<S359>/Constant'
 */
#define rtCP_Constant_Value_ar         (HmiDataFromCllsnFwdWarnCtrl1VccObjTyp0_UkwnClass)

/* Expression: Value
 * Referenced by: '<S172>/Constant'
 */
#define rtCP_Constant_Value_mz         (NoYes1_Yes)

/* Expression: Value
 * Referenced by: '<S568>/Constant'
 */
#define rtCP_Constant_Value_p0         (NoYes1_Yes)

/* Expression: Value
 * Referenced by: '<S694>/Constant'
 */
#define rtCP_Constant_Value_mzx        (NoYes1_Yes)

/* Expression: Value
 * Referenced by: '<S5953>/Constant'
 */
#define rtCP_Constant_Value_gc0        (NoYes1_Yes)

/* Expression: Value
 * Referenced by: '<S758>/Constant'
 */
#define rtCP_Constant_Value_ij         (NoYes1Vcc_Yes)

/* Expression: Value
 * Referenced by: '<S759>/Constant'
 */
#define rtCP_Constant_Value_fi         (NoYes1Vcc_No)

/* Expression: Value
 * Referenced by: '<S996>/Constant'
 */
#define rtCP_Constant_Value_if         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S997>/Constant'
 */
#define rtCP_Constant_Value_bxn        (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S1325>/Constant'
 */
#define rtCP_Constant_Value_l0         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S1326>/Constant'
 */
#define rtCP_Constant_Value_lz         (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S1821>/Constant'
 */
#define rtCP_Constant_Value_gf         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S1822>/Constant'
 */
#define rtCP_Constant_Value_g4         (ObjClassn3Vcc_Anim)

/* Expression: const
 * Referenced by: '<S765>/Constant'
 */
#define rtCP_Constant_Value_ki         (ObjClassn3Vcc_ObjGen)

/* Expression: const
 * Referenced by: '<S827>/Constant'
 */
#define rtCP_Constant_Value_jp         (ObjClassn3Vcc_ObjGen)

/* Expression: const
 * Referenced by: '<S840>/Constant'
 */
#define rtCP_Constant_Value_fo         (ObjClassn3Vcc_ObjGen)

/* Expression: const
 * Referenced by: '<S846>/Constant'
 */
#define rtCP_Constant_Value_hmr        (ObjClassn3Vcc_ObjGen)

/* Expression: const
 * Referenced by: '<S869>/Constant'
 */
#define rtCP_Constant_Value_py         (ObjClassn3Vcc_Truck)

/* Expression: const
 * Referenced by: '<S870>/Constant'
 */
#define rtCP_Constant_Value_fe         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S944>/Constant'
 */
#define rtCP_Constant_Value_ky         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S960>/Constant5'
 */
#define rtCP_Constant5_Value_d         (ObjClassn3Vcc_UkwnClass)

/* Expression: const
 * Referenced by: '<S297>/Constant'
 */
#define rtCP_Constant_Value_dm         (ObjClassn3Vcc_ObjGen)

/* Expression: Value
 * Referenced by: '<S504>/Constant'
 */
#define rtCP_Constant_Value_hz         (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S507>/Constant'
 */
#define rtCP_Constant_Value_oq         (ObjClassn3Vcc_Ped)

/* Expression: Value
 * Referenced by: '<S661>/Constant'
 */
#define rtCP_Constant_Value_oj         (ObjClassn3Vcc_Ped)

/* Expression: Value
 * Referenced by: '<S662>/Constant'
 */
#define rtCP_Constant_Value_bl         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S663>/Constant'
 */
#define rtCP_Constant_Value_ea         (ObjClassn3Vcc_Motorcycle)

/* Expression: Value
 * Referenced by: '<S664>/Constant'
 */
#define rtCP_Constant_Value_h1         (ObjClassn3Vcc_Ped)

/* Expression: Value
 * Referenced by: '<S665>/Constant'
 */
#define rtCP_Constant_Value_cr         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S666>/Constant'
 */
#define rtCP_Constant_Value_no         (ObjClassn3Vcc_Motorcycle)

/* Expression: Value
 * Referenced by: '<S711>/Constant'
 */
#define rtCP_Constant_Value_ay         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S745>/Constant'
 */
#define rtCP_Constant_Value_j3t        (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S746>/Constant'
 */
#define rtCP_Constant_Value_pft        (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S2137>/Constant'
 */
#define rtCP_Constant_Value_nf         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S2138>/Constant'
 */
#define rtCP_Constant_Value_boa        (ObjClassn3Vcc_Anim)

/* Expression: const
 * Referenced by: '<S2141>/Constant'
 */
#define rtCP_Constant_Value_i0         (ObjClassn3Vcc_Ped)

/* Expression: const
 * Referenced by: '<S2142>/Constant'
 */
#define rtCP_Constant_Value_jg         (ObjClassn3Vcc_ObjGen)

/* Expression: Value
 * Referenced by: '<S2155>/Constant'
 */
#define rtCP_Constant_Value_jt         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S2156>/Constant'
 */
#define rtCP_Constant_Value_a3x        (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S2197>/Constant'
 */
#define rtCP_Constant_Value_i2         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S2199>/Constant'
 */
#define rtCP_Constant_Value_hv         (ObjClassn3Vcc_Motorcycle)

/* Expression: const
 * Referenced by: '<S2200>/Constant'
 */
#define rtCP_Constant_Value_dse        (ObjClassn3Vcc_Car)

/* Expression: const
 * Referenced by: '<S2210>/Constant'
 */
#define rtCP_Constant_Value_gk         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S2212>/Constant'
 */
#define rtCP_Constant_Value_et         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S2213>/Constant'
 */
#define rtCP_Constant_Value_fy         (ObjClassn3Vcc_Motorcycle)

/* Expression: const
 * Referenced by: '<S2227>/Constant'
 */
#define rtCP_Constant_Value_g3         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S2229>/Constant'
 */
#define rtCP_Constant_Value_jrv        (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S2230>/Constant'
 */
#define rtCP_Constant_Value_kx         (ObjClassn3Vcc_Motorcycle)

/* Expression: const
 * Referenced by: '<S2231>/Constant'
 */
#define rtCP_Constant_Value_m0         (ObjClassn3Vcc_Car)

/* Expression: Value
 * Referenced by: '<S2276>/Constant'
 */
#define rtCP_Constant_Value_c1         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S2277>/Constant'
 */
#define rtCP_Constant_Value_kv         (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S2285>/Constant'
 */
#define rtCP_Constant_Value_gkt        (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S2286>/Constant'
 */
#define rtCP_Constant_Value_hu         (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S2331>/Constant'
 */
#define rtCP_Constant_Value_dz         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S2332>/Constant'
 */
#define rtCP_Constant_Value_fj         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S3251>/Constant'
 */
#define rtCP_Constant_Value_bk         (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S3568>/Constant'
 */
#define rtCP_Constant_Value_pt         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S2115>/Constant1'
 */
#define rtCP_Constant1_Value_d         (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2115>/Constant10'
 */
#define rtCP_Constant10_Value          (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Bicycle
 * Referenced by: '<S2115>/Constant11'
 */
#define rtCP_Constant11_Value_i        (ObjClassn3Vcc_Bicycle)

/* Expression: ObjClassn3Vcc.VehOfUkwnClass
 * Referenced by: '<S2115>/Constant12'
 */
#define rtCP_Constant12_Value_j        (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S2115>/Constant13'
 */
#define rtCP_Constant13_Value_b        (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2115>/Constant15'
 */
#define rtCP_Constant15_Value          (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S2115>/Constant16'
 */
#define rtCP_Constant16_Value          (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2115>/Constant17'
 */
#define rtCP_Constant17_Value          (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2115>/Constant2'
 */
#define rtCP_Constant2_Value_l         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Car
 * Referenced by: '<S2115>/Constant3'
 */
#define rtCP_Constant3_Value_l         (ObjClassn3Vcc_Car)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S2115>/Constant4'
 */
#define rtCP_Constant4_Value_isc       (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.Truck
 * Referenced by: '<S2115>/Constant5'
 */
#define rtCP_Constant5_Value_b         (ObjClassn3Vcc_Truck)

/* Expression: ObjClassn3Vcc.Ped
 * Referenced by: '<S2115>/Constant6'
 */
#define rtCP_Constant6_Value           (ObjClassn3Vcc_Ped)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2115>/Constant7'
 */
#define rtCP_Constant7_Value_n         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S2115>/Constant8'
 */
#define rtCP_Constant8_Value           (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Anim
 * Referenced by: '<S2115>/Constant9'
 */
#define rtCP_Constant9_Value           (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S3825>/Constant'
 */
#define rtCP_Constant_Value_nc         (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: Value
 * Referenced by: '<S3826>/Constant'
 */
#define rtCP_Constant_Value_ejv        (ObjClassn3Vcc_Anim)

/* Expression: const
 * Referenced by: '<S3829>/Constant'
 */
#define rtCP_Constant_Value_d2         (ObjClassn3Vcc_Ped)

/* Expression: const
 * Referenced by: '<S3830>/Constant'
 */
#define rtCP_Constant_Value_o5         (ObjClassn3Vcc_ObjGen)

/* Expression: Value
 * Referenced by: '<S3843>/Constant'
 */
#define rtCP_Constant_Value_dsj        (ObjClassn3Vcc_Bicycle)

/* Expression: Value
 * Referenced by: '<S3844>/Constant'
 */
#define rtCP_Constant_Value_hd         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S3885>/Constant'
 */
#define rtCP_Constant_Value_n1         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S3887>/Constant'
 */
#define rtCP_Constant_Value_ie         (ObjClassn3Vcc_Motorcycle)

/* Expression: const
 * Referenced by: '<S3888>/Constant'
 */
#define rtCP_Constant_Value_mm         (ObjClassn3Vcc_Car)

/* Expression: const
 * Referenced by: '<S3898>/Constant'
 */
#define rtCP_Constant_Value_mp         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S3900>/Constant'
 */
#define rtCP_Constant_Value_bs         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S3901>/Constant'
 */
#define rtCP_Constant_Value_k1f        (ObjClassn3Vcc_Motorcycle)

/* Expression: const
 * Referenced by: '<S3915>/Constant'
 */
#define rtCP_Constant_Value_fl         (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S3917>/Constant'
 */
#define rtCP_Constant_Value_ejy        (ObjClassn3Vcc_Bicycle)

/* Expression: const
 * Referenced by: '<S3918>/Constant'
 */
#define rtCP_Constant_Value_pr         (ObjClassn3Vcc_Motorcycle)

/* Expression: const
 * Referenced by: '<S3919>/Constant'
 */
#define rtCP_Constant_Value_h0         (ObjClassn3Vcc_Car)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S3803>/Constant1'
 */
#define rtCP_Constant1_Value_c         (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S3803>/Constant10'
 */
#define rtCP_Constant10_Value_b        (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Bicycle
 * Referenced by: '<S3803>/Constant11'
 */
#define rtCP_Constant11_Value_k        (ObjClassn3Vcc_Bicycle)

/* Expression: ObjClassn3Vcc.VehOfUkwnClass
 * Referenced by: '<S3803>/Constant12'
 */
#define rtCP_Constant12_Value_n        (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S3803>/Constant13'
 */
#define rtCP_Constant13_Value_a        (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S3803>/Constant15'
 */
#define rtCP_Constant15_Value_i        (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S3803>/Constant16'
 */
#define rtCP_Constant16_Value_j        (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S3803>/Constant17'
 */
#define rtCP_Constant17_Value_m        (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S3803>/Constant2'
 */
#define rtCP_Constant2_Value_n         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Car
 * Referenced by: '<S3803>/Constant3'
 */
#define rtCP_Constant3_Value_n         (ObjClassn3Vcc_Car)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S3803>/Constant4'
 */
#define rtCP_Constant4_Value_a1a       (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.Truck
 * Referenced by: '<S3803>/Constant5'
 */
#define rtCP_Constant5_Value_i         (ObjClassn3Vcc_Truck)

/* Expression: ObjClassn3Vcc.Ped
 * Referenced by: '<S3803>/Constant6'
 */
#define rtCP_Constant6_Value_m         (ObjClassn3Vcc_Ped)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S3803>/Constant7'
 */
#define rtCP_Constant7_Value_o         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S3803>/Constant8'
 */
#define rtCP_Constant8_Value_i         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Anim
 * Referenced by: '<S3803>/Constant9'
 */
#define rtCP_Constant9_Value_f         (ObjClassn3Vcc_Anim)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S6146>/Constant1'
 */
#define rtCP_Constant1_Value_br        (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S6146>/Constant10'
 */
#define rtCP_Constant10_Value_p        (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Bicycle
 * Referenced by: '<S6146>/Constant11'
 */
#define rtCP_Constant11_Value_d        (ObjClassn3Vcc_Bicycle)

/* Expression: ObjClassn3Vcc.VehOfUkwnClass
 * Referenced by: '<S6146>/Constant12'
 */
#define rtCP_Constant12_Value_nt       (ObjClassn3Vcc_VehOfUkwnClass)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S6146>/Constant13'
 */
#define rtCP_Constant13_Value_j        (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.ObjGen
 * Referenced by: '<S6146>/Constant16'
 */
#define rtCP_Constant16_Value_e        (ObjClassn3Vcc_ObjGen)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S6146>/Constant2'
 */
#define rtCP_Constant2_Value_jq        (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Car
 * Referenced by: '<S6146>/Constant3'
 */
#define rtCP_Constant3_Value_d         (ObjClassn3Vcc_Car)

/* Expression: ObjClassn3Vcc.Motorcycle
 * Referenced by: '<S6146>/Constant4'
 */
#define rtCP_Constant4_Value_n         (ObjClassn3Vcc_Motorcycle)

/* Expression: ObjClassn3Vcc.Truck
 * Referenced by: '<S6146>/Constant5'
 */
#define rtCP_Constant5_Value_e         (ObjClassn3Vcc_Truck)

/* Expression: ObjClassn3Vcc.Ped
 * Referenced by: '<S6146>/Constant6'
 */
#define rtCP_Constant6_Value_b         (ObjClassn3Vcc_Ped)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S6146>/Constant7'
 */
#define rtCP_Constant7_Value_b         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.UkwnClass
 * Referenced by: '<S6146>/Constant8'
 */
#define rtCP_Constant8_Value_o         (ObjClassn3Vcc_UkwnClass)

/* Expression: ObjClassn3Vcc.Anim
 * Referenced by: '<S6146>/Constant9'
 */
#define rtCP_Constant9_Value_l         (ObjClassn3Vcc_Anim)

/* Expression: Value
 * Referenced by: '<S1031>/Constant'
 */
#define rtCP_Constant_Value_d5         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S1235>/Constant'
 */
#define rtCP_Constant_Value_mw         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S1236>/Constant'
 */
#define rtCP_Constant_Value_o2r        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S1564>/Constant'
 */
#define rtCP_Constant_Value_o3         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S1565>/Constant'
 */
#define rtCP_Constant_Value_en3        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S2060>/Constant'
 */
#define rtCP_Constant_Value_dj         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2061>/Constant'
 */
#define rtCP_Constant_Value_hl         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: ObjMtnPat1Vcc.MovgToSelf
 * Referenced by: '<S2150>/Constant2'
 */
#define rtCP_Constant2_Value_lv        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: ObjMtnPat1Vcc.Staty
 * Referenced by: '<S2152>/Constant18'
 */
#define rtCP_Constant18_Value          (ObjMtnPat1Vcc_Staty)

/* Expression: ObjMtnPat1Vcc.MovgFromSelf
 * Referenced by: '<S2148>/Constant4'
 */
#define rtCP_Constant4_Value_lu        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: ObjMtnPat1Vcc.Ukwn
 * Referenced by: '<S2153>/Constant3'
 */
#define rtCP_Constant3_Value_c         (ObjMtnPat1Vcc_Ukwn)

/* Expression: Value
 * Referenced by: '<S2426>/Constant'
 */
#define rtCP_Constant_Value_k3a        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2448>/Constant'
 */
#define rtCP_Constant_Value_nu         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2472>/Constant'
 */
#define rtCP_Constant_Value_c0         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2496>/Constant'
 */
#define rtCP_Constant_Value_il         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2517>/Constant'
 */
#define rtCP_Constant_Value_bt         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2583>/Constant'
 */
#define rtCP_Constant_Value_djl        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2599>/Constant'
 */
#define rtCP_Constant_Value_ce         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3141>/Constant'
 */
#define rtCP_Constant_Value_gg         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3157>/Constant'
 */
#define rtCP_Constant_Value_p0i        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S808>/Constant'
 */
#define rtCP_Constant_Value_la         (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S897>/Constant'
 */
#define rtCP_Constant_Value_bn         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S920>/Constant'
 */
#define rtCP_Constant_Value_ip         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S942>/Constant'
 */
#define rtCP_Constant_Value_eol        (ObjMtnPat1Vcc_Ukwn)

/* Expression: Value
 * Referenced by: '<S744>/Constant'
 */
#define rtCP_Constant_Value_hne        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S747>/Constant'
 */
#define rtCP_Constant_Value_cgu        (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S2102>/Constant'
 */
#define rtCP_Constant_Value_lm         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S2103>/Constant'
 */
#define rtCP_Constant_Value_ov0        (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S2104>/Constant'
 */
#define rtCP_Constant_Value_id         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S2105>/Constant'
 */
#define rtCP_Constant_Value_e2u        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S2140>/Constant'
 */
#define rtCP_Constant_Value_fv         (ObjMtnPat1Vcc_Staty)

/* Expression: Value
 * Referenced by: '<S2154>/Constant'
 */
#define rtCP_Constant_Value_lx         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2157>/Constant'
 */
#define rtCP_Constant_Value_fle        (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S2146>/Constant'
 */
#define rtCP_Constant_Value_for        (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S2147>/Constant'
 */
#define rtCP_Constant_Value_pyj        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S2846>/Constant'
 */
#define rtCP_Constant_Value_jd         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2847>/Constant'
 */
#define rtCP_Constant_Value_m1y        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S2855>/Constant'
 */
#define rtCP_Constant_Value_e1d        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2856>/Constant'
 */
#define rtCP_Constant_Value_ae         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S2864>/Constant'
 */
#define rtCP_Constant_Value_ata        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2865>/Constant'
 */
#define rtCP_Constant_Value_ovn        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S2873>/Constant'
 */
#define rtCP_Constant_Value_ny         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2874>/Constant'
 */
#define rtCP_Constant_Value_nxj        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S2882>/Constant'
 */
#define rtCP_Constant_Value_n3         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S2883>/Constant'
 */
#define rtCP_Constant_Value_gs         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3412>/Constant'
 */
#define rtCP_Constant_Value_ht         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3413>/Constant'
 */
#define rtCP_Constant_Value_ik         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3421>/Constant'
 */
#define rtCP_Constant_Value_pq         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3422>/Constant'
 */
#define rtCP_Constant_Value_cu         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3430>/Constant'
 */
#define rtCP_Constant_Value_huo        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3431>/Constant'
 */
#define rtCP_Constant_Value_ncy        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3439>/Constant'
 */
#define rtCP_Constant_Value_dp         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3440>/Constant'
 */
#define rtCP_Constant_Value_bo0        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S3448>/Constant'
 */
#define rtCP_Constant_Value_c0a        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3449>/Constant'
 */
#define rtCP_Constant_Value_eom        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: const
 * Referenced by: '<S3790>/Constant'
 */
#define rtCP_Constant_Value_pw         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S3791>/Constant'
 */
#define rtCP_Constant_Value_p3o        (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S3792>/Constant'
 */
#define rtCP_Constant_Value_nyr        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S3793>/Constant'
 */
#define rtCP_Constant_Value_hk         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: const
 * Referenced by: '<S3828>/Constant'
 */
#define rtCP_Constant_Value_o0n        (ObjMtnPat1Vcc_Staty)

/* Expression: Value
 * Referenced by: '<S3842>/Constant'
 */
#define rtCP_Constant_Value_nou        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S3845>/Constant'
 */
#define rtCP_Constant_Value_kb         (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S3834>/Constant'
 */
#define rtCP_Constant_Value_jf         (ObjMtnPat1Vcc_Staty)

/* Expression: const
 * Referenced by: '<S3835>/Constant'
 */
#define rtCP_Constant_Value_nul        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S4534>/Constant'
 */
#define rtCP_Constant_Value_mmg        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S4535>/Constant'
 */
#define rtCP_Constant_Value_pwy        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S4543>/Constant'
 */
#define rtCP_Constant_Value_bc5        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S4544>/Constant'
 */
#define rtCP_Constant_Value_bw         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S4552>/Constant'
 */
#define rtCP_Constant_Value_jb         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S4553>/Constant'
 */
#define rtCP_Constant_Value_j5         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S4561>/Constant'
 */
#define rtCP_Constant_Value_otu        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S4562>/Constant'
 */
#define rtCP_Constant_Value_kg         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S4570>/Constant'
 */
#define rtCP_Constant_Value_fq         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S4571>/Constant'
 */
#define rtCP_Constant_Value_kl         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S5100>/Constant'
 */
#define rtCP_Constant_Value_bdz        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S5101>/Constant'
 */
#define rtCP_Constant_Value_ipg        (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S5109>/Constant'
 */
#define rtCP_Constant_Value_aw         (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S5110>/Constant'
 */
#define rtCP_Constant_Value_dy         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: Value
 * Referenced by: '<S5118>/Constant'
 */
#define rtCP_Constant_Value_lns        (ObjMtnPat1Vcc_MovgToSelf)

/* Expression: Value
 * Referenced by: '<S5119>/Constant'
 */
#define rtCP_Constant_Value_fs         (ObjMtnPat1Vcc_MovgFromSelf)

/* Expression: const
 * Referenced by: '<S5979>/Constant'
 */
#define rtCP_Constant_Value_l0k        (ObjMtnPat1Vcc_Staty)

/* Expression: Value
 * Referenced by: '<S514>/Constant'
 */
#define rtCP_Constant_Value_d2n        (OnOff1_Off)

/* Expression: Value
 * Referenced by: '<S518>/Constant'
 */
#define rtCP_Constant_Value_dv         (OnOff1_On)

/* Expression: Value
 * Referenced by: '<S25>/Constant'
 */
#define rtCP_Constant_Value_ovh        (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S369>/Constant'
 */
#define rtCP_Constant_Value_gu         (OnOff1Vcc_Off)

/* Expression: Value
 * Referenced by: '<S370>/Constant'
 */
#define rtCP_Constant_Value_pc         (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S391>/Constant'
 */
#define rtCP_Constant_Value_ggn        (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S392>/Constant'
 */
#define rtCP_Constant_Value_a4         (OnOff1Vcc_Off)

/* Expression: Value
 * Referenced by: '<S350>/Constant'
 */
#define rtCP_Constant_Value_n1u        (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S351>/Constant'
 */
#define rtCP_Constant_Value_oz0        (OnOff1Vcc_Off)

/* Expression: OnOff1Vcc.On
 * Referenced by: '<S456>/Constant'
 */
#define rtCP_Constant_Value_ly         (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S750>/Constant'
 */
#define rtCP_Constant_Value_n0         (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S751>/Constant'
 */
#define rtCP_Constant_Value_gxi        (OnOff1Vcc_Off)

/* Expression: Value
 * Referenced by: '<S752>/Constant'
 */
#define rtCP_Constant_Value_oqt        (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S753>/Constant'
 */
#define rtCP_Constant_Value_f5z        (OnOff1Vcc_Off)

/* Expression: Value
 * Referenced by: '<S754>/Constant'
 */
#define rtCP_Constant_Value_m1i        (OnOff1Vcc_On)

/* Expression: Value
 * Referenced by: '<S755>/Constant'
 */
#define rtCP_Constant_Value_nt         (OnOff1Vcc_Off)

/* Expression: Value
 * Referenced by: '<S5571>/Constant'
 */
#define rtCP_Constant_Value_fou        (OnOff1Vcc_On)

/* Expression: const
 * Referenced by: '<S908>/Constant'
 */
#define rtCP_Constant_Value_ntx        (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S892>/Constant'
 */
#define rtCP_Constant_Value_m1r        (PreSceniaroClass_AEBCarPosnInValidHostStright)

/* Expression: const
 * Referenced by: '<S895>/Constant'
 */
#define rtCP_Constant_Value_cb         (PreSceniaroClass_SceniaroInhibit)

/* Expression: const
 * Referenced by: '<S913>/Constant'
 */
#define rtCP_Constant_Value_pmw        (PreSceniaroClass_PedPosnLatInValidHostStright)

/* Expression: const
 * Referenced by: '<S914>/Constant'
 */
#define rtCP_Constant_Value_o4t        (PreSceniaroClass_CarPosnLatInValidHostStright)

/* Expression: const
 * Referenced by: '<S917>/Constant'
 */
#define rtCP_Constant_Value_ox         (PreSceniaroClass_MotorPosnLatInValidHostStright)

/* Expression: const
 * Referenced by: '<S921>/Constant'
 */
#define rtCP_Constant_Value_lz4        (PreSceniaroClass_SceniaroInhibit)

/* Expression: const
 * Referenced by: '<S617>/Constant'
 */
#define rtCP_Constant_Value_nd         (PreSceniaroClass_Pre_CCFT)

/* Expression: const
 * Referenced by: '<S618>/Constant'
 */
#define rtCP_Constant_Value_fm         (PreSceniaroClass_Pre_CSTA_LN)

/* Expression: const
 * Referenced by: '<S619>/Constant'
 */
#define rtCP_Constant_Value_o0q        (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S620>/Constant'
 */
#define rtCP_Constant_Value_fc0        (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S621>/Constant'
 */
#define rtCP_Constant_Value_dfr        (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S622>/Constant'
 */
#define rtCP_Constant_Value_px         (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S668>/Constant'
 */
#define rtCP_Constant_Value_jj         (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S671>/Constant'
 */
#define rtCP_Constant_Value_as         (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S672>/Constant'
 */
#define rtCP_Constant_Value_gt         (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S2159>/Constant'
 */
#define rtCP_Constant_Value_ig         (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S2160>/Constant'
 */
#define rtCP_Constant_Value_dmu        (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S2161>/Constant'
 */
#define rtCP_Constant_Value_e1a        (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S2162>/Constant'
 */
#define rtCP_Constant_Value_cv         (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S2243>/Constant'
 */
#define rtCP_Constant_Value_h0j        (PreSceniaroClass_Pre_CCStrightInpath)

/* Expression: const
 * Referenced by: '<S3847>/Constant'
 */
#define rtCP_Constant_Value_lmd        (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S3848>/Constant'
 */
#define rtCP_Constant_Value_jg1        (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S3849>/Constant'
 */
#define rtCP_Constant_Value_nys        (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S3850>/Constant'
 */
#define rtCP_Constant_Value_iz         (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S3931>/Constant'
 */
#define rtCP_Constant_Value_g1         (PreSceniaroClass_Pre_CCStrightInpath)

/* Expression: const
 * Referenced by: '<S5655>/Constant'
 */
#define rtCP_Constant_Value_he         (PreSceniaroClass_Pre_CSTA_LN)

/* Expression: const
 * Referenced by: '<S5656>/Constant'
 */
#define rtCP_Constant_Value_ppz        (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S5657>/Constant'
 */
#define rtCP_Constant_Value_eyi        (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S5658>/Constant'
 */
#define rtCP_Constant_Value_cnj        (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S5659>/Constant'
 */
#define rtCP_Constant_Value_nb         (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S5660>/Constant'
 */
#define rtCP_Constant_Value_jfg        (PreSceniaroClass_Pre_CCFT)

/* Expression: const
 * Referenced by: '<S5702>/Constant'
 */
#define rtCP_Constant_Value_l0u        (PreSceniaroClass_Pre_CSTA_LN)

/* Expression: const
 * Referenced by: '<S5703>/Constant'
 */
#define rtCP_Constant_Value_ety        (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S5704>/Constant'
 */
#define rtCP_Constant_Value_pvg        (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S5705>/Constant'
 */
#define rtCP_Constant_Value_ok         (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S5706>/Constant'
 */
#define rtCP_Constant_Value_in         (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S5707>/Constant'
 */
#define rtCP_Constant_Value_cw         (PreSceniaroClass_Pre_CCFT)

/* Expression: const
 * Referenced by: '<S6120>/Constant'
 */
#define rtCP_Constant_Value_c2         (PreSceniaroClass_Pre_CCStrightInpath)

/* Expression: const
 * Referenced by: '<S6121>/Constant'
 */
#define rtCP_Constant_Value_eb0        (PreSceniaroClass_Pre_GenObjStrightInpath)

/* Expression: const
 * Referenced by: '<S6122>/Constant'
 */
#define rtCP_Constant_Value_e5g        (PreSceniaroClass_Pre_CBStrightInpath)

/* Expression: const
 * Referenced by: '<S6123>/Constant'
 */
#define rtCP_Constant_Value_bsv        (PreSceniaroClass_Pre_CPStrightInpath)

/* Expression: const
 * Referenced by: '<S6124>/Constant'
 */
#define rtCP_Constant_Value_pcn        (PreSceniaroClass_Pre_CCStrightInpath)

/* Expression: const
 * Referenced by: '<S6125>/Constant'
 */
#define rtCP_Constant_Value_ju         (PreSceniaroClass_Pre_GenObjStrightInpath)

/* Expression: const
 * Referenced by: '<S6126>/Constant'
 */
#define rtCP_Constant_Value_kjr        (PreSceniaroClass_Pre_CBStrightInpath)

/* Expression: const
 * Referenced by: '<S6127>/Constant'
 */
#define rtCP_Constant_Value_ek         (PreSceniaroClass_Pre_CPStrightInpath)

/* Expression: const
 * Referenced by: '<S6134>/Constant'
 */
#define rtCP_Constant_Value_gr         (PreSceniaroClass_Pre_CCFT)

/* Expression: const
 * Referenced by: '<S6135>/Constant'
 */
#define rtCP_Constant_Value_m1s        (PreSceniaroClass_Pre_CSTA_LN)

/* Expression: const
 * Referenced by: '<S6136>/Constant'
 */
#define rtCP_Constant_Value_l2         (PreSceniaroClass_Pre_CSTA_RN)

/* Expression: const
 * Referenced by: '<S6137>/Constant'
 */
#define rtCP_Constant_Value_new        (PreSceniaroClass_Pre_CPTA_LN)

/* Expression: const
 * Referenced by: '<S6138>/Constant'
 */
#define rtCP_Constant_Value_ez         (PreSceniaroClass_Pre_CPTA_LF)

/* Expression: const
 * Referenced by: '<S6139>/Constant'
 */
#define rtCP_Constant_Value_n4         (PreSceniaroClass_Pre_CPTA_RF)

/* Expression: const
 * Referenced by: '<S6131>/Constant'
 */
#define rtCP_Constant_Value_o2z        (Prefill_ACTIVE)

/* Expression: const
 * Referenced by: '<S6158>/Constant'
 */
#define rtCP_Constant_Value_me         (Prefill_ACTIVE)

/* Expression: Value
 * Referenced by: '<S965>/Constant'
 */
#define rtCP_Constant_Value_p30        (PrimTarWarn1VccPrimTarInPahNow0_FALSE)

/* Expression: Value
 * Referenced by: '<S973>/Constant'
 */
#define rtCP_Constant_Value_hjs        (PrimTarWarn1VccPrimTarInPahNow0_TRUE)

/* Expression: Value
 * Referenced by: '<S974>/Constant'
 */
#define rtCP_Constant_Value_fh         (PrimTarWarn1VccPrimTarInPahNow0_FALSE)

/* Expression: Value
 * Referenced by: '<S59>/Constant'
 */
#define rtCP_Constant_Value_mf         (PrimTarWarn1VccPrimTarInPahNow0_TRUE)

/* Expression: Value
 * Referenced by: '<S1577>/Constant'
 */
#define rtCP_Constant_Value_dx         (Relbl1Vcc_Relbl)

/* Expression: Value
 * Referenced by: '<S1582>/Constant'
 */
#define rtCP_Constant_Value_e55        (Relbl1Vcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S1799>/Constant'
 */
#define rtCP_Constant_Value_a0         (Relbl1Vcc_Relbl)

/* Expression: Value
 * Referenced by: '<S937>/Constant'
 */
#define rtCP_Constant_Value_ml         (Relbl1Vcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S1807>/Constant'
 */
#define rtCP_Constant_Value_nkj        (Relbl1Vcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S1804>/Constant'
 */
#define rtCP_Constant_Value_a5         (Relbl1Vcc_Relbl)

/* Expression: Value
 * Referenced by: '<S560>/Constant'
 */
#define rtCP_Constant_Value_dpf        (Relbl1Vcc_Relbl)

/* Expression: Value
 * Referenced by: '<S642>/Constant'
 */
#define rtCP_Constant_Value_ks         (Relbl1Vcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S687>/Constant'
 */
#define rtCP_Constant_Value_ebb        (Relbl1Vcc_NotRelbl)

/* Expression: Value
 * Referenced by: '<S510>/Constant'
 */
#define rtCP_Constant_Value_fo1        (ReqSts1Vcc_ThreatHi)

/* Expression: Value
 * Referenced by: '<S511>/Constant'
 */
#define rtCP_Constant_Value_mk         (ReqSts1Vcc_Ukwn)

/* Expression: Value
 * Referenced by: '<S512>/Constant'
 */
#define rtCP_Constant_Value_cj         (ReqSts1Vcc_ThreatMed)

/* Expression: Value
 * Referenced by: '<S5572>/Constant'
 */
#define rtCP_Constant_Value_fp         (ReqSts1Vcc_ThreatMed)

/* Expression: Value
 * Referenced by: '<S5573>/Constant'
 */
#define rtCP_Constant_Value_c3i        (ReqSts1Vcc_ThreatHi)

/* Expression: Value
 * Referenced by: '<S5984>/Constant'
 */
#define rtCP_Constant_Value_guj        (Snvty1_LoSnvty)

/* Expression: Value
 * Referenced by: '<S5985>/Constant'
 */
#define rtCP_Constant_Value_od         (Snvty1_NormSnvty)

/* Expression: Value
 * Referenced by: '<S5986>/Constant'
 */
#define rtCP_Constant_Value_okc        (Snvty1_HiSnvty)

/* Expression: Value
 * Referenced by: '<S515>/Constant'
 */
#define rtCP_Constant_Value_cnf        (TqAllwdPosAndNeg_NoTq)

/* Expression: Value
 * Referenced by: '<S516>/Constant'
 */
#define rtCP_Constant_Value_cd         (TqAllwdPosAndNeg_Neg)

/* Expression: Value
 * Referenced by: '<S517>/Constant'
 */
#define rtCP_Constant_Value_fy3        (TqAllwdPosAndNeg_Pos)

/* Expression: Value
 * Referenced by: '<S441>/Constant'
 */
#define rtCP_Constant_Value_fdh        (VehMtnStSafeGroup0VehMtnSt0_StandStillVal3)

/* Expression: Value
 * Referenced by: '<S442>/Constant'
 */
#define rtCP_Constant_Value_b0z        (VehMtnStSafeGroup0VehMtnSt0_StandStillVal2)

/* Computed Parameter: rtCP_Constant_Value_fcb
 * Referenced by: '<S5893>/Constant'
 */
#define rtCP_Constant_Value_fcb        (1)

/* Computed Parameter: rtCP_Constant_Value_gv
 * Referenced by: '<S5916>/Constant'
 */
#define rtCP_Constant_Value_gv         (1)

/* Computed Parameter: rtCP_ForIterator_IterationLimit
 * Referenced by: '<S5877>/For Iterator'
 */
#define rtCP_ForIterator_IterationLimit (4)

/* Computed Parameter: rtCP_Constant_Value_ly1
 * Referenced by: '<S5830>/Constant'
 */
#define rtCP_Constant_Value_ly1        (1)

/* Computed Parameter: rtCP_Constant_Value_jy
 * Referenced by: '<S5836>/Constant'
 */
#define rtCP_Constant_Value_jy         (1)

/* Computed Parameter: rtCP_ForIterator_IterationLimit_e
 * Referenced by: '<S5814>/For Iterator'
 */
#define rtCP_ForIterator_IterationLimit_e (4)

/* Computed Parameter: rtCP_Constant_Value_nv
 * Referenced by: '<S5681>/Constant'
 */
#define rtCP_Constant_Value_nv         (0)

/* Computed Parameter: rtCP_Constant_Value_jx
 * Referenced by: '<S5682>/Constant'
 */
#define rtCP_Constant_Value_jx         (8)

/* Computed Parameter: rtCP_Constant_Value_c5
 * Referenced by: '<S5683>/Constant'
 */
#define rtCP_Constant_Value_c5         (13)

/* Computed Parameter: rtCP_Constant_Value_df2
 * Referenced by: '<S5685>/Constant'
 */
#define rtCP_Constant_Value_df2        (0)

/* Computed Parameter: rtCP_Constant_Value_n2
 * Referenced by: '<S5686>/Constant'
 */
#define rtCP_Constant_Value_n2         (0)

/* Computed Parameter: rtCP_Constant_Value_dhw
 * Referenced by: '<S5728>/Constant'
 */
#define rtCP_Constant_Value_dhw        (0)

/* Computed Parameter: rtCP_Constant_Value_em
 * Referenced by: '<S5729>/Constant'
 */
#define rtCP_Constant_Value_em         (8)

/* Computed Parameter: rtCP_Constant_Value_brc
 * Referenced by: '<S5730>/Constant'
 */
#define rtCP_Constant_Value_brc        (13)

/* Computed Parameter: rtCP_Constant_Value_av
 * Referenced by: '<S5732>/Constant'
 */
#define rtCP_Constant_Value_av         (0)

/* Computed Parameter: rtCP_Constant_Value_hpb
 * Referenced by: '<S5733>/Constant'
 */
#define rtCP_Constant_Value_hpb        (0)

/* Expression: int32(0)
 * Referenced by: '<S6194>/Constant35'
 */
#define rtCP_Constant35_Value          (0)

/* Computed Parameter: rtCP_Constant1_Value_g
 * Referenced by: '<S6205>/Constant1'
 */
#define rtCP_Constant1_Value_g         (1)

/* Computed Parameter: rtCP_Constant2_Value_d
 * Referenced by: '<S6205>/Constant2'
 */
#define rtCP_Constant2_Value_d         (0)

/* Computed Parameter: rtCP_Constant44_Value
 * Referenced by: '<S6205>/Constant44'
 */
#define rtCP_Constant44_Value          (2)

/* Expression: int32(0)
 * Referenced by: '<S6195>/Constant33'
 */
#define rtCP_Constant33_Value          (0)

/* Computed Parameter: rtCP_motor_out_Value
 * Referenced by: '<S6196>/motor_out'
 */
#define rtCP_motor_out_Value           (6)

/* Expression: int32(0)
 * Referenced by: '<S6197>/Constant'
 */
#define rtCP_Constant_Value_jj0        (0)

/* Expression: int32(0)
 * Referenced by: '<S6143>/Constant29'
 */
#define rtCP_Constant29_Value          (0)

/* Expression: int32(0)
 * Referenced by: '<S6143>/Constant34'
 */
#define rtCP_Constant34_Value          (0)

/* Computed Parameter: rtCP_Constant1_Value_nx
 * Referenced by: '<S6198>/Constant1'
 */
#define rtCP_Constant1_Value_nx        (1)

/* Expression: int32(0)
 * Referenced by: '<S6198>/Constant13'
 */
#define rtCP_Constant13_Value_h        (0)

/* Computed Parameter: rtCP_Constant2_Value_p
 * Referenced by: '<S6198>/Constant2'
 */
#define rtCP_Constant2_Value_p         (0)

/* Computed Parameter: rtCP_Constant44_Value_k
 * Referenced by: '<S6198>/Constant44'
 */
#define rtCP_Constant44_Value_k        (2)

/* Expression: int32(6)
 * Referenced by: '<S6199>/Constant1'
 */
#define rtCP_Constant1_Value_go        (6)

/* Expression: int32(0)
 * Referenced by: '<S6199>/Constant13'
 */
#define rtCP_Constant13_Value_f        (0)

/* Expression: int32(1)
 * Referenced by: '<S6199>/Constant2'
 */
#define rtCP_Constant2_Value_dp        (1)

/* Expression: int32(11)
 * Referenced by: '<S6199>/Constant3'
 */
#define rtCP_Constant3_Value_j         (11)

/* Expression: int32(0)
 * Referenced by: '<S6199>/Constant4'
 */
#define rtCP_Constant4_Value_ps        (0)

/* Expression: int32(4)
 * Referenced by: '<S6201>/Constant1'
 */
#define rtCP_Constant1_Value_dp        (4)

/* Expression: int32(0)
 * Referenced by: '<S6201>/Constant13'
 */
#define rtCP_Constant13_Value_l        (0)

/* Expression: int32(0)
 * Referenced by: '<S6201>/Constant38'
 */
#define rtCP_Constant38_Value          (0)

/* Computed Parameter: rtCP_Saturation_UpperSat
 * Referenced by: '<S248>/Saturation'
 */
#define rtCP_Saturation_UpperSat       (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat
 * Referenced by: '<S248>/Saturation'
 */
#define rtCP_Saturation_LowerSat       (0.0F)

/* Expression: ZeroThreshold
 * Referenced by: '<S592>/QuadraticEquationSolver'
 */
#define rtCP_QuadraticEquationSolver_ZeroThreshold (0.01F)

/* Expression: single(0)
 * Referenced by: '<S1016>/FirstPointInSegment'
 */
#define rtCP_FirstPointInSegment_Value (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1025>/Constant'
 */
#define rtCP_Constant_Value_pvb        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1025>/Constant1'
 */
#define rtCP_Constant1_Value_hq        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1025>/Constant2'
 */
#define rtCP_Constant2_Value_m0        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1025>/Constant3'
 */
#define rtCP_Constant3_Value_i         (0.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S1030>/Constant1'
 */
#define rtCP_Constant1_Value_l         (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S1030>/Constant2'
 */
#define rtCP_Constant2_Value_g         (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1038>/Constant5'
 */
#define rtCP_Constant5_Value_j         (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_dl
 * Referenced by: '<S1028>/Constant'
 */
#define rtCP_Constant_Value_dl         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pvn
 * Referenced by: '<S1032>/Constant'
 */
#define rtCP_Constant_Value_pvn        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_kh
 * Referenced by: '<S1032>/Constant1'
 */
#define rtCP_Constant1_Value_kh        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1042>/Constant'
 */
#define rtCP_Constant_Value_hb         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_dii
 * Referenced by: '<S1046>/Constant'
 */
#define rtCP_Constant_Value_dii        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value
 * Referenced by: '<S1044>/LimitSource'
 */
#define rtCP_LimitSource_Value         (0.0001F)

/* Computed Parameter: rtCP_Gain_Gain_b
 * Referenced by: '<S1043>/Gain'
 */
#define rtCP_Gain_Gain_b               (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_nj
 * Referenced by: '<S1049>/Constant'
 */
#define rtCP_Constant_Value_nj         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_kh4
 * Referenced by: '<S1049>/Constant1'
 */
#define rtCP_Constant1_Value_kh4       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1054>/Constant'
 */
#define rtCP_Constant_Value_ak         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ga
 * Referenced by: '<S1058>/Constant'
 */
#define rtCP_Constant_Value_ga         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_f
 * Referenced by: '<S1056>/LimitSource'
 */
#define rtCP_LimitSource_Value_f       (0.0001F)

/* Expression: single(0.5)
 * Referenced by: '<S1050>/Constant'
 */
#define rtCP_Constant_Value_gkf        (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_h
 * Referenced by: '<S1055>/Gain'
 */
#define rtCP_Gain_Gain_h               (-1.0F)

/* Expression: single(pi)
 * Referenced by: '<S1065>/Saturation'
 */
#define rtCP_Saturation_UpperSat_i     (3.14159274F)

/* Expression: single(-pi)
 * Referenced by: '<S1065>/Saturation'
 */
#define rtCP_Saturation_LowerSat_h     (-3.14159274F)

/* Expression: single(pi/2)
 * Referenced by: '<S1064>/Constant_1'
 */
#define rtCP_Constant_1_Value          (1.57079637F)

/* Expression: single(pi)
 * Referenced by: '<S1064>/Constant_2'
 */
#define rtCP_Constant_2_Value          (3.14159274F)

/* Computed Parameter: rtCP_Gain_1_Gain_f
 * Referenced by: '<S1064>/Gain_1'
 */
#define rtCP_Gain_1_Gain_f             (-1.0F)

/* Expression: ZeroThreshold
 * Referenced by: '<S1097>/QuadraticEquationSolver'
 */
#define rtCP_QuadraticEquationSolver_ZeroThreshold_l (0.01F)

/* Computed Parameter: rtCP_Constant_Value_mke
 * Referenced by: '<S1098>/Constant'
 */
#define rtCP_Constant_Value_mke        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mr
 * Referenced by: '<S1099>/Constant'
 */
#define rtCP_Constant_Value_mr         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1100>/Constant5'
 */
#define rtCP_Constant5_Value_ih        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_dl5
 * Referenced by: '<S1104>/Constant'
 */
#define rtCP_Constant_Value_dl5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ep5
 * Referenced by: '<S1105>/Constant'
 */
#define rtCP_Constant_Value_ep5        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1106>/Constant5'
 */
#define rtCP_Constant5_Value_l         (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_h4
 * Referenced by: '<S1110>/Constant'
 */
#define rtCP_Constant_Value_h4         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_b1
 * Referenced by: '<S1113>/Constant'
 */
#define rtCP_Constant_Value_b1         (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_g
 * Referenced by: '<S1095>/Gain'
 */
#define rtCP_Gain_Gain_g               (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_j
 * Referenced by: '<S1096>/Gain'
 */
#define rtCP_Gain_Gain_j               (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_d
 * Referenced by: '<S1097>/Gain'
 */
#define rtCP_Gain_Gain_d               (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ao
 * Referenced by: '<S1117>/Constant'
 */
#define rtCP_Constant_Value_ao         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gf4
 * Referenced by: '<S1118>/Constant'
 */
#define rtCP_Constant_Value_gf4        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1119>/Constant5'
 */
#define rtCP_Constant5_Value_k         (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_bz
 * Referenced by: '<S1123>/Constant'
 */
#define rtCP_Constant_Value_bz         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_e4
 * Referenced by: '<S1124>/Constant'
 */
#define rtCP_Constant_Value_e4         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1125>/Constant5'
 */
#define rtCP_Constant5_Value_kb        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_di5
 * Referenced by: '<S1129>/Constant'
 */
#define rtCP_Constant_Value_di5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kw
 * Referenced by: '<S1132>/Constant'
 */
#define rtCP_Constant_Value_kw         (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_e2
 * Referenced by: '<S1114>/Gain'
 */
#define rtCP_Gain_Gain_e2              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_i
 * Referenced by: '<S1115>/Gain'
 */
#define rtCP_Gain_Gain_i               (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_c
 * Referenced by: '<S1116>/Gain'
 */
#define rtCP_Gain_Gain_c               (0.5F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1220>/Constant5'
 */
#define rtCP_Constant5_Value_p         (1.0E+10F)

/* Computed Parameter: rtCP_Gain3_Gain
 * Referenced by: '<S1215>/Gain3'
 */
#define rtCP_Gain3_Gain                (-2.0F)

/* Expression: single(1/2)
 * Referenced by: '<S1213>/Constant'
 */
#define rtCP_Constant_Value_n0s        (0.5F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1216>/Constant5'
 */
#define rtCP_Constant5_Value_dn        (1.0E+10F)

/* Computed Parameter: rtCP_Gain_Gain_bz
 * Referenced by: '<S1213>/Gain'
 */
#define rtCP_Gain_Gain_bz              (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_ow3
 * Referenced by: '<S1202>/Constant'
 */
#define rtCP_Constant_Value_ow3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ed
 * Referenced by: '<S1203>/Constant'
 */
#define rtCP_Constant_Value_ed         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1204>/Constant5'
 */
#define rtCP_Constant5_Value_hu        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1209>/Constant5'
 */
#define rtCP_Constant5_Value_ex        (1.0E+10F)

/* Computed Parameter: rtCP_Zero_1_Value
 * Referenced by: '<S1200>/Zero_1'
 */
#define rtCP_Zero_1_Value              (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain
 * Referenced by: '<S1198>/Gain1'
 */
#define rtCP_Gain1_Gain                (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_h
 * Referenced by: '<S1200>/Gain1'
 */
#define rtCP_Gain1_Gain_h              (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain
 * Referenced by: '<S1200>/Gain2'
 */
#define rtCP_Gain2_Gain                (2.0F)

/* Expression: single(0)
 * Referenced by: '<S1225>/Zero_1'
 */
#define rtCP_Zero_1_Value_h            (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1227>/Constant5'
 */
#define rtCP_Constant5_Value_de        (1.0E+10F)

/* Computed Parameter: rtCP_Zero_1_Value_k
 * Referenced by: '<S1226>/Zero_1'
 */
#define rtCP_Zero_1_Value_k            (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_d
 * Referenced by: '<S1226>/Gain1'
 */
#define rtCP_Gain1_Gain_d              (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_o
 * Referenced by: '<S1226>/Gain2'
 */
#define rtCP_Gain2_Gain_o              (2.0F)

/* Expression: single(0)
 * Referenced by: '<S1076>/Constant'
 */
#define rtCP_Constant_Value_mzxu       (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_b
 * Referenced by: '<S1084>/LimitSource'
 */
#define rtCP_LimitSource_Value_b       (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ede
 * Referenced by: '<S1085>/Constant'
 */
#define rtCP_Constant_Value_ede        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_my
 * Referenced by: '<S1086>/Constant'
 */
#define rtCP_Constant_Value_my         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_g
 * Referenced by: '<S1087>/LimitSource'
 */
#define rtCP_LimitSource_Value_g       (0.01F)

/* Computed Parameter: rtCP_Constant_Value_hdz
 * Referenced by: '<S1088>/Constant'
 */
#define rtCP_Constant_Value_hdz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ksi
 * Referenced by: '<S1089>/Constant'
 */
#define rtCP_Constant_Value_ksi        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_o5v
 * Referenced by: '<S1090>/Constant'
 */
#define rtCP_Constant_Value_o5v        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ojr
 * Referenced by: '<S1091>/Constant'
 */
#define rtCP_Constant_Value_ojr        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_npz
 * Referenced by: '<S1092>/Constant'
 */
#define rtCP_Constant_Value_npz        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1078>/Constant'
 */
#define rtCP_Constant_Value_el         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1078>/Constant1'
 */
#define rtCP_Constant1_Value_j         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_h
 * Referenced by: '<S1173>/LimitSource'
 */
#define rtCP_LimitSource_Value_h       (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_e
 * Referenced by: '<S1174>/LimitSource'
 */
#define rtCP_LimitSource_Value_e       (0.01F)

/* Computed Parameter: rtCP_Constant_Value_dv3
 * Referenced by: '<S1175>/Constant'
 */
#define rtCP_Constant_Value_dv3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_guy
 * Referenced by: '<S1176>/Constant'
 */
#define rtCP_Constant_Value_guy        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_o
 * Referenced by: '<S1177>/LimitSource'
 */
#define rtCP_LimitSource_Value_o       (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_en
 * Referenced by: '<S1178>/LimitSource'
 */
#define rtCP_LimitSource_Value_en      (0.01F)

/* Computed Parameter: rtCP_Zero_Value
 * Referenced by: '<S1184>/Zero'
 */
#define rtCP_Zero_Value                (0.0F)

/* Computed Parameter: rtCP_Constant_Value_eat
 * Referenced by: '<S1185>/Constant'
 */
#define rtCP_Constant_Value_eat        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jw
 * Referenced by: '<S1186>/Constant'
 */
#define rtCP_Constant_Value_jw         (0.0F)

/* Computed Parameter: rtCP_Zero_1_Value_m
 * Referenced by: '<S1179>/Zero_1'
 */
#define rtCP_Zero_1_Value_m            (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1187>/Constant5'
 */
#define rtCP_Constant5_Value_o         (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_dzi
 * Referenced by: '<S1181>/Constant'
 */
#define rtCP_Constant_Value_dzi        (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_hg
 * Referenced by: '<S1196>/Constant'
 */
#define rtCP_Constant_Value_hg         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_bb
 * Referenced by: '<S1197>/LimitSource'
 */
#define rtCP_LimitSource_Value_bb      (0.01F)

/* Expression: single(2)
 * Referenced by: '<S1183>/Constant'
 */
#define rtCP_Constant_Value_hlb        (2.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1231>/Constant'
 */
#define rtCP_Constant_Value_o0y        (0.5F)

/* Expression: single(pi/2)
 * Referenced by: '<S1070>/Constant'
 */
#define rtCP_Constant_Value_iu2        (1.57079637F)

/* Computed Parameter: rtCP_Gain1_Gain_c
 * Referenced by: '<S1078>/Gain1'
 */
#define rtCP_Gain1_Gain_c              (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_a
 * Referenced by: '<S1078>/Gain2'
 */
#define rtCP_Gain2_Gain_a              (-1.0F)

/* Computed Parameter: rtCP_ALgtRqrd_Y0
 * Referenced by: '<S978>/ALgtRqrd'
 */
#define rtCP_ALgtRqrd_Y0               (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jjg
 * Referenced by: '<S998>/Constant'
 */
#define rtCP_Constant_Value_jjg        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ki
 * Referenced by: '<S984>/Constant1'
 */
#define rtCP_Constant1_Value_ki        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pxz
 * Referenced by: '<S1003>/Constant'
 */
#define rtCP_Constant_Value_pxz        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_a
 * Referenced by: '<S1001>/LimitSource'
 */
#define rtCP_LimitSource_Value_a       (0.0001F)

/* Computed Parameter: rtCP_Constant_Value_pb
 * Referenced by: '<S1237>/Constant'
 */
#define rtCP_Constant_Value_pb         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mfk
 * Referenced by: '<S1238>/Constant'
 */
#define rtCP_Constant_Value_mfk        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nw
 * Referenced by: '<S1239>/Constant'
 */
#define rtCP_Constant_Value_nw         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i1
 * Referenced by: '<S1240>/Constant'
 */
#define rtCP_Constant_Value_i1         (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_i3
 * Referenced by: '<S1000>/Gain'
 */
#define rtCP_Gain_Gain_i3              (-1.0F)

/* Expression: single(0.001)
 * Referenced by: '<S1009>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat      (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_m
 * Referenced by: '<S1009>/Saturation'
 */
#define rtCP_Saturation_UpperSat_m     (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_h2
 * Referenced by: '<S1009>/Saturation'
 */
#define rtCP_Saturation_LowerSat_h2    (0.0F)

/* Computed Parameter: rtCP_Merge_1_InitialOutput
 * Referenced by: '<S986>/Merge'
 */
#define rtCP_Merge_1_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_Merge_2_InitialOutput
 * Referenced by: '<S986>/Merge'
 */
#define rtCP_Merge_2_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_Merge_3_InitialOutput
 * Referenced by: '<S986>/Merge'
 */
#define rtCP_Merge_3_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_Merge_4_InitialOutput
 * Referenced by: '<S986>/Merge'
 */
#define rtCP_Merge_4_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_Merge_5_InitialOutput
 * Referenced by: '<S986>/Merge'
 */
#define rtCP_Merge_5_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_Merge_6_InitialOutput
 * Referenced by: '<S986>/Merge'
 */
#define rtCP_Merge_6_InitialOutput     (0.0F)

/* Computed Parameter: rtCP_ALatRqrd_Y0
 * Referenced by: '<S979>/ALatRqrd'
 */
#define rtCP_ALatRqrd_Y0               (0.0F)

/* Computed Parameter: rtCP_PosnLatRelAtTTR_Y0
 * Referenced by: '<S979>/PosnLatRelAtTTR'
 */
#define rtCP_PosnLatRelAtTTR_Y0        (0.0F)

/* Computed Parameter: rtCP_ProjectedLengthSideLat_Y0
 * Referenced by: '<S979>/ProjectedLengthSideLat'
 */
#define rtCP_ProjectedLengthSideLat_Y0 (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ap
 * Referenced by: '<S1250>/Constant'
 */
#define rtCP_Constant_Value_ap         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cq
 * Referenced by: '<S1241>/Constant'
 */
#define rtCP_Constant_Value_cq         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_nt
 * Referenced by: '<S1241>/Constant1'
 */
#define rtCP_Constant1_Value_nt        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_i
 * Referenced by: '<S1241>/Constant2'
 */
#define rtCP_Constant2_Value_i         (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1242>/Constant'
 */
#define rtCP_Constant_Value_mwm        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_hs
 * Referenced by: '<S1255>/Constant'
 */
#define rtCP_Constant_Value_hs         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_n0h
 * Referenced by: '<S1258>/Constant'
 */
#define rtCP_Constant_Value_n0h        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1246>/Constant'
 */
#define rtCP_Constant_Value_bq2        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_aq5
 * Referenced by: '<S1261>/Constant'
 */
#define rtCP_Constant_Value_aq5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gvy
 * Referenced by: '<S1262>/Constant'
 */
#define rtCP_Constant_Value_gvy        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1247>/Constant2'
 */
#define rtCP_Constant2_Value_e         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1247>/Constant3'
 */
#define rtCP_Constant3_Value_pk        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_h3
 * Referenced by: '<S1243>/Gain'
 */
#define rtCP_Gain_Gain_h3              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_n
 * Referenced by: '<S1244>/Gain'
 */
#define rtCP_Gain_Gain_n               (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_l
 * Referenced by: '<S1247>/Gain1'
 */
#define rtCP_Gain1_Gain_l              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_dg
 * Referenced by: '<S979>/Gain1'
 */
#define rtCP_Gain1_Gain_dg             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_i
 * Referenced by: '<S1247>/Gain2'
 */
#define rtCP_Gain2_Gain_i              (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_b
 * Referenced by: '<S1248>/Gain2'
 */
#define rtCP_Gain2_Gain_b              (2.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ou
 * Referenced by: '<S1249>/Gain2'
 */
#define rtCP_Gain2_Gain_ou             (2.0F)

/* Computed Parameter: rtCP_Constant_Value_m03
 * Referenced by: '<S1378>/Constant'
 */
#define rtCP_Constant_Value_m03        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_kc
 * Referenced by: '<S1378>/Constant1'
 */
#define rtCP_Constant1_Value_kc        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1383>/Constant'
 */
#define rtCP_Constant_Value_gst        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ef
 * Referenced by: '<S1387>/Constant'
 */
#define rtCP_Constant_Value_ef         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_a4
 * Referenced by: '<S1385>/LimitSource'
 */
#define rtCP_LimitSource_Value_a4      (0.0001F)

/* Expression: single(0.5)
 * Referenced by: '<S1379>/Constant'
 */
#define rtCP_Constant_Value_b1r        (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_l5
 * Referenced by: '<S1384>/Gain'
 */
#define rtCP_Gain_Gain_l5              (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_d2h
 * Referenced by: '<S1427>/Constant'
 */
#define rtCP_Constant_Value_d2h        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fg
 * Referenced by: '<S1428>/Constant'
 */
#define rtCP_Constant_Value_fg         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1429>/Constant5'
 */
#define rtCP_Constant5_Value_ac        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_hjsl
 * Referenced by: '<S1433>/Constant'
 */
#define rtCP_Constant_Value_hjsl       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_poz
 * Referenced by: '<S1434>/Constant'
 */
#define rtCP_Constant_Value_poz        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1435>/Constant5'
 */
#define rtCP_Constant5_Value_lz        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_cm
 * Referenced by: '<S1439>/Constant'
 */
#define rtCP_Constant_Value_cm         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oxo
 * Referenced by: '<S1442>/Constant'
 */
#define rtCP_Constant_Value_oxo        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_eq
 * Referenced by: '<S1424>/Gain'
 */
#define rtCP_Gain_Gain_eq              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_gv
 * Referenced by: '<S1425>/Gain'
 */
#define rtCP_Gain_Gain_gv              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_ha
 * Referenced by: '<S1426>/Gain'
 */
#define rtCP_Gain_Gain_ha              (0.5F)

/* Computed Parameter: rtCP_Constant_Value_duy
 * Referenced by: '<S1446>/Constant'
 */
#define rtCP_Constant_Value_duy        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_js
 * Referenced by: '<S1447>/Constant'
 */
#define rtCP_Constant_Value_js         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1448>/Constant5'
 */
#define rtCP_Constant5_Value_je        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_kf
 * Referenced by: '<S1452>/Constant'
 */
#define rtCP_Constant_Value_kf         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kgu
 * Referenced by: '<S1453>/Constant'
 */
#define rtCP_Constant_Value_kgu        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1454>/Constant5'
 */
#define rtCP_Constant5_Value_al        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_gln
 * Referenced by: '<S1458>/Constant'
 */
#define rtCP_Constant_Value_gln        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kvw
 * Referenced by: '<S1461>/Constant'
 */
#define rtCP_Constant_Value_kvw        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_du
 * Referenced by: '<S1443>/Gain'
 */
#define rtCP_Gain_Gain_du              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_o
 * Referenced by: '<S1444>/Gain'
 */
#define rtCP_Gain_Gain_o               (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_fl
 * Referenced by: '<S1445>/Gain'
 */
#define rtCP_Gain_Gain_fl              (0.5F)

/* Expression: single(0)
 * Referenced by: '<S1405>/Constant'
 */
#define rtCP_Constant_Value_cpw        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ch
 * Referenced by: '<S1413>/LimitSource'
 */
#define rtCP_LimitSource_Value_ch      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_if3
 * Referenced by: '<S1414>/Constant'
 */
#define rtCP_Constant_Value_if3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pk
 * Referenced by: '<S1415>/Constant'
 */
#define rtCP_Constant_Value_pk         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_k
 * Referenced by: '<S1416>/LimitSource'
 */
#define rtCP_LimitSource_Value_k       (0.01F)

/* Computed Parameter: rtCP_Constant_Value_hc4
 * Referenced by: '<S1417>/Constant'
 */
#define rtCP_Constant_Value_hc4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lf
 * Referenced by: '<S1418>/Constant'
 */
#define rtCP_Constant_Value_lf         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_b12
 * Referenced by: '<S1419>/Constant'
 */
#define rtCP_Constant_Value_b12        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mo
 * Referenced by: '<S1420>/Constant'
 */
#define rtCP_Constant_Value_mo         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hut
 * Referenced by: '<S1421>/Constant'
 */
#define rtCP_Constant_Value_hut        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1407>/Constant'
 */
#define rtCP_Constant_Value_k0g        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1407>/Constant1'
 */
#define rtCP_Constant1_Value_cw        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ft
 * Referenced by: '<S1502>/LimitSource'
 */
#define rtCP_LimitSource_Value_ft      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_hv
 * Referenced by: '<S1503>/LimitSource'
 */
#define rtCP_LimitSource_Value_hv      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_cy
 * Referenced by: '<S1504>/Constant'
 */
#define rtCP_Constant_Value_cy         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_klb
 * Referenced by: '<S1505>/Constant'
 */
#define rtCP_Constant_Value_klb        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_o0
 * Referenced by: '<S1506>/LimitSource'
 */
#define rtCP_LimitSource_Value_o0      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_fy
 * Referenced by: '<S1507>/LimitSource'
 */
#define rtCP_LimitSource_Value_fy      (0.01F)

/* Computed Parameter: rtCP_Zero_Value_j
 * Referenced by: '<S1513>/Zero'
 */
#define rtCP_Zero_Value_j              (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ike
 * Referenced by: '<S1514>/Constant'
 */
#define rtCP_Constant_Value_ike        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_l2x
 * Referenced by: '<S1515>/Constant'
 */
#define rtCP_Constant_Value_l2x        (0.0F)

/* Computed Parameter: rtCP_Zero_1_Value_i
 * Referenced by: '<S1508>/Zero_1'
 */
#define rtCP_Zero_1_Value_i            (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1516>/Constant5'
 */
#define rtCP_Constant5_Value_gz        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_fjz
 * Referenced by: '<S1510>/Constant'
 */
#define rtCP_Constant_Value_fjz        (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_lo
 * Referenced by: '<S1525>/Constant'
 */
#define rtCP_Constant_Value_lo         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ow
 * Referenced by: '<S1526>/LimitSource'
 */
#define rtCP_LimitSource_Value_ow      (0.01F)

/* Expression: single(2)
 * Referenced by: '<S1512>/Constant'
 */
#define rtCP_Constant_Value_hpv        (2.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1560>/Constant'
 */
#define rtCP_Constant_Value_hqd        (0.5F)

/* Expression: single(pi/2)
 * Referenced by: '<S1399>/Constant'
 */
#define rtCP_Constant_Value_bk4        (1.57079637F)

/* Computed Parameter: rtCP_Gain1_Gain_m
 * Referenced by: '<S1407>/Gain1'
 */
#define rtCP_Gain1_Gain_m              (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_d
 * Referenced by: '<S1407>/Gain2'
 */
#define rtCP_Gain2_Gain_d              (-1.0F)

/* Computed Parameter: rtCP_ALgtRqrd_Y0_g
 * Referenced by: '<S1287>/ALgtRqrd'
 */
#define rtCP_ALgtRqrd_Y0_g             (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ja
 * Referenced by: '<S1327>/Constant'
 */
#define rtCP_Constant_Value_ja         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_bl
 * Referenced by: '<S1313>/Constant1'
 */
#define rtCP_Constant1_Value_bl        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lnb
 * Referenced by: '<S1332>/Constant'
 */
#define rtCP_Constant_Value_lnb        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_oq
 * Referenced by: '<S1330>/LimitSource'
 */
#define rtCP_LimitSource_Value_oq      (0.0001F)

/* Computed Parameter: rtCP_Constant_Value_nq
 * Referenced by: '<S1566>/Constant'
 */
#define rtCP_Constant_Value_nq         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bl3
 * Referenced by: '<S1567>/Constant'
 */
#define rtCP_Constant_Value_bl3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_k5
 * Referenced by: '<S1568>/Constant'
 */
#define rtCP_Constant_Value_k5         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lxm
 * Referenced by: '<S1569>/Constant'
 */
#define rtCP_Constant_Value_lxm        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_e2p
 * Referenced by: '<S1329>/Gain'
 */
#define rtCP_Gain_Gain_e2p             (-1.0F)

/* Expression: single(0.001)
 * Referenced by: '<S1338>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_c    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_p
 * Referenced by: '<S1338>/Saturation'
 */
#define rtCP_Saturation_UpperSat_p     (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_o
 * Referenced by: '<S1338>/Saturation'
 */
#define rtCP_Saturation_LowerSat_o     (0.0F)

/* Computed Parameter: rtCP_Merge_1_InitialOutput_k
 * Referenced by: '<S1315>/Merge'
 */
#define rtCP_Merge_1_InitialOutput_k   (0.0F)

/* Computed Parameter: rtCP_Merge_2_InitialOutput_k
 * Referenced by: '<S1315>/Merge'
 */
#define rtCP_Merge_2_InitialOutput_k   (0.0F)

/* Computed Parameter: rtCP_Merge_3_InitialOutput_k
 * Referenced by: '<S1315>/Merge'
 */
#define rtCP_Merge_3_InitialOutput_k   (0.0F)

/* Computed Parameter: rtCP_Merge_4_InitialOutput_k
 * Referenced by: '<S1315>/Merge'
 */
#define rtCP_Merge_4_InitialOutput_k   (0.0F)

/* Computed Parameter: rtCP_Merge_5_InitialOutput_k
 * Referenced by: '<S1315>/Merge'
 */
#define rtCP_Merge_5_InitialOutput_k   (0.0F)

/* Computed Parameter: rtCP_Merge_6_InitialOutput_k
 * Referenced by: '<S1315>/Merge'
 */
#define rtCP_Merge_6_InitialOutput_k   (0.0F)

/* Expression: LTAPSampleTime
 * Referenced by: '<S1685>/SampleTime'
 */
#define rtCP_SampleTime_Value          (0.05F)

/* Expression: single(0)
 * Referenced by: '<S1685>/Constant'
 */
#define rtCP_Constant_Value_i5         (0.0F)

/* Expression: LTAPSampleTime
 * Referenced by: '<S1689>/SampleTime'
 */
#define rtCP_SampleTime_Value_n        (0.05F)

/* Expression: single(1)
 * Referenced by: '<S1700>/Constant1'
 */
#define rtCP_Constant1_Value_pd        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S1700>/Constant2'
 */
#define rtCP_Constant2_Value_f         (1.0F)

/* Expression: single(0)
 * Referenced by: '<S1901>/Constant'
 */
#define rtCP_Constant_Value_j22        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ea
 * Referenced by: '<S1909>/LimitSource'
 */
#define rtCP_LimitSource_Value_ea      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ijg
 * Referenced by: '<S1910>/Constant'
 */
#define rtCP_Constant_Value_ijg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_c4f
 * Referenced by: '<S1911>/Constant'
 */
#define rtCP_Constant_Value_c4f        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_fp
 * Referenced by: '<S1912>/LimitSource'
 */
#define rtCP_LimitSource_Value_fp      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_oxm
 * Referenced by: '<S1913>/Constant'
 */
#define rtCP_Constant_Value_oxm        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_af
 * Referenced by: '<S1914>/Constant'
 */
#define rtCP_Constant_Value_af         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_a1
 * Referenced by: '<S1915>/Constant'
 */
#define rtCP_Constant_Value_a1         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dy5
 * Referenced by: '<S1916>/Constant'
 */
#define rtCP_Constant_Value_dy5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_c5i
 * Referenced by: '<S1917>/Constant'
 */
#define rtCP_Constant_Value_c5i        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1903>/Constant'
 */
#define rtCP_Constant_Value_ap0        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1903>/Constant1'
 */
#define rtCP_Constant1_Value_piw       (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_m
 * Referenced by: '<S1998>/LimitSource'
 */
#define rtCP_LimitSource_Value_m       (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_j
 * Referenced by: '<S1999>/LimitSource'
 */
#define rtCP_LimitSource_Value_j       (0.01F)

/* Computed Parameter: rtCP_Constant_Value_d2g
 * Referenced by: '<S2000>/Constant'
 */
#define rtCP_Constant_Value_d2g        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ii
 * Referenced by: '<S2001>/Constant'
 */
#define rtCP_Constant_Value_ii         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_js
 * Referenced by: '<S2002>/LimitSource'
 */
#define rtCP_LimitSource_Value_js      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_p
 * Referenced by: '<S2003>/LimitSource'
 */
#define rtCP_LimitSource_Value_p       (0.01F)

/* Computed Parameter: rtCP_Zero_Value_i
 * Referenced by: '<S2009>/Zero'
 */
#define rtCP_Zero_Value_i              (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nxg
 * Referenced by: '<S2010>/Constant'
 */
#define rtCP_Constant_Value_nxg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fz
 * Referenced by: '<S2011>/Constant'
 */
#define rtCP_Constant_Value_fz         (0.0F)

/* Computed Parameter: rtCP_Zero_1_Value_f
 * Referenced by: '<S2004>/Zero_1'
 */
#define rtCP_Zero_1_Value_f            (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2012>/Constant5'
 */
#define rtCP_Constant5_Value_pb        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_aof
 * Referenced by: '<S2006>/Constant'
 */
#define rtCP_Constant_Value_aof        (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_gc3
 * Referenced by: '<S2021>/Constant'
 */
#define rtCP_Constant_Value_gc3        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_fb
 * Referenced by: '<S2022>/LimitSource'
 */
#define rtCP_LimitSource_Value_fb      (0.01F)

/* Expression: single(2)
 * Referenced by: '<S2008>/Constant'
 */
#define rtCP_Constant_Value_iv         (2.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2056>/Constant'
 */
#define rtCP_Constant_Value_kqm        (0.5F)

/* Expression: single(pi/2)
 * Referenced by: '<S1895>/Constant'
 */
#define rtCP_Constant_Value_fjzo       (1.57079637F)

/* Computed Parameter: rtCP_Gain1_Gain_i
 * Referenced by: '<S1903>/Gain1'
 */
#define rtCP_Gain1_Gain_i              (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_ee
 * Referenced by: '<S1903>/Gain2'
 */
#define rtCP_Gain2_Gain_ee             (-1.0F)

/* Computed Parameter: rtCP_ALgtRqrd_Y0_f
 * Referenced by: '<S1805>/ALgtRqrd'
 */
#define rtCP_ALgtRqrd_Y0_f             (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ol
 * Referenced by: '<S1823>/Constant'
 */
#define rtCP_Constant_Value_ol         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ll
 * Referenced by: '<S1809>/Constant1'
 */
#define rtCP_Constant1_Value_ll        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1824>/Constant'
 */
#define rtCP_Constant_Value_l2b        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_cng
 * Referenced by: '<S1828>/Constant'
 */
#define rtCP_Constant_Value_cng        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_gy
 * Referenced by: '<S1826>/LimitSource'
 */
#define rtCP_LimitSource_Value_gy      (0.0001F)

/* Computed Parameter: rtCP_Constant_Value_dr
 * Referenced by: '<S2062>/Constant'
 */
#define rtCP_Constant_Value_dr         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kh
 * Referenced by: '<S2063>/Constant'
 */
#define rtCP_Constant_Value_kh         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pa
 * Referenced by: '<S2064>/Constant'
 */
#define rtCP_Constant_Value_pa         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aww
 * Referenced by: '<S2065>/Constant'
 */
#define rtCP_Constant_Value_aww        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_cr
 * Referenced by: '<S1825>/Gain'
 */
#define rtCP_Gain_Gain_cr              (-1.0F)

/* Expression: single(0.001)
 * Referenced by: '<S1834>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_b    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_h
 * Referenced by: '<S1834>/Saturation'
 */
#define rtCP_Saturation_UpperSat_h     (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_d
 * Referenced by: '<S1834>/Saturation'
 */
#define rtCP_Saturation_LowerSat_d     (0.0F)

/* Computed Parameter: rtCP_Merge_1_InitialOutput_c
 * Referenced by: '<S1811>/Merge'
 */
#define rtCP_Merge_1_InitialOutput_c   (0.0F)

/* Computed Parameter: rtCP_Merge_2_InitialOutput_c
 * Referenced by: '<S1811>/Merge'
 */
#define rtCP_Merge_2_InitialOutput_c   (0.0F)

/* Computed Parameter: rtCP_Merge_3_InitialOutput_c
 * Referenced by: '<S1811>/Merge'
 */
#define rtCP_Merge_3_InitialOutput_c   (0.0F)

/* Computed Parameter: rtCP_Merge_4_InitialOutput_c
 * Referenced by: '<S1811>/Merge'
 */
#define rtCP_Merge_4_InitialOutput_c   (0.0F)

/* Computed Parameter: rtCP_Merge_5_InitialOutput_c
 * Referenced by: '<S1811>/Merge'
 */
#define rtCP_Merge_5_InitialOutput_c   (0.0F)

/* Computed Parameter: rtCP_Merge_6_InitialOutput_c
 * Referenced by: '<S1811>/Merge'
 */
#define rtCP_Merge_6_InitialOutput_c   (0.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S2119>/Constant'
 */
#define rtCP_Constant_Value_ky3        (1.57079637F)

/* Computed Parameter: rtCP_Constant_Value_fh4
 * Referenced by: '<S2122>/Constant'
 */
#define rtCP_Constant_Value_fh4        (0.0F)

/* Expression: single(-1)
 * Referenced by: '<S2119>/Gain'
 */
#define rtCP_Gain_Gain_oo              (-1.0F)

/* Expression: single(pi)
 * Referenced by: '<S2121>/Constant'
 */
#define rtCP_Constant_Value_exi        (3.14159274F)

/* Computed Parameter: rtCP_Constant_Value_guj0
 * Referenced by: '<S2128>/Constant'
 */
#define rtCP_Constant_Value_guj0       (0.0F)

/* Expression: single(pi)
 * Referenced by: '<S2120>/Constant'
 */
#define rtCP_Constant_Value_dt         (3.14159274F)

/* Computed Parameter: rtCP_Constant_Value_gi
 * Referenced by: '<S2125>/Constant'
 */
#define rtCP_Constant_Value_gi         (0.0F)

/* Computed Parameter: rtCP_Zero_1_Value_kb
 * Referenced by: '<S2415>/Zero_1'
 */
#define rtCP_Zero_1_Value_kb           (0.0F)

/* Computed Parameter: rtCP_Zero_2_Value
 * Referenced by: '<S2415>/Zero_2'
 */
#define rtCP_Zero_2_Value              (0.0F)

/* Computed Parameter: rtCP_Zero_3_Value
 * Referenced by: '<S2415>/Zero_3'
 */
#define rtCP_Zero_3_Value              (0.0F)

/* Computed Parameter: rtCP_Zero_5_Value
 * Referenced by: '<S2415>/Zero_5'
 */
#define rtCP_Zero_5_Value              (0.0F)

/* Computed Parameter: rtCP_Zero_6_Value
 * Referenced by: '<S2415>/Zero_6'
 */
#define rtCP_Zero_6_Value              (0.0F)

/* Computed Parameter: rtCP_Zero_4_Value
 * Referenced by: '<S2415>/Zero_4'
 */
#define rtCP_Zero_4_Value              (0.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S2425>/Constant1'
 */
#define rtCP_Constant1_Value_bu        (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S2425>/Constant2'
 */
#define rtCP_Constant2_Value_dg        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2433>/Constant5'
 */
#define rtCP_Constant5_Value_bf        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_d2c
 * Referenced by: '<S2424>/Constant'
 */
#define rtCP_Constant_Value_d2c        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_piz
 * Referenced by: '<S2427>/Constant1'
 */
#define rtCP_Constant1_Value_piz       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2437>/Constant'
 */
#define rtCP_Constant_Value_ouz        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_gq
 * Referenced by: '<S2441>/Constant'
 */
#define rtCP_Constant_Value_gq         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_gq
 * Referenced by: '<S2439>/LimitSource'
 */
#define rtCP_LimitSource_Value_gq      (0.0001F)

/* Expression: single(pi/2)
 * Referenced by: '<S2447>/Constant1'
 */
#define rtCP_Constant1_Value_kw        (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S2447>/Constant2'
 */
#define rtCP_Constant2_Value_fj        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2455>/Constant5'
 */
#define rtCP_Constant5_Value_kk        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_fju
 * Referenced by: '<S2446>/Constant'
 */
#define rtCP_Constant_Value_fju        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_p2
 * Referenced by: '<S2449>/Constant1'
 */
#define rtCP_Constant1_Value_p2        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2459>/Constant'
 */
#define rtCP_Constant_Value_cqn        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_jdv
 * Referenced by: '<S2463>/Constant'
 */
#define rtCP_Constant_Value_jdv        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_n
 * Referenced by: '<S2461>/LimitSource'
 */
#define rtCP_LimitSource_Value_n       (0.0001F)

/* Expression: single(pi/2)
 * Referenced by: '<S2471>/Constant1'
 */
#define rtCP_Constant1_Value_cgr       (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S2471>/Constant2'
 */
#define rtCP_Constant2_Value_eq        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2479>/Constant5'
 */
#define rtCP_Constant5_Value_pqa       (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_ckt
 * Referenced by: '<S2470>/Constant'
 */
#define rtCP_Constant_Value_ckt        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_jc
 * Referenced by: '<S2473>/Constant1'
 */
#define rtCP_Constant1_Value_jc        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2483>/Constant'
 */
#define rtCP_Constant_Value_cy2        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_owj
 * Referenced by: '<S2487>/Constant'
 */
#define rtCP_Constant_Value_owj        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_cy
 * Referenced by: '<S2485>/LimitSource'
 */
#define rtCP_LimitSource_Value_cy      (0.0001F)

/* Expression: single(pi/2)
 * Referenced by: '<S2495>/Constant1'
 */
#define rtCP_Constant1_Value_c2        (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S2495>/Constant2'
 */
#define rtCP_Constant2_Value_l3        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2503>/Constant5'
 */
#define rtCP_Constant5_Value_gg        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_cs
 * Referenced by: '<S2494>/Constant'
 */
#define rtCP_Constant_Value_cs         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ij
 * Referenced by: '<S2497>/Constant1'
 */
#define rtCP_Constant1_Value_ij        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2507>/Constant'
 */
#define rtCP_Constant_Value_fr         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_dsu
 * Referenced by: '<S2511>/Constant'
 */
#define rtCP_Constant_Value_dsu        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ov
 * Referenced by: '<S2509>/LimitSource'
 */
#define rtCP_LimitSource_Value_ov      (0.0001F)

/* Expression: single(pi/2)
 * Referenced by: '<S2516>/Constant1'
 */
#define rtCP_Constant1_Value_hl        (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S2516>/Constant2'
 */
#define rtCP_Constant2_Value_du        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2524>/Constant5'
 */
#define rtCP_Constant5_Value_m4        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_bvj
 * Referenced by: '<S2515>/Constant'
 */
#define rtCP_Constant_Value_bvj        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_je
 * Referenced by: '<S2518>/Constant1'
 */
#define rtCP_Constant1_Value_je        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2528>/Constant'
 */
#define rtCP_Constant_Value_jdm        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ayg
 * Referenced by: '<S2532>/Constant'
 */
#define rtCP_Constant_Value_ayg        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_hc
 * Referenced by: '<S2530>/LimitSource'
 */
#define rtCP_LimitSource_Value_hc      (0.0001F)

/* Computed Parameter: rtCP_Gain_Gain_pe
 * Referenced by: '<S2438>/Gain'
 */
#define rtCP_Gain_Gain_pe              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_lx
 * Referenced by: '<S2460>/Gain'
 */
#define rtCP_Gain_Gain_lx              (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_j
 * Referenced by: '<S2466>/Gain_1'
 */
#define rtCP_Gain_1_Gain_j             (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain
 * Referenced by: '<S2466>/Gain_2'
 */
#define rtCP_Gain_2_Gain               (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_l2
 * Referenced by: '<S2484>/Gain'
 */
#define rtCP_Gain_Gain_l2              (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_d
 * Referenced by: '<S2490>/Gain_1'
 */
#define rtCP_Gain_1_Gain_d             (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_a
 * Referenced by: '<S2490>/Gain_2'
 */
#define rtCP_Gain_2_Gain_a             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_jf
 * Referenced by: '<S2508>/Gain'
 */
#define rtCP_Gain_Gain_jf              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_ph
 * Referenced by: '<S2529>/Gain'
 */
#define rtCP_Gain_Gain_ph              (-1.0F)

/* Computed Parameter: rtCP_Constant1_Value_dc
 * Referenced by: '<S2540>/Constant1'
 */
#define rtCP_Constant1_Value_dc        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2547>/Constant'
 */
#define rtCP_Constant_Value_iss        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_p5w
 * Referenced by: '<S2551>/Constant'
 */
#define rtCP_Constant_Value_p5w        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_d
 * Referenced by: '<S2549>/LimitSource'
 */
#define rtCP_LimitSource_Value_d       (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_jcn
 * Referenced by: '<S2541>/Constant1'
 */
#define rtCP_Constant1_Value_jcn       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2554>/Constant'
 */
#define rtCP_Constant_Value_mh         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_mhd
 * Referenced by: '<S2558>/Constant'
 */
#define rtCP_Constant_Value_mhd        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_jh
 * Referenced by: '<S2556>/LimitSource'
 */
#define rtCP_LimitSource_Value_jh      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_l3
 * Referenced by: '<S2561>/Constant1'
 */
#define rtCP_Constant1_Value_l3        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2568>/Constant'
 */
#define rtCP_Constant_Value_exw        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_pnc
 * Referenced by: '<S2572>/Constant'
 */
#define rtCP_Constant_Value_pnc        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_el
 * Referenced by: '<S2570>/LimitSource'
 */
#define rtCP_LimitSource_Value_el      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_pis
 * Referenced by: '<S2562>/Constant1'
 */
#define rtCP_Constant1_Value_pis       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2575>/Constant'
 */
#define rtCP_Constant_Value_a3i        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_pe
 * Referenced by: '<S2579>/Constant'
 */
#define rtCP_Constant_Value_pe         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_mx
 * Referenced by: '<S2577>/LimitSource'
 */
#define rtCP_LimitSource_Value_mx      (0.0001F)

/* Expression: single(0.5)
 * Referenced by: '<S2584>/Constant'
 */
#define rtCP_Constant_Value_h4h        (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S2585>/Constant'
 */
#define rtCP_Constant_Value_jn         (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S2600>/Constant'
 */
#define rtCP_Constant_Value_nl         (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S2601>/Constant'
 */
#define rtCP_Constant_Value_ekk        (0.5F)

/* Computed Parameter: rtCP_Constant1_Value_o1
 * Referenced by: '<S2614>/Constant1'
 */
#define rtCP_Constant1_Value_o1        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2618>/Constant'
 */
#define rtCP_Constant_Value_dle        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ltj
 * Referenced by: '<S2622>/Constant'
 */
#define rtCP_Constant_Value_ltj        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_gp
 * Referenced by: '<S2620>/LimitSource'
 */
#define rtCP_LimitSource_Value_gp      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_pf
 * Referenced by: '<S2615>/Constant1'
 */
#define rtCP_Constant1_Value_pf        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S2625>/Constant'
 */
#define rtCP_Constant_Value_m0z        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_iy
 * Referenced by: '<S2629>/Constant'
 */
#define rtCP_Constant_Value_iy         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_i
 * Referenced by: '<S2627>/LimitSource'
 */
#define rtCP_LimitSource_Value_i       (0.0001F)

/* Computed Parameter: rtCP_Gain_Gain_gp
 * Referenced by: '<S2535>/Gain'
 */
#define rtCP_Gain_Gain_gp              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_g1
 * Referenced by: '<S2535>/Gain1'
 */
#define rtCP_Gain1_Gain_g1             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_c5
 * Referenced by: '<S2548>/Gain'
 */
#define rtCP_Gain_Gain_c5              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_n2
 * Referenced by: '<S2555>/Gain'
 */
#define rtCP_Gain_Gain_n2              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_mu
 * Referenced by: '<S2536>/Gain'
 */
#define rtCP_Gain_Gain_mu              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ja
 * Referenced by: '<S2536>/Gain1'
 */
#define rtCP_Gain1_Gain_ja             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_csl
 * Referenced by: '<S2569>/Gain'
 */
#define rtCP_Gain_Gain_csl             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_ay
 * Referenced by: '<S2576>/Gain'
 */
#define rtCP_Gain_Gain_ay              (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_de
 * Referenced by: '<S2582>/Gain_1'
 */
#define rtCP_Gain_1_Gain_de            (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_o
 * Referenced by: '<S2582>/Gain_2'
 */
#define rtCP_Gain_2_Gain_o             (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_k
 * Referenced by: '<S2598>/Gain_1'
 */
#define rtCP_Gain_1_Gain_k             (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_l
 * Referenced by: '<S2598>/Gain_2'
 */
#define rtCP_Gain_2_Gain_l             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_bn
 * Referenced by: '<S2619>/Gain'
 */
#define rtCP_Gain_Gain_bn              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_pg
 * Referenced by: '<S2626>/Gain'
 */
#define rtCP_Gain_Gain_pg              (-1.0F)

/* Computed Parameter: rtCP_Constant1_Value_g0
 * Referenced by: '<S3098>/Constant1'
 */
#define rtCP_Constant1_Value_g0        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3105>/Constant'
 */
#define rtCP_Constant_Value_kd3        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ps
 * Referenced by: '<S3109>/Constant'
 */
#define rtCP_Constant_Value_ps         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ok
 * Referenced by: '<S3107>/LimitSource'
 */
#define rtCP_LimitSource_Value_ok      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_kk
 * Referenced by: '<S3099>/Constant1'
 */
#define rtCP_Constant1_Value_kk        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3112>/Constant'
 */
#define rtCP_Constant_Value_d25        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_lxmb
 * Referenced by: '<S3116>/Constant'
 */
#define rtCP_Constant_Value_lxmb       (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_jj
 * Referenced by: '<S3114>/LimitSource'
 */
#define rtCP_LimitSource_Value_jj      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_et
 * Referenced by: '<S3119>/Constant1'
 */
#define rtCP_Constant1_Value_et        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3126>/Constant'
 */
#define rtCP_Constant_Value_bai        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_lxj
 * Referenced by: '<S3130>/Constant'
 */
#define rtCP_Constant_Value_lxj        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_kz
 * Referenced by: '<S3128>/LimitSource'
 */
#define rtCP_LimitSource_Value_kz      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_jt
 * Referenced by: '<S3120>/Constant1'
 */
#define rtCP_Constant1_Value_jt        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3133>/Constant'
 */
#define rtCP_Constant_Value_er         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_pnj
 * Referenced by: '<S3137>/Constant'
 */
#define rtCP_Constant_Value_pnj        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ftl
 * Referenced by: '<S3135>/LimitSource'
 */
#define rtCP_LimitSource_Value_ftl     (0.0001F)

/* Expression: single(0.5)
 * Referenced by: '<S3142>/Constant'
 */
#define rtCP_Constant_Value_cra        (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S3143>/Constant'
 */
#define rtCP_Constant_Value_af2        (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S3158>/Constant'
 */
#define rtCP_Constant_Value_g0         (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S3159>/Constant'
 */
#define rtCP_Constant_Value_b2         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_h1l
 * Referenced by: '<S3172>/Constant'
 */
#define rtCP_Constant_Value_h1l        (1.0F)

/* Computed Parameter: rtCP_Constant1_Value_knt
 * Referenced by: '<S3173>/Constant1'
 */
#define rtCP_Constant1_Value_knt       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3178>/Constant'
 */
#define rtCP_Constant_Value_gn1        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_crc
 * Referenced by: '<S3182>/Constant'
 */
#define rtCP_Constant_Value_crc        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_mn
 * Referenced by: '<S3180>/LimitSource'
 */
#define rtCP_LimitSource_Value_mn      (0.0001F)

/* Computed Parameter: rtCP_Constant1_Value_pgp
 * Referenced by: '<S3174>/Constant1'
 */
#define rtCP_Constant1_Value_pgp       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S3185>/Constant'
 */
#define rtCP_Constant_Value_dvm        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_prg
 * Referenced by: '<S3189>/Constant'
 */
#define rtCP_Constant_Value_prg        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_h5
 * Referenced by: '<S3187>/LimitSource'
 */
#define rtCP_LimitSource_Value_h5      (0.0001F)

/* Computed Parameter: rtCP_Gain_Gain_dj
 * Referenced by: '<S3093>/Gain'
 */
#define rtCP_Gain_Gain_dj              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ch
 * Referenced by: '<S3093>/Gain1'
 */
#define rtCP_Gain1_Gain_ch             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_p5
 * Referenced by: '<S3106>/Gain'
 */
#define rtCP_Gain_Gain_p5              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_fd
 * Referenced by: '<S3113>/Gain'
 */
#define rtCP_Gain_Gain_fd              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_es
 * Referenced by: '<S3094>/Gain'
 */
#define rtCP_Gain_Gain_es              (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_f5
 * Referenced by: '<S3094>/Gain1'
 */
#define rtCP_Gain1_Gain_f5             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_mo
 * Referenced by: '<S3127>/Gain'
 */
#define rtCP_Gain_Gain_mo              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_pv
 * Referenced by: '<S3134>/Gain'
 */
#define rtCP_Gain_Gain_pv              (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_pz
 * Referenced by: '<S3140>/Gain_1'
 */
#define rtCP_Gain_1_Gain_pz            (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_j
 * Referenced by: '<S3140>/Gain_2'
 */
#define rtCP_Gain_2_Gain_j             (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_h
 * Referenced by: '<S3156>/Gain_1'
 */
#define rtCP_Gain_1_Gain_h             (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_i
 * Referenced by: '<S3156>/Gain_2'
 */
#define rtCP_Gain_2_Gain_i             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_hp
 * Referenced by: '<S3179>/Gain'
 */
#define rtCP_Gain_Gain_hp              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_iz
 * Referenced by: '<S3186>/Gain'
 */
#define rtCP_Gain_Gain_iz              (-1.0F)

/* Expression: single(pi)
 * Referenced by: '<S3414>/Constant_1'
 */
#define rtCP_Constant_1_Value_b        (3.14159274F)

/* Expression: single(pi)
 * Referenced by: '<S3414>/Constant_2'
 */
#define rtCP_Constant_2_Value_ou       (3.14159274F)

/* Computed Parameter: rtCP_Gain_1_Gain_fm
 * Referenced by: '<S3414>/Gain_1'
 */
#define rtCP_Gain_1_Gain_fm            (-1.0F)

/* Computed Parameter: rtCP_Constant_Value_cnu
 * Referenced by: '<S3593>/Constant'
 */
#define rtCP_Constant_Value_cnu        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_p5e
 * Referenced by: '<S3594>/Constant'
 */
#define rtCP_Constant_Value_p5e        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3595>/Constant5'
 */
#define rtCP_Constant5_Value_j1        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_g5
 * Referenced by: '<S3596>/LimitSource'
 */
#define rtCP_LimitSource_Value_g5      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_dmv
 * Referenced by: '<S3600>/Constant'
 */
#define rtCP_Constant_Value_dmv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_iyy
 * Referenced by: '<S3601>/Constant'
 */
#define rtCP_Constant_Value_iyy        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3602>/Constant5'
 */
#define rtCP_Constant5_Value_bb        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_al
 * Referenced by: '<S3603>/LimitSource'
 */
#define rtCP_LimitSource_Value_al      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_l3
 * Referenced by: '<S3607>/Constant'
 */
#define rtCP_Constant_Value_l3         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pue
 * Referenced by: '<S3610>/Constant'
 */
#define rtCP_Constant_Value_pue        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_g4
 * Referenced by: '<S3590>/Gain'
 */
#define rtCP_Gain_Gain_g4              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_i5g
 * Referenced by: '<S3591>/Gain'
 */
#define rtCP_Gain_Gain_i5g             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_mo1
 * Referenced by: '<S3592>/Gain'
 */
#define rtCP_Gain_Gain_mo1             (0.5F)

/* Computed Parameter: rtCP_Constant_Value_by
 * Referenced by: '<S3614>/Constant'
 */
#define rtCP_Constant_Value_by         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gj
 * Referenced by: '<S3615>/Constant'
 */
#define rtCP_Constant_Value_gj         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3616>/Constant5'
 */
#define rtCP_Constant5_Value_bs        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_cf
 * Referenced by: '<S3617>/LimitSource'
 */
#define rtCP_LimitSource_Value_cf      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ppc
 * Referenced by: '<S3621>/Constant'
 */
#define rtCP_Constant_Value_ppc        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cpo
 * Referenced by: '<S3622>/Constant'
 */
#define rtCP_Constant_Value_cpo        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3623>/Constant5'
 */
#define rtCP_Constant5_Value_gt        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_nq
 * Referenced by: '<S3624>/LimitSource'
 */
#define rtCP_LimitSource_Value_nq      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_j4
 * Referenced by: '<S3628>/Constant'
 */
#define rtCP_Constant_Value_j4         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_exwb
 * Referenced by: '<S3631>/Constant'
 */
#define rtCP_Constant_Value_exwb       (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_ic
 * Referenced by: '<S3611>/Gain'
 */
#define rtCP_Gain_Gain_ic              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_dq
 * Referenced by: '<S3612>/Gain'
 */
#define rtCP_Gain_Gain_dq              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_hsf
 * Referenced by: '<S3613>/Gain'
 */
#define rtCP_Gain_Gain_hsf             (0.5F)

/* Computed Parameter: rtCP_Constant_Value_lwo
 * Referenced by: '<S3635>/Constant'
 */
#define rtCP_Constant_Value_lwo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mgm
 * Referenced by: '<S3636>/Constant'
 */
#define rtCP_Constant_Value_mgm        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3637>/Constant5'
 */
#define rtCP_Constant5_Value_at        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_mm
 * Referenced by: '<S3638>/LimitSource'
 */
#define rtCP_LimitSource_Value_mm      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ozl
 * Referenced by: '<S3642>/Constant'
 */
#define rtCP_Constant_Value_ozl        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ft
 * Referenced by: '<S3643>/Constant'
 */
#define rtCP_Constant_Value_ft         (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3644>/Constant5'
 */
#define rtCP_Constant5_Value_pk        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_dc
 * Referenced by: '<S3645>/LimitSource'
 */
#define rtCP_LimitSource_Value_dc      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ld5
 * Referenced by: '<S3649>/Constant'
 */
#define rtCP_Constant_Value_ld5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bs2
 * Referenced by: '<S3652>/Constant'
 */
#define rtCP_Constant_Value_bs2        (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_d0n
 * Referenced by: '<S3632>/Gain'
 */
#define rtCP_Gain_Gain_d0n             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_er
 * Referenced by: '<S3633>/Gain'
 */
#define rtCP_Gain_Gain_er              (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_fh
 * Referenced by: '<S3634>/Gain'
 */
#define rtCP_Gain_Gain_fh              (0.5F)

/* Computed Parameter: rtCP_Constant_Value_juy
 * Referenced by: '<S5884>/Constant'
 */
#define rtCP_Constant_Value_juy        (1.0F)

/* Expression: const
 * Referenced by: '<S5885>/Constant'
 */
#define rtCP_Constant_Value_jv         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5878>/Constant1'
 */
#define rtCP_Constant1_Value_my        (0.0F)

/* Expression: single(0.1)
 * Referenced by: '<S5878>/Constant2'
 */
#define rtCP_Constant2_Value_o         (0.1F)

/* Expression: VehSelfMinSpdInDrvrStEstimr
 * Referenced by: '<S5878>/Constant7'
 */
#define rtCP_Constant7_Value_op        (0.2F)

/* Expression: single(0)
 * Referenced by: '<S5878>/Constant8'
 */
#define rtCP_Constant8_Value_g         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5888>/Constant'
 */
#define rtCP_Constant_Value_hxt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ars
 * Referenced by: '<S5892>/Constant'
 */
#define rtCP_Constant_Value_ars        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_bg
 * Referenced by: '<S5880>/Constant1'
 */
#define rtCP_Constant1_Value_bg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dk
 * Referenced by: '<S5900>/Constant'
 */
#define rtCP_Constant_Value_dk         (0.0F)

/* Expression: single(3)
 * Referenced by: '<S5897>/Constant'
 */
#define rtCP_Constant_Value_o3a        (3.0F)

/* Expression: -single(0.5)
 * Referenced by: '<S5897>/Constant1'
 */
#define rtCP_Constant1_Value_ai        (-0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S5897>/Constant4'
 */
#define rtCP_Constant4_Value_c5        (0.5F)

/* Expression: single(2)
 * Referenced by: '<S5904>/Constant'
 */
#define rtCP_Constant_Value_akq        (2.0F)

/* Expression: single(3)
 * Referenced by: '<S5904>/Constant1'
 */
#define rtCP_Constant1_Value_gl        (3.0F)

/* Expression: single(6)
 * Referenced by: '<S5904>/Constant2'
 */
#define rtCP_Constant2_Value_je        (6.0F)

/* Expression: single(2)
 * Referenced by: '<S5904>/Constant3'
 */
#define rtCP_Constant3_Value_f         (2.0F)

/* Expression: single(0)
 * Referenced by: '<S5896>/Constant'
 */
#define rtCP_Constant_Value_ctf        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_dz
 * Referenced by: '<S5915>/Constant1'
 */
#define rtCP_Constant1_Value_dz        (0.0F)

/* Computed Parameter: rtCP_Constant5_Value_mz
 * Referenced by: '<S5915>/Constant5'
 */
#define rtCP_Constant5_Value_mz        (0.0F)

/* Computed Parameter: rtCP_Constant6_Value_l
 * Referenced by: '<S5915>/Constant6'
 */
#define rtCP_Constant6_Value_l         (0.0F)

/* Computed Parameter: rtCP_Constant7_Value_a3
 * Referenced by: '<S5915>/Constant7'
 */
#define rtCP_Constant7_Value_a3        (0.0F)

/* Computed Parameter: rtCP_Constant9_Value_m
 * Referenced by: '<S5915>/Constant9'
 */
#define rtCP_Constant9_Value_m         (0.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_ii
 * Referenced by: '<S5878>/Saturation'
 */
#define rtCP_Saturation_UpperSat_ii    (4.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_oj
 * Referenced by: '<S5878>/Saturation'
 */
#define rtCP_Saturation_LowerSat_oj    (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S5878>/Gain1'
 */
#define rtCP_Gain1_Gain_cl             (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S5878>/Gain2'
 */
#define rtCP_Gain2_Gain_hl             (0.5F)

/* Expression: single(1/3)
 * Referenced by: '<S5895>/Gain9'
 */
#define rtCP_Gain9_Gain                (0.333333343F)

/* Computed Parameter: rtCP_Gain7_Gain
 * Referenced by: '<S5895>/Gain7'
 */
#define rtCP_Gain7_Gain                (2.0F)

/* Expression: single(1/6)
 * Referenced by: '<S5895>/Gain5'
 */
#define rtCP_Gain5_Gain                (0.166666672F)

/* Computed Parameter: rtCP_Gain9_Gain_p
 * Referenced by: '<S5890>/Gain9'
 */
#define rtCP_Gain9_Gain_p              (3.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput
 * Referenced by: '<S5899>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput
 * Referenced by: '<S5899>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput
 * Referenced by: '<S5899>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput
 * Referenced by: '<S5899>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput   (0.0F)

/* Expression: single(1/3)
 * Referenced by: '<S5895>/Gain8'
 */
#define rtCP_Gain8_Gain                (0.333333343F)

/* Computed Parameter: rtCP_Gain4_Gain
 * Referenced by: '<S5895>/Gain4'
 */
#define rtCP_Gain4_Gain                (2.0F)

/* Expression: single(1/6)
 * Referenced by: '<S5895>/Gain2'
 */
#define rtCP_Gain2_Gain_ls             (0.166666672F)

/* Computed Parameter: rtCP_Gain4_Gain_m
 * Referenced by: '<S5890>/Gain4'
 */
#define rtCP_Gain4_Gain_m              (3.0F)

/* Computed Parameter: rtCP_Gain8_Gain_e
 * Referenced by: '<S5890>/Gain8'
 */
#define rtCP_Gain8_Gain_e              (3.0F)

/* Computed Parameter: rtCP_Gain_Gain_la
 * Referenced by: '<S5890>/Gain'
 */
#define rtCP_Gain_Gain_la              (3.0F)

/* Expression: LoPosValInDrvrStEstimr
 * Referenced by: '<S5879>/Saturation'
 */
#define rtCP_Saturation_LowerSat_j     (1.0E-8F)

/* Expression: single(0.1)
 * Referenced by: '<S5879>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat      (0.1F)

/* Expression: single(-0.1)
 * Referenced by: '<S5879>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_a    (-0.1F)

/* Computed Parameter: rtCP_Constant_Value_ow0
 * Referenced by: '<S5821>/Constant'
 */
#define rtCP_Constant_Value_ow0        (1.0F)

/* Expression: const
 * Referenced by: '<S5822>/Constant'
 */
#define rtCP_Constant_Value_ovr        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5815>/Constant1'
 */
#define rtCP_Constant1_Value_k0        (0.0F)

/* Expression: single(0.1)
 * Referenced by: '<S5815>/Constant2'
 */
#define rtCP_Constant2_Value_oj        (0.1F)

/* Expression: VehSelfMinSpdInDrvrStEstimr
 * Referenced by: '<S5815>/Constant7'
 */
#define rtCP_Constant7_Value_as        (0.2F)

/* Expression: single(0)
 * Referenced by: '<S5815>/Constant8'
 */
#define rtCP_Constant8_Value_f         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5825>/Constant'
 */
#define rtCP_Constant_Value_lfn        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ft3
 * Referenced by: '<S5829>/Constant'
 */
#define rtCP_Constant_Value_ft3        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_na
 * Referenced by: '<S5817>/Constant1'
 */
#define rtCP_Constant1_Value_na        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_oul
 * Referenced by: '<S5835>/Constant1'
 */
#define rtCP_Constant1_Value_oul       (0.0F)

/* Computed Parameter: rtCP_Constant5_Value_lp
 * Referenced by: '<S5835>/Constant5'
 */
#define rtCP_Constant5_Value_lp        (0.0F)

/* Computed Parameter: rtCP_Constant6_Value_m2
 * Referenced by: '<S5835>/Constant6'
 */
#define rtCP_Constant6_Value_m2        (0.0F)

/* Computed Parameter: rtCP_Constant7_Value_i
 * Referenced by: '<S5835>/Constant7'
 */
#define rtCP_Constant7_Value_i         (0.0F)

/* Computed Parameter: rtCP_Constant9_Value_a
 * Referenced by: '<S5835>/Constant9'
 */
#define rtCP_Constant9_Value_a         (0.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_en
 * Referenced by: '<S5815>/Saturation'
 */
#define rtCP_Saturation_UpperSat_en    (4.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_h2y
 * Referenced by: '<S5815>/Saturation'
 */
#define rtCP_Saturation_LowerSat_h2y   (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S5815>/Gain1'
 */
#define rtCP_Gain1_Gain_is             (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S5815>/Gain2'
 */
#define rtCP_Gain2_Gain_dn             (0.5F)

/* Expression: single(1/3)
 * Referenced by: '<S5832>/Gain9'
 */
#define rtCP_Gain9_Gain_g              (0.333333343F)

/* Computed Parameter: rtCP_Gain7_Gain_e
 * Referenced by: '<S5832>/Gain7'
 */
#define rtCP_Gain7_Gain_e              (2.0F)

/* Expression: single(1/6)
 * Referenced by: '<S5832>/Gain5'
 */
#define rtCP_Gain5_Gain_j              (0.166666672F)

/* Computed Parameter: rtCP_Gain9_Gain_gp
 * Referenced by: '<S5827>/Gain9'
 */
#define rtCP_Gain9_Gain_gp             (3.0F)

/* Computed Parameter: rtCP_Gain4_Gain_f
 * Referenced by: '<S5827>/Gain4'
 */
#define rtCP_Gain4_Gain_f              (3.0F)

/* Expression: single(1/3)
 * Referenced by: '<S5832>/Gain8'
 */
#define rtCP_Gain8_Gain_b              (0.333333343F)

/* Computed Parameter: rtCP_Gain4_Gain_k
 * Referenced by: '<S5832>/Gain4'
 */
#define rtCP_Gain4_Gain_k              (2.0F)

/* Expression: single(1/6)
 * Referenced by: '<S5832>/Gain2'
 */
#define rtCP_Gain2_Gain_m              (0.166666672F)

/* Computed Parameter: rtCP_Gain8_Gain_g
 * Referenced by: '<S5827>/Gain8'
 */
#define rtCP_Gain8_Gain_g              (3.0F)

/* Computed Parameter: rtCP_Gain_Gain_ks
 * Referenced by: '<S5827>/Gain'
 */
#define rtCP_Gain_Gain_ks              (3.0F)

/* Expression: LoPosValInDrvrStEstimr
 * Referenced by: '<S5816>/Saturation'
 */
#define rtCP_Saturation_LowerSat_np    (1.0E-8F)

/* Expression: single(0.1)
 * Referenced by: '<S5816>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_g    (0.1F)

/* Expression: single(-0.1)
 * Referenced by: '<S5816>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_cw   (-0.1F)

/* Computed Parameter: rtCP_Constant1_Value_px
 * Referenced by: '<S5945>/Constant1'
 */
#define rtCP_Constant1_Value_px        (31.0F)

/* Computed Parameter: rtCP_Constant2_Value_h
 * Referenced by: '<S5945>/Constant2'
 */
#define rtCP_Constant2_Value_h         (0.0F)

/* Expression: PerdFctCallInDrvrStEstimr
 * Referenced by: '<S5929>/Constant'
 */
#define rtCP_Constant_Value_oko        (0.02F)

/* Computed Parameter: rtCP_Constant2_Value_dt
 * Referenced by: '<S5946>/Constant2'
 */
#define rtCP_Constant2_Value_dt        (1.0F)

/* Computed Parameter: rtCP_Constant4_Value_hj
 * Referenced by: '<S5948>/Constant4'
 */
#define rtCP_Constant4_Value_hj        (1.0F)

/* Expression: AOfGrvyInDrvrStEstimr
 * Referenced by: '<S6052>/g'
 */
#define rtCP_g_Value                   (-9.8F)

/* Expression: AOfGrvyInDrvrStEstimr
 * Referenced by: '<S6053>/g'
 */
#define rtCP_g_Value_f                 (-9.8F)

/* Expression: single(0.5)
 * Referenced by: '<S775>/Constant'
 */
#define rtCP_Constant_Value_o2a        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_mte
 * Referenced by: '<S780>/Constant'
 */
#define rtCP_Constant_Value_mte        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_k2y
 * Referenced by: '<S783>/Constant'
 */
#define rtCP_Constant_Value_k2y        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S778>/Constant'
 */
#define rtCP_Constant_Value_f0         (0.5F)

/* Computed Parameter: rtCP_Constant_Value_gfr
 * Referenced by: '<S786>/Constant'
 */
#define rtCP_Constant_Value_gfr        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pik
 * Referenced by: '<S787>/Constant'
 */
#define rtCP_Constant_Value_pik        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S779>/Constant2'
 */
#define rtCP_Constant2_Value_pt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S779>/Constant3'
 */
#define rtCP_Constant3_Value_g         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dz1
 * Referenced by: '<S797>/Constant'
 */
#define rtCP_Constant_Value_dz1        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_ebt
 * Referenced by: '<S798>/Constant'
 */
#define rtCP_Constant_Value_ebt        (0.9F)

/* Computed Parameter: rtCP_Constant_Value_az
 * Referenced by: '<S799>/Constant'
 */
#define rtCP_Constant_Value_az         (0.3F)

/* Expression: const
 * Referenced by: '<S802>/Constant'
 */
#define rtCP_Constant_Value_ikq        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_nz
 * Referenced by: '<S809>/Constant'
 */
#define rtCP_Constant_Value_nz         (30.0F)

/* Expression: single(0)
 * Referenced by: '<S812>/Constant3'
 */
#define rtCP_Constant3_Value_a         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_d5f
 * Referenced by: '<S815>/Constant'
 */
#define rtCP_Constant_Value_d5f        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_jyi
 * Referenced by: '<S816>/Constant'
 */
#define rtCP_Constant_Value_jyi        (20.0F)

/* Computed Parameter: rtCP_Constant_Value_ezn
 * Referenced by: '<S817>/Constant'
 */
#define rtCP_Constant_Value_ezn        (5.0F)

/* Computed Parameter: rtCP_Constant_Value_o2l
 * Referenced by: '<S818>/Constant'
 */
#define rtCP_Constant_Value_o2l        (5.0F)

/* Expression: const
 * Referenced by: '<S842>/Constant'
 */
#define rtCP_Constant_Value_ij1        (1.0F)

/* Expression: single(0)
 * Referenced by: '<S843>/Constant3'
 */
#define rtCP_Constant3_Value_kg        (0.0F)

/* Expression: const
 * Referenced by: '<S847>/Constant'
 */
#define rtCP_Constant_Value_mpa        (1.5F)

/* Computed Parameter: rtCP_Constant_Value_kwq
 * Referenced by: '<S855>/Constant'
 */
#define rtCP_Constant_Value_kwq        (0.0F)

/* Expression: const
 * Referenced by: '<S873>/Constant'
 */
#define rtCP_Constant_Value_hzv        (1.5F)

/* Expression: single(0)
 * Referenced by: '<S837>/Constant'
 */
#define rtCP_Constant_Value_nmx        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gv2
 * Referenced by: '<S903>/Constant'
 */
#define rtCP_Constant_Value_gv2        (26.0F)

/* Computed Parameter: rtCP_Constant_Value_jwm
 * Referenced by: '<S907>/Constant'
 */
#define rtCP_Constant_Value_jwm        (0.0F)

/* Expression: const
 * Referenced by: '<S910>/Constant'
 */
#define rtCP_Constant_Value_k1o        (-2.0F)

/* Expression: LTAPSampleTime
 * Referenced by: '<S1754>/SampleTime'
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
 * Referenced by: '<S1641>/Constant'
 */
#define rtCP_Constant_Value_hjt        (0.5F)

/* Expression: single(pi)
 * Referenced by: '<S1641>/Constant1'
 */
#define rtCP_Constant1_Value_fl        (3.14159274F)

/* Expression: single(pi/2)
 * Referenced by: '<S1710>/Constant1'
 */
#define rtCP_Constant1_Value_o4m       (1.57079637F)

/* Expression: single(1)
 * Referenced by: '<S1710>/Constant2'
 */
#define rtCP_Constant2_Value_od        (1.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S1713>/Constant5'
 */
#define rtCP_Constant5_Value_o1        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_iya
 * Referenced by: '<S1709>/Constant'
 */
#define rtCP_Constant_Value_iya        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oyk
 * Referenced by: '<S1711>/Constant'
 */
#define rtCP_Constant_Value_oyk        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ow
 * Referenced by: '<S1711>/Constant1'
 */
#define rtCP_Constant1_Value_ow        (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1717>/Constant'
 */
#define rtCP_Constant_Value_fi4        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_p2
 * Referenced by: '<S1721>/Constant'
 */
#define rtCP_Constant_Value_p2         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ir
 * Referenced by: '<S1719>/LimitSource'
 */
#define rtCP_LimitSource_Value_ir      (0.0001F)

/* Expression: single(0.5)
 * Referenced by: '<S1724>/Constant'
 */
#define rtCP_Constant_Value_jyr        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_na1
 * Referenced by: '<S1725>/Constant'
 */
#define rtCP_Constant_Value_na1        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_kig
 * Referenced by: '<S1725>/Constant1'
 */
#define rtCP_Constant1_Value_kig       (0.0F)

/* Expression: single(0.5)
 * Referenced by: '<S1727>/Constant'
 */
#define rtCP_Constant_Value_i5u        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_bnn
 * Referenced by: '<S1731>/Constant'
 */
#define rtCP_Constant_Value_bnn        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_lv
 * Referenced by: '<S1729>/LimitSource'
 */
#define rtCP_LimitSource_Value_lv      (0.0001F)

/* Expression: single(pi)
 * Referenced by: '<S1734>/Constant_2'
 */
#define rtCP_Constant_2_Value_dg       (3.14159274F)

/* Computed Parameter: rtCP_Constant_Value_i3
 * Referenced by: '<S1737>/Constant'
 */
#define rtCP_Constant_Value_i3         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fbr
 * Referenced by: '<S1738>/Constant'
 */
#define rtCP_Constant_Value_fbr        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nnh
 * Referenced by: '<S1739>/Constant'
 */
#define rtCP_Constant_Value_nnh        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ntp
 * Referenced by: '<S1740>/Constant'
 */
#define rtCP_Constant_Value_ntp        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1572>/Constant1'
 */
#define rtCP_Constant1_Value_jv        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1572>/Constant6'
 */
#define rtCP_Constant6_Value_f         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1573>/Constant1'
 */
#define rtCP_Constant1_Value_cgp       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1573>/Constant2'
 */
#define rtCP_Constant2_Value_gs        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1573>/Constant3'
 */
#define rtCP_Constant3_Value_k3        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1573>/Constant4'
 */
#define rtCP_Constant4_Value_b2        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1573>/Constant5'
 */
#define rtCP_Constant5_Value_n5        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1573>/Constant6'
 */
#define rtCP_Constant6_Value_o         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S1573>/Constant8'
 */
#define rtCP_Constant8_Value_d         (0.0F)

/* Expression: single(5)
 * Referenced by: '<S1798>/Constant'
 */
#define rtCP_Constant_Value_gjb        (5.0F)

/* Expression: single(-1)
 * Referenced by: '<S1798>/Constant2'
 */
#define rtCP_Constant2_Value_in        (-1.0F)

/* Expression: single(1)
 * Referenced by: '<S1798>/Constant3'
 */
#define rtCP_Constant3_Value_b         (1.0F)

/* Computed Parameter: rtCP_Constant_Value_ib1
 * Referenced by: '<S1800>/Constant'
 */
#define rtCP_Constant_Value_ib1        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S936>/Constant10'
 */
#define rtCP_Constant10_Value_k        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S936>/Constant3'
 */
#define rtCP_Constant3_Value_px        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S936>/Constant5'
 */
#define rtCP_Constant5_Value_p2        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S936>/Constant6'
 */
#define rtCP_Constant6_Value_p         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S936>/Constant8'
 */
#define rtCP_Constant8_Value_e         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S959>/Constant'
 */
#define rtCP_Constant_Value_lkg        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S960>/Constant6'
 */
#define rtCP_Constant6_Value_lk        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S960>/Constant8'
 */
#define rtCP_Constant8_Value_a         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ac
 * Referenced by: '<S1803>/Constant1'
 */
#define rtCP_Constant1_Value_ac        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_pn
 * Referenced by: '<S1803>/Constant3'
 */
#define rtCP_Constant3_Value_pn        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_pp
 * Referenced by: '<S1803>/Constant4'
 */
#define rtCP_Constant4_Value_pp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_je
 * Referenced by: '<S2088>/Constant'
 */
#define rtCP_Constant_Value_je         (0.0F)

/* Computed Parameter: rtCP_BrakeReductionLimit_Value
 * Referenced by: '<S27>/BrakeReductionLimit'
 */
#define rtCP_BrakeReductionLimit_Value (3.05555558F)

/* Computed Parameter: rtCP_zeroConstant2_Value
 * Referenced by: '<S15>/zeroConstant2'
 */
#define rtCP_zeroConstant2_Value       (0.0F)

/* Computed Parameter: rtCP_zeroConstant3_Value
 * Referenced by: '<S15>/zeroConstant3'
 */
#define rtCP_zeroConstant3_Value       (0.0F)

/* Computed Parameter: rtCP_zeroConstant4_Value
 * Referenced by: '<S15>/zeroConstant4'
 */
#define rtCP_zeroConstant4_Value       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S7>/Constant3'
 */
#define rtCP_Constant3_Value_jw        (0.0F)

/* Computed Parameter: rtCP_LowestSpeedToLimit_Value
 * Referenced by: '<S26>/LowestSpeedToLimit'
 */
#define rtCP_LowestSpeedToLimit_Value  (0.5F)

/* Expression: single(6)
 * Referenced by: '<S26>/ResetTime'
 */
#define rtCP_ResetTime_Value           (6.0F)

/* Expression: FCW_TypAvlLgtAccr_Co
 * Referenced by: '<S193>/FCW_TypAvlLgtAccr_Co'
 */
#define rtCP_FCW_TypAvlLgtAccr_Co_Value (-7.0F)

/* Computed Parameter: rtCP_ZERO_Value
 * Referenced by: '<S193>/ZERO'
 */
#define rtCP_ZERO_Value                (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bs0
 * Referenced by: '<S242>/Constant'
 */
#define rtCP_Constant_Value_bs0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pfz
 * Referenced by: '<S194>/Constant'
 */
#define rtCP_Constant_Value_pfz        (0.0F)

/* Computed Parameter: rtCP_FullOverlap_Value
 * Referenced by: '<S194>/FullOverlap'
 */
#define rtCP_FullOverlap_Value         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gd
 * Referenced by: '<S200>/Constant'
 */
#define rtCP_Constant_Value_gd         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_fn
 * Referenced by: '<S200>/Constant1'
 */
#define rtCP_Constant1_Value_fn        (1.0F)

/* Computed Parameter: rtCP_Constant3_Value_h0
 * Referenced by: '<S200>/Constant3'
 */
#define rtCP_Constant3_Value_h0        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_oxn
 * Referenced by: '<S200>/Constant4'
 */
#define rtCP_Constant4_Value_oxn       (1.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S200>/FCW_Freq_Co'
 */
#define rtCP_FCW_Freq_Co_Value         (50.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S200>/FCW_Freq_Co1'
 */
#define rtCP_FCW_Freq_Co1_Value        (50.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S203>/FCW_Freq_Co'
 */
#define rtCP_FCW_Freq_Co_Value_g       (50.0F)

/* Computed Parameter: rtCP_Constant_Value_jk
 * Referenced by: '<S269>/Constant'
 */
#define rtCP_Constant_Value_jk         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_oj
 * Referenced by: '<S269>/Constant1'
 */
#define rtCP_Constant1_Value_oj        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_ls
 * Referenced by: '<S286>/Constant'
 */
#define rtCP_Constant_Value_ls         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_iir
 * Referenced by: '<S300>/Constant'
 */
#define rtCP_Constant_Value_iir        (2.0F)

/* Computed Parameter: rtCP_Constant_Value_pzd
 * Referenced by: '<S301>/Constant'
 */
#define rtCP_Constant_Value_pzd        (13.8888893F)

/* Computed Parameter: rtCP_Constant_Value_n34
 * Referenced by: '<S205>/Constant'
 */
#define rtCP_Constant_Value_n34        (-1.0F)

/* Expression: FCW_TypAvlLatAccr_Co
 * Referenced by: '<S311>/FCW_TypAvlLatAccr_Co'
 */
#define rtCP_FCW_TypAvlLatAccr_Co_Value (2.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S313>/FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca2'
 */
#define rtCP_FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca2_Value (50.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S313>/FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca8'
 */
#define rtCP_FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca8_Value (50.0F)

/* Computed Parameter: rtCP_Constant_Value_jz
 * Referenced by: '<S316>/Constant'
 */
#define rtCP_Constant_Value_jz         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ay
 * Referenced by: '<S316>/Constant1'
 */
#define rtCP_Constant1_Value_ay        (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_gd
 * Referenced by: '<S317>/Constant2'
 */
#define rtCP_Constant2_Value_gd        (1.0F)

/* Computed Parameter: rtCP_Constant4_Value_or
 * Referenced by: '<S317>/Constant4'
 */
#define rtCP_Constant4_Value_or        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_loo
 * Referenced by: '<S315>/Constant'
 */
#define rtCP_Constant_Value_loo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_p3b
 * Referenced by: '<S329>/Constant'
 */
#define rtCP_Constant_Value_p3b        (0.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S324>/FCW_Freq_Co'
 */
#define rtCP_FCW_Freq_Co_Value_g0      (50.0F)

/* Expression: single(0)
 * Referenced by: '<S321>/NoDelay'
 */
#define rtCP_NoDelay_Value             (0.0F)

/* Expression: single(0)
 * Referenced by: '<S321>/NoDelay1'
 */
#define rtCP_NoDelay1_Value            (0.0F)

/* Expression: FCW_Freq_Co
 * Referenced by: '<S40>/FCW_Freq_Co'
 */
#define rtCP_FCW_Freq_Co_Value_e       (50.0F)

/* Computed Parameter: rtCP_Constant_Value_eii
 * Referenced by: '<S354>/Constant'
 */
#define rtCP_Constant_Value_eii        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_g0d
 * Referenced by: '<S354>/Constant1'
 */
#define rtCP_Constant1_Value_g0d       (1.0F)

/* Expression: single(0)
 * Referenced by: '<S463>/AccReqNoActivation'
 */
#define rtCP_AccReqNoActivation_Value  (0.0F)

/* Computed Parameter: rtCP_Constant_Value_clu
 * Referenced by: '<S468>/Constant'
 */
#define rtCP_Constant_Value_clu        (0.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S471>/iteration time2'
 */
#define rtCP_iterationtime2_Value      (0.02F)

/* Computed Parameter: rtCP_Constant_Value_bq0
 * Referenced by: '<S480>/Constant'
 */
#define rtCP_Constant_Value_bq0        (0.0F)

/* Expression: single(1)
 * Referenced by: '<S485>/PreBrkMaxIncrease'
 */
#define rtCP_PreBrkMaxIncrease_Value   (1.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S485>/iteration time2'
 */
#define rtCP_iterationtime2_Value_j    (0.02F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S505>/SampleTime'
 */
#define rtCP_SampleTime_Value_l        (0.02F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S501>/SampleTime'
 */
#define rtCP_SampleTime_Value_i        (0.02F)

/* Expression: single(0)
 * Referenced by: '<S467>/Constant1'
 */
#define rtCP_Constant1_Value_gco       (0.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S527>/SampleTime'
 */
#define rtCP_SampleTime_Value_nv       (0.02F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S528>/SampleTime'
 */
#define rtCP_SampleTime_Value_k        (0.02F)

/* Expression: single(0)
 * Referenced by: '<S555>/ZeroAcceleration'
 */
#define rtCP_ZeroAcceleration_Value    (0.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S554>/PeriodFunctionCall'
 */
#define rtCP_PeriodFunctionCall_Value  (0.02F)

/* Expression: CMBB_LoPosValInCllsnRednByBrkg_Co
 * Referenced by: '<S534>/LoPosValInCllsnRednByBrkg  '
 */
#define rtCP_LoPosValInCllsnRednByBrkg_Value (0.0001F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S535>/PeriodFunctionCall'
 */
#define rtCP_PeriodFunctionCall_Value_n (0.02F)

/* Expression: k_AEB_FrqFctCallInCllsnRednByBrkg
 * Referenced by: '<S565>/Constant9'
 */
#define rtCP_Constant9_Value_k         (40.0F)

/* Computed Parameter: rtCP_Constant2_Value_pf
 * Referenced by: '<S570>/Constant2'
 */
#define rtCP_Constant2_Value_pf        (1.0F)

/* Computed Parameter: rtCP_Constant4_Value_jo
 * Referenced by: '<S570>/Constant4'
 */
#define rtCP_Constant4_Value_jo        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S455>/Constant1'
 */
#define rtCP_Constant1_Value_ko        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_es
 * Referenced by: '<S589>/Constant2'
 */
#define rtCP_Constant2_Value_es        (1.0F)

/* Computed Parameter: rtCP_Constant4_Value_d1
 * Referenced by: '<S589>/Constant4'
 */
#define rtCP_Constant4_Value_d1        (0.0F)

/* Expression: k_AEB_FrqFctCallInCllsnRednByBrkg
 * Referenced by: '<S583>/iteration time2'
 */
#define rtCP_iterationtime2_Value_k    (40.0F)

/* Expression: single(100)
 * Referenced by: '<S584>/CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca'
 */
#define rtCP_CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca_Value (100.0F)

/* Expression: single(0)
 * Referenced by: '<S584>/CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca1'
 */
#define rtCP_CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca1_Value (0.0F)

/* Expression: single(0)
 * Referenced by: '<S584>/CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca3'
 */
#define rtCP_CMBB_TiDlyDeactvnInCllsnRednByBrkg_Ca3_Value (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aiw
 * Referenced by: '<S593>/Constant'
 */
#define rtCP_Constant_Value_aiw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ea2
 * Referenced by: '<S594>/Constant'
 */
#define rtCP_Constant_Value_ea2        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_jt
 * Referenced by: '<S596>/LimitSource'
 */
#define rtCP_LimitSource_Value_jt      (0.01F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S591>/SampleTime'
 */
#define rtCP_SampleTime_Value_ia       (0.02F)

/* Computed Parameter: rtCP_Constant3_Value_lv
 * Referenced by: '<S592>/Constant3'
 */
#define rtCP_Constant3_Value_lv        (100.0F)

/* Computed Parameter: rtCP_Constant_Value_lc
 * Referenced by: '<S601>/Constant'
 */
#define rtCP_Constant_Value_lc         (0.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S604>/SampleTime'
 */
#define rtCP_SampleTime_Value_j        (0.02F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S609>/PeriodFunctionCall'
 */
#define rtCP_PeriodFunctionCall_Value_p (0.02F)

/* Expression: CMBB_LoPosValInCllsnRednByBrkg_Co
 * Referenced by: '<S588>/LoPosValInCllsnRednByBrkg  '
 */
#define rtCP_LoPosValInCllsnRednByBrkg_Value_k (0.0001F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S611>/SampleTime'
 */
#define rtCP_SampleTime_Value_kv       (0.02F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S578>/PeriodFunctionCall'
 */
#define rtCP_PeriodFunctionCall_Value_na (0.02F)

/* Computed Parameter: rtCP_Constant_Value_pg
 * Referenced by: '<S667>/Constant'
 */
#define rtCP_Constant_Value_pg         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jbm
 * Referenced by: '<S693>/Constant'
 */
#define rtCP_Constant_Value_jbm        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_kb
 * Referenced by: '<S688>/Constant1'
 */
#define rtCP_Constant1_Value_kb        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S698>/Constant3'
 */
#define rtCP_Constant3_Value_kz        (0.0F)

/* Expression: single(pi)
 * Referenced by: '<S704>/Constant4'
 */
#define rtCP_Constant4_Value_nk        (3.14159274F)

/* Expression: k_AEB_FrqFctCallInCllsnRednByBrkg
 * Referenced by: '<S707>/Constant9'
 */
#define rtCP_Constant9_Value_i         (40.0F)

/* Computed Parameter: rtCP_Constant_Value_pl
 * Referenced by: '<S715>/Constant'
 */
#define rtCP_Constant_Value_pl         (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_bly
 * Referenced by: '<S715>/Constant1'
 */
#define rtCP_Constant1_Value_bly       (1.0F)

/* Expression: single(pi)
 * Referenced by: '<S718>/Constant5'
 */
#define rtCP_Constant5_Value_ok        (3.14159274F)

/* Expression: single(0)
 * Referenced by: '<S719>/Constant8'
 */
#define rtCP_Constant8_Value_n         (0.0F)

/* Expression: k_AEB_FrqFctCallInCllsnRednByBrkg
 * Referenced by: '<S719>/Constant9'
 */
#define rtCP_Constant9_Value_c         (40.0F)

/* Computed Parameter: rtCP_Constant_Value_bi2
 * Referenced by: '<S730>/Constant'
 */
#define rtCP_Constant_Value_bi2        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_cnfp
 * Referenced by: '<S730>/Constant1'
 */
#define rtCP_Constant1_Value_cnfp      (1.0F)

/* Expression: k_AEB_FrqFctCallInCllsnRednByBrkg
 * Referenced by: '<S722>/Constant9'
 */
#define rtCP_Constant9_Value_p         (40.0F)

/* Computed Parameter: rtCP_Constant_Value_dkl
 * Referenced by: '<S732>/Constant'
 */
#define rtCP_Constant_Value_dkl        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_oc
 * Referenced by: '<S732>/Constant1'
 */
#define rtCP_Constant1_Value_oc        (1.0F)

/* Expression: single(0)
 * Referenced by: '<S691>/Constant'
 */
#define rtCP_Constant_Value_jbg        (0.0F)

/* Expression: k_AEB_PerdFctCallInCllsnRednByBrkg
 * Referenced by: '<S739>/SampleTime'
 */
#define rtCP_SampleTime_Value_c        (0.02F)

/* Expression: single(1)
 * Referenced by: '<S2117>/CosHeading'
 */
#define rtCP_CosHeading_Value          (1.0F)

/* Expression: single(0.01)
 * Referenced by: '<S2117>/LengthSideLat'
 */
#define rtCP_LengthSideLat_Value       (0.01F)

/* Expression: single(0.01)
 * Referenced by: '<S2117>/LengthSideLgt'
 */
#define rtCP_LengthSideLgt_Value       (0.01F)

/* Expression: single(0)
 * Referenced by: '<S2117>/RotationAngle'
 */
#define rtCP_RotationAngle_Value       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2117>/SinHeading'
 */
#define rtCP_SinHeading_Value          (0.0F)

/* Computed Parameter: rtCP_Constant_Value_n1s
 * Referenced by: '<S2139>/Constant'
 */
#define rtCP_Constant_Value_n1s        (0.0F)

/* Expression: single(2)
 * Referenced by: '<S2089>/Constant13'
 */
#define rtCP_Constant13_Value_hv       (2.0F)

/* Computed Parameter: rtCP_Constant20_Value
 * Referenced by: '<S2089>/Constant20'
 */
#define rtCP_Constant20_Value          (1.0F)

/* Expression: single(0)
 * Referenced by: '<S2089>/Constant32'
 */
#define rtCP_Constant32_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2089>/Constant33'
 */
#define rtCP_Constant33_Value_n        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2089>/Constant34'
 */
#define rtCP_Constant34_Value_d        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2089>/Constant35'
 */
#define rtCP_Constant35_Value_j        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2089>/Constant36'
 */
#define rtCP_Constant36_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2089>/Constant9'
 */
#define rtCP_Constant9_Value_cd        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2089>/Constant_2'
 */
#define rtCP_Constant_2_Value_c        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2089>/Constant_25'
 */
#define rtCP_Constant_25_Value         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2106>/Constant4'
 */
#define rtCP_Constant4_Value_h0        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2167>/Constant5'
 */
#define rtCP_Constant5_Value_l4        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2168>/Constant5'
 */
#define rtCP_Constant5_Value_dj        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_eyw
 * Referenced by: '<S2190>/Constant'
 */
#define rtCP_Constant_Value_eyw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_le4
 * Referenced by: '<S2191>/Constant'
 */
#define rtCP_Constant_Value_le4        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_i1
 * Referenced by: '<S2192>/LimitSource'
 */
#define rtCP_LimitSource_Value_i1      (0.01F)

/* Computed Parameter: rtCP_Zero_Value_p
 * Referenced by: '<S2183>/Zero'
 */
#define rtCP_Zero_Value_p              (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_p3
 * Referenced by: '<S2175>/Constant3'
 */
#define rtCP_Constant3_Value_p3        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2175>/OffsMinForCllsnRednByBrkgActv1'
 */
#define rtCP_OffsMinForCllsnRednByBrkgActv1_Value (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_n3
 * Referenced by: '<S2187>/Constant3'
 */
#define rtCP_Constant3_Value_n3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ksz
 * Referenced by: '<S2193>/Constant'
 */
#define rtCP_Constant_Value_ksz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_eqw
 * Referenced by: '<S2176>/Constant'
 */
#define rtCP_Constant_Value_eqw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nhh
 * Referenced by: '<S2198>/Constant'
 */
#define rtCP_Constant_Value_nhh        (4.0F)

/* Computed Parameter: rtCP_Constant_Value_cey
 * Referenced by: '<S2178>/Constant'
 */
#define rtCP_Constant_Value_cey        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gp
 * Referenced by: '<S2201>/Constant'
 */
#define rtCP_Constant_Value_gp         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ph
 * Referenced by: '<S2202>/Constant'
 */
#define rtCP_Constant_Value_ph         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kit
 * Referenced by: '<S2203>/Constant'
 */
#define rtCP_Constant_Value_kit        (0.0F)

/* Expression: single(-0.5)
 * Referenced by: '<S2203>/Constant1'
 */
#define rtCP_Constant1_Value_euq       (-0.5F)

/* Computed Parameter: rtCP_Constant_Value_ayk
 * Referenced by: '<S2214>/Constant'
 */
#define rtCP_Constant_Value_ayk        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ewy
 * Referenced by: '<S2215>/Constant'
 */
#define rtCP_Constant_Value_ewy        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ad
 * Referenced by: '<S2216>/Constant'
 */
#define rtCP_Constant_Value_ad         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bc2
 * Referenced by: '<S2219>/Constant'
 */
#define rtCP_Constant_Value_bc2        (0.65F)

/* Computed Parameter: rtCP_Constant_Value_d5q
 * Referenced by: '<S2217>/Constant'
 */
#define rtCP_Constant_Value_d5q        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f1k
 * Referenced by: '<S2232>/Constant'
 */
#define rtCP_Constant_Value_f1k        (4.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2234>/Constant5'
 */
#define rtCP_Constant5_Value_hj        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2235>/Constant5'
 */
#define rtCP_Constant5_Value_fc        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_gh
 * Referenced by: '<S2236>/LimitSource'
 */
#define rtCP_LimitSource_Value_gh      (1.0E-5F)

/* Computed Parameter: rtCP_Constant_Value_jnt
 * Referenced by: '<S2244>/Constant'
 */
#define rtCP_Constant_Value_jnt        (0.2F)

/* Computed Parameter: rtCP_Constant_Value_in0
 * Referenced by: '<S2245>/Constant'
 */
#define rtCP_Constant_Value_in0        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_cvp
 * Referenced by: '<S2246>/Constant'
 */
#define rtCP_Constant_Value_cvp        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_e2r
 * Referenced by: '<S2248>/Constant'
 */
#define rtCP_Constant_Value_e2r        (1.2F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2260>/Constant5'
 */
#define rtCP_Constant5_Value_cvk       (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2261>/Constant5'
 */
#define rtCP_Constant5_Value_fq        (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_dxf
 * Referenced by: '<S2278>/Constant'
 */
#define rtCP_Constant_Value_dxf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cvo
 * Referenced by: '<S2287>/Constant'
 */
#define rtCP_Constant_Value_cvo        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2323>/Constant'
 */
#define rtCP_Constant_Value_do         (0.0F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S2325>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value (0.01F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S2325>/LengthSideLgtNoLength1'
 */
#define rtCP_LengthSideLgtNoLength1_Value (0.01F)

/* Computed Parameter: rtCP_Constant_Value_cmr
 * Referenced by: '<S2348>/Constant'
 */
#define rtCP_Constant_Value_cmr        (4.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2353>/Constant5'
 */
#define rtCP_Constant5_Value_o5        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2354>/Constant5'
 */
#define rtCP_Constant5_Value_iu        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_cvi
 * Referenced by: '<S2355>/LimitSource'
 */
#define rtCP_LimitSource_Value_cvi     (1.0E-5F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2362>/Constant5'
 */
#define rtCP_Constant5_Value_cr        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2363>/Constant5'
 */
#define rtCP_Constant5_Value_fm        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_dp
 * Referenced by: '<S2364>/LimitSource'
 */
#define rtCP_LimitSource_Value_dp      (1.0E-5F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2371>/Constant5'
 */
#define rtCP_Constant5_Value_go        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2372>/Constant5'
 */
#define rtCP_Constant5_Value_hh        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_cwy
 * Referenced by: '<S2373>/LimitSource'
 */
#define rtCP_LimitSource_Value_cwy     (1.0E-5F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2380>/Constant5'
 */
#define rtCP_Constant5_Value_nz        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S2381>/Constant5'
 */
#define rtCP_Constant5_Value_a5        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_cft
 * Referenced by: '<S2382>/LimitSource'
 */
#define rtCP_LimitSource_Value_cft     (1.0E-5F)

/* Computed Parameter: rtCP_Constant1_Value_p2j
 * Referenced by: '<S2393>/Constant1'
 */
#define rtCP_Constant1_Value_p2j       (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_ci
 * Referenced by: '<S2393>/Constant2'
 */
#define rtCP_Constant2_Value_ci        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_od
 * Referenced by: '<S2393>/Constant3'
 */
#define rtCP_Constant3_Value_od        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_bj
 * Referenced by: '<S2393>/Constant4'
 */
#define rtCP_Constant4_Value_bj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mim
 * Referenced by: '<S2397>/Constant'
 */
#define rtCP_Constant_Value_mim        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ia
 * Referenced by: '<S2394>/Constant1'
 */
#define rtCP_Constant1_Value_ia        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_aq
 * Referenced by: '<S2394>/Constant2'
 */
#define rtCP_Constant2_Value_aq        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_pe
 * Referenced by: '<S2394>/Constant3'
 */
#define rtCP_Constant3_Value_pe        (0.0F)

/* Computed Parameter: rtCP_Constant8_Value_p
 * Referenced by: '<S2394>/Constant8'
 */
#define rtCP_Constant8_Value_p         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_our
 * Referenced by: '<S2399>/Constant'
 */
#define rtCP_Constant_Value_our        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_dzs
 * Referenced by: '<S2395>/Constant1'
 */
#define rtCP_Constant1_Value_dzs       (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_edp
 * Referenced by: '<S2395>/Constant2'
 */
#define rtCP_Constant2_Value_edp       (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_bp
 * Referenced by: '<S2395>/Constant3'
 */
#define rtCP_Constant3_Value_bp        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_h0x
 * Referenced by: '<S2395>/Constant4'
 */
#define rtCP_Constant4_Value_h0x       (0.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S2413>/Constant_1'
 */
#define rtCP_Constant_1_Value_by       (1.57079637F)

/* Computed Parameter: rtCP_Constant_2_Value_ot
 * Referenced by: '<S2413>/Constant_2'
 */
#define rtCP_Constant_2_Value_ot       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_orz
 * Referenced by: '<S2773>/Constant'
 */
#define rtCP_Constant_Value_orz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pup
 * Referenced by: '<S2774>/Constant'
 */
#define rtCP_Constant_Value_pup        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_bv
 * Referenced by: '<S2775>/LimitSource'
 */
#define rtCP_LimitSource_Value_bv      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_dil
 * Referenced by: '<S2776>/Constant'
 */
#define rtCP_Constant_Value_dil        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_anj
 * Referenced by: '<S2777>/Constant'
 */
#define rtCP_Constant_Value_anj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mtt
 * Referenced by: '<S2778>/Constant'
 */
#define rtCP_Constant_Value_mtt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mg0
 * Referenced by: '<S2779>/Constant'
 */
#define rtCP_Constant_Value_mg0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oc
 * Referenced by: '<S2780>/Constant'
 */
#define rtCP_Constant_Value_oc         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f0v
 * Referenced by: '<S2781>/Constant'
 */
#define rtCP_Constant_Value_f0v        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hys
 * Referenced by: '<S2782>/Constant'
 */
#define rtCP_Constant_Value_hys        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2772>/Constant'
 */
#define rtCP_Constant_Value_jle        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2772>/Constant1'
 */
#define rtCP_Constant1_Value_pm        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_emt
 * Referenced by: '<S2788>/Constant'
 */
#define rtCP_Constant_Value_emt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_l4u
 * Referenced by: '<S2789>/Constant'
 */
#define rtCP_Constant_Value_l4u        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_om
 * Referenced by: '<S2790>/LimitSource'
 */
#define rtCP_LimitSource_Value_om      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_e5s
 * Referenced by: '<S2791>/Constant'
 */
#define rtCP_Constant_Value_e5s        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_clb
 * Referenced by: '<S2792>/Constant'
 */
#define rtCP_Constant_Value_clb        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ltc
 * Referenced by: '<S2793>/Constant'
 */
#define rtCP_Constant_Value_ltc        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fif
 * Referenced by: '<S2794>/Constant'
 */
#define rtCP_Constant_Value_fif        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gon
 * Referenced by: '<S2795>/Constant'
 */
#define rtCP_Constant_Value_gon        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_e3z
 * Referenced by: '<S2796>/Constant'
 */
#define rtCP_Constant_Value_e3z        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i3s
 * Referenced by: '<S2797>/Constant'
 */
#define rtCP_Constant_Value_i3s        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2787>/Constant'
 */
#define rtCP_Constant_Value_am         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2787>/Constant1'
 */
#define rtCP_Constant1_Value_ja        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mb
 * Referenced by: '<S2801>/Constant'
 */
#define rtCP_Constant_Value_mb         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jew
 * Referenced by: '<S2802>/Constant'
 */
#define rtCP_Constant_Value_jew        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nhn
 * Referenced by: '<S2803>/Constant'
 */
#define rtCP_Constant_Value_nhn        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ia
 * Referenced by: '<S2804>/Constant'
 */
#define rtCP_Constant_Value_ia         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_iah
 * Referenced by: '<S2805>/Constant'
 */
#define rtCP_Constant_Value_iah        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dix
 * Referenced by: '<S2806>/Constant'
 */
#define rtCP_Constant_Value_dix        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_axc
 * Referenced by: '<S2807>/Constant'
 */
#define rtCP_Constant_Value_axc        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2800>/Constant'
 */
#define rtCP_Constant_Value_kws        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2800>/Constant1'
 */
#define rtCP_Constant1_Value_bm        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jh
 * Referenced by: '<S2811>/Constant'
 */
#define rtCP_Constant_Value_jh         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ll
 * Referenced by: '<S2812>/Constant'
 */
#define rtCP_Constant_Value_ll         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jbd
 * Referenced by: '<S2813>/Constant'
 */
#define rtCP_Constant_Value_jbd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jf5
 * Referenced by: '<S2814>/Constant'
 */
#define rtCP_Constant_Value_jf5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ix
 * Referenced by: '<S2815>/Constant'
 */
#define rtCP_Constant_Value_ix         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dn5
 * Referenced by: '<S2816>/Constant'
 */
#define rtCP_Constant_Value_dn5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_j54
 * Referenced by: '<S2817>/Constant'
 */
#define rtCP_Constant_Value_j54        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2810>/Constant'
 */
#define rtCP_Constant_Value_mbf        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2810>/Constant1'
 */
#define rtCP_Constant1_Value_ek        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_chl
 * Referenced by: '<S2821>/Constant'
 */
#define rtCP_Constant_Value_chl        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hvc
 * Referenced by: '<S2822>/Constant'
 */
#define rtCP_Constant_Value_hvc        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gly
 * Referenced by: '<S2823>/Constant'
 */
#define rtCP_Constant_Value_gly        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ka
 * Referenced by: '<S2824>/Constant'
 */
#define rtCP_Constant_Value_ka         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ea3
 * Referenced by: '<S2825>/Constant'
 */
#define rtCP_Constant_Value_ea3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lv
 * Referenced by: '<S2826>/Constant'
 */
#define rtCP_Constant_Value_lv         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mzi
 * Referenced by: '<S2827>/Constant'
 */
#define rtCP_Constant_Value_mzi        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2820>/Constant'
 */
#define rtCP_Constant_Value_gcz        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2820>/Constant1'
 */
#define rtCP_Constant1_Value_kc1       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_h0q
 * Referenced by: '<S2831>/Constant'
 */
#define rtCP_Constant_Value_h0q        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_atp
 * Referenced by: '<S2832>/Constant'
 */
#define rtCP_Constant_Value_atp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fg5
 * Referenced by: '<S2833>/Constant'
 */
#define rtCP_Constant_Value_fg5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lmf
 * Referenced by: '<S2834>/Constant'
 */
#define rtCP_Constant_Value_lmf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_afw
 * Referenced by: '<S2835>/Constant'
 */
#define rtCP_Constant_Value_afw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f0z
 * Referenced by: '<S2836>/Constant'
 */
#define rtCP_Constant_Value_f0z        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cl2
 * Referenced by: '<S2837>/Constant'
 */
#define rtCP_Constant_Value_cl2        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2830>/Constant'
 */
#define rtCP_Constant_Value_hdn        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2830>/Constant1'
 */
#define rtCP_Constant1_Value_i4t       (0.0F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S2409>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value_e (0.01F)

/* Expression: single(pi/2)
 * Referenced by: '<S2843>/Constant'
 */
#define rtCP_Constant_Value_dzn        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S2852>/Constant'
 */
#define rtCP_Constant_Value_bca        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S2861>/Constant'
 */
#define rtCP_Constant_Value_f2         (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S2870>/Constant'
 */
#define rtCP_Constant_Value_eoo        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S2879>/Constant'
 */
#define rtCP_Constant_Value_etyy       (1.57079637F)

/* Computed Parameter: rtCP_Constant_Value_iel
 * Referenced by: '<S3339>/Constant'
 */
#define rtCP_Constant_Value_iel        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_o04
 * Referenced by: '<S3340>/Constant'
 */
#define rtCP_Constant_Value_o04        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_hz
 * Referenced by: '<S3341>/LimitSource'
 */
#define rtCP_LimitSource_Value_hz      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_jnp
 * Referenced by: '<S3342>/Constant'
 */
#define rtCP_Constant_Value_jnp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lq0
 * Referenced by: '<S3343>/Constant'
 */
#define rtCP_Constant_Value_lq0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oyv
 * Referenced by: '<S3344>/Constant'
 */
#define rtCP_Constant_Value_oyv        (-0.41F)

/* Computed Parameter: rtCP_Constant_Value_on
 * Referenced by: '<S3345>/Constant'
 */
#define rtCP_Constant_Value_on         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bmq
 * Referenced by: '<S3346>/Constant'
 */
#define rtCP_Constant_Value_bmq        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lqo
 * Referenced by: '<S3347>/Constant'
 */
#define rtCP_Constant_Value_lqo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_c3l
 * Referenced by: '<S3348>/Constant'
 */
#define rtCP_Constant_Value_c3l        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3338>/Constant'
 */
#define rtCP_Constant_Value_avu        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3338>/Constant1'
 */
#define rtCP_Constant1_Value_jp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mki
 * Referenced by: '<S3354>/Constant'
 */
#define rtCP_Constant_Value_mki        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ii4
 * Referenced by: '<S3355>/Constant'
 */
#define rtCP_Constant_Value_ii4        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_lt
 * Referenced by: '<S3356>/LimitSource'
 */
#define rtCP_LimitSource_Value_lt      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_fyk
 * Referenced by: '<S3357>/Constant'
 */
#define rtCP_Constant_Value_fyk        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ptt
 * Referenced by: '<S3358>/Constant'
 */
#define rtCP_Constant_Value_ptt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hpx
 * Referenced by: '<S3359>/Constant'
 */
#define rtCP_Constant_Value_hpx        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_eh
 * Referenced by: '<S3360>/Constant'
 */
#define rtCP_Constant_Value_eh         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bpd
 * Referenced by: '<S3361>/Constant'
 */
#define rtCP_Constant_Value_bpd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dss
 * Referenced by: '<S3362>/Constant'
 */
#define rtCP_Constant_Value_dss        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f1z
 * Referenced by: '<S3363>/Constant'
 */
#define rtCP_Constant_Value_f1z        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3353>/Constant'
 */
#define rtCP_Constant_Value_gb2        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3353>/Constant1'
 */
#define rtCP_Constant1_Value_g2        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_db
 * Referenced by: '<S3367>/Constant'
 */
#define rtCP_Constant_Value_db         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_myo
 * Referenced by: '<S3368>/Constant'
 */
#define rtCP_Constant_Value_myo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ar1
 * Referenced by: '<S3369>/Constant'
 */
#define rtCP_Constant_Value_ar1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kww
 * Referenced by: '<S3370>/Constant'
 */
#define rtCP_Constant_Value_kww        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_abg
 * Referenced by: '<S3371>/Constant'
 */
#define rtCP_Constant_Value_abg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_apz
 * Referenced by: '<S3372>/Constant'
 */
#define rtCP_Constant_Value_apz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f3
 * Referenced by: '<S3373>/Constant'
 */
#define rtCP_Constant_Value_f3         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3366>/Constant'
 */
#define rtCP_Constant_Value_cbo        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3366>/Constant1'
 */
#define rtCP_Constant1_Value_in        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_njw
 * Referenced by: '<S3377>/Constant'
 */
#define rtCP_Constant_Value_njw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gf4u
 * Referenced by: '<S3378>/Constant'
 */
#define rtCP_Constant_Value_gf4u       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nxw
 * Referenced by: '<S3379>/Constant'
 */
#define rtCP_Constant_Value_nxw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dn1
 * Referenced by: '<S3380>/Constant'
 */
#define rtCP_Constant_Value_dn1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_k2i
 * Referenced by: '<S3381>/Constant'
 */
#define rtCP_Constant_Value_k2i        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hf
 * Referenced by: '<S3382>/Constant'
 */
#define rtCP_Constant_Value_hf         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bjq
 * Referenced by: '<S3383>/Constant'
 */
#define rtCP_Constant_Value_bjq        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3376>/Constant'
 */
#define rtCP_Constant_Value_bxk        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3376>/Constant1'
 */
#define rtCP_Constant1_Value_ed        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lom
 * Referenced by: '<S3387>/Constant'
 */
#define rtCP_Constant_Value_lom        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cmo
 * Referenced by: '<S3388>/Constant'
 */
#define rtCP_Constant_Value_cmo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dxv
 * Referenced by: '<S3389>/Constant'
 */
#define rtCP_Constant_Value_dxv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_js1
 * Referenced by: '<S3390>/Constant'
 */
#define rtCP_Constant_Value_js1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mtx
 * Referenced by: '<S3391>/Constant'
 */
#define rtCP_Constant_Value_mtx        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pnz
 * Referenced by: '<S3392>/Constant'
 */
#define rtCP_Constant_Value_pnz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_he5
 * Referenced by: '<S3393>/Constant'
 */
#define rtCP_Constant_Value_he5        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3386>/Constant'
 */
#define rtCP_Constant_Value_hgp        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3386>/Constant1'
 */
#define rtCP_Constant1_Value_jd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nuq
 * Referenced by: '<S3397>/Constant'
 */
#define rtCP_Constant_Value_nuq        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kgv
 * Referenced by: '<S3398>/Constant'
 */
#define rtCP_Constant_Value_kgv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hgo
 * Referenced by: '<S3399>/Constant'
 */
#define rtCP_Constant_Value_hgo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dc
 * Referenced by: '<S3400>/Constant'
 */
#define rtCP_Constant_Value_dc         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ljf
 * Referenced by: '<S3401>/Constant'
 */
#define rtCP_Constant_Value_ljf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_j1o
 * Referenced by: '<S3402>/Constant'
 */
#define rtCP_Constant_Value_j1o        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lue
 * Referenced by: '<S3403>/Constant'
 */
#define rtCP_Constant_Value_lue        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3396>/Constant'
 */
#define rtCP_Constant_Value_azt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3396>/Constant1'
 */
#define rtCP_Constant1_Value_jo        (0.0F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S2967>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value_f (0.01F)

/* Expression: single(2)
 * Referenced by: '<S3409>/Constant'
 */
#define rtCP_Constant_Value_lne        (2.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S3418>/Constant'
 */
#define rtCP_Constant_Value_efv        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S3427>/Constant'
 */
#define rtCP_Constant_Value_ibv        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S3436>/Constant'
 */
#define rtCP_Constant_Value_de         (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S3445>/Constant'
 */
#define rtCP_Constant_Value_nkw        (1.57079637F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3545>/Constant5'
 */
#define rtCP_Constant5_Value_iy        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3546>/Constant5'
 */
#define rtCP_Constant5_Value_ld        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_o1q
 * Referenced by: '<S3547>/LimitSource'
 */
#define rtCP_LimitSource_Value_o1q     (1.0E-5F)

/* Expression: single(0)
 * Referenced by: '<S3570>/Constant'
 */
#define rtCP_Constant_Value_lff        (0.0F)

/* Expression: single(0.2)
 * Referenced by: '<S3571>/Constant'
 */
#define rtCP_Constant_Value_oj4        (0.2F)

/* Computed Parameter: rtCP_Constant_Value_asc
 * Referenced by: '<S3653>/Constant'
 */
#define rtCP_Constant_Value_asc        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_afz
 * Referenced by: '<S3654>/Constant'
 */
#define rtCP_Constant_Value_afz        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_gpk
 * Referenced by: '<S3655>/LimitSource'
 */
#define rtCP_LimitSource_Value_gpk     (0.01F)

/* Computed Parameter: rtCP_Constant_Value_kp
 * Referenced by: '<S3662>/Constant'
 */
#define rtCP_Constant_Value_kp         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jxt
 * Referenced by: '<S3663>/Constant'
 */
#define rtCP_Constant_Value_jxt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_feg
 * Referenced by: '<S3664>/Constant'
 */
#define rtCP_Constant_Value_feg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fui
 * Referenced by: '<S3665>/Constant'
 */
#define rtCP_Constant_Value_fui        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mij
 * Referenced by: '<S3742>/Constant'
 */
#define rtCP_Constant_Value_mij        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_p0n
 * Referenced by: '<S3743>/Constant'
 */
#define rtCP_Constant_Value_p0n        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_pi
 * Referenced by: '<S3744>/LimitSource'
 */
#define rtCP_LimitSource_Value_pi      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_iyd
 * Referenced by: '<S3751>/Constant'
 */
#define rtCP_Constant_Value_iyd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kzu
 * Referenced by: '<S3752>/Constant'
 */
#define rtCP_Constant_Value_kzu        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ld0
 * Referenced by: '<S3753>/Constant'
 */
#define rtCP_Constant_Value_ld0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_g3c
 * Referenced by: '<S3754>/Constant'
 */
#define rtCP_Constant_Value_g3c        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_dn
 * Referenced by: '<S3761>/LimitSource'
 */
#define rtCP_LimitSource_Value_dn      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_bx
 * Referenced by: '<S3762>/LimitSource'
 */
#define rtCP_LimitSource_Value_bx      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_hex
 * Referenced by: '<S3763>/Constant'
 */
#define rtCP_Constant_Value_hex        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lx5
 * Referenced by: '<S3764>/Constant'
 */
#define rtCP_Constant_Value_lx5        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_m1a
 * Referenced by: '<S3765>/LimitSource'
 */
#define rtCP_LimitSource_Value_m1a     (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_kl
 * Referenced by: '<S3766>/LimitSource'
 */
#define rtCP_LimitSource_Value_kl      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_bb1
 * Referenced by: '<S3767>/Constant'
 */
#define rtCP_Constant_Value_bb1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hrf
 * Referenced by: '<S3768>/Constant'
 */
#define rtCP_Constant_Value_hrf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_f0v1
 * Referenced by: '<S3769>/Constant'
 */
#define rtCP_Constant_Value_f0v1       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jmn
 * Referenced by: '<S3770>/Constant'
 */
#define rtCP_Constant_Value_jmn        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ljo
 * Referenced by: '<S3771>/Constant'
 */
#define rtCP_Constant_Value_ljo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lcj
 * Referenced by: '<S3772>/Constant'
 */
#define rtCP_Constant_Value_lcj        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3579>/Constant1'
 */
#define rtCP_Constant1_Value_lz        (0.0F)

/* Expression: single(0.01)
 * Referenced by: '<S3579>/Constant2'
 */
#define rtCP_Constant2_Value_p4        (0.01F)

/* Expression: single(0)
 * Referenced by: '<S3579>/Constant3'
 */
#define rtCP_Constant3_Value_g4        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3579>/Constant4'
 */
#define rtCP_Constant4_Value_di        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3773>/Constant5'
 */
#define rtCP_Constant5_Value_i2        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3774>/Constant5'
 */
#define rtCP_Constant5_Value_mzv       (1.0E+10F)

/* Expression: single(0.5)
 * Referenced by: '<S3775>/Constant'
 */
#define rtCP_Constant_Value_lkf        (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S3776>/Constant'
 */
#define rtCP_Constant_Value_ehp        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_p5j
 * Referenced by: '<S3784>/Constant'
 */
#define rtCP_Constant_Value_p5j        (1.6F)

/* Computed Parameter: rtCP_Constant_Value_mjn
 * Referenced by: '<S3785>/Constant'
 */
#define rtCP_Constant_Value_mjn        (0.6F)

/* Expression: single(1)
 * Referenced by: '<S3805>/CosHeading'
 */
#define rtCP_CosHeading_Value_m        (1.0F)

/* Expression: single(0.01)
 * Referenced by: '<S3805>/LengthSideLat'
 */
#define rtCP_LengthSideLat_Value_l     (0.01F)

/* Expression: single(0.01)
 * Referenced by: '<S3805>/LengthSideLgt'
 */
#define rtCP_LengthSideLgt_Value_h     (0.01F)

/* Expression: single(0)
 * Referenced by: '<S3805>/RotationAngle'
 */
#define rtCP_RotationAngle_Value_g     (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3805>/SinHeading'
 */
#define rtCP_SinHeading_Value_b        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bs3
 * Referenced by: '<S3827>/Constant'
 */
#define rtCP_Constant_Value_bs3        (0.0F)

/* Expression: single(2)
 * Referenced by: '<S2090>/Constant13'
 */
#define rtCP_Constant13_Value_js       (2.0F)

/* Computed Parameter: rtCP_Constant20_Value_m
 * Referenced by: '<S2090>/Constant20'
 */
#define rtCP_Constant20_Value_m        (1.0F)

/* Expression: single(0)
 * Referenced by: '<S2090>/Constant32'
 */
#define rtCP_Constant32_Value_n        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2090>/Constant33'
 */
#define rtCP_Constant33_Value_o        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2090>/Constant34'
 */
#define rtCP_Constant34_Value_m        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2090>/Constant35'
 */
#define rtCP_Constant35_Value_d        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2090>/Constant36'
 */
#define rtCP_Constant36_Value_f        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2090>/Constant9'
 */
#define rtCP_Constant9_Value_d         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2090>/Constant_2'
 */
#define rtCP_Constant_2_Value_fl       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2090>/Constant_25'
 */
#define rtCP_Constant_25_Value_p       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3794>/Constant4'
 */
#define rtCP_Constant4_Value_no        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3855>/Constant5'
 */
#define rtCP_Constant5_Value_f5        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3856>/Constant5'
 */
#define rtCP_Constant5_Value_al2       (1.0E+10F)

/* Computed Parameter: rtCP_Constant_Value_jv2
 * Referenced by: '<S3878>/Constant'
 */
#define rtCP_Constant_Value_jv2        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bw3
 * Referenced by: '<S3879>/Constant'
 */
#define rtCP_Constant_Value_bw3        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_k3
 * Referenced by: '<S3880>/LimitSource'
 */
#define rtCP_LimitSource_Value_k3      (0.01F)

/* Computed Parameter: rtCP_Zero_Value_n
 * Referenced by: '<S3871>/Zero'
 */
#define rtCP_Zero_Value_n              (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_f5
 * Referenced by: '<S3863>/Constant3'
 */
#define rtCP_Constant3_Value_f5        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S3863>/OffsMinForCllsnRednByBrkgActv1'
 */
#define rtCP_OffsMinForCllsnRednByBrkgActv1_Value_n (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_im
 * Referenced by: '<S3875>/Constant3'
 */
#define rtCP_Constant3_Value_im        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jof
 * Referenced by: '<S3881>/Constant'
 */
#define rtCP_Constant_Value_jof        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_a20
 * Referenced by: '<S3864>/Constant'
 */
#define rtCP_Constant_Value_a20        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dq
 * Referenced by: '<S3886>/Constant'
 */
#define rtCP_Constant_Value_dq         (4.0F)

/* Computed Parameter: rtCP_Constant_Value_cp4
 * Referenced by: '<S3866>/Constant'
 */
#define rtCP_Constant_Value_cp4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bsw
 * Referenced by: '<S3889>/Constant'
 */
#define rtCP_Constant_Value_bsw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_km
 * Referenced by: '<S3890>/Constant'
 */
#define rtCP_Constant_Value_km         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nua
 * Referenced by: '<S3891>/Constant'
 */
#define rtCP_Constant_Value_nua        (0.0F)

/* Expression: single(-0.5)
 * Referenced by: '<S3891>/Constant1'
 */
#define rtCP_Constant1_Value_bpc       (-0.5F)

/* Computed Parameter: rtCP_Constant_Value_fw
 * Referenced by: '<S3902>/Constant'
 */
#define rtCP_Constant_Value_fw         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_npl
 * Referenced by: '<S3903>/Constant'
 */
#define rtCP_Constant_Value_npl        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aa
 * Referenced by: '<S3904>/Constant'
 */
#define rtCP_Constant_Value_aa         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ir
 * Referenced by: '<S3907>/Constant'
 */
#define rtCP_Constant_Value_ir         (0.6F)

/* Computed Parameter: rtCP_Constant_Value_lpv
 * Referenced by: '<S3905>/Constant'
 */
#define rtCP_Constant_Value_lpv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cdo
 * Referenced by: '<S3920>/Constant'
 */
#define rtCP_Constant_Value_cdo        (4.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3922>/Constant5'
 */
#define rtCP_Constant5_Value_fr        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3923>/Constant5'
 */
#define rtCP_Constant5_Value_ep        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_fzb
 * Referenced by: '<S3924>/LimitSource'
 */
#define rtCP_LimitSource_Value_fzb     (1.0E-5F)

/* Computed Parameter: rtCP_Constant_Value_jov
 * Referenced by: '<S3932>/Constant'
 */
#define rtCP_Constant_Value_jov        (0.2F)

/* Computed Parameter: rtCP_Constant_Value_oak
 * Referenced by: '<S3933>/Constant'
 */
#define rtCP_Constant_Value_oak        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_chc
 * Referenced by: '<S3934>/Constant'
 */
#define rtCP_Constant_Value_chc        (1.0F)

/* Computed Parameter: rtCP_Constant_Value_ja0
 * Referenced by: '<S3936>/Constant'
 */
#define rtCP_Constant_Value_ja0        (1.2F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3948>/Constant5'
 */
#define rtCP_Constant5_Value_ji        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S3949>/Constant5'
 */
#define rtCP_Constant5_Value_iyi       (1.0E+10F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S4013>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value_p (0.01F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S4013>/LengthSideLgtNoLength1'
 */
#define rtCP_LengthSideLgtNoLength1_Value_l (0.01F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4059>/Constant5'
 */
#define rtCP_Constant5_Value_on        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S4060>/Constant5'
 */
#define rtCP_Constant5_Value_po        (1.0E+10F)

/* Computed Parameter: rtCP_LimitSource_Value_b5
 * Referenced by: '<S4061>/LimitSource'
 */
#define rtCP_LimitSource_Value_b5      (1.0E-5F)

/* Computed Parameter: rtCP_Constant1_Value_dt
 * Referenced by: '<S4081>/Constant1'
 */
#define rtCP_Constant1_Value_dt        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_hx
 * Referenced by: '<S4081>/Constant2'
 */
#define rtCP_Constant2_Value_hx        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_p1
 * Referenced by: '<S4081>/Constant3'
 */
#define rtCP_Constant3_Value_p1        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_a2
 * Referenced by: '<S4081>/Constant4'
 */
#define rtCP_Constant4_Value_a2        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oz2
 * Referenced by: '<S4085>/Constant'
 */
#define rtCP_Constant_Value_oz2        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_gld
 * Referenced by: '<S4082>/Constant1'
 */
#define rtCP_Constant1_Value_gld       (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_lay
 * Referenced by: '<S4082>/Constant2'
 */
#define rtCP_Constant2_Value_lay       (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_p2
 * Referenced by: '<S4082>/Constant3'
 */
#define rtCP_Constant3_Value_p2        (0.0F)

/* Computed Parameter: rtCP_Constant8_Value_ou
 * Referenced by: '<S4082>/Constant8'
 */
#define rtCP_Constant8_Value_ou        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oq4
 * Referenced by: '<S4087>/Constant'
 */
#define rtCP_Constant_Value_oq4        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_eh
 * Referenced by: '<S4083>/Constant1'
 */
#define rtCP_Constant1_Value_eh        (0.0F)

/* Computed Parameter: rtCP_Constant2_Value_m4
 * Referenced by: '<S4083>/Constant2'
 */
#define rtCP_Constant2_Value_m4        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_hc
 * Referenced by: '<S4083>/Constant3'
 */
#define rtCP_Constant3_Value_hc        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_e
 * Referenced by: '<S4083>/Constant4'
 */
#define rtCP_Constant4_Value_e         (0.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S4101>/Constant_1'
 */
#define rtCP_Constant_1_Value_g        (1.57079637F)

/* Computed Parameter: rtCP_Constant_2_Value_jx
 * Referenced by: '<S4101>/Constant_2'
 */
#define rtCP_Constant_2_Value_jx       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pzq
 * Referenced by: '<S4461>/Constant'
 */
#define rtCP_Constant_Value_pzq        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jyb
 * Referenced by: '<S4462>/Constant'
 */
#define rtCP_Constant_Value_jyb        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_c4
 * Referenced by: '<S4463>/LimitSource'
 */
#define rtCP_LimitSource_Value_c4      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_hch
 * Referenced by: '<S4464>/Constant'
 */
#define rtCP_Constant_Value_hch        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_k0r
 * Referenced by: '<S4465>/Constant'
 */
#define rtCP_Constant_Value_k0r        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oya
 * Referenced by: '<S4466>/Constant'
 */
#define rtCP_Constant_Value_oya        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hxv
 * Referenced by: '<S4467>/Constant'
 */
#define rtCP_Constant_Value_hxv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_iab
 * Referenced by: '<S4468>/Constant'
 */
#define rtCP_Constant_Value_iab        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fo5
 * Referenced by: '<S4469>/Constant'
 */
#define rtCP_Constant_Value_fo5        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dlec
 * Referenced by: '<S4470>/Constant'
 */
#define rtCP_Constant_Value_dlec       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4460>/Constant'
 */
#define rtCP_Constant_Value_oim        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4460>/Constant1'
 */
#define rtCP_Constant1_Value_ph        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ckn
 * Referenced by: '<S4476>/Constant'
 */
#define rtCP_Constant_Value_ckn        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cof
 * Referenced by: '<S4477>/Constant'
 */
#define rtCP_Constant_Value_cof        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_cg
 * Referenced by: '<S4478>/LimitSource'
 */
#define rtCP_LimitSource_Value_cg      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_h42
 * Referenced by: '<S4479>/Constant'
 */
#define rtCP_Constant_Value_h42        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jnj
 * Referenced by: '<S4480>/Constant'
 */
#define rtCP_Constant_Value_jnj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ivp
 * Referenced by: '<S4481>/Constant'
 */
#define rtCP_Constant_Value_ivp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cjo
 * Referenced by: '<S4482>/Constant'
 */
#define rtCP_Constant_Value_cjo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dud
 * Referenced by: '<S4483>/Constant'
 */
#define rtCP_Constant_Value_dud        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dod
 * Referenced by: '<S4484>/Constant'
 */
#define rtCP_Constant_Value_dod        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hxu
 * Referenced by: '<S4485>/Constant'
 */
#define rtCP_Constant_Value_hxu        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4475>/Constant'
 */
#define rtCP_Constant_Value_afi        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4475>/Constant1'
 */
#define rtCP_Constant1_Value_lr        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mpj
 * Referenced by: '<S4489>/Constant'
 */
#define rtCP_Constant_Value_mpj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dor
 * Referenced by: '<S4490>/Constant'
 */
#define rtCP_Constant_Value_dor        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ljfz
 * Referenced by: '<S4491>/Constant'
 */
#define rtCP_Constant_Value_ljfz       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_frb
 * Referenced by: '<S4492>/Constant'
 */
#define rtCP_Constant_Value_frb        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_btd
 * Referenced by: '<S4493>/Constant'
 */
#define rtCP_Constant_Value_btd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i03
 * Referenced by: '<S4494>/Constant'
 */
#define rtCP_Constant_Value_i03        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_adv
 * Referenced by: '<S4495>/Constant'
 */
#define rtCP_Constant_Value_adv        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4488>/Constant'
 */
#define rtCP_Constant_Value_p3u        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4488>/Constant1'
 */
#define rtCP_Constant1_Value_mz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_irk
 * Referenced by: '<S4499>/Constant'
 */
#define rtCP_Constant_Value_irk        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jvj
 * Referenced by: '<S4500>/Constant'
 */
#define rtCP_Constant_Value_jvj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ak0
 * Referenced by: '<S4501>/Constant'
 */
#define rtCP_Constant_Value_ak0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_l4h
 * Referenced by: '<S4502>/Constant'
 */
#define rtCP_Constant_Value_l4h        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_eh2
 * Referenced by: '<S4503>/Constant'
 */
#define rtCP_Constant_Value_eh2        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_puf
 * Referenced by: '<S4504>/Constant'
 */
#define rtCP_Constant_Value_puf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fcx
 * Referenced by: '<S4505>/Constant'
 */
#define rtCP_Constant_Value_fcx        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4498>/Constant'
 */
#define rtCP_Constant_Value_kgur       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4498>/Constant1'
 */
#define rtCP_Constant1_Value_euv       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lnhq
 * Referenced by: '<S4509>/Constant'
 */
#define rtCP_Constant_Value_lnhq       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cqd
 * Referenced by: '<S4510>/Constant'
 */
#define rtCP_Constant_Value_cqd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gut
 * Referenced by: '<S4511>/Constant'
 */
#define rtCP_Constant_Value_gut        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aj0
 * Referenced by: '<S4512>/Constant'
 */
#define rtCP_Constant_Value_aj0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i0a
 * Referenced by: '<S4513>/Constant'
 */
#define rtCP_Constant_Value_i0a        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_btj
 * Referenced by: '<S4514>/Constant'
 */
#define rtCP_Constant_Value_btj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i5z
 * Referenced by: '<S4515>/Constant'
 */
#define rtCP_Constant_Value_i5z        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4508>/Constant'
 */
#define rtCP_Constant_Value_ke0        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4508>/Constant1'
 */
#define rtCP_Constant1_Value_gz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lh
 * Referenced by: '<S4519>/Constant'
 */
#define rtCP_Constant_Value_lh         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_j3f
 * Referenced by: '<S4520>/Constant'
 */
#define rtCP_Constant_Value_j3f        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_aei
 * Referenced by: '<S4521>/Constant'
 */
#define rtCP_Constant_Value_aei        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nq3
 * Referenced by: '<S4522>/Constant'
 */
#define rtCP_Constant_Value_nq3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cc
 * Referenced by: '<S4523>/Constant'
 */
#define rtCP_Constant_Value_cc         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ca
 * Referenced by: '<S4524>/Constant'
 */
#define rtCP_Constant_Value_ca         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dzip
 * Referenced by: '<S4525>/Constant'
 */
#define rtCP_Constant_Value_dzip       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4518>/Constant'
 */
#define rtCP_Constant_Value_i4m        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S4518>/Constant1'
 */
#define rtCP_Constant1_Value_imv       (0.0F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S4097>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value_b (0.01F)

/* Expression: single(pi/2)
 * Referenced by: '<S4531>/Constant'
 */
#define rtCP_Constant_Value_cth        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S4540>/Constant'
 */
#define rtCP_Constant_Value_ns         (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S4549>/Constant'
 */
#define rtCP_Constant_Value_hnk        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S4558>/Constant'
 */
#define rtCP_Constant_Value_bmm        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S4567>/Constant'
 */
#define rtCP_Constant_Value_kwz        (1.57079637F)

/* Computed Parameter: rtCP_Constant_Value_n1i
 * Referenced by: '<S5027>/Constant'
 */
#define rtCP_Constant_Value_n1i        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hzvb
 * Referenced by: '<S5028>/Constant'
 */
#define rtCP_Constant_Value_hzvb       (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_i4
 * Referenced by: '<S5029>/LimitSource'
 */
#define rtCP_LimitSource_Value_i4      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_coo
 * Referenced by: '<S5030>/Constant'
 */
#define rtCP_Constant_Value_coo        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gd4
 * Referenced by: '<S5031>/Constant'
 */
#define rtCP_Constant_Value_gd4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_pyg
 * Referenced by: '<S5032>/Constant'
 */
#define rtCP_Constant_Value_pyg        (-0.41F)

/* Computed Parameter: rtCP_Constant_Value_arb
 * Referenced by: '<S5033>/Constant'
 */
#define rtCP_Constant_Value_arb        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jtw
 * Referenced by: '<S5034>/Constant'
 */
#define rtCP_Constant_Value_jtw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ib0u
 * Referenced by: '<S5035>/Constant'
 */
#define rtCP_Constant_Value_ib0u       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jva
 * Referenced by: '<S5036>/Constant'
 */
#define rtCP_Constant_Value_jva        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5026>/Constant'
 */
#define rtCP_Constant_Value_chn        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5026>/Constant1'
 */
#define rtCP_Constant1_Value_nt2       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_me4
 * Referenced by: '<S5042>/Constant'
 */
#define rtCP_Constant_Value_me4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_lng
 * Referenced by: '<S5043>/Constant'
 */
#define rtCP_Constant_Value_lng        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_bh
 * Referenced by: '<S5044>/LimitSource'
 */
#define rtCP_LimitSource_Value_bh      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ewp
 * Referenced by: '<S5045>/Constant'
 */
#define rtCP_Constant_Value_ewp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jow
 * Referenced by: '<S5046>/Constant'
 */
#define rtCP_Constant_Value_jow        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dfe
 * Referenced by: '<S5047>/Constant'
 */
#define rtCP_Constant_Value_dfe        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ap4
 * Referenced by: '<S5048>/Constant'
 */
#define rtCP_Constant_Value_ap4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gw
 * Referenced by: '<S5049>/Constant'
 */
#define rtCP_Constant_Value_gw         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_bsm
 * Referenced by: '<S5050>/Constant'
 */
#define rtCP_Constant_Value_bsm        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_agp
 * Referenced by: '<S5051>/Constant'
 */
#define rtCP_Constant_Value_agp        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5041>/Constant'
 */
#define rtCP_Constant_Value_e4i        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5041>/Constant1'
 */
#define rtCP_Constant1_Value_fl5       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kwwh
 * Referenced by: '<S5055>/Constant'
 */
#define rtCP_Constant_Value_kwwh       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_njf
 * Referenced by: '<S5056>/Constant'
 */
#define rtCP_Constant_Value_njf        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nfq
 * Referenced by: '<S5057>/Constant'
 */
#define rtCP_Constant_Value_nfq        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gz
 * Referenced by: '<S5058>/Constant'
 */
#define rtCP_Constant_Value_gz         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fq3
 * Referenced by: '<S5059>/Constant'
 */
#define rtCP_Constant_Value_fq3        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dpk
 * Referenced by: '<S5060>/Constant'
 */
#define rtCP_Constant_Value_dpk        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_csv
 * Referenced by: '<S5061>/Constant'
 */
#define rtCP_Constant_Value_csv        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5054>/Constant'
 */
#define rtCP_Constant_Value_eyk        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5054>/Constant1'
 */
#define rtCP_Constant1_Value_e4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dxt
 * Referenced by: '<S5065>/Constant'
 */
#define rtCP_Constant_Value_dxt        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ioe
 * Referenced by: '<S5066>/Constant'
 */
#define rtCP_Constant_Value_ioe        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cf
 * Referenced by: '<S5067>/Constant'
 */
#define rtCP_Constant_Value_cf         (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dh4
 * Referenced by: '<S5068>/Constant'
 */
#define rtCP_Constant_Value_dh4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nzi
 * Referenced by: '<S5069>/Constant'
 */
#define rtCP_Constant_Value_nzi        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_nch
 * Referenced by: '<S5070>/Constant'
 */
#define rtCP_Constant_Value_nch        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kzg
 * Referenced by: '<S5071>/Constant'
 */
#define rtCP_Constant_Value_kzg        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5064>/Constant'
 */
#define rtCP_Constant_Value_lkc        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5064>/Constant1'
 */
#define rtCP_Constant1_Value_oz        (0.0F)

/* Expression: LengthSideLgtNoLength
 * Referenced by: '<S4655>/LengthSideLgtNoLength'
 */
#define rtCP_LengthSideLgtNoLength_Value_c (0.01F)

/* Expression: single(2)
 * Referenced by: '<S5097>/Constant'
 */
#define rtCP_Constant_Value_afe        (2.0F)

/* Expression: single(pi/2)
 * Referenced by: '<S5106>/Constant'
 */
#define rtCP_Constant_Value_k2n        (1.57079637F)

/* Expression: single(pi/2)
 * Referenced by: '<S5115>/Constant'
 */
#define rtCP_Constant_Value_hpe        (1.57079637F)

/* Expression: single(0)
 * Referenced by: '<S5258>/Constant'
 */
#define rtCP_Constant_Value_dlp        (0.0F)

/* Expression: single(0.2)
 * Referenced by: '<S5259>/Constant'
 */
#define rtCP_Constant_Value_l3u        (0.2F)

/* Computed Parameter: rtCP_Constant_Value_ezg
 * Referenced by: '<S5341>/Constant'
 */
#define rtCP_Constant_Value_ezg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_kfk
 * Referenced by: '<S5342>/Constant'
 */
#define rtCP_Constant_Value_kfk        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_ms
 * Referenced by: '<S5343>/LimitSource'
 */
#define rtCP_LimitSource_Value_ms      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_ehr
 * Referenced by: '<S5350>/Constant'
 */
#define rtCP_Constant_Value_ehr        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_km0
 * Referenced by: '<S5351>/Constant'
 */
#define rtCP_Constant_Value_km0        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_evu
 * Referenced by: '<S5352>/Constant'
 */
#define rtCP_Constant_Value_evu        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_jro
 * Referenced by: '<S5353>/Constant'
 */
#define rtCP_Constant_Value_jro        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hu1
 * Referenced by: '<S5430>/Constant'
 */
#define rtCP_Constant_Value_hu1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_dhq
 * Referenced by: '<S5431>/Constant'
 */
#define rtCP_Constant_Value_dhq        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_do
 * Referenced by: '<S5432>/LimitSource'
 */
#define rtCP_LimitSource_Value_do      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_fbp
 * Referenced by: '<S5439>/Constant'
 */
#define rtCP_Constant_Value_fbp        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fwx
 * Referenced by: '<S5440>/Constant'
 */
#define rtCP_Constant_Value_fwx        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_myj
 * Referenced by: '<S5441>/Constant'
 */
#define rtCP_Constant_Value_myj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_hpa
 * Referenced by: '<S5442>/Constant'
 */
#define rtCP_Constant_Value_hpa        (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_nj
 * Referenced by: '<S5449>/LimitSource'
 */
#define rtCP_LimitSource_Value_nj      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_b4t
 * Referenced by: '<S5450>/LimitSource'
 */
#define rtCP_LimitSource_Value_b4t     (0.01F)

/* Computed Parameter: rtCP_Constant_Value_iuv
 * Referenced by: '<S5451>/Constant'
 */
#define rtCP_Constant_Value_iuv        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_g5
 * Referenced by: '<S5452>/Constant'
 */
#define rtCP_Constant_Value_g5         (0.0F)

/* Computed Parameter: rtCP_LimitSource_Value_j2
 * Referenced by: '<S5453>/LimitSource'
 */
#define rtCP_LimitSource_Value_j2      (0.01F)

/* Computed Parameter: rtCP_LimitSource_Value_eg
 * Referenced by: '<S5454>/LimitSource'
 */
#define rtCP_LimitSource_Value_eg      (0.01F)

/* Computed Parameter: rtCP_Constant_Value_doj
 * Referenced by: '<S5455>/Constant'
 */
#define rtCP_Constant_Value_doj        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_b5y
 * Referenced by: '<S5456>/Constant'
 */
#define rtCP_Constant_Value_b5y        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fyw
 * Referenced by: '<S5457>/Constant'
 */
#define rtCP_Constant_Value_fyw        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_gc4
 * Referenced by: '<S5458>/Constant'
 */
#define rtCP_Constant_Value_gc4        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ci1
 * Referenced by: '<S5459>/Constant'
 */
#define rtCP_Constant_Value_ci1        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_i2x
 * Referenced by: '<S5460>/Constant'
 */
#define rtCP_Constant_Value_i2x        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5267>/Constant1'
 */
#define rtCP_Constant1_Value_pa        (0.0F)

/* Expression: single(0.01)
 * Referenced by: '<S5267>/Constant2'
 */
#define rtCP_Constant2_Value_d5        (0.01F)

/* Expression: single(0)
 * Referenced by: '<S5267>/Constant3'
 */
#define rtCP_Constant3_Value_gh        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5267>/Constant4'
 */
#define rtCP_Constant4_Value_ez        (0.0F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S5461>/Constant5'
 */
#define rtCP_Constant5_Value_fl        (1.0E+10F)

/* Expression: MaxOutpValueFromSafeDivInAsyEvlrCritEve
 * Referenced by: '<S5462>/Constant5'
 */
#define rtCP_Constant5_Value_ncq       (1.0E+10F)

/* Expression: single(0.5)
 * Referenced by: '<S5463>/Constant'
 */
#define rtCP_Constant_Value_men        (0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S5464>/Constant'
 */
#define rtCP_Constant_Value_ot1        (0.5F)

/* Computed Parameter: rtCP_Constant_Value_eji
 * Referenced by: '<S5472>/Constant'
 */
#define rtCP_Constant_Value_eji        (1.6F)

/* Computed Parameter: rtCP_Constant_Value_pss
 * Referenced by: '<S5473>/Constant'
 */
#define rtCP_Constant_Value_pss        (0.6F)

/* Expression: single(0)
 * Referenced by: '<S5476>/Constant'
 */
#define rtCP_Constant_Value_bi4        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5476>/Constant1'
 */
#define rtCP_Constant1_Value_py        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5476>/Constant50'
 */
#define rtCP_Constant50_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5476>/Constant51'
 */
#define rtCP_Constant51_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5476>/Constant52'
 */
#define rtCP_Constant52_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5476>/Constant53'
 */
#define rtCP_Constant53_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5476>/Constant54'
 */
#define rtCP_Constant54_Value          (0.0F)

/* Expression: single(1)
 * Referenced by: '<S5476>/Constant61'
 */
#define rtCP_Constant61_Value          (1.0F)

/* Expression: single(0)
 * Referenced by: '<S5477>/Constant'
 */
#define rtCP_Constant_Value_ntt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5477>/Constant1'
 */
#define rtCP_Constant1_Value_ocb       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5477>/Constant50'
 */
#define rtCP_Constant50_Value_i        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5477>/Constant51'
 */
#define rtCP_Constant51_Value_c        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5477>/Constant52'
 */
#define rtCP_Constant52_Value_l        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5477>/Constant53'
 */
#define rtCP_Constant53_Value_h        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5477>/Constant54'
 */
#define rtCP_Constant54_Value_i        (0.0F)

/* Expression: single(1)
 * Referenced by: '<S5477>/Constant61'
 */
#define rtCP_Constant61_Value_k        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S5506>/Constant'
 */
#define rtCP_Constant_Value_fp4        (1.0F)

/* Expression: single(0)
 * Referenced by: '<S5506>/Constant1'
 */
#define rtCP_Constant1_Value_dl        (0.0F)

/* Expression: single(1)
 * Referenced by: '<S5525>/Constant1'
 */
#define rtCP_Constant1_Value_fe        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S5526>/Constant'
 */
#define rtCP_Constant_Value_lio        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S5548>/Constant1'
 */
#define rtCP_Constant1_Value_f2        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S5549>/Constant'
 */
#define rtCP_Constant_Value_jbb        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S5519>/Constant'
 */
#define rtCP_Constant_Value_erj        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S5520>/Constant'
 */
#define rtCP_Constant_Value_hi         (1.0F)

/* Computed Parameter: rtCP_Constant_Value_e4j
 * Referenced by: '<S5587>/Constant'
 */
#define rtCP_Constant_Value_e4j        (12.0F)

/* Computed Parameter: rtCP_Constant_Value_c2k
 * Referenced by: '<S5588>/Constant'
 */
#define rtCP_Constant_Value_c2k        (3.0F)

/* Computed Parameter: rtCP_Constant_Value_jbr
 * Referenced by: '<S5589>/Constant'
 */
#define rtCP_Constant_Value_jbr        (15.0F)

/* Computed Parameter: rtCP_Constant_Value_iqz
 * Referenced by: '<S5591>/Constant'
 */
#define rtCP_Constant_Value_iqz        (5.0F)

/* Expression: single(0)
 * Referenced by: '<S5600>/Constant3'
 */
#define rtCP_Constant3_Value_gb        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5601>/Constant3'
 */
#define rtCP_Constant3_Value_il        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5602>/Constant3'
 */
#define rtCP_Constant3_Value_kzr       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5603>/Constant3'
 */
#define rtCP_Constant3_Value_k1        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5604>/Constant3'
 */
#define rtCP_Constant3_Value_lu        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5605>/Constant3'
 */
#define rtCP_Constant3_Value_nd        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5606>/Constant3'
 */
#define rtCP_Constant3_Value_l1        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5607>/Constant3'
 */
#define rtCP_Constant3_Value_p1n       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_l5g
 * Referenced by: '<S5610>/Constant'
 */
#define rtCP_Constant_Value_l5g        (0.1F)

/* Expression: single(0)
 * Referenced by: '<S5623>/Constant3'
 */
#define rtCP_Constant3_Value_jm        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ilp
 * Referenced by: '<S5627>/Constant'
 */
#define rtCP_Constant_Value_ilp        (0.0F)

/* Expression: const
 * Referenced by: '<S5628>/Constant'
 */
#define rtCP_Constant_Value_menc       (15.0F)

/* Expression: const
 * Referenced by: '<S5629>/Constant'
 */
#define rtCP_Constant_Value_iju        (10.0F)

/* Expression: const
 * Referenced by: '<S5630>/Constant'
 */
#define rtCP_Constant_Value_mcp        (-15.0F)

/* Computed Parameter: rtCP_Constant_Value_b03
 * Referenced by: '<S5646>/Constant'
 */
#define rtCP_Constant_Value_b03        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5493>/Constant3'
 */
#define rtCP_Constant3_Value_bg        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_ev3
 * Referenced by: '<S5654>/Constant'
 */
#define rtCP_Constant_Value_ev3        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ne
 * Referenced by: '<S5653>/Constant1'
 */
#define rtCP_Constant1_Value_ne        (0.0F)

/* Expression: const
 * Referenced by: '<S5667>/Constant'
 */
#define rtCP_Constant_Value_exk        (8.0F)

/* Expression: const
 * Referenced by: '<S5668>/Constant'
 */
#define rtCP_Constant_Value_je5        (4.0F)

/* Expression: const
 * Referenced by: '<S5669>/Constant'
 */
#define rtCP_Constant_Value_ps2        (8.0F)

/* Expression: const
 * Referenced by: '<S5670>/Constant'
 */
#define rtCP_Constant_Value_ej0        (4.0F)

/* Expression: const
 * Referenced by: '<S5671>/Constant'
 */
#define rtCP_Constant_Value_bnv        (8.0F)

/* Expression: const
 * Referenced by: '<S5672>/Constant'
 */
#define rtCP_Constant_Value_kda        (4.0F)

/* Expression: const
 * Referenced by: '<S5673>/Constant'
 */
#define rtCP_Constant_Value_dhp        (8.0F)

/* Expression: const
 * Referenced by: '<S5674>/Constant'
 */
#define rtCP_Constant_Value_bsf        (4.0F)

/* Expression: const
 * Referenced by: '<S5675>/Constant'
 */
#define rtCP_Constant_Value_nud        (8.0F)

/* Expression: const
 * Referenced by: '<S5676>/Constant'
 */
#define rtCP_Constant_Value_hff        (4.0F)

/* Expression: const
 * Referenced by: '<S5677>/Constant'
 */
#define rtCP_Constant_Value_dz2        (8.0F)

/* Expression: const
 * Referenced by: '<S5678>/Constant'
 */
#define rtCP_Constant_Value_k5r        (4.0F)

/* Computed Parameter: rtCP_Constant_Value_fih
 * Referenced by: '<S5701>/Constant'
 */
#define rtCP_Constant_Value_fih        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_mit
 * Referenced by: '<S5700>/Constant1'
 */
#define rtCP_Constant1_Value_mit       (0.0F)

/* Expression: const
 * Referenced by: '<S5714>/Constant'
 */
#define rtCP_Constant_Value_efr        (8.0F)

/* Expression: const
 * Referenced by: '<S5715>/Constant'
 */
#define rtCP_Constant_Value_crx        (4.0F)

/* Expression: const
 * Referenced by: '<S5716>/Constant'
 */
#define rtCP_Constant_Value_kkr        (8.0F)

/* Expression: const
 * Referenced by: '<S5717>/Constant'
 */
#define rtCP_Constant_Value_mge        (4.0F)

/* Expression: const
 * Referenced by: '<S5718>/Constant'
 */
#define rtCP_Constant_Value_gi3        (8.0F)

/* Expression: const
 * Referenced by: '<S5719>/Constant'
 */
#define rtCP_Constant_Value_fcd        (4.0F)

/* Expression: const
 * Referenced by: '<S5720>/Constant'
 */
#define rtCP_Constant_Value_irl        (8.0F)

/* Expression: const
 * Referenced by: '<S5721>/Constant'
 */
#define rtCP_Constant_Value_ikvv       (4.0F)

/* Expression: const
 * Referenced by: '<S5722>/Constant'
 */
#define rtCP_Constant_Value_kt         (8.0F)

/* Expression: const
 * Referenced by: '<S5723>/Constant'
 */
#define rtCP_Constant_Value_n0y        (4.0F)

/* Expression: const
 * Referenced by: '<S5724>/Constant'
 */
#define rtCP_Constant_Value_hbx        (8.0F)

/* Expression: const
 * Referenced by: '<S5725>/Constant'
 */
#define rtCP_Constant_Value_apr        (4.0F)

/* Expression: single(0)
 * Referenced by: '<S5756>/Constant'
 */
#define rtCP_Constant_Value_km0i       (0.0F)

/* Expression: single(1)
 * Referenced by: '<S5768>/Constant1'
 */
#define rtCP_Constant1_Value_pzo       (1.0F)

/* Expression: single(1)
 * Referenced by: '<S5769>/Constant'
 */
#define rtCP_Constant_Value_nzx        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S5791>/Constant1'
 */
#define rtCP_Constant1_Value_d1n       (1.0F)

/* Expression: single(1)
 * Referenced by: '<S5792>/Constant'
 */
#define rtCP_Constant_Value_pud        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S5765>/Constant'
 */
#define rtCP_Constant_Value_gnw        (1.0F)

/* Expression: single(1)
 * Referenced by: '<S5766>/Constant'
 */
#define rtCP_Constant_Value_bnt        (1.0F)

/* Expression: LoPosValInDrvrStEstimr
 * Referenced by: '<S5759>/Constant'
 */
#define rtCP_Constant_Value_p05        (1.0E-8F)

/* Expression: single(0)
 * Referenced by: '<S5847>/Constant'
 */
#define rtCP_Constant_Value_paw        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5847>/Constant1'
 */
#define rtCP_Constant1_Value_bo        (0.0F)

/* Expression: TiForLenMinOfPathInDrvrStEstimr
 * Referenced by: '<S5849>/NecessaryPredictionTime'
 */
#define rtCP_NecessaryPredictionTime_Value (2.1F)

/* Computed Parameter: rtCP_Constant_Value_mq
 * Referenced by: '<S5857>/Constant'
 */
#define rtCP_Constant_Value_mq         (0.0F)

/* Expression: single(3)
 * Referenced by: '<S5856>/Constant'
 */
#define rtCP_Constant_Value_jbz        (3.0F)

/* Expression: -single(0.5)
 * Referenced by: '<S5856>/Constant1'
 */
#define rtCP_Constant1_Value_dd        (-0.5F)

/* Expression: single(0.5)
 * Referenced by: '<S5856>/Constant3'
 */
#define rtCP_Constant3_Value_do        (0.5F)

/* Expression: single(2)
 * Referenced by: '<S5861>/Constant'
 */
#define rtCP_Constant_Value_drm        (2.0F)

/* Expression: single(3)
 * Referenced by: '<S5861>/Constant1'
 */
#define rtCP_Constant1_Value_nih       (3.0F)

/* Expression: single(6)
 * Referenced by: '<S5861>/Constant2'
 */
#define rtCP_Constant2_Value_kr        (6.0F)

/* Expression: single(2)
 * Referenced by: '<S5861>/Constant3'
 */
#define rtCP_Constant3_Value_d5        (2.0F)

/* Expression: ALatAbsMaxForPathChgInDrvrStEstimr
 * Referenced by: '<S5870>/Constant1'
 */
#define rtCP_Constant1_Value_ae        (1.2F)

/* Computed Parameter: rtCP_Constant3_Value_ga
 * Referenced by: '<S5870>/Constant3'
 */
#define rtCP_Constant3_Value_ga        (0.0F)

/* Computed Parameter: rtCP_Constant4_Value_bz
 * Referenced by: '<S5870>/Constant4'
 */
#define rtCP_Constant4_Value_bz        (0.0F)

/* Expression: MinimumSpeedForLaneFollowingInDrvrStEstimr
 * Referenced by: '<S5871>/MinimumSpeedForLaneFollowing'
 */
#define rtCP_MinimumSpeedForLaneFollowing_Value (9.72222233F)

/* Expression: FrqFctCallInDrvrStEstimr
 * Referenced by: '<S5922>/C_Ts'
 */
#define rtCP_C_Ts_Value                (50.0F)

/* Computed Parameter: rtCP_Constant_Value_otz
 * Referenced by: '<S5962>/Constant'
 */
#define rtCP_Constant_Value_otz        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_cjd
 * Referenced by: '<S5963>/Constant'
 */
#define rtCP_Constant_Value_cjd        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S5978>/Constant2'
 */
#define rtCP_Constant2_Value_el        (0.0F)

/* Expression: FrqFctCallInDrvrStEstimr
 * Referenced by: '<S5989>/CmpFacForALgtCmftInDrvrStEstimr1'
 */
#define rtCP_CmpFacForALgtCmftInDrvrStEstimr1_Value (50.0F)

/* Computed Parameter: rtCP_Constant_Value_iqb
 * Referenced by: '<S5997>/Constant'
 */
#define rtCP_Constant_Value_iqb        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_ju
 * Referenced by: '<S5997>/Constant1'
 */
#define rtCP_Constant1_Value_ju        (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_dk
 * Referenced by: '<S5998>/Constant2'
 */
#define rtCP_Constant2_Value_dk        (1.0F)

/* Computed Parameter: rtCP_Constant4_Value_l5
 * Referenced by: '<S5998>/Constant4'
 */
#define rtCP_Constant4_Value_l5        (0.0F)

/* Computed Parameter: rtCP_Constant1_Value_gv
 * Referenced by: '<S5987>/Constant1'
 */
#define rtCP_Constant1_Value_gv        (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_ny
 * Referenced by: '<S5987>/Constant2'
 */
#define rtCP_Constant2_Value_ny        (1.25F)

/* Computed Parameter: rtCP_Constant6_Value_l5
 * Referenced by: '<S5987>/Constant6'
 */
#define rtCP_Constant6_Value_l5        (1.0F)

/* Expression: PerdFctCallInDrvrStEstimr
 * Referenced by: '<S6037>/updateTime'
 */
#define rtCP_updateTime_Value          (0.02F)

/* Expression: PerdFctCallInDrvrStEstimr
 * Referenced by: '<S6038>/updateTime'
 */
#define rtCP_updateTime_Value_c        (0.02F)

/* Computed Parameter: rtCP_Constant4_Value_du
 * Referenced by: '<S6036>/Constant4'
 */
#define rtCP_Constant4_Value_du        (1.0F)

/* Expression: LoPosValInDrvrStEstimr
 * Referenced by: '<S6048>/LoPosVal'
 */
#define rtCP_LoPosVal_Value            (1.0E-8F)

/* Computed Parameter: rtCP_Constant_Value_ouzr
 * Referenced by: '<S6057>/Constant'
 */
#define rtCP_Constant_Value_ouzr       (0.0F)

/* Computed Parameter: rtCP_Constant_Value_mq3
 * Referenced by: '<S6063>/Constant'
 */
#define rtCP_Constant_Value_mq3        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S2096>/Constant1'
 */
#define rtCP_Constant1_Value_nvl       (0.0F)

/* Expression: single(1)
 * Referenced by: '<S2096>/Constant11'
 */
#define rtCP_Constant11_Value_kx       (1.0F)

/* Expression: single(0)
 * Referenced by: '<S2097>/Constant7'
 */
#define rtCP_Constant7_Value_a4        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6114>/Constant3'
 */
#define rtCP_Constant3_Value_cn        (0.0F)

/* Computed Parameter: rtCP_Constant3_Value_gd
 * Referenced by: '<S6>/Constant3'
 */
#define rtCP_Constant3_Value_gd        (1.0F)

/* Expression: single(0)
 * Referenced by: '<S6115>/Constant3'
 */
#define rtCP_Constant3_Value_gj        (0.0F)

/* Computed Parameter: rtCP_Constant29_Value_d
 * Referenced by: '<S6>/Constant29'
 */
#define rtCP_Constant29_Value_d        (0.0F)

/* Computed Parameter: rtCP_Constant31_Value
 * Referenced by: '<S6>/Constant31'
 */
#define rtCP_Constant31_Value          (0.0F)

/* Computed Parameter: rtCP_Constant42_Value
 * Referenced by: '<S6>/Constant42'
 */
#define rtCP_Constant42_Value          (0.0F)

/* Computed Parameter: rtCP_Constant_Value_fvs
 * Referenced by: '<S6128>/Constant'
 */
#define rtCP_Constant_Value_fvs        (1.0F)

/* Computed Parameter: rtCP_Constant2_Value_jg
 * Referenced by: '<S6128>/Constant2'
 */
#define rtCP_Constant2_Value_jg        (-1.0F)

/* Expression: single(0)
 * Referenced by: '<S6141>/Constant'
 */
#define rtCP_Constant_Value_pef        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6150>/Constant'
 */
#define rtCP_Constant_Value_d0h        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6150>/Constant3'
 */
#define rtCP_Constant3_Value_g2        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6153>/Constant3'
 */
#define rtCP_Constant3_Value_hj        (0.0F)

/* Expression: C_ZERO_SINGLE
 * Referenced by: '<S6142>/Constant'
 */
#define rtCP_Constant_Value_kdh        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6142>/Constant20'
 */
#define rtCP_Constant20_Value_j        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6142>/Constant21'
 */
#define rtCP_Constant21_Value_g        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6142>/Constant22'
 */
#define rtCP_Constant22_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6142>/Constant24'
 */
#define rtCP_Constant24_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6142>/Constant9'
 */
#define rtCP_Constant9_Value_n         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6143>/Constant30'
 */
#define rtCP_Constant30_Value          (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6143>/Constant31'
 */
#define rtCP_Constant31_Value_m        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6143>/Constant32'
 */
#define rtCP_Constant32_Value_j        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6143>/Constant5'
 */
#define rtCP_Constant5_Value_jt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6143>/Constant6'
 */
#define rtCP_Constant6_Value_j         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6239>/Constant3'
 */
#define rtCP_Constant3_Value_bt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6240>/Constant3'
 */
#define rtCP_Constant3_Value_io        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6241>/Constant3'
 */
#define rtCP_Constant3_Value_gr        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6242>/Constant3'
 */
#define rtCP_Constant3_Value_dx        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6243>/Constant3'
 */
#define rtCP_Constant3_Value_mi        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6244>/Constant3'
 */
#define rtCP_Constant3_Value_ff        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6245>/Constant3'
 */
#define rtCP_Constant3_Value_kc        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6246>/Constant3'
 */
#define rtCP_Constant3_Value_at        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6247>/Constant3'
 */
#define rtCP_Constant3_Value_oz        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6248>/Constant3'
 */
#define rtCP_Constant3_Value_ob        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6249>/Constant3'
 */
#define rtCP_Constant3_Value_hw        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6250>/Constant3'
 */
#define rtCP_Constant3_Value_m3        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6251>/Constant3'
 */
#define rtCP_Constant3_Value_oo        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6252>/Constant3'
 */
#define rtCP_Constant3_Value_hs        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6253>/Constant3'
 */
#define rtCP_Constant3_Value_p2i       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6254>/Constant3'
 */
#define rtCP_Constant3_Value_kgx       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6255>/Constant3'
 */
#define rtCP_Constant3_Value_h5        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6256>/Constant3'
 */
#define rtCP_Constant3_Value_p3z       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6257>/Constant3'
 */
#define rtCP_Constant3_Value_gq        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6258>/Constant3'
 */
#define rtCP_Constant3_Value_jx        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6259>/Constant3'
 */
#define rtCP_Constant3_Value_or        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6273>/Constant3'
 */
#define rtCP_Constant3_Value_df        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6274>/Constant3'
 */
#define rtCP_Constant3_Value_iy        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6275>/Constant3'
 */
#define rtCP_Constant3_Value_nq        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6276>/Constant3'
 */
#define rtCP_Constant3_Value_m4        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6277>/Constant3'
 */
#define rtCP_Constant3_Value_e         (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6278>/Constant3'
 */
#define rtCP_Constant3_Value_fa        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6279>/Constant3'
 */
#define rtCP_Constant3_Value_cw        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6280>/Constant3'
 */
#define rtCP_Constant3_Value_ip        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6282>/Constant3'
 */
#define rtCP_Constant3_Value_dfg       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6283>/Constant3'
 */
#define rtCP_Constant3_Value_b0        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6284>/Constant3'
 */
#define rtCP_Constant3_Value_kt        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6281>/Constant3'
 */
#define rtCP_Constant3_Value_cd        (0.0F)

/* Computed Parameter: rtCP_Constant_Value_oia
 * Referenced by: '<S6295>/Constant'
 */
#define rtCP_Constant_Value_oia        (2.0F)

/* Computed Parameter: rtCP_Constant_Value_dbv
 * Referenced by: '<S6310>/Constant'
 */
#define rtCP_Constant_Value_dbv        (3.0F)

/* Computed Parameter: rtCP_Constant_Value_ex5
 * Referenced by: '<S6311>/Constant'
 */
#define rtCP_Constant_Value_ex5        (0.5F)

/* Expression: single(0)
 * Referenced by: '<S6312>/Constant3'
 */
#define rtCP_Constant3_Value_nv        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6298>/Constant3'
 */
#define rtCP_Constant3_Value_er        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6299>/Constant3'
 */
#define rtCP_Constant3_Value_jh        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6300>/Constant3'
 */
#define rtCP_Constant3_Value_pxo       (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6301>/Constant3'
 */
#define rtCP_Constant3_Value_k5        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6302>/Constant3'
 */
#define rtCP_Constant3_Value_if        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6303>/Constant3'
 */
#define rtCP_Constant3_Value_n1        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6304>/Constant3'
 */
#define rtCP_Constant3_Value_gn        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6305>/Constant3'
 */
#define rtCP_Constant3_Value_i1        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6306>/Constant3'
 */
#define rtCP_Constant3_Value_be        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6307>/Constant3'
 */
#define rtCP_Constant3_Value_gg        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6308>/Constant3'
 */
#define rtCP_Constant3_Value_fn        (0.0F)

/* Expression: single(0)
 * Referenced by: '<S6309>/Constant3'
 */
#define rtCP_Constant3_Value_jt        (0.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_n
 * Referenced by: '<S5519>/Saturation'
 */
#define rtCP_Saturation_UpperSat_n     (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_oe
 * Referenced by: '<S5519>/Saturation'
 */
#define rtCP_Saturation_LowerSat_oe    (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_gvl
 * Referenced by: '<S5491>/Gain'
 */
#define rtCP_Gain_Gain_gvl             (0.5F)

/* Expression: single(pi/180)
 * Referenced by: '<S5489>/Gain'
 */
#define rtCP_Gain_Gain_nz              (0.0174532924F)

/* Expression: single(0.3)
 * Referenced by: '<S5506>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_i    (0.3F)

/* Expression: single(-0.3)
 * Referenced by: '<S5506>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_bn   (-0.3F)

/* Computed Parameter: rtCP_Saturation_UpperSat_l4
 * Referenced by: '<S5520>/Saturation'
 */
#define rtCP_Saturation_UpperSat_l4    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_hs
 * Referenced by: '<S5520>/Saturation'
 */
#define rtCP_Saturation_LowerSat_hs    (0.0F)

/* Expression: single(pi/180)
 * Referenced by: '<S5489>/Gain1'
 */
#define rtCP_Gain1_Gain_nu             (0.0174532924F)

/* Expression: single(0.3)
 * Referenced by: '<S5506>/Saturation2'
 */
#define rtCP_Saturation2_UpperSat      (0.3F)

/* Expression: single(-0.3)
 * Referenced by: '<S5506>/Saturation2'
 */
#define rtCP_Saturation2_LowerSat      (-0.3F)

/* Expression: single(3.6)
 * Referenced by: '<S2097>/Gain'
 */
#define rtCP_Gain_Gain_eei             (3.6F)

/* Expression: single(180)
 * Referenced by: '<S5575>/Gain1'
 */
#define rtCP_Gain1_Gain_mi             (180.0F)

/* Expression: single(180)
 * Referenced by: '<S5575>/Gain'
 */
#define rtCP_Gain_Gain_bn4             (180.0F)

/* Expression: single(180)
 * Referenced by: '<S5577>/Gain'
 */
#define rtCP_Gain_Gain_cl              (180.0F)

/* Expression: single(180)
 * Referenced by: '<S5577>/Gain1'
 */
#define rtCP_Gain1_Gain_pz             (180.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_e2
 * Referenced by: '<S3579>/Gain_1'
 */
#define rtCP_Gain_1_Gain_e2            (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_iw
 * Referenced by: '<S3579>/Gain_2'
 */
#define rtCP_Gain_2_Gain_iw            (-1.0F)

/* Expression: single(0.1)
 * Referenced by: '<S5844>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_cj   (0.1F)

/* Expression: single(0.5)
 * Referenced by: '<S5848>/Gain_2'
 */
#define rtCP_Gain_2_Gain_g5            (0.5F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput_i
 * Referenced by: '<S5845>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput_i
 * Referenced by: '<S5845>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput_i
 * Referenced by: '<S5845>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput_i
 * Referenced by: '<S5845>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput_i (0.0F)

/* Expression: single(0.1)
 * Referenced by: '<S5870>/Saturation'
 */
#define rtCP_Saturation_LowerSat_eq    (0.1F)

/* Computed Parameter: rtCP_Time_Gain
 * Referenced by: '<S5871>/Time'
 */
#define rtCP_Time_Gain                 (4.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_ee
 * Referenced by: '<S5765>/Saturation'
 */
#define rtCP_Saturation_UpperSat_ee    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_m
 * Referenced by: '<S5765>/Saturation'
 */
#define rtCP_Saturation_LowerSat_m     (0.0F)

/* Expression: single(0.1)
 * Referenced by: '<S5756>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_e    (0.1F)

/* Expression: single(-0.1)
 * Referenced by: '<S5756>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_cx   (-0.1F)

/* Computed Parameter: rtCP_Saturation_UpperSat_mv
 * Referenced by: '<S5766>/Saturation'
 */
#define rtCP_Saturation_UpperSat_mv    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_n2
 * Referenced by: '<S5766>/Saturation'
 */
#define rtCP_Saturation_LowerSat_n2    (0.0F)

/* Expression: single(0.1)
 * Referenced by: '<S5756>/Saturation'
 */
#define rtCP_Saturation_UpperSat_ea    (0.1F)

/* Expression: single(-0.1)
 * Referenced by: '<S5756>/Saturation'
 */
#define rtCP_Saturation_LowerSat_lm    (-0.1F)

/* Computed Parameter: rtCP_Gain1_Gain_pl
 * Referenced by: '<S2203>/Gain1'
 */
#define rtCP_Gain1_Gain_pl             (-1.0F)

/* Expression: single(3.6)
 * Referenced by: '<S5922>/Gain'
 */
#define rtCP_Gain_Gain_fnf             (3.6F)

/* Computed Parameter: rtCP_Gain_Gain_kum
 * Referenced by: '<S5925>/Gain'
 */
#define rtCP_Gain_Gain_kum             (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_pv
 * Referenced by: '<S5925>/Gain1'
 */
#define rtCP_Gain1_Gain_pv             (0.5F)

/* Computed Parameter: rtCP_Switch_Threshold
 * Referenced by: '<S5925>/Switch'
 */
#define rtCP_Switch_Threshold          (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_pgl
 * Referenced by: '<S2203>/Gain'
 */
#define rtCP_Gain_Gain_pgl             (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_o
 * Referenced by: '<S2202>/Gain1'
 */
#define rtCP_Gain1_Gain_o              (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_a3
 * Referenced by: '<S2202>/Gain2'
 */
#define rtCP_Gain2_Gain_a3             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_pi
 * Referenced by: '<S2202>/Gain'
 */
#define rtCP_Gain_Gain_pi              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_lg
 * Referenced by: '<S2217>/Gain1'
 */
#define rtCP_Gain1_Gain_lg             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_ib
 * Referenced by: '<S2217>/Gain'
 */
#define rtCP_Gain_Gain_ib              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_cp
 * Referenced by: '<S2216>/Gain1'
 */
#define rtCP_Gain1_Gain_cp             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_lk
 * Referenced by: '<S2216>/Gain'
 */
#define rtCP_Gain_Gain_lk              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_pvi
 * Referenced by: '<S2215>/Gain1'
 */
#define rtCP_Gain1_Gain_pvi            (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ob
 * Referenced by: '<S2215>/Gain2'
 */
#define rtCP_Gain2_Gain_ob             (0.5F)

/* Computed Parameter: rtCP_Gain3_Gain_o
 * Referenced by: '<S2215>/Gain3'
 */
#define rtCP_Gain3_Gain_o              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_hi
 * Referenced by: '<S2215>/Gain'
 */
#define rtCP_Gain_Gain_hi              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_gg
 * Referenced by: '<S2214>/Gain1'
 */
#define rtCP_Gain1_Gain_gg             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ml
 * Referenced by: '<S2214>/Gain2'
 */
#define rtCP_Gain2_Gain_ml             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_bw
 * Referenced by: '<S2214>/Gain'
 */
#define rtCP_Gain_Gain_bw              (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_os
 * Referenced by: '<S2178>/Gain2'
 */
#define rtCP_Gain2_Gain_os             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_o0
 * Referenced by: '<S2178>/Gain'
 */
#define rtCP_Gain_Gain_o0              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_a5
 * Referenced by: '<S2178>/Gain1'
 */
#define rtCP_Gain1_Gain_a5             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_d5
 * Referenced by: '<S2176>/Gain2'
 */
#define rtCP_Gain2_Gain_d5             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_la1
 * Referenced by: '<S2176>/Gain'
 */
#define rtCP_Gain_Gain_la1             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_jv
 * Referenced by: '<S2188>/Gain'
 */
#define rtCP_Gain_Gain_jv              (0.5F)

/* Computed Parameter: rtCP_Gain_1_Gain_p1
 * Referenced by: '<S2233>/Gain_1'
 */
#define rtCP_Gain_1_Gain_p1            (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_cn
 * Referenced by: '<S2177>/Gain1'
 */
#define rtCP_Gain1_Gain_cn             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_aq
 * Referenced by: '<S2201>/Gain2'
 */
#define rtCP_Gain2_Gain_aq             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_lke
 * Referenced by: '<S2201>/Gain'
 */
#define rtCP_Gain_Gain_lke             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_bgd
 * Referenced by: '<S776>/Gain'
 */
#define rtCP_Gain_Gain_bgd             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_n42
 * Referenced by: '<S777>/Gain'
 */
#define rtCP_Gain_Gain_n42             (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_lu
 * Referenced by: '<S779>/Gain1'
 */
#define rtCP_Gain1_Gain_lu             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_bx
 * Referenced by: '<S779>/Gain2'
 */
#define rtCP_Gain2_Gain_bx             (0.5F)

/* Expression: single(180/pi)
 * Referenced by: '<S879>/Gain1'
 */
#define rtCP_Gain1_Gain_nf             (57.2957802F)

/* Expression: single(180/pi)
 * Referenced by: '<S879>/Gain2'
 */
#define rtCP_Gain2_Gain_e0             (57.2957802F)

/* Computed Parameter: rtCP_Gain_Gain_bfu
 * Referenced by: '<S769>/Gain'
 */
#define rtCP_Gain_Gain_bfu             (57.2957802F)

/* Computed Parameter: rtCP_Gain1_Gain_l4
 * Referenced by: '<S769>/Gain1'
 */
#define rtCP_Gain1_Gain_l4             (57.2957802F)

/* Computed Parameter: rtCP_Gain_1_Gain_pl
 * Referenced by: '<S5267>/Gain_1'
 */
#define rtCP_Gain_1_Gain_pl            (-1.0F)

/* Computed Parameter: rtCP_Gain_2_Gain_jm
 * Referenced by: '<S5267>/Gain_2'
 */
#define rtCP_Gain_2_Gain_jm            (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ae
 * Referenced by: '<S3891>/Gain1'
 */
#define rtCP_Gain1_Gain_ae             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_j0
 * Referenced by: '<S3891>/Gain'
 */
#define rtCP_Gain_Gain_j0              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_nj
 * Referenced by: '<S3890>/Gain1'
 */
#define rtCP_Gain1_Gain_nj             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_k2
 * Referenced by: '<S3890>/Gain2'
 */
#define rtCP_Gain2_Gain_k2             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_cxi
 * Referenced by: '<S3890>/Gain'
 */
#define rtCP_Gain_Gain_cxi             (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_hh
 * Referenced by: '<S3905>/Gain1'
 */
#define rtCP_Gain1_Gain_hh             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_fx
 * Referenced by: '<S3905>/Gain'
 */
#define rtCP_Gain_Gain_fx              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_d5
 * Referenced by: '<S3904>/Gain1'
 */
#define rtCP_Gain1_Gain_d5             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_i0
 * Referenced by: '<S3904>/Gain'
 */
#define rtCP_Gain_Gain_i0              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_ke
 * Referenced by: '<S3903>/Gain1'
 */
#define rtCP_Gain1_Gain_ke             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ob0
 * Referenced by: '<S3903>/Gain2'
 */
#define rtCP_Gain2_Gain_ob0            (0.5F)

/* Computed Parameter: rtCP_Gain3_Gain_a
 * Referenced by: '<S3903>/Gain3'
 */
#define rtCP_Gain3_Gain_a              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_ne
 * Referenced by: '<S3903>/Gain'
 */
#define rtCP_Gain_Gain_ne              (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_ba
 * Referenced by: '<S3902>/Gain1'
 */
#define rtCP_Gain1_Gain_ba             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_jd
 * Referenced by: '<S3902>/Gain2'
 */
#define rtCP_Gain2_Gain_jd             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_cb
 * Referenced by: '<S3902>/Gain'
 */
#define rtCP_Gain_Gain_cb              (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_iu
 * Referenced by: '<S3866>/Gain2'
 */
#define rtCP_Gain2_Gain_iu             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_jw3
 * Referenced by: '<S3866>/Gain'
 */
#define rtCP_Gain_Gain_jw3             (0.5F)

/* Computed Parameter: rtCP_Gain1_Gain_de
 * Referenced by: '<S3866>/Gain1'
 */
#define rtCP_Gain1_Gain_de             (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_oa
 * Referenced by: '<S3864>/Gain2'
 */
#define rtCP_Gain2_Gain_oa             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_fo
 * Referenced by: '<S3864>/Gain'
 */
#define rtCP_Gain_Gain_fo              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_org
 * Referenced by: '<S3876>/Gain'
 */
#define rtCP_Gain_Gain_org             (0.5F)

/* Computed Parameter: rtCP_Gain_1_Gain_f5
 * Referenced by: '<S3921>/Gain_1'
 */
#define rtCP_Gain_1_Gain_f5            (-1.0F)

/* Computed Parameter: rtCP_Gain1_Gain_lvy
 * Referenced by: '<S3865>/Gain1'
 */
#define rtCP_Gain1_Gain_lvy            (-1.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ev
 * Referenced by: '<S3889>/Gain2'
 */
#define rtCP_Gain2_Gain_ev             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_bk
 * Referenced by: '<S3889>/Gain'
 */
#define rtCP_Gain_Gain_bk              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_og
 * Referenced by: '<S1639>/Gain'
 */
#define rtCP_Gain_Gain_og              (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_fdf
 * Referenced by: '<S1728>/Gain'
 */
#define rtCP_Gain_Gain_fdf             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_it3
 * Referenced by: '<S1718>/Gain'
 */
#define rtCP_Gain_Gain_it3             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_if0
 * Referenced by: '<S1761>/Gain'
 */
#define rtCP_Gain_Gain_if0             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_fsg
 * Referenced by: '<S1671>/Gain'
 */
#define rtCP_Gain_Gain_fsg             (0.5F)

/* Expression: single(0.001)
 * Referenced by: '<S1769>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_n    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_eq
 * Referenced by: '<S1769>/Saturation'
 */
#define rtCP_Saturation_UpperSat_eq    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_og
 * Referenced by: '<S1769>/Saturation'
 */
#define rtCP_Saturation_LowerSat_og    (0.0F)

/* Computed Parameter: rtCP_Sat_3_UpperSat
 * Referenced by: '<S1572>/Sat_3'
 */
#define rtCP_Sat_3_UpperSat            (0.0F)

/* Computed Parameter: rtCP_Sat_4_UpperSat
 * Referenced by: '<S1572>/Sat_4'
 */
#define rtCP_Sat_4_UpperSat            (0.0F)

/* Computed Parameter: rtCP_Sat_3_UpperSat_d
 * Referenced by: '<S1801>/Sat_3'
 */
#define rtCP_Sat_3_UpperSat_d          (0.0F)

/* Computed Parameter: rtCP_Sat_4_UpperSat_g
 * Referenced by: '<S1801>/Sat_4'
 */
#define rtCP_Sat_4_UpperSat_g          (0.0F)

/* Expression: single(6)
 * Referenced by: '<S27>/ResetTime'
 */
#define rtCP_ResetTime_Value_i         (6.0F)

/* Computed Parameter: rtCP_ActuationManagerPeriodicity1_Value
 * Referenced by: '<S27>/ActuationManagerPeriodicity1'
 */
#define rtCP_ActuationManagerPeriodicity1_Value (1.0F)

/* Computed Parameter: rtCP_Saturation1_UpperSat_gm
 * Referenced by: '<S7>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_gm   (4.0F)

/* Computed Parameter: rtCP_Saturation1_LowerSat_l
 * Referenced by: '<S7>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_l    (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_as
 * Referenced by: '<S455>/Gain'
 */
#define rtCP_Gain_Gain_as              (-1.0F)

/* Expression: CMBB_CrvtAbsltMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/CurvatureAbsltMaxThreshold'
 */
#define rtCP_CurvatureAbsltMaxThreshold_UpperSat (0.2F)

/* Expression: CMBB_CrvtAbsltMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/CurvatureAbsltMaxThreshold'
 */
#define rtCP_CurvatureAbsltMaxThreshold_LowerSat (0.0F)

/* Expression: CMBB_CrvtRateAbsltMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/CurvatureRateAbsltMaxThreshold'
 */
#define rtCP_CurvatureRateAbsltMaxThreshold_UpperSat (2.0F)

/* Expression: CMBB_CrvtRateAbsltMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/CurvatureRateAbsltMaxThreshold'
 */
#define rtCP_CurvatureRateAbsltMaxThreshold_LowerSat (0.0F)

/* Expression: CMBB_APosMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/ALatAbsltMaxThreshold'
 */
#define rtCP_ALatAbsltMaxThreshold_UpperSat (10.0F)

/* Expression: CMBB_ALatMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/ALatAbsltMaxThreshold'
 */
#define rtCP_ALatAbsltMaxThreshold_LowerSat (1.0F)

/* Computed Parameter: rtCP_Gain_Gain_fqs
 * Referenced by: '<S634>/Gain'
 */
#define rtCP_Gain_Gain_fqs             (3.6F)

/* Expression: CMBB_JerkNegMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/JerkLgtNegMinThreshold'
 */
#define rtCP_JerkLgtNegMinThreshold_UpperSat (10.0F)

/* Expression: CMBB_JerkNegMinInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/JerkLgtNegMinThreshold'
 */
#define rtCP_JerkLgtNegMinThreshold_LowerSat (-22.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_gf
 * Referenced by: '<S691>/Saturation'
 */
#define rtCP_Saturation_LowerSat_gf    (0.0F)

/* Computed Parameter: rtCP_Gain_Gain_m3
 * Referenced by: '<S733>/Gain'
 */
#define rtCP_Gain_Gain_m3              (3.6F)

/* Expression: single(pi/2-0.01)
 * Referenced by: '<S716>/Saturation'
 */
#define rtCP_Saturation_UpperSat_g5    (1.56079638F)

/* Expression: -single(pi/2-0.01)
 * Referenced by: '<S716>/Saturation'
 */
#define rtCP_Saturation_LowerSat_lj    (-1.56079638F)

/* Computed Parameter: rtCP_Gain_Gain_hsk
 * Referenced by: '<S728>/Gain'
 */
#define rtCP_Gain_Gain_hsk             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_ap
 * Referenced by: '<S729>/Gain'
 */
#define rtCP_Gain_Gain_ap              (0.5F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_e
 * Referenced by: '<S730>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_e (8.64E+7F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_et
 * Referenced by: '<S732>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_et (8.64E+7F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_l
 * Referenced by: '<S715>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_l (8.64E+7F)

/* Expression: CMBB_CrvtAbsltMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/CurvatureAbsltCmftThreshold'
 */
#define rtCP_CurvatureAbsltCmftThreshold_UpperSat (0.2F)

/* Expression: CMBB_CrvtAbsltMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/CurvatureAbsltCmftThreshold'
 */
#define rtCP_CurvatureAbsltCmftThreshold_LowerSat (0.0F)

/* Expression: CMBB_CrvtRateAbsltMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/CurvatureRateAbsltCmftThreshold'
 */
#define rtCP_CurvatureRateAbsltCmftThreshold_UpperSat (2.0F)

/* Expression: CMBB_CrvtRateAbsltMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/CurvatureRateAbsltCmftThreshold'
 */
#define rtCP_CurvatureRateAbsltCmftThreshold_LowerSat (0.0F)

/* Expression: CMBB_APosMaxThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/ALatAbsltCmftThreshold'
 */
#define rtCP_ALatAbsltCmftThreshold_UpperSat (10.0F)

/* Expression: CMBB_ALatMinThdInCllsnRednByBrkg_Co
 * Referenced by: '<S451>/ALatAbsltCmftThreshold'
 */
#define rtCP_ALatAbsltCmftThreshold_LowerSat (1.0F)

/* Computed Parameter: rtCP_Gain_Gain_c0
 * Referenced by: '<S677>/Gain'
 */
#define rtCP_Gain_Gain_c0              (3.6F)

/* Computed Parameter: rtCP_Gain_Gain_pev
 * Referenced by: '<S590>/Gain'
 */
#define rtCP_Gain_Gain_pev             (2.0F)

/* Computed Parameter: rtCP_Gain_Gain_hen
 * Referenced by: '<S592>/Gain'
 */
#define rtCP_Gain_Gain_hen             (0.5F)

/* Computed Parameter: rtCP_Gain_Gain_ew
 * Referenced by: '<S472>/Gain'
 */
#define rtCP_Gain_Gain_ew              (3.6F)

/* Computed Parameter: rtCP_Saturation_UpperSat_lh
 * Referenced by: '<S193>/Saturation'
 */
#define rtCP_Saturation_UpperSat_lh    (0.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_gfx
 * Referenced by: '<S193>/Saturation'
 */
#define rtCP_Saturation_LowerSat_gfx   (-10.0F)

/* Computed Parameter: rtCP_Saturation1_UpperSat_o
 * Referenced by: '<S193>/Saturation1'
 */
#define rtCP_Saturation1_UpperSat_o    (0.0F)

/* Computed Parameter: rtCP_Saturation1_LowerSat_bw
 * Referenced by: '<S193>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_bw   (-10.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_c
 * Referenced by: '<S269>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_c (8.64E+7F)

/* Computed Parameter: rtCP_Gain_Gain_bv
 * Referenced by: '<S326>/Gain'
 */
#define rtCP_Gain_Gain_bv              (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_h1
 * Referenced by: '<S325>/Gain'
 */
#define rtCP_Gain_Gain_h1              (10.0F)

/* Expression: FCW_Ts_Co
 * Referenced by: '<S325>/c_FCW_Ts gain'
 */
#define rtCP_c_FCW_Tsgain_Gain         (0.02F)

/* Expression: single(0)
 * Referenced by: '<S325>/Saturation'
 */
#define rtCP_Saturation_LowerSat_k2    (0.0F)

/* Computed Parameter: rtCP_Saturation2_LowerSat_p
 * Referenced by: '<S311>/Saturation2'
 */
#define rtCP_Saturation2_LowerSat_p    (0.0F)

/* Computed Parameter: rtCP_Saturation_UpperSat_du
 * Referenced by: '<S311>/Saturation'
 */
#define rtCP_Saturation_UpperSat_du    (3.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_ii
 * Referenced by: '<S311>/Saturation'
 */
#define rtCP_Saturation_LowerSat_ii    (1.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_k0
 * Referenced by: '<S316>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_k0 (8.64E+7F)

/* Computed Parameter: rtCP_Gain_Gain_ko
 * Referenced by: '<S313>/Gain'
 */
#define rtCP_Gain_Gain_ko              (-1.0F)

/* Computed Parameter: rtCP_Saturation3_UpperSat
 * Referenced by: '<S311>/Saturation3'
 */
#define rtCP_Saturation3_UpperSat      (9.8F)

/* Computed Parameter: rtCP_Saturation3_LowerSat
 * Referenced by: '<S311>/Saturation3'
 */
#define rtCP_Saturation3_LowerSat      (0.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_in
 * Referenced by: '<S354>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_in (8.64E+7F)

/* Expression: -single(pi)
 * Referenced by: '<S2413>/Gain'
 */
#define rtCP_Gain_Gain_gc              (-3.14159274F)

/* Computed Parameter: rtCP_Merge_1_1_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_1_InitialOutput   (0.0F)

/* Expression: single(0.001)
 * Referenced by: '<S2670>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_i    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_mh
 * Referenced by: '<S2670>/Saturation'
 */
#define rtCP_Saturation_UpperSat_mh    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_em
 * Referenced by: '<S2670>/Saturation'
 */
#define rtCP_Saturation_LowerSat_em    (0.0F)

/* Computed Parameter: rtCP_Merge_1_2_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_2_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_a54
 * Referenced by: '<S2772>/Gain1'
 */
#define rtCP_Gain1_Gain_a54            (0.5F)

/* Computed Parameter: rtCP_Merge_1_5_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_5_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_bxy
 * Referenced by: '<S2772>/Gain2'
 */
#define rtCP_Gain2_Gain_bxy            (-1.0F)

/* Computed Parameter: rtCP_Merge_1_3_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_3_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_1_4_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_4_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_1_6_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_6_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_1_7_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_7_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ho
 * Referenced by: '<S2800>/Gain1'
 */
#define rtCP_Gain1_Gain_ho             (0.5F)

/* Computed Parameter: rtCP_Merge_1_10_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_10_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_el
 * Referenced by: '<S2800>/Gain2'
 */
#define rtCP_Gain2_Gain_el             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_16_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_16_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_17_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_17_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_a3
 * Referenced by: '<S2820>/Gain1'
 */
#define rtCP_Gain1_Gain_a3             (0.5F)

/* Computed Parameter: rtCP_Merge_1_20_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_20_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_an
 * Referenced by: '<S2820>/Gain2'
 */
#define rtCP_Gain2_Gain_an             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_21_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_21_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_22_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_22_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_n4
 * Referenced by: '<S2830>/Gain1'
 */
#define rtCP_Gain1_Gain_n4             (0.5F)

/* Computed Parameter: rtCP_Merge_1_25_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_25_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_nq
 * Referenced by: '<S2830>/Gain2'
 */
#define rtCP_Gain2_Gain_nq             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput_k
 * Referenced by: '<S2406>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_2_5_InitialOutput
 * Referenced by: '<S2406>/Merge_2'
 */
#define rtCP_Merge_2_5_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_8_InitialOutput
 * Referenced by: '<S2406>/Merge_2'
 */
#define rtCP_Merge_2_8_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_no
 * Referenced by: '<S2787>/Gain1'
 */
#define rtCP_Gain1_Gain_no             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_gi
 * Referenced by: '<S2787>/Gain2'
 */
#define rtCP_Gain2_Gain_gi             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput_k
 * Referenced by: '<S2406>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_2_6_InitialOutput
 * Referenced by: '<S2406>/Merge_2'
 */
#define rtCP_Merge_2_6_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_7_InitialOutput
 * Referenced by: '<S2406>/Merge_2'
 */
#define rtCP_Merge_2_7_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_9_InitialOutput
 * Referenced by: '<S2406>/Merge_2'
 */
#define rtCP_Merge_2_9_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_2_10_InitialOutput
 * Referenced by: '<S2406>/Merge_2'
 */
#define rtCP_Merge_2_10_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_1_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_1_InitialOutput_i (0.0F)

/* Expression: single(0.001)
 * Referenced by: '<S3230>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_f    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_fl
 * Referenced by: '<S3230>/Saturation'
 */
#define rtCP_Saturation_UpperSat_fl    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_f
 * Referenced by: '<S3230>/Saturation'
 */
#define rtCP_Saturation_LowerSat_f     (0.0F)

/* Computed Parameter: rtCP_Merge_1_2_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_2_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_iv
 * Referenced by: '<S3338>/Gain1'
 */
#define rtCP_Gain1_Gain_iv             (0.5F)

/* Computed Parameter: rtCP_Merge_1_5_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_5_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_he
 * Referenced by: '<S3338>/Gain2'
 */
#define rtCP_Gain2_Gain_he             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_3_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_3_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_4_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_4_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_6_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_6_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_7_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_7_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_a1
 * Referenced by: '<S3366>/Gain1'
 */
#define rtCP_Gain1_Gain_a1             (0.5F)

/* Computed Parameter: rtCP_Merge_1_10_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_10_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_az
 * Referenced by: '<S3366>/Gain2'
 */
#define rtCP_Gain2_Gain_az             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_16_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_16_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_17_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_17_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_d4
 * Referenced by: '<S3386>/Gain1'
 */
#define rtCP_Gain1_Gain_d4             (0.5F)

/* Computed Parameter: rtCP_Merge_1_20_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_20_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_kp
 * Referenced by: '<S3386>/Gain2'
 */
#define rtCP_Gain2_Gain_kp             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_21_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_21_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_22_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_22_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_pg
 * Referenced by: '<S3396>/Gain1'
 */
#define rtCP_Gain1_Gain_pg             (0.5F)

/* Computed Parameter: rtCP_Merge_1_25_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_25_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_hb
 * Referenced by: '<S3396>/Gain2'
 */
#define rtCP_Gain2_Gain_hb             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput_g
 * Referenced by: '<S2963>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_5_InitialOutput_g
 * Referenced by: '<S2963>/Merge_2'
 */
#define rtCP_Merge_2_5_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_8_InitialOutput_g
 * Referenced by: '<S2963>/Merge_2'
 */
#define rtCP_Merge_2_8_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_lvv
 * Referenced by: '<S3353>/Gain1'
 */
#define rtCP_Gain1_Gain_lvv            (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_ns
 * Referenced by: '<S3353>/Gain2'
 */
#define rtCP_Gain2_Gain_ns             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput_g
 * Referenced by: '<S2963>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_6_InitialOutput_g
 * Referenced by: '<S2963>/Merge_2'
 */
#define rtCP_Merge_2_6_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_7_InitialOutput_g
 * Referenced by: '<S2963>/Merge_2'
 */
#define rtCP_Merge_2_7_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_9_InitialOutput_g
 * Referenced by: '<S2963>/Merge_2'
 */
#define rtCP_Merge_2_9_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_10_InitialOutput_g
 * Referenced by: '<S2963>/Merge_2'
 */
#define rtCP_Merge_2_10_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Gain4_Gain_c
 * Referenced by: '<S2325>/Gain4'
 */
#define rtCP_Gain4_Gain_c              (0.5F)

/* Computed Parameter: rtCP_Gain_1_Gain_nn
 * Referenced by: '<S2350>/Gain_1'
 */
#define rtCP_Gain_1_Gain_nn            (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_bj
 * Referenced by: '<S2351>/Gain_1'
 */
#define rtCP_Gain_1_Gain_bj            (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_cj
 * Referenced by: '<S2352>/Gain_1'
 */
#define rtCP_Gain_1_Gain_cj            (-1.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_gw
 * Referenced by: '<S2349>/Gain_1'
 */
#define rtCP_Gain_1_Gain_gw            (-1.0F)

/* Computed Parameter: rtCP_Merge_1_11_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_11_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_12_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_12_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_gx
 * Referenced by: '<S2810>/Gain1'
 */
#define rtCP_Gain1_Gain_gx             (0.5F)

/* Computed Parameter: rtCP_Merge_1_15_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_15_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ant
 * Referenced by: '<S2810>/Gain2'
 */
#define rtCP_Gain2_Gain_ant            (-1.0F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput_k
 * Referenced by: '<S2406>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput_k
 * Referenced by: '<S2406>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_11_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_11_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_12_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_12_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ne
 * Referenced by: '<S3376>/Gain1'
 */
#define rtCP_Gain1_Gain_ne             (0.5F)

/* Computed Parameter: rtCP_Merge_1_15_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_15_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ou2
 * Referenced by: '<S3376>/Gain2'
 */
#define rtCP_Gain2_Gain_ou2            (-1.0F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput_g
 * Referenced by: '<S2963>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput_g
 * Referenced by: '<S2963>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput_g (0.0F)

/* Computed Parameter: rtCP_Gain_1_Gain_cl
 * Referenced by: '<S3544>/Gain_1'
 */
#define rtCP_Gain_1_Gain_cl            (-1.0F)

/* Computed Parameter: rtCP_Merge_1_13_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_13_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_14_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_14_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_18_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_18_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_19_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_19_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_23_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_23_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_24_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_24_InitialOutput  (0.0F)

/* Computed Parameter: rtCP_Merge_1_8_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_8_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_1_9_InitialOutput
 * Referenced by: '<S2406>/Merge_1'
 */
#define rtCP_Merge_1_9_InitialOutput   (0.0F)

/* Computed Parameter: rtCP_Merge_1_13_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_13_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_14_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_14_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_18_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_18_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_19_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_19_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_23_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_23_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_24_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_24_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_8_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_8_InitialOutput_i (0.0F)

/* Computed Parameter: rtCP_Merge_1_9_InitialOutput_i
 * Referenced by: '<S2963>/Merge_1'
 */
#define rtCP_Merge_1_9_InitialOutput_i (0.0F)

/* Expression: -single(pi)
 * Referenced by: '<S4101>/Gain'
 */
#define rtCP_Gain_Gain_il              (-3.14159274F)

/* Computed Parameter: rtCP_Merge_1_1_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_1_InitialOutput_j (0.0F)

/* Expression: single(0.001)
 * Referenced by: '<S4358>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_o    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_n1
 * Referenced by: '<S4358>/Saturation'
 */
#define rtCP_Saturation_UpperSat_n1    (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_pg
 * Referenced by: '<S4358>/Saturation'
 */
#define rtCP_Saturation_LowerSat_pg    (0.0F)

/* Computed Parameter: rtCP_Merge_1_2_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_2_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_dl
 * Referenced by: '<S4460>/Gain1'
 */
#define rtCP_Gain1_Gain_dl             (0.5F)

/* Computed Parameter: rtCP_Merge_1_5_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_5_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_dy
 * Referenced by: '<S4460>/Gain2'
 */
#define rtCP_Gain2_Gain_dy             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_3_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_3_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_4_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_4_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_6_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_6_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_7_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_7_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_pi
 * Referenced by: '<S4488>/Gain1'
 */
#define rtCP_Gain1_Gain_pi             (0.5F)

/* Computed Parameter: rtCP_Merge_1_10_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_10_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_fv
 * Referenced by: '<S4488>/Gain2'
 */
#define rtCP_Gain2_Gain_fv             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_16_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_16_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_17_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_17_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_k5
 * Referenced by: '<S4508>/Gain1'
 */
#define rtCP_Gain1_Gain_k5             (0.5F)

/* Computed Parameter: rtCP_Merge_1_20_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_20_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_bk
 * Referenced by: '<S4508>/Gain2'
 */
#define rtCP_Gain2_Gain_bk             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_21_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_21_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_22_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_22_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_lc
 * Referenced by: '<S4518>/Gain1'
 */
#define rtCP_Gain1_Gain_lc             (0.5F)

/* Computed Parameter: rtCP_Merge_1_25_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_25_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_hy
 * Referenced by: '<S4518>/Gain2'
 */
#define rtCP_Gain2_Gain_hy             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput_f
 * Referenced by: '<S4094>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_5_InitialOutput_f
 * Referenced by: '<S4094>/Merge_2'
 */
#define rtCP_Merge_2_5_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_8_InitialOutput_f
 * Referenced by: '<S4094>/Merge_2'
 */
#define rtCP_Merge_2_8_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_cs
 * Referenced by: '<S4475>/Gain1'
 */
#define rtCP_Gain1_Gain_cs             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_hg
 * Referenced by: '<S4475>/Gain2'
 */
#define rtCP_Gain2_Gain_hg             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput_f
 * Referenced by: '<S4094>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_6_InitialOutput_f
 * Referenced by: '<S4094>/Merge_2'
 */
#define rtCP_Merge_2_6_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_7_InitialOutput_f
 * Referenced by: '<S4094>/Merge_2'
 */
#define rtCP_Merge_2_7_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_9_InitialOutput_f
 * Referenced by: '<S4094>/Merge_2'
 */
#define rtCP_Merge_2_9_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_10_InitialOutput_f
 * Referenced by: '<S4094>/Merge_2'
 */
#define rtCP_Merge_2_10_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_1_1_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_1_InitialOutput_k (0.0F)

/* Expression: single(0.001)
 * Referenced by: '<S4918>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_j    (0.001F)

/* Computed Parameter: rtCP_Saturation_UpperSat_j
 * Referenced by: '<S4918>/Saturation'
 */
#define rtCP_Saturation_UpperSat_j     (1.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_hg
 * Referenced by: '<S4918>/Saturation'
 */
#define rtCP_Saturation_LowerSat_hg    (0.0F)

/* Computed Parameter: rtCP_Merge_1_2_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_2_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_og
 * Referenced by: '<S5026>/Gain1'
 */
#define rtCP_Gain1_Gain_og             (0.5F)

/* Computed Parameter: rtCP_Merge_1_5_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_5_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_ew
 * Referenced by: '<S5026>/Gain2'
 */
#define rtCP_Gain2_Gain_ew             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_3_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_3_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_4_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_4_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_6_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_6_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_7_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_7_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_kh
 * Referenced by: '<S5054>/Gain1'
 */
#define rtCP_Gain1_Gain_kh             (0.5F)

/* Computed Parameter: rtCP_Merge_1_10_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_10_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_li
 * Referenced by: '<S5054>/Gain2'
 */
#define rtCP_Gain2_Gain_li             (-1.0F)

/* Computed Parameter: rtCP_Merge_1_16_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_16_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_17_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_17_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_20_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_20_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_21_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_21_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_22_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_22_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_25_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_25_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_2_1_InitialOutput_j
 * Referenced by: '<S4651>/Merge_2'
 */
#define rtCP_Merge_2_1_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_5_InitialOutput_j
 * Referenced by: '<S4651>/Merge_2'
 */
#define rtCP_Merge_2_5_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_8_InitialOutput_j
 * Referenced by: '<S4651>/Merge_2'
 */
#define rtCP_Merge_2_8_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_ar
 * Referenced by: '<S5041>/Gain1'
 */
#define rtCP_Gain1_Gain_ar             (0.5F)

/* Computed Parameter: rtCP_Gain2_Gain_lg
 * Referenced by: '<S5041>/Gain2'
 */
#define rtCP_Gain2_Gain_lg             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_2_InitialOutput_j
 * Referenced by: '<S4651>/Merge_2'
 */
#define rtCP_Merge_2_2_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_6_InitialOutput_j
 * Referenced by: '<S4651>/Merge_2'
 */
#define rtCP_Merge_2_6_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_7_InitialOutput_j
 * Referenced by: '<S4651>/Merge_2'
 */
#define rtCP_Merge_2_7_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_9_InitialOutput_j
 * Referenced by: '<S4651>/Merge_2'
 */
#define rtCP_Merge_2_9_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_10_InitialOutput_j
 * Referenced by: '<S4651>/Merge_2'
 */
#define rtCP_Merge_2_10_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain4_Gain_h
 * Referenced by: '<S4013>/Gain4'
 */
#define rtCP_Gain4_Gain_h              (0.5F)

/* Computed Parameter: rtCP_Gain_1_Gain_iw
 * Referenced by: '<S4039>/Gain_1'
 */
#define rtCP_Gain_1_Gain_iw            (-1.0F)

/* Computed Parameter: rtCP_Merge_1_11_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_11_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_12_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_12_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_io
 * Referenced by: '<S4498>/Gain1'
 */
#define rtCP_Gain1_Gain_io             (0.5F)

/* Computed Parameter: rtCP_Merge_1_15_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_15_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_jy
 * Referenced by: '<S4498>/Gain2'
 */
#define rtCP_Gain2_Gain_jy             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput_f
 * Referenced by: '<S4094>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput_f
 * Referenced by: '<S4094>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput_f (0.0F)

/* Computed Parameter: rtCP_Merge_1_11_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_11_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_12_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_12_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain1_Gain_aa
 * Referenced by: '<S5064>/Gain1'
 */
#define rtCP_Gain1_Gain_aa             (0.5F)

/* Computed Parameter: rtCP_Merge_1_15_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_15_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Gain2_Gain_j3
 * Referenced by: '<S5064>/Gain2'
 */
#define rtCP_Gain2_Gain_j3             (-1.0F)

/* Computed Parameter: rtCP_Merge_2_3_InitialOutput_j
 * Referenced by: '<S4651>/Merge_2'
 */
#define rtCP_Merge_2_3_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_2_4_InitialOutput_j
 * Referenced by: '<S4651>/Merge_2'
 */
#define rtCP_Merge_2_4_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_13_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_13_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_14_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_14_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_18_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_18_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_19_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_19_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_23_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_23_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_24_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_24_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_8_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_8_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_9_InitialOutput_j
 * Referenced by: '<S4094>/Merge_1'
 */
#define rtCP_Merge_1_9_InitialOutput_j (0.0F)

/* Computed Parameter: rtCP_Merge_1_13_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_13_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_14_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_14_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_18_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_18_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_19_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_19_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_23_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_23_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_24_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_24_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_8_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_8_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_Merge_1_9_InitialOutput_k
 * Referenced by: '<S4651>/Merge_1'
 */
#define rtCP_Merge_1_9_InitialOutput_k (0.0F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_ky
 * Referenced by: '<S5997>/UnitDelay'
 */
#define rtCP_UnitDelay_InitialCondition_ky (8.64E+7F)

/* Computed Parameter: rtCP_Saturation_UpperSat_hu
 * Referenced by: '<S6058>/Saturation'
 */
#define rtCP_Saturation_UpperSat_hu    (0.0F)

/* Computed Parameter: rtCP_Saturation1_LowerSat_e
 * Referenced by: '<S6005>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_e    (0.0F)

/* Computed Parameter: rtCP_Saturation2_LowerSat_h
 * Referenced by: '<S6005>/Saturation2'
 */
#define rtCP_Saturation2_LowerSat_h    (0.0F)

/* Computed Parameter: rtCP_Saturation1_LowerSat_no
 * Referenced by: '<S6004>/Saturation1'
 */
#define rtCP_Saturation1_LowerSat_no   (0.0F)

/* Computed Parameter: rtCP_Saturation_LowerSat_pgq
 * Referenced by: '<S6004>/Saturation'
 */
#define rtCP_Saturation_LowerSat_pgq   (0.0F)

/* Expression: single(3.6)
 * Referenced by: '<S6>/Gain'
 */
#define rtCP_Gain_Gain_ige             (3.6F)

/* Expression: single(180/pi)
 * Referenced by: '<S6>/Gain1'
 */
#define rtCP_Gain1_Gain_l5z            (57.2957802F)

/* Computed Parameter: rtCP_UnitDelay_InitialCondition_ih
 * Referenced by: '<S6128>/Unit Delay'
 */
#define rtCP_UnitDelay_InitialCondition_ih (-1.0F)

/* Expression: single(-1)
 * Referenced by: '<S6141>/Gain1'
 */
#define rtCP_Gain1_Gain_el             (-1.0F)

/* Computed Parameter: rtCP_Gain_Gain_ck
 * Referenced by: '<S6200>/Gain'
 */
#define rtCP_Gain_Gain_ck              (57.2957802F)

/* Computed Parameter: rtCP_Idn_Y0
 * Referenced by: '<S979>/Idn'
 */
#define rtCP_Idn_Y0                    (0U)

/* Computed Parameter: rtCP_Constant_Value_dkh
 * Referenced by: '<S838>/Constant'
 */
#define rtCP_Constant_Value_dkh        (0U)

/* Computed Parameter: rtCP_Constant_Value_iks
 * Referenced by: '<S839>/Constant'
 */
#define rtCP_Constant_Value_iks        (0U)

/* Computed Parameter: rtCP_Constant_Value_ks4
 * Referenced by: '<S844>/Constant'
 */
#define rtCP_Constant_Value_ks4        (0U)

/* Computed Parameter: rtCP_Constant_Value_g3u
 * Referenced by: '<S845>/Constant'
 */
#define rtCP_Constant_Value_g3u        (0U)

/* Computed Parameter: rtCP_Constant_Value_n5z
 * Referenced by: '<S848>/Constant'
 */
#define rtCP_Constant_Value_n5z        (0U)

/* Computed Parameter: rtCP_Constant_Value_pda
 * Referenced by: '<S849>/Constant'
 */
#define rtCP_Constant_Value_pda        (0U)

/* Computed Parameter: rtCP_Constant_Value_mhx
 * Referenced by: '<S856>/Constant'
 */
#define rtCP_Constant_Value_mhx        (0U)

/* Computed Parameter: rtCP_Constant_Value_nba
 * Referenced by: '<S858>/Constant'
 */
#define rtCP_Constant_Value_nba        (0U)

/* Computed Parameter: rtCP_Constant_Value_h34
 * Referenced by: '<S859>/Constant'
 */
#define rtCP_Constant_Value_h34        (0U)

/* Computed Parameter: rtCP_Constant_Value_nd4
 * Referenced by: '<S862>/Constant'
 */
#define rtCP_Constant_Value_nd4        (0U)

/* Computed Parameter: rtCP_Constant_Value_gfj
 * Referenced by: '<S863>/Constant'
 */
#define rtCP_Constant_Value_gfj        (0U)

/* Computed Parameter: rtCP_Constant_Value_acl
 * Referenced by: '<S872>/Constant'
 */
#define rtCP_Constant_Value_acl        (0U)

/* Computed Parameter: rtCP_Constant_Value_eac3
 * Referenced by: '<S874>/Constant'
 */
#define rtCP_Constant_Value_eac3       (0U)

/* Computed Parameter: rtCP_Constant_Value_pcq
 * Referenced by: '<S875>/Constant'
 */
#define rtCP_Constant_Value_pcq        (0U)

/* Computed Parameter: rtCP_Constant_Value_f1a
 * Referenced by: '<S1583>/Constant'
 */
#define rtCP_Constant_Value_f1a        (0U)

/* Computed Parameter: rtCP_Constant_Value_p1
 * Referenced by: '<S1584>/Constant'
 */
#define rtCP_Constant_Value_p1         (0U)

/* Expression: uint32(0)
 * Referenced by: '<S936>/Constant1'
 */
#define rtCP_Constant1_Value_a0        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S936>/Constant13'
 */
#define rtCP_Constant13_Value_af       (0U)

/* Expression: uint32(0)
 * Referenced by: '<S960>/Constant12'
 */
#define rtCP_Constant12_Value_l        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S960>/Constant4'
 */
#define rtCP_Constant4_Value_eq        (0U)

/* Computed Parameter: rtCP_Constant_Value_gin
 * Referenced by: '<S975>/Constant'
 */
#define rtCP_Constant_Value_gin        (0U)

/* Computed Parameter: rtCP_Constant_Value_ifa
 * Referenced by: '<S1285>/Constant'
 */
#define rtCP_Constant_Value_ifa        (0U)

/* Computed Parameter: rtCP_DefaultId_Value
 * Referenced by: '<S575>/DefaultId'
 */
#define rtCP_DefaultId_Value           (0U)

/* Computed Parameter: rtCP_Constant_Value_o3w
 * Referenced by: '<S2100>/Constant'
 */
#define rtCP_Constant_Value_o3w        (0U)

/* Computed Parameter: rtCP_Constant_Value_ij0
 * Referenced by: '<S2101>/Constant'
 */
#define rtCP_Constant_Value_ij0        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S2325>/Constant'
 */
#define rtCP_Constant_Value_k4         (0U)

/* Computed Parameter: rtCP_Constant_Value_lmo
 * Referenced by: '<S3788>/Constant'
 */
#define rtCP_Constant_Value_lmo        (0U)

/* Computed Parameter: rtCP_Constant_Value_d1i
 * Referenced by: '<S3789>/Constant'
 */
#define rtCP_Constant_Value_d1i        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S4013>/Constant'
 */
#define rtCP_Constant_Value_mu         (0U)

/* Computed Parameter: rtCP_Constant_Value_fw2
 * Referenced by: '<S5474>/Constant'
 */
#define rtCP_Constant_Value_fw2        (0U)

/* Computed Parameter: rtCP_Constant_Value_kwh
 * Referenced by: '<S5475>/Constant'
 */
#define rtCP_Constant_Value_kwh        (0U)

/* Computed Parameter: rtCP_Constant_Value_ggx
 * Referenced by: '<S5511>/Constant'
 */
#define rtCP_Constant_Value_ggx        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S6142>/Constant6'
 */
#define rtCP_Constant6_Value_kd        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S6142>/Constant8'
 */
#define rtCP_Constant8_Value_g5        (0U)

/* Expression: uint32(2)
 * Referenced by: '<S6166>/Constant'
 */
#define rtCP_Constant_Value_ms1        (2U)

/* Expression: uint32(0)
 * Referenced by: '<S6166>/Constant1'
 */
#define rtCP_Constant1_Value_op        (0U)

/* Computed Parameter: rtCP_Constant_Value_ise
 * Referenced by: '<S6169>/Constant'
 */
#define rtCP_Constant_Value_ise        (3U)

/* Computed Parameter: rtCP_Constant1_Value_lxj
 * Referenced by: '<S6169>/Constant1'
 */
#define rtCP_Constant1_Value_lxj       (6U)

/* Computed Parameter: rtCP_Constant2_Value_kf
 * Referenced by: '<S6169>/Constant2'
 */
#define rtCP_Constant2_Value_kf        (4U)

/* Computed Parameter: rtCP_Constant3_Value_kzv
 * Referenced by: '<S6169>/Constant3'
 */
#define rtCP_Constant3_Value_kzv       (1U)

/* Computed Parameter: rtCP_Constant4_Value_lp
 * Referenced by: '<S6169>/Constant4'
 */
#define rtCP_Constant4_Value_lp        (2U)

/* Computed Parameter: rtCP_Constant6_Value_fj
 * Referenced by: '<S6169>/Constant6'
 */
#define rtCP_Constant6_Value_fj        (0U)

/* Computed Parameter: rtCP_Constant_Value_c31
 * Referenced by: '<S6209>/Constant'
 */
#define rtCP_Constant_Value_c31        (4U)

/* Computed Parameter: rtCP_Constant1_Value_mc
 * Referenced by: '<S6209>/Constant1'
 */
#define rtCP_Constant1_Value_mc        (0U)

/* Expression: uint32(0)
 * Referenced by: '<S6143>/Constant2'
 */
#define rtCP_Constant2_Value_br        (0U)

/* Computed Parameter: rtCP_One_1_Value
 * Referenced by: '<S506>/One_1'
 */
#define rtCP_One_1_Value               (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_d
 * Referenced by: '<S506>/Zero_2'
 */
#define rtCP_Zero_2_Value_d            (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_m
 * Referenced by: '<S508>/One_1'
 */
#define rtCP_One_1_Value_m             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_l
 * Referenced by: '<S508>/Zero_2'
 */
#define rtCP_Zero_2_Value_l            (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_b
 * Referenced by: '<S529>/One_1'
 */
#define rtCP_One_1_Value_b             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_hb
 * Referenced by: '<S529>/Zero_2'
 */
#define rtCP_Zero_2_Value_hb           (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_f
 * Referenced by: '<S530>/One_1'
 */
#define rtCP_One_1_Value_f             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_e
 * Referenced by: '<S530>/Zero_2'
 */
#define rtCP_Zero_2_Value_e            (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_a
 * Referenced by: '<S598>/One_1'
 */
#define rtCP_One_1_Value_a             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_hg
 * Referenced by: '<S598>/Zero_2'
 */
#define rtCP_Zero_2_Value_hg           (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_c
 * Referenced by: '<S605>/One_1'
 */
#define rtCP_One_1_Value_c             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_hr
 * Referenced by: '<S605>/Zero_2'
 */
#define rtCP_Zero_2_Value_hr           (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_g
 * Referenced by: '<S612>/One_1'
 */
#define rtCP_One_1_Value_g             (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_p
 * Referenced by: '<S612>/Zero_2'
 */
#define rtCP_Zero_2_Value_p            (((uint16_T)0U))

/* Computed Parameter: rtCP_One_1_Value_gf
 * Referenced by: '<S740>/One_1'
 */
#define rtCP_One_1_Value_gf            (((uint16_T)1U))

/* Computed Parameter: rtCP_Zero_2_Value_c
 * Referenced by: '<S740>/Zero_2'
 */
#define rtCP_Zero_2_Value_c            (((uint16_T)0U))

/* Computed Parameter: rtCP_Constant_Value_eu1
 * Referenced by: '<S6064>/Constant'
 */
#define rtCP_Constant_Value_eu1        (((uint16_T)0U))

/* Expression: uint16(4)
 * Referenced by: '<S6167>/Constant10'
 */
#define rtCP_Constant10_Value_bl       (((uint16_T)4U))

/* Expression: uint16(8)
 * Referenced by: '<S6167>/Constant11'
 */
#define rtCP_Constant11_Value_h        (((uint16_T)8U))

/* Expression: uint16(0)
 * Referenced by: '<S6167>/Constant2'
 */
#define rtCP_Constant2_Value_bb        (((uint16_T)0U))

/* Expression: uint16(1)
 * Referenced by: '<S6167>/Constant3'
 */
#define rtCP_Constant3_Value_an        (((uint16_T)1U))

/* Expression: uint16(16)
 * Referenced by: '<S6167>/Constant4'
 */
#define rtCP_Constant4_Value_b3        (((uint16_T)16U))

/* Expression: uint16(32)
 * Referenced by: '<S6167>/Constant5'
 */
#define rtCP_Constant5_Value_px        (((uint16_T)32U))

/* Expression: uint16(2)
 * Referenced by: '<S6167>/Constant7'
 */
#define rtCP_Constant7_Value_p         (((uint16_T)2U))

/* Computed Parameter: rtCP_DataStoreMemory1_InitialValue_d
 * Referenced by: '<S705>/Data Store Memory1'
 */
#define rtCP_DataStoreMemory1_InitialValue_d (((uint16_T)1U))

/* Expression: const
 * Referenced by: '<S896>/Constant'
 */
#define rtCP_Constant_Value_b14        (SceniaroInvalidReason_CCFT_SpdInValid)

/* Expression: const
 * Referenced by: '<S898>/Constant'
 */
#define rtCP_Constant_Value_fnk        (SceniaroInvalidReason_CCFT_HostInValid)

/* Expression: const
 * Referenced by: '<S899>/Constant'
 */
#define rtCP_Constant_Value_pax        (SceniaroInvalidReason_CCSCP_VlgtInValid)

/* Expression: const
 * Referenced by: '<S900>/Constant'
 */
#define rtCP_Constant_Value_h3g        (SceniaroInvalidReason_CCSCP_HeadingInValid)

/* Expression: const
 * Referenced by: '<S901>/Constant'
 */
#define rtCP_Constant_Value_ibc        (SceniaroInvalidReason_CBFANA_VlgtInValid)

/* Expression: const
 * Referenced by: '<S915>/Constant'
 */
#define rtCP_Constant_Value_cou        (SceniaroInvalidReason_CCSCP_HeadingInValid)

/* Expression: const
 * Referenced by: '<S916>/Constant'
 */
#define rtCP_Constant_Value_d34        (SceniaroInvalidReason_CBFANA_VlgtInValid)

/* Expression: const
 * Referenced by: '<S922>/Constant'
 */
#define rtCP_Constant_Value_dp2        (SceniaroInvalidReason_CCFT_SpdInValid)

/* Expression: const
 * Referenced by: '<S923>/Constant'
 */
#define rtCP_Constant_Value_ojd        (SceniaroInvalidReason_CCFT_HostInValid)

/* Expression: const
 * Referenced by: '<S924>/Constant'
 */
#define rtCP_Constant_Value_jdl        (SceniaroInvalidReason_CCSCP_VlgtInValid)

/* Expression: VehMtnSt2.StandStillVal3
 * Referenced by: '<S5490>/Constant'
 */
#define rtCP_Constant_Value_g4w        (VehMtnSt2_StandStillVal3)

/* Expression: VehMtnSt2.RollgBackwVal1
 * Referenced by: '<S5490>/Constant1'
 */
#define rtCP_Constant1_Value_bxr       (VehMtnSt2_RollgBackwVal1)

/* Expression: VehMtnSt2.RollgFwdVal1
 * Referenced by: '<S5490>/Constant2'
 */
#define rtCP_Constant2_Value_ot        (VehMtnSt2_RollgFwdVal1)

/* Expression: VehMtnSt2.RollgFwdVal2
 * Referenced by: '<S5490>/Constant3'
 */
#define rtCP_Constant3_Value_h5f       (VehMtnSt2_RollgFwdVal2)

/* Expression: true
 * Referenced by: '<S990>/true1'
 */
#define rtCP_true1_Value               (true)

/* Expression: true
 * Referenced by: '<S992>/true1'
 */
#define rtCP_true1_Value_l             (true)

/* Expression: true
 * Referenced by: '<S995>/true1'
 */
#define rtCP_true1_Value_f             (true)

/* Expression: true
 * Referenced by: '<S1319>/true1'
 */
#define rtCP_true1_Value_e             (true)

/* Expression: true
 * Referenced by: '<S1321>/true1'
 */
#define rtCP_true1_Value_g             (true)

/* Expression: true
 * Referenced by: '<S1324>/true1'
 */
#define rtCP_true1_Value_m             (true)

/* Expression: true
 * Referenced by: '<S1815>/true1'
 */
#define rtCP_true1_Value_i             (true)

/* Expression: true
 * Referenced by: '<S1817>/true1'
 */
#define rtCP_true1_Value_b             (true)

/* Expression: true
 * Referenced by: '<S1820>/true1'
 */
#define rtCP_true1_Value_l0            (true)

/* Computed Parameter: rtCP_False_Value
 * Referenced by: '<S2412>/False'
 */
#define rtCP_False_Value               (false)

/* Computed Parameter: rtCP_True_Value
 * Referenced by: '<S2412>/True'
 */
#define rtCP_True_Value                (true)

/* Computed Parameter: rtCP_False_Value_o
 * Referenced by: '<S2414>/False'
 */
#define rtCP_False_Value_o             (false)

/* Computed Parameter: rtCP_True_Value_f
 * Referenced by: '<S2414>/True'
 */
#define rtCP_True_Value_f              (true)

/* Computed Parameter: rtCP_False_Value_i
 * Referenced by: '<S2698>/False'
 */
#define rtCP_False_Value_i             (false)

/* Computed Parameter: rtCP_False_Value_ih
 * Referenced by: '<S2699>/False'
 */
#define rtCP_False_Value_ih            (false)

/* Computed Parameter: rtCP_False_Value_a
 * Referenced by: '<S2972>/False'
 */
#define rtCP_False_Value_a             (false)

/* Computed Parameter: rtCP_True_Value_a
 * Referenced by: '<S2972>/True'
 */
#define rtCP_True_Value_a              (true)

/* Expression: false
 * Referenced by: '<S3590>/Constant'
 */
#define rtCP_Constant_Value_h1i        (false)

/* Expression: false
 * Referenced by: '<S3591>/Constant'
 */
#define rtCP_Constant_Value_da1        (false)

/* Expression: false
 * Referenced by: '<S3611>/Constant'
 */
#define rtCP_Constant_Value_lzs        (false)

/* Expression: false
 * Referenced by: '<S3612>/Constant'
 */
#define rtCP_Constant_Value_ika        (false)

/* Expression: false
 * Referenced by: '<S3632>/Constant'
 */
#define rtCP_Constant_Value_jch        (false)

/* Expression: false
 * Referenced by: '<S3633>/Constant'
 */
#define rtCP_Constant_Value_ehj        (false)

/* Computed Parameter: rtCP_Constant3_Value_ax
 * Referenced by: '<S5943>/Constant3'
 */
#define rtCP_Constant3_Value_ax        (true)

/* Computed Parameter: rtCP_Constant4_Value_eu
 * Referenced by: '<S5943>/Constant4'
 */
#define rtCP_Constant4_Value_eu        (false)

/* Expression: const
 * Referenced by: '<S800>/Constant'
 */
#define rtCP_Constant_Value_hbn        (false)

/* Expression: const
 * Referenced by: '<S830>/Constant'
 */
#define rtCP_Constant_Value_bcq        (false)

/* Expression: true
 * Referenced by: '<S878>/Constant'
 */
#define rtCP_Constant_Value_ivb        (true)

/* Expression: false
 * Referenced by: '<S878>/Constant1'
 */
#define rtCP_Constant1_Value_jhk       (false)

/* Expression: true
 * Referenced by: '<S883>/Constant'
 */
#define rtCP_Constant_Value_jyt        (true)

/* Expression: false
 * Referenced by: '<S883>/Constant1'
 */
#define rtCP_Constant1_Value_h3z       (false)

/* Computed Parameter: rtCP_Constant_Value_ioj
 * Referenced by: '<S1801>/Constant'
 */
#define rtCP_Constant_Value_ioj        (true)

/* Computed Parameter: rtCP_Constant2_Value_ce
 * Referenced by: '<S1801>/Constant2'
 */
#define rtCP_Constant2_Value_ce        (true)

/* Expression: false
 * Referenced by: '<S15>/zeroConstant5'
 */
#define rtCP_zeroConstant5_Value       (false)

/* Expression: true
 * Referenced by: '<S7>/true'
 */
#define rtCP_true_Value                (true)

/* Expression: false
 * Referenced by: '<S134>/Constant'
 */
#define rtCP_Constant_Value_cio        (false)

/* Expression: true
 * Referenced by: '<S135>/Constant'
 */
#define rtCP_Constant_Value_cnv        (true)

/* Expression: false
 * Referenced by: '<S135>/Constant1'
 */
#define rtCP_Constant1_Value_aci       (false)

/* Expression: false
 * Referenced by: '<S136>/Constant1'
 */
#define rtCP_Constant1_Value_jrb       (false)

/* Expression: true
 * Referenced by: '<S136>/Constant2'
 */
#define rtCP_Constant2_Value_eu        (true)

/* Computed Parameter: rtCP_Constant_Value_db1
 * Referenced by: '<S220>/Constant'
 */
#define rtCP_Constant_Value_db1        (false)

/* Computed Parameter: rtCP_Constant_Value_kc2x
 * Referenced by: '<S222>/Constant'
 */
#define rtCP_Constant_Value_kc2x       (false)

/* Computed Parameter: rtCP_Constant_Value_p2g
 * Referenced by: '<S224>/Constant'
 */
#define rtCP_Constant_Value_p2g        (false)

/* Computed Parameter: rtCP_Constant_Value_pdc
 * Referenced by: '<S226>/Constant'
 */
#define rtCP_Constant_Value_pdc        (false)

/* Computed Parameter: rtCP_Constant_Value_dmx
 * Referenced by: '<S228>/Constant'
 */
#define rtCP_Constant_Value_dmx        (false)

/* Computed Parameter: rtCP_Constant_Value_ixq
 * Referenced by: '<S230>/Constant'
 */
#define rtCP_Constant_Value_ixq        (false)

/* Computed Parameter: rtCP_Constant_Value_bo53
 * Referenced by: '<S232>/Constant'
 */
#define rtCP_Constant_Value_bo53       (false)

/* Expression: false
 * Referenced by: '<S192>/FCW_DrvrDecelThdForBrkGainInCllsnFwdWarnCtrl_Ca2'
 */
#define rtCP_FCW_DrvrDecelThdForBrkGainInCllsnFwdWarnCtrl_Ca2_Value (false)

/* Expression: false
 * Referenced by: '<S241>/AllowAnimsForAccBrkCapacity'
 */
#define rtCP_AllowAnimsForAccBrkCapacity_Value (false)

/* Expression: false
 * Referenced by: '<S241>/AllowBicForAccBrkCapacity'
 */
#define rtCP_AllowBicForAccBrkCapacity_Value (false)

/* Expression: true
 * Referenced by: '<S241>/AllowCarsForAccBrkCapacity'
 */
#define rtCP_AllowCarsForAccBrkCapacity_Value (true)

/* Expression: true
 * Referenced by: '<S241>/AllowMcsForAccBrkCapacity'
 */
#define rtCP_AllowMcsForAccBrkCapacity_Value (true)

/* Expression: false
 * Referenced by: '<S241>/AllowObjGenForAccBrkCapacity'
 */
#define rtCP_AllowObjGenForAccBrkCapacity_Value (false)

/* Expression: false
 * Referenced by: '<S241>/AllowPedsForAccBrkCapacity'
 */
#define rtCP_AllowPedsForAccBrkCapacity_Value (false)

/* Expression: true
 * Referenced by: '<S241>/AllowTrucksForAccBrkCapacity'
 */
#define rtCP_AllowTrucksForAccBrkCapacity_Value (true)

/* Expression: true
 * Referenced by: '<S241>/AllowVehOfUnknwnClassForAccBrkCapacity'
 */
#define rtCP_AllowVehOfUnknwnClassForAccBrkCapacity_Value (true)

/* Expression: false
 * Referenced by: '<S241>/DefaultState'
 */
#define rtCP_DefaultState_Value        (false)

/* Expression: false
 * Referenced by: '<S194>/false'
 */
#define rtCP_false_Value               (false)

/* Expression: false
 * Referenced by: '<S203>/false10'
 */
#define rtCP_false10_Value             (false)

/* Expression: true
 * Referenced by: '<S287>/AllowOncomingObjects2'
 */
#define rtCP_AllowOncomingObjects2_Value (true)

/* Expression: true
 * Referenced by: '<S287>/false1'
 */
#define rtCP_false1_Value              (true)

/* Expression: false
 * Referenced by: '<S287>/false10'
 */
#define rtCP_false10_Value_e           (false)

/* Expression: true
 * Referenced by: '<S287>/false2'
 */
#define rtCP_false2_Value              (true)

/* Expression: true
 * Referenced by: '<S287>/false3'
 */
#define rtCP_false3_Value              (true)

/* Expression: true
 * Referenced by: '<S287>/false5'
 */
#define rtCP_false5_Value              (true)

/* Expression: true
 * Referenced by: '<S287>/false6'
 */
#define rtCP_false6_Value              (true)

/* Expression: true
 * Referenced by: '<S287>/false7'
 */
#define rtCP_false7_Value              (true)

/* Expression: true
 * Referenced by: '<S287>/false8'
 */
#define rtCP_false8_Value              (true)

/* Expression: true
 * Referenced by: '<S287>/false9'
 */
#define rtCP_false9_Value              (true)

/* Expression: false
 * Referenced by: '<S288>/false1'
 */
#define rtCP_false1_Value_c            (false)

/* Expression: false
 * Referenced by: '<S288>/false10'
 */
#define rtCP_false10_Value_d           (false)

/* Expression: false
 * Referenced by: '<S288>/false2'
 */
#define rtCP_false2_Value_a            (false)

/* Expression: false
 * Referenced by: '<S288>/false3'
 */
#define rtCP_false3_Value_n            (false)

/* Expression: true
 * Referenced by: '<S288>/false4'
 */
#define rtCP_false4_Value              (true)

/* Expression: true
 * Referenced by: '<S288>/false5'
 */
#define rtCP_false5_Value_f            (true)

/* Expression: false
 * Referenced by: '<S288>/false6'
 */
#define rtCP_false6_Value_f            (false)

/* Expression: false
 * Referenced by: '<S288>/false7'
 */
#define rtCP_false7_Value_m            (false)

/* Expression: false
 * Referenced by: '<S288>/false8'
 */
#define rtCP_false8_Value_j            (false)

/* Expression: false
 * Referenced by: '<S288>/false9'
 */
#define rtCP_false9_Value_m            (false)

/* Expression: false
 * Referenced by: '<S205>/DstCmftActvdForBicycleInCllsnFwdWarnCtrl'
 */
#define rtCP_DstCmftActvdForBicycleInCllsnFwdWarnCtrl_Value (false)

/* Expression: false
 * Referenced by: '<S205>/DstCmftActvdForCarInCllsnFwdWarnCtrl'
 */
#define rtCP_DstCmftActvdForCarInCllsnFwdWarnCtrl_Value (false)

/* Expression: false
 * Referenced by: '<S205>/DstCmftActvdForMotorcycleInCllsnFwdWarnCtrl'
 */
#define rtCP_DstCmftActvdForMotorcycleInCllsnFwdWarnCtrl_Value (false)

/* Expression: false
 * Referenced by: '<S205>/DstCmftActvdForPedInCllsnFwdWarnCtrl'
 */
#define rtCP_DstCmftActvdForPedInCllsnFwdWarnCtrl_Value (false)

/* Expression: false
 * Referenced by: '<S205>/DstCmftActvdForTruckInCllsnFwdWarnCtrl'
 */
#define rtCP_DstCmftActvdForTruckInCllsnFwdWarnCtrl_Value (false)

/* Expression: false
 * Referenced by: '<S205>/false'
 */
#define rtCP_false_Value_c             (false)

/* Expression: false
 * Referenced by: '<S590>/Constant'
 */
#define rtCP_Constant_Value_d3w        (false)

/* Expression: true
 * Referenced by: '<S603>/Constant'
 */
#define rtCP_Constant_Value_auz        (true)

/* Expression: false
 * Referenced by: '<S603>/Constant1'
 */
#define rtCP_Constant1_Value_hls       (false)

/* Expression: true
 * Referenced by: '<S623>/Constant2'
 */
#define rtCP_Constant2_Value_df        (true)

/* Computed Parameter: rtCP_Constant3_Value_n3s
 * Referenced by: '<S629>/Constant3'
 */
#define rtCP_Constant3_Value_n3s       (true)

/* Computed Parameter: rtCP_Constant4_Value_ca
 * Referenced by: '<S629>/Constant4'
 */
#define rtCP_Constant4_Value_ca        (false)

/* Expression: true
 * Referenced by: '<S651>/Constant2'
 */
#define rtCP_Constant2_Value_n3        (true)

/* Computed Parameter: rtCP_Constant_Value_bil
 * Referenced by: '<S685>/Constant'
 */
#define rtCP_Constant_Value_bil        (true)

/* Computed Parameter: rtCP_Constant1_Value_di
 * Referenced by: '<S685>/Constant1'
 */
#define rtCP_Constant1_Value_di        (false)

/* Expression: false
 * Referenced by: '<S706>/Constant'
 */
#define rtCP_Constant_Value_ewpv       (false)

/* Expression: true
 * Referenced by: '<S733>/Constant3'
 */
#define rtCP_Constant3_Value_i4        (true)

/* Computed Parameter: rtCP_Constant_Value_lbr
 * Referenced by: '<S735>/Constant'
 */
#define rtCP_Constant_Value_lbr        (true)

/* Computed Parameter: rtCP_Constant1_Value_es
 * Referenced by: '<S735>/Constant1'
 */
#define rtCP_Constant1_Value_es        (false)

/* Computed Parameter: rtCP_Denied_Value
 * Referenced by: '<S575>/Denied'
 */
#define rtCP_Denied_Value              (true)

/* Computed Parameter: rtCP_NotDenied_Value
 * Referenced by: '<S575>/NotDenied'
 */
#define rtCP_NotDenied_Value           (false)

/* Computed Parameter: rtCP_NotDenied1_Value
 * Referenced by: '<S575>/NotDenied1'
 */
#define rtCP_NotDenied1_Value          (false)

/* Expression: false
 * Referenced by: '<S576>/Constant2'
 */
#define rtCP_Constant2_Value_co        (false)

/* Expression: false
 * Referenced by: '<S742>/Constant3'
 */
#define rtCP_Constant3_Value_pb        (false)

/* Expression: true
 * Referenced by: '<S742>/Constant5'
 */
#define rtCP_Constant5_Value_na        (true)

/* Expression: true
 * Referenced by: '<S743>/Constant'
 */
#define rtCP_Constant_Value_gl2        (true)

/* Expression: false
 * Referenced by: '<S743>/Constant1'
 */
#define rtCP_Constant1_Value_cnu       (false)

/* Expression: true
 * Referenced by: '<S2131>/true1'
 */
#define rtCP_true1_Value_k             (true)

/* Expression: true
 * Referenced by: '<S2133>/true1'
 */
#define rtCP_true1_Value_n             (true)

/* Expression: true
 * Referenced by: '<S2136>/true1'
 */
#define rtCP_true1_Value_np            (true)

/* Expression: false
 * Referenced by: '<S2089>/Constant_21'
 */
#define rtCP_Constant_21_Value         (false)

/* Expression: false
 * Referenced by: '<S2089>/Constant_3'
 */
#define rtCP_Constant_3_Value          (false)

/* Expression: false
 * Referenced by: '<S2089>/Constant_32'
 */
#define rtCP_Constant_32_Value         (false)

/* Expression: false
 * Referenced by: '<S2089>/Constant_4'
 */
#define rtCP_Constant_4_Value          (false)

/* Expression: false
 * Referenced by: '<S2089>/Constant_5'
 */
#define rtCP_Constant_5_Value          (false)

/* Expression: k_AEB_CPTA_EnCPRF_SpdCorrect
 * Referenced by: '<S2106>/Constant11'
 */
#define rtCP_Constant11_Value_do       (true)

/* Expression: k_AEB_CPTA_EnCPRF_SpdCorrect
 * Referenced by: '<S2106>/Constant13'
 */
#define rtCP_Constant13_Value_g        (true)

/* Expression: false
 * Referenced by: '<S2145>/Constant3'
 */
#define rtCP_Constant3_Value_e3        (false)

/* Expression: true
 * Referenced by: '<S2145>/Constant5'
 */
#define rtCP_Constant5_Value_nv        (true)

/* Expression: true
 * Referenced by: '<S2149>/Constant'
 */
#define rtCP_Constant_Value_cyb        (true)

/* Expression: false
 * Referenced by: '<S2149>/Constant1'
 */
#define rtCP_Constant1_Value_hs        (false)

/* Expression: true
 * Referenced by: '<S2107>/Constant'
 */
#define rtCP_Constant_Value_jbdg       (true)

/* Expression: false
 * Referenced by: '<S2107>/Constant1'
 */
#define rtCP_Constant1_Value_hg        (false)

/* Expression: true
 * Referenced by: '<S2270>/true1'
 */
#define rtCP_true1_Value_nf            (true)

/* Expression: true
 * Referenced by: '<S2272>/true1'
 */
#define rtCP_true1_Value_ec            (true)

/* Expression: true
 * Referenced by: '<S2275>/true1'
 */
#define rtCP_true1_Value_h             (true)

/* Expression: true
 * Referenced by: '<S2279>/true1'
 */
#define rtCP_true1_Value_lf            (true)

/* Expression: true
 * Referenced by: '<S2281>/true1'
 */
#define rtCP_true1_Value_he            (true)

/* Expression: true
 * Referenced by: '<S2284>/true1'
 */
#define rtCP_true1_Value_i0            (true)

/* Expression: false
 * Referenced by: '<S2326>/Constant9'
 */
#define rtCP_Constant9_Value_cw        (false)

/* Expression: false
 * Referenced by: '<S2390>/Constant'
 */
#define rtCP_Constant_Value_az1        (false)

/* Expression: false
 * Referenced by: '<S3566>/Constant1'
 */
#define rtCP_Constant1_Value_eum       (false)

/* Expression: false
 * Referenced by: '<S3566>/Constant2'
 */
#define rtCP_Constant2_Value_a4        (false)

/* Expression: true
 * Referenced by: '<S3566>/Constant3'
 */
#define rtCP_Constant3_Value_br        (true)

/* Expression: false
 * Referenced by: '<S3566>/Constant4'
 */
#define rtCP_Constant4_Value_ea        (false)

/* Computed Parameter: rtCP_Constant_Value_jm2
 * Referenced by: '<S3559>/Constant'
 */
#define rtCP_Constant_Value_jm2        (false)

/* Expression: true
 * Referenced by: '<S3560>/Constant_1'
 */
#define rtCP_Constant_1_Value_on       (true)

/* Expression: false
 * Referenced by: '<S3560>/Constant_3'
 */
#define rtCP_Constant_3_Value_k        (false)

/* Expression: true
 * Referenced by: '<S3561>/Constant_1'
 */
#define rtCP_Constant_1_Value_p3       (true)

/* Expression: false
 * Referenced by: '<S3561>/Constant_3'
 */
#define rtCP_Constant_3_Value_g        (false)

/* Expression: true
 * Referenced by: '<S3819>/true1'
 */
#define rtCP_true1_Value_bs            (true)

/* Expression: true
 * Referenced by: '<S3821>/true1'
 */
#define rtCP_true1_Value_j             (true)

/* Expression: true
 * Referenced by: '<S3824>/true1'
 */
#define rtCP_true1_Value_fx            (true)

/* Expression: false
 * Referenced by: '<S2090>/Constant_21'
 */
#define rtCP_Constant_21_Value_e       (false)

/* Expression: false
 * Referenced by: '<S2090>/Constant_3'
 */
#define rtCP_Constant_3_Value_i        (false)

/* Expression: false
 * Referenced by: '<S2090>/Constant_32'
 */
#define rtCP_Constant_32_Value_h       (false)

/* Expression: false
 * Referenced by: '<S2090>/Constant_4'
 */
#define rtCP_Constant_4_Value_d        (false)

/* Expression: false
 * Referenced by: '<S2090>/Constant_5'
 */
#define rtCP_Constant_5_Value_g        (false)

/* Expression: k_AEB_CPTA_EnCPRF_SpdCorrect
 * Referenced by: '<S3794>/Constant11'
 */
#define rtCP_Constant11_Value_l        (true)

/* Expression: k_AEB_CPTA_EnCPRF_SpdCorrect
 * Referenced by: '<S3794>/Constant13'
 */
#define rtCP_Constant13_Value_n        (true)

/* Expression: false
 * Referenced by: '<S3833>/Constant3'
 */
#define rtCP_Constant3_Value_he        (false)

/* Expression: true
 * Referenced by: '<S3833>/Constant5'
 */
#define rtCP_Constant5_Value_ak        (true)

/* Expression: true
 * Referenced by: '<S3837>/Constant'
 */
#define rtCP_Constant_Value_bu         (true)

/* Expression: false
 * Referenced by: '<S3837>/Constant1'
 */
#define rtCP_Constant1_Value_k0r       (false)

/* Expression: true
 * Referenced by: '<S3795>/Constant'
 */
#define rtCP_Constant_Value_bn0        (true)

/* Expression: false
 * Referenced by: '<S3795>/Constant1'
 */
#define rtCP_Constant1_Value_gzk       (false)

/* Expression: false
 * Referenced by: '<S5495>/Constant'
 */
#define rtCP_Constant_Value_lr         (false)

/* Expression: false
 * Referenced by: '<S5495>/Constant1'
 */
#define rtCP_Constant1_Value_hts       (false)

/* Expression: true
 * Referenced by: '<S5495>/Constant10'
 */
#define rtCP_Constant10_Value_f        (true)

/* Expression: false
 * Referenced by: '<S5495>/Constant2'
 */
#define rtCP_Constant2_Value_gb        (false)

/* Expression: true
 * Referenced by: '<S5495>/Constant3'
 */
#define rtCP_Constant3_Value_f1        (true)

/* Expression: true
 * Referenced by: '<S5495>/Constant8'
 */
#define rtCP_Constant8_Value_ah        (true)

/* Expression: true
 * Referenced by: '<S5495>/Constant9'
 */
#define rtCP_Constant9_Value_i2        (true)

/* Expression: false
 * Referenced by: '<S5498>/Constant'
 */
#define rtCP_Constant_Value_lka        (false)

/* Expression: false
 * Referenced by: '<S5498>/Constant1'
 */
#define rtCP_Constant1_Value_ka        (false)

/* Expression: false
 * Referenced by: '<S5498>/Constant2'
 */
#define rtCP_Constant2_Value_ej        (false)

/* Expression: true
 * Referenced by: '<S5498>/Constant3'
 */
#define rtCP_Constant3_Value_pv        (true)

/* Expression: false
 * Referenced by: '<S5498>/Constant4'
 */
#define rtCP_Constant4_Value_lc        (false)

/* Expression: false
 * Referenced by: '<S5498>/Constant6'
 */
#define rtCP_Constant6_Value_a         (false)

/* Expression: false
 * Referenced by: '<S5498>/Constant7'
 */
#define rtCP_Constant7_Value_ns        (false)

/* Expression: true
 * Referenced by: '<S5513>/Constant'
 */
#define rtCP_Constant_Value_mav        (true)

/* Computed Parameter: rtCP_Constant3_Value_cq
 * Referenced by: '<S5980>/Constant3'
 */
#define rtCP_Constant3_Value_cq        (true)

/* Computed Parameter: rtCP_Constant4_Value_it
 * Referenced by: '<S5980>/Constant4'
 */
#define rtCP_Constant4_Value_it        (false)

/* Expression: false
 * Referenced by: '<S5988>/false'
 */
#define rtCP_false_Value_i             (false)

/* Expression: true
 * Referenced by: '<S5988>/true'
 */
#define rtCP_true_Value_c              (true)

/* Expression: true
 * Referenced by: '<S5987>/Constant'
 */
#define rtCP_Constant_Value_lpw        (true)

/* Computed Parameter: rtCP_Constant3_Value_oa
 * Referenced by: '<S6067>/Constant3'
 */
#define rtCP_Constant3_Value_oa        (true)

/* Computed Parameter: rtCP_Constant4_Value_l2
 * Referenced by: '<S6067>/Constant4'
 */
#define rtCP_Constant4_Value_l2        (false)

/* Expression: true
 * Referenced by: '<S2097>/Constant3'
 */
#define rtCP_Constant3_Value_le        (true)

/* Expression: true
 * Referenced by: '<S2097>/Constant4'
 */
#define rtCP_Constant4_Value_hk        (true)

/* Expression: true
 * Referenced by: '<S2097>/Constant5'
 */
#define rtCP_Constant5_Value_eq        (true)

/* Expression: true
 * Referenced by: '<S2097>/Constant6'
 */
#define rtCP_Constant6_Value_ez        (true)

/* Expression: C_TRUE
 * Referenced by: '<S2097>/Constant'
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
 * Referenced by: '<S6>/Constant1'
 */
#define rtCP_Constant1_Value_f0        (true)

/* Expression: true
 * Referenced by: '<S6>/Constant11'
 */
#define rtCP_Constant11_Value_gb       (true)

/* Expression: true
 * Referenced by: '<S6>/Constant12'
 */
#define rtCP_Constant12_Value_d        (true)

/* Expression: false
 * Referenced by: '<S6>/Constant39'
 */
#define rtCP_Constant39_Value          (false)

/* Expression: true
 * Referenced by: '<S6>/Constant4'
 */
#define rtCP_Constant4_Value_en        (true)

/* Expression: true
 * Referenced by: '<S6>/Constant5'
 */
#define rtCP_Constant5_Value_ls        (true)

/* Expression: true
 * Referenced by: '<S6>/Constant7'
 */
#define rtCP_Constant7_Value_c         (true)

/* Expression: true
 * Referenced by: '<S6>/Constant8'
 */
#define rtCP_Constant8_Value_ns        (true)

/* Expression: true
 * Referenced by: '<S6133>/Constant1'
 */
#define rtCP_Constant1_Value_l3b       (true)

/* Computed Parameter: rtCP_Constant_Value_ay0
 * Referenced by: '<S6163>/Constant'
 */
#define rtCP_Constant_Value_ay0        (false)

/* Computed Parameter: rtCP_Constant_Value_eqg
 * Referenced by: '<S6164>/Constant'
 */
#define rtCP_Constant_Value_eqg        (false)

/* Expression: C_FALSE
 * Referenced by: '<S6142>/Constant11'
 */
#define rtCP_Constant11_Value_j        (false)

/* Expression: C_FALSE
 * Referenced by: '<S6142>/Constant15'
 */
#define rtCP_Constant15_Value_d        (false)

/* Expression: C_FALSE
 * Referenced by: '<S6142>/Constant23'
 */
#define rtCP_Constant23_Value_a        (false)

/* Expression: C_FALSE
 * Referenced by: '<S6142>/Constant25'
 */
#define rtCP_Constant25_Value          (false)

/* Expression: C_FALSE
 * Referenced by: '<S6142>/Constant5'
 */
#define rtCP_Constant5_Value_gr        (false)

/* Expression: C_FALSE
 * Referenced by: '<S6142>/Constant7'
 */
#define rtCP_Constant7_Value_ci        (false)

/* Expression: true
 * Referenced by: '<S6225>/Constant'
 */
#define rtCP_Constant_Value_nnq        (true)

/* Computed Parameter: rtCP_Constant_Value_j1nl
 * Referenced by: '<S6261>/Constant'
 */
#define rtCP_Constant_Value_j1nl       (false)

/* Expression: false
 * Referenced by: '<S6226>/Constant12'
 */
#define rtCP_Constant12_Value_h        (false)

/* Expression: EnEspOff_AWBActive2Passive
 * Referenced by: '<S6227>/Constant49'
 */
#define rtCP_Constant49_Value          (true)

/* Expression: EnAccPose_HBAActive2Passive
 * Referenced by: '<S6227>/Constant68'
 */
#define rtCP_Constant68_Value          (true)

/* Expression: EnWheelAngle_HBAActive2Passive
 * Referenced by: '<S6227>/Constant71'
 */
#define rtCP_Constant71_Value          (true)

/* Expression: EnNotD_HBAActive2Passive
 * Referenced by: '<S6227>/Constant74'
 */
#define rtCP_Constant74_Value          (true)

/* Computed Parameter: rtCP_ForIterator_IterationLimit_h
 * Referenced by: '<S1012>/For Iterator'
 */
#define rtCP_ForIterator_IterationLimit_h (4)

/* Computed Parameter: rtCP_true2_Value
 * Referenced by: '<S990>/true2'
 */
#define rtCP_true2_Value               (((uint8_T)1U))

/* Expression: uint8([1:4])
 * Referenced by: '<S1010>/Indices'
 */
#define rtCP_Indices_Value_EL_0        (((uint8_T)1U))
#define rtCP_Indices_Value_EL_1        (((uint8_T)2U))
#define rtCP_Indices_Value_EL_2        (((uint8_T)3U))
#define rtCP_Indices_Value_EL_3        (((uint8_T)4U))

/* Computed Parameter: rtCP_true2_Value_o
 * Referenced by: '<S1319>/true2'
 */
#define rtCP_true2_Value_o             (((uint8_T)1U))

/* Expression: uint8([1:4])
 * Referenced by: '<S1339>/Indices'
 */
#define rtCP_Indices_Value_l_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_l_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_l_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_l_EL_3      (((uint8_T)4U))

/* Computed Parameter: rtCP_true2_Value_d
 * Referenced by: '<S1815>/true2'
 */
#define rtCP_true2_Value_d             (((uint8_T)1U))

/* Expression: uint8([1:4])
 * Referenced by: '<S1835>/Indices'
 */
#define rtCP_Indices_Value_lp_EL_0     (((uint8_T)1U))
#define rtCP_Indices_Value_lp_EL_1     (((uint8_T)2U))
#define rtCP_Indices_Value_lp_EL_2     (((uint8_T)3U))
#define rtCP_Indices_Value_lp_EL_3     (((uint8_T)4U))

/* Computed Parameter: rtCP_FixPtConstant_Value
 * Referenced by: '<S5941>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value       (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition
 * Referenced by: '<S5941>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtConstant_Value_d
 * Referenced by: '<S5944>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_d     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_d
 * Referenced by: '<S5944>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_d (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtConstant_Value_a
 * Referenced by: '<S5949>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_a     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_l
 * Referenced by: '<S5949>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_l (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtConstant_Value_k
 * Referenced by: '<S789>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_k     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_p
 * Referenced by: '<S804>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_p     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_du
 * Referenced by: '<S813>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_du    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_g
 * Referenced by: '<S814>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_g     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_f
 * Referenced by: '<S820>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_f     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_p3
 * Referenced by: '<S824>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_p3    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_m
 * Referenced by: '<S829>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_m     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_o
 * Referenced by: '<S832>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_o     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_b
 * Referenced by: '<S853>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_b     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_c
 * Referenced by: '<S854>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_c     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_n
 * Referenced by: '<S867>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_n     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_mv
 * Referenced by: '<S868>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_mv    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_c4
 * Referenced by: '<S877>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_c4    (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_ih
 * Referenced by: '<S909>/Constant'
 */
#define rtCP_Constant_Value_ih         (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_pb
 * Referenced by: '<S912>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_pb    (((uint8_T)0U))

/* Expression: uint8([1:4])
 * Referenced by: '<S1770>/Indices'
 */
#define rtCP_Indices_Value_m_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_m_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_m_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_m_EL_3      (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant_Value_jrf
 * Referenced by: '<S185>/Constant'
 */
#define rtCP_Constant_Value_jrf        (((uint8_T)16U))

/* Computed Parameter: rtCP_Constant1_Value_fo
 * Referenced by: '<S185>/Constant1'
 */
#define rtCP_Constant1_Value_fo        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant10_Value_oy
 * Referenced by: '<S185>/Constant10'
 */
#define rtCP_Constant10_Value_oy       (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S185>/Constant11'
 */
#define rtCP_Constant11_Value_n        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant2_Value_hk
 * Referenced by: '<S185>/Constant2'
 */
#define rtCP_Constant2_Value_hk        (((uint8_T)4U))

/* Computed Parameter: rtCP_Constant3_Value_aj
 * Referenced by: '<S185>/Constant3'
 */
#define rtCP_Constant3_Value_aj        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant8_Value_k
 * Referenced by: '<S185>/Constant8'
 */
#define rtCP_Constant8_Value_k         (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant9_Value_ph
 * Referenced by: '<S185>/Constant9'
 */
#define rtCP_Constant9_Value_ph        (((uint8_T)8U))

/* Expression: uint8(0)
 * Referenced by: '<S313>/FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca7'
 */
#define rtCP_FCW_SteerRatThdForBrkGainHiInCllsnFwdWarnCtrl_Ca7_Value (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_jdi
 * Referenced by: '<S305>/Constant'
 */
#define rtCP_Constant_Value_jdi        (((uint8_T)16U))

/* Expression: uint8(170)
 * Referenced by: '<S40>/Constant'
 */
#define rtCP_Constant_Value_ox4        (((uint8_T)170U))

/* Expression: uint8(170)
 * Referenced by: '<S40>/Constant1'
 */
#define rtCP_Constant1_Value_mmf       (((uint8_T)170U))

/* Expression: uint8(0)
 * Referenced by: '<S398>/Constant1'
 */
#define rtCP_Constant1_Value_o0        (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S398>/Constant2'
 */
#define rtCP_Constant2_Value_op        (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S398>/Constant3'
 */
#define rtCP_Constant3_Value_h2        (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_mw
 * Referenced by: '<S477>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_mw    (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_jpo
 * Referenced by: '<S544>/Constant'
 */
#define rtCP_Constant_Value_jpo        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant1_Value_g21
 * Referenced by: '<S544>/Constant1'
 */
#define rtCP_Constant1_Value_g21       (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_ojy
 * Referenced by: '<S534>/Constant'
 */
#define rtCP_Constant_Value_ojy        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_g32
 * Referenced by: '<S454>/Constant'
 */
#define rtCP_Constant_Value_g32        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_at1
 * Referenced by: '<S455>/Constant'
 */
#define rtCP_Constant_Value_at1        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant1_Value_ep
 * Referenced by: '<S607>/Constant1'
 */
#define rtCP_Constant1_Value_ep        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_hyk
 * Referenced by: '<S587>/Constant'
 */
#define rtCP_Constant_Value_hyk        (((uint8_T)1U))

/* Expression: uint8(0)
 * Referenced by: '<S587>/Constant1'
 */
#define rtCP_Constant1_Value_goe       (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S579>/Constant1'
 */
#define rtCP_Constant1_Value_jce       (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S579>/Constant2'
 */
#define rtCP_Constant2_Value_gb4       (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S579>/Constant3'
 */
#define rtCP_Constant3_Value_fs        (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_bg
 * Referenced by: '<S630>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_bg    (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S581>/Constant1'
 */
#define rtCP_Constant1_Value_dv        (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S581>/Constant2'
 */
#define rtCP_Constant2_Value_ca        (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S581>/Constant3'
 */
#define rtCP_Constant3_Value_d2        (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_p0
 * Referenced by: '<S686>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_p0    (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S699>/Constant'
 */
#define rtCP_Constant_Value_ff         (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S699>/Constant1'
 */
#define rtCP_Constant1_Value_nxr       (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S699>/Constant2'
 */
#define rtCP_Constant2_Value_bv        (((uint8_T)0U))

/* Expression: uint8(0)
 * Referenced by: '<S699>/Constant3'
 */
#define rtCP_Constant3_Value_aon       (((uint8_T)0U))

/* Expression: uint8(2)
 * Referenced by: '<S728>/Constant3'
 */
#define rtCP_Constant3_Value_cz        (((uint8_T)2U))

/* Expression: uint8(2)
 * Referenced by: '<S729>/Constant3'
 */
#define rtCP_Constant3_Value_cy        (((uint8_T)2U))

/* Computed Parameter: rtCP_FixPtConstant_Value_e
 * Referenced by: '<S736>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_e     (((uint8_T)0U))

/* Computed Parameter: rtCP_true2_Value_b
 * Referenced by: '<S2131>/true2'
 */
#define rtCP_true2_Value_b             (((uint8_T)1U))

/* Expression: uint8(3)
 * Referenced by: '<S2089>/Constant37'
 */
#define rtCP_Constant37_Value          (((uint8_T)3U))

/* Computed Parameter: rtCP_FixPtConstant_Value_c2
 * Referenced by: '<S2208>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_c2    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_h
 * Referenced by: '<S2209>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_h     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_bm
 * Referenced by: '<S2225>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_bm    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_ax
 * Referenced by: '<S2226>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_ax    (((uint8_T)0U))

/* Computed Parameter: rtCP_true2_Value_ba
 * Referenced by: '<S2270>/true2'
 */
#define rtCP_true2_Value_ba            (((uint8_T)1U))

/* Computed Parameter: rtCP_true2_Value_h
 * Referenced by: '<S2279>/true2'
 */
#define rtCP_true2_Value_h             (((uint8_T)1U))

/* Expression: uint8([1:4])
 * Referenced by: '<S2671>/Indices'
 */
#define rtCP_Indices_Value_g_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_g_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_g_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_g_EL_3      (((uint8_T)4U))

/* Expression: uint8([1:4])
 * Referenced by: '<S3231>/Indices'
 */
#define rtCP_Indices_Value_e_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_e_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_e_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_e_EL_3      (((uint8_T)4U))

/* Computed Parameter: rtCP_true2_Value_n
 * Referenced by: '<S3819>/true2'
 */
#define rtCP_true2_Value_n             (((uint8_T)1U))

/* Expression: uint8(3)
 * Referenced by: '<S2090>/Constant37'
 */
#define rtCP_Constant37_Value_k        (((uint8_T)3U))

/* Computed Parameter: rtCP_FixPtConstant_Value_n1
 * Referenced by: '<S3896>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_n1    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_cz
 * Referenced by: '<S3897>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_cz    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_ex
 * Referenced by: '<S3913>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_ex    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_ah
 * Referenced by: '<S3914>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_ah    (((uint8_T)0U))

/* Expression: uint8([1:4])
 * Referenced by: '<S4359>/Indices'
 */
#define rtCP_Indices_Value_j_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_j_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_j_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_j_EL_3      (((uint8_T)4U))

/* Expression: uint8([1:4])
 * Referenced by: '<S4919>/Indices'
 */
#define rtCP_Indices_Value_n_EL_0      (((uint8_T)1U))
#define rtCP_Indices_Value_n_EL_1      (((uint8_T)2U))
#define rtCP_Indices_Value_n_EL_2      (((uint8_T)3U))
#define rtCP_Indices_Value_n_EL_3      (((uint8_T)4U))

/* Expression: uint8(3)
 * Referenced by: '<S5476>/Constant55'
 */
#define rtCP_Constant55_Value          (((uint8_T)3U))

/* Expression: uint8(3)
 * Referenced by: '<S5477>/Constant55'
 */
#define rtCP_Constant55_Value_e        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant_Value_ffg
 * Referenced by: '<S5496>/Constant'
 */
#define rtCP_Constant_Value_ffg        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_lxr
 * Referenced by: '<S5497>/Constant'
 */
#define rtCP_Constant_Value_lxr        (((uint8_T)1U))

/* Expression: uint8(0)
 * Referenced by: '<S2092>/Constant1'
 */
#define rtCP_Constant1_Value_on        (((uint8_T)0U))

/* Expression: const
 * Referenced by: '<S5508>/Constant'
 */
#define rtCP_Constant_Value_dhs        (((uint8_T)4U))

/* Expression: const
 * Referenced by: '<S5509>/Constant'
 */
#define rtCP_Constant_Value_eea        (((uint8_T)2U))

/* Expression: const
 * Referenced by: '<S5510>/Constant'
 */
#define rtCP_Constant_Value_p1g        (((uint8_T)3U))

/* Computed Parameter: rtCP_FixPtConstant_Value_p2
 * Referenced by: '<S5608>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_p2    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_mx
 * Referenced by: '<S5620>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_mx    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_a4
 * Referenced by: '<S5621>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_a4    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_do
 * Referenced by: '<S5624>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_do    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_gr
 * Referenced by: '<S5633>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_gr    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_m3
 * Referenced by: '<S5634>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_m3    (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_pam
 * Referenced by: '<S5645>/Constant'
 */
#define rtCP_Constant_Value_pam        (((uint8_T)5U))

/* Computed Parameter: rtCP_FixPtConstant_Value_hi
 * Referenced by: '<S5692>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_hi    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_ps
 * Referenced by: '<S5693>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_ps    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_pa
 * Referenced by: '<S5694>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_pa    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_hd
 * Referenced by: '<S5739>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_hd    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_ev
 * Referenced by: '<S5740>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_ev    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_pl
 * Referenced by: '<S5741>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_pl    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_ab
 * Referenced by: '<S5933>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_ab    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_ow
 * Referenced by: '<S5935>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_ow    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_hv
 * Referenced by: '<S5937>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_hv    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_hr
 * Referenced by: '<S5939>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_hr    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_i
 * Referenced by: '<S5951>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_i     (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_fh
 * Referenced by: '<S5982>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_fh    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_br
 * Referenced by: '<S5983>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_br    (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_j
 * Referenced by: '<S6068>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_j     (((uint8_T)0U))

/* Expression: uint8(3)
 * Referenced by: '<S6080>/Constant'
 */
#define rtCP_Constant_Value_mqx        (((uint8_T)3U))

/* Expression: uint8(2)
 * Referenced by: '<S6080>/Constant1'
 */
#define rtCP_Constant1_Value_h4        (((uint8_T)2U))

/* Expression: uint8(1)
 * Referenced by: '<S6080>/Constant2'
 */
#define rtCP_Constant2_Value_fx        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant_Value_gxip
 * Referenced by: '<S6119>/Constant'
 */
#define rtCP_Constant_Value_gxip       (((uint8_T)0U))

/* Computed Parameter: rtCP_FixPtConstant_Value_l
 * Referenced by: '<S6154>/FixPt Constant'
 */
#define rtCP_FixPtConstant_Value_l     (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant1_Value_pw
 * Referenced by: '<S6155>/Constant1'
 */
#define rtCP_Constant1_Value_pw        (((uint8_T)7U))

/* Computed Parameter: rtCP_Constant2_Value_h0
 * Referenced by: '<S6155>/Constant2'
 */
#define rtCP_Constant2_Value_h0        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant3_Value_jv
 * Referenced by: '<S6155>/Constant3'
 */
#define rtCP_Constant3_Value_jv        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant4_Value_gz
 * Referenced by: '<S6155>/Constant4'
 */
#define rtCP_Constant4_Value_gz        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant5_Value_h1
 * Referenced by: '<S6155>/Constant5'
 */
#define rtCP_Constant5_Value_h1        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant6_Value_mu
 * Referenced by: '<S6155>/Constant6'
 */
#define rtCP_Constant6_Value_mu        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6142>/Constant10'
 */
#define rtCP_Constant10_Value_g        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6142>/Constant12'
 */
#define rtCP_Constant12_Value_c        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6142>/Constant16'
 */
#define rtCP_Constant16_Value_m        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6142>/Constant17'
 */
#define rtCP_Constant17_Value_g        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6142>/Constant19'
 */
#define rtCP_Constant19_Value_i        (((uint8_T)0U))

/* Expression: C_ZERO
 * Referenced by: '<S6142>/Constant2'
 */
#define rtCP_Constant2_Value_oo        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_h0z
 * Referenced by: '<S6165>/Constant'
 */
#define rtCP_Constant_Value_h0z        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant1_Value_m0
 * Referenced by: '<S6165>/Constant1'
 */
#define rtCP_Constant1_Value_m0        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant2_Value_lvy
 * Referenced by: '<S6165>/Constant2'
 */
#define rtCP_Constant2_Value_lvy       (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant6_Value_n5
 * Referenced by: '<S6165>/Constant6'
 */
#define rtCP_Constant6_Value_n5        (((uint8_T)2U))

/* Expression: const
 * Referenced by: '<S6183>/Constant'
 */
#define rtCP_Constant_Value_nab        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant1_Value_atl
 * Referenced by: '<S6170>/Constant1'
 */
#define rtCP_Constant1_Value_atl       (((uint8_T)7U))

/* Computed Parameter: rtCP_Constant2_Value_db
 * Referenced by: '<S6170>/Constant2'
 */
#define rtCP_Constant2_Value_db        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant3_Value_ky
 * Referenced by: '<S6170>/Constant3'
 */
#define rtCP_Constant3_Value_ky        (((uint8_T)6U))

/* Computed Parameter: rtCP_Constant4_Value_hc
 * Referenced by: '<S6170>/Constant4'
 */
#define rtCP_Constant4_Value_hc        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant5_Value_d3
 * Referenced by: '<S6170>/Constant5'
 */
#define rtCP_Constant5_Value_d3        (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant6_Value_jk
 * Referenced by: '<S6170>/Constant6'
 */
#define rtCP_Constant6_Value_jk        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant2_Value_d0
 * Referenced by: '<S6203>/Constant2'
 */
#define rtCP_Constant2_Value_d0        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant44_Value_c
 * Referenced by: '<S6203>/Constant44'
 */
#define rtCP_Constant44_Value_c        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant1_Value_iai
 * Referenced by: '<S6202>/Constant1'
 */
#define rtCP_Constant1_Value_iai       (((uint8_T)1U))

/* Computed Parameter: rtCP_Constant10_Value_m
 * Referenced by: '<S6202>/Constant10'
 */
#define rtCP_Constant10_Value_m        (((uint8_T)3U))

/* Computed Parameter: rtCP_Constant2_Value_kj
 * Referenced by: '<S6202>/Constant2'
 */
#define rtCP_Constant2_Value_kj        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant44_Value_b
 * Referenced by: '<S6202>/Constant44'
 */
#define rtCP_Constant44_Value_b        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_poe
 * Referenced by: '<S6224>/Constant'
 */
#define rtCP_Constant_Value_poe        (((uint8_T)0U))

/* Computed Parameter: rtCP_Constant_Value_cvd
 * Referenced by: '<S6235>/Constant'
 */
#define rtCP_Constant_Value_cvd        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_oq1
 * Referenced by: '<S6270>/Constant'
 */
#define rtCP_Constant_Value_oq1        (((uint8_T)2U))

/* Computed Parameter: rtCP_Constant_Value_ouv
 * Referenced by: '<S6287>/Constant'
 */
#define rtCP_Constant_Value_ouv        (((uint8_T)11U))

/* Expression: const
 * Referenced by: '<S6289>/Constant'
 */
#define rtCP_Constant_Value_dby        (((uint8_T)2U))

/* Expression: uint8(1)
 * Referenced by: '<S5488>/Delay'
 */
#define rtCP_Delay_InitialCondition_f  (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_k
 * Referenced by: '<S5608>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_k (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_kv
 * Referenced by: '<S5624>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_kv (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_ls
 * Referenced by: '<S5633>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_ls (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_p
 * Referenced by: '<S5634>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_p (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_g
 * Referenced by: '<S5620>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_g (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_b
 * Referenced by: '<S5621>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_b (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_n
 * Referenced by: '<S5694>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_n (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_i
 * Referenced by: '<S5692>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_i (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_pq
 * Referenced by: '<S5693>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_pq (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_l3
 * Referenced by: '<S2208>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_l3 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_pe
 * Referenced by: '<S5935>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_pe (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_km
 * Referenced by: '<S5951>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_km (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_f
 * Referenced by: '<S2209>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_f (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_nw
 * Referenced by: '<S5939>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_nw (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_o
 * Referenced by: '<S2225>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_o (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_d3
 * Referenced by: '<S2226>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_d3 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_ld
 * Referenced by: '<S5933>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_ld (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_e
 * Referenced by: '<S789>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_e (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_c
 * Referenced by: '<S804>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_c (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_kmi
 * Referenced by: '<S832>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_kmi (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_dm
 * Referenced by: '<S824>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_dm (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_dw
 * Referenced by: '<S813>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_dw (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_l5
 * Referenced by: '<S814>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_l5 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_cl
 * Referenced by: '<S820>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_cl (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_pt
 * Referenced by: '<S877>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_pt (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_pn
 * Referenced by: '<S853>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_pn (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_j
 * Referenced by: '<S854>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_j (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_cg
 * Referenced by: '<S829>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_cg (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_it
 * Referenced by: '<S867>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_it (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_m
 * Referenced by: '<S868>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_m (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_kw
 * Referenced by: '<S912>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_kw (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_l1
 * Referenced by: '<S5741>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_l1 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_mp
 * Referenced by: '<S5739>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_mp (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_lz
 * Referenced by: '<S5740>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_lz (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_fb
 * Referenced by: '<S3896>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_fb (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_bd
 * Referenced by: '<S3897>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_bd (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_ox
 * Referenced by: '<S3913>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_ox (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_mz
 * Referenced by: '<S3914>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_mz (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_b3
 * Referenced by: '<S6068>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_b3 (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_pez
 * Referenced by: '<S736>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_pez (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_oa
 * Referenced by: '<S630>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_oa (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_ma
 * Referenced by: '<S686>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_ma (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_ce
 * Referenced by: '<S477>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_ce (((uint8_T)1U))

/* Expression: BitMask
 * Referenced by: '<S219>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask (((uint8_T)2U))

/* Expression: BitMask
 * Referenced by: '<S221>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_n (((uint8_T)4U))

/* Expression: BitMask
 * Referenced by: '<S223>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_f (((uint8_T)8U))

/* Expression: BitMask
 * Referenced by: '<S225>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_m (((uint8_T)16U))

/* Expression: BitMask
 * Referenced by: '<S227>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_nd (((uint8_T)32U))

/* Expression: BitMask
 * Referenced by: '<S229>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_o (((uint8_T)64U))

/* Expression: BitMask
 * Referenced by: '<S231>/FixPt Bitwise Operator1'
 */
#define rtCP_FixPtBitwiseOperator1_BitMask_j (((uint8_T)128U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_h
 * Referenced by: '<S5937>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_h (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_bo
 * Referenced by: '<S5983>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_bo (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_hi
 * Referenced by: '<S5982>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_hi (((uint8_T)1U))

/* Expression: BitMask
 * Referenced by: '<S6238>/Bitwise Operator2'
 */
#define rtCP_BitwiseOperator2_BitMask  (((uint8_T)4U))

/* Expression: BitMask
 * Referenced by: '<S6238>/Bitwise Operator1'
 */
#define rtCP_BitwiseOperator1_BitMask  (((uint8_T)2U))

/* Expression: BitMask
 * Referenced by: '<S6238>/Bitwise Operator'
 */
#define rtCP_BitwiseOperator_BitMask   (((uint8_T)1U))

/* Computed Parameter: rtCP_FixPtUnitDelay2_InitialCondition_ow
 * Referenced by: '<S6154>/FixPt Unit Delay2'
 */
#define rtCP_FixPtUnitDelay2_InitialCondition_ow (((uint8_T)1U))

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
extern real32_T LongSafe_SWC_DSE_TimeCountUp(boolean_T rtu_reset, real32_T
  rtu_increment, DW_DSE_TimeCountUp_LongSafe_SWC_T *localDW);
extern real32_T LongSafe_SWC_DSE_CalcPredDrvrDecel(real32_T rtu_VehicleSpeed,
  real32_T rtu_Slope, real32_T rtu_Offset, real32_T
  rtu_PredictedAccelerationLimit);
extern real32_T LongSafe_SWC_DSE_CalcPredDrvrDecel_d(real32_T rtu_VehicleSpeed,
  real32_T rtu_Slope, real32_T rtu_Offset, real32_T
  rtu_predictedDecelerationLimit);
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
