
#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>
#include <string>

#include "path_planner/src/math/vec.h"

namespace ads_x {
namespace planning {
namespace math {

using Vec3d = pnc_x::Vec3<double>;
typedef Eigen::Vector3d Vector3d;
typedef Eigen::Quaterniond Quaterniond;
typedef Eigen::AngleAxisd AngleAxisd;
typedef Eigen::Isometry3d Isometry3d;

}  // namespace math
}  // namespace planning
}  // namespace ads_x
