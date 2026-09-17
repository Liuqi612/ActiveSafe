cmake_minimum_required(VERSION 3.15.0)
project(pnc_math_geometry VERSION 0.1.0 LANGUAGES C CXX)

find_package_sense(ADFramework REQUIRED COMPONENTS ad_log ad_common ad_time)
find_package(Eigen3 REQUIRED)

file(GLOB SRC_FILES
    "*.cc"
    "*.cpp"
)

add_library(pnc_math_geometry STATIC ${SRC_FILES})

target_include_directories(pnc_math_geometry PUBLIC
    ${ADFramework_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(pnc_math_geometry PUBLIC
    ${ADFramework_LIBRARIES}
    Eigen3::Eigen
    glog
    pnc_proto
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
