cmake_minimum_required(VERSION 3.15.0)
project(pnc_plan VERSION 0.1.0 LANGUAGES C CXX)

find_package(Eigen3 REQUIRED)

file(GLOB SRCS
  "*.cc"
  "*.cpp"
)

add_library(pnc_plan STATIC ${SRCS}
)

target_include_directories(pnc_plan PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_plan PUBLIC
  Eigen3::Eigen
  pnc_math
  pnc_proto
  pnc_problem
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DESTINATION include
  FILES_MATCHING PATTERN "*.h*"
)


