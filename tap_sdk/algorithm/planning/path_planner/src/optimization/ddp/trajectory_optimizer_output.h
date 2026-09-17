
#pragma once

#include <string>
#include <vector>

#include "optimization/ddp/ddp_optimizer_debug_hook.h"
#include "optimization/ddp/per_step_cost_recorder_hook.h"
#include "optimization/ddp/trajectory_optimizer_defs.h"
#include "optimization/ddp/trajectory_optimizer_state.h"
#include "plan/trajectory_point.h"
#include "pncx_planner.pb.h"
#include "util/hmi_content_util.h"

namespace pnc_x {
namespace planning {

struct DdpDebugBuildArgs {
  // 轨迹
  std::vector<TrajectoryPoint> astart_traj;
  std::vector<TrajectoryPoint> solve_init_traj;
  std::vector<TrajectoryPoint> final_traj;

  // 迭代hook & 单步hook
  std::unique_ptr<OptimizerSolverDebugHook<optimizer::Mfob>> solver_debug_hook;
  std::unique_ptr<PerStepCostRecorderHook<optimizer::Mfob>> perstep_hook;

  // 运行时间
  double solve_time_ms = 0.0;
  double add_cost_time_ms = 0.0;

  // 初始轨迹来源
  std::string solver_init_traj_source;

  // nudge 列表（可为空）
  NudgeInfos nudge_infos;  
  
  // L 信息
  std::vector<double> solve_init_traj_l_info;
  std::vector<double> final_traj_l_info;

  DdpDebugBuildArgs() = default;
};

struct TrajectoryOptimizerOutput {
  std::vector<TrajectoryPoint> trajectory;
  std::vector<ApolloTrajectoryPointProto> trajectory_proto;

  boost::optional<NudgeObjectInfo> nudge_object_info;

  TrajectoryOptimizerState trajectory_optimizer_state;
  boost::optional<ads_x::planning::BorrowDirection> borrow_direction;

  DdpDebugBuildArgs ddp_debug_args;

  SamplingTrajectoryInfo sample_step_info;
};

} // namespace planning
} // namespace pnc_x
