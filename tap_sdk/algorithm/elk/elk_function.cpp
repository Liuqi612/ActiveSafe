#include "elk_function.h"

#include "elk_debug_logger.h"

namespace active_safety {
namespace elk {

void ElkFunction::Update(const AsVseOut &vse_out, const LanesInfo &road_info, const GlobalConfig &config, const AsObstacleList &obs_list)
{
    elk_target_selector_.Update(vse_out, road_info, config, obs_list);
    environment_processor_.Update(vse_out, road_info);
    const LaneBoundaryParameters lane_boundary = environment_processor_.getLaneBoundaryInfo();
    const LaneCenterParameters lane_center = environment_processor_.getLaneCenterInfo();
    const AsOnComingOut &oncoming_out = elk_target_selector_.GetOncomingOutput();
    const AsOverTakingOut &overtaking_out = elk_target_selector_.GetOvertakingOutput();
    elk_threat_assessor_.Update(vse_out,
                                lane_center,
                                vse_out.config,
                                config,
                                oncoming_out,
                                overtaking_out);
    const ElkTaSl ta_info = elk_threat_assessor_.getElkTAInfo();
    elk_state_machine_.Update(vse_out,
                              road_info,
                              lane_boundary,
                              lane_center,
                              ta_info,
                              config);
    LogElkFrame(vse_out,
                road_info,
                config,
                lane_boundary,
                lane_center,
                ta_info,
                elk_threat_assessor_.getElkThreatDebugSnapshot(),
                oncoming_out,
                overtaking_out,
                elk_state_machine_,
                rollingCounter_);

    if (rollingCounter_ >= 255) {
        rollingCounter_ = 0;
    } else {
        rollingCounter_++;
    }
}

void ElkFunction::Update(const AsVseOut &vse_out,
                         const LanesInfo &road_info,
                         const GlobalConfig &config,
                         const AsObstacleList &obs_list,
                         float elk_torsion_bar_trq)
{
    AsVseOut elk_vse_out = vse_out;

    // ELK uses the raw torsion-bar torque from replay input for driver override.
    // Keep this override local to ELK so VSE output used by other modules is not changed.
    elk_vse_out.torsion_bar_trq = elk_torsion_bar_trq;

    Update(elk_vse_out, road_info, config, obs_list);
}

} // namespace elk
} // namespace active_safety
