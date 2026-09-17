
#include <float.h>

#include "line_curve1d.h"
#include "math/linear_interpolation.h"

namespace ads_x {
namespace planning {

void LineCurve1d::Clear() { curve_map_.clear(); };

bool LineCurve1d::IsValid() const { return !curve_map_.empty(); }

std::map<double, double> LineCurve1d::GetCurveMap() const { return curve_map_; }

void LineCurve1d::SetValue(const double x, const double value) {
    curve_map_[x] = value;
}

double LineCurve1d::GetValue(const double x) const {
    if (curve_map_.empty()) {
        return DBL_MAX;
    }
    if (curve_map_.size() == 1) {
        return curve_map_.begin()->second;
    }
    auto it0 = curve_map_.lower_bound(x);
    if (it0 == curve_map_.begin()) {
        return curve_map_.begin()->second;
    } else if (it0 == curve_map_.end()) {
        return curve_map_.rbegin()->second;
    }
    auto it1 = it0;
    it0--;
    return math::lerp(it0->second, it0->first, it1->second, it1->first, x,
                      true);
}

bool LineCurve1d::GetRange(double *begin, double *end) const {
    if (curve_map_.empty()) {
        return false;
    }
    *begin = curve_map_.begin()->first;
    *end = curve_map_.rbegin()->first;
    return true;
}
}  // namespace planning
}  // namespace ads_x