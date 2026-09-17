#ifndef TAP_SDK_ALGORITHM_ELK_ELK_THREAT_ASSESSMENT_H_
#define TAP_SDK_ALGORITHM_ELK_ELK_THREAT_ASSESSMENT_H_
#include "environment_processing.h"
#include "math/lookuptable/lookuptable.h"
#include "math/signalprocess/on_delay_block/on_delay_block.h"

#include <cstdint>

namespace active_safety {
namespace elk {

    struct ElkObjSl {
        float x;
        float y;
        float s;
        float l;
        float vs;
        float vl;
        float as;
        float al;
        float ttc_s;
        float ttc_l;
        bool threat;
    }; // 道路模型下，障碍物相对于自车的运动信息

    struct ElkEgoSl {
        float x;
        float x_front_head; // 前保中心x坐标
        float x_front_left_corner; // 左前角点x坐标
        float x_front_right_corner; // 右前角点x坐标
        float y;
        float y_front_head; // 前保中心y坐标
        float y_front_left_corner; // 左前角点y坐标
        float y_front_right_corner; // 右前角点y坐标
        float s;
        float l;
        float l_front_left_corner; // 左前角点l坐标
        float l_front_right_corner; // 右前角点l坐标（负值表示在车道中心线右侧）
        float vs;
        float vl;
        float as;
        float al;
    };

    struct ElkTaSl {
        ElkObjSl oncoming_front_left;
        ElkObjSl oncoming_front_right;
        ElkObjSl overtaking_rear_left;
        ElkObjSl overtaking_rear_right;
        ElkEgoSl ego;
    };

    struct ElkOcMotionGuardDebug {
        float long_vel = 0.0f;
        float min_oncoming_speed = 0.0f;
        float heading_abs = 0.0f;
        float heading_threshold = 0.0f;
        uint8_t f_oncoming = 0U;
        uint8_t movement = 0U;
        bool speed_valid = false;
        bool f_oncoming_valid = false;
        bool movement_valid = false;
        bool heading_valid = false;
        bool motion_valid = false;
        bool collision_consistent = false;
    };

    struct ElkThreatDebugSnapshot {
        ElkOcMotionGuardDebug left_oc_motion_guard;
        ElkOcMotionGuardDebug right_oc_motion_guard;
        bool left_ot_collision_consistent = false;
        bool right_ot_collision_consistent = false;
        bool left_ot_const_vel_model = false;
        bool right_ot_const_vel_model = false;
    };

    class ElkThreatAssessment
    {
    public:
        ElkThreatAssessment();
        ~ElkThreatAssessment() = default;

        void Update(const AsVseOut &vse_out,
                    const LaneCenterParameters &lane_info,
                    const VehicleConfig &veh_config,
                    const GlobalConfig &config,
                    const AsOnComingOut &oncom_out,
                    const AsOverTakingOut &overtake_out);
        const ElkTaSl getElkTAInfo() const { return ta_sl_info_; };
        const ElkThreatDebugSnapshot &getElkThreatDebugSnapshot() const { return threat_debug_snapshot_; }
    private:
        ElkCal elk_cals_;
        
        void calEgoSL(const AsVseOut &vse_out, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config);
        void calOncomingLeftSL(const AsOnComingObject &as_oc, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config);
        void calOncomingRightSL(const AsOnComingObject &as_oc, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config);
        float calOncomingToEgoS(const float x, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config);

        void calOvertakingRearLeftSL(const AsOverTakingObject &as_ot, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config);
        void calOvertakingRearRightSL(const AsOverTakingObject &as_ot, const LaneCenterParameters &lane_info, const VehicleConfig &veh_config);

        void calculateTTC(const AsOverTakingOut &overtake_out);
        void calQuadraticEquationS(ElkObjSl &obj_sl, bool is_front_obj, bool use_const_vel_model);
        void calQuadraticEquationL(ElkObjSl &obj_sl, bool use_const_vel_model);
        float predictLongDist(const ElkObjSl &obj_sl, float pred_time, bool use_const_vel_model) const;
        float predictLatDist(const ElkObjSl &obj_sl, float pred_time, bool use_const_vel_model) const;
        bool checkCollisionConsistent(const ElkObjSl &obj_sl,
                                      bool is_left_obj,
                                      bool is_front_obj,
                                      float obj_length,
                                      float host_front_dist,
                                      bool use_const_vel_model) const;

        void oncomingSLJudge(const AsVseOut &vse_out, const AsOnComingOut &oncom_out, const GlobalConfig &config);
        void overtakingSLJudge(const AsVseOut &vse_out, const AsOverTakingOut &overtake_out, const GlobalConfig &config);

        ElkTaSl ta_sl_info_;
        ElkThreatDebugSnapshot threat_debug_snapshot_;
    /* data */
    };
    
} // namespace elk
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_ELK_ELK_THREAT_ASSESSMENT_H_
