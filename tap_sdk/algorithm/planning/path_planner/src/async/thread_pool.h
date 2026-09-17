
#pragma once

#include <cstdint>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

// #include <gflags/gflags.h>
#include <sched.h>

#include "async/future.h"
#include <absl/base/thread_annotations.h>
#include <absl/status/status.h>
#include <absl/synchronization/mutex.h>

namespace pnc_x {

class ThreadPool {
 public:
#if defined(__linux__) || defined(__unix__)
    enum class SchedulePolicy : int {
        DEFAULT = SCHED_OTHER,
        REALTIME = SCHED_RR,
        LOW = SCHED_IDLE
    };

    enum class SchedulePriority { NO_VALUE, HIGH, VERY_HIGH, ULTRA_HIGH };
#endif

    explicit ThreadPool(int num_workers,
                        const std::function<void(int index)> &init_thread = {},
                        const std::string &pool_name = "ThreadPool");
    ~ThreadPool();

    static ThreadPool *DefaultPool();

    static ThreadPool *MapDefaultPool();

    static ThreadPool *DisposalPool();

    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;

    int NumWorkers() const { return static_cast<int>(workers_.size()); }

#if defined(__linux__) || defined(__unix__)
    absl::Status SetScheduleParam(SchedulePolicy policy,
                                  SchedulePriority priority);
#endif

    template <class Func, class... Args>
    using FutureType = Future<typename std::result_of<Func(Args...)>::type>;

    template <class Func, class... Args>
    FutureType<Func, Args...> Schedule(Func &&f, Args &&... args)
        ABSL_LOCKS_EXCLUDED(mutex_);

    void Drain(void);

 private:
    absl::Mutex mutex_;
    absl::CondVar cond_var_ ABSL_GUARDED_BY(mutex_);

    std::vector<std::thread> workers_;

    std::queue<std::function<void()>> tasks_ ABSL_GUARDED_BY(mutex_);
    bool stop_requested_ ABSL_GUARDED_BY(mutex_) = false;
    std::once_flag drain_flag_;
};

template <class Func, class... Args>
ThreadPool::FutureType<Func, Args...> ThreadPool::Schedule(Func &&f,
                                                           Args &&... args) {
    using ReturnType = typename std::result_of<Func(Args...)>::type;
    const auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward<Func>(f), std::forward<Args>(args)...));
    Future<ReturnType> res(task->get_future());

    int64_t tasks_size = -1;
    if (workers_.empty()) {
        (*task)();
    } else {
        absl::MutexLock lock(&mutex_);

        tasks_.emplace([task]() { (*task)(); });
        tasks_size = static_cast<int64_t>(tasks_.size());
        cond_var_.Signal();
    }
    return res;
}

}  // namespace pnc_x
