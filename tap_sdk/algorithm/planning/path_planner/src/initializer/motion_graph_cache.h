
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <math.h>

#include "async/async_util.h"
#include "initializer/motion_search_types.h"
#include "initializer/dp_motion_searcher_defs.h"
#include "initializer/geometry/geometry_graph.h"
#include "initializer/motion_form.h"
#include "initializer/motion_graph.h"
#include <absl/container/flat_hash_map.h>
#include <absl/status/statusor.h>
#include <absl/strings/str_cat.h>

namespace pnc_x {
namespace planning {

struct MotionEdgeCache {
    std::unique_ptr<MotionForm> ptr_motion_form;
    std::vector<double> costs;
    IgnoreTrajMap ignored_trajs;
};

// DP-only cache key. A* has its own de-duplication key in motion_search_types.h.
struct DpMotionEdgeKey {
    int acc;
    int init_v;
    int t;
    GeometryEdgeIndex geom_edge_index;
    double v0() const { return static_cast<double>(init_v) / 100.0; }
    double a0() const { return static_cast<double>(acc) / 100.0; }
    double t0() const { return static_cast<double>(t) / 100.0; }
    std::string DebugString() const;
    DpMotionEdgeKey(double acceleration, double initial_velocity, double time,
                    GeometryEdgeIndex edge)
        : acc(static_cast<int>(std::lround(acceleration * 100.0))),
          init_v(static_cast<int>(std::lround(initial_velocity * 100.0))),
          t(static_cast<int>(std::lround(time * 100.0))),
          geom_edge_index(edge) {}
    DpMotionEdgeKey()
        : acc(0), init_v(0), t(0),
          geom_edge_index(static_cast<GeometryEdgeIndex>(-1)) {}
    friend bool operator==(const DpMotionEdgeKey &lhs,
                           const DpMotionEdgeKey &rhs) {
        return lhs.acc == rhs.acc && lhs.init_v == rhs.init_v && lhs.t == rhs.t &&
               lhs.geom_edge_index.value() == rhs.geom_edge_index.value();
    }
    template <typename H>
    friend H AbslHashValue(H h, const DpMotionEdgeKey &key) {
        return H::combine(std::move(h), key.acc, key.init_v, key.t,
                           key.geom_edge_index.value());
    }
};

struct NewCacheInfo {
    DpMotionEdgeKey key;
    MotionEdgeCache cache;
};

struct DpMotionInfo {
    DpMotionEdgeKey key;
    double sum_cost = 0.0;
    std::vector<double> costs;
    double start_t = 0.0;
    MotionEdgeIndex prev_motion_edge_index;
    GeometryNodeIndex end_geometry_node_index;
    MotionForm *motion_form;
    GeometryEdgeIndex geometry_edge_index;
    IgnoreTrajMap ignored_trajs;
    std::string DebugString() const;
};

class MotionGraphCache {
 public:
    MotionGraphCache();

    void BatchGetOrFail(const std::vector<DpMotionEdgeKey> &samples,
                        std::vector<DpMotionInfo> *ptr_result,
                        std::vector<int> *failed_idx) const;

    void Insert(const DpMotionEdgeKey &key,
                std::vector<double> costs,
                IgnoreTrajMap ignored_trajs,
                std::unique_ptr<MotionForm> ptr_motion_form);

    void BatchInsert(std::vector<NewCacheInfo> new_motion_forms);

    bool has(const DpMotionEdgeKey &key) const;

    absl::StatusOr<MotionForm *> GetMotionForm(const DpMotionEdgeKey &key) const;

    absl::StatusOr<std::vector<double>> GetCosts(
        const DpMotionEdgeKey &key) const;

    int size() const;

    ~MotionGraphCache();

 private:
    absl::flat_hash_map<DpMotionEdgeKey, MotionEdgeCache> cache_;
};

}  // namespace planning
}  // namespace pnc_x
