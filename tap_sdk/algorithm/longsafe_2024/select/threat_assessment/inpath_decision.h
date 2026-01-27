/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include "algorithm/longsafe_2024/algo_interface/active_safety_vse.h"
#include "math/lookuptable/lookuptable.h"
#include "coll_eval.h"
#include "ego_path.h"
#include "algorithm/obstacle/obstacle.h"
#include "safemargin_evaluator.h"

namespace math = active_safety::math;
using namespace active_safety::math;


namespace senseAD {
namespace tap {

struct AobjAvoidance {
    float decel_long_pretime;
    float decel_short_pretime;
    float alat_steer;

    AobjAvoidance() : decel_long_pretime(0.0f), decel_short_pretime(0.0f), alat_steer(0.0f) {}
};

struct PredictObjMotion {
    float p_lgt;
    float p_lat;
    float spd;
    float v_lgt;
    float v_lat;
    float heading;
    float a;
    float a_lgt;
    float a_lat;
    float curv;
    bool  in_path;
    float dist_from_left;
    float dist_from_right;
    float pred_offset;
    int   manv_type;

    PredictObjMotion()
        : p_lgt(0.0f), p_lat(0.0f), spd(0.0f), v_lgt(0.0f), v_lat(0.0f), heading(0.0f), a(0.0f), a_lgt(0.0f), a_lat(0.0f), curv(0.0f), in_path(false),
          dist_from_left(0.0), dist_from_right(0.0), pred_offset(0.0), manv_type(0) {}
};

struct RelativePose {
    float heading;
    float sin_rotation;
    float cos_rotation;
    float p_lgt;
    float p_lat;
    float v_lat;
    bool  point_on_dist_side;

    RelativePose() : heading(0.0f), sin_rotation(0.0f), cos_rotation(0.0f), p_lgt(0.0f), p_lat(0.0f), v_lat(0.0f), point_on_dist_side(false) {}
};

struct PredictPoseInfo {
    PredictObjMotion rel_pos_def;
    PredictObjMotion rel_pos_dec_long_time;
    PredictObjMotion rel_pos_dec_short_time;
    PredictObjMotion rel_pos_dec_trun_left;
    PredictObjMotion rel_pos_dec_trun_right;

    PredictPoseInfo() : rel_pos_def(), rel_pos_dec_long_time(), rel_pos_dec_short_time(), rel_pos_dec_trun_left(), rel_pos_dec_trun_right() {}
};

struct InPathInfo {
    bool in_path_default;
    bool in_path_pred_zero_length;
    bool in_path_pred_long_time;
    bool in_path_pred_short_time;
    bool in_path_pred_trun_left;
    bool in_path_pred_trun_right;

    InPathInfo()
        : in_path_default(false), in_path_pred_zero_length(false), in_path_pred_long_time(false), in_path_pred_short_time(false),
          in_path_pred_trun_left(false), in_path_pred_trun_right(false) {}
};

struct InPathData {
    PredictObjMotion inpath_long_pred;
    PredictObjMotion inpath_short_pred;

    InPathData() : inpath_long_pred(), inpath_short_pred() {}
};
struct CornerPoints {
    float close_left_lgt;
    float close_left_lat;
    float close_right_lgt;
    float close_right_lat;
    float remote_left_lgt;
    float remote_left_lat;
    float remote_right_lgt;
    float remote_right_lat;

    CornerPoints()
        : close_left_lgt(0.0f), close_left_lat(0.0f), close_right_lgt(0.0f), close_right_lat(0.0f), remote_left_lgt(0.0f), remote_left_lat(0.0f),
          remote_right_lgt(0.0f), remote_right_lat(0.0f) {}
};
struct CornerCorvedPoints {
    float close_left_lgt_corved;
    float close_left_lat_corved;
    float close_right_lgt_corved;
    float close_right_lat_corved;
    float remote_left_lgt_corved;
    float remote_left_lat_corved;
    float remote_right_lgt_corved;
    float remote_right_lat_corved;

    CornerCorvedPoints()
        : close_left_lgt_corved(0.0f), close_left_lat_corved(0.0f), close_right_lgt_corved(0.0f), close_right_lat_corved(0.0f),
          remote_left_lgt_corved(0.0f), remote_left_lat_corved(0.0f), remote_right_lgt_corved(0.0f), remote_right_lat_corved(0.0f) {}
};

struct ObjProjData {
    float dist_from_host_left  = 0.0;
    float dist_from_host_right = 0.0;
};

struct ObjProjInfo {
    ObjProjData proj_dist_defult;
    ObjProjData proj_dist_zero_length;
    ObjProjData proj_dist_long_pred;
    ObjProjData proj_dist_short_pred;
    ObjProjData proj_dist_trun_left;
    ObjProjData proj_dist_trun_right;
};

struct EdgeDistance {
    float closet_dist_r;
    float closet_dist_l;
    float far_dist_r;
    float far_dist_l;

    EdgeDistance() : closet_dist_r(0.0f), closet_dist_l(0.0f), far_dist_r(0.0f), far_dist_l(0.0f) {}
};

struct PossibleManoeuvres {
    bool obj_try_brake;
    bool obj_try_steer;
    bool obj_oncoming_inpath_long_pred;
    bool obj_oncoming_inpath_short_pred;
    bool obj_brake_long_pred;
    bool obj_brake_short_pred;
    bool obj_steer_left;
    bool obj_steer_right;

    PossibleManoeuvres()
        : obj_try_brake(false), obj_try_steer(false), obj_oncoming_inpath_long_pred(false), obj_oncoming_inpath_short_pred(false),
          obj_brake_long_pred(false), obj_brake_short_pred(false), obj_steer_left(false), obj_steer_right(false) {}
};

enum ObjectManoeuver {
    OBJ_MAVN_CURRENT          = 0,
    OBJ_MANV_PRED_STEER_LEFT  = 2,
    OBJ_MANV_PRED_BRAKE       = 1,
    OBJ_MANV_PRED_STEER_RIGHT = 3,
    OBJ_MANV_PRED_ZEROLENGTH  = 4,
    OBJ_MANV_PRED_DEF         = 5,
};

struct AsInPathDecision {
    AsInPathDecision();
    ~AsInPathDecision() noexcept;
    void Clear();
    void ProcessInPathDecision(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                               const SafetyMarginEvaluator &safemargin_eval, const AsVseOut &vse_out, const AsEgoPath &curv_path);

    static bool             LinearMovementPredictorWithStop(bool stopena, float &posn, float &spd, float &a, float t);
    static PredictObjMotion PredictObjectCurveMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                     PredictObjMotion pre_motion, float pred_time);

    const InPathData &GetResultData() const;
    const InPathData &GetCurrentInPathData() const;
    const InPathData &GetPredictInPathData() const;

  private:
    void CalInPathDataWithPredictPose(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                      const SafetyMarginEvaluator &safemargin_eval, const AsVseOut &vse_out, const AsEgoPath &curv_path);

    void CalInPathDataWithCurrentPose(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                      const SafetyMarginEvaluator &safemagin_eval, const AsVseOut &vse_out);

    InPathData SelectInPathData(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, const AsVseOut &vse_out, bool ttr_pred_valid);
    bool       CheckUsePredForTruck(const active_safety::AsObstacle &obj);

    void  CalCornerPoints(const AsVseOut &vse_out, const BoundingBox &bd_box, const active_safety::AsObstacle &obj);
    void  CalcAvoidanceManoeuvers(const active_safety::AsObstacle &obj);
    float CalcDeclerationForAovidance(const active_safety::AsObstacle &obj, float conf_value);
    bool  CalClosestCornerDistance(const AsVseOut &vse_out, const active_safety::AsObstacle &obj, float &min_lat);
    bool  CheckInPathGeometrically(const PredictOffset &pred_offst, bool cross_flag, float min_lat);
    bool  CheckSteeringOutOfPath(const AsVseOut &vse_out, const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, bool in_path_def);
    InPathData      CalcCreatInPathDataAtTTC(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                             const SafetyMarginEvaluator &safemargin_eval, const AsVseOut &vse_out, const AsEgoPath &curv_path,
                                             float ttc_value, bool is_ttr);
    bool            CalcInPathAsymmetricOffset(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, RelativePose rel_pos,
                                               ObjProjData &obj_proj, float lat_close_offs, float lat_far_offs, float ego_half_width, bool zero_length,
                                               bool symmetric_sta);
    PredictPoseInfo CalcPredictAccelerationAndPosition(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                       const SafetyMarginEvaluator &safemargin_eval, float ttc_value);
    PredictPoseInfo CalcNoPredAccAndPos(const active_safety::AsObstacle &obj, float head_sta);

    PredictPoseInfo CalcCircularPredAccAndPos(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, float ttc_value);

    PredictPoseInfo CalcLinearPredAccAndPos(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                            const SafetyMarginEvaluator &safemargin_eval, float ttc_value, AobjAvoidance avoid_a, float head_sta);

    PredictObjMotion CalcBrakingObjCircularMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, float ttc_value,
                                                  float decel_pre);

    PredictObjMotion CalcDefaultObjCircularMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, float ttc_value);

    PredictObjMotion CalcTurningObjCircularMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, float ttc_value,
                                                  float alat_steer, bool turn_left);

    PredictObjMotion CalcCartesianMovement(const active_safety::AsObstacle &obj, float crvt);

    PredictObjMotion CalcDefaultObjLinearMotion(const active_safety::AsObstacle &obj, float ttc_value);

    PredictObjMotion CalcBrakingObjLinearMotion(const active_safety::AsObstacle &obj, const SafetyMarginEvaluator &saffmargin_eval, float decel_pre,
                                                float ttc_value, float head_sta);

    PredictObjMotion CalcTurningObjLinearMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                const SafetyMarginEvaluator &safemargin_eval, float decel_pre, float ttc_value, bool turn_left);
    RelativePose CalcRelativePositionToHostPath(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, PredictObjMotion pre_pos,
                                                EgoMotionStateAtTime host_pred_info);
    float        CalcTransPosnToRemoteSide(float posn, float length, float heading);

    float CalcTransPosnFromRemoteSide(float posn, float length, float heading);

    PossibleManoeuvres CalcObjPossibleManoeuver(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, const AsVseOut &vse_out,
                                                bool is_ttr);
    PossibleManoeuvres CheckIfObjTriesToManoeuverTTR(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, const AsVseOut &vse_out);
    PossibleManoeuvres CheckIfObjTriesToManoeuverTTM(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, const AsVseOut &vse_out);
    PredictObjMotion   DetermineInPathDataAtPredTime(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval,
                                                     PossibleManoeuvres obj_manv, PredictPoseInfo pre_pos, bool is_long_pred, float obj_offs[6]);

    bool CompareManoeuvers(bool manv1, float a_manv1, bool manv2, float a_manv2);

    bool CheckObjLowLateralSpd(const active_safety::AsObstacle &obj);

    bool               CheckUsePredictionSta(bool use_outpath, bool use_inpath, bool inpath_ttr, bool inpath_curr, bool pred_valid);
    CornerPoints       corner_points;
    CornerCorvedPoints corner_corved_points;
    InPathData         inpath_curr_data;
    InPathData         inpath_pred_data;
    InPathData         inpath_data;

    AobjAvoidance obj_avoidance;

    // defaut, predict long time, short time, turn left, trun right
    RelativePose rel_pos_def;
    RelativePose rel_pos_long_time;
    RelativePose rel_pos_short_time;
    RelativePose rel_pos_turn_left;
    RelativePose rel_pos_turn_right;
    InPathInfo   in_path_info;

    ObjProjInfo proj_dist_info;

    bool obj_try_brake = false;
};
} // namespace tap
} // namespace senseAD
