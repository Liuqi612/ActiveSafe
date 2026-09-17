

#pragma once

#include <Eigen/Core>
#include <stdexcept>

#include "path_planner/src/math/geometry/LBFGSpp/Param.h"

namespace LBFGSpp {

template <typename Scalar>
class LineSearchMoreThuente {
 private:
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;

    static Scalar quadratic_interp(const Scalar &a,
                                   const Scalar &b,
                                   const Scalar &fa,
                                   const Scalar &ga,
                                   const Scalar &fb) {
        const Scalar ba = b - a;
        return a + Scalar(0.5) * ba * ba * ga / (fa - fb + ba * ga);
    }

    static Scalar quadratic_interp(const Scalar &a,
                                   const Scalar &b,
                                   const Scalar &ga,
                                   const Scalar &gb) {
        return b + (b - a) * gb / (ga - gb);
    }

    static Scalar cubic_interp(const Scalar &a,
                               const Scalar &b,
                               const Scalar &fa,
                               const Scalar &fb,
                               const Scalar &ga,
                               const Scalar &gb) {
        using std::abs;
        using std::sqrt;

        if (a == b) return a;

        const Scalar ba = b - a;
        const Scalar ba2 = ba * ba;
        const Scalar ba3 = ba2 * ba;
        const Scalar fba = fb - fa;
        const Scalar z = (ga + gb) * ba - Scalar(2) * fba;
        const Scalar w = fba * ba - ga * ba2;

        const Scalar endmin = (fa < fb) ? a : b;
        if (abs(z) < std::numeric_limits<Scalar>::epsilon()) {
            const Scalar c2 = fba / ba2 - ga / ba;
            const Scalar c1 = fba / ba - (a + b) * c2;

            const Scalar globmin = -c1 / (Scalar(2) * c2);

            return (c2 > Scalar(0) && globmin >= a && globmin <= b) ? globmin
                                                                    : endmin;
        }

        const Scalar v =
            (-Scalar(2) * a * w + ga * ba3 + a * (a + Scalar(2) * b) * z) /
            (w - (Scalar(2) * a + b) * z);

        const Scalar u = (w / z - (Scalar(2) * a + b)) / Scalar(3);

        if (v / u >= Scalar(1)) return endmin;

        const Scalar vu = Scalar(1) + sqrt(Scalar(1) - v / u);
        const Scalar sol1 = -u * vu;
        const Scalar sol2 = -v / vu;
        if ((sol1 - a) * (sol1 - b) >= Scalar(0) &&
            (sol2 - a) * (sol2 - b) >= Scalar(0))
            return endmin;

        const Scalar c3 = z / ba3;
        const Scalar c2 = Scalar(3) * c3 * u;
        const Scalar qpp1 = Scalar(2) * c2 + Scalar(6) * c3 * sol1;
        const Scalar sol = (qpp1 > Scalar(0)) ? sol1 : sol2;

        if ((sol - a) * (sol - b) >= Scalar(0)) return endmin;

        const Scalar c1 = v * c2;
        const Scalar fsol = fa + c1 * (sol - a) + c2 * (sol * sol - a * a) +
                            c3 * (sol * sol * sol - a * a * a);
        return (fsol < std::min(fa, fb)) ? sol : endmin;
    }

    static Scalar step_selection(const Scalar &al,
                                 const Scalar &au,
                                 const Scalar &at,
                                 const Scalar &fl,
                                 const Scalar &fu,
                                 const Scalar &ft,
                                 const Scalar &gl,
                                 const Scalar &gu,
                                 const Scalar &gt) {
        if (al == au) return al;

        const Scalar ac = cubic_interp(al, at, fl, ft, gl, gt);
        const Scalar aq = quadratic_interp(al, at, fl, gl, ft);

        if (ft > fl)
            return (std::abs(ac - al) < std::abs(aq - al))
                       ? ac
                       : ((aq + ac) / Scalar(2));

        const Scalar as = quadratic_interp(al, at, gl, gt);

        if (gt * gl < Scalar(0))
            return (std::abs(ac - at) >= std::abs(as - at)) ? ac : as;

        const Scalar delta = Scalar(0.66);
        if (std::abs(gt) < std::abs(gl)) {
            const Scalar res =
                (std::abs(ac - at) < std::abs(as - at)) ? ac : as;
            return (at > al) ? std::min(at + delta * (au - at), res)
                             : std::max(at + delta * (au - at), res);
        }

        const Scalar ae = cubic_interp(at, au, ft, fu, gt, gu);

        return (at > al) ? std::min(at + delta * (au - at), ae)
                         : std::max(at + delta * (au - at), ae);
    }

 public:
    template <typename Foo>
    static void LineSearch(Foo &f,
                           Scalar &fx,
                           Vector &x,
                           Vector &grad,
                           Scalar &step,
                           const Scalar &step_max,
                           const Vector &drt,
                           const Vector &xp,
                           const LBFGSBParam<Scalar> &param) {
        if (step <= Scalar(0))
            throw std::invalid_argument("'step' must be positive");
        if (step > step_max)
            throw std::invalid_argument("'step' exceeds 'step_max'");

        const Scalar fx_init = fx;

        const Scalar dg_init = grad.dot(drt);

        if (dg_init >= 0)
            throw std::logic_error(
                "the moving direction does not decrease the objective function "
                "value");

        const Scalar test_decr = param.ftol * dg_init;

        const Scalar test_curv = -param.wolfe * dg_init;

        Scalar I_lo = Scalar(0), I_hi = std::numeric_limits<Scalar>::infinity();
        Scalar fI_lo = Scalar(0),
               fI_hi = std::numeric_limits<Scalar>::infinity();
        Scalar gI_lo = (Scalar(1) - param.ftol) * dg_init,
               gI_hi = std::numeric_limits<Scalar>::infinity();

        x.noalias() = xp + step * drt;
        fx = f(x, grad);
        Scalar dg = grad.dot(drt);

        if (fx <= fx_init + step * test_decr && std::abs(dg) <= test_curv) {
            return;
        }

        const Scalar delta = Scalar(1.1);
        int iter;
        for (iter = 0; iter < param.max_linesearch; iter++) {
            const Scalar ft = fx - fx_init - step * test_decr;
            const Scalar gt = dg - param.ftol * dg_init;

            Scalar new_step;
            if (ft > fI_lo) {
                new_step = step_selection(I_lo, I_hi, step, fI_lo, fI_hi, ft,
                                          gI_lo, gI_hi, gt);
                I_hi = step;
                fI_hi = ft;
                gI_hi = gt;

            } else if (gt * (fI_lo - step) > Scalar(0)) {
                new_step = std::min(step_max, step + delta * (step - I_lo));

                I_lo = step;
                fI_lo = ft;
                gI_lo = gt;

            } else {
                new_step = step_selection(I_lo, I_hi, step, fI_lo, fI_hi, ft,
                                          gI_lo, gI_hi, gt);
                I_hi = I_lo;
                fI_hi = fI_lo;
                gI_hi = gI_lo;

                I_lo = step;
                fI_lo = ft;
                gI_lo = gt;
            }

            if (step == step_max && new_step >= step_max) {
                return;
            }

            step = new_step;

            if (step < param.min_step)
                throw std::runtime_error(
                    "the line search step became smaller than the minimum "
                    "value "
                    "allowed");

            if (step > param.max_step)
                throw std::runtime_error(
                    "the line search step became larger than the maximum value "
                    "allowed");

            x.noalias() = xp + step * drt;
            fx = f(x, grad);
            dg = grad.dot(drt);

            if (fx <= fx_init + step * test_decr && std::abs(dg) <= test_curv) {
                return;
            }
            if (step >= step_max) {
                return;
            }
        }

        if (iter >= param.max_linesearch)
            throw std::runtime_error(
                "the line search routine reached the maximum number of "
                "iterations");
    }
};

}  // namespace LBFGSpp
