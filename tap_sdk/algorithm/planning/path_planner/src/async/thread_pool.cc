

#include <cerrno>
#include <cstring>
#include <mutex>
#include <string>

#include "common/log.h"
#include <pthread.h>
#include <unistd.h>

#include "async/thread_pool.h"
#include "common/gflags.h"
#include "util/thread_util.h"
#include <absl/strings/str_format.h>

namespace pnc_x {
namespace {
int ToPOSIXPolicy(ThreadPool::SchedulePolicy policy) {
    return static_cast<int>(policy);
}

std::pair<int, int> GetPriorityMinMax(ThreadPool::SchedulePolicy policy) {
    int posix_policy = ToPOSIXPolicy(policy);
    return std::make_pair(sched_get_priority_min(posix_policy),
                          sched_get_priority_max(posix_policy));
}

int ToPOSIXPriority(ThreadPool::SchedulePolicy policy,
                    ThreadPool::SchedulePriority priority) {
    auto minmax = GetPriorityMinMax(policy);
    const int min_value = minmax.first;
    const int max_value = minmax.second;
    const int span = max_value - min_value;
    switch (priority) {
        case ThreadPool::SchedulePriority::NO_VALUE:
            return 0;
        case ThreadPool::SchedulePriority::HIGH:
            return min_value;
        case ThreadPool::SchedulePriority::VERY_HIGH:
            return static_cast<int>(min_value + (0.5 * static_cast<double>(span)));
        case ThreadPool::SchedulePriority::ULTRA_HIGH:
            return max_value;
        default:
            return 0;
    }
}
}  // namespace

ThreadPool::ThreadPool(int num_workers,
                       const std::function<void(int index)> &init_thread,
                       const std::string &pool_name) {
    XCHECK_GE(num_workers, 0);

    for (int index = 0; index < num_workers; ++index) {
        workers_.emplace_back([this, index, init_thread, pool_name] {
            QCONTEXT_THREAD_NAME_SET(pool_name);
            [[maybe_unused]] int new_value = nice(-10);
            if (init_thread) {
                init_thread(index);
            }

            while (true) {
                std::function<void()> task;
                {
                    absl::MutexLock lock(&mutex_);

                    while (!stop_requested_ && tasks_.empty()) {
                        cond_var_.Wait(&mutex_);
                    }
                    if (stop_requested_ && tasks_.empty()) {
                        return;
                    }
                    task = std::move(tasks_.front());
                    tasks_.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() { Drain(); }

void ThreadPool::Drain(void) {
    std::call_once(drain_flag_, [&] {
        {
            absl::MutexLock lock(&mutex_);
            stop_requested_ = true;
            cond_var_.SignalAll();
        }
        for (std::thread &worker : workers_) {
            worker.join();
        }
    });
}

ThreadPool *ThreadPool::DefaultPool() {
    static std::unique_ptr<ThreadPool> default_pool =
        std::make_unique<ThreadPool>(
            FLAGS_pnc_x_city_planner_pool_size, [](int index) { (void)index; },
            "DefaultPool");
    return default_pool.get();
}

ThreadPool *ThreadPool::MapDefaultPool() {
    static std::unique_ptr<ThreadPool> map_pool = std::make_unique<ThreadPool>(
        FLAGS_pnc_x_city_planner_pool_size, [](int index) { (void)index; },
        "MapDefaultPool");
    return map_pool.get();
}

ThreadPool *ThreadPool::DisposalPool() {
    static std::unique_ptr<ThreadPool> disposal_pool =
        std::make_unique<ThreadPool>(
            1, [](int index) { (void)index; }, "DisposalPool");
    return disposal_pool.get();
}

absl::Status ThreadPool::SetScheduleParam(SchedulePolicy policy,
                                          SchedulePriority priority) {
    sched_param sch;
    sch.sched_priority = ToPOSIXPriority(policy, priority);
    int posix_policy = ToPOSIXPolicy(policy);
    for (auto &worker : workers_) {
        int ret =
            pthread_setschedparam(worker.native_handle(), posix_policy, &sch);
        if (ret != 0) {
            switch (ret) {
                case EPERM:
                    return absl::PermissionDeniedError(
                        "Setting thread pool schedule policy");
                case EINVAL:
                    return absl::InvalidArgumentError(absl::StrFormat(
                        "policy is not a recognized policy, or priority "
                        "does not make sense "
                        "for the policy. policy: %d, priority: %d",
                        posix_policy, sch.sched_priority));
                default:
                    return absl::UnknownError(absl::StrFormat(
                        "Failed to setschedparam: %s. policy: %d, priority: %d",
                        static_cast<const char *>(std::strerror(errno)),
                        posix_policy, sch.sched_priority));
            }
        }
    }
    return absl::OkStatus();
}

}  // namespace pnc_x
