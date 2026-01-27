/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include "algorithm/longsafe_2024/algo_interface/active_safety_vse.h"
#include "algorithm/longsafe_2024/algo_interface/as_fusion_object.h"
#include "algorithm/longsafe_2024/param/as_param.h"
#include "algorithm/obstacle/obstacle.h"
#include "algorithm/vse/vehicle_state_estimed.h"
#include "math/lookuptable/lookuptable.h"
#include "math/utils/util_math.h"

#include <cmath>

namespace senseAD {
namespace tap {
enum AsSocierySceneData {
    AS_TEST_SCENE          = (1 << 0),
    AS_SOCIERY_OBJ_EVALUAT = (1 << 1),
    AS_COMPLEX_SCENE       = (1 << 2),
    AS_STRICT_SCP_SCENE    = (1 << 3),
    AS_STRICT_CPNCO_SCENE  = (1 << 4),
    AS_STRICT_CPFAO_SCENE  = (1 << 5),
    AS_STRICT_CBNAO_SCENE  = (1 << 6),
    AS_STRICT_CSFAO_SCENE  = (1 << 7),
    AS_STRICT_SCPO_SCENE   = (1 << 8)
};

namespace math = active_safety::math;
using namespace active_safety::math;

class AsSocietyScene {
  public:
    AsSocietyScene();
    ~AsSocietyScene();
    bool     IsTestScene() const;
    uint32_t GetSocietySceneResult() const;
    void     ProcessSocietyScene(const active_safety::AsObstacleList &obj_list, const AsVseOut &vse_out, const AsParamConfig_T &longparam);
    int      GetStrictScpObj() const;
    int      GetStrictCpncoObj() const;

    int  GetCptalObj() const;
    int  GetCstaRnObj() const;
    bool GetCptalObjRequire() const;
    bool GetCstaRnObjRequire() const;
    bool GetTurnConstandSpdFlag() const;

    int GetCpfaoObj() const;
    int GetCbnaoObj() const;
    int GetCsfaoObj() const;
    int GetScpoObj() const;

    bool GetCpfaoObjRequire() const;
    bool GetCbnaoObjRequire() const;
    bool GetCsfaoObjRequire() const;
    bool GetScpoObjRequire() const;

    bool GetJustStartValid() const;
    bool GetConstantSpdValid() const;
    bool GetDisableJustStartValid() const { return disable_just_start; };

  private:
    void CalcTestScene(const active_safety::AsObstacleList &obj_list);
    void ProcessObstacles(const active_safety::AsObstacleList &obj_list);
    void ProcessTruckObsctacle(const active_safety::AsObstacle &obj);
    void EgoAtComplexScenePrev(const active_safety::AsObstacleList &obj_list);
    void DecideStrictScp(const active_safety::AsObstacleList &obj_list);
    void DecideStrictCpnco(const active_safety::AsObstacleList &obj_list);

    void DecideCpta_L(const active_safety::AsObstacleList &obj_list);
    void DecideCsta_Rn(const active_safety::AsObstacleList &obj_list);

    void CheckSceneBaseEgoInfo(const active_safety::AsObstacleList &obj_list);
    void CheckEgoJustStationary2Start(const active_safety::AsObstacleList &obj_list);
    void DisableEgoJustStartValid();
    void ResetCrossTapObj();
    void CheckEgoConstantSpdForTime();
    void CheckBehindCar(const active_safety::AsObstacle &obj);
    void CheckBehindTruck(const active_safety::AsObstacle &obj);

    void CrossingSceneCheck(const active_safety::AsObstacleList &obj_list);
    void CrossingObjProcess(const active_safety::AsObstacle &obj);
    void CalPoseLongThdForBrake();

    void CheckCpfaoBarrierCar(const active_safety::AsObstacle &obj);
    void CheckCsfaoBarrierCar(const active_safety::AsObstacle &obj);
    void CheckCbnaoBarrierCar(const active_safety::AsObstacle &obj);
    void CheckScpoBarrierCar(const active_safety::AsObstacle &obj);

    void CheckCPFAOTarget(const active_safety::AsObstacle &obj);
    void CheckCBNAOTarget(const active_safety::AsObstacle &obj);
    void CheckCSFAOTarget(const active_safety::AsObstacle &obj);
    void CheckScpoTarget(const active_safety::AsObstacle &obj);

    AsVseOut ego_;
    bool     k_at_test_scene_    = false;
    bool     k_cross_vlat_check_ = false;
    bool     k_cross_vlgt_check_ = false;
    uint32_t society_scene       = 0;
    // Ego at complex scene.
    int  ego_at_complex_scene_reset_time = 0;
    bool ego_at_complx_scene             = false;
    // Obj society evaluate.
    bool    society_evaluate_obj      = false;
    int     moving_tgt_cnt            = 0;
    int     truck_cnt                 = 0;
    int     mov_truck_cnt             = 0;
    int     invalid_truck_heading_cnt = 0;
    int     bike_cnt                  = 0;
    int     ped_cnt                   = 0;
    int     stat_twowhl_cnt           = 0;
    int     backforward_moving_car    = 0;
    int     ego_stright_inpath_car    = 0;
    int     backforward_moving_truck  = 0;
    int     tap_moving_forward_car    = 0;
    uint8_t scp_obj_id                = 0;
    uint8_t cpnco_obj_id              = 0;
    uint8_t child_obj_label_jump_cnt  = 0;

    // ego infomation
    float display_spd_kph_                  = 0;
    float forbrake_poselong_thd_            = 0;
    bool  within_validtime_after_ego_start_ = false;
    bool  disable_just_start                = false;
    bool  ego_during_turn_constant_spd_     = false;
    bool  ego_during_stright_constant_spd_  = false;
    bool  ego_cross_scpo_constant_spd_      = false;
    bool  ego_cross_constant_spd_           = false;
    int   validtime_after_ego_start_cnt     = 0;
    bool  ego_stationaty_                   = false;
    bool  pre_ego_stationaty_               = false;
    bool  ego_at_test_scene_                = false;
    bool  ego_at_turn_scene_                = false;

    bool ego_10kph_confirmeok = false;
    bool ego_20kph_confirmeok = false;
    bool ego_30kph_confirmeok = false;
    bool ego_40kph_confirmeok = false;
    bool ego_50kph_confirmeok = false;
    bool ego_60kph_confirmeok = false;

    int ego_10kph_confirm_cnt = 0;
    int ego_20kph_confirm_cnt = 0;
    int ego_30kph_confirm_cnt = 0;
    int ego_40kph_confirm_cnt = 0;
    int ego_50kph_confirm_cnt = 0;
    int ego_60kph_confirm_cnt = 0;

    int ego_not_10kph_delay_cnt = 0;
    int ego_not_20kph_delay_cnt = 0;
    int ego_not_30kph_delay_cnt = 0;
    int ego_not_40kph_delay_cnt = 0;
    int ego_not_50kph_delay_cnt = 0;
    int ego_not_60kph_delay_cnt = 0;

    //  cpta_l  confirm
    int  cpta_l_lowspd_cnt       = 0;
    int  cpta_l_midspd_cnt       = 0;
    bool pre_enter_cpta_l_midspd = false;
    bool pre_enter_cpta_l_lowspd = false;

    //  csta_rn  confirm
    int csta_rn_confirm_lowspd_cnt = 0;
    int csta_rn_confirm_midspd_cnt = 0;

    int  csta_rn_track_id         = 0;
    bool pre_enter_csta_rn_lowspd = false;
    bool pre_enter_csta_rn_midspd = false;

    bool cpta_l_require  = false;
    bool csta_rn_require = false;
    bool cpfao_require   = false;
    bool cbnao_require   = false;
    bool csfao_require   = false;
    bool scpo_require    = false;

    uint32_t cbnao_track_id  = 0;
    uint32_t cpfao_track_id  = 0;
    uint32_t csfao_track_id  = 0;
    uint32_t scpo_track_id   = 0;
    uint32_t cpta_l_track_id = 0;

    uint32_t csfao_fusion_id         = 0;
    uint32_t csta_rn_fusion_track_id = 0;
    uint32_t cpta_l_fusion_track_id  = 0;

    uint32_t simulation_check_cnt = 0;
    bool     simulation_check     = false;

    float cpta_l_nearest_posnlgt            = 100;
    float csta_rn_nearest_posnlgt           = 100;
    float cpfao_barrier_car_nearest_posnlgt = 100;
    float cbnao_barrier_car_nearest_posnlgt = 100;
    float csfao_barrier_car_nearest_posnlgt = 100;
    float scpo_barrier_car_nearest_posnlgt  = 100;

    // cross barrier car
    int  barrier_car_cpfao_count_        = 0;
    int  barrier_car_cpfao_num_          = 0;
    bool cpfao_barrier_car_condition_ok_ = false;

    int  barrier_car_cbnao_count_        = 0;
    int  barrier_car_cbnao_num_          = 0;
    bool cbnao_barrier_car_condition_ok_ = false;

    int  barrier_car_csfao_count_        = 0;
    int  barrier_car_csfao_num_          = 0;
    bool csfao_barrier_car_condition_ok_ = false;

    int  barrier_car_scpo_count_        = 0;
    int  barrier_car_scpo_num_          = 0;
    bool scpo_barrier_car_condition_ok_ = false;
};

} // namespace tap
} // namespace senseAD
