
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "object/spacetime_trajectory_manager.h"
#include "router/drive_passage.h"

namespace pnc_x {
namespace planning {

class RefSpeedVec {
 public:
    RefSpeedVec() {}
    RefSpeedVec(const DrivePassage &drive_passage,
                const std::vector<std::pair<double, double>> &obj_info,
                double stop_s);
    double FastComputeRefSpeed(double s) const;

 private:
    double start_s_;
    double end_s_;
    std::vector<double> discretized_ref_speed_by_s_;
};

class RefSpeedTable {
 public:
    RefSpeedTable(const SpacetimeTrajectoryManager &st_traj_mgr,
                  const std::vector<std::string> &leading_objs,
                  const DrivePassage &drive_passage,
                  const std::vector<double> &stop_s);

    std::pair<double, double> LookUpRefSpeed(double time, double span) const;

    const std::vector<RefSpeedVec> &ref_speed_table() const {
        return ref_speed_table_;
    }

 private:
    std::vector<double> station_accum_s_;
    std::vector<double> station_speed_limits_;
    std::vector<RefSpeedVec> ref_speed_table_;
};

}  // namespace planning
}  // namespace pnc_x
