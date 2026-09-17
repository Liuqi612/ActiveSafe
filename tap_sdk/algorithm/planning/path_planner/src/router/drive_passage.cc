

#include <algorithm>
#include <boost/optional.hpp>
#include <cmath>
#include <typeindex>
#include <iterator>
#include <limits>
#include <typeindex>
#include <typeinfo>

#include "math/geometry/segment2d.h"
#include "math/util.h"
#include "router/drive_passage.h"
#include "util/status_builder.h"
#include "util/status_macros.h"
#include <absl/strings/str_format.h>

namespace pnc_x {
namespace planning {

mapping::LanePoint StationCenter::GetLanePoint() const {
    return mapping::LanePoint(lane_id, fraction);
}

Vec2d StationCenter::lat_point(double signed_offset) const {
    return xy + tangent.Perp() * signed_offset;
}
Vec2d StationCenter::lon_point(double signed_offset) const {
    return xy + tangent * signed_offset;
}
double StationCenter::lat_offset(const Vec2d &v) const {
    return tangent.CrossProd(v - xy);
}
double StationCenter::lon_offset(const Vec2d &v) const {
    return tangent.Dot(v - xy);
}

std::string StationBoundaryTypeName(StationBoundaryType type) { return "TODO"; }

bool StationBoundary::IsSolid(double query_lat_offset) const {
    constexpr double kEpsilon = 0.5;
    switch (type) {
        case StationBoundaryType::SOLID_WHITE:
        case StationBoundaryType::SOLID_YELLOW:
        case StationBoundaryType::SOLID_DOUBLE_YELLOW:
        case StationBoundaryType::CURB:
        case StationBoundaryType::VIRTUAL_CURB:
            return true;
        case StationBoundaryType::BROKEN_LEFT_DOUBLE_WHITE:
            return query_lat_offset < lat_offset - kEpsilon;
        case StationBoundaryType::BROKEN_RIGHT_DOUBLE_WHITE:
            return query_lat_offset > lat_offset + kEpsilon;
        case StationBoundaryType::UNKNOWN_TYPE:
        case StationBoundaryType::BROKEN_WHITE:
        case StationBoundaryType::BROKEN_YELLOW:
        case StationBoundaryType::VIRTUAL_LANE:
            return false;
        default:
            throw std::runtime_error("switch case on enum unexpected");
    }
}

Station::Station(StationCenter center, std::vector<StationBoundary> bounds)
    : center_(std::move(center)), boundaries_(std::move(bounds)) {}

mapping::ElementId Station::lane_id() const { return center_.lane_id; }
const Vec2d &Station::xy() const { return center_.xy; }
const Vec2d &Station::tangent() const { return center_.tangent; }
double Station::accumulated_s() const { return center_.accum_s; }
double Station::speed_limit() const { return center_.speed_limit; }
bool Station::is_virtual() const { return center_.is_virtual; }

StationInfo Station::station_info() const { return center_.station_info; }
bool Station::is_merging() const { return center_.is_merging; }
bool Station::is_splitting() const { return center_.is_splitting; }
bool Station::is_in_wide_lane() const { return center_.is_in_wide_lane; }
bool Station::is_in_intersection() const { return center_.is_in_intersection; }
bool Station::has_cross_curb() const { return center_.has_cross_curb; }
ads_x::planning::TurnType Station::turn_type() const {
    return center_.turn_type;
}

Vec2d Station::lat_point(double signed_offset) const {
    return center_.lat_point(signed_offset);
}
Vec2d Station::lon_point(double signed_offset) const {
    return center_.lon_point(signed_offset);
}
double Station::lat_offset(const Vec2d &v) const {
    return center_.lat_offset(v);
}
double Station::lon_offset(const Vec2d &v) const {
    return center_.lon_offset(v);
}

absl::Span<const StationBoundary> Station::boundaries() const {
    return boundaries_;
}

mapping::LanePoint Station::GetLanePoint() const {
    return center_.GetLanePoint();
}

const bool DrivePassage::GetIsChangeAbnormal() const {
    return is_change_abnormal_;
}
void DrivePassage::SetIsChangeAbnormal(bool is_change_abnormal) {
    is_change_abnormal_ = is_change_abnormal;
}
const bool DrivePassage::GetIsChangeAbnormalForDegrade() const {
    return is_change_abnormal_for_degrade_;
}
void DrivePassage::SetIsChangeAbnormalForDegrade(
    bool is_change_abnormal_for_degrade) {
    is_change_abnormal_for_degrade_ = is_change_abnormal_for_degrade;
}

const int DrivePassage::GetAbnormalStep() const { return abnormal_step_; }
void DrivePassage::SetAbnormalStep(int abnormal_step) {
    abnormal_step_ = abnormal_step;
}

TurnType DrivePassage::GetEgoTurnType() const { return ego_turn_type_; }
void DrivePassage::SetEgoTurnType(TurnType ego_turn_type) {
    ego_turn_type_ = ego_turn_type;
}

bool DrivePassage::GetHasSplit() const { return has_split_; };
void DrivePassage::SetHasSplit(bool has_split) { has_split_ = has_split; };

bool DrivePassage::GetIsOnRamp() const { return is_on_ramp_; }
void DrivePassage::SetIsOnRamp(bool is_on_ramp) { is_on_ramp_ = is_on_ramp; }

void DrivePassage::SetAdFunctionType(AD_FunctionType ad_function_type) {
    ad_function_type_ = ad_function_type;
};
AD_FunctionType DrivePassage::GetAdFunctionType() const {
    return ad_function_type_;
}

void DrivePassage::SetAdLateralState(AD_LateralState ad_lateral_state) {
    ad_lateral_state_ = ad_lateral_state;
}
AD_LateralState DrivePassage::GetAdLateralState() const {
    return ad_lateral_state_;
}

absl::StatusOr<std::pair<double, double>> Station::QueryCurbOffsetAt(
    double signed_lat) const {
    const double right_offset = boundaries_.front().lat_offset;
    const double left_offset = boundaries_.back().lat_offset;
    if (signed_lat < right_offset || signed_lat > left_offset) {
        return absl::OutOfRangeError(
            absl::StrFormat("Lateral offset %.2f out of range [%.2f, %.2f]!",
                            signed_lat, right_offset, left_offset));
    }

    return std::make_pair(right_offset - signed_lat, left_offset - signed_lat);
}

absl::StatusOr<BoundaryQueryResponse> Station::QueryEnclosingLaneBoundariesAt(
    double signed_lat) const {
    const double right_offset = boundaries_.front().lat_offset;
    const double left_offset = boundaries_.back().lat_offset;
    if (signed_lat < right_offset || signed_lat > left_offset) {
        return absl::OutOfRangeError(
            absl::StrFormat("Lateral offset %.2f out of range [%.2f, %.2f]!",
                            signed_lat, right_offset, left_offset));
    }

    const auto it = std::upper_bound(
        boundaries_.begin(), boundaries_.end(), signed_lat,
        [](double val, const auto &it) { return val < it.lat_offset; });

    BoundaryQueryResponse res;
    res.right = *std::prev(it);
    res.right->lat_offset -= signed_lat;
    res.left = it == boundaries_.end()
                   ? boost::none
                   : OptionalBoundary(StationBoundary{
                         it->type, it->lat_offset - signed_lat});
    return res;
}

DrivePassage::DrivePassage(StationVector<Station> stations,
                           mapping::LanePath lane_path,
                           mapping::LanePath extend_lane_path,
                           double lane_path_start_s,
                           bool reach_destination,
                           FrenetFrameType type,
                           std::vector<int> change_index,
                           ads_x::planning::LaneSeqInfoPtr lane_seq_info)
    : stations_(std::move(stations)),
      lane_path_(std::move(lane_path)),
      extend_lane_path_(std::move(extend_lane_path)),
      beyond_lane_path_(lane_path_.IsEmpty()
                            ? false
                            : lane_path_.back() != extend_lane_path_.back()),
      reach_destination_(reach_destination),
      lane_path_start_s_(lane_path_start_s),
      type_(type),
      lane_seq_info_(lane_seq_info),
      change_index_(change_index) {
    const int n = stations_.size();
    last_real_station_index_ = StationIndex(n - 1);
    for (const auto index : stations_.index_range()) {
        if (stations_[index].lane_id() == mapping::kInvalidElementId) {
            last_real_station_index_ = StationIndex(index.value() - 1);
            break;
        }
    }
    center_seg_inv_len_.reserve(static_cast<size_t>(n - 1));
    segments_.reserve(static_cast<size_t>(n - 1));
    for (const auto index : stations_.index_from(1)) {
        const StationIndex prev_index(index.value() - 1);
        center_seg_inv_len_.emplace_back(
            1.0 / stations_[prev_index].xy().DistanceTo(stations_[index].xy()));
        segments_.emplace_back(stations_[prev_index].xy(),
                               stations_[index].xy());
    }
    BuildFrenetFrame();
}

absl::StatusOr<double> DrivePassage::QuerySpeedLimitAt(
    const Vec2d &point) const {
    return FindNearestStation(point).speed_limit();
}

absl::StatusOr<double> DrivePassage::QuerySpeedLimitAtS(double s) const {
    if (empty() || size() < 2) {
        return absl::OutOfRangeError("Station is empty!");
    }
    if (s < front_s() || s > end_s()) {
        return absl::OutOfRangeError(
            absl::StrFormat("%.2f is out of accumulated_s range [%.2f, %.2f].",
                            s, front_s(), end_s()));
    }

    const auto result = BinarySearchForNearStation(s);
    return stations_[result.near_station_index].speed_limit();
}

absl::StatusOr<std::pair<double, double>> DrivePassage::QueryCurbOffsetAt(
    const Vec2d &point) const {
    ASSIGN_OR_RETURN(const auto projection,
                     ProjectPointToStations(point, true));
    const auto status = IsProjectionResultOnDrivePassage(projection);
    if (!status.ok()) {
        return status;
    }
    const auto &station = stations_[projection.near_station_index];

    return station.QueryCurbOffsetAt(projection.signed_l);
}

absl::StatusOr<std::pair<double, double>>
DrivePassage::QueryNearestBoundaryLateralOffset(double s) const {
    if (s < front_s() || s > end_s()) {
        return absl::OutOfRangeError(
            absl::StrFormat("%.2f is out of accumulated_s range [%.2f, %.2f].",
                            s, front_s(), end_s()));
    }
    const auto result = BinarySearchForNearStation(s);
    const auto &near_station = stations_[result.near_station_index];
    double right_offset = std::numeric_limits<double>::lowest();
    double left_offset = std::numeric_limits<double>::max();
    for (const auto &bound : near_station.boundaries()) {
        if (bound.lat_offset < 0.0) {
            right_offset = std::max(right_offset, bound.lat_offset);
        }
        if (bound.lat_offset > 0.0) {
            left_offset = std::min(left_offset, bound.lat_offset);
        }
    }
    return std::make_pair(right_offset, left_offset);
}

absl::StatusOr<std::pair<double, double>> DrivePassage::QueryCurbOffsetAtS(
    double s) const {
    if (s < front_s() || s > end_s()) {
        return absl::OutOfRangeError(
            absl::StrFormat("%.2f is out of accumulated_s range [%.2f, %.2f].",
                            s, front_s(), end_s()));
    }

    const auto result = BinarySearchForNearStation(s);
    return stations_[result.near_station_index].QueryCurbOffsetAt(0.0);
}

absl::StatusOr<std::pair<Vec2d, Vec2d>> DrivePassage::QueryCurbPointAt(
    const Vec2d &point) const {
    ASSIGN_OR_RETURN(const auto projection,
                     ProjectPointToStations(point, true));
    const auto status = IsProjectionResultOnDrivePassage(projection);
    if (!status.ok()) {
        return status;
    }
    const auto &station = stations_[projection.near_station_index];
    ASSIGN_OR_RETURN(const auto offsets,
                     station.QueryCurbOffsetAt(projection.signed_l));
    const Vec2d normal = station.tangent().Perp();

    return std::make_pair(point + normal * offsets.first,
                          point + normal * offsets.second);
}

absl::StatusOr<std::pair<Vec2d, Vec2d>> DrivePassage::QueryCurbPointAtS(
    double s) const {
    if (s < front_s() || s > end_s()) {
        return absl::OutOfRangeError(
            absl::StrFormat("%.2f is out of accumulated_s range [%.2f, %.2f].",
                            s, front_s(), end_s()));
    }
    const auto result = BinarySearchForNearStation(s);
    const auto &near_station = stations_[result.near_station_index];
    ASSIGN_OR_RETURN(const auto offsets, near_station.QueryCurbOffsetAt(0.0));
    const auto &prev_station = stations_[result.station_index_1];
    const auto &succ_station = stations_[result.station_index_2];
    const double t = result.ds / (succ_station.accumulated_s() -
                                  prev_station.accumulated_s());
    const auto normal = Vec2d::FastUnitFromAngle(
                            LerpAngle(prev_station.tangent().FastAngle(),
                                      succ_station.tangent().FastAngle(), t))
                            .Perp();
    const auto center = Lerp(prev_station.xy(), succ_station.xy(), t);
    return std::make_pair(center + normal * offsets.first,
                          center + normal * offsets.second);
}

absl::StatusOr<BoundaryQueryResponse>
DrivePassage::QueryEnclosingLaneBoundariesAt(const Vec2d &point) const {
    ASSIGN_OR_RETURN(const auto projection,
                     ProjectPointToStations(point, true));
    const auto status = IsProjectionResultOnDrivePassage(projection);
    if (!status.ok()) {
        return status;
    }
    const auto &station = stations_[projection.near_station_index];

    return station.QueryEnclosingLaneBoundariesAt(projection.signed_l);
}

BoundaryQueryResponse DrivePassage::QueryEnclosingLaneBoundariesAtS(
    double s) const {
    const auto station_index = FindNearestStationIndexAtS(s);

    return stations_[station_index].QueryEnclosingLaneBoundariesAt(0.0).value();
}

absl::StatusOr<std::pair<Station, Station>> DrivePassage::GetNearStation(
    double s) const {
    const auto result = BinarySearchForNearStation(s);
    const auto &prev_station = stations_[result.station_index_1];
    const auto &succ_station = stations_[result.station_index_2];
    return std::make_pair(prev_station, succ_station);
}

absl::StatusOr<Vec2d> DrivePassage::QueryLaterallyUnboundedTangentAt(
    const Vec2d &point) const {
    ASSIGN_OR_RETURN(const auto projection,
                     ProjectPointToStations(point, true));
    return stations_[projection.station_index_1].tangent();
}

absl::StatusOr<Vec2d> DrivePassage::QueryTangentAt(const Vec2d &point) const {
    ASSIGN_OR_RETURN(const auto projection,
                     ProjectPointToStations(point, true));
    const auto status = IsProjectionResultOnDrivePassage(projection);
    if (!status.ok()) {
        return status;
    }

    return stations_[projection.station_index_1].tangent();
}

absl::StatusOr<Vec2d> DrivePassage::QueryTangentAtS(double s) const {
    ASSIGN_OR_RETURN(const auto angle, QueryTangentAngleAtS(s));
    return Vec2d::FastUnitFromAngle(angle);
}

absl::StatusOr<double> DrivePassage::QueryTangentAngleAtS(double s) const {
    if (s < front_s() || s > end_s()) {
        return absl::OutOfRangeError(
            absl::StrFormat("%.2f is out of accumulated_s range [%.2f, %.2f].",
                            s, front_s(), end_s()));
    }

    const auto result = BinarySearchForNearStation(s);
    const auto &prev_station = stations_[result.station_index_1];
    const auto &succ_station = stations_[result.station_index_2];

    const double t = result.ds / (succ_station.accumulated_s() -
                                  prev_station.accumulated_s());
    return NormalizeAngle(LerpAngle(prev_station.tangent().FastAngle(),
                                    succ_station.tangent().FastAngle(), t));
}

absl::StatusOr<Vec2d> DrivePassage::QueryPointXYAtS(double s) const {
    if (s < front_s() || s > end_s()) {
        return absl::OutOfRangeError(
            absl::StrFormat("%.2f is out of accumulated_s range [%.2f, %.2f].",
                            s, front_s(), end_s()));
    }

    const auto result = BinarySearchForNearStation(s);

    return stations_[result.station_index_1].xy() +
           stations_[result.station_index_1].tangent() * result.ds;
}

absl::StatusOr<Vec2d> DrivePassage::QueryPointXYAtSL(double s, double l) const {
    if (s < front_s() || s > end_s()) {
        return absl::OutOfRangeError(
            absl::StrFormat("%.2f is out of accumulated_s range [%.2f, %.2f].",
                            s, front_s(), end_s()));
    }
    const auto result = BinarySearchForNearStation(s);
    const auto ref_tangent = stations_[result.station_index_1].tangent();
    const auto ref_xy = stations_[result.station_index_1].xy() +
                        stations_[result.station_index_1].tangent() * result.ds;

    const Vec2d normal = ref_tangent.Perp();

    return ref_xy + normal * l;
}

absl::StatusOr<StationWaypoint> DrivePassage::QueryFrenetLonOffsetAt(
    const Vec2d &point) const {
    ASSIGN_OR_RETURN(const auto projection,
                     ProjectPointToStations(point, true));
    const auto status = IsProjectionResultOnDrivePassage(projection);
    if (!status.ok()) {
        return status;
    }

    return StationWaypoint{
        .station_index = projection.near_station_index,
        .lon_offset = projection.accum_s -
                      stations_[projection.near_station_index].accumulated_s(),
        .accum_s = projection.accum_s};
}

absl::StatusOr<double> DrivePassage::QueryFrenetLatOffsetAt(
    const Vec2d &point) const {
    ASSIGN_OR_RETURN(const auto projection,
                     ProjectPointToStations(point, true));
    const auto status = IsProjectionResultOnDrivePassage(projection);
    if (!status.ok()) {
        return status;
    }

    return projection.signed_l;
}

absl::StatusOr<FrenetCoordinate>
DrivePassage::QueryLaterallyUnboundedFrenetCoordinateAt(
    const Vec2d &point) const {
    ASSIGN_OR_RETURN(const auto projection,
                     ProjectPointToStations(point, true));
    FrenetCoordinate result;
    result.s = projection.accum_s;
    result.l = projection.signed_l;
    return result;
}

absl::StatusOr<FrenetCoordinate> DrivePassage::QueryUnboundedFrenetCoordinateAt(
    const Vec2d &point) const {
    ASSIGN_OR_RETURN(const auto projection,
                     ProjectPointToStations(point, true));

    FrenetCoordinate result;
    result.s = projection.accum_s;
    result.l = projection.signed_l;
    return result;
}

absl::StatusOr<FrenetCoordinate> DrivePassage::QueryFrenetCoordinateAt(
    const Vec2d &point) const {
    ASSIGN_OR_RETURN(const auto projection,
                     ProjectPointToStations(point, true));
    const auto status = IsProjectionResultOnDrivePassage(projection);
    if (!status.ok()) {
        return status;
    }
    FrenetCoordinate result;
    result.s = projection.accum_s;
    result.l = projection.signed_l;
    return result;
}

absl::StatusOr<FrenetBox> DrivePassage::QueryFrenetBoxAt(
    const Box2d &box, bool zone_checking) const {
    return QueryFrenetBoxAtContourPoints(box.GetCornersCounterClockwise(),
                                         zone_checking);
}

absl::StatusOr<FrenetBox> DrivePassage::QueryFrenetBoxAtContour(
    const Polygon2d &contour, bool zone_checking) const {
    return QueryFrenetBoxAtContourPoints(contour.points(), zone_checking);
}

absl::StatusOr<FrenetBox> DrivePassage::QueryFrenetBoxAtContourPoints(
    absl::Span<const Vec2d> contour_points, bool zone_checking) const {
    if (frenet_frame_.get() == nullptr) {
        return absl::InternalError(
            "Failed to project contour points because of null frenet_frame_ "
            "pointer.");
    }
    bool beyond_front_s = false, behind_end_s = false,
         left_of_right_curb = false, right_of_left_curb = false;
    FrenetBox frenet_box;
    frenet_box.s_max = -std::numeric_limits<double>::infinity();
    frenet_box.s_min = std::numeric_limits<double>::infinity();
    frenet_box.l_max = -std::numeric_limits<double>::infinity();
    frenet_box.l_min = std::numeric_limits<double>::infinity();

    auto update_frenet_box = [&](double accum_s, double signed_l,
                                 const StationIndex near_station_index) {
        if (accum_s > front_s()) beyond_front_s = true;
        if (accum_s < end_s()) behind_end_s = true;

        const auto curb_offsets =
            stations_[near_station_index].QueryCurbOffsetAt(0.0).value();
        const double right_curb = curb_offsets.first;
        const double left_curb = curb_offsets.second;
        if (signed_l > right_curb) left_of_right_curb = true;
        if (signed_l < left_curb) right_of_left_curb = true;

        const double final_s = zone_checking
                                   ? boost::algorithm::clamp(accum_s, front_s(),
                                                             end_s())
                                   : accum_s;
        const double final_l = zone_checking
                                   ? boost::algorithm::clamp(
                                         signed_l, right_curb, left_curb)
                                   : signed_l;
        frenet_box.s_max = std::max(frenet_box.s_max, final_s);
        frenet_box.s_min = std::min(frenet_box.s_min, final_s);
        frenet_box.l_max = std::max(frenet_box.l_max, final_l);
        frenet_box.l_min = std::min(frenet_box.l_min, final_l);
    };

    if (type_ == FrenetFrameType::kBvh) {
        std::vector<FrenetCoordinate> sls;
        std::vector<Vec2d> normals;
        std::vector<int> indices;
        std::vector<double> alphas;
        frenet_frame_->XYToSLBatch(contour_points, &sls, &normals, &indices,
                                   &alphas);
        const auto &raw_indices = frenet_frame_->raw_indices();
        const int raw_size = static_cast<int>(raw_indices.size());
        const int station_size = static_cast<int>(stations_.size());

        for (size_t i = 0; i < contour_points.size(); ++i) {
            const int index = indices[i];
            if ((index < 0) || (index + 1 >= raw_size)) {
                return absl::NotFoundError("No valid projection is found.");
            }
            const int raw_idx_prev = raw_indices[static_cast<size_t>(index)];
            const int raw_idx_next = raw_indices[static_cast<size_t>(index + 1)];
            if ((raw_idx_prev < 0) || (raw_idx_next < 0) ||
                (raw_idx_prev >= station_size) || (raw_idx_next >= station_size)) {
                return absl::InternalError(
                    "Raw index from frenet frame is out of station range.");
            }
            const auto prev_station_idx = StationIndex(raw_idx_prev);
            const auto next_station_idx = StationIndex(raw_idx_next);
            const auto near_station_idx =
                alphas[i] < 0.5 ? prev_station_idx : next_station_idx;
            const double accum_s =
                Lerp(stations_[prev_station_idx].accumulated_s(),
                     stations_[next_station_idx].accumulated_s(), alphas[i]);
            update_frenet_box(accum_s, sls[i].l, near_station_idx);
        }
    } else {
        for (const auto &pt : contour_points) {
            ASSIGN_OR_RETURN(const auto projection,
                             ProjectPointToStations(pt, true));
            update_frenet_box(projection.accum_s, projection.signed_l,
                              projection.near_station_index);
        }
    }

    if (zone_checking &&
        !(beyond_front_s && behind_end_s && left_of_right_curb &&
          right_of_left_curb)) {
        return absl::NotFoundError("Box has no overlap with drive passage.");
    }

    return frenet_box;
}

absl::StatusOr<std::vector<boost::optional<FrenetBox>>>
DrivePassage::BatchQueryFrenetBoxes(absl::Span<const Box2d> boxes,
                                    bool laterally_bounded) const {
    if (boxes.empty()) return absl::FailedPreconditionError("");

    const int n = boxes.size();
    std::vector<boost::optional<FrenetBox>> results;
    results.reserve(static_cast<size_t>(n));

    const auto &first_box = boxes.front();
    ASSIGN_OR_RETURN(auto prev_projection,
                     ProjectPointToStations(first_box.center(), true));

    ASSIGN_OR_RETURN(
        auto frenet_box,
        QueryFrenetBoxWithinRadius(first_box, prev_projection,
                                   first_box.radius(), laterally_bounded));
    results.push_back(frenet_box);

    for (int i = 1; i < n; ++i) {
        const auto &prev_box = boxes[static_cast<size_t>(i - 1)];
        const auto &box = boxes[static_cast<size_t>(i)];
        constexpr double kSearchExpansionRatio = 2.0;
        const double state_search_radius =
            (prev_box.center() - box.center()).Length() * kSearchExpansionRatio;
        ASSIGN_OR_RETURN(const auto projection,
                         ProjectPointToStationsWithinRadius(
                             box.center(), prev_projection, prev_box.center(),
                             state_search_radius));
        ASSIGN_OR_RETURN(frenet_box,
                         QueryFrenetBoxWithinRadius(
                             box, projection, box.radius(), laterally_bounded));
        results.push_back(frenet_box);
        prev_projection = projection;
    }

    return results;
}

absl::StatusOr<boost::optional<FrenetBox>>
DrivePassage::QueryFrenetBoxWithinRadius(
    const Box2d &box,
    const ProjectionResult &center_projection,
    double search_radius,
    bool laterally_bounded) const {
    if (frenet_frame_.get() == nullptr) {
        return absl::InternalError(
            "Failed to project box points because of null frenet_frame_ "
            "pointer.");
    }
    bool beyond_front_s = false, behind_end_s = false,
         left_of_right_curb = false, right_of_left_curb = false;
    FrenetBox frenet_box;
    frenet_box.s_max = -std::numeric_limits<double>::infinity();
    frenet_box.s_min = std::numeric_limits<double>::infinity();
    frenet_box.l_max = -std::numeric_limits<double>::infinity();
    frenet_box.l_min = std::numeric_limits<double>::infinity();
    const auto corners = box.GetCornersCounterClockwise();
    auto update_frenet_box = [&](ProjectionResult projection) {
        if (projection.accum_s > front_s()) beyond_front_s = true;
        if (projection.accum_s < end_s()) behind_end_s = true;
        projection.accum_s =
            boost::algorithm::clamp(projection.accum_s, front_s(), end_s());

        const auto curb_offsets = stations_[projection.near_station_index]
                                      .QueryCurbOffsetAt(0.0)
                                      .value();
        const double right_curb = curb_offsets.first;
        const double left_curb = curb_offsets.second;
        if (projection.signed_l > right_curb) left_of_right_curb = true;
        if (projection.signed_l < left_curb) right_of_left_curb = true;
        if (laterally_bounded) {
            projection.signed_l = boost::algorithm::clamp(
                projection.signed_l, right_curb, left_curb);
        }

        frenet_box.s_max = std::max(frenet_box.s_max, projection.accum_s);
        frenet_box.s_min = std::min(frenet_box.s_min, projection.accum_s);
        frenet_box.l_max = std::max(frenet_box.l_max, projection.signed_l);
        frenet_box.l_min = std::min(frenet_box.l_min, projection.signed_l);
    };

    if (type_ == FrenetFrameType::kBvh) {
        std::vector<FrenetCoordinate> sls;
        std::vector<Vec2d> normals;
        std::vector<int> indices;
        std::vector<double> alphas;
        frenet_frame_->XYToSLBatch(corners, &sls, &normals, &indices, &alphas);
        const auto &raw_indices = frenet_frame_->raw_indices();
        const int raw_size = static_cast<int>(raw_indices.size());
        const int station_size = static_cast<int>(stations_.size());

        for (size_t i = 0; i < corners.size(); ++i) {
            ProjectionResult projection;
            bool use_batch_projection = false;
            const int index = indices[i];
            if ((index >= 0) && (index + 1 < raw_size)) {
                const int raw_idx_prev = raw_indices[static_cast<size_t>(index)];
                const int raw_idx_next = raw_indices[static_cast<size_t>(index + 1)];
                if ((raw_idx_prev >= 0) && (raw_idx_next >= 0) &&
                    (raw_idx_prev < station_size) && (raw_idx_next < station_size)) {
                    const auto prev_station_idx = StationIndex(raw_idx_prev);
                    const auto next_station_idx = StationIndex(raw_idx_next);
                    projection.station_index_1 = prev_station_idx;
                    projection.station_index_2 = next_station_idx;
                    projection.near_station_index =
                        alphas[i] < 0.5 ? prev_station_idx : next_station_idx;
                    projection.accum_s =
                        Lerp(stations_[prev_station_idx].accumulated_s(),
                             stations_[next_station_idx].accumulated_s(),
                             alphas[i]);
                    projection.signed_l = sls[i].l;
                    projection.lerp_factor = alphas[i];
                    if (std::fabs(projection.accum_s - center_projection.accum_s) <=
                        search_radius) {
                        use_batch_projection = true;
                    }
                }
            }

            if (!use_batch_projection) {
                ASSIGN_OR_RETURN(
                    projection,
                    ProjectPointToStationsWithinRadius(
                        corners[i], center_projection, box.center(),
                        search_radius),
                    _ << "No frenet conversion is found.");
            }
            update_frenet_box(projection);
        }
    } else {
        for (const auto &pt : corners) {
            ASSIGN_OR_RETURN(
                auto projection,
                ProjectPointToStationsWithinRadius(pt, center_projection,
                                                   box.center(), search_radius),
                _ << "No frenet conversion is found.");
            update_frenet_box(projection);
        }
    }
    if (!(beyond_front_s && behind_end_s && left_of_right_curb &&
          right_of_left_curb)) {
        return boost::none;
    }

    return frenet_box;
}

absl::StatusOr<Vec2d> DrivePassage::FindNearestPointOnCenterLine(
    const Vec2d &point) const {
    ASSIGN_OR_RETURN(const auto projection,
                     ProjectPointToStations(point, true));
    const auto status = IsProjectionResultOnDrivePassage(projection);
    if (!status.ok()) {
        return status;
    }
    return Lerp(stations_[projection.station_index_1].xy(),
                stations_[projection.station_index_2].xy(),
                projection.lerp_factor);
}

StationIndex DrivePassage::FindNearestStationIndex(const Vec2d &point) const {
    auto min_dis = std::numeric_limits<double>::max();
    StationIndex min_dis_index;
    for (const auto i : stations_.index_range()) {
        const auto &station = stations_[i];
        const auto dis = point.DistanceSquareTo(station.xy());
        if (dis < min_dis) {
            min_dis = dis;
            min_dis_index = i;
        }
    }
    return min_dis_index;
}

StationIndex DrivePassage::FindNearestStationIndexAtS(double s) const {
    const auto it = std::upper_bound(stations_.begin(), stations_.end(), s,
                                     [](double val, const Station &station) {
                                         return val < station.accumulated_s();
                                     });
    if (it == stations_.begin()) return StationIndex(0);
    if (it == stations_.end()) return StationIndex(stations_.size() - 1);

    return std::fabs(it->accumulated_s() - s) <
                   std::fabs(std::prev(it)->accumulated_s() - s)
               ? StationIndex(it - stations_.begin())
               : StationIndex(it - stations_.begin() - 1);
}

absl::StatusOr<DrivePassage::ProjectionResult>
DrivePassage::ProjectPointToStations(const Vec2d &point,
                                     bool allow_extrapolation) const {
    if (frenet_frame_.get() == nullptr) {
        return absl::InternalError(
            "Failed to project point to stations because of null frenet_frame_ "
            "pointer.");
    }

    FrenetCoordinate frenet_pt;
    Vec2d normal;
    std::pair<int, int> raw_index_pair;
    double lerp_factor;

    frenet_frame_->XYToSL(point, &frenet_pt, &normal, &raw_index_pair,
                          &lerp_factor);

    int nearest_index = raw_index_pair.first;
    const auto &nearest_seg = segments_[static_cast<size_t>(nearest_index)];
    const auto prev_station_idx = StationIndex(nearest_index);
    const auto next_station_idx = StationIndex(raw_index_pair.second);
    const auto &prev_station = stations_[prev_station_idx];
    const auto &station = stations_[next_station_idx];
    double l = frenet_pt.l;
    double s = Lerp(prev_station.accumulated_s(), station.accumulated_s(),
                    lerp_factor);

    if (allow_extrapolation) {
        ProjectionResult result;
        result.station_index_1 = prev_station_idx;
        result.station_index_2 = next_station_idx;
        result.near_station_index =
            lerp_factor < 0.5 ? prev_station_idx : next_station_idx;
        result.accum_s = s;
        result.signed_l = l;
        result.lerp_factor = lerp_factor;
        return result;
    }

    if (lerp_factor < 0.0 && nearest_index > 1) {
        l = std::copysign(nearest_seg.start().DistanceTo(point), l);
        s = prev_station.accumulated_s();
        lerp_factor = 0.0;
    } else if ((lerp_factor > 1.0) && (nearest_index + 1 < static_cast<int>(stations_.size()))) {
        l = std::copysign(nearest_seg.end().DistanceTo(point), l);
        s = station.accumulated_s();
        lerp_factor = 1.0;
    }

    constexpr double kEpsilon = 0.1;
    if (s < front_s() - kEpsilon || s > end_s() + kEpsilon) {
        return absl::NotFoundError("No valid projection is found.");
    }
    s = boost::algorithm::clamp(s, front_s(), end_s());

    ProjectionResult result;
    result.station_index_1 = prev_station_idx;
    result.station_index_2 = next_station_idx;
    result.near_station_index =
        lerp_factor < 0.5 ? prev_station_idx : next_station_idx;
    result.accum_s = s;
    result.signed_l = l;
    result.lerp_factor = lerp_factor;
    return result;
}

absl::StatusOr<DrivePassage::ProjectionResult>
DrivePassage::ProjectPointToStationsWithinRadius(
    const Vec2d &point,
    const ProjectionResult &projection,
    const Vec2d &prev_point,
    double search_radius) const {
    const int start_segment_idx = projection.station_index_1.value();
    int nearest_segment_idx = start_segment_idx;
    double min_squared_dist =
        segments_[static_cast<size_t>(start_segment_idx)].DistanceSquareTo(point);
    const double angle_diff =
        NormalizeAngle((point - prev_point).FastAngle() -
                       segments_[static_cast<size_t>(start_segment_idx)].heading());

    std::vector<int> search_step_vec;
    constexpr double kForwardSearchThres = M_PI * 2.0 / 3.0;
    constexpr double kBackwardSearchThres = M_PI / 3.0;
    if (std::fabs(angle_diff) < kForwardSearchThres) {
        search_step_vec.push_back(1);
    }
    if (std::fabs(angle_diff) > kBackwardSearchThres) {
        search_step_vec.push_back(-1);
    }

    for (const auto step : search_step_vec) {
        for (auto idx = start_segment_idx + step;
             (idx >= 0) && (idx < static_cast<int>(segments_.size())); idx += step) {
            double squared_dist = segments_[static_cast<size_t>(idx)].DistanceSquareTo(point);
            if (squared_dist < min_squared_dist) {
                min_squared_dist = squared_dist;
                nearest_segment_idx = idx;
            }
            if (std::fabs(projection.accum_s -
                          stations_[StationIndex(idx)].accumulated_s()) >
                search_radius) {
                break;
            }
        }
    }

    const auto &nearest_seg = segments_[static_cast<size_t>(nearest_segment_idx)];
    const double prod = nearest_seg.ProductOntoUnit(point);
    const double proj = nearest_seg.ProjectOntoUnit(point) *
                        center_seg_inv_len_[static_cast<size_t>(nearest_segment_idx)];
    const auto prev_station_idx = StationIndex(nearest_segment_idx);
    const auto next_station_idx = StationIndex(nearest_segment_idx + 1);
    const auto &prev_station = stations_[prev_station_idx];
    const auto &station = stations_[next_station_idx];

    return ProjectionResult{
        .station_index_1 = prev_station_idx,
        .station_index_2 = next_station_idx,
        .near_station_index = proj < 0.5 ? prev_station_idx : next_station_idx,
        .accum_s =
            Lerp(prev_station.accumulated_s(), station.accumulated_s(), proj),
        .signed_l = prod,
        .lerp_factor = proj};
}

absl::Status DrivePassage::IsProjectionResultOnDrivePassage(
    const ProjectionResult &res) const {
    const auto &near_station = stations_[res.near_station_index];
    if (res.signed_l < 0.0) {
        if (res.signed_l < near_station.boundaries().front().lat_offset) {
            return absl::OutOfRangeError(absl::StrFormat(
                "%f is out of right lateral range %f.", res.signed_l,
                near_station.boundaries().front().lat_offset));
        }
    } else {
        if (res.signed_l > near_station.boundaries().back().lat_offset) {
            return absl::OutOfRangeError(absl::StrFormat(
                "%f is out of left lateral range %f.", res.signed_l,
                near_station.boundaries().back().lat_offset));
        }
    }

    return absl::OkStatus();
}

bool DrivePassage::ContainIntersection(const int check_step) const {
    for (int i = 0; i < stations_.size(); i = i + check_step) {
        if (stations_[StationIndex(i)].is_in_intersection()) {
            return true;
        }
    }
    return false;
}

double DrivePassage::GetDistanceToIntersection(const Vec2d &point) const {
    double min_dis = std::numeric_limits<double>::max();
    int cur_index = FindNearestStationIndex(point).value();
    if (stations_[StationIndex(cur_index)].is_in_intersection()) {
        return 0.0;
    }
    for (int i = cur_index; i < stations_.size(); ++i) {
        const auto &station = stations_[StationIndex(i)];
        if (station.is_in_intersection()) {
            min_dis = std::min(min_dis, station.accumulated_s());
            break;
        }
    }
    return min_dis - stations_[StationIndex(cur_index)].accumulated_s();
}

double DrivePassage::GetDistanceToNonIntersection(const Vec2d &point) const {
    int cur_index = FindNearestStationIndex(point).value();
    if (!stations_[StationIndex(cur_index)].is_in_intersection()) {
        return 0.0;
    }
    for (int i = cur_index; i < stations_.size(); ++i) {
        const auto &station = stations_[static_cast<StationIndex>(i)];
        if (!station.is_in_intersection()) {
            return station.accumulated_s() -
                   stations_[StationIndex(cur_index)].accumulated_s();
        }
    }
    return end_s() - stations_[StationIndex(cur_index)].accumulated_s();
}

const Station &DrivePassage::GetFirstNonIntersectionStation(
    const Vec2d &point) const {
    int cur_index = FindNearestStationIndex(point).value();
    if (!stations_[StationIndex(cur_index)].is_in_intersection()) {
        return stations_[StationIndex(cur_index)];
    }
    for (int i = cur_index; i < stations_.size(); ++i) {
        if (!stations_[static_cast<StationIndex>(i)].is_in_intersection()) {
            return stations_[static_cast<StationIndex>(i)];
        }
    }
    return stations_[StationIndex(cur_index)];
}

DrivePassage::BinarySeachResult DrivePassage::BinarySearchForNearStation(
    double s) const {
    const auto it = std::upper_bound(stations_.begin(), stations_.end(), s,
                                     [](double val, const Station &station) {
                                         return val < station.accumulated_s();
                                     });
    StationIndex prev_index;
    StationIndex next_index;
    if (it == stations_.begin()) {
        prev_index = StationIndex(0);
        next_index = StationIndex(1);
    } else if (it == stations_.end()) {
        prev_index = StationIndex(stations_.size() - 2);
        next_index = StationIndex(stations_.size() - 1);
    } else {
        prev_index = StationIndex(it - stations_.begin() - 1);
        next_index = StationIndex(it - stations_.begin());
    }

    const double ds1 = s - stations_[prev_index].accumulated_s();
    const double ds2 = stations_[next_index].accumulated_s() - s;

    return BinarySeachResult{.station_index_1 = prev_index,
                             .station_index_2 = next_index,
                             .near_station_index = std::abs(ds1) < std::abs(ds2)
                                                       ? prev_index
                                                       : next_index,
                             .ds = ds1};
}

void DrivePassage::BuildFrenetFrame() {
    std::vector<Vec2d> points;
    points.reserve(static_cast<size_t>(stations_.size()));
    for (const auto &station : stations_) {
        points.push_back(station.xy());
    }
    switch (type_) {
        case FrenetFrameType::kBruteFroce:
            frenet_frame_ = std::make_unique<BruteForceFrenetFrame>(
                BuildBruteForceFrenetFrame(points, false).value());
            break;

        case FrenetFrameType::kKdTree:
            frenet_frame_ = std::make_unique<KdTreeFrenetFrame>(
                BuildKdTreeFrenetFrame(points, false).value());

            break;
        case FrenetFrameType::kQtfmKdTree:
            frenet_frame_ = std::make_unique<QtfmEnhancedKdTreeFrenetFrame>(
                BuildQtfmEnhancedKdTreeFrenetFrame(points, false).value());
            break;
        case FrenetFrameType::kRTree:
            frenet_frame_ = std::make_unique<RTreeFrenetFrame>(
                BuildRTreeFrenetFrame(points, false).value());
            break;
        case FrenetFrameType::kBvh:
            {
                auto frame_or = BuildBVHFrenetFrame(points, false);
                XCHECK(frame_or.ok());
                frenet_frame_ = std::move(frame_or).value();
            }
            break;
    }

    XCHECK_EQ(frenet_frame_->points().size(), stations_.size());
}

DrivePassage::DrivePassage(DrivePassage const &o)
    : stations_(o.stations_),
      last_real_station_index_(o.last_real_station_index_),
      center_seg_inv_len_(o.center_seg_inv_len_),
      lane_path_(o.lane_path_),
      extend_lane_path_(o.extend_lane_path_),
      beyond_lane_path_(o.beyond_lane_path_),
      reach_destination_(o.reach_destination_),
      lane_path_start_s_(o.lane_path_start_s_),
      segments_(o.segments_),
      type_(o.type_),
      lane_seq_info_(o.lane_seq_info_),
      change_index_(o.change_index_),
      ego_turn_type_(o.ego_turn_type_),
      has_split_(o.has_split_),
      is_on_ramp_(o.is_on_ramp_) {
    BuildFrenetFrame();
}

DrivePassage &DrivePassage::operator=(DrivePassage const &o) {
    stations_ = o.stations_;
    last_real_station_index_ = o.last_real_station_index_;
    center_seg_inv_len_ = o.center_seg_inv_len_;
    lane_path_ = o.lane_path_;
    extend_lane_path_ = o.extend_lane_path_;
    beyond_lane_path_ = o.beyond_lane_path_;
    reach_destination_ = o.reach_destination_;
    lane_path_start_s_ = o.lane_path_start_s_;
    segments_ = o.segments_;
    type_ = o.type_;
    ego_turn_type_ = o.ego_turn_type_;
    has_split_ = o.has_split_;
    is_on_ramp_ = o.is_on_ramp_;
    BuildFrenetFrame();
    return *this;
}

const Station &DrivePassage::FindNearestStation(const Vec2d &point) const {
    return stations_[FindNearestStationIndex(point)];
}
const Station &DrivePassage::FindNearestStationAtS(double s) const {
    return stations_[FindNearestStationIndexAtS(s)];
}

double DrivePassage::end_s() const { return stations_.back().accumulated_s(); }
double DrivePassage::front_s() const {
    return stations_.front().accumulated_s();
}
double DrivePassage::lane_path_start_s() const { return lane_path_start_s_; }
bool DrivePassage::beyond_lane_path() const { return beyond_lane_path_; }
bool DrivePassage::reach_destination() const { return reach_destination_; }

bool DrivePassage::empty() const { return stations_.size() == 0; }
int DrivePassage::size() const { return stations_.size(); }

const Station &DrivePassage::station(StationIndex index) const {
    return stations_[index];
}
const StationVector<Station> &DrivePassage::stations() const {
    return stations_;
}
StationIndex DrivePassage::last_real_station_index() const {
    return last_real_station_index_;
}
const std::vector<int> &DrivePassage::change_index() const {
    return change_index_;
}

const FrenetFrame *DrivePassage::frenet_frame() const {
    return frenet_frame_.get();
}

const mapping::LanePath &DrivePassage::extend_lane_path() const {
    return extend_lane_path_;
}

const mapping::LanePath &DrivePassage::lane_path() const { return lane_path_; }

const std::vector<Segment2d> &DrivePassage::segments() const {
    return segments_;
}
const ads_x::planning::LaneSeqInfoPtr DrivePassage::lane_seq_info() const {
    return lane_seq_info_;
}

void DrivePassage::InitRoadBoundaryRTree() {
    std::vector<RTreeValue> values;
    for (const auto &pair : road_boundary_map_) {
        const auto &boundary = pair.second;
        if (!boundary || (boundary->points().size() < 2)) { continue; }
        if (boundary->type().boundary_type ==
            ads_x::planning::BoundaryType::VIRTUAL)
            continue;

        const auto &points = boundary->points();
        pnc_x::mapping::SegmentId seg_id(0);
        for (size_t i = 0; i < points.size() - 1; ++i, ++seg_id) {
            const auto &p1 = points[i];
            const auto &p2 = points[i + 1];

            RTreeBox box(RTreePoint(std::min(p1.x(), p2.x()),
                                    std::min(p1.y(), p2.y())),
                         RTreePoint(std::max(p1.x(), p2.x()),
                                    std::max(p1.y(), p2.y())));

            values.emplace_back(box, std::make_pair(boundary->id(), seg_id));
        }
    }
    road_boundary_rtree_ = RoadBoundaryRTree(values.begin(), values.end());
}

ads_x::planning::RoadBoundaryConstPtr DrivePassage::GetRoadBoundaryById(
    const uint64_t id) const {
    if (road_boundary_map_.find(id) == road_boundary_map_.end()) return nullptr;
    if (road_boundary_map_.at(id)->type().boundary_type ==
        ads_x::planning::BoundaryType::VIRTUAL)
        return nullptr;
    return road_boundary_map_.at(id);
}

std::vector<pnc_x::mapping::v2::Segment>
DrivePassage::FindRoadBoundarySegmentsInRadius(double lon, double lat,
                                               double radius) const {
    if (road_boundary_rtree_.empty()) return {};

    RTreeBox query_box(RTreePoint(lon - radius, lat - radius),
                       RTreePoint(lon + radius, lat + radius));

    std::vector<RTreeValue> result_values;
    road_boundary_rtree_.query(boost::geometry::index::intersects(query_box),
                               std::back_inserter(result_values));

    std::vector<pnc_x::mapping::v2::Segment> segments;
    Vec2d point(lon, lat);

    for (const auto &val : result_values) {
        auto element_id = val.second.first;
        auto segment_id = val.second.second;

        auto boundary = GetRoadBoundaryById(element_id);
        if (!boundary) continue;

        size_t idx = static_cast<size_t>(segment_id.value());
        if (idx + 1 >= boundary->points().size()) continue;

        if (Segment2d(boundary->points()[idx], boundary->points()[idx + 1])
                .DistanceSquareTo(point) <= radius * radius) {
            segments.push_back(
                {.element_id = element_id, .segment_id = segment_id});
        }
    }
    return segments;
}

std::vector<ImpassableBoundaryInfo> DrivePassage::GetImpassableBoundariesInfo(
    const Vec2d &smooth_coord, double radius) const {
    const auto curb_vec = FindRoadBoundarySegmentsInRadius(
        smooth_coord.x(), smooth_coord.y(), radius);

    std::vector<ImpassableBoundaryInfo> boundary_infos;
    boundary_infos.reserve(curb_vec.size());

    for (const auto &curb_seg : curb_vec) {
        auto lane_boundary = GetRoadBoundaryById(curb_seg.element_id);
        if (!lane_boundary) continue;

        ImpassableBoundaryInfo boundary_info;
        const size_t seg_idx = static_cast<size_t>(curb_seg.segment_id.value());
        boundary_info.segment =
            Segment2d(lane_boundary->points()[seg_idx],
                      lane_boundary->points()[seg_idx + 1]);
        boundary_info.height =
            lane_boundary->has_height()
                ? boost::make_optional(lane_boundary->height())
                : boost::none;
        boundary_info.id = absl::StrFormat("CURB|%lld|%d", curb_seg.element_id,
                                           curb_seg.segment_id);
        boundary_info.type = lane_boundary->type();
        boundary_infos.emplace_back(std::move(boundary_info));
    }
    return boundary_infos;
}

std::vector<ads_x::planning::RoadBoundaryConstPtr>
DrivePassage::FindRoadBoundariesInRadius(double lon, double lat,
                                         double radius) const {
    if (road_boundary_rtree_.empty()) return {};

    RTreeBox query_box(RTreePoint(lon - radius, lat - radius),
                       RTreePoint(lon + radius, lat + radius));

    std::vector<RTreeValue> result_values;
    road_boundary_rtree_.query(boost::geometry::index::intersects(query_box),
                               std::back_inserter(result_values));

    std::vector<ads_x::planning::RoadBoundaryConstPtr> result;
    absl::flat_hash_set<uint64_t> result_ids;
    Vec2d point(lon, lat);

    for (const auto &val : result_values) {
        auto element_id = val.second.first;
        auto segment_id = val.second.second;

        if (result_ids.contains(element_id)) continue;

        auto boundary = GetRoadBoundaryById(element_id);
        if (!boundary) continue;

        size_t idx = static_cast<size_t>(segment_id.value());
        if (idx + 1 >= boundary->points().size()) continue;

        if (Segment2d(boundary->points()[idx], boundary->points()[idx + 1])
                .DistanceSquareTo(point) <= radius * radius) {
            result.push_back(boundary);
            result_ids.insert(element_id);
        }
    }
    return result;
}

std::vector<ads_x::planning::RoadBoundaryConstPtr>
DrivePassage::GetRoadBoundaries(const Vec2d &smooth_coord,
                                double radius) const {
    const auto boundary_vec =
        FindRoadBoundariesInRadius(smooth_coord.x(), smooth_coord.y(), radius);

    std::vector<ads_x::planning::RoadBoundaryConstPtr> road_boundaries;
    road_boundaries.reserve(boundary_vec.size());
    for (const auto &road_boundary : boundary_vec) {
        ads_x::planning::RoadBoundaryPtr road_boundary_ptr = nullptr;
        if (road_boundary_map_.find(road_boundary->id()) !=
            road_boundary_map_.end()) {
            if (road_boundary_map_.at(road_boundary->id())
                    ->type()
                    .boundary_type != ads_x::planning::BoundaryType::VIRTUAL) {
                road_boundary_ptr = road_boundary_map_.at(road_boundary->id());
            }
        }
        if (road_boundary_ptr == nullptr) continue;
        road_boundaries.push_back(road_boundary_ptr);
    }
    return road_boundaries;
}

}  // namespace planning
}  // namespace pnc_x
