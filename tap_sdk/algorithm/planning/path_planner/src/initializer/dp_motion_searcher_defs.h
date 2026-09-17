
#pragma once

#include <algorithm>
#include <array>
#include <string>
#include <utility>
#include <vector>

#include "initializer/motion_graph.h"
#include "initializer/motion_search_types.h"
#include "math/util.h"
#include "plan/planner_defs.h"
#include "pncx_trajectory_point.pb.h"
#include <absl/container/flat_hash_map.h>
#include <absl/hash/hash.h>
namespace pnc_x {
namespace planning {

constexpr double kDpDiscreteSpeedSampleStep = 3.0;
constexpr double kDpDiscreteTimeSampleStep = 2.5;
const int kDpDiscreteTimeHorizon =
    CeilToInt(kInitializerTrajectoryTimeHorizon / kDpDiscreteTimeSampleStep);
constexpr int kConstVelSampleLayerSizeThreshold = 5;

struct DpMotionSample {
    int v_discrete;
    int t_discrete;
    DpMotionSample(double v, double t)
        : v_discrete(std::max(0, RoundToInt(v / kDpDiscreteSpeedSampleStep))),
          t_discrete(
              boost::algorithm::clamp(RoundToInt(t / kDpDiscreteTimeSampleStep),
                                      0,
                                      kDpDiscreteTimeHorizon)) {}

    friend bool operator==(const DpMotionSample &lhs,
                           const DpMotionSample &rhs) {
        return lhs.v_discrete == rhs.v_discrete &&
               lhs.t_discrete == rhs.t_discrete;
    }

    template <typename H>
    friend H AbslHashValue(H h, const DpMotionSample &ms) {
        return H::combine(std::move(h), ms.v_discrete, ms.t_discrete);
    }
};

struct TrajInfo {
    MotionEdgeIndex idx;
    double total_cost;
    std::vector<double> feature_costs;
    std::vector<ApolloTrajectoryPointProto> traj_points;
};

struct BestEdgeInfo {
    MotionEdgeIndex idx;
    double total_cost = 0.0;
    bool is_created_stationary_motion = false;
};

}  // namespace planning
}  // namespace pnc_x
