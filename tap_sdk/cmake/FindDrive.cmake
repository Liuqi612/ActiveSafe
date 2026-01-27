## Copyright (C) 2019-2020 by SenseTime Group Limited. All rights reserved.

if(DRIVE_IS_INCLUDED)
    return()
endif()
set(DRIVE_IS_INCLUDED CACHE BOOL "" true)

## Append to search driveworks samples cmake first
list(APPEND CMAKE_MODULE_PATH "/usr/local/driveworks/samples/cmake/")

## Get Cuda
if (CMAKE_CROSSCOMPILING)
    set(CUDA_TOOLKIT_TARGET_DIR /usr/local/cuda/targets/aarch64-linux)
endif ()
find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})
include_directories(${CUDA_INCLUDE_DIRS}/thrust/system/cuda/detail)

## Get Cudnn
if(CMAKE_CROSSCOMPILING)
    find_library(CUDNN_LIBRARIES NAMES cudnn)
else()
    set(CUDNN_LIBRARIES cudnn)
endif()

## Get TensorRT
find_library(TENSORRT_LIBRARIES NAMES libnvinfer.so.5
    PATHS /usr/local/driveworks-2.0/targets/${PLATFORM_NAME}-Linux/lib NO_DEFAULT_PATH)
include_directories(/usr/local/driveworks/targets/${PLATFORM_NAME}-Linux/include/dw)

## Get Driveworks
# Compilation with >g++-4.9 is not officially supported in CUDA10.0
set(DW_EXPERIMENTAL_ENABLE_ABI11 ON CACHE BOOL docstring)
message(STATUS "DW_EXPERIMENTAL_ENABLE_ABI11 enable")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
find_package(Driveworks REQUIRED)
include_directories(${Driveworks_INCLUDE_DIRS})
set(Driveworks_LIBS "")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)

## Get Opencv
# refer: https://gitlab.kitware.com/cmake/cmake/issues/17150
set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)

# nvcc compiler
set(CUDA_NVCC_FLAGS "")
list(APPEND CUDA_NVCC_FLAGS -std=c++11;-O2)
list(APPEND CUDA_NVCC_FLAGS -Xcompiler;-fPIC)
if(NOT CPPBUILD_TEST)
    list(APPEND CUDA_NVCC_FLAGS -Xcompiler;-fvisibility=hidden)
endif()

list(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_60,code=sm_60)
list(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_61,code=sm_61)
# DRIVE AGX Xavier: 1x Volta iGPU(sm=7.2)
list(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_72,code=sm_72)
# DRIVE AGX Pegasus: 2x Volta iGPU(sm=7.2) + 2x Turing dGPUs(sm=7.5)
list(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_75,code=sm_75)

list(APPEND CUDA_NVCC_FLAGS --default-stream per-thread)
if (CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "${Blue}NVCC DEBUG FLAG: -G${ColourReset}")
    list(APPEND CUDA_NVCC_FLAGS -G)
endif()

set(CUDA_HOST_COMPILER ${CMAKE_CXX_COMPILER})
set(CUDA_PROPAGATE_HOST_FLAGS OFF)

# export libraries
set(CUDA_LIBS "")
list(APPEND CUDA_LIBS ${CUDA_curand_LIBRARY})
list(APPEND CUDA_LIBS ${CUDA_cusparse_LIBRARY})
list(APPEND CUDA_LIBS ${CUDA_CUBLAS_LIBRARIES})

list(APPEND CUDA_LIBS ${CUDA_LIBRARIES})
list(APPEND CUDA_LIBS ${CUDNN_LIBRARIES})
list(APPEND CUDA_LIBS ${TENSORRT_LIBRARIES})

# NVTX from cuda, installed by Drive Software
# TODO(chenshengjie): localization depends on ${NVTX_LIBS}
set(NVTX_LIBS "/usr/local/driveworks/targets/${PLATFORM_NAME}-${CMAKE_SYSTEM_NAME}/lib/libnvToolsExt.so.1")
if (BUILD_NVTX)
    file(GLOB NVTX_INCLUDE_DIRS "/opt/nvidia/nsight-systems/*/target-${TARGET_OS}-x64/nvtx/include")
    if (NOT NVTX_INCLUDE_DIRS)
        VMESSAGE(FATAL "Failed to find nvtx include directories in '/opt/nvidia/nsight-systems/*/target-${TARGET_OS}-x64/nvtx/include'")
    endif()
    include_directories(SYSTEM ${NVTX_INCLUDE_DIRS})
endif()
list(APPEND CUDA_LIBS ${NVTX_LIBS})

if(Driveworks_FOUND)
    add_definitions(-DUSE_DRIVEWORKS)
    add_definitions(-DCUDA_API_PER_THREAD_DEFAULT_STREAM)
    add_definitions(-DDRIVEWORKS_GE_2_0)
    if (PLATFORM_NAME MATCHES aarch64)
        # make sure VIBRANTE ON on DRIVE AGX platforms
        set(VIBRANTE ON CACHE BOOL docstring)
        add_definitions(-DVIBRANTE)
    endif ()
endif()

if(VIBRANTE)
    find_library(EGL_LIBRARY NAMES EGL)
    set(Driveworks_LIBS
        ${Driveworks_LIBRARIES}
        ${EGL_LIBRARY}
    )
    find_library(CUDA_LIBRARY NAMES cuda)
    list(APPEND CUDA_LIBS "${CUDA_LIBRARY}")
else()
    set(Driveworks_LIBS ${Driveworks_LIBRARIES})
endif()

message(STATUS "${Green}======================================================")
message(STATUS " CUDA DIR: ${CUDA_TOOLKIT_ROOT_DIR}")
message(STATUS " CUDNN DIR: header: ${CUDNN_INCLUDE_DIR} lib: ${CUDNN_LIBRARIES}")
message(STATUS " TensorRT DIR: header: ${TENSORRT_INCLUDE_DIRS} lib: ${TENSORRT_LIBRARIES}")
message(STATUS " DRIVEWORKS DIR: header: ${Driveworks_INCLUDE_DIRS} lib: ${Driveworks_LIBRARIES}")
message(STATUS "======================================================${ColourReset}")
