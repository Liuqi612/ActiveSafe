#ifndef TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_LONGSAFE_OBS_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_LONGSAFE_OBS_H_
#include "algorithm/longsafe/longsafe_cals.h"
#include "algorithm/obstacle/obstacle.h"
#include "motion_predict_types.h"

#include <memory>
namespace active_safety {
namespace longsafe {
enum ObsMotionMantype {
    CROSS_LEAN_TO_STRAIGHT_BY_SPD = 1 << 0,
};

enum class PredInpathFailReason {
    NONE = 0,
    LGT_OUT_OF_RANGE,
    LAT_OUT_OF_RANGE,
    OBS_LGT_OUT_OF_RANGE,
    OBS_LAT_OUT_OF_RANGE,
};

struct CornerPoints {
    float corner_fl_lgt;
    float corner_fl_lat;
    float corner_fr_lgt;
    float corner_fr_lat;
    float corner_rl_lgt;
    float corner_rl_lat;
    float corner_rr_lgt;
    float corner_rr_lat;
    float corved_corner_fl_lat;
    float corved_corner_fr_lat;
    float corved_corner_rl_lat;
    float corved_corner_rr_lat;

    CornerPoints()
        : corner_fl_lgt(0.0F), corner_fl_lat(0.0F), corner_fr_lgt(0.0F), corner_fr_lat(0.0F), corner_rl_lgt(0.0F), corner_rl_lat(0.0F),
          corner_rr_lgt(0.0F), corner_rr_lat(0.0F), corved_corner_fl_lat(0.0F), corved_corner_fr_lat(0.0F), corved_corner_rl_lat(0.0F),
          corved_corner_rr_lat(0.0F) {}
};

class LgSfObsData {
  public:
    LgSfObsData() { obs = std::make_shared<AsObstacle>(); }
    std::shared_ptr<AsObstacle> obs = nullptr;

    CornerPoints corner_pt_;
    float xoxp_meas;
    // Motion behavior.
    bool use_moving_heading = false;
    bool stationary = false;
    bool oncoming = false;
    bool curve_motion = false;
    bool cutin = false;
    float cutin_prob = 0.0F;

    uint32_t mans_type;
    // Latdist info.
    float lat_dist_to_host = 5.0F;
    // Latvel info.
    float lat_vel_to_host = 0.0F;
    // Ttlc info.
    float ttlc = 0.0F;
    // Heading info.
    float heading_to_host = 0.0F;

    bool will_brake = false;
    bool will_left_steer = false;
    bool will_right_steer = false;

    // Avoidance behavior.
    float pred_decel = 0.0F;      // predicted deceleration
    float lat_steer_accel = 0.0F; // lateral steering acceleration

    // SafeMargin.
    float offs_lgt_long_pred = 0.0F;             // Calc object inpath safe simple long acc needed for fcw.
    float offs_lat_long_pred = 0.0F;             // Calc object inpath safe simple long/lat acc needed for fcw.
    float offs_lgt_short_pred = 0.0F;            // Calc object inpath safe simple long acc needed for aeb.
    float offs_lat_short_pred = 0.0F;            // Calc object inpath safe simple long/lat acc needed for aeb.
    float offs_lat_manoeuvre = 0.0F;             // Object inpath judge if object has manoeuvre.
    float offs_lat_inpath_primary_target = 0.0F; // Estimate object pos inpath in ltap.
    float offs_lgt_inpath_pred_edge = 0.0F;      // Check predict relative long pos.
    float offs_lat_inpath_pred_edge = 0.0F;      // Check predict relative lat pos.
    float offs_lat_inpath_current = 0.0F;        // Check inpath current.
    float offs_obs_lat_pred = 0.0F;              // Check predict obs lat offset in obs coordinate.
    float offs_lat_intersection = 0.0F;          // For onComing or intersecting motor vehicle.
    // BoundingBox
    float side_length; // obs length for inpath
    float side_width;  // obs width for inpath

    // Predict and inpath info.
    std::array<MotionPredictInfo, 4> pred_info;
    // 0:default traj;
    // 1:decel traj;
    // 2:turn left traj;
    // 3:turn right traj;
    int predict_traj_idx = MotionType::Brake;
    bool predict_valid = false;
    // predict_valid 的子判据，便于排查目标为何未被选中
    bool predict_valid_spd_ok = false;
    bool predict_valid_pred_distance = false;
    bool predict_valid_ttr_valid = false;
    bool predict_valid_pred_type_valid = false;
    bool inpath_current = false;
    bool inpath_predict = false;
    PredInpathFailReason pred_inpath_fail_reason = PredInpathFailReason::NONE;
    PredInpathDebug pred_inpath_debug; // pred inpath 失败时各检查的中间量
    bool inpath_res = false;
    bool aeb_atv_target = false;
    bool select_target = false;

    void Reset();
};

struct LongSafeObject {
    int index = -1;
    int32_t fus_trkID = 0;
    int32_t vis_trkID = 0;
    ObjectClass type = ObjectClass::UNDETERMINED;
    float age = 0.0F;
    float lat_posn = 20.0F;
    float long_posn = 200.0F;
    float lat_vel = 0.0F;
    float long_vel = 0.0F;
    float lat_accel = 0.0F;
    float long_accel = 0.0F;
    float curvature = 0.0F;

    float length = 0.0F;
    float width = 0.0F;
    float height = 0.0F;
    float heading = 0.0F;

    float speed = 0.0F;
    float accel = 0.0F;

    float ttr = 100.0F;

    float offs_lat_inpath_primary_target = 0.0F; // Estimate object pos inpath in ltap.
    float offs_lgt_short_pred = 0.0F;            // Calc object inpath safe simple long acc needed for aeb.
    float offs_lat_short_pred = 0.0F;            // Calc object inpath safe simple long/lat acc needed for aeb.

    bool stationary = false;
    bool oncoming = false;
    bool cutin = false;
    bool curve_motion = false;

    bool inpath_current = false;
    bool inpath_predict = false;

    uint32_t man_type = 0;

    void Update(const LgSfObsData &obs_data);
    void Reset();
};

} // namespace longsafe
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_LONGSAFE_THREAT_ASSESSOR_LONGSAFE_OBS_H_
