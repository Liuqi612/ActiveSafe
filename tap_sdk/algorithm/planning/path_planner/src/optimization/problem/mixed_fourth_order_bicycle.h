
#pragma once

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <limits>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "math/fast_math.h"
#include "math/util.h"
#include "math/vec.h"
#include "optimization/problem/cost.h"
#include "optimization/problem/cost_helper.h"
#include "plan/trajectory_point.h"
#include "pncx_planner_params.pb.h"
#include "pncx_vehicle.pb.h"
#include "common/log.h"

namespace pnc_x {
namespace planning {

class MixedFourthOrderBicycle {
 public:
    struct ClampInfo {
        std::vector<int> indice;
        std::vector<std::pair<double, double>> values;
    };

 public:
    MixedFourthOrderBicycle(
        const MotionConstraintParamsProto *motion_constraint_params,
        const VehicleGeometryParamsProto *val_veh_geo_params,
        const VehicleDriveParamsProto *val_veh_drive_params,
        int val_dense_horizon,
        int val_sparse_horizon,
        double dense_trajectory_time_step,
        double sparse_trajectory_time_step,
        bool val_enable_dynamic_2nd_derivatives,
        bool val_enable_post_process)
        : motion_constraint_params_(motion_constraint_params),
          veh_geo_params_(val_veh_geo_params),
          veh_drive_params_(val_veh_drive_params),
          dense_horizon_(val_dense_horizon),
          sparse_horizon_(val_sparse_horizon),
          horizon_(dense_horizon_ + sparse_horizon_),
          dense_dt_(dense_trajectory_time_step),
          sparse_dt_(sparse_trajectory_time_step),
          enable_dynamic_2nd_derivatives_(val_enable_dynamic_2nd_derivatives),
          enable_post_process_(val_enable_post_process){
        XCHECK_GT(dense_horizon_, 0);

        XCHECK_GT(horizon_, 0);
    }

    static constexpr char kProblemPrefix[] = "Mfob";

    static constexpr int kStateSize = 8;
    static constexpr int kStateXIndex = 0;
    static constexpr int kStateYIndex = 1;
    static constexpr int kStateThetaIndex = 2;
    static constexpr int kStateVIndex = 3;
    static constexpr int kStateKappaIndex = 4;
    static constexpr int kStateAIndex = 5;
    static constexpr int kStatePsiIndex = 6;
    static constexpr int kStateSIndex = 7;

    static constexpr int kControlSize = 2;
    static constexpr int kControlChiIndex = 0;
    static constexpr int kControlJIndex = 1;

    static constexpr double kMinSpeed = 1e-6;
    static constexpr double kMaxSpeed = std::numeric_limits<double>::infinity();

    using StateType = Eigen::Matrix<double, kStateSize, 1>;
    using ControlType = Eigen::Matrix<double, kControlSize, 1>;
    using StatesType = Eigen::Matrix<double, Eigen::Dynamic, 1>;
    using ControlsType = Eigen::Matrix<double, Eigen::Dynamic, 1>;

    using GType = double;
    using DGDxType = Eigen::Matrix<double, 1, kStateSize>;
    using DGDuType = Eigen::Matrix<double, 1, kControlSize>;
    using DDGDxDxType = Eigen::Matrix<double, kStateSize, kStateSize>;
    using DDGDxDuType = Eigen::Matrix<double, kStateSize, kControlSize>;
    using DDGDuDxType = Eigen::Matrix<double, kControlSize, kStateSize>;
    using DDGDuDuType = Eigen::Matrix<double, kControlSize, kControlSize>;

    using FType = StateType;
    using DFDxType = Eigen::Matrix<double, kStateSize, kStateSize>;
    using DFDuType = Eigen::Matrix<double, kStateSize, kControlSize>;

    using DDFDxDxType = std::array<DDGDxDxType, kStateSize>;
    using DDFDxDuType = std::array<DDGDxDuType, kStateSize>;
    using DDFDuDxType = std::array<DDGDuDxType, kStateSize>;
    using DDFDuDuType = std::array<DDGDuDuType, kStateSize>;

    static StateType MakeState(double pos_x,
                               double pos_y,
                               double val_theta,
                               double val_v,
                               double val_kappa,
                               double val_a,
                               double val_psi,
                               double val_s) {
        StateType local_state;
        StateSetX(pos_x, &local_state);
        StateSetY(pos_y, &local_state);
        StateSetTheta(val_theta, &local_state);
        StateSetV(val_v, &local_state);
        StateSetKappa(val_kappa, &local_state);
        StateSetA(val_a, &local_state);
        StateSetS(val_s, &local_state);
        StateSetPsi(val_psi, &local_state);
        return local_state;
    }

    static StateType TestState() {
        return MakeState(1.0, 0.5, 0.0, 1.0, 0.1, 0.1, 0.05, 0.4);
    }

    static ControlType MakeControl(double val_chi, double val_j) {
        ControlType u;
        ControlSetChi(val_chi, &u);
        ControlSetJ(val_j, &u);
        return u;
    }

    static ControlType TestControl() { return MakeControl(0.01, 0.05); }

    static double StateGetX(const StateType &val_state) { return val_state[kStateXIndex]; }
    static double StateGetY(const StateType &val_state) { return val_state[kStateYIndex]; }
    static Vec2d StateGetPos(const StateType &val_state) {
        return Vec2d(val_state[kStateXIndex], val_state[kStateYIndex]);
    }
    static double StateGetTheta(const StateType &val_state) {
        return val_state[kStateThetaIndex];
    }
    static double StateGetV(const StateType &val_state) { return val_state[kStateVIndex]; }
    static double StateGetKappa(const StateType &val_state) {
        return val_state[kStateKappaIndex];
    }
    static double StateGetA(const StateType &val_state) { return val_state[kStateAIndex]; }
    static double StateGetS(const StateType &val_state) { return val_state[kStateSIndex]; }
    static double StateGetPsi(const StateType &val_state) { return val_state[kStatePsiIndex]; }
    static void StateSetX(double pos_x, StateType *val_state) {
        (*val_state)[kStateXIndex] = pos_x;
    }
    static void StateSetY(double pos_y, StateType *val_state) {
        (*val_state)[kStateYIndex] = pos_y;
    }
    static void StateSetPos(const Vec2d &val_pos, StateType *val_state) {
        (*val_state)[kStateXIndex] = val_pos.x();
        (*val_state)[kStateYIndex] = val_pos.y();
    }
    static void StateSetTheta(double val_theta, StateType *val_state) {
        (*val_state)[kStateThetaIndex] = val_theta;
    }
    static void StateSetV(double val_v, StateType *val_state) { (*val_state)[kStateVIndex] = val_v; }
    static void StateSetKappa(double val_kappa, StateType *val_state) {
        (*val_state)[kStateKappaIndex] = val_kappa;
    }
    static void StateSetA(double val_a, StateType *val_state) { (*val_state)[kStateAIndex] = val_a; }
    static void StateSetS(double val_s, StateType *val_state) { (*val_state)[kStateSIndex] = val_s; }
    static void StateSetPsi(double val_psi, StateType *val_state) {
        (*val_state)[kStatePsiIndex] = val_psi;
    }

    static double ControlGetChi(const ControlType &u) {
        return u[kControlChiIndex];
    }
    static double ControlGetJ(const ControlType &u) {
        return u[kControlJIndex];
    }
    static void ControlSetChi(double val_chi, ControlType *u) {
        (*u)[kControlChiIndex] = val_chi;
    }
    static void ControlSetJ(double val_j, ControlType *u) {
        (*u)[kControlJIndex] = val_j;
    }

    static StateType GetStateAtStep(const StatesType &xs, int k) {
        return xs.template segment<kStateSize>(k * kStateSize);
    }
    static Eigen::Map<const StateType> GetStateMapAtStep(const StatesType &xs,
                                                         int k) {
        return Eigen::Map<const StateType>(xs.data() + k * kStateSize,
                                           kStateSize);
    }
    static Eigen::Map<const StateType> GetStatesBeforeStep(const StatesType &xs,
                                                           int k) {
        return Eigen::Map<const StateType>(xs.data(), k * kStateSize);
    }
    static ControlType GetControlAtStep(const ControlsType &us, int k) {
        return us.template segment<kControlSize>(k * kControlSize);
    }
    static Eigen::Map<const ControlsType> GetControlMapAtStep(
        const ControlsType &us, int k) {
        return Eigen::Map<const ControlsType>(us.data() + k * kControlSize,
                                              kControlSize);
    }
    static Eigen::Map<const ControlsType> GetControlsBeforeStep(
        const ControlsType &us, int k) {
        return Eigen::Map<const ControlsType>(us.data(), k * kControlSize);
    }
    static void SetStateAtStep(const StateType &val_x, int k, StatesType *xs) {
        xs->template segment<kStateSize>(k * kStateSize) = val_x;
    }
    static void SetControlAtStep(const ControlType &u,
                                 int k,
                                 ControlsType *us) {
        us->template segment<kControlSize>(k * kControlSize) = u;
    }

    static double x(const StatesType &xs, int k) {
        return xs[k * kStateSize + kStateXIndex];
    }
    static double y(const StatesType &xs, int k) {
        return xs[k * kStateSize + kStateYIndex];
    }
    static Vec2d pos(const StatesType &xs, int k) {
        return Vec2d(xs(k * kStateSize + kStateXIndex),
                     xs(k * kStateSize + kStateYIndex));
    }
    static double theta(const StatesType &xs, int k) {
        return xs[k * kStateSize + kStateThetaIndex];
    }
    static double v(const StatesType &xs, int k) {
        return xs[k * kStateSize + kStateVIndex];
    }
    static double kappa(const StatesType &xs, int k) {
        return xs[k * kStateSize + kStateKappaIndex];
    }
    static double a(const StatesType &xs, int k) {
        return xs[k * kStateSize + kStateAIndex];
    }
    static double s(const StatesType &xs, int k) {
        return xs[k * kStateSize + kStateSIndex];
    }
    static double psi(const StatesType &xs, int k) {
        return xs[k * kStateSize + kStatePsiIndex];
    }
    static double chi(const ControlsType &us, int k) {
        return us[k * kControlSize + kControlChiIndex];
    }
    static double j(const ControlsType &us, int k) {
        return us[k * kControlSize + kControlJIndex];
    }

    static void set_x(double val_x, int k, StatesType *xs) {
        (*xs)[k * kStateSize + kStateXIndex] = val_x;
    }
    static void set_y(double val_y, int k, StatesType *xs) {
        (*xs)[k * kStateSize + kStateYIndex] = val_y;
    }
    static void set_pos(const Vec2d &val_pos, int k, StatesType *xs) {
        (*xs)(k * kStateSize + kStateXIndex) = val_pos.x();
        (*xs)(k * kStateSize + kStateYIndex) = val_pos.y();
    }
    static void set_theta(double val_theta, int k, StatesType *xs) {
        (*xs)[k * kStateSize + kStateThetaIndex] = val_theta;
    }
    static void set_v(double val_v, int k, StatesType *xs) {
        (*xs)[k * kStateSize + kStateVIndex] = val_v;
    }
    static void set_kappa(double val_kappa, int k, StatesType *xs) {
        (*xs)[k * kStateSize + kStateKappaIndex] = val_kappa;
    }
    static void set_a(double val_a, int k, StatesType *xs) {
        (*xs)[k * kStateSize + kStateAIndex] = val_a;
    }
    static void set_s(double val_s, int k, StatesType *xs) {
        (*xs)[k * kStateSize + kStateSIndex] = val_s;
    }
    static void set_psi(double val_psi, int k, StatesType *xs) {
        (*xs)[k * kStateSize + kStatePsiIndex] = val_psi;
    }
    static void set_chi(double val_chi, int k, ControlsType *us) {
        (*us)[k * kControlSize + kControlChiIndex] = val_chi;
    }
    static void set_j(double val_j, int k, ControlsType *us) {
        (*us)[k * kControlSize + kControlJIndex] = val_j;
    }

    double dense_dt() const { return dense_dt_; }
    double sparse_dt() const { return sparse_dt_; }

    bool enable_post_process() const { return enable_post_process_; }
    bool enable_dynamic_2nd_derivatives() const {
        return enable_dynamic_2nd_derivatives_;
    }

    struct FDerivatives {
        FType value;
        DFDxType dfdx;
        DFDuType dfdu;
        DDFDxDxType ddfdxdx;
        DDFDuDxType ddfdudx;
        DDFDuDuType ddfdudu;
        FDerivatives() {
            value = FType::Zero();
            dfdx = DFDxType::Zero();
            dfdu = DFDuType::Zero();
            ddfdxdx.fill(DDGDxDxType::Zero());
            ddfdudx.fill(DDGDuDxType::Zero());
            ddfdudu.fill(DDGDuDuType::Zero());
        }
    };
    void EvaluateFDerivatives(int k,
                              const StateType &state,
                              const ControlType &u,
                              FDerivatives *fd) const {
        const double dt = (k < dense_horizon_) ? dense_dt_ : sparse_dt_;
        const double kSquareDt = Sqr(dt);
        const double kCubicDt = Cube(dt);
        const double kQuarticDt = Quar(dt);

        const double pos_x = StateGetX(state);
        const double pos_y = StateGetY(state);
        const double local_theta = StateGetTheta(state);
        const double local_v = StateGetV(state);
        const double local_kappa = StateGetKappa(state);
        const double local_a = StateGetA(state);
        const double local_s = StateGetS(state);
        const double local_psi = StateGetPsi(state);
        const double local_chi = ControlGetChi(u);
        const double local_j = ControlGetJ(u);

        const double half_da = 0.5 * local_j * dt;
        const double halfway_a = local_a + half_da;
        const double half_dv = 0.5 * halfway_a * dt;
        const double halfway_v = local_v + half_dv;
        const double half_dpsi = 0.5 * local_chi * dt;
        const double halfway_psi = local_psi + half_dpsi;
        const double half_dkappa = 0.5 * halfway_psi * dt;
        const double halfway_kappa = local_kappa + half_dkappa;
        const double half_dtheta = 0.5 * halfway_v * halfway_kappa * dt;
        const double halfway_theta = local_theta + half_dtheta;
        const double cos_halfway_theta = std::cos(halfway_theta);
        const double sin_halfway_theta = std::sin(halfway_theta);

        const double next_pos_x = pos_x + halfway_v * cos_halfway_theta * dt;
        const double next_pos_y = pos_y + halfway_v * sin_halfway_theta * dt;
        const double next_theta = halfway_theta + half_dtheta;
        const double next_v = halfway_v + half_dv;
        const double next_kappa = halfway_kappa + half_dkappa;
        const double next_psi = halfway_psi + half_dpsi;
        const double next_a = halfway_a + half_da;
        const double next_s =
            local_s + local_v * dt + 0.5 * local_a * kSquareDt +
            local_j * kCubicDt / 6.0;

        StateSetX(next_pos_x, &fd->value);
        StateSetY(next_pos_y, &fd->value);
        StateSetTheta(next_theta, &fd->value);
        StateSetV(next_v, &fd->value);
        StateSetKappa(next_kappa, &fd->value);
        StateSetA(next_a, &fd->value);
        StateSetS(next_s, &fd->value);
        StateSetPsi(next_psi, &fd->value);

        DFDxType &dfdx = fd->dfdx;
        dfdx = DFDxType::Zero();
        dfdx(kStateXIndex, kStateXIndex) = 1.0;
        dfdx(kStateXIndex, kStateThetaIndex) =
            -halfway_v * sin_halfway_theta * dt;
        dfdx(kStateXIndex, kStateVIndex) =
            cos_halfway_theta * dt -
            halfway_v * sin_halfway_theta * 0.5 * halfway_kappa * kSquareDt;
        dfdx(kStateXIndex, kStateKappaIndex) =
            -halfway_v * sin_halfway_theta * 0.5 * halfway_v * kSquareDt;
        dfdx(kStateXIndex, kStateAIndex) =
            cos_halfway_theta * 0.5 * kSquareDt -
            halfway_v * sin_halfway_theta * 0.25 * halfway_kappa * kCubicDt;
        dfdx(kStateXIndex, kStatePsiIndex) =
            -halfway_v * sin_halfway_theta * 0.25 * halfway_v * kCubicDt;
        dfdx(kStateYIndex, kStateYIndex) = 1.0;
        dfdx(kStateYIndex, kStateThetaIndex) =
            halfway_v * cos_halfway_theta * dt;
        dfdx(kStateYIndex, kStateVIndex) =
            sin_halfway_theta * dt +
            halfway_v * cos_halfway_theta * 0.5 * halfway_kappa * kSquareDt;
        dfdx(kStateYIndex, kStateKappaIndex) =
            halfway_v * cos_halfway_theta * 0.5 * halfway_v * kSquareDt;
        dfdx(kStateYIndex, kStatePsiIndex) =
            halfway_v * cos_halfway_theta * 0.25 * halfway_v * kCubicDt;
        dfdx(kStateYIndex, kStateAIndex) =
            sin_halfway_theta * 0.5 * kSquareDt +
            halfway_v * cos_halfway_theta * 0.25 * halfway_kappa * kCubicDt;
        dfdx(kStateThetaIndex, kStateThetaIndex) = 1.0;
        dfdx(kStateThetaIndex, kStateVIndex) = halfway_kappa * dt;
        dfdx(kStateThetaIndex, kStateKappaIndex) = halfway_v * dt;
        dfdx(kStateThetaIndex, kStatePsiIndex) = 0.5 * halfway_v * kSquareDt;
        dfdx(kStateThetaIndex, kStateAIndex) = 0.5 * halfway_kappa * kSquareDt;
        dfdx(kStateVIndex, kStateVIndex) = 1.0;
        dfdx(kStateVIndex, kStateAIndex) = dt;
        dfdx(kStateKappaIndex, kStateKappaIndex) = 1.0;
        dfdx(kStateKappaIndex, kStatePsiIndex) = dt;
        dfdx(kStateAIndex, kStateAIndex) = 1.0;
        dfdx(kStateSIndex, kStateVIndex) = dt;
        dfdx(kStateSIndex, kStateAIndex) = 0.5 * kSquareDt;
        dfdx(kStateSIndex, kStateSIndex) = 1.0;
        dfdx(kStatePsiIndex, kStatePsiIndex) = 1.0;

        DFDuType &dfdu = fd->dfdu;
        dfdu = DFDuType::Zero();
        dfdu(kStateXIndex, kControlChiIndex) =
            -halfway_v * sin_halfway_theta * 0.125 * halfway_v * kQuarticDt;
        dfdu(kStateXIndex, kControlJIndex) =
            cos_halfway_theta * 0.25 * kCubicDt -
            halfway_v * sin_halfway_theta * 0.125 * halfway_kappa * kQuarticDt;
        dfdu(kStateYIndex, kControlChiIndex) =
            halfway_v * cos_halfway_theta * 0.125 * halfway_v * kQuarticDt;
        dfdu(kStateYIndex, kControlJIndex) =
            sin_halfway_theta * 0.25 * kCubicDt +
            halfway_v * cos_halfway_theta * 0.125 * halfway_kappa * kQuarticDt;
        dfdu(kStateThetaIndex, kControlChiIndex) = 0.25 * halfway_v * kCubicDt;
        dfdu(kStateThetaIndex, kControlJIndex) =
            0.25 * halfway_kappa * kCubicDt;
        dfdu(kStateVIndex, kControlJIndex) = 0.5 * kSquareDt;
        dfdu(kStateKappaIndex, kControlChiIndex) = 0.5 * kSquareDt;
        dfdu(kStateAIndex, kControlJIndex) = dt;
        dfdu(kStatePsiIndex, kControlChiIndex) = dt;
        dfdu(kStateSIndex, kControlJIndex) = kCubicDt / 6.0;

        if (!enable_dynamic_2nd_derivatives_) { return; }
        DDFDxDxType &ddfdxdx = fd->ddfdxdx;
        for (std::size_t i = 0U; i < kStateSize; ++i) ddfdxdx[i] = DDGDxDxType::Zero();
        DDFDuDxType &ddfdudx = fd->ddfdudx;
        for (std::size_t i = 0U; i < kStateSize; ++i) ddfdudx[i] = DDGDuDxType::Zero();
        DDFDuDuType &ddfdudu = fd->ddfdudu;
        for (std::size_t i = 0U; i < kStateSize; ++i) ddfdudu[i] = DDGDuDuType::Zero();
    }

    void EvaluateFDerivativesForAllSteps(const StatesType &xs,
                                         const ControlsType &us,
                                         std::vector<FDerivatives> *fds) const {
        if (!XCHECK_NOTNULL(fds)) {
            return;
        }
        const std::size_t fds_size = static_cast<std::size_t>(horizon_);
        fds->resize(fds_size);
        for (int k = 0; k < horizon_; ++k) {
            const std::size_t step_index = static_cast<std::size_t>(k);
            EvaluateFDerivatives(k, GetStateAtStep(xs, k),
                                 GetControlAtStep(us, k), &(*fds)[step_index]);
        }
    }

    FType EvaluateF(int k, const StateType &state, const ControlType &u) const {
        const double dt = (k < dense_horizon_) ? dense_dt_ : sparse_dt_;
        return EvaluateF(k, state, u, dt);
    }

    static FType EvaluateF(int k,
                           const StateType &state,
                           const ControlType &u,
                           double dt) {
        const double pos_x = StateGetX(state);
        const double pos_y = StateGetY(state);
        const double local_theta = StateGetTheta(state);
        const double local_v = StateGetV(state);
        const double local_kappa = StateGetKappa(state);
        const double local_a = StateGetA(state);
        const double local_s = StateGetS(state);
        const double local_psi = StateGetPsi(state);
        const double local_chi = ControlGetChi(u);
        const double local_j = ControlGetJ(u);

        const double half_da = 0.5 * local_j * dt;
        const double halfway_a = local_a + half_da;
        const double half_dv = 0.5 * halfway_a * dt;
        const double halfway_v = local_v + half_dv;
        const double half_dpsi = 0.5 * local_chi * dt;
        const double halfway_psi = local_psi + half_dpsi;
        const double half_dkappa = 0.5 * local_psi * dt + 0.25 * local_chi * Sqr(dt);
        const double halfway_kappa = local_kappa + half_dkappa;
        const double half_dtheta = 0.5 * halfway_v * halfway_kappa * dt;
        const double halfway_theta = local_theta + half_dtheta;
        const double cos_halfway_theta = std::cos(halfway_theta);
        const double sin_halfway_theta = std::sin(halfway_theta);

        constexpr double kMaxValue = 1e50;

        const double next_pos_x = boost::algorithm::clamp(
            pos_x + halfway_v * cos_halfway_theta * dt, -kMaxValue, kMaxValue);
        const double next_pos_y = boost::algorithm::clamp(
            pos_y + halfway_v * sin_halfway_theta * dt, -kMaxValue, kMaxValue);
        const double next_theta = boost::algorithm::clamp(
            halfway_theta + half_dtheta, -kMaxValue, kMaxValue);
        const double next_v =
            boost::algorithm::clamp(halfway_v + half_dv, -kMaxValue, kMaxValue);
        const double next_kappa = boost::algorithm::clamp(
            halfway_kappa + half_dkappa, -kMaxValue, kMaxValue);
        const double next_psi = boost::algorithm::clamp(halfway_psi + half_dpsi,
                                                        -kMaxValue, kMaxValue);
        const double next_a =
            boost::algorithm::clamp(halfway_a + half_da, -kMaxValue, kMaxValue);
        const double next_s = boost::algorithm::clamp(
            local_s + local_v * dt + 0.5 * local_a * Sqr(dt) +
            local_j * Cube(dt) / 6.0, -kMaxValue, kMaxValue);

        FType next_x = FType::Zero();
        StateSetX(next_pos_x, &next_x);
        StateSetY(next_pos_y, &next_x);
        StateSetTheta(next_theta, &next_x);
        StateSetV(next_v, &next_x);
        StateSetKappa(next_kappa, &next_x);
        StateSetA(next_a, &next_x);
        StateSetS(next_s, &next_x);
        StateSetPsi(next_psi, &next_x);
        return next_x;
    }

    struct GDerivatives {
        GType value;
        DGDxType dgdx;
        DGDuType dgdu;
        DDGDxDxType ddgdxdx;
        DDGDuDxType ddgdudx;
        DDGDuDuType ddgdudu;
    };
    void EvaluateGDerivatives(int k,
                              const StateType &state,
                              const ControlType &u,
                              GDerivatives *gd) const {
        gd->value = 0.0;
        gd->dgdx = DGDxType::Zero();
        gd->dgdu = DGDuType::Zero();
        gd->ddgdxdx = DDGDxDxType::Zero();
        gd->ddgdudx = DDGDuDxType::Zero();
        gd->ddgdudu = DDGDuDuType::Zero();
        for (const auto &cost : costs_) {
            gd->value += cost->EvaluateG(k, state, u);
            gd->dgdx += cost->EvaluateDGDx(k, state, u);
            gd->dgdu += cost->EvaluateDGDu(k, state, u);
            gd->ddgdxdx += cost->EvaluateDDGDxDx(k, state, u);
            gd->ddgdudx += cost->EvaluateDDGDuDx(k, state, u);
            gd->ddgdudu += cost->EvaluateDDGDuDu(k, state, u);
        }
    }

    void EvaluateGDerivativesForAllSteps(const StatesType &xs,
                                         const ControlsType &us,
                                         std::vector<GDerivatives> *gds) const {
        if (!XCHECK_NOTNULL(gds)) {
            return;
        }
        const std::size_t gds_size = static_cast<std::size_t>(horizon_);
        gds->resize(gds_size);
        for (int k = 0; k < horizon_; ++k) {
            const std::size_t step_index = static_cast<std::size_t>(k);
            EvaluateGDerivatives(k, GetStateAtStep(xs, k),
                                 GetControlAtStep(us, k), &(*gds)[step_index]);
        }
    }

    void AddGDerivatives(int k,
                         const StateType &state,
                         const ControlType &u,
                         GDerivatives *gd) const {
        gd->value = 0.0;
        gd->dgdx = DGDxType::Zero();
        gd->dgdu = DGDuType::Zero();
        gd->ddgdxdx = DDGDxDxType::Zero();
        gd->ddgdudx = DDGDuDxType::Zero();
        gd->ddgdudu = DDGDuDuType::Zero();
        for (const auto &cost : costs_) {
            gd->value += cost->EvaluateG(k, state, u);
            cost->AddDGDx(k, state, u, &gd->dgdx);
            cost->AddDGDu(k, state, u, &gd->dgdu);
            cost->AddDDGDxDx(k, state, u, &gd->ddgdxdx);
            cost->AddDDGDuDx(k, state, u, &gd->ddgdudx);
            cost->AddDDGDuDu(k, state, u, &gd->ddgdudu);
        }
    }

    void AddGDerivativesForAllSteps(const StatesType &xs,
                                    const ControlsType &us,
                                    std::vector<GDerivatives> *gds) const {
        if (!XCHECK_NOTNULL(gds)) {
            return;
        }
        const std::size_t gds_size = static_cast<std::size_t>(horizon_);
        gds->resize(gds_size);
        for (int k = 0; k < horizon_; ++k) {
            const std::size_t step_index = static_cast<std::size_t>(k);
            AddGDerivatives(k, GetStateAtStep(xs, k), GetControlAtStep(us, k),
                            &(*gds)[step_index]);
        }
    }

    ControlType PostProcessLonU(const int k,
                                ControlType u,
                                const StateType &state,
                                const StateType &x_next,
                                ClampInfo *control_clamp_info,
                                bool forward) const {
        if (!enable_post_process_) { return u; }
        const double dt = (k < dense_horizon_) ? dense_dt_ : sparse_dt_;
        const ControlType u_origin = u;
        static const double max_accel =
            motion_constraint_params_->max_acceleration();
        static const double max_decel =
            motion_constraint_params_->max_deceleration();
        static const double max_accel_jerk =
            motion_constraint_params_->max_accel_jerk();
        static const double max_decel_jerk =
            motion_constraint_params_->max_decel_jerk();

        const double j_fit = (StateGetA(x_next) - StateGetA(state)) / dt;
        if ((j_fit <= max_accel_jerk) && (j_fit >= max_decel_jerk) &&
            (StateGetA(x_next) <= max_accel) && (StateGetA(x_next) >= max_decel)) {
            ControlSetJ(j_fit, &u);
        }

        ControlSetJ(boost::algorithm::clamp(ControlGetJ(u),
                                            (max_decel - StateGetA(state)) / dt,
                                            (max_accel - StateGetA(state)) / dt),
                    &u);
        ControlSetJ(
            boost::algorithm::clamp(
                ControlGetJ(u),
                ((kMinSpeed - StateGetV(state)) / dt - StateGetA(state)) / (dt * 0.5),
                ((kMaxSpeed - StateGetV(state)) / dt - StateGetA(state)) / (dt * 0.5)),
            &u);
        ControlSetJ(boost::algorithm::clamp(ControlGetJ(u), max_decel_jerk,
                                            max_accel_jerk),
                    &u);
        constexpr double kEps = 1e-7;
        if (std::abs(u_origin[kControlJIndex] - u[kControlJIndex]) > kEps) {
            control_clamp_info->indice.emplace_back(kControlJIndex);
            control_clamp_info->values.emplace_back(u_origin[kControlJIndex],
                                                    u[kControlJIndex]);
        }
        return u;
    }

    StateType PostProcessLonX(const int k,
                              StateType state,
                              const ControlType &u,
                              ClampInfo *state_clamp_info) const {
        if (!enable_post_process_) { return state; }
        const double dt = (k < dense_horizon_) ? dense_dt_ : sparse_dt_;
        const StateType x_origin = state;
        static const double max_accel =
            motion_constraint_params_->max_acceleration();
        static const double max_decel =
            motion_constraint_params_->max_deceleration();
        static const double max_accel_jerk =
            motion_constraint_params_->max_accel_jerk();
        static const double max_decel_jerk =
            motion_constraint_params_->max_decel_jerk();

        StateSetV(boost::algorithm::clamp(StateGetV(state), kMinSpeed, kMaxSpeed),
                  &state);
        StateSetA(
            boost::algorithm::clamp(
                StateGetA(state),
                (kMinSpeed - StateGetV(state)) / dt - max_accel_jerk * dt / 2.0,
                (kMaxSpeed - StateGetV(state)) / dt - max_decel_jerk * dt / 2.0),
            &state);
        StateSetA(boost::algorithm::clamp(StateGetA(state), max_decel, max_accel),
                  &state);
        constexpr double kEps = 1e-7;
        for (const int index : {kStateVIndex, kStateAIndex}) {
            if (std::abs(x_origin[index] - state[index]) > kEps) {
                state_clamp_info->indice.emplace_back(index);
                state_clamp_info->values.emplace_back(x_origin[index],
                                                      state[index]);
            }
        }
        return state;
    }

    bool CheckDu(const ControlsType &dus, const std::string &prefix) const {
        constexpr double kDuMagnitudeLimit = 1e6;
        for (Eigen::Index k = 0, n = dus.size(); k < n; ++k) {
            const double du = dus[k];
            if ((!std::isfinite(du)) || (du > kDuMagnitudeLimit) || (du < -kDuMagnitudeLimit)) {
                return false;
            }
        }
        return true;
    }

    static StateType FitInitialState(
        const std::vector<TrajectoryPoint> &init_traj_points) {
        XCHECK_GE(init_traj_points.size(), 2);
        const TrajectoryPoint &p0 = init_traj_points[0];
        StateType state;
        StateSetX(p0.pos().x(), &state);
        StateSetY(p0.pos().y(), &state);
        StateSetTheta(p0.theta(), &state);
        StateSetV(p0.v(), &state);
        StateSetKappa(p0.kappa(), &state);
        StateSetA(p0.a(), &state);
        StateSetS(p0.s(), &state);
        StateSetPsi(p0.psi(), &state);
        return state;
    }

    static StatesType FitState(
        const std::vector<TrajectoryPoint> &init_traj_points) {
        const int local_horizon = static_cast<int>(init_traj_points.size());
        StatesType xs(local_horizon * kStateSize);
        XCHECK_GT(local_horizon, 0);

        for (int k = 0; k < local_horizon; ++k) {
            const std::size_t state_index = static_cast<std::size_t>(k);
            const TrajectoryPoint &p0 = init_traj_points[state_index];
            StateType state;
            StateSetX(p0.pos().x(), &state);
            StateSetY(p0.pos().y(), &state);
            StateSetTheta(p0.theta(), &state);
            StateSetV(p0.v(), &state);
            StateSetKappa(p0.kappa(), &state);
            StateSetA(p0.a(), &state);
            StateSetS(p0.s(), &state);
            StateSetPsi(p0.psi(), &state);
            SetStateAtStep(state, k, &xs);
        }
        return xs;
    }

    static ControlsType FitControl(
        const std::vector<TrajectoryPoint> &traj_points, const StateType &x0) {
        const int local_horizon = static_cast<int>(traj_points.size());
        XCHECK_GT(local_horizon, 0);

        ControlsType us = ControlsType::Zero(local_horizon * kControlSize);
        for (int k = 0; (k + 1) < local_horizon; ++k) {
            const std::size_t current_index = static_cast<std::size_t>(k);
            const std::size_t next_index = current_index + 1U;
            const double dt =
                traj_points[next_index].t() - traj_points[current_index].t();
            const TrajectoryPoint &p0 = traj_points[current_index];
            const TrajectoryPoint &p1 = traj_points[next_index];
            set_chi((p1.psi() - p0.psi()) / dt, k, &us);
            set_j((p1.a() - p0.a()) / dt, k, &us);
        }
        set_chi(chi(us, local_horizon - 2), local_horizon - 1, &us);
        set_j(j(us, local_horizon - 2), local_horizon - 1, &us);
        return us;
    }

    StatesType RollOutControl(const StateType &x0,
                              const ControlsType &us) const {
        return RollOutControl(x0, us, dense_dt_, sparse_dt_);
    }

    StatesType RollOutControl(const StateType &x0,
                              const ControlsType &us,
                              double local_dense_dt,
                              double local_sparse_dt) const {
        StatesType xs(horizon_ * kStateSize);
        SetStateAtStep(x0, 0, &xs);
        for (int k = 0; k < dense_horizon_; ++k) {
            SetStateAtStep(EvaluateF(k, GetStateAtStep(xs, k),
                                     GetControlAtStep(us, k), local_dense_dt),
                           k + 1, &xs);
        }
        for (int k = dense_horizon_; k < horizon_; ++k) {
            SetStateAtStep(EvaluateF(k, GetStateAtStep(xs, k),
                                     GetControlAtStep(us, k), local_sparse_dt),
                           k + 1, &xs);
        }
        return xs;
    }

    static void ExtractTrajectoryPoint(int k,
                                       const StateType &state,
                                       const ControlType &u,
                                       const double local_dense_dt,
                                       const double local_sparse_dt,
                                       const int local_dense_horizon,
                                       const int local_sparse_horizon,
                                       TrajectoryPoint *traj_point) {
        if (traj_point == nullptr) {
            return;
        }
        const double step = static_cast<double>(k);
        const double dense_horizon_step = static_cast<double>(local_dense_horizon);
        if (k <= local_dense_horizon) {
            traj_point->set_t(local_dense_dt * step);
        } else {
            traj_point->set_t((local_dense_dt * dense_horizon_step) +
                              ((step - dense_horizon_step) * local_sparse_dt));
        }
        traj_point->set_pos(StateGetPos(state));
        traj_point->set_theta(StateGetTheta(state));
        traj_point->set_v(StateGetV(state));
        traj_point->set_kappa(StateGetKappa(state));
        traj_point->set_a(StateGetA(state));
        traj_point->set_s(StateGetS(state));
        traj_point->set_psi(StateGetPsi(state));
        traj_point->set_chi(ControlGetChi(u));
        traj_point->set_j(ControlGetJ(u));
    }

    void ExtractTrajectoryPoint(int k,
                                const StateType &local_x,
                                const ControlType &u,
                                TrajectoryPoint *traj_point) const {
        if (traj_point == nullptr) {
            return;
        }
        ExtractTrajectoryPoint(k, local_x, u, dense_dt_, sparse_dt_, dense_horizon_,
                               sparse_horizon_, traj_point);
    }

    using CostType = Cost<MixedFourthOrderBicycle>;
    void AddCost(std::unique_ptr<CostType> cost) {
        costs_.push_back(std::move(cost));
    }
    const std::vector<std::unique_ptr<CostType>> &costs() const {
        return costs_;
    }

    using CostHelperType = CostHelper<MixedFourthOrderBicycle>;
    void AddCostHelper(std::unique_ptr<CostHelperType> helper) {
        cost_helpers_.push_back(std::move(helper));
    }
    const std::vector<std::unique_ptr<CostHelperType>> &cost_helpers() const {
        return cost_helpers_;
    }

    static const std::array<double, kStateSize> &state_scales() {
        static const std::array<double, kStateSize> scales = {
            1.0, 1.0, 5.0, 0.2, 10.0, 0.4, 1.0};
        return scales;
    }
    static const std::array<double, kControlSize> &control_scales() {
        static const std::array<double, kControlSize> scales = {20.0, 1.0};
        return scales;
    }

    ControlType PurePursuitController(
        const int k,
        const StateType &state,
        const StateType &longitudinal_target,
        const StateType &lateral_target,
        const double lookahead_time,
        const double lateral_look_ahead_dist) const {
        const double dt = (k < dense_horizon_) ? dense_dt_ : sparse_dt_;
        const Vec2d local_pos = StateGetPos(state);

        const double v_target =
            (StateGetS(longitudinal_target) - StateGetS(state)) / lookahead_time;
        const double local_a = (v_target - StateGetV(state)) / dt;
        const double local_j = (local_a - StateGetA(state)) / dt;

        const Vec2d lateral_target_pos = StateGetPos(lateral_target);
        const double local_theta = StateGetTheta(state);
        const double alpha =
            Vec2d(lateral_target_pos - local_pos).FastAngle() - local_theta;
        const double local_kappa =
            2.0 * fast_math::SinN<12>(alpha) / lateral_look_ahead_dist;
        const double local_psi = (local_kappa - StateGetKappa(state)) / dt;
        const double local_chi = (local_psi - StateGetPsi(state)) / dt;

        ControlType u;
        ControlSetChi(local_chi, &u);
        ControlSetJ(local_j, &u);
        return u;
    }

    static std::string ControlIndexToName(int index) {
        switch (index) {
            case kControlChiIndex:
                return "chi";
            case kControlJIndex:
                return "j";
            default:
                // LOG(FATAL) << "Not Control Index: [" << index << "]";
                return "";
        }
    }

    static std::string StateIndexToName(int index) {
        switch (index) {
            case kStateXIndex:
                return "x";
            case kStateYIndex:
                return "y";
            case kStateThetaIndex:
                return "theta";
            case kStateVIndex:
                return "v";
            case kStateKappaIndex:
                return "kappa";
            case kStateAIndex:
                return "a";
            case kStateSIndex:
                return "s";
            case kStatePsiIndex:
                return "psi";
            default:
                // LOG(FATAL) << "Not State Index: [" << index << "]";
                return "";
        }
    }

    int horizon() const { return horizon_; }
    int dense_horizon() const { return dense_horizon_; }
    int sparse_horizon() const { return sparse_horizon_; }

    const VehicleGeometryParamsProto *veh_geo_params() const {
        return veh_geo_params_;
    }

    const VehicleDriveParamsProto *veh_drive_params() const {
        return veh_drive_params_;
    }

 private:
    std::vector<std::unique_ptr<CostType>> costs_;
    std::vector<std::unique_ptr<CostHelperType>> cost_helpers_;
    const MotionConstraintParamsProto *motion_constraint_params_;
    const VehicleGeometryParamsProto *veh_geo_params_;
    const VehicleDriveParamsProto *veh_drive_params_;
    int dense_horizon_ = 0;
    int sparse_horizon_ = 0;
    int horizon_ = 0;
    double dense_dt_ = 0.0;
    double sparse_dt_ = 0.0;
    bool enable_post_process_ = false;
    bool enable_dynamic_2nd_derivatives_ = false;
};

}  // namespace planning
}  // namespace pnc_x
