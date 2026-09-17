cmake_minimum_required(VERSION 3.15.0)
project(pnc_math VERSION 0.1.0 LANGUAGES C CXX)

# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Eigen3 REQUIRED)

add_subdirectory(geometry)
add_subdirectory(segment_matcher)

file(GLOB SRC_FILES
  "*.cc"
  "*.cpp"
)

add_library(pnc_math STATIC ${SRC_FILES})

target_include_directories(pnc_math PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  $<INSTALL_INTERFACE:include>
)

# abseil
include_directories(/opt/senseauto_active/senseauto-3rdparty/3rdparty/abseil-cpp/include)
link_directories(/opt/senseauto_active/senseauto-3rdparty/3rdparty/abseil-cpp/lib)

target_link_libraries(pnc_math PUBLIC
  Eigen3::Eigen
  pnc_math_geometry
  pnc_math_segment_matcher
  pnc_proto
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DESTINATION include
  FILES_MATCHING PATTERN "*.h*"
)
