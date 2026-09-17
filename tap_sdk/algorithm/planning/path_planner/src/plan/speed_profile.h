
#pragma once

#include <algorithm>
#include <limits>
#include <ostream>
#include <utility>
#include <vector>

#include "common/log.h"

#include "math/piecewise_linear_function.h"
#include "math/util.h"

namespace pnc_x {
namespace planning {

class SpeedProfile {
 public:
    using Plf = PiecewiseLinearFunction<double, double>;

    SpeedProfile() = default;
    explicit SpeedProfile(Plf st);

    void set_st(Plf st);
    const Plf &st() const;

    double GetSAtTime(double t) const;
    double GetVAtTime(double t) const;

    double GetTimeAtS(double s) const;

 private:
    Plf st_;
};

class PiecewiseAccelSpeedProfile {
 public:
    using Plf = PiecewiseLinearFunction<double, double>;

    PiecewiseAccelSpeedProfile() = default;

    PiecewiseAccelSpeedProfile(Plf vt, double init_s);

    PiecewiseAccelSpeedProfile(std::vector<double> s,
                               std::vector<double> t,
                               double init_v);

    PiecewiseAccelSpeedProfile(Plf vt, std::vector<double> s);

    void set_vt(Plf vt);
    const Plf &vt() const;

    double GetSAtTime(double t) const;
    double GetVAtTime(double t) const;

    void GetSVAAtTime(double t, double *s_t, double *v_t, double *a_t);

 private:
    Plf vt_;
    std::vector<double> s_;
};

}  // namespace planning
}  // namespace pnc_x
