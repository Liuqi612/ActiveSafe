
#pragma once

#include <vector>

#include "async/thread_pool.h"
#include <absl/status/statusor.h>

#include "common/path_sl_boundary.h"
#include "decision/leading_groups_builder.h"
#include "pncx_initializer.pb.h"
#include "initializer/collision_checker.h"
#include "initializer/geometry/geometry_form_builder.h"
#include "initializer/geometry/geometry_graph.h"
#include "initializer/geometry/geometry_graph_cache.h"
#include "object/spacetime_trajectory_manager.h"
#include "router/drive_passage.h"
#include "pncx_trajectory_point.pb.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

struct GeometryGraphSamplingParams {
    double layer_gap;
    double lateral_resolution;
    int cross_layer_connection;
    double unit_length_lateral_span;
    bool is_lane_change;
};

struct GeometryGraphSamplingStrategy {
    std::vector<double> range_list;

    std::vector<double> layer_gap_list;

    std::vector<double> lateral_resolution_list;

    std::vector<int> cross_layer_connection_list;

    std::vector<double> unit_length_lateral_span_list;
    bool is_lane_change = false;

    GeometryGraphSamplingParams FindSamplingParams(double dist_to_start) const {
        if (!XCHECK_GT(range_list.size(), 1) ||
            !XCHECK_EQ(range_list.size(), layer_gap_list.size()) ||
            !XCHECK_EQ(range_list.size(), lateral_resolution_list.size()) ||
            !XCHECK_EQ(range_list.size(), cross_layer_connection_list.size()) ||
            !XCHECK_EQ(range_list.size(),
                       unit_length_lateral_span_list.size())) {
            return GeometryGraphSamplingParams{};
        }
        for (std::vector<double>::size_type i = 0U, n = range_list.size();
             i < n; ++i) {
            if (dist_to_start <= range_list[i]) {
                return GeometryGraphSamplingParams{
                    .layer_gap = layer_gap_list[i],
                    .lateral_resolution = lateral_resolution_list[i],
                    .cross_layer_connection = cross_layer_connection_list[i],
                    .unit_length_lateral_span =
                        unit_length_lateral_span_list[i],
                    .is_lane_change = is_lane_change};
            }
        }
        return GeometryGraphSamplingParams{
            .layer_gap = layer_gap_list.back(),
            .lateral_resolution = lateral_resolution_list.back(),
            .cross_layer_connection = cross_layer_connection_list.back(),
            .unit_length_lateral_span = unit_length_lateral_span_list.back(),
            .is_lane_change = is_lane_change};
    }
};

struct CurvyGeometryGraphBuilderInput {
    const DrivePassage *passage = nullptr;
    const PathSlBoundary *sl_boundary = nullptr;
    const std::vector<double> *stop_s_vec = nullptr;
    const std::vector<LeadingGroup> *leading_groups = nullptr;
    const SpacetimeTrajectoryManager *st_traj_mgr = nullptr;
    const ApolloTrajectoryPointProto *plan_start_point = nullptr;
    double s_from_start = 0.0;
    const VehicleGeometryParamsProto *vehicle_geom = nullptr;
    const CollisionChecker *collision_checker = nullptr;
    const GeometryGraphSamplingStrategy *sampling_params = nullptr;
    const VehicleDriveParamsProto *vehicle_drive = nullptr;
    const GeometryFormBuilder *form_builder = nullptr;
    bool lc_multiple_traj = false;
};

absl::StatusOr<XYGeometryGraph> BuildCurvyGeometryGraph(
    const CurvyGeometryGraphBuilderInput &input,
    bool retry_collision_checker,
    GeometryGraphCache *graph_cache,
    ThreadPool *thread_pool,
    InitializerDebugProto *debug_proto);

}  // namespace planning
}  // namespace pnc_x
