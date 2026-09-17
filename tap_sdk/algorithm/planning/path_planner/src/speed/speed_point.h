
#pragma once

#include <string>

#include "math/vec.h"
#include "pncx_speed_finder.pb.h"
#include <absl/strings/str_format.h>

namespace pnc_x {
namespace planning {

class SpeedPoint {
 public:
    SpeedPoint() = default;

    SpeedPoint(double t, double s, double v, double a, double j);

    virtual ~SpeedPoint() = default;

    double t() const;

    void set_t(double t);

    double s() const;

    void set_s(double s);

    double v() const;

    void set_v(double v);

    double a() const;

    void set_a(double a);

    double j() const;

    void set_j(double j);

    void FromProto(const SpeedPointProto &proto);
    void ToProto(SpeedPointProto *proto) const;

    std::string DebugString() const;

 private:
    double t_ = 0.0;
    double s_ = 0.0;
    double v_ = 0.0;
    double a_ = 0.0;
    double j_ = 0.0;
};

}  // namespace planning
}  // namespace pnc_x
