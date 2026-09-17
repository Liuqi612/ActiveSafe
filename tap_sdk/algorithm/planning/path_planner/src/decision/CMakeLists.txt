cmake_minimum_required(VERSION 3.15.0)
project(pnc_decision VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SRCS
    "*.cc"
    "*.cpp"
)

add_library(pnc_decision STATIC ${SRCS})

target_include_directories(pnc_decision PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_decision PUBLIC
    pnc_math
    pnc_maps
    pnc_common
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
