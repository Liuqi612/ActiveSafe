#include "cip_evaluator.h"

#include "obj_eval_param.h"

#include <cmath>
namespace senseAD {
namespace tap {
AsCipEvaluator::AsCipEvaluator() {
}
AsCipEvaluator::~AsCipEvaluator() = default;
AsCipEvaluatorParam cip_param;
void                AsCipEvaluator::ProcessCipEvaluator(const active_safety::AsObstacle &cip_obj, const AsVseOut &vse_out) {
    CheckIsCipScene(cip_obj, vse_out);
    CheckOverlap(cip_obj, vse_out);
}
void AsCipEvaluator::CheckIsCipScene(const active_safety::AsObstacle &cip_obj, const AsVseOut &vse_out) {
    // if (vse_out.host_state == AsHostState::AS_HOST_IN_HARD_CURVE) {
    //     cip_flag = false;
    // } else {
    //     bool validPos = cip_obj.long_posn > 0;
    //     cip_flag = validPos;
    // }
}
void AsCipEvaluator::CheckOverlap(const active_safety::AsObstacle &cip_obj, const AsVseOut &vse_out) {
    bool isOverlap = false;
    // bool isCipObjHdgValid =
    //     (fabsf(cip_obj.heading) < 0.52 || fabsf(cip_obj.heading) > 2.6);
    float xolc_funnel = active_safety::math::LookUpTable::LookupTable1D<8>(cip_param.k_xolc_funnel_range_points, cip_param.k_xolc_funnel_width,
                                                                           cip_obj.long_posn - vse_out.host_dist_to_front);
    float ct_long_pos = cip_obj.long_posn + cosf(cip_obj.heading) * 0.5 * cip_obj.length;
    float squard_pos  = ct_long_pos * ct_long_pos;
    float xolc        = 0.5 * vse_out.rear_curvature * squard_pos + 0.16667 * vse_out.rear_curvaturerate * squard_pos * ct_long_pos;
    if (fabsf(xolc) > xolc_funnel) {
        isOverlap = true;
    }
    Set(isOverlap && cip_flag, AsScenarioDiscInfo::AS_CIP_LOW_OVERLAP);
}
void AsCipEvaluator::CheckObjectSuddenlyDetect(const active_safety::AsObstacle &cip_obj) {
    // bool object_close_first_detect = false;
    // if (cip_obj.fus_trkID != fus_id && cip_obj.fus_trkID > 0 &&
    //     cip_obj.long_posn < 10.0f && cip_obj.lat_posn < 1.0f) {
    //   object_close_first_detect = true;
    // }
    fus_id = cip_obj.fus_trkID;
    // Set(object_close_first_detect && cip_flag,
    //     AsScenarioDiscInfo::AS_CIP_OBJ_CLOSE_FITST_DETECT);
}

} // namespace tap
} // namespace senseAD
