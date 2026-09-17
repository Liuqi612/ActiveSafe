cmake_minimum_required(VERSION 3.15.0)
project(pnc_initializer VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SRCS
    "*.cc"
    "*.cpp"
)

add_library(pnc_initializer STATIC ${SRCS})

target_include_directories(pnc_initializer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_initializer PUBLIC
    pnc_math
    pnc_async
    pnc_maps
    pnc_proto
    pnc_decision
    pnc_scheduler
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
