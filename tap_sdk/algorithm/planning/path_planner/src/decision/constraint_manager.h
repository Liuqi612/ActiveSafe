
#pragma once

#include <map>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "pncx_constraint.pb.h"
#include "decision/traffic_gap_finder.h"
#include "math/geometry/box2d.h"
#include "math/geometry/halfplane.h"
#include "math/geometry/polygon2d.h"
#include "object/planner_object.h"
#include "object/spacetime_object_trajectory.h"
#include "object/spacetime_trajectory_manager.h"
#include "speed/open_loop_speed_limit.h"
#include "util/map_util.h"
#include <absl/container/flat_hash_set.h>
#include <absl/types/span.h>

namespace pnc_x {
namespace planning {

class ConstraintManager {
 public:
    ConstraintManager() = default;

    void AddSpeedRegion(ConstraintProto::SpeedRegionProto speed_region);

    void AddStopLine(ConstraintProto::StopLineProto stop_line);

    void AddPathSpeedRegion(
        ConstraintProto::PathSpeedRegionProto path_speed_region);

    void AddPathStopLine(ConstraintProto::PathStopLineProto path_stop_line);

    void AddAvoidLine(ConstraintProto::AvoidLineProto avoid_line);

    void AddSpeedProfile(ConstraintProto::SpeedProfileProto speed_profile);

    void AddALimit(const double &acc,
                   const boost::optional<double> &speed,
                   std::string source = "");

    void AddVLimit(const double &speed,
                   const double &time,
                   std::string source = "");

    void SetTrafficGap(TrafficGapResult traffic_gap);

    absl::Span<const ConstraintProto::SpeedRegionProto> SpeedRegion() const;

    absl::Span<const ConstraintProto::StopLineProto> StopLine() const;

    absl::Span<const ConstraintProto::AvoidLineProto> AvoidLine() const;

    const TrafficGapResult &TrafficGap() const;

    absl::Span<const ConstraintProto::PathSpeedRegionProto> PathSpeedRegion()
        const;
    absl::Span<const ConstraintProto::PathStopLineProto> PathStopLine() const;

    absl::Span<const ConstraintProto::SpeedProfileProto> SpeedProfiles() const;

    const OpenLoopSpeedLimit &OpenLoopSpeedLimits() const;

 private:
    std::vector<ConstraintProto::SpeedRegionProto> speed_region_;
    std::vector<ConstraintProto::StopLineProto> stop_line_;
    std::vector<ConstraintProto::PathStopLineProto> path_stop_line_;
    std::vector<ConstraintProto::PathSpeedRegionProto> path_speed_region_;
    std::vector<ConstraintProto::AvoidLineProto> avoid_line_;
    std::vector<ConstraintProto::SpeedProfileProto> speed_profiles_;

    TrafficGapResult traffic_gap_;
    OpenLoopSpeedLimit open_loop_speed_limits_;
};
}  // namespace planning
}  // namespace pnc_x
