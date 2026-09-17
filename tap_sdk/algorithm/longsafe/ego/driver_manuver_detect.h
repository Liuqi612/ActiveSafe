#ifndef TAP_SDK_ALGORITHM_LONGSAFE_EGO_DRIVER_MANUVER_DETECT_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_EGO_DRIVER_MANUVER_DETECT_H_
#include "longsafe_cals.h"
#include "threat_assessor/longsafe_obs.h"
#include "algorithm/vse/vehicle_state_estimed.h"
#include "math/signalprocess/off_delay_block/off_delay_block.h"
#include "math/signalprocess/on_delay_block/on_delay_block.h"

#include <array>

namespace active_safety {
namespace longsafe {

class DriverManuverDetect {
  public:
    DriverManuverDetect();
    ~DriverManuverDetect();

    void Update(const AsVseOut &vse_out);

    bool drv_turn_  = false;
    bool drv_accel_ = false;
    bool drv_brake_ = false;

  private:
    void CheckDrvTurn(const AsVseOut &vse_out);
    void CheckDrvAccel(const AsVseOut &vse_out);
    void CheckDrvBrake(const AsVseOut &vse_out);

    math::OnDelayBlock  str_angle_inhibit_ondly_;
    math::OffDelayBlock drv_turn_offdly;

    DrvManuverDetCal drv_det_cal_;
};

} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_EGO_DRIVER_MANUVER_DETECT_H_
