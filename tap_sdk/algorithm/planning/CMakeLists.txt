cmake_minimum_required(VERSION 3.15)
project(tap_planning_core LANGUAGES CXX)

# This target is the rule-based emergency Planning core.  Its source list is
# intentionally explicit: DLP-only modules and future unreviewed files cannot
# enter production by appearing in the source tree.
set(TAP_PLANNING_SRC_ROOT "${CMAKE_CURRENT_LIST_DIR}/path_planner/src")
set(TAP_PLANNING_PROTO_ROOT "${TAP_PLANNING_SRC_ROOT}/proto")
set(TAP_PLANNING_GENERATED_ROOT "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(TAP_PLANNING_SOURCES
    path_planner/src/async/parallel_for.cc
    path_planner/src/async/thread_pool.cc
    path_planner/src/common/assist_util.cc
    path_planner/src/common/gflags.cc
    path_planner/src/common/lane_change_safety.cc
    path_planner/src/common/log.cc
    path_planner/src/common/path_sl_boundary.cc
    path_planner/src/common/timer.cc
    path_planner/src/common/type_def.cc
    path_planner/src/common/vehicle_behavior_helper.cc
    path_planner/src/common/vehicle_speed_config_helper.cc
    path_planner/src/decision/constraint_manager.cc
    path_planner/src/decision/decision_util.cc
    path_planner/src/decision/leading_groups_builder.cc
    path_planner/src/decision/obstacle_intention_estimation.cc
    path_planner/src/initializer/a_star_motion_searcher_defs.cc
    path_planner/src/initializer/a_star_motion_searcher_util.cc
    path_planner/src/initializer/brute_force_collision_checker.cc
    path_planner/src/initializer/collision_checker.cc
    path_planner/src/initializer/cost_provider.cc
    # Shared interaction cost features used by A*; the DP search implementation
    # itself is only in tap_planning_dp_initializer below.
    path_planner/src/initializer/dp_cost_feature.cc
    path_planner/src/initializer/dp_motion_searcher_util.cc
    path_planner/src/initializer/geometry/geometry_form.cc
    path_planner/src/initializer/geometry/geometry_form_builder.cc
    path_planner/src/initializer/geometry/geometry_graph.cc
    path_planner/src/initializer/geometry/geometry_graph_builder.cc
    path_planner/src/initializer/geometry/geometry_graph_cache.cc
    path_planner/src/initializer/geometry/geometry_graph_debug.cc
    path_planner/src/initializer/initializer_util.cc
    path_planner/src/initializer/interactive_search/decision_extractor/gap_decision.cc
    path_planner/src/initializer/interactive_search/decision_extractor/object_decision.cc
    path_planner/src/initializer/interactive_search/decision_groups_generator/compute_decision_group.cc
    path_planner/src/initializer/interactive_search/map/grid_map.cc
    path_planner/src/initializer/interactive_search/search/a_star_search.cc
    path_planner/src/initializer/interactive_search/search/goal_condition.cc
    path_planner/src/initializer/interactive_search/search/interaction_cost.cc
    path_planner/src/initializer/interactive_search/search/node.cc
    path_planner/src/initializer/interactive_search/search/safety_check.cc
    path_planner/src/initializer/motion_form.cc
    path_planner/src/initializer/motion_graph.cc
    path_planner/src/initializer/motion_graph_cache.cc
    path_planner/src/initializer/motion_search_util.cc
    path_planner/src/initializer/motion_searcher.cc
    path_planner/src/initializer/multi_traj_selector.cc
    path_planner/src/initializer/ref_speed_table.cc
    path_planner/src/initializer/reference_line_cost_feature.cc
    path_planner/src/initializer/reference_line_searcher.cc
    path_planner/src/initializer/search_motion.cc
    path_planner/src/initializer/select_nudge_object.cpp
    path_planner/src/maps/crosswalk.cpp
    path_planner/src/maps/lane.cpp
    path_planner/src/maps/lane_boundaries.cpp
    path_planner/src/maps/lane_boundary.cpp
    path_planner/src/maps/lane_path.cc
    path_planner/src/maps/lane_path_data.cc
    path_planner/src/maps/lane_point.cc
    path_planner/src/maps/lane_sequence.cpp
    path_planner/src/maps/road_boundaries.cpp
    path_planner/src/maps/road_boundary.cpp
    path_planner/src/math/angle.cpp
    path_planner/src/math/cosine_approximation.cc
    path_planner/src/math/cubic_spiral_boundary_value_problem.cc
    path_planner/src/math/cubic_spline.cc
    path_planner/src/math/curve_limits.cpp
    path_planner/src/math/double.cpp
    path_planner/src/math/frenet_frame.cc
    path_planner/src/math/frenet_frame_util.cc
    path_planner/src/math/geometry/aabox2d.cc
    path_planner/src/math/geometry/affine_transformation.cc
    path_planner/src/math/geometry/arc2d.cc
    path_planner/src/math/geometry/box2d.cc
    path_planner/src/math/geometry/grid_frame_util.cc
    path_planner/src/math/geometry/halfplane.cc
    path_planner/src/math/geometry/intersection_util.cc
    path_planner/src/math/geometry/kdtree.cc
    path_planner/src/math/geometry/polygon2d.cc
    path_planner/src/math/geometry/polygon2d_util.cc
    path_planner/src/math/geometry/polyline2d.cc
    path_planner/src/math/geometry/segment2d.cc
    path_planner/src/math/geometry/util.cc
    path_planner/src/math/line_curve1d.cpp
    path_planner/src/math/line_curve2d.cpp
    path_planner/src/math/linear_interpolation.cpp
    path_planner/src/math/math_utils.cpp
    path_planner/src/math/piecewise_const_function.cc
    path_planner/src/math/quintic_spiral_boundary_value_problem.cc
    path_planner/src/math/rtree/boost_geometry_common.cpp
    path_planner/src/math/rtree/bvh_common.cpp
    path_planner/src/math/segment_matcher/segment_matcher.cc
    path_planner/src/math/segment_matcher/segment_matcher_kdtree.cc
    path_planner/src/math/sin_table.cpp
    path_planner/src/math/spiral.cc
    path_planner/src/math/util.cc
    path_planner/src/math/vec.cc
    path_planner/src/math/vec2d.cpp
    path_planner/src/math/vec3d.cpp
    path_planner/src/object/object_history.cc
    path_planner/src/object/planner_object.cc
    path_planner/src/object/spacetime_object_state.cc
    path_planner/src/object/spacetime_object_trajectory.cc
    path_planner/src/object/spacetime_planner_object_trajectories_filter.cc
    path_planner/src/object/spacetime_trajectory_manager.cc
    path_planner/src/optimization/ddp/buffer_calc_util.cc
    path_planner/src/optimization/ddp/ddp_optimizer.cc
    path_planner/src/optimization/ddp/object_cost_util.cc
    path_planner/src/optimization/ddp/path_time_corridor.cc
    path_planner/src/optimization/ddp/speed_limit_cost_util.cc
    path_planner/src/optimization/ddp/static_boundary_cost_util.cc
    path_planner/src/optimization/ddp/trajectory_optimizer.cc
    path_planner/src/optimization/ddp/trajectory_optimizer_state.cc
    path_planner/src/optimization/ddp/trajectory_optimizer_util.cc
    path_planner/src/optimization/problem/mixed_fourth_order_bicycle.cc
    path_planner/src/plan/discretized_path.cc
    path_planner/src/plan/mfob_trajectory_smoother.cc
    path_planner/src/plan/planner_flags.cc
    path_planner/src/plan/planner_util.cc
    path_planner/src/plan/second_order_trajectory_point.cc
    path_planner/src/plan/speed_profile.cc
    path_planner/src/plan/trajectory_point.cc
    path_planner/src/plan/trajectory_util.cc
    path_planner/src/prediction/perception_util.cc
    path_planner/src/prediction/predicted_trajectory.cc
    path_planner/src/prediction/prediction.cc
    path_planner/src/prediction/prediction_util.cc
    path_planner/src/router/drive_passage.cc
    path_planner/src/scheduler/path_boundary_builder.cc
    path_planner/src/scheduler/path_boundary_builder_helper.cc
    path_planner/src/scheduler/smooth_reference_line_result.cc
    path_planner/src/speed/speed_limit.cc
    path_planner/src/speed/speed_point.cc
    path_planner/src/speed/st_boundary.cc
    path_planner/src/speed/st_boundary_with_decision.cc
    path_planner/src/speed/st_point.cc
    path_planner/src/speed/vt_point.cc
    path_planner/src/speed/vt_speed_limit.cc
    path_planner/src/util/file_util.cc
    path_planner/src/util/hmi_content_util.cc
    path_planner/src/util/logger_stack.cpp
    path_planner/src/util/min_segment_distance_problem.cc
    path_planner/src/util/path_util.cc
    path_planner/src/util/perception_util.cc
    path_planner/src/util/qtfm_segment_matcher_util.cc
    path_planner/src/util/qtfm_segment_matcher_v2.cc
    path_planner/src/util/status_builder.cc
    path_planner/src/util/thread_pool.cpp
    path_planner/src/util/thread_util.cc
    path_planner/src/util/time_util.cc
    path_planner/src/util/vehicle_geometry_util.cc
)

set(TAP_PLANNING_PROTOS
    path_planner/src/proto/pncx_aabox.proto
    path_planner/src/proto/pncx_aabox3d.proto
    path_planner/src/proto/pncx_affine_transformation.proto
    path_planner/src/proto/pncx_alc.proto
    path_planner/src/proto/pncx_arc2d.proto
    path_planner/src/proto/pncx_autonomy_state.proto
    path_planner/src/proto/pncx_behavior.proto
    path_planner/src/proto/pncx_bev_info.proto
    path_planner/src/proto/pncx_box2d.proto
    path_planner/src/proto/pncx_charts.proto
    path_planner/src/proto/pncx_color.proto
    path_planner/src/proto/pncx_common.proto
    path_planner/src/proto/pncx_constraint.proto
    path_planner/src/proto/pncx_crosswalk_state.proto
    path_planner/src/proto/pncx_driving_style.proto
    path_planner/src/proto/pncx_dynamic_object.proto
    path_planner/src/proto/pncx_est_planner_debug.proto
    path_planner/src/proto/pncx_frame.proto
    path_planner/src/proto/pncx_glog.proto
    path_planner/src/proto/pncx_halfplane.proto
    path_planner/src/proto/pncx_hmi_content.proto
    path_planner/src/proto/pncx_initializer.proto
    path_planner/src/proto/pncx_initializer_config.proto
    path_planner/src/proto/pncx_lane_change.proto
    path_planner/src/proto/pncx_lane_change_type.proto
    path_planner/src/proto/pncx_lane_path.proto
    path_planner/src/proto/pncx_lane_point.proto
    path_planner/src/proto/pncx_lite_common.proto
    path_planner/src/proto/pncx_localization.proto
    path_planner/src/proto/pncx_logic_map.proto
    path_planner/src/proto/pncx_optimizer.proto
    path_planner/src/proto/pncx_perception.proto
    path_planner/src/proto/pncx_piecewise_const_function.proto
    path_planner/src/proto/pncx_piecewise_linear_function.proto
    path_planner/src/proto/pncx_plan_lane_sequence.proto
    path_planner/src/proto/pncx_plan_treesearch.proto
    path_planner/src/proto/pncx_planner.proto
    path_planner/src/proto/pncx_planner_object.proto
    path_planner/src/proto/pncx_planner_params.proto
    path_planner/src/proto/pncx_planner_state.proto
    path_planner/src/proto/pncx_planner_status.proto
    path_planner/src/proto/pncx_planning_config.proto
    path_planner/src/proto/pncx_pnp_info.proto
    path_planner/src/proto/pncx_positioning.proto
    path_planner/src/proto/pncx_prediction.proto
    path_planner/src/proto/pncx_prediction_common.proto
    path_planner/src/proto/pncx_prediction_offline_feature.proto
    path_planner/src/proto/pncx_prediction_rules.proto
    path_planner/src/proto/pncx_reference_line_qp_smoother.proto
    path_planner/src/proto/pncx_route.proto
    path_planner/src/proto/pncx_route_manager_output.proto
    path_planner/src/proto/pncx_route_specific_semantic_map.proto
    path_planner/src/proto/pncx_scene_understanding.proto
    path_planner/src/proto/pncx_scheduler.proto
    path_planner/src/proto/pncx_selector_debug.proto
    path_planner/src/proto/pncx_selector_params.proto
    path_planner/src/proto/pncx_selector_state.proto
    path_planner/src/proto/pncx_smooth_reference_line.proto
    path_planner/src/proto/pncx_speed_finder.proto
    path_planner/src/proto/pncx_speed_finder_params.proto
    path_planner/src/proto/pncx_timestamp.proto
    path_planner/src/proto/pncx_traffic_light.proto
    path_planner/src/proto/pncx_traffic_light_info.proto
    path_planner/src/proto/pncx_trajectory.proto
    path_planner/src/proto/pncx_trajectory_point.proto
    path_planner/src/proto/pncx_trajectory_validation.proto
    path_planner/src/proto/pncx_turn_signal.proto
    path_planner/src/proto/pncx_vector_map.proto
    path_planner/src/proto/pncx_vehicle.proto
)

# Protobuf is part of the runtime ABI: generated sources, headers and the
# linked library must come from the same package.  The Node SDK exposes a
# merged include directory before this target's includes, so falling back to
# the host /usr/bin/protoc while Node uses the platform 3rd-party headers
# creates translation units containing two incompatible Protobuf APIs.
set(TAP_PLANNING_PROTOBUF_ROOT "" CACHE PATH
    "Root of the Protobuf package used by Planning and the host Node")
set(TAP_PLANNING_PROTOBUF_CANDIDATES)
if(TAP_PLANNING_PROTOBUF_ROOT)
    list(APPEND TAP_PLANNING_PROTOBUF_CANDIDATES
        "${TAP_PLANNING_PROTOBUF_ROOT}")
endif()
if(DEFINED PATH_SOURCE_3RDPARTY AND PATH_SOURCE_3RDPARTY)
    list(APPEND TAP_PLANNING_PROTOBUF_CANDIDATES
        "${PATH_SOURCE_3RDPARTY}/protobuf")
endif()

set(TAP_PLANNING_PLATFORM_PROTOBUF_ROOT "")
foreach(candidate IN LISTS TAP_PLANNING_PROTOBUF_CANDIDATES)
    if(EXISTS "${candidate}/bin/protoc" AND
       EXISTS "${candidate}/include/google/protobuf/stubs/common.h" AND
       EXISTS "${candidate}/lib/libprotobuf.so")
        set(TAP_PLANNING_PLATFORM_PROTOBUF_ROOT "${candidate}")
        break()
    endif()
endforeach()

if(TAP_PLANNING_PLATFORM_PROTOBUF_ROOT)
    set(TAP_PLANNING_PROTOC
        "${TAP_PLANNING_PLATFORM_PROTOBUF_ROOT}/bin/protoc")
    set(TAP_PLANNING_PROTOBUF_INCLUDE
        "${TAP_PLANNING_PLATFORM_PROTOBUF_ROOT}/include")
    add_library(tap_planning_protobuf SHARED IMPORTED)
    set_target_properties(tap_planning_protobuf PROPERTIES
        IMPORTED_LOCATION
            "${TAP_PLANNING_PLATFORM_PROTOBUF_ROOT}/lib/libprotobuf.so"
        INTERFACE_INCLUDE_DIRECTORIES
            "${TAP_PLANNING_PLATFORM_PROTOBUF_ROOT}/include")
    message(STATUS
        "Planning Protobuf: using platform package ${TAP_PLANNING_PLATFORM_PROTOBUF_ROOT}")
else()
    # Standalone developer builds may not mount the SenseAuto platform.  The
    # CMake package still supplies all three pieces as one host-side baseline.
    find_package(Protobuf REQUIRED)
    set(TAP_PLANNING_PROTOC "${Protobuf_PROTOC_EXECUTABLE}")
    set(TAP_PLANNING_PROTOBUF_INCLUDE "${Protobuf_INCLUDE_DIRS}")
    if(TARGET protobuf::libprotobuf)
        set(TAP_PLANNING_PROTOBUF_TARGET protobuf::libprotobuf)
    elseif(TARGET Protobuf::libprotobuf)
        set(TAP_PLANNING_PROTOBUF_TARGET Protobuf::libprotobuf)
    else()
        message(FATAL_ERROR "Planning Protobuf package has no libprotobuf target")
    endif()
    message(STATUS
        "Planning Protobuf: using host CMake package ${Protobuf_VERSION}")
endif()
find_package(Threads REQUIRED)

set(TAP_PLANNING_PROTO_SRCS)
set(TAP_PLANNING_PROTO_HDRS)
foreach(proto IN LISTS TAP_PLANNING_PROTOS)
    get_filename_component(proto_name "${proto}" NAME_WE)
    set(proto_src "${TAP_PLANNING_GENERATED_ROOT}/${proto_name}.pb.cc")
    set(proto_hdr "${TAP_PLANNING_GENERATED_ROOT}/${proto_name}.pb.h")
    add_custom_command(
        OUTPUT "${proto_src}" "${proto_hdr}"
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${TAP_PLANNING_GENERATED_ROOT}"
        COMMAND "${TAP_PLANNING_PROTOC}"
                --proto_path=${TAP_PLANNING_PROTO_ROOT}
                --cpp_out=${TAP_PLANNING_GENERATED_ROOT}
                ${CMAKE_CURRENT_LIST_DIR}/${proto}
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/${proto}"
        VERBATIM
    )
    list(APPEND TAP_PLANNING_PROTO_SRCS "${proto_src}")
    list(APPEND TAP_PLANNING_PROTO_HDRS "${proto_hdr}")
endforeach()

# The upstream Initializer contains two search implementations in one source
# file.  TAP production has one product path (Interactive A* -> DDP); compile
# that path as a dedicated variant so DP cannot be selected by a runtime flag.
# The DP implementation is retained in a separate reference target for the
# mandatory build/smoke check, but is not linked by the TAP adapter or Node.
set(TAP_PLANNING_SEARCH_VARIANT_SOURCES
    path_planner/src/initializer/motion_searcher.cc
    path_planner/src/initializer/search_motion.cc)
list(REMOVE_ITEM TAP_PLANNING_SOURCES
    path_planner/src/initializer/motion_searcher.cc
    path_planner/src/initializer/search_motion.cc
    path_planner/src/initializer/dp_motion_searcher_util.cc
    path_planner/src/initializer/motion_graph_cache.cc)

add_library(tap_planning_shared OBJECT
    ${TAP_PLANNING_SOURCES}
    ${TAP_PLANNING_PROTO_SRCS})
add_library(tap_planning_emergency_initializer OBJECT
    ${TAP_PLANNING_SEARCH_VARIANT_SOURCES})
target_compile_definitions(tap_planning_emergency_initializer PRIVATE
    TAP_PLANNING_EMERGENCY_ONLY=1)

add_library(tap_planning_dp_initializer OBJECT
    ${TAP_PLANNING_SEARCH_VARIANT_SOURCES}
    path_planner/src/initializer/dp_motion_searcher_util.cc
    path_planner/src/initializer/motion_graph_cache.cc)
target_compile_definitions(tap_planning_dp_initializer PRIVATE
    TAP_PLANNING_EMERGENCY_ONLY=0)

add_library(tap_planning_core STATIC
    $<TARGET_OBJECTS:tap_planning_shared>
    $<TARGET_OBJECTS:tap_planning_emergency_initializer>)
add_library(tap_planning_dp_reference STATIC
    $<TARGET_OBJECTS:tap_planning_shared>
    $<TARGET_OBJECTS:tap_planning_dp_initializer>)

set(TAP_SDK_ROOT "${CMAKE_CURRENT_LIST_DIR}/../..")
set(TAP_EIGEN_INCLUDE "${TAP_SDK_ROOT}/thirdparty/eigen-3.3.9/include/eigen3")
set(TAP_BOOST_INCLUDE "${TAP_SDK_ROOT}/thirdparty/boost_1.88/include")
set(TAP_BOOST_LIB_ROOT "${TAP_SDK_ROOT}/thirdparty/boost_1.88/lib")
# file_util.cc uses Boost.Filesystem.  The checked-in x86 archive is not
# position independent, so it cannot be folded into the Node shared object.
# Prefer the matching shared artifact on x86; keep the static artifact for
# target/cross builds where the platform package supplies a PIC archive.
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|i.86" AND
   EXISTS "${TAP_BOOST_LIB_ROOT}/libboost_filesystem.so")
    set(TAP_BOOST_FILESYSTEM
        "${TAP_BOOST_LIB_ROOT}/libboost_filesystem.so")
else()
    set(TAP_BOOST_FILESYSTEM
        "${TAP_BOOST_LIB_ROOT}/libboost_filesystem.a")
endif()
set(TAP_ABSL_INCLUDE "${TAP_SDK_ROOT}/thirdparty/abseil-cpp/include")
set(TAP_ABSL_CMAKE "${TAP_SDK_ROOT}/thirdparty/abseil-cpp/lib/cmake/absl")

# The checked-in Abseil archive is used by the target-platform packaging
# flow, but the workspace copy is AArch64.  Host verification in thor_x86
# must use the matching x86_64 platform package instead of silently mixing
# architectures at link time.  Keep the repository copy as the portable
# fallback for cross builds where no platform package is available.
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|i.86")
    foreach(TAP_HOST_ABSL_ROOT
            "/opt/senseauto_active/senseauto-3rdparty/3rdparty/abseil-cpp"
            "/opt/senseauto/senseauto-3rdparty/active/3rdparty/abseil-cpp")
        if(EXISTS "${TAP_HOST_ABSL_ROOT}/lib/cmake/absl/abslConfig.cmake")
            set(TAP_ABSL_INCLUDE "${TAP_HOST_ABSL_ROOT}/include")
            set(TAP_ABSL_CMAKE "${TAP_HOST_ABSL_ROOT}/lib/cmake/absl")
            message(STATUS "Planning Abseil: using host x86 package ${TAP_HOST_ABSL_ROOT}")
            break()
        endif()
    endforeach()
endif()

set(TAP_PLANNING_COMPILE_TARGETS
    tap_planning_shared
    tap_planning_emergency_initializer
    tap_planning_dp_initializer)
foreach(target IN LISTS TAP_PLANNING_COMPILE_TARGETS)
    target_include_directories(${target}
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}"
            "${TAP_PLANNING_SRC_ROOT}"
            "${TAP_PLANNING_SRC_ROOT}/optimization/ddp"
            "${TAP_PLANNING_SRC_ROOT}/optimization/problem"
            "${TAP_PLANNING_GENERATED_ROOT}"
            "${TAP_EIGEN_INCLUDE}"
            "${TAP_BOOST_INCLUDE}"
            "${TAP_ABSL_INCLUDE}"
            ${TAP_PLANNING_PROTOBUF_INCLUDE}
            /opt/senseauto/senseauto-framework-sdk/active/include
            /opt/senseauto/senseauto-rscl/active/include
            /opt/senseauto_active/senseauto-3rdparty/3rdparty/glog/include)
endforeach()

# Object-library usage requirements are not propagated through a static
# archive.  Export the exact same Planning include contract on the two public
# archives so tap_adapter and standalone smoke executables compile against
# the platform Boost/Abseil/ADFramework headers as well.
get_target_property(TAP_PLANNING_SHARED_INCLUDE_DIRS
    tap_planning_shared INCLUDE_DIRECTORIES)
target_include_directories(tap_planning_core PUBLIC
    ${TAP_PLANNING_SHARED_INCLUDE_DIRS})
target_include_directories(tap_planning_dp_reference PUBLIC
    ${TAP_PLANNING_SHARED_INCLUDE_DIRS})

if(EXISTS "${TAP_ABSL_CMAKE}/abslConfig.cmake")
    find_package(absl CONFIG REQUIRED PATHS "${TAP_ABSL_CMAKE}" NO_DEFAULT_PATH)
    set(TAP_PLANNING_ABSL_LIBS
        absl::status
        absl::statusor
        absl::strings
        absl::synchronization
        absl::time
        absl::flat_hash_map)
endif()

if(TARGET tap_planning_protobuf)
    set(TAP_PLANNING_PROTOBUF_LIB tap_planning_protobuf)
else()
    set(TAP_PLANNING_PROTOBUF_LIB ${TAP_PLANNING_PROTOBUF_TARGET})
endif()

set(TAP_PLANNING_LINK_TARGETS
    tap_planning_core
    tap_planning_dp_reference)
foreach(target IN LISTS TAP_PLANNING_LINK_TARGETS)
    target_link_libraries(${target} PUBLIC
        ${TAP_PLANNING_ABSL_LIBS}
        ${TAP_PLANNING_PROTOBUF_LIB}
        Threads::Threads)
endforeach()
if(EXISTS "${TAP_BOOST_FILESYSTEM}")
    # file_util.cc uses Boost.Filesystem; expose the dependency with the core
    # so every final executable gets the implementation matching our headers.
    foreach(target IN LISTS TAP_PLANNING_LINK_TARGETS)
        target_link_libraries(${target} PUBLIC "${TAP_BOOST_FILESYSTEM}")
    endforeach()
endif()

# The migrated logger macros are backed by ADFramework.  Keep a direct library
# fallback for this standalone build; the Node package can still supply its
# normal imported ADFramework target when it integrates the core.
find_library(TAP_AD_LOG_LIBRARY
    NAMES ad_log
    PATHS
        /opt/senseauto/senseauto-rscl/active/lib
        /opt/senseauto_active/senseauto-rscl/active/lib
    NO_DEFAULT_PATH)
if(TAP_AD_LOG_LIBRARY)
    foreach(target IN LISTS TAP_PLANNING_LINK_TARGETS)
        target_link_libraries(${target} PUBLIC "${TAP_AD_LOG_LIBRARY}")
    endforeach()
endif()

# The Thor x86 package currently shipped in the SDK was built with Abseil's
# legacy `absl::string_view` ABI.  In C++17 mode Abseil's drop-in headers
# select `std::string_view`, which makes a target compile successfully but
# fail at link time against that package (and can also duplicate inline
# constants).  The upstream planning build uses the same C++14 setting for
# non-Thor prebuilt Abseil, so keep the ABI choice explicit here.  ARM and
# source/cross builds retain the C++17 requirement used by the migrated core.
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|i.86")
    # The Thor Abseil archives were built with the pre-C++17 string_view ABI.
    # CMAKE_CXX_STANDARD is 17 at the SDK root, so a compile-feature request
    # alone cannot downgrade this target; set the target property explicitly
    # and apply the same standard to consumers that include Abseil headers.
    foreach(target IN LISTS TAP_PLANNING_COMPILE_TARGETS TAP_PLANNING_LINK_TARGETS)
        set_target_properties(${target} PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON)
    endforeach()
else()
    foreach(target IN LISTS TAP_PLANNING_COMPILE_TARGETS TAP_PLANNING_LINK_TARGETS)
        set_target_properties(${target} PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON)
    endforeach()
endif()
set_target_properties(tap_planning_shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(tap_planning_emergency_initializer PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(tap_planning_dp_initializer PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(tap_planning_core PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(tap_planning_dp_reference PROPERTIES POSITION_INDEPENDENT_CODE ON)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|i.86")
    # BVH uses _mm_movehdup_ps in its SSE path; make that ISA requirement
    # explicit instead of relying on the host compiler default.
    foreach(target IN LISTS TAP_PLANNING_COMPILE_TARGETS)
        target_compile_options(${target} PRIVATE -msse3)
    endforeach()
endif()

option(BUILD_TAP_PLANNING_TESTS
       "Build isolated smoke tests for the emergency Planning core" OFF)
if(BUILD_TAP_PLANNING_TESTS)
    enable_testing()
    set(TAP_PLANNING_TEST_DATA_DIR
        "${CMAKE_CURRENT_BINARY_DIR}/tests/data")
    file(MAKE_DIRECTORY "${TAP_PLANNING_TEST_DATA_DIR}")
    configure_file(
        tests/data/trajectory_optimizer_default_params.pb.txt
        "${TAP_PLANNING_TEST_DATA_DIR}/trajectory_optimizer_default_params.pb.txt"
        COPYONLY)
    configure_file(
        tests/data/planner_default_params.pb.txt
        "${TAP_PLANNING_TEST_DATA_DIR}/planner_default_params.pb.txt"
        COPYONLY)
    add_executable(tap_planning_validation_smoke
        tests/normal_planning_validation_smoke.cc)
    add_executable(tap_planning_dp_smoke
        tests/normal_planning_validation_smoke.cc)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|i.86")
        set_target_properties(tap_planning_validation_smoke PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON)
        set_target_properties(tap_planning_dp_smoke PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON)
    endif()
    set(TAP_PLANNING_SMOKE_INCLUDE_DIRS
        "${CMAKE_CURRENT_LIST_DIR}"
        "${TAP_PLANNING_SRC_ROOT}"
        "${TAP_PLANNING_SRC_ROOT}/optimization/ddp"
        "${TAP_PLANNING_SRC_ROOT}/optimization/problem"
        "${TAP_PLANNING_GENERATED_ROOT}"
        "${TAP_EIGEN_INCLUDE}"
        "${TAP_BOOST_INCLUDE}"
        "${TAP_ABSL_INCLUDE}"
        ${TAP_PLANNING_PROTOBUF_INCLUDE}
        /opt/senseauto/senseauto-framework-sdk/active/include
        /opt/senseauto/senseauto-rscl/active/include
        /opt/senseauto_active/senseauto-3rdparty/3rdparty/glog/include)
    target_include_directories(tap_planning_validation_smoke PRIVATE
        ${TAP_PLANNING_SMOKE_INCLUDE_DIRS})
    target_include_directories(tap_planning_dp_smoke PRIVATE
        ${TAP_PLANNING_SMOKE_INCLUDE_DIRS})
    target_link_libraries(tap_planning_validation_smoke
        PRIVATE tap_planning_core)
    target_link_libraries(tap_planning_dp_smoke
        PRIVATE tap_planning_dp_reference)
    target_compile_definitions(tap_planning_validation_smoke PRIVATE
        TAP_PLANNING_TEST_DATA_DIR="${TAP_PLANNING_TEST_DATA_DIR}")
    target_compile_definitions(tap_planning_dp_smoke PRIVATE
        TAP_PLANNING_TEST_DATA_DIR="${TAP_PLANNING_TEST_DATA_DIR}"
        TAP_PLANNING_DP_SMOKE=1)
    add_test(NAME tap_planning_validation_smoke
             COMMAND tap_planning_validation_smoke)
    add_test(NAME tap_planning_dp_smoke
             COMMAND tap_planning_dp_smoke)
endif()

add_custom_target(tap_planning_proto ALL
    DEPENDS ${TAP_PLANNING_PROTO_SRCS} ${TAP_PLANNING_PROTO_HDRS})
add_dependencies(tap_planning_shared tap_planning_proto)
add_dependencies(tap_planning_core tap_planning_proto)
add_dependencies(tap_planning_dp_reference tap_planning_proto)

install(TARGETS tap_planning_core ARCHIVE DESTINATION lib)
# The x86 Node links Boost.Filesystem dynamically because the checked-in
# archive is not PIC. Package the versioned SONAME beside the component; the
# component's production RPATH already searches the TAP lib directory.
if(TAP_BOOST_FILESYSTEM MATCHES "\\.so$")
    get_filename_component(TAP_BOOST_FILESYSTEM_REAL
        "${TAP_BOOST_FILESYSTEM}" REALPATH)
    install(FILES "${TAP_BOOST_FILESYSTEM_REAL}" DESTINATION lib)
endif()
install(DIRECTORY "${TAP_PLANNING_SRC_ROOT}/"
        DESTINATION include/tap_planning
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
install(FILES ${TAP_PLANNING_PROTO_HDRS} DESTINATION include/tap_planning/proto)
# Runtime parameters are reviewed emergency Planning inputs, not generated code.
# Keep them beside the installed core so Node can load the exact same bundle
# used by the independent closed-loop smoke.
install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/resource/config/"
        DESTINATION share/tap_planning/config
        FILES_MATCHING PATTERN "*.pb.txt")
