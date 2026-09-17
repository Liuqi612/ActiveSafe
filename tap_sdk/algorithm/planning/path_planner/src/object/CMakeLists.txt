cmake_minimum_required(VERSION 3.15.0)
project(pnc_object VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SRCS
    "*.cc"
    "*.cpp"
)

add_library(pnc_object STATIC ${SRCS})

target_include_directories(pnc_object PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_object PUBLIC
    pnc_async
    pnc_math
    pnc_prediction
    pnc_speed
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
