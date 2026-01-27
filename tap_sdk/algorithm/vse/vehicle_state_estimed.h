#pragma once
#include "Eigen/Dense"
#include "common/global_config.h"
#include "interface/active_safety_vse.h"
#include "interface/vse_input.h"
#include "math/historyinfo/historyinfo.h"
#include "math/kalman_filter/kalman_filter.h"
#include "math/lookuptable/lookuptable.h"
#include "math/utils/util_math.h"
#include "vse_types.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <math.h>
#include <memory>
#include <time.h>

namespace active_safety {

class VehicleStateEstimed {
  public:
    VehicleStateEstimed();
    ~VehicleStateEstimed() = default;

    void Init();
    void Run(const VseInput &vse_input, uint64_t curtime);

    Eigen::Vector3f TransformPosForDelay(float deltaTm) const;
    // Vse Output
    AsVseOut vse_ipc_;

  private:
    void  UpdateSteerInfo();
    void  CalcLongVelocityAndAccel();
    void  CalcLatVelocityAndAccel();
    void  UpdateBcmAcuBcsInfo();
    void  CalcCurvatureAndSideSlip();
    void  CalcHeadingSeries();
    void  CalcTrajectorySeries();
    void  CheckHostStraightDriving();
    void  SeriesRecord();
    float FilterYawRate(float yawrate_rps);

    AsVseCal vse_cal_;
    // Vse persistant input info.
    VseInput           vse_inport_;
    math::KalmanFilter curvature_filter_;
    math::KalmanFilter speed_filter_;  // 速度估计卡尔曼滤波器

    bool     f_prev_abs_triggered_{0};
    uint64_t curtime_ms_{0};
    uint64_t prev_time_{0};
    float    dist_based_curv_{0};
    float    curv_dist_{0};
    float    curv_integ_yaw_{0};
    float    yawrate_filtered_{0};
    float    host_speed_est_;

    math::AsHistoryInfo<uint64_t> time_series;
    math::AsHistoryInfo<float>    yawrate_series;
    math::AsHistoryInfo<float>    rear_sideslip_series;
    math::AsHistoryInfo<float>    rear_curv_series;
    math::AsHistoryInfo<float>    rear_posx_series;
    math::AsHistoryInfo<float>    rear_posy_series;
    math::AsHistoryInfo<float>    speed_series;
    math::AsHistoryInfo<float>    heading_series;
};

} // namespace active_safety
