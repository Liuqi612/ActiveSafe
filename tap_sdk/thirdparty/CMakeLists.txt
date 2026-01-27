cmake_minimum_required(VERSION 3.14.0)
project(thirdparty VERSION 2.0.0 LANGUAGES C)
message(STATUS "${BoldGreen}[${PROJECT_NAME}]${ColourReset} Building....")
# CXX version
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED on)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(json11)
add_subdirectory(eigen-3.3.9)
