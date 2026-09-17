/*
 * File: LongSafe_SWC_data.c
 *
 * Code generated for Simulink model 'LongSafe_SWC'.
 *
 * Model version                  : 7.3245
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Mon Jun 29 11:49:25 2026
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

#include "LongSafe_SWC.h"
#include "LongSafe_SWC_private.h"

/* Invariant block signals (default storage) */
const ConstB_LongSafe_SWC_T LongSafe_SWC_ConstB = {
  /* Start of '<Root>/AEB' */
  {
    /* Start of '<S1>/Ltap' */
    {
      /* Start of '<S2>/AEB' */
      {
        {
          0U,
          0U,
          0.0F,
          0,
          0,
          0,
          0,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          100.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0U,
          0U,
          0U,
          0U,
          false,
          false,
          false,
          false,
          false,
          0U,
          0U
        },                             /* '<S6138>/Bus Assignment1' */

        {
          0U,
          0U,
          0.0F,
          0,
          0,
          0,
          0,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          100.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0.0F,
          0U,
          0U,
          0U,
          0U,
          false,
          false,
          false,
          false,
          false,
          0U,
          0U
        },                             /* '<S6185>/Bus Assignment1' */
        0.01,                          /* '<S1078>/Abs2' */
        0.01,                          /* '<S1078>/Abs3' */
        0.01,                          /* '<S1078>/Abs4' */
        6.28318548F,                   /* '<S2212>/Gain_1' */
        -1.0E+10F,                     /* '<S2223>/Gain' */
        6.28318548F,                   /* '<S2246>/Gain_1' */
        0.0F,                          /* '<S1382>/Signal Conversion' */
        0.02F,                         /* '<S1389>/Divide' */
        0.0F,                          /* '<S1389>/Product' */
        0.0F,                          /* '<S1389>/Saturation' */
        0.0F,                          /* '<S124>/ConvertALV' */
        0.0F,                          /* '<S122>/Signal Conversion' */
        -0.0001F,                      /* '<S606>/Unary Minus' */
        6.28318548F,                   /* '<S742>/Gain_1' */
        6.28318548F,                   /* '<S755>/Gain_1' */
        0.0F,                          /* '<S900>/Gain_1' */
        0.0F,                          /* '<S900>/Gain_2' */
        0.0F,                          /* '<S905>/Product7' */
        0.0F,                          /* '<S905>/Product8' */
        0.0F,                          /* '<S905>/Add2' */
        0.0F,                          /* '<S900>/Gain_3' */
        0.0F,                          /* '<S900>/Gain_4' */
        0.0F,                          /* '<S906>/Product7' */
        0.0F,                          /* '<S906>/Product8' */
        0.0F,                          /* '<S906>/Add2' */
        0.0F,                          /* '<S900>/Gain_5' */
        0.0F,                          /* '<S900>/Gain_6' */
        0.0F,                          /* '<S903>/Signal Conversion' */
        0.0F,                          /* '<S905>/Product3' */
        0.0F,                          /* '<S905>/Product9' */
        0.0F,                          /* '<S905>/Product4' */
        0.0F,                          /* '<S905>/Add1' */
        0.0F,                          /* '<S905>/Product' */
        0.0F,                          /* '<S905>/Product1' */
        0.0F,                          /* '<S905>/Product10' */
        0.0F,                          /* '<S905>/Product2' */
        0.0F,                          /* '<S906>/Product3' */
        0.0F,                          /* '<S906>/Product9' */
        0.0F,                          /* '<S906>/Product4' */
        0.0F,                          /* '<S906>/Add1' */
        0.0F,                          /* '<S906>/Product' */
        0.0F,                          /* '<S906>/Product1' */
        0.0F,                          /* '<S906>/Product10' */
        0.0F,                          /* '<S906>/Product2' */
        0.0F,                          /* '<S907>/Product3' */
        0.0F,                          /* '<S907>/Product9' */
        0.0F,                          /* '<S907>/Product4' */
        0.0F,                          /* '<S907>/Add1' */
        0.0F,                          /* '<S907>/Product7' */
        0.0F,                          /* '<S907>/Product8' */
        0.0F,                          /* '<S907>/Add2' */
        0.0F,                          /* '<S907>/Product' */
        0.0F,                          /* '<S907>/Product1' */
        0.0F,                          /* '<S907>/Product10' */
        0.0F,                          /* '<S907>/Product2' */
        -0.0F,                         /* '<S901>/Gain_1' */
        0.0F,                          /* '<S901>/Abs' */
        0.0F,                          /* '<S901>/Gain_3' */
        0.0F,                          /* '<S901>/Sign' */
        0.0F,                          /* '<S902>/Sum of Elements' */
        9.0F,                          /* '<S909>/Square' */
        0.0F,                          /* '<S898>/Sum of Elements1' */
        0.0F,                          /* '<S898>/Sum of Elements' */
        50.0F,                         /* '<S978>/FrqFctCallInDrvrStEstimr' */
        0.08F,                         /* '<S1199>/Product1' */
        -9.8F,                         /* '<S1176>/Times' */
        1.57142854F,                   /* '<S1189>/Product2' */
        -15.0F,                        /* '<S1181>/Signal Conversion' */
        0.0F,                          /* '<S1131>/Signal Conversion' */
        -1.0E+10F,                     /* '<S2676>/Gain' */
        -1.0E+10F,                     /* '<S2677>/Gain' */
        -1.0E+10F,                     /* '<S2732>/Gain' */
        -1.0E+10F,                     /* '<S2733>/Gain' */
        -1.0E+10F,                     /* '<S2758>/Gain' */
        -1.0E+10F,                     /* '<S2759>/Gain' */
        -1.0E+10F,                     /* '<S2851>/Gain' */
        -1.0E+10F,                     /* '<S2852>/Gain' */
        -1.0E+10F,                     /* '<S2860>/Gain' */
        -1.0E+10F,                     /* '<S2861>/Gain' */
        -1.0E+10F,                     /* '<S2869>/Gain' */
        -1.0E+10F,                     /* '<S2870>/Gain' */
        -1.0E+10F,                     /* '<S2878>/Gain' */
        -1.0E+10F,                     /* '<S2879>/Gain' */
        -1.0E+10F,                     /* '<S4043>/Gain' */
        -1.0E+10F,                     /* '<S4044>/Gain' */
        -1.0E+10F,                     /* '<S4271>/Gain' */
        -1.0E+10F,                     /* '<S4272>/Gain' */
        -1.0E+10F,                     /* '<S4353>/Gain' */
        -1.0E+10F,                     /* '<S4354>/Gain' */
        -1.0E+10F,                     /* '<S4409>/Gain' */
        -1.0E+10F,                     /* '<S4410>/Gain' */
        -1.0E+10F,                     /* '<S4435>/Gain' */
        -1.0E+10F,                     /* '<S4436>/Gain' */
        -1.0E+10F,                     /* '<S4528>/Gain' */
        -1.0E+10F,                     /* '<S4529>/Gain' */
        -1.0E+10F,                     /* '<S4537>/Gain' */
        -1.0E+10F,                     /* '<S4538>/Gain' */
        -1.0E+10F,                     /* '<S4546>/Gain' */
        -1.0E+10F,                     /* '<S4547>/Gain' */
        -1.0E+10F,                     /* '<S4555>/Gain' */
        -1.0E+10F,                     /* '<S4556>/Gain' */
        -1.0E+10F,                     /* '<S5720>/Gain' */
        -1.0E+10F,                     /* '<S5721>/Gain' */
        -1.0E+10F,                     /* '<S5948>/Gain' */
        -1.0E+10F,                     /* '<S5949>/Gain' */
        0.0F,                          /* '<S2601>/Constant' */
        1.0F,                          /* '<S5976>/Cast1' */
        0.0F,                          /* '<S5976>/Cast7' */
        0.0F,                          /* '<S5976>/Cast8' */
        0.0F,                          /* '<S5976>/Cast9' */
        0.0F,                          /* '<S6125>/Signal Conversion' */
        255.0F,                        /* '<S6297>/Data Type Conversion' */
        -1.0E+10F,                     /* '<S2522>/Gain' */
        -1.0E+10F,                     /* '<S1959>/Gain' */
        -1.0E+10F,                     /* '<S1630>/Gain' */
        9.0F,                          /* '<S950>/Square' */
        0.0F,                          /* '<S952>/Sum of Elements1' */
        0.0F,                          /* '<S952>/Sum of Elements' */
        SnsrDataSts1Vcc_Fusn,          /* '<S2599>/Data Type Conversion8' */
        SnsrDataSts1Vcc_Fusn,          /* '<S2600>/Data Type Conversion8' */
        SnsrDataSts1Vcc_Fusn,          /* '<S5963>/Data Type Conversion21' */
        SnsrDataSts1Vcc_Fusn,          /* '<S5964>/Data Type Conversion21' */
        Side1Vcc_Re,                   /* '<S2599>/Data Type Conversion' */
        Side1Vcc_Re,                   /* '<S2600>/Data Type Conversion' */
        Side1Vcc_Re,                   /* '<S5963>/Data Type Conversion23' */
        Side1Vcc_Re,                   /* '<S5964>/Data Type Conversion23' */
        Relbl4Vcc_BrkgRelbl,           /* '<S2599>/Data Type Conversion11' */
        Relbl4Vcc_BrkgRelbl,           /* '<S2600>/Data Type Conversion11' */
        Relbl4Vcc_BrkgRelbl,           /* '<S5963>/Data Type Conversion6' */
        Relbl4Vcc_BrkgRelbl,           /* '<S5964>/Data Type Conversion6' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S2599>/Data Type Conversion15' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S2600>/Data Type Conversion15' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S5963>/Data Type Conversion19' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S5964>/Data Type Conversion19' */
        Relbl1Vcc_Relbl,               /* '<S2599>/Data Type Conversion12' */
        Relbl1Vcc_Relbl,               /* '<S2600>/Data Type Conversion12' */
        Relbl1Vcc_Relbl,               /* '<S5963>/Data Type Conversion7' */
        Relbl1Vcc_Relbl,               /* '<S5964>/Data Type Conversion7' */
        OnOff1Vcc_On,                  /* '<S116>/ConvertALV' */
        OnOff1_On,                     /* '<S10>/Constant23' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S2599>/Data Type Conversion10' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S2600>/Data Type Conversion10' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S5963>/Data Type Conversion4' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S5964>/Data Type Conversion4' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S2599>/Data Type Conversion14' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S2600>/Data Type Conversion14' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S5963>/Data Type Conversion18' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S5964>/Data Type Conversion18' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S2599>/Data Type Conversion9' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S2600>/Data Type Conversion9' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S5963>/Data Type Conversion22' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S5964>/Data Type Conversion22' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S2599>/Data Type Conversion16' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S2600>/Data Type Conversion16' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S5963>/Data Type Conversion20' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S5964>/Data Type Conversion20' */
        ObjMtnPatHist1Vcc_Ukwn,        /* '<S2599>/Data Type Conversion5' */
        ObjMtnPatHist1Vcc_Ukwn,        /* '<S2600>/Data Type Conversion5' */
        NoYes1_No,                     /* '<S5982>/Data Type Conversion' */
        NoYes1_Yes,                    /* '<S5972>/Data Type Conversion1' */
        NoYes1_Yes,                    /* '<S5990>/Signal Conversion' */
        LiSts1Vcc_Off,                 /* '<S2599>/Data Type Conversion2' */
        LiSts1Vcc_Off,                 /* '<S2599>/Data Type Conversion3' */
        LiSts1Vcc_Off,                 /* '<S2600>/Data Type Conversion2' */
        LiSts1Vcc_Off,                 /* '<S2600>/Data Type Conversion3' */
        LiSts1Vcc_Ukwn,                /* '<S5963>/Data Type Conversion25' */
        LiSts1Vcc_Ukwn,                /* '<S5963>/Data Type Conversion26' */
        LiSts1Vcc_Ukwn,                /* '<S5964>/Data Type Conversion25' */
        LiSts1Vcc_Ukwn,                /* '<S5964>/Data Type Conversion26' */
        IndcrTypExt1_Off,              /* '<S971>/Signal Conversion' */
        IndcrTurn1Vcc_Le,              /* '<S2599>/Data Type Conversion1' */
        IndcrTurn1Vcc_Le,              /* '<S2600>/Data Type Conversion1' */
        IndcrTurn1Vcc_NoIndcn,         /* '<S5963>/Data Type Conversion24' */
        IndcrTurn1Vcc_NoIndcn,         /* '<S5964>/Data Type Conversion24' */
        IdPen_Prof1,                   /* '<S5975>/Data Type Conversion' */
        IdPen_Prof1,                   /* '<S5992>/Signal Conversion' */
        GenQf1_TmpUndefdData,          /* '<S5977>/Data Type Conversion' */
        GenQf1_TmpUndefdData,          /* '<S6126>/Signal Conversion' */
        GenQf1_DataAccurNotWithinSpcn, /* '<S5972>/Data Type Conversion2' */
        GenQf1_DataAccurNotWithinSpcn, /* '<S5987>/Signal Conversion' */
        GenQf1_DataAccurNotWithinSpcn, /* '<S184>/ConvertALV' */
        GenQf1_TmpUndefdData,          /* '<S6124>/Signal Conversion' */
        GenQf1_TmpUndefdData,          /* '<S6129>/Signal Conversion' */
        DynCalPrmForAccStopNGo0_Yes,   /* '<S153>/ConvertALV' */
        AsyBltLvl1Vcc_NoActvn,         /* '<S48>/Switch1' */
        AsyBltLvl1Vcc_NoActvn,         /* '<S380>/ConvertALV' */
        ActtnDataFromCllsnRednByBrkgCtrl1VccSteerGainEna0_FALSE,/* '<S411>/Switch' */
        AEB_ACTIVE,                    /* '<S6337>/Data Type Conversion' */
        0U,                            /* '<S199>/Conversion3' */
        200U,                          /* '<S199>/Add2' */
        4U,                            /* '<S2106>/Width' */
        4U,                            /* '<S2280>/Width' */
        0U,                            /* '<S108>/ConvertALV' */
        0U,                            /* '<S79>/Signal Conversion' */
        0U,                            /* '<S155>/ConvertALV' */
        0U,                            /* '<S165>/ConvertALV' */
        1U,                            /* '<S46>/Data Type Conversion' */
        0U,                            /* '<S149>/Signal Conversion' */
        0U,                            /* '<S151>/Signal Conversion' */
        0U,                            /* '<S192>/Data Type Conversion3' */
        0U,                            /* '<S193>/Switch3' */
        100U,                          /* '<S467>/Add' */
        4U,                            /* '<S3169>/Width' */
        4U,                            /* '<S3729>/Width' */
        4U,                            /* '<S4846>/Width' */
        4U,                            /* '<S5406>/Width' */
        1U,                            /* '<S5988>/Signal Conversion' */
        1U,                            /* '<S5989>/Signal Conversion' */
        1U,                            /* '<S6123>/Signal Conversion' */
        1U,                            /* '<S6128>/Signal Conversion' */
        1U,                            /* '<S6131>/Signal Conversion' */
        1U,                            /* '<S6132>/Signal Conversion' */
        1U,                            /* '<S5982>/Constant1' */
        1U,                            /* '<S5982>/Constant2' */
        1U,                            /* '<S2606>/Data Type Conversion24' */
        1U,                            /* '<S2606>/Data Type Conversion' */
        0U,                            /* '<S2606>/Data Type Conversion16' */
        4U,                            /* '<S2345>/Width' */
        4U,                            /* '<S2128>/Width' */
        4U,                            /* '<S1782>/Width' */
        4U,                            /* '<S1453>/Width' */
        0,                             /* '<S732>/Multiport Switch' */
        0,                             /* '<S732>/Sign' */
        1,                             /* '<S732>/Switch1' */
        1,                             /* '<S732>/Switch' */
        0,                             /* '<S2143>/Data Type Conversion' */
        0,                             /* '<S1402>/Relational Operator1' */
        0,                             /* '<S42>/Relational Operator1' */
        1,                             /* '<S44>/Relational Operator' */
        0,                             /* '<S192>/Logical Operator' */
        0,                             /* '<S600>/Logical Operator3' */
        0,                             /* '<S687>/Data Type Conversion' */
        0,                             /* '<S714>/Data Type Conversion' */
        0,                             /* '<S732>/Relational Operator3' */
        0,                             /* '<S732>/Relational Operator1' */
        0,                             /* '<S732>/Logical Operator' */
        1,                             /* '<S732>/Relational Operator5' */
        0,                             /* '<S765>/Data Type Conversion' */
        1,                             /* '<S596>/Relational Operator6' */
        0,                             /* '<S596>/Relational Operator' */
        0,                             /* '<S596>/Logical Operator3' */
        0,                             /* '<S414>/Multiport Switch' */
        1,                             /* '<S417>/Relational Operator' */
        0,                             /* '<S902>/Relop_1' */
        0,                             /* '<S1083>/Data Type Conversion' */
        0,                             /* '<S1084>/Data Type Conversion' */
        0,                             /* '<S1085>/Data Type Conversion' */
        0,                             /* '<S1044>/Constant' */
        0,                             /* '<S1089>/Multiport Switch' */
        1,                             /* '<S1089>/Relational Operator2' */
        0,                             /* '<S1089>/Logical Operator' */
        0,                             /* '<S1105>/Signal Conversion' */
        1,                             /* '<S2602>/Constant' */
        0,                             /* '<S6236>/Data Type Conversion' */
        0,                             /* '<S6242>/Logical Operator' */
        0,                             /* '<S6251>/Logical Operator1' */
        0,                             /* '<S6260>/Logical Operator' */
        1,                             /* '<S6261>/Logical Operator1' */
        1,                             /* '<S6270>/Logical Operator1' */
        0,                             /* '<S6279>/Logical Operator2' */
        0,                             /* '<S6279>/Logical Operator3' */
        1,                             /* '<S6394>/Logical Operator13' */
        0,                             /* '<S6394>/Logical Operator26' */
        1,                             /* '<S6394>/Logical Operator4' */
        1,                             /* '<S6394>/Logical Operator5' */
        1,                             /* '<S6394>/Logical Operator6' */
        0,                             /* '<S1071>/Data Type Conversion' */
        0,                             /* '<S1028>/Rel5' */
        0,                             /* '<S1028>/Rel6' */

        /* Start of '<S5749>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S5901>/Gain' */
          -1.0E+10F,                   /* '<S5908>/Gain' */
          -1.0E+10F,                   /* '<S5880>/Gain' */
          -1.0E+10F,                   /* '<S5887>/Gain' */
          -1.0E+10F,                   /* '<S5859>/Gain' */
          -1.0E+10F                    /* '<S5866>/Gain' */
        }
        ,

        /* End of '<S5749>/CalculateTTI' */

        /* Start of '<S5748>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S5812>/Gain' */
          -1.0E+10F,                   /* '<S5819>/Gain' */
          -1.0E+10F,                   /* '<S5791>/Gain' */
          -1.0E+10F,                   /* '<S5798>/Gain' */
          -1.0E+10F,                   /* '<S5770>/Gain' */
          -1.0E+10F                    /* '<S5777>/Gain' */
        }
        ,

        /* End of '<S5748>/CalculateTTI' */

        /* Start of '<S5621>/MovingObject' */
        {
          3.14159274F,                 /* '<S5627>/Gain_1' */
          6.28318548F                  /* '<S5628>/Gain_1' */
        }
        ,

        /* End of '<S5621>/MovingObject' */

        /* Start of '<S5612>/MovingObject' */
        {
          3.14159274F,                 /* '<S5618>/Gain_1' */
          6.28318548F                  /* '<S5619>/Gain_1' */
        }
        ,

        /* End of '<S5612>/MovingObject' */

        /* Start of '<S5603>/MovingObject' */
        {
          3.14159274F,                 /* '<S5609>/Gain_1' */
          6.28318548F                  /* '<S5610>/Gain_1' */
        }
        ,

        /* End of '<S5603>/MovingObject' */

        /* Start of '<S5594>/MovingObject' */
        {
          3.14159274F,                 /* '<S5600>/Gain_1' */
          6.28318548F                  /* '<S5601>/Gain_1' */
        }
        ,

        /* End of '<S5594>/MovingObject' */

        /* Start of '<S5585>/MovingObject' */
        {
          6.28318548F,                 /* '<S5591>/Gain_1' */
          6.28318548F                  /* '<S5592>/Gain_1' */
        }
        ,

        /* End of '<S5585>/MovingObject' */

        /* Start of '<S5406>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S5418>/Width' */
        }
        ,

        /* End of '<S5406>/ForEachSegmentInPahEstimn' */

        /* Start of '<S5138>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S5166>/Gain' */
          -1.0E+10F,                   /* '<S5188>/Gain' */
          -1.0E+10F,                   /* '<S5212>/Gain' */
          -1.0E+10F,                   /* '<S5236>/Gain' */
          -1.0E+10F                    /* '<S5257>/Gain' */
        }
        ,

        /* End of '<S5138>/CircularPrediction' */

        /* Start of '<S5055>/MovingObject' */
        {
          3.14159274F,                 /* '<S5061>/Gain_1' */
          6.28318548F                  /* '<S5062>/Gain_1' */
        }
        ,

        /* End of '<S5055>/MovingObject' */

        /* Start of '<S5046>/MovingObject' */
        {
          3.14159274F,                 /* '<S5052>/Gain_1' */
          6.28318548F                  /* '<S5053>/Gain_1' */
        }
        ,

        /* End of '<S5046>/MovingObject' */

        /* Start of '<S5037>/MovingObject' */
        {
          3.14159274F,                 /* '<S5043>/Gain_1' */
          6.28318548F                  /* '<S5044>/Gain_1' */
        }
        ,

        /* End of '<S5037>/MovingObject' */

        /* Start of '<S5028>/MovingObject' */
        {
          3.14159274F,                 /* '<S5034>/Gain_1' */
          6.28318548F                  /* '<S5035>/Gain_1' */
        }
        ,

        /* End of '<S5028>/MovingObject' */

        /* Start of '<S5019>/MovingObject' */
        {
          3.14159274F,                 /* '<S5025>/Gain_1' */
          6.28318548F                  /* '<S5026>/Gain_1' */
        }
        ,

        /* End of '<S5019>/MovingObject' */

        /* Start of '<S4846>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S4858>/Width' */
        }
        ,

        /* End of '<S4846>/ForEachSegmentInPahEstimn' */

        /* Start of '<S4581>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S4608>/Gain' */
          -1.0E+10F,                   /* '<S4630>/Gain' */
          -1.0E+10F,                   /* '<S4654>/Gain' */
          -1.0E+10F,                   /* '<S4678>/Gain' */
          -1.0E+10F                    /* '<S4699>/Gain' */
        }
        ,

        /* End of '<S4581>/CircularPrediction' */

        /* Start of '<S4302>/MovingVehicle' */
        {
          6.28318548F                  /* '<S4312>/Gain_1' */
        }
        ,

        /* End of '<S4302>/MovingVehicle' */

        /* Start of '<S4302>/StationaryVehicle' */
        {
          6.28318548F                  /* '<S4315>/Gain_1' */
        }
        ,

        /* End of '<S4302>/StationaryVehicle' */

        /* Start of '<S4302>/MovingOncomingVehicleWhenActive' */
        {
          3.14159274F                  /* '<S4309>/Gain_1' */
        }
        ,

        /* End of '<S4302>/MovingOncomingVehicleWhenActive' */

        /* Start of '<S4072>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S4224>/Gain' */
          -1.0E+10F,                   /* '<S4231>/Gain' */
          -1.0E+10F,                   /* '<S4203>/Gain' */
          -1.0E+10F,                   /* '<S4210>/Gain' */
          -1.0E+10F,                   /* '<S4182>/Gain' */
          -1.0E+10F                    /* '<S4189>/Gain' */
        }
        ,

        /* End of '<S4072>/CalculateTTI' */

        /* Start of '<S4071>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S4135>/Gain' */
          -1.0E+10F,                   /* '<S4142>/Gain' */
          -1.0E+10F,                   /* '<S4114>/Gain' */
          -1.0E+10F,                   /* '<S4121>/Gain' */
          -1.0E+10F,                   /* '<S4093>/Gain' */
          -1.0E+10F                    /* '<S4100>/Gain' */
        }
        ,

        /* End of '<S4071>/CalculateTTI' */

        /* Start of '<S3944>/MovingObject' */
        {
          3.14159274F,                 /* '<S3950>/Gain_1' */
          6.28318548F                  /* '<S3951>/Gain_1' */
        }
        ,

        /* End of '<S3944>/MovingObject' */

        /* Start of '<S3935>/MovingObject' */
        {
          3.14159274F,                 /* '<S3941>/Gain_1' */
          6.28318548F                  /* '<S3942>/Gain_1' */
        }
        ,

        /* End of '<S3935>/MovingObject' */

        /* Start of '<S3926>/MovingObject' */
        {
          3.14159274F,                 /* '<S3932>/Gain_1' */
          6.28318548F                  /* '<S3933>/Gain_1' */
        }
        ,

        /* End of '<S3926>/MovingObject' */

        /* Start of '<S3917>/MovingObject' */
        {
          3.14159274F,                 /* '<S3923>/Gain_1' */
          6.28318548F                  /* '<S3924>/Gain_1' */
        }
        ,

        /* End of '<S3917>/MovingObject' */

        /* Start of '<S3908>/MovingObject' */
        {
          6.28318548F,                 /* '<S3914>/Gain_1' */
          6.28318548F                  /* '<S3915>/Gain_1' */
        }
        ,

        /* End of '<S3908>/MovingObject' */

        /* Start of '<S3729>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S3741>/Width' */
        }
        ,

        /* End of '<S3729>/ForEachSegmentInPahEstimn' */

        /* Start of '<S3461>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S3489>/Gain' */
          -1.0E+10F,                   /* '<S3511>/Gain' */
          -1.0E+10F,                   /* '<S3535>/Gain' */
          -1.0E+10F,                   /* '<S3559>/Gain' */
          -1.0E+10F                    /* '<S3580>/Gain' */
        }
        ,

        /* End of '<S3461>/CircularPrediction' */

        /* Start of '<S3378>/MovingObject' */
        {
          3.14159274F,                 /* '<S3384>/Gain_1' */
          6.28318548F                  /* '<S3385>/Gain_1' */
        }
        ,

        /* End of '<S3378>/MovingObject' */

        /* Start of '<S3369>/MovingObject' */
        {
          3.14159274F,                 /* '<S3375>/Gain_1' */
          6.28318548F                  /* '<S3376>/Gain_1' */
        }
        ,

        /* End of '<S3369>/MovingObject' */

        /* Start of '<S3360>/MovingObject' */
        {
          3.14159274F,                 /* '<S3366>/Gain_1' */
          6.28318548F                  /* '<S3367>/Gain_1' */
        }
        ,

        /* End of '<S3360>/MovingObject' */

        /* Start of '<S3351>/MovingObject' */
        {
          3.14159274F,                 /* '<S3357>/Gain_1' */
          6.28318548F                  /* '<S3358>/Gain_1' */
        }
        ,

        /* End of '<S3351>/MovingObject' */

        /* Start of '<S3342>/MovingObject' */
        {
          3.14159274F,                 /* '<S3348>/Gain_1' */
          6.28318548F                  /* '<S3349>/Gain_1' */
        }
        ,

        /* End of '<S3342>/MovingObject' */

        /* Start of '<S3169>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S3181>/Width' */
        }
        ,

        /* End of '<S3169>/ForEachSegmentInPahEstimn' */

        /* Start of '<S2904>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S2931>/Gain' */
          -1.0E+10F,                   /* '<S2953>/Gain' */
          -1.0E+10F,                   /* '<S2977>/Gain' */
          -1.0E+10F,                   /* '<S3001>/Gain' */
          -1.0E+10F                    /* '<S3022>/Gain' */
        }
        ,

        /* End of '<S2904>/CircularPrediction' */

        /* Start of '<S2625>/MovingVehicle' */
        {
          6.28318548F                  /* '<S2635>/Gain_1' */
        }
        ,

        /* End of '<S2625>/MovingVehicle' */

        /* Start of '<S2625>/StationaryVehicle' */
        {
          6.28318548F                  /* '<S2638>/Gain_1' */
        }
        ,

        /* End of '<S2625>/StationaryVehicle' */

        /* Start of '<S2625>/MovingOncomingVehicleWhenActive' */
        {
          3.14159274F                  /* '<S2632>/Gain_1' */
        }
        ,

        /* End of '<S2625>/MovingOncomingVehicleWhenActive' */

        /* Start of '<S2517>/ObjectIsNotBraking' */
        {
          -1.0E+10F                    /* '<S2562>/Gain' */
        }
        ,

        /* End of '<S2517>/ObjectIsNotBraking' */

        /* Start of '<S2517>/ObjectIsBraking' */
        {
          -1.0E+10F,                   /* '<S2539>/Gain' */
          -1.0E+10F,                   /* '<S2544>/Gain' */
          -1.0E+10F,                   /* '<S2551>/Gain' */
          -1.0E+10F                    /* '<S2555>/Gain' */
        }
        ,

        /* End of '<S2517>/ObjectIsBraking' */

        /* Start of '<S2415>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S2494>/Gain' */
          -1.0E+10F                    /* '<S2500>/Gain' */
        }
        ,

        /* End of '<S2415>/RightClosest' */

        /* Start of '<S2415>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S2475>/Gain' */
          -1.0E+10F                    /* '<S2481>/Gain' */
        }
        ,

        /* End of '<S2415>/LeftClosest' */

        /* Start of '<S2414>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S2454>/Gain' */
          -1.0E+10F                    /* '<S2460>/Gain' */
        }
        ,

        /* End of '<S2414>/RightClosest' */

        /* Start of '<S2414>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S2435>/Gain' */
          -1.0E+10F                    /* '<S2441>/Gain' */
        }
        ,

        /* End of '<S2414>/LeftClosest' */

        /* Start of '<S2322>/MovingObject' */
        {
          3.14159274F,                 /* '<S2401>/Gain_1' */
          6.28318548F                  /* '<S2402>/Gain_1' */
        }
        ,

        /* End of '<S2322>/MovingObject' */

        /* Start of '<S2321>/CircularPrediction' */
        {
          -1.0E+10F                    /* '<S2373>/Gain' */
        }
        ,

        /* End of '<S2321>/CircularPrediction' */

        /* Start of '<S2345>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S2357>/Width' */
        }
        ,

        /* End of '<S2345>/ForEachSegmentInPahEstimn' */

        /* Start of '<S2280>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S2292>/Width' */
        }
        ,

        /* End of '<S2280>/ForEachSegmentInPahEstimn' */

        /* Start of '<S2128>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S2140>/Width' */
        }
        ,

        /* End of '<S2128>/ForEachSegmentInPahEstimn' */

        /* Start of '<S2106>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S2118>/Width' */
        }
        ,

        /* End of '<S2106>/ForEachSegmentInPahEstimn' */

        /* Start of '<S1954>/ObjectIsNotBraking' */
        {
          -1.0E+10F                    /* '<S1999>/Gain' */
        }
        ,

        /* End of '<S1954>/ObjectIsNotBraking' */

        /* Start of '<S1954>/ObjectIsBraking' */
        {
          -1.0E+10F,                   /* '<S1976>/Gain' */
          -1.0E+10F,                   /* '<S1981>/Gain' */
          -1.0E+10F,                   /* '<S1988>/Gain' */
          -1.0E+10F                    /* '<S1992>/Gain' */
        }
        ,

        /* End of '<S1954>/ObjectIsBraking' */

        /* Start of '<S1852>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S1931>/Gain' */
          -1.0E+10F                    /* '<S1937>/Gain' */
        }
        ,

        /* End of '<S1852>/RightClosest' */

        /* Start of '<S1852>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S1912>/Gain' */
          -1.0E+10F                    /* '<S1918>/Gain' */
        }
        ,

        /* End of '<S1852>/LeftClosest' */

        /* Start of '<S1851>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S1891>/Gain' */
          -1.0E+10F                    /* '<S1897>/Gain' */
        }
        ,

        /* End of '<S1851>/RightClosest' */

        /* Start of '<S1851>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S1872>/Gain' */
          -1.0E+10F                    /* '<S1878>/Gain' */
        }
        ,

        /* End of '<S1851>/LeftClosest' */

        /* Start of '<S1759>/MovingObject' */
        {
          3.14159274F,                 /* '<S1838>/Gain_1' */
          6.28318548F                  /* '<S1839>/Gain_1' */
        }
        ,

        /* End of '<S1759>/MovingObject' */

        /* Start of '<S1758>/CircularPrediction' */
        {
          -1.0E+10F                    /* '<S1810>/Gain' */
        }
        ,

        /* End of '<S1758>/CircularPrediction' */

        /* Start of '<S1782>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S1794>/Width' */
        }
        ,

        /* End of '<S1782>/ForEachSegmentInPahEstimn' */

        /* Start of '<S1625>/ObjectIsNotBraking' */
        {
          -1.0E+10F                    /* '<S1670>/Gain' */
        }
        ,

        /* End of '<S1625>/ObjectIsNotBraking' */

        /* Start of '<S1625>/ObjectIsBraking' */
        {
          -1.0E+10F,                   /* '<S1647>/Gain' */
          -1.0E+10F,                   /* '<S1652>/Gain' */
          -1.0E+10F,                   /* '<S1659>/Gain' */
          -1.0E+10F                    /* '<S1663>/Gain' */
        }
        ,

        /* End of '<S1625>/ObjectIsBraking' */

        /* Start of '<S1523>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S1602>/Gain' */
          -1.0E+10F                    /* '<S1608>/Gain' */
        }
        ,

        /* End of '<S1523>/RightClosest' */

        /* Start of '<S1523>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S1583>/Gain' */
          -1.0E+10F                    /* '<S1589>/Gain' */
        }
        ,

        /* End of '<S1523>/LeftClosest' */

        /* Start of '<S1522>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S1562>/Gain' */
          -1.0E+10F                    /* '<S1568>/Gain' */
        }
        ,

        /* End of '<S1522>/RightClosest' */

        /* Start of '<S1522>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S1543>/Gain' */
          -1.0E+10F                    /* '<S1549>/Gain' */
        }
        ,

        /* End of '<S1522>/LeftClosest' */

        /* Start of '<S1430>/MovingObject' */
        {
          3.14159274F,                 /* '<S1509>/Gain_1' */
          6.28318548F                  /* '<S1510>/Gain_1' */
        }
        ,

        /* End of '<S1430>/MovingObject' */

        /* Start of '<S1429>/CircularPrediction' */
        {
          -1.0E+10F                    /* '<S1481>/Gain' */
        }
        ,

        /* End of '<S1429>/CircularPrediction' */

        /* Start of '<S1453>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S1465>/Width' */
        }
        /* End of '<S1453>/ForEachSegmentInPahEstimn' */
      }
      /* End of '<S2>/AEB' */
    }
    /* End of '<S1>/Ltap' */
  }
  /* End of '<Root>/AEB' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
