
#pragma once

#include <boost/optional.hpp>
#include <string>
#include <vector>

#include "common/type_def.h"
#include "math/frenet_common.h"
#include "math/frenet_frame.h"
#include "object/spacetime_object_trajectory.h"
#include "object/spacetime_trajectory_manager.h"
#include <absl/status/statusor.h>
#include <absl/types/span.h>

namespace pnc_x {
namespace planning {
struct TrafficGap {
    absl::Span<const SpacetimeObjectTrajectory *const> leader_trajectories;
    absl::Span<const SpacetimeObjectTrajectory *const> follower_trajectories;
    double s_start;
    double s_end;
};

class VTCurve {
 public:
    struct VTPoint {
        double time;
        double velocity;

        bool operator<(const VTPoint &other) const { return time < other.time; }

        friend bool operator==(const VTPoint &lhs, const VTPoint &rhs) {
            return (lhs.time == rhs.time) && (lhs.velocity == rhs.velocity);
        }
        friend bool operator!=(const VTPoint &lhs, const VTPoint &rhs) {
            return !(lhs == rhs);
        }
    };

    void AddPoint(double time, double velocity) {
        VTPoint newPoint{time, velocity};
        auto it = std::lower_bound(points_.begin(), points_.end(), newPoint);
        points_.insert(it, newPoint);
    }

    double GetVelocity(double time) const {
        if (points_.empty()) {
            return 0.0;
        }

        if (time <= points_.front().time) { return points_.front().velocity; }
        if (time >= points_.back().time) { return points_.back().velocity; }

        VTPoint search{time, 0.0};
        auto it = std::lower_bound(points_.begin(), points_.end(), search);
        if (it == points_.begin()) { return it->velocity; }

        auto prev = it - 1;
        double ratio = (time - prev->time) / (it->time - prev->time);
        return prev->velocity + (ratio * (it->velocity - prev->velocity));
    }

    const std::vector<VTPoint> &GetPoints() const { return points_; }

 private:
    std::vector<VTPoint> points_;
};

struct TrafficGapResult {
    boost::optional<std::string> leader_id = boost::none;
    boost::optional<std::string> follower_id = boost::none;
    boost::optional<std::string> ori_lead_id = boost::none;
    boost::optional<double> dec_gap_target_speed = boost::none;
    boost::optional<double> dec_gap_target_a = boost::none;
    boost::optional<double> acc_gap_target_speed = boost::none;
    boost::optional<double> acc_gap_target_a = boost::none;
    boost::optional<double> bargain_ori_lead_headway = boost::none;
    boost::optional<VTCurve> gap_vt_curve = boost::none;
};

}  // namespace planning
}  // namespace pnc_x
