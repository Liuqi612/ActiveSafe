

#pragma once

#include <Eigen/Core>

#include "path_planner/src/math/geometry/LBFGSpp/BFGSMat.h"
#include "path_planner/src/math/geometry/LBFGSpp/Param.h"
#include "path_planner/src/math/geometry/LBFGSpp/LineSearchBacktracking.h"
#include "path_planner/src/math/geometry/LBFGSpp/LineSearchBracketing.h"
#include "path_planner/src/math/geometry/LBFGSpp/LineSearchNocedalWright.h"

namespace LBFGSpp {

template <typename Scalar,
          template <class> class LineSearch = LineSearchBacktracking>
class LBFGSSolver {
 private:
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> Matrix;
    typedef Eigen::Map<Vector> MapVec;

    const LBFGSParam<Scalar> &m_param;
    BFGSMat<Scalar> m_bfgs;
    Vector m_fx;
    Vector m_xp;
    Vector m_grad;
    Vector m_gradp;
    Vector m_drt;

    inline void reset(Eigen::Index n) {
        const int m = m_param.m;
        m_bfgs.reset(static_cast<int>(n), m);
        m_xp.resize(n);
        m_grad.resize(n);
        m_gradp.resize(n);
        m_drt.resize(n);
        if (m_param.past > 0) { m_fx.resize(m_param.past); }
    }

 public:
    LBFGSSolver(const LBFGSParam<Scalar> &param) : m_param(param) {
        m_param.check_param();
    }

    template <typename Foo>
    inline int minimize(Foo &f, Vector &x, Scalar &fx) {
        using std::abs;

        const Eigen::Index n = x.size();
        reset(n);

        const int fpast = m_param.past;

        fx = f(x, m_grad);
        Scalar gnorm = m_grad.norm();
        if (fpast > 0) { m_fx[0] = fx; }

        if ((gnorm <= m_param.epsilon) ||
            (gnorm <= m_param.epsilon_rel * x.norm())) {
            return 1;
        }

        m_drt.noalias() = -m_grad;

        Scalar step = Scalar(1) / m_drt.norm();

        int k = 1;
        for (;;) {
            m_xp.noalias() = x;
            m_gradp.noalias() = m_grad;

            LineSearch<Scalar>::LineSearch(f, fx, x, m_grad, step, m_drt, m_xp,
                                           m_param);

            gnorm = m_grad.norm();

            if ((gnorm <= m_param.epsilon) ||
                (gnorm <= m_param.epsilon_rel * x.norm())) {
                return k;
            }

            if (fpast > 0) {
                const Scalar fxd = m_fx[k % fpast];
                if ((k >= fpast) &&
                    (abs(fxd - fx) <=
                        m_param.delta *
                            std::max(std::max(abs(fx), abs(fxd)), Scalar(1)))) {
                    return k;
                }

                m_fx[k % fpast] = fx;
            }

            if ((m_param.max_iterations != 0) && (k >= m_param.max_iterations)) {
                return k;
            }

            m_bfgs.add_correction(x - m_xp, m_grad - m_gradp);

            m_bfgs.apply_Hv(m_grad, -Scalar(1), m_drt);

            step = Scalar(1);
            k++;
        }

        return k;
    }
};

}  // namespace LBFGSpp
