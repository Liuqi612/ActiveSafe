#ifndef TAP_SDK_ALGORITHM_LONGSAFE_EGO_DRIVER_EVALUATOR_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_EGO_DRIVER_EVALUATOR_H_
#include "algorithm/longsafe/ego/curvature_path.h"
#include "algorithm/longsafe/longsafe_cals.h"
#include "algorithm/longsafe/threat_assessor/longsafe_obs.h"
#include "algorithm/vse/vehicle_state_estimed.h"
#include "math/historyinfo/historyinfo.h"
#include "math/signalprocess/off_delay_block/off_delay_block.h"
#include "math/signalprocess/relay_block/relay_block.h"

#include <array>

namespace active_safety {
namespace longsafe {

struct MotionLimit {
    float long_jerk_measd = 0.00F;
    float long_neg_accel_measd = 0.00F;
    float cmft_long_neg_accel = 0.00F;
    float cmft_long_neg_jerk = 0.00F;
    float cmft_long_pos_jerk = 0.00F;
    float cmft_long_pos_accel = 0.00F;
    float cmft_abs_lat_jerk = 0.00F;
    float cmft_abs_lat_accel = 0.00F;
    float cmft_abs_crvt_rate = 0.00F;
    float cmft_abs_crvt = 0.00F;
    float max_long_pos_accel = 0.00F;
    float max_long_pos_jerk = 0.00F;
    float max_abs_lat_jerk = 0.00F;
    float max_abs_lat_accel = 0.00F;
    float max_abs_crvt_rate = 0.00F;
    float max_abs_crvt = 0.00F;
    float min_long_neg_accel = 0.00F;
    float min_long_neg_jerk = 0.00F;
};

struct DrvrActvEventSts {
    bool drvr_braking = false;
    bool drvr_accelerating = false;
    bool drvr_decel = false;
    bool drvr_steer = false;
    bool drvr_steer_fast = false;
    bool accel_pedal_released = false;
    bool accel_pedal_pos_change_rate = false;
    bool acc_active = false;
    bool acc_braking = false;
    bool drvr_in_curve = false;
    bool low_speed = false;
    bool city_driving = false;
    bool high_steer_angle_rate = false;
};

struct MotionCompFactor {
    float crit_lat_comp_factor = 0.00F;
    float cmft_lat_comp_factor = 0.00F;
    float cmft_long_comp_factor = 0.00F;
    float frct_and_mass_factor = 0.00F;
};

class DriverEvaluator {
  public:
    DriverEvaluator();
    ~DriverEvaluator();
    void Run(const AsVseOut &vse_out, const LongSafeObject &obs);

    // driver active event status
    DrvrActvEventSts drvr_actv_sts_;

    // driver engage mode.
    int drvr_engage_ = 0;
    enum DrvrEngage { NotEngage = 0, Steer = 1 << 0, Brake = 1 << 1, Accel = 1 << 2 };
    // driver mode
    enum DrvrTranMode { AccelToTgt, BrkForTgt, OvtkTgt, NoChange, LaneChange, Cornrg, Brking };
    int drvr_tran_mode = NoChange;

    // motion limit
    MotionLimit motion_limit_;
    MotionCompFactor motion_factor_;

  private:
    // calibration
    DrvrEvaluatorCal drvr_cal_;
    // compensate factor.
    // 1  DriverTired
    // 2  Overtaking
    // 3  CityDriving
    // 4  CruiseControlActive
    // 5  DriverNotInVehicle
    // 6  HighSteeringWheelAngle
    // 7  CollisionSensitityEarly
    // 8  CollisionSensitivityLate
    // 9  PrimaryTargetAbnormalBehaviour
    // 10 DriverAggressive
    std::array<bool, INDIVIDUAL_ACTIVE_ARRAY_SIZE> contributing_factors_;

    // motion limit
    float curvature_to_steering_wheel_coeffcient_ = 0.0F;
    float jerk_meas_neg_k1_ = 0.0F;
    float longacc_meas_neg_k1_ = 0.0F;
    math::AsHistoryInfo<float> accel_delay_;
    math::OffDelayBlock drvr_accel_;
    math::RelayBlock drvr_steer_angle_relay_;
    math::OffDelayBlock drvr_steer_angle_offdly;
    math::RelayBlock drvr_steer_angle_fast_relay_;
    math::OffDelayBlock drvr_steer_angle_fast_offdly;

    void CalcMotionLimit(const AsVseOut &vse_out);
    void CalcCompensationFactor(const AsVseOut &vse_out);
    void MaxLatJerkAndAccelEstimed(const AsVseOut &vse_out);
    void MinLongAccelEstimed(const AsVseOut &vse_out);
    float CalcPredDrvrDecel(float host_speed, float slope, float offset, float predict_accel_limit);
    void LongPositiveAccEstimed(bool brake_pedal_apld);
    void CheckDriverDecelerating(const AsVseOut &vse_out);
    void CheckDriverBehaviorEvaluator(const AsVseOut &vse_out, const LongSafeObject &obs);
    void CheckDriverBraking(const AsVseOut &vse_out);
    void CheckDriverAccelerating(const AsVseOut &vse_out, const LongSafeObject &obs);
    void CheckDriverSteer(const AsVseOut &vse_out);
};

} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_EGO_DRIVER_EVALUATOR_H_
