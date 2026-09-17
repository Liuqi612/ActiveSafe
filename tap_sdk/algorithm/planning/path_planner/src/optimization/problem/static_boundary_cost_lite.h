
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
#include "optimization/problem/cost.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class StaticBoundaryCostLite : public Cost<PROB> {
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

    static constexpr double kNormalizedScale = 10.0;
    StaticBoundaryCostLite(int horizon,
                           std::vector<Vec2d> station_points,
                           std::vector<double> l_min,
                           std::vector<double> l_max,
                           double rac_circle_radius,
                           std::string name_in = absl::StrCat(
                               PROB::kProblemPrefix, "StaticBoundaryCostLite"),
                           double scale_in = 1.0)
        : Cost<PROB>(std::move(name_in), scale_in * kNormalizedScale),
          horizon_(horizon),
          station_points_(std::move(station_points)),
          l_min_(std::move(l_min)),
          l_max_(std::move(l_max)),
          rac_circle_radius_(rac_circle_radius) {
        const int n = station_points_.size();
        XCHECK_GT(n, 1);
        XCHECK_EQ(n, l_min_.size());
        XCHECK_EQ(n, l_max_.size());

        for (int i = 0; i < n; ++i) {
            XCHECK_GE(l_max_[i], l_min_[i]);
        }

        auto frame_or = BuildBVHFrenetFrame(station_points_, true);
        XCHECK(frame_or.ok());
        path_frame_ = std::move(frame_or).value();
        result_cache_.resize(horizon_, OneStepResult{});
        rac_sls_.resize(horizon_, FrenetCoordinate{0.0, 0.0});
        norms_.resize(horizon_, Vec2d(0.0, 0.0));
        index_pairs_.resize(horizon_, std::pair<int, int>{0, 0});
        alphas_.resize(horizon_, 0.0);
    }

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        XCHECK_EQ(horizon, horizon_);
        DividedG res(1);
        res.SetSubName(0, Cost<PROB>::name());
        for (int k = 0; k < horizon_; ++k) {
            res.AddSubG(0,
                        result_cache_[k].g_without_scale * Cost<PROB>::scale());
        }

        return res;
    }

    DividedG EvaluateGWithDebugInfo(int k,
                                    const StateType &x,
                                    const ControlType &u,
                                    bool using_scale) const override {
        const double local_scale = using_scale ? Cost<PROB>::scale() : 1.0;
        DividedG res(1);

        res.SetSubName(0, Cost<PROB>::name());
        res.AddSubG(0, result_cache_[k].g_without_scale * local_scale);
        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        return result_cache_[k].g_without_scale * Cost<PROB>::scale();
    }

    void AddDGDx(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDxType *dgdx) const override {
        (*dgdx).template segment<2>(PROB::kStateXIndex) +=
            result_cache_[k].jaccobian_over_xy;
    }

    void AddDGDu(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDuType *dgdu) const override {}

    void AddDDGDxDx(int k,
                    const StateType &x,
                    const ControlType &u,
                    DDGDxDxType *ddgdxdx) const override {
        (*ddgdxdx).template block<2, 2>(PROB::kStateXIndex,
                                        PROB::kStateXIndex) +=
            result_cache_[k].hessian_over_xy;
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
        XCHECK_NOTNULL(path_frame_);
        XCHECK_EQ(horizon_, horizon);

        for (int k = 0; k < horizon_; ++k) {
            const Vec2d rac = PROB::StateGetPos(PROB::GetStateAtStep(xs, k));

            FrenetCoordinate &rac_sl = rac_sls_[k];
            Vec2d &norm = norms_[k];
            std::pair<int, int> &index_pair = index_pairs_[k];
            double &alpha = alphas_[k];
            path_frame_->XYToSL(rac, &rac_sl, &norm, &index_pair, &alpha);

            XCHECK_LT(index_pair.first, station_points_.size());
            XCHECK_LT(index_pair.second, station_points_.size());
            const double l_min_0 = l_min_[index_pair.first];
            const double l_min_1 = l_min_[index_pair.second];
            const double l_max_0 = l_max_[index_pair.first];
            const double l_max_1 = l_max_[index_pair.second];

            const double l_min = LerpWithClamp(l_min_0, l_min_1, alpha);
            const double l_max = LerpWithClamp(l_max_0, l_max_1, alpha);
            const double l_rac = rac_sl.l;

            OneStepResult &res = result_cache_[k];
            res.g_without_scale = 0.0;

            const double left_invasion = l_rac + rac_circle_radius_ - l_max;
            if (left_invasion > 0.0) {
                res.g_without_scale += Sqr(left_invasion) * 0.5;
            }
            const double right_invasion = l_min - l_rac + rac_circle_radius_;
            if (right_invasion > 0.0) {
                res.g_without_scale += Sqr(right_invasion) * 0.5;
            }
        }
    }

    void UpdateDerivatives(const StatesType &xs,
                           const ControlsType &us,
                           int horizon) override {
        XCHECK_NOTNULL(path_frame_);
        XCHECK_EQ(horizon_, horizon);

        for (int k = 0; k < horizon_; ++k) {
            FrenetCoordinate &rac_sl = rac_sls_[k];
            Vec2d &norm = norms_[k];
            std::pair<int, int> &index_pair = index_pairs_[k];
            double &alpha = alphas_[k];

            XCHECK_LT(index_pair.first, station_points_.size());
            XCHECK_LT(index_pair.second, station_points_.size());
            const double l_min_0 = l_min_[index_pair.first];
            const double l_min_1 = l_min_[index_pair.second];
            const double l_max_0 = l_max_[index_pair.first];
            const double l_max_1 = l_max_[index_pair.second];

            const double l_min = LerpWithClamp(l_min_0, l_min_1, alpha);
            const double l_max = LerpWithClamp(l_max_0, l_max_1, alpha);
            const double l_rac = rac_sl.l;
            const Vec2d segment = station_points_[index_pair.second] -
                                  station_points_[index_pair.first];

            OneStepResult &res = result_cache_[k];
            res.hessian_over_xy.setZero();
            res.jaccobian_over_xy.setZero();

            const double left_invasion = l_rac + rac_circle_radius_ - l_max;
            if (left_invasion > 0.0) {
                Vec2d push_direction;
                if ((alpha > 1.0) || (alpha < 0.0)) {
                    push_direction = -norm;
                } else {
                    push_direction =
                        (l_max_1 - l_max_0) * segment / segment.squaredNorm() -
                        norm;
                }
                res.jaccobian_over_xy += -push_direction.transpose() *
                                         Cost<PROB>::scale() * left_invasion;
                res.hessian_over_xy += push_direction *
                                       push_direction.transpose() *
                                       Cost<PROB>::scale();
            }
            const double right_invasion = l_min - l_rac + rac_circle_radius_;
            if (right_invasion > 0.0) {
                Vec2d push_direction;
                if ((alpha > 1.0) || (alpha < 0.0)) {
                    push_direction = norm;
                } else {
                    push_direction =
                        -(l_min_1 - l_min_0) * segment / segment.squaredNorm() +
                        norm;
                }
                res.jaccobian_over_xy += -push_direction.transpose() *
                                         Cost<PROB>::scale() * right_invasion;
                res.hessian_over_xy += push_direction *
                                       push_direction.transpose() *
                                       Cost<PROB>::scale();
            }
        }
    }

 private:
    static double LerpWithClamp(double v0, double v1, double ratio) {
        if (ratio > 1.0) {
            return v1;
        }
        if (ratio < 0.0) {
            return v0;
        }
        return Lerp(v0, v1, ratio);
    }

    struct OneStepResult {
        double g_without_scale = 0.0;
        Eigen::Matrix2d hessian_over_xy;
        Eigen::Vector2d jaccobian_over_xy;

        void SetZero() {
            g_without_scale = 0.0;
            hessian_over_xy.setZero();
            jaccobian_over_xy.setZero();
        }
    };

    int horizon_ = 0;
    std::vector<Vec2d> station_points_;
    std::vector<double> l_min_;
    std::vector<double> l_max_;
    double rac_circle_radius_ = 0.0;

    std::unique_ptr<FrenetFrame> path_frame_;

    std::vector<OneStepResult> result_cache_;
    std::vector<FrenetCoordinate> rac_sls_;
    std::vector<Vec2d> norms_;
    std::vector<std::pair<int, int>> index_pairs_;
    std::vector<double> alphas_;
};

}  // namespace planning
}  // namespace pnc_x
