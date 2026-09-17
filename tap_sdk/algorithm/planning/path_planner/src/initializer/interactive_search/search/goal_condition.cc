
#include "initializer/interactive_search/search/goal_condition.h"
#include "initializer/motion_search_util.h"
#include "math/geometry/util.h"
#include "util/status_macros.h"

namespace pnc_x {
namespace planning {

void UpdateGoalSByLeadObs(const ObstacleDecisionGroup &decision_group,
                          const InitializerConfig &initializer_params,
                          const VehicleParamsProto *vehicle_params,
                          const Node &start,
                          double &goal_s) {
    bool has_lead = decision_group.obs_goal_gap.lead_obj_id.has_value();
    if (!has_lead) {
        return;
    }

    auto it = decision_group.obstacles_decision.find(
        std::string(decision_group.obs_goal_gap.lead_obj_id.value()));
    if (it == decision_group.obstacles_decision.end()) {
        return;
    }

    const auto &lead_obs = it->second;
    const double &goal_time =
        initializer_params.interactive_astar_search_config().goal_time();
    const double &ego_length =
        vehicle_params->vehicle_geometry_params().length();
    const double &front_edge_to_center =
        vehicle_params->vehicle_geometry_params().front_edge_to_center();
    const double s_buffer = ego_length + front_edge_to_center;

    if (lead_obs.modified_pred_traj.empty()) {
        return;
    }

    double lead_end_s = lead_obs.modified_pred_traj.back().sl_boundary.s_min;
    double lead_end_t = lead_obs.modified_pred_traj.back().traj_point.t();

    if (lead_end_t > goal_time) {
        size_t index = goal_time / decision_group.traj_time_step;
        index = std::min(index, lead_obs.modified_pred_traj.size() - 1);
        lead_end_s = lead_obs.modified_pred_traj[index].sl_boundary.s_min;
    } else if (lead_end_t < goal_time) {
        double remaining_time = goal_time - lead_end_t;
        double lead_end_v = lead_obs.modified_pred_traj.back().traj_point.v();
        const double &time_resolution =
            initializer_params.interactive_astar_search_config()
                .time_resolution();
        while (remaining_time > 0) {
            remaining_time -= time_resolution;
            lead_end_s += lead_end_v * time_resolution;
        }
    }

    goal_s = std::max(lead_end_s - s_buffer, 0.0);
    goal_s = std::min(goal_s, start.V() * goal_time);
}

std::vector<std::pair<double, double>> SortAndMerge(
    const std::vector<std::pair<double, double>> &ori_intervals) {
    std::vector<std::pair<double, double>> sorted_merged;
    std::vector<std::pair<double, double>> intervals = ori_intervals;
    if (intervals.empty()) {
        return sorted_merged;
    }

    std::sort(intervals.begin(), intervals.end(),
              [](const auto &a, const auto &b) { return a.first < b.first; });

    sorted_merged.push_back(intervals[0]);
    for (size_t i = 1; i < intervals.size(); ++i) {
        auto &last_gap = sorted_merged.back();
        if (intervals[i].first <= last_gap.second) {
            last_gap.second = std::max(last_gap.second, intervals[i].second);
        } else {
            sorted_merged.push_back(intervals[i]);
        }
    }

    return sorted_merged;
}

std::vector<std::pair<double, double>> FindComplement(
    const VehicleParamsProto *vehicle_params,
    const std::pair<double, double> &universe,
    const std::vector<std::pair<double, double>> &intervals) {
    std::vector<std::pair<double, double>> result;
    double current = universe.first;

    for (const auto &interval : intervals) {
        if (interval.second < universe.first ||
            interval.first > universe.second) {
            continue;
        }

        double left = std::max(interval.first, universe.first);
        double right = std::min(interval.second, universe.second);

        if (left - current >
            vehicle_params->vehicle_geometry_params().width()) {
            result.emplace_back(current, left);
        }
        current = std::max(current, right);
    }

    if (current < universe.second) {
        result.emplace_back(current, universe.second);
    }

    return result;
}

std::vector<std::pair<double, double>> GetLGaps(
    const DrivePassage *drive_passage,
    const VehicleParamsProto *vehicle_params,
    const double &s,
    const std::vector<std::pair<std::string, Polygon2d>> &obs_polygons) {
    const auto center_point = drive_passage->QueryPointXYAtS(s);
    const auto tangent = drive_passage->QueryTangentAtS(s);
    const auto ego_lane_boundary_info =
        drive_passage->QueryEnclosingLaneBoundariesAtS(s);
    const double &left_width = ego_lane_boundary_info.left->lat_offset;
    const double &right_width = ego_lane_boundary_info.right->lat_offset;
    Vec2d start_point =
        center_point.value() - tangent.value().Perp() * std::abs(right_width);
    Vec2d end_point =
        center_point.value() + tangent.value().Perp() * std::abs(left_width);

    ads_x::planning::math::LineSegment2d line_segment(start_point, end_point);
    std::vector<std::pair<double, double>> l_gaps;
    for (const auto &obs_polygon : obs_polygons) {
        const auto &polygon = obs_polygon.second;
        if (polygon.HasOverlap(line_segment)) {
            Vec2d first, last;
            (void)polygon.GetOverlap(line_segment, &first, &last);
            const auto first_offset =
                drive_passage->QueryFrenetLatOffsetAt(first);
            const auto last_offset =
                drive_passage->QueryFrenetLatOffsetAt(last);
            if (!first_offset.ok() || !last_offset.ok()) {
                continue;
            }

            double l_min = first_offset.value();
            double l_max = last_offset.value();
            if (first_offset.value() > last_offset.value()) {
                std::swap(l_min, l_max);
            }
            std::pair<double, double> l_gap(l_min, l_max);
            l_gaps.emplace_back(l_gap);
        }
    }

    if (l_gaps.empty()) {
        return l_gaps;
    }

    l_gaps = SortAndMerge(l_gaps);

    std::pair<double, double> universe(right_width, left_width);
    const auto &valid_l_gaps = FindComplement(vehicle_params, universe, l_gaps);

    return valid_l_gaps;
}

bool FindNextValidGaps(
    const VehicleParamsProto *vehicle_params,
    const double &s,
    const double &delta_s,
    const std::vector<std::pair<double, double>> &curr_l_gaps,
    const std::vector<std::pair<double, double>> &next_l_gaps,
    std::vector<std::pair<double, double>> &valid_next_l_gaps) {
    if (curr_l_gaps.empty() || next_l_gaps.empty()) {
        return true;
    }

    static constexpr double l_to_s_ratio = 0.5;

    for (const auto &curr_l_gap : curr_l_gaps) {
        for (const auto &next_l_gap : next_l_gaps) {
            std::pair<double, double> valid_next_l_gap;
            valid_next_l_gap.first = std::max(
                curr_l_gap.first - (delta_s * l_to_s_ratio), next_l_gap.first);
            valid_next_l_gap.second = std::min(
                curr_l_gap.second + (delta_s * l_to_s_ratio), next_l_gap.second);
            if (valid_next_l_gap.second - valid_next_l_gap.first >
                vehicle_params->vehicle_geometry_params().width()) {
                valid_next_l_gaps.emplace_back(valid_next_l_gap);
            }
        }
    }

    if (valid_next_l_gaps.empty()) {
        return true;
    }

    if (valid_next_l_gaps.size() == 1) {
        return false;
    }

    valid_next_l_gaps = SortAndMerge(valid_next_l_gaps);
    return false;
}

bool GetBlockS(const SpacetimeTrajectoryManager &st_traj_mgr,
               const DrivePassage *drive_passage,
               const VehicleParamsProto *vehicle_params,
               double *block_s) {
    *block_s = 0;
    if (drive_passage == nullptr) {
        return false;
    }
    const auto &stationary_object_trajs = st_traj_mgr.stationary_object_trajs();

    if (stationary_object_trajs.empty()) {
        *block_s = drive_passage->end_s();
        return false;
    }
    double s_min = drive_passage->end_s();
    double s_max = 0;
    std::vector<std::pair<std::string, Polygon2d>> obs_polygons;
    for (const auto &stationary_object : stationary_object_trajs) {
        const auto &id = stationary_object->object_id();
        const auto &contour = stationary_object->contour();
        auto obj_frenet_box = drive_passage->QueryFrenetBoxAtContour(contour);
        if (obj_frenet_box.ok()) {
            if (obj_frenet_box.value().s_min >
                vehicle_params->vehicle_geometry_params()
                    .front_edge_to_center()) {
                const auto ego_lane_boundary_info =
                    drive_passage->QueryEnclosingLaneBoundariesAtS(
                        obj_frenet_box.value().s_min);
                const double &left_width =
                    ego_lane_boundary_info.left->lat_offset;
                const double &right_width =
                    ego_lane_boundary_info.right->lat_offset;
                if (obj_frenet_box.value().l_min > left_width ||
                    obj_frenet_box.value().l_max < right_width) {
                    continue;
                }
                obs_polygons.emplace_back(id, contour);

                if (obj_frenet_box.value().s_min < s_min) {
                    s_min = obj_frenet_box.value().s_min;
                }
                if (obj_frenet_box.value().s_max > s_max) {
                    s_max = obj_frenet_box.value().s_max;
                }
            }
        }
    }

    if (s_min >= s_max) {
        *block_s = drive_passage->end_s();
        return false;
    }

    std::vector<std::vector<std::pair<double, double>>> l_gaps_vec;
    static constexpr double delta_s = 1;
    l_gaps_vec.reserve(std::ceil((s_max - s_min) / delta_s));
    for (double s = s_min; s <= s_max; s += delta_s) {
        const auto &l_gap =
            GetLGaps(drive_passage, vehicle_params, s, obs_polygons);
        if (!l_gap.empty()) {
            l_gaps_vec.emplace_back(l_gap);
        }
    }

    if (l_gaps_vec.empty()) {
        *block_s = drive_passage->end_s();
        return false;
    }

    std::vector<std::pair<double, double>> valid_next_l_gaps;
    std::vector<std::pair<double, double>> last_l_gaps = l_gaps_vec[0];
    for (size_t i = 0; i < l_gaps_vec.size() - 1; ++i) {
        valid_next_l_gaps.clear();
        const double &s = s_min + (i * delta_s);

        if (FindNextValidGaps(vehicle_params, s, delta_s, last_l_gaps,
                              l_gaps_vec[i + 1], valid_next_l_gaps)) {
            *block_s = s;
            return true;
        }

        last_l_gaps = valid_next_l_gaps;
    }

    return false;
}

}  // namespace planning
}  // namespace pnc_x