#ifndef TAP_SDK_ALGORITHM_ELK_ELK_FUNCTION_H_
#define TAP_SDK_ALGORITHM_ELK_ELK_FUNCTION_H_
#include "elk_state_machine.h"
#include "elk_target_selection.h"
#include "environment_processing.h"
#include "elk_threat_assessment.h"

namespace active_safety {
namespace elk {

class ElkFunction {
  public:
    using ElkState = ElkStateMachine::State;

    ElkFunction()
      : rollingCounter_(0) {};
    ~ElkFunction() = default;

    void Update(const AsVseOut &vse_out, const LanesInfo &road_info, const GlobalConfig &config, const AsObstacleList &obs_list);
    void Update(const AsVseOut &vse_out,
                const LanesInfo &road_info,
                const GlobalConfig &config,
                const AsObstacleList &obs_list,
                float elk_torsion_bar_trq);

    const ElkTargetSelection& getElkTargetSelectionObj() const {return elk_target_selector_;};
    const ElkThreatAssessment& getElkThreatAssossmentObj() const {return elk_threat_assessor_;};
    const EnvironmentProcessing& getElkEnvironmentProcessObj() const {return environment_processor_;};
    const ElkStateMachine& getElkStateMachineObj() const { return elk_state_machine_; };

    uint8_t getElkRLC() const { return rollingCounter_; };
    std::array<uint8_t, 3> getElkVersion() const { return version_info_; };

  private:
    void Init();

    // function
    ElkTargetSelection    elk_target_selector_;
    EnvironmentProcessing environment_processor_;
    ElkThreatAssessment   elk_threat_assessor_;
    ElkStateMachine       elk_state_machine_;

    // information
    uint8_t rollingCounter_;
    std::array<uint8_t, 3> version_info_{1, 1, 0};

};

} // namespace elk
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_ELK_ELK_FUNCTION_H_
