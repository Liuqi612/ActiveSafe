cmake_minimum_required(VERSION 3.15.0)
project(pnc_container VERSION 0.1.0 LANGUAGES C CXX)

add_library(pnc_container INTERFACE)

target_include_directories(pnc_container INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  $<INSTALL_INTERFACE:include>
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION include
        FILES_MATCHING PATTERN "*.h*"
)


