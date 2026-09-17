

#include <algorithm>
#include <limits>
#include <ostream>
#include <utility>
#include <vector>

#include "common/log.h"

#include "math/piecewise_linear_function.h"
#include "math/util.h"
#include "plan/speed_profile.h"

namespace pnc_x {
namespace planning {

SpeedProfile::SpeedProfile(Plf st) { set_st(std::move(st)); }

void SpeedProfile::set_st(Plf st) { st_ = std::move(st); }
const SpeedProfile::Plf &SpeedProfile::st() const { return st_; }

double SpeedProfile::GetSAtTime(double t) const { return st_.Evaluate(t); }
double SpeedProfile::GetVAtTime(double t) const { return st_.EvaluateSlope(t); }

double SpeedProfile::GetTimeAtS(double s) const {
    const auto &ts = st_.x();
    const auto &ss = st_.y();
    const auto it = std::lower_bound(ss.begin(), ss.end(), s);
    if (it == ss.end()) {
        return std::numeric_limits<double>::infinity();
    }
    if (it == ss.begin()) {
        return 0.0;
    }
    const size_t index = static_cast<size_t>(it - ss.begin());
    XCHECK_GT(index, 0U);
    XCHECK_LT(index, ss.size());
    XCHECK_GE(s, ss[index - 1U]);
    XCHECK_LE(s, ss[index]);
    return Lerp(ts[index - 1U], ts[index],
                LerpFactor(ss[index - 1U], ss[index], s));
}

PiecewiseAccelSpeedProfile::PiecewiseAccelSpeedProfile(Plf vt, double init_s) {
    set_vt(std::move(vt));
    XCHECK_GT(vt_.x().size(), 1);
    s_.resize(vt_.x().size());
    s_[0] = init_s;
    for (size_t i = 0; i + 1 < vt_.x().size(); ++i) {
        const double v0 = vt_.y()[i];
        const double v1 = vt_.y()[i + 1];
        const double dt = vt_.x()[i + 1] - vt_.x()[i];
        const double a = (v1 - v0) / dt;
        s_[i + 1] = s_[i] + (v0 * dt) + (0.5 * a * dt * dt);
    }
}

PiecewiseAccelSpeedProfile::PiecewiseAccelSpeedProfile(std::vector<double> s,
                                                       std::vector<double> t,
                                                       double init_v)
    : s_(std::move(s)) {
    XCHECK_GT(s_.size(), 1);
    XCHECK_EQ(s_.size(), t.size());

    std::vector<double> v(t.size());
    v[0] = init_v;
    for (size_t i = 0; i + 1 < t.size(); ++i) {
        const double s0 = s_[i];
        const double s1 = s_[i + 1];
        const double dt = t[i + 1] - t[i];
        v[i + 1] = (2 * (s1 - s0) / dt) - v[i];
    }
    set_vt(Plf(std::move(t), std::move(v)));
}

PiecewiseAccelSpeedProfile::PiecewiseAccelSpeedProfile(Plf vt,
                                                       std::vector<double> s)
    : s_(std::move(s)) {
    set_vt(std::move(vt));

    XCHECK_EQ(vt_.x().size(), s_.size());
    for (size_t i = 0; i + 1 < vt_.x().size(); ++i) {
        const double v0 = vt_.y()[i];
        const double v1 = vt_.y()[i + 1];
        const double dt = vt_.x()[i + 1] - vt_.x()[i];
        const double a = (v1 - v0) / dt;
        XCHECK_NEAR(s_[i + 1], s_[i] + (v0 * dt) + (0.5 * a * dt * dt), 1.0e-6);
    }
}

void PiecewiseAccelSpeedProfile::set_vt(Plf vt) { vt_ = std::move(vt); }
const SpeedProfile::Plf &PiecewiseAccelSpeedProfile::vt() const { return vt_; }

double PiecewiseAccelSpeedProfile::GetSAtTime(double t) const {
    const auto it = std::upper_bound(vt_.x().begin(), vt_.x().end(), t);
    if (it == vt_.x().begin()) {
        const double v = vt_.y()[0];
        const double dt = t - vt_.x()[0];
        return s_[0] + (v * dt);
    } else if (it == vt_.x().end()) {
        const double v = vt_.y().back();
        const double dt = t - vt_.x().back();
        return s_.back() + (v * dt);
    } else {
        const size_t index = static_cast<size_t>(it - vt_.x().begin()) - 1U;
        const double v = vt_.y()[index];
        const double a = (vt_.y()[index + 1U] - vt_.y()[index]) /
                         (vt_.x()[index + 1U] - vt_.x()[index]);
        const double dt = t - vt_.x()[index];
        return s_[index] + (v * dt) + (0.5 * a * dt * dt);
    }
}

double PiecewiseAccelSpeedProfile::GetVAtTime(double t) const {
    return vt_.Evaluate(t);
}

void PiecewiseAccelSpeedProfile::GetSVAAtTime(double t,
                                              double *s_t,
                                              double *v_t,
                                              double *a_t) {
    const auto it = std::upper_bound(vt_.x().begin(), vt_.x().end(), t);
    if (it == vt_.x().begin()) {
        const double v = vt_.y()[0];
        const double dt = t - vt_.x()[0];
        *a_t = 0.0;
        *v_t = v;
        *s_t = s_[0] + (v * dt);
        return;
    } else if (it == vt_.x().end()) {
        const double v = vt_.y().back();
        const double dt = t - vt_.x().back();
        *a_t = 0.0;
        *v_t = v;
        *s_t = s_.back() + (v * dt);
        return;
    } else {
        const size_t index = static_cast<size_t>(it - vt_.x().begin()) - 1U;
        const double v = vt_.y()[index];
        const double a = (vt_.y()[index + 1U] - vt_.y()[index]) /
                         (vt_.x()[index + 1U] - vt_.x()[index]);
        const double dt = t - vt_.x()[index];
        *a_t = a;
        *v_t = v + (a * dt);
        *s_t = s_[index] + (v * dt) + (0.5 * a * dt * dt);
        return;
    }
}

}  // namespace planning
}  // namespace pnc_x
