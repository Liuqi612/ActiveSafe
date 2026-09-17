#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "initializer/interactive_search/search/node.h"
#include "object/spacetime_trajectory_manager.h"
#include "router/drive_passage.h"
// #include <gflags/gflags.h>

namespace pnc_x {
namespace planning {

struct CompareSearchNodes {
    bool operator()(const std::pair<int, double> &lhs,
                    const std::pair<int, double> &rhs) const {
        return lhs.second > rhs.second;
    }
};

typedef boost::heap::pairing_heap<std::pair<uint64_t, double>,
                                  boost::heap::compare<CompareSearchNodes>>
    searchPriorityQueue;

class AStarSearch final {
 public:
    AStarSearch() = default;
    explicit AStarSearch(const ObstacleDecisionGroup *decision_group,
                         const std::unordered_map<std::string, ObstacleBehavior>
                             *obs_behavior_map,
                         const VehicleParamsProto *vehicle_params,
                         const InitializerConfig &initializer_params,
                         const DrivePassage *drive_passage,
                         const PathSlBoundary *sl_boundary,
                         const std::vector<double> &thw,
                         double tail_ttc)
        : vehicle_params_(vehicle_params),
          initializer_params_(initializer_params),
          obs_behavior_map_(obs_behavior_map),
          drive_passage_(drive_passage),
          sl_boundary_(sl_boundary) {
        safety_checker_ = std::make_shared<SafetyCheck>(
            decision_group, obs_behavior_map, vehicle_params,
            initializer_params, drive_passage, sl_boundary, thw, tail_ttc);
    }
    ~AStarSearch() = default;

    uint64_t Search(Node &start,
                    double goal_s,
                    std::unordered_map<uint64_t, Node> &nodes_map,
                    const ObstacleDecisionGroup &decision_group,
                    const std::string group_prefix,
                    const std::vector<double> &xy_range,
                    bool is_lane_change,
                    bool is_manual_lane_change,
                    std::vector<double> speed_limits,
                    const SpacetimeTrajectoryManager &st_traj_mgr,
                    bool is_pre_safe);

    void TraceBack(uint64_t result_index,
                   std::unordered_map<uint64_t, Node> &nodes_map,
                   std::string &search_info);

    bool ReachGoal(Node &current_node,
                   const ObstacleDecisionGroup &decision_group,
                   bool is_lane_change,
                   const InitializerConfig &initializer_params,
                   const Node &start_node);

    double GetYawRateLimit(const double v);

    double GetSteerLimit(const double v);

    bool GetCoarseTrajectory(
        std::vector<ApolloTrajectoryPointProto> &planning_trajectory,
        int *first_safe_to_gap_index,
        bool start_node_safety,
        bool is_pre_safe,
        int *all_node_safety,
        std::string *infos);

    void SetIterations(int iter) { iterations_ = iter; }

    int GetIterations() const { return iterations_; }

    static std::pair<std::vector<double>, std::vector<double>> yaw_rate_map_;

    const std::shared_ptr<SafetyCheck> &safety_checker() const {
        return safety_checker_;
    }

    const std::string &SearchInfo() const { return search_info_; }

    const std::string &SearchFailReason() const { return search_fail_reason_; }

 private:
    const VehicleParamsProto *vehicle_params_;
    const InitializerConfig &initializer_params_;
    double a_star_time_ = 0.0;
    int iterations_ = 0;
    double goal_s_ = 0.0;
    bool reached_lane_change_star_point_ = false;

    const std::unordered_map<std::string, ObstacleBehavior> *obs_behavior_map_;
    std::vector<Node> node_list_;
    std::shared_ptr<SafetyCheck> safety_checker_;
    std::shared_ptr<ObstacleDecisionGroup> object_ptr_;
    const DrivePassage *drive_passage_;
    const PathSlBoundary *sl_boundary_;

    std::string search_fail_reason_ = "";
    std::string search_info_ = "";
};

}  // namespace planning
}  // namespace pnc_x