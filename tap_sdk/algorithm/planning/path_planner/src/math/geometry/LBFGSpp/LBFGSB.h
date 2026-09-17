

#pragma once

#include <Eigen/Core>
#include <stdexcept>
#include <vector>

#include "path_planner/src/math/geometry/LBFGSpp/BFGSMat.h"
#include "path_planner/src/math/geometry/LBFGSpp/Cauchy.h"
#include "path_planner/src/math/geometry/LBFGSpp/LineSearchMoreThuente.h"
#include "path_planner/src/math/geometry/LBFGSpp/Param.h"
#include "path_planner/src/math/geometry/LBFGSpp/SubspaceMin.h"

namespace LBFGSpp {

template <typename Scalar,
          template <class> class LineSearch = LineSearchMoreThuente>
class LBFGSBSolver {
 private:
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> Matrix;
    typedef Eigen::Map<Vector> MapVec;
    typedef std::vector<int> IndexSet;

    const LBFGSBParam<Scalar> &m_param;
    BFGSMat<Scalar, true> m_bfgs;
    Vector m_fx;
    Vector m_xp;
    Vector m_grad;
    Vector m_gradp;
    Vector m_drt;

    inline void reset(int n) {
        const int m = m_param.m;
        m_bfgs.reset(n, m);
        m_xp.resize(n);
        m_grad.resize(n);
        m_gradp.resize(n);
        m_drt.resize(n);
        if (m_param.past > 0) m_fx.resize(m_param.past);
    }

    static void force_bounds(Vector &x, const Vector &lb, const Vector &ub) {
        x.noalias() = x.cwiseMax(lb).cwiseMin(ub);
    }

    static Scalar proj_grad_norm(const Vector &x,
                                 const Vector &g,
                                 const Vector &lb,
                                 const Vector &ub) {
        return ((x - g).cwiseMax(lb).cwiseMin(ub) - x).cwiseAbs().maxCoeff();
    }

    static Scalar max_step_size(const Vector &x0,
                                const Vector &drt,
                                const Vector &lb,
                                const Vector &ub) {
        const int n = x0.size();
        Scalar step = std::numeric_limits<Scalar>::infinity();

        for (int i = 0; i < n; i++) {
            if (drt[i] > Scalar(0)) {
                step = std::min(step, (ub[i] - x0[i]) / drt[i]);
            } else if (drt[i] < Scalar(0)) {
                step = std::min(step, (lb[i] - x0[i]) / drt[i]);
            }
        }

        return step;
    }

 public:
    LBFGSBSolver(const LBFGSBParam<Scalar> &param) : m_param(param) {
        m_param.check_param();
    }

    template <typename Foo>
    inline int minimize(
        Foo &f, Vector &x, Scalar &fx, const Vector &lb, const Vector &ub) {
        using std::abs;

        const int n = x.size();
        if (lb.size() != n || ub.size() != n)
            throw std::invalid_argument(
                "'lb' and 'ub' must have the same size as 'x'");

        force_bounds(x, lb, ub);

        reset(n);

        const int fpast = m_param.past;

        fx = f(x, m_grad);
        Scalar projgnorm = proj_grad_norm(x, m_grad, lb, ub);
        if (fpast > 0) m_fx[0] = fx;

        if (projgnorm <= m_param.epsilon ||
            projgnorm <= m_param.epsilon_rel * x.norm()) {
            return 1;
        }

        Vector xcp(n), vecc;
        IndexSet newact_set, fv_set;
        Cauchy<Scalar>::get_cauchy_point(m_bfgs, x, m_grad, lb, ub, xcp, vecc,
                                         newact_set, fv_set);

        m_drt.noalias() = xcp - x;
        m_drt.normalize();

        const Scalar eps = std::numeric_limits<Scalar>::epsilon();

        Vector vecs(n), vecy(n);

        int k = 1;
        for (;;) {
            m_xp.noalias() = x;
            m_gradp.noalias() = m_grad;

            Scalar step_max = max_step_size(x, m_drt, lb, ub);
            step_max = std::min(m_param.max_step, step_max);
            Scalar step = Scalar(1);
            step = std::min(step, step_max);
            LineSearch<Scalar>::LineSearch(f, fx, x, m_grad, step, step_max,
                                           m_drt, m_xp, m_param);

            projgnorm = proj_grad_norm(x, m_grad, lb, ub);

            if (projgnorm <= m_param.epsilon ||
                projgnorm <= m_param.epsilon_rel * x.norm()) {
                return k;
            }

            if (fpast > 0) {
                const Scalar fxd = m_fx[k % fpast];
                if (k >= fpast &&
                    abs(fxd - fx) <=
                        m_param.delta *
                            std::max(std::max(abs(fx), abs(fxd)), Scalar(1)))
                    return k;

                m_fx[k % fpast] = fx;
            }

            if (m_param.max_iterations != 0 && k >= m_param.max_iterations) {
                return k;
            }

            vecs.noalias() = x - m_xp;
            vecy.noalias() = m_grad - m_gradp;
            if (vecs.dot(vecy) > eps * vecy.squaredNorm())
                m_bfgs.add_correction(vecs, vecy);

            force_bounds(x, lb, ub);
            Cauchy<Scalar>::get_cauchy_point(m_bfgs, x, m_grad, lb, ub, xcp,
                                             vecc, newact_set, fv_set);

            SubspaceMin<Scalar>::subspace_minimize(m_bfgs, x, xcp, m_grad, lb,
                                                   ub, vecc, newact_set, fv_set,
                                                   m_param.max_submin, m_drt);

            k++;
        }

        return k;
    }
};

}  // namespace LBFGSpp
