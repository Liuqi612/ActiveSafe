#include "driver_manuver_detect.h"

namespace active_safety {
namespace longsafe {
DriverManuverDetect::DriverManuverDetect() {
}
DriverManuverDetect::~DriverManuverDetect() = default;

void DriverManuverDetect::Update(const AsVseOut &vse_out) {
}

void DriverManuverDetect::CheckDrvTurn(const AsVseOut &vse_out) {
    float str_ang_thres = math::LookUpTable::LookupTable1D<9>(drv_det_cal_.k_host_spd_x, drv_det_cal_.k_hard_turn_strang_y, vse_out.speed);

    (void)str_angle_inhibit_ondly_.onDelay(fabs(vse_out.steerwheelangle) > str_ang_thres, drv_det_cal_.k_drv_strang_turn_ondelay_time, LGSF_FUNC_TIME_STEP);

    float str_ang_rate_thres = math::LookUpTable::LookupTable1D<9>(drv_det_cal_.k_host_spd_x, drv_det_cal_.k_hard_turn_strangrate_y, vse_out.speed);

    bool str_fast = fabs(vse_out.steerwheelangle_rate) > str_ang_rate_thres;

    drv_turn_ = (str_angle_inhibit_ondly_.getStateOut() || str_fast) && vse_out.speed > drv_det_cal_.k_zero_spd_thres;
    drv_turn_ = drv_turn_offdly.offDelay(drv_turn_, drv_det_cal_.k_drv_turn_inhibit_time, LGSF_FUNC_TIME_STEP);
}

void DriverManuverDetect::CheckDrvAccel(const AsVseOut &vse_out) {
  
}

void DriverManuverDetect::CheckDrvBrake(const AsVseOut &vse_out) {
}

} // namespace longsafe
} // namespace active_safety