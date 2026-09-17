

#pragma once

#include <Eigen/Core>
#include <stdexcept>

namespace LBFGSpp {

enum LINE_SEARCH_TERMINATION_CONDITION {

    LBFGS_LINESEARCH_BACKTRACKING_ARMIJO = 1,

    LBFGS_LINESEARCH_BACKTRACKING = 2,

    LBFGS_LINESEARCH_BACKTRACKING_WOLFE = 2,

    LBFGS_LINESEARCH_BACKTRACKING_STRONG_WOLFE = 3
};

template <typename Scalar = double>
class LBFGSParam {
 public:
    int m;

    Scalar epsilon;

    Scalar epsilon_rel;

    int past;

    Scalar delta;

    int max_iterations;

    int linesearch;

    int max_linesearch;

    Scalar min_step;

    Scalar max_step;

    Scalar ftol;

    Scalar wolfe;

 public:
    LBFGSParam() {
        m = 6;
        epsilon = Scalar(1e-5);
        epsilon_rel = Scalar(1e-5);
        past = 0;
        delta = Scalar(0);
        max_iterations = 0;
        linesearch = LBFGS_LINESEARCH_BACKTRACKING_ARMIJO;
        max_linesearch = 20;
        min_step = Scalar(1e-20);
        max_step = Scalar(1e+20);
        ftol = Scalar(1e-4);
        wolfe = Scalar(0.9);
    }

    inline void check_param() const {
        if (m <= 0) { throw std::invalid_argument("'m' must be positive"); }
        if (epsilon < 0) {
            throw std::invalid_argument("'epsilon' must be non-negative");
        }
        if (epsilon_rel < 0) {
            throw std::invalid_argument("'epsilon_rel' must be non-negative");
        }
        if (past < 0) {
            throw std::invalid_argument("'past' must be non-negative");
        }
        if (delta < 0) {
            throw std::invalid_argument("'delta' must be non-negative");
        }
        if (max_iterations < 0) {
            throw std::invalid_argument(
                "'max_iterations' must be non-negative");
        }
        if ((linesearch < LBFGS_LINESEARCH_BACKTRACKING_ARMIJO) ||
            (linesearch > LBFGS_LINESEARCH_BACKTRACKING_STRONG_WOLFE)) {
            throw std::invalid_argument(
                "unsupported line search termination condition");
        }
        if (max_linesearch <= 0) {
            throw std::invalid_argument("'max_linesearch' must be positive");
        }
        if (min_step < 0) {
            throw std::invalid_argument("'min_step' must be positive");
        }
        if (max_step < min_step) {
            throw std::invalid_argument(
                "'max_step' must be greater than 'min_step'");
        }
        if ((ftol <= 0) || (ftol >= 0.5)) {
            throw std::invalid_argument("'ftol' must satisfy 0 < ftol < 0.5");
        }
        if ((wolfe <= ftol) || (wolfe >= 1)) {
            throw std::invalid_argument(
                "'wolfe' must satisfy ftol < wolfe < 1");
        }
    }
};

template <typename Scalar = double>
class LBFGSBParam {
 public:
    int m;

    Scalar epsilon;

    Scalar epsilon_rel;

    int past;

    Scalar delta;

    int max_iterations;

    int max_submin;

    int max_linesearch;

    Scalar min_step;

    Scalar max_step;

    Scalar ftol;

    Scalar wolfe;

 public:
    LBFGSBParam() {
        m = 6;
        epsilon = Scalar(1e-5);
        epsilon_rel = Scalar(1e-5);
        past = 1;
        delta = Scalar(1e-10);
        max_iterations = 0;
        max_submin = 10;
        max_linesearch = 20;
        min_step = Scalar(1e-20);
        max_step = Scalar(1e+20);
        ftol = Scalar(1e-4);
        wolfe = Scalar(0.9);
    }

    inline void check_param() const {
        if (m <= 0) throw std::invalid_argument("'m' must be positive");
        if (epsilon < 0)
            throw std::invalid_argument("'epsilon' must be non-negative");
        if (epsilon_rel < 0)
            throw std::invalid_argument("'epsilon_rel' must be non-negative");
        if (past < 0)
            throw std::invalid_argument("'past' must be non-negative");
        if (delta < 0)
            throw std::invalid_argument("'delta' must be non-negative");
        if (max_iterations < 0)
            throw std::invalid_argument(
                "'max_iterations' must be non-negative");
        if (max_submin < 0)
            throw std::invalid_argument("'max_submin' must be non-negative");
        if (max_linesearch <= 0)
            throw std::invalid_argument("'max_linesearch' must be positive");
        if (min_step < 0)
            throw std::invalid_argument("'min_step' must be positive");
        if (max_step < min_step)
            throw std::invalid_argument(
                "'max_step' must be greater than 'min_step'");
        if (ftol <= 0 || ftol >= 0.5)
            throw std::invalid_argument("'ftol' must satisfy 0 < ftol < 0.5");
        if (wolfe <= ftol || wolfe >= 1)
            throw std::invalid_argument(
                "'wolfe' must satisfy ftol < wolfe < 1");
    }
};

}  // namespace LBFGSpp
