
#pragma once

namespace ads_x {
namespace planning {

enum class ErrorCode : int {
    PLANNING_FINISHED = -1,
    PLANNING_OK = 0,
    PLANNING_SKIP = 1,
    PLANNING_ERROR_NULL_POINTER = 2,
    PLANNING_ERROR_NOT_FOUND = 3,
    PLANNING_ERROR_NAN = 4,
    PLANNING_ERROR_TIMEOUT = 5,
    PLANNING_ERROR_FAILED = 6,
    PLANNING_MAP_FAILED = 7,
    PLANNING_OBSTACLE_FAILED = 8,
};

}
}  // namespace ads_x
