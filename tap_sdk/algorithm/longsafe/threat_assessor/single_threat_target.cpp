#include "single_threat_target.h"

#include <algorithm>
#include <numeric>
namespace active_safety {
namespace longsafe {

SingleThreatTarget::SingleThreatTarget() {
}
SingleThreatTarget::~SingleThreatTarget() = default;

SingleThreatTargetCal SingleThreatTarget::single_tgt_cal_{};

void SingleThreatTarget::SelectLongThreatTgt(const AsVseOut &vse_out, AsObstacleList &obs_list, const GlobalConfig &config) {
    // 倒车轨迹预测：标定使能 且 底盘反馈实际处于倒车状态时才启用，
    // 避免前进工况下瞬时负速度噪声误入倒车分支。
    // 复合判据与 VSE 速度定号逻辑保持一致(车轮反转 或 R 挡)，覆盖“挂 R 挡但车轮未转”的过渡帧，
    // 使 enable_reverse 与 vcs_long_vel 的符号严格对齐。
    bool host_reversing = (vse_out.f_reverse_status != 0) || (vse_out.actual_gear == 1);
    bool enable_reverse = config.k_Lgsf_EnReverseTrajPred && host_reversing;
    if (vse_out.aeb_active) {
        ego_path_.UpdatePath(vse_out.vcs_long_vel, 0.0F, vse_out.rear_curvature, vse_out.rear_curvaturerate, vse_out.config.k_host_width,
                             vse_out.config.k_host_length, vse_out.config.k_dist_to_rear_axle, enable_reverse);
    } else {
        ego_path_.UpdatePath(vse_out.vcs_long_vel, vse_out.long_accel, vse_out.rear_curvature, vse_out.rear_curvaturerate,
                             vse_out.config.k_host_width, vse_out.config.k_host_length, vse_out.config.k_dist_to_rear_axle,
                             enable_reverse);
    }

    for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
        // set obstacle
        //         if (obs_list[i]->fus_trkID != 9897) {
        //             continue;
        //         }
        obs_data_[i].obs            = obs_list[i];
        obs_data_[i].aeb_atv_target = (vse_out.aeb_active  &&  (obs_data_[i].obs->fus_trkID == aeb_target.fus_trkID));
        obs_data_[i].select_target  = (obs_data_[i].obs->fus_trkID == aeb_target.fus_trkID);
        BehaviorEvaluator::ObjBehaviorEvaluator(vse_out, obs_data_[i]);
        // printf("LongPos:%f,LatPos:%f,LongVel:%f,LatVel:%f,Hdg:%f,LgtAcc:%f,LatAcc:%f,CutProb:%f\n", obs_data_[i].obs->long_posn,
        //        obs_data_[i].obs->lat_posn, obs_data_[i].obs->long_vel, obs_data_[i].obs->lat_vel, obs_data_[i].obs->heading,
        //        obs_data_[i].obs->long_accel, obs_data_[i].obs->lat_accel, obs_data_[i].cutin_prob);
    }

    Preprocess(vse_out, config);

    for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
        // if (obs_data_[i].obs->fus_trkID != 9897 || obs_data_[i].obs->long_posn > 12.0F)
        //     continue;
        //        printf("LongPos:%f,LatPos:%f,LongVel:%f,LatVel:%f,Hdg:%f,LgtAcc:%f,LatAcc:%f\n", obs_data_[i].obs->long_posn,
        //        obs_data_[i].obs->lat_posn,
        //               obs_data_[i].obs->long_vel, obs_data_[i].obs->lat_vel, obs_data_[i].obs->heading, obs_data_[i].obs->long_accel,
        //               obs_data_[i].obs->lat_accel);
        if (std::find(sort_index.begin(), sort_index.end(), i) != sort_index.end()) {
            SafeMargin::CalculateSafeMargin(vse_out, obs_data_[i]);
            CollisionEvaluator::ObjInPathEvaluator(vse_out, ego_path_, obs_data_[i]);
        } else {
            obs_data_[i].Reset();
        }
    }

    LongThreatTarget(vse_out);

    UpdateDebugInfo(vse_out);
}

void SingleThreatTarget::LongThreatTarget(const AsVseOut &vse_out) {
    // 1.找出Inpath的目标
    inpath_index.clear();
    cur_inpath_index.clear();
    pred_inpath_index.clear();
    only_pred_inpath_index.clear();
    for (std::size_t i = 0; i < kMaxFusionObject; ++i) {
        if (obs_data_[i].inpath_res == false) {
            continue;
        }
        inpath_index.push_back(i);

        if (obs_data_[i].inpath_current == true) {
            cur_inpath_index.push_back(i);
        }
        if (obs_data_[i].inpath_predict == true) {
            pred_inpath_index.push_back(i);
        }
        if ((obs_data_[i].inpath_predict == true)  &&  (obs_data_[i].inpath_current == false)) {
            only_pred_inpath_index.push_back(i);
        }
    }
    //目前先选择inpath_index中距离自车最近的那个目标
    int   min_dist_idx = -1;
    float min_dist     = 10000.0F;
    for (std::size_t i = 0; i < inpath_index.size(); ++i) {
        if (min_dist >= obs_data_[inpath_index[i]].obs->long_posn) {
            min_dist_idx = inpath_index[i];
            min_dist     = obs_data_[inpath_index[i]].obs->long_posn;
        }
    }
    if (min_dist_idx >= 0) {
        BehaviorEvaluator::UpdateObsManType(vse_out, obs_data_[min_dist_idx]);
        aeb_target.Update(obs_data_[min_dist_idx]);
    } else {
        aeb_target.Reset();
    }
}

void SingleThreatTarget::UpdateDebugInfo(const AsVseOut &vse_out) {
    tsel_debug_.Reset();

    tsel_debug_.ego_spd       = vse_out.vcs_long_vel;
    tsel_debug_.ego_accel     = vse_out.long_accel;
    tsel_debug_.ego_yawrate   = vse_out.yawrate;
    tsel_debug_.ego_curvature = vse_out.rear_curvature;
    tsel_debug_.aeb_active    = vse_out.aeb_active;

    tsel_debug_.presel_num           = static_cast<int>(sort_index.size());
    tsel_debug_.inpath_num           = static_cast<int>(inpath_index.size());
    tsel_debug_.cur_inpath_num       = static_cast<int>(cur_inpath_index.size());
    tsel_debug_.pred_inpath_num      = static_cast<int>(pred_inpath_index.size());
    tsel_debug_.only_pred_inpath_num = static_cast<int>(only_pred_inpath_index.size());
    tsel_debug_.has_target           = (aeb_target.fus_trkID != 0);

    // 按 fus_trkID 锁定槽位，保证同一目标跨帧 index 稳定，便于观察。
    // 1) 先清除当前帧已不存在(丢失)的槽位。
    auto in_cur_frame = [&](int32_t fus_id) {
        for (int idx : sort_index) {
            if (obs_data_[idx].obs->fus_trkID == fus_id) {
                return true;
            }
        }
        return false;
    };
    for (auto &slot : tsel_debug_.objs) {
        if (slot.valid  &&  !in_cur_frame(slot.fus_trkID)) {
            slot.Clear();
        }
    }

    // 单目标信息填充。
    auto fill_obj = [&](TselObjDebug &dbg, int idx) {
        const LgSfObsData &od = obs_data_[idx];
        dbg.valid        = true;
        dbg.index        = idx;
        dbg.fus_trkID    = od.obs->fus_trkID;
        dbg.vis_trkID    = od.obs->vis_trkID;
        dbg.object_class = static_cast<int32_t>(od.obs->object_class);

        dbg.long_posn  = od.obs->long_posn;
        dbg.lat_posn   = od.obs->lat_posn;
        dbg.long_vel   = od.obs->long_vel;
        dbg.lat_vel    = od.obs->lat_vel;
        dbg.long_accel = od.obs->long_accel;
        dbg.lat_accel  = od.obs->lat_accel;
        dbg.heading    = od.obs->heading;
        dbg.speed      = od.obs->speed;

        dbg.stationary   = od.stationary;
        dbg.oncoming     = od.oncoming;
        dbg.curve_motion = od.curve_motion;
        dbg.cutin        = od.cutin;
        dbg.cutin_prob   = od.cutin_prob;

        dbg.offs_lat_inpath_current   = od.offs_lat_inpath_current;
        dbg.offs_lgt_inpath_pred_edge = od.offs_lgt_inpath_pred_edge;
        dbg.offs_lat_inpath_pred_edge = od.offs_lat_inpath_pred_edge;

        dbg.predict_valid                 = od.predict_valid;
        dbg.predict_valid_spd_ok          = od.predict_valid_spd_ok;
        dbg.predict_valid_pred_distance   = od.predict_valid_pred_distance;
        dbg.predict_valid_ttr_valid       = od.predict_valid_ttr_valid;
        dbg.predict_valid_pred_type_valid = od.predict_valid_pred_type_valid;
        dbg.ttr                           = od.pred_info[MotionType::Default].ttr;
        dbg.ttp                           = od.pred_info[MotionType::Default].ttp;
        dbg.ttp_index                     = od.pred_info[MotionType::Default].ttp_index;
        dbg.ttr_lat_overlap_rate          = od.pred_info[MotionType::Default].ttr_lat_overlap_rate;

        dbg.inpath_current          = od.inpath_current;
        dbg.inpath_predict          = od.inpath_predict;
        dbg.pred_inpath_fail_reason = static_cast<int>(od.pred_inpath_fail_reason);
        dbg.inpath_res              = od.inpath_res;

        dbg.pi_rel_lgt            = od.pred_inpath_debug.rel_lgt;
        dbg.pi_front_limit        = od.pred_inpath_debug.front_limit;
        dbg.pi_rear_limit         = od.pred_inpath_debug.rear_limit;
        dbg.pi_safe_lat           = od.pred_inpath_debug.safe_lat;
        dbg.pi_half_host_width    = od.pred_inpath_debug.half_host_width;
        dbg.pi_host_rel_obs_lgt   = od.pred_inpath_debug.host_rel_obs_lgt;
        dbg.pi_obs_lgt_safe_space = od.pred_inpath_debug.obs_lgt_safe_space;
        dbg.pi_host_rel_obs_lat   = od.pred_inpath_debug.host_rel_obs_lat;
        dbg.pi_obs_lat_safe_space = od.pred_inpath_debug.obs_lat_safe_space;

        dbg.is_inpath   = (std::find(inpath_index.begin(), inpath_index.end(), idx) != inpath_index.end());
        dbg.is_selected = (aeb_target.fus_trkID != 0)  &&  (od.obs->fus_trkID == aeb_target.fus_trkID);
    };

    // 2) 更新已有槽位的目标(原地更新，index 不变)。
    for (int idx : sort_index) {
        int32_t fus_id = obs_data_[idx].obs->fus_trkID;
        for (auto &slot : tsel_debug_.objs) {
            if (slot.valid  &&  slot.fus_trkID == fus_id) {
                fill_obj(slot, idx);
                break;
            }
        }
    }

    // 3) 新出现的目标分配到第一个空闲槽位。
    for (int idx : sort_index) {
        int32_t fus_id = obs_data_[idx].obs->fus_trkID;
        bool already = false;
        for (const auto &slot : tsel_debug_.objs) {
            if (slot.valid  &&  slot.fus_trkID == fus_id) {
                already = true;
                break;
            }
        }
        if (already) {
            continue;
        }
        for (auto &slot : tsel_debug_.objs) {
            if (!slot.valid) {
                fill_obj(slot, idx);
                break;
            }
        }
    }
}

void SingleThreatTarget::Preprocess(const AsVseOut &vse_out, const GlobalConfig &config) {
    std::vector<int> valid_obs;

    //查找有效目标
    for (std::size_t idx = 0; idx < obs_data_.size(); ++idx) {
        bool vld_id = obs_data_[idx].obs->fus_trkID > 0 ;
        if (vld_id == false) {
            continue;
        }

        bool vld_type = (obs_data_[idx].obs->object_class == ObjectClass::CAR || obs_data_[idx].obs->object_class == ObjectClass::TRUCK ||
                         obs_data_[idx].obs->object_class == ObjectClass::BUS || obs_data_[idx].obs->object_class == ObjectClass::MOTORCYCLE ||
                         obs_data_[idx].obs->object_class == ObjectClass::ESCOOTER || obs_data_[idx].obs->object_class == ObjectClass::BICYCLE ||
                         obs_data_[idx].obs->object_class == ObjectClass::PEDESTRIAN || obs_data_[idx].obs->object_class == ObjectClass::GOD ||
                         obs_data_[idx].obs->object_class == ObjectClass::GENOBJ || obs_data_[idx].obs->object_class == ObjectClass::ANIMAL ||
                         obs_data_[idx].obs->object_class == ObjectClass::OCC);
        if (vld_type == false) {
            continue;
        }

        bool vld_pos;
        if (std::abs(obs_data_[idx].obs->lat_posn) < vse_out.config.k_host_width * 0.5) {
            vld_pos = (obs_data_[idx].obs->long_posn > vse_out.config.k_dist_to_rear_axle);
        } else {
            float vld_long_pos_thres = 0.0F;
            if (fabs(vse_out.yawrate) > 0.027F && obs_data_[idx].obs->lat_posn < -0.5 * vse_out.config.k_host_width &&
                obs_data_[idx].obs->lat_posn > -4.0F && obs_data_[idx].obs->long_vel > 2.0F &&
                (obs_data_[idx].obs->object_class == ObjectClass::ESCOOTER || obs_data_[idx].obs->object_class == ObjectClass::BICYCLE)) {
                vld_long_pos_thres = -7.0F;
            }
            vld_pos = (obs_data_[idx].obs->long_posn > vld_long_pos_thres);
        }
        if (vld_pos == false) {
            continue;
        }

        bool vld_conf = config.k_Lgsf_ForOldRsclBag || obs_data_[idx].obs->confidence > ObsConfidence::LOW_CONF;
        if (vld_conf == false) {
            continue;
        }
        valid_obs.push_back(idx);
    }

    //有效目标未超过阈值，直接返回
    if (valid_obs.size() <= PRE_TSEL_OBJ_NUM) {
        sort_index.clear();
        if (aeb_target.index > 0) {
            sort_index.push_back(aeb_target.index - 1);
        }
        for (int idx : valid_obs) {
            if (sort_index.size() >= PRE_TSEL_OBJ_NUM) {
                break;
            }
            sort_index.push_back(idx);
        }
        return;
    }
    //若有效目标超过10个，则需要进行初步排序
    std::vector<float> valid_obs_ttc;

    for (auto &idx : valid_obs) {
        //计算纵向TTC
        float rel_longacc   = obs_data_[idx].obs->long_accel - vse_out.long_accel;
        float rel_longvel   = obs_data_[idx].obs->long_vel - vse_out.vcs_long_vel;
        float long_distance = obs_data_[idx].obs->long_posn - vse_out.config.k_dist_to_rear_axle - single_tgt_cal_.k_first_sort_safe_long_dist_thres;
        float ttc_1, ttc_2, ttc;
        if (!math::SolveQuadratic(rel_longacc / 2.0F, rel_longvel, long_distance, ttc_1, ttc_2)) {
            ttc = single_tgt_cal_.k_max_ttc;
        } else {
            if ((ttc_1 <= 0)  &&  (ttc_2 > 0)) {
                ttc = ttc_2;
            } else if (ttc_1 > 0 && ttc_2 <= 0) {
                ttc = ttc_1;
            } else if (ttc_1 >= 0 && ttc_2 >= 0) {
                ttc = std::min(ttc_1, ttc_2);
            } else {
                ttc = single_tgt_cal_.k_max_ttc;
            }
        }
        //计算横向TTC
        float lat_ttc;
        if (std::abs(obs_data_[idx].obs->lat_posn) < single_tgt_cal_.k_first_sort_lat_zone) {
            lat_ttc = 0;
        } else {
            //计算自车横向运动
            float dist_lat_host = vse_out.vcs_long_vel * vse_out.yawrate * ttc * ttc / 2.0F;
            //左侧TTC
            float left_lat_ttc =
                -(obs_data_[idx].obs->lat_posn - (dist_lat_host + single_tgt_cal_.k_first_sort_inpath_width)) / obs_data_[idx].obs->lat_vel;
            if (left_lat_ttc < 0) {
                left_lat_ttc = single_tgt_cal_.k_max_ttc;
            }
            //右侧TTC
            float right_lat_ttc =
                -(obs_data_[idx].obs->lat_posn - (dist_lat_host - single_tgt_cal_.k_first_sort_inpath_width)) / obs_data_[idx].obs->lat_vel;
            if (right_lat_ttc < 0) {
                right_lat_ttc = single_tgt_cal_.k_max_ttc;
            }
            lat_ttc = std::min(left_lat_ttc, right_lat_ttc);
        }
        ttc = std::max(ttc, lat_ttc);
        valid_obs_ttc.push_back(ttc);
    }
    //根据ttc排序
    SortByIdAndTTC(valid_obs, valid_obs_ttc);

    sort_index.clear();

    int aeb_idx = aeb_target.index > 0 ? aeb_target.index - 1 : -1;
    // 若 valid_obs 中包含满足索引和 fus_trkID 都一致的 AEB 目标，
    // 则将其放在 sort_index 第一个位置，剩下按照排序结果依次填充
    if (aeb_idx >= 0) {
        sort_index.push_back(aeb_idx);
        for (int idx : valid_obs) {
            if (idx == aeb_idx) {
                continue; // 跳过已放入的 AEB 目标
            }
            if (sort_index.size() >= PRE_TSEL_OBJ_NUM) {
                break;
            }
            sort_index.push_back(idx);
        }
        return;
    }

    // 若 valid_obs 中没有 AEB 目标，则直接取前 10 个有效目标
    for (int idx : valid_obs) {
        if (sort_index.size() >= PRE_TSEL_OBJ_NUM) {
            break;
        }
        sort_index.push_back(idx);
    }
}

void SingleThreatTarget::SortByIdAndTTC(std::vector<int> &ids, std::vector<float> &ttcs) {
    // 检查输入有效性
    if ((ids.size() != ttcs.size())  ||  ids.empty()) {
        return;
    }

    // 创建下标数组
    std::vector<size_t> indices(ids.size());
    std::iota(indices.begin(), indices.end(), 0);

    // 根据ttc值对下标排序
    std::sort(indices.begin(), indices.end(), [&](size_t i, size_t j) { return ttcs[i] < ttcs[j]; });

    // 根据排序后的下标重新排列ids和ttcs
    std::vector<int>   sorted_ids(ids.size());
    std::vector<float> sorted_ttcs(ttcs.size());

    for (size_t i = 0; i < indices.size(); ++i) {
        sorted_ids[i]  = ids[indices[i]];
        sorted_ttcs[i] = ttcs[indices[i]];
    }

    // 更新原数组
    ids  = std::move(sorted_ids);
    ttcs = std::move(sorted_ttcs);
}
} // namespace longsafe
} // namespace active_safety
