

#include <algorithm>
#include <cmath>
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
class ReferenceSingleStateDeviationCost : public Cost<PROB> {
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
    ReferenceSingleStateDeviationCost(
        StateType ref_state,
        int ref_index,
        std::vector<double> weights,
        std::vector<double> base_numbers,
        std::string name_in = absl::StrCat(PROB::kProblemPrefix,
                                        "ReferenceSingleStateDeviationCost"),
        double scale_in = 1.0,
        CostType cost_type_in = Cost<PROB>::CostType::MUST_HAVE)
        : Cost<PROB>(std::move(name_in), scale_in * kNormalizedScale, cost_type_in),
          ref_state_(std::move(ref_state)),
          ref_index_(ref_index),
          weights_(std::move(weights)),
          base_numbers_(std::move(base_numbers)) {
        XCHECK_EQ(ref_state_.size(), weights_.size());
        XCHECK_EQ(ref_state_.size(), base_numbers_.size());
        ks_.resize(PROB::kStateSize, 0.0);
        bs_.resize(PROB::kStateSize, 0.0);
        for (int i = 0; i < PROB::kStateSize; ++i) {
            const double base_number = base_numbers_[i];
            XCHECK_GE(base_number, 0.0);
            ks_[i] = 2.0 * base_number;
            bs_[i] = -Sqr(base_number);
        }
    }

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        XCHECK_LT(ref_index_, horizon);
        DividedG res(1);
        res.SetSubName(0, Cost<PROB>::name());
        StateType x_diff = PROB::GetStateAtStep(xs, ref_index_) - ref_state_;
        x_diff[PROB::kStateThetaIndex] =
            NormalizeAngle(x_diff[PROB::kStateThetaIndex]);
        for (int i = 0; i < PROB::kStateSize; ++i) {
            const double diff = x_diff[i];
            const double base_number = base_numbers_[i];
            const double k = ks_[i];
            const double b = bs_[i];
            if (std::abs(diff) < base_number) {
                res.AddSubG(0, Sqr(x_diff[i]) * weights_[i]);
            } else if (diff > 0.0) {
                res.AddSubG(0, ((k * diff) + b) * weights_[i]);
            } else {
                res.AddSubG(0, ((-k * diff) + b) * weights_[i]);
            }
        }
        res.Multi(0.5 * Cost<PROB>::scale());
        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        if (k != ref_index_) {
            return 0.0;
        }
        StateType x_diff = x - ref_state_;
        x_diff[PROB::kStateThetaIndex] =
            NormalizeAngle(x_diff[PROB::kStateThetaIndex]);
        double g = 0.0;
        for (int i = 0; i < PROB::kStateSize; ++i) {
            const double diff = x_diff[i];
            const double base_number = base_numbers_[i];
            const double k = ks_[i];
            const double b = bs_[i];
            if (std::abs(diff) < base_number) {
                g += Sqr(x_diff[i]) * weights_[i];
            } else if (diff > 0.0) {
                g += ((k * diff) + b) * weights_[i];
            } else {
                g += ((-k * diff) + b) * weights_[i];
            }
        }
        g *= 0.5 * Cost<PROB>::scale();

        return g;
    }

    void AddDGDx(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDxType *dgdx) const override {
        if (k != ref_index_) {
            return;
        }
        StateType x_diff = x - ref_state_;
        x_diff[PROB::kStateThetaIndex] =
            NormalizeAngle(x_diff[PROB::kStateThetaIndex]);
        for (int i = 0; i < PROB::kStateSize; ++i) {
            const double diff = x_diff[i];
            const double base_number = base_numbers_[i];
            const double k = ks_[i];
            if (std::abs(diff) < base_number) {
                (*dgdx)[i] += Cost<PROB>::scale() * x_diff[i] * weights_[i];
            } else if (diff > 0.0) {
                (*dgdx)[i] += 0.5 * Cost<PROB>::scale() * k * weights_[i];
            } else {
                (*dgdx)[i] -= 0.5 * Cost<PROB>::scale() * k * weights_[i];
            }
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
        if (k != ref_index_) {
            return;
        }
        StateType x_diff = x - ref_state_;
        x_diff[PROB::kStateThetaIndex] =
            NormalizeAngle(x_diff[PROB::kStateThetaIndex]);
        for (int i = 0; i < PROB::kStateSize; ++i) {
            const double diff = x_diff[i];
            const double base_number = base_numbers_[i];
            if (std::abs(diff) < base_number) {
                (*ddgdxdx)(i, i) += Cost<PROB>::scale() * weights_[i];
            } else {
            }
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
    StateType ref_state_;
    int ref_index_;
    std::vector<double> weights_;
    std::vector<double> base_numbers_;
    std::vector<double> ks_;
    std::vector<double> bs_;
};

}  // namespace planning
}  // namespace pnc_x
