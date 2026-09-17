
#pragma once

#include <map>
#include <vector>

#include "path_planner/src/common/type_def.h"
#include "path_planner/src/math/line_curve1d.h"

namespace ads_x {
namespace planning {
class CurveLimit {
 public:
    CurveLimit() = default;
    ~CurveLimit() = default;

    bool Create(const LineCurve1d &lower_boundary,
                const LineCurve1d &upper_boundary,
                double s_interval = 0.5);

    void Clear();
    bool IsValid() const;

    void SetBoundary(const double &x, const double &lower, const double &upper);

    bool GetBoundary(const double &x, double *lower, double *upper) const;
    const std::map<double, std::pair<double, double>> &GetBoundary() const;
    bool GetBoundary(std::vector<double> &x,
                     std::vector<double> &lower,
                     std::vector<double> &upper) const;
    bool GetBoundary(std::vector<ads_x::planning::Point2d> &lower,
                     std::vector<ads_x::planning::Point2d> &upper) const;
    bool GetBoundary(std::map<double, double> &left_limit,
                     std::map<double, double> &right_limit) const;

    bool GetRange(double *begin, double *end) const;

 private:
    std::map<double, std::pair<double, double>> boundary_map_;
};
using CurveLimitPtr = std::shared_ptr<CurveLimit>;
}  // namespace planning
}  // namespace ads_x
