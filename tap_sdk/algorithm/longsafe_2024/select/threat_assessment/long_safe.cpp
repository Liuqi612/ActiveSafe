/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */

#include "long_safe.h"

#include <cstdio>
#include <limits>
namespace senseAD {
namespace tap {

AsLongSafe::AsLongSafe() {
    for (std::size_t i = 0; i < obs_list_.size(); ++i) {
        obs_list_[i] = std::make_shared<active_safety::AsObstacle>();
    }
}
AsLongSafe::~AsLongSafe() {
}

int32_t AsLongSafe::GetAebObjFusId() const {
    return long_safe_out_.longsafe_aeb.prm_tgt.obj.fus_trkID;
}

void AsLongSafe::Run(const active_safety::AsObstacleList &obs_list, const AS_LaneMarkerInfo_T &road_maker_info, const AsVseOut &vse,
                     const AsSocietyScene &society_scene) {
    vse_ = vse;
    for (std::size_t i = 0; i < obs_list.size() && i < obs_list_.size(); ++i) {
        if (obs_list[i] != nullptr) {
            *obs_list_[i] = *obs_list[i];
        } else {
            obs_list_[i]->Clear();
        }
    }
    // 修改位置：将位置从物体中心调整到物体后边缘（用于碰撞检测）
    for (std::size_t i = 0; i < obs_list_.size(); ++i) {
        if (obs_list_[i] != nullptr &&
            (obs_list_[i]->object_class == active_safety::ObjectClass::BUS || obs_list_[i]->object_class == active_safety::ObjectClass::TRUCK ||
             obs_list_[i]->object_class == active_safety::ObjectClass::CAR || obs_list_[i]->object_class == active_safety::ObjectClass::BICYCLE ||
             obs_list_[i]->object_class == active_safety::ObjectClass::ESCOOTER ||
             obs_list_[i]->object_class == active_safety::ObjectClass::MOTORCYCLE)) {
            obs_list_[i]->lat_posn = obs_list_[i]->lat_posn - 0.5f * sinf(obs_list_[i]->heading) * obs_list_[i]->length;
            obs_list_[i]->long_posn = obs_list_[i]->long_posn - 0.5f * cosf(obs_list_[i]->heading) * obs_list_[i]->length;
        }
    }
    curv_path_.UpdatePath(vse_.vcs_long_vel, vse_.long_accel, vse_.rear_curvature, vse_.rear_curvaturerate, vse_.host_width, vse_.host_length,
                          vse_.host_dist_to_front);

    CalcObstacleData(obs_list_, society_scene);
    FindThreatTarget(obs_list_, society_scene);
    object_evaluator.ProcessAsScenarioDisc(single_ass.GetIntvPrimData().prim_tgt.obj, obs_list_, vse_, road_maker_info);
#ifdef DEBUG_LONG_TSEL
    std::cout << "AebId:" << single_ass.GetIntvPrimData().prim_tgt.obj.fus_trkID
              << "long_pose:" << single_ass.GetIntvPrimData().prim_tgt.obj.long_posn
              << "lat_pose:" << single_ass.GetIntvPrimData().prim_tgt.obj.lat_posn
              << "type:" << (int)single_ass.GetIntvPrimData().prim_tgt.obj.object_class << std::endl;
#endif
}

void AsLongSafe::CalcObstacleData(const active_safety::AsObstacleList &obs_list, const AsSocietyScene &society_scene) {

    for (std::size_t i = 0; i < kMaxFusionObject; i++) {

        if (!CheckValidLongSafeObject(vse_, *obs_list[i])) {
            obstacle_data_[i].Clear();
            continue;
        }

        obstacle_data_[i].ObjectPreProcess(*obs_list[i], curv_path_, vse_, society_scene);
#ifdef DEBUG_LONG_TSEL
        std::cout << "FusId:" << obs_list[i].fus_trkID << " LongPos:" << obs_list[i].long_posn << " LatPos:" << obs_list[i].lat_posn << std::endl;
        std::cout << " DistFromLeft:" << obstacle_data_[i].GetInpathData().GetPredictInPathData().inpath_short_pred.dist_from_left
                  << " DistFromRight:" << obstacle_data_[i].GetInpathData().GetPredictInPathData().inpath_short_pred.dist_from_right
                  << " PredOffset:" << obstacle_data_[i].GetInpathData().GetPredictInPathData().inpath_short_pred.pred_offset << std::endl;
        std::cout << " CloseEdge:" << obstacle_data_[i].GetSafeMarginEvalData().predict_offset.offs_lat_in_path_close_edge
                  << " FarEdge:" << obstacle_data_[i].GetSafeMarginEvalData().predict_offset.offs_lat_in_path_far_edge
                  << " SideLat:" << obstacle_data_[i].GetCollisionEvalData().bounding_box.length_side_lat
                  << " SideLong:" << obstacle_data_[i].GetCollisionEvalData().bounding_box.length_side_lgt << std::endl;
#endif
    }
}
void AsLongSafe::FindThreatTarget(const active_safety::AsObstacleList &obs_list, const AsSocietyScene &society_scene) {
    (void)(society_scene);
    single_ass.ResetPrimaryTargetData();

    for (std::size_t i = 0; i < kMaxFusionObject; i++) {
        if (obstacle_data_[i].GetInpathData().GetResultData().inpath_short_pred.in_path) {
            single_ass.FindPrimaryTargetForIntv(*obs_list[i], obstacle_data_[i], curv_path_, vse_);
        }
        if (obstacle_data_[i].GetInpathData().GetResultData().inpath_long_pred.in_path) {
            single_ass.FindPrimaryTargetForWarn(*obs_list[i], obstacle_data_[i], curv_path_, vse_);
        }
    }

    //   strict_scp_obj_idx = society_scene.GetStrictScpObj();
    //   strict_cpnco_obj_idx = society_scene.GetStrictCpncoObj();
    // if (strict_scp_obj_idx > 0) {
    //   UpdateLongSafeOutForStrictScp();
    // } else if (strict_cpnco_obj_idx > 0) {
    //   UpdateLongSafeOutForStrictCpnco();
    // } else if (society_scene.GetCptalObjRequire() == true) {
    //   cpta_l_obj_index = society_scene.GetCptalObj() - 1;
    //   UpdateLongSafeOutForCptal();
    // } else if (society_scene.GetCstaRnObjRequire() == true) {
    //   csta_rn_obj_index = society_scene.GetCstaRnObj() - 1;
    //   UpdateLongSafeOutForCstaRn();
    // } else if (society_scene.GetCpfaoObjRequire() == true) {
    //   cpfao_obj_index = society_scene.GetCpfaoObj() - 1;
    //   UpdateLongSafeOutForCpfao();
    // } else if (society_scene.GetCbnaoObjRequire() == true) {
    //   cbnao_obj_index = society_scene.GetCbnaoObj() - 1;
    //   UpdateLongSafeOutForCbnao();
    // } else if (society_scene.GetCsfaoObjRequire() == true) {
    //   csfao_obj_index = society_scene.GetCsfaoObj() - 1;
    //   UpdateLongSafeOutForCsfao();
    // } else if (society_scene.GetScpoObjRequire() == true) {
    //   scpo_obj_index = society_scene.GetScpoObj() - 1;
    //   UpdateLongSafeOutForScpo();
    // } else {
    UpdateLongSafeOut(single_ass);
    // }

    //     std::cout << "选中目标"
    // << "选中目标 纵向位置"
    // <<long_safe_out_.longsafe_aeb.prm_tgt.obj.long_posn
    // << "选中目标 横向位置"
    // <<long_safe_out_.longsafe_aeb.prm_tgt.obj.lat_posn
    // << "选中目标 Vel_x"
    // <<long_safe_out_.longsafe_aeb.prm_tgt.obj.long_vel
    // << "选中目标 Vel_y"
    // <<long_safe_out_.longsafe_aeb.prm_tgt.obj.lat_vel
    // << std::endl;
    // }
}

bool AsLongSafe::CheckValidLongSafeObject(const AsVseOut &ego, const active_safety::AsObstacle &obs) {
    bool simple_check = false;
    bool position_check = false;
    bool road_edge_check = true;
    if (obs.fus_trkID > 0 && obs.object_class > active_safety::ObjectClass::UNDETERMINED &&
        (obs.fusion_source == active_safety::FusionSource::RADAR_VISION || obs.fusion_source == active_safety::FusionSource::VISION_ONLY) &&
        obs.confidence < 4.8f) {
        simple_check = true;
    }
    // Check valid position for forward
    float rear_valid_posn_lgt = 0;
    if (obs.object_class == active_safety::ObjectClass::ESCOOTER && obs.long_vel > 3) {
        rear_valid_posn_lgt = -8;
    } else {
        rear_valid_posn_lgt = -2;
    }
    if (ego.f_reverse_status == 0) {
        float abs_heading = std::abs(obs.heading);
        float proj_width = sinf(abs_heading) * obs.length + obs.width * cosf(abs_heading);
        float overlap_pos = 0.5 * (proj_width + ego.host_width);
        if (ego.straight_driving) {
            if (((std::abs(obs.lat_posn) <= overlap_pos) && (obs.long_posn > 3.7)) ||
                ((std::abs(obs.lat_posn) > overlap_pos) && (obs.long_posn > 0.8))) {
                position_check = true;
            }
        } else if (obs.long_posn > rear_valid_posn_lgt) {

            position_check = true;
        }
        if ((obs.object_class == active_safety::ObjectClass::CAR || obs.object_class == active_safety::ObjectClass::TRUCK) && obs.long_posn < 0.0f) {
            position_check = false;
        }
    }
    return (simple_check && position_check && road_edge_check);
}

void AsLongSafe::UpdateLongSafeOutForScpo(const active_safety::AsObstacleList &obs_list) {
    // // version
    ++long_safe_out_.longsafe_roll_cnt;
    long_safe_out_.longsafe_major_version = long_safe_cal_.k_longsafe_major_version;
    long_safe_out_.longsafe_minor_version = long_safe_cal_.k_longsafe_minor_version;
    long_safe_out_.longsafe_aeb.prm_tgt.obj = *obs_list[scpo_obj_index];
    long_safe_out_.longsafe_aeb.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_aeb.prm_tgt.obj_data = obstacle_data_[scpo_obj_index];

    // long_safe_out_.longsafe_aeb.prm_tgt.obj.match_conf = 5;

    long_safe_out_.longsafe_fcw.prm_tgt.obj = *obs_list[scpo_obj_index];
    long_safe_out_.longsafe_fcw.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_fcw.prm_tgt.obj_data = obstacle_data_[scpo_obj_index];
    //    if (obs_list[scpo_obj_index].lat_vel > 0) {
    //        long_safe_out_.longsafe_aeb.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    //        long_safe_out_.longsafe_fcw.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    //    } else {
    //        long_safe_out_.longsafe_aeb.prm_tgt.obj.motion_type = ObjectMotionType::LEFT_STRAIGHT_CROSS;
    //        long_safe_out_.longsafe_fcw.prm_tgt.obj.motion_type = ObjectMotionType::LEFT_STRAIGHT_CROSS;
    //    }

    // long_safe_out_.longsafe_fcw.prm_tgt.obj.match_conf = 5;
}
void AsLongSafe::UpdateLongSafeOutForCsfao(const active_safety::AsObstacleList &obs_list) {
    // // version
    ++long_safe_out_.longsafe_roll_cnt;
    long_safe_out_.longsafe_major_version = long_safe_cal_.k_longsafe_major_version;
    long_safe_out_.longsafe_minor_version = long_safe_cal_.k_longsafe_minor_version;
    long_safe_out_.longsafe_aeb.prm_tgt.obj = *obs_list[csfao_obj_index];
    long_safe_out_.longsafe_aeb.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_aeb.prm_tgt.obj_data = obstacle_data_[csfao_obj_index];

    // long_safe_out_.longsafe_aeb.prm_tgt.obj.match_conf = 5;

    long_safe_out_.longsafe_fcw.prm_tgt.obj = *obs_list[csfao_obj_index];
    long_safe_out_.longsafe_fcw.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_fcw.prm_tgt.obj_data = obstacle_data_[csfao_obj_index];
    //    if (obs_list[csfao_obj_index].lat_vel > 0) {
    //        long_safe_out_.longsafe_aeb.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    //        long_safe_out_.longsafe_fcw.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    //    } else {
    //        long_safe_out_.longsafe_aeb.prm_tgt.obj.motion_type = ObjectMotionType::LEFT_STRAIGHT_CROSS;
    //        long_safe_out_.longsafe_fcw.prm_tgt.obj.motion_type = ObjectMotionType::LEFT_STRAIGHT_CROSS;
    //    }
    // long_safe_out_.longsafe_fcw.prm_tgt.obj.match_conf = 5;
}
void AsLongSafe::UpdateLongSafeOutForCbnao(const active_safety::AsObstacleList &obs_list) {
    // // version
    ++long_safe_out_.longsafe_roll_cnt;
    long_safe_out_.longsafe_major_version = long_safe_cal_.k_longsafe_major_version;
    long_safe_out_.longsafe_minor_version = long_safe_cal_.k_longsafe_minor_version;
    long_safe_out_.longsafe_aeb.prm_tgt.obj = *obs_list[cbnao_obj_index];
    long_safe_out_.longsafe_aeb.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_aeb.prm_tgt.obj_data = obstacle_data_[cbnao_obj_index];

    // long_safe_out_.longsafe_aeb.prm_tgt.obj.match_conf = 5;

    long_safe_out_.longsafe_fcw.prm_tgt.obj = *obs_list[cbnao_obj_index];
    long_safe_out_.longsafe_fcw.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_fcw.prm_tgt.obj_data = obstacle_data_[cbnao_obj_index];
    //    if (obs_list[cbnao_obj_index].lat_vel > 0) {
    //        long_safe_out_.longsafe_aeb.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    //        long_safe_out_.longsafe_fcw.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    //    } else {
    //        long_safe_out_.longsafe_aeb.prm_tgt.obj.motion_type = ObjectMotionType::LEFT_STRAIGHT_CROSS;
    //        long_safe_out_.longsafe_fcw.prm_tgt.obj.motion_type = ObjectMotionType::LEFT_STRAIGHT_CROSS;
    //    }
    // long_safe_out_.longsafe_fcw.prm_tgt.obj.match_conf = 5;
}

void AsLongSafe::UpdateLongSafeOutForCpfao(const active_safety::AsObstacleList &obs_list) {
    // // version
    ++long_safe_out_.longsafe_roll_cnt;
    long_safe_out_.longsafe_major_version = long_safe_cal_.k_longsafe_major_version;
    long_safe_out_.longsafe_minor_version = long_safe_cal_.k_longsafe_minor_version;
    long_safe_out_.longsafe_aeb.prm_tgt.obj = *obs_list[cpfao_obj_index];
    long_safe_out_.longsafe_aeb.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_aeb.prm_tgt.obj_data = obstacle_data_[cpfao_obj_index];

    // long_safe_out_.longsafe_aeb.prm_tgt.obj.match_conf = 5;

    long_safe_out_.longsafe_fcw.prm_tgt.obj = *obs_list[cpfao_obj_index];
    long_safe_out_.longsafe_fcw.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_fcw.prm_tgt.obj_data = obstacle_data_[cpfao_obj_index];
    //    if (obs_list[cpfao_obj_index].lat_vel > 0) {
    //        long_safe_out_.longsafe_aeb.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    //        long_safe_out_.longsafe_fcw.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    //    } else {
    //        long_safe_out_.longsafe_aeb.prm_tgt.obj.motion_type = ObjectMotionType::LEFT_STRAIGHT_CROSS;
    //        long_safe_out_.longsafe_fcw.prm_tgt.obj.motion_type = ObjectMotionType::LEFT_STRAIGHT_CROSS;
    //    }
    // long_safe_out_.longsafe_fcw.prm_tgt.obj.match_conf = 5;
}
void AsLongSafe::UpdateLongSafeOutForStrictCpnco(const active_safety::AsObstacleList &obs_list) {
    // // version
    int obj_id = strict_cpnco_obj_idx - 1;
    ++long_safe_out_.longsafe_roll_cnt;
    long_safe_out_.longsafe_major_version = long_safe_cal_.k_longsafe_major_version;
    long_safe_out_.longsafe_minor_version = long_safe_cal_.k_longsafe_minor_version;
    long_safe_out_.longsafe_aeb.prm_tgt.obj = *obs_list[obj_id];
    long_safe_out_.longsafe_aeb.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_aeb.prm_tgt.obj_data = obstacle_data_[obj_id];

    long_safe_out_.longsafe_fcw.prm_tgt.obj = *obs_list[obj_id];
    long_safe_out_.longsafe_fcw.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_fcw.prm_tgt.obj_data = obstacle_data_[obj_id];
    //    long_safe_out_.longsafe_aeb.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    //    long_safe_out_.longsafe_fcw.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    // long_safe_out_.longsafe_aeb.prm_tgt.obj.match_conf = 5;
    // long_safe_out_.longsafe_fcw.prm_tgt.obj.match_conf = 5;
}

void AsLongSafe::UpdateLongSafeOutForStrictScp(const active_safety::AsObstacleList &obs_list) {
    // // version
    int obj_id = strict_scp_obj_idx - 1;
    ++long_safe_out_.longsafe_roll_cnt;
    long_safe_out_.longsafe_major_version = long_safe_cal_.k_longsafe_major_version;
    long_safe_out_.longsafe_minor_version = long_safe_cal_.k_longsafe_minor_version;
    long_safe_out_.longsafe_aeb.prm_tgt.obj = *obs_list[obj_id];
    long_safe_out_.longsafe_aeb.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_aeb.prm_tgt.obj_data = obstacle_data_[obj_id];

    // long_safe_out_.longsafe_aeb.prm_tgt.obj.match_conf = 5;

    long_safe_out_.longsafe_fcw.prm_tgt.obj = *obs_list[obj_id];
    long_safe_out_.longsafe_fcw.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_fcw.prm_tgt.obj_data = obstacle_data_[obj_id];

    //    if (obs_list[obj_id].lat_vel > 0) {
    //        long_safe_out_.longsafe_aeb.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    //        long_safe_out_.longsafe_fcw.prm_tgt.obj.motion_type = ObjectMotionType::RIGHT_STRAIGHT_CROSS;
    //    } else {
    //        long_safe_out_.longsafe_aeb.prm_tgt.obj.motion_type = ObjectMotionType::LEFT_STRAIGHT_CROSS;
    //        long_safe_out_.longsafe_fcw.prm_tgt.obj.motion_type = ObjectMotionType::LEFT_STRAIGHT_CROSS;
    //    }
    // long_safe_out_.longsafe_fcw.prm_tgt.obj.match_conf = 5;
}
void AsLongSafe::UpdateLongSafeOutForCstaRn(const active_safety::AsObstacleList &obs_list) {
    // // version
    ++long_safe_out_.longsafe_roll_cnt;
    long_safe_out_.longsafe_major_version = long_safe_cal_.k_longsafe_major_version;
    long_safe_out_.longsafe_minor_version = long_safe_cal_.k_longsafe_minor_version;
    long_safe_out_.longsafe_aeb.prm_tgt.obj = *obs_list[csta_rn_obj_index];
    long_safe_out_.longsafe_aeb.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_aeb.prm_tgt.obj_data = obstacle_data_[csta_rn_obj_index];

    //  //long_safe_out_.longsafe_aeb.prm_tgt.obj.match_conf = 5;

    long_safe_out_.longsafe_fcw.prm_tgt.obj = *obs_list[csta_rn_obj_index];
    long_safe_out_.longsafe_fcw.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_fcw.prm_tgt.obj_data = obstacle_data_[csta_rn_obj_index];

    // long_safe_out_.longsafe_fcw.prm_tgt.obj.match_conf = 5;
}
void AsLongSafe::UpdateLongSafeOutForCptal(const active_safety::AsObstacleList &obs_list) {
    ++long_safe_out_.longsafe_roll_cnt;
    long_safe_out_.longsafe_major_version = long_safe_cal_.k_longsafe_major_version;
    long_safe_out_.longsafe_minor_version = long_safe_cal_.k_longsafe_minor_version;
    long_safe_out_.longsafe_aeb.prm_tgt.obj = *obs_list[cpta_l_obj_index];
    long_safe_out_.longsafe_aeb.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_aeb.prm_tgt.obj_data = obstacle_data_[cpta_l_obj_index];

    // long_safe_out_.longsafe_aeb.prm_tgt.obj.match_conf = 5;

    long_safe_out_.longsafe_fcw.prm_tgt.obj = *obs_list[cpta_l_obj_index];
    long_safe_out_.longsafe_fcw.prm_tgt.obj.status = active_safety::TrackStatus::UPDATED;
    long_safe_out_.longsafe_fcw.prm_tgt.obj_data = obstacle_data_[cpta_l_obj_index];

    // long_safe_out_.longsafe_fcw.prm_tgt.obj.match_conf = 5;
}
void AsLongSafe::UpdateLongSafeOut(const AsSingleThreatAssessor &ass) {
    // // version
    ++long_safe_out_.longsafe_roll_cnt;
    long_safe_out_.longsafe_major_version = long_safe_cal_.k_longsafe_major_version;
    long_safe_out_.longsafe_minor_version = long_safe_cal_.k_longsafe_minor_version;

    long_safe_out_.longsafe_aeb.prm_tgt = ass.GetIntvPrimData().prim_tgt;
    long_safe_out_.longsafe_fcw.prm_tgt = ass.GetWarnPrimData().prim_tgt;
}

void AsLongSafe::GetLongSafeOut(AsLongSafeOut &tap_out, const AsSocietyScene &society_scene) {
    ConvertLongSafeToTapOut(long_safe_out_.longsafe_aeb, tap_out.longsafe_aeb, true);
    ConvertLongSafeToTapOut(long_safe_out_.longsafe_fcw, tap_out.longsafe_fcw, false);
    tap_out.longsafe_scenario.resv1 = society_scene.GetDisableJustStartValid();
    tap_out.longsafe_scenario.resv2 = 0;
    tap_out.longsafe_scenario.obj_evaluator = object_evaluator.GetAsScenarioDisc();
    tap_out.longsafe_roll_cnt = long_safe_out_.longsafe_roll_cnt;
    tap_out.longsafe_major_version = long_safe_out_.longsafe_major_version;
    tap_out.longsafe_minor_version = long_safe_out_.longsafe_minor_version;
}

void AsLongSafe::ConvertLongSafeToTapOut(const AsLgSafeTgt &long_safe_out, AsLongSafeObject &tap_obj, bool isLongPredTime) {
    if (long_safe_out.prm_tgt.obj.fus_trkID <= 0) {
        tap_obj = AsLongSafeObject{};
        return;
    }
    tap_obj.index = long_safe_out.prm_tgt.obj.track_id;
    tap_obj.status = (uint8_t)long_safe_out.prm_tgt.obj.status;
    tap_obj.age = long_safe_out.prm_tgt.obj.age;
    tap_obj.vis_trkId = long_safe_out.prm_tgt.obj.vis_trkID;
    tap_obj.fus_trkId = long_safe_out.prm_tgt.obj.fus_trkID;
    tap_obj.object_class = (int32_t)long_safe_out.prm_tgt.obj.object_class;
    tap_obj.detection_sensor = (int32_t)long_safe_out.prm_tgt.obj.fusion_source;
    tap_obj.long_posn = long_safe_out.prm_tgt.obj.long_posn - vse_.host_dist_to_front;
    tap_obj.lat_posn = long_safe_out.prm_tgt.obj.lat_posn;
    tap_obj.heading = long_safe_out.prm_tgt.obj.heading;
    tap_obj.speed = long_safe_out.prm_tgt.obj.speed;
    tap_obj.lat_vel = long_safe_out.prm_tgt.obj.lat_vel;
    tap_obj.long_vel = long_safe_out.prm_tgt.obj.long_vel;
    tap_obj.lat_accel = long_safe_out.prm_tgt.obj.lat_accel;
    tap_obj.long_accel = long_safe_out.prm_tgt.obj.long_accel;
    tap_obj.ttc = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().ttr;
    tap_obj.xolc = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().xolc;
    tap_obj.lat_est = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().lat_est;
    tap_obj.accel_lat_req = long_safe_out.prm_tgt.a_lat_req;
    tap_obj.accel_lgt_req = long_safe_out.prm_tgt.a_lgt_req;
    tap_obj.length = long_safe_out.prm_tgt.obj.length;
    tap_obj.width = long_safe_out.prm_tgt.obj.width;
    if (isLongPredTime) {
        tap_obj.offs_lgt_pred = long_safe_out.prm_tgt.obj_data.GetSafeMarginEvalData().predict_offset.offs_lgt_long_pred;
        tap_obj.offs_lat_pred = long_safe_out.prm_tgt.obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_long_pred;
        tap_obj.para_veh_pred = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().motion_type.para_veh_long_pred;
        tap_obj.pred_long_accel = long_safe_out.prm_tgt.obj_data.GetInpathData().GetResultData().inpath_long_pred.a_lgt;
        tap_obj.pred_lat_accel = long_safe_out.prm_tgt.obj_data.GetInpathData().GetResultData().inpath_long_pred.a_lat;
        tap_obj.pred_accel = long_safe_out.prm_tgt.obj_data.GetInpathData().GetResultData().inpath_long_pred.a;
        tap_obj.pred_cvt = long_safe_out.prm_tgt.obj_data.GetInpathData().GetResultData().inpath_long_pred.curv;
        tap_obj.inpath_current = long_safe_out.prm_tgt.obj_data.GetInpathData().GetCurrentInPathData().inpath_long_pred.in_path;
        tap_obj.inpath_predict = long_safe_out.prm_tgt.obj_data.GetInpathData().GetPredictInPathData().inpath_long_pred.in_path;
    } else {
        tap_obj.offs_lgt_pred = long_safe_out.prm_tgt.obj_data.GetSafeMarginEvalData().predict_offset.offs_lgt_short_pred;
        tap_obj.offs_lat_pred = long_safe_out.prm_tgt.obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_short_pred;
        tap_obj.para_veh_pred = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().motion_type.para_veh_short_pred;
        tap_obj.pred_long_accel = long_safe_out.prm_tgt.obj_data.GetInpathData().GetResultData().inpath_short_pred.a_lgt;
        tap_obj.pred_lat_accel = long_safe_out.prm_tgt.obj_data.GetInpathData().GetResultData().inpath_short_pred.a_lat;
        tap_obj.pred_accel = long_safe_out.prm_tgt.obj_data.GetInpathData().GetResultData().inpath_short_pred.a;
        tap_obj.pred_cvt = long_safe_out.prm_tgt.obj_data.GetInpathData().GetResultData().inpath_short_pred.curv;
        tap_obj.inpath_current = long_safe_out.prm_tgt.obj_data.GetInpathData().GetCurrentInPathData().inpath_short_pred.in_path;
        tap_obj.inpath_predict = long_safe_out.prm_tgt.obj_data.GetInpathData().GetPredictInPathData().inpath_short_pred.in_path;
    }

    tap_obj.offs_lat_manoeuvre = long_safe_out.prm_tgt.obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_manoeuvre;
    tap_obj.offs_lat_in_path_primary_target = long_safe_out.prm_tgt.obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_in_path_primary_target;
    tap_obj.offs_lat_in_path_close_edge = long_safe_out.prm_tgt.obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_in_path_close_edge;
    tap_obj.offs_lat_in_path_far_edge = long_safe_out.prm_tgt.obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_in_path_far_edge;
    tap_obj.offs_lat_intersection = long_safe_out.prm_tgt.obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_intersection;
    tap_obj.offs_lat_multi_target = long_safe_out.prm_tgt.obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_multi_target;
    tap_obj.abs_heading = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().motion_type.abs_heading;
    tap_obj.length_side_lat = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().bounding_box.length_side_lat;
    tap_obj.length_side_lgt = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().bounding_box.length_side_lgt;
    tap_obj.sin_rotation = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().bounding_box.sin_rotation;
    tap_obj.cos_rotation = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().bounding_box.cos_rotation;
    //  tap_obj.match_conf = long_safe_out.prm_tgt.obj.match_conf;
    //  tap_obj.motion_type = (uint8_t)long_safe_out.prm_tgt.obj.motion_type;
    tap_obj.stationary = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().motion_type.stationary;
    tap_obj.moving_oncoming = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().motion_type.moving_oncoming;
    tap_obj.obs_is_vehicle = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().motion_type.obs_is_vehicle;
    tap_obj.obs_is_motor_veh = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().motion_type.obs_is_motor_veh;
    tap_obj.curved_motion = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().motion_type.curved_motion;
    tap_obj.side_closest = long_safe_out.prm_tgt.obj_data.GetCollisionEvalData().motion_type.side_closest;
}

} // namespace tap
} // namespace senseAD
