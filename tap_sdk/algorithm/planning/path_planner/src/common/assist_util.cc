

#include "common/assist_util.h"

#include <cmath>
#include <utility>

#include <absl/status/statusor.h>
// #include <gflags/gflags.h>

#include "pncx_autonomy_state.pb.h"
#include "math/frenet_common.h"
#include "math/util.h"
#include "math/vec.h"
#include "plan/planner_defs.h"
#include "util/status_macros.h"

// DEFINE_int32(teleop_expire_seconds, 3, "Instruction expiration");

int32_t FLAGS_teleop_expire_seconds = 3;

namespace pnc_x {
namespace planning {

namespace {

absl::StatusOr<bool> LaneChangeCompleted(const DrivePassage &dp,
                                         const Vec2d &ego_pos,
                                         double ego_heading) {
    ASSIGN_OR_RETURN(const auto sl, dp.QueryFrenetCoordinateAt(ego_pos));
    ASSIGN_OR_RETURN(const auto angle, dp.QueryTangentAngleAtS(sl.s));

    constexpr double kAngleThreshold = d2r(10.0);

    return std::abs(sl.l) < kMaxLaneKeepLateralOffset &&
           std::abs(NormalizeAngle(angle - ego_heading)) < kAngleThreshold;
}
}  // namespace

absl::StatusOr<bool> CrossedBoundary(const DrivePassage &dp,
                                     const Vec2d &ego_pos) {
    ASSIGN_OR_RETURN(const auto sl, dp.QueryFrenetCoordinateAt(ego_pos));

    constexpr double kMaxHalfWidth = 2.5;
    if (std::abs(sl.l) > kMaxHalfWidth) return false;

    constexpr double kMinHalfWidth = 1.0;
    if (std::abs(sl.l) < kMinHalfWidth) return true;

    ASSIGN_OR_RETURN(const auto l_pair,
                     dp.QueryNearestBoundaryLateralOffset(sl.s));

    return sl.l > l_pair.first && sl.l < l_pair.second;
}

absl::StatusOr<ALCState> UpdateAlcState(ALCState state,
                                        const Vec2d &preview_pos,
                                        const Vec2d &ego_pos,
                                        double ego_heading,
                                        const DrivePassage &drive_passage) {
    switch (state) {
        case ALCState::ALC_OFF:
        case ALCState::ALC_STANDBY:
        case ALCState::ALC_STANDBY_ENABLE:
        case ALCState::ALC_PREPARE:
            return state;

        case ALCState::ALC_RETURN_COMPLETED:
        case ALCState::ALC_COMPLETED:
            return ALCState::ALC_STANDBY_ENABLE;

        case ALCState::ALC_CROSSING_LANE: {
            ASSIGN_OR_RETURN(
                const bool comp,
                LaneChangeCompleted(drive_passage, ego_pos, ego_heading));
            return comp ? ALCState::ALC_COMPLETED : ALCState::ALC_CROSSING_LANE;
        }

        case ALCState::ALC_RETURNING: {
            ASSIGN_OR_RETURN(
                const bool comp,
                LaneChangeCompleted(drive_passage, ego_pos, ego_heading));
            return comp ? ALCState::ALC_RETURN_COMPLETED
                        : ALCState::ALC_RETURNING;
        }
        case ALCState::ALC_ONGOING: {
            ASSIGN_OR_RETURN(bool cross,
                             CrossedBoundary(drive_passage, preview_pos));
            return cross ? ALCState::ALC_CROSSING_LANE : ALCState::ALC_ONGOING;
        }
        default:
            throw std::runtime_error("switch case on enum unexpected");
    }
}

void ReportPlcEventSignal(ALCState old_state,
                          ALCState new_state,
                          DriverAction::LaneChangeCommand lc_cmd) {
    switch (new_state) {
        case ALC_OFF:
        case ALC_STANDBY:
        case ALC_STANDBY_ENABLE:
        case ALC_CROSSING_LANE:
            return;
        case ALC_PREPARE:
            if (old_state != ALC_PREPARE) {
                if (lc_cmd == DriverAction::LC_CMD_LEFT) {
                    AD_LINFO(PP) << "Start waiting to lane change to left.";

                } else {
                    AD_LINFO(PP) << "Start waiting to lane change to right.";
                }
            }
            return;
        case ALC_ONGOING:
            if (old_state != ALC_ONGOING) {
                if (lc_cmd == DriverAction::LC_CMD_LEFT) {
                    AD_LINFO(PP) << "Start lane changing to left.";

                } else {
                    AD_LINFO(PP) << "Start lane changing to right.";
                }
            }
            return;
        case ALC_RETURNING:
            if (old_state != ALC_RETURNING) {
                if (lc_cmd == DriverAction::LC_CMD_LEFT) {
                    AD_LINFO(PP) << "Start returning to left.";

                } else {
                    AD_LINFO(PP) << "Start returning to right.";
                }
            }
            return;
        case ALC_COMPLETED:
            AD_LINFO(PP) << "Completed lane change.";

            return;
        case ALC_RETURN_COMPLETED:
            AD_LINFO(PP) << "Completed lane change return.";

            return;
    }
}

}  // namespace planning
}  // namespace pnc_x
