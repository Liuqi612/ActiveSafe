#pragma once
#include <stdint.h>
namespace active_safety {

//这个结构体主要是接收外围输入，然后给算法做适配
typedef struct {
    float   master_imu_yawrate;           // WI_MstrIMUYawRate:deg/s;
    float   master_imu_longaccel;         // WI_MstrIMULongAcc:m/s2;
    float   master_imu_lataccel;          // WI_MstrIMULatAcc:m/s2,左正右负;
    float   brk_pdl_drvr_apld_prs;        // WI_BrkPdlDrvrApldPrs;
    float   steer_wheel_angle;            // WI_StrWhlAng:deg,左正右负;
    float   steer_wheel_angle_rate;       // WI_StrWhlAngSpd:deg/s,左正右负;
    float   left_driven_wheel_speed;      // WI_LDWheelSpd:km/h;
    float   left_notdriven_wheel_speed;   // WI_LNDWheelSpd:km/h;
    float   right_driven_wheel_speed;     // WI_RDWheelSpd:km/h;
    float   right_notdriven_wheel_speed;  // WI_RNDWheelSpd:km/h;
    float   veh_speed_driven_avg;         // WI_VehSpdDrvnAvg:km/h:
    float   veh_speed_not_driven_avg;     // WI_VehSpdNDrvnAvg:km/h
    float   front_left_wheel_speed_mps;   // WI_FLWheelSpd_mps:m/s;
    float   front_right_wheel_speed_mps;  // WI_FRWheelSpd_mps:m/s;
    float   rear_left_wheel_speed_mps;    // WI_RLWheelSpd_mps:m/s;
    float   rear_right_wheel_speed_mps;   // WI_RRWheelSpd_mps:m/s;
    float   esp_hosd_spd;                 // speed from esp,not mapping:m/s;
    float   display_speed;                // WI_VehicleSpeedDisplay:km/h:
    float   accel_ped_pos;                // WI_AccelPedPos:%,[0,100]
    float   brk_pedal_pos;                // WI_BrkPedalPos:%,[0,100]
    float   torsion_bar_trq;              // WI_TorsionBarTrq
    uint8_t long_ctrl_active;             // WI_LgCtrlBrakeAct:0:Not Active,1:Active
    uint8_t auto_brake_active;            // WI_AutoBrakeAct:0:Not Active,1:Active
    uint8_t brk_pedal_prsd;               // WI_BrkPedalPrsd:0:Not Press,1:Press
    uint8_t tcs_mod;                      // WI_TCSMod:0: esp off,1:Normal,2:off road
    uint8_t epb_stat;                     // WI_EPBStat:0:Released,1:Applied,2:Fault
    uint8_t sys_pwr_mod;                  // WI_SysPwrMod: 0:Off,1:Accessory,2:ON/Run,3:Crank
    uint8_t vse_act;                      // WI_VSEAct: 0:Not Active,1:Active
    uint8_t veh_dyn_cntl_stat;            // WI_VehDynCntlStat
    uint8_t tcs_act;                      // WI_TCSAct: 0:Not Active,1:Active
    uint8_t tcs_sta;                      // WI_TCSStat: 0=Inactive; 1=Active; 2=Fault
    uint8_t lgctrl_trq_req_sts;           /*WI_LgCtrlTrqRqStat 
                                            0: No Request
                                            1: Request Honored
                                            3: Request Denied
                                            4: Request Suspended till driver input/wait until driver input*/
    uint8_t veh_crash;                    // WI_VehCrashTrig: 0=False; 1=True
    uint8_t hdc_stat;                     // WI_HDCStat: 2:Active,Ohter:Not Active
    uint8_t airbag_virt_dev_avl;          // WI_AirbagVirtDevAvl
    uint8_t tire_presr_fault;             // WI_TirePresrFault
    uint8_t lka_trq_ovl_dlvd_stat;        // WI_LKATrqOvlDlvdStat
    uint8_t brake_sys_avail_mask;         // WI_AutoBrkSysAvailMask:
                                          // Bit0: AebAvailable;
                                          // Bit1: AbpAvailable;
                                          // Bit2: AwbAvailable;
                                          // Bit3: AbaAvailable;
    uint8_t brake_sys_active_mask;        // WI_AutoBrkSysAtvMask:
                                          // Bit0: AebActive;
                                          // Bit1: AbpActive;
                                          // Bit2: AwbActive;
                                          // Bit3: AbaActive;
    uint8_t fcw_snvty_set;                // WI_FCWSnvtySet:
                                          // 1:Normal;
                                          // 2:Close;
                                          // 3:Far;
                                          // 0:Or Other:NotUsed
    uint8_t longsafe_cus_set;             // WI_LgSafeVehCusSet:
                                          // 0:UnKnown;
                                          // 1:Off;
                                          // 2:Alert;
                                          // 3:Alert and Brake;
                                          // 4:Alert And Brake And Steer;
    uint8_t fcaclnwarn_cus_set;           // WI_FCAClnWarnCustSet:
                                          // 0:UnKnown;
                                          // 1:Off;
                                          // 2:Alert;
                                          // 3:Alert and Brake;
                                          // 4:Alert And Brake And Steer;
    uint8_t lss_switch;                   // WI_LSSSw: 0:关闭，1:预警，2:预警+纠偏
    uint8_t lss_sensitivity;              // WI_LatSafeSnvtySet
                                          // 0x00:Normal
                                          // 0x01:High sensitivity
                                          // 0x02:Low sensitivity
                                          // 0x03:Reserved
    uint8_t elk_switch;                   // WI_ELKSw: 0:关闭，1：开启
    uint8_t ldw_switch;                   // Unused_uint8_8派生: LDW开关
    uint8_t lka_switch;                   // Unused_uint8_8派生: LKA开关
    uint8_t esa_switch;                   // WI_ESASw
    uint8_t aes_switch;                   // WI_AESSw
    uint8_t bsd_switch_req;               // WI_LCA_BSDSwitchReq: Undefined
    uint8_t rcta_switch_req;              // WI_RCTASwitchReq: Undefined
    uint8_t fcta_switch_req;              // WI_FCTASwitchReq: Undefined
    uint8_t rcw_switch_req;               // WI_RECWSwitchReq: Undefined
    uint8_t dow_switch_req;               // WI_DOWSwitchReq: Undefined
    uint8_t aeb_switch;                   // WI_AEBSw: 0:关闭，1：开启
    uint8_t fcw_switch;                   // WI_FCWSw: 0:关闭，1：开启
    uint8_t hazard_light_stat;            // WI_HazLightStat: 0:Not Pressed,1:Pressed
    uint8_t hl_beam_sw_stat;              // WI_HLBeamSwStat: 0:Off,1:On
    uint8_t frnt_fog_lmp_stat;            // WI_FrntFogLmpStat: 0:Off, 1:On
    uint8_t rear_fog_lmp_stat;            // WI_RearFogLmpStat: 0:Off, 1:On
    uint8_t lturn_lmp_fault_st;           // WI_LTurnLmpFaultStat: 0:NotFault, 1:Fault
    uint8_t rturn_lmp_fault_st;           // WI_RTurnLmpFaultStat: 0:NotFault, 1:Fault
    uint8_t drvr_door_open;               // WI_DrvrDoorOpen:0:Not Open,1:Open
    uint8_t psngr_door_ajar_st;           // WI_PsngrDoorAjarSt:0:Not Open,1:Open
    uint8_t drvr_sb_fasten;               // WI_DrvrSBFasten:0:Not fasten,1:fasten
    uint8_t rl_door_ajar_st;              // WI_RLDoorAjarSt:0:Not Open,1:Open
    uint8_t rr_door_ajar_st;              // WI_RRDoorAjarSt:0:Not Open,1:Open
    uint8_t trunk_ajar_st;                // WI_TruckAjarSt:
                                          // 包含HoodDoor和TrunkDoor:
                                          // 0:Not Open,1:Open
    uint8_t wind_shield_wiper_active;     // WI_WindShieldWprAct: 0:NotActive,1:Active
    uint8_t turn_lamp_switchpos;          // WI_TurnLmpSwPos:
                                          // 0x0 == Neutral;
                                          // 0x1 == Left;
                                          // 0x2 == illegal combination;
                                          // 0x3 = right;
    uint8_t abs_active;                   // WI_ABSActive:0:NotActive,1:Active
    uint8_t trans_estd_gear;              // WI_TransEstdGear:
                                          // 0:Not Supported;
                                          // 12:CVT Forward Gear;
                                          // 13:Natual Gear;
                                          // 14:Reverse Gear;
                                          // 15:Park Gear;
    uint8_t left_driven_wheel_rotdir;     // WI_LDWheelRotDir:左侧驱动轮方向
                                          // 4: Forward
                                          // 2: Reverse
    uint8_t right_driven_wheel_rotdir;    // WI_RDWheelRotDir:右侧驱动轮方向
                                          // 4: Forward
                                          // 2: Reverse
    uint8_t right_notdriven_wheel_rotdir; // WI_RNDWheelRotDir:右侧非驱动轮方向
                                          // 4: Forward
                                          // 2: Reverse
    uint8_t left_notdriven_wheel_rotdir;  // WI_LNDWheelRotDir:左侧驱动轮方向
                                          // 4: Forward
                                          // 2: Reverse
    uint32_t yawrate_timestamp_ms;        // WI_YawRate_timestamp_ms;
    uint32_t function_did_config;         // WI_FunctionDIDConfig

} VseInput;

} // namespace active_safety
