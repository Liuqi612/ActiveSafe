
#pragma once

#include <vector>

#include "path_planner/src/common/log.h"

namespace pnc_x {

class CubicSpline {
 public:
    enum class BoundaryType { FOD = 0, SOD = 1 };
    struct BoundaryCondition {
        BoundaryType type = BoundaryType::SOD;
        double value = 0.0;
    };

    CubicSpline(std::vector<double> x, std::vector<double> y);

    CubicSpline(std::vector<double> x,
                std::vector<double> y,
                BoundaryCondition left,
                BoundaryCondition right);

    double Evaluate(double x) const;

    template <int Order>
    typename std::enable_if<(Order > 0), double>::type EvaluateDerivative(
        double x_val) const {
        // C++14: no if constexpr, use normal if and template specializations
        if (Order > 3) {
            return 0.0;
        }
        const int n = static_cast<int>(x_.size());
        double value = 0.0;
        if (x_val < x_[0]) {
            const double h = x_val - x_[0];
            if (Order == 1) {
                value = (2.0 * c0_ * h) + b_[0];
            } else if (Order == 2) {
                value = 2.0 * c0_;
            } else {
                value = 0.0;
            }
        } else if (x_val > x_[n - 1]) {
            const double h = x_val - x_[n - 1];
            if (Order == 1) {
                value = (2.0 * c_[n - 1] * h) + b_[n - 1];
            } else if (Order == 2) {
                value = 2.0 * c_[n - 1];
            } else {
                value = 0.0;
            }
        } else {
            const int idx = FindNearestIndex(x_val);
            const double h = x_val - x_[idx];
            if (Order == 1) {
                value = (((3.0 * d_[idx] * h) + (2.0 * c_[idx])) * h) + b_[idx];
            } else if (Order == 2) {
                value = (6.0 * d_[idx] * h) + (2.0 * c_[idx]);
            } else if (Order == 3) {
                value = 6.0 * d_[idx];
            } else {
                value = 0.0;
            }
        }
        return value;
    }

    const std::vector<double> &x() const;
    const std::vector<double> &y() const;

 protected:
    int FindNearestIndex(double x) const;

    void CheckInput(const std::vector<double> &x, const std::vector<double> &y);

    void Solve();

    std::vector<double> x_;
    std::vector<double> y_;

    std::vector<double> b_;
    std::vector<double> c_;
    std::vector<double> d_;

    double c0_ = 0.0;
    BoundaryCondition left_;
    BoundaryCondition right_;
};

}  // namespace pnc_x
