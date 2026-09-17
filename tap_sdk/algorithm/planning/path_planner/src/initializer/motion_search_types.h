#pragma once

#include <array>
#include <cmath>
#include <string>
#include <utility>

#include <absl/container/flat_hash_map.h>

#include "initializer/geometry/geometry_graph.h"

namespace pnc_x {
namespace planning {

constexpr double kCanSetToZeroSpeed = 1.0;
constexpr double kSearchFailedCanSetToZeroSpeed = 1.5;
constexpr double kCanSetToZeroTrajLength = 4.0;
constexpr double kMinSpeedForFinalCost = 3.0;
constexpr std::array<double, 9> kAccelerationSamplePoints = {
    -4.0, -3.0, -2.0, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5};

// Collision handling is shared by the production Interactive A* search and
// the optional DP reference implementation.  Keep this small contract out of
// dp_motion_searcher_defs.h so the production target does not depend on DP
// headers merely to represent ignored prediction branches.
enum class CollisionConfiguration {
    NONE = 0,
    FRONT = 1,
    LEFT = 2,
    RIGHT = 3,
    BACK = 4,
};

struct CollisionConfigurationInfo {
    int time_idx = 0;
    CollisionConfiguration collision_config = CollisionConfiguration::NONE;
};

using IgnoreTrajMap =
    absl::flat_hash_map<std::string, CollisionConfigurationInfo>;

// A* uses this key only to de-duplicate acceleration samples. Keeping the key
// here avoids pulling the DP cache into the production initializer target.
struct MotionEdgeKey {
    int acc;
    int init_v;
    int t;
    GeometryEdgeIndex geom_edge_index;

    double v0() const { return static_cast<double>(init_v) / 100.0; }
    double a0() const { return static_cast<double>(acc) / 100.0; }
    double t0() const { return static_cast<double>(t) / 100.0; }

    MotionEdgeKey(double acceleration, double initial_velocity, double time,
                  GeometryEdgeIndex edge)
        : acc(static_cast<int>(std::lround(acceleration * 100.0))),
          init_v(static_cast<int>(std::lround(initial_velocity * 100.0))),
          t(static_cast<int>(std::lround(time * 100.0))),
          geom_edge_index(edge) {}
    MotionEdgeKey()
        : acc(0),
          init_v(0),
          t(0),
          geom_edge_index(static_cast<GeometryEdgeIndex>(-1)) {}

    friend bool operator==(const MotionEdgeKey &lhs, const MotionEdgeKey &rhs) {
        return lhs.acc == rhs.acc && lhs.init_v == rhs.init_v && lhs.t == rhs.t &&
               lhs.geom_edge_index.value() == rhs.geom_edge_index.value();
    }

    template <typename H>
    friend H AbslHashValue(H h, const MotionEdgeKey &key) {
        return H::combine(std::move(h), key.acc, key.init_v, key.t,
                           key.geom_edge_index.value());
    }
};

}  // namespace planning
}  // namespace pnc_x
