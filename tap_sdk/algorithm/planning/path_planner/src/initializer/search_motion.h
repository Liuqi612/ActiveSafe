#pragma once

#include <string>

#include "async/thread_pool.h"
#include "decision/decider_output.h"
#include "decision/traffic_gap_finder.h"
#include "pncx_initializer.pb.h"
#include "initializer/initializer_input.h"
#include "initializer/initializer_output.h"
#include "scheduler/scheduler_output.h"
#include <absl/container/flat_hash_set.h>
#include <absl/status/statusor.h>

namespace pnc_x {
namespace planning {

absl::StatusOr<MotionSearchOutput> SearchMotion(
    const MotionSearchInput &motion_input, ThreadPool *thread_pool);

absl::StatusOr<TrafficGapResult> EvaluateBestGapFromSearch(
    const MotionSearchOutput &motion_out, const InitializerConfig &config);

absl::StatusOr<InitializerOutput> RunInitializer(
    const InitializerInput &initializer_input,
    absl::flat_hash_set<std::string> *unsafe_object_ids,
    SchedulerOutput *scheduler_output,
    DeciderOutput *decider_output,
    InitializerDebugProto *debug_proto,
    ThreadPool *thread_pool,
    std::map<std::string, bool> *obj_lead,
    pnc_x::planning::PlannerStatusProto::PlannerStatusCode *lc_status_code,
    double *last_lane_offset);

}  // namespace planning
}  // namespace pnc_x
