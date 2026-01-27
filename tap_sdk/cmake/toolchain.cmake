
if(TOOLCHAIN_IS_INCLUDED)
return()
endif()
set(TOOLCHAIN_IS_INCLUDED CACHE BOOL "" true)

## LIB_SUFFIX
if(NOT DEFINED TARGET_OS)
    if(CMAKE_HOST_SYSTEM_NAME MATCHES Linux*)
        set(TARGET_OS linux)
    elseif(CMAKE_HOST_SYSTEM_NAME MATCHES Darwin*)
        set(TARGET_OS mac)
    elseif(CMAKE_HOST_SYSTEM_NAME MATCHES Windows*)
        set(TARGET_OS windows)
    endif()
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES i.86 OR BUILD_I386)
    set(PLATFORM_NAME x86)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES x86*)
    set(PLATFORM_NAME x86_64)
    add_definitions(-Dx86_64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES armv7*)
    set(PLATFORM_NAME armv7)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES aarch64)
    set(PLATFORM_NAME aarch64)
endif()

## COLOR INFO
if(NOT WIN32)
    string(ASCII 27 Esc)
    set(ColourReset "${Esc}[m")
    set(ColourBold  "${Esc}[1m")
    set(Red         "${Esc}[31m")
    set(Green       "${Esc}[32m")
    set(Yellow      "${Esc}[33m")
    set(Blue        "${Esc}[34m")
    set(Magenta     "${Esc}[35m")
    set(Cyan        "${Esc}[36m")
    set(White       "${Esc}[37m")
    set(BoldRed     "${Esc}[1;31m")
    set(BoldGreen   "${Esc}[1;32m")
    set(BoldYellow  "${Esc}[1;33m")
    set(BoldBlue    "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan    "${Esc}[1;36m")
    set(BoldWhite   "${Esc}[1;37m")
endif()

function(VMESSAGE SEVERITY COMMAND)
    set(one_value_args LOG_LEVEL)
    cmake_parse_arguments(ARG
        "ALWAYS"
        "${one_value_args}"
        ""
        ${ARGN})
    set(_log_level 0)
    if (ARG_LOG_LEVEL)
        set(_log_level ${ARG_LOG_LEVEL})
    endif()
    set(_env_log_level $ENV{LOG_LEVEL})
    if (NOT _env_log_level)
        set(_env_log_level -1)
    endif()
    if(ARG_ALWAYS)
        message(${SEVERITY} ${COMMAND})
    elseif((${_env_log_level} GREATER ${_log_level}) OR (${_env_log_level} EQUAL ${_log_level}))
        message(${SEVERITY} ${COMMAND})
    endif()
endfunction()

macro(find_package)
    if (NOT TARGET ${ARGV0} AND NOT TARGET ${ARGV0}::${ARGV0})
        _find_package(${ARGV})
    else()
        if (TARGET ${ARGV0}::${ARGV0})
            set(_target ${ARGV0}::${ARGV0})
            get_target_property(type ${_target} TYPE)
            if (NOT ${type} STREQUAL "INTERFACE_LIBRARY")
                get_target_property(_target_version ${_target} VERSION)
            endif()
            get_target_property(_target_include_dirs ${_target} INTERFACE_INCLUDE_DIRECTORIES)
        else()
            set(_target ${ARGV0})
            get_target_property(type ${_target} TYPE)
            if (NOT ${type} STREQUAL "INTERFACE_LIBRARY")
                get_target_property(_target_version ${_target} VERSION)
            endif()
            get_target_property(_target_include_dirs ${_target} INTERFACE_INCLUDE_DIRECTORIES)
        endif()
        #message(STATUS "Found ${ARGV0}: Target: ${_target}, Version: ${_target_version}, Include dirs: ${_target_include_dirs}")
        #message(STATUS "Variable-like include dirs: ${${ARGV0}_INCLUDE_DIRS}")
        unset(_target)
        unset(_target_version)
        set(${ARGV0}_FOUND TRUE)
    endif()
endmacro()

if(WITH_MDC)
    set(PATH_SOURCE_3RDPARTY ${CMAKE_SOURCE_DIR}/../../senseauto-gac-3rdparty)
elseif(WITH_ORIN)
    set(PATH_SOURCE_3RDPARTY /opt/senseauto/senseauto-3rdparty/active/3rdparty)
else()
    set(PATH_SOURCE_3RDPARTY /opt/senseauto/senseauto-3rdparty/active/3rdparty)
endif()

function(generate_proto)
    cmake_parse_arguments(ARG
        ""
        "PROTO_NAME;PROTO_PATH;PROTO_DEP;PROTO_SRC;PROTO_INCLUDE"
        ""
        ${ARGN}
        )
    ## handle protobuf
    if (CMAKE_CROSSCOMPILING)
        set(PROTOC_ENV LD_LIBRARY_PATH=${PATH_SOURCE_3RDPARTY}/bin/protoc/linux_x86_64/)
        set(PROTOC_BIN ${PATH_SOURCE_3RDPARTY}/bin/protoc/linux_x86_64/protoc)
    else()
        message(STATUS "++++++++++++++++++++CMAKE CROSSCOMPILING IS NOT SET++++++++++++++++++++")
        set(PROTOC_ENV LD_LIBRARY_PATH=${PATH_SOURCE_3RDPARTY}/bin/protoc/linux_${PLATFORM_NAME}/)
        set(PROTOC_BIN ${PATH_SOURCE_3RDPARTY}/bin/protoc/linux_${PLATFORM_NAME}/protoc)
    endif()
    # to prevent recompile after cmake
    execute_process(
        COMMAND
            mkdir -p auto_generate/proto_tmp
        COMMAND
            mkdir -p auto_generate/proto
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}
    )
    execute_process(
        COMMAND
            ${CMAKE_COMMAND} -E env ${PROTOC_ENV}
            ${PROTOC_BIN} -I=${${ARG_PROTO_PATH}} -I=${common_proto_path} --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/auto_generate/proto_tmp/ ${${ARG_PROTO_PATH}}/${ARG_PROTO_NAME}.proto ${${ARG_PROTO_DEP}}
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}
    )

    execute_process(
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/auto_generate/proto_tmp/${ARG_PROTO_NAME}.pb.cc ${CMAKE_BINARY_DIR}/auto_generate/${PROJECT_NAME}/proto/${ARG_PROTO_NAME}.pb.cc
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/auto_generate/proto_tmp/${ARG_PROTO_NAME}.pb.h ${CMAKE_BINARY_DIR}/auto_generate/${PROJECT_NAME}/proto/${ARG_PROTO_NAME}.pb.h
    )
    execute_process(
        COMMAND
            rm -rf auto_generate/proto_tmp
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}
    )
    set(proto_includes ${CMAKE_BINARY_DIR}/auto_generate/${PROJECT_NAME}/
                       ${CMAKE_BINARY_DIR}/auto_generate/perception_common/
                       ### For Module Proto
                       ${CMAKE_BINARY_DIR}/auto_generate/perception_common/proto/
    )
    file(GLOB proto_src_file "${CMAKE_BINARY_DIR}/auto_generate/${PROJECT_NAME}/proto/*.pb.cc")
    file(GLOB common_proto_src "${CMAKE_BINARY_DIR}/auto_generate/perception_common/proto/*.pb.cc")
    if(ARG_PROTO_INCLUDE)
        set(${ARG_PROTO_INCLUDE} ${proto_includes} PARENT_SCOPE)
    endif()
    if(ARG_PROTO_SRC)
        set(${ARG_PROTO_SRC} ${proto_src_file} ${common_proto_src} PARENT_SCOPE)
    endif()
endfunction()

function(generate_unittests)
    cmake_parse_arguments(ARG
        ""
        "HEADER;SOURCE;PRIVATE_LIBRARIES;PUBLIC_LIBRARIES;LIBRARIES_DIR"
        ""
        ${ARGN}
        )
    list(APPEND GLOG_STATIC_DEPS
        gtest
    )
    list(APPEND GLOG_SHARED_DEPS
        gflags
        glog
    )
    find_3rdparty_package(
        HAS_ROOT_INCLUDE
        HEADER glog_includes
        LIBRARIES glog_libraries
        STATIC_DEPS GLOG_STATIC_DEPS
        SHARED_DEPS GLOG_SHARED_DEPS
    )
    foreach(unittest ${${ARG_SOURCE}})
        string(REGEX MATCH "[^/]+$" SRC_FILE ${unittest})
        string(REPLACE ".cpp" "" APP_NAME ${SRC_FILE})
        set(_target_name ${APP_NAME})
        if(${_target_name} MATCHES "unittest")
            if(TARGET ${_target_name})
                continue()
            endif()
            add_executable(${_target_name} ${unittest})
            link_directories(${_target_name} PRIVATE
                                    ${${ARG_LIBRARIES_DIR}}
            )
            target_include_directories(${_target_name} PRIVATE
                    ${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${glog_includes}
                    ${${ARG_HEADER}}
                    ${CMAKE_CURRENT_SOURCE_DIR}/src
            )
            target_link_libraries(${_target_name} PRIVATE
                    ${glog_libraries}
                    ${${ARG_PUBLIC_LIBRARIES}}
                    ${${ARG_PRIVATE_LIBRARIES}}
            )
            add_test(NAME ${_target_name} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${_target_name})
        endif()
    endforeach()
    set(test_data_path ${CMAKE_CURRENT_SOURCE_DIR}/unittests/${PROJECT_NAME}_test_data)
    set(local_config_path ${CMAKE_CURRENT_SOURCE_DIR}/unittests/${PROJECT_NAME}_config)
    if(EXISTS ${test_data_path})
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${test_data_path} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_test_data)
    endif()
    if(EXISTS ${local_config_path})
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${local_config_path} ${CMAKE_CURRENT_BINARY_DIR}/config)
    endif()
endfunction()

include(CTest)
function(generate_library)
    cmake_parse_arguments(ARG
        "SHARED"
        "LIB_NAME;EXPORT_NAME;MODULE_NAME;HEADER;MODULE_HEADER;SOURCE;PRIVATE_LIBRARIES;PUBLIC_LIBRARIES;LIBRARIES_DIR"
        ""
        ${ARGN}
        )
    if (TARGET ${ARG_LIB_NAME})
        VMESSAGE(STATUS "${BoldGreen}[${PROJECT_NAME}]${ColourReset} Already had library: ${Cyan}${LIB_NAME}${ColourReset}" LOG_LEVEL 1)
        return()
    endif()
    if (ARG_SHARED)
        add_library(${ARG_LIB_NAME} SHARED ${${ARG_SOURCE}})
    else()
        add_library(${ARG_LIB_NAME} STATIC ${${ARG_SOURCE}})
    endif()
    add_library(${ARG_EXPORT_NAME}::${ARG_EXPORT_NAME} ALIAS ${ARG_LIB_NAME})
    ### Include Directories for Lib
    target_include_directories(${ARG_LIB_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:perception_sdk/${ARG_MODULE_NAME}/include>
            ${${ARG_HEADER}}
            ${${ARG_MODULE_HEADER}}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
    ### Link Directories for Lib
    link_directories(${ARG_LIB_NAME}
        PUBLIC
            ${${ARG_LIBRARIES_DIR}}
    )
    ### Link Libraries for Lib
    target_link_libraries(${ARG_LIB_NAME}
        PUBLIC
            ${${ARG_PUBLIC_LIBRARIES}}
        PRIVATE
            ${${ARG_PRIVATE_LIBRARIES}}
    )
endfunction()

set(PATH_SOURCE_3RDPARTY ${SENSEAUTO_DEV_INSTALLED_ROOT}/opt/senseauto/senseauto-3rdparty/active/3rdparty)
set(RSCL_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})

# include(${BUILDTOOLS_UTILS_CMAKE_DIR}/SenseIdlUtils.cmake)
# include(${BUILDTOOLS_UTILS_CMAKE_DIR}/SenseInstallUtils.cmake)


function(find_3rdparty_package)
    cmake_parse_arguments(ARG
        "HAS_ROOT_INCLUDE"
        "HEADER;LIBRARIES;STATIC_DEPS;SHARED_DEPS;LIBRARIES_DIR"
        ""
        ${ARGN}
        )
    set(_target_includes)
    list(APPEND _target_includes ${PATH_SOURCE_3RDPARTY}/include)
    set(_target_libs_fullpath)
    if (WITH_ORIN)
        set(_libs_root ${PATH_SOURCE_3RDPARTY}/lib)
    else()
        set(_libs_root ${PATH_SOURCE_3RDPARTY}/lib)
    endif()
    if(IS_DIRECTORY ${_libs_root})
        # Search for libraries
        file(GLOB_RECURSE _static_libs "${_libs_root}/*.a")
        foreach(_dep ${${ARG_STATIC_DEPS}})
            # Specifiy dep name
            string(REGEX REPLACE "(.*)[.]a$" "\\1" _temp ${_dep})
            string(REGEX REPLACE "^lib(.*)" "\\1" _dep_name ${_temp})
            set(_include_seperate ${PATH_SOURCE_3RDPARTY}/${_dep_name}/include)
            set(_include_merged ${PATH_SOURCE_3RDPARTY}/include/${_dep_name})
            if(IS_DIRECTORY ${_include_seperate})
                list(APPEND _target_includes ${_include_seperate})
            elseif(IS_DIRECTORY ${_include_merged})
                list(APPEND _target_includes ${_include_merged})
            endif()
            # Fetch 3rdparty static libraries fullpath
            foreach(_lib_fullpath ${_static_libs})
                string(REGEX MATCH "3rdparty/.*$" _lib_strip_path ${_lib_fullpath})
                if("${_lib_strip_path}" MATCHES "${_dep}")
                    list(APPEND _target_libs_fullpath "${_lib_fullpath}")
                endif()
            endforeach()
        endforeach()
        # Search for libraries
        file(GLOB _shared_libs "${_libs_root}/*.so")
        file(GLOB _shared_cuda_dependent_libs "${_libs_root}/${TARGET_OS}_${PLATFORM_NAME}-CUDA${CUDA_VERSION_MAJOR}.0/*.so")
        list(APPEND _shared_libs ${_shared_cuda_dependent_libs})
        foreach(_dep ${${ARG_SHARED_DEPS}})
            # Specifiy dep name
            string(REGEX REPLACE "(.*)[.]so.*$" "\\1" _temp ${_dep})
            string(REGEX REPLACE "^lib(.*)" "\\1" _dep_name ${_temp})
            set(_include_seperate ${PATH_SOURCE_3RDPARTY}/${_dep_name}/include)
            set(_include_merged ${PATH_SOURCE_3RDPARTY}/include/${_dep_name})
            if(IS_DIRECTORY ${_include_seperate})
                list(APPEND _target_includes ${_include_seperate})
            elseif(IS_DIRECTORY ${_include_merged})
                list(APPEND _target_includes ${_include_merged})
            endif()
            # Fetch 3rdparty static libraries fullpath
            foreach(_lib_fullpath ${_shared_libs})
                string(REGEX MATCH "3rdparty/.*$" _lib_strip_path ${_lib_fullpath})
                if("${_lib_strip_path}" MATCHES "${_dep}")
                    list(APPEND _target_libs_fullpath "${_lib_fullpath}")
                endif()
            endforeach()
        endforeach()
    else()
        message(FATAL_ERROR "${BoldRed}3rdparty libraries root: ${_libs_root} not found.${ColourReset}")
    endif()
    if(ARG_HAS_ROOT_INCLUDE)
        list(APPEND _target_includes ${PATH_SOURCE_3RDPARTY}/include)
    endif()
    if(_target_includes)
        list(REMOVE_DUPLICATES _target_includes)
    endif()
    if(_target_libs_fullpath)
        list(REMOVE_DUPLICATES _target_libs_fullpath)
    endif()
    if(ARG_HEADER)
        set(${ARG_HEADER} ${_target_includes} PARENT_SCOPE)
    endif()
    if(ARG_LIBRARIES)
        set(${ARG_LIBRARIES} ${_target_libs_fullpath} PARENT_SCOPE)
    endif()
    if(ARG_LIBRARIES_DIR)
        set(_target_lib_dirs)
        foreach(_target_lib_fullpath ${_target_libs_fullpath})
            get_filename_component(_target_lib_dir ${_target_lib_fullpath} DIRECTORY)
            list(APPEND _target_lib_dirs ${_target_lib_dir})
        endforeach()
        set(${ARG_LIBRARIES_DIR} ${_target_lib_dirs} PARENT_SCOPE)
    endif()
endfunction()
