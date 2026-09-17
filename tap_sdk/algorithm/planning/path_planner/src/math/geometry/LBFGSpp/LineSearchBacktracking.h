

#pragma once

#include <Eigen/Core>
#include <stdexcept>

namespace LBFGSpp {

template <typename Scalar>
class LineSearchBacktracking {
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
        const Scalar dec = 0.5;
        const Scalar inc = 2.1;

        if (step <= static_cast<Scalar>(0)) {
            throw std::invalid_argument("'step' must be positive");
        }

        const Scalar fx_init = fx;

        const Scalar dg_init = grad.dot(drt);

        if (dg_init > 0) {
            throw std::logic_error(
                "the moving direction increases the objective function value");
        }

        const Scalar test_decr = param.ftol * dg_init;
        Scalar width;

        int iter;
        for (iter = 0; iter < param.max_linesearch; iter++) {
            x.noalias() = xp + step * drt;

            fx = f(x, grad);

            if ((fx > fx_init + (step * test_decr)) || (fx != fx)) {
                width = dec;
            } else {
                if (param.linesearch == LBFGS_LINESEARCH_BACKTRACKING_ARMIJO) {
                    break;
                }

                const Scalar dg = grad.dot(drt);
                if (dg < param.wolfe * dg_init) {
                    width = inc;
                } else {
                    if (param.linesearch == LBFGS_LINESEARCH_BACKTRACKING_WOLFE) {
                        break;
                    }

                    if (dg > -param.wolfe * dg_init) {
                        width = dec;
                    } else {
                        break;
                    }
                }
            }

            if (step < param.min_step) {
                throw std::runtime_error(
                    "the line search step became smaller than the "
                    "minimum value allowed");
            }

            if (step > param.max_step) {
                throw std::runtime_error(
                    "the line search step became larger than the "
                    "maximum value allowed");
            }

            step *= width;
        }

        if (iter >= param.max_linesearch) {
            throw std::runtime_error(
                "the line search routine reached the maximum number of "
                "iterations");
        }
    }
};

}  // namespace LBFGSpp
