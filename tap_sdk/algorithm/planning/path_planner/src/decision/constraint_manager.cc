
#include "decision/constraint_manager.h"

namespace pnc_x {
namespace planning {

void ConstraintManager::AddSpeedRegion(
    ConstraintProto::SpeedRegionProto speed_region) {
    const auto it = std::lower_bound(
        speed_region_.begin(), speed_region_.end(), speed_region,
        [](const ConstraintProto::SpeedRegionProto &elem,
           const ConstraintProto::SpeedRegionProto &val) {
            return elem.start_s() < val.start_s();
        });
    speed_region_.insert(it, std::move(speed_region));
}

void ConstraintManager::AddStopLine(ConstraintProto::StopLineProto stop_line) {
    const auto it =
        std::lower_bound(stop_line_.begin(), stop_line_.end(), stop_line,
                         [](const ConstraintProto::StopLineProto &elem,
                            const ConstraintProto::StopLineProto &val) {
                             return elem.s() < val.s();
                         });
    stop_line_.insert(it, std::move(stop_line));
}

void ConstraintManager::AddPathSpeedRegion(
    ConstraintProto::PathSpeedRegionProto path_speed_region) {
    const auto it = std::lower_bound(
        path_speed_region_.begin(), path_speed_region_.end(), path_speed_region,
        [](const ConstraintProto::PathSpeedRegionProto &elem,
           const ConstraintProto::PathSpeedRegionProto &val) {
            return elem.start_s() < val.start_s();
        });
    path_speed_region_.insert(it, std::move(path_speed_region));
}

void ConstraintManager::AddPathStopLine(
    ConstraintProto::PathStopLineProto path_stop_line) {
    const auto it = std::lower_bound(
        path_stop_line_.begin(), path_stop_line_.end(), path_stop_line,
        [](const ConstraintProto::PathStopLineProto &elem,
           const ConstraintProto::PathStopLineProto &val) {
            return elem.s() < val.s();
        });
    path_stop_line_.insert(it, std::move(path_stop_line));
}

void ConstraintManager::AddAvoidLine(
    ConstraintProto::AvoidLineProto avoid_line) {
    avoid_line_.push_back(std::move(avoid_line));
}

void ConstraintManager::AddSpeedProfile(
    ConstraintProto::SpeedProfileProto speed_profile) {
    speed_profiles_.emplace_back(std::move(speed_profile));
}

void ConstraintManager::AddALimit(const double &acc,
                                  const boost::optional<double> &speed,
                                  std::string source) {
    open_loop_speed_limits_.AddALimit(acc, speed, source);
}

void ConstraintManager::AddVLimit(const double &speed,
                                  const double &time,
                                  std::string source) {
    open_loop_speed_limits_.AddVLimit(speed, time, source);
}

void ConstraintManager::SetTrafficGap(TrafficGapResult traffic_gap) {
    traffic_gap_ = std::move(traffic_gap);
}

absl::Span<const ConstraintProto::SpeedRegionProto>
ConstraintManager::SpeedRegion() const {
    return speed_region_;
}

absl::Span<const ConstraintProto::StopLineProto> ConstraintManager::StopLine()
    const {
    return stop_line_;
}

absl::Span<const ConstraintProto::AvoidLineProto> ConstraintManager::AvoidLine()
    const {
    return avoid_line_;
}

const TrafficGapResult &ConstraintManager::TrafficGap() const {
    return traffic_gap_;
}

absl::Span<const ConstraintProto::PathSpeedRegionProto>
ConstraintManager::PathSpeedRegion() const {
    return path_speed_region_;
}
absl::Span<const ConstraintProto::PathStopLineProto>
ConstraintManager::PathStopLine() const {
    return path_stop_line_;
}

absl::Span<const ConstraintProto::SpeedProfileProto>
ConstraintManager::SpeedProfiles() const {
    return speed_profiles_;
}

const OpenLoopSpeedLimit &ConstraintManager::OpenLoopSpeedLimits() const {
    return open_loop_speed_limits_;
}

}  // namespace planning
}  // namespace pnc_x
