cmake_minimum_required(VERSION 3.15.0)
project(pnc_math_segment_matcher VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SRC_FILES
    "*.cc"
    "*.cpp"
)

add_library(pnc_math_segment_matcher STATIC ${SRC_FILES})

target_include_directories(pnc_math_segment_matcher PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_math_segment_matcher PUBLIC
    pnc_math_geometry
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
