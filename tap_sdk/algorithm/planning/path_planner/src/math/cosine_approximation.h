#include <limits>
#pragma once

namespace pnc_x {
namespace fast_math {

double Cos_52(double x);

double Cos_73(double x);

double Cos_121(double x);

template <int N = 7>
double CosPi2(double angle) {
    switch (N) {
        case 5:
            return Cos_52(angle);
        case 7:
            return Cos_73(angle);
        case 12:
            return Cos_121(angle);
        default:

            return std::numeric_limits<double>::quiet_NaN();
    }
}

}  // namespace fast_math
}  // namespace pnc_x
