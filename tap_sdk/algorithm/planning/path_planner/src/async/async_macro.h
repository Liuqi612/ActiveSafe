
#pragma once

#include <memory>
#include <string>
#include <system_error>
#include <utility>

#include "async/async_util.h"
#include <absl/strings/str_format.h>

#define MOVE_DESTROY_CONTAINER_ASYNC(thread_pool, container)           \
    ScheduleFuture(thread_pool, [_ = std::move(container)]() mutable { \
        const std::string container_name =                             \
            absl::StrFormat("%s_%d", #container, __LINE__);            \
        const std::string file(__FILE__);                              \
        SCOPED_QTRACE_ARG2("DestroyContainerAsync", "container name",  \
                           container_name, "file", file);              \
        [[maybe_unused]] const auto unused = std::move(_);             \
    })

#define MOVE_DESTROY_CONTAINER_ASYNC_DISPOSAL(container) \
    MOVE_DESTROY_CONTAINER_ASYNC(ThreadPool::DisposalPool(), container)
