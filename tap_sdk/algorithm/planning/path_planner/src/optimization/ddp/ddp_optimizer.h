
#pragma once

#include <algorithm>
#include <array>
#include <boost/optional.hpp>
#include <cmath>
#include <memory>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "base/macros.h"
#include <Eigen/Eigen>
#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <absl/strings/str_format.h>
// #include <gflags/gflags.h>
#include "common/log.h"

#include "math/util.h"
#include "math/vec.h"
#include "optimization/ddp/ddp_cost_manager_hook.h"
#include "optimization/ddp/ddp_optimizer_hook.h"
#include "optimization/problem/cost.h"
#include "plan/planner_defs.h"
#include "plan/trajectory_point.h"
#include "pncx_planner_params.pb.h"
#include "util/loop_guard.h"

#define ENABLE_DDP_OPTIMIZER_DEBUG_COST_STRING 0

namespace pnc_x {
namespace planning {
template <typename PROB>

class DdpOptimizer;
}
}  // namespace pnc_x

// DECLARE_int32(planner_dopt_canvas_level);

namespace pnc_x {
namespace planning {

// #define DDPVLOG(verboselevel) VLOG(verboselevel)

template <typename PROB>
class DdpOptimizer {
 public:
    struct SolveConfig {
        int max_iteration = INT_MAX;
        bool forward = true;
        bool enable_iteration_failure_postprocess = true;
        bool enable_qtrace = false;
        bool enable_qevent = false;

        static constexpr SolveConfig Default() {
            return SolveConfig{
                .max_iteration = INT_MAX,
                .forward = true,
                .enable_iteration_failure_postprocess = true,
                .enable_qtrace = false,
                .enable_qevent = false,
            };
        }

        static constexpr SolveConfig Onboard() {
            return SolveConfig{
                .max_iteration = INT_MAX,
                .forward = true,
                .enable_iteration_failure_postprocess = true,
                .enable_qtrace = true,
                .enable_qevent = true,
            };
        }
    };

    static constexpr int kStateSize = PROB::kStateSize;
    static constexpr int kControlSize = PROB::kControlSize;

    using StateType = typename PROB::StateType;
    using ControlType = typename PROB::ControlType;
    using StatesType = typename PROB::StatesType;
    using ControlsType = typename PROB::ControlsType;

    DdpOptimizer(int plan_id,
                 const PROB *problem,
                 int dense_horizon,
                 int sparse_horizon,
                 std::string owner,
                 int verbosity,
                 DdpOptimizerParamsProto params,
                 std::string dopt_tag);

    DdpOptimizer(int plan_id,
                 const PROB *problem,
                 int dense_horizon,
                 int sparse_horizon,
                 std::string owner,
                 int verbosity,
                 DdpOptimizerParamsProto params)
        : DdpOptimizer(plan_id,
                       problem,
                       dense_horizon,
                       sparse_horizon,
                       owner,
                       verbosity,
                       params,
                       "0") {}

    DdpOptimizer(int plan_id,
                 const PROB *problem,
                 int dense_horizon,
                 int sparse_horizon,
                 std::string owner,
                 int verbosity)
        : DdpOptimizer(plan_id,
                       problem,
                       dense_horizon,
                       sparse_horizon,
                       owner,
                       verbosity,
                       CreateDefaultParams()) {}

    DdpOptimizer(int plan_id,
                 const PROB *problem,
                 int dense_horizon,
                 int sparse_horizon,
                 std::string owner)
        : DdpOptimizer(
              plan_id, problem, dense_horizon, sparse_horizon, owner, 0) {}

    DdpOptimizer(int plan_id,
                 const PROB *problem,
                 int dense_horizon,
                 int sparse_horizon)
        : DdpOptimizer(plan_id, problem, dense_horizon, sparse_horizon, "") {}

    using HookType = typename pnc_x::planning::DdpOptimizerHook<PROB>;

    void AddHook(HookType *hook) { hooks_.push_back(hook); }

    absl::StatusOr<std::vector<TrajectoryPoint>> Solve(
        const std::vector<TrajectoryPoint> &init_trajectory,
        const SolveConfig &config = SolveConfig::Default(),
        bool is_compare_weight = false) const;

    double EvaluateCostForTrajectory(
        const std::vector<TrajectoryPoint> &trajectory) const {
        XCHECK_GE(trajectory.size(), horizon_);
        StateType x0;
        ControlsType us(horizon_ * kControlSize);
        StatesType xs(horizon_ * kStateSize);
        FitTrajectoryPointToSolverStates(trajectory, &x0, &us, &xs);

        typename HookType::OptimizerInspector oi;
        for (auto *hook : hooks_) {
            hook->OnSolveStart(xs, us, oi);
        }

        return EvaluateCost(xs, us);
    }

    boost::optional<double> GetFinalTotalCost() const {
        return final_total_cost_;
    }

    const std::vector<std::string> &GetFinalCostDebug() const {
        return final_cost_debug_;
    }

    int problem_costs_size() const { return problem_->costs().size(); }

 protected:
    using FType = typename PROB::FType;
    using DFDxType = typename PROB::DFDxType;
    using DFDuType = typename PROB::DFDuType;
    using DDFDxDxType = typename PROB::DDFDxDxType;
    using DDFDxDuType = typename PROB::DDFDxDuType;
    using DDFDuDxType = typename PROB::DDFDuDxType;
    using DDFDuDuType = typename PROB::DDFDuDuType;
    using GType = typename PROB::GType;
    using DGDxType = typename PROB::DGDxType;
    using DGDuType = typename PROB::DGDuType;
    using DDGDxDxType = typename PROB::DDGDxDxType;
    using DDGDxDuType = typename PROB::DDGDxDuType;
    using DDGDuDxType = typename PROB::DDGDuDxType;
    using DDGDuDuType = typename PROB::DDGDuDuType;
    using ClampInfo = typename PROB::ClampInfo;
    using JType = double;
    using DJDxType = Eigen::Matrix<double, 1, kStateSize>;
    using DDJDxDxType = Eigen::Matrix<double, kStateSize, kStateSize>;

    double SolveLinearDdp(const PROB &problem,
                          const StatesType &xs,
                          const ControlsType &us,
                          double curr_cost,
                          StatesType *dxs,
                          ControlsType *dus,
                          ControlsType *dus_open,
                          std::vector<DDGDuDxType> *dus_close_gain,
                          int *k_ne) const;

    static bool IsDdJdxdxSemiPositive(const DDJDxDxType &ddJdxdx);

    template <typename HESSG>
    static HESSG GradJDot(const Eigen::Matrix<double, 1, kStateSize> &grad_j,
                          const std::array<HESSG, kStateSize> &hess_f,
                          bool enable_dynamic_2nd_derivatives) {
        if (enable_dynamic_2nd_derivatives) { return HESSG::Zero(); }
        HESSG hess_g = HESSG::Zero();
        for (int i = 0; i < kStateSize; ++i) {
            hess_g += grad_j[i] * hess_f[i];
        }
        return hess_g;
    }

    double EvaluateCost(const StatesType &xs,
                        const ControlsType &us,
                        std::vector<NamedCostEntry> *named_costs) const;
    double EvaluateCost(const StatesType &xs, const ControlsType &us) const {
        return EvaluateCost(xs, us, nullptr);
    }

    void FitTrajectoryPointToSolverStates(
        std::vector<TrajectoryPoint> trajectory,
        StateType *x0,
        ControlsType *us,
        StatesType *xs) const;

    std::vector<TrajectoryPoint> GenerateTrajectoryPointsFromSolverStates(
        const StatesType &xs, const ControlsType &us, bool s_increasing) const;

    double LineSearchAndEvaluateCost(
        int iteration,
        const StatesType &tentative_xs,
        const ControlsType &tentative_us,
        const StatesType &full_dxs,
        const ControlsType &full_dus,
        double alpha,
        typename HookType::OptimizerInspector *oi) const;

    double StepSizeAdjustmentAndEvaluateCost(
        int iteration,
        const StatesType &xs,
        const ControlsType &us,
        int k_stepsize,
        typename HookType::OptimizerInspector *oi) const;

    ControlsType OptimizeInitialControl(const StatesType &init_xs,
                                        const ControlsType &init_us);

    DdpOptimizerParamsProto CreateDefaultParams() {
        DdpOptimizerParamsProto params;
        return params;
    }

 private:
    const PROB *problem_;
    int dense_horizon_ = 0;
    int sparse_horizon_ = 0;
    int horizon_ = 0;
    std::string owner_;
    int verbosity_ = 0;
    int plan_id_ = 0;
    DdpOptimizerParamsProto params_;
    std::string dopt_tag_;
    std::unique_ptr<DdpCostManagerHook<PROB>> cost_manager_hook_;

    std::vector<HookType *> hooks_;
    std::vector<TrajectoryPoint> init_points_;
    mutable boost::optional<double> final_total_cost_ = boost::none;
    mutable std::vector<std::string> final_cost_debug_;
};

template <typename PROB>
DdpOptimizer<PROB>::DdpOptimizer(int plan_id,
                                 const PROB *problem,
                                 int dense_horizon,
                                 int sparse_horizon,
                                 std::string owner,
                                 int verbosity,
                                 DdpOptimizerParamsProto params,
                                 std::string dopt_tag)
    : problem_(XCHECK_NOTNULL(problem)),
      dense_horizon_(dense_horizon),
      sparse_horizon_(sparse_horizon),
      horizon_(dense_horizon + sparse_horizon),
      owner_(std::move(owner)),
      verbosity_(verbosity),
      plan_id_(plan_id),
      params_(std::move(params)),
      dopt_tag_(std::move(dopt_tag)) {
    XCHECK_GT(horizon_, 0);
    cost_manager_hook_ = std::make_unique<DdpCostManagerHook<PROB>>(horizon_);
    for (const auto &helper : problem_->cost_helpers()) {
        cost_manager_hook_->AddCostHelper(helper.get());
    }
    for (const auto &cost : problem_->costs()) {
        cost_manager_hook_->AddCost(cost.get());
    }
    AddHook(cost_manager_hook_.get());
}

template <typename PROB>
bool DdpOptimizer<PROB>::IsDdJdxdxSemiPositive(const DDJDxDxType &ddJdxdx) {
    constexpr double kEps = 1e-9;
    const int size = ddJdxdx.rows();
    StateType D_vec = StateType::Zero();
    DDJDxDxType L = DDJDxDxType::Identity();
    for (int j = 0; j < size; ++j) {
        double D_j = ddJdxdx(j, j);
        for (int k = 0; k < j; ++k) {
            D_j -= Sqr(L(j, k)) * D_vec(k);
        }
        D_vec(j) = D_j;
        if (D_j < -kEps) {
            return false;
        }
        if (std::abs(D_j) < kEps) {
            for (int i = j + 1; i < size; ++i) {
                L(i, j) = 0.0;
            }
        } else {
            double D_j_recip = 1.0 / D_j;
            for (int i = j + 1; i < size; ++i) {
                double L_ij = ddJdxdx(i, j);
                for (int k = 0; k < j; ++k) {
                    L_ij -= L(i, k) * L(j, k) * D_vec(k);
                }
                L_ij *= D_j_recip;
                L(i, j) = L_ij;
            }
        }
    }
    return true;
}

template <typename PROB>
double DdpOptimizer<PROB>::SolveLinearDdp(
    const PROB &problem,
    const StatesType &xs,
    const ControlsType &us,
    double curr_cost,
    StatesType *dxs,
    ControlsType *dus,
    ControlsType *dus_open,
    std::vector<DDGDuDxType> *dus_close_gain,
    int *k_ne) const {
    const StateType x0 = PROB::GetStateAtStep(xs, 0);

    struct LinearDdpScratch {
        std::vector<JType> Js;
        std::vector<DJDxType> dJdxs;
        std::vector<DDJDxDxType> ddJdxdxs;
        std::vector<ControlType> dus_open_tmp;
        std::vector<DDGDuDxType> dus_close_gain_tmp;
        std::vector<typename PROB::FDerivatives> fds;
        std::vector<typename PROB::GDerivatives> gds;
    };
    thread_local LinearDdpScratch scratch;
    auto &Js = scratch.Js;
    auto &dJdxs = scratch.dJdxs;
    auto &ddJdxdxs = scratch.ddJdxdxs;
    auto &dus_open_tmp = scratch.dus_open_tmp;
    auto &dus_close_gain_tmp = scratch.dus_close_gain_tmp;
    auto &fds = scratch.fds;
    auto &gds = scratch.gds;

    Js.resize(horizon_ + 1);
    dJdxs.resize(horizon_ + 1);
    ddJdxdxs.resize(horizon_ + 1);
    dus_open_tmp.resize(horizon_);
    dus_close_gain_tmp.resize(horizon_);

    Js[horizon_] = 0.0;
    dJdxs[horizon_] = DJDxType::Zero();
    ddJdxdxs[horizon_] = DDJDxDxType::Zero();

    boost::optional<int> k_n_e;
    constexpr double kEps = 1e-8;

    problem.EvaluateFDerivativesForAllSteps(xs, us, &fds);
    problem.AddGDerivativesForAllSteps(xs, us, &gds);
    XCHECK_EQ(fds.size(), horizon_);
    XCHECK_EQ(gds.size(), horizon_);
    for (int k = horizon_ - 1; k >= 0; --k) {
        // A0_1_1-a: f is a reference to fds[k].value but never read
        // const FType &f = fds[k].value;
        const DFDxType &dfdx = fds[k].dfdx;
        const DFDuType &dfdu = fds[k].dfdu;
        const DDFDxDxType &ddfdxdx = fds[k].ddfdxdx;
        const DDFDuDxType &ddfdudx = fds[k].ddfdudx;
        const DDFDuDuType &ddfdudu = fds[k].ddfdudu;

        const GType &g = gds[k].value;
        const DGDxType &dgdx = gds[k].dgdx;
        const DGDuType &dgdu = gds[k].dgdu;
        const DDGDxDxType &ddgdxdx = gds[k].ddgdxdx;
        const DDGDuDxType &ddgdudx = gds[k].ddgdudx;
        const DDGDuDuType &ddgdudu = gds[k].ddgdudu;

        const JType &J = Js[k + 1];
        const DJDxType &dJdx = dJdxs[k + 1];
        const DDJDxDxType &ddJdxdx = ddJdxdxs[k + 1];


        // enable_dynamic_2nd_derivatives 来决定是iLQR还是DDP
        // Quu = luu + Vx^T * fuu + fu^T * Vxx * fu
        const DDGDuDuType A =
            ddgdudu +
            GradJDot(dJdx, ddfdudu, problem.enable_dynamic_2nd_derivatives()) +
            dfdu.transpose() * ddJdxdx * dfdu;
        // Qux = lux + Vx^T * fux + fu^T * Vxx * fx 
        const DDGDuDxType b_lin =
            ddgdudx +
            GradJDot(dJdx, ddfdudx, problem.enable_dynamic_2nd_derivatives()) +
            dfdu.transpose() * ddJdxdx * dfdx;

        // 根据下面公式来修正Q矩阵 
        // Quu_hat = Quu - fu^T * lambda * fu;
        // Qux_hat = Qux - fu^T * lambda * fx; 
        // double min_eigen_value = 0.0;
        // if (!IsDdJdxdxSemiPositive(ddJdxdx)) {
        //     Eigen::EigenSolver<DDJDxDxType> es(ddJdxdx);
        //     min_eigen_value = es.pseudoEigenvalueMatrix().minCoeff();
        // }

        double min_eigen_value = 0.0;

        // 1) 先用 LDLT 判定 ddJdxdx 是否（数值上）半正定
        {
          constexpr double kEps = 1e-9;
          // ddJdxdx 通常是对称实：只用下三角，减少访存
          auto Axx = ddJdxdx.template selfadjointView<Eigen::Lower>();
          Eigen::LDLT<DDJDxDxType> ldlt_xx;
          ldlt_xx.compute(Axx);

          bool psd = false;
          if (ldlt_xx.info() == Eigen::Success) {
            // 数值半正定：D 中最小对角元 >= -kEps
            const auto &D = ldlt_xx.vectorD();
            psd = (D.array() >= -kEps).all();
          }

          if (!psd) {
            // 2) 仅在非 PSD 时再求 λ_min（
            Eigen::SelfAdjointEigenSolver<DDJDxDxType> es;
            es.compute(Axx, Eigen::EigenvaluesOnly);
            if (es.info() == Eigen::Success) {
              min_eigen_value = es.eigenvalues().minCoeff();
            } else {
              // 兜底：若特征分解失败，当作轻微非 PSD 处理
              min_eigen_value = -kEps;
            }
          }
        }
        
        const DDGDuDuType A_tilde =
            A - dfdu.transpose() * min_eigen_value * dfdu;
        const DDGDuDuType Ainv_tilde = A_tilde.inverse();
        // Qu = lu + Vx^T * fu
        const DGDuType b_base_tilde = dgdu + (dJdx * dfdu);
        const DDGDuDxType b_lin_tilde =
            b_lin - dfdu.transpose() * min_eigen_value * dfdx;
        // Vt = g + V_(t+1)
        const GType c_base_tilde = g + J;

        // 更新前馈增益du_open 和 反馈增益du_close_gain
        auto &du_open = dus_open_tmp[k];
        auto &du_close_gain = dus_close_gain_tmp[k];
        du_open = -Ainv_tilde * b_base_tilde.transpose();
        du_close_gain = -Ainv_tilde * b_lin_tilde;
        const auto du_open_transpose = du_open.transpose();
        const auto du_close_gain_transpose = du_close_gain.transpose();
        
        // 二次近似预期下降值cost: delta_v =  kt^T * Qu + (0.5 * kt)^t * Quu * kt
        const double dJ_expected =
            0.5 * du_open_transpose * A * du_open + (b_base_tilde * du_open)(0);
        // 期望cost在第一次出现明显负下降的步之后(k+1)记为 k_n_e，后面“截断”时作为“只在后段施加增量”的
        if (dJ_expected < -kEps && !k_n_e.has_value()) { k_n_e = k + 1; }

        // 标准值函数更新公式
        Js[k] = c_base_tilde + dJ_expected;
        dJdxs[k] = dgdx + (dJdx * dfdx) + du_open_transpose * A * du_close_gain +
                   b_base_tilde * du_close_gain + (du_open_transpose * b_lin);
        ddJdxdxs[k] =
            ddgdxdx +
            GradJDot(dJdx, ddfdxdx, problem.enable_dynamic_2nd_derivatives()) +
            dfdx.transpose() * ddJdxdx * dfdx +
            du_close_gain_transpose * A * du_close_gain +
            du_close_gain_transpose * b_lin + b_lin.transpose() * du_close_gain;
        // 数值稳定操作
        ddJdxdxs[k] = (ddJdxdxs[k] + ddJdxdxs[k].transpose()) * 0.5;
    }

    *dxs = StatesType::Zero(horizon_ * kStateSize);
    *dus = ControlsType::Zero(horizon_ * kControlSize);

    const int k_stepsize_upper = k_n_e.has_value() ? *k_n_e : 0;
    int k_stepsize = -k_stepsize_upper;
    constexpr double kDuLimit = 1e4;
    /*
    允许在后段应用控制修正（因为后段线性化更准确，偏差小），
    而前段保持参考轨迹不动（冻结 du=0），避免大修正导致的爆炸。

    为什么要用二分的操作？
        1.我们不知道最小的安全截断点在哪里；
        2.如果一次性选得太靠后，可能过于保守（浪费了可下降空间）；
        3.用二分，可以在对数时间复杂度内逐步找到“刚好安全”的截断点。
    */
    do {
        // 二分操作
        k_stepsize = (k_stepsize + k_stepsize_upper) >> 1;
        StateType x = x0;

        for (int k = 0; k < horizon_; ++k) {
            const StateType dx = x - PROB::GetStateAtStep(xs, k);
            PROB::SetStateAtStep(dx, k, dxs);
            if (k < k_stepsize) {
                x = PROB::GetStateAtStep(xs, k + 1);
                (*dus_close_gain)[k] = DDGDuDxType::Zero();
                PROB::SetControlAtStep(ControlType::Zero(), k, dus);
                PROB::SetControlAtStep(ControlType::Zero(), k, dus_open);

            } else {
                const ControlType du =
                    dus_open_tmp[k] + dus_close_gain_tmp[k] * dx;
                const ControlType u = PROB::GetControlAtStep(us, k) + du;
                x = problem.EvaluateF(k, x, u);
                (*dus_close_gain)[k] = dus_close_gain_tmp[k];
                PROB::SetControlAtStep(du, k, dus);
                PROB::SetControlAtStep(dus_open_tmp[k], k, dus_open);
            }
        }
    } while ((dus->maxCoeff() > kDuLimit || dus->minCoeff() < -kDuLimit) &&
             k_stepsize < (k_stepsize_upper - 1));

    *k_ne = k_stepsize_upper;

    return Js[0];
}

template <typename PROB>
absl::StatusOr<std::vector<TrajectoryPoint>> DdpOptimizer<PROB>::Solve(
    const std::vector<TrajectoryPoint> &init_trajectory,
    const SolveConfig &config,
    bool is_compare_weight) const {
    XCHECK_GE(init_trajectory.size(), horizon_);
    constexpr char kTrajectoryOptimizerOwner[] = "trajectory_optimizer";

    const int xs_length = horizon_ * kStateSize;
    const int us_length = horizon_ * kControlSize;

    StateType x0;
    ControlsType init_us(us_length);
    StatesType init_xs(xs_length);
    FitTrajectoryPointToSolverStates(init_trajectory, &x0, &init_us, &init_xs);

    typename HookType::OptimizerInspector oi;
    StatesType xs = init_xs;
    ControlsType us = init_us;
    for (auto *hook : hooks_) {
        hook->OnSolveStart(xs, us, oi);
    }

    // ============= hook 记录 =============
    double total_cost = 0.0;
    {
        const double init_cost =
            EvaluateCost(init_xs, init_us, &oi.named_costs);

        std::string prefix;
        std::vector<std::string> init_cost_debug;
        // DDPVLOG(2) << "Initial cost: " << init_cost;
        const std::string init_cost_debug_first_line =
            is_compare_weight
                ? prefix + " Compare weight Initial cost: " +
                      std::to_string(init_cost)
                : prefix + " Initial cost: " + std::to_string(init_cost);
        init_cost_debug.push_back(init_cost_debug_first_line);
#if ENABLE_DDP_OPTIMIZER_DEBUG_COST_STRING
        for (size_t idx = 0; idx < oi.named_costs.size(); ++idx) {
            const auto &entry = oi.named_costs[idx];
            const std::string &cost_name = entry.name;
            double cost = entry.value;
            bool is_soft = entry.is_soft;
            std::string debug_stream = absl::StrFormat(
                "  [%s]\t cost: %f\t is_soft: %d", cost_name, cost, is_soft);
            // DDPVLOG(2) << debug_stream;
            init_cost_debug.push_back(std::move(debug_stream));
        }
#endif

        if (owner_ == kTrajectoryOptimizerOwner) {
        }

        total_cost = init_cost;
        oi.cost = init_cost;
    }

    // ============= line search 初始化 =============
    std::vector<double> line_search_alphas;
    constexpr double kLineSearchAlphaMultiplier = 0.5;

    line_search_alphas.push_back(1.0);
    auto loop_guard1 = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (line_search_alphas.back() > params_.line_search_min_alpha() &&
           loop_guard1) {
        line_search_alphas.push_back(line_search_alphas.back() *
                                     kLineSearchAlphaMultiplier);
    }

    std::size_t alpha_idx = 1U;
    const std::size_t alpha_count = line_search_alphas.size();
    int line_search_count = 0;

    int iteration;
    const int max_iters = std::min(params_.max_iters(), config.max_iteration);
    std::vector<std::string> final_cost_debug;

    // These buffers are reused across DDP iterations. The line-search path
    // keeps several full-horizon Eigen matrices alive at once, so allocating
    // them inside the loop causes repeated heap traffic without changing the
    // numerical algorithm.
    struct SolveScratch {
        StatesType dxs;
        ControlsType dus;
        ControlsType dus_open;
        std::vector<DDGDuDxType> dus_close_gain;
        StatesType line_search_full_dxs;
        ControlsType line_search_full_dus;
        ControlsType line_search_dus_open;
        std::vector<DDGDuDxType> line_search_dus_close_gain;
        StatesType tentative_xs;
        ControlsType tentative_us;
        StatesType curr_xs;
        ControlsType curr_us;
        StatesType next_xs;
        ControlsType next_us;

        void Resize(int xs_length, int us_length, int horizon) {
            dxs.resize(xs_length);
            dus.resize(us_length);
            dus_open.resize(us_length);
            dus_close_gain.resize(horizon);
            line_search_full_dxs.resize(xs_length);
            line_search_full_dus.resize(us_length);
            line_search_dus_open.resize(us_length);
            line_search_dus_close_gain.resize(horizon);
            tentative_xs.resize(xs_length);
            tentative_us.resize(us_length);
            curr_xs.resize(xs_length);
            curr_us.resize(us_length);
            next_xs.resize(xs_length);
            next_us.resize(us_length);
        }
    } solve_scratch;
    solve_scratch.Resize(xs_length, us_length, horizon_);

    // ============= 迭代求解 =============
    for (iteration = 0; iteration < max_iters; ++iteration) {
        if (config.enable_qtrace) {
        }

        for (auto *hook : hooks_) {
            hook->OnIterationStart(iteration, xs, us, oi);
        }

        int k_n_e = horizon_;
        auto &dxs = solve_scratch.dxs;
        auto &dus = solve_scratch.dus;
        auto &dus_open = solve_scratch.dus_open;
        auto &dus_close_gain = solve_scratch.dus_close_gain;
        const double Js0 =
            SolveLinearDdp(*problem_, xs, us, total_cost, &dxs, &dus, &dus_open,
                           &dus_close_gain, &k_n_e);

        auto summarize_controls = [&](const ControlsType &controls,
                                      const std::string &name) {
            int peak_index = -1;
            int first_nonfinite_index = -1;
            double peak_value = 0.0;
            double peak_abs_value = -1.0;
            double l2_norm_sq = 0.0;
            for (int i = 0; i < controls.size(); ++i) {
                const double value = controls[i];
                if (!std::isfinite(value) && first_nonfinite_index < 0) {
                    first_nonfinite_index = i;
                }
                const double abs_value = std::abs(value);
                if (std::isfinite(value)) {
                    l2_norm_sq += value * value;
                }
                if (abs_value > peak_abs_value) {
                    peak_abs_value = abs_value;
                    peak_value = value;
                    peak_index = i;
                }
            }

            const int peak_step =
                peak_index >= 0 ? peak_index / kControlSize : -1;
            const int peak_dim =
                peak_index >= 0 ? peak_index % kControlSize : -1;
            const int nonfinite_step =
                first_nonfinite_index >= 0
                    ? first_nonfinite_index / kControlSize
                    : -1;
            const int nonfinite_dim =
                first_nonfinite_index >= 0
                    ? first_nonfinite_index % kControlSize
                    : -1;
            return absl::StrFormat(
                "%s{max_abs=%.6e, value=%.6e, step=%d, dim=%d, l2=%.6e, "
                "first_nonfinite_step=%d, first_nonfinite_dim=%d}",
                name, peak_abs_value, peak_value, peak_step, peak_dim,
                std::sqrt(l2_norm_sq), nonfinite_step, nonfinite_dim);
        };

        auto summarize_top_costs = [&]() {
            if (oi.named_costs.empty()) {
                return std::string("none");
            }
            std::vector<NamedCostEntry> sorted_costs = oi.named_costs;
            const int top_k = std::min<int>(5, sorted_costs.size());
            std::partial_sort(
                sorted_costs.begin(), sorted_costs.begin() + top_k,
                sorted_costs.end(),
                [](const NamedCostEntry &lhs, const NamedCostEntry &rhs) {
                    return lhs.value > rhs.value;
                });
            std::ostringstream ss;
            for (int i = 0; i < top_k; ++i) {
                if (i > 0) {
                    ss << ", ";
                }
                ss << sorted_costs[i].name << "=" << sorted_costs[i].value;
            }
            return ss.str();
        };

        const bool dus_ok = problem_->CheckDu(dus, owner_);
        const bool dus_open_ok = problem_->CheckDu(dus_open, owner_);
        if (!dus_ok || !dus_open_ok) {
            return absl::InternalError(absl::StrFormat(
                "%s ddp unreasonable du: iter=%d, total_cost=%.6f, "
                "expected_cost=%.6f, k_n_e=%d, dus_ok=%d, dus_open_ok=%d, "
                "%s, %s, top_init_costs=[%s]",
                owner_, iteration, total_cost, Js0, k_n_e, dus_ok,
                dus_open_ok, summarize_controls(dus, "dus"),
                summarize_controls(dus_open, "dus_open"),
                summarize_top_costs()));
        }

        const bool dx_converged =
            (dxs.squaredNorm() < Sqr(params_.convergence_tolerance_dx()));
        const bool du_converged =
            (dus.squaredNorm() < Sqr(params_.convergence_tolerance_du()));

        /*
        整体线搜索流程：
            1. **检查是否需要找步长**

                * 若 `dx/du` 均未收敛 → 进入步长策略；否则跳过。

            2. **备份方向与起点**

                * 备份 `dxs,dus,k,K` 为 line search 用；
                * 构造 α=1 的候选解 `tentative_xs/us`，记录起始成本 `line_search_init_cost = total_cost`。

            3. **评估 α=1**

                * `curr_alpha = 1.0`；
                * 计算 `curr_cost = LineSearchAndEvaluateCost(...)`。

            4. **线搜索（两种模式择一）**

                * **找极小模式** `line_search_to_min==true`：沿 α 序列（如 1, 0.5, 0.25…）前滚，寻找“先降后升”的拐点；若 `next_cost < curr_cost` 则采用 next。
                * **足够下降模式** `line_search_to_min==false`：若 `curr_cost` 未达到“足够下降”（> `init_cost - tol`），就继续用更小 α，直到满足或α用尽。

            5. **若线搜索失败 → 逐步截断（后段应用）**

                * 用 `k_n_e` 给出“可信后段”的上界，从 `k_stepsize` 开始仅在后段应用 `du = k + (K * dx)`，前段冻结 `du=0`；
                * 用二分将 `k_stepsize` 向后推，直到成本下降或无可用位置。

            6. **决定是否接受更新**

                * 若配置强制 `line_search_min_alpha>=1` → 直接接受当前 `curr`；
                * 否则：
                    * 若仍未达到“足够下降” → **回退**（保持原 `xs/us`）；
                    * 若达到了 → **接受**（更新 `xs/us`，并计算 `dcost`）。

            7. **自适应调整下轮 α 起点**（若启用）
                * 成功下降后：`alpha_idx = max(1, floor(alpha_idx*2/3) - 1)`，避免下一轮过激进。
        */
        double dcost = 0.0;
        if (!dx_converged && !du_converged) {
            const double min_acceptable_cost_drop =
                params_.convergence_tolerance_dcost();
            auto &line_search_full_dxs = solve_scratch.line_search_full_dxs;
            auto &line_search_full_dus = solve_scratch.line_search_full_dus;
            auto &line_search_dus_open = solve_scratch.line_search_dus_open;
            auto &line_search_dus_close_gain =
                solve_scratch.line_search_dus_close_gain;
            line_search_full_dxs = dxs;
            line_search_full_dus = dus;
            line_search_dus_open = dus_open;
            line_search_dus_close_gain = dus_close_gain;

            auto &tentative_xs = solve_scratch.tentative_xs;
            auto &tentative_us = solve_scratch.tentative_us;
            tentative_xs = xs + dxs;
            tentative_us = us + dus;
            const double line_search_init_cost = total_cost;

            double curr_alpha = line_search_alphas.front();
            auto &curr_xs = solve_scratch.curr_xs;
            auto &curr_us = solve_scratch.curr_us;
            curr_xs = tentative_xs;
            curr_us = tentative_us;
            double curr_cost = LineSearchAndEvaluateCost(
                iteration, curr_xs, curr_us, line_search_full_dxs,
                line_search_full_dus, curr_alpha, &oi);

            if (params_.line_search_to_min()) {
                double next_alpha = curr_alpha;
                auto &next_xs = solve_scratch.next_xs;
                auto &next_us = solve_scratch.next_us;
                next_xs = curr_xs;
                next_us = curr_us;
                double next_cost = curr_cost;

                auto loop_guard2 = DEFAULT_LOOP_GUARD();
                while (!((curr_cost <
                             (line_search_init_cost - min_acceptable_cost_drop)) &&
                         (next_cost > curr_cost)) &&
                       alpha_idx < alpha_count && loop_guard2) {
                    curr_alpha = next_alpha;
                    curr_xs = next_xs;
                    curr_us = next_us;
                    curr_cost = next_cost;
                    next_alpha = line_search_alphas[alpha_idx];

                    const ControlsType processed_dus_open =
                        line_search_dus_open * next_alpha;
                    StateType x = x0;
                    for (int k = 0; k < horizon_; ++k) {
                        PROB::SetStateAtStep(x, k, &next_xs);
                        const StateType dx = x - PROB::GetStateAtStep(xs, k);
                        const ControlType du =
                            (PROB::GetControlAtStep(processed_dus_open, k) +
                            (line_search_dus_close_gain[k] * dx));
                        const ControlType u =
                            (PROB::GetControlAtStep(us, k) + du);
                        PROB::SetControlAtStep(u, k, &next_us);
                        x = problem_->EvaluateF(k, x, u);
                    }

                    next_cost = LineSearchAndEvaluateCost(
                        iteration, next_xs, next_us, line_search_full_dxs,
                        line_search_full_dus, next_alpha, &oi);

                    ++alpha_idx;
                    ++line_search_count;
                }

                if (next_cost < curr_cost) {
                    curr_alpha = next_alpha;
                    curr_xs = next_xs;
                    curr_us = next_us;
                    curr_cost = next_cost;
                }
            } else if (curr_cost >
                       line_search_init_cost - min_acceptable_cost_drop) {
                do {
                    curr_alpha = line_search_alphas[alpha_idx];
                    const ControlsType processed_dus_open =
                        line_search_dus_open * curr_alpha;
                    StateType x = x0;
                    for (int k = 0; k < horizon_; ++k) {
                        PROB::SetStateAtStep(x, k, &curr_xs);
                        const StateType dx = x - PROB::GetStateAtStep(xs, k);
                        const ControlType du =
                            PROB::GetControlAtStep(processed_dus_open, k) +
                            line_search_dus_close_gain[k] * dx;
                        const ControlType u =
                            PROB::GetControlAtStep(us, k) + du;
                        PROB::SetControlAtStep(u, k, &curr_us);
                        x = problem_->EvaluateF(k, x, u);
                    }
                    curr_cost = LineSearchAndEvaluateCost(
                        iteration, curr_xs, curr_us, line_search_full_dxs,
                        line_search_full_dus, curr_alpha, &oi);

                    ++alpha_idx;
                    ++line_search_count;
                } while ((curr_cost >
                          line_search_init_cost - min_acceptable_cost_drop) &&
                         alpha_idx < alpha_count);
            }

            if (curr_cost > line_search_init_cost - min_acceptable_cost_drop) {
                int k_stepsize = -k_n_e;

                do {
                    curr_xs = xs;
                    curr_us = us;
                    k_stepsize = (k_stepsize + k_n_e) >> 1;
                    StateType x = PROB::GetStateAtStep(curr_xs, k_stepsize);
                    for (int k = k_stepsize; k < horizon_; ++k) {
                        PROB::SetStateAtStep(x, k, &curr_xs);
                        const StateType dx = x - PROB::GetStateAtStep(xs, k);
                        const ControlType du =
                            PROB::GetControlAtStep(line_search_dus_open, k) +
                            line_search_dus_close_gain[k] * dx;
                        const ControlType u =
                            PROB::GetControlAtStep(us, k) + du;
                        PROB::SetControlAtStep(u, k, &curr_us);
                        x = problem_->EvaluateF(k, x, u);
                    }

                    curr_cost = StepSizeAdjustmentAndEvaluateCost(
                        iteration, curr_xs, curr_us, k_stepsize, &oi);

                } while ((curr_cost >
                          line_search_init_cost - min_acceptable_cost_drop) &&
                         k_stepsize < (k_n_e - 1));
            }

            if (params_.line_search_min_alpha() >= 1.0) {
                dcost = curr_cost - total_cost;
                total_cost = curr_cost;
                tentative_xs = curr_xs;
                tentative_us = curr_us;
            } else if (curr_cost >
                       line_search_init_cost - min_acceptable_cost_drop) {
                tentative_xs = xs;
                tentative_us = us;

                if (!params_.line_search_to_min()) {
                    for (auto *hook : hooks_) {
                        hook->OnLineSearchIterationStart(
                            iteration, tentative_xs, tentative_us,
                            line_search_full_dxs, line_search_full_dus,
                            curr_alpha, oi);
                    }
                }
            } else {
                dcost = curr_cost - total_cost;
                total_cost = curr_cost;
                tentative_xs = curr_xs;
                tentative_us = curr_us;

                constexpr double kLineSearchDecayFactor = 2.0 / 3.0;
                const int alpha_idx_offset = -1;
                alpha_idx =
                    params_.enable_adaptive_alpha()
                        ? std::max(
                              1, static_cast<int>(
                                     floor(alpha_idx * kLineSearchDecayFactor) +
                                     alpha_idx_offset))
                        : 1;
            }

            if (params_.line_search_to_min()) {
                for (auto *hook : hooks_) {
                    hook->OnLineSearchIterationStart(
                        iteration, tentative_xs, tentative_us,
                        line_search_full_dxs, line_search_full_dus, curr_alpha,
                        oi);
                }
            }

            oi.cost = total_cost;
            dxs = tentative_xs - xs;
            dus = (tentative_us - us);
            xs = tentative_xs;
            us = tentative_us;
            // DDPVLOG(3) << "End of line search : cost = " << total_cost;
        }

        total_cost = EvaluateCost(xs, us, &oi.named_costs);
        oi.cost = total_cost;
        oi.js0 = Js0;

        final_cost_debug.clear();
        // DDPVLOG(2) << "Total cost: " << total_cost;
        std::string prefix;
        const std::string final_cost_debug_first_line =
            is_compare_weight
                ? prefix + " Compare weight Total cost: " +
                      std::to_string(total_cost)
                : prefix + " Total cost: " + std::to_string(total_cost);
        final_cost_debug.push_back(
            prefix + " Total cost: " + std::to_string(total_cost));
#if ENABLE_DDP_OPTIMIZER_DEBUG_COST_STRING
        for (size_t idx = 0; idx < oi.named_costs.size(); ++idx) {
            const auto &entry = oi.named_costs[idx];
            const std::string &cost_name = entry.name;
            double cost = entry.value;
            bool is_soft = entry.is_soft;
            std::string debug_stream = absl::StrFormat(
                "  [%s]\t cost: %f\t is_soft: %d", cost_name, cost, is_soft);
            // DDPVLOG(2) << debug_stream;
            final_cost_debug.push_back(std::move(debug_stream));
        }
#endif

        for (auto *hook : hooks_) {
            hook->OnIterationEnd(iteration, xs, us, oi);
        }

        if (du_converged) {
            break;
        }
        if (dx_converged) {
            break;
        }
        if (std::abs(dcost) < params_.convergence_tolerance_dcost()) {
            constexpr double drop_failed_js0_cost = 2.0;
            if (((total_cost - Js0) > drop_failed_js0_cost) &&
                (owner_ == "trajectory_optimizer")) {
            }
            break;
        }
    }

    {
        constexpr int kLineSearchQeventRecordLimit = 50;
        if (line_search_count >= kLineSearchQeventRecordLimit) {
            if (owner_ == "trajectory_optimizer" && config.enable_qevent) {
            }
        }
    }

    if (owner_ == kTrajectoryOptimizerOwner) {
        final_cost_debug.push_back("  iteration :" + std::to_string(iteration));
    }
    // DDPVLOG(2) << "Final cost: " << total_cost;
    final_cost_debug_ = std::move(final_cost_debug);
    final_total_cost_ = total_cost;

    // ============= 控制量修正 =============
    if (iteration > 0 || config.enable_iteration_failure_postprocess) {
        StateType x = x0;
        for (int k = 0; k < horizon_; ++k) {
            PROB::SetStateAtStep(x, k, &xs);
            ControlType u;
            ClampInfo state_clamp_info, control_clamp_info;
            u = problem_->PostProcessLonU(
                k, PROB::GetControlAtStep(us, k), x,
                k != horizon_ - 1
                    ? PROB::GetStateAtStep(xs, k + 1)
                    : problem_->EvaluateF(k, x, PROB::GetControlAtStep(us, k)),
                &control_clamp_info, config.forward);
            PROB::SetControlAtStep(u, k, &us);
            const auto x_origin = problem_->EvaluateF(k, x, u);
            x = problem_->PostProcessLonX(k, x_origin, u, &state_clamp_info);
        }
    }

    for (auto *hook : hooks_) {
        hook->OnSolveEnd(xs, us, oi);
    }

    // ============= 提取优化轨迹 =============
    std::vector<TrajectoryPoint> res =
        GenerateTrajectoryPointsFromSolverStates(xs, us, config.forward);
    if (UNLIKELY(PNC_VLOG_IS_ON(3))) {
        for (int k = 0; k < horizon_; ++k) {
        }
    }

    return res;
}

template <typename PROB>
void DdpOptimizer<PROB>::FitTrajectoryPointToSolverStates(
    std::vector<TrajectoryPoint> trajectory,
    StateType *x0,
    ControlsType *us,
    StatesType *xs) const {
    if (!XCHECK_NOTNULL(x0) || !XCHECK_NOTNULL(us) || !XCHECK_NOTNULL(xs)) {
        return;
    }

    {
        XCHECK_GE(trajectory.size(), horizon_);
        for (int k = 0; k < horizon_; ++k) {
            k <= dense_horizon_
                ? trajectory[k].set_t(k * problem_->dense_dt())
                : trajectory[k].set_t(dense_horizon_ * problem_->dense_dt() +
                                      (k - dense_horizon_) *
                                          problem_->sparse_dt());
        }

        // 第一个点归一化，避免数值突变
        trajectory.front().set_theta(
            trajectory[1].theta() +
            NormalizeAngle(trajectory.front().theta() - trajectory[1].theta()));
    }

    *x0 = problem_->FitInitialState(trajectory);
    *us = problem_->FitControl(trajectory, *x0);
    *xs = problem_->FitState(trajectory);
}

template <typename PROB>
std::vector<TrajectoryPoint>
DdpOptimizer<PROB>::GenerateTrajectoryPointsFromSolverStates(
    const StatesType &xs, const ControlsType &us, bool s_increasing) const {
    std::vector<TrajectoryPoint> res;
    res.resize(horizon_);
    for (int k = 0; k < horizon_; ++k) {
        TrajectoryPoint &point = res[k];
        problem_->ExtractTrajectoryPoint(k, PROB::GetStateAtStep(xs, k),
                                         PROB::GetControlAtStep(us, k), &point);
    }

    if (problem_->enable_post_process()) {
        res.front().set_s(0.0);
        for (int i = 1; i < horizon_; ++i) {
            const double d = (res[i].pos() - res[i - 1].pos()).norm();
            if (s_increasing) {
                res[i].set_s(res[i - 1].s() + d);
            } else {
                res[i].set_s(res[i - 1].s() - d);
            }
        }
    }

    return res;
}

template <typename PROB>
double DdpOptimizer<PROB>::EvaluateCost(
    const StatesType &xs,
    const ControlsType &us,
    std::vector<NamedCostEntry> *named_costs) const {
    std::vector<double> costs(problem_->costs().size(), 0.0);

    if (named_costs != nullptr) { named_costs->clear(); }

    for (int i = 0; i < problem_->costs().size(); ++i) {
        const auto divided_g =
            problem_->costs()[i]->SumGForAllSteps(xs, us, horizon_);
        costs[i] += divided_g.sum();
        if (named_costs != nullptr) {
            for (const auto &cost : divided_g.gs()) {
                named_costs->push_back(cost);
            }
        }
    }
    const double total_cost = std::accumulate(costs.begin(), costs.end(), 0.0);

    return total_cost;
}

template <typename PROB>
double DdpOptimizer<PROB>::LineSearchAndEvaluateCost(
    int iteration,
    const StatesType &tentative_xs,
    const ControlsType &tentative_us,
    const StatesType &full_dxs,
    const ControlsType &full_dus,
    double alpha,
    typename HookType::OptimizerInspector *oi) const {
    for (auto *hook : hooks_) {
        hook->OnLineSearchIterationStart(iteration, tentative_xs, tentative_us,
                                         full_dxs, full_dus, alpha, *oi);
    }
    const double cost = EvaluateCost(tentative_xs, tentative_us);
    oi->cost = cost;
    for (auto *hook : hooks_) {
        hook->OnLineSearchIterationEnd(iteration, tentative_xs, tentative_us,
                                       full_dxs, full_dus, alpha, cost, *oi);
    }
    return cost;
}

template <typename PROB>
double DdpOptimizer<PROB>::StepSizeAdjustmentAndEvaluateCost(
    int iteration,
    const StatesType &xs,
    const ControlsType &us,
    int k_stepsize,
    typename HookType::OptimizerInspector *oi) const {
    for (auto *hook : hooks_) {
        hook->OnStepSizeAdjustmentIterationStart(iteration, xs, us, k_stepsize,
                                                 *oi);
    }
    const double cost = EvaluateCost(xs, us);
    oi->cost = cost;
    for (auto *hook : hooks_) {
        hook->OnStepSizeAdjustmentIterationEnd(iteration, xs, us, k_stepsize,
                                               cost, *oi);
    }
    return cost;
}

// #undef DDPVLOG
}  // namespace planning
}  // namespace pnc_x
