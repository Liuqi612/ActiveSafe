

#include "initializer/geometry/geometry_graph_builder.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <map>
#include <memory>

#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "async/parallel_for.h"
#include "common/timer.h"
#include <absl/container/flat_hash_set.h>
#include <absl/hash/hash.h>
#include <absl/status/status.h>
#include <absl/strings/str_cat.h>
#include <absl/strings/string_view.h>
#include <absl/types/span.h>
#include "common/log.h"

#include "initializer/geometry/geometry_form.h"
#include "initializer/geometry/geometry_graph_cache.h"
#include "initializer/geometry/geometry_graph_debug.h"
#include "initializer/geometry/geometry_state.h"
#include "math/frenet_common.h"
#include "math/geometry/util.h"
#include "math/piecewise_linear_function.h"
#include "math/util.h"
#include "math/vec.h"
#include "object/planner_object.h"
#include "object/spacetime_object_trajectory.h"
#include "plan/planner_defs.h"
#include "plan/planner_flags.h"
#include "util/loop_guard.h"
#include "util/status_builder.h"
#include "util/status_macros.h"
#include "util/vehicle_geometry_util.h"

namespace pnc_x {
namespace planning {

namespace {

constexpr double kAccumulatedSEpsilon = 0.1;
constexpr double kGeometryFormSamplingS = 1.0;
constexpr double kResMeter = 0.1;
constexpr double kHalfMinSamplingWidth = 0.5;
constexpr double kStartLayerMinDistFromSDCLayerS = 1.0;
constexpr double kStartLayerMultipleCurvatureVelocityThreshold = 0.5;
constexpr std::array<double, 11> kSampleCurvature = {
    0.0, -0.01, 0.01, -0.02, 0.02, -0.03, 0.03, -0.04, 0.04, -0.05, 0.05};

constexpr double kNearCurbRelaxationFactor = 1.11;
constexpr double kCurvatureRelaxRatio = 1.3;
constexpr double kInitializerMaxLKSamplingWidth = 4.0;

constexpr double kInitializerMaxLCSamplingWidth = 8.0;

struct NodeCollisionInfo {
    double max_collision_s = std::numeric_limits<double>::lowest();
    boost::optional<std::string> collision_obj_id_with_max_s = boost::none;

    std::string Debug() const {
        if (collision_obj_id_with_max_s.has_value()) {
            return absl::StrCat("Collide with obj ",
                                collision_obj_id_with_max_s.value(), " at ",
                                max_collision_s, ".");
        } else {
            return "No collision.";
        }
    }
};

struct DpEdgeInfo {
    GeometryGraphCacheKey key;
    GeometryNodeIndex start_node_index;
    GeometryNodeIndex end_node_index;
    bool truncate;
};

struct ConnectEdgesInput {
    const ApolloTrajectoryPointProto *plan_start_point;
    const GeometryFormBuilder *form_builder;
    const CollisionChecker *collision_checker;
    bool retry_collision_checker;
    const PiecewiseLinearFunction<double, double> *max_l_s;
    const PiecewiseLinearFunction<double, double> *min_l_s;
    double max_curvature;
    const std::vector<GeometryGraphSamplingParams> *ptr_layer_params;
};

std::vector<GeometryState> SampleGeometryStates(
    const GeometryForm *ptr_geometry_form) {
    double sampling_ds = kGeometryFormSamplingS;
    constexpr int kMinEvalSteps = 5;
    if (sampling_ds * kMinEvalSteps > ptr_geometry_form->length()) {
        sampling_ds = ptr_geometry_form->length() / kMinEvalSteps;
    }
    return ptr_geometry_form->Sample(sampling_ds);
}

GeometryNodeVector<GeometryNode> SampleOneLayer(
    const PathSlBoundary &sl_boundary,
    const Station &station,
    const int station_index,
    double ego_width,
    double lat_step,
    bool is_lane_change,
    int *nodes_cnt) {
    const double accum_s = station.accumulated_s();
    const double ref_center_l = sl_boundary.QueryReferenceCenterL(accum_s);
    const double outer_buffer = 0.12;
    double right_curb = -10.0;
    double left_curb = 10.0;
    absl::StatusOr<std::pair<double, double>> curb_value =
        station.QueryCurbOffsetAt(0.0);
    if (curb_value.ok()) {
        std::tie(right_curb, left_curb) = curb_value.value();
    }
    auto boundary_l = sl_boundary.QueryBoundaryL(accum_s);
    const double outer_right_l = boundary_l.first;
    const double outer_left_l = boundary_l.second;
    const auto boundary_right_l =
        std::fmax(outer_right_l, right_curb + outer_buffer);
    const auto boundary_left_l =
        std::fmin(outer_left_l, left_curb - outer_buffer);
    const double right_width =
        std::max(0.0, ref_center_l - boundary_right_l - ego_width * 0.5);
    const double left_width =
        std::max(0.0, boundary_left_l - ref_center_l - ego_width * 0.5);

    const double default_sampling_width =
        is_lane_change ? kInitializerMaxLCSamplingWidth - ego_width
                       : kInitializerMaxLKSamplingWidth - ego_width;
    XCHECK_GT(default_sampling_width, 0.0);
    const double half_default_sampling_width = 0.5 * default_sampling_width;
    int right_n = CeilToInt(std::min(right_width, half_default_sampling_width) /
                            lat_step);
    int left_n =
        CeilToInt(std::min(left_width, half_default_sampling_width) / lat_step);

    double resampled_right_lat_step = 0.0, resampled_left_lat_step = 0.0;
    if (right_n > 0) {
        resampled_right_lat_step = right_width / static_cast<double>(right_n);
        right_n = RoundToInt(right_width / resampled_right_lat_step);
    }
    if (left_n > 0) {
        resampled_left_lat_step = left_width / static_cast<double>(left_n);
        left_n = RoundToInt(left_width / resampled_left_lat_step);
    }

    GeometryNodeVector<GeometryNode> nodes_layer;
    nodes_layer.reserve(left_n + right_n + 1);
    for (int i = -right_n; i <= left_n; ++i) {
        const double lat_offset =
            ref_center_l +
            (i < 0 ? resampled_right_lat_step : resampled_left_lat_step) *
                static_cast<double>(i);
        nodes_layer.emplace_back(
            GeometryNode{.index = GeometryNodeIndex((*nodes_cnt)++),
                         .xy = station.lat_point(lat_offset),
                         .k = 0.0,
                         .station_index = station_index,
                         .lateral_offset = lat_offset,
                         .accumulated_s = accum_s,
                         .reachable = false});
    }

    return nodes_layer;
}

void ResetReachableStatus(
    std::vector<GeometryNodeVector<GeometryNode>> *ptr_nodes_layers) {
    auto &nodes_layers = *ptr_nodes_layers;

    for (int i = 1; i < nodes_layers.size(); ++i) {
        auto &nodes = nodes_layers[static_cast<std::size_t>(i)];
        for (auto &node : nodes) {
            node.reachable = false;
        }
    }
}

absl::StatusOr<GeometryNodeVector<GeometryNode>> CreateStartNodeLayer(
    const DrivePassage &passage,
    const GeometryState &plan_start_state,
    double sdc_v,
    StationIndex *ptr_next_index) {
    ASSIGN_OR_RETURN(
        const auto ego_waypoint,
        passage.QueryFrenetLonOffsetAt(plan_start_state.xy),
        _.SetPrepend() << "Cannot find frenet mapping of ego vehicle state: ");
    ASSIGN_OR_RETURN(
        const auto lat_offset,
        passage.QueryFrenetLatOffsetAt(plan_start_state.xy),
        _.SetPrepend() << "Cannot find frenet mapping of ego vehicle state: ");
    if (ego_waypoint.lon_offset >= 0.0) {
        *ptr_next_index = StationIndex(ego_waypoint.station_index.value() + 1);
    } else {
        *ptr_next_index = ego_waypoint.station_index;
    }
    GeometryNodeVector<GeometryNode> start_node_layer;
    const double accumulated_s =
        passage.station(ego_waypoint.station_index).accumulated_s() +
        ego_waypoint.lon_offset;
    const int station_index = std::max(0, ptr_next_index->value() - 1);
    start_node_layer.emplace_back(GeometryNode{.index = GeometryNodeIndex(0),
                                               .xy = plan_start_state.xy,
                                               .k = plan_start_state.k,
                                               .station_index = station_index,
                                               .lateral_offset = lat_offset,
                                               .accumulated_s = accumulated_s,
                                               .reachable = true});

    if (sdc_v < kStartLayerMultipleCurvatureVelocityThreshold) {
        start_node_layer.reserve(static_cast<int>(kSampleCurvature.size()) + 1);

        for (int i = 0; i < kSampleCurvature.size(); ++i) {
            if (kSampleCurvature[i] == plan_start_state.k) {
                continue;
            }
            const int curr_node_cnt = start_node_layer.size();
            start_node_layer.emplace_back(
                GeometryNode{.index = GeometryNodeIndex(curr_node_cnt),
                             .xy = plan_start_state.xy,
                             .k = kSampleCurvature[static_cast<std::size_t>(i)],
                             .station_index = station_index,
                             .lateral_offset = lat_offset,
                             .accumulated_s = accumulated_s,
                             .reachable = true});
        }
    }
    return start_node_layer;
}

double FindCurbBuffer(const DrivePassage &passage,
                      const Vec2d &ego_pos,
                      StationIndex next_station_idx,
                      double ego_half_width) {
    ASSIGN_OR_RETURN(const auto ego_pos_curb_offset,
                     passage.QueryCurbOffsetAt(ego_pos), 0.0);
    ASSIGN_OR_RETURN(const auto next_station_curb_offset,
                     passage.station(next_station_idx).QueryCurbOffsetAt(0.0),
                     0.0);

    const double ego_pos_curb_width =
        ego_pos_curb_offset.second - ego_pos_curb_offset.first;
    const double next_station_curb_width =
        next_station_curb_offset.second - next_station_curb_offset.first;

    const double relax_factor = ego_pos_curb_width > next_station_curb_width
                                    ? kNearCurbRelaxationFactor
                                    : 1.0;

    const double min_dist_to_curb =
        std::min(std::abs(ego_pos_curb_offset.first),
                 std::abs(ego_pos_curb_offset.second));
    return boost::algorithm::clamp(
        min_dist_to_curb - ego_half_width * relax_factor, 0.0, ego_half_width);
}

bool IsInvalidCurvature(absl::Span<const GeometryState> states,
                        double max_curvature) {
    for (const auto &state : states) {
        if (std::fabs(state.k) > max_curvature) {
            return true;
        }
    }
    return false;
}

bool IsEdgeConvergingToLaneCenter(double cur_offset, double future_offset) {
    if (cur_offset > 0.0 && future_offset < cur_offset + kResMeter &&
        future_offset > -kResMeter) {
        return true;
    }
    if (cur_offset <= 0.0 && future_offset > cur_offset - kResMeter &&
        future_offset < kResMeter) {
        return true;
    }

    if (std::fabs(future_offset) < kDefaultHalfLaneWidth &&
        std::fabs(cur_offset) < kDefaultHalfLaneWidth) {
        return true;
    }
    return false;
}

bool IsEdgeHittingCurb(absl::Span<const GeometryState> states,
                       const PiecewiseLinearFunction<double, double> &max_l_s,
                       const PiecewiseLinearFunction<double, double> &min_l_s) {
    for (int i = 0; i < states.size(); ++i) {
        const auto &state = states[static_cast<std::size_t>(i)];

        if (state.l >= max_l_s(state.accumulated_s) ||
            state.l <= min_l_s(state.accumulated_s)) {
            return true;
        }
    }
    return false;
}

bool IsEdgeCollidingWithStaticObject(absl::Span<const GeometryState> states,
                                     const CollisionChecker &collision_checker,
                                     int *ptr_collide_state_idx,
                                     std::string *ptr_obj_id) {
    XCHECK_GT(states.size(), 0);
    CollisionInfo collision_info;
    collision_checker.CheckCollisionWithStationaryObjects(states,
                                                          &collision_info);
    if (!collision_info.collision_objects.empty()) {
        const auto min_it = std::min_element(
            collision_info.collision_objects.begin(),
            collision_info.collision_objects.end(),
            [](const CollisionInfo::ObjectCollision &lhs,
               const CollisionInfo::ObjectCollision &rhs) {
                if (lhs.time == rhs.time)
                    return lhs.traj->traj_id() < rhs.traj->traj_id();
                return lhs.time < rhs.time;
            });
        *ptr_collide_state_idx = min_it->time;
        *ptr_obj_id = std::string(min_it->traj->object_id());
        return true;
    }
    return false;
}

bool PassPreGeometryFormBuildCheck(const GeometryGraphSamplingParams &params,
                                   const GeometryNode &this_node,
                                   const GeometryNode &next_node,
                                   double layer_idx,
                                   GeometryEdgeCache *edge_info) {
    const double dl = next_node.lateral_offset - this_node.lateral_offset;
    const double ds = next_node.accumulated_s - this_node.accumulated_s;
    if (ds < kAccumulatedSEpsilon) {
        edge_info->connection_result = ConnectionResult::OMIT_TOO_SHORT;
        return false;
    }
    if (std::fabs(dl / ds) >= params.unit_length_lateral_span) {
        edge_info->connection_result = ConnectionResult::OMIT_LATERAL_OFFSET;
        return false;
    }

    if (layer_idx != 0.0 && params.is_lane_change &&
        (!IsEdgeConvergingToLaneCenter(this_node.lateral_offset,
                                       next_node.lateral_offset))) {
        edge_info->connection_result =
            ConnectionResult::OMIT_NOT_CONVERGE_TO_CENTER;
        return false;
    }
    return true;
}

absl::StatusOr<PiecewiseLinearGeometry> BuildGeometryForm(
    const GeometryFormBuilder &form_builder,
    const GeometryNode &this_node,
    const GeometryNode &next_node,
    const ApolloTrajectoryPointProto &plan_start_point,
    int layer_idx) {
    const DrivePassageSamplePoint next_point = {
        next_node.xy, next_node.lateral_offset, next_node.accumulated_s,
        next_node.station_index};
    if (layer_idx == 0) {
        double dk = plan_start_point.path_point().lambda();
        if (this_node.k != plan_start_point.path_point().kappa()) {
            dk = 0.0;
        }
        const GeometryState start_state = {
            .xy = this_node.xy,
            .h = plan_start_point.path_point().theta(),
            .k = this_node.k,
            .dk = dk};
        const auto &quintic_spiral_or =
            form_builder.BuildQuinticSpiralGeometry(start_state, next_point);
        if (quintic_spiral_or.ok()) {
            return *quintic_spiral_or;
        } else {
            const auto &cubic_spiral_or =
                form_builder.BuildCubicSpiralGeometry(start_state, next_point);
            if (cubic_spiral_or.ok()) {
                return *cubic_spiral_or;
            }
        }
    }

    const DrivePassageSamplePoint this_point = {
        this_node.xy, this_node.lateral_offset, this_node.accumulated_s,
        this_node.station_index};
    return form_builder.BuildLateralQuinticPolyGeometry(this_point, next_point);
}

bool PassCurvatureAndCurbCheck(
    const std::vector<GeometryState> &states,
    const double max_curvature,
    const PiecewiseLinearFunction<double, double> &max_l_s,
    const PiecewiseLinearFunction<double, double> &min_l_s,
    GeometryEdgeCache *edge_info) {
    if (IsInvalidCurvature(states, max_curvature)) {
        edge_info->connection_result = ConnectionResult::FAIL_INVALID_CURVATURE;
        return false;
    }
    if (IsEdgeHittingCurb(states, max_l_s, min_l_s)) {
        edge_info->connection_result = ConnectionResult::FAIL_CURB_COLLISION;
        return false;
    }
    return true;
}

ConnectionResult CheckCollision(const CollisionChecker &collision_checker,
                                const std::vector<GeometryState> &states,
                                NodeCollisionInfo *ptr_node_collision_info,
                                int *colliding_index,
                                std::string *obj_id) {
    if (IsEdgeCollidingWithStaticObject(states, collision_checker,
                                        colliding_index, obj_id)) {
        const double last_s = states[static_cast<std::size_t>(*colliding_index)].accumulated_s;

        if (last_s >= ptr_node_collision_info->max_collision_s) {
            ptr_node_collision_info->max_collision_s = last_s;
            ptr_node_collision_info->collision_obj_id_with_max_s = *obj_id;
        }
        constexpr double kMinTruncatedEdgeLength = 1.0;
        if ((*colliding_index > 1) &&
            (states[*colliding_index].accumulated_s - states[0].accumulated_s >
                kMinTruncatedEdgeLength)) {
            return ConnectionResult::COLLIDE_TRUNCATE;
        } else {
            return ConnectionResult::COLLIDE_NO_EDGE;
        }
    }

    return ConnectionResult::SUCCESS;
}

void UpdateEdgeInfoInCache(const GeometryGraphCacheKey &key,
                           const ConnectionResult &new_result,
                           const std::vector<GeometryState> &states,
                           const GeometryNode &this_node,
                           int colliding_index,
                           const GeometryNode &next_node,
                           const std::string &obj_id,
                           std::vector<DpEdgeInfo> *this_node_outgoing_edges,
                           GeometryGraphCache *graph_cache) {
    if (new_result == ConnectionResult::SUCCESS) {
        graph_cache->UpdateConnectionResult(key, new_result);
        this_node_outgoing_edges->emplace_back(DpEdgeInfo{
            .key = key,
            .start_node_index = this_node.index,
            .end_node_index = next_node.index,
            .truncate = false,
        });
        return;
    }

    const double collision_s = states[static_cast<std::size_t>(colliding_index)].accumulated_s;

    if (new_result == ConnectionResult::COLLIDE_TRUNCATE) {
        std::vector<GeometryState> truncated_states(
            states.begin(), states.begin() + colliding_index);
        std::unique_ptr<GeometryForm> ptr_geometry_form_truncated =
            std::make_unique<PiecewiseLinearGeometry>(truncated_states);
        const auto &final_state = truncated_states.back();
        graph_cache->UpdateTruncatedGeometryForm(
            key, final_state, std::move(ptr_geometry_form_truncated), obj_id,
            collision_s);
        this_node_outgoing_edges->emplace_back(DpEdgeInfo{
            .key = key,
            .start_node_index = this_node.index,
            .end_node_index = static_cast<GeometryNodeIndex>(-1),
            .truncate = true,
        });
        return;
    }

    if (new_result == ConnectionResult::COLLIDE_NO_EDGE) {
        graph_cache->UpdateConnectionResult(key, new_result);
        graph_cache->UpdateCollisionInfo(key, obj_id, collision_s);
        return;
    }
}

std::pair<double, std::string> GetLeadingObjectAccumulatedS(
    const DrivePassage &passage,
    const LeadingGroup &leading_group,
    const SpacetimeTrajectoryManager &st_traj_mgr) {
    double min_accumulated_s = std::numeric_limits<double>::max();
    std::string obj_id;
    for (const auto &pair : leading_group) {
        const auto &traj_id = pair.first;
        const auto *traj_ptr = st_traj_mgr.FindTrajectoryById(traj_id);
        // AD_LINFO(PP) << "trajectory ptr: " << traj_ptr;

        if (!traj_ptr->is_stationary()) continue;

        ASSIGN_OR_CONTINUE(const auto frenet_box,
                           passage.QueryFrenetBoxAt(
                               traj_ptr->planner_object().bounding_box()));
        if (min_accumulated_s > frenet_box.s_min) {
            min_accumulated_s = frenet_box.s_min;
            obj_id = traj_ptr->planner_object().id();
        }
    }
    return {min_accumulated_s, obj_id};
}

void FillTruncateEdgeInfo(const std::vector<GeometryState> &states,
                          int colliding_index,
                          const std::string &obj_id,
                          GeometryEdgeCache *edge_info) {
    std::vector<GeometryState> truncated_states(
        states.begin(), states.begin() + colliding_index);
    edge_info->collision_accum_s.push_back(
        states[static_cast<std::size_t>(colliding_index)].accumulated_s);
    edge_info->collision_ids.push_back(obj_id);
    edge_info->ptr_geometry_form_truncated =
        std::make_unique<PiecewiseLinearGeometry>(truncated_states);
    edge_info->final_state = truncated_states.back();
}

absl::Status SampleGeometryNodesWithVaryingResolutionStrategy(
    const DrivePassage &passage,
    const PathSlBoundary &sl_boundary,
    const GeometryGraphSamplingStrategy &sampling_params,
    double max_sampling_accum_s,
    double constraint_stop_sampling_s,
    double s_from_start,
    double ego_v,
    double ego_width,
    double ego_accum_s,
    int start_index,
    std::vector<GeometryNodeVector<GeometryNode>> *ptr_nodes_layers,
    std::vector<GeometryGraphSamplingParams> *ptr_layer_params,
    int *total_nodes) {
    if (!XCHECK_GT(ptr_nodes_layers->size(), 0) ||
        !XCHECK_GT(ptr_nodes_layers->at(0).size(), 0)) {
        return absl::InternalError("input error");
    }

    const int num_stations = passage.stations().size();
    if (!XCHECK_GT(num_stations, start_index)) {
        return absl::InternalError("input error");
    }

    const int nodes_cnt_before = *total_nodes;
    int &nodes_cnt = *total_nodes;

    const double s_from_start_with_diff = s_from_start - ego_accum_s;
    const auto start_param = sampling_params.FindSamplingParams(0.0);
    double accum_s = passage.station(StationIndex(start_index)).accumulated_s();
    double route_s = s_from_start_with_diff + accum_s;
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while ((start_index + 1 < num_stations) &&
           (accum_s < constraint_stop_sampling_s) &&
           ((route_s < start_param.layer_gap - kResMeter) ||
            (accum_s - ego_accum_s < kStartLayerMinDistFromSDCLayerS)) &&
           loop_guard) {
        accum_s = passage.station(StationIndex(++start_index)).accumulated_s();
        route_s = s_from_start_with_diff + accum_s;
    }

    double prev_layer_s = ego_accum_s;
    for (int cur_index = start_index; cur_index < num_stations; ++cur_index) {
        const double dist2start =
            passage.station(StationIndex(cur_index)).accumulated_s() -
            passage.station(StationIndex(start_index)).accumulated_s();

        if (dist2start > max_sampling_accum_s) break;

        const auto cur_param = sampling_params.FindSamplingParams(dist2start);
        const auto &station = passage.station(StationIndex(cur_index));
        if (station.accumulated_s() - prev_layer_s >=
            cur_param.layer_gap - kResMeter) {
            ptr_nodes_layers->emplace_back(
                SampleOneLayer(sl_boundary, station, cur_index, ego_width,
                               cur_param.lateral_resolution,
                               cur_param.is_lane_change, &nodes_cnt));
            ptr_layer_params->push_back(cur_param);
            prev_layer_s = station.accumulated_s();

            if (station.accumulated_s() >=
                constraint_stop_sampling_s + cur_param.layer_gap) {
                break;
            }
        }
    }

    if (nodes_cnt - nodes_cnt_before == 0) {
        return absl::InternalError(
            "Zero nodes sampled! Path boundary width < sdc_width?");
    }

    return absl::OkStatus();
}

void ExpandGeometryEdgesFromLayerNode(
    const ApolloTrajectoryPointProto &plan_start_point,
    const CollisionChecker &collision_checker,
    bool retry_collision_checker,
    const GeometryGraphSamplingParams &params,
    const GeometryFormBuilder &form_builder,
    const PiecewiseLinearFunction<double, double> &max_l_s,
    const PiecewiseLinearFunction<double, double> &min_l_s,
    int layer_idx,
    int this_layer_node_idx,
    double max_curvature,
    const std::vector<GeometryNodeVector<GeometryNode>> &nodes_layers,
    std::vector<DpEdgeInfo> *ptr_edge_container,
    NodeCollisionInfo *ptr_node_collision_info,
    GeometryGraphCache *graph_cache) {
    auto &this_node_outgoing_edges = *ptr_edge_container;
    const auto &this_node =
        nodes_layers[static_cast<std::size_t>(layer_idx)][GeometryNodeIndex(this_layer_node_idx)];
    const int total_layer_num = static_cast<int>(nodes_layers.size());

    ptr_node_collision_info->max_collision_s =
        std::numeric_limits<double>::lowest();
    ptr_node_collision_info->collision_obj_id_with_max_s = boost::none;

    const int cross_layer_connection_num = std::min(
        params.cross_layer_connection, total_layer_num - 1 - layer_idx);
    for (int i = 1; i <= cross_layer_connection_num; ++i) {
        const int to_be_connected_layer_index = layer_idx + i;

        for (const auto &next_node :
             nodes_layers[static_cast<std::size_t>(to_be_connected_layer_index)]) {
            GeometryGraphCacheKey key(this_node, next_node);
            const auto connection_result_or =
                graph_cache->GetConnectionResult(key);
            if (!connection_result_or.ok()) {
                GeometryEdgeCache edge_info;

                if (FLAGS_planner_initializer_debug_level >= 1) {
                    edge_info.debug_info = EdgeDebugInfo{
                        .start_layer_idx = layer_idx,
                        .end_layer_idx = to_be_connected_layer_index,
                        .start_station_idx = this_node.station_index,
                        .end_station_idx = next_node.station_index,
                    };
                }

                if (!PassPreGeometryFormBuildCheck(params, this_node, next_node,
                                                   static_cast<double>(layer_idx), &edge_info)) {
                    graph_cache->AddEdge(key, std::move(edge_info));
                    continue;
                }

                auto poly_form_or =
                    BuildGeometryForm(form_builder, this_node, next_node,
                                      plan_start_point, layer_idx);
                if (!poly_form_or.ok()) {
                    edge_info.connection_result =
                        ConnectionResult::FAIL_NO_POLY;
                    graph_cache->AddEdge(key, std::move(edge_info));
                    continue;
                }
                std::unique_ptr<GeometryForm> ptr_geometry_form =
                    std::make_unique<PiecewiseLinearGeometry>(
                        std::move(poly_form_or).value());
                const auto states =
                    SampleGeometryStates(ptr_geometry_form.get());

                const double relaxed_allowed_curvature =
                    layer_idx == 0 && i == 1 ? 2.0 * max_curvature
                                             : max_curvature;
                if (!PassCurvatureAndCurbCheck(states,
                                               relaxed_allowed_curvature,
                                               max_l_s, min_l_s, &edge_info)) {
                    graph_cache->AddEdge(key, std::move(edge_info));
                    continue;
                }

                edge_info.ptr_geometry_form = std::move(ptr_geometry_form);
                int colliding_index = 0;
                std::string obj_id;
                edge_info.connection_result = CheckCollision(
                    collision_checker, states, ptr_node_collision_info,
                    &colliding_index, &obj_id);
                const auto &result = edge_info.connection_result;
                if (result == ConnectionResult::COLLIDE_TRUNCATE) {
                    FillTruncateEdgeInfo(states, colliding_index, obj_id,
                                         &edge_info);
                    if (graph_cache->AddEdge(key, std::move(edge_info))) {
                        this_node_outgoing_edges.emplace_back(
                            DpEdgeInfo{.key = key,
                                       .start_node_index = this_node.index,
                                       .end_node_index =
                                           static_cast<GeometryNodeIndex>(-1),
                                       .truncate = true});
                    }
                } else if (result == ConnectionResult::SUCCESS) {
                    if (graph_cache->AddEdge(key, std::move(edge_info))) {
                        this_node_outgoing_edges.push_back(
                            DpEdgeInfo{.key = key,
                                       .start_node_index = this_node.index,
                                       .end_node_index = next_node.index,
                                       .truncate = false});
                    }
                } else if (result == ConnectionResult::COLLIDE_NO_EDGE) {
                    edge_info.collision_accum_s.push_back(
                        states[static_cast<std::size_t>(colliding_index)].accumulated_s);
                    edge_info.collision_ids.push_back(obj_id);
                    graph_cache->AddEdge(key, std::move(edge_info));
                }
            } else {
                const auto &connection_result = *connection_result_or;

                if (connection_result == ConnectionResult::SUCCESS) {
                    this_node_outgoing_edges.push_back(
                        DpEdgeInfo{.key = key,
                                   .start_node_index = this_node.index,
                                   .end_node_index = next_node.index,
                                   .truncate = false});
                    continue;
                }

                if (!retry_collision_checker &&
                    connection_result == ConnectionResult::COLLIDE_TRUNCATE) {
                    this_node_outgoing_edges.emplace_back(DpEdgeInfo{
                        .key = key,
                        .start_node_index = this_node.index,
                        .end_node_index = static_cast<GeometryNodeIndex>(-1),
                        .truncate = true});
                    auto info = *graph_cache->GetCollisionInfo(key);
                    auto collision_accum_s = info.first;
                    auto collision_id = info.second;
                    if (collision_accum_s >=
                        ptr_node_collision_info->max_collision_s) {
                        ptr_node_collision_info->max_collision_s =
                            collision_accum_s;
                        ptr_node_collision_info->collision_obj_id_with_max_s =
                            collision_id;
                    }
                    continue;
                }

                if (retry_collision_checker &&
                    (connection_result == ConnectionResult::COLLIDE_TRUNCATE ||
                     connection_result == ConnectionResult::COLLIDE_NO_EDGE)) {
                    ASSIGN_OR_DIE(const auto geom_form,
                                  graph_cache->GetFullGeometryForm(key));
                    const auto states = SampleGeometryStates(geom_form);
                    int colliding_index = 0;
                    std::string obj_id;
                    const ConnectionResult new_result = CheckCollision(
                        collision_checker, states, ptr_node_collision_info,
                        &colliding_index, &obj_id);
                    UpdateEdgeInfoInCache(key, new_result, states, this_node,
                                          colliding_index, next_node, obj_id,
                                          &this_node_outgoing_edges,
                                          graph_cache);
                }
            }
        }
    }
}

void AddResampleNodes(
    const DrivePassage &drive_passage,
    std::vector<GeometryNodeVector<GeometryNode>> *ptr_nodes_layers,
    int *total_nodes,
    GeometryGraphCache *graph_cache) {
    auto &nodes_layers = *ptr_nodes_layers;
    if (!XCHECK_GE(nodes_layers.size(), 2)) {
        return;
    }
    std::vector<ResampleReason> resample_result(
        nodes_layers.size() - 1, ResampleReason::NOT_INITIALIZED);
    for (int i = 1, n = nodes_layers.size(); i < n; ++i) {
        double max_reachable_l = std::numeric_limits<double>::lowest();
        double min_reachable_l = std::numeric_limits<double>::max();
        double original_max_l = std::numeric_limits<double>::lowest();
        double original_min_l = std::numeric_limits<double>::max();
        int n_reachable = 0;
        for (const auto &node : nodes_layers[static_cast<std::size_t>(i)]) {
            if (node.reachable) {
                n_reachable++;

                max_reachable_l =
                    std::max(max_reachable_l, node.lateral_offset);
                min_reachable_l =
                    std::min(min_reachable_l, node.lateral_offset);
            }
            original_max_l = std::max(original_max_l, node.lateral_offset);
            original_min_l = std::min(original_min_l, node.lateral_offset);
        }
        const int n_unreachable =
            nodes_layers[static_cast<std::size_t>(i)].size() - n_reachable;
        if (n_unreachable == 0) {
            resample_result[static_cast<std::size_t>(i - 1)] = ResampleReason::NR_ALL_REACHABLE;
            continue;
        }
        if (n_reachable == 0) {
            resample_result[static_cast<std::size_t>(i - 1)] = ResampleReason::NR_ZERO_REACHABLE;
            continue;
        }
        if (max_reachable_l < min_reachable_l) {
            resample_result[static_cast<std::size_t>(i - 1)] = ResampleReason::NR_INVALID_RANGE;
            continue;
        }
        double avg_step =
            std::fmax(0.1, (original_max_l - original_min_l) /
                               std::max(1,
                                        nodes_layers[static_cast<std::size_t>(i)]
                                                .size() -
                                            1));
        double max_len = original_max_l - max_reachable_l;
        double min_len = min_reachable_l - original_min_l;
        double extra_len =
            std::fmin(max_len + min_len, 5.2 * kHalfMinSamplingWidth);
        double max_extra_len = extra_len * max_len / (max_len + min_len);
        double min_extra_len = extra_len * min_len / (max_len + min_len);
        max_extra_len = (FloorToInt(max_extra_len / avg_step) + 0.5) * avg_step;
        min_extra_len = (FloorToInt(min_extra_len / avg_step) + 0.5) * avg_step;
        max_reachable_l += std::fmin(max_extra_len, max_len);
        min_reachable_l -= std::fmin(min_extra_len, min_len);

        const double resample_lat_step =
            (max_reachable_l - min_reachable_l) / static_cast<double>(n_unreachable + 1);
        resample_result[static_cast<std::size_t>(i - 1)] = ResampleReason::RESAMPLED;
        const double accum_s = nodes_layers[static_cast<std::size_t>(i)].front().accumulated_s;
        const int station_index = nodes_layers[static_cast<std::size_t>(i)].front().station_index;
        const auto &station =
            drive_passage.station(StationIndex(station_index));
        for (int count = 0; count < n_unreachable; ++count) {
            const double lateral_offset =
                min_reachable_l + static_cast<double>(count + 1) * resample_lat_step;
            nodes_layers[static_cast<std::size_t>(i)].push_back(GeometryNode{
                .index = GeometryNodeIndex((*total_nodes)++),
                .xy = station.lat_point(lateral_offset),
                .k = 0.0,
                .station_index = station_index,
                .lateral_offset = lateral_offset,
                .accumulated_s = accum_s,
                .reachable = false,
                .resampled = true,
            });
        }
    }
    graph_cache->AddResampleReasons(resample_result);
}

void SetEdgeEndNodesReachable(
    const GeometryNodeVector<std::vector<DpEdgeInfo>> &outgoing_edges,
    int layer_index,
    std::vector<GeometryNodeVector<GeometryNode>> *ptr_nodes_layers) {
    auto &nodes_layers = *ptr_nodes_layers;
    absl::flat_hash_set<GeometryNodeIndex> reachable_nodes;
    for (const auto &node : nodes_layers[static_cast<std::size_t>(layer_index)]) {
        for (const auto &edge : outgoing_edges[node.index]) {
            if (edge.end_node_index != static_cast<GeometryNodeIndex>(-1)) {
                reachable_nodes.insert(edge.end_node_index);
            }
        }
    }

    for (int i = layer_index + 1; i < nodes_layers.size(); ++i) {
        for (auto &node : nodes_layers[static_cast<std::size_t>(i)]) {
            if (reachable_nodes.contains(node.index)) {
                node.reachable = true;
            }
        }
    }
}

absl::Status ConnectEdges(
    const ConnectEdgesInput &connect_edges_input,
    int nodes_cnt,
    std::vector<GeometryNodeVector<GeometryNode>> *ptr_nodes_layers,
    GeometryNodeVector<std::vector<DpEdgeInfo>> *ptr_outgoing_edges,
    GeometryNodeVector<NodeCollisionInfo> *ptr_node_collision_infos,
    ThreadPool *thread_pool,
    GeometryGraphCache *graph_cache) {
    const auto &plan_start_point = *connect_edges_input.plan_start_point;
    const auto &form_builder = *connect_edges_input.form_builder;
    const auto &collision_checker = *connect_edges_input.collision_checker;
    const bool retry_collision_checker =
        connect_edges_input.retry_collision_checker;
    const auto &layer_params = *connect_edges_input.ptr_layer_params;
    const auto &max_l_s = *connect_edges_input.max_l_s;
    const auto &min_l_s = *connect_edges_input.min_l_s;
    graph_cache->reset_debug();

    auto &nodes_layers = *ptr_nodes_layers;
    auto &outgoing_edges = *ptr_outgoing_edges;
    auto &node_collision_infos = *ptr_node_collision_infos;
    outgoing_edges.resize(nodes_cnt);
    node_collision_infos.resize(nodes_cnt);

    auto &first_layer = nodes_layers[0];
    int count_zero_out_edge_node = 0;
    for (int this_layer_node_idx = 0; this_layer_node_idx < first_layer.size();
         this_layer_node_idx++) {
        auto &this_node = first_layer[GeometryNodeIndex(this_layer_node_idx)];
        ExpandGeometryEdgesFromLayerNode(
            plan_start_point, collision_checker, retry_collision_checker,
            layer_params[0], form_builder, max_l_s, min_l_s, 0,
            this_layer_node_idx, connect_edges_input.max_curvature,
            nodes_layers, &outgoing_edges[this_node.index],
            &node_collision_infos[this_node.index], graph_cache);
        if (outgoing_edges[this_node.index].size() > 0) {
            for (int i = this_layer_node_idx + 1; i < first_layer.size(); ++i) {
                first_layer[GeometryNodeIndex(i)].reachable = false;
            }
            break;
        }

        ++count_zero_out_edge_node;
        if (this_layer_node_idx != 0) {
            this_node.reachable = false;
        }
    }
    if (count_zero_out_edge_node == first_layer.size()) {
        return absl::NotFoundError(
            "No valid geometry edge found from the current ego state!");
    }
    SetEdgeEndNodesReachable(outgoing_edges, 0, &nodes_layers);

    for (int layer_idx = 1; layer_idx + 1 < static_cast<int>(nodes_layers.size()); ++layer_idx) {
        if (nodes_layers[static_cast<std::size_t>(layer_idx)].size() == 0) continue;

        ParallelFor(
            0, static_cast<int>(nodes_layers[static_cast<std::size_t>(layer_idx)].size()), thread_pool,
            [&](int this_layer_node_idx) {
                const auto &this_node =
                    nodes_layers[static_cast<std::size_t>(layer_idx)]
                                [GeometryNodeIndex(this_layer_node_idx)];
                if (!this_node.reachable) return;

                ExpandGeometryEdgesFromLayerNode(
                    plan_start_point, collision_checker,
                    retry_collision_checker, layer_params[layer_idx],
                    form_builder, max_l_s, min_l_s, layer_idx,
                    this_layer_node_idx, connect_edges_input.max_curvature,
                    nodes_layers, &outgoing_edges[this_node.index],
                    &node_collision_infos[this_node.index], graph_cache);
            });

        SetEdgeEndNodesReachable(outgoing_edges, layer_idx, &nodes_layers);
    }
    return absl::OkStatus();
}

}  // namespace

absl::StatusOr<XYGeometryGraph> BuildCurvyGeometryGraph(
    const CurvyGeometryGraphBuilderInput &input,
    bool retry_collision_checker,
    GeometryGraphCache *graph_cache,
    ThreadPool *thread_pool,
    InitializerDebugProto *debug_proto) {
    Timer start_time;
    // VLOG(3) << "------ BuildCurvyGeometryGraph ------";
    // if (retry_collision_checker) {
    //     VLOG(3) << "retry_collision_checker:\t true.";
    // } else {
    //     VLOG(3) << "retry_collision_checker:\t false.";
    // }

    if (!XCHECK_NOTNULL(input.passage) || !XCHECK_NOTNULL(input.sl_boundary) ||
        !XCHECK_NOTNULL(input.stop_s_vec) ||
        !XCHECK_NOTNULL(input.leading_groups) ||
        !XCHECK_NOTNULL(input.st_traj_mgr) ||
        !XCHECK_NOTNULL(input.plan_start_point) ||
        !XCHECK_NOTNULL(input.vehicle_geom) ||
        !XCHECK_NOTNULL(input.collision_checker) ||
        !XCHECK_NOTNULL(input.sampling_params) ||
        !XCHECK_NOTNULL(input.vehicle_drive) ||
        !XCHECK_NOTNULL(input.form_builder)) {
        return absl::CancelledError();
    }

    const auto &drive_passage = *input.passage;
    const auto &plan_start_point = *input.plan_start_point;
    const auto &stop_s_vec = *input.stop_s_vec;
    const auto &vehicle_geom = *input.vehicle_geom;
    const auto &sampling_params = *input.sampling_params;

    const Vec2d plan_start_point_pos =
        Vec2dFromApolloTrajectoryPointProto(plan_start_point);
    const GeometryState plan_start_state(
        {.xy = plan_start_point_pos,
         .h = plan_start_point.path_point().theta(),
         .k = plan_start_point.path_point().kappa()});
    StationIndex sdc_next_station_idx;
    ASSIGN_OR_RETURN(
        auto start_node_layer,
        CreateStartNodeLayer(drive_passage, plan_start_state,
                             plan_start_point.v(), &sdc_next_station_idx));
    const double sdc_accumulated_s = start_node_layer.front().accumulated_s;

    std::vector<GeometryNodeVector<GeometryNode>> nodes_layers;
    if (sampling_params.layer_gap_list.empty()) {
        return absl::CancelledError();
    }
    nodes_layers.reserve(static_cast<std::size_t>(CeilToInt((drive_passage.end_s() - sdc_accumulated_s) /
                                   sampling_params.layer_gap_list[0])));
    nodes_layers.push_back(std::move(start_node_layer));

    std::vector<GeometryGraphSamplingParams> layer_params;
    layer_params.push_back(sampling_params.FindSamplingParams(0.0));

    const double curb_buffer =
        FindCurbBuffer(drive_passage, plan_start_point_pos,
                       sdc_next_station_idx, 0.5 * vehicle_geom.width());

    std::vector<double> station_s, station_max_l, station_min_l;
    station_s.reserve(static_cast<std::size_t>(drive_passage.size()));
    station_max_l.reserve(static_cast<std::size_t>(drive_passage.size()));
    station_min_l.reserve(static_cast<std::size_t>(drive_passage.size()));
    for (const auto &station : drive_passage.stations()) {
        const auto station_curboffset = station.QueryCurbOffsetAt(0.0);
        if (station_curboffset.ok()) {
            station_max_l.push_back(station_curboffset->second - curb_buffer);
            station_min_l.push_back(station_curboffset->first + curb_buffer);
            station_s.push_back(station.accumulated_s());
        }
    }
    PiecewiseLinearFunction<double, double> max_l_s(station_s, station_max_l);
    PiecewiseLinearFunction<double, double> min_l_s(station_s, station_min_l);

    const double max_sampling_accum_s =
        input.form_builder->smooth_dp_sampling_acc_s();

    double leading_obj_caused_target_s = std::numeric_limits<double>::max();
    boost::optional<std::string> static_leading_id = boost::none;
    if (!input.lc_multiple_traj && (input.leading_groups->size() == 1)) {
        const auto &pair = GetLeadingObjectAccumulatedS(
            drive_passage, input.leading_groups->front(), *input.st_traj_mgr);
        const auto &nearest_leading_s = pair.first;
        const auto &nearest_leading_id = pair.second;
        static_leading_id = nearest_leading_id;

        leading_obj_caused_target_s = std::max(
            drive_passage.station(sdc_next_station_idx).accumulated_s() +
                kResMeter,
            nearest_leading_s - vehicle_geom.front_edge_to_center() -
                kInitializerMinFollowDistance);
    }

    const double stop_line_accumulated_s =
        stop_s_vec.empty() ? std::numeric_limits<double>::max()
                           : std::max(sdc_accumulated_s, stop_s_vec[0]);

    const double constraint_stop_sampling_s =
        std::min(leading_obj_caused_target_s, stop_line_accumulated_s);

    int nodes_cnt = nodes_layers.front().size();
    RETURN_IF_ERROR(SampleGeometryNodesWithVaryingResolutionStrategy(
        drive_passage, *input.sl_boundary, sampling_params,
        max_sampling_accum_s, constraint_stop_sampling_s, input.s_from_start,
        plan_start_point.v(), vehicle_geom.width(), sdc_accumulated_s,
        sdc_next_station_idx.value(), &nodes_layers, &layer_params,
        &nodes_cnt));

    GeometryNodeVector<std::vector<DpEdgeInfo>> outgoing_edges;
    GeometryNodeVector<NodeCollisionInfo> node_collision_infos;
    const double max_curvature =
        ComputeRelaxedCenterMaxCurvature(vehicle_geom, *input.vehicle_drive) *
        kCurvatureRelaxRatio;
    ConnectEdgesInput connect_edge_input{
        .plan_start_point = input.plan_start_point,
        .form_builder = input.form_builder,
        .collision_checker = input.collision_checker,
        .retry_collision_checker = retry_collision_checker,
        .max_l_s = &max_l_s,
        .min_l_s = &min_l_s,
        .max_curvature = max_curvature,
        .ptr_layer_params = &layer_params,
    };
    RETURN_IF_ERROR(ConnectEdges(connect_edge_input, nodes_cnt, &nodes_layers,
                                 &outgoing_edges, &node_collision_infos,
                                 thread_pool, graph_cache));
    // VLOG(3) << "(1) " << graph_cache->Debug();

    const int nodes_cnt_pre_resample = nodes_cnt;
    AddResampleNodes(drive_passage, &nodes_layers, &nodes_cnt, graph_cache);

    if (nodes_cnt_pre_resample != nodes_cnt) {
        // VLOG(3) << "Add " << nodes_cnt - nodes_cnt_pre_resample << " nodes.";
        outgoing_edges.clear();
        node_collision_infos.clear();
        ResetReachableStatus(&nodes_layers);
        RETURN_IF_ERROR(ConnectEdges(
            connect_edge_input, nodes_cnt, &nodes_layers, &outgoing_edges,
            &node_collision_infos, thread_pool, graph_cache));
        // VLOG(3) << "(2) " << graph_cache->Debug();
    }

    GeometryEdgeVector<GeometryEdge> edges;
    GeometryNodeVector<std::vector<GeometryEdgeIndex>> outgoing_edges_idxs;
    GeometryNodeVector<GeometryNode> blocked_nodes;
    outgoing_edges_idxs.reserve(nodes_cnt);
    int edge_idx = 0;
    for (auto &out_edges_per_node : outgoing_edges) {
        std::vector<GeometryEdgeIndex> edge_idxs_per_node;
        edge_idxs_per_node.reserve(out_edges_per_node.size());
        for (const auto &out_edge : out_edges_per_node) {
            const GeometryEdgeIndex cur_idx(edge_idx);

            if (!out_edge.truncate) {
                ASSIGN_OR_DIE(const auto ptr_geometry_form,
                              graph_cache->GetGeometryForm(out_edge.key));
                edges.push_back(GeometryEdge{.index = cur_idx,
                                             .start = out_edge.start_node_index,
                                             .end = out_edge.end_node_index,
                                             .geometry = ptr_geometry_form});
            } else {
                const auto &final_state =
                    graph_cache->GetFinalState(out_edge.key);
                ASSIGN_OR_CONTINUE(
                    const auto station_waypoint,
                    drive_passage.QueryFrenetLonOffsetAt(final_state.xy));
                GeometryNode end_node = GeometryNode{
                    .index = GeometryNodeIndex(nodes_cnt++),
                    .xy = final_state.xy,
                    .k = 0.0,
                    .station_index = station_waypoint.station_index.value(),
                    .lateral_offset = final_state.l,
                    .accumulated_s = final_state.accumulated_s,
                    .reachable = true};
                blocked_nodes.push_back(end_node);
                ASSIGN_OR_DIE(const auto ptr_geometry_form,
                              graph_cache->GetGeometryForm(out_edge.key));
                edges.push_back(GeometryEdge{.index = cur_idx,
                                             .start = out_edge.start_node_index,
                                             .end = end_node.index,
                                             .geometry = ptr_geometry_form,
                                             .truncated = true});
            }
            edge_idxs_per_node.push_back(cur_idx);
            edge_idx++;
        }
        outgoing_edges_idxs.push_back(std::move(edge_idxs_per_node));
    }
    for (int i = 0; i < blocked_nodes.size(); ++i) {
        outgoing_edges_idxs.emplace_back(std::vector<GeometryEdgeIndex>());
    }
    nodes_layers.push_back(std::move(blocked_nodes));
    // VLOG(3) << "Total edges " << edges.size();

    GeometryNodeVector<GeometryNode> nodes;
    nodes.resize(nodes_cnt);
    std::vector<std::vector<GeometryNodeIndex>> nodes_layers_idx;
    nodes_layers_idx.reserve(nodes_layers.size());
    for (int i = 0; i < static_cast<int>(nodes_layers.size()); ++i) {
        auto &nodes_layer = nodes_layers[static_cast<std::size_t>(i)];
        std::vector<GeometryNodeIndex> nodes_layer_indices;
        nodes_layer_indices.reserve(static_cast<std::size_t>(nodes_layer.size()));
        for (auto &node : nodes_layer) {
            nodes_layer_indices.push_back(node.index);
            nodes[node.index] = std::move(node);
        }
        nodes_layers_idx.push_back(std::move(nodes_layer_indices));
    }

    double max_geom_graph_len = std::numeric_limits<double>::lowest();
    for (const auto &node : nodes) {
        if (node.reachable) {
            max_geom_graph_len =
                std::max(node.accumulated_s, max_geom_graph_len);
        }
    }
    max_geom_graph_len =
        std::min(max_geom_graph_len, constraint_stop_sampling_s);
    GeometryGraphProto::EndInfo end_info;
    boost::optional<std::string> colliding_obj_id;
    double max_collision_distance = std::numeric_limits<double>::lowest();
    for (const auto &node_collision_info : node_collision_infos) {
        if (node_collision_info.collision_obj_id_with_max_s.has_value() &&
            (node_collision_info.max_collision_s > max_collision_distance) &&
            (node_collision_info.max_collision_s < constraint_stop_sampling_s)) {
            max_collision_distance = node_collision_info.max_collision_s;
            colliding_obj_id = node_collision_info.collision_obj_id_with_max_s;
        }
    }
    // VLOG(3) << "max_collision_distance: (within reachable accum_s_limit) "
    //         << max_collision_distance;
    // VLOG(3) << "stop_line_accumualted_s: " << stop_line_accumulated_s;
    // VLOG(3) << "leading obj caused: " << leading_obj_caused_target_s;
    // VLOG(3) << "reachable accumu s limit: " << constraint_stop_sampling_s;
    // VLOG(3) << "geometry_graph_len: " << max_geom_graph_len;

    const double route_s_acc_s_diff = input.s_from_start - sdc_accumulated_s;
    if (colliding_obj_id.has_value() &&
        (max_geom_graph_len <= max_collision_distance)) {
        end_info.set_end_reason(GeometryGraphProto::END_STATIC_OBJ);
        end_info.set_object_id(colliding_obj_id.value());
        // VLOG(3) << "End_info: static_obj: " << colliding_obj_id.value();

        end_info.set_end_route_s(max_collision_distance + route_s_acc_s_diff);
        end_info.set_end_accumulated_s(max_collision_distance);
    } else {
        if (max_sampling_accum_s < constraint_stop_sampling_s) {
            end_info.set_end_reason(
                GeometryGraphProto::END_REACH_MAX_SAMPLING_DIS);
            end_info.set_end_route_s(max_sampling_accum_s + route_s_acc_s_diff);
            end_info.set_end_accumulated_s(max_sampling_accum_s);
            // VLOG(3) << "End_info: max_sampling_accum_s";
        } else {
            if (leading_obj_caused_target_s < stop_line_accumulated_s) {
                end_info.set_end_reason(
                    GeometryGraphProto::END_STATIC_LEADING_OBJ);
                end_info.set_object_id(*static_leading_id);
                end_info.set_end_route_s(leading_obj_caused_target_s +
                                         route_s_acc_s_diff);
                end_info.set_end_accumulated_s(leading_obj_caused_target_s);
                // VLOG(3) << "End_info: static_leading_obj: "
                //         << *static_leading_id;
            } else {
                end_info.set_end_reason(GeometryGraphProto::END_STOP_LINE);
                end_info.set_end_route_s(stop_line_accumulated_s +
                                         route_s_acc_s_diff);
                end_info.set_end_accumulated_s(stop_line_accumulated_s);
                // VLOG(3) << "End_info: end_stop_line.";
            }
        }
    }

    if (FLAGS_planner_initializer_debug_level >= 1) {
        debug_proto->mutable_geometry_graph_debug()->Clear();
        graph_cache->ParseConnectionProcessDebugInfoToProto(
            debug_proto->mutable_geometry_graph_debug());
        graph_cache->ParseResampleReasonToProto(
            debug_proto->mutable_geometry_graph_debug());
        graph_cache->ParseCollisionInfoToProto(
            debug_proto->mutable_geometry_graph_debug());
    }
    // VLOG(3) << "BuildCurvyGraph time: " << start_time.Time();
    // VLOG(3) << "------------------------------------";
    return XYGeometryGraph(std::move(nodes), std::move(nodes_layers_idx),
                           std::move(edges), std::move(outgoing_edges_idxs),
                           std::move(end_info));
}

}  // namespace planning
}  // namespace pnc_x
