#pragma once

#include "common/log.h"

namespace ads_x {
namespace planning {
class LoopGuard {
 public:
    explicit LoopGuard(int max_attempts, const std::string &func_name)
        : max_(max_attempts), count_(0), warn_msg_(func_name) {}

    operator bool() {
        if (++count_ > max_) {
            return false;
        }
        return true;
    }

    int attempts() const { return count_; }

 private:
    const int max_;
    int count_;
    std::string warn_msg_;
};

#define CREATE_LOOP_GUARD(max, msg) ads_x::planning::LoopGuard((max), (msg))

#define DEFAULT_LOOP_GUARD() \
    ads_x::planning::LoopGuard(1000000, "Loop exceeded")

#define DEFAULT_LOOP_GUARD_WITH_FUNC() \
    ads_x::planning::LoopGuard(1000000, __func__)

}  // namespace planning
}  // namespace ads_x
