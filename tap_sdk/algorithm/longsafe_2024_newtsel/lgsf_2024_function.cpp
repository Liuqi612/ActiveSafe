#include "algorithm/longsafe_2024_newtsel/lgsf_2024_function.h"

#include <cstring>

namespace active_safety {
namespace longsafe_2024_newtsel {

LgSafe2024Function::LgSafe2024Function() {
    // 静态分配模型所需的内存结构
    static B_LongSafe_SWC_T b;
    static DW_LongSafe_SWC_T dw;
    static RT_MODEL_LongSafe_SWC_T m;

    rtm_ = &m;
    rtm_->blockIO = &b;
    rtm_->dwork = &dw;

    // 初始化输入输出缓冲区
    std::memset(&simulink_u_vse_, 0, sizeof(simulink_u_vse_));
    std::memset(&simulink_u_core_out_, 0, sizeof(simulink_u_core_out_));
    std::memset(&simulink_u_param_config_, 0, sizeof(simulink_u_param_config_));
    std::memset(&simulink_y_lg_safe_, 0, sizeof(simulink_y_lg_safe_));
    std::memset(&simulink_y_cmd_lg_safe_, 0, sizeof(simulink_y_cmd_lg_safe_));
    std::memset(&simulink_y_display_lg_safe_, 0, sizeof(simulink_y_display_lg_safe_));
    Init();
}

LgSafe2024Function::~LgSafe2024Function() {
    LongSafe_SWC_terminate(rtm_);
}

void LgSafe2024Function::Init() {
    // 调用 Simulink 生成的初始化函数
    LongSafe_SWC_initialize(rtm_, (::AsVseOut *)&simulink_u_vse_, (::AsCoreOut_T *)&simulink_u_core_out_,
                            (::AsParamConfig_T *)&simulink_u_param_config_, (::LgSafe_T *)&simulink_y_lg_safe_,
                            (::AsCmdLgSafe_T *)&simulink_y_cmd_lg_safe_, (::AsDisplayLgSafe_T *)&simulink_y_display_lg_safe_);
}

void LgSafe2024Function::UpdateNewTsel(const active_safety::AsVseOut &vse_in, const active_safety::longsafe::LongSafeObject lgsf_obj,
                                       const senseAD::tap::AsParamConfig_T &long_safe_param) {
    senseAD::tap::AsVseOut vse_out;

    MapVseInput(vse_in, vse_out);
    MapNewTselRes2SelectOut(select_output_.longsafe_aeb, lgsf_obj);
    MapNewTselRes2SelectOut(select_output_.longsafe_fcw, lgsf_obj);
    MapToSimulinkInput(vse_out, select_output_, long_safe_param);

    LongSafe_SWC_step(rtm_, (::AsVseOut *)&simulink_u_vse_, (::AsCoreOut_T *)&simulink_u_core_out_, (::AsParamConfig_T *)&simulink_u_param_config_,
                      (::LgSafe_T *)&simulink_y_lg_safe_, (::AsCmdLgSafe_T *)&simulink_y_cmd_lg_safe_,
                      (::AsDisplayLgSafe_T *)&simulink_y_display_lg_safe_);
    OverrideLgsfTargetFromCoreOut();
    MapFromSimulinkOutput(simulink_y_lg_safe_, simulink_y_cmd_lg_safe_, simulink_y_display_lg_safe_);
}
void LgSafe2024Function::OverrideLgsfTargetFromCoreOut() {
    // 用 CoreOut 输入的 longsafe_aeb 主目标属性，直接替换 step 输出的 lgsf_target 主目标属性。
    // 字段映射沿用 Simulink 内部对 lgsf_target 的填充约定：
    // posx/spdx/accelx 取纵向量，posy/spdy/accely 取横向量。
    const senseAD::tap::AsLongSafeObject &aeb = select_output_.longsafe_aeb;
    senseAD::tap::AsTargetInfo_T &tgt = simulink_y_cmd_lg_safe_.lgsf_target;

    tgt.id = static_cast<uint32_T>(aeb.fus_trkId);
    tgt.type = static_cast<uint32_T>(aeb.object_class);
    tgt.source = static_cast<uint32_T>(aeb.detection_sensor);
    tgt.posx = aeb.long_posn;
    tgt.posy = aeb.lat_posn;
    tgt.spdx = aeb.long_vel;
    tgt.spdy = aeb.lat_vel;
    tgt.accelx = aeb.long_accel;
    tgt.accely = aeb.lat_accel;
    tgt.heading = aeb.heading;
    tgt.ttc = aeb.ttc;
    tgt.width = aeb.width;
    tgt.length = aeb.length;
}
void LgSafe2024Function::MapNewTselRes2SelectOut(senseAD::tap::AsLongSafeObject &res, active_safety::longsafe::LongSafeObject lgsf_obj) {
    res.fus_trkId = lgsf_obj.fus_trkID;
    res.age = lgsf_obj.age;
    res.stationary = lgsf_obj.stationary;
    res.object_class = static_cast<int32_t>(lgsf_obj.type);
    res.long_posn = lgsf_obj.long_posn - 3.7F;
    res.long_vel = lgsf_obj.long_vel;
    res.long_accel = lgsf_obj.long_accel;
    res.lat_posn = lgsf_obj.lat_posn;
    res.lat_vel = lgsf_obj.lat_vel;
    res.lat_accel = lgsf_obj.lat_accel;
    res.heading = lgsf_obj.heading;
    res.length = lgsf_obj.length;
    res.width  = lgsf_obj.width;
    res.length_side_lgt = lgsf_obj.length;
    res.length_side_lat = lgsf_obj.width;
    res.inpath_current = lgsf_obj.inpath_current;
    res.inpath_predict = lgsf_obj.inpath_predict;
    res.speed = lgsf_obj.speed;
    res.ttc = lgsf_obj.ttr;
    // 中心点转换到目标后屁股中心且 纵向位置坐标原点移位到自车车头位置 与下游控制端保持统一
    if ((lgsf_obj.type == ObjectClass::PEDESTRIAN)  ||  (lgsf_obj.type == ObjectClass::CONE)  ||  (lgsf_obj.type == ObjectClass::GOD)) {

        res.lat_posn = lgsf_obj.lat_posn;
        res.long_posn = lgsf_obj.long_posn - 3.7F;
    } else {
        res.lat_posn = lgsf_obj.lat_posn - 0.5F * sinf(lgsf_obj.heading) * lgsf_obj.length;
        res.long_posn = lgsf_obj.long_posn - 0.5F * cosf(lgsf_obj.heading) * lgsf_obj.length - 3.7F;
    }

    // 关键信息需补充Pred_Algt Pred_Alat Pred_Alat 目前暂由实际值代替[TODO]
    res.pred_long_accel = lgsf_obj.long_accel;
    res.pred_lat_accel = lgsf_obj.lat_accel;
    res.pred_accel = lgsf_obj.accel;

    // is_vehicle  
    res.obs_is_vehicle = lgsf_obj.type == ObjectClass::CAR || lgsf_obj.type == ObjectClass::TRUCK || lgsf_obj.type == ObjectClass::BUS ||
        lgsf_obj.type == ObjectClass::UNIDENTIFIED_VEHICLE || lgsf_obj.type == ObjectClass::THREEWHEEl_VEHICLE;
}

void LgSafe2024Function::MapToSimulinkInput(const senseAD::tap::AsVseOut &vse_out, const senseAD::tap::AsLongSafeOut &select_out,
                                            const senseAD::tap::AsParamConfig_T &long_safe_param) {
    simulink_u_vse_ = vse_out;
    simulink_u_core_out_.longsafe = select_out;
    simulink_u_param_config_ = long_safe_param;
}

void LgSafe2024Function::MapFromSimulinkOutput(const senseAD::tap::LgSafe_T &lg_safe_internal, const senseAD::tap::AsCmdLgSafe_T &cmd_internal,
                                               const senseAD::tap::AsDisplayLgSafe_T &display_internal) {
    cmd_output_ = cmd_internal;
    display_output_ = display_internal;
    ltap_output_ = lg_safe_internal.LgSf_Ltap;
}

void LgSafe2024Function::MapVseInput(const active_safety::AsVseOut &vse_in, senseAD::tap::AsVseOut &vse_out) {
    vse_out.host_length = vse_in.config.k_host_length;
    vse_out.host_width = vse_in.config.k_host_width;
    vse_out.host_dist_to_front = vse_in.config.k_dist_to_rear_axle;
    vse_out.speed = vse_in.speed;
    vse_out.display_speed = vse_in.display_speed;
    vse_out.yawrate = vse_in.yawrate;
    vse_out.yawrate_unfiltered_rps = vse_in.yawrate_unfiltered_rps;
    vse_out.long_accel = vse_in.long_accel;
    vse_out.lat_accel = vse_in.lat_accel;
    vse_out.host_pitch_rad = vse_in.host_pitch_rad;
    vse_out.host_roll_rad = vse_in.host_roll_rad;
    vse_out.vcs_sideslip = vse_in.vcs_sideslip;
    vse_out.vcs_long_vel = vse_in.vcs_long_vel;
    vse_out.vcs_lat_vel = vse_in.vcs_lat_vel;
    vse_out.sensor_sideslip = vse_in.sensor_sideslip;
    vse_out.sensor_long_vel = vse_in.sensor_long_vel;
    vse_out.sensor_lat_vel = vse_in.sensor_lat_vel;
    vse_out.rear_curvature = vse_in.rear_curvature;
    vse_out.rear_curvaturerate = vse_in.rear_curvaturerate;
    vse_out.rear_curvature_radius = vse_in.rear_curvature_radius;
    vse_out.rear_sideslip = vse_in.rear_sideslip;
    vse_out.steerwheelangle = vse_in.steerwheelangle;
    vse_out.steerwheelangle_rate = vse_in.steerwheelangle_rate;
    vse_out.slope_long_rad = vse_in.slope_long_rad;
    vse_out.slope_lat_rad = vse_in.slope_lat_rad;
    vse_out.gas_pedal_pos = vse_in.gas_pedal_pos;
    vse_out.brake_pedal_pos = vse_in.brake_pedal_pos;
    vse_out.brake_pressure = vse_in.brake_pressure;
    vse_out.gas_pedal_pos_rate = vse_in.gas_pedal_pos_rate;
    vse_out.brake_pedal_pos_rate = vse_in.brake_pedal_pos_rate;
    vse_out.brake_pressure_rate = vse_in.brake_pressure_rate;
    vse_out.hazard_lamp_st = vse_in.hazard_lamp_st;
    vse_out.front_fog_lamp_st = vse_in.front_fog_lamp_st;
    vse_out.back_fog_lamp_st = vse_in.back_fog_lamp_st;
    vse_out.left_light_fault_st = vse_in.left_light_fault_st;
    vse_out.right_light_fault_st = vse_in.right_light_fault_st;
    vse_out.epb_applied = vse_in.epb_applied;
    vse_out.high_beam_st = vse_in.high_beam_st;
    vse_out.vdc_active_st = vse_in.vdc_active_st;
    vse_out.tcs_active_st = vse_in.tcs_active_st;
    vse_out.hdc_active_st = vse_in.hdc_active_st;
    vse_out.esc_off_st = vse_in.esc_off_st;
    vse_out.fl_door_st = vse_in.fl_door_st;
    vse_out.fr_door_st = vse_in.fr_door_st;
    vse_out.rl_door_st = vse_in.rl_door_st;
    vse_out.rr_door_st = vse_in.rr_door_st;
    vse_out.turn_light_switch_pos = vse_in.turn_light_switch_pos;
    vse_out.left_light_st = vse_in.left_light_st;
    vse_out.right_light_st = vse_in.right_light_st;
    vse_out.eng_hood_unlock_warn = vse_in.eng_hood_unlock_warn;
    vse_out.trunk_st = vse_in.trunk_st;
    vse_out.front_wiper_work_st = vse_in.front_wiper_work_st;
    vse_out.f_reverse_status = vse_in.f_reverse_status;
    vse_out.driver_belt_switch_st = vse_in.driver_belt_switch_st;
    vse_out.actual_gear = vse_in.actual_gear;
    vse_out.brake_pedal_type = vse_in.brake_pedal_type;
    vse_out.fcw_warn_dist = vse_in.fcw_warn_dist;
    vse_out.longsafe_switch = vse_in.longsafe_switch;
    vse_out.bsd_switch = vse_in.bsd_switch;
    vse_out.dow_switch = vse_in.dow_switch;
    vse_out.fctb_switch = vse_in.fctb_switch;
    vse_out.rctb_switch = vse_in.rctb_switch;
    vse_out.rcw_switch = vse_in.rcw_switch;
    vse_out.brake_pedal_apld = vse_in.brake_pedal_apld;
    vse_out.abs_active = vse_in.abs_active;
    vse_out.aeb_active = vse_in.aeb_active;
    vse_out.power_mode = vse_in.power_mode;
    vse_out.long_ctrl_brake_active = vse_in.long_ctrl_brake_active;
    vse_out.straight_driving = vse_in.straight_driving;
    vse_out.esp_brake_available_st = vse_in.esp_brake_available_st;
    vse_out.function_did_config = vse_in.function_did_config;
    vse_out.state_machine_sts = vse_in.state_machine_sts;
}

} // namespace longsafe_2024_newtsel
} // namespace active_safety
