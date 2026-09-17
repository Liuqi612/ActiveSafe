#include "elk_threat_assessment.h"

#include <algorithm>
#include <cmath>

namespace active_safety {
namespace elk {

namespace {
bool updateOcMotionGuardDebug(const AsOnComingObject &target,
                              const ElkCal &elk_cals,
                              ElkOcMotionGuardDebug &debug)
{
    debug.long_vel = target.vcs_long_vel;
    debug.min_oncoming_speed = elk_cals.k_ELK_OC_MinOncomingSpeed;
    debug.heading_abs = std::abs(target.curv_heading);
    debug.heading_threshold = elk_cals.k_oc_trk_heading;
    debug.f_oncoming = target.f_oncoming;
    debug.movement = target.movement;
    debug.speed_valid = target.vcs_long_vel <= -elk_cals.k_ELK_OC_MinOncomingSpeed;
    debug.f_oncoming_valid = target.f_oncoming != 0U;
    debug.movement_valid = target.movement == 4U;
    debug.heading_valid = debug.heading_abs >= elk_cals.k_oc_trk_heading;
    debug.motion_valid = debug.speed_valid && debug.f_oncoming_valid && debug.movement_valid && debug.heading_valid;
    return debug.motion_valid;
}
}

    ElkThreatAssessment::ElkThreatAssessment() {}

    void ElkThreatAssessment::Update(const AsVseOut &vse_out,
                                     const LaneCenterParameters &lane_info,
                                     const VehicleConfig &veh_config,
                                     const GlobalConfig &config,
                                     const AsOnComingOut &oncom_out,
                                     const AsOverTakingOut &overtake_out)
    {
        threat_debug_snapshot_ = ElkThreatDebugSnapshot();
        calEgoSL(vse_out, lane_info, veh_config);

        calOncomingLeftSL(oncom_out.oncom_target_1, lane_info, veh_config);

        calOncomingRightSL(oncom_out.oncom_target_2, lane_info, veh_config);

        calOvertakingRearLeftSL(overtake_out.overtake_target_rear_left, lane_info, veh_config);

        calOvertakingRearRightSL(overtake_out.overtake_target_rear_right, lane_info, veh_config);

        calculateTTC(overtake_out);

        oncomingSLJudge(vse_out, oncom_out, config);

        overtakingSLJudge(vse_out, overtake_out, config);
    }

    void ElkThreatAssessment::calEgoSL(const AsVseOut &vse_out, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config)
    {
        float egoRear2Front, x2, x3, h_sin, h_cos; 
        egoRear2Front = veh_config.k_dist_to_rear_axle; // 自车后轴中心到前保距离
        x2 = egoRear2Front * egoRear2Front;
        x3 = x2 * egoRear2Front;
        h_sin = std::sin(lane_info.heading);
        h_cos = std::cos(lane_info.heading);
        ta_sl_info_.ego.x = 0.0F;
        ta_sl_info_.ego.y = lane_info.c0;
        ta_sl_info_.ego.s = 0.0F;
        ta_sl_info_.ego.l = ta_sl_info_.ego.y * h_cos;
        ta_sl_info_.ego.x_front_head = egoRear2Front;
        ta_sl_info_.ego.x_front_left_corner = egoRear2Front;
        ta_sl_info_.ego.x_front_right_corner = egoRear2Front;
        ta_sl_info_.ego.y_front_head = lane_info.c0 + lane_info.c1 * egoRear2Front + lane_info.c2 * x2 + lane_info.c3 * x3; // 自车前保中心距离道路中心线横向距离

        ta_sl_info_.ego.y_front_left_corner = ta_sl_info_.ego.y_front_head + 0.5F * veh_config.k_host_width; // 自车左前角点距离道路中心线横向距离
        ta_sl_info_.ego.l_front_left_corner = ta_sl_info_.ego.y_front_left_corner * h_cos; // 自车左前角点距离道路中心线横向投影距离（负值表示在道路中心线右侧）

        ta_sl_info_.ego.y_front_right_corner = ta_sl_info_.ego.y_front_head - 0.5 * veh_config.k_host_width; // 自车右前角点距离道路中心线横向距离
        ta_sl_info_.ego.l_front_right_corner = ta_sl_info_.ego.y_front_right_corner * h_cos; // 自车右前角点距离道路中心线横向投影距离（正值表示在道路中心线左侧）

        ta_sl_info_.ego.vs = vse_out.speed; // 自车s方向运动属性暂时用笛卡尔坐标系直接代替
        ta_sl_info_.ego.as = vse_out.long_accel;

        ta_sl_info_.ego.vl = vse_out.speed * h_sin; // 自车相对车道中心线横向偏离速度；（负值表示向右偏离）
        ta_sl_info_.ego.al = vse_out.lat_accel * h_cos + vse_out.long_accel * h_sin;
    }

    void ElkThreatAssessment::calOncomingLeftSL(const AsOnComingObject &as_oc, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config)
    {
        float obj_x, obj_y, lane_objx_y, lane_objx_heading, obj_x2, obj_x3;
        float lane_objx_heading_sin, lane_objx_heading_cos;
        float lFrmObjPnt2Rd;
        // 处理左侧车道oncoming目标
        obj_x = as_oc.vcs_long_posn + 0.5 * as_oc.length * std::cos(-as_oc.curv_heading); // 前保中心x坐标，后保中心转至前保中心
        obj_y = as_oc.vcs_lat_posn + 0.5F * as_oc.length * std::sin(-as_oc.curv_heading); // 前保中心y坐标
        ta_sl_info_.oncoming_front_left.x = obj_x;
        ta_sl_info_.oncoming_front_left.y = obj_y;

        obj_x2 = obj_x * obj_x;
        obj_x3 = obj_x2 * obj_x;
        lane_objx_y = lane_info.c0 + lane_info.c1 * obj_x + lane_info.c2 * obj_x2 + lane_info.c3 * obj_x3; // 道路中心线在目标前保中心x处的y坐标
        lFrmObjPnt2Rd = obj_y - lane_objx_y; // 目标前保中心相对于道路中心线的横向距离（负值表示在中心线左侧）
        lFrmObjPnt2Rd = lFrmObjPnt2Rd + 0.5 * as_oc.width; // 目标左前角点相对于道路中心线的横向距离
        
        lane_objx_heading = std::atan2(lane_info.c1 + 2 * lane_info.c2 * obj_x + 3 * lane_info.c3 * obj_x2, 1); // 目标前保中心处相对于道路中心线的heading
        lane_objx_heading_sin = std::sin(lane_objx_heading);
        lane_objx_heading_cos = std::cos(lane_objx_heading);

        // ta_sl_info_.oncoming_front_left.l = (lFrmObjPnt2Rd + lFrmEgoPnt2Rd) * lane_objx_heading_cos;
        ta_sl_info_.oncoming_front_left.l = lFrmObjPnt2Rd * lane_objx_heading_cos + ta_sl_info_.ego.l_front_left_corner; // 在道路模型下目标左前角点相对于自车左前角点距离（负值表示障碍物在自车左侧）
        ta_sl_info_.oncoming_front_left.vl = as_oc.vcs_long_vel * lane_objx_heading_sin - as_oc.vcs_lat_vel * lane_objx_heading_cos;
        ta_sl_info_.oncoming_front_left.al = as_oc.vcs_long_accel * lane_objx_heading_sin - as_oc.vcs_lat_accel * lane_objx_heading_cos;
        
        ta_sl_info_.oncoming_front_left.s = calOncomingToEgoS(obj_x, lane_info, veh_config); // 目标前保与自车前保
        ta_sl_info_.oncoming_front_left.vs = as_oc.vcs_long_vel * lane_objx_heading_cos + as_oc.vcs_lat_vel * lane_objx_heading_sin;
        ta_sl_info_.oncoming_front_left.as = as_oc.vcs_long_accel * lane_objx_heading_cos + as_oc.vcs_lat_accel * lane_objx_heading_sin;
    }

    void ElkThreatAssessment::calOncomingRightSL(const AsOnComingObject &as_oc, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config)
    {
        float obj_x, obj_y, lane_objx_y, lane_objx_heading, obj_x2, obj_x3;
        float lane_objx_heading_sin, lane_objx_heading_cos;
        float lFrmObjPnt2Rd;
        // 处理右侧车道oncoming目标
        obj_x = as_oc.vcs_long_posn + 0.5 * as_oc.length * std::cos(-as_oc.curv_heading); // 前保中心x坐标
        obj_y = as_oc.vcs_lat_posn + 0.5 * as_oc.length * std::sin(-as_oc.curv_heading); // 前保中心y坐标（正值表示在自车右侧）
        ta_sl_info_.oncoming_front_right.x = obj_x;
        ta_sl_info_.oncoming_front_right.y = obj_y;

        obj_x2 = obj_x * obj_x;
        obj_x3 = obj_x2 * obj_x;
        lane_objx_y = lane_info.c0 + lane_info.c1 * obj_x + lane_info.c2 * obj_x2 + lane_info.c3 * obj_x3; // 道路中心线在目标前保中心x处的y坐标（正值表示在道路中心线左侧）
        lFrmObjPnt2Rd = obj_y - lane_objx_y; // 目标前保中心相对于道路中心线的横向距离（正值表示在道路中心线右侧）
        lFrmObjPnt2Rd = lFrmObjPnt2Rd - 0.5 * as_oc.width; // 目标右前角点相对于道路中心线的横向距离

        lane_objx_heading = std::atan2(lane_info.c1 + 2 * lane_info.c2 * obj_x + 3 * lane_info.c3 * obj_x2, 1); // 目标前保中心处相对于道路中心线的heading
        lane_objx_heading_sin = std::sin(lane_objx_heading);
        lane_objx_heading_cos = std::cos(lane_objx_heading);

        // ta_sl_info_.oncoming_front_right.l = (lFrmObjPnt2Rd - lFrmEgoPnt2Rd) * lane_objx_heading_cos;
        ta_sl_info_.oncoming_front_right.l = lFrmObjPnt2Rd * lane_objx_heading_cos + ta_sl_info_.ego.l_front_right_corner; // 在道路模型下目标右前角点相对于自车右前角点距离;（正值表示障碍物在自车右侧）
        ta_sl_info_.oncoming_front_right.vl = as_oc.vcs_long_vel * lane_objx_heading_sin - as_oc.vcs_lat_vel * lane_objx_heading_cos;
        ta_sl_info_.oncoming_front_right.al = as_oc.vcs_long_accel * lane_objx_heading_sin - as_oc.vcs_lat_accel * lane_objx_heading_cos;
        
        ta_sl_info_.oncoming_front_right.s = calOncomingToEgoS(obj_x, lane_info, veh_config);
        ta_sl_info_.oncoming_front_right.vs = as_oc.vcs_long_vel * lane_objx_heading_cos + as_oc.vcs_lat_vel * lane_objx_heading_sin;
        ta_sl_info_.oncoming_front_right.as = as_oc.vcs_long_accel * lane_objx_heading_cos + as_oc.vcs_lat_accel * lane_objx_heading_sin;
    }

    float ElkThreatAssessment::calOncomingToEgoS(const float x, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config)
    {
        float xFromEgoToObj, oc_s, x0, y0, x1, y1, x0_2, x0_3;
        float k_DiscreteInterval = elk_cals_.k_ELK_DiscreteInterval;
        size_t disPntNum = 0;
        xFromEgoToObj = x - veh_config.k_dist_to_rear_axle; // 目标前保中心与自车前保中心x方向间距
        if (xFromEgoToObj <= 0) {
            oc_s = 100.0F;
        } else {
            disPntNum = std::floor(xFromEgoToObj / k_DiscreteInterval);
            if (disPntNum <= 1) {
                oc_s = xFromEgoToObj;
            } else {
                oc_s = 0.0F;
                for (size_t i = 1; i < disPntNum; i++) {
                    x0 = veh_config.k_dist_to_rear_axle + static_cast<float>(i - 1) * k_DiscreteInterval;
                    x0_2 = x0 * x0;
                    x0_3 = x0_2 * x0;
                    y0 = lane_info.c0 + lane_info.c1 * x0 + lane_info.c2 * x0_2 + lane_info.c3 * x0_3;

                    x1 = veh_config.k_dist_to_rear_axle + static_cast<float>(i) * k_DiscreteInterval;
                    x0_2 = x1 * x1;
                    x0_3 = x0_2 * x1;
                    y1 = lane_info.c0 + lane_info.c1 * x1 + lane_info.c2 * x0_2 + lane_info.c3 * x0_3;

                    oc_s = oc_s + std::sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
                }
            }
        }
        return oc_s;
    }

    void ElkThreatAssessment::calOvertakingRearLeftSL(const AsOverTakingObject &as_ot, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config)
    {
        float obj_x, obj_y, lane_objx_y, lane_objx_heading, obj_x2, obj_x3;
        float lane_objx_heading_sin, lane_objx_heading_cos;
        float lFrmObjPnt2Rd;
        // 处理左侧车道后向overtaking目标
        obj_x = as_ot.vcs_long_posn + 0.5 * as_ot.length * std::cos(-as_ot.vcs_heading); // 前保中心x坐标
        obj_y = as_ot.vcs_lat_posn + 0.5F * as_ot.length * std::sin(-as_ot.vcs_heading); // 前保中心y坐标(负值表示在自车左侧)
        ta_sl_info_.overtaking_rear_left.x = obj_x;
        ta_sl_info_.overtaking_rear_left.y = obj_y;

        obj_x2 = obj_x * obj_x;
        obj_x3 = obj_x2 * obj_x;
        lane_objx_y = lane_info.c0 + lane_info.c1 * obj_x + lane_info.c2 * obj_x2 + lane_info.c3 * obj_x3; // 道路中心线在目标前保中心x处的y坐标（正值表示在道路中心线左侧）
        lFrmObjPnt2Rd = obj_y - lane_objx_y; // 目标前保中心相对于道路中心线的横向距离(负值表示在道路中心线左侧)
        lFrmObjPnt2Rd = lFrmObjPnt2Rd + 0.5 * as_ot.width; // 目标右前角点相对于道路中心线的横向距离
        
        lane_objx_heading = std::atan2(lane_info.c1 + 2 * lane_info.c2 * obj_x + 3 * lane_info.c3 * obj_x2, 1); // 目标前保中心处相对于道路中心线的heading
        lane_objx_heading_sin = std::sin(lane_objx_heading);
        lane_objx_heading_cos = std::cos(lane_objx_heading);

        // ta_sl_info_.overtaking_rear_left.l = (lFrmObjPnt2Rd + lFrmEgoPnt2Rd) * lane_objx_heading_cos;
        ta_sl_info_.overtaking_rear_left.l = lFrmObjPnt2Rd * lane_objx_heading_cos + ta_sl_info_.ego.l_front_left_corner; // 在道路模型下目标右前角点相对于自车左前角点距离；（负值表示障碍物在自车左侧）
        ta_sl_info_.overtaking_rear_left.vl = as_ot.vcs_long_vel * lane_objx_heading_sin - as_ot.vcs_lat_vel * lane_objx_heading_cos;
        ta_sl_info_.overtaking_rear_left.al = as_ot.vcs_long_accel * lane_objx_heading_sin - as_ot.vcs_lat_accel * lane_objx_heading_cos;
        
        ta_sl_info_.overtaking_rear_left.s = obj_x; // 纵向信息用笛卡尔坐标系下的，目标前保与自车后轴
        ta_sl_info_.overtaking_rear_left.vs = as_ot.vcs_long_vel;
        ta_sl_info_.overtaking_rear_left.as = as_ot.vcs_long_accel;
    }

    void ElkThreatAssessment::calOvertakingRearRightSL(const AsOverTakingObject &as_ot, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config)
    {
        float obj_x, obj_y, lane_objx_y, lane_objx_heading, obj_x2, obj_x3;
        float lane_objx_heading_sin, lane_objx_heading_cos;
        float lFrmObjPnt2Rd;
        // 处理右侧车道后向overtaking目标
        obj_x = as_ot.vcs_long_posn + 0.5F * as_ot.length * std::cos(-as_ot.vcs_heading); // 前保中心x坐标
        obj_y = as_ot.vcs_lat_posn + 0.5 * as_ot.length * std::sin(-as_ot.vcs_heading); // 前保中心y坐标相对于自车的横向距离(正值表示在自车右侧)
        // 融合输入是几何中心，LgSafe处理成后保中心
        // vcs_heading正值表示自车运动方向需要逆时针旋转到目标运动方向
        ta_sl_info_.overtaking_rear_right.x = obj_x;
        ta_sl_info_.overtaking_rear_right.y = obj_y;

        obj_x2 = obj_x * obj_x;
        obj_x3 = obj_x2 * obj_x;
        lane_objx_y = lane_info.c0 + lane_info.c1 * obj_x + lane_info.c2 * obj_x2 + lane_info.c3 * obj_x3; // 道路中心线在目标前保中心x处的y坐标(负值表示在道路中心线右侧)
        lFrmObjPnt2Rd = obj_y - lane_objx_y; // 目标前保中心相对于道路中心线的横向距离(正值表示在道路中心线右侧)
        lFrmObjPnt2Rd = lFrmObjPnt2Rd - 0.5 * as_ot.width; // 目标左前角点相对于道路中心线的横向距离

        lane_objx_heading = std::atan2(lane_info.c1 + 2 * lane_info.c2 * obj_x + 3 * lane_info.c3 * obj_x2, 1); // 目标前保中心处相对于道路中心线的heading(负值自车车头朝右)
        lane_objx_heading_sin = std::sin(lane_objx_heading);
        lane_objx_heading_cos = std::cos(lane_objx_heading);

        // ta_sl_info_.oncoming_front_right.l = (lFrmObjPnt2Rd + lFrmEgoPnt2Rd) * lane_objx_heading_cos;
        ta_sl_info_.overtaking_rear_right.l = lFrmObjPnt2Rd * lane_objx_heading_cos + ta_sl_info_.ego.l_front_right_corner; // 在道路模型下目标左前角点相对于自车右前角点距离;（正值表示障碍物在自车右侧）
        ta_sl_info_.overtaking_rear_right.vl = as_ot.vcs_long_vel * lane_objx_heading_sin - as_ot.vcs_lat_vel * lane_objx_heading_cos; // 在道路模型下目标前轴相对于车道中心偏离速度;（负值表示向右偏离）
        ta_sl_info_.overtaking_rear_right.al = as_ot.vcs_long_accel * lane_objx_heading_sin - as_ot.vcs_lat_accel * lane_objx_heading_cos;
        
        ta_sl_info_.overtaking_rear_right.s = obj_x; // 纵向信息用笛卡尔坐标系下的，目标前保与自车后轴
        ta_sl_info_.overtaking_rear_right.vs = as_ot.vcs_long_vel;
        ta_sl_info_.overtaking_rear_right.as = as_ot.vcs_long_accel;
    }

    void ElkThreatAssessment::calQuadraticEquationS(ElkObjSl &obj_sl, bool is_front_obj, bool use_const_vel_model)
    {
        float A, B, C, delta, delta_sqrt, root1, root2;
        float epsn = 1e-4;

        if (is_front_obj) {
            A = 0.5 * (obj_sl.as - ta_sl_info_.ego.as);
            B = (obj_sl.vs - ta_sl_info_.ego.vs);
            C = obj_sl.s;
        } else {
            A = 0.5 * (ta_sl_info_.ego.as - obj_sl.as);
            B = (ta_sl_info_.ego.vs - obj_sl.vs);
            C = -obj_sl.s;
        }
        if (use_const_vel_model) {
            A = 0.0F;
        }
        delta = B * B - 4 * A * C;

        if ((fabs(A) <= epsn)  &&  (fabs(B) <= epsn)) {
            obj_sl.ttc_s = 10.0F;
        } else if (fabs(A) <= epsn) {
            obj_sl.ttc_s = math::SafeDivide(-C, B);
        } else { // 一元二次方程问题
            if (delta < 0) { // 无解，无碰撞风险
                obj_sl.ttc_s = 10.0F;
            } else if (delta <= epsn) { // 有唯一解
                obj_sl.ttc_s = math::SafeDivide(-B, 2 * A);
            } else { // 有2个解
                delta_sqrt = std::sqrt(delta);
                root1 = math::SafeDivide(-B + delta_sqrt, 2 * A);
                root2 = math::SafeDivide(-B - delta_sqrt, 2 * A);
                if (root1 * root2 > 0) obj_sl.ttc_s = std::min(root1, root2);
                else if (root1 >= 0) obj_sl.ttc_s = root1;
                else obj_sl.ttc_s = root2;
            }
        }
    }

    void ElkThreatAssessment::calQuadraticEquationL(ElkObjSl &obj_sl, bool use_const_vel_model)
    {
        float A, B, C, delta, delta_sqrt, root1, root2;
        float epsn = 1e-4;

        A = 0.5 * (ta_sl_info_.ego.al - obj_sl.al);
        B = ta_sl_info_.ego.vl - obj_sl.vl;
        C = obj_sl.l;
        if (use_const_vel_model) {
            A = 0.0F;
        }
        delta = B * B - 4 * A * C;

        if ((fabs(A) <= epsn)  &&  (fabs(B) <= epsn)) {
            obj_sl.ttc_l = 10.0F;
        } else if (fabs(A) <= epsn) {
            obj_sl.ttc_l = math::SafeDivide(-C, B);
        } else { // 一元二次方程问题
            if (delta < 0) { // 无解，无碰撞风险
                obj_sl.ttc_l = 10.0F;
            } else if (delta <= epsn) { // 有唯一解
                obj_sl.ttc_l = math::SafeDivide(-B, 2 * A);
            } else { // 有2个解
                delta_sqrt = std::sqrt(delta);
                root1 = math::SafeDivide(-B + delta_sqrt, 2 * A);
                root2 = math::SafeDivide(-B - delta_sqrt, 2 * A);
                if (root1 * root2 > 0) obj_sl.ttc_l = std::min(root1, root2);
                else if (root1 >= 0) obj_sl.ttc_l = root1;
                else obj_sl.ttc_l = root2;
            }
        }
    }

    float ElkThreatAssessment::predictLongDist(const ElkObjSl &obj_sl, float pred_time, bool use_const_vel_model) const
    {
        const float rel_accel = use_const_vel_model ? 0.0F : (obj_sl.as - ta_sl_info_.ego.as);
        return obj_sl.s + (obj_sl.vs - ta_sl_info_.ego.vs) * pred_time + 0.5F * rel_accel * pred_time * pred_time;
    }

    float ElkThreatAssessment::predictLatDist(const ElkObjSl &obj_sl, float pred_time, bool use_const_vel_model) const
    {
        const float rel_accel = use_const_vel_model ? 0.0F : (ta_sl_info_.ego.al - obj_sl.al);
        return obj_sl.l + (ta_sl_info_.ego.vl - obj_sl.vl) * pred_time + 0.5F * rel_accel * pred_time * pred_time;
    }

    bool ElkThreatAssessment::checkCollisionConsistent(const ElkObjSl &obj_sl,
                                                       bool is_left_obj,
                                                       bool is_front_obj,
                                                       float obj_length,
                                                       float host_front_dist,
                                                       bool use_const_vel_model) const
    {
        if ((obj_sl.ttc_s < 0.01F) || (obj_sl.ttc_l < 0.01F)) {
            return false;
        }

        const float pred_time = std::max(obj_sl.ttc_s, obj_sl.ttc_l);
        if (pred_time > elk_cals_.k_ELK_TA_MaxPredictionTime) {
            return false;
        }

        const float l_at_t = predictLatDist(obj_sl, pred_time, use_const_vel_model);
        const bool lat_consistent = is_left_obj ?
            (l_at_t >= -elk_cals_.k_ELK_TA_Collision_LatMargin) :
            (l_at_t <= elk_cals_.k_ELK_TA_Collision_LatMargin);

        const float s_at_t = predictLongDist(obj_sl, pred_time, use_const_vel_model);
        bool long_consistent = false;
        float target_tail_s_at_t = 0.0F;
        if (is_front_obj) {
            long_consistent = s_at_t >= -elk_cals_.k_ELK_TA_Collision_LongMargin;
        } else {
            target_tail_s_at_t = s_at_t - obj_length;
            long_consistent = (s_at_t >= -elk_cals_.k_ELK_TA_Collision_LongMargin) &&
                (target_tail_s_at_t <= host_front_dist + elk_cals_.k_ELK_TA_Collision_LongMargin);
        }

        return lat_consistent && long_consistent;
    }

    void ElkThreatAssessment::calculateTTC(const AsOverTakingOut &overtake_out)
    {
        calQuadraticEquationS(ta_sl_info_.oncoming_front_left, true, false);    // 计算左前oncoming目标纵向ttc
        calQuadraticEquationL(ta_sl_info_.oncoming_front_left, false);          // 计算左前oncoming目标横向ttc

        calQuadraticEquationS(ta_sl_info_.oncoming_front_right, true, false);   // 计算右前oncoming目标纵向ttc
        calQuadraticEquationL(ta_sl_info_.oncoming_front_right, false);         // 计算右前oncoming目标横向ttc

        const bool use_const_vel_left =
            overtake_out.overtake_target_rear_left.length > elk_cals_.k_ELK_LargeRearTargetLength;
        threat_debug_snapshot_.left_ot_const_vel_model = use_const_vel_left;
        calQuadraticEquationS(ta_sl_info_.overtaking_rear_left, false, use_const_vel_left);  // 计算左后overtaking目标纵向ttc
        calQuadraticEquationL(ta_sl_info_.overtaking_rear_left, use_const_vel_left);         // 计算左后overtaking目标横向ttc

        const bool use_const_vel_right =
            overtake_out.overtake_target_rear_right.length > elk_cals_.k_ELK_LargeRearTargetLength;
        threat_debug_snapshot_.right_ot_const_vel_model = use_const_vel_right;
        calQuadraticEquationS(ta_sl_info_.overtaking_rear_right, false, use_const_vel_right); // 计算右后overtaking目标纵向ttc
        calQuadraticEquationL(ta_sl_info_.overtaking_rear_right, use_const_vel_right);        // 计算右后overtaking目标横向ttc
    }

    void ElkThreatAssessment::oncomingSLJudge(const AsVseOut &vse_out,
                                              const AsOnComingOut &oncom_out,
                                              const GlobalConfig &config)
    {
        float s_thr, rel_spd_kph;
        bool dist_s_judge, ttc_s_judge, dist_l_judge, collision_consistent_judge;

        // 左侧危险性判断
        rel_spd_kph = (vse_out.speed + fabs(oncom_out.oncom_target_1.vcs_long_vel)) * 3.6;
        s_thr = math::LookUpTable::LookupTable1D<9>(elk_cals_.k_ELK_S_FrontEdgeThr_OC_x, elk_cals_.k_ELK_S_FrontEdgeThr_OC_z, rel_spd_kph);
        
        dist_s_judge = (ta_sl_info_.oncoming_front_left.s >= 0) && (ta_sl_info_.oncoming_front_left.s <= s_thr);
        ttc_s_judge = (ta_sl_info_.oncoming_front_left.ttc_s >= 0.01) &&
            (ta_sl_info_.oncoming_front_left.ttc_s <= elk_cals_.k_ELK_S_TTCThr_OC * config.k_ELK_OC_ObjTTCScale);

        dist_l_judge = ta_sl_info_.oncoming_front_left.l >= -elk_cals_.k_ELK_L_LatEdgThr_OC;
        collision_consistent_judge = checkCollisionConsistent(
            ta_sl_info_.oncoming_front_left, true, true, oncom_out.oncom_target_1.length, 0.0F, false);
        const bool left_oc_motion_judge = updateOcMotionGuardDebug(
            oncom_out.oncom_target_1, elk_cals_, threat_debug_snapshot_.left_oc_motion_guard);
        threat_debug_snapshot_.left_oc_motion_guard.collision_consistent = collision_consistent_judge;

        // For ELK LCT target activation, lateral risk is judged by lane-departure TTLC
        // in ElkScenarioDecision. The legacy collision check remains diagnostic only.
        ta_sl_info_.oncoming_front_left.threat = (oncom_out.oncom_target_1.track_id > 0) &&
            left_oc_motion_judge && (dist_s_judge && ttc_s_judge) && dist_l_judge;

        // 右侧危险性判断
        rel_spd_kph = (vse_out.speed + fabs(oncom_out.oncom_target_2.vcs_long_vel)) * 3.6;
        s_thr = math::LookUpTable::LookupTable1D<9>(elk_cals_.k_ELK_S_FrontEdgeThr_OC_x, elk_cals_.k_ELK_S_FrontEdgeThr_OC_z, rel_spd_kph);
        s_thr *= elk_cals_.k_ELK_RightOC_S_FrontEdgeThrScale;
        
        dist_s_judge = (ta_sl_info_.oncoming_front_right.s >= 0) && (ta_sl_info_.oncoming_front_right.s <= s_thr);
        ttc_s_judge = (ta_sl_info_.oncoming_front_right.ttc_s >= 0.01) &&
            (ta_sl_info_.oncoming_front_right.ttc_s <= elk_cals_.k_ELK_RightOC_S_TTCThr * config.k_ELK_OC_ObjTTCScale);

        dist_l_judge = ta_sl_info_.oncoming_front_right.l <= elk_cals_.k_ELK_RightOC_L_LatEdgThr;
        collision_consistent_judge = checkCollisionConsistent(
            ta_sl_info_.oncoming_front_right, false, true, oncom_out.oncom_target_2.length, 0.0F, false);
        const bool right_oc_motion_judge = updateOcMotionGuardDebug(
            oncom_out.oncom_target_2, elk_cals_, threat_debug_snapshot_.right_oc_motion_guard);
        threat_debug_snapshot_.right_oc_motion_guard.collision_consistent = collision_consistent_judge;

        // For ELK LCT target activation, lateral risk is judged by lane-departure TTLC
        // in ElkScenarioDecision. The legacy collision check remains diagnostic only.
        ta_sl_info_.oncoming_front_right.threat = (oncom_out.oncom_target_2.track_id > 0) &&
            right_oc_motion_judge && (dist_s_judge && ttc_s_judge) && dist_l_judge;
    }

    void ElkThreatAssessment::overtakingSLJudge(const AsVseOut &vse_out,
                                                const AsOverTakingOut &overtake_out,
                                                const GlobalConfig &config)
    {
        float s_thr;
        bool dist_s_judge, ttc_s_judge, dist_l_judge, ttc_l_judge, collision_consistent_judge;
        s_thr = math::LookUpTable::LookupTable1D<12>(elk_cals_.k_ELK_S_LonEdgThr_OT_x, elk_cals_.k_ELK_S_LonEdgThr_OT_z, 3.6 * vse_out.speed);

        // 左侧危险性判断
        dist_s_judge = (ta_sl_info_.overtaking_rear_left.s >= -s_thr) && (ta_sl_info_.overtaking_rear_left.s <= s_thr);
        ttc_s_judge = (ta_sl_info_.overtaking_rear_left.ttc_s >= 0.01) &&
            (ta_sl_info_.overtaking_rear_left.ttc_s <= elk_cals_.k_ELK_S_TTCThr_OT * config.k_ELK_OT_ObjTTCScale);

        dist_l_judge = ta_sl_info_.overtaking_rear_left.l >= -elk_cals_.k_ELK_L_LatEdgThr_OT;
        ttc_l_judge = (ta_sl_info_.overtaking_rear_left.ttc_l >= 0.01) &&
            (ta_sl_info_.overtaking_rear_left.ttc_l <= elk_cals_.k_ELK_L_TTCThr_OT * config.k_ELK_OT_ObjTTCScale);
        collision_consistent_judge = checkCollisionConsistent(
            ta_sl_info_.overtaking_rear_left,
            true,
            false,
            overtake_out.overtake_target_rear_left.length,
            vse_out.config.k_dist_to_rear_axle,
            overtake_out.overtake_target_rear_left.length > elk_cals_.k_ELK_LargeRearTargetLength);

        threat_debug_snapshot_.left_ot_collision_consistent = collision_consistent_judge;
        ta_sl_info_.overtaking_rear_left.threat = (overtake_out.overtake_target_rear_left.track_id > 0) && 
            (dist_s_judge && ttc_s_judge) && (dist_l_judge && ttc_l_judge) && collision_consistent_judge;

        // 右侧危险性判断
        dist_s_judge = (ta_sl_info_.overtaking_rear_right.s >= -s_thr) && (ta_sl_info_.overtaking_rear_right.s <= s_thr);
        ttc_s_judge = (ta_sl_info_.overtaking_rear_right.ttc_s >= 0.01) &&
            (ta_sl_info_.overtaking_rear_right.ttc_s <= elk_cals_.k_ELK_S_TTCThr_OT * config.k_ELK_OT_ObjTTCScale);

        dist_l_judge = ta_sl_info_.overtaking_rear_right.l <= elk_cals_.k_ELK_L_LatEdgThr_OT;
        ttc_l_judge = (ta_sl_info_.overtaking_rear_right.ttc_l >= 0.01) &&
            (ta_sl_info_.overtaking_rear_right.ttc_l <= elk_cals_.k_ELK_L_TTCThr_OT * config.k_ELK_OT_ObjTTCScale);
        collision_consistent_judge = checkCollisionConsistent(
            ta_sl_info_.overtaking_rear_right,
            false,
            false,
            overtake_out.overtake_target_rear_right.length,
            vse_out.config.k_dist_to_rear_axle,
            overtake_out.overtake_target_rear_right.length > elk_cals_.k_ELK_LargeRearTargetLength);

        threat_debug_snapshot_.right_ot_collision_consistent = collision_consistent_judge;
        ta_sl_info_.overtaking_rear_right.threat = (overtake_out.overtake_target_rear_right.track_id > 0) && 
            (dist_s_judge && ttc_s_judge) && (dist_l_judge && ttc_l_judge) && collision_consistent_judge;
    }
} // namespace elk
} // namespace active_safety
