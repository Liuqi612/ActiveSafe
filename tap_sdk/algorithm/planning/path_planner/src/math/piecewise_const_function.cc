

#include "math/piecewise_const_function.h"

#include <vector>

#include "path_planner/src/common/throw_check.h"
#include "pncx_piecewise_const_function.pb.h"

namespace pnc_x {

PiecewiseConstFunction<double, double> PiecewiseConstFunctionFromProto(
    const PiecewiseConstFunctionDoubleProto &proto) {
    XCHECK_EQ(proto.x_size(), proto.y_size() + 1);
    std::vector<double> x(proto.x().begin(), proto.x().end());
    std::vector<double> y(proto.y().begin(), proto.y().end());
    return PiecewiseConstFunction<double, double>(std::move(x), std::move(y));
}

}  // namespace pnc_x
