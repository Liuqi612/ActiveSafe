
#pragma once

#include <utility>
#include <vector>

#include "math/frenet_common.h"
#include "math/geometry/polygon2d.h"
#include "math/util.h"
#include "math/vec.h"
#include "pncx_trajectory_point.pb.h"
#include "util/loop_guard.h"
#include "common/log.h"

namespace pnc_x {
namespace planning {

class DiscretizedPath : public std::vector<PathPoint> {
 public:
    DiscretizedPath() = default;

    explicit DiscretizedPath(std::vector<PathPoint> path_points);

    double length() const {
        if (empty()) {
            return 0.0;
        }
        return back().s();
    }

    FrenetCoordinate XYToSL(const Vec2d &pos) const;

    FrenetPolygon XYToSL(const Polygon2d &contour, const Vec2d &pos) const;

    PathPoint Evaluate(double path_s) const;

    PathPoint EvaluateReverse(double path_s) const;

    static DiscretizedPath CreateResampledPath(
        std::vector<PathPoint> raw_path_points, double interval) {
        XCHECK_GE(raw_path_points.size(), 2);
        DiscretizedPath raw_path(std::move(raw_path_points));
        double s = 0.0;
        std::vector<PathPoint> path_points;
        path_points.reserve(CeilToInt(raw_path.length() / interval));
        auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
        while ((s < raw_path.length()) ? static_cast<bool>(loop_guard) : false) {
            path_points.push_back(raw_path.Evaluate(s));
            s += interval;
        }
        return DiscretizedPath(std::move(path_points));
    }

 protected:
    std::vector<PathPoint>::const_iterator QueryLowerBound(double path_s) const;
    std::vector<PathPoint>::const_iterator QueryUpperBound(double path_s) const;
};

}  // namespace planning
}  // namespace pnc_x
