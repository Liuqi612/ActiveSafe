

#include <algorithm>
#include <cmath>
#include <ostream>
#include <vector>

#include "path_planner/src/math/geometry/util.h"
#include "path_planner/src/common/log.h"

namespace {
constexpr double kGeomUtil_Two = 2.0;
}  // namespace

namespace pnc_x {

std::pair<double, double> ProjectBoxToRay(const Vec2d &ray_center,
                                          const Vec2d &ray_dir,
                                          const Box2d &box) {
    const double center = ray_dir.Dot(box.center() - ray_center);
    const Vec2d box_tangent = box.tangent();
    const double offset =
        0.5 * (std::abs(ray_dir.Dot(box_tangent * box.length())) +
               std::abs(ray_dir.Dot(box_tangent.Perp() * box.width())));
    return {center - offset, center + offset};
}

std::vector<Circle2d> GenerateCirclesInsideBox(const Box2d &box,
                                               double circle_center_dist) {
    if (std::abs(box.half_length() - box.half_width()) < 0.01) {
        return {Circle2d(box.center(),
                         std::min(box.half_length(), box.half_width()))};
    }

    if (box.length() < box.width()) {
        return GenerateCirclesInsideBox(
            Box2d(box.half_width(), box.half_length(), box.center(),
                  NormalizeAngle(box.heading() + M_PI_2), box.tangent().Perp()),
            circle_center_dist);
    }

    const double circle_radius = box.half_width();
    const int num_circles =
        CeilToInt((box.length() - (2.0 * circle_radius)) / circle_center_dist) +
        1;

    std::vector<Circle2d> circles;
    circles.reserve(static_cast<size_t>(num_circles));

    const Vec2d rear_center = box.center() - box.tangent() * box.half_length();
    const int num_circles_minus_1 = num_circles - 1;
    const double inner_circle_step =
        (box.length() - (kGeomUtil_Two * circle_radius)) / static_cast<double>(num_circles_minus_1);
    for (int i = 0; i < num_circles; ++i) {
        circles.push_back(
            Circle2d(rear_center + (box.tangent() *
                                       (circle_radius + (i * inner_circle_step))),
                     circle_radius));
    }

    return circles;
}

Mat3d ComputeMeanValueForRoatationMatrices(
    const std::vector<Mat3d> &rotation_matrices) {
    XCHECK_GT(rotation_matrices.size(), 1);
    Mat3d R = rotation_matrices[0];
    const double epsilon = 1e-13;
    for (int loop = 0; loop < 20; ++loop) {
        Vec3d r = Vec3d::Zero();
        for (const auto &mat : rotation_matrices) {
            Eigen::AngleAxisd angle_axis(R.transpose() * mat);
            r += angle_axis.angle() * angle_axis.axis();
        }
        r /= static_cast<double>(rotation_matrices.size());

        if (r.norm() < epsilon) return R;

        Eigen::AngleAxisd so3_r(r.norm(), r.normalized());
        R = R * so3_r;
    }
    // AD_LWARN(PP) << "Compute Mean Value For Roatation Matrices : bad
    // converge!!!";
    return R;
}

template <typename T>
Eigen::Matrix<T, 3, 3> SkewSymmetricMatrix(const Eigen::Matrix<T, 3, 1> &v) {
    Eigen::Matrix<T, 3, 3> m = Eigen::Matrix<T, 3, 3>::Zero();
    m(0, 1) = -v[2];
    m(1, 0) = v[2];
    m(0, 2) = v[1];
    m(2, 0) = -v[1];
    m(1, 2) = -v[0];
    m(2, 1) = v[0];
    return m;
}

Quaternion VectorToVectorQuaternion(const Vec3d &vec) {
    return Quaternion(0.0, vec.x(), vec.y(), vec.z());
}

Quaternion EulerVectorToQuaternion(Vec3d vec) {
    const double angle = vec.norm();
    if (angle < 1e-8) {
        Quaternion q(1.0, 0.5 * vec.x(), 0.5 * vec.y(), 0.5 * vec.z());
        q.normalize();
        return q;
    }
    vec /= angle;
    return Quaternion(AngleAxis(angle, vec));
}

void Vec2dToProto(const Vec2d &v, Vec2dProto *proto) {
    proto->set_x(v.x());
    proto->set_y(v.y());
}

Vec2d Vec2dFromProto(const Vec2dProto &proto) {
    return Vec2d(proto.x(), proto.y());
}

Vec2d Vec2dFromProto(const Vec3dProto &proto) {
    return Vec2d(proto.x(), proto.y());
}

Vec2d Vec2dFromPoseProto(const PoseProto &proto) {
    return Vec2d(proto.pos_smooth().x(), proto.pos_smooth().y());
}

Vec2d Vec2dFromTrajectoryPointProto(const TrajectoryPointProto &proto) {
    return Vec2d(proto.pos().x(), proto.pos().y());
}

Vec2d Vec2dFromApolloTrajectoryPointProto(
    const ApolloTrajectoryPointProto &proto) {
    return Vec2d(proto.path_point().x(), proto.path_point().y());
}

Vec2d Vec2dFromPathPoint(const PathPoint &proto) {
    return Vec2d(proto.x(), proto.y());
}

void Vec3dToProto(const Vec3d &v, Vec3dProto *proto) {
    proto->set_x(v.x());
    proto->set_y(v.y());
    proto->set_z(v.z());
}

Vec3d Vec3dFromProto(const Vec3dProto &proto) {
    return Vec3d(proto.x(), proto.y(), proto.z());
}

void Vec3iToProto(const Vec3i &v, Vec3iProto *proto) {
    proto->set_x(v.x());
    proto->set_y(v.y());
    proto->set_z(v.z());
}

Vec3i Vec3iFromProto(const Vec3iProto &proto) {
    return Vec3i(proto.x(), proto.y(), proto.z());
}

void Vec4dToProto(const Vec4d &v, Vec4dProto *proto) {
    proto->set_x(v.x());
    proto->set_y(v.y());
    proto->set_z(v.z());
    proto->set_w(v.w());
}

Vec4d Vec4dFromProto(const Vec4dProto &proto) {
    return Vec4d(proto.x(), proto.y(), proto.z(), proto.w());
}

void Mat2dToProto(const Mat2d &m, Mat2dProto *proto) {
    for (int i = 0; i < 4; ++i) proto->add_m(m.data()[i]);
}

void Mat2dFromProto(const Mat2dProto &proto, Mat2d *m) {
    XCHECK_EQ(proto.m_size(), 4);
    for (int i = 0; i < 4; ++i) m->data()[i] = proto.m(i);
}

void Mat3dToProto(const Mat3d &m, Mat3dProto *proto) {
    for (int i = 0; i < 9; ++i) proto->add_m(m.data()[i]);
}

void Mat3dFromProto(const Mat3dProto &proto, Mat3d *m) {
    XCHECK_EQ(proto.m_size(), 9);
    for (int i = 0; i < 9; ++i) m->data()[i] = proto.m(i);
}

void Mat4dToProto(const Mat4d &m, Mat4dProto *proto) {
    for (int i = 0; i < 16; ++i) proto->add_m(m.data()[i]);
}

void Mat4dFromProto(const Mat4dProto &proto, Mat4d *m) {
    XCHECK_EQ(proto.m_size(), 16);
    for (int i = 0; i < 16; ++i) m->data()[i] = proto.m(i);
}

std::pair<double, double> ProjectBoxToRay(const Vec2d &ray_center,
                                          const Vec2d &ray_dir,
                                          const Box2d &box);

template <typename InputIt, typename OutIt>
int FillNoSelfIntersectSimplifyPoints(InputIt first,
                                      InputIt last,
                                      OutIt out,
                                      double epision) {
    typedef boost::geometry::model::d2::point_xy<double> xy;
    typedef boost::geometry::model::linestring<xy> PLine;
    PLine pline;
    pline.reserve(std::distance(first, last));
    for (InputIt it = first; it != last; it++) {
        pline.emplace_back(it->x(), it->y());
    }
    PLine simplified;
    boost::geometry::simplify(pline, simplified, epision);
    for (const auto &point : simplified) {
        *out++ = {point.x(), point.y()};
    }
    return simplified.size();
}

}  // namespace pnc_x
