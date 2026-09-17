
#pragma once

#include <string>

#include <absl/strings/str_format.h>

namespace pnc_x {
namespace planning {

class AttPoint {
 public:
    AttPoint() = default;

    AttPoint(double in_a, double in_dur, double in_t) : a_(in_a), dur_(in_dur), t_(in_t) {}

    double a() const { return a_; }

    double dur() const { return dur_; }

    double t() const { return t_; }

    void set_a(double in_a) { a_ = in_a; }

    void set_dur(double in_dur) { dur_ = in_dur; }

    void set_t(double in_t) { t_ = in_t; }

    std::string DebugString() const {
        return absl::StrFormat("{ t : %.6f, dur : %.6f, a : %.6f }", t_, dur_,
                               a_);
    }

 private:
    double a_ = 0.0;
    double dur_ = 0.0;

    double t_ = 0.0;
};
}  // namespace planning
}  // namespace pnc_x
