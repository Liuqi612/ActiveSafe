
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <absl/status/statusor.h>
#include <absl/strings/str_cat.h>

#include "math/frenet_common.h"
#include "math/frenet_frame.h"
#include "math/util.h"
#include "math/vec.h"
#include "optimization/problem/center_line_query_helper.h"
#include "optimization/problem/cost.h"
#include "optimization/problem/mixed_fourth_order_bicycle.h"
#include "common/log.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class EndHeadingCost : public Cost<PROB> {
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

    static constexpr double kNormalizedScale = 5.0;
    EndHeadingCost(int horizon,
                   std::vector<double> ref_thetas,
                   const std::vector<Vec2d> &ref_points,
                   const CenterLineQueryHelper<PROB> *center_line_helper,
                   std::vector<double> gains,
                   std::string local_name = absl::StrCat(PROB::kProblemPrefix,
                                                   "EndHeadingCost"),
                   double local_scale = 1.0,
                   CostType local_cost_type = Cost<PROB>::CostType::MUST_HAVE)
        : Cost<PROB>(std::move(local_name), local_scale * kNormalizedScale, local_cost_type),
          horizon_(horizon),
          ref_thetas_(std::move(ref_thetas)),
          center_line_helper_(center_line_helper),
          ref_gains_(std::move(gains)),
          ref_thetas_size_(static_cast<int>(ref_thetas_.size())) {
        if (center_line_helper_ == nullptr) {
            XCHECK_GT(ref_points.size(), 1);
            XCHECK_LT(ref_thetas_.size(), ref_points.size());
            XCHECK_LT(ref_gains_.size(), ref_points.size());
            auto frame_or = BuildBVHFrenetFrame(ref_points, false);
            XCHECK(frame_or.ok());
            ref_path_ = std::move(frame_or).value();

            XCHECK_EQ(ref_points.size(), ref_path_->points().size());
        } else {
            XCHECK_LT(ref_thetas_.size(), center_line_helper_->points().size());
            XCHECK_LT(ref_gains_.size(), center_line_helper_->points().size());
        }

        XCHECK_GT(horizon_, 0);
        deviations_.resize(horizon_);
        factors_.resize(horizon_);
        gains_.resize(horizon_);
    }

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        XCHECK_EQ(horizon, horizon_);
        DividedG res(1);
        for (int k = 0; (k < horizon_) && (k < effective_index_); ++k) {
            res.AddSubG(0, gains_[k] * Sqr(deviations_[k]));
        }
        res.Multi(0.5 * Cost<PROB>::scale());
        res.SetSubName(0, Cost<PROB>::name());
        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        if (k >= effective_index_) { return 0.0; }
        return 0.5 * gains_[k] * Cost<PROB>::scale() * Sqr(deviations_[k]);
    }

    void AddDGDx(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDxType *dgdx) const override {
        if (k >= effective_index_) { return; }
        const double gain = gains_[k] * Cost<PROB>::scale();
        (*dgdx)(PROB::kStateThetaIndex) += gain * deviations_[k];
        (*dgdx).template segment<2>(PROB::kStateXIndex) +=
            gain * deviations_[k] * factors_[k];
    }
    void AddDGDu(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDuType *dgdu) const override {}

    void AddDDGDxDx(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDxDxType *ddgdxdx) const override {
        if (k >= effective_index_) { return; }
        const double gain = gains_[k] * Cost<PROB>::scale();
        (*ddgdxdx)(PROB::kStateThetaIndex, PROB::kStateThetaIndex) += gain;
        const auto &factor_k = factors_[k];
        const Vec2d ddgdthetadxy = gain * factor_k;
        const Vec2d ddgdxydxy =
            gain * Vec2d(Sqr(factor_k.x()), Sqr(factor_k.y()));
        const double ddgdxdy = gain * factor_k.x() * factor_k.y();
        (*ddgdxdx)(PROB::kStateThetaIndex, PROB::kStateXIndex) +=
            ddgdthetadxy[0];
        (*ddgdxdx)(PROB::kStateThetaIndex, PROB::kStateYIndex) +=
            ddgdthetadxy[1];
        (*ddgdxdx)(PROB::kStateXIndex, PROB::kStateThetaIndex) +=
            ddgdthetadxy[0];
        (*ddgdxdx)(PROB::kStateYIndex, PROB::kStateThetaIndex) +=
            ddgdthetadxy[1];
        (*ddgdxdx)(PROB::kStateXIndex, PROB::kStateXIndex) += ddgdxydxy[0];
        (*ddgdxdx)(PROB::kStateYIndex, PROB::kStateYIndex) += ddgdxydxy[1];
        (*ddgdxdx)(PROB::kStateXIndex, PROB::kStateYIndex) += ddgdxdy;
        (*ddgdxdx)(PROB::kStateYIndex, PROB::kStateXIndex) += ddgdxdy;
    }
    void AddDDGDuDx(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDuDxType *ddgdudx) const override {}
    void AddDDGDuDu(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDuDuType *ddgdudu) const override {}

    void Update(const StatesType &xs,
                const ControlsType &us,
                int horizon) override {
        XCHECK_EQ(horizon, horizon_);
        effective_index_ = horizon_;
        constexpr double kEps = 1e-7;
        if (center_line_helper_ == nullptr) {
            const std::vector<double> &s_knot = ref_path_->s_knots();
            for (int k = 0; k < horizon_; ++k) {
                const Vec2d pos =
                    PROB::StateGetPos(PROB::GetStateAtStep(xs, k));
                FrenetCoordinate sl;
                Vec2d normal;
                std::pair<int, int> raw_index_pair;
                double alpha = 0.0;
                ref_path_->XYToSL(pos, &sl, &normal, &raw_index_pair, &alpha);
                if (raw_index_pair.second >= ref_thetas_size_) {
                    effective_index_ = k;
                    break;
                }
                int current_index = raw_index_pair.first;
                int next_index = boost::algorithm::clamp(
                    raw_index_pair.second, 0,
                    static_cast<int>(ref_thetas_.size() - 1));
                const auto curent_ref_theta = ref_thetas_[current_index];
                const auto next_ref_theta = ref_thetas_[next_index];
                const double ref_theta =
                    LerpAngle(curent_ref_theta, next_ref_theta, alpha);
                const double arc_length =
                    s_knot[next_index] - s_knot[current_index];
                if (arc_length < kEps) {
                    factors_[k] = Vec2d(0.0, 0.0);
                } else {
                    factors_[k] =
                        NormalizeAngle(next_ref_theta - curent_ref_theta) *
                        normal.Perp() / arc_length;
                }
                deviations_[k] = NormalizeAngle(
                    PROB::StateGetTheta(PROB::GetStateAtStep(xs, k)) -
                    ref_theta);
                const double gain_factor1 = (k == (horizon_ - 1)) ? kEndStateGain : kPathGain;
                gains_[k] = ref_gains_[current_index] * gain_factor1;
            }
        } else {
            const auto &rac_index_pairs = center_line_helper_->index_pairs();
            const auto &alphas = center_line_helper_->alphas();
            const std::vector<double> &s_knot = center_line_helper_->s_knots();
            const auto &normals = center_line_helper_->normals();
            for (int k = 0; k < horizon_; ++k) {
                if (rac_index_pairs[k].second >= ref_thetas_size_) {
                    effective_index_ = k;
                    break;
                }
                const int current_index = rac_index_pairs[k].first;
                int next_index = boost::algorithm::clamp(
                    rac_index_pairs[k].second, 0,
                    static_cast<int>(ref_thetas_.size() - 1));
                const auto curent_ref_theta = ref_thetas_[current_index];
                const auto next_ref_theta = ref_thetas_[next_index];
                const double ref_theta =
                    LerpAngle(curent_ref_theta, next_ref_theta, alphas[k]);
                const double arc_length =
                    s_knot[next_index] - s_knot[current_index];
                if (arc_length < kEps) {
                    factors_[k] = Vec2d(0.0, 0.0);
                } else {
                    factors_[k] =
                        NormalizeAngle(next_ref_theta - curent_ref_theta) *
                        normals[k].Perp() / arc_length;
                }
                deviations_[k] = NormalizeAngle(
                    PROB::StateGetTheta(PROB::GetStateAtStep(xs, k)) -
                    ref_theta);
                const double gain_factor2 = (k == (horizon_ - 1)) ? kEndStateGain : kPathGain;
                gains_[k] = ref_gains_[current_index] * gain_factor2;
            }
        }
    }

 protected:
    static constexpr double kPathGain = 2.0;
    static constexpr double kEndStateGain = 10.0;

 private:
    int horizon_ = 0;
    std::vector<double> ref_thetas_;
    std::unique_ptr<FrenetFrame> ref_path_;
    const CenterLineQueryHelper<PROB> *center_line_helper_;
    std::vector<double> ref_gains_;
    int ref_thetas_size_;

    std::vector<double> deviations_;
    std::vector<Vec2d> factors_;
    std::vector<double> gains_;
    int effective_index_ = 0;
};

}  // namespace planning
}  // namespace pnc_x
