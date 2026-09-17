

#pragma once

#include <Eigen/Core>
#include <stdexcept>

namespace LBFGSpp {

template <typename Scalar>
class LineSearchBracketing {
 private:
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;

 public:
    template <typename Foo>
    static void LineSearch(Foo &f,
                           Scalar &fx,
                           Vector &x,
                           Vector &grad,
                           Scalar &step,
                           const Vector &drt,
                           const Vector &xp,
                           const LBFGSParam<Scalar> &param) {
        if (step <= Scalar(0))
            throw std::invalid_argument("'step' must be positive");

        const Scalar fx_init = fx;

        const Scalar dg_init = grad.dot(drt);

        if (dg_init > 0)
            throw std::logic_error(
                "the moving direction increases the objective function value");

        const Scalar test_decr = param.ftol * dg_init;

        Scalar step_lo = 0, step_hi = std::numeric_limits<Scalar>::infinity();

        int iter;
        for (iter = 0; iter < param.max_linesearch; iter++) {
            x.noalias() = xp + step * drt;

            fx = f(x, grad);

            if (fx > fx_init + step * test_decr || (fx != fx)) {
                step_hi = step;
            } else {
                if (param.linesearch == LBFGS_LINESEARCH_BACKTRACKING_ARMIJO)
                    break;

                const Scalar dg = grad.dot(drt);
                if (dg < param.wolfe * dg_init) {
                    step_lo = step;
                } else {
                    if (param.linesearch == LBFGS_LINESEARCH_BACKTRACKING_WOLFE)
                        break;

                    if (dg > -param.wolfe * dg_init) {
                        step_hi = step;
                    } else {
                        break;
                    }
                }
            }

            assert(step_lo < step_hi);

            if (step < param.min_step)
                throw std::runtime_error(
                    "the line search step became smaller than the "
                    "minimum value allowed");

            if (step > param.max_step)
                throw std::runtime_error(
                    "the line search step became larger than the "
                    "maximum value allowed");

            step = std::isinf(step_hi) ? 2 * step : step_lo / 2 + step_hi / 2;
        }

        if (iter >= param.max_linesearch)
            throw std::runtime_error(
                "the line search routine reached the maximum number of "
                "iterations");
    }
};

}  // namespace LBFGSpp
