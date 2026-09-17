

#pragma once

#include <Eigen/Core>
#include <vector>

#include "math/geometry/LBFGSpp/BFGSMat.h"

namespace LBFGSpp {

template <typename Scalar>
class ArgSort {
 private:
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;
    typedef std::vector<int> IndexSet;

    const Scalar *values;

 public:
    ArgSort(const Vector &value_vec) : values(value_vec.data()) {}

    inline bool operator()(int key1, int key2) {
        return values[key1] < values[key2];
    }
    inline void sort_key(IndexSet &key_vec) const {
        std::sort(key_vec.begin(), key_vec.end(), *this);
    }
};

template <typename Scalar>
class Cauchy {
 private:
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;
    typedef Eigen::Matrix<int, Eigen::Dynamic, 1> IntVector;
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> Matrix;
    typedef std::vector<int> IndexSet;

    static int search_greater(const Vector &brk,
                              const IndexSet &ord,
                              const Scalar &t,
                              int start = 0) {
        const int nord = ord.size();
        int i;
        for (i = start; i < nord; i++) {
            if (brk[ord[i]] > t) break;
        }

        return i;
    }

 public:
    static void get_cauchy_point(const BFGSMat<Scalar, true> &bfgs,
                                 const Vector &x0,
                                 const Vector &g,
                                 const Vector &lb,
                                 const Vector &ub,
                                 Vector &xcp,
                                 Vector &vecc,
                                 IndexSet &newact_set,
                                 IndexSet &fv_set) {
        const int n = x0.size();
        xcp.resize(n);
        xcp.noalias() = x0;
        vecc.resize(2 * bfgs.num_corrections());
        vecc.setZero();
        newact_set.clear();
        newact_set.reserve(n);
        fv_set.clear();
        fv_set.reserve(n);

        Vector brk(n), vecd(n);

        IndexSet ord;
        ord.reserve(n);
        const Scalar inf = std::numeric_limits<Scalar>::infinity();
        for (int i = 0; i < n; i++) {
            if (lb[i] == ub[i])
                brk[i] = Scalar(0);
            else if (g[i] < Scalar(0))
                brk[i] = (x0[i] - ub[i]) / g[i];
            else if (g[i] > Scalar(0))
                brk[i] = (x0[i] - lb[i]) / g[i];
            else
                brk[i] = inf;

            const bool iszero = (brk[i] == Scalar(0));
            vecd[i] = iszero ? Scalar(0) : -g[i];

            if (brk[i] == inf)
                fv_set.push_back(i);
            else if (!iszero)
                ord.push_back(i);
        }

        ArgSort<Scalar> sorting(brk);
        sorting.sort_key(ord);

        const int nord = ord.size();
        const int nfree = fv_set.size();
        if ((nfree < 1) && (nord < 1)) {
            return;
        }

        Vector vecp;
        bfgs.apply_Wtv(vecd, vecp);

        Scalar fp = -vecd.squaredNorm();

        Vector cache;
        bfgs.apply_Mv(vecp, cache);
        Scalar fpp = -bfgs.theta() * fp - vecp.dot(cache);

        Scalar deltatmin = -fp / fpp;

        Scalar il = Scalar(0);

        int b = 0;
        Scalar iu = (nord < 1) ? inf : brk[ord[b]];
        Scalar deltat = iu - il;

        bool crossed_all = false;
        const int ncorr = bfgs.num_corrections();
        Vector wact(2 * ncorr);
        while (deltatmin >= deltat) {
            vecc.noalias() += deltat * vecp;

            const int act_begin = b;
            const int act_end = search_greater(brk, ord, iu, b) - 1;

            if ((nfree == 0) && (act_end == nord - 1)) {
                for (int i = act_begin; i <= act_end; i++) {
                    const int act = ord[i];
                    xcp[act] = (vecd[act] > Scalar(0)) ? ub[act] : lb[act];
                    newact_set.push_back(act);
                }

                crossed_all = true;
                break;
            }

            fp += deltat * fpp;
            for (int i = act_begin; i <= act_end; i++) {
                const int act = ord[i];
                xcp[act] = (vecd[act] > Scalar(0)) ? ub[act] : lb[act];

                const Scalar zact = xcp[act] - x0[act];
                const Scalar gact = g[act];
                const Scalar ggact = gact * gact;
                wact.noalias() = bfgs.Wb(act);
                bfgs.apply_Mv(wact, cache);
                fp +=
                    ggact + bfgs.theta() * gact * zact - gact * cache.dot(vecc);
                fpp -= (bfgs.theta() * ggact + 2 * gact * cache.dot(vecp) +
                        ggact * cache.dot(wact));
                vecp.noalias() += gact * wact;
                vecd[act] = Scalar(0);
                newact_set.push_back(act);
            }

            deltatmin = -fp / fpp;

            il = iu;
            b = act_end + 1;

            if (b >= nord) break;
            iu = brk[ord[b]];

            deltat = iu - il;
        }

        const Scalar eps = std::numeric_limits<Scalar>::epsilon();
        if (fpp < eps) deltatmin = -fp / eps;

        if (!crossed_all) {
            deltatmin = std::max(deltatmin, Scalar(0));
            vecc.noalias() += deltatmin * vecp;
            const Scalar tfinal = il + deltatmin;

            for (int i = 0; i < nfree; i++) {
                const int coord = fv_set[i];
                xcp[coord] = x0[coord] + tfinal * vecd[coord];
            }
            for (int i = b; i < nord; i++) {
                const int coord = ord[i];
                xcp[coord] = x0[coord] + tfinal * vecd[coord];
                fv_set.push_back(coord);
            }
        }
    }
};

}  // namespace LBFGSpp
