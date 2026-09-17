
#pragma once

#include <absl/strings/str_cat.h>
#include <glog/logging.h>

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "common/log.h"
#include "math/geometry/segment2d.h"
#include "math/piecewise_linear_function.h"
#include "math/util.h"
#include "math/vec.h"
#include "optimization/problem/center_line_query_helper.h"
#include "optimization/problem/cost.h"
#include "plan/planner_defs.h"
#include "util/occ_ddp_csv_debug_writer.h"
#include "util/min_segment_distance_problem.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class MsdStaticBoundaryCostV2 : public Cost<PROB> {
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

    using PenetrationJacobianType = Eigen::Matrix<double, 1, PROB::kStateSize>;
    using PenetrationHessianType =
        Eigen::Matrix<double, PROB::kStateSize, PROB::kStateSize>;

    using GradArrowInfo = std::tuple<double, /*penetration*/
                                     double, /*buffer*/
                                     Vec2d,  /*foot_point*/
                                     Vec2d /*direction*/>;

    struct Layer {
        double gain_of_weight = 1.0;
        PiecewiseLinearFunction<double> buffer_at_speed;
    };

    static constexpr double kNormalizedScale = 10.0;

    MsdStaticBoundaryCostV2(
        int horizon,
        int decay_time,
        std::vector<double> decay_scale,
        MsdProblemWithBuffer curb_msd,
        const CenterLineQueryHelper<PROB> *center_line_helper,
        OccDdpCsvFrameContext csv_ctx,

        std::vector<std::string> sub_names,
        std::vector<Layer> sub_layers,

        std::vector<Vec2d> circle_center_offsets,
        std::vector<double> circle_radiuses,

        bool using_hessian_approximate,
        double max_abs_hard_penetration,
        double max_abs_soft_penetration,
        std::string name = absl::StrCat(PROB::kProblemPrefix,
                                        "MsdStaticBoundaryCostV2"),
        double scale = 1.0,
        CostType cost_type = Cost<PROB>::CostType::UNKNOWN)
        : Cost<PROB>(std::move(name), scale * kNormalizedScale, cost_type),
          horizon_(horizon),
          decay_time_(decay_time),
          decay_scale_(std::move(decay_scale)),
          curb_msd_(std::move(curb_msd)),
          center_line_helper_(center_line_helper),
          csv_ctx_(csv_ctx),
          sub_names_(std::move(sub_names)),
          sub_layers_(std::move(sub_layers)),
          circle_center_offsets_(std::move(circle_center_offsets)),
          circle_radiuses_(std::move(circle_radiuses)),
          using_hessian_approximate_(using_hessian_approximate),
          max_abs_hard_penetration_(max_abs_hard_penetration),
          max_abs_soft_penetration_(max_abs_soft_penetration) {
        XCHECK_GT(horizon_, 0);

        const int num_layers = static_cast<int>(sub_layers_.size());
        XCHECK_GT(num_layers, 0);
        XCHECK_EQ(num_layers, sub_names_.size());

        const int num_circles = static_cast<int>(circle_center_offsets_.size());
        XCHECK_GT(num_circles, 0);
        XCHECK_EQ(num_circles, circle_radiuses_.size());

        workspaces_.resize(horizon_);
        for (int i = 0; i < horizon_; ++i) {
            workspaces_[i].circles.resize(num_circles);
            workspaces_[i].circle_centers.resize(num_circles);
            workspaces_[i].nearest_segments.resize(num_circles);
            workspaces_[i].sub_layer_buffers.resize(num_layers);
            workspaces_[i].sub_layer_dbuffer_dv.resize(num_layers);
        }
        active_cost_steps_.reserve(horizon_);
        batch_circle_centers_.reserve(horizon_ * num_circles);
        batch_nearest_segments_.reserve(horizon_ * num_circles);

        cost_result_.resize(horizon_);
        for (int i = 0; i < horizon_; ++i) {
            cost_result_[i].cost_at_layer.resize(num_layers);
        }
        gradient_result_.resize(horizon_);

        inner_max_penetration_and_buffer_idx.assign(
            horizon_, std::make_tuple(std::numeric_limits<double>::infinity(),
                                      std::numeric_limits<double>::infinity(),
                                      Vec2d(0.0, 0.0), Vec2d(0.0, 0.0)));

        outer_max_penetration_and_buffer_idx.assign(
            horizon_, std::make_tuple(std::numeric_limits<double>::infinity(),
                                      std::numeric_limits<double>::infinity(),
                                      Vec2d(0.0, 0.0), Vec2d(0.0, 0.0)));
    }

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        XCHECK_EQ(horizon_, horizon);
        XCHECK(cost_updated_);
        DividedG res(static_cast<int>(sub_names_.size()));
        for (int i = 0; i < sub_names_.size(); ++i) {
            res.SetSubName(i, sub_names_[i] + Cost<PROB>::name());
            res.SetIsSoft(i, sub_names_[i] == SoftNameString);
        }
        for (int k = 0; k < horizon_; ++k) {
            for (int i = 0; i < sub_names_.size(); ++i) {
                res.AddSubG(i, cost_result_[k].cost_at_layer[i]);
            }
        }
        return res;
    }

    DividedG EvaluateGWithDebugInfo(int k,
                                    const StateType &x,
                                    const ControlType &u,
                                    bool using_scale) const override {
        XCHECK(cost_updated_);
        XCHECK_LT(k, horizon_);
        XCHECK_GE(k, 0);
        const size_t sub_name_size = sub_names_.size();
        const int num_sub_names = static_cast<int>(sub_name_size);
        DividedG res(num_sub_names);
        for (int i = 0; i < sub_names_.size(); ++i) {
            res.SetSubName(i, sub_names_[i] + Cost<PROB>::name());
        }

        for (int i = 0; i < sub_names_.size(); ++i) {
            if (using_scale) {
                res.AddSubG(i, cost_result_[k].cost_at_layer[i]);
            } else {
                res.AddSubG(i, cost_result_[k].cost_at_layer[i] /
                                   sub_layers_[i].gain_of_weight);
            }
        }

        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        XCHECK(cost_updated_);
        XCHECK_LT(k, horizon_);
        XCHECK_GE(k, 0);
        double g = 0.0;
        for (int i = 0; i < sub_layers_.size(); ++i) {
            g += cost_result_[k].cost_at_layer[i];
        }
        return g;
    }

    void AddDGDx(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDxType *dgdx) const override {
        XCHECK(gradient_updated_);
        XCHECK_LT(k, horizon_);
        XCHECK_GE(k, 0);
        if (!gradient_result_[k].is_trivial) {
            *dgdx += gradient_result_[k].dg_dx;
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
        XCHECK(gradient_updated_);
        XCHECK_LT(k, horizon_);
        XCHECK_GE(k, 0);
        if (!gradient_result_[k].is_trivial) {
            *ddgdxdx += gradient_result_[k].d2g_dx2;
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

    void Update(const StatesType &xs,
                const ControlsType &,
                int horizon) override {
        XCHECK_EQ(horizon_, horizon);
        MoveTo(xs);
        UpdateCost();
        UpdateDerivatives();
    }

    void UpdateDerivatives(const StatesType &xs,
                           const ControlsType &,
                           int horizon) override {
        XCHECK_EQ(horizon_, horizon);
        UpdateDerivatives();
    }

    GradArrowWithCost EvaluateBoundary(int k) const override {
      XCHECK_GE(k, 0);
      XCHECK_LT(k, horizon_);

      const auto &inner = inner_max_penetration_and_buffer_idx[k];
      const auto &outer = outer_max_penetration_and_buffer_idx[k];

      const auto &inner_buffer = std::get<1>(inner);
      const auto &inner_foot = std::get<2>(inner);
      const auto &inner_dir = std::get<3>(inner);

      const auto &outer_buffer = std::get<1>(outer);
      const auto &outer_foot = std::get<2>(outer);
      const auto &outer_dir = std::get<3>(outer);

      // foot_point = foot + dir * buffer
      const double inner_px = inner_foot.x() + (inner_dir.x() * inner_buffer);
      const double inner_py = inner_foot.y() + (inner_dir.y() * inner_buffer);
      const double outer_px = outer_foot.x() + (outer_dir.x() * outer_buffer);
      const double outer_py = outer_foot.y() + (outer_dir.y() * outer_buffer);

      GradArrowWithCost result;

      result.inner_arrow.px = inner_px;
      result.inner_arrow.py = inner_py;
      result.inner_arrow.dx = inner_dir.x();
      result.inner_arrow.dy = inner_dir.y();
      result.inner_arrow.circle_idx = -1;
      result.inner_arrow.step_idx = k;

      result.outer_arrow.px = outer_px;
      result.outer_arrow.py = outer_py;
      result.outer_arrow.dx = outer_dir.x();
      result.outer_arrow.dy = outer_dir.y();
      result.outer_arrow.circle_idx = -1;
      result.outer_arrow.step_idx = k;

      const bool has_inner_boundary =
          std::get<0>(inner) < std::numeric_limits<double>::infinity() &&
          inner_dir.Sqr() > 1e-6;
      const bool has_outer_boundary =
          std::get<0>(outer) < std::numeric_limits<double>::infinity() &&
          outer_dir.Sqr() > 1e-6;
      if (has_inner_boundary) {
          WriteOccDdpCsvArrow(csv_ctx_, "occ_arrow_inner",
                              absl::StrCat("inner_step_", k), inner_px,
                              inner_py, inner_dir.x(), inner_dir.y());
      }
      if (has_outer_boundary) {
          WriteOccDdpCsvArrow(csv_ctx_, "occ_arrow_outer",
                              absl::StrCat("outer_step_", k), outer_px,
                              outer_py, outer_dir.x(), outer_dir.y());
      }
      result.has_boundary = has_inner_boundary || has_outer_boundary;
      return result;

    }

 private:
    struct CircleInfo {
        bool is_trivial = true;
        double msd = 0.0;
        Vec2d circle_center;

        const Segment2d *seg_ptr = nullptr;
    };

    struct OneStepWorkspace {
        Vec2d vehicle_tangent;
        std::vector<CircleInfo> circles;
        std::vector<Vec2d> circle_centers;
        std::vector<const MsdProblemWithBuffer::SegmentType *>
            nearest_segments;
        std::vector<double> sub_layer_buffers;
        std::vector<double> sub_layer_dbuffer_dv;
    };

    struct OneStepGradientResult {
        bool is_trivial = true;
        DGDxType dg_dx;
        DDGDxDxType d2g_dx2;

        void SetZero() {
            is_trivial = true;
            dg_dx.setZero();
            d2g_dx2.setZero();
        }
    };

    struct OneStepCostResult {
        std::vector<double> cost_at_layer;
        void SetZero() {
            for (int i = 0; i < cost_at_layer.size(); ++i) {
                cost_at_layer[i] = 0.0;
            }
        }
    };

    void MoveTo(const StatesType &xs) {
        cost_updated_ = false;
        gradient_updated_ = false;
        xs_ptr_ = &xs;
    }

    void PrepareBatchNearestSegments() {
        batch_circle_centers_.clear();
        for (const int k : active_cost_steps_) {
            const StateType &state = PROB::GetStateAtStep(*xs_ptr_, k);
            OneStepWorkspace &workspace = workspaces_[k];
            const Vec2d pos = PROB::StateGetPos(state);
            workspace.vehicle_tangent =
                Vec2d::FastUnitFromAngleN12(PROB::StateGetTheta(state));
            const Vec2d vehicle_tangent_perp =
                workspace.vehicle_tangent.Perp();
            for (int i = 0; i < circle_center_offsets_.size(); ++i) {
                const Vec2d &offset = circle_center_offsets_[i];
                workspace.circle_centers[i] =
                    pos + (workspace.vehicle_tangent * offset.x()) +
                    (vehicle_tangent_perp * offset.y());
            }
            batch_circle_centers_.insert(batch_circle_centers_.end(),
                                         workspace.circle_centers.begin(),
                                         workspace.circle_centers.end());
        }

        curb_msd_.GetNearestSegmentsWithBuffer(
            batch_circle_centers_, &batch_nearest_segments_,
            &batch_nearest_query_);

        size_t offset = 0;
        for (const int k : active_cost_steps_) {
            OneStepWorkspace &workspace = workspaces_[k];
            std::copy_n(batch_nearest_segments_.begin() + offset,
                        workspace.nearest_segments.size(),
                        workspace.nearest_segments.begin());
            offset += workspace.nearest_segments.size();
        }
    }

    void UpdateCost() {
        if (!XCHECK_NOTNULL(xs_ptr_)) {
            return;
        }
        if (cost_updated_) {
            return;
        }
        const bool is_occ_boundary_cost =
            Cost<PROB>::name().find("occ_boundary") != std::string::npos;
        active_cost_steps_.clear();
        if (center_line_helper_ == nullptr) {
            for (int k = 0; k < horizon_; ++k) {
                active_cost_steps_.push_back(k);
            }
            PrepareBatchNearestSegments();
            for (const int k : active_cost_steps_) {
                const StateType &state = PROB::GetStateAtStep(*xs_ptr_, k);
                CalculateCost(state, k, &cost_result_[k], &workspaces_[k]);
            }
            if (IsOccDebugEnabled() && is_occ_boundary_cost &&
                update_cost_debug_print_count_ < 20) {
                OccDebugPrintUpdateCostNoHelper(Cost<PROB>::name(), horizon_);
                ++update_cost_debug_print_count_;
            }
        } else {
            const int last_real_point_index =
                center_line_helper_->last_real_point_index();
            const auto &indices = center_line_helper_->indices();
            const bool enable_station_gate = last_real_point_index >= 0;
            int calc_steps = 0;
            int gated_steps = 0;
            int first_calc_step = -1;
            int first_gated_step = -1;
            for (int k = 0; k < horizon_; ++k) {
                if (enable_station_gate && indices[k] > last_real_point_index) {
                    cost_result_[k].SetZero();
                    ++gated_steps;
                    if (first_gated_step < 0) {
                        first_gated_step = k;
                    }
                } else {
                    active_cost_steps_.push_back(k);
                    ++calc_steps;
                    if (first_calc_step < 0) {
                        first_calc_step = k;
                    }
                }
            }
            PrepareBatchNearestSegments();
            for (const int k : active_cost_steps_) {
                const StateType &state = PROB::GetStateAtStep(*xs_ptr_, k);
                CalculateCost(state, k, &cost_result_[k], &workspaces_[k]);
            }
            if (IsOccDebugEnabled() && is_occ_boundary_cost &&
                update_cost_debug_print_count_ < 20) {
                OccDebugPrintUpdateCostGate(
                    {Cost<PROB>::name(),
                     horizon_,
                     last_real_point_index,
                     enable_station_gate,
                     &indices,
                     calc_steps,
                     gated_steps,
                     first_calc_step,
                     first_gated_step});
                ++update_cost_debug_print_count_;
            }
        }
        cost_updated_ = true;
    }

    void UpdateDerivatives() {
        if (!XCHECK_NOTNULL(xs_ptr_)) {
            return;
        }
        if (gradient_updated_) {
            return;
        }
        XCHECK(cost_updated_);
        if (center_line_helper_ == nullptr) {
            for (int k = 0; k < horizon_; ++k) {
                const StateType &state = PROB::GetStateAtStep(*xs_ptr_, k);
                CalculateGradient(state, k, &gradient_result_[k],
                                  &workspaces_[k]);
            }
        } else {
            const int last_real_point_index =
                center_line_helper_->last_real_point_index();
            const auto &indices = center_line_helper_->indices();
            const bool enable_station_gate = last_real_point_index >= 0;

            for (int k = 0; k < horizon_; ++k) {
                if (enable_station_gate && indices[k] > last_real_point_index) {
                    gradient_result_[k].SetZero();
                } else {
                    const StateType &state = PROB::GetStateAtStep(*xs_ptr_, k);
                    CalculateGradient(state, k, &gradient_result_[k],
                                      &workspaces_[k]);
                }
            }
        }

        gradient_updated_ = true;
    }

    void CalculateCost(const StateType &state,
                       const int k,
                       OneStepCostResult *result,
                       OneStepWorkspace *workspace) {
        if (!XCHECK_NOTNULL(workspace) || !XCHECK_NOTNULL(result) ||
            !XCHECK_EQ(result->cost_at_layer.size(), sub_layers_.size()) ||
            !XCHECK_EQ(workspace->circles.size(),
                       circle_center_offsets_.size()) ||
            !XCHECK_EQ(workspace->circle_centers.size(),
                       circle_center_offsets_.size()) ||
            !XCHECK_EQ(workspace->nearest_segments.size(),
                       circle_center_offsets_.size()) ||
            !XCHECK_EQ(workspace->sub_layer_buffers.size(),
                       sub_layers_.size())) {
            return;
        }

        const double speed = state[PROB::kStateVIndex];

        for (int i = 0; i < sub_layers_.size(); ++i) {
            workspace->sub_layer_buffers[i] =
                sub_layers_[i].buffer_at_speed.Evaluate(speed);
        }

        for (int i = 0; i < sub_layers_.size(); ++i) {
            result->cost_at_layer[i] = 0.0;
        }

        double step_best_inner_pen = std::numeric_limits<double>::infinity();
        double step_best_outer_pen = std::numeric_limits<double>::infinity();
        int best_inner_circle = -1;
        int best_outer_circle = -1;
        double best_inner_buffer = std::numeric_limits<double>::infinity();
        double best_outer_buffer = std::numeric_limits<double>::infinity();
        GradArrowInfo step_best_inner_info =
            std::make_tuple(std::numeric_limits<double>::infinity(),
                            std::numeric_limits<double>::infinity(),
                            Vec2d(0.0, 0.0), Vec2d(0.0, 0.0));
        GradArrowInfo step_best_outer_info =
            std::make_tuple(std::numeric_limits<double>::infinity(),
                            std::numeric_limits<double>::infinity(),
                            Vec2d(0.0, 0.0), Vec2d(0.0, 0.0));

        for (int i = 0; i < circle_center_offsets_.size(); ++i) {
            const Vec2d &circle_center = workspace->circle_centers[i];
            const MsdProblemWithBuffer::SegmentType *seg_with_buffer_ptr =
                workspace->nearest_segments[i];

            double msd = curb_msd_.cutoff_distance();
            if (seg_with_buffer_ptr != nullptr) {
                msd = seg_with_buffer_ptr->segment.DistanceTo(circle_center) -
                      seg_with_buffer_ptr->buffer;
            }

            bool has_cost = false;
            for (int j = 0; j < sub_layers_.size(); ++j) {
                double max_abs_penetration = max_abs_soft_penetration_;
                if ((j < sub_names_.size()) &&
                    (sub_names_[j] == HardNameString)) {
                    max_abs_penetration = max_abs_hard_penetration_;
                }
                const double buffer_j =
                    workspace->sub_layer_buffers[j] + circle_radiuses_[i];
                const double penetration_raw = msd - buffer_j;
                const double penetration =
                    std::max(-max_abs_penetration, penetration_raw);

                // Keep the raw most critical boundary over all vehicle circles
                // for per-step debug/canvas output. The cost itself still uses
                // the clipped penetration below.
                if (seg_with_buffer_ptr != nullptr && (j % 2) == 0) {  // outer
                    if (penetration_raw < step_best_outer_pen) {
                        step_best_outer_pen = penetration_raw;
                        best_outer_circle = i;
                        best_outer_buffer = buffer_j;
                    }
                } else if (seg_with_buffer_ptr != nullptr) {  // inner
                    if (penetration_raw < step_best_inner_pen) {
                        step_best_inner_pen = penetration_raw;
                        best_inner_circle = i;
                        best_inner_buffer = buffer_j;
                    }
                }

                if (penetration < 0.0) {
                    has_cost = true;
                    double scale = decay_scale_[k];
                    result->cost_at_layer[j] +=
                        0.5 * Cost<PROB>::scale() * scale *
                        sub_layers_[j].gain_of_weight * Sqr(penetration);
                }
            }

            CircleInfo &circle = workspace->circles[i];
            circle.circle_center = std::move(circle_center);
            circle.msd = msd;
            circle.seg_ptr = seg_with_buffer_ptr != nullptr
                                 ? &seg_with_buffer_ptr->segment
                                 : nullptr;
            circle.is_trivial = !has_cost;
        }

        // The perpendicular foot/direction is only consumed by the debug
        // arrows returned from EvaluateBoundary().  Compute it lazily for
        // the most critical inner/outer circle instead of once per circle.
        if (best_inner_circle >= 0) {
            const int i = best_inner_circle;
            const auto *seg_with_buffer_ptr = workspace->nearest_segments[i];
            Vec2d foot_point(0.0, 0.0);
            Vec2d dir(0.0, 0.0);
            seg_with_buffer_ptr->segment.GetPerpendicularFootAndDir(
                workspace->circle_centers[i], &foot_point, &dir);
            step_best_inner_info = std::make_tuple(
                step_best_inner_pen, best_inner_buffer, foot_point, dir);
        }
        if (best_outer_circle >= 0) {
            const int i = best_outer_circle;
            const auto *seg_with_buffer_ptr = workspace->nearest_segments[i];
            Vec2d foot_point(0.0, 0.0);
            Vec2d dir(0.0, 0.0);
            seg_with_buffer_ptr->segment.GetPerpendicularFootAndDir(
                workspace->circle_centers[i], &foot_point, &dir);
            step_best_outer_info = std::make_tuple(
                step_best_outer_pen, best_outer_buffer, foot_point, dir);
        }

        inner_max_penetration_and_buffer_idx[k] = step_best_inner_info;
        outer_max_penetration_and_buffer_idx[k] = step_best_outer_info;
    }

    void CalculateGradient(const StateType &state,
                           const int k,
                           OneStepGradientResult *result,
                           OneStepWorkspace *workspace) const {
        if (!XCHECK_NOTNULL(result) || !XCHECK_NOTNULL(workspace) ||
            !XCHECK_EQ(workspace->sub_layer_dbuffer_dv.size(),
                       sub_layers_.size())) {
            return;
        }

        const double speed = state[PROB::kStateVIndex];

        for (int i = 0; i < sub_layers_.size(); ++i) {
            workspace->sub_layer_dbuffer_dv[i] =
                sub_layers_[i].buffer_at_speed.EvaluateSlope(speed);
        }

        result->SetZero();

        for (int i = 0; i < circle_center_offsets_.size(); ++i) {
            const CircleInfo &circle_cache = workspace->circles[i];

            if ((circle_cache.seg_ptr == nullptr) || circle_cache.is_trivial) {
                continue;
            }

            PenetrationHessianType msd_hessian = PenetrationHessianType::Zero();
            PenetrationJacobianType msd_jacobian =
                PenetrationJacobianType::Zero();
            {
                const Vec2d rotated_offset = circle_center_offsets_[i].Rotate(
                    workspace->vehicle_tangent.x(),
                    workspace->vehicle_tangent.y());
                const Vec2d rotated_offset_perp = rotated_offset.Perp();

                const double projection = circle_cache.seg_ptr->ProjectOntoUnit(
                    circle_cache.circle_center);
                const double production = circle_cache.seg_ptr->ProductOntoUnit(
                    circle_cache.circle_center);

                if ((projection >= 0.0) &&
                    (projection <= circle_cache.seg_ptr->length())) {
                    Vec2d force_dir =
                        circle_cache.seg_ptr->unit_direction().Perp();
                    if (production < 0.0) {
                        force_dir = -force_dir;
                    }
                    msd_jacobian.template segment<2>(PROB::kStateXIndex) =
                        force_dir;
                    msd_jacobian(PROB::kStateThetaIndex) =
                        force_dir.dot(rotated_offset_perp);

                    if (!using_hessian_approximate_) {
                        msd_hessian(PROB::kStateThetaIndex,
                                    PROB::kStateThetaIndex) =
                            force_dir.dot(-rotated_offset);
                    }
                } else {
                    const auto &nearest_point_on_seg =
                        (projection < 0.0) ? circle_cache.seg_ptr->start()
                                           : circle_cache.seg_ptr->end();
                    const Vec2d x1 =
                        circle_cache.circle_center - nearest_point_on_seg;

                    const double dist = std::max(x1.Length(), 1e-5);
                    const double dist_inv = 1.0 / dist;
                    const double dist_inv_cube = Cube(dist_inv);
                    msd_jacobian.template segment<2>(PROB::kStateXIndex) =
                        x1 * dist_inv;
                    msd_jacobian(PROB::kStateThetaIndex) =
                        x1.dot(rotated_offset_perp) * dist_inv;

                    if (!using_hessian_approximate_) {
                        msd_hessian(PROB::kStateXIndex, PROB::kStateXIndex) =
                            dist_inv - (Sqr(x1.x()) * dist_inv_cube);
                        msd_hessian(PROB::kStateXIndex, PROB::kStateYIndex) =
                            (-x1.x()) * x1.y() * dist_inv_cube;
                        msd_hessian(PROB::kStateXIndex,
                                    PROB::kStateThetaIndex) =
                            (rotated_offset_perp.x() * dist_inv) -
                            (dist_inv_cube * x1.x() *
                             x1.dot(rotated_offset_perp));

                        msd_hessian(PROB::kStateYIndex, PROB::kStateXIndex) =
                            msd_hessian(PROB::kStateXIndex, PROB::kStateYIndex);
                        msd_hessian(PROB::kStateYIndex, PROB::kStateYIndex) =
                            dist_inv - (Sqr(x1.y()) * dist_inv_cube);
                        msd_hessian(PROB::kStateYIndex,
                                    PROB::kStateThetaIndex) =
                            (rotated_offset_perp.y() * dist_inv) -
                            (dist_inv_cube * x1.y() *
                             x1.dot(rotated_offset_perp));

                        msd_hessian(PROB::kStateThetaIndex,
                                    PROB::kStateXIndex) =
                            msd_hessian(PROB::kStateXIndex,
                                        PROB::kStateThetaIndex);
                        msd_hessian(PROB::kStateThetaIndex,
                                    PROB::kStateYIndex) =
                            msd_hessian(PROB::kStateYIndex,
                                        PROB::kStateThetaIndex);
                        msd_hessian(PROB::kStateThetaIndex,
                                    PROB::kStateThetaIndex) =
                            ((x1.dot(-rotated_offset) +
                              rotated_offset_perp.Sqr()) *
                             dist_inv) -
                            (dist_inv_cube * Sqr(x1.dot(rotated_offset_perp)));
                    }
                }
            }

            for (int j = 0; j < sub_layers_.size(); ++j) {
                double max_abs_penetration = max_abs_soft_penetration_;
                if ((j < sub_names_.size()) &&
                    (sub_names_[j] == HardNameString)) {
                    max_abs_penetration = max_abs_hard_penetration_;
                }
                const double penatration = std::max(
                    -max_abs_penetration, circle_cache.msd -
                                              workspace->sub_layer_buffers[j] -
                                              circle_radiuses_[i]);
                if (penatration < 0.0) {
                    const double old_entry = msd_jacobian(PROB::kStateVIndex);
                    msd_jacobian(PROB::kStateVIndex) -=
                        workspace->sub_layer_dbuffer_dv[j];

                    const PenetrationJacobianType &penetration_jacobian =
                        msd_jacobian;
                    const PenetrationHessianType &penetration_hessian =
                        msd_hessian;

                    if (using_hessian_approximate_) {
                        double scale = decay_scale_[k];
                        result->d2g_dx2 += Cost<PROB>::scale() * scale *
                                           sub_layers_[j].gain_of_weight *
                                           (penetration_jacobian.transpose() *
                                            penetration_jacobian);
                    } else {
                        double scale = decay_scale_[k];
                        result->d2g_dx2 +=
                            Cost<PROB>::scale() * scale *
                            sub_layers_[j].gain_of_weight *
                            ((penatration * penetration_hessian) +
                             (penetration_jacobian.transpose() *
                              penetration_jacobian));
                    }

                    double scale = decay_scale_[k];
                    result->dg_dx += Cost<PROB>::scale() * scale *
                                     sub_layers_[j].gain_of_weight *
                                     penatration * penetration_jacobian;
                    result->is_trivial = false;

                    msd_jacobian(PROB::kStateVIndex) = old_entry;
                }
            }
        }
    }

    int horizon_ = 0;
    int decay_time_ = 0;
    const std::vector<double> decay_scale_;
    MsdProblemWithBuffer curb_msd_;
    const CenterLineQueryHelper<PROB> *center_line_helper_;
    OccDdpCsvFrameContext csv_ctx_;

    std::vector<std::string> sub_names_;
    std::vector<Layer> sub_layers_;

    std::vector<Vec2d> circle_center_offsets_;
    std::vector<double> circle_radiuses_;

    bool using_hessian_approximate_ = false;

    const StatesType *xs_ptr_ = nullptr;
    bool cost_updated_ = false;
    bool gradient_updated_ = false;
    std::vector<OneStepWorkspace> workspaces_;
    std::vector<int> active_cost_steps_;
    std::vector<Vec2d> batch_circle_centers_;
    std::vector<const MsdProblemWithBuffer::SegmentType *>
        batch_nearest_segments_;
    MinSegmentDistanceProblem::BatchQueryWorkspace batch_nearest_query_;

    std::vector<OneStepCostResult> cost_result_;
    std::vector<OneStepGradientResult> gradient_result_;
    double max_abs_hard_penetration_ = 1.0;
    double max_abs_soft_penetration_ = 1.0;
    int update_cost_debug_print_count_ = 0;

    std::vector<GradArrowInfo> inner_max_penetration_and_buffer_idx;
    std::vector<GradArrowInfo> outer_max_penetration_and_buffer_idx;

    static bool IsOccDebugSegment(const std::string &segment_id) {
        return segment_id.rfind("occ_poly:", 0) == 0;
    }
};

}  // namespace planning
}  // namespace pnc_x
