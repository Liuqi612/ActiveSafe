
#pragma once

#include <string>
#include <utility>
#include <vector>

#include <Eigen/Core>
#include <absl/strings/str_cat.h>

#include "math/util.h"
#include "optimization/problem/cost.h"
#include "optimization/problem/mixed_fourth_order_bicycle.h"
#include "common/log.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class ReferenceStateDeviationCost : public Cost<PROB> {
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
    ReferenceStateDeviationCost(
        StatesType ref_xs,
        std::vector<double> weights = {},
        std::string name = absl::StrCat(PROB::kProblemPrefix,
                                        "ReferenceStateDeviationCost"),
        double scale = 1.0,
        CostType cost_type = Cost<PROB>::CostType::MUST_HAVE)
        : Cost<PROB>(std::move(name), scale * kNormalizedScale, cost_type),
          ref_xs_(std::move(ref_xs)),
          weights_(weights.empty() ? std::vector<double>(ref_xs_.size(), 1.0)
                                   : std::move(weights)) {
        XCHECK_EQ(ref_xs_.size(), weights_.size());
    }

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        XCHECK_EQ(xs.rows(), ref_xs_.rows());
        DividedG res(1);
        res.SetSubName(0, Cost<PROB>::name());
        for (int k = 0; k < horizon; ++k) {
            StateType x_diff =
                PROB::GetStateAtStep(xs, k) - PROB::GetStateAtStep(ref_xs_, k);
            x_diff[PROB::kStateThetaIndex] =
                NormalizeAngle(x_diff[PROB::kStateThetaIndex]);
            for (int i = 0; i < PROB::kStateSize; ++i) {
                res.AddSubG(
                    0, Sqr(x_diff[i]) * weights_[(k * PROB::kStateSize) + i]);
            }
        }
        res.Multi(0.5 * Cost<PROB>::scale());
        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        StateType x_diff = x - PROB::GetStateAtStep(ref_xs_, k);
        x_diff[PROB::kStateThetaIndex] =
            NormalizeAngle(x_diff[PROB::kStateThetaIndex]);
        double g = 0.0;
        for (int i = 0; i < PROB::kStateSize; ++i) {
            g += Sqr(x_diff[i]) * weights_[(k * PROB::kStateSize) + i];
        }
        g *= 0.5 * Cost<PROB>::scale();
        return g;
    }

    void AddDGDx(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDxType *dgdx) const override {
        StateType x_diff = x - PROB::GetStateAtStep(ref_xs_, k);
        x_diff[PROB::kStateThetaIndex] =
            NormalizeAngle(x_diff[PROB::kStateThetaIndex]);
        for (int i = 0; i < PROB::kStateSize; ++i) {
            (*dgdx)[i] += Cost<PROB>::scale() * x_diff[i] *
                          weights_[(k * PROB::kStateSize) + i];
        }
    }
    void AddDGDu(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDuType *dgdu) const override {}

    void AddDDGDxDx(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDxDxType *ddgdxdx) const override {
        for (int i = 0; i < PROB::kStateSize; ++i) {
            (*ddgdxdx)(i, i) +=
                Cost<PROB>::scale() * weights_[(k * PROB::kStateSize) + i];
        }
    }
    void AddDDGDuDx(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDuDxType *ddgdudx) const override {}
    void AddDDGDuDu(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDuDuType *ddgdudu) const override {}

 private:
    StatesType ref_xs_;
    std::vector<double> weights_;
};

}  // namespace planning
}  // namespace pnc_x
