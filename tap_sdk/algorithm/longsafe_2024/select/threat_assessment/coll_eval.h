/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include "algorithm/longsafe_2024/algo_interface/active_safety_vse.h"
#include "algorithm/longsafe_2024/scenario_analysis/society_scene.h"
#include "algorithm/obstacle/obstacle.h"
#include "ego_path.h"
#include "math/lookuptable/lookuptable.h"
#include "math/utils/util_math.h"

#include <cmath>

namespace senseAD {
namespace tap {
namespace math = active_safety::math;
using namespace active_safety::math;

struct AsObstacleMotionType {
    bool  stationary          = false;
    bool  moving_oncoming     = false;
    bool  para_veh_long_pred  = false;
    bool  para_veh_short_pred = false;
    bool  obs_is_vehicle      = false;
    bool  obs_is_motor_veh    = false;
    bool  curved_motion       = false;
    bool  side_closest        = false;
    float abs_heading         = 0.0;
};
struct BoundingBox {
    float length_side_lgt;
    float length_side_lat;
    float sin_rotation;
    float cos_rotation;

    BoundingBox() : length_side_lgt(0.0f), length_side_lat(0.0f), sin_rotation(0.0f), cos_rotation(0.0f) {}
};
struct MotionData {
    float v_rel;
    float v_rel_host_sta;
    float v_rel_object_sta;
    float a_rel;
    float a_rel_host_sta;
    float a_rel_object_sta;

    MotionData() : v_rel(0.0f), v_rel_host_sta(0.0f), v_rel_object_sta(0.0f), a_rel(0.0f), a_rel_host_sta(0.0f), a_rel_object_sta(0.0f) {}
};

struct EdgeDistanceData {
    float close_edge_dis;
    float middle_edge_dis;
    float far_edge_dis;

    EdgeDistanceData() : close_edge_dis(0.0f), middle_edge_dis(0.0f), far_edge_dis(0.0f) {}
};

struct StoppingData {
    float obj_delta_pos  = 0.0f;
    float obj_stop_time  = 0.0f;
    float host_delta_pos = 0.0f;
    float host_stop_time = 0.0f;
};

struct TTIInputData {
    bool       is_front_closest;
    MotionData md_front_closest;
    MotionData md_rear_closest;
    float      edge_dis_front;
    float      edge_dis_rear;
    float      ego_stop_dis;
    float      veh_stop_dis;

    TTIInputData()
        : is_front_closest(false), md_front_closest(), md_rear_closest(), edge_dis_front(0.0f), edge_dis_rear(0.0f), ego_stop_dis(0.0f),
          veh_stop_dis(0.0f) {}
};

struct TTIDataSel {
    float normal_edge_dis;
    float normal_v_rel;
    float normal_a_rel;
    float alter_edge_dis;
    float alter_v_rel;
    float alter_a_rel;

    TTIDataSel() : normal_edge_dis(0.0f), normal_v_rel(0.0f), normal_a_rel(0.0f), alter_edge_dis(0.0f), alter_v_rel(0.0f), alter_a_rel(0.0f) {}
};

struct TTIMotionData {
    TTIDataSel tti_moving_para;
    TTIDataSel tti_hoststop_para;
    TTIDataSel tti_objstop_para;

    TTIMotionData() : tti_moving_para(), tti_hoststop_para(), tti_objstop_para() {}
};

struct TTIData {
    bool  moving_sol_exit;
    float moving_tti;
    bool  ego_stop_sol_exit;
    float ego_stop_tti;
    bool  veh_stop_sol_exit;
    float veh_stop_tti;

    TTIData()
        : moving_sol_exit(false), moving_tti(0.0f), ego_stop_sol_exit(false), ego_stop_tti(0.0f), veh_stop_sol_exit(false), veh_stop_tti(0.0f) {}
};

#define MAX_TTC_THD 100.0f

class CollisionEvaluator {
  public:
    CollisionEvaluator();
    ~CollisionEvaluator() noexcept;

    void                 Clear();
    static float         SolveTTISolution(float VRel, float ARel, float Posn);
    void                 ProcessCollisionEvaluator(const active_safety::AsObstacle &obj, const AsVseOut &vse_out, const AsEgoPath &curv_path,
                                                   const AsSocietyScene &society_scene);
    AsObstacleMotionType motion_type;
    BoundingBox          bounding_box;

    float ttm     = 100.0;
    float ttr     = 100.0;
    float xolc    = 20.0f;
    float lat_est = 20.0f;

  private:
    void CalMotionType(const AsVseOut &vse_out, const active_safety::AsObstacle &obj);
    void CalcMotionClass(const active_safety::AsObstacle &obj, const AsVseOut &vse_out);
    void CalBoundingBox(const AsVseOut &vse_out, const active_safety::AsObstacle &obj);
    void CalTTRAndTTM(const AsVseOut &vse_out, const active_safety::AsObstacle &obj);
    void CalTTRAndTTMForTurnScene(const AsEgoPath &curv_path, const AsVseOut &vse_out, const active_safety::AsObstacle &obj,
                                  const AsSocietyScene &society_scene);
    void CalLatEstimedInfo(const active_safety::AsObstacle &obj, const AsVseOut &vse_out);
    void CheckVehicle(const active_safety::AsObstacle &obj);
    void CheckMotorVehicle(const active_safety::AsObstacle &obj);
    void CheckAbsHeading(const active_safety::AsObstacle &obj);
    void CheckStationary(const active_safety::AsObstacle &obj);
    void CheckOncoming(const active_safety::AsObstacle &obj);
    void CheckParallellVehicleLongPred(const active_safety::AsObstacle &obj);
    void CheckParallellVehicleShortPred(const active_safety::AsObstacle &obj);
    void CheckCurvedMotion(const active_safety::AsObstacle &obj);
    void CheckSideIsClosest(const AsVseOut &vse_out, const active_safety::AsObstacle &obj);

    float CalLenLat(const active_safety::AsObstacle &obj);
    float CalLenLgt(const AsVseOut &vse_out, const active_safety::AsObstacle &obj);
    float CalSinRotation(const active_safety::AsObstacle &obj);
    float CalCosRotation(const active_safety::AsObstacle &obj);

    void         CalMotionData(const AsVseOut &vse_out, const active_safety::AsObstacle &obj);
    void         CalEdgeDistanceData(const AsVseOut &vse_out, const active_safety::AsObstacle &obj);
    StoppingData CalcStopDataForTTI(const active_safety::AsObstacle &obj, const AsVseOut &vse_out);
    bool         CleckIsFrontClosest(const active_safety::AsObstacle &obj);

    void CalTTI(const TTIInputData &input_data, TTIData &tti_data);
    bool SelectTTI(const TTIData &tti_data, float ego_stop_time, float veh_stop_time, float &tti);
    bool CheckTTISolution(float edge_dis, float v_rel, float a_rel);
    bool CalTTIResult(TTIDataSel tti_para, float delta_pos, float &tti);
    bool SelectMotionData(bool host_front_is_closest, MotionData md_front, MotionData md_rear, float ed_front, float ed_rear, TTIMotionData &output);

    MotionData         md_front_closest;
    MotionData         md_rear_closest;
    EdgeDistanceData   ed_front;
    EdgeDistanceData   ed_rear;
    AsObstacleSideNear side_near = AsObstacleSideNear::AS_OBS_SD_UNKNOWN;

    float seprate_axle_ttc = 100.0f;
    float seprate_axle_ttm = 100.0f;
    float long_ttc         = 100.0f;
    float long_ttm         = 100.0f;
};
} // namespace tap
} // namespace senseAD
