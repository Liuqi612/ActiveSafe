
#pragma once

#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "math/geometry/util.h"
#include "math/vec.h"
#include "object/spacetime_trajectory_manager.h"
#include "optimization/ddp/ddp_optimizer_hook.h"
#include "pncx_optimizer.pb.h"
#include "plan/planner_defs.h"
#include "plan/trajectory_point.h"
#include "pncx_vehicle.pb.h"
#include <absl/container/flat_hash_map.h>

namespace pnc_x {
namespace planning {

constexpr double kTrajVisZInc =
    kSpaceTimeVisualizationDefaultTimeScale * kTrajectoryTimeStep;
template <typename PROB>
struct OptimizerSolverDebugHook : public DdpOptimizerHook<PROB> {
 public:
    using ObjectResponseProto =
        TrajectoryOptimizerDebugProto::ObjectResponseProto;

    OptimizerSolverDebugHook(int horizon,
                             const TrajectoryPoint &av_pose,
                             const SpacetimeTrajectoryManager &st_traj_mgr)
        : DdpOptimizerHook<PROB>(horizon), av_pose_(av_pose) {
        for (const auto &traj : st_traj_mgr.trajectories()) {
            object_map[traj.traj_id()] = &traj;
        }
    }

    using OptimizerInspector =
        typename DdpOptimizerHook<PROB>::OptimizerInspector;
    using StatesType = typename PROB::StatesType;
    using ControlsType = typename PROB::ControlsType;

    void OnSolveStart(const StatesType &xs,
                      const ControlsType &us,
                      const OptimizerInspector &oi) override {
        solve_start_xs = xs;
        solve_start_us = us;
        iterations.clear();
        object_responses.clear();
        init_costs.ddp_costs.clear();
        final_costs.ddp_costs.clear();
    }

    void OnSolveEnd(const StatesType &xs,
                    const ControlsType &us,
                    const OptimizerInspector &oi) override {
        solve_end_xs = xs;
        solve_end_us = us;

        static const std::regex obj_response_cost_regex =
            std::regex(".+for (.+)-(\\w+)");
        for (const auto &named_cost : oi.named_costs) {
            const std::string &cost_name = named_cost.name;
            double cost = named_cost.value;
            // A0_1_1-a: is_soft assigned but never used
            // bool is_soft = named_cost.is_soft;
            std::smatch obj_response_cost_match;
            if (!std::regex_match(cost_name, obj_response_cost_match,
                                  obj_response_cost_regex)) {
                continue;
            }

            // constexpr double kCostThresholdResponse = 1.0;

            // if (cost < kCostThresholdResponse) continue;

            XCHECK_EQ(obj_response_cost_match.size(), 3);
            const std::string obj_id = obj_response_cost_match[1];
            const std::string obj_pred_index = obj_response_cost_match[2];

            const std::string obj_traj_name = obj_id + "-" + obj_pred_index;
            const auto it = object_map.find(obj_traj_name);
            if (it == object_map.end()) {
                // LOG(ERROR) << "Unknown object ID " << obj_id << " from cost
                // name "
                //            << cost_name;
                continue;
            }
            const SpacetimeObjectTrajectory &st_obj = *(it->second);
            // C++14 does not support emplace_back() returning a reference, so
            // use push_back and get reference
            object_responses.push_back(ObjectResponseProto());
            ObjectResponseProto &response = object_responses.back();
            response.set_object_id(obj_traj_name);
            response.set_cost(cost);
            response.set_cost_name(cost_name);

            response.set_peak_step(0);
            Vec2dToProto(st_obj.pose().pos(),
                         response.mutable_peak_object_position());
            const Vec2d force_dir =
                (st_obj.pose().pos() - av_pose_.pos()).normalized();
            Vec2dToProto(force_dir, response.mutable_peak_force_direction());
        }

        final_costs.cost = oi.cost;
        final_costs.ddp_costs.clear();
        for (const auto &named_cost : oi.named_costs) {
            // constexpr double kCostThresholdForLog = 1.0;
            // if (named_cost.value < kCostThresholdForLog) continue;
            final_costs.ddp_costs.push_back(named_cost);
        }
    }

    void OnIterationStart(int iteration,
                          const StatesType &xs,
                          const ControlsType &us,
                          const OptimizerInspector &oi) override {
        if (iteration >= iterations.size()) {
            iterations.emplace_back();
        }
        if (iteration == 0) {
            init_costs.cost = oi.cost;
            init_costs.ddp_costs.clear();
            for (const auto &named_cost : oi.named_costs) {
                constexpr double kCostThresholdForLog = 1.0;
                // if (named_cost.value < kCostThresholdForLog) continue;
                init_costs.ddp_costs.push_back(named_cost);
            }
        }
    }
    void OnIterationEnd(int iteration,
                        const StatesType &xs,
                        const ControlsType &us,
                        const OptimizerInspector &oi) override {
        XCHECK_EQ(iteration + 1, iterations.size());
        iterations.back().final_cost = oi.cost;
        iterations.back().js0 = oi.js0;
    }
    void OnLineSearchIterationEnd(int iteration,
                                  const StatesType &xs,
                                  const ControlsType &us,
                                  const StatesType &full_dxs,
                                  const ControlsType &full_dus,
                                  double alpha,
                                  double cost,
                                  const OptimizerInspector &oi) override {
        XCHECK_EQ(iteration + 1, iterations.size());
        auto &iter = iterations.back();
        iter.alphas.push_back(alpha);
        iter.line_search_costs.push_back(cost);
    }

    void OnStepSizeAdjustmentIterationEnd(
        int iteration,
        const StatesType &xs,
        const ControlsType &us,
        int k_stepsize,
        double cost,
        const OptimizerInspector &oi) override {
        XCHECK_EQ(iteration + 1, iterations.size());
        auto &iter = iterations.back();
        iter.k_s.push_back(k_stepsize);
        iter.stepsize_adjustment_costs.push_back(cost);
    }

    TrajectoryPoint av_pose_;
    absl::flat_hash_map<std::string, const SpacetimeObjectTrajectory *>
        object_map;

    StatesType solve_start_xs;
    ControlsType solve_start_us;

    StatesType solve_end_xs;
    ControlsType solve_end_us;

    struct CostDebugInfo {
        double cost;
        std::vector<NamedCostEntry> ddp_costs;
    };
    CostDebugInfo init_costs;
    CostDebugInfo final_costs;

    struct IterationDebugInfo {
        std::vector<double> alphas;
        std::vector<double> line_search_costs;
        std::vector<int> k_s;
        std::vector<double> stepsize_adjustment_costs;

        double final_cost;

        double js0;
    };
    std::vector<IterationDebugInfo> iterations;

    std::vector<ObjectResponseProto> object_responses;
};

}  // namespace planning
}  // namespace pnc_x
