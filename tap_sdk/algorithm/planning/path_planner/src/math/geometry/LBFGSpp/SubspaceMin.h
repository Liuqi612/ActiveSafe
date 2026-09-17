

#pragma once

#include <Eigen/Core>
#include <stdexcept>
#include <vector>

#include "path_planner/src/math/geometry/LBFGSpp/BFGSMat.h"

namespace LBFGSpp {

template <typename Scalar>
class SubspaceMin {
 private:
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> Matrix;
    typedef std::vector<int> IndexSet;

    static Vector subvec(const Vector &v, const IndexSet &ind) {
        const int nsub = ind.size();
        Vector res(nsub);
        for (int i = 0; i < nsub; i++) res[i] = v[ind[i]];
        return res;
    }

    static void subvec_assign(Vector &v,
                              const IndexSet &ind,
                              const Vector &rhs) {
        const int nsub = ind.size();
        for (int i = 0; i < nsub; i++) v[ind[i]] = rhs[i];
    }

    static bool in_bounds(const Vector &x, const Vector &lb, const Vector &ub) {
        const int n = x.size();
        for (int i = 0; i < n; i++) {
            if (x[i] < lb[i] || x[i] > ub[i]) return false;
        }
        return true;
    }

    static bool P_converged(const IndexSet &yP_set,
                            const Vector &vecy,
                            const Vector &vecl,
                            const Vector &vecu) {
        const int nP = yP_set.size();
        for (int i = 0; i < nP; i++) {
            const int coord = yP_set[i];
            if (vecy[coord] < vecl[coord] || vecy[coord] > vecu[coord])
                return false;
        }
        return true;
    }

    static bool L_converged(const IndexSet &yL_set, const Vector &lambda) {
        const int nL = yL_set.size();
        for (int i = 0; i < nL; i++) {
            const int coord = yL_set[i];
            if (lambda[coord] < Scalar(0)) return false;
        }
        return true;
    }

    static bool U_converged(const IndexSet &yU_set, const Vector &mu) {
        const int nU = yU_set.size();
        for (int i = 0; i < nU; i++) {
            const int coord = yU_set[i];
            if (mu[coord] < Scalar(0)) return false;
        }
        return true;
    }

 public:
    static void subspace_minimize(const BFGSMat<Scalar, true> &bfgs,
                                  const Vector &x0,
                                  const Vector &xcp,
                                  const Vector &g,
                                  const Vector &lb,
                                  const Vector &ub,
                                  const Vector &Wd,
                                  const IndexSet &newact_set,
                                  const IndexSet &fv_set,
                                  int maxit,
                                  Vector &drt) {
        drt.noalias() = xcp - x0;

        const int nfree = fv_set.size();

        if (nfree < 1) {
            return;
        }

        Matrix WF = bfgs.Wb(fv_set);

        Vector vecc(nfree);
        bfgs.compute_FtBAb(WF, fv_set, newact_set, Wd, drt, vecc);

        Vector vecl(nfree), vecu(nfree);
        for (int i = 0; i < nfree; i++) {
            const int coord = fv_set[i];
            vecl[i] = lb[coord] - x0[coord];
            vecu[i] = ub[coord] - x0[coord];
            vecc[i] += g[coord];
        }

        Vector vecy(nfree);
        bfgs.solve_PtBP(WF, -vecc, vecy);

        if (in_bounds(vecy, vecl, vecu)) {
            subvec_assign(drt, fv_set, vecy);
            return;
        }

        Vector yfallback = vecy;

        Vector lambda = Vector::Zero(nfree), mu = Vector::Zero(nfree);

        IndexSet L_set, U_set, P_set, yL_set, yU_set, yP_set;
        L_set.reserve(nfree / 3);
        yL_set.reserve(nfree / 3);
        U_set.reserve(nfree / 3);
        yU_set.reserve(nfree / 3);
        P_set.reserve(nfree);
        yP_set.reserve(nfree);
        int k;
        for (k = 0; k < maxit; k++) {
            L_set.clear();
            U_set.clear();
            P_set.clear();

            yL_set.clear();
            yU_set.clear();
            yP_set.clear();
            for (int i = 0; i < nfree; i++) {
                const int coord = fv_set[i];
                const Scalar li = vecl[i], ui = vecu[i];
                if ((vecy[i] < li) ||
                    (vecy[i] == li && lambda[i] >= Scalar(0))) {
                    L_set.push_back(coord);
                    yL_set.push_back(i);
                    vecy[i] = li;
                    mu[i] = Scalar(0);
                } else if ((vecy[i] > ui) ||
                           (vecy[i] == ui && mu[i] >= Scalar(0))) {
                    U_set.push_back(coord);
                    yU_set.push_back(i);
                    vecy[i] = ui;
                    lambda[i] = Scalar(0);
                } else {
                    P_set.push_back(coord);
                    yP_set.push_back(i);
                    lambda[i] = Scalar(0);
                    mu[i] = Scalar(0);
                }
            }

            Matrix WP = bfgs.Wb(P_set);

            const int nP = P_set.size();
            if (nP > 0) {
                Vector rhs = subvec(vecc, yP_set);
                Vector lL = subvec(vecl, yL_set);
                Vector uU = subvec(vecu, yU_set);
                Vector tmp(nP);
                bool nonzero = bfgs.apply_PtBQv(WP, L_set, lL, tmp, true);
                if (nonzero) rhs.noalias() += tmp;
                nonzero = bfgs.apply_PtBQv(WP, U_set, uU, tmp, true);
                if (nonzero) rhs.noalias() += tmp;

                bfgs.solve_PtBP(WP, -rhs, tmp);
                subvec_assign(vecy, yP_set, tmp);
            }

            const int nL = L_set.size();
            const int nU = U_set.size();
            Vector Fy;
            if (nL > 0 || nU > 0) bfgs.apply_WtPv(fv_set, vecy, Fy);
            if (nL > 0) {
                Vector res;
                bfgs.apply_PtWMv(L_set, Fy, res, Scalar(-1));
                res.noalias() += subvec(vecc, yL_set);
                subvec_assign(lambda, yL_set, res);
            }

            if (nU > 0) {
                Vector res;
                bfgs.apply_PtWMv(U_set, Fy, res, Scalar(-1));
                res.noalias() = -res - subvec(vecc, yU_set);
                subvec_assign(mu, yU_set, res);
            }

            if (L_converged(yL_set, lambda) && U_converged(yU_set, mu) &&
                P_converged(yP_set, vecy, vecl, vecu))
                break;
        }

        if (k >= maxit) {
            vecy.noalias() = vecy.cwiseMax(vecl).cwiseMin(vecu);
            subvec_assign(drt, fv_set, vecy);

            Scalar dg = drt.dot(g);

            if (dg <= -std::numeric_limits<Scalar>::epsilon()) return;

            vecy.noalias() = yfallback.cwiseMax(vecl).cwiseMin(vecu);
            subvec_assign(drt, fv_set, vecy);
            dg = drt.dot(g);
            if (dg <= -std::numeric_limits<Scalar>::epsilon()) return;

            subvec_assign(drt, fv_set, yfallback);
            return;
        }

        subvec_assign(drt, fv_set, vecy);
    }
};

}  // namespace LBFGSpp
