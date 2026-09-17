

#include "initializer/ref_speed_table.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <memory>
#include <ostream>

#include "math/frenet_common.h"
#include "math/util.h"
#include "object/spacetime_object_state.h"
#include "object/spacetime_object_trajectory.h"
#include "prediction/predicted_trajectory.h"
#include "util/status_macros.h"
#include <absl/status/statusor.h>
#include <absl/types/span.h>
#include "common/log.h"

namespace pnc_x {
namespace planning {

namespace {
constexpr int kSampleTimeSteps = 9;
constexpr double kPredictionTimeSampleStep = 0.1;
constexpr std::array<double, kSampleTimeSteps> kTimeSamples{
    0.0, 0.9, 1.9, 2.9, 3.9, 4.9, 5.9, 6.9, 7.9};

constexpr double kSpanDiscretizationStep = 0.5;

constexpr double kSafeLeadingDist = 4.5;
constexpr double kSafeLeadingTime = 1.0;
constexpr double kMaxComfortableDeceleration = -1.0;

}  // namespace

RefSpeedVec::RefSpeedVec(const DrivePassage &drive_passage,
                         const std::vector<std::pair<double, double>> &obj_info,
                         double stop_s) {
    std::vector<double> station_accum_s, ref_speed_vec;
    station_accum_s.reserve(drive_passage.size());
    ref_speed_vec.reserve(drive_passage.size());

    for (const auto &station : drive_passage.stations()) {
        double current_s = station.accumulated_s();
        if (current_s > stop_s) break;

        const double limit_from_stop = std::sqrt(
            2.0 * (stop_s - current_s) * (-kMaxComfortableDeceleration));

        double limit_from_obj = std::numeric_limits<double>::max();
        for (size_t i = 0; i < obj_info.size(); ++i) {
            const double obj_s = obj_info[i].first;
            const double obj_v = obj_info[i].second;
            const double obj_ref_v =
                current_s >= obj_s
                    ? obj_v
                    : std::sqrt(Sqr(obj_v) - 2.0 * (obj_s - current_s) *
                                                 kMaxComfortableDeceleration);
            limit_from_obj = std::min(limit_from_obj, obj_ref_v);
        }

        station_accum_s.push_back(current_s);
        ref_speed_vec.push_back(std::min(limit_from_stop, limit_from_obj));
    }

    start_s_ = station_accum_s.front();
    end_s_ = station_accum_s.back();
    const int discretized_num =
        CeilToInt((end_s_ - start_s_) / kSpanDiscretizationStep);
    discretized_ref_speed_by_s_.resize(static_cast<size_t>(discretized_num) + 1U, 0.0);
    for (int i = 0, s_idx = 0; i <= discretized_num; ++i) {
        const double sample_s = (static_cast<double>(i) * kSpanDiscretizationStep) + start_s_;
        if ((sample_s <= start_s_) || (sample_s >= end_s_)) { continue; }

        if (sample_s > station_accum_s[static_cast<size_t>(s_idx)]) { ++s_idx; }
        discretized_ref_speed_by_s_[static_cast<size_t>(i)] =
            Lerp(ref_speed_vec[static_cast<size_t>(s_idx) - 1U],
                 ref_speed_vec[static_cast<size_t>(s_idx)],
                 (sample_s - station_accum_s[static_cast<size_t>(s_idx) - 1U]) /
                     (station_accum_s[static_cast<size_t>(s_idx)] -
                      station_accum_s[static_cast<size_t>(s_idx) - 1U]));
    }
}

double RefSpeedVec::FastComputeRefSpeed(double s) const {
    if (s <= start_s_ || s >= end_s_) return 0.0;

    return discretized_ref_speed_by_s_[RoundToInt((s - start_s_) /
                                                  kSpanDiscretizationStep)];
}

RefSpeedTable::RefSpeedTable(const SpacetimeTrajectoryManager &st_traj_mgr,
                             const std::vector<std::string> &leading_trajs,
                             const DrivePassage &drive_passage,
                             const std::vector<double> &stop_s) {
    const double nearest_stop_s =
        stop_s.empty() ? std::numeric_limits<double>::max()
                       : *std::min_element(stop_s.begin(), stop_s.end());

    station_accum_s_.reserve(drive_passage.size());
    station_speed_limits_.reserve(drive_passage.size());
    for (const auto &station : drive_passage.stations()) {
        station_accum_s_.push_back(station.accumulated_s());
        station_speed_limits_.push_back(station.speed_limit());
    }

    ref_speed_table_.reserve(static_cast<size_t>(kSampleTimeSteps));
    for (const double time_sample : kTimeSamples) {
        const int obj_state_idx =
            RoundToInt(time_sample / kPredictionTimeSampleStep);

        std::vector<std::pair<double, double>> obj_info;
        obj_info.reserve(leading_trajs.size());
        for (const auto &traj_id : leading_trajs) {
            const auto *traj_ptr = st_traj_mgr.FindTrajectoryById(traj_id);
            if (traj_ptr == nullptr) {
                AD_LWARN(PP)
                    << "Leading trajectory " << traj_id << " cannot be found.";
                continue;
            }
            const auto &states = traj_ptr->states();
            if (states.size() <= obj_state_idx) continue;
            if (states[0].traj_point->v() > 4.0 &&
                states[obj_state_idx].traj_point->v() < 1e-5)
                continue;

            ASSIGN_OR_CONTINUE(
                const auto obj_aabbox,
                drive_passage.QueryFrenetBoxAt(states[obj_state_idx].box));
            const double obj_v = states[obj_state_idx].traj_point->v();
            const double obj_s =
                std::max(0.0, obj_aabbox.s_min - kSafeLeadingDist -
                                  obj_v * kSafeLeadingTime);
            obj_info.push_back({obj_s, obj_v});
        }
        ref_speed_table_.emplace_back(drive_passage, obj_info, nearest_stop_s);
    }
}

std::pair<double, double> RefSpeedTable::LookUpRefSpeed(double time,
                                                        double span) const {
    XCHECK_GE(time, 0.0);

    const int station_idx = std::upper_bound(station_accum_s_.begin(),
                                             station_accum_s_.end(), span) -
                            station_accum_s_.begin();
    const double speed_limit = station_idx == station_accum_s_.size()
                                   ? station_speed_limits_.back()
                                   : station_speed_limits_[station_idx];

    double ref_speed;
    const int next_index =
        std::upper_bound(kTimeSamples.begin(), kTimeSamples.end(), time) -
        kTimeSamples.begin();
    if (next_index == kTimeSamples.size()) {
        ref_speed = ref_speed_table_.back().FastComputeRefSpeed(span);
    } else {
        const double prev_ref_speed =
            ref_speed_table_[static_cast<size_t>(next_index) - 1U].FastComputeRefSpeed(span);
        const double succ_ref_speed =
            ref_speed_table_[next_index].FastComputeRefSpeed(span);
        const double interp_t =
            (time - kTimeSamples[static_cast<size_t>(next_index) - 1U]) /
            (kTimeSamples[static_cast<size_t>(next_index)] -
             kTimeSamples[static_cast<size_t>(next_index) - 1U]);

        ref_speed = Lerp(prev_ref_speed, succ_ref_speed, interp_t);
    }

    return {speed_limit, std::min(speed_limit, ref_speed)};
}

}  // namespace planning
}  // namespace pnc_x
