
#pragma once

#include <future>
#include <string>
#include <type_traits>
#include <utility>

#include "async/future.h"
#include "async/thread_pool.h"

namespace pnc_x {

template <typename Func, typename... Args>
auto ScheduleFuture(ThreadPool *thread_pool, Func &&f, Args &&... args) {
    if (thread_pool == nullptr) {
        Future<typename std::result_of<Func(Args...)>::type> future(
            std::async(std::launch::deferred, std::forward<Func>(f),
                       std::forward<Args>(args)...));
        future.Wait();
        return future;
    }
    return thread_pool->Schedule(std::forward<Func>(f),
                                 std::forward<Args>(args)...);
}

template <typename Func, typename... Args>
auto ScheduleFuture(Func &&f, Args &&... args) {
    return ScheduleFuture(ThreadPool::DefaultPool(), std::forward<Func>(f),
                          std::forward<Args>(args)...);
}

template <typename ContainerT>
void DestroyContainerAsync(ThreadPool *thread_pool, ContainerT container) {
    ScheduleFuture(
        thread_pool, [container_to_destroy = std::move(container)]() mutable {
            const auto unused = std::move(container_to_destroy);
            (void)unused;  // C++14 way to suppress unused variable warning
        });
}

template <typename ContainerT>
void DestroyContainerAsync(ContainerT container) {
    DestroyContainerAsync(ThreadPool::DisposalPool(), std::move(container));
}

template <typename ContainerT>
void DestroyContainerAsyncMarkSource(ThreadPool *thread_pool,
                                     ContainerT container,
                                     std::string source) {
    ScheduleFuture(thread_pool, [container_to_destroy = std::move(container),
                                 str_source = std::move(source)]() mutable {
        const auto unused = std::move(container_to_destroy);
        (void)unused;      // C++14 way to suppress unused variable warning
        (void)str_source;  // Suppress unused variable warning for source
    });
}

template <typename ContainerT>
void DestroyContainerAsyncMarkSource(ContainerT container, std::string source) {
    DestroyContainerAsyncMarkSource(ThreadPool::DisposalPool(),
                                    std::move(container), std::move(source));
}

template <typename PointerT,
          std::enable_if_t<std::is_pointer<PointerT>::value, bool> = true>
void DestroyPointerAsync(ThreadPool *thread_pool, PointerT ptr) {
    ScheduleFuture(thread_pool, [ptr = std::move(ptr)]() mutable {
        if (ptr != nullptr) delete ptr;
    });
}

template <typename PointerT,
          std::enable_if_t<std::is_pointer<PointerT>::value, bool> = true>
void DestroyPointerAsync(PointerT ptr) {
    DestroyPointerAsync(ThreadPool::DisposalPool(), std::move(ptr));
}

template <typename T>
struct AsyncDeleter {
    void operator()(T *p) const { DestroyPointerAsync(p); }
};

template <typename T>
void WaitForFuture(const Future<T> &future) {
    future.Wait();
}

template <typename T>
class AsyncDestroyedResourceHolder {
 public:
    AsyncDestroyedResourceHolder() = default;
    ~AsyncDestroyedResourceHolder() { DestroyContainerAsync(std::move(val_)); }
    explicit AsyncDestroyedResourceHolder(T &&val) : val_(val) {}
    void TakeOwnership(T val) {
        DestroyContainerAsync(std::move(val_));
        val_ = std::move(val);
    }
    T &operator*() { return val_; }
    const T &operator*() const { return val_; }

 private:
    T val_;
};
}  // namespace pnc_x
