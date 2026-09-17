
#pragma once

#include <utility>

#include "common/path_sl_boundary.h"
#include "pncx_constraint.pb.h"
#include "math/frenet_common.h"
#include "object/spacetime_object_trajectory.h"
#include "pncx_perception.pb.h"
#include "plan/speed_profile.h"
#include "router/drive_passage.h"
#include <absl/types/span.h>

namespace pnc_x {
namespace planning {

SpeedProfile CreateSpeedProfile(
    double v_now,
    const DrivePassage &passage,
    const absl::Span<const ConstraintProto::SpeedRegionProto> &speed_zones,
    const absl::Span<const ConstraintProto::StopLineProto> &stop_points);

ConstraintProto::SpeedRegionProto MergeSameElement(
    absl::Span<const ConstraintProto::SpeedRegionProto> elements);

bool IsLeadingObjectType(ObjectType type);

std::pair<double, double> CalcSlBoundaries(const PathSlBoundary &sl_boundary,
                                           const FrenetBox &frenet_box);

ConstraintProto::LeadingObjectProto CreateLeadingObject(
    const SpacetimeObjectTrajectory &traj,
    const DrivePassage &passage,
    ConstraintProto::LeadingObjectProto::Reason reason,
    bool is_group_tail = false);

bool IsTrafficLightControlledLane(const ads_x::planning::Lane &lane);

}  // namespace planning
}  // namespace pnc_x
