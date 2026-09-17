#include "optimization/problem/mixed_fourth_order_bicycle.h"

namespace pnc_x {
namespace planning {

// 为 constexpr 静态成员变量提供定义
constexpr double MixedFourthOrderBicycle::kMinSpeed;
constexpr double MixedFourthOrderBicycle::kMaxSpeed;
constexpr int MixedFourthOrderBicycle::kControlJIndex;
constexpr int MixedFourthOrderBicycle::kControlChiIndex;
constexpr int MixedFourthOrderBicycle::kStateSize;
constexpr int MixedFourthOrderBicycle::kControlSize;
constexpr int MixedFourthOrderBicycle::kStateXIndex;
constexpr int MixedFourthOrderBicycle::kStateYIndex;
constexpr int MixedFourthOrderBicycle::kStateThetaIndex;
constexpr int MixedFourthOrderBicycle::kStateVIndex;
constexpr int MixedFourthOrderBicycle::kStateKappaIndex;
constexpr int MixedFourthOrderBicycle::kStateAIndex;
constexpr int MixedFourthOrderBicycle::kStatePsiIndex;
constexpr int MixedFourthOrderBicycle::kStateSIndex;
constexpr char MixedFourthOrderBicycle::kProblemPrefix[];

}  // namespace planning
}  // namespace pnc_x