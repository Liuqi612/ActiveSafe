cmake_minimum_required(VERSION 3.15.0)
project(pnc_common VERSION 0.1.0 LANGUAGES C CXX)

# find_package(gflags REQUIRED)
find_package_sense(ADFramework REQUIRED COMPONENTS ad_log ad_common ad_time)

file(GLOB SRCS
  "*.cc"
  "*.cpp"
)
add_library(pnc_common STATIC ${SRCS})

target_include_directories(pnc_common PUBLIC
  ${ADFramework_INCLUDE_DIRS}
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_common PUBLIC
  ${ADFramework_LIBRARIES}
  pnc_proto
  pnc_math
  pnc_plan
  # gflags
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DESTINATION include
  FILES_MATCHING PATTERN "*.h*"
)


