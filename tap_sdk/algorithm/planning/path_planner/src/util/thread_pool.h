
#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <future>
#include "common/log.h"

namespace ads_x {
namespace planning {

class ThreadPool {
 public:
    ThreadPool(int number);

    ThreadPool(int number, int next_thread_pool_level);

    ThreadPool(int number, int next_thread_pool_level, int thread_pool_index);

    template <typename InputIter, typename OutputIter, typename F>
    OutputIter transform(InputIter begin, InputIter end, OutputIter out, F f);

    template <typename InputIter, typename F>
    void for_each(InputIter begin, InputIter end, F f);

    template <typename FuncType>
    std::future<typename std::result_of<FuncType()>::type> post(
        FuncType &&func);

    template <typename F>
    auto delay_clean(F &&f);

    void stop();

    ~ThreadPool();

 private:
    boost::thread_group _thread_group;
    // Boost 1.66+ renamed io_service to io_context and replaced the legacy
    // nested work type with an executor work guard.  The guard keeps worker
    // threads alive while the pool is idle, matching the upstream behavior.
    boost::asio::io_context _io;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type>
        _work;
    bool _stopped = false;
};

#define MAX_THREAD_POOL_LEVEL 5
#define MAX_THREAD_POOL_INDEX 3
const static int
    THREAD_POOL_CAPACITY[MAX_THREAD_POOL_INDEX][MAX_THREAD_POOL_LEVEL] = {
        {10, 10, 10, 10, 10}, {10, 10, 10, 10, 10}, {10, 10, 10, 10, 10}};

template <int LEVEL, int INDEX>
class LevelThreadPool : public ThreadPool {
 public:
    static LevelThreadPool *instance() {
        static LevelThreadPool<LEVEL, INDEX> pool;
        return &pool;
    }

 private:
    LevelThreadPool()
        : ThreadPool(THREAD_POOL_CAPACITY[INDEX][LEVEL], LEVEL + 1, INDEX) {
        printf("index %d level %d thread pool capacity = %d", INDEX, LEVEL,
               THREAD_POOL_CAPACITY[INDEX][LEVEL]);
    }
};

class GlobalThreadPool {
 public:
    static ThreadPool *instance();
    static void set_index(int index);

    static thread_local int s_thread_pool_level;
    static thread_local int s_thread_pool_index;
};

namespace parallel {

template <typename InputIter, typename OutputIter, typename F>
OutputIter transform(InputIter begin, InputIter end, OutputIter out, F f);

template <typename InputIter, typename F>
void for_each(InputIter begin, InputIter end, F f);

template <typename F>
void for_each(size_t n, F f);

template <typename InputIter, typename F>
void for_each_with_index(InputIter begin, InputIter end, F f);

}  // namespace parallel

}  // namespace planning
}  // namespace ads_x

#define DELAY_CLEAN(p) GlobalThreadPool::instance()->delay_clean(p)
