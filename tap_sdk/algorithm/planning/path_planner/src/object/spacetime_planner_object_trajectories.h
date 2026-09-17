
#pragma once

#include <string>
#include <utility>
#include <vector>
#include <regex>
#include <memory>
#include "object/spacetime_object_trajectory.h"
#include "pncx_planner_object.pb.h"
#include "util/map_util.h"
#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>

namespace pnc_x {
namespace planning {

struct SpacetimePlannerObjectTrajectories {
    std::shared_ptr<std::vector<SpacetimeObjectTrajectory>> trajectories =
        std::make_shared<std::vector<SpacetimeObjectTrajectory>>();
    std::shared_ptr<std::vector<SpacetimeObjectTrajectory>>
        extended_trajectories = trajectories;
    absl::flat_hash_map<std::string,
                        std::vector<const SpacetimeObjectTrajectory *>>
        extended_objects_id_map;
    absl::flat_hash_map<std::string, const SpacetimeObjectTrajectory *>
        extended_trajectories_id_map;

    struct TrajectoryInfo {
        int traj_index;
        std::string object_id;
        SpacetimePlannerObjectTrajectoryReason::Type reason;
    };
    std::vector<TrajectoryInfo> trajectory_infos;
    absl::flat_hash_set<std::string> trajectory_ids;
    double st_start_offset = 0.0;

    SpacetimePlannerObjectTrajectories() = default;

    SpacetimePlannerObjectTrajectories(
        SpacetimePlannerObjectTrajectories &&other) noexcept {
        *this = std::move(other);
    }

    SpacetimePlannerObjectTrajectories &operator=(
        SpacetimePlannerObjectTrajectories &&other) noexcept {
        if (this != &other) {
            trajectories = std::move(other.trajectories);
            extended_trajectories = std::move(other.extended_trajectories);
            if (!trajectories) {
                trajectories =
                    std::make_shared<std::vector<SpacetimeObjectTrajectory>>();
            }
            if (!extended_trajectories) {
                extended_trajectories = trajectories;
            }
            trajectory_infos = std::move(other.trajectory_infos);
            trajectory_ids = std::move(other.trajectory_ids);
            st_start_offset = other.st_start_offset;
            SetExtendTrajectoryMap();
        }
        return *this;
    }

    void SetExtendTrajectoryMap() {
        extended_objects_id_map.clear();
        extended_trajectories_id_map.clear();
        for (const auto &traj : *extended_trajectories) {
            extended_objects_id_map[traj.planner_object().id()].push_back(
                &traj);
            extended_trajectories_id_map[traj.traj_id()] = &traj;
        }
    }

    absl::Span<const SpacetimeObjectTrajectory *const>
    FindTrajectoriesByObjectId(std::string id) const {
        for (const auto &kv : extended_objects_id_map) {
            const auto &tid = kv.first;
            const auto &traj = kv.second;
            std::regex pattern("^" + id + "-.+");
            if (id == tid || std::regex_match(tid, pattern)) {
                return traj;
            }
        }
        return {};
    }

    const PlannerObject *FindObjectByObjectId(std::string id) const {
        const auto iter = extended_objects_id_map.find(id);
        if (iter == extended_objects_id_map.end()) { return nullptr; }
        return &(iter->second.front()->planner_object());
    }

    const SpacetimeObjectTrajectory *FindTrajectoryById(
        absl::string_view traj_id) const {
        auto str = std::string(traj_id);
        return FindPtrOrNull(extended_trajectories_id_map, str);
    }

    void AddSpacetimePlannerObjectTrajectory(
        SpacetimeObjectTrajectory input_trajectory,
        const SpacetimePlannerObjectTrajectoryReason::Type reason) {
        if (!trajectory_ids.contains(input_trajectory.traj_id())) {
            (void)trajectory_ids.insert(std::string(input_trajectory.traj_id()));
            trajectory_infos.push_back(
                {.traj_index = input_trajectory.traj_index(),
                 .object_id = input_trajectory.planner_object().id(),
                 .reason = reason});
            trajectories->push_back(std::move(input_trajectory));
        }
    }

    void ToProto(SpacetimePlannerObjectTrajectoriesProto *proto) const {
        const int num_trajs = trajectories->size();
        proto->mutable_trajectory()->Reserve(num_trajs);
        for (int i = 0; i < num_trajs; ++i) {
            auto *traj_proto = proto->add_trajectory();
            traj_proto->set_reason(trajectory_infos[i].reason);
            traj_proto->set_id(std::string((*trajectories)[i].traj_id()));
            traj_proto->set_index((*trajectories)[i].traj_index());
            auto *traj = traj_proto->mutable_predicted_trajectory();
            (*trajectories)[i].trajectory().ToProto(traj, false);
        }
    }
};

}  // namespace planning
}  // namespace pnc_x
