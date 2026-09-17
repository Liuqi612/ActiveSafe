

#include "async/parallel_for.h"

#include <algorithm>
#include <atomic>
#include <memory>
#include <utility>

#include "common/log.h"

namespace pnc_x {

void ParallelFor(int begin,
                 int end,
                 ThreadPool *thread_pool,
                 const parallel_for::Options &options,
                 std::function<void(parallel_for::WorkerIndex, int)> &&func) {
    if (end == begin) {
        return;
    }

    if (thread_pool == nullptr) {
        for (int i = begin; i < end; ++i) {
            func(parallel_for::WorkerIndex(0), i);
        }
        return;
    }

    const int num_iters = end - begin;
    constexpr int kBlockSizeDivider = 4;
    int block_size = options.block_size;
    if (block_size == 0) {
        block_size = std::max<int>(
            1,
            num_iters / ((thread_pool->NumWorkers() + 1) * kBlockSizeDivider));
    }

    auto shared_state = std::make_shared<SharedState>(num_iters);
    const auto grab_tasks =
        [=, func = std::move(func)](parallel_for::WorkerIndex worker_index) {
            int iters_done = 0;
            std::string error_msg = "";
            while (true) {
                const int index = shared_state->next_index.fetch_add(
                                      block_size, std::memory_order_acq_rel) +
                                  begin;
                if (index >= end) { break; }
                for (int i = index; i < std::min(end, index + block_size);
                     ++i, ++iters_done) {
                    try {
                        func(worker_index, i);
                    } catch (std::exception &e) {
                        shared_state->block_until_finished.Finished(iters_done);
                        {
                            std::lock_guard<std::mutex> lock(
                                shared_state->exception_mutex);
                            shared_state->exception_msg +=
                                std::string(e.what()) + ";";
                        }
                    }
                }
            }
            shared_state->block_until_finished.Finished(iters_done);
        };

    const int min_num_workers = (num_iters + block_size - 1) / block_size;
    const int num_workers =
        std::min(min_num_workers - 1, thread_pool->NumWorkers());

    for (int i = 0; i < num_workers; ++i) {
        (void)thread_pool->Schedule(grab_tasks, parallel_for::WorkerIndex(i + 1));
    }

    grab_tasks(parallel_for::WorkerIndex(0));

    shared_state->block_until_finished.Block();

    {
        std::lock_guard<std::mutex> lock(shared_state->exception_mutex);
        if (!shared_state->exception_msg.empty()) {
            throw std::runtime_error(shared_state->exception_msg);
        }
    }
}

void ParallelFor(int begin,
                 int end,
                 ThreadPool *thread_pool,
                 std::function<void(parallel_for::WorkerIndex, int)> &&func) {
    ParallelFor(
        begin, end, thread_pool, {},
        std::forward<std::function<void(parallel_for::WorkerIndex, int)>>(
            func));
}

void ParallelFor(int begin,
                 int end,
                 std::function<void(parallel_for::WorkerIndex, int)> &&func) {
    ParallelFor(
        begin, end, ThreadPool::DefaultPool(),
        std::forward<std::function<void(parallel_for::WorkerIndex, int)>>(
            func));
}

void ParallelFor(int begin,
                 int end,
                 ThreadPool *thread_pool,
                 const parallel_for::Options &options,
                 std::function<void(int)> &&func) {
    ParallelFor(begin, end, thread_pool, options,
                [func = std::move(func)](int worker_index, int i) { func(i); });
}

void ParallelFor(int begin,
                 int end,
                 ThreadPool *thread_pool,
                 std::function<void(int)> &&func) {
    ParallelFor(begin, end, thread_pool, {},
                [func = std::move(func)](int worker_index, int i) { func(i); });
}

void ParallelFor(int begin, int end, std::function<void(int)> &&func) {
    ParallelFor(begin, end, ThreadPool::DefaultPool(),
                [func = std::move(func)](int worker_index, int i) { func(i); });
}

}  // namespace pnc_x
