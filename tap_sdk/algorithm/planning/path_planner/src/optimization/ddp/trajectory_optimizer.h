
#pragma once

#include "async/thread_pool.h"
#include "optimization/ddp/per_step_cost_recorder_hook.h"
#include "optimization/ddp/trajectory_optimizer_defs.h"
#include "optimization/ddp/trajectory_optimizer_input.h"
#include "optimization/ddp/trajectory_optimizer_output.h"
#include "pncx_optimizer.pb.h"
#include <absl/status/statusor.h>

namespace pnc_x {
namespace planning {
  
absl::StatusOr<TrajectoryOptimizerOutput>
OptimizeTrajectory(const TrajectoryOptimizerInput &input,
                   TrajectoryOptimizerDebugProto *optimizer_debug,
                   bool is_compare_weight, ThreadPool *thread_pool);

struct ChangIndexInfo {
  enum TopoActionType { TYPE_NONE = 0, TYPE_SPLIT = 1, TYPE_MERGE = 2 };
  TopoActionType topo_action{TYPE_NONE};
  int start_point_index{0};
  int key_point_index{0};
  double key_point_s{0.0};
};
} // namespace planning
} // namespace pnc_x
