
#pragma once

#include <vector>

#include "math/eigen.h"
#include "optimization/ddp/ddp_optimizer_hook.h"
#include "optimization/problem/cost.h"
#include "optimization/problem/cost_helper.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class DdpCostManagerHook : public DdpOptimizerHook<PROB> {
 public:
    using OptimizerInspector =
        typename DdpOptimizerHook<PROB>::OptimizerInspector;
    using StatesType = typename PROB::StatesType;
    using ControlsType = typename PROB::ControlsType;

    explicit DdpCostManagerHook(int horizon)
        : DdpOptimizerHook<PROB>(horizon) {}

    void OnSolveStart(const StatesType &xs,
                      const ControlsType &us,
                      const OptimizerInspector &oi) override {
        for (auto *helper : helpers_) {
            helper->Update(xs, us);
        }
        for (auto *cost : costs_) {
            cost->Update(xs, us, DdpOptimizerHook<PROB>::horizon());
        }
    }

    void OnIterationStart(int iter,
                          const StatesType &xs,
                          const ControlsType &us,
                          const OptimizerInspector &oi) override {
        for (auto *cost : costs_) {
            cost->UpdateDerivatives(xs, us, DdpOptimizerHook<PROB>::horizon());
        }
    }

    void OnLineSearchIterationStart(int iter,
                                    const StatesType &xs,
                                    const ControlsType &us,
                                    const StatesType &full_dxs,
                                    const ControlsType &full_dus,
                                    double alpha,
                                    const OptimizerInspector &oi) override {
        for (auto *helper : helpers_) {
            helper->Update(xs, us);
        }
        for (auto *cost : costs_) {
            cost->Update(xs, us, DdpOptimizerHook<PROB>::horizon());
        }
    }

    void OnStepSizeAdjustmentIterationStart(
        int iter,
        const StatesType &xs,
        const ControlsType &us,
        int k_stepsize,
        const OptimizerInspector &oi) override {
        for (auto *helper : helpers_) {
            helper->Update(xs, us);
        }
        for (auto *cost : costs_) {
            cost->Update(xs, us, DdpOptimizerHook<PROB>::horizon());
        }
    }

    void AddCost(Cost<PROB> *cost) {
        if (!XCHECK(cost != nullptr)) {
            return;
        }
        costs_.push_back(cost);
    }
    void AddCostHelper(CostHelper<PROB> *helper) {
        if (!XCHECK(helper != nullptr)) {
            return;
        }
        helpers_.push_back(helper);
    }

 private:
    std::vector<Cost<PROB> *> costs_;
    std::vector<CostHelper<PROB> *> helpers_;
};

}  // namespace planning
}  // namespace pnc_x
