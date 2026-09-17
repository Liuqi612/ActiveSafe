
#pragma once

#include <map>

namespace ads_x {
namespace planning {
class LineCurve1d {
 public:
    LineCurve1d() = default;
    ~LineCurve1d() = default;

    void Clear();

    bool IsValid() const;

    void SetValue(const double x, const double value);

    double GetValue(const double x) const;

    bool GetRange(double *begin, double *end) const;

    std::map<double, double> GetCurveMap() const;

 private:
    std::map<double, double> curve_map_;
};
}  // namespace planning
}  // namespace ads_x
