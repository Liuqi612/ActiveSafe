#include "object_history.h"

namespace pnc_x {
namespace planning {

std::deque<ObjectFrame> &ObjectHistory::GetFrames() { return frames_; }

const ObjectFrame *ObjectHistory::GetOldestFrame() const {
    if (Empty()) {
        return nullptr;
    }
    return &(frames_.front());
}
const ObjectFrame *ObjectHistory::GetLatestFrame() const {
    if (Empty()) {
        return nullptr;
    }
    return &(frames_.back());
}
const ObjectFrame *ObjectHistory::GetFrameByTimestamp(
    const int64_t timestamp) const {
    if (Empty()) {
        return nullptr;
    }
    auto it = std::lower_bound(frames_.begin(), frames_.end(), timestamp,
                               [](const ObjectFrame &frame, int64_t ts) {
                                   return frame.timestamp < ts;
                               });

    if (it == frames_.end()) {
        return GetLatestFrame();
    } else if (it == frames_.begin()) {
        return GetOldestFrame();
    } else {
        auto prev_it = std::prev(it);
        return ((timestamp - prev_it->timestamp) < (it->timestamp - timestamp))
                   ? &(*prev_it)
                   : &(*it);
    }
}
const size_t ObjectHistory::Size() const { return frames_.size(); }
bool ObjectHistory::Empty() const { return frames_.empty(); }
void ObjectHistory::CleanExceeded(const int64_t exceeded_timestamp) {
    auto iter =
        std::lower_bound(frames_.begin(), frames_.end(), exceeded_timestamp,
                         [](const ObjectFrame &data, int64_t value) {
                             return data.timestamp < value;
                         });
    frames_.erase(frames_.begin(), iter);
}

bool ObjectHistoryManager::HasObject(absl::string_view obj_id) {
    return obj_history_map_.find(std::string(obj_id)) != obj_history_map_.end();
}
const ObjectHistory *ObjectHistoryManager::GetObjHistory(
    absl::string_view obj_id) const {
    const auto iter = obj_history_map_.find(std::string(obj_id));
    if (iter == obj_history_map_.end()) return nullptr;
    return &(iter->second);
}
const ObjectFrame *ObjectHistoryManager::GetObjLatestFrame(
    absl::string_view obj_id) const {
    const auto iter = obj_history_map_.find(std::string(obj_id));
    if (iter == obj_history_map_.end()) return nullptr;
    return iter->second.GetLatestFrame();
}
const ObjectFrame *ObjectHistoryManager::GetFrameByTimestamp(
    absl::string_view obj_id, const int64_t timestamp) const {
    return GetObjHistory(obj_id)->GetFrameByTimestamp(timestamp);
}

void ObjectHistoryManager::CleanExceeded(const int64_t cur_timestamp) {
    int64_t exceeded_timestamp = cur_timestamp - kMaxHistoryLengthUs;
    std::vector<std::string> to_erase;
    for (auto it = obj_history_map_.begin(); it != obj_history_map_.end();
         ++it) {
        it->second.CleanExceeded(exceeded_timestamp);
        if (it->second.Empty()) {
            to_erase.push_back(it->first);
        }
    }
    for (auto &id : to_erase) {
        obj_history_map_.erase(id);
    }
}
void ObjectHistoryManager::Clear() { obj_history_map_.clear(); }

void ObjectHistoryManager::AddObjectsFrameToHistory(
    absl::flat_hash_map<std::string, ObjectFrame> &&objects_frame) {
    for (auto &pair : objects_frame) {
        const std::string &obj_id = pair.first;
        ObjectFrame &obj_frame = pair.second;
        auto iter_pair = obj_history_map_.emplace(obj_id, ObjectHistory());
        auto &iter = iter_pair.first;
        iter->second.GetFrames().emplace_back(std::move(obj_frame));
    }
}

void UpdateObjectsHistory(
    ObjectHistoryManager &obj_history_mgr,
    const boost::optional<ObjectsProto> &objects_proto,
    const std::vector<StBoundaryWithDecision> &st_boundaries_with_decision,
    const SpacetimePlannerObjectTrajectoriesProto &st_planner_obj_trjs,
    const std::map<std::string, bool> &obj_leading,
    const absl::flat_hash_set<std::string> &stalled_objects,
    const boost::optional<NudgeObjectInfo> &nudge_info,
    int plan_id) {
    const int64_t cur_timestamp = objects_proto->header().timestamp();
    obj_history_mgr.CleanExceeded(cur_timestamp);
    absl::flat_hash_map<std::string, ObjectFrame> objects_frame;

    for (const auto &object : objects_proto->objects()) {
        objects_frame.try_emplace(object.id(),
                                  ObjectFrame{.id = object.id(),
                                              .timestamp = cur_timestamp,
                                              .object_proto = object});

        if (nudge_info.has_value() && (object.id() == nudge_info->id)) {
            objects_frame[object.id()].is_nudge = true;
        }
    }

    for (const auto &lead : obj_leading) {
        objects_frame.at(lead.first).is_leading = lead.second;
    }
    for (const auto &stalled : stalled_objects) {
        objects_frame.at(stalled).is_stalled = true;
    }

    for (const auto &boundary_with_decision : st_boundaries_with_decision) {
        if (!boundary_with_decision.object_id().has_value()) {
            continue;
        }
        std::string obs_idx = boundary_with_decision.id();
        std::string obj_id = boundary_with_decision.object_id().value();
        objects_frame.at(obj_id).lon_decision =
            boundary_with_decision.decision_type();

        if (boundary_with_decision.st_boundary()) {
            const auto &obj_scene_info =
                boundary_with_decision.st_boundary()->obj_scenario_info();
            const auto &param = obj_scene_info.obj_decision_param;
            if (param.desired_follow_time_headway.has_value()) {
                objects_frame.at(obj_id).desired_follow_time_headway =
                    param.desired_follow_time_headway;
            }
        }
    }

    for (size_t i = 0UL;
         i < static_cast<unsigned long>(st_planner_obj_trjs.trajectory_size());
         ++i) {
        std::string obj_id =
            st_planner_obj_trjs.trajectory(static_cast<int>(i)).id();
        objects_frame.at(obj_id).lat_decision =
            st_planner_obj_trjs.trajectory(static_cast<int>(i)).reason();
    }

    obj_history_mgr.AddObjectsFrameToHistory(std::move(objects_frame));
}
}  // namespace planning
}  // namespace pnc_x
