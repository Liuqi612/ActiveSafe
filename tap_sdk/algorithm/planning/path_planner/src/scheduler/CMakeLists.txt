cmake_minimum_required(VERSION 3.15.0)
project(pnc_scheduler VERSION 0.1.0 LANGUAGES C CXX)

# find_package(gflags REQUIRED)

file(GLOB SRCS
    "*.cc"
    "*.cpp"
)

add_library(pnc_scheduler STATIC ${SRCS})

target_include_directories(pnc_scheduler PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_scheduler PUBLIC
    pnc_math
    pnc_maps
    # gflags
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
