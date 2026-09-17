/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#include "ego_path.h"

#include <array>
namespace senseAD {
namespace tap {

EgoMotionStateAtTime AsEgoPath::GetHostStateAtTime(float time) {
    if (time <= 0.005F) {
        return EgoMotionStateAtTime{};
    }
    EgoMotionStateAtTime host_state_at_time;
    std::size_t          idx = SelectSegment(time);
    float                tau =
        math::Clamp(math::SafeDivide(time - path_estimn[idx].t0, path_estimn[idx].t1 - path_estimn[idx].t0), 0.0F, 1.0F);

    float squard_tau            = tau * tau;
    float third_tau             = squard_tau * tau;
    host_state_at_time.long_pos = EstimedPosn(path_estimn[idx].ctrl_point_long_p0, path_estimn[idx].ctrl_point_long_p1,
                                              path_estimn[idx].ctrl_point_long_p2, path_estimn[idx].ctrl_point_long_p3, tau, squard_tau, third_tau);
    host_state_at_time.lat_pos  = EstimedPosn(path_estimn[idx].ctrl_point_lat_p0, path_estimn[idx].ctrl_point_lat_p1,
                                             path_estimn[idx].ctrl_point_lat_p2, path_estimn[idx].ctrl_point_lat_p3, tau, squard_tau, third_tau);
    float dx  = EstimedPosnDerivative(path_estimn[idx].ctrl_point_long_p0, path_estimn[idx].ctrl_point_long_p1, path_estimn[idx].ctrl_point_long_p2,
                                     path_estimn[idx].ctrl_point_long_p3, tau, squard_tau);
    float dy  = EstimedPosnDerivative(path_estimn[idx].ctrl_point_lat_p0, path_estimn[idx].ctrl_point_lat_p1, path_estimn[idx].ctrl_point_lat_p2,
                                     path_estimn[idx].ctrl_point_lat_p3, tau, squard_tau);
    float ddx = EstimedVelDerivative(path_estimn[idx].ctrl_point_long_p0, path_estimn[idx].ctrl_point_long_p1, path_estimn[idx].ctrl_point_long_p2,
                                     path_estimn[idx].ctrl_point_long_p3, tau);
    float ddy = EstimedVelDerivative(path_estimn[idx].ctrl_point_lat_p0, path_estimn[idx].ctrl_point_lat_p1, path_estimn[idx].ctrl_point_lat_p2,
                                     path_estimn[idx].ctrl_point_lat_p3, tau);
    host_state_at_time.pred_curv = math::SafeDivide((dx * ddy - ddx * dy), powf((dx * dx + dy * dy), 1.50F));

    bool SpeedValid = (dx * dx + dy * dy > spd_thres_in_evaluation * spd_thres_in_evaluation);
    if (SpeedValid) {
        host_state_at_time.heading_angle = std::atan2(dy, dx);
        host_state_at_time.lat_vel       = dy;
        host_state_at_time.long_vel      = dx;
    } else {
        bool        spd_valid[4] = {0};
        float       dx_2[4], dy_2[4];
        std::size_t valid_segment_index = 0;
        for (std::size_t i = 0; i < 4; i++) {
            dx_2[i]      = -3.0F * path_estimn[i].ctrl_point_long_p0 + 3.0F * path_estimn[i].ctrl_point_long_p1;
            dy_2[i]      = -3.0F * path_estimn[i].ctrl_point_lat_p0 + 3.0F * path_estimn[i].ctrl_point_lat_p1;
            spd_valid[i] = (dx_2[i] * dx_2[i] + dy_2[i] * dy_2[i] > spd_thres_in_evaluation * spd_thres_in_evaluation);
        }
        for (std::size_t i = 1; i <= 4; i++) {
            if (spd_valid[i - 1]  &&  (i <= idx + 1)) {
                valid_segment_index = i;
            }
        }
        if (valid_segment_index > 0) {
            host_state_at_time.heading_angle = std::atan2(dy_2[valid_segment_index - 1], dx_2[valid_segment_index - 1]);
            host_state_at_time.lat_vel       = dy_2[valid_segment_index - 1];
            host_state_at_time.long_vel      = dx_2[valid_segment_index - 1];
        } else {
            host_state_at_time.heading_angle = 0.0F;
            host_state_at_time.lat_vel       = 0.0F;
            host_state_at_time.long_vel      = 0.0F;
        }
    }

    return host_state_at_time;
}

float AsEgoPath::GetEndTimeOfPath() const {
    return 4.0F;
}

float AsEgoPath::EstimedPosn(float p0, float p1, float p2, float p3, float tau, float squrdTau, float thirdTau) const {
    return ((3.0F * (p1 - p2) - p0 + p3) * thirdTau + 3 * (p0 - 2 * p1 + p2) * squrdTau + 3 * (p1 - p0) * tau + p0);
}
float AsEgoPath::EstimedPosnDerivative(float p0, float p1, float p2, float p3, float tau, float squrdTau) const {
    // return ((9.0 * p1 - 3.0 * p0 - 9.0 * p2 + 3.0 * p3) * squrdTau +
    //         (6.0 * p0 - 12.0 * p1 + 6.0 * p2) * tau - 3.0 * p0 + 3.0 * p1);
    const float common_term = p0 - 2.0F * p1 + p2;
    return 3.0F * (3.0F * p1 - p0 - 3.0F * p2 + p3) * squrdTau + 6.0F * common_term * tau + 3.0F * (p1 - p0);
}
float AsEgoPath::EstimedVelDerivative(float p0, float p1, float p2, float p3, float tau) const {
    // float d_ret = 0.0F;
    // d_ret = (18.0F * p1 - 6.0F * p0 - 18.0F * p2 + 6.0F * p3) * tau + 6.0F *
    // p0
    // -
    //         12.0F * p1 + 6.0F * p2;
    // return d_ret;
    const float common_term = 3.0F * p1 - p0 - 3.0F * p2 + p3;
    return 6.0F * common_term * tau + 6.0F * (p0 - 2.0F * p1 + p2);
}
EgoMotionStateAtTime AsEgoPath::GetHostState(float time) const {
    EgoMotionStateAtTime ms;
    std::size_t          idx = Time2Num(time);
    if (idx < SIZEOFHOST) {
        ms = hostPosInfo[idx].host_state;
    } else {
        ms = hostPosInfo.back().host_state;
    }
    return ms;
}

Box2D AsEgoPath::GetHostBoudingBox(float time) const {
    std::size_t idx = Time2Num(time);
    if (idx < SIZEOFHOST) {
        return hostPosInfo[idx].host_box;
    } else {
        return hostPosInfo.back().host_box;
    }
}
std::size_t AsEgoPath::Time2Num(float time) const {
    return static_cast<std::size_t>(static_cast<int32_t>(std::floor(std::round(time * 1000))) / int32_t(20));
}

void AsEgoPath::UpdatePath(float vlgt, float algt, float c0, float c1, float width, float length, float distRearToFnt) {
    VehicleMotionStateT0 t0;
    VehicleMotionStateT1 t1;
    const float          start_time[4] = {0.0, 1.0, 2.0, 3.0};
    const float          end_time[4]   = {1.0, 2.0, 3.0, 4.0};
    for (std::size_t idx = 1; idx <= 4; idx++) {
        // printf("Idx:%d\n", (int)idx);
        if (idx == 1) {
            t0.position_long  = 0.0F;
            t0.vel_long       = vlgt;
            t0.accel          = algt;
            t0.accel_long     = algt;
            t0.position_lat   = 0.0F;
            t0.vel_lat        = 0.0F;
            t0.accel_lat      = vlgt * vlgt * c0;
            t0.speed          = vlgt;
            t0.curvature      = c0;
            t0.curvature_rate = c1;
            t0.heading_angle  = 0.0F;
        } else {
            t0.position_long = t1.position_long;
            t0.vel_long      = t1.vel_long;
            t0.accel         = t1.accel;
            t0.accel_long    = t1.accel_long;
            t0.position_lat  = t1.position_lat;
            t0.vel_lat       = t1.vel_lat;
            t0.accel_lat     = t1.accel_lat;
            t0.speed         = t1.speed;
            t0.curvature     = t1.curvature;
            if (idx == 2) {
                t0.curvature_rate = -c1;
            } else {
                t0.curvature_rate = 0.0F;
            }
            t0.heading_angle = t1.heading_angle;
        }

        bool  stops_within_segment       = true;
        float longitudinal_stopping_dist = 0.0F, lateral_stopping_dist = 0.0F;
        if (std::abs(t0.speed) >= spd_thres_in_evaluation) {
            float stop_time            = math::Clamp(math::SafeDivide(t0.speed, -t0.accel), 0.0F, 4.0F);
            stops_within_segment       = ((stop_time < 1.0F)  &&  (stop_time > 0.0F));
            longitudinal_stopping_dist = t0.vel_long * stop_time + 0.5F * t0.accel_long * stop_time * stop_time;
            lateral_stopping_dist      = t0.vel_lat * stop_time + 0.5F * t0.accel_lat * stop_time * stop_time;
        }
        path_estimn[idx - 1].ctrl_point_long_p0 = t0.position_long;
        path_estimn[idx - 1].ctrl_point_lat_p0  = t0.position_lat;
        // printf("stops_within_segment:%d\n", stops_within_segment);
        if (stops_within_segment) {
            path_estimn[idx - 1].ctrl_point_long_p1 = longitudinal_stopping_dist + t0.position_long;
            path_estimn[idx - 1].ctrl_point_long_p2 = longitudinal_stopping_dist + t0.position_long;
            path_estimn[idx - 1].ctrl_point_lat_p1  = lateral_stopping_dist + t0.position_lat;
            path_estimn[idx - 1].ctrl_point_lat_p2  = lateral_stopping_dist + t0.position_lat;
        } else {
            path_estimn[idx - 1].ctrl_point_long_p1 = t0.position_long + t0.vel_long * 0.33333F;
            path_estimn[idx - 1].ctrl_point_long_p2 =
                2.0F * (t0.position_long + t0.vel_long * 0.33333F) - t0.position_long + 0.166667F * t0.accel_long;
            path_estimn[idx - 1].ctrl_point_lat_p1 = t0.position_lat + t0.vel_lat * 0.33333F;
            path_estimn[idx - 1].ctrl_point_lat_p2 = 2.0F * (t0.position_lat + t0.vel_lat * 0.33333F) - t0.position_lat + 0.166667F * t0.accel_lat;
        }
        const float detectableCuvature = 0.00001F;
        if ((std::abs(t0.curvature) > detectableCuvature)  &&  (std::abs(t0.curvature + t0.curvature_rate) > detectableCuvature)) {
            // Distance at time 1s, which equals the arc length.
            // 0.5*a0*t^2+v0*t, fot t=1
            float distance = 0.5F * t0.accel + t0.speed;
            // Curvature radius.
            float r1          = math::SafeDivide(1.0F, t0.curvature);
            float r2          = math::SafeDivide(1.0F, t0.curvature + t0.curvature_rate);
            float angleOfArc1 = math::SafeDivide(distance, r1);
            float angleOfArc2 = math::SafeDivide(distance, r2);
            // Position in coordinate system rotated with heading h0.
            // Position if radius = 1/c0.
            float xrot1 = r1 * std::sin(angleOfArc1);
            float yrot1 = -r1 * std::cos(angleOfArc1) + r1;
            // Position if radius = 1/(c0+c1).
            float xrot2 = r2 * std::sin(angleOfArc2);
            float yrot2 = -r2 * std::cos(angleOfArc2) + r2;
            float x1    = xrot1 * std::cos(t0.heading_angle) - yrot1 * std::sin(t0.heading_angle);
            float y1    = xrot1 * std::sin(t0.heading_angle) + yrot1 * std::cos(t0.heading_angle);
            float x2    = xrot2 * std::cos(t0.heading_angle) - yrot2 * std::sin(t0.heading_angle);
            float y2    = xrot2 * std::sin(t0.heading_angle) + yrot2 * std::cos(t0.heading_angle);
            // Longitudinal and lateral position at time 1s.
            path_estimn[idx - 1].ctrl_point_long_p3 = t0.position_long + 0.7F * x1 + 0.3F * x2;
            path_estimn[idx - 1].ctrl_point_lat_p3  = t0.position_lat + 0.7F * y1 + 0.3F * y2;
            //     printf("c0:%f  c1:%f\n",t0.curvature,t0.curvature_rate);
            // printf("r1:%f  r2:%f angleOfArc1:%f angleOfArc2:%f\n", r1, r2,
            //        angleOfArc1, angleOfArc2);
            // printf("headingAngle:%f\n", t0.heading_angle);
            // printf("longpos:%f  x1:%f  x2:%f\n", t0.position_long, x1, x2);
            // printf("latpos:%f  y1:%f  y2:%f\n", t0.position_lat, y1, y2);

        } else {
            path_estimn[idx - 1].ctrl_point_long_p3 = t0.position_long + (0.5F * t0.accel + t0.speed) * std::cos(t0.heading_angle);
            path_estimn[idx - 1].ctrl_point_lat_p3  = t0.position_lat + (0.5F * t0.accel + t0.speed) * std::sin(t0.heading_angle);
        }
        // If vehicle stops, use the stopping distance for calculating the
        // predicted position.
        if (stops_within_segment) {
            path_estimn[idx - 1].ctrl_point_long_p3 = t0.position_long + longitudinal_stopping_dist;
            path_estimn[idx - 1].ctrl_point_lat_p3  = t0.position_lat + lateral_stopping_dist;
        }
        path_estimn[idx - 1].t0 = start_time[idx - 1];
        path_estimn[idx - 1].t1 = end_time[idx - 1];

        // Compute Vehicle State at t1
        t1.position_long = path_estimn[idx - 1].ctrl_point_long_p3;
        t1.position_lat  = path_estimn[idx - 1].ctrl_point_lat_p3;
        // v1 = v0 + a * 1s.
        t1.speed = math::Clamp(t0.speed + t0.accel, 0.0F, 50.0F);
        if (stops_within_segment) {
            t1.accel = 0.0F;
        } else {
            t1.accel = t0.accel;
        }
        float lat_vel  = 3.0F * path_estimn[idx - 1].ctrl_point_lat_p3 - path_estimn[idx - 1].ctrl_point_lat_p2 * 3.0F;
        float long_vel = 3.0F * path_estimn[idx - 1].ctrl_point_long_p3 - path_estimn[idx - 1].ctrl_point_long_p2 * 3.0F;
        if (std::abs(std::atan2(lat_vel, long_vel)) > 0.0F) {
            t1.heading_angle = std::atan2(lat_vel, long_vel);
        } else {
            t1.heading_angle = t0.heading_angle;
        }
        // c = c0 + c1 * 1s.
        t1.curvature              = math::Clamp(t0.curvature + t0.curvature_rate, -0.1F, 0.1F);
        float accel_perpendicular = t1.curvature * t1.speed * t1.speed;
        // Convert accelaration to cartesian coordinate system.
        t1.accel_long = -accel_perpendicular * std::sin(t1.heading_angle) + t1.accel * std::cos(t1.heading_angle);
        t1.accel_lat  = accel_perpendicular * std::cos(t1.heading_angle) + t1.accel * std::sin(t1.heading_angle);
        // Convert speed to cartesian coordinate system.
        t1.vel_long = t1.speed * std::cos(t1.heading_angle);
        t1.vel_lat  = t1.speed * std::sin(t1.heading_angle);
    }
    std::size_t sz = 0;
    for (float tm = 0.000F; tm <= 4.000F; tm = tm + 0.02F) {
        //自车轨迹此时位置
        if (sz >= SIZEOFHOST) {
            break;
        }
        hostPosInfo[sz].host_state = GetHostStateAtTime(tm);
        //预测自车Box
        float cosHeadingAngle = std::cos(hostPosInfo[sz].host_state.heading_angle);
        float sinHeadingAngle = std::sin(hostPosInfo[sz].host_state.heading_angle);
        float halfHostWidth   = 0.5F * width;

        hostPosInfo[sz].host_box.left_top.x = hostPosInfo[sz].host_state.long_pos + distRearToFnt * cosHeadingAngle + halfHostWidth * sinHeadingAngle;
        hostPosInfo[sz].host_box.left_top.y = hostPosInfo[sz].host_state.lat_pos + distRearToFnt * sinHeadingAngle + halfHostWidth * cosHeadingAngle;
        hostPosInfo[sz].host_box.right_top.x =
            hostPosInfo[sz].host_state.long_pos + distRearToFnt * cosHeadingAngle - halfHostWidth * sinHeadingAngle;
        hostPosInfo[sz].host_box.right_top.y = hostPosInfo[sz].host_state.lat_pos + distRearToFnt * sinHeadingAngle - halfHostWidth * cosHeadingAngle;
        hostPosInfo[sz].host_box.left_bottom.x  = hostPosInfo[sz].host_box.left_top.x - length * cosHeadingAngle;
        hostPosInfo[sz].host_box.left_bottom.y  = hostPosInfo[sz].host_box.left_top.y - length * sinHeadingAngle;
        hostPosInfo[sz].host_box.right_bottom.x = hostPosInfo[sz].host_box.right_top.x - length * cosHeadingAngle;
        hostPosInfo[sz].host_box.right_bottom.y = hostPosInfo[sz].host_box.right_top.y - length * sinHeadingAngle;
        sz++;
    }
}

std::size_t AsEgoPath::SelectSegment(float time) {
    if ((time <= 0.0F)  ||  (time > 4.0F)) {
        return std::size_t(3);
    }
    for (std::size_t idx = 0; idx < 4; idx++) {
        if ((time > path_estimn[idx].t0)  &&  (time <= path_estimn[idx].t1)) {
            return idx;
        }
    }
    return std::size_t(3);
}

} // namespace tap
} // namespace senseAD