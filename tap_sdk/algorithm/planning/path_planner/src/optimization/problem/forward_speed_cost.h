
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "math/util.h"
#include "optimization/problem/cost.h"
#include <absl/strings/str_cat.h>

namespace pnc_x {
namespace planning {

template <typename PROB>
class ForwardSpeedCost : public Cost<PROB> {
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

    static constexpr double kNormalizedScale = 1000.0;
    explicit ForwardSpeedCost(
        std::string name = absl::StrCat(PROB::kProblemPrefix,
                                        "ForwardSpeedCost"),
        double scale = 1.0,
        CostType cost_type = Cost<PROB>::CostType::MUST_HAVE)
        : Cost<PROB>(std::move(name), scale * kNormalizedScale, cost_type) {}

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        DividedG res(1);
        for (int k = 0; k < horizon; ++k) {
            res.AddSubG(0, SingleSideSqr(-PROB::v(xs, k)));
        }
        res.Multi(0.5 * Cost<PROB>::scale());
        res.SetSubName(0, Cost<PROB>::name());
        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        return 0.5 * Cost<PROB>::scale() * SingleSideSqr(-PROB::StateGetV(x));
    }

    void AddDGDx(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDxType *dgdx) const override {
        (*dgdx)[PROB::kStateVIndex] -=
            Cost<PROB>::scale() * ReLU(-PROB::StateGetV(x));
    }
    void AddDGDu(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDuType *dgdu) const override {}

    void AddDDGDxDx(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDxDxType *ddgdxdx) const override {
        const double speed_penalty = (PROB::StateGetV(x) < 0.0) ? 1.0 : 0.0;
        (*ddgdxdx)(PROB::kStateVIndex, PROB::kStateVIndex) +=
            Cost<PROB>::scale() * speed_penalty;
    }
    void AddDDGDuDx(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDuDxType *ddgdudx) const override {}
    void AddDDGDuDu(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDuDuType *ddgdudu) const override {}
};

}  // namespace planning
}  // namespace pnc_x
