#pragma once

#include <algorithm>
#include <cmath>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include <absl/strings/str_cat.h>
#include <absl/types/span.h>
#include "common/log.h"

#include "math/geometry/segment2d.h"
#include "math/util.h"
#include "math/vec.h"
#include "optimization/problem/center_line_query_helper.h"
#include "optimization/problem/cost.h"
#include "util/min_segment_distance_problem.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class MsdStaticBoundaryCost : public Cost<PROB> {
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

    static constexpr double kNormalizedScale = 10.0;
    MsdStaticBoundaryCost(int horizon,
                          VehicleGeometryParamsProto vehicle_geometry_params,
                          MsdProblemWithBuffer curb_msd,
                          const CenterLineQueryHelper<PROB> *center_line_helper,
                          std::vector<std::string> sub_names,
                          std::vector<double> cascade_buffers,
                          std::vector<double> cascade_gains,
                          std::vector<Vec2d> circle_center_offsets,
                          std::vector<double> circle_radiuses,
                          int effect_index,
                          bool using_hessian_approximate,
                          std::string name = absl::StrCat(
                              PROB::kProblemPrefix, "MsdStaticBoundaryCost"),
                          double scale = 1.0,
                          CostType cost_type = Cost<PROB>::CostType::UNKNOWN)
        : Cost<PROB>(std::move(name), scale * kNormalizedScale, cost_type),
          horizon_(horizon),
          vehicle_geometry_params_(std::move(vehicle_geometry_params)),
          curb_msd_(std::move(curb_msd)),
          center_line_helper_(center_line_helper),
          cascade_buffers_(std::move(cascade_buffers)),
          cascade_gains_(std::move(cascade_gains)),
          circle_center_offsets_(std::move(circle_center_offsets)),
          circle_radiuses_(std::move(circle_radiuses)),
          sub_names_(std::move(sub_names)),
          effect_index_(effect_index),
          using_hessian_approximate_(using_hessian_approximate) {
        const int n = static_cast<int>(cascade_buffers_.size());
        XCHECK_GT(n, 0);
        XCHECK_EQ(n, cascade_gains_.size());
        XCHECK_EQ(n, sub_names_.size());
        XCHECK_LE(effect_index_, horizon_);

        cascade_gains_final.reserve(n);

        double max_radius = 0.0;
        for (int i = 0; i < n; ++i) {
            cascade_gains_final.push_back(cascade_gains_[i] *
                                          Cost<PROB>::scale() * 0.5);
            max_radius = std::max(circle_radiuses_.back(), max_radius);
        }

        penetrations_.resize(effect_index_);
        segments_ptr_.resize(effect_index_);
        penetration_jacobians_.resize(effect_index_);
        penetration_hessians_.resize(effect_index_);
        for (int k = 0; k < horizon_; ++k) {
            penetrations_[k].resize(circle_center_offsets_.size());
            segments_ptr_[k].resize(circle_center_offsets_.size(), nullptr);
            penetration_jacobians_[k].resize(circle_center_offsets_.size(),
                                             PenetrationJacobianType::Zero());
            penetration_hessians_[k].resize(circle_center_offsets_.size(),
                                            PenetrationHessianType::Zero());
            for (int i = 0; i < penetrations_[k].size(); ++i) {
                penetrations_[k][i].resize(
                    n, std::numeric_limits<double>::infinity());
            }
        }

        inner_max_penetration_and_buffer_idx.assign(
            horizon_, std::make_tuple(std::numeric_limits<double>::infinity(),
                                      std::numeric_limits<double>::infinity(),
                                      Vec2d(0.0, 0.0), Vec2d(0.0, 0.0)));

        outer_max_penetration_and_buffer_idx.assign(
            horizon_, std::make_tuple(std::numeric_limits<double>::infinity(),
                                      std::numeric_limits<double>::infinity(),
                                      Vec2d(0.0, 0.0), Vec2d(0.0, 0.0)));

        XCHECK_LE(max_radius, curb_msd_.cutoff_distance());
        XCHECK_EQ(circle_center_offsets_.size(), circle_radiuses_.size());
    }

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        XCHECK_EQ(horizon, horizon_);
        DividedG res(static_cast<int>(sub_names_.size()));
        for (int i = 0; i < sub_names_.size(); ++i) {
            res.SetSubName(i, sub_names_[i] + Cost<PROB>::name());
        }
        for (int k = 0; k < effect_index_; ++k) {
            const auto penetrations_k = absl::MakeConstSpan(penetrations_[k]);
            for (int i = 0; i < penetrations_k.size(); ++i) {
                const auto penetrations_i =
                    absl::MakeConstSpan(penetrations_k[i]);
                for (int j = 0; j < penetrations_i.size(); ++j) {
                    if (penetrations_i[j] < 0.0) {
                        res.AddSubG(j, 0.5 * Cost<PROB>::scale() *
                                           cascade_gains_[j] *
                                           Sqr(penetrations_i[j]));
                    }
                }
            }
        }

        return res;
    }

    DividedG EvaluateGWithDebugInfo(int k,
                                    const StateType &x,
                                    const ControlType &u,
                                    bool using_scale) const override {
        DividedG res(static_cast<int>(sub_names_.size()));
        for (int i = 0; i < sub_names_.size(); ++i) {
            res.SetSubName(i, sub_names_[i] + Cost<PROB>::name());
        }
        if (k >= effect_index_) return res;
        const auto penetrations_k = absl::MakeConstSpan(penetrations_[k]);
        for (int i = 0; i < penetrations_k.size(); ++i) {
            const auto penetrations_i = absl::MakeConstSpan(penetrations_k[i]);
            for (int j = 0; j < penetrations_i.size(); ++j) {
                if (penetrations_i[j] < 0.0) {
                    res.AddSubG(j, 0.5 * Cost<PROB>::scale() *
                                       cascade_gains_[j] *
                                       Sqr(penetrations_i[j]));
                }
            }
        }
        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        XCHECK_GE(k, 0);
        if (k >= effect_index_) return 0.0;
        double g = 0.0;
        const auto penetrations_k = absl::MakeConstSpan(penetrations_[k]);
        for (int i = 0; i < penetrations_k.size(); ++i) {
            const auto penetrations_i = absl::MakeConstSpan(penetrations_k[i]);
            for (int j = 0; j < penetrations_i.size(); ++j) {
                if (penetrations_i[j] < 0.0) {
                    g += 0.5 * Cost<PROB>::scale() * cascade_gains_[j] *
                         Sqr(penetrations_i[j]);
                }
            }
        }
        return g;
    }

    void AddDGDx(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDxType *dgdx) const override {
        XCHECK_GE(k, 0);
        if (k >= effect_index_) return;
        const auto penetrations_k = absl::MakeConstSpan(penetrations_[k]);
        const auto &penetration_jacobians_k = penetration_jacobians_[k];
        for (int i = 0; i < penetrations_k.size(); ++i) {
            const auto penetrations_i = absl::MakeConstSpan(penetrations_k[i]);
            for (int j = 0; j < penetrations_i.size(); ++j) {
                if (penetrations_i[j] < 0.0) {
                    *dgdx += Cost<PROB>::scale() * cascade_gains_[j] *
                             penetrations_i[j] * penetration_jacobians_k[i];
                }
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
        XCHECK_GE(k, 0);
        if (k >= effect_index_) return;
        const auto penetrations_k = absl::MakeConstSpan(penetrations_[k]);
        const auto &penetration_jacobians_k = penetration_jacobians_[k];
        const auto &penetration_hessians_k = penetration_hessians_[k];
        for (int i = 0; i < penetrations_k.size(); ++i) {
            const auto penetrations_i = absl::MakeConstSpan(penetrations_k[i]);
            for (int j = 0; j < penetrations_i.size(); ++j) {
                if (penetrations_i[j] < 0.0) {
                    if (!using_hessian_approximate_) {
                        *ddgdxdx +=
                            Cost<PROB>::scale() * cascade_gains_[j] *
                            ((penetrations_i[j] * penetration_hessians_k[i]) +
                             (penetration_jacobians_k[i].transpose() *
                                 penetration_jacobians_k[i]));
                    } else {
                        *ddgdxdx += Cost<PROB>::scale() * cascade_gains_[j] *
                                    (penetration_jacobians_k[i].transpose() *
                                     penetration_jacobians_k[i]);
                    }
                }
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

    void Update(const StatesType &xs,
                const ControlsType &,
                int horizon) override {
        XCHECK_EQ(horizon, horizon_);
        if (center_line_helper_ == nullptr) {
            for (int k = 0; k < effect_index_; ++k) {
                const StateType &state = PROB::GetStateAtStep(xs, k);
                UpdateOneStep(state, k, true);
            }
        } else {
            const int last_real_point_index =
                center_line_helper_->last_real_point_index();
            const auto &indices = center_line_helper_->indices();
            for (int k = 0; k < effect_index_; ++k) {
                const StateType &state = PROB::GetStateAtStep(xs, k);
                UpdateOneStep(state, k, indices[k] <= last_real_point_index);
            }
        }
    }

    void UpdateDerivatives(const StatesType &xs,
                           const ControlsType &,
                           int horizon) override {
        XCHECK_EQ(horizon, horizon_);
        if (center_line_helper_ == nullptr) {
            for (int k = 0; k < effect_index_; ++k) {
                const StateType &state = PROB::GetStateAtStep(xs, k);
                UpdateOneStepWithDerivative(state, k, true);
            }
        } else {
            const int last_real_point_index =
                center_line_helper_->last_real_point_index();
            const auto &indices = center_line_helper_->indices();
            for (int k = 0; k < effect_index_; ++k) {
                const StateType &state = PROB::GetStateAtStep(xs, k);
                UpdateOneStepWithDerivative(
                    state, k, indices[k] <= last_real_point_index);
            }
        }
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

      result.has_boundary = true;
      return result;
    }


 private:
    void UpdateOneStepWithDerivative(const StateType &state,
                                     int k,
                                     bool update_active) {
        auto &penetration_jacobians_k = penetration_jacobians_[k];
        auto &penetration_hessians_k = penetration_hessians_[k];

        for (int i = 0; i < circle_center_offsets_.size(); ++i) {
            auto &penetration_jacobians_ki = penetration_jacobians_k[i];
            auto &penetration_hessians_ki = penetration_hessians_k[i];

            penetration_jacobians_ki.template segment<3>(PROB::kStateXIndex) =
                Eigen::Matrix<double, 3, 1>::Zero();
            penetration_hessians_ki.template block<3, 3>(PROB::kStateXIndex,
                                                         PROB::kStateXIndex) =
                Eigen::Matrix<double, 3, 3>::Zero();

            if (!update_active) continue;

            const Vec2d &offset = circle_center_offsets_[i];

            const Vec2d av_tangent =
                Vec2d::FastUnitFromAngleN12(PROB::StateGetTheta(state));
            const Vec2d pos = PROB::StateGetPos(state);

            const Vec2d rotated_offset =
                offset.Rotate(av_tangent.x(), av_tangent.y());
            const Vec2d rotated_offset_perp = rotated_offset.Perp();

            const Segment2d *line_pt = segments_ptr_[k][i];
            if (line_pt != nullptr) {
                const double xr = pos.x() + (offset.x() * av_tangent.x()) -
                                  (offset.y() * av_tangent.y());
                const double yr = pos.y() + (offset.x() * av_tangent.y()) +
                                  (offset.y() * av_tangent.x());
                const Vec2d pt = {xr, yr};
                const double projection = line_pt->ProjectOntoUnit(pt);
                if ((projection > 0.0) && (projection < line_pt->length())) {
                    const double signed_dist = line_pt->ProductOntoUnit(pt);
                    const Vec2d force_dir =
                        ((signed_dist < 0.0) ? -line_pt->unit_direction().Perp()
                                              : line_pt->unit_direction().Perp());
                    penetration_jacobians_ki.template segment<2>(
                        PROB::kStateXIndex) = force_dir;
                    penetration_jacobians_ki(PROB::kStateThetaIndex) =
                        force_dir.dot(rotated_offset_perp);
                    penetration_hessians_ki(PROB::kStateThetaIndex,
                                            PROB::kStateThetaIndex) =
                        force_dir.dot(-rotated_offset);
                } else {
                    const auto &pt2 =
                        (projection < 0.0) ? line_pt->start() : line_pt->end();
                    const Vec2d x1 = pt - pt2;
                    const double dist = std::sqrt(x1.Sqr());
                    const double dist_inv = 1.0 / dist;
                    const double dist_inv_cube = Cube(dist_inv);
                    penetration_jacobians_ki.template segment<2>(
                        PROB::kStateXIndex) = x1 * dist_inv;
                    penetration_jacobians_ki(PROB::kStateThetaIndex) =
                        x1.dot(rotated_offset_perp) * dist_inv;
                    penetration_hessians_ki(PROB::kStateXIndex,
                                            PROB::kStateXIndex) =
                        dist_inv - (Sqr(x1.x()) * dist_inv_cube);
                    penetration_hessians_ki(PROB::kStateXIndex,
                                            PROB::kStateYIndex) =
                        -x1.x() * x1.y() * dist_inv_cube;
                    penetration_hessians_ki(PROB::kStateXIndex,
                                            PROB::kStateThetaIndex) =
                        (rotated_offset_perp.x() * dist_inv) -
                        (dist_inv_cube * x1.x() * x1.dot(rotated_offset_perp));

                    penetration_hessians_ki(PROB::kStateYIndex,
                                            PROB::kStateXIndex) =
                        penetration_hessians_ki(PROB::kStateXIndex,
                                                PROB::kStateYIndex);
                    penetration_hessians_ki(PROB::kStateYIndex,
                                            PROB::kStateYIndex) =
                        dist_inv - (Sqr(x1.y()) * dist_inv_cube);
                    penetration_hessians_ki(1, PROB::kStateThetaIndex) =
                        (rotated_offset_perp.y() * dist_inv) -
                        (dist_inv_cube * x1.y() * x1.dot(rotated_offset_perp));

                    penetration_hessians_ki(PROB::kStateThetaIndex,
                                            PROB::kStateXIndex) =
                        penetration_hessians_ki(PROB::kStateXIndex,
                                                PROB::kStateThetaIndex);
                    penetration_hessians_ki(PROB::kStateThetaIndex,
                                            PROB::kStateYIndex) =
                        penetration_hessians_ki(PROB::kStateYIndex,
                                                PROB::kStateThetaIndex);
                    penetration_hessians_ki(PROB::kStateThetaIndex,
                                            PROB::kStateThetaIndex) =
                        ((x1.dot(-rotated_offset) +
                         rotated_offset_perp.dot(rotated_offset_perp)) *
                            dist_inv) -
                        (dist_inv_cube * x1.dot(rotated_offset_perp) *
                            x1.dot(rotated_offset_perp));
                }
            }
        }
    }

    void UpdateOneStep(const StateType &state, int k, bool update_active) {
        const double x = state[PROB::kStateXIndex];
        const double y = state[PROB::kStateYIndex];

        const Vec2d av_tangent =
            Vec2d::FastUnitFromAngleN12(PROB::StateGetTheta(state));
        const Vec2d av_tangent_perp = av_tangent.Perp();

        auto penetrations_k = absl::MakeSpan(penetrations_[k]);
        std::vector<Vec2d> circle_centers(circle_center_offsets_.size());
        for (int i = 0; i < circle_center_offsets_.size(); ++i) {
            const Vec2d &offset = circle_center_offsets_[i];
            circle_centers[i] =
                Vec2d{x, y} + (av_tangent * offset.x()) +
                (av_tangent_perp * offset.y());
        }
        std::vector<const MsdProblemWithBuffer::SegmentType *> nearest_segments;
        curb_msd_.GetNearestSegmentsWithBuffer(circle_centers,
                                               &nearest_segments);
        for (int i = 0; i < circle_center_offsets_.size(); ++i) {
            if (!update_active) {
                for (int j = 0; j < penetrations_k[i].size(); ++j) {
                    penetrations_k[i][j] = 0.0;
                }
                continue;
            }

            const Vec2d &pt = circle_centers[i];
            const MsdProblemWithBuffer::SegmentType *line_pt =
                (i < nearest_segments.size()) ? nearest_segments[i] : nullptr;
            segments_ptr_[k][i] = nullptr;
            double msd = curb_msd_.cutoff_distance();
            Vec2d foot_point(0.0, 0.0);
            Vec2d dir(0.0, 0.0);
            if (line_pt != nullptr) {
                msd = line_pt->segment.DistanceTo(pt) - line_pt->buffer;
                segments_ptr_[k][i] = &line_pt->segment;
                line_pt->segment.GetPerpendicularFootAndDir(
                  pt, &foot_point, &dir);
            }

            // 圈 i 内的“最小 penetration”（inner/outer各一份；无论是否侵入都比较）
            double best_inner_pen = std::numeric_limits<double>::infinity();
            int best_inner_j = -1;
            GradArrowInfo best_inner_info =
                std::make_tuple(std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                Vec2d(0.0, 0.0), Vec2d(0.0, 0.0));

            double best_outer_pen = std::numeric_limits<double>::infinity();
            int best_outer_j = -1;
            GradArrowInfo best_outer_info =
                std::make_tuple(std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                Vec2d(0.0, 0.0), Vec2d(0.0, 0.0));

            for (int j = 0; j < penetrations_k[i].size(); ++j) {
                const double buffer_j = cascade_buffers_[j] + circle_radiuses_[i];
                double penetration = msd - buffer_j;
                penetrations_k[i][j] = penetration;

                if ((j % 2) == 0) { // outer
                  if (penetration < best_outer_pen) {
                    best_outer_pen = penetration;
                    best_outer_j = j;
                    best_outer_info =
                        std::make_tuple(penetration, buffer_j, foot_point, dir);
                  }
                } else { // inner
                  if (penetration < best_inner_pen) {
                    best_inner_pen = penetration;
                    best_inner_j = j;
                    best_inner_info =
                        std::make_tuple(penetration, buffer_j, foot_point, dir);
                  }
                }
            }

            if (best_inner_j >= 0) {
              inner_max_penetration_and_buffer_idx[k] = best_inner_info;
            }
            if (best_outer_j >= 0) {
              outer_max_penetration_and_buffer_idx[k] = best_outer_info;
            }
        }
    }

    int horizon_ = 0;
    VehicleGeometryParamsProto vehicle_geometry_params_;
    MsdProblemWithBuffer curb_msd_;
    const CenterLineQueryHelper<PROB> *center_line_helper_;

    std::vector<double> cascade_buffers_;
    const std::vector<double> cascade_gains_;
    std::vector<Vec2d> circle_center_offsets_;
    std::vector<double> circle_radiuses_;
    std::vector<double> cascade_gains_final;
    std::vector<std::string> sub_names_;

    int effect_index_ = 0;

    bool using_hessian_approximate_ = false;

    std::vector<std::vector<std::vector<double>>> penetrations_;
    std::vector<std::vector<const Segment2d *>> segments_ptr_;
    std::vector<std::vector<PenetrationJacobianType>> penetration_jacobians_;
    std::vector<std::vector<PenetrationHessianType>> penetration_hessians_;

    std::vector<GradArrowInfo> inner_max_penetration_and_buffer_idx;
    std::vector<GradArrowInfo> outer_max_penetration_and_buffer_idx;
};

}  // namespace planning
}  // namespace pnc_x
