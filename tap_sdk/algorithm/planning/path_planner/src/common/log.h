
#pragma once

#include <cstdarg>
#include <string>

#include "common/log.h"

#include "ad_log/ad_log.hpp"

namespace ads_x {
namespace planning {
enum LogLevel : int { DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3, FATAL = 4 };
}
}  // namespace ads_x

std::string const_prefix(const char* file_name, int line_no);

std::string const_prefix(char const* module_name,
                         char const* file_name,
                         int line_no);

std::string lcformat(const char* fmt, ...);

#define MODULE const_prefix("PNC", __FILE__, __LINE__).c_str()

#define PNC_FATAL_M(MODULE) LOG(FATAL) << MODULE << ": "
#define PNC_ERROR_M(MODULE) LOG(ERROR) << MODULE << ": "
#define PNC_WARN_M(MODULE) AD_LWARN(PP) << MODULE << ": "
#define PNC_INFO_M(MODULE) AD_LINFO(PP) << MODULE << ": "

#define LLOG_LEVEL(log_level)                                             \
    do {                                                                  \
        FLAGS_pnc_x_planning_log_level = static_cast<int32_t>(log_level); \
    } while (0)

#define LFATAL(fmt, args...)                            \
    do {                                                \
        PNC_FATAL_M(MODULE) << lcformat((fmt), ##args); \
    } while (0)
#define LERROR(fmt, args...)                            \
    do {                                                \
        PNC_ERROR_M(MODULE) << lcformat((fmt), ##args); \
    } while (0)
#define LWARN(fmt, args...)                            \
    do {                                               \
        PNC_WARN_M(MODULE) << lcformat((fmt), ##args); \
    } while (0)
#define LINFO(fmt, args...)                            \
    do {                                               \
        PNC_INFO_M(MODULE) << lcformat((fmt), ##args); \
    } while (0)
#define LDEBUG(fmt, args...)                            \
    do {                                                \
        PNC_DEBUG_M(MODULE) << lcformat((fmt), ##args); \
    } while (0)

#define LOG_FATAL(...)             \
    do {                           \
        std::ostringstream oss;    \
        oss << __VA_ARGS__;        \
        LFATAL(oss.str().c_str()); \
    } while (0)

#define LOG_ERROR(...)             \
    do {                           \
        std::ostringstream oss;    \
        oss << __VA_ARGS__;        \
        LERROR(oss.str().c_str()); \
    } while (0)

#define LOG_WARN(...)             \
    do {                          \
        std::ostringstream oss;   \
        oss << __VA_ARGS__;       \
        LWARN(oss.str().c_str()); \
    } while (0)

#define LOG_INFO(...)             \
    do {                          \
        std::ostringstream oss;   \
        oss << __VA_ARGS__;       \
        LINFO(oss.str().c_str()); \
    } while (0)

#define LOG_DEBUG(...)             \
    do {                           \
        std::ostringstream oss;    \
        oss << __VA_ARGS__;        \
        LDEBUG(oss.str().c_str()); \
    } while (0)

#define XCHECK(cond) XCheck(cond, #cond, __FILE__, __LINE__)
#define XCHECK_EQ(val1, val2) \
    XCheckEq(val1, val2, #val1, #val2, __FILE__, __LINE__)
#define XCHECK_NE(val1, val2) \
    XCheckNe(val1, val2, #val1, #val2, __FILE__, __LINE__)
#define XCHECK_LE(val1, val2) \
    XCheckLe(val1, val2, #val1, #val2, __FILE__, __LINE__)
#define XCHECK_LT(val1, val2) \
    XCheckLt(val1, val2, #val1, #val2, __FILE__, __LINE__)
#define XCHECK_GE(val1, val2) \
    XCheckGe(val1, val2, #val1, #val2, __FILE__, __LINE__)
#define XCHECK_GT(val1, val2) \
    XCheckGt(val1, val2, #val1, #val2, __FILE__, __LINE__)
#define XCHECK_NOTNULL(val) XCheckNotNull(val, #val, __FILE__, __LINE__)
#define XCHECK_NEAR(val1, val2, tol)                                         \
    XCheck(std::abs((val1) - (val2)) <= (tol), #val1 " ~= " #val2, __FILE__, \
           __LINE__)

template <typename T>
inline bool XCheck(T condition, const char* name, const char* file, int line) {
    if (!(condition)) {
        AD_LDEBUG(PP) << file << ":" << line << " XCheck failed: " << name;
        return false;
    }
    return true;
}

template <typename T1, typename T2>
inline bool XCheckEq(T1 val1,
                     T2 val2,
                     const char* name1,
                     const char* name2,
                     const char* file,
                     int line) {
    if (!(val1 == val2)) {
        AD_LDEBUG(PP) << file << ":" << line << " XCheck failed: " << name1
                      << " == " << name2 << " (values: " << val1 << " vs "
                      << val2 << ")";
        return false;
    }
    return true;
}

template <typename T1, typename T2>
inline bool XCheckNe(T1 val1,
                     T2 val2,
                     const char* name1,
                     const char* name2,
                     const char* file,
                     int line) {
    if (!(val1 != val2)) {
        AD_LDEBUG(PP) << file << ":" << line << " XCheck failed: " << name1
                      << " != " << name2 << " (values: " << val1 << " vs "
                      << val2 << ")";
        return false;
    }
    return true;
}

template <typename T1, typename T2>
inline bool XCheckLe(T1 val1,
                     T2 val2,
                     const char* name1,
                     const char* name2,
                     const char* file,
                     int line) {
    if (!(val1 <= val2)) {
        AD_LDEBUG(PP) << file << ":" << line << " XCheck failed: " << name1
                      << " <= " << name2 << " (values: " << val1 << " vs "
                      << val2 << ")";
        return false;
    }
    return true;
}

template <typename T1, typename T2>
inline bool XCheckLt(T1 val1,
                     T2 val2,
                     const char* name1,
                     const char* name2,
                     const char* file,
                     int line) {
    if (!(val1 < val2)) {
        AD_LDEBUG(PP) << file << ":" << line << " XCheck failed: " << name1
                      << " < " << name2 << " (values: " << val1 << " vs "
                      << val2 << ")";
        return false;
    }
    return true;
}

template <typename T1, typename T2>
inline bool XCheckGe(T1 val1,
                     T2 val2,
                     const char* name1,
                     const char* name2,
                     const char* file,
                     int line) {
    if (!(val1 >= val2)) {
        AD_LDEBUG(PP) << file << ":" << line << " XCheck failed: " << name1
                      << " >= " << name2 << " (values: " << val1 << " vs "
                      << val2 << ")";
        return false;
    }
    return true;
}

template <typename T1, typename T2>
inline bool XCheckGt(T1 val1,
                     T2 val2,
                     const char* name1,
                     const char* name2,
                     const char* file,
                     int line) {
    if (!(val1 > val2)) {
        AD_LDEBUG(PP) << file << ":" << line << " XCheck failed: " << name1
                      << " > " << name2 << " (values: " << val1 << " vs "
                      << val2 << ")";
        return false;
    }
    return true;
}

template <typename T>
inline T XCheckNotNull(T&& t, const char* name, const char* file, int line) {
    if (!t) {
        AD_LDEBUG(PP) << file << ":" << line << " XCheck failed: " << name
                      << " must be non-NULL";
    }
    return std::forward<T>(t);
}