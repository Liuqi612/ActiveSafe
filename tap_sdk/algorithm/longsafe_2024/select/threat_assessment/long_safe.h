/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_THREAT_ASSESSMENT_LONG_SAFE_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_THREAT_ASSESSMENT_LONG_SAFE_H_
#include "algorithm//vse/vehicle_state_estimed.h"
#include "algorithm/longsafe_2024/algo_interface/active_safety_coreout.h"
#include "algorithm/longsafe_2024/algo_interface/active_safety_vse.h"

#include "algorithm/longsafe_2024/algo_interface/as_lane_marker.h"
#include "algorithm/longsafe_2024/param/as_param.h"
#include "algorithm/longsafe_2024/scenario_analysis/society_scene.h"
#include "algorithm/longsafe_2024/select/object_evaluator/object_evaluator.h"
#include "algorithm/longsafe_2024/select/threat_assessment/ego_path.h"
#include "algorithm/longsafe_2024/select/threat_assessment/long_safe_if.h"
#include "algorithm/longsafe_2024/select/threat_assessment/longsafe_cal.h"
#include "math/lookuptable/lookuptable.h"
#include "math/utils/util_math.h"
#include "single_threat_assessor.h"

#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <map>
#include <tuple>
#include <utility>
// #define DEBUG_LONG_TSEL
namespace senseAD {
namespace tap {

class AsLongSafe {
  public:
    AsLongSafe();
    ~AsLongSafe();
    void Run(const active_safety::AsObstacleList &obs_list, const AS_LaneMarkerInfo_T &road_maker_info, const AsVseOut &vse,
             const AsSocietyScene &society_scene);
    void GetLongSafeOut(AsLongSafeOut &tap_out, const AsSocietyScene &society_scene);
    int32_t GetAebObjFusId() const;

  private:
    AsLongSafeCal long_safe_cal_;
    // Long safe target select output.
    As_LongSafeOut_T long_safe_out_;
    AsVseOut vse_;
    AsObstacleDataList obstacle_data_;
    active_safety::AsObstacleList obs_list_;

    AsSingleThreatAssessor single_ass;
    AsEgoPath curv_path_;
    AsScenarioDisc object_evaluator;
    int strict_scp_obj_idx = 0;
    int strict_cpnco_obj_idx = 0;
    int cpta_l_obj_index = 0;
    int csta_rn_obj_index = 0;

    int cpfao_obj_index = 0;
    int cbnao_obj_index = 0;
    int csfao_obj_index = 0;
    int scpo_obj_index = 0;
    bool CheckValidLongSafeObject(const AsVseOut &ego, const active_safety::AsObstacle &obs);
    void ConvertLongSafeToTapOut(const AsLgSafeTgt &long_safe_out, AsLongSafeObject &tap_obj, bool isLongPredTime);
    // Core Algorithm
    void CalcObstacleData(const active_safety::AsObstacleList &obs_list, const AsSocietyScene &society_scene);
    void FindThreatTarget(const active_safety::AsObstacleList &obs_list, const AsSocietyScene &society_scene);
    void UpdateLongSafeOut(const AsSingleThreatAssessor &ass);
    void UpdateLongSafeOutForStrictCpnco(const active_safety::AsObstacleList &obs_list);
    void UpdateLongSafeOutForStrictScp(const active_safety::AsObstacleList &obs_list);
    void UpdateLongSafeOutForCstaRn(const active_safety::AsObstacleList &obs_list);
    void UpdateLongSafeOutForCptal(const active_safety::AsObstacleList &obs_list);
    void UpdateLongSafeOutForCpfao(const active_safety::AsObstacleList &obs_list);
    void UpdateLongSafeOutForCbnao(const active_safety::AsObstacleList &obs_list);
    void UpdateLongSafeOutForCsfao(const active_safety::AsObstacleList &obs_list);
    void UpdateLongSafeOutForScpo(const active_safety::AsObstacleList &obs_list);
};
} // namespace tap
} // namespace senseAD
#endif // TAP_SDK_ALGORITHM_LONGSAFE_2024_SELECT_THREAT_ASSESSMENT_LONG_SAFE_H_
