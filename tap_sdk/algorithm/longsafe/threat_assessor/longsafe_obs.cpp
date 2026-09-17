#include "longsafe_obs.h"

namespace active_safety {
namespace longsafe {
void LgSfObsData::Reset() {
    stationary   = false;
    oncoming     = false;
    cutin        = false;
    curve_motion = false;

    pred_decel      = 0.0F;
    lat_steer_accel = 0.0F;

    offs_lgt_long_pred             = 0.0F;
    offs_lat_long_pred             = 0.0F;
    offs_lgt_short_pred            = 0.0F;
    offs_lat_short_pred            = 0.0F;
    offs_lat_manoeuvre             = 0.0F;
    offs_lat_inpath_primary_target = 0.0F;
    offs_lgt_inpath_pred_edge      = 0.0F;
    offs_lat_inpath_pred_edge      = 0.0F;
    offs_lat_inpath_current        = 0.0F;
    offs_lat_intersection          = 0.0F;

    predict_traj_idx = MotionType::Default;
    predict_valid    = false;
    predict_valid_spd_ok           = false;
    predict_valid_pred_distance    = false;
    predict_valid_ttr_valid        = false;
    predict_valid_pred_type_valid  = false;
    inpath_current   = false;
    inpath_predict   = false;
    inpath_res       = false;
    pred_inpath_debug.Reset();
}

void LongSafeObject::Reset() {
    index     = -1;
    fus_trkID = 0;
    vis_trkID = 0;

    age        = 0.0F;
    lat_posn   = 20.0F;
    long_posn  = 200.0F;
    lat_vel    = 0.0F;
    long_vel   = 0.0F;
    lat_accel  = 0.0F;
    long_accel = 0.0F;
    curvature  = 0.0F;
    length     = 0.0F;
    width      = 0.0F;
    height     = 0.0F;
    heading    = 0.0F;
    speed      = 0.0F;
    accel      = 0.0F;
    ttr        = 100.0F;

    offs_lat_inpath_primary_target = 0.0F; // Estimate object pos inpath in ltap.
    offs_lgt_short_pred            = 0.0F; // Calc object inpath safe simple long acc needed for aeb.
    offs_lat_short_pred            = 0.0F; // Calc object inpath safe simple long/lat acc needed for aeb.

    stationary   = false;
    oncoming     = false;
    cutin        = false;
    curve_motion = false;

    man_type = 0;
    inpath_current   = false;
    inpath_predict   = false;
}

void LongSafeObject::Update(const LgSfObsData &obs_data) {
    index     = obs_data.obs->track_id;
    fus_trkID = obs_data.obs->fus_trkID;
    vis_trkID = obs_data.obs->vis_trkID;
    
    type       = obs_data.obs->object_class;
    age        = obs_data.obs->age;
    lat_posn   = obs_data.obs->lat_posn;
    long_posn  = obs_data.obs->long_posn;
    lat_vel    = obs_data.obs->lat_vel;
    long_vel   = obs_data.obs->long_vel;
    lat_accel  = obs_data.obs->lat_accel;
    long_accel = obs_data.obs->long_accel;
    curvature  = obs_data.obs->curvature;
    length     = obs_data.obs->length;
    width      = obs_data.obs->width;
    height     = obs_data.obs->height;
    heading    = obs_data.obs->heading;
    speed      = obs_data.obs->speed;
    accel      = obs_data.obs->accel;
    ttr        = obs_data.pred_info[0].ttr;

    offs_lat_inpath_primary_target = obs_data.offs_lat_inpath_primary_target;
    offs_lgt_short_pred            = obs_data.offs_lgt_short_pred;
    offs_lat_short_pred            = obs_data.offs_lat_short_pred;

    stationary   = obs_data.stationary;
    oncoming     = obs_data.oncoming;
    cutin        = obs_data.cutin;
    curve_motion = obs_data.curve_motion;

    man_type     =   obs_data.mans_type;
    inpath_current = obs_data.inpath_current;
    inpath_predict = obs_data.inpath_predict;
}

} // namespace longsafe
} // namespace active_safety
