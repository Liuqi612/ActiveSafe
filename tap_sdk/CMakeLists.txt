cmake_minimum_required(VERSION 3.14.0)
project(tap VERSION 2.0.0 LANGUAGES CXX)
message(STATUS "${BoldGreen}[${PROJECT_NAME}]${ColourReset} Building....")

include(cmake/toolchain.cmake)

# CXX version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES_CXX ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

# Remove thirdparty files to avoid duplicate definitions from boost, etc.
list(FILTER SOURCES_CXX EXCLUDE REGEX ".*/thirdparty/.*")
list(FILTER SOURCES_C EXCLUDE REGEX ".*/thirdparty/.*")

# LongSafe Legacy 编译开关
option(USE_LONGSAFE_LEGACY "Enable LongSafe Legacy support" OFF)

# LongSafe Legacy 目录路径（在 myself/longsafe 下）
# 注意：CMAKE_CURRENT_SOURCE_DIR 可能是符号链接（如 node/module/tap_sdk -> ../../tap_sdk）
# 需要解析到实际路径，然后找到 myself 目录下的 longsafe
get_filename_component(CURRENT_DIR_REAL "${CMAKE_CURRENT_SOURCE_DIR}" REALPATH)
get_filename_component(PARENT_DIR "${CURRENT_DIR_REAL}/.." ABSOLUTE)
set(LONGSAFE_LEGACY_DIR "${PARENT_DIR}/longsafe")

# 根据开关决定是否启用 LongSafe Legacy
if(USE_LONGSAFE_LEGACY)
    if(EXISTS "${LONGSAFE_LEGACY_DIR}" AND IS_DIRECTORY "${LONGSAFE_LEGACY_DIR}")
        # 添加 longsafe 目录的源文件
        file(GLOB_RECURSE LONGSAFE_SOURCES_CXX "${LONGSAFE_LEGACY_DIR}/*.cpp")
        file(GLOB_RECURSE LONGSAFE_SOURCES_C "${LONGSAFE_LEGACY_DIR}/*.c")
        list(APPEND SOURCES_CXX ${LONGSAFE_SOURCES_CXX})
        list(APPEND SOURCES_C ${LONGSAFE_SOURCES_C})
        
        # 为了兼容代码中的 #include "algorithm/longsafe/..." 路径
        # 在 tap_sdk/algorithm/ 目录下创建符号链接指向 ../longsafe
        set(ALGORITHM_LONGSAFE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/algorithm/longsafe")
        set(ALGORITHM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/algorithm")
        
        # 确保 algorithm 目录存在
        if(NOT EXISTS "${ALGORITHM_DIR}")
            file(MAKE_DIRECTORY "${ALGORITHM_DIR}")
        endif()
        
        # 如果符号链接或目录不存在，创建它
        if(NOT EXISTS "${ALGORITHM_LONGSAFE_LINK}")
            # 计算从 CMAKE_CURRENT_SOURCE_DIR 到 LONGSAFE_LEGACY_DIR 的相对路径
            file(RELATIVE_PATH RELATIVE_LONGSAFE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${LONGSAFE_LEGACY_DIR}")
            # 使用 CMake 的 create_symlink 命令（跨平台）
            execute_process(
                COMMAND ${CMAKE_COMMAND} -E create_symlink 
                "${RELATIVE_LONGSAFE_PATH}" 
                "${ALGORITHM_LONGSAFE_LINK}"
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE SYMLINK_RESULT
                ERROR_QUIET
            )
            if(SYMLINK_RESULT EQUAL 0)
                message(STATUS "Created symlink: ${ALGORITHM_LONGSAFE_LINK} -> ${RELATIVE_LONGSAFE_PATH}")
            else()
                # 如果符号链接失败（Windows 或权限问题）
                # 注意：Windows 上需要管理员权限才能创建符号链接
                message(WARNING "Failed to create symlink for longsafe, code may need to use 'longsafe/...' instead of 'algorithm/longsafe/...'")
            endif()
        endif()
        
        add_definitions(-DUSE_LONGSAFE_LEGACY=1)
        message(STATUS "${BoldGreen}LongSafe Legacy: ENABLED${ColourReset} (${LONGSAFE_LEGACY_DIR})")
    else()
        message(WARNING "USE_LONGSAFE_LEGACY is ON but directory not found: ${LONGSAFE_LEGACY_DIR}")
        add_definitions(-DUSE_LONGSAFE_LEGACY=0)
        message(STATUS "${BoldYellow}LongSafe Legacy: DISABLED (directory not found)${ColourReset}")
    endif()
else()
    add_definitions(-DUSE_LONGSAFE_LEGACY=0)
    message(STATUS "${BoldYellow}LongSafe Legacy: DISABLED (option is OFF)${ColourReset}")
endif()

# Explicitly add json11 since it is required
list(APPEND SOURCES_CXX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/json11/json11.cpp)

# Remove ert_main.c to avoid multiple definition of 'main'
list(FILTER SOURCES_C EXCLUDE REGEX ".*ert_main\\.c$")

set(SOURCES ${SOURCES_CXX} ${SOURCES_C})

find_package_sense(ADFramework REQUIRED COMPONENTS ad_log ad_rscl ad_time ad_utils)

set(PROJECT_NAME_SO "${PROJECT_NAME}_so")

add_library(${PROJECT_NAME_SO} SHARED ${SOURCES})

target_link_options(${PROJECT_NAME_SO} PRIVATE
  "LINKER:-rpath,/opt/senseauto/senseauto-tap/active/lib")

target_include_directories(
  ${PROJECT_NAME_SO}
  PUBLIC  
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/json11
  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/eigen-3.3.9/include/eigen3
  /opt/senseauto_active/senseauto-rscl/include
  ${HOBOT_INCLUDE_DIRS}
  ${PATH_SOURCE_3RDPARTY}/include
  ${HOBOT_ROOT}/param_manager/include
)

# 如果启用了 LongSafe Legacy，头文件搜索路径已经包含 ${CMAKE_CURRENT_SOURCE_DIR}
# 因此可以通过 #include "algorithm/longsafe/..." 访问（通过符号链接）
# 不需要额外添加 include 路径

target_link_directories(${PROJECT_NAME_SO}
PUBLIC
  /opt/senseauto/senseauto-rscl/active/lib
)

target_link_libraries(
  ${PROJECT_NAME_SO}
  m
  ad_log
)

install(TARGETS ${PROJECT_NAME_SO}
LIBRARY DESTINATION "lib"
)
