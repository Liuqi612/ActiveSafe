cmake_minimum_required(VERSION 3.15.0)
project(pnc_speed VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SRCS
    "*.cc"
    "*.cpp"
)

add_library(pnc_speed STATIC ${SRCS})

target_include_directories(pnc_speed PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_speed PUBLIC
    pnc_math
    pnc_maps
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
