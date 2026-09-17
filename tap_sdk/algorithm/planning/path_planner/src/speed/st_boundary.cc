

#include "speed/st_boundary.h"

#include <algorithm>
#include <boost/optional.hpp>
#include <cmath>

#include <absl/strings/str_cat.h>
#include <absl/strings/str_format.h>

#include "math/geometry/segment2d.h"
#include "math/util.h"
#include "util/loop_guard.h"

namespace pnc_x {
namespace planning {

namespace {

void RemoveRedundantPoints(
    std::vector<std::pair<StPoint, StPoint>> *point_pairs) {
    if (!point_pairs || (point_pairs->size() <= 2)) return;

    constexpr double kMaxDist = 0.01;
    int i = 0;
    int j = 1;

    const auto is_point_near = [](const auto &seg, const Vec2d &point,
                                  double max_dist) {
        return seg.DistanceSquareTo(point) < Sqr(max_dist);
    };
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while ((i < static_cast<int>(point_pairs->size())) &&
           (j + 1 < static_cast<int>(point_pairs->size())) &&
           loop_guard) {
        const Segment2d lower_seg(ToVec2d((*point_pairs)[i].first),
                                  ToVec2d((*point_pairs)[j + 1].first));
        const Segment2d upper_seg(ToVec2d((*point_pairs)[i].second),
                                  ToVec2d((*point_pairs)[j + 1].second));
        if (!is_point_near(lower_seg, ToVec2d((*point_pairs)[j].first),
                           kMaxDist) ||
            !is_point_near(upper_seg, ToVec2d((*point_pairs)[j].second),
                           kMaxDist)) {
            ++i;
            if (i != j) {
                (*point_pairs)[i] = (*point_pairs)[j];
            }
        }
        ++j;
    }
    (*point_pairs)[++i] = point_pairs->back();
    point_pairs->resize(i + 1);
}

}  // namespace

StBoundary::StBoundary(std::vector<std::pair<StPoint, StPoint>> point_pairs,
                       std::vector<VtPoint> speed_points,
                       std::vector<OverlapInfo> overlap_infos,
                       std::vector<NearestSlPoint> nearest_sl_points,
                       StBoundaryProto::ObjectType object_type,
                       std::string id,
                       double probability,
                       bool is_stationary,
                       StBoundaryProto::ProtectionType protection_type,
                       bool is_large_vehicle,
                       bool is_traffic_light,
                       boost::optional<StOverlapMetaProto> overlap_meta,
                       boost::optional<std::string> protected_st_boundary_id,
                       ObjectSlInfo obj_sl_info,
                       ObjectScenarioInfo obj_scenario_info,
                       SecondOrderTrajectoryPoint pose)
    : object_type_(object_type),
      source_type_(ObjectTypeToSourceType(object_type)),
      protection_type_(protection_type),
      speed_points_(std::move(speed_points)),
      overlap_infos_(std::move(overlap_infos)),
      nearest_sl_points_(std::move(nearest_sl_points)),
      id_(std::move(id)),
      traj_id_(RecoverTrajId(id_, source_type_)),
      object_id_(RecoverObjectId(id_, source_type_)),
      probability_(probability),
      is_stationary_(is_stationary),
      is_large_vehicle_(is_large_vehicle),
      is_traffic_light_(is_traffic_light),
      overlap_meta_(std::move(overlap_meta)),
      protected_st_boundary_id_(std::move(protected_st_boundary_id)),
      obj_sl_info_(obj_sl_info),
      obj_scenario_info_(obj_scenario_info),
      pose_(pose) {
    Init(std::move(point_pairs));
}

void StBoundary::Init(std::vector<std::pair<StPoint, StPoint>> point_pairs) {
    RemoveRedundantPoints(&point_pairs);

    lower_points_.clear();
    upper_points_.clear();
    lower_points_.reserve(point_pairs.size());
    upper_points_.reserve(point_pairs.size());
    points_.clear();
    points_.reserve(point_pairs.size() * 2);

    for (const auto &item : point_pairs) {
        const double t = item.first.t();
        lower_points_.emplace_back(item.first.s(), t);
        upper_points_.emplace_back(item.second.s(), t);
    }

    for (const auto &point : lower_points_) {
        points_.emplace_back(point.t(), point.s());
    }

    for (auto rit = upper_points_.rbegin(); rit != upper_points_.rend();
         ++rit) {
        points_.emplace_back(rit->t(), rit->s());
    }

    XCHECK(lower_points_.size() == upper_points().size());
    BuildFromPoints();

    for (const auto &point : lower_points_) {
        min_s_ = std::fmin(min_s_, point.s());
    }
    for (const auto &point : upper_points_) {
        max_s_ = std::fmax(max_s_, point.s());
    }

    min_t_ = lower_points_.front().t();
    max_t_ = lower_points_.back().t();
}

bool StBoundary::IsValid(
    const std::vector<std::pair<StPoint, StPoint>> &point_pairs) const {
    if (point_pairs.size() < 2) {
        // AD_LWARN(PP) << "point_pairs.size() must > 2. current
        // point_pairs.size() = "
        //              << point_pairs.size();
        return false;
    }

    constexpr double kStBoundaryEpsilon = 1e-9;
    constexpr double kMinDeltaT = 1e-6;
    for (int i = 0; i < point_pairs.size(); ++i) {
        const auto &curr_lower = point_pairs[i].first;
        const auto &curr_upper = point_pairs[i].second;
        if (curr_upper.s() < curr_lower.s()) {
            // AD_LWARN(PP) << "s is not increasing";
            return false;
        }

        if (std::fabs(curr_lower.t() - curr_upper.t()) > kStBoundaryEpsilon) {
            // AD_LWARN(PP) << "t diff is larger in each StPoint pair";
            return false;
        }

        if (i + 1 != point_pairs.size()) {
            const auto &next_lower = point_pairs[i + 1].first;
            const auto &next_upper = point_pairs[i + 1].second;
            if (std::fmax(curr_lower.t(), curr_upper.t()) + kMinDeltaT >=
                std::fmin(next_lower.t(), next_upper.t())) {
                // AD_LWARN(PP) << "t is not increasing";
                // AD_LWARN(PP) << " curr_lower: " << curr_lower.DebugString();
                // AD_LWARN(PP) << " curr_upper: " << curr_upper.DebugString();
                // AD_LWARN(PP) << " next_lower: " << next_lower.DebugString();
                // AD_LWARN(PP) << " next_upper: " << next_upper.DebugString();
                return false;
            }
        }
    }
    return true;
}

bool StBoundary::IsPointInBoundary(const StPoint &st_point) const {
    if (st_point.t() <= min_t_ || st_point.t() >= max_t_) {
        return false;
    }
    int left = 0;
    int right = 0;
    if (!GetLowerPointsIndexRange(st_point.t(), &left, &right)) {
        // AD_LWARN(PP) << "failed to get index range.";
        return false;
    }
    XCHECK_NE(left, right);

    const auto cross_prod = [](const Vec2d &start_point,
                               const Vec2d &end_point_1,
                               const Vec2d &end_point_2) {
        return Vec2d(end_point_1 - start_point)
            .CrossProd(Vec2d(end_point_2 - start_point));
    };

    const double check_upper =
        cross_prod(ToVec2d(st_point), ToVec2d(upper_points_[left]),
                   ToVec2d(upper_points_[right]));
    const double check_lower =
        cross_prod(ToVec2d(st_point), ToVec2d(lower_points_[left]),
                   ToVec2d(lower_points_[right]));

    return (check_upper * check_lower < 0);
}

void StBoundary::ExpandByT(double left, double right) {
    // AD_LINFO(PP) << " ====== check time " << left << ", " << right;
    XCHECK_GE(left, 0.0);
    XCHECK_GE(right, 0.0);
    constexpr double kEps = 1e-6;
    if (left < kEps && right < kEps) {
        return;
    }

    std::vector<std::pair<StPoint, StPoint>> point_pairs;
    point_pairs.reserve(lower_points_.size() + 2);
    std::vector<VtPoint> speed_points;
    speed_points.reserve(speed_points_.size() + 2);

    if ((left > 0.0) && (lower_points_.front().t() > 0.0)) {
        const double left_expanded_t =
            std::max(0.0, lower_points_.front().t() - left);
        const StPoint left_expanded_lower_point(lower_points_.front().s(),
                                                left_expanded_t);
        const StPoint left_expanded_upper_point(upper_points_.front().s(),
                                                left_expanded_t);
        const VtPoint left_expanded_speed_point(speed_points_.front().v(),
                                                left_expanded_t);
        point_pairs.emplace_back(left_expanded_lower_point,
                                 left_expanded_upper_point);
        speed_points.push_back(left_expanded_speed_point);
    }

    for (int i = 0; i < lower_points_.size(); ++i) {
        point_pairs.emplace_back(lower_points_[i], upper_points_[i]);
    }
    for (int i = 0; i < speed_points_.size(); ++i) {
        speed_points.push_back(speed_points_[i]);
    }

    if (right > 0.0) {
        const double right_expanded_t = lower_points_.back().t() + right;
        const StPoint right_expanded_lower_point(lower_points_.back().s(),
                                                 right_expanded_t);
        const StPoint right_expanded_upper_point(upper_points_.back().s(),
                                                 right_expanded_t);
        const VtPoint right_expanded_speed_point(speed_points_.back().v(),
                                                 right_expanded_t);
        point_pairs.emplace_back(right_expanded_lower_point,
                                 right_expanded_upper_point);
        speed_points.push_back(right_expanded_speed_point);
    }

    set_speed_points(std::move(speed_points));
    Init(std::move(point_pairs));
}

StBoundarySourceTypeProto::Type StBoundary::ObjectTypeToSourceType(
    StBoundaryProto::ObjectType object_type) {
    switch (object_type) {
        case StBoundaryProto::UNKNOWN_OBJECT:
            return StBoundarySourceTypeProto::UNKNOWN;
        case StBoundaryProto::VEHICLE:
        case StBoundaryProto::CYCLIST:
        case StBoundaryProto::PEDESTRIAN:
        case StBoundaryProto::STATIC:
        case StBoundaryProto::IGNORABLE:
            return StBoundarySourceTypeProto::ST_OBJECT;
        case StBoundaryProto::VIRTUAL:
            return StBoundarySourceTypeProto::VIRTUAL;
        case StBoundaryProto::IMPASSABLE_BOUNDARY:
            return StBoundarySourceTypeProto::IMPASSABLE_BOUNDARY;
        case StBoundaryProto::PATH_BOUNDARY:
            return StBoundarySourceTypeProto::PATH_BOUNDARY;
        default:
            throw std::runtime_error("switch case on enum unexpected");
    }
}

std::string StBoundary::SourceTypeName(
    StBoundarySourceTypeProto::Type source_type) {
    switch (source_type) {
        case StBoundarySourceTypeProto::IMPASSABLE_BOUNDARY:
            return "IMPASSABLE_BOUNDARY";
        case StBoundarySourceTypeProto::ST_OBJECT:
            return "ST_OBJECT";
        case StBoundarySourceTypeProto::UNKNOWN:
            return "UNKNOWN";
        case StBoundarySourceTypeProto::VIRTUAL:
            return "VIRTUAL";
        case StBoundarySourceTypeProto::PATH_BOUNDARY:
            return "PATH_BOUNDARY";
        default:
            throw std::runtime_error("switch case on enum unexpected");
    }
}

boost::optional<std::pair<double, double>> StBoundary::GetBoundarySRange(
    double curr_time) const {
    if (curr_time < min_t_ || curr_time > max_t_) {
        return boost::none;
    }

    int left = 0;
    int right = 0;
    if (!GetLowerPointsIndexRange(curr_time, &left, &right)) {
        // AD_LWARN(PP) << "Fail to get index range.";
        return boost::none;
    }
    XCHECK_NE(left, right);

    const double alpha = (curr_time - upper_points_[left].t()) /
                         (upper_points_[right].t() - upper_points_[left].t());

    return std::make_pair(
        upper_points_[left].s() +
            alpha * (upper_points_[right].s() - upper_points_[left].s()),
        lower_points_[left].s() +
            alpha * (lower_points_[right].s() - lower_points_[left].s()));
}

boost::optional<double> StBoundary::GetStBoundarySpeedAtT(double t) const {
    if ((t < min_t_) || (t > max_t_)) return boost::none;

    int left = 0;
    int right = 0;
    if (!GetSpeedPointsIndexRange(t, &left, &right)) {
        // AD_LWARN(PP) << "Fail to get index range.";
        return boost::none;
    }
    XCHECK_NE(left, right);

    const double alpha =
        LerpFactor(speed_points_[left].t(), speed_points_[right].t(), t);

    return Lerp(speed_points_[left].v(), speed_points_[right].v(), alpha);
}

StBoundaryRef StBoundary::CreateInstance(
    const StBoundaryPoints &st_boundary_points,
    StBoundaryProto::ObjectType object_type,
    std::string id,
    double probability,
    bool is_stationary,
    StBoundaryProto::ProtectionType protection_type,
    bool is_large_vehicle,
    bool is_traffic_light,
    SecondOrderTrajectoryPoint pose,
    ObjectSlInfo obj_sl_info,
    ObjectScenarioInfo obj_scenario_info) {
    XCHECK_EQ(st_boundary_points.lower_points.size(),
              st_boundary_points.upper_points.size());
    XCHECK_GE(st_boundary_points.lower_points.size(), 2);
    std::vector<std::pair<StPoint, StPoint>> point_pairs;
    point_pairs.reserve(st_boundary_points.lower_points.size());
    for (int i = 0; i < st_boundary_points.lower_points.size(); ++i) {
        point_pairs.emplace_back(st_boundary_points.lower_points[i],
                                 st_boundary_points.upper_points[i]);
    }
    return StBoundaryRef(new StBoundary(
        std::move(point_pairs), st_boundary_points.speed_points,
        st_boundary_points.overlap_infos, st_boundary_points.nearest_sl_points,
        object_type, std::move(id), probability, is_stationary, protection_type,
        is_large_vehicle, is_traffic_light, boost::none, boost::none,
        obj_sl_info, obj_scenario_info, pose));
}

StBoundaryRef StBoundary::CopyInstance(const StBoundary &st_boundary) {
    const auto &lower_points = st_boundary.lower_points();
    const auto &upper_points = st_boundary.upper_points();

    std::vector<std::pair<StPoint, StPoint>> point_pairs;
    point_pairs.reserve(lower_points.size());
    for (int i = 0; i < lower_points.size(); ++i) {
        point_pairs.emplace_back(lower_points[i], upper_points[i]);
    }

    return StBoundaryRef(new StBoundary(
        std::move(point_pairs), st_boundary.speed_points(),
        st_boundary.overlap_infos(), st_boundary.nearest_sl_points(),
        st_boundary.object_type(), st_boundary.id(), st_boundary.probability(),
        st_boundary.is_stationary(), st_boundary.protection_type(),
        st_boundary.is_large_vehicle(), st_boundary.is_traffic_light(),
        st_boundary.overlap_meta(), st_boundary.protected_st_boundary_id(),
        st_boundary.obj_sl_info(), st_boundary.obj_scenario_info(),
        st_boundary.obj_pose_info()));
}

std::string StBoundary::DebugString() const {
    if (IsEmpty()) {
        return "St boundary is empty.";
    }
    std::string ret = absl::StrFormat(
        "St boundary ( id : %s, min_s : %f, max_s : %f, min_t : %f, max_t : "
        "%f "
        ")\n",
        id_, min_s(), max_s(), min_t(), max_t());
    ret = absl::StrCat(ret, "upper_points: ");
    for (const auto &up : upper_points_) {
        ret = absl::StrCat(ret, up.DebugString(), ", ");
    }
    ret = absl::StrCat(ret, "\nlower_points: ");
    for (const auto &lp : lower_points_) {
        ret = absl::StrCat(ret, lp.DebugString(), ", ");
    }
    return ret;
}

void StBoundary::set_id(const std::string &id) {
    id_ = id;
    traj_id_ = RecoverTrajId(id, source_type_);
    object_id_ = RecoverObjectId(id, source_type_);
}

boost::optional<std::string> StBoundary::RecoverObjectId(
    const std::string &st_boundary_id,
    StBoundarySourceTypeProto::Type source_type) {
    if (source_type != StBoundarySourceTypeProto::ST_OBJECT) {
        return boost::none;
    }
    auto found = st_boundary_id.find("-idx");
    if (found == std::string::npos) {
        // LOG(ERROR) << "St_boundary_id of st_object [" << st_boundary_id
        //            << "] should contain \"-idx\" but not!";
        return boost::none;
    } else {
        return st_boundary_id.substr(0, found);
    }
}

boost::optional<std::string> StBoundary::RecoverTrajId(
    const std::string &st_boundary_id,
    StBoundarySourceTypeProto::Type source_type) {
    if (source_type != StBoundarySourceTypeProto::ST_OBJECT) {
        return boost::none;
    }
    const auto it = st_boundary_id.find('|');
    if (it == std::string::npos) {
        return st_boundary_id;
    }
    return st_boundary_id.substr(0, it);
}

bool StBoundary::GetLowerPointsIndexRange(double t,
                                          int *left,
                                          int *right) const {
    return QueryIndexRange(lower_points_, t, left, right);
}

bool StBoundary::GetUpperPointsIndexRange(double t,
                                          int *left,
                                          int *right) const {
    return QueryIndexRange(upper_points_, t, left, right);
}
bool StBoundary::GetSpeedPointsIndexRange(double t,
                                          int *left,
                                          int *right) const {
    return QueryIndexRange(speed_points_, t, left, right);
}

StBoundaryProto::ObjectType ToStBoundaryObjectType(ObjectType type) {
    switch (type) {
        case ObjectType::OT_VEHICLE:
        case ObjectType::OT_LARGE_VEHICLE:
        case ObjectType::OT_UNKNOWN_MOVABLE:
            return StBoundaryProto::VEHICLE;
        case ObjectType::OT_MOTORCYCLIST:
        case ObjectType::OT_CYCLIST:
        case ObjectType::OT_TRICYCLIST:
            return StBoundaryProto::CYCLIST;
        case ObjectType::OT_PEDESTRIAN:
            return StBoundaryProto::PEDESTRIAN;
        case ObjectType::OT_UNKNOWN_STATIC:
        case ObjectType::OT_BARRIER:
        case ObjectType::OT_CONE:
        case ObjectType::OT_WARNING_TRIANGLE:
            return StBoundaryProto::STATIC;
        case ObjectType::OT_FOD:
        case ObjectType::OT_VEGETATION:
            return StBoundaryProto::IGNORABLE;
        default:
            throw std::runtime_error("switch case on enum unexpected");
    }
}

std::string GetStBoundaryIntegrationId(const StBoundary &st_boundary) {
    if (st_boundary.source_type() == StBoundarySourceTypeProto::ST_OBJECT) {
        const auto &object_id = st_boundary.object_id();
        XCHECK(object_id.has_value());
        return st_boundary.is_protective()
                   ? *object_id + "|" +
                         StBoundaryProto::ProtectionType_Name(
                             st_boundary.protection_type())
                   : *object_id;
    }
    return st_boundary.id();
}

bool StBoundary::IsEmpty() const { return lower_points_.empty(); }

bool StBoundary::IsPointInBoundary(const StPoint &st_point) const;

StPoint StBoundary::upper_left_point() const {
    XCHECK(!upper_points_.empty());
    return upper_points_.front();
}

StPoint StBoundary::upper_right_point() const {
    XCHECK(!upper_points_.empty());
    return upper_points_.back();
}

StPoint StBoundary::bottom_left_point() const {
    XCHECK(!lower_points_.empty());
    return lower_points_.front();
}

StPoint StBoundary::bottom_right_point() const {
    XCHECK(!lower_points_.empty());
    return lower_points_.back();
}

void StBoundary::ExpandByT(double left, double right);

StBoundarySourceTypeProto::Type StBoundary::source_type() const {
    return source_type_;
}
void StBoundary::set_source_type(StBoundarySourceTypeProto::Type source_type) {
    source_type_ = source_type;
}
std::string StBoundary::SourceTypeName(
    StBoundarySourceTypeProto::Type source_type);

StBoundarySourceTypeProto::Type StBoundary::ObjectTypeToSourceType(
    StBoundaryProto::ObjectType object_type);

StBoundaryProto::ObjectType StBoundary::object_type() const {
    return object_type_;
}

void StBoundary::set_object_type(StBoundaryProto::ObjectType type) {
    XCHECK(type != StBoundaryProto::UNKNOWN_OBJECT);

    object_type_ = type;
    set_source_type(ObjectTypeToSourceType(type));
}

const std::string &StBoundary::id() const { return id_; }
void StBoundary::set_id(const std::string &id);
const boost::optional<std::string> &StBoundary::traj_id() const {
    return traj_id_;
}
const boost::optional<std::string> &StBoundary::object_id() const {
    return object_id_;
}

double StBoundary::probability() const { return probability_; }
void StBoundary::set_probability(double probability) {
    XCHECK_GE(probability, 0.0);
    XCHECK_LE(probability, 1.0);
    probability_ = probability;
}

bool StBoundary::is_stationary() const { return is_stationary_; }
void StBoundary::set_is_stationary(bool is_stationary) {
    is_stationary_ = is_stationary;
}

bool StBoundary::is_protective() const {
    return protection_type_ != StBoundaryProto::NON_PROTECTIVE;
}

StBoundaryProto::ProtectionType StBoundary::protection_type() const {
    return protection_type_;
}
void StBoundary::set_protection_type(
    StBoundaryProto::ProtectionType protection_type) {
    protection_type_ = protection_type;
}

boost::optional<std::string> StBoundary::protected_st_boundary_id() const {
    return protected_st_boundary_id_;
}
void StBoundary::set_protected_st_boundary_id(
    std::string protected_st_boundary_id) {
    protected_st_boundary_id_ = std::move(protected_st_boundary_id);
}

bool StBoundary::is_large_vehicle() const { return is_large_vehicle_; }
bool StBoundary::is_traffic_light() const { return is_traffic_light_; }
void StBoundary::set_is_large_vehicle_vehicle(bool is_large_vehicle) {
    is_large_vehicle_ = is_large_vehicle;
}

void StBoundary::set_obj_sl_info(ObjectSlInfo obj_sl_info) {
    obj_sl_info_ = obj_sl_info;
}

void StBoundary::set_obj_scenario_info(ObjectScenarioInfo obj_scenario_info) {
    obj_scenario_info_ = obj_scenario_info;
}

boost::optional<double> StBoundary::GetStBoundarySpeedAtT(double t) const;

bool StBoundary::GetLowerPointsIndexRange(double t,
                                          int *left,
                                          int *right) const;

bool StBoundary::GetUpperPointsIndexRange(double t,
                                          int *left,
                                          int *right) const;

bool StBoundary::GetSpeedPointsIndexRange(double t,
                                          int *left,
                                          int *right) const;

double StBoundary::min_s() const { return min_s_; }
double StBoundary::min_t() const { return min_t_; }
double StBoundary::max_s() const { return max_s_; }
double StBoundary::max_t() const { return max_t_; }

ObjectSlInfo StBoundary::obj_sl_info() const { return obj_sl_info_; }

ObjectScenarioInfo StBoundary::obj_scenario_info() const {
    return obj_scenario_info_;
}
ObjectScenarioInfo &StBoundary::mutable_obj_scenario_info() {
    return obj_scenario_info_;
}
SecondOrderTrajectoryPoint StBoundary::obj_pose_info() const { return pose_; }

const std::vector<StPoint> &StBoundary::upper_points() const {
    return upper_points_;
}
const std::vector<StPoint> &StBoundary::lower_points() const {
    return lower_points_;
}
const std::vector<VtPoint> &StBoundary::speed_points() const {
    return speed_points_;
}
const std::vector<OverlapInfo> &StBoundary::overlap_infos() const {
    return overlap_infos_;
}
const std::vector<NearestSlPoint> &StBoundary::nearest_sl_points() const {
    return nearest_sl_points_;
}

void StBoundary::set_speed_points(std::vector<VtPoint> speed_points) {
    speed_points_ = std::move(speed_points);
}

const boost::optional<StOverlapMetaProto> &StBoundary::overlap_meta() const {
    return overlap_meta_;
}
void StBoundary::set_overlap_meta(StOverlapMetaProto meta) {
    overlap_meta_ = std::move(meta);
}

template <typename T>
bool StBoundary::QueryIndexRange(const std::vector<T> &points,
                                 double t,
                                 int *left,
                                 int *right) const {
    if (!XCHECK_NOTNULL(left) || !XCHECK_NOTNULL(right) ||
        !XCHECK_GT(points.size(), 1)) {
        return false;
    }
    if ((t < points.front().t()) || (t > points.back().t())) {
        // AD_LWARN(PP) << "t is out of range. t = " << t
        //              << " range: " << points.front().t() << ", "
        //              << points.back().t();
        return false;
    }
    const auto it =
        std::lower_bound(points.begin(), points.end(), t,
                         [](const T &p, double t) { return p.t() < t; });
    const int index = std::distance(points.begin(), it);
    if (index == 0) {
        *left = 0;
        *right = *left + 1;
    } else if (it == points.end()) {
        *left = points.size() - 1;
        *right = *left - 1;
    } else {
        *left = index - 1;
        *right = index;
    }
    return true;
}

}  // namespace planning
}  // namespace pnc_x
