

#include <ostream>
#include <Eigen/Eigen>

#include "path_planner/src/math/cubic_spline.h"
#include "path_planner/src/math/eigen.h"
#include "path_planner/src/math/util.h"

namespace pnc_x {

CubicSpline::CubicSpline(std::vector<double> x, std::vector<double> y)
    : x_(std::move(x)),
      y_(std::move(y)),
      left_({.type = BoundaryType::SOD, .value = 0.0}),
      right_({.type = BoundaryType::SOD, .value = 0.0}) {
    CheckInput(x_, y_);
    Solve();
}

CubicSpline::CubicSpline(std::vector<double> x,
                         std::vector<double> y,
                         BoundaryCondition left,
                         BoundaryCondition right)
    : x_(std::move(x)), y_(std::move(y)), left_(left), right_(right) {
    CheckInput(x_, y_);
    Solve();
}

const std::vector<double> &CubicSpline::x() const { return x_; }
const std::vector<double> &CubicSpline::y() const { return y_; }

int CubicSpline::FindNearestIndex(double x) const {
    const auto it = std::upper_bound(x_.begin(), x_.end(), x);
    const int idx = std::max(static_cast<int>(it - x_.begin() - 1), 0);
    return idx;
}

void CubicSpline::CheckInput(const std::vector<double> &x,
                             const std::vector<double> &y) {
    XCHECK_EQ(x.size(), y.size());
    XCHECK_GT(x.size(), 1);

    for (int i = 0; i < x.size() - 1; ++i) {
        const size_t si = static_cast<size_t>(i);
        XCHECK_LT(x[si], x[si + 1U]);
    }
}

void CubicSpline::Solve() {
    const int n = x_.size();
    SMatXd A(n, n);
    VecXd b(n, 1);
    constexpr double kThreeInv = 1.0 / 3.0;
    for (int i = 1; i < (n - 1); i++) {
        const size_t si = static_cast<size_t>(i);
        A.insert(i, i - 1) = 1.0 * kThreeInv * (x_[si] - x_[si - 1U]);
        A.insert(i, i) =
            2.0 * kThreeInv * (x_[si + 1U] - x_[si - 1U]);
        A.insert(i, i + 1) = 1.0 * kThreeInv * (x_[si + 1U] - x_[si]);
        b(i) = ((y_[si + 1U] - y_[si]) / (x_[si + 1U] - x_[si])) -
               ((y_[si] - y_[si - 1U]) / (x_[si] - x_[si - 1U]));
    }

    if (left_.type == BoundaryType::SOD) {
        A.insert(0, 0) = 2.0;
        A.insert(0, 1) = 0.0;
        b(0) = left_.value;
    } else if (left_.type == BoundaryType::FOD) {
        A.insert(0, 0) = 2.0 * (x_[1] - x_[0]);
        A.insert(0, 1) = 1.0 * (x_[1] - x_[0]);
        b(0) = 3.0 * (((y_[1] - y_[0]) / (x_[1] - x_[0])) - left_.value);
    } else {
        // LOG(FATAL) << "Unknown left boundary type " <<
        // static_cast<int>(left_.type);
    }
    if (right_.type == BoundaryType::SOD) {
        A.insert(n - 1, n - 1) = 2.0;
        A.insert(n - 1, n - 2) = 0.0;
        b(n - 1) = right_.value;
    } else if (right_.type == BoundaryType::FOD) {
        const size_t nm1 = static_cast<size_t>(n - 1);
        const size_t nm2 = static_cast<size_t>(n - 2);
        A.insert(n - 1, n - 1) = 2.0 * (x_[nm1] - x_[nm2]);
        A.insert(n - 1, n - 2) = 1.0 * (x_[nm1] - x_[nm2]);
        b(n - 1) = 3.0 * (right_.value -
                          ((y_[nm1] - y_[nm2]) / (x_[nm1] - x_[nm2])));
    } else {
        // LOG(FATAL) << "Unknown right boundary type "
        //            << static_cast<int>(right_.type);
    }

    A.makeCompressed();
    Eigen::SparseLU<SMatXd> solver;
    solver.analyzePattern(A);
    solver.factorize(A);
    XCHECK(solver.info() == Eigen::Success);

    const auto c = solver.solve(b);
    c_.clear();
    c_.reserve(n);
    for (int i = 0; i < n; ++i) {
        c_.push_back(c(i));
    }

    d_.clear();
    d_.resize(n);
    b_.clear();
    b_.resize(n);
    for (int i = 0; i < (n - 1); ++i) {
        const size_t si = static_cast<size_t>(i);
        d_[si] = 1.0 * kThreeInv * (c_[si + 1U] - c_[si]) / (x_[si + 1U] - x_[si]);
        b_[si] =
            ((y_[si + 1U] - y_[si]) / (x_[si + 1U] - x_[si])) -
            (1.0 * kThreeInv * ((2.0 * c_[si]) + c_[si + 1U]) *
             (x_[si + 1U] - x_[si]));
    }
    const size_t nm1 = static_cast<size_t>(n - 1);
    const size_t nm2 = static_cast<size_t>(n - 2);
    const double h = x_[nm1] - x_[nm2];
    d_[nm1] = 0.0;
    b_[nm1] = (3.0 * d_[nm2] * Sqr(h)) + (2.0 * c_[nm2] * h) + b_[nm2];
    if (right_.type == BoundaryType::FOD) {
        c_[nm1] = 0.0;
    }

    c0_ = (left_.type == BoundaryType::FOD) ? 0.0 : c_[0];
}

double CubicSpline::Evaluate(double x) const {
    const int n = x_.size();
    const size_t nm1 = static_cast<size_t>(n - 1);
    double value;
    if (x < x_[0]) {
        const double h = x - x_[0];
        value = (((c0_ * h) + b_[0]) * h) + y_[0];
    } else if (x > x_[nm1]) {
        const double h = x - x_[nm1];
        value = (((c_[nm1] * h) + b_[nm1]) * h) + y_[nm1];
    } else {
        const int idx = FindNearestIndex(x);
        const size_t sidx = static_cast<size_t>(idx);
        const double h = x - x_[sidx];
        value = (((((d_[sidx] * h) + c_[sidx]) * h) + b_[sidx]) * h) + y_[sidx];
    }

    return value;
}

}  // namespace pnc_x
