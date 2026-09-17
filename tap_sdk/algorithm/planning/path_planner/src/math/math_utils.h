
#pragma once

#include <cstdint>
#include <limits>
#include <list>
#include <utility>
#include <vector>

#include "path_planner/src/common/type_def.h"
#include "path_planner/src/math/vec2d.h"

namespace ads_x {
namespace planning {
namespace math {
double Sqr(const double x);

double CrossProd(const Vec2d &start_point,
                 const Vec2d &end_point_1,
                 const Vec2d &end_point_2);

double InnerProd(const Vec2d &start_point,
                 const Vec2d &end_point_1,
                 const Vec2d &end_point_2);

double CrossProd(const double x0,
                 const double y0,
                 const double x1,
                 const double y1);

double InnerProd(const double x0,
                 const double y0,
                 const double x1,
                 const double y1);

double WrapAngle(const double angle);

double NormalizeAngle(const double angle);

double AngleDiff(const double a1, const double a2);

int RandomInt(const int s, const int t, unsigned int rand_seed = 1U);

double RandomDouble(const double s,
                    const double t,
                    unsigned int rand_seed = 1U);

TurnType GetTurnTypeByHeading(const double &entry_heading,
                              const double &exit_heading);

template <typename T>
T Square(const T value) {
    return value * value;
}

template <typename T>
T Clamp(const T value, T bound1, T bound2) {
    if (bound1 > bound2) {
        std::swap(bound1, bound2);
    }

    if (value < bound1) {
        return bound1;
    } else if (value > bound2) {
        return bound2;
    }
    return value;
}

double Gaussian(const double u, const double std, const double x);

double Sigmoid(const double x);

std::pair<double, double> RotateVector2d(const double x,
                                         const double y,
                                         const double theta);

Vec2d RotateVector2d(const Vec2d &vec, const double &theta);

std::pair<double, double> RFUToFLU(const double x, const double y);

std::pair<double, double> FLUToRFU(const double x, const double y);

void L2Norm(int feat_dim, float *feat_data);

std::pair<double, double> Cartesian2Polar(double x, double y);

template <typename T>
T interp1_inc(const std::vector<T> &X, const std::vector<T> &Y, T xp) {
    T temp1 = 0;
    uint16_t i;

    if (X.size() != Y.size()) {
        return 0;
    }

    if (xp <= X.front()) {
        temp1 = Y.front();
    } else if (xp >= X.back()) {
        temp1 = Y.back();
    } else {
        for (i = 0; i < X.size() - 1; ++i) {
            if (xp >= X.at(i) && xp < X.at(i + 1)) {
                break;
            }
        }
        if (i == X.size() - 1) {
            i = i - 1;
        }
        temp1 = Y.at(i) + (((Y.at(i + 1) - Y.at(i)) / (X.at(i + 1) - X.at(i))) *
                           (xp - X.at(i)));
    }
    return temp1;
}

template <typename T>
T interp1_dec(std::vector<T> &X, std::vector<T> &Y, T xp);

template <typename T>
T RateLmt(T CurrentValue, const T &LastValue, T &MinLmt, T &MaxLmt);

template <typename T>
T Cubic(const T value);

template <typename T>
T interp2_inc(std::vector<T> &X,
              std::vector<T> &Y,
              std::vector<std::vector<T>> &Z,
              T xp,
              T yp);

template <typename T>
T SafeDivide(const T &divisor, T dividend);

template <typename T>
T QuaternionToYaw(T w, T x, T y, T z) {
    return atan2(
        static_cast<T>(2.0) * ((x * y) + (w * z)),
        static_cast<T>(1.0) - (static_cast<T>(2.0) * ((y * y) + (z * z))));
}

}  // namespace math
}  // namespace planning
}  // namespace ads_x
