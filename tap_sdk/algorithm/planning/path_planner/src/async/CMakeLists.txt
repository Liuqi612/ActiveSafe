cmake_minimum_required(VERSION 3.15.0)
project(pnc_async VERSION 0.1.0 LANGUAGES C CXX)

add_library(pnc_async STATIC
  ./thread_pool.cc
  ./parallel_for.cc
)

target_include_directories(pnc_async PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_async PUBLIC
  glog
  pnc_util
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION include
        FILES_MATCHING PATTERN "*.h*"
)


