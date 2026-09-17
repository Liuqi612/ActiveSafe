cmake_minimum_required(VERSION 3.14.0)
project(longsafe_2024 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 收集源文件
file(GLOB_RECURSE SOURCES_CXX ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

# Remove thirdparty files to avoid duplicate definitions from boost, etc.
list(FILTER SOURCES_CXX EXCLUDE REGEX ".*/thirdparty/.*")
list(FILTER SOURCES_C EXCLUDE REGEX ".*/thirdparty/.*")

# 排除 ert_main.c 避免重复定义 main 函数
list(FILTER SOURCES_C EXCLUDE REGEX ".*ert_main\\.c$")

# 设置源文件列表
set(SOURCES ${SOURCES_CXX} ${SOURCES_C})

# 查找依赖
find_package_sense(ADFramework REQUIRED COMPONENTS ad_log ad_rscl ad_utils)

# 创建共享库
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# 设置包含目录
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/aeb/LongSafe_SWC_ert_rtw
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/algo_interface
    ${CMAKE_CURRENT_SOURCE_DIR}/param
    ${CMAKE_CURRENT_SOURCE_DIR}/scenario_analysis
    ${CMAKE_CURRENT_SOURCE_DIR}/select/object_evaluator
    ${CMAKE_CURRENT_SOURCE_DIR}/select/threat_assessment
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    /opt/senseauto/senseauto-rscl/active/lib
    ${HOBOT_INCLUDE_DIRS}
    ${PATH_SOURCE_3RDPARTY}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/eigen-3.3.9/include/eigen3
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../interface
    ${CMAKE_CURRENT_SOURCE_DIR}/../../math/geometry
    ${CMAKE_CURRENT_SOURCE_DIR}/../../math/historyinfo
)

# 链接库
target_link_libraries(${PROJECT_NAME}
    PUBLIC
    m
)

# 安装
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
)
