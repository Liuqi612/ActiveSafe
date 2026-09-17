
#pragma once

#include "pncx_initializer.pb.h"
#include "math/vec.h"
#include <absl/strings/str_cat.h>
#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace pnc_x {
namespace planning {

struct MotionState {
    Vec2d xy;
    double h = 0.0;
    double k = 0.0;
    double ref_k = 0.0;
    double t = 0.0;
    double v = 0.0;
    double a = 0.0;
    double accumulated_s = 0.0;
    double s = 0.0;
    double l = 0.0;
    boost::optional<double> dl = boost::none;
    boost::optional<double> ddl = boost::none;
    boost::optional<double> dddl = boost::none;

    std::string DebugString() const {
        return absl::StrCat("xy:", xy.DebugString(), ", h:", h, ", k:", k,
                            ", t:", t, ", v:", v, ", a:", a,
                            ", accumulated_s:", accumulated_s, ", arc_s:", s,
                            ", l:", l, ", dl:", dl.has_value() ? *dl : 0.0,
                            ", ddl:", ddl.has_value() ? *ddl : 0.0,
                            ", dddl:", dddl.has_value() ? *dddl : 0.0);
    }
    void ToProto(MotionStateProto *proto) const {
        proto->set_x(xy.x());
        proto->set_y(xy.y());
        proto->set_k(k);
        proto->set_h(h);
        proto->set_t(t);
        proto->set_v(v);
        proto->set_a(a);
        proto->set_a(a);
        proto->set_accumulated_s(accumulated_s);
        proto->set_s(s);
        proto->set_l(l);
        if (dl.has_value()) {
            proto->set_dl(*dl);
        }
        if (ddl.has_value()) {
            proto->set_ddl(*ddl);
        }
        if (dddl.has_value()) {
            proto->set_dddl(*dddl);
        }
    }
};

}  // namespace planning
}  // namespace pnc_x
