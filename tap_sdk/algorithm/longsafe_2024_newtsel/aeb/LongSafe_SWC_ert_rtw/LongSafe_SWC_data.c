/*
 * File: LongSafe_SWC_data.c
 *
 * Code generated for Simulink model 'LongSafe_SWC'.
 *
 * Model version                  : 7.3246
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue Aug 18 17:02:34 2026
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
        },                             /* '<S6163>/Bus Assignment1' */

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
        },                             /* '<S6210>/Bus Assignment1' */
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
        -1.0E+10F,                     /* '<S2749>/Gain' */
        -1.0E+10F,                     /* '<S2750>/Gain' */
        -1.0E+10F,                     /* '<S2775>/Gain' */
        -1.0E+10F,                     /* '<S2776>/Gain' */
        -1.0E+10F,                     /* '<S2868>/Gain' */
        -1.0E+10F,                     /* '<S2869>/Gain' */
        -1.0E+10F,                     /* '<S2877>/Gain' */
        -1.0E+10F,                     /* '<S2878>/Gain' */
        -1.0E+10F,                     /* '<S2886>/Gain' */
        -1.0E+10F,                     /* '<S2887>/Gain' */
        -1.0E+10F,                     /* '<S2895>/Gain' */
        -1.0E+10F,                     /* '<S2896>/Gain' */
        -1.0E+10F,                     /* '<S4060>/Gain' */
        -1.0E+10F,                     /* '<S4061>/Gain' */
        -1.0E+10F,                     /* '<S4288>/Gain' */
        -1.0E+10F,                     /* '<S4289>/Gain' */
        -1.0E+10F,                     /* '<S4370>/Gain' */
        -1.0E+10F,                     /* '<S4371>/Gain' */
        -1.0E+10F,                     /* '<S4434>/Gain' */
        -1.0E+10F,                     /* '<S4435>/Gain' */
        -1.0E+10F,                     /* '<S4460>/Gain' */
        -1.0E+10F,                     /* '<S4461>/Gain' */
        -1.0E+10F,                     /* '<S4553>/Gain' */
        -1.0E+10F,                     /* '<S4554>/Gain' */
        -1.0E+10F,                     /* '<S4562>/Gain' */
        -1.0E+10F,                     /* '<S4563>/Gain' */
        -1.0E+10F,                     /* '<S4571>/Gain' */
        -1.0E+10F,                     /* '<S4572>/Gain' */
        -1.0E+10F,                     /* '<S4580>/Gain' */
        -1.0E+10F,                     /* '<S4581>/Gain' */
        -1.0E+10F,                     /* '<S5745>/Gain' */
        -1.0E+10F,                     /* '<S5746>/Gain' */
        -1.0E+10F,                     /* '<S5973>/Gain' */
        -1.0E+10F,                     /* '<S5974>/Gain' */
        0.0F,                          /* '<S2610>/Constant' */
        1.0F,                          /* '<S6001>/Cast1' */
        0.0F,                          /* '<S6001>/Cast7' */
        0.0F,                          /* '<S6001>/Cast8' */
        0.0F,                          /* '<S6001>/Cast9' */
        0.0F,                          /* '<S6150>/Signal Conversion' */
        255.0F,                        /* '<S6323>/Data Type Conversion' */
        -1.0E+10F,                     /* '<S2531>/Gain' */
        -1.0E+10F,                     /* '<S1964>/Gain' */
        -1.0E+10F,                     /* '<S1635>/Gain' */
        9.0F,                          /* '<S955>/Square' */
        0.0F,                          /* '<S957>/Sum of Elements1' */
        0.0F,                          /* '<S957>/Sum of Elements' */
        SnsrDataSts1Vcc_Fusn,          /* '<S2608>/Data Type Conversion8' */
        SnsrDataSts1Vcc_Fusn,          /* '<S2609>/Data Type Conversion8' */
        SnsrDataSts1Vcc_Fusn,          /* '<S5988>/Data Type Conversion21' */
        SnsrDataSts1Vcc_Fusn,          /* '<S5989>/Data Type Conversion21' */
        Side1Vcc_Re,                   /* '<S2608>/Data Type Conversion' */
        Side1Vcc_Re,                   /* '<S2609>/Data Type Conversion' */
        Side1Vcc_Re,                   /* '<S5988>/Data Type Conversion23' */
        Side1Vcc_Re,                   /* '<S5989>/Data Type Conversion23' */
        Relbl4Vcc_BrkgRelbl,           /* '<S2608>/Data Type Conversion11' */
        Relbl4Vcc_BrkgRelbl,           /* '<S2609>/Data Type Conversion11' */
        Relbl4Vcc_BrkgRelbl,           /* '<S5988>/Data Type Conversion6' */
        Relbl4Vcc_BrkgRelbl,           /* '<S5989>/Data Type Conversion6' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S2608>/Data Type Conversion15' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S2609>/Data Type Conversion15' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S5988>/Data Type Conversion19' */
        Relbl3Vcc_SoonNotRelbl,        /* '<S5989>/Data Type Conversion19' */
        Relbl1Vcc_Relbl,               /* '<S2608>/Data Type Conversion12' */
        Relbl1Vcc_Relbl,               /* '<S2609>/Data Type Conversion12' */
        Relbl1Vcc_Relbl,               /* '<S5988>/Data Type Conversion7' */
        Relbl1Vcc_Relbl,               /* '<S5989>/Data Type Conversion7' */
        OnOff1Vcc_On,                  /* '<S116>/ConvertALV' */
        OnOff1_On,                     /* '<S10>/Constant23' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S2608>/Data Type Conversion10' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S2609>/Data Type Conversion10' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S5988>/Data Type Conversion4' */
        ObjPpty1VccTrfcSceno0_TurnAcrssPah,/* '<S5989>/Data Type Conversion4' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S2608>/Data Type Conversion14' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S2609>/Data Type Conversion14' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S5988>/Data Type Conversion18' */
        ObjPpty1VccTrfcJamAssiQly0_NotRelbl,/* '<S5989>/Data Type Conversion18' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S2608>/Data Type Conversion9' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S2609>/Data Type Conversion9' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S5988>/Data Type Conversion22' */
        ObjPpty1VccMdlOfMtn0_MdlBicycle,/* '<S5989>/Data Type Conversion22' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S2608>/Data Type Conversion16' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S2609>/Data Type Conversion16' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S5988>/Data Type Conversion20' */
        ObjPpty1VccEmgyLaneKeepAidPosnQly0_Relbl,/* '<S5989>/Data Type Conversion20' */
        ObjMtnPatHist1Vcc_Ukwn,        /* '<S2608>/Data Type Conversion5' */
        ObjMtnPatHist1Vcc_Ukwn,        /* '<S2609>/Data Type Conversion5' */
        NoYes1_No,                     /* '<S6007>/Data Type Conversion' */
        NoYes1_Yes,                    /* '<S5997>/Data Type Conversion1' */
        NoYes1_Yes,                    /* '<S6015>/Signal Conversion' */
        LiSts1Vcc_Off,                 /* '<S2608>/Data Type Conversion2' */
        LiSts1Vcc_Off,                 /* '<S2608>/Data Type Conversion3' */
        LiSts1Vcc_Off,                 /* '<S2609>/Data Type Conversion2' */
        LiSts1Vcc_Off,                 /* '<S2609>/Data Type Conversion3' */
        LiSts1Vcc_Ukwn,                /* '<S5988>/Data Type Conversion25' */
        LiSts1Vcc_Ukwn,                /* '<S5988>/Data Type Conversion26' */
        LiSts1Vcc_Ukwn,                /* '<S5989>/Data Type Conversion25' */
        LiSts1Vcc_Ukwn,                /* '<S5989>/Data Type Conversion26' */
        IndcrTypExt1_Off,              /* '<S976>/Signal Conversion' */
        IndcrTurn1Vcc_Le,              /* '<S2608>/Data Type Conversion1' */
        IndcrTurn1Vcc_Le,              /* '<S2609>/Data Type Conversion1' */
        IndcrTurn1Vcc_NoIndcn,         /* '<S5988>/Data Type Conversion24' */
        IndcrTurn1Vcc_NoIndcn,         /* '<S5989>/Data Type Conversion24' */
        IdPen_Prof1,                   /* '<S6000>/Data Type Conversion' */
        IdPen_Prof1,                   /* '<S6017>/Signal Conversion' */
        GenQf1_TmpUndefdData,          /* '<S6002>/Data Type Conversion' */
        GenQf1_TmpUndefdData,          /* '<S6151>/Signal Conversion' */
        GenQf1_DataAccurNotWithinSpcn, /* '<S5997>/Data Type Conversion2' */
        GenQf1_DataAccurNotWithinSpcn, /* '<S6012>/Signal Conversion' */
        GenQf1_DataAccurNotWithinSpcn, /* '<S184>/ConvertALV' */
        GenQf1_TmpUndefdData,          /* '<S6149>/Signal Conversion' */
        GenQf1_TmpUndefdData,          /* '<S6154>/Signal Conversion' */
        DynCalPrmForAccStopNGo0_Yes,   /* '<S153>/ConvertALV' */
        AsyBltLvl1Vcc_NoActvn,         /* '<S48>/Switch1' */
        AsyBltLvl1Vcc_NoActvn,         /* '<S380>/ConvertALV' */
        ActtnDataFromCllsnRednByBrkgCtrl1VccSteerGainEna0_FALSE,/* '<S411>/Switch' */
        AEB_ACTIVE,                    /* '<S6363>/Data Type Conversion' */
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
        4U,                            /* '<S3186>/Width' */
        4U,                            /* '<S3746>/Width' */
        4U,                            /* '<S4871>/Width' */
        4U,                            /* '<S5431>/Width' */
        1U,                            /* '<S6013>/Signal Conversion' */
        1U,                            /* '<S6014>/Signal Conversion' */
        1U,                            /* '<S6148>/Signal Conversion' */
        1U,                            /* '<S6153>/Signal Conversion' */
        1U,                            /* '<S6156>/Signal Conversion' */
        1U,                            /* '<S6157>/Signal Conversion' */
        1U,                            /* '<S6007>/Constant1' */
        1U,                            /* '<S6007>/Constant2' */
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
        0,                             /* '<S6264>/Data Type Conversion' */
        0,                             /* '<S6270>/Logical Operator' */
        0,                             /* '<S6279>/Logical Operator1' */
        0,                             /* '<S6288>/Logical Operator' */
        1,                             /* '<S6289>/Logical Operator1' */
        1,                             /* '<S6298>/Logical Operator1' */
        0,                             /* '<S6307>/Logical Operator2' */
        0,                             /* '<S6307>/Logical Operator3' */
        1,                             /* '<S6420>/Logical Operator13' */
        0,                             /* '<S6420>/Logical Operator26' */
        1,                             /* '<S6420>/Logical Operator4' */
        1,                             /* '<S6420>/Logical Operator5' */
        1,                             /* '<S6420>/Logical Operator6' */
        0,                             /* '<S1076>/Data Type Conversion' */
        0,                             /* '<S1033>/Rel5' */
        0,                             /* '<S1033>/Rel6' */

        /* Start of '<S5774>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S5926>/Gain' */
          -1.0E+10F,                   /* '<S5933>/Gain' */
          -1.0E+10F,                   /* '<S5905>/Gain' */
          -1.0E+10F,                   /* '<S5912>/Gain' */
          -1.0E+10F,                   /* '<S5884>/Gain' */
          -1.0E+10F                    /* '<S5891>/Gain' */
        }
        ,

        /* End of '<S5774>/CalculateTTI' */

        /* Start of '<S5773>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S5837>/Gain' */
          -1.0E+10F,                   /* '<S5844>/Gain' */
          -1.0E+10F,                   /* '<S5816>/Gain' */
          -1.0E+10F,                   /* '<S5823>/Gain' */
          -1.0E+10F,                   /* '<S5795>/Gain' */
          -1.0E+10F                    /* '<S5802>/Gain' */
        }
        ,

        /* End of '<S5773>/CalculateTTI' */

        /* Start of '<S5646>/MovingObject' */
        {
          3.14159274F,                 /* '<S5652>/Gain_1' */
          6.28318548F                  /* '<S5653>/Gain_1' */
        }
        ,

        /* End of '<S5646>/MovingObject' */

        /* Start of '<S5637>/MovingObject' */
        {
          3.14159274F,                 /* '<S5643>/Gain_1' */
          6.28318548F                  /* '<S5644>/Gain_1' */
        }
        ,

        /* End of '<S5637>/MovingObject' */

        /* Start of '<S5628>/MovingObject' */
        {
          3.14159274F,                 /* '<S5634>/Gain_1' */
          6.28318548F                  /* '<S5635>/Gain_1' */
        }
        ,

        /* End of '<S5628>/MovingObject' */

        /* Start of '<S5619>/MovingObject' */
        {
          3.14159274F,                 /* '<S5625>/Gain_1' */
          6.28318548F                  /* '<S5626>/Gain_1' */
        }
        ,

        /* End of '<S5619>/MovingObject' */

        /* Start of '<S5610>/MovingObject' */
        {
          6.28318548F,                 /* '<S5616>/Gain_1' */
          6.28318548F                  /* '<S5617>/Gain_1' */
        }
        ,

        /* End of '<S5610>/MovingObject' */

        /* Start of '<S5431>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S5443>/Width' */
        }
        ,

        /* End of '<S5431>/ForEachSegmentInPahEstimn' */

        /* Start of '<S5163>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S5191>/Gain' */
          -1.0E+10F,                   /* '<S5213>/Gain' */
          -1.0E+10F,                   /* '<S5237>/Gain' */
          -1.0E+10F,                   /* '<S5261>/Gain' */
          -1.0E+10F                    /* '<S5282>/Gain' */
        }
        ,

        /* End of '<S5163>/CircularPrediction' */

        /* Start of '<S5080>/MovingObject' */
        {
          3.14159274F,                 /* '<S5086>/Gain_1' */
          6.28318548F                  /* '<S5087>/Gain_1' */
        }
        ,

        /* End of '<S5080>/MovingObject' */

        /* Start of '<S5071>/MovingObject' */
        {
          3.14159274F,                 /* '<S5077>/Gain_1' */
          6.28318548F                  /* '<S5078>/Gain_1' */
        }
        ,

        /* End of '<S5071>/MovingObject' */

        /* Start of '<S5062>/MovingObject' */
        {
          3.14159274F,                 /* '<S5068>/Gain_1' */
          6.28318548F                  /* '<S5069>/Gain_1' */
        }
        ,

        /* End of '<S5062>/MovingObject' */

        /* Start of '<S5053>/MovingObject' */
        {
          3.14159274F,                 /* '<S5059>/Gain_1' */
          6.28318548F                  /* '<S5060>/Gain_1' */
        }
        ,

        /* End of '<S5053>/MovingObject' */

        /* Start of '<S5044>/MovingObject' */
        {
          3.14159274F,                 /* '<S5050>/Gain_1' */
          6.28318548F                  /* '<S5051>/Gain_1' */
        }
        ,

        /* End of '<S5044>/MovingObject' */

        /* Start of '<S4871>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S4883>/Width' */
        }
        ,

        /* End of '<S4871>/ForEachSegmentInPahEstimn' */

        /* Start of '<S4606>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S4633>/Gain' */
          -1.0E+10F,                   /* '<S4655>/Gain' */
          -1.0E+10F,                   /* '<S4679>/Gain' */
          -1.0E+10F,                   /* '<S4703>/Gain' */
          -1.0E+10F                    /* '<S4724>/Gain' */
        }
        ,

        /* End of '<S4606>/CircularPrediction' */

        /* Start of '<S4319>/MovingVehicle' */
        {
          6.28318548F                  /* '<S4329>/Gain_1' */
        }
        ,

        /* End of '<S4319>/MovingVehicle' */

        /* Start of '<S4319>/StationaryVehicle' */
        {
          6.28318548F                  /* '<S4332>/Gain_1' */
        }
        ,

        /* End of '<S4319>/StationaryVehicle' */

        /* Start of '<S4319>/MovingOncomingVehicleWhenActive' */
        {
          3.14159274F                  /* '<S4326>/Gain_1' */
        }
        ,

        /* End of '<S4319>/MovingOncomingVehicleWhenActive' */

        /* Start of '<S4089>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S4241>/Gain' */
          -1.0E+10F,                   /* '<S4248>/Gain' */
          -1.0E+10F,                   /* '<S4220>/Gain' */
          -1.0E+10F,                   /* '<S4227>/Gain' */
          -1.0E+10F,                   /* '<S4199>/Gain' */
          -1.0E+10F                    /* '<S4206>/Gain' */
        }
        ,

        /* End of '<S4089>/CalculateTTI' */

        /* Start of '<S4088>/CalculateTTI' */
        {
          -1.0E+10F,                   /* '<S4152>/Gain' */
          -1.0E+10F,                   /* '<S4159>/Gain' */
          -1.0E+10F,                   /* '<S4131>/Gain' */
          -1.0E+10F,                   /* '<S4138>/Gain' */
          -1.0E+10F,                   /* '<S4110>/Gain' */
          -1.0E+10F                    /* '<S4117>/Gain' */
        }
        ,

        /* End of '<S4088>/CalculateTTI' */

        /* Start of '<S3961>/MovingObject' */
        {
          3.14159274F,                 /* '<S3967>/Gain_1' */
          6.28318548F                  /* '<S3968>/Gain_1' */
        }
        ,

        /* End of '<S3961>/MovingObject' */

        /* Start of '<S3952>/MovingObject' */
        {
          3.14159274F,                 /* '<S3958>/Gain_1' */
          6.28318548F                  /* '<S3959>/Gain_1' */
        }
        ,

        /* End of '<S3952>/MovingObject' */

        /* Start of '<S3943>/MovingObject' */
        {
          3.14159274F,                 /* '<S3949>/Gain_1' */
          6.28318548F                  /* '<S3950>/Gain_1' */
        }
        ,

        /* End of '<S3943>/MovingObject' */

        /* Start of '<S3934>/MovingObject' */
        {
          3.14159274F,                 /* '<S3940>/Gain_1' */
          6.28318548F                  /* '<S3941>/Gain_1' */
        }
        ,

        /* End of '<S3934>/MovingObject' */

        /* Start of '<S3925>/MovingObject' */
        {
          6.28318548F,                 /* '<S3931>/Gain_1' */
          6.28318548F                  /* '<S3932>/Gain_1' */
        }
        ,

        /* End of '<S3925>/MovingObject' */

        /* Start of '<S3746>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S3758>/Width' */
        }
        ,

        /* End of '<S3746>/ForEachSegmentInPahEstimn' */

        /* Start of '<S3478>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S3506>/Gain' */
          -1.0E+10F,                   /* '<S3528>/Gain' */
          -1.0E+10F,                   /* '<S3552>/Gain' */
          -1.0E+10F,                   /* '<S3576>/Gain' */
          -1.0E+10F                    /* '<S3597>/Gain' */
        }
        ,

        /* End of '<S3478>/CircularPrediction' */

        /* Start of '<S3395>/MovingObject' */
        {
          3.14159274F,                 /* '<S3401>/Gain_1' */
          6.28318548F                  /* '<S3402>/Gain_1' */
        }
        ,

        /* End of '<S3395>/MovingObject' */

        /* Start of '<S3386>/MovingObject' */
        {
          3.14159274F,                 /* '<S3392>/Gain_1' */
          6.28318548F                  /* '<S3393>/Gain_1' */
        }
        ,

        /* End of '<S3386>/MovingObject' */

        /* Start of '<S3377>/MovingObject' */
        {
          3.14159274F,                 /* '<S3383>/Gain_1' */
          6.28318548F                  /* '<S3384>/Gain_1' */
        }
        ,

        /* End of '<S3377>/MovingObject' */

        /* Start of '<S3368>/MovingObject' */
        {
          3.14159274F,                 /* '<S3374>/Gain_1' */
          6.28318548F                  /* '<S3375>/Gain_1' */
        }
        ,

        /* End of '<S3368>/MovingObject' */

        /* Start of '<S3359>/MovingObject' */
        {
          3.14159274F,                 /* '<S3365>/Gain_1' */
          6.28318548F                  /* '<S3366>/Gain_1' */
        }
        ,

        /* End of '<S3359>/MovingObject' */

        /* Start of '<S3186>/ForEachSegmentInPahEstimn' */
        {
          4                            /* '<S3198>/Width' */
        }
        ,

        /* End of '<S3186>/ForEachSegmentInPahEstimn' */

        /* Start of '<S2921>/CircularPrediction' */
        {
          -1.0E+10F,                   /* '<S2948>/Gain' */
          -1.0E+10F,                   /* '<S2970>/Gain' */
          -1.0E+10F,                   /* '<S2994>/Gain' */
          -1.0E+10F,                   /* '<S3018>/Gain' */
          -1.0E+10F                    /* '<S3039>/Gain' */
        }
        ,

        /* End of '<S2921>/CircularPrediction' */

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
