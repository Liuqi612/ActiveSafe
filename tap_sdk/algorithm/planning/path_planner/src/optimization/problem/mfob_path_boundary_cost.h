
#pragma once

#include <algorithm>
#include <boost/algorithm/clamp.hpp>
#include <functional>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "base/macros.h"
#include <absl/status/statusor.h>
#include <absl/strings/str_cat.h>
#include "common/log.h"

#include "math/fast_math.h"
#include "math/frenet_common.h"
#include "math/frenet_frame.h"
#include "math/util.h"
#include "math/vec.h"
#include "optimization/problem/center_line_query_helper.h"
#include "optimization/problem/cost.h"
#include "optimization/problem/mixed_fourth_order_bicycle.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class MfobPathBoundaryCost : public Cost<PROB> {
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

    static constexpr double kNormalizedScale = 10.0;
    MfobPathBoundaryCost(int horizon,
                         VehicleGeometryParamsProto vehicle_geometry_params,
                         const std::vector<Vec2d> &path_points,
                         const CenterLineQueryHelper<PROB> *center_line_helper,
                         std::vector<double> l_offsets,
                         std::vector<std::vector<double>> path_boundary_dists,
                         bool left,
                         bool using_hessian_approximate,
                         std::vector<double> mid_edges_to_center,
                         std::vector<std::vector<double>> ref_gains,
                         std::vector<std::string> sub_names,
                         bool use_qtfm,
                         std::vector<double> buffers_min = {-1.0},
                         std::vector<double> rear_buffers_max = {1.0},
                         std::vector<double> front_buffers_max = {0.6},
                         std::vector<double> mid_buffers_max = {0.6},
                         std::vector<double> cascade_gains = {1.0},
                         std::vector<double> rear_gain = {1.0},
                         std::vector<double> front_gain = {1.0},
                         std::string name = absl::StrCat(PROB::kProblemPrefix,
                                                         "PathBoundaryCost"),
                         double scale = 1.0,
                         CostType cost_type = Cost<PROB>::CostType::MUST_HAVE)
        : Cost<PROB>(std::move(name), scale * kNormalizedScale, cost_type),
          horizon_(horizon),
          vehicle_geometry_params_(std::move(vehicle_geometry_params)),
          path_points_(path_points),
          l_offsets_(std::move(l_offsets)),
          path_boundary_dists_(std::move(path_boundary_dists)),
          path_boundary_size_(static_cast<int>(l_offsets_.size())),
          left_(left),
          using_hessian_approximate_(using_hessian_approximate),

          mid_edges_to_center_(std::move(mid_edges_to_center)),
          ref_gains_(std::move(ref_gains)),
          cascade_gains_(std::move(cascade_gains)),
          sub_names_(std::move(sub_names)),
          center_line_helper_(center_line_helper),
          rear_gain_(std::move(rear_gain)),
          front_gain_(std::move(front_gain)) {
        static_cast<void>(use_qtfm);
        XCHECK_GT(horizon_, 0);
        XCHECK_GT(path_points_.size(), 1);
        XCHECK_EQ(path_boundary_dists_.size(), sub_names_.size());
        XCHECK_EQ(path_boundary_dists_.size(), cascade_gains_.size());
        XCHECK_EQ(path_boundary_dists_.size(), rear_gain_.size());
        XCHECK_EQ(path_boundary_dists_.size(), front_gain_.size());
        XCHECK_EQ(path_boundary_dists_.size(), ref_gains_.size());
        XCHECK_EQ(path_boundary_dists_.size(), buffers_min.size());
        XCHECK_EQ(path_boundary_dists_.size(), rear_buffers_max.size());
        XCHECK_EQ(path_boundary_dists_.size(), front_buffers_max.size());
        XCHECK_EQ(path_boundary_dists_.size(), mid_buffers_max.size());
        XCHECK_GE(path_points_.size(), l_offsets_.size());
        XCHECK_GE(path_points_.size(), path_boundary_dists_.front().size());
        if (center_line_helper_ != nullptr) {
        } else {
            auto frame_or = BuildBVHFrenetFrame(path_points, true);
            XCHECK(frame_or.ok());
            path_ = std::move(frame_or).value();
        }
        const double half_width = vehicle_geometry_params_.width() * 0.5;
        const int num_of_path_boundaries = cascade_gains_.size();

        rear_clamped_path_boundary_buffers_.resize(num_of_path_boundaries);
        front_clamped_path_boundary_buffers_.resize(num_of_path_boundaries);
        mid_clamped_path_boundary_buffers_.resize(mid_edges_to_center_.size());
        for (int i = 0; i < mid_edges_to_center_.size(); ++i) {
            mid_clamped_path_boundary_buffers_[i].resize(
                num_of_path_boundaries);
        }
        for (int i = 0; i < num_of_path_boundaries; ++i) {
            auto &rear_clamped_path_boundary_buffers =
                rear_clamped_path_boundary_buffers_[i];
            auto &front_clamped_path_boundary_buffers =
                front_clamped_path_boundary_buffers_[i];

            const int path_boundary_dists_i_size =
                path_boundary_dists_[i].size();
            rear_clamped_path_boundary_buffers.reserve(
                path_boundary_dists_i_size);
            front_clamped_path_boundary_buffers.reserve(
                path_boundary_dists_i_size);
            for (int j = 0; j < mid_edges_to_center_.size(); ++j) {
                mid_clamped_path_boundary_buffers_[j][i].reserve(
                    path_boundary_dists_i_size);
            }
            const auto &path_boundary_dist = path_boundary_dists_[i];
            for (int k = 0; k < path_boundary_dist.size(); ++k) {
                double center_to_boundary_dist = path_boundary_dist[k];
                if (left_) {
                    center_to_boundary_dist -= l_offsets_[k];
                } else {
                    center_to_boundary_dist += l_offsets_[k];
                }
                rear_clamped_path_boundary_buffers.push_back(
                    boost::algorithm::clamp(
                        center_to_boundary_dist - half_width, buffers_min[i],
                        rear_buffers_max[i]));
                front_clamped_path_boundary_buffers.push_back(
                    boost::algorithm::clamp(
                        center_to_boundary_dist - half_width, buffers_min[i],
                        front_buffers_max[i]));
                for (int j = 0; j < mid_edges_to_center_.size(); ++j) {
                    mid_clamped_path_boundary_buffers_[j][i].push_back(
                        boost::algorithm::clamp(
                            center_to_boundary_dist - half_width,
                            buffers_min[i], mid_buffers_max[i]));
                }
            }
        }

        const std::vector<double> horizon_size_double_vector(horizon_, 0.0);
        const std::vector<Vec2d> horizon_size_vec2d_vector(horizon_,
                                                           {0.0, 0.0});
        const std::vector<std::pair<int, int>> horizon_size_int_pair_vector(
            horizon_, {0, 0});

        mid_normals_.resize(mid_edges_to_center_.size(),
                            horizon_size_vec2d_vector);
        mid_index_pairs_.resize(mid_edges_to_center_.size(),
                                horizon_size_int_pair_vector);
        mid_alphas_.resize(mid_edges_to_center_.size(),
                           horizon_size_double_vector);
        mid_dynamic_buffers_.resize(mid_edges_to_center_.size());
        mid_to_path_boundary_dists_.resize(mid_edges_to_center_.size());
        mid_gains_.resize(mid_edges_to_center_.size());
        mid_effective_index_.resize(mid_edges_to_center_.size());

        state_dynamic_buffers_.resize(num_of_path_boundaries,
                                      horizon_size_double_vector);
        corner_dynamic_buffers_.resize(num_of_path_boundaries,
                                       horizon_size_double_vector);
        state_to_path_boundary_dists_.resize(num_of_path_boundaries,
                                             horizon_size_double_vector);
        corner_to_path_boundary_dists_.resize(num_of_path_boundaries,
                                              horizon_size_double_vector);
        state_gains_.resize(num_of_path_boundaries, horizon_size_double_vector);
        corner_gains_.resize(num_of_path_boundaries,
                             horizon_size_double_vector);
        for (int i = 0; i < mid_edges_to_center_.size(); ++i) {
            mid_dynamic_buffers_[i].resize(num_of_path_boundaries,
                                           horizon_size_double_vector);
            mid_to_path_boundary_dists_[i].resize(num_of_path_boundaries,
                                                  horizon_size_double_vector);
            mid_gains_[i].resize(num_of_path_boundaries,
                                 horizon_size_double_vector);
        }

        inner_max_penetration_and_buffer_idx.assign(
            horizon_, std::make_tuple(std::numeric_limits<double>::infinity(),
                                      std::numeric_limits<double>::infinity(),
                                      Vec2d(0.0, 0.0), Vec2d(0.0, 0.0)));

        outer_max_penetration_and_buffer_idx.assign(
            horizon_, std::make_tuple(std::numeric_limits<double>::infinity(),
                                      std::numeric_limits<double>::infinity(),
                                      Vec2d(0.0, 0.0), Vec2d(0.0, 0.0)));

        state_normals_.resize(horizon_);
        state_index_pairs_.resize(horizon_);
        state_alphas_.resize(horizon_);
        corner_normals_.resize(horizon_);
        corner_index_pairs_.resize(horizon_);
        corner_alphas_.resize(horizon_);
    }

    DividedG SumGForAllSteps(const StatesType &xs,
                             const ControlsType &us,
                             int horizon) const override {
        XCHECK_EQ(horizon, horizon_);
        DividedG res(static_cast<int>(sub_names_.size()));
        for (int k = 0; k < horizon_; ++k) {
            for (int j = 0; j < path_boundary_dists_.size(); ++j) {
                if (k < state_effective_index_) {
                    const double d = state_to_path_boundary_dists_[j][k];
                    if (d < state_dynamic_buffers_[j][k]) {
                        res.AddSubG(
                            j, 0.5 * Cost<PROB>::scale() * state_gains_[j][k] *
                                   rear_gain_[j] *
                                   Sqr(state_dynamic_buffers_[j][k] - d));
                    }
                }

                if (k < corner_effective_index_) {
                    const double d_corner =
                        corner_to_path_boundary_dists_[j][k];
                    if (d_corner < corner_dynamic_buffers_[j][k]) {
                        res.AddSubG(
                            j,
                            0.5 * Cost<PROB>::scale() * corner_gains_[j][k] *
                                front_gain_[j] *
                                Sqr(corner_dynamic_buffers_[j][k] - d_corner));
                    }
                }

                for (int i = 0; i < mid_edges_to_center_.size(); ++i) {
                    if (k < mid_effective_index_[i]) {
                        const double d_mid =
                            mid_to_path_boundary_dists_[i][j][k];
                        if (d_mid < mid_dynamic_buffers_[i][j][k]) {
                            res.AddSubG(
                                j,
                                0.5 * Cost<PROB>::scale() *
                                    mid_gains_[i][j][k] * front_gain_[j] *
                                    Sqr(mid_dynamic_buffers_[i][j][k] - d_mid));
                        }
                    }
                }
            }
        }
        for (int i = 0; i < sub_names_.size(); ++i) {
            res.SetSubName(i, sub_names_[i] + Cost<PROB>::name());
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
        for (int j = 0; j < path_boundary_dists_.size(); ++j) {
            if (k < state_effective_index_) {
                const double d = state_to_path_boundary_dists_[j][k];
                if (d < state_dynamic_buffers_[j][k]) {
                    res.AddSubG(j, 0.5 * Cost<PROB>::scale() *
                                       state_gains_[j][k] * rear_gain_[j] *
                                       Sqr(state_dynamic_buffers_[j][k] - d));
                }
            }

            if (k < corner_effective_index_) {
                const double d_corner = corner_to_path_boundary_dists_[j][k];
                if (d_corner < corner_dynamic_buffers_[j][k]) {
                    res.AddSubG(
                        j, 0.5 * Cost<PROB>::scale() * corner_gains_[j][k] *
                               front_gain_[j] *
                               Sqr(corner_dynamic_buffers_[j][k] - d_corner));
                }
            }

            for (int i = 0; i < mid_edges_to_center_.size(); ++i) {
                if (k < mid_effective_index_[i]) {
                    const double d_mid = mid_to_path_boundary_dists_[i][j][k];
                    if (d_mid < mid_dynamic_buffers_[i][j][k]) {
                        res.AddSubG(
                            j, 0.5 * Cost<PROB>::scale() * mid_gains_[i][j][k] *
                                   front_gain_[j] *
                                   Sqr(mid_dynamic_buffers_[i][j][k] - d_mid));
                    }
                }
            }
        }
        if (!using_scale) {
            res.VecDiv(cascade_gains_);
        }
        return res;
    }

    double EvaluateG(int k,
                     const StateType &x,
                     const ControlType &u) const override {
        double g = 0.0;
        for (int j = 0; j < path_boundary_dists_.size(); ++j) {
            if (k < state_effective_index_) {
                const double d = state_to_path_boundary_dists_[j][k];
                if (d < state_dynamic_buffers_[j][k]) {
                    g += 0.5 * Cost<PROB>::scale() * state_gains_[j][k] *
                         rear_gain_[j] * Sqr(state_dynamic_buffers_[j][k] - d);
                }
            }

            if (k < corner_effective_index_) {
                const double d_corner = corner_to_path_boundary_dists_[j][k];
                if (d_corner < corner_dynamic_buffers_[j][k]) {
                    g += 0.5 * Cost<PROB>::scale() * corner_gains_[j][k] *
                         front_gain_[j] *
                         Sqr(corner_dynamic_buffers_[j][k] - d_corner);
                }
            }

            for (int i = 0; i < mid_edges_to_center_.size(); ++i) {
                if (k < mid_effective_index_[i]) {
                    const double d_mid = mid_to_path_boundary_dists_[i][j][k];
                    if (d_mid < mid_dynamic_buffers_[i][j][k]) {
                        g += 0.5 * Cost<PROB>::scale() * mid_gains_[i][j][k] *
                             front_gain_[j] *
                             Sqr(mid_dynamic_buffers_[i][j][k] - d_mid);
                    }
                }
            }
        }
        return g;
    }

    void AddDGDx(int k,
                 const StateType &x,
                 const ControlType &u,
                 DGDxType *dgdx) const override {
        const double theta = PROB::StateGetTheta(x);
        const double half_width = vehicle_geometry_params_.width() * 0.5;
        const double cos_theta = fast_math::CosN<12>(theta);
        const double sin_theta = fast_math::SinN<12>(theta);

        for (int j = 0; j < path_boundary_dists_.size(); ++j) {
            if (k < state_effective_index_) {
                const double d = state_to_path_boundary_dists_[j][k];
                if (d < state_dynamic_buffers_[j][k]) {
                    const double d_penetration =
                        d - state_dynamic_buffers_[j][k];
                    const Vec2d segment =
                        path_points_[state_index_pairs_[k].second] -
                        path_points_[state_index_pairs_[k].first];
                    const double d0 =
                        path_boundary_dists_[j][state_index_pairs_[k].first];
                    const double d1 =
                        path_boundary_dists_[j][state_index_pairs_[k].second];
                    double d_buffer = 0.0;
                    if ((state_alphas_[k] >= 0.0) && (state_alphas_[k] <= 1.0)) {
                        d_buffer = rear_clamped_path_boundary_buffers_
                                       [j][state_index_pairs_[k].second] -
                                   rear_clamped_path_boundary_buffers_
                                       [j][state_index_pairs_[k].first];
                    }
                    const double sign = left_ ? -1.0 : 1.0;
                    if ((state_alphas_[k] < 0.0) || (state_alphas_[k] > 1.0)) {
                        (*dgdx).template segment<2>(PROB::kStateXIndex) +=
                            Cost<PROB>::scale() * state_gains_[j][k] *
                            rear_gain_[j] * d_penetration * sign *
                            state_normals_[k].transpose();
                    } else {
                        (*dgdx).template segment<2>(PROB::kStateXIndex) +=
                            Cost<PROB>::scale() * state_gains_[j][k] *
                            rear_gain_[j] * d_penetration *
                            (((d1 - d0 - d_buffer) * segment.transpose() /
                                 segment.squaredNorm()) +
                             (sign * state_normals_[k].transpose()));
                    }
                }
            }

            if (k < corner_effective_index_) {
                AddEdgePointDGDx(
                    dgdx, corner_to_path_boundary_dists_[j][k],
                    vehicle_geometry_params_.front_edge_to_center(), sin_theta,
                    cos_theta, half_width, corner_dynamic_buffers_[j][k],
                    path_boundary_dists_[j],
                    front_clamped_path_boundary_buffers_[j],
                    corner_index_pairs_[k], corner_alphas_[k],
                    corner_normals_[k], corner_gains_[j][k], front_gain_[j]);
            }

            for (int i = 0; i < mid_edges_to_center_.size(); ++i) {
                if (k < mid_effective_index_[i]) {
                    AddEdgePointDGDx(dgdx, mid_to_path_boundary_dists_[i][j][k],
                                     mid_edges_to_center_[i], sin_theta,
                                     cos_theta, half_width,
                                     mid_dynamic_buffers_[i][j][k],
                                     path_boundary_dists_[j],
                                     mid_clamped_path_boundary_buffers_[i][j],
                                     mid_index_pairs_[i][k], mid_alphas_[i][k],
                                     mid_normals_[i][k], mid_gains_[i][j][k],
                                     front_gain_[j]);
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
        const double theta = PROB::StateGetTheta(x);
        const double half_width = vehicle_geometry_params_.width() * 0.5;
        const double cos_theta = fast_math::CosN<12>(theta);
        const double sin_theta = fast_math::SinN<12>(theta);

        for (int j = 0; j < path_boundary_dists_.size(); ++j) {
            if (k < state_effective_index_) {
                const double d = state_to_path_boundary_dists_[j][k];
                if (d < state_dynamic_buffers_[j][k]) {
                    const Vec2d segment =
                        path_points_[state_index_pairs_[k].second] -
                        path_points_[state_index_pairs_[k].first];
                    const double d0 =
                        path_boundary_dists_[j][state_index_pairs_[k].first];
                    const double d1 =
                        path_boundary_dists_[j][state_index_pairs_[k].second];
                    double d_buffer = 0.0;
                    if ((state_alphas_[k] >= 0.0) && (state_alphas_[k] <= 1.0)) {
                        d_buffer = rear_clamped_path_boundary_buffers_
                                       [j][state_index_pairs_[k].second] -
                                   rear_clamped_path_boundary_buffers_
                                       [j][state_index_pairs_[k].first];
                    }
                    const double sign = left_ ? -1.0 : 1.0;
                    if ((state_alphas_[k] < 0.0) || (state_alphas_[k] > 1.0)) {
                        (*ddgdxdx).template block<2, 2>(PROB::kStateXIndex,
                                                        PROB::kStateXIndex) +=
                            Cost<PROB>::scale() * state_gains_[j][k] *
                            rear_gain_[j] * state_normals_[k] *
                            state_normals_[k].transpose();
                    } else {
                        const Vec2d vec = ((d1 - d0 - d_buffer) * segment /
                                              segment.squaredNorm()) +
                                          (sign * state_normals_[k]);
                        (*ddgdxdx).template block<2, 2>(PROB::kStateXIndex,
                                                        PROB::kStateXIndex) +=
                            Cost<PROB>::scale() * state_gains_[j][k] *
                            rear_gain_[j] * vec * vec.transpose();
                    }
                }
            }

            if (k < corner_effective_index_) {
                AddEdgePointDDGDxDx(
                    ddgdxdx, corner_to_path_boundary_dists_[j][k],
                    vehicle_geometry_params_.front_edge_to_center(), sin_theta,
                    cos_theta, half_width, corner_dynamic_buffers_[j][k],
                    path_boundary_dists_[j],
                    front_clamped_path_boundary_buffers_[j],
                    corner_index_pairs_[k], corner_alphas_[k],
                    corner_normals_[k], corner_gains_[j][k], front_gain_[j]);
            }

            for (int i = 0; i < mid_edges_to_center_.size(); ++i) {
                if (k < mid_effective_index_[i]) {
                    AddEdgePointDDGDxDx(
                        ddgdxdx, mid_to_path_boundary_dists_[i][j][k],
                        mid_edges_to_center_[i], sin_theta, cos_theta,
                        half_width, mid_dynamic_buffers_[i][j][k],
                        path_boundary_dists_[j],
                        mid_clamped_path_boundary_buffers_[i][j],
                        mid_index_pairs_[i][k], mid_alphas_[i][k],
                        mid_normals_[i][k], mid_gains_[i][j][k],
                        front_gain_[j]);
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
        XCHECK_EQ(horizon, horizon_);
        // if (left_) {
        //     VLOG(4) << "Update rac for left boundary.";
        // } else {
        //     VLOG(4) << "Update rac for right boundary.";
        // }

        const double half_width = vehicle_geometry_params_.width() * 0.5;
        const auto get_rac_to_path_boundary_distance =
            [&half_width, this](double boundary_dist,
                                double state_dist) -> double {
            return this->left_ ? boundary_dist - state_dist - half_width
                               : boundary_dist + state_dist - half_width;
        };

        if (center_line_helper_ == nullptr) {
            Update(GetStatePosAtStep, get_rac_to_path_boundary_distance,
                   rear_clamped_path_boundary_buffers_, xs, &state_normals_,
                   &state_dynamic_buffers_, &state_to_path_boundary_dists_,
                   &state_gains_, &state_index_pairs_, &state_alphas_,
                   &state_effective_index_);
        } else {
            UpdateWithCenterLineHelper(get_rac_to_path_boundary_distance,
                                       rear_clamped_path_boundary_buffers_, xs,
                                       &state_normals_, &state_dynamic_buffers_,
                                       &state_to_path_boundary_dists_,
                                       &state_gains_, &state_index_pairs_,
                                       &state_alphas_, &state_effective_index_);
        }
        // if (left_) {
        //     VLOG(4) << "Update corner for left boundary.";
        // } else {
        //     VLOG(4) << "Update corner for right boundary.";
        // }

        const auto get_edge_point_to_path_boundary_distance =
            [this](double boundary_dist, double state_dist) -> double {
            return this->left_ ? boundary_dist - state_dist
                               : boundary_dist + state_dist;
        };

        Update(std::bind(GetEdgePointPosAtStep, std::placeholders::_1,
                         std::placeholders::_2,
                         vehicle_geometry_params_.front_edge_to_center(),
                         vehicle_geometry_params_, left_),
               get_edge_point_to_path_boundary_distance,
               front_clamped_path_boundary_buffers_, xs, &corner_normals_,
               &corner_dynamic_buffers_, &corner_to_path_boundary_dists_,
               &corner_gains_, &corner_index_pairs_, &corner_alphas_,
               &corner_effective_index_);
        // if (left_) {
        //     VLOG(4) << "Update mid edge for left boundary.";
        // } else {
        //     VLOG(4) << "Update mid edge for right boundary.";
        // }

        for (int i = 0; i < mid_edges_to_center_.size(); ++i) {
            Update(std::bind(GetEdgePointPosAtStep, std::placeholders::_1,
                             std::placeholders::_2, mid_edges_to_center_[i],
                             vehicle_geometry_params_, left_),
                   get_edge_point_to_path_boundary_distance,
                   mid_clamped_path_boundary_buffers_[i], xs, &mid_normals_[i],
                   &mid_dynamic_buffers_[i], &mid_to_path_boundary_dists_[i],
                   &mid_gains_[i], &mid_index_pairs_[i], &mid_alphas_[i],
                   &mid_effective_index_[i]);
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
    static Vec2d GetStatePosAtStep(const StatesType &xs, int k) {
        return PROB::StateGetPos(PROB::GetStateAtStep(xs, k));
    }
    static Vec2d GetEdgePointPosAtStep(
        const StatesType &xs,
        int k,
        double dist_to_rac,
        const VehicleGeometryParamsProto &vehicle_geometry_params,
        bool left) {
        const StateType state = PROB::GetStateAtStep(xs, k);
        const double x = PROB::StateGetX(state);
        const double y = PROB::StateGetY(state);
        const double theta = PROB::StateGetTheta(state);
        const double half_width = vehicle_geometry_params.width() * 0.5;
        const double cos_theta = fast_math::CosN<12>(theta);
        const double sin_theta = fast_math::SinN<12>(theta);
        return left
                   ? Vec2d(x + (dist_to_rac * cos_theta) - (half_width * sin_theta),
                           y + (dist_to_rac * sin_theta) + (half_width * cos_theta))
                   : Vec2d(
                         x + (dist_to_rac * cos_theta) + (half_width * sin_theta),
                         y + (dist_to_rac * sin_theta) - (half_width * cos_theta));
    }

    void UpdateWithCenterLineHelper(
        const std::function<double(double, double)>
            &get_distance_to_path_boundary,
        const std::vector<std::vector<double>> &clamped_path_boundary_buffers,
        const StatesType &xs,
        std::vector<Vec2d> *normals,
        std::vector<std::vector<double>> *dynamic_buffer,
        std::vector<std::vector<double>> *to_path_boundary_dists,
        std::vector<std::vector<double>> *gains,
        std::vector<std::pair<int, int>> *index_pairs,
        std::vector<double> *alphas,
        int *effective_index) {
        const int buffer_count = static_cast<int>(to_path_boundary_dists->size());
        const auto &rac_alphas = center_line_helper_->alphas();
        const auto &rac_s_l_list = center_line_helper_->s_l_list();
        const auto &rac_normals = center_line_helper_->normals();
        const auto &rac_index_pairs = center_line_helper_->index_pairs();
        *effective_index = horizon_;
        for (int k = 0; k < horizon_; ++k) {
            const FrenetCoordinate sl = rac_s_l_list[k];
            const Vec2d &normal = rac_normals[k];
            const std::pair<int, int> &index_pair = rac_index_pairs[k];
            const double alpha = rac_alphas[k];
            if (index_pair.second >= path_boundary_size_) {
                *effective_index = k;
                break;
            }

            (*normals)[k] = normal;
            (*index_pairs)[k] = index_pair;
            (*alphas)[k] = alpha;

            // 中心线插值点
            Vec2d center_foot;
            if (alpha < 0.0) {
                center_foot = path_points_[index_pair.first];
            } else if (alpha > 1.0) {
                center_foot = path_points_[index_pair.second];
            } else {
                center_foot = Lerp(path_points_[index_pair.first],
                                path_points_[index_pair.second], alpha);
            }

            // 车道内侧方向（normal 指向左）
            const Vec2d inward_dir = left_ ? (-normal) : normal;

            // 记录该步 k 的最危险 inner/outer
            double best_inner_pen = std::numeric_limits<double>::infinity();
            int    best_inner_j   = -1;
            GradArrowInfo best_inner_info =
                std::make_tuple(std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                Vec2d(0.0, 0.0), Vec2d(0.0, 0.0));

            double best_outer_pen = std::numeric_limits<double>::infinity();
            int    best_outer_j   = -1;
            GradArrowInfo best_outer_info =
                std::make_tuple(std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                Vec2d(0.0, 0.0), Vec2d(0.0, 0.0));

            for (int i = 0; i < buffer_count; ++i) {
                if (alpha < 0.0) {
                    (*dynamic_buffer)[i][k] =
                        clamped_path_boundary_buffers[i][index_pair.first];
                    (*to_path_boundary_dists)[i][k] =
                        get_distance_to_path_boundary(
                            path_boundary_dists_[i][index_pair.first], sl.l);
                    (*gains)[i][k] =
                        ref_gains_[i][index_pair.first] * cascade_gains_[i];

                } else if (alpha > 1.0) {
                    (*dynamic_buffer)[i][k] =
                        clamped_path_boundary_buffers[i][index_pair.second];
                    (*to_path_boundary_dists)[i][k] =
                        get_distance_to_path_boundary(
                            path_boundary_dists_[i][index_pair.second], sl.l);
                    (*gains)[i][k] =
                        ref_gains_[i][index_pair.second] * cascade_gains_[i];
                } else {
                    (*dynamic_buffer)[i][k] = Lerp(
                        clamped_path_boundary_buffers[i][index_pair.first],
                        clamped_path_boundary_buffers[i][index_pair.second],
                        alpha);
                    const double boundary_dist =
                        Lerp(path_boundary_dists_[i][index_pair.first],
                             path_boundary_dists_[i][index_pair.second], alpha);
                    (*to_path_boundary_dists)[i][k] =
                        get_distance_to_path_boundary(boundary_dist, sl.l);
                    (*gains)[i][k] =
                        ref_gains_[i][index_pair.first] * cascade_gains_[i];
                }

                // 计算 penetration（越小越危险；负值表示侵入）
                const double buffer_j   = (*dynamic_buffer)[i][k];
                const double penetration = (*to_path_boundary_dists)[i][k] - buffer_j;

                // 该层级 i 的边界垂足（在中心线法向方向上偏移）
                double boundary_dist_at_alpha = 0.0;
                if (alpha < 0.0) {
                    boundary_dist_at_alpha = path_boundary_dists_[i][index_pair.first];
                } else if (alpha > 1.0) {
                    boundary_dist_at_alpha = path_boundary_dists_[i][index_pair.second];
                } else {
                    boundary_dist_at_alpha = Lerp(
                        path_boundary_dists_[i][index_pair.first],
                        path_boundary_dists_[i][index_pair.second], alpha);
                }

                Vec2d boundary_foot{0.0, 0.0};
                if (left_) {

                  boundary_foot =
                      center_foot + normal * (boundary_dist_at_alpha - buffer_j);
                } else {
                  boundary_foot =
                      center_foot + (-normal) * (boundary_dist_at_alpha - buffer_j);
                }

                if ((i % 2) == 0) {  // outer
                    if (penetration < best_outer_pen) {
                        best_outer_pen = penetration;
                        best_outer_j   = i;
                        best_outer_info = std::make_tuple(
                            penetration, buffer_j, boundary_foot, inward_dir);
                    }
                } else {  // inner
                    if (penetration < best_inner_pen) {
                        best_inner_pen = penetration;
                        best_inner_j   = i;
                        best_inner_info = std::make_tuple(
                            penetration, buffer_j, boundary_foot, inward_dir);
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

    const FrenetFrame &GetPath() const {
        if (center_line_helper_ != nullptr) {
            return center_line_helper_->path();
        } else {
            XCHECK_NOTNULL(path_);
            return *path_;
        }
    }

    void Update(
        const std::function<Vec2d(const StatesType &, int)> &get_pos_at_step,
        const std::function<double(double, double)>
            &get_distance_to_path_boundary,
        const std::vector<std::vector<double>> &clamped_path_boundary_buffers,
        const StatesType &xs,
        std::vector<Vec2d> *normals,
        std::vector<std::vector<double>> *dynamic_buffer,
        std::vector<std::vector<double>> *to_path_boundary_dists,
        std::vector<std::vector<double>> *gains,
        std::vector<std::pair<int, int>> *index_pairs,
        std::vector<double> *alphas,
        int *effective_index) {
        const size_t to_path_boundary_dist_size = to_path_boundary_dists->size();
        const int buffer_count = static_cast<int>(to_path_boundary_dist_size);
        *effective_index = horizon_;

        const auto &path = GetPath();
        thread_local std::vector<Vec2d> xys_local;
        thread_local std::vector<FrenetCoordinate> sls_local;
        thread_local std::vector<Vec2d> normals_local;
        thread_local std::vector<int> indices_local;
        thread_local std::vector<double> alphas_local;
        xys_local.resize(horizon_);
        sls_local.resize(horizon_);
        normals_local.resize(horizon_);
        indices_local.resize(horizon_);
        alphas_local.resize(horizon_);
        for (int k = 0; k < horizon_; ++k) {
            const Vec2d xy = get_pos_at_step(xs, k);
            xys_local[k] = xy;
        }
        path.XYToSLBatch(xys_local, &sls_local, &normals_local,
                            &indices_local, &alphas_local);

        const auto& raw_indices = path.raw_indices();

        for (int k = 0; k < horizon_; ++k) {
            const auto& sl = sls_local[k];
            const auto& normal = normals_local[k];
            const int index = indices_local[k];
            // If index is invalid (e.g. -1 from BVH), handle it or skip. 
            // The original code implicitely assumed valid return or didn't check.
            // But frenet_frame batch might return -1. 
            // In FrenetFrame::XYToSL (batch), we usually get a valid index if within range. 
            // However, let's assume valid for now to match logic structure, or better, protect access.
            
            std::pair<int, int> index_pair;
            if ((index >= 0) && ((index + 1) < raw_indices.size())) {
                 index_pair = {raw_indices[index], raw_indices[index + 1]};
            } else {
                 // Fallback or error handling if index is out of bounds
                 // For now, if invalid, maybe we should consider it effective_index break?
                 // Or keep 0,0.
                 index_pair = {0, 0}; 
            }
            
            const auto& alpha = alphas_local[k];

            if (index_pair.second >= path_boundary_size_) {
                *effective_index = k;
                break;
            }

            (*normals)[k] = normal;
            (*index_pairs)[k] = index_pair;
            (*alphas)[k] = alpha;

            // 中心线插值点（用于构造边界垂足）
            Vec2d center_foot;
            if (alpha < 0.0) {
                center_foot = path_points_[index_pair.first];
            } else if (alpha > 1.0) {
                center_foot = path_points_[index_pair.second];
            } else {
                center_foot = Lerp(path_points_[index_pair.first],
                                path_points_[index_pair.second], alpha);
            }
            // 车道内侧方向（normal 指向左）
            const Vec2d inward_dir = left_ ? (-normal) : normal;

            // 记录该步 k 的最危险 inner/outer
            double best_inner_pen = std::numeric_limits<double>::infinity();
            int    best_inner_j   = -1;
            GradArrowInfo best_inner_info =
                std::make_tuple(std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                Vec2d(0.0, 0.0), Vec2d(0.0, 0.0));

            double best_outer_pen = std::numeric_limits<double>::infinity();
            int    best_outer_j   = -1;
            GradArrowInfo best_outer_info =
                std::make_tuple(std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                Vec2d(0.0, 0.0), Vec2d(0.0, 0.0));

            for (int i = 0; i < buffer_count; ++i) {
                if (alpha < 0.0) {
                    (*dynamic_buffer)[i][k] =
                        clamped_path_boundary_buffers[i][index_pair.first];
                    (*to_path_boundary_dists)[i][k] =
                        get_distance_to_path_boundary(
                            path_boundary_dists_[i][index_pair.first], sl.l);
                    (*gains)[i][k] =
                        ref_gains_[i][index_pair.first] * cascade_gains_[i];

                } else if (alpha > 1.0) {
                    (*dynamic_buffer)[i][k] =
                        clamped_path_boundary_buffers[i][index_pair.second];
                    (*to_path_boundary_dists)[i][k] =
                        get_distance_to_path_boundary(
                            path_boundary_dists_[i][index_pair.second], sl.l);
                    (*gains)[i][k] =
                        ref_gains_[i][index_pair.second] * cascade_gains_[i];
                } else {
                    (*dynamic_buffer)[i][k] = Lerp(
                        clamped_path_boundary_buffers[i][index_pair.first],
                        clamped_path_boundary_buffers[i][index_pair.second],
                        alpha);
                    const double boundary_dist =
                        Lerp(path_boundary_dists_[i][index_pair.first],
                             path_boundary_dists_[i][index_pair.second], alpha);
                    (*to_path_boundary_dists)[i][k] =
                        get_distance_to_path_boundary(boundary_dist, sl.l);
                    (*gains)[i][k] =
                        ref_gains_[i][index_pair.first] * cascade_gains_[i];
                }

                // penetration（d - buffer）
                const double buffer_j   = (*dynamic_buffer)[i][k];
                const double penetration = (*to_path_boundary_dists)[i][k] - buffer_j;

                // 该层级 i 的边界垂足（在中心线法向方向上偏移）
                double boundary_dist_at_alpha = 0.0;
                if (alpha < 0.0) {
                    boundary_dist_at_alpha = path_boundary_dists_[i][index_pair.first];
                } else if (alpha > 1.0) {
                    boundary_dist_at_alpha = path_boundary_dists_[i][index_pair.second];
                } else {
                    boundary_dist_at_alpha = Lerp(
                        path_boundary_dists_[i][index_pair.first],
                        path_boundary_dists_[i][index_pair.second], alpha);
                }

                Vec2d boundary_foot{0.0, 0.0};
                if (left_) {
                  boundary_foot =
                      center_foot + normal * (boundary_dist_at_alpha - buffer_j);
                } else {
                  boundary_foot = center_foot +
                                  (-normal) * (boundary_dist_at_alpha - buffer_j);
                }

                if ((i % 2) == 0) { // outer
                  if (penetration < best_outer_pen) {
                    best_outer_pen = penetration;
                    best_outer_j = i;
                    best_outer_info = std::make_tuple(
                        penetration, buffer_j, boundary_foot, inward_dir);
                  }
                } else { // inner
                  if (penetration < best_inner_pen) {
                    best_inner_pen = penetration;
                    best_inner_j = i;
                    best_inner_info = std::make_tuple(
                        penetration, buffer_j, boundary_foot, inward_dir);
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

    void AddEdgePointDGDx(
        DGDxType *dgdx,
        double d_corner,
        double dist_to_rac,
        double sin_theta,
        double cos_theta,
        double half_width,
        double corner_dynamic_buffer,
        const std::vector<double> &path_boundary_dists,
        const std::vector<double> &clamped_path_boundary_buffers,
        const std::pair<int, int> &corner_index_pair,
        double corner_alpha,
        const Vec2d &corner_normal,
        double gain,
        double point_gain) const {
        Vec2d d_delta;
        if (!left_) {
            d_delta[0] = (-dist_to_rac * sin_theta) + (half_width * cos_theta);
            d_delta[1] = (dist_to_rac * cos_theta) + (half_width * sin_theta);
        } else {
            d_delta[0] = (-dist_to_rac * sin_theta) - (half_width * cos_theta);
            d_delta[1] = (dist_to_rac * cos_theta) - (half_width * sin_theta);
        }
        if (d_corner < corner_dynamic_buffer) {
            const double d_penetration = d_corner - corner_dynamic_buffer;
            const Vec2d segment = path_points_[corner_index_pair.second] -
                                  path_points_[corner_index_pair.first];
            const double d0 = path_boundary_dists[corner_index_pair.first];
            const double d1 = path_boundary_dists[corner_index_pair.second];
            double d_buffer = 0.0;
            if ((corner_alpha >= 0.0) && (corner_alpha <= 1.0)) {
                d_buffer =
                    clamped_path_boundary_buffers[corner_index_pair.second] -
                    clamped_path_boundary_buffers[corner_index_pair.first];
            }
            const double sign = left_ ? -1.0 : 1.0;
            const double final_gain = Cost<PROB>::scale() * gain * point_gain;
            if ((corner_alpha < 0.0) || (corner_alpha > 1.0)) {
                (*dgdx).template segment<2>(0) += final_gain * d_penetration *
                                                  sign *
                                                  corner_normal.transpose();
                (*dgdx)[2] += final_gain * d_penetration * sign *
                              corner_normal.dot(d_delta);
            } else {
                const Vec2d vec =
                    ((d1 - d0 - d_buffer) * segment / segment.squaredNorm()) +
                    (sign * corner_normal);
                (*dgdx).template segment<2>(0) +=
                    final_gain * d_penetration *
                    (((d1 - d0 - d_buffer) * segment.transpose() /
                         segment.squaredNorm()) +
                     (sign * corner_normal.transpose()));
                (*dgdx)[2] += final_gain * d_penetration * vec.dot(d_delta);
            }
        }
    }

    void AddEdgePointDDGDxDx(
        DDGDxDxType *ddgdxdx,
        double d_corner,
        double dist_to_rac,
        double sin_theta,
        double cos_theta,
        double half_width,
        double corner_dynamic_buffer,
        const std::vector<double> &path_boundary_dists,
        const std::vector<double> &clamped_path_boundary_buffers,
        const std::pair<int, int> &corner_index_pair,
        double corner_alpha,
        const Vec2d &corner_normal,
        double gain,
        double point_gain) const {
        Vec2d d_delta, dd_delta;
        if (!left_) {
            d_delta[0] = (-dist_to_rac * sin_theta) + (half_width * cos_theta);
            d_delta[1] = (dist_to_rac * cos_theta) + (half_width * sin_theta);
            dd_delta[0] = (-dist_to_rac * cos_theta) - (half_width * sin_theta);
            dd_delta[1] = (-dist_to_rac * sin_theta) + (half_width * cos_theta);
        } else {
            d_delta[0] = (-dist_to_rac * sin_theta) - (half_width * cos_theta);
            d_delta[1] = (dist_to_rac * cos_theta) - (half_width * sin_theta);
            dd_delta[0] = (-dist_to_rac * cos_theta) + (half_width * sin_theta);
            dd_delta[1] = (-dist_to_rac * sin_theta) - (half_width * cos_theta);
        }
        if (d_corner < corner_dynamic_buffer) {
            const double d_penetration = d_corner - corner_dynamic_buffer;
            const Vec2d segment = path_points_[corner_index_pair.second] -
                                  path_points_[corner_index_pair.first];
            const double d0 = path_boundary_dists[corner_index_pair.first];
            const double d1 = path_boundary_dists[corner_index_pair.second];
            double d_buffer = 0.0;
            if ((corner_alpha >= 0.0) && (corner_alpha <= 1.0)) {
                d_buffer =
                    clamped_path_boundary_buffers[corner_index_pair.second] -
                    clamped_path_boundary_buffers[corner_index_pair.first];
            }
            const double sign = left_ ? -1.0 : 1.0;
            const double final_gain = Cost<PROB>::scale() * gain * point_gain;
            if (using_hessian_approximate_) {
                if ((corner_alpha < 0.0) || (corner_alpha > 1.0)) {
                    (*ddgdxdx).template block<2, 2>(PROB::kStateXIndex,
                                                    PROB::kStateXIndex) +=
                        final_gain * corner_normal * corner_normal.transpose();
                    (*ddgdxdx).template block<2, 1>(PROB::kStateXIndex,
                                                    PROB::kStateThetaIndex) +=
                        final_gain * corner_normal * corner_normal.dot(d_delta);
                    (*ddgdxdx).template block<1, 2>(PROB::kStateThetaIndex,
                                                    PROB::kStateXIndex) +=
                        final_gain * corner_normal.transpose() *
                        corner_normal.dot(d_delta);
                    (*ddgdxdx)(PROB::kStateThetaIndex,
                               PROB::kStateThetaIndex) +=
                        final_gain * (Sqr(corner_normal.dot(d_delta)));
                } else {
                    const Vec2d vec =
                        ((d1 - d0 - d_buffer) * segment / segment.squaredNorm()) +
                        (sign * corner_normal);
                    (*ddgdxdx).template block<2, 2>(PROB::kStateXIndex,
                                                    PROB::kStateXIndex) +=
                        final_gain * vec * vec.transpose();
                    (*ddgdxdx).template block<2, 1>(PROB::kStateXIndex,
                                                    PROB::kStateThetaIndex) +=
                        final_gain * vec * vec.dot(d_delta);
                    (*ddgdxdx).template block<1, 2>(PROB::kStateThetaIndex,
                                                    PROB::kStateXIndex) +=
                        final_gain * vec.transpose() * vec.dot(d_delta);
                    (*ddgdxdx)(PROB::kStateThetaIndex,
                               PROB::kStateThetaIndex) +=
                        final_gain * (Sqr(vec.dot(d_delta)));
                }

            } else {
                if ((corner_alpha < 0.0) || (corner_alpha > 1.0)) {
                    (*ddgdxdx).template block<2, 2>(PROB::kStateXIndex,
                                                    PROB::kStateXIndex) +=
                        final_gain * corner_normal * corner_normal.transpose();
                    (*ddgdxdx).template block<2, 1>(PROB::kStateXIndex,
                                                    PROB::kStateThetaIndex) +=
                        final_gain * corner_normal * corner_normal.dot(d_delta);
                    (*ddgdxdx).template block<1, 2>(PROB::kStateThetaIndex,
                                                    PROB::kStateXIndex) +=
                        final_gain * corner_normal.transpose() *
                        corner_normal.dot(d_delta);
                    (*ddgdxdx)(PROB::kStateThetaIndex,
                               PROB::kStateThetaIndex) +=
                        final_gain *
                        (Sqr(corner_normal.dot(d_delta)) +
                         (d_penetration * sign * corner_normal.dot(dd_delta)));
                } else {
                    const Vec2d vec =
                        ((d1 - d0 - d_buffer) * segment / segment.squaredNorm()) +
                        (sign * corner_normal);
                    (*ddgdxdx).template block<2, 2>(PROB::kStateXIndex,
                                                    PROB::kStateXIndex) +=
                        final_gain * vec * vec.transpose();
                    (*ddgdxdx).template block<2, 1>(PROB::kStateXIndex,
                                                    PROB::kStateThetaIndex) +=
                        final_gain * vec * vec.dot(d_delta);
                    (*ddgdxdx).template block<1, 2>(PROB::kStateThetaIndex,
                                                    PROB::kStateXIndex) +=
                        final_gain * vec.transpose() * vec.dot(d_delta);
                    (*ddgdxdx)(PROB::kStateThetaIndex,
                               PROB::kStateThetaIndex) +=
                        final_gain * (Sqr(vec.dot(d_delta)) +
                                      (d_penetration * vec.dot(dd_delta)));
                }
            }
        }
    }

    int horizon_ = 0;
    VehicleGeometryParamsProto vehicle_geometry_params_;
    std::vector<Vec2d> path_points_;

    std::vector<double> l_offsets_;
    std::vector<std::vector<double>> path_boundary_dists_;
    std::vector<std::vector<double>> rear_clamped_path_boundary_buffers_;
    std::vector<std::vector<double>> front_clamped_path_boundary_buffers_;
    std::vector<std::vector<std::vector<double>>>
        mid_clamped_path_boundary_buffers_;
    int path_boundary_size_;

    bool left_ = false;
    bool using_hessian_approximate_;

    std::vector<double> mid_edges_to_center_;

    std::vector<std::vector<double>> ref_gains_;

    std::vector<double> cascade_gains_;
    std::vector<std::string> sub_names_;

    std::unique_ptr<FrenetFrame> path_;
    const CenterLineQueryHelper<PROB> *center_line_helper_;

    std::vector<double> rear_gain_;
    std::vector<double> front_gain_;

    std::vector<Vec2d> state_normals_;
    std::vector<std::pair<int, int>> state_index_pairs_;
    std::vector<double> state_alphas_;
    std::vector<std::vector<double>> state_dynamic_buffers_;

    std::vector<std::vector<double>> state_to_path_boundary_dists_;
    std::vector<std::vector<double>> state_gains_;
    int state_effective_index_ = 0;

    std::vector<Vec2d> corner_normals_;
    std::vector<std::pair<int, int>> corner_index_pairs_;
    std::vector<double> corner_alphas_;
    std::vector<std::vector<double>> corner_dynamic_buffers_;

    std::vector<std::vector<double>> corner_to_path_boundary_dists_;
    std::vector<std::vector<double>> corner_gains_;
    int corner_effective_index_;

    std::vector<std::vector<Vec2d>> mid_normals_;
    std::vector<std::vector<std::pair<int, int>>> mid_index_pairs_;
    std::vector<std::vector<double>> mid_alphas_;
    std::vector<std::vector<std::vector<double>>> mid_dynamic_buffers_;

    std::vector<std::vector<std::vector<double>>> mid_to_path_boundary_dists_;
    std::vector<std::vector<std::vector<double>>> mid_gains_;
    std::vector<int> mid_effective_index_;

    std::vector<GradArrowInfo> inner_max_penetration_and_buffer_idx;
    std::vector<GradArrowInfo> outer_max_penetration_and_buffer_idx;
};

}  // namespace planning
}  // namespace pnc_x
