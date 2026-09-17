#pragma once

#include <algorithm>
#include <boost/algorithm/clamp.hpp>
#include <boost/optional.hpp>
#include <chrono>
#include <utility>
#include <vector>

#include "math/piecewise_linear_function.h"
#include "math/vec2d.h"
#include "router/drive_passage.h"
#include "util/hmi_content_util.h"
#include "util/status_macros.h"

namespace pnc_x {
namespace planning {

namespace {
PiecewiseLinearFunction<double, double> evade_offset_damp_plf(
    {5.0, 10.0, 15.0, 20.0, 30.0, 40.0}, {1.0, 0.9, 0.8, 0.7, 0.6, 0.5});
}

struct LaneEvadeInfo {
    bool is_evade = false;
    bool is_ramp_out = false;
    bool is_large_vehicle_over_lane = false;
    bool is_large_vehicle_both_side = false;
    double offset = 0.0;
    boost::optional<NudgeObjectInfo> evade_obs = boost::none;

    void Reset() {
        is_evade = false;
        is_ramp_out = false;
        is_large_vehicle_over_lane = false;
        is_large_vehicle_both_side = false;
        offset = 0.0;
        evade_obs = boost::none;
    }
};

class LaneEvadeStatus {
 public:
    bool is_in_evade() const { return is_in_evade_; }
    bool is_ramp_out() const { return is_ramp_out_; }
    void set_is_in_evade(bool evad_status) { is_in_evade_ = evad_status; }
    void set_pr_in_evade(bool evad_status) { pr_in_evade_ = evad_status; }
    int enter_evade_count() { return enter_evade_count_; }
    void set_enter_evade_count(int count) { enter_evade_count_ = count; }
    int &quit_evade_count() { return quit_evade_count_; }

    int &shift_quit_count() { return shift_quit_count_; }

    int &quit_block_count() { return quit_block_count_; }

    int &shortest_evade_count() { return shortest_evade_count_; }

    std::string prev_obs_id() { return prev_obs_id_; }
    void set_prev_obs_id(std::string id) { prev_obs_id_ = id; }

    bool set_lat_offset(const FrenetBox &tar_sl_box,
                        const FrenetBox &ego_sl_box,
                        const double ego_v,
                        double safe_curb_dist,
                        double safe_dist,
                        double max_evade,
                        double min_evade,
                        bool is_chg_tar,
                        std::string *infos) {
        const double offset =
            std::min(std::fabs(tar_sl_box.l_max), std::fabs(tar_sl_box.l_min));
        double temp_lat_offset = 0.0;
        const double s_diff = tar_sl_box.s_min - ego_sl_box.s_max;
        const double speed_ratio = std::max(1.0, ego_v / 25.0);

        double offset_damp = evade_offset_damp_plf(s_diff);
        *infos += "origin: " + std::to_string(safe_dist - offset);

        temp_lat_offset =
            boost::algorithm::clamp((safe_dist - offset) * offset_damp,
                                    min_evade, max_evade * offset_damp);
        temp_lat_offset = std::min(temp_lat_offset * speed_ratio, max_evade);
        *infos += ", s_diff: " + std::to_string(s_diff) +
                  ", damp: " + std::to_string(offset_damp) +
                  ", minmax: " + std::to_string(temp_lat_offset);

        temp_lat_offset = std::min(temp_lat_offset, safe_curb_dist);
        *infos += ", curb: " + std::to_string(temp_lat_offset) + "\n";

        if (temp_lat_offset >= cur_lat_offset_ &&
            (cur_lat_offset_ < 1e-4 || is_chg_tar)) {
            cur_lat_offset_ = temp_lat_offset;
        }
        *infos += ", final: " + std::to_string(cur_lat_offset_) + "\n";

        return true;
    }

    void set_ramp_out(uint32_t ramp_out_thrs) {
        if ((pr_in_evade_ && !is_in_evade_) ||
            (ramp_out_count_ > 0 && ramp_out_count_ < ramp_out_thrs)) {
            ramp_out_count_++;
            is_ramp_out_ = true;
        } else {
            ramp_out_count_ = 0;
            is_ramp_out_ = false;
        }
    }

    void set_evade_obs(int i, const PlannerObject *obs) {
        NudgeObjectInfo evade_obs;
        evade_obs.id = obs->id();
        evade_obs.direction = (i == 0) ? 1 : -1;
        evade_obs.type = obs->type();
        evade_obs.is_stationary = obs->is_stationary();
        evade_obs.nudge_state = NudgeObjectInfo::NudgeState::NUDGE;

        evade_obs_ = std::move(evade_obs);
    }

    double cur_lat_offset() const { return cur_lat_offset_; }

    boost::optional<NudgeObjectInfo> evade_obs() const { return evade_obs_; };

    uint32_t ramp_out_count() const { return ramp_out_count_; };

    void reset_counter() {
        quit_evade_count_ = 0;
        shift_quit_count_ = 0;
        quit_block_count_ = 0;
        shortest_evade_count_ = 20;
    }

    void reset_status() {
        reset_counter();
        is_in_evade_ = false;
        enter_evade_count_ = 0;
        prev_obs_id_ = "";
        cur_lat_offset_ = 0.0;
        evade_obs_.reset();
    }

    void reset_ramp() {
        pr_in_evade_ = false;
        is_ramp_out_ = false;
        ramp_out_count_ = 0;
    }

 private:
    bool is_in_evade_ = false;
    bool pr_in_evade_ = false;
    bool is_ramp_out_ = false;
    uint32_t ramp_out_count_ = 0;
    int enter_evade_count_ = 0;
    int quit_evade_count_ = 0;
    int shift_quit_count_ = 0;
    int quit_block_count_ = 0;
    int shortest_evade_count_ = 20;
    std::string prev_obs_id_ = "";
    double cur_lat_offset_ = 0.0;
    boost::optional<NudgeObjectInfo> evade_obs_;
};

}  // namespace planning
}  // namespace pnc_x
