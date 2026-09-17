/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_ALGORITHM_OBSTACLE_OBSTACLE_H_
#define TAP_SDK_ALGORITHM_OBSTACLE_OBSTACLE_H_
#include "Eigen/Dense"
#include "algorithm/vse/vehicle_state_estimed.h"
#include "common/enum_type.h"
#include "interface/fusion_object.h"
#include "interface/lane_marker.h"
#include "math/geometry/geometry.h"
#include "math/historyinfo/historyinfo.h"
#include "obstacle_define.h"

#include <cmath>

namespace active_safety {
struct AsObstacle;
using AsObstacleList = std::array<std::shared_ptr<AsObstacle>, kMaxFusionObject>;
using math::Point2D;

struct ObsTimeComp {
    struct {
        Eigen::Vector3f delta_ego;
        float delta_time;
        uint64_t input_time;
        bool f_input_update;
    } fus_comp, gop_comp;
};

struct AsObstacle {
    AsObstacle();
    ~AsObstacle();

    void CorrectAttributes();
    void Clear();
    void UpdateObstacle(const FusionObs &obs, const AsVseOut &vse_out, const ObsTimeComp &obs_time_comp, const Eigen::Vector3f &delta_ego_last_cycle);

    void PositionUpdateForLatency(Eigen::Vector3f deltaEgo, float deltaTm, bool f_input_update);
    void ConvertVCSToCurvi(const AsVseOut &ego);
    void CorrectObstacleType();
    void CorrectObstacleCrvt();
    void CheckTurning();
    void CheckCrossDecel();

    uint8_t track_id = 0;
    int32_t fus_trkID = 0;
    int32_t vis_trkID = 0;

    float age = 0.0F;
    float lat_posn = 20.0F;
    float long_posn = 200.0F;
    float lat_vel = 0.0F;
    float long_vel = 0.0F;
    float lat_accel = 0.0F;
    float long_accel = 0.0F;
    float curvi_long_posn = 0.0F;
    float curvi_lat_posn = 0.0F;
    float curvi_long_vel = 0.0F;
    float curvi_lat_vel = 0.0F;
    float curvi_long_accel = 0.0F;
    float curvi_lat_accel = 0.0F;
    float curvi_long_vel_rel = 0.0F;
    float curvi_lat_vel_rel = 0.0F;
    float curvi_heading = 0.0F;
    float speed = 0.0F;
    float accel = 0.0F;
    float heading = 0.0F;
    float lat_accel_raw = 0.0F;
    float long_accel_raw = 0.0F;
    float heading_raw = 0.0F;
    float curvature = 0.0F;
    float length = 0.0F;
    float width = 0.0F;
    float height = 0.0F;

    bool f_is_vehicle = false;
    bool f_is_motor_vehicle = false;
    bool f_is_bicycle = false;
    bool f_turning = false;
    bool f_obs_straight_cross = false;
    bool f_cross_decel = false;

    ObsConfidence confidence = ObsConfidence::LOW_CONF;
    TrackStatus status = TrackStatus::INVALID;
    ObjectClass object_class = ObjectClass::UNDETERMINED;
    FusionSource fusion_source = FusionSource::SRR_ONLY;
    AsObstacleMotionPattern motion_pattern = AsObstacleMotionPattern::AS_OBS_MP_UNKNOWN;

    math::AsHistoryInfo<Point2D> fus_pos;
    math::AsHistoryInfo<Point2D> fus_vel;
    math::AsHistoryInfo<float> fus_heading;

    static AsObstacleCal obj_param;
};
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_OBSTACLE_OBSTACLE_H_
