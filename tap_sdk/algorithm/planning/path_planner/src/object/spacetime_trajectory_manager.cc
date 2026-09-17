

#include <algorithm>
#include <iterator>
#include <ostream>

#include "async/parallel_for.h"
#include "object/spacetime_trajectory_manager.h"

#include "object/trajectory_filter.h"
#include "pncx_perception.pb.h"
#include "prediction/prediction.h"

namespace pnc_x {
namespace planning {
SpacetimeTrajectoryManager::SpacetimeTrajectoryManager(
    absl::Span<const TrajectoryFilter *const> filters,
    absl::Span<const PlannerObject> planner_objects,
    ThreadPool *thread_pool) {
    const int num_objects = planner_objects.size();
    NestedVector<SpacetimeObjectTrajectory> considered_trajs_per_object(
        num_objects);
    NestedVector<IgnoredTrajectory> ignored_trajs_per_object(num_objects);
    NestedVector<StationaryObject> stationary_per_object(num_objects);

    ParallelFor(0, num_objects, thread_pool, [&](int i) {
        const auto &planner_obj = planner_objects[i];
        const auto &trajectories = planner_obj.prediction().trajectories();
        XCHECK(!trajectories.empty());
        if (planner_obj.is_stationary()) {
            stationary_per_object[i].push_back(
                {.object_id = planner_obj.id(), .planner_object = planner_obj});
        }
        for (int traj_index = 0, s = trajectories.size(); traj_index < s;
             ++traj_index) {
            const auto &pred_traj = trajectories[traj_index];
            bool filtered = false;
            for (const auto *filter : filters) {
                const auto filter_reason =
                    filter->Filter(planner_obj, pred_traj);
                if (filter_reason != FilterReason::NONE) {
                    IgnoredTrajectory ignored_traj;
                    ignored_traj.traj = &pred_traj;
                    ignored_traj.object_id = planner_obj.id();
                    ignored_traj.reason = filter_reason;
                    ignored_trajs_per_object[i].push_back(ignored_traj);
                    filtered = true;
                    break;
                }
            }
            if (filtered) continue;

            const double required_lateral_gap =
                ComputeRequiredLateralGap(planner_obj);
            considered_trajs_per_object[i].emplace_back(planner_obj, traj_index,
                                                        required_lateral_gap);
        }
    });

    int trajectories_size = 0;
    for (const auto &planner_object : planner_objects) {
        trajectories_size += planner_object.prediction().trajectories().size();
    }
    considered_trajs_->reserve(trajectories_size);
    ignored_trajs_->reserve(trajectories_size);

    int stationary_count = 0;
    for (auto &trajs : considered_trajs_per_object) {
        for (const auto &traj : trajs) {
            if (traj.is_stationary()) stationary_count++;
        }
        std::move(trajs.begin(), trajs.end(),
                  std::back_inserter(*considered_trajs_));
    }
    for (auto &trajs : ignored_trajs_per_object) {
        std::move(trajs.begin(), trajs.end(),
                  std::back_inserter(*ignored_trajs_));
    }
    for (auto &obj : stationary_per_object) {
        std::move(obj.begin(), obj.end(),
                  std::back_inserter(*stationary_objs_));
    }

    UpdatePointers(stationary_count);
}

SpacetimeTrajectoryManager::SpacetimeTrajectoryManager(
    absl::Span<SpacetimeObjectTrajectory> spacetime_trajectories) {
    const int traj_size = spacetime_trajectories.size();
    considered_trajs_->reserve(traj_size);
    int stationary_count = 0;
    for (auto &traj : spacetime_trajectories) {
        if (traj.is_stationary()) {
            stationary_count++;
        }
        considered_trajs_->push_back(std::move(traj));
    }
    UpdatePointers(stationary_count);
}

SpacetimeTrajectoryManager::SpacetimeTrajectoryManager(
    const SpacetimeTrajectoryManager &other) {
    *this = other;
}

SpacetimeTrajectoryManager &SpacetimeTrajectoryManager::operator=(
    const SpacetimeTrajectoryManager &other) {
    if (this != &other) {
        ignored_trajs_ = other.ignored_trajs_;
        considered_trajs_ = other.considered_trajs_;
        stationary_objs_ = other.stationary_objs_;
        UpdatePointers(other.considered_stationary_trajs_.size());
    }
    return *this;
}

void SpacetimeTrajectoryManager::UpdatePointers(int stationary_size) {
    considered_stationary_trajs_.clear();
    considered_moving_trajs_.clear();
    objects_id_map_.clear();
    trajectories_id_map_.clear();
    const int traj_size = considered_trajs_->size();
    considered_stationary_trajs_.reserve(stationary_size);
    XCHECK_GE(traj_size, stationary_size);
    considered_moving_trajs_.reserve(traj_size - stationary_size);
    objects_id_map_.reserve(traj_size);
    trajectories_id_map_.reserve(traj_size);
    for (const auto &traj : *considered_trajs_) {
        if (traj.is_stationary()) {
            considered_stationary_trajs_.push_back(&traj);
        } else {
            considered_moving_trajs_.push_back(&traj);
        }

        objects_id_map_[traj.planner_object().id()].push_back(&traj);
        trajectories_id_map_[traj.traj_id()] = &traj;
    }
}

}  // namespace planning
}  // namespace pnc_x
