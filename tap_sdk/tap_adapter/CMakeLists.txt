cmake_minimum_required(VERSION 3.15)

# The adapter owns snapshot metadata and timestamp policy.  It deliberately
# has no RSCL, Cap'n Proto, or Planning algorithm dependency.
add_library(tap_planning_adapter STATIC
    src/planning_snapshot.cc)

target_include_directories(tap_planning_adapter
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/..")

set_target_properties(tap_planning_adapter PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON)

option(BUILD_TAP_PLANNING_TESTS
       "Build isolated smoke tests for the emergency Planning core" OFF)
if(BUILD_TAP_PLANNING_TESTS)
    enable_testing()
    add_executable(tap_planning_snapshot_test
        tests/planning_snapshot_test.cc)
    set_target_properties(tap_planning_snapshot_test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON)
    # Release builds define NDEBUG globally.  This test intentionally uses
    # assert(), so re-enable it to keep CTest meaningful in the official
    # Release verification flow.
    target_compile_options(tap_planning_snapshot_test PRIVATE -UNDEBUG)
    target_link_libraries(tap_planning_snapshot_test
        PRIVATE tap_planning_adapter)
    add_test(NAME tap_planning_snapshot_test
             COMMAND tap_planning_snapshot_test)
endif()

install(TARGETS tap_planning_adapter ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/tap_adapter
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
