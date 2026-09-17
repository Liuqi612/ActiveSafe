#ifndef TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_SAFE_MARGIN_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_SAFE_MARGIN_H_
#include "algorithm/vse/vehicle_state_estimed.h"
#include "longsafe_obs.h"

namespace active_safety {
namespace longsafe {

using math::LookUpTable;

class SafeMargin {
  public:
    SafeMargin();
    ~SafeMargin();

    static void CalculateSafeMargin(const AsVseOut &vse_out, LgSfObsData &obs_data);

  private:
    static void CalcInPathOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);

    static void CalcLatInPathOffsetForLtap(LgSfObsData &obs_data);

    static void CalcBoundingBox(LgSfObsData &obs_data);

    static void CalcObjLength(LgSfObsData &obs_data);

    static void CalcObjWidth(LgSfObsData &obs_data);

    static void CalcLongPredTimeOffset(LgSfObsData &obs_data, float host_long_vel);

    static void CalcShortPredTimeOffset(LgSfObsData &obs_data, float host_long_vel, float host_dist_to_front, bool aeb_active, bool straight_driving);

    static void CalcLateralManoeuverOffset(LgSfObsData &obs_data, float host_long_vel);

    static void CalcLateralIntersectionOffset(LgSfObsData &obs_data, float long_vel);

    static void CalcPedInpathPredOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);
    static void CalcPedInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);

    static void CalcBikeInpathPredOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);
    static void CalcBikeInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);
    static void CalcGodInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);
    static void CalcGenobjInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);

    static void CalcCarInpathPredOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);
    static void CalcCarInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);

    static void CalcTruckBusInpathPredOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);
    static void CalcTruckBusInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);

    static void CalcMotorBikeInpathPredOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);
    static void CalcMotorBikeInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data);

    static SafeMarginCal safemargin_cal_;
};
} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_SAFE_MARGIN_H_
