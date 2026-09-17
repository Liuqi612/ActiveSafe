#include "evaluator_base.h"
namespace senseAD {
namespace tap {
AsBaseEvaluator::AsBaseEvaluator() {}
AsBaseEvaluator::~AsBaseEvaluator() = default;

uint32_t AsBaseEvaluator::behavior = 0;

uint32_t AsBaseEvaluator::Get() { return behavior; }

void AsBaseEvaluator::Set(bool flag, uint32_t behv) {
  if (flag == true) {
    behavior |= behv;
  } else {
    behavior &= ~behv;
  }
}
} // namespace tap
} // namespace senseAD
