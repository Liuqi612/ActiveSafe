
#pragma once

#ifdef __SSE4_1__
#include <immintrin.h>
#include <smmintrin.h>
#include <xmmintrin.h>
#ifndef __AVX512F__
#include <emmintrin.h>
#endif
#endif

#include <algorithm>
#include <boost/algorithm/clamp.hpp>
#include <cmath>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>
#include <absl/strings/str_format.h>

#include "path_planner/src/base/macros.h"
#include "path_planner/src/common/log.h"

namespace pnc_x {

namespace math_util_internal {

#ifdef __SSE4_1__

template <int kRoundingMode>
inline int RoundHelper(float val) {
#ifdef __AVX512F__
    return _mm_cvt_roundss_i32(_mm_load_ss(&val), kRoundingMode);
#else
    const auto t =
        static_cast<__m128>(_mm_round_ss(_mm_undefined_ps(), _mm_load_ss(&val), kRoundingMode));
    float rounded;
    static_cast<__v4sf>(_MM_EXTRACT_FLOAT(rounded, t, 0));
    return static_cast<int>(rounded);
#endif
}

template <int kRoundingMode>
inline int RoundHelper(double val) {
#ifdef __AVX512F__
    return _mm_cvt_roundsd_i32(_mm_load_ss(&val), kRoundingMode);
#else
    const auto rounded = _mm_cvtsd_f64(
        static_cast<__m128d>(_mm_round_sd(_mm_undefined_pd(), _mm_load_sd(&val), kRoundingMode)));
    return static_cast<int>(rounded);
#endif
}

#endif

}  // namespace math_util_internal

template <typename T>
inline int FloorToInt(T val) {
#ifdef __SSE4_1__
    return math_util_internal::RoundHelper<_MM_FROUND_TO_NEG_INF |
                                           _MM_FROUND_NO_EXC>(val);
#else
    return static_cast<int>(std::floor(val));
#endif
}

template <typename T>
inline int CeilToInt(T val) {
#ifdef __SSE4_1__
    return math_util_internal::RoundHelper<_MM_FROUND_TO_POS_INF |
                                           _MM_FROUND_NO_EXC>(val);
#else
    return static_cast<int>(std::ceil(val));
#endif
}

template <typename T>
inline int RoundToInt(T val) {
#ifdef __SSE4_1__
    return math_util_internal::RoundHelper<_MM_FROUND_TO_NEAREST_INT |
                                           _MM_FROUND_NO_EXC>(val);
#else
    return static_cast<int>(std::round(val));
#endif
}

template <typename T>
inline int TruncateToInt(T val) {
#ifdef __SSE4_1__
    return math_util_internal::RoundHelper<_MM_FROUND_TO_ZERO |
                                           _MM_FROUND_NO_EXC>(val);
#else
    return static_cast<int>(val);
#endif
}

template <typename T>
inline T Sign(T val) {
    const int positive_value = 1;
    const int negative_value = -1;
    const int zero_value = 0;
    const T positive = static_cast<T>(positive_value);
    const T negative = static_cast<T>(negative_value);
    const T zero = static_cast<T>(zero_value);
    if (val > zero) { return positive; }
    if (val < zero) { return negative; }
    return zero;
}

template <typename T>
inline bool IsInt(T val) {
    return val == TruncateToInt(val);
}

template <typename T>
bool InRange(T val, T bound0, T bound1) {
    if (bound0 > bound1) {
        std::swap(bound0, bound1);
    }
    return (val >= bound0) && (val <= bound1);
}

template <typename T>
constexpr T d2r(T d) {
    static_assert(std::is_floating_point<T>::value,
                  "d2r requires floating point type");
    return d * T(M_PI / 180.);
}
template <typename T>
constexpr T r2d(T r) {
    static_assert(std::is_floating_point<T>::value,
                  "r2d requires floating point type");
    return r * T(180. / M_PI);
}

inline constexpr double Mph2Mps(double mph) { return mph * (1609.34 / 3600.0); }
inline constexpr double Mps2Mph(double mps) { return mps * (3600.0 / 1609.34); }

inline constexpr double Kph2Mps(double kph) { return kph * (1000.0 / 3600.0); }
inline constexpr double Mps2Kph(double mps) { return mps * 3.6; }
constexpr double kMathEpsilon = 1e-10;
inline constexpr double CentiMeterToMeter(double centimeter) {
    return centimeter * 1e-2;
}
inline constexpr double MeterToCentiMeter(double meter) { return meter * 1e2; }

template <typename T>
constexpr T Sqr(T val) {
    return val * val;
}

template <typename T>
constexpr T SingleSideSqr(T val) {
    return (val > 0.0) ? (val * val) : 0.0;
}

template <typename T>
constexpr T ReLU(T val) {
    return (val > 0.0) ? val : 0.0;
}

template <typename T>
constexpr T UnitStep(T val) {
    return (val > 0.0) ? 1.0 : 0.0;
}

template <typename T>
constexpr T Cube(T val) {
    return val * Sqr(val);
}

template <typename T>
constexpr T Quar(T val) {
    return val * Cube(val);
}

template <typename T>
constexpr T Quin(T val) {
    return val * Quar(val);
}

template <typename T, typename U>
constexpr typename std::enable_if<std::is_integral<U>::value, T>::type Power(
    T val, U exp) {
    XCHECK(exp >= 0);
    T res = 1;
    while (exp > 0) {
        if (exp & 1) res *= val;
        exp >>= 1;
        val *= val;
    }
    return res;
}

template <typename T>
T Hypot(T a, T b) {
    return std::sqrt(Sqr(a) + Sqr(b));
}

template <typename T>
T Hypot(T a, T b, T c) {
    return std::sqrt(Sqr(a) + Sqr(b) + Sqr(c));
}

template <typename T, typename TS>
constexpr T Lerp(T a, T b, TS s) {
    return a + ((b - a) * s);
}

template <typename T>
T Lerp(const T &x0,
       const double t0,
       const T &x1,
       const double t1,
       const double t,
       bool clamp = false) {
    if (std::abs(t1 - t0) <= kMathEpsilon) {
        return x0;
    }
    if (clamp) {
        if (t0 <= t1) {
            if (t <= t0) {
                return x0;
            }
            if (t >= t1) {
                return x1;
            }
        } else {
            if (t >= t0) {
                return x0;
            }
            if (t <= t1) {
                return x1;
            }
        }
    }
    const double r = (t - t0) / (t1 - t0);
    const T x = x0 + (r * (x1 - x0));
    return x;
}

template <typename T>
constexpr T LerpFactor(T a, T b, T value) {
    if (b == a) { return 0.0; }
    return (value - a) / (b - a);
}

template <typename T>
constexpr T WrapIfNegative(T val, T range) {
    return val < 0.0 ? val + range : val;
}

template <typename T>
constexpr T WrapToRange(T val, T min_val, T max_val) {
    return WrapIfNegative(std::fmod(val - min_val, max_val - min_val),
                          max_val - min_val) +
           min_val;
}

template <typename T>
T NormalizeAngle(T angle) {
    const auto pi_value = M_PI;
    const auto normalize_threshold = M_PI * 10.0;
    const auto two_pi_value = M_PI * 2.0;
    const T pi = static_cast<T>(pi_value);
    const T negative_pi = -pi;
    const T pi_normalize_threshold = static_cast<T>(normalize_threshold);
    const T two_pi = static_cast<T>(two_pi_value);
    if (LIKELY(std::abs(angle) < pi)) {
        return angle;
    }
    if (std::abs(angle) > pi_normalize_threshold) {
        const auto normalized_angle = std::fmod(angle, two_pi_value);
        angle = static_cast<T>(normalized_angle);
    }
    if (angle < negative_pi) {
        do {
            angle += two_pi;
        } while (angle < negative_pi);
    } else {
        while (angle >= pi) {
            angle -= two_pi;
        }
    }
    return angle;
}

template <typename T>
T WrapAngle(T angle) {
    T new_angle = std::fmod(angle, M_PI * 2.0);
    return new_angle < T(0.0) ? new_angle + T(M_PI * 2.0) : new_angle;
}

template <typename T>
T WrapAngleInDegree(T angle_in_degree) {
    T new_angle_in_degree = std::fmod(angle_in_degree, 360.0);
    return new_angle_in_degree < T(0.0) ? new_angle_in_degree + T(360.0)
                                        : new_angle_in_degree;
}

template <typename T, typename TS>
constexpr T LerpAngle(T a, T b, TS s) {
    return NormalizeAngle(a + (NormalizeAngle(b - a) * s));
}

template <typename T>
constexpr T AngleDifference(T from, T to) {
    return NormalizeAngle(to - from);
}

inline double MeanAngle(const std::vector<double> &angles) {
    if (angles.empty()) {
        return 0.0;
    }
    double sin_sum = 0.0;
    double cos_sum = 0.0;
    for (const auto angle : angles) {
        sin_sum += std::sin(angle);
        cos_sum += std::cos(angle);
    }
    return std::atan2(sin_sum, cos_sum);
}

inline double OppositeAngle(double angle) {
    return NormalizeAngle(angle + M_PI);
}

template <typename T>
inline T SafeClamp(const T x,
                   const T min,
                   const T max,
                   bool failure_upon_exception = true) {
    constexpr double kEpsilon = 1e-8;
    if (min > max - kEpsilon) {
        // VLOG(1) << absl::StreamFormat(
        //     "Illegal clamp config: min = %7.6f > max = %7.6f !", min, max);
    }
    if (failure_upon_exception) XCHECK_LE(min, max);
    return boost::algorithm::clamp(x, min, max);
}

template <typename T>
inline void UpdateMax(const T x, T *max_val) {
    *max_val = std::max(x, *max_val);
}

template <typename T>
inline void UpdateMin(const T x, T *min_val) {
    *min_val = std::min(x, *min_val);
}

template <typename T>
inline T Min(T &&t) {
    return std::forward<T>(t);
}
template <typename T0, typename T1, typename... Ts>
inline typename std::common_type<T0, T1, Ts...>::type Min(T0 &&v0,
                                                          T1 &&v1,
                                                          Ts &&... vs) {
    if (v0 < v1) {
        return Min(v0, std::forward<Ts>(vs)...);
    } else {
        return Min(v1, std::forward<Ts>(vs)...);
    }
}
template <typename T>
inline T Max(T &&t) {
    return std::forward<T>(t);
}
template <typename T0, typename T1, typename... Ts>
inline typename std::common_type<T0, T1, Ts...>::type Max(T0 &&v0,
                                                          T1 &&v1,
                                                          Ts &&... vs) {
    if (v0 > v1) {
        return Max(v0, std::forward<Ts>(vs)...);
    } else {
        return Max(v1, std::forward<Ts>(vs)...);
    }
}

template <typename T>
inline T EvaluatePolynominal(const std::vector<T> &coef, T var) {
    T res = 0;
    for (auto i = coef.rbegin(); i != coef.rend(); ++i) {
        res = (res * var) + *i;
    }
    return res;
}

std::vector<double> QuadraticRoot(double a, double b, double c);

double FloorWithBase(double x, double base);

inline double Sigmoid(const double x) { return 1.0 / (1.0 + std::exp(-x)); }

template <typename T>
std::vector<double> SoftMax(const std::vector<T> &input) {
    double m = std::numeric_limits<double>::lowest();
    int size = input.size();
    for (int i = 0; i < size; ++i) {
        if (m < input[i]) {
            m = input[i];
        }
    }

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += exp(input[i] - m);
    }

    const double constant = m + log(sum);
    std::vector<double> output(size, 0.0);
    for (int i = 0; i < size; ++i) {
        output[i] = exp(input[i] - constant);
    }
    return output;
}

double QuadraticFunctionMinValue(
    double a, double b, double c, double x0, double x1);

inline constexpr int64_t CumProd(int m, int n) {
    if (m > n) { return 0; }
    if (m == n) { return m; }
    return CumProd(m, n - 1) * n;
}

inline double PowerThreeHalves(double x) { return x * std::sqrt(x); }
}  // namespace pnc_x
