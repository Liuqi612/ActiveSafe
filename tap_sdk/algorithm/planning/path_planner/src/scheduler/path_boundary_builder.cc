

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "scheduler/path_boundary_builder.h"
#include <absl/status/status.h>
#include <absl/strings/string_view.h>
#include <absl/types/span.h>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include "math/geometry/box2d.h"
#include "math/geometry/util.h"
#include "math/vec.h"
#include "plan/planner_defs.h"
#include "scheduler/path_boundary_builder.h"
#include "scheduler/path_boundary_builder_helper.h"

#include "common/log.h"
#include "common/vehicle_behavior_helper.h"
#include "util/loop_guard.h"
#include "util/status_builder.h"
#include "util/status_macros.h"
#include "util/vehicle_geometry_util.h"

extern bool FLAGS_planner_enable_path_boundary_debug;

namespace pnc_x {
namespace planning {
namespace {

// using BgPoint = bg::model::d2::point_xy<double>;

constexpr double kMaxInnerBoundLaneChangeLatAccel = 0.09;
constexpr double kMaxOuterBoundLaneChangeLatAccel = 0.08;
constexpr double kMaxLaneChangeCancelLatAccel = 0.5;
constexpr double kExtendOuterBoundWidth = kDefaultHalfLaneWidth;

struct BoundaryDebugView {
    const char *name = nullptr;
    const PathBoundary *boundary = nullptr;
};

std::string DebugDouble(double value) {
    if (!std::isfinite(value)) {
        return value > 0.0 ? "inf" : (value < 0.0 ? "-inf" : "nan");
    }
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << value;
    return oss.str();
}

void LogBoundarySummary(absl::string_view stage,
                        absl::string_view name,
                        absl::Span<const double> s_vec,
                        const PathBoundary &boundary) {
    if (!FLAGS_planner_enable_path_boundary_debug) {
        return;
    }

    const int n = std::min(static_cast<int>(s_vec.size()), boundary.size());
    double min_width = std::numeric_limits<double>::infinity();
    double max_width = -std::numeric_limits<double>::infinity();
    int min_width_idx = -1;
    int invalid_count = 0;
    int first_invalid_idx = -1;
    for (int i = 0; i < n; ++i) {
        const double width = boundary.left(i) - boundary.right(i);
        if (width < min_width) {
            min_width = width;
            min_width_idx = i;
        }
        max_width = std::max(max_width, width);
        if (boundary.left(i) < boundary.right(i)) {
            ++invalid_count;
            if (first_invalid_idx < 0) {
                first_invalid_idx = i;
            }
        }
    }

    AD_LDEBUG(PP)
        << "[PathBoundaryDebug][summary]"
        << " stage=" << std::string(stage) << " name=" << std::string(name)
        << " size=" << boundary.size() << " s_size=" << s_vec.size()
        << " min_width=" << DebugDouble(min_width)
        << " max_width=" << DebugDouble(max_width)
        << " min_width_idx=" << min_width_idx << " min_width_s="
        << (min_width_idx >= 0 ? DebugDouble(s_vec[min_width_idx]) : "nan")
        << " min_width_right="
        << (min_width_idx >= 0 ? DebugDouble(boundary.right(min_width_idx))
                               : "nan")
        << " min_width_left="
        << (min_width_idx >= 0 ? DebugDouble(boundary.left(min_width_idx))
                               : "nan")
        << " invalid_count=" << invalid_count
        << " first_invalid_idx=" << first_invalid_idx;
}

void LogBoundarySnapshot(absl::string_view stage,
                         const DrivePassage &drive_passage,
                         absl::Span<const double> s_vec,
                         absl::Span<const double> center_l,
                         absl::Span<const BoundaryDebugView> boundaries) {
    if (!FLAGS_planner_enable_path_boundary_debug) {
        return;
    }

    AD_LDEBUG(PP) << "[PathBoundaryDebug][snapshot]"
                  << " stage=" << std::string(stage)
                  << " station_size=" << drive_passage.size()
                  << " s_size=" << s_vec.size()
                  << " center_l_size=" << center_l.size();

    for (const auto &boundary : boundaries) {
        if (boundary.boundary != nullptr) {
            LogBoundarySummary(stage, boundary.name, s_vec, *boundary.boundary);
        }
    }

    const int n =
        std::min(static_cast<int>(s_vec.size()), drive_passage.size());
    for (int i = 0; i < n; ++i) {
        const auto &station = drive_passage.station(StationIndex(i));
        std::ostringstream oss;
        oss << "[PathBoundaryDebug][point]"
            << " stage=" << std::string(stage) << " i=" << i
            << " s=" << DebugDouble(s_vec[i]) << " center_l="
            << (i < center_l.size() ? DebugDouble(center_l[i]) : "nan")
            << " station_s=" << DebugDouble(station.accumulated_s())
            << " xy_x=" << DebugDouble(station.xy().x())
            << " xy_y=" << DebugDouble(station.xy().y())
            << " turn=" << station.turn_type()
            << " split=" << station.is_splitting()
            << " merge=" << station.is_merging()
            << " intersection=" << station.is_in_intersection()
            << " virtual=" << station.is_virtual()
            << " cross_curb=" << station.has_cross_curb();
        for (const auto &boundary : boundaries) {
            if (boundary.boundary == nullptr ||
                i >= boundary.boundary->size()) {
                oss << " " << boundary.name << "_valid=0";
                continue;
            }
            const double right = boundary.boundary->right(i);
            const double left = boundary.boundary->left(i);
            oss << " " << boundary.name << "_valid=1"
                << " " << boundary.name << "_right=" << DebugDouble(right)
                << " " << boundary.name << "_left=" << DebugDouble(left) << " "
                << boundary.name << "_width=" << DebugDouble(left - right);
        }
        AD_LDEBUG(PP) << oss.str();
    }
}

void LogBoundaryContext(absl::string_view stage,
                        const LaneEvadeInfo &lane_evade_info,
                        const LaneChangeStateProto &lc_state,
                        const FrenetCoordinate &cur_sl,
                        const FrenetBox &sl_box,
                        double target_lane_offset,
                        double used_target_lane_offset,
                        const double *last_used_target_lane_offset,
                        bool borrow_lane_boundary,
                        bool lane_change_pause_or_push,
                        bool should_smooth,
                        bool is_ego_corner_across_lane_bound,
                        bool is_limited_pause,
                        int is_force_lc,
                        double force_lc_offset_ratio,
                        double half_target_lane_width,
                        const std::pair<int, int> &left_split_range,
                        const std::pair<int, int> &right_split_range,
                        int clamp_idx) {
    if (!FLAGS_planner_enable_path_boundary_debug) {
        return;
    }

    AD_LDEBUG(PP)
        << "[PathBoundaryDebug][context]"
        << " stage=" << std::string(stage) << " lc_stage=" << lc_state.stage()
        << " lc_left=" << lc_state.lc_left()
        << " entered_target_lane=" << lc_state.entered_target_lane()
        << " push_state=" << lc_state.push_state()
        << " pre_push_state=" << lc_state.pre_push_state()
        << " lane_evade=" << lane_evade_info.is_evade
        << " lane_evade_offset=" << DebugDouble(lane_evade_info.offset)
        << " cur_s=" << DebugDouble(cur_sl.s)
        << " cur_l=" << DebugDouble(cur_sl.l)
        << " sl_box_s_min=" << DebugDouble(sl_box.s_min)
        << " sl_box_s_max=" << DebugDouble(sl_box.s_max)
        << " sl_box_l_min=" << DebugDouble(sl_box.l_min)
        << " sl_box_l_max=" << DebugDouble(sl_box.l_max)
        << " target_lane_offset=" << DebugDouble(target_lane_offset)
        << " used_target_lane_offset=" << DebugDouble(used_target_lane_offset)
        << " last_used_target_lane_offset="
        << (last_used_target_lane_offset != nullptr
                ? DebugDouble(*last_used_target_lane_offset)
                : "null")
        << " borrow_lane_boundary=" << borrow_lane_boundary
        << " lane_change_pause_or_push=" << lane_change_pause_or_push
        << " should_smooth=" << should_smooth
        << " ego_corner_across_lane_bound=" << is_ego_corner_across_lane_bound
        << " is_limited_pause=" << is_limited_pause
        << " is_force_lc=" << is_force_lc
        << " force_lc_offset_ratio=" << DebugDouble(force_lc_offset_ratio)
        << " half_target_lane_width=" << DebugDouble(half_target_lane_width)
        << " left_split_range=[" << left_split_range.first << ","
        << left_split_range.second << "]"
        << " right_split_range=[" << right_split_range.first << ","
        << right_split_range.second << "]"
        << " clamp_idx=" << clamp_idx;
}

PathBoundary ExtendBoundaryBy(const DrivePassage &drive_passage,
                              PathBoundary boundary,
                              bool is_lane_changing,
                              bool lc_left,
                              double extend_width) {
    const auto function_type = drive_passage.GetAdFunctionType();
    const auto lateral_state = drive_passage.GetAdLateralState();
    if (AD_FunctionType::CNOP == function_type) {
        extend_width = std::min(0.5, extend_width);
    }
    double left_extend_path_boundary_width =
        is_lane_changing && lc_left ? 0.0 : extend_width;
    double right_extend_path_boundary_width =
        is_lane_changing && !lc_left ? 0.0 : extend_width;

    if (!is_lane_changing && (AD_FunctionType::HNOP == function_type)) {
        left_extend_path_boundary_width = 0.0;
        right_extend_path_boundary_width = 0.0;
    }

    if (AD_LateralState::LEFT_LANE_BORROW == lateral_state) {
        left_extend_path_boundary_width =
            std::max(left_extend_path_boundary_width, 3.5);
    }

    if (AD_LateralState::LEFT_LANE_BORROW == lateral_state) {
        right_extend_path_boundary_width =
            std::max(right_extend_path_boundary_width, 3.5);
    }

    boost::optional<double> uturn_middle_s;
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
        uturn_middle_s = 0.5 * (u_turn_start_s + u_turn_end_s);
    }

    for (int i = 0; i < boundary.size(); ++i) {
        const auto &station = drive_passage.station(StationIndex(i));
        boundary.ShiftLeftByIndex(i, left_extend_path_boundary_width);
        if ((station.turn_type() == ads_x::planning::TurnType::U_TURN) &&
            uturn_middle_s.has_value() &&
            (station.accumulated_s() < *uturn_middle_s)) {
            continue;
        }
        boundary.ShiftRightByIndex(i, -right_extend_path_boundary_width);
    }

    return boundary;
}

std::vector<double> PostprocessOuterBoundary(absl::Span<const double> s_vec,
                                             absl::Span<const double> inner_vec,
                                             std::vector<double> outer_vec) {
    constexpr double kEpsilon = 0.1;
    constexpr double kMinContinuousExtendedBoundLength = 3.0;
    int first_extended_idx = -1;
    for (int i = 1; i < inner_vec.size(); ++i) {
        bool curr_is_extended = std::fabs(inner_vec[i] - outer_vec[i]) >
                                (kExtendOuterBoundWidth - kEpsilon);
        bool prev_is_extended = std::fabs(inner_vec[i - 1] - outer_vec[i - 1]) >
                                (kExtendOuterBoundWidth - kEpsilon);
        if (first_extended_idx == -1) {
            if (curr_is_extended && !prev_is_extended) {
                first_extended_idx = i;
            }
        } else if (!curr_is_extended) {
            if ((s_vec[i - 1] - s_vec[first_extended_idx]) <=
                kMinContinuousExtendedBoundLength) {
                for (int j = first_extended_idx; j < i; ++j) {
                    outer_vec[j] = outer_vec[first_extended_idx - 1];
                }
            }
            first_extended_idx = -1;
        }
    }

    return outer_vec;
}

void SmoothBoundary(absl::Span<const double> s_vec,
                    const std::pair<int, int> &split_range,
                    bool is_left,
                    std::vector<double> *vec_ptr) {
    if ((nullptr == vec_ptr) || (vec_ptr->size() < 4)) return;
    auto &vec = *vec_ptr;
    int front_idx = 0;
    int back_idx = vec.size() - 1;
    const double ramp_factor = 0.25;
    if (is_left) {
        auto loop_guard1 = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((front_idx < back_idx) && loop_guard1) {
            if (vec[front_idx] > vec[back_idx] + 0.01) {
                --back_idx;
                if (vec[back_idx] < vec[back_idx + 1])
                    vec[back_idx] = vec[back_idx + 1];
            } else {
                ++front_idx;
                if (vec[front_idx] < vec[front_idx - 1])
                    vec[front_idx] = vec[front_idx - 1];
            }
        }
        auto loop_guard2 = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((front_idx > 0) && loop_guard2) {
            --front_idx;
            double left_ramp_factor =
                ((split_range.first > 0) && (front_idx >= split_range.first) &&
                 (front_idx <= split_range.second))
                    ? 0.1
                    : ramp_factor;
            double temp_l =
                vec[front_idx + 1] -
                (s_vec[front_idx + 1] - s_vec[front_idx]) * left_ramp_factor;
            if (temp_l > vec[front_idx]) vec[front_idx] = temp_l;
        }
        auto loop_guard3 = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((back_idx < vec.size() - 1) && loop_guard3) {
            ++back_idx;
            double left_ramp_factor =
                ((split_range.first > 0) && (back_idx >= split_range.first) &&
                 (back_idx <= split_range.second))
                    ? 0.1
                    : ramp_factor;
            double temp_l =
                vec[back_idx - 1] -
                (s_vec[back_idx] - s_vec[back_idx - 1]) * left_ramp_factor;
            if (temp_l > vec[back_idx]) vec[back_idx] = temp_l;
        }
    } else {
        auto loop_guard1 = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((front_idx < back_idx) && loop_guard1) {
            if (vec[front_idx] < vec[back_idx] - 0.01) {
                --back_idx;
                if (vec[back_idx] > vec[back_idx + 1])
                    vec[back_idx] = vec[back_idx + 1];
            } else {
                ++front_idx;
                if (vec[front_idx] > vec[front_idx - 1])
                    vec[front_idx] = vec[front_idx - 1];
            }
        }
        auto loop_guard2 = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((front_idx > 0) && loop_guard2) {
            --front_idx;
            double right_ramp_factor =
                ((split_range.first > 0) && (front_idx >= split_range.first) &&
                 (front_idx <= split_range.second))
                    ? 0.1
                    : ramp_factor;
            double temp_l =
                vec[front_idx + 1] +
                (s_vec[front_idx + 1] - s_vec[front_idx]) * right_ramp_factor;
            if (temp_l < vec[front_idx]) vec[front_idx] = temp_l;
        }
        auto loop_guard3 = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((back_idx < vec.size() - 1) && loop_guard3) {
            ++back_idx;
            double right_ramp_factor =
                ((split_range.first > 0) && (back_idx >= split_range.first) &&
                 (back_idx <= split_range.second))
                    ? 0.1
                    : ramp_factor;
            double temp_l =
                vec[back_idx - 1] +
                (s_vec[back_idx] - s_vec[back_idx - 1]) * right_ramp_factor;
            if (temp_l < vec[back_idx]) vec[back_idx] = temp_l;
        }
    }
}

}  // namespace

absl::StatusOr<PathSlBoundary> BuildPathBoundaryFromDrivePassage(
    const DrivePassage &drive_passage) {
    const int n = drive_passage.size();
    std::vector<double> s_vec, center_l(n, 0.0);
    s_vec.reserve(n);
    for (const auto &station : drive_passage.stations()) {
        s_vec.push_back(station.accumulated_s());
    }
    const std::pair<int, int> left_split_range = {-1, -1};
    const std::pair<int, int> right_split_range = {-1, -1};
    const double ego_v = 5.0;
    auto inner_boundary = BuildPathBoundaryFromTargetLane(
        drive_passage, ego_v, left_split_range, right_split_range,
        0.5 * kMinLaneWidth, false);

    const auto curb_boundary = BuildCurbPathBoundary(drive_passage);
    const std::vector<BoundaryDebugView> raw_views = {
        {"inner", &inner_boundary}, {"curb", &curb_boundary}};
    LogBoundarySnapshot("drive_passage_raw", drive_passage, s_vec, center_l,
                        raw_views);
    inner_boundary.OuterClampBy(curb_boundary);
    PathBoundary outer_boundary = inner_boundary;
    PathBoundary opt_outer_boundary = outer_boundary;
    const std::vector<BoundaryDebugView> final_views = {
        {"inner", &inner_boundary},
        {"outer", &outer_boundary},
        {"opt_outer", &opt_outer_boundary}};
    LogBoundarySnapshot("drive_passage_final", drive_passage, s_vec, center_l,
                        final_views);

    return BuildPathSlBoundary(drive_passage, std::move(s_vec),
                               std::move(center_l), std::move(inner_boundary),
                               std::move(outer_boundary),
                               std::move(opt_outer_boundary));
}

absl::StatusOr<PathSlBoundary> BuildPathBoundaryFromPose(
    const DrivePassage &drive_passage,
    const ApolloTrajectoryPointProto &plan_start_point,
    const LaneEvadeInfo &lane_evade_info,
    const VehicleGeometryParamsProto &vehicle_geom,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const LaneChangeStateProto &lc_state,
    const SmoothedReferenceLineResultMap &smooth_result_map,
    bool borrow_lane_boundary,
    bool should_smooth,
    double *last_used_target_lane_offset,
    const boost::optional<double> ref_centered_compensation_offset,
    int is_force_lc,
    double force_lc_offset_ratio,
    bool is_ego_corner_across_lane_bound,
    const DrivePassage *lk_drive_passage,
    bool is_limited_pause,
    bool adjust_astar_search_boundary_for_lc,
    bool is_uturn) {
    const Box2d ego_box =
        ComputeAvBox(Vec2dFromApolloTrajectoryPointProto(plan_start_point),
                     plan_start_point.path_point().theta(), vehicle_geom);

    ASSIGN_OR_RETURN(
        const auto sl_box, drive_passage.QueryFrenetBoxAt(ego_box),
        _ << "BuildPathBoundaryFromPose: Fail to project ego box on "
             "drive passage.");

    ASSIGN_OR_RETURN(
        const auto cur_sl,
        drive_passage.QueryFrenetCoordinateAt(
            Vec2dFromApolloTrajectoryPointProto(plan_start_point)),
        _ << "BuildPathBoundaryFromPose: Fail to project ego pos on "
             "drive passage.");
    constexpr double kEpsilon = 1e-6;
    constexpr double kMaxIncreaseDeltaIffset = 0.15;
    constexpr double kMaxDecreaseDeltaOffset = 0.1;
    const int n = drive_passage.stations().size();
    std::vector<double> s_vec;
    s_vec.reserve(n);
    std::pair<int, int> split_range = {-1, -1};
    int split_type = 0;
    int clamp_idx = n + 4, idx = 0;
    bool is_split_followed_by_intersection = false;
    for (const auto &station : drive_passage.stations()) {
        s_vec.push_back(station.accumulated_s());
        if ((clamp_idx > n) && station.has_cross_curb()) {
            clamp_idx = idx;
        }
        if (idx > 0) {
            if (station.is_splitting()) {
                if (split_range.first < 0) {
                    split_type = (SplitTopology::TOPOLOGY_SPLIT_LEFT ==
                                  station.station_info().split_topo)
                                     ? 1
                                     : ((SplitTopology::TOPOLOGY_SPLIT_RIGHT ==
                                         station.station_info().split_topo)
                                            ? 2
                                            : 0);
                    if (split_type > 0) {
                        split_range.first = idx;
                        split_range.second = idx;
                    }
                } else if (split_range.second + 1 == idx) {
                    if (station.is_in_intersection()) {
                        is_split_followed_by_intersection = true;
                    } else {
                        split_range.second = idx;
                    }
                }
            } else if (split_range.second + 1 == idx) {
                is_split_followed_by_intersection =
                    station.is_in_intersection() || station.is_virtual();
            }
        }
        ++idx;
    }
    if (is_split_followed_by_intersection) {
        const double virtual_buffer = 10.0;
        split_range.second -= virtual_buffer;
        if (split_range.second - split_range.first < virtual_buffer * 0.5) {
            split_type = 0;
        }
    }
    std::pair<int, int> left_split_range =
        (1 == split_type) ? split_range : std::make_pair(-1, -1);
    std::pair<int, int> right_split_range =
        (2 == split_type) ? split_range : std::make_pair(-1, -1);

    // TODO:(CXC):referenceline has been smoothed, so we can use it directly
    std::vector<double> center_l =
        ComputeSmoothedReferenceLine(drive_passage, smooth_result_map);

    center_l =
        ComputeCompensationRefLine(drive_passage, center_l, plan_start_point,
                                   ref_centered_compensation_offset);

    // TODO:(CXC):NEED lane_evade_info
    double target_lane_offset = 0.0;
    double used_target_lane_offset = 0.0;
    auto lc_target_lane_offset = ComputeTargetLaneOffset(
        drive_passage, cur_sl, lc_state, plan_start_point,
        vehicle_geom.width() * 0.5, is_force_lc, force_lc_offset_ratio,
        st_traj_mgr.trajectories());
    if ((lc_state.push_state() != PushState::NONE_PUSH) &&
        lane_evade_info.is_evade) {
        if ((lane_evade_info.offset > kEpsilon) &&
            ((lc_state.push_state() == PushState::LEFT_PUSH) ||
             (lc_state.push_state() == PushState::CONGESTION_LEFT_PUSH))) {
            target_lane_offset =
                std::fmin(target_lane_offset, lane_evade_info.offset);
        } else if ((lane_evade_info.offset < -kEpsilon) &&
                   ((lc_state.push_state() == PushState::RIGHT_PUSH) ||
                    (lc_state.push_state() ==
                        PushState::CONGESTION_RIGHT_PUSH))) {
            target_lane_offset =
                std::fmax(target_lane_offset, lane_evade_info.offset);
        }
    } else if (lane_evade_info.is_evade) {
        target_lane_offset = lane_evade_info.offset;
        // 仅在 last_used 为 0 且与 offset 同侧时初始化，避免收敛到 0 后循环重置
        if (last_used_target_lane_offset != nullptr &&
            std::abs(*last_used_target_lane_offset) < kEpsilon &&
            std::abs(lane_evade_info.offset) > kEpsilon) {
            *last_used_target_lane_offset = lane_evade_info.offset;
        }
    } else {
        target_lane_offset = lc_target_lane_offset;
        if (lc_state.stage() == LaneChangeStage::LCS_PAUSE) {
            target_lane_offset = lc_state.pause_shift_l();
        }
    }
    if (last_used_target_lane_offset != nullptr) {
        if (is_force_lc > 0) {
            used_target_lane_offset = target_lane_offset;
            *last_used_target_lane_offset = 0.0;
        } else if (lc_state.stage() == LaneChangeStage::LCS_PAUSE) {
            used_target_lane_offset = target_lane_offset;
            *last_used_target_lane_offset = 0.0;
        } else {
            if (target_lane_offset > kEpsilon) {
                if (*last_used_target_lane_offset < target_lane_offset) {
                    used_target_lane_offset = std::min(
                        *last_used_target_lane_offset + kMaxIncreaseDeltaIffset,
                        target_lane_offset);
                } else {
                    used_target_lane_offset = std::max(
                        *last_used_target_lane_offset - kMaxDecreaseDeltaOffset,
                        target_lane_offset);
                }

            } else if (target_lane_offset < -kEpsilon) {
                if (*last_used_target_lane_offset > target_lane_offset) {
                    used_target_lane_offset = std::max(
                        *last_used_target_lane_offset - kMaxIncreaseDeltaIffset,
                        target_lane_offset);
                } else {
                    used_target_lane_offset = std::min(
                        *last_used_target_lane_offset + kMaxDecreaseDeltaOffset,
                        target_lane_offset);
                }
            } else {
                if (*last_used_target_lane_offset > target_lane_offset) {
                    used_target_lane_offset = std::max(
                        *last_used_target_lane_offset - kMaxDecreaseDeltaOffset,
                        target_lane_offset);

                } else {
                    used_target_lane_offset = std::min(
                        *last_used_target_lane_offset + kMaxDecreaseDeltaOffset,
                        target_lane_offset);
                }
            }
        }
        if ((lc_state.stage() != LaneChangeStage::LCS_NONE) &&
            (lc_state.stage() != LaneChangeStage::LCS_PAUSE) &&
            (is_force_lc == 0) && !lane_evade_info.is_evade) {
            used_target_lane_offset = 0.0;
            *last_used_target_lane_offset = used_target_lane_offset;
        }
    }

    bool lane_change_pause_or_push =
        (lc_state.stage() == LaneChangeStage::LCS_PAUSE) ||
        (lc_state.push_state() != PushState::NONE_PUSH);
    double half_target_lane_width = kDefaultHalfLaneWidth;
    std::vector<double> smooth_center_offset(n, 0.0);
    if (lane_change_pause_or_push || lane_evade_info.is_evade ||
        (std::abs(used_target_lane_offset) > kEpsilon)) {
        const auto cur_station_index =
            drive_passage
                .FindNearestStationIndex(
                    Vec2dFromApolloTrajectoryPointProto(plan_start_point))
                .value();
        if (lk_drive_passage == nullptr) {
            smooth_center_offset.assign(
                n, used_target_lane_offset - center_l[cur_station_index]);
        } else {
            absl::StatusOr<double> start_point_l_at_lk =
                lk_drive_passage->QueryFrenetLatOffsetAt(
                    Vec2dFromApolloTrajectoryPointProto(plan_start_point));
            if (start_point_l_at_lk.ok() &&
                (std::abs(start_point_l_at_lk.value()) < 1.75)) {
                for (int i = 0; i < n; ++i) {
                    const Vec2d &station_xy =
                        drive_passage.station(StationIndex(i)).xy();
                    absl::StatusOr<double> station_sl =
                        lk_drive_passage->QueryFrenetLatOffsetAt(station_xy);
                    if (!station_sl.ok() ||
                        ((std::abs(used_target_lane_offset -
                                  center_l[cur_station_index]) <
                             std::abs(station_sl.value())) &&
                         is_ego_corner_across_lane_bound)) {
                        smooth_center_offset[i] = used_target_lane_offset -
                                                  center_l[cur_station_index];

                    } else {
                        if (is_limited_pause) {
                            smooth_center_offset[i] = -station_sl.value();
                        } else {
                            constexpr double kMinStationOffset = 0.5;
                            const double fixed_offset =
                                used_target_lane_offset < 0.0
                                    ? std::max(used_target_lane_offset -
                                                   center_l[cur_station_index],
                                               -station_sl.value())
                                    : std::min(used_target_lane_offset -
                                                   center_l[cur_station_index],
                                               std::abs(station_sl.value()));
                            smooth_center_offset[i] = fixed_offset;
                        }
                    }
                }
            } else {
                smooth_center_offset.assign(
                    n, used_target_lane_offset - center_l[cur_station_index]);
            }
        }

        const auto smoothed_center_offset =
            used_target_lane_offset - center_l[cur_station_index];
        if ((is_force_lc > 0) && (lc_state.stage() == LaneChangeStage::LCS_NONE)) {
            auto start_station_index = -1;
            auto end_station_index = -1;
            for (int i = 0; i < n; ++i) {
                const auto &station = drive_passage.station(StationIndex(i));
                if (station.is_merging() && (start_station_index == -1)) {
                    start_station_index = i;
                } else if (!station.is_merging() && (start_station_index != -1) &&
                           (end_station_index == -1)) {
                    end_station_index = i;
                    break;
                }
            }
            if ((start_station_index != -1) && (end_station_index != -1) &&
                (start_station_index < end_station_index)) {
                for (int i = 0; i < n; ++i) {
                    if (i <= start_station_index) {
                        center_l[i] += smoothed_center_offset;
                    } else if (i >= end_station_index) {
                        center_l[i] += 0.;
                    } else {
                        double ratio =
                            1.0 -
                            (static_cast<double>(i) - start_station_index) /
                                (end_station_index - start_station_index);
                        center_l[i] += smoothed_center_offset * ratio;
                    }
                }
            } else {
                used_target_lane_offset = 0.0;
            }
        } else {
            for (int i = 0; i < n; ++i) {
                center_l[i] += smooth_center_offset[i];
            }
        }
        if (!lane_evade_info.is_evade) {
            const auto &cur_station =
                drive_passage.station(StationIndex(cur_station_index));
            double right_offset = std::numeric_limits<double>::lowest();
            double left_offset = std::numeric_limits<double>::max();
            for (const auto &cur_bound : cur_station.boundaries()) {
                if (cur_bound.lat_offset < 0.0) {
                    right_offset = std::max(right_offset, cur_bound.lat_offset);
                }
                if (cur_bound.lat_offset > 0.0) {
                    left_offset = std::min(left_offset, cur_bound.lat_offset);
                }
            }
            half_target_lane_width = lc_state.lc_left()
                                         ? std::fabs(right_offset)
                                         : std::fabs(left_offset);
        }
    }
    LogBoundaryContext("after_target_lane_offset", lane_evade_info, lc_state,
                       cur_sl, sl_box, target_lane_offset,
                       used_target_lane_offset, last_used_target_lane_offset,
                       borrow_lane_boundary, lane_change_pause_or_push,
                       should_smooth, is_ego_corner_across_lane_bound,
                       is_limited_pause, is_force_lc, force_lc_offset_ratio,
                       half_target_lane_width, left_split_range,
                       right_split_range, clamp_idx);

    auto boundary = BuildPathBoundaryFromTargetLane(
        drive_passage, plan_start_point.v(), left_split_range,
        right_split_range, 0.1, borrow_lane_boundary);

    const auto solid_boundary = BuildSolidPathBoundary(
        drive_passage, cur_sl, vehicle_geom, plan_start_point, st_traj_mgr,
        lc_state, used_target_lane_offset, left_split_range, right_split_range,
        center_l);

    const auto curb_boundary = BuildCurbPathBoundary(drive_passage);

    const bool is_lane_changing =
        ((lc_state.stage() == LaneChangeStage::LCS_EXECUTING) ||
         (lc_state.stage() == LaneChangeStage::LCS_RETURN)) &&
        !lc_state.entered_target_lane();

    const double inner_bound_lat_acc =
        ((lc_state.stage() == LaneChangeStage::LCS_EXECUTING) ||
         drive_passage.GetIsChangeAbnormal())
            ? kMaxInnerBoundLaneChangeLatAccel
            : kMaxLaneChangeCancelLatAccel;
    const double outer_bound_lat_acc =
        ((lc_state.stage() == LaneChangeStage::LCS_EXECUTING) ||
         drive_passage.GetIsChangeAbnormal())
            ? kMaxOuterBoundLaneChangeLatAccel
            : kMaxLaneChangeCancelLatAccel;
    const auto inner_kinematic_boundary = BuildPathBoundaryFromAvKinematics(
        drive_passage, plan_start_point, vehicle_geom, cur_sl, sl_box, lc_state,
        s_vec, used_target_lane_offset, inner_bound_lat_acc,
        lane_change_pause_or_push);
    const auto outer_kinematic_boundary = BuildPathBoundaryFromAvKinematics(
        drive_passage, plan_start_point, vehicle_geom, cur_sl, sl_box, lc_state,
        s_vec, used_target_lane_offset, outer_bound_lat_acc,
        lane_change_pause_or_push);
    const std::vector<BoundaryDebugView> raw_boundary_views = {
        {"base", &boundary},
        {"solid", &solid_boundary},
        {"curb", &curb_boundary},
        {"inner_kinematic", &inner_kinematic_boundary},
        {"outer_kinematic", &outer_kinematic_boundary}};
    LogBoundarySnapshot("raw_boundaries", drive_passage, s_vec, center_l,
                        raw_boundary_views);

    PathBoundary outer_boundary = boundary;
    outer_boundary.InnerClampBy(outer_kinematic_boundary);
    {
        const std::vector<BoundaryDebugView> views = {
            {"inner", &boundary}, {"outer", &outer_boundary}};
        LogBoundarySnapshot("after_outer_kinematic_clamp", drive_passage, s_vec,
                            center_l, views);
    }

    if (!(borrow_lane_boundary || lane_change_pause_or_push)) {
        const bool lc_left = lc_state.lc_left();
        double extend_outer_bound_width = 0.0;
        if (drive_passage.GetIsChangeAbnormal()) {
            extend_outer_bound_width = 2.0 * kExtendOuterBoundWidth;
            extend_outer_bound_width = 2.0 * kExtendOuterBoundWidth;
        } else {
            extend_outer_bound_width = kExtendOuterBoundWidth;
        }
        outer_boundary = ExtendBoundaryBy(
            drive_passage, std::move(outer_boundary), is_lane_changing, lc_left,
            extend_outer_bound_width);

        if (is_lane_changing) {
            boundary.InnerClampBy(outer_boundary);
        }
        const std::vector<BoundaryDebugView> views = {
            {"inner", &boundary}, {"outer", &outer_boundary}};
        LogBoundarySnapshot("after_outer_extend", drive_passage, s_vec,
                            center_l, views);
    }

    if (lane_change_pause_or_push) {
        outer_boundary = ShrinkPathBoundaryForLaneChangePause(
            vehicle_geom, sl_box, lc_state, std::move(outer_boundary),
            used_target_lane_offset, center_l);
        outer_boundary.InnerClampBy(inner_kinematic_boundary);
        boundary.OuterClampBy(outer_boundary);
        const std::vector<BoundaryDebugView> views = {
            {"inner", &boundary},
            {"outer", &outer_boundary},
            {"inner_kinematic", &inner_kinematic_boundary}};
        LogBoundarySnapshot("after_lc_pause_or_push_shrink", drive_passage,
                            s_vec, center_l, views);
    }
    if (lc_state.stage() == LaneChangeStage::LCS_PAUSE) {
        PathBoundary pause_extend_boundary = boundary;
        pause_extend_boundary = ExtendPathBoundaryForLaneChangePause(
            lc_state, half_target_lane_width, std::move(pause_extend_boundary),
            smooth_center_offset);
        boundary.InnerClampBy(pause_extend_boundary);
        const std::vector<BoundaryDebugView> views = {
            {"inner", &boundary},
            {"pause_extend", &pause_extend_boundary},
            {"outer", &outer_boundary}};
        LogBoundarySnapshot("after_lc_pause_extend", drive_passage, s_vec,
                            center_l, views);
    }

    SmoothBoundary(s_vec, right_split_range, true, boundary.mutable_left_vec());
    SmoothBoundary(s_vec, left_split_range, false,
                   boundary.mutable_right_vec());
    SmoothBoundary(s_vec, right_split_range, true,
                   outer_boundary.mutable_left_vec());
    SmoothBoundary(s_vec, left_split_range, false,
                   outer_boundary.mutable_right_vec());
    {
        const std::vector<BoundaryDebugView> views = {
            {"inner", &boundary}, {"outer", &outer_boundary}};
        LogBoundarySnapshot("after_smooth", drive_passage, s_vec, center_l,
                            views);
    }

    if (!borrow_lane_boundary) {
        boundary.SoftOuterClampBy(solid_boundary, left_split_range,
                                  right_split_range);

        bool is_on_ramp = drive_passage.GetIsOnRamp();
        // TODO:(xc)
        // const auto &cur_lane = psmm.GetNearestLane(Vec2d(
        //     plan_start_point.path_point().x(),
        //     plan_start_point.path_point().y()));
        // const bool is_on_ramp =
        //     cur_lane ? (cur_lane->type() == LaneType::LANE_RAMP ? true :
        //     false)
        //              : false;
        if ((static_cast<ads_x::planning::VehicleDriveStyle>(
                    ads_x::planning::VehicleBehaviorHelper::instance()
                        ->GetDriveStyle()) !=
                ads_x::planning::VehicleDriveStyle::KDriveStyleAggressive) ||
            is_on_ramp || is_lane_changing || split_type) {
            outer_boundary.SoftOuterClampBy(solid_boundary, left_split_range,
                                            right_split_range);
        }
        outer_boundary.InnerClampBy(outer_kinematic_boundary);
        if (is_lane_changing || lane_change_pause_or_push) {
            boundary.InnerClampBy(inner_kinematic_boundary);
        }
        const std::vector<BoundaryDebugView> views = {
            {"inner", &boundary},
            {"outer", &outer_boundary},
            {"solid", &solid_boundary},
            {"outer_kinematic", &outer_kinematic_boundary},
            {"inner_kinematic", &inner_kinematic_boundary}};
        LogBoundarySnapshot("after_solid_and_kinematic_clamp", drive_passage,
                            s_vec, center_l, views);
    }
    boundary.OuterClampBy(curb_boundary);
    outer_boundary.OuterClampBy(curb_boundary);
    PathBoundary opt_outer_boundary = outer_boundary;
    {
        const std::vector<BoundaryDebugView> views = {
            {"inner", &boundary},
            {"outer", &outer_boundary},
            {"opt_outer", &opt_outer_boundary},
            {"curb", &curb_boundary}};
        LogBoundarySnapshot("after_curb_clamp", drive_passage, s_vec, center_l,
                            views);
    }

    const double clamp_width = vehicle_geom.width() * 0.5;
    for (int i = 0; i < n; ++i) {
        if ((i > clamp_idx - 3 && !is_uturn) ||
            (boundary.left(i) - boundary.right(i) <
                clamp_width + ads_x::planning::Constants::ZERO)) {
            if (i <= 1) {
                if (boundary.left(i) - boundary.right(i) <
                    clamp_width + ads_x::planning::Constants::ZERO) {
                    return absl::InternalError(absl::StrCat(
                        "Path boundary width insufficient at station i=", i,
                        ": left=", boundary.left(i),
                        ", right=", boundary.right(i), ", width=",
                        boundary.left(i) - boundary.right(i), ", required_min=",
                        clamp_width + ads_x::planning::Constants::ZERO,
                        ", vehicle_half_width=", clamp_width,
                        ", clamp_idx=", clamp_idx));
                } else {
                    return absl::InternalError(absl::StrCat(
                        "Path boundary truncated too early at station i=", i,
                        ": left=", boundary.left(i),
                        ", right=", boundary.right(i),
                        ", width=", boundary.left(i) - boundary.right(i),
                        ", clamp_idx=", clamp_idx));
                }
            }
            s_vec.resize(i);
            center_l.resize(i);
            boundary.EraseFrom(i);
            outer_boundary.EraseFrom(i);
            opt_outer_boundary.EraseFrom(i);
            break;
        }
    }
    {
        const std::vector<BoundaryDebugView> views = {
            {"inner", &boundary},
            {"outer", &outer_boundary},
            {"opt_outer", &opt_outer_boundary}};
        LogBoundarySnapshot("after_truncate_check", drive_passage, s_vec,
                            center_l, views);
    }

    constexpr double KSafetyBuffer = 0.15;
    std::vector<double> c_right_bound_vec, c_left_bound_vec;
    c_right_bound_vec.reserve(n);
    c_left_bound_vec.reserve(n);
    double center_bound_left_width = KSafetyBuffer + clamp_width;
    double center_bound_right_width = KSafetyBuffer + clamp_width;
    if (lane_change_pause_or_push) {
        center_bound_left_width =
            (lc_state.lc_left() ||
             (lc_state.push_state() == PushState::LEFT_PUSH) ||
             (lc_state.push_state() == PushState::CONGESTION_LEFT_PUSH))
                ? 0.0
                : center_bound_left_width;

        center_bound_right_width =
            (!lc_state.lc_left() ||
             (lc_state.push_state() == PushState::RIGHT_PUSH) ||
             (lc_state.push_state() == PushState::CONGESTION_RIGHT_PUSH))
                ? 0.0
                : center_bound_right_width;
    }

    const bool is_left_split =
        (((left_split_range.first == -1) && (left_split_range.second == -1)) ||
         (left_split_range.first == left_split_range.second))
            ? false
            : true;
    const bool is_right_split =
        (((right_split_range.first == -1) && (right_split_range.second == -1)) ||
         (right_split_range.first == right_split_range.second))
            ? false
            : true;
    for (int i = 0; i < n; i++) {
        c_right_bound_vec.push_back(0.0);
        c_left_bound_vec.push_back(0.0);
        double &right = c_right_bound_vec.back();
        double &left = c_left_bound_vec.back();
        if (is_left_split && (i >= left_split_range.first) &&
            (i <= left_split_range.second)) {
            right = center_l[i] - center_bound_right_width;
            left = center_l[i];
        } else if (is_right_split && (i >= right_split_range.first) &&
                   (i <= right_split_range.second)) {
            right = center_l[i];
            left = center_l[i] + center_bound_right_width;
        } else {
            right = center_l[i] - center_bound_right_width;
            left = center_l[i] + center_bound_left_width;
        }
    }
    PathBoundary center_boundary(std::move(c_right_bound_vec),
                                 std::move(c_left_bound_vec));
    {
        const std::vector<BoundaryDebugView> views = {
            {"inner_before_center", &boundary},
            {"center", &center_boundary},
            {"curb", &curb_boundary}};
        LogBoundarySnapshot("before_center_clamp", drive_passage, s_vec,
                            center_l, views);
    }
    boundary.InnerClampBy(center_boundary);
    boundary.OuterClampBy(curb_boundary);
    {
        const std::vector<BoundaryDebugView> views = {
            {"inner", &boundary},
            {"center", &center_boundary},
            {"curb", &curb_boundary}};
        LogBoundarySnapshot("after_center_clamp", drive_passage, s_vec,
                            center_l, views);
    }

    std::vector<Vec2d> center_xy;
    for (int i = 0; i < boundary.size(); ++i) {
        const auto &station = drive_passage.station(StationIndex(i));
        center_xy.push_back(station.lat_point(center_l[i]));
    }
    if (!is_lane_changing && !drive_passage.GetIsChangeAbnormal()) {
        outer_boundary = ShrinkPathBoundaryForObject(
            drive_passage, st_traj_mgr, plan_start_point, s_vec, center_l,
            center_xy, boundary, curb_boundary, std::move(outer_boundary),
            sl_box, borrow_lane_boundary);
        if (borrow_lane_boundary) {
            boundary.OuterClampBy(outer_boundary);
        }
        outer_boundary.InnerClampBy(outer_kinematic_boundary);
        outer_boundary.OuterClampBy(curb_boundary);
        const std::vector<BoundaryDebugView> views = {
            {"inner", &boundary},
            {"outer", &outer_boundary},
            {"outer_kinematic", &outer_kinematic_boundary},
            {"curb", &curb_boundary}};
        LogBoundarySnapshot("after_object_shrink", drive_passage, s_vec,
                            center_l, views);
    }

    outer_boundary =
        PathBoundary(PostprocessOuterBoundary(s_vec, boundary.right_vec(),
                                              outer_boundary.right_vec()),
                     PostprocessOuterBoundary(s_vec, boundary.left_vec(),
                                              outer_boundary.left_vec()));
    opt_outer_boundary =
        PathBoundary(PostprocessOuterBoundary(s_vec, boundary.right_vec(),
                                              opt_outer_boundary.right_vec()),
                     PostprocessOuterBoundary(s_vec, boundary.left_vec(),
                                              opt_outer_boundary.left_vec()));

    outer_boundary.InnerClampBy(boundary);
    opt_outer_boundary.InnerClampBy(boundary);
    {
        const std::vector<BoundaryDebugView> views = {
            {"inner", &boundary},
            {"outer", &outer_boundary},
            {"opt_outer", &opt_outer_boundary}};
        LogBoundarySnapshot("final", drive_passage, s_vec, center_l, views);
    }

    // 变道时仅压缩 opt_outer_boundary（A* 搜索约束），
    // 不修改 inner/outer_boundary，避免影响 optimizer 求解导致变道猛。
    // 左变道：opt_outer 的 right 压到自车右边缘，防止 A* 搜索向右侧车道扩散。
    // 右变道：opt_outer 的 left 压到自车左边缘，防止 A* 搜索向左侧车道扩散。

    // 压缩 opt_outer_boundary 放在 InnerClampBy 之后，防止被 min 操作还原。
    // 仅影响 A* 搜索（QueryOptBoundaryL），optimizer 用的 outer_boundary 不变。
    constexpr double kLcBoundaryBuffer = 0.30;
    if (adjust_astar_search_boundary_for_lc) {
        const bool lc_left = lc_state.lc_left();
        for (int i = 0; i < opt_outer_boundary.size(); ++i) {
            if (lc_left) {
                const double limit =
                    cur_sl.l - vehicle_geom.width() * 0.5 - kLcBoundaryBuffer;
                opt_outer_boundary.OuterClampRightByIndex(i, limit);
            } else {
                const double limit =
                    cur_sl.l + vehicle_geom.width() * 0.5 + kLcBoundaryBuffer;
                opt_outer_boundary.OuterClampLeftByIndex(i, limit);
            }
        }
    }

#if 0
    // debug start
    // Convert boundary, outer_boundary, and opt_outer_boundary to BgPoint and
    // print
    std::vector<BgPoint> boundary_left_points, boundary_right_points;
    std::vector<BgPoint> outer_boundary_left_points,
        outer_boundary_right_points;
    std::vector<BgPoint> opt_outer_boundary_left_points,
        opt_outer_boundary_right_points;

    for (int i = 0; i < boundary.size(); ++i) {
        const auto &station = drive_passage.station(StationIndex(i));
        // Convert left and right boundary points to BgPoint
        Vec2d left_xy = station.lat_point(boundary.left(i));
        Vec2d right_xy = station.lat_point(boundary.right(i));
        boundary_left_points.emplace_back(left_xy.x(), left_xy.y());
        boundary_right_points.emplace_back(right_xy.x(), right_xy.y());

        // Convert outer_boundary points to BgPoint
        Vec2d outer_left_xy = station.lat_point(outer_boundary.left(i));
        Vec2d outer_right_xy = station.lat_point(outer_boundary.right(i));
        outer_boundary_left_points.emplace_back(outer_left_xy.x(),
                                                outer_left_xy.y());
        outer_boundary_right_points.emplace_back(outer_right_xy.x(),
                                                 outer_right_xy.y());

        // Convert opt_outer_boundary points to BgPoint
        Vec2d opt_outer_left_xy = station.lat_point(opt_outer_boundary.left(i));
        Vec2d opt_outer_right_xy =
            station.lat_point(opt_outer_boundary.right(i));
        opt_outer_boundary_left_points.emplace_back(opt_outer_left_xy.x(),
                                                    opt_outer_left_xy.y());
        opt_outer_boundary_right_points.emplace_back(opt_outer_right_xy.x(),
                                                     opt_outer_right_xy.y());
    }

    // Print boundary points
    AD_LDEBUG(PP) << "Boundary Left Points:";
    for (const auto &point : boundary_left_points) {
        AD_LDEBUG(PP) << "  (" << point.x() << ", " << point.y() << ")";
    }
    AD_LDEBUG(PP) << "Boundary Right Points:";
    for (const auto &point : boundary_right_points) {
        AD_LDEBUG(PP) << "  (" << point.x() << ", " << point.y() << ")";
    }

    // Print outer_boundary points
    AD_LDEBUG(PP) << "Outer Boundary Left Points:";
    for (const auto &point : outer_boundary_left_points) {
        AD_LDEBUG(PP) << "  (" << point.x() << ", " << point.y() << ")";
    }
    AD_LDEBUG(PP) << "Outer Boundary Right Points:";
    for (const auto &point : outer_boundary_right_points) {
        AD_LDEBUG(PP) << "  (" << point.x() << ", " << point.y() << ")";
    }

    // Print opt_outer_boundary points
    AD_LDEBUG(PP) << "Optimized Outer Boundary Left Points:";
    for (const auto &point : opt_outer_boundary_left_points) {
        AD_LDEBUG(PP) << "  (" << point.x() << ", " << point.y() << ")";
    }
    AD_LDEBUG(PP) << "Optimized Outer Boundary Right Points:";
    for (const auto &point : opt_outer_boundary_right_points) {
        AD_LDEBUG(PP) << "  (" << point.x() << ", " << point.y() << ")";
    }
// debug end
#endif

    return BuildPathSlBoundary(drive_passage, std::move(s_vec),
                               std::move(center_l), std::move(boundary),
                               std::move(outer_boundary),
                               std::move(opt_outer_boundary));
}

}  // namespace planning
}  // namespace pnc_x
