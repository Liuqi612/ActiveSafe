
#pragma once

#include <cmath>
#include <cstdint>
#include <ostream>

#include "path_planner/src/math/cosine_approximation.h"
#include "path_planner/src/math/util.h"
#include "path_planner/src/common/log.h"

namespace {
constexpr int kFastMath_FloatMantissaBits = 23;
constexpr float kFastMath_FloatLn2 = 0.69314718F;
constexpr float kFastMath_FloatExpBias = 127.0F;
constexpr float kFastMath_FloatExpOffset = 0.043677448F;
constexpr int kFastMath_FloatMaxExp = 255;
constexpr int kFastMath_DoubleMantissaBits = 52;
constexpr double kFastMath_DoubleLn2 = 0.6931471805599453;
constexpr double kFastMath_DoubleExpBias = 1023.0;
constexpr double kFastMath_DoubleExpOffset = 0.04367744890362246;
constexpr int kFastMath_DoubleMaxExp = 2047;
}  // namespace

namespace pnc_x {
namespace fast_math {

template <typename T>
inline T Atan2(T y, T x) {
    const T abs_x = std::abs(x);
    const T abs_y = std::abs(y);
    T min_val;
    T max_val;
    const bool x_lt_y = abs_x < abs_y;
    if (x_lt_y) {
        min_val = abs_x;
        max_val = abs_y;
    } else {
        min_val = abs_y;
        max_val = abs_x;
    }
    if (max_val == T(0.0)) {
        return 0.0;
    }
    const T a = min_val / max_val;
    const T s = a * a;
    T r = (((((T(-0.0464964749) * s) + T(0.15931422)) * s) - T(0.327622764)) *
           s * a) +
          a;
    if (x_lt_y) {
        r = T(M_PI_2) - r;
    }
    if (x < 0) {
        r = T(M_PI) - r;
    }
    if (y < 0) {
        r = -r;
    }
    return r;
}

template <int N = 7>
inline double CosNormalized(double x) {
    constexpr double kTwoOverPi = 2.0 * M_1_PI;
    const int quad = FloorToInt(x * kTwoOverPi) + 2;
    switch (quad) {
        case 0:
            return -CosPi2<N>(x + M_PI);
        case 1:
            return CosPi2<N>(-x);
        case 2:
            return CosPi2<N>(x);
        case 3:
            return -CosPi2<N>(M_PI - x);
        default:
            // LOG(FATAL) << "Invalid quad " << quad << " with input " << x;
            return -1.0;
    }
}
template <int N = 7>
inline double SinNormalized(double angle) {
    if (angle <= -M_PI_2) {
        return -CosPi2<N>(-angle - M_PI_2);
    } else {
        return CosNormalized<N>(NormalizeAngle(M_PI_2 - angle));
    }
}

inline double Sin(double angle) {
    return CosNormalized<7>(NormalizeAngle(M_PI_2 - angle));
}

inline double Cos(double angle) {
    return CosNormalized<7>(NormalizeAngle(angle));
}

template <int N = 7>
inline double SinN(double angle) {
    return CosNormalized<N>(NormalizeAngle(M_PI_2 - angle));
}

template <int N = 7>
inline double CosN(double angle) {
    return CosNormalized<N>(NormalizeAngle(angle));
}

inline constexpr float Log2(float x) {
    union {
        float f;
        uint32_t i;
    } vx = {x};
    union {
        uint32_t i;
        float f;
    } mx = {(vx.i & 0x007FFFFF) | 0x3f000000};

    union {
        uint32_t i;
        float f;
    } vy = {vx.i & 0xFF800000};
    float y = vy.f;

    return y - 124.22551499F - (1.498030302F * mx.f) -
           (1.72587999F / (0.3520887068F + mx.f));
}

inline constexpr float Log(float p) { return 0.69314718F * Log2(p); }

inline float FastExpSchraudolph(float x) {
    constexpr uint32_t kShiftVal = 1U << kFastMath_FloatMantissaBits;
    constexpr float kA = static_cast<float>(kShiftVal) / kFastMath_FloatLn2;
    constexpr float kB = static_cast<float>(kShiftVal) *
                         (kFastMath_FloatExpBias - kFastMath_FloatExpOffset);
    float res = (kA * x) + kB;

    constexpr float kC = static_cast<float>(kShiftVal);
    constexpr float kD = static_cast<float>(kShiftVal) * static_cast<float>(kFastMath_FloatMaxExp);
    if ((res < kC) || (res > kD)) {
        res = (res < kC) ? 0.0F : kD;
    }

    uint32_t n = static_cast<uint32_t>(res);
    memcpy(&res, &n, 4);
    return res;
}

inline double FastExpSchraudolph(double x) {
    constexpr uint64_t kShiftVal = 1ULL << kFastMath_DoubleMantissaBits;
    constexpr double kA = static_cast<double>(kShiftVal) / kFastMath_DoubleLn2;
    constexpr double kB = static_cast<double>(kShiftVal) *
                          (kFastMath_DoubleExpBias - kFastMath_DoubleExpOffset);
    double res = (kA * x) + kB;

    constexpr double kC = static_cast<double>(kShiftVal);
    constexpr double kD = static_cast<double>(kShiftVal) * static_cast<double>(kFastMath_DoubleMaxExp);
    if ((res < kC) || (res > kD)) {
        res = (res < kC) ? 0.0 : kD;
    }

    uint64_t n = static_cast<uint64_t>(res);
    memcpy(&res, &n, 8);
    return res;
}
}  // namespace fast_math
}  // namespace pnc_x
