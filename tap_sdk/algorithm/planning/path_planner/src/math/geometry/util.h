
#pragma once

#include <iterator>
#include <utility>
#include <vector>
#include <boost/geometry.hpp>

#include "pncx_affine_transformation.pb.h"
#include "pncx_positioning.pb.h"
#include "pncx_trajectory_point.pb.h"

#include "path_planner/src/math/eigen.h"
#include "path_planner/src/common/log.h"
#include "path_planner/src/math/geometry/box2d.h"
#include "path_planner/src/math/geometry/circle2d.h"
#include "path_planner/src/math/geometry/polygon2d.h"
#include "path_planner/src/math/util.h"
#include "path_planner/src/math/vec.h"

namespace pnc_x {

class VehiclePoseLerper {
 public:
};

template <typename T>
Eigen::Matrix<T, 3, 3> SkewSymmetricMatrix(const Eigen::Matrix<T, 3, 1> &v);

Quaternion VectorToVectorQuaternion(const Vec3d &vec);

Quaternion EulerVectorToQuaternion(Vec3d vec);

void Vec2dToProto(const Vec2d &v, Vec2dProto *proto);

Vec2d Vec2dFromProto(const Vec2dProto &proto);

Vec2d Vec2dFromProto(const Vec3dProto &proto);

Vec2d Vec2dFromPoseProto(const PoseProto &proto);

Vec2d Vec2dFromTrajectoryPointProto(const TrajectoryPointProto &proto);

Vec2d Vec2dFromApolloTrajectoryPointProto(
    const ApolloTrajectoryPointProto &proto);

Vec2d Vec2dFromPathPoint(const PathPoint &proto);

void Vec3dToProto(const Vec3d &v, Vec3dProto *proto);

Vec3d Vec3dFromProto(const Vec3dProto &proto);

void Vec3iToProto(const Vec3i &v, Vec3iProto *proto);

Vec3i Vec3iFromProto(const Vec3iProto &proto);

void Vec4dToProto(const Vec4d &v, Vec4dProto *proto);

Vec4d Vec4dFromProto(const Vec4dProto &proto);

void Mat2dToProto(const Mat2d &m, Mat2dProto *proto);

void Mat2dFromProto(const Mat2dProto &proto, Mat2d *m);

void Mat3dToProto(const Mat3d &m, Mat3dProto *proto);

void Mat3dFromProto(const Mat3dProto &proto, Mat3d *m);

void Mat4dToProto(const Mat4d &m, Mat4dProto *proto);

void Mat4dFromProto(const Mat4dProto &proto, Mat4d *m);

std::pair<double, double> ProjectBoxToRay(const Vec2d &ray_center,
                                          const Vec2d &ray_dir,
                                          const Box2d &box);

template <typename InputIt, typename OutIt>
int FillNoSelfIntersectSimplifyPoints(InputIt first,
                                      InputIt last,
                                      OutIt out,
                                      double epision);

std::vector<Circle2d> GenerateCirclesInsideBox(const Box2d &box,
                                               double circle_center_dist);

Mat3d ComputeMeanValueForRoatationMatrices(
    const std::vector<Mat3d> &rotation_matrices);

}  // namespace pnc_x
