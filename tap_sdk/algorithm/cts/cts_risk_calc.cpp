#include "cts_function.h"

#include <iostream>


namespace active_safety {
namespace cts {

void CtsFunction::CheckMotion(CtsObsData &obs_data) {
    if (obs_data.m_obs->speed < m_cts_cal.k_cta_stationary_speed_thres) {
        obs_data.m_stationary = true;
    } else {
        obs_data.m_stationary = false;
    }
    CheckCrossDecel(obs_data);
}

void CtsFunction::CheckCrossDecel(CtsObsData &obs_data) {
    bool tmp_cd = obs_data.m_cross_decel;
    obs_data.m_cross_decel = obs_data.m_cross_decel_offdly.offDelay(obs_data.m_obs->f_cross_decel, m_cts_cal.k_cta_cross_decel_offdly_time, CTS_STEP_TIME);
    if (obs_data.m_cross_decel && !tmp_cd) {
        obs_data.m_init_cross_decel_lat_vel = obs_data.m_obs->lat_vel;
    } else if (!obs_data.m_cross_decel) {
        obs_data.m_init_cross_decel_lat_vel = 0.0f;
    }
}

void CtsFunction::SetThresData(const AsVseOut &vse_out) {
    m_rcts_thres = m_cts_cal.k_cta_thres_data;
    for (ThresData &td : m_rcts_thres) {
        td.inter_sec_min -= vse_out.config.k_host_length;
        td.inter_sec_max -= vse_out.config.k_host_length;
    }

    m_fcts_thres = m_cts_cal.k_cta_thres_data;
    for (ThresData &td : m_fcts_thres) {
        float tmp = td.inter_sec_min;
        td.inter_sec_min = -td.inter_sec_max;
        td.inter_sec_max = -tmp;
    }
    if (m_fcta_ttc_execution_state) {
        if (fabs(vse_out.speed) > m_cts_cal.k_cta_speed_threshold_deactive_fcta_ttc) {
            m_fcts_thres[0].ttc_thres -= m_cts_cal.k_cta_ttc_threshold_offset_fcta_fast;
            m_fcta_ttc_execution_state = false;
        } else {
            m_fcts_thres[0].ttc_thres -= m_cts_cal.k_cta_ttc_threshold_offset_fcta_slow;
            m_fcta_ttc_execution_state = true;
        }
    } else {
        if (fabs(vse_out.speed) < m_cts_cal.k_cta_speed_threshold_activate_fcta_ttc) {
            m_fcts_thres[0].ttc_thres -= m_cts_cal.k_cta_ttc_threshold_offset_fcta_slow;
            m_fcta_ttc_execution_state = true;
        } else {
            m_fcts_thres[0].ttc_thres -= m_cts_cal.k_cta_ttc_threshold_offset_fcta_fast;
            m_fcta_ttc_execution_state = false;
        }
    }
}

void CtsFunction::CheckCTA(const AsVseOut &vse_out, const std::array<ThresData, CTS_MAX_LEVEL> &thres, CtsObsData &obs_data, ObsAttribute &obs_attr,
                           std::array<WarnInfo, CTS_MAX_SIDE> &warn_info, CtsDirection dir) {
    if (ValidObs(vse_out, warn_info, obs_data, obs_attr)) {
        if (warn_info[0].highest_critical_obs_idx == -1 && obs_data.m_approach_side == CTA_APPROACH_FROM_LEFT) {
            warn_info[0].highest_critical_obs_idx = obs_data.m_obs->track_id - 1;
        }
        if (warn_info[1].highest_critical_obs_idx == -1 && obs_data.m_approach_side == CTA_APPROACH_FROM_RIGHT) {
            warn_info[1].highest_critical_obs_idx = obs_data.m_obs->track_id - 1;
        }
        CalculateTargetReferencePoint(obs_data, obs_attr);
        CalculateTimeToConflict(vse_out.config, obs_data, obs_attr);
        CalculateIntersecPoint(obs_data.m_relative_velocity, obs_attr);
        CalculateRadialDistance(vse_out.config, obs_attr);
        CheckObsInZone(vse_out, obs_data, obs_attr);
        CheckAllLevel(vse_out, thres, obs_data, obs_attr, warn_info, dir);
    } else {
        obs_attr.Reset();
    }
}

void CtsFunction::ProcessThreatLevel(std::array<WarnInfo, CTS_MAX_SIDE> &warn_infos, CtsDirection dir) {
    for (std::size_t i = 0; i < CTS_MAX_SIDE; ++i) {
        WarnInfo &warn_info = warn_infos[i];

        if (m_common_inhibit_offdly.getStateOut()) {
            warn_info.hold_cnt = 0;
            warn_info.obs_fusId = 0;
            warn_info.obs_index = -1;
            warn_info.last_level = 0;
            continue;
        }

        if (warn_info.max_level > warn_info.last_level) {
            warn_info.hold_cnt = 0;
            if (warn_info.highest_critical_obs_idx >= 0) {
                warn_info.last_level = warn_info.max_level;
                warn_info.obs_fusId = m_obs_data[warn_info.highest_critical_obs_idx].m_obs->fus_trkID;
                warn_info.obs_index = m_obs_data[warn_info.highest_critical_obs_idx].m_obs->track_id - 1;
            }
        } else {
            warn_info.hold_cnt = std::min(warn_info.hold_cnt + 1, 255);
            if (warn_info.hold_cnt > m_cts_cal.k_cts_hold_cycles) {
                warn_info.last_level = warn_info.max_level;
                if (warn_info.highest_critical_obs_idx >= 0) {
                    if (warn_info.max_level > 0) {
                        warn_info.hold_cnt = 0;
                        warn_info.obs_fusId = m_obs_data[warn_info.highest_critical_obs_idx].m_obs->fus_trkID;
                        warn_info.obs_index = m_obs_data[warn_info.highest_critical_obs_idx].m_obs->track_id - 1;
                    } else {
                        warn_info.obs_fusId = 0;
                        warn_info.obs_index = -1;
                    }
                }
            } else {
                if (warn_info.highest_critical_obs_idx >= 0 && warn_info.obs_fusId == m_obs_data[warn_info.highest_critical_obs_idx].m_obs->fus_trkID) {
                    int last_level = warn_info.last_level - 1;
                    if (last_level >= 0) {
                        m_obs_data[warn_info.highest_critical_obs_idx].m_attr[static_cast<int>(dir)].counter_val[last_level] = 255;
                    }
                }
            }
        }
        warn_info.cur_level = warn_info.last_level;

        // 记录保持/迟滞结果(等价被删掉的 ProcessThreatLevel cout)
        if (m_cts_cal.k_cts_debug_log_enable) {
            CtsTargetDebug &td = m_debug.target[static_cast<int>(dir)][i];
            td.last_level = warn_info.last_level;
            td.cur_level = warn_info.cur_level;
            td.hold_cnt = warn_info.hold_cnt;
            if (td.max_level == 0) {
                td.max_level = warn_info.max_level;
            }
        }
    }
}
void CtsFunction::CheckAllLevel(const AsVseOut &vse_out, const std::array<ThresData, CTS_MAX_LEVEL> &thres, const CtsObsData &obs_data,
                                ObsAttribute &obs_attr, std::array<WarnInfo, CTS_MAX_SIDE> &warn_info, CtsDirection dir) {
    int side = 0;
    if (obs_data.m_approach_side == ObsApproachSide::CTA_APPROACH_FROM_RIGHT) {
        side = 1;
    }
    int &side_idx = warn_info[side].highest_critical_obs_idx;

    int cur_level = 0;

    std::array<ThresData, CTS_MAX_LEVEL> ts = thres;

    // 记录当前目标的逐级判据，循环结束后若其为该侧关键目标则提交到 m_debug
    const bool dbg_on = m_cts_cal.k_cts_debug_log_enable;
    CtsTargetDebug tgt_dbg;
    if (dbg_on) {
        tgt_dbg.valid = true;
        tgt_dbg.fus_trkID = obs_data.m_obs->fus_trkID;
        tgt_dbg.track_id = obs_data.m_obs->track_id;
        tgt_dbg.heading = obs_data.m_obs->heading;
        tgt_dbg.lat_posn = obs_data.m_obs->lat_posn;
        tgt_dbg.long_posn = obs_data.m_obs->long_posn;
        tgt_dbg.lat_vel = obs_data.m_obs->lat_vel;
        tgt_dbg.long_vel = obs_data.m_obs->long_vel;
    }

    for (std::size_t k = 0; k < ts.size(); ++k) {
        if (obs_attr.last_level > ts[k].level) {
            // ApplyLevelThresHyst();
        }
        if (m_veh_decel_offdly.getStateOut() &&
            m_drv_wantbrake_ondly.getCurCount() >= static_cast<uint32_t>(m_cts_cal.k_cts_drv_brake_cnt_thres)) {
            // 车辆在减速且驾驶员踩刹车一定时间,判断在多目标复杂场景下驾驶员有操作意识，且此场景下目标信息容易有误
            ts[k].inter_sec_max *= m_cts_cal.k_cta_brake_zone_shrink_factor;
        }
        if (m_drv_continues_steer_offdly.getStateOut()) {
            // 驾驶员持续转向一定时间时，其盲区视角会缩小
            ts[k].inter_sec_max *= m_cts_cal.k_cta_continues_steer_shrink_factor;
            if (m_drv_continues_steer_ondly.getCurCount() >= static_cast<uint32_t>(m_cts_cal.k_cts_continues_steer_cnt_thres)) {
                ts[k].inter_sec_max *= m_cts_cal.k_cta_long_steer_shrink_factor;
            }
        }
        if (obs_data.m_cross_decel) {
            ts[k].inter_sec_max *= m_cts_cal.k_cta_cross_decel_shrink_factor;
        }

        if (m_cts_cal.k_cta_inter_sec_max_correction_enabled && ((dir == CtsDirection::FRONT) || (dir == CtsDirection::REAR))) {

            // float inter_sec_max_offset =
            //     math::LookUpTable::LookupTable1D<5>(
            //         m_cts_cal.k_fcta_inter_sec_max_correction_speed,
            //         m_cts_cal.k_fcta_inter_sec_max_correction_x,
            //         fabs(vse_out.speed));
            float inter_sec_max_offset;
            if (vse_out.speed < 0.0f) {
                inter_sec_max_offset = m_cts_cal.k_cta_offset_reverse;
            } else if (vse_out.speed > m_cts_cal.k_cta_offset_speed_seg_thres) {
                inter_sec_max_offset = m_cts_cal.k_cta_offset_high_speed_base +
                    std::max(vse_out.speed * m_cts_cal.k_cta_offset_speed_coeff, m_cts_cal.k_cta_offset_min) + m_cts_cal.k_cta_offset_margin;
            } else {
                inter_sec_max_offset = fabs(vse_out.speed) * fabs(vse_out.speed) / m_cts_cal.k_cta_offset_assumed_decel /
                        m_cts_cal.k_cta_offset_kinematic_factor +
                    std::max(vse_out.speed * m_cts_cal.k_cta_offset_speed_coeff, m_cts_cal.k_cta_offset_min) + m_cts_cal.k_cta_offset_margin;
            }

            // ts[3].inter_sec_max = std::min(ts[3].inter_sec_max,inter_sec_max_offset);
            // ts[4].inter_sec_max = std::min(ts[4].inter_sec_max,inter_sec_max_offset);
            if (k == 3 || k == 4) {
                ts[k].inter_sec_max = std::min(ts[k].inter_sec_max, inter_sec_max_offset);
            }
        }

        bool ttc_check = (0.0f < obs_attr.lat_ttc && obs_attr.lat_ttc < ts[k].ttc_thres);
        bool radial_dist_check = obs_attr.radial_distance < ts[k].rad_dist_thres;
        bool inter_x_check = (ts[k].inter_sec_min + vse_out.config.k_dist_to_rear_axle < obs_attr.intersect_pt.x &&
                              obs_attr.intersect_pt.x < ts[k].inter_sec_max + vse_out.config.k_dist_to_rear_axle);
        if (static_cast<int>(k + 1) >= m_cts_cal.k_ctb_min_active_level) {
            ttc_check &= obs_attr.lgt_ttc > 0.0f;
        }

        // 记录本级判据(等价被删掉的 CheckAllLevel cout)
        CtsLevelDebug &ld = tgt_dbg.levels[k];
        if (dbg_on) {
            ld.in_zone = obs_attr.in_zone;
            ld.lat_ttc = obs_attr.lat_ttc;
            ld.ttc_thres = ts[k].ttc_thres;
            ld.lgt_ttc = obs_attr.lgt_ttc;
            ld.ttc_check = ttc_check;
            ld.radial_distance = obs_attr.radial_distance;
            ld.rad_dist_thres = ts[k].rad_dist_thres;
            ld.radial_dist_check = radial_dist_check;
            ld.intersect_x = obs_attr.intersect_pt.x;
            ld.inter_min = ts[k].inter_sec_min + vse_out.config.k_dist_to_rear_axle;
            ld.inter_max = ts[k].inter_sec_max + vse_out.config.k_dist_to_rear_axle;
            ld.inter_x_check = inter_x_check;
        }

        if (obs_attr.in_zone && ttc_check && radial_dist_check && inter_x_check) {
            obs_attr.counter_val[k]++;
            // FCTA斜穿自行车目标额外确认帧：
            // 仅当自车稳定直行（straight_driving）且目标为自行车类型（f_is_bicycle）时生效。
            // |heading| <= 60°          ：额外 extra_max 帧
            // |heading| ∈ (60°, 75°)   ：线性插值 extra_max → extra_min
            // |heading| ∈ [75°, 105°]  ：不增加
            // |heading| ∈ (105°, 120°) ：线性插值 extra_min → extra_max
            // |heading| >= 120°         ：额外 extra_max 帧
            int confirm_thres = ts[k].above_thres_cnt;
            if (dir == CtsDirection::FRONT &&
                vse_out.straight_driving &&
                obs_data.m_obs->f_is_bicycle) {
                float heading_abs = fabs(obs_data.m_obs->heading);
                int extra = 0;
                if (heading_abs <= m_cts_cal.k_fcta_diag_heading_low_thrd) {
                    extra = m_cts_cal.k_fcta_diag_extra_confirm_frames;
                } else if (heading_abs < m_cts_cal.k_fcta_diag_heading_low_fade) {
                    float t = (heading_abs - m_cts_cal.k_fcta_diag_heading_low_thrd) /
                              (m_cts_cal.k_fcta_diag_heading_low_fade - m_cts_cal.k_fcta_diag_heading_low_thrd);
                    extra = static_cast<int>(
                        m_cts_cal.k_fcta_diag_extra_confirm_frames_min +
                        (1.0f - t) * (m_cts_cal.k_fcta_diag_extra_confirm_frames - m_cts_cal.k_fcta_diag_extra_confirm_frames_min) + 0.5f);
                } else if (heading_abs > m_cts_cal.k_fcta_diag_heading_high_thrd) {
                    extra = m_cts_cal.k_fcta_diag_extra_confirm_frames;
                } else if (heading_abs > m_cts_cal.k_fcta_diag_heading_high_fade) {
                    float t = (heading_abs - m_cts_cal.k_fcta_diag_heading_high_fade) /
                              (m_cts_cal.k_fcta_diag_heading_high_thrd - m_cts_cal.k_fcta_diag_heading_high_fade);
                    extra = static_cast<int>(
                        m_cts_cal.k_fcta_diag_extra_confirm_frames_min +
                        t * (m_cts_cal.k_fcta_diag_extra_confirm_frames - m_cts_cal.k_fcta_diag_extra_confirm_frames_min) + 0.5f);
                }
                confirm_thres += extra;
            }
            if (dbg_on) {
                ld.counter_val = obs_attr.counter_val[k];
                ld.confirm_thres = confirm_thres;
                ld.level_passed = (obs_attr.counter_val[k] > confirm_thres);
            }
            if (obs_attr.counter_val[k] > confirm_thres) {
                cur_level = k + 1;
                if (cur_level > warn_info[side].max_level) {
                    warn_info[side].max_level = cur_level;
                    side_idx = obs_data.m_obs->track_id - 1;
                } else if (side_idx >= 0 && cur_level == warn_info[side].max_level && obs_attr.lat_ttc <= m_obs_data[side_idx].m_attr[side].lat_ttc) {
                    if (!(fabs(obs_attr.lat_ttc - m_obs_data[side_idx].m_attr[side].lat_ttc) < EQUALS_TOLERANCE &&
                          obs_attr.radial_distance >= m_obs_data[side_idx].m_attr[side].radial_distance)) {
                        side_idx = obs_data.m_obs->track_id - 1;
                    }
                }
            }
        } else {
            obs_attr.counter_val[k] = 0;
            if (dbg_on) {
                ld.counter_val = 0;
                ld.confirm_thres = ts[k].above_thres_cnt;
                ld.level_passed = false;
            }
        }
    }
    obs_attr.last_level = cur_level;

    // 若当前目标是该侧关键目标(升级或维持 max_level)，提交其逐级明细供回灌调试打印
    if (dbg_on && side_idx == obs_data.m_obs->track_id - 1) {
        int dir_idx = static_cast<int>(dir);
        tgt_dbg.max_level = warn_info[side].max_level;
        tgt_dbg.highest_critical_obs_idx = side_idx;
        m_debug.target[dir_idx][side] = tgt_dbg;
    }
}

bool CtsFunction::ValidObs(const AsVseOut &vse_out, const std::array<WarnInfo, CTS_MAX_SIDE> &warn_info, CtsObsData &obs_data,
                           ObsAttribute &obs_attr) {
    bool f_return = true;
    const bool dbg_on = m_cts_cal.k_cts_debug_log_enable;
    std::size_t debug_obs_index = m_obs_data.size();
    const std::size_t debug_dir_index = static_cast<std::size_t>(obs_attr.direction);
    if (dbg_on) {
        for (std::size_t i = 0; i < m_obs_data.size(); ++i) {
            if (&m_obs_data[i] == &obs_data) {
                debug_obs_index = i;
                break;
            }
        }
    }

    const bool has_debug_record = dbg_on && debug_obs_index < m_obs_data.size() && debug_dir_index < 2U;
    if (has_debug_record) {
        CtsInvalidTargetDebug &debug_record = m_debug.invalid_target[debug_dir_index][debug_obs_index];
        debug_record = CtsInvalidTargetDebug{};
        debug_record.evaluated = true;
        debug_record.fus_trkID = obs_data.m_obs->fus_trkID;
        debug_record.track_id = obs_data.m_obs->track_id;
        debug_record.approach_side = static_cast<uint8_t>(obs_data.m_approach_side);
        debug_record.age = obs_data.m_obs->age;
        debug_record.speed = obs_data.m_obs->speed;
        debug_record.heading = obs_data.m_obs->heading;
        debug_record.lat_approach_speed = fabs(obs_data.m_relative_velocity.y);
        debug_record.angle_diff = fabs(obs_data.m_angle_diff);
        debug_record.lat_posn = obs_data.m_obs->lat_posn;
        debug_record.long_posn = obs_data.m_obs->long_posn;
        debug_record.lat_vel = obs_data.m_obs->lat_vel;
        debug_record.long_vel = obs_data.m_obs->long_vel;
    }

    auto record_reason = [&](uint32_t reason) {
        if (has_debug_record) {
            m_debug.invalid_target[debug_dir_index][debug_obs_index].reasons |= reason;
        }
    };

    auto check = [&](bool condition, uint32_t reason) {
        if (!condition) {
            f_return = false;
            record_reason(reason);
        }
    };

    // Keep evaluating every independent check so the debug frame can explain
    // all rejection reasons, while the accumulated result below preserves the
    // original validity decision.
    check(obs_data.m_obs->fus_trkID > 0, CTS_INVALID_NO_TRACK_ID);
    check(obs_data.m_obs->confidence != ObsConfidence::LOW_CONF, CTS_INVALID_LOW_CONFIDENCE);
    // 非调试模式保持快速返回；调试模式继续收集其他失败原因，调试模式下跳过空目标槽位，避免对大量空槽执行后续几何计算
    if (!f_return && !dbg_on) {
        return false;
    }
    
    if (dbg_on && obs_data.m_obs->fus_trkID <= 0 && obs_data.m_obs->track_id <= 0) {
        return false;
    }

    // 1. 滞后处理 (Hysteresis)
    float k_cta_heading_angle_hys = m_cts_cal.k_cta_cross_dist_max_lat_angle_diff * m_cts_cal.k_cta_rel_warning_hysteresis;
    float min_speed_obj = m_cts_cal.k_cta_min_speed;
    float min_lat_approach_spd = m_cts_cal.k_cta_min_lateral_approach_speed;

    float min_hdg_obj, max_hdg_obj;
    if (obs_data.m_approach_side == ObsApproachSide::CTA_APPROACH_FROM_LEFT) {
        min_hdg_obj = m_cts_cal.k_cta_cross_dist_max_lat_angle_diff - m_pi;
        max_hdg_obj = -m_cts_cal.k_cta_cross_dist_max_lat_angle_diff;
    } else {
        min_hdg_obj = m_cts_cal.k_cta_cross_dist_max_lat_angle_diff;
        max_hdg_obj = m_pi - m_cts_cal.k_cta_cross_dist_max_lat_angle_diff;
    }

    if (obs_attr.last_level > 0) {
        min_speed_obj -= m_cts_cal.k_cta_min_speed_hys;
        min_lat_approach_spd -= min_lat_approach_spd * m_cts_cal.k_cta_rel_warning_hysteresis;
        min_hdg_obj -= k_cta_heading_angle_hys;
        max_hdg_obj += k_cta_heading_angle_hys;
    }

    // 静止目标校验
    if (m_cts_cal.k_cta_check_stationary_signal) {
        check(!obs_data.m_stationary, CTS_INVALID_STATIONARY);
    }

    // 生存周期校验
    if ((obs_attr.direction == CtsDirection::FRONT &&
         ((obs_data.m_approach_side == ObsApproachSide::CTA_APPROACH_FROM_LEFT && obs_data.m_obs->heading < -m_cts_cal.k_cta_diag_front_heading_min &&
           obs_data.m_obs->heading > -m_cts_cal.k_cta_diag_front_heading_max) ||
          (obs_data.m_approach_side == ObsApproachSide::CTA_APPROACH_FROM_RIGHT && obs_data.m_obs->heading > m_cts_cal.k_cta_diag_front_heading_min &&
           obs_data.m_obs->heading < m_cts_cal.k_cta_diag_front_heading_max))) ||
        (obs_attr.direction == CtsDirection::REAR &&
         ((obs_data.m_approach_side == ObsApproachSide::CTA_APPROACH_FROM_LEFT && obs_data.m_obs->heading > -m_cts_cal.k_cta_diag_rear_heading_max &&
           obs_data.m_obs->heading < -m_cts_cal.k_cta_diag_rear_heading_min) ||
          (obs_data.m_approach_side == ObsApproachSide::CTA_APPROACH_FROM_RIGHT && obs_data.m_obs->heading < m_cts_cal.k_cta_diag_rear_heading_max &&
           obs_data.m_obs->heading > m_cts_cal.k_cta_diag_rear_heading_min)))) {
        // 对向斜穿目标增加校验时间，因为视角较大，会因为路口二轮车突然出现而误触发
        check(obs_data.m_obs->age > m_cts_cal.k_cta_min_object_age_for_diagonal_tgt, CTS_INVALID_AGE);
    } else {
        check(obs_data.m_obs->age > m_cts_cal.k_cta_min_object_age_in_cycles, CTS_INVALID_AGE);
    }

    // 速度校验
    check(obs_data.m_obs->speed >= min_speed_obj, CTS_INVALID_SPEED);

    // 航向角区间校验
    check(obs_data.m_obs->heading >= min_hdg_obj && obs_data.m_obs->heading <= max_hdg_obj, CTS_INVALID_HEADING_RANGE);

    // 横向靠近速度校验
    check(fabs(obs_data.m_relative_velocity.y) >= min_lat_approach_spd, CTS_INVALID_LATERAL_APPROACH_SPEED);

    // 方向校验
    check(obs_data.m_approach_side != CTA_APPROACH_UNDEFINED, CTS_INVALID_APPROACH_SIDE);

    // 航向角滤波器/角度偏差校验
    check((obs_data.m_obs->speed > m_cts_cal.k_cta_object_heading_filter_max_speed_thres) ||
              (fabs(obs_data.m_angle_diff) < m_cts_cal.k_cta_object_max_angle_diff), CTS_INVALID_HEADING_FILTER);

    bool no_overlap_chk = true;
    size_t side = static_cast<size_t>(obs_data.m_approach_side);
    if (side < warn_info.size() && warn_info[side].obs_fusId != obs_data.m_obs->fus_trkID) {
        for (const math::Point2D &pt : obs_data.m_corner_pts) {
            if (fabs(pt.y) < m_cts_cal.k_cta_overlap_check_lat_thres) {
                no_overlap_chk = false;
                break;
            }
        }
        if (no_overlap_chk) {
            bool has_left_corner = false;
            bool has_right_corner = false;

            for (int i = 0; i < 4; ++i) {
                int corner_idx = 2 * i;
                const math::Point2D &pt = obs_data.m_corner_pts[corner_idx];
                if (pt.y > 0.0f) {
                    has_left_corner = true;
                } else if (pt.y < 0.0f) {
                    has_right_corner = true;
                }
            }

            if (has_left_corner && has_right_corner) {
                no_overlap_chk = false;
            }
        }
    }

    check(no_overlap_chk, CTS_INVALID_OVERLAP);

    check(!((obs_data.m_obs->f_is_motor_vehicle || obs_data.m_obs->f_is_bicycle) && obs_data.m_obs->f_turning), CTS_INVALID_TURNING);

    if (obs_attr.last_level == 0) {
        // 对于斜穿目标，在可视范围内则筛除.
        if ((obs_attr.direction == CtsDirection::FRONT &&
             ((obs_data.m_approach_side == ObsApproachSide::CTA_APPROACH_FROM_LEFT &&
               obs_data.m_obs->heading < -m_cts_cal.k_cta_visible_diag_heading_min && obs_data.m_obs->heading > -m_cts_cal.k_cta_visible_diag_heading_max) ||
              (obs_data.m_approach_side == ObsApproachSide::CTA_APPROACH_FROM_RIGHT &&
               obs_data.m_obs->heading > m_cts_cal.k_cta_visible_diag_heading_min &&
               obs_data.m_obs->heading < m_cts_cal.k_cta_visible_diag_heading_max))) &&
            fabs(vse_out.yawrate) < m_cts_cal.k_cta_yawrate_thres) {
            float azimuth = std::atan2(obs_data.m_obs->lat_posn, obs_data.m_obs->long_posn);
            float abs_azimuth = std::abs(azimuth);
            if (obs_data.m_obs->long_posn > m_cts_cal.k_cta_visible_long_dist_thres && abs_azimuth < m_cts_cal.k_cta_visible_azimuth_thres) {
                check(false, CTS_INVALID_VISIBLE_DIAGONAL);
            }
        }
    }

    if (fabs(atan2(obs_data.m_obs->lat_vel, obs_data.m_obs->long_vel) - obs_data.m_obs->heading) > m_cts_cal.k_cta_heading_dev_thres) {
        // 对于运动目标，其航向角和感知输出角度有较大误差认为无效目标，主要发生在目标较多+FOV边缘场景
        check(false, CTS_INVALID_HEADING_DEVIATION);
    }

    // This check is evaluated even when an earlier check failed, so a target
    // can report PATH_CONFLICT together with its other rejection reasons.
    if (f_return) {
        check(CalculateObsDuringObsToHost(vse_out, obs_data), CTS_INVALID_PATH_CONFLICT);
    }

    return f_return;
}

} // namespace cts
} // namespace active_safety
