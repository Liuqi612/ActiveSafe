#include <algorithm>

#include "common/throw_check.h"
#include "initializer/geometry/geometry_graph_cache.h"
#include "util/map_util.h"
#include <absl/status/status.h>

namespace pnc_x {
namespace planning {
namespace {
bool NewConnection(const ConnectionResult &prev,
                   const ConnectionResult &current) {
    if (prev != ConnectionResult::SUCCESS &&
        current == ConnectionResult::SUCCESS) {
        return true;
    }
    if (prev == ConnectionResult::COLLIDE_NO_EDGE &&
        current == ConnectionResult::COLLIDE_TRUNCATE) {
        return true;
    }
    return false;
}
}  // namespace

bool operator==(const GeometryGraphCacheKey &lhs,
                const GeometryGraphCacheKey &rhs) {
    return lhs.start_x == rhs.start_x && lhs.end_x == rhs.end_x &&
           lhs.start_y == rhs.start_y && lhs.start_k == rhs.start_k &&
           lhs.end_y == rhs.end_y;
}

template <typename H>
H AbslHashValue(H h, const GeometryGraphCacheKey &key) {
    return H::combine(std::move(h), key.start_k, key.start_x, key.start_y,
                      key.end_x, key.end_y);
}

GeometryGraphCacheKey::GeometryGraphCacheKey(const GeometryNode &start_node,
                                             const GeometryNode &end_node) {
    const double discretize_factor = 100.0;
    start_x = static_cast<int>(start_node.xy.x() * discretize_factor);
    start_y = static_cast<int>(start_node.xy.y() * discretize_factor);
    start_k = static_cast<int>(start_node.k * discretize_factor);
    end_x = static_cast<int>(end_node.xy.x() * discretize_factor);
    end_y = static_cast<int>(end_node.xy.y() * discretize_factor);
}

std::string GeometryGraphCacheKey::Debug() const {
    return absl::StrCat(start_x, "\t", start_y, "\t", start_k, "\t", end_x,
                        "\t", end_y);
}

absl::StatusOr<GeometryForm *> GeometryGraphCache::GetGeometryForm(
    const GeometryGraphCacheKey &key) const {
    absl::ReaderMutexLock lock(&mutex_);

    const auto ptr_edge_info = FindOrNull(cache_, key);
    if (ptr_edge_info == nullptr) {
        return absl::NotFoundError(
            "Geometry graph cache contains empty geometry form. Should not "
            "come "
            "here!");
    }
    const auto &connection_result = ptr_edge_info->connection_result;
    if (connection_result == ConnectionResult::SUCCESS) {
        return ptr_edge_info->ptr_geometry_form.get();
    }
    if (connection_result == ConnectionResult::COLLIDE_TRUNCATE) {
        return ptr_edge_info->ptr_geometry_form_truncated.get();
    }
    return absl::NotFoundError(
        "Get geometry form other than success/truncate.");
}

absl::StatusOr<GeometryForm *> GeometryGraphCache::GetFullGeometryForm(
    const GeometryGraphCacheKey &key) const {
    absl::ReaderMutexLock lock(&mutex_);
    const auto ptr_edge_info = FindOrNull(cache_, key);
    if (ptr_edge_info == nullptr) {
        return absl::NotFoundError(
            "key not in cache, can not get full geometry form, should not come "
            "here!");
    }
    return ptr_edge_info->ptr_geometry_form.get();
}

absl::StatusOr<ConnectionResult> GeometryGraphCache::GetConnectionResult(
    const GeometryGraphCacheKey &key) {
    absl::ReaderMutexLock lock(&mutex_);
    absl::WriterMutexLock lock_debug(&mutex_debug_);
    try_to_connect_++;
    const auto ptr_edge_info = FindOrNull(cache_, key);
    if (ptr_edge_info == nullptr) {
        return absl::NotFoundError(
            "In GetConnectionResult, queried key not in cache yet.");
    } else {
        revisited_time_++;
        return ptr_edge_info->connection_result;
    }
}

absl::StatusOr<std::pair<double, std::string>>
GeometryGraphCache::GetCollisionInfo(const GeometryGraphCacheKey &key) const {
    absl::ReaderMutexLock lock(&mutex_);
    const auto &ptr_edge_info = FindOrNull(cache_, key);
    if (ptr_edge_info == nullptr) {
        return absl::NotFoundError(
            "In GetCollisionInfo, queried key not in cache yet.");
    } else {
        return std::make_pair(ptr_edge_info->collision_accum_s.front(),
                              ptr_edge_info->collision_ids.front());
    }
}

bool GeometryGraphCache::AddEdge(const GeometryGraphCacheKey &key,
                                 GeometryEdgeCache edge_info) {
    absl::WriterMutexLock lock(&mutex_);
    if (!edge_info.collision_ids.empty()) {
        for (const auto &id : edge_info.collision_ids) {
            collision_counter_[id]++;
        }
    }
    const auto connection_result = edge_info.connection_result;
    auto it_success = cache_.emplace(std::make_pair(key, std::move(edge_info)));
    bool success = it_success.second;
    if (success && (connection_result == ConnectionResult::SUCCESS ||
                    connection_result == ConnectionResult::COLLIDE_TRUNCATE)) {
        absl::WriterMutexLock lock_debug(&mutex_debug_);
        successful_connection_++;
    }
    return success;
}

void GeometryGraphCache::UpdateCollisionInfo(
    const GeometryGraphCacheKey &key,
    const std::string &collision_obj_id,
    double collision_s) {
    absl::WriterMutexLock lock(&mutex_);
    auto *ptr_edge_info = FindOrNull(cache_, key);
    if (ptr_edge_info == nullptr) return;
    ptr_edge_info->collision_accum_s.clear();
    ptr_edge_info->collision_ids.clear();
    ptr_edge_info->collision_accum_s.push_back(collision_s);
    ptr_edge_info->collision_ids.push_back(collision_obj_id);
}

void GeometryGraphCache::UpdateTruncatedGeometryForm(
    const GeometryGraphCacheKey &key,
    const GeometryState &final_state,
    std::unique_ptr<GeometryForm> ptr_geometry_form_truncated,
    const std::string &collision_obj_id,
    double collision_s) {
    absl::WriterMutexLock lock(&mutex_);
    absl::WriterMutexLock lock_debug(&mutex_debug_);
    auto *ptr_edge_info = FindOrNull(cache_, key);
    if (ptr_edge_info == nullptr) return;
    if (ptr_edge_info->connection_result == ConnectionResult::COLLIDE_NO_EDGE) {
        successful_connection_++;
    }
    ptr_edge_info->connection_result = ConnectionResult::COLLIDE_TRUNCATE;
    ptr_edge_info->ptr_geometry_form_truncated =
        std::move(ptr_geometry_form_truncated);
    ptr_edge_info->final_state = final_state;
    ptr_edge_info->collision_accum_s.push_back(collision_s);
    ptr_edge_info->collision_ids.push_back(collision_obj_id);
}

void GeometryGraphCache::UpdateConnectionResult(
    const GeometryGraphCacheKey &key, const ConnectionResult result) {
    absl::WriterMutexLock lock(&mutex_);
    absl::WriterMutexLock lock_debug(&mutex_debug_);
    auto *ptr_edge_info = FindOrNull(cache_, key);
    if (!XCHECK_NOTNULL(ptr_edge_info)) {
        return;
    }
    if (NewConnection(ptr_edge_info->connection_result, result)) {
        successful_connection_++;
    }
    ptr_edge_info->connection_result = result;
}

void GeometryGraphCache::ParseResampleReasonToProto(
    GeometryGraphDebugProto *graph_debug_proto) const {
    absl::ReaderMutexLock lock(&mutex_);
    absl::ReaderMutexLock lock_debug(&mutex_debug_);
    graph_debug_proto->mutable_resample_result()->Reserve(
        static_cast<int>(resample_reasons_.size()));
    for (int i = 0, n = static_cast<int>(resample_reasons_.size()); i < n; i++) {
        auto *new_result = graph_debug_proto->add_resample_result();
        new_result->set_layer_idx(i + 1);
        switch (resample_reasons_[i]) {
            case ResampleReason::RESAMPLED:
                new_result->set_resample_reason(
                    GeometryGraphDebugProto_ResampleResult::RESAMPLED);
                break;
            case ResampleReason::NR_ZERO_REACHABLE:
                new_result->set_resample_reason(
                    GeometryGraphDebugProto_ResampleResult::NR_ZERO_REACHABLE);
                break;
            case ResampleReason::NR_ALL_REACHABLE:
                new_result->set_resample_reason(
                    GeometryGraphDebugProto_ResampleResult::NR_ALL_REACHABLE);
                break;
            case ResampleReason::NR_INVALID_RANGE:
                new_result->set_resample_reason(
                    GeometryGraphDebugProto_ResampleResult::NR_INVALID_RANGE);
                break;
            case ResampleReason::NR_LATERAL_RESOLUTION:
                new_result->set_resample_reason(
                    GeometryGraphDebugProto_ResampleResult::
                        NR_LATERAL_RESOLUTION);
                break;
            case ResampleReason::NOT_INITIALIZED:
                break;
        }
    }
}

void GeometryGraphCache::ParseConnectionProcessDebugInfoToProto(
    GeometryGraphDebugProto *graph_debug_proto) const {
    absl::ReaderMutexLock lock(&mutex_);
    absl::ReaderMutexLock lock_debug(&mutex_debug_);
    graph_debug_proto->mutable_connection_process()->Reserve(static_cast<int>(cache_.size()));
    for (const auto &edge_info : cache_) {
        const auto &ei = edge_info.second;
        const auto &cp = edge_info.second.debug_info;
        const auto &connection_result = ei.connection_result;
        auto *new_process = graph_debug_proto->add_connection_process();
        auto *start = new_process->mutable_start();
        start->set_layer_index(cp.start_layer_idx);
        start->set_station_index(cp.start_station_idx);

        auto *end = new_process->mutable_end();
        end->set_layer_index(cp.end_layer_idx);
        end->set_station_index(cp.end_station_idx);

        switch (connection_result) {
            case ConnectionResult::SUCCESS:
                new_process->set_connection_result(
                    GeometryGraphDebugProto_ConnectionProcess::SUCCESS);
                break;
            case ConnectionResult::OMIT_TOO_SHORT:
                new_process->set_connection_result(
                    GeometryGraphDebugProto_ConnectionProcess::OMIT_TOO_SHORT);
                break;
            case ConnectionResult::OMIT_LATERAL_OFFSET:
                new_process->set_connection_result(
                    GeometryGraphDebugProto_ConnectionProcess::
                        OMIT_LATERAL_OFFSET);
                break;
            case ConnectionResult::OMIT_NOT_CONVERGE_TO_CENTER:
                new_process->set_connection_result(
                    GeometryGraphDebugProto_ConnectionProcess::
                        OMIT_NOT_CONVERGE_TO_CENTER);
                break;
            case ConnectionResult::FAIL_NO_POLY:
                new_process->set_connection_result(
                    GeometryGraphDebugProto_ConnectionProcess::FAIL_NO_POLY);
                break;
            case ConnectionResult::COLLIDE_TRUNCATE:
                new_process->set_connection_result(
                    GeometryGraphDebugProto_ConnectionProcess::
                        COLLIDE_TRUNCATE);
                break;
            case ConnectionResult::COLLIDE_NO_EDGE:
                new_process->set_connection_result(
                    GeometryGraphDebugProto_ConnectionProcess::COLLIDE_NO_EDGE);
                break;
            case ConnectionResult::FAIL_CURB_COLLISION:
                new_process->set_connection_result(
                    GeometryGraphDebugProto_ConnectionProcess::
                        FAIL_CURB_COLLISION);
                break;
            case ConnectionResult::FAIL_INVALID_CURVATURE:
                new_process->set_connection_result(
                    GeometryGraphDebugProto_ConnectionProcess::
                        FAIL_INVALID_CURVATURE);
                break;
            case ConnectionResult::NOT_SET:
                new_process->set_connection_result(
                    GeometryGraphDebugProto_ConnectionProcess::NOT_SET);
                break;
        }

        auto *collision_info = new_process->mutable_collision_info();
        if ((connection_result == ConnectionResult::COLLIDE_NO_EDGE) ||
            (connection_result == ConnectionResult::COLLIDE_TRUNCATE)) {
            if (!XCHECK_EQ(ei.collision_ids.size(),
                           ei.collision_accum_s.size())) {
                continue;
            }
            collision_info->mutable_collision_accum_s()->Reserve(
                static_cast<int>(ei.collision_accum_s.size()));
            collision_info->mutable_collide_obj_id()->Reserve(
                static_cast<int>(ei.collision_ids.size()));
            for (int i = 0, n = static_cast<int>(ei.collision_ids.size()); i < n; i++) {
                collision_info->add_collision_accum_s(ei.collision_accum_s[i]);
                collision_info->add_collide_obj_id(ei.collision_ids[i]);
            }
        }
    }
}

void GeometryGraphCache::ParseCollisionInfoToProto(
    GeometryGraphDebugProto *proto) const {
    absl::ReaderMutexLock lock(&mutex_);
    absl::ReaderMutexLock lock_debug(&mutex_debug_);
    if (collision_counter_.empty()) return;
    proto->mutable_static_collision()->Reserve(static_cast<int>(collision_counter_.size()));
    for (const auto &collision : collision_counter_) {
        auto *new_collision = proto->add_static_collision();
        new_collision->set_collision_traj_id(std::string(collision.first));
        new_collision->set_number(collision.second);
    }
}

GeometryGraphCache::GeometryGraphCache()
    : revisited_time_(0), successful_connection_(0), try_to_connect_(0) {}

const GeometryState &GeometryGraphCache::GetFinalState(
    const GeometryGraphCacheKey &key) const {
    absl::ReaderMutexLock lock(&mutex_);
    const auto ptr_edge_info = FindOrNull(cache_, key);
    XCHECK(ptr_edge_info->connection_result ==
           ConnectionResult::COLLIDE_TRUNCATE);
    return ptr_edge_info->final_state;
}

bool GeometryGraphCache::has(const GeometryGraphCacheKey &key) const {
    absl::ReaderMutexLock lock(&mutex_);
    return cache_.contains(key);
}
int GeometryGraphCache::size() const {
    absl::MutexLock lock(&mutex_);
    return static_cast<int>(cache_.size());
}
void GeometryGraphCache::reset_debug() {
    absl::WriterMutexLock lock(&mutex_debug_);
    revisited_time_ = 0;
    try_to_connect_ = 0;
}

void GeometryGraphCache::AddResampleReasons(
    const std::vector<ResampleReason> &reasons) {
    absl::WriterMutexLock lock(&mutex_debug_);
    resample_reasons_ = std::move(reasons);
}

std::string GeometryGraphCache::Debug() const {
    absl::ReaderMutexLock lock(&mutex_);
    absl::ReaderMutexLock lock_debug(&mutex_debug_);
    return absl::StrCat("Cache debug: total size: ", cache_.size(),
                        ", revisited time: ", revisited_time_,
                        ", try to connect: ", try_to_connect_,
                        ", successful connection: ", successful_connection_);
}

}  // namespace planning
}  // namespace pnc_x
