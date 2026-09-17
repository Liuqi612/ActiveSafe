
#include "math/angle.h"
#include "math/sin_table.h"

namespace ads_x {
namespace planning {
namespace math {

float sin(Angle16 a) {
    int16_t idx = a.raw();
    if (idx < -Angle16::RAW_PI_2) {
        idx += static_cast<int16_t>(Angle16::RAW_PI);
        return -SIN_TABLE[idx];
    }
    if (idx < 0) {
        return -SIN_TABLE[-idx];
    }
    if (idx < Angle16::RAW_PI_2) {
        return SIN_TABLE[idx];
    }
    idx = static_cast<int16_t>(Angle16::RAW_PI - idx);
    if (idx < 0) {
        idx = -idx;
    }
    return SIN_TABLE[idx];
}

float cos(Angle16 a) {
    Angle16 b(Angle16::RAW_PI_2 - a.raw());
    return sin(b);
}

float tan(Angle16 a) { return sin(a) / cos(a); }

float sin(Angle8 a) {
    Angle16 b((a.raw()) << 8);
    return sin(b);
}

float cos(Angle8 a) {
    Angle16 b((a.raw()) << 8);
    return cos(b);
}

float tan(Angle8 a) {
    Angle16 b((a.raw()) << 8);
    return tan(b);
}
}  // namespace math
}  // namespace planning
}  // namespace ads_x