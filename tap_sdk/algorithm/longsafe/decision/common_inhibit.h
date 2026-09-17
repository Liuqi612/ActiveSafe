#ifndef TAP_SDK_ALGORITHM_LONGSAFE_DECISION_COMMON_INHIBIT_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_DECISION_COMMON_INHIBIT_H_

#include "math/signalprocess/off_delay_block/off_delay_block.h"
#include "math/signalprocess/on_delay_block/on_delay_block.h"
#include "math/utils/util_math.h"
#include "algorithm/longsafe/longsafe_cals.h"
#include "threat_assessor.h"
namespace active_safety {
namespace longsafe {

#define YAW_RATE_NUM (100)

struct LtapInhibitor {
    bool target_high_curvature_inhibit = false;
    bool target_heading_inhibit        = false;
    bool recent_s_curvature_inhibit    = false;
    bool no_turning_inhibit            = false;
    bool not_tap_inhibit               = false;
    bool target_type_inhibit           = false;
    bool oncoming_confirm              = false;
    bool ego_turning_longtime          = false;
};
class CommonInhibit {

  public:
    CommonInhibit();
    ~CommonInhibit();
    CommonInhibitCal common_inhibit_cal_;

    void Update(const AsVseOut &vse_out, const LongSafeObject &obs, const ThreatAssessor &threat_assessor);

    LtapInhibitor ltap_inhibit_;

    bool spd_inhibit_              = false;
    bool host_avoid_inhibit_       = false;
    bool inhibit_res_              = false;
    bool ego_not_turning_          = false;
    bool no_recent_turn_change_    = false;
    bool ego_no_just_started_      = false;
    bool target_oncoming_confirm_  = false;
    bool ltap_inhibit_flag_        = false;

    float yaw_rate_sum_ = 0.0F;
    float yaw_rate_vector_[YAW_RATE_NUM];
    int   yaw_rate_vec_index_      = 0;
    bool  last_curvature_left_     = false;
    bool  last_curvature_right_    = false;
    bool  last_curvature_exit_left = false;
    int   ego_turning_cnt_         = 0;

    int  inpath_age_         = 0;
    bool inpath_age_inhibit_ = false;

    math::OffDelayBlock ego_turning_offdelay_;
    math::OffDelayBlock s_curvature_offdelay_;
    math::OffDelayBlock recent_turn_change_offdelay_;
    math::OffDelayBlock ego_just_started_;
    math::OffDelayBlock ego_turning_longtime_offdelay_;

    math::OnDelayBlock ego_turn_around_ondelay_;

    void  SpdInhibit(const LongSafeObject &obs, const AsVseOut &vse_out);
    void  HostAvoidInhibit(const AsVseOut &vse_out, const ThreatAssessor &threat_assessor);
    void  LtapInhibit(const LongSafeObject &obs, const AsVseOut &vse_out);
    float CalcIntegAngle(const AsVseOut &vse_out);
    void  CheckScurvature(const AsVseOut &vse_out);
    void  CheckEgoTurnLongTime(const AsVseOut &vse_out);
    void  CheckTarOncoming(const LongSafeObject &obs);
    void  CheckInPathAgeInhibit(const LongSafeObject &obs);
};

} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_DECISION_COMMON_INHIBIT_H_
