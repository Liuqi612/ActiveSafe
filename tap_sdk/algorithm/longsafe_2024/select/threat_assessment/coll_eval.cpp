/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#include "coll_eval.h"
#include "longsafe_cal.h"

#include <array>
namespace senseAD {
namespace tap {
AsObsCollEvaCal           colleva_param;
SafetyObsColliDetecConfig colli_detec_param;
CollisionEvaluator::CollisionEvaluator() {
}

CollisionEvaluator::~CollisionEvaluator() {
}

void CollisionEvaluator::ProcessCollisionEvaluator(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, const AsEgoPath &curv_path,
                                                   const AsSocietyScene &society_scene) {
    AsVseOut egoInfo = vse_out;
    if (egoInfo.aeb_active) {
        egoInfo.long_accel = 0.f;
    }
    CalMotionType(egoInfo, obj);
    CalBoundingBox(egoInfo, obj);
    if (fabs(vse_out.yawrate) > 0.2f) {
        CalTTRAndTTMForTurnScene(curv_path, egoInfo, obj, society_scene);
        ttr = seprate_axle_ttc;
        ttm = seprate_axle_ttm;
    } else {
        CalTTRAndTTM(egoInfo, obj);
        ttr = long_ttc;
        ttm = long_ttm;
    }
    CalLatEstimedInfo(obj, egoInfo);
    // std::cout << "TTC:" << ttr << " Xolc:" << xolc << " LatEst:" << lat_est
    //           << std::endl;
}

void CollisionEvaluator::Clear() {
    motion_type.stationary            = false;
    motion_type.moving_oncoming       = false;
    motion_type.para_veh_long_pred    = false;
    motion_type.para_veh_short_pred   = false;
    motion_type.obs_is_vehicle        = false;
    motion_type.obs_is_motor_veh      = false;
    motion_type.curved_motion         = false;
    motion_type.side_closest          = false;
    motion_type.abs_heading           = 0.0f;
    bounding_box.length_side_lgt      = 0.0f;
    bounding_box.length_side_lat      = 0.0f;
    bounding_box.sin_rotation         = 0.0f;
    bounding_box.cos_rotation         = 0.0f;
    md_front_closest.v_rel            = 0.0f;
    md_front_closest.v_rel_host_sta   = 0.0f;
    md_front_closest.v_rel_object_sta = 0.0f;
    md_front_closest.a_rel            = 0.0f;
    md_front_closest.a_rel_host_sta   = 0.0f;
    md_front_closest.a_rel_object_sta = 0.0f;
    md_rear_closest.v_rel             = 0.0f;
    md_rear_closest.v_rel_host_sta    = 0.0f;
    md_rear_closest.v_rel_object_sta  = 0.0f;
    md_rear_closest.a_rel             = 0.0f;
    md_rear_closest.a_rel_host_sta    = 0.0f;
    md_rear_closest.a_rel_object_sta  = 0.0f;
    ed_front.close_edge_dis           = 0.0f;
    ed_front.middle_edge_dis          = 0.0f;
    ed_front.far_edge_dis             = 0.0f;
    ed_rear.close_edge_dis            = 0.0f;
    ed_rear.middle_edge_dis           = 0.0f;
    ed_rear.far_edge_dis              = 0.0f;
    side_near                         = AsObstacleSideNear::AS_OBS_SD_UNKNOWN;
    seprate_axle_ttc                  = 100.0f;
    seprate_axle_ttm                  = 100.0f;
    long_ttc                          = 100.0f;
    long_ttm                          = 100.0f;
    ttm                               = 100.0;
    ttr                               = 100.0;
    xolc                              = 20.0f;
    lat_est                           = 20.0f;
}

void CollisionEvaluator::CalTTRAndTTM(const AsVseOut &vse_out, const active_safety::AsObstacle &obj) {
    CalMotionData(vse_out, obj);
    CalEdgeDistanceData(vse_out, obj);
    StoppingData stopping_data = CalcStopDataForTTI(obj, vse_out);

    bool is_front_closest = CleckIsFrontClosest(obj);

    // Calculate TTR
    TTIInputData ttr_input;
    TTIData      ttr_data;
    bool         ttr_solution_exist = false;
    float        ttr_tti            = 0.0f;
    ttr_input.is_front_closest      = is_front_closest;
    ttr_input.md_front_closest      = md_front_closest;
    ttr_input.md_rear_closest       = md_rear_closest;
    ttr_input.edge_dis_front        = ed_front.close_edge_dis;
    ttr_input.edge_dis_rear         = ed_rear.close_edge_dis;
    ttr_input.ego_stop_dis          = stopping_data.host_delta_pos;
    ttr_input.veh_stop_dis          = stopping_data.obj_delta_pos;
    CalTTI(ttr_input, ttr_data);
    ttr_solution_exist = SelectTTI(ttr_data, stopping_data.host_stop_time, stopping_data.obj_stop_time, ttr_tti);

    // Calculate TTM
    TTIInputData ttm_input;
    TTIData      ttm_data;
    bool         ttm_solution_exist = false;
    float        ttm_tti            = 0.0f;
    ttm_input.is_front_closest      = is_front_closest;
    ttm_input.md_front_closest      = md_front_closest;
    ttm_input.md_rear_closest       = md_rear_closest;
    ttm_input.edge_dis_front        = ed_front.middle_edge_dis;
    ttm_input.edge_dis_rear         = ed_rear.middle_edge_dis;
    ttm_input.ego_stop_dis          = stopping_data.host_delta_pos;
    ttm_input.veh_stop_dis          = stopping_data.obj_delta_pos;
    CalTTI(ttm_input, ttm_data);
    ttm_solution_exist = SelectTTI(ttm_data, stopping_data.host_stop_time, stopping_data.obj_stop_time, ttm_tti);

    // Correct TTR
    float correct_ttr = 0.0f;
    if (true == ttr_solution_exist) {
        correct_ttr = ttr_tti;
    } else {
        if (((ed_front.close_edge_dis < 0.0f) ^ (ed_front.far_edge_dis < 0.0f)) ^ (ttm_tti < 0.0f)) {
            correct_ttr = colleva_param.k_tti_low;
        } else {
            correct_ttr = colleva_param.k_tti_uppr;
        }
    }

    // Modify TTR
    float default_ttr = 0.0f;
    if ((ed_front.close_edge_dis < 0.0f) ^ (ed_front.far_edge_dis < 0.0f)) {
        default_ttr = colleva_param.k_tti_low;
    } else {
        default_ttr = colleva_param.k_tti_uppr;
    }
    if ((fabsf(md_front_closest.v_rel) < 0.01f) && (fabsf(md_front_closest.a_rel) < 0.01f)) {
        correct_ttr = default_ttr;
    }
    if (correct_ttr < colleva_param.k_tti_low) {
        correct_ttr = colleva_param.k_tti_low;
    }
    if (correct_ttr > colleva_param.k_tti_uppr) {
        correct_ttr = colleva_param.k_tti_uppr;
    }

    // Correct TTM
    float correct_ttm = 0.0f;
    if (true == ttm_solution_exist) {
        correct_ttm = ttm_tti;
    } else {
        if (((ed_front.close_edge_dis < 0.0f) ^ (ed_front.far_edge_dis < 0.0f)) ^ (ttr_tti < 0.0f)) {
            correct_ttm = colleva_param.k_tti_low;
        } else {
            correct_ttm = colleva_param.k_tti_uppr;
        }
    }
    if ((fabsf(md_front_closest.v_rel) < 0.01f) && (fabsf(md_front_closest.a_rel) < 0.01f)) {
        correct_ttm = colleva_param.k_tti_uppr;
    }
    if (correct_ttm < colleva_param.k_tti_low) {
        correct_ttm = colleva_param.k_tti_low;
    }
    if (correct_ttm > colleva_param.k_tti_uppr) {
        correct_ttm = colleva_param.k_tti_uppr;
    }

    long_ttc = correct_ttr;
    long_ttm = correct_ttm;
}

void CollisionEvaluator::CalLatEstimedInfo(const active_safety::AsObstacle &obj, const AsVseOut &vse_out) {
    float squrd_pos = obj.long_posn * obj.long_posn;
    // if(motion_type.obs_is_vehicle)
    xolc = obj.lat_posn - 0.5f * vse_out.rear_curvature * squrd_pos + 0.16667f * vse_out.rear_curvaturerate * squrd_pos * obj.long_posn;
    xolc = math::Clamp(xolc, -20.0f, 20.0f);
    float obj_lat_moving_dist = ttr * obj.lat_vel;

    lat_est = xolc + obj_lat_moving_dist;
    lat_est = math::Clamp(lat_est, -20.0f, 20.0f);
}

void CollisionEvaluator::CalTTRAndTTMForTurnScene(const AsEgoPath &curv_path, const AsVseOut &vse_out, const active_safety::AsObstacle &obj,
                                                  const AsSocietyScene &society_scene) {
    (void)(vse_out);
    float width_offset  = 0;
    float length_offset = 0;
    bool  turn_left     = (vse_out.rear_curvature_radius < colli_detec_param.k_turn_left_radius) && (vse_out.rear_curvature_radius > 0);
    bool  turn_right    = (vse_out.rear_curvature_radius > colli_detec_param.k_turn_right_radius) && (vse_out.rear_curvature_radius < 0);
    if (vse_out.aeb_active) {
        if ((obj.object_class == active_safety::ObjectClass::PEDESTRIAN) || (obj.object_class == active_safety::ObjectClass::MOTORCYCLE) ||
            (obj.object_class == active_safety::ObjectClass::BICYCLE) || (obj.object_class == active_safety::ObjectClass::ESCOOTER)) {
            bounding_box.length_side_lgt = fmax(bounding_box.length_side_lgt, 2);
            bounding_box.length_side_lat = fmax(bounding_box.length_side_lat, 2);
        } else if (obj.object_class == active_safety::ObjectClass::CAR) {

            bounding_box.length_side_lgt = bounding_box.length_side_lgt + 2;
            bounding_box.length_side_lat = bounding_box.length_side_lat + 2;
        } else {
        }
    } else if (society_scene.GetTurnConstandSpdFlag()) {
        switch (obj.object_class) {
            case active_safety::ObjectClass::CAR:
                // ccft
                if ((obj.long_vel < colli_detec_param.k_ccft_oncoming_spd_max) && turn_left)
                    width_offset = LookUpTable::LookupTable2D(colli_detec_param.ccft_ego_speed, colli_detec_param.ccft_obj_speed,
                                                              colli_detec_param.ccft_width_offset, vse_out.speed, fabs(obj.long_vel));
                length_offset = LookUpTable::LookupTable2D(colli_detec_param.ccft_ego_speed, colli_detec_param.ccft_obj_speed,
                                                           colli_detec_param.ccft_length_offset, vse_out.speed, fabs(obj.long_vel));
                bounding_box.length_side_lat += width_offset;
                bounding_box.length_side_lgt += length_offset;

                break;

            // Check if the bike is fast enough
            case active_safety::ObjectClass::ESCOOTER:
            case active_safety::ObjectClass::BICYCLE: {
                // csta
                if ((obj.long_vel > colli_detec_param.k_csta_fromself_spd_max) && turn_right) {
                    width_offset  = LookUpTable::LookupTable2D(colli_detec_param.csta_ego_speed, colli_detec_param.csta_obj_speed,
                                                              colli_detec_param.csta_rn_width_offset, vse_out.speed, fabs(obj.long_vel));
                    length_offset = LookUpTable::LookupTable2D(colli_detec_param.csta_ego_speed, colli_detec_param.csta_obj_speed,
                                                               colli_detec_param.csta_rn_length_offset, vse_out.speed, fabs(obj.long_vel));
                } else if ((obj.long_vel < colli_detec_param.k_csta_oncoming_spd_max) && turn_left) {
                    width_offset  = LookUpTable::LookupTable2D(colli_detec_param.csta_ego_speed, colli_detec_param.csta_obj_speed,
                                                              colli_detec_param.csta_ln_width_offset, vse_out.speed, fabs(obj.long_vel));
                    length_offset = LookUpTable::LookupTable2D(colli_detec_param.csta_ego_speed, colli_detec_param.csta_obj_speed,
                                                               colli_detec_param.csta_ln_length_offset, vse_out.speed, fabs(obj.long_vel));
                }

                bounding_box.length_side_lat += width_offset;
                bounding_box.length_side_lgt += length_offset;
            }
            case active_safety::ObjectClass::PEDESTRIAN:
                // cpta
                if ((obj.long_vel < colli_detec_param.k_cpta_oncoming_spd_max) && turn_left) {
                    width_offset = LookUpTable::LookupTable2D(colli_detec_param.cpta_ego_speed, colli_detec_param.cpta_obj_speed,
                                                              colli_detec_param.cpta_ln_width_offset, vse_out.speed, fabs(obj.long_vel));

                    length_offset = LookUpTable::LookupTable2D(colli_detec_param.cpta_ego_speed, colli_detec_param.cpta_obj_speed,
                                                               colli_detec_param.cpta_ln_length_offset, vse_out.speed, fabs(obj.long_vel));
                } else if ((obj.long_vel > colli_detec_param.k_cpta_fromself_spd_max) && turn_left) {
                    width_offset = LookUpTable::LookupTable2D(colli_detec_param.cpta_ego_speed, colli_detec_param.cpta_obj_speed,
                                                              colli_detec_param.cpta_lf_width_offset, vse_out.speed, fabs(obj.long_vel));

                    length_offset = LookUpTable::LookupTable2D(colli_detec_param.cpta_ego_speed, colli_detec_param.cpta_obj_speed,
                                                               colli_detec_param.cpta_lf_length_offset, vse_out.speed, fabs(obj.long_vel));
                } else if ((obj.long_vel < colli_detec_param.k_cpta_oncoming_spd_max) && turn_right) {
                    width_offset = LookUpTable::LookupTable2D(colli_detec_param.cpta_ego_speed, colli_detec_param.cpta_obj_speed,
                                                              colli_detec_param.cpta_lf_width_offset, vse_out.speed, fabs(obj.long_vel));

                    length_offset = LookUpTable::LookupTable2D(colli_detec_param.cpta_ego_speed, colli_detec_param.cpta_obj_speed,
                                                               colli_detec_param.cpta_lf_length_offset, vse_out.speed, fabs(obj.long_vel));
                }

                bounding_box.length_side_lat += width_offset;
                bounding_box.length_side_lgt += length_offset;
            case active_safety::ObjectClass::ANIMAL:
            case active_safety::ObjectClass::GENOBJ:
            case active_safety::ObjectClass::UNDETERMINED:
            case active_safety::ObjectClass::GOD: {
                break;
            }

            default: {
                break;
            }
        }
    }
    Box2D stationary_target_rect;
    if (motion_type.stationary) {
        stationary_target_rect.BuildFromCenter(obj.long_posn, obj.lat_posn, obj.heading, bounding_box.length_side_lgt, bounding_box.length_side_lat);
    }

    constexpr int kMaxSteps = 150; // 3.0s / 0.02s
    for (int step = 0; step <= kMaxSteps; ++step) {
        const float iterTm = step * 0.02f;

        // const auto &hostState = curv_path.GetHostState(iterTm);
        auto hostBox = curv_path.GetHostBoudingBox(iterTm);
        hostBox.ComputeAABB();

        Box2D targetRect;
        if (!motion_type.stationary) {
            EgoMotionStateAtTime targetState;
            math::PredictMotionWithStop(obj.long_posn, obj.long_vel, obj.long_accel, iterTm, targetState.long_pos, targetState.long_vel,
                                            targetState.long_accel);

            math::PredictMotionWithStop(obj.lat_posn, obj.lat_vel, obj.lat_accel, iterTm, targetState.lat_pos, targetState.lat_vel,
                                            targetState.lat_accel);
            targetState.heading_angle = (obj.speed > 0.1f) ? std::atan2(obj.lat_vel, obj.long_vel) : obj.heading;
            targetRect.BuildFromCenter(targetState.long_pos, targetState.lat_pos, targetState.heading_angle, bounding_box.length_side_lgt,
                                       bounding_box.length_side_lat);
        } else {
            targetRect = stationary_target_rect;
        }
        if (hostBox.QuickRejectTest(targetRect)) {
            continue;
        }

        if (hostBox.IsCollisionSAT(targetRect)) {
            // std::cout << hostBox.left_bottom << " " << hostBox.left_top << "
            // "
            //           << hostBox.right_top << " " << hostBox.right_bottom <<
            //           " "
            //           << targetRect.left_bottom << " " << targetRect.left_top
            //           << "
            //           "
            //           << targetRect.right_top << " " <<
            //           targetRect.right_bottom
            //           << std::endl;
            seprate_axle_ttm = iterTm;
            seprate_axle_ttc = iterTm;
            // std::cout << vse_out.speed << ":" << seprate_axle_ttc << ", "
            //           << seprate_axle_ttm << "(" << obj.lat_posn << ","
            //           << obj.long_posn << ")" << std::endl;
            break;
        }
    }
}

void CollisionEvaluator::CalBoundingBox(const AsVseOut &vse_out, const active_safety::AsObstacle &obj) {
    bounding_box.length_side_lgt = CalLenLgt(vse_out, obj);
    bounding_box.length_side_lat = CalLenLat(obj);
    bounding_box.sin_rotation    = CalSinRotation(obj);
    bounding_box.cos_rotation    = CalCosRotation(obj);
}

void CollisionEvaluator::CalMotionType(const AsVseOut &vse_out, const active_safety::AsObstacle &obj) {
    CheckVehicle(obj);
    CheckMotorVehicle(obj);
    CheckAbsHeading(obj);
    CheckStationary(obj);
    CheckOncoming(obj);
    // CheckParallellVehicleLongPred(obj);
    // CheckParallellVehicleShortPred(obj);
    CheckCurvedMotion(obj);
    CheckSideIsClosest(vse_out, obj);
}

void CollisionEvaluator::CalMotionData(const AsVseOut &vse_out, const active_safety::AsObstacle &obj) {
    md_front_closest.v_rel            = obj.long_vel - vse_out.vcs_long_vel;
    md_front_closest.v_rel_host_sta   = obj.long_vel;
    md_front_closest.v_rel_object_sta = -vse_out.vcs_long_vel;
    md_front_closest.a_rel            = obj.long_accel - vse_out.long_accel;
    md_front_closest.a_rel_host_sta   = obj.long_accel;
    md_front_closest.a_rel_object_sta = -vse_out.long_accel;

    md_rear_closest.v_rel            = -(obj.long_vel - vse_out.vcs_long_vel);
    md_rear_closest.v_rel_host_sta   = -(obj.long_vel);
    md_rear_closest.v_rel_object_sta = vse_out.vcs_long_vel;
    md_rear_closest.a_rel            = -(obj.long_accel - vse_out.long_accel);
    md_rear_closest.a_rel_host_sta   = -obj.long_accel;
    md_rear_closest.a_rel_object_sta = vse_out.long_accel;
}
void CollisionEvaluator::CalEdgeDistanceData(const AsVseOut &vse_out, const active_safety::AsObstacle &obj) {
    ed_front.close_edge_dis  = obj.long_posn - vse_out.host_dist_to_front;
    ed_front.middle_edge_dis = ed_front.close_edge_dis + 0.2 * vse_out.host_length;
    ed_front.far_edge_dis    = ed_front.middle_edge_dis;
    ed_rear.close_edge_dis   = -ed_front.far_edge_dis;
    ed_rear.middle_edge_dis  = -ed_front.middle_edge_dis;
    ed_rear.far_edge_dis     = -ed_front.close_edge_dis;
}

StoppingData CollisionEvaluator::CalcStopDataForTTI(const active_safety::AsObstacle &obj, const AsVseOut &vse_out) {
    StoppingData stop_data;
    stop_data.host_stop_time = math::Clamp(math::SafeDivide(vse_out.vcs_long_vel, -vse_out.long_accel), -100000.0f, 100000.0f);
    stop_data.host_delta_pos = math::PredictPosition(0.0f, vse_out.vcs_long_vel, vse_out.long_accel, stop_data.host_stop_time);
    if (motion_type.stationary) {
        stop_data.obj_stop_time = 0.01f;
        stop_data.obj_delta_pos = 0.0f;
    } else {
        stop_data.obj_stop_time = math::Clamp(math::SafeDivide(obj.long_vel, -obj.long_accel), -100000.0f, 100000.0f);
        stop_data.obj_delta_pos = math::PredictPosition(0.0f, obj.long_vel, obj.long_accel, stop_data.obj_stop_time);
    }
    return stop_data;
}

bool CollisionEvaluator::CleckIsFrontClosest(const active_safety::AsObstacle &obj) {
    bool front_closest = false;
    if ((md_front_closest.v_rel < 0.0f) || ((fabsf(md_front_closest.v_rel) < 0.01f) && (obj.long_posn > 0.0f))) {
        front_closest = true;
    } else {
        front_closest = false;
    }
    return front_closest;
}

void CollisionEvaluator::CalTTI(const TTIInputData &input_data, TTIData &tti_data) {
    TTIMotionData tti_motion_data;
    SelectMotionData(input_data.is_front_closest, input_data.md_front_closest, input_data.md_rear_closest, input_data.edge_dis_front,
                     input_data.edge_dis_rear, tti_motion_data);

    // Calculate TTI for vse_out vehicle and object moving
    float moving_delta_pos   = 0.0f;
    tti_data.moving_sol_exit = CalTTIResult(tti_motion_data.tti_moving_para, moving_delta_pos, tti_data.moving_tti);

    // Calculate TTI for vse_out vehicle stopped
    tti_data.ego_stop_sol_exit = CalTTIResult(tti_motion_data.tti_hoststop_para, -input_data.ego_stop_dis, tti_data.ego_stop_tti);

    // Calculate TTI for object stopped
    tti_data.veh_stop_sol_exit = CalTTIResult(tti_motion_data.tti_objstop_para, input_data.veh_stop_dis, tti_data.veh_stop_tti);
}

bool CollisionEvaluator::SelectTTI(const TTIData &tti_data, float ego_stop_time, float veh_stop_time, float &tti) {
    // Ego vehicle will stop
    bool ego_will_stop = false;
    if ((tti_data.ego_stop_tti > ego_stop_time) && (ego_stop_time > 0.0f) && (ego_stop_time < 3.0f) &&
        (!((ego_stop_time > tti_data.moving_tti) && (tti_data.moving_tti > 0.0f)))) {
        ego_will_stop = true;
    }

    // Object will stop
    bool veh_will_stop = false;
    if ((tti_data.veh_stop_tti > veh_stop_time) && (veh_stop_time > 0.0f) && (veh_stop_time < 3.0f) &&
        (!((veh_stop_time > tti_data.moving_tti) && (tti_data.moving_tti > 0.0f)))) {
        veh_will_stop = true;
    }

    bool solutoin_exit = false;
    if (true == ego_will_stop && true == veh_will_stop) {
        if (veh_stop_time < ego_stop_time) {
            solutoin_exit = tti_data.veh_stop_sol_exit;
            tti           = tti_data.veh_stop_tti;
        } else {
            solutoin_exit = tti_data.ego_stop_sol_exit;
            tti           = tti_data.ego_stop_tti;
        }
    } else if (true == ego_will_stop && false == veh_will_stop) {
        solutoin_exit = tti_data.ego_stop_sol_exit;
        tti           = tti_data.ego_stop_tti;
    } else if (false == ego_will_stop && true == veh_will_stop) {
        solutoin_exit = tti_data.veh_stop_sol_exit;
        tti           = tti_data.veh_stop_tti;
    } else {
        solutoin_exit = tti_data.moving_sol_exit;
        tti           = tti_data.moving_tti;
    }

    return solutoin_exit;
}

bool CollisionEvaluator::SelectMotionData(bool host_front_is_closest, MotionData md_front, MotionData md_rear, float ed_front, float ed_rear,
                                          TTIMotionData &output) {
    if (true == host_front_is_closest) {
        output.tti_moving_para.normal_edge_dis = ed_front;
        output.tti_moving_para.normal_v_rel    = md_front.v_rel;
        output.tti_moving_para.normal_a_rel    = md_front.a_rel;

        output.tti_hoststop_para.normal_edge_dis = ed_front;
        output.tti_hoststop_para.normal_v_rel    = md_front.v_rel_host_sta;
        output.tti_hoststop_para.normal_a_rel    = md_front.a_rel_host_sta;

        output.tti_objstop_para.normal_edge_dis = ed_front;
        output.tti_objstop_para.normal_v_rel    = md_front.v_rel_object_sta;
        output.tti_objstop_para.normal_a_rel    = md_front.a_rel_object_sta;

        output.tti_moving_para.alter_edge_dis = ed_rear;
        output.tti_moving_para.alter_v_rel    = md_rear.v_rel;
        output.tti_moving_para.alter_a_rel    = md_rear.a_rel;

        output.tti_hoststop_para.alter_edge_dis = ed_rear;
        output.tti_hoststop_para.alter_v_rel    = md_rear.v_rel_host_sta;
        output.tti_hoststop_para.alter_a_rel    = md_rear.a_rel_host_sta;

        output.tti_objstop_para.alter_edge_dis = ed_rear;
        output.tti_objstop_para.alter_v_rel    = md_rear.v_rel_object_sta;
        output.tti_objstop_para.alter_a_rel    = md_rear.a_rel_object_sta;

    } else {
        output.tti_moving_para.normal_edge_dis = ed_rear;
        output.tti_moving_para.normal_v_rel    = md_rear.v_rel;
        output.tti_moving_para.normal_a_rel    = md_rear.a_rel;

        output.tti_hoststop_para.normal_edge_dis = ed_rear;
        output.tti_hoststop_para.normal_v_rel    = md_rear.v_rel_host_sta;
        output.tti_hoststop_para.normal_a_rel    = md_rear.a_rel_host_sta;

        output.tti_objstop_para.normal_edge_dis = ed_rear;
        output.tti_objstop_para.normal_v_rel    = md_rear.v_rel_object_sta;
        output.tti_objstop_para.normal_a_rel    = md_rear.a_rel_object_sta;

        output.tti_moving_para.alter_edge_dis = ed_front;
        output.tti_moving_para.alter_v_rel    = md_front.v_rel;
        output.tti_moving_para.alter_a_rel    = md_front.a_rel;

        output.tti_hoststop_para.alter_edge_dis = ed_front;
        output.tti_hoststop_para.alter_v_rel    = md_front.v_rel_host_sta;
        output.tti_hoststop_para.alter_a_rel    = md_front.a_rel_host_sta;

        output.tti_objstop_para.alter_edge_dis = ed_front;
        output.tti_objstop_para.alter_v_rel    = md_front.v_rel_object_sta;
        output.tti_objstop_para.alter_a_rel    = md_front.a_rel_object_sta;
    }

    return true;
}
bool CollisionEvaluator::CalTTIResult(TTIDataSel tti_para, float delta_pos, float &tti) {
    bool normal_solution_no_exist = CheckTTISolution(tti_para.normal_edge_dis, tti_para.normal_v_rel, tti_para.normal_a_rel);
    bool alter_solution_no_exist  = CheckTTISolution(tti_para.alter_edge_dis, tti_para.alter_v_rel, tti_para.alter_a_rel);

    bool moving_solution_exist = false;
    if (true == normal_solution_no_exist) {
        if (true == alter_solution_no_exist) {
            tti                   = MAX_TTC_THD;
            moving_solution_exist = false;
        } else {
            tti                   = SolveTTISolution(tti_para.alter_v_rel, tti_para.alter_a_rel, tti_para.alter_edge_dis + delta_pos);
            moving_solution_exist = true;
        }
    } else {
        tti                   = SolveTTISolution(tti_para.normal_v_rel, tti_para.normal_a_rel, tti_para.normal_edge_dis + delta_pos);
        moving_solution_exist = true;
    }

    return moving_solution_exist;
}

bool CollisionEvaluator::CheckTTISolution(float edge_dis, float v_rel, float a_rel) {
    // For normal
    float v2          = powf(v_rel, 2.0f);
    float s           = math::Clamp(math::SafeDivide(v2, 2.0f * a_rel), -100000.0f, 100000.0f);
    bool  below_limit = false;
    if (edge_dis < s) {
        below_limit = true;
    }

    bool no_sln_pos_a_rel = false;
    if (a_rel > 0 && edge_dis > s) {
        no_sln_pos_a_rel = true;
    }

    bool no_sln_neg_a_rel = false;
    if (true == below_limit && a_rel < 0) {
        no_sln_neg_a_rel = true;
    }

    bool no_solution_using_a_rel = false;
    if (no_sln_pos_a_rel || no_sln_neg_a_rel) {
        no_solution_using_a_rel = true;
    }

    bool no_solution = false;
    if (fabs(a_rel) > 0.01f) {
        no_solution = no_solution_using_a_rel;
    } else {
        no_solution = false;
    }

    return no_solution;
}

float CollisionEvaluator::SolveTTISolution(float v_rel, float a_rel, float edge_dis) {
    float a = 0.5f * a_rel;
    float b = v_rel;
    float c = edge_dis;

    bool        solution_found = false;
    const float zero_thr       = 0.000001f;
    float       solution_1     = 0.0f;
    float       solution_2     = 0.0f;
    if (fabsf(a) < zero_thr && fabsf(b) < zero_thr) {
        if (fabsf(c) < zero_thr) {
            solution_found = true;
            solution_1     = 0.0f;
            solution_2     = 0.0f;
        } else {
            solution_found = false;
        }
    } else if (fabsf(a) < zero_thr) {
        solution_found = true;
        solution_1     = -c / b;
        solution_2     = -c / b;
    } else {
        if (4.0f * a * c > powf(b, 2.0f)) {
            solution_found = false;
            solution_1     = 0.0f;
            solution_2     = 0.0f;
        } else {
            solution_found = true;
            solution_1     = (-b + sqrtf(powf(b, 2.0f) - 4.0f * a * c)) / (2.0f * a);
            solution_2     = (-b - sqrtf(powf(b, 2.0f) - 4.0f * a * c)) / (2.0f * a);
        }
    }

    float solution = 0.0f;
    if (true == solution_found) {
        if (a_rel < 0.0f) {
            solution = fmaxf(solution_1, solution_2);
        } else {
            solution = fminf(solution_1, solution_2);
        }
    } else {
        if (edge_dis < 0.0f) {
            solution = -MAX_TTC_THD;
        } else {
            solution = MAX_TTC_THD;
        }
    }
    return solution;
}

float CollisionEvaluator::CalLenLat(const active_safety::AsObstacle &obj) {
    float m_len_lat = 0.0f;
    switch (obj.object_class) {
        case active_safety::ObjectClass::CAR:
        case active_safety::ObjectClass::TRUCK:
        case active_safety::ObjectClass::MOTORCYCLE:
        case active_safety::ObjectClass::UNIDENTIFIED_VEHICLE: {
            m_len_lat = obj.width;
            break;
        }
        // Check if the bike is fast enough
        case active_safety::ObjectClass::ESCOOTER:
        case active_safety::ObjectClass::BICYCLE: {
            if (obj.speed > colleva_param.k_bike_spd_thd) {
                m_len_lat = colleva_param.k_bike_width;
                break;
            } else {
                m_len_lat = 0.01f;
                break;
            }
        }
        case active_safety::ObjectClass::PEDESTRIAN:
        case active_safety::ObjectClass::ANIMAL:
        case active_safety::ObjectClass::GENOBJ:
        case active_safety::ObjectClass::UNDETERMINED: {
            m_len_lat = 0.01f;
            break;
        }
        case active_safety::ObjectClass::GOD: {
            m_len_lat = fmin(obj.width, colleva_param.k_barrier_max_width);
            break;
        }
        default: {
            m_len_lat = 0.0f;
            break;
        }
    }
    return m_len_lat;
}
float CollisionEvaluator::CalLenLgt(const AsVseOut &vse_out, const active_safety::AsObstacle &obj) {
    float m_len_lgt = 0.0f;
    switch (obj.object_class) {
        case active_safety::ObjectClass::CAR: {
            m_len_lgt = colleva_param.k_car_length;
            break;
        }
        case active_safety::ObjectClass::UNIDENTIFIED_VEHICLE: {
            if (true == motion_type.moving_oncoming && true == vse_out.aeb_active) {
                m_len_lgt = colleva_param.k_car_length;
                break;
            } else {
                m_len_lgt = colleva_param.k_veh_unknown_length;
                break;
            }
        }
        case active_safety::ObjectClass::MOTORCYCLE: {
            m_len_lgt = colleva_param.k_motorcycle_length;
            break;
        }
        case active_safety::ObjectClass::ESCOOTER:
        case active_safety::ObjectClass::BICYCLE: {
            if (obj.speed > colleva_param.k_bike_low_thd) {
                m_len_lgt = colleva_param.k_bicycle_length;
                break;
            } else {
                m_len_lgt = 0.01f;
                break;
            }
        }
        case active_safety::ObjectClass::TRUCK: {
            m_len_lgt = (obj.length < m_len_lgt) ? obj.length : colleva_param.k_truck_length;
            break;
        }
        case active_safety::ObjectClass::PEDESTRIAN:
        case active_safety::ObjectClass::ANIMAL:
        case active_safety::ObjectClass::GENOBJ:
        case active_safety::ObjectClass::UNDETERMINED: {
            m_len_lgt = 0.01f;
            break;
        }
        case active_safety::ObjectClass::GOD: {
            m_len_lgt = fmin(obj.length, colleva_param.k_barrier_max_length);
            break;
        }
        default: {
            m_len_lgt = 0.0f;
            break;
        }
    }
    return m_len_lgt;
}

// stationary or movefromself select MapAngToInterval M_PI
// oncoming select MapAngToInterval M_PI/2
float CollisionEvaluator::CalSinRotation(const active_safety::AsObstacle &obj) {
    float m_sin_rotation        = 0.0f;
    bool  is_vehicle            = false;
    bool  vehicle_is_stationary = false;

    is_vehicle = (active_safety::ObjectClass::MOTORCYCLE == obj.object_class || active_safety::ObjectClass::ESCOOTER == obj.object_class ||
                  active_safety::ObjectClass::CAR == obj.object_class || active_safety::ObjectClass::TRUCK == obj.object_class ||
                  active_safety::ObjectClass::UNIDENTIFIED_VEHICLE == obj.object_class);

    vehicle_is_stationary = (obj.speed < 2) && (fabsf(obj.lat_vel) < 1);
    if (vehicle_is_stationary && is_vehicle) {
        m_sin_rotation = sinf(active_safety::math::MapAngToInterval(static_cast<float>(M_PI), obj.heading));
    } else {
        m_sin_rotation = sinf(active_safety::math::MapAngToInterval(static_cast<float>(M_PI_2), obj.heading));
    }

    if (active_safety::ObjectClass::PEDESTRIAN == obj.object_class || active_safety::ObjectClass::ANIMAL == obj.object_class ||
        active_safety::ObjectClass::GENOBJ == obj.object_class || active_safety::ObjectClass::UNDETERMINED == obj.object_class ||
        ((active_safety::ObjectClass::BICYCLE == obj.object_class || obj.object_class == active_safety::ObjectClass::ESCOOTER) &&
         !(obj.speed > colleva_param.k_bike_spd_thd))) {
        m_sin_rotation = 0.0f;
    }
    return m_sin_rotation;
}

float CollisionEvaluator::CalCosRotation(const active_safety::AsObstacle &obj) {
    float m_cos_rotation        = 0.0f;
    bool  is_vehicle            = false;
    bool  vehicle_is_stationary = false;

    is_vehicle = (active_safety::ObjectClass::MOTORCYCLE == obj.object_class || active_safety::ObjectClass::ESCOOTER == obj.object_class ||
                  active_safety::ObjectClass::CAR == obj.object_class || active_safety::ObjectClass::TRUCK == obj.object_class ||
                  active_safety::ObjectClass::UNIDENTIFIED_VEHICLE == obj.object_class);

    vehicle_is_stationary = (obj.speed < 2) && (fabsf(obj.lat_vel) < 1);
    if (vehicle_is_stationary && is_vehicle) {
        m_cos_rotation = cosf(active_safety::math::MapAngToInterval(static_cast<float>(M_PI), obj.heading));
    } else {
        m_cos_rotation = cosf(active_safety::math::MapAngToInterval(static_cast<float>(M_PI_2), obj.heading));
    }

    if (active_safety::ObjectClass::PEDESTRIAN == obj.object_class || active_safety::ObjectClass::ANIMAL == obj.object_class ||
        active_safety::ObjectClass::GENOBJ == obj.object_class || active_safety::ObjectClass::UNDETERMINED == obj.object_class ||
        ((active_safety::ObjectClass::BICYCLE == obj.object_class || obj.object_class == active_safety::ObjectClass::ESCOOTER) &&
         (!(obj.speed > colleva_param.k_bike_spd_thd)))) {
        m_cos_rotation = 1.0f;
    }
    return m_cos_rotation;
}
void CollisionEvaluator::CheckVehicle(const active_safety::AsObstacle &obj) {
    bool is_vehicle = false;
    if (active_safety::ObjectClass::BICYCLE == obj.object_class || active_safety::ObjectClass::MOTORCYCLE == obj.object_class ||
        active_safety::ObjectClass::ESCOOTER == obj.object_class || active_safety::ObjectClass::CAR == obj.object_class ||
        active_safety::ObjectClass::TRUCK == obj.object_class || active_safety::ObjectClass::UNIDENTIFIED_VEHICLE == obj.object_class) {
        is_vehicle = true;
    }
    motion_type.obs_is_vehicle = is_vehicle;
}

void CollisionEvaluator::CheckMotorVehicle(const active_safety::AsObstacle &obj) {
    bool is_motor_vehicle = false;
    if (active_safety::ObjectClass::MOTORCYCLE == obj.object_class || active_safety::ObjectClass::CAR == obj.object_class ||
        active_safety::ObjectClass::TRUCK == obj.object_class || active_safety::ObjectClass::UNIDENTIFIED_VEHICLE == obj.object_class) {
        is_motor_vehicle = true;
    }
    motion_type.obs_is_motor_veh = is_motor_vehicle;
}

void CollisionEvaluator::CheckAbsHeading(const active_safety::AsObstacle &obj) {
//    float abs_heading      = 0.0f;
//    bool  head_need_modify = false;
//    if (obj.long_vel < -0.5f) {
//        if (active_safety::AS_OBS_MP_MOV_FROM_SELF == obj.motion_pattern || active_safety::AS_OBS_MP_MOV_TO_SELF == obj.motion_pattern) {
//            head_need_modify = true;
//        }
//    }

//    if (true == head_need_modify) {
//        float ang   = obj.heading - static_cast<float>(M_PI);
//        ang         = active_safety::math::MapAngToInterval(static_cast<float>(M_PI), ang);
//        abs_heading = fabsf(ang);
//    } else {
//        abs_heading = fabsf(obj.heading);
//    }
    motion_type.abs_heading = fabsf(obj.heading);
}

void CollisionEvaluator::CheckStationary(const active_safety::AsObstacle &obj) {
    bool rec_ro_stat_veh = false;
    if ((active_safety::AS_OBS_MP_MOV_FROM_SELF == obj.motion_pattern || active_safety::AS_OBS_MP_STATIONARY == obj.motion_pattern) && true == motion_type.obs_is_vehicle) {
        rec_ro_stat_veh = true;
    }

    bool sta_no_vehicle = false;
    if (active_safety::AS_OBS_MP_STATIONARY == obj.motion_pattern && false == motion_type.obs_is_vehicle) {
        sta_no_vehicle = true;
    }

    bool rec_ro_stat = false;
    if (rec_ro_stat_veh || sta_no_vehicle) {
        rec_ro_stat = true;
    }

    bool motion_pattern_sta = false;
    if (true == rec_ro_stat && obj.long_vel < 0.0f && obj.long_vel > -2.0) {
        motion_pattern_sta = true;
    }

    bool no_detec_v_lgt = false;
    if (fabsf(obj.long_vel) < colleva_param.k_spd_thd_for_stat_lgt) {
        no_detec_v_lgt = true;
    }

    bool stat_lgt = false;
    if (no_detec_v_lgt) {
        stat_lgt = true;
    }

    bool stat_lat = false;
    if (fabsf(obj.lat_vel) < colleva_param.k_spd_thd_for_stat_lat) {
        stat_lat = true;
    }

    bool stat_vision = false;
    if ((active_safety::AS_OBS_MP_STATIONARY == obj.motion_pattern) &&
        ((active_safety::ObjectClass::CAR == obj.object_class) || (active_safety::ObjectClass::TRUCK == obj.object_class) ||
         (active_safety::ObjectClass::UNIDENTIFIED_VEHICLE == obj.object_class))) {
        stat_vision = true;
    }

    bool stationary = false;
    if ((true == stat_lgt && true == stat_lat)) {
        stationary = true;
    }
    motion_type.stationary = stationary;
}

void CollisionEvaluator::CheckOncoming(const active_safety::AsObstacle &obj) {
    bool moving_oncomming  = false;
    bool mtn_pat_oncomming = false;
    if (active_safety::AS_OBS_MP_MOV_TO_SELF == obj.motion_pattern) {
        mtn_pat_oncomming = true;
    }

    if (true == motion_type.obs_is_motor_veh) {
        bool moving_on_comming_plausible = false;
        if (obj.speed >= 0.0f && true == mtn_pat_oncomming && (fabs(obj.heading) > M_PI_2 + M_PI / 5.0f || obj.long_vel < -0.5)) {
            moving_on_comming_plausible = true;
        }
        bool moving_on_comming_probable = false;
        if (obj.long_vel < -0.5f && active_safety::AS_OBS_MP_MOV_FROM_SELF == obj.motion_pattern) {
            moving_on_comming_probable = true;
        }
        bool confirmed_moving_oncomming = false;
        if (true == moving_on_comming_plausible || true == moving_on_comming_probable) {
            confirmed_moving_oncomming = true;
        }
        moving_oncomming = confirmed_moving_oncomming;
    } else {
        moving_oncomming = false;
    }
    motion_type.moving_oncoming = moving_oncomming;
}

void CollisionEvaluator::CheckParallellVehicleLongPred(const active_safety::AsObstacle &obj) {
    float in_path_heading_thd = 0.0f;
    if (active_safety::ObjectClass::BICYCLE == obj.object_class) {
        in_path_heading_thd = colleva_param.k_bicycle_heading_thd_in_path;
    } else {
        in_path_heading_thd = colleva_param.k_obs_heading_thd_in_path_long;
    }

    bool is_long_pred_obs = false;
    if (true == motion_type.obs_is_vehicle && motion_type.abs_heading < in_path_heading_thd) {
        is_long_pred_obs = true;
    }
    motion_type.para_veh_long_pred = is_long_pred_obs;
}

void CollisionEvaluator::CheckParallellVehicleShortPred(const active_safety::AsObstacle &obj) {
    (void)(obj);
    // bool is_short_pred_obs = false;
    // if (true == motion_type.obs_is_motor_veh &&
    // motion_type.abs_heading < colleva_param.k_obs_heading_thd_in_path_short)
    // { is_short_pred_obs = true;
    // }
    motion_type.para_veh_short_pred = false;
}

void CollisionEvaluator::CheckCurvedMotion(const active_safety::AsObstacle &obj) {
    bool curved_motion = false;
    if (fabs(obj.speed) > colleva_param.k_spd_thd_for_stat_lgt && fabsf(obj.curvature) > colleva_param.k_crvt_thd_for_curved_motion &&
        true == motion_type.obs_is_vehicle) {
        curved_motion = true;
    }
    motion_type.curved_motion = curved_motion;
}

void CollisionEvaluator::CheckSideIsClosest(const AsVseOut &vse_out, const active_safety::AsObstacle &obj) {
    (void)(vse_out);
    bool side_close = false;
    if (false == motion_type.obs_is_vehicle) {
        side_near                = AS_OBS_SD_UNKNOWN;
        motion_type.side_closest = side_close;
        return;
    }
    if (fabs(obj.heading) > M_PI_2) {
        side_near = AS_OBS_SD_FRONT;
    } else {
        side_near = AS_OBS_SD_REAR;
    }
    // switch (obj.object_class) {
    //     case active_safety::ObjectClass::CAR:
    //     case active_safety::ObjectClass::TRUCK:
    //     case active_safety::ObjectClass::UNIDENTIFIED_VEHICLE:
    //         switch (obj.m_pos_type) {
    //             case SFObsPositionType::SAF_POS_TYPE_UNKNOWN:
    //                 side_near = AS_OBS_SD_UNKNOWN;
    //                 break;
    //             case SFObsPositionType::SAF_POS_TYPE_FRONT_CENTER:
    //                 side_near = AS_OBS_SD_FRONT;
    //                 break;
    //             case SFObsPositionType::SAF_POS_TYPE_REAR_CENTER:
    //                 side_near = AS_OBS_SD_REAR;
    //                 break;
    //             case SFObsPositionType::SAF_POS_TYPE_LEFT_CENTER:
    //                 side_near = AS_OBS_SD_LEFT;
    //                 side_close = true;
    //                 break;
    //             case SFObsPositionType::SAF_POS_TYPE_RIGHT_CENTER:
    //                 side_near = AS_OBS_SD_RIGHT;
    //                 side_close = true;
    //                 break;
    //             case SFObsPositionType::SAF_POS_TYPE_CENTER:
    //             default:
    //                 side_near = AS_OBS_SD_REAR;
    //                 break;
    //         }
    //         motion_type.side_closest = side_close;
    //         break;

    //     default:
    //         // Only for car, truck, veh_unknown, motor_bic, bic
    //         float min_lgt_err = 0.8f;
    //         float min_lat_err = 0.8f;
    //         float ego_half_width = vse_out.host_width / 2.0f;
    //         int near_side = AS_OBS_SD_UNKNOWN;
    //         if ((fabs(obj.long_vel) <= min_lgt_err) &&
    //             (obj.lat_vel > min_lat_err)) {
    //             // Obstacle is crossing to left
    //             near_side = AS_OBS_SD_LEFT;
    //         } else if ((fabs(obj.long_vel) <= min_lgt_err) &&
    //                    (obj.lat_vel < -min_lat_err)) {
    //             // Obstacle is crossing to right
    //             near_side = AS_OBS_SD_RIGHT;
    //         } else if ((obj.long_vel > min_lgt_err) &&
    //                    (fabs(obj.lat_vel) <= min_lat_err)) {
    //             // Obstacle is moving forward-straight
    //             near_side = AS_OBS_SD_REAR;
    //         } else if ((obj.long_vel < -min_lgt_err) &&
    //                    (fabs(obj.lat_vel) <= min_lat_err)) {
    //             // Obstacle is moving backward-straight
    //             near_side = AS_OBS_SD_FRONT;
    //         } else if ((obj.long_vel > min_lgt_err) &&
    //                    (obj.lat_vel >= min_lat_err)) {
    //             // Obstacle is moving foward-left
    //             float left_top =
    //                 obj.lat_posn +
    //                 (obj.width / 2.0f * obj.m_bounding_box.cos_rotation) +
    //                 (obj.length * obj.m_bounding_box.sin_rotation);
    //             float right_bot =
    //                 obj.lat_posn -
    //                 (obj.width / 2.0f * obj.m_bounding_box.cos_rotation);
    //             if ((left_top > ego_half_width) &&
    //                 (right_bot > ego_half_width)) {
    //                 near_side = AS_OBS_SD_REAR;
    //             } else if ((left_top < -ego_half_width) &&
    //                        (right_bot < -ego_half_width)) {
    //                 near_side = AS_OBS_SD_LEFT;
    //             } else {
    //                 // do nothing
    //             }
    //         } else if ((obj.long_vel > min_lgt_err) &&
    //                    (obj.lat_vel < -min_lat_err)) {
    //             // Obstacle is moving forward-right
    //             float left_bot =
    //                 obj.lat_posn +
    //                 (obj.width / 2.0f * obj.m_bounding_box.cos_rotation);
    //             float right_top =
    //                 obj.lat_posn -
    //                 (obj.width / 2.0f * obj.m_bounding_box.cos_rotation) +
    //                 (obj.length * obj.m_bounding_box.sin_rotation);
    //             if ((left_bot > ego_half_width) &&
    //                 (right_top > ego_half_width)) {
    //                 near_side = AS_OBS_SD_RIGHT;
    //             } else if ((left_bot < -ego_half_width) &&
    //                        (right_top < -ego_half_width)) {
    //                 near_side = AS_OBS_SD_REAR;
    //             } else {
    //                 // do nothing
    //             }
    //         } else if ((obj.long_vel < -min_lgt_err) &&
    //                    (obj.lat_vel >= min_lat_err)) {
    //             // Obstacle is moving backward-left
    //             float right_top =
    //                 obj.lat_posn -
    //                 (obj.width / 2.0f * obj.m_bounding_box.cos_rotation) +
    //                 (obj.length * obj.m_bounding_box.sin_rotation);
    //             float left_bot =
    //                 obj.lat_posn +
    //                 (obj.width / 2.0f * obj.m_bounding_box.cos_rotation);
    //             if ((right_top > ego_half_width) &&
    //                 (left_bot > ego_half_width)) {
    //                 near_side = AS_OBS_SD_LEFT;
    //             } else if ((right_top < -ego_half_width) &&
    //                        (left_bot < -ego_half_width)) {
    //                 near_side = AS_OBS_SD_FRONT;
    //             } else {
    //                 // do nothing
    //             }
    //         } else if ((obj.long_vel < -min_lgt_err) &&
    //                    (obj.lat_vel < -min_lat_err)) {
    //             // Obstacle is moving backward-right
    //             float left_top =
    //                 obj.lat_posn +
    //                 (obj.width / 2.0f * obj.m_bounding_box.cos_rotation) +
    //                 (obj.length * obj.m_bounding_box.sin_rotation);
    //             float right_bot =
    //                 obj.lat_posn -
    //                 (obj.width / 2.0f * obj.m_bounding_box.cos_rotation);
    //             if ((left_top > ego_half_width) &&
    //                 (right_bot > ego_half_width)) {
    //                 near_side = AS_OBS_SD_FRONT;
    //             } else if ((left_top < -ego_half_width) &&
    //                        (right_bot < -ego_half_width)) {
    //                 near_side = AS_OBS_SD_RIGHT;
    //             } else {
    //                 // do nothing
    //             }
    //         } else {
    //             near_side = AS_OBS_SD_REAR;
    //         }
    //         side_near = near_side;
    //         if ((AS_OBS_SD_LEFT == side_near) ||
    //             (AS_OBS_SD_RIGHT == side_near)) {
    //             side_close = true;
    //         }
    //         motion_type.side_closest = side_close;
    //         break;
    // }
    motion_type.side_closest = false;
}

} // namespace tap
} // namespace senseAD
