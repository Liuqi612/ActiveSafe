#pragma once

#include <string>
#include <utility>
#include <vector>
#include <memory>

#include "async/thread_pool.h"
#include "object/planner_object.h"
#include "object/spacetime_object_trajectory.h"
#include "pncx_planner_object.pb.h"
#include "prediction/predicted_trajectory.h"
#include "util/map_util.h"
#include <absl/container/flat_hash_map.h>
#include <absl/strings/string_view.h>
#include <absl/types/span.h>

namespace pnc_x {

namespace planning {

class TrajectoryFilter;

namespace {
template <typename T>
using NestedVector = std::vector<std::vector<T>>;

double ComputeRequiredLateralGap(const PlannerObject &object) {
    switch (object.type()) {
        case OT_FOD:
            return 0.0;
        case OT_UNKNOWN_STATIC:
        case OT_VEGETATION:
        case OT_BARRIER:
        case OT_CONE:
        case OT_WARNING_TRIANGLE:
            return 0.15;
        case OT_VEHICLE:
        case OT_LARGE_VEHICLE:
        case OT_UNKNOWN_MOVABLE:
        case OT_MOTORCYCLIST:
        case OT_PEDESTRIAN:
        case OT_CYCLIST:
        case OT_TRICYCLIST:
            return 0.2;
        default:
            throw std::runtime_error("switch case on enum unexpected");
    }
}
}  // namespace

class SpacetimeTrajectoryManager {
 public:
    SpacetimeTrajectoryManager() = default;

    SpacetimeTrajectoryManager(
        absl::Span<const TrajectoryFilter *const> filters,
        absl::Span<const PlannerObject> planner_objects,
        ThreadPool *thread_pool);
    explicit SpacetimeTrajectoryManager(
        absl::Span<const PlannerObject> planner_objects,
        ThreadPool *thread_pool = nullptr)
        : SpacetimeTrajectoryManager({}, planner_objects, thread_pool) {}

    explicit SpacetimeTrajectoryManager(
        absl::Span<SpacetimeObjectTrajectory> spacetime_trajectories);

    SpacetimeTrajectoryManager(const SpacetimeTrajectoryManager &other);
    SpacetimeTrajectoryManager &operator=(
        const SpacetimeTrajectoryManager &other);

    SpacetimeTrajectoryManager(SpacetimeTrajectoryManager &&other) = default;
    SpacetimeTrajectoryManager &operator=(SpacetimeTrajectoryManager &&other) =
        default;

    absl::Span<const SpacetimeObjectTrajectory *const> stationary_object_trajs()
        const {
        return considered_stationary_trajs_;
    }

    absl::Span<const SpacetimeObjectTrajectory *const> moving_object_trajs()
        const {
        return considered_moving_trajs_;
    }

    absl::Span<const SpacetimeObjectTrajectory> trajectories() const {
        return *considered_trajs_;
    }

    std::vector<SpacetimeObjectTrajectory> *mutable_trajectories() {
        return considered_trajs_.get();
    }

    const absl::flat_hash_map<std::string,
                              std::vector<const SpacetimeObjectTrajectory *>>
        &object_trajectories_map() const {
        return objects_id_map_;
    }

    absl::Span<const SpacetimeObjectTrajectory *const>
    FindTrajectoriesByObjectId(std::string id) const {
        const auto iter = objects_id_map_.find(id);
        if (iter == objects_id_map_.end()) { return {}; }
        return iter->second;
    }

    const PlannerObject *FindObjectByObjectId(std::string id) const {
        const auto iter = objects_id_map_.find(id);
        if (iter == objects_id_map_.end()) { return nullptr; }
        return &(iter->second.front()->planner_object());
    }

    const SpacetimeObjectTrajectory *FindTrajectoryById(
        std::string traj_id) const {
        auto str = std::string(traj_id);

        return FindPtrOrNull(trajectories_id_map_, str);
    }

    struct IgnoredTrajectory {
        const prediction::PredictedTrajectory *traj;
        std::string object_id;
        FilterReason::Type reason;
    };
    struct StationaryObject {
        std::string object_id;
        PlannerObject planner_object;
    };

    absl::Span<const IgnoredTrajectory> ignored_trajectories() const {
        return *ignored_trajs_;
    }

    absl::Span<const StationaryObject> stationary_objects() const {
        return *stationary_objs_;
    }

    void UpdatePointers(int stationary_size);

 protected:
    absl::flat_hash_map<std::string,
                        std::vector<const SpacetimeObjectTrajectory *>>
        objects_id_map_;
    absl::flat_hash_map<std::string, const SpacetimeObjectTrajectory *>
        trajectories_id_map_;

    std::shared_ptr<std::vector<SpacetimeObjectTrajectory>> considered_trajs_ =
        std::make_shared<std::vector<SpacetimeObjectTrajectory>>();
    std::shared_ptr<std::vector<IgnoredTrajectory>> ignored_trajs_ =
        std::make_shared<std::vector<IgnoredTrajectory>>();
    std::shared_ptr<std::vector<StationaryObject>> stationary_objs_ =
        std::make_shared<std::vector<StationaryObject>>();
    std::vector<const SpacetimeObjectTrajectory *> considered_stationary_trajs_;
    std::vector<const SpacetimeObjectTrajectory *> considered_moving_trajs_;
};

}  // namespace planning
}  // namespace pnc_x
