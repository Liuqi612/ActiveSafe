
#pragma once

#include <unordered_map>
#include <vector>

#include "decision/leading_groups_builder.h"
#include "initializer/interactive_search/decision_extractor/object_decision.h"
#include "initializer/interactive_search/search/node.h"

namespace pnc_x {
namespace planning {

void UpdateGoalSByLeadObs(const ObstacleDecisionGroup &decision_group,
                          const InitializerConfig &initializer_params,
                          const VehicleParamsProto *vehicle_params,
                          const Node &start,
                          double &goal_s);

std::vector<std::pair<double, double>> GetLGaps(
    const DrivePassage *drive_passage,
    const VehicleParamsProto *vehicle_params,
    const double &s,
    const std::vector<std::pair<std::string, Polygon2d>> &obs_polygons);

std::vector<std::pair<double, double>> SortAndMerge(
    const std::vector<std::pair<double, double>> &intervals);

std::vector<std::pair<double, double>> FindComplement(
    const VehicleParamsProto *vehicle_params,
    const std::pair<double, double> &universe,
    const std::vector<std::pair<double, double>> &intervals);

bool FindNextValidGaps(
    const VehicleParamsProto *vehicle_params,
    const double &s,
    const double &delta_s,
    const std::vector<std::pair<double, double>> &curr_l_gaps,
    const std::vector<std::pair<double, double>> &next_l_gaps,
    std::vector<std::pair<double, double>> &valid_next_l_gaps);

bool GetBlockS(const SpacetimeTrajectoryManager &st_traj_mgr,
               const DrivePassage *drive_passage,
               const VehicleParamsProto *vehicle_params,
               double *block_s);

}  // namespace planning
}  // namespace pnc_x
