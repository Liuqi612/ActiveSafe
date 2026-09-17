/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_ALGORITHM_LONGSAFE_2024_SCENARIO_ANALYSIS_SOCIETY_SCENE_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_2024_SCENARIO_ANALYSIS_SOCIETY_SCENE_H_
#include "algorithm/longsafe_2024/algo_interface/active_safety_vse.h"
#include "algorithm/longsafe_2024/param/as_param.h"
#include "algorithm/obstacle/obstacle.h"
#include "algorithm/vse/vehicle_state_estimed.h"
#include "math/lookuptable/lookuptable.h"
#include "math/utils/util_math.h"

#include <cmath>

namespace senseAD {
namespace tap {

struct SpeedCheckParam {
    int target_speed;         // 目标车速(kph)
    float speed_err;          // 车速误差阈值
    int &confirm_cnt;         // 车速确认计数（引用）
    bool &confirm_ok;         // 车速确认状态（引用）
    int &not_speed_delay_cnt; // 非目标车速延迟计数（引用）
    int dec_step;             // 计数递减步长
    int confirm_thrd;         // 确认阈值
};
namespace math = active_safety::math;
using namespace active_safety::math;

class AsSocietyScene {
  public:
    AsSocietyScene();
    ~AsSocietyScene();
    void ProcessSocietyScene(const active_safety::AsObstacleList &obj_list, const AsVseOut &vse_out, const AsParamConfig_T &longparam);
    bool GetDisableJustStartValid() const { return ego_just_start_state_disabled; };
    bool GetTestSceneFlg() const { return ego_at_test_scene_; };
    bool GetTurnConstandSpdFlag() const {return ego_at_turn_scene_;};

  private:
    void CheckTestSceneBaseEgoInfo(const active_safety::AsObstacleList &obj_list);
    void CheckEgoFromStationaryToStart();
    void InvalidateEgoJustStartState();
    void UpdateEgoTestSceneState();
    void UpdateEgoTurnSceneState();

    void CheckEgoConstantSpeedDuration();
    void CheckAroundCar(const active_safety::AsObstacle &obj);
    void CheckAroundTruck(const active_safety::AsObstacle &obj);
    void CheckSurroundingEnvironment(const active_safety::AsObstacleList &obj_list);
    void ResetSurroundingEnvironmentCounters();
    void UpdateEgoVehicleState(const AsVseOut& vse_out);
    bool IsEgoInAutoDrivingState(const AsVseOut& vse_out);

    void CheckSimulationMode(bool simulation_enabled);
    void ResetEgoSpeedConfirmCounters();
    void ResetEgoSpeedDelayCounters();
    void UpdateEgoStartValidTimeCounter(const bool is_ego_started);
    void UpdateSpeedConfirmState(SpeedCheckParam &param, bool is_curvature_valid);
    void UpdateEgoConstantSpeedFlags();
    AsVseOut ego_;

    int backforward_moving_car = 0;
    int ego_stright_inpath_car = 0;
    int backforward_moving_truck = 0;
    int tap_moving_forward_car = 0;

    // ego infomation
    float display_spd_kph_ = 0;
    bool within_validtime_after_ego_start_ = false;
    bool ego_just_start_state_disabled = false;
    bool ego_during_turn_constant_spd_ = false;
    bool ego_during_stright_constant_spd_ = false;
    bool ego_cross_constant_spd_ = false;
    int validtime_after_ego_start_cnt = 0;
    bool ego_stationaty_ = false;
    bool pre_ego_stationary_ = false;
    bool ego_at_test_scene_ = false;
    bool ego_at_turn_scene_ = false;

    bool ego_10kph_confirmeok = false;
    bool ego_20kph_confirmeok = false;
    bool ego_30kph_confirmeok = false;
    bool ego_40kph_confirmeok = false;
    bool ego_50kph_confirmeok = false;
    bool ego_60kph_confirmeok = false;
    bool ego_70kph_confirmeok = false;
    bool ego_80kph_confirmeok = false;

    int ego_10kph_confirm_cnt = 0;
    int ego_20kph_confirm_cnt = 0;
    int ego_30kph_confirm_cnt = 0;
    int ego_40kph_confirm_cnt = 0;
    int ego_50kph_confirm_cnt = 0;
    int ego_60kph_confirm_cnt = 0;
    int ego_70kph_confirm_cnt = 0;
    int ego_80kph_confirm_cnt = 0;

    int ego_not_10kph_delay_cnt = 0;
    int ego_not_20kph_delay_cnt = 0;
    int ego_not_30kph_delay_cnt = 0;
    int ego_not_40kph_delay_cnt = 0;
    int ego_not_50kph_delay_cnt = 0;
    int ego_not_60kph_delay_cnt = 0;
    int ego_not_70kph_delay_cnt = 0;
    int ego_not_80kph_delay_cnt = 0;

    uint32_t simulation_check_cnt = 0;
    bool simulation_check = false; // 仅仿真模式预热期间为 true
    bool is_auto_driving_ = false;
    bool test_scene_enabled = false;
};

} // namespace tap
} // namespace senseAD
#endif // TAP_SDK_ALGORITHM_LONGSAFE_2024_SCENARIO_ANALYSIS_SOCIETY_SCENE_H_
