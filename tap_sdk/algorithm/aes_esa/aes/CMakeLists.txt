cmake_minimum_required(VERSION 3.14.0)
project(aeb_ctrl VERSION 2.0.0 LANGUAGES C)
message(STATUS "${BoldGreen}[${PROJECT_NAME}]${ColourReset} Building....")
# CXX version
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED on)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE C_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c )
# remove main
list(REMOVE_ITEM C_SRC ${CMAKE_CURRENT_SOURCE_DIR}/AES_ESA_SWC_ert_rtw/ert_main.c)

set(SOURCES
  ${C_SRC}
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

foreach(filename ${HEADERS})
  get_filename_component(file_dir ${filename} DIRECTORY)
  list(APPEND HEADER_DIRS ${file_dir})
endforeach()
list(REMOVE_DUPLICATES HEADER_DIRS)
message(${HEADER_DIRS})

# lib
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${HEADER_DIRS}
)

target_link_libraries(
  ${PROJECT_NAME}
  m
)
install(TARGETS ${PROJECT_NAME}
LIBRARY DESTINATION "lib"
)
