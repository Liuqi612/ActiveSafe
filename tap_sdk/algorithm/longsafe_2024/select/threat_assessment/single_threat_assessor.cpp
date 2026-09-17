#include "single_threat_assessor.h"

#include "math/lookuptable/lookuptable.h"
#include "longsafe_cal.h"

namespace senseAD {
namespace tap {
AsSingleThreatAssessor::AsSingleThreatAssessor() {
}

AsSingleThreatAssessor::~AsSingleThreatAssessor() = default;

AsThreatAssessorCal ta_param;
AsPrimDataForIntv   AsSingleThreatAssessor::GetIntvPrimData() const {
    return prim_data_intv;
}
AsPrimDataForWarn AsSingleThreatAssessor::GetWarnPrimData() const {
    return prim_data_warn;
}

void AsSingleThreatAssessor::FindPrimaryTargetForWarn(const active_safety::AsObstacle &obj, const AsObstacleData &obj_data,
                                                      const AsEgoPath &curv_path, const AsVseOut &vse_out) {
    if (CheckEnableForIntv(obj, obj_data.GetCollisionEvalData(), obj_data.GetInpathData(), obj_data.GetSafeMarginEvalData().pred_ttr_valid) ==
        false) {
        return;
    }
    // Required Longitudinal Acceleration Computer For Warn
    // const zero now.
    float drv_react_ti = 0.0F;
    float pred_time    = drv_react_ti + ta_param.k_driver_brk_dely_time;

    float algt_req_warn = RequireLgtAccelerationCalc(obj, obj_data.GetCollisionEvalData(), curv_path, vse_out,
                                                     obj_data.GetInpathData().GetResultData().inpath_long_pred,
                                                     obj_data.GetSafeMarginEvalData().predict_offset.offs_lgt_long_pred,
                                                     obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_long_pred, pred_time);

    // Min Lgt Position selector
    if (obj.long_posn < m_prim_posnlgt_warn.obj.long_posn) {
        m_prim_posnlgt_warn.new_ta_found = true;
        m_prim_posnlgt_warn.obj          = obj;
        m_prim_posnlgt_warn.obj_data     = obj_data;
    } else {
        // do nothing
    }
    // Min Lgt Acceleration selector
    if (algt_req_warn < m_prim_algt_warn.a_lgt_req) {
        m_prim_algt_warn.a_lgt_req    = algt_req_warn;
        m_prim_algt_warn.new_ta_found = true;
        m_prim_algt_warn.obj          = obj;
        m_prim_algt_warn.obj_data     = obj_data;
    } else {
        // do nothing
    }

    // Primary Target selector for warn
    if (m_prim_algt_warn.a_lgt_req < 0.0F) {
        prim_data_warn.prim_tgt = m_prim_algt_warn;
    } else {
        prim_data_warn.prim_tgt = m_prim_posnlgt_warn;
    }

    if (((true == m_prim_algt_warn.new_ta_found) && (m_prim_algt_warn.a_lgt_req < 0.0F)) || (m_prim_posnlgt_warn.new_ta_found)) {
        prim_data_warn.prim_tgt.new_ta_found = true;
    } else {
        // do thing
    }
}

void AsSingleThreatAssessor::FindPrimaryTargetForIntv(const active_safety::AsObstacle &obj, const AsObstacleData &obj_data,
                                                      const AsEgoPath &curv_path, const AsVseOut &vse_out) {
    // Check if enable for intv, if not,do not update primary target info.
    if (CheckEnableForIntv(obj, obj_data.GetCollisionEvalData(), obj_data.GetInpathData(), obj_data.GetSafeMarginEvalData().pred_ttr_valid) ==
        false) {
        return;
    }
    // the estimator lateral acceleration for intv
    LateralAccForIntv lat_high_threat_intv;

    float brakedelay_time = CalcBrakeDelayTime(vse_out);

    // Required Longitudinal Acceleration computer For Intv
    float algt_req_intv = RequireLgtAccelerationCalc(obj, obj_data.GetCollisionEvalData(), curv_path, vse_out,
                                                     obj_data.GetInpathData().GetResultData().inpath_short_pred,
                                                     obj_data.GetSafeMarginEvalData().predict_offset.offs_lgt_short_pred,
                                                     obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_short_pred, brakedelay_time);

    // Required Lateral Acceleration computer For Intv
    LateralAccForIntv lat_acc_ttr =
        LatAccelerationEstimatorCalc(obj, obj_data.GetCollisionEvalData(), vse_out, obj_data.GetInpathData().GetResultData().inpath_short_pred,
                                     obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_short_pred, obj_data.GetCollisionEvalData().ttr);
    if (SWITCH_FOR_TTM) {
        // Not use consider the ttm for intv.
        LateralAccForIntv lat_acc_ttm =
            LatAccelerationEstimatorCalc(obj, obj_data.GetCollisionEvalData(), vse_out, obj_data.GetInpathData().GetResultData().inpath_short_pred,
                                         obj_data.GetSafeMarginEvalData().predict_offset.offs_lat_short_pred, obj_data.GetCollisionEvalData().ttm);

        // Find Highest Lateral Threat
        if (fabsf(lat_acc_ttr.a_lat_req) > fabsf(lat_acc_ttm.a_lat_req)) {
            lat_high_threat_intv.a_lat_req   = lat_acc_ttr.a_lat_req;
            lat_high_threat_intv.pos_lat_rel = lat_acc_ttr.pos_lat_rel;
            lat_high_threat_intv.side_lat    = lat_acc_ttr.side_lat;
        } else {
            lat_high_threat_intv.a_lat_req   = lat_acc_ttm.a_lat_req;
            lat_high_threat_intv.pos_lat_rel = lat_acc_ttm.pos_lat_rel;
            lat_high_threat_intv.side_lat    = lat_acc_ttm.side_lat;
        }
    } else {
        lat_high_threat_intv.a_lat_req   = lat_acc_ttr.a_lat_req;
        lat_high_threat_intv.pos_lat_rel = lat_acc_ttr.pos_lat_rel;
        lat_high_threat_intv.side_lat    = lat_acc_ttr.side_lat;
    }

    // Find primary target for intv according to longtudinal position
    if (obj.long_posn < m_prim_posnlgt_intv.obj.long_posn) {
        m_prim_posnlgt_intv.a_lgt_req    = algt_req_intv;
        m_prim_posnlgt_intv.a_lat_req    = lat_high_threat_intv.a_lat_req;
        m_prim_posnlgt_intv.new_ta_found = true;
        m_prim_posnlgt_intv.obj          = obj;
        m_prim_posnlgt_intv.obj_data     = obj_data;
    } else {
        // do nothing
    }
    // Find primary target for intv according to longtudinal acceleration
    if (algt_req_intv < m_prim_algt_intv.a_lgt_req) {
        m_prim_algt_intv.a_lat_req    = lat_high_threat_intv.a_lat_req;
        m_prim_algt_intv.a_lgt_req    = algt_req_intv;
        m_prim_algt_intv.new_ta_found = true;
        m_prim_algt_intv.obj          = obj;
        m_prim_algt_intv.obj_data     = obj_data;
    } else {
        // do nothing
    }
    // Find primary target for intv according to lateral acceleration
    // Need add the confidence
    if (fabsf(lat_high_threat_intv.a_lat_req) > fabsf(m_prim_alat_intv.a_lat_req)) {
        m_prim_alat_intv.a_lgt_req    = algt_req_intv;
        m_prim_alat_intv.a_lat_req    = lat_high_threat_intv.a_lat_req;
        m_prim_alat_intv.new_ta_found = true;
        m_prim_alat_intv.obj          = obj;
        m_prim_alat_intv.obj_data     = obj_data;
    } else {
        // do nothing
    }

    // Find Primary Target For Intv
    if (fabsf(m_prim_alat_intv.a_lat_req) > 2.0F) {
        prim_data_intv.prim_tgt = m_prim_alat_intv;
    } else if (m_prim_algt_intv.a_lgt_req < -0.5F) {
        prim_data_intv.prim_tgt = m_prim_algt_intv;
    } else {
        prim_data_intv.prim_tgt = m_prim_posnlgt_intv;
    }
}

bool AsSingleThreatAssessor::CheckEnableForWarn(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                const AsInPathDecision &ip_des, const AsVseOut &vse_out) {
    bool obj_ena_for_warn = false;
    // Check if Quality is OK for Warn
#if ENABLE_WARN_ONLY_USE_CIPV
    if (obj.m_is_cipv) {
        obj_ena_for_warn = true;
    } else {
        obj_ena_for_warn = false;
    }
#else
    bool is_qulity_ok_for_warn = false;
    if ((coll_eval.motion_type.obs_is_motor_veh == true || obj.object_class == active_safety::ObjectClass::BICYCLE) && (coll_eval.ttr < 4.0F) &&
        (vse_out.speed < ta_param.k_max_spd_warn_qly_check)) {
        is_qulity_ok_for_warn = true;
    } else {
        if (obj.object_class == active_safety::ObjectClass::PEDESTRIAN) {
            if (obj.vis_trkID > 0) {
                is_qulity_ok_for_warn = true;
            } else {
                is_qulity_ok_for_warn = false;
            }
        } else {
        }
    }
    // Check vehicles of unknown class
    bool is_no_sta_unkown_class = false;
    if (obj.object_class == active_safety::ObjectClass::UNIDENTIFIED_VEHICLE) {
        if (coll_eval.motion_type.stationary) {
            is_no_sta_unkown_class = false;
        } else {
            is_no_sta_unkown_class = true;
        }
    } else {
        is_no_sta_unkown_class = true;
    }
    // Check oncoming object conditions
    bool on_coming_ok_for_warn = false;
    if (((obj.long_vel < ta_param.k_max_spd_mov_to_self_for_warn) && (!coll_eval.motion_type.obs_is_motor_veh))) {
        on_coming_ok_for_warn = false;
    } else {
        on_coming_ok_for_warn = true;
    }
    // Check confirmation time
    bool obj_confirmed = true;

    // Check the Object Enable for warn
    if ((is_qulity_ok_for_warn && is_no_sta_unkown_class && on_coming_ok_for_warn && obj_confirmed &&
                          ip_des.GetResultData().inpath_long_pred.in_path && obj.long_posn <= ta_param.k_max_target_select_long_pos_thres)) {
        obj_ena_for_warn = true;
    } else {
        obj_ena_for_warn = false;
    }
#endif
    return obj_ena_for_warn;
}

bool AsSingleThreatAssessor::CheckEnableForIntv(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                const AsInPathDecision &ip_des, bool predict_valid) {
    bool obj_ena_for_intv = false;
    // Check if Quality is OK for Interve
    bool quality_ok_for_intv = true;
    // Check Speed
    bool spd_ok_for_intv = false;
    // fast on comming vehicle not as aeb target
    if ((obj.speed > ta_param.k_max_spd_mov_to_self_for_intv) && coll_eval.motion_type.moving_oncoming && coll_eval.motion_type.obs_is_vehicle) {
        spd_ok_for_intv = false;
    } else {
        spd_ok_for_intv = true;
    }
    // Check Prediction Vaild for this object
    bool pred_valid_for_intv = false;
    if ((obj.speed > ta_param.k_min_pred_spd_for_intv) && coll_eval.motion_type.moving_oncoming && coll_eval.motion_type.obs_is_motor_veh &&
        (!predict_valid)) {
        pred_valid_for_intv = false;
    } else {
        pred_valid_for_intv = true;
    }
    // Check the object enable for interve
    bool cmbb_active = false;
    if (quality_ok_for_intv && spd_ok_for_intv && ip_des.GetResultData().inpath_short_pred.in_path && (pred_valid_for_intv || cmbb_active) &&
        obj.long_posn <= ta_param.k_max_target_select_long_pos_thres) {
        obj_ena_for_intv = true;
    } else {
        obj_ena_for_intv = false;
    }
    return obj_ena_for_intv;
}

void AsSingleThreatAssessor::ThreatAssesorForWarn(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                  const SafetyMarginEvaluator &safemargin_eval, const AsInPathDecision &ip_des,
                                                  const AsEgoPath &curv_path, const AsVseOut &vse_out) {
    float predtime = ta_param.k_driver_brk_dely_time;
    if (prim_data_warn.prim_tgt.new_ta_found) {
        // Lateral simpale lateral acceleration Estimator
        LateralAccForIntv lat_acc_warn        = LatAccelerationEstimatorCalc(obj, coll_eval, vse_out, ip_des.GetResultData().inpath_long_pred,
                                                                      safemargin_eval.predict_offset.offs_lat_long_pred, coll_eval.ttr);
        prim_data_warn.mtn_req.a_lat_req      = lat_acc_warn.a_lat_req;
        prim_data_warn.mtn_req.a_lat_req      = fmax(prim_data_warn.mtn_req.a_lat_req, ta_param.k_min_a_lat_req_limit_for_warn);
        prim_data_warn.mtn_req.a_lat_req      = fmin(prim_data_warn.mtn_req.a_lat_req, ta_param.k_max_a_lat_req_limit_for_warn);
        prim_data_warn.mtn_req.a_lat_quality  = 1.0F;
        prim_data_warn.mtn_req.a_neg_lgt_warn = prim_data_warn.mtn_req.a_neg_lgt_warn;
        prim_data_warn.mtn_req.a_neg_lgt_warn = fmax(prim_data_warn.mtn_req.a_neg_lgt_warn, ta_param.k_min_a_lat_req_limit_for_warn);
        prim_data_warn.mtn_req.a_neg_lgt_warn = fmin(prim_data_warn.mtn_req.a_neg_lgt_warn, 0.0F);
        prim_data_warn.mtn_req.a_neg_lgt_intv = RequireLgtAccelerationCalc(
            obj, coll_eval, curv_path, vse_out, ip_des.GetResultData().inpath_short_pred, safemargin_eval.predict_offset.offs_lgt_short_pred,
            safemargin_eval.predict_offset.offs_lat_short_pred, predtime);
        prim_data_warn.mtn_req.a_neg_lgt_intv = fmax(prim_data_warn.mtn_req.a_neg_lgt_intv, ta_param.k_min_a_lat_req_limit_for_warn);
        prim_data_warn.mtn_req.a_neg_lgt_intv = fmin(prim_data_warn.mtn_req.a_neg_lgt_intv, 0.0F);
    } else {
        prim_data_warn.mtn_req.a_lat_req      = 0.0F;
        prim_data_warn.mtn_req.a_lat_quality  = 0.0F;
        prim_data_warn.mtn_req.a_neg_lgt_warn = 0.0F;
        prim_data_warn.mtn_req.a_neg_lgt_intv = 0.0F;
    }
}

void AsSingleThreatAssessor::ThreatAssesorForIntv(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                  const SafetyMarginEvaluator &safemargin_eval, const AsInPathDecision &ip_des,
                                                  const AsVseOut &vse_out) {
    if (prim_data_intv.prim_tgt.new_ta_found) {
        // Find the highest lateral threat
        LateralAccForIntv lat_ttr_intv = LatAccelerationEstimatorCalc(obj, coll_eval, vse_out, ip_des.GetResultData().inpath_short_pred,
                                                                      safemargin_eval.predict_offset.offs_lat_short_pred, coll_eval.ttr);
        if (SWITCH_FOR_TTM) {
            LateralAccForIntv lat_ttm_intv = LatAccelerationEstimatorCalc(obj, coll_eval, vse_out, ip_des.GetResultData().inpath_short_pred,
                                                                          safemargin_eval.predict_offset.offs_lat_short_pred, coll_eval.ttm);
            if (fabsf(lat_ttr_intv.a_lat_req) > fabsf(lat_ttm_intv.a_lat_req)) {
                prim_data_intv.mtn_req.a_lat_req = lat_ttr_intv.a_lat_req;
            } else {
                prim_data_intv.mtn_req.a_lat_req = lat_ttm_intv.a_lat_req;
            }
        } else {
            prim_data_intv.mtn_req.a_lat_req = lat_ttr_intv.a_lat_req;
        }
        prim_data_intv.mtn_req.a_lat_quality = 1.0F;
        prim_data_intv.mtn_req.ttc_value     = coll_eval.ttr;
    } else {
        prim_data_intv.mtn_req.a_lat_req       = 0.0F;
        prim_data_intv.mtn_req.a_lat_quality   = 0.0F;
        prim_data_intv.mtn_req.a_neg_lgt       = 0.0F;
        prim_data_intv.mtn_req.a_pos_lgt       = 0.0F;
        prim_data_intv.mtn_req.crvt_left       = 0.0F;
        prim_data_intv.mtn_req.crvt_rate_left  = 0.0F;
        prim_data_intv.mtn_req.crvt_right      = 0.0F;
        prim_data_intv.mtn_req.crvt_rate_right = 0.0F;
        prim_data_intv.mtn_req.ttc_value       = 0.0F;
    }
}

float AsSingleThreatAssessor::CalcBrakeDelayTime(const AsVseOut &vse_out) const {
    float ret = 0.0F;
    ret       = LookUpTable::LookupTable1D<10>(ta_param.k_ego_algt, ta_param.k_brake_delay_value, vse_out.long_accel);

    ret = fmaxf(ta_param.k_min_brakedelay_thd, ret);
    ret = fminf(ta_param.k_max_brakedelay_thd, ret);
    return ret;
}

float AsSingleThreatAssessor::RequireLgtAccelerationCalc(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                         const AsEgoPath &curv_path, const AsVseOut &vse_out, PredictObjMotion pred_motion,
                                                         float offset_lgt, float offset_lat, float pred_time) {
    // input variable adapt
    // Predict object
    PredictObjMotion obj_pred_motion = PredictObjectMotion(obj, coll_eval, pred_motion, pred_time);

    // Predict vse_out position
    EgoMotionStateAtTime ego_pred_pos = curv_path.GetHostState(pred_time);

    // Translate and rotate coordination system
    PredictObjMotion obj_trans_motion = TransRotateCoordSys(obj_pred_motion, ego_pred_pos);

    // Check prediction validity
    bool use_predict_value = false;
    use_predict_value      = CheckPredictionValidity(obj, coll_eval, curv_path.GetEndTimeOfPath(), pred_time);

    // Linear movement predictor with stop host longitual
    float ego_v_lgt = vse_out.vcs_long_vel;
    float ego_a_lgt = vse_out.long_accel;
    float ego_posn  = 0.0F;
    AsInPathDecision::LinearMovementPredictorWithStop(true, ego_posn, ego_v_lgt, ego_a_lgt, pred_time);

    // Relative Heading and Rotation
    RelativePose obj_rel_pos =
        RelativePositionCalc(coll_eval.bounding_box, coll_eval.motion_type, ego_pred_pos.heading_angle, obj_pred_motion.heading);

    // Required Longitudinal Acceleration start
    // Check Position of mearsured point
    bool on_distance_side = false;
    if (((fabsf(obj_rel_pos.heading) < static_cast<float>(M_PI_2)) && (active_safety::AS_OBS_MP_MOV_TO_SELF == obj.motion_pattern)) ||
        ((!(fabsf(obj_rel_pos.heading) < static_cast<float>(M_PI_2))) && (active_safety::AS_OBS_MP_MOV_FROM_SELF == obj.motion_pattern))) {
        on_distance_side = true;
    } else {
        on_distance_side = false;
    }

    // Lateral close and far Edge distance include offset calculation
    EdgeDistance obj_edge_dist = LateralEdgeDistCalc(vse_out, obj_rel_pos, coll_eval.bounding_box, obj_trans_motion, offset_lat, on_distance_side);

    // Define relative speed and acceleration
    float v_lat_rel = 0.0F;
    float a_lat_rel = 0.0F;
    // the threshold should be discussed
    if (fabsf(obj_trans_motion.v_lat) < 0.3F) {
        a_lat_rel = 0.0F;
    } else {
        a_lat_rel = obj_trans_motion.a_lat;
    }
    v_lat_rel = obj_trans_motion.v_lat;

    // Determine lateral closet side
    bool ego_left_closet = false;
    if (((!(fabs(obj_trans_motion.v_lat) > 0.01F)) && (obj_trans_motion.p_lat > 0.0F)) || (obj_trans_motion.v_lat < 0.0F)) {
        ego_left_closet = true;
    } else {
        ego_left_closet = false;
    }

    // Actual Close And Far Edge Distance calculation
    float close_edge_dist = 0.0F;
    float far_edge_dist   = 0.0F;
    if (true == ego_left_closet) {
        close_edge_dist = obj_edge_dist.closet_dist_l;
        far_edge_dist   = obj_edge_dist.far_dist_l;
    } else {
        close_edge_dist = obj_edge_dist.closet_dist_r;
        far_edge_dist   = obj_edge_dist.far_dist_r;
    }

    // Lateral ttr Computer
    float ttr = LateralTtcCalc(ego_left_closet, v_lat_rel, a_lat_rel, obj_edge_dist.closet_dist_l, obj_edge_dist.closet_dist_r);

    // Lateral ttp Computer
    float ttp = LateralTtcCalc(ego_left_closet, v_lat_rel, a_lat_rel, obj_edge_dist.far_dist_l, obj_edge_dist.far_dist_r);
    // Modify ttr and  ttp  at Same Speed And Acceleration
    if ((fabs(obj_trans_motion.v_lat) < 0.01F) && (fabs(obj_trans_motion.a_lat) < 0.01F)) {
        bool neg_clost_dist = false;
        bool neg_far_dist   = false;
        if (close_edge_dist < 0.0F) {
            neg_clost_dist = true;
        } else {
            neg_clost_dist = false;
        }

        if (far_edge_dist < 0.0F) {
            neg_far_dist = true;
        } else {
            neg_far_dist = false;
        }

        if (neg_clost_dist ^ neg_far_dist) {
            ttr = -MAX_TTC_THD;
        } else {
            ttr = MAX_TTC_THD;
        }
        ttp = MAX_TTC_THD;

    } else {
        // do nothing
    }

    // Required Acceleration for Laterally Moving object
    float posn_lgt_rel = obj_trans_motion.p_lgt - vse_out.host_dist_to_front - offset_lgt;
    float vlgt_rel     = obj_trans_motion.v_lgt - ego_v_lgt;
    if (fabsf(ttr) < MAX_TTC_THD) {
        AsInPathDecision::AsInPathDecision::LinearMovementPredictorWithStop(false, posn_lgt_rel, vlgt_rel, obj_trans_motion.a_lgt, ttr);
    } else {
        // do nothing
    }

    float algt_req_lat = (2.0F * (posn_lgt_rel - ego_v_lgt * ttp)) / (ttp * ttp);
    // Required Acceleration for in path object
    float algt_req_inpath =
        RequiredAccForInPathObject(obj_trans_motion.a_lgt, obj_trans_motion.v_lgt, posn_lgt_rel, ego_v_lgt, coll_eval.motion_type);

    // Calculate the object stop time
    float obj_stop_time = active_safety::math::Clamp(math::SafeDivide(vlgt_rel, -obj_trans_motion.a_lgt), -ta_param.k_max_stop_time_obj_for_intv,
                                          ta_param.k_max_stop_time_obj_for_intv);
    // Claculate the relative speed when time to zero
    float rel_spd_ttz = math::SafeDivide(-vlgt_rel, obj_trans_motion.a_lgt - algt_req_inpath);
    // Algorithm chooser
    bool obj_never_inpath = false;
    bool obj_outside      = false;
    if ((!(ttr < MAX_TTC_THD)) && (!(ttp < MAX_TTC_THD))) {
        obj_outside = true;
    } else {
        obj_outside = false;
    }
    // Check the obj will never in path
    // 1. obj has already passed
    // 2. obj drives parallel outside path
    if ((ttp < 0.0F) || obj_outside) {
        obj_never_inpath = true;
    } else {
        obj_never_inpath = false;
    }

    float ret = 0.0F;
    if (obj_never_inpath) {
        ret = 0.0F;
    } else {
        // Choose the longtudinal acceleration required from lateral and in path
        // check the lateral condition is fulfilled
        bool lat_enable = false;
        if ((ttp < 100.0F) && (true == use_predict_value) &&
            ((algt_req_lat > 0.0F) || (true == coll_eval.motion_type.moving_oncoming) || ((ttr > rel_spd_ttz) && (rel_spd_ttz > 0.0F)) ||
             ((rel_spd_ttz > ttp) && (obj_stop_time > ttp)))) {
            lat_enable = true;
        } else {
            lat_enable = false;
        }

        if (lat_enable) {
            ret = algt_req_lat;
        } else {
            ret = algt_req_inpath;
        }
    }
    return ret;
}

RelativePose AsSingleThreatAssessor::RelativePositionCalc(BoundingBox boudbox, AsObstacleMotionType motiontype, float ego_heading,
                                                          float obj_heading) {
    RelativePose ret;
    // Check the object moving state
    bool obj_is_sta = motiontype.stationary;

    if (true == obj_is_sta) {
        // Relative sin rotation
        float EgoSinHeading = sinf(ego_heading);
        float EgoCosHeading = cosf(ego_heading);

        ret.sin_rotation = (boudbox.sin_rotation * EgoCosHeading) - (boudbox.cos_rotation * EgoSinHeading);

        // Relative cos rotation
        ret.cos_rotation = (boudbox.cos_rotation * EgoCosHeading) + (boudbox.sin_rotation * EgoSinHeading);

        // Relative heading
        ret.heading = obj_heading - ego_heading;

    } else {
        // Relative heading  and lengthangle
        ret.heading       = obj_heading - ego_heading;
        float lengthangle = 0.0F;
        lengthangle       = active_safety::math::MapAngToInterval(static_cast<float>(M_PI_2), ret.heading);
        ret.heading       = active_safety::math::MapAngToInterval(static_cast<float>(M_PI), ret.heading);

        // Sin  and Cos Relative Rotation calc
        float sin_length_angle = sinf(lengthangle);
        float cos_length_angle = cosf(lengthangle);
        float sign_angle       = math::SafeDivide(fabs(lengthangle), lengthangle);

        if (motiontype.side_closest) {
            ret.sin_rotation = -cos_length_angle * sign_angle;
            ret.cos_rotation = sin_length_angle * sign_angle;
        } else {
            ret.sin_rotation = sin_length_angle;
            ret.cos_rotation = cos_length_angle;
        }
    }
    return ret;
}

EdgeDistance AsSingleThreatAssessor::LateralEdgeDistCalc(const AsVseOut &vse_out, RelativePose rel_pos, BoundingBox boudbox,
                                                         PredictObjMotion transcoord, float offset_lat, bool onside) const {
    (void)(rel_pos);
    EdgeDistance edge_dist;
    // Calculate the sin rotation mod
    float sin_rotation_mod = boudbox.sin_rotation;
    if (boudbox.cos_rotation > 0.0F) {
        // do nothing
    } else {
        sin_rotation_mod = -boudbox.sin_rotation;
    }

    bool proj_to_left  = false;
    bool proj_to_right = false;
    if (((sin_rotation_mod < 0.0F) && onside) || ((sin_rotation_mod > 0.0F) && (!onside))) {
        proj_to_left = true;
    } else {
        proj_to_left = false;
    }
    if (((sin_rotation_mod > 0.0F) && onside) || ((sin_rotation_mod < 0.0F) && (!onside))) {
        proj_to_right = true;
    } else {
        proj_to_right = false;
    }

    // Calculate the rigth and left edge to edge distance
    float abs_proj_lgt    = fabsf(boudbox.length_side_lgt * boudbox.sin_rotation);
    float abs_proj_lat    = fabsf(0.5F * boudbox.length_side_lat * boudbox.cos_rotation);
    float dist_host_left  = 0.0F;
    float dist_host_right = 0.0F;
    if (true == proj_to_left) {
        dist_host_right = transcoord.p_lat + abs_proj_lgt + abs_proj_lat + vse_out.host_width * 0.5F;
    } else {
        dist_host_right = transcoord.p_lat + abs_proj_lat + vse_out.host_width * 0.5F;
    }

    if (true == proj_to_right) {
        dist_host_left = transcoord.p_lat - abs_proj_lat - abs_proj_lgt - vse_out.host_width * 0.5F;
    } else {
        dist_host_left = transcoord.p_lat - abs_proj_lat - vse_out.host_width * 0.5F;
    }
    // Lateral far and close edge including offset.
    float offs_lat_in_path_close_edge = offset_lat;
    float offs_lat_in_path_far_edge   = offset_lat;
    edge_dist.closet_dist_l           = dist_host_left - offs_lat_in_path_close_edge;
    edge_dist.closet_dist_r           = -dist_host_right - offs_lat_in_path_close_edge;

    edge_dist.far_dist_l = dist_host_right + offs_lat_in_path_far_edge;
    edge_dist.far_dist_r = -dist_host_left + offs_lat_in_path_far_edge;

    return edge_dist;
}

float AsSingleThreatAssessor::LateralTtcCalc(bool left_closest, float v_lat, float a_lat, float dist_left, float dist_right) {
    float time_to_intsec = MAX_TTC_THD;
    // If left edge is the closet.
    if (left_closest) {
        // Check the Left solution is exists
        bool no_solution_existleft   = CheckIfSolutionExist(dist_left, v_lat, a_lat);
        bool no_solution_exist_right = CheckIfSolutionExist(dist_right, -v_lat, -a_lat);
        if (no_solution_existleft && no_solution_exist_right) {
            time_to_intsec = MAX_TTC_THD;
        } else {
            if (!no_solution_existleft) {
                time_to_intsec = CollisionEvaluator::SolveTTISolution(v_lat, a_lat, dist_left);
            } else {
                time_to_intsec = CollisionEvaluator::SolveTTISolution(-v_lat, -a_lat, dist_right);
            }
        }
    } else {
        // If right edge is the closet.
        // Check the Left and right solution is exists
        bool NoSolutionExistleft  = CheckIfSolutionExist(dist_left, v_lat, a_lat);
        bool NoSolutionExistRight = CheckIfSolutionExist(dist_right, -v_lat, -a_lat);
        if (NoSolutionExistleft && NoSolutionExistRight) {
            time_to_intsec = MAX_TTC_THD;
        } else {
            if (!NoSolutionExistRight) {
                time_to_intsec = CollisionEvaluator::SolveTTISolution(-v_lat, -a_lat, dist_right);
            } else {
                time_to_intsec = CollisionEvaluator::SolveTTISolution(v_lat, a_lat, dist_left);
            }
        }
    }
    return time_to_intsec;
}

bool AsSingleThreatAssessor::CheckIfSolutionExist(float dist, float v_rel, float a_rel) {
    // Calc the Rel Distance
    float Rel_Distance = math::SafeDivide(v_rel * v_rel, 2.0F * a_rel);
    // Check the Postive ARel ,whether there has solution
    bool NoSoluPosARel = false;
    if ((dist > Rel_Distance) && (a_rel > 0.0F)) {
        NoSoluPosARel = true;
    } else {
        NoSoluPosARel = false;
    }

    // Check the Postive ARel ,whether there has solution
    bool NoSoluNegARel = false;
    if ((dist < Rel_Distance) && (a_rel < 0.0F)) {
        NoSoluNegARel = true;
    } else {
        NoSoluNegARel = false;
    }

    // Check solution , true = No Solution, false = has solution.
    bool ret = true;
    if (NoSoluNegARel || NoSoluPosARel) {
        ret = true;
    } else {
        ret = false;
    }

    return ret;
}

bool AsSingleThreatAssessor::CheckPredictionValidity(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, float endtimeofpath,
                                                     float pred_time) {
    // Check the Prediciton Within Path Estimatior
    bool pred_ti_within_path_est = false;
    if ((pred_time > 0.0F) && (pred_time < endtimeofpath)) {
        pred_ti_within_path_est = true;
    } else {
        pred_ti_within_path_est = false;
    }

    // Check the Prediction time Below threshold
    bool pred_ti_below_thd = false;
    if (ta_param.k_min_pred_time_thd_for_warn > pred_time) {
        pred_ti_below_thd = true;
    } else {
        pred_ti_below_thd = false;
    }
    // Check Prediction Distance below threshold
    // Check speed above threshold
    // Check confidence for heading

    bool  pre_dst_below_thd = false;
    bool  spd_above_thd     = false;
    bool  heading_valid     = false;
    float pred_dist         = obj.speed * pred_time;
    if (true == coll_eval.motion_type.obs_is_motor_veh) {
        if (pred_dist < ta_param.k_max_pred_dist_thd_for_warn) {
            pre_dst_below_thd = true;
        } else {
            pre_dst_below_thd = false;
        }

        if (ta_param.k_min_pred_spd_thd_for_warn < fabsf(obj.speed)) {
            spd_above_thd = true;
        } else {
            spd_above_thd = false;
        }

        if (ta_param.k_max_pred_spd_thd_for_ag_dir_warn > obj.speed) {
            if (active_safety::FusionSource::SINGLE_TRACKLET != obj.fusion_source) {
                heading_valid = true;
            } else {
                heading_valid = false;
            }

        } else {
            heading_valid = true;
        }
    } else {
        pre_dst_below_thd = true;
        spd_above_thd     = true;
        heading_valid     = true;
    }
    // Check object type
    bool valid_obj_type = false;
    if ((active_safety::ObjectClass::UNIDENTIFIED_VEHICLE != obj.object_class) && (active_safety::ObjectClass::ANIMAL != obj.object_class)) {
        valid_obj_type = true;
    } else {
        valid_obj_type = false;
    }

    // Check the valid of the obj
    bool use_prediction = false;
    if (pred_ti_within_path_est && pred_ti_below_thd && pre_dst_below_thd && spd_above_thd && heading_valid && valid_obj_type) {
        use_prediction = true;
    } else {
        use_prediction = false;
    }
    return use_prediction;
}

float AsSingleThreatAssessor::RequiredAccForInPathObject(float obj_aLgt, float obj_vlgt, float rel_plgt, float ego_vlgt,
                                                         AsObstacleMotionType mot_type) {
    // Check the obj is braking
    bool obj_braking = false;
    if ((mot_type.stationary) || (fabsf(obj_vlgt) < 0.01F) || (obj_vlgt * obj_aLgt < 0.0F)) {
        obj_braking = true;
    } else {
        obj_braking = false;
    }

    float a_lgt_rqrd = 0.0F;
    float vlgt_rel   = obj_vlgt - ego_vlgt;
    float pos_dist   = 2.0F * fmaxf(0.0F, rel_plgt);

    if (obj_braking) {
        // needed acceleration moving parallel object
        float algt_rel_req = vlgt_rel * vlgt_rel * math::SignF(vlgt_rel);
        algt_rel_req       = math::Clamp(math::SafeDivide(algt_rel_req, pos_dist), -5.0F, 5.0F);
        float algt_req     = algt_rel_req + obj_aLgt;

        // check speed at impact for braking object
        float spd_at_impact = math::Clamp(math::SafeDivide(-vlgt_rel, algt_rel_req), -20.0F, 20.0F);
        spd_at_impact       = spd_at_impact * obj_aLgt;
        bool use_parallel   = false;
        if ((obj_vlgt > 0.0F) && ((obj_vlgt + spd_at_impact) > 0.0F) && (spd_at_impact < ego_vlgt)) {
            use_parallel = true;
        } else {
            use_parallel = false;
        }

        if (true == use_parallel) {
            a_lgt_rqrd = algt_req;
        } else {
            // available stopM_PIng distance
            float stop_dist = rel_plgt + 0.5F * math::SafeDivide(obj_vlgt, -obj_aLgt) * obj_vlgt;
            if (stop_dist > 0.0F) {
                a_lgt_rqrd = math::SafeDivide(ego_vlgt * ego_vlgt, -2.0F * stop_dist);
            } else {
                a_lgt_rqrd = -20.0F;
            }
        }
    } else {
        // check the obj is oncoming
        if (mot_type.moving_oncoming) {
            a_lgt_rqrd = 0.0F;
        } else {
            float algt_rel_nobrak = math::Clamp(math::SafeDivide(vlgt_rel * vlgt_rel, pos_dist), -10000.0F, 10000.0F);
            algt_rel_nobrak       = -algt_rel_nobrak * math::SignF(vlgt_rel);
            a_lgt_rqrd            = obj_aLgt - algt_rel_nobrak;
        }
    }

    return a_lgt_rqrd;
}

PredictObjMotion AsSingleThreatAssessor::PredictObjectMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                             PredictObjMotion pre_motion, float pred_time) {
    PredictObjMotion ret;
    // define the pre
    // Prediction type define according to the object motion type
    if (true == coll_eval.motion_type.stationary) {
        // No Prediction
        ret.heading = atan2f(coll_eval.bounding_box.sin_rotation, coll_eval.bounding_box.cos_rotation);

        ret.p_lgt = obj.long_posn;
        ret.v_lgt = 0.0F;
        ret.p_lat = obj.lat_posn;
        ret.v_lat = 0.0F;
        ret.a_lgt = 0.0F;
        ret.a_lat = 0.0F;

    } else if ((false == coll_eval.motion_type.stationary) && (true == coll_eval.motion_type.curved_motion)) {
        // Circular Prediction
        ret = AsInPathDecision::PredictObjectCurveMotion(obj, coll_eval, pre_motion, pred_time);

        ret.curv = pre_motion.curv;
        // predicted cartesian movement
        ret = CalcCatesianMovement(ret);

    } else {
        // Linear Prediction longitudinal
        ret.p_lgt = obj.long_posn;
        ret.v_lgt = obj.long_vel;
        ret.a_lgt = pre_motion.a_lgt;
        AsInPathDecision::LinearMovementPredictorWithStop(true, ret.p_lgt, ret.v_lgt, ret.a_lgt, pred_time);

        // Linear prediction lateral movement
        ret.p_lat = obj.lat_posn;
        ret.v_lat = obj.lat_vel;
        ret.a_lat = pre_motion.a_lat;
        AsInPathDecision::LinearMovementPredictorWithStop(false, ret.p_lat, ret.v_lat, ret.a_lat, pred_time);

        if (coll_eval.motion_type.obs_is_vehicle) {
            ret.heading = obj.heading;
        } else {
            ret.heading = atan2f(ret.v_lat, ret.v_lgt);
        }
    }

    return ret;
}

LateralAccForIntv AsSingleThreatAssessor::LatAccelerationEstimatorCalc(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                                       const AsVseOut &vse_out, PredictObjMotion pred_motion,
                                                                       float offs_lat_short_pred, float ttc_lgt) const {
    LateralAccForIntv ret;
    // Calculate the object position at ttr time
    float ttr_filter   = 0.0F;
    float obj_lat_posn = 0.0F;
    if (coll_eval.motion_type.obs_is_vehicle) {
        // min stop time calculation
        float stop_time = -math::SafeDivide(obj.speed, pred_motion.a);
        if (stop_time > 0.0F) {
            ttr_filter = fminf(stop_time, ttc_lgt);
        } else {
            ttr_filter = ttc_lgt;
        }
    } else {
        ttr_filter = ttc_lgt;
    }
    float lat_posn_acc = 0.5F * pred_motion.a_lat * ttr_filter * ttr_filter;
    obj_lat_posn       = obj.lat_posn + obj.lat_vel * ttr_filter + lat_posn_acc;
    // Calculate the vse_out position at ttr time
    float ego_ttr      = 0.0F;
    float ego_lat_posn = 0.0F;
    float ego_stop_ti  = -math::SafeDivide(vse_out.speed, vse_out.long_accel);
    if (ego_stop_ti > 0.0F) {
        ego_ttr = fminf(ego_stop_ti, ttc_lgt);
    } else {
        ego_ttr = ttc_lgt;
    }
    float ego_a_lat = vse_out.lat_accel;
    ego_lat_posn    = 0.5F * ego_a_lat * ego_ttr * ego_ttr;

    // Calcuate the relative position before projection
    ret.pos_lat_rel = obj_lat_posn - ego_lat_posn;

    // Projection adaption
    float left_most_point = 0.0F;
    float rigt_most_point = 0.0F;
    float proj_side_lgt   = fabsf(coll_eval.bounding_box.length_side_lgt * coll_eval.bounding_box.sin_rotation);
    float proj_side_lat   = fabsf(0.5F * coll_eval.bounding_box.length_side_lat * coll_eval.bounding_box.cos_rotation);

    if (coll_eval.bounding_box.sin_rotation > 0.0F) {
        left_most_point = ret.pos_lat_rel + proj_side_lgt + proj_side_lat;
        rigt_most_point = ret.pos_lat_rel - proj_side_lat;
    } else {
        left_most_point = ret.pos_lat_rel + proj_side_lat;
        rigt_most_point = ret.pos_lat_rel - proj_side_lat - proj_side_lgt;
    }

    ret.side_lat    = left_most_point - rigt_most_point;
    ret.pos_lat_rel = 0.5F * (left_most_point + rigt_most_point);
    // Calculate the required lateral acceleration
    float halfwidth = 0.5F * (ret.side_lat + vse_out.host_width);
    ret.a_lat_req   = CalcRequiredAccLat(ret.pos_lat_rel, ttc_lgt, halfwidth, offs_lat_short_pred);
    return ret;
}

float AsSingleThreatAssessor::CalcRequiredAccLat(float rel_pos, float ttr, float width, float offlat) const {
    // lateral distance limit
    float left_dist = rel_pos + width + offlat;
    left_dist       = fminf(left_dist, ta_param.k_max_dist_movment_for_intv);

    float right_dist = rel_pos - width - offlat;
    right_dist       = fmaxf(right_dist, -ta_param.k_max_dist_movment_for_intv);
    // lateral acceleration calculation
    float left_a_req = math::SafeDivide(2.0F * left_dist, ttr * ttr);
    left_a_req       = fmaxf(left_a_req, 0.0F);

    float right_a_req = math::SafeDivide(2.0F * right_dist, ttr * ttr);
    right_a_req       = fminf(right_a_req, 0.0F);

    // lateral acceleration filter
    float ret = 0.0F;
    if (ttr > 0.0F) {
        if (left_a_req < fabsf(right_a_req)) {
            ret = left_a_req;
        } else {
            ret = right_a_req;
        }
    } else {
        ret = 0.0F;
    }
    return ret;
}

PredictObjMotion AsSingleThreatAssessor::CalcCatesianMovement(PredictObjMotion pre_motion) {
    PredictObjMotion ret;
    ret.v_lat = pre_motion.spd * sinf(pre_motion.heading);
    ret.v_lgt = pre_motion.spd * cosf(pre_motion.heading);

    ret.a_lat = pre_motion.a * sinf(pre_motion.heading) + pre_motion.spd * pre_motion.spd * pre_motion.curv * cosf(pre_motion.heading);
    ret.a_lgt = pre_motion.a * cosf(pre_motion.heading) - pre_motion.spd * pre_motion.spd * pre_motion.curv * sinf(pre_motion.heading);
    return ret;
}

PredictObjMotion AsSingleThreatAssessor::TransRotateCoordSys(const PredictObjMotion &obj_pred, const EgoMotionStateAtTime &ego_pred) {
    PredictObjMotion ret;
    // Calc the vse_out angle direction trigonometric function
    float sinvalue = sinf(ego_pred.heading_angle);
    float cosvalue = cosf(ego_pred.heading_angle);

    // Calc the transformed longitudinal position
    float cos_posn_lgt = (obj_pred.p_lgt - ego_pred.long_pos) * cosvalue;
    float sin_posn_lat = (obj_pred.p_lat - ego_pred.lat_pos) * sinvalue;
    ret.p_lgt          = cos_posn_lgt + sin_posn_lat;

    // Calc the transformed lateral position
    float cos_posn_lat = (obj_pred.p_lat - ego_pred.lat_pos) * cosvalue;
    float sin_posn_lgt = (obj_pred.p_lgt - ego_pred.long_pos) * sinvalue;
    ret.p_lat          = cos_posn_lat - sin_posn_lgt;

    // Calc the transformed longtiudinal spd
    ret.v_lgt = (obj_pred.v_lgt * cosvalue) + (obj_pred.v_lat * sinvalue);
    // Calc the transformed lateral spd
    ret.v_lat = (obj_pred.v_lat * cosvalue) - (obj_pred.v_lgt * sinvalue);
    // Calc the transformed longtiudinal acceleration
    ret.a_lgt = (obj_pred.a_lgt * cosvalue) + (obj_pred.a_lat * sinvalue);
    // Calc the transformed lateral acceleration
    ret.a_lat = (obj_pred.a_lat * cosvalue) - (obj_pred.a_lgt * sinvalue);

    // Remove the Noise
    ret.v_lgt = RemoveNoise(ret.v_lgt, ta_param.k_v_lgt_obj_noise_thd);
    ret.v_lat = RemoveNoise(ret.v_lat, ta_param.k_v_lat_obj_nosie_thd);
    ret.a_lgt = RemoveNoise(ret.a_lgt, ta_param.k_a_lgt_obj_nosie_thd);
    ret.a_lat = RemoveNoise(ret.a_lat, ta_param.k_a_lat_obj_nosie_thd);

    return ret;
}

float AsSingleThreatAssessor::RemoveNoise(float raw, float threshold) {
    float ret;
    if (fabs(raw) < threshold) {
        ret = 0.0F;
    } else {
        ret = raw;
    }
    return ret;
}

void AsSingleThreatAssessor::ResetPrimaryTargetData() {
    // Reset the primary algt intv target data
    m_prim_algt_intv = PrimaryTarget{};

    // Reset the primary alat intv target data
    m_prim_alat_intv = PrimaryTarget{};

    // Reset the primary posn intv target data
    m_prim_posnlgt_intv = PrimaryTarget{};

    // Reset the primary warn target data
    prim_data_intv.prim_tgt = PrimaryTarget{};
    prim_data_intv.mtn_req  = MtnIntvRequired{};

    // Reset the primary alat warn target data
    m_prim_algt_warn = PrimaryTarget{};

    // Reset the primary posn warn target data
    m_prim_posnlgt_warn = PrimaryTarget{};

    // Reset the primary warn target data
    prim_data_warn.prim_tgt = PrimaryTarget{};
    prim_data_warn.mtn_req  = MtnWarnRequired{};
}

} // namespace tap
} // namespace senseAD
