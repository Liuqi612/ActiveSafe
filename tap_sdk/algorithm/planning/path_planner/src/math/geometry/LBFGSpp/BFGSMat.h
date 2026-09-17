

#pragma once

#include <Eigen/Core>
#include <vector>

#include "path_planner/src/math/geometry/LBFGSpp/BKLDLT.h"

namespace LBFGSpp {

template <typename Scalar, bool LBFGSB = false>
class BFGSMat {
 private:
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> Matrix;
    typedef Eigen::Ref<const Vector> RefConstVec;
    typedef std::vector<int> IndexSet;

    int m_m;
    Scalar m_theta;
    Matrix m_s;
    Matrix m_y;
    Vector m_ys;
    Vector m_alpha;
    int m_ncorr;
    int m_ptr;

    Matrix m_permMinv;
    BKLDLT<Scalar> m_permMsolver;

 public:
    BFGSMat() {}

    inline void reset(int n, int m) {
        m_m = m;
        m_theta = static_cast<Scalar>(1);
        m_s.resize(n, m);
        m_y.resize(n, m);
        m_ys.resize(m);
        m_alpha.resize(m);
        m_ncorr = 0;
        m_ptr = m;

        if (LBFGSB) {
            m_permMinv.resize(2 * m, 2 * m);
            (void)m_permMinv.setZero();
            (void)m_permMinv.diagonal().setOnes();
        }
    }

    inline void add_correction(const RefConstVec &s, const RefConstVec &y) {
        const int loc = m_ptr % m_m;

        m_s.col(loc).noalias() = s;
        m_y.col(loc).noalias() = y;

        const Scalar ys = m_s.col(loc).dot(m_y.col(loc));
        m_ys[loc] = ys;

        m_theta = m_y.col(loc).squaredNorm() / ys;

        if (m_ncorr < m_m) { m_ncorr++; }

        m_ptr = loc + 1;

        if (LBFGSB) {
            m_permMinv(loc, loc) = -ys;

            Vector Ss = m_s.leftCols(m_ncorr).transpose() * m_s.col(loc);
            m_permMinv.block(m_m + loc, m_m, 1, m_ncorr).noalias() =
                Ss.transpose();
            m_permMinv.block(m_m, m_m + loc, m_ncorr, 1).noalias() = Ss;

            const int len = m_ncorr - 1;

            if (m_ncorr >= m_m) { (void)m_permMinv.block(m_m, loc, m_m, 1).setZero(); }

            int yloc = (loc + m_m - 1) % m_m;
            for (int i = 0; i < len; i++) {
                m_permMinv(m_m + loc, yloc) = m_s.col(loc).dot(m_y.col(yloc));
                yloc = (yloc + m_m - 1) % m_m;
            }

            (void)(m_permMinv.block(m_m, m_m, m_m, m_m) *= m_theta);
            m_permMsolver.compute(m_permMinv);
            (void)(m_permMinv.block(m_m, m_m, m_m, m_m) /= m_theta);
        }
    }

    inline void apply_Hv(const Vector &v, const Scalar &a, Vector &res) {
        res.resize(v.size());

        res.noalias() = a * v;
        int j = m_ptr % m_m;
        for (int i = 0; i < m_ncorr; i++) {
            j = (j + m_m - 1) % m_m;
            m_alpha[j] = m_s.col(j).dot(res) / m_ys[j];
            res.noalias() -= m_alpha[j] * m_y.col(j);
        }

        res /= m_theta;

        for (int i = 0; i < m_ncorr; i++) {
            const Scalar beta = m_y.col(j).dot(res) / m_ys[j];
            res.noalias() += (m_alpha[j] - beta) * m_s.col(j);
            j = (j + 1) % m_m;
        }
    }

    inline Scalar theta() const { return m_theta; }

    inline int num_corrections() const { return m_ncorr; }

    inline void apply_Wtv(const Vector &v, Vector &res) const {
        res.resize(2 * m_ncorr);
        res.head(m_ncorr).noalias() = m_y.leftCols(m_ncorr).transpose() * v;
        res.tail(m_ncorr).noalias() =
            m_theta * m_s.leftCols(m_ncorr).transpose() * v;
    }

    inline Vector Wb(int b) const {
        Vector res(2 * m_ncorr);
        for (int j = 0; j < m_ncorr; j++) {
            res[j] = m_y(b, j);
            res[m_ncorr + j] = m_s(b, j);
        }
        res.tail(m_ncorr) *= m_theta;
        return res;
    }

    inline Matrix Wb(const IndexSet &b) const {
        const int nb = b.size();
        const int *bptr = b.data();
        Matrix res(nb, 2 * m_ncorr);

        for (int j = 0; j < m_ncorr; j++) {
            const Scalar *Yptr = &m_y(0, j);
            const Scalar *Sptr = &m_s(0, j);
            Scalar *resYptr = res.data() + j * nb;
            Scalar *resSptr = resYptr + m_ncorr * nb;
            for (int i = 0; i < nb; i++) {
                const int row = bptr[i];
                resYptr[i] = Yptr[row];
                resSptr[i] = Sptr[row];
            }
        }
        return res;
    }

    inline void apply_Mv(const Vector &v, Vector &res) const {
        res.resize(2 * m_ncorr);
        if (m_ncorr < 1) return;

        Vector vpadding = Vector::Zero(2 * m_m);
        vpadding.head(m_ncorr).noalias() = v.head(m_ncorr);
        vpadding.segment(m_m, m_ncorr).noalias() = v.tail(m_ncorr);

        m_permMsolver.solve_inplace(vpadding);

        res.head(m_ncorr).noalias() = vpadding.head(m_ncorr);
        res.tail(m_ncorr).noalias() = vpadding.segment(m_m, m_ncorr);
    }

    inline bool apply_WtPv(const IndexSet &P_set,
                           const Vector &v,
                           Vector &res,
                           bool test_zero = false) const {
        const int *Pptr = P_set.data();
        const Scalar *vptr = v.data();
        int nP = P_set.size();

        IndexSet P_reduced;
        std::vector<Scalar> v_reduced;
        if (test_zero) {
            P_reduced.reserve(nP);
            for (int i = 0; i < nP; i++) {
                if (vptr[i] != Scalar(0)) {
                    P_reduced.push_back(Pptr[i]);
                    v_reduced.push_back(vptr[i]);
                }
            }
            Pptr = P_reduced.data();
            vptr = v_reduced.data();
            nP = P_reduced.size();
        }

        res.resize(2 * m_ncorr);
        if (m_ncorr < 1 || nP < 1) {
            res.setZero();
            return false;
        }

        for (int j = 0; j < m_ncorr; j++) {
            Scalar resy = Scalar(0), ress = Scalar(0);
            const Scalar *yptr = &m_y(0, j);
            const Scalar *sptr = &m_s(0, j);
            for (int i = 0; i < nP; i++) {
                const int row = Pptr[i];
                resy += yptr[row] * vptr[i];
                ress += sptr[row] * vptr[i];
            }
            res[j] = resy;
            res[m_ncorr + j] = ress;
        }
        res.tail(m_ncorr) *= m_theta;
        return true;
    }

    inline bool apply_PtWMv(const IndexSet &P_set,
                            const Vector &v,
                            Vector &res,
                            const Scalar &scale) const {
        const int nP = P_set.size();
        res.resize(nP);
        res.setZero();
        if (m_ncorr < 1 || nP < 1) return false;

        Vector Mv;
        apply_Mv(v, Mv);

        Mv.tail(m_ncorr) *= m_theta;
        for (int j = 0; j < m_ncorr; j++) {
            const Scalar *yptr = &m_y(0, j);
            const Scalar *sptr = &m_s(0, j);
            const Scalar Mvy = Mv[j], Mvs = Mv[m_ncorr + j];
            for (int i = 0; i < nP; i++) {
                const int row = P_set[i];
                res[i] += Mvy * yptr[row] + Mvs * sptr[row];
            }
        }
        res *= scale;
        return true;
    }

    inline bool apply_PtWMv(const Matrix &WP,
                            const Vector &v,
                            Vector &res,
                            const Scalar &scale) const {
        const int nP = WP.rows();
        res.resize(nP);
        if (m_ncorr < 1 || nP < 1) {
            res.setZero();
            return false;
        }

        Vector Mv;
        apply_Mv(v, Mv);

        Mv.tail(m_ncorr) *= m_theta;
        res.noalias() = scale * (WP * Mv);
        return true;
    }

    inline void compute_FtBAb(const Matrix &WF,
                              const IndexSet &fv_set,
                              const IndexSet &newact_set,
                              const Vector &Wd,
                              const Vector &drt,
                              Vector &res) const {
        const int nact = newact_set.size();
        const int nfree = WF.rows();
        res.resize(nfree);
        if (m_ncorr < 1 || nact < 1 || nfree < 1) {
            res.setZero();
            return;
        }

        Vector rhs(2 * m_ncorr);
        if (nact <= nfree) {
            Vector Ad(nfree);
            for (int i = 0; i < nact; i++) Ad[i] = drt[newact_set[i]];
            apply_WtPv(newact_set, Ad, rhs);
        } else {
            Vector Fd(nfree);
            for (int i = 0; i < nfree; i++) Fd[i] = drt[fv_set[i]];

            rhs.noalias() = WF.transpose() * Fd;
            rhs.tail(m_ncorr) *= m_theta;
            rhs.noalias() = Wd - rhs;
        }

        apply_PtWMv(WF, rhs, res, Scalar(-1));
    }

    inline void solve_PtBP(const Matrix &WP,
                           const Vector &v,
                           Vector &res) const {
        const int nP = WP.rows();
        res.resize(nP);
        if (m_ncorr < 1 || nP < 1) {
            res.noalias() = v / m_theta;
            return;
        }

        Matrix mid(2 * m_ncorr, 2 * m_ncorr);

        for (int j = 0; j < m_ncorr; j++) {
            mid.col(j).segment(j, m_ncorr - j).noalias() =
                m_permMinv.col(j).segment(j, m_ncorr - j) -
                WP.block(0, j, nP, m_ncorr - j).transpose() * WP.col(j) /
                    m_theta;
        }

        mid.block(m_ncorr, 0, m_ncorr, m_ncorr).noalias() =
            m_permMinv.block(m_m, 0, m_ncorr, m_ncorr) -
            WP.rightCols(m_ncorr).transpose() * WP.leftCols(m_ncorr);

        for (int j = 0; j < m_ncorr; j++) {
            mid.col(m_ncorr + j).segment(m_ncorr + j, m_ncorr - j).noalias() =
                m_theta *
                (m_permMinv.col(m_m + j).segment(m_m + j, m_ncorr - j) -
                 WP.rightCols(m_ncorr - j).transpose() * WP.col(m_ncorr + j));
        }

        BKLDLT<Scalar> midsolver(mid);

        Vector WPv = WP.transpose() * v;
        WPv.tail(m_ncorr) *= m_theta;
        midsolver.solve_inplace(WPv);
        WPv.tail(m_ncorr) *= m_theta;
        res.noalias() = v / m_theta + (WP * WPv) / (m_theta * m_theta);
    }

    inline bool apply_PtBQv(const Matrix &WP,
                            const IndexSet &Q_set,
                            const Vector &v,
                            Vector &res,
                            bool test_zero = false) const {
        const int nP = WP.rows();
        const int nQ = Q_set.size();
        res.resize(nP);
        if (m_ncorr < 1 || nP < 1 || nQ < 1) {
            res.setZero();
            return false;
        }

        Vector WQtv;
        bool nonzero = apply_WtPv(Q_set, v, WQtv, test_zero);
        if (!nonzero) {
            res.setZero();
            return false;
        }

        Vector MWQtv;
        apply_Mv(WQtv, MWQtv);
        MWQtv.tail(m_ncorr) *= m_theta;
        res.noalias() = -WP * MWQtv;
        return true;
    }

    inline bool apply_PtBQv(const Matrix &WP,
                            const Matrix &WQ,
                            const Vector &v,
                            Vector &res) const {
        const int nP = WP.rows();
        const int nQ = WQ.rows();
        res.resize(nP);
        if (m_ncorr < 1 || nP < 1 || nQ < 1) {
            res.setZero();
            return false;
        }

        Vector WQtv = WQ.transpose() * v;
        WQtv.tail(m_ncorr) *= m_theta;
        Vector MWQtv;
        apply_Mv(WQtv, MWQtv);
        MWQtv.tail(m_ncorr) *= m_theta;
        res.noalias() = -WP * MWQtv;
        return true;
    }
};

}  // namespace LBFGSpp
