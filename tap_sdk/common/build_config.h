#pragma once

#ifndef USE_LONGSAFE_LEGACY
    // 优先从 tap_sdk/.. 目录（myself 目录）查找 longsafe 头文件
    #if __has_include("../longsafe/decision/lgsf_function.h")
        #define USE_LONGSAFE_LEGACY 1
    #else
        #define USE_LONGSAFE_LEGACY 0
    #endif
#endif

