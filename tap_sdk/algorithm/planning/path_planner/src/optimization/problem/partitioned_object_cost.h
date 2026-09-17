#pragma once

#include <algorithm>
#include <cmath>
#include <iterator>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include <absl/algorithm/container.h>
#include <absl/strings/str_cat.h>
#include <absl/types/span.h>
#include "common/log.h"

#include "math/geometry/segment2d.h"
#include "math/util.h"
#include "math/vec.h"
#include "optimization/problem/av_model_helper.h"
#include "optimization/problem/cost.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class PartitionedObjectCost : public Cost<PROB> {
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

    using GradArrowInfo = std::tuple<double, /*penetration*/
                                     double, /*buffer*/
                                     Vec2d,  /*foot_point*/
                                     Vec2d /*direction*/>;

    struct Object {
        std::vector<Segment2d> lines;
        std::vector<double> buffers;
        std::vector<double> gains;
        Vec2d ref_x;
        double offset;
        Vec2d ref_tangent;

        bool enable = false;
    };

    struct filter {
        Vec2d ref_x;
        Vec2d ref_tangent;
        double offset;
    };

    static constexpr double kNormalizedScale = 1.0;
    PartitionedObjectCost(
        std::vector<std::vector<Object>> objects,
        std::vector<filter> filters,
        std::vector<double> dist_to_rac,
        std::vector<double> angle_to_axis,
        std::vector<double> cascade_gains,
        const AvModelHelper<PROB> *av_model_helper,
        std::vector<std::string> sub_names,
        bool using_hessian_approximate,
        std::string name_in = absl::StrCat(PROB::kProblemPrefix,
                                        "PartitionedObjectCost"),
        double scale_in = 1.0,
        CostType cost_type_in = Cost<PROB>::CostType::GROUP_OBJECT)
        : Cost<PROB>(std::move(name_in), scale_in * kNormalizedScale, cost_type_in),
          objects_(std::move(objects)),
          filters_(std::move(filters)),
          num_objects_(static_cast<int>(objects_.size())),
          dist_to_rac_(std::move(dist_to_rac)),
          angle_to_axis_(std::move(angle_to_axis)),
          circle_size_(static_cast<int>(dist_to_rac_.size())),
          cascade_gains_(std::move(cascade_gains)),
          av_model_helper_(av_model_helper),
          sub_names_(std::move(sub_names)),
          using_hessian_approximate_(using_hessian_approximate) {
        XCHECK_EQ(cascade_gains_.size(), sub_names_.size());
        XCHECK_EQ(dist_to_rac_.size(), angle_to_axis_.size());
        XCHECK_EQ(objects_.size(), filters_.size());

        outer_filtered_.resize(num_objects_, 0);
        penetrations_.resize(num_objects_);
        penetration_jacobians_.resize(num_objects_);
        penetration_hessians_.resize(num_objects_);
        filtered_.resize(num_objects_);
        in_object_.resize(num_objects_);
        in_corner_region_.resize(num_objects_);
        lines_ptr_.resize(num_objects_);

        for (int k = 0; k < num_objects_; ++k) {
            penetrations_[k].resize(circle_size_);
            penetration_jacobians_[k].resize(circle_size_,
                                             PenetrationJacobianType::Zero());
            penetration_hessians_[k].resize(circle_size_,
                                            PenetrationHessianType::Zero());
            filtered_[k].resize(circle_size_, 0);
            in_object_[k].resize(circle_size_, 0);
            in_corner_region_[k].resize(circle_size_, 0);
            lines_ptr_[k].resize(circle_size_, nullptr);
        }

        for (int i = 0, n = num_objects_; i < n; ++i) {
            for (int idx = 0; idx < circle_size_; ++idx) {
                auto &ob = objects_[i][idx];
                XCHECK_EQ(ob.buffers.size(), ob.gains.size());
                XCHECK_GE(cascade_gains_.size(), ob.gains.size());
                auto &penetrations_i = penetrations_[i];
                const auto ob_buffers = absl::MakeConstSpan(ob.buffers);
                penetrations_i[idx].reserve(ob_buffers.size());
                for (int k = 0; k < ob_buffers.size(); ++k) {
                    penetrations_i[idx].push_back(
                        std::numeric_limits<double>::infinity());
                }
            }
        }
        if (av_model_helper_ != nullptr) {
            for (int i = 0; i < dist_to_rac_.size(); ++i) {
                XCHECK_NEAR(dist_to_rac_[i], av_model_helper_->dist_to_rac()[i],
                            1e-9);
                XCHECK_NEAR(angle_to_axis_[i],
                            av_model_helper_->angle_to_axis()[i], 1e-9);
            }
        }

        inner_max_penetration_and_buffer_idx.assign(
            num_objects_, std::make_tuple(std::numeric_limits<double>::infinity(),
                                      std::numeric_limits<double>::infinity(),
                                      Vec2d(0.0, 0.0), Vec2d(0.0, 0.0)));

        outer_max_penetration_and_buffer_idx.assign(
            num_objects_, std::make_tuple(std::numeric_limits<double>::infinity(),
                                      std::numeric_limits<double>::infinity(),
                                      Vec2d(0.0, 0.0), Vec2d(0.0, 0.0)));
    }

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        DividedG res(sub_names_.size());
        horizon = std::min(horizon, num_objects_);
        for (int k = 0; k < horizon; ++k) {
            for (int idx = 0; idx < circle_size_; ++idx) {
                const auto penetrations_k =
                    absl::MakeConstSpan(penetrations_[k][idx]);
                const auto &ob_k = objects_[k][idx];
                for (int i = 0; i < penetrations_k.size(); ++i) {
                    if (penetrations_k[i] < 0.0) {
                        res.AddSubG(i, cascade_gains_[i] * ob_k.gains[i] *
                                           Sqr(penetrations_k[i]));
                    }
                }
            }
        }
        for (int i = 0; i < sub_names_.size(); ++i) {
            res.SetSubName(i, sub_names_[i] + Cost<PROB>::name());
        }
        res.Multi(0.5 * Cost<PROB>::scale());
        return res;
    }

    DividedG EvaluateGWithDebugInfo(int k,
                                    const StateType &x,
                                    const ControlType &u,
                                    bool using_scale) const override {
        XCHECK_GE(k, 0);
        std::vector<double> cascade_gains(cascade_gains_.size());
        if (using_scale) {
            cascade_gains = cascade_gains_;
        } else {
            std::fill(cascade_gains.begin(), cascade_gains.end(), 1.0);
        }
        DividedG res(sub_names_.size());
        for (int i = 0; i < sub_names_.size(); ++i) {
            res.SetSubName(i, sub_names_[i] + Cost<PROB>::name());
        }
        if (k >= num_objects_) return res;
        for (int idx = 0; idx < circle_size_; ++idx) {
            const auto penetrations_k =
                absl::MakeConstSpan(penetrations_[k][idx]);
            const auto &ob_k = objects_[k][idx];
            for (int i = 0; i < penetrations_k.size(); ++i) {
                if (penetrations_k[i] < 0.0) {
                    res.AddSubG(i, 0.5 * Cost<PROB>::scale() *
                                       cascade_gains[i] * ob_k.gains[i] *
                                       Sqr(penetrations_k[i]));
                }
            }
        }
        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        XCHECK_GE(k, 0);
        if (k >= num_objects_) return 0.0;

        double g = 0.0;
        for (int idx = 0; idx < circle_size_; ++idx) {
            const auto penetrations_k =
                absl::MakeConstSpan(penetrations_[k][idx]);
            const auto &ob_k = objects_[k][idx];
            for (int i = 0; i < penetrations_k.size(); ++i) {
                if (penetrations_k[i] < 0.0) {
                    g += 0.5 * Cost<PROB>::scale() * cascade_gains_[i] *
                         ob_k.gains[i] * Sqr(penetrations_k[i]);
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
        if (k >= num_objects_) return;

        for (int idx = 0; idx < circle_size_; ++idx) {
            const auto penetrations_k =
                absl::MakeConstSpan(penetrations_[k][idx]);
            const auto &ob_k = objects_[k][idx];
            const auto &penetration_jacobians_k =
                penetration_jacobians_[k][idx];
            for (int i = 0; i < penetrations_k.size(); ++i) {
                if (penetrations_k[i] < 0.0) {
                    *dgdx += Cost<PROB>::scale() * cascade_gains_[i] *
                             ob_k.gains[i] * penetrations_k[i] *
                             penetration_jacobians_k;
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
        if (k >= num_objects_) return;
        for (int idx = 0; idx < circle_size_; ++idx) {
            const auto penetrations_k =
                absl::MakeConstSpan(penetrations_[k][idx]);
            const auto &ob_k = objects_[k][idx];
            const auto &penetration_jacobians_k =
                penetration_jacobians_[k][idx];
            const auto &penetration_hessians_k = penetration_hessians_[k][idx];
            for (int i = 0; i < penetrations_k.size(); ++i) {
                if (penetrations_k[i] < 0.0) {
                    if (using_hessian_approximate_) {
                        *ddgdxdx += Cost<PROB>::scale() * cascade_gains_[i] *
                                    ob_k.gains[i] *
                                    (penetration_jacobians_k.transpose() *
                                     penetration_jacobians_k);
                    } else {
                        *ddgdxdx +=
                            Cost<PROB>::scale() * cascade_gains_[i] *
                            ob_k.gains[i] *
                            (penetrations_k[i] * penetration_hessians_k +
                             penetration_jacobians_k.transpose() *
                                 penetration_jacobians_k);
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
                const ControlsType &us,
                int horizon) override {
        const std::vector<std::vector<Vec2d>> *centers_ptr = nullptr;
        if (av_model_helper_ != nullptr) {
            centers_ptr = &av_model_helper_->centers();
        }
        Vec2d x_fac_val;

        horizon = std::min(horizon, num_objects_);
        for (int k = 0; k < horizon; ++k) {
            outer_filtered_[k] = false;

            for (int i = 0; i < circle_size_; ++i) {
                auto penetrations_k = absl::MakeSpan(penetrations_[k][i]);

                for (int i = 0; i < penetrations_k.size(); ++i) {
                    penetrations_k[i] = std::numeric_limits<double>::infinity();
                }
            }

            const Vec2d pos = PROB::pos(xs, k);

            const auto &local_filter = filters_[k];
            if (std::abs((pos - local_filter.ref_x).dot(local_filter.ref_tangent)) >
                local_filter.offset) {
                outer_filtered_[k] = true;
                continue;
            }

            // 圈 i 内的“最小
            // penetration”（inner/outer各一份；无论是否侵入都比较）
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

            for (int i = 0; i < circle_size_; ++i) {
                filtered_[k][i] = false;
                in_object_[k][i] = false;
                lines_ptr_[k][i] = nullptr;
                in_corner_region_[k][i] = false;

                auto penetrations_k = absl::MakeSpan(penetrations_[k][i]);
                const Object &ob = objects_[k][i];

                if (!ob.enable) continue;
                const double dist_to_rac = dist_to_rac_[i];
                const double angle_to_axis = angle_to_axis_[i];

                const Vec2d *x_fac_ptr = nullptr;
                if (av_model_helper_ != nullptr) {
                    x_fac_ptr = &(*centers_ptr)[k][i];
                } else {
                    x_fac_ptr = &x_fac_val;
                    const Vec2d tangent_val = Vec2d::FastUnitFromAngleN12(
                        PROB::theta(xs, k) + angle_to_axis);
                    x_fac_val = pos + tangent_val * dist_to_rac;
                }

                const Vec2d &x_fac = *x_fac_ptr;

                if (std::abs((x_fac - ob.ref_x).dot(ob.ref_tangent)) >
                    ob.offset) {
                    filtered_[k][i] = true;
                    continue;
                }

                const auto lines = absl::MakeConstSpan(ob.lines);
                const auto buffers = absl::MakeConstSpan(ob.buffers);

                std::vector<double> cross_prods =
                    compute_point_cross_prod_on_lines(lines, x_fac);
                const bool in_object = absl::c_all_of(
                    cross_prods,
                    [](double cross_prod) { return cross_prod >= 0.0; });
                in_object_[k][i] = in_object;
                if (in_object) {
                    auto min_iter = absl::c_min_element(cross_prods);
                    const int min_index =
                        std::distance(cross_prods.begin(), min_iter);
                    const Segment2d &line = lines[min_index];
                    lines_ptr_[k][i] = &line;

                    Vec2d foot_point(0.0, 0.0);
                    Vec2d dir(0.0, 0.0);
                    (void)line.GetPerpendicularFootAndDir(x_fac, &foot_point, &dir);

                    const Vec2d &obs_unit_dir_perp =
                        line.unit_direction().Perp();
                    const double dist =
                        -(x_fac - line.start()).dot(obs_unit_dir_perp);

                    for (size_t j = 0; j < penetrations_k.size(); j++) {
                      const double buffer_j = buffers[j];
                      const double penetration = dist - buffers[j];
                      penetrations_k[j] = penetration;

                      if ((j % 2) == 0) { // inner
                        if (penetration < best_inner_pen) {
                          best_inner_pen = penetration;
                          best_inner_j = j;
                          best_inner_info = std::make_tuple(
                              penetration, buffer_j, foot_point, dir);
                        }
                      } else { // outer
                        if (penetration < best_outer_pen) {
                          best_outer_pen = penetration;
                          best_outer_j = j;
                          best_outer_info = std::make_tuple(
                              penetration, buffer_j, foot_point, dir);
                        }
                      }
                    }
                } else {
                    int index = 0;
                    const bool is_in_corner_region = compute_pos_partition(
                        lines, x_fac, cross_prods, &index);

                    const Segment2d &line = lines[index];
                    lines_ptr_[k][i] = &line;
                    in_corner_region_[k][i] = is_in_corner_region;

                    Vec2d foot_point(0.0, 0.0);
                    Vec2d dir(0.0, 0.0);
                    (void)line.GetPerpendicularFootAndDir(x_fac, &foot_point,
                                                    &dir);

                    if (!is_in_corner_region) {
                        const Vec2d obs_unit_dir_perp =
                            line.unit_direction().Perp();
                        const double dist =
                            -(x_fac - line.start()).dot(obs_unit_dir_perp);
                        for (size_t j = 0; j < penetrations_k.size(); j++) {
                            const double buffer_j = buffers[j];
                            const double penetration = dist - buffers[j];
                            penetrations_k[j] = penetration;

                            if ((j % 2) == 0) { // inner
                                if (penetration < best_inner_pen) {
                                best_inner_pen = penetration;
                                best_inner_j = j;
                                best_inner_info = std::make_tuple(
                                    penetration, buffer_j, foot_point, dir);
                                }
                            } else { // outer
                                if (penetration < best_outer_pen) {
                                best_outer_pen = penetration;
                                best_outer_j = j;
                                best_outer_info = std::make_tuple(
                                    penetration, buffer_j, foot_point, dir);
                                }
                            }
                        }
                    } else {
                        const Vec2d diff_x1_fac = x_fac - line.start();
                        const double diff_x1_fac_norm = diff_x1_fac.norm();
                        for (size_t j = 0; j < penetrations_k.size(); j++) {
                            const double buffer_j = buffers[j];
                            const double penetration = diff_x1_fac_norm - buffer_j;
                            penetrations_k[j] = penetration;

                            if ((j % 2) == 0) { // inner
                                if (penetration < best_inner_pen) {
                                best_inner_pen = penetration;
                                best_inner_j = j;
                                best_inner_info = std::make_tuple(
                                    penetration, buffer_j, foot_point, dir);
                                }
                            } else { // outer
                                if (penetration < best_outer_pen) {
                                best_outer_pen = penetration;
                                best_outer_j = j;
                                best_outer_info = std::make_tuple(
                                    penetration, buffer_j, foot_point, dir);
                                }
                            }
                        }
                    }
                }
            }
            // 将圈 i 的“圈内最小”写回（便于调试/可视化）
            if (best_inner_j >= 0) {
              inner_max_penetration_and_buffer_idx[k] = best_inner_info;
            }
            if (best_outer_j >= 0) {
              outer_max_penetration_and_buffer_idx[k] = best_outer_info;
            }
        }
    }

    void UpdateDerivatives(const StatesType &xs,
                           const ControlsType &us,
                           int horizon) override {
        const std::vector<std::vector<Vec2d>> *centers_ptr = nullptr;
        const std::vector<std::vector<Vec2d>> *tangents_ptr = nullptr;
        const std::vector<std::vector<Vec2d>> *normals_ptr = nullptr;
        if (av_model_helper_ != nullptr) {
            centers_ptr = &av_model_helper_->centers();
            tangents_ptr = &av_model_helper_->tangents();
            normals_ptr = &av_model_helper_->normals();
        }
        Vec2d tangent_val, normal_val, x_fac_val;

        horizon = std::min(horizon, num_objects_);
        for (int k = 0; k < horizon; ++k) {
            for (int i = 0; i < circle_size_; ++i) {
                auto &penetration_jacobians_k = penetration_jacobians_[k][i];
                auto &penetration_hessians_k = penetration_hessians_[k][i];
                penetration_jacobians_k.template segment<3>(
                    PROB::kStateXIndex) = Eigen::Matrix<double, 3, 1>::Zero();
                penetration_hessians_k.template block<3, 3>(
                    PROB::kStateXIndex, PROB::kStateXIndex) =
                    Eigen::Matrix<double, 3, 3>::Zero();
            }

            const Vec2d pos = PROB::pos(xs, k);

            if (outer_filtered_[k]) {
                continue;
            }

            for (int i = 0; i < circle_size_; ++i) {
                auto &penetration_jacobians_k = penetration_jacobians_[k][i];
                auto &penetration_hessians_k = penetration_hessians_[k][i];
                const Object &ob = objects_[k][i];

                if (!ob.enable) continue;
                const double dist_to_rac = dist_to_rac_[i];
                const double angle_to_axis = angle_to_axis_[i];

                const Vec2d *tangent_ptr = nullptr;
                const Vec2d *normal_ptr = nullptr;
                const Vec2d *x_fac_ptr = nullptr;
                if (av_model_helper_ != nullptr) {
                    tangent_ptr = &(*tangents_ptr)[k][i];
                    normal_ptr = &(*normals_ptr)[k][i];
                    x_fac_ptr = &(*centers_ptr)[k][i];
                } else {
                    tangent_ptr = &tangent_val;
                    normal_ptr = &normal_val;
                    x_fac_ptr = &x_fac_val;
                    tangent_val = Vec2d::FastUnitFromAngleN12(
                        PROB::theta(xs, k) + angle_to_axis);
                    normal_val = tangent_val.Perp();
                    x_fac_val = pos + tangent_val * dist_to_rac;
                }

                const Vec2d &tangent = *tangent_ptr;
                const Vec2d &normal = *normal_ptr;
                const Vec2d &x_fac = *x_fac_ptr;

                if (filtered_[k][i]) {
                    continue;
                }

                const bool in_object = in_object_[k][i];
                if (in_object) {
                    const Segment2d &line = *lines_ptr_[k][i];
                    const Vec2d &obs_unit_dir_perp =
                        line.unit_direction().Perp();
                    penetration_jacobians_k.template segment<2>(
                        PROB::kStateXIndex) = -obs_unit_dir_perp;
                    if (dist_to_rac != 0.0) {
                        penetration_jacobians_k(PROB::kStateThetaIndex) =
                            -obs_unit_dir_perp.dot(normal * dist_to_rac);
                        penetration_hessians_k(PROB::kStateThetaIndex,
                                               PROB::kStateThetaIndex) =
                            -obs_unit_dir_perp.dot(-tangent * dist_to_rac);
                    }
                } else {
                    const bool is_in_corner_region = in_corner_region_[k][i];
                    const Segment2d &line = *lines_ptr_[k][i];

                    if (!is_in_corner_region) {
                        const Vec2d obs_unit_dir_perp =
                            line.unit_direction().Perp();
                        penetration_jacobians_k.template segment<2>(
                            PROB::kStateXIndex) = -obs_unit_dir_perp;
                        if (dist_to_rac != 0.0) {
                            penetration_jacobians_k(PROB::kStateThetaIndex) =
                                -obs_unit_dir_perp.dot(normal * dist_to_rac);
                            penetration_hessians_k(PROB::kStateThetaIndex,
                                                   PROB::kStateThetaIndex) =
                                -obs_unit_dir_perp.dot(-tangent * dist_to_rac);
                        }
                    } else {
                        const Vec2d diff_x1_fac = x_fac - line.start();
                        const double diff_x1_fac_norm = diff_x1_fac.norm();
                        const double diff_x1_fac_norm_div =
                            1.0 / diff_x1_fac_norm;
                        const double sqrtqrdiff_x1 = Cube(diff_x1_fac_norm_div);

                        penetration_jacobians_k.template segment<2>(
                            PROB::kStateXIndex) =
                            diff_x1_fac * diff_x1_fac_norm_div;
                        penetration_hessians_k(PROB::kStateXIndex,
                                               PROB::kStateXIndex) =
                            diff_x1_fac_norm_div -
                            diff_x1_fac.x() * diff_x1_fac.x() * sqrtqrdiff_x1;
                        penetration_hessians_k(PROB::kStateXIndex,
                                               PROB::kStateYIndex) =
                            -diff_x1_fac.x() * diff_x1_fac.y() * sqrtqrdiff_x1;
                        penetration_hessians_k(PROB::kStateYIndex,
                                               PROB::kStateXIndex) =
                            penetration_hessians_k(PROB::kStateXIndex,
                                                   PROB::kStateYIndex);
                        penetration_hessians_k(PROB::kStateYIndex,
                                               PROB::kStateYIndex) =
                            diff_x1_fac_norm_div -
                            diff_x1_fac.y() * diff_x1_fac.y() * sqrtqrdiff_x1;
                        if (dist_to_rac != 0.0) {
                            penetration_jacobians_k(PROB::kStateThetaIndex) =
                                diff_x1_fac.dot(normal * dist_to_rac) *
                                diff_x1_fac_norm_div;
                            penetration_hessians_k(PROB::kStateXIndex,
                                                   PROB::kStateThetaIndex) =
                                normal.x() * dist_to_rac *
                                    diff_x1_fac_norm_div -
                                sqrtqrdiff_x1 * diff_x1_fac.x() *
                                    diff_x1_fac.dot(normal * dist_to_rac);
                            penetration_hessians_k(PROB::kStateYIndex,
                                                   PROB::kStateThetaIndex) =
                                normal.y() * dist_to_rac *
                                    diff_x1_fac_norm_div -
                                sqrtqrdiff_x1 * diff_x1_fac.y() *
                                    diff_x1_fac.dot(normal * dist_to_rac);
                            penetration_hessians_k(PROB::kStateThetaIndex,
                                                   PROB::kStateXIndex) =
                                penetration_hessians_k(PROB::kStateXIndex,
                                                       PROB::kStateThetaIndex);
                            penetration_hessians_k(PROB::kStateThetaIndex,
                                                   PROB::kStateYIndex) =
                                penetration_hessians_k(PROB::kStateYIndex,
                                                       PROB::kStateThetaIndex);
                            penetration_hessians_k(PROB::kStateThetaIndex,
                                                   PROB::kStateThetaIndex) =
                                (diff_x1_fac.dot(-tangent * dist_to_rac) +
                                 dist_to_rac *
                                     normal.dot(normal * dist_to_rac)) *
                                    diff_x1_fac_norm_div -
                                sqrtqrdiff_x1 *
                                    diff_x1_fac.dot(normal * dist_to_rac) *
                                    diff_x1_fac.dot(normal * dist_to_rac);
                        }
                    }
                }
            }
        }
    }

GradArrowWithCost EvaluateBoundary(int k) const override {
    XCHECK_GE(k, 0);
    GradArrowWithCost result;
    if (k < num_objects_) {
        const auto &inner = inner_max_penetration_and_buffer_idx[k];
        const auto &outer = outer_max_penetration_and_buffer_idx[k];

        const auto &inner_buffer = std::get<1>(inner);
        const auto &inner_foot = std::get<2>(inner);
        const auto &inner_dir = std::get<3>(inner);

        const auto &outer_buffer = std::get<1>(outer);
        const auto &outer_foot = std::get<2>(outer);
        const auto &outer_dir = std::get<3>(outer);

        if (!std::isfinite(inner_buffer) || !std::isfinite(outer_buffer)) {
            return result; 
        }

        // foot_point = foot + dir * buffer
        const double inner_px = inner_foot.x() + inner_dir.x() * inner_buffer;
        const double inner_py = inner_foot.y() + inner_dir.y() * inner_buffer;
        const double outer_px = outer_foot.x() + outer_dir.x() * outer_buffer;
        const double outer_py = outer_foot.y() + outer_dir.y() * outer_buffer;

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
    }

    return result;
}

 private:
    const std::vector<double> compute_point_cross_prod_on_lines(
        absl::Span<const Segment2d> lines, const Vec2d &pos) {
        std::vector<double> cross_prods;
        cross_prods.reserve(lines.size());
        for (const auto &line : lines) {
            cross_prods.emplace_back(line.ProductOntoUnit(pos));
        }
        return cross_prods;
    }

    bool compute_pos_partition(absl::Span<const Segment2d> lines,
                               const Vec2d &pos,
                               absl::Span<const double> cross_pod,
                               int *index) {
        bool is_in_corner_region = false;
        const double prod_start = lines[0].ProjectOntoUnit(pos);
        const double prod_end = lines.back().ProjectOntoUnit(pos);
        if ((prod_start < 0.0) && (cross_pod[0] < 0.0)) {
            *index = 0;
        } else {
            if ((prod_end > lines.back().length()) && (cross_pod.back() < 0.0)) {
                *index = static_cast<int>(lines.size()) - 1;
            } else {
                for (int i = 0; i < lines.size(); ++i) {
                    const Segment2d &line = lines[i];
                    const double dot = line.ProjectOntoUnit(pos);
                    if ((dot >= 0.0) && (dot <= line.length()) &&
                        (cross_pod[i] <= 0)) {
                        *index = i;
                        break;
                    }
                    if ((dot < 0.0) && (i != 0)) {
                        *index = i;
                        is_in_corner_region = true;
                        break;
                    }
                }
            }
        }
        return is_in_corner_region;
    }
    std::vector<std::vector<Object>> objects_;
    std::vector<filter> filters_;
    int num_objects_;

    std::vector<double> dist_to_rac_;
    std::vector<double> angle_to_axis_;
    int circle_size_;

    std::vector<double> cascade_gains_;
    const AvModelHelper<PROB> *av_model_helper_;

    std::vector<std::string> sub_names_;
    bool using_hessian_approximate_;

    using PenetrationJacobianType = Eigen::Matrix<double, 1, PROB::kStateSize>;
    using PenetrationHessianType =
        Eigen::Matrix<double, PROB::kStateSize, PROB::kStateSize>;

    std::vector<std::vector<std::vector<double>>> penetrations_;
    std::vector<char> outer_filtered_;
    std::vector<std::vector<char>> filtered_;
    std::vector<std::vector<char>> in_object_;
    std::vector<std::vector<char>> in_corner_region_;
    std::vector<std::vector<const Segment2d *>> lines_ptr_;
    std::vector<std::vector<PenetrationJacobianType>> penetration_jacobians_;
    std::vector<std::vector<PenetrationHessianType>> penetration_hessians_;

    std::vector<GradArrowInfo> inner_max_penetration_and_buffer_idx;
    std::vector<GradArrowInfo> outer_max_penetration_and_buffer_idx;
};

}  // namespace planning
}  // namespace pnc_x
