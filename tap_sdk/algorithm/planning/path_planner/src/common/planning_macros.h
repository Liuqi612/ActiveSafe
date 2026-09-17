
#pragma once

#include <absl/cleanup/cleanup.h>
#include "common/log.h"

#define DECLARE_CLASS_SINGLETON(classname) \
 public:                                   \
    static classname *instance() {         \
        static classname instance;         \
        return &instance;                  \
    }                                      \
                                           \
 private:                                  \
    classname()

#define QUIT_IF(CONDITION, RET, LEVEL, MSG, ...) \
    do {                                         \
        if (CONDITION) {                         \
            L##LEVEL((MSG), ##__VA_ARGS__);      \
            return (RET);                        \
        }                                        \
    } while (0)

#define QUIT_IF_VOID_QUIET(CONDITION) \
    do {                              \
        if (CONDITION) {              \
            return;                   \
        }                             \
    } while (0)

#define QUIT_IF_VOID(CONDITION, LEVEL, MSG, ...) \
    do {                                         \
        if (CONDITION) {                         \
            L##LEVEL((MSG), ##__VA_ARGS__);      \
            return;                              \
        }                                        \
    } while (0)

#define PRED_CALL_MACRO_(_, N, MACRO) (MACRO)(N)
#define PRED_DIRECT_RUN_(_, N, CODE) (CODE)

// Simple macro expansion for small repetitions (0-9)
#define PLAN_REPEAT_0(MACRO)
#define PLAN_REPEAT_1(MACRO) MACRO(0)
#define PLAN_REPEAT_2(MACRO) PLAN_REPEAT_1(MACRO) MACRO(1)
#define PLAN_REPEAT_3(MACRO) PLAN_REPEAT_2(MACRO) MACRO(2)
#define PLAN_REPEAT_4(MACRO) PLAN_REPEAT_3(MACRO) MACRO(3)
#define PLAN_REPEAT_5(MACRO) PLAN_REPEAT_4(MACRO) MACRO(4)
#define PLAN_REPEAT_6(MACRO) PLAN_REPEAT_5(MACRO) MACRO(5)
#define PLAN_REPEAT_7(MACRO) PLAN_REPEAT_6(MACRO) MACRO(6)
#define PLAN_REPEAT_8(MACRO) PLAN_REPEAT_7(MACRO) MACRO(7)
#define PLAN_REPEAT_9(MACRO) PLAN_REPEAT_8(MACRO) MACRO(8)

#define PLAN_REPEAT_CONCAT(N, MACRO) PLAN_REPEAT_##N(MACRO)
#define PLAN_REPEAT(N, MACRO) PLAN_REPEAT_CONCAT(N, MACRO)

#define PLAN_SIMPLE_REPEAT_0(CODE)
#define PLAN_SIMPLE_REPEAT_1(CODE) CODE
#define PLAN_SIMPLE_REPEAT_2(CODE) PLAN_SIMPLE_REPEAT_1(CODE) CODE
#define PLAN_SIMPLE_REPEAT_3(CODE) PLAN_SIMPLE_REPEAT_2(CODE) CODE
#define PLAN_SIMPLE_REPEAT_4(CODE) PLAN_SIMPLE_REPEAT_3(CODE) CODE
#define PLAN_SIMPLE_REPEAT_5(CODE) PLAN_SIMPLE_REPEAT_4(CODE) CODE

#define PLAN_SIMPLE_REPEAT_CONCAT(N, CODE) PLAN_SIMPLE_REPEAT_##N(CODE)
#define PLAN_SIMPLE_REPEAT(N, CODE) PLAN_SIMPLE_REPEAT_CONCAT(N, CODE)

#define PLAN_UNUSED(variable) (void)(variable)

#define DECLARE_PTR(CLASS)                     \
    using Ptr = std::shared_ptr<CLASS>;        \
    using UPtr = std::unique_ptr<CLASS>;       \
    using CPtr = std::shared_ptr<const CLASS>; \
    using CUPtr = std::unique_ptr<const CLASS>

#define VAR_CONCAT_INNER(VAR1, VAR2) VAR1##VAR2

#define VAR_CONCAT(VAR1, VAR2) VAR_CONCAT_INNER((VAR1), (VAR2))

#define RETURN_IF_NOT_OK(lhs, status_or_exp) \
    RETURN_IF_NOT_OK_3_((lhs), VAR_CONCAT(statusor, __LINE__), (status_or_exp))

#define RETURN_IF_NOT_OK_3_(lhs, statusor_var, statusor_exp) \
    auto statusor_var = (statusor_exp);                      \
    if (!(statusor_var).ok()) {                              \
        return (statusor_var).status();                      \
    }                                                        \
    (lhs) = std::move(statusor_var).value();

#define SCOPED_TRACE(name) \
    // const auto &_function_name = (name);                                         \
  // AD_LINFO(PP) << _function_name;                                                 \
  // pnc_x::Timer _scope_timer(_function_name);
