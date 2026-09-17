

#include "scheduler/path_boundary_builder_helper.h"

#include <boost/optional.hpp>
#include <cmath>
#include <limits>

#include <absl/container/flat_hash_map.h>
#include <absl/hash/hash.h>
#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <absl/strings/str_cat.h>
// #include <gflags/gflags.h>

#include "maps/lane_path.h"
#include "maps/lane_point.h"
#include "maps/map_or_die_macros.h"
#include "math/frenet_frame.h"
#include "math/geometry/box2d.h"
#include "math/geometry/util.h"
#include "math/piecewise_linear_function.h"
#include "math/util.h"
#include "object/spacetime_object_state.h"
#include "object/spacetime_object_trajectory.h"
#include "plan/planner_defs.h"

#include "util/loop_guard.h"
#include "util/map_util.h"
#include "util/status_builder.h"
#include "util/status_macros.h"

// DEFINE_bool(
//     planner_enable_path_boundary_debug, false,
//     "Enable debug for path boundary. Will draw infos on canvas if enabled.");

bool FLAGS_planner_enable_path_boundary_debug = false;

namespace pnc_x {
namespace planning {
namespace {

constexpr double kObjectBuffer = 0.55;
constexpr double kVirtualStationHalfWidth = 3.0;
constexpr double kBackWardTimeBuffer = 1.0;
constexpr double kFrontTimeBuffer = 1.5;
constexpr double kPrePursuitBuffer = 3.0;
constexpr double kPostPursuitBuffer = 4.0;
constexpr double kBorrowPrePursuitBuffer = 4.0;
constexpr double kBorrowPostPursuitBuffer = 5.0;
constexpr double kLkPursuitTimeConsider = 3.0;
constexpr double kBorrowPursuitTimeConsider = 4.0;
constexpr double kBorrowLaneOffset = 3.9;
constexpr double kEgoLatBuffer = 0.3;
constexpr double kLcPauseEgoLatBuffer = 0.75;

constexpr double kComfortLaneChangeCancelLatAccel = 0.5;
constexpr double kMaxComfortLatJerk = 1.0;
constexpr int kAvTrajPointsMinSize = 5;
constexpr double kMinKinematicTrajLonSpeed = 3.0;
constexpr double kMinKinematicBoundaryProtectedZone = 15.0;

constexpr double kMaxLaneChangePauseRefCenterStep = 0.7;

constexpr double kIntersectionTurningMaxHalfLaneWidth = 3.5;

boost::optional<double> FindPursuitTime(absl::Span<const double> av_s_vec,
                                        absl::Span<const double> av_t_vec,
                                        absl::Span<const double> obj_s_vec,
                                        absl::Span<const double> obj_t_vec,
                                        const double &obj_length) {
    XCHECK_EQ(av_s_vec.size(), av_t_vec.size());
    XCHECK_EQ(obj_s_vec.size(), obj_t_vec.size());
    const double kRearToRearAxle = 1.15, kFrontToRearAxle = 4.10;
    const double half_obj_length = 0.5 * obj_length;

    for (int i = 0; i < av_t_vec.size() - 1; ++i) {
        for (int j = 0; j < obj_t_vec.size() - 1; ++j) {
            if (av_t_vec[i + 1] < obj_t_vec[j] ||
                av_t_vec[i] > obj_t_vec[j + 1]) {
                continue;
            }
            const Segment2d av_s_t(Vec2d(av_t_vec[i], av_s_vec[i]),
                                   Vec2d(av_t_vec[i + 1], av_s_vec[i + 1]));
            Vec2d intersect_pt;
            const bool has_intersect = av_s_t.GetIntersect(
                Segment2d(Vec2d(obj_t_vec[j], obj_s_vec[j]),
                          Vec2d(obj_t_vec[j + 1], obj_s_vec[j + 1])),
                &intersect_pt);
            if (has_intersect) {
                return intersect_pt.x();
            } else {
                if (std::fmin(av_s_vec[i] + kFrontToRearAxle,
                              obj_s_vec[j] + half_obj_length) >
                    std::fmax(av_s_vec[i] - kRearToRearAxle,
                              obj_s_vec[j] - half_obj_length)) {
                    return av_t_vec[i];
                } else if (std::fmin(av_s_vec[i + 1] + kFrontToRearAxle,
                                     obj_s_vec[j + 1] + half_obj_length) >
                           std::fmax(av_s_vec[i + 1] - kRearToRearAxle,
                                     obj_s_vec[j + 1] - half_obj_length)) {
                    return av_t_vec[i + 1];
                }
            }
        }
    }
    return boost::none;
}

absl::StatusOr<PiecewiseLinearFunction<double, double>>
GenerateAvTrajAlongRefCenterLine(
    const DrivePassage &drive_passage,
    const ApolloTrajectoryPointProto &plan_start_point,
    absl::Span<const Vec2d> center_xy_vec) {
    ASSIGN_OR_RETURN(const auto center_frame,
                     BuildBruteForceFrenetFrame(center_xy_vec, true));
    const auto cur_sl = center_frame.XYToSL(
        Vec2dFromApolloTrajectoryPointProto(plan_start_point));

    std::vector<double> vec_t, vec_s;
    vec_t.reserve(kTrajectorySteps);
    vec_s.reserve(kTrajectorySteps);

    double center_s = cur_sl.s;
    const double speed = plan_start_point.v();
    for (double t = 0; t <= kTrajectoryTimeHorizon; t += kTrajectoryTimeStep) {
        const auto center_xy = center_frame.SLToXY({center_s, 0.0});
        const auto dp_sl = drive_passage.QueryFrenetCoordinateAt(center_xy);
        if (!dp_sl.ok()) break;

        vec_t.push_back(t);
        vec_s.push_back(dp_sl->s);
        center_s += kTrajectoryTimeStep * speed;
    }

    if (vec_s.size() > 1) {
        return PiecewiseLinearFunction<double, double>(vec_s, vec_t);
    } else {
        return absl::InternalError("");
    }
}

absl::StatusOr<PiecewiseLinearFunction<double, double>>
GenerateConstLateralAccelConstSpeedTraj(
    const DrivePassage &drive_passage,
    const ApolloTrajectoryPointProto &plan_start_point,
    const FrenetCoordinate &cur_sl,
    double target_lane_offset,
    double max_lat_accel) {
    ASSIGN_OR_RETURN(const auto lane_tangent,
                     drive_passage.QueryTangentAtS(cur_sl.s),
                     _ << "Unable to find lane tangent at current s.");

    std::vector<double> vec_l, vec_s;
    vec_l.reserve(kTrajectorySteps);
    vec_s.reserve(kTrajectorySteps);

    constexpr double kReachTargetLaneThreshold = 0.1;
    constexpr double kZeroLateralVelThreshold = 0.01;
    constexpr double kDt = kTrajectoryTimeStep;
    const auto heading_tangent =
        Vec2d::FastUnitFromAngle(plan_start_point.path_point().theta());
    double s, l, lat_v, lat_a, speed;
    s = cur_sl.s;
    l = cur_sl.l;
    speed = plan_start_point.v();
    lat_v = speed * lane_tangent.CrossProd(heading_tangent);
    lat_a = (plan_start_point.a() * lane_tangent.CrossProd(heading_tangent)) +
            (speed * lane_tangent.Dot(heading_tangent) * speed *
             plan_start_point.path_point().kappa());
    lat_v = std::fabs(lat_v) < kZeroLateralVelThreshold ? 0.0 : lat_v;
    speed = std::max(speed, kMinKinematicTrajLonSpeed);
    vec_l.push_back(l);
    vec_s.push_back(s);

    const double expect_lat_a =
        -std::copysign(max_lat_accel, l - target_lane_offset);

    const int const_lat_jerk_steps =
        FloorToInt(std::abs(expect_lat_a - lat_a) / kMaxComfortLatJerk / kDt);
    for (int i = 0; i < const_lat_jerk_steps; ++i) {
        l += lat_v * kDt;
        s += speed * kDt;
        lat_v += lat_a * kDt;
        lat_a += std::copysign(kMaxComfortLatJerk, expect_lat_a - lat_a) * kDt;
        vec_l.push_back(l);
        vec_s.push_back(s);
    }

    lat_a = -std::copysign(max_lat_accel, l - target_lane_offset);
    for (int i = 0; i < kTrajectorySteps - const_lat_jerk_steps - 1; ++i) {
        l += lat_v * kDt;
        s += speed * kDt;
        lat_v += lat_a * kDt;

        if ((std::fabs(l - target_lane_offset) < kReachTargetLaneThreshold &&
             std::fabs(lat_v) < kZeroLateralVelThreshold) ||
            ((l - target_lane_offset) * (vec_l.back() - target_lane_offset)) <
                0.0) {
            break;
        }
        vec_l.push_back(l);
        vec_s.push_back(s);
    }

    if (vec_s.size() < kAvTrajPointsMinSize) {
        return absl::NotFoundError("");
    }

    const int extend_traj_size = CeilToInt(vec_s.size() * 0.1);
    for (int i = 0; i < extend_traj_size; ++i) {
        if (vec_s.size() >= kTrajectorySteps) break;
        vec_l.push_back(target_lane_offset);
        vec_s.push_back(s);
        s += speed * kDt;
    }
    return PiecewiseLinearFunction<double, double>(vec_s, vec_l);
}

PathBoundary BuildBoundaryForStationaryObject(const DrivePassage &drive_passage,
                                              absl::Span<const double> center_l,
                                              const FrenetBox &obj_fbox,
                                              absl::Span<const double> s_vec,
                                              PathBoundary boundary) {
    const int n = boundary.size();
    std::vector<double> left_bound_vec, right_bound_vec;
    left_bound_vec.reserve(n);
    right_bound_vec.reserve(n);

    auto index = std::lower_bound(s_vec.begin(), s_vec.end(), obj_fbox.s_max) -
                 s_vec.begin();
    if (index > n - 1) {
        index = n - 1;
    }
    auto index_near = index;
    auto index_far = index_near;
    auto loop_guard1 = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (index_near > 0 && s_vec[index_near] >= obj_fbox.s_min &&
           loop_guard1) {
        --index_near;
    }
    auto loop_guard2 = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (index_far < n - 1 && s_vec[index_far] <= obj_fbox.s_max &&
           loop_guard2) {
        ++index_far;
    }

    if (obj_fbox.l_max < center_l[index]) {
        const double lat_offset = obj_fbox.l_max;
        for (int i = index_near; i <= index_far; ++i) {
            boundary.OuterClampRightByIndex(i, lat_offset + kObjectBuffer);
        }
    } else if (obj_fbox.l_min > center_l[index]) {
        const double lat_offset = obj_fbox.l_min;
        for (int i = index_near; i <= index_far; ++i) {
            boundary.OuterClampLeftByIndex(i, lat_offset - kObjectBuffer);
        }
    }

    return boundary;
}

PathBoundary BuildBoundaryForDynamicObject(
    const DrivePassage &drive_passage,
    absl::Span<const double> center_l,
    const SpacetimeObjectTrajectory &traj,
    const PiecewiseLinearFunction<double, double> &av_t_s,
    absl::Span<const double> s_vec,
    const PathBoundary &inner_boundary,
    const PathBoundary &curb_boundary,
    PathBoundary boundary,
    const bool &borrow_lane) {
    const auto &av_s_vec = av_t_s.x();
    const auto &av_t_vec = av_t_s.y();
    const int num_stations = s_vec.size();
    const int time_num_steps = traj.states().size();

    absl::flat_hash_map<int, FrenetBox> frenet_box_map;
    std::vector<double> obj_s_vec, obj_t_vec, obj_max_l_vec, obj_min_l_vec;
    obj_s_vec.reserve(time_num_steps);
    obj_t_vec.reserve(time_num_steps);
    obj_max_l_vec.reserve(time_num_steps);
    obj_min_l_vec.reserve(time_num_steps);

    std::vector<Box2d> box_vec;
    box_vec.reserve(time_num_steps);
    for (const auto &state : traj.states()) {
        box_vec.push_back(state.box);
    }
    ASSIGN_OR_RETURN(auto fbox_vec,
                     drive_passage.BatchQueryFrenetBoxes(box_vec, false),
                     boundary);

    for (int i = 0; i < time_num_steps; ++i) {
        if (!fbox_vec[i].has_value()) continue;

        auto fbox = fbox_vec[i].value();

        const auto index =
            std::lower_bound(s_vec.begin(), s_vec.end(), fbox.s_min) -
            s_vec.begin();
        if (index == s_vec.size()) continue;

        if (fbox.l_min < center_l[index] && fbox.l_max > center_l[index]) {
            continue;
        }
        obj_s_vec.push_back(0.5 * (fbox.s_max + fbox.s_min));
        obj_t_vec.push_back(i * kTrajectoryTimeStep);
        obj_max_l_vec.push_back(fbox.l_max);
        obj_min_l_vec.push_back(fbox.l_min);

        frenet_box_map[i] = fbox;
    }

    double obj_length = traj.states().front().box.length();
    if (av_t_vec.size() > 1 && obj_t_vec.size() > 1) {
        const auto pursuit_time = FindPursuitTime(av_s_vec, av_t_vec, obj_s_vec,
                                                  obj_t_vec, obj_length);

        if (pursuit_time.has_value()) {
            const PiecewiseLinearFunction<double, double> obj_max_l_t(
                obj_t_vec, obj_max_l_vec);
            const PiecewiseLinearFunction<double, double> obj_min_l_t(
                obj_t_vec, obj_min_l_vec);
            const int pursuit_idx =
                static_cast<int>(*pursuit_time / kTrajectoryTimeStep);
            const double pre_pursuit_buffer =
                borrow_lane ? kBorrowPrePursuitBuffer : kPrePursuitBuffer;
            const double post_pursuit_buffer =
                borrow_lane ? kBorrowPostPursuitBuffer : kPostPursuitBuffer;
            const int pursuit_min_idx = std::max(
                0, pursuit_idx - static_cast<int>(pre_pursuit_buffer /
                                                  kTrajectoryTimeStep));
            const int pursuit_max_idx =
                std::min(time_num_steps - 1,
                         pursuit_idx + static_cast<int>(post_pursuit_buffer /
                                                        kTrajectoryTimeStep));
            for (int i = 0; i < num_stations; ++i) {
                const auto s = s_vec[i];
                if (s < av_s_vec.front() || s > av_s_vec.back()) {
                    continue;
                }
                const double av_arrive_t = av_t_s(s);
                const int av_arrive_t_index =
                    static_cast<int>(av_arrive_t / kTrajectoryTimeStep);
                if (av_arrive_t_index < 0 ||
                    av_arrive_t_index >= time_num_steps ||
                    av_arrive_t_index < pursuit_min_idx ||
                    av_arrive_t_index > pursuit_max_idx) {
                    continue;
                }
                const double pursuit_max_l = obj_max_l_t(av_arrive_t);
                const double pursuit_min_l = obj_min_l_t(av_arrive_t);
                const double pursuit_l_diff = pursuit_max_l - pursuit_min_l;
                if (borrow_lane) {
                    const auto lane_boundary_info =
                        drive_passage.QueryEnclosingLaneBoundariesAtS(s);
                    if (lane_boundary_info.left.has_value() &&
                        lane_boundary_info.right.has_value()) {
                        const double left = lane_boundary_info.left->lat_offset;
                        const double right =
                            lane_boundary_info.right->lat_offset;
                        if (pursuit_max_l < center_l[i] &&
                            std::fabs(curb_boundary.right(i) - right) >
                                pursuit_l_diff) {
                            boundary.OuterClampRightByIndex(
                                i, pursuit_max_l + kObjectBuffer);
                        }
                        if (pursuit_min_l > center_l[i] &&
                            std::fabs(curb_boundary.left(i) - left) >
                                pursuit_l_diff) {
                            boundary.OuterClampLeftByIndex(
                                i, pursuit_min_l - kObjectBuffer);
                        }
                    }
                } else {
                    if (pursuit_max_l < center_l[i] &&
                        std::fabs(curb_boundary.right(i) -
                                  inner_boundary.right(i)) > pursuit_l_diff) {
                        boundary.OuterClampRightByIndex(
                            i, pursuit_max_l + kObjectBuffer);
                    }
                    if (pursuit_min_l > center_l[i] &&
                        std::fabs(curb_boundary.left(i) -
                                  inner_boundary.left(i)) > pursuit_l_diff) {
                        boundary.OuterClampLeftByIndex(
                            i, pursuit_min_l - kObjectBuffer);
                    }
                }
            }
        }
    }

    return boundary;
}

}  // namespace

PathBoundary::PathBoundary(std::vector<double> right, std::vector<double> left)
    : right_(std::move(right)), left_(std::move(left)) {}

const std::vector<double> &PathBoundary::right_vec() const { return right_; }

const std::vector<double> &PathBoundary::left_vec() const { return left_; }

std::vector<double> *PathBoundary::mutable_right_vec() { return &right_; }

std::vector<double> *PathBoundary::mutable_left_vec() { return &left_; }

std::vector<double> &&PathBoundary::moved_left_vec() {
    return std::move(left_);
}
std::vector<double> &&PathBoundary::moved_right_vec() {
    return std::move(right_);
}

double PathBoundary::right(int i) const { return right_[i]; }

double PathBoundary::left(int i) const { return left_[i]; }

void PathBoundary::ExtendLeftTo(double uniform_left) {
    for (auto &left_l : left_) {
        left_l = std::max(left_l, uniform_left);
    }
}

void PathBoundary::ExtendRightTo(double uniform_right) {
    for (auto &right_l : right_) {
        right_l = std::min(right_l, uniform_right);
    }
}

void PathBoundary::ShiftLeftBy(double offset) {
    for (auto &left_l : left_) {
        left_l += offset;
    }
}

void PathBoundary::ShiftRightBy(double offset) {
    for (auto &right_l : right_) {
        right_l += offset;
    }
}

void PathBoundary::ShiftLeftByIndex(int index, double offset) {
    left_[index] += offset;
}

void PathBoundary::ShiftRightByIndex(int index, double offset) {
    right_[index] += offset;
}

void PathBoundary::OuterClampRightByIndex(int index, double right_l) {
    right_[index] = std::max(right_[index], right_l);
}

void PathBoundary::OuterClampLeftByIndex(int index, double left_l) {
    left_[index] = std::min(left_[index], left_l);
}

void PathBoundary::InnerClampRightByIndex(int index, double right_l) {
    right_[index] = std::min(right_[index], right_l);
}

void PathBoundary::InnerClampLeftByIndex(int index, double left_l) {
    left_[index] = std::max(left_[index], left_l);
}

void PathBoundary::OuterClampBy(const PathBoundary &other) {
    const int n = static_cast<int>(left_.size());
    XCHECK_EQ(n, right_.size());
    XCHECK_LE(n, other.right_vec().size());
    for (int i = 0; i < n; ++i) {
        left_[i] = std::min(left_[i], other.left(i));
        right_[i] = std::max(right_[i], other.right(i));
    }
}

void PathBoundary::SoftOuterClampBy(
    const PathBoundary &other,
    const std::pair<int, int> &left_split_range,
    const std::pair<int, int> &right_split_range) {
    const int n = static_cast<int>(left_.size());
    XCHECK_EQ(n, right_.size());
    XCHECK_LE(n, other.right_vec().size());
    const double ramp_factor = 0.25;
    double last_left = 0.0;
    double last_right = 0.0;
    for (int i = 0; i < n; ++i) {
        double left_cmp =
            right_split_range.first > 0 && i >= right_split_range.first &&
                    i <= right_split_range.second && left_[i] > other.left(i) &&
                    left_[i] < last_left + 0.06
                ? std::fmax(left_[i - 1] - ramp_factor, other.left(i))
                : other.left(i);
        double right_cmp =
            left_split_range.first > 0 && i >= left_split_range.first &&
                    i <= left_split_range.second && right_[i] < other.left(i) &&
                    right_[i] > last_right - 0.06
                ? std::fmin(right_[i - 1] + ramp_factor, other.right(i))
                : other.right(i);
        last_left = left_[i];
        last_right = right_[i];
        left_[i] = std::fmin(left_[i], left_cmp);
        right_[i] = std::fmax(right_[i], right_cmp);
    }
}

void PathBoundary::InnerClampBy(const PathBoundary &other) {
    const int n = static_cast<int>(left_.size());
    XCHECK_EQ(n, right_.size());
    XCHECK_LE(n, other.size());
    for (int i = 0; i < n; ++i) {
        left_[i] = std::max(left_[i], other.left(i));
        right_[i] = std::min(right_[i], other.right(i));
    }
}

void PathBoundary::EraseFrom(int index) {
    XCHECK_LT(index, size());
    left_.resize(index);
    right_.resize(index);
}

int PathBoundary::size() const { return left_.size(); }

bool IsTurningLanePath(const DrivePassage &drive_passage,
                       mapping::ElementId lane_id) {
    const auto &lanes_map = drive_passage.GetLaneMap();
    if (lanes_map.find(lane_id) == lanes_map.end()) {
        return false;
    }
    const auto &lane_info = lanes_map.at(lane_id);

    // TODO:(xc)
    return (lane_info->junction_id() &&
            (lane_info->turn_type() == ads_x::planning::LEFT_TURN ||
             lane_info->turn_type() == ads_x::planning::RIGHT_TURN));
}

PathBoundary BuildPathBoundaryFromTargetLane(
    const DrivePassage &drive_passage,
    const double &ego_v,
    const std::pair<int, int> &left_split_range,
    const std::pair<int, int> &right_split_range,
    double min_half_lane_width,
    bool borrow_lane_boundary) {
    min_half_lane_width -= 0.1;

    const int n = drive_passage.size();
    std::vector<double> left_bound_vec, right_bound_vec;
    left_bound_vec.reserve(n);
    right_bound_vec.reserve(n);
    const double v_factor = boost::algorithm::clamp(ego_v / 10.0, 0.3, 1.0);
    const double split_ramp_factor_by_v = 1.3 * v_factor;
    const double split_entrance_ramp_factor_by_v = 0.8 * v_factor;
    const int split_entrance_range =
        CeilToInt(kDefaultLaneWidth * (1.3 - 0.8) / 0.1);
    const int left_split_th_low =
        left_split_range.first > 0
            ? left_split_range.first +
                  std::min(
                      split_entrance_range,
                      (left_split_range.second - left_split_range.first) / 3)
            : -1;
    const int left_split_th_high =
        left_split_range.first > 0
            ? left_split_range.first +
                  ((left_split_range.second - left_split_range.first) * 2 / 3)
            : -1;
    const int right_split_th_low =
        right_split_range.first > 0
            ? right_split_range.first +
                  std::min(
                      split_entrance_range,
                      (right_split_range.second - right_split_range.first) / 3)
            : -1;
    const int right_split_th_high =
        right_split_range.first > 0
            ? right_split_range.first +
                  ((right_split_range.second - right_split_range.first) * 2 / 3)
            : -1;
    int station_idx = -1;
    for (const auto &station : drive_passage.stations()) {
        ++station_idx;
        left_bound_vec.push_back(0.0);
        right_bound_vec.push_back(0.0);
        auto &left_bound = left_bound_vec.back();
        auto &right_bound = right_bound_vec.back();
        // const auto &lane_info =
        // psmm.FindCurveLaneByIdOrNull(station.lane_id());
        // TODO:(xc)
        if (borrow_lane_boundary &&
            station.turn_type() != ads_x::planning::NO_TURN) {
            right_bound = -kBorrowLaneOffset;
            left_bound = kBorrowLaneOffset;
            continue;
        } else if (station.turn_type() != ads_x::planning::NO_TURN) {
            right_bound = -kVirtualStationHalfWidth;
            left_bound = kVirtualStationHalfWidth;
            if (station.turn_type() == ads_x::planning::U_TURN) {
                right_bound = -kDefaultHalfLaneWidth;
                continue;
            }

            const auto &lanes_map = drive_passage.GetLaneMap();
            if (lanes_map.find(station.lane_id()) == lanes_map.end()) {
                continue;
            }
            const auto &lane_info = lanes_map.at(station.lane_id());

            if (station.turn_type() == ads_x::planning::LEFT_TURN) {
                right_bound = -kDefaultHalfLaneWidth;

                left_bound = (lane_info->left_lane_id() != 0)
                                 ? left_bound
                                 : kIntersectionTurningMaxHalfLaneWidth;
            } else if (station.turn_type() == ads_x::planning::RIGHT_TURN) {
                right_bound = (lane_info->right_lane_id() != 0)
                                  ? right_bound
                                  : -kIntersectionTurningMaxHalfLaneWidth;
                left_bound = kDefaultHalfLaneWidth;
            }
            continue;
        }
#if 0
        ads_x::planning::Lane *lane_info = nullptr;  /////
        if (borrow_lane_boundary &&
            station.turn_type() != ads_x::planning::NO_TURN) {
            right_bound = -kBorrowLaneOffset;
            left_bound = kBorrowLaneOffset;
            continue;
        } else if (station.turn_type() != ads_x::planning::NO_TURN) {
            right_bound = -kVirtualStationHalfWidth;
            left_bound = kVirtualStationHalfWidth;
            if (station.turn_type() == ads_x::planning::U_TURN) {
                right_bound = -kDefaultHalfLaneWidth;
                continue;
            }
            if (lane_info != nullptr) {
                if (station.turn_type() == ads_x::planning::LEFT_TURN) {
                    right_bound = -kDefaultHalfLaneWidth;

                    left_bound = (lane_info->left_lane_id() != 0)
                                     ? left_bound
                                     : kIntersectionTurningMaxHalfLaneWidth;
                } else if (station.turn_type() == ads_x::planning::RIGHT_TURN) {
                    right_bound = (lane_info->right_lane_id() != 0)
                                      ? right_bound
                                      : -kIntersectionTurningMaxHalfLaneWidth;
                    left_bound = kDefaultHalfLaneWidth;
                }
            }
            continue;
        }
#endif

        double right_l = -std::numeric_limits<double>::infinity();
        double left_l = std::numeric_limits<double>::infinity();
        // bool vitrual_boundary = false;
        // constexpr double kEps = 1e-2;  // 判定容差，可按量纲调

        for (const auto &bound : station.boundaries()) {
            // if (std::fabs(bound.lat_offset) >= (kMaxHalfLaneWidth - kEps)) {
            //     vitrual_boundary = true;
            //     break;
            // }
            if (-kMaxHalfLaneWidth < bound.lat_offset &&
                bound.lat_offset < -min_half_lane_width) {
                if (bound.lat_offset > right_l) {
                    right_l = bound.lat_offset;
                }
            }

            if (min_half_lane_width < bound.lat_offset &&
                bound.lat_offset < kMaxHalfLaneWidth) {
                if (bound.lat_offset < left_l) {
                    left_l = bound.lat_offset;
                }
            }
        }

        // if (vitrual_boundary) {
        //   right_bound = -kMaxHalfLaneWidth;
        //   left_bound = kMaxHalfLaneWidth;
        // } else {
        //   right_bound = std::isinf(right_l) ? -kDefaultHalfLaneWidth :
        //   right_l; left_bound = std::isinf(left_l) ? kDefaultHalfLaneWidth :
        //   left_l;
        // }

        right_bound = std::isinf(right_l) ? -kDefaultHalfLaneWidth : right_l;
        left_bound = std::isinf(left_l) ? kDefaultHalfLaneWidth : left_l;

        if (borrow_lane_boundary) {
            const auto &lanes_map = drive_passage.GetLaneMap();
            if (lanes_map.find(station.lane_id()) == lanes_map.end()) {
                right_bound = -kBorrowLaneOffset;
                left_bound = kBorrowLaneOffset;
            }
            const auto &lane_info = lanes_map.at(station.lane_id());

            left_bound =
                lane_info->left_lane_id() != 0 ? kBorrowLaneOffset : left_bound;
            right_bound = lane_info->right_lane_id() != 0 ? -kBorrowLaneOffset
                                                          : right_bound;

#if 0
            if (lane_info != nullptr) {
                left_bound = lane_info->left_lane_id() != 0 ? kBorrowLaneOffset
                                                            : left_bound;
                right_bound = lane_info->right_lane_id() != 0
                                  ? -kBorrowLaneOffset
                                  : right_bound;
            } else {
                right_bound = -kBorrowLaneOffset;
                left_bound = kBorrowLaneOffset;
            }
#endif
            continue;
        }

        if (station.is_splitting()) {
            if (left_split_range.first > 0) {
                if (station_idx < left_split_th_low) {
                    right_bound = std::fmin(
                        right_bound,
                        -kDefaultLaneWidth * split_entrance_ramp_factor_by_v);
                } else if (station_idx < left_split_th_high) {
                    right_bound =
                        std::fmin(right_bound,
                                  -kDefaultLaneWidth * split_ramp_factor_by_v);
                }
            } else if (right_split_range.first > 0) {
                if (station_idx < right_split_th_low) {
                    left_bound = std::fmax(
                        left_bound,
                        kDefaultLaneWidth * split_entrance_ramp_factor_by_v);
                } else if (station_idx < right_split_th_high) {
                    left_bound = std::fmax(
                        left_bound, kDefaultLaneWidth * split_ramp_factor_by_v);
                }
            }
        }
    }

    return PathBoundary(std::move(right_bound_vec), std::move(left_bound_vec));
}

PathBoundary BuildCurbPathBoundary(const DrivePassage &drive_passage) {
    const int n = drive_passage.stations().size();
    std::vector<double> left_bound_vec, right_bound_vec;
    left_bound_vec.reserve(n);
    right_bound_vec.reserve(n);

    for (const auto &station : drive_passage.stations()) {
        auto curb_offsets = station.QueryCurbOffsetAt(0.0).value();
        double right_curb = curb_offsets.first;
        double left_curb = curb_offsets.second;
        right_bound_vec.push_back(right_curb);
        left_bound_vec.push_back(left_curb);
    }

    return PathBoundary(std::move(right_bound_vec), std::move(left_bound_vec));
}

PathBoundary BuildSolidPathBoundary(
    const DrivePassage &drive_passage,
    const FrenetCoordinate &cur_sl,
    const VehicleGeometryParamsProto &vehicle_geom,
    const ApolloTrajectoryPointProto &plan_start_point,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const LaneChangeStateProto &lc_state,
    double target_lane_offset,
    const std::pair<int, int> &left_split_range,
    const std::pair<int, int> &right_split_range,
    const std::vector<double> &center_l) {
    const int n = drive_passage.size();
    std::vector<double> left_bound_vec, right_bound_vec;
    left_bound_vec.reserve(n);
    right_bound_vec.reserve(n);

    const bool is_left_split =
        ((left_split_range.first == -1 && left_split_range.second == -1) ||
         (left_split_range.first == left_split_range.second))
            ? false
            : true;
    const bool is_right_split =
        ((right_split_range.first == -1 && right_split_range.second == -1) ||
         (right_split_range.first == right_split_range.second))
            ? false
            : true;

    constexpr double kVirtualStationConsiderTime = 5.5;
    constexpr double kVirtualStationConsiderDist = 60.0;
    const double virtual_station_consider_dist =
        std::min(kVirtualStationConsiderTime * plan_start_point.v(),
                 kVirtualStationConsiderDist);
    const bool is_lane_change_task =
        (LaneChangeStage::LCS_EXECUTING == lc_state.stage() ||
         LaneChangeStage::LCS_RETURN == lc_state.stage());
    const bool is_congestion_scene =
        (PushState::CONGESTION_LEFT_PUSH == lc_state.pre_push_state() ||
         PushState::CONGESTION_RIGHT_PUSH == lc_state.pre_push_state());
    std::pair<int, int> allow_solid_range = {0, n - 1};
    std::pair<int, int> force_solid_range = {-1, -1};
    if (is_lane_change_task) {
        int idx = 0;
        int cur_idx = 0;
        for (const auto &station : drive_passage.stations()) {
            if (station.accumulated_s() < cur_sl.s) ++cur_idx;
            if (station.is_in_intersection() ||
                ((station.accumulated_s() - cur_sl.s <
                  virtual_station_consider_dist) &&
                 station.is_virtual())) {
                allow_solid_range.second = idx;
                cur_idx = std::min(cur_idx, std::max(0, idx - 12));
                auto start_idx =
                    is_congestion_scene ? cur_idx : std::max(idx - 50, cur_idx);
                allow_solid_range.first = start_idx;
                force_solid_range.first = allow_solid_range.first;
                force_solid_range.second = allow_solid_range.second;
                break;
            }
            ++idx;
        }
    }

    std::vector<std::pair<double, double>> left_force_solid_range;
    std::vector<std::pair<double, double>> right_force_solid_range;
    // TODO:（CXC）:need lane info
    const auto &lanes = drive_passage.GetLaneMap();
    for (const auto &single_lane : lanes) {
        const auto current_lane = single_lane.second;
        if (current_lane->left_lane_id() == 0) {
            if (!current_lane->points().empty()) {
                std::pair<double, double> tmp_solid_range;
                const auto &start_point_or =
                    drive_passage.QueryFrenetLonOffsetAt(
                        current_lane->points().front());
                const auto &end_point_or = drive_passage.QueryFrenetLonOffsetAt(
                    current_lane->points().back());
                if (start_point_or.ok() && end_point_or.ok()) {
                    tmp_solid_range.first = start_point_or.value().accum_s;
                    tmp_solid_range.second = end_point_or.value().accum_s;
                    left_force_solid_range.push_back(tmp_solid_range);
                }
            }
        }
        if (current_lane->right_lane_id() == 0) {
            if (!current_lane->points().empty()) {
                std::pair<double, double> tmp_solid_range;
                const auto &start_point_or =
                    drive_passage.QueryFrenetLonOffsetAt(
                        current_lane->points().front());
                const auto &end_point_or = drive_passage.QueryFrenetLonOffsetAt(
                    current_lane->points().back());
                if (start_point_or.ok() && end_point_or.ok()) {
                    tmp_solid_range.first = start_point_or.value().accum_s;
                    tmp_solid_range.second = end_point_or.value().accum_s;
                    right_force_solid_range.push_back(tmp_solid_range);
                }
            }
        }
    }
#if 0
    const auto lane_seq_ptr = drive_passage.lane_path().lane_seq();
    if (lane_seq_ptr != nullptr) {
        const auto &lanes = lane_seq_ptr->lanes();
        for (auto lane_ptr : lanes) {
            if (!lane_ptr) continue;
            if (lane_ptr->left_lane_id() == 0) {
                if (!lane_ptr->points().empty()) {
                    std::pair<double, double> tmp_solid_range;
                    const auto &start_point_or =
                        drive_passage.QueryFrenetLonOffsetAt(
                            lane_ptr->points().front());
                    const auto &end_point_or =
                        drive_passage.QueryFrenetLonOffsetAt(
                            lane_ptr->points().back());
                    if (start_point_or.ok() && end_point_or.ok()) {
                        tmp_solid_range.first = start_point_or.value().accum_s;
                        tmp_solid_range.second = end_point_or.value().accum_s;
                        left_force_solid_range.push_back(tmp_solid_range);
                    }
                }
            }
            if (lane_ptr->right_lane_id() == 0) {
                if (!lane_ptr->points().empty()) {
                    std::pair<double, double> tmp_solid_range;
                    const auto &start_point_or =
                        drive_passage.QueryFrenetLonOffsetAt(
                            lane_ptr->points().front());
                    const auto &end_point_or =
                        drive_passage.QueryFrenetLonOffsetAt(
                            lane_ptr->points().back());
                    if (start_point_or.ok() && end_point_or.ok()) {
                        tmp_solid_range.first = start_point_or.value().accum_s;
                        tmp_solid_range.second = end_point_or.value().accum_s;
                        right_force_solid_range.push_back(tmp_solid_range);
                    }
                }
            }
        }
    }
#endif

    double left_offset = 1.75;
    double right_offset = -1.75;
    std::pair<double, double> left_construction_scene_range = {0.0, 0.0};
    std::pair<double, double> right_construction_scene_range = {0.0, 0.0};
    for (const auto &stationary_obj : st_traj_mgr.stationary_objects()) {
        if (stationary_obj.planner_object.type() !=
                ObjectType::OT_UNKNOWN_STATIC &&
            stationary_obj.planner_object.type() !=
                ObjectType::OT_WARNING_TRIANGLE &&
            stationary_obj.planner_object.type() != ObjectType::OT_CONE &&
            stationary_obj.planner_object.type() != ObjectType::OT_BARRIER) {
            continue;
        }

        ASSIGN_OR_CONTINUE(const auto frenet_box,
                           drive_passage.QueryFrenetBoxAtContour(
                               stationary_obj.planner_object.contour()));
        if (frenet_box.l_min > 0.0 && frenet_box.l_min < 1.75) {
            if (frenet_box.l_min < left_offset) {
                left_offset = frenet_box.l_min;
            }
            if (frenet_box.s_max > left_construction_scene_range.second) {
                left_construction_scene_range.second = frenet_box.s_max;
            }
        }
        if (frenet_box.l_max < -0.0 && frenet_box.l_max > -1.75) {
            if (frenet_box.l_max > right_offset) {
                right_offset = frenet_box.l_max;
            }
            if (frenet_box.s_max > right_construction_scene_range.second) {
                right_construction_scene_range.second = frenet_box.s_max;
            }
        }
    }

    const double line_buffer = (vehicle_geom.width() * 0.5) + 0.3;
    for (int i = 0; i < n && i < center_l.size(); ++i) {
        const auto &station = drive_passage.station(StationIndex(i));
        auto curb_offsets = station.QueryCurbOffsetAt(0.0).value();
        double right_curb = curb_offsets.first;
        double left_curb = curb_offsets.second;
        double right_l = right_curb;
        double left_l = left_curb;

        if (i < allow_solid_range.first || i > allow_solid_range.second) {
            right_bound_vec.push_back(right_l);
            left_bound_vec.push_back(left_l);
            continue;
        }
        const bool force_solid_flag =
            (i >= force_solid_range.first && i <= force_solid_range.second);

        bool is_prohibited_widening_left = false;
        bool is_prohibited_widening_right = false;
        double use_left_min_l = 0, use_right_max_l = 0;
        double use_line_buffer_left = 0, use_line_buffer_right = 0;
        if (is_left_split && i >= left_split_range.first &&
            i <= left_split_range.second) {
            is_prohibited_widening_left = true;
        } else if (is_right_split && i >= right_split_range.first &&
                   i <= right_split_range.second) {
            is_prohibited_widening_right = true;
        }
        use_left_min_l =
            is_prohibited_widening_left
                ? 0
                : 0.1;  // center_l[i] + vehicle_geom.width() * 0.5;
        use_right_max_l =
            is_prohibited_widening_right
                ? 0
                : 0.1;  // center_l[i] - vehicle_geom.width() * 0.5;
        use_line_buffer_left = is_prohibited_widening_left ? 0 : line_buffer;
        use_line_buffer_right = is_prohibited_widening_right ? 0 : line_buffer;
        for (const auto &bound : station.boundaries()) {
            if (bound.lat_offset <= use_right_max_l &&
                bound.lat_offset > right_l &&
                (bound.IsSolid(cur_sl.l) || force_solid_flag)) {
                right_l = std::fmin(bound.lat_offset,
                                    center_l[i] - use_line_buffer_right);
            }
            if (bound.lat_offset >= use_left_min_l &&
                bound.lat_offset < left_l &&
                (bound.IsSolid(cur_sl.l) || force_solid_flag)) {
                left_l = std::fmax(bound.lat_offset,
                                   center_l[i] + use_line_buffer_left);
            }
        }

        bool is_in_left_force_range = false;
        bool is_in_right_force_range = false;
        for (const auto &tmp_range : left_force_solid_range) {
            if (station.accumulated_s() > tmp_range.first &&
                station.accumulated_s() < tmp_range.second) {
                is_in_left_force_range = true;
                break;
            }
        }
        for (const auto &tmp_range : right_force_solid_range) {
            if (station.accumulated_s() > tmp_range.first &&
                station.accumulated_s() < tmp_range.second) {
                is_in_right_force_range = true;
                break;
            }
        }
        if (station.accumulated_s() >
                left_construction_scene_range.first - vehicle_geom.length() &&
            station.accumulated_s() <
                left_construction_scene_range.second + vehicle_geom.length() &&
            !is_in_right_force_range) {
            right_l =
                std::min(right_l, left_offset - vehicle_geom.width() - 1.0);
        }
        if (station.accumulated_s() >
                right_construction_scene_range.first - vehicle_geom.length() &&
            station.accumulated_s() <
                right_construction_scene_range.second + vehicle_geom.length() &&
            !is_in_left_force_range) {
            left_l =
                std::max(left_l, vehicle_geom.width() + 1.0 + right_offset);
        }
        right_bound_vec.push_back(right_l);
        left_bound_vec.push_back(left_l);
    }

    return PathBoundary(std::move(right_bound_vec), std::move(left_bound_vec));
}

PathBoundary BuildPathBoundaryFromAvKinematics(
    const DrivePassage &drive_passage,
    const ApolloTrajectoryPointProto &plan_start_point,
    const VehicleGeometryParamsProto &vehicle_geom,
    const FrenetCoordinate &cur_sl,
    const FrenetBox &sl_box,
    const LaneChangeStateProto &lc_state,
    absl::Span<const double> s_vec,
    double target_lane_offset,
    double max_lane_change_lat_accel,
    bool lane_change_pause) {
    const auto traj_l_s = GenerateConstLateralAccelConstSpeedTraj(
        drive_passage, plan_start_point, cur_sl, target_lane_offset,
        max_lane_change_lat_accel);

    const int n = drive_passage.size();
    const double half_av_width = vehicle_geom.width() * 0.5;
    double ego_lat_buffer = half_av_width + kEgoLatBuffer;
    if (drive_passage.GetIsChangeAbnormal()) {
        ego_lat_buffer += vehicle_geom.width() * 0.5;
    }
    std::vector<double> right_bound_vec, left_bound_vec;
    right_bound_vec.reserve(n);
    left_bound_vec.reserve(n);
    const bool is_lane_change_task =
        (LaneChangeStage::LCS_EXECUTING == lc_state.stage() ||
         LaneChangeStage::LCS_RETURN == lc_state.stage());
    const bool is_congestion_scene =
        (PushState::CONGESTION_LEFT_PUSH == lc_state.pre_push_state() ||
         PushState::CONGESTION_RIGHT_PUSH == lc_state.pre_push_state());
    const bool is_left_congestion =
        PushState::CONGESTION_LEFT_PUSH == lc_state.pre_push_state();
    const double lc_congestion_dist =
        std::fmax(3.0, plan_start_point.v() * 4.0);
    const double lc_protect_dist = 0.5 * plan_start_point.v();
    std::vector<double> speed_vec = {40, 60, 80, 100, 120};
    std::vector<double> lat_v_vec = {0.90, 0.81, 0.72, 0.65, 0.60};
    const PiecewiseLinearFunction<double, double> plf(speed_vec, lat_v_vec);
    const double lat_v =
        plf.Evaluate(std::fmax(plan_start_point.v(), 1.0) * 3.6) * 1.05;

    for (int i = 0; i < drive_passage.size(); ++i) {
        const auto s = s_vec[i];
        right_bound_vec.push_back(0.0);
        left_bound_vec.push_back(0.0);
        auto &right_bound = right_bound_vec.back();
        auto &left_bound = left_bound_vec.back();

        right_bound = std::numeric_limits<double>::infinity();
        left_bound = -std::numeric_limits<double>::infinity();

        if (is_lane_change_task && is_congestion_scene) {
            if (s < sl_box.s_max + lc_congestion_dist) {
                double lat_dist =
                    lat_v * std::fmax(0.0, s - sl_box.s_max - lc_protect_dist) /
                    std::fmax(1.0, plan_start_point.v());
                if (is_left_congestion) {
                    right_bound = sl_box.l_min - kEgoLatBuffer + lat_dist;
                } else {
                    left_bound = sl_box.l_max + kEgoLatBuffer - lat_dist;
                }
            }
        } else {
            if (traj_l_s.ok() && s >= traj_l_s->x().front() &&
                s <= traj_l_s->x().back()) {
                right_bound = traj_l_s->Evaluate(s) - ego_lat_buffer;
                left_bound = traj_l_s->Evaluate(s) + ego_lat_buffer;
            }
            if (s < sl_box.s_max + kMinKinematicBoundaryProtectedZone) {
                right_bound =
                    std::min(right_bound, sl_box.l_min - kEgoLatBuffer);
                left_bound = std::max(left_bound, sl_box.l_max + kEgoLatBuffer);
            }
        }
        if (lane_change_pause) {
            right_bound =
                std::min(right_bound, target_lane_offset - ego_lat_buffer);
            left_bound =
                std::max(left_bound, target_lane_offset + ego_lat_buffer);
        }
    }

    return PathBoundary(std::move(right_bound_vec), std::move(left_bound_vec));
}

PathBoundary ShrinkPathBoundaryForLaneChangePause(
    const VehicleGeometryParamsProto &vehicle_geom,
    const FrenetBox &sl_box,
    const LaneChangeStateProto &lc_state,
    PathBoundary boundary,
    double target_lane_offset,
    const std::vector<double> &center_l) {
    const double half_av_width = vehicle_geom.width() * 0.5;
    if (lc_state.lc_left()) {
        for (int i = 0; i < boundary.size() && i < center_l.size(); ++i) {
            const double shrinked_l =
                std::max(center_l[i] + half_av_width, sl_box.l_max) +
                kLcPauseEgoLatBuffer;
            boundary.OuterClampLeftByIndex(i, shrinked_l);
        }
    } else {
        for (int i = 0; i < boundary.size() && i < center_l.size(); ++i) {
            const double shrinked_l =
                std::min(center_l[i] - half_av_width, sl_box.l_min) -
                kLcPauseEgoLatBuffer;
            boundary.OuterClampRightByIndex(i, shrinked_l);
        }
    }

    return boundary;
}

PathBoundary ExtendPathBoundaryForLaneChangePause(
    const LaneChangeStateProto &lc_state,
    const double half_lane_width,
    PathBoundary boundary,
    const std::vector<double> &smooth_center_offset) {
    if (lc_state.lc_left()) {
        for (int i = 0; i < boundary.size() && i < smooth_center_offset.size();
             ++i) {
            boundary.InnerClampRightByIndex(
                i, std::min(-3.0 * half_lane_width,
                            smooth_center_offset[i] - kDefaultHalfLaneWidth));
        }
    } else {
        for (int i = 0; i < boundary.size() && i < smooth_center_offset.size();
             ++i) {
            boundary.InnerClampLeftByIndex(
                i, std::max(3.0 * half_lane_width,
                            smooth_center_offset[i] + kDefaultHalfLaneWidth));
        }
    }
    return boundary;
}

PathBoundary ShrinkPathBoundaryForObject(
    const DrivePassage &drive_passage,
    const SpacetimeTrajectoryManager &st_traj_mgr,
    const ApolloTrajectoryPointProto &plan_start_point,
    absl::Span<const double> s_vec,
    absl::Span<const double> center_l,
    absl::Span<const Vec2d> center_xy,
    const PathBoundary &inner_boundary,
    const PathBoundary &curb_boundary,
    PathBoundary boundary,
    const FrenetBox &sl_box,
    const bool &borrow_lane) {
    for (const auto &traj : st_traj_mgr.stationary_object_trajs()) {
        const auto obj_fbox_or = drive_passage.QueryFrenetBoxAtContour(
            traj->states().front().contour);
        if (!obj_fbox_or.ok() || obj_fbox_or->s_min > s_vec.back()) {
            continue;
        }
        const auto &obj_fbox = obj_fbox_or.value();
        if (std::fmin(std::fabs(obj_fbox.l_max), std::fabs(obj_fbox.l_min)) <
            1.2) {
            continue;
        }
        boundary = BuildBoundaryForStationaryObject(
            drive_passage, center_l, obj_fbox, s_vec, std::move(boundary));
    }
    const auto av_t_s = GenerateAvTrajAlongRefCenterLine(
        drive_passage, plan_start_point, center_xy);

    if (av_t_s.ok()) {
        for (const auto &traj : st_traj_mgr.moving_object_trajs()) {
            const auto obj_fbox_or = drive_passage.QueryFrenetBoxAtContour(
                traj->states().front().contour);
            if (!obj_fbox_or.ok() || obj_fbox_or->s_min > s_vec.back()) {
                continue;
            }

            if (obj_fbox_or.value().l_max < sl_box.l_min - 2.7 ||
                obj_fbox_or.value().l_min > sl_box.l_max + 2.7 ||
                (traj->states().front().traj_point->v() <
                     plan_start_point.v() &&
                 obj_fbox_or.value().s_max <= sl_box.s_min) ||
                (traj->states().front().traj_point->v() >
                     plan_start_point.v() &&
                 obj_fbox_or.value().s_min >= sl_box.s_max)) {
                continue;
            }

            double lat_overlap = 0.0;
            if (obj_fbox_or.value().l_max < sl_box.l_max &&
                obj_fbox_or.value().l_max >= sl_box.l_min) {
                lat_overlap = obj_fbox_or.value().l_max - sl_box.l_min;
            } else if (sl_box.l_max < obj_fbox_or.value().l_max &&
                       sl_box.l_max >= obj_fbox_or.value().l_min) {
                lat_overlap = sl_box.l_max - obj_fbox_or.value().l_min;
            }

            if (lat_overlap > 0.5) {
                continue;
            }

            const double pursuit_time = borrow_lane ? kBorrowPursuitTimeConsider
                                                    : kLkPursuitTimeConsider;
            double judge_length = std::max(
                10.0, std::fabs(plan_start_point.v() -
                                traj->states().front().traj_point->v()) *
                          pursuit_time);

            if (obj_fbox_or.value().s_max < sl_box.s_min) {
                double s_back = sl_box.s_min - obj_fbox_or.value().s_max;
                if (s_back > judge_length) {
                    continue;
                }
            } else if (obj_fbox_or.value().s_max > sl_box.s_min) {
                double s_back = obj_fbox_or.value().s_min - sl_box.s_max;
                if (s_back > judge_length) {
                    continue;
                }
            }

            boundary = BuildBoundaryForDynamicObject(
                drive_passage, center_l, *traj, *av_t_s, s_vec, inner_boundary,
                curb_boundary, std::move(boundary), borrow_lane);
        }
    }

    return boundary;
}

bool ObstsacleFilter(const SpacetimeObjectTrajectory *traj,
                     const DrivePassage &drive_passage,
                     const ApolloTrajectoryPointProto &plan_start_point) {
    if (!traj) return true;
    const auto av_sl_point = drive_passage.QueryFrenetCoordinateAt(
        Vec2dFromApolloTrajectoryPointProto(plan_start_point));
    double obs_speed = traj->states().front().traj_point->v();
    const auto obj_fbox_or =
        drive_passage.QueryUnboundedFrenetCoordinateAt(traj->pose().pos());

    if (av_sl_point.ok() && obj_fbox_or.ok()) {
        if (obj_fbox_or->s < av_sl_point->s ||
            obj_fbox_or->s >
                av_sl_point->s + ((plan_start_point.v() - obs_speed) * 3.0)) {
            return true;
        }
    }
    return false;
}

double ComputeCollisionFreeOffset(
    const DrivePassage &drive_passage,
    const FrenetCoordinate &cur_sl,
    const ApolloTrajectoryPointProto &plan_start_point,
    double half_av_width,
    absl::Span<const SpacetimeObjectTrajectory> obj_trajs,
    const bool is_left,
    const bool is_lc_pause) {
    const double kRearToRearAxle = 1.15;
    const double kFrontToRearAxle = 4.10;
    const double kDefaultLonDist = 2.5;
    const double kDefaultFrontLonDist = 20.0;
    const double kTimeToCollision = 4.0;
    const double kLonRange = 0.5;
    const double kSpeedDiffThreshold = 1.0;
    std::vector<double> speed_safe_lat_dist_ramp = {0.8, 0.9, 1.1, 1.3, 1.4};
    std::vector<double> safe_speed_ramp = {
        0.0 * ads_x::planning::Constants::KPH2MPS,
        10.0 * ads_x::planning::Constants::KPH2MPS,
        30.0 * ads_x::planning::Constants::KPH2MPS,
        60.0 * ads_x::planning::Constants::KPH2MPS,
        135.0 * ads_x::planning::Constants::KPH2MPS};
    PiecewiseLinearFunction<double, double> safe_lat_dist_plf(
        safe_speed_ramp, speed_safe_lat_dist_ramp);
    double speed_safe_lat_dist =
        safe_lat_dist_plf.Evaluate(plan_start_point.v());
    double obj_center_left_range =
        0.5 * ads_x::planning::Constants::DEFAULT_LANE_WIDTH;
    double obj_center_right_range =
        -0.5 * ads_x::planning::Constants::DEFAULT_LANE_WIDTH;
    double safe_offset = is_left ? std::numeric_limits<double>::max()
                                 : std::numeric_limits<double>::lowest();
    if (!is_lc_pause) {
        obj_center_left_range =
            is_left ? 1.5 * ads_x::planning::Constants::DEFAULT_LANE_WIDTH
                    : -0.5 * ads_x::planning::Constants::DEFAULT_LANE_WIDTH;
        obj_center_right_range =
            is_left ? 0.5 * ads_x::planning::Constants::DEFAULT_LANE_WIDTH
                    : -1.5 * ads_x::planning::Constants::DEFAULT_LANE_WIDTH;
    }
    for (const auto &traj : obj_trajs) {
        if (traj.object_type() != ObjectType::OT_VEHICLE &&
            traj.object_type() != ObjectType::OT_LARGE_VEHICLE) {
            continue;
        }

        auto object_box = traj.bounding_box();
        auto obj_frenet_box = drive_passage.QueryFrenetBoxAt(object_box);
        if (!obj_frenet_box.ok()) {
            continue;
        }

        if (obj_frenet_box->center_l() > obj_center_left_range ||
            obj_frenet_box->center_l() < obj_center_right_range) {
            continue;
        }

        double obj_speed = traj.pose().v();
        if ((obj_frenet_box->s_max <
                 cur_sl.s - kRearToRearAxle - kDefaultLonDist &&
             (kTimeToCollision * (obj_speed - plan_start_point.v())) <
                 cur_sl.s - kRearToRearAxle - obj_frenet_box->s_max) ||
            (obj_frenet_box->s_min >
                 cur_sl.s + kFrontToRearAxle + kDefaultFrontLonDist &&
             (kTimeToCollision * (plan_start_point.v() - obj_speed)) <
                 obj_frenet_box->s_min - cur_sl.s - kFrontToRearAxle)) {
            continue;
        }
        if (obj_frenet_box->s_max < cur_sl.s - kRearToRearAxle - kLonRange &&
            plan_start_point.v() > obj_speed + kSpeedDiffThreshold) {
            continue;
        }

        if (traj.object_type() == ObjectType::OT_LARGE_VEHICLE &&
            !is_lc_pause) {
            safe_offset = 0.0;
            break;
        }

        safe_offset = is_left ? std::fmin(safe_offset, obj_frenet_box->l_min -
                                                           speed_safe_lat_dist -
                                                           half_av_width)
                              : std::fmax(safe_offset, obj_frenet_box->l_max +
                                                           speed_safe_lat_dist +
                                                           half_av_width);
    }
    return safe_offset;
}

double ComputeTargetLaneOffset(
    const DrivePassage &drive_passage,
    const FrenetCoordinate &cur_sl,
    const LaneChangeStateProto &lc_state,
    const ApolloTrajectoryPointProto &plan_start_point,
    double half_av_width,
    int is_force_lc,
    double force_lc_offset_ratio,
    absl::Span<const SpacetimeObjectTrajectory> obj_trajs) {
    double target_lane_offset = 0.0;
    if (lc_state.stage() != LaneChangeStage::LCS_PAUSE &&
        lc_state.push_state() == PushState::NONE_PUSH && is_force_lc == 0) {
        return target_lane_offset;
    }

    if (is_force_lc > 0) {
        constexpr double kMinLateralBuffer = 0.3;
        constexpr double kMinKinematicBuffer = 0.1;
        const auto boundaries =
            drive_passage.QueryEnclosingLaneBoundariesAtS(cur_sl.s);

        const double right_offset =
            std::max(boundaries.right->lat_offset, -kMaxHalfLaneWidth);
        const double left_offset =
            std::min(boundaries.left->lat_offset, kMaxHalfLaneWidth);
        const double lane_width = std::abs(right_offset - left_offset);
        if (is_force_lc == 1) {
            if (lc_state.stage() == LaneChangeStage::LCS_NONE) {
                target_lane_offset =
                    (force_lc_offset_ratio * left_offset) + kMinKinematicBuffer;
            }
            if (lc_state.stage() == LaneChangeStage::LCS_PAUSE) {
                target_lane_offset =
                    -lane_width + (force_lc_offset_ratio * lane_width);
            }
        } else if (is_force_lc == 2) {
            if (lc_state.stage() == LaneChangeStage::LCS_PAUSE) {
                target_lane_offset =
                    lane_width + (force_lc_offset_ratio * (-lane_width));
            }
        }
    } else if (lc_state.stage() == LaneChangeStage::LCS_PAUSE) {
        double kinematic_lat_offset = cur_sl.l;
        const auto lane_tangent = drive_passage.QueryTangentAtS(cur_sl.s);
        if (lane_tangent.ok()) {
            const double lat_v =
                plan_start_point.v() *
                lane_tangent->CrossProd(Vec2d::FastUnitFromAngle(
                    plan_start_point.path_point().theta()));
            kinematic_lat_offset += std::copysign(
                Sqr(lat_v) * 0.5 / kComfortLaneChangeCancelLatAccel, lat_v);
        }

        constexpr double kMinLateralBuffer = 0.3;
        constexpr double kMinKinematicBuffer = 0.1;
        const auto boundaries =
            drive_passage.QueryEnclosingLaneBoundariesAtS(cur_sl.s);

        const double right_offset =
            std::max(boundaries.right->lat_offset, -kMaxHalfLaneWidth);
        const double left_offset =
            std::min(boundaries.left->lat_offset, kMaxHalfLaneWidth);
        const double lane_width = std::abs(right_offset - left_offset);
        if (lc_state.lc_left()) {
            target_lane_offset =
                std::max(right_offset - half_av_width - kMinLateralBuffer,
                         kinematic_lat_offset - kMinKinematicBuffer);
            double collision_free_offset = ComputeCollisionFreeOffset(
                drive_passage, cur_sl, plan_start_point, half_av_width,
                obj_trajs, true, true);
            target_lane_offset =
                std::fmin(target_lane_offset, collision_free_offset);
            if (collision_free_offset < kDefaultHalfLaneWidth) {
                target_lane_offset =
                    std::fmin(target_lane_offset, std::fmax(cur_sl.l, 0.0));
            }

            target_lane_offset = std::fmax(target_lane_offset, -lane_width);

        } else {
            target_lane_offset =
                std::min(left_offset + half_av_width + kMinLateralBuffer,
                         kinematic_lat_offset + kMinKinematicBuffer);
            double collision_free_offset = ComputeCollisionFreeOffset(
                drive_passage, cur_sl, plan_start_point, half_av_width,
                obj_trajs, false, true);
            target_lane_offset =
                std::fmax(target_lane_offset, collision_free_offset);
            if (collision_free_offset > -kDefaultHalfLaneWidth) {
                target_lane_offset =
                    std::fmax(target_lane_offset, std::fmin(cur_sl.l, 0.0));
            }

            target_lane_offset = std::fmax(target_lane_offset, lane_width);
        }

        if (std::abs(cur_sl.l - target_lane_offset) >
            kMaxLaneChangePauseRefCenterStep) {
            target_lane_offset =
                cur_sl.l + std::copysign(kMaxLaneChangePauseRefCenterStep,
                                         target_lane_offset - cur_sl.l);
        }

    } else {
        const bool is_congestion =
            (lc_state.push_state() == PushState::CONGESTION_LEFT_PUSH ||
             lc_state.push_state() == PushState::CONGESTION_RIGHT_PUSH);
        const double kDefaultPushOffset = is_congestion ? 0.6 : 0.6;
        if (lc_state.push_state() == PushState::LEFT_PUSH ||
            lc_state.push_state() == PushState::CONGESTION_LEFT_PUSH) {
            double safe_push_offset = ComputeCollisionFreeOffset(
                drive_passage, cur_sl, plan_start_point, half_av_width,
                obj_trajs, true, false);
            target_lane_offset =
                std::fmin(std::fmax(safe_push_offset, 0.0), kDefaultPushOffset);

        } else if (lc_state.push_state() == PushState::RIGHT_PUSH ||
                   lc_state.push_state() == PushState::CONGESTION_RIGHT_PUSH) {
            double safe_push_offset = ComputeCollisionFreeOffset(
                drive_passage, cur_sl, plan_start_point, half_av_width,
                obj_trajs, false, false);
            target_lane_offset = std::fmax(std::fmin(safe_push_offset, 0.0),
                                           -kDefaultPushOffset);
        }
    }
    return target_lane_offset;
}

PathSlBoundary BuildPathSlBoundary(const DrivePassage &drive_passage,
                                   std::vector<double> s_vec,
                                   std::vector<double> ref_center_l,
                                   PathBoundary inner_boundary,
                                   PathBoundary outer_boundary,
                                   PathBoundary opt_outer_boundary) {
    const int n = s_vec.size();
    std::vector<Vec2d> inner_right_xy, inner_left_xy, outer_right_xy,
        outer_left_xy, opt_outer_right_xy, opt_outer_left_xy, ref_center_xy;
    inner_right_xy.reserve(n);
    inner_left_xy.reserve(n);
    outer_right_xy.reserve(n);
    outer_left_xy.reserve(n);
    opt_outer_right_xy.reserve(n);
    opt_outer_left_xy.reserve(n);
    ref_center_xy.reserve(n);
    for (int i = 0; i < n; ++i) {
        const auto &station = drive_passage.station(StationIndex(i));
        inner_left_xy.emplace_back(station.lat_point(inner_boundary.left(i)));
        inner_right_xy.emplace_back(station.lat_point(inner_boundary.right(i)));
        outer_right_xy.emplace_back(station.lat_point(outer_boundary.right(i)));
        outer_left_xy.emplace_back(station.lat_point(outer_boundary.left(i)));
        opt_outer_right_xy.emplace_back(
            station.lat_point(opt_outer_boundary.right(i)));
        opt_outer_left_xy.emplace_back(
            station.lat_point(opt_outer_boundary.left(i)));
        ref_center_xy.push_back(station.lat_point(ref_center_l[i]));
    }

    return PathSlBoundary(
        std::move(s_vec), std::move(ref_center_l),
        outer_boundary.moved_right_vec(), outer_boundary.moved_left_vec(),
        opt_outer_boundary.moved_right_vec(),
        opt_outer_boundary.moved_left_vec(), inner_boundary.moved_right_vec(),
        inner_boundary.moved_left_vec(), std::move(ref_center_xy),
        std::move(outer_right_xy), std::move(outer_left_xy),
        std::move(opt_outer_right_xy), std::move(opt_outer_left_xy),
        std::move(inner_right_xy), std::move(inner_left_xy));
}

std::vector<double> ComputeSmoothedReferenceLine(
    const DrivePassage &drive_passage,
    const SmoothedReferenceLineResultMap &smooth_result_map_tmp) {
    const int n = drive_passage.size();
    std::vector<double> smoothed_reference_center(n, 0.0);
    absl::flat_hash_map<pnc_x::mapping::ElementId,
                        PiecewiseLinearFunction<double, double>>
        lane_id_to_smoothed_lateral_offset;

    int cur_begin = -1;
    const auto &lane_path = drive_passage.extend_lane_path();
    std::vector<ads_x::planning::LaneConstPtr> lanes_ptr_vec;
    // const auto &map_ptr = psmm.map_ptr();
    // if (map_ptr) {
    //   for (const auto &lane_id : lane_path.lane_ids()) {

    //     ads_x::planning::LaneConstPtr lane_ptr =
    //     map_ptr->GetLaneById(lane_id); if (lane_ptr) {
    //       lanes_ptr_vec.emplace_back(lane_ptr);
    //     }
    //   }
    // }

    ads_x::planning::LaneSequencePtr lane_sequence_ptr =
        std::make_shared<ads_x::planning::LaneSequence>(lanes_ptr_vec);
    SmoothedReferenceLineResultMap smooth_result_map;
    auto smooth_result_map_or = GenerateSmoothedResultMap(lane_sequence_ptr);
    if (smooth_result_map_or.ok()) {
        smooth_result_map = std::move(smooth_result_map_or).value();
    }

    for (int i = 0; i < lane_path.size(); ++i) {
        const bool should_smooth =
            smooth_result_map.IfSmoothLaneForRamp(lane_path.lane_id(i));
        if ((cur_begin == -1) && should_smooth) {
            cur_begin = i;
        }
        int end_idx = 0;
        const bool smooth_end =
            smooth_result_map.IsSmoothLaneEnd(lane_path.lane_id(i));
        if (should_smooth && smooth_end) {
            end_idx = i + 1;
        } else if (!should_smooth) {
            end_idx = i;
        }
        if ((cur_begin != -1) && smooth_end) {
            const std::vector<mapping::ElementId> lane_ids(
                lane_path.lane_ids().begin() + cur_begin,
                lane_path.lane_ids().begin() + end_idx);
            cur_begin = -1;
            if (lane_ids.size() < 2) continue;
            const auto smoothed_result =
                smooth_result_map.FindOverlapSmoothedResult(lane_ids);
            if (smoothed_result.ok()) {
                lane_id_to_smoothed_lateral_offset.insert(
                    smoothed_result->lane_id_to_smoothed_lateral_offset.begin(),
                    smoothed_result->lane_id_to_smoothed_lateral_offset.end());
            }
        }
    }

    if (cur_begin != -1) {
        const std::vector<mapping::ElementId> lane_ids(
            lane_path.lane_ids().begin() + cur_begin,
            lane_path.lane_ids().end());
        if (lane_ids.size() > 1) {
            const auto smoothed_result =
                smooth_result_map.FindOverlapSmoothedResult(lane_ids);
            if (smoothed_result.ok()) {
                lane_id_to_smoothed_lateral_offset.insert(
                    smoothed_result->lane_id_to_smoothed_lateral_offset.begin(),
                    smoothed_result->lane_id_to_smoothed_lateral_offset.end());
            }
        }
    }

    SmoothedReferenceCenterResult smooth_results = {
        .lane_id_to_smoothed_lateral_offset =
            std::move(lane_id_to_smoothed_lateral_offset)};
    for (int i = 0; i < n; ++i) {
        const mapping::LanePoint &lane_point =
            drive_passage.station(StationIndex(i)).GetLanePoint();
        const auto smoothed_l =
            smooth_results.GetSmoothedLateralOffset(lane_point);
        if (smoothed_l.ok()) {
            smoothed_reference_center[i] = *smoothed_l;
        }
    }

    return smoothed_reference_center;
}

std::vector<double> ComputeCompensationRefLine(
    const DrivePassage &drive_passage,
    const std::vector<double> &center_l,
    const ApolloTrajectoryPointProto &plan_start_point,
    const boost::optional<double> &ref_centered_compensation_offset) {
    constexpr double kEps = 0.001;
    constexpr double kMaxCompensationRatio = 0.01;
    std::vector<double> compensation_center_l(center_l);
    if (!ref_centered_compensation_offset.has_value()) {
        return compensation_center_l;
    }
    const Vec2d ego_pos = Vec2dFromApolloTrajectoryPointProto(plan_start_point);
    const auto &ego_nearest_station_idx =
        drive_passage.FindNearestStationIndex(ego_pos);
    const auto &ego_nearest_station =
        drive_passage.station(ego_nearest_station_idx);
    const auto &s_nearest_station = drive_passage.FindNearestStationAtS(
        plan_start_point.v() * kMaxCenterNum * kTrajectoryTimeStep);
    const double ego_nearest_station_s = ego_nearest_station.accumulated_s();
    const double s_nearest_station_s = s_nearest_station.accumulated_s();
    const double s_diff = s_nearest_station_s - ego_nearest_station_s;
    if (std::abs(s_diff) < kEps) {
        return compensation_center_l;
    }
    const double offset = *ref_centered_compensation_offset;
    const double compensation_ratio = boost::algorithm::clamp(
        offset / s_diff, -kMaxCompensationRatio, kMaxCompensationRatio);
    for (int i = ego_nearest_station_idx.value(); i < center_l.size(); ++i) {
        compensation_center_l[i] +=
            compensation_ratio *
            (drive_passage.station(static_cast<StationIndex>(i))
                 .accumulated_s() -
             ego_nearest_station_s);
    }
    return compensation_center_l;
}

void DecasteljauRecursion(std::vector<Vec2d> &control_points, int n, double t) {
    if (n <= 1) {
        return;
    }
    for (int i = 0; i < n - 1; ++i) {
        control_points[i].set_x(((1 - t) * control_points[i].x()) +
                                (t * control_points[i + 1].x()));
        control_points[i].set_y(((1 - t) * control_points[i].y()) +
                                (t * control_points[i + 1].y()));
    }
    DecasteljauRecursion(control_points, n - 1, t);
}

ads_x::planning::math::LineCurve2d ConstructCurveFromPoints(
    ads_x::planning::LaneSequencePtr lane_seq_ptr,
    const std::pair<double, double> &range) {
    double start_s = range.first;
    double end_s = range.second;
    std::vector<Vec2d> control_points;

    const double bezier_length = std::abs(end_s - start_s);
    const Vec2d &point_1 = lane_seq_ptr->GetPointAtS(start_s);
    const Vec2d &start_tangent = lane_seq_ptr->GetTangentAtS(start_s);
    const Vec2d &point_2 = point_1 + (start_tangent * bezier_length / 3.0);
    const Vec2d &point_4 = lane_seq_ptr->GetPointAtS(end_s);
    const Vec2d &end_tangent = lane_seq_ptr->GetTangentAtS(end_s);
    const Vec2d &point_3 = point_4 - (end_tangent * bezier_length / 3.0);
    control_points.emplace_back(point_1);
    control_points.emplace_back(point_2);
    control_points.emplace_back(point_3);
    control_points.emplace_back(point_4);

    std::vector<Vec2d> bezier_points;
    int n = control_points.size();
    double dt = 0.1;
    for (double t = -0.1; t < 1.1 - dt; t += dt) {
        auto control_points_tmp = control_points;
        DecasteljauRecursion(control_points_tmp, n, t);
        auto &bezier_point = control_points_tmp.front();
        bezier_points.emplace_back(bezier_point);
    }

    ads_x::planning::math::LineCurve2d curve(bezier_points);
    return curve;
}

absl::StatusOr<SmoothedReferenceCenterResult> GetSmoothedResult(
    ads_x::planning::LaneSequencePtr lane_sequence,
    const std::pair<double, double> &range,
    std::vector<mapping::ElementId> *lane_ids) {
    std::vector<Vec2d> points;
    for (double s = range.first; s <= range.second; s += 0.5) {
        const Vec2d &point = lane_sequence->GetPointAtS(s);
        points.emplace_back(point);
    }

    if (points.size() < 2) {
        return absl::NotFoundError("points.size < 2");
    }

    std::vector<Vec2d> control_points;
    control_points.push_back(points.front());
    control_points.push_back(points.back());
    const auto &curve = ConstructCurveFromPoints(lane_sequence, range);
    std::set<ads_x::planning::LaneConstPtr> lane_id_set;
    std::vector<double> fractions;
    std::vector<double> offsets;
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        fractional_offsets;
    for (const auto &point : points) {
        ads_x::planning::LaneConstPtr lane_ptr =
            lane_sequence->GetNearestLane(point);
        if (!lane_ptr) continue;
        const mapping::ElementId &lane_id =
            static_cast<mapping::ElementId>(lane_ptr->id());
        if (lane_id_set.count(lane_ptr) == 0) {
            lane_id_set.emplace(lane_ptr);
            lane_ids->emplace_back(lane_id);
            fractional_offsets.emplace_back();
        }
        ads_x::planning::SLPoint sl_point;
        lane_ptr->GetSLWithoutLimitV2(point, &sl_point);
        const double fraction = sl_point.s / lane_ptr->curve_length();
        fractional_offsets.back().first.emplace_back(fraction);
        double tmp_s, tmp_l;
        curve.GetProjection(point, &tmp_s, &tmp_l);
        double lane_width = lane_ptr->GetWidthAtPoint(point.x(), point.y());
        if (!lane_ptr->IsVirtual() && lane_width > 4.0 &&
            std::abs(tmp_l) > std::max(0.7 * lane_width, 4.0)) {
            return absl::NotFoundError("smoothing error too large");
        }
        fractional_offsets.back().second.emplace_back(-tmp_l);
    }

    absl::flat_hash_map<mapping::ElementId,
                        PiecewiseLinearFunction<double, double>>
        smoothed_lane_map;
    if (lane_ids->size() != fractional_offsets.size()) {
        return absl::NotFoundError("lane_ids offsets size not equal");
    }

    for (int i = 0; i < lane_ids->size(); ++i) {
        smoothed_lane_map[lane_ids->at(i)] =
            PiecewiseLinearFunction<double, double>(
                std::move(fractional_offsets[i].first),
                std::move(fractional_offsets[i].second));
    }

    return SmoothedReferenceCenterResult{.lane_id_to_smoothed_lateral_offset =
                                             std::move(smoothed_lane_map)};
}

bool IsDiscontinuousSplit(ads_x::planning::LaneSequencePtr lane_sequence,
                          int i) {
    const auto &lanes = lane_sequence->lanes();
    if ((lanes.size() == 0) || (i == (lanes.size() - 1))) {
        return false;
    }

    ads_x::planning::LaneConstPtr curr_lane_ptr = lanes[i];
    ads_x::planning::LaneConstPtr next_lane_ptr = lanes[i + 1];

    if (curr_lane_ptr == nullptr || next_lane_ptr == nullptr) {
        return false;
    }

    const auto &next_lane_ids = curr_lane_ptr->next_lane_ids();

    if (next_lane_ids.size() < 2) {
        return false;
    }

    if (curr_lane_ptr->center_line().points().empty() ||
        next_lane_ptr->center_line().points().empty()) {
        return false;
    }

    Vec2d curr_lane_end = curr_lane_ptr->center_line().end_point();
    Vec2d next_lane_begin = next_lane_ptr->center_line().begin_point();

    constexpr double distance_threshold = 0.5;
    const double distance = (curr_lane_end - next_lane_begin).norm();

    if (distance > distance_threshold) {
        return true;
    }

    return false;
}

bool IsDiscontinuousMerge(ads_x::planning::LaneSequencePtr lane_sequence,
                          int i) {
    const auto &lanes = lane_sequence->lanes();
    if ((lanes.size() == 0) || (i == (lanes.size() - 1))) {
        return false;
    }

    ads_x::planning::LaneConstPtr curr_lane_ptr = lanes[i];
    ads_x::planning::LaneConstPtr next_lane_ptr = lanes[i + 1];

    if (curr_lane_ptr == nullptr || next_lane_ptr == nullptr) {
        return false;
    }

    const auto &prev_lane_ids = next_lane_ptr->pre_lane_ids();

    if (prev_lane_ids.size() < 2) {
        return false;
    }

    if (curr_lane_ptr->center_line().points().empty() ||
        next_lane_ptr->center_line().points().empty()) {
        return false;
    }

    Vec2d curr_lane_end = curr_lane_ptr->center_line().end_point();
    Vec2d next_lane_begin = next_lane_ptr->center_line().begin_point();

    constexpr double distance_threshold = 0.5;

    if ((curr_lane_end - next_lane_begin).norm() > distance_threshold) {
        return true;
    }

    static constexpr double ULTRA_LANE_WIDTH =
        ads_x::planning::Constants::DEFAULT_LANE_WIDTH * 1.3;
    if (next_lane_ptr->GetWidthAtAccumS(0.0) > ULTRA_LANE_WIDTH) {
        return true;
    }

    return false;
}

std::pair<double, double> GetSRange(
    ads_x::planning::LaneSequencePtr lane_sequence_ptr,
    const std::string &type,
    const int &i,
    const double &s) {
    double start_s = s;
    double optimal_start_s = start_s;
    auto loop_guard1 = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (start_s > 0.0 && std::abs(start_s - s) < 150.0 && loop_guard1) {
        if (std::abs(lane_sequence_ptr->GetWidthAtS(start_s) -
                     ads_x::planning::Constants::DEFAULT_LANE_WIDTH) < 1.5) {
            optimal_start_s = start_s;
        }
        if (std::abs(optimal_start_s - s) > 10.0) {
            break;
        }
        start_s -= 1.0;
    }

    double end_s = s;
    double optimal_end_s = end_s;
    auto loop_guard2 = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (end_s < lane_sequence_ptr->GetTrueLength() &&
           std::abs(end_s - s) < 150.0 && loop_guard2) {
        if (std::abs(lane_sequence_ptr->GetWidthAtS(end_s) -
                     ads_x::planning::Constants::DEFAULT_LANE_WIDTH) < 1.5) {
            optimal_end_s = end_s;
        }
        if (std::abs(optimal_end_s - s) > 10.0) {
            break;
        }
        end_s += 1.0;
    }

    std::pair<double, double> range(s - optimal_start_s, optimal_end_s - s);
    return range;
}

std::vector<std::pair<double, double>> FindNonSmoothRange(
    ads_x::planning::LaneSequencePtr lane_sequence_ptr) {
    if (lane_sequence_ptr == nullptr) {
        return std::vector<std::pair<double, double>>{};
    }
    const auto &lanes = lane_sequence_ptr->lanes();

    double seq_length = 0;

    constexpr double kMaxCheckingLength = 600.0;
    int i = 0;
    std::vector<std::pair<std::string, int>> indexs;
    std::vector<double> s_vec;
    for (ads_x::planning::LaneConstPtr lane_ptr : lanes) {
        const bool is_split = IsDiscontinuousSplit(lane_sequence_ptr, i);
        const bool is_merge = IsDiscontinuousMerge(lane_sequence_ptr, i);
        seq_length += lane_ptr->curve_length();
        if (is_split || is_merge) {
            if (is_split) {
                indexs.emplace_back("split", i);
            } else {
                indexs.emplace_back("merge", i);
            }
        }
        ++i;
        s_vec.push_back(seq_length);
        if (seq_length > kMaxCheckingLength) {
            break;
        }
    }

    std::vector<std::pair<double, double>> ranges;
    for (const auto &pair : indexs) {
        auto type = pair.first;
        int i = pair.second;
        const double s = s_vec[i];
        auto s_range = GetSRange(lane_sequence_ptr, type, i, s);
        const double s_behind = s_range.first;
        const double s_front = s_range.second;
        const double s_start = std::max(0.0, s - s_behind);
        const double s_end = std::min(s + s_front, seq_length);
        ranges.emplace_back(s_start, s_end);
    }

    std::vector<std::pair<double, double>> combined_ranges;
    for (size_t i = 0; i < ranges.size(); ++i) {
        double s_start = ranges[i].first;
        double s_end = ranges[i].second;
        auto loop_guard = DEFAULT_LOOP_GUARD();
        while ((i + 1 < ranges.size()) && loop_guard) {
            if (s_end > ranges[i + 1].first) {
                s_end = ranges[i + 1].second;
                ++i;
            } else {
                break;
            }
        }
        combined_ranges.emplace_back(s_start, s_end);
    }

    return combined_ranges;
}

absl::StatusOr<SmoothedReferenceLineResultMap> GenerateSmoothedResultMap(
    ads_x::planning::LaneSequencePtr lane_sequence_ptr) {
    SmoothedReferenceLineResultMap results;
    results.Clear();
    results.ClearSmoothLanesForRamp();
    bool should_smooth = true;
    results.SetSmoothReferencelineForRamp(should_smooth);

    const std::vector<std::pair<double, double>> &non_smooth_ranges =
        FindNonSmoothRange(lane_sequence_ptr);
    if (non_smooth_ranges.empty()) {
        return results;
    }

    for (const auto &range : non_smooth_ranges) {
        std::vector<mapping::ElementId> lane_ids;
        auto smoothed_result =
            GetSmoothedResult(lane_sequence_ptr, range, &lane_ids);
        if (lane_ids.empty()) {
            continue;
        }

        bool is_end = false;
        for (const auto &lane_id : lane_ids) {
            if (lane_id == lane_ids.back()) {
                is_end = true;
            }

            results.AddSmoothLaneForRamp(lane_id, is_end);
        }
        if (smoothed_result.ok()) {
            results.AddResult(lane_ids, std::move(smoothed_result).value());
        }
    }

    return results;
}

}  // namespace planning
}  // namespace pnc_x
