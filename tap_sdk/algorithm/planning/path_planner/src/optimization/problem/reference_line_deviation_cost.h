

#ifndef PNC_PLANNER_OPTIMIZATION_PROBLEM_REFERENCE_LINE_DEVIATION_COST_H_
#define PNC_PLANNER_OPTIMIZATION_PROBLEM_REFERENCE_LINE_DEVIATION_COST_H_

#include <algorithm>
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
class ReferenceLineDeviationCost : public Cost<PROB> {
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
    ReferenceLineDeviationCost(
        int horizon,
        double path_gain,
        double end_state_gain,
        std::vector<double> ref_ls,
        const std::vector<Vec2d> &ref_points,
        const CenterLineQueryHelper<PROB> *center_line_helper,
        std::vector<double> gains = {},
        std::string name_in = absl::StrCat(PROB::kProblemPrefix,
                                        "ReferenceLineDeviationCost"),
        double scale_in = 1.0,
        CostType cost_type_in = Cost<PROB>::CostType::MUST_HAVE)
        : Cost<PROB>(std::move(name_in), scale_in * kNormalizedScale, cost_type_in),
          horizon_(horizon),
          ref_ls_(std::move(ref_ls)),
          ref_gains_(std::move(gains)),
          path_gain_(path_gain),
          end_state_gain_(end_state_gain),
          center_line_helper_(center_line_helper),
          ref_ls_size_(0) {
        const std::vector<double>::size_type ref_ls_size = ref_ls_.size();
        ref_ls_size_ = static_cast<int>(ref_ls_size);
        XCHECK_GT(horizon_, 0);
        if (center_line_helper_ == nullptr) {
            XCHECK_GT(ref_points.size(), 1);
            if (ref_gains_.empty()) {
                ref_gains_.resize(ref_points.size() - 1, 1.0);
            }
            XCHECK_LT(ref_gains_.size(), ref_points.size());
            XCHECK_LT(ref_ls_.size(), ref_points.size());
            auto frame_or = BuildBVHFrenetFrame(ref_points, false);
            XCHECK(frame_or.ok());
            ref_path_ = std::move(frame_or).value();

            XCHECK_EQ(ref_points.size(), ref_path_->points().size());
        } else {
            XCHECK_LT(ref_ls_.size(), center_line_helper_->points().size());
            XCHECK_LT(ref_gains_.size(), center_line_helper_->points().size());
        }

        ref_normals_.resize(horizon_);
        deviations_.resize(horizon_);
        gains_.resize(horizon_);
    }

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        DividedG res(1);
        XCHECK_EQ(horizon, horizon_);
        for (int k = 0; (k < horizon_) && (k < effective_index_); ++k) {
            res.AddSubG(0, gains_[k] * Sqr(deviations_[k]));
        }
        res.SetSubName(0, Cost<PROB>::name());
        res.Multi(0.5 * Cost<PROB>::scale());
        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        if (k >= effective_index_) { return 0.0; }
        return 0.5 * Cost<PROB>::scale() * gains_[k] * Sqr(deviations_[k]);
    }

    DividedG EvaluateGWithDebugInfo(int k,
                                    const StateType &x,
                                    const ControlType &u,
                                    bool using_scale) const override {
        DividedG res(1);
        res.SetSubName(0, Cost<PROB>::name());
        res.AddSubG(0, EvaluateG(k, x, u));
        if (k >= effective_index_) { return res; }
        if (!using_scale) {
            if (k != (horizon_ - 1)) {
                if (path_gain_ != 0.0) {
                    res.Multi(1.0 / path_gain_);
                }
            }
        }
        return res;
    }

    void AddDGDx(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDxType *dgdx) const override {
        if (k >= effective_index_) { return; }
        (*dgdx).template segment<2>(PROB::kStateXIndex) +=
            Cost<PROB>::scale() * gains_[k] * deviations_[k] *
            ref_normals_[k].transpose();
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
        (*ddgdxdx).template block<2, 2>(PROB::kStateXIndex,
                                        PROB::kStateXIndex) +=
            Cost<PROB>::scale() * gains_[k] * ref_normals_[k] *
            ref_normals_[k].transpose();
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
        if (center_line_helper_ == nullptr) {
            for (int k = 0; k < horizon_; ++k) {
                const Vec2d pos =
                    PROB::StateGetPos(PROB::GetStateAtStep(xs, k));
                FrenetCoordinate sl;
                Vec2d normal;
                int index;
                double alpha = 0.0;
                ref_path_->XYToSL(pos, &sl, &normal, &index, &alpha);
                if (index >= ref_ls_size_) {
                    effective_index_ = k;
                    break;
                }
                ref_normals_[k] = normal;
                deviations_[k] = sl.l - ref_ls_[index];
                const double gain_factor1 = (k == (horizon_ - 1)) ? end_state_gain_ : path_gain_;
                gains_[k] = ref_gains_[index] * gain_factor1;
            }
        } else {
            const auto &rac_indices = center_line_helper_->indices();
            const auto &rac_s_l_list = center_line_helper_->s_l_list();
            const auto &rac_normals = center_line_helper_->normals();
            for (int k = 0; k < horizon_; ++k) {
                const int index = rac_indices[k];
                if (index >= ref_ls_size_) {
                    effective_index_ = k;
                    break;
                }
                deviations_[k] = rac_s_l_list[k].l - ref_ls_[index];
                ref_normals_[k] = rac_normals[k];
                const double gain_factor2 = (k == (horizon_ - 1)) ? end_state_gain_ : path_gain_;
                gains_[k] = ref_gains_[index] * gain_factor2;
            }
        }
    }

 private:
    int horizon_ = 0;
    std::vector<double> ref_ls_;
    std::vector<double> ref_gains_;
    double path_gain_ = 0.0;
    double end_state_gain_ = 0.0;
    std::unique_ptr<FrenetFrame> ref_path_;
    const CenterLineQueryHelper<PROB> *center_line_helper_;
    int ref_ls_size_ = 0;

    std::vector<Vec2d> ref_normals_;
    std::vector<double> deviations_;
    std::vector<double> gains_;
    int effective_index_ = 0;
};

}  // namespace planning
}  // namespace pnc_x

#endif
