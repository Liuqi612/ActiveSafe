cmake_minimum_required(VERSION 3.15.0)
project(pnc_ddp VERSION 0.1.0 LANGUAGES C CXX)

find_package_sense(ADMsgIDL REQUIRED)

file(GLOB SRCS
    "*.cc"
    "*.cpp"
)

add_library(pnc_ddp STATIC ${SRCS})

target_link_libraries(pnc_ddp PUBLIC
    pnc_math
    pnc_common
    pnc_async
    pnc_util
    pnc_maps
    pnc_object
    pnc_rounter
)

target_include_directories(pnc_ddp PUBLIC
    ${ADMsgIDL_INCLUDE_DIRS}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<INSTALL_INTERFACE:include>
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
