
#pragma once

#include <string>
#include <vector>

#include "pncx_optimizer.pb.h"
#include "plan/trajectory_point.h"
#include <absl/time/time.h>

namespace pnc_x {
namespace planning {

struct TrajectoryOptimizerState {
    TrajectoryOptimizerState() = default;
    explicit TrajectoryOptimizerState(
        const TrajectoryOptimizerStateProto &proto) {
        FromProto(proto);
    }

    void FromProto(const TrajectoryOptimizerStateProto &proto);

    TrajectoryOptimizerStateProto ToProto() const;

    absl::Time last_plan_start_time;

    // 存储上一帧轨迹给下一帧计算帧间吸引cost
    std::vector<TrajectoryPoint> last_optimized_trajectory;
    std::vector<ApolloTrajectoryPointProto> apollo_last_optimized_trajectory;
};

}  // namespace planning
}  // namespace pnc_x
