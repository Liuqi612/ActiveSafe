
#include <cmath>

#include "path_planner/src/common/log.h"
#include "path_planner/src/common/throw_check.h"
#include "path_planner/src/math/double.h"

namespace ads_x {
namespace planning {
namespace math {

constexpr double Double::epsilon_;

Double::CompareType Double::Compare(const double &a, const double &b) {
    return Double::Compare(a, b, epsilon_);
}

Double::CompareType Double::Compare(const double &a,
                                    const double &b,
                                    const double &epsilon) {
    XCHECK(!(std::isnan(a) && std::isnan(b) && std::isnan(epsilon)));
    if (LessThan(a, b, epsilon)) {
        return CompareType::LESS;
    } else if (GreaterThan(a, b, epsilon)) {
        return CompareType::GREATER;
    } else {
        return CompareType::EQUAL;
    }
}

bool Double::LessThan(const double &a, const double &b, const double &epsilon) {
    return (b - a) > epsilon;
}

bool Double::GreaterThan(const double &a,
                         const double &b,
                         const double &epsilon) {
    return (a - b) > epsilon;
}

}  // namespace math
}  // namespace planning
}  // namespace ads_x
