
#pragma once

#include <cmath>
#include <string>
#include <utility>
#include <vector>

#include "math/util.h"
#include "optimization/problem/cost.h"
#include "optimization/problem/mixed_fourth_order_bicycle.h"
#include <Eigen/Eigen>
#include <absl/strings/str_cat.h>

namespace pnc_x {
namespace planning {

template <typename PROB>
class CurvatureCost : public Cost<PROB> {
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

    static constexpr double kNormalizedScale = 0.1;
    explicit CurvatureCost(double curvature_buffer,
                           int buffer_index,
                           int free_index,
                           double scale_free,
                           std::string local_name = absl::StrCat(PROB::kProblemPrefix,
                                                           "CurvatureCost"),
                           double local_scale = 1.0,
                           CostType local_cost_type = Cost<PROB>::CostType::MUST_HAVE)
        : Cost<PROB>(std::move(local_name), local_scale * kNormalizedScale, local_cost_type),
          curvature_buffer_(curvature_buffer),
          buffer_index_(buffer_index),
          free_index_(free_index),
          curvature_free_gain_(scale_free) {}

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        DividedG res(1);
        for (int k = 0; k < horizon; ++k) {
            const double gain = k < free_index_ ? curvature_free_gain_ : 1.0;
            res.AddSubG(0, gain * Sqr(PROB::kappa(xs, k)));
            if (k < buffer_index_ &&
                std::fabs(PROB::kappa(xs, k)) > curvature_buffer_) {
                res.AddSubG(
                    0, kMaxBufferGain * Sqr(PROB::kappa(xs, k) -
                                            std::copysign(curvature_buffer_,
                                                          PROB::kappa(xs, k))));
            }
        }
        res.SetSubName(0, Cost<PROB>::name());
        res.Multi(0.5 * Cost<PROB>::scale());
        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        const double gain = k < free_index_ ? curvature_free_gain_ : 1.0;
        double g =
            0.5 * gain * Cost<PROB>::scale() * Sqr(x[PROB::kStateKappaIndex]);
        if (k < buffer_index_ &&
            std::fabs(x[PROB::kStateKappaIndex]) > curvature_buffer_) {
            g += 0.5 * kMaxBufferGain * Cost<PROB>::scale() *
                 Sqr(x[PROB::kStateKappaIndex] -
                     std::copysign(curvature_buffer_,
                                   x[PROB::kStateKappaIndex]));
        }
        return g;
    }

    void AddDGDx(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDxType *dgdx) const override {
        const double gain = k < free_index_ ? curvature_free_gain_ : 1.0;

        (*dgdx)[PROB::kStateKappaIndex] +=
            gain * Cost<PROB>::scale() * x[PROB::kStateKappaIndex];
        if (k < buffer_index_ &&
            std::fabs(x[PROB::kStateKappaIndex]) > curvature_buffer_) {
            (*dgdx)[PROB::kStateKappaIndex] +=
                kMaxBufferGain * Cost<PROB>::scale() *
                (x[PROB::kStateKappaIndex] -
                 std::copysign(curvature_buffer_, x[PROB::kStateKappaIndex]));
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
        const double gain = k < free_index_ ? curvature_free_gain_ : 1.0;
        (*ddgdxdx)(PROB::kStateKappaIndex, PROB::kStateKappaIndex) +=
            gain * Cost<PROB>::scale();
        if (k < buffer_index_ &&
            std::fabs(x[PROB::kStateKappaIndex]) > curvature_buffer_) {
            (*ddgdxdx)(PROB::kStateKappaIndex, PROB::kStateKappaIndex) +=
                kMaxBufferGain * Cost<PROB>::scale();
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

 protected:
    double curvature_buffer_;
    int buffer_index_;
    int free_index_;
    double curvature_free_gain_;
    static constexpr double kMaxBufferGain = 10000.0;
};

}  // namespace planning
}  // namespace pnc_x
