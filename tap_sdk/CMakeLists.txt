cmake_minimum_required(VERSION 3.14.0)
project(tap VERSION 2.0.0 LANGUAGES CXX)
message(STATUS "${BoldGreen}[${PROJECT_NAME}]${ColourReset} Building....")

include(cmake/toolchain.cmake)

# CXX version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES_CXX ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

# Remove thirdparty files to avoid duplicate definitions from boost, etc.
list(FILTER SOURCES_CXX EXCLUDE REGEX ".*/thirdparty/.*")
list(FILTER SOURCES_C EXCLUDE REGEX ".*/thirdparty/.*")

# Planning is a separately-portable library.  Keep its explicit source lists
# out of the legacy repository-wide glob so it cannot be linked into tap_so
# accidentally.
list(FILTER SOURCES_CXX EXCLUDE REGEX ".*/algorithm/planning/.*")
list(FILTER SOURCES_C EXCLUDE REGEX ".*/algorithm/planning/.*")

# Remove longsafe_2024 subproject sources (avoid duplicate definitions)
list(FILTER SOURCES_CXX EXCLUDE REGEX ".*/algorithm/longsafe_2024/.*")
list(FILTER SOURCES_C EXCLUDE REGEX ".*/algorithm/longsafe_2024/.*")

# Remove longsafe_2024_newtsel subproject sources (avoid duplicate definitions)
list(FILTER SOURCES_CXX EXCLUDE REGEX ".*/algorithm/longsafe_2024_newtsel/.*")
list(FILTER SOURCES_C EXCLUDE REGEX ".*/algorithm/longsafe_2024_newtsel/.*")

# Explicitly add json11 since it is required
list(APPEND SOURCES_CXX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/json11/json11.cpp)

# Remove ert_main.c to avoid multiple definition of 'main'
list(FILTER SOURCES_C EXCLUDE REGEX ".*ert_main\\.c$")

# Add longsafe_2024 subdirectory
add_subdirectory(algorithm/longsafe_2024)
add_subdirectory(algorithm/longsafe_2024_newtsel)

# AES ert/_sharedutils shares some utility functions with AEB's LongSafe_SWC_ert_rtw.
# Exclude the pure-function duplicates from AES (these are binary-identical across codegen).
# Note: const_params.c is kept from BOTH because each model has model-specific pool constants;
#       --allow-multiple-definition handles the small set of identical pooled symbols.
set(AES_SHAREDUTILS_DUPS
  look1_iflf_binlcapw
  look1_iflf_binlcpw
  look1_iflf_binlxpw
  rtGetInf
  rtGetNaN
  rt_nonfinite
)
foreach(_f ${AES_SHAREDUTILS_DUPS})
  list(FILTER SOURCES_C EXCLUDE REGEX ".*/aes_esa/aes/ert/_sharedutils/${_f}\\.c$")
endforeach()

set(SOURCES ${SOURCES_CXX} ${SOURCES_C})

find_package_sense(ADFramework REQUIRED COMPONENTS ad_log ad_rscl ad_time ad_utils)

set(PROJECT_NAME_SO "${PROJECT_NAME}_so")

add_library(${PROJECT_NAME_SO} SHARED ${SOURCES})

target_link_options(${PROJECT_NAME_SO} PRIVATE
  "LINKER:-rpath,/opt/senseauto/senseauto-tap/active/lib"
  # Both AEB and AES const_params.c define a small shared subset of rtCP_pooled_* symbols.
  # These are identical (hash-named), so allow the duplicate; the first definition wins.
  "LINKER:--allow-multiple-definition")

target_include_directories(
  ${PROJECT_NAME_SO}
  PUBLIC  
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/json11
  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/eigen-3.3.9/include/eigen3
  # AES 模型头文件路径
  ${CMAKE_CURRENT_SOURCE_DIR}/algorithm/aes_esa/aes/AES_ESA_SWC_ert_rtw
  ${CMAKE_CURRENT_SOURCE_DIR}/algorithm/aes_esa/aes/ert/_sharedutils
  ${CMAKE_CURRENT_SOURCE_DIR}/algorithm/aes_esa/aes/CAL
  # MemMap.h 空桩：AUTOSAR 平台文件，x86 CI 无 BSW 层故需桩文件
  # 放在 aes 代码产物目录外，替换 aes 代码包时不会被覆盖
  ${CMAKE_CURRENT_SOURCE_DIR}/algorithm/aes_esa/platform_stubs
  /opt/senseauto_active/senseauto-rscl/include
  ${HOBOT_INCLUDE_DIRS}
  ${PATH_SOURCE_3RDPARTY}/include
  ${HOBOT_ROOT}/param_manager/include
)

# Add LongSafe include directory
target_include_directories(${PROJECT_NAME_SO} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/algorithm/longsafe)

# Add longsafe_2024 include directory
target_include_directories(${PROJECT_NAME_SO} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/algorithm/longsafe_2024)
target_include_directories(${PROJECT_NAME_SO} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/algorithm/longsafe_2024_newtsel)

target_link_directories(${PROJECT_NAME_SO}
PUBLIC
  /opt/senseauto/senseauto-rscl/active/lib
)

target_link_libraries(
  ${PROJECT_NAME_SO}
  m
  ad_log
  longsafe_2024
  longsafe_2024_newtsel
)

install(TARGETS ${PROJECT_NAME_SO}
LIBRARY DESTINATION "lib"
)

# The emergency Planning core and its normalized adapter are opt-in for the
# module repository; node enables this target when building the integrated
# emergency path.
add_subdirectory(tap_adapter)
option(BUILD_TAP_PLANNING_CORE
       "Build the independently ported emergency Planning core" OFF)
if(BUILD_TAP_PLANNING_CORE)
    add_subdirectory(algorithm/planning)
    add_subdirectory(tap_adapter/core)
endif()
