#ifndef TAP_SDK_ALGORITHM_LONGSAFE_DECISION_THREAT_ASSESSOR_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_DECISION_THREAT_ASSESSOR_H_
#include "algorithm/longsafe/ego/driver_evaluator.h"
#include "algorithm/longsafe/threat_assessor/longsafe_obs.h"
#include "algorithm/longsafe/threat_assessor/motion_curve_predict.h"
#include "algorithm/longsafe/threat_assessor/motion_linear_predict.h"
#include "algorithm/vse/vehicle_state_estimed.h"
#include "math/geometry/geometry.h"

#define LTAP_TIME_NUM            150
#define LTAP_TTI_AROUND_TIME_NUM 11
#define LTAP_TIME_STEP           0.02F

namespace active_safety {
namespace longsafe {

using math::Geometry;
using math::Point2D;
using Intersection = Geometry::SegmentCircleIntersection;

struct LtapEdge {
    Point2D p0;
    Point2D p1;
};

struct LtapLongDistInfo {
    float dist_near;
    float dist_far;
};

class ThreatAssessor {
  public:
    ThreatAssessor();
    ~ThreatAssessor();

    void Update(const AsVseOut &vse_out, const DriverEvaluator &drvr_sts, const LongSafeObject &obs, const AsCurvaturePath &ego_path);
    void VehDelayComp(const AsVseOut &vse_out, const DriverEvaluator &drvr_sts, const LongSafeObject &obs);
    void ThreatEvaluator(const AsVseOut &vse_out, const LongSafeObject &obs, const DriverEvaluator &drvr_evaluator);
    void CircularPredictAlgorithm(const LongSafeObject &obs, float time, MotionPredict &motion_predict);
    void LinearPredictAlgorithm(const LongSafeObject &obs, float time, MotionPredict &motion_predict);
    void HostPredictAlgorithm(const AsVseOut &vse_out, float time, MotionPredict &motion_predict);
    void TransformObject();
    void ObjectPredictPath(const LongSafeObject &obs);
    void CollectStateData(const AsVseOut &vse_out, const DriverEvaluator &drvr_sts, const LongSafeObject &obs);
    void EstimateObjectPosInpath(float offs_lat_inpath_primary_target, float offs_lgt_short_pred);
    void LtapThreatAssessLongitudinal();
    void LtapThreatAssessLateral(const LongSafeObject &obs, const AsCurvaturePath &ego_path);
    void CalcFcwTtcByDist(const AsVseOut &vse_out, const LongSafeObject &obs);
    void CalcTimeToBrake(float host_spd, float host_accel, float tgt_spd, float tgt_accel, float desired_hit_spd);
    void CalcTtrTimeDistNear(const AsCurvaturePath &ego_path, const LongSafeObject &obs, const AsVseOut &vse_out);
    void StopDistanceFactorCal(const AsVseOut &vse_out, const LongSafeObject &obs, const DriverEvaluator &drvr_evaluator);

    float CalcObsTTBTravelBeforeStop(float tgt_spd, float tgt_accel);

    float CalcMinDecelTimeWithConstJerk(float desired_spd, float host_spd, float host_accel, float jerk);

    std::array<LtapEdge, 3> LtapGetLongClosestEdge(float lgt_pos, float lat_pos, float heading);

    LtapLongDistInfo CalcHostStraightLongDist(const LtapEdge &edge, float half_host_width, float host_rear_bump_dist);
    LtapLongDistInfo CalcHostCurveLongDist(const LtapEdge &edge, float half_host_width);

    bool LtapLongDistForEndInPath(const Point2D &pt, float host_rear_bump_dist, float left_radius, float right_radius, float center_radius,
                                  float host_raduis, Intersection &inter_sec);

    enum LtapEdgeType { FRONT, RIGHT, REAR, LEFT };

    void LtapFindLatClosestEdges(float lgt_pos, float lat_pos, float heading, float l0, float width, int index, const MotionStateAtTime host_state);

    struct LtapHostData {
        float c0;
        float v0;
        float a0;
        float amin;
        float amax;
        float tj_brake;
        float tj_accel;
        float cmax;
        float length;
        float width;
        float d0;
        float ttheta_left;
        float ttheta_right;
    };

    struct LtapObjData {
        float offs_lat;
        float width;
        float length;
        float l0;
    };

    bool threat_autobraking_ = false;
    bool threat_iba_         = false;
    bool threat_abp_         = false;
    bool threat_aba_         = false;

    float veh_delay_time_;
    float veh_delay_host_travel_;
    float veh_delay_obs_travel_;

    std::array<float, LTAP_TIME_NUM> obj_pred_lgt_pos_;
    std::array<float, LTAP_TIME_NUM> obj_pred_lat_pos_;
    std::array<float, LTAP_TIME_NUM> obj_pred_heading_;
    //
    std::array<float, LTAP_TIME_NUM> obj_dist_near_;
    std::array<float, LTAP_TIME_NUM> obj_lgt_jerk_;
    std::array<float, LTAP_TIME_NUM> obj_dist_far_;
    std::array<bool, LTAP_TIME_NUM>  obj_inpath_;
    //
    std::array<std::array<LtapEdge, 3>, LTAP_TTI_AROUND_TIME_NUM> obj_edges_;

    // ltap threat value.
    float rqrd_neg_lgt_jerk_;
    float rqrd_pos_lgt_accel_;
    float rqrd_neg_lgt_accel_;
    float rqrd_left_crvt_;
    float rqrd_right_crvt_;
    float rqrd_left_crvt_rate_;
    float rqrd_right_crvt_rate_;

    float fcw_ttc;
    // consider actuator response.
    float brk_low_delay_time_;
    float brk_low_during_time_;
    float brk_high_delay_time_;
    float brk_high_during_time_;
    float brk_full_delay_time_;
    float brk_full_during_time_;
    float threat_range_;
    float min_dist_near_;
    float aeb_dist_factor_;
    float iba_dist_factor_ = 1.0;

    LtapHostData      host_data_;
    LtapObjData       obj_data_;
    MotionStateAtTime curr_host_sts_;

    MotionPredict     linear_predict_;
    MotionPredict     circular_predict_;
    MotionPredict     host_predict_;
    MotionStateAtTime host_state_;
    ThreatAssessorCal threat_ass_cal_;
};

} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_DECISION_THREAT_ASSESSOR_H_
