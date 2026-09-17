
#include <cmath>
#include <utility>

#include "path_planner/src/math/angle.h"
#include "path_planner/src/math/fast_math.h"
#include "path_planner/src/math/math_utils.h"
namespace ads_x {
namespace planning {
namespace math {
double Sqr(const double x) { return x * x; }

double CrossProd(const Vec2d &start_point,
                 const Vec2d &end_point_1,
                 const Vec2d &end_point_2) {
    return (end_point_1 - start_point).CrossProd(end_point_2 - start_point);
}

double InnerProd(const Vec2d &start_point,
                 const Vec2d &end_point_1,
                 const Vec2d &end_point_2) {
    return (end_point_1 - start_point).InnerProd(end_point_2 - start_point);
}

double CrossProd(const double x0,
                 const double y0,
                 const double x1,
                 const double y1) {
    return (x0 * y1) - (x1 * y0);
}

double InnerProd(const double x0,
                 const double y0,
                 const double x1,
                 const double y1) {
    return (x0 * x1) + (y0 * y1);
}

double WrapAngle(const double angle) {
    const double new_angle = std::fmod(angle, M_PI * 2.0);
    return new_angle < 0.0 ? new_angle + (M_PI * 2.0) : new_angle;
}

double NormalizeAngle(const double angle) {
    double a = std::fmod(angle + M_PI, 2.0 * M_PI);
    if (a < 0.0) {
        a += 2.0 * M_PI;
    }
    return a - M_PI;
}

double AngleDiff(const double a1, const double a2) {
    return NormalizeAngle(a1 - a2);
}

int RandomInt(const int s, const int t, unsigned int rand_seed) {
    if (s >= t) {
        return s;
    }
    return s + (rand_r(&rand_seed) % (t - s + 1));
}

double RandomDouble(const double s, const double t, unsigned int rand_seed) {
    return s + ((t - s) / 16383.0 *
                static_cast<double>(rand_r(&rand_seed) & 16383));
}

double Gaussian(const double u, const double std, const double x) {
    return (1.0 / std::sqrt(2.0 * M_PI * std * std)) *
           std::exp(-(x - u) * (x - u) / (2.0 * std * std));
}

std::pair<double, double> RotateVector2d(const double x_in,
                                         const double y_in,
                                         const double theta) {
    const auto angle = math::Angle16::FromRad(theta);
    const double cos_theta = math::cos(angle);
    const double sin_theta = math::sin(angle);

    double x = (cos_theta * x_in) - (sin_theta * y_in);
    double y = (sin_theta * x_in) + (cos_theta * y_in);

    return std::make_pair(x, y);
}

std::pair<double, double> Cartesian2Polar(double x, double y) {
    double r = std::sqrt((x * x) + (y * y));
    double theta = pnc_x::fast_math::Atan2(y, x);
    return std::make_pair(r, theta);
}

Vec2d RotateVector2d(const Vec2d &vec, const double &theta) {
    const auto angle = math::Angle16::FromRad(theta);
    const double cos_angle = math::cos(angle);
    const double sin_angle = math::sin(angle);
    return Vec2d((cos_angle * vec.x()) - (sin_angle * vec.y()),
                 (sin_angle * vec.x()) + (cos_angle * vec.y()));
}

TurnType GetTurnTypeByHeading(const double &entry_heading,
                              const double &exit_heading) {
    double diff = math::AngleDiff(exit_heading, entry_heading);
    if (std::fabs(diff) < M_PI / 6.0) {
        return TurnType::NO_TURN;
    } else if (std::fabs(math::AngleDiff(diff, M_PI)) < M_PI / 6.0) {
        return TurnType::U_TURN;
    } else if (diff > 0.0) {
        return TurnType::LEFT_TURN;
    } else {
        return TurnType::RIGHT_TURN;
    }
}

double Sigmoid(const double x) { return 1.0 / (1.0 + std::exp(-x)); }

std::pair<double, double> RFUToFLU(const double x, const double y) {
    return std::make_pair(y, -x);
}

std::pair<double, double> FLUToRFU(const double x, const double y) {
    return std::make_pair(-y, x);
}

void L2Norm(int feat_dim, float *feat_data) {
    if (feat_dim == 0) {
        return;
    }

    float l2norm = 0.0F;
    for (int i = 0; i < feat_dim; ++i) {
        l2norm += feat_data[i] * feat_data[i];
    }
    if (l2norm == 0) {
        float val = 1.F / std::sqrt(static_cast<float>(feat_dim));
        for (int i = 0; i < feat_dim; ++i) {
            feat_data[i] = val;
        }
    } else {
        l2norm = std::sqrt(l2norm);
        for (int i = 0; i < feat_dim; ++i) {
            feat_data[i] /= l2norm;
        }
    }
}

template <typename T>
T interp1_dec(std::vector<T> &X, std::vector<T> &Y, T xp) {
    T temp1 = 0;
    uint16_t i;

    if (X.size() != Y.size()) {
        return 0;
    }

    if (xp >= X.front()) {
        temp1 = Y.front();
    } else if (xp <= X.back()) {
        temp1 = Y.back();
    } else {
        for (i = 0; i < X.size() - 1; ++i) {
            if (xp < X.at(i) && xp >= X.at(i + 1)) {
                break;
            }
        }
        if (i == X.size() - 1) {
            i = i - 1;
        }
        temp1 = Y.at(i) + (Y.at(i + 1) - Y.at(i)) / (X.at(i + 1) - X.at(i)) *
                              (xp - X.at(i));
    }
    return temp1;
}

template <typename T>
T RateLmt(T CurrentValue, const T &LastValue, T &MinLmt, T &MaxLmt) {
    if (MinLmt > MaxLmt) {
        std::swap(MinLmt, MaxLmt);
    }

    if ((CurrentValue - LastValue) > MaxLmt) {
        CurrentValue = LastValue + MaxLmt;
    } else if ((CurrentValue - LastValue) < MinLmt) {
        CurrentValue = LastValue + MinLmt;
    }
    return CurrentValue;
}

template <typename T>
T Cubic(const T value) {
    return value * value * value;
}

template <typename T>
T interp2_inc(std::vector<T> &X,
              std::vector<T> &Y,
              std::vector<std::vector<T>> &Z,
              T xp,
              T yp) {
    std::vector<T> temp_z_line;
    std::vector<T> temp_y_line = Z.front();
    uint16_t size_x = X.size();
    uint16_t size_y = Y.size();
    if (size_y != Z.size()) {
        return 0;
    }

    for (uint16_t iy = 0; iy < size_y; iy++) {
        temp_y_line = Z[iy];
        if (size_x != temp_y_line.size()) {
            return 0;
        }
        temp_z_line.push_back(interp1_inc(X, temp_y_line, xp));
    }
    return interp1_inc(Y, temp_z_line, yp);
}

template <typename T>
T SafeDivide(const T &divisor, T dividend) {
    const T eps = std::numeric_limits<T>::epsilon();
    if (std::abs(dividend) < eps) {
        dividend = eps;
    }
    return dividend == static_cast<T>(0) ? std::numeric_limits<T>::max()
                                         : divisor / dividend;
}

}  // namespace math
}  // namespace planning
}  // namespace ads_x
