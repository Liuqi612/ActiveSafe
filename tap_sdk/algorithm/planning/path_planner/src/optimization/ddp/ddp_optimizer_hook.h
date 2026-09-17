
#pragma once

#include <string>
#include <vector>

#include "math/eigen.h"
#include "math/vec.h"
#include "optimization/problem/cost.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class DdpOptimizerHook {
 public:
    using StateType = typename PROB::StateType;
    using ControlType = typename PROB::ControlType;
    using StatesType = typename PROB::StatesType;
    using ControlsType = typename PROB::ControlsType;

    struct OptimizerInspector {
        double cost;
        double js0;

        std::vector<NamedCostEntry> named_costs;
    };

    explicit DdpOptimizerHook(int horizon) : horizon_(horizon) {
        XCHECK_GT(horizon_, 0);
    }

    virtual ~DdpOptimizerHook() = default;
    virtual void OnSolveStart(const StatesType &xs,
                              const ControlsType &us,
                              const OptimizerInspector &oi) {}
    virtual void OnSolveEnd(const StatesType &xs,
                            const ControlsType &us,
                            const OptimizerInspector &oi) {}
    virtual void OnIterationStart(int iter,
                                  const StatesType &xs,
                                  const ControlsType &us,
                                  const OptimizerInspector &oi) {}
    virtual void OnIterationEnd(int iter,
                                const StatesType &xs,
                                const ControlsType &us,
                                const OptimizerInspector &oi) {}
    virtual void OnLineSearchIterationStart(int iter,
                                            const StatesType &xs,
                                            const ControlsType &us,
                                            const StatesType &full_dxs,
                                            const ControlsType &full_dus,
                                            double alpha,
                                            const OptimizerInspector &oi) {}
    virtual void OnLineSearchIterationEnd(int iter,
                                          const StatesType &xs,
                                          const ControlsType &us,
                                          const StatesType &full_dxs,
                                          const ControlsType &full_dus,
                                          double alpha,
                                          double cost,
                                          const OptimizerInspector &oi) {}
    virtual void OnStepSizeAdjustmentIterationStart(
        int iter,
        const StatesType &xs,
        const ControlsType &us,
        int k_stepsize,
        const OptimizerInspector &oi) {}
    virtual void OnStepSizeAdjustmentIterationEnd(
        int iter,
        const StatesType &xs,
        const ControlsType &us,
        int k_stepsize,
        double cost,
        const OptimizerInspector &oi) {}

    int horizon() const { return horizon_; }

 private:
    int horizon_ = 0;
};

}  // namespace planning
}  // namespace pnc_x
