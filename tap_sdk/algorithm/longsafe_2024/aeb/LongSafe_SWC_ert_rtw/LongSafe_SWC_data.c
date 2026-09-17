/*
 * File: LongSafe_SWC_data.c
 *
 * Code generated for Simulink model 'LongSafe_SWC'.
 *
 * Model version                  : 7.3246
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Wed Sep 16 13:07:45 2026
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
        },                             /* '<S6175>/Bus Assignment1' */

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
        },                             /* '<S6222>/Bus Assignment1' */
        0.01,                          /* '<S1083>/Abs2' */
        0.01,                          /* '<S1083>/Abs3' */
        0.01,                          /* '<S1083>/Abs4' */
        6.28318548F,                   /* '<S2221>/Gain_1' */
        -1.0E+10F,                     /* '<S2232>/Gain' */
        6.28318548F,                   /* '<S2255>/Gain_1' */
        0.0F,                          /* '<S1387>/Signal Conversion' */
        0.02F,                         /* '<S1394>/Divide' */
        0.0F,                          /* '<S1394>/Product' */
        0.0F,                          /* '<S1394>/Saturation' */
        0.0F,                          /* '<S124>/ConvertALV' */
        0.0F,                          /* '<S122>/Signal Conversion' */
        -0.0001F,                      /* '<S608>/Unary Minus' */
        6.28318548F,                   /* '<S747>/Gain_1' */
        6.28318548F,                   /* '<S760>/Gain_1' */
        0.0F,                          /* '<S905>/Gain_1' */
        0.0F,                          /* '<S905>/Gain_2' */
        0.0F,                          /* '<S910>/Product7' */
        0.0F,                          /* '<S910>/Product8' */
        0.0F,                          /* '<S910>/Add2' */
        0.0F,                          /* '<S905>/Gain_3' */
        0.0F,                          /* '<S905>/Gain_4' */
        0.0F,                          /* '<S911>/Product7' */
        0.0F,                          /* '<S911>/Product8' */
        0.0F,                          /* '<S911>/Add2' */
        0.0F,                          /* '<S905>/Gain_5' */
        0.0F,                          /* '<S905>/Gain_6' */
        0.0F,                          /* '<S908>/Signal Conversion' */
        0.0F,                          /* '<S910>/Product3' */
        0.0F,                          /* '<S910>/Product9' */
        0.0F,                          /* '<S910>/Product4' */
        0.0F,                          /* '<S910>/Add1' */
        0.0F,                          /* '<S910>/Product' */
        0.0F,                          /* '<S910>/Product1' */
        0.0F,                          /* '<S910>/Product10' */
        0.0F,                          /* '<S910>/Product2' */
        0.0F,                          /* '<S911>/Product3' */
        0.0F,                          /* '<S911>/Product9' */
        0.0F,                          /* '<S911>/Product4' */
        0.0F,                          /* '<S911>/Add1' */
        0.0F,                          /* '<S911>/Product' */
        0.0F,                          /* '<S911>/Product1' */
        0.0F,                          /* '<S911>/Product10' */
        0.0F,                          /* '<S911>/Product2' */
        0.0F,                          /* '<S912>/Product3' */
        0.0F,                          /* '<S912>/Product9' */
        0.0F,                          /* '<S912>/Product4' */
        0.0F,                          /* '<S912>/Add1' */
        0.0F,                          /* '<S912>/Product7' */
        0.0F,                          /* '<S912>/Product8' */
        0.0F,                          /* '<S912>/Add2' */
        0.0F,                          /* '<S912>/Product' */
        0.0F,                          /* '<S912>/Product1' */
        0.0F,                          /* '<S912>/Product10' */
        0.0F,                          /* '<S912>/Product2' */
        -0.0F,                         /* '<S906>/Gain_1' */
        0.0F,                          /* '<S906>/Abs' */
        0.0F,                          /* '<S906>/Gain_3' */
        0.0F,                          /* '<S906>/Sign' */
        0.0F,                          /* '<S907>/Sum of Elements' */
        9.0F,                          /* '<S914>/Square' */
        0.0F,                          /* '<S903>/Sum of Elements1' */
        0.0F,                          /* '<S903>/Sum of Elements' */
        50.0F,                         /* '<S983>/FrqFctCallInDrvrStEstimr' */
        0.08F,                         /* '<S1204>/Product1' */
        -9.8F,                         /* '<S1181>/Times' */
        1.57142854F,                   /* '<S1194>/Product2' */
        -15.0F,                        /* '<S1186>/Signal Conversion' */
        0.0F,                          /* '<S1136>/Signal Conversion' */
        -1.0E+10F,                     /* '<S2685>/Gain' */
        -1.0E+10F,                     /* '<S2686>/Gain' */
        -1.0E+10F,                     /* '<S2755>/Gain' */
        -1.0E+10F,                     /* '<S2756>/Gain' */
        -1.0E+10F,                     /* '<S2781>/Gain' */
        -1.0E+10F,                     /* '<S2782>/Gain' */
        -1.0E+10F,                     /* '<S2874>/Gain' */
        -1.0E+10F,                     /* '<S2875>/Gain' */
        -1.0E+10F,                     /* '<S2883>/Gain' */
        -1.0E+10F,                     /* '<S2884>/Gain' */
        -1.0E+10F,                     /* '<S2892>/Gain' */
        -1.0E+10F,                     /* '<S2893>/Gain' */
        -1.0E+10F,                     /* '<S2901>/Gain' */
        -1.0E+10F,                     /* '<S2902>/Gain' */
        -1.0E+10F,                     /* '<S4066>/Gain' */
        -1.0E+10F,                     /* '<S4067>/Gain' */
        -1.0E+10F,                     /* '<S4294>/Gain' */
        -1.0E+10F,                     /* '<S4295>/Gain' */
        -1.0E+10F,                     /* '<S4376>/Gain' */
        -1.0E+10F,                     /* '<S4377>/Gain' */
        -1.0E+10F,                     /* '<S4446>/Gain' */
        -1.0E+10F,                     /* '<S4447>/Gain' */
        -1.0E+10F,                     /* '<S4472>/Gain' */
        -1.0E+10F,                     /* '<S4473>/Gain' */
        -1.0E+10F,                     /* '<S4565>/Gain' */
        -1.0E+10F,                     /* '<S4566>/Gain' */
        -1.0E+10F,                     /* '<S4574>/Gain' */
        -1.0E+10F,                     /* '<S4575>/Gain' */
        -1.0E+10F,                     /* '<S4583>/Gain' */
        -1.0E+10F,                     /* '<S4584>/Gain' */
        -1.0E+10F,                     /* '<S4592>/Gain' */
        -1.0E+10F,                     /* '<S4593>/Gain' */
        -1.0E+10F,                     /* '<S5757>/Gain' */
        -1.0E+10F,                     /* '<S5758>/Gain' */
        -1.0E+10F,                     /* '<S5985>/Gain' */
        -1.0E+10F,                     /* '<S5986>/Gain' */
        0.0F,                          /* '<S2610>/Constant' */
        1.0F,                          /* '<S6013>/Cast1' */
        0.0F,                          /* '<S6013>/Cast7' */
        0.0F,                          /* '<S6013>/Cast8' */
        0.0F,                          /* '<S6013>/Cast9' */
        0.0F,                          /* '<S6162>/Signal Conversion' */
        255.0F,                        /* '<S6335>/Data Type Conversion' */
        -1.0E+10F,                     /* '<S2531>/Gain' */
        -1.0E+10F,                     /* '<S1964>/Gain' */
        -1.0E+10F,                     /* '<S1635>/Gain' */
        9.0F,                          /* '<S955>/Square' */
        0.0F,                          /* '<S957>/Sum of Elements1' */
        0.0F,                          /* '<S957>/Sum of Elements' */
        SnsrDataSts1Vcc_Fusn,          /* '<S2608>/Data Type Conversion8' */
        SnsrDataSts1Vcc_Fusn,          /* '<S2609>/Data Type Conversion8' */
        SnsrDataSts1Vcc_Fusn,          /* '<S6000>/Data Type Conversion21' */
        SnsrDataSts1Vcc_Fusn,          /* '<S6001>/Data Type Conversion21' */
        Side1Vcc_Re,                   /* '<S2608>/Data Type Conversion' */
        Side1Vcc_Re,                   /* '<S2609>/Data Type Conversion' */
        Side1Vcc_Re,                   /* '<S6000>/Data Type Conversion23' */
        Side1Vcc_Re,                   /* '<S6001>/Data Type Conversion23' */
        Relbl4Vcc_BrkgRelbl,           /* '<S2608>/Data Type Conversion11' */
        Relbl4Vcc_BrkgRelbl,           /* '<S2609>/Data Type Conversion11' */
        Relbl4Vcc_BrkgRelbl,           /* '<S6000>/Data Type Conversion6' */
        Relbl4Vcc_BrkgRelbl,           /* '<S6001>/Data Type Conversion6' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S2608>/Data Type Conversion15' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S2609>/Data Type Conversion15' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S6000>/Data Type Conversion19' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S6001>/Data Type Conversion19' */
        Relbl1Vcc_Relbl,               /* '<S2608>/Data Type Conversion12' */
        Relbl1Vcc_Relbl,               /* '<S2609>/Data Type Conversion12' */
        Relbl1Vcc_Relbl,               /* '<S6000>/Data Type Conversion7' */
        Relbl1Vcc_Relbl,               /* '<S6001>/Data Type Conversion7' */
        OnOff1Vcc_On,                  /* '<S116>/ConvertALV' */
        OnOff1_On,                     /* '<S10>/Constant23' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S2608>/Data Type Conversion10' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S2609>/Data Type Conversion10' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S6000>/Data Type Conversion4' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S6001>/Data Type Conversion4' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S2608>/Data Type Conversion14' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S2609>/Data Type Conversion14' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S6000>/Data Type Conversion18' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S6001>/Data Type Conversion18' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S2608>/Data Type Conversion9' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S2609>/Data Type Conversion9' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S6000>/Data Type Conversion22' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S6001>/Data Type Conversion22' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S2608>/Data Type Conversion16' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S2609>/Data Type Conversion16' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S6000>/Data Type Conversion20' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S6001>/Data Type Conversion20' */
        ObjMtnPatHist1Vcc_Ukwn,        /* '<S2608>/Data Type Conversion5' */
        ObjMtnPatHist1Vcc_Ukwn,        /* '<S2609>/Data Type Conversion5' */
        NoYes1_No,                     /* '<S6019>/Data Type Conversion' */
        NoYes1_Yes,                    /* '<S6009>/Data Type Conversion1' */
        NoYes1_Yes,                    /* '<S6027>/Signal Conversion' */
        LiSts1Vcc_Off,                 /* '<S2608>/Data Type Conversion2' */
        LiSts1Vcc_Off,                 /* '<S2608>/Data Type Conversion3' */
        LiSts1Vcc_Off,                 /* '<S2609>/Data Type Conversion2' */
        LiSts1Vcc_Off,                 /* '<S2609>/Data Type Conversion3' */
        LiSts1Vcc_Ukwn,                /* '<S6000>/Data Type Conversion25' */
        LiSts1Vcc_Ukwn,                /* '<S6000>/Data Type Conversion26' */
        LiSts1Vcc_Ukwn,                /* '<S6001>/Data Type Conversion25' */
        LiSts1Vcc_Ukwn,                /* '<S6001>/Data Type Conversion26' */
        IndcrTypExt1_Off,              /* '<S976>/Signal Conversion' */
        IndcrTurn1Vcc_Le,              /* '<S2608>/Data Type Conversion1' */
        IndcrTurn1Vcc_Le,              /* '<S2609>/Data Type Conversion1' */
        IndcrTurn1Vcc_NoIndcn,         /* '<S6000>/Data Type Conversion24' */
        IndcrTurn1Vcc_NoIndcn,         /* '<S6001>/Data Type Conversion24' */
        IdPen_Prof1,                   /* '<S6012>/Data Type Conversion' */
        IdPen_Prof1,                   /* '<S6029>/Signal Conversion' */
        GenQf1_TmpUndefdData,          /* '<S6014>/Data Type Conversion' */
        GenQf1_TmpUndefdData,          /* '<S6163>/Signal Conversion' */
        GenQf1_DataAccurNotWithinSpcn, /* '<S6009>/Data Type Conversion2' */
        GenQf1_DataAccurNotWithinSpcn, /* '<S6024>/Signal Conversion' */
        GenQf1_DataAccurNotWithinSpcn, /* '<S184>/ConvertALV' */
        GenQf1_TmpUndefdData,          /* '<S6161>/Signal Conversion' */
        GenQf1_TmpUndefdData,          /* '<S6166>/Signal Conversion' */
        DynCalPrmForAccStopNGo0_Yes,   /* '<S153>/ConvertALV' */
        AsyBltLvl1Vcc_NoActvn,         /* '<S48>/Switch1' */
        AsyBltLvl1Vcc_NoActvn,         /* '<S380>/ConvertALV' */
        ActtnDataFromCllsnRednByBrkgCtrl1VccSteerGainEna0_FALSE,/* '<S411>/Switch' */
        AEB_ACTIVE,                    /* '<S6375>/Data Type Conversion' */
        0U,                            /* '<S199>/Conversion3' */
        200U,                          /* '<S199>/Add2' */
        4U,                            /* '<S2112>/Width' */
        4U,                            /* '<S2289>/Width' */
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
        4U,                            /* '<S3192>/Width' */
        4U,                            /* '<S3752>/Width' */
        4U,                            /* '<S4883>/Width' */
        4U,                            /* '<S5443>/Width' */
        1U,                            /* '<S6025>/Signal Conversion' */
        1U,                            /* '<S6026>/Signal Conversion' */
        1U,                            /* '<S6160>/Signal Conversion' */
        1U,                            /* '<S6165>/Signal Conversion' */
        1U,                            /* '<S6168>/Signal Conversion' */
        1U,                            /* '<S6169>/Signal Conversion' */
        1U,                            /* '<S6019>/Constant1' */
        1U,                            /* '<S6019>/Constant2' */
        1U,                            /* '<S2615>/Data Type Conversion24' */
        1U,                            /* '<S2615>/Data Type Conversion' */
        0U,                            /* '<S2615>/Data Type Conversion16' */
        4U,                            /* '<S2354>/Width' */
        4U,                            /* '<S2134>/Width' */
        4U,                            /* '<S1787>/Width' */
        4U,                            /* '<S1458>/Width' */
        0,                             /* '<S737>/Multiport Switch' */
        0,                             /* '<S737>/Sign' */
        1,                             /* '<S737>/Switch1' */
        1,                             /* '<S737>/Switch' */
        0,                             /* '<S2152>/Data Type Conversion' */
        0,                             /* '<S1407>/Relational Operator1' */
        0,                             /* '<S42>/Relational Operator1' */
        1,                             /* '<S44>/Relational Operator' */
        0,                             /* '<S192>/Logical Operator' */
        0,                             /* '<S485>/Data Type Conversion' */
        0,                             /* '<S649>/Data Type Conversion' */
        0,                             /* '<S602>/Logical Operator3' */
        0,                             /* '<S691>/Data Type Conversion' */
        0,                             /* '<S718>/Data Type Conversion' */
        0,                             /* '<S737>/Relational Operator3' */
        0,                             /* '<S737>/Relational Operator1' */
        0,                             /* '<S737>/Logical Operator' */
        1,                             /* '<S737>/Relational Operator5' */
        0,                             /* '<S770>/Data Type Conversion' */
        1,                             /* '<S598>/Relational Operator6' */
        0,                             /* '<S598>/Relational Operator' */
        0,                             /* '<S598>/Logical Operator3' */
        0,                             /* '<S414>/Multiport Switch' */
        1,                             /* '<S417>/Relational Operator' */
        0,                             /* '<S907>/Relop_1' */
        0,                             /* '<S1088>/Data Type Conversion' */
        0,                             /* '<S1089>/Data Type Conversion' */
        0,                             /* '<S1090>/Data Type Conversion' */
        0,                             /* '<S1049>/Constant' */
        0,                             /* '<S1094>/Multiport Switch' */
        1,                             /* '<S1094>/Relational Operator2' */
        0,                             /* '<S1094>/Logical Operator' */
        0,                             /* '<S1110>/Signal Conversion' */
        1,                             /* '<S2611>/Constant' */
        0,                             /* '<S6276>/Data Type Conversion' */
        0,                             /* '<S6282>/Logical Operator' */
        0,                             /* '<S6291>/Logical Operator1' */
        0,                             /* '<S6300>/Logical Operator' */
        1,                             /* '<S6301>/Logical Operator1' */
        1,                             /* '<S6310>/Logical Operator1' */
        0,                             /* '<S6319>/Logical Operator2' */
        0,                             /* '<S6319>/Logical Operator3' */
        1,                             /* '<S6432>/Logical Operator13' */
        0,                             /* '<S6432>/Logical Operator26' */
        1,                             /* '<S6432>/Logical Operator4' */
        1,                             /* '<S6432>/Logical Operator5' */
        1,                             /* '<S6432>/Logical Operator6' */
        0,                             /* '<S1076>/Data Type Conversion' */
        0,                             /* '<S1033>/Rel5' */
        0,                             /* '<S1033>/Rel6' */

        /* Start of '<S5786>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S5938>/Gain' */
          -1.0E+10F,                   /* '<S5945>/Gain' */
          -1.0E+10F,                   /* '<S5917>/Gain' */
          -1.0E+10F,                   /* '<S5924>/Gain' */
          -1.0E+10F,                   /* '<S5896>/Gain' */
          -1.0E+10F                    /* '<S5903>/Gain' */
        }
        ,

        /* End of '<S5786>/CalculateTTI' */

        /* Start of '<S5785>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S5849>/Gain' */
          -1.0E+10F,                   /* '<S5856>/Gain' */
          -1.0E+10F,                   /* '<S5828>/Gain' */
          -1.0E+10F,                   /* '<S5835>/Gain' */
          -1.0E+10F,                   /* '<S5807>/Gain' */
          -1.0E+10F                    /* '<S5814>/Gain' */
        }
        ,

        /* End of '<S5785>/CalculateTTI' */

        /* Start of '<S5658>/MovingObject' */
        {
          3.14159274F,                 /* '<S5664>/Gain_1' */
          6.28318548F                  /* '<S5665>/Gain_1' */
        }
        ,

        /* End of '<S5658>/MovingObject' */

        /* Start of '<S5649>/MovingObject' */
        {
          3.14159274F,                 /* '<S5655>/Gain_1' */
          6.28318548F                  /* '<S5656>/Gain_1' */
        }
        ,

        /* End of '<S5649>/MovingObject' */

        /* Start of '<S5640>/MovingObject' */
        {
          3.14159274F,                 /* '<S5646>/Gain_1' */
          6.28318548F                  /* '<S5647>/Gain_1' */
        }
        ,

        /* End of '<S5640>/MovingObject' */

        /* Start of '<S5631>/MovingObject' */
        {
          3.14159274F,                 /* '<S5637>/Gain_1' */
          6.28318548F                  /* '<S5638>/Gain_1' */
        }
        ,

        /* End of '<S5631>/MovingObject' */

        /* Start of '<S5622>/MovingObject' */
        {
          6.28318548F,                 /* '<S5628>/Gain_1' */
          6.28318548F                  /* '<S5629>/Gain_1' */
        }
        ,

        /* End of '<S5622>/MovingObject' */

        /* Start of '<S5443>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S5455>/Width' */
        }
        ,

        /* End of '<S5443>/ForEachSegmentInPahEstimn' */

        /* Start of '<S5175>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S5203>/Gain' */
          -1.0E+10F,                   /* '<S5225>/Gain' */
          -1.0E+10F,                   /* '<S5249>/Gain' */
          -1.0E+10F,                   /* '<S5273>/Gain' */
          -1.0E+10F                    /* '<S5294>/Gain' */
        }
        ,

        /* End of '<S5175>/CircularPrediction' */

        /* Start of '<S5092>/MovingObject' */
        {
          3.14159274F,                 /* '<S5098>/Gain_1' */
          6.28318548F                  /* '<S5099>/Gain_1' */
        }
        ,

        /* End of '<S5092>/MovingObject' */

        /* Start of '<S5083>/MovingObject' */
        {
          3.14159274F,                 /* '<S5089>/Gain_1' */
          6.28318548F                  /* '<S5090>/Gain_1' */
        }
        ,

        /* End of '<S5083>/MovingObject' */

        /* Start of '<S5074>/MovingObject' */
        {
          3.14159274F,                 /* '<S5080>/Gain_1' */
          6.28318548F                  /* '<S5081>/Gain_1' */
        }
        ,

        /* End of '<S5074>/MovingObject' */

        /* Start of '<S5065>/MovingObject' */
        {
          3.14159274F,                 /* '<S5071>/Gain_1' */
          6.28318548F                  /* '<S5072>/Gain_1' */
        }
        ,

        /* End of '<S5065>/MovingObject' */

        /* Start of '<S5056>/MovingObject' */
        {
          3.14159274F,                 /* '<S5062>/Gain_1' */
          6.28318548F                  /* '<S5063>/Gain_1' */
        }
        ,

        /* End of '<S5056>/MovingObject' */

        /* Start of '<S4883>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S4895>/Width' */
        }
        ,

        /* End of '<S4883>/ForEachSegmentInPahEstimn' */

        /* Start of '<S4618>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S4645>/Gain' */
          -1.0E+10F,                   /* '<S4667>/Gain' */
          -1.0E+10F,                   /* '<S4691>/Gain' */
          -1.0E+10F,                   /* '<S4715>/Gain' */
          -1.0E+10F                    /* '<S4736>/Gain' */
        }
        ,

        /* End of '<S4618>/CircularPrediction' */

        /* Start of '<S4325>/MovingVehicle' */
        {
          6.28318548F                  /* '<S4335>/Gain_1' */
        }
        ,

        /* End of '<S4325>/MovingVehicle' */

        /* Start of '<S4325>/StationaryVehicle' */
        {
          6.28318548F                  /* '<S4338>/Gain_1' */
        }
        ,

        /* End of '<S4325>/StationaryVehicle' */

        /* Start of '<S4325>/MovingOncomingVehicleWhenActive' */
        {
          3.14159274F                  /* '<S4332>/Gain_1' */
        }
        ,

        /* End of '<S4325>/MovingOncomingVehicleWhenActive' */

        /* Start of '<S4095>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S4247>/Gain' */
          -1.0E+10F,                   /* '<S4254>/Gain' */
          -1.0E+10F,                   /* '<S4226>/Gain' */
          -1.0E+10F,                   /* '<S4233>/Gain' */
          -1.0E+10F,                   /* '<S4205>/Gain' */
          -1.0E+10F                    /* '<S4212>/Gain' */
        }
        ,

        /* End of '<S4095>/CalculateTTI' */

        /* Start of '<S4094>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S4158>/Gain' */
          -1.0E+10F,                   /* '<S4165>/Gain' */
          -1.0E+10F,                   /* '<S4137>/Gain' */
          -1.0E+10F,                   /* '<S4144>/Gain' */
          -1.0E+10F,                   /* '<S4116>/Gain' */
          -1.0E+10F                    /* '<S4123>/Gain' */
        }
        ,

        /* End of '<S4094>/CalculateTTI' */

        /* Start of '<S3967>/MovingObject' */
        {
          3.14159274F,                 /* '<S3973>/Gain_1' */
          6.28318548F                  /* '<S3974>/Gain_1' */
        }
        ,

        /* End of '<S3967>/MovingObject' */

        /* Start of '<S3958>/MovingObject' */
        {
          3.14159274F,                 /* '<S3964>/Gain_1' */
          6.28318548F                  /* '<S3965>/Gain_1' */
        }
        ,

        /* End of '<S3958>/MovingObject' */

        /* Start of '<S3949>/MovingObject' */
        {
          3.14159274F,                 /* '<S3955>/Gain_1' */
          6.28318548F                  /* '<S3956>/Gain_1' */
        }
        ,

        /* End of '<S3949>/MovingObject' */

        /* Start of '<S3940>/MovingObject' */
        {
          3.14159274F,                 /* '<S3946>/Gain_1' */
          6.28318548F                  /* '<S3947>/Gain_1' */
        }
        ,

        /* End of '<S3940>/MovingObject' */

        /* Start of '<S3931>/MovingObject' */
        {
          6.28318548F,                 /* '<S3937>/Gain_1' */
          6.28318548F                  /* '<S3938>/Gain_1' */
        }
        ,

        /* End of '<S3931>/MovingObject' */

        /* Start of '<S3752>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S3764>/Width' */
        }
        ,

        /* End of '<S3752>/ForEachSegmentInPahEstimn' */

        /* Start of '<S3484>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S3512>/Gain' */
          -1.0E+10F,                   /* '<S3534>/Gain' */
          -1.0E+10F,                   /* '<S3558>/Gain' */
          -1.0E+10F,                   /* '<S3582>/Gain' */
          -1.0E+10F                    /* '<S3603>/Gain' */
        }
        ,

        /* End of '<S3484>/CircularPrediction' */

        /* Start of '<S3401>/MovingObject' */
        {
          3.14159274F,                 /* '<S3407>/Gain_1' */
          6.28318548F                  /* '<S3408>/Gain_1' */
        }
        ,

        /* End of '<S3401>/MovingObject' */

        /* Start of '<S3392>/MovingObject' */
        {
          3.14159274F,                 /* '<S3398>/Gain_1' */
          6.28318548F                  /* '<S3399>/Gain_1' */
        }
        ,

        /* End of '<S3392>/MovingObject' */

        /* Start of '<S3383>/MovingObject' */
        {
          3.14159274F,                 /* '<S3389>/Gain_1' */
          6.28318548F                  /* '<S3390>/Gain_1' */
        }
        ,

        /* End of '<S3383>/MovingObject' */

        /* Start of '<S3374>/MovingObject' */
        {
          3.14159274F,                 /* '<S3380>/Gain_1' */
          6.28318548F                  /* '<S3381>/Gain_1' */
        }
        ,

        /* End of '<S3374>/MovingObject' */

        /* Start of '<S3365>/MovingObject' */
        {
          3.14159274F,                 /* '<S3371>/Gain_1' */
          6.28318548F                  /* '<S3372>/Gain_1' */
        }
        ,

        /* End of '<S3365>/MovingObject' */

        /* Start of '<S3192>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S3204>/Width' */
        }
        ,

        /* End of '<S3192>/ForEachSegmentInPahEstimn' */

        /* Start of '<S2927>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S2954>/Gain' */
          -1.0E+10F,                   /* '<S2976>/Gain' */
          -1.0E+10F,                   /* '<S3000>/Gain' */
          -1.0E+10F,                   /* '<S3024>/Gain' */
          -1.0E+10F                    /* '<S3045>/Gain' */
        }
        ,

        /* End of '<S2927>/CircularPrediction' */

        /* Start of '<S2634>/MovingVehicle' */
        {
          6.28318548F                  /* '<S2644>/Gain_1' */
        }
        ,

        /* End of '<S2634>/MovingVehicle' */

        /* Start of '<S2634>/StationaryVehicle' */
        {
          6.28318548F                  /* '<S2647>/Gain_1' */
        }
        ,

        /* End of '<S2634>/StationaryVehicle' */

        /* Start of '<S2634>/MovingOncomingVehicleWhenActive' */
        {
          3.14159274F                  /* '<S2641>/Gain_1' */
        }
        ,

        /* End of '<S2634>/MovingOncomingVehicleWhenActive' */

        /* Start of '<S2526>/ObjectIsNotBraking' */
        {
          -1.0E+10F                    /* '<S2571>/Gain' */
        }
        ,

        /* End of '<S2526>/ObjectIsNotBraking' */

        /* Start of '<S2526>/ObjectIsBraking' */
        {
          -1.0E+10F,                   /* '<S2548>/Gain' */
          -1.0E+10F,                   /* '<S2553>/Gain' */
          -1.0E+10F,                   /* '<S2560>/Gain' */
          -1.0E+10F                    /* '<S2564>/Gain' */
        }
        ,

        /* End of '<S2526>/ObjectIsBraking' */

        /* Start of '<S2424>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S2503>/Gain' */
          -1.0E+10F                    /* '<S2509>/Gain' */
        }
        ,

        /* End of '<S2424>/RightClosest' */

        /* Start of '<S2424>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S2484>/Gain' */
          -1.0E+10F                    /* '<S2490>/Gain' */
        }
        ,

        /* End of '<S2424>/LeftClosest' */

        /* Start of '<S2423>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S2463>/Gain' */
          -1.0E+10F                    /* '<S2469>/Gain' */
        }
        ,

        /* End of '<S2423>/RightClosest' */

        /* Start of '<S2423>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S2444>/Gain' */
          -1.0E+10F                    /* '<S2450>/Gain' */
        }
        ,

        /* End of '<S2423>/LeftClosest' */

        /* Start of '<S2331>/MovingObject' */
        {
          3.14159274F,                 /* '<S2410>/Gain_1' */
          6.28318548F                  /* '<S2411>/Gain_1' */
        }
        ,

        /* End of '<S2331>/MovingObject' */

        /* Start of '<S2330>/CircularPrediction' */
        {
          -1.0E+10F                    /* '<S2382>/Gain' */
        }
        ,

        /* End of '<S2330>/CircularPrediction' */

        /* Start of '<S2354>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S2366>/Width' */
        }
        ,

        /* End of '<S2354>/ForEachSegmentInPahEstimn' */

        /* Start of '<S2289>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S2301>/Width' */
        }
        ,

        /* End of '<S2289>/ForEachSegmentInPahEstimn' */

        /* Start of '<S2134>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S2146>/Width' */
        }
        ,

        /* End of '<S2134>/ForEachSegmentInPahEstimn' */

        /* Start of '<S2112>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S2124>/Width' */
        }
        ,

        /* End of '<S2112>/ForEachSegmentInPahEstimn' */

        /* Start of '<S1959>/ObjectIsNotBraking' */
        {
          -1.0E+10F                    /* '<S2004>/Gain' */
        }
        ,

        /* End of '<S1959>/ObjectIsNotBraking' */

        /* Start of '<S1959>/ObjectIsBraking' */
        {
          -1.0E+10F,                   /* '<S1981>/Gain' */
          -1.0E+10F,                   /* '<S1986>/Gain' */
          -1.0E+10F,                   /* '<S1993>/Gain' */
          -1.0E+10F                    /* '<S1997>/Gain' */
        }
        ,

        /* End of '<S1959>/ObjectIsBraking' */

        /* Start of '<S1857>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S1936>/Gain' */
          -1.0E+10F                    /* '<S1942>/Gain' */
        }
        ,

        /* End of '<S1857>/RightClosest' */

        /* Start of '<S1857>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S1917>/Gain' */
          -1.0E+10F                    /* '<S1923>/Gain' */
        }
        ,

        /* End of '<S1857>/LeftClosest' */

        /* Start of '<S1856>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S1896>/Gain' */
          -1.0E+10F                    /* '<S1902>/Gain' */
        }
        ,

        /* End of '<S1856>/RightClosest' */

        /* Start of '<S1856>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S1877>/Gain' */
          -1.0E+10F                    /* '<S1883>/Gain' */
        }
        ,

        /* End of '<S1856>/LeftClosest' */

        /* Start of '<S1764>/MovingObject' */
        {
          3.14159274F,                 /* '<S1843>/Gain_1' */
          6.28318548F                  /* '<S1844>/Gain_1' */
        }
        ,

        /* End of '<S1764>/MovingObject' */

        /* Start of '<S1763>/CircularPrediction' */
        {
          -1.0E+10F                    /* '<S1815>/Gain' */
        }
        ,

        /* End of '<S1763>/CircularPrediction' */

        /* Start of '<S1787>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S1799>/Width' */
        }
        ,

        /* End of '<S1787>/ForEachSegmentInPahEstimn' */

        /* Start of '<S1630>/ObjectIsNotBraking' */
        {
          -1.0E+10F                    /* '<S1675>/Gain' */
        }
        ,

        /* End of '<S1630>/ObjectIsNotBraking' */

        /* Start of '<S1630>/ObjectIsBraking' */
        {
          -1.0E+10F,                   /* '<S1652>/Gain' */
          -1.0E+10F,                   /* '<S1657>/Gain' */
          -1.0E+10F,                   /* '<S1664>/Gain' */
          -1.0E+10F                    /* '<S1668>/Gain' */
        }
        ,

        /* End of '<S1630>/ObjectIsBraking' */

        /* Start of '<S1528>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S1607>/Gain' */
          -1.0E+10F                    /* '<S1613>/Gain' */
        }
        ,

        /* End of '<S1528>/RightClosest' */

        /* Start of '<S1528>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S1588>/Gain' */
          -1.0E+10F                    /* '<S1594>/Gain' */
        }
        ,

        /* End of '<S1528>/LeftClosest' */

        /* Start of '<S1527>/RightClosest' */
        {
          -1.0E+10F,                   /* '<S1567>/Gain' */
          -1.0E+10F                    /* '<S1573>/Gain' */
        }
        ,

        /* End of '<S1527>/RightClosest' */

        /* Start of '<S1527>/LeftClosest' */
        {
          -1.0E+10F,                   /* '<S1548>/Gain' */
          -1.0E+10F                    /* '<S1554>/Gain' */
        }
        ,

        /* End of '<S1527>/LeftClosest' */

        /* Start of '<S1435>/MovingObject' */
        {
          3.14159274F,                 /* '<S1514>/Gain_1' */
          6.28318548F                  /* '<S1515>/Gain_1' */
        }
        ,

        /* End of '<S1435>/MovingObject' */

        /* Start of '<S1434>/CircularPrediction' */
        {
          -1.0E+10F                    /* '<S1486>/Gain' */
        }
        ,

        /* End of '<S1434>/CircularPrediction' */

        /* Start of '<S1458>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S1470>/Width' */
        }
        /* End of '<S1458>/ForEachSegmentInPahEstimn' */
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
