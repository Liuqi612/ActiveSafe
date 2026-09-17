

#include "util/hmi_content_util.h"
#include "maps/lane_point.h"
#include <absl/status/statusor.h>

#include "math/frenet_common.h"
#include "math/geometry/util.h"
#include "util/path_util.h"
#include "util/status_macros.h"

namespace pnc_x {
namespace planning {
namespace {

constexpr int kBoundaryResampleStep = 10;

bool IsYellowLaneBoundary(StationBoundaryType type) {
    switch (type) {
        case StationBoundaryType::BROKEN_YELLOW:
        case StationBoundaryType::SOLID_YELLOW:
        case StationBoundaryType::SOLID_DOUBLE_YELLOW:
            return true;
        case StationBoundaryType::VIRTUAL_CURB:
        case StationBoundaryType::CURB:
        case StationBoundaryType::SOLID_WHITE:
        case StationBoundaryType::BROKEN_LEFT_DOUBLE_WHITE:
        case StationBoundaryType::BROKEN_RIGHT_DOUBLE_WHITE:
        case StationBoundaryType::UNKNOWN_TYPE:
        case StationBoundaryType::BROKEN_WHITE:
        case StationBoundaryType::VIRTUAL_LANE:
            return false;
    }
    return false;  // 添加默认返回值
}

bool CheckTrajectoryCrossingLeftYellowLaneBoundary(
    const DrivePassage &drive_passage,
    const std::vector<ApolloTrajectoryPointProto> &traj_points) {
    for (size_t i = 0; i < traj_points.size(); ++i) {
        const auto path_point_xy = ToVec2d(traj_points[i].path_point());
        ASSIGN_OR_CONTINUE(
            const auto path_point_sl,
            drive_passage.QueryFrenetCoordinateAt(path_point_xy));
        auto boundary =
            drive_passage.QueryEnclosingLaneBoundariesAtS(path_point_sl.s);
        auto left_boundary = boundary.left;
        if (left_boundary.has_value() &&
            IsYellowLaneBoundary(left_boundary->type) &&
            (path_point_sl.l > left_boundary->lat_offset)) {
            return true;
        }
    }
    return false;
}

}  // namespace

HmiContentProto ReportHmiContent(const HmiContentInput &input) { return {}; }

HmiPathBoundaryProto ReportBoundaryPointsToHmiContent(
    const std::vector<Vec2d> &points,
    bool is_left,
    HmiPathBoundaryProto::BoundaryRenderStyle style) {
    HmiPathBoundaryProto path_boundary;
    if (points.empty()) return path_boundary;

    if (is_left) {
        path_boundary.set_left_render_style(style);
    } else {
        path_boundary.set_right_render_style(style);
    }

    const size_t size = points.size();
    const int resample_size =
        (static_cast<int>(size) / kBoundaryResampleStep) + 2;
    auto *boundary_ptr = is_left ? path_boundary.mutable_left_boundary()
                                 : path_boundary.mutable_right_boundary();
    boundary_ptr->Reserve(resample_size);
    for (size_t i = 0; i < size; ++i) {
        if (!(((i % static_cast<size_t>(kBoundaryResampleStep)) == 0U) ||
              (i == (size - 1U)))) {
            continue;
        }
        Vec2dToProto(points[i], boundary_ptr->Add());
    }
    return path_boundary;
}

HmiPathBoundaryProto ReportPathBoundaryToHmiContent(
    const PathSlBoundary *sl_boundary,
    HmiPathBoundaryProto::BoundaryRenderStyle left_style,
    HmiPathBoundaryProto::BoundaryRenderStyle right_style) {
    HmiPathBoundaryProto path_boundary;
    if ((sl_boundary == nullptr) || sl_boundary->IsEmpty()) return path_boundary;

    path_boundary.set_left_render_style(left_style);
    path_boundary.set_right_render_style(right_style);

    const size_t size = sl_boundary->size();
    const int resample_size =
        (static_cast<int>(size) / kBoundaryResampleStep) + 2;
    path_boundary.mutable_left_boundary()->Reserve(resample_size);
    path_boundary.mutable_right_boundary()->Reserve(resample_size);

    constexpr double kMaxBoundaryRenderDist = 50.0;
    for (size_t i = 0; i < size; ++i) {
        if (!(((i % static_cast<size_t>(kBoundaryResampleStep)) == 0U) ||
              (i == (size - 1U)))) {
            continue;
        }
        Vec2dToProto(sl_boundary->left_xy_vector()[i],
                     path_boundary.add_left_boundary());
        Vec2dToProto(sl_boundary->right_xy_vector()[i],
                     path_boundary.add_right_boundary());
        if (sl_boundary->s_vector()[i] > kMaxBoundaryRenderDist) break;
    }
    return path_boundary;
}

}  // namespace planning
}  // namespace pnc_x
