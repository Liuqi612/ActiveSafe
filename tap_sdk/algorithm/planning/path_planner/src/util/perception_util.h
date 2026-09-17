
#pragma once

#include <string>

#include "math/geometry/polygon2d.h"
#include "pncx_perception.pb.h"
#include "pncx_positioning.pb.h"
#include "pncx_vehicle.pb.h"

namespace pnc_x {
namespace planning {

bool IsConsiderMirrorObject(const ObjectProto &object_proto,
                            double min_mirror_height_avg,
                            double max_mirror_height_avg);

bool IsVehicle(ObjectType type);

bool IsLargeVehicle(const ObjectProto &object);

Polygon2d ComputeObjectContour(const ObjectProto &object);

ObjectProto AvPoseProtoToObjectProto(
    const std::string &object_id,
    const VehicleGeometryParamsProto &vehicle_geom,
    const PoseProto &pose,
    bool offroad);

bool IsCameraObject(const ObjectProto &object);

}  // namespace planning
}  // namespace pnc_x
