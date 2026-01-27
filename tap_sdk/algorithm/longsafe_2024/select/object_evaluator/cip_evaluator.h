/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include "algorithm/longsafe_2024/algo_interface/active_safety_vse.h"
#include "algorithm/longsafe_2024/algo_interface/as_fusion_object.h"
#include "math/lookuptable/lookuptable.h"
#include "algorithm/obstacle/obstacle.h"
#include "evaluator_base.h"
#include "obj_eval_types.h"
namespace senseAD {
namespace tap {

/*AsCipEvaluator:: Check for long moving scene*/
class AsCipEvaluator : public AsBaseEvaluator {
  public:
    AsCipEvaluator();
    ~AsCipEvaluator();
    void ProcessCipEvaluator(const active_safety::AsObstacle &cip_obj, const AsVseOut &vse_out);

  private:
    void    CheckIsCipScene(const active_safety::AsObstacle &cip_obj, const AsVseOut &vse_out);
    void    CheckOverlap(const active_safety::AsObstacle &cip_obj, const AsVseOut &vse_out);
    void    CheckObjectSuddenlyDetect(const active_safety::AsObstacle &cip_obj);
    bool    cip_flag = false;
    int32_t fus_id   = 0;
};

} // namespace tap
} // namespace senseAD
