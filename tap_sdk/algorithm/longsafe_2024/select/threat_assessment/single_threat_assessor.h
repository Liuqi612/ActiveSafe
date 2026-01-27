/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include "coll_eval.h"
#include "ego_path.h"
#include "inpath_decision.h"
#include "algorithm/obstacle/obstacle.h"
#include "obstacle_data.h"
#include "safemargin_evaluator.h"

namespace math = active_safety::math;
using namespace active_safety::math;


namespace senseAD {
namespace tap {

struct LateralAccForIntv {
    float a_lat_req;
    float pos_lat_rel;
    float side_lat;

    LateralAccForIntv() : a_lat_req(0.0f), pos_lat_rel(0.0f), side_lat(0.0f) {}
};

struct MtnWarnRequired {
    float a_lat_req;
    float a_lat_quality;
    float a_neg_lgt_warn;
    float a_neg_lgt_intv;

    MtnWarnRequired() : a_lat_req(0.0f), a_lat_quality(0.0f), a_neg_lgt_warn(0.0f), a_neg_lgt_intv(0.0f) {}
};

struct MtnIntvRequired {
    float a_lat_req;
    float a_lat_quality;
    float a_pos_lgt;
    float a_neg_lgt;
    float jerk_neg_lgt;
    float crvt_rate_left;
    float crvt_rate_right;
    float crvt_left;
    float crvt_right;
    float ttc_value;

    MtnIntvRequired()
        : a_lat_req(0.0f), a_lat_quality(0.0f), a_pos_lgt(0.0f), a_neg_lgt(0.0f), jerk_neg_lgt(0.0f), crvt_rate_left(0.0f), crvt_rate_right(0.0f),
          crvt_left(0.0f), crvt_right(0.0f), ttc_value(0.0f) {}
};

struct PrimaryTarget {
    bool                      new_ta_found = false;
    active_safety::AsObstacle obj          = active_safety::AsObstacle{};
    AsObstacleData            obj_data     = AsObstacleData{};
    float                     a_lat_req    = 0.0;
    float                     a_lgt_req    = 0.0;
};

struct AsPrimDataForIntv {
    PrimaryTarget   prim_tgt;
    MtnIntvRequired mtn_req;
};

struct AsPrimDataForWarn {
    PrimaryTarget   prim_tgt;
    MtnWarnRequired mtn_req;
};

class AsSingleThreatAssessor {
  public:
    AsSingleThreatAssessor();

    ~AsSingleThreatAssessor() noexcept;

    void FindPrimaryTargetForWarn(const active_safety::AsObstacle &obj, const AsObstacleData &obj_data, const AsEgoPath &curv_path,
                                  const AsVseOut &vse_out);
    void FindPrimaryTargetForIntv(const active_safety::AsObstacle &obj, const AsObstacleData &obj_data, const AsEgoPath &curv_path,
                                  const AsVseOut &vse_out);
    void ThreatAssesorForWarn(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, const SafetyMarginEvaluator &safemargin_eval,
                              const AsInPathDecision &ip_des, const AsEgoPath &curv_path, const AsVseOut &vse_out);
    void ThreatAssesorForIntv(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, const SafetyMarginEvaluator &safemargin_eval,
                              const AsInPathDecision &ip_des, const AsVseOut &vse_out);
    void ResetPrimaryTargetData();
    AsPrimDataForIntv GetIntvPrimData() const;
    AsPrimDataForWarn GetWarnPrimData() const;

  private:
    bool CheckEnableForIntv(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, const AsInPathDecision &ip_des,
                            bool predict_valid);
    bool CheckEnableForWarn(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, const AsInPathDecision &ip_des,
                            const AsVseOut &vse_out);

    float RequireLgtAccelerationCalc(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, const AsEgoPath &curv_path,
                                     const AsVseOut &vse_out, PredictObjMotion pred_motion, float offset_lgt, float offset_lat, float pred_time);
    float CalcBrakeDelayTime(const AsVseOut &vse_out) const;
    PredictObjMotion  CalcCatesianMovement(PredictObjMotion pre_motion);
    PredictObjMotion  PredictObjectMotion(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, PredictObjMotion pre_motion,
                                          float pred_time);
    LateralAccForIntv LatAccelerationEstimatorCalc(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, const AsVseOut &vse_out,
                                                   PredictObjMotion pred_motion, float offs_lat_short_pred, float ttc_lgt) const;
    bool CheckPredictionValidity(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eval, float endtimeofpath, float pred_time);
    EdgeDistance LateralEdgeDistCalc(const AsVseOut &vse_out, RelativePose rel_pos, BoundingBox boudbox, PredictObjMotion transcoord, float offset_lat,
                                     bool onside) const;
    RelativePose RelativePositionCalc(BoundingBox boudbox, AsObstacleMotionType motiontype, float ego_heading, float obj_heading);
    float        RequiredAccForInPathObject(float obj_aLgt, float obj_vlgt, float rel_plgt, float ego_vlgt, AsObstacleMotionType mot_type);
    PredictObjMotion TransRotateCoordSys(const PredictObjMotion &obj_pred, const EgoMotionStateAtTime &ego_pred);
    float            CalcRequiredAccLat(float rel_pos, float ttr, float width, float offlat) const;
    bool             CheckIfSolutionExist(float dist, float v_rel, float a_rel);
    float            LateralTtcCalc(bool left_closest, float v_lat, float a_lat, float dist_left, float dist_right);
    float            RemoveNoise(float raw, float threshold);

    PrimaryTarget m_prim_algt_warn;
    PrimaryTarget m_prim_posnlgt_warn;

    PrimaryTarget m_prim_algt_intv;
    PrimaryTarget m_prim_alat_intv;
    PrimaryTarget m_prim_posnlgt_intv;

    AsPrimDataForIntv prim_data_intv;
    AsPrimDataForWarn prim_data_warn;
};

} // namespace tap
} // namespace senseAD
