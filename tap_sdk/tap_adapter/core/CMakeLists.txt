cmake_minimum_required(VERSION 3.15)

# This target is deliberately created after tap_planning_core.  It converts
# normalized data at the adapter boundary; it does not add a second planner.
add_library(tap_planning_core_adapter STATIC
    planning_core_adapter.cc
    planning_object_adapter.cc
    planning_runtime_adapter.cc)

target_include_directories(tap_planning_core_adapter
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/../.."
        "${CMAKE_CURRENT_LIST_DIR}/../../algorithm/planning"
        "${CMAKE_CURRENT_LIST_DIR}/../../algorithm/planning/path_planner/src")
target_link_libraries(tap_planning_core_adapter
    PUBLIC tap_planning_core)
set_target_properties(tap_planning_core_adapter PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON)

option(BUILD_TAP_PLANNING_TESTS
       "Build isolated smoke tests for the emergency Planning core" OFF)
if(BUILD_TAP_PLANNING_TESTS)
    add_executable(tap_planning_core_adapter_test
        planning_core_adapter_test.cc)
    target_link_libraries(tap_planning_core_adapter_test
        PRIVATE tap_planning_core_adapter)
    set_target_properties(tap_planning_core_adapter_test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON)
    target_compile_options(tap_planning_core_adapter_test PRIVATE -UNDEBUG)
    add_test(NAME tap_planning_core_adapter_test
             COMMAND tap_planning_core_adapter_test)

    add_executable(tap_planning_object_adapter_test
        planning_object_adapter_test.cc)
    target_link_libraries(tap_planning_object_adapter_test
        PRIVATE tap_planning_core_adapter)
    set_target_properties(tap_planning_object_adapter_test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON)
    target_compile_options(tap_planning_object_adapter_test PRIVATE -UNDEBUG)
    add_test(NAME tap_planning_object_adapter_test
             COMMAND tap_planning_object_adapter_test)

    add_executable(tap_planning_runtime_adapter_test
        planning_runtime_adapter_test.cc)
    target_link_libraries(tap_planning_runtime_adapter_test
        PRIVATE tap_planning_core_adapter)
    target_compile_definitions(tap_planning_runtime_adapter_test PRIVATE
        "TAP_PLANNING_RUNTIME_CONFIG_DIR=\"${CMAKE_CURRENT_LIST_DIR}/../../algorithm/planning/resource/config\"")
    set_target_properties(tap_planning_runtime_adapter_test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON)
    target_compile_options(tap_planning_runtime_adapter_test PRIVATE -UNDEBUG)
    add_test(NAME tap_planning_runtime_adapter_test
             COMMAND tap_planning_runtime_adapter_test)
endif()

install(TARGETS tap_planning_core_adapter ARCHIVE DESTINATION lib)
install(FILES planning_core_adapter.h planning_object_adapter.h
              planning_normalized_types.h planning_runtime_adapter.h
              planning_runtime_types.h
        DESTINATION include/tap_adapter/core)
