cmake_minimum_required(VERSION 3.15.0)
project(pnc_util VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# boost
include_directories(BEFORE /opt/senseauto_active/senseauto-3rdparty/3rdparty/boost_1.76.0/include)
link_directories(BEFORE /opt/senseauto_active/senseauto-3rdparty/3rdparty/boost_1.76.0/lib)

# abseil
if(NOT DEFINED absl_INCLUDE_DIRS)
    set(absl_INCLUDE_DIRS /opt/senseauto_active/senseauto-3rdparty/3rdparty/abseil-cpp/include)
endif()
if(NOT DEFINED absl_LIBRARY_DIRS)
    set(absl_LIBRARY_DIRS /opt/senseauto_active/senseauto-3rdparty/3rdparty/abseil-cpp/lib)
endif()
include_directories(BEFORE ${absl_INCLUDE_DIRS})
link_directories(BEFORE ${absl_LIBRARY_DIRS})


file(GLOB SRCS
  "*.cc"
  "*.cpp"
)

add_library(pnc_util STATIC ${SRCS})

target_include_directories(pnc_util PUBLIC
    ${absl_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_util PUBLIC
    pnc_proto
    pnc_math
    absl_str_format_internal
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DESTINATION include
  FILES_MATCHING PATTERN "*.h*"
)

