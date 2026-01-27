#include "inpath_decision.h"

#include "math/utils/util_math.h"
#include "longsafe_cal.h"

namespace senseAD {
namespace tap {
InPathDecisionCal inpath_decision_param;
AsInPathDecision::AsInPathDecision() {
}

AsInPathDecision::~AsInPathDecision() noexcept {
}

const InPathData &AsInPathDecision::GetResultData() const {
    return inpath_data;
}
const InPathData &AsInPathDecision::GetCurrentInPathData() const {
    return inpath_curr_data;
}
const InPathData &AsInPathDecision::GetPredictInPathData() const {
    return inpath_pred_data;
}

void AsInPathDecision::ProcessInPathDecision(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                             const SafetyMarginEvaluator &safemargin_eval, const AsVseOut &vse_out,
                                             const AsEgoPath &curv_path) {
    CalInPathDataWithPredictPose(obj, coll_eval, safemargin_eval, vse_out, curv_path);
    CalInPathDataWithCurrentPose(obj, coll_eval, safemargin_eval, vse_out);

    inpath_data = SelectInPathData(obj, coll_eval, vse_out, safemargin_eval.pred_ttr_valid);
    // std::cout << " ArbInPath:"
    //           << static_cast<uint32_t>(inpath_data.inpath_short_pred.in_path)
    //           << " CurrInPath:"
    //           <<
    //           static_cast<uint32_t>(inpath_curr_data.inpath_short_pred.in_path)
    //           << " PredInPath:"
    //           <<
    //           static_cast<uint32_t>(inpath_pred_data.inpath_short_pred.in_path)
    //           <<"lat_posn"<<obj.lat_posn
    //           <<"lat_vel"<<obj.lat_vel
    //            <<"long_posn"<<obj.long_posn
    //           <<"long_vel"<<obj.long_vel
    //           << std::endl;
}

void AsInPathDecision::Clear() {
    corner_points.close_left_lgt   = 0.0f;
    corner_points.close_left_lat   = 0.0f;
    corner_points.close_right_lgt  = 0.0f;
    corner_points.close_right_lat  = 0.0f;
    corner_points.remote_left_lgt  = 0.0f;
    corner_points.remote_left_lat  = 0.0f;
    corner_points.remote_right_lgt = 0.0f;
    corner_points.remote_right_lat = 0.0f;

    corner_corved_points.close_left_lgt_corved   = 0.0f;
    corner_corved_points.close_left_lat_corved   = 0.0f;
    corner_corved_points.close_right_lgt_corved  = 0.0f;
    corner_corved_points.close_right_lat_corved  = 0.0f;
    corner_corved_points.remote_left_lgt_corved  = 0.0f;
    corner_corved_points.remote_left_lat_corved  = 0.0f;
    corner_corved_points.remote_right_lgt_corved = 0.0f;
    corner_corved_points.remote_right_lat_corved = 0.0f;

    inpath_curr_data.inpath_long_pred.p_lgt           = 0.0f;
    inpath_curr_data.inpath_long_pred.p_lat           = 0.0f;
    inpath_curr_data.inpath_long_pred.spd             = 0.0f;
    inpath_curr_data.inpath_long_pred.v_lgt           = 0.0f;
    inpath_curr_data.inpath_long_pred.v_lat           = 0.0f;
    inpath_curr_data.inpath_long_pred.heading         = 0.0f;
    inpath_curr_data.inpath_long_pred.a               = 0.0f;
    inpath_curr_data.inpath_long_pred.a_lgt           = 0.0f;
    inpath_curr_data.inpath_long_pred.a_lat           = 0.0f;
    inpath_curr_data.inpath_long_pred.curv            = 0.0f;
    inpath_curr_data.inpath_long_pred.in_path         = 0.0f;
    inpath_curr_data.inpath_long_pred.dist_from_left  = 0.0f;
    inpath_curr_data.inpath_long_pred.dist_from_right = 0.0f;
    inpath_curr_data.inpath_long_pred.pred_offset     = 0.0f;
    inpath_curr_data.inpath_long_pred.manv_type       = 0;

    inpath_pred_data.inpath_long_pred.p_lgt           = 0.0f;
    inpath_pred_data.inpath_long_pred.p_lat           = 0.0f;
    inpath_pred_data.inpath_long_pred.spd             = 0.0f;
    inpath_pred_data.inpath_long_pred.v_lgt           = 0.0f;
    inpath_pred_data.inpath_long_pred.v_lat           = 0.0f;
    inpath_pred_data.inpath_long_pred.heading         = 0.0f;
    inpath_pred_data.inpath_long_pred.a               = 0.0f;
    inpath_pred_data.inpath_long_pred.a_lgt           = 0.0f;
    inpath_pred_data.inpath_long_pred.a_lat           = 0.0f;
    inpath_pred_data.inpath_long_pred.curv            = 0.0f;
    inpath_pred_data.inpath_long_pred.in_path         = 0.0f;
    inpath_pred_data.inpath_long_pred.dist_from_left  = 0.0f;
    inpath_pred_data.inpath_long_pred.dist_from_right = 0.0f;
    inpath_pred_data.inpath_long_pred.pred_offset     = 0.0f;
    inpath_pred_data.inpath_long_pred.manv_type       = 0;

    inpath_data.inpath_long_pred.p_lgt           = 0.0f;
    inpath_data.inpath_long_pred.p_lat           = 0.0f;
    inpath_data.inpath_long_pred.spd             = 0.0f;
    inpath_data.inpath_long_pred.v_lgt           = 0.0f;
    inpath_data.inpath_long_pred.v_lat           = 0.0f;
    inpath_data.inpath_long_pred.heading         = 0.0f;
    inpath_data.inpath_long_pred.a               = 0.0f;
    inpath_data.inpath_long_pred.a_lgt           = 0.0f;
    inpath_data.inpath_long_pred.a_lat           = 0.0f;
    inpath_data.inpath_long_pred.curv            = 0.0f;
    inpath_data.inpath_long_pred.in_path         = 0.0f;
    inpath_data.inpath_long_pred.dist_from_left  = 0.0f;
    inpath_data.inpath_long_pred.dist_from_right = 0.0f;
    inpath_data.inpath_long_pred.pred_offset     = 0.0f;
    inpath_data.inpath_long_pred.manv_type       = 0;

    inpath_curr_data.inpath_short_pred.p_lgt           = 0.0f;
    inpath_curr_data.inpath_short_pred.p_lat           = 0.0f;
    inpath_curr_data.inpath_short_pred.spd             = 0.0f;
    inpath_curr_data.inpath_short_pred.v_lgt           = 0.0f;
    inpath_curr_data.inpath_short_pred.v_lat           = 0.0f;
    inpath_curr_data.inpath_short_pred.heading         = 0.0f;
    inpath_curr_data.inpath_short_pred.a               = 0.0f;
    inpath_curr_data.inpath_short_pred.a_lgt           = 0.0f;
    inpath_curr_data.inpath_short_pred.a_lat           = 0.0f;
    inpath_curr_data.inpath_short_pred.curv            = 0.0f;
    inpath_curr_data.inpath_short_pred.in_path         = 0.0f;
    inpath_curr_data.inpath_short_pred.dist_from_left  = 0.0f;
    inpath_curr_data.inpath_short_pred.dist_from_right = 0.0f;
    inpath_curr_data.inpath_short_pred.pred_offset     = 0.0f;
    inpath_curr_data.inpath_short_pred.manv_type       = 0;

    inpath_pred_data.inpath_short_pred.p_lgt           = 0.0f;
    inpath_pred_data.inpath_short_pred.p_lat           = 0.0f;
    inpath_pred_data.inpath_short_pred.spd             = 0.0f;
    inpath_pred_data.inpath_short_pred.v_lgt           = 0.0f;
    inpath_pred_data.inpath_short_pred.v_lat           = 0.0f;
    inpath_pred_data.inpath_short_pred.heading         = 0.0f;
    inpath_pred_data.inpath_short_pred.a               = 0.0f;
    inpath_pred_data.inpath_short_pred.a_lgt           = 0.0f;
    inpath_pred_data.inpath_short_pred.a_lat           = 0.0f;
    inpath_pred_data.inpath_short_pred.curv            = 0.0f;
    inpath_pred_data.inpath_short_pred.in_path         = 0.0f;
    inpath_pred_data.inpath_short_pred.dist_from_left  = 0.0f;
    inpath_pred_data.inpath_short_pred.dist_from_right = 0.0f;
    inpath_pred_data.inpath_short_pred.pred_offset     = 0.0f;
    inpath_pred_data.inpath_short_pred.manv_type       = 0;

    inpath_data.inpath_short_pred.p_lgt           = 0.0f;
    inpath_data.inpath_short_pred.p_lat           = 0.0f;
    inpath_data.inpath_short_pred.spd             = 0.0f;
    inpath_data.inpath_short_pred.v_lgt           = 0.0f;
    inpath_data.inpath_short_pred.v_lat           = 0.0f;
    inpath_data.inpath_short_pred.heading         = 0.0f;
    inpath_data.inpath_short_pred.a               = 0.0f;
    inpath_data.inpath_short_pred.a_lgt           = 0.0f;
    inpath_data.inpath_short_pred.a_lat           = 0.0f;
    inpath_data.inpath_short_pred.curv            = 0.0f;
    inpath_data.inpath_short_pred.in_path         = 0.0f;
    inpath_data.inpath_short_pred.dist_from_left  = 0.0f;
    inpath_data.inpath_short_pred.dist_from_right = 0.0f;
    inpath_data.inpath_short_pred.pred_offset     = 0.0f;
    inpath_data.inpath_short_pred.manv_type       = 0;

    obj_avoidance.decel_long_pretime  = 0.0f;
    obj_avoidance.decel_short_pretime = 0.0f;
    obj_avoidance.alat_steer          = 0.0f;

    rel_pos_def.heading            = 0.0f;
    rel_pos_def.sin_rotation       = 0.0f;
    rel_pos_def.cos_rotation       = 0.0f;
    rel_pos_def.p_lgt              = 0.0f;
    rel_pos_def.p_lat              = 0.0f;
    rel_pos_def.v_lat              = 0.0f;
    rel_pos_def.point_on_dist_side = false;

    rel_pos_long_time.heading            = 0.0f;
    rel_pos_long_time.sin_rotation       = 0.0f;
    rel_pos_long_time.cos_rotation       = 0.0f;
    rel_pos_long_time.p_lgt              = 0.0f;
    rel_pos_long_time.p_lat              = 0.0f;
    rel_pos_long_time.v_lat              = 0.0f;
    rel_pos_long_time.point_on_dist_side = false;

    rel_pos_short_time.heading            = 0.0f;
    rel_pos_short_time.sin_rotation       = 0.0f;
    rel_pos_short_time.cos_rotation       = 0.0f;
    rel_pos_short_time.p_lgt              = 0.0f;
    rel_pos_short_time.p_lat              = 0.0f;
    rel_pos_short_time.v_lat              = 0.0f;
    rel_pos_short_time.point_on_dist_side = false;

    rel_pos_turn_left.heading            = 0.0f;
    rel_pos_turn_left.sin_rotation       = 0.0f;
    rel_pos_turn_left.cos_rotation       = 0.0f;
    rel_pos_turn_left.p_lgt              = 0.0f;
    rel_pos_turn_left.p_lat              = 0.0f;
    rel_pos_turn_left.v_lat              = 0.0f;
    rel_pos_turn_left.point_on_dist_side = false;

    rel_pos_turn_right.heading            = 0.0f;
    rel_pos_turn_right.sin_rotation       = 0.0f;
    rel_pos_turn_right.cos_rotation       = 0.0f;
    rel_pos_turn_right.p_lgt              = 0.0f;
    rel_pos_turn_right.p_lat              = 0.0f;
    rel_pos_turn_right.v_lat              = 0.0f;
    rel_pos_turn_right.point_on_dist_side = false;

    in_path_info.in_path_default          = false;
    in_path_info.in_path_pred_zero_length = false;
    in_path_info.in_path_pred_long_time   = false;
    in_path_info.in_path_pred_short_time  = false;
    in_path_info.in_path_pred_trun_left   = false;
    in_path_info.in_path_pred_trun_right  = false;

    proj_dist_info.proj_dist_defult.dist_from_host_left      = 0.0f;
    proj_dist_info.proj_dist_zero_length.dist_from_host_left = 0.0f;
    proj_dist_info.proj_dist_long_pred.dist_from_host_left   = 0.0f;
    proj_dist_info.proj_dist_short_pred.dist_from_host_left  = 0.0f;
    proj_dist_info.proj_dist_trun_left.dist_from_host_left   = 0.0f;
    proj_dist_info.proj_dist_trun_right.dist_from_host_left  = 0.0f;

    proj_dist_info.proj_dist_defult.dist_from_host_right      = 0.0f;
    proj_dist_info.proj_dist_zero_length.dist_from_host_right = 0.0f;
    proj_dist_info.proj_dist_long_pred.dist_from_host_right   = 0.0f;
    proj_dist_info.proj_dist_short_pred.dist_from_host_right  = 0.0f;
    proj_dist_info.proj_dist_trun_left.dist_from_host_right   = 0.0f;
    proj_dist_info.proj_dist_trun_right.dist_from_host_right  = 0.0f;

    obj_try_brake = false;
}

void AsInPathDecision::CalInPathDataWithPredictPose(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                    const SafetyMarginEvaluator &safemargin_eval, const AsVseOut &vse_out,
                                                    const AsEgoPath &curv_path) {
    // Calculate the avoidance manoeuvers
    CalcAvoidanceManoeuvers(obj);

    // Creat in path data ttr
    InPathData obj_inpath_ttr = CalcCreatInPathDataAtTTC(obj, coll_eval, safemargin_eval, vse_out, curv_path, safemargin_eval.modified_ttr, true);

    if (SWITCH_FOR_TTM) {
        // Creat in path data ttm
        InPathData obj_inpath_ttm = CalcCreatInPathDataAtTTC(obj, coll_eval, safemargin_eval, vse_out, curv_path, coll_eval.ttm, false);
        // Choose long prediction in path data (the last bool needs to be
        // discussed)
        if ((false == obj_inpath_ttr.inpath_long_pred.in_path) && (true == obj_inpath_ttm.inpath_long_pred.in_path) &&
            (true == safemargin_eval.pred_ttm_valid) && (true == obj_try_brake) && (active_safety::ObjectClass::BICYCLE == obj.object_class)) {
            inpath_pred_data.inpath_long_pred = obj_inpath_ttm.inpath_long_pred;
        } else {
            inpath_pred_data.inpath_long_pred = obj_inpath_ttr.inpath_long_pred;
        }

        // Choose short prediction in path data
        if ((false == obj_inpath_ttr.inpath_short_pred.in_path) && (true == obj_inpath_ttm.inpath_short_pred.in_path) &&
            (true == safemargin_eval.pred_ttm_valid) && (true == obj_try_brake) && (true == coll_eval.motion_type.obs_is_vehicle)) {
            inpath_pred_data.inpath_short_pred = obj_inpath_ttm.inpath_short_pred;
        } else {
            inpath_pred_data.inpath_short_pred = obj_inpath_ttr.inpath_short_pred;
        }
    } else {
        inpath_pred_data.inpath_long_pred  = obj_inpath_ttr.inpath_long_pred;
        inpath_pred_data.inpath_short_pred = obj_inpath_ttr.inpath_short_pred;
    }
}

void AsInPathDecision::CalInPathDataWithCurrentPose(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                    const SafetyMarginEvaluator &safemagin_eval, const AsVseOut &vse_out) {
    CalCornerPoints(vse_out, coll_eval.bounding_box, obj);

    float min_lat      = 0.0f;
    bool  cross_flag   = CalClosestCornerDistance(vse_out, obj, min_lat);
    bool  in_path_def  = CheckInPathGeometrically(safemagin_eval.predict_offset, cross_flag, min_lat);
    bool  in_path_flag = CheckSteeringOutOfPath(vse_out, obj, coll_eval, in_path_def);
#ifdef USING_RSCL
    // AD_LERROR() << "MinLat:" << min_lat
    //             << " InPathDef:" << static_cast<uint32_t>(in_path_def)
    //             << "  CloseOffset:"
    //             << safemagin_eval.predict_offset.offs_lat_in_path_close_edge;
#endif

    inpath_curr_data.inpath_long_pred.in_path     = in_path_flag;
    inpath_curr_data.inpath_long_pred.a_lgt       = obj.long_accel;
    inpath_curr_data.inpath_long_pred.a_lat       = obj.lat_accel;
    inpath_curr_data.inpath_long_pred.a           = obj.accel;
    inpath_curr_data.inpath_long_pred.curv        = obj.curvature;
    inpath_curr_data.inpath_long_pred.p_lgt       = obj.long_posn;
    inpath_curr_data.inpath_long_pred.p_lat       = safemagin_eval.curv_coord_info.pos_lat_rel;
    inpath_curr_data.inpath_long_pred.spd         = obj.speed;
    inpath_curr_data.inpath_long_pred.v_lat       = obj.lat_vel;
    inpath_curr_data.inpath_long_pred.v_lgt       = obj.long_vel;
    inpath_curr_data.inpath_long_pred.heading     = obj.heading;
    inpath_curr_data.inpath_long_pred.manv_type   = OBJ_MAVN_CURRENT;
    inpath_curr_data.inpath_long_pred.pred_offset = safemagin_eval.predict_offset.offs_lat_in_path_close_edge;

    inpath_curr_data.inpath_short_pred.in_path     = in_path_flag;
    inpath_curr_data.inpath_short_pred.a_lgt       = obj.long_accel;
    inpath_curr_data.inpath_short_pred.a_lat       = obj.lat_accel;
    inpath_curr_data.inpath_short_pred.a           = obj.accel;
    inpath_curr_data.inpath_short_pred.curv        = obj.curvature;
    inpath_curr_data.inpath_short_pred.p_lgt       = obj.long_posn;
    inpath_curr_data.inpath_short_pred.p_lat       = safemagin_eval.curv_coord_info.pos_lat_rel;
    inpath_curr_data.inpath_short_pred.spd         = obj.speed;
    inpath_curr_data.inpath_short_pred.v_lat       = obj.lat_vel;
    inpath_curr_data.inpath_short_pred.v_lgt       = obj.long_vel;
    inpath_curr_data.inpath_short_pred.heading     = obj.heading;
    inpath_curr_data.inpath_short_pred.manv_type   = OBJ_MAVN_CURRENT;
    inpath_curr_data.inpath_short_pred.pred_offset = safemagin_eval.predict_offset.offs_lat_in_path_close_edge;
}

InPathData AsInPathDecision::CalcCreatInPathDataAtTTC(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                      const SafetyMarginEvaluator &safemargin_eval, const AsVseOut &vse_out,
                                                      const AsEgoPath &curv_path, float ttc_value, bool is_ttr) {
    // Calculate acceleration and prediction position
    PredictPoseInfo   obj_pred_pose  = CalcPredictAccelerationAndPosition(obj, coll_eval, safemargin_eval, ttc_value);
    EgoMotionStateAtTime host_pred_info = curv_path.GetHostState(ttc_value);
    // predict relative  lateral position at ttc time
    rel_pos_def       = CalcRelativePositionToHostPath(obj, coll_eval, obj_pred_pose.rel_pos_def, host_pred_info);
    rel_pos_long_time = CalcRelativePositionToHostPath(obj, coll_eval, obj_pred_pose.rel_pos_dec_long_time, host_pred_info);

    rel_pos_short_time = CalcRelativePositionToHostPath(obj, coll_eval, obj_pred_pose.rel_pos_dec_short_time, host_pred_info);

    rel_pos_turn_left = CalcRelativePositionToHostPath(obj, coll_eval, obj_pred_pose.rel_pos_dec_trun_left, host_pred_info);

    rel_pos_turn_right = CalcRelativePositionToHostPath(obj, coll_eval, obj_pred_pose.rel_pos_dec_trun_right, host_pred_info);

    // Determine in Path calculation
    float ego_half_width = 0.5f * vse_out.host_width;

    in_path_info.in_path_default          = CalcInPathAsymmetricOffset(obj, coll_eval, rel_pos_def, proj_dist_info.proj_dist_defult,
                                                              safemargin_eval.predict_offset.offs_lat_in_path_close_edge,
                                                              safemargin_eval.predict_offset.offs_lat_in_path_far_edge, ego_half_width, false, false);
    in_path_info.in_path_pred_zero_length = CalcInPathAsymmetricOffset(
        obj, coll_eval, rel_pos_def, proj_dist_info.proj_dist_zero_length, safemargin_eval.predict_offset.offs_lat_in_path_close_edge,
        safemargin_eval.predict_offset.offs_lat_in_path_far_edge, ego_half_width, true, false);

    in_path_info.in_path_pred_long_time = CalcInPathAsymmetricOffset(obj, coll_eval, rel_pos_long_time, proj_dist_info.proj_dist_long_pred,
                                                                     safemargin_eval.predict_offset.offs_lat_manoeuvre,
                                                                     safemargin_eval.predict_offset.offs_lat_manoeuvre, ego_half_width, false, true);

    float                   short_time_offset_lat = safemargin_eval.predict_offset.offs_lat_manoeuvre;
    SafetyMarginEvalatorCal safe_margin_parm{};
    if (inpath_decision_param.k_overwrite_offset_short) {
        switch (obj.object_class) {
            case active_safety::ObjectClass::PEDESTRIAN:
                short_time_offset_lat +=
                    LookUpTable::LookupTable1D<8>(safe_margin_parm.k_manv_vlgt_ego, safe_margin_parm.k_manv_latoffs_diff_vru, vse_out.vcs_long_vel);
                break;
            case active_safety::ObjectClass::BICYCLE:
                short_time_offset_lat +=
                    LookUpTable::LookupTable1D<8>(safe_margin_parm.k_manv_vlgt_ego, safe_margin_parm.k_manv_latoffs_diff_bike, vse_out.vcs_long_vel);
                break;
            case active_safety::ObjectClass::CAR:
                short_time_offset_lat +=
                    LookUpTable::LookupTable1D<8>(safe_margin_parm.k_manv_vlgt_ego, safe_margin_parm.k_manv_latoffs_diff_veh, vse_out.vcs_long_vel);
                break;
            default:
                break;
        }
    }

    in_path_info.in_path_pred_short_time = CalcInPathAsymmetricOffset(obj, coll_eval, rel_pos_short_time, proj_dist_info.proj_dist_short_pred,
                                                                      safemargin_eval.predict_offset.offs_lat_manoeuvre,
                                                                      safemargin_eval.predict_offset.offs_lat_manoeuvre, ego_half_width, false, true);

    float turn_pred_offset_lat = safemargin_eval.predict_offset.offs_lat_manoeuvre;

    in_path_info.in_path_pred_trun_left = CalcInPathAsymmetricOffset(obj, coll_eval, rel_pos_turn_left, proj_dist_info.proj_dist_trun_left,
                                                                     safemargin_eval.predict_offset.offs_lat_manoeuvre,
                                                                     safemargin_eval.predict_offset.offs_lat_manoeuvre, ego_half_width, false, true);

    in_path_info.in_path_pred_trun_right = CalcInPathAsymmetricOffset(obj, coll_eval, rel_pos_turn_right, proj_dist_info.proj_dist_trun_right,
                                                                      safemargin_eval.predict_offset.offs_lat_manoeuvre,
                                                                      safemargin_eval.predict_offset.offs_lat_manoeuvre, ego_half_width, false, true);

    // Check the possible of obj manoeuvres
    PossibleManoeuvres obj_posible_manv = CalcObjPossibleManoeuver(obj, coll_eval, vse_out, is_ttr);

    obj_try_brake = obj_posible_manv.obj_try_brake;

    float obj_long_offs[6]  = {safemargin_eval.predict_offset.offs_lat_in_path_close_edge,
                              safemargin_eval.predict_offset.offs_lat_manoeuvre,
                              turn_pred_offset_lat,
                              turn_pred_offset_lat,
                              safemargin_eval.predict_offset.offs_lat_in_path_close_edge,
                              safemargin_eval.predict_offset.offs_lat_in_path_close_edge};
    float obj_short_offs[6] = {safemargin_eval.predict_offset.offs_lat_in_path_close_edge,
                               safemargin_eval.predict_offset.offs_lat_manoeuvre,
                               turn_pred_offset_lat,
                               turn_pred_offset_lat,
                               safemargin_eval.predict_offset.offs_lat_in_path_close_edge,
                               safemargin_eval.predict_offset.offs_lat_in_path_close_edge};

    InPathData ret;
    // Creat in path data at long pred time
    ret.inpath_long_pred = DetermineInPathDataAtPredTime(obj, coll_eval, obj_posible_manv, obj_pred_pose, true, obj_long_offs);
    // creat in path data at short pred time
    ret.inpath_short_pred = DetermineInPathDataAtPredTime(obj, coll_eval, obj_posible_manv, obj_pred_pose, false, obj_short_offs);

    ret.inpath_long_pred.in_path  = (vse_out.straight_driving == false) && (coll_eval.ttr == 4.0f) ? false : ret.inpath_long_pred.in_path;
    ret.inpath_short_pred.in_path = (vse_out.straight_driving == false) && (coll_eval.ttr == 4.0f) ? false : ret.inpath_short_pred.in_path;

    return ret;
}

bool AsInPathDecision::CalcInPathAsymmetricOffset(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, RelativePose rel_pos,
                                                  ObjProjData &obj_proj, float lat_close_offs, float lat_far_offs, float ego_half_width,
                                                  bool zero_length, bool symmetric_sta) {
    (void)(obj);
    // First Module: Lateral Edge To Edge Distances.
    // Calculate the sin rotation mod
    float sin_rotation_mod = rel_pos.sin_rotation;
    if (rel_pos.cos_rotation > -0.41f) {
        // do nothing
    } else {
        sin_rotation_mod = -rel_pos.sin_rotation;
    }

    bool proj_to_left  = false;
    bool proj_to_right = false;
    if (((sin_rotation_mod < 0.0f) && rel_pos.point_on_dist_side) || ((sin_rotation_mod > 0.0f) && (!rel_pos.point_on_dist_side))) {
        proj_to_left = true;
    } else {
        proj_to_left = false;
    }
    if (((sin_rotation_mod > 0.0f) && rel_pos.point_on_dist_side) || ((sin_rotation_mod < 0.0f) && (!rel_pos.point_on_dist_side))) {
        proj_to_right = true;
    } else {
        proj_to_right = false;
    }
    // Computes the right and left edge to edge distances.
    // The leftmost and rightmost points of the object are seen from host's
    // point of view. Calculate the rigth and left edge to edge distance
    float abs_proj_lgt = 0.0f;
    float abs_proj_lat = 0.0;
    if (true == zero_length) {
        // For zero length scene.
        abs_proj_lgt = fabsf(0.01f * rel_pos.sin_rotation);
    } else {
        if (coll_eval.motion_type.side_closest) {
            abs_proj_lat = fabsf(coll_eval.bounding_box.length_side_lat * rel_pos.sin_rotation);
        } else {
            abs_proj_lgt = fabsf(coll_eval.bounding_box.length_side_lgt * rel_pos.sin_rotation);
        }
    }
    if (coll_eval.motion_type.side_closest) {
        abs_proj_lat = fabsf(0.5f * coll_eval.bounding_box.length_side_lgt * rel_pos.cos_rotation);
    } else {
        abs_proj_lat = fabsf(0.5f * coll_eval.bounding_box.length_side_lat * rel_pos.cos_rotation);
    }
    float dist_from_host_left  = 0.0f;
    float dist_from_host_right = 0.0f;
    if (proj_to_left) {
        dist_from_host_right = rel_pos.p_lat + abs_proj_lgt + abs_proj_lat + ego_half_width;
    } else {
        dist_from_host_right = rel_pos.p_lat + abs_proj_lat + ego_half_width;
    }

    if (proj_to_right) {
        dist_from_host_left = rel_pos.p_lat - abs_proj_lat - abs_proj_lgt - ego_half_width;
    } else {
        dist_from_host_left = rel_pos.p_lat - abs_proj_lat - ego_half_width;
    }

    // create obj proj data
    obj_proj.dist_from_host_left  = dist_from_host_left;
    obj_proj.dist_from_host_right = dist_from_host_right;
    // Lateral far and close edge including offset.
    EdgeDistance edge_dist;
    edge_dist.closet_dist_l = dist_from_host_left - lat_close_offs;
    edge_dist.closet_dist_r = -dist_from_host_right - lat_close_offs;

    edge_dist.far_dist_l = dist_from_host_right + lat_far_offs;
    edge_dist.far_dist_r = -dist_from_host_left + lat_far_offs;

    float close_edge_dist = 0.0f;
    float far_edge_dist   = 0.0f;

    if (false == symmetric_sta) {
        // Host left side is closest to the object when they reach each other.
        // 0.01 is to avoid floating-point equality.
        if (rel_pos.p_lat > 0.0f) {
            close_edge_dist = edge_dist.closet_dist_l;
            far_edge_dist   = edge_dist.far_dist_l;
        } else {
            close_edge_dist = edge_dist.closet_dist_r;
            far_edge_dist   = edge_dist.far_dist_r;
        }
    } else {
        close_edge_dist = edge_dist.closet_dist_l;
        far_edge_dist   = edge_dist.far_dist_l;
    }
    bool ret = false;
    // std::cout << "close_edge_dist:" << close_edge_dist
    //           << " far_edge_dist:" << far_edge_dist
    //           << " dist_from_host_right:" << dist_from_host_right
    //           << " dist_from_host_left:" << dist_from_host_left
    //           << " lat_far_offs:" << lat_far_offs
    //           << " lat_close_offs:" << lat_close_offs << std::endl;
    if ((close_edge_dist < 0.0f) ^ (far_edge_dist < 0.0f)) {
        ret = true;
    } else {
        ret = false;
    }
    return ret;
}

bool AsInPathDecision::CalClosestCornerDistance(const AsVseOut &vse_out, const active_safety::AsObstacle &obj, float &min_lat) {
    (void)(obj);
    float curv        = vse_out.rear_curvature;
    float curv_radius = math::SafeDivide(1.0, vse_out.rear_curvature);

    int sing_count = 0;
    min_lat        = std::numeric_limits<float>::max();

    math::CalculateCurveCoords(curv, curv_radius, corner_points.close_left_lgt, corner_points.close_left_lat,
                                   &corner_corved_points.close_left_lgt_corved, &corner_corved_points.close_left_lat_corved);

    if (corner_corved_points.close_left_lat_corved > 0.0f) {
        sing_count += 1;
    } else {
        sing_count -= 1;
    }
    if (fabsf(corner_corved_points.close_left_lat_corved) < min_lat) {
        min_lat = fabsf(corner_corved_points.close_left_lat_corved);
    }

    math::CalculateCurveCoords(curv, curv_radius, corner_points.close_right_lgt, corner_points.close_right_lat,
                                   &corner_corved_points.close_right_lgt_corved, &corner_corved_points.close_right_lat_corved);

    if (corner_corved_points.close_right_lat_corved > 0.0f) {
        sing_count += 1;
    } else {
        sing_count -= 1;
    }
    if (fabsf(corner_corved_points.close_right_lat_corved) < min_lat) {
        min_lat = fabsf(corner_corved_points.close_right_lat_corved);
    }

    math::CalculateCurveCoords(curv, curv_radius, corner_points.remote_left_lgt, corner_points.remote_left_lat,
                                   &corner_corved_points.remote_left_lgt_corved, &corner_corved_points.remote_left_lat_corved);

    if (corner_corved_points.remote_left_lat_corved > 0.0f) {
        sing_count += 1;
    } else {
        sing_count -= 1;
    }
    if (fabsf(corner_corved_points.remote_left_lat_corved) < min_lat) {
        min_lat = fabsf(corner_corved_points.remote_left_lat_corved);
    }

    math::CalculateCurveCoords(curv, curv_radius, corner_points.remote_right_lgt, corner_points.remote_right_lat,
                                   &corner_corved_points.remote_right_lgt_corved, &corner_corved_points.remote_right_lat_corved);

    if (corner_corved_points.remote_right_lat_corved > 0.0f) {
        sing_count += 1;
    } else {
        sing_count -= 1;
    }
    if (fabsf(corner_corved_points.remote_right_lat_corved) < min_lat) {
        min_lat = fabsf(corner_corved_points.remote_right_lat_corved);
    }
#ifdef USING_RSCL
    // AD_LERROR() << "Curv:" << curv;
    // AD_LERROR() << "FarRight:" <<
    // corner_corved_points.remote_right_lat_corved
    //             << " FatLeft: " <<
    //             corner_corved_points.remote_left_lat_corved
    //             << " CloseRight:" <<
    //             corner_corved_points.close_right_lat_corved
    //             << " CloseLeft:" <<
    //             corner_corved_points.close_left_lat_corved;
    // AD_LERROR() << "CorFarRight:" << corner_points.remote_right_lat
    //             << " CorFatLeft: " << corner_points.remote_left_lat
    //             << " CorCloseRight:" << corner_points.close_right_lat
    //             << " CorCloseLeft:" << corner_points.close_left_lat;
#endif
    if (4 == sing_count || -4 == sing_count) {
        return false;
    } else {
        return true;
    }
}

void AsInPathDecision::CalCornerPoints(const AsVseOut &vse_out, const BoundingBox &bd_box, const active_safety::AsObstacle &obj) {
    float len_side_lgt = bd_box.length_side_lgt;
    float len_side_lat = bd_box.length_side_lat;
    /*角点计算中 机动车需考虑：
      1、接近静止且大角度横置考虑 len_side_lgt
      2、运动/非大角度/aeb未激活 不考虑len_side_lgt
        UNDETERMINED = 0,
     */
    if (false == vse_out.aeb_active) {
        if (obj.object_class == active_safety::ObjectClass::BICYCLE || obj.object_class == active_safety::ObjectClass::ESCOOTER ||
            obj.object_class == active_safety::ObjectClass::THREEWHEEl_VEHICLE || obj.object_class == active_safety::ObjectClass::CAR ||
            obj.object_class == active_safety::ObjectClass::TRUCK || obj.object_class == active_safety::ObjectClass::UNIDENTIFIED_VEHICLE) {
            if ((fabs(obj.heading) < 1.2) || (obj.speed > 1.5)) {
                len_side_lgt = 0.01f;
            }
        } else {
            len_side_lgt = 0.01f;
        }
    }

    corner_points.close_left_lgt  = obj.long_posn - 0.5f * len_side_lat * bd_box.sin_rotation;
    corner_points.close_right_lgt = obj.long_posn + 0.5f * len_side_lat * bd_box.sin_rotation;

    corner_points.close_left_lat  = obj.lat_posn + 0.5f * len_side_lat * bd_box.cos_rotation;
    corner_points.close_right_lat = obj.lat_posn - 0.5f * len_side_lat * bd_box.cos_rotation;

    corner_points.remote_left_lgt  = obj.long_posn - 0.5f * len_side_lat * bd_box.sin_rotation + len_side_lgt * bd_box.cos_rotation;
    corner_points.remote_right_lgt = obj.long_posn + 0.5f * len_side_lat * bd_box.sin_rotation + len_side_lgt * bd_box.cos_rotation;

    corner_points.remote_left_lat  = obj.lat_posn + 0.5f * len_side_lat * bd_box.cos_rotation + len_side_lgt * bd_box.sin_rotation;
    corner_points.remote_right_lat = obj.lat_posn - 0.5f * len_side_lat * bd_box.cos_rotation + len_side_lgt * bd_box.sin_rotation;
    // std::cout << "close_left_lat" << corner_points.close_left_lat
    //           << "close_right_lat" << corner_points.close_right_lat
    //           << "remote_left_lat" << corner_points.remote_left_lat
    //           << "remote_right_lat" << corner_points.remote_right_lat
    //           << "long_posn" << obj.long_posn
    //           << "lat_posn" << obj.lat_posn
    //           << "sin_rotation" << bd_box.sin_rotation
    //           << "cos_rotation" << bd_box.cos_rotation
    //           << std::endl;
}

PredictPoseInfo AsInPathDecision::CalcPredictAccelerationAndPosition(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                                     const SafetyMarginEvaluator &safemargin_eval, float ttc_value) {
    // Calculate the heading stationary
    float head_stationary = 0.0f;
    float temp_angle      = atan2f(coll_eval.bounding_box.sin_rotation, coll_eval.bounding_box.cos_rotation);
    if ((true == coll_eval.motion_type.obs_is_vehicle) && (coll_eval.motion_type.abs_heading > M_PI / 2.0f)) {
        head_stationary = temp_angle + (-static_cast<float>(M_PI) * math::SignF(temp_angle));
    } else {
        head_stationary = temp_angle;
    }
    head_stationary = obj.heading_raw;
    PredictPoseInfo ret;
    if (true == coll_eval.motion_type.stationary) {
        // No Prediction
        ret = CalcNoPredAccAndPos(obj, head_stationary);
    } else if ((false == coll_eval.motion_type.stationary) && (true == coll_eval.motion_type.curved_motion)) {
        // Circular prediction
        ret = CalcCircularPredAccAndPos(obj, coll_eval, ttc_value);
    } else {
        // Linear Prediction
        ret = CalcLinearPredAccAndPos(obj, coll_eval, safemargin_eval, ttc_value, obj_avoidance, head_stationary);
    }
    return ret;
}

PossibleManoeuvres AsInPathDecision::CalcObjPossibleManoeuver(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                              const AsVseOut &vse_out, bool is_ttr) {
    PossibleManoeuvres ret;
    // Calculate the possible manoeuvres
    if (true == is_ttr) {
        ret = CheckIfObjTriesToManoeuverTTR(obj, coll_eval, vse_out);
    } else {
        ret = CheckIfObjTriesToManoeuverTTM(obj, coll_eval, vse_out);
    }

    // Check obj oncoming in path long pred time
    if ((true == in_path_info.in_path_default) && (true == in_path_info.in_path_pred_long_time) && (true == in_path_info.in_path_pred_trun_left) &&
        (true == in_path_info.in_path_pred_trun_right) && (true == ret.obj_try_steer)) {
        ret.obj_oncoming_inpath_long_pred = true;
    } else {
        ret.obj_oncoming_inpath_long_pred = false;
    }

    // Check obj oncoming in path short pred time
    if ((true == in_path_info.in_path_default) && (true == in_path_info.in_path_pred_short_time) && (true == in_path_info.in_path_pred_trun_left) &&
        (true == in_path_info.in_path_pred_trun_right) && (true == ret.obj_try_steer)) {
        ret.obj_oncoming_inpath_short_pred = true;
    } else {
        ret.obj_oncoming_inpath_short_pred = false;
    }

    // Check obj brake long pred time
    if ((true == in_path_info.in_path_default) && (false == in_path_info.in_path_pred_long_time) && (true == ret.obj_try_brake)) {
        ret.obj_brake_long_pred = true;
    } else {
        ret.obj_brake_long_pred = false;
    }

    // Check obj brake short pred time
    if ((true == in_path_info.in_path_default) && (false == in_path_info.in_path_pred_short_time) && (true == ret.obj_try_brake)) {
        ret.obj_brake_short_pred = true;
    } else {
        ret.obj_brake_short_pred = false;
    }

    // Check obj steer left
    if ((true == in_path_info.in_path_default) && (false == in_path_info.in_path_pred_trun_left) && (true == ret.obj_try_steer)) {
        ret.obj_steer_left = true;
    } else {
        ret.obj_steer_left = false;
    }

    // Check obj steer right
    if ((true == in_path_info.in_path_default) && (false == in_path_info.in_path_pred_trun_right) && (true == ret.obj_try_steer)) {
        ret.obj_steer_right = true;
    } else {
        ret.obj_steer_right = false;
    }
    return ret;
}

PossibleManoeuvres AsInPathDecision::CheckIfObjTriesToManoeuverTTR(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                                   const AsVseOut &vse_out) {
    PossibleManoeuvres ret;
    bool               obj_head_ok  = false;
    float              obj_abs_head = fabsf(atan2f(obj.lat_vel, obj.long_vel));
    bool               aeb_active   = vse_out.aeb_active;
    if ((active_safety::ObjectClass::BICYCLE == obj.object_class) && (false == aeb_active)) {
        if (obj_abs_head > inpath_decision_param.k_min_heading_bike_steer) {
            obj_head_ok = true;
        } else {
            obj_head_ok = false;
        }
    } else {
        if (obj_abs_head > inpath_decision_param.k_min_heading_steer) {
            obj_head_ok = true;
        } else {
            obj_head_ok = false;
        }
    }

    // Check the obj try brake and steer
    if ((!coll_eval.motion_type.stationary) && (true == obj_head_ok) && (false == aeb_active)) {
        ret.obj_try_steer = true;
    } else {
        ret.obj_try_steer = false;
    }

    if ((obj_abs_head > inpath_decision_param.k_min_heading_brake) && (!coll_eval.motion_type.stationary) && (false == aeb_active)) {
        ret.obj_try_brake = true;
    } else {
        ret.obj_try_brake = false;
    }
    return ret;
}

PossibleManoeuvres AsInPathDecision::CheckIfObjTriesToManoeuverTTM(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                                   const AsVseOut &vse_out) {
    (void)(vse_out);
    PossibleManoeuvres ret;
    float              obj_abs_head = fabsf(atan2f(obj.lat_vel, obj.long_vel));
    // Check the obj try steer
    if ((obj_abs_head > inpath_decision_param.k_min_heading_steer) && (!coll_eval.motion_type.stationary)) {
        ret.obj_try_steer = true;
    } else {
        ret.obj_try_steer = false;
    }

    // Check the obj try brake
    if ((obj_abs_head > inpath_decision_param.k_min_heading_brake) && (!coll_eval.motion_type.stationary)) {
        ret.obj_try_brake = true;
    } else {
        ret.obj_try_brake = false;
    }
    return ret;
}

PredictObjMotion AsInPathDecision::DetermineInPathDataAtPredTime(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                                 PossibleManoeuvres obj_manv, PredictPoseInfo pre_pos, bool is_long_pred,
                                                                 float obj_offs[6]) {
    // select the input value for long and short pred.
    bool  obj_can_brake   = false;
    bool  paral_vehicle   = false;
    float a_lgt_obj_brake = 0.0f;
    float a_lat_obj_brake = 0.0f;
    float rel_pos_lat     = 0.0f;
    float rel_pos_lgt     = 0.0f;
    float rel_pos_yaw     = 0.0f;
    bool  in_path_def     = false;
    // bool in_path_zero = false;
    bool  in_path_obj_brake = false;
    float decel             = 0.0f;

    float dist_left  = 0.0;
    float dist_right = 0.0;

    in_path_def = in_path_info.in_path_default;
    // in_path_zero = in_path_info.in_path_pred_zero_length;
    bool steer_left  = obj_manv.obj_steer_left;
    bool steer_right = obj_manv.obj_steer_right;

    float a_turn_left  = pre_pos.rel_pos_dec_trun_left.a_lgt;
    float a_turn_right = pre_pos.rel_pos_dec_trun_right.a_lgt;

    // the oncoming vehicle with low speed is assumed to brake
    bool obj_oncoming_brake = false;
    if ((obj.speed < inpath_decision_param.k_max_spd_obj_mov_to_self) && (true == coll_eval.motion_type.moving_oncoming) &&
        (true == coll_eval.motion_type.obs_is_motor_veh)) {
        obj_oncoming_brake = true;
    } else {
        obj_oncoming_brake = false;
    }

    // the input difference between long pred and short pred
    if (true == is_long_pred) {
        obj_can_brake     = obj_manv.obj_brake_long_pred;
        paral_vehicle     = coll_eval.motion_type.para_veh_long_pred;
        a_lgt_obj_brake   = pre_pos.rel_pos_dec_long_time.a_lgt;
        a_lat_obj_brake   = pre_pos.rel_pos_dec_long_time.a_lat;
        rel_pos_lgt       = pre_pos.rel_pos_dec_long_time.p_lgt;
        rel_pos_lat       = pre_pos.rel_pos_dec_long_time.p_lat;
        rel_pos_yaw       = pre_pos.rel_pos_dec_long_time.heading;
        in_path_obj_brake = in_path_info.in_path_pred_long_time;
        decel             = obj_avoidance.decel_long_pretime;
        dist_left         = proj_dist_info.proj_dist_long_pred.dist_from_host_left;
        dist_right        = proj_dist_info.proj_dist_long_pred.dist_from_host_right;
    } else {
        obj_can_brake     = obj_manv.obj_brake_short_pred;
        paral_vehicle     = coll_eval.motion_type.para_veh_short_pred;
        a_lgt_obj_brake   = pre_pos.rel_pos_dec_short_time.a_lgt;
        a_lat_obj_brake   = pre_pos.rel_pos_dec_short_time.a_lat;
        rel_pos_lgt       = pre_pos.rel_pos_dec_short_time.p_lgt;
        rel_pos_lat       = rel_pos_short_time.p_lat;
        rel_pos_yaw       = rel_pos_short_time.heading;
        in_path_obj_brake = in_path_info.in_path_pred_short_time;
        decel             = obj_avoidance.decel_short_pretime;
        dist_left         = proj_dist_info.proj_dist_short_pred.dist_from_host_left;
        dist_right        = proj_dist_info.proj_dist_short_pred.dist_from_host_right;
    }

    // check using zero length
    int obj_act_manv = OBJ_MANV_PRED_DEF;
    if ((true == paral_vehicle) || ((true == coll_eval.motion_type.stationary) && (true == coll_eval.motion_type.obs_is_motor_veh))) {
        obj_act_manv = OBJ_MANV_PRED_ZEROLENGTH;
    } else {
        obj_act_manv = OBJ_MANV_PRED_DEF;
    }

    // determine object manoeuver
    bool can_steer = false;

    // the oncoming object with low speed is assumed that it will brake.
    if ((true == obj_oncoming_brake) && (true == in_path_def)) {
        obj_act_manv = OBJ_MANV_PRED_BRAKE;
    } else {
        // check if object can steer out of path firstly
        if ((true == steer_left) || (true == steer_right)) {
            can_steer = true;
        } else {
            can_steer = false;
        }

        // TODO: need add standard trigger_flag @liuqi
        bool m_standard_trigger_flag = false;
        if (obj.object_class == active_safety::ObjectClass::BICYCLE && m_standard_trigger_flag) {
            obj_can_brake = false;
        }

        // and then check if turning left is the easiest
        bool left_easiest = false;
        if (true == can_steer) {
            left_easiest = CompareManoeuvers(steer_left, a_turn_left, steer_right, a_turn_right);
        } else {
            // do nothing
        }
        // check whether to use braking or steering
        if (true == obj_can_brake) {
            if (false == can_steer) {
                obj_act_manv = OBJ_MANV_PRED_BRAKE;
            } else {
                // the object can both brake and steer out of path
                if (true == left_easiest) {
                    // the object can brake or steer left
                    bool brake_flag = CompareManoeuvers(obj_can_brake, fabsf(a_lgt_obj_brake), steer_left, a_turn_left);
                    if (true == brake_flag) {
                        obj_act_manv = OBJ_MANV_PRED_BRAKE;
                    } else {
                        obj_act_manv = OBJ_MANV_PRED_STEER_LEFT;
                    }
                } else {
                    // the object can brake or steer right
                    bool brake_flag = CompareManoeuvers(obj_can_brake, fabsf(a_lgt_obj_brake), steer_right, a_turn_right);
                    if (true == brake_flag) {
                        obj_act_manv = OBJ_MANV_PRED_BRAKE;
                    } else {
                        obj_act_manv = OBJ_MANV_PRED_STEER_RIGHT;
                    }
                }
            }
        } else {
            // the object cannot brake out of path
            if (true == can_steer) {
                // check the object can turn left or right
                if (true == left_easiest) {
                    obj_act_manv = OBJ_MANV_PRED_STEER_LEFT;
                } else {
                    obj_act_manv = OBJ_MANV_PRED_STEER_RIGHT;
                }
            } else {
                // do nothing
            }
        }
    }
    // determine the in path data according to the obj actual manoeuver
    PredictObjMotion ret;
    obj_act_manv = OBJ_MANV_PRED_DEF;
    switch (obj_act_manv) {
        case (OBJ_MANV_PRED_BRAKE): {
            ret.a               = decel;
            ret.a_lgt           = a_lgt_obj_brake;
            ret.a_lat           = a_lat_obj_brake;
            ret.curv            = obj.curvature;
            ret.p_lgt           = rel_pos_lgt;
            ret.p_lat           = rel_pos_lat;
            ret.heading         = rel_pos_yaw;
            ret.in_path         = in_path_obj_brake;
            ret.dist_from_left  = dist_left;
            ret.dist_from_right = dist_right;
            ret.manv_type       = OBJ_MANV_PRED_BRAKE;
            ret.pred_offset     = obj_offs[OBJ_MANV_PRED_BRAKE];
            break;
        }
        case (OBJ_MANV_PRED_STEER_LEFT): {
            ret.a               = obj.accel;
            ret.a_lgt           = pre_pos.rel_pos_dec_trun_left.a_lgt;
            ret.a_lat           = pre_pos.rel_pos_dec_trun_left.a_lat;
            ret.curv            = pre_pos.rel_pos_dec_trun_left.curv;
            ret.p_lgt           = pre_pos.rel_pos_dec_trun_left.p_lgt;
            ret.p_lat           = pre_pos.rel_pos_dec_trun_left.p_lat;
            ret.heading         = pre_pos.rel_pos_dec_trun_left.heading;
            ret.in_path         = false;
            ret.dist_from_left  = proj_dist_info.proj_dist_trun_left.dist_from_host_left;
            ret.dist_from_right = proj_dist_info.proj_dist_trun_left.dist_from_host_right;
            ret.manv_type       = OBJ_MANV_PRED_STEER_LEFT;
            ret.pred_offset     = obj_offs[OBJ_MANV_PRED_STEER_LEFT];
            break;
        }
        case (OBJ_MANV_PRED_STEER_RIGHT): {
            ret.a               = obj.accel;
            ret.a_lgt           = pre_pos.rel_pos_dec_trun_right.a_lgt;
            ret.a_lat           = pre_pos.rel_pos_dec_trun_right.a_lat;
            ret.curv            = pre_pos.rel_pos_dec_trun_right.curv;
            ret.p_lgt           = pre_pos.rel_pos_dec_trun_right.p_lgt;
            ret.p_lat           = pre_pos.rel_pos_dec_trun_right.p_lat;
            ret.heading         = pre_pos.rel_pos_dec_trun_right.heading;
            ret.in_path         = false;
            ret.dist_from_left  = proj_dist_info.proj_dist_trun_right.dist_from_host_left;
            ret.dist_from_right = proj_dist_info.proj_dist_trun_right.dist_from_host_right;
            ret.manv_type       = OBJ_MANV_PRED_STEER_RIGHT;
            ret.pred_offset     = obj_offs[OBJ_MANV_PRED_STEER_RIGHT];
            break;
        }
        case (OBJ_MANV_PRED_ZEROLENGTH): {
            ret.a               = obj.accel;
            ret.a_lgt           = obj.long_accel;
            ret.a_lat           = obj.lat_accel;
            ret.curv            = obj.curvature;
            ret.p_lgt           = rel_pos_lgt;
            ret.p_lat           = rel_pos_lat;
            ret.heading         = pre_pos.rel_pos_def.heading;
            ret.in_path         = in_path_info.in_path_pred_zero_length;
            ret.dist_from_left  = proj_dist_info.proj_dist_zero_length.dist_from_host_left;
            ret.dist_from_right = proj_dist_info.proj_dist_zero_length.dist_from_host_right;
            ret.manv_type       = OBJ_MANV_PRED_ZEROLENGTH;
            ret.pred_offset     = obj_offs[OBJ_MANV_PRED_ZEROLENGTH];
            break;
        }
        default: {
            // case (OBJ_NO_MANOEUVER)
            ret.a               = obj.accel;
            ret.a_lgt           = obj.long_accel;
            ret.a_lat           = obj.lat_accel;
            ret.curv            = obj.curvature;
            ret.p_lgt           = rel_pos_lgt;
            ret.p_lat           = rel_pos_lat;
            ret.heading         = pre_pos.rel_pos_def.heading;
            ret.in_path         = in_path_info.in_path_default;
            ret.dist_from_left  = proj_dist_info.proj_dist_defult.dist_from_host_left;
            ret.dist_from_right = proj_dist_info.proj_dist_defult.dist_from_host_right;
            ret.manv_type       = OBJ_MANV_PRED_DEF;
            ret.pred_offset     = obj_offs[OBJ_MANV_PRED_DEF];
            break;
        }
    }

    ret.spd   = obj.speed;
    ret.v_lat = obj.lat_vel;
    ret.v_lgt = obj.long_vel;

    return ret;
}

bool AsInPathDecision::CompareManoeuvers(bool manv1, float a_manv1, bool manv2, float a_manv2) {
    // this function is used when at least one of two manoeuvers is allowed
    bool use_manv1 = false;
    if (false == manv1) {
        use_manv1 = false;
    } else if (false == manv2) {
        use_manv1 = true;
    } else {
        if (fabsf(a_manv1) < fabsf(a_manv2)) {
            use_manv1 = true;
        } else {
            use_manv1 = false;
        }
    }
    return use_manv1;
}

InPathData AsInPathDecision::SelectInPathData(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, const AsVseOut &vse_out,
                                              bool ttr_pred_valid) {
    // define the strict in path scenarios
    bool use_inpath_short = false;
    bool use_inpath_long  = false;
    // Judge whether the lateral speed of the target is small enough
    bool obj_low_lateral_spd = (vse_out.straight_driving == false) ? false : CheckObjLowLateralSpd(obj);

    if (((active_safety::ObjectClass::UNDETERMINED == obj.object_class) && (true == coll_eval.motion_type.moving_oncoming)) ||
        (true == obj_low_lateral_spd) || (true == coll_eval.motion_type.para_veh_short_pred)) {
        use_inpath_short = true;
    } else {
        // do nothing;
    }

    // long pred scenario
    if (((active_safety::ObjectClass::UNDETERMINED == obj.object_class) && (true == coll_eval.motion_type.moving_oncoming)) ||
        (true == obj_low_lateral_spd) || (true == coll_eval.motion_type.para_veh_long_pred)) {
        use_inpath_long = true;
    } else {
        // do nothing;
    }

    // define the strict out of path scenarios
    bool use_outpath_short = vse_out.aeb_active;
    bool use_outpath_long  = false;

    bool use_pred_long = CheckUsePredictionSta(use_outpath_long, use_inpath_long, inpath_pred_data.inpath_long_pred.in_path,
                                               inpath_curr_data.inpath_long_pred.in_path, ttr_pred_valid);

    bool       use_pred_short    = CheckUsePredictionSta(use_outpath_short, use_inpath_short, inpath_pred_data.inpath_short_pred.in_path,
                                                inpath_curr_data.inpath_short_pred.in_path, ttr_pred_valid);
    bool       use_predict_truck = CheckUsePredForTruck(obj);
    InPathData ret;
    if (true == use_pred_long && use_predict_truck) {
        ret.inpath_long_pred = inpath_pred_data.inpath_long_pred;
    } else {
        ret.inpath_long_pred = inpath_curr_data.inpath_long_pred;
    }

    if (true == use_pred_short && use_predict_truck) {
        ret.inpath_short_pred = inpath_pred_data.inpath_short_pred;
    } else {
        ret.inpath_short_pred = inpath_curr_data.inpath_short_pred;
    }
    return ret;
}
bool AsInPathDecision::CheckUsePredForTruck(const active_safety::AsObstacle &obj) {
    if (obj.object_class == active_safety::ObjectClass::TRUCK) {
        return false;
    } else {
        return true;
    }
}
bool AsInPathDecision::CheckObjLowLateralSpd(const active_safety::AsObstacle &obj) {
    bool ret = false;
    switch (obj.object_class) {
        case (active_safety::ObjectClass::CAR):
        case (active_safety::ObjectClass::TRUCK):
        case (active_safety::ObjectClass::MOTORCYCLE):
        case (active_safety::ObjectClass::UNIDENTIFIED_VEHICLE): {
            ret = false;
            break;
        }
        case (active_safety::ObjectClass::BICYCLE): {
            if (fabsf(obj.lat_vel) < inpath_decision_param.k_bike_inpath_lat_spd_thd) {
                ret = true;
            } else {
                // do nothing
            }
            break;
        }
        case (active_safety::ObjectClass::PEDESTRIAN): {
            if (fabsf(obj.lat_vel) < inpath_decision_param.k_ped_inpath_lat_spd_thdcrvt_rot_thd) {
                ret = true;
            } else {
                // do nothing
            }
            break;
        }
        case (active_safety::ObjectClass::ANIMAL): {
            ret = false;
            break;
        }
        case (active_safety::ObjectClass::GENOBJ): {
            ret = true;
            break;
        }
        case (active_safety::ObjectClass::UNDETERMINED):
        default: {
            break;
        }
    }
    return ret;
}

bool AsInPathDecision::CheckUsePredictionSta(bool use_outpath, bool use_inpath, bool inpath_ttr, bool inpath_curr, bool pred_valid) {
    // Select the long pred time path data
    bool use_pred = false;
    if (true == pred_valid) {
        if (true == use_outpath) {
            if ((true == inpath_ttr) || (false == inpath_curr)) {
                use_pred = true;
            } else {
                use_pred = false;
            }
        } else {
            if (true == use_inpath) {
                if ((false == inpath_ttr) || (true == inpath_curr)) {
                    use_pred = true;
                } else {
                    use_pred = false;
                }
            } else {
                use_pred = true;
            }
        }
    } else {
        use_pred = false;
    }
    return use_pred;
}

void AsInPathDecision::CalcAvoidanceManoeuvers(const active_safety::AsObstacle &obj) {
    // Avoidance manoeuvers calculation
    switch (obj.object_class) {
        case active_safety::ObjectClass::PEDESTRIAN: {
            obj_avoidance.decel_long_pretime  = inpath_decision_param.k_ped_decel_long_pred;
            obj_avoidance.decel_short_pretime = inpath_decision_param.k_ped_decel_short_pred;
            obj_avoidance.alat_steer          = inpath_decision_param.k_ped_alat_steer_pred;
            break;
        }
        case active_safety::ObjectClass::ANIMAL: {
            obj_avoidance.decel_long_pretime  = 0.0f;
            obj_avoidance.decel_short_pretime = 0.0f;
            obj_avoidance.alat_steer          = 0.0f;
            break;
        }
        case active_safety::ObjectClass::GENOBJ: {
            obj_avoidance.decel_long_pretime  = 0.0f;
            obj_avoidance.decel_short_pretime = 0.0f;
            obj_avoidance.alat_steer          = 0.0f;
            break;
        }
        case active_safety::ObjectClass::BICYCLE: {
            obj_avoidance.decel_long_pretime  = inpath_decision_param.k_bike_decel_long_pred;
            obj_avoidance.decel_short_pretime = inpath_decision_param.k_bike_decel_short_pred;
            obj_avoidance.alat_steer          = inpath_decision_param.k_bike_alat_steer_pred;
            break;
        }
        case active_safety::ObjectClass::MOTORCYCLE: {
            obj_avoidance.decel_long_pretime  = CalcDeclerationForAovidance(obj, inpath_decision_param.k_veh_decel_long_pred);
            obj_avoidance.decel_short_pretime = CalcDeclerationForAovidance(obj, inpath_decision_param.k_veh_decel_short_pred);
            float tmp7                        = fabsf(obj.speed);
            obj_avoidance.alat_steer =
                LookUpTable::LookupTable1D<9>(inpath_decision_param.k_obj_veh_spd_steer, inpath_decision_param.k_veh_alat_steer_pred, tmp7);
            break;
        }
        case active_safety::ObjectClass::TRUCK: {
            obj_avoidance.decel_long_pretime  = CalcDeclerationForAovidance(obj, inpath_decision_param.k_veh_decel_long_pred);
            obj_avoidance.decel_short_pretime = CalcDeclerationForAovidance(obj, inpath_decision_param.k_veh_decel_short_pred);
            float tmp8                        = fabsf(obj.speed);
            obj_avoidance.alat_steer =
                LookUpTable::LookupTable1D<9>(inpath_decision_param.k_obj_veh_spd_steer, inpath_decision_param.k_veh_alat_steer_pred, tmp8);
            break;
        }
        case active_safety::ObjectClass::CAR: {
            obj_avoidance.decel_long_pretime  = CalcDeclerationForAovidance(obj, inpath_decision_param.k_veh_decel_long_pred);
            obj_avoidance.decel_short_pretime = CalcDeclerationForAovidance(obj, inpath_decision_param.k_veh_decel_short_pred);
            float tmp9                        = fabsf(obj.speed);
            obj_avoidance.alat_steer =
                LookUpTable::LookupTable1D<9>(inpath_decision_param.k_obj_veh_spd_steer, inpath_decision_param.k_veh_alat_steer_pred, tmp9);
            break;
        }
        case active_safety::ObjectClass::UNIDENTIFIED_VEHICLE: {
            obj_avoidance.decel_long_pretime  = CalcDeclerationForAovidance(obj, inpath_decision_param.k_veh_decel_long_pred);
            obj_avoidance.decel_short_pretime = CalcDeclerationForAovidance(obj, inpath_decision_param.k_veh_decel_short_pred);
            float tmp10                       = fabsf(obj.speed);
            obj_avoidance.alat_steer =
                LookUpTable::LookupTable1D<9>(inpath_decision_param.k_obj_veh_spd_steer, inpath_decision_param.k_veh_alat_steer_pred, tmp10);
            break;
        }
        default: {
            obj_avoidance.decel_long_pretime  = 0.0f;
            obj_avoidance.decel_short_pretime = 0.0f;
            obj_avoidance.alat_steer          = 0.0f;
            break;
        }
    }
    obj_avoidance.decel_long_pretime  = 0.0f;
    obj_avoidance.decel_short_pretime = 0.0f;
    obj_avoidance.alat_steer          = 0.0f;
}

PredictPoseInfo AsInPathDecision::CalcNoPredAccAndPos(const active_safety::AsObstacle &obj, float head_sta) {
    PredictPoseInfo ret;
    ret.rel_pos_def.p_lgt   = obj.long_posn;
    ret.rel_pos_def.p_lat   = obj.lat_posn;
    ret.rel_pos_def.v_lgt   = 0.0f;
    ret.rel_pos_def.v_lat   = 0.0f;
    ret.rel_pos_def.a_lgt   = 0.0f;
    ret.rel_pos_def.a_lat   = 0.0f;
    ret.rel_pos_def.heading = head_sta;
    ret.rel_pos_def.spd     = 0.0f;
    ret.rel_pos_def.a       = 0.0f;
    ret.rel_pos_def.curv    = 0.0f;
    ret.rel_pos_def.in_path = false;

    ret.rel_pos_dec_long_time.p_lgt   = obj.long_posn;
    ret.rel_pos_dec_long_time.p_lat   = obj.lat_posn;
    ret.rel_pos_dec_long_time.v_lgt   = 0.0f;
    ret.rel_pos_dec_long_time.v_lat   = 0.0f;
    ret.rel_pos_dec_long_time.a_lgt   = 0.0f;
    ret.rel_pos_dec_long_time.a_lat   = 0.0f;
    ret.rel_pos_dec_long_time.heading = head_sta;
    ret.rel_pos_dec_long_time.spd     = 0.0f;
    ret.rel_pos_dec_long_time.a       = 0.0f;
    ret.rel_pos_dec_long_time.curv    = 0.0f;
    ret.rel_pos_dec_long_time.in_path = false;

    ret.rel_pos_dec_short_time.p_lgt   = obj.long_posn;
    ret.rel_pos_dec_short_time.p_lat   = obj.lat_posn;
    ret.rel_pos_dec_short_time.v_lgt   = 0.0f;
    ret.rel_pos_dec_short_time.v_lat   = 0.0f;
    ret.rel_pos_dec_short_time.a_lgt   = 0.0f;
    ret.rel_pos_dec_short_time.a_lat   = 0.0f;
    ret.rel_pos_dec_short_time.heading = head_sta;
    ret.rel_pos_dec_short_time.spd     = 0.0f;
    ret.rel_pos_dec_short_time.a       = 0.0f;
    ret.rel_pos_dec_short_time.curv    = 0.0f;
    ret.rel_pos_dec_short_time.in_path = false;

    ret.rel_pos_dec_trun_left.p_lgt   = obj.long_posn;
    ret.rel_pos_dec_trun_left.p_lat   = obj.lat_posn;
    ret.rel_pos_dec_trun_left.v_lgt   = 0.0f;
    ret.rel_pos_dec_trun_left.v_lat   = 0.0f;
    ret.rel_pos_dec_trun_left.a_lgt   = 0.0f;
    ret.rel_pos_dec_trun_left.a_lat   = 0.0f;
    ret.rel_pos_dec_trun_left.heading = head_sta;
    ret.rel_pos_dec_trun_left.spd     = 0.0f;
    ret.rel_pos_dec_trun_left.a       = 0.0f;
    ret.rel_pos_dec_trun_left.curv    = 0.0f;
    ret.rel_pos_dec_trun_left.in_path = false;

    ret.rel_pos_dec_trun_right.p_lgt   = obj.long_posn;
    ret.rel_pos_dec_trun_right.p_lat   = obj.lat_posn;
    ret.rel_pos_dec_trun_right.v_lgt   = 0.0f;
    ret.rel_pos_dec_trun_right.v_lat   = 0.0f;
    ret.rel_pos_dec_trun_right.a_lgt   = 0.0f;
    ret.rel_pos_dec_trun_right.a_lat   = 0.0f;
    ret.rel_pos_dec_trun_right.heading = head_sta;
    ret.rel_pos_dec_trun_right.spd     = 0.0f;
    ret.rel_pos_dec_trun_right.a       = 0.0f;
    ret.rel_pos_dec_trun_right.curv    = 0.0f;
    ret.rel_pos_dec_trun_right.in_path = false;

    return ret;
}

// Circular prediction
PredictPoseInfo AsInPathDecision::CalcCircularPredAccAndPos(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                            float ttc_value) {
    PredictPoseInfo ret;
    // Circular prediction of obj at ttr
    ret.rel_pos_def = CalcDefaultObjCircularMotion(obj, coll_eval, ttc_value);

    // Acceleration Calculation and circular prediction of braking obj at ttc
    // time
    ret.rel_pos_dec_long_time = CalcBrakingObjCircularMotion(obj, coll_eval, ttc_value, obj_avoidance.decel_long_pretime);

    ret.rel_pos_dec_short_time = CalcBrakingObjCircularMotion(obj, coll_eval, ttc_value, obj_avoidance.decel_short_pretime);

    // Acceleration Calculation and circular prediciton of turning obj at ttc
    // time
    ret.rel_pos_dec_trun_left = CalcTurningObjCircularMotion(obj, coll_eval, ttc_value, obj_avoidance.alat_steer, true);

    ret.rel_pos_dec_trun_right = CalcTurningObjCircularMotion(obj, coll_eval, ttc_value, obj_avoidance.alat_steer, false);

    return ret;
}

PredictPoseInfo AsInPathDecision::CalcLinearPredAccAndPos(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                          const SafetyMarginEvaluator &safemargin_eval, float ttc_value, AobjAvoidance avoid_a,
                                                          float head_sta) {
    PredictPoseInfo ret;
    // Default prediction TTR longitudinal and lateral
    ret.rel_pos_def = CalcDefaultObjLinearMotion(obj, ttc_value);
    // Braking object linear prediction
    ret.rel_pos_dec_long_time  = CalcBrakingObjLinearMotion(obj, safemargin_eval, avoid_a.decel_long_pretime, ttc_value, head_sta);
    ret.rel_pos_dec_short_time = CalcBrakingObjLinearMotion(obj, safemargin_eval, avoid_a.decel_short_pretime, ttc_value, head_sta);
    // Turning object linear prediction
    ret.rel_pos_dec_trun_left  = CalcTurningObjLinearMotion(obj, coll_eval, safemargin_eval, avoid_a.alat_steer, ttc_value, true);
    ret.rel_pos_dec_trun_right = CalcTurningObjLinearMotion(obj, coll_eval, safemargin_eval, avoid_a.alat_steer, ttc_value, false);

    return ret;
}

PredictObjMotion AsInPathDecision::CalcDefaultObjCircularMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                                float ttc_value) {
    PredictObjMotion ret;
    PredictObjMotion obj_curr_motion;
    obj_curr_motion.a    = obj.accel;
    obj_curr_motion.curv = obj.curvature;

    ret = PredictObjectCurveMotion(obj, coll_eval, obj_curr_motion, ttc_value);

    ret.v_lgt = ret.spd * cosf(ret.heading);
    ret.v_lat = ret.spd * sinf(ret.heading);
    return ret;
}
PredictObjMotion AsInPathDecision::CalcBrakingObjCircularMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                                float ttc_value, float decel_pre) {
    PredictObjMotion ret;
    PredictObjMotion obj_curr_motion;
    obj_curr_motion.a    = decel_pre;
    obj_curr_motion.curv = obj.curvature;
    ret                  = PredictObjectCurveMotion(obj, coll_eval, obj_curr_motion, ttc_value);

    ret.v_lgt = ret.spd * cosf(ret.heading);
    ret.v_lat = ret.spd * sinf(ret.heading);

    ret.a_lgt = decel_pre * cosf(obj.heading);
    ret.a_lat = decel_pre * sinf(obj.heading);
    return ret;
}

PredictObjMotion AsInPathDecision::CalcTurningObjCircularMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                                float ttc_value, float alat_steer, bool turn_left) {
    // Calculate curvature
    float temp_crvt      = 0.0f;
    float sign_speed_sqr = obj.speed * obj.speed * math::SignF(obj.speed);

    if (turn_left) {
        temp_crvt = math::SafeDivide(alat_steer, sign_speed_sqr) + obj.curvature;
    } else {
        temp_crvt = math::SafeDivide(-alat_steer, sign_speed_sqr) + obj.curvature;
    }
    if (fabsf(temp_crvt) > inpath_decision_param.k_obj_crvt_rot_thd) {
        // do thing
    } else {
        if (turn_left) {
            temp_crvt = inpath_decision_param.k_obj_crvt_rot_thd;
        } else {
            temp_crvt = -inpath_decision_param.k_obj_crvt_rot_thd;
        }
    }
    PredictObjMotion ret;
    PredictObjMotion obj_curr_motion;
    obj_curr_motion.a    = obj.accel;
    obj_curr_motion.curv = temp_crvt;
    // Prediction postion
    ret = PredictObjectCurveMotion(obj, coll_eval, obj_curr_motion, ttc_value);
    // Computer catesian movement
    obj_curr_motion = CalcCartesianMovement(obj, temp_crvt);

    ret.v_lgt = ret.spd * cosf(ret.heading);
    ret.v_lat = ret.spd * sinf(ret.heading);
    ret.a_lat = obj_curr_motion.a_lat;
    ret.a_lgt = obj_curr_motion.a_lgt;
    ret.curv  = obj_curr_motion.curv;
    return ret;
}

PredictObjMotion AsInPathDecision::CalcDefaultObjLinearMotion(const active_safety::AsObstacle &obj, float ttc_value) {
    PredictObjMotion ret;
    // Calculate the longitudinal linear movement
    ret.p_lgt = obj.long_posn;
    ret.v_lgt = obj.long_vel;
    ret.a_lgt = obj.long_accel;
    LinearMovementPredictorWithStop(true, ret.p_lgt, ret.v_lgt, ret.a_lgt, ttc_value);
    // Calculate the lateral linear movement
    ret.p_lat = obj.lat_posn;
    ret.v_lat = obj.lat_vel;
    ret.a_lat = obj.lat_accel;
    LinearMovementPredictorWithStop(true, ret.p_lat, ret.v_lat, ret.a_lat, ttc_value);
    ret.heading = atan2f(ret.v_lat, ret.v_lgt);
    return ret;
}

PredictObjMotion AsInPathDecision::CalcBrakingObjLinearMotion(const active_safety::AsObstacle &obj, const SafetyMarginEvaluator &saffmargin_eval,
                                                              float decel_pre, float ttc_value, float head_sta) {
    PredictObjMotion ret;
    // braking lateral and longitudinal deceleration
    float temp_a_steer = obj.lat_accel * saffmargin_eval.cos_heading - obj.long_accel * saffmargin_eval.sin_heading;
    float temp_a_lgt   = decel_pre * saffmargin_eval.cos_heading - temp_a_steer * saffmargin_eval.sin_heading;
    float temp_a_lat   = decel_pre * saffmargin_eval.sin_heading + temp_a_steer * saffmargin_eval.cos_heading;

    ret.a_lat = temp_a_lat;
    ret.a_lgt = temp_a_lgt;

    // Linear longitudinal movement with brake
    ret.p_lgt      = obj.long_posn;
    ret.v_lgt      = obj.long_vel;
    bool lgt_stops = LinearMovementPredictorWithStop(true, ret.p_lgt, ret.v_lgt, ret.a_lgt, ttc_value);

    // Linear lateral movement with brake
    ret.p_lat      = obj.lat_posn;
    ret.v_lat      = obj.lat_vel;
    bool lat_stops = LinearMovementPredictorWithStop(true, ret.p_lat, ret.v_lat, ret.a_lat, ttc_value);
    // Heading filter
    if (true == lgt_stops && true == lat_stops) {
        ret.heading = head_sta;
    } else {
        ret.heading = atan2f(ret.v_lat, ret.v_lgt);
    }
    return ret;
}

PredictObjMotion AsInPathDecision::CalcTurningObjLinearMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                              const SafetyMarginEvaluator &safemargin_eval, float decel_pre, float ttc_value,
                                                              bool turn_left) {
    PredictObjMotion ret;
    // the crvt of pred
    ret.curv = obj.curvature;

    // Calculate the acceleration
    if (true == turn_left) {
        ret.a_lgt = obj.long_accel - decel_pre * safemargin_eval.sin_heading;
        ret.a_lat = obj.lat_accel + decel_pre * safemargin_eval.cos_heading;
    } else {
        ret.a_lgt = obj.long_accel + decel_pre * safemargin_eval.sin_heading;
        ret.a_lat = obj.lat_accel - decel_pre * safemargin_eval.cos_heading;
    }
    // Calculate the translate position
    float Leng_sgn_spd = math::SignF(obj.speed) * coll_eval.bounding_box.length_side_lgt;
    if (active_safety::AS_OBS_MP_MOV_TO_SELF == obj.motion_pattern) {
        ret.p_lgt = CalcTransPosnToRemoteSide(obj.long_posn, Leng_sgn_spd, safemargin_eval.cos_heading);
        ret.p_lat = CalcTransPosnToRemoteSide(obj.lat_posn, Leng_sgn_spd, safemargin_eval.sin_heading);
    } else {
        ret.p_lgt = obj.long_posn;
        ret.p_lat = obj.lat_posn;
    }

    ret.v_lgt = obj.long_vel;
    ret.v_lat = obj.lat_vel;

    LinearMovementPredictorWithStop(false, ret.p_lgt, ret.v_lgt, ret.a_lgt, ttc_value);

    LinearMovementPredictorWithStop(false, ret.p_lat, ret.v_lat, ret.a_lat, ttc_value);

    ret.heading = atan2f(ret.v_lat, ret.v_lgt);
    // modify the predicted obj  postion if turning
    if (active_safety::AS_OBS_MP_MOV_TO_SELF == obj.motion_pattern) {
        ret.p_lgt = CalcTransPosnFromRemoteSide(ret.p_lgt, Leng_sgn_spd, cosf(ret.heading));
        ret.p_lat = CalcTransPosnFromRemoteSide(ret.p_lat, Leng_sgn_spd, sinf(ret.heading));
    } else {
        // do thing
    }

    return ret;
}
float AsInPathDecision::CalcTransPosnToRemoteSide(float posn, float length, float heading) {
    float ret = posn - length * heading;
    return ret;
}

float AsInPathDecision::CalcTransPosnFromRemoteSide(float posn, float length, float heading) {
    float ret = posn + length * heading;
    return ret;
}

RelativePose AsInPathDecision::CalcRelativePositionToHostPath(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                              PredictObjMotion pre_pos, EgoMotionStateAtTime host_pred_info) {
    RelativePose ret;
    float        ego_cos_heading = cosf(host_pred_info.heading_angle);
    float        ego_sin_heading = sinf(host_pred_info.heading_angle);
    float        rel_heading     = pre_pos.heading - host_pred_info.heading_angle;
    // Calculate the relative heading and rotation
    if (true == coll_eval.motion_type.stationary) {
        ret.sin_rotation = coll_eval.bounding_box.sin_rotation * ego_cos_heading - coll_eval.bounding_box.cos_rotation * ego_sin_heading;

        ret.cos_rotation = coll_eval.bounding_box.cos_rotation * ego_cos_heading + coll_eval.bounding_box.sin_rotation * ego_sin_heading;

        ret.heading = rel_heading;
        ret.heading = math::Clamp(ret.heading, -static_cast<float>(M_PI), static_cast<float>(M_PI));
    } else {
        ret.heading      = active_safety::math::MapAngToInterval(static_cast<float>(M_PI), rel_heading);
        float length_ang = active_safety::math::MapAngToInterval(static_cast<float>(M_PI), rel_heading);

        if (true == coll_eval.motion_type.side_closest) {
            ret.sin_rotation = -math::SignF(length_ang) * cosf(length_ang);
            ret.cos_rotation = math::SignF(length_ang) * sinf(length_ang);
        } else {
            ret.sin_rotation = sinf(length_ang);
            ret.cos_rotation = cosf(length_ang);
        }
    }
    // Calculate the lateral position and lateral velocity
    ret.p_lat = (pre_pos.p_lat - host_pred_info.lat_pos) * ego_cos_heading - (pre_pos.p_lgt - host_pred_info.long_pos) * ego_sin_heading;

    ret.v_lat = pre_pos.v_lat * ego_cos_heading - pre_pos.v_lgt * ego_sin_heading;

    // Check the position of measure point
    bool rear_closest = false;
    if (fabsf(ret.heading) < 2.0) {
        rear_closest = true;
    } else {
        rear_closest = false;
    }

    if ((rear_closest && active_safety::AS_OBS_MP_MOV_TO_SELF == obj.motion_pattern) || (!rear_closest && active_safety::AS_OBS_MP_MOV_FROM_SELF == obj.motion_pattern)) {
        ret.point_on_dist_side = true;
    } else {
        ret.point_on_dist_side = false;
    }
    return ret;
}

PredictObjMotion AsInPathDecision::PredictObjectCurveMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                            PredictObjMotion pre_motion, float pred_time) {
    PredictObjMotion ret;
    // Linear movement predict with stop detection
    ret.p_lgt = 0.0f;
    ret.spd   = obj.speed;
    ret.a     = pre_motion.a;
    LinearMovementPredictorWithStop(true, ret.p_lgt, ret.spd, ret.a, pred_time);

    // Calculate the length with speed sign
    float Length_sgnspd = math::SignF(obj.long_vel) * coll_eval.bounding_box.length_side_lgt;

    // Calculate the position of lateral and longitudinal remote
    float lgt_posn = 0.0f;
    float lat_posn = 0.0f;
    if (active_safety::AS_OBS_MP_MOV_TO_SELF == obj.motion_pattern) {
        lat_posn = obj.lat_posn - Length_sgnspd * sinf(obj.heading);
        lgt_posn = obj.long_posn - Length_sgnspd * cosf(obj.heading);
    } else {
        lat_posn = obj.lat_posn;
        lgt_posn = obj.long_posn;
    }

    // Calculate the center rotation
    float obj_radius      = math::Clamp(math::SafeDivide(1.0f, pre_motion.curv), -1000.0f, 1000.0f);
    float obj_agdir_rad   = 0.0f;
    obj_agdir_rad         = obj.heading + static_cast<float>(M_PI_2);
    float center_rota_lgt = obj.long_posn + cosf(obj_agdir_rad) * obj_radius;
    float center_rota_lat = obj.lat_posn + sinf(obj_agdir_rad) * obj_radius;

    // the predict heading calc
    float obj_rotation = ret.p_lgt * pre_motion.curv;
    ret.heading        = obj.heading + obj_rotation;

    // Rotate around COR
    float rotate_posn_lgt = center_rota_lgt + (lgt_posn - center_rota_lgt) * cosf(obj_rotation) - (lat_posn - center_rota_lat) * sinf(obj_rotation);
    float rotate_posn_lat = center_rota_lat + (lat_posn - center_rota_lat) * cosf(obj_rotation) + (lgt_posn - center_rota_lgt) * sinf(obj_rotation);

    // Translate posn lat from Remote side
    if (active_safety::AS_OBS_MP_MOV_TO_SELF == obj.motion_pattern) {
        ret.p_lgt = rotate_posn_lgt + (Length_sgnspd * cosf(ret.heading));
        ret.p_lat = rotate_posn_lat + (Length_sgnspd * sinf(ret.heading));
    } else {
        ret.p_lgt = rotate_posn_lgt;
        ret.p_lat = rotate_posn_lat;
    }
    return ret;
}

float AsInPathDecision::CalcDeclerationForAovidance(const active_safety::AsObstacle &obj, float conf_value) {
    float ret       = 0.0f;
    float signDecel = conf_value * math::SignF(obj.speed);
    if (obj.speed < 0.0f) {
        ret = fmaxf(signDecel, obj.accel);
    } else {
        ret = fminf(signDecel, obj.accel);
    }
    return ret;
}

bool AsInPathDecision::CheckInPathGeometrically(const PredictOffset &pred_offst, bool cross_flag, float min_lat) {
    float funnel_width = 0;
    bool  in_path_flag = false;
    if (true == cross_flag) {
        in_path_flag = true;
    } else {
        float offset = 0.0f;
        // radar only
        // if (0 >= obj.vis_trk_id) {
        //     offset = 0.0f;
        // } else {
        offset = pred_offst.offs_lat_in_path_close_edge;
        // }
        float funnel_width = offset + inpath_decision_param.k_veh_half_width;
        if (min_lat < funnel_width) {
            in_path_flag = true;
        }
    }

    return in_path_flag;
}

PredictObjMotion AsInPathDecision::CalcCartesianMovement(const active_safety::AsObstacle &obj, float crvt) {
    PredictObjMotion ret;
    float            a_crv = obj.speed * obj.speed * crvt;

    ret.a_lat = obj.accel * sinf(obj.heading) + a_crv * cosf(obj.heading);
    ret.a_lgt = obj.accel * cosf(obj.heading) - a_crv * sinf(obj.heading);

    ret.v_lat = obj.speed * sinf(obj.heading);
    ret.v_lgt = obj.speed * cosf(obj.heading);
    return ret;
}

bool AsInPathDecision::CheckSteeringOutOfPath(const AsVseOut &vse_out, const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                              bool in_path_def) {
    bool is_moter_veh = false;
    if (true == coll_eval.motion_type.obs_is_vehicle && active_safety::ObjectClass::BICYCLE != obj.object_class) {
        is_moter_veh = true;
    }

    bool ttr_valid = false;
    if (coll_eval.ttr < inpath_decision_param.k_uppr_lim_ttr) {
        ttr_valid = true;
    }

    bool  heading_ok  = false;
    float abs_heading = 0.0f;
    abs_heading       = fabsf(atan2f(obj.lat_vel, obj.long_vel));
    if (active_safety::ObjectClass::BICYCLE == obj.object_class && false == vse_out.aeb_active) {
        if (abs_heading > inpath_decision_param.k_ang_dir_for_bicycle_steer_thd) {
            heading_ok = true;
        }
    } else {
        if (abs_heading > inpath_decision_param.k_ang_dir_for_steer_thd) {
            heading_ok = true;
        }
    }

    bool tries_to_steer = false;
    if (false == vse_out.aeb_active && false == coll_eval.motion_type.stationary && true == heading_ok) {
        tries_to_steer = true;
    }

    // if the object cannot steer out of path
    bool in_path = false;
    if (false == is_moter_veh || true == ttr_valid || false == tries_to_steer) {
        if (true == in_path_def) {
            in_path = true;
        }
    }

    return in_path;
}

bool AsInPathDecision::LinearMovementPredictorWithStop(bool stopena, float &posn, float &spd, float &a, float t) {
    // Min of ti or obj stopped
    float stoptime = -math::SafeDivide(spd, a);
    float mintime  = t;
    if ((stoptime > 0.0f) && (stopena)) {
        mintime = fminf(t, stoptime);
    } else {
        // do noting
    }

    // Linear movement predictor
    float powtime = mintime * mintime;
    posn          = posn + spd * mintime + 0.5f * a * powtime;
    spd           = spd + a * mintime;

    // Obj stop state detected
    bool objstops = false;
    if (fabs(t - mintime) > 0.0001f) {
        spd      = 0.0f;
        a        = 0.0f;
        objstops = true;
    } else {
        // do nothing
    }

    return objstops;
}

} // namespace tap
} // namespace senseAD
