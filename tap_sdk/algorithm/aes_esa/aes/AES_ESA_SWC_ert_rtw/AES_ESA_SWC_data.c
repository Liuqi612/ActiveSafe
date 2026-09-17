/*
 * File: AES_ESA_SWC_data.c
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

#include "AES_ESA_SWC.h"
#include "AES_ESA_SWC_private.h"

/* Invariant block signals (default storage) */
const ConstB_AES_ESA_SWC_T AES_ESA_SWC_ConstB = {
  1000.0,                              /* '<S349>/MinMax2' */
  0.001,                               /* '<S349>/Divide' */
  1600.0,                              /* '<S349>/MinMax1' */
  0.000625,                            /* '<S349>/Divide1' */
  260821U,                             /* '<S4>/Signal Conversion13' */
  260821U,                             /* '<S4>/Data Type Conversion19' */
  7U,                                  /* '<S4>/Data Type Conversion21' */
  1024U,                               /* '<S271>/Product10' */
  2048U,                               /* '<S271>/Product11' */
  4U,                                  /* '<S271>/Product2' */
  512U,                                /* '<S271>/Product9' */
  1024U,                               /* '<S272>/Product10' */
  2048U,                               /* '<S272>/Product11' */
  4U,                                  /* '<S272>/Product2' */
  512U,                                /* '<S272>/Product9' */
  2048U,                               /* '<S1016>/Data Type Conversion11' */
  0U,                                  /* '<S1016>/Data Type Conversion16' */
  0U,                                  /* '<S1016>/Data Type Conversion42' */
  16U,                                 /* '<S1016>/Data Type Conversion54' */
  32U,                                 /* '<S1016>/Data Type Conversion55' */
  0U,                                  /* '<S1016>/Gain53' */
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
  0.75F,                               /* '<S4>/Saturation' */
  0.75F,                               /* '<S4>/Data Type Conversion8' */
  0.75F,                               /* '<S4>/Saturation1' */
  0.75F,                               /* '<S4>/Data Type Conversion9' */
  0.0F,                                /* '<S4>/Signal Conversion5' */
  0.02F,                               /* '<S284>/Data Type Conversion1' */
  0.02F,                               /* '<S284>/Data Type Conversion' */
  0.1F,                                /* '<S302>/Data Type Conversion1' */
  0.1F,                                /* '<S308>/Data Type Conversion1' */
  0.1F,                                /* '<S305>/Data Type Conversion1' */
  0.1F,                                /* '<S311>/Data Type Conversion1' */
  0.1F,                                /* '<S279>/Data Type Conversion1' */
  0.1F,                                /* '<S280>/Data Type Conversion1' */
  0.1F,                                /* '<S325>/Data Type Conversion1' */
  0.1F,                                /* '<S327>/Data Type Conversion1' */
  0.1F,                                /* '<S329>/Data Type Conversion1' */
  0.1F,                                /* '<S330>/Data Type Conversion1' */
  0.1F,                                /* '<S338>/Data Type Conversion1' */
  0.1F,                                /* '<S344>/Data Type Conversion1' */
  0.1F,                                /* '<S341>/Data Type Conversion1' */
  0.1F,                                /* '<S347>/Data Type Conversion1' */
  1000.0F,                             /* '<S349>/Product' */
  1600.0F,                             /* '<S349>/Product1' */
  0.1F,                                /* '<S354>/Data Type Conversion1' */
  0.1F,                                /* '<S357>/Data Type Conversion1' */
  0.1F,                                /* '<S360>/Data Type Conversion1' */
  0.1F,                                /* '<S363>/Data Type Conversion1' */
  0.1F,                                /* '<S382>/Data Type Conversion1' */
  0.1F,                                /* '<S384>/Data Type Conversion1' */
  0.1F,                                /* '<S386>/Data Type Conversion1' */
  0.1F,                                /* '<S388>/Data Type Conversion1' */
  0.1F,                                /* '<S393>/Data Type Conversion1' */
  0.1F,                                /* '<S394>/Data Type Conversion1' */
  0.399999976F,                        /* '<S282>/Gain' */
  0.399999976F,                        /* '<S283>/Gain' */
  0.0F,                                /* '<S6>/Data Type Conversion' */
  0.25F,                               /* '<S876>/Data Type Conversion19' */
  0.25F,                               /* '<S876>/Data Type Conversion50' */
  -0.0015F,                            /* '<S913>/Gain33' */
  0.0015F,                             /* '<S913>/Gain34' */
  3.9F,                                /* '<S976>/Constant' */
  100.0F,                              /* '<S977>/Data Type Conversion6' */
  0.0F,                                /* '<S977>/Data Type Conversion8' */
  0.0F,                                /* '<S977>/Data Type Conversion9' */
  1.8F,                                /* '<S981>/Constant5' */
  3.089F,                              /* '<S9>/Add1' */
  0.95F,                               /* '<S1000>/Gain' */
  15.210001F,                          /* '<S1000>/Square1' */
  255.0F,                              /* '<S434>/Data Type Conversion' */
  0.0F,                                /* '<S424>/Gain' */
  250.0F,                              /* '<S454>/Data Type Conversion' */
  500.0F,                              /* '<S475>/Data Type Conversion1' */
  3000.0F,                             /* '<S476>/Data Type Conversion1' */
  3000.0F,                             /* '<S477>/Data Type Conversion1' */
  200.0F,                              /* '<S505>/Data Type Conversion1' */
  500.0F,                              /* '<S483>/Data Type Conversion1' */
  500.0F,                              /* '<S485>/Data Type Conversion1' */
  200.0F,                              /* '<S486>/Data Type Conversion1' */
  200.0F,                              /* '<S487>/Data Type Conversion1' */
  300.0F,                              /* '<S511>/Data Type Conversion1' */
  300.0F,                              /* '<S512>/Data Type Conversion1' */
  3000.0F,                             /* '<S531>/Data Type Conversion1' */
  3000.0F,                             /* '<S532>/Data Type Conversion1' */
  500.0F,                              /* '<S541>/Data Type Conversion1' */
  200.0F,                              /* '<S542>/Data Type Conversion1' */
  500.0F,                              /* '<S545>/Data Type Conversion1' */
  200.0F,                              /* '<S546>/Data Type Conversion1' */
  300.0F,                              /* '<S549>/Data Type Conversion1' */
  300.0F,                              /* '<S550>/Data Type Conversion1' */
  -0.0F,                               /* '<S555>/Gain' */
  -0.0F,                               /* '<S527>/Gain1' */
  -0.0F,                               /* '<S527>/Gain2' */
  -0.0F,                               /* '<S555>/Gain1' */
  -0.0F,                               /* '<S555>/Gain2' */
  -0.0F,                               /* '<S555>/Gain3' */
  -0.001F,                             /* '<S555>/Product' */
  9.54192066F,                         /* '<S556>/Product1' */
  29.4749928F,                         /* '<S556>/Product2' */
  0.0F,                                /* '<S527>/Switch23' */
  0.0F,                                /* '<S527>/Switch23' */
  0.0F,                                /* '<S527>/Switch23' */
  0.0F,                                /* '<S527>/Switch23' */
  0.0F,                                /* '<S527>/Switch23' */
  -0.0F,                               /* '<S562>/Gain' */
  -0.0F,                               /* '<S562>/Gain1' */
  -0.0F,                               /* '<S562>/Gain2' */
  -0.0F,                               /* '<S562>/Gain3' */
  9.54192066F,                         /* '<S563>/Product1' */
  29.4749928F,                         /* '<S563>/Product2' */
  0.0F,                                /* '<S528>/Switch23' */
  0.0F,                                /* '<S528>/Switch23' */
  0.0F,                                /* '<S528>/Switch23' */
  0.0F,                                /* '<S528>/Switch23' */
  0.0F,                                /* '<S528>/Switch23' */
  -0.2F,                               /* '<S567>/Gain' */
  -0.0F,                               /* '<S529>/Gain' */
  -0.0F,                               /* '<S529>/Gain2' */
  -0.2F,                               /* '<S578>/Gain' */
  -0.2F,                               /* '<S594>/Gain' */
  -0.0F,                               /* '<S589>/Gain' */
  -0.0F,                               /* '<S589>/Gain2' */
  -0.5F,                               /* '<S590>/Gain' */
  -0.5F,                               /* '<S590>/Gain1' */
  0.02F,                               /* '<S590>/Gain2' */
  -3.0F,                               /* '<S590>/Gain3' */
  9.54192066F,                         /* '<S591>/Product1' */
  29.4749928F,                         /* '<S591>/Product2' */
  9.54192066F,                         /* '<S592>/Product1' */
  29.4749928F,                         /* '<S592>/Product2' */
  -0.2F,                               /* '<S607>/Gain' */
  4500.0F,                             /* '<S627>/Data Type Conversion1' */
  20.0F,                               /* '<S628>/Data Type Conversion1' */
  1000.0F,                             /* '<S638>/Data Type Conversion1' */
  1000.0F,                             /* '<S646>/Data Type Conversion1' */
  0.3F,                                /* '<S650>/Data Type Conversion' */
  0.3F,                                /* '<S651>/Data Type Conversion' */
  0.3F,                                /* '<S652>/Data Type Conversion' */
  0.3F,                                /* '<S653>/Data Type Conversion' */
  0.3F,                                /* '<S654>/Data Type Conversion' */
  1000.0F,                             /* '<S666>/Data Type Conversion1' */
  150.0F,                              /* '<S671>/Sum' */
  0.13333334F,                         /* '<S671>/Product' */
  0.13333334F,                         /* '<S656>/Data Type Conversion' */
  0.0400000028F,                       /* '<S670>/Gain1' */
  -0.0005F,                            /* '<S657>/Gain3' */
  -0.0100000007F,                      /* '<S657>/Gain' */
  0.0100000007F,                       /* '<S657>/Gain2' */
  -1.00000007E-5F,                     /* '<S657>/Product2' */
  1.00000007E-5F,                      /* '<S657>/Product3' */
  0.0F,                                /* '<S864>/Data Type Conversion1' */
  0.0F,                                /* '<S864>/Data Type Conversion2' */
  0.0F,                                /* '<S864>/Data Type Conversion4' */
  0.0F,                                /* '<S864>/Data Type Conversion5' */
  0.0F,                                /* '<S865>/Data Type Conversion3' */
  8.0F,                                /* '<S684>/Abs' */
  8.0F,                                /* '<S687>/Abs' */
  200.0F,                              /* '<S763>/Data Type Conversion' */
  200.0F,                              /* '<S801>/Data Type Conversion1' */
  200.0F,                              /* '<S802>/Data Type Conversion1' */
  200.0F,                              /* '<S803>/Data Type Conversion1' */
  200.0F,                              /* '<S804>/Data Type Conversion1' */
  6000.0F,                             /* '<S833>/Data Type Conversion1' */
  100.0F,                              /* '<S860>/Sum' */
  0.2F,                                /* '<S860>/Product' */
  220.0F,                              /* '<S785>/Sum' */
  0.0909090936F,                       /* '<S785>/Product' */
  200.0F,                              /* '<S677>/Data Type Conversion' */
  8.0F,                                /* '<S677>/MinMax4' */
  200.0F,                              /* '<S740>/Data Type Conversion1' */
  200.0F,                              /* '<S741>/Data Type Conversion1' */
  400.0F,                              /* '<S742>/Data Type Conversion1' */
  150.0F,                              /* '<S743>/Data Type Conversion1' */
  6000.0F,                             /* '<S744>/Data Type Conversion1' */
  220.0F,                              /* '<S745>/Sum' */
  0.0909090936F,                       /* '<S745>/Product' */
  150.0F,                              /* '<S637>/Data Type Conversion1' */
  120.0F,                              /* '<S520>/Sum' */
  0.166666672F,                        /* '<S520>/Product' */
  220.0F,                              /* '<S504>/Sum' */
  0.0909090936F,                       /* '<S504>/Product' */
  220.0F,                              /* '<S500>/Sum' */
  0.0909090936F,                       /* '<S500>/Product' */
  270.0F,                              /* '<S468>/Sum' */
  0.0740740746F,                       /* '<S468>/Product' */
  220.0F,                              /* '<S392>/Sum' */
  0.0909090936F,                       /* '<S392>/Product' */
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
  15U,                                 /* '<S856>/Data Type Conversion' */
  0U,                                  /* '<S4>/Data Type Conversion1' */
  0U,                                  /* '<S4>/Data Type Conversion2' */
  7U,                                  /* '<S4>/Signal Conversion14' */
  3U,                                  /* '<S977>/Data Type Conversion4' */
  4U,                                  /* '<S977>/Data Type Conversion5' */
  1U,                                  /* '<S9>/Constant17' */
  0U,                                  /* '<S1016>/Gain41' */
  0U,                                  /* '<S1016>/Signal Conversion' */
  0U,                                  /* '<S527>/Switch23' */
  0U,                                  /* '<S528>/Switch23' */
  0U,                                  /* '<S864>/Data Type Conversion10' */
  0U,                                  /* '<S864>/Data Type Conversion11' */
  0U,                                  /* '<S864>/Data Type Conversion12' */
  0U,                                  /* '<S864>/Data Type Conversion13' */
  0U,                                  /* '<S864>/Data Type Conversion7' */
  0U,                                  /* '<S864>/Data Type Conversion8' */
  0U,                                  /* '<S864>/Data Type Conversion9' */
  8U,                                  /* '<S865>/TJA_SP_TYPE_POHPP' */
  15U,                                 /* '<S856>/Saturation' */
  128U,                                /* '<S1016>/Gain48' */
  128U,                                /* '<S1016>/Gain49' */
  128U,                                /* '<S1016>/Gain11' */
  0U,                                  /* '<S1016>/Gain16' */
  1,                                   /* '<S52>/NOT' */
  0,                                   /* '<S180>/Compare' */
  0,                                   /* '<S219>/Compare' */
  0,                                   /* '<S4>/Signal Conversion3' */
  0,                                   /* '<S4>/Signal Conversion6' */
  1,                                   /* '<S268>/Logical Operator3' */
  1,                                   /* '<S268>/Logical Operator4' */
  1,                                   /* '<S1030>/Compare' */
  0,                                   /* '<S1045>/Compare' */
  0,                                   /* '<S1075>/Compare' */
  1,                                   /* '<S1088>/Compare' */
  0,                                   /* '<S439>/Relational Operator' */
  0,                                   /* '<S439>/Relational Operator1' */
  0,                                   /* '<S440>/Relational Operator' */
  0,                                   /* '<S440>/Relational Operator1' */
  1,                                   /* '<S458>/Logical Operator1' */
  0,                                   /* '<S555>/Relational Operator' */
  0,                                   /* '<S555>/Relational Operator1' */
  1,                                   /* '<S555>/Relational Operator3' */
  0,                                   /* '<S555>/Logical Operator' */
  0,                                   /* '<S555>/Relational Operator2' */
  0,                                   /* '<S555>/Logical Operator1' */
  0,                                   /* '<S527>/Switch23' */
  0,                                   /* '<S527>/Switch23' */
  0,                                   /* '<S562>/Relational Operator' */
  0,                                   /* '<S562>/Relational Operator1' */
  1,                                   /* '<S562>/Relational Operator3' */
  0,                                   /* '<S562>/Logical Operator' */
  0,                                   /* '<S562>/Relational Operator2' */
  0,                                   /* '<S562>/Logical Operator1' */
  0,                                   /* '<S528>/Switch23' */
  0,                                   /* '<S528>/Switch23' */
  0,                                   /* '<S675>/Logical Operator11' */
  0,                                   /* '<S775>/Relational Operator' */
  0,                                   /* '<S775>/Relational Operator1' */
  0,                                   /* '<S775>/Logical Operator' */
  0,                                   /* '<S775>/Relational Operator22' */
  0,                                   /* '<S775>/Relational Operator23' */
  0,                                   /* '<S775>/Logical Operator1' */
  0,                                   /* '<S775>/Relational Operator5' */
  0,                                   /* '<S775>/Relational Operator6' */
  0,                                   /* '<S775>/Logical Operator2' */
  0,                                   /* '<S775>/Relational Operator7' */
  0,                                   /* '<S775>/Relational Operator8' */
  0,                                   /* '<S775>/Logical Operator3' */
  0,                                   /* '<S775>/Relational Operator10' */
  0,                                   /* '<S775>/Relational Operator11' */
  0,                                   /* '<S775>/Logical Operator4' */
  0,                                   /* '<S775>/Relational Operator2' */
  0,                                   /* '<S775>/Relational Operator3' */
  0,                                   /* '<S775>/Logical Operator5' */
  0,                                   /* '<S775>/Relational Operator15' */
  0,                                   /* '<S775>/Relational Operator16' */
  0,                                   /* '<S775>/Logical Operator6' */
  0,                                   /* '<S775>/Relational Operator17' */
  0,                                   /* '<S775>/Relational Operator18' */
  0,                                   /* '<S775>/Logical Operator7' */
  0,                                   /* '<S775>/Relational Operator20' */
  0,                                   /* '<S775>/Relational Operator21' */
  0,                                   /* '<S775>/Logical Operator8' */
  0,                                   /* '<S775>/Relational Operator25' */
  0,                                   /* '<S775>/Relational Operator26' */
  0,                                   /* '<S775>/Logical Operator9' */
  0,                                   /* '<S775>/Relational Operator14' */
  0,                                   /* '<S775>/Relational Operator19' */
  0,                                   /* '<S775>/Relational Operator24' */
  0,                                   /* '<S775>/Relational Operator4' */
  0,                                   /* '<S775>/Relational Operator9' */
  0,                                   /* '<S763>/Relational Operator1' */
  0,                                   /* '<S763>/Relational Operator2' */
  0,                                   /* '<S763>/Relational Operator3' */
  0,                                   /* '<S763>/Relational Operator4' */
  0,                                   /* '<S786>/Relational Operator15' */
  0,                                   /* '<S786>/Relational Operator16' */
  0,                                   /* '<S786>/Relational Operator17' */
  0,                                   /* '<S786>/Relational Operator18' */
  0,                                   /* '<S786>/Logical Operator6' */
  0,                                   /* '<S786>/Relational Operator19' */
  0,                                   /* '<S766>/Relational Operator10' */
  0,                                   /* '<S766>/Relational Operator11' */
  0,                                   /* '<S766>/Relational Operator15' */
  0,                                   /* '<S766>/Relational Operator5' */
  0,                                   /* '<S766>/Relational Operator7' */
  0,                                   /* '<S766>/Relational Operator8' */
  0,                                   /* '<S678>/Relational Operator9' */
  0,                                   /* '<S678>/Relational Operator14' */
  0,                                   /* '<S678>/Logical Operator4' */
  0,                                   /* '<S678>/Relational Operator19' */
  0,                                   /* '<S825>/Relational Operator10' */
  0,                                   /* '<S825>/Relational Operator11' */
  0,                                   /* '<S825>/Logical Operator10' */
  1,                                   /* '<S715>/Logical Operator2' */
  0,                                   /* '<S677>/Relational Operator8' */
  0,                                   /* '<S677>/Relational Operator12' */
  0,                                   /* '<S677>/Logical Operator11' */
  1,                                   /* '<S716>/Logical Operator2' */
  1,                                   /* '<S717>/Logical Operator2' */
  1,                                   /* '<S718>/Logical Operator2' */
  1,                                   /* '<S719>/Logical Operator2' */
  1,                                   /* '<S720>/Logical Operator2' */
  0,                                   /* '<S677>/Relational Operator14' */
  0,                                   /* '<S677>/Relational Operator21' */
  0,                                   /* '<S677>/Logical Operator4' */
  1,                                   /* '<S677>/Logical Operator2' */
  1,                                   /* '<S677>/Logical Operator22' */
  1,                                   /* '<S677>/Logical Operator25' */
  1,                                   /* '<S677>/Logical Operator9' */
  0,                                   /* '<S677>/Relational Operator1' */
  0,                                   /* '<S677>/Relational Operator11' */
  0,                                   /* '<S677>/Relational Operator13' */
  0,                                   /* '<S677>/Relational Operator15' */
  0,                                   /* '<S677>/Relational Operator16' */
  0,                                   /* '<S677>/Relational Operator30' */
  0,                                   /* '<S677>/Relational Operator31' */
  0,                                   /* '<S677>/Relational Operator6' */
  0,                                   /* '<S677>/Relational Operator7' */

  /* Start of '<S1135>/SfD1' */
  {
    0.02F,                             /* '<S1148>/Abs' */
    1.0F,                              /* '<S1148>/Sign' */
    1.0F,                              /* '<S1148>/Switch1' */
    1                                  /* '<S1149>/Compare' */
  }
  ,

  /* End of '<S1135>/SfD1' */

  /* Start of '<S1134>/SfD1' */
  {
    0.02F,                             /* '<S1145>/Abs' */
    1.0F,                              /* '<S1145>/Sign' */
    1.0F,                              /* '<S1145>/Switch1' */
    1                                  /* '<S1146>/Compare' */
  }
  ,

  /* End of '<S1134>/SfD1' */

  /* Start of '<S1025>/SfD1' */
  {
    0.02F,                             /* '<S1140>/Abs' */
    1.0F,                              /* '<S1140>/Sign' */
    1.0F,                              /* '<S1140>/Switch1' */
    1                                  /* '<S1141>/Compare' */
  }
  ,

  /* End of '<S1025>/SfD1' */

  /* Start of '<S1024>/SfD1' */
  {
    0.02F,                             /* '<S1137>/Abs' */
    1.0F,                              /* '<S1137>/Sign' */
    1.0F,                              /* '<S1137>/Switch1' */
    1                                  /* '<S1138>/Compare' */
  }
  ,

  /* End of '<S1024>/SfD1' */

  /* Start of '<S971>/SfD1' */
  {
    0.02F,                             /* '<S983>/Abs' */
    1.0F,                              /* '<S983>/Sign' */
    1.0F,                              /* '<S983>/Switch1' */
    1                                  /* '<S984>/Compare' */
  }
  ,

  /* End of '<S971>/SfD1' */

  /* Start of '<S678>/Rate_Limiter4' */
  {
    -0.0005F,                          /* '<S770>/Gain2' */
    -0.0100000007F,                    /* '<S770>/Gain' */
    0.0100000007F,                     /* '<S770>/Gain1' */
    -1.00000007E-5F,                   /* '<S770>/Product' */
    1.00000007E-5F                     /* '<S770>/Product2' */
  }
  ,

  /* End of '<S678>/Rate_Limiter4' */

  /* Start of '<S678>/Rate_Limiter3' */
  {
    -0.004F,                           /* '<S769>/Gain2' */
    -0.0800000057F,                    /* '<S769>/Gain' */
    0.0800000057F,                     /* '<S769>/Gain1' */
    -8.00000053E-5F,                   /* '<S769>/Product' */
    8.00000053E-5F                     /* '<S769>/Product2' */
  }
  ,

  /* End of '<S678>/Rate_Limiter3' */

  /* Start of '<S678>/Rate_Limiter2' */
  {
    -0.05F,                            /* '<S768>/Gain2' */
    -1.0F,                             /* '<S768>/Gain' */
    1.0F,                              /* '<S768>/Gain1' */
    -0.001F,                           /* '<S768>/Product' */
    0.001F                             /* '<S768>/Product2' */
  }
  ,

  /* End of '<S678>/Rate_Limiter2' */

  /* Start of '<S678>/Rate_Limiter' */
  {
    -2.0F,                             /* '<S767>/Gain2' */
    -40.0F,                            /* '<S767>/Gain' */
    40.0F,                             /* '<S767>/Gain1' */
    -0.04F,                            /* '<S767>/Product' */
    0.04F                              /* '<S767>/Product2' */
  }
  ,

  /* End of '<S678>/Rate_Limiter' */

  /* Start of '<S766>/Rate_Limiter6' */
  {
    -0.2F,                             /* '<S796>/Gain2' */
    -4.0F,                             /* '<S796>/Gain' */
    4.0F,                              /* '<S796>/Gain1' */
    -0.004F,                           /* '<S796>/Product' */
    0.004F                             /* '<S796>/Product2' */
  }
  ,

  /* End of '<S766>/Rate_Limiter6' */

  /* Start of '<S766>/Rate_Limiter5' */
  {
    -0.2F,                             /* '<S795>/Gain2' */
    -4.0F,                             /* '<S795>/Gain' */
    4.0F,                              /* '<S795>/Gain1' */
    -0.004F,                           /* '<S795>/Product' */
    0.004F                             /* '<S795>/Product2' */
  }
  ,

  /* End of '<S766>/Rate_Limiter5' */

  /* Start of '<S766>/First_Order_Lag_Filter_LIB7' */
  {
    40.0F,                             /* '<S812>/Sum' */
    0.5F                               /* '<S812>/Product' */
  }
  ,

  /* End of '<S766>/First_Order_Lag_Filter_LIB7' */

  /* Start of '<S766>/First_Order_Lag_Filter_LIB6' */
  {
    40.0F,                             /* '<S811>/Sum' */
    0.5F                               /* '<S811>/Product' */
  }
  ,

  /* End of '<S766>/First_Order_Lag_Filter_LIB6' */

  /* Start of '<S766>/First_Order_Lag_Filter_LIB14' */
  {
    80.0F,                             /* '<S809>/Sum' */
    0.25F                              /* '<S809>/Product' */
  }
  ,

  /* End of '<S766>/First_Order_Lag_Filter_LIB14' */

  /* Start of '<S766>/First_Order_Lag_Filter_LIB13' */
  {
    80.0F,                             /* '<S808>/Sum' */
    0.25F                              /* '<S808>/Product' */
  }
  ,

  /* End of '<S766>/First_Order_Lag_Filter_LIB13' */

  /* Start of '<S788>/Rate_Limiter1' */
  {
    -0.3F,                             /* '<S806>/Gain2' */
    -6.0F,                             /* '<S806>/Gain' */
    6.0F,                              /* '<S806>/Gain1' */
    -0.006F,                           /* '<S806>/Product' */
    0.006F                             /* '<S806>/Product2' */
  }
  ,

  /* End of '<S788>/Rate_Limiter1' */

  /* Start of '<S788>/First_Order_Lag_Filter_LIB1' */
  {
    2020.0F,                           /* '<S807>/Sum' */
    0.00990099F                        /* '<S807>/Product' */
  }
  ,

  /* End of '<S788>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S678>/First_Order_Lag_Filter_LIB4' */
  {
    80.0F,                             /* '<S774>/Sum' */
    0.25F                              /* '<S774>/Product' */
  }
  ,

  /* End of '<S678>/First_Order_Lag_Filter_LIB4' */

  /* Start of '<S678>/First_Order_Lag_Filter_LIB3' */
  {
    80.0F,                             /* '<S773>/Sum' */
    0.25F                              /* '<S773>/Product' */
  }
  ,

  /* End of '<S678>/First_Order_Lag_Filter_LIB3' */

  /* Start of '<S678>/First_Order_Lag_Filter_LIB2' */
  {
    80.0F,                             /* '<S772>/Sum' */
    0.25F                              /* '<S772>/Product' */
  }
  ,

  /* End of '<S678>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S678>/First_Order_Lag_Filter_LIB' */
  {
    80.0F,                             /* '<S771>/Sum' */
    0.25F                              /* '<S771>/Product' */
  }
  ,

  /* End of '<S678>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S677>/Rate_Limiter6' */
  {
    -0.035F,                           /* '<S736>/Gain2' */
    -0.7F,                             /* '<S736>/Gain' */
    0.7F,                              /* '<S736>/Gain1' */
    -0.0007F,                          /* '<S736>/Product' */
    0.0007F                            /* '<S736>/Product2' */
  }
  ,

  /* End of '<S677>/Rate_Limiter6' */

  /* Start of '<S677>/Rate_Limiter4' */
  {
    -0.035F,                           /* '<S735>/Gain2' */
    -0.7F,                             /* '<S735>/Gain' */
    0.7F,                              /* '<S735>/Gain1' */
    -0.0007F,                          /* '<S735>/Product' */
    0.0007F                            /* '<S735>/Product2' */
  }
  ,

  /* End of '<S677>/Rate_Limiter4' */

  /* Start of '<S677>/Rate_Limiter1' */
  {
    -0.3F,                             /* '<S732>/Gain2' */
    -6.0F,                             /* '<S732>/Gain' */
    6.0F,                              /* '<S732>/Gain1' */
    -0.006F,                           /* '<S732>/Product' */
    0.006F                             /* '<S732>/Product2' */
  }
  ,

  /* End of '<S677>/Rate_Limiter1' */

  /* Start of '<S677>/Rate_Limiter' */
  {
    -0.5F,                             /* '<S731>/Gain2' */
    -10.0F,                            /* '<S731>/Gain' */
    10.0F,                             /* '<S731>/Gain1' */
    -0.01F,                            /* '<S731>/Product' */
    0.01F                              /* '<S731>/Product2' */
  }
  ,

  /* End of '<S677>/Rate_Limiter' */

  /* Start of '<S677>/First_Order_Lag_Filter_LIB6' */
  {
    120.0F,                            /* '<S752>/Sum' */
    0.166666672F                       /* '<S752>/Product' */
  }
  ,

  /* End of '<S677>/First_Order_Lag_Filter_LIB6' */

  /* Start of '<S677>/First_Order_Lag_Filter_LIB3' */
  {
    80.0F,                             /* '<S749>/Sum' */
    0.25F                              /* '<S749>/Product' */
  }
  ,

  /* End of '<S677>/First_Order_Lag_Filter_LIB3' */

  /* Start of '<S677>/First_Order_Lag_Filter_LIB2' */
  {
    120.0F,                            /* '<S748>/Sum' */
    0.166666672F                       /* '<S748>/Product' */
  }
  ,

  /* End of '<S677>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S677>/First_Order_Lag_Filter_LIB1' */
  {
    2020.0F,                           /* '<S747>/Sum' */
    0.00990099F                        /* '<S747>/Product' */
  }
  ,

  /* End of '<S677>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S655>/Delay_set_EP' */
  {
    150.0F                             /* '<S665>/Data Type Conversion1' */
  }
  ,

  /* End of '<S655>/Delay_set_EP' */

  /* Start of '<S642>/Delay_set_EP' */
  {
    150.0F                             /* '<S645>/Data Type Conversion1' */
  }
  ,

  /* End of '<S642>/Delay_set_EP' */

  /* Start of '<S618>/First_Order_Lag_Filter_LIB2' */
  {
    820.0F,                            /* '<S631>/Sum' */
    0.024390243F                       /* '<S631>/Product' */
  }
  ,

  /* End of '<S618>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S618>/Delay_set_EP' */
  {
    500.0F                             /* '<S623>/Data Type Conversion1' */
  }
  ,

  /* End of '<S618>/Delay_set_EP' */

  /* Start of '<S593>/First_Order_Lag_Filter_w_IC1' */
  {
    20.0F,                             /* '<S617>/Sum' */
    1.0F                               /* '<S617>/Product' */
  }
  ,

  /* End of '<S593>/First_Order_Lag_Filter_w_IC1' */

  /* Start of '<S593>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S616>/Sum' */
    1.0F                               /* '<S616>/Product' */
  }
  ,

  /* End of '<S593>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S589>/First_Order_Lag_Filter_LIB1' */
  {
    20.0F,                             /* '<S604>/Sum' */
    1.0F                               /* '<S604>/Product' */
  }
  ,

  /* End of '<S589>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S589>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S603>/Sum' */
    1.0F                               /* '<S603>/Product' */
  }
  ,

  /* End of '<S589>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S530>/First_Order_Lag_Filter_w_IC1' */
  {
    20.0F,                             /* '<S588>/Sum' */
    1.0F                               /* '<S588>/Product' */
  }
  ,

  /* End of '<S530>/First_Order_Lag_Filter_w_IC1' */

  /* Start of '<S530>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S587>/Sum' */
    1.0F                               /* '<S587>/Product' */
  }
  ,

  /* End of '<S530>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S529>/First_Order_Lag_Filter_LIB1' */
  {
    20.0F,                             /* '<S577>/Sum' */
    1.0F                               /* '<S577>/Product' */
  }
  ,

  /* End of '<S529>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S529>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S576>/Sum' */
    1.0F                               /* '<S576>/Product' */
  }
  ,

  /* End of '<S529>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S528>/First_Order_Lag_Filter_LIB1' */
  {
    20.0F,                             /* '<S565>/Sum' */
    1.0F                               /* '<S565>/Product' */
  }
  ,

  /* End of '<S528>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S528>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S564>/Sum' */
    1.0F                               /* '<S564>/Product' */
  }
  ,

  /* End of '<S528>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S527>/First_Order_Lag_Filter_LIB1' */
  {
    20.0F,                             /* '<S558>/Sum' */
    1.0F                               /* '<S558>/Product' */
  }
  ,

  /* End of '<S527>/First_Order_Lag_Filter_LIB1' */

  /* Start of '<S527>/First_Order_Lag_Filter_LIB' */
  {
    20.0F,                             /* '<S557>/Sum' */
    1.0F                               /* '<S557>/Product' */
  }
  ,

  /* End of '<S527>/First_Order_Lag_Filter_LIB' */

  /* Start of '<S533>/First_Order_Lag_Filter_w_IC_LIB' */
  {
    120.0F,                            /* '<S540>/Sum' */
    0.166666672F                       /* '<S540>/Product' */
  }
  ,

  /* End of '<S533>/First_Order_Lag_Filter_w_IC_LIB' */

  /* Start of '<S458>/First_Order_Lag_Filter_LIB2' */
  {
    820.0F,                            /* '<S517>/Sum' */
    0.024390243F                       /* '<S517>/Product' */
  }
  ,

  /* End of '<S458>/First_Order_Lag_Filter_LIB2' */

  /* Start of '<S478>/First_Order_Lag_Filter_w_IC_LIB' */
  {
    120.0F,                            /* '<S496>/Sum' */
    0.166666672F                       /* '<S496>/Product' */
  }
  ,

  /* End of '<S478>/First_Order_Lag_Filter_w_IC_LIB' */

  /* Start of '<S323>/Rate_Limiter1' */
  {
    -3.0F,                             /* '<S391>/Gain2' */
    -60.0F,                            /* '<S391>/Gain' */
    60.0F,                             /* '<S391>/Gain1' */
    -0.06F,                            /* '<S391>/Product' */
    0.06F                              /* '<S391>/Product2' */
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
