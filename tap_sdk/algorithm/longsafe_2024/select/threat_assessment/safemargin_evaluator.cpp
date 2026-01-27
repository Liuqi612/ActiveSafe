#include "safemargin_evaluator.h"

namespace senseAD {
namespace tap {

SafetyMarginEvaluator::SafetyMarginEvaluator() {
}

SafetyMarginEvaluator::~SafetyMarginEvaluator() {
}

void SafetyMarginEvaluator::ProcessSafetyMarginEvaluator(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eva,
                                                         const AsEgoPath &curv_path, const AsVseOut &vse_out) {
    CalcHeadingFromVelocity(obj);
    CalcDetermineOffset(obj, coll_eva, vse_out);
    modified_ttr   = CalcModifiedTTR(obj, vse_out, coll_eva.ttr);
    pred_ttr_valid = CheckPredictValidity(obj, coll_eva, curv_path, modified_ttr);
    pred_ttm_valid = CheckPredictValidity(obj, coll_eva, curv_path, coll_eva.ttm);
    CalcCoordTransformToCurve(obj, vse_out);
}

void SafetyMarginEvaluator::Clear() {
    curv_coord_info.curv                           = 0.0f;
    curv_coord_info.curv_radius                    = 0.0f;
    curv_coord_info.pos_lat_rel                    = 0.0f;
    curv_coord_info.spd_lat_rel                    = 0.0f;
    predict_offset.offs_lgt_long_pred              = 0.0f;
    predict_offset.offs_lat_long_pred              = 0.0f;
    predict_offset.offs_lgt_short_pred             = 0.0f;
    predict_offset.offs_lat_short_pred             = 0.0f;
    predict_offset.offs_lat_manoeuvre              = 0.0f;
    predict_offset.offs_lat_in_path_primary_target = 0.0f;
    predict_offset.offs_lat_in_path_close_edge     = 0.0f;
    predict_offset.offs_lat_in_path_far_edge       = 0.0f;
    predict_offset.offs_lat_intersection           = 0.0f;
    predict_offset.offs_lat_multi_target           = 0.0f;
    cos_heading                                    = 0.0f;
    sin_heading                                    = 0.0f;
    pred_ttr_valid                                 = false;
    pred_ttm_valid                                 = false;
    modified_ttr                                   = 100.0f;
}

void SafetyMarginEvaluator::CalcHeadingFromVelocity(const active_safety::AsObstacle &obj) {
    // obj speed calculation
    float obj_abs_spd = sqrtf(obj.lat_vel * obj.lat_vel + obj.long_vel * obj.long_vel);
    cos_heading       = math::Clamp(math::SafeDivide(obj.long_vel, obj_abs_spd), -100000.0f, 100000.0f);
    sin_heading       = math::Clamp(math::SafeDivide(obj.lat_vel, obj_abs_spd), -100000.0f, 100000.0f);
}

float SafetyMarginEvaluator::CalcModifiedTTR(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float ttc_raw) {
    float ttr_temp              = ttc_raw;
    float cycle_and_car_lat_ttc = fmaxf(0.0, fabsf(obj.lat_posn / obj.lat_vel));
    if (vse_out.aeb_active) {
        bool obj_is_largevel_cross_flag =
            (((obj.object_class == active_safety::ObjectClass::MOTORCYCLE) || (obj.object_class == active_safety::ObjectClass::BICYCLE) ||
              obj.object_class == active_safety::ObjectClass::CAR) &&
             fabs(obj.lat_vel) > 2.5);
        ttr_temp = obj_is_largevel_cross_flag ? fminf(ttc_raw, cycle_and_car_lat_ttc) : fminf(ttc_raw, safemagin_param.k_max_aeb_active_ttr_thd);
    }
    return ttr_temp;
}

void SafetyMarginEvaluator::CalcCoordTransformToCurve(const active_safety::AsObstacle &obj, const AsVseOut &vse_out) {
    float ego_curv_radius = math::SafeDivide(1.0f, vse_out.rear_curvature);
    float t_posn_lat      = obj.lat_posn - ego_curv_radius;
    float t_agdir         = atan2f(t_posn_lat, obj.long_posn);
    float t_v_lat         = obj.long_vel * cosf(t_agdir) + obj.lat_vel * sinf(t_agdir);
    // Calc the spd lateral relative
    curv_coord_info.spd_lat_rel = t_v_lat * (-math::SignF(ego_curv_radius));

    // Calculate the curved lgt position
    float t_pos         = math::SafeDivide(obj.long_posn, t_posn_lat);
    float curv_lgt_posn = -ego_curv_radius * atanf(t_pos);
    float t_crv_rad     = sinf(curv_lgt_posn * vse_out.rear_curvature);
    t_crv_rad           = math::SafeDivide(obj.long_posn, t_crv_rad);

    if (fabsf(vse_out.rear_curvature) > 0.0001f) {
        curv_coord_info.pos_lat_rel = ego_curv_radius - t_crv_rad;
    } else {
        curv_coord_info.pos_lat_rel = obj.lat_posn;
    }

    // Calculate the curvature radius
    curv_coord_info.curv_radius = ego_curv_radius;

    // Calculate the curvature radius
    curv_coord_info.curv = vse_out.rear_curvature;
}

bool SafetyMarginEvaluator::CheckPredictValidity(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eva,
                                                 const AsEgoPath &curv_path, float ttc) {
    // Check prediction time with path estimation
    bool  path_estima_ena  = false;
    float endtimeoflastseg = curv_path.GetEndTimeOfPath();
    if ((ttc > 0.0f) && (ttc < endtimeoflastseg)) {
        path_estima_ena = true;
    } else {
        path_estima_ena = false;
    }
    // Check prediction time below threshold
    bool pred_ti_ena = false;
    if (ttc < safemagin_param.k_max_pred_tti_thd) {
        pred_ti_ena = true;
    } else {
        pred_ti_ena = false;
    }
    // Check prediction distance and speed condition
    bool pred_dist_ena = false;
    bool spd_ena       = false;
    if (coll_eva.motion_type.obs_is_motor_veh) {
        if (fabsf(obj.speed) * ttc < safemagin_param.k_max_pred_dist_thd) {
            pred_dist_ena = true;
        } else {
            pred_dist_ena = false;
        }

        if (fabsf(obj.speed) > safemagin_param.k_min_pred_spd_thd) {
            spd_ena = true;
        } else {
            spd_ena = false;
        }
    } else {
        pred_dist_ena = true;
        spd_ena       = true;
    }
    // Check the confidence for heading
    bool head_ena = false;
    if ((fabsf(obj.speed) < safemagin_param.k_ag_dir_spd_thd) && (coll_eva.motion_type.obs_is_motor_veh)) {
        if (obj.fusion_source != active_safety::FusionSource::SRR_ONLY) {
            head_ena = true;
        } else {
            head_ena = false;
        }
    } else {
        head_ena = true;
    }

    // check the object type
    bool obj_type_ena = false;
    if ((obj.object_class != active_safety::ObjectClass::UNIDENTIFIED_VEHICLE) && (obj.object_class != active_safety::ObjectClass::ANIMAL)) {
        obj_type_ena = true;
    } else {
        obj_type_ena = false;
    }

    // check prediction ok for use
    bool ret = false;
    if (path_estima_ena && pred_ti_ena && pred_dist_ena && spd_ena && head_ena && obj_type_ena) {
        ret = true;
    } else {
        ret = false;
    }
    return ret;
}

void SafetyMarginEvaluator::CalcDetermineOffset(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eva, const AsVseOut &vse_out) {
    float half_proj_cycle_length = 0.0f;
    float half_proj_cycle_width  = 0.0f;
    ProjectedBicycleInfo(coll_eva, half_proj_cycle_length, half_proj_cycle_width);
    CalcLongPredTimeOffset(obj, vse_out, half_proj_cycle_width, half_proj_cycle_length, predict_offset);
    CalcShortPredTimeOffset(obj, vse_out, half_proj_cycle_width, half_proj_cycle_length, predict_offset);
    CalcLateralManoeuverOffset(obj, vse_out, half_proj_cycle_width, predict_offset);
    CalcLatInPathOffsetForLTAP(obj, vse_out, half_proj_cycle_width, predict_offset);
    CalcLatInPathOffset(obj, vse_out, predict_offset);
    CalcLateralIntersectionOffset(obj, vse_out, predict_offset);
    CalcLateralOffsetForMultipleTgt(obj, vse_out, half_proj_cycle_width, predict_offset);
}

void SafetyMarginEvaluator::CalcLongPredTimeOffset(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float half_width, float half_length,
                                                   PredictOffset &predoffst) {
    float vlgt_rel = vse_out.vcs_long_vel - obj.long_vel;
    switch (obj.object_class) {
        case active_safety::ObjectClass::PEDESTRIAN:
        case active_safety::ObjectClass::ANIMAL:
        case active_safety::ObjectClass::GENOBJ:
        case active_safety::ObjectClass::BICYCLE: {
            float k_longlgt_vlgt_vru_offs =
                LookUpTable::LookupTable1D<8>(safemagin_param.k_longlgt_vlgtrel, safemagin_param.k_longlgt_vlgt_vru_offs, vlgt_rel);

            float longlat_vlgt_vlat_vru_offs =
                LookUpTable::LookupTable2D<8, 8>(safemagin_param.k_longlat_vlgtrel, safemagin_param.k_longlat_vlatrel,
                                                 safemagin_param.k_longlat_vlgt_vlat_vru, vlgt_rel, fabsf(obj.lat_vel));

            if (obj.object_class == active_safety::ObjectClass::BICYCLE) {
                k_longlgt_vlgt_vru_offs += half_length;
                longlat_vlgt_vlat_vru_offs += half_width;
            }
            if (obj.object_class == active_safety::ObjectClass::PEDESTRIAN || obj.object_class == active_safety::ObjectClass::ANIMAL ||
                obj.object_class == active_safety::ObjectClass::GENOBJ) {
                longlat_vlgt_vlat_vru_offs += obj.width * 0.5;
            }
            predoffst.offs_lgt_long_pred = k_longlgt_vlgt_vru_offs;
            predoffst.offs_lat_long_pred = longlat_vlgt_vlat_vru_offs;
            break;
        }
        case active_safety::ObjectClass::CAR:
        case active_safety::ObjectClass::TRUCK:
        case active_safety::ObjectClass::MOTORCYCLE:
        case active_safety::ObjectClass::UNIDENTIFIED_VEHICLE: {
            float k_longlgt_vlgt_veh_offs =
                LookUpTable::LookupTable1D<8>(safemagin_param.k_longlgt_vlgtrel, safemagin_param.k_longlgt_vlgt_veh_offs, vlgt_rel);

            float longlat_alat_veh_offs =
                LookUpTable::LookupTable1D<9>(safemagin_param.k_longlat_algtraw, safemagin_param.k_longlat_algt_veh_offs, obj.long_accel);

            float longlat_vlgt_vlat_veh_offs =
                LookUpTable::LookupTable2D<8, 8>(safemagin_param.k_longlat_vlgtrel, safemagin_param.k_longlat_vlatabs,
                                                 safemagin_param.k_longlat_vlgt_vlat_veh, vlgt_rel, fabsf(obj.lat_vel));
            predoffst.offs_lgt_long_pred = k_longlgt_vlgt_veh_offs;
            predoffst.offs_lat_long_pred = longlat_alat_veh_offs + longlat_vlgt_vlat_veh_offs;
            break;
        }

        default: {
            predoffst.offs_lgt_long_pred = 0.0f;
            predoffst.offs_lat_long_pred = 0.0f;
            break;
        }
    }
}
void SafetyMarginEvaluator::CalcShortPredTimeOffset(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float half_width,
                                                    float half_length, PredictOffset &predoffst) {
    float vlgt_rel = vse_out.vcs_long_vel - obj.long_vel;
    // long offset for vru
    float k_shortlgt_vlgt_vru_offs =
        LookUpTable::LookupTable1D<8>(safemagin_param.k_shortlgt_vlgtrel, safemagin_param.k_shortlgt_vlgt_vru_offs, vlgt_rel);
    // long offset for veh.
    float k_shortlgt_poslgt_veh_offs = LookUpTable::LookupTable1D<8>(safemagin_param.k_shortlgt_poslgt, safemagin_param.k_shortlgt_poslgt_veh_offs,
                                                                     obj.long_posn - vse_out.host_dist_to_front);
    // lat offset for vru.
    float shortlat_vlgt_vlat_vru_offs = LookUpTable::LookupTable2D<8, 8>(safemagin_param.k_shortlat_vlgtrel, safemagin_param.k_shortlat_vlatabs,
                                                                         safemagin_param.k_shortlat_vlgt_vlat_vru, vlgt_rel, fabs(obj.lat_vel));
    // lat offset for two wheel.
    float shortlat_vlgt_vlat_cyclist_offs =
        LookUpTable::LookupTable2D<8, 8>(safemagin_param.k_shortlat_vlgtrel_cyclist, safemagin_param.k_shortlat_vlatabs_cyclist,
                                         safemagin_param.k_shortlat_vlgt_vlat_cyclist, vlgt_rel, fabs(obj.lat_vel));
    // long offset for four wheel car.
    float k_shortlat_algt_veh_offs =
        LookUpTable::LookupTable1D<9>(safemagin_param.k_shortlat_algtabs, safemagin_param.k_shortlat_algt_veh_offs, obj.long_accel);

    // lat offset for car.
    float shortlat_vlgt_vlat_veh_offs =
        LookUpTable::LookupTable2D<8, 8>(safemagin_param.k_shortlat_vlgtrel_veh, safemagin_param.k_shortlat_vlatrel_veh,
                                         safemagin_param.k_shortlat_vlgt_vlat_veh, vlgt_rel, fabs(obj.lat_vel));

    switch (obj.object_class) {
        case active_safety::ObjectClass::PEDESTRIAN:
        case active_safety::ObjectClass::ANIMAL:
        case active_safety::ObjectClass::GENOBJ: {
            if (vse_out.straight_driving) {
                predoffst.offs_lgt_short_pred = k_shortlgt_vlgt_vru_offs;
            } else {
                predoffst.offs_lgt_short_pred = 0.0f;
            }
            predoffst.offs_lat_short_pred = shortlat_vlgt_vlat_vru_offs + 0.5f * obj.width;
            break;
        }
        case active_safety::ObjectClass::BICYCLE: {
            if (vse_out.straight_driving) {
                predoffst.offs_lgt_short_pred = half_length;
            } else {
                predoffst.offs_lgt_short_pred = k_shortlgt_vlgt_vru_offs + half_length;
            }
            predoffst.offs_lat_short_pred = shortlat_vlgt_vlat_cyclist_offs + half_width;
            break;
        }
        case active_safety::ObjectClass::MOTORCYCLE:
        case active_safety::ObjectClass::ESCOOTER: {
            predoffst.offs_lgt_short_pred = k_shortlgt_poslgt_veh_offs;
            predoffst.offs_lat_short_pred = k_shortlat_algt_veh_offs + shortlat_vlgt_vlat_cyclist_offs;
            break;
        }

        case active_safety::ObjectClass::CAR:
        case active_safety::ObjectClass::TRUCK:
        case active_safety::ObjectClass::UNIDENTIFIED_VEHICLE: {
            predoffst.offs_lgt_short_pred = k_shortlgt_poslgt_veh_offs;
            predoffst.offs_lat_short_pred = k_shortlat_algt_veh_offs + shortlat_vlgt_vlat_veh_offs;
            break;
        }
        default: {
            predoffst.offs_lgt_short_pred = 0.0f;
            predoffst.offs_lat_short_pred = 0.0f;
            break;
        }
    }
    if (vse_out.aeb_active) {
        predoffst.offs_lgt_short_pred = safemagin_param.k_vel_offs_lgt;
    }
}
void SafetyMarginEvaluator::CalcLateralManoeuverOffset(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float half_width,
                                                       PredictOffset &predoffst) {
    switch (obj.object_class) {
        case active_safety::ObjectClass::PEDESTRIAN:
        case active_safety::ObjectClass::ANIMAL:
        case active_safety::ObjectClass::GENOBJ: {
            predoffst.offs_lat_manoeuvre = 0.5f * obj.width + LookUpTable::LookupTable1D<8>(safemagin_param.k_manv_vlgt_ego,
                                                                                            safemagin_param.k_manv_latoffs_vru, vse_out.vcs_long_vel);
            break;
        }
        case active_safety::ObjectClass::BICYCLE: {
            predoffst.offs_lat_manoeuvre = half_width + LookUpTable::LookupTable1D<8>(safemagin_param.k_manv_vlgt_ego,
                                                                                      safemagin_param.k_manv_latoffs_bike, vse_out.vcs_long_vel);
            break;
        }
        case active_safety::ObjectClass::CAR:
        case active_safety::ObjectClass::TRUCK:
        case active_safety::ObjectClass::MOTORCYCLE:
        case active_safety::ObjectClass::ESCOOTER:
        case active_safety::ObjectClass::UNIDENTIFIED_VEHICLE: {
            float vlgt_rel = vse_out.vcs_long_vel - obj.long_vel;
            predoffst.offs_lat_manoeuvre =
                LookUpTable::LookupTable1D<8>(safemagin_param.k_manv_vlgt_rel, safemagin_param.k_manv_latoffs_veh, vlgt_rel);
            break;
        }
        default: {
            predoffst.offs_lat_manoeuvre = 0.0f;
            break;
        }
    }
}
void SafetyMarginEvaluator::CalcLatInPathOffsetForLTAP(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float half_width,
                                                       PredictOffset &predoffst) {
    (void)(vse_out);
    switch (obj.object_class) {
        case active_safety::ObjectClass::PEDESTRIAN:
        case active_safety::ObjectClass::ANIMAL:
        case active_safety::ObjectClass::GENOBJ: {
            predoffst.offs_lat_in_path_primary_target = safemagin_param.k_inpath_ltap_latoffs_veh + obj.width * 0.5;
            break;
        }
        case active_safety::ObjectClass::BICYCLE: {
            predoffst.offs_lat_in_path_primary_target = safemagin_param.k_inpath_ltap_latoffs_veh + half_width;
            break;
        }
        case active_safety::ObjectClass::CAR:
        case active_safety::ObjectClass::TRUCK:
        case active_safety::ObjectClass::MOTORCYCLE:
        case active_safety::ObjectClass::UNIDENTIFIED_VEHICLE: {
            predoffst.offs_lat_in_path_primary_target = safemagin_param.k_inpath_ltap_latoffs_veh;
            break;
        }

        default: {
            predoffst.offs_lat_in_path_primary_target = 0.0f;
            break;
        }
    }
}
void SafetyMarginEvaluator::CalcLatInPathOffset(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, PredictOffset &predoffst) {
    // optional choice
    // float inpath_latoffs_veh_opt = LookUpTable::LookupTable2D<8, 8>(
    //     safemagin_param.k_inpath_vlgt, safemagin_param.k_inpath_yaw_rate,
    //     safemagin_param.k_inpath_offset_optional, vse_out.vcs_long_vel,
    //     vse_out.yawrate);
    // additional far edge offset
    float dist_to_far_hostedge = 0.0f;
    if (((curv_coord_info.pos_lat_rel > 0.0f) && (fabsf(curv_coord_info.spd_lat_rel) < 1.0f)) || (curv_coord_info.spd_lat_rel < 0.0f)) {
        dist_to_far_hostedge = 0.5f * vse_out.host_width + curv_coord_info.pos_lat_rel;
    } else {
        dist_to_far_hostedge = 0.5f * vse_out.host_width - curv_coord_info.pos_lat_rel;
    }
    float addition_far_edge_offs = 0.0f;
    if (fabsf(curv_coord_info.spd_lat_rel) > safemagin_param.k_inpath_obj_detect_spdthd) {
        if (vse_out.aeb_active) {
            addition_far_edge_offs =
                LookUpTable::LookupTable1D<9>(safemagin_param.k_inpath_dist_host, safemagin_param.k_inpath_add_dist_offs, dist_to_far_hostedge);
        } else {
            float limit_faredge_offs =
                LookUpTable::LookupTable1D<5>(safemagin_param.k_inpath_vlgt_ego_add, safemagin_param.k_inpath_vlgt_lim_offs, vse_out.vcs_long_vel);
            float far_edge_offs =
                LookUpTable::LookupTable1D<9>(safemagin_param.k_in_path_rem_edge, safemagin_param.k_inpath_add_dist_offs1, dist_to_far_hostedge);
            addition_far_edge_offs = fminf(limit_faredge_offs, far_edge_offs);
        }
    } else {
        addition_far_edge_offs = 0.0f;
    }
    float obj_width = obj.width;
    // selected bicycle width
    if (active_safety::ObjectClass::BICYCLE == obj.object_class) {
        obj_width = safemagin_param.k_bike_width_offset;
    } else {
        // do nothing
    }

    // float vlgt_rel = obj.long_vel - vse_out.vcs_long_vel;
    switch (obj.object_class) {
        case active_safety::ObjectClass::PEDESTRIAN:
        case active_safety::ObjectClass::ANIMAL: {
            // close edge offset for small obj.
            float inpath_latoffs_vru =
                LookUpTable::LookupTable1D<8>(safemagin_param.k_inpath_vlgt_ego_ped, safemagin_param.k_inpath_vlgt_ped_offs, vse_out.vcs_long_vel);
            if (vse_out.aeb_active) {
                predoffst.offs_lat_in_path_close_edge = fmaxf(inpath_latoffs_vru, safemagin_param.k_min_lat_cmbb) + 0.5f * obj_width;
            } else {
                predoffst.offs_lat_in_path_close_edge = inpath_latoffs_vru + 0.5f * obj_width;
            }
            float verfied_offs = CalcVerifiedFarEdgeOffset(obj_width, predoffst.offs_lat_in_path_close_edge);
            // bool fast_ped_flag = false;
            // if (obj.speed > safemagin_param.k_fast_ped_spd_thd) {
            //   fast_ped_flag = true;
            // } else {
            //   fast_ped_flag = false;
            // }
            // if (obj.object_class == active_safety::ObjectClass::PEDESTRIAN &&
            // fast_ped_flag) { predoffst.offs_lat_in_path_close_edge = 0.0;
            predoffst.offs_lat_in_path_far_edge = addition_far_edge_offs + 0.5f * obj_width + verfied_offs;
            // } else {
            // predoffst.offs_lat_in_path_close_edge = 0.0;
            // predoffst.offs_lat_in_path_far_edge =
            //     addition_far_edge_offs + 0.5f * obj_width +
            //     verfied_offs;
            // }
            break;
        }
        case active_safety::ObjectClass::GENOBJ: {
            // close edge offset for small obj.
            float inpath_latoffs_vru =
                LookUpTable::LookupTable1D<8>(safemagin_param.k_inpath_vlgt_ego_ped, safemagin_param.k_inpath_vlgt_gop_offs, vse_out.vcs_long_vel);
            if (vse_out.aeb_active) {
                predoffst.offs_lat_in_path_close_edge = fmaxf(inpath_latoffs_vru, safemagin_param.k_gop_min_lat_cmbb) ;
            } else {
                predoffst.offs_lat_in_path_close_edge = inpath_latoffs_vru;
            }
            float verfied_offs = CalcVerifiedFarEdgeOffset(obj_width, predoffst.offs_lat_in_path_close_edge);
            // bool fast_ped_flag = false;
            // if (obj.speed > safemagin_param.k_fast_ped_spd_thd) {
            //   fast_ped_flag = true;
            // } else {
            //   fast_ped_flag = false;
            // }
            // if (obj.object_class == active_safety::ObjectClass::PEDESTRIAN &&
            // fast_ped_flag) { predoffst.offs_lat_in_path_close_edge = 0.0;
            predoffst.offs_lat_in_path_far_edge = addition_far_edge_offs + verfied_offs;
            // } else {
            // predoffst.offs_lat_in_path_close_edge = 0.0;
            // predoffst.offs_lat_in_path_far_edge =
            //     addition_far_edge_offs + 0.5f * obj_width +
            //     verfied_offs;
            // }
            break;
        }
        case active_safety::ObjectClass::ESCOOTER:
        case active_safety::ObjectClass::BICYCLE: {
            // close edge offset for two wheel.
            float inpath_latoffs_bike =
                LookUpTable::LookupTable1D<8>(safemagin_param.k_inpath_vlgt_ego_bike, safemagin_param.k_inpath_vlgt_bike_offs, vse_out.vcs_long_vel);
            bool fast_bike_flag       = false;
            bool stationary_bike_flag = false;

            if (obj.speed < safemagin_param.k_stationary_bike_spd_thd) {
                stationary_bike_flag = true;
            } else {
                stationary_bike_flag = false;
            }
            if (obj.speed > safemagin_param.k_fast_bike_spd_thd) {
                fast_bike_flag = true;
            } else {
                fast_bike_flag = false;
            }
            if (vse_out.aeb_active) {
                predoffst.offs_lat_in_path_close_edge = fmaxf(inpath_latoffs_bike, safemagin_param.k_min_lat_cmbb);
            } else {
                if ((obj.long_posn < 4) || (stationary_bike_flag) || (fabs(obj.lat_vel) < 0.5)) {

                    predoffst.offs_lat_in_path_close_edge = -0.3;

                } else {
                    predoffst.offs_lat_in_path_close_edge = inpath_latoffs_bike;
                }
            }
            float verfied_offs                  = CalcVerifiedFarEdgeOffset(obj_width, predoffst.offs_lat_in_path_close_edge);
            predoffst.offs_lat_in_path_far_edge = verfied_offs + addition_far_edge_offs;
            if ((fast_bike_flag == false) && (stationary_bike_flag == false)) {
                predoffst.offs_lat_in_path_close_edge += 0.5 * safemagin_param.k_bike_width_offset;
                predoffst.offs_lat_in_path_far_edge += 0.5 * safemagin_param.k_bike_width_offset;
            }

            break;
        }
        case active_safety::ObjectClass::TRUCK: {
            float inpath_latoffs_truck = LookUpTable::LookupTable1D<11>(
                safemagin_param.k_inpath_posnlgt_truck, safemagin_param.k_inpath_posnlgt_truck_offs, obj.long_posn - vse_out.host_dist_to_front);
            if (vse_out.aeb_active) {
                predoffst.offs_lat_in_path_close_edge = fmaxf(inpath_latoffs_truck, safemagin_param.k_min_lat_cmbb);
            } else {
                predoffst.offs_lat_in_path_close_edge = inpath_latoffs_truck;
            }
            predoffst.offs_lat_in_path_far_edge = CalcVerifiedFarEdgeOffset(obj_width, predoffst.offs_lat_in_path_close_edge);
            break;
        }
        case active_safety::ObjectClass::CAR:
        case active_safety::ObjectClass::MOTORCYCLE:
        case active_safety::ObjectClass::UNIDENTIFIED_VEHICLE: {

            float inpath_latoffs_veh;

            if (obj.speed < 2) {
                inpath_latoffs_veh =
                    LookUpTable::LookupTable1D<11>(safemagin_param.k_inpath_posnlgt_veh, safemagin_param.k_inpath_posnlgt_lowspd_veh_offs,
                                                   obj.long_posn - vse_out.host_dist_to_front);

            } else {
                inpath_latoffs_veh = LookUpTable::LookupTable1D<11>(safemagin_param.k_inpath_posnlgt_veh, safemagin_param.k_inpath_posnlgt_veh_offs,
                                                                    obj.long_posn - vse_out.host_dist_to_front);
            }
            if (vse_out.aeb_active) {
                predoffst.offs_lat_in_path_close_edge = fmaxf(inpath_latoffs_veh, safemagin_param.k_min_lat_cmbb);
            } else {
                predoffst.offs_lat_in_path_close_edge = inpath_latoffs_veh;
            }
            predoffst.offs_lat_in_path_far_edge = CalcVerifiedFarEdgeOffset(obj_width, predoffst.offs_lat_in_path_close_edge);
            // if ((vse_out.host_state & AsHostState::AS_HOST_IN_HARD_CURVE) > 0) {
            //   predoffst.offs_lat_in_path_close_edge += 2.0f;
            // }
//            if (vse_out.straight_driving == false && obj.f_is_aeb_active_tgt) {
//                // 2025-02-27 Ly3 add offset when aeb active for ccft scene.
//                predoffst.offs_lat_in_path_far_edge += 1.0f;
//            }
            break;
        }
        default: {
            predoffst.offs_lat_in_path_close_edge = 0.0f;
            predoffst.offs_lat_in_path_far_edge   = 0.0f;
            break;
        }
    }
}
void SafetyMarginEvaluator::CalcLateralIntersectionOffset(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, PredictOffset &predoffst) {
    float vlgt_rel = vse_out.vcs_long_vel - obj.long_vel;
    predoffst.offs_lat_intersection =
        LookUpTable::LookupTable1D<8>(safemagin_param.k_intersec_vlgtrel, safemagin_param.k_intersec_latoffs_all, vlgt_rel);
    ;
}
void SafetyMarginEvaluator::CalcLateralOffsetForMultipleTgt(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float half_width,
                                                            PredictOffset &predoffst) {
    float vlgt_rel = obj.long_vel - vse_out.vcs_long_vel;
    switch (obj.object_class) {
        case active_safety::ObjectClass::PEDESTRIAN:
        case active_safety::ObjectClass::ANIMAL:
        case active_safety::ObjectClass::GENOBJ:
        case active_safety::ObjectClass::ESCOOTER:
        case active_safety::ObjectClass::BICYCLE: {
            // float multi_Latoffs_vru = LookUpTable::LookupTable2D<8,8>(
            //     safemagin_param.k_muti_vlgt_rel,
            //     safemagin_param.k_muti_vlgt_rel.size(),
            //     safemagin_param.k_muti_vlat_abs,
            //     safemagin_param.k_muti_vlat_abs.size(),
            //     safemagin_param.k_muti_vlgt_vlat_vru, vlgt_rel,
            //     fabs(obj.lat_vel));
            float multi_Latoffs_vru = 0.0;
            if (obj.object_class == active_safety::ObjectClass::BICYCLE) {
                predoffst.offs_lat_multi_target = multi_Latoffs_vru + half_width;

            } else {
                predoffst.offs_lat_multi_target = multi_Latoffs_vru + 0.5 * obj.width;
            }
            break;
        }
        case active_safety::ObjectClass::CAR:
        case active_safety::ObjectClass::TRUCK:
        case active_safety::ObjectClass::MOTORCYCLE:
        case active_safety::ObjectClass::UNIDENTIFIED_VEHICLE: {
            float multi_alat_veh =
                LookUpTable::LookupTable1D<9>(safemagin_param.k_muti_algt_raw, safemagin_param.k_muti_algt_veh_offs, obj.long_accel);
            float multi_vlgt_vlat_veh = LookUpTable::LookupTable2D<8, 8>(safemagin_param.k_muti_vlgt_rel, safemagin_param.k_muti_vlat_abs,
                                                                         safemagin_param.k_muti_vlgt_vlat_veh, vlgt_rel, fabs(obj.lat_vel));

            predoffst.offs_lat_multi_target = multi_alat_veh + multi_vlgt_vlat_veh;
            break;
        }

        default: {
            predoffst.offs_lat_in_path_primary_target = 0.0f;
            break;
        }
    }
}

float SafetyMarginEvaluator::CalcVerifiedFarEdgeOffset(float width, float inpath_offs) {
    float lat_close_edge = inpath_offs + 0.5f * width;
    float ret            = 0.0f;
    if (lat_close_edge < 0.0f) {
        ret = -0.5f * width - lat_close_edge;
    } else {
        ret = inpath_offs;
    }
    return ret;
}

void SafetyMarginEvaluator::ProjectedBicycleInfo(const CollisionEvaluator &coll_eva, float &half_proj_cycle_length, float &half_proj_cycle_width) {
#if 0
  // projected bicycle width
  float proj_bike_width = 0.0f;
  if (obj.speed > safemagin_param.k_min_bike_spd_thd) {
    proj_bike_width = 0;
  } else {
    proj_bike_width = safemagin_param.k_bike_width_offset;
  }
  half_proj_cycle_width = 0.5f * proj_bike_width;
  half_proj_cycle_length = 0.0f;
#else
    float proj_bike_width = 0.0f;
    if (true == coll_eva.motion_type.stationary) {
        proj_bike_width = safemagin_param.k_bike_width_offset;
    } else {
        proj_bike_width = safemagin_param.k_bike_width_offset * fabsf(cos_heading) + safemagin_param.k_bike_length_offset * fabsf(sin_heading);
    }
    half_proj_cycle_length = 0.0f;
    half_proj_cycle_width  = 0.5f * proj_bike_width;
#endif
}

} // namespace tap
} // namespace senseAD
