#include "tap_adapter/core/planning_object_adapter.h"

#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <utility>

#include <absl/status/status.h>
#include <absl/strings/str_cat.h>
#include <absl/types/span.h>

#include "object/planner_object.h"
#include "pncx_perception.pb.h"
#include "pncx_prediction.pb.h"
#include "prediction/predicted_trajectory.h"
#include "prediction/prediction.h"

namespace tap {
namespace planning_adapter {
namespace core {
namespace {

constexpr double kEpsilon = 1e-6;
constexpr double kPi = 3.14159265358979323846;
constexpr double kMaxCoordinate = 1.0e7;
constexpr double kMaxSpeed = 100.0;
constexpr double kMaxAcceleration = 50.0;
constexpr double kMaxYawRate = 10.0;
constexpr double kMaxCurvature = 2.0;
constexpr double kMaxDimension = 50.0;
constexpr double kMinContourArea = 1e-3;
constexpr double kMaxFirstPointOffset = 5.0;

bool IsFinite(double value) { return std::isfinite(value); }

absl::Status InvalidObject(const NormalizedPredictedObject &object,
                           const std::string &reason) {
    return absl::InvalidArgumentError(
        absl::StrCat("invalid object '", object.id, "': ", reason));
}

pnc_x::ObjectType ToObjectType(NormalizedObjectType type) {
    switch (type) {
        case NormalizedObjectType::kUnknownStatic:
            return pnc_x::ObjectType::OT_UNKNOWN_STATIC;
        case NormalizedObjectType::kUnknownMovable:
            return pnc_x::ObjectType::OT_UNKNOWN_MOVABLE;
        case NormalizedObjectType::kVehicle:
            return pnc_x::ObjectType::OT_VEHICLE;
        case NormalizedObjectType::kLargeVehicle:
            return pnc_x::ObjectType::OT_LARGE_VEHICLE;
        case NormalizedObjectType::kPedestrian:
            return pnc_x::ObjectType::OT_PEDESTRIAN;
        case NormalizedObjectType::kCyclist:
            return pnc_x::ObjectType::OT_CYCLIST;
        case NormalizedObjectType::kCone:
            return pnc_x::ObjectType::OT_CONE;
        case NormalizedObjectType::kBarrier:
            return pnc_x::ObjectType::OT_BARRIER;
    }
    return pnc_x::ObjectType::OT_UNKNOWN_STATIC;
}

pnc_x::PredictionType ToPredictionType(NormalizedPredictionType type) {
    switch (type) {
        case NormalizedPredictionType::kStationary:
            return pnc_x::PredictionType::PT_STATIONARY;
        case NormalizedPredictionType::kVehicle:
            return pnc_x::PredictionType::PT_VEHICLE_LANE_FOLLOW;
        case NormalizedPredictionType::kPedestrian:
            return pnc_x::PredictionType::PT_PED_KINEMATIC;
        case NormalizedPredictionType::kCyclist:
            return pnc_x::PredictionType::PT_BIKE_LANE_FOLLOW;
        case NormalizedPredictionType::kUnknown:
            return pnc_x::PredictionType::PT_VOID;
    }
    return pnc_x::PredictionType::PT_VOID;
}

double SignedContourArea(const std::vector<NormalizedPoint2d> &contour) {
    double twice_area = 0.0;
    for (size_t i = 0; i < contour.size(); ++i) {
        const auto &a = contour[i];
        const auto &b = contour[(i + 1) % contour.size()];
        twice_area += (a.x * b.y) - (a.y * b.x);
    }
    return 0.5 * twice_area;
}

bool IsStrictConvexContour(const std::vector<NormalizedPoint2d> &contour) {
    double previous_cross = 0.0;
    for (size_t i = 0; i < contour.size(); ++i) {
        const auto &a = contour[i];
        const auto &b = contour[(i + 1) % contour.size()];
        const auto &c = contour[(i + 2) % contour.size()];
        const double ab_x = b.x - a.x;
        const double ab_y = b.y - a.y;
        const double bc_x = c.x - b.x;
        const double bc_y = c.y - b.y;
        if (std::hypot(ab_x, ab_y) <= kEpsilon) {
            return false;
        }
        const double cross = (ab_x * bc_y) - (ab_y * bc_x);
        if (std::abs(cross) <= kEpsilon) {
            return false;
        }
        if (previous_cross != 0.0 && cross * previous_cross < 0.0) {
            return false;
        }
        previous_cross = cross;
    }
    return true;
}

absl::Status ValidatePoint(const NormalizedPredictedObject &object,
                           const NormalizedPredictedPoint &point,
                           size_t trajectory_index,
                           size_t point_index) {
    if (!IsFinite(point.x) || !IsFinite(point.y) || !IsFinite(point.s) ||
        !IsFinite(point.heading) || !IsFinite(point.curvature) ||
        !IsFinite(point.relative_time) || !IsFinite(point.speed) ||
        !IsFinite(point.acceleration)) {
        return InvalidObject(
            object, absl::StrCat("non-finite trajectory ", trajectory_index,
                                 " point ", point_index));
    }
    if (std::abs(point.x) > kMaxCoordinate ||
        std::abs(point.y) > kMaxCoordinate ||
        std::abs(point.heading) > kPi + kEpsilon ||
        std::abs(point.curvature) > kMaxCurvature ||
        std::abs(point.speed) > kMaxSpeed ||
        std::abs(point.acceleration) > kMaxAcceleration) {
        return InvalidObject(object,
                             absl::StrCat("trajectory units out of range at ",
                                          trajectory_index, ":", point_index));
    }
    return absl::OkStatus();
}

absl::Status ValidateObject(const NormalizedPredictedObject &object) {
    if (object.source_timestamp_ns == 0) {
        return InvalidObject(object, "timestamp is zero");
    }
    if (object.id.empty()) {
        return InvalidObject(object, "id is empty");
    }
    if (!IsFinite(object.x) || !IsFinite(object.y) ||
        !IsFinite(object.heading) || !IsFinite(object.yaw_rate) ||
        !IsFinite(object.velocity_x) || !IsFinite(object.velocity_y) ||
        !IsFinite(object.acceleration_x) || !IsFinite(object.acceleration_y) ||
        !IsFinite(object.length) || !IsFinite(object.width)) {
        return InvalidObject(object, "base state contains non-finite data");
    }
    if (std::abs(object.x) > kMaxCoordinate ||
        std::abs(object.y) > kMaxCoordinate ||
        std::abs(object.heading) > kPi + kEpsilon ||
        std::abs(object.yaw_rate) > kMaxYawRate ||
        std::hypot(object.velocity_x, object.velocity_y) > kMaxSpeed ||
        std::hypot(object.acceleration_x, object.acceleration_y) >
            kMaxAcceleration ||
        object.length <= kEpsilon || object.length > kMaxDimension ||
        object.width <= kEpsilon || object.width > kMaxDimension) {
        return InvalidObject(object,
                             "base state violates coordinate or unit limits");
    }
    if (object.contour.size() < 3) {
        return InvalidObject(object, "contour has fewer than three points");
    }
    for (const auto &point : object.contour) {
        if (!IsFinite(point.x) || !IsFinite(point.y) ||
            std::abs(point.x) > kMaxCoordinate ||
            std::abs(point.y) > kMaxCoordinate) {
            return InvalidObject(object, "contour contains invalid point");
        }
    }
    if (std::abs(SignedContourArea(object.contour)) < kMinContourArea) {
        return InvalidObject(object, "contour is degenerate");
    }
    if (!IsStrictConvexContour(object.contour)) {
        return InvalidObject(object, "contour must be a strict convex polygon");
    }
    if (object.trajectories.empty()) {
        return InvalidObject(object, "prediction trajectory is missing");
    }

    std::unordered_set<int> trajectory_indices;
    double probability_sum = 0.0;
    for (size_t trajectory_index = 0;
         trajectory_index < object.trajectories.size(); ++trajectory_index) {
        const auto &trajectory = object.trajectories[trajectory_index];
        if (trajectory.index < 0) {
            return InvalidObject(object, "trajectory index is negative");
        }
        if (!trajectory_indices.insert(trajectory.index).second) {
            return InvalidObject(object, "duplicate trajectory index");
        }
        if (!IsFinite(trajectory.probability) ||
            trajectory.probability <= 0.0 || trajectory.probability > 1.0) {
            return InvalidObject(object, "trajectory probability is invalid");
        }
        probability_sum += trajectory.probability;
        const bool stationary =
            trajectory.type == NormalizedPredictionType::kStationary;
        if ((stationary && trajectory.points.size() != 1) ||
            (!stationary && trajectory.points.size() < 2)) {
            return InvalidObject(object, "prediction trajectory is too short");
        }
        for (size_t point_index = 0; point_index < trajectory.points.size();
             ++point_index) {
            const auto &point = trajectory.points[point_index];
            const auto status =
                ValidatePoint(object, point, trajectory_index, point_index);
            if (!status.ok()) {
                return status;
            }
            if (point_index == 0) {
                if (std::abs(point.relative_time) > kEpsilon ||
                    std::abs(point.s) > kEpsilon ||
                    std::hypot(point.x - object.x, point.y - object.y) >
                        kMaxFirstPointOffset) {
                    return InvalidObject(
                        object,
                        "trajectory must start at t=0, s=0 near base pose");
                }
                if (stationary &&
                    (std::abs(point.speed) > kEpsilon ||
                     std::abs(point.acceleration) > kEpsilon ||
                     std::hypot(object.velocity_x, object.velocity_y) > 0.5)) {
                    return InvalidObject(
                        object, "stationary prediction contains moving state");
                }
            } else {
                const auto &previous = trajectory.points[point_index - 1];
                if (point.relative_time <= previous.relative_time + kEpsilon ||
                    point.s + kEpsilon < previous.s) {
                    return InvalidObject(object,
                                         "trajectory time/s is not monotonic");
                }
                const double chord =
                    std::hypot(point.x - previous.x, point.y - previous.y);
                const double delta_s = point.s - previous.s;
                const double max_arc_chord_error =
                    std::max(0.5, 0.2 * std::max(delta_s, kEpsilon));
                if (chord > delta_s + 0.5 ||
                    delta_s - chord > max_arc_chord_error) {
                    return InvalidObject(object,
                                         "trajectory s/geometry mismatch");
                }
            }
        }
    }
    if (probability_sum > 1.0 + kEpsilon) {
        return InvalidObject(object, "trajectory probability sum exceeds one");
    }
    return absl::OkStatus();
}

pnc_x::ObjectProto BuildObjectProto(const NormalizedPredictedObject &object) {
    pnc_x::ObjectProto proto;
    proto.set_id(object.id);
    proto.set_type(ToObjectType(object.type));
    proto.set_timestamp(static_cast<double>(object.source_timestamp_ns) * 1e-9);
    proto.mutable_pos()->set_x(object.x);
    proto.mutable_pos()->set_y(object.y);
    proto.set_yaw(object.heading);
    proto.set_yaw_rate(object.yaw_rate);
    proto.mutable_vel()->set_x(object.velocity_x);
    proto.mutable_vel()->set_y(object.velocity_y);
    proto.mutable_accel()->set_x(object.acceleration_x);
    proto.mutable_accel()->set_y(object.acceleration_y);
    for (const auto &point : object.contour) {
        auto *output = proto.add_contour();
        output->set_x(point.x);
        output->set_y(point.y);
    }
    auto *box = proto.mutable_bounding_box();
    box->set_x(object.x);
    box->set_y(object.y);
    box->set_heading(object.heading);
    box->set_length(object.length);
    box->set_width(object.width);
    proto.set_confidence_level(3);
    return proto;
}

pnc_x::prediction::PredictedTrajectory BuildPredictedTrajectory(
    const NormalizedPredictedTrajectory &trajectory) {
    pnc_x::PredictedTrajectoryProto proto;
    proto.set_index(trajectory.index);
    proto.set_probability(trajectory.probability);
    proto.set_type(ToPredictionType(trajectory.type));
    for (const auto &point : trajectory.points) {
        auto *output = proto.add_points();
        output->mutable_pos()->set_x(point.x);
        output->mutable_pos()->set_y(point.y);
        output->set_s(point.s);
        output->set_theta(point.heading);
        output->set_kappa(point.curvature);
        output->set_t(point.relative_time);
        output->set_v(point.speed);
        output->set_a(point.acceleration);
    }
    // The upstream constructor expands a one-point PT_STATIONARY prediction
    // to the standard planning horizon; reuse that behavior here.
    return pnc_x::prediction::PredictedTrajectory(proto);
}

}  // namespace

absl::Status ValidatePredictedObjects(
    const std::vector<NormalizedPredictedObject> &objects) {
    std::unordered_set<std::string> object_ids;
    const uint64_t source_timestamp_ns =
        objects.empty() ? 0 : objects.front().source_timestamp_ns;
    for (const auto &object : objects) {
        const auto status = ValidateObject(object);
        if (!status.ok()) {
            return status;
        }
        if (!object_ids.insert(object.id).second) {
            return InvalidObject(object, "duplicate object id");
        }
        if (object.source_timestamp_ns != source_timestamp_ns) {
            return InvalidObject(object, "objects have different timestamps");
        }
    }
    return absl::OkStatus();
}

absl::StatusOr<pnc_x::planning::SpacetimeTrajectoryManager>
BuildSpacetimeTrajectoryManager(
    const std::vector<NormalizedPredictedObject> &objects) {
    const auto validation = ValidatePredictedObjects(objects);
    if (!validation.ok()) {
        return validation;
    }
    std::vector<pnc_x::planning::PlannerObject> planner_objects;
    planner_objects.reserve(objects.size());
    for (const auto &object : objects) {
        std::vector<pnc_x::prediction::PredictedTrajectory> trajectories;
        trajectories.reserve(object.trajectories.size());
        for (const auto &trajectory : object.trajectories) {
            trajectories.push_back(BuildPredictedTrajectory(trajectory));
        }
        pnc_x::prediction::ObjectPrediction prediction(
            std::move(trajectories), BuildObjectProto(object));
        planner_objects.emplace_back(std::move(prediction));
    }
    if (planner_objects.empty()) {
        return pnc_x::planning::SpacetimeTrajectoryManager{};
    }
    return pnc_x::planning::SpacetimeTrajectoryManager(
        absl::MakeConstSpan(planner_objects));
}

}  // namespace core
}  // namespace planning_adapter
}  // namespace tap
