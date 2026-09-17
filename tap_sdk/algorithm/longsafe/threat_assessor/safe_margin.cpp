#include "safe_margin.h"

namespace active_safety {
namespace longsafe {
SafeMargin::SafeMargin() {
}
SafeMargin::~SafeMargin() = default;
SafeMarginCal SafeMargin::safemargin_cal_{};

void SafeMargin::CalculateSafeMargin(const AsVseOut &vse_out, LgSfObsData &obs_data, bool clamp_inpath_pred_offsets) {
    CalcLongPredTimeOffset(obs_data, vse_out.vcs_long_vel);
    CalcShortPredTimeOffset(obs_data, vse_out.vcs_long_vel, vse_out.config.k_dist_to_rear_axle, vse_out.aeb_active, vse_out.straight_driving);
    CalcLateralManoeuverOffset(obs_data, vse_out.vcs_long_vel);
    CalcLateralIntersectionOffset(obs_data, vse_out.vcs_long_vel);
    CalcLatInPathOffsetForLtap(obs_data);
    CalcInPathOffset(vse_out, obs_data, clamp_inpath_pred_offsets);
    CalcBoundingBox(obs_data);
}

void SafeMargin::CalcInPathOffset(const AsVseOut &vse_out, LgSfObsData &obs_data, bool clamp_inpath_pred_offsets) {
    switch (obs_data.obs->object_class) {
        case ObjectClass::CAR:
            CalcCarInpathPredOffset(vse_out, obs_data);
            CalcCarInpathCurrOffset(vse_out, obs_data);
            break;
        case ObjectClass::UNIDENTIFIED_VEHICLE:
            break;
        case ObjectClass::TRUCK:
        case ObjectClass::BUS:
            CalcTruckBusInpathPredOffset(vse_out, obs_data);
            CalcTruckBusInpathCurrOffset(vse_out, obs_data);
            break;
        case ObjectClass::GOD:
            obs_data.offs_lgt_inpath_pred_edge = 0.0F;
            obs_data.offs_lat_inpath_pred_edge = -0.5F;
            CalcGodInpathCurrOffset(vse_out, obs_data);
            break;
        case ObjectClass::PEDESTRIAN:
            CalcPedInpathPredOffset(vse_out, obs_data);
            CalcPedInpathCurrOffset(vse_out, obs_data);
            break;
        case ObjectClass::TREE:
        case ObjectClass::POLE:
        case ObjectClass::ANIMAL:
            obs_data.offs_lgt_inpath_pred_edge = 0.0F;
            obs_data.offs_lat_inpath_pred_edge = -0.5F;
            obs_data.offs_lat_inpath_current = -0.5F;
            break;
        case ObjectClass::BICYCLE:
            CalcBikeInpathPredOffset(vse_out, obs_data);
            CalcBikeInpathCurrOffset(vse_out, obs_data);
            break;

        case ObjectClass::CONE:
        case ObjectClass::GENOBJ:
            obs_data.offs_lgt_inpath_pred_edge = 0.0F;
            obs_data.offs_lat_inpath_pred_edge = -0.5F;
            CalcGenobjInpathCurrOffset(vse_out, obs_data);
            break;

        case ObjectClass::THREEWHEEl_VEHICLE:
            obs_data.offs_lgt_inpath_pred_edge = 0.0F;
            obs_data.offs_lat_inpath_pred_edge = -0.2F;
            obs_data.offs_lat_inpath_current   = -0.2F;
            break;

        case ObjectClass::MOTORCYCLE:
        case ObjectClass::ESCOOTER:
            CalcMotorBikeInpathPredOffset(vse_out, obs_data);
            CalcMotorBikeInpathCurrOffset(vse_out, obs_data);
            break;
            
        default:
            obs_data.offs_lgt_inpath_pred_edge = 0.0F;
            obs_data.offs_lat_inpath_pred_edge = -0.3F;
            obs_data.offs_lat_inpath_current   = -0.3F;
            break;
    }
    if (obs_data.select_target) {
        //当目标被选中后，则放宽其释放条件
        obs_data.offs_lgt_inpath_pred_edge *= 1.1F;
        if (obs_data.offs_lat_inpath_pred_edge < 0.0F) {
            obs_data.offs_lat_inpath_pred_edge *= 0.85F;
        }
        if (obs_data.offs_lat_inpath_current < 0.0F) {
            obs_data.offs_lat_inpath_current *= 0.85F;
        }
    }

    if (clamp_inpath_pred_offsets) {
        obs_data.offs_lat_inpath_pred_edge = fmaxf(obs_data.offs_lat_inpath_pred_edge, 0.0F);
        obs_data.offs_obs_lat_pred = fmaxf(obs_data.offs_obs_lat_pred, 0.0F);
    }
}

void SafeMargin::CalcPedInpathPredOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    float rel_lgt_vel = obs_data.stationary ? vse_out.vcs_long_vel : (vse_out.vcs_long_vel - obs_data.obs->long_vel);
    float lgt_pos = obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle;

    if (fabsf(vse_out.rear_curvature_radius) < 100.0f) {
        obs_data.offs_lat_inpath_pred_edge = LookUpTable::LookupTable2D<10, 11>(
            safemargin_cal_.k_inpath_host_spd_x, safemargin_cal_.k_inpath_veh_oncoming_turning_lgtpos_x,
            safemargin_cal_.k_inpath_ped_turning_lat_pred_offs, vse_out.speed, lgt_pos);
        obs_data.offs_obs_lat_pred = LookUpTable::LookupTable2D<10, 11>(
            safemargin_cal_.k_inpath_host_spd_x, safemargin_cal_.k_inpath_veh_oncoming_turning_lgtpos_x,
            safemargin_cal_.k_inpath_ped_obs_lat_turning_pred_offs, vse_out.speed, lgt_pos);
    } else {
        obs_data.offs_lat_inpath_pred_edge = LookUpTable::LookupTable2D<10, 10>(
            safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
            safemargin_cal_.k_inpath_ped_lat_pred_offs, lgt_pos, rel_lgt_vel);
        obs_data.offs_obs_lat_pred = LookUpTable::LookupTable2D<10, 10>(
            safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
            safemargin_cal_.k_inpath_ped_obs_lat_pred_offs, lgt_pos, rel_lgt_vel);
    }

    obs_data.offs_lgt_inpath_pred_edge = 0.0F;
    if (obs_data.aeb_atv_target) {
        obs_data.offs_obs_lat_pred = 0.3;
        obs_data.offs_lat_inpath_pred_edge = fmax(safemargin_cal_.k_inpath_lat_pred_max, obs_data.offs_lat_inpath_pred_edge);
        obs_data.offs_lgt_inpath_pred_edge = fmax(safemargin_cal_.k_inpath_long_pred_max, obs_data.offs_lgt_inpath_pred_edge);
    }
}

void SafeMargin::CalcPedInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    float rel_lgt_vel = obs_data.stationary ? vse_out.vcs_long_vel : (vse_out.vcs_long_vel - obs_data.obs->long_vel);

    obs_data.offs_lat_inpath_current = LookUpTable::LookupTable2D<10, 10>(safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
                                                                          safemargin_cal_.k_inpath_ped_lat_curr_offs,
                                                                          obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle, rel_lgt_vel);
}

void SafeMargin::CalcGenobjInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    float rel_lgt_vel = vse_out.vcs_long_vel; 

    obs_data.offs_lat_inpath_current = LookUpTable::LookupTable2D<10, 10>(safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
                                                                          safemargin_cal_.k_inpath_genobj_lat_curr_offs,
                                                                          obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle, rel_lgt_vel);
}

void SafeMargin::CalcBikeInpathPredOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    float rel_lgt_vel = obs_data.stationary ? vse_out.vcs_long_vel : (vse_out.vcs_long_vel - obs_data.obs->long_vel);
    float lgt_pos = obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle;

    if (fabsf(vse_out.rear_curvature_radius) < 100.0f) {
        obs_data.offs_lat_inpath_pred_edge = LookUpTable::LookupTable2D<10, 11>(
            safemargin_cal_.k_inpath_host_spd_x, safemargin_cal_.k_inpath_veh_oncoming_turning_lgtpos_x,
            safemargin_cal_.k_inpath_ebike_turning_lat_pred_offs, vse_out.speed, lgt_pos);
        obs_data.offs_obs_lat_pred = LookUpTable::LookupTable2D<10, 11>(
            safemargin_cal_.k_inpath_host_spd_x, safemargin_cal_.k_inpath_veh_oncoming_turning_lgtpos_x,
            safemargin_cal_.k_inpath_ebike_obs_lat_turning_pred_offs, vse_out.speed, lgt_pos);
    } else {
        obs_data.offs_lat_inpath_pred_edge = LookUpTable::LookupTable2D<10, 10>(
            safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
            safemargin_cal_.k_inpath_bike_lat_pred_offs, lgt_pos, rel_lgt_vel);
        obs_data.offs_obs_lat_pred = LookUpTable::LookupTable2D<10, 10>(
            safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
            safemargin_cal_.k_inpath_bike_obs_lat_pred_offs, lgt_pos, rel_lgt_vel);
          
    }

    obs_data.offs_lgt_inpath_pred_edge = 0.0F;
    obs_data.offs_lat_inpath_pred_edge = 0.0F;
    obs_data.offs_obs_lat_pred = 0.0F;
    if (obs_data.aeb_atv_target) {
        obs_data.offs_obs_lat_pred = 0.3;
        obs_data.offs_lat_inpath_pred_edge = fmax(safemargin_cal_.k_inpath_lat_pred_max, obs_data.offs_lat_inpath_pred_edge);
        obs_data.offs_lgt_inpath_pred_edge = fmax(safemargin_cal_.k_inpath_long_pred_max, obs_data.offs_lgt_inpath_pred_edge);
    }
}

void SafeMargin::CalcBikeInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    float rel_lgt_vel = obs_data.stationary ? vse_out.vcs_long_vel : (vse_out.vcs_long_vel - obs_data.obs->long_vel);

    obs_data.offs_lat_inpath_current = LookUpTable::LookupTable2D<10, 10>(safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
                                                                          safemargin_cal_.k_inpath_bike_lat_curr_offs,
                                                                          obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle, rel_lgt_vel);
}

void SafeMargin::CalcGodInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    float rel_lgt_vel = obs_data.stationary ? vse_out.vcs_long_vel : (vse_out.vcs_long_vel - obs_data.obs->long_vel);

    obs_data.offs_lat_inpath_current = LookUpTable::LookupTable2D<10, 10>(safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
                                                                          safemargin_cal_.k_inpath_god_lat_curr_offs,
                                                                          obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle, rel_lgt_vel);
}

void SafeMargin::CalcCarInpathPredOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    float rel_lgt_vel = obs_data.stationary ? vse_out.vcs_long_vel : (vse_out.vcs_long_vel - obs_data.obs->long_vel);
    float lgt_pos = obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle;

    // 自车转弯场景（曲率半径<100m）且目标物为oncoming类型，根据自车合速度和距离查表
    if (fabsf(vse_out.rear_curvature_radius) < 100.0f && obs_data.oncoming) {
        obs_data.offs_lat_inpath_pred_edge = LookUpTable::LookupTable2D<10, 11>(
            safemargin_cal_.k_inpath_host_spd_x, safemargin_cal_.k_inpath_veh_oncoming_turning_lgtpos_x,
            safemargin_cal_.k_inpath_veh_oncoming_turning_lat_pred_offs, vse_out.speed, lgt_pos);
        obs_data.offs_obs_lat_pred = LookUpTable::LookupTable2D<10, 11>(
            safemargin_cal_.k_inpath_host_spd_x, safemargin_cal_.k_inpath_veh_oncoming_turning_lgtpos_x,
            safemargin_cal_.k_inpath_veh_obs_lat_turning_pred_offs, vse_out.speed, lgt_pos);
    } else {
        obs_data.offs_lat_inpath_pred_edge = LookUpTable::LookupTable2D<10, 10>(
            safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
            safemargin_cal_.k_inpath_veh_lat_pred_offs, lgt_pos, rel_lgt_vel);
        obs_data.offs_obs_lat_pred = LookUpTable::LookupTable2D<10, 10>(
            safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
            safemargin_cal_.k_inpath_veh_obs_lat_pred_offs, lgt_pos, rel_lgt_vel);
    }

    obs_data.offs_lgt_inpath_pred_edge = 0.0F;
    if (obs_data.aeb_atv_target) {
        obs_data.offs_obs_lat_pred = 0.3;
        obs_data.offs_lat_inpath_pred_edge = fmax(safemargin_cal_.k_inpath_lat_pred_max, obs_data.offs_lat_inpath_pred_edge);
        obs_data.offs_lgt_inpath_pred_edge = fmax(safemargin_cal_.k_inpath_long_pred_max, obs_data.offs_lgt_inpath_pred_edge);
    }
}

void SafeMargin::CalcCarInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    obs_data.offs_lat_inpath_current = LookUpTable::LookupTable1D<10>(safemargin_cal_.k_inpath_posnlgt_veh, safemargin_cal_.k_inpath_posnlgt_veh_offs,
                                                                      obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle);
}

void SafeMargin::CalcTruckBusInpathPredOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    float rel_lgt_vel = obs_data.stationary ? vse_out.vcs_long_vel : (vse_out.vcs_long_vel - obs_data.obs->long_vel);

    float offs_range_rel_vel = LookUpTable::LookupTable2D<10, 10>(safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
                                                                  safemargin_cal_.k_inpath_truck_lat_pred_offs,
                                                                  obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle, rel_lgt_vel);

    obs_data.offs_lat_inpath_pred_edge = offs_range_rel_vel;
    obs_data.offs_lgt_inpath_pred_edge = 0.0F;
    if (obs_data.aeb_atv_target) {
        obs_data.offs_lat_inpath_pred_edge = fmax(safemargin_cal_.k_inpath_lat_pred_max, obs_data.offs_lat_inpath_pred_edge);
        obs_data.offs_lgt_inpath_pred_edge = fmax(safemargin_cal_.k_inpath_long_pred_max, obs_data.offs_lgt_inpath_pred_edge);
    }
}

void SafeMargin::CalcTruckBusInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    obs_data.offs_lat_inpath_current = LookUpTable::LookupTable1D<10>(safemargin_cal_.k_inpath_posnlgt_truck, safemargin_cal_.k_inpath_posnlgt_truck_offs,
                                                                      obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle);
}

void SafeMargin::CalcMotorBikeInpathPredOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    float rel_lgt_vel = obs_data.stationary ? vse_out.vcs_long_vel : (vse_out.vcs_long_vel - obs_data.obs->long_vel);
    float lgt_pos = obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle;

    if (fabsf(vse_out.rear_curvature_radius) < 100.0f) {
        obs_data.offs_lat_inpath_pred_edge = LookUpTable::LookupTable2D<10, 11>(
            safemargin_cal_.k_inpath_host_spd_x, safemargin_cal_.k_inpath_veh_oncoming_turning_lgtpos_x,
            safemargin_cal_.k_inpath_ebike_turning_lat_pred_offs, vse_out.speed, lgt_pos);
        obs_data.offs_obs_lat_pred = LookUpTable::LookupTable2D<10, 11>(
            safemargin_cal_.k_inpath_host_spd_x, safemargin_cal_.k_inpath_veh_oncoming_turning_lgtpos_x,
            safemargin_cal_.k_inpath_ebike_obs_lat_turning_pred_offs, vse_out.speed, lgt_pos);
    } else {
        obs_data.offs_lat_inpath_pred_edge = LookUpTable::LookupTable2D<10, 10>(
            safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
            safemargin_cal_.k_inpath_ebike_lat_pred_offs, lgt_pos, rel_lgt_vel);
        obs_data.offs_obs_lat_pred = LookUpTable::LookupTable2D<10, 10>(
            safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
            safemargin_cal_.k_inpath_ebike_obs_lat_pred_offs, lgt_pos, rel_lgt_vel);
    }

    obs_data.offs_lgt_inpath_pred_edge = 0.0F;
    obs_data.offs_lat_inpath_pred_edge = 0.0F;
    obs_data.offs_obs_lat_pred = 0.0F;
    if (obs_data.aeb_atv_target) {
        obs_data.offs_obs_lat_pred = 0.3;
        obs_data.offs_lat_inpath_pred_edge = fmax(safemargin_cal_.k_inpath_lat_pred_max, obs_data.offs_lat_inpath_pred_edge);
        obs_data.offs_lgt_inpath_pred_edge = fmax(safemargin_cal_.k_inpath_long_pred_max, obs_data.offs_lgt_inpath_pred_edge);
    }
}

void SafeMargin::CalcMotorBikeInpathCurrOffset(const AsVseOut &vse_out, LgSfObsData &obs_data) {
    float rel_lgt_vel = obs_data.stationary ? vse_out.vcs_long_vel : (vse_out.vcs_long_vel - obs_data.obs->long_vel);

    obs_data.offs_lat_inpath_current = LookUpTable::LookupTable2D<10, 10>(safemargin_cal_.k_inpath_lgtpos_x, safemargin_cal_.k_inpath_rel_lgtvel_x,
                                                                          safemargin_cal_.k_inpath_ebike_lat_curr_offs,
                                                                          obs_data.obs->long_posn - vse_out.config.k_dist_to_rear_axle, rel_lgt_vel);
}

void SafeMargin::CalcBoundingBox(LgSfObsData &obs_data) {
    CalcObjLength(obs_data);
    CalcObjWidth(obs_data);
}

void SafeMargin::CalcObjLength(LgSfObsData &obs_data) {
    switch (obs_data.obs->object_class) {
        case ObjectClass::CAR: {
            obs_data.side_length = safemargin_cal_.k_car_length;
            break;
        }
        case ObjectClass::UNIDENTIFIED_VEHICLE: {
            obs_data.side_length = safemargin_cal_.k_veh_unknown_length;
            break;
        }
        case ObjectClass::MOTORCYCLE: {
            obs_data.side_length = safemargin_cal_.k_motorcycle_length;
            break;
        }
        case ObjectClass::ESCOOTER:
        case ObjectClass::BICYCLE: {
            if (obs_data.obs->speed > safemargin_cal_.k_bike_low_thd) {
                obs_data.side_length = safemargin_cal_.k_bicycle_length;
            } else {
                obs_data.side_length = 0.01F;
            }
            if (obs_data.aeb_atv_target) {
                obs_data.side_length += 0.5F;
            }
            break;
        }
        case ObjectClass::TRUCK:
        case ObjectClass::BUS: {
            obs_data.side_length = (obs_data.obs->length < safemargin_cal_.k_truck_length) ? obs_data.obs->length : safemargin_cal_.k_truck_length;
            break;
        }
        case ObjectClass::PEDESTRIAN:
        case ObjectClass::ANIMAL:
        case ObjectClass::GENOBJ:
        case ObjectClass::UNDETERMINED: {
            obs_data.side_length = 0.01F;
            if (obs_data.aeb_atv_target) {
                obs_data.side_length += 0.5F;
            }
            break;
        }
        case ObjectClass::GOD: {
            obs_data.side_length = fmin(obs_data.obs->length, safemargin_cal_.k_barrier_max_length);
            break;
        }
        default: {
            obs_data.side_length = 0.0F;
            break;
        }
    }
}

void SafeMargin::CalcObjWidth(LgSfObsData &obs_data) {
    switch (obs_data.obs->object_class) {
        case ObjectClass::CAR:
        case ObjectClass::TRUCK:
        case ObjectClass::MOTORCYCLE:
        case ObjectClass::UNIDENTIFIED_VEHICLE:
        case ObjectClass::BUS: {
            obs_data.side_width = obs_data.obs->width;
            break;
        }
        case ObjectClass::ESCOOTER:
        case ObjectClass::BICYCLE: {
         
             obs_data.side_width = fmin(obs_data.obs->width,safemargin_cal_.k_bike_width);

            if (obs_data.aeb_atv_target) {
                obs_data.side_width += 0.5F;
            }
            break;
        }
        case ObjectClass::PEDESTRIAN:
        case ObjectClass::ANIMAL:
        case ObjectClass::GENOBJ:
        case ObjectClass::UNDETERMINED: {
            obs_data.side_width = 0.01F;
            if (obs_data.aeb_atv_target) {
                obs_data.side_width += 0.5F;
            }
            break;
        }
        case ObjectClass::GOD: {
            obs_data.side_width = fmin(obs_data.obs->width, safemargin_cal_.k_barrier_max_width);
            break;
        }
        default: {
            obs_data.side_width = 0.0F;
            break;
        }
    }
}

void SafeMargin::CalcLatInPathOffsetForLtap(LgSfObsData &obs_data) {
    switch (obs_data.obs->object_class) {
        case ObjectClass::PEDESTRIAN:
        case ObjectClass::ANIMAL:
        case ObjectClass::GENOBJ:
        case ObjectClass::BICYCLE:
        case ObjectClass::ESCOOTER: {
            obs_data.offs_lat_inpath_primary_target = safemargin_cal_.k_inpath_ltap_latoffs_veh + obs_data.obs->width * 0.5F;
            break;
        }
        case ObjectClass::CAR:
        case ObjectClass::TRUCK:
        case ObjectClass::MOTORCYCLE:
        case ObjectClass::UNIDENTIFIED_VEHICLE: {
            obs_data.offs_lat_inpath_primary_target = safemargin_cal_.k_inpath_ltap_latoffs_veh;
            break;
        }

        default: {
            obs_data.offs_lat_inpath_primary_target = 0.0F;
            break;
        }
    }
}

void SafeMargin::CalcLongPredTimeOffset(LgSfObsData &obs_data, float host_long_vel) {
    float rel_lgt_vel = obs_data.obs->long_vel - host_long_vel;
    switch (obs_data.obs->object_class) {
        case ObjectClass::PEDESTRIAN:
        case ObjectClass::ANIMAL:
        case ObjectClass::GENOBJ:
        case ObjectClass::BICYCLE:
        case ObjectClass::ESCOOTER: {
            float k_longlgt_vlgt_vru_offs =
                LookUpTable::LookupTable1D<8>(safemargin_cal_.k_longlgt_vlgtrel, safemargin_cal_.k_longlgt_vlgt_vru_offs, rel_lgt_vel);

            float longlat_vlgt_vlat_vru_offs =
                LookUpTable::LookupTable2D<8, 8>(safemargin_cal_.k_longlat_vlgtrel, safemargin_cal_.k_longlat_vlatrel,
                                                 safemargin_cal_.k_longlat_vlgt_vlat_vru, rel_lgt_vel, fabsf(obs_data.obs->lat_vel));

            if (obs_data.obs->object_class == ObjectClass::PEDESTRIAN || obs_data.obs->object_class == ObjectClass::ANIMAL ||
                obs_data.obs->object_class == ObjectClass::GENOBJ) {
                longlat_vlgt_vlat_vru_offs += obs_data.obs->width * 0.5;
            }

            obs_data.offs_lgt_long_pred = k_longlgt_vlgt_vru_offs;
            obs_data.offs_lat_long_pred = longlat_vlgt_vlat_vru_offs;
            break;
        }
        case ObjectClass::CAR:
        case ObjectClass::TRUCK:
        case ObjectClass::MOTORCYCLE:
        case ObjectClass::UNIDENTIFIED_VEHICLE: {
            float k_longlgt_vlgt_veh_offs =
                LookUpTable::LookupTable1D<8>(safemargin_cal_.k_longlgt_vlgtrel, safemargin_cal_.k_longlgt_vlgt_veh_offs, rel_lgt_vel);

            float longlat_alat_veh_offs =
                LookUpTable::LookupTable1D<9>(safemargin_cal_.k_longlat_algtraw, safemargin_cal_.k_longlat_algt_veh_offs, obs_data.obs->long_accel);

            float longlat_vlgt_vlat_veh_offs =
                LookUpTable::LookupTable2D<8, 8>(safemargin_cal_.k_longlat_vlgtrel, safemargin_cal_.k_longlat_vlatabs,
                                                 safemargin_cal_.k_longlat_vlgt_vlat_veh, rel_lgt_vel, fabsf(obs_data.obs->lat_vel));
            obs_data.offs_lgt_long_pred = k_longlgt_vlgt_veh_offs;
            obs_data.offs_lat_long_pred = longlat_alat_veh_offs + longlat_vlgt_vlat_veh_offs;
            break;
        }

        default: {
            obs_data.offs_lgt_long_pred = 0.0F;
            obs_data.offs_lat_long_pred = 0.0F;
            break;
        }
    }
}

void SafeMargin::CalcShortPredTimeOffset(LgSfObsData &obs_data, float host_long_vel, float host_dist_to_front, bool aeb_active,
                                         bool straight_driving) {
    float rel_lgt_vel = fabs(obs_data.obs->long_vel - host_long_vel);
    if (obs_data.stationary) {
        rel_lgt_vel = fabs(host_long_vel);
    }
    // long offset for brake distance.
    float k_shortlgt_vlgt_offs = LookUpTable::LookupTable1D<9>(safemargin_cal_.k_shortlgt_vlgtrel, safemargin_cal_.k_shortlgt_vlgt_offs, rel_lgt_vel);

    // lat offset for vru.
    float shortlat_vlgt_vlat_vru_offs =
        LookUpTable::LookupTable2D<8, 8>(safemargin_cal_.k_shortlat_vlgtrel, safemargin_cal_.k_shortlat_vlatabs,
                                         safemargin_cal_.k_shortlat_vlgt_vlat_vru, rel_lgt_vel, fabs(obs_data.obs->lat_vel));
    // lat offset for two wheel.
    float shortlat_vlgt_vlat_cyclist_offs =
        LookUpTable::LookupTable2D<8, 8>(safemargin_cal_.k_shortlat_vlgtrel_cyclist, safemargin_cal_.k_shortlat_vlatabs_cyclist,
                                         safemargin_cal_.k_shortlat_vlgt_vlat_cyclist, rel_lgt_vel, fabs(obs_data.obs->lat_vel));
    // lat offset for four wheel car.
    float k_shortlat_algt_veh_offs =
        LookUpTable::LookupTable1D<9>(safemargin_cal_.k_shortlat_algtabs, safemargin_cal_.k_shortlat_algt_veh_offs, obs_data.obs->long_accel);

    // lat offset for car.
    float shortlat_vlgt_vlat_veh_offs =
        LookUpTable::LookupTable2D<8, 8>(safemargin_cal_.k_shortlat_vlgtrel_veh, safemargin_cal_.k_shortlat_vlatrel_veh,
                                         safemargin_cal_.k_shortlat_vlgt_vlat_veh, rel_lgt_vel, fabs(obs_data.obs->lat_vel));

    switch (obs_data.obs->object_class) {
        case ObjectClass::PEDESTRIAN:
        case ObjectClass::ANIMAL:
        case ObjectClass::GENOBJ: {
            obs_data.offs_lgt_short_pred = k_shortlgt_vlgt_offs;
            obs_data.offs_lat_short_pred = shortlat_vlgt_vlat_vru_offs + 0.5F * obs_data.obs->width;
            break;
        }
        case ObjectClass::BICYCLE: {
            obs_data.offs_lgt_short_pred = k_shortlgt_vlgt_offs;
            obs_data.offs_lat_short_pred = shortlat_vlgt_vlat_cyclist_offs;
            break;
        }
        case ObjectClass::MOTORCYCLE:
        case ObjectClass::ESCOOTER: {
            obs_data.offs_lgt_short_pred = k_shortlgt_vlgt_offs;
            obs_data.offs_lat_short_pred = k_shortlat_algt_veh_offs + shortlat_vlgt_vlat_cyclist_offs;
            break;
        }

        case ObjectClass::CAR:
        case ObjectClass::TRUCK:
        case ObjectClass::UNIDENTIFIED_VEHICLE: {
            obs_data.offs_lgt_short_pred = k_shortlgt_vlgt_offs;
            obs_data.offs_lat_short_pred = k_shortlat_algt_veh_offs + shortlat_vlgt_vlat_veh_offs;
            break;
        }
        default: {
            obs_data.offs_lgt_short_pred = 0.0F;
            obs_data.offs_lat_short_pred = 0.0F;
            break;
        }
    }
}

void SafeMargin::CalcLateralManoeuverOffset(LgSfObsData &obs_data, float host_long_vel) {
    switch (obs_data.obs->object_class) {
        case ObjectClass::PEDESTRIAN:
        case ObjectClass::ANIMAL:
        case ObjectClass::GENOBJ: {
            obs_data.offs_lat_manoeuvre =
                0.5F * obs_data.obs->width +
                LookUpTable::LookupTable1D<8>(safemargin_cal_.k_manv_vlgt_ego, safemargin_cal_.k_manv_latoffs_vru, host_long_vel);
            break;
        }
        case ObjectClass::BICYCLE: {
            obs_data.offs_lat_manoeuvre =
                LookUpTable::LookupTable1D<8>(safemargin_cal_.k_manv_vlgt_ego, safemargin_cal_.k_manv_latoffs_bike, host_long_vel);
            break;
        }
        case ObjectClass::CAR:
        case ObjectClass::TRUCK:
        case ObjectClass::MOTORCYCLE:
        case ObjectClass::ESCOOTER:
        case ObjectClass::UNIDENTIFIED_VEHICLE: {
            float vlgt_rel = host_long_vel - obs_data.obs->long_vel;
            obs_data.offs_lat_manoeuvre =
                LookUpTable::LookupTable1D<8>(safemargin_cal_.k_manv_vlgt_rel, safemargin_cal_.k_manv_latoffs_veh, vlgt_rel);
            break;
        }
        default: {
            obs_data.offs_lat_manoeuvre = 0.0F;
            break;
        }
    }
}

void SafeMargin::CalcLateralIntersectionOffset(LgSfObsData &obs_data, float host_long_vel) {
    float vlgt_rel = obs_data.obs->long_vel - host_long_vel;

    obs_data.offs_lat_intersection =
        LookUpTable::LookupTable1D<8>(safemargin_cal_.k_intersec_vlgtrel, safemargin_cal_.k_intersec_latoffs_all, vlgt_rel);
}

} // namespace longsafe
} // namespace active_safety
