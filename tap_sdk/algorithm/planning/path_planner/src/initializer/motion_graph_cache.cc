

#include <algorithm>

#include "initializer/motion_graph_cache.h"
#include <absl/status/status.h>

#include "util/map_util.h"

namespace pnc_x {
namespace planning {

std::string DpMotionEdgeKey::DebugString() const {
    return absl::StrCat(acc, "\t", init_v, "\t", t, "\t",
                        geom_edge_index.value());
}

MotionGraphCache::MotionGraphCache() {}

void MotionGraphCache::BatchGetOrFail(
    const std::vector<DpMotionEdgeKey> &keys,
    std::vector<DpMotionInfo> *ptr_dp_motion_infos,
    std::vector<int> *ptr_failed_idx) const {
    auto &dp_motion_infos = *ptr_dp_motion_infos;
    auto &failed_idx = *ptr_failed_idx;
    for (int i = 0; i < keys.size(); i++) {
        const auto &key = keys[static_cast<std::size_t>(i)];
        const auto ptr_edge_info = FindOrNull(cache_, key);
        if (ptr_edge_info != nullptr) {
            dp_motion_infos[static_cast<std::size_t>(i)].costs.resize(ptr_edge_info->costs.size());
            dp_motion_infos[static_cast<std::size_t>(i)].costs = ptr_edge_info->costs;
            dp_motion_infos[static_cast<std::size_t>(i)].motion_form =
                ptr_edge_info->ptr_motion_form.get();
            dp_motion_infos[static_cast<std::size_t>(i)].ignored_trajs = ptr_edge_info->ignored_trajs;

        } else {
            failed_idx.push_back(i);
        }
    }
}

void MotionGraphCache::Insert(const DpMotionEdgeKey &key,
                              std::vector<double> costs,
                              IgnoreTrajMap ignored_trajs,
                              std::unique_ptr<MotionForm> ptr_motion_form) {
    if (!cache_.contains(key)) {
        MotionEdgeCache edge_cache;
        edge_cache.ptr_motion_form = std::move(ptr_motion_form);
        edge_cache.costs = std::move(costs);
        edge_cache.ignored_trajs = std::move(ignored_trajs);
        auto insert_result =
            cache_.emplace(std::make_pair(key, std::move(edge_cache)));
        bool success = insert_result.second;
        XCHECK(success);
    }
}

void MotionGraphCache::BatchInsert(std::vector<NewCacheInfo> new_motion_forms) {
    for (auto it = new_motion_forms.begin(); it != new_motion_forms.end();
         ++it) {
        if (!cache_.count(it->key)) {
            auto insert_result =
                cache_.emplace(std::make_pair(it->key, std::move(it->cache)));
            bool success = insert_result.second;
            XCHECK(success);
        }
    }
}

std::string DpMotionInfo::DebugString() const {
    return absl::StrCat(
        "sum_cost: ", sum_cost, "start_t: ", start_t,
        "prev_motion_edge_index: ", prev_motion_edge_index.value(),
        "end_geometry_node_index: ", end_geometry_node_index.value(),
        "\n Geometry edge index: ", geometry_edge_index.value());
}

bool MotionGraphCache::has(const DpMotionEdgeKey &key) const {
    return cache_.contains(key);
}

int MotionGraphCache::size() const { return static_cast<int>(cache_.size()); }

absl::StatusOr<MotionForm *> MotionGraphCache::GetMotionForm(
    const DpMotionEdgeKey &key) const {
    const auto ptr_edge_info = FindOrNull(cache_, key);
    if (ptr_edge_info != nullptr) {
        return ptr_edge_info->ptr_motion_form.get();
    } else {
        return absl::NotFoundError("Queried motion form not in cache.");
    }
}

absl::StatusOr<std::vector<double>> MotionGraphCache::GetCosts(
    const DpMotionEdgeKey &key) const {
    const auto ptr_edge_info = FindOrNull(cache_, key);
    if (ptr_edge_info != nullptr) {
        return ptr_edge_info->costs;
    } else {
        return absl::NotFoundError("Queried motion costs not in cache.");
    }
}

MotionGraphCache::~MotionGraphCache() {
    DestroyContainerAsyncMarkSource(std::move(cache_), "");
}

}  // namespace planning
}  // namespace pnc_x
