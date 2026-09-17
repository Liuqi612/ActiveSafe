

#pragma once

#include <string>
#include <utility>
#include <vector>

#include "math/util.h"
#include "optimization/problem/cost.h"
#include "optimization/problem/mixed_fourth_order_bicycle.h"
#include <Eigen/Core>
#include <absl/strings/str_cat.h>

namespace pnc_x {
namespace planning {

template <typename PROB>
class ReferenceLongitudinalJerkDeviationCost : public Cost<PROB> {
 public:
    using StateType = typename PROB::StateType;
    using ControlType = typename PROB::ControlType;
    using StatesType = typename PROB::StatesType;
    using ControlsType = typename PROB::ControlsType;

    using GType = typename PROB::GType;
    using DGDxType = typename PROB::DGDxType;
    using DGDuType = typename PROB::DGDuType;
    using DDGDxDxType = typename PROB::DDGDxDxType;
    using DDGDxDuType = typename PROB::DDGDxDuType;
    using DDGDuDxType = typename PROB::DDGDuDxType;
    using DDGDuDuType = typename PROB::DDGDuDuType;

    using DividedG = typename Cost<PROB>::DividedG;

    using CostType = typename Cost<PROB>::CostType;

    static constexpr double kNormalizedScale = 1.0;
    ReferenceLongitudinalJerkDeviationCost(
        std::vector<double> ref_jerk,
        std::vector<double> weights,
        std::string name = absl::StrCat(
            PROB::kProblemPrefix, "ReferenceLongitudinalJerkDeviationCost"),
        double scale = 1.0,
        CostType cost_type = Cost<PROB>::CostType::GROUP_IMMEDIATE_FUTURE)
        : Cost<PROB>(std::move(name), scale * kNormalizedScale, cost_type),
          ref_jerk_(std::move(ref_jerk)),
          weights_(std::move(weights)) {
        const int horizon = static_cast<int>(ref_jerk_.size());
        XCHECK_EQ(horizon, weights_.size());
    }

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        DividedG res(1);
        XCHECK_EQ(horizon, weights_.size());
        for (int k = 0; k < horizon; ++k) {
            const double jerk_diff = PROB::j(us, k) - ref_jerk_[k];
            res.AddSubG(0, Sqr(jerk_diff) * weights_[k]);
        }
        res.SetSubName(0, Cost<PROB>::name());
        res.Multi(0.5 * Cost<PROB>::scale());
        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        const double jerk_diff = u[PROB::kControlJIndex] - ref_jerk_[k];
        return 0.5 * Cost<PROB>::scale() * Sqr(jerk_diff) * weights_[k];
    }

    void AddDGDx(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDxType *dgdx) const override {}
    void AddDGDu(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDuType *dgdu) const override {
        const double jerk_diff = u[PROB::kControlJIndex] - ref_jerk_[k];
        (*dgdu)[PROB::kControlJIndex] +=
            Cost<PROB>::scale() * jerk_diff * weights_[k];
    }

    void AddDDGDxDx(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDxDxType *ddgdxdx) const override {}
    void AddDDGDuDx(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDuDxType *ddgdudx) const override {}
    void AddDDGDuDu(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDuDuType *ddgdudu) const override {
        (*ddgdudu)(PROB::kControlJIndex, PROB::kControlJIndex) +=
            Cost<PROB>::scale() * weights_[k];
    }

 private:
    std::vector<double> ref_jerk_;
    std::vector<double> weights_;
};

}  // namespace planning
}  // namespace pnc_x
