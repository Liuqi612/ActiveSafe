#include "society_scene.h"

#include "math/lookuptable/lookuptable.h"
#include "society_scene_cal.h"

#include <array>
#include <cmath>
namespace senseAD {

namespace tap {

AsSocietyScene::AsSocietyScene() {
}

AsSocietyScene::~AsSocietyScene() {
}

AsSocietySceneParam society_param = AsSocietySceneParam{};

bool AsSocietyScene::IsTestScene() const {
    return ((society_scene & AsSocierySceneData::AS_TEST_SCENE) > 0);
}

uint32_t AsSocietyScene::GetSocietySceneResult() const {
    return society_scene;
}

int AsSocietyScene::GetStrictScpObj() const {
    // if (((society_scene & AsSocierySceneData::AS_STRICT_SCP_SCENE) ==
    //      AsSocierySceneData::AS_STRICT_SCP_SCENE) &&
    //     ((society_scene & AsSocierySceneData::AS_TEST_SCENE) ==
    //      AsSocierySceneData::AS_TEST_SCENE) &&
    //     ((ego_.host_state & AsHostState::AS_HOST_IN_CONST_STRAIGHT) ==
    //      AsHostState::AS_HOST_IN_CONST_STRAIGHT)) {
    //   return (int)scp_obj_id;
    // } else {
    //   return 0;
    // }
    return 0;
}

int AsSocietyScene::GetStrictCpncoObj() const {
    // if (((society_scene & AsSocierySceneData::AS_STRICT_CPNCO_SCENE) ==
    //      AsSocierySceneData::AS_STRICT_CPNCO_SCENE) &&
    //     ((society_scene & AsSocierySceneData::AS_TEST_SCENE) ==
    //      AsSocierySceneData::AS_TEST_SCENE) &&
    //     ((ego_.host_state & AsHostState::AS_HOST_IN_CONST_STRAIGHT) ==
    //      AsHostState::AS_HOST_IN_CONST_STRAIGHT)) {
    //   return (int)cpnco_obj_id;
    // } else {
    //   return 0;
    // }
    return 0;
}

int AsSocietyScene::GetCptalObj() const {
    return cpta_l_track_id;
}
int AsSocietyScene::GetCstaRnObj() const {
    return csta_rn_track_id;
}
bool AsSocietyScene::GetCptalObjRequire() const {
    return cpta_l_require;
}
bool AsSocietyScene::GetCstaRnObjRequire() const {
    return csta_rn_require;
}
bool AsSocietyScene::GetTurnConstandSpdFlag() const {
    return ego_at_turn_scene_;
};

int AsSocietyScene::GetCpfaoObj() const {
    return cpfao_track_id;
}
int AsSocietyScene::GetCbnaoObj() const {
    return cbnao_track_id;
}
int AsSocietyScene::GetCsfaoObj() const {
    return csfao_track_id;
}
int AsSocietyScene::GetScpoObj() const {
    return scpo_track_id;
}

bool AsSocietyScene::GetCpfaoObjRequire() const {
    return cpfao_require;
}
bool AsSocietyScene::GetCbnaoObjRequire() const {
    return cbnao_require;
}
bool AsSocietyScene::GetCsfaoObjRequire() const {
    return csfao_require;
}
bool AsSocietyScene::GetScpoObjRequire() const {
    return scpo_require;
}

bool AsSocietyScene::GetJustStartValid() const {
    return ego_during_stright_constant_spd_;
}
bool AsSocietyScene::GetConstantSpdValid() const {
    return within_validtime_after_ego_start_;
}
// bool k_at_test_scene)
void AsSocietyScene::ProcessSocietyScene(const active_safety::AsObstacleList &obj_list, const AsVseOut &vse_out, const AsParamConfig_T &longparam) {
    ego_                = vse_out;
    k_at_test_scene_    = longparam.k_LgSf_EnTestScene;
    k_cross_vlat_check_ = false;
    k_cross_vlgt_check_ = false;
    simulation_check_cnt += 1;
    simulation_check_cnt = std::min(society_param.k_simulation_max_steps, simulation_check_cnt);
    if (simulation_check_cnt < 3500) {
        simulation_check = true;
    }
    CalcTestScene(obj_list);
    CheckSceneBaseEgoInfo(obj_list);
    DisableEgoJustStartValid();

    DecideStrictScp(obj_list);
    DecideStrictCpnco(obj_list);
    // CalPoseLongThdForBrake();
    // if (society_scene & 1) {
    //   DecideCpta_L(obj_list);
    //   DecideCsta_Rn(obj_list);
    //   CrossingSceneCheck(obj_list);
    // } else {
    //   ResetCrossTapObj();
    // }
}

void AsSocietyScene::CalcTestScene(const active_safety::AsObstacleList &obj_list) {
    ProcessObstacles(obj_list);
    EgoAtComplexScenePrev(obj_list);

    // if ((society_evaluate_obj == false && ego_at_complx_scene == false &&
    //      (ego_.host_state & AsHostState::AS_HOST_CONST_VELOCITY) &&
    //      within_validtime_after_ego_start_ && ego_during_stright_constant_spd_
    //      &&
    //      ((ego_.host_state & AsHostState::AS_HOST_IN_CONST_STRAIGHT) ||
    //       (ego_.host_state & AsHostState::AS_HOST_IN_HARD_CURVE))) ||
    //     k_at_test_scene_) {
    //   // std::cout << "进入测试场景" << std::endl;
    //   society_scene |= AsSocierySceneData::AS_TEST_SCENE;
    // } else {
    //   society_scene &= ~AsSocierySceneData::AS_TEST_SCENE;
    // }
    // if ((society_evaluate_obj == false && ego_at_complx_scene == false &&
    //      (ego_.host_state & AsHostState::AS_HOST_CONST_VELOCITY) &&
    //      ((ego_.host_state & AsHostState::AS_HOST_IN_CONST_STRAIGHT) ||
    //       (ego_.host_state & AsHostState::AS_HOST_IN_HARD_CURVE))) ||
    //     k_at_test_scene_) {
    //   // std::cout << "进入测试场景" << std::endl;
    //   society_scene |= AsSocierySceneData::AS_TEST_SCENE;
    // } else {
    //   society_scene &= ~AsSocierySceneData::AS_TEST_SCENE;
    // }
}

void AsSocietyScene::DecideStrictCpnco(const active_safety::AsObstacleList &obj_list) {
    // uint32_t right_stat_veh_cnt = 0;
    // uint32_t left_veh_cnt = 0;
    // uint32_t child_cnt = 0;
    // uint8_t child_id = 0;
    // uint32_t right_vru_cnt = 0;

    // float stat_car_long_posn_thres = LookUpTable::LookupTable1D<5>(
    //     society_param.k_cpnco_scene_hostspd_brakepoints,
    //     society_param.k_cpnco_scene_statcar_longposthres, ego_.speed);
    // float child_long_posn_thres = LookUpTable::LookupTable1D<5>(
    //     society_param.k_cpnco_scene_hostspd_brakepoints,
    //     society_param.k_cpnco_scene_child_longposthres, ego_.speed);
    // if (ego_.aeb_active) {
    //   child_long_posn_thres = 30.f;
    // }
    // for (std::size_t i = 0; i < kMaxFusionObject; i++) {
    //   const active_safety::AsObstacle &obj = obj_list[i];
    //   if (obj.object_class == active_safety::ObjectClass::CAR &&
    //       obj.speed < society_param.k_sc_moving_veh &&
    //       obj.long_posn - ego_.host_dist_to_front < stat_car_long_posn_thres &&
    //       obj.lat_posn < 0.f && obj.lat_posn > -6.0f &&
    //       (std::abs(obj.heading) < 1.0f)) {
    //     right_stat_veh_cnt++;
    //   }
    //   if (obj.object_class != active_safety::ObjectClass::PEDESTRIAN &&
    //       cpnco_obj_id == obj.track_id && cpnco_obj_id > 0) {
    //     child_obj_label_jump_cnt++;
    //   } else {
    //     if (cpnco_obj_id == obj.track_id &&
    //         obj.object_class == active_safety::ObjectClass::PEDESTRIAN) {
    //       child_obj_label_jump_cnt = 0;
    //     } else {
    //     }
    //   }
    //   if (((obj.object_class == active_safety::ObjectClass::PEDESTRIAN &&
    //         obj.height < society_param.k_sc_max_child_height) ||
    //        (cpnco_obj_id > 0 && cpnco_obj_id == obj.track_id &&
    //         child_obj_label_jump_cnt < 6 &&
    //         obj.height < society_param.k_sc_max_child_height)) &&
    //       (obj.lat_posn > -3.0f && obj.lat_posn < 3.0f) && obj.long_posn > 0.f) {
    //     child_id = obj.track_id;
    //     child_cnt++;
    //   }
    //   if ((obj.object_class == active_safety::ObjectClass::PEDESTRIAN ||
    //        obj.object_class == active_safety::ObjectClass::ESCOOTER ||
    //        obj.object_class == active_safety::ObjectClass::BICYCLE ||
    //        obj.object_class == active_safety::ObjectClass::MOTORCYCLE) &&
    //       obj.lat_posn < 0.0f && obj.lat_posn > -6.0f) {
    //     right_vru_cnt++;
    //   }
    //   if (obj.object_class == active_safety::ObjectClass::CAR &&
    //       obj.long_posn - ego_.host_dist_to_front < stat_car_long_posn_thres &&
    //       obj.lat_posn > 0.f && obj.lat_posn < 8.0f) {
    //     left_veh_cnt++;
    //   }
    // }
    // // std::cout << " ChildId:" << static_cast<uint32_t>(child_id)
    // //           << " ChildCnt:" << static_cast<uint32_t>(child_cnt)
    // //           << " StatVehCnt:" << static_cast<uint32_t>(right_stat_veh_cnt)
    // //           << " PosThres:" << child_long_posn_thres << std::endl;
    // // AD_LERROR() << " ChildId:" << static_cast<uint32_t>(child_id)
    // //             << " ChildCnt:" << static_cast<uint32_t>(child_cnt)
    // //             << " StatVehCnt:" << static_cast<uint32_t>(right_stat_veh_cnt)
    // //             << " PosThres:" << child_long_posn_thres;
    // if (child_cnt > 1) {
    //   child_id = 0;
    // }
    // bool intv_tgt_check =
    //     (moving_tgt_cnt <= 3 && truck_cnt == 0 &&
    //      (bike_cnt == 0 || child_obj_label_jump_cnt > 0) &&
    //      (stat_twowhl_cnt == 0 || child_obj_label_jump_cnt > 0) &&
    //      left_veh_cnt < 1 && right_vru_cnt < 2) ||
    //     (k_at_test_scene_);
    // bool shadow_car_check = (right_stat_veh_cnt > 0 && right_stat_veh_cnt < 3);
    // if (child_id > 0) {
    //   float long_pos_thres = obj_list[child_id - 1].long_posn + 2.0f;
    //   for (std::size_t i = 0; i < kMaxFusionObject; i++) {
    //     if (obj_list[i].object_class == active_safety::ObjectClass::CAR &&
    //         obj_list[i].long_posn - ego_.host_dist_to_front <= 20.0f) {
    //       float low_long =
    //           obj_list[i].long_posn -
    //           0.5 * obj_list[i].width * std::sin(std::abs(obj_list[i].heading));
    //       float up_long =
    //           obj_list[i].long_posn +
    //           0.5 * obj_list[i].width * std::sin(std::abs(obj_list[i].heading)) +
    //           obj_list[i].length * std::cos(std::abs(obj_list[i].heading));
    //       bool lat_pos_check = std::abs(obj_list[i].lat_posn -
    //                                     obj_list[child_id - 1].lat_posn) < 2.0f;
    //       if ((up_long > long_pos_thres || low_long > long_pos_thres) &&
    //           lat_pos_check) {
    //         // AD_LERROR() << " Reset" << obj_list[i].fus_trkID;
    //         child_id = 0;
    //         break;
    //       }
    //     }
    //   }
    // }

    // if (intv_tgt_check && shadow_car_check &&
    //     (child_id > 0 &&
    //      obj_list[child_id - 1].long_posn - ego_.host_dist_to_front <
    //          child_long_posn_thres &&
    //      obj_list[child_id - 1].height < society_param.k_sc_max_child_height &&
    //      obj_list[child_id - 1].f_beyond_roadedge == false)) {
    //   society_scene |= AsSocierySceneData::AS_STRICT_CPNCO_SCENE;
    // } else {
    //   society_scene &= ~AsSocierySceneData::AS_STRICT_CPNCO_SCENE;
    //   child_id = 0;
    // }
    // cpnco_obj_id = child_id;

    // // std::cout << " C1:" << static_cast<uint32_t>(moving_tgt_cnt <= 3)
    // //           << " C2:" << static_cast<uint32_t>(truck_cnt == 0) << " C3:"
    // //           << static_cast<uint32_t>(bike_cnt == 0 ||
    // //                                    child_obj_label_jump_cnt > 0)
    // //           << " C4:"
    // //           << static_cast<uint32_t>(right_stat_veh_cnt > 0 &&
    // //                                    right_stat_veh_cnt < 3)
    // //           << " C5:" << static_cast<uint32_t>(left_veh_cnt < 1)
    // //           << " C6:" << static_cast<uint32_t>(right_vru_cnt < 2) << " C7:"
    // //           << static_cast<uint32_t>(stat_twowhl_cnt == 0 ||
    // //                                    child_obj_label_jump_cnt > 0)
    // //           << " C8:"
    // //           << static_cast<uint32_t>(
    // //                  child_id > 0 &&
    // //                  obj_list[child_id - 1].long_posn < child_long_posn_thres
    // //                  && obj_list[child_id - 1].height <
    // //                  society_param.k_sc_max_child_height)
    // //           << std::endl;
    // // std::cout << " ChildId:" << static_cast<uint32_t>(cpnco_obj_id)
    // //           << " ChildCnt:" << static_cast<uint32_t>(child_cnt) << std::endl;
    // // std::cout << " MovingCnt:" << static_cast<uint32_t>(moving_tgt_cnt)
    // //           << " TruckCnt:" << static_cast<uint32_t>(truck_cnt)
    // //           << " BikeCnt:" << static_cast<uint32_t>(bike_cnt)
    // //           << " RightStatVehCnt:" <<
    // //           static_cast<uint32_t>(right_stat_veh_cnt)
    // //           << " JumpCnt:" << static_cast<uint32_t>(child_obj_label_jump_cnt)
    // //           << std::endl;
    // // std::cout << " RightVruCnt:" << static_cast<uint32_t>(right_vru_cnt)
    // //           << " LeftVehCnt:" << static_cast<uint32_t>(left_veh_cnt)
    // //           << " StateTwoWhlCnt:" << static_cast<uint32_t>(stat_twowhl_cnt)
    // //           << std::endl;
}
void AsSocietyScene::DecideStrictScp(const active_safety::AsObstacleList &obj_list) {
    // bool allow_strict_scp = false;

    // float tgt_latspd_thres_low = LookUpTable::LookupTable1D<4>(
    //     society_param.k_scp_scene_hostspd_brakepoints,
    //     society_param.k_scp_scene_obj_latspd_brakepoints, ego_.speed);
    // float tgt_latspd_thres_high = LookUpTable::LookupTable1D<4>(
    //     society_param.k_scp_scene_hostspd_brakepoints,
    //     society_param.k_scp_scene_obj_highlatspd_brakepoints, ego_.speed);
    // float tgt_latspd_thres_high_select = LookUpTable::LookupTable1D<4>(
    //     society_param.k_scp_scene_hostspd_brakepoints,
    //     society_param.k_scp_scene_obj_highlatspd_select_brakepoints, ego_.speed);
    // float tgt_longpos_thres = LookUpTable::LookupTable1D<4>(
    //     society_param.k_scp_scene_hostspd_brakepoints,
    //     society_param.k_scp_scene_obj_longpos_brakepoints, ego_.speed);

    // bool host_spd_allow = (ego_.speed > 5.55 && ego_.speed < 17.f);
    // bool f_high_lat_vel_obj = false;
    // if (moving_tgt_cnt < 2) {
    //   for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
    //     if (obj_list[i].object_class == active_safety::ObjectClass::CAR &&
    //         obj_list[i].lat_vel > 9.f) {
    //       f_high_lat_vel_obj = true;
    //       break;
    //     }
    //   }
    // }
    // int right_stat_obj_cnt = 0;
    // if (f_high_lat_vel_obj) {
    //   for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
    //     if (obj_list[i].object_class == active_safety::ObjectClass::CAR &&
    //         obj_list[i].lat_posn > -5.f && obj_list[i].lat_posn < 0.f &&
    //         obj_list[i].long_posn < 5.f) {
    //       right_stat_obj_cnt++;
    //     }
    //   }
    // }
    // if (right_stat_obj_cnt > 0 && right_stat_obj_cnt <= 3) {
    //   if (ego_.speed <= 14.f) {
    //     tgt_latspd_thres_high = 19.0f;
    //     tgt_latspd_thres_low = 5.0f;
    //   } else if (ego_.speed <= 17.0f) {
    //     tgt_latspd_thres_low = 5.0f;
    //     tgt_latspd_thres_high = 20.0f;
    //   }
    // }

    // for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
    //   bool tgt_select = (scp_obj_id > 0 && scp_obj_id == obj_list[i].track_id);
    //   bool lat_vel_check =
    //       (((std::abs(obj_list[i].lat_vel) > tgt_latspd_thres_low) &&
    //         (tgt_latspd_thres_high > std::abs(obj_list[i].lat_vel) ||
    //          (tgt_select &&
    //           tgt_latspd_thres_high_select > std::abs(obj_list[i].lat_vel)))) ||
    //        (ego_.high_dynamic && tgt_select));
    //   bool longvel_check = ((std::abs(obj_list[i].long_vel) <
    //                          society_param.k_scp_scene_obj_longvel_thres) ||
    //                         (ego_.high_dynamic && tgt_select));
    //   bool long_pos_check =
    //       (obj_list[i].long_posn > 5 &&
    //        obj_list[i].long_posn - ego_.host_dist_to_front < tgt_longpos_thres) ||
    //       (ego_.high_dynamic && tgt_select);
    //   bool direction_check = false;
    //   if (obj_list[i].lat_vel < 0) {
    //     direction_check = (obj_list[i].heading < 0);
    //   } else {
    //     direction_check = (obj_list[i].heading >= 0);
    //   }
    //   bool lat_position_check = false;
    //   if (obj_list[i].lat_vel <= 0) {
    //     lat_position_check =
    //         ((obj_list[i].lat_posn >= 0 && obj_list[i].lat_posn < 30) ||
    //          (ego_.high_dynamic && tgt_select));
    //   } else {
    //     lat_position_check =
    //         ((obj_list[i].lat_posn < 0 && obj_list[i].lat_posn > -30) ||
    //          (ego_.high_dynamic && tgt_select));
    //   }
    //   bool angle_check = (std::abs(std::atan(math::SafeDivide(
    //                           obj_list[i].lat_posn, obj_list[i].long_posn))) *
    //                       57.3f) < 65;
    //   bool road_edge_check = (obj_list[i].f_beyond_roadedge == false);
    //   if (obj_list[i].object_class == active_safety::ObjectClass::CAR && lat_vel_check &&
    //       long_pos_check && longvel_check && direction_check &&
    //       lat_position_check && road_edge_check && angle_check) {
    //     // std::cout << "LatVel:" << obj_list[i].lat_vel
    //     //             << " LatVelThres:" << tgt_latspd_thres_low
    //     //             << " LongPosThres:" << tgt_longpos_thres<<std::endl;
    //     scp_obj_id = obj_list[i].track_id;
    //     allow_strict_scp = true;
    //     break;
    //   }
    // }
    // if (allow_strict_scp == false) {
    //   scp_obj_id = 0;
    // }
    // if (moving_tgt_cnt <= 2 && truck_cnt == 0 && bike_cnt == 0 &&
    //     stat_twowhl_cnt == 0 && allow_strict_scp && host_spd_allow) {
    //   society_scene |= AsSocierySceneData::AS_STRICT_SCP_SCENE;
    // } else {
    //   if (ego_.aeb_active || ego_.high_dynamic) {
    //   } else {
    //     society_scene &= ~AsSocierySceneData::AS_STRICT_SCP_SCENE;
    //   }
    // }
    // // std::cout << " MovingCnt:" << static_cast<uint32_t>(moving_tgt_cnt)
    // //             << " TruckCnt:" << static_cast<uint32_t>(truck_cnt)
    // //             << " BikeCnt:" << static_cast<uint32_t>(bike_cnt)
    // //             << " AllowScp:" << static_cast<uint32_t>(allow_strict_scp)
    // //             << " StateTwoWhlCnt:" <<
    // //             static_cast<uint32_t>(stat_twowhl_cnt)
    // //             << " LatSpdHigh:" << tgt_latspd_thres_high
    // //             << " LatSpdHighSel:" << tgt_latspd_thres_high_select
    // //             << " LatSpdLow:" << tgt_latspd_thres_low<<std::endl;
}

void AsSocietyScene::ProcessObstacles(const active_safety::AsObstacleList &obj_list) {
    // moving_tgt_cnt = 0;
    // mov_truck_cnt = 0;
    // invalid_truck_heading_cnt = 0;
    // truck_cnt = 0;
    // bike_cnt = 0;
    // ped_cnt = 0;
    // stat_twowhl_cnt = 0;
    // backforward_moving_car = 0;
    // tap_moving_forward_car = 0;
    // backforward_moving_truck = 0;
    // ego_stright_inpath_car = 0;
    // for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
    //   const active_safety::AsObstacle &obj = obj_list[i];
    //   if ((obj.object_class == active_safety::ObjectClass::BICYCLE ||
    //        obj.object_class == active_safety::ObjectClass::PEDESTRIAN ||
    //        obj.object_class == active_safety::ObjectClass::GENOBJ ||
    //        obj.object_class == active_safety::ObjectClass::ANIMAL ||
    //        obj.object_class == active_safety::ObjectClass::ESCOOTER ||
    //        obj.object_class == active_safety::ObjectClass::MOTORCYCLE) &&
    //       (std::abs(obj.long_posn) > 50.f || std::abs(obj.lat_posn) > 10.0f)) {
    //     continue;
    //   }
    //   switch (obj.object_class) {
    //   case active_safety::ObjectClass::UNIDENTIFIED_VEHICLE:
    //   case active_safety::ObjectClass::CAR: {
    //     if (obj.speed > society_param.k_sc_moving_veh && 0.0 < obj.long_posn &&
    //         obj.long_posn < 50.0f) {
    //       if (std::abs(obj.long_vel) > 2.0 && std::abs(obj.lat_posn) > 7.0) {
    //       } else {
    //         moving_tgt_cnt += 1;
    //       }
    //     }
    //     CheckBehindCar(obj);

    //     break;
    //   }
    //   case active_safety::ObjectClass::TRUCK: {
    //     ProcessTruckObsctacle(obj);
    //     CheckBehindTruck(obj);
    //     break;
    //   }
    //   case active_safety::ObjectClass::GENOBJ:
    //   case active_safety::ObjectClass::ANIMAL:
    //   case active_safety::ObjectClass::PEDESTRIAN: {
    //     if (obj.speed > 1.1f && 0.0f < obj.long_posn && obj.long_posn < 50.0f &&
    //         std::abs(obj.lat_posn) <= 7.0f) {
    //       moving_tgt_cnt += 1;
    //     }
    //     ped_cnt += 1;
    //     break;
    //   }
    //   case active_safety::ObjectClass::BICYCLE:
    //   case active_safety::ObjectClass::ESCOOTER:
    //   case active_safety::ObjectClass::MOTORCYCLE: {
    //     if (obj.speed > 2.5f) {
    //       moving_tgt_cnt += 1;
    //     } else {
    //       stat_twowhl_cnt += 1;
    //     }
    //     bike_cnt += 1;
    //     break;
    //   }
    //   default:
    //     break;
    //   }
    // }
    // if (ego_.aeb_active) {
    // } else {
    //   bool truck_check =
    //       (truck_cnt > 2 || mov_truck_cnt > 0 || invalid_truck_heading_cnt > 0);
    //   if (moving_tgt_cnt > 3 || truck_check || bike_cnt > 2 ||
    //       stat_twowhl_cnt > 2 || ped_cnt > 4 || backforward_moving_car > 0 ||
    //       ego_stright_inpath_car > 0) {
    //     society_evaluate_obj = true;
    //   } else {
    //     society_evaluate_obj = false;
    //   }
    // }
    // if (society_evaluate_obj) {
    //   society_scene |= AsSocierySceneData::AS_SOCIERY_OBJ_EVALUAT;
    // } else {
    //   society_scene &= ~AsSocierySceneData::AS_SOCIERY_OBJ_EVALUAT;
    // }
}
void AsSocietyScene::ProcessTruckObsctacle(const active_safety::AsObstacle &obj) {
    if (obj.long_posn > 80.f) {
        return;
    }
    if (obj.speed > society_param.k_sc_moving_truck) {
        moving_tgt_cnt += 1;
        mov_truck_cnt += 1;
    }
    truck_cnt += 1;
    if (std::abs(obj.heading) >= 1.0f) {
        invalid_truck_heading_cnt += 1;
    }
}
void AsSocietyScene::CheckBehindCar(const active_safety::AsObstacle &obj) {
    if ((obj.speed > 5) && (-20.0 < obj.long_posn) && (obj.long_posn < 0) && (abs(obj.lat_posn) < 2)) {
        backforward_moving_car += 1;
    }

    if ((abs(ego_.rear_curvature) < 0.001) && (-15.0 < obj.long_posn) && (!simulation_check) && (obj.long_posn < 10) && (abs(obj.lat_posn) < 1.5)) {
        // std::cout<<"fus_trkID" << obj.fus_trkID
        // <<"fus_trkID" << obj.fus_trkID
        // <<"lat_vel" << obj.lat_vel
        // <<"long_posn" << obj.long_posn
        // <<"lat_posn" << obj.lat_posn
        // <<std::endl;
        ego_stright_inpath_car += 1;
    }

    if ((abs(ego_.rear_curvature) > 0.001) && (5.0 < obj.long_posn) && (obj.long_posn < 15) && (obj.long_vel > 3) && (abs(obj.lat_posn) < 3)) {
        tap_moving_forward_car += 1;
    }
}
void AsSocietyScene::CheckBehindTruck(const active_safety::AsObstacle &obj) {
    if ((obj.speed > 4) && (-30.0 < obj.long_posn) && (obj.long_posn < 30) && (abs(obj.lat_posn) < 7)) {
        backforward_moving_truck += 1;
    }
    if ((-10.0 < obj.long_posn) && (obj.long_posn < 10) && (abs(obj.lat_posn) < 5)) {
        backforward_moving_truck += 1;
    }
}

void AsSocietyScene::EgoAtComplexScenePrev(const active_safety::AsObstacleList &obj_list) {
    // int valid_obj_cnt = 0;
    // for (std::size_t idx = 0; idx < kMaxFusionObject; ++idx) {
    //   if (obj_list[idx].fus_trkID > 0 &&
    //       obj_list[idx].fusion_source == FusionSource::RADAR_VISION &&
    //       obj_list[idx].object_class > active_safety::ObjectClass::UNDETERMINED &&
    //       std::abs(obj_list[idx].lat_posn) < 5.0 &&
    //       obj_list[idx].long_posn - ego_.host_dist_to_front <= 30) {
    //     valid_obj_cnt++;
    //   }
    // }
    // if (valid_obj_cnt > 5) {
    //   ego_at_complex_scene_reset_time = 20 * 60 * 1000;
    //   ego_at_complx_scene = true;
    // } else {
    //   if (ego_at_complex_scene_reset_time > LOOP_TIME_SOCIETY) {
    //     ego_at_complex_scene_reset_time -= LOOP_TIME_SOCIETY;
    //   } else {
    //     ego_at_complex_scene_reset_time = 0;
    //     ego_at_complx_scene = false;
    //   }
    // }
    // if (ego_at_complx_scene) {
    //   society_scene |= AsSocierySceneData::AS_COMPLEX_SCENE;
    // } else {
    //   society_scene &= ~AsSocierySceneData::AS_COMPLEX_SCENE;
    // }
}

void AsSocietyScene::CheckEgoJustStationary2Start(const active_safety::AsObstacleList &obj_list) {
    (void)(obj_list);
    bool ego_stationaty2start = false;
    ego_stationaty_           = (display_spd_kph_ <= 0) ? true : false;
    if (!ego_stationaty_ && pre_ego_stationaty_)

    {
        ego_10kph_confirm_cnt = 0;
        ego_20kph_confirm_cnt = 0;
        ego_30kph_confirm_cnt = 0;
        ego_40kph_confirm_cnt = 0;
        ego_50kph_confirm_cnt = 0;
        ego_60kph_confirm_cnt = 0;

        ego_not_10kph_delay_cnt = 0;
        ego_not_20kph_delay_cnt = 0;
        ego_not_30kph_delay_cnt = 0;
        ego_not_40kph_delay_cnt = 0;
        ego_not_50kph_delay_cnt = 0;
        ego_not_60kph_delay_cnt = 0;
        ego_stationaty2start    = true;
    }
    if (ego_stationaty2start) {
        validtime_after_ego_start_cnt = society_param.k_stationary2start_max_valid_time;
    } else {
        validtime_after_ego_start_cnt = validtime_after_ego_start_cnt - 1;

        if (disable_just_start) {
            validtime_after_ego_start_cnt = 0;
        }
    }

    if (validtime_after_ego_start_cnt > 0) {
        within_validtime_after_ego_start_ = true;
    } else {
        within_validtime_after_ego_start_ = false;
    }

    pre_ego_stationaty_ = ego_stationaty_;
}

void AsSocietyScene::CheckEgoConstantSpdForTime() {
    if (display_spd_kph_ > (10 - society_param.k_constand_spd_max_err) && (abs(ego_.rear_curvature) < society_param.k_constant_spd_allow_max_curv) &&
        display_spd_kph_ < (10 + society_param.k_constand_spd_max_err)) {
        ego_10kph_confirm_cnt = ego_10kph_confirm_cnt + 1;
        ego_10kph_confirm_cnt = std::min(ego_10kph_confirm_cnt, 600);
    } else {
        if (!ego_10kph_confirmeok) {
            ego_10kph_confirm_cnt = std::max(ego_10kph_confirm_cnt - 100, 0);
        } else if (ego_10kph_confirmeok) {
            ego_not_10kph_delay_cnt = ego_not_10kph_delay_cnt + 1;
            if (ego_not_10kph_delay_cnt > society_param.k_ego_not_constant_spd_cnt_thrd) {
                ego_10kph_confirm_cnt = 0;
            }
        }
    }

    if (display_spd_kph_ > (20 - society_param.k_constand_spd_max_err) && (abs(ego_.rear_curvature) < society_param.k_constant_spd_allow_max_curv) &&
        display_spd_kph_ < (20 + society_param.k_constand_spd_max_err)) {
        ego_20kph_confirm_cnt = ego_20kph_confirm_cnt + 1;
        ego_20kph_confirm_cnt = std::min(ego_20kph_confirm_cnt, 600);
    } else {
        if (!ego_20kph_confirmeok) {
            ego_20kph_confirm_cnt = std::max(ego_20kph_confirm_cnt - 100, 0);
        } else if (ego_20kph_confirmeok) {
            ego_not_20kph_delay_cnt = ego_not_20kph_delay_cnt + 1;
            if (ego_not_20kph_delay_cnt > society_param.k_ego_not_constant_spd_cnt_thrd) {
                ego_20kph_confirm_cnt = 0;
            }
        }
    }

    if (display_spd_kph_ > (30 - society_param.k_constand_spd_max_err) && (abs(ego_.rear_curvature) < society_param.k_constant_spd_allow_max_curv) &&
        display_spd_kph_ < (30 + society_param.k_constand_spd_max_err)) {
        ego_30kph_confirm_cnt = ego_30kph_confirm_cnt + 1;
        ego_30kph_confirm_cnt = std::min(ego_30kph_confirm_cnt, 600);
    } else {
        if (!ego_30kph_confirmeok) {
            ego_30kph_confirm_cnt = std::max(ego_30kph_confirm_cnt - 100, 0);
        } else if (ego_30kph_confirmeok) {
            ego_not_30kph_delay_cnt = ego_not_30kph_delay_cnt + 1;
            if (ego_not_30kph_delay_cnt > society_param.k_ego_not_constant_spd_cnt_thrd) {
                ego_30kph_confirm_cnt = 0;
            }
        }
    }

    if (display_spd_kph_ > (40 - society_param.k_constand_spd_max_err) && (abs(ego_.rear_curvature) < society_param.k_constant_spd_allow_max_curv) &&
        display_spd_kph_ < (40 + society_param.k_constand_spd_max_err)) {
        ego_40kph_confirm_cnt = ego_40kph_confirm_cnt + 1;
        ego_40kph_confirm_cnt = std::min(ego_40kph_confirm_cnt, 600);
    } else {
        if (!ego_40kph_confirmeok) {
            ego_40kph_confirm_cnt = std::max(ego_40kph_confirm_cnt - 100, 0);
        } else if (ego_40kph_confirmeok) {
            ego_not_40kph_delay_cnt = ego_not_40kph_delay_cnt + 1;
            if (ego_not_40kph_delay_cnt > society_param.k_ego_not_constant_spd_cnt_thrd) {
                ego_40kph_confirm_cnt = 0;
            }
        }
    }

    if (display_spd_kph_ > (50 - society_param.k_constand_spd_max_err) && (abs(ego_.rear_curvature) < society_param.k_constant_spd_allow_max_curv) &&
        display_spd_kph_ < (50 + society_param.k_constand_spd_max_err)) {
        ego_50kph_confirm_cnt = ego_50kph_confirm_cnt + 1;
        ego_50kph_confirm_cnt = std::min(ego_50kph_confirm_cnt, 600);
    } else {
        if (!ego_50kph_confirmeok) {
            ego_50kph_confirm_cnt = std::max(ego_50kph_confirm_cnt - 60, 0);
        } else if (ego_50kph_confirmeok) {
            ego_not_50kph_delay_cnt = ego_not_50kph_delay_cnt + 1;
            if (ego_not_50kph_delay_cnt > society_param.k_ego_not_constant_spd_cnt_thrd) {
                ego_50kph_confirm_cnt = 0;
            }
        }
    }

    if (display_spd_kph_ > (60 - society_param.k_constand_highspd_max_err) &&
        (abs(ego_.rear_curvature) < society_param.k_constant_spd_allow_max_curv) &&
        display_spd_kph_ < (60 + society_param.k_constand_highspd_max_err)) {
        ego_60kph_confirm_cnt = ego_60kph_confirm_cnt + 1;
        ego_60kph_confirm_cnt = std::min(ego_60kph_confirm_cnt, 600);
    } else {
        if (!ego_60kph_confirmeok) {
            ego_60kph_confirm_cnt = std::max(ego_60kph_confirm_cnt - 40, 0);
        } else if (ego_60kph_confirmeok) {
            ego_not_60kph_delay_cnt = ego_not_60kph_delay_cnt + 1;
            if (ego_not_60kph_delay_cnt > society_param.k_ego_not_constant_spd_cnt_thrd) {
                ego_60kph_confirm_cnt = 0;
            }
        }
    }

    if (ego_10kph_confirm_cnt > society_param.k_ego_constant_spd_cnt_thrd) {
        ego_10kph_confirmeok = true;
    } else {
        ego_10kph_confirmeok = false;
    }
    if (ego_20kph_confirm_cnt > society_param.k_ego_constant_spd_cnt_thrd) {
        ego_20kph_confirmeok = true;
    } else {
        ego_20kph_confirmeok = false;
    }
    if (ego_30kph_confirm_cnt > society_param.k_ego_constant_spd_cnt_thrd) {
        ego_30kph_confirmeok = true;
    } else {
        ego_30kph_confirmeok = false;
    }
    if (ego_40kph_confirm_cnt > society_param.k_ego_constant_spd_cnt_thrd) {
        ego_40kph_confirmeok = true;
    } else {
        ego_40kph_confirmeok = false;
    }

    if (ego_50kph_confirm_cnt > society_param.k_ego_constant_spd_cnt_thrd) {
        ego_50kph_confirmeok = true;
    } else {
        ego_50kph_confirmeok = false;
    }
    if (ego_60kph_confirm_cnt > society_param.k_ego_constant_highspd_cnt_thrd) {
        ego_60kph_confirmeok = true;
    } else {
        ego_60kph_confirmeok = false;
    }
    ego_during_turn_constant_spd_ = ego_10kph_confirmeok || ego_20kph_confirmeok || ego_30kph_confirmeok;
    ego_during_stright_constant_spd_ =
        ego_10kph_confirmeok || ego_20kph_confirmeok || ego_30kph_confirmeok || ego_40kph_confirmeok || ego_50kph_confirmeok || ego_60kph_confirmeok;
    ego_cross_constant_spd_      = ego_20kph_confirmeok || ego_40kph_confirmeok || ego_60kph_confirmeok;
    ego_cross_scpo_constant_spd_ = ego_50kph_confirmeok || ego_60kph_confirmeok;
}

void AsSocietyScene::DisableEgoJustStartValid() {
    if ((backforward_moving_car > 0) || (backforward_moving_truck > 0) || (ego_stright_inpath_car > 0) || (tap_moving_forward_car > 0) ||
        (ego_.gas_pedal_pos > society_param.k_disable_testscene_accel_pose_thd) ||
        ((ego_.brake_pedal_pos > society_param.k_disable_testscene_brake_pose_thd) && (!simulation_check))) {
        // std::cout << "brake_pedal_pos" << ego_.brake_pedal_pos
        //     <<"gas_pedal_pos" << ego_.gas_pedal_pos
        //     <<"backforward_moving_car" << backforward_moving_car
        //     <<"ego_stright_inpath_car" << ego_stright_inpath_car
        //     <<"backforward_moving_truck" << backforward_moving_truck
        //     <<"tap_moving_forward_car" << tap_moving_forward_car
        //      <<"simulation_check_cnt" << simulation_check_cnt
        //     <<std::endl;
        disable_just_start = true;
    } else {
        disable_just_start = false;
    }
}
void AsSocietyScene::CheckSceneBaseEgoInfo(const active_safety::AsObstacleList &obj_list) {
    display_spd_kph_ = ego_.speed * 3.6;

    CheckEgoJustStationary2Start(obj_list);
    CheckEgoConstantSpdForTime();

    ego_at_test_scene_ = within_validtime_after_ego_start_ && ego_during_turn_constant_spd_ && (society_scene & 1);
    ego_at_turn_scene_ = within_validtime_after_ego_start_ && ego_during_turn_constant_spd_;
}
void AsSocietyScene::DecideCpta_L(const active_safety::AsObstacleList &obj_list) {
    // for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
    //   const active_safety::AsObstacle &obj = obj_list[i];

    //   if ((((display_spd_kph_ < 21) && (display_spd_kph_ > 19)) ||
    //        ((display_spd_kph_ < 11) && (display_spd_kph_ > 9))) &&
    //       obj.object_class == active_safety::ObjectClass::PEDESTRIAN && ego_at_test_scene_ &&
    //       obj.lat_posn > 8.0f && obj.lat_posn < 11.0f && obj.long_posn > 10.0f &&
    //       obj.long_posn < 60.0f && (cpta_l_require == false)) {
    //     cpta_l_lowspd_cnt = cpta_l_lowspd_cnt + 1;

    //     if (cpta_l_lowspd_cnt > society_param.k_cpta_l_low_cnt_thrd) {
    //       pre_enter_cpta_l_lowspd = true;
    //     }

    //   } else if ((display_spd_kph_ < 31) && (display_spd_kph_ > 29) &&
    //              obj.object_class == active_safety::ObjectClass::PEDESTRIAN &&
    //              ego_at_test_scene_ && obj.lat_posn > 24.0f &&
    //              obj.lat_posn < 30.0f && obj.long_posn > 10.0f &&
    //              (cpta_l_require == false)) {
    //     cpta_l_midspd_cnt = cpta_l_midspd_cnt + 1;
    //     if (cpta_l_midspd_cnt > society_param.k_cpta_l_mid_cnt_thrd) {
    //       pre_enter_cpta_l_midspd = true;
    //     }
    //   } else {
    //   }

    //   if ((ego_.aeb_active) || (!ego_at_test_scene_) || (display_spd_kph_ < 2)) {
    //     pre_enter_cpta_l_lowspd = false;
    //     pre_enter_cpta_l_midspd = false;
    //     cpta_l_midspd_cnt = 0;
    //     cpta_l_lowspd_cnt = 0;
    //   }

    //   if (((pre_enter_cpta_l_lowspd) &&
    //        (ego_.steerwheelangle >
    //         society_param.k_turn_left_steerangle_lowspd_thrd) &&
    //        obj.long_posn < 12.0 && obj.long_posn > 2.0 &&
    //        obj.long_posn < cpta_l_nearest_posnlgt &&
    //        obj.object_class == active_safety::ObjectClass::PEDESTRIAN) ||
    //       (((pre_enter_cpta_l_midspd) &&
    //         (ego_.steerwheelangle >
    //          society_param.k_turn_left_steerangle_midspd_thrd) &&
    //         obj.long_posn < 12.0 && obj.long_posn > 2.0 &&
    //         obj.long_posn < cpta_l_nearest_posnlgt &&
    //         obj.object_class == active_safety::ObjectClass::PEDESTRIAN))) {
    //     //           std::cout << " obj.long_posn =  " <<
    //     //           obj.long_posn
    //     // << " cpta_l_nearest_posnlgt = " << cpta_l_nearest_posnlgt
    //     // << std::endl;
    //     cpta_l_require = true;
    //     cpta_l_fusion_track_id = obj.fus_trkID;
    //     cpta_l_track_id = obj.track_id;
    //     cpta_l_nearest_posnlgt = obj.long_posn;

    //     break;

    //   } else {
    //     cpta_l_require = false;
    //     cpta_l_fusion_track_id = 0;
    //     cpta_l_nearest_posnlgt = 100;
    //     cpta_l_track_id = 0;
    //   }
    // }
    // // std::cout << " cpta_l_midspd_cnt =  " << cpta_l_midspd_cnt
    // // << " pre_enter_cpta_l_midspd = " << pre_enter_cpta_l_midspd
    // // << "终止" << static_cast<int32_t>((ego_.aeb_active) ||
    // // (!ego_at_test_scene_) || (display_spd_kph_ < 2))
    // // << "aeb_active: " << static_cast<int32_t>(ego_.aeb_active)
    // // << "ego_at_test_scene_: " << static_cast<int32_t>(ego_at_test_scene_)
    // // << "display_spd_kph_: " << display_spd_kph_
    // // << std::endl;
}

void AsSocietyScene::DecideCsta_Rn(const active_safety::AsObstacleList &obj_list) {
    // for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
    //   const active_safety::AsObstacle &obj = obj_list[i];

    //   if ((((display_spd_kph_ < 12) && (display_spd_kph_ > 8))) &&
    //       ((obj.object_class == active_safety::ObjectClass::ESCOOTER) ||
    //        (obj.object_class == active_safety::ObjectClass::MOTORCYCLE) ||
    //        (obj.object_class == active_safety::ObjectClass::BICYCLE)) &&
    //       ego_at_test_scene_ && obj.lat_posn < -2.5f && obj.lat_posn > -3.8f &&
    //       obj.long_posn > -18.0f && obj.long_posn < 50.0f &&
    //       (csta_rn_require == false)) {
    //     csta_rn_confirm_lowspd_cnt = csta_rn_confirm_lowspd_cnt + 1;
    //     if (csta_rn_confirm_lowspd_cnt >
    //         society_param.k_csta_rn_cnt_lowspd_thrd) {
    //       pre_enter_csta_rn_lowspd = true;
    //     }
    //   }

    //   if ((((display_spd_kph_ < 22) && (display_spd_kph_ > 18))) &&
    //       ((obj.object_class == active_safety::ObjectClass::ESCOOTER) ||
    //        (obj.object_class == active_safety::ObjectClass::MOTORCYCLE) ||
    //        (obj.object_class == active_safety::ObjectClass::BICYCLE)) &&
    //       ego_at_test_scene_ && obj.lat_posn < -2.5f && obj.lat_posn > -3.8f &&
    //       obj.long_posn > 0.0f && obj.long_posn < 50.0f &&
    //       (csta_rn_require == false)) {
    //     csta_rn_confirm_midspd_cnt = csta_rn_confirm_midspd_cnt + 1;
    //     if (csta_rn_confirm_midspd_cnt >
    //         society_param.k_csta_rn_cnt_midspd_thrd) {
    //       pre_enter_csta_rn_midspd = true;
    //     }
    //   }

    //   if ((ego_.aeb_active) || (!ego_at_test_scene_) || (display_spd_kph_ < 2)) {
    //     csta_rn_fusion_track_id = 0;
    //     pre_enter_csta_rn_lowspd = false;
    //     pre_enter_csta_rn_midspd = false;
    //     csta_rn_confirm_lowspd_cnt = 0;
    //     csta_rn_confirm_midspd_cnt = 0;
    //   }

    //   if (((pre_enter_csta_rn_lowspd) &&
    //        ((obj.object_class == active_safety::ObjectClass::ESCOOTER) ||
    //         (obj.object_class == active_safety::ObjectClass::BICYCLE) ||
    //         (obj.object_class == active_safety::ObjectClass::MOTORCYCLE)) &&
    //        (ego_.steerwheelangle <
    //         society_param.k_turn_right_steerangle_lowthrd) &&
    //        (obj.long_vel > 3.5) && (obj.long_posn < 3.7) &&
    //        (obj.long_posn > -10) && obj.long_posn < cpta_l_nearest_posnlgt) ||
    //       ((pre_enter_csta_rn_midspd) &&
    //        ((obj.object_class == active_safety::ObjectClass::ESCOOTER) ||
    //         (obj.object_class == active_safety::ObjectClass::BICYCLE) ||
    //         (obj.object_class == active_safety::ObjectClass::MOTORCYCLE)) &&
    //        (ego_.steerwheelangle <
    //         society_param.k_turn_right_steerangle_midthrd) &&
    //        (obj.long_vel > 4.0) && (obj.long_posn < 3.7) &&
    //        (obj.long_posn > -5) && obj.long_posn < cpta_l_nearest_posnlgt)) {
    //     csta_rn_require = true;
    //     csta_rn_fusion_track_id = obj.fus_trkID;
    //     csta_rn_track_id = obj.track_id;
    //     csta_rn_nearest_posnlgt = obj.long_posn;
    //     break;

    //   } else {
    //     csta_rn_require = false;
    //     csta_rn_fusion_track_id = 0;
    //     csta_rn_track_id = 0;
    //     csta_rn_nearest_posnlgt = 100;
    //   }
    // }
}

void AsSocietyScene::CheckCpfaoBarrierCar(const active_safety::AsObstacle &obj) {
    if ((obj.lat_posn > 4) && (obj.lat_posn < 8) && (obj.long_posn < 80) && (obj.long_posn > 5) && (obj.speed < society_param.k_sc_moving_veh) &&
        (abs(ego_.rear_curvature) < 0.0015)) {
        barrier_car_cpfao_count_ += 1;
        barrier_car_cpfao_num_ += 1;

        if ((cpfao_barrier_car_condition_ok_) && (obj.long_posn < cpfao_barrier_car_nearest_posnlgt)) {
            cpfao_barrier_car_nearest_posnlgt = obj.long_posn;
        }
        // if (ego_20kph_confirmeok || ego_40kph_confirmeok || ego_60kph_confirmeok)
        // {
        //   // std::cout << "barrier_car_cpfao_count_" << barrier_car_cpfao_count_
        //   //           << "barrier_car_cpfao_num_" << barrier_car_cpfao_num_
        //   //           << "within_validtime_after_ego_start_"
        //   //           << within_validtime_after_ego_start_ << "display_spd_kph_"
        //   //           << display_spd_kph_ << "cpfao_barrier_car_condition_ok_"
        //   //           << cpfao_barrier_car_condition_ok_ << "obj.long_posn"
        //   //           << obj.long_posn << "obj.lat_posn" << obj.lat_posn
        //   //           << "cpfao_barrier_car_nearest_posnlgt"
        //   //           << cpfao_barrier_car_nearest_posnlgt << "obj.fus_trkID"
        //   //           << obj.fus_trkID << std::endl;
        // }
    }

    if ((!within_validtime_after_ego_start_) || (display_spd_kph_ < 2) || (abs(ego_.rear_curvature) > 0.01)) {
        barrier_car_cpfao_count_        = 0;
        cpfao_barrier_car_condition_ok_ = false;
    }
    if ((barrier_car_cpfao_count_ > society_param.k_cpfao_barrier_car_thrd_) && (barrier_car_cpfao_num_ > 0) && (barrier_car_cpfao_num_ < 4) &&
        (ego_20kph_confirmeok || ego_40kph_confirmeok)) {
        cpfao_barrier_car_condition_ok_ = true;
    } else if ((barrier_car_cpfao_count_ > society_param.k_cpfao_barrier_car_highspd_thrd_) && (barrier_car_cpfao_num_ > 0) &&
               (barrier_car_cpfao_num_ < 4) && ego_60kph_confirmeok) {
        cpfao_barrier_car_condition_ok_ = true;
    }
}
void AsSocietyScene::CheckCPFAOTarget(const active_safety::AsObstacle &obj) {
    if ((obj.lat_posn > 0) && (obj.lat_posn < 7) && (obj.long_posn > 3.7) && ((obj.lat_vel < -0.5) || (!k_cross_vlat_check_)) &&
        ((abs(obj.long_vel) < 2) || (!k_cross_vlgt_check_)) && ego_cross_constant_spd_ && (obj.long_posn < forbrake_poselong_thd_) &&
        within_validtime_after_ego_start_ && cpfao_barrier_car_condition_ok_ && (obj.long_posn > (cpfao_barrier_car_nearest_posnlgt - 2)) &&
        (abs(obj.long_posn - cpfao_barrier_car_nearest_posnlgt) < society_param.k_cpfao_max_ped_car_delt_Poselgt)) {
        // std::cout << "捕捉到CPFAO"
        //           << "ped.poselgt" << obj.long_posn << "ped.poselat" <<
        //           obj.lat_posn
        //           << "cpfao_barrier_car_nearest_posnlgt"
        //           << cpfao_barrier_car_nearest_posnlgt << "display_spd_kph_"
        //           << display_spd_kph_ << "距离阈值" << forbrake_poselong_thd_
        //           << "横穿目标速度" << obj.lat_vel << "自车键速度" << "fusion_id"
        //           << obj.fus_trkID << ego_.long_accel << std::endl;
        cpfao_track_id = obj.track_id;
        cpfao_require  = true;
        society_scene |= AsSocierySceneData::AS_STRICT_CPFAO_SCENE;

    } else {
        cpfao_track_id = uint32_t(0);
        cpfao_require  = false;
        society_scene &= ~AsSocierySceneData::AS_STRICT_CPFAO_SCENE;
        // if (cpfao_barrier_car_condition_ok_ && within_validtime_after_ego_start_)
        // {
        //   std::cout << "发现CPFAO"
        //             << "ped.poselgt" << obj.long_posn << "ped.poselat"
        //             << obj.lat_posn << "cpfao_barrier_car_nearest_posnlgt"
        //             << cpfao_barrier_car_nearest_posnlgt << "display_spd_kph_"
        //             << display_spd_kph_ << "距离阈值" << forbrake_poselong_thd_
        //             << "横穿目标速度" << obj.lat_vel << "fusion_id" <<
        //             obj.fus_trkID
        //             << std::endl;
        // }
    }
}

void AsSocietyScene::CheckCBNAOTarget(const active_safety::AsObstacle &obj) {
    if ((obj.lat_posn < 0) && (obj.lat_posn > -12) && (obj.long_posn > 3.7) && (obj.lat_vel < 12.0) &&
        ((obj.lat_vel > 1) || (!k_cross_vlat_check_)) && ((abs(obj.long_vel) < 3) || (!k_cross_vlgt_check_)) && ego_cross_constant_spd_ &&
        (obj.long_posn < forbrake_poselong_thd_) && within_validtime_after_ego_start_ && (obj.long_posn > (cbnao_barrier_car_nearest_posnlgt - 4)) &&
        cbnao_barrier_car_condition_ok_ &&
        (abs(obj.long_posn - cbnao_barrier_car_nearest_posnlgt) < society_param.k_cbnao_max_ped_car_delt_Poselgt)) {
        // std::cout << "捕捉到CBNAO"
        //           << "cb.poselgt" << obj.long_posn << "ped.poselat" <<
        //           obj.lat_posn
        //           << "cbnao_barrier_car_nearest_posnlgt"
        //           << cbnao_barrier_car_nearest_posnlgt << "display_spd_kph_"
        //           << display_spd_kph_ << std::endl;
        cbnao_track_id = obj.track_id;
        cbnao_require  = true;
        society_scene |= AsSocierySceneData::AS_STRICT_CBNAO_SCENE;

    } else {
        cbnao_track_id = uint32_t(0);
        cbnao_require  = false;
        society_scene &= ~AsSocierySceneData::AS_STRICT_CBNAO_SCENE;
    }
}
void AsSocietyScene::CheckCSFAOTarget(const active_safety::AsObstacle &obj) {
    if ((obj.lat_posn > 0) && (obj.lat_posn < 18) && (obj.long_posn > 3.7) && ((obj.lat_vel < -1.0) || (!k_cross_vlat_check_)) &&
        ((abs(obj.long_vel) < 3) || (!k_cross_vlgt_check_)) && ego_cross_constant_spd_ && (obj.long_posn < forbrake_poselong_thd_) &&
        within_validtime_after_ego_start_ && (obj.long_posn > (csfao_barrier_car_nearest_posnlgt - 4)) && csfao_barrier_car_condition_ok_ &&
        (abs(obj.long_posn - csfao_barrier_car_nearest_posnlgt) < society_param.k_csfao_max_ped_car_delt_Poselgt)) {
        // std::cout << "捕捉到CSFAO"
        //           << "cb.poselgt" << obj.long_posn << "ped.poselat" <<
        //           obj.lat_posn
        //           << "fusion_id" << obj.fus_trkID
        //           << "csfao_barrier_car_nearest_posnlgt"
        //           << csfao_barrier_car_nearest_posnlgt << "display_spd_kph_"
        //           << display_spd_kph_ << std::endl;
        csfao_track_id  = obj.track_id;
        csfao_fusion_id = obj.fus_trkID;
        csfao_require   = true;
        society_scene |= AsSocierySceneData::AS_STRICT_CSFAO_SCENE;

    } else {
        csfao_track_id  = uint32_t(0);
        csfao_fusion_id = uint32_t(0);
        csfao_require   = false;
        society_scene &= ~AsSocierySceneData::AS_STRICT_CSFAO_SCENE;
    }
}

void AsSocietyScene::CheckScpoTarget(const active_safety::AsObstacle &obj) {
    if ((obj.lat_posn < 0) && (obj.lat_posn > -50) && (obj.long_posn > 3.7) && ((obj.lat_vel > 5) || (!k_cross_vlat_check_)) &&
        ((abs(obj.long_vel) < 3) || (!k_cross_vlgt_check_)) && ego_cross_scpo_constant_spd_ && (obj.long_posn < forbrake_poselong_thd_) &&
        (abs(obj.heading) > 1.2) && (abs(obj.heading) < 1.9) && (obj.lat_vel > 2.0) && (obj.long_posn > (scpo_barrier_car_nearest_posnlgt - 4)) &&
        scpo_barrier_car_condition_ok_ && (abs(obj.long_posn - scpo_barrier_car_nearest_posnlgt) < society_param.k_csfao_max_car_car_delt_Poselgt)) {
        // std::cout << "捕捉到scpo"
        //           << "cb.poselgt" << obj.long_posn << "ped.poselat" <<
        //           obj.lat_posn
        //           << "ped.heading" << obj.heading
        //           << "scpo_barrier_car_nearest_posnlgt"
        //           << scpo_barrier_car_nearest_posnlgt << "display_spd_kph_"
        //           << display_spd_kph_ << "距离阈值" << forbrake_poselong_thd_
        //           << "横穿目标速度" << obj.lat_vel << "fusion_id" <<
        //           obj.fus_trkID
        //           << std::endl;
        scpo_track_id = obj.track_id;
        scpo_require  = true;
        society_scene |= AsSocierySceneData::AS_STRICT_SCPO_SCENE;

    } else {
        scpo_track_id = uint32_t(0);
        scpo_require  = false;
        society_scene &= ~AsSocierySceneData::AS_STRICT_SCPO_SCENE;
        // if (scpo_barrier_car_condition_ok_ && within_validtime_after_ego_start_
        // &&
        //     (obj.lat_posn < 0) && (obj.lat_posn > -50) && (obj.long_posn > 3.7))
        //     {
        //   std::cout << "发现SCPO"
        //             << "ped.poselgt" << obj.long_posn << "ped.poselat"
        //             << obj.lat_posn << "scpo_barrier_car_nearest_posnlgt"
        //             << scpo_barrier_car_nearest_posnlgt << "display_spd_kph_"
        //             << display_spd_kph_ << "距离阈值" << forbrake_poselong_thd_
        //             << "横穿目标速度" << obj.lat_vel << "fusion_id" <<
        //             obj.fus_trkID
        //             << std::endl;
        // }
    }
}
void AsSocietyScene::CheckCbnaoBarrierCar(const active_safety::AsObstacle &obj) {
    if ((obj.lat_posn > -12) && (obj.lat_posn < -8) && (obj.long_posn < 80) && (obj.long_posn > 3.7) && (obj.speed < society_param.k_sc_moving_veh) &&
        (abs(ego_.rear_curvature) < 0.0015)) {
        barrier_car_cbnao_count_ += 1;
        barrier_car_cbnao_num_ += 1;

        if ((cbnao_barrier_car_condition_ok_) && (obj.long_posn < cbnao_barrier_car_nearest_posnlgt)) {
            cbnao_barrier_car_nearest_posnlgt = obj.long_posn;
        }
        // if ((obj.long_posn > 2) &&
        //     ((18 < display_spd_kph_) && (display_spd_kph_ < 22) ||
        //      (38 < display_spd_kph_) && (display_spd_kph_ < 42) ||
        //      (58 < display_spd_kph_) && (display_spd_kph_ < 62))) {
        //   std::cout << "barrier_car_cbnao_count_" << barrier_car_cbnao_count_
        //             << "barrier_car_cbnao_num_" << barrier_car_cbnao_num_
        //             << "within_validtime_after_ego_start_"
        //             << within_validtime_after_ego_start_ << "display_spd_kph_"
        //             << display_spd_kph_ << "cbnao_barrier_car_condition_ok_"
        //             << cbnao_barrier_car_condition_ok_ << "obj.long_posn"
        //             << obj.long_posn << "obj.lat_posn" << obj.lat_posn
        //             << "cbnao_barrier_car_nearest_posnlgt"
        //             << cbnao_barrier_car_nearest_posnlgt << "obj.fus_trkID"
        //             << obj.fus_trkID << std::endl;
        // }
    }

    if ((!within_validtime_after_ego_start_) || (display_spd_kph_ < 2) || (abs(ego_.rear_curvature) > 0.01)) {
        barrier_car_cbnao_count_        = 0;
        cbnao_barrier_car_condition_ok_ = false;
    }
    if ((barrier_car_cbnao_count_ > society_param.k_cbnao_barrier_car_thrd_) && (barrier_car_cbnao_num_ > 0) && (barrier_car_cbnao_num_ < 4) &&
        (ego_20kph_confirmeok || ego_40kph_confirmeok)) {
        cbnao_barrier_car_condition_ok_ = true;
    } else if ((barrier_car_cbnao_count_ > society_param.k_cbnao_barrier_car_highspd_thrd_) && (barrier_car_cbnao_num_ > 0) &&
               (barrier_car_cbnao_num_ < 4) && (ego_60kph_confirmeok)) {
        cbnao_barrier_car_condition_ok_ = true;
    }
}
void AsSocietyScene::CheckCsfaoBarrierCar(const active_safety::AsObstacle &obj) {
    if ((obj.lat_posn > 15) && (obj.lat_posn < 19) && (obj.long_posn < 80) && (obj.long_posn > 3.7) && (obj.speed < society_param.k_sc_moving_veh) &&
        (abs(ego_.rear_curvature) < 0.0015)) {
        barrier_car_csfao_count_ += 1;
        barrier_car_csfao_num_ += 1;
        if ((csfao_barrier_car_condition_ok_) && (obj.long_posn < csfao_barrier_car_nearest_posnlgt)) {
            csfao_barrier_car_nearest_posnlgt = obj.long_posn;
        }
    }

    if ((!within_validtime_after_ego_start_) || (display_spd_kph_ < 2) || (abs(ego_.rear_curvature) > 0.01)) {
        barrier_car_csfao_count_        = 0;
        csfao_barrier_car_condition_ok_ = false;
    }
    if ((barrier_car_csfao_count_ > society_param.k_csfao_barrier_car_thrd_) && (barrier_car_csfao_num_ > 0) && (barrier_car_csfao_num_ < 4) &&
        (ego_20kph_confirmeok || ego_40kph_confirmeok)) {
        csfao_barrier_car_condition_ok_ = true;
    } else if ((barrier_car_csfao_count_ > society_param.k_csfao_barrier_car_highspd_thrd_) && (barrier_car_csfao_num_ > 0) &&
               (barrier_car_csfao_num_ < 4) && ego_60kph_confirmeok) {
        csfao_barrier_car_condition_ok_ = true;
    }

    // if ((obj.long_posn > 2) &&
    //     ((18 < display_spd_kph_) && (display_spd_kph_ < 22) ||
    //      (38 < display_spd_kph_) && (display_spd_kph_ < 42) ||
    //      (58 < display_spd_kph_) && (display_spd_kph_ < 62))) {
    //   // std::cout << "barrier_car_csfao_count_" << barrier_car_csfao_count_
    //   //           << "barrier_car_csfao_num_" << barrier_car_csfao_num_
    //   //           << "within_validtime_after_ego_start_"
    //   //           << within_validtime_after_ego_start_ << "display_spd_kph_"
    //   //           << display_spd_kph_ << "csfao_barrier_car_condition_ok_"
    //   //           << csfao_barrier_car_condition_ok_ << "obj.long_posn"
    //   //           << obj.long_posn << "obj.lat_posn" << obj.lat_posn
    //   //           << "csfao_barrier_car_nearest_posnlgt"
    //   //           << csfao_barrier_car_nearest_posnlgt << "obj.fus_trkID"
    //   //           << obj.fus_trkID << std::endl;
    // }
}

void AsSocietyScene::CheckScpoBarrierCar(const active_safety::AsObstacle &obj) {
    if ((obj.lat_posn > -5.5) && (obj.lat_posn < -1.5) && (obj.long_posn < 80) && (obj.long_posn > 3.7) &&
        (obj.speed < society_param.k_sc_moving_veh) && (abs(ego_.rear_curvature) < 0.0015)) {
        barrier_car_scpo_count_ += 1;
        barrier_car_scpo_num_ += 1;
        if ((scpo_barrier_car_condition_ok_) && (obj.long_posn < scpo_barrier_car_nearest_posnlgt)) {
            scpo_barrier_car_nearest_posnlgt = obj.long_posn;
        }
    }

    if ((!within_validtime_after_ego_start_) || (display_spd_kph_ < 2) || (abs(ego_.rear_curvature) > 0.01)) {
        barrier_car_scpo_count_        = 0;
        scpo_barrier_car_condition_ok_ = false;
    }
    if ((barrier_car_scpo_count_ > society_param.k_scpo_barrier_car_highspd_thrd_) && (barrier_car_scpo_num_ > 0) && (barrier_car_scpo_num_ < 5) &&
        (ego_50kph_confirmeok || ego_60kph_confirmeok)) {
        scpo_barrier_car_condition_ok_ = true;
    }

    // if ((obj.long_posn > 2) &&
    //     ((48 < display_spd_kph_) && (display_spd_kph_ < 52) ||
    //      (58 < display_spd_kph_) && (display_spd_kph_ < 62))) {
    //   // std::cout << "barrier_car_scpo_count_" << barrier_car_scpo_count_
    //   //           << "barrier_car_scpo_num_" << barrier_car_scpo_num_
    //   //           << "within_validtime_after_ego_start_"
    //   //           << within_validtime_after_ego_start_ << "display_spd_kph_"
    //   //           << display_spd_kph_ << "scpo_barrier_car_condition_ok_"
    //   //           << scpo_barrier_car_condition_ok_ << "obj.long_posn"
    //   //           << obj.long_posn << "obj.lat_posn" << obj.lat_posn
    //   //           << "scpo_barrier_car_nearest_posnlgt"
    //   //           << scpo_barrier_car_nearest_posnlgt << "obj.fus_trkID"
    //   //           << obj.fus_trkID << std::endl;
    // }
}
void AsSocietyScene::CrossingObjProcess(const active_safety::AsObstacle &obj) {
    switch (obj.object_class) {
        case active_safety::ObjectClass::PEDESTRIAN:
            CheckCPFAOTarget(obj);

            break;
        case active_safety::ObjectClass::CAR:

            CheckCpfaoBarrierCar(obj);
            CheckCbnaoBarrierCar(obj);
            CheckCsfaoBarrierCar(obj);
            CheckScpoBarrierCar(obj);
            CheckScpoTarget(obj);

            break;

        case active_safety::ObjectClass::MOTORCYCLE:
        case active_safety::ObjectClass::BICYCLE:
        case active_safety::ObjectClass::ESCOOTER:
            CheckCBNAOTarget(obj);
            CheckCSFAOTarget(obj);
            break;

        default:

            break;
    }
}
//

void AsSocietyScene::CalPoseLongThdForBrake() {
    forbrake_poselong_thd_ =
        LookUpTable::LookupTable1D<6>(society_param.k_host_spd_brakepoints, society_param.k_brake_distance_brakepoints, display_spd_kph_);
    if ((ego_.long_accel < -4) || (ego_.aeb_active) || scpo_barrier_car_condition_ok_) {
        if (ego_60kph_confirmeok) {
            if (scpo_barrier_car_condition_ok_) {
                forbrake_poselong_thd_ = forbrake_poselong_thd_ + 27;
            } else {
                forbrake_poselong_thd_ = forbrake_poselong_thd_ + 7;
            }

        } else if (ego_50kph_confirmeok && scpo_barrier_car_condition_ok_) {
            forbrake_poselong_thd_ = forbrake_poselong_thd_ + 20;
        } else if (ego_40kph_confirmeok) {
            forbrake_poselong_thd_ = forbrake_poselong_thd_ + 5;
        } else if (ego_20kph_confirmeok) {
            forbrake_poselong_thd_ = forbrake_poselong_thd_ + 3;
        }
    }
}
void AsSocietyScene::ResetCrossTapObj() {
    // reset require
    cpfao_require   = false;
    cbnao_require   = false;
    csfao_require   = false;
    scpo_require    = false;
    csta_rn_require = false;
    cpta_l_require  = false;

    // reset require id
    cpfao_track_id   = 0;
    cbnao_track_id   = 0;
    csfao_track_id   = 0;
    scpo_track_id    = 0;
    csta_rn_track_id = 0;
    cpta_l_track_id  = 0;

    // reset
    society_scene &= ~AsSocierySceneData::AS_STRICT_CPFAO_SCENE;
    society_scene &= ~AsSocierySceneData::AS_STRICT_CBNAO_SCENE;
    society_scene &= ~AsSocierySceneData::AS_STRICT_CSFAO_SCENE;
    society_scene &= ~AsSocierySceneData::AS_STRICT_SCPO_SCENE;
}
void AsSocietyScene::CrossingSceneCheck(const active_safety::AsObstacleList &obj_list) {
    // barrier_car_cpfao_num_ = 0;
    // barrier_car_cbnao_num_ = 0;
    // barrier_car_csfao_num_ = 0;
    // barrier_car_scpo_num_ = 0;

    // for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
    //   const active_safety::AsObstacle &obj = obj_list[i];
    //   if (((obj.object_class == active_safety::ObjectClass::ESCOOTER) ||
    //        (obj.object_class == active_safety::ObjectClass::MOTORCYCLE) ||
    //        (obj.object_class == active_safety::ObjectClass::BICYCLE) ||
    //        (obj.object_class == active_safety::ObjectClass::PEDESTRIAN) ||
    //        (obj.object_class == active_safety::ObjectClass::CAR)) &&
    //       (obj.fus_trkID > 0) && society_param.k_enable_cross_special_select) {
    //     CrossingObjProcess(obj);
    //   }
    // }
}

} // namespace tap
} // namespace senseAD
