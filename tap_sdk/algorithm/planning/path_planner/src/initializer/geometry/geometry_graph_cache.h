
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <absl/base/thread_annotations.h>
#include <absl/container/flat_hash_map.h>
#include <absl/status/statusor.h>
#include <absl/synchronization/mutex.h>

#include "pncx_initializer.pb.h"
#include "initializer/geometry/geometry_form.h"
#include "initializer/geometry/geometry_graph.h"
#include "initializer/geometry/geometry_graph_debug.h"
#include "initializer/geometry/geometry_state.h"
#include "math/vec.h"
#include "util/map_util.h"

namespace pnc_x {
namespace planning {

struct GeometryGraphCacheKey {
    int start_x;
    int start_y;
    int start_k;
    int end_x;
    int end_y;

    GeometryGraphCacheKey(const GeometryNode &start_node,
                          const GeometryNode &end_node);

    friend bool operator==(const GeometryGraphCacheKey &lhs,
                           const GeometryGraphCacheKey &rhs);
    template <typename H>
    friend H AbslHashValue(H h, const GeometryGraphCacheKey &key);

    std::string Debug() const;
};

enum class ConnectionResult {
    SUCCESS = 1,
    OMIT_TOO_SHORT = 2,
    OMIT_LATERAL_OFFSET = 3,
    OMIT_NOT_CONVERGE_TO_CENTER = 4,
    FAIL_NO_POLY = 5,
    COLLIDE_TRUNCATE = 6,
    COLLIDE_NO_EDGE = 7,
    FAIL_CURB_COLLISION = 8,
    FAIL_INVALID_CURVATURE = 9,
    NOT_SET = 10
};

struct GeometryEdgeCache {
    std::unique_ptr<GeometryForm> ptr_geometry_form;
    std::unique_ptr<GeometryForm> ptr_geometry_form_truncated;
    ConnectionResult connection_result = ConnectionResult::NOT_SET;
    GeometryState final_state;
    std::vector<std::string> collision_ids;
    std::vector<double> collision_accum_s;
    EdgeDebugInfo debug_info;
};

class GeometryGraphCache {
 public:
    GeometryGraphCache();
    absl::StatusOr<GeometryForm *> GetGeometryForm(
        const GeometryGraphCacheKey &key) const;
    absl::StatusOr<GeometryForm *> GetFullGeometryForm(
        const GeometryGraphCacheKey &key) const;
    absl::StatusOr<ConnectionResult> GetConnectionResult(
        const GeometryGraphCacheKey &key);
    absl::StatusOr<std::pair<double, std::string>> GetCollisionInfo(
        const GeometryGraphCacheKey &key) const;
    const GeometryState &GetFinalState(const GeometryGraphCacheKey &key) const;
    bool AddEdge(const GeometryGraphCacheKey &key, GeometryEdgeCache edge_info);
    void UpdateCollisionInfo(const GeometryGraphCacheKey &key,
                             const std::string &collision_obj_id,
                             double collision_s);
    void UpdateConnectionResult(const GeometryGraphCacheKey &key,
                                const ConnectionResult result);
    void UpdateTruncatedGeometryForm(
        const GeometryGraphCacheKey &key,
        const GeometryState &final_state,
        std::unique_ptr<GeometryForm> ptr_geometry_form_truncated,
        const std::string &collision_obj_id,
        double collision_s);

    bool has(const GeometryGraphCacheKey &key) const;
    int size() const;
    void reset_debug();

    void AddResampleReasons(const std::vector<ResampleReason> &reasons);

    void ParseResampleReasonToProto(
        GeometryGraphDebugProto *graph_debug_proto) const;
    void ParseConnectionProcessDebugInfoToProto(
        GeometryGraphDebugProto *graph_debug_proto) const;
    void ParseCollisionInfoToProto(GeometryGraphDebugProto *proto) const;

    std::string Debug() const;

 private:
    mutable absl::Mutex mutex_;
    mutable absl::Mutex mutex_debug_;
    absl::flat_hash_map<GeometryGraphCacheKey, GeometryEdgeCache> cache_
        ABSL_GUARDED_BY(mutex_);
    absl::flat_hash_map<std::string, int> collision_counter_
        ABSL_GUARDED_BY(mutex_);

    std::vector<ResampleReason> resample_reasons_ ABSL_GUARDED_BY(mutex_debug_);
    int revisited_time_ ABSL_GUARDED_BY(mutex_debug_);
    int successful_connection_ ABSL_GUARDED_BY(mutex_debug_);
    int try_to_connect_ ABSL_GUARDED_BY(mutex_debug_);
};
}  // namespace planning
}  // namespace pnc_x
