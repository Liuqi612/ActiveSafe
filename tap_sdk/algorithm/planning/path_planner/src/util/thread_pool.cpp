

#include "util/thread_pool.h"
#include "common/gflags.h"
#include "common/planning_macros.h"
#include "util/logger_stack.h"

namespace ads_x {
namespace planning {

template <typename InputIter, typename OutputIter, typename F>
OutputIter ThreadPool::transform(InputIter begin,
                                 InputIter end,
                                 OutputIter out,
                                 F f) {
    typedef std::future<decltype(f(*begin))> Future;
    std::vector<Future> futures;
    for (auto i = begin; i != end; ++i) {
        auto &num = *i;
        futures.emplace_back(this->post([&] { return f(num); }));
    }
    bool succ = true;
    for (auto &future : futures) {
        try {
            *(out++) = future.get();
        } catch (std::exception &e) {
            printf("exception occured: %s", e.what());
            LoggerStack::PrintLoggerStackTrace();
            succ = false;
        } catch (...) {
            printf("Unknown exception occured");
            LoggerStack::PrintLoggerStackTrace();
            succ = false;
        }
    }
    if (succ) {
        AD_LINFO(PP) << "excpetion occured in thread pool user function";
    }

    return out;
}

template <typename InputIter, typename F>
void ThreadPool::for_each(InputIter begin, InputIter end, F f) {
    if (std::distance(begin, end) == 1) {
        f(*begin);
        return;
    }
    typedef std::future<void> Future;
    std::vector<Future> futures;
    for (auto i = begin; i != end; ++i) {
        auto &num = *i;
        futures.emplace_back(this->post([&] { f(num); }));
    }
    bool succ = true;
    for (auto &future : futures) {
        if (future.wait_for(std::chrono::seconds(
                FLAGS_pnc_x_planning_future_wait_timeout)) ==
            std::future_status::timeout) {
            // XCHECK(false) << "future wait timeout";
        }
        try {
            future.get();
        } catch (std::exception &e) {
            printf("exception occured: %s", e.what());
            LoggerStack::PrintLoggerStackTrace();
            succ = false;
        } catch (...) {
            printf("Unknown exception occured");
            LoggerStack::PrintLoggerStackTrace();
            succ = false;
        }
    }
    
    if (succ) {
        AD_LINFO(PP) << "excpetion occured in thread pool user function";
    }
}

template <typename FuncType>
std::future<typename std::result_of<FuncType()>::type> ThreadPool::post(
    FuncType &&func) {
    typedef typename std::result_of<FuncType()>::type return_type;
    typedef typename std::packaged_task<return_type()> task_type;

    std::shared_ptr<task_type> task =
        std::make_shared<task_type>(std::move(func));
    std::future<return_type> returned_future = task->get_future();
    uint64_t father_logger_id = LoggerStack::GetStack().current_id();

    boost::asio::post(_io, [=] {
        LoggerStack::SetThreadFatherId(father_logger_id);
        (*task)();
    });
    return returned_future;
}

template <typename F>
auto ThreadPool::delay_clean(F &&f) {
    return post(std::move(f));
}

void ThreadPool::stop() {
    _io.stop();
    _thread_group.join_all();
    _stopped = true;
}

ThreadPool::~ThreadPool() {
    if (!_stopped) {
        try {
            stop();
        } catch (std::exception &e) {
            (void)printf("stop thread pool failed. %s", e.what());
        }
    }
}

ThreadPool::ThreadPool(int num, int next_thread_pool_level)
    : ThreadPool(num, next_thread_pool_level, 0) {}

ThreadPool::ThreadPool(int num, int next_thread_pool_level, int pool_index)
    : _work(boost::asio::make_work_guard(_io)) {
    (void)printf("Starting thread pool, thread_num = %d, index = %d", num,
           pool_index);
    for (int i = 0; i != num; ++i) {
        _thread_group.create_thread(
            [this, next_thread_pool_level, pool_index, i] {
                GlobalThreadPool::s_thread_pool_level = next_thread_pool_level;
                GlobalThreadPool::s_thread_pool_index = pool_index;
                this->_io.run();
            });
    }
}

ThreadPool::ThreadPool(int num)
    : ThreadPool(num, GlobalThreadPool::s_thread_pool_level) {}

thread_local int GlobalThreadPool::s_thread_pool_level = 0;
thread_local int GlobalThreadPool::s_thread_pool_index = 0;

#define CASE_LEVEL_THREAD_POOL(N, INDEX) \
    case N:                              \
        return LevelThreadPool<N, INDEX>::instance();

#define CASE_LEVEL_THREAD_POOL_0(N) CASE_LEVEL_THREAD_POOL(N, 0)
#define CASE_LEVEL_THREAD_POOL_1(N) CASE_LEVEL_THREAD_POOL(N, 1)
#define CASE_LEVEL_THREAD_POOL_2(N) CASE_LEVEL_THREAD_POOL(N, 2)

ThreadPool *GlobalThreadPool::instance() {
    int pool_level = s_thread_pool_level;
    if (!XCHECK_LT(pool_level, MAX_THREAD_POOL_LEVEL)) {
        AD_LDEBUG(PP) << "max supported pool level is 4";
    }

    int index = s_thread_pool_index;
    switch (index) {
        case 0:
            switch (pool_level) {
                PLAN_REPEAT(MAX_THREAD_POOL_LEVEL, CASE_LEVEL_THREAD_POOL_0)
            }
            [[fallthrough]];
        case 1:
            switch (pool_level) {
                PLAN_REPEAT(MAX_THREAD_POOL_LEVEL, CASE_LEVEL_THREAD_POOL_1)
            }
            [[fallthrough]];
        case 2:
            switch (pool_level) {
                PLAN_REPEAT(MAX_THREAD_POOL_LEVEL, CASE_LEVEL_THREAD_POOL_2)
            }
    }
    // XCHECK(false) << "pool level " << pool_level << " is invalid";

    return nullptr;
}

void GlobalThreadPool::set_index(int index) { s_thread_pool_index = index; }

namespace parallel {

template <typename InputIter, typename OutputIter, typename F>
OutputIter transform(InputIter begin, InputIter end, OutputIter out, F f) {
    return GlobalThreadPool::instance()->transform(begin, end, out, f);
}

template <typename InputIter, typename F>
void for_each(InputIter begin, InputIter end, F f) {
    GlobalThreadPool::instance()->for_each(begin, end, f);
}

template <typename F>
void for_each(size_t n, F f) {
    std::vector<size_t> ranges(n);
    for (size_t i = 0; i != n; ++i) {
        ranges[i] = i;
    }
    GlobalThreadPool::instance()->for_each(ranges.begin(), ranges.end(), f);
}

template <typename InputIter, typename F>
void for_each_with_index(InputIter begin, InputIter end, F f) {
    std::vector<std::pair<size_t, InputIter>> ranges;
    size_t count = 0;
    for (auto i = begin; i != end; ++i, ++count) {
        ranges.push_back(std::make_pair(count, i));
    }
    GlobalThreadPool::instance()->for_each(
        ranges.begin(), ranges.end(),
        [&](const std::pair<size_t, InputIter> &pair) {
            f(pair.first, *(pair.second));
        });
}

}  // namespace parallel

}  // namespace planning
}  // namespace ads_x
