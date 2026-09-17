

#include "initializer/cost_provider.h"

#include <algorithm>
#include <string>
#include <utility>

#include <absl/strings/str_cat.h>
#include <absl/strings/string_view.h>
#include <google/protobuf/descriptor.h>

#include "initializer/dp_cost_feature.h"
#include "initializer/geometry/geometry_state.h"
#include "initializer/ref_speed_table.h"
#include "initializer/reference_line_cost_feature.h"
#include "pncx_initializer_config.pb.h"

namespace pnc_x {
namespace planning {

namespace {
constexpr double kGeometryEdgeSampleStep = 0.5;
}

template <typename Config>
void CostProviderBase::BuildWeightTable(const Config &cost_config) {
    const auto *reflection = cost_config.GetReflection();
    const auto *descriptor = cost_config.GetDescriptor();
    for (const auto &feature : features_) {
        auto *feature_desc =
            descriptor->FindFieldByName(std::string(feature->name()));
        const auto &feature_conf =
            reflection->GetMessage(cost_config, feature_desc);
        const auto *feature_ref = feature_conf.GetReflection();
        std::vector<const google::protobuf::FieldDescriptor *>
            feature_weights_desc;
        feature_ref->ListFields(feature_conf, &feature_weights_desc);
        int feature_size = 0;
        for (const auto *desc : feature_weights_desc) {
            if (desc->type() !=
                google::protobuf::FieldDescriptor::TYPE_DOUBLE) {
                continue;
            }
            ++feature_size;
            cost_names_.push_back(
                absl::StrCat(feature->name(), ".", desc->name()));
            weights_.push_back(feature_ref->GetDouble(feature_conf, desc));
        }
        feature_size_.push_back(feature_size);
    }
}

void CostProviderBase::ComputeDpCost(const double start_t,
                                     const MotionForm *motion_form,
                                     absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), weights_.size())) {
        return;
    }
    auto sampled_states = motion_form->SampleStates();
    MotionEdgeInfo edge_info{
        .start_t = start_t,
        .motion_form = motion_form,
        .const_interval_states =
            std::move(sampled_states.const_interval_states),
        .equal_interval_states =
            std::move(sampled_states.equal_interval_states),
    };
    for (int i = 0, index = 0, n = features_.size(); i < n; ++i) {
        features_[i]->ComputeCost(edge_info,
                                  cost.subspan(static_cast<size_t>(index), static_cast<size_t>(feature_size_[i])));
        index += feature_size_[i];
    }
    for (size_t i = 0; i < cost.size(); ++i) {
        cost[i] = cost[i] * weights_[i];
    }
}

IgnoreTrajMap CostProviderBase::ComputeInteractiveCost(
    double start_t,
    const MotionForm *motion_form,
    const IgnoreTrajMap &ignored_trajs,
    absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), weights_.size())) {
        return ignored_trajs;
    }
    auto sampled_states = motion_form->SampleStates();
    MotionEdgeInfo edge_info{
        .start_t = start_t,
        .motion_form = motion_form,
        .const_interval_states =
            std::move(sampled_states.const_interval_states),
        .equal_interval_states =
            std::move(sampled_states.equal_interval_states),
    };
    IgnoreTrajMap new_ignored_trajs;
    for (int i = 0, index = 0, n = features_.size(); i < n; ++i) {
        if (features_[i]->name() == "dp_dynamic_collision") {
            new_ignored_trajs =
                reinterpret_cast<const DpDynamicCollisionFeatureCost *>(
                    features_[i].get())
                    ->ComputeInteractiveCost(
                        edge_info, ignored_trajs,
                        cost.subspan(static_cast<size_t>(index), static_cast<size_t>(feature_size_[i])));
        } else {
            features_[i]->ComputeCost(edge_info,
                                      cost.subspan(static_cast<size_t>(index), static_cast<size_t>(feature_size_[i])));
        }
        index += feature_size_[i];
    }
    for (int i = 0; i < cost.size(); ++i) {
        cost[i] = cost[i] * weights_[i];
    }
    return new_ignored_trajs;
}

void CostProviderBase::ComputeDpLeadingObjCost(double start_t,
                                               const MotionForm *motion_form,
                                               absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), weights_.size())) {
        return;
    }
    MotionEdgeInfo edge_info{
        .start_t = start_t,
        .motion_form = motion_form,
        .equal_interval_states = motion_form->SampleEqualIntervalStates(),
    };
    for (int i = 0, index = 0, n = features_.size(); i < n; ++i) {
        if ("dp_leading_object" == features_[i]->name() ||
            "dp_final_progress" == features_[i]->name() ||
            "dp_ref_speed" == features_[i]->name()) {
            features_[i]->ComputeCost(edge_info,
                                      cost.subspan(static_cast<size_t>(index), static_cast<size_t>(feature_size_[i])));
            for (int j = 0; j < feature_size_[i]; ++j) {
                const size_t idx = static_cast<size_t>(index + j);
                cost[idx] = cost[idx] * weights_[idx];
            }
        }
        index += feature_size_[i];
    }
}

void CostProviderBase::ComputeRefLineCost(const GeometryForm *geometry_form,
                                          bool terminating,
                                          absl::Span<double> cost) const {
    if (!XCHECK_EQ(cost.size(), weights_.size())) {
        return;
    }
    GeometryEdgeInfo geom_edge_info;
    geom_edge_info.geometry_form = geometry_form;
    geom_edge_info.terminating = terminating;
    geom_edge_info.states = geometry_form->Sample(kGeometryEdgeSampleStep);
    for (int i = 0, index = 0, n = features_.size(); i < n; ++i) {
        features_[i]->ComputeCost(geom_edge_info,
                                  cost.subspan(static_cast<size_t>(index), static_cast<size_t>(feature_size_[i])));
        index += feature_size_[i];
    }
    for (int i = 0; i < cost.size(); ++i) {
        cost[i] = cost[i] * weights_[i];
    }
}

CostProvider::CostProvider(
    const DrivePassage &drive_passage,
    const InitializerConfig &initializer_params,
    const MotionConstraintParamsProto &motion_constraint_params,
    const std::vector<double> &stop_s_vec,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const std::vector<std::string> &leading_trajs,
    const VehicleGeometryParamsProto &vehicle_geom,
    const CollisionChecker *collision_checker,
    const PathSlBoundary *path_sl,
    const RefSpeedTable *ref_speed_table,

    const InitializerSceneType init_scene_type,
    bool is_lane_change,
    double max_accumulated_s,
    bool is_post_evaluation) {
    const auto &cost_config = is_post_evaluation
                                  ? initializer_params.dp_post_cost_config()
                                  : initializer_params.dp_cost_config();
    if (cost_config.has_dp_acceleration()) {
        features_.emplace_back(std::make_unique<DpAccelerationFeatureCost>(
            motion_constraint_params, init_scene_type));
    }

    if (cost_config.has_dp_lane_boundary()) {
        features_.emplace_back(std::make_unique<DpLaneBoundaryFeatureCost>(
            path_sl, init_scene_type, vehicle_geom.width() * 0.5));
    }

    if (cost_config.has_dp_curvature()) {
        features_.emplace_back(std::make_unique<DpCurvatureFeatureCost>());
    }

    if (cost_config.has_dp_lateral_acceleration()) {
        features_.emplace_back(
            std::make_unique<DpLateralAccelerationFeatureCost>(init_scene_type,
                                                               is_lane_change));
    }

    if (cost_config.has_dp_stop_constraint()) {
        features_.emplace_back(
            std::make_unique<DpStopConstraintFeatureCost>(stop_s_vec));
    }

    if (cost_config.has_dp_ref_speed()) {
        features_.emplace_back(std::make_unique<DpRefSpeedFeatureCost>(
            ref_speed_table, init_scene_type));
    }

    if (cost_config.has_dp_dynamic_collision()) {
        features_.emplace_back(
            std::make_unique<DpDynamicCollisionFeatureCost>(collision_checker));
    }

    if (cost_config.has_dp_leading_object()) {
        features_.emplace_back(std::make_unique<DpLeadingObjectFeatureCost>(
            drive_passage, st_traj_mgr, leading_trajs,
            vehicle_geom.front_edge_to_center()));
    }

    if (cost_config.has_dp_final_progress()) {
        features_.emplace_back(std::make_unique<DpFinalProgressFeatureCost>(
            path_sl, init_scene_type, max_accumulated_s));
    }

    BuildWeightTable<InitializerConfig::DpFeatureCostConfig>(cost_config);
}

RefLineCostProvider::RefLineCostProvider(
    const SpacetimePlannerObjectTrajectories *st_planner_object_traj,
    const DrivePassage *drive_passage,
    const PathSlBoundary *path_sl,
    double geom_graph_max_accum_s,
    double relaxed_center_max_curvature,
    const InitializerConfig &initializer_params) {
    const auto &cost_config = initializer_params.ref_line_cost_config();
    if (cost_config.has_ref_line_stationary_object()) {
        features_.emplace_back(
            std::make_unique<RefLineStationaryObjectFeatureCost>(
                st_planner_object_traj, drive_passage));
    }

    if (cost_config.has_ref_line_progress()) {
        features_.emplace_back(std::make_unique<RefLineProgressFeatureCost>(
            geom_graph_max_accum_s, path_sl));
    }

    if (cost_config.has_ref_line_path_boundary()) {
        features_.emplace_back(
            std::make_unique<RefLinePathBoundaryFeatureCost>(path_sl));
    }

    if (cost_config.has_ref_line_curvature()) {
        features_.emplace_back(std::make_unique<RefLineCurvatureFeatureCost>(
            relaxed_center_max_curvature));
    }

    BuildWeightTable<InitializerConfig::RefLineFeatureCostConfig>(cost_config);
}

}  // namespace planning
}  // namespace pnc_x
