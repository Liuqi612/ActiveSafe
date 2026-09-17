
#pragma once

#include <mutex>
#include <string>
#include <unordered_map>

#include "base/singleton.h"

namespace pnc_x {

#define QCONTEXT_THREAD_NAME_SET(thread_name) \
    pnc_x::ThreadUtil::Instance()->QSetThreadName(thread_name);

#define QCONTEXT_THREAD_NAME_GET(pid) \
    pnc_x::ThreadUtil::Instance()->QGetThreadName(pid);

class ThreadUtil {
 public:
    void QSetThreadName(const std::string &name);
    const std::string QGetThreadName(int pid);

 private:
    std::mutex mutex_;
    std::unordered_map<int, std::string> pid_to_name;

    DECLARE_SINGLETON(ThreadUtil);
};

}  // namespace pnc_x
