

#include "optimization/ddp/static_boundary_cost_util.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <optional>
#include <ostream>
#include <string>
#include <unordered_set>
#include <utility>

#include "container/strong_int.h"
#include <absl/status/statusor.h>
#include <absl/strings/str_cat.h>
#include <absl/strings/str_format.h>
#include <absl/types/span.h>
// #include <gflags/gflags.h>
#include "common/log.h"

#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include "pncx_aabox3d.pb.h"
#include "pncx_affine_transformation.pb.h"
#include "pncx_constraint.pb.h"
#include "maps/semantic_map_defs.h"
#include "math/frenet_common.h"
#include "math/geometry/box2d.h"
#include "math/geometry/segment2d.h"
#include "math/piecewise_linear_function.h"
#include "math/util.h"
#include "math/vec.h"
#include "optimization/problem/mfob_path_boundary_cost.h"
#include "optimization/problem/msd_static_boundary_cost.h"
#include "optimization/problem/msd_static_boundary_cost_v2.h"
#include "plan/discretized_path.h"
#include "plan/planner_defs.h"
#include "plan/planner_semantic_map_manager.h"

#include "util/occ_ddp_debug_support.h"
#include "util/occ_ddp_csv_debug_writer.h"
#include "util/min_segment_distance_problem.h"
#include "util/qtfm_segment_matcher_v2.h"
#include "util/vehicle_geometry_util.h"
#include "optimization/ddp/curve_defensive_util.h"

// DEFINE_int32(static_boundary_canvas_level, 0,
//              "Boundary points canvas verbosity level.");

// DEFINE_bool(msd_static_boundary_cost_v2, true,
//             "V2 version of msd_static_boundary_cost, the curb buffer is speed
//             " "variant.");

// DEFINE_bool(trajectory_optimizer_ignore_u_turn_right_boundary, true,
//             "Whether to ignore right boundary of u turn.");

int FLAGS_static_boundary_canvas_level = 0;
bool FLAGS_msd_static_boundary_cost_v2 = true;
bool FLAGS_trajectory_optimizer_ignore_u_turn_right_boundary = true;

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

using BgPoint = bg::model::d2::point_xy<double>;
using BgRing = bg::model::ring<BgPoint>;  // 闭合环
using BgPolygon = bg::model::polygon<BgPoint>;
using BgLinestring = bg::model::linestring<BgPoint>;

namespace pnc_x {
namespace planning {

bool FLAGS_planner_enable_occ_debug = false;

namespace optimizer {
namespace {

constexpr bool kEnableOccBoundaryCost = true;

// 使用Boost simplify算法简化点集
// 使用Douglas-Peucker算法简化轨迹，移除不必要的点
std::vector<Vec2d> SimplifyPointsUsingBoostSimplify(
    const std::vector<Vec2d> &points,
    double tolerance) {
  if (points.size() <= 2) {
    return points;
  }

  // 将Vec2d点集转换为Boost Geometry linestring
  BgLinestring linestring;
  for (const auto &point : points) {
    bg::append(linestring, BgPoint(point.x(), point.y()));
  }

  // 使用Boost simplify算法简化
  BgLinestring simplified;
  bg::simplify(linestring, simplified, tolerance);

  // 将简化后的点集转换回Vec2d
  std::vector<Vec2d> simplified_points;
  for (const auto &bg_point : simplified) {
    simplified_points.emplace_back(bg::get<0>(bg_point), bg::get<1>(bg_point));
  }

  return simplified_points;
}


const char *BoundaryTypeName(ads_x::planning::BoundaryType boundary_type) {
  switch (boundary_type) {
    case ads_x::planning::BoundaryType::GUARDRAIL:
      return "GUARDRAIL";
    case ads_x::planning::BoundaryType::FENCE:
      return "FENCE";
    case ads_x::planning::BoundaryType::WALL:
      return "WALL";
    case ads_x::planning::BoundaryType::CURB:
      return "CURB";
    case ads_x::planning::BoundaryType::OCC_VEGETATION:
      return "OCC_VEGETATION";
    case ads_x::planning::BoundaryType::UNKNOWN_BOUNDARY:
      return "UNKNOWN_BOUNDARY";
    case ads_x::planning::BoundaryType::LANELINE:
      return "LANELINE";
    case ads_x::planning::BoundaryType::CENTER:
      return "CENTER";
    case ads_x::planning::BoundaryType::CONCRETE_BARRIER:
      return "CONCRETE_BARRIER";
    case ads_x::planning::BoundaryType::CANOPY:
      return "CANOPY";
    case ads_x::planning::BoundaryType::PAVE:
      return "PAVE";
    case ads_x::planning::BoundaryType::DITCH:
      return "DITCH";
    case ads_x::planning::BoundaryType::PUNCHEON:
      return "PUNCHEON";
    case ads_x::planning::BoundaryType::VIRTUAL:
      return "VIRTUAL";
    case ads_x::planning::BoundaryType::LIDAR_UU:
      return "LIDAR_UU";
    case ads_x::planning::BoundaryType::OCC_UU:
      return "OCC_UU";
    case ads_x::planning::BoundaryType::OCC_CURB:
      return "OCC_CURB";
    case ads_x::planning::BoundaryType::OCC_CONJECTURE:
      return "OCC_CONJECTURE";
    case ads_x::planning::BoundaryType::WATERFILLED:
      return "WATERFILLED";
    case ads_x::planning::BoundaryType::CONEBARRIER:
      return "CONEBARRIER";
    default:
      return "OTHER";
  }
}

// 取 OCC polygon 外环点，并去掉闭环尾部和首点重复的那个点。
std::vector<Vec2d> ExtractOccPolygonOuterPoints(
    const senseAD::planning_pilot::BgPolygon &polygon) {
  const auto &outer = polygon.outer();
  std::vector<Vec2d> points;
  if (outer.empty()) {
    return points;
  }
  size_t point_count = outer.size();
  if (point_count >= 2) {
    const Vec2d first_pt(outer.front().x(), outer.front().y());
    const Vec2d last_pt(outer.back().x(), outer.back().y());
    if (first_pt.DistanceTo(last_pt) < 1e-3) {
      --point_count;
    }
  }
  points.reserve(point_count);
  for (size_t i = 0; i < point_count; ++i) {
    points.emplace_back(outer[i].x(), outer[i].y());
  }
  return points;
}

struct OccEdgeGeometry {
  Segment2d segment;
  double length = 0.0;
  Vec2d unit_direction;
};

// 识别细长带状 polygon 两端的封口边，避免误当成路沿 cost segment。
bool IsOccCapEdge(const std::vector<OccEdgeGeometry> &edges, int start_idx) {
  if (edges.size() < 4) {
    return false;
  }
  const int size = static_cast<int>(edges.size());
  const int prev_idx = (start_idx - 1 + size) % size;
  const int next_idx = (start_idx + 1) % size;
  const OccEdgeGeometry &prev_seg = edges[prev_idx];
  const OccEdgeGeometry &cur_seg = edges[start_idx];
  const OccEdgeGeometry &next_seg = edges[next_idx];

  if (cur_seg.length <= QtfmSegmentMatcherV2::kMinSegmentLength) {
    return false;
  }

  constexpr double kOccCapMaxLength = 1.2;
  constexpr double kOccCapNeighborLengthRatio = 2.0;
  constexpr double kOccCapNeighborParallel = 0.85;
  constexpr double kOccCapPerpendicular = 0.45;

  if (cur_seg.length > kOccCapMaxLength) {
    return false;
  }
  if (prev_seg.length < cur_seg.length * kOccCapNeighborLengthRatio ||
      next_seg.length < cur_seg.length * kOccCapNeighborLengthRatio) {
    return false;
  }

  const double neighbor_alignment =
      std::abs(prev_seg.unit_direction.Dot(next_seg.unit_direction));
  const double cur_prev_alignment =
      std::abs(cur_seg.unit_direction.Dot(prev_seg.unit_direction));
  const double cur_next_alignment =
      std::abs(cur_seg.unit_direction.Dot(next_seg.unit_direction));

  return neighbor_alignment >= kOccCapNeighborParallel &&
         cur_prev_alignment <= kOccCapPerpendicular &&
         cur_next_alignment <= kOccCapPerpendicular;
}


// 根据边界类型判断是否需要考虑后视镜间隙（仅在无高度信息时作为fallback使用）。
// 高刚性障碍物（护栏、墙体等）返回true；低矮障碍物（路沿、路面等）返回false；
// 高度不确定的类型（OCC_UU等）返回nullopt，由调用方决定默认值。
boost::optional<bool> ShouldConsiderMirrorsByBoundaryType(
    ads_x::planning::BoundaryType boundary_type) {
  switch (boundary_type) {
    case ads_x::planning::BoundaryType::GUARDRAIL:
    case ads_x::planning::BoundaryType::FENCE:
    case ads_x::planning::BoundaryType::WALL:
    case ads_x::planning::BoundaryType::CONCRETE_BARRIER:
    case ads_x::planning::BoundaryType::CANOPY:
    case ads_x::planning::BoundaryType::WATERFILLED:
      return true;
    case ads_x::planning::BoundaryType::CURB:
    case ads_x::planning::BoundaryType::OCC_CURB:
    case ads_x::planning::BoundaryType::PAVE:
    case ads_x::planning::BoundaryType::DITCH:
    case ads_x::planning::BoundaryType::PUNCHEON:
    case ads_x::planning::BoundaryType::CONEBARRIER:
    case ads_x::planning::BoundaryType::VIRTUAL:
      return false;
    default:
      return boost::none;
  }
}

bool IsRigidRoadBoundaryType(ads_x::planning::BoundaryType boundary_type) {
  switch (boundary_type) {
    case ads_x::planning::BoundaryType::GUARDRAIL:
    case ads_x::planning::BoundaryType::FENCE:
    case ads_x::planning::BoundaryType::WALL: {
      // printf("[RigidRBBoost] boundary type %s is not considered rigid.\n",
      //        BoundaryTypeName(boundary_type));
      return true;
    }
    default: {
      // printf("[RigidRBBoost] boundary type %s is not considered rigid.\n",
      //        BoundaryTypeName(boundary_type));
      return false;
    }
  }
}

// 计算弯道外侧curb段的额外防御性buffer
// 逻辑：1) 判断ODD是否使能 2) 计算curb段中点的frenet坐标
// 3) 用三点差分计算该位置的有符号曲率(signed kappa)
// 4) 判断curb是否在弯道外侧(左弯时右侧/右弯时左侧)
// 5) 根据曲率半径查表返回额外buffer
double ComputeOuterCurveExtraBuffer(
    const Segment2d &seg,
    const std::unique_ptr<BVHFrenetFrame> &ref_center_frenet,
    absl::Span<const Vec2d> ref_center_vector,
    const DiscretizedPath &ref_center_path,
    double ego_s,
    double ego_v,
    bool curve_defensive_enabled) {
    if (!curve_defensive_enabled) {
        return 0.0;
    }

    // 取curb段中点，投影到参考线获取frenet坐标
    const Vec2d mid_point = 0.5 * (seg.start() + seg.end());
    const auto sl = ref_center_frenet->XYToSL(mid_point);

    // 太靠近参考线中心的段不处理（避免误判）
    constexpr double kMinLateralOffset = 0.5;
    if (std::abs(sl.l) < kMinLateralOffset) {
        return 0.0;
    }

    // 在ref_center_vector中找到距离curb段最近的参考线点索引
    const int num_points = static_cast<int>(ref_center_vector.size());
    const auto path_point = ref_center_path.Evaluate(sl.s);
    const Vec2d ref_pos(path_point.x(), path_point.y());

    int closest_idx = 0;
    double min_dist = std::numeric_limits<double>::max();
    for (int i = 0; i < num_points; ++i) {
        const double d = ref_center_vector[i].DistanceTo(ref_pos);
        if (d < min_dist) {
            min_dist = d;
            closest_idx = i;
        }
    }

    if ((closest_idx < 1) || (closest_idx >= num_points - 1)) {
        return 0.0;
    }

    // 三点差分计算有符号曲率：kappa>0为左弯，kappa<0为右弯
    const Vec2d &p0 = ref_center_vector[closest_idx - 1];
    const Vec2d &p1 = ref_center_vector[closest_idx];
    const Vec2d &p2 = ref_center_vector[closest_idx + 1];
    const Vec2d dxy = -0.5 * p0 + 0.5 * p2;
    const Vec2d d2xy = p0 - 2.0 * p1 + p2;
    const double denom = Sqr(dxy.x()) + Sqr(dxy.y());
    if (denom < 1e-12) {
        return 0.0;
    }
    const double tmp = 1.0 / denom;
    const double signed_kappa =
        (dxy.x() * d2xy.y() - d2xy.x() * dxy.y()) * tmp * std::sqrt(tmp);

    // 弯道外侧判断：左弯(kappa>0)时l<0为外侧，右弯(kappa<0)时l>0为外侧
    const bool is_outer = ((signed_kappa > 0.0) && (sl.l < 0.0)) ||
                          ((signed_kappa < 0.0) && (sl.l > 0.0));
    if (!is_outer) {
        return 0.0;
    }

    const double abs_kappa = std::abs(signed_kappa);
    if (abs_kappa < 1e-6) {
        return 0.0;
    }
    const double roc = 1.0 / abs_kappa;  // 曲率半径
    const double buffer = GetCurveDefensiveBuffer(roc);

    // std::printf("[CurveDefensive] seg_mid=(%.2f,%.2f) s=%.2f l=%.2f "
    //            "signed_kappa=%.5f roc=%.2f is_outer=%d buffer=%.3f\n",
    //            mid_point.x(), mid_point.y(), sl.s, sl.l,
    //            signed_kappa, roc, static_cast<int>(is_outer), buffer);

    return buffer;
}

double GetRigidBoundaryOppositeVehicleBufferBoost(
    uint64_t boundary_id,
    const DrivePassage& drive_passage,
    const PathTimeCorridor* path_time_corridor,
    const Segment2d& boundary_segment,
    const ads_x::planning::RoadBoundaryType& road_boundary_type) {
    if ((path_time_corridor == nullptr) ||
        !IsRigidRoadBoundaryType(road_boundary_type.boundary_type)) {
        return 0.0;
    }
    constexpr double kMinBoundarySideOffset = 0.2;
    constexpr double kRigidBoundaryVehicleBufferBoost = 0.15;
    constexpr double kRigidBoundaryLargeVehicleBufferBoost = 0.20;
    const Vec2d middle_point =
        0.5 * (boundary_segment.start() + boundary_segment.end());
    const auto frenet_or =
        drive_passage.QueryUnboundedFrenetCoordinateAt(middle_point);
    if (!frenet_or.ok() || (std::abs(frenet_or->l) < kMinBoundarySideOffset)) {
        return 0.0;
    }
    const bool boundary_on_left = frenet_or->l > 0.0;
    const auto corridor_boundary =
        path_time_corridor->QueryBoundaryL(frenet_or->s, 0.0);
    const auto opposite_boundary_type =
        boundary_on_left ? corridor_boundary.first.type
                         : corridor_boundary.second.type;
    if ((opposite_boundary_type ==
            PathTimeCorridor::BoundaryInfo::Type::LARGE_VEHICLE) ||
        (opposite_boundary_type == PathTimeCorridor::BoundaryInfo::Type::VEHICLE)) {
        // (void)boundary_id;
        // (void)BoundaryTypeName(road_boundary_type.boundary_type);
        // std::printf(
        //     "[RigidRBBoost] boundary_id=%llu type=%s side=%s s=%.2f l=%.2f "
        //     "boost=%.2f\n",
        //     static_cast<unsigned long long>(boundary_id),
        //     BoundaryTypeName(road_boundary_type.boundary_type),
        //     boundary_on_left ? "left" : "right", frenet_or->s, frenet_or->l,
        //     kRigidBoundaryLargeVehicleBufferBoost);
    }
    if (opposite_boundary_type ==
        PathTimeCorridor::BoundaryInfo::LARGE_VEHICLE) {
        return kRigidBoundaryLargeVehicleBufferBoost;
    }
    if (opposite_boundary_type == PathTimeCorridor::BoundaryInfo::VEHICLE) {
        return kRigidBoundaryVehicleBufferBoost;
    }
    return 0.0;
}

void CollectCurbSegmentsAroundDrivePassage(
    bool consider_mirrors_by_default,
    const VehicleGeometryParamsProto &veh_geo_params,
    const TrajectoryPoint &plan_start_point,
    const DrivePassage &drive_passage,
    const std::function<std::tuple<double, double, double>(const Vec2d &)>
        &query_extra_buffer,
    const PathTimeCorridor *path_time_corridor,
    const boost::optional<double> &u_turn_middle_s,
    std::vector<MsdProblemWithBuffer::SegmentType>
        *below_mirror_curb_named_segments,
    std::vector<int> *below_mirror_curb_start_segment_ids,
    std::vector<MsdProblemWithBuffer::SegmentType>
        *above_mirror_curb_named_segments,
    std::vector<int> *above_mirror_curb_start_segment_ids,
    std::vector<MsdProblemWithBuffer::SegmentType> *uturn_right_named_segments,
    std::vector<int> *uturn_right_start_segment_ids,
    bool *uturn_curb_consider_mirrors,
    double *nearest_curb_distance,
    const std::unique_ptr<BVHFrenetFrame> &ref_center_frenet,
    absl::Span<const Vec2d> ref_center_vector,
    const DiscretizedPath &ref_center_path,
    bool curve_defensive_enabled) {
    if (!XCHECK_NOTNULL(below_mirror_curb_named_segments) ||
        !XCHECK_NOTNULL(below_mirror_curb_start_segment_ids) ||
        !XCHECK_NOTNULL(above_mirror_curb_named_segments) ||
        !XCHECK_NOTNULL(above_mirror_curb_start_segment_ids) ||
        !XCHECK_NOTNULL(uturn_right_named_segments) ||
        !XCHECK_NOTNULL(uturn_right_start_segment_ids) ||
        !XCHECK_NOTNULL(uturn_curb_consider_mirrors)) {
        return;
    }

    std::unordered_set<mapping::ElementId> curb_boundaries;
    const int last_scan_station =
        drive_passage.last_real_station_index().value();
    for (int i = 1; i < drive_passage.size(); ++i) {
        if (i > last_scan_station) {
            break;
        }
        const Vec2d p0 = drive_passage.station(StationIndex(i - 1)).xy();
        const Vec2d &p1 = drive_passage.station(StationIndex(i)).xy();
        const double search_radius =
            kMaxLateralOffset + (p1 - p0).Length() * 0.5;
        const Vec2d search_center = 0.5 * (p0 + p1);
        const std::vector<ads_x::planning::RoadBoundaryConstPtr>
            candidate_boundaries =
                drive_passage.GetRoadBoundaries(search_center, search_radius);
        for (const auto &candidate_boundary : candidate_boundaries) {
            curb_boundaries.insert(candidate_boundary->id());
        }
    }

    const auto is_on_uturn_right = [&drive_passage, &u_turn_middle_s](
                                       const Segment2d &boundary) {
        return false; // TODO:(liuyi8) If needed, implement U-turn right boundary check
        if (!u_turn_middle_s.has_value()) return false;
        const auto start_frenet_or =
            drive_passage.QueryUnboundedFrenetCoordinateAt(boundary.start());
        if (!start_frenet_or.ok()) return false;
        const auto end_frenet_or =
            drive_passage.QueryUnboundedFrenetCoordinateAt(boundary.end());
        if (!end_frenet_or.ok()) return false;
        if ((start_frenet_or->s >= *u_turn_middle_s &&
             start_frenet_or->l < 0.0) ||
            (end_frenet_or->s >= *u_turn_middle_s && end_frenet_or->l < 0.0)) {
            return true;
        }
        return false;
    };

    const bool has_mirror =
        veh_geo_params.has_left_mirror() && veh_geo_params.has_right_mirror();
    const double mirror_height_avg =
        ((veh_geo_params.left_mirror().z() -
          veh_geo_params.left_mirror().height() * 0.5) +
         (veh_geo_params.right_mirror().z() -
          veh_geo_params.right_mirror().height() * 0.5)) *
        0.5;

    above_mirror_curb_named_segments->clear();
    above_mirror_curb_start_segment_ids->clear();
    below_mirror_curb_named_segments->clear();
    below_mirror_curb_start_segment_ids->clear();
    uturn_right_named_segments->clear();
    uturn_right_start_segment_ids->clear();
    for (const auto &id : curb_boundaries) {
        ads_x::planning::RoadBoundaryConstPtr road_boundary =
            drive_passage.GetRoadBoundaryById(id);
        // TODO:(xc)
        // = psmm.FindRoadBoundaryByIdOrNull(id);
        if (road_boundary == nullptr) continue;
        const auto type_based_mirror =
            ShouldConsiderMirrorsByBoundaryType(road_boundary->type().boundary_type);
        // 高度和类型满足其中一个即考虑后视镜：
        // 有高度信息且高于后视镜，或类型推断为需要考虑后视镜
        const bool height_requires_mirror =
            road_boundary->has_height() &&
            (road_boundary->height() > mirror_height_avg);
        const bool type_requires_mirror =
            type_based_mirror.value_or(consider_mirrors_by_default);
        const bool consider_mirrors =
            has_mirror && (height_requires_mirror || type_requires_mirror);
        // std::printf("[MirrorCurb] boundary_id=%llu type=%s has_height=%d "
        //             "height=%.2f mirror_avg=%.2f type_based=%s consider_mirrors=%d\n",
        //             static_cast<unsigned long long>(road_boundary->id()),
        //             BoundaryTypeName(road_boundary->type().boundary_type),
        //             road_boundary->has_height(),
        //             road_boundary->has_height() ? road_boundary->height() : -1.0,
        //             mirror_height_avg,
        //             type_based_mirror.has_value()
        //                 ? (type_based_mirror.value() ? "true" : "false")
        //                 : "default",
        //             consider_mirrors);
        const std::vector<Vec2d> &points = road_boundary->curve_points();
        if (points.empty()) {
            continue;
        }

        const double simplify_tolerance = 0.05;  // 公差单位为米
        const std::vector<Vec2d> simplified_points =
            SimplifyPointsUsingBoostSimplify(points, simplify_tolerance);

        bool has_no_prev_segment = true;
        bool uturn_right_has_no_prev_segment = true;
        Vec2d prev = simplified_points.front();
        for (int i = 1; i < simplified_points.size(); ++i) {
            if (prev.DistanceTo(simplified_points[i]) <=
                QtfmSegmentMatcherV2::kMinSegmentLength) {
                continue;
            }

            const Segment2d cur_seg(prev, simplified_points[i]);
            double extra_buffer =
                std::min(std::get<0>(query_extra_buffer(cur_seg.start())),
                         std::get<0>(query_extra_buffer(cur_seg.end())));
            extra_buffer += GetRigidBoundaryOppositeVehicleBufferBoost(
                road_boundary->id(), drive_passage, path_time_corridor, cur_seg,
                road_boundary->type());
            // 弯道外侧防御性避让：对外侧curb段额外增加基于曲率半径的buffer
            extra_buffer += ComputeOuterCurveExtraBuffer(
                cur_seg, ref_center_frenet, ref_center_vector,
                ref_center_path, plan_start_point.s(),
                plan_start_point.v(), curve_defensive_enabled);

            const double lane_width =
                std::min(std::get<1>(query_extra_buffer(cur_seg.start())),
                         std::get<1>(query_extra_buffer(cur_seg.end())));

            const double length =
                std::min(std::get<2>(query_extra_buffer(cur_seg.start())),
                         std::get<2>(query_extra_buffer(cur_seg.end())));

            if (is_on_uturn_right(cur_seg)) {
                has_no_prev_segment = true;

                uturn_right_named_segments->push_back(
                    {absl::StrCat("id:", id), cur_seg, extra_buffer,
                     lane_width, length});
                if (uturn_right_has_no_prev_segment) {
                    uturn_right_start_segment_ids->push_back(
                        uturn_right_named_segments->size() - 1);
                    uturn_right_has_no_prev_segment = false;
                }
                *uturn_curb_consider_mirrors |= consider_mirrors;
            } else {
                uturn_right_has_no_prev_segment = true;

                consider_mirrors
                    ? above_mirror_curb_named_segments->push_back(
                          {absl::StrCat("id:", id), cur_seg,
                           extra_buffer, lane_width, length})
                    : below_mirror_curb_named_segments->push_back(
                          {absl::StrCat("id:", id), cur_seg,
                           extra_buffer, lane_width, length});
                if (has_no_prev_segment) {
                    consider_mirrors
                        ? above_mirror_curb_start_segment_ids->push_back(
                              above_mirror_curb_named_segments->size() - 1)
                        : below_mirror_curb_start_segment_ids->push_back(
                              below_mirror_curb_named_segments->size() - 1);
                    has_no_prev_segment = false;
                }
            }
            prev = simplified_points[i];
        }
    }
}

void CollectOccSegmentsFromPolygon(
    const OccDdpCsvFrameContext &csv_ctx,
    const std::vector<senseAD::planning_pilot::BgPolygon> *occ_polygons,
    const DrivePassage &drive_passage,
    const std::function<std::tuple<double, double, double>(const Vec2d &)>
        &query_extra_buffer,
    std::vector<MsdProblemWithBuffer::SegmentType> *occ_named_segments,
    std::vector<int> *occ_start_segment_ids,
    OccSegmentCollectionStats *stats) {
    // 直接把 polygon 转成 OCC 专用 static-boundary cost 可消费的 segment 集合。
    if (!XCHECK_NOTNULL(occ_named_segments) ||
        !XCHECK_NOTNULL(occ_start_segment_ids) ||
        !XCHECK_NOTNULL(stats)) {
        return;
    }
    if (occ_polygons == nullptr || occ_polygons->empty()) {
        return;
    }

    stats->polygon_count = occ_polygons->size();

    constexpr double kOccSimplifyTolerance = 0.05;
    constexpr double kOccMinAbsL = 0.3;
    constexpr double kOccMinHeadingAlignment = 0.5;  // about 60 degrees
    constexpr double kOccMaxAbsL = 3.5;
    constexpr double kOccPolygonMinLongSpan = 2.0;
    constexpr double kOccPolygonMinAspectRatio = 1.5;
    constexpr double kOccDominantAlignment = 0.9;
    constexpr double kOccDominantLengthRatio = 0.45;
    struct CachedFrenetPoint {
        bool queried = false;
        bool ok = false;
        FrenetCoordinate frenet;
    };
    struct CachedExtraBuffer {
        bool queried = false;
        std::tuple<double, double, double> value{0.0, 0.0, 0.0};
    };

    for (size_t polygon_idx = 0; polygon_idx < occ_polygons->size();
         ++polygon_idx) {
        std::vector<Vec2d> raw_outer_points =
            ExtractOccPolygonOuterPoints(occ_polygons->at(polygon_idx));
        if (raw_outer_points.size() < 3) {
            continue;
        }
        const std::string polygon_id = absl::StrCat("occ_poly_", polygon_idx);
        WriteOccDdpCsvPolygon(csv_ctx, "occ_raw_polygon", polygon_id,
                              raw_outer_points, true,
                              OccDdpCsvRejectReason::kNone);

        std::vector<Vec2d> outer_points = raw_outer_points;
        outer_points =
            SimplifyPointsUsingBoostSimplify(outer_points, kOccSimplifyTolerance);
        if (outer_points.size() < 3) {
            continue;
        }
        WriteOccDdpCsvPolygon(csv_ctx, "occ_simplified_ring", polygon_id,
                              outer_points, true,
                              OccDdpCsvRejectReason::kNone);

        bool polygon_started = false;
        int polygon_segment_count = 0;
        const int point_count = static_cast<int>(outer_points.size());
        std::vector<OccEdgeGeometry> edge_geometries;
        edge_geometries.reserve(point_count);
        for (int i = 0; i < point_count; ++i) {
            const int next_idx = (i + 1) % point_count;
            const Segment2d seg(outer_points[i], outer_points[next_idx]);
            const double seg_length = seg.length();
            edge_geometries.push_back(
                {seg,
                 seg_length,
                 seg_length > QtfmSegmentMatcherV2::kMinSegmentLength
                     ? seg.unit_direction()
                     : Vec2d(0.0, 0.0)});
        }
        std::vector<CachedFrenetPoint> point_frenet_cache(point_count);
        std::vector<CachedExtraBuffer> point_extra_buffer_cache(point_count);
        const auto get_point_frenet = [&](int point_idx) -> const CachedFrenetPoint & {
            CachedFrenetPoint &cached = point_frenet_cache[point_idx];
            if (!cached.queried) {
                cached.queried = true;
                const auto frenet_or =
                    drive_passage.QueryUnboundedFrenetCoordinateAt(
                        outer_points[point_idx]);
                if (frenet_or.ok()) {
                    cached.ok = true;
                    cached.frenet = *frenet_or;
                }
            }
            return cached;
        };
        const auto get_point_extra_buffer =
            [&](int point_idx) -> const CachedExtraBuffer & {
                CachedExtraBuffer &cached = point_extra_buffer_cache[point_idx];
                if (!cached.queried) {
                    cached.queried = true;
                    cached.value = query_extra_buffer(outer_points[point_idx]);
                }
                return cached;
            };

        bool has_polygon_frenet = false;
        bool polygon_far_lateral = true;
        for (int i = 0; i < point_count; ++i) {
            const CachedFrenetPoint &point_frenet = get_point_frenet(i);
            if (!point_frenet.ok) {
                continue;
            }
            has_polygon_frenet = true;
            if (std::abs(point_frenet.frenet.l) <= kOccMaxAbsL) {
                polygon_far_lateral = false;
                break;
            }
        }
        if (has_polygon_frenet && polygon_far_lateral) {
            ++stats->skip_polygon_far_lateral_count;
            WriteOccDdpCsvPolygon(
                csv_ctx, "occ_seg_reject", polygon_id, outer_points, true,
                OccDdpCsvRejectReason::kSkipPolygonFarLateral);
            continue;
        }

        std::vector<bool> cap_edge_mask(point_count, false);
        double max_non_cap_length = 0.0;
        int dominant_edge_idx = -1;
        for (int i = 0; i < point_count; ++i) {
            cap_edge_mask[i] = IsOccCapEdge(edge_geometries, i);
            if (cap_edge_mask[i]) {
                continue;
            }
            if (edge_geometries[i].length > max_non_cap_length) {
                max_non_cap_length = edge_geometries[i].length;
                dominant_edge_idx = i;
            }
        }
        if (dominant_edge_idx < 0 ||
            max_non_cap_length <= QtfmSegmentMatcherV2::kMinSegmentLength) {
            ++stats->skip_polygon_shape_count;
            WriteOccDdpCsvPolygon(csv_ctx, "occ_seg_reject", polygon_id,
                                  outer_points, true,
                                  OccDdpCsvRejectReason::kSkipPolygonShape);
            continue;
        }

        const Vec2d dominant_dir =
            edge_geometries[dominant_edge_idx].unit_direction;
        const Vec2d dominant_normal(-dominant_dir.y(), dominant_dir.x());
        double min_long_proj = outer_points.front().Dot(dominant_dir);
        double max_long_proj = min_long_proj;
        double min_lat_proj = outer_points.front().Dot(dominant_normal);
        double max_lat_proj = min_lat_proj;
        for (int i = 1; i < point_count; ++i) {
            const double long_proj = outer_points[i].Dot(dominant_dir);
            const double lat_proj = outer_points[i].Dot(dominant_normal);
            min_long_proj = std::min(min_long_proj, long_proj);
            max_long_proj = std::max(max_long_proj, long_proj);
            min_lat_proj = std::min(min_lat_proj, lat_proj);
            max_lat_proj = std::max(max_lat_proj, lat_proj);
        }
        const double polygon_long_span = max_long_proj - min_long_proj;
        const double polygon_lat_span = max_lat_proj - min_lat_proj;
        if (polygon_long_span < kOccPolygonMinLongSpan ||
            polygon_long_span < polygon_lat_span * kOccPolygonMinAspectRatio) {
            ++stats->skip_polygon_shape_count;
            WriteOccDdpCsvPolygon(csv_ctx, "occ_seg_reject", polygon_id,
                                  outer_points, true,
                                  OccDdpCsvRejectReason::kSkipPolygonShape);
            continue;
        }

        const double dominant_length_threshold =
            std::max(QtfmSegmentMatcherV2::kMinSegmentLength,
                     max_non_cap_length * kOccDominantLengthRatio);
        for (int i = 0; i < point_count; ++i) {
            const int next_idx = (i + 1) % point_count;
            const Segment2d &cur_seg = edge_geometries[i].segment;
            const std::string segment_id =
                absl::StrCat(polygon_id, "_seg_", i);
            if (edge_geometries[i].length <=
                QtfmSegmentMatcherV2::kMinSegmentLength) {
                ++stats->skip_short_segment_count;
                WriteOccDdpCsvSegment(csv_ctx, "occ_seg_reject", segment_id,
                                      cur_seg.start(), cur_seg.end(),
                                      OccDdpCsvRejectReason::kSkipShort);
                continue;
            }
            if (cap_edge_mask[i]) {
                ++stats->skip_cap_edge_count;
                WriteOccDdpCsvSegment(csv_ctx, "occ_seg_reject", segment_id,
                                      cur_seg.start(), cur_seg.end(),
                                      OccDdpCsvRejectReason::kSkipCap);
                continue;
            }
            if (edge_geometries[i].length < dominant_length_threshold ||
                std::abs(edge_geometries[i].unit_direction.Dot(dominant_dir)) <
                    kOccDominantAlignment) {
                ++stats->skip_dominant_edge_count;
                WriteOccDdpCsvSegment(csv_ctx, "occ_seg_reject", segment_id,
                                      cur_seg.start(), cur_seg.end(),
                                      OccDdpCsvRejectReason::kSkipDominantEdge);
                continue;
            }

            const Vec2d center = cur_seg.center();
            const auto center_frenet_or =
                drive_passage.QueryUnboundedFrenetCoordinateAt(center);
            if (!center_frenet_or.ok()) {
                ++stats->skip_cross_ref_count;
                WriteOccDdpCsvSegment(csv_ctx, "occ_seg_reject", segment_id,
                                      cur_seg.start(), cur_seg.end(),
                                      OccDdpCsvRejectReason::kSkipCross);
                continue;
            }

            const double center_l = center_frenet_or->l;
            if (std::abs(center_l) > kOccMaxAbsL) {
                ++stats->skip_far_lateral_count;
                WriteOccDdpCsvSegment(csv_ctx, "occ_seg_reject", segment_id,
                                      cur_seg.start(), cur_seg.end(),
                                      OccDdpCsvRejectReason::kSkipFarLateral);
                continue;
            }
            const CachedFrenetPoint &start_frenet = get_point_frenet(i);
            const CachedFrenetPoint &end_frenet = get_point_frenet(next_idx);
            if (!start_frenet.ok || !end_frenet.ok) {
                ++stats->skip_cross_ref_count;
                WriteOccDdpCsvSegment(csv_ctx, "occ_seg_reject", segment_id,
                                      cur_seg.start(), cur_seg.end(),
                                      OccDdpCsvRejectReason::kSkipCross);
                continue;
            }
            const double start_l = start_frenet.frenet.l;
            const double end_l = end_frenet.frenet.l;
            const bool on_left =
                start_l > kOccMinAbsL && end_l > kOccMinAbsL &&
                center_l > kOccMinAbsL;
            const bool on_right =
                start_l < -kOccMinAbsL && end_l < -kOccMinAbsL &&
                center_l < -kOccMinAbsL;
            if (!on_left && !on_right) {
                const bool cross_refline =
                    (start_l * end_l < 0.0) || (start_l * center_l < 0.0) ||
                    (end_l * center_l < 0.0);
                if (cross_refline) {
                    ++stats->skip_cross_ref_count;
                    WriteOccDdpCsvSegment(csv_ctx, "occ_seg_reject",
                                          segment_id, cur_seg.start(),
                                          cur_seg.end(),
                                          OccDdpCsvRejectReason::kSkipCross);
                } else {
                    ++stats->skip_side_ambiguous_count;
                    WriteOccDdpCsvSegment(csv_ctx, "occ_seg_reject",
                                          segment_id, cur_seg.start(),
                                          cur_seg.end(),
                                          OccDdpCsvRejectReason::kSkipSide);
                }
                continue;
            }

            const auto tangent_or =
                drive_passage.QueryTangentAtS(center_frenet_or->s);
            if (!tangent_or.ok() ||
                std::abs(edge_geometries[i].unit_direction.Dot(*tangent_or)) <
                    kOccMinHeadingAlignment) {
                ++stats->skip_heading_count;
                WriteOccDdpCsvSegment(csv_ctx, "occ_seg_reject", segment_id,
                                      cur_seg.start(), cur_seg.end(),
                                      OccDdpCsvRejectReason::kSkipHeading);
                continue;
            }

            const CachedExtraBuffer &start_extra_buffer =
                get_point_extra_buffer(i);
            const CachedExtraBuffer &end_extra_buffer =
                get_point_extra_buffer(next_idx);
            const double extra_buffer = std::min(
                std::get<0>(start_extra_buffer.value),
                std::get<0>(end_extra_buffer.value));
            const double lane_width = std::min(
                std::get<1>(start_extra_buffer.value),
                std::get<1>(end_extra_buffer.value));
            const double length =
                std::min(std::get<2>(start_extra_buffer.value),
                         std::get<2>(end_extra_buffer.value));

            if (!polygon_started) {
                occ_start_segment_ids->push_back(occ_named_segments->size());
                polygon_started = true;
                ++stats->accepted_polygon_count;
            }

            occ_named_segments->push_back(
                {absl::StrCat("occ_poly:", polygon_idx, "_seg:", i), cur_seg,
                 extra_buffer, lane_width, length});
            WriteOccDdpCsvSegment(csv_ctx, "occ_seg_accept", segment_id,
                                  cur_seg.start(), cur_seg.end(),
                                  OccDdpCsvRejectReason::kNone);
            ++polygon_segment_count;
            ++stats->accepted_segment_count;
        }

        if (polygon_started && polygon_segment_count == 0) {
            occ_start_segment_ids->pop_back();
            if (stats->accepted_polygon_count > 0) {
                --stats->accepted_polygon_count;
            }
        }
    }
}

void CollectExtendSolidLinesWithinPathBoundary(
    const VehicleGeometryParamsProto &vehicle_geometry_params,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    const ConstraintManager &constraint_manager,
    const std::vector<TrajectoryPoint> &smooth_init_traj,
    double solid_line_buffer,
    double extend_distance,
    std::vector<int> *solid_line_start_segment_ids,
    std::vector<MsdProblemWithBuffer::SegmentType> *solid_line_segments) {
    constexpr double kVehicleBoxHalfWidth = 0.2;
    const double lateral_buffer =
        kVehicleBoxHalfWidth - 0.5 * vehicle_geometry_params.width();
    std::vector<Box2d> av_boxes;
    av_boxes.reserve(smooth_init_traj.size());
    for (const auto &pt : smooth_init_traj) {
        av_boxes.push_back(ComputeAvBoxWithBuffer(pt.pos(), pt.theta(),
                                                  vehicle_geometry_params, 0.0,
                                                  lateral_buffer));
    }
    const auto has_overlap_with_solid_line =
        [&av_boxes](const std::vector<Vec2d> &points) {
            for (int i = 0; i + 1 < points.size(); ++i) {
                const Segment2d segment(points[i], points[i + 1]);
                for (const auto &box : av_boxes) {
                    if (box.HasOverlap(segment)) return true;
                }
            }
            return false;
        };

    const Vec2d start_pos = smooth_init_traj.front().pos();
    const double start_theta = smooth_init_traj.front().theta();

    solid_line_start_segment_ids->clear();
    solid_line_segments->clear();
    for (const auto &avoid_line : constraint_manager.AvoidLine()) {
        if (!avoid_line.source().has_solid_line_within_boundary()) continue;
        std::vector<Vec2d> solid_line;
        solid_line.reserve(avoid_line.xy_points().size() + 2);
        for (const auto &pt : avoid_line.xy_points()) {
            solid_line.emplace_back(pt.x(), pt.y());
        }
        if (has_overlap_with_solid_line(solid_line)) continue;

        XCHECK_GT(solid_line.size(), 1);
        const Segment2d seg1(solid_line[1], solid_line[0]);
        solid_line.insert(solid_line.begin(),
                          seg1.end() + seg1.unit_direction() * extend_distance);
        const Segment2d seg2(solid_line[solid_line.size() - 2],
                             solid_line.back());
        solid_line.insert(solid_line.end(),
                          seg2.end() + seg2.unit_direction() * extend_distance);

        bool has_no_prev_segment = true;
        Vec2d prev = solid_line.front();
        for (int i = 1; i < solid_line.size(); ++i) {
            if (prev.DistanceTo(solid_line[i]) <=
                QtfmSegmentMatcherV2::kMinSegmentLength) {
                continue;
            }
            const Segment2d line(prev, solid_line[i]);
            double extra_buffer = 0.0;
            for (const auto &circle :
                 trajectory_optimizer_vehicle_model_params.circles()) {
                const Vec2d center =
                    start_pos + Vec2d::FastUnitFromAngleN12(
                                    start_theta + circle.angle_to_axis()) *
                                    circle.dist_to_rac();
                const double dist = line.DistanceTo(center) - circle.radius();
                extra_buffer = std::min(extra_buffer, dist - solid_line_buffer);
            }
            for (const auto &circle :
                 trajectory_optimizer_vehicle_model_params.mirror_circles()) {
                const Vec2d center =
                    start_pos + Vec2d::FastUnitFromAngleN12(
                                    start_theta + circle.angle_to_axis()) *
                                    circle.dist_to_rac();
                const double dist = line.DistanceTo(center) - circle.radius();
                extra_buffer = std::min(extra_buffer, dist - solid_line_buffer);
            }

            solid_line_segments->push_back(
                {absl::StrCat("id:", avoid_line.id(), ",seg:", i), line,
                 extra_buffer});
            prev = solid_line[i];

            if (has_no_prev_segment) {
                solid_line_start_segment_ids->push_back(
                    solid_line_segments->size() - 1);
                has_no_prev_segment = false;
            }
        }
    }
}

void GeneratePathBoundariesWithRightBoundaryAfterUTurnIgnored(
    const DrivePassage &drive_passage,
    const PathSlBoundary &path_sl_boundary,
    std::vector<double> *left_dists_to_curb,
    std::vector<double> *right_dists_to_curb,
    std::vector<double> *left_dists_to_path_boundary,
    std::vector<double> *right_dists_to_path_boundary,
    std::vector<double> *left_dists_to_target_path_boundary,
    std::vector<double> *right_dists_to_target_path_boundary,
    std::vector<double> *reference_center_l_offsets,
    boost::optional<double> *uturn_middle_s) {
    bool u_turn_passed = false;
    double u_turn_start_s = 0.0;
    double u_turn_end_s = 0.0;
    for (const auto &station : drive_passage.stations()) {
        if (station.turn_type() == ads_x::planning::U_TURN) {
            if (!u_turn_passed) {
                u_turn_start_s = station.accumulated_s();
                u_turn_end_s = station.accumulated_s();
                u_turn_passed = true;
            } else {
                u_turn_end_s = station.accumulated_s();
            }
        } else if (u_turn_passed) {
            break;
        }
    }
    if (u_turn_passed) {
        *uturn_middle_s = 0.5 * (u_turn_start_s + u_turn_end_s);
    }

    constexpr double kBoundaryExtendDistOnUTurn = 20.0;
    constexpr double kEps = 1e-6;
    const auto drive_passage_size = drive_passage.stations().size();
    left_dists_to_curb->reserve(drive_passage_size);
    right_dists_to_curb->reserve(drive_passage_size);
    for (int i = 0; i < drive_passage.stations().size(); ++i) {
        const auto &station = drive_passage.stations()[StationIndex(i)];
        const auto curb_pair_or = station.QueryCurbOffsetAt(0.0);

        left_dists_to_curb->push_back(curb_pair_or->second);
        if (uturn_middle_s->has_value() &&
            (station.accumulated_s() + kEps >= **uturn_middle_s)) {
            right_dists_to_curb->push_back(-curb_pair_or->first +
                                           kBoundaryExtendDistOnUTurn);
        } else {
            right_dists_to_curb->push_back(-curb_pair_or->first);
        }
    }

    const auto path_boundary_size = path_sl_boundary.size();
    left_dists_to_path_boundary->reserve(path_boundary_size);
    left_dists_to_target_path_boundary->reserve(path_boundary_size);
    right_dists_to_path_boundary->reserve(path_boundary_size);
    right_dists_to_target_path_boundary->reserve(path_boundary_size);
    reference_center_l_offsets->reserve(path_boundary_size);
    XCHECK_GE(drive_passage.stations().size(), path_boundary_size);
    for (int i = 0; i < path_boundary_size; ++i) {
        left_dists_to_path_boundary->push_back(
            path_sl_boundary.left_l_vector()[i]);
        left_dists_to_target_path_boundary->push_back(
            path_sl_boundary.target_left_l_vector()[i]);
        if (uturn_middle_s->has_value() &&
            (drive_passage.stations()[StationIndex(i)].accumulated_s() + kEps >=
                **uturn_middle_s)) {
            right_dists_to_path_boundary->push_back(
                -path_sl_boundary.right_l_vector()[i] +
                kBoundaryExtendDistOnUTurn);
            right_dists_to_target_path_boundary->push_back(
                -path_sl_boundary.target_right_l_vector()[i]);
        } else {
            right_dists_to_path_boundary->push_back(
                -path_sl_boundary.right_l_vector()[i]);
            right_dists_to_target_path_boundary->push_back(
                -path_sl_boundary.target_right_l_vector()[i]);
        }
        reference_center_l_offsets->push_back(
            path_sl_boundary.reference_center_l_vector()[i]);
    }
}

void GeneratePathBoundaries(
    const DrivePassage &drive_passage,
    const NudgeInfos &nudge_info,
    const PathSlBoundary &path_sl_boundary,
    std::vector<double> *left_dists_to_curb,
    std::vector<double> *right_dists_to_curb,
    std::vector<double> *left_dists_to_path_boundary,
    std::vector<double> *right_dists_to_path_boundary,
    std::vector<double> *left_dists_to_target_path_boundary,
    std::vector<double> *right_dists_to_target_path_boundary,
    std::vector<double> *reference_center_l_offsets) {
    const auto drive_passage_size = drive_passage.stations().size();
    left_dists_to_curb->reserve(drive_passage_size);
    right_dists_to_curb->reserve(drive_passage_size);
    for (int i = 0; i < drive_passage.stations().size(); ++i) {
        const auto &station = drive_passage.stations()[StationIndex(i)];
        const auto curb_pair_or = station.QueryCurbOffsetAt(0.0);

        left_dists_to_curb->push_back(curb_pair_or->second);
        right_dists_to_curb->push_back(-curb_pair_or->first);
    }

    const auto path_boundary_size = path_sl_boundary.size();
    left_dists_to_path_boundary->reserve(path_boundary_size);
    left_dists_to_target_path_boundary->reserve(path_boundary_size);
    right_dists_to_path_boundary->reserve(path_boundary_size);
    right_dists_to_target_path_boundary->reserve(path_boundary_size);
    reference_center_l_offsets->reserve(path_boundary_size);
    XCHECK_GE(drive_passage.stations().size(), path_boundary_size);

    // todo::使用nudge_info
    bool nudge_left = false;
    bool nudge_right = false;

    // left/right l 要比 target left/right l 范围大
    // 意思是在nudge的时候会扩一些边界，让自车有更大的空间绕行
    for (int i = 0; i < path_boundary_size; ++i) {
        left_dists_to_path_boundary->push_back(
            path_sl_boundary.left_l_vector()[i]);
        if (nudge_left) {
            left_dists_to_target_path_boundary->push_back(
                path_sl_boundary.left_l_vector()[i]);
        } else {
            left_dists_to_target_path_boundary->push_back(
                path_sl_boundary.target_left_l_vector()[i]);
        }

        right_dists_to_path_boundary->push_back(
            -path_sl_boundary.right_l_vector()[i]);
        if (nudge_right) {
            right_dists_to_target_path_boundary->push_back(
                -path_sl_boundary.right_l_vector()[i]);
        } else {
            right_dists_to_target_path_boundary->push_back(
                -path_sl_boundary.target_right_l_vector()[i]);
        }
        reference_center_l_offsets->push_back(
            path_sl_boundary.reference_center_l_vector()[i]);
    }
}

void AddMsdStaticBoundaryCost(
    int trajectory_steps,
    std::string base_name,
    std::string source_name,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const TrajectoryPoint &plan_start_point,
    const VehicleGeometryParamsProto &veh_geo_params,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    bool consider_mirrors,
    const std::vector<int> &start_segment_ids,
    std::vector<MsdProblemWithBuffer::SegmentType> named_segments,
    std::vector<std::string> sub_names,
    std::vector<double> cascade_buffers,
    std::vector<double> cascade_gains,
    const std::unique_ptr<CenterLineQueryHelper<Mfob>> &stations_query_helper,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs) {
    constexpr double kCutoffDistExtraBuffer = 0.1;
    const double cutoff_distance =
        *std::max_element(cascade_buffers.begin(), cascade_buffers.end()) +
        0.5 * veh_geo_params.width() + kCutoffDistExtraBuffer;
    MsdProblemWithBuffer msd(std::move(named_segments), cutoff_distance,
                             start_segment_ids);

    if (FLAGS_static_boundary_canvas_level >= 1) {
    }

    std::vector<Vec2d> circle_center_offsets;
    std::vector<double> circle_radiuses;
    int circle_size = trajectory_optimizer_vehicle_model_params.circles_size();
    if (consider_mirrors) {
        circle_size +=
            trajectory_optimizer_vehicle_model_params.mirror_circles_size();
    }
    circle_center_offsets.reserve(circle_size);
    circle_radiuses.reserve(circle_size);
    for (const auto &circle :
         trajectory_optimizer_vehicle_model_params.circles()) {
        circle_center_offsets.push_back(
            Vec2d(circle.dist_to_rac() * std::cos(circle.angle_to_axis()),
                  circle.dist_to_rac() * std::sin(circle.angle_to_axis())));
        circle_radiuses.push_back(circle.radius());
    }
    if (consider_mirrors) {
        for (const auto &circle :
             trajectory_optimizer_vehicle_model_params.mirror_circles()) {
            circle_center_offsets.push_back(
                Vec2d(circle.dist_to_rac() * std::cos(circle.angle_to_axis()),
                      circle.dist_to_rac() * std::sin(circle.angle_to_axis())));
            circle_radiuses.push_back(circle.radius());
        }
    }

    costs->emplace_back(std::make_unique<MsdStaticBoundaryCost<Mfob>>(
        trajectory_steps, veh_geo_params, std::move(msd),
        stations_query_helper.get(), std::move(sub_names),
        std::move(cascade_buffers), std::move(cascade_gains),
        circle_center_offsets, circle_radiuses, trajectory_steps, true,
        "MsdStaticBoundaryCost",
        cost_weight_params.msd_static_boundary_cost_weight(),
        source_name == "solid_line"
            ? Cost<Mfob>::CostType::SOLID_LINE_MSD_STATIC_BOUNDARY
            : Cost<Mfob>::CostType::MUST_HAVE));
}

BgRing MakeCircleRingFromOffset(const Vec2d &ego_pos,
                                double ego_theta,
                                const Vec2d &offset,  // circle_center_offsets
                                double radius,
                                int num_points = 36) {
    BgRing ring;
    ring.reserve(num_points + 1);

    // 将相对偏移旋转到车辆朝向
    double x_center = ego_pos.x() + (offset.x() * std::cos(ego_theta)) -
                      (offset.y() * std::sin(ego_theta));
    double y_center = ego_pos.y() + offset.x() * std::sin(ego_theta) +
                      offset.y() * std::cos(ego_theta);

    for (int i = 0; i < num_points; ++i) {
        double theta = 2.0 * M_PI * i / num_points;
        ring.emplace_back(x_center + radius * std::cos(theta),
                          y_center + radius * std::sin(theta));
    }
    ring.push_back(ring.front());  // 闭合
    return ring;
}

std::vector<BgRing> MakeEgoCirclesFromOffsets(
    const Vec2d &ego_pos,
    double ego_theta,
    const std::vector<Vec2d> &circle_center_offsets,
    const std::vector<double> &circle_radiuses) {
    std::vector<BgRing> ego_circles;
    ego_circles.reserve(circle_center_offsets.size());
    for (size_t i = 0; i < circle_center_offsets.size(); ++i) {
        ego_circles.push_back(MakeCircleRingFromOffset(
            ego_pos, ego_theta, circle_center_offsets[i], circle_radiuses[i]));
    }
    return ego_circles;
}

/**
* V1 是“多层固定缓冲 + 固定权重”的老版本实现，cutoff 依赖车宽与最大层缓冲。
  V2 是“软/硬双层 + 速度/车道宽自适应 + 时间衰减”的升级版，
    cutoff
依赖最大圆半径与速度相关缓冲，支持更细的动态策略与侵入上限控制，并允许按来源
source_scale 调整体系权重。
 */
void AddMsdStaticBoundaryCostV2(
    int trajectory_steps,
    std::string base_name,
    const OccDdpCsvFrameContext &csv_ctx,
    std::string source_name,
    double source_scale,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const TrajectoryPoint &plan_start_point,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    bool consider_mirrors,
    const std::vector<int> &start_segment_ids,
    std::vector<MsdProblemWithBuffer::SegmentType> named_segments,
    const std::unique_ptr<CenterLineQueryHelper<Mfob>> &stations_query_helper,
    const boost::optional<double> &lane_width_curb_buffer_opt,
    const boost::optional<double> &current_curb_interval,
    const boost::optional<double> &speed_rel_hard_curb_interval,
    const double lane_width,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs) {
    XCHECK_GT(trajectory_steps, 0);
    constexpr double kOccExtraSoftBuffer = -0.15;
    constexpr double kOccExtraHardBuffer = -0.15;
    const bool is_occ_boundary = (source_name == "occ_boundary");
    const auto decay_plf = PiecewiseLinearFunctionFromProto(
        cost_weight_params.dist_to_curb_decay_params()
            .dist_to_curb_decay_scale_plf());

    const double decay_scale = 1.0;

    auto lane_width_curb_scale = PiecewiseLinearFunctionFromProto(
        cost_weight_params.lane_width_curb_scale());

    double lane_width_scale = lane_width_curb_scale(lane_width);

    auto speed_rel_hard_curb_clearance_plf =
        PiecewiseLinearFunctionFromProtoScale(
            cost_weight_params.speed_rel_hard_curb_clearance_plf(),
            lane_width_scale);

    auto speed_rel_soft_curb_clearance_plf =
        PiecewiseLinearFunctionFromProtoScale(
            cost_weight_params.speed_rel_soft_curb_clearance_plf(),
            lane_width_scale);

    if (is_occ_boundary) {
        std::vector<double> occ_soft_y =
            speed_rel_soft_curb_clearance_plf.y();
        for (double &y : occ_soft_y) {
            y += kOccExtraSoftBuffer;
        }
        speed_rel_soft_curb_clearance_plf =
            PiecewiseLinearFunction<double, double>(
                speed_rel_soft_curb_clearance_plf.x(), std::move(occ_soft_y));

        std::vector<double> occ_hard_y =
            speed_rel_hard_curb_clearance_plf.y();
        for (double &y : occ_hard_y) {
            y += kOccExtraHardBuffer;
        }
        speed_rel_hard_curb_clearance_plf =
            PiecewiseLinearFunction<double, double>(
                speed_rel_hard_curb_clearance_plf.x(), std::move(occ_hard_y));
    }

    if (current_curb_interval.has_value() &&
        lane_width_curb_buffer_opt.has_value() &&
        speed_rel_hard_curb_interval.has_value()) {
    }

    MsdStaticBoundaryCostV2<Mfob>::Layer hard_layer{
        .gain_of_weight = cost_weight_params.static_boundary_hard_gain(),
        .buffer_at_speed = speed_rel_hard_curb_clearance_plf

    };

    MsdStaticBoundaryCostV2<Mfob>::Layer soft_layer{
        .gain_of_weight = cost_weight_params.static_boundary_soft_gain(),
        .buffer_at_speed = speed_rel_soft_curb_clearance_plf

    };

    std::vector<Vec2d> circle_center_offsets;
    std::vector<double> circle_radiuses;
    int circle_size = trajectory_optimizer_vehicle_model_params.circles_size();
    if (consider_mirrors) {
        circle_size +=
            trajectory_optimizer_vehicle_model_params.mirror_circles_size();
    }
    circle_center_offsets.reserve(circle_size);
    circle_radiuses.reserve(circle_size);
    double max_circle_radius = 0.0;
    for (const auto &circle :
         trajectory_optimizer_vehicle_model_params.circles()) {
        circle_center_offsets.push_back(
            Vec2d(circle.dist_to_rac() * std::cos(circle.angle_to_axis()),
                  circle.dist_to_rac() * std::sin(circle.angle_to_axis())));
        circle_radiuses.push_back(circle.radius());
        max_circle_radius = std::max(max_circle_radius, circle.radius());
    }
    if (consider_mirrors) {
        for (const auto &circle :
             trajectory_optimizer_vehicle_model_params.mirror_circles()) {
            circle_center_offsets.push_back(
                Vec2d(circle.dist_to_rac() * std::cos(circle.angle_to_axis()),
                      circle.dist_to_rac() * std::sin(circle.angle_to_axis())));
            circle_radiuses.push_back(circle.radius());
            max_circle_radius = std::max(max_circle_radius, circle.radius());
        }
    }

#if 0
    // debug start
    Vec2d ego_pos(plan_start_point.pos().x(), plan_start_point.pos().y());
    double ego_theta = plan_start_point.theta();

    // circle_center_offsets 和 circle_radiuses 已从 trajectory_optimizer_vehicle_model_params 获取
    std::vector<BgRing> ego_circles = MakeEgoCirclesFromOffsets(
        ego_pos,
        ego_theta,
        circle_center_offsets,
        circle_radiuses
    );

    std::vector<Vec2d> mirror_circle_center_offsets;
    std::vector<double> mirror_circle_radiuses;
    for (const auto &circle :
         trajectory_optimizer_vehicle_model_params.mirror_circles()) {
        mirror_circle_center_offsets.push_back(
            Vec2d(circle.dist_to_rac() * std::cos(circle.angle_to_axis()),
                  circle.dist_to_rac() * std::sin(circle.angle_to_axis())));
        mirror_circle_radiuses.push_back(circle.radius());
        // max_circle_radius = std::max(max_circle_radius, circle.radius());
    }

    std::vector<BgRing> mirror_ego_circles = MakeEgoCirclesFromOffsets(
        ego_pos,
        ego_theta,
        mirror_circle_center_offsets,
        mirror_circle_radiuses
    );

    // 输出调试信息（距离 ego 圆最近的 curb）
    for (size_t c = 0; c < ego_circles.size(); ++c) {
        const auto& circle = ego_circles[c];
    }
    // debug end
#endif

    constexpr double kCutoffDistExtraBuffer = 0.1;
    double max_buffer = std::max(hard_layer.buffer_at_speed.y().back(),
                                 soft_layer.buffer_at_speed.y().back());
    const double cutoff_distance =
        max_buffer + max_circle_radius + kCutoffDistExtraBuffer;
    MsdProblemWithBuffer msd(std::move(named_segments), cutoff_distance,
                             start_segment_ids);

    if (FLAGS_static_boundary_canvas_level >= 1) {
    }

    const std::vector<double> decay_v_table(
        cost_weight_params.dist_to_curb_decay_params().decay_v().begin(),
        cost_weight_params.dist_to_curb_decay_params().decay_v().end());
    const std::vector<double> decay_time_table(
        cost_weight_params.dist_to_curb_decay_params().decay_time().begin(),
        cost_weight_params.dist_to_curb_decay_params().decay_time().end());
    int decay_time = 1;
    for (int i = 0; (i < decay_v_table.size()) && (i < decay_time_table.size());
         ++i) {
        if (plan_start_point.v() < decay_v_table[i]) {
            decay_time = decay_time_table[i];
            break;
        }
    }

    // 15步之后衰减到 min_decay_scale
    const double min_decay_scale = 0.1;
    decay_time = 15;
    std::vector<double> decay_scale_vec(trajectory_steps, 1.0);
    if (!is_occ_boundary) {
        for (int i = 0; i < trajectory_steps; ++i) {
            decay_scale_vec[i] = std::min(
                1.0, i / decay_time * (1.0 - min_decay_scale) +
                         min_decay_scale);
        }
    } else {
        OccDebugPrintBufferConfig({std::string(source_name),
                                   kOccExtraSoftBuffer,
                                   kOccExtraHardBuffer,
                                   cutoff_distance});
    }

    costs->emplace_back(std::make_unique<MsdStaticBoundaryCostV2<Mfob>>(
        trajectory_steps, decay_time, decay_scale_vec, std::move(msd),
        stations_query_helper.get(), csv_ctx,
        std::vector<std::string>{SoftNameString, HardNameString},
        std::vector<MsdStaticBoundaryCostV2<Mfob>::Layer>{
            std::move(soft_layer), std::move(hard_layer)},
        std::move(circle_center_offsets), std::move(circle_radiuses), true,
        cost_weight_params.max_abs_hard_penetration(),
        cost_weight_params.max_abs_soft_penetration(),

        absl::StrCat("MsdStaticBoundaryCostV2_", std::string(source_name)),
        cost_weight_params.msd_static_boundary_cost_weight() * source_scale,
        source_name == "uturn_right_curb"
            ? Cost<Mfob>::CostType::UTURN_RIGHT_CURB_MSD_STATIC_BOUNDARY_V2
            : Cost<Mfob>::CostType::CURB_MSD_STATIC_BOUNDARY_V2));
}

}  // namespace

void AddStaticBoundaryCosts(
    int trajectory_steps,
    std::string base_name,
    int frame_id,
    long long stamp_us,
    bool enable_three_point_turn,
    const TrajectoryPoint &plan_start_point,
    const DrivePassage &drive_passage,
    const NudgeInfos &nudge_info,
    const PathSlBoundary &path_sl_boundary,
    const std::vector<senseAD::planning_pilot::BgPolygon> *occ_polygon,
    const std::vector<double> &inner_path_boundary_gains,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    const std::unique_ptr<CenterLineQueryHelper<Mfob>> &stations_query_helper,
    const PathTimeCorridor *path_time_corridor,
    const boost::optional<double> &lane_width_curb_buffer_opt,
    const double lane_width,
    boost::optional<double> *extra_curb_buffer_opt,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs,
    const LaneChangeStage lc_stage,
    bool borrow_lane) {
    XCHECK_GT(trajectory_steps, 0);
    XCHECK_GT(drive_passage.stations().size(), 0);
    const OccDdpCsvFrameContext csv_ctx{frame_id, stamp_us};
    constexpr double kOccBoundaryGain = 1.0;

    std::vector<double> mid_edges_to_center = {};
    if (cost_weight_params.vehicle_model_params().enable_middle_circles()) {
        const auto &mid_edge_to_centers =
            cost_weight_params.vehicle_model_params().mid_edge_to_center();
        mid_edges_to_center.assign(mid_edge_to_centers.begin(),
                                   mid_edge_to_centers.end());
    }

    const std::vector<Vec2d> &station_points = stations_query_helper->points();
    std::vector<double> left_dists_to_curb;
    std::vector<double> right_dists_to_curb;
    std::vector<double> left_dists_to_path_boundary;
    std::vector<double> right_dists_to_path_boundary;
    std::vector<double> left_dists_to_target_path_boundary;
    std::vector<double> right_dists_to_target_path_boundary;
    std::vector<double> reference_center_l_offsets;
    boost::optional<double> uturn_middle_s = boost::none;
    if (FLAGS_trajectory_optimizer_ignore_u_turn_right_boundary &&
        enable_three_point_turn) {
        GeneratePathBoundariesWithRightBoundaryAfterUTurnIgnored(
            drive_passage, path_sl_boundary, &left_dists_to_curb,
            &right_dists_to_curb, &left_dists_to_path_boundary,
            &right_dists_to_path_boundary, &left_dists_to_target_path_boundary,
            &right_dists_to_target_path_boundary, &reference_center_l_offsets,
            &uturn_middle_s);
    } else {
        GeneratePathBoundaries(
            drive_passage, nudge_info, path_sl_boundary, &left_dists_to_curb,
            &right_dists_to_curb, &left_dists_to_path_boundary,
            &right_dists_to_path_boundary, &left_dists_to_target_path_boundary,
            &right_dists_to_target_path_boundary, &reference_center_l_offsets);
    }

    const auto &ref_center_vector =
        path_sl_boundary.reference_center_xy_vector();
    const int points_num = ref_center_vector.size();
    std::vector<PathPoint> raw_path_points;
    raw_path_points.reserve(points_num);
    for (const auto &pt : ref_center_vector) {
        raw_path_points.emplace_back();
        auto &path_point = raw_path_points.back();
        path_point.set_x(pt.x());
        path_point.set_y(pt.y());
    }
    for (int i = 0; i + 2 < points_num; ++i) {
        const Vec2d dxy =
            (-0.5 * ref_center_vector[i]) + (0.5 * ref_center_vector[i + 2]);
        const Vec2d d2xy = ref_center_vector[i] -
                           2.0 * ref_center_vector[i + 1] +
                           ref_center_vector[i + 2];
        const double tmp = 1.0 / (Sqr(dxy.x()) + Sqr(dxy.y()));
        const double kappa =
            (dxy.x() * d2xy.y() - d2xy.x() * dxy.y()) * tmp * std::sqrt(tmp);

        raw_path_points[i + 1].set_kappa(std::abs(kappa));
        raw_path_points[i + 1].set_s(
            raw_path_points[i].s() +
            ref_center_vector[i + 1].DistanceTo(ref_center_vector[i]));
    }
    XCHECK_GT(points_num, 1);
    raw_path_points[0].set_kappa(raw_path_points[1].kappa());
    raw_path_points.back().set_s(raw_path_points[points_num - 2].s() +
                                 ref_center_vector[points_num - 1].DistanceTo(
                                     ref_center_vector[points_num - 2]));

    constexpr double kMaxCurvatureLookBackDist = 5.0;
    constexpr double kLookBackDistExtensionInUTurn = 15.0;
    constexpr double kUTurnCheckMaxDist = 40.0;
    double look_back_dist = kMaxCurvatureLookBackDist;
    for (const auto &station : drive_passage.stations()) {
        if (station.turn_type() == ads_x::planning::U_TURN) {
            look_back_dist += kLookBackDistExtensionInUTurn;
            break;
        }
        if (station.accumulated_s() > kUTurnCheckMaxDist) {
            break;
        }
    }
    for (int i = points_num - 1; i >= 0; --i) {
        double max_kappa = raw_path_points[i].kappa();
        for (int j = i; j >= 0; --j) {
            if (raw_path_points[i].s() - raw_path_points[j].s() >
                look_back_dist) {
                break;
            }
            max_kappa = std::max(max_kappa, raw_path_points[j].kappa());
        }
        raw_path_points[i].set_kappa(max_kappa);
    }

    const DiscretizedPath ref_center_path(std::move(raw_path_points));
    auto ref_center_frenet_status =
        BuildBVHFrenetFrame(ref_center_vector, false);
    XCHECK(ref_center_frenet_status.ok());
    const auto ref_center_frenet = std::move(ref_center_frenet_status).value();
    const auto kappa_buffer_plf = PiecewiseLinearFunctionFromProto(
        cost_weight_params.kappa_rel_curb_clearance_buffer_plf());

    std::deque<double> input_kappa;
    for (double i = 0.1; i < 10; ++i) {
        input_kappa.push_back(std::abs(
            ref_center_path
                .Evaluate(
                    ref_center_frenet->XYToSL(plan_start_point.pos()).s +
                    0.5 * i)
                .kappa()));
    }

    XCHECK_GT(input_kappa.size(), 0);
    auto filteredKappa = [&](std::deque<double> input) {
        double sum = 0.0;
        for (const double &value : input) {
            sum += value;
        }
        return sum / input.size();
    };

    double filter_kappa = filteredKappa(input_kappa);
    input_kappa.clear();

    const auto query_curb_extra_buffer =
        [&ref_center_path, &ref_center_frenet, &kappa_buffer_plf,
         &drive_passage, &plan_start_point, &filter_kappa](
            const Vec2d &pos) -> std::tuple<double, double, double> {
        const auto sl = ref_center_frenet->XYToSL(pos);
        const auto lane_boundary_info =
            drive_passage.QueryEnclosingLaneBoundariesAtS(sl.s);
        const double lane_width = lane_boundary_info.left->lat_offset -
                                  lane_boundary_info.right->lat_offset;
        const double length = sl.s - plan_start_point.s();
        return {kappa_buffer_plf(filter_kappa), lane_width, length};
    };

    *extra_curb_buffer_opt =
        std::get<0>(query_curb_extra_buffer(plan_start_point.pos()));

    const auto av_sl_pos_or =
        drive_passage.QueryFrenetCoordinateAt(plan_start_point.pos());
    if (!av_sl_pos_or.ok()) return;
    const auto av_curb_pair_or =
        drive_passage.QueryCurbOffsetAtS(av_sl_pos_or->s);
    if (!av_curb_pair_or.ok()) return;

    const PiecewiseLinearFunction<double> speed_rel_soft_curb_clearance_plf =
        PiecewiseLinearFunctionFromProto(
            cost_weight_params.speed_rel_soft_curb_clearance_plf());

    const double vehicle_half_width = 0.5 * veh_geo_params.width();
    const auto get_hard_curb_clearance =
        [&vehicle_half_width, &av_sl_pos_or](double dist_to_curb_at_av_s) {
            constexpr double kHardCurbClearanceShift = 0.05;
            constexpr double kHardCurbClearanceMax = 0.5;
            constexpr double kHardCurbClearanceMin = 0.15;
            return boost::algorithm::clamp(
                std::abs(dist_to_curb_at_av_s - av_sl_pos_or->l) -
                    vehicle_half_width + kHardCurbClearanceShift,
                kHardCurbClearanceMin, kHardCurbClearanceMax);
        };

    const std::vector<double> cascade_gains = {
        cost_weight_params.static_boundary_soft_cost_weight(),
        cost_weight_params.static_boundary_hard_cost_weight()};

    const double soft_curb_clearance =
        speed_rel_soft_curb_clearance_plf(plan_start_point.v());
    const double hard_curb_clearance = get_hard_curb_clearance(
        std::min(av_curb_pair_or->second, av_curb_pair_or->first));

    std::vector<int> below_mirror_curb_start_segment_ids,
        above_mirror_curb_start_segment_ids, uturn_right_curb_start_segment_ids,
        occ_boundary_start_segment_ids;
    std::vector<MsdProblemWithBuffer::SegmentType> below_mirror_curb_segments,
        above_mirror_curb_segments, uturn_right_curb_segments,
        occ_boundary_segments;
    bool uturn_curb_consider_mirrors = false;
    double nearest_curb_distance = 10.0;

    // 弯道外侧防御性避让ODD条件判断：
    // 1) 自车车速 > 10m/s
    // 2) 前方max(30m, v*2s)范围内存在连续高曲率段
    constexpr double kCurveDefensiveMinSpeed = 10.0;
    const double ego_s_on_ref =
        ref_center_frenet->XYToSL(plan_start_point.pos()).s;
    const double curve_look_ahead_dist =
        std::max(30.0, plan_start_point.v() * 2.0);
    const bool curve_defensive_enabled =
        (plan_start_point.v() > kCurveDefensiveMinSpeed) &&
        HasConsecutiveHighCurvatureAhead(
            ref_center_path, ego_s_on_ref, curve_look_ahead_dist);

    // std::printf("[CurveDefensive] v=%.2f ego_s=%.2f look_ahead=%.2f enabled=%d\n",
    //            plan_start_point.v(), ego_s_on_ref, curve_look_ahead_dist,
    //            static_cast<int>(curve_defensive_enabled));

    CollectCurbSegmentsAroundDrivePassage(
        trajectory_optimizer_vehicle_model_params.consider_mirrors_by_default(),
        veh_geo_params, plan_start_point, drive_passage,
        query_curb_extra_buffer, path_time_corridor,
        uturn_middle_s, &below_mirror_curb_segments,
        &below_mirror_curb_start_segment_ids, &above_mirror_curb_segments,
        &above_mirror_curb_start_segment_ids, &uturn_right_curb_segments,
        &uturn_right_curb_start_segment_ids, &uturn_curb_consider_mirrors,
        &nearest_curb_distance,
        ref_center_frenet, ref_center_vector, ref_center_path,
        curve_defensive_enabled);
    const size_t map_below_curb_segment_count =
        below_mirror_curb_segments.size();
    const size_t map_above_curb_segment_count =
        above_mirror_curb_segments.size();
    OccSegmentCollectionStats occ_stats;
    CollectOccSegmentsFromPolygon(
        csv_ctx, occ_polygon, drive_passage, query_curb_extra_buffer,
        &occ_boundary_segments, &occ_boundary_start_segment_ids,
        &occ_stats);
    OccDebugPrintStaticBoundarySummary(
        {map_below_curb_segment_count,
         map_above_curb_segment_count,
         occ_boundary_segments.size(),
         occ_boundary_start_segment_ids.size(),
         below_mirror_curb_segments.size(),
         below_mirror_curb_start_segment_ids.size(),
         above_mirror_curb_segments.size(),
         above_mirror_curb_start_segment_ids.size(),
         uturn_right_curb_segments.size(),
         uturn_right_curb_start_segment_ids.size(),
         occ_stats});


    std::vector<std::pair<double, Vec2d>> plan_start_circles;
    std::vector<std::pair<double, Vec2d>> plan_start_mirror_circles;

    for (int id : below_mirror_curb_start_segment_ids) {
    }
    for (const auto &circle :
         trajectory_optimizer_vehicle_model_params.circles()) {
        const Vec2d tangent = Vec2d::FastUnitFromAngle(
            plan_start_point.theta() + circle.angle_to_axis());
        plan_start_circles.emplace_back(
            circle.radius(),
            plan_start_point.pos() + circle.dist_to_rac() * tangent);
    }
    for (const auto &circle :
         trajectory_optimizer_vehicle_model_params.mirror_circles()) {
        const Vec2d tangent = Vec2d::FastUnitFromAngle(
            plan_start_point.theta() + circle.angle_to_axis());
        plan_start_mirror_circles.emplace_back(
            circle.radius(),
            plan_start_point.pos() + circle.dist_to_rac() * tangent);
    }
    const double min_mirror_height_avg =
        ComputeMinMaxMirrorAverageHeight(veh_geo_params).first;
    constexpr double kNearbyDistance = 10.0;
    double nearest_dist = kNearbyDistance;
    const std::vector<ImpassableBoundaryInfo> boundaries_info =
        drive_passage.GetImpassableBoundariesInfo(plan_start_point.pos(),
                                                  kNearbyDistance);
    // TODO:(xc)
    // = psmm.GetImpassableBoundariesInfo(plan_start_point.pos(),
    // kNearbyDistance);
    for (const auto &boundary_info : boundaries_info) {
        const bool consider_mirrors =
            boundary_info.height.has_value()
                ? (boundary_info.height.value() > min_mirror_height_avg)
                : trajectory_optimizer_vehicle_model_params
                      .consider_mirrors_by_default();
        for (const auto &circle : plan_start_circles) {
            nearest_dist = std::min(
                nearest_dist,
                boundary_info.segment.DistanceTo(circle.second) - circle.first);
        }
        if (consider_mirrors) {
            for (const auto &circle : plan_start_mirror_circles) {
                nearest_dist =
                    std::min(nearest_dist,
                             boundary_info.segment.DistanceTo(circle.second) -
                                 circle.first);
            }
        }
    }

    auto speed_rel_hard_curb_clearance_plf = PiecewiseLinearFunctionFromProto(
        cost_weight_params.speed_rel_hard_curb_clearance_plf());

    const double speed_rel_hard_curb_interval =
        speed_rel_hard_curb_clearance_plf(plan_start_point.v());

    if (!below_mirror_curb_segments.empty()) {
        if (FLAGS_msd_static_boundary_cost_v2) {
            OccDebugPrintStaticBoundaryCall(
                {"below_mirror_curb",
                 below_mirror_curb_segments.size(),
                 below_mirror_curb_start_segment_ids.size(),
                 nearest_dist,
                 lane_width});
            AddMsdStaticBoundaryCostV2(
                trajectory_steps, base_name, csv_ctx, "below_mirror_curb",
                kCurbGain,
                cost_weight_params, plan_start_point,
                trajectory_optimizer_vehicle_model_params, false,
                below_mirror_curb_start_segment_ids,
                std::move(below_mirror_curb_segments), stations_query_helper,
                lane_width_curb_buffer_opt, nearest_dist,
                speed_rel_hard_curb_interval, lane_width, costs);
        } else {
            AddMsdStaticBoundaryCost(
                trajectory_steps, base_name, "below_mirror_curb",
                cost_weight_params, plan_start_point, veh_geo_params,
                trajectory_optimizer_vehicle_model_params, false,
                below_mirror_curb_start_segment_ids,
                std::move(below_mirror_curb_segments), {"CurbSoft", "CurbHard"},
                {soft_curb_clearance, hard_curb_clearance}, cascade_gains,
                stations_query_helper, costs);
        }
    }
    if (!above_mirror_curb_segments.empty()) {
        if (FLAGS_msd_static_boundary_cost_v2) {
            OccDebugPrintStaticBoundaryCall(
                {"above_mirror_curb",
                 above_mirror_curb_segments.size(),
                 above_mirror_curb_start_segment_ids.size(),
                 nearest_dist,
                 lane_width});
            AddMsdStaticBoundaryCostV2(
                trajectory_steps, base_name, csv_ctx, "above_mirror_curb",
                kCurbGain,
                cost_weight_params, plan_start_point,
                trajectory_optimizer_vehicle_model_params, true,
                above_mirror_curb_start_segment_ids,
                std::move(above_mirror_curb_segments), stations_query_helper,
                lane_width_curb_buffer_opt, nearest_dist,
                speed_rel_hard_curb_interval, lane_width, costs);
        } else {
            AddMsdStaticBoundaryCost(
                trajectory_steps, base_name, "above_mirror_curb",
                cost_weight_params, plan_start_point, veh_geo_params,
                trajectory_optimizer_vehicle_model_params, true,
                above_mirror_curb_start_segment_ids,
                std::move(above_mirror_curb_segments), {"CurbSoft", "CurbHard"},
                {soft_curb_clearance, hard_curb_clearance}, cascade_gains,
                stations_query_helper, costs);
        }
    }
    if (!uturn_right_curb_segments.empty()) {
        if (FLAGS_msd_static_boundary_cost_v2) {
            OccDebugPrintStaticBoundaryCall(
                {"uturn_right_curb",
                 uturn_right_curb_segments.size(),
                 uturn_right_curb_start_segment_ids.size(),
                 nearest_dist,
                 lane_width});
            AddMsdStaticBoundaryCostV2(
                trajectory_steps, base_name, csv_ctx, "uturn_right_curb",
                kUTurnCurbGain,
                cost_weight_params, plan_start_point,
                trajectory_optimizer_vehicle_model_params,
                uturn_curb_consider_mirrors, uturn_right_curb_start_segment_ids,
                std::move(uturn_right_curb_segments), stations_query_helper,
                lane_width_curb_buffer_opt, nearest_dist,
                speed_rel_hard_curb_interval, lane_width, costs);
        } else {
            const std::vector<double> uturn_right_curb_cascade_gains = {
                cost_weight_params.static_boundary_soft_cost_weight() *
                    kUTurnCurbGain,
                cost_weight_params.static_boundary_hard_cost_weight() *
                    kUTurnCurbGain};
            AddMsdStaticBoundaryCost(
                trajectory_steps, base_name, "uturn_right_curb",
                cost_weight_params, plan_start_point, veh_geo_params,
                trajectory_optimizer_vehicle_model_params,
                uturn_curb_consider_mirrors, uturn_right_curb_start_segment_ids,
                std::move(uturn_right_curb_segments),
                {"UTurnRightCurbSoft", "UTurnRightCurbHard"},
                {soft_curb_clearance, hard_curb_clearance},
                uturn_right_curb_cascade_gains, stations_query_helper, costs);
        }
    }
    if (kEnableOccBoundaryCost && !occ_boundary_segments.empty()) {
        if (FLAGS_msd_static_boundary_cost_v2) {
            OccDebugPrintStaticBoundaryCall(
                {"occ_boundary",
                 occ_boundary_segments.size(),
                 occ_boundary_start_segment_ids.size(),
                 nearest_dist,
                 lane_width});
            AddMsdStaticBoundaryCostV2(
                trajectory_steps, base_name, csv_ctx, "occ_boundary",
                kOccBoundaryGain,
                cost_weight_params, plan_start_point,
                trajectory_optimizer_vehicle_model_params, false,
                occ_boundary_start_segment_ids,
                std::move(occ_boundary_segments), stations_query_helper,
                lane_width_curb_buffer_opt, nearest_dist,
                speed_rel_hard_curb_interval, lane_width, costs);
        } else {
            const std::vector<double> occ_cascade_gains = {
                cost_weight_params.static_boundary_soft_cost_weight() *
                    kOccBoundaryGain,
                cost_weight_params.static_boundary_hard_cost_weight() *
                    kOccBoundaryGain};
            AddMsdStaticBoundaryCost(
                trajectory_steps, base_name, "occ_boundary",
                cost_weight_params, plan_start_point, veh_geo_params,
                trajectory_optimizer_vehicle_model_params, false,
                occ_boundary_start_segment_ids,
                std::move(occ_boundary_segments),
                {"OccBoundarySoft", "OccBoundaryHard"},
                {soft_curb_clearance, hard_curb_clearance},
                occ_cascade_gains, stations_query_helper, costs);
        }
    }

    const std::vector<double> rear_gain = {
        cost_weight_params.path_boundary_cost_params()
            .rear_path_boundary_cost_weight(),
        cost_weight_params.target_path_boundary_cost_params()
            .rear_path_boundary_cost_weight()};
    const std::vector<double> front_gain = {
        cost_weight_params.path_boundary_cost_params()
            .front_path_boundary_cost_weight(),
        cost_weight_params.target_path_boundary_cost_params()
            .front_path_boundary_cost_weight()};
    const std::vector<double> buffers_min = {
        cost_weight_params.path_boundary_cost_params().buffer_min(),
        cost_weight_params.target_path_boundary_cost_params().buffer_min()};
    const std::vector<double> rear_buffers_max = {
        cost_weight_params.path_boundary_cost_params().rear_buffer_max(),
        cost_weight_params.target_path_boundary_cost_params()
            .rear_buffer_max()};
    const std::vector<double> front_buffers_max = {
        cost_weight_params.path_boundary_cost_params().front_buffer_max(),
        cost_weight_params.target_path_boundary_cost_params()
            .front_buffer_max()};
    const std::vector<double> mid_buffers_max = {
        cost_weight_params.path_boundary_cost_params().mid_buffer_max(),
        cost_weight_params.target_path_boundary_cost_params().mid_buffer_max()};

    for (const bool left : {false, true}) {
        std::vector<std::vector<double>> dists_to_path_boundary;
        dists_to_path_boundary.reserve(2);
        std::vector<double> cascade_gains;
        cascade_gains.reserve(2);
        if (left) {
            dists_to_path_boundary.push_back(left_dists_to_path_boundary);
            dists_to_path_boundary.push_back(
                left_dists_to_target_path_boundary);
            cascade_gains.push_back(
                cost_weight_params.path_boundary_cost_params()
                    .left_path_boundary_cost_weight());
            cascade_gains.push_back(
                cost_weight_params.target_path_boundary_cost_params()
                    .left_path_boundary_cost_weight());
        } else {
            dists_to_path_boundary.push_back(right_dists_to_path_boundary);
            dists_to_path_boundary.push_back(
                right_dists_to_target_path_boundary);
            cascade_gains.push_back(
                cost_weight_params.path_boundary_cost_params()
                    .right_path_boundary_cost_weight());
            cascade_gains.push_back(
                cost_weight_params.target_path_boundary_cost_params()
                    .right_path_boundary_cost_weight());
        }
        std::vector<std::vector<double>> ref_gains;
        ref_gains.reserve(cascade_gains.size());
        std::vector<double> outer_path_boundary_gains(station_points.size(),
                                                      1.0);
        ref_gains.push_back(std::move(outer_path_boundary_gains));
        ref_gains.push_back(inner_path_boundary_gains);
        auto &gains = ref_gains.back();
        constexpr double kDecayGainLookAheadTime = 2.5;
        const double decay_gain_look_ahead_s =
            plan_start_point.v() * kDecayGainLookAheadTime +
            veh_geo_params.front_edge_to_center();
        const auto &stations = drive_passage.stations();
        const int s_index = std::distance(
            stations.begin(),
            std::upper_bound(stations.begin(), stations.end(),
                             decay_gain_look_ahead_s,
                             [](double val, const Station &station) {
                                 return val < station.accumulated_s();
                             }));

        if ((lc_stage == LaneChangeStage::LCS_NONE) && !borrow_lane) {
          const auto kDecayGain_func = PiecewiseLinearFunctionFromProto(
              cost_weight_params.path_boundary_cost_params()
                  .decay_inner_path_boundary_gains());
          double kDecayGain = kDecayGain_func(plan_start_point.v());
          for (int i = 0; i < gains.size(); ++i) {
            if (i > s_index) {break;}
             gains[i] = kDecayGain;
          }
        } else {
          double kDecayGain = cost_weight_params.path_boundary_cost_params()
                                  .default_decay_inner_path_boundary_gains();
          for (int i = 0; i < gains.size(); ++i) {
            if (i > s_index) {break;}
            gains[i] = std::min(gains[i], kDecayGain);
          }
        }

        std::vector<std::string> sub_names = {"Outer", "Inner"};
        costs->emplace_back(std::make_unique<MfobPathBoundaryCost<Mfob>>(
            trajectory_steps, veh_geo_params, station_points,
            stations_query_helper.get(), reference_center_l_offsets,
            dists_to_path_boundary, left, true, mid_edges_to_center,
            std::move(ref_gains), std::move(sub_names), true, buffers_min,
            rear_buffers_max, front_buffers_max, mid_buffers_max, cascade_gains,
            rear_gain, front_gain,
            absl::StrCat("PathBoundaryCost: ",
                         left ? "left path boundary" : "right path boundary"),
            1.0, Cost<Mfob>::CostType::MUST_HAVE));
    }
}

void AddSolidWhiteLineCost(
    int trajectory_steps,
    std::string base_name,
    const std::vector<TrajectoryPoint> &solver_init_traj,
    const ConstraintManager &constraint_manager,
    const TrajectoryPoint &plan_start_point,
    const TrajectoryOptimizerCostWeightParamsProto &cost_weight_params,
    const VehicleGeometryParamsProto &veh_geo_params,
    const VehicleCircleModelParamsProto
        &trajectory_optimizer_vehicle_model_params,
    const std::unique_ptr<CenterLineQueryHelper<Mfob>> &stations_query_helper,
    std::vector<std::unique_ptr<Cost<Mfob>>> *costs) {
    if (!XCHECK_GT(trajectory_steps, 0) || !XCHECK_NOTNULL(costs)) {
        return;
    }

    constexpr double kSolidLineExtendDistance = 0.5;
    constexpr double kSolidLineBuffer = 0.2;
    std::vector<int> solid_line_start_segment_ids;
    std::vector<MsdProblemWithBuffer::SegmentType> solid_line_segments;
    CollectExtendSolidLinesWithinPathBoundary(
        veh_geo_params, trajectory_optimizer_vehicle_model_params,
        constraint_manager, solver_init_traj, kSolidLineBuffer,
        kSolidLineExtendDistance, &solid_line_start_segment_ids,
        &solid_line_segments);
    if (FLAGS_static_boundary_canvas_level >= 1) {
    }
    if (!solid_line_segments.empty()) {
        AddMsdStaticBoundaryCost(
            trajectory_steps, base_name, "solid_line", cost_weight_params,
            plan_start_point, veh_geo_params,
            trajectory_optimizer_vehicle_model_params, false,
            solid_line_start_segment_ids, std::move(solid_line_segments),
            {"SolidLine"}, {kSolidLineBuffer},

            {cost_weight_params.static_boundary_solid_line_cost_weight()},
            stations_query_helper, costs);
    }
}

}  // namespace optimizer
}  // namespace planning
}  // namespace pnc_x
