
#include "maps/lane_sequence.h"
#include "math/math_utils.h"
#include "util/loop_guard.h"

#include <cctype>
#include <cstdint>
namespace ads_x {
namespace planning {
LaneSequence::LaneSequence(const std::vector<LaneConstPtr> &lanes_ptr_vec) {
    for (const auto &lane : lanes_ptr_vec) {
        if (!lane) break;
        if (lanes_.empty() || (lane->id() != lanes_.back()->id())) {
            lanes_.emplace_back(lane);
        }
    }
}

const std::vector<LaneConstPtr> &LaneSequence::lanes() const { return lanes_; }
std::vector<LaneConstPtr> &LaneSequence::mutable_lanes() { return lanes_; }

LaneConstPtr LaneSequence::front_lane() const {
    if (!lanes_.empty()) {
        return lanes_.front();
    }
    return nullptr;
}

bool LaneSequence::IsValid() {
    if (!lanes_.empty() && lanes_.front()) {
        return lanes_.front()->center_line().IsValid();
    }
    return false;
}

bool LaneSequence::SamplePoints(double start_s,
                                std::vector<Point2d> *const points,
                                double interval) const {
    double lane_start_s = start_s;
    for (const auto &lane : lanes_) {
        if (!lane->center_line().IsValid()) break;
        std::vector<ads_x::planning::math::Vec2d> sample_points;
        bool flag = lane->center_line().SamplePoints(
            lane_start_s, lane->center_line().length(), &sample_points,
            interval);
        if (flag) {
            lane_start_s = lane_start_s +
                           ((double)sample_points.size() * interval) -
                           lane->center_line().length();
            points->insert(points->end(), sample_points.begin(),
                           sample_points.end());
        }
    }
    return true;
}

bool LaneSequence::AddLane(const LaneConstPtr &lane) {
    if (!lane) {
        return false;
    }
    if (lanes_.empty()) {
        lanes_.emplace_back(lane);
        return true;
    } else if ((!lane->center_line().IsValid() ||
                !lanes_.back()->center_line().IsValid()) &&
               lanes_.back()->IsNext(lane->id())) {
        lanes_.emplace_back(lane);
        return true;
    } else if ((std::fabs(lanes_.back()->center_line().end_point().x() -
                         lane->center_line().begin_point().x()) < 0.1) &&
               (std::fabs(lanes_.back()->center_line().end_point().y() -
                         lane->center_line().begin_point().y()) < 0.1)) {
        lanes_.emplace_back(lane);
        return true;
    }
    return false;
}

double LaneSequence::GetTrueLength() const {
    double len = 0;
    for (auto &lane : lanes_) {
        len += lane->topo_length();
    }
    return len;
}

double LaneSequence::GetPointsLength() const {
    double len = 0;
    for (auto &lane : lanes_) {
        len += lane->curve_length();
    }
    return len;
}

math::Vec2d LaneSequence::GetPointAtS(double s) const {
    math::Vec2d point_s;
    double accumulate_s = 0.0;
    for (const auto &lane : lanes_) {
        if (!lane->center_line().IsValid()) break;
        if (((accumulate_s + lane->center_line().length()) > s) ||
            lane == lanes_.back()) {
            point_s = lane->center_line().GetPointAtS(s - accumulate_s);
            break;
        }
        accumulate_s += lane->center_line().length();
    }
    return point_s;
}

double LaneSequence::GetWidthAtS(double s) const {
    math::Vec2d point = GetPointAtS(s);
    LaneConstPtr nearest_lane = GetNearestLane(point, nullptr);
    const double &width = nearest_lane->GetWidthAtPoint(point.x(), point.y());
    return width;
};

math::Vec2d LaneSequence::GetTangentAtS(double s) const {
    math::Vec2d point = GetPointAtS(s);
    LaneConstPtr nearest_lane = GetNearestLane(point, nullptr);
    SLPoint sl_point;
    nearest_lane->GetSLWithoutLimit(point, &sl_point);
    const double query_fraction =
        std::max(0.0, sl_point.s / nearest_lane->curve_length());
    return nearest_lane->GetTangent(query_fraction);
}

double LaneSequence::GetProjectionDistance(const double &x,
                                           const double &y) const {
    return GetProjectionDistance(math::Vec2d(x, y), nullptr);
}

double LaneSequence::GetProjectionDistance(const math::Vec2d &point) const {
    return GetProjectionDistance(point, nullptr);
}

double LaneSequence::GetProjectionDistance(const math::Vec2d &point,
                                           double *s_offset,
                                           double *l_offset) const {
    double project_l = std::numeric_limits<double>::max();
    const auto nearest_lane = GetNearestLane(point, nullptr);
    if (!nearest_lane) {
        return project_l;
    }
    double project_s = std::numeric_limits<double>::max();
    nearest_lane->center_line().GetProjection(point, &project_s, &project_l);
    for (const auto &lane : lanes_) {
        if (lane && lane == nearest_lane) break;
        project_s += lane->center_line().length();
    }
    if (s_offset) {
        *s_offset = project_s;
    }
    if (l_offset) {
        *l_offset = project_l;
    }
    return std::fabs(project_l);
}
bool IsNumeric(const std::string &str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

double LaneSequence::GetDistanceToPOI(
    const PoiType &poi_type,
    const double &x,
    const double &y,
    LaneConstPtr &poi_lane,
    const ads_x::planning::NaviPosition *navi_start) {
    double dist_to_poi = std::numeric_limits<double>::max();
    int start_idx = -1;
    double project_dis;
    LaneConstPtr start_lane =
        GetNearestLane(ads_x::planning::math::Vec2d(x, y), &project_dis);
    if ((project_dis > (3.5 * Constants::MIN_HALF_LANE_WIDTH)) || !start_lane) {
        return dist_to_poi;
    }
    for (const auto &lane : lanes_) {
        start_idx++;
        if (lane && (lane->id() == start_lane->id())) {
            start_lane = lane;
            break;
        }
    }

    if (!start_lane) {
        return dist_to_poi;
    }

    double s = 0.0;
    double l = 0.0;
    start_lane->center_line().GetProjection({x, y}, &s, &l);

    double lane_seq_length = GetTrueLength();
    if (poi_type == PoiType::Poi_To_Long_Solid_Left) {
        double curr_dist = 0.0;
        double check_dist = 0.0;
        bool find_solid = false;
        bool find_solid_end = false;
        double solid_start_dis = std::numeric_limits<double>::max();
        double solid_end_dis = std::numeric_limits<double>::max();
        left_solid_length_ = std::numeric_limits<double>::max();
        if (!navi_start || !navi_start->section_id) {
            return solid_start_dis;
        }
        for (const auto &lane : lanes_) {
            if (!lane) {
                return std::numeric_limits<double>::max();
            }
            if (lane->can_pass_left_lane_boundaries()) {
                if (find_solid) {
                    check_dist += lane->topo_length();
                    if (check_dist > 150.0) {
                        left_solid_length_ = solid_end_dis - solid_start_dis;
                        find_solid_end = true;
                        break;
                    }
                }
            } else {
                if (!find_solid) {
                    find_solid = true;
                    solid_start_dis = curr_dist;
                } else {
                    check_dist = 0.0;
                }
                solid_end_dis = curr_dist + lane->topo_length();
            }
            curr_dist += lane->topo_length();
        }
        return solid_start_dis;
    }

    if (poi_type == PoiType::Poi_To_Long_Solid_Right) {
        double curr_dist = 0.0;
        bool find_solid = false;
        bool find_solid_end = false;
        double check_dist = 0;
        double solid_start_dis = std::numeric_limits<double>::max();
        double solid_end_dis = std::numeric_limits<double>::max();
        right_solid_length_ = std::numeric_limits<double>::max();
        if (!navi_start || !navi_start->section_id) {
            return solid_start_dis;
        }
        for (const auto &lane : lanes_) {
            if (!lane) {
                return std::numeric_limits<double>::max();
            }
            if (lane->can_pass_right_lane_boundaries()) {
                if (find_solid) {
                    check_dist += lane->topo_length();
                    if (check_dist > 150.0) {
                        right_solid_length_ = solid_end_dis - solid_start_dis;
                        find_solid_end = true;
                        break;
                    }
                }
            } else {
                if (!find_solid) {
                    find_solid = true;
                    solid_start_dis = curr_dist;
                } else {
                    check_dist = 0.0;
                }
                solid_end_dis = curr_dist + lane->topo_length();
            }
            curr_dist += lane->topo_length();
        }
        return solid_start_dis;
    }

    if (poi_type == PoiType::Poi_NaviEnd) {
        if (!navi_start || !navi_start->section_id) {
            return dist_to_poi;
        }
        dist_to_poi = 0.0;
        bool find_navi_start = false;
        bool find_navigation = false;
        for (const auto &lane : lanes_) {
            if (find_navigation && !lane->is_navigation()) {
                break;
            }
            if (lane->is_navigation()) {
                find_navigation = true;
                poi_lane = lane;
                dist_to_poi += lane->topo_length();
            }
            if (lane->section_id() == navi_start->section_id) {
                find_navi_start = true;
                dist_to_poi = lane->topo_length();
            }
        }
        if (!find_navigation) {
            return std::numeric_limits<double>::max();
        }
        if (find_navi_start) {
            dist_to_poi -= navi_start->s_offset;
        }
        return dist_to_poi;
    }

    if (poi_type == PoiType::Poi_Split) {
        if (lanes_[start_idx]->split_topology() != TOPOLOGY_SPLIT_NONE) {
            poi_lane = lanes_[start_idx];
            return 0.0;
        }
        dist_to_poi = start_lane->center_line().length() - s;
        ++start_idx;
        auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((start_idx < static_cast<int>(lanes_.size())) &&
               (lanes_[start_idx]->split_topology() == TOPOLOGY_SPLIT_NONE) &&
               loop_guard) {
            dist_to_poi += lanes_[start_idx]->topo_length();
            ++start_idx;
        }
        if (start_idx == static_cast<int>(lanes_.size())) {
            dist_to_poi = std::numeric_limits<double>::max();
            poi_lane = nullptr;
        } else {
            poi_lane = lanes_[start_idx];
        }
        return dist_to_poi;
    }

    if (poi_type == PoiType::Poi_Merge) {
        dist_to_poi = start_lane->center_line().length() - s;
        if ((lanes_[start_idx]->merge_topology() == TOPOLOGY_MERGE_LEFT) ||
            (lanes_[start_idx]->merge_topology() == TOPOLOGY_MERGE_RIGHT) ||
            (lanes_[start_idx]->merge_topology() == TOPOLOGY_MERGE_UNKNOWN)) {
            poi_lane = lanes_[start_idx];
            return dist_to_poi;
        }
        ++start_idx;
        auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((start_idx < static_cast<int>(lanes_.size())) &&
               (lanes_[start_idx]->merge_topology() != TOPOLOGY_MERGE_LEFT) &&
               (lanes_[start_idx]->merge_topology() != TOPOLOGY_MERGE_RIGHT) &&
               (lanes_[start_idx]->merge_topology() != TOPOLOGY_MERGE_UNKNOWN) &&
               loop_guard) {
            dist_to_poi += lanes_[start_idx]->topo_length();
            ++start_idx;
        }
        if (start_idx == static_cast<int>(lanes_.size())) {
            dist_to_poi = std::numeric_limits<double>::max();
            poi_lane = nullptr;
        } else {
            dist_to_poi += lanes_[start_idx]->topo_length();
            poi_lane = lanes_[start_idx];
        }
        return dist_to_poi;
    }

    if (poi_type == PoiType::Poi_To_Be_Merged) {
        dist_to_poi = start_lane->center_line().length() - s;
        if (lanes_[start_idx]->merge_topology() == TOPOLOGY_TO_BE_MERGED) {
            poi_lane = lanes_[start_idx];
            return dist_to_poi;
        }
        ++start_idx;
        auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((start_idx < static_cast<int>(lanes_.size())) &&
               (lanes_[start_idx]->merge_topology() != TOPOLOGY_TO_BE_MERGED) &&
               loop_guard) {
            dist_to_poi += lanes_[start_idx]->topo_length();
            ++start_idx;
        }
        if (start_idx == static_cast<int>(lanes_.size())) {
            dist_to_poi = std::numeric_limits<double>::max();
            poi_lane = nullptr;
        } else {
            dist_to_poi += lanes_[start_idx]->topo_length();
            poi_lane = lanes_[start_idx];
        }
        return dist_to_poi;
    }

    if (poi_type == PoiType::Poi_To_Avoidance) {
        dist_to_poi = start_lane->center_line().length() - s;
        if (lanes_[start_idx]->IsAvoidanceLane()) {
            poi_lane = lanes_[start_idx];
            return dist_to_poi;
        }
        ++start_idx;
        auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((start_idx < static_cast<int>(lanes_.size())) &&
               !lanes_[start_idx]->IsAvoidanceLane() && loop_guard) {
            dist_to_poi += lanes_[start_idx]->topo_length();
            ++start_idx;
        }
        if (start_idx == static_cast<int>(lanes_.size())) {
            dist_to_poi = std::numeric_limits<double>::max();
            poi_lane = nullptr;
        } else {
            dist_to_poi += lanes_[start_idx]->topo_length();
            poi_lane = lanes_[start_idx];
        }
        return dist_to_poi;
    }
    auto IsHighway = [](LaneConstPtr lane_ptr) {
        return lane_ptr->is_highway() &&
               lane_ptr->type() == LaneType::LANE_NORMAL;
    };
    auto IsRamp = [](LaneConstPtr lane_ptr) {
        return lane_ptr->type() == LaneType::LANE_RAMP ||
               lane_ptr->type() == LaneType::LANE_ACC ||
               lane_ptr->type() == LaneType::LANE_DEC;
    };

    if (poi_type == PoiType::Poi_Enter_Mainboard) {
        dist_to_poi = start_lane->center_line().length() - s;
        if (IsHighway(lanes_[start_idx]) || !IsRamp(lanes_[start_idx])) {
            poi_lane = lanes_[start_idx];
            return std::numeric_limits<double>::max();
        }
        ++start_idx;
        while ((start_idx < static_cast<int>(lanes_.size())) &&
               !IsHighway(lanes_[start_idx]) && IsRamp(lanes_[start_idx])) {
            dist_to_poi += lanes_[start_idx]->topo_length();
            ++start_idx;
        }
        if (start_idx == static_cast<int>(lanes_.size())) {
            dist_to_poi = std::numeric_limits<double>::max();
            poi_lane = nullptr;
        } else {
            poi_lane = lanes_[start_idx];
            if (!IsHighway(lanes_[start_idx])) {
                dist_to_poi = std::numeric_limits<double>::max();
            }
        }
        return dist_to_poi;
    }

    if (poi_type == PoiType::Poi_Exit_Mainboard) {
        dist_to_poi = start_lane->center_line().length() - s;
        if (!IsHighway(lanes_[start_idx])) {
            poi_lane = lanes_[start_idx];
            return std::numeric_limits<double>::max();
        }
        ++start_idx;
        while ((start_idx < static_cast<int>(lanes_.size())) &&
               IsHighway(lanes_[start_idx])) {
            dist_to_poi += lanes_[start_idx]->topo_length();
            ++start_idx;
        }
        if (start_idx == static_cast<int>(lanes_.size())) {
            dist_to_poi = std::numeric_limits<double>::max();
            poi_lane = nullptr;
        } else {
            poi_lane = lanes_[start_idx];
            if (!IsRamp(lanes_[start_idx])) {
                dist_to_poi = std::numeric_limits<double>::max();
            }
        }
        return dist_to_poi;
    }

    return dist_to_poi;
}

double LaneSequence::GetDistanceToPOI(const PoiType &poi_type,
                                      const double &x,
                                      const double &y) {
    LaneConstPtr poi_lane;
    return GetDistanceToPOI(poi_type, x, y, poi_lane, nullptr);
}

LaneConstPtr LaneSequence::GetNearestLane(const math::Vec2d &point,
                                          double *dis,
                                          bool use_ego_heading,
                                          double ego_heading) const {
    LaneConstPtr nearest_lane = nullptr;
    double min_dist = std::numeric_limits<double>::max();
    for (const auto &lane : lanes_) {
        if (!lane->center_line().IsValid()) continue;

        if (use_ego_heading) {
            double s_temp;
            int index_temp1, index_temp2;
            ads_x::planning::math::Vec2d nearestpoint;
            auto dis_temp =
                lane->center_line().GetDistance(point, &nearestpoint, &s_temp);
            const int points_size_minus2 =
                static_cast<int>(lane->center_line().points().size()) - 2;
            index_temp1 =
                std::min(lane->center_line().GetIndexByS(s_temp),
                         points_size_minus2);
            index_temp2 = lane->center_line().GetIndexByS(s_temp + 5.0);
            index_temp2 =
                (index_temp2 == index_temp1) ? (index_temp1 + 1) : index_temp2;

            double theta_temp = ads_x::planning::math::NormalizeAngle(
                (lane->center_line().points().at(index_temp2) -
                 lane->center_line().points().at(index_temp1))
                    .Angle());
            double heading_diff = fabs(ads_x::planning::math::NormalizeAngle(
                theta_temp - ego_heading));

            if (heading_diff >
                ((lane->turn_type() == U_TURN) ? (M_PI / 3.0) : (M_PI / 4.0))) {
                continue;
            }
        }

        double d = lane->center_line().GetDistance(point);
        if (d < min_dist) {
            min_dist = d;
            nearest_lane = lane;
        }
    }
    if (dis) {
        *dis = min_dist;
    }
    return nearest_lane;
}

void LaneSequence::GetBoundaryTypeFromS(
    const bool &is_left,
    const double &s,
    std::vector<LaneBoundaryType> &boundary_type) const {
    LaneConstPtr nearest_lane = nullptr;
    double accumulate_s = 0.0;
    for (const auto &lane : lanes_) {
        if (!lane) break;
        accumulate_s += lane->curve_length();
        if (accumulate_s > s) {
            nearest_lane = lane;
            break;
        }
    }
    if (!nearest_lane) return;
    auto pt = nearest_lane->center_line().GetPointAtS(
        s + nearest_lane->curve_length() - accumulate_s);
    GetBoundaryTypeFromPoint(is_left, pt, boundary_type);
}

void LaneSequence::GetBoundaryTypeFromPoint(
    const bool &is_left,
    const math::Vec2d &point,
    std::vector<LaneBoundaryType> &boundary_type) const {
    auto nearest_lane = GetNearestLane(point, nullptr);
    if (!nearest_lane) return;
    nearest_lane->forward_boundary_type(is_left, point, boundary_type);
    if (boundary_type.empty()) return;
    bool find_nearest = false;
    for (const auto &lane : lanes_) {
        if (!lane) break;
        const auto &boundary_ptr =
            is_left ? lane->left_boundary() : lane->right_boundary();
        if (!boundary_ptr) break;
        const double &start_s = boundary_type.back().s;
        if (find_nearest) {
            const auto &all_boundary_type = boundary_ptr->boundary_types();
            for (const auto &boundary : all_boundary_type) {
                boundary_type.emplace_back(
                    LaneBoundaryType{boundary.s + start_s, boundary.line_type,
                                     boundary.line_color});
            }
        }
        if (nearest_lane->id() == lane->id()) {
            find_nearest = true;
        }
    }
}

double LaneSequence::GetDistanceToJunction(
    LaneConstPtr &poi_lane,
    const ads_x::planning::NaviPosition &navi_start,
    bool end_check,
    bool special_check) const {
    double dist_to_junction = std::numeric_limits<double>::max();
    LaneConstPtr start_lane = nullptr;
    if (!navi_start.section_id) {
        poi_lane = nullptr;
        return dist_to_junction;
    }
    bool find_nearest = false;
    bool find_junction = false;
    for (int index = 0; index < static_cast<int>(lanes_.size()); index++) {
        if (lanes_[index] == nullptr) break;
        if (lanes_[index]->section_id() == navi_start.section_id) {
            dist_to_junction = 0.0;
            find_nearest = true;
        }
        if (lanes_[index]->junction_id() && find_nearest) {
            if (special_check) {
                dist_to_junction += lanes_[index]->topo_length();
                continue;
            }
            poi_lane = lanes_[index];
            find_junction = true;
            break;
        }
        if (find_nearest) {
            dist_to_junction += lanes_[index]->topo_length();
        }
    }
    if (end_check) {
        return std::max(dist_to_junction - navi_start.s_offset,
                        Constants::ZERO);
    }
    return find_junction ? std::max(dist_to_junction - navi_start.s_offset, 0.0)
                         : std::numeric_limits<double>::max();
}

double LaneSequence::GetDistanceBetweenJunction(
    const uint64_t begin_junction_id, LaneConstPtr &next_virtual_lane) const {
    double dist_to_junction = 0.0;
    LaneConstPtr begin_lane = nullptr;
    for (const auto &lane : lanes_) {
        if (lane && !begin_lane && (lane->junction_id() == begin_junction_id)) {
            begin_lane = lane;
        } else if (lane && (begin_lane) &&
                   lane->junction_id() != begin_junction_id &&
                   lane->junction_id()) {
            next_virtual_lane = lane;
            return dist_to_junction;
        } else if (lane && begin_lane && !lane->junction_id()) {
            dist_to_junction += lane->topo_length();
        }
    }
    return dist_to_junction;
}

double LaneSequence::GetDistanceToJunction(const double &x,
                                           const double &y,
                                           LaneConstPtr &poi_lane) const {
    double dist_to_junction = std::numeric_limits<double>::max();
    int start_idx = -1;
    double project_dis;
    LaneConstPtr start_lane =
        GetNearestLane(ads_x::planning::math::Vec2d(x, y), &project_dis);
    if ((project_dis > Constants::DEFAULT_LANE_WIDTH) || !start_lane) {
        return dist_to_junction;
    }
    for (const auto &lane : lanes_) {
        start_idx++;
        if (lane && (lane->id() == start_lane->id())) {
            break;
        }
    }

    if (lanes_[start_idx]->junction_id()) {
        poi_lane = lanes_[start_idx];
        return 0.0;
    }

    double s = 0.0;
    double l = 0.0;
    start_lane->center_line().GetProjection({x, y}, &s, &l);
    dist_to_junction = start_lane->center_line().length() - s;
    ++start_idx;
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while ((start_idx < static_cast<int>(lanes_.size())) &&
           (lanes_[start_idx]->junction_id() == 0) && loop_guard) {
        dist_to_junction += lanes_[start_idx]->topo_length();
        ++start_idx;
    }
    if (start_idx == static_cast<int>(lanes_.size())) {
        dist_to_junction = std::numeric_limits<double>::max();
        poi_lane = nullptr;
    } else {
        poi_lane = lanes_[start_idx];
    }
    return dist_to_junction;
}

double LaneSequence::GetDistanceExitJunction(
    const ads_x::planning::NaviPosition &navi_start) const {
    double dist_exit_junction = std::numeric_limits<double>::max();
    if (!navi_start.section_id) {
        return dist_exit_junction;
    }
    bool find_nearest = false;
    bool find_junction_start = false;
    bool find_junction_end = false;
    for (int index = 0; index < static_cast<int>(lanes_.size()); index++) {
        if (lanes_[index] == nullptr) break;
        if (find_junction_end) {
            break;
        }
        if (find_junction_start) {
            if ((lanes_[index]->type() != LANE_VIRTUAL_JUNCTION) &&
                (lanes_[index]->type() != LANE_LEFT_WAIT)) {
                find_junction_end = true;
                continue;
            }
        }
        if (lanes_[index]->section_id() == navi_start.section_id) {
            dist_exit_junction = 0.0;
            find_nearest = true;
        }
        if (lanes_[index]->junction_id() && find_nearest) {
            find_junction_start = true;
        }
        if (find_nearest) {
            dist_exit_junction += lanes_[index]->topo_length();
        }
    }
    return find_junction_end
               ? std::fmax(dist_exit_junction - navi_start.s_offset, 0.0)
               : std::numeric_limits<double>::max();
}

bool LaneSequence::CanPassJunction(
    const ads_x::planning::NaviPosition &navi_start,
    double *dist_to_junction,
    bool next_junction) {
    LaneConstPtr junction_lane = nullptr;
    double dist = GetDistanceToJunction(junction_lane, navi_start, true);
    if (dist_to_junction) {
        *dist_to_junction = dist;
    }
    bool navi_virtual_lane = true;
    if (next_junction && (junction_lane) &&
        junction_lane->section_id() == navi_start.section_id) {
        GetDistanceBetweenJunction(junction_lane->junction_id(), junction_lane);
    }
    if (junction_lane && !junction_lane->is_navigation()) {
        navi_virtual_lane = false;
    }
    if (!junction_lane && (dist < std::numeric_limits<double>::max())) {
        navi_virtual_lane = false;
    }
    return navi_virtual_lane;
}
bool LaneSequence::IsTurnLeft(const double &x, const double &y) {
    int start_idx = -1;
    double project_dis;
    LaneConstPtr start_lane =
        GetNearestLane(ads_x::planning::math::Vec2d(x, y), &project_dis);
    if ((project_dis > Constants::DEFAULT_LANE_WIDTH) || !start_lane) {
        return false;
    }
    for (const auto &lane : lanes_) {
        start_idx++;
        if (lane && (lane->id() == start_lane->id())) {
            break;
        }
    }
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while ((start_idx < static_cast<int>(lanes_.size())) &&
           !lanes_[start_idx]->junction_id() && loop_guard) {
        ++start_idx;
    }
    if ((start_idx == -1) || (start_idx >= static_cast<int>(lanes_.size()))) {
        return false;
    }
    return lanes_[start_idx]->turn_type() == LEFT_TURN;
}
bool LaneSequence::IsTurnRight(const double &x, const double &y) {
    int start_idx = -1;
    double project_dis;
    LaneConstPtr start_lane =
        GetNearestLane(ads_x::planning::math::Vec2d(x, y), &project_dis);
    if ((project_dis > Constants::DEFAULT_LANE_WIDTH) || !start_lane) {
        return false;
    }
    for (const auto &lane : lanes_) {
        start_idx++;
        if (lane && (lane->id() == start_lane->id())) {
            break;
        }
    }
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while ((start_idx < static_cast<int>(lanes_.size())) &&
           !lanes_[start_idx]->junction_id() && loop_guard) {
        ++start_idx;
    }
    if ((start_idx == -1) || (start_idx >= static_cast<int>(lanes_.size()))) {
        return false;
    }
    return lanes_[start_idx]->turn_type() == RIGHT_TURN;
}

bool LaneSequence::IsOnLaneSequence(const LaneConstPtr &lane) const {
    if (lanes_.empty() || !lane) {
        return false;
    }
    for (const auto &compare_lane : lanes_) {
        if (compare_lane && (compare_lane->id() == lane->id())) {
            return true;
        }
    }
    return false;
}

const LanePtr LaneSequence::GetPreLaneOnLaneSequence(
    const LaneConstPtr &lane) const {
    if ((lanes_.size() < 2) || !lane) {
        return nullptr;
    }
    for (int i = 0; i < lanes_.size(); i++) {
        if (lanes_[i] && (lanes_[i]->id() == lane->id())) {
            return std::const_pointer_cast<ads_x::planning::Lane>(
                (i > 0) ? lanes_[i - 1] : nullptr);
        }
    }
    return nullptr;
}

double LaneSequence::GetDistanceToTargetLaneType(
    LaneConstPtr &poi_lane,
    const std::unordered_set<LaneType> &lane_type_set,
    const ads_x::planning::NaviPosition &navi_start) const {
    double dist_to_lane = std::numeric_limits<double>::max();
    LaneConstPtr start_lane = nullptr;
    if (!navi_start.section_id) {
        poi_lane = nullptr;
        return dist_to_lane;
    }
    bool find_nearest = false;
    bool find_lane = false;
    for (int index = 0; index < lanes_.size(); index++) {
        if (lanes_[index] == nullptr) break;
        if (lanes_[index]->section_id() == navi_start.section_id) {
            dist_to_lane = 0.0;
            find_nearest = true;
        }
        if (!find_nearest) {
            continue;
        }
        if (lane_type_set.find(lanes_[index]->type()) != lane_type_set.end()) {
            poi_lane = lanes_[index];
            find_lane = true;
            break;
        }
        if (find_nearest) {
            dist_to_lane += lanes_[index]->topo_length();
        }
    }
    return find_lane ? std::max(dist_to_lane - navi_start.s_offset, 0.0)
                     : std::numeric_limits<double>::max();
}

double LaneSequence::GetDistanceToCustomSpeedLimit(
    const ads_x::planning::NaviPosition &navi_start,
    double *speed_limit) const {
    double dist_to_custom = DBL_MAX;
    if (!navi_start.section_id) {
        return dist_to_custom;
    }
    bool find_navi_start_lane = false;
    bool find_custom_lane = false;
    for (const auto &lane : lanes_) {
        if (!lane) continue;
        if (!lane->is_navigation() && find_navi_start_lane) break;
        if (!lane->is_navigation() && !find_navi_start_lane) continue;
        if (lane->section_id() == navi_start.section_id) {
            dist_to_custom = 0.0;
            find_navi_start_lane = true;
        }
        if (!find_navi_start_lane) continue;

        double custom_speed_limit = 0.0;
        if (lane->GetCustomSpeedLimit(&custom_speed_limit)) {
            find_custom_lane = true;
            *speed_limit = custom_speed_limit;
            break;
        }
        dist_to_custom += lane->topo_length();
    }
    if (!find_custom_lane) {
        dist_to_custom = DBL_MAX;
    } else {
        dist_to_custom -= navi_start.s_offset;
    }
    return dist_to_custom;
}

boost::optional<LaneConstPtr> LaneSequence::FindPreLaneOnLaneseq(Lane lane) {
    const auto &pre_lane_ids = lane.pre_lane_ids();
    if (pre_lane_ids.size() == 0) return boost::none;
    for (const auto &lane_id : pre_lane_ids) {
        for (const auto &lane : lanes_) {
            if (lane->id() == lane_id) {
                return lane;
            }
        }
    }
    return boost::none;
}

NavigableLaneSequence::NavigableLaneSequence(
    const std::vector<LaneConstPtr> &lanes_ptr_vec)
    : LaneSequence(lanes_ptr_vec) {
    navi_distance_ = 0.0F;
}

bool NavigableLaneSequence::IsOverLap(
    const std::vector<LaneConstPtr> &other_lane_sequence) {
    const std::vector<LaneConstPtr> &cur_lane_sequence = lanes();
    if (cur_lane_sequence.empty() || other_lane_sequence.empty()) {
        return false;
    }
    std::vector<uint64_t> cur_lane_sequence_ids;
    std::vector<uint64_t> other_lane_sequence_ids;
    for (const auto &lane : cur_lane_sequence) {
        cur_lane_sequence_ids.emplace_back(lane->id());
    }
    for (const auto &lane : other_lane_sequence) {
        other_lane_sequence_ids.emplace_back(lane->id());
    }
    auto iter1 = cur_lane_sequence_ids.begin();
    auto start_iter2 = std::find(other_lane_sequence_ids.begin(),
                                 other_lane_sequence_ids.end(), *iter1);
    if (start_iter2 == other_lane_sequence_ids.end()) {
        return false;
    }
    for (auto iter2 = start_iter2; iter1 != cur_lane_sequence_ids.end() &&
                                   iter2 != other_lane_sequence_ids.end();
         iter1++, iter2++) {
        if (*iter1 != *iter2) {
            return false;
        }
    }
    return true;
}

bool NavigableLaneSequence::IsTwoSplitLane(
    const std::vector<LaneConstPtr> &other_lane_sequence) {
    const std::vector<LaneConstPtr> &cur_lane_sequence = lanes();
    if (cur_lane_sequence.empty() || other_lane_sequence.empty()) {
        return false;
    }
    std::vector<uint64_t> cur_lane_sequence_ids;
    std::vector<uint64_t> other_lane_sequence_ids;
    for (const auto &lane : cur_lane_sequence) {
        cur_lane_sequence_ids.emplace_back(lane->id());
    }
    for (const auto &lane : other_lane_sequence) {
        other_lane_sequence_ids.emplace_back(lane->id());
    }
    auto iter1 = cur_lane_sequence_ids.begin();
    auto start_iter2 = std::find(other_lane_sequence_ids.begin(),
                                 other_lane_sequence_ids.end(), *iter1);
    if (start_iter2 == other_lane_sequence_ids.end()) {
        return false;
    }
    for (auto iter2 = start_iter2; iter1 != cur_lane_sequence_ids.end() &&
                                   iter2 != other_lane_sequence_ids.end();
         iter1++, iter2++) {
        if (*iter1 != *iter2) {
            return true;
        }
    }
    return false;
}

uint64_t NavigableLaneSequence::FindSamePrevLane(
    const std::vector<LaneConstPtr> &other_lane_sequence) {
    const std::vector<LaneConstPtr> &cur_lane_sequence = lanes();
    if (cur_lane_sequence.empty() || other_lane_sequence.empty()) {
        return 0UL;
    }
    if (cur_lane_sequence.at(0)->id() == other_lane_sequence.at(0)->id()) {
        return 0UL;
    }
    std::vector<uint64_t> cur_prevs = cur_lane_sequence.at(0)->pre_lane_ids();
    std::vector<uint64_t> other_prevs =
        other_lane_sequence.at(0)->pre_lane_ids();
    std::vector<uint64_t> common;
    std::sort(cur_prevs.begin(), cur_prevs.end());
    std::sort(other_prevs.begin(), other_prevs.end());
    std::set_intersection(cur_prevs.begin(), cur_prevs.end(),
                          other_prevs.begin(), other_prevs.end(),
                          std::back_inserter(common));

    if (!common.empty()) {
        return common.at(0);
    }
    return 0UL;
}

void LaneSequence::GetRoadSegments(
    const bool is_left, std::vector<math::LineSegment2d> *road_segs) const {
    road_segs->clear();
    for (const auto &lane : lanes_) {
        if (!lane) continue;
        const auto &road_boundary =
            is_left ? lane->left_road_boundary() : lane->right_road_boundary();
        if (!road_boundary) continue;
        for (const auto &road : road_boundary->road_boundaries()) {
            const auto &points = road->points();
            for (int i = 1; i < points.size(); i++) {
                road_segs->emplace_back(points[i - 1], points[i]);
            }
        }
    }
}

void NavigableLaneSequence::SetNaviDistance(const float navi_dis) {
    navi_distance_ = navi_dis;
}
void NavigableLaneSequence::SetNearestObstacleVel(
    const float nearest_obstacle_vel) {
    nearest_obstacle_vel_ = nearest_obstacle_vel;
}
void NavigableLaneSequence::SetNearestObstacleDistance(
    const float nearest_obstacle_distance) {
    nearest_obstacle_distance_ = nearest_obstacle_distance;
}
void NavigableLaneSequence::SetDistanceToEgoCar(
    const float distance_to_ego_car) {
    distance_to_ego_car_ = distance_to_ego_car;
};
void NavigableLaneSequence::SetSequenceIdx(const float sequence_idx) {
    sequence_idx_ = sequence_idx;
}
void NavigableLaneSequence::SetIsNaviSequence(const bool is_navi_sequence) {
    is_navi_sequence_ = is_navi_sequence;
}
void NavigableLaneSequence::SetProbability(const float probability) {
    probability_ = probability;
}
void NavigableLaneSequence::SetLcReason(const LcReason lc_reason) {
    lc_reason_ = lc_reason;
}
void NavigableLaneSequence::SetDebugContent(const std::string &debug_content) {
    debug_content_ += debug_content;
}
void NavigableLaneSequence::SetProjectionPoint(
    const Point2d &projection_point) {
    projection_point_ = projection_point;
}
void NavigableLaneSequence::SetIsOccupyLaneSeq(bool is_occupy_lane_seq) {
    is_occupy_lane_seq_ = is_occupy_lane_seq;
}
void NavigableLaneSequence::SetIsOptimalLaneSeq(bool is_optimal_lane_seq) {
    is_optimal_lane_seq_ = is_optimal_lane_seq;
}
void NavigableLaneSequence::SetCompleteSequences(
    std::vector<std::vector<LaneConstPtr>> &complete_sequences) {
    complete_sequences_ = complete_sequences;
}
void NavigableLaneSequence::SetNearestObstacle(
    const ObstacleForLane &obstacle) {
    nearest_obstacle_ = obstacle;
}
void NavigableLaneSequence::SetRightRoundaboutLanesNum(
    const std::int32_t right_roundabout_lanes_num) {
    right_roundabout_lanes_num_ = right_roundabout_lanes_num;
}
void NavigableLaneSequence::SetRightLanesNum(
    const std::int32_t right_lanes_num) {
    right_lanes_num_ = right_lanes_num;
}
void NavigableLaneSequence::SetScoreInStraightJunction(
    const float score_in_straight_junction) {
    score_in_straight_junction_ = score_in_straight_junction;
}
void NavigableLaneSequence::AddObstacleInSequence(
    const std::pair<std::string, double> &obstacle_in_sequence) {
    obstacles_in_sequence_.emplace_back(obstacle_in_sequence);
}
const float NavigableLaneSequence::GetNaviDistance() { return navi_distance_; }
const float NavigableLaneSequence::GetSequenceIdx() { return sequence_idx_; }
const float NavigableLaneSequence::GetNearestObstacleVel() {
    return nearest_obstacle_vel_;
}
const float NavigableLaneSequence::GetNearestObstacleDistance() {
    return nearest_obstacle_distance_;
}
const float NavigableLaneSequence::GetDistanceToEgoCar() const {
    return distance_to_ego_car_;
}
const float NavigableLaneSequence::GetProbability() const {
    return probability_;
}
const LcReason &NavigableLaneSequence::GetLcReason() const {
    return lc_reason_;
}
const bool NavigableLaneSequence::GetIsNaviSequence() {
    return is_navi_sequence_;
}
const bool NavigableLaneSequence::GetIsOccupyLaneSeq() {
    return is_occupy_lane_seq_;
}
const bool NavigableLaneSequence::GetIsOptimalLaneSeq() {
    return is_optimal_lane_seq_;
}
const std::int32_t NavigableLaneSequence::GetRightRoundaboutLanesNum() {
    return right_roundabout_lanes_num_;
}
const std::int32_t NavigableLaneSequence::GetRightLanesNum() {
    return right_lanes_num_;
}
const std::vector<std::pair<std::string, double>>
NavigableLaneSequence::GetObstaclesInSequence() {
    return obstacles_in_sequence_;
}
const std::string NavigableLaneSequence::GetDebugContent() {
    return debug_content_;
}
const Point2d NavigableLaneSequence::GetProjectionPoint() {
    return projection_point_;
}
const std::vector<std::vector<LaneConstPtr>>
NavigableLaneSequence::GetCompleteSequences() {
    return complete_sequences_;
}
const ObstacleForLane NavigableLaneSequence::GetNearestObstacle() {
    return nearest_obstacle_;
}
const float NavigableLaneSequence::GetScoreInStraightJunction() {
    return score_in_straight_junction_;
}

}  // namespace planning
}  // namespace ads_x