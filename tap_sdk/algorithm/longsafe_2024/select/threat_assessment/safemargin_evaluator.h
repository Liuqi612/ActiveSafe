/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include "algorithm/longsafe_2024/algo_interface/active_safety_vse.h"
#include "algorithm/longsafe_2024/algo_interface/as_enum_type.h"
#include "algorithm/longsafe_2024/algo_interface/as_fusion_object.h"
#include "math/lookuptable/lookuptable.h"
#include "math/utils/util_math.h"
#include "algorithm/obstacle/obstacle.h"
#include "coll_eval.h"
#include "ego_path.h"
#include "longsafe_cal.h"

namespace senseAD {
namespace tap {


struct PredictOffset {
    float offs_lgt_long_pred;
    float offs_lat_long_pred;
    float offs_lgt_short_pred;
    float offs_lat_short_pred;
    float offs_lat_manoeuvre;
    float offs_lat_in_path_primary_target;
    float offs_lat_in_path_close_edge;
    float offs_lat_in_path_far_edge;
    float offs_lat_intersection;
    float offs_lat_multi_target;

    PredictOffset()
        : offs_lgt_long_pred(0.0f), offs_lat_long_pred(0.0f), offs_lgt_short_pred(0.0f), offs_lat_short_pred(0.0f), offs_lat_manoeuvre(0.0f),
          offs_lat_in_path_primary_target(0.0f), offs_lat_in_path_close_edge(0.0f), offs_lat_in_path_far_edge(0.0f), offs_lat_intersection(0.0f),
          offs_lat_multi_target(0.0f) {}
};

struct CurvCoordPose {
    float curv;
    float curv_radius;
    float pos_lat_rel;
    float spd_lat_rel;

    CurvCoordPose() : curv(0.0f), curv_radius(0.0f), pos_lat_rel(0.0f), spd_lat_rel(0.0f) {}
};

class SafetyMarginEvaluator {
  public:
    SafetyMarginEvaluator();
    ~SafetyMarginEvaluator() noexcept;

    void          Clear();
    void          ProcessSafetyMarginEvaluator(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eva, const AsEgoPath &curv_path,
                                               const AsVseOut &vse_out);
    CurvCoordPose curv_coord_info;
    PredictOffset predict_offset;
    float         cos_heading    = 0.0f;
    float         sin_heading    = 0.0f;
    bool          pred_ttr_valid = false;
    bool          pred_ttm_valid = false;
    float         modified_ttr   = 100.0f;

  private:
    void CalcHeadingFromVelocity(const active_safety::AsObstacle &obj);

    void CalcCoordTransformToCurve(const active_safety::AsObstacle &obj, const AsVseOut &vse_out);

    float CalcModifiedTTR(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float ttc_raw);

    bool CheckPredictValidity(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eva, const AsEgoPath &curv_path, float ttc);

    void  CalcDetermineOffset(const active_safety::AsObstacle &obj, const CollisionEvaluator &coll_eva, const AsVseOut &vse_out);
    void  CalcLongPredTimeOffset(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float half_width, float half_length,
                                 PredictOffset &predoffst);
    void  CalcShortPredTimeOffset(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float half_width, float half_length,
                                  PredictOffset &predoffst);
    void  CalcLateralManoeuverOffset(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float half_width, PredictOffset &predoffst);
    void  CalcLatInPathOffsetForLTAP(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float half_width, PredictOffset &predoffst);
    void  CalcLatInPathOffset(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, PredictOffset &predoffst);
    void  CalcLateralIntersectionOffset(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, PredictOffset &predoffst);
    void  CalcLateralOffsetForMultipleTgt(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, float half_width, PredictOffset &predoffst);
    float CalcVerifiedFarEdgeOffset(float width, float inpath_offs);
    void  ProjectedBicycleInfo(const CollisionEvaluator &coll_eva, float &half_proj_cycle_length, float &half_proj_cycle_width);
    SafetyMarginEvalatorCal safemagin_param;
};
} // namespace tap
} // namespace senseAD
