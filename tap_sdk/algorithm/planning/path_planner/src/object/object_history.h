
#pragma once

#include "pncx_planner_object.pb.h"
#include "speed/st_boundary_with_decision.h"
#include "pncx_speed_finder.pb.h"
#include "util/hmi_content_util.h"
#include "util/time_util.h"
#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>
#include <boost/optional.hpp>

namespace pnc_x {
namespace planning {

struct ObjectFrame {
    std::string id;
    int64_t timestamp;
    ObjectProto object_proto;
    bool is_leading = true;
    bool is_stalled = false;
    bool is_nudge = false;
    boost::optional<double> desired_follow_time_headway = boost::none;

    StBoundaryProto::DecisionType lon_decision = StBoundaryProto::UNKNOWN;
    SpacetimePlannerObjectTrajectoryReason::Type lat_decision =
        SpacetimePlannerObjectTrajectoryReason::NONE;
};

class ObjectHistory {
 public:
    std::deque<ObjectFrame> &GetFrames();
    const ObjectFrame *GetOldestFrame() const;
    const ObjectFrame *GetLatestFrame() const;
    const ObjectFrame *GetFrameByTimestamp(const int64_t timestamp) const;
    const size_t Size() const;
    bool Empty() const;
    void CleanExceeded(const int64_t exceeded_timestamp);

 private:
    std::deque<ObjectFrame> frames_;
};

class ObjectHistoryManager {
 public:
    using ObjectsFrame = absl::flat_hash_map<std::string, ObjectFrame>;
    ObjectHistoryManager() = default;
    ~ObjectHistoryManager() = default;

    bool HasObject(absl::string_view obj_id);
    const ObjectHistory *GetObjHistory(absl::string_view obj_id) const;
    const ObjectFrame *GetObjLatestFrame(absl::string_view obj_id) const;
    const ObjectFrame *GetFrameByTimestamp(absl::string_view obj_id,
                                           const int64_t timestamp) const;

    void CleanExceeded(const int64_t cur_timestamp);
    void Clear();

    void AddObjectsFrameToHistory(
        absl::flat_hash_map<std::string, ObjectFrame> &&objects_frame);

 private:
    absl::flat_hash_map<std::string, ObjectHistory> obj_history_map_;
    static constexpr int64_t kMaxHistoryLengthUs = 1e6;
};

void UpdateObjectsHistory(
    ObjectHistoryManager &obj_history_mgr,
    const boost::optional<ObjectsProto> &objects_proto,
    const std::vector<StBoundaryWithDecision> &st_boundaries_with_decision,
    const SpacetimePlannerObjectTrajectoriesProto &st_planner_obj_trjs,
    const std::map<std::string, bool> &obj_leading,
    const absl::flat_hash_set<std::string> &stalled_objects,
    const boost::optional<NudgeObjectInfo> &nudge_info,
    int plan_id);

}  // namespace planning
}  // namespace pnc_x
