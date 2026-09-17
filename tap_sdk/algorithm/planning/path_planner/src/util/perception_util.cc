

#include "util/perception_util.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>
#include <vector>

#include <absl/strings/str_format.h>

#include "pncx_affine_transformation.pb.h"
#include "pncx_box2d.pb.h"
#include "math/geometry/box2d.h"
#include "math/geometry/util.h"
#include "math/vec.h"
#include "util/vehicle_geometry_util.h"

namespace pnc_x {
namespace planning {

bool IsConsiderMirrorObject(const ObjectProto &object_proto,
                            double min_mirror_height_avg,
                            double max_mirror_height_avg) {
    if (!object_proto.has_min_z() || !object_proto.has_max_z() ||
        !object_proto.has_ground_z()) {
        return true;
    }
    const double object_max_height =
        object_proto.max_z() - object_proto.ground_z();
    const double object_min_height =
        object_proto.min_z() - object_proto.ground_z();
    return (object_max_height > min_mirror_height_avg) &&
           (object_min_height < max_mirror_height_avg);
}

bool IsVehicle(ObjectType type) {
    return ((type == ObjectType::OT_VEHICLE) ||
            (type == ObjectType::OT_LARGE_VEHICLE));
}

bool IsLargeVehicle(const ObjectProto &object) {
    constexpr double kLargeVehicleLength = 7.0;
    constexpr double kTruckLargeVehicleLength = 6.0;
    constexpr double kLargeVehicleWidth = 3.0;
    constexpr double kLargeVehicleHeight = 3.0;

    const double length = object.bounding_box().length();
    const double width = object.bounding_box().width();
    const double height = object.max_z() - object.ground_z();
    return (length > kLargeVehicleLength) ||
           ((width > kLargeVehicleWidth) && (height > kLargeVehicleHeight)) ||
           (object.type() == OT_LARGE_VEHICLE);
}

Polygon2d ComputeObjectContour(const ObjectProto &object_proto) {
    int contour_size = object_proto.contour_size();
    std::vector<Vec2d> vertices;
    vertices.reserve(contour_size);
    for (int j = 0; j < contour_size; ++j) {
        vertices.push_back(Vec2dFromProto(object_proto.contour(j)));
    }
    XCHECK_GT(vertices.size(), 2);
    return Polygon2d(std::move(vertices), true);
}

ObjectProto AvPoseProtoToObjectProto(
    const std::string &object_id,
    const VehicleGeometryParamsProto &vehicle_geom,
    const PoseProto &pose,
    bool offroad) {
    ObjectProto object;
    object.set_id(object_id);
    object.set_type(ObjectType::OT_VEHICLE);

    const Box2d box =
        ComputeAvBox(Vec2d(pose.pos_smooth().x(), pose.pos_smooth().y()),
                     pose.yaw(), vehicle_geom);
    object.mutable_pos()->set_x(box.center().x());
    object.mutable_pos()->set_y(box.center().y());

    object.set_yaw(pose.yaw());

    object.mutable_vel()->set_x(pose.vel_smooth().x());
    object.mutable_vel()->set_y(pose.vel_smooth().y());

    object.mutable_accel()->set_x(pose.accel_smooth().x());
    object.mutable_accel()->set_y(pose.accel_smooth().y());

    for (const auto &pt : box.GetCornersCounterClockwise()) {
        pt.ToProto(object.add_contour());
    }

    box.ToProto(object.mutable_bounding_box());

    object.set_parked(false);

    constexpr double kMinSpeed = 0.2;

    object.set_min_z(pose.pos_smooth().z());
    object.set_max_z(pose.pos_smooth().z() + vehicle_geom.height());

    if (pose.has_timestamp()) {
        object.set_timestamp(pose.timestamp());
    } else {
        // AD_LINFO(PP) << absl::StrFormat("I do not find any timestamp for the
        // av!");
    }
    return object;
}

bool IsCameraObject(const ObjectProto &object) { return true; }

}  // namespace planning
}  // namespace pnc_x
