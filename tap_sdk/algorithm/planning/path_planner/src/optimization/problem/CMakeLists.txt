cmake_minimum_required(VERSION 3.15.0)
project(pnc_problem VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SRCS
    "*.cc"
    "*.cpp"
)

add_library(pnc_problem STATIC ${SRCS})

target_link_libraries(pnc_problem PUBLIC pnc_math)

target_include_directories(pnc_problem PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<INSTALL_INTERFACE:include>
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
