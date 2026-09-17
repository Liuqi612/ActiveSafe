cmake_minimum_required(VERSION 3.15.0)
project(pnc_maps VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SRCS
  "*.cc"
  "*.cpp"
)
add_library(pnc_maps STATIC ${SRCS})

target_include_directories(pnc_maps PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_maps PUBLIC
    pnc_proto
    pnc_math
    pnc_container
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DESTINATION include
  FILES_MATCHING PATTERN "*.h*"
)


