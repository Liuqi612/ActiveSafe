#include "decision/obstacle_intention_estimation.h"
#include "initializer/interactive_search/common/common.h"

namespace pnc_x {
namespace planning {

class InteractionCost final {
 public:
    static double GetInteractionCost(
        const VehicleParamsProto *vehicle_params,
        const ObstacleDecisionGroup &decision_group,
        const std::unordered_map<std::string, ObstacleBehavior>
            *obs_behavior_map,
        double cur_node_time,
        double cur_node_s,
        double cur_node_v,
        double cur_node_l,
        bool is_lane_change);

 private:
    static double FrontCost(const ObstacleDecision &obs,
                            const VehicleParamsProto *vehicle_params,
                            int pred_pt_index,
                            double cur_node_s,
                            double cur_node_v,
                            double cur_node_l);
    static double SideCost(const ObstacleDecision &obs,
                           const VehicleParamsProto *vehicle_params,
                           int pred_pt_index,
                           double cur_node_s,
                           double cur_node_v,
                           double cur_node_l);
    static double CutinCost(const ObstacleDecision &obs,
                            const VehicleParamsProto *vehicle_params,
                            int pred_pt_index,
                            double cur_node_s,
                            double cur_node_v);
    static double CrossCost(const ObstacleDecision &obs,
                            const VehicleParamsProto *vehicle_params,
                            int pred_pt_index,
                            double cur_node_s,
                            double cur_node_v);
    static double LeadingCost(const ObstacleDecision &obs,
                              const VehicleParamsProto *vehicle_params,
                              int pred_pt_index,
                              double cur_node_s,
                              double cur_node_v);
};

}  // namespace planning
}  // namespace pnc_x