#include "initializer/interactive_search/search/interaction_cost.h"
#include "common/assist_util.h"
#include "util/map_util.h"

namespace pnc_x {
namespace planning {

double InteractionCost::GetInteractionCost(
    const VehicleParamsProto *vehicle_params,
    const ObstacleDecisionGroup &decision_group,
    const std::unordered_map<std::string, ObstacleBehavior> *obs_behavior_map,
    double cur_node_time,
    double cur_node_s,
    double cur_node_v,
    double cur_node_l,
    bool is_lane_change) {
    double dynamic_obs_cost = 0.0;
    int pred_pt_index = cur_node_time / decision_group.traj_time_step;
    for (const auto &pair : decision_group.obstacles_decision) {
        const auto &object_id = pair.first;
        const auto &obs_decision = pair.second;

        if (!is_lane_change) {
            if (decision_group.obs_goal_gap.lead_obj_id.has_value() &&
                obs_decision.obj_id ==
                    decision_group.obs_goal_gap.lead_obj_id.value()) {
                dynamic_obs_cost +=
                    LeadingCost(obs_decision, vehicle_params, pred_pt_index,
                                cur_node_s, cur_node_v);
            }
        }
    }

    return dynamic_obs_cost;
}

double InteractionCost::CutinCost(const ObstacleDecision &obs,
                                  const VehicleParamsProto *vehicle_params,
                                  int pred_pt_index,
                                  double cur_node_s,
                                  double cur_node_v) {
    int traj_pt_size = obs.modified_pred_traj.size();
    if (pred_pt_index >= traj_pt_size) {
        return 0.0;
    }

    double obs_max_l =
        obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)]
            .sl_boundary.l_max;
    double obs_min_l =
        obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)]
            .sl_boundary.l_min;
    bool obs_intruded =
        std::fabs(obs_max_l) < 1.75 || std::fabs(obs_min_l) < 1.75;
    if (!obs_intruded) {
        return 0.0;
    }
    double intruded_dis = 0.0;
    if ((obs_max_l > -1.75) && (obs_min_l < -1.75)) {
        intruded_dis = 1.75 - std::fabs(obs_max_l);
    } else if ((obs_max_l > 1.75) && (obs_min_l < 1.75)) {
        intruded_dis = 1.75 - std::fabs(obs_max_l);
    } else {
        intruded_dis = obs_max_l - obs_min_l;
    }
    double slack_cost_weight = 1e4 * std::pow(intruded_dis, 2);
    const double cuntin_stational_ratio = 1.0;
    const double ttc_threshold = 2.0;
    double obs_v =
        obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)]
            .traj_point.v();

    if (obs.decision_tag.lon_decision_tag == OvertakeYieldType::kOvertake) {
        double obs_max_s =
            obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].sl_boundary.s_max;
        double ego_min_s =
            cur_node_s -
            vehicle_params->vehicle_geometry_params().back_edge_to_center();
        double overtake_s_diff = ego_min_s - obs_max_s;
        double expected_overtake_dis = 0.2 * obs_v;
        if (obs_v > cur_node_v) {
            expected_overtake_dis += ttc_threshold * (obs_v - cur_node_v);
        }
        if (overtake_s_diff < 0.0) {
            return slack_cost_weight * std::pow(std::fabs(overtake_s_diff), 2);
        } else if (overtake_s_diff < expected_overtake_dis) {
            return cuntin_stational_ratio *
                   (expected_overtake_dis - overtake_s_diff);
        }
    } else if (obs.decision_tag.lon_decision_tag == OvertakeYieldType::kYield) {
        double obs_min_s =
            obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)]
                .sl_boundary.s_min;
        double ego_max_s =
            cur_node_s +
            vehicle_params->vehicle_geometry_params().front_edge_to_center();
        double yield_s_diff = obs_min_s - ego_max_s;
        double expected_yield_dis = std::max(0.3 * cur_node_v, 2.0);
        if (obs_v < cur_node_v) {
            expected_yield_dis += ttc_threshold * (cur_node_v - obs_v);
        }
        if (yield_s_diff < 0.0) {
            return slack_cost_weight * std::pow(std::fabs(yield_s_diff), 2);
        } else if (yield_s_diff < expected_yield_dis) {
            return cuntin_stational_ratio * (expected_yield_dis - yield_s_diff);
        }
    }

    return 0.0;
}

double InteractionCost::CrossCost(const ObstacleDecision &obs,
                                  const VehicleParamsProto *vehicle_params,
                                  int pred_pt_index,
                                  double cur_node_s,
                                  double cur_node_v) {
    int traj_pt_size = obs.modified_pred_traj.size();
    if (pred_pt_index >= traj_pt_size) {
        return 0.0;
    }

    float obs_max_l = obs.modified_pred_traj[pred_pt_index].sl_boundary.l_max;
    float obs_min_l = obs.modified_pred_traj[pred_pt_index].sl_boundary.l_min;
    if ((obs_min_l > 1.75) && (obs_max_l < -1.75)) {
        return 0.0;
    }

    double total_cost = 0.0;
    const double cross_stational_ratio = 1.0;
    const double ttc_threshold = 2.0;
    double obs_v = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].traj_point.v();
    double obs_max_s = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].sl_boundary.s_max;
    double obs_min_s = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].sl_boundary.s_min;
    double ego_max_s =
        cur_node_s +
        vehicle_params->vehicle_geometry_params().front_edge_to_center();
    double ego_min_s =
        cur_node_s -
        vehicle_params->vehicle_geometry_params().back_edge_to_center();

    if (obs.decision_tag.lon_decision_tag == OvertakeYieldType::kOvertake) {
        double overtake_s_diff = ego_min_s - obs_max_s;
        const double ttc_threshold = 2.0;
        if (ego_min_s < obs_max_s) {
            return cross_stational_ratio * std::pow(obs_max_s - ego_min_s, 2);
        }
    } else if (obs.decision_tag.lon_decision_tag == OvertakeYieldType::kYield) {
        double yield_s_diff = obs_min_s - ego_max_s;
        double expected_yield_dis = std::max(0.3 * cur_node_v, 2.0);
        const double ttc_threshold = 2.0;
        expected_yield_dis += ttc_threshold * cur_node_v;
        if (yield_s_diff < expected_yield_dis) {
            return cross_stational_ratio * (expected_yield_dis - yield_s_diff);
        }
    }

    return total_cost;
}

double InteractionCost::SideCost(const ObstacleDecision &obs,
                                 const VehicleParamsProto *vehicle_params,
                                 int pred_pt_index,
                                 double cur_node_s,
                                 double cur_node_v,
                                 double cur_node_l) {
    int traj_pt_size = obs.modified_pred_traj.size();
    if (pred_pt_index >= traj_pt_size) {
        return 0.0;
    }
    float ego_max_l =
        cur_node_l + (0.5 * vehicle_params->vehicle_geometry_params().width());
    float ego_min_l =
        cur_node_l - (0.5 * vehicle_params->vehicle_geometry_params().width());
    bool corner_in_side_lane = (ego_min_l > 1.75) || (ego_max_l < -1.75);
    if (!corner_in_side_lane) {
        return 0.0;
    }

    double total_cost = 0.0;

    double ego_max_s =
        cur_node_s +
        vehicle_params->vehicle_geometry_params().front_edge_to_center();
    double ego_min_s =
        cur_node_s -
        vehicle_params->vehicle_geometry_params().back_edge_to_center();
    double obs_v = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].traj_point.v();
    double obs_max_s = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].sl_boundary.s_max;
    double obs_min_s = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].sl_boundary.s_min;
    double yield_s_diff = obs_min_s - ego_max_s;
    double overtake_s_diff = ego_min_s - obs_max_s;
    double expected_yield_dis = std::max(0.3 * cur_node_v, 2.0);
    double expected_overtake_dis = 1.0 * obs_v;
    const double sideback_stational_ratio = 10.0;
    const double ttc_threshold = 2.0;
    if (obs.decision_tag.lon_decision_tag == OvertakeYieldType::kOvertake) {
        double overtake_s_diff = ego_min_s - obs_max_s;
        double expected_overtake_dis = 0.2 * obs_v;
        if (obs_v > cur_node_v) {
            expected_overtake_dis += ttc_threshold * (obs_v - cur_node_v);
        }
        if (overtake_s_diff < expected_overtake_dis) {
            return sideback_stational_ratio *
                   (expected_overtake_dis - overtake_s_diff);
        }
    } else if (obs.decision_tag.lon_decision_tag == OvertakeYieldType::kYield) {
        double yield_s_diff = obs_min_s - ego_max_s;
        double expected_yield_dis = std::max(0.3 * cur_node_v, 2.0);
        if (obs_v < cur_node_v) {
            expected_yield_dis += ttc_threshold * (cur_node_v - obs_v);
        }
        if (yield_s_diff < expected_yield_dis) {
            return sideback_stational_ratio *
                   (expected_yield_dis - yield_s_diff);
        }
    }

    return total_cost;
}

double InteractionCost::FrontCost(const ObstacleDecision &obs,
                                  const VehicleParamsProto *vehicle_params,
                                  int pred_pt_index,
                                  double cur_node_s,
                                  double cur_node_v,
                                  double cur_node_l) {
    int traj_pt_size = obs.modified_pred_traj.size();
    if (pred_pt_index >= traj_pt_size) {
        return 0.0;
    }

    float total_cost = 0.0F;

    double ego_max_s =
        cur_node_s +
        vehicle_params->vehicle_geometry_params().front_edge_to_center();
    double ego_min_s =
        cur_node_s -
        vehicle_params->vehicle_geometry_params().back_edge_to_center();
    double ego_max_l =
        cur_node_l + (0.5 * vehicle_params->vehicle_geometry_params().width());
    double ego_min_l =
        cur_node_l - (0.5 * vehicle_params->vehicle_geometry_params().width());
    double obs_v = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].traj_point.v();
    double obs_max_l = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].sl_boundary.l_max;
    double obs_min_l = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].sl_boundary.l_min;
    double obs_max_s = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].sl_boundary.s_max;
    double obs_min_s = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].sl_boundary.s_min;

    double yield_s_diff = obs_min_s - ego_max_s;
    double overtake_s_diff = ego_min_s - obs_max_s;
    double expected_yield_dis = std::max(0.3 * cur_node_v, 1.0);
    double expected_overtake_dis = 0.1 * obs_v;
    const double lateral_ratio = 10.0;
    const double stational_ratio = 1.0;

    bool stationally_overlapped =
        (ego_max_s > obs_min_s) && (ego_min_s < obs_max_s);
    bool laterally_overlapped =
        (ego_max_l > obs_min_l) && (ego_min_l < obs_max_l);
    if (stationally_overlapped) {
        double left_nudge_dis = ego_min_l - obs_max_l;
        double right_nudge_dis = obs_min_l - ego_max_l;
        if ((left_nudge_dis > 0.0) && (left_nudge_dis < 1.0)) {
            total_cost += lateral_ratio * (1.0 - left_nudge_dis);
        } else if ((right_nudge_dis > 0.0) && (right_nudge_dis < 1.0)) {
            total_cost += lateral_ratio * (1.0 - right_nudge_dis);
        }
    } else if (laterally_overlapped) {
        if (obs_v < cur_node_v) {
            const double ttc_threshold = 2.0;
            expected_yield_dis += ttc_threshold * (cur_node_v - obs_v);
        } else {
            const double ttc_threshold = 2.0;
            expected_overtake_dis += ttc_threshold * (obs_v - cur_node_v);
        }
        if ((yield_s_diff > 0.0) && (yield_s_diff < expected_yield_dis)) {
            total_cost += stational_ratio * (expected_yield_dis - yield_s_diff);
        } else if ((overtake_s_diff > 0.0) &&
                   (overtake_s_diff < expected_overtake_dis)) {
            total_cost +=
                stational_ratio * (expected_overtake_dis - overtake_s_diff);
        }
    }

    return total_cost;
}

double InteractionCost::LeadingCost(const ObstacleDecision &obs,
                                    const VehicleParamsProto *vehicle_params,
                                    int pred_pt_index,
                                    double cur_node_s,
                                    double cur_node_v) {
    int traj_pt_size = obs.modified_pred_traj.size();
    if (pred_pt_index >= traj_pt_size) {
        return 0.0;
    }

    const double stational_ratio = 1.0;
    double ego_max_s =
        cur_node_s +
        vehicle_params->vehicle_geometry_params().front_edge_to_center();
    double obs_min_s = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].sl_boundary.s_min;
    double obs_v = obs.modified_pred_traj[static_cast<size_t>(pred_pt_index)].traj_point.v();
    double total_cost = 0.0;
    double yield_s_diff = obs_min_s - ego_max_s;
    double expected_yield_dis = std::max(0.3 * cur_node_v, 1.0);
    if (obs_v < cur_node_v) {
        const double ttc_threshold = 2.0;
        expected_yield_dis += ttc_threshold * (cur_node_v - obs_v);
    }
    if (yield_s_diff < expected_yield_dis) {
        total_cost += stational_ratio * (expected_yield_dis - yield_s_diff);
    }

    return total_cost;
}

}  // namespace planning
}  // namespace pnc_x
