
#include "threat_assessor.h"

namespace active_safety {
namespace longsafe {

ThreatAssessor::ThreatAssessor() {
}

ThreatAssessor::~ThreatAssessor() = default;

void ThreatAssessor::Update(const AsVseOut &vse_out, const DriverEvaluator &drvr_sts, const LongSafeObject &obs, const AsCurvaturePath &ego_path) {
    if (obs.fus_trkID <= 0) {
        return;
    }

    VehDelayComp(vse_out, drvr_sts, obs);
    ObjectPredictPath(obs);
    EstimateObjectPosInpath(obs.offs_lat_inpath_primary_target, obs.offs_lgt_short_pred);
    LtapThreatAssessLongitudinal();
    LtapThreatAssessLateral(obs, ego_path);
    CalcFcwTtcByDist(vse_out, obs);
    CalcTtrTimeDistNear(ego_path, obs, vse_out);
    if (fabs(vse_out.rear_curvature_radius) < 70.0F) {
        CalcTimeToBrake(host_data_.v0, host_data_.a0, 0.0F, 0.0F, 0.0F);
    } else {
        CalcTimeToBrake(host_data_.v0, host_data_.a0, linear_predict_.long_vel, linear_predict_.long_accel, 0.0F);
    }
    ThreatEvaluator(vse_out, obs, drvr_sts);
}

void ThreatAssessor::VehDelayComp(const AsVseOut &vse_out, const DriverEvaluator &drvr_sts, const LongSafeObject &obs) {
    // Calc veh delay.
    veh_delay_time_ = math::LookUpTable::LookupTable1D<10>(threat_ass_cal_.k_accel_points_for_brake_delay_x,
                                                           threat_ass_cal_.k_accel_time_for_brake_delay_y, vse_out.long_accel);
    veh_delay_time_ = fminf(threat_ass_cal_.k_brake_delay_max_time, veh_delay_time_);
    veh_delay_time_ = fmaxf(threat_ass_cal_.k_brake_delay_min_time, veh_delay_time_);

    // Predict object state after veh brake delay.
    LinearPredictAlgorithm(obs, veh_delay_time_, linear_predict_);
    CircularPredictAlgorithm(obs, veh_delay_time_, circular_predict_);
    // Predict host state after veh brake delay.
    HostPredictAlgorithm(vse_out, veh_delay_time_, host_predict_);
    // Transform object to current vehicle coordinate.
    TransformObject();
    CollectStateData(vse_out, drvr_sts, obs);

    veh_delay_host_travel_ = host_predict_.long_pos;
    veh_delay_obs_travel_ = linear_predict_.long_pos - obs.long_posn;
}

void ThreatAssessor::CalcTtrTimeDistNear(const AsCurvaturePath &ego_path, const LongSafeObject &obs, const AsVseOut &vse_out) {

    if (fabs(vse_out.rear_curvature) < 0.001F) {
        min_dist_near_ = ego_path.GetHostState(obs.ttr).long_pos;
        return;
    }
    constexpr float max_predict_time = 4.0F;

    MotionStateAtTime pre_host_sts{};
    MotionStateAtTime curr_host_sts{};

    const float ratio = math::SafeDivide(obs.ttr, LGSF_FUNC_TIME_STEP);
    const int iter_idx = static_cast<int>(std::round(ratio));
    const int valid_idx = std::max(1, iter_idx);

    min_dist_near_ = 0.0F;
    for (int i = 1; i <= valid_idx; ++i) {
        const float pred_time = std::fmin(static_cast<float>(i) * LGSF_FUNC_TIME_STEP, max_predict_time);
        curr_host_sts = ego_path.GetHostState(pred_time);

        const float dx = curr_host_sts.long_pos - pre_host_sts.long_pos;
        const float dy = curr_host_sts.lat_pos - pre_host_sts.lat_pos;
        const float dist = std::hypot(dx, dy);

        min_dist_near_ += dist;

        pre_host_sts = curr_host_sts;
    }
    // std::cout << "obs.ttr:" << obs.ttr << "obs.long_posn:" << obs.long_posn << "total_brk_time:" << total_brk_time
    //           << "min_dist_near:" << min_dist_near_ << "rear_curvature:" << vse_out.rear_curvature << "speed:" << vse_out.speed
    //           << "threat_range_:" << threat_range_ << std::endl;
}

void ThreatAssessor::StopDistanceFactorCal(const AsVseOut &vse_out, const LongSafeObject &obs, const DriverEvaluator &drvr_evaluator) {

    bool drvr_braking = drvr_evaluator.drvr_actv_sts_.drvr_braking;
    aeb_dist_factor_ = 1.0;

    if (drvr_evaluator.drvr_actv_sts_.drvr_steer) {
        aeb_dist_factor_ = fmin(threat_ass_cal_.k_drvbeh_str_fac, aeb_dist_factor_);
    }
    if (drvr_evaluator.drvr_actv_sts_.drvr_steer_fast) {
        aeb_dist_factor_ = fmin(threat_ass_cal_.k_drvbeh_strfast_fac, aeb_dist_factor_);
    }
    if (drvr_evaluator.drvr_actv_sts_.drvr_accelerating) {
        aeb_dist_factor_ = fmin(threat_ass_cal_.k_drvbeh_accel_fac, aeb_dist_factor_);
    }

    if (threat_ass_cal_.k_drv_enable_drvbrk_fac) {
        if (drvr_evaluator.drvr_actv_sts_.drvr_braking) {
            aeb_dist_factor_ = fmin(threat_ass_cal_.k_drvbeh_brake_fac, aeb_dist_factor_);
        }
    } else {
        if (drvr_evaluator.drvr_actv_sts_.drvr_decel) {
            aeb_dist_factor_ = fmin(threat_ass_cal_.k_drvbeh_brake_fac, aeb_dist_factor_);
        }
    }

    iba_dist_factor_ = 1.0;
    aeb_dist_factor_ = math::Clamp(aeb_dist_factor_, 0.5F, 1.0F);
}

void ThreatAssessor::ThreatEvaluator(const AsVseOut &vse_out, const LongSafeObject &obs, const DriverEvaluator &drvr_evaluator) {
    threat_range_ = threat_range_ + veh_delay_host_travel_ - veh_delay_obs_travel_ + obs.offs_lgt_short_pred;
    bool ttc_check = false;
    if (vse_out.aeb_active) {
        ttc_check = true;
    } else {
        float rel_spd = fabs(obs.long_vel - vse_out.vcs_long_vel);
        float ttc_thres =
            math::LookUpTable::LookupTable1D<9>(threat_ass_cal_.k_rel_spd_min_ttc_for_threat, threat_ass_cal_.k_ttc_min_ttc_for_threat, rel_spd);
        if ((obs.ttr > veh_delay_time_)  &&  (obs.ttr < ttc_thres)) {
            ttc_check = true;
        }
    }
    StopDistanceFactorCal(vse_out, obs, drvr_evaluator);
    float aeb_threat_dist = threat_range_ * aeb_dist_factor_;
    float rel_spd = fabs(vse_out.vcs_long_vel - obs.long_vel);
    float abp_threat_dist = aeb_threat_dist + rel_spd * 0.15F;
    float aba_threat_dist = abp_threat_dist + rel_spd * 0.8F;

    threat_autobraking_ = ((aeb_threat_dist >= (min_dist_near_))  &&  (threat_range_ >= 1e-6)  &&  ttc_check);
    threat_iba_ = ((threat_range_ * iba_dist_factor_ >= (min_dist_near_))  &&  (threat_range_ >= 1e-6)  &&  ttc_check);

    threat_abp_ = ((abp_threat_dist >= (min_dist_near_))  &&  (threat_range_ >= 1e-6)  &&  ttc_check);
    threat_aba_ = ((aba_threat_dist >= (min_dist_near_))  &&  (threat_range_ >= 1e-6)  &&  ttc_check);
}

void ThreatAssessor::CollectStateData(const AsVseOut &vse_out, const DriverEvaluator &drvr_sts, const LongSafeObject &obs) {
    // Collect host data.
    host_data_.c0 = host_predict_.curvature;
    host_data_.v0 = host_predict_.long_vel;
    host_data_.a0 = host_predict_.long_accel;
    host_data_.amin = drvr_sts.motion_limit_.min_long_neg_accel;
    host_data_.amax = drvr_sts.motion_limit_.max_long_pos_accel;
    host_data_.length = vse_out.config.k_host_length;
    host_data_.width = vse_out.config.k_host_width;
    // d0 = Length - Lc,Lc is dist to rear axle, here Lc is 0.
    host_data_.d0 = vse_out.config.k_dist_to_rear_axle;

    host_data_.tj_brake = math::SafeDivide(drvr_sts.motion_limit_.min_long_neg_accel - host_data_.a0, drvr_sts.motion_limit_.min_long_neg_jerk);
    host_data_.tj_brake = fmaxf(threat_ass_cal_.k_min_jerk_duration, host_data_.tj_brake);

    host_data_.tj_accel = math::SafeDivide(drvr_sts.motion_limit_.max_long_pos_accel - host_data_.a0, drvr_sts.motion_limit_.max_long_pos_jerk);
    host_data_.tj_accel = fmaxf(threat_ass_cal_.k_min_jerk_duration, host_data_.tj_accel);

    float squard_v0 = host_data_.v0 * host_data_.v0;

    float c0_max_lat_acc = math::SafeDivide(drvr_sts.motion_limit_.max_abs_lat_accel, squard_v0);
    //
    float c0_max_drvr = math::SafeDivide(threat_ass_cal_.k_max_str_whl_ang_rad, vse_out.config.k_wheel_base);
    host_data_.cmax = fminf(c0_max_drvr, c0_max_lat_acc);

    float c1_max_lat_jerk = math::SafeDivide(drvr_sts.motion_limit_.max_abs_lat_jerk, squard_v0);

    float c1_max_drvr_str_rate = math::SafeDivide(threat_ass_cal_.k_max_str_whl_ang_rate_rad, vse_out.config.k_steer_ratio);
    c1_max_drvr_str_rate = math::SafeDivide(c1_max_drvr_str_rate, vse_out.config.k_wheel_base);
    float c1_max = fminf(c1_max_drvr_str_rate, c1_max_lat_jerk);

    host_data_.ttheta_left = math::SafeDivide(host_data_.cmax - host_data_.c0, c1_max);
    host_data_.ttheta_left = fmaxf(threat_ass_cal_.k_min_jerk_duration, host_data_.ttheta_left);

    host_data_.ttheta_right = math::SafeDivide(host_data_.cmax + host_data_.c0, c1_max);
    host_data_.ttheta_right = fmaxf(threat_ass_cal_.k_min_jerk_duration, host_data_.ttheta_right);

    // Collect object data.
    obj_data_.offs_lat = obs.offs_lat_short_pred;
    obj_data_.width = obs.width;
    obj_data_.length = obs.length;
    obj_data_.l0 = obs.length * 0.5F;
}

void ThreatAssessor::LtapFindLatClosestEdges(float lgt_pos, float lat_pos, float heading, float l0, float width, int index,
                                             const MotionStateAtTime host_state) {

    float half_tgt_width = width * 0.5F;
    float cos_hdg = cosf(heading);
    float sin_hdg = sinf(heading);

    float cos_hf_width = cos_hdg * half_tgt_width;
    float sin_hf_width = sin_hdg * half_tgt_width;

    float cos_l0 = cos_hdg * l0;
    float sin_l0 = sin_hdg * l0;

    Point2D rear_right;
    Point2D rear_left;
    Point2D front_right;
    Point2D front_left;

    Point2D relative_rear_right;
    Point2D relative_rear_left;
    Point2D relative_front_right;
    Point2D relative_front_left;

    relative_rear_right.x = lgt_pos - cos_l0 + sin_hf_width - host_state.long_pos;
    relative_rear_right.y = lat_pos - sin_l0 - cos_hf_width - host_state.lat_pos;

    relative_rear_left.x = lgt_pos - cos_l0 - sin_hf_width - host_state.long_pos;
    relative_rear_left.y = lat_pos - sin_l0 + cos_hf_width - host_state.lat_pos;

    relative_front_right.x = lgt_pos + cos_l0 + sin_hf_width - host_state.long_pos;
    relative_front_right.y = lat_pos + sin_l0 - cos_hf_width - host_state.lat_pos;

    relative_front_left.x = lgt_pos + cos_l0 - sin_hf_width - host_state.long_pos;
    relative_front_left.y = lat_pos + sin_l0 + cos_hf_width - host_state.lat_pos;

    rear_right.x = lgt_pos - cos_l0 + sin_hf_width;
    rear_right.y = lat_pos - sin_l0 - cos_hf_width;

    rear_left.x = lgt_pos - cos_l0 - sin_hf_width;
    rear_left.y = lat_pos - sin_l0 + cos_hf_width;

    front_right.x = lgt_pos + cos_l0 + sin_hf_width;
    front_right.y = lat_pos + sin_l0 - cos_hf_width;

    front_left.x = lgt_pos + cos_l0 - sin_hf_width;
    front_left.y = lat_pos + sin_l0 + cos_hf_width;

    // 构造候选边：4 条边 + 2 条对角线
    LtapEdge cand_edges[6];
    LtapEdge relative_cand_edges[6];
    // FRONT
    cand_edges[0].p0 = front_left;
    cand_edges[0].p1 = front_right;
    // REAR
    cand_edges[1].p0 = rear_left;
    cand_edges[1].p1 = rear_right;
    // LEFT
    cand_edges[2].p0 = rear_left;
    cand_edges[2].p1 = front_left;
    // RIGHT
    cand_edges[3].p0 = rear_right;
    cand_edges[3].p1 = front_right;
    // DIAGONAL FL-RR
    cand_edges[4].p0 = front_left;
    cand_edges[4].p1 = rear_right;
    // DIAGONAL FR-RL
    cand_edges[5].p0 = front_right;
    cand_edges[5].p1 = rear_left;

    // FRONT
    relative_cand_edges[0].p0 = relative_front_left;
    relative_cand_edges[0].p1 = relative_front_right;
    // REAR
    relative_cand_edges[1].p0 = relative_rear_left;
    relative_cand_edges[1].p1 = relative_rear_right;
    // LEFT
    relative_cand_edges[2].p0 = relative_rear_left;
    relative_cand_edges[2].p1 = relative_front_left;
    // RIGHT
    relative_cand_edges[3].p0 = relative_rear_right;
    relative_cand_edges[3].p1 = relative_front_right;
    // DIAGONAL FL-RR
    relative_cand_edges[4].p0 = relative_front_left;
    relative_cand_edges[4].p1 = relative_rear_right;
    // DIAGONAL FR-RL
    relative_cand_edges[5].p0 = relative_front_right;
    relative_cand_edges[5].p1 = relative_rear_left;

    // 计算每条候选边中点到圆心(0,0)的距离平方
    float dist2[6];
    for (int i = 0; i < 6; ++i) {
        float mid_x = 0.5F * (relative_cand_edges[i].p0.x + relative_cand_edges[i].p1.x);
        float mid_y = 0.5F * (relative_cand_edges[i].p0.y + relative_cand_edges[i].p1.y);
        dist2[i] = mid_x * mid_x + mid_y * mid_y;
    }

    // 选出距离圆心最近的 3 条边（按中点距离从小到大）
    int first_idx = 0;
    int second_idx = 1;
    int third_idx = 2;

    // 先对前 3 个做一个简单排序，保证 dist2[first] <= dist2[second] <= dist2[third]
    if (dist2[first_idx] > dist2[second_idx]) {
        int tmp = first_idx;
        first_idx = second_idx;
        second_idx = tmp;
    }
    if (dist2[second_idx] > dist2[third_idx]) {
        int tmp = second_idx;
        second_idx = third_idx;
        third_idx = tmp;
    }
    if (dist2[first_idx] > dist2[second_idx]) {
        int tmp = first_idx;
        first_idx = second_idx;
        second_idx = tmp;
    }

    // 用之后的候选边更新前三小
    for (int i = 3; i < 6; ++i) {
        if (dist2[i] < dist2[third_idx]) {
            if (dist2[i] < dist2[second_idx]) {
                if (dist2[i] < dist2[first_idx]) {
                    third_idx = second_idx;
                    second_idx = first_idx;
                    first_idx = i;
                } else {
                    third_idx = second_idx;
                    second_idx = i;
                }
            } else {
                third_idx = i;
            }
        }
    }

    obj_edges_[index][0] = cand_edges[first_idx];
    obj_edges_[index][1] = cand_edges[second_idx];
    obj_edges_[index][2] = cand_edges[third_idx];
}

std::array<LtapEdge, 3> ThreatAssessor::LtapGetLongClosestEdge(float lgt_pos, float lat_pos, float heading) {
    std::array<LtapEdge, 3> edges;

    float half_tgt_width = obj_data_.width * 0.5F;
    float cos_hdg = cosf(heading);
    float sin_hdg = sinf(heading);

    float cos_hf_width = cos_hdg * half_tgt_width;
    float sin_hf_width = sin_hdg * half_tgt_width;

    float cos_l0 = cos_hdg * obj_data_.l0;
    float sin_l0 = sin_hdg * obj_data_.l0;

    Point2D rear_right;
    Point2D rear_left;
    Point2D front_right;
    Point2D front_left;

    rear_right.x = lgt_pos - cos_l0 + sin_hf_width;
    rear_right.y = lat_pos - sin_l0 - cos_hf_width;

    rear_left.x = lgt_pos - cos_l0 - sin_hf_width;
    rear_left.y = lat_pos - sin_l0 + cos_hf_width;

    front_right.x = lgt_pos + cos_l0 + sin_hf_width;
    front_right.y = lat_pos + sin_l0 - cos_hf_width;

    front_left.x = lgt_pos + cos_l0 - sin_hf_width;
    front_left.y = lat_pos + sin_l0 + cos_hf_width;
    if (cos_hdg > 0.0F) {
        // heading ∈ (-pi/2, pi/2)
        // near
        edges[0].p0 = rear_right;
        edges[0].p1 = rear_left;
        // left
        edges[1].p0 = rear_left;
        edges[1].p1 = front_left;
        // right
        edges[2].p0 = rear_right;
        edges[2].p1 = front_right;
    } else {
        // near
        edges[0].p0 = front_right;
        edges[0].p1 = front_left;
        // left
        edges[1].p0 = front_left;
        edges[1].p1 = rear_left;
        // right
        edges[2].p0 = front_right;
        edges[2].p1 = rear_right;
    }

    return edges;
}

void ThreatAssessor::EstimateObjectPosInpath(float offs_lat_inpath_primary_target, float offs_lgt_short_pred) {
    float half_host_width = host_data_.width * 0.5F + offs_lat_inpath_primary_target;
    // CoG pos for the object ,here equal half object length.
    float host_lat_accel = host_data_.v0 * host_data_.v0 * host_data_.c0;

    bool host_in_curve = fabsf(host_lat_accel) > 0.1F;

    for (int i = 0; i < LTAP_TIME_NUM; ++i) {
        const std::array<LtapEdge, 3> &edge = LtapGetLongClosestEdge(obj_pred_lgt_pos_[i], obj_pred_lat_pos_[i], obj_pred_heading_[i]);

        std::array<LtapLongDistInfo, 3> edge_dist;
        for (int m = 0; m < 3; m++) {
            // iterator three edges which are near/left/right edge.
            const LtapEdge &e = edge[m];

            if (!host_in_curve) {
                edge_dist[m] = CalcHostStraightLongDist(e, half_host_width, host_data_.d0 - host_data_.length);
            } else {
                edge_dist[m] = CalcHostCurveLongDist(e, half_host_width);
            }
        }
        obj_dist_near_[i] = 200.0F;
        obj_dist_far_[i] = -100.0F;
        for (const LtapLongDistInfo &dist : edge_dist) {
            // 判断是否为有效值：dist_near 不应该大于 199.0F，dist_far 不应该小于 -99.0F
            if ((dist.dist_near <= 199.0F)  &&  (dist.dist_far >= -99.0F)) {
                obj_dist_near_[i] = fminf(obj_dist_near_[i], dist.dist_near);
                obj_dist_far_[i] = fmaxf(obj_dist_far_[i], dist.dist_far);
            }
        }
        if ((obj_dist_near_[i] > 199.0F)  ||  (obj_dist_far_[i] < -99.0F)) {
            obj_inpath_[i] = false;
            obj_dist_near_[i] = obj_dist_near_[i] - offs_lgt_short_pred;
        } else {
            obj_inpath_[i] = true;
            obj_dist_near_[i] = obj_dist_near_[i] - offs_lgt_short_pred;
            obj_dist_far_[i] = fminf(200.0F, obj_dist_far_[i] + threat_ass_cal_.k_ltap_add_dist_aposlgt + offs_lgt_short_pred);
        }
    }
}

LtapLongDistInfo ThreatAssessor::CalcHostStraightLongDist(const LtapEdge &edge, float half_host_width, float host_rear_bump_dist) {
    LtapLongDistInfo long_dist;

    float min_y = fminf(edge.p0.y, edge.p1.y);
    float max_y = fmaxf(edge.p0.y, edge.p1.y);
    float max_x = fmaxf(edge.p0.x, edge.p1.x);

    long_dist.dist_far = -100.F;
    long_dist.dist_near = 200.F;

    if ((min_y < half_host_width)  &&  (max_y > -half_host_width)  &&  (max_x > host_rear_bump_dist)) {
        if ((max_y < half_host_width && min_y > -half_host_width)  ||  (fabsf(edge.p0.y - edge.p1.y) < 0.05F)  ||  (fabsf(edge.p0.x - edge.p1.x) < 0.05F)) {
            // Check if the entire edge is in path, or the edge is parallel or perpendicular to the host vehicle.
            // Update the temporary variables for close and far critical point, using the corner positions
            long_dist.dist_near = fminf(edge.p0.x, edge.p1.x);
            long_dist.dist_far = max_x;
        } else {
            // Only a part of the edge is in path.
            // Find the leftmost and rightmost point of the edge that is in path.
            float left_y_edge = fminf(max_y, half_host_width);
            float right_y_edge = fmaxf(min_y, -half_host_width);

            float left_x_edge, right_x_edge;
            float dx = edge.p1.x - edge.p0.x;
            float dy = edge.p1.y - edge.p0.y;
            if (fabsf(edge.p0.y - edge.p1.y) > 0.05F) {
                left_x_edge = edge.p0.x + math::SafeDivide(dx * (left_y_edge - edge.p0.y), (edge.p1.y - edge.p0.y));
                right_x_edge = edge.p0.x + math::SafeDivide(dx * (right_y_edge - edge.p0.y), (edge.p1.y -edge.p0.y));
            } else {
                left_x_edge = fmaxf(edge.p0.x, host_rear_bump_dist);
                right_x_edge = fmaxf(edge.p1.x, host_rear_bump_dist);
            }

            long_dist.dist_near = fminf(left_x_edge, right_x_edge);
            long_dist.dist_far = fmaxf(left_x_edge, right_x_edge);
        }
    }
    return long_dist;
}

LtapLongDistInfo ThreatAssessor::CalcHostCurveLongDist(const LtapEdge &edge, float half_host_width) {
    LtapLongDistInfo long_dist;
    long_dist.dist_far = -100.F;
    long_dist.dist_near = 200.F;

    float host_radius = math::SafeDivide(1.0, host_data_.c0);
    float squard_d = host_data_.d0 * host_data_.d0;
    float left_sqrd_radius = (host_radius - half_host_width) * (host_radius - half_host_width) + squard_d;
    float right_sqrd_radius = (host_radius + half_host_width) * (host_radius + half_host_width) + squard_d;
    float left_radius = math::SignF(host_radius) * sqrtf(left_sqrd_radius);
    float right_radius = math::SignF(host_radius) * sqrtf(right_sqrd_radius);
    float center_radius = math::SignF(host_radius) * sqrtf(host_radius * host_radius + squard_d);

    Point2D center{0.0F, host_radius};

    float quarter_host_radius = m_pi * fabs(host_radius) * 0.5F;

    std::vector<Intersection> inter_secs;
    //判断边和圆弧是否有交点
    std::vector<Intersection> seg_left_cir_inter = Geometry::IntersectSegmentCircle(edge.p0, edge.p1, fabsf(left_radius), center);
    for (auto &it : seg_left_cir_inter) {
        // 修正 arc_length：使用与 LtapLongDistForEndInPath 一致的计算方式
        // 使用中心路径半径计算弧长，与 LtapLongDistForEndInPath 保持一致
        float radius_for_arc = fmaxf(fabsf(center_radius), 1.0F);
        it.arc_length = radius_for_arc * math::SignF(it.point.x) * asinf(fminf(math::SafeDivide(it.point.x, radius_for_arc), 1.0F));
        if ((it.arc_length > quarter_host_radius)  ||  (it.point.x < host_data_.d0 - host_data_.length)) {
            continue;
        }
        inter_secs.push_back(it);
    }

    std::vector<Intersection> seg_right_cir_inter = Geometry::IntersectSegmentCircle(edge.p0, edge.p1, fabsf(right_radius), center);
    for (auto &it : seg_right_cir_inter) {
        // 修正 arc_length：使用与 LtapLongDistForEndInPath 一致的计算方式
        float radius_for_arc = fmaxf(fabsf(center_radius), 1.0F);
        it.arc_length = radius_for_arc * math::SignF(it.point.x) * asinf(fminf(math::SafeDivide(it.point.x, radius_for_arc), 1.0F));
        if ((it.arc_length > quarter_host_radius)  ||  (it.point.x < host_data_.d0 - host_data_.length)) {
            continue;
        }
        inter_secs.push_back(it);
    }
    // 判断边和圆环的关系：端点若在圆环内，则也视作“有效交点”，并带有对应弧长
    Intersection end;
    bool end_inpath =
        LtapLongDistForEndInPath(edge.p0, host_data_.d0 - host_data_.length, left_radius, right_radius, center_radius, host_radius, end);
    if (end_inpath && (end.arc_length <= quarter_host_radius && end.point.x >= host_data_.d0 - host_data_.length)) {
        inter_secs.push_back(end);
    }
    end_inpath = LtapLongDistForEndInPath(edge.p1, host_data_.d0 - host_data_.length, left_radius, right_radius, center_radius, host_radius, end);
    if (end_inpath && (end.arc_length <= quarter_host_radius && end.point.x >= host_data_.d0 - host_data_.length)) {
        inter_secs.push_back(end);
    }

    // 找出 inter_secs 中 pt.x 最小/最大的点，对应的 arc_length 作为本条边的近端/远端距离
    if (!inter_secs.empty()) {
        float min_x = inter_secs[0].point.x;
        float max_x = inter_secs[0].point.x;
        float near_arc = inter_secs[0].arc_length;
        float far_arc = inter_secs[0].arc_length;

        for (const auto &it : inter_secs) {
            if (it.point.x < min_x) {
                min_x = it.point.x;
                near_arc = it.arc_length;
            }
            if (it.point.x > max_x) {
                max_x = it.point.x;
                far_arc = it.arc_length;
            }
        }
        long_dist.dist_near = near_arc;
        long_dist.dist_far = far_arc;
    } else {
        long_dist.dist_near = 200.0F;
        long_dist.dist_far = -100.0F;
    }
    return long_dist;
}

bool ThreatAssessor::LtapLongDistForEndInPath(const Point2D &pt, float host_rear_bump_dist, float left_radius, float right_radius,
                                              float center_radius, float host_raduis, Intersection &inter_sec) {
    if ((pt.x > host_rear_bump_dist)  &&  (fabsf(pt.y) < fmaxf(fabsf(left_radius), fabsf(right_radius)))) {
        float dy = pt.y - host_raduis;
        float r_edge = pt.x * pt.x + dy * dy;
        float left_r = left_radius * left_radius;
        float right_r = right_radius * right_radius;
        if ((r_edge > fminf(left_r, right_r))  &&  (r_edge < fmaxf(left_r, right_r))) {
            inter_sec.point = pt;
            float radius = fmaxf(fabsf(center_radius), 1.0F);
            inter_sec.arc_length = radius * math::SignF(pt.x) * asinf(fminf(math::SafeDivide(pt.x, radius), 1.0F));
            return true;
        }
    }
    return false;
}

void ThreatAssessor::LtapThreatAssessLongitudinal() {

    float half_accel = host_data_.a0 * 0.5;

    for (int i = 0; i < LTAP_TIME_NUM; ++i) {
        float pred_time = LTAP_TIME_STEP * static_cast<float>(i);

        float tj = fminf(host_data_.tj_brake, pred_time);
        float tj_squard = tj * tj;

        float const_acc_time = pred_time - tj;

        float dist_pre = host_data_.v0 * tj + half_accel * tj * tj + const_acc_time * (host_data_.v0 + host_data_.a0 * tj) +
            host_data_.a0 * const_acc_time * const_acc_time * 0.5F;

        float den = tj_squard * tj * 0.166667F + const_acc_time * tj * tj * 0.5F + tj * const_acc_time * const_acc_time * 0.5F;

        obj_lgt_jerk_[i] = math::SafeDivide(obj_dist_near_[i] - dist_pre, den);
    }

    float min_jerk = obj_lgt_jerk_[0];
    int min_jerk_index = -1;

    for (int i = 1; i < LTAP_TIME_NUM; ++i) {
        if (obj_inpath_[i]) {
            min_jerk = fmin(min_jerk, obj_lgt_jerk_[i]);
            min_jerk_index = i;
        }
    }

    if (min_jerk_index >= 0) {
        rqrd_neg_lgt_jerk_ = min_jerk;
        rqrd_neg_lgt_accel_ = host_data_.a0 + min_jerk * host_data_.tj_brake;
    } else {
        rqrd_neg_lgt_jerk_ = 0.0F;
        rqrd_neg_lgt_accel_ = 0.0F;
    }
}

void ThreatAssessor::LtapThreatAssessLateral(const LongSafeObject &obs, const AsCurvaturePath &ego_path) {
    float length = 2.0F * obj_data_.offs_lat + obj_data_.length;
    float l0 = obj_data_.offs_lat + obj_data_.l0;
    float width = 2.0F * obj_data_.offs_lat + obj_data_.width;
    float v0_pow2 = host_data_.v0 * host_data_.v0;
    float half_width = 0.5F * width;
    float ttr = obs.ttr;

    for (int i = 0; i < LTAP_TTI_AROUND_TIME_NUM; ++i) {
        float pred_time = ttr + threat_ass_cal_.k_ltap_tti_around_offset[i];
        host_state_ = ego_path.GetHostState(pred_time);
        int i1 = pred_time / LTAP_TIME_STEP;
        if (i1 >= LTAP_TIME_NUM - 1) {
            continue;
        }
        float factor = fmod(pred_time, LTAP_TIME_STEP);
        // ltap_tti_around_offset间隔均在20ms 只需计算i1j即可
        float lgt_pos = obj_pred_lgt_pos_[i1] + (obj_pred_lgt_pos_[i1 + 1] - obj_pred_lgt_pos_[i1]) * factor;
        float lat_pos = obj_pred_lat_pos_[i1] + (obj_pred_lat_pos_[i1 + 1] - obj_pred_lat_pos_[i1]) * factor;
        float heading = obj_pred_heading_[i1] + (obj_pred_heading_[i1 + 1] - obj_pred_heading_[i1]) * factor;

        LtapFindLatClosestEdges(lgt_pos, lat_pos, heading, (length - l0), width, i, host_state_);

        for (const LtapEdge &e : obj_edges_[i]) {
            float host_dist_pred = host_data_.v0 * pred_time + 0.5F * host_data_.a0 * pred_time * pred_time;
            if (fminf(e.p0.x, e.p1.x) < host_dist_pred + host_data_.d0 &&
                fmaxf(e.p0.x, e.p1.x) > host_dist_pred + host_data_.d0 - host_data_.length) {
                float d_min = -0.3F * host_data_.v0 * pred_time;

                float xp = fminf(host_dist_pred + host_data_.d0, fmaxf(e.p0.x, e.p1.x));
                float dp = fmaxf(d_min, xp - host_dist_pred);

                float xm = fminf(e.p0.x, e.p1.x);
                float dm = fmaxf(d_min, xm - host_dist_pred);

                float dp_v0_product = dp * host_data_.v0;
                float dm_v0_product = dm * host_data_.v0;

                float yp = e.p0.y;
                float ym = e.p1.y;
                if (fabsf(e.p0.x - e.p1.x) > 0.01F) {
                    yp = e.p0.y + (e.p1.y - e.p0.y) * (xp - e.p0.x) / (e.p1.x - e.p0.x);
                    ym = e.p1.y + (e.p0.y - e.p1.y) * (xm - e.p1.x) / (e.p0.x - e.p1.x);
                }

                float time_pow_div_2 = pred_time * pred_time * 0.5F;

                float c = v0_pow2 * time_pow_div_2;

                float fp = host_data_.c0 * (c + dp_v0_product * pred_time);
                float fm = host_data_.c0 * (c + dm_v0_product * pred_time);

                // Calc Left
                float time_l = fminf(host_data_.ttheta_left, pred_time);

                float ti_minus_multi_theta_left = (pred_time - time_l) * host_data_.ttheta_left;

                float term_a = v0_pow2 * (time_l * time_l * time_l / 6.0F + pred_time * ti_minus_multi_theta_left * 0.5F);
                float term_b = time_l * time_l * 0.5F + ti_minus_multi_theta_left;

                float Gp_l = term_a + dp_v0_product * term_b;
                float c1_left_p = math::SafeDivide(yp + half_width - fp, Gp_l);

                float Gm_l = term_a + dm_v0_product * term_b;
                float c1_left_m = math::SafeDivide(ym + half_width - fm, Gm_l);

                float c1_left = fmaxf(c1_left_p, c1_left_m);
                float c0_left = host_data_.c0 + time_l * c1_left;
                rqrd_left_crvt_ = fmaxf(rqrd_left_crvt_, c0_left);
                rqrd_left_crvt_rate_ = fmaxf(rqrd_left_crvt_rate_, c1_left);

                // Calc Right
                float time_r = fmaxf(host_data_.ttheta_right, pred_time);

                float ti_minus_multi_theta_right = (pred_time - time_r) * host_data_.ttheta_right;

                term_a = v0_pow2 * (time_r * time_r * time_r / 6.0F + pred_time * ti_minus_multi_theta_right * 0.5F);
                term_b = time_r * time_r * 0.5F + ti_minus_multi_theta_right;

                float Gp_r = term_a + dp_v0_product * term_b;
                float c1_right_p = math::SafeDivide(yp - half_width - fp, Gp_r);

                float Gm_r = term_a + dm_v0_product * term_b;
                float c1_right_m = 100000.0F;
                if (fabsf(Gm_r) > 0.001F) {
                    c1_right_m = math::SafeDivide(ym - half_width - fm, Gm_r);
                }

                float c1_right = fminf(c1_right_p, c1_right_m);
                float c0_right = host_data_.c0 + time_r * c1_right;
                rqrd_right_crvt_ = fminf(rqrd_right_crvt_, c0_right);
                rqrd_right_crvt_rate_ = fminf(rqrd_right_crvt_rate_, c1_right);
            }
        }
    }
}

void ThreatAssessor::CalcTimeToBrake(float host_spd, float host_accel, float tgt_spd, float tgt_accel, float desired_hit_spd) {
    float obs_stop_time = math::Clamp(math::SafeDivide(tgt_spd, fabs(tgt_accel)), 0.0F, 25.5F);
    if (tgt_accel > 0.1F) {
        obs_stop_time = 25.5F;
    }

    if (host_spd < threat_ass_cal_.k_high_brk_spd_thres) {
        //低速时，只考虑全制动风险距离.
        brk_low_delay_time_ = 0.0F;
        brk_low_during_time_ = 0.0F;
        brk_high_delay_time_ = 0.0F;
        brk_high_during_time_ = 0.0F;
        //考虑在delay时间时是否会进入同速情况.
        float const_jerk_2_full_time = CalcMinDecelTimeWithConstJerk(tgt_spd, host_spd, host_accel, threat_ass_cal_.k_max_jerk);

        brk_full_delay_time_ = math::LookUpTable::LookupTable1D<13>(threat_ass_cal_.k_decel_diff_x, threat_ass_cal_.k_esp_settime_y,
                                                                    threat_ass_cal_.k_fullbrk_req_accel - host_accel);
        brk_full_delay_time_ = fmin(brk_full_delay_time_, const_jerk_2_full_time);
        float full_brk_delay_time_sqrd = brk_full_delay_time_ * brk_full_delay_time_;
        float host_pred_spd = host_spd + host_accel * brk_full_delay_time_ + 0.5F * threat_ass_cal_.k_max_jerk * full_brk_delay_time_sqrd;
        float target_pred_spd = fmax(tgt_spd + tgt_accel * brk_full_delay_time_, 0.0F);

        float chassis_resp_decel = threat_ass_cal_.k_fullbrk_req_accel + threat_ass_cal_.k_fullbrk_req_accel_offs;
        if (host_pred_spd <= 0.0F) {
            brk_full_during_time_ = 0.0F;
        } else {
            brk_full_during_time_ = fmax(math::SafeDivide(target_pred_spd - host_pred_spd, chassis_resp_decel - tgt_accel), 0.0F);
            if (brk_full_during_time_ + brk_full_delay_time_ > obs_stop_time) {
                //目标在到达时间前已经停止，重新计算
                brk_full_during_time_ = math::SafeDivide(host_pred_spd, fabs(chassis_resp_decel));
            }
            if (brk_full_during_time_ * chassis_resp_decel + host_pred_spd < desired_hit_spd) {
                //根据碰撞速度限制时间
                brk_full_during_time_ = fmax(math::SafeDivide(host_pred_spd - desired_hit_spd, fabs(chassis_resp_decel)), 0.0F);
            }
        }
        float host_travel_dist_delay_time = host_spd * brk_full_delay_time_ + 0.5F * host_accel * full_brk_delay_time_sqrd +
            0.16667F * threat_ass_cal_.k_max_jerk * full_brk_delay_time_sqrd * brk_full_delay_time_;
        float host_travel_dist_duing_time =
            host_pred_spd * brk_full_during_time_ + 0.5F * chassis_resp_decel * brk_full_during_time_ * brk_full_during_time_;

        threat_range_ = host_travel_dist_delay_time + host_travel_dist_duing_time;
        threat_range_ = math::Clamp(threat_range_, 0.0F, 150.0F);
        return;
    }
    if (host_spd < threat_ass_cal_.k_low_brk_spd_thres) {
        //中速情况下，考虑 0.8g->1.0g or 1.2g的变化情况，其中可忽略0.8->1.0 or 1.2的delay值
        brk_low_delay_time_ = 0.0F;
        brk_low_during_time_ = 0.0F;
        float const_jerk_time_2_high_time = CalcMinDecelTimeWithConstJerk(tgt_spd, host_spd, host_accel, threat_ass_cal_.k_max_jerk);

        brk_high_delay_time_ = math::LookUpTable::LookupTable1D<13>(threat_ass_cal_.k_decel_diff_x, threat_ass_cal_.k_esp_settime_y,
                                                                    threat_ass_cal_.k_highbrk_req_accel - host_accel);

        brk_high_delay_time_ = fmin(brk_high_delay_time_, const_jerk_time_2_high_time);

        float high_brk_delay_time_sqrd = brk_high_delay_time_ * brk_high_delay_time_;

        float host_pred_spd = host_spd + host_accel * brk_high_delay_time_ + 0.5F * threat_ass_cal_.k_max_jerk * high_brk_delay_time_sqrd;
        if (host_pred_spd <= 0.0F) {
            //自车CJ过程中已经刹停，可能性不大,但先考虑着.
            brk_high_during_time_ = 0.0F;
            brk_full_delay_time_ = 0.0F;
            brk_full_during_time_ = 0.0F;
            float tp, tm;
            math::SolveQuadratic(0.5 * threat_ass_cal_.k_max_jerk, host_accel, host_spd, tp, tm);
            tp = fmax(0.0F, fmaxf(tp, tm));

            float tp_sqrd = tp * tp;
            float host_travel_dist = host_spd * tp + 0.5F * host_accel * tp_sqrd + 0.16667F * threat_ass_cal_.k_max_jerk * tp_sqrd * tp;

            threat_range_ = host_travel_dist;
            threat_range_ = math::Clamp(threat_range_, 0.0F, 150.0F);
            return;
        }
        float target_pred_spd = fmax(tgt_spd + tgt_accel * brk_high_delay_time_, 0.0F);
        float chassis_resp_decel_high = threat_ass_cal_.k_highbrk_req_accel + threat_ass_cal_.k_highbrk_req_accel_offs;
        float tm_decel_2_same_spd = math::Clamp(math::SafeDivide(host_pred_spd - target_pred_spd, tgt_accel - chassis_resp_decel_high), 0.0F, 25.5F);
        float pred_spd_same_spd = host_pred_spd + chassis_resp_decel_high * tm_decel_2_same_spd;

        float host_dist_high_dly = host_spd * brk_high_delay_time_ + 0.5F * host_accel * brk_high_delay_time_ * brk_high_delay_time_ +
            0.16667F * threat_ass_cal_.k_max_jerk * brk_high_delay_time_ * brk_high_delay_time_ * brk_high_delay_time_;

        if (pred_spd_same_spd > threat_ass_cal_.k_high_brk_spd_thres) {
            //如果目标加速，且在自车制动过程中超过HeavySpd,则不需要全力制动.
            brk_high_during_time_ = tm_decel_2_same_spd;
            brk_full_delay_time_ = 0.0F;
            brk_full_during_time_ = 0.0F;
            if (host_pred_spd + chassis_resp_decel_high * brk_high_during_time_ < desired_hit_spd) {
                //根据碰撞速度限制时间
                brk_high_during_time_ = fmax(math::SafeDivide(host_pred_spd - desired_hit_spd, fabs(chassis_resp_decel_high)), 0.0F);
            }
            float host_dist_high_during =
                host_pred_spd * brk_high_during_time_ + 0.5F * chassis_resp_decel_high * brk_high_during_time_ * brk_high_during_time_;
            threat_range_ = host_dist_high_dly + host_dist_high_during;
            threat_range_ = math::Clamp(threat_range_, 0.0F, 150.0F);
            return;
        }
        //仍需要全力制动
        brk_high_during_time_ =
            math::Clamp(math::SafeDivide(host_pred_spd - threat_ass_cal_.k_high_brk_spd_thres, fabs(chassis_resp_decel_high)), 0.0F, 25.5F);
        brk_full_delay_time_ = 0.0F;

        // 高制动结束后的速度
        float host_spd_after_high = threat_ass_cal_.k_high_brk_spd_thres;
        float chassis_resp_decel_full = threat_ass_cal_.k_fullbrk_req_accel + threat_ass_cal_.k_fullbrk_req_accel_offs;

        if (host_pred_spd + chassis_resp_decel_high * brk_high_during_time_ < desired_hit_spd) {
            brk_high_during_time_ = fmax(math::SafeDivide(host_pred_spd - desired_hit_spd, fabs(chassis_resp_decel_high)), 0.0F);
            brk_full_during_time_ = 0.0F;
        } else {
            target_pred_spd = fmax(target_pred_spd + tgt_accel * (brk_high_during_time_ + brk_high_delay_time_), 0.0F);
            brk_full_during_time_ = fmax(0.0F, math::SafeDivide(host_spd_after_high - target_pred_spd, tgt_accel - chassis_resp_decel_full));
            if (brk_high_delay_time_ + brk_high_during_time_ + brk_full_delay_time_ + brk_full_during_time_ > obs_stop_time) {
                brk_full_during_time_ = math::SafeDivide(host_spd_after_high, fabs(chassis_resp_decel_full));
            }
            if (host_spd_after_high + chassis_resp_decel_full * brk_full_during_time_ < desired_hit_spd) {
                //根据碰撞速度限制时间
                brk_full_during_time_ = fmax(math::SafeDivide(host_spd_after_high - desired_hit_spd, fabs(chassis_resp_decel_full)), 0.0F);
            }
        }

        float host_dist_high_during =
            host_pred_spd * brk_high_during_time_ + 0.5F * chassis_resp_decel_high * brk_high_during_time_ * brk_high_during_time_;
        float host_dist_full_during =
            host_spd_after_high * brk_full_during_time_ + 0.5F * chassis_resp_decel_full * brk_full_during_time_ * brk_full_during_time_;

        threat_range_ = host_dist_high_dly + host_dist_high_during + host_dist_full_during;
        threat_range_ = math::Clamp(threat_range_, 0.0F, 150.0F);
        return;
    }
    //计算三阶制动所需的距离（高速情况：低制动 -> 高制动 -> 全制动）
    // 第一阶段：低制动（从当前速度减速到 k_low_brk_spd_thres）
    float const_jerk_time_2_low_time =
        CalcMinDecelTimeWithConstJerk(threat_ass_cal_.k_low_brk_spd_thres, host_spd, host_accel, threat_ass_cal_.k_max_jerk);

    brk_low_delay_time_ = math::LookUpTable::LookupTable1D<13>(threat_ass_cal_.k_decel_diff_x, threat_ass_cal_.k_esp_settime_y,
                                                               threat_ass_cal_.k_lowbrk_req_accel - host_accel);
    brk_low_delay_time_ = fmin(brk_low_delay_time_, const_jerk_time_2_low_time);

    float low_brk_delay_time_sqrd = brk_low_delay_time_ * brk_low_delay_time_;
    float host_pred_spd_low = host_spd + host_accel * brk_low_delay_time_ + 0.5F * threat_ass_cal_.k_max_jerk * low_brk_delay_time_sqrd;

    if (host_pred_spd_low <= 0.0F) {
        // 自车在低制动 jerk 过程中已经刹停
        brk_low_during_time_ = 0.0F;
        brk_high_delay_time_ = 0.0F;
        brk_high_during_time_ = 0.0F;
        brk_full_delay_time_ = 0.0F;
        brk_full_during_time_ = 0.0F;
        float tp, tm;
        math::SolveQuadratic(0.5F * threat_ass_cal_.k_max_jerk, host_accel, host_spd, tp, tm);
        tp = fmax(0.0F, fmaxf(tp, tm));
        float tp_sqrd = tp * tp;
        threat_range_ = host_spd * tp + 0.5F * host_accel * tp_sqrd + 0.16667F * threat_ass_cal_.k_max_jerk * tp_sqrd * tp;
        threat_range_ = math::Clamp(threat_range_, 0.0F, 150.0F);
        return;
    }

    float chassis_resp_decel_low = threat_ass_cal_.k_lowbrk_req_accel + threat_ass_cal_.k_lowbrk_req_accel_offs;
    brk_low_during_time_ =
        math::Clamp(math::SafeDivide(host_pred_spd_low - threat_ass_cal_.k_low_brk_spd_thres, fabs(chassis_resp_decel_low)), 0.0F, 25.5F);

    // 第二阶段：高制动（从 k_low_brk_spd_thres 减速到 k_high_brk_spd_thres）
    float host_spd_after_low = threat_ass_cal_.k_low_brk_spd_thres;
    float const_jerk_time_2_high_time =
        CalcMinDecelTimeWithConstJerk(threat_ass_cal_.k_high_brk_spd_thres, host_spd_after_low, chassis_resp_decel_low, threat_ass_cal_.k_max_jerk);

    brk_high_delay_time_ = math::LookUpTable::LookupTable1D<13>(threat_ass_cal_.k_decel_diff_x, threat_ass_cal_.k_esp_settime_y,
                                                                threat_ass_cal_.k_highbrk_req_accel - chassis_resp_decel_low);
    brk_high_delay_time_ = fmin(brk_high_delay_time_, const_jerk_time_2_high_time);

    float high_brk_delay_time_sqrd = brk_high_delay_time_ * brk_high_delay_time_;
    float host_pred_spd_high =
        host_spd_after_low + chassis_resp_decel_low * brk_high_delay_time_ + 0.5F * threat_ass_cal_.k_max_jerk * high_brk_delay_time_sqrd;

    if (host_pred_spd_high <= 0.0F) {
        // 自车在高制动 jerk 过程中已经刹停
        brk_high_during_time_ = 0.0F;
        brk_full_delay_time_ = 0.0F;
        brk_full_during_time_ = 0.0F;
        // 计算总距离
        float host_dist_low_delay = host_spd * brk_low_delay_time_ + 0.5F * host_accel * low_brk_delay_time_sqrd +
            0.16667F * threat_ass_cal_.k_max_jerk * low_brk_delay_time_sqrd * brk_low_delay_time_;
        float host_dist_low_during =
            host_pred_spd_low * brk_low_during_time_ + 0.5F * chassis_resp_decel_low * brk_low_during_time_ * brk_low_during_time_;
        threat_range_ = host_dist_low_delay + host_dist_low_during;
        threat_range_ = math::Clamp(threat_range_, 0.0F, 150.0F);
        return;
    }

    float chassis_resp_decel_high = threat_ass_cal_.k_highbrk_req_accel + threat_ass_cal_.k_highbrk_req_accel_offs;
    float target_pred_spd_high = fmax(tgt_spd + tgt_accel * (brk_low_delay_time_ + brk_low_during_time_ + brk_high_delay_time_), 0.0F);
    float tm_decel_2_same_spd_high =
        math::Clamp(math::SafeDivide(host_pred_spd_high - target_pred_spd_high, tgt_accel - chassis_resp_decel_high), 0.0F, 25.5F);
    float pred_spd_same_spd_high = host_pred_spd_high + chassis_resp_decel_high * tm_decel_2_same_spd_high;

    if (pred_spd_same_spd_high > threat_ass_cal_.k_high_brk_spd_thres) {
        // 如果目标加速，且在自车高制动过程中超过 k_high_brk_spd_thres，则不需要全制动
        brk_high_during_time_ = tm_decel_2_same_spd_high;
        brk_full_delay_time_ = 0.0F;
        brk_full_during_time_ = 0.0F;
        if (host_pred_spd_high + chassis_resp_decel_high * brk_high_during_time_ < desired_hit_spd) {
            // 根据碰撞速度限制时间
            brk_high_during_time_ = fmax(math::SafeDivide(host_pred_spd_high - desired_hit_spd, fabs(chassis_resp_decel_high)), 0.0F);
        }
        // 计算总距离
        float host_dist_low_delay = host_spd * brk_low_delay_time_ + 0.5F * host_accel * low_brk_delay_time_sqrd +
            0.16667F * threat_ass_cal_.k_max_jerk * low_brk_delay_time_sqrd * brk_low_delay_time_;
        float host_dist_low_during =
            host_pred_spd_low * brk_low_during_time_ + 0.5F * chassis_resp_decel_low * brk_low_during_time_ * brk_low_during_time_;
        float host_dist_high_delay = host_spd_after_low * brk_high_delay_time_ + 0.5F * chassis_resp_decel_low * high_brk_delay_time_sqrd +
            0.16667F * threat_ass_cal_.k_max_jerk * high_brk_delay_time_sqrd * brk_high_delay_time_;
        float host_dist_high_during =
            host_pred_spd_high * brk_high_during_time_ + 0.5F * chassis_resp_decel_high * brk_high_during_time_ * brk_high_during_time_;
        threat_range_ = host_dist_low_delay + host_dist_low_during + host_dist_high_delay + host_dist_high_during;
        threat_range_ = math::Clamp(threat_range_, 0.0F, 150.0F);
        return;
    }

    // 仍需要全制动
    brk_high_during_time_ =
        math::Clamp(math::SafeDivide(host_pred_spd_high - threat_ass_cal_.k_high_brk_spd_thres, fabs(chassis_resp_decel_high)), 0.0F, 25.5F);
    brk_full_delay_time_ = 0.0F;

    // 第三阶段：全制动（从 k_high_brk_spd_thres 减速到 desired_hit_spd 或停止）
    float host_spd_after_high = threat_ass_cal_.k_high_brk_spd_thres;
    float target_pred_spd_full = fmax(target_pred_spd_high + tgt_accel * brk_high_during_time_, 0.0F);
    float chassis_resp_decel_full = threat_ass_cal_.k_fullbrk_req_accel + threat_ass_cal_.k_fullbrk_req_accel_offs;

    if (host_pred_spd_high + chassis_resp_decel_high * brk_high_during_time_ < desired_hit_spd) {
        // 高制动阶段已经达到 desired_hit_spd，不需要全制动
        brk_high_during_time_ = fmax(math::SafeDivide(host_pred_spd_high - desired_hit_spd, fabs(chassis_resp_decel_high)), 0.0F);
        brk_full_during_time_ = 0.0F;
    } else {
        brk_full_during_time_ = fmax(0.0F, math::SafeDivide(host_spd_after_high - target_pred_spd_full, tgt_accel - chassis_resp_decel_full));

        // 检查目标是否在到达时间前停止
        float total_time =
            brk_low_delay_time_ + brk_low_during_time_ + brk_high_delay_time_ + brk_high_during_time_ + brk_full_delay_time_ + brk_full_during_time_;
        if (total_time > obs_stop_time) {
            // 目标在到达时间前已经停止，重新计算全制动时间
            brk_full_during_time_ = math::SafeDivide(host_spd_after_high, fabs(chassis_resp_decel_full));
        }

        // 检查是否达到 desired_hit_spd
        if (host_spd_after_high + chassis_resp_decel_full * brk_full_during_time_ < desired_hit_spd) {
            // 根据碰撞速度限制时间
            brk_full_during_time_ = fmax(math::SafeDivide(host_spd_after_high - desired_hit_spd, fabs(chassis_resp_decel_full)), 0.0F);
        }
    }

    // 计算各阶段的行驶距离
    float host_dist_low_delay = host_spd * brk_low_delay_time_ + 0.5F * host_accel * low_brk_delay_time_sqrd +
        0.16667F * threat_ass_cal_.k_max_jerk * low_brk_delay_time_sqrd * brk_low_delay_time_;
    float host_dist_low_during =
        host_pred_spd_low * brk_low_during_time_ + 0.5F * chassis_resp_decel_low * brk_low_during_time_ * brk_low_during_time_;
    float host_dist_high_delay = host_spd_after_low * brk_high_delay_time_ + 0.5F * chassis_resp_decel_low * high_brk_delay_time_sqrd +
        0.16667F * threat_ass_cal_.k_max_jerk * high_brk_delay_time_sqrd * brk_high_delay_time_;
    float host_dist_high_during =
        host_pred_spd_high * brk_high_during_time_ + 0.5F * chassis_resp_decel_high * brk_high_during_time_ * brk_high_during_time_;
    float host_dist_full_during =
        host_spd_after_high * brk_full_during_time_ + 0.5F * chassis_resp_decel_full * brk_full_during_time_ * brk_full_during_time_;

    threat_range_ = host_dist_low_delay + host_dist_low_during + host_dist_high_delay + host_dist_high_during + host_dist_full_during;
    threat_range_ = math::Clamp(threat_range_, 0.0F, 150.0F);
}

float ThreatAssessor::CalcObsTTBTravelBeforeStop(float tgt_spd, float tgt_accel) {
    float final_ttb =
        brk_low_delay_time_ + brk_low_during_time_ + brk_high_delay_time_ + brk_high_during_time_ + brk_full_delay_time_ + brk_full_during_time_;
    final_ttb = math::Clamp(final_ttb, 0.0, 25.5F);
    if (tgt_accel <= 1.0F) {
        final_ttb = fmin(final_ttb, math::Clamp(math::SafeDivide(tgt_spd, fabs(tgt_accel)), 0.0F, 25.5F));
    }
    return tgt_spd * final_ttb + 0.5F * tgt_accel * final_ttb * final_ttb;
}

float ThreatAssessor::CalcMinDecelTimeWithConstJerk(float desired_spd, float host_spd, float host_accel, float jerk) {
    if (fabs(jerk) < 0.001F) {
        return fminf(10.0F, fabs(math::SafeDivide(host_spd, host_accel)));
    }
    float delta = host_accel * host_accel - 2.0F * jerk * (host_spd - desired_spd);
    if (delta < 0.0F) {
        return 0.0F;
    }
    float tp = math::SafeDivide(sqrtf(delta) - host_accel, jerk);
    float tm = math::SafeDivide(-sqrtf(delta) - host_accel, jerk);
    if ((tp >= 0.0F)  &&  (tm >= 0.0F)) {
        return fmin(tp, tm);
    } else if (math::SignF(tp) * math::SignF(tm) < 0.0F) {
        return fmax(tp, tm);
    } else {
        return 0.0F;
    }
}

void ThreatAssessor::CalcFcwTtcByDist(const AsVseOut &vse_out, const LongSafeObject &obs) {
    float rel_long_vel = obs.long_vel - vse_out.vcs_long_vel;
    float rel_long_acc = obs.long_accel - vse_out.long_accel;
    float rel_range =
        obs.long_posn - vse_out.config.k_dist_to_rear_axle - cosf(obs.heading) * 0.5F * obs.length - sinf(obs.heading) * 0.5F * obs.width;
    if (fabsf(rel_long_acc) <= 0.2F) {
        // CV
        if (rel_long_vel >= 0) {
            fcw_ttc = 30.0F;
        } else {
            fcw_ttc = math::SafeDivide(rel_range, fabs(rel_long_vel));
            if (fcw_ttc < 0.0F) {
                fcw_ttc = 30.0F;
            }
        }
    } else {
        // CA
        float collision_flag = rel_long_vel * rel_long_vel + 2.0F * rel_long_acc * rel_range;
        if (collision_flag < 0.0F) {
            fcw_ttc = 30.0F;
            return;
        }
        fcw_ttc = math::SafeDivide(sqrtf(fmaxf(collision_flag, 0.0F)) - rel_range, rel_long_acc);
        if (fcw_ttc < 0.0F) {
            fcw_ttc = 30.0F;
        }
    }
}

void ThreatAssessor::TransformObject() {
    float cos_h0 = cosf(host_predict_.heading);
    float sin_h0 = sinf(host_predict_.heading);
    // Linear transform.
    float local_lgt_pos = linear_predict_.long_pos - host_predict_.long_pos;
    float local_lat_pos = linear_predict_.lat_pos - host_predict_.lat_pos;
    linear_predict_.long_pos = cos_h0 * local_lgt_pos + sin_h0 * local_lat_pos;
    linear_predict_.lat_pos = cos_h0 * local_lat_pos - sin_h0 * local_lgt_pos;

    linear_predict_.long_vel = cos_h0 * linear_predict_.long_vel + sin_h0 * linear_predict_.lat_vel;
    linear_predict_.long_vel = math::RemoveNoise(linear_predict_.long_vel, 0.2F);
    linear_predict_.lat_vel = cos_h0 * linear_predict_.lat_vel - sin_h0 * linear_predict_.long_vel;
    linear_predict_.lat_vel = math::RemoveNoise(linear_predict_.lat_vel, 0.2F);

    linear_predict_.long_accel = cos_h0 * linear_predict_.long_accel + sin_h0 * linear_predict_.lat_accel;
    linear_predict_.long_accel = math::RemoveNoise(linear_predict_.long_accel, 0.2F);
    linear_predict_.lat_accel = cos_h0 * linear_predict_.lat_accel - sin_h0 * linear_predict_.long_accel;
    linear_predict_.lat_accel = math::RemoveNoise(linear_predict_.lat_accel, 0.2F);
    // Circular transform.
    circular_predict_.heading = circular_predict_.heading - host_predict_.heading;
    circular_predict_.heading = math::MapAngToInterval(M_PI, circular_predict_.heading);

    local_lgt_pos = circular_predict_.long_pos - host_predict_.long_pos;
    local_lat_pos = circular_predict_.lat_pos - host_predict_.lat_pos;

    circular_predict_.long_pos = cos_h0 * local_lgt_pos + sin_h0 * local_lat_pos;
    circular_predict_.lat_pos = cos_h0 * local_lat_pos - sin_h0 * local_lgt_pos;
}

void ThreatAssessor::ObjectPredictPath(const LongSafeObject &obs) {
    if (obs.stationary) {
        for (int i = 0; i < LTAP_TIME_NUM; ++i) {
            obj_pred_lgt_pos_[i] = linear_predict_.long_pos;
            obj_pred_lat_pos_[i] = linear_predict_.lat_pos;
            obj_pred_heading_[i] = linear_predict_.heading;
        }
    } else if (obs.curve_motion) {

    } else {
        for (int i = 0; i < LTAP_TIME_NUM; ++i) {
            float pred_time = LTAP_TIME_STEP * static_cast<float>(i);

            obj_pred_lgt_pos_[i] = linear_predict_.long_pos;
            obj_pred_lat_pos_[i] = linear_predict_.lat_pos;

            float lgt_vel = linear_predict_.long_vel;
            float lgt_accel = linear_predict_.long_accel;
            MotionLinearPredict::LinearPredictWithStop(obj_pred_lgt_pos_[i], lgt_vel, lgt_accel, pred_time, true);

            float lat_vel = linear_predict_.lat_vel;
            float lat_accel = linear_predict_.lat_accel;
            MotionLinearPredict::LinearPredictWithStop(obj_pred_lat_pos_[i], lat_vel, lat_accel, pred_time, true);

            // obj_pred_heading_[i] = atan2f(lat_vel, lgt_vel);
            obj_pred_heading_[i] = linear_predict_.heading;
        }
    }
}

void ThreatAssessor::CircularPredictAlgorithm(const LongSafeObject &obs, float time, MotionPredict &motion_predict) {
}

void ThreatAssessor::LinearPredictAlgorithm(const LongSafeObject &obs, float time, MotionPredict &motion_predict) {
    motion_predict.long_pos = obs.long_posn;
    motion_predict.long_vel = obs.long_vel;
    motion_predict.long_accel = obs.long_accel;
    MotionLinearPredict::LinearPredictWithStop(motion_predict.long_pos, motion_predict.long_vel, motion_predict.long_accel, time, true);

    motion_predict.lat_pos = obs.lat_posn;
    motion_predict.lat_vel = obs.lat_vel;
    motion_predict.lat_accel = obs.lat_accel;
    MotionLinearPredict::LinearPredictWithStop(motion_predict.lat_pos, motion_predict.lat_vel, motion_predict.lat_accel, time, true);

    // motion_predict.heading   = atan2f(motion_predict.lat_vel, motion_predict.long_vel);
    motion_predict.heading = obs.heading;
    motion_predict.curvature = 0.0F;
}

void ThreatAssessor::HostPredictAlgorithm(const AsVseOut &vse_out, float time, MotionPredict &motion_predict) {
    // We want to calculate curvature c0, speed v0, heading h0 and position (x0, y0) at the
    // prediction time.
    // The acceleration a0 is assumed to be constant.
    motion_predict.accel = vse_out.long_accel;
    motion_predict.long_accel = vse_out.long_accel;
    motion_predict.lat_accel = vse_out.lat_accel;
    // v1 = v0 + a0*t
    motion_predict.long_vel = vse_out.vcs_long_vel + vse_out.long_accel * time;

    // c0 = f(PinionAg) + c1*t, where c1 = f(PinionAgRate)
    float pred_curv = time * vse_out.rear_curvaturerate + vse_out.rear_curvature;

    // Why do this?
    // if (obs.f_is_motor_vehicle && obs.oncoming && obs.predict_valid) {
    //     pred_curv = ttr * vse_out.rear_curvaturerate + vse_out.rear_curvature
    // }

    motion_predict.curvature = math::Clamp(pred_curv, -0.1999, 0.1999);

    // h0 = c0*d, where d is the distance along the curve, a0*t^2/2 + VLgt*t
    float dist = vse_out.vcs_long_vel * time + 0.5 * vse_out.long_accel * time * time;
    motion_predict.heading = motion_predict.curvature * dist;
    motion_predict.heading = math::MapAngToInterval(M_PI, motion_predict.heading);

    if (fabsf(pred_curv) > 0.001F) {
        // If c0 is greater than a threshold value, then
        // x0 = sin(h0)/c0
        // y0 = (1-cos(h0))/c0
        float radius = math::SafeDivide(1.0F, motion_predict.curvature);
        motion_predict.long_pos = radius * sinf(motion_predict.heading);
        motion_predict.lat_pos = radius * (1.0F - cosf(motion_predict.heading));
    } else {
        // Otherwise a linear approximation is made:
        // x0 = d*cos(h0)
        // y0 = d*sin(h0)
        motion_predict.long_pos = dist * cosf(motion_predict.heading);
        motion_predict.lat_pos = dist * sinf(motion_predict.heading);
    }
}

} // namespace longsafe
} // namespace active_safety
