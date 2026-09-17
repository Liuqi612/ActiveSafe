/*
 * File: AES_ESA_SWC_data.c
 *
 * Code generated for Simulink model 'AES_ESA_SWC'.
 *
 * Model version                  : 7.1509
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Mon Sep 14 15:48:50 2026
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

#include "AES_ESA_SWC.h"
#include "AES_ESA_SWC_private.h"

/* Invariant block signals (default storage) */
const ConstB_AES_ESA_SWC_T AES_ESA_SWC_ConstB = {
  1000.0,                              /* '<S350>/MinMax2' */
  0.001,                               /* '<S350>/Divide' */
  1600.0,                              /* '<S350>/MinMax1' */
  0.000625,                            /* '<S350>/Divide1' */
  260914U,                             /* '<S4>/Signal Conversion13' */
  260914U,                             /* '<S4>/Data Type Conversion19' */
  7U,                                  /* '<S4>/Data Type Conversion21' */
  1024U,                               /* '<S271>/Product10' */
  2048U,                               /* '<S271>/Product11' */
  4U,                                  /* '<S271>/Product2' */
  1024U,                               /* '<S272>/Product10' */
  2048U,                               /* '<S272>/Product11' */
  4U,                                  /* '<S272>/Product2' */
  2048U,                               /* '<S1019>/Data Type Conversion11' */
  0U,                                  /* '<S1019>/Data Type Conversion16' */
  0U,                                  /* '<S1019>/Data Type Conversion42' */
  16U,                                 /* '<S1019>/Data Type Conversion54' */
  0U,                                  /* '<S1019>/Gain53' */
  0.000200000009F,                     /* '<S52>/Add' */
  -200.0F,                             /* '<S55>/Gain' */
  -200.0F,                             /* '<S55>/Gain4' */
  1.0F,                                /* '<S61>/Data Type Conversion' */
  -1.0F,                               /* '<S61>/Gain2' */
  -20.0F,                              /* '<S61>/Gain' */
  20.0F,                               /* '<S61>/Gain1' */
  -0.02F,                              /* '<S61>/Product3' */
  0.02F,                               /* '<S61>/Product5' */
  1.0F,                                /* '<S62>/Data Type Conversion' */
  -1.0F,                               /* '<S62>/Gain2' */
  -20.0F,                              /* '<S62>/Gain' */
  20.0F,                               /* '<S62>/Gain1' */
  -0.02F,                              /* '<S62>/Product3' */
  0.02F,                               /* '<S62>/Product5' */
  -5.0F,                               /* '<S70>/Gain2' */
  -100.0F,                             /* '<S70>/Gain' */
  100.0F,                              /* '<S70>/Gain1' */
  -0.1F,                               /* '<S70>/Product3' */
  0.1F,                                /* '<S70>/Product5' */
  -5.0F,                               /* '<S80>/Gain2' */
  -100.0F,                             /* '<S80>/Gain' */
  100.0F,                              /* '<S80>/Gain1' */
  -0.1F,                               /* '<S80>/Product3' */
  0.1F,                                /* '<S80>/Product5' */
  -0.5F,                               /* '<S57>/Gain2' */
  -10.0F,                              /* '<S57>/Gain' */
  10.0F,                               /* '<S57>/Gain1' */
  -0.01F,                              /* '<S57>/Product3' */
  0.01F,                               /* '<S57>/Product5' */
  -100.0F,                             /* '<S85>/Gain' */
  -2.0F,                               /* '<S88>/Gain2' */
  -0.04F,                              /* '<S88>/Gain' */
  0.04F,                               /* '<S88>/Gain1' */
  -10.0F,                              /* '<S101>/Gain2' */
  -200.0F,                             /* '<S101>/Gain' */
  200.0F,                              /* '<S101>/Gain1' */
  -0.2F,                               /* '<S101>/Product3' */
  0.2F,                                /* '<S101>/Product5' */
  -10.0F,                              /* '<S102>/Gain2' */
  -200.0F,                             /* '<S102>/Gain' */
  200.0F,                              /* '<S102>/Gain1' */
  -0.2F,                               /* '<S102>/Product3' */
  0.2F,                                /* '<S102>/Product5' */
  -8.0F,                               /* '<S103>/Gain2' */
  -160.0F,                             /* '<S103>/Gain' */
  160.0F,                              /* '<S103>/Gain1' */
  -0.16F,                              /* '<S103>/Product3' */
  0.16F,                               /* '<S103>/Product5' */
  -8.0F,                               /* '<S104>/Gain5' */
  -160.0F,                             /* '<S104>/Gain3' */
  160.0F,                              /* '<S104>/Gain4' */
  -0.16F,                              /* '<S104>/Product3' */
  0.16F,                               /* '<S104>/Product5' */
  -1.0F,                               /* '<S139>/Gain2' */
  -0.02F,                              /* '<S139>/Gain' */
  0.02F,                               /* '<S139>/Gain1' */
  -1.0F,                               /* '<S142>/Gain2' */
  -0.02F,                              /* '<S142>/Gain' */
  0.02F,                               /* '<S142>/Gain1' */
  -1.0F,                               /* '<S145>/Gain2' */
  -0.02F,                              /* '<S145>/Gain' */
  0.02F,                               /* '<S145>/Gain1' */
  -1.0F,                               /* '<S148>/Gain2' */
  -0.02F,                              /* '<S148>/Gain' */
  0.02F,                               /* '<S148>/Gain1' */
  -167000.0F,                          /* '<S39>/Gain1' */
  3.089F,                              /* '<S39>/Add2' */
  -0.00597538613F,                     /* '<S39>/Product4' */
  -157000.0F,                          /* '<S39>/Gain' */
  -0.00766503578F,                     /* '<S39>/Product5' */
  0.00168964965F,                      /* '<S39>/Add1' */
  -0.5F,                               /* '<S157>/Gain2' */
  -10.0F,                              /* '<S157>/Gain' */
  10.0F,                               /* '<S157>/Gain1' */
  -0.01F,                              /* '<S157>/Product3' */
  0.01F,                               /* '<S157>/Product5' */
  -0.5F,                               /* '<S158>/Gain2' */
  -10.0F,                              /* '<S158>/Gain' */
  10.0F,                               /* '<S158>/Gain1' */
  -0.01F,                              /* '<S158>/Product3' */
  0.01F,                               /* '<S158>/Product5' */
  -0.5F,                               /* '<S159>/Gain2' */
  -10.0F,                              /* '<S159>/Gain' */
  10.0F,                               /* '<S159>/Gain1' */
  -0.01F,                              /* '<S159>/Product3' */
  0.01F,                               /* '<S159>/Product5' */
  -0.5F,                               /* '<S160>/Gain2' */
  -10.0F,                              /* '<S160>/Gain' */
  10.0F,                               /* '<S160>/Gain1' */
  -0.01F,                              /* '<S160>/Product3' */
  0.01F,                               /* '<S160>/Product5' */
  -1.0F,                               /* '<S162>/Gain2' */
  -0.02F,                              /* '<S162>/Gain' */
  0.02F,                               /* '<S162>/Gain1' */
  -1.0F,                               /* '<S165>/Gain2' */
  -0.02F,                              /* '<S165>/Gain' */
  0.02F,                               /* '<S165>/Gain1' */
  200.0F,                              /* '<S172>/Data Type Conversion1' */
  5.0F,                                /* '<S204>/Data Type Conversion1' */
  -0.1F,                               /* '<S183>/Gain' */
  -0.1F,                               /* '<S183>/Gain1' */
  -0.3F,                               /* '<S178>/Gain3' */
  0.2F,                                /* '<S179>/Divide' */
  4.0F,                                /* '<S179>/Product' */
  -4.0F,                               /* '<S179>/Gain1' */
  0.05F,                               /* '<S18>/Saturation' */
  0.05F,                               /* '<S18>/Saturation1' */
  0.0015F,                             /* '<S18>/Gain3' */
  -0.0015F,                            /* '<S18>/Gain33' */
  1.0F,                                /* '<S4>/Saturation' */
  1.0F,                                /* '<S4>/Data Type Conversion8' */
  1.0F,                                /* '<S4>/Saturation1' */
  1.0F,                                /* '<S4>/Data Type Conversion9' */
  0.0F,                                /* '<S4>/Signal Conversion5' */
  0.02F,                               /* '<S284>/Data Type Conversion1' */
  0.02F,                               /* '<S284>/Data Type Conversion' */
  0.1F,                                /* '<S302>/Data Type Conversion1' */
  0.1F,                                /* '<S308>/Data Type Conversion1' */
  0.1F,                                /* '<S305>/Data Type Conversion1' */
  0.1F,                                /* '<S311>/Data Type Conversion1' */
  0.1F,                                /* '<S279>/Data Type Conversion1' */
  0.1F,                                /* '<S280>/Data Type Conversion1' */
  0.1F,                                /* '<S326>/Data Type Conversion1' */
  0.1F,                                /* '<S328>/Data Type Conversion1' */
  0.1F,                                /* '<S330>/Data Type Conversion1' */
  0.1F,                                /* '<S331>/Data Type Conversion1' */
  0.1F,                                /* '<S339>/Data Type Conversion1' */
  0.1F,                                /* '<S345>/Data Type Conversion1' */
  0.1F,                                /* '<S342>/Data Type Conversion1' */
  0.1F,                                /* '<S348>/Data Type Conversion1' */
  1000.0F,                             /* '<S350>/Product' */
  1600.0F,                             /* '<S350>/Product1' */
  0.1F,                                /* '<S355>/Data Type Conversion1' */
  0.1F,                                /* '<S358>/Data Type Conversion1' */
  0.1F,                                /* '<S361>/Data Type Conversion1' */
  0.1F,                                /* '<S364>/Data Type Conversion1' */
  0.1F,                                /* '<S383>/Data Type Conversion1' */
  0.1F,                                /* '<S385>/Data Type Conversion1' */
  0.1F,                                /* '<S387>/Data Type Conversion1' */
  0.1F,                                /* '<S389>/Data Type Conversion1' */
  0.1F,                                /* '<S394>/Data Type Conversion1' */
  0.1F,                                /* '<S395>/Data Type Conversion1' */
  0.399999976F,                        /* '<S282>/Gain' */
  0.399999976F,                        /* '<S283>/Gain' */
  0.0F,                                /* '<S6>/Data Type Conversion' */
  0.25F,                               /* '<S882>/Data Type Conversion19' */
  0.25F,                               /* '<S882>/Data Type Conversion50' */
  -0.0015F,                            /* '<S919>/Gain33' */
  0.0015F,                             /* '<S919>/Gain34' */
  3.9F,                                /* '<S982>/Constant' */
  100.0F,                              /* '<S983>/Data Type Conversion6' */
  0.0F,                                /* '<S983>/Data Type Conversion8' */
  0.0F,                                /* '<S983>/Data Type Conversion9' */
  1.8F,                                /* '<S987>/Constant5' */
  3.089F,                              /* '<S9>/Add1' */
  0.95F,                               /* '<S1003>/Gain' */
  15.210001F,                          /* '<S1003>/Square1' */
  255.0F,                              /* '<S440>/Data Type Conversion' */
  0.0F,                                /* '<S430>/Gain' */
  250.0F,                              /* '<S460>/Data Type Conversion' */
  500.0F,                              /* '<S481>/Data Type Conversion1' */
  3000.0F,                             /* '<S482>/Data Type Conversion1' */
  3000.0F,                             /* '<S483>/Data Type Conversion1' */
  200.0F,                              /* '<S511>/Data Type Conversion1' */
  500.0F,                              /* '<S489>/Data Type Conversion1' */
  500.0F,                              /* '<S491>/Data Type Conversion1' */
  200.0F,                              /* '<S492>/Data Type Conversion1' */
  200.0F,                              /* '<S493>/Data Type Conversion1' */
  300.0F,                              /* '<S517>/Data Type Conversion1' */
  300.0F,                              /* '<S518>/Data Type Conversion1' */
  3000.0F,                             /* '<S537>/Data Type Conversion1' */
  3000.0F,                             /* '<S538>/Data Type Conversion1' */
  500.0F,                              /* '<S547>/Data Type Conversion1' */
  200.0F,                              /* '<S548>/Data Type Conversion1' */
  500.0F,                              /* '<S551>/Data Type Conversion1' */
  200.0F,                              /* '<S552>/Data Type Conversion1' */
  300.0F,                              /* '<S555>/Data Type Conversion1' */
  300.0F,                              /* '<S556>/Data Type Conversion1' */
  -0.0F,                               /* '<S561>/Gain' */
  -0.0F,                               /* '<S533>/Gain1' */
  -0.0F,                               /* '<S533>/Gain2' */
  -0.0F,                               /* '<S561>/Gain1' */
  -0.0F,                               /* '<S561>/Gain2' */
  -0.0F,                               /* '<S561>/Gain3' */
  -0.001F,                             /* '<S561>/Product' */
  9.54192066F,                         /* '<S562>/Product1' */
  29.4749928F,                         /* '<S562>/Product2' */
  0.0F,                                /* '<S533>/Switch23' */
  0.0F,                                /* '<S533>/Switch23' */
  0.0F,                                /* '<S533>/Switch23' */
  0.0F,                                /* '<S533>/Switch23' */
  0.0F,                                /* '<S533>/Switch23' */
  -0.0F,                               /* '<S568>/Gain' */
  -0.0F,                               /* '<S568>/Gain1' */
  -0.0F,                               /* '<S568>/Gain2' */
  -0.0F,                               /* '<S568>/Gain3' */
  9.54192066F,                         /* '<S569>/Product1' */
  29.4749928F,                         /* '<S569>/Product2' */
  0.0F,                                /* '<S534>/Switch23' */
  0.0F,                                /* '<S534>/Switch23' */
  0.0F,                                /* '<S534>/Switch23' */
  0.0F,                                /* '<S534>/Switch23' */
  0.0F,                                /* '<S534>/Switch23' */
  -0.2F,                               /* '<S573>/Gain' */
  -0.0F,                               /* '<S535>/Gain' */
  -0.0F,                               /* '<S535>/Gain2' */
  -0.2F,                               /* '<S584>/Gain' */
  -0.2F,                               /* '<S600>/Gain' */
  -0.0F,                               /* '<S595>/Gain' */
  -0.0F,                               /* '<S595>/Gain2' */
  -0.5F,                               /* '<S596>/Gain' */
  -0.5F,                               /* '<S596>/Gain1' */
  0.02F,                               /* '<S596>/Gain2' */
  -3.0F,                               /* '<S596>/Gain3' */
  9.54192066F,                         /* '<S597>/Product1' */
  29.4749928F,                         /* '<S597>/Product2' */
  9.54192066F,                         /* '<S598>/Product1' */
  29.4749928F,                         /* '<S598>/Product2' */
  -0.2F,                               /* '<S613>/Gain' */
  4500.0F,                             /* '<S633>/Data Type Conversion1' */
  20.0F,                               /* '<S634>/Data Type Conversion1' */
  1000.0F,                             /* '<S644>/Data Type Conversion1' */
  1000.0F,                             /* '<S652>/Data Type Conversion1' */
  0.3F,                                /* '<S656>/Data Type Conversion' */
  0.3F,                                /* '<S657>/Data Type Conversion' */
  0.3F,                                /* '<S658>/Data Type Conversion' */
  0.3F,                                /* '<S659>/Data Type Conversion' */
  0.3F,                                /* '<S660>/Data Type Conversion' */
  1000.0F,                             /* '<S672>/Data Type Conversion1' */
  150.0F,                              /* '<S677>/Sum' */
  0.13333334F,                         /* '<S677>/Product' */
  0.13333334F,                         /* '<S662>/Data Type Conversion' */
  0.0400000028F,                       /* '<S676>/Gain1' */
  -0.0005F,                            /* '<S663>/Gain3' */
  -0.0100000007F,                      /* '<S663>/Gain' */
  0.0100000007F,                       /* '<S663>/Gain2' */
  -1.00000007E-5F,                     /* '<S663>/Product2' */
  1.00000007E-5F,                      /* '<S663>/Product3' */
  0.0F,                                /* '<S870>/Data Type Conversion1' */
  0.0F,                                /* '<S870>/Data Type Conversion2' */
  0.0F,                                /* '<S870>/Data Type Conversion4' */
  0.0F,                                /* '<S870>/Data Type Conversion5' */
  0.0F,                                /* '<S871>/Data Type Conversion3' */
  8.0F,                                /* '<S690>/Abs' */
  8.0F,                                /* '<S693>/Abs' */
  200.0F,                              /* '<S769>/Data Type Conversion' */
  200.0F,                              /* '<S807>/Data Type Conversion1' */
  200.0F,                              /* '<S808>/Data Type Conversion1' */
  200.0F,                              /* '<S809>/Data Type Conversion1' */
  200.0F,                              /* '<S810>/Data Type Conversion1' */
  6000.0F,                             /* '<S839>/Data Type Conversion1' */
  100.0F,                              /* '<S866>/Sum' */
  0.2F,                                /* '<S866>/Product' */
  220.0F,                              /* '<S791>/Sum' */
  0.0909090936F,                       /* '<S791>/Product' */
  200.0F,                              /* '<S683>/Data Type Conversion' */
  8.0F,                                /* '<S683>/MinMax4' */
  200.0F,                              /* '<S746>/Data Type Conversion1' */
  200.0F,                              /* '<S747>/Data Type Conversion1' */
  400.0F,                              /* '<S748>/Data Type Conversion1' */
  150.0F,                              /* '<S749>/Data Type Conversion1' */
  6000.0F,                             /* '<S750>/Data Type Conversion1' */
  220.0F,                              /* '<S751>/Sum' */
  0.0909090936F,                       /* '<S751>/Product' */
  150.0F,                              /* '<S643>/Data Type Conversion1' */
  120.0F,                              /* '<S526>/Sum' */
  0.166666672F,                        /* '<S526>/Product' */
  220.0F,                              /* '<S510>/Sum' */
  0.0909090936F,                       /* '<S510>/Product' */
  220.0F,                              /* '<S506>/Sum' */
  0.0909090936F,                       /* '<S506>/Product' */
  270.0F,                              /* '<S474>/Sum' */
  0.0740740746F,                       /* '<S474>/Product' */
  220.0F,                              /* '<S393>/Sum' */
  0.0909090936F,                       /* '<S393>/Product' */
  40.0F,                               /* '<S223>/Sum' */
  0.5F,                                /* '<S223>/Product' */
  26.666666F,                          /* '<S216>/Divide' */
  0.533333302F,                        /* '<S216>/Product' */
  0.533333302F,                        /* '<S216>/Abs1' */
  1.0666666F,                          /* '<S216>/Gain' */
  26.666666F,                          /* '<S215>/Divide' */
  0.533333302F,                        /* '<S215>/Product' */
  0.533333302F,                        /* '<S215>/Abs1' */
  1.0666666F,                          /* '<S215>/Gain' */
  15U,                                 /* '<S862>/Data Type Conversion' */
  0U,                                  /* '<S4>/Data Type Conversion1' */
  0U,                                  /* '<S4>/Data Type Conversion2' */
  7U,                                  /* '<S4>/Signal Conversion14' */
  3U,                                  /* '<S983>/Data Type Conversion4' */
  4U,                                  /* '<S983>/Data Type Conversion5' */
  1U,                                  /* '<S9>/Constant17' */
  0U,                                  /* '<S1019>/Gain41' */
  0U,                                  /* '<S1019>/Signal Conversion' */
  0U,                                  /* '<S533>/Switch23' */
  0U,                                  /* '<S534>/Switch23' */
  0U,                                  /* '<S870>/Data Type Conversion10' */
  0U,                                  /* '<S870>/Data Type Conversion11' */
  0U,                                  /* '<S870>/Data Type Conversion12' */
  0U,                                  /* '<S870>/Data Type Conversion13' */
  0U,                                  /* '<S870>/Data Type Conversion7' */
  0U,                                  /* '<S870>/Data Type Conversion8' */
  0U,                                  /* '<S870>/Data Type Conversion9' */
  8U,                                  /* '<S871>/TJA_SP_TYPE_POHPP' */
  15U,                                 /* '<S862>/Saturation' */
  128U,                                /* '<S1019>/Gain48' */
  128U,                                /* '<S1019>/Gain11' */
  0U,                                  /* '<S1019>/Gain16' */
  1,                                   /* '<S52>/NOT' */
  0,                                   /* '<S180>/Compare' */
  0,                                   /* '<S219>/Compare' */
  0,                                   /* '<S4>/Signal Conversion3' */
  0,                                   /* '<S4>/Signal Conversion6' */
  1,                                   /* '<S414>/Compare' */
  1,                                   /* '<S416>/Compare' */
  1,                                   /* '<S268>/Logical Operator3' */
  1,                                   /* '<S268>/Logical Operator4' */
  1,                                   /* '<S1033>/Compare' */
  0,                                   /* '<S1048>/Compare' */
  0,                                   /* '<S1078>/Compare' */
  1,                                   /* '<S1091>/Compare' */
  0,                                   /* '<S445>/Relational Operator' */
  0,                                   /* '<S445>/Relational Operator1' */
  0,                                   /* '<S446>/Relational Operator' */
  0,                                   /* '<S446>/Relational Operator1' */
  1,                                   /* '<S464>/Logical Operator1' */
  0,                                   /* '<S561>/Relational Operator' */
  0,                                   /* '<S561>/Relational Operator1' */
  1,                                   /* '<S561>/Relational Operator3' */
  0,                                   /* '<S561>/Logical Operator' */
  0,                                   /* '<S561>/Relational Operator2' */
  0,                                   /* '<S561>/Logical Operator1' */
  0,                                   /* '<S533>/Switch23' */
  0,                                   /* '<S533>/Switch23' */
  0,                                   /* '<S568>/Relational Operator' */
  0,                                   /* '<S568>/Relational Operator1' */
  1,                                   /* '<S568>/Relational Operator3' */
  0,                                   /* '<S568>/Logical Operator' */
  0,                                   /* '<S568>/Relational Operator2' */
  0,                                   /* '<S568>/Logical Operator1' */
  0,                                   /* '<S534>/Switch23' */
  0,                                   /* '<S534>/Switch23' */
  0,                                   /* '<S681>/Logical Operator11' */
  0,                                   /* '<S781>/Relational Operator' */
  0,                                   /* '<S781>/Relational Operator1' */
  0,                                   /* '<S781>/Logical Operator' */
  0,                                   /* '<S781>/Relational Operator22' */
  0,                                   /* '<S781>/Relational Operator23' */
  0,                                   /* '<S781>/Logical Operator1' */
  0,                                   /* '<S781>/Relational Operator5' */
  0,                                   /* '<S781>/Relational Operator6' */
  0,                                   /* '<S781>/Logical Operator2' */
  0,                                   /* '<S781>/Relational Operator7' */
  0,                                   /* '<S781>/Relational Operator8' */
  0,                                   /* '<S781>/Logical Operator3' */
  0,                                   /* '<S781>/Relational Operator10' */
  0,                                   /* '<S781>/Relational Operator11' */
  0,                                   /* '<S781>/Logical Operator4' */
  0,                                   /* '<S781>/Relational Operator2' */
  0,                                   /* '<S781>/Relational Operator3' */
  0,                                   /* '<S781>/Logical Operator5' */
  0,                                   /* '<S781>/Relational Operator15' */
  0,                                   /* '<S781>/Relational Operator16' */
  0,                                   /* '<S781>/Logical Operator6' */
  0,                                   /* '<S781>/Relational Operator17' */
  0,                                   /* '<S781>/Relational Operator18' */
  0,                                   /* '<S781>/Logical Operator7' */
  0,                                   /* '<S781>/Relational Operator20' */
  0,                                   /* '<S781>/Relational Operator21' */
  0,                                   /* '<S781>/Logical Operator8' */
  0,                                   /* '<S781>/Relational Operator25' */
  0,                                   /* '<S781>/Relational Operator26' */
  0,                                   /* '<S781>/Logical Operator9' */
  0,                                   /* '<S781>/Relational Operator14' */
  0,                                   /* '<S781>/Relational Operator19' */
  0,                                   /* '<S781>/Relational Operator24' */
  0,                                   /* '<S781>/Relational Operator4' */
  0,                                   /* '<S781>/Relational Operator9' */
  0,                                   /* '<S769>/Relational Operator1' */
  0,                                   /* '<S769>/Relational Operator2' */
  0,                                   /* '<S769>/Relational Operator3' */
  0,                                   /* '<S769>/Relational Operator4' */
  0,                                   /* '<S792>/Relational Operator15' */
  0,                                   /* '<S792>/Relational Operator16' */
  0,                                   /* '<S792>/Relational Operator17' */
  0,                                   /* '<S792>/Relational Operator18' */
  0,                                   /* '<S792>/Logical Operator6' */
  0,                                   /* '<S792>/Relational Operator19' */
  0,                                   /* '<S772>/Relational Operator10' */
  0,                                   /* '<S772>/Relational Operator11' */
  0,                                   /* '<S772>/Relational Operator15' */
  0,                                   /* '<S772>/Relational Operator5' */
  0,                                   /* '<S772>/Relational Operator7' */
  0,                                   /* '<S772>/Relational Operator8' */
  0,                                   /* '<S684>/Relational Operator9' */
  0,                                   /* '<S684>/Relational Operator14' */
  0,                                   /* '<S684>/Logical Operator4' */
  0,                                   /* '<S684>/Relational Operator19' */
  0,                                   /* '<S831>/Relational Operator10' */
  0,                                   /* '<S831>/Relational Operator11' */
  0,                                   /* '<S831>/Logical Operator10' */
  1,                                   /* '<S721>/Logical Operator2' */
  0,                                   /* '<S683>/Relational Operator8' */
  0,                                   /* '<S683>/Relational Operator12' */
  0,                                   /* '<S683>/Logical Operator11' */
  1,                                   /* '<S722>/Logical Operator2' */
  1,                                   /* '<S723>/Logical Operator2' */
  1,                                   /* '<S724>/Logical Operator2' */
  1,                                   /* '<S725>/Logical Operator2' */
  1,                                   /* '<S726>/Logical Operator2' */
  0,                                   /* '<S683>/Relational Operator14' */
  0,                                   /* '<S683>/Relational Operator21' */
  0,                                   /* '<S683>/Logical Operator4' */
  1,                                   /* '<S683>/Logical Operator2' */
  1,                                   /* '<S683>/Logical Operator22' */
  1,                                   /* '<S683>/Logical Operator25' */
  1,                                   /* '<S683>/Logical Operator9' */
  0,                                   /* '<S683>/Relational Operator1' */
  0,                                   /* '<S683>/Relational Operator11' */
  0,                                   /* '<S683>/Relational Operator13' */
  0,                                   /* '<S683>/Relational Operator15' */
  0,                                   /* '<S683>/Relational Operator16' */
  0,                                   /* '<S683>/Relational Operator30' */
  0,                                   /* '<S683>/Relational Operator31' */
  0,                                   /* '<S683>/Relational Operator6' */
  0,                                   /* '<S683>/Relational Operator7' */

  /* Start of '<S1137>/SfD1' */
  {
    0.02F,                             /* '<S1150>/Abs' */
    1.0F,                              /* '<S1150>/Sign' */
    1.0F,                              /* '<S1150>/Switch1' */
    1                                  /* '<S1151>/Compare' */
  }
  ,

  /* End of '<S1137>/SfD1' */

  /* Start of '<S1136>/SfD1' */
  {
    0.02F,                             /* '<S1147>/Abs' */
    1.0F,                              /* '<S1147>/Sign' */
    1.0F,                              /* '<S1147>/Switch1' */
    1                                  /* '<S1148>/Compare' */
  }
  ,

  /* End of '<S1136>/SfD1' */

  /* Start of '<S1028>/SfD1' */
  {
    0.02F,                             /* '<S1142>/Abs' */
    1.0F,                              /* '<S1142>/Sign' */
    1.0F,                              /* '<S1142>/Switch1' */
    1                                  /* '<S1143>/Compare' */
  }
  ,

  /* End of '<S1028>/SfD1' */

  /* Start of '<S1027>/SfD1' */
  {
    0.02F,                             /* '<S1139>/Abs' */
    1.0F,                              /* '<S1139>/Sign' */
    1.0F,                              /* '<S1139>/Switch1' */
    1                                  /* '<S1140>/Compare' */
  }
  ,

  /* End of '<S1027>/SfD1' */

  /* Start of '<S684>/Rate_Limiter4' */
  {
    -0.0005F,                          /* '<S776>/Gain2' */
    -0.0100000007F,                    /* '<S776>/Gain' */
    0.0100000007F,                     /* '<S776>/Gain1' */
    -1.00000007E-5F,                   /* '<S776>/Product' */
    1.00000007E-5F                     /* '<S776>/Product2' */
  }
  ,

  /* End of '<S684>/Rate_Limiter4' */

  /* Start of '<S684>/Rate_Limiter3' */
  {
    -0.004F,                           /* '<S775>/Gain2' */
    -0.0800000057F,                    /* '<S775>/Gain' */
    0.0800000057F,                     /* '<S775>/Gain1' */
    -8.00000053E-5F,                   /* '<S775>/Product' */
    8.00000053E-5F                     /* '<S775>/Product2' */
  }
  ,

  /* End of '<S684>/Rate_Limiter3' */

  /* Start of '<S684>/Rate_Limiter2' */
  {
    -0.05F,                            /* '<S774>/Gain2' */
    -1.0F,                             /* '<S774>/Gain' */
    1.0F,                              /* '<S774>/Gain1' */
    -0.001F,                           /* '<S774>/Product' */
    0.001F                             /* '<S774>/Product2' */
  }
  ,

  /* End of '<S684>/Rate_Limiter2' */

  /* Start of '<S684>/Rate_Limiter' */
  {
    -2.0F,                             /* '<S773>/Gain2' */
    -40.0F,                            /* '<S773>/Gain' */
    40.0F,                             /* '<S773>/Gain1' */
    -0.04F,                            /* '<S773>/Product' */
    0.04F                              /* '<S773>/Product2' */
  }
  ,

  /* End of '<S684>/Rate_Limiter' */

  /* Start of '<S772>/Rate_Limiter6' */
  {
    -0.2F,                             /* '<S802>/Gain2' */
    -4.0F,                             /* '<S802>/Gain' */
    4.0F,                              /* '<S802>/Gain1' */
    -0.004F,                           /* '<S802>/Product' */
    0.004F                             /* '<S802>/Product2' */
  }
  ,

  /* End of '<S772>/Rate_Limiter6' */

  /* Start of '<S772>/Rate_Limiter5' */
  {
    -0.2F,                             /* '<S801>/Gain2' */
    -4.0F,                             /* '<S801>/Gain' */
    4.0F,                              /* '<S801>/Gain1' */
    -0.004F,                           /* '<S801>/Product' */
    0.004F                             /* '<S801>/Product2' */
  }
  ,

  /* End of '<S772>/Rate_Limiter5' */

  /* Start of '<S772>/First_Order_Lag_Filter_LIB7' */
  {
    40.0F,                             /* '<S818>/Sum' */
    0.5F                               /* '<S818>/Product' */
  }
  ,

  /* End of '<S772>/First_Order_Lag_Filter_LIB7' */

  /* Start of '<S772>/First_Order_Lag_Filter_LIB6' */
  {
    40.0F,                             /* '<S817>/Sum' */
    0.5F                               /* '<S817>/Product' */
  }
  ,

  /* End of '<S772>/First_Order_Lag_Filter_LIB6' */

  /* Start of '<S772>/First_Order_Lag_Filter_LIB14' */
  {
    80.0F,                             /* '<S815>/Sum' */
    0.25F                              /* '<S815>/Product' */
  }
  ,

  /* End of '<S772>/First_Order_Lag_Filter_LIB14' */

  /* Start of '<S772>/First_Order_Lag_Filter_LIB13' */
  {
    80.0F,                             /* '<S814>/Sum' */
    0.25F                              /* '<S814>/Product' */
  }
  ,

  /* End of '<S772>/First_Order_Lag_Filter_LIB13' */

  /* Start of '<S794>/Rate_Limiter1' */
  {
    -0.3F,                             /* '<S812>/Gain2' */
    -6.0F,                             /* '<S812>/Gain' */
    6.0F,                              /* '<S812>/Gain1' */
    -0.006F,                           /* '<S812>/Product' */
    0.006F                             /* '<S812>/Product2' */
  }
  ,

  /* End of '<S794>/Rate_Limiter1' */

  /* Start of '<S794>/First_Order_Lag_Filter_LIB1' */
  {
    2020.0F,                           /* '<S813>/Sum' */
    0.00990099F                        /* '<S813>/Product' */
  }
  ,

  /* End of '<S794>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S684>/First_Order_Lag_Filter_LIB4' */
  {
    80.0F,                             /* '<S780>/Sum' */
    0.25F                              /* '<S780>/Product' */
  }
  ,

  /* End of '<S684>/First_Order_Lag_Filter_LIB4' */

  /* Start of '<S684>/First_Order_Lag_Filter_LIB3' */
  {
    80.0F,                             /* '<S779>/Sum' */
    0.25F                              /* '<S779>/Product' */
  }
  ,

  /* End of '<S684>/First_Order_Lag_Filter_LIB3' */

  /* Start of '<S684>/First_Order_Lag_Filter_LIB2' */
  {
    80.0F,                             /* '<S778>/Sum' */
    0.25F                              /* '<S778>/Product' */
  }
  ,

  /* End of '<S684>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S684>/First_Order_Lag_Filter_LIB' */
  {
    80.0F,                             /* '<S777>/Sum' */
    0.25F                              /* '<S777>/Product' */
  }
  ,

  /* End of '<S684>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S683>/Rate_Limiter6' */
  {
    -0.035F,                           /* '<S742>/Gain2' */
    -0.7F,                             /* '<S742>/Gain' */
    0.7F,                              /* '<S742>/Gain1' */
    -0.0007F,                          /* '<S742>/Product' */
    0.0007F                            /* '<S742>/Product2' */
  }
  ,

  /* End of '<S683>/Rate_Limiter6' */

  /* Start of '<S683>/Rate_Limiter4' */
  {
    -0.035F,                           /* '<S741>/Gain2' */
    -0.7F,                             /* '<S741>/Gain' */
    0.7F,                              /* '<S741>/Gain1' */
    -0.0007F,                          /* '<S741>/Product' */
    0.0007F                            /* '<S741>/Product2' */
  }
  ,

  /* End of '<S683>/Rate_Limiter4' */

  /* Start of '<S683>/Rate_Limiter1' */
  {
    -0.3F,                             /* '<S738>/Gain2' */
    -6.0F,                             /* '<S738>/Gain' */
    6.0F,                              /* '<S738>/Gain1' */
    -0.006F,                           /* '<S738>/Product' */
    0.006F                             /* '<S738>/Product2' */
  }
  ,

  /* End of '<S683>/Rate_Limiter1' */

  /* Start of '<S683>/Rate_Limiter' */
  {
    -0.5F,                             /* '<S737>/Gain2' */
    -10.0F,                            /* '<S737>/Gain' */
    10.0F,                             /* '<S737>/Gain1' */
    -0.01F,                            /* '<S737>/Product' */
    0.01F                              /* '<S737>/Product2' */
  }
  ,

  /* End of '<S683>/Rate_Limiter' */

  /* Start of '<S683>/First_Order_Lag_Filter_LIB6' */
  {
    120.0F,                            /* '<S758>/Sum' */
    0.166666672F                       /* '<S758>/Product' */
  }
  ,

  /* End of '<S683>/First_Order_Lag_Filter_LIB6' */

  /* Start of '<S683>/First_Order_Lag_Filter_LIB3' */
  {
    80.0F,                             /* '<S755>/Sum' */
    0.25F                              /* '<S755>/Product' */
  }
  ,

  /* End of '<S683>/First_Order_Lag_Filter_LIB3' */

  /* Start of '<S683>/First_Order_Lag_Filter_LIB2' */
  {
    120.0F,                            /* '<S754>/Sum' */
    0.166666672F                       /* '<S754>/Product' */
  }
  ,

  /* End of '<S683>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S683>/First_Order_Lag_Filter_LIB1' */
  {
    2020.0F,                           /* '<S753>/Sum' */
    0.00990099F                        /* '<S753>/Product' */
  }
  ,

  /* End of '<S683>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S661>/Delay_set_EP' */
  {
    150.0F                             /* '<S671>/Data Type Conversion1' */
  }
  ,

  /* End of '<S661>/Delay_set_EP' */

  /* Start of '<S648>/Delay_set_EP' */
  {
    150.0F                             /* '<S651>/Data Type Conversion1' */
  }
  ,

  /* End of '<S648>/Delay_set_EP' */

  /* Start of '<S624>/First_Order_Lag_Filter_LIB2' */
  {
    820.0F,                            /* '<S637>/Sum' */
    0.024390243F                       /* '<S637>/Product' */
  }
  ,

  /* End of '<S624>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S624>/Delay_set_EP' */
  {
    500.0F                             /* '<S629>/Data Type Conversion1' */
  }
  ,

  /* End of '<S624>/Delay_set_EP' */

  /* Start of '<S599>/First_Order_Lag_Filter_w_IC1' */
  {
    20.0F,                             /* '<S623>/Sum' */
    1.0F                               /* '<S623>/Product' */
  }
  ,

  /* End of '<S599>/First_Order_Lag_Filter_w_IC1' */

  /* Start of '<S599>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S622>/Sum' */
    1.0F                               /* '<S622>/Product' */
  }
  ,

  /* End of '<S599>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S595>/First_Order_Lag_Filter_LIB1' */
  {
    20.0F,                             /* '<S610>/Sum' */
    1.0F                               /* '<S610>/Product' */
  }
  ,

  /* End of '<S595>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S595>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S609>/Sum' */
    1.0F                               /* '<S609>/Product' */
  }
  ,

  /* End of '<S595>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S536>/First_Order_Lag_Filter_w_IC1' */
  {
    20.0F,                             /* '<S594>/Sum' */
    1.0F                               /* '<S594>/Product' */
  }
  ,

  /* End of '<S536>/First_Order_Lag_Filter_w_IC1' */

  /* Start of '<S536>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S593>/Sum' */
    1.0F                               /* '<S593>/Product' */
  }
  ,

  /* End of '<S536>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S535>/First_Order_Lag_Filter_LIB1' */
  {
    20.0F,                             /* '<S583>/Sum' */
    1.0F                               /* '<S583>/Product' */
  }
  ,

  /* End of '<S535>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S535>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S582>/Sum' */
    1.0F                               /* '<S582>/Product' */
  }
  ,

  /* End of '<S535>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S534>/First_Order_Lag_Filter_LIB1' */
  {
    20.0F,                             /* '<S571>/Sum' */
    1.0F                               /* '<S571>/Product' */
  }
  ,

  /* End of '<S534>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S534>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S570>/Sum' */
    1.0F                               /* '<S570>/Product' */
  }
  ,

  /* End of '<S534>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S533>/First_Order_Lag_Filter_LIB1' */
  {
    20.0F,                             /* '<S564>/Sum' */
    1.0F                               /* '<S564>/Product' */
  }
  ,

  /* End of '<S533>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S533>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S563>/Sum' */
    1.0F                               /* '<S563>/Product' */
  }
  ,

  /* End of '<S533>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S539>/First_Order_Lag_Filter_w_IC_LIB' */
  {
    120.0F,                            /* '<S546>/Sum' */
    0.166666672F                       /* '<S546>/Product' */
  }
  ,

  /* End of '<S539>/First_Order_Lag_Filter_w_IC_LIB' */

  /* Start of '<S464>/First_Order_Lag_Filter_LIB2' */
  {
    820.0F,                            /* '<S523>/Sum' */
    0.024390243F                       /* '<S523>/Product' */
  }
  ,

  /* End of '<S464>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S484>/First_Order_Lag_Filter_w_IC_LIB' */
  {
    120.0F,                            /* '<S502>/Sum' */
    0.166666672F                       /* '<S502>/Product' */
  }
  ,

  /* End of '<S484>/First_Order_Lag_Filter_w_IC_LIB' */

  /* Start of '<S323>/Rate_Limiter1' */
  {
    -3.0F,                             /* '<S392>/Gain2' */
    -60.0F,                            /* '<S392>/Gain' */
    60.0F,                             /* '<S392>/Gain1' */
    -0.06F,                            /* '<S392>/Product' */
    0.06F                              /* '<S392>/Product2' */
  }
  ,

  /* End of '<S323>/Rate_Limiter1' */

  /* Start of '<S284>/First_Order_Lag_Filter_LIB2' */
  {
    0.120000005F,                      /* '<S291>/Sum' */
    0.166666657F                       /* '<S291>/Product' */
  }
  ,

  /* End of '<S284>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S284>/First_Order_Lag_Filter_LIB1' */
  {
    0.120000005F,                      /* '<S290>/Sum' */
    0.166666657F                       /* '<S290>/Product' */
  }
  ,

  /* End of '<S284>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S13>/First_Order_Lag_Filter_LIB' */
  {
    30.0F,                             /* '<S239>/Sum' */
    0.666666687F                       /* '<S239>/Product' */
  }
  ,

  /* End of '<S13>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S51>/First_Order_Lag_Filter_LIB' */
  {
    70.0F,                             /* '<S237>/Sum' */
    0.285714298F                       /* '<S237>/Product' */
  }
  ,

  /* End of '<S51>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S50>/First_Order_Lag_Filter_LIB' */
  {
    70.0F,                             /* '<S235>/Sum' */
    0.285714298F                       /* '<S235>/Product' */
  }
  ,

  /* End of '<S50>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S49>/First_Order_Lag_Filter_LIB' */
  {
    60.0F,                             /* '<S233>/Sum' */
    0.166666672F                       /* '<S233>/Product' */
  }
  ,

  /* End of '<S49>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S48>/First_Order_Lag_Filter_LIB' */
  {
    70.0F,                             /* '<S231>/Sum' */
    0.285714298F                       /* '<S231>/Product' */
  }
  ,

  /* End of '<S48>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S47>/First_Order_Lag_Filter_LIB' */
  {
    70.0F,                             /* '<S229>/Sum' */
    0.285714298F                       /* '<S229>/Product' */
  }
  ,

  /* End of '<S47>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S46>/First_Order_Lag_Filter_LIB' */
  {
    70.0F,                             /* '<S227>/Sum' */
    0.285714298F                       /* '<S227>/Product' */
  }
  ,

  /* End of '<S46>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S41>/First_Order_Lag_Filter_LIB2' */
  {
    140.0F,                            /* '<S166>/Sum' */
    0.142857149F                       /* '<S166>/Product' */
  }
  ,

  /* End of '<S41>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S40>/First_Order_Lag_Filter_LIB2' */
  {
    140.0F,                            /* '<S163>/Sum' */
    0.142857149F                       /* '<S163>/Product' */
  }
  ,

  /* End of '<S40>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S38>/First_Order_Lag_Filter_LIB2' */
  {
    140.0F,                            /* '<S149>/Sum' */
    0.142857149F                       /* '<S149>/Product' */
  }
  ,

  /* End of '<S38>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S37>/First_Order_Lag_Filter_LIB2' */
  {
    140.0F,                            /* '<S146>/Sum' */
    0.142857149F                       /* '<S146>/Product' */
  }
  ,

  /* End of '<S37>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S36>/First_Order_Lag_Filter_LIB2' */
  {
    140.0F,                            /* '<S143>/Sum' */
    0.142857149F                       /* '<S143>/Product' */
  }
  ,

  /* End of '<S36>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S34>/First_Order_Lag_Filter_LIB2' */
  {
    140.0F,                            /* '<S140>/Sum' */
    0.142857149F                       /* '<S140>/Product' */
  }
  ,

  /* End of '<S34>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S122>/First_Order_Lag_Filter_LIB' */
  {
    70.0F,                             /* '<S127>/Sum' */
    0.285714298F                       /* '<S127>/Product' */
  }
  ,

  /* End of '<S122>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S121>/First_Order_Lag_Filter_LIB' */
  {
    70.0F,                             /* '<S125>/Sum' */
    0.285714298F                       /* '<S125>/Product' */
  }
  ,

  /* End of '<S121>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S24>/First_Order_Lag_Filter' */
  {
    20.0F,                             /* '<S123>/Sum' */
    1.0F                               /* '<S123>/Product' */
  }
  ,

  /* End of '<S24>/First_Order_Lag_Filter' */

  /* Start of '<S23>/First_Order_Lag_Filter_LIB' */
  {
    40.0F,                             /* '<S117>/Sum' */
    0.5F                               /* '<S117>/Product' */
  }
  ,

  /* End of '<S23>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S22>/First_Order_Lag_Filter_LIB' */
  {
    30.0F,                             /* '<S111>/Sum' */
    0.666666687F                       /* '<S111>/Product' */
  }
  ,

  /* End of '<S22>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S85>/First_Order_Lag_Filter' */
  {
    20.0F,                             /* '<S92>/Sum' */
    1.0F                               /* '<S92>/Product' */
  }
  ,

  /* End of '<S85>/First_Order_Lag_Filter' */

  /* Start of '<S55>/First_Order_Lag_Filter' */
  {
    20.0F,                             /* '<S69>/Sum' */
    1.0F                               /* '<S69>/Product' */
  }
  /* End of '<S55>/First_Order_Lag_Filter' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
