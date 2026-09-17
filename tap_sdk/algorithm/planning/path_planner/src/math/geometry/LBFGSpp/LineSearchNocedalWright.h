

#pragma once

#include <Eigen/Core>
#include <stdexcept>

namespace LBFGSpp {

template <typename Scalar>
class LineSearchNocedalWright {
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

        if (param.linesearch != LBFGS_LINESEARCH_BACKTRACKING_STRONG_WOLFE)
            throw std::invalid_argument(
                "'param.linesearch' must be "
                "'LBFGS_LINESEARCH_BACKTRACKING_STRONG_WOLFE'"
                " for LineSearchNocedalWright");

        const Scalar expansion = Scalar(2);

        const Scalar fx_init = fx;

        const Scalar dg_init = grad.dot(drt);

        if (dg_init > 0)
            throw std::logic_error(
                "the moving direction increases the objective function value");

        const Scalar test_decr = param.ftol * dg_init,
                     test_curv = -param.wolfe * dg_init;

        Scalar step_hi, step_lo = 0, fx_hi, fx_lo = fx_init, dg_hi,
                        dg_lo = dg_init;

        int iter = 0;
        for (;;) {
            x.noalias() = xp + step * drt;
            fx = f(x, grad);

            if (iter++ >= param.max_linesearch) return;

            const Scalar dg = grad.dot(drt);

            if (fx - fx_init > step * test_decr ||
                (0 < step_lo && fx >= fx_lo)) {
                step_hi = step;
                fx_hi = fx;
                dg_hi = dg;
                break;
            }

            if (std::abs(dg) <= test_curv) return;

            step_hi = step_lo;
            fx_hi = fx_lo;
            dg_hi = dg_lo;
            step_lo = step;
            fx_lo = fx;
            dg_lo = dg;

            if (dg >= 0) break;

            step *= expansion;
        }

        for (;;) {
            step = (fx_hi - fx_lo) * step_lo -
                   (step_hi * step_hi - step_lo * step_lo) * dg_lo / 2;
            step /= (fx_hi - fx_lo) - (step_hi - step_lo) * dg_lo;

            if (step <= std::min(step_lo, step_hi) ||
                step >= std::max(step_lo, step_hi))
                step = step_lo / 2 + step_hi / 2;

            x.noalias() = xp + step * drt;
            fx = f(x, grad);

            if (iter++ >= param.max_linesearch) return;

            const Scalar dg = grad.dot(drt);

            if (fx - fx_init > step * test_decr || fx >= fx_lo) {
                if (step == step_hi)
                    throw std::runtime_error(
                        "the line search routine failed, possibly "
                        "due to insufficient numeric precision");

                step_hi = step;
                fx_hi = fx;
                dg_hi = dg;
            } else {
                if (std::abs(dg) <= test_curv) return;

                if (dg * (step_hi - step_lo) >= 0) {
                    step_hi = step_lo;
                    fx_hi = fx_lo;
                    dg_hi = dg_lo;
                }

                if (step == step_lo)
                    throw std::runtime_error(
                        "the line search routine failed, possibly "
                        "due to insufficient numeric precision");

                step_lo = step;
                fx_lo = fx;
                dg_lo = dg;
            }
        }
    }
};

}  // namespace LBFGSpp
